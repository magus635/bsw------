"""Tests for IntegrationWizard and ProjectController integration flow."""
import json
from pathlib import Path
from unittest.mock import MagicMock

import pytest
from PySide6.QtCore import Qt
from PySide6.QtWidgets import QFileDialog, QInputDialog, QMessageBox

from autosar_configurator.core.packages.library import LibraryRef
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.ui.controllers.project_controller import ProjectController
from autosar_configurator.ui.wizards.integration_wizard import IntegrationWizard


_DEF_XML = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Vendor</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>{module}</SHORT-NAME>
          <CONTAINERS>
            <ECUC-PARAM-CONF-CONTAINER-DEF>
              <SHORT-NAME>{module}General</SHORT-NAME>
              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
              <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
              <PARAMETERS>
                <ECUC-STRING-PARAM-DEF>
                  <SHORT-NAME>Mode</SHORT-NAME>
                </ECUC-STRING-PARAM-DEF>
              </PARAMETERS>
            </ECUC-PARAM-CONF-CONTAINER-DEF>
          </CONTAINERS>
        </ECUC-MODULE-DEF>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""

_REC_XML = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Vendor</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>{module}_Rec</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/{module}</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>{module}General</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/{module}/{module}General</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-TEXTUAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Vendor/{module}/{module}General/Mode</DEFINITION-REF>
                  <VALUE>{mode}</VALUE>
                </ECUC-TEXTUAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


def _make_package_lib(lib_dir: Path, module: str = "Foo", mode: str = "Fast") -> Path:
    pkg_dir = lib_dir / module
    (pkg_dir / "def").mkdir(parents=True, exist_ok=True)
    (pkg_dir / "config").mkdir(parents=True, exist_ok=True)
    (pkg_dir / "def" / f"{module}.arxml").write_text(_DEF_XML.format(module=module), encoding="utf-8")
    (pkg_dir / "config" / f"{module}_rec.arxml").write_text(
        _REC_XML.format(module=module, mode=mode), encoding="utf-8"
    )
    (pkg_dir / "module.json").write_text(
        json.dumps({
            "schema": 1,
            "module": module,
            "definition": f"/Vendor/{module}",
            "files": [f"def/{module}.arxml", f"config/{module}_rec.arxml"],
            "pre": [],
            "rec": [f"/Vendor/{module}_Rec"],
        }),
        encoding="utf-8",
    )
    return lib_dir


def _new_v8_project(tmp_path: Path, with_lib: bool = True):
    wm = WorkspaceManager()
    project = wm.create_project("TestProj", tmp_path / "proj" / "TestProj.dpa", format_version=8)
    project.selected_chip = None
    lib_dir = _make_package_lib(tmp_path / "lib", "Foo", "Fast")
    if with_lib:
        project.module_libraries.append(LibraryRef(path=lib_dir.as_posix(), kind="package"))
    return wm, project, lib_dir


def test_add_library_and_cancel_does_not_mutate_project(qtbot, monkeypatch, tmp_path):
    wm, project, lib_dir = _new_v8_project(tmp_path, with_lib=False)
    extra_lib = _make_package_lib(tmp_path / "extra_lib", "Bar", "Eco")

    wizard = IntegrationWizard(project)
    qtbot.addWidget(wizard)
    lib_page = wizard.page(wizard.pageIds()[0])

    monkeypatch.setattr(QFileDialog, "getExistingDirectory", lambda *a, **k: str(extra_lib))
    monkeypatch.setattr(QInputDialog, "getItem", lambda *a, **k: ("package", True))

    # Must not raise AttributeError (previously called QComboBox.getItem)
    lib_page._add_library()
    assert len(lib_page.get_data()["libraries"]) == 1
    assert lib_page.lib_table.item(0, 2).text() == "1"

    # Rejecting/canceling wizard leaves project.module_libraries untouched
    wizard.reject()
    assert project.module_libraries == []


def test_accept_emits_wizard_completed_once_and_updates_tree(qtbot, monkeypatch, tmp_path):
    wm, project, _ = _new_v8_project(tmp_path, with_lib=True)

    wizard = IntegrationWizard(project)
    qtbot.addWidget(wizard)
    mod_page = wizard.page(wizard.pageIds()[1])
    mod_page.initializePage()
    mod_page._select_all()
    assert len(mod_page._get_selected_candidates()) == 1

    emitted = []
    wizard.wizard_completed.connect(lambda res: emitted.append(res))
    wizard.accept()

    assert len(emitted) == 1
    assert emitted[0]["added"] == ["Foo"]
    assert "Foo" in project.module_managers
    assert project.module_managers["Foo"].configuration.containers[0].parameter_values["Mode"].value == "Fast"

    # Controller refresh on completion
    win = MagicMock()
    win.current_project = project
    info_calls = []
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: info_calls.append(a) or QMessageBox.Ok)
    ctrl = ProjectController(win)
    ctrl._on_integration_complete(emitted[0])

    assert len(info_calls) == 1
    assert win._has_unsaved_changes is True
    win.tree_view.set_project.assert_called_once_with(project)


def test_skip_and_replace_strategies_behave_distinctly(qtbot, tmp_path):
    # 1. skip: adds new module WITHOUT loading Pre/Rec baseline
    wm, project_skip, _ = _new_v8_project(tmp_path / "skip_case", with_lib=True)
    w_skip = IntegrationWizard(project_skip)
    qtbot.addWidget(w_skip)
    mod_page = w_skip.page(w_skip.pageIds()[1])
    conf_page = w_skip.page(w_skip.pageIds()[2])
    mod_page.initializePage()
    mod_page._select_all()
    conf_page.initializePage()
    conf_page.merge_strategy_skip.setChecked(True)
    w_skip.accept()

    mgr_skip = project_skip.module_managers["Foo"]
    assert mgr_skip.configuration.containers == []

    # 2. replace: overwrites existing saved user config with package Pre/Rec baseline
    wm2, project_rep, lib_dir = _new_v8_project(tmp_path / "replace_case", with_lib=True)
    w_init = IntegrationWizard(project_rep)
    qtbot.addWidget(w_init)
    mp = w_init.page(w_init.pageIds()[1])
    mp.initializePage()
    mp._select_all()
    w_init.accept()
    # User changes Mode to Custom and saves
    mgr = project_rep.module_managers["Foo"]
    mgr.set_parameter_value(mgr.configuration.containers[0], "Mode", "Custom")
    wm2.save_project()

    # Package Rec updated to Ultra
    _make_package_lib(lib_dir, "Foo", "Ultra")

    w_rep = IntegrationWizard(project_rep)
    qtbot.addWidget(w_rep)
    mp2 = w_rep.page(w_rep.pageIds()[1])
    cp2 = w_rep.page(w_rep.pageIds()[2])
    mp2.initializePage()
    # Even though Foo is already installed, it must be selectable
    cat_item = mp2.tree.topLevelItem(0)
    foo_item = cat_item.child(0)
    assert foo_item.flags() & Qt.ItemIsEnabled
    foo_item.setCheckState(0, Qt.Checked)
    cp2.initializePage()
    cp2.merge_strategy_replace.setChecked(True)
    w_rep.accept()

    mgr_after = project_rep.module_managers["Foo"]
    assert mgr_after.configuration.containers[0].parameter_values["Mode"].value == "Ultra"


def test_merge_strategy_respects_confirm_merge_callback(qtbot, tmp_path):
    """merge strategy must pass confirm_merge to reconcile_baseline and track rejections."""
    pre_xml = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>Vendor</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>Foo_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/Foo</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>FooGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/Foo/FooGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/Vendor/Foo/FooGeneral/Mode</DEFINITION-REF>
              <VALUE>{pre_mode}</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>
"""
    wm, project, lib_dir = _new_v8_project(tmp_path / "merge_cb", with_lib=True)
    pkg_dir = lib_dir / "Foo"
    (pkg_dir / "config" / "Foo_pre.arxml").write_text(pre_xml.format(pre_mode="PreInitial"), encoding="utf-8")
    (pkg_dir / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "Foo",
        "definition": "/Vendor/Foo",
        "files": ["def/Foo.arxml", "config/Foo_pre.arxml"],
        "pre": ["/Vendor/Foo_Pre"],
        "rec": [],
    }), encoding="utf-8")

    # Install Foo initially with PreInitial
    w_init = IntegrationWizard(project)
    qtbot.addWidget(w_init)
    mp = w_init.page(w_init.pageIds()[1])
    mp.initializePage()
    mp._select_all()
    w_init.accept()
    wm.save_project()
    assert project.module_managers["Foo"].configuration.containers[0].parameter_values["Mode"].value == "PreInitial"

    # Update Pre in package to PreUpdated
    (pkg_dir / "config" / "Foo_pre.arxml").write_text(pre_xml.format(pre_mode="PreUpdated"), encoding="utf-8")

    # 1. Rejecting confirm_merge leaves Active unchanged and records merge_rejected
    seen_previews = []
    w_rej = IntegrationWizard(
        project,
        confirm_merge=lambda preview, res: seen_previews.append(preview) or False,
    )
    qtbot.addWidget(w_rej)
    mp_rej = w_rej.page(w_rej.pageIds()[1])
    cp_rej = w_rej.page(w_rej.pageIds()[2])
    mp_rej.initializePage()
    mp_rej.tree.topLevelItem(0).child(0).setCheckState(0, Qt.Checked)
    cp_rej.initializePage()
    cp_rej.merge_strategy_merge.setChecked(True)
    w_rej.accept()

    assert len(seen_previews) == 1
    assert w_rej._result["merge_rejected"] == ["Foo"]
    assert "Foo" not in w_rej._result["added"]
    assert project.module_managers["Foo"].configuration.containers[0].parameter_values["Mode"].value == "PreInitial"

    # 2. Accepting confirm_merge applies PreUpdated
    w_acc = IntegrationWizard(project, confirm_merge=lambda preview, res: True)
    qtbot.addWidget(w_acc)
    mp_acc = w_acc.page(w_acc.pageIds()[1])
    cp_acc = w_acc.page(w_acc.pageIds()[2])
    mp_acc.initializePage()
    mp_acc.tree.topLevelItem(0).child(0).setCheckState(0, Qt.Checked)
    cp_acc.initializePage()
    cp_acc.merge_strategy_merge.setChecked(True)
    w_acc.accept()

    assert w_acc._result["merge_rejected"] == []
    assert w_acc._result["added"] == ["Foo"]
    assert project.module_managers["Foo"].configuration.containers[0].parameter_values["Mode"].value == "PreUpdated"


def test_project_controller_integrate_modules_passes_confirm_merge_preview(monkeypatch, tmp_path):
    """ProjectController.integrate_modules() wires _confirm_merge_preview into IntegrationWizard."""
    from autosar_configurator.ui.controllers import project_controller as pc
    from autosar_configurator.ui.wizards import integration_wizard as iw

    _, project, _ = _new_v8_project(tmp_path / "ctrl_cb", with_lib=True)
    win = MagicMock()
    win.current_project = project
    ctrl = ProjectController(win)

    captured = {}

    class _FakeWizard:
        def __init__(self, proj, parent=None, confirm_merge=None):
            captured["project"] = proj
            captured["parent"] = parent
            captured["confirm_merge"] = confirm_merge
            self.wizard_completed = MagicMock()

        def exec(self):
            return 0

    monkeypatch.setattr(iw, "IntegrationWizard", _FakeWizard)
    ctrl.integrate_modules()

    assert captured["project"] is project
    assert captured["parent"] is win
    assert captured["confirm_merge"] == ctrl._confirm_merge_preview


def _make_variant_package_lib(lib_dir: Path) -> Path:
    """Create a package library containing two sibling CanTrcv variants plus Dio."""
    cantrcv_tpl = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>{pkg_sub}</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY>
            <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>"""

    for pkg_dir_name, sw_ver, infix in (
        ("CanTrcv_GenericCan", "1.0.0", "GenericCan"),
        ("CanTrcv_Tle9255", "2.3.0", "Tle9255"),
    ):
        pkg_dir = lib_dir / pkg_dir_name
        (pkg_dir / "config").mkdir(parents=True, exist_ok=True)
        (pkg_dir / "config" / "CanTrcv.arxml").write_text(
            cantrcv_tpl.format(pkg_sub=pkg_dir_name), encoding="utf-8"
        )
        (pkg_dir / "module.json").write_text(
            json.dumps({
                "schema": 1,
                "module": "CanTrcv",
                "definition": f"/MICROSAR/{pkg_dir_name}/CanTrcv",
                "files": ["config/CanTrcv.arxml"],
                "pre": [],
                "rec": [],
                "origin": {
                    "source": "davinci",
                    "sw_version": sw_ver,
                    "implementation": {
                        "sw_version": sw_ver,
                        "vendor_api_infix": infix,
                    },
                },
            }),
            encoding="utf-8",
        )

    dio_dir = lib_dir / "Dio"
    (dio_dir / "config").mkdir(parents=True, exist_ok=True)
    (dio_dir / "config" / "Dio.arxml").write_text(_DEF_XML.format(module="Dio"), encoding="utf-8")
    (dio_dir / "module.json").write_text(
        json.dumps({
            "schema": 1,
            "module": "Dio",
            "definition": "/MICROSAR/Dio",
            "files": ["config/Dio.arxml"],
            "pre": [],
            "rec": [],
        }),
        encoding="utf-8",
    )
    return lib_dir


def test_integration_wizard_distinguishes_variants_and_mutual_exclusion(qtbot, monkeypatch, tmp_path):
    """IntegrationWizard distinguishes sibling variants, enforces mutual exclusion, and skips ambiguous Select All."""
    from autosar_configurator.core.packages.library import find_package, scan_library

    lib_dir = _make_variant_package_lib(tmp_path / "lib")

    # Case 1: project has CanTrcv_Tle9255 installed
    wm = WorkspaceManager()
    project = wm.create_project("VarProj", tmp_path / "proj" / "VarProj.dpa", format_version=8)
    lib_ref = LibraryRef(path=lib_dir.as_posix(), kind="package")
    project.module_libraries.append(lib_ref)
    pkgs = scan_library(lib_ref, tmp_path / "proj")
    lib_idx, tle_pkg = find_package([(0, pkgs)], "/MICROSAR/CanTrcv_Tle9255/CanTrcv")
    project.add_module_from_package(tle_pkg, lib_index=lib_idx, persist=True, confirm=lambda *_: True)

    wizard = IntegrationWizard(project)
    qtbot.addWidget(wizard)
    mod_page = wizard.page(wizard.pageIds()[1])
    mod_page.initializePage()

    assert mod_page.tree.columnCount() == 5

    items_by_def = {}
    for i in range(mod_page.tree.topLevelItemCount()):
        cat_item = mod_page.tree.topLevelItem(i)
        for j in range(cat_item.childCount()):
            child = cat_item.child(j)
            cand = child.data(0, Qt.UserRole)
            if cand is not None:
                items_by_def[cand.package.manifest.definition] = (child, cand)

    tle_item, tle_cand = items_by_def["/MICROSAR/CanTrcv_Tle9255/CanTrcv"]
    gen_item, gen_cand = items_by_def["/MICROSAR/CanTrcv_GenericCan/CanTrcv"]

    assert tle_cand.is_installed is True
    assert tle_cand.is_other_variant is False
    assert tle_item.text(4) == "Installed"

    assert gen_cand.is_installed is False
    assert gen_cand.is_other_variant is True
    assert gen_item.text(4) == "Other Variant"

    mod_page.tree.setCurrentItem(tle_item)
    html = mod_page.detail_browser.toHtml()
    assert "2.3.0" in html
    assert "Tle9255" in html
    assert "/MICROSAR/CanTrcv_Tle9255/CanTrcv" in html

    mod_page._apply_filter("Tle9255")
    assert gen_item.isHidden() is True
    assert tle_item.isHidden() is False
    mod_page._apply_filter("")
    assert gen_item.isHidden() is False
    assert tle_item.isHidden() is False

    # Mutual exclusion: checking CanTrcv_GenericCan then CanTrcv_Tle9255 unchecks GenericCan
    gen_item.setCheckState(0, Qt.Checked)
    tle_item.setCheckState(0, Qt.Checked)
    assert gen_item.checkState(0) == Qt.Unchecked
    assert tle_item.checkState(0) == Qt.Checked
    assert [c.package.manifest.definition for c in mod_page._get_selected_candidates()] == [
        "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    ]

    # Case 2: fresh project -> Select All skips ambiguous CanTrcv variants, checks Dio only
    wm2 = WorkspaceManager()
    fresh_project = wm2.create_project("FreshProj", tmp_path / "fresh" / "FreshProj.dpa", format_version=8)
    fresh_project.module_libraries.append(lib_ref)

    wizard2 = IntegrationWizard(fresh_project)
    qtbot.addWidget(wizard2)
    mod_page2 = wizard2.page(wizard2.pageIds()[1])
    conf_page2 = wizard2.page(wizard2.pageIds()[2])
    mod_page2.initializePage()
    mod_page2._select_all()

    selected_mods = [c.package.manifest.module for c in mod_page2._get_selected_candidates()]
    assert selected_mods == ["Dio"]
    assert "CanTrcv" in mod_page2.last_skipped_ambiguous

    # ConfirmationPage blocks duplicate module candidates
    fresh_items = {}
    for i in range(mod_page2.tree.topLevelItemCount()):
        cat_item = mod_page2.tree.topLevelItem(i)
        for j in range(cat_item.childCount()):
            child = cat_item.child(j)
            cand = child.data(0, Qt.UserRole)
            if cand is not None:
                fresh_items[cand.package.manifest.definition] = cand
    dup_cands = [
        fresh_items["/MICROSAR/CanTrcv_GenericCan/CanTrcv"],
        fresh_items["/MICROSAR/CanTrcv_Tle9255/CanTrcv"],
    ]
    monkeypatch.setattr(mod_page2, "get_data", lambda: {"selected": dup_cands})
    warn_calls = []
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **k: warn_calls.append(a) or QMessageBox.Ok)
    conf_page2.initializePage()
    assert conf_page2.validatePage() is False
    assert len(warn_calls) == 1


def test_tree_view_and_properties_dialog_show_variant_and_switch_flow(qtbot, monkeypatch, tmp_path):
    """DaVinciTreeView, ProjectPropertiesDialog, and ProjectController support variant display and switching."""
    from PySide6.QtWidgets import QMenu
    from autosar_configurator.core.packages.library import find_package, scan_library
    from autosar_configurator.ui.dialogs.project_properties_dialog import ProjectPropertiesDialog
    from autosar_configurator.ui.widgets.davinci_tree_view import DaVinciTreeView

    proj_dir = tmp_path / "Proj"
    _make_variant_package_lib(proj_dir / "modules")

    wm = WorkspaceManager()
    project = wm.create_project("Proj", proj_dir / "Proj.dpa", format_version=8)
    lib_ref = LibraryRef(path="modules", kind="package")
    project.module_libraries.append(lib_ref)
    pkgs = scan_library(lib_ref, proj_dir)
    lib_idx, tle_pkg = find_package([(0, pkgs)], "/MICROSAR/CanTrcv_Tle9255/CanTrcv")
    project.add_module_from_package(tle_pkg, lib_index=lib_idx, persist=True, confirm=lambda *_: True)
    wm.save_project()

    variant_tpl = proj_dir / "templates" / "CanTrcv_Tle9255" / "CanTrcv_Cfg.h"
    variant_tpl.parent.mkdir(parents=True, exist_ok=True)
    variant_tpl.write_text("/* tle overlay */\n", encoding="utf-8")

    # 1. DaVinciTreeView label, tooltip, and Switch Variant context menu signal
    tree = DaVinciTreeView()
    qtbot.addWidget(tree)
    tree.set_project(project)
    cantrcv_item = next(
        tree.topLevelItem(i)
        for i in range(tree.topLevelItemCount())
        if tree.topLevelItem(i).data(0, Qt.UserRole)["def"].short_name == "CanTrcv"
    )
    assert "CanTrcv_Tle9255" in cantrcv_item.text(0)
    assert "/MICROSAR/CanTrcv_Tle9255/CanTrcv" in cantrcv_item.toolTip(0)

    menu = QMenu(tree)
    tree._populate_module_menu(menu, "CanTrcv")
    switch_actions = [a for a in menu.actions() if "Switch Variant" in a.text()]
    assert len(switch_actions) == 1
    emitted = []
    tree.switch_module_variant_requested.connect(emitted.append)
    switch_actions[0].trigger()
    assert emitted == ["CanTrcv"]

    # 2. ProjectPropertiesDialog displays module definition path and variant overlay template
    dlg = ProjectPropertiesDialog(project, None)
    qtbot.addWidget(dlg)
    assert "/MICROSAR/CanTrcv_Tle9255/CanTrcv" in dlg.modules_text.toPlainText()
    assert dlg.templates_table.rowCount() >= 1
    source_paths = [
        dlg.templates_table.item(r, 3).text()
        for r in range(dlg.templates_table.rowCount())
    ]
    assert any("CanTrcv_Tle9255" in p and "CanTrcv_Cfg.h" in p for p in source_paths)

    # 3. ProjectController.switch_module_variant flow (rejection then confirmed switch)
    win = MagicMock()
    win.current_project = project
    win.config_manager = project.module_managers["CanTrcv"]
    win.module_def = win.config_manager.module_def
    ctrl = ProjectController(win)

    monkeypatch.setattr(
        QInputDialog,
        "getItem",
        lambda parent, title, label, items, *a, **k: (
            next(item for item in items if "/MICROSAR/CanTrcv_GenericCan/CanTrcv" in item),
            True,
        ),
    )
    info_calls = []
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: info_calls.append(a) or QMessageBox.Ok)

    assert ctrl.switch_module_variant("CanTrcv", confirm=lambda *_: False) is False
    assert project.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"

    assert ctrl.switch_module_variant("CanTrcv", confirm=lambda *_: True) is True
    assert project.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_GenericCan/CanTrcv"
    assert win._has_unsaved_changes is True
    win.tree_view.set_project.assert_called_with(project)
    assert len(info_calls) == 1


def _make_pre_and_plain_cantrcv_lib(lib_dir: Path):
    """Build GenericCan (with Pre + CanTrcvHwInterface) and Tle9255 (no Pre/Rec, no HwInterface)."""
    gen_dir = lib_dir / "CanTrcv_GenericCan" / "config"
    gen_dir.mkdir(parents=True, exist_ok=True)
    (gen_dir / "CanTrcv.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_GenericCan</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            <PARAMETERS>
              <ECUC-STRING-PARAM-DEF><SHORT-NAME>CanTrcvHwInterface</SHORT-NAME></ECUC-STRING-PARAM-DEF>
              <ECUC-BOOLEAN-PARAM-DEF><SHORT-NAME>CanTrcvDevErrorDetect</SHORT-NAME></ECUC-BOOLEAN-PARAM-DEF>
            </PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (gen_dir / "CanTrcv_Pre.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><ELEMENTS>
    <ECUC-MODULE-CONFIGURATION-VALUES>
      <SHORT-NAME>CanTrcv_GenericCan_Pre</SHORT-NAME>
      <DEFINITION-REF DEST="ECUC-MODULE-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv</DEFINITION-REF>
      <CONTAINERS>
        <ECUC-CONTAINER-VALUE>
          <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral</DEFINITION-REF>
          <PARAMETER-VALUES>
            <ECUC-TEXTUAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-STRING-PARAM-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral/CanTrcvHwInterface</DEFINITION-REF>
              <VALUE>SPI</VALUE>
            </ECUC-TEXTUAL-PARAM-VALUE>
            <ECUC-NUMERICAL-PARAM-VALUE>
              <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/MICROSAR/CanTrcv_GenericCan/CanTrcv/CanTrcvGeneral/CanTrcvDevErrorDetect</DEFINITION-REF>
              <VALUE>true</VALUE>
            </ECUC-NUMERICAL-PARAM-VALUE>
          </PARAMETER-VALUES>
        </ECUC-CONTAINER-VALUE>
      </CONTAINERS>
    </ECUC-MODULE-CONFIGURATION-VALUES>
  </ELEMENTS></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (lib_dir / "CanTrcv_GenericCan" / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "CanTrcv",
        "definition": "/MICROSAR/CanTrcv_GenericCan/CanTrcv",
        "files": ["config/CanTrcv.arxml", "config/CanTrcv_Pre.arxml"],
        "pre": ["/MICROSAR/CanTrcv_GenericCan_Pre"],
        "rec": [],
    }), encoding="utf-8")

    tle_dir = lib_dir / "CanTrcv_Tle9255" / "config"
    tle_dir.mkdir(parents=True, exist_ok=True)
    (tle_dir / "CanTrcv.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF>
        <SHORT-NAME>CanTrcv</SHORT-NAME>
        <CONTAINERS>
          <ECUC-PARAM-CONF-CONTAINER-DEF>
            <SHORT-NAME>CanTrcvGeneral</SHORT-NAME>
            <LOWER-MULTIPLICITY>1</LOWER-MULTIPLICITY><UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
            <PARAMETERS>
              <ECUC-BOOLEAN-PARAM-DEF><SHORT-NAME>CanTrcvDevErrorDetect</SHORT-NAME></ECUC-BOOLEAN-PARAM-DEF>
            </PARAMETERS>
          </ECUC-PARAM-CONF-CONTAINER-DEF>
        </CONTAINERS>
      </ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
    (lib_dir / "CanTrcv_Tle9255" / "module.json").write_text(json.dumps({
        "schema": 1,
        "module": "CanTrcv",
        "definition": "/MICROSAR/CanTrcv_Tle9255/CanTrcv",
        "files": ["config/CanTrcv.arxml"],
        "pre": [],
        "rec": [],
    }), encoding="utf-8")


def _select_wizard_variant_and_accept(qtbot, project, target_def: str, strategy: str, monkeypatch=None, fail_replace=False):
    wiz = IntegrationWizard(project, confirm_merge=lambda *_: True)
    qtbot.addWidget(wiz)
    mp = wiz.page(wiz.pageIds()[1])
    cp = wiz.page(wiz.pageIds()[2])
    mp.initializePage()
    for i in range(mp.tree.topLevelItemCount()):
        cat_item = mp.tree.topLevelItem(i)
        for j in range(cat_item.childCount()):
            child = cat_item.child(j)
            cand = child.data(0, Qt.UserRole)
            if cand and cand.package.manifest.definition == target_def:
                child.setCheckState(0, Qt.Checked)
    cp.initializePage()
    if strategy == "skip":
        cp.merge_strategy_skip.setChecked(True)
    elif strategy == "replace":
        cp.merge_strategy_replace.setChecked(True)
    else:
        cp.merge_strategy_merge.setChecked(True)
    if fail_replace and monkeypatch is not None:
        def _boom(*_args, **_kwargs):
            raise RuntimeError("boom")
        monkeypatch.setattr(wiz, "_apply_replace_baseline", _boom)
    wiz.accept()
    return wiz


def test_integration_wizard_cross_variant_replace_and_skip_cleanup_and_rollback(qtbot, monkeypatch, tmp_path):
    """Cross-variant skip/replace cleans up stale baseline state safely and rolls back on failure."""
    from autosar_configurator.core.packages.library import find_package, scan_library

    # Scenario A: GenericCan (with Pre) -> Tle9255 (no Pre/Rec) via SKIP
    proj_skip_dir = tmp_path / "skip_proj"
    _make_pre_and_plain_cantrcv_lib(proj_skip_dir / "modules")
    wm_skip = WorkspaceManager()
    proj_skip = wm_skip.create_project("SkipVar", proj_skip_dir / "SkipVar.dpa", format_version=8)
    lib_ref_a = LibraryRef(path="modules", kind="package")
    proj_skip.module_libraries.append(lib_ref_a)
    pkgs_a = scan_library(lib_ref_a, proj_skip_dir)
    _, gen_pkg_a = find_package([(0, pkgs_a)], "/MICROSAR/CanTrcv_GenericCan/CanTrcv")
    proj_skip.add_module_from_package(gen_pkg_a, lib_index=0, persist=True, confirm=lambda *_: True)
    wm_skip.save_project()

    snap_a = proj_skip_dir / "config" / "base" / "CanTrcv.arxml"
    layers_a = proj_skip_dir / "config" / "base" / "CanTrcv.layers.json"
    assert snap_a.is_file() and layers_a.is_file()

    _select_wizard_variant_and_accept(qtbot, proj_skip, "/MICROSAR/CanTrcv_Tle9255/CanTrcv", "skip")
    assert proj_skip.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    assert "CanTrcv" not in proj_skip.baselines
    assert proj_skip.module_entries["CanTrcv"].base_hash is None
    gen_c = proj_skip.module_managers["CanTrcv"].configuration.containers[0]
    assert gen_c.parameter_values["CanTrcvHwInterface"].value == "SPI"
    assert "CanTrcvHwInterface" in gen_c.unknown_parameters
    assert snap_a.is_file()  # deferred until save
    wm_skip.save_project()
    assert not snap_a.exists()
    assert not layers_a.exists()

    # Scenario B: GenericCan (with Pre) -> Tle9255 (no Pre/Rec) via REPLACE
    proj_rep_dir = tmp_path / "rep_proj"
    _make_pre_and_plain_cantrcv_lib(proj_rep_dir / "modules")
    wm_rep = WorkspaceManager()
    proj_rep = wm_rep.create_project("RepVar", proj_rep_dir / "RepVar.dpa", format_version=8)
    lib_ref_b = LibraryRef(path="modules", kind="package")
    proj_rep.module_libraries.append(lib_ref_b)
    pkgs_b = scan_library(lib_ref_b, proj_rep_dir)
    _, gen_pkg_b = find_package([(0, pkgs_b)], "/MICROSAR/CanTrcv_GenericCan/CanTrcv")
    proj_rep.add_module_from_package(gen_pkg_b, lib_index=0, persist=True, confirm=lambda *_: True)
    wm_rep.save_project()

    _select_wizard_variant_and_accept(qtbot, proj_rep, "/MICROSAR/CanTrcv_Tle9255/CanTrcv", "replace")
    rep_mgr = proj_rep.module_managers["CanTrcv"]
    assert rep_mgr.configuration.containers == []
    assert rep_mgr.configuration.definition_ref == "/MICROSAR/CanTrcv_Tle9255/CanTrcv"
    assert "CanTrcv" not in proj_rep.baselines
    assert proj_rep.module_entries["CanTrcv"].base_hash is None
    wm_rep.save_project()
    assert not (proj_rep_dir / "config" / "base" / "CanTrcv.arxml").exists()

    # Scenario C: Failure during cross-variant replace rolls back cleanly
    proj_rb_dir = tmp_path / "rb_proj"
    _make_pre_and_plain_cantrcv_lib(proj_rb_dir / "modules")
    wm_rb = WorkspaceManager()
    proj_rb = wm_rb.create_project("RbVar", proj_rb_dir / "RbVar.dpa", format_version=8)
    lib_ref_c = LibraryRef(path="modules", kind="package")
    proj_rb.module_libraries.append(lib_ref_c)
    pkgs_c = scan_library(lib_ref_c, proj_rb_dir)
    _, gen_pkg_c = find_package([(0, pkgs_c)], "/MICROSAR/CanTrcv_GenericCan/CanTrcv")
    proj_rb.add_module_from_package(gen_pkg_c, lib_index=0, persist=True, confirm=lambda *_: True)
    wm_rb.save_project()

    wiz_err = _select_wizard_variant_and_accept(
        qtbot, proj_rb, "/MICROSAR/CanTrcv_Tle9255/CanTrcv", "replace",
        monkeypatch=monkeypatch, fail_replace=True,
    )
    assert any(m == "CanTrcv" for m, _err in wiz_err._result["failed"])
    assert proj_rb.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_GenericCan/CanTrcv"
    assert proj_rb.module_managers["CanTrcv"].module_def.ar_path == "/MICROSAR/CanTrcv_GenericCan/CanTrcv"
    assert "CanTrcv" in proj_rb.baselines


def test_controller_clears_undo_stack_refreshes_active_mgr_and_disambiguates_duplicate_labels(qtbot, monkeypatch, tmp_path):
    """switch_module_variant distinguishes identical directory names across libraries and clears undo_stack;
    _on_integration_complete also clears undo_stack and refreshes active window module references."""
    from autosar_configurator.core.packages.library import find_package, scan_library

    proj_dir = tmp_path / "DualLibProj"
    lib_a = proj_dir / "lib_a"
    lib_b = proj_dir / "lib_b"
    _make_variant_package_lib(lib_a)
    _make_variant_package_lib(lib_b)

    wm = WorkspaceManager()
    project = wm.create_project("DualLibProj", proj_dir / "DualLibProj.dpa", format_version=8)
    project.module_libraries = [
        LibraryRef(path="lib_a", kind="package"),
        LibraryRef(path="lib_b", kind="package"),
    ]
    pkgs_a = scan_library(project.module_libraries[0], proj_dir)
    _, tle_pkg = find_package([(0, pkgs_a)], "/MICROSAR/CanTrcv_Tle9255/CanTrcv")
    project.add_module_from_package(tle_pkg, lib_index=0, persist=True, confirm=lambda *_: True)

    stale_mgr = project.module_managers["CanTrcv"]
    win = MagicMock()
    win.current_project = project
    win.config_manager = stale_mgr
    win.module_def = stale_mgr.module_def
    ctrl = ProjectController(win)

    seen_items = []

    def _pick_lib_b(_parent, _title, _label, items, *_args, **_kwargs):
        seen_items.extend(items)
        chosen = next(item for item in items if "/MICROSAR/CanTrcv_GenericCan/CanTrcv" in item and "lib_b" in item)
        return chosen, True

    monkeypatch.setattr(QInputDialog, "getItem", _pick_lib_b)
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **k: QMessageBox.Ok)

    assert ctrl.switch_module_variant("CanTrcv", confirm=lambda *_: True) is True
    assert len(seen_items) == len(set(seen_items))
    assert project.module_entries["CanTrcv"].library == 1
    win.undo_stack.clear.assert_called_once()

    # Now simulate wizard completion while main window still held stale_mgr/module_def
    win.undo_stack.clear.reset_mock()
    win.config_panel.clear.reset_mock()
    win.config_manager = stale_mgr
    win.module_def = stale_mgr.module_def
    new_mgr = project.module_managers["CanTrcv"]
    assert new_mgr is not stale_mgr

    ctrl._on_integration_complete({
        "added": ["CanTrcv"],
        "failed": [],
        "merge_conflicts": [],
        "merge_rejected": [],
    })
    win.undo_stack.clear.assert_called_once()
    assert win.config_manager is new_mgr
    assert win.module_def is new_mgr.module_def
    win.config_panel.clear.assert_called_once()


def test_tree_menu_variant_switch_visibility_matches_alternative_definitions(qtbot, tmp_path):
    """Tree context menu shows Switch Variant iff registered libraries contain an alternative definition."""
    from PySide6.QtWidgets import QMenu
    from autosar_configurator.core.model.definition_model import EcucModuleDef
    from autosar_configurator.core.packages.library import find_package, scan_library
    from autosar_configurator.ui.widgets.davinci_tree_view import DaVinciTreeView

    # Case 1: two libraries both provide only /MICROSAR/CanTrcv_Tle9255/CanTrcv -> no Switch Variant
    proj1_dir = tmp_path / "same_def_proj"
    for lib_name in ("lib_1", "lib_2"):
        tle_dir = proj1_dir / lib_name / "CanTrcv_Tle9255" / "config"
        tle_dir.mkdir(parents=True)
        (tle_dir / "CanTrcv.arxml").write_text("""<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES><AR-PACKAGE><SHORT-NAME>MICROSAR</SHORT-NAME><AR-PACKAGES>
    <AR-PACKAGE><SHORT-NAME>CanTrcv_Tle9255</SHORT-NAME><ELEMENTS>
      <ECUC-MODULE-DEF><SHORT-NAME>CanTrcv</SHORT-NAME></ECUC-MODULE-DEF>
    </ELEMENTS></AR-PACKAGE>
  </AR-PACKAGES></AR-PACKAGE></AR-PACKAGES>
</AUTOSAR>""", encoding="utf-8")
        (proj1_dir / lib_name / "CanTrcv_Tle9255" / "module.json").write_text(json.dumps({
            "schema": 1,
            "module": "CanTrcv",
            "definition": "/MICROSAR/CanTrcv_Tle9255/CanTrcv",
            "files": ["config/CanTrcv.arxml"],
            "pre": [],
            "rec": [],
        }), encoding="utf-8")

    wm1 = WorkspaceManager()
    proj1 = wm1.create_project("SameDef", proj1_dir / "SameDef.dpa", format_version=8)
    proj1.module_libraries = [
        LibraryRef(path="lib_1", kind="package"),
        LibraryRef(path="lib_2", kind="package"),
    ]
    pkgs1 = scan_library(proj1.module_libraries[0], proj1_dir)
    _, tle_pkg1 = find_package([(0, pkgs1)], "/MICROSAR/CanTrcv_Tle9255/CanTrcv")
    proj1.add_module_from_package(tle_pkg1, lib_index=0, persist=True, confirm=lambda *_: True)

    tree1 = DaVinciTreeView()
    qtbot.addWidget(tree1)
    tree1.set_project(proj1)
    menu1 = QMenu(tree1)
    tree1._populate_module_menu(menu1, "CanTrcv")
    assert [a for a in menu1.actions() if "Switch Variant" in a.text()] == []

    # Case 2: active module has /MICROSAR/CanTrcv_Old/CanTrcv, library has 1 package /MICROSAR/CanTrcv_Tle9255/CanTrcv -> show Switch Variant
    wm2 = WorkspaceManager()
    proj2 = wm2.create_project("OneAlt", proj1_dir / "OneAlt.dpa", format_version=8)
    proj2.module_libraries = [LibraryRef(path="lib_1", kind="package")]
    old_def = EcucModuleDef(
        short_name="CanTrcv",
        definition_ref="/AUTOSAR/EcucDefs/CanTrcv",
        ar_path="/MICROSAR/CanTrcv_Old/CanTrcv",
    )
    proj2.add_module(old_def, proj1_dir / "old_def.arxml")

    tree2 = DaVinciTreeView()
    qtbot.addWidget(tree2)
    tree2.set_project(proj2)
    menu2 = QMenu(tree2)
    tree2._populate_module_menu(menu2, "CanTrcv")
    assert len([a for a in menu2.actions() if "Switch Variant" in a.text()]) == 1


def test_integration_wizard_replace_prunes_stale_pre_unlocked_and_controller_syncs_chip(qtbot, monkeypatch, tmp_path):
    """Cross-variant replace prunes pre_unlocked keys absent in the target baseline;
    ProjectController.switch_module_variant applies chip selectors and refreshes dep graph."""
    from types import SimpleNamespace
    from PySide6.QtWidgets import QInputDialog, QMessageBox
    from autosar_configurator.core.packages.library import find_package, scan_library
    from autosar_configurator.ui.controllers.project_controller import ProjectController

    proj_dir = tmp_path / "prune_proj"
    _make_pre_and_plain_cantrcv_lib(proj_dir / "modules")
    wm = WorkspaceManager()
    project = wm.create_project("PruneVar", proj_dir / "PruneVar.dpa", format_version=8)
    lib_ref = LibraryRef(path="modules", kind="package")
    project.module_libraries.append(lib_ref)
    pkgs = scan_library(lib_ref, proj_dir)
    _, tle_pkg = find_package([(0, pkgs)], "/MICROSAR/CanTrcv_Tle9255/CanTrcv")
    project.add_module_from_package(tle_pkg, lib_index=0, persist=True, confirm=lambda *_: True)
    project.module_entries["CanTrcv"].pre_unlocked = [
        "P:/CanTrcv/CanTrcvChannel_0.CanTrcvBaudrateRatio",
        "P:/CanTrcv/CanTrcvGeneral.CanTrcvHwInterface",
    ]
    wm.save_project()

    # Replace Tle9255 -> GenericCan (which has Pre for CanTrcvHwInterface only)
    _select_wizard_variant_and_accept(qtbot, project, "/MICROSAR/CanTrcv_GenericCan/CanTrcv", "replace")
    assert project.module_entries["CanTrcv"].pre_unlocked == [
        "P:/CanTrcv/CanTrcvGeneral.CanTrcvHwInterface"
    ]

    # Controller switch back GenericCan -> Tle9255 calls apply_chip_selectors and refreshes dep graph
    chip_calls = []
    dep_refreshed = []
    monkeypatch.setattr(project, "apply_chip_selectors", lambda modules=None: chip_calls.append(modules))

    fake_win = SimpleNamespace(
        current_project=project,
        config_manager=project.module_managers["CanTrcv"],
        module_def=project.module_managers["CanTrcv"].module_def,
        undo_stack=SimpleNamespace(clear=lambda: None),
        tree_view=SimpleNamespace(set_project=lambda _p: None),
        config_panel=SimpleNamespace(clear=lambda: None),
        statusbar=SimpleNamespace(showMessage=lambda *_a, **_kw: None),
        dep_graph_controller=SimpleNamespace(
            _update_dependency_graph_if_open=lambda: dep_refreshed.append(True)
        ),
        _has_unsaved_changes=False,
        _update_mode_actions=lambda: None,
    )
    ctrl = ProjectController(fake_win)
    monkeypatch.setattr(QInputDialog, "getItem", lambda *_a, **_kw: (_a[3][0], True))
    monkeypatch.setattr(QMessageBox, "information", lambda *_a, **_kw: QMessageBox.Ok)

    assert ctrl.switch_module_variant("CanTrcv", confirm=lambda *_: True) is True
    assert chip_calls == [["CanTrcv"]]
    assert dep_refreshed == [True]


def test_cross_variant_merge_via_confirm_merge_preview_delegates_to_variant_switch(qtbot, monkeypatch, tmp_path):
    """P0 regression: cross-variant merge via ProjectController._confirm_merge_preview must
    delegate VariantSwitchPlan to _confirm_variant_switch instead of crashing in MergePreviewDialog;
    MergePreviewDialog itself must also tolerate VariantSwitchPlan and None."""
    from types import SimpleNamespace
    from autosar_configurator.core.packages.library import find_package, scan_library
    from autosar_configurator.ui.controllers.project_controller import ProjectController
    from autosar_configurator.ui.dialogs.merge_preview_dialog import MergePreviewDialog

    proj_dir = tmp_path / "p0_proj"
    _make_pre_and_plain_cantrcv_lib(proj_dir / "modules")
    wm = WorkspaceManager()
    project = wm.create_project("P0Var", proj_dir / "P0Var.dpa", format_version=8)
    lib_ref = LibraryRef(path="modules", kind="package")
    project.module_libraries.append(lib_ref)
    pkgs = scan_library(lib_ref, proj_dir)
    _, tle_pkg = find_package([(0, pkgs)], "/MICROSAR/CanTrcv_Tle9255/CanTrcv")
    project.add_module_from_package(tle_pkg, lib_index=0, persist=True, confirm=lambda *_: True)
    wm.save_project()

    fake_win = SimpleNamespace(current_project=project)
    ctrl = ProjectController(fake_win)
    captured_plans = []

    def _fake_confirm_variant_switch(preview_md, plan):
        captured_plans.append(plan)
        # Also verify MergePreviewDialog itself tolerates VariantSwitchPlan and None
        dlg_plan = MergePreviewDialog(None, plan.module_name, preview_md, plan)
        qtbot.addWidget(dlg_plan)
        dlg_none = MergePreviewDialog(None, plan.module_name, preview_md, None)
        qtbot.addWidget(dlg_none)
        return True

    monkeypatch.setattr(ctrl, "_confirm_variant_switch", _fake_confirm_variant_switch)

    wizard = IntegrationWizard(project, confirm_merge=ctrl._confirm_merge_preview)
    qtbot.addWidget(wizard)
    mod_page = wizard.page(wizard.pageIds()[1])
    mod_page.initializePage()

    target_found = False
    for i in range(mod_page.tree.topLevelItemCount()):
        cat = mod_page.tree.topLevelItem(i)
        for j in range(cat.childCount()):
            item = cat.child(j)
            cand = item.data(0, Qt.UserRole)
            if cand and cand.package.manifest.definition == "/MICROSAR/CanTrcv_GenericCan/CanTrcv":
                item.setCheckState(0, Qt.Checked)
                target_found = True
    assert target_found

    conf_page = wizard.page(wizard.pageIds()[2])
    conf_page.initializePage()
    conf_page.merge_strategy_merge.setChecked(True)
    wizard.accept()

    assert len(captured_plans) == 1
    assert captured_plans[0].target_definition == "/MICROSAR/CanTrcv_GenericCan/CanTrcv"
    assert wizard._result["added"] == ["CanTrcv"]
    assert project.module_entries["CanTrcv"].definition == "/MICROSAR/CanTrcv_GenericCan/CanTrcv"


def test_library_dedup_in_use_removal_block_index_remap_and_rollback(qtbot, monkeypatch, tmp_path):
    """LibrarySelectionPage deduplicates libraries, blocks removing in-use libraries,
    remaps entry.library on unused library removal, and rolls back on empty/failed integration."""
    from PySide6.QtWidgets import QFileDialog, QInputDialog, QMessageBox
    from autosar_configurator.core.packages.library import scan_library

    proj_dir = tmp_path / "lib_proj"
    unused_lib_dir = _make_package_lib(proj_dir / "unused_lib", "ModUnused", "Fast")
    active_lib_dir = _make_package_lib(proj_dir / "active_lib", "ModA", "Fast")
    _make_package_lib(active_lib_dir, "ModB", "Eco")

    wm = WorkspaceManager()
    project = wm.create_project("LibProj", proj_dir / "LibProj.dpa", format_version=8)
    project.module_libraries = [
        LibraryRef(path="unused_lib", kind="package"),
        LibraryRef(path="active_lib", kind="package"),
    ]
    pkgs = scan_library(project.module_libraries[1], proj_dir)
    pkg_a = next(p for p in pkgs if p.manifest.module == "ModA")
    project.add_module_from_package(pkg_a, lib_index=1, persist=True, confirm=lambda *_: True)
    assert project.module_entries["ModA"].library == 1

    infos = []
    warnings = []
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **kw: (infos.append(a[2]), QMessageBox.Ok)[1])
    monkeypatch.setattr(QMessageBox, "warning", lambda *a, **kw: (warnings.append(a[2]), QMessageBox.Ok)[1])

    wizard = IntegrationWizard(project)
    qtbot.addWidget(wizard)
    lib_page = wizard.page(wizard.pageIds()[0])

    # 1. Duplicate add is ignored with info message
    monkeypatch.setattr(QFileDialog, "getExistingDirectory", lambda *a, **kw: str(active_lib_dir))
    monkeypatch.setattr(QInputDialog, "getItem", lambda *a, **kw: ("package", True))
    lib_page._add_library()
    assert len(lib_page._libraries) == 2
    assert len(infos) == 1

    # 2. Removing in-use library (row 1) is blocked with warning
    lib_page.lib_table.selectRow(1)
    lib_page._remove_library()
    assert len(lib_page._libraries) == 2
    assert any("ModA" in w for w in warnings)

    # 3. Removing unused earlier library (row 0) succeeds; if nothing is integrated, project rolls back
    lib_page.lib_table.selectRow(0)
    lib_page._remove_library()
    assert len(lib_page._libraries) == 1
    wizard.accept()
    assert wizard._result["added"] == []
    assert len(project.module_libraries) == 2
    assert project.module_entries["ModA"].library == 1

    # 4. Removing unused earlier library (row 0) AND integrating ModB remaps ModA.library from 1 -> 0
    wizard2 = IntegrationWizard(project)
    qtbot.addWidget(wizard2)
    lib_page2 = wizard2.page(wizard2.pageIds()[0])
    lib_page2.lib_table.selectRow(0)
    lib_page2._remove_library()
    mod_page2 = wizard2.page(wizard2.pageIds()[1])
    mod_page2.initializePage()
    for i in range(mod_page2.tree.topLevelItemCount()):
        cat = mod_page2.tree.topLevelItem(i)
        for j in range(cat.childCount()):
            item = cat.child(j)
            cand = item.data(0, Qt.UserRole)
            if cand and cand.package.manifest.module == "ModB":
                item.setCheckState(0, Qt.Checked)
    wizard2.accept()
    assert wizard2._result["added"] == ["ModB"]
    assert len(project.module_libraries) == 1
    assert project.module_entries["ModA"].library == 0
    assert project.module_entries["ModB"].library == 0


def test_same_variant_merge_rejection_rolls_back_state_and_is_modified(qtbot, tmp_path):
    """Rejecting a same-variant baseline merge must roll back module_entries/packages/module_def
    and must not mark the project as modified."""
    proj_dir = tmp_path / "rej_proj"
    lib_dir = _make_package_lib(proj_dir / "lib", "ModA", "Fast")

    wm = WorkspaceManager()
    project = wm.create_project("RejProj", proj_dir / "RejProj.dpa", format_version=8)
    project.module_libraries = [LibraryRef(path="lib", kind="package")]

    # Initial install via wizard
    w1 = IntegrationWizard(project, confirm_merge=lambda *_: True)
    qtbot.addWidget(w1)
    mp1 = w1.page(w1.pageIds()[1])
    mp1.initializePage()
    mp1._select_all()
    w1.accept()
    wm.save_project()
    project.is_modified = False

    orig_pkg_record = dict(project.module_entries["ModA"].package_record)
    orig_mode = (
        project.module_managers["ModA"]
        .configuration.containers[0]
        .parameter_values["Mode"]
        .value
    )
    assert orig_mode == "Fast"

    # Update package Rec on disk so reconcile_baseline prompts user
    _make_package_lib(lib_dir, "ModA", "Ultra")

    w2 = IntegrationWizard(project, confirm_merge=lambda *_: False)
    qtbot.addWidget(w2)
    mp2 = w2.page(w2.pageIds()[1])
    mp2.initializePage()
    for i in range(mp2.tree.topLevelItemCount()):
        cat = mp2.tree.topLevelItem(i)
        for j in range(cat.childCount()):
            item = cat.child(j)
            cand = item.data(0, Qt.UserRole)
            if cand and cand.package.manifest.module == "ModA":
                item.setCheckState(0, Qt.Checked)
    cp2 = w2.page(w2.pageIds()[2])
    cp2.initializePage()
    cp2.merge_strategy_merge.setChecked(True)
    w2.accept()

    assert w2._result["merge_rejected"] == ["ModA"]
    assert w2._result["added"] == []
    assert project.is_modified is False
    assert project.module_entries["ModA"].package_record == orig_pkg_record
    assert (
        project.module_managers["ModA"]
        .configuration.containers[0]
        .parameter_values["Mode"]
        .value
        == "Fast"
    )


def test_replace_strategy_defers_baseline_disk_write_until_save_project(qtbot, tmp_path):
    """Replace strategy must mark baseline dirty in memory instead of writing .baseline/ immediately."""
    from autosar_configurator.core.baseline import session as baseline_session

    proj_dir = tmp_path / "defer_proj"
    lib_dir = _make_package_lib(proj_dir / "lib", "ModA", "Fast")

    wm = WorkspaceManager()
    project = wm.create_project("DeferProj", proj_dir / "DeferProj.dpa", format_version=8)
    project.module_libraries = [LibraryRef(path="lib", kind="package")]
    wm.save_project()

    snap_path = baseline_session.base_snapshot_path(project, "ModA")
    assert not snap_path.exists()

    # 1. New module with replace strategy: no disk write before save_project()
    w1 = IntegrationWizard(project)
    qtbot.addWidget(w1)
    mp1 = w1.page(w1.pageIds()[1])
    mp1.initializePage()
    mp1._select_all()
    cp1 = w1.page(w1.pageIds()[2])
    cp1.initializePage()
    cp1.merge_strategy_replace.setChecked(True)
    w1.accept()

    assert project.baselines["ModA"].dirty is True
    assert not snap_path.exists()

    wm.save_project()
    assert snap_path.exists()
    old_bytes = snap_path.read_bytes()

    # 2. Existing module with replace strategy after package update: still deferred until save_project()
    _make_package_lib(lib_dir, "ModA", "Turbo")
    w2 = IntegrationWizard(project)
    qtbot.addWidget(w2)
    mp2 = w2.page(w2.pageIds()[1])
    mp2.initializePage()
    for i in range(mp2.tree.topLevelItemCount()):
        cat = mp2.tree.topLevelItem(i)
        for j in range(cat.childCount()):
            item = cat.child(j)
            cand = item.data(0, Qt.UserRole)
            if cand and cand.package.manifest.module == "ModA":
                item.setCheckState(0, Qt.Checked)
    cp2 = w2.page(w2.pageIds()[2])
    cp2.initializePage()
    cp2.merge_strategy_replace.setChecked(True)
    w2.accept()

    assert project.baselines["ModA"].dirty is True
    assert snap_path.read_bytes() == old_bytes

    wm.save_project()
    assert snap_path.read_bytes() != old_bytes


def test_filtered_select_all_and_cross_library_duplicate_dedup(qtbot, tmp_path):
    """ModuleSelectionPage deduplicates identical (module, definition) across libraries,
    and _select_all only selects visible matching items when a filter is active."""
    proj_dir = tmp_path / "filter_proj"
    lib1 = _make_package_lib(proj_dir / "lib1", "ModAlpha", "Fast")
    _make_package_lib(lib1, "ModBeta", "Eco")
    # Same (ModAlpha, /Vendor/ModAlpha) duplicated in second library
    _make_package_lib(proj_dir / "lib2", "ModAlpha", "Fast")

    wm = WorkspaceManager()
    project = wm.create_project("FilterProj", proj_dir / "FilterProj.dpa", format_version=8)
    project.module_libraries = [
        LibraryRef(path="lib1", kind="package"),
        LibraryRef(path="lib2", kind="package"),
    ]

    wizard = IntegrationWizard(project)
    qtbot.addWidget(wizard)
    mod_page = wizard.page(wizard.pageIds()[1])
    mod_page.initializePage()

    # Cross-library duplicate of ModAlpha should be deduplicated into 1 candidate
    alpha_cands = [c for c in mod_page.candidates if c.package.manifest.module == "ModAlpha"]
    assert len(alpha_cands) == 1

    # Filter to only ModAlpha and click Select All -> only ModAlpha should be selected
    mod_page.filter_edit.setText("ModAlpha")
    mod_page._select_all()
    selected = [c.package.manifest.module for c in mod_page._get_selected_candidates()]
    assert selected == ["ModAlpha"]
    assert mod_page.last_skipped_ambiguous == []


def test_on_integration_complete_updates_title_dep_graph_and_resolves_references(monkeypatch):
    """ProjectController._on_integration_complete re-resolves references after chip selectors
    and refreshes window title and dependency graph."""
    from types import SimpleNamespace
    from PySide6.QtWidgets import QMessageBox
    from autosar_configurator.ui.controllers.project_controller import ProjectController

    events = []
    fake_proj = SimpleNamespace(
        module_managers={},
        load_ecu_resources=lambda: events.append("load_ecu"),
        apply_chip_selectors=lambda modules=None: events.append(("apply_chip", modules)),
        resolve_all_references=lambda force=False: events.append(("resolve_refs", force)),
        build_reverse_reference_index=lambda: events.append("reverse_index"),
    )
    fake_win = SimpleNamespace(
        current_project=fake_proj,
        module_def=None,
        config_manager=None,
        undo_stack=SimpleNamespace(clear=lambda: events.append("clear_undo")),
        tree_view=SimpleNamespace(set_project=lambda _p: events.append("set_project")),
        statusbar=SimpleNamespace(showMessage=lambda msg: events.append(("status", msg))),
        _update_window_title=lambda: events.append("update_title"),
        dep_graph_controller=SimpleNamespace(
            _update_dependency_graph_if_open=lambda: events.append("update_dep_graph")
        ),
        _has_unsaved_changes=False,
    )
    monkeypatch.setattr(QMessageBox, "information", lambda *a, **kw: QMessageBox.Ok)

    ctrl = ProjectController(fake_win)
    ctrl._on_integration_complete({"added": ["Can"], "failed": [], "merge_conflicts": [], "merge_rejected": []})

    assert ("apply_chip", ["Can"]) in events
    assert ("resolve_refs", True) in events
    assert "reverse_index" in events
    assert events.index(("apply_chip", ["Can"])) < events.index(("resolve_refs", True))
    assert "update_title" in events
    assert "update_dep_graph" in events




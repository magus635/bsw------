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

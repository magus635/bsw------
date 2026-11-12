"""EB project import produces a format 8 project (design §6.10, task 13 / W9).

The import registers the EB plugins directory as an ``eb-plugins`` module library (link)
or copies the plugins into ``modules/`` (copy), writes the EPC values to
``config/<M>.arxml``, copies no template and creates no symlink. A plugin's
``PreConfiguration`` is a Pre layer of the module's baseline: a module with EPC values is
a migrated module (no Base, every value USER) whose Pre values change only behind
``confirm``.
"""
import json
import os
import shutil
from pathlib import Path

import pytest

from autosar_configurator.core.baseline.merge import MergeKind
from autosar_configurator.core.baseline.origin import Origin
from autosar_configurator.core.workspace_manager import WorkspaceManager
from tests.core.test_eb_import_modes import (
    DIO_DEF_SAMPLE, DIO_EPC, write_dio_plugin, write_v7_imported_project)

REPO_ROOT = Path(__file__).resolve().parents[2]
IMPORT_PROJECT = REPO_ROOT / "test_import_project"
MCU_PLUGIN = IMPORT_PROJECT / "Def" / "plugins" / "Mcu_THA6_AS440"
CHIP = "THA6206_LFBGA292"

requires_eb_fixture = pytest.mark.skipif(not MCU_PLUGIN.is_dir(), reason="EB plugin fixture missing")

_MCU_PRE_ESR0 = "P:/Mcu/McuPublishedInformation/MCU_RSTREASON_ESR0.McuResetReason"

# Mcu values as EB tresos exports them: one reset reason only, with a value that differs
# from the plugin's McuPreConfiguration (0), and a general parameter Pre does not own.
MCU_EPC = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Mcu</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>Mcu</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/THA6_AS440_FuSa/Mcu</DEFINITION-REF>
          <IMPLEMENTATION-CONFIG-VARIANT>VARIANT-PRE-COMPILE</IMPLEMENTATION-CONFIG-VARIANT>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>McuGeneralConfiguration</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_AS440_FuSa/Mcu/McuGeneralConfiguration</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-BOOLEAN-PARAM-DEF">/THA6_AS440_FuSa/Mcu/McuGeneralConfiguration/McuDevErrorDetect</DEFINITION-REF>
                  <VALUE>true</VALUE>
                </ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>McuPublishedInformation</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_AS440_FuSa/Mcu/McuPublishedInformation</DEFINITION-REF>
              <SUB-CONTAINERS>
                <ECUC-CONTAINER-VALUE>
                  <SHORT-NAME>MCU_RSTREASON_ESR0</SHORT-NAME>
                  <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/THA6_AS440_FuSa/Mcu/McuPublishedInformation/McuResetReasonConf</DEFINITION-REF>
                  <PARAMETER-VALUES>
                    <ECUC-NUMERICAL-PARAM-VALUE>
                      <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/THA6_AS440_FuSa/Mcu/McuPublishedInformation/McuResetReasonConf/McuResetReason</DEFINITION-REF>
                      <VALUE>5</VALUE>
                    </ECUC-NUMERICAL-PARAM-VALUE>
                  </PARAMETER-VALUES>
                </ECUC-CONTAINER-VALUE>
              </SUB-CONTAINERS>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


# --- fixtures -------------------------------------------------------------------------

@pytest.fixture
def dio_tree(tmp_path):
    """A small EB tree: one Dio plugin (with plugin.xml) and its EPC."""
    src = tmp_path / "EbDio"
    write_dio_plugin(src / "Define" / "EbPlugins" / "eclipse" / "Dio_TS_T40D11M7I0R0")
    output = src / "Config" / "THA6206" / "output"
    output.mkdir(parents=True)
    (output / "Dio.epc").write_text(DIO_EPC, encoding="utf-8")
    return src


@pytest.fixture
def mcu_tree(tmp_path):
    """An EB tree with the real Mcu plugin (its McuPreConfiguration) and an Mcu EPC."""
    src = tmp_path / "EbMcu"
    plugin = src / "Define" / "EbPlugins" / "eclipse" / MCU_PLUGIN.name
    plugin.mkdir(parents=True)
    shutil.copy(MCU_PLUGIN / "plugin.xml", plugin / "plugin.xml")
    for sub in ("config", "autosar"):
        shutil.copytree(MCU_PLUGIN / sub, plugin / sub)
    output = src / "Config" / CHIP / "output"
    output.mkdir(parents=True)
    (output / "Mcu.epc").write_text(MCU_EPC, encoding="utf-8")
    return src


def _import(source, tmp_path, mode, confirm=None, name="Imported", progress=None):
    manager = WorkspaceManager()
    target = tmp_path / name
    target.mkdir()
    project, loaded, failed = manager.import_eb_project(
        source, target_dir=target, mode=mode, confirm=confirm, progress_callback=progress)
    return manager, project, loaded, failed, target


def _symlinks(root: Path):
    found = []
    for dirpath, dirnames, filenames in os.walk(root):
        for name in dirnames + filenames:
            if (Path(dirpath) / name).is_symlink():
                found.append(Path(dirpath) / name)
    return found


def _container(config, *names):
    containers = config.containers
    found = None
    for name in names:
        (found,) = [c for c in containers if c.short_name == name]
        containers = found.sub_containers
    return found


class _Recorder:
    def __init__(self, answer):
        self.answer = answer
        self.calls = []

    def __call__(self, preview, result):
        self.calls.append((preview, result))
        return self.answer


# --- link / copy ------------------------------------------------------------------------

def test_import_link_no_symlink(dio_tree, tmp_path):
    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "link")
    assert "Dio" in loaded, failed

    plugins = dio_tree / "Define" / "EbPlugins" / "eclipse"
    assert project.format_version == 8
    assert len(project.module_libraries) == 1
    assert project.module_libraries[0].kind == "eb-plugins"
    # outside the project: absolute, POSIX
    assert project.module_libraries[0].path == plugins.resolve().as_posix()
    assert project.module_libraries[0].exclude == []
    # definitions come straight from the EB tree
    assert plugins.resolve() in project.module_defs["Dio"].resolve().parents

    manager.save_project()
    assert _symlinks(target) == []
    assert not (target / "Def").exists()
    assert not (target / "templates").exists()
    data = json.loads(project.path.read_text(encoding="utf-8"))
    assert data["format_version"] == 8
    assert data["module_libraries"] == [
        {"path": plugins.resolve().as_posix(), "kind": "eb-plugins", "exclude": []}]
    assert "\\" not in json.dumps(data["module_libraries"])


@requires_eb_fixture
def test_import_copy_into_modules(mcu_tree, tmp_path):
    manager, project, loaded, failed, target = _import(
        mcu_tree, tmp_path, "copy", confirm=lambda preview, result: True)
    assert loaded == ["Mcu"], failed

    assert (target / "modules" / "Mcu_THA6_AS440" / "plugin.xml").is_file()
    assert project.module_defs["Mcu"] == target / "modules" / "Mcu_THA6_AS440" / "config" / "Mcu.xdm"

    manager.save_project()
    data = json.loads(project.path.read_text(encoding="utf-8"))
    assert data["format_version"] == 8
    assert data["module_libraries"] == [{"path": "modules", "kind": "eb-plugins", "exclude": []}]
    (mcu,) = data["modules"]
    assert mcu["name"] == "Mcu"
    assert mcu["definition"] == "/THA6_AS440_FuSa/Mcu"
    assert mcu["library"] == 0
    assert mcu["config_path"] == "config/Mcu.arxml"
    assert mcu["base_hash"].startswith("sha256:")      # the accepted Base' was written
    files = mcu["package_record"]["files"]
    assert sorted(files) == ["config/Mcu.xdm", "config/McuPreConfiguration.xdm"]
    assert all(v.startswith("sha256:") for v in files.values())
    assert mcu["package_record"]["sw_version"] == "1.2.0"

    # EPC values in the format 8 config directory; no template copy, no legacy dirs
    assert (target / "config" / "Mcu.arxml").is_file()
    for legacy in ("ConfigValue", "templates", "Def"):
        assert not (target / legacy).exists(), legacy
    assert _symlinks(target) == []

    # The copied project opens on its own; the accepted baseline needs no new confirm
    reopen = _Recorder(True)
    loaded_project, failed = WorkspaceManager().load_project(project.path, confirm=reopen)
    assert failed == []
    assert reopen.calls == []
    assert "Mcu" in loaded_project.module_managers


# --- Pre ------------------------------------------------------------------------------

@requires_eb_fixture
def test_import_mcu_preconfiguration_applied(tmp_path):
    """Acceptance 1: McuPreConfiguration reaches the configuration as PRE; autosar/ is not loaded."""
    manager, project, loaded, failed, target = _import(
        IMPORT_PROJECT, tmp_path, "link", confirm=lambda preview, result: True)
    assert "Mcu" in loaded, failed
    mcu = project.module_managers["Mcu"]

    published = _container(mcu.configuration, "McuPublishedInformation")
    reasons = [c for c in published.sub_containers
               if c.definition_ref.endswith("/McuResetReasonConf")]
    assert len(reasons) == 14
    esr0 = _container(mcu.configuration, "McuPublishedInformation", "MCU_RSTREASON_ESR0")
    assert esr0.parameter_values["McuResetReason"].value == 0
    assert mcu.value_origin(esr0, "McuResetReason") is Origin.PRE
    assert mcu.value_origin(esr0) is Origin.PRE

    # Definitions come from config/*.xdm; the autosar/ exchange copies are not loaded
    plugins = IMPORT_PROJECT / "Def" / "plugins"
    assert project.module_defs["Mcu"] == plugins / "Mcu_THA6_AS440" / "config" / "Mcu.xdm"
    assert all("autosar" not in p.parts for p in project.module_defs.values())
    assert project.packages["Mcu"].manifest.exchange_copies == [
        "autosar/Mcu_THA610X_LFBGA180.arxml",
        "autosar/Mcu_THA6206_LFBGA292.arxml",
        "autosar/Mcu_THA6412_BGA516.arxml",
    ]
    assert not any("autosar" in f for f in project.module_entries["Mcu"].package_record["files"])
    # McuPreConfiguration is not a module of its own
    assert "McuPreConfiguration" not in project.module_managers
    # link mode wrote nothing into the source tree
    for written in ("config", "modules", ".history"):
        assert not (IMPORT_PROJECT / written).exists(), written


@requires_eb_fixture
def test_import_epc_pre_changes_only_behind_confirm(mcu_tree, tmp_path):
    confirm = _Recorder(True)
    manager, project, loaded, failed, target = _import(mcu_tree, tmp_path, "link", confirm=confirm)
    assert loaded == ["Mcu"], failed

    # One preview, for Mcu: the EPC value Pre owns is forced, the missing Pre containers created
    (preview, result), = confirm.calls
    assert [i.key for i in result.of_kind(MergeKind.PRE_FORCED)] == [_MCU_PRE_ESR0]
    assert len([i for i in result.of_kind(MergeKind.CREATE) if i.key.startswith("C:")]) == 13
    assert "预设强制" in preview

    mcu = project.module_managers["Mcu"]
    esr0 = _container(mcu.configuration, "McuPublishedInformation", "MCU_RSTREASON_ESR0")
    assert esr0.parameter_values["McuResetReason"].value == 0
    assert len(_container(mcu.configuration, "McuPublishedInformation").sub_containers) == 14
    # A value Pre does not own keeps the EPC value: it is the user's
    general = _container(mcu.configuration, "McuGeneralConfiguration")
    assert str(general.parameter_values["McuDevErrorDetect"].value).lower() == "true"
    assert mcu.value_origin(general, "McuDevErrorDetect") is Origin.USER
    assert mcu.value_origin(esr0, "McuResetReason") is Origin.PRE


@requires_eb_fixture
def test_import_epc_values_kept_without_confirm(mcu_tree, tmp_path):
    manager, project, loaded, failed, target = _import(mcu_tree, tmp_path, "link")
    assert loaded == ["Mcu"], failed

    mcu = project.module_managers["Mcu"]
    esr0 = _container(mcu.configuration, "McuPublishedInformation", "MCU_RSTREASON_ESR0")
    assert esr0.parameter_values["McuResetReason"].value == 5           # never silently rewritten
    assert len(_container(mcu.configuration, "McuPublishedInformation").sub_containers) == 1

    (report,) = sorted((target / ".history" / "reports").glob("*_import.md"))
    text = report.read_text(encoding="utf-8")
    assert _MCU_PRE_ESR0 in text                                         # the conflict is reported
    assert "未应用" in text

    # Saved without a Base: the next open asks again
    manager.save_project()
    data = json.loads(project.path.read_text(encoding="utf-8"))
    assert data["modules"][0]["base_hash"] is None
    again = _Recorder(False)
    WorkspaceManager().load_project(project.path, confirm=again)
    assert len(again.calls) == 1


# --- report and excluded MCAL ---------------------------------------------------------------

def test_import_report_lists_skipped_mcal(dio_tree, tmp_path):
    plugins = dio_tree / "Define" / "EbPlugins" / "eclipse"
    bswmd = plugins / "Mcal_Tha62x" / "BSWMD"          # Vector-wrapped MCAL: same definition as the EB plugin
    bswmd.mkdir(parents=True)
    shutil.copy(DIO_DEF_SAMPLE, bswmd / "Copy_Dio_THA6206_LFBGA292.arxml")
    (dio_tree / "Config" / "THA6206" / "output" / "Foo.epc").write_text(
        DIO_EPC.replace("<SHORT-NAME>Dio</SHORT-NAME>", "<SHORT-NAME>Foo</SHORT-NAME>")
               .replace("/THA6_AS440_FuSa/Dio", "/Vendor/Foo"), encoding="utf-8")

    lines = []
    manager, project, loaded, failed, target = _import(
        dio_tree, tmp_path, "link", progress=lines.append)
    assert loaded == ["Dio"]
    assert [name for name, _ in failed] == ["Foo"]
    assert project.module_libraries[0].exclude == ["Mcal_Tha62x"]
    assert "Mcal_Tha62x" not in project.module_defs["Dio"].parts

    (report,) = sorted((target / ".history" / "reports").glob("*_import.md"))
    text = report.read_text(encoding="utf-8")
    assert text.strip()
    skipped = text.split("## 跳过的 MCAL 模块", 1)[1].split("\n## ", 1)[0]
    assert "Mcal_Tha62x" in skipped and "/THA6_AS440_FuSa/Dio" in skipped
    assert "Foo" in text                                  # EPC values with no plugin are reported
    assert "### Dio" in text and "容器 1" in text
    # The same summary goes through the progress callback
    assert any("Mcal_Tha62x" in line for line in lines)
    assert any(str(report.name) in line for line in lines)


def test_copy_mode_leaves_wrapped_mcal_out(dio_tree, tmp_path):
    bswmd = dio_tree / "Define" / "EbPlugins" / "eclipse" / "Mcal_Tha62x" / "BSWMD"
    bswmd.mkdir(parents=True)
    shutil.copy(DIO_DEF_SAMPLE, bswmd / "Copy_Dio_THA6206_LFBGA292.arxml")

    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "copy")
    assert loaded == ["Dio"], failed
    assert sorted(p.name for p in (target / "modules").iterdir()) == ["Dio_TS_T40D11M7I0R0"]
    assert [lib.to_dict() for lib in project.module_libraries] == [
        {"path": "modules", "kind": "eb-plugins", "exclude": []}]
    (report,) = sorted((target / ".history" / "reports").glob("*_import.md"))
    assert "Mcal_Tha62x" in report.read_text(encoding="utf-8")


def test_two_eb_plugins_for_one_definition_fail_but_keep_the_values(dio_tree, tmp_path):
    """The import cannot choose between two EB plugins: the module fails, nothing is lost."""
    write_dio_plugin(dio_tree / "Define" / "EbPlugins" / "eclipse" / "Dio_TS_T40D11M8I0R0")

    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "link")
    assert loaded == []
    ((name, reason),) = failed
    assert name == "Dio" and "multiple packages" in reason
    assert project.module_libraries[0].exclude == []        # never chosen silently
    # The EPC values stay in the project, under an entry the next open retries
    assert project.module_entries["Dio"].config_path == "config/Dio.arxml"
    assert "DioConfig" in (target / "config" / "Dio.arxml").read_text(encoding="utf-8")
    (report,) = sorted((target / ".history" / "reports").glob("*_import.md"))
    text = report.read_text(encoding="utf-8")
    assert "Dio_TS_T40D11M7I0R0" in text and "Dio_TS_T40D11M8I0R0" in text


def test_import_refuses_to_overwrite_a_project(dio_tree, tmp_path):
    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "copy")
    config = target / "config" / "Dio.arxml"
    before = config.read_bytes()

    with pytest.raises(ValueError, match="导入不会覆盖"):
        WorkspaceManager().import_eb_project(dio_tree, target_dir=target, mode="copy")
    assert config.read_bytes() == before
    assert len(list((target / ".history" / "reports").glob("*_import.md"))) == 1


# --- where the project goes (never into the EB tree) -----------------------------------------

def _tree(root: Path):
    return sorted(p.relative_to(root).as_posix() for p in root.rglob("*"))


@pytest.mark.parametrize("target", ["none", "eb_root"])
def test_import_into_the_eb_tree_goes_to_a_sibling(dio_tree, target):
    before = _tree(dio_tree)

    project, loaded, failed = WorkspaceManager().import_eb_project(
        dio_tree, target_dir=None if target == "none" else dio_tree, mode="copy")

    sibling = dio_tree.parent / "EbDio_imported"
    assert loaded == ["Dio"], failed
    assert project.path == sibling / "EbDio_imported.dpa"
    assert project.path.is_file()
    assert (sibling / "modules" / "Dio_TS_T40D11M7I0R0" / "plugin.xml").is_file()
    assert list((sibling / ".history" / "reports").glob("*_import.md"))
    # The EB tree is only read (its own Config/ is the only config-like entry in it)
    assert _tree(dio_tree) == before
    for written in ("modules", ".history", "EbDio.dpa", "EbDio_imported.dpa"):
        assert not (dio_tree / written).exists(), written


def test_import_target_inside_the_eb_tree_is_refused(dio_tree):
    before = _tree(dio_tree)
    with pytest.raises(ValueError, match="EB"):
        WorkspaceManager().import_eb_project(dio_tree, target_dir=dio_tree / "Imported")
    assert _tree(dio_tree) == before


def test_import_target_for_a_chosen_folder(tmp_path):
    from autosar_configurator.core.eb_import import import_target

    root = tmp_path / "Eb"
    root.mkdir()
    assert import_target(root, tmp_path / "out") == tmp_path / "out" / "Eb"
    assert import_target(root, None) == tmp_path / "Eb_imported"
    # Choosing the folder that holds the EB tree would name the tree itself
    assert import_target(root, tmp_path) == tmp_path / "Eb_imported"
    for inside in (root, root / "sub"):
        with pytest.raises(ValueError, match="EB"):
            import_target(root, inside)


# --- an EPC binds only to the plugin of its definition -------------------------------------

def test_epc_for_another_definition_is_not_bound(dio_tree, tmp_path):
    epc = dio_tree / "Config" / "THA6206" / "output" / "Dio.epc"
    epc.write_text(DIO_EPC.replace("/THA6_AS440_FuSa/Dio", "/Vendor/Dio"), encoding="utf-8")

    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "link")

    assert loaded == []
    ((name, reason),) = failed
    assert name == "Dio" and "/Vendor/Dio" in reason and "/THA6_AS440_FuSa/Dio" in reason
    assert "Dio" not in project.module_managers        # not filled with another module's values
    # The values are kept, under the definition the EPC names
    assert project.module_entries["Dio"].definition == "/Vendor/Dio"
    assert "/Vendor/Dio" in (target / "config" / "Dio.arxml").read_text(encoding="utf-8")
    (report,) = sorted((target / ".history" / "reports").glob("*_import.md"))
    text = report.read_text(encoding="utf-8")
    assert "/Vendor/Dio" in text and "/THA6_AS440_FuSa/Dio" in text


def test_epc_binds_to_the_plugin_of_its_definition(dio_tree, tmp_path):
    plugins = dio_tree / "Define" / "EbPlugins" / "eclipse"
    write_dio_plugin(plugins / "Dio_Vendor", package="Vendor")       # same module name, other path
    epc = dio_tree / "Config" / "THA6206" / "output" / "Dio.epc"
    epc.write_text(DIO_EPC.replace("/THA6_AS440_FuSa/Dio", "/Vendor/Dio"), encoding="utf-8")

    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "link")

    assert loaded == ["Dio"]
    assert project.module_entries["Dio"].definition == "/Vendor/Dio"
    assert "Dio_Vendor" in project.module_defs["Dio"].parts
    assert [c.short_name for c in project.module_managers["Dio"].configuration.containers] == ["DioConfig"]
    ((name, reason),) = failed                                    # the other Dio plugin is reported
    assert name == "Dio" and "/THA6_AS440_FuSa/Dio" in reason


def test_epc_naming_the_standard_definition_still_binds(dio_tree, tmp_path):
    epc = dio_tree / "Config" / "THA6206" / "output" / "Dio.epc"
    epc.write_text(DIO_EPC.replace(">/THA6_AS440_FuSa/Dio<", ">/AUTOSAR/EcucDefs/Dio<"),
                   encoding="utf-8")

    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "link")
    assert loaded == ["Dio"], failed


# --- plugin layouts ---------------------------------------------------------------------

def test_nested_eclipse_plugins_layout(tmp_path):
    src = tmp_path / "EbNested"
    write_dio_plugin(src / "Define" / "EbPlugins" / "eclipse" / "plugins" / "Dio_TS")
    output = src / "Config" / "THA6206" / "output"
    output.mkdir(parents=True)
    (output / "Dio.epc").write_text(DIO_EPC, encoding="utf-8")

    manager, project, loaded, failed, target = _import(src, tmp_path, "link")
    assert loaded == ["Dio"], failed
    assert project.module_libraries[0].path.endswith("/eclipse/plugins")


def test_wrapper_named_after_its_module_does_not_hide_the_eb_plugin(dio_tree, tmp_path):
    bswmd = dio_tree / "Define" / "EbPlugins" / "eclipse" / "Dio" / "BSWMD"
    bswmd.mkdir(parents=True)
    shutil.copy(DIO_DEF_SAMPLE, bswmd / "Copy_Dio_THA6206_LFBGA292.arxml")

    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "link")
    assert project.module_libraries[0].exclude == ["Dio"]
    assert loaded == ["Dio"], failed
    assert "Dio_TS_T40D11M7I0R0" in project.module_defs["Dio"].parts


def test_copy_mode_keeps_symlinks_as_links(dio_tree, tmp_path):
    plugin = dio_tree / "Define" / "EbPlugins" / "eclipse" / "Dio_TS_T40D11M7I0R0"
    try:
        os.symlink(plugin / "generate_PB" / "Dio" / "Dio_Cfg.h.tpl", plugin / "linked.tpl")
    except (OSError, NotImplementedError):
        pytest.skip("symlinks cannot be created here")

    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "copy")
    assert loaded == ["Dio"], failed
    assert (target / "modules" / "Dio_TS_T40D11M7I0R0" / "linked.tpl").is_symlink()


# --- save-as keeps a format 8 project whole ------------------------------------------------

@requires_eb_fixture
def test_relocated_project_keeps_modules_baseline_and_values(mcu_tree, tmp_path):
    (mcu_tree / "Config" / CHIP / "output" / "Foo.epc").write_text(
        DIO_EPC.replace("<SHORT-NAME>Dio</SHORT-NAME>", "<SHORT-NAME>Foo</SHORT-NAME>")
               .replace("/THA6_AS440_FuSa/Dio", "/Vendor/Foo"), encoding="utf-8")
    manager, project, loaded, failed, target = _import(
        mcu_tree, tmp_path, "copy", confirm=lambda preview, result: True)
    assert loaded == ["Mcu"] and [n for n, _ in failed] == ["Foo"]

    new_dpa = tmp_path / "SavedAs" / "Imported.dpa"
    manager.relocate_project(new_dpa)
    manager.save_project()

    moved = new_dpa.parent
    assert (moved / "modules" / "Mcu_THA6_AS440" / "plugin.xml").is_file()
    assert (moved / "config" / "base" / "Mcu.arxml").is_file()        # the accepted Base
    assert (moved / "config" / "Foo.arxml").is_file()                 # values of a failed module
    assert list((moved / ".history" / "reports").glob("*_import.md"))  # the import report
    data = json.loads(new_dpa.read_text(encoding="utf-8"))
    assert data["module_libraries"] == [{"path": "modules", "kind": "eb-plugins", "exclude": []}]

    reopen = _Recorder(True)
    loaded_project, failed = WorkspaceManager().load_project(new_dpa, confirm=reopen)
    assert [n for n, _ in failed] == ["Foo"]
    assert reopen.calls == []                                         # Base came along
    assert moved in loaded_project.module_defs["Mcu"].parents


def test_relocated_project_makes_an_outside_library_absolute(dio_tree, tmp_path):
    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "link")
    plugins = dio_tree / "Define" / "EbPlugins" / "eclipse"
    project.module_libraries[0].path = Path(os.path.relpath(plugins, target)).as_posix()
    assert project.module_libraries[0].path.startswith("../")

    new_dpa = tmp_path / "Elsewhere" / "deep" / "Imported.dpa"
    manager.relocate_project(new_dpa)
    assert project.module_libraries[0].path == plugins.resolve().as_posix()
    manager.save_project()
    loaded_project, failed = WorkspaceManager().load_project(new_dpa)
    assert failed == [] and "Dio" in loaded_project.module_managers


# --- round 2: free sibling names, ambiguous bindings ----------------------------------------

def test_import_never_merges_into_an_existing_sibling(dio_tree):
    taken = dio_tree.parent / "EbDio_imported"
    (taken / "modules" / "Stale").mkdir(parents=True)
    (taken / "modules" / "Stale" / "plugin.xml").write_text("<plugin/>", encoding="utf-8")
    (taken / "other.dpa").write_text("{}", encoding="utf-8")
    before = _tree(taken)
    lines = []

    project, loaded, failed = WorkspaceManager().import_eb_project(
        dio_tree, target_dir=None, mode="copy", progress_callback=lines.append)

    second = dio_tree.parent / "EbDio_imported_2"
    assert loaded == ["Dio"], failed
    assert project.path == second / "EbDio_imported_2.dpa"
    assert _tree(taken) == before                              # the existing folder is untouched
    assert sorted(p.name for p in (second / "modules").iterdir()) == ["Dio_TS_T40D11M7I0R0"]
    assert list(second.glob("*.dpa")) == [project.path]
    # The chosen place is said, in the report and through the progress callback
    (report,) = sorted((second / ".history" / "reports").glob("*_import.md"))
    assert second.as_posix() in report.read_text(encoding="utf-8")
    assert any(second.as_posix() in line for line in lines)


def test_free_sibling_names_count_up(tmp_path):
    from autosar_configurator.core.eb_import import import_project_dir

    root = tmp_path / "Eb"
    root.mkdir()
    assert import_project_dir(root, None) == tmp_path / "Eb_imported"
    (tmp_path / "Eb_imported").mkdir()                         # empty: still free
    assert import_project_dir(root, None) == tmp_path / "Eb_imported"
    (tmp_path / "Eb_imported" / "x.txt").write_text("x", encoding="utf-8")
    (tmp_path / "Eb_imported_2").write_text("a file", encoding="utf-8")
    assert import_project_dir(root, None) == tmp_path / "Eb_imported_3"
    assert import_project_dir(root, root) == tmp_path / "Eb_imported_3"


def test_explicit_target_with_files_is_refused(dio_tree, tmp_path):
    target = tmp_path / "Chosen"
    (target / "notes").mkdir(parents=True)
    (target / "notes" / "readme.txt").write_text("mine", encoding="utf-8")
    before = _tree(target)

    with pytest.raises(ValueError, match="导入不会覆盖"):
        WorkspaceManager().import_eb_project(dio_tree, target_dir=target, mode="copy")
    assert _tree(target) == before


@pytest.mark.parametrize("epc_ref", ["none", "standard"])
def test_an_epc_two_plugins_could_take_is_not_bound(dio_tree, tmp_path, epc_ref):
    plugins = dio_tree / "Define" / "EbPlugins" / "eclipse"
    write_dio_plugin(plugins / "Dio_Vendor", package="Vendor")       # /Vendor/Dio and /THA6.../Dio
    epc = dio_tree / "Config" / "THA6206" / "output" / "Dio.epc"
    text = DIO_EPC.replace(">/THA6_AS440_FuSa/Dio<", ">/AUTOSAR/EcucDefs/Dio<")
    if epc_ref == "none":
        text = text.replace(
            '<DEFINITION-REF DEST="ECUC-MODULE-DEF">/AUTOSAR/EcucDefs/Dio</DEFINITION-REF>', "")
    epc.write_text(text, encoding="utf-8")

    manager, project, loaded, failed, target = _import(dio_tree, tmp_path, "link")

    assert loaded == []
    assert "Dio" not in project.module_managers
    reasons = [reason for name, reason in failed if name == "Dio"]
    assert len(reasons) == 1
    assert "/THA6_AS440_FuSa/Dio" in reasons[0] and "/Vendor/Dio" in reasons[0]
    # The values are kept for the user to resolve, not given to either plugin
    assert project.module_entries["Dio"].config_path == "config/Dio.arxml"
    assert "DioConfig" in (target / "config" / "Dio.arxml").read_text(encoding="utf-8")
    (report,) = sorted((target / ".history" / "reports").glob("*_import.md"))
    text = report.read_text(encoding="utf-8")
    assert "Dio_Vendor" in text and "Dio_TS_T40D11M7I0R0" in text


# --- old projects ---------------------------------------------------------------------

def test_old_v7_imported_project_still_opens(tmp_path):
    dpa = write_v7_imported_project(tmp_path / "OldImport")

    manager = WorkspaceManager()
    project, failed = manager.load_project(dpa)
    assert failed == []
    assert project.format_version == 7
    assert project.module_libraries == [] and project.module_entries == {}
    assert project.baselines == {}
    assert project.module_defs["Dio"] == (
        dpa.parent / "Def" / "plugins" / "Dio_TS_T40D11M7I0R0" / "autosar" / "Dio_THA6206_LFBGA292.arxml")
    assert project.module_provenance["Dio"]["origin"] == "eb-import"
    assert [c.short_name for c in project.module_managers["Dio"].configuration.containers] == ["DioConfig"]

    manager.save_project()
    data = json.loads(dpa.read_text(encoding="utf-8"))
    assert data["format_version"] == 7
    assert "module_libraries" not in data
    assert data["modules"][0]["def_path"].replace("\\", "/") == (
        "Def/plugins/Dio_TS_T40D11M7I0R0/autosar/Dio_THA6206_LFBGA292.arxml")

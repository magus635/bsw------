"""Chip dependency scan: keywords, chip-name checks, default branches, hard-coded
values, resource coverage, ordering, checklist and read-only behaviour."""
import hashlib
from pathlib import Path
from types import SimpleNamespace

import pytest

from autosar_configurator.core.hardware import chip_dependency_scan as scan
from autosar_configurator.core.hardware.chip_database import ChipDefinition
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef, EcucParameterDef, EcucParameterType)

THA6206 = ChipDefinition(name="THA6206_LFBGA292",
                         selectors={"Os.OsResourceSubderivative": "Os_THA6206"})
THA6412 = ChipDefinition(name="THA6412_BGA516",
                         selectors={"Os.OsResourceSubderivative": "Os_THA6412"})
THA6104 = ChipDefinition(name="THA6104_LFBGA180")
CHIPS = [THA6206, THA6412, THA6104]

OS_XDM = """<?xml version='1.0'?>
<datamodel xmlns:a="http://www.tresos.de/_projects/DataModel2/08/attribute.xsd">
  <v:var name="OsResourceSubderivative" type="ENUMERATION">
    <a:a name="DESC" value="EN: Selects THA6206 or THA6412"/>
  </v:var>
  <v:lst name="MemoryBlock">
    <a:da name="ENABLE" type="XPath"
          expr="node:value(./../OsResourceSubderivative) = &apos;Os_THA6206&apos;"/>
  </v:lst>
</datamodel>
"""

OS_TEMPLATE = """[!// comment: [!IF "OsResourceSubderivative = 'Os_THA6412'"!] is not code
[!IF "OsResourceSubderivative != 'Os_SC300'"!][!//
const uint32 Os_IsrGICAddr[] = {
[!IF "OsResourceSubderivative = 'Os_THA6206'"!][!//
    0xF0000000U,
[!ELSE!][!//
    0xF0200000U,
[!ENDIF!][!//
};
[!ENDIF!][!//
; CPUXBTCM 0x00100000 is a comment
#define SMALL 0x100U
"""

PORT_TEMPLATE = """[!IF "contains(node:value(ResourceSubderivative), 'THA610X')"!]
x
[!ENDIF!]
[!IF "not(contains(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative, 'THA6412'))"!]
[!ENDIF!]
"""

KERNEL_C = """#include "THA6412_regs.h"
/* THA6206 needs core IDs
   #ifdef OS_THA6412 in a comment */
#ifdef OS_THA6206
    IntConfig.coreID = 1;
#else
    IntConfig.priority = 1;
#endif
#ifdef THA6_REG_PROTECT
#endif
#if !defined(THA6_THA6412) && \\
    defined(FOO)
#endif
"""

PLUGIN_XML = """<?xml version="1.0"?>
<plugin>
   <extension point="dreisoft.tresos.autosar2.api.plugin.ecuresource">
      <ecuresource derivate="THA6XXX" file="resource/Os_Resource_THA6206.properties"
                   moduleId="Os_THA6_ASR21" target="ARM">
         <parameter name="subderivative" value="Os_THA6206"></parameter>
      </ecuresource>
   </extension>
   <extension point="dreisoft.tresos.autosar2.api.plugin.ecuresource">
      <ecuresource derivate="THA6XXX" file="resource/Os_Resource_Wrong.properties"
                   moduleId="Os_THA6_ASR21" target="ARM">
         <parameter name="subderivative" value="Os_THA6412"></parameter>
      </ecuresource>
   </extension>
</plugin>
"""


def _write(path: Path, text: str) -> Path:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
    return path


@pytest.fixture
def workspace(tmp_path):
    project_dir = tmp_path / "proj"
    plugin = tmp_path / "plugins" / "Os_THA6_ASR21"
    xdm = _write(plugin / "config" / "Os.xdm", OS_XDM)
    _write(plugin / "generate_PB" / "Os" / "isr" / "Os_isr_Lcfg.c", OS_TEMPLATE)
    _write(plugin / "plugin.xml", PLUGIN_XML)
    _write(plugin / "resource" / "Os_Resource_THA6206.properties",
           "OsResource.NumOfCores=2\nOs.GicIntTriggerMethod=LEVEL\n")
    _write(plugin / "resource" / "Os_Resource_Wrong.properties", "OsResource.NumOfCores=4\n")
    _write(project_dir / "templates" / "Port" / "src" / "Port_PBcfg.c", PORT_TEMPLATE)
    _write(project_dir / "templates" / "Os" / "Os_Cfg.h",
           "[!VAR \"n\" = \"ecu:get('OsResource.NumOfCores')\"!]"
           "[!VAR \"t\" = \"ecu:get('Os.GicIntTriggerMethod')\"!]\n")
    _write(tmp_path / "OS_Kernel" / "Os" / "isr" / "Os_isr_hal.c", KERNEL_C)
    dpa = _write(project_dir / "p.dpa", "{}")

    module_def = EcucModuleDef(short_name="Os")
    module_def.parameters["OsResourceSubderivative"] = EcucParameterDef(
        short_name="OsResourceSubderivative", param_type=EcucParameterType.ENUMERATION,
        literals=["Os_THA6206", "Os_THA6412", "Os_SC300"])
    # Port is loaded without a definition file at hand: its project templates are scanned
    project = SimpleNamespace(path=dpa, module_defs={"Os": xdm, "Port": project_dir / "Port.xdm"},
                              module_managers={"Os": SimpleNamespace(module_def=module_def)})
    return SimpleNamespace(project=project, root=tmp_path, project_dir=project_dir)


def _scan(workspace, **kwargs):
    kwargs.setdefault("extra_dirs", ["../OS_Kernel"])
    return scan.scan_project(workspace.project, chips=CHIPS, **kwargs)


def _at(result, category, path_end, line=None):
    return [f for f in result.by_category(category)
            if f.path.endswith(path_end) and (line is None or f.line == line)]


# --- keywords ------------------------------------------------------------------

def test_keywords_family_and_tokens():
    keywords = scan.ChipKeywords(["THA6104_LFBGA180", "THA6206_LFBGA292", "Os_SC300"])
    assert keywords.tokens == {"THA6104", "THA6206", "SC300"}
    assert keywords.chips_in("THA610X") == ["THA610X"]
    assert keywords.chips_in("THA6XXX") == ["THA6XXX"]
    assert keywords.chips_in("THA6206_LFBGA292") == ["THA6206_LFBGA292"]
    assert keywords.chips_in("OS_THA6206") == ["THA6206"]
    assert keywords.chips_in("THA6_REG_PROTECT") == []
    assert keywords.chips_in("LFBGA292") == []


def test_user_keyword():
    keywords = scan.ChipKeywords(["THA6206_LFBGA292"], extra=["NEWCHIP"])
    assert keywords.chips_in("CFG_NEWCHIP_A") == ["NEWCHIP"]


# --- checks --------------------------------------------------------------------

def test_xdm_condition_reported_description_not(workspace):
    result = _scan(workspace)
    found = _at(result, scan.CHECK, "config/Os.xdm")
    assert [f.line for f in found] == [8]
    assert found[0].chips == ("Os_THA6206",)
    assert "&apos;" not in found[0].text


def test_contains_in_port_template(workspace):
    result = _scan(workspace)
    found = _at(result, scan.CHECK, "templates/Port/src/Port_PBcfg.c", 1)
    assert found and found[0].chips == ("THA610X",)
    assert found[0].path == "templates/Port/src/Port_PBcfg.c"
    quoted_first_argument = _at(result, scan.CHECK, "templates/Port/src/Port_PBcfg.c", 4)
    assert quoted_first_argument and quoted_first_argument[0].chips == ("THA6412",)


def test_template_comment_not_reported(workspace):
    result = _scan(workspace)
    lines = [f.line for f in _at(result, scan.CHECK, "Os_isr_Lcfg.c")]
    assert lines == [2, 4]


def test_kernel_preprocessor_checks(workspace):
    result = _scan(workspace)
    found = _at(result, scan.CHECK, "Os/isr/Os_isr_hal.c")
    assert [(f.line, f.chips) for f in found] == [(4, ("OS_THA6206",)), (11, ("THA6412",))]
    assert found[0].path == "../OS_Kernel/Os/isr/Os_isr_hal.c"


# --- default branches ------------------------------------------------------------

def test_else_and_negated_branches(workspace):
    result = _scan(workspace)
    template = _at(result, scan.DEFAULT_BRANCH, "Os_isr_Lcfg.c")
    assert [(f.line, f.chips) for f in template] == [(2, ("Os_SC300",)), (6, ("Os_THA6206",))]
    assert "第 4 行" in template[1].note
    kernel = _at(result, scan.DEFAULT_BRANCH, "Os_isr_hal.c")
    assert [f.line for f in kernel] == [6, 11]


# --- hard-coded values -------------------------------------------------------------

def test_hardcoded_values(workspace):
    result = _scan(workspace)
    found = _at(result, scan.HARDCODED, "Os_isr_Lcfg.c")
    assert [f.line for f in found] == [5, 7]


def test_hardcoded_limit(tmp_path):
    keywords = scan.ChipKeywords(["THA6206_LFBGA292"])
    text = "\n".join(f"0x{0x30000000 + i:08X}" for i in range(60))
    findings, more = scan.scan_template("[!VAR \"a\" = \"1\"!]\n" + text, "t.c", keywords)
    assert len(findings) == scan.MAX_HARDCODED_PER_FILE and more == 10


# --- coverage --------------------------------------------------------------------

def test_coverage(workspace):
    texts = [f.text for f in _scan(workspace).by_category(scan.COVERAGE)]
    assert "Os.OsResourceSubderivative = Os_SC300：芯片库中没有声明此值的芯片" in texts
    assert ("Os.OsResourceSubderivative = Os_SC300：Os_THA6_ASR21 的 plugin.xml "
            "没有为此值登记资源文件") in texts
    assert any("Os_THA6412：EB 登记 Os_Resource_Wrong.properties，本工具按文件名不会为芯片 "
               "THA6412_BGA516 加载它" in t for t in texts)
    assert any(t.startswith("Os.OsResourceSubderivative = Os_THA6412：缺少 Os.GicIntTriggerMethod")
               for t in texts)
    assert not any("Os_THA6206：缺少" in t for t in texts)


def test_missing_registered_file(workspace):
    plugin_xml = workspace.root / "plugins" / "Os_THA6_ASR21" / "plugin.xml"
    plugin_xml.write_text(PLUGIN_XML.replace("Os_Resource_Wrong", "Os_Resource_THA6412"),
                          encoding="utf-8")
    found = [f for f in _scan(workspace).by_category(scan.COVERAGE) if "不存在" in f.text]
    assert len(found) == 1 and found[0].line == 10
    assert found[0].path.endswith("plugins/Os_THA6_ASR21/plugin.xml")


# --- ordering, export, read-only ---------------------------------------------------

def test_order_is_deterministic(workspace):
    first = _scan(workspace).findings
    assert first == _scan(workspace).findings
    assert first == sorted(first, key=scan.Finding.sort_key)
    assert [f.category for f in first] == sorted((f.category for f in first),
                                                  key=scan.CATEGORIES.index)


def test_markdown_checklist(workspace):
    text = scan.to_markdown(_scan(workspace))
    assert "## 芯片名判断" in text and "## 资源覆盖" in text
    assert "- [ ] `../OS_Kernel/Os/isr/Os_isr_hal.c:4` #ifdef OS_THA6206（芯片：OS_THA6206）" in text


def test_cancel(workspace):
    with pytest.raises(scan.ScanCancelled):
        _scan(workspace, progress=lambda i, total, path: i < 1)


def test_scan_changes_nothing(workspace):
    def digest():
        return {p: hashlib.sha1(p.read_bytes()).hexdigest()
                for p in sorted(workspace.root.rglob("*")) if p.is_file()}

    before = digest()
    _scan(workspace)
    assert digest() == before


def test_large_file_skipped(workspace, monkeypatch):
    monkeypatch.setattr(scan, "MAX_SCAN_BYTES", 100)
    result = _scan(workspace)
    assert any(p.endswith("Os_isr_Lcfg.c") for p in result.skipped)


def test_display_path_far_away(tmp_path):
    base = tmp_path / "a" / "b" / "c" / "d"
    assert scan.display_path(tmp_path / "x.c", base) == (tmp_path / "x.c").as_posix()
    assert scan.display_path(tmp_path / "a" / "x.c", base) == "../../../x.c"


def test_scan_settings_saved_with_project(tmp_path):
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    manager = WorkspaceManager()
    project = manager.create_project("demo", tmp_path / "demo.dpa")
    assert project.chip_scan_dirs == [] and project.chip_scan_keywords == []
    project.chip_scan_dirs = ["../OS_Kernel"]
    project.chip_scan_keywords = ["THA6XXX"]
    manager.save_project()

    reopened, _ = WorkspaceManager().load_project(tmp_path / "demo.dpa")
    assert reopened.chip_scan_dirs == ["../OS_Kernel"]
    assert reopened.chip_scan_keywords == ["THA6XXX"]


def test_older_project_without_scan_settings(tmp_path):
    import json
    from autosar_configurator.core.workspace_manager import WorkspaceManager

    manager = WorkspaceManager()
    manager.create_project("demo", tmp_path / "demo.dpa")
    manager.save_project()
    data = json.loads((tmp_path / "demo.dpa").read_text(encoding="utf-8"))
    del data["chip_scan_dirs"], data["chip_scan_keywords"]
    (tmp_path / "demo.dpa").write_text(json.dumps(data), encoding="utf-8")

    reopened, _ = WorkspaceManager().load_project(tmp_path / "demo.dpa")
    assert reopened.chip_scan_dirs == [] and reopened.chip_scan_keywords == []

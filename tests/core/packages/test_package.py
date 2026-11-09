"""Tests for ModulePackage chip selection, definition lookup and PRE/REC loading."""

from pathlib import Path

import pytest

from autosar_configurator.core.packages.errors import PackageConflictError, PackageError
from autosar_configurator.core.packages.manifest import infer_package
from autosar_configurator.core.packages.package import ModulePackage
from autosar_configurator.core.packages.types import ModuleManifest, PackageFile

REPO = Path(__file__).resolve().parents[3]
MCU_PLUGIN = REPO / "test_import_project/Def/plugins/Mcu_THA6_AS440"

_VALUES = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Vendor</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-CONFIGURATION-VALUES>
          <SHORT-NAME>X_Pre</SHORT-NAME>
          <DEFINITION-REF DEST="ECUC-MODULE-DEF">/Vendor/X</DEFINITION-REF>
          <CONTAINERS>
            <ECUC-CONTAINER-VALUE>
              <SHORT-NAME>{container}</SHORT-NAME>
              <DEFINITION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">/Vendor/X/General</DEFINITION-REF>
              <PARAMETER-VALUES>
                <ECUC-NUMERICAL-PARAM-VALUE>
                  <DEFINITION-REF DEST="ECUC-INTEGER-PARAM-DEF">/Vendor/X/General/P</DEFINITION-REF>
                  <VALUE>{value}</VALUE>
                </ECUC-NUMERICAL-PARAM-VALUE>
              </PARAMETER-VALUES>
            </ECUC-CONTAINER-VALUE>
          </CONTAINERS>
        </ECUC-MODULE-CONFIGURATION-VALUES>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""

_DEF = """<?xml version="1.0" encoding="UTF-8"?>
<AUTOSAR xmlns="http://autosar.org/schema/r4.0">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>Vendor</SHORT-NAME>
      <ELEMENTS>
        <ECUC-MODULE-DEF>
          <SHORT-NAME>X</SHORT-NAME>
        </ECUC-MODULE-DEF>
      </ELEMENTS>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
"""


def _write(root: Path, rel: str, text: str) -> None:
    path = root / rel
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")


def _pkg(root: Path, files, pre=("/Vendor/X_Pre",), rec=()) -> ModulePackage:
    return ModulePackage(
        root,
        ModuleManifest(
            module="X",
            definition="/Vendor/X",
            files=[PackageFile(path=p, chips=list(c)) for p, c in files],
            pre=list(pre),
            rec=list(rec),
        ),
    )


def _param(config, container="General"):
    ctr = next(c for c in config.containers if c.short_name == container)
    return next(iter(ctr.parameter_values.values())).value


def test_chip_selects_pre_file(tmp_path):
    _write(tmp_path, "config/X_A_pre.arxml", _VALUES.format(container="General", value=1))
    _write(tmp_path, "config/X_B_pre.arxml", _VALUES.format(container="General", value=2))
    pkg = _pkg(tmp_path, [("config/X_A_pre.arxml", ["A"]), ("config/X_B_pre.arxml", ["B"])])

    assert [p.name for p in pkg.selected_files("B")] == ["X_B_pre.arxml"]
    [config] = pkg.load_pre("B")
    assert str(_param(config)) == "2"
    [config] = pkg.load_pre("A")
    assert str(_param(config)) == "1"
    assert pkg.warnings == []


def test_selected_files_unconditional_and_sorted(tmp_path):
    pkg = _pkg(tmp_path, [("config/z.arxml", []), ("config/b.arxml", ["B"]), ("config/a.arxml", [])])
    assert [p.name for p in pkg.selected_files(None)] == ["a.arxml", "z.arxml"]
    assert [p.name for p in pkg.selected_files("B")] == ["a.arxml", "b.arxml", "z.arxml"]


def test_two_pre_same_chip_conflict(tmp_path):
    _write(tmp_path, "config/p1.arxml", _VALUES.format(container="General", value=10))
    _write(tmp_path, "config/p2.arxml", _VALUES.format(container="General", value=20))
    pkg = _pkg(tmp_path, [("config/p1.arxml", ["A"]), ("config/p2.arxml", ["A"])])

    with pytest.raises(PackageConflictError) as exc:
        pkg.load_pre("A")
    names = sorted(Path(f).name for f in exc.value.files)
    assert names == ["p1.arxml", "p2.arxml"]
    assert "/Vendor/X_Pre" in exc.value.path


def test_pre_merged_from_two_files(tmp_path):
    _write(tmp_path, "config/p1.arxml", _VALUES.format(container="One", value=1))
    _write(tmp_path, "config/p2.arxml", _VALUES.format(container="Two", value=2))
    pkg = _pkg(tmp_path, [("config/p1.arxml", []), ("config/p2.arxml", [])])
    [config] = pkg.load_pre(None)
    assert sorted(c.short_name for c in config.containers) == ["One", "Two"]


def test_missing_pre_path_warns(tmp_path):
    _write(tmp_path, "config/p.arxml", _VALUES.format(container="General", value=1))
    pkg = _pkg(tmp_path, [("config/p.arxml", [])], pre=["/MICROSAR/Arti_Pre", "/Vendor/X_Pre"])

    result = pkg.load_pre(None)
    assert len(result) == 1
    assert len(pkg.warnings) == 1
    assert "/MICROSAR/Arti_Pre" in pkg.warnings[0]


def test_pre_only_in_unselected_chip_file_errors(tmp_path):
    _write(tmp_path, "config/p.arxml", _VALUES.format(container="General", value=1))
    pkg = _pkg(tmp_path, [("config/p.arxml", ["THA6412_BGA516"])])
    with pytest.raises(PackageError) as exc:
        pkg.load_pre("THA6206_LFBGA292")
    msg = str(exc.value)
    assert "/Vendor/X_Pre" in msg and "THA6206_LFBGA292" in msg and "p.arxml" in msg


def test_rec_uses_rec_paths(tmp_path):
    _write(tmp_path, "config/p.arxml", _VALUES.format(container="General", value=1))
    pkg = _pkg(tmp_path, [("config/p.arxml", [])], pre=[], rec=["/Vendor/X_Pre"])
    assert pkg.load_pre(None) == []
    assert len(pkg.load_rec(None)) == 1


def test_definition_file_arxml(tmp_path):
    _write(tmp_path, "config/X_def.arxml", _DEF)
    _write(tmp_path, "config/X_pre.arxml", _VALUES.format(container="General", value=1))
    pkg = _pkg(tmp_path, [("config/X_def.arxml", []), ("config/X_pre.arxml", [])])
    assert pkg.definition_file(None).name == "X_def.arxml"


def test_definition_file_conflict_and_missing(tmp_path):
    _write(tmp_path, "config/d1.arxml", _DEF)
    _write(tmp_path, "config/d2.arxml", _DEF)
    pkg = _pkg(tmp_path, [("config/d1.arxml", ["A"]), ("config/d2.arxml", ["A", "B"])])
    with pytest.raises(PackageConflictError) as exc:
        pkg.definition_file("A")
    assert exc.value.path == "/Vendor/X"
    assert len(exc.value.files) == 2
    assert pkg.definition_file("B").name == "d2.arxml"
    with pytest.raises(PackageError):
        pkg.definition_file("C")


def test_definition_file_matches_full_path(tmp_path):
    _write(tmp_path, "config/d.arxml", _DEF.replace("<SHORT-NAME>Vendor</SHORT-NAME>",
                                                    "<SHORT-NAME>Other</SHORT-NAME>"))
    pkg = _pkg(tmp_path, [("config/d.arxml", [])])
    with pytest.raises(PackageError):
        pkg.definition_file(None)


@pytest.mark.skipif(not MCU_PLUGIN.is_dir(), reason="EB plugin fixture missing")
def test_eb_mcu_definition_and_pre():
    pkg = ModulePackage(MCU_PLUGIN, infer_package(MCU_PLUGIN))
    assert pkg.definition_file(None).name == "Mcu.xdm"
    configs = pkg.load_pre(None)
    assert len(configs) == 1
    assert pkg.template_dir() is not None


def test_missing_manifest_file_raises(tmp_path):
    _write(tmp_path, "config/X_def.arxml", _DEF)
    pkg = _pkg(tmp_path, [("config/X_def.arxml", []), ("config/gone_pre.arxml", ["A"])])
    for call in (lambda: pkg.definition_file("A"), lambda: pkg.load_pre("A"),
                 lambda: pkg.load_rec(None)):
        with pytest.raises(PackageError) as exc:
            call()
        assert "config/gone_pre.arxml" in str(exc.value)
        assert tmp_path.as_posix() in str(exc.value)


def test_template_and_resource_dirs(tmp_path):
    (tmp_path / "generate").mkdir()
    pkg = _pkg(tmp_path, [])
    pkg.manifest.templates = "generate"
    pkg.manifest.resources = "resource"  # does not exist
    assert pkg.template_dir() == tmp_path / "generate"
    assert pkg.resource_dir() is None
    pkg.manifest.templates = None
    assert pkg.template_dir() is None

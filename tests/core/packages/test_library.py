"""Tests for module library scanning and package lookup."""

import json
from pathlib import Path

import pytest

from autosar_configurator.core.packages.errors import PackageConflictError, PackageError
from autosar_configurator.core.packages.library import LibraryRef, find_package, scan_library
from autosar_configurator.core.packages.package import ModulePackage
from autosar_configurator.core.packages.types import ModuleManifest

REPO = Path(__file__).resolve().parents[3]
EB_PLUGINS = REPO / "test_import_project/Def/plugins"


@pytest.mark.skipif(not EB_PLUGINS.is_dir(), reason="EB plugin fixture missing")
def test_eb_library_scan():
    ref = LibraryRef(path=EB_PLUGINS.as_posix(), kind="eb-plugins", exclude=["Dio_THA6_AS440"])
    packages = scan_library(ref, base=REPO)

    dirs = [p.root.name for p in packages]
    assert dirs == sorted(dirs)
    modules = {p.manifest.module for p in packages}
    assert "Mcu" in modules
    assert "Dio" not in modules
    assert "Dio_THA6_AS440" not in dirs
    mcu = next(p for p in packages if p.manifest.module == "Mcu")
    assert mcu.manifest.definition == "/THA6_AS440_FuSa/Mcu"


@pytest.mark.skipif(not EB_PLUGINS.is_dir(), reason="EB plugin fixture missing")
def test_eb_library_relative_path():
    ref = LibraryRef(path="test_import_project/Def/plugins", kind="eb-plugins")
    assert any(p.manifest.module == "Mcu" for p in scan_library(ref, base=REPO))


def _write_pkg(lib: Path, name: str, definition: str) -> None:
    d = lib / name
    d.mkdir(parents=True)
    (d / "module.json").write_text(
        json.dumps({"schema": 1, "module": name, "definition": definition, "files": []}),
        encoding="utf-8",
    )


def test_package_library_scan_skips_invalid_and_excluded(tmp_path):
    lib = tmp_path / "lib"
    _write_pkg(lib, "Zeta", "/V/Zeta")
    _write_pkg(lib, "Alpha", "/V/Alpha")
    _write_pkg(lib, "Skip", "/V/Skip")
    (lib / "NoManifest").mkdir()
    (lib / "Broken").mkdir()
    (lib / "Broken" / "module.json").write_text('{"schema": 99}', encoding="utf-8")
    (lib / "file.txt").write_text("x", encoding="utf-8")

    packages = scan_library(LibraryRef(path="lib", kind="package", exclude=["Skip"]), base=tmp_path)
    assert [p.root.name for p in packages] == ["Alpha", "Zeta"]


def test_scan_missing_library_returns_empty(tmp_path):
    assert scan_library(LibraryRef(path="nope", kind="package"), base=tmp_path) == []


def test_scan_unknown_kind_raises(tmp_path):
    with pytest.raises(PackageError):
        scan_library(LibraryRef(path=".", kind="weird"), base=tmp_path)


def _pkg(root: Path, definition: str) -> ModulePackage:
    return ModulePackage(root, ModuleManifest(module=root.name, definition=definition))


def test_duplicate_definition_across_libraries(tmp_path):
    a = _pkg(tmp_path / "lib1" / "Mcu", "/THA6_AS440_FuSa/Mcu")
    b = _pkg(tmp_path / "lib2" / "Mcu_THA6_AS440", "/THA6_AS440_FuSa/Mcu")
    with pytest.raises(PackageConflictError) as exc:
        find_package([(0, [a]), (1, [b])], "/THA6_AS440_FuSa/Mcu")
    assert exc.value.path == "/THA6_AS440_FuSa/Mcu"
    assert exc.value.files == [a.root.as_posix(), b.root.as_posix()]


def test_find_package_hit_and_miss(tmp_path):
    a = _pkg(tmp_path / "Mcu", "/V/Mcu")
    b = _pkg(tmp_path / "Can", "/V/Can")
    assert find_package([(0, [a]), (1, [b])], "/V/Can") == (1, b)
    with pytest.raises(PackageError):
        find_package([(0, [a, b])], "/V/Port")

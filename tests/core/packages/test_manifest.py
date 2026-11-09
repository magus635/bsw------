"""Tests for module manifest loading and writing."""

import json
import tempfile
from pathlib import Path
import pytest

from autosar_configurator.core.packages import (
    PackageFile,
    ModuleManifest,
    load_manifest,
    write_manifest,
    PackageError,
)


def test_manifest_roundtrip():
    """Write manifest, load it back, should match."""
    with tempfile.TemporaryDirectory() as tmpdir:
        pkg_dir = Path(tmpdir)

        # Create manifest with various fields
        manifest = ModuleManifest(
            module="TestModule",
            definition="/Vendor/TestModule",
            implementation_path="/Vendor/TestImpl",
            files=[
                PackageFile(path="config/test.xdm"),
                PackageFile(path="config/chip_specific.xdm", chips=["THA6412_BGA516"]),
            ],
            pre=["/Vendor/TestModule_Pre"],
            rec=["/Vendor/TestModule_Rec"],
            templates="generate_PB",
            resources="resource",
            implementation="src",
            exchange_copies=["autosar/Test_THA6412.arxml"],
            origin={"source": "test"},
            inferred=False,
            chip_selector={"field": "some_selector"},
        )

        write_manifest(pkg_dir, manifest)
        loaded = load_manifest(pkg_dir)

        assert loaded.module == manifest.module
        assert loaded.definition == manifest.definition
        assert loaded.implementation_path == manifest.implementation_path
        assert len(loaded.files) == 2
        assert loaded.files[0].path == "config/test.xdm"
        assert loaded.files[0].chips == []
        assert loaded.files[1].path == "config/chip_specific.xdm"
        assert loaded.files[1].chips == ["THA6412_BGA516"]
        assert loaded.pre == manifest.pre
        assert loaded.rec == manifest.rec
        assert loaded.templates == manifest.templates
        assert loaded.resources == manifest.resources
        assert loaded.implementation == manifest.implementation
        assert loaded.exchange_copies == manifest.exchange_copies
        assert loaded.origin == manifest.origin
        assert loaded.inferred == manifest.inferred
        assert loaded.chip_selector == manifest.chip_selector


def test_manifest_minimal():
    """Minimal manifest with only required fields."""
    with tempfile.TemporaryDirectory() as tmpdir:
        pkg_dir = Path(tmpdir)

        manifest = ModuleManifest(
            module="MinimalModule",
            definition="/Vendor/MinimalModule",
        )

        write_manifest(pkg_dir, manifest)
        loaded = load_manifest(pkg_dir)

        assert loaded.module == "MinimalModule"
        assert loaded.definition == "/Vendor/MinimalModule"
        assert loaded.files == []
        assert loaded.pre == []
        assert loaded.rec == []
        assert loaded.templates is None
        assert loaded.resources is None
        assert loaded.implementation_path is None


def test_manifest_bad_schema_rejected():
    """Manifest with unsupported schema version raises PackageError."""
    with tempfile.TemporaryDirectory() as tmpdir:
        pkg_dir = Path(tmpdir)
        manifest_path = pkg_dir / "module.json"

        # Write manifest with schema version 2
        with open(manifest_path, "w") as f:
            json.dump({
                "schema": 2,
                "module": "Test",
                "definition": "/Test/Module",
            }, f)

        with pytest.raises(PackageError, match="Unsupported manifest schema 2"):
            load_manifest(pkg_dir)


def test_manifest_keys_sorted():
    """write_manifest produces sorted keys."""
    with tempfile.TemporaryDirectory() as tmpdir:
        pkg_dir = Path(tmpdir)

        manifest = ModuleManifest(
            module="SortTest",
            definition="/SortTest/Module",
            templates="generate_PB",
            resources="resource",
            pre=["/SortTest/Pre"],
            rec=["/SortTest/Rec"],
        )

        write_manifest(pkg_dir, manifest)

        with open(pkg_dir / "module.json", "r") as f:
            data = json.load(f)
            keys = list(data.keys())

        # Check that keys are sorted
        assert keys == sorted(keys)


def test_load_manifest_missing():
    """load_manifest raises PackageError if module.json missing."""
    with tempfile.TemporaryDirectory() as tmpdir:
        pkg_dir = Path(tmpdir)

        with pytest.raises(PackageError, match="No module.json"):
            load_manifest(pkg_dir)

"""tools/os_port_check: object comparison and setup errors; the SC300 run on QEMU when the kernel,
T1, arm-none-eabi-gcc and QEMU are available (OS_KERNEL_DIR, OS_T1_DIR; see the tool's README)."""
import os
import shutil
from pathlib import Path

import pytest

from tools.os_port_check import __main__ as cli
from tools.os_port_check import common, sc300


def _objects(directory: Path, **files):
    directory.mkdir(parents=True, exist_ok=True)
    for name, content in files.items():
        (directory / f"{name}.o").write_bytes(content)
    return directory


def test_identical_objects(tmp_path):
    a = _objects(tmp_path / "a", x=b"1", y=b"2")
    b = _objects(tmp_path / "b", x=b"1", y=b"2")
    assert common.compare_objects(a, b) == []


def test_differing_and_missing_objects_are_listed(tmp_path):
    a = _objects(tmp_path / "a", x=b"1", y=b"2", gone=b"3")
    b = _objects(tmp_path / "b", x=b"1", y=b"changed", new=b"4")
    assert common.compare_objects(a, b) == ["only in baseline: gone.o", "only in current: new.o", "differs: y.o"]


def test_missing_directory_is_a_setup_problem(monkeypatch, capsys):
    monkeypatch.delenv("OS_KERNEL_DIR", raising=False)
    monkeypatch.delenv("OS_T1_DIR", raising=False)
    assert cli.main(["sc300"]) == 2
    assert "OS_KERNEL_DIR" in capsys.readouterr().err


def test_directory_must_exist(tmp_path):
    with pytest.raises(common.CheckError, match="not a directory"):
        common.directory(str(tmp_path / "nope"), "X", "thing")


def _available():
    try:
        common.gcc()
        common.qemu()
    except common.CheckError:
        return False
    return all(os.environ.get(v) and Path(os.environ[v]).is_dir() for v in ("OS_KERNEL_DIR", "OS_T1_DIR"))


@pytest.mark.skipif(not _available(), reason="needs OS_KERNEL_DIR, OS_T1_DIR, arm-none-eabi-gcc and QEMU")
def test_sc300_example_runs_on_qemu(tmp_path):
    passed, output = sc300.check(Path(os.environ["OS_KERNEL_DIR"]), Path(os.environ["OS_T1_DIR"]), tmp_path / "w")
    assert passed, output
    assert output.count("\n") >= 17
    shutil.rmtree(tmp_path / "w", ignore_errors=True)

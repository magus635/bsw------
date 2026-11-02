"""The layout session of a project: open, update from a scan, place by hand, save."""
import json
from types import SimpleNamespace

from autosar_configurator.core.memmap import rules as rl
from autosar_configurator.core.memmap.check import CheckResult, SectionRow
from autosar_configurator.core.memmap.config import config_path, load_config
from autosar_configurator.core.memmap.session import LayoutSession, project_dir
from autosar_configurator.core.memmap.symbols import COPY, RegionNeed, Reference


def _project(tmp_path, chip="THA6206_LFBGA292"):
    return SimpleNamespace(path=tmp_path / "p.dpa", selected_chip=chip, chip_database=None)


def _need(name):
    return RegionNeed(name, [COPY], [Reference(name, (COPY,), "startup.c", 1, "X")])


def _row(output, kind="BSS", core=None):
    return SectionRow(output=output, kind=kind, names=(), modules=("CAN",), core=core,
                      non_cacheable=False, uses=())


def _result(needs=()):
    return CheckResult(needs=list(needs))


def test_the_path_is_in_the_projects_integration_directory(tmp_path):
    session = LayoutSession.open(_project(tmp_path))
    assert session.path == config_path(tmp_path) and project_dir(_project(tmp_path)) == tmp_path


def test_a_project_without_a_file_opens_empty_and_writes_nothing(tmp_path):
    session = LayoutSession.open(_project(tmp_path))
    assert session.config.regions == [] and not session.dirty and session.load_error == ""
    assert not (tmp_path / "IntegrationProject").exists()


def test_a_damaged_file_is_reported_and_the_project_still_opens(tmp_path):
    path = config_path(tmp_path)
    path.parent.mkdir(parents=True)
    path.write_text("{bad", encoding="utf-8")
    session = LayoutSession.open(_project(tmp_path))
    assert "memorymap.json" in session.load_error and session.config.regions == []


def test_update_prepares_the_factory_rules_and_the_required_regions(tmp_path):
    session = LayoutSession.open(_project(tmp_path))
    prepared = session.update(_result([_need("PRIVATE_DATA_CORE0")]))
    assert prepared.rules_installed and session.dirty
    assert session.config.region("PRIVATE_DATA_CORE0").window == "CPU0BTCM"


def test_a_second_update_without_changes_does_not_mark_it_changed(tmp_path):
    session = LayoutSession.open(_project(tmp_path))
    session.update(_result([_need("PRIVATE_DATA_CORE0")]))
    session.save()
    session.update(_result([_need("PRIVATE_DATA_CORE0")]))
    assert not session.dirty


def test_place_by_hand_and_the_refusals(tmp_path):
    session = LayoutSession.open(_project(tmp_path))
    session.update(_result())
    refused = session.place([_row(".a", "BSS"), _row(".b", "TEXT")], "UNDEFINE_RAM_BSS")
    assert session.config.manual == {".a": "UNDEFINE_RAM_BSS"}
    assert len(refused) == 1 and refused[0].startswith(".b：") and "TEXT" in refused[0]
    assert session.placements([_row(".a")])[".a"].status == rl.MANUAL


def test_unplace_returns_to_the_rules(tmp_path):
    session = LayoutSession.open(_project(tmp_path))
    session.update(_result())
    session.place([_row(".a")], "UNDEFINE_RAM_BSS")
    session.unplace([".a", ".never"])
    placed = session.placements([_row(".a")])[".a"]
    assert placed.status == rl.BY_RULE and placed.target == "UNDEFINE_RAM_BSS"


def test_placing_where_it_already_is_does_not_mark_it_changed(tmp_path):
    session = LayoutSession.open(_project(tmp_path))
    session.update(_result())
    session.place([_row(".a")], "UNDEFINE_RAM_BSS")
    session.save()
    session.place([_row(".a")], "UNDEFINE_RAM_BSS")
    assert not session.dirty


def test_save_and_open_again(tmp_path):
    session = LayoutSession.open(_project(tmp_path))
    session.update(_result())
    session.place([_row(".a")], "PRIVATE_BSS_CORE0")
    path = session.save()
    assert not session.dirty and path.is_file()
    again = LayoutSession.open(_project(tmp_path))
    assert again.config.manual == {".a": "PRIVATE_BSS_CORE0"}
    assert json.loads(path.read_text(encoding="utf-8"))["chip"] == "THA6206_LFBGA292"


def test_saving_without_a_project_location_is_an_error(tmp_path):
    import pytest
    from autosar_configurator.core.memmap.config import ConfigError
    session = LayoutSession.open(SimpleNamespace(path=None, selected_chip="X"))
    with pytest.raises(ConfigError, match="保存位置"):
        session.save()


def test_saving_clears_a_load_error(tmp_path):
    path = config_path(tmp_path)
    path.parent.mkdir(parents=True)
    path.write_text("{bad", encoding="utf-8")
    session = LayoutSession.open(_project(tmp_path))
    session.save()
    assert session.load_error == "" and load_config(path).regions == []


def test_the_cores_of_the_chip_trim_the_regions(tmp_path):
    session = LayoutSession.open(_project(tmp_path))
    session.update(_result([_need("PRIVATE_DATA_CORE0"), _need("PRIVATE_DATA_CORE2")]))
    assert session.config.region("PRIVATE_DATA_CORE2") is None
    assert session.config.trimmed == ["PRIVATE_DATA_CORE2"]

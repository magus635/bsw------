"""The chip YAML keeps memory regions with and without the grouping fields, and the
library chips keep their checksum (the compatibility guarantee of add-chip-memory-editor)."""
import copy

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
    default_chips_dir,
)
from autosar_configurator.core.hardware.chip_exporter import ChipDefinitionExporter, chip_checksum
from autosar_configurator.core.hardware.memory_regions import (
    LOCAL,
    MemoryRegionDef,
    group_memories,
    memory_region_dict,
)

PLAIN = [MemoryRegionDef("CPUXATCM", 0x0, 0x10000, "ram", LOCAL, False),
         MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True)]
GROUPED = [MemoryRegionDef("GMU_NORMAL", 0x10000000, 0x40000, "ram", None, True, "GMU", "normal",
                           "LinkerAdsPf.scat 注释表"),
           MemoryRegionDef("GMU_DEVICE", 0x82000000, 0x40000, "ram", None, False, "GMU", "device")]


def _save_and_load(tmp_path, regions, name="DEMO"):
    chip = ChipDefinition(name=name, memory_regions=regions)
    path = tmp_path / f"{name}.yaml"
    ChipDefinitionExporter().save_yaml(chip, path)
    return path, ChipDatabase()._load_chip_from_yaml(path)


def test_grouped_entries_survive_a_save_and_load(tmp_path):
    _, loaded = _save_and_load(tmp_path, GROUPED)
    assert loaded.memory_regions == GROUPED and not loaded.content_modified
    assert [g.name for g in group_memories(loaded.memory_regions)] == ["GMU"]


def test_the_yaml_text_of_plain_entries_has_no_new_keys(tmp_path):
    path, _ = _save_and_load(tmp_path, PLAIN)
    text = path.read_text(encoding="utf-8")
    assert "memory:" not in text and "window:" not in text and "source:" not in text


def test_the_yaml_text_of_grouped_entries_has_them(tmp_path):
    path, _ = _save_and_load(tmp_path, GROUPED)
    text = path.read_text(encoding="utf-8")
    assert "memory: GMU" in text and "window: device" in text and "LinkerAdsPf.scat" in text


def test_checksum_of_plain_entries_is_what_it_always_was():
    """The exported dict of an entry without the new fields is the old one, key for key."""
    for region in PLAIN:
        assert list(memory_region_dict(region)) == (
            ["name", "start", "size", "type", "core", "cacheable"] if region.core is not None
            else ["name", "start", "size", "type", "cacheable"])


def test_a_new_field_changes_the_checksum():
    """It is chip content: editing it must show as a change."""
    plain = ChipDefinition(name="X", memory_regions=copy.deepcopy(PLAIN))
    grouped = ChipDefinition(name="X", memory_regions=[
        MemoryRegionDef("CPUXATCM", 0x0, 0x10000, "ram", LOCAL, False, memory="ATCM"), PLAIN[1]])
    assert chip_checksum(plain) != chip_checksum(grouped)


def test_every_library_chip_keeps_its_stored_checksum():
    db = ChipDatabase(default_chips_dir())
    for name in db.list_chips():
        chip = db.get_chip(name)
        assert not chip.content_modified, name
        if chip.checksum:
            assert chip_checksum(chip) == chip.checksum, name


def test_the_library_chips_other_than_tha6206_have_no_new_fields():
    db = ChipDatabase(default_chips_dir())
    for name in db.list_chips():
        if name == "THA6206_LFBGA292":
            continue
        for region in db.get_chip(name).memory_regions:
            assert (region.memory, region.window, region.source) == (None, None, None), name

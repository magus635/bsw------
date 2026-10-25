"""generalize-chip-peripheral-resources: peripheral instances of any type."""
import shutil
from pathlib import Path

import pytest
import yaml

from autosar_configurator.core.hardware.chip_database import (
    CanResourceDef,
    ChipDatabase,
    ChipDefinition,
    IntcSourceDef,
    PortPinDef,
    default_chips_dir,
    parse_peripheral_resources,
)
from autosar_configurator.core.hardware.chip_exporter import ChipDefinitionExporter
from autosar_configurator.core.hardware.generic_mapper import GenericResourceMapper
from autosar_configurator.core.hardware.generic_resource import (
    GenericResourceDef,
    convert_legacy_chip,
)
from autosar_configurator.core.hardware.mapping_rule import (
    get_default_rule_loader,
    rule_resource_requirements,
)

MODULES = ["Can", "Adc", "Spi", "Port", "Dio", "Intc"]


def _load(tmp_path: Path, text: str, name="chip.yaml") -> ChipDefinition:
    path = tmp_path / name
    path.write_text(text, encoding="utf-8")
    return ChipDatabase()._load_chip_from_yaml(path)


def _roundtrip(chip: ChipDefinition, tmp_path: Path) -> ChipDefinition:
    path = tmp_path / f"{chip.name}.yaml"
    ChipDefinitionExporter().save_yaml(chip, path)
    return ChipDatabase()._load_chip_from_yaml(path)


def _actions(chip: ChipDefinition):
    """Mapping actions per module; a module whose rule fails maps to its error
    (the Port rule fails the same way before this change: its iterate yields a bool)."""
    mapper = GenericResourceMapper(chip=convert_legacy_chip(chip), rule_loader=get_default_rule_loader())
    result = {}
    for module in MODULES:
        try:
            result[module] = [str(a) for a in mapper.generate_mapping(module)]
        except Exception as e:  # noqa: BLE001 - compared, not hidden
            result[module] = f"ERROR {type(e).__name__}: {e}"
    return result


# --- 1. data layer -------------------------------------------------------------------------

def test_any_peripheral_type_is_loaded(tmp_path):
    chip = _load(tmp_path, """
name: C
resources:
  gpt_channel:
    - {resource_id: GPT0, properties: {channel_id: 0}}
    - {resource_id: GPT1, display_name: Timer 1, properties: {channel_id: 1}}
""")
    gpts = chip.resources["gpt_channel"]
    assert [g.resource_id for g in gpts] == ["GPT0", "GPT1"]
    assert gpts[0].display_name == "GPT0" and gpts[1].display_name == "Timer 1"
    assert gpts[1].properties == {"channel_id": 1}


@pytest.mark.parametrize("section, text", [
    ("duplicate", "can_controller: [{resource_id: CAN0}, {resource_id: CAN0}]"),
    ("empty id", "can_controller: [{resource_id: ''}]"),
    ("nested list", "can_controller: [{resource_id: CAN0, properties: {x: [[1]]}}]"),
    ("not a list", "can_controller: {resource_id: CAN0}"),
])
def test_invalid_instances_name_file_type_and_instance(tmp_path, section, text):
    path = tmp_path / "bad.yaml"
    path.write_text("name: B\nresources:\n  " + text + "\n", encoding="utf-8")
    with pytest.raises(ValueError) as err:
        ChipDatabase()._load_chip_from_yaml(path)
    assert "bad.yaml" in str(err.value) and "can_controller" in str(err.value)


def test_lossless_round_trip_with_per_instance_properties(tmp_path):
    chip = ChipDefinition(name="C", resources={
        "can_controller": [
            GenericResourceDef("can_controller", "CAN0", "CAN0", {"controller_id": 0, "supports_fd": True}),
            GenericResourceDef("can_controller", "CAN1", "Second", {"controller_id": 1, "supports_fd": False}),
        ],
        "clock_source": [GenericResourceDef("clock_source", "XOSC", "XOSC",
                                            {"frequency": 40000000, "type": "crystal"})],
        "adc_unit": [GenericResourceDef("adc_unit", "ADC0", "ADC0", {"channels": [0, 1, 2]})],
    })
    again = _roundtrip(chip, tmp_path)
    assert again.resources == chip.resources
    assert again.resources["can_controller"][1].properties["supports_fd"] is False


def test_legacy_and_new_format_are_equivalent(tmp_path):
    legacy = _load(tmp_path, """
name: C
can_resources:
  - {name: CAN0, controller_id: 0, max_baudrate: 1000000, supports_fd: true, mailbox_count: 64}
intc_sources:
  - {name: IRQ0, vector_number: 32}
""", "legacy.yaml")
    new = _load(tmp_path, """
name: C
resources:
  can_controller:
    - resource_id: CAN0
      display_name: CAN Controller 0
      properties: {controller_id: 0, max_baudrate: 1000000, supports_fd: true, mailbox_count: 64}
  intc_source:
    - {resource_id: IRQ0, properties: {vector_number: 32, priority_bits: 4, is_configurable: true}}
""", "new.yaml")
    assert legacy.effective_resources() == new.effective_resources()
    assert legacy.can_resources == [] and legacy.intc_sources == []      # one form only


def test_saving_writes_only_resources(tmp_path):
    legacy = _load(tmp_path, "name: C\ncan_resources:\n  - {name: CAN0, controller_id: 0}\n")
    path = tmp_path / "saved.yaml"
    ChipDefinitionExporter().save_yaml(legacy, path)
    data = yaml.safe_load(path.read_text(encoding="utf-8"))
    assert "resources" in data
    assert not {"can_resources", "adc_resources", "spi_resources", "intc_sources"} & set(data)


def test_resources_win_over_legacy_section(tmp_path, caplog):
    with caplog.at_level("WARNING"):
        chip = _load(tmp_path, """
name: C
can_resources: [{name: OLD, controller_id: 9}]
resources:
  can_controller: [{resource_id: CAN0, properties: {controller_id: 0}}]
""")
    assert [c.resource_id for c in chip.resources["can_controller"]] == ["CAN0"]
    assert any("can_resources" in r.message for r in caplog.records)


def test_chip_built_with_legacy_fields_still_works():
    chip = ChipDefinition(name="C", can_resources=[CanResourceDef(name="CAN0", controller_id=0)],
                          intc_sources=[IntcSourceDef(name="IRQ", vector_number=1)])
    eff = chip.effective_resources()
    assert eff["can_controller"][0].properties["controller_id"] == 0
    assert eff["intc_source"][0].resource_id == "IRQ"
    assert chip.peripheral_counts() == {"can_controller": 1, "intc_source": 1}


def test_validation_helper_directly():
    assert parse_peripheral_resources(None) == {}
    with pytest.raises(ValueError):
        parse_peripheral_resources(["x"])


# --- 2. mapping rule requirements ----------------------------------------------------------

def test_rule_requirements_of_the_builtin_rules():
    req = rule_resource_requirements()
    assert len(req) == 13
    assert req["can_controller"] == {"modules": ["Can"], "properties": ["controller_id", "supports_fd"]}
    assert req["gpt_channel"]["modules"] == ["Gpt"] and req["gpt_channel"]["properties"] == ["channel_id"]
    assert set(req["clock_source"]["properties"]) == {"frequency", "type"}
    assert set(req["spi_unit"]["properties"]) >= {"unit_id", "supports_dma"}


def test_rule_requirements_of_a_missing_directory(tmp_path):
    assert rule_resource_requirements(tmp_path / "none") == {}


# --- 3. hardware mapping -----------------------------------------------------------------

@pytest.mark.parametrize("name", ["THA610X_LFBGA180", "THA6206_LFBGA292", "THA6412_BGA516"])
def test_mapping_unchanged_after_migration(tmp_path, name):
    legacy = ChipDatabase()._load_chip_from_yaml(default_chips_dir() / f"{name}.yaml")
    # the same chip built with the legacy typed lists, as before this change
    as_before = ChipDefinition(name=name, ports=legacy.ports)
    for res in legacy.effective_resources().get("can_controller", []):
        p = res.properties
        # mailbox_count is not read by the Can rule; absent, the legacy default applies
        extra = {"mailbox_count": p["mailbox_count"]} if "mailbox_count" in p else {}
        as_before.can_resources.append(CanResourceDef(
            name=res.resource_id, controller_id=p["controller_id"], max_baudrate=p["max_baudrate"],
            supports_fd=p["supports_fd"], **extra))
    migrated = _roundtrip(legacy, tmp_path)
    assert _actions(migrated)["Can"] == _actions(as_before)["Can"]
    assert _actions(migrated) == _actions(legacy)


def test_new_peripheral_type_reaches_its_rule():
    chip = ChipDefinition(name="C", resources={"gpt_channel": [
        GenericResourceDef("gpt_channel", "GPT0", "GPT0", {"channel_id": 0}),
        GenericResourceDef("gpt_channel", "GPT1", "GPT1", {"channel_id": 1}),
    ]})
    mapper = GenericResourceMapper(chip=convert_legacy_chip(chip), rule_loader=get_default_rule_loader())
    actions = [str(a) for a in mapper.generate_mapping("Gpt")]
    assert any("GPT0" in a for a in actions) and any("GPT1" in a for a in actions)


def test_pins_still_become_gpio_instances():
    chip = ChipDefinition(name="C", ports={"PORT_A": [PortPinDef(name="PA0", port="PORT_A", pin=0)]})
    generic = convert_legacy_chip(chip)
    assert [r.resource_id for r in generic.get_resources("gpio_port")] == ["PORT_A"]
    assert [r.resource_id for r in generic.get_resources("gpio_pin")] == ["PA0"]


def test_wizard_offers_and_selects_a_chip_only_in_the_project(qtbot, tmp_path):
    from autosar_configurator.core.hardware.project_chip_store import ProjectChipStore
    from autosar_configurator.core.workspace_manager import WorkspaceProject
    from autosar_configurator.ui.wizards.hardware_mapping_wizard import (
        ChipSelectionPage,
    )

    ProjectChipStore(tmp_path).save(ChipDefinition(name="ONLY_HERE", resources={
        "gpt_channel": [GenericResourceDef("gpt_channel", "GPT0", "GPT0", {"channel_id": 0})]}))
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.selected_chip = "ONLY_HERE"
    project.chip_database = ChipDatabase()

    page = ChipSelectionPage(ChipDatabase(), tmp_path, project)
    qtbot.addWidget(page)
    assert page.chip_combo.currentData() == "ONLY_HERE"
    assert [r.resource_id for r in page.selected_chip.get_resources("gpt_channel")] == ["GPT0"]


def test_wizard_project_copy_wins_over_library(qtbot, tmp_path):
    from autosar_configurator.core.hardware.project_chip_store import ProjectChipStore
    from autosar_configurator.core.workspace_manager import WorkspaceProject
    from autosar_configurator.ui.wizards.hardware_mapping_wizard import (
        ChipSelectionPage,
    )

    library = ChipDatabase()
    library.register_chip(ChipDefinition(name="C", description="library"))
    ProjectChipStore(tmp_path).save(ChipDefinition(name="C", description="project copy"))
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.selected_chip = "C"
    project.chip_database = library

    page = ChipSelectionPage(library, tmp_path, project)
    qtbot.addWidget(page)
    assert page.selected_chip.description == "project copy"


def test_wizard_loads_a_chip_yaml_file_with_pins(qtbot, tmp_path, monkeypatch):
    from PySide6.QtWidgets import QFileDialog

    from autosar_configurator.ui.wizards.hardware_mapping_wizard import (
        ChipSelectionPage,
    )

    src = default_chips_dir() / "THA610X_LFBGA180.yaml"
    copy = tmp_path / "x.yaml"
    shutil.copy(src, copy)
    monkeypatch.setattr(QFileDialog, "getOpenFileName", lambda *a, **k: (str(copy), ""))
    page = ChipSelectionPage(ChipDatabase(), None)
    qtbot.addWidget(page)
    page._load_chip_from_file()
    assert page.selected_chip.get_resources("gpio_pin")          # pins come along


def test_pin_instances_in_resources_are_mapped_and_kept(qtbot):
    from autosar_configurator.ui.dialogs.peripheral_editor import PeripheralEditor

    chip = ChipDefinition(name="C", resources={"gpio_port": [
        GenericResourceDef("gpio_port", "PORT_A", "Port A", {"port_index": 0, "pin_count": 16})]})
    generic = convert_legacy_chip(chip)                       # no pin table: taken from resources
    assert [r.resource_id for r in generic.get_resources("gpio_port")] == ["PORT_A"]

    editor = PeripheralEditor(requirements=rule_resource_requirements())
    qtbot.addWidget(editor)
    editor.set_resources(chip.effective_resources())
    assert editor.type_list.count() == 0                      # not shown on the peripheral page
    assert editor.resources()["gpio_port"] == chip.resources["gpio_port"]   # but not dropped


def test_pin_table_takes_precedence_over_pin_resources():
    chip = ChipDefinition(
        name="C", ports={"PORT_A": [PortPinDef(name="PA0", port="PORT_A", pin=0)]},
        resources={"gpio_port": [GenericResourceDef("gpio_port", "PORT_A", "Old", {"pin_count": 99}),
                                 GenericResourceDef("gpio_port", "PORT_B", "Port B", {"pin_count": 8})]})
    ports = {r.resource_id: r for r in convert_legacy_chip(chip).get_resources("gpio_port")}
    assert ports["PORT_A"].properties["pin_count"] == 1        # from the pin table
    assert ports["PORT_B"].properties["pin_count"] == 8        # only in resources


def test_port_mapping_rule_generates_pin_subcontainers():
    chip = ChipDefinition(
        name="C",
        ports={
            "PORT_A": [PortPinDef(name=f"PA{i}", port="PORT_A", pin=i) for i in range(3)],
            "PORT_B": [PortPinDef(name=f"PB{i}", port="PORT_B", pin=i) for i in range(2)],
        },
    )
    mapper = GenericResourceMapper(chip=convert_legacy_chip(chip), rule_loader=get_default_rule_loader())
    actions = [str(a) for a in mapper.generate_mapping("Port")]
    assert "[CREATE] PortConfigSet/PortContainer_PORT_A" in actions
    assert "[CREATE] PortConfigSet/PortContainer_PORT_A/PortPin_PORT_A2" in actions
    assert "[CREATE] PortConfigSet/PortContainer_PORT_B/PortPin_PORT_B1" in actions
    assert "  [SET] PortPinId = 17" in actions  # port_index(1) * 16 + item_index(1)


def test_peripherals_derived_from_ecu_resources():
    from autosar_configurator.core.hardware.ecu_resource_diagnostics import (
        peripherals_from_ecu,
    )

    ecu = {
        "Can": {"HwUnitNode": ["CAN0", "CAN1"], "FDSupport": True, "MaxHwObjects": 64},
        "Adc": {"HwUnitId": ["SARADC0"], "MaxResolution": 12, "AdcChannels_Adc0": ["AN0", "AN1", "AN2"]},
        "Spi": {"HwUnitList": ["Spi_0", "Spi_1"], "DmaSupport": True},
        "Eth": {"MaxControllers": 1, "EthPhyIntf": ["RGMII"], "EthSpeed": ["ETH_1000MBPS"]},
        "Wdg": {"WdgInstance": "WDOG0"},
        "Mcu": {"SysPllClkMaxFrequency": 400000000, "HSEClkFrequency": 20000000},
        "Basetimer": {"HwUnitList": ["BASETIMER0", "BASETIMER1"]},
        "Asi": {"AvailableHWUnit": ["ASI0", "ASI1", "ASI2"]},
    }
    derived = peripherals_from_ecu(ecu)
    assert [r.resource_id for r in derived["can_controller"]] == ["CAN0", "CAN1"]
    assert derived["adc_unit"][0].properties["channel_count"] == 3
    assert [r.resource_id for r in derived["spi_unit"]] == ["Spi_0", "Spi_1"]
    assert derived["eth_controller"][0].properties["max_speed"] == 1000
    assert [r.resource_id for r in derived["wdg_unit"]] == ["WDOG0"]
    assert [r.resource_id for r in derived["clock_source"]] == ["PLL0", "XTAL"]
    assert [r.resource_id for r in derived["gpt_channel"]] == ["BASETIMER0", "BASETIMER1"]
    assert [r.resource_id for r in derived["lin_channel"]] == ["ASI0", "ASI1", "ASI2"]
    # Can.MaxHwObjects is a driver-wide limit and the vendor files give no
    # watchdog timeout range: neither is turned into a per-instance property
    assert "mailbox_count" not in derived["can_controller"][0].properties
    assert derived["wdg_unit"][0].properties == {"unit_id": 0}


@pytest.mark.parametrize("name", ["THA610X_LFBGA180", "THA6206_LFBGA292", "THA6412_BGA516"])
def test_builtin_chips_carry_ecu_resources_and_pass_consistency(name):
    from autosar_configurator.core.hardware.ecu_resource_data import (
        flatten_ecu_resources,
    )
    from autosar_configurator.core.hardware.ecu_resource_diagnostics import (
        check_consistency,
        typed_field_differences,
    )

    chip = ChipDatabase()._load_chip_from_yaml(default_chips_dir() / f"{name}.yaml")
    assert chip is not None
    assert not chip.content_modified
    assert chip.ecu_resources
    # A difference is accepted only for a field marked unconfirmed (flagged, not changed):
    # THA610X counts the lockstep pair as 2 cores, the Os uses 1
    unconfirmed = tuple((chip.metadata.get("unconfirmed") or {}))
    assert [m for m in typed_field_differences(chip) if not m.startswith(unconfirmed)] == []
    assert check_consistency(flatten_ecu_resources(chip.ecu_resources)) == []


@pytest.mark.parametrize("name", ["THA610X_LFBGA180", "THA6206_LFBGA292", "THA6412_BGA516"])
def test_builtin_chip_peripherals_agree_with_ecu_resources(name):
    """The hardware mapping wizard (resources) and code generation (ecu_resources)
    must see the same peripherals for every type the ECU resources describe."""
    from autosar_configurator.core.hardware.ecu_resource_diagnostics import (
        peripherals_from_ecu,
    )

    chip = ChipDatabase()._load_chip_from_yaml(default_chips_dir() / f"{name}.yaml")
    derived = peripherals_from_ecu(chip.ecu_resources)
    assert {"can_controller", "adc_unit", "spi_unit", "intc_source"} <= set(derived)
    for res_type, instances in derived.items():
        expected = [(r.resource_id, r.properties) for r in instances]
        actual = [(r.resource_id, r.properties) for r in chip.resources.get(res_type, [])]
        assert actual == expected, res_type


def test_interrupt_sources_derived_from_intc_resources():
    from autosar_configurator.core.hardware.ecu_resource_diagnostics import (
        peripherals_from_ecu,
    )

    ecu = {"Intc": {
        "IntSrcClass": ["GIC_PPI", "CAN", "EXTI", "BAD"],
        "CoreFixedIntClass": ["GIC_PPI"],
        "GIC_PPI.SubClassName": ["CPU0_PPI", "CPU1_PPI"],
        "GIC_PPI.CPU0_PPI.IntName": ["CPU0_TIMER"], "GIC_PPI.CPU0_PPI.IntID": [30],
        # vendor typo: CPU1's source reuses CPU0's name; the first one is kept
        "GIC_PPI.CPU1_PPI.IntName": ["CPU0_TIMER"], "GIC_PPI.CPU1_PPI.IntID": [30],
        "CAN.SubClassName": ["CAN0"],
        "CAN.CAN0.IntName": ["CAN00_INT0", "CAN00_INT1"], "CAN.CAN0.IntID": [256, 257],
        "EXTI.SubClassName": "EXTI0",                       # a single subclass is a scalar
        "EXTI.EXTI0.IntName": "EXTI0_IOUT0", "EXTI.EXTI0.IntID": 671,
        "BAD.SubClassName": ["X"],                          # names and IDs do not pair up
        "BAD.X.IntName": ["A", "B"], "BAD.X.IntID": [1],
    }}
    sources = peripherals_from_ecu(ecu)["intc_source"]
    assert [(s.resource_id, s.properties) for s in sources] == [
        ("CPU0_TIMER", {"vector_number": 30, "is_configurable": False, "int_class": "GIC_PPI"}),
        ("CAN00_INT0", {"vector_number": 256, "is_configurable": True, "int_class": "CAN"}),
        ("CAN00_INT1", {"vector_number": 257, "is_configurable": True, "int_class": "CAN"}),
        ("EXTI0_IOUT0", {"vector_number": 671, "is_configurable": True, "int_class": "EXTI"}),
    ]


"""add-chip-ports-from-ecu-resources: pin table from ECU resources, real port and pin numbers."""
import pytest

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
    PortPinDef,
    default_chips_dir,
)
from autosar_configurator.core.hardware.chip_exporter import chip_checksum
from autosar_configurator.core.hardware.ecu_resource_diagnostics import (
    pin_table_differences,
    ports_from_ecu,
)
from autosar_configurator.core.hardware.generic_mapper import GenericResourceMapper
from autosar_configurator.core.hardware.generic_resource import convert_legacy_chip, port_number_of
from autosar_configurator.core.hardware.mapping_rule import get_default_rule_loader

BUILTIN = ["THA610X_LFBGA180", "THA6206_LFBGA292", "THA6412_BGA516"]


def _port(**keys):
    return {"Port": keys}


def _builtin(name):
    return ChipDatabase()._load_chip_from_yaml(default_chips_dir() / f"{name}.yaml")


def _actions(chip, module):
    mapper = GenericResourceMapper(chip=convert_legacy_chip(chip), rule_loader=get_default_rule_loader())
    return [str(a) for a in mapper.generate_mapping(module)]


def _value_after(actions, create, name):
    index = actions.index(f"[CREATE] {create}")
    return next(a for a in actions[index + 1:] if a.startswith(f"  [SET] {name} = "))


# --- derivation ----------------------------------------------------------------------

def test_ports_and_pins_with_gaps():
    ports = ports_from_ecu(_port(AvailablePortsID="_0_ _10_", Port0_AvailablePins="_0_ _1_",
                                 Port10_AvailablePins="_0_ _1_ _2_ _3_ _4_ _5_ _6_ _7_ _8_ _9_ _10_ _11_ _13_ _14_ _15_"))
    assert list(ports) == ["P00", "P10"]
    assert [p.pin for p in ports["P10"]] == [*range(12), 13, 14, 15]
    assert ports["P10"][12].name == "P10_13"
    assert all(p.default_direction == "INPUT" and p.port == "P10" for p in ports["P10"])


def test_functions_from_the_hexadecimal_keys():
    ports = ports_from_ecu(_port(AvailablePortsID="_10_", Port10_AvailablePins="_0_",
                                 InputModesXDMa0="GPIO CAN00_RXDH", OutputModesXDMa0="GPIO CAN00_TXD"))
    assert ports["P10"][0].alternate_functions == ["GPIO", "CAN00_RXDH", "CAN00_TXD"]


def test_hex_suffix_is_lower_case_without_padding():
    ports = ports_from_ecu(_port(AvailablePortsID="_0_", Port0_AvailablePins="_0_ _11_",
                                 OutputModesXDM0="GPIO A", OutputModesXDMb="GPIO B"))
    assert [p.alternate_functions for p in ports["P00"]] == [["GPIO", "A"], ["GPIO", "B"]]


def test_read_only_port_lists_input_functions_only():
    ports = ports_from_ecu(_port(AvailablePortsID="_40_", AvailableReadOnlyPorts="_40_",
                                 Port40_AvailablePins="_0_", InputModesXDM280="GPIO SENT_SENT0A",
                                 OutputModesXDM280="GPIO GTM_TOUT1"))
    assert ports["P40"][0].alternate_functions == ["GPIO", "SENT_SENT0A"]


def test_no_port_data_and_port_without_pin_list():
    assert ports_from_ecu({}) == {}
    assert ports_from_ecu({"Mcu": {"A": 1}}) == {}
    assert list(ports_from_ecu(_port(AvailablePortsID="_0_ _1_", Port1_AvailablePins="_0_"))) == ["P01"]


@pytest.mark.parametrize("name, ports, pins", [("THA610X_LFBGA180", 16, 123),
                                               ("THA6206_LFBGA292", 17, 146),
                                               ("THA6412_BGA516", 23, 286)])
def test_builtin_chip_pin_table_equals_its_derivation(name, ports, pins):
    chip = _builtin(name)
    assert chip.ports == ports_from_ecu(chip.ecu_resources)
    assert (len(chip.ports), sum(len(p) for p in chip.ports.values())) == (ports, pins)
    assert not chip.content_modified and chip.checksum == chip_checksum(chip)
    assert pin_table_differences(chip) == []


# --- port numbers and mapping --------------------------------------------------------

@pytest.mark.parametrize("name, number", [("P10", 10), ("P00", 0), ("PORT_B", 1), ("PORT_A", 0),
                                          ("PORT_10", 10), ("GPIO_X", 0)])
def test_port_number_of(name, number):
    assert port_number_of(name) == number


def test_gpio_port_carries_real_pins_and_full_display_name():
    chip = ChipDefinition(name="C", ports={"P10": [PortPinDef(name="P10_13", port="P10", pin=13),
                                                   PortPinDef(name="P10_0", port="P10", pin=0)]})
    port = convert_legacy_chip(chip).get_resources("gpio_port")[0]
    assert port.properties["pins"] == [0, 13] and port.properties["port_index"] == 10
    assert port.display_name == "Port P10"


def test_builtin_thA6412_port_and_dio_numbers():
    chip = _builtin("THA6412_BGA516")
    port = _actions(chip, "Port")
    assert "[CREATE] PortConfigSet/PortContainer_P10/PortPin_P10_12" not in port      # no pin 12
    assert _value_after(port, "PortConfigSet/PortContainer_P10/PortPin_P10_13", "PortPinId") == \
        "  [SET] PortPinId = 173"
    assert _value_after(port, "PortConfigSet/PortContainer_P00/PortPin_P00_0", "PortPinId") == \
        "  [SET] PortPinId = 0"
    assert _value_after(port, "PortConfigSet/PortContainer_P10/PortPin_P10_0", "PortPinId") == \
        "  [SET] PortPinId = 160"
    dio = _actions(chip, "Dio")
    assert _value_after(dio, "DioConfig/DioPort_P10/DioChannel_P10_13", "DioChannelId") == \
        "  [SET] DioChannelId = 173"


def test_vendor_pin_ids_match():
    # PortPinId must be one of Port.PinId_Port<N>, the check of the vendor Port definition
    chip = _builtin("THA6412_BGA516")
    port = _actions(chip, "Port")
    for number in (0, 10, 41):
        name = f"P{number:02d}"
        vendor = [int(x) for x in chip.ecu_resources["Port"][f"PinId_Port{number}"].split("_") if x.strip()]
        ids = [int(_value_after(port, f"PortConfigSet/PortContainer_{name}/PortPin_{name}_{p.pin}",
                                "PortPinId").rsplit(" ", 1)[1]) for p in chip.ports[name]]
        assert ids == vendor


def test_port_containers_follow_available_ports_order():
    # PortNumber is derived from the container's position in Port.AvailablePortsID
    chip = _builtin("THA6412_BGA516")
    created = [a.split("PortContainer_")[1] for a in _actions(chip, "Port")
               if a.startswith("[CREATE] PortConfigSet/PortContainer_") and "/PortPin_" not in a]
    order = [int(x) for x in chip.ecu_resources["Port"]["AvailablePortsID"].split("_") if x.strip()]
    assert created == [f"P{n:02d}" for n in order]


def test_letter_named_ports_keep_their_numbers():
    chip = ChipDefinition(name="C", ports={
        "PORT_A": [PortPinDef(name=f"PA{i}", port="PORT_A", pin=i) for i in range(16)],
        "PORT_B": [PortPinDef(name=f"PB{i}", port="PORT_B", pin=i) for i in range(16)]})
    port = _actions(chip, "Port")
    assert _value_after(port, "PortConfigSet/PortContainer_PORT_B/PortPin_PORT_B_15", "PortPinId") == \
        "  [SET] PortPinId = 31"
    dio = _actions(chip, "Dio")      # was "DioChannelId = False": pins carried no port_index
    assert _value_after(dio, "DioConfig/DioPort_PORT_B/DioChannel_PB1", "DioChannelId") == \
        "  [SET] DioChannelId = 17"


def test_port_given_only_in_resources_maps_its_pins():
    from autosar_configurator.core.hardware.generic_resource import GenericResourceDef

    chip = ChipDefinition(name="C", resources={"gpio_port": [
        GenericResourceDef("gpio_port", "PORT_A", "Port A", {"port_index": 0, "pin_count": 2})]})
    port = _actions(chip, "Port")
    assert "[CREATE] PortConfigSet/PortContainer_PORT_A/PortPin_PORT_A_1" in port
    assert chip.resources["gpio_port"][0].properties == {"port_index": 0, "pin_count": 2}   # not changed


# --- consistency warning ---------------------------------------------------------------

def test_demo_pin_table_warns_without_blocking():
    chip = ChipDefinition(name="C", ecu_resources=_port(AvailablePortsID="_0_ _1_ _10_"),
                          ports={n: [PortPinDef(name=f"{n}0", port=n, pin=0)] for n in ("PORT_A", "PORT_D")})
    messages = pin_table_differences(chip)
    assert messages == ["pin table lacks ports of Port.AvailablePortsID: P01, P10",
                        "pin table has ports not in Port.AvailablePortsID: PORT_D"]


def test_no_warning_without_port_data():
    assert pin_table_differences(ChipDefinition(name="C", ports={"PORT_A": []})) == []


def test_port_mapping_sets_no_pin_mode_and_keeps_pin_ids():
    chip = _builtin("THA6412_BGA516")
    port = _actions(chip, "Port")
    assert not any("PortPinMode" in a or "PortPinInitialMode" in a for a in port)
    create = "PortConfigSet/PortContainer_P10/PortPin_P10_13"
    assert _value_after(port, create, "PortPinId").endswith("= 173")

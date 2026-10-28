"""The Port mapping rule agrees with the vendor Port definition."""
from pathlib import Path

import pytest
import yaml

from autosar_configurator.core.hardware.mapping_rule import get_default_rule_loader
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

REPO = Path(__file__).resolve().parent.parent.parent
PORT_XDM = REPO / "test_import_project/Def/plugins/Port_THA6_AS440/config/Port.xdm"
RULE = REPO / "autosar_configurator/data/mapping_rules/port.yaml"
TEMPLATES = REPO / "autosar_configurator/data/templates/port"


def _definition_parameters():
    """Parameter name -> literals of the vendor definition (empty when it lists none)."""
    module = EcucDefParser().parse_module_def_file(PORT_XDM)
    found = {}

    def walk(container):
        for name, param in container.parameters.items():
            found[name] = set(getattr(param, "literals", None) or [])
        for sub in container.sub_containers.values():
            walk(sub)

    for container in module.containers.values():
        walk(container)
    return found


def _rule_parameters():
    rule = yaml.safe_load(RULE.read_text(encoding="utf-8"))
    out = []

    def walk(node):
        for param in node.get("parameters", []) or []:
            options = (param.get("ui_options") or {}).get("options") or []
            values = set(options)
            if isinstance(param.get("default"), str):
                values.add(param["default"])
            out.append((param["name"], values))
        for sub in node.get("sub_containers", []) or []:
            walk(sub)

    for container in rule["containers"]:
        walk(container)
    return out


def test_rule_agrees_with_vendor_definition():
    definition = _definition_parameters()
    assert definition, "vendor Port definition was not parsed"
    rule = _rule_parameters()
    assert rule
    for name, values in rule:
        assert name in definition, f"{name} is not a parameter of the vendor definition"
        if definition[name]:
            assert values <= definition[name], f"{name}: {values - definition[name]} not in the definition"


def test_pin_mode_not_written():
    assert "PortPinMode" not in {n for n, _ in _rule_parameters()}


def test_initial_pin_mode_not_written():
    # its range is decided per pin at configuration time, so it cannot be compared statically
    assert "PortPinInitialMode" not in {n for n, _ in _rule_parameters()}
    assert not _definition_parameters().get("PortPinInitialMode")


def test_port_page_offers_no_inoperative_options():
    rule = get_default_rule_loader().get_rule("Port")
    names = [o.name for o in rule.ui_config.options]
    assert "default_mode" not in names and "default_direction" not in names


@pytest.mark.parametrize("name", ["port_gpio_input.yaml", "port_gpio_output.yaml"])
def test_templates_do_not_set_pin_mode(name):
    data = yaml.safe_load((TEMPLATES / name).read_text(encoding="utf-8"))
    adjustable = {p["name"] for p in data["parameters"].get("adjustable", [])}
    assert "PortPinMode" not in adjustable
    assert "PortPinMode" not in data["parameters"].get("fixed", {})

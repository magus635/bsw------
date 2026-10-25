"""add-sc300-kernel-port: the SC300 limits in the Os plugin (Os.xdm INVALID of
OsResourceSubderivative) and the SC300 branch of the Os_memmap.h template.

Uses the plugin files (see os_templates.py); skipped when they are not available. EB evaluates the
INVALID rules; here they are evaluated with the tool's XPath engine to check what they say.
"""
import html
import re

import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.generator.eb.renderer import Renderer

from .os_templates import ROOT, requires_templates

pytestmark = requires_templates
OS_XDM = ROOT.parent / "config" / "Os.xdm" if ROOT is not None else None
needs_xdm = pytest.mark.skipif(OS_XDM is None or not OS_XDM.is_file(), reason="plugin Os.xdm not found")


def _rules():
    text = OS_XDM.read_text(encoding="ascii", errors="replace")
    start = text.index("<a:v>Os_THA610X</a:v>")
    block = text[start:text.index("</v:var>", start)]
    return [(html.unescape(e), m) for e, m in re.findall(r'<a:tst expr="([^"]*)"\s*true = "([^"]*)"', block)]


@pytest.fixture(scope="module")
def os_def():
    parser = EcucDefParser()
    parser.set_selector_values({})
    return parser.parse_module_def_file(OS_XDM)


def _config(os_def, chip="Os_SC300", sc="SC1", cores=1, priorities=(3, 4), counter_source=15, hrt=False,
            last_source=17):
    mgr = ConfigurationManager(os_def)
    c = os_def.containers
    mgr.configuration.set_parameter_value("OsResourceSubderivative", chip,
                                          os_def.parameters["OsResourceSubderivative"].definition_ref)
    os_os = mgr.create_container_instance(c["OsOS"], None, "OsOS")
    mgr.set_parameter_value(os_os, "OsScalabilityClass", sc)
    mgr.set_parameter_value(os_os, "OsNumberOfCores", cores)
    for i, prio in enumerate(priorities):
        isr = mgr.create_container_instance(c["OsIsr"], None, f"Isr_{i}")
        mgr.set_parameter_value(isr, "OsIsrPriority", prio)
        source = counter_source if i == 0 else (last_source if i == len(priorities) - 1 else 16 + i)
        mgr.set_parameter_value(isr, "OsIsrInterruptSource", source)
    counter = mgr.create_container_instance(c["OsCounter"], None, "SystemTick")
    mgr.set_parameter_value(counter, "OsCounterType", "HARDWARE")
    mgr.set_parameter_value(counter, "OsTimerHighResolution", hrt)
    counter.set_reference_value("OsTimerTypeIsrRef", "/Os/Os/Isr_0",
                                c["OsCounter"].references["OsTimerTypeIsrRef"].definition_ref)
    return mgr


def _tripped(os_def, mgr):
    renderer = Renderer(strict=False)
    renderer.load_module(os_def, mgr.configuration)
    root = renderer.symbol_table.get_module("Os")
    node = next(n for n in root.children if n.short_name == "OsResourceSubderivative")
    return [i + 1 for i, (expr, _) in enumerate(_rules()) if renderer.evaluate_condition_at(node, expr, {})]


@needs_xdm
def test_four_rules_with_messages():
    messages = [m for _, m in _rules()]
    assert len(messages) == 5
    assert "SC1" in messages[0] and "1 to 7" in messages[1] and "SysTick" in messages[2] and "one core" in messages[3]
    assert "73 external interrupts" in messages[4] and "0 to 88" in messages[4]


@needs_xdm
@pytest.mark.parametrize("change, expected", [
    ({}, []),
    ({"sc": "SC3"}, [1]),
    ({"priorities": (0, 4)}, [2]),
    ({"priorities": (3, 12)}, [2]),
    ({"hrt": True}, [3]),
    ({"counter_source": 30}, [3]),
    ({"cores": 2}, [4]),
    ({"last_source": 88}, []),          # the last of the 73 external interrupts
    ({"last_source": 89}, [5]),
    ({"last_source": 255}, [5]),
])
def test_sc300_limits(os_def, change, expected):
    assert _tripped(os_def, _config(os_def, **change)) == expected


@needs_xdm
def test_other_chips_are_not_limited(os_def):
    mgr = _config(os_def, chip="Os_THA6206", sc="SC3", cores=2, priorities=(0, 30), counter_source=30, hrt=True)
    assert _tripped(os_def, mgr) == []


def test_memmap_template_has_a_default_branch_for_sc300():
    text = (ROOT / "Os" / "memorymap" / "Os_memmap.h").read_text(encoding="ascii")
    branch = re.search(r"\[!IF \"node:value\(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsResourceSubderivative\) = "
                       r"'Os_SC300'\"!\]\[!//\s*#undef MEMMAP_ERROR\s*\[!ENDIF!\]", text)
    assert branch, "SC300 keeps the Os sections in the default sections"
    assert branch.end() < text.index("#ifdef MEMMAP_ERROR"), "before the error check"

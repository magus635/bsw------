"""The reference drop-down selects the target of an EB-style reference value.

ARXML written by EB tresos (and by the Os ARTI template) uses "/<package>/<module>/<rest>", for example
/Arti/Arti/ArtiValues/E_X or /Os/Os/Task_A, while the panel lists targets by this tool's container path
"/<module>/<rest>". The selector used to leave such references on "(Not set)".
"""
import pytest

from autosar_configurator.core.model.configuration_model import EcucContainerValue, EcucModuleConfiguration
from autosar_configurator.core.model.definition_model import EcucReferenceDef
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel


class _Manager:
    def __init__(self, module, containers):
        self.configuration = EcucModuleConfiguration(short_name=module, definition_ref=f"/AUTOSAR/EcucDefs/{module}")
        for c in containers:
            c.module_name = module
            self.configuration.containers.append(c)


class _Project:
    def __init__(self, managers):
        self.module_managers = managers


def _container(name, definition):
    return EcucContainerValue(short_name=name, definition_ref=definition)


@pytest.fixture
def panel(qtbot):
    p = DaVinciConfigPanel()
    qtbot.addWidget(p)
    p.project = _Project({
        "Os": _Manager("Os", [_container("Task_A", "/AUTOSAR/EcucDefs/Os/OsTask"),
                              _container("Task_B", "/AUTOSAR/EcucDefs/Os/OsTask")]),
        "Arti": _Manager("Arti", [_container("E_X", "/AUTOSAR/EcucDefs/Arti/ArtiValues/ArtiExpression")]),
    })
    return p


def _ref_def(destination):
    return EcucReferenceDef(short_name="R", definition_ref="/AUTOSAR/EcucDefs/Arti/R", destination_ref=destination)


def _selected(panel, destination, value):
    combo = panel._create_reference_selector("R", _ref_def(destination), value)
    return combo.currentData(), combo.currentIndex()


def test_tool_style_path_is_selected(panel):
    assert _selected(panel, "/AUTOSAR/EcucDefs/Os/OsTask", "/Os/Task_A")[0] == "/Os/Task_A"


@pytest.mark.parametrize("value, expected", [
    ("/Os/Os/Task_B", "/Os/Task_B"),                                  # /<package>/<module>/<rest>
    ("/THA6_ASR21/Os/Task_A", "/Os/Task_A"),                          # package name differs from the module
])
def test_eb_style_path_is_selected(panel, value, expected):
    assert _selected(panel, "/AUTOSAR/EcucDefs/Os/OsTask", value)[0] == expected


def test_eb_style_path_inside_arti_is_selected(panel):
    value = "/Arti/Arti/E_X"
    assert _selected(panel, "/AUTOSAR/EcucDefs/Arti/ArtiValues/ArtiExpression", value)[0] == "/Arti/E_X"


def test_missing_target_stays_not_set(panel):
    assert _selected(panel, "/AUTOSAR/EcucDefs/Os/OsTask", "/Os/Os/Task_Gone") == (None, 0)


def test_path_without_a_loaded_module_is_not_stripped(panel):
    """/Foo/Bar/Task_A: the second segment 'Bar' is not a loaded module, so the first segment is not dropped"""
    assert _selected(panel, "/AUTOSAR/EcucDefs/Os/OsTask", "/Foo/Bar/Task_A") == (None, 0)


def test_a_target_of_the_wrong_type_is_not_offered(panel):
    """The expression container is not an OsTask: even with a matching name the reference stays unset."""
    assert _selected(panel, "/AUTOSAR/EcucDefs/Os/OsTask", "/Arti/Arti/E_X") == (None, 0)

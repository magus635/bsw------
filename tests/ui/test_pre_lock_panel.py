"""The config panel's Pre lock: a locked value is greyed, says where it came from, and the
unlock is recorded through the same manager call the project file reads (design §6.5 D1).

A stub manager stands in for the project wiring — the panel only asks it for
``value_origin``, ``pre_unlock_state`` and ``set_pre_unlocked`` — so the test is about the
panel, and the lock itself is covered by ``tests/core/test_pre_lock.py``.
"""
import pytest

PySide6 = pytest.importorskip("PySide6")

from autosar_configurator.core.baseline.origin import Origin
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue, EcucParameterValue)
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef, EcucParameterDef, EcucParameterType)
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel

LEVEL = "P:/Trk/TrkGeneral.Level"


class _Manager:
    """Just enough manager for the panel: values, their origins and the unlock state."""

    def __init__(self):
        self._locked = {"Level"}
        self.prototype = None

    def check_editable(self, instance, name=None):
        from autosar_configurator.core.config_manager import PreLockedError

        if name in self._locked:
            raise PreLockedError(f"P:/Trk/TrkGeneral.{name}")

    def value_origin(self, instance, name):
        if name in self._locked:
            return Origin.PRE
        return Origin.REC

    def pre_unlock_state(self, instance, name):
        if name != "Level":
            return None
        return "locked" if name in self._locked else "unlocked"

    def set_pre_unlocked(self, instance, name, unlocked):
        if name != "Level":
            return False
        if unlocked:
            self._locked.discard(name)
        else:
            self._locked.add(name)
        return True


def _container_def():
    container = EcucContainerDef(short_name="TrkGeneral", definition_ref="/Vendor/Trk/TrkGeneral")
    for name in ("Mode", "Level"):
        container.parameters[name] = EcucParameterDef(
            short_name=name, param_type=EcucParameterType.STRING,
            definition_ref=f"/Vendor/Trk/TrkGeneral/{name}",
            lower_multiplicity=0, upper_multiplicity=1)
    return container


def _instance():
    instance = EcucContainerValue(short_name="TrkGeneral", definition_ref="/Vendor/Trk/TrkGeneral")
    for name, value in (("Mode", "Fast"), ("Level", "3")):
        instance.parameter_values[name] = EcucParameterValue(
            definition_ref=f"/Vendor/Trk/TrkGeneral/{name}", value=value)
    return instance


@pytest.fixture
def panel(qtbot):
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    panel.show_instance(_instance(), _container_def(), _Manager())
    return panel


def _row(panel, param_name):
    for row in range(panel.params_table.rowCount()):
        item = panel.params_table.item(row, 0)
        if item is not None and item.data(0x0100) == param_name:
            return row
    raise AssertionError(f"{param_name} is not in the table")


def test_locked_value_is_greyed_and_disabled(panel):
    row = _row(panel, "Level")
    name_item = panel.params_table.item(row, 0)
    editor = panel.params_table.cellWidget(row, 1)

    assert name_item.text().startswith("🔒 ")
    assert "来源：PRE" in name_item.toolTip() and "锁定" in name_item.toolTip()
    assert editor.isEnabled() is False


def test_unlocked_value_is_editable_again(panel):
    manager = panel.config_manager
    manager._locked.clear()
    panel.refresh()
    row = _row(panel, "Level")
    assert "已解锁" in panel.params_table.item(row, 0).toolTip()
    assert "🔒" not in panel.params_table.item(row, 0).text()
    assert panel.params_table.cellWidget(row, 1).isEnabled() is True


def test_rec_value_has_no_lock(panel):
    row = _row(panel, "Mode")
    assert "🔒" not in panel.params_table.item(row, 0).text()
    assert "来源：REC" in panel.params_table.item(row, 0).toolTip()
    assert panel.params_table.cellWidget(row, 1).isEnabled() is True


def test_unlock_action_records_and_refreshes(panel):
    manager = panel.config_manager
    panel._set_pre_unlocked("Level", True)
    assert manager._locked == set()                       # recorded
    row = _row(panel, "Level")
    assert panel.params_table.cellWidget(row, 1).isEnabled() is True
    panel._set_pre_unlocked("Level", False)
    assert manager._locked == {"Level"}
    assert panel.params_table.cellWidget(_row(panel, "Level"), 1).isEnabled() is False


class _Project:
    """A project whose Trk baseline lost its layers: every value is USER, the lock is off."""

    packages = {}

    def __init__(self):
        from autosar_configurator.core.baseline.session import ModuleBaseline

        self.baselines = {"Trk": ModuleBaseline(
            base_config=object(), layers={}, pre_keys=set(), module_name="Trk",
            layers_untrusted=True)}
        self.module_managers = {}
        self.is_modified = False


class _UnavailableManager(_Manager):
    """Manager of the untrusted project: no per-value origin, no lock state — as core says."""

    def __init__(self):
        super().__init__()
        self.module_def = type("Def", (), {"short_name": "Trk"})()
        self.project_context = _Project()

    def value_origin(self, instance, name):
        return None

    def pre_unlock_state(self, instance, name):
        return None


def test_unavailable_baseline_shows_the_notice_and_no_lock(qtbot):
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    manager = _UnavailableManager()
    panel.show_instance(_instance(), _container_def(), manager, manager.project_context)

    assert not panel.baseline_notice.isHidden()          # shown (the panel itself is not)
    assert "基线不可用" in panel.baseline_notice.text()
    row = _row(panel, "Level")
    assert "🔒" not in panel.params_table.item(row, 0).text()
    assert panel.params_table.cellWidget(row, 1).isEnabled() is True


def test_batch_edit_skips_locked_values_and_lists_them(qtbot, monkeypatch):
    """The batch dialog never writes a locked value and says which ones it left alone.

    The dialog is built for the real ``Parameter`` class (it decides what it can edit from
    the elements' type), so the elements are real ones and only the lock check is a stub.
    """
    from autosar_configurator.core.config_manager import PreLockedError
    from autosar_configurator.core.model.container import Parameter
    from autosar_configurator.ui.widgets import batch_edit_dialog

    messages = []
    monkeypatch.setattr(batch_edit_dialog.QMessageBox, "information",
                        lambda *args, **kwargs: messages.append(args[2]))

    def check_locked(element, name):
        if name == "Locked":
            raise PreLockedError("P:/Trk/TrkGeneral.Locked")

    class _CommandManager:
        def __init__(self):
            self.executed = []

        def execute_command(self, command):
            self.executed.append(command)

    manager = _CommandManager()
    dialog = batch_edit_dialog.BatchEditDialog(
        [Parameter(short_name="Locked", value="3"), Parameter(short_name="Free", value="1")],
        manager, check_locked=check_locked)
    qtbot.addWidget(dialog)
    dialog.value_input.setText("9")
    dialog.property_combo.setCurrentText("value")
    dialog._apply_changes()

    assert dialog.skipped_locked == ["P:/Trk/TrkGeneral.Locked"]
    assert len(manager.executed) == 1                    # one command: Free only
    names = [c.parameter.short_name for c in manager.executed[0].commands]
    assert names == ["Free"]
    assert any("P:/Trk/TrkGeneral.Locked" in text for text in messages)


def test_variant_override_is_not_written_for_a_locked_value(qtbot):
    """A variant change on a locked value writes nothing — the override is persisted."""
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    manager = _Manager()
    instance = _instance()

    class _ModuleConfig:
        def __init__(self):
            self.written = []

        def get_value_for_variant(self, path, variant):
            return None, False

        def set_value_for_variant(self, path, value, variant):
            self.written.append((path, value, variant))

    instance.module_config = _ModuleConfig()

    class _Project:
        active_variant = "V2"
        is_modified = False

    panel.show_instance(instance, _container_def(), manager, _Project())
    panel._on_value_changed("Level", "9")

    assert instance.module_config.written == []       # nothing landed in variant_overrides
    assert instance.module_config is not None


def test_unlocked_value_may_be_overridden_per_variant(qtbot):
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    manager = _Manager()
    manager._locked.clear()
    instance = _instance()

    class _ModuleConfig:
        def __init__(self):
            self.written = []

        def get_value_for_variant(self, path, variant):
            return None, False

        def set_value_for_variant(self, path, value, variant):
            self.written.append((path, value, variant))

    instance.module_config = _ModuleConfig()

    class _Project:
        active_variant = "V2"
        is_modified = False

    panel.show_instance(instance, _container_def(), manager, _Project())
    panel._on_value_changed("Level", "9")

    # The panel keys the override on the instance path; the instance has no module name here
    assert instance.module_config.written == [("/Config/TrkGeneral.Level", "9", "V2")]


def test_comparison_highlight_keeps_the_lock_marker(qtbot):
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    instance = _instance()
    panel.show_instance(instance, _container_def(), _Manager())
    panel.compare_btn.setChecked(True)       # the highlight mode refresh() preserves
    panel.comparison_results = {"Level": {"current": "3", "reference": "4"}}
    panel.refresh()

    row = _row(panel, "Level")
    text = panel.params_table.item(row, 0).text()
    assert text.startswith("🔒 ") and "⚡" in text


def test_template_apply_is_all_or_nothing_on_a_locked_value(monkeypatch):
    """A template naming a locked Pre key writes nothing at all (no half-applied instance)."""
    from autosar_configurator.core.config_manager import PreLockedError
    from autosar_configurator.ui.wizards import template_wizard
    from autosar_configurator.ui.wizards.template_wizard import TemplateWizard

    written = []

    class _Manager:
        def check_editable(self, instance, name):
            if name == "Level":
                raise PreLockedError("P:/Trk/TrkGeneral.Level")

        def set_parameter_value(self, instance, name, value, enforce_lock=True):
            written.append(name)

    class _Template:
        container_def = "TrkGeneral"

        def get_all_params(self, values):
            return {"Mode": "Fast", "Level": "9"}

    class _Page:
        def __init__(self, data):
            self._data = data

        def get_data(self):
            return self._data

    wizard = TemplateWizard.__new__(TemplateWizard)
    wizard.category_page = _Page({"template": _Template()})
    wizard.param_page = _Page({"parameter_values": {}})
    wizard.target_page = _Page({"create_new": False, "existing_instance": object()})
    wizard.config_manager = _Manager()
    wizard.parent_instance = None
    wizard.created_instance = None

    from PySide6 import QtWidgets
    messages = []
    monkeypatch.setattr(QtWidgets.QMessageBox, "warning",
                        staticmethod(lambda *args, **kwargs: messages.append(args[2])))

    wizard.accept()

    assert written == []                                   # nothing was applied
    assert any("Level" in text for text in messages)        # and the user was told why

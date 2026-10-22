"""update-unified-chip-selection: one way to apply the project's chip; selectors read-only."""
from pathlib import Path
from unittest.mock import MagicMock

import pytest

from autosar_configurator.core.hardware.chip_database import (
    ChipDatabase,
    ChipDefinition,
)
from autosar_configurator.core.hardware.chip_selectors import configured_selector_values
from autosar_configurator.core.model.configuration_model import EcucContainerValue
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef,
    EcucParameterDef,
    EcucParameterType,
)
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.workspace_manager import WorkspaceProject
from autosar_configurator.ui.controllers.project_controller import ProjectController
from autosar_configurator.ui.dialogs.project_properties_dialog import (
    ProjectPropertiesDialog,
)
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel

REPO = Path(__file__).resolve().parent.parent.parent
RESOURCE_XDM = REPO / "test_import_project/Def/plugins/Resource_THA6_AS440/config/Resource.xdm"

THA6206 = ChipDefinition(name="THA6206_LFBGA292",
                         selectors={"Resource.ResourceSubderivative": "THA6206_LFBGA292"})
THA6412 = ChipDefinition(name="THA6412_BGA516",
                         selectors={"Resource.ResourceSubderivative": "THA6412_BGA516"})


def _project(tmp_path, chip, resource_value):
    db = ChipDatabase()
    db.register_chip(THA6206)
    db.register_chip(THA6412)
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.chip_database = db
    project.selected_chip = chip
    parser = EcucDefParser()
    parser.set_selector_values({})
    project.add_module(parser.parse_module_def_file(RESOURCE_XDM), RESOURCE_XDM)
    project.selected_chip = "THA6206_LFBGA292"
    project.apply_chip_selectors()                 # holder container with the 6206 value
    project.selected_chip = chip
    if resource_value is not None:
        for c in _walk(project.module_managers["Resource"].configuration.containers):
            if "ResourceSubderivative" in c.parameter_values:
                c.parameter_values["ResourceSubderivative"].value = resource_value
    return project


def _walk(containers):
    for c in containers:
        yield c
        yield from _walk(c.sub_containers)


def _value(project):
    return configured_selector_values(project, "Resource.ResourceSubderivative")


def _controller(project):
    win = MagicMock()
    win.current_project = project
    win._has_unsaved_changes = False
    win.chip_constraint_service.current_chip = project.selected_chip
    return ProjectController(win), win


def test_explicit_selection_writes_selectors_and_reloads_constraints(tmp_path):
    project = _project(tmp_path, "THA6206_LFBGA292", "THA6206_LFBGA292")
    ctrl, win = _controller(project)
    result = ctrl.apply_project_chip("THA6412_BGA516", write_selectors=True)
    assert project.selected_chip == "THA6412_BGA516"
    assert _value(project) == ["THA6412_BGA516"]
    assert result.changed == [("Resource.ResourceSubderivative", "THA6206_LFBGA292", "THA6412_BGA516")]
    assert win._has_unsaved_changes is True
    win.chip_constraint_service.set_project.assert_called_with(project)
    win.chip_constraint_service.set_chip.assert_called_once_with("THA6412_BGA516")


def test_open_or_import_keeps_the_configuration(tmp_path):
    project = _project(tmp_path, None, "THA6206_LFBGA292")
    ctrl, _win = _controller(project)
    assert ctrl.apply_project_chip("THA6412_BGA516", write_selectors=False) is None
    assert _value(project) == ["THA6206_LFBGA292"]
    assert len(ctrl.selector_mismatches()) == 1
    assert "Apply Chip Selectors" in ctrl._selector_status()


def test_same_chip_still_refreshes_the_ui(tmp_path):
    project = _project(tmp_path, "THA6412_BGA516", "THA6412_BGA516")
    ctrl, win = _controller(project)
    ctrl.apply_project_chip("THA6412_BGA516", write_selectors=False)
    win.chip_constraint_service.set_chip.assert_not_called()
    win._on_chip_constraints_changed.assert_called_once_with("THA6412_BGA516")


def test_apply_chip_selectors_action_in_project_properties(qtbot, tmp_path):
    project = _project(tmp_path, "THA6412_BGA516", "THA6206_LFBGA292")
    ctrl, _win = _controller(project)
    dialog = ProjectPropertiesDialog(project, None, apply_selectors=ctrl.apply_chip_selectors_now,
                                     selector_mismatches=ctrl.selector_mismatches)
    qtbot.addWidget(dialog)
    assert dialog.apply_selectors_btn.isEnabled()
    assert "THA6206_LFBGA292" in dialog.selector_label.text()

    from unittest.mock import patch
    with patch("autosar_configurator.ui.dialogs.project_properties_dialog.QMessageBox.information"), \
            patch.object(ProjectController, "_show_chip_change_preview", return_value=True) as shown:
        dialog._apply_chip_selectors()
    report = shown.call_args.args[0]
    assert report.selector_result.changed == [
        ("Resource.ResourceSubderivative", "THA6206_LFBGA292", "THA6412_BGA516")]
    assert _value(project) == ["THA6412_BGA516"]
    assert not dialog.apply_selectors_btn.isEnabled()
    assert dialog.selector_label.text() == ""


def test_apply_chip_selectors_cancelled_in_the_preview(qtbot, tmp_path):
    from unittest.mock import patch

    project = _project(tmp_path, "THA6412_BGA516", "THA6206_LFBGA292")
    ctrl, win = _controller(project)
    dialog = ProjectPropertiesDialog(project, None, apply_selectors=ctrl.apply_chip_selectors_now,
                                     selector_mismatches=ctrl.selector_mismatches)
    qtbot.addWidget(dialog)
    with patch("autosar_configurator.ui.dialogs.project_properties_dialog.QMessageBox.information") as info, \
            patch.object(ProjectController, "_show_chip_change_preview", return_value=False):
        dialog._apply_chip_selectors()
    info.assert_not_called()
    assert _value(project) == ["THA6206_LFBGA292"]
    assert dialog.apply_selectors_btn.isEnabled()
    assert win._has_unsaved_changes is False


def _properties_with_chip(ctrl, chip, confirm):
    """Run Project Properties with ``chip`` chosen and the preview answered ``confirm``."""
    from unittest.mock import patch

    from autosar_configurator.ui.dialogs import project_properties_dialog as ppd

    data = {"name": "p", "version": "1", "author": "", "description": "", "selected_chip": chip}
    dialog = MagicMock()
    dialog.exec.return_value = True
    dialog.get_data.return_value = data
    with patch("importlib.reload", side_effect=lambda m: m), \
            patch.object(ppd, "ProjectPropertiesDialog", return_value=dialog), \
            patch.object(ProjectController, "_show_chip_change_preview",
                         return_value=confirm) as shown:
        ctrl.show_project_properties()
    return shown


def test_chip_change_in_project_properties_is_previewed_then_applied(qtbot, tmp_path):
    project = _project(tmp_path, "THA6206_LFBGA292", "THA6206_LFBGA292")
    ctrl, win = _controller(project)
    shown = _properties_with_chip(ctrl, "THA6412_BGA516", confirm=True)
    report = shown.call_args.args[0]
    assert (report.current_chip, report.chip_name) == ("THA6206_LFBGA292", "THA6412_BGA516")
    assert report.error is None
    assert project.selected_chip == "THA6412_BGA516"
    assert _value(project) == ["THA6412_BGA516"]
    win.chip_constraint_service.set_chip.assert_called_once_with("THA6412_BGA516")


def test_chip_change_cancelled_in_the_preview(qtbot, tmp_path):
    project = _project(tmp_path, "THA6206_LFBGA292", "THA6206_LFBGA292")
    ctrl, win = _controller(project)
    resources = dict(project.ecu_resources or {})
    _properties_with_chip(ctrl, "THA6412_BGA516", confirm=False)
    assert project.selected_chip == "THA6206_LFBGA292"
    assert _value(project) == ["THA6206_LFBGA292"]
    assert dict(project.ecu_resources or {}) == resources
    win.chip_constraint_service.set_chip.assert_not_called()
    assert project.name == "p"                     # other properties are still saved


def test_preview_error_still_allows_the_change(qtbot, tmp_path):
    from unittest.mock import patch

    project = _project(tmp_path, "THA6206_LFBGA292", "THA6206_LFBGA292")
    ctrl, _win = _controller(project)
    with patch("autosar_configurator.generator.eb.enable_conditions.disabled_containers",
               side_effect=RuntimeError("boom")):
        report = ctrl.preview_chip_change("THA6412_BGA516")
    assert report.error == "boom"
    assert project.selected_chip == "THA6206_LFBGA292"


def test_preview_dialog_lists_groups(qtbot):
    from autosar_configurator.core.hardware.chip_selectors import SelectorResult
    from autosar_configurator.generator.eb.enable_conditions import DisabledContainer
    from autosar_configurator.ui.dialogs.chip_change_preview_dialog import (
        ChipChangePreviewDialog,
        ChipChangeReport,
        summary_lines,
    )

    disabled = [DisabledContainer("Os", f"/Os/{name}", "MemoryBlock") for name in ("os_bss", "BSS", "RODATA")]
    disabled.append(DisabledContainer("Os", "/Os/SystemModeStack", "SystemModeStack"))
    selectors = SelectorResult(changed=[("Os.OsResourceSubderivative", None, "Os_THA6412")])
    report = ChipChangeReport("THA6412_BGA516", "THA6206_LFBGA292", selector_result=selectors,
                              disabled=disabled)
    assert summary_lines(disabled) == ["Os: MemoryBlock x3", "Os: SystemModeStack x1"]

    dialog = ChipChangePreviewDialog(report)
    qtbot.addWidget(dialog)
    assert "从 THA6206_LFBGA292 切换为 THA6412_BGA516" in dialog.heading_label.text()
    table = dialog.selector_table
    assert [table.item(0, c).text() for c in range(3)] == [
        "Os.OsResourceSubderivative", "（未设置）", "Os_THA6412"]
    tree = dialog.disabled_tree
    assert [tree.topLevelItem(i).text(0) for i in range(tree.topLevelItemCount())] == [
        "Os：MemoryBlock × 3", "Os：SystemModeStack × 1"]
    group = tree.topLevelItem(0)
    assert [group.child(i).text(0) for i in range(group.childCount())] == [
        "/Os/BSS", "/Os/os_bss", "/Os/RODATA"]          # case-insensitive order
    assert "将失效" in dialog.status_label.text()
    assert dialog.accept_button.text() == "切换"

    enabled_only = ChipChangePreviewDialog(ChipChangeReport("A", "B", enabled=disabled))
    qtbot.addWidget(enabled_only)
    assert "重新参与代码生成" in enabled_only.status_label.text()
    assert "保留在项目中" not in enabled_only.status_label.text()

    assert not dialog.unavailable_label.isVisibleTo(dialog)

    warned = ChipChangePreviewDialog(ChipChangeReport(
        "THA6412_BGA516", "THA6206_LFBGA292", disabled=disabled,
        unavailable=[("Os", "MemoryBlock")],
        descriptions={("Os", "MemoryBlock"): "Memory Block indicate the data block."}))
    qtbot.addWidget(warned)
    assert warned.unavailable_label.isVisibleTo(warned)
    assert "Os：MemoryBlock" in warned.unavailable_label.text()
    assert "无法编译或链接" in warned.unavailable_label.text()
    tree = warned.disabled_tree
    assert tree.topLevelItem(0).text(0) == "Os：MemoryBlock × 3（全部失效）"
    assert tree.topLevelItem(0).toolTip(0) == "MemoryBlock：Memory Block indicate the data block."
    assert tree.topLevelItem(1).text(0) == "Os：SystemModeStack × 1"
    assert "没有描述" in tree.topLevelItem(1).toolTip(0)

    condition = "node:value(./../OsResourceSubderivative) = 'Os_THA6206'"
    explained = ChipChangePreviewDialog(ChipChangeReport(
        "THA6412_BGA516", "THA6206_LFBGA292", disabled=disabled,
        disabled_reasons={
            ("Os", "MemoryBlock"): [(condition, ["OsResourceSubderivative：Os_THA6206 → Os_THA6412"])],
            ("Os", "SystemModeStack"): [(condition, ["OsResourceSubderivative：Os_THA6206 → Os_THA6412"])]}))
    qtbot.addWidget(explained)
    assert explained.reason_label.text() == (
        f"失效原因：ENABLE 条件 {condition} 不再成立（OsResourceSubderivative：Os_THA6206 → Os_THA6412）。"
        "涉及：MemoryBlock、SystemModeStack")
    first = explained.disabled_tree.topLevelItem(0).child(0).text(0)
    assert first.startswith("原因：ENABLE 条件") and "Os_THA6412" in first
    assert explained.disabled_tree.topLevelItem(0).child(1).text(0) == "/Os/BSS"

    unexplained = ChipChangePreviewDialog(ChipChangeReport(
        "A", "B", enabled=disabled[:1], enabled_reasons={("Os", "MemoryBlock"): [("x = 1", [])]}))
    qtbot.addWidget(unexplained)
    assert "恢复原因" in unexplained.reason_label.text()
    assert "未能定位具体变化" in unexplained.reason_label.text()

    empty = ChipChangePreviewDialog(ChipChangeReport("X", "X"))
    qtbot.addWidget(empty)
    assert "没有已配置的容器" in empty.status_label.text()
    assert "写入配置" in empty.heading_label.text()
    assert not empty.selector_table.isVisibleTo(empty)


@pytest.fixture
def panel(qtbot):
    panel = DaVinciConfigPanel()
    qtbot.addWidget(panel)
    return panel


def test_selector_parameter_is_read_only(panel, tmp_path):
    container_def = EcucContainerDef(short_name="ResourceGeneral",
                                     definition_ref="/Resource/ResourceGeneral")
    container_def.parameters["ResourceSubderivative"] = EcucParameterDef(
        short_name="ResourceSubderivative", param_type=EcucParameterType.ENUMERATION,
        definition_ref="/Resource/ResourceGeneral/ResourceSubderivative",
        lower_multiplicity=1, upper_multiplicity=1, literals=["THA6206_LFBGA292", "THA6412_BGA516"])
    container_def.parameters["ResourceOther"] = EcucParameterDef(
        short_name="ResourceOther", param_type=EcucParameterType.INTEGER,
        definition_ref="/Resource/ResourceGeneral/ResourceOther",
        lower_multiplicity=1, upper_multiplicity=1)
    manager = MagicMock()
    manager.module_def.short_name = "Resource"
    db = ChipDatabase()
    db.register_chip(THA6412)
    project = WorkspaceProject("p", tmp_path / "p.dpa")
    project.chip_database = db
    project.selected_chip = "THA6412_BGA516"

    instance = EcucContainerValue(short_name="ResourceGeneral", definition_ref="/Resource/ResourceGeneral")
    panel.show_instance(instance, container_def, manager, project)
    editors = {panel.params_table.item(r, 0).text(): panel.params_table.cellWidget(r, 1)
               for r in range(panel.params_table.rowCount())}
    assert not editors["ResourceSubderivative"].isEnabled()
    assert "Project Properties" in editors["ResourceSubderivative"].toolTip()
    assert editors["ResourceOther"].isEnabled()

    project.selected_chip = None                    # no chip: nothing is locked
    panel.show_instance(instance, container_def, manager, project)
    editors = {panel.params_table.item(r, 0).text(): panel.params_table.cellWidget(r, 1)
               for r in range(panel.params_table.rowCount())}
    assert editors["ResourceSubderivative"].isEnabled()

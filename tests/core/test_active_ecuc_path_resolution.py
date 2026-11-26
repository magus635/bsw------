"""Regression tests for /ActiveEcuC/... path normalization, lookup, rules, generator, and UI."""

from pathlib import Path
from unittest.mock import MagicMock
import pytest

from autosar_configurator.core.analysis.impact_analyzer import ImpactAnalyzer
from autosar_configurator.core.config_manager import ConfigurationManager, ValidationError
from autosar_configurator.core.model.configuration_model import (
    EcucContainerValue,
    EcucModuleConfiguration,
    EcucParameterValue,
    EcucReferenceValue,
    ResolutionError,
)
from autosar_configurator.core.model.definition_model import (
    EcucContainerDef,
    EcucModuleDef,
    EcucParameterDef,
    EcucParameterType,
    EcucReferenceDef,
)
from autosar_configurator.core.model.ecuc_paths import (
    ecuc_ref_matches_container,
    ecuc_ref_targets_module,
    is_active_ecuc_path,
    normalize_ecuc_path,
    strip_active_ecuc_prefix,
    strip_ecuc_prefixes,
)
from autosar_configurator.core.rules.dependency_rules import CircularDependencyRule
from autosar_configurator.core.rules.reference_rules import (
    DanglingReferenceRule,
    ReferenceIntegrityRule,
)
from autosar_configurator.core.workspace_manager import WorkspaceProject
from autosar_configurator.generator.eb.overlay_engine import OverlayEngine
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.generator import CodeGenerator
from autosar_configurator.ui.controllers.navigation_controller import NavigationController
from autosar_configurator.ui.widgets.dependency_graph import DependencyGraphWidget


def _build_os_and_com_project(os_config_short_name: str = "Os"):
    project = WorkspaceProject("ActiveEcuCTest")

    os_def = EcucModuleDef("Os", definition_ref="/MICROSAR/Os")
    task_def = EcucContainerDef("OsTask", definition_ref="/MICROSAR/Os/OsTask", upper_multiplicity=-1)
    prio_def = EcucParameterDef(
        "OsTaskPriority",
        definition_ref="/MICROSAR/Os/OsTask/OsTaskPriority",
        param_type=EcucParameterType.INTEGER,
    )
    autostart_def = EcucContainerDef(
        "OsTaskAutostart",
        definition_ref="/MICROSAR/Os/OsTask/OsTaskAutostart",
    )
    appmode_def = EcucParameterDef(
        "OsTaskAppMode",
        definition_ref="/MICROSAR/Os/OsTask/OsTaskAutostart/OsTaskAppMode",
        param_type=EcucParameterType.STRING,
    )
    autostart_def.parameters["OsTaskAppMode"] = appmode_def
    task_def.parameters["OsTaskPriority"] = prio_def
    task_def.sub_containers["OsTaskAutostart"] = autostart_def
    os_def.containers["OsTask"] = task_def

    com_def = EcucModuleDef("Com", definition_ref="/MICROSAR/Com")
    com_cfg_def = EcucContainerDef("ComConfig", definition_ref="/MICROSAR/Com/ComConfig")
    ipdu_def = EcucContainerDef(
        "ComIPdu",
        definition_ref="/MICROSAR/Com/ComConfig/ComIPdu",
        upper_multiplicity=-1,
    )
    ref_def = EcucReferenceDef(
        "ComTaskRef",
        definition_ref="/MICROSAR/Com/ComConfig/ComIPdu/ComTaskRef",
        destination_ref="/MICROSAR/Os/OsTask",
    )
    ipdu_def.references["ComTaskRef"] = ref_def
    com_cfg_def.sub_containers["ComIPdu"] = ipdu_def
    com_def.containers["ComConfig"] = com_cfg_def

    os_mgr = project.add_module(os_def, Path("Os.arxml"))
    if os_config_short_name != "Os":
        os_mgr.configuration.short_name = os_config_short_name
    com_mgr = project.add_module(com_def, Path("Com.arxml"))

    task0 = os_mgr.create_container_instance(task_def, instance_name="OsTask_0")
    task0.set_parameter_value("OsTaskPriority", 10, prio_def.definition_ref)
    auto0 = EcucContainerValue("OsTaskAutostart_0", autostart_def.definition_ref)
    auto0.parameter_values["OsTaskAppMode"] = EcucParameterValue(
        appmode_def.definition_ref, "OSDEFAULTAPPMODE"
    )
    task0.add_sub_container(auto0)

    com_cfg = com_mgr.create_container_instance(com_cfg_def, instance_name="ComConfig")
    ipdu0 = com_mgr.create_container_instance(ipdu_def, parent=com_cfg, instance_name="ComIPdu_0")
    ipdu0.set_reference_value("ComTaskRef", "/ActiveEcuC/Os/OsTask_0", ref_def.definition_ref)

    return project, os_def, os_mgr, task0, auto0, com_def, com_mgr, com_cfg, ipdu0


class TestEcucPathsHelper:
    def test_normalization_and_prefix_stripping(self):
        assert normalize_ecuc_path(" /ActiveEcuC//Os/OsTask_0/ ") == "/ActiveEcuC/Os/OsTask_0"
        assert normalize_ecuc_path("   ") == ""
        assert strip_active_ecuc_prefix("/ActiveEcuC/Os/OsTask_0") == "/Os/OsTask_0"
        assert strip_active_ecuc_prefix("/ActiveEcuC/ActiveEcuC/Os/OsTask_0") == "/Os/OsTask_0"
        assert strip_active_ecuc_prefix("/activeecuc/Os") == "/Os"
        assert strip_active_ecuc_prefix("/ActiveEcuC") == "/ActiveEcuC"
        assert is_active_ecuc_path("/ActiveEcuC/Os") is True
        assert is_active_ecuc_path("/ActiveEcuC/ActiveEcuC/Os/OsTask_0") is True
        assert is_active_ecuc_path("/ActiveEcuC") is False
        assert is_active_ecuc_path("/MICROSAR_MemMap/SwAddrMethods/CODE") is False

        assert strip_ecuc_prefixes("/ActiveEcuC/Os/OsTask_0") == "/Os/OsTask_0"
        assert strip_ecuc_prefixes("/ActiveEcuC/ActiveEcuC/Os/OsTask_0") == "/Os/OsTask_0"
        assert strip_ecuc_prefixes("/Config/Os/OsTask_0") == "/Os/OsTask_0"
        assert strip_ecuc_prefixes("/I2c_Config/I2c/I2cChannel_0") == "/I2c/I2cChannel_0"
        assert strip_ecuc_prefixes("/Pkg/Os/OsTask_0", known_modules={"Os"}) == "/Os/OsTask_0"
        assert strip_ecuc_prefixes("/Os/Os/OsTask_0", known_modules={"Os"}) == "/Os/OsTask_0"
        # Depth-2 /Iom/Iom must remain intact
        assert strip_ecuc_prefixes("/Iom/Iom", known_modules={"Iom"}) == "/Iom/Iom"


class TestCoreActiveEcuCResolutionAndRules:
    def test_single_module_get_instance_by_path_strips_active_ecuc(self):
        project, _, os_mgr, task0, auto0, _, _, _, _ = _build_os_and_com_project()
        cfg = os_mgr.configuration

        assert cfg.get_instance_by_path("/ActiveEcuC/Os/OsTask_0") is task0
        assert cfg.get_instance_by_path("/ActiveEcuC/ActiveEcuC/Os/OsTask_0/OsTaskAutostart_0") is auto0
        assert cfg.get_instance_by_path(" /activeecuc/Os/OsTask_0/ ") is task0

    def test_single_module_short_name_differs_from_definition_leaf(self):
        cfg = EcucModuleConfiguration("Can_30_Core", "/MICROSAR/Can")
        ctrl = EcucContainerValue("CanController_0", "/MICROSAR/Can/CanConfigSet/CanController")
        cfg_set = EcucContainerValue("CanConfigSet", "/MICROSAR/Can/CanConfigSet")
        cfg_set.add_sub_container(ctrl)
        cfg.add_container(cfg_set)

        assert cfg.get_instance_by_path("/ActiveEcuC/Can/CanConfigSet/CanController_0") is ctrl
        assert cfg.get_instance_by_path("/ActiveEcuC/Can_30_Core/CanConfigSet/CanController_0") is ctrl

    def test_workspace_get_instance_by_path_handles_all_edge_cases(self):
        project, _, _, task0, auto0, _, _, _, _ = _build_os_and_com_project(os_config_short_name="Os_Core0")

        assert project.get_instance_by_path("/ActiveEcuC/Os/OsTask_0") is task0
        assert project.get_instance_by_path("/ActiveEcuC/Os_Core0/OsTask_0") is task0
        assert project.get_instance_by_path("/ActiveEcuC/ActiveEcuC/Os/OsTask_0/OsTaskAutostart_0") is auto0
        assert project.get_instance_by_path(" /activeecuc/Os/OsTask_0/ ") is task0

        proxy1 = project.get_instance_by_path("/ActiveEcuC/Os")
        proxy2 = project.get_instance_by_path("/ActiveEcuC/ActiveEcuC/Os_Core0/")
        proxy3 = project.get_instance_by_path("/activeecuc/Os")
        assert proxy1 is not None and getattr(proxy1, "_is_module_root_proxy", False)
        assert proxy2 is not None and proxy2.module_name == "Os"
        assert proxy3 is not None and proxy3.module_name == "Os"

    def test_unresolved_double_prefix_diagnostic_identifies_real_module(self):
        cfg = EcucModuleConfiguration("vSet", "/MICROSAR/vSet")
        c = EcucContainerValue("Init", "/MICROSAR/vSet/vSetBswInit")
        c.reference_values["ForeignMod"] = EcucReferenceValue(
            "/Def/ModRef", "/ActiveEcuC/ActiveEcuC/Lin", dest_type="ECUC-FOREIGN-REFERENCE-DEF"
        )
        c.reference_values["DeepMissing"] = EcucReferenceValue(
            "/Def/Ref", "/ActiveEcuC/ActiveEcuC/Can/CanConfigSet/Missing", dest_type="ECUC-REFERENCE-DEF"
        )
        cfg.add_container(c)
        _, errs = cfg.resolve_references(lambda _p: None)
        assert errs == 2
        assert c.reference_values["ForeignMod"].resolution_error.error_type == ResolutionError.MODULE_NOT_LOADED
        assert "'Lin'" in c.reference_values["ForeignMod"].resolution_error.suggestion
        assert "'Can'" in c.reference_values["DeepMissing"].resolution_error.suggestion

    def test_reverse_ref_find_deletion_guard_and_remove_module_proxy_cleanup(self):
        project, _, os_mgr, task0, _, _, com_mgr, com_cfg, ipdu0 = _build_os_and_com_project()

        # Add unresolved multi-ref targeting /ActiveEcuC/Os/OsTask_0
        ipdu0.add_multi_reference_value(
            "ExtraTasks",
            "/ActiveEcuC/ActiveEcuC/Os/OsTask_0",
            "/MICROSAR/Com/ComConfig/ComIPdu/ExtraTasks",
            0,
        )
        # Add module-root ref targeting /ActiveEcuC/Os
        ipdu0.set_reference_value(
            "OsModuleRoot",
            "/ActiveEcuC/Os",
            "/MICROSAR/Com/ComConfig/ComIPdu/OsModuleRoot",
            dest_type="ECUC-FOREIGN-REFERENCE-DEF",
        )

        # Before resolve_all_references(): find_global_references_to, _find_references_to, find_references_to_module all match
        refs_before = project.find_global_references_to(task0)
        assert (ipdu0, "ComTaskRef") in refs_before
        assert (ipdu0, "ExtraTasks") in refs_before
        assert os_mgr._find_references_to(task0)  # deletion guard sees cross-module /ActiveEcuC ref

        mod_refs_before = project.find_references_to_module("Os")
        assert any(r[2] == "ComTaskRef" for r in mod_refs_before)
        assert any(r[2] == "OsModuleRoot" for r in mod_refs_before)

        # After resolve_all_references(): delete_container_instance refuses, remove_module clears proxy too
        project.resolve_all_references(force=True)
        assert ipdu0.reference_values["OsModuleRoot"].is_resolved is True
        assert getattr(ipdu0.reference_values["OsModuleRoot"].target, "_is_module_root_proxy", False)

        with pytest.raises(ValidationError, match="Referenced by"):
            os_mgr.delete_container_instance(task0)
        project.remove_module("Os")
        assert "Os" not in project.module_managers
        assert ipdu0.reference_values["ComTaskRef"].target is None
        assert ipdu0.reference_values["OsModuleRoot"].target is None

    def test_validation_rules_and_impact_analyzer_handle_active_ecuc(self):
        cfg = EcucModuleConfiguration("Os", "/MICROSAR/Os")
        t1 = EcucContainerValue("TaskA", "/MICROSAR/Os/OsTask")
        t2 = EcucContainerValue("TaskB", "/MICROSAR/Os/OsTask")
        t1.set_reference_value("ChainRef", "/ActiveEcuC/Os/TaskB", "/MICROSAR/Os/OsTask/ChainRef")
        t2.add_multi_reference_value("ChainList", "/ActiveEcuC/ActiveEcuC/Os/TaskA", "/MICROSAR/Os/OsTask/ChainList", 0)
        cfg.add_container(t1)
        cfg.add_container(t2)

        assert ReferenceIntegrityRule().validate(None, cfg).messages == []
        assert DanglingReferenceRule().validate(None, cfg).messages == []

        # Truly dangling path still fails
        t2.set_reference_value("BrokenRef", "/ActiveEcuC/Os/NoSuchTask", "/MICROSAR/Os/OsTask/BrokenRef")
        assert len(ReferenceIntegrityRule().validate(None, cfg).messages) == 1
        assert len(DanglingReferenceRule().validate(None, cfg).messages) == 1

        # Cycle across /ActiveEcuC/... and /ActiveEcuC/ActiveEcuC/... is detected
        cycle_res = CircularDependencyRule().validate(None, cfg)
        assert not cycle_res.is_valid

        analyzer = ImpactAnalyzer()
        assert analyzer._normalize_path("/ActiveEcuC/Os/OsTask_0") == "Os.OsTask_0"
        assert analyzer._normalize_path("/ActiveEcuC/ActiveEcuC/Os/OsTask_0") == "Os.OsTask_0"


class TestGeneratorActiveEcuCSupport:
    def test_renderer_node_exists_refvalid_resolve_ref_and_alias(self):
        project, os_def, os_mgr, _, _, com_def, com_mgr, _, _ = _build_os_and_com_project(
            os_config_short_name="Os_Core0"
        )

        renderer = Renderer()
        renderer.load_module(os_def, os_mgr.configuration)
        renderer.load_module(com_def, com_mgr.configuration)

        # Alias must not pollute get_all_modules(), while resolving via symbol_table
        assert set(renderer.symbol_table.get_all_modules()) == {"os", "com"}
        assert renderer.symbol_table.get_module("Os_Core0") is not None

        assert renderer.render("[!IF \"node:exists('/ActiveEcuC/Os/OsTask_0')\"!]OK[!ENDIF!]", module_name="Com") == "OK"
        assert renderer.render("[!IF \"node:exists('/ActiveEcuC/Os_Core0/OsTask_0')\"!]OK[!ENDIF!]", module_name="Com") == "OK"
        assert renderer.render("[!IF \"node:exists('/ActiveEcuC/Os/OsTask_0/OsTaskAutostart_0/OsTaskAppMode')\"!]OK[!ENDIF!]", module_name="Com") == "OK"
        assert renderer.render("[!IF \"node:exists(node:value('/Com/ComConfig/ComIPdu_0/ComTaskRef'))\"!]OK[!ENDIF!]", module_name="Com") == "OK"
        assert renderer.render("[!\"node:refvalid('/ActiveEcuC/Os/OsTask_0')\"!]", module_name="Com") == "true"
        assert renderer.render("[!\"node:refvalid(node:value('/Com/ComConfig/ComIPdu_0/ComTaskRef'))\"!]", module_name="Com") == "true"
        assert renderer.render("[!\"node:refvalid('/ActiveEcuC/Os/DoesNotExist')\"!]", module_name="Com") == "false"

        # CodeGenerator.resolve_ref must not leak ActiveEcuC_ into C identifiers
        gen = CodeGenerator(com_def, com_mgr.configuration)
        assert gen.resolve_ref("/ActiveEcuC/Os/OsTask_0") == "Os_OsTask_0"
        assert gen.resolve_ref("/ActiveEcuC/ActiveEcuC/Os/OsTask_0") == "Os_OsTask_0"
        assert gen.resolve_ref("/Config/Os/OsTask_0") == "Os_OsTask_0"


class TestUIActiveEcuCBypassFixes:
    def test_dependency_graph_analyze_strips_active_ecuc_single_and_multi(self):
        project, _, _, task0, _, _, com_mgr, _, ipdu0 = _build_os_and_com_project()
        ipdu0.add_multi_reference_value(
            "ExtraTasks",
            "/ActiveEcuC/ActiveEcuC/Os/OsTask_0",
            "/MICROSAR/Com/ComConfig/ComIPdu/ExtraTasks",
            0,
        )

        class _GraphStub:
            _analyze_container_deps = DependencyGraphWidget._analyze_container_deps

        # Do NOT call resolve_all_references first to verify string fallback too
        deps = {}
        widget_stub = _GraphStub()
        widget_stub._analyze_container_deps(
            com_mgr.configuration.containers[0],
            deps,
            "Com",
            prefix="Com",
        )
        ipdu_deps = deps["Com/ComConfig/ComIPdu_0"]
        assert ("Os/OsTask_0", "ComTaskRef") in ipdu_deps
        assert ("Os/OsTask_0", "ExtraTasks") in ipdu_deps

        # Also verify resolved pointer branch
        project.resolve_all_references(force=True)
        deps_resolved = {}
        widget_stub._analyze_container_deps(
            com_mgr.configuration.containers[0],
            deps_resolved,
            "Com",
            prefix="Com",
        )
        assert deps_resolved["Com/ComConfig/ComIPdu_0"] == [
            ("Os/OsTask_0", "ComTaskRef"),
            ("Os/OsTask_0", "ExtraTasks"),
        ]

    def test_navigation_controller_jump_failure_and_multi_ref_owner_lookup(self):
        win = MagicMock()
        target_proxy = EcucContainerValue("Os", "/MICROSAR/Os")
        target_proxy._is_module_root_proxy = True
        win.current_project.get_instance_by_path.return_value = target_proxy
        win.tree_view.select_container.return_value = False
        ctrl = NavigationController(win)

        ctrl._on_reference_jump_requested("/ActiveEcuC/Os")
        win.statusbar.showMessage.assert_called_with("Could not find: /ActiveEcuC/Os", 3000)

        win.tree_view.select_container.return_value = True
        ctrl._on_reference_jump_requested("/ActiveEcuC/Os")
        win.statusbar.showMessage.assert_called_with("Navigated to: /ActiveEcuC/Os", 3000)

        # Multi-valued reference lookup in _search_for_ref_in_containers
        multi_ref = EcucReferenceValue("/Def/MultiRef", "/ActiveEcuC/Os/OsTask_0", index=0)
        holder = EcucContainerValue("Holder", "/Com/Holder")
        holder.multi_reference_values["MultiRef"] = [multi_ref]
        other = EcucContainerValue("Other", "/Com/Other")
        assert ctrl._search_for_ref_in_containers(multi_ref, [other, holder]) is holder

    def test_tree_view_and_config_panel_handle_active_ecuc_and_module_root_proxy(self, qapp):
        from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel
        from autosar_configurator.ui.widgets.davinci_tree_view import DaVinciTreeView

        project, os_def, _, task0, _, com_def, com_mgr, _, ipdu0 = _build_os_and_com_project()
        ipdu0.set_reference_value(
            "OsModuleRoot",
            "/ActiveEcuC/Os",
            "/MICROSAR/Com/ComConfig/ComIPdu/OsModuleRoot",
            dest_type="ECUC-FOREIGN-REFERENCE-DEF",
        )
        project.resolve_all_references(force=True)

        tree = DaVinciTreeView()
        tree.set_project(project)

        # 1. select_item_by_path strips /ActiveEcuC/... and /ActiveEcuC/ActiveEcuC/...
        rem = tree.select_item_by_path("/ActiveEcuC/ActiveEcuC/Os/OsTask_0/OsTaskPriority")
        assert rem == "OsTaskPriority"
        assert tree.get_selected_instance() is task0

        # 2. select_container selects MODULE item for a module-root proxy
        proxy = project.get_instance_by_path("/ActiveEcuC/Os")
        assert tree.select_container(proxy) is True
        cur_data = tree.currentItem().data(0, 0x0100)  # Qt.UserRole
        assert cur_data["type"] == "MODULE"
        assert cur_data["def"] is os_def

        # 3. _create_reference_selector shows module-root resolved ref as non-error 📦 item
        panel = DaVinciConfigPanel()
        panel.project = project
        panel.config_manager = com_mgr
        mod_ref_def = EcucReferenceDef(
            "OsModuleRoot",
            definition_ref="/MICROSAR/Com/ComConfig/ComIPdu/OsModuleRoot",
            destination_ref="/AUTOSAR/EcucDefs/Os",
        )
        mod_ref_val = ipdu0.reference_values["OsModuleRoot"]
        combo = panel._create_reference_selector("OsModuleRoot", mod_ref_def, "/ActiveEcuC/Os", ref_val=mod_ref_val)
        assert combo.currentText().startswith("📦 ")
        assert combo.itemData(combo.currentIndex(), panel.UNRESOLVED_REF_ROLE) is not True

        # Deep /ActiveEcuC/ActiveEcuC/Os/OsTask_0 still selects /Os/OsTask_0 item directly
        task_ref_def = com_def.containers["ComConfig"].sub_containers["ComIPdu"].references["ComTaskRef"]
        task_combo = panel._create_reference_selector(
            "ComTaskRef",
            task_ref_def,
            "/ActiveEcuC/ActiveEcuC/Os/OsTask_0",
            ref_val=ipdu0.reference_values["ComTaskRef"],
        )
        assert task_combo.currentData() == "/Os/OsTask_0"

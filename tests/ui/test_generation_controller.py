"""Unit tests for GenerationController (P2-6 phase 6).

Exercise the mode-dispatch and config-collection logic with a stub window —
QMessageBox patched, no QApplication required.
"""
from types import SimpleNamespace
from unittest.mock import MagicMock, patch

from autosar_configurator.ui.controllers.generation_controller import (
    GenerationController, _template_sources)


def test_generate_code_dispatches_to_project_mode():
    win = MagicMock()
    win.current_project = MagicMock()
    ctrl = GenerationController(win)

    with patch.object(ctrl, "_generate_project_code") as proj, \
         patch.object(ctrl, "_generate_single_module_code") as single:
        ctrl.generate_code()
        proj.assert_called_once()
        single.assert_not_called()


def test_generate_code_dispatches_to_single_module():
    win = MagicMock()
    win.current_project = None
    win.config_manager = MagicMock()
    ctrl = GenerationController(win)

    with patch.object(ctrl, "_generate_project_code") as proj, \
         patch.object(ctrl, "_generate_single_module_code") as single:
        ctrl.generate_code()
        single.assert_called_once()
        proj.assert_not_called()


def test_generate_code_warns_without_configuration():
    win = MagicMock()
    win.current_project = None
    win.config_manager = None
    ctrl = GenerationController(win)

    with patch(
        "autosar_configurator.ui.controllers.generation_controller.QMessageBox"
    ) as mb:
        ctrl.generate_code()
        mb.warning.assert_called_once()


def test_get_all_project_configurations_collects_modules():
    mdef, cfg = object(), object()
    mgr = MagicMock()
    mgr.module_def = mdef
    mgr.configuration = cfg
    win = MagicMock()
    win.current_project.module_managers = {"Can": mgr}
    ctrl = GenerationController(win)

    result = ctrl._get_all_project_configurations()
    assert result == {"Can": (mdef, cfg)}


def test_get_all_project_configurations_empty_without_project():
    win = MagicMock()
    win.current_project = None
    ctrl = GenerationController(win)
    assert ctrl._get_all_project_configurations() == {}


def test_template_sources_project_without_path_is_safe():
    """A falsy ``project.path`` must not reach ``Path(None)`` (batch gen crashed)."""
    from autosar_configurator.core.project_paths import ProjectDirectories
    project = SimpleNamespace(path=None, format_version=8,
                              directories=ProjectDirectories.default_v8(), packages={})
    win = SimpleNamespace(current_project=project, current_project_file=None)
    assert _template_sources(win, "Dio") == (None, None, None)


def test_template_sources_eb_directory_project_passes_overlay_and_root(tmp_path):
    """EB project: ``path`` is the project dir, overlay comes from the project dir"""
    from autosar_configurator.core.project_paths import ProjectDirectories
    (tmp_path / "templates" / "Dio").mkdir(parents=True)
    project = SimpleNamespace(path=tmp_path, format_version=7,
                              directories=ProjectDirectories.legacy(), packages={})
    win = SimpleNamespace(current_project=project, current_project_file=None)

    overlay, package_dir, project_root = _template_sources(win, "Dio")
    assert overlay == tmp_path / "templates"
    assert package_dir is None
    assert project_root == tmp_path


def test_generate_single_module_passes_project_variants_and_default_variant(tmp_path):
    """_generate_single_module_code passes project.variants to CodeGenerator and defaults None to 'Default'."""
    from autosar_configurator.core.project_paths import ProjectDirectories

    captured = {}

    class _FakeGenerator:
        last_status = "ok"

        def __init__(self, *args, **kwargs):
            captured["init_kwargs"] = kwargs
            self.project_template_dir = None
            self.package_template_dir = None
            self.user_template_dir = None

        def generate_all(self, output_dir, **kwargs):
            captured["generate_all_kwargs"] = kwargs
            return True

    project = SimpleNamespace(
        active_variant=None,
        variants=["Default", "V1", "V2"],
        selected_chip=None,
        path=tmp_path / "Proj.dpa",
        format_version=8,
        directories=ProjectDirectories.default_v8(),
        packages={},
        module_managers={},
        load_ecu_resources=lambda: {},
    )
    cfg = SimpleNamespace(short_name="Can", variant_overrides={})
    win = SimpleNamespace(
        current_project=project,
        current_project_file=None,
        module_def=object(),
        config_manager=SimpleNamespace(configuration=cfg),
        statusbar=SimpleNamespace(showMessage=lambda *_a, **_kw: None),
    )

    with patch("autosar_configurator.ui.controllers.generation_controller.QFileDialog.getExistingDirectory",
               return_value=str(tmp_path / "out")), \
         patch("autosar_configurator.ui.controllers.generation_controller.QMessageBox"), \
         patch("autosar_configurator.generator.generator.CodeGenerator", _FakeGenerator):
        GenerationController(win)._generate_single_module_code()

    assert captured["init_kwargs"]["project_variants"] == ["Default", "V1", "V2"]
    assert captured["generate_all_kwargs"]["variant"] == "Default"


def test_generate_project_code_worker_passes_project_variants_and_override_layer(tmp_path):
    """_generate_project_code passes project.variants into GenWorker -> CodeGenerator and keeps variant_overrides."""
    from autosar_configurator.core.project_paths import ProjectDirectories

    captured = {}

    class _FakeGenerator:
        last_status = "ok"

        def __init__(self, *args, **kwargs):
            captured["init_kwargs"] = kwargs

        def generate_all(self, output_dir, **kwargs):
            captured["generate_all_kwargs"] = kwargs
            return True

    cfg = SimpleNamespace(
        short_name="Can",
        variant_overrides={"V1": {"CanGeneral/CanDevErrorDetect": True}},
    )
    mgr = SimpleNamespace(module_def=object(), configuration=cfg)
    project = SimpleNamespace(
        active_variant="V1",
        variants=["Default", "V1"],
        selected_chip=None,
        path=tmp_path / "Proj.dpa",
        format_version=8,
        directories=ProjectDirectories.default_v8(),
        packages={},
        module_managers={"Can": mgr},
        load_ecu_resources=lambda: {},
    )
    win = SimpleNamespace(
        current_project=project,
        current_project_file=None,
        thread_pool=SimpleNamespace(start=lambda worker: worker.run()),
        statusbar=SimpleNamespace(showMessage=lambda *_a, **_kw: None),
    )

    with patch("PySide6.QtWidgets.QProgressDialog"), \
         patch("autosar_configurator.ui.controllers.generation_controller.QMessageBox"), \
         patch("autosar_configurator.generator.generator.CodeGenerator", _FakeGenerator):
        GenerationController(win)._generate_project_code()

    assert captured["init_kwargs"]["project_variants"] == ["Default", "V1"]
    assert captured["init_kwargs"]["variant_name"] == "V1"
    assert captured["init_kwargs"]["variant_overrides"] == {"CanGeneral/CanDevErrorDetect": True}
    assert captured["generate_all_kwargs"]["variant"] == "V1"


def test_generate_single_module_rte_dispatches_model_driven_generator(tmp_path):
    from autosar_configurator.core.config_manager import ConfigurationManager
    from autosar_configurator.core.model.configuration_model import (
        EcucContainerValue,
        EcucModuleConfiguration,
    )
    from autosar_configurator.core.model.definition_model import EcucModuleDef
    from autosar_configurator.core.project_paths import ProjectDirectories
    from autosar_configurator.core.workspace_manager import WorkspaceProject
    from autosar_configurator.ui.controllers.generation_controller import GenerationController

    project_dir = tmp_path / "proj"
    project_dir.mkdir()
    project = WorkspaceProject(name="TestProj", path=project_dir / "TestProj.dpa", format_version=8)
    project.directories = ProjectDirectories.default_v8()

    rte_def = EcucModuleDef(short_name="Rte", definition_ref="/MICROSAR/Rte")
    rte_cfg = EcucModuleConfiguration(short_name="Rte", definition_ref="/MICROSAR/Rte")
    com_inst = EcucContainerValue(
        short_name="Com",
        definition_ref="/MICROSAR/Rte/RteBswModuleInstance",
    )
    com_inst.set_reference_value(
        "RteBswModuleConfigurationRef",
        "/ActiveEcuC/Com",
        "/MICROSAR/Rte/RteBswModuleInstance/RteBswModuleConfigurationRef",
    )
    rte_cfg.add_container(com_inst)
    com_def = EcucModuleDef(short_name="Com", definition_ref="/MICROSAR/Com")
    com_cfg = EcucModuleConfiguration(short_name="Com", definition_ref="/MICROSAR/Com")

    rte_mgr = ConfigurationManager(rte_def)
    rte_mgr.configuration = rte_cfg
    com_mgr = ConfigurationManager(com_def)
    com_mgr.configuration = com_cfg

    project.module_managers = {"Rte": rte_mgr, "Com": com_mgr}

    current_module_tree = SimpleNamespace(
        current_manager=rte_mgr,
        module_def=rte_def,
        configuration=rte_cfg,
    )
    win = SimpleNamespace(
        current_project=project,
        current_project_file=None,
        config_manager=rte_mgr,
        module_def=rte_def,
        module_trees={"Rte": current_module_tree, "Com": SimpleNamespace()},
        tab_widget=SimpleNamespace(currentWidget=lambda: current_module_tree),
        statusbar=SimpleNamespace(showMessage=lambda *_a, **_kw: None),
        project_dir=project_dir,
    )

    with patch(
        "autosar_configurator.ui.controllers.generation_controller.QFileDialog.getExistingDirectory",
        return_value=str(project_dir / "gen"),
    ), patch("autosar_configurator.ui.controllers.generation_controller.QMessageBox") as mock_msg:
        GenerationController(win)._generate_single_module_code()

    assert mock_msg.information.called
    gen_inc = project_dir / "gen" / "Rte" / "include"
    assert (gen_inc / "Rte.h").exists()
    assert (gen_inc / "Rte_Cfg.h").exists()
    assert (gen_inc / "Rte_Main.h").exists()
    assert (gen_inc / "Rte_Type.h").exists()
    assert (gen_inc / "Rte_UserTypes.h").exists()
    assert (gen_inc / "SchM_Com.h").exists()
    assert (gen_inc / "SchM_Com_Type.h").exists()


def test_generate_project_code_rte_overlay_overrides_synthesized_schm_and_cfg(tmp_path):
    from autosar_configurator.core.config_manager import ConfigurationManager
    from autosar_configurator.core.model.configuration_model import (
        EcucContainerValue,
        EcucModuleConfiguration,
    )
    from autosar_configurator.core.model.definition_model import EcucModuleDef
    from autosar_configurator.core.project_paths import ProjectDirectories
    from autosar_configurator.core.workspace_manager import WorkspaceProject
    from autosar_configurator.ui.controllers.generation_controller import GenerationController

    project_dir = tmp_path / "proj_overlay"
    overlay_inc = project_dir / "templates" / "Rte" / "include"
    overlay_inc.mkdir(parents=True)
    (overlay_inc / "SchM_Com.h").write_text("/* custom SchM_Com overlay */\n", encoding="utf-8")
    (overlay_inc / "Rte_Cfg.h").write_text("/* custom Rte_Cfg overlay */\n", encoding="utf-8")
    com_inc = project_dir / "templates" / "Com" / "include"
    com_inc.mkdir(parents=True)
    (com_inc / "Com_Cfg.h").write_text("/* minimal Com template */\n", encoding="utf-8")

    project = WorkspaceProject(name="TestOverlay", path=project_dir / "TestOverlay.dpa", format_version=8)
    project.directories = ProjectDirectories.from_dict(
        {"gen_layout": "flat"},
        ProjectDirectories.default_v8(),
    )

    rte_def = EcucModuleDef(short_name="Rte", definition_ref="/MICROSAR/Rte")
    rte_cfg = EcucModuleConfiguration(short_name="Rte", definition_ref="/MICROSAR/Rte")
    com_inst = EcucContainerValue(
        short_name="Com",
        definition_ref="/MICROSAR/Rte/RteBswModuleInstance",
    )
    com_inst.set_reference_value(
        "RteBswModuleConfigurationRef",
        "/ActiveEcuC/Com",
        "/MICROSAR/Rte/RteBswModuleInstance/RteBswModuleConfigurationRef",
    )
    rte_cfg.add_container(com_inst)
    com_def = EcucModuleDef(short_name="Com", definition_ref="/MICROSAR/Com")
    com_cfg = EcucModuleConfiguration(short_name="Com", definition_ref="/MICROSAR/Com")

    rte_mgr = ConfigurationManager(rte_def)
    rte_mgr.configuration = rte_cfg
    com_mgr = ConfigurationManager(com_def)
    com_mgr.configuration = com_cfg

    project.module_managers = {"Rte": rte_mgr, "Com": com_mgr}

    win = SimpleNamespace(
        current_project=project,
        current_project_file=None,
        thread_pool=SimpleNamespace(start=lambda worker: worker.run()),
        statusbar=SimpleNamespace(showMessage=lambda *_a, **_kw: None),
    )

    with patch("PySide6.QtWidgets.QProgressDialog"), \
         patch("autosar_configurator.ui.controllers.generation_controller.QMessageBox") as mock_msg:
        GenerationController(win)._generate_project_code()

    gen_inc = project_dir / "gen" / "include"
    assert (gen_inc / "Rte.h").exists()
    assert "#ifndef RTE_H" in (gen_inc / "Rte.h").read_text(encoding="utf-8")
    assert (gen_inc / "Rte_Main.h").exists()
    assert (gen_inc / "Rte_Type.h").exists()
    assert (gen_inc / "Rte_UserTypes.h").exists()
    assert (gen_inc / "Com_Cfg.h").exists()
    assert (gen_inc / "SchM_Com_Type.h").exists()
    assert (gen_inc / "SchM_Com.h").read_text(encoding="utf-8") == "/* custom SchM_Com overlay */\n"
    assert (gen_inc / "Rte_Cfg.h").read_text(encoding="utf-8") == "/* custom Rte_Cfg overlay */\n"
    assert not mock_msg.critical.called


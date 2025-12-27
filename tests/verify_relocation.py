import os
import sys
import json
import shutil
import logging
from pathlib import Path

# Add project root to sys.path
sys.path.append(os.getcwd())

from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType
from autosar_configurator.core.workspace_manager import WorkspaceManager
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.generator.generator import CodeGenerator

# Setup logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def test_relocation_and_generation():
    wm = WorkspaceManager()
    project_root = Path("test_project_relocation")
    if project_root.exists():
        shutil.rmtree(project_root)
    project_root.mkdir()
    
    project_file = project_root / "test.davinci"
    project = wm.create_project("TestRelocation", project_file)
    
    # 1. Add Mcu Module (using existing Def file)
    logger.info("Adding Mcu module...")
    mcu_def_path = Path("tests/test_data/Mcu_Def.arxml")
    parser = EcucDefParser()
    mcu_def = parser.parse_module_def_file(mcu_def_path)
    mcu_manager = project.add_module(mcu_def, mcu_def_path)
    
    # Setup some Mcu config
    clk_def = mcu_def.containers['McuClockConfig']
    clk_inst = mcu_manager.create_container_instance(clk_def, None, "McuClockConfig_0")
    src_def = clk_def.sub_containers['McuClockSource']
    src_inst = mcu_manager.create_container_instance(src_def, clk_inst, "McuClockSource_0")
    mcu_manager.set_parameter_value(src_inst, "McuClockFrequency", 160000000)
    mcu_manager.set_parameter_value(src_inst, "McuClockSourceType", "MCU_CLOCK_PLL")
    
    # 2. Add Port Module (using mock Def since Port_Def.arxml is missing)
    logger.info("Adding Port module (mock)...")
    port_def = EcucModuleDef("Port", definition_ref="/AUTOSAR/EcucDefs/Port")
    pin_def = EcucContainerDef("PortPin", definition_ref="/AUTOSAR/EcucDefs/Port/PortPin")
    pin_def.upper_multiplicity = -1
    pin_def.add_parameter(EcucParameterDef("PortPinId", EcucParameterType.INTEGER, definition_ref="/AUTOSAR/EcucDefs/Port/PortPin/PortPinId"))
    pin_def.add_parameter(EcucParameterDef("PortPinMode", EcucParameterType.ENUMERATION, definition_ref="/AUTOSAR/EcucDefs/Port/PortPin/PortPinMode", literals=["PORT_PIN_MODE_GPIO", "PORT_PIN_MODE_ADC"]))
    pin_def.add_parameter(EcucParameterDef("PortPinDirection", EcucParameterType.ENUMERATION, definition_ref="/AUTOSAR/EcucDefs/Port/PortPin/PortPinDirection", literals=["PORT_PIN_IN", "PORT_PIN_OUT"]))
    pin_def.add_parameter(EcucParameterDef("PortPinInitialMode", EcucParameterType.ENUMERATION, definition_ref="/AUTOSAR/EcucDefs/Port/PortPin/PortPinInitialMode", literals=["PORT_PIN_MODE_GPIO"]))
    port_def.add_container(pin_def)
    
    port_def_path = project_root / "Port_Def.arxml"
    # We don't actually need to save def for this test, just reference it
    port_manager = project.add_module(port_def, port_def_path)
    p1 = port_manager.create_container_instance(pin_def, None, "PortPin_0")
    port_manager.set_parameter_value(p1, "PortPinId", 10)
    port_manager.set_parameter_value(p1, "PortPinMode", "PORT_PIN_MODE_GPIO")
    
    # 3. Save Project and Verify Relocation
    logger.info("Saving project...")
    wm.save_project()
    
    config_value_dir = project_root / "ConfigValue"
    assert config_value_dir.exists(), "ConfigValue directory should be created"
    assert (config_value_dir / "Mcu_Config.arxml").exists(), "Mcu config should be in ConfigValue"
    assert (config_value_dir / "Port_Config.arxml").exists(), "Port config should be in ConfigValue"
    
    with open(project_file, 'r') as f:
        data = json.load(f)
        for m in data['modules']:
            assert "ConfigValue/" in m['config_path'], f"Module {m['name']} path should be relative to ConfigValue"
            
    # 4. Generate Code for all modules
    logger.info("Generating code...")
    gen_dir = project_root / "generateCode"
    for name, manager in project.module_managers.items():
        module_def = manager.module_def
        config = manager.configuration
        generator = CodeGenerator(module_def, config)
        generator.generate_all(gen_dir)
        
    assert (gen_dir / "Mcu/include/Mcu_Cfg.h").exists(), "Mcu_Cfg.h should be generated"
    assert (gen_dir / "Port/src/Port_Lcfg.c").exists(), "Port_Lcfg.c should be generated"
    
    logger.info("SUCCESS: Relocation and Multi-module generation verified!")

if __name__ == "__main__":
    test_relocation_and_generation()

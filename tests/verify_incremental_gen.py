import os
import sys
import logging
import shutil
from pathlib import Path

# Add project root to sys.path
sys.path.append(os.getcwd())

from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.generator.generator import CodeGenerator

# Setup logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)

def setup_mock_adc():
    module_def = EcucModuleDef("Adc", definition_ref="/AUTOSAR/EcucDefs/Adc")
    cd = EcucContainerDef("AdcGeneral", definition_ref="/AUTOSAR/EcucDefs/Adc/AdcGeneral")
    cd.add_parameter(EcucParameterDef("AdcDevErrorDetect", EcucParameterType.BOOLEAN, definition_ref="/AUTOSAR/EcucDefs/Adc/AdcGeneral/AdcDevErrorDetect"))
    module_def.add_container(cd)
    return module_def

def test_incremental():
    module_def = setup_mock_adc()
    config_manager = ConfigurationManager(module_def)
    config = config_manager.configuration
    
    # Create an instance
    gen_def = module_def.containers['AdcGeneral']
    gen_inst = config_manager.create_container_instance(gen_def, None, "AdcGeneral_0")
    config_manager.set_parameter_value(gen_inst, "AdcDevErrorDetect", True)
    
    output_dir = Path("output_test_incremental")
    if output_dir.exists():
        shutil.rmtree(output_dir)
    
    generator = CodeGenerator(module_def, config)
    
    # 1. First run - should generate
    logger.info("--- First Run ---")
    gen1 = generator.generate_all(output_dir)
    assert gen1 == True, "First run should generate files"
    
    # 2. Second run - no changes, should skip
    logger.info("--- Second Run (No Changes) ---")
    gen2 = generator.generate_all(output_dir)
    assert gen2 == False, "Second run should skip generation"
    
    # 3. Third run - modification, should generate
    logger.info("--- Third Run (Modification) ---")
    config_manager.set_parameter_value(gen_inst, "AdcDevErrorDetect", False)
    # We need a new generator or update config in current one
    # CodeGenerator holds reference to config, so it should see the change
    gen3 = generator.generate_all(output_dir)
    assert gen3 == True, "Third run after modification should generate files"
    
    # 4. Fourth run - force generation
    logger.info("--- Fourth Run (Force) ---")
    gen4 = generator.generate_all(output_dir, force=True)
    assert gen4 == True, "Fourth run with force=True should generate files even if no changes"
    
    logger.info("SUCCESS: Incremental generation logic verified!")

if __name__ == "__main__":
    test_incremental()

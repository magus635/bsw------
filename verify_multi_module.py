import os
import sys
import logging
from pathlib import Path

# Add project root to path
sys.path.append(os.getcwd())

from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.generator.generator import CodeGenerator

# Setup logging
logging.basicConfig(level=logging.DEBUG)
logger = logging.getLogger(__name__)

def create_crypto_def():
    module_def = EcucModuleDef("Crypto", definition_ref="/AUTOSAR/EcucDefs/Crypto")
    
    # CryptoKey container
    key_def = EcucContainerDef("CryptoKey", definition_ref="/AUTOSAR/EcucDefs/Crypto/CryptoKey")
    key_def.add_parameter(EcucParameterDef("CryptoKeyId", EcucParameterType.INTEGER, definition_ref="/AUTOSAR/EcucDefs/Crypto/CryptoKey/CryptoKeyId"))
    key_def.add_parameter(EcucParameterDef("CryptoKeyType", EcucParameterType.ENUMERATION, definition_ref="/AUTOSAR/EcucDefs/Crypto/CryptoKey/CryptoKeyType", 
                                        literals=["KEY_AES_128", "KEY_AES_256"]))
    
    # CryptoKeyElement sub-container
    elem_def = EcucContainerDef("CryptoKeyElement", definition_ref="/AUTOSAR/EcucDefs/Crypto/CryptoKey/CryptoKeyElement")
    elem_def.upper_multiplicity = -1
    elem_def.add_parameter(EcucParameterDef("CryptoKeyElementId", EcucParameterType.INTEGER, definition_ref="/AUTOSAR/EcucDefs/Crypto/CryptoKey/CryptoKeyElement/CryptoKeyElementId"))
    elem_def.add_parameter(EcucParameterDef("CryptoKeyElementSize", EcucParameterType.INTEGER, definition_ref="/AUTOSAR/EcucDefs/Crypto/CryptoKey/CryptoKeyElement/CryptoKeyElementSize"))
    
    key_def.add_sub_container(elem_def)
    module_def.add_container(key_def)
    
    return module_def

def create_dsadc_def():
    module_def = EcucModuleDef("Dsadc", definition_ref="/AUTOSAR/EcucDefs/Dsadc")
    
    # DsadcChannel container
    ch_def = EcucContainerDef("DsadcChannel", definition_ref="/AUTOSAR/EcucDefs/Dsadc/DsadcChannel")
    ch_def.add_parameter(EcucParameterDef("DsadcChannelId", EcucParameterType.INTEGER, definition_ref="/AUTOSAR/EcucDefs/Dsadc/DsadcChannel/DsadcChannelId"))
    ch_def.add_parameter(EcucParameterDef("DsadcModulatorClockDivider", EcucParameterType.INTEGER, definition_ref="/AUTOSAR/EcucDefs/Dsadc/DsadcChannel/DsadcModulatorClockDivider"))
    ch_def.add_parameter(EcucParameterDef("DsadcModulatorInputSelect", EcucParameterType.ENUMERATION, definition_ref="/AUTOSAR/EcucDefs/Dsadc/DsadcChannel/DsadcModulatorInputSelect",
                                        literals=["INPUT_A", "INPUT_B"]))
    ch_def.add_parameter(EcucParameterDef("DsadcFilterOverSamplingRate", EcucParameterType.INTEGER, definition_ref="/AUTOSAR/EcucDefs/Dsadc/DsadcChannel/DsadcFilterOverSamplingRate"))
    ch_def.add_parameter(EcucParameterDef("DsadcFilterCombFilterShift", EcucParameterType.INTEGER, definition_ref="/AUTOSAR/EcucDefs/Dsadc/DsadcChannel/DsadcFilterCombFilterShift"))
    
    module_def.add_container(ch_def)
    return module_def

def verify_module(module_name, module_def, setup_config_fn):
    logger.info(f"--- Verifying {module_name} ---")
    config_manager = ConfigurationManager(module_def)
    config = config_manager.configuration
    
    setup_config_fn(config_manager, module_def, config)
    
    output_dir = Path(f"output_verify_{module_name.lower()}")
    generator = CodeGenerator(module_def, config)
    generator.generate_all(output_dir, force=True)
    
    logger.info(f"Generated files for {module_name} to {output_dir}")

def setup_crypto_config(config_manager, module_def, config):
    key_def = module_def.containers['CryptoKey']
    key_inst = config_manager.create_container_instance(key_def, None, "MyKey_0")
    config_manager.set_parameter_value(key_inst, "CryptoKeyId", 1)
    config_manager.set_parameter_value(key_inst, "CryptoKeyType", "KEY_AES_128")
    
    elem_def = key_def.sub_containers['CryptoKeyElement']
    e1 = config_manager.create_container_instance(elem_def, key_inst, "Element_0")
    config_manager.set_parameter_value(e1, "CryptoKeyElementId", 101)
    config_manager.set_parameter_value(e1, "CryptoKeyElementSize", 16)
    
    e2 = config_manager.create_container_instance(elem_def, key_inst, "Element_1")
    config_manager.set_parameter_value(e2, "CryptoKeyElementId", 102)
    config_manager.set_parameter_value(e2, "CryptoKeyElementSize", 32)

def setup_dsadc_config(config_manager, module_def, config):
    ch_def = module_def.containers['DsadcChannel']
    c1 = config_manager.create_container_instance(ch_def, None, "DsadcChannel_0")
    config_manager.set_parameter_value(c1, "DsadcChannelId", 0)
    config_manager.set_parameter_value(c1, "DsadcModulatorClockDivider", 4)
    config_manager.set_parameter_value(c1, "DsadcModulatorInputSelect", "INPUT_A")
    config_manager.set_parameter_value(c1, "DsadcFilterOverSamplingRate", 64)
    config_manager.set_parameter_value(c1, "DsadcFilterCombFilterShift", 2)

if __name__ == "__main__":
    verify_module("Crypto", create_crypto_def(), setup_crypto_config)
    verify_module("Dsadc", create_dsadc_def(), setup_dsadc_config)

import sys
import os
import logging
from pathlib import Path

# Setup logging
logging.basicConfig(level=logging.INFO, format='%(levelname)s: %(message)s')
logger = logging.getLogger(__name__)

# Add current directory to sys.path
sys.path.insert(0, str(Path(__file__).parent))

try:
    from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType
    from autosar_configurator.core.config_manager import ConfigurationManager
    from autosar_configurator.generator.generator import CodeGenerator
except ImportError as e:
    logger.error(f"Import error: {e}")
    sys.exit(1)

def setup_mock_crypto():
    # 1. Create Module Definition
    crypto_def = EcucModuleDef("Crypto")
    crypto_def.definition_ref = "/AUTOSAR/EcucDefs/Crypto"
    
    # Driver Objects
    driver_obj_def = EcucContainerDef("CryptoDriverObject")
    driver_obj_def.definition_ref = "/AUTOSAR/EcucDefs/Crypto/CryptoDriverObject"
    driver_obj_def.upper_multiplicity = -1
    
    # Key
    key_def = EcucContainerDef("CryptoKey")
    key_def.definition_ref = "/AUTOSAR/EcucDefs/Crypto/CryptoDriverObject/CryptoKey"
    key_def.upper_multiplicity = -1
    key_id_def = EcucParameterDef("CryptoKeyId", EcucParameterType.INTEGER)
    key_id_def.definition_ref = "/AUTOSAR/EcucDefs/Crypto/CryptoDriverObject/CryptoKey/CryptoKeyId"
    key_def.parameters["CryptoKeyId"] = key_id_def
    
    # Key Element
    element_def = EcucContainerDef("CryptoKeyElement")
    element_def.definition_ref = "/AUTOSAR/EcucDefs/Crypto/CryptoDriverObject/CryptoKey/CryptoKeyElement"
    element_def.upper_multiplicity = -1
    element_id_def = EcucParameterDef("CryptoKeyElementId", EcucParameterType.INTEGER)
    element_id_def.definition_ref = "/AUTOSAR/EcucDefs/Crypto/CryptoDriverObject/CryptoKey/CryptoKeyElement/CryptoKeyElementId"
    element_size_def = EcucParameterDef("CryptoKeyElementSize", EcucParameterType.INTEGER)
    element_size_def.definition_ref = "/AUTOSAR/EcucDefs/Crypto/CryptoDriverObject/CryptoKey/CryptoKeyElement/CryptoKeyElementSize"
    element_format_def = EcucParameterDef("CryptoKeyElementFormat", EcucParameterType.ENUMERATION)
    element_format_def.definition_ref = "/AUTOSAR/EcucDefs/Crypto/CryptoDriverObject/CryptoKey/CryptoKeyElement/CryptoKeyElementFormat"
    element_format_def.literals = ["HEX", "BINARY"]
    
    element_def.parameters["CryptoKeyElementId"] = element_id_def
    element_def.parameters["CryptoKeyElementSize"] = element_size_def
    element_def.parameters["CryptoKeyElementFormat"] = element_format_def
    
    key_def.sub_containers["CryptoKeyElement"] = element_def
    driver_obj_def.sub_containers["CryptoKey"] = key_def
    crypto_def.containers["CryptoDriverObject"] = driver_obj_def
    
    # 2. Create Configuration
    config_manager = ConfigurationManager(crypto_def)
    
    # Instance 1: DriverObject_0
    do0 = config_manager.create_container_instance(driver_obj_def, None, "DriverObject_0")
    
    # Key_0
    k0 = config_manager.create_container_instance(key_def, do0, "Key_0")
    config_manager.set_parameter_value(k0, "CryptoKeyId", 1)
    
    # Element_0
    e0 = config_manager.create_container_instance(element_def, k0, "Element_0")
    config_manager.set_parameter_value(e0, "CryptoKeyElementId", 100)
    config_manager.set_parameter_value(e0, "CryptoKeyElementSize", 32)
    config_manager.set_parameter_value(e0, "CryptoKeyElementFormat", "HEX")
    
    # Element_1
    e1 = config_manager.create_container_instance(element_def, k0, "Element_1")
    config_manager.set_parameter_value(e1, "CryptoKeyElementId", 101)
    config_manager.set_parameter_value(e1, "CryptoKeyElementSize", 64)
    # No format for e1
    
    return crypto_def, config_manager.configuration

def main():
    module_def, configuration = setup_mock_crypto()
    
    template_dir = Path("test_project_relocation/templates")
    output_dir = Path("output_crypto_eb")
    output_dir.mkdir(exist_ok=True)
    
    logger.info("Running CodeGenerator for Crypto with EB Template...")
    generator = CodeGenerator(module_def, configuration, project_template_dir=template_dir)
    
    # Generate based on the newly created EB template
    # Note: Generator will find Crypto_EB_Lcfg.c.tpl and output it as Crypto_EB_Lcfg.c
    success = generator.generate_all(output_dir, force=True)
    
    if success:
        gen_file = output_dir / "Crypto" / "src" / "Crypto_EB_Lcfg.c"
        if gen_file.exists():
            content = gen_file.read_text()
            logger.info(f"Generated Content:\n{content}")
            
            # Simple checks
            if "DriverObject_0" in content and "KeyId = 1" in content and "ElementId = 100" in content:
                logger.info("✅ EB Template rendering verified for Crypto!")
            else:
                logger.error("❌ EB Template rendering failed verification.")
        else:
            logger.error(f"❌ Result file not found: {gen_file}")
    else:
        logger.error("❌ Generation failed.")

if __name__ == "__main__":
    main()

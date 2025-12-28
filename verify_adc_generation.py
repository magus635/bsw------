import sys
import os
import logging
from pathlib import Path

# Setup logging to see our debug messages
logging.basicConfig(level=logging.DEBUG, format='%(levelname)s: %(message)s')
logger = logging.getLogger(__name__)

# Add current directory to sys.path
sys.path.insert(0, str(Path(__file__).parent))

try:
    from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
    from autosar_configurator.core.config_manager import ConfigurationManager
    from autosar_configurator.generator.generator import CodeGenerator
    from autosar_configurator.core.model.definition_model import EcucParameterType
except ImportError as e:
    logger.error(f"Import error: {e}")
    sys.exit(1)

def main():
    def_file = Path("Adc_THA6206_LFBGA292.arxml")
    if not def_file.exists():
        logger.error(f"DEF file not found: {def_file}")
        return

    # 1. Parse DEF
    logger.info("Parsing module definition...")
    parser = EcucDefParser()
    module_def = parser.parse_module_def_file(def_file)
    logger.info(f"Parsed module: {module_def.short_name}")

    # 2. Create Config
    logger.info("Creating configuration...")
    config_manager = ConfigurationManager(module_def)
    
    # Add a container instance for testing Lcfg.c
    if 'AdcConfigSet' in module_def.containers:
        cd = module_def.containers['AdcConfigSet']
        inst = config_manager.create_container_instance(cd, None, "AdcConfig_0")
        
        # Add AdcHwUnit
        if 'AdcHwUnit' in cd.sub_containers:
            hwd = cd.sub_containers['AdcHwUnit']
            hw_inst = config_manager.create_container_instance(hwd, inst, "AdcHwUnit_0")
            if 'AdcHwUnitId' in hwd.parameters:
                config_manager.set_parameter_value(hw_inst, 'AdcHwUnitId', 'SARADC0')
                
            # Add AdcChannel under AdcHwUnit
            if 'AdcChannel' in hwd.sub_containers:
                scd = hwd.sub_containers['AdcChannel']
                sinst = config_manager.create_container_instance(scd, hw_inst, "AdcChannel_0")
                if 'AdcChannelId' in scd.parameters:
                    config_manager.set_parameter_value(sinst, 'AdcChannelId', 0)

    # 3. Generate Code
    logger.info("Generating code...")
    output_dir = Path("output_verify")
    output_dir.mkdir(exist_ok=True)
    
    project_templ_dir = Path("test_project_relocation/templates")
    generator = CodeGenerator(module_def, config_manager.configuration, project_template_dir=project_templ_dir)
    
    # Test enum extraction manually first
    enums = generator._get_enums()
    logger.info(f"Extracted {len(enums)} enums")
    for e in enums:
        logger.info(f"Enum: {e['name']} with {len(e['literals'])} literals")

    # Run generation
    generator.generate_all(output_dir, force=True)
    
    # Check output
    cfg_h = output_dir / "Adc" / "include" / "Adc_Cfg.h"
    lcfg_c = output_dir / "Adc" / "src" / "Adc_Lcfg.c"
    pbcfg_c = output_dir / "Adc" / "src" / "Adc_PBcfg.c"
    
    if cfg_h.exists():
        logger.info(f"Adc_Cfg.h generated. Size: {cfg_h.stat().st_size}")
        # Check if it uses the custom template (e.g. contains "Adc General Configuration")
        content = cfg_h.read_text()
        if "Adc General Configuration" in content:
            logger.info("Adc_Cfg.h uses custom template")
        else:
            logger.warning("Adc_Cfg.h uses default template")
    else:
        logger.error("Adc_Cfg.h NOT generated")

    if lcfg_c.exists():
        logger.info(f"Adc_Lcfg.c generated. Size: {lcfg_c.stat().st_size}")
    else:
        logger.error("Adc_Lcfg.c NOT generated")

    if pbcfg_c.exists():
        logger.info(f"Adc_PBcfg.c generated. Size: {pbcfg_c.stat().st_size}")
    else:
        logger.error("Adc_PBcfg.c NOT generated")

if __name__ == "__main__":
    main()

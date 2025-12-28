import sys
import os
import logging
from pathlib import Path

# Setup logging
logging.basicConfig(level=logging.DEBUG, format='%(levelname)s: %(message)s')
logger = logging.getLogger(__name__)

# Add current directory to sys.path
sys.path.insert(0, str(Path(__file__).parent))

try:
    from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
    from autosar_configurator.core.config_manager import ConfigurationManager
    from autosar_configurator.generator.generator import CodeGenerator
except ImportError as e:
    logger.error(f"Import error: {e}")
    sys.exit(1)

def main():
    # 1. Setup Mock Module
    def_file = Path("Adc_THA6206_LFBGA292.arxml")
    parser = EcucDefParser()
    module_def = parser.parse_module_def_file(def_file)
    config_manager = ConfigurationManager(module_def)
    
    # Add some data for looping
    if 'AdcConfigSet' in module_def.containers:
        cd = module_def.containers['AdcConfigSet']
        inst = config_manager.create_container_instance(cd, None, "AdcConfig_0")
        if 'AdcHwUnit' in cd.sub_containers:
            hwd = cd.sub_containers['AdcHwUnit']
            config_manager.create_container_instance(hwd, inst, "HW_0")
            config_manager.create_container_instance(hwd, inst, "HW_1")

    output_dir = Path("output_eb_verify")
    output_dir.mkdir(exist_ok=True)
    
    # 2. Create EB-style template
    template_dir = Path("eb_test_templates/Adc")
    template_dir.mkdir(parents=True, exist_ok=True)
    
    eb_template = """/**
 * @file Adc_EB_Test.h
 * EB Syntax Test
 */
[!VAR "TotalHW"="0"!]
[!LOOP "AdcConfigSet/AdcHwUnit"!][!//!]
    [!VAR "TotalHW"="$TotalHW + 1"!]
    #define ADC_HW_UNIT_[!"node:name(.)"!]    [!"node:value(./AdcHwUnitId)"!]
[!ENDLOOP!]

#define ADC_TOTAL_HW_UNITS    [!"$TotalHW"!]
"""
    with open(template_dir / "Adc_EB_Test.h.tpl", "w") as f:
        f.write(eb_template)

    # 3. Create Standard-style template for comparison
    std_template = """/**
 * Standard Syntax Test
 */
#define MODULE_NAME    {{ module_name }}
"""
    with open(template_dir / "Adc_Std_Test.h.tpl", "w") as f:
        f.write(std_template)

    # 4. Run Generation
    logger.info("Running dual-engine generation...")
    generator = CodeGenerator(module_def, config_manager.configuration, project_template_dir=Path("eb_test_templates"))
    generator.generate_all(output_dir, force=True)

    # 5. Verify Outputs
    eb_out = output_dir / "Adc" / "include" / "Adc_EB_Test.h"
    std_out = output_dir / "Adc" / "include" / "Adc_Std_Test.h"

    if eb_out.exists():
        content = eb_out.read_text()
        logger.info(f"EB Output generated:\n{content}")
        if "ADC_TOTAL_HW_UNITS    2" in content:
            logger.info("✅ EB Syntax Logic Verified (Loop + Var + node:name)")
        else:
            logger.error("❌ EB Syntax Logic Failed")
    else:
        logger.error("❌ EB Output NOT generated")

    if std_out.exists():
        content = std_out.read_text()
        logger.info(f"Std Output generated:\n{content}")
        if "#define MODULE_NAME    Adc" in content:
            logger.info("✅ Standard Syntax Logic Verified")
        else:
            logger.error("❌ Standard Syntax Logic Failed")
    else:
        logger.error("❌ Std Output NOT generated")

if __name__ == "__main__":
    main()

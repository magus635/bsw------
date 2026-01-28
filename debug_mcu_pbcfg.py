
import logging
import sys
from pathlib import Path

# Setup logging
logging.basicConfig(level=logging.DEBUG, format='%(levelname)s: %(message)s')
logger = logging.getLogger(__name__)

# Add the project root to sys.path
sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.generator.generator import CodeGenerator

def debug_mcu():
    # Paths
    project_root = Path("/Users/qlwang/Desktop/project/t5")
    mcu_arxml = project_root / "ConfigValue" / "Mcu_Config.arxml"
    mcu_def_arxml = Path("/Users/qlwang/Desktop/bsw图形配置工具/autosar_configurator/resources/EcucDefs_Mcu.arxml")
    template_dir = project_root / "templates"
    
    # 1. Parse Definition
    print("Parsing Mcu Definition...")
    def_parser = EcucDefParser()
    module_defs = def_parser.parse(str(mcu_def_arxml))
    mcu_def = module_defs.get('Mcu')
    
    # 2. Use ConfigurationManager to load ARXML
    print("Loading Mcu Configuration using ConfigurationManager...")
    manager = ConfigurationManager(mcu_def)
    manager.load_configuration(mcu_arxml)
    mcu_config = manager.configuration

    if not mcu_config:
        print("Error: Mcu configuration result is empty")
        return

    # 3. Initialize Generator
    print("Initializing Generator...")
    generator = CodeGenerator(
        module_def=mcu_def,
        configuration=mcu_config,
        project_template_dir=template_dir
    )

    # 4. Debug template info
    print("\nTemplate Info:")
    info = generator.get_template_info('Mcu')
    for item in info:
        print(f"  Type: {item['type']}, Engine: {item['engine']}, Path: {item['path']}")

    # 5. Extract context and check variables
    context = generator._prepare_context()
    print("\nContext Keys:", context.keys())
    
    # Check for GTM containers
    gtm_containers = [c for c in mcu_config.containers if 'GtmConfiguration' in c.definition_ref]
    print(f"Found {len(gtm_containers)} GtmConfiguration containers")
    if gtm_containers:
        print(f"Gtm short name: {gtm_containers[0].short_name}")
        # Verify subcontainers (Tom, etc.)
        tom_count = len([sc for sc in gtm_containers[0].sub_containers if 'Tom' in sc.definition_ref])
        print(f"Found {tom_count} Tom containers")

    # 6. Attempt a dry run of Mcu_PBcfg.c
    print("\n--- Dry Run: Mcu_PBcfg.c ---")
    try:
        # Load from Mcu/src/Mcu_PBcfg.c
        template_content, source_dir = generator._load_template_with_path("PBcfg.c", "Mcu")

        if template_content:
            print(f"Loaded template from: {source_dir}")
            from autosar_configurator.generator.eb_template_engine import EBTemplateEngine
            # Render using the EB engine
            eb_engine = EBTemplateEngine(strict=False, template_dir=source_dir)
            rendered = eb_engine.render(template_content, context)
            
            print("\nRendered Output Length:", len(rendered))
            print("\nFirst 500 chars of output:")
            print(rendered[:500])
            print("\nLast 500 chars of output:")
            print(rendered[-500:])
        else:
            print("Error: Could not find Mcu_PBcfg.c template")

    except Exception as e:
        print(f"\nCRITICAL ERROR during rendering: {e}")
        import traceback
        traceback.print_exc()

if __name__ == "__main__":
    debug_mcu()

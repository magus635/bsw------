import os
import sys
from pathlib import Path

# Add the project root to sys.path
root_dir = "/Users/qlwang/Desktop/bsw图形配置工具"
if root_dir not in sys.path:
    sys.path.insert(0, root_dir)

from autosar_configurator.generator.eb_template_engine import EBTemplateEngine
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.parser.arxml_parser import ArxmlParser

def load_module(engine, module_name, def_path, cfg_path):
    print(f"[DEBUG] load_module: Loading module '{module_name}'")
    if not Path(def_path).exists():
        print(f"[DEBUG] load_module: Definition file NOT FOUND: {def_path}")
        return
    if not Path(cfg_path).exists():
        print(f"[DEBUG] load_module: Configuration file NOT FOUND: {cfg_path}")
        return

    def_parser = EcucDefParser()
    module_def = def_parser.parse_module_def_file(Path(def_path))
    
    # ArxmlParser constructor doesn't take module_def
    ar_parser = ArxmlParser()
    # It seems parse_file returns the configuration
    configuration = ar_parser.parse_file(Path(cfg_path))
    
    engine.add_module(module_name, module_def, configuration)

def main():
    print("--- Running verification for Sent ---")
    engine = EBTemplateEngine(strict=False)
    
    # Path setup
    eclipse_base = Path("/Users/qlwang/Desktop/eclipse")
    project_base = Path("/Users/qlwang/Desktop/project/t5")
    
    # Load Resource module (needed for core allocation)
    res_def_file = eclipse_base / "Resource_THA6_AS440/autosar/Resource_THA6206_LFBGA292.arxml"
    res_cfg_file = project_base / "ConfigValue/Resource_Config.arxml"
    load_module(engine, "Resource", res_def_file, res_cfg_file)
    
    # Load Sent module
    sent_def_file = eclipse_base / "Sent_THA6_AS440/autosar/Sent_THA6206_LFBGA292.arxml"
    sent_cfg_file = project_base / "ConfigValue/Sent_Config.arxml"
    load_module(engine, "Sent", sent_def_file, sent_cfg_file)
    
    # Generate Sent files
    template_dir = project_base / "templates" / "Sent"
    output_dir = project_base / "output_verify"
    output_dir.mkdir(exist_ok=True)
    
    # Generate include/Sent_Cfg.h
    cfg_h_tpl = template_dir / "include" / "Sent_Cfg.h"
    cfg_h_path = output_dir / "Sent" / "include" / "Sent_Cfg.h"
    cfg_h_path.parent.mkdir(parents=True, exist_ok=True)
    
    if cfg_h_tpl.exists():
        print(f"Generating {cfg_h_path}...")
        engine.generate(cfg_h_tpl, cfg_h_path)
        
        content = cfg_h_path.read_text()
        print(f"\n--- {cfg_h_path.name} Preview ---")
        for line in content.splitlines():
            if any(x in line for x in ["SENT_CFG_AR_RELEASE", "SENT_CFG_SW", "SENT_MAX_CHANNELS_CONFIGURED", "SENT_DEV_ERROR_DETECT", "SENT_SAFETY_ENABLE"]):
                print(line)

        if "(NoneU)" in content:
            print("❌ ERROR: (NoneU) still exists in Sent_Cfg.h")
        else:
            print("✅ SUCCESS: No (NoneU) found in Sent_Cfg.h")
            
        if "#define SENT_DEV_ERROR_DETECT  (STD_ON)" in content or "#define SENT_DEV_ERROR_DETECT  (STD_OFF)" in content:
            print("✅ SUCCESS: Macro spacing looks correct")

    # Generate src/Sent_PBcfg.c
    pb_c_tpl = template_dir / "src" / "Sent_PBcfg.c"
    pb_c_path = output_dir / "Sent" / "src" / "Sent_PBcfg.c"
    pb_c_path.parent.mkdir(parents=True, exist_ok=True)
    
    if pb_c_tpl.exists():
        print(f"Generating {pb_c_path}...")
        engine.generate(pb_c_tpl, pb_c_path)
        
        content = pb_c_path.read_text()
        print(f"\n--- {pb_c_path.name} Preview ---")
        lines = content.splitlines()
        for i, line in enumerate(lines):
            if "Sent_ChannelConfigType" in line and "[" in line:
                print(line)
                if "[0]" in line:
                    print("❌ ERROR: Zero-sized array found in Sent_PBcfg.c")
                else:
                    print("✅ SUCCESS: Sent_ChannelConfigType array size is non-zero")
            
            if "Sent_HwChannelIdxMap" in line:
                 print(line)
                 if "[0]" in line:
                    print("❌ ERROR: Zero-sized array found for Sent_HwChannelIdxMap")

        if "CORE2" in content or "CORE3" in content:
             print("⚠️ WARNING: References to CORE2/3 found (check if they exist on this target)")

if __name__ == "__main__":
    main()

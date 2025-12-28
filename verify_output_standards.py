import os
import shutil
from pathlib import Path
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType, ConfigClass
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from autosar_configurator.generator.generator import CodeGenerator

def setup_dummy_module():
    # 1. Create Module Definition
    module_def = EcucModuleDef("TestModule", "/AUTOSAR/EcucDefs/TestModule")
    
    container_def = EcucContainerDef("TestContainer", "/AUTOSAR/EcucDefs/TestModule/TestContainer")
    
    # Pre-Compile Param
    p1 = EcucParameterDef("PreCompileParam", "/AUTOSAR/EcucDefs/TestModule/TestContainer/PreCompileParam", EcucParameterType.INTEGER)
    p1.config_class = ConfigClass.PRE_COMPILE
    container_def.parameters["PreCompileParam"] = p1
    
    # Link-Time Param
    p2 = EcucParameterDef("LinkTimeParam", "/AUTOSAR/EcucDefs/TestModule/TestContainer/LinkTimeParam", EcucParameterType.INTEGER)
    p2.config_class = ConfigClass.LINK_TIME
    container_def.parameters["LinkTimeParam"] = p2
    
    # Post-Build Param
    p3 = EcucParameterDef("PostBuildParam", "/AUTOSAR/EcucDefs/TestModule/TestContainer/PostBuildParam", EcucParameterType.INTEGER)
    p3.config_class = ConfigClass.POST_BUILD
    container_def.parameters["PostBuildParam"] = p3
    
    module_def.containers["TestContainer"] = container_def
    
    # 2. Create Configuration
    config = EcucModuleConfiguration("TestModule", "/AUTOSAR/EcucDefs/TestModule")
    container_val = EcucContainerValue("TestInstance", "/AUTOSAR/EcucDefs/TestModule/TestContainer")
    container_val.set_parameter_value("PreCompileParam", 100, p1.definition_ref)
    container_val.set_parameter_value("LinkTimeParam", 200, p2.definition_ref)
    container_val.set_parameter_value("PostBuildParam", 300, p3.definition_ref)
    config.add_container(container_val)
    
    return module_def, config

def verify():
    output_dir = Path("./verification_output")
    if output_dir.exists():
        shutil.rmtree(output_dir)
    output_dir.mkdir()
    
    module_def, config = setup_dummy_module()
    generator = CodeGenerator(module_def, config)
    generator.generate_all(output_dir)
    
    print("\n--- Verifying Output Standards ---")
    
    files = list(output_dir.glob("TestModule_*"))
    print(f"Generated files: {[f.name for f in files]}")
    
    expected_files = [
        Path("TestModule/include/TestModule_Cfg.h"),
        Path("TestModule/src/TestModule_Lcfg.c"),
        Path("TestModule/src/TestModule_PBcfg.c")
    ]
    for ef in expected_files:
        if (output_dir / ef).exists():
            print(f"✅ Found {ef}")
        else:
            print(f"❌ Missing {ef}")

    # Check for Std_Types.h in Cfg.h
    cfg_h = (output_dir / "TestModule/include/TestModule_Cfg.h").read_text()
    if '#include "Std_Types.h"' in cfg_h:
        print("✅ TestModule_Cfg.h includes Std_Types.h")
    else:
        print("❌ TestModule_Cfg.h missing Std_Types.h")
        
    if "#define TESTMODULE_PRECOMPILEPARAM    (100)" in cfg_h:
        print("✅ TestModule_Cfg.h contains Pre-Compile macro")

    # Check for MemMap in Lcfg.c
    lcfg_c = (output_dir / "TestModule/src/TestModule_Lcfg.c").read_text()
    if "START_SEC_CONFIG_DATA_UNSPECIFIED" in lcfg_c and "STOP_SEC_CONFIG_DATA_UNSPECIFIED" in lcfg_c:
        print("✅ TestModule_Lcfg.c contains MemMap segments")
    if "CONST(TestModule_ConfigType, TESTMODULE_CONST) TestModule_Config" in lcfg_c:
        print("✅ TestModule_Lcfg.c uses CONST macro")

    # Check for MemMap in PBcfg.c
    pbcfg_c = (output_dir / "TestModule/src/TestModule_PBcfg.c").read_text()
    if "START_SEC_CONFIG_DATA_POSTBUILD" in pbcfg_c and "STOP_SEC_CONFIG_DATA_POSTBUILD" in pbcfg_c:
        print("✅ TestModule_PBcfg.c contains Post-Build MemMap segments")

    print("\n--- Verification Complete ---")

if __name__ == "__main__":
    verify()

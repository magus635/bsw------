"""Comprehensive verification for complex EB Tresos templates and XPath expressions"""
from pathlib import Path
import logging
import tempfile
import shutil

logging.basicConfig(level=logging.INFO)

from autosar_configurator.generator.generator import CodeGenerator
from autosar_configurator.generator.eb_template_engine import EBTemplateEngine
from autosar_configurator.core.model.definition_model import EcucModuleDef
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration

# Setup mock objects
class MockParam:
    def __init__(self, name, value):
        self.short_name = name
        self.value = value
        self.node_type = 'parameter' 
    def get_value(self): return self.value

class MockContainer:
    def __init__(self, name, def_ref):
        self.short_name = name
        self.definition_ref = def_ref
        self.parameter_values = {}
        self.reference_values = {}
        self.sub_containers = []
        self.node_type = 'container'
    def get_child(self, name):
        if name in self.parameter_values: return self.parameter_values[name]
        for c in self.sub_containers:
            if c.short_name == name: return c
        return None
    def get_sub_containers(self): return self.sub_containers
    def get_value(self): return None
    def __iter__(self): return iter(self.sub_containers)

class MockConfig:
    def __init__(self, name):
        self.short_name = name
        self.containers = []
        self.last_saved = None
    def get_child(self, name):
        for c in self.containers:
            if c.short_name == name: return c
        return None

# Create project structure
temp_dir = Path(tempfile.mkdtemp())
templates_dir = temp_dir / "templates"
fee_tpl_dir = templates_dir / "FEE"
fee_tpl_dir.mkdir(parents=True)

# Create Fee_PBcfg.c using the complex logic from user's request
fee_c_content = """[!SELECT "as:modconf('Fee')[1]"!][!//
[!VAR "Count" = "'0'"!][!//
[!LOOP "FeeBlockConfiguration/*"!][!//
[!VAR "Count" = "$Count + '1'"!][!//
[!ENDLOOP!][!//
Total Blocks: [!"$Count"!]
[!LOOP "FeeBlockConfiguration/*"!][!//
    {
[!VAR "imm" = "FeeImmediateData"!][!//
[!VAR "blk_num" = "FeeBlockNumber"!][!//
        [!"$blk_num"!]U,     /* Block number */
[!IF "$imm = 'true'"!][!//
        TRUE,    /* immediate */
[!ELSE!][!//
        FALSE,   /* normal */
[!ENDIF!][!//
    },
[!ENDLOOP!][!//
[!ENDSELECT!][!//
"""
(fee_tpl_dir / "Fee_PBcfg.c").write_text(fee_c_content)

# Create mock data
config = MockConfig('Fee')
p_cont = MockContainer('FeeBlockConfiguration', '/AUTOSAR/EcucDefs/Fee/FeeBlockConfiguration')
config.containers.append(p_cont)

b1 = MockContainer('Block1', '/AUTOSAR/EcucDefs/Fee/FeeBlockConfiguration/Block')
b1.parameter_values['FeeBlockNumber'] = MockParam('FeeBlockNumber', 10)
b1.parameter_values['FeeImmediateData'] = MockParam('FeeImmediateData', True)
p_cont.sub_containers.append(b1)

b2 = MockContainer('Block2', '/AUTOSAR/EcucDefs/Fee/FeeBlockConfiguration/Block')
b2.parameter_values['FeeBlockNumber'] = MockParam('FeeBlockNumber', 20)
b2.parameter_values['FeeImmediateData'] = MockParam('FeeImmediateData', False)
p_cont.sub_containers.append(b2)

# Create proper module definition
from autosar_configurator.core.model.definition_model import (
    EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType
)

fee_def = EcucModuleDef(short_name='Fee', definition_ref='/AUTOSAR/EcucDefs/Fee')
block_cfg_def = EcucContainerDef(short_name='FeeBlockConfiguration', definition_ref='/AUTOSAR/EcucDefs/Fee/FeeBlockConfiguration')
block_def = EcucContainerDef(short_name='Block', definition_ref='/AUTOSAR/EcucDefs/Fee/FeeBlockConfiguration/Block')

block_def.add_parameter(EcucParameterDef(short_name='FeeBlockNumber', param_type=EcucParameterType.INTEGER, definition_ref='/AUTOSAR/EcucDefs/Fee/FeeBlockConfiguration/Block/FeeBlockNumber'))
block_def.add_parameter(EcucParameterDef(short_name='FeeImmediateData', param_type=EcucParameterType.BOOLEAN, definition_ref='/AUTOSAR/EcucDefs/Fee/FeeBlockConfiguration/Block/FeeImmediateData'))

block_cfg_def.add_sub_container(block_def)
fee_def.add_container(block_cfg_def)

# Run generator
generator = CodeGenerator(
    fee_def,
    config,
    project_template_dir=templates_dir
)

# Enable debug logging for the generator modules
logging.getLogger('autosar_configurator').setLevel(logging.DEBUG)

print("=== Running complex verification ===")
out_dir = Path(tempfile.mkdtemp())

try:
    # Generate the file
    generator._generate_single_file('PBcfg.c', out_dir)
    
    output_file = out_dir / "Fee_PBcfg.c"
    if output_file.exists():
        content = output_file.read_text()
        print("--- Generated Content ---")
        print(content)
        
        # Validation checks
        all_passed = True
        
        # 1. XPath Indexing check
        if "Total Blocks: 2" not in content:
            print("❌ FAILED: Total Blocks count incorrect or SELECT failed")
            all_passed = False
            
        # 2. OUTPUT Unwrapping check
        if "10U" not in content or "20U" not in content:
            print("❌ FAILED: Block numbers not correctly unwrapped")
            all_passed = False
            
        # 3. IF condition with string value check
        if "TRUE,    /* immediate */" not in content or "FALSE,   /* normal */" not in content:
            print("❌ FAILED: IF conditions not correctly evaluated (string vs bool)")
            all_passed = False

        if all_passed:
            print("\n✅ Verification SUCCESSFUL! All complex logic handled correctly.")
        else:
            print("\n❌ Verification FAILED!")
    else:
        print("\n❌ Output file not found!")

finally:
    shutil.rmtree(temp_dir)
    shutil.rmtree(out_dir)

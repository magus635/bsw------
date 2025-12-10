
import sys
import os
from unittest.mock import MagicMock

# Add project root to path
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))

from autosar_configurator.core.ai.validator import IntelligentValidator
from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue, EcucParameterValue
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType

def run_verification():
    print("=== Test: Project-Wide Intelligent Validation ===")
    
    # 1. Mock Knowledge Base & Gemini Client
    mock_kb = MagicMock()
    mock_kb.is_ready = True
    mock_kb.search.return_value = [("Module A constraint: Max speed 100", 0.9), ("Module B constraint: Must be enabled", 0.8)]
    
    mock_gemini = MagicMock()
    mock_gemini.generate_response.return_value = "✅ Mock Validation Passed: All project modules checked."
    
    validator = IntelligentValidator(mock_kb, mock_gemini)
    
    # 2. Mock Project Structure
    mock_project = MagicMock()
    mock_project.module_managers = {}
    
    # Module A Setup
    # mod_a_def object is used for structure but reference strings should be used for values
    
    # 1. Create Module Config (short_name, def_ref)
    mod_a_conf = EcucModuleConfiguration("ModuleA_Config", "/AUTOSAR/EcucDefs/ModuleA")
    
    # 2. Create Parameter Value (def_ref, value)
    # Note: EcucParameterValue expects references as strings, not objects
    param_val_a = EcucParameterValue("/AUTOSAR/EcucDefs/ModuleA/SpeedContainer/Speed", 50)
    
    # 3. Create Container Value (short_name, def_ref, parent=None)
    cnt_a = EcucContainerValue("SpeedContainer_1", "/AUTOSAR/EcucDefs/ModuleA/SpeedContainer", parent=None)
    cnt_a.parameter_values["Speed"] = param_val_a
    
    mod_a_conf.containers.append(cnt_a)
    
    manager_a = MagicMock(spec=ConfigurationManager)
    # manager.module_def needs short_name for validator validation context name
    mod_a_def = MagicMock()
    mod_a_def.short_name = "ModuleA"
    manager_a.module_def = mod_a_def
    manager_a.configuration = mod_a_conf
    
    # Module B Setup
    mod_b_conf = EcucModuleConfiguration("ModuleB_Config", "/AUTOSAR/EcucDefs/ModuleB")
    
    param_val_b = EcucParameterValue("/AUTOSAR/EcucDefs/ModuleB/StatusContainer/Enabled", True)
    
    cnt_b = EcucContainerValue("StatusContainer_1", "/AUTOSAR/EcucDefs/ModuleB/StatusContainer", parent=None)
    cnt_b.parameter_values["Enabled"] = param_val_b
    
    mod_b_conf.containers.append(cnt_b)
    
    manager_b = MagicMock(spec=ConfigurationManager)
    mod_b_def = MagicMock()
    mod_b_def.short_name = "ModuleB"
    manager_b.module_def = mod_b_def
    manager_b.configuration = mod_b_conf
    
    # Add to Project
    mock_project.module_managers["ModuleA"] = manager_a
    mock_project.module_managers["ModuleB"] = manager_b
    
    # 3. Run Validation
    print("Executing validator.validate_project()...")
    result = validator.validate_project(mock_project)
    
    print(f"\nResult:\n{result}")
    
    # 4. Verify Inputs to Gemini
    # Check if create_snapshot was called implies we iterated. 
    # But effectively checking the combined prompt sent to Gemini is best.
    
    args, kwargs = mock_gemini.generate_response.call_args
    prompt_sent = args[0]
    
    print("\n--- Verifying Prompt Content ---")
    if "ModuleA_Config" in prompt_sent and "ModuleB_Config" in prompt_sent:
        print("✅ SUCCESS: Prompt contains snapshots from both modules.")
    else:
        print("❌ FAILURE: Prompt missing module data.")
        print(f"Content snippet: {prompt_sent[:200]}...")
        
    if "Reference Documentation" in prompt_sent:
         print("✅ SUCCESS: Prompt contains reference docs.")

if __name__ == "__main__":
    run_verification()

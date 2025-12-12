
import sys
from PySide6.QtWidgets import QApplication, QWidget, QVBoxLayout
from PySide6.QtCore import Qt
from unittest.mock import MagicMock

# Import necessary classes (adjust paths as needed)
sys.path.append('/Users/qlwang/Desktop/bsw图形配置工具')
from autosar_configurator.ui.widgets.davinci_config_panel import DaVinciConfigPanel
from autosar_configurator.core.model.definition_model import EcucContainerDef, EcucParameterDef, EcucParameterType, EcucReferenceDef
from autosar_configurator.core.model.configuration_model import EcucContainerValue

def create_mock_data():
    # Def A: Has references
    def_a = EcucContainerDef("ContainerA")
    ref_def = EcucReferenceDef("MyRef", destination_ref="/Path/To/Dest")
    def_a.add_reference(ref_def)
    
    # Instance A
    inst_a = EcucContainerValue("InstanceA", def_a.definition_ref)
    
    # Def B: No references, just params
    def_b = EcucContainerDef("ContainerB")
    param_def = EcucParameterDef("MyParam", EcucParameterType.INTEGER)
    def_b.add_parameter(param_def)
    
    # Instance B
    inst_b = EcucContainerValue("InstanceB", def_b.definition_ref)
    
    return (def_a, inst_a), (def_b, inst_b)

def test_panel_switch():
    app = QApplication(sys.argv)
    
    # Create panel
    panel = DaVinciConfigPanel()
    panel.show()
    
    (def_a, inst_a), (def_b, inst_b) = create_mock_data()
    
    config_manager = MagicMock()
    # Mock configuration for searches
    config_manager.configuration.containers = []
    
    print("\n--- Test 1: Show Instance A (With Refs) ---")
    try:
        panel.show_instance(inst_a, def_a, config_manager, project=None)
        print("Show A success")
        print(f"Ref Group Visible: {not panel.references_group.isHidden()}")
        print(f"Rows in Ref Table: {panel.refs_table.rowCount()}")
    except Exception as e:
        print(f"Show A Failed: {e}")
        import traceback
        traceback.print_exc()

    print("\n--- Test 2: Show Instance B (No Refs) ---")
    try:
        panel.show_instance(inst_b, def_b, config_manager, project=None)
        print("Show B success")
        print(f"Ref Group Visible: {not panel.references_group.isHidden()}")
        print(f"Rows in Ref Table: {panel.refs_table.rowCount()}")
        
        if not panel.references_group.isHidden():
            print("FAILURE: Ref Group should be hidden for Node B!")
        else:
            print("SUCCESS: Ref Group is hidden.")
            
    except Exception as e:
        print(f"Show B Failed: {e}")
        import traceback
        traceback.print_exc()

    # app.exec() # Don't block

if __name__ == "__main__":
    test_panel_switch()

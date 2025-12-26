"""
Test script for EMF-style Reference Resolution

Verifies that cross-module references can be resolved from string paths
to actual object pointers, enabling object navigation.
"""

import sys
from pathlib import Path

# Add project root to path
sys.path.insert(0, str(Path(__file__).parent))

from autosar_configurator.core.model.configuration_model import (
    EcucModuleConfiguration,
    EcucContainerValue,
    EcucReferenceValue
)


def test_reference_resolution():
    """Test that references can be resolved to object pointers"""
    print("=" * 60)
    print("EMF Reference Resolution Test")
    print("=" * 60)
    
    # Create a mock "Can" module with a CanController
    can_config = EcucModuleConfiguration(
        short_name="Can",
        definition_ref="/AUTOSAR/EcucDefs/Can"
    )
    
    can_controller = EcucContainerValue(
        short_name="CanController_0",
        definition_ref="/AUTOSAR/EcucDefs/Can/CanConfigSet/CanController"
    )
    can_controller.set_parameter_value("CanControllerId", 0, "/def/path")
    can_controller.set_parameter_value("CanControllerBaudRate", 500000, "/def/path")
    
    can_config.add_container(can_controller)
    
    # Create a mock "CanIf" module with a reference to the CanController
    canif_config = EcucModuleConfiguration(
        short_name="CanIf",
        definition_ref="/AUTOSAR/EcucDefs/CanIf"
    )
    
    canif_ctrl = EcucContainerValue(
        short_name="CanIfCtrlCfg_0",
        definition_ref="/AUTOSAR/EcucDefs/CanIf/CanIfCtrlDrvCfg/CanIfCtrlCfg"
    )
    
    # Set a reference to the CanController
    canif_ctrl.set_reference_value(
        "CanIfCtrlCanCtrlRef",
        can_controller.get_path(),  # This is the string path
        "/AUTOSAR/EcucDefs/CanIf/CanIfCtrlDrvCfg/CanIfCtrlCfg/CanIfCtrlCanCtrlRef"
    )
    
    canif_config.add_container(canif_ctrl)
    
    # Check initial state: target should be None
    ref = canif_ctrl.reference_values["CanIfCtrlCanCtrlRef"]
    print(f"\n1. Before Resolution:")
    print(f"   - value_ref (string path): {ref.value_ref}")
    print(f"   - target (object): {ref.target}")
    print(f"   - is_resolved: {ref.is_resolved}")
    
    assert ref.target is None, "Target should be None before resolution"
    assert not ref.is_resolved, "is_resolved should be False before resolution"
    
    # Create a global resolver function (simulating WorkspaceProject.get_instance_by_path)
    all_configs = [can_config, canif_config]
    
    def global_resolver(path: str):
        for config in all_configs:
            instance = config.get_instance_by_path(path)
            if instance is not None:
                return instance
        return None
    
    # Resolve references
    resolved_count = canif_config.resolve_references(global_resolver)
    
    print(f"\n2. After Resolution:")
    print(f"   - Resolved count: {resolved_count}")
    print(f"   - value_ref (string path): {ref.value_ref}")
    print(f"   - target (object): {ref.target}")
    print(f"   - is_resolved: {ref.is_resolved}")
    
    assert ref.target is not None, "Target should NOT be None after resolution"
    assert ref.is_resolved, "is_resolved should be True after resolution"
    assert ref.target is can_controller, "Target should be the exact CanController object"
    
    # Demonstrate object navigation
    print(f"\n3. EMF-Style Object Navigation:")
    print(f"   - ref.target.short_name: {ref.target.short_name}")
    baud_rate = ref.target.parameter_values.get("CanControllerBaudRate")
    if baud_rate:
        print(f"   - ref.target.parameter_values['CanControllerBaudRate'].value: {baud_rate.value}")
    
    print("\n" + "=" * 60)
    print("✅ All tests passed! EMF Reference Resolution working correctly.")
    print("=" * 60)
    
    return True


if __name__ == "__main__":
    success = test_reference_resolution()
    sys.exit(0 if success else 1)

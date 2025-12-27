
import pytest
from pathlib import Path
from autosar_configurator.core.model.configuration_model import (
    EcucModuleConfiguration,
    EcucContainerValue,
    EcucReferenceValue,
    ResolutionError
)
from autosar_configurator.core.config_manager import ConfigurationManager, ValidationError
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef

class TestReferenceEdgeCases:
    def setup_method(self):
        # Create a mock module definition
        self.module_def = EcucModuleDef("TestModule")
        self.module_def.definition_ref = "/AUTOSAR/EcucDefs/TestModule"
        self.container_def = EcucContainerDef("TestContainer")
        self.container_def.definition_ref = "/AUTOSAR/EcucDefs/TestModule/TestContainer"
        self.container_def.upper_multiplicity = -1 # Allow multiple instances
        self.module_def.add_container(self.container_def)
        
        # Initialize manager
        self.manager = ConfigurationManager(self.module_def)
        self.config = self.manager.configuration

    def test_reverse_reference_indexing(self):
        """Test that reverse references are correctly indexed in WorkspaceProject"""
        from autosar_configurator.core.workspace_manager import WorkspaceProject
        
        project = WorkspaceProject("TestProject")
        manager = project.add_module(self.module_def, Path("test.arxml"))
        
        # Create two containers
        c1 = manager.create_container_instance(self.container_def, instance_name="C1")
        c2 = manager.create_container_instance(self.container_def, instance_name="C2")
        
        # C1 references C2
        c1.set_reference_value("RefToC2", "/Config/C2", "/Def/Ref")
        
        # Resolve references
        project.resolve_all_references()
        
        # Build reverse index
        count = project.build_reverse_reference_index()
        assert count == 1
        
        # Check if C2 knows it is referenced by C1
        assert len(c2.referenced_by) == 1
        assert c2.referenced_by[0].value_ref == "/Config/C2"
        # Since ref_value is what's in C1.reference_values["RefToC2"]
        assert c2.referenced_by[0] == c1.reference_values["RefToC2"]

    def test_deletion_protection(self):
        """Test that a container cannot be deleted if it is referenced"""
        # Create two containers
        c1 = self.manager.create_container_instance(self.container_def, instance_name="C1")
        c2 = self.manager.create_container_instance(self.container_def, instance_name="C2")
        
        # C1 references C2 using C2's actual path
        c1.set_reference_value("RefToC2", c2.get_path(), "/Def/Ref")
        
        # Try to delete C2 - should fail
        with pytest.raises(ValidationError) as excinfo:
            self.manager.delete_container_instance(c2)
        
        assert "Cannot delete C2" in str(excinfo.value)
        assert "Referenced by 1 other container(s)" in str(excinfo.value)
        
        # Remove reference first
        del c1.reference_values["RefToC2"]
        
        # Now delete should succeed
        self.manager.delete_container_instance(c2)
        assert c2 not in self.config.containers

    def test_cross_module_resolution(self):
        """Test reference resolution across different modules"""
        from autosar_configurator.core.workspace_manager import WorkspaceProject
        
        project = WorkspaceProject("TestProject")
        
        # Module A
        def_a = EcucModuleDef("ModA")
        def_a.definition_ref = "/AUTOSAR/EcucDefs/ModA"
        cont_a_def = EcucContainerDef("ContA")
        cont_a_def.definition_ref = "/AUTOSAR/EcucDefs/ModA/ContA"
        cont_a_def.upper_multiplicity = -1
        def_a.add_container(cont_a_def)
        manager_a = project.add_module(def_a, Path("a.arxml"))
        inst_a = manager_a.create_container_instance(cont_a_def, instance_name="InstA")
        
        # Module B
        def_b = EcucModuleDef("ModB")
        def_b.definition_ref = "/AUTOSAR/EcucDefs/ModB"
        cont_b_def = EcucContainerDef("ContB")
        cont_b_def.definition_ref = "/AUTOSAR/EcucDefs/ModB/ContB"
        cont_b_def.upper_multiplicity = -1
        def_b.add_container(cont_b_def)
        manager_b = project.add_module(def_b, Path("b.arxml"))
        inst_b = manager_b.create_container_instance(cont_b_def, instance_name="InstB")
        
        # InstA references InstB
        inst_a.set_reference_value("RefToB", "/Config/InstB", "/Def/Ref")
        
        # Resolve
        total_resolved, total_errors = project.resolve_all_references()
        
        assert total_resolved == 1
        assert total_errors == 0
        assert inst_a.reference_values["RefToB"].is_resolved
        assert inst_a.reference_values["RefToB"].target == inst_b

if __name__ == "__main__":
    pytest.main([__file__, "-v"])

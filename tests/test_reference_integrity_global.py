import pytest
from pathlib import Path
from autosar_configurator.core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucReferenceDef
from autosar_configurator.core.workspace_manager import WorkspaceProject
from autosar_configurator.core.config_manager import ValidationError

def setup_project():
    # Setup two modules: ModuleA and ModuleB
    # ModuleB has a reference to ModuleA
    
    # Module A
    def_a = EcucModuleDef("ModuleA")
    def_a.definition_ref = "/AUTOSAR/EcucDefs/ModuleA"
    cont_a_def = EcucContainerDef("ContA", lower_multiplicity=0, upper_multiplicity=-1)
    cont_a_def.definition_ref = "/AUTOSAR/EcucDefs/ModuleA/ContA"
    def_a.containers["ContA"] = cont_a_def
    
    # Module B
    def_b = EcucModuleDef("ModuleB")
    def_b.definition_ref = "/AUTOSAR/EcucDefs/ModuleB"
    cont_b_def = EcucContainerDef("ContB", lower_multiplicity=0, upper_multiplicity=-1)
    cont_b_def.definition_ref = "/AUTOSAR/EcucDefs/ModuleB/ContB"
    ref_def = EcucReferenceDef("RefToA", destination_ref="/AUTOSAR/EcucDefs/ModuleA/ContA")
    ref_def.definition_ref = "/AUTOSAR/EcucDefs/ModuleB/ContB/RefToA"
    cont_b_def.references["RefToA"] = ref_def
    def_b.containers["ContB"] = cont_b_def
    
    project = WorkspaceProject("TestProject")
    mgr_a = project.add_module(def_a, Path("ModuleA_Def.arxml"))
    mgr_b = project.add_module(def_b, Path("ModuleB_Def.arxml"))
    
    # Create instances
    inst_a = mgr_a.create_container_instance(cont_a_def, instance_name="InstA")
    inst_b = mgr_b.create_container_instance(cont_b_def, instance_name="InstB")
    
    # Set reference from B to A
    inst_b.set_reference_value("RefToA", inst_a.get_path(), ref_def.definition_ref)
    
    # Resolve and build index
    project.resolve_all_references()
    project.build_reverse_reference_index()
    
    return project, mgr_a, mgr_b, inst_a, inst_b

def test_cross_module_deletion_protection():
    project, mgr_a, mgr_b, inst_a, inst_b = setup_project()
    
    # Try to delete InstA from mgr_a
    # Since InstA is referenced by InstB (in ModuleB), it should fail
    with pytest.raises(ValidationError) as excinfo:
        mgr_a.delete_container_instance(inst_a)
    
    assert "Referenced by 1 other container(s)" in str(excinfo.value)
    assert "InstB.RefToA" in str(excinfo.value)
    
    # Now remove the reference
    del inst_b.reference_values["RefToA"]
    # We also need to manually unregister if not using commands, 
    # but in real app commands handle this. 
    # For this low-level test, let's just re-index or manual unregister.
    project.unregister_container_references(inst_b) # This cleans up the old ref
    
    # Now deletion should succeed
    mgr_a.delete_container_instance(inst_a)
    assert inst_a not in mgr_a.configuration.containers

def test_ghost_reference_prevention_on_update():
    project, mgr_a, mgr_b, inst_a, inst_b = setup_project()
    
    # Create another InstA2
    cont_a_def = mgr_a.module_def.containers["ContA"]
    inst_a2 = mgr_a.create_container_instance(cont_a_def, instance_name="InstA2")
    
    assert len(inst_a.referenced_by) == 1
    assert len(inst_a2.referenced_by) == 0
    
    # Update reference in B from InstA to InstA2
    # We'll simulate what SetReferenceCommand does
    old_ref = inst_b.reference_values["RefToA"]
    old_target = old_ref.target
    
    # 1. Unregister old
    if old_target and old_ref in old_target.referenced_by:
        old_target.referenced_by.remove(old_ref)
        
    # 2. Update to new
    inst_b.set_reference_value("RefToA", inst_a2.get_path(), old_ref.definition_ref)
    new_ref = inst_b.reference_values["RefToA"]
    new_ref.target = inst_a2
    inst_a2.referenced_by.append(new_ref)
    
    # 3. Verify
    assert len(inst_a.referenced_by) == 0  # No ghost reference
    assert len(inst_a2.referenced_by) == 1 # Correct new reference

def test_ghost_reference_prevention_on_deletion():
    project, mgr_a, mgr_b, inst_a, inst_b = setup_project()
    
    assert len(inst_a.referenced_by) == 1
    
    # Delete InstB (which references InstA)
    # mgr_b.delete_container_instance should now unregister references
    mgr_b.delete_container_instance(inst_b)
    
    # Verify InstA is no longer referenced
    assert len(inst_a.referenced_by) == 0 # No ghost reference

"""
Overlay Engine - Merges Definition (XDM/ARXML DEF) and Configuration (ARXML VALUE)

Implements the XDM + ARXML Overlay mechanism:
1. Base Layer: Load module definition with default values
2. Overlay Layer: Apply user configuration values
3. Fallback: If config value missing, use definition default
"""
import os
import tempfile
from typing import Optional, Dict, Any
from .symbol_table import ConfigurationNode, SymbolTable
from .errors import MultiplicityViolationError

# Debug log file path - cross-platform
_DEBUG_LOG_PATH = os.path.join(tempfile.gettempdir(), 'bsw_gen.log')

def _debug_log(msg: str):
    """Helper to write diagnostic logs to a fixed file for worker threads."""
    try:
        with open(_DEBUG_LOG_PATH, 'a') as f:
            f.write(msg + '\n')
        print(f"[DEBUG] {msg}")
    except (IOError, OSError):
        pass

# Import existing project models
from ...core.model.definition_model import (
    EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucReferenceDef
)
from ...core.model.configuration_model import (
    EcucModuleConfiguration, EcucContainerValue
)


class OverlayEngine:
    """Merges Definition and Configuration into unified ConfigurationNode tree.
    
    This engine creates a unified view where:
    - Every parameter has access to both its configured value and default value
    - Cross-module references can be resolved via SymbolTable
    - Multiplicity constraints are validated
    """
    
    def __init__(self, symbol_table: Optional[SymbolTable] = None, strict: bool = True):
        """Initialize overlay engine.
        
        Args:
            symbol_table: Global symbol table for cross-module references
            strict: If True, raise errors on constraint violations
        """
        self.symbol_table = symbol_table or SymbolTable()
        self.strict = strict
    
    def build_configuration_tree(
        self, 
        module_def: EcucModuleDef, 
        configuration: Optional[EcucModuleConfiguration] = None,
        variant: Optional[str] = None
    ) -> ConfigurationNode:
        """Build unified ConfigurationNode tree from definition and configuration.
        
        Args:
            module_def: Module definition (from ARXML DEF / XDM)
            configuration: Module configuration (from ARXML VALUE), optional
            variant: Name of the active variant for selecting top-level container instances
            
        Returns:
            Root ConfigurationNode for the module
        """
        module_name = module_def.short_name
        
        # Create module root node
        root = ConfigurationNode(
            short_name=module_name,
            node_type='module',
            path=f"/{module_name}",
            definition_ref=module_def.definition_ref
        )
        
        _debug_log(f"DEBUG_OVERLAY: Tree root created: {root.short_name} (path={root.path})")
        for container_name, container_def in module_def.containers.items():
            # Find matching configuration instances
            matching_instances = []
            if configuration:
                matching_instances = [c for c in configuration.containers 
                                      if c.definition_ref == container_name or c.definition_ref.endswith(f"/{container_name}")]

            _debug_log(f"DEBUG_OVERLAY: Processing module container definition: {container_name}, found {len(matching_instances)} instances")
            
            # Create a WRAPPER node for this container definition
            # This allows [!LOOP "as:modconf('Can')/CanConfigSet/*"!]
            wrapper_path = f"/{module_name}/{container_name}"
            wrapper_node = ConfigurationNode(
                short_name=container_name,
                node_type='container', # Use container type so it's navigable
                path=wrapper_path,
                definition_ref=container_def.definition_ref
            )
            
            active_instance_node = None
            
            if matching_instances:
                for inst in matching_instances:
                    # Build instances as children of the wrapper
                    nodes = self._build_container_nodes(
                        container_def,
                        inst,
                        parent_path=wrapper_path
                    )
                    for node in nodes:
                        wrapper_node.add_child(node)
                        # Check if this is the active instance for the variant
                        if variant and getattr(inst, 'variant', None) == variant:
                            active_instance_node = node
                
                # If no variant match, select the instance with the MOST sub-containers
                # This ensures CanConfigSet_1 (with 3 controllers) is preferred over 
                # CanConfigSet (with 1 controller)
                if not active_instance_node and wrapper_node.get_children_list():
                    children_list = wrapper_node.get_children_list()
                    # Find the child with most nested sub-container INSTANCES
                    # Structure: CanConfigSet_1 -> CanController (wrapper) -> [CanController_0, CanController_1, ...]
                    best_node = None
                    max_total_instances = -1
                    for child in children_list:
                        total_instances = 0
                        # Count all instances inside container-type children (wrappers)
                        for child_name, child_node in child.children.items():
                            if hasattr(child_node, 'node_type') and child_node.node_type == 'container':
                                # This is a wrapper node (like CanController)
                                # Count its children (the actual instances)
                                wrapper_children = child_node.get_children_list() if hasattr(child_node, 'get_children_list') else []
                                total_instances += len(wrapper_children)
                        if total_instances > max_total_instances:
                            max_total_instances = total_instances
                            best_node = child
                    active_instance_node = best_node if best_node else children_list[0]
                
                # ALIASING: Make the wrapper node also behave like the active instance.
                # This allows as:modconf('Can')/CanConfigSet/CanController to work.
                if active_instance_node:
                    for sub_name, sub_node in active_instance_node.children.items():
                        # Alias parameters and sub-container WRAPPERS to the parent wrapper
                        # This allows paths like /Can/CanConfigSet/CanController to work
                        if sub_name not in wrapper_node.children:
                             wrapper_node.children[sub_name] = sub_node


            elif container_def.is_required:

                # Build from defaults if required
                nodes = self._build_container_nodes(
                    container_def,
                    None,
                    parent_path=wrapper_path
                )
                for node in nodes:
                    wrapper_node.add_child(node)

            # Add the wrapper to the module root
            root.add_child(wrapper_node)
            
            # Special Alias Selection:
            # If a specific variant is active and we found a matching instance, 
            # we can make the wrapper node's values reflect that instance?
            # Actually, EB Tresos often lets you use the definition name as an alias for the active instance.
            # For now, the user mostly wants the iteration to work.
            
            # If we have an active_instance_node, we could optionally alias it?
            # But wait, if they say 'CanConfigSet/CanController', and CanConfigSet is a wrapper,
            # it won't find CanController unless we search deeper or alias.
            
            # Simple Aliasing: if we have an active instance, and it's NOT named the same as the wrapper,
            # we can add its children to the wrapper's children? (No, that's messy).
            
            # Better Aliasing: Provide access to the active instance's content via the wrapper node if searched.
            # This is handled by the XPath engine usually.

        
        # Register in symbol table
        self.symbol_table.register_module(module_name, root)
        
        return root
    
    def _build_container_nodes(
        self,
        container_def: EcucContainerDef,
        config_instance: Optional[EcucContainerValue],
        parent_path: str
    ) -> list:
        """Build ConfigurationNode(s) for a container definition.
        
        If config_instance exists, create node from it.
        If not but definition requires it (lowerMultiplicity > 0), create from defaults.
        
        For EB Tresos template compatibility:
        - Multi-instance container definitions (e.g., CanHardwareObject) create a wrapper node
        - Instances are added as children of this wrapper node
        - This allows XPath patterns like "CanHardwareObject/*" to work correctly
        """
        nodes = []
        container_name = container_def.short_name
        container_path = f"{parent_path}/{container_name}"
        
        if config_instance:
            # Create node from configuration using instance's actual name (may differ from def name)
            instance_name = config_instance.short_name
            instance_path = f"{parent_path}/{instance_name}"
            node = self._create_container_node(container_def, config_instance, instance_path)
            nodes.append(node)
            
            _debug_log(f"DEBUG_OVERLAY: Processing sub-containers for instance: {instance_name} (path={instance_path})")
            
            def matches_def(ref, name):
                if not ref: return False
                return ref == name or ref.endswith(f"/{name}")

            # Handle sub-container instances - GROUP BY DEFINITION
            # First, collect all instances by their definition name
            all_subs = getattr(config_instance, 'sub_containers', []) or []
            if not all_subs:
                children = getattr(config_instance, 'children', [])
                if isinstance(children, dict):
                    all_subs = [v for k, v in children.items() if not hasattr(v, 'value')]
                else:
                    all_subs = children
            
            for sub_def_name, sub_def in container_def.sub_containers.items():
                # Find matching sub-container instances by definition reference
                matching_subs = [s for s in all_subs 
                                 if matches_def(getattr(s, 'definition_ref', ''), sub_def_name)]
                
                if matching_subs:



                    # ALWAYS create a wrapper/group node for sub-containers
                    # This allows XPath like "CanHardwareObject/*" to return instances
                    # Even when there's only 1 instance, the XPath pattern expects instances, not parameters
                    wrapper_path = f"{instance_path}/{sub_def_name}"
                    wrapper_node = ConfigurationNode(
                        short_name=sub_def_name,
                        node_type='container',
                        path=wrapper_path,
                        definition_ref=sub_def.definition_ref,
                        lower_multiplicity=sub_def.lower_multiplicity,
                        upper_multiplicity=sub_def.upper_multiplicity
                    )
                    
                    # Add each instance as a child of the wrapper
                    for sub_config_raw in matching_subs:
                        sub_instance_name = sub_config_raw.short_name
                        sub_instance_path = f"{wrapper_path}/{sub_instance_name}"
                        sub_node = self._create_container_node(sub_def, sub_config_raw, sub_instance_path)
                        
                        # Recursively process sub-sub-containers
                        self._process_sub_containers(sub_def, sub_config_raw, sub_node, sub_instance_path)
                        
                        wrapper_node.add_child(sub_node)
                    
                    node.add_child(wrapper_node)
                elif sub_def.is_required:
                    # Create from defaults if required
                    default_node = self._create_default_container_node(sub_def, instance_path)
                    node.add_child(default_node)
        else:
            # No config instance - create from defaults if required
            if container_def.is_required:
                node = self._create_default_container_node(container_def, container_path)
                nodes.append(node)
        
        return nodes
    
    def _process_sub_containers(
        self,
        container_def: EcucContainerDef,
        config_instance: EcucContainerValue,
        node: ConfigurationNode,
        instance_path: str
    ):
        """Recursively process sub-containers for a container instance."""
        all_subs = getattr(config_instance, 'sub_containers', []) or []
        if not all_subs:
            children = getattr(config_instance, 'children', [])
            if isinstance(children, dict):
                all_subs = [v for k, v in children.items() if not hasattr(v, 'value')]
            else:
                all_subs = children
        
        for sub_def_name, sub_def in container_def.sub_containers.items():
            matching_subs = [s for s in all_subs 
                             if getattr(s, 'short_name', None) == sub_def_name or 
                             getattr(s, 'definition_ref', '') == sub_def_name or
                             getattr(s, 'definition_ref', '').endswith(f"/{sub_def_name}")]

            _debug_log(f"DEBUG_OVERLAY:   Checking sub-container def {sub_def_name} for node {node.short_name}, found {len(matching_subs)} matches")
            
            if matching_subs:
                # ALWAYS create wrapper node for sub-containers
                wrapper_path = f"{instance_path}/{sub_def_name}"
                wrapper_node = ConfigurationNode(
                    short_name=sub_def_name,
                    node_type='container',
                    path=wrapper_path,
                    definition_ref=sub_def.definition_ref,
                    lower_multiplicity=sub_def.lower_multiplicity,
                    upper_multiplicity=sub_def.upper_multiplicity
                )
                
                for sub_config_raw in matching_subs:
                    sub_instance_name = sub_config_raw.short_name
                    sub_instance_path = f"{wrapper_path}/{sub_instance_name}"
                    sub_node = self._create_container_node(sub_def, sub_config_raw, sub_instance_path)
                    self._process_sub_containers(sub_def, sub_config_raw, sub_node, sub_instance_path)
                    wrapper_node.add_child(sub_node)
                
                node.add_child(wrapper_node)
            elif sub_def.is_required:
                default_node = self._create_default_container_node(sub_def, instance_path)
                node.add_child(default_node)
    
    def _create_container_node(
        self,
        container_def: EcucContainerDef,
        config_instance: EcucContainerValue,
        path: str
    ) -> ConfigurationNode:
        """Create a ConfigurationNode from definition and configuration instance."""
        node = ConfigurationNode(
            short_name=config_instance.short_name,
            node_type='container',
            path=path,
            definition_ref=container_def.definition_ref,
            lower_multiplicity=container_def.lower_multiplicity,
            upper_multiplicity=container_def.upper_multiplicity,
            index=getattr(config_instance, 'index', 0)
        )
        
        # Add parameters
        params_source = getattr(config_instance, 'parameter_values', {}) or \
                        {k: v for k, v in getattr(config_instance, 'children', {}).items() if hasattr(v, 'value') and not hasattr(v, 'value_ref')}

        for param_name, param_def in container_def.parameters.items():
            param_node = self._create_parameter_node(
                param_def,
                params_source.get(param_name),
                f"{path}/{param_name}"
            )
            node.add_child(param_node)

        
        # Add references
        refs_source = getattr(config_instance, 'reference_values', {}) or \
                      {k: v for k, v in getattr(config_instance, 'children', {}).items() if hasattr(v, 'value_ref')}
        multi_refs_source = getattr(config_instance, 'multi_reference_values', {}) or {}
        for ref_name, ref_def in container_def.references.items():
            is_multi = ref_def.upper_multiplicity == -1 or ref_def.upper_multiplicity > 1
            multi_ref_list = multi_refs_source.get(ref_name, [])
            if is_multi and multi_ref_list:
                # Multi-valued reference: create wrapper node with indexed children
                wrapper_node = ConfigurationNode(
                    short_name=ref_name,
                    node_type='reference',
                    path=f"{path}/{ref_name}",
                    definition_ref=ref_def.definition_ref,
                    lower_multiplicity=ref_def.lower_multiplicity,
                    upper_multiplicity=ref_def.upper_multiplicity
                )
                for ref_val in sorted(multi_ref_list, key=lambda r: r.index if r.index is not None else 0):
                    idx = ref_val.index if ref_val.index is not None else 0
                    child_node = ConfigurationNode(
                        short_name=str(idx),
                        node_type='reference',
                        path=f"{path}/{ref_name}/{idx}",
                        value=ref_val.value_ref,
                        definition_ref=ref_def.definition_ref,
                        index=idx
                    )
                    wrapper_node.add_child(child_node)
                node.add_child(wrapper_node)
            else:
                # Single-valued reference
                ref_node = self._create_reference_node(
                    ref_def,
                    refs_source.get(ref_name),
                    f"{path}/{ref_name}"
                )
                node.add_child(ref_node)
        
        return node
    
    def _create_default_container_node(
        self,
        container_def: EcucContainerDef,
        parent_path: str
    ) -> ConfigurationNode:
        """Create a ConfigurationNode from definition defaults only."""
        path = f"{parent_path}/{container_def.short_name}"
        
        node = ConfigurationNode(
            short_name=container_def.short_name,
            node_type='container',
            path=path,
            definition_ref=container_def.definition_ref,
            lower_multiplicity=container_def.lower_multiplicity,
            upper_multiplicity=container_def.upper_multiplicity
        )
        
        # Add parameters with only default values
        for param_name, param_def in container_def.parameters.items():
            param_node = ConfigurationNode(
                short_name=param_name,
                node_type='parameter',
                path=f"{path}/{param_name}",
                value=None,
                default_value=param_def.default_value,
                definition_ref=param_def.definition_ref,
                param_type=param_def.param_type.value if param_def.param_type else ""
            )
            node.add_child(param_node)
        
        # Add references (no value, just structure)
        for ref_name, ref_def in container_def.references.items():
            is_multi = ref_def.upper_multiplicity == -1 or ref_def.upper_multiplicity > 1
            if is_multi:
                # Multi-valued reference: create empty wrapper node
                wrapper_node = ConfigurationNode(
                    short_name=ref_name,
                    node_type='reference',
                    path=f"{path}/{ref_name}",
                    value=None,
                    definition_ref=ref_def.definition_ref,
                    lower_multiplicity=ref_def.lower_multiplicity,
                    upper_multiplicity=ref_def.upper_multiplicity
                )
                node.add_child(wrapper_node)
            else:
                ref_node = ConfigurationNode(
                    short_name=ref_name,
                    node_type='reference',
                    path=f"{path}/{ref_name}",
                    value=None,
                    definition_ref=ref_def.definition_ref
                )
                node.add_child(ref_node)
        
        # Recursively add required sub-containers
        for sub_name, sub_def in container_def.sub_containers.items():
            if sub_def.is_required:
                sub_node = self._create_default_container_node(sub_def, path)
                node.add_child(sub_node)
        
        return node
    
    def _create_parameter_node(
        self,
        param_def: EcucParameterDef,
        param_value,  # EcucParameterValue or None
        path: str
    ) -> ConfigurationNode:
        """Create a parameter ConfigurationNode."""
        value = param_value.value if param_value else None
        
        return ConfigurationNode(
            short_name=param_def.short_name,
            node_type='parameter',
            path=path,
            value=value,
            default_value=param_def.default_value,
            definition_ref=param_def.definition_ref,
            param_type=param_def.param_type.value if param_def.param_type else "",
            lower_multiplicity=param_def.lower_multiplicity,
            upper_multiplicity=param_def.upper_multiplicity
        )


    
    def _create_reference_node(
        self,
        ref_def: EcucReferenceDef,
        ref_value,  # EcucReferenceValue or None
        path: str
    ) -> ConfigurationNode:
        """Create a reference ConfigurationNode."""
        value = ref_value.value_ref if ref_value else None
        
        return ConfigurationNode(
            short_name=ref_def.short_name,
            node_type='reference',
            path=path,
            value=value,
            definition_ref=ref_def.definition_ref,
            lower_multiplicity=ref_def.lower_multiplicity,
            upper_multiplicity=ref_def.upper_multiplicity
        )
    
    def validate_multiplicity(self, root: ConfigurationNode) -> list:
        """Validate multiplicity constraints on the configuration tree.
        
        Returns:
            List of error messages (empty if valid)
        """
        errors = []
        self._validate_node_multiplicity(root, errors)
        return errors
    
    def _validate_node_multiplicity(self, node: ConfigurationNode, errors: list):
        """Recursively validate multiplicity."""
        if node.node_type == 'container':
            # Count children by definition ref
            child_counts: Dict[str, int] = {}
            for child in node.children.values():
                if child.node_type == 'container':
                    ref = child.definition_ref
                    child_counts[ref] = child_counts.get(ref, 0) + 1
            
            # Validate against constraints (simplified - would need def lookup)
            for child in node.children.values():
                if child.node_type == 'container':
                    count = child_counts.get(child.definition_ref, 0)
                    if count < child.lower_multiplicity:
                        errors.append(
                            f"Too few instances of {child.short_name}: "
                            f"{count} < {child.lower_multiplicity}"
                        )
                    if child.upper_multiplicity != -1 and count > child.upper_multiplicity:
                        errors.append(
                            f"Too many instances of {child.short_name}: "
                            f"{count} > {child.upper_multiplicity}"
                        )
        
        # Recurse
        for child in node.children.values():
            self._validate_node_multiplicity(child, errors)

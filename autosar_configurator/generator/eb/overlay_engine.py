"""
Overlay Engine - Merges Definition (XDM/ARXML DEF) and Configuration (ARXML VALUE)

Implements the XDM + ARXML Overlay mechanism:
1. Base Layer: Load module definition with default values
2. Overlay Layer: Apply user configuration values
3. Fallback: If config value missing, use definition default
"""
from typing import Optional, Dict, Any
from .symbol_table import ConfigurationNode, SymbolTable
from .errors import MultiplicityViolationError

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

        for container_name, container_def in module_def.containers.items():
            # Find matching configuration instances
            matching_instances = []
            if configuration:
                matching_instances = [c for c in configuration.containers 
                                      if c.definition_ref == container_name or c.definition_ref.endswith(f"/{container_name}")]

            # Create a WRAPPER node for this container definition
            # This allows [!LOOP "as:modconf('Can')/CanConfigSet/*"!]
            wrapper_path = f"/{module_name}/{container_name}"
            wrapper_node = ConfigurationNode(
                short_name=container_name,
                node_type='container', # Use container type so it's navigable
                path=wrapper_path,
                definition_ref=container_def.definition_ref,
                is_wrapper=True
            )

            # FIX: Add wrapper to root BEFORE adding children, so that children can correctly
            # resolve their parent (handling the case where child path == wrapper path)
            root.add_child(wrapper_node)

            active_instance_node = None
            
            if matching_instances:
                for inst in matching_instances:
                    # Build instances as children of the wrapper
                    nodes = self._build_container_nodes(
                        container_def,
                        inst,
                        parent_path=wrapper_node.path
                    )
                    for node in nodes:
                        wrapper_node.add_child(node)
                        # Check if this is the active instance for the variant
                        if variant and getattr(inst, 'variant', None) == variant:
                            active_instance_node = node
                
                self._alias_active_instance(wrapper_node, variant)


            elif container_def.is_required:

                # Build from defaults if required
                nodes = self._build_container_nodes(
                    container_def,
                    None,
                    parent_path=root.path
                )
                for node in nodes:
                    wrapper_node.add_child(node)

            # Add the wrapper to the module root (MOVED UP)
            # root.add_child(wrapper_node) -> See above
            
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

        # Process containers from configuration that are NOT in definition (Schema Inference)
        if not self.strict and configuration:
            processed_refs = {c_def.definition_ref for c_def in module_def.containers.values()}
            
            unknown_containers_by_def = {}
            for container in configuration.containers:
                is_processed = False
                for c_def_ref in processed_refs:
                    if container.definition_ref == c_def_ref or \
                       (c_def_ref and container.definition_ref and container.definition_ref.endswith(f"/{c_def_ref.split('/')[-1]}")):
                        is_processed = True
                        break
                if not is_processed:
                    def_name = container.definition_ref.split('/')[-1] if container.definition_ref else container.short_name.split('_')[0]
                    if def_name not in unknown_containers_by_def:
                        unknown_containers_by_def[def_name] = []
                    unknown_containers_by_def[def_name].append(container)

            for def_name, containers in unknown_containers_by_def.items():
                is_multiple = len(containers) > 1 or containers[0].short_name != def_name
                
                if is_multiple:
                    wrapper_node = root.get_child(def_name)
                    if not wrapper_node:
                        wrapper_path = f"/{module_name}/{def_name}"
                        wrapper_node = ConfigurationNode(
                            short_name=def_name,
                            node_type='container',
                            path=wrapper_path,
                            definition_ref=containers[0].definition_ref,
                            is_wrapper=True
                        )
                        root.add_child(wrapper_node)
                    
                    for container in containers:
                        instance_path = f"{wrapper_node.path}/{container.short_name}"
                        node = self._create_container_node(None, container, instance_path)
                        wrapper_node.add_child(node)
                else:
                    # Single instance, no wrapper
                    container = containers[0]
                    instance_path = f"/{module_name}/{container.short_name}"
                    node = self._create_container_node(None, container, instance_path)
                    root.add_child(node)
        
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
            
            # FIX: Avoid redundant path segments if instance name matches wrapper name
            # This happens when container definition name equals instance name (common for singletons)
            if parent_path.endswith(f"/{instance_name}"):
                instance_path = parent_path
            else:
                instance_path = f"{parent_path}/{instance_name}"

            node = self._create_container_node(container_def, config_instance, instance_path)
            nodes.append(node)

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
                        upper_multiplicity=sub_def.upper_multiplicity,
                        is_wrapper=True
                    )
                    
                    # Add each instance as a child of the wrapper
                    for sub_config_raw in matching_subs:
                        sub_instance_name = sub_config_raw.short_name
                        # FIX: Child instances are relative to their wrapper, not the grandparent instance
                        sub_instance_path = f"{wrapper_path}/{sub_instance_name}"
                        sub_node = self._create_container_node(sub_def, sub_config_raw, sub_instance_path)
                        
                        # Recursively process sub-sub-containers
                        self._process_sub_containers(sub_def, sub_config_raw, sub_node, sub_instance_path)
                        
                        wrapper_node.add_child(sub_node)
                    
                    node.add_child(wrapper_node)
                elif sub_def.is_required:
                    # Create from defaults if required
                    # FIX: Use instance_path as parent, not wrapper_path
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

            if matching_subs:
                # ALWAYS create wrapper node for sub-containers
                wrapper_path = f"{instance_path}/{sub_def_name}"
                wrapper_node = ConfigurationNode(
                    short_name=sub_def_name,
                    node_type='container',
                    path=wrapper_path,
                    definition_ref=sub_def.definition_ref,
                    lower_multiplicity=sub_def.lower_multiplicity,
                    upper_multiplicity=sub_def.upper_multiplicity,
                    is_wrapper=True
                )
                
                for sub_config_raw in matching_subs:
                    sub_instance_name = sub_config_raw.short_name
                    # FIX: Child instances are relative to their wrapper
                    sub_instance_path = f"{wrapper_path}/{sub_instance_name}"
                    sub_node = self._create_container_node(sub_def, sub_config_raw, sub_instance_path)
                    self._process_sub_containers(sub_def, sub_config_raw, sub_node, sub_instance_path)
                    wrapper_node.add_child(sub_node)
                
                self._alias_active_instance(wrapper_node)
                node.add_child(wrapper_node)
            elif sub_def.is_required:
                # FIX: Use instance_path as parent
                default_node = self._create_default_container_node(sub_def, instance_path)
                node.add_child(default_node)
    
    def _create_container_node(
        self,
        container_def: Optional[EcucContainerDef],
        config_instance: EcucContainerValue,
        path: str
    ) -> ConfigurationNode:
        """Create a ConfigurationNode from definition and configuration instance."""
        
        # Handle Schema Inference (Missing Definition)
        if container_def is None:
            node = ConfigurationNode(
                short_name=config_instance.short_name,
                node_type='container',
                path=path,
                definition_ref=config_instance.definition_ref,
                index=getattr(config_instance, 'index', 0)
            )
            
            # Add parameters from config
            for param_name, param_val in config_instance.parameter_values.items():
                p_node = ConfigurationNode(
                    short_name=param_name,
                    node_type='parameter',
                    path=f"{path}/{param_name}",
                    value=param_val.value,
                    definition_ref=param_val.definition_ref
                )
                node.add_child(p_node)
            
            # Add references from config
            for ref_name, ref_val in config_instance.reference_values.items():
                r_node = ConfigurationNode(
                    short_name=ref_name,
                    node_type='reference',
                    path=f"{path}/{ref_name}",
                    value=ref_val.value_ref,
                    definition_ref=ref_val.definition_ref
                )
                node.add_child(r_node)
            
            # Add sub-containers (grouped by definition name for wrappers)
            subs_by_def = {}
            for sub in config_instance.sub_containers:
                def_name = sub.definition_ref.split('/')[-1] if sub.definition_ref else "Unknown"
                if def_name not in subs_by_def:
                    subs_by_def[def_name] = []
                subs_by_def[def_name].append(sub)
            
            for def_name, subs in subs_by_def.items():
                # Heuristic: Create wrapper only if multiple instances or name suggests multiplicity
                # (e.g. "PortContainer_0" vs "PortContainer")
                is_multiple = len(subs) > 1 or subs[0].short_name != def_name
                
                if is_multiple:
                    wrapper_path = f"{path}/{def_name}"
                    wrapper = ConfigurationNode(
                        short_name=def_name,
                        node_type='container',
                        path=wrapper_path,
                        definition_ref=subs[0].definition_ref,
                        is_wrapper=True
                    )
                    for sub in subs:
                        # FIX: Avoid redundant path segments if sub instance name matches wrapper name
                        if wrapper_path.endswith(f"/{sub.short_name}"):
                            sub_path = wrapper_path
                        else:
                            sub_path = f"{wrapper_path}/{sub.short_name}"
                        sub_node = self._create_container_node(None, sub, sub_path)
                        wrapper.add_child(sub_node)
                    node.add_child(wrapper)
                else:
                    # Single instance, no wrapper
                    sub = subs[0]
                    # FIX: Avoid redundant path segments if sub instance name matches parent path
                    if path.endswith(f"/{sub.short_name}"):
                        sub_path = path
                    else:
                        sub_path = f"{path}/{sub.short_name}"
                    sub_node = self._create_container_node(None, sub, sub_path)
                    node.add_child(sub_node)
                
            return node

        # Standard Logic (Definition Available)
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
        multi_params_source = getattr(config_instance, 'multi_parameter_values', {}) or {}

        for param_name, param_def in container_def.parameters.items():
            is_multi = param_def.upper_multiplicity == -1 or param_def.upper_multiplicity > 1
            multi_param_list = multi_params_source.get(param_name, [])
            
            if is_multi and multi_param_list:
                # Multi-valued parameter: create wrapper node with indexed children
                wrapper_node = ConfigurationNode(
                    short_name=param_name,
                    node_type='parameter',
                    path=f"{path}/{param_name}",
                    definition_ref=param_def.definition_ref,
                    lower_multiplicity=param_def.lower_multiplicity,
                    upper_multiplicity=param_def.upper_multiplicity,
                    is_wrapper=True
                )
                for idx, param_val in enumerate(multi_param_list):
                    child_node = ConfigurationNode(
                        short_name=str(idx),
                        node_type='parameter',
                        path=f"{path}/{param_name}/{idx}",
                        value=param_val.value,
                        definition_ref=param_def.definition_ref,
                        index=idx,
                        param_type=param_def.param_type.value if param_def.param_type else ""
                    )
                    wrapper_node.add_child(child_node)
                node.add_child(wrapper_node)
            else:
                param_node = self._create_parameter_node(
                    param_def,
                    params_source.get(param_name),
                    f"{path}/{param_name}"
                )
                node.add_child(param_node)
        
        # Add unknown parameters from config (if strict=False)
        if not self.strict:
            for param_name, param_val in params_source.items():
                if param_name not in container_def.parameters:
                    # Parameter exists in config but not definition
                    p_node = ConfigurationNode(
                        short_name=param_name,
                        node_type='parameter',
                        path=f"{path}/{param_name}",
                        value=param_val.value,
                        definition_ref=param_val.definition_ref
                    )
                    node.add_child(p_node)

        
        # Add references
        refs_source = getattr(config_instance, 'reference_values', {}) or \
                      {k: v for k, v in getattr(config_instance, 'children', {}).items() if hasattr(v, 'value_ref')}
        multi_refs_source = getattr(config_instance, 'multi_reference_values', {}) or {}
        for ref_name, ref_def in container_def.references.items():
            is_multi = ref_def.upper_multiplicity == -1 or ref_def.upper_multiplicity > 1
            multi_ref_list = multi_refs_source.get(ref_name, [])
            
            # EB Tresos compatibility: If definition says it's multi-valued, but config has only one entry
            # (stored in reference_values), treat it as a list of one to ensure wrapper node creation.
            if is_multi and not multi_ref_list and ref_name in refs_source:
                multi_ref_list = [refs_source[ref_name]]

            if is_multi and multi_ref_list:
                # Multi-valued reference: create wrapper node with indexed children
                wrapper_node = ConfigurationNode(
                    short_name=ref_name,
                    node_type='container',
                    path=f"{path}/{ref_name}",
                    definition_ref=ref_def.definition_ref,
                    lower_multiplicity=ref_def.lower_multiplicity,
                    upper_multiplicity=ref_def.upper_multiplicity,
                    is_wrapper=True
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
                    upper_multiplicity=ref_def.upper_multiplicity,
                    is_wrapper=True
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
            for child in node.children:
                if child.node_type == 'container':
                    ref = child.definition_ref
                    child_counts[ref] = child_counts.get(ref, 0) + 1
            
            # Validate against constraints (simplified - would need def lookup)
            for child in node.children:
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
        for child in node.children:
            self._validate_node_multiplicity(child, errors)

    def _alias_active_instance(self, wrapper_node: ConfigurationNode, variant: Optional[str] = None):
        """Pick the best instance child and alias its sub-features to the wrapper."""
        if not wrapper_node.children:
            return

        active_instance_node = None
        
        # 1. Try variant match if provided (placeholder)
        if variant:
            pass

        # 2. Heuristic: Pick the instance with the MOST sub-container instances
        if not active_instance_node:
            best_node = None
            max_instances = -1
            for child in wrapper_node.children:
                total_instances = 0
                for sub in child.children:
                    if hasattr(sub, 'node_type') and sub.node_type == 'container':
                        total_instances += len(sub.children)
                if total_instances > max_instances:
                    max_instances = total_instances
                    best_node = child
            active_instance_node = best_node if best_node else wrapper_node.children[0]

        # 3. Perform Aliasing - only alias sub-containers, NOT parameters/references
        # This prevents parameter nodes from appearing as siblings of container
        # instances when iterating with wildcards (e.g., AdcGroup/*).
        if active_instance_node:
            for sub_node in active_instance_node.children:
                if sub_node.node_type != 'container':
                    continue
                if not wrapper_node.get_child(sub_node.short_name):
                    wrapper_node.add_alias(sub_node)



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
        configuration: Optional[EcucModuleConfiguration] = None
    ) -> ConfigurationNode:
        """Build unified ConfigurationNode tree from definition and configuration.
        
        Args:
            module_def: Module definition (from ARXML DEF / XDM)
            configuration: Module configuration (from ARXML VALUE), optional
            
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
                # Match by exact name or definition reference
                matching_instances = [c for c in configuration.containers 
                                      if c.short_name == container_name or 
                                      c.definition_ref.endswith(f"/{container_name}")]
            
            if matching_instances:
                for inst in matching_instances:
                    container_nodes = self._build_container_nodes(
                        container_def,
                        inst,
                        parent_path=f"/{module_name}"
                    )
                    for node in container_nodes:
                        root.add_child(node)
            elif container_def.is_required:
                # Build from defaults if required but no instance found
                container_nodes = self._build_container_nodes(
                    container_def,
                    None,
                    parent_path=f"/{module_name}"
                )
                for node in container_nodes:
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
        """
        nodes = []
        container_name = container_def.short_name
        container_path = f"{parent_path}/{container_name}"
        
        if config_instance:
            # Create node from configuration
            node = self._create_container_node(container_def, config_instance, container_path)
            nodes.append(node)
            
            # Handle sub-container instances
            for sub_def_name, sub_def in container_def.sub_containers.items():
                # Find matching sub-container instances
                all_subs = getattr(config_instance, 'sub_containers', []) or []
                if not all_subs:
                    children = getattr(config_instance, 'children', [])
                    if isinstance(children, dict):
                        # For dictionary children, assume values are the subjects
                        all_subs = [v for k, v in children.items() if not hasattr(v, 'value')]
                    else:
                        all_subs = children
                
                matching_subs = [s for s in all_subs 
                                 if getattr(s, 'short_name', None) == sub_def_name or 
                                 getattr(s, 'definition_ref', '').endswith(f"/{sub_def_name}")]
                
                if matching_subs:
                    for sub_config_raw in matching_subs:
                        sub_nodes = self._build_container_nodes(
                            sub_def, sub_config_raw, container_path
                        )
                        for sub_node in sub_nodes:
                            node.add_child(sub_node)
                elif sub_def.is_required:
                    # Create from defaults if required
                    default_node = self._create_default_container_node(sub_def, container_path)
                    node.add_child(default_node)
        else:
            # No config instance - create from defaults if required
            if container_def.is_required:
                node = self._create_default_container_node(container_def, container_path)
                nodes.append(node)
        
        return nodes
    
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
            upper_multiplicity=container_def.upper_multiplicity
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
        for ref_name, ref_def in container_def.references.items():
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

"""
Symbol Table for Cross-Module References
Provides global access to all loaded module configurations.
"""
from typing import Dict, Optional, Any, List
from dataclasses import dataclass, field


@dataclass
class ConfigurationNode:
    """Unified node representing either a container or parameter value.
    
    This is the core data structure for the Overlay mechanism.
    """
    short_name: str
    node_type: str  # 'module', 'container', 'parameter', 'reference'
    path: str  # Absolute path like /Mcu/McuConfig/McuClockSource
    
    # Value (for parameters)
    value: Any = None
    default_value: Any = None
    
    # Definition reference
    definition_ref: str = ""
    
    # Children (for containers) - now a list to support multiple nodes with same name
    children: List['ConfigurationNode'] = field(default_factory=list)
    
    # Lookup map for fast name-based access (returns the latest added child if name conflicts)
    _children_by_name: Dict[str, 'ConfigurationNode'] = field(default_factory=dict, repr=False)
    
    # Parent reference
    parent: Optional['ConfigurationNode'] = field(default=None, repr=False)
    
    # Metadata from definition
    lower_multiplicity: int = 0
    upper_multiplicity: int = 1
    param_type: str = ""  # For parameters
    
    # Instance index
    index: int = 0
    
    # Is this a wrapper node (OverlayEngine implementation detail)?
    is_wrapper: bool = False
    
    def get_value(self) -> Any:
        """Get value with fallback to default"""
        if self.value is not None:
            return self.value
        return self.default_value
    
    def get_child(self, name: str) -> Optional['ConfigurationNode']:
        """Get child node by name"""
        return self._children_by_name.get(name)
    
    def get_children_list(self) -> List['ConfigurationNode']:
        """Get all children as a list"""
        return self.children
    
    def get_children_recursive(self) -> List['ConfigurationNode']:
        """Recursively get all children/descendants"""
        results = []
        for child in self.children:
            results.append(child)
            results.extend(child.get_children_recursive())
        return results
    
    def add_child(self, node: 'ConfigurationNode'):
        """Add a child node"""
        node.parent = self
        self.children.append(node)
        self._children_by_name[node.short_name] = node

    def add_alias(self, node: 'ConfigurationNode'):
        """Add a child reference WITHOUT changing the node's parent pointer.

        Used by _alias_active_instance to make sub-containers accessible
        from the wrapper node while preserving the original parent chain
        needed for correct '..' (parent axis) XPath navigation.

        Note: Aliases are added ONLY to the lookup map (_children_by_name),
        NOT to the main children list. This ensures that:
        1. Wildcard iteration (count(*)) only counts distinct structural children (instances)
        2. Named lookup (node.get_child('name')) still works via the map
        """
        # Do not append to self.children to avoid duplication in iteration
        # self.children.append(node) 
        self._children_by_name[node.short_name] = node

    def __post_init__(self):
        # If children were passed as a dict during construction (for legacy reasons), 
        # convert them to list and populate lookup
        if isinstance(self.children, dict):
            legacy_dict = self.children
            self.children = []
            self._children_by_name = {}
            for name, node in legacy_dict.items():
                self.add_child(node)
        elif not hasattr(self, '_children_by_name') or self._children_by_name is None:
            self._children_by_name = {}
            for node in self.children:
                self._children_by_name[node.short_name] = node

    def __str__(self):
        """String representation showing value or short name"""
        val = self.get_value()
        if val is not None:
            return str(val)
        return self.short_name



class SymbolTable:
    """Global registry for all loaded module configurations.
    
    Enables cross-module references like as:modconf('Port') from Mcu templates.
    """
    
    def __init__(self):
        # Module name -> root ConfigurationNode
        self._modules: Dict[str, ConfigurationNode] = {}
        # Absolute path -> ConfigurationNode (cache for fast lookup)
        self._path_index: Dict[str, ConfigurationNode] = {}
    
    def register_module(self, module_name: str, root_node: ConfigurationNode):
        """Register a module's configuration tree"""
        self._modules[module_name.lower()] = root_node
        self._index_node(root_node)
    
    def _index_node(self, node: ConfigurationNode):
        """Recursively index all nodes by their path"""
        self._path_index[node.path] = node
        for child in node.children:
            self._index_node(child)
    
    def get_module(self, module_name: str) -> Optional[ConfigurationNode]:
        """Get a module's root configuration node by name."""
        if not module_name:
            return None
        
        name_lower = module_name.lower()
        res = self._modules.get(name_lower)
        if res:
            return res
            
        # Fallback for Resource module if not explicitly loaded
        if name_lower == 'resource':
            # Note: builtins will populate this if called from Renderer
            # For now, return None if not registered to avoid circular dependency
            return self._modules.get('resource')
            
        return None

    
    def get_by_path(self, path: str) -> Optional[ConfigurationNode]:
        """Get any node by its absolute path"""
        return self._path_index.get(path)
    
    def resolve_reference(self, ref_path: str) -> Optional[ConfigurationNode]:
        """Resolve a reference path to its target node.

        Args:
            ref_path: Reference path like /AUTOSAR/EcucDefs/Mcu/McuConfig/...

        Returns:
            Target ConfigurationNode or None
        """
        from .renderer import _debug_log
        _debug_log(f"resolve_reference: Resolving '{ref_path}'")

        # Try direct path lookup first
        if ref_path in self._path_index:
            _debug_log(f"resolve_reference: Found exact match in path_index")
            return self._path_index[ref_path]

        # Cleanup path
        parts = [p for p in ref_path.split('/') if p]
        if not parts:
            return None

        # Identify candidate modules.
        # ARXML references often wrap the module name multiple times or use /AUTOSAR prefix.
        # We look for ANY part that matches a registered module name.
        candidates = []
        for i, part in enumerate(parts):
            mod = self.get_module(part)
            if mod:
                candidates.append((mod, i))
        
        if not candidates:
            _debug_log(f"resolve_reference: No candidate modules found for parts: {parts}")
            return None

        # Successively try to resolve starting from each candidate module
        for root, start_idx in candidates:
            _debug_log(f"resolve_reference: Attempting resolution from module '{root.short_name}' (start_idx={start_idx})")
            
            # Recursive search function to skip wrappers and handle structural mismatches
            def navigate(current: ConfigurationNode, parts_to_find: list) -> Optional[ConfigurationNode]:
                if not parts_to_find:
                    return current
                
                target = parts_to_find[0]
                remaining = parts_to_find[1:]
                
                # Try direct child
                child = current.get_child(target)
                if child:
                    return navigate(child, remaining)
                
                # CASE 1: Skip "structural" wrapper nodes in the tree
                # If current has children that are wrappers or have the same name as current,
                # explore them if they might contain our target.
                for child_node in current.children:
                    # If the child looks like a structural node (wrapper or same name alias),
                    # try to see if it contains the target.
                    if child_node.node_type == 'container':
                        # OPTION A: The child IS the target (but maybe its name is slightly different, dealt with above)
                        # OPTION B: The child is a wrapper node - try to look INSIDE it for 'target'
                        res = navigate(child_node, parts_to_find)
                        if res: return res
                
                # CASE 2: The ARXML path might have redundant segments (like /Can/Can/...)
                # If the current node's name matches the target, skip this segment and continue from here
                if current.short_name.lower() == target.lower():
                    return navigate(current, remaining)
                
                return None

            # Start navigation skipping the module name part itself
            result = navigate(root, parts[start_idx + 1:])
            if result:
                _debug_log(f"resolve_reference: Successfully resolved to '{result.path}'")
                return result

        _debug_log(f"resolve_reference: Resolution FAILED for '{ref_path}'")
        return None
    
    def get_all_modules(self) -> List[str]:
        """Get list of all registered module names"""
        return list(self._modules.keys())
    
    def clear(self):
        """Clear all registered modules"""
        self._modules.clear()
        self._path_index.clear()

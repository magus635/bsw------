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
        # Cycle Prevention: Check if adding 'node' as a child would create a cycle.
        # This happens if 'node' is already an ancestor of 'self'.
        ancestor = self
        while ancestor:
            if ancestor == node:
                from .renderer import _debug_log
                _debug_log(f"ERROR_CYCLE_DETECTED: Computed parent {self.short_name} (path={self.path}) is a descendant of child {node.short_name} (path={node.path}). Rejecting add_child to prevent cycle.")
                return
            ancestor = ancestor.parent

        # FIX: If the child's path is the same as the parent's path, and parent is a wrapper,
        # it means this child instance effectively 'replaces' the wrapper in the hierarchy.
        # In this case, the child's logical parent should be the wrapper's parent.
        if node.path == self.path and self.is_wrapper:
            node.parent = self.parent
        else:
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
        # Modules that have code generation templates (MODULE-DEF in XDM terms)
        # Only these appear when enumerating /AUTOSAR/TOP-LEVEL-PACKAGES/*/ELEMENTS/*
        self._template_modules: set = set()
    
    def register_module(self, module_name: str, root_node: ConfigurationNode):
        """Register a module's configuration tree"""
        self._modules[module_name.lower()] = root_node
        self._index_node(root_node)
    
    def _index_node(self, node: ConfigurationNode):
        """Recursively index all nodes by their path"""
        self._path_index[node.path] = node
        for child in node.children:
            self._index_node(child)

    def rebuild_path_index(self):
        """Rebuild the absolute-path → node cache from the registered module trees.

        The path index is a cache keyed by ``node.path``. After a rename or move
        the node paths change, leaving the cache stale (old paths still resolving
        to moved/renamed nodes). Callers that mutate the tree in place must invoke
        this to refresh the cache so ``get_by_path`` / ``resolve_reference``
        return current data instead of pointing at outdated paths.
        """
        self._path_index.clear()
        for root in self._modules.values():
            self._index_node(root)

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
        # Try direct path lookup first
        if ref_path in self._path_index:
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
            return None

        # Strategy: Successively try to resolve starting from each candidate module.
        # ARXML paths might have wrapper segments like /Os/Os/Task1 where we have /Os/Os/OsTask/Task1.
        for root, start_idx in candidates:
            # Simple path traversal first
            remaining_parts = parts[start_idx + 1:]
            
            def find_path(current: ConfigurationNode, parts_to_find: List[str]) -> Optional[ConfigurationNode]:
                if not parts_to_find:
                    return current
                
                target = parts_to_find[0]
                rest = parts_to_find[1:]
                
                # Try direct child
                child = current.get_child(target)
                if child:
                    return find_path(child, rest)
                
                # Try case-insensitive child lookup
                for c_node in current.children:
                    if c_node.short_name.lower() == target.lower():
                        return find_path(c_node, rest)
                
                # CASE 1: Skip intermediate container nodes if target might be inside
                # (e.g. tree has /OsTask wrapper, ARXML ref is /Os/Task1)
                # Also traverse non-wrapper instance containers to handle
                # wrapper→instance→wrapper chains (e.g. Mcu module references)
                for c_node in current.children:
                    if c_node.node_type == 'container' and c_node.children:
                        res = find_path(c_node, parts_to_find)
                        if res: return res
                
                # CASE 2: Skip redundant segments in the ARXML path
                # (e.g. ARXML ref is /Os/Os/Task1, tree is /Os/OsTask/Task1)
                if current.short_name.lower() == target.lower():
                    return find_path(current, rest)
                
                return None

            result = find_path(root, remaining_parts)
            if result:
                return result

        return None

        return None
    
    def get_all_modules(self) -> List[str]:
        """Get list of all registered module names"""
        return list(self._modules.keys())

    def mark_template_module(self, module_name: str):
        """Mark a module as having code generation templates (MODULE-DEF in XDM)."""
        self._template_modules.add(module_name.lower())

    def get_template_modules(self) -> List[str]:
        """Get module names that have code generation templates.

        If no modules have been explicitly marked, fall back to all modules
        (backward compatibility for cases where marking isn't done).
        """
        if self._template_modules:
            return [m for m in self._modules.keys() if m in self._template_modules]
        return list(self._modules.keys())

    def clear(self):
        """Clear all registered modules"""
        self._modules.clear()
        self._path_index.clear()
        self._template_modules.clear()

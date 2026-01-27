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
    
    # Children (for containers)
    children: Dict[str, 'ConfigurationNode'] = field(default_factory=dict)
    
    # Parent reference
    parent: Optional['ConfigurationNode'] = field(default=None, repr=False)
    
    # Metadata from definition
    lower_multiplicity: int = 0
    upper_multiplicity: int = 1
    param_type: str = ""  # For parameters
    
    def get_value(self) -> Any:
        """Get value with fallback to default"""
        if self.value is not None:
            return self.value
        return self.default_value
    
    def get_child(self, name: str) -> Optional['ConfigurationNode']:
        """Get child node by name"""
        return self.children.get(name)
    
    def get_children_list(self) -> List['ConfigurationNode']:
        """Get all children as a list"""
        return list(self.children.values())
    
    def get_children_recursive(self) -> List['ConfigurationNode']:
        """Recursively get all children/descendants"""
        results = []
        for child in self.children.values():
            results.append(child)
            results.extend(child.get_children_recursive())
        return results
    
    def add_child(self, node: 'ConfigurationNode'):
        """Add a child node"""
        node.parent = self
        self.children[node.short_name] = node

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
        for child in node.children.values():
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
        _debug_log(f"resolve_reference: Available modules: {list(self._modules.keys())}")

        # Try direct path lookup first
        if ref_path in self._path_index:
            _debug_log(f"resolve_reference: Found in path_index")
            return self._path_index[ref_path]



        # Try to parse and resolve
        parts = [p for p in ref_path.split('/') if p]
        if not parts:
            return None


        # Check if it starts with a known module

        for module_name, root in self._modules.items():
            # Module names are stored in lowercase, so compare case-insensitively
            p0_lower = parts[0].lower()
            p1_lower = parts[1].lower() if len(parts) > 1 else ""
            module_name_lower = module_name.lower()

            is_match = False
            start_idx = 0

            if p0_lower == module_name_lower:
                is_match = True
                start_idx = 1
            elif p1_lower == module_name_lower:
                # Handle /AUTOSAR/EcucDefs/Mcu or similar prefixes where module is second
                is_match = True
                start_idx = 2

            if is_match:
                _debug_log(f"resolve_reference: Matched module '{module_name}', navigating from index {start_idx}")
                # Navigate from module root
                current = root
                for part in parts[start_idx:]:
                    _debug_log(f"resolve_reference: Looking for child '{part}' in '{current.short_name}' (children: {list(current.children.keys())})")
                    child = current.get_child(part)
                    if child is None:
                        # Fallback: check for wrapper containers (EB Tresos structural mismatch)
                        # If 'part' is not found directly, check if it exists inside any child container
                        # (skipping one level of hierarchy often introduced by container definition wrappers)
                        found_in_wrapper = False
                        for wrapper in current.children.values():
                            if wrapper.node_type == 'container':
                                inner = wrapper.get_child(part)
                                if inner:
                                    child = inner
                                    found_in_wrapper = True
                                    _debug_log(f"resolve_reference: Found '{part}' in wrapper '{wrapper.short_name}'")
                                    break

                        if not found_in_wrapper:
                            _debug_log(f"resolve_reference: Child '{part}' NOT FOUND")
                            return None

                    current = child
                _debug_log(f"resolve_reference: Successfully resolved to '{current.path}'")
                return current

        _debug_log(f"resolve_reference: No matching module found for path '{ref_path}'")
        return None
    
    def get_all_modules(self) -> List[str]:
        """Get list of all registered module names"""
        return list(self._modules.keys())
    
    def clear(self):
        """Clear all registered modules"""
        self._modules.clear()
        self._path_index.clear()

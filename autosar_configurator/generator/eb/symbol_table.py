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
    
    def add_child(self, node: 'ConfigurationNode'):
        """Add a child node"""
        node.parent = self
        self.children[node.short_name] = node


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
        self._modules[module_name] = root_node
        self._index_node(root_node)
    
    def _index_node(self, node: ConfigurationNode):
        """Recursively index all nodes by their path"""
        self._path_index[node.path] = node
        for child in node.children.values():
            self._index_node(child)
    
    def get_module(self, module_name: str) -> Optional[ConfigurationNode]:
        """Get a module's root configuration node by name.
        
        This is the implementation of as:modconf('ModuleName').
        """
        return self._modules.get(module_name)
    
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
        
        # Try to parse and resolve
        parts = [p for p in ref_path.split('/') if p]
        if not parts:
            return None
        
        # Check if it starts with a known module
        for module_name, root in self._modules.items():
            if parts[0] == module_name or (len(parts) > 1 and parts[1] == module_name):
                # Navigate from module root
                current = root
                start_idx = 1 if parts[0] == module_name else 2
                for part in parts[start_idx:]:
                    child = current.get_child(part)
                    if child is None:
                        return None
                    current = child
                return current
        
        return None
    
    def get_all_modules(self) -> List[str]:
        """Get list of all registered module names"""
        return list(self._modules.keys())
    
    def clear(self):
        """Clear all registered modules"""
        self._modules.clear()
        self._path_index.clear()

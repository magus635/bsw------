"""
Built-in Functions for EB Template Engine

Implements the required function library:
- Node functions: node:ref, node:path, node:name, node:value, node:exists, node:current
- Model functions: as:modconf, as:container
- Number functions: num:i, num:inttohex, num:is_nan
- String functions: string:concat, string:split, string:trim, string:upper, string:lower, string:match
"""
import re
from typing import Any, List, Optional, Callable, TYPE_CHECKING

if TYPE_CHECKING:
    from .symbol_table import ConfigurationNode, SymbolTable
    from .context import ContextStack


class BuiltinFunctions:
    """Registry and implementation of all built-in functions"""
    
    def __init__(self, symbol_table: 'SymbolTable', context_stack: 'ContextStack'):
        self.symbol_table = symbol_table
        self.context_stack = context_stack
        
        # Build function registry
        self._functions = {
            # Node functions
            'node:value': self.node_value,
            'node:name': self.node_name,
            'node:path': self.node_path,
            'node:ref': self.node_ref,
            'node:exists': self.node_exists,
            'node:current': self.node_current,
            'node:order': self.node_order,
            
            # EcuC interface functions (per spec 4.1/4.2)
            'ecuC:getParamValue': self.ecuc_get_param_value,
            'ecuC:getContainers': self.ecuc_get_containers,
            'ecuC:hasParam': self.node_exists,  # Alias
            'ecuC:getReference': self.ecuc_get_reference,
            
            # Model functions
            'as:modconf': self.as_modconf,
            'as:container': self.as_container,
            
            # Number functions
            'num:i': self.num_i,
            'num:inttohex': self.num_inttohex,
            'num:is_nan': self.num_is_nan,
            
            # String functions
            'string:concat': self.string_concat,
            'string:split': self.string_split,
            'string:trim': self.string_trim,
            'string:upper': self.string_upper,
            'string:lower': self.string_lower,
            'string:match': self.string_match,
            'string:length': self.string_length,
            'string:contains': self.string_contains,
            
            # Count function
            'count': self.count,
            
            # Boolean helpers
            'not': self.logical_not,
            
            # Variant functions (MUST-Minimal per spec 4.4)
            'variant:check': self.variant_check,
            'variant:exists': self.variant_exists,
        }
    
    def get(self, name: str) -> Optional[Callable]:
        """Get a function by name"""
        return self._functions.get(name)
    
    def has(self, name: str) -> bool:
        """Check if a function exists"""
        return name in self._functions
    
    def call(self, name: str, *args) -> Any:
        """Call a function by name with arguments"""
        func = self._functions.get(name)
        if func is None:
            raise NameError(f"Unknown function: {name}")
        return func(*args)
    
    # ========== Node Functions ==========
    
    def node_value(self, node_or_path: Any) -> Any:
        """Get the value of a node (with default fallback).
        ...
        """
        node = node_or_path
        path = None
        
        # Auto-resolve string paths
        if isinstance(node, str):
            path = node
            if path.startswith('/'):
                # Absolute path
                node = self.symbol_table.get_by_path(path)
            else:
                # Relative path
                current = self.context_stack.current_node()
                if current:
                    try:
                        # Attempt simple child lookup first
                        # For full XPath support, we rely on the renderer evaluating XPaths
                        # But bare paths passed as strings end up here.
                        # Simple traversal for now:
                        parts = path.split('/')
                        node = current
                        for part in parts:
                            if node is None: break
                            # Evaluate predicate? No, simplified
                            node = node.get_child(part)
                    except:
                        node = None
                else:
                    node = None
        
        if node is None:
            # If resolution failed, but input was a string, assume input IS the value
            # Note: We check the original input variable 'node_or_path' which is passed as 'node'
            if isinstance(path, str): # path was set if input was str
                return path
            # If input was not str, but node became None (shouldn't happen if we didn't enter first if)
            return None
        
        # Robustness: If node is already a value (not a ConfigurationNode), return it
        if not hasattr(node, 'get_value') and not hasattr(node, 'value'):
            return node
            
        value = node.get_value() if hasattr(node, 'get_value') else node.value
        
        param_type = getattr(node, 'param_type', None)
        if param_type:
            param_type = param_type.upper()
            
            # Boolean -> AUTOSAR semantic mapping
            if 'BOOLEAN' in param_type:
                bool_val = self._parse_boolean(value)
                
                # Determine if feature or runtime boolean
                # Feature booleans typically have names ending with Enable/Disable/Dev/Support
                is_feature = any(kw in node.short_name.upper() for kw in 
                    ['ENABLE', 'DISABLE', 'DEV', 'SUPPORT', 'AVAILABLE', 'PRESENT'])
                
                if is_feature:
                    # Feature flag: STD_ON / STD_OFF
                    return 'STD_ON' if bool_val else 'STD_OFF'
                else:
                    # Runtime boolean: TRUE / FALSE
                    return 'TRUE' if bool_val else 'FALSE'
            
            # Enum -> ShortName (already string)
            # Reference -> Resolve
            if 'REFERENCE' in param_type or node.node_type == 'reference':
                # Return the target path (string) or object?
                # Spec says "Reference: resolved target object"
                # But typically node:value returns the value stored in the node.
                # For ref, value is the path string. 
                # node:ref() function is used to get the object.
                # EB Spec 8.1 "ecuC.getReference -> TargetObject".
                # node:value() usually returns the string path.
                return value
        
        return value
    
    def _parse_boolean(self, value: Any) -> bool:
        """Parse value as boolean"""
        if isinstance(value, bool):
            return value
        if isinstance(value, str):
            return value.lower() in ('true', '1', 'yes', 'on', 'std_on')
        if isinstance(value, (int, float)):
            return bool(value)
        return False
    
    def node_name(self, node: 'ConfigurationNode') -> str:
        """Get the short name of a node"""
        if node is None:
            return ""
        return node.short_name
    
    def node_path(self, node: 'ConfigurationNode') -> str:
        """Get the absolute path of a node"""
        if node is None:
            return ""
        return node.path
    
    def node_ref(self, node: 'ConfigurationNode') -> Optional['ConfigurationNode']:
        """Resolve a reference node to its target.
        
        For reference-type nodes, this returns the node being referenced.
        """
        if node is None or node.node_type != 'reference':
            return None
        
        ref_path = node.get_value()
        if not ref_path:
            return None
        
        return self.symbol_table.resolve_reference(ref_path)
    
    def node_exists(self, path_or_node) -> bool:
        """Check if a path or node exists"""
        if isinstance(path_or_node, str):
            if path_or_node.startswith('/'):
                return self.symbol_table.get_by_path(path_or_node) is not None
            else:
                current = self.context_stack.current_node()
                if current:
                    return current.get_child(path_or_node) is not None
                return False
        return True  # Node object exists
    
    def node_current(self) -> Optional['ConfigurationNode']:
        """Get the current context node"""
        return self.context_stack.current_node()
    
    def node_order(self, nodes: List['ConfigurationNode'], key: str = 'short_name') -> List['ConfigurationNode']:
        """Sort nodes by a property"""
        if not nodes:
            return []
        return sorted(nodes, key=lambda n: getattr(n, key, n.short_name))
    
    # ========== Model Functions ==========
    
    def as_modconf(self, module_name: str) -> Optional['ConfigurationNode']:
        """Get a module's configuration root by name.
        
        This is the key function for cross-module access.
        Example: as:modconf('Mcu') returns the Mcu module root.
        """
        # Strip quotes if present
        if module_name.startswith(("'", '"')) and module_name.endswith(("'", '"')):
            module_name = module_name[1:-1]
        
        return self.symbol_table.get_module(module_name)
    
    def as_container(self, path: str) -> Optional['ConfigurationNode']:
        """Get a container by path from current context"""
        current = self.context_stack.current_node()
        if current is None:
            return None
        
        # Navigate from current node
        parts = [p for p in path.split('/') if p]
        node = current
        for part in parts:
            child = node.get_child(part)
            if child is None:
                return None
            node = child
        return node
    
    # ========== Number Functions ==========
    
    def num_i(self, value: Any) -> int:
        """Convert value to integer"""
        if value is None:
            return 0
        if isinstance(value, int):
            return value
        if isinstance(value, float):
            return int(value)
        if isinstance(value, str):
            # Handle hex strings
            value = value.strip()
            if value.lower().startswith('0x'):
                return int(value, 16)
            try:
                return int(value)
            except ValueError:
                return 0
        # If it's a node, get its value
        if hasattr(value, 'get_value'):
            return self.num_i(value.get_value())
        if hasattr(value, 'value'):
            return self.num_i(value.value)
        return 0
    
    def num_inttohex(self, value: Any, width: int = 0) -> str:
        """Convert integer to hex string.
        
        Args:
            value: Integer value
            width: Minimum width (with leading zeros)
            
        Returns:
            Hex string like "0x000A"
        """
        int_val = self.num_i(value)
        if width > 0:
            # Format with leading zeros
            hex_str = format(int_val, f'0{width}X')
        else:
            hex_str = format(int_val, 'X')
        return f"0x{hex_str}"
    
    def num_is_nan(self, value: Any) -> bool:
        """Check if value is not a number"""
        try:
            float(value)
            return False
        except (ValueError, TypeError):
            return True
    
    # ========== String Functions ==========
    
    def string_concat(self, *args) -> str:
        """Concatenate strings"""
        return "".join(str(a) for a in args)
    
    def string_split(self, s: str, delimiter: str = " ") -> List[str]:
        """Split string by delimiter"""
        if not isinstance(s, str):
            s = str(s)
        return s.split(delimiter)
    
    def string_trim(self, s: str) -> str:
        """Trim whitespace from string"""
        if not isinstance(s, str):
            s = str(s)
        return s.strip()
    
    def string_upper(self, s: str) -> str:
        """Convert string to uppercase"""
        if not isinstance(s, str):
            s = str(s)
        return s.upper()
    
    def string_lower(self, s: str) -> str:
        """Convert string to lowercase"""
        if not isinstance(s, str):
            s = str(s)
        return s.lower()
    
    def string_match(self, s: str, pattern: str) -> bool:
        """Check if string matches regex pattern"""
        if not isinstance(s, str):
            s = str(s)
        try:
            return bool(re.search(pattern, s))
        except re.error:
            return False
    
    def string_length(self, s: str) -> int:
        """Get string length"""
        if not isinstance(s, str):
            s = str(s)
        return len(s)
    
    def string_contains(self, s: str, substring: str) -> bool:
        """Check if string contains substring"""
        if not isinstance(s, str):
            s = str(s)
        return substring in s
    
    # ========== Other Functions ==========
    
    def count(self, items) -> int:
        """Count items in a collection or node's children"""
        if items is None:
            return 0
        if isinstance(items, list):
            return len(items)
        if hasattr(items, 'children'):
            return len(items.children)
        if hasattr(items, '__len__'):
            return len(items)
        return 0
    
    def logical_not(self, value: Any) -> bool:
        """Logical NOT"""
        return not bool(value)
    
    # ========== Variant Functions (MUST-Minimal per spec 4.4) ==========
    
    def variant_check(self, condition: str = "") -> bool:
        """Check a Variant condition.
        
        Per spec 4.4: If Project has no Variant information,
        all Variant judgments return true.
        
        This is a compatibility fuse.
        """
        # Currently no variant info loaded -> always return true
        return True
    
    def variant_exists(self, variant_name: str = "") -> bool:
        """Check if a Variant exists.
        
        Returns true if no variant info (compatibility mode).
        """
        return True
    
    # ========== EcuC Interface Functions (per spec 4.1/4.2) ==========
    
    def ecuc_get_param_value(self, path: str) -> Any:
        """Get parameter value by path.
        
        Per spec 4.1: If parameter does not exist, throw diagnosable error (not silent fail).
        
        Args:
            path: Path to parameter
            
        Returns:
            TypedValue or raises error
        """
        # Start from current context
        current = self.context_stack.current_node()
        if current is None:
            from .errors import DanglingReferenceError
            raise DanglingReferenceError(path, "ecuC:getParamValue called with no context")
        
        # Navigate to parameter
        parts = [p for p in path.split('/') if p]
        node = current
        for part in parts:
            if node is None:
                break
            node = node.get_child(part)
        
        if node is None:
            from .errors import DanglingReferenceError
            raise DanglingReferenceError(path, f"Parameter not found from {current.path}")
        
        return self.node_value(node)
    
    def ecuc_get_containers(self, container_path: str) -> List['ConfigurationNode']:
        """Get containers by path.
        
        Per spec 4.2: Returns list of containers with stable index.
        
        Args:
            container_path: Path to container definition
            
        Returns:
            List of Container objects with index attribute
        """
        current = self.context_stack.current_node()
        if current is None:
            return []
        
        # Navigate to container parent
        parts = [p for p in container_path.split('/') if p]
        node = current
        for part in parts[:-1]:
            if node is None:
                return []
            node = node.get_child(part)
        
        if node is None:
            return []
        
        # Get all children matching the container name
        target_name = parts[-1] if parts else ""
        containers = []
        for child in node.children.values():
            if child.short_name.startswith(target_name) or target_name == "*":
                containers.append(child)
        
        return containers
    
    def ecuc_get_reference(self, ref_path: str) -> Optional['ConfigurationNode']:
        """Get reference target by path.
        
        Per spec 8.1: Must support ECUC Reference resolution.
        Per spec 8.2: Must allow cross-module access.
        
        Args:
            ref_path: Path to reference parameter
            
        Returns:
            Target object or raises error
        """
        # Get the reference node first
        current = self.context_stack.current_node()
        if current is None:
            from .errors import DanglingReferenceError
            raise DanglingReferenceError(ref_path, "No context for reference resolution")
        
        # Navigate to reference
        parts = [p for p in ref_path.split('/') if p]
        node = current
        for part in parts:
            if node is None:
                break
            node = node.get_child(part)
        
        if node is None:
            from .errors import DanglingReferenceError
            raise DanglingReferenceError(ref_path, f"Reference not found from {current.path}")
        
        # Resolve the reference to its target
        return self.node_ref(node)


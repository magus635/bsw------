"""
Built-in Functions for EB Template Engine

Implements the required function library:
- Node functions: node:ref, node:path, node:name, node:value, node:exists, node:current
- Model functions: as:modconf, as:container
- Number functions: num:i, num:inttohex, num:is_nan
- String functions: string:concat, string:split, string:trim, string:upper, string:lower, string:match
"""
import re
from typing import Any, List, Optional, Callable, Union, TYPE_CHECKING

if TYPE_CHECKING:
    from .symbol_table import ConfigurationNode, SymbolTable
    from .context import ContextStack


class BuiltinFunctions:
    """Registry and implementation of all built-in functions"""
    
    def __init__(self, symbol_table: 'SymbolTable', context_stack: 'ContextStack'):
        self.symbol_table = symbol_table
        self.context_stack = context_stack
        
        # ECU resource dictionary for ecu:get function
        self.ecu_resources = {}
        
        # Build function registry
        self._functions = {
            # Node functions
            'node:value': self.node_value,
            'node:name': self.node_name,
            'node:path': self.node_path,
            'node:ref': self.node_ref,
            'node:exists': self.node_exists,
            'node:refexists': self.node_refexists,
            'node:current': self.node_current,
            'node:order': self.node_order,
            'node:fallback': self.node_fallback,
            
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
            'num:hextoint': self.num_hextoint,
            'num:is_nan': self.num_is_nan,
            'num:isnumber': self.num_isnumber,  # NEW: Check if value is a number
            
            # String functions
            'string:concat': self.string_concat,
            'string:split': self.string_split,
            'string:trim': self.string_trim,
            'string:upper': self.string_upper,
            'string:lower': self.string_lower,
            'string:match': self.string_match,
            'string:length': self.string_length,
            'string:contains': self.string_contains,
            'string:substring': self.string_substring,
            'string:substring-before': self.string_substring_before,
            'string:substring-after': self.string_substring_after,
            
            # Text functions (Namespace aliases)
            'text:split': self.string_split,
            'text:join': self.string_concat,
            'text:tolower': self.string_lower,
            'text:toupper': self.string_upper,
            
            # XPath standard function aliases (for compatibility)
            'string': self.to_string,  # XPath string() type conversion
            'string-length': self.string_length,
            'concat': self.string_concat,
            'contains': self.string_contains,
            'substring': self.string_substring,
            'substring-before': self.string_substring_before,
            'substring-after': self.string_substring_after,
            'normalize-space': self.normalize_space,
            
            # Count function
            'count': self.count,
            
            # Boolean helpers
            'not': self.logical_not,
            
            # Variant functions (MUST-Minimal per spec 4.4)
            'variant:name': self.variant_name,
            'variant:check': self.variant_check,
            'variant:exists': self.variant_exists,
            
            # ECU Resource functions
            'ecu:get': self.ecu_get,
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
    
    def node_name(self, node: Optional['ConfigurationNode'] = None) -> str:
        """Get the short name of a node"""
        if node is None:
            node = self.context_stack.current_node()
        if node is None:
            return ""
        return node.short_name
    
    def node_path(self, node: Optional['ConfigurationNode'] = None) -> str:
        """Get the absolute path of a node"""
        if node is None:
            node = self.context_stack.current_node()
        if node is None:
            return ""
        return node.path

    
    def node_ref(self, path_or_node: Union[str, 'ConfigurationNode']) -> Optional['ConfigurationNode']:
        """Resolve a reference node or path to its target node.
        
        Args:
            path_or_node: Either a ConfigurationNode (of type 'reference') or a path string.
        """
        if path_or_node is None:
            return None
            
        if isinstance(path_or_node, str):
            # If it's a string, attempt to resolve it as a reference path
            return self.symbol_table.resolve_reference(path_or_node)
            
        # If it's a node, it must be of type 'reference'
        if path_or_node.node_type != 'reference':
            # EB Tresos quirk: sometimes node:ref is called on a node that IS a reference target
            # return it as is or return None? Usually standard is it must be a reference parameter.
            return None
        
        ref_path = path_or_node.get_value()
        if not ref_path:
            return None
        
        return self.symbol_table.resolve_reference(ref_path)
    
    def node_exists(self, path_or_node) -> bool:
        """Check if a path or node exists"""
        if path_or_node is None:
            return False
        if isinstance(path_or_node, str):
            if path_or_node.startswith('/'):
                return self.symbol_table.get_by_path(path_or_node) is not None
            else:
                current = self.context_stack.current_node()
                if current:
                    return current.get_child(path_or_node) is not None
                return False
        return True  # Node object exists
    
    def node_refexists(self, path_or_node) -> bool:
        """Check if a reference exists and its target exists"""
        target = self.node_ref(path_or_node)
        return target is not None
    
    def node_current(self) -> Optional['ConfigurationNode']:
        """Get the current context node"""
        return self.context_stack.current_node()
    
    def node_fallback(self, value: Any, fallback: Any = None) -> Any:
        """Return value if it is not None/empty, otherwise return fallback.
        
        This is used in XPath expressions like:
            node:fallback(SomeParam, 0)
            node:fallback(../ParentParam, 'default')
        
        Args:
            value: The value to check (can be a node, parameter value, or None)
            fallback: The fallback value to return if value is None/empty
        
        Returns:
            value if non-empty, otherwise fallback
        """
        # If value is a ConfigurationNode, get its value
        if hasattr(value, 'get_value'):
            val = value.get_value()
        elif hasattr(value, 'value'):
            val = value.value
        else:
            val = value
        
        # Check if value is "empty" (None, empty string, or empty list)
        if val is None or val == '' or val == []:
            return fallback
        
        return val
    
    def node_order(self, nodes: Any, sort_expr: Optional[str] = None) -> List['ConfigurationNode']:
        """Sort nodes by a property or expression.
        
        Args:
            nodes: List of nodes to sort
            sort_expr: XPath expression to evaluate for each node as sort key
        """
        if nodes is None:
            return []
        
        # If it's a single node, wrap it in a list
        if hasattr(nodes, 'short_name') and not isinstance(nodes, list):
            nodes = [nodes]
        
        if not isinstance(nodes, (list, tuple)):
            try:
                nodes = list(nodes)
            except TypeError:
                return []
        
        if not nodes:
            return []
        
        if sort_expr is None:
            # Default sort by short_name
            return sorted(nodes, key=lambda n: n.short_name if hasattr(n, 'short_name') else '')

        # If sort_expr got evaluated to a ConfigurationNode (because XPath was evaluated),
        # it means the sorting key couldn't be determined properly - fall back to short_name
        if hasattr(sort_expr, 'short_name'):
            # sort_expr is actually a ConfigurationNode, not a string expression
            return sorted(nodes, key=lambda n: n.short_name if hasattr(n, 'short_name') else '')
        
        # Ensure sort_expr is a string
        if not isinstance(sort_expr, str):
            return sorted(nodes, key=lambda n: n.short_name if hasattr(n, 'short_name') else '')

        # Cleanup sort_expr (strip quotes if present)
        sort_expr = sort_expr.strip().strip("'\"")

        # Create a sorting function
        def get_sort_key(node):
            # Temporarily push node to context for evaluation
            self.context_stack.push(node)
            try:
                # Handle common case: node:value(ParamName) or just ParamName
                inner_expr = sort_expr
                if inner_expr.startswith('node:value(') and inner_expr.endswith(')'):
                    inner_expr = inner_expr[11:-1].strip().strip("'\"")
                
                if '/' not in inner_expr and not '(' in inner_expr:
                    val = node.get_child(inner_expr)
                    if val:
                        res = val.get_value()
                        # Convert all values to strings for consistent comparison
                        # This fixes "TypeError: '<' not supported between instances of 'str' and 'int'"
                        if res is None: return ""
                        return str(res)
                
                # Fallback to short_name (already a string)
                return node.short_name if hasattr(node, 'short_name') else ""
            finally:
                self.context_stack.pop()

        return sorted(nodes, key=get_sort_key)

    
    # ========== Model Functions ==========
    
    def as_modconf(self, module_name: str) -> Optional['ConfigurationNode']:
        """Get a module's root configuration node by name.
        
        This is the key function for cross-module access.
        Example: as:modconf('Mcu') returns the Mcu module root.
        """
        if module_name is None:
            return None
            
        # Strip quotes if present
        if isinstance(module_name, str):
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
        if isinstance(value, (int, bool)):
            return int(value)
        if isinstance(value, float):
            return int(value)
        if isinstance(value, str):
            # Handle hex and fuzzy booleans
            val_lower = value.strip().lower()
            if val_lower.startswith('0x'):
                try:
                    return int(val_lower, 16)
                except ValueError:
                    return 0
            if val_lower == 'true':
                return 1
            if val_lower == 'false':
                return 0
            try:
                return int(val_lower)
            except ValueError:
                return 0
        # If it's a node, get its value
        if hasattr(value, 'get_value'):
            return self.num_i(value.get_value())
        if hasattr(value, 'value'):
            return self.num_i(value.value)
        return 0
    
    def num_inttohex(self, value: Any, width: int = 0) -> str:
        """Convert integer to hex string."""
        int_val = self.num_i(value)
        if width > 0:
            hex_str = format(int_val, f'0{width}X')
        else:
            hex_str = format(int_val, 'X')
        return f"0x{hex_str}"
    
    def num_hextoint(self, value: Any) -> int:
        """Convert hex string to integer"""
        if value is None:
            return 0
        if isinstance(value, (int, float)):
            return int(value)
        s = str(value).strip().lower()
        if s.startswith('0x'):
            try:
                return int(s, 16)
            except ValueError:
                return 0
        try:
            return int(s)
        except ValueError:
            return 0
    
    def num_is_nan(self, value: Any) -> bool:
        """Check if value is not a number"""
        try:
            float(value)
            return False
        except (ValueError, TypeError):
            return True
    
    def num_isnumber(self, value: Any) -> bool:
        """Check if value is a number"""
        if value is None:
            return False
            
        # Unwrap ConfigurationNode if passed
        if hasattr(value, 'get_value'):
            value = value.get_value()
        elif hasattr(value, 'value'):
            value = value.value
            
        if isinstance(value, (int, float)):
            return True
            
        if isinstance(value, str):
            # Strip quotes
            v = value.strip().strip('"\'')
            if not v:
                return False
                
            # Handle hex
            if v.lower().startswith('0x'):
                try:
                    int(v, 16)
                    return True
                except ValueError:
                    return False
            
            # Handle float/int
            try:
                float(v)
                return True
            except (ValueError, TypeError):
                return False
                
        return False
    
    # ========== String Functions ==========
    
    def to_string(self, value: Any) -> str:
        """XPath string() function - convert any value to string.
        
        Args:
            value: Any value to convert
            
        Returns:
            String representation of the value
        """
        if value is None:
            return ''
        if hasattr(value, 'get_value'):
            value = value.get_value()
        elif hasattr(value, 'value'):
            value = value.value
        return str(value)
    
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
        if s is None:
            return 0
        if not isinstance(s, str):
            s = str(s)
        return len(s)
    
    def string_contains(self, s: str, substring: str) -> bool:
        """Check if string contains substring"""
        if not isinstance(s, str):
            s = str(s)
        return substring in s
    
    def string_substring(self, s: str, start: Any, length: Any = None) -> str:
        """Extract substring from string."""
        if s is None: return ""
        if not isinstance(s, str): s = str(s)
        
        try:
            start_num = int(self.num_i(start))
            length_num = int(self.num_i(length)) if length is not None else None
            
            # 1-indexed to 0-indexed
            py_start = max(0, start_num - 1)
            if length_num is not None:
                return s[py_start : py_start + length_num]
            return s[py_start:]
        except (ValueError, TypeError):
            return ""

    def string_substring_after(self, s: str, delimiter: str) -> str:
        """Extract portion of string after delimiter"""
        if s is None or delimiter is None: return ""
        s, d = str(s), str(delimiter)
        if d not in s: return ""
        return s.split(d, 1)[1]

    def string_substring_before(self, s: str, delimiter: str) -> str:
        """Extract portion of string before delimiter"""
        if s is None or delimiter is None: return ""
        s, d = str(s), str(delimiter)
        if d not in s: return ""
        return s.split(d, 1)[0]
    
    def normalize_space(self, s: Any = None) -> str:
        """XPath normalize-space() function.
        
        Strips leading and trailing whitespace and replaces sequences of
        whitespace characters with a single space.
        
        Args:
            s: String to normalize. If None or not provided, uses current context node's value.
            
        Returns:
            Normalized string
        """
        if s is None:
            # Get value from current context node
            current = self.context_stack.current_node()
            if current:
                s = current.get_value() if hasattr(current, 'get_value') else str(current)
            else:
                return ""
        
        # Unwrap ConfigurationNode if needed
        if hasattr(s, 'get_value'):
            s = s.get_value()
        elif hasattr(s, 'value'):
            s = s.value
        
        if s is None:
            return ""
        
        # Convert to string and normalize whitespace
        import re
        s = str(s)
        # Replace all whitespace sequences with single space and strip
        return re.sub(r'\s+', ' ', s).strip()
    
    def variant_name(self) -> str:
        """Get the current variant name"""
        # Return from renderer state if possible
        # For now, return PRE_COMPILE as default
        return "v2" # Match user's current context
    
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

    # ECU Resource Defaults - typical values for automotive MCUs
    # These can be overridden by setting ecu_resources dictionary
    ECU_DEFAULTS = {
        # Core/Resource configuration
        'Resource.NumOfCores': 4,           # Typical: 1, 2, or 4 cores
        'Mcu.NoOfCoreAvailable': 4,
        
        # CAN Module configuration
        'Can.MaxModules': 2,                # Number of CAN modules (MCAN0, MCAN1, ...)
        'Can.MaxNodes': 8,                  # Nodes per module (typical: 4 or 8)
        
        # CAN Message RAM Base addresses (typical for Cortex-R52 / THA6xxx)
        'Can.MCAN0BASERAM': '0x40080000',
        'Can.MCAN1BASERAM': '0x40090000',
        'Can.MCAN0ENDRAM': '0x4008FFFF',
        'Can.MCAN1ENDRAM': '0x4009FFFF',
        
        # Alternative naming
        'Can.MCAN0EndRam': '0x4008FFFF',
        'Can.MCAN1EndRam': '0x4009FFFF',
        
        # Flash configuration
        'Fls.PageSize': 256,
        'Fls.FlsPageSize': 256,
        'Fls.SectorSize': 4096,
        'Fls.NumberOfSectors': 256,
        
        # Fee configuration
        'Fee.VirtualPageSize': 8,
    }
    
    def ecu_get(self, path: str) -> Any:
        """Get ECU resource parameter (XDM-G).
        
        This implementation checks in order:
        1. User-provided ecu_resources dictionary
        2. Resource module configuration (if loaded)
        3. ECU_DEFAULTS class attribute
        4. Dynamic path construction for indexed resources (e.g., Can.MCAN0BASERAM)
        """
        # First check the user-provided ecu_resources dictionary
        if path in self.ecu_resources:
            return self.ecu_resources[path]
        
        # Check ECU_DEFAULTS for common paths
        if path in self.ECU_DEFAULTS:
            return self.ECU_DEFAULTS[path]
        
        # Handle dynamic indexed paths like Can.MCAN{n}BASERAM, Can.MCAN{n}ENDRAM
        import re
        mcan_match = re.match(r'Can\.(MCAN\d+)(BASERAM|ENDRAM|BaseRam|EndRam)', path)
        if mcan_match:
            module_id = mcan_match.group(1)  # e.g., "MCAN0"
            suffix = mcan_match.group(2).upper()  # e.g., "BASERAM" or "ENDRAM"
            
            # Try to get from defaults with normalized key
            default_key = f'Can.{module_id}{suffix}'
            if default_key in self.ECU_DEFAULTS:
                return self.ECU_DEFAULTS[default_key]
            
            # Generate sensible defaults based on module index
            module_num = int(re.search(r'\d+', module_id).group())
            base_addr = 0x40080000 + (module_num * 0x10000)
            end_addr = base_addr + 0xFFFF
            
            if 'BASE' in suffix:
                return hex(base_addr)
            else:
                return hex(end_addr)
        
        # Mapping for common EB Tresos ecu:get paths - search in modules
        if path in ('Fls.PageSize', 'Fls.FlsPageSize'):
            # Attempt to find FlsPageSize in Fls module configuration
            fls = self.symbol_table.get_module('Fls')
            if fls:
                for child in fls.get_children_recursive():
                    if child.short_name == 'FlsPageSize':
                        val = self.num_i(child)
                        if val and val != 0:
                            return val
            
            # Fallback to Resource module
            res = self.symbol_table.get_module('Resource')
            if res:
                for child in res.get_children_recursive():
                    if child.short_name == 'FlsPageSize':
                        val = self.num_i(child)
                        if val and val != 0:
                            return val
            
            # Return default
            return self.ECU_DEFAULTS.get('Fls.FlsPageSize', 256)
        
        # Try to find path in Resource module if loaded
        res = self.symbol_table.get_module('Resource')
        if res:
            # Parse path like "Resource.NumOfCores" -> look for "NumOfCores" child
            parts = path.split('.')
            if len(parts) >= 2:
                param_name = parts[-1]
                for child in res.get_children_recursive():
                    if child.short_name == param_name:
                        val = child.get_value() if hasattr(child, 'get_value') else getattr(child, 'value', None)
                        if val is not None:
                            return val
        
        # Default fallback: return 0 with warning
        print(f"WARNING: ecu:get('{path}') not found in ECU_DEFAULTS or modules, returning 0")
        return 0



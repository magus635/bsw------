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

    def __init__(self, symbol_table: 'SymbolTable', context_stack: 'ContextStack', ecu_resources: Optional[dict] = None):
        self.symbol_table = symbol_table
        self.context_stack = context_stack

        # ECU resource dictionary for ecu:get function
        self.ecu_resources = ecu_resources or {}

        # Variant name (will be set by renderer)
        self._variant_name = ""

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
            'text:replace': self.string_replace,
            
            # XPath standard function aliases (for compatibility)
            'string': self.to_string,  # XPath string() type conversion
            'string-length': self.string_length,
            'concat': self.string_concat,
            'contains': self.string_contains,
            'replace': self.string_replace,
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
            'variant:size': self.variant_size,
            'variant:all': self.variant_all,

            # Variable functions
            'var:defined': self.var_defined,
            'var:set': self.var_set,

            # ECU Resource functions
            'ecu:get': self.ecu_get,
            'ecu:list': self.ecu_list,

            # Bit manipulation functions
            'bit:shl': self.bit_shl,
            'bit:or': self.bit_or,
            'bit:and': self.bit_and,
            'bit:xor': self.bit_xor,
            'bit:not': self.bit_not,
            'bit:shr': self.bit_shr,

            # Additional node functions
            'node:refvalid': self.node_refvalid,
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
        try:
            return func(*args)
        except Exception as e:
            raise e
    
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

        For EB Tresos compatibility, this handles:
        1. Relative paths: Look for container by name or definition within current context
        2. Absolute paths: Resolve via symbol table
        3. Reference nodes: Get the target of the reference
        """
        if path_or_node is None:
            return None

        if isinstance(path_or_node, str):
            path_str = path_or_node.strip()

            # For relative paths (not starting with /), look within current context first
            if not path_str.startswith('/'):
                current = self.context_stack.current_node()
                if current:
                    # Try direct child lookup by short_name
                    child = current.get_child(path_str)
                    if child:
                        return child

                    # EB Tresos behavior: If not found by exact name, try to find by definition name
                    # e.g., looking for 'McuModuleConfiguration' might match 'McuModuleConfiguration_0'
                    # if its definition ends with '/McuModuleConfiguration'
                    for child_name, child_node in current.children.items():
                        # Check if child's definition_ref matches the search term
                        if child_node.definition_ref:
                            def_name = child_node.definition_ref.split('/')[-1]
                            if def_name == path_str:
                                return child_node
                        # Also check if child's short_name starts with the search term
                        # (handles cases like McuModuleConfiguration_0 for McuModuleConfiguration)
                        if child_name.startswith(path_str + '_') or child_name == path_str:
                            return child_node

            # Try absolute path resolution via symbol table
            res = self.symbol_table.resolve_reference(path_str)
            if res:
                return res

            return None

        # If it's a node, it must be of type 'reference'
        target_path = path_or_node.get_value()
        if not target_path:
             return None

        res = self.symbol_table.resolve_reference(str(target_path))
        return res
    
    def node_exists(self, path_or_node) -> bool:
        """Check if a path or node exists.

        Handles:
        1. String: Relative or absolute path check.
        2. Node: Returns True (unless it's a reference with no value).
        3. List: Returns True if non-empty.

        Important: For reference type nodes, this function checks whether the
        reference has a configured value. A reference node that exists in the
        definition but has no configured value is considered "not exists".
        """
        if path_or_node is None:
            return False

        if isinstance(path_or_node, list):
            # Filter out empty references from the list
            valid_items = []
            for item in path_or_node:
                if self._is_empty_reference(item):
                    continue
                valid_items.append(item)
            return len(valid_items) > 0

        if hasattr(path_or_node, 'short_name') or hasattr(path_or_node, 'node_type'):
            # It's already a node - check if it's an empty reference
            if self._is_empty_reference(path_or_node):
                return False
            return True

        if isinstance(path_or_node, str):
            if path_or_node.startswith('/'):
                node = self.symbol_table.get_by_path(path_or_node)
                if node is None:
                    return False
                # Check if it's an empty reference
                if self._is_empty_reference(node):
                    return False
                return True
            else:
                current = self.context_stack.current_node()
                if current:
                    # Check if it's a child name
                    child = current.get_child(path_or_node)
                    if child is not None:
                        # Check if it's an empty reference
                        if self._is_empty_reference(child):
                            return False
                        return True
                    # Check if it's an XPath from current context
                    try:
                        res = self.renderer._xpath_engine.evaluate(path_or_node)
                        if res is not None:
                            if isinstance(res, list):
                                # Filter out empty references
                                valid_items = [item for item in res if not self._is_empty_reference(item)]
                                return len(valid_items) > 0
                            # Single result - check if it's an empty reference
                            if self._is_empty_reference(res):
                                return False
                            return True
                    except:
                        pass
                return False

        return bool(path_or_node)

    def _is_empty_reference(self, node) -> bool:
        """Check if a node is a reference type with no configured value.

        Reference nodes that exist in the definition but have no configured
        value (value is None or empty string) are considered "empty".

        Args:
            node: A ConfigurationNode or similar object

        Returns:
            True if node is a reference with no value, False otherwise
        """
        if not hasattr(node, 'node_type'):
            return False
        if node.node_type != 'reference':
            return False
        # Get the value of the reference
        value = node.get_value() if hasattr(node, 'get_value') else getattr(node, 'value', None)
        return value is None or value == ''
    
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
                
                val = None
                if '/' not in inner_expr and not '(' in inner_expr:
                    child = node.get_child(inner_expr)
                    if child:
                        val = child.get_value()
                
                if val is None:
                    # Fallback to short_name if value not found, or empty string
                    if inner_expr == 'short_name':
                        val = node.short_name
                    else:
                        # Path traversal logic for complex expressions relative to node
                        # Simple implementation: check if it's a path
                        if '/' in inner_expr:
                            # Try to descend
                            current = node
                            parts = inner_expr.split('/')
                            for part in parts:
                                if current:
                                    current = current.get_child(part)
                            if current:
                                val = current.get_value()

                # Convert all values to strings for consistent comparison

                # This fixes "TypeError: '<' not supported between instances of 'str' and 'int'"
                res_str = str(val) if val is not None else ""
                
                # Return tuple for stability: (primary_key, short_name)
                return (res_str, node.short_name)
            finally:
                self.context_stack.pop()
        
        return sorted(nodes, key=get_sort_key)

    
    # ========== Model Functions ==========

    def as_modconf(self, module_name: str) -> Optional['ConfigurationNode']:
        """Get a module's root configuration node by name.

        This is the key function for cross-module access.
        Example: as:modconf('Mcu') returns the Mcu module root.
        """
        from .renderer import _debug_log

        if module_name is None:
            return None

        _debug_log(f"as_modconf: Looking for module '{module_name}'")
        _debug_log(f"as_modconf: Available modules: {self.symbol_table.get_all_modules()}")

        result = self.symbol_table.get_module(module_name)
        if result:
            _debug_log(f"as_modconf: Found module '{module_name}' with children: {list(result.children.keys())}")
        else:
            _debug_log(f"WARNING: Module '{module_name}' not loaded")
        return result


    
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
        if isinstance(value, list):
            if not value: return 0
            value = value[0]
            
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
                # Try as int first
                return int(val_lower)
            except ValueError:
                # Try as float, then truncate to int
                try:
                    return int(float(val_lower))
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
        return str(value) if value is not None else ''
    
    def string_concat(self, *args) -> str:
        """Concatenate strings"""
        return "".join(str(a) if a in (False, 0) or a else "" for a in args)
    
    def string_split(self, s: str, delimiter: str = " ") -> List[str]:
        """Split string by delimiter.

        Note: Empty strings are filtered out to match EB Tresos behavior.
        This allows both:
        - text:split('/Adc/Config/Unit', '/')[3] = 'Unit'
        - text:split('CORE0', 'CORE')[1] = '0'
        """
        if not isinstance(s, str):
            s = str(s)
        # Filter empty strings to match EB Tresos behavior
        return [x for x in s.split(delimiter) if x]
    
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
    
    def string_replace(self, s: Any, old: str, new: str) -> str:
        """Replace substrings"""
        if s is None: return ""
        return str(s).replace(str(old), str(new))
    
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

    def set_variant(self, variant: str):
        """Set the current variant name."""
        self._variant_name = variant or ""

    def variant_name(self) -> str:
        """Get the current variant name"""
        return self._variant_name
    
    def count(self, items) -> int:
        """Count items in a collection or node's children.
        
        EB Templates often use count(XPath) where XPath might return a single node or a list.
        """
        if items is None:
            return 0
            
        if isinstance(items, list):
            return len(items)
            
        if hasattr(items, 'short_name') or hasattr(items, 'node_type'):
            # It's a single ConfigurationNode (wrapped or overlay)
            return 1
            
        # For non-node, non-list items (like simple strings or numbers)
        # If it's a string, we treat it as 1 item (don't count characters!)
        if isinstance(items, str):
            return 1 if items else 0
            
        # collections/iterables except strings/bytes
        if hasattr(items, '__len__') and not isinstance(items, (str, bytes)):
            try:
                return len(items)
            except:
                pass
                
        # Default truthiness count
        return 1 if items else 0

    
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

    def variant_all(self) -> List[str]:
        """Get all variant names defined in the project.

        Returns a list of all variant names. If a variant is set,
        returns a list containing that variant name.
        """
        if self._variant_name:
            return [self._variant_name]
        return []

    # ========== Variable Functions ==========

    def var_defined(self, var_name: str) -> bool:
        """Check if a variable is defined in the current context.

        Args:
            var_name: Name of the variable (without $ prefix)

        Returns:
            True if the variable is defined, False otherwise
        """
        # Remove $ prefix if present
        if var_name.startswith('$'):
            var_name = var_name[1:]
        return self.context_stack.has_variable(var_name)

    def var_set(self, var_name: str, value: Any) -> str:
        """Set a variable in the current context.

        Args:
            var_name: Name of the variable (without $ prefix)
            value: Value to set

        Returns:
            Empty string (no output)
        """
        # Remove $ prefix if present
        if var_name.startswith('$'):
            var_name = var_name[1:]
        self.context_stack.set_variable(var_name, value)
        return ""

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

    def ecu_get(self, path: str) -> Any:
        """Get ECU resource parameter (XDM-G).

        Lookup order:
        1. User-provided ecu_resources dictionary (for testing/overrides)
        2. Module configuration query (from loaded define files)
        3. Module definition default values
        4. Return None with warning if not found
        """
        from .renderer import _debug_log

        # 1. User override (retained for testing)
        if path in self.ecu_resources:
            return self.ecu_resources[path]

        # 2. Parse path "Module.ParamName" or "Module.Container.ParamName"
        parts = path.split('.')
        if len(parts) < 2:
            _debug_log(f"WARNING: ecu:get('{path}') - invalid path format")
            return None

        module_name = parts[0]
        param_parts = parts[1:]

        # 3. Get module from SymbolTable
        module = self.symbol_table.get_module(module_name)
        if module is None:
            # Also try Resource module as a fallback for cross-module params
            module = self.symbol_table.get_module('Resource')
            if module is None:
                _debug_log(f"WARNING: ecu:get('{path}') - module '{module_name}' not loaded")
                return None

        # 4. Search for the parameter in the module
        param_name = param_parts[-1]

        # First try navigating the exact path (e.g., "Container.ParamName")
        if len(param_parts) > 1:
            current = module
            for part in param_parts[:-1]:
                found = False
                for child in current.children.values():
                    if child.short_name == part:
                        current = child
                        found = True
                        break
                if not found:
                    break
            else:
                # Exact path traversal succeeded, look for param in this container
                for child in current.children.values():
                    if child.short_name == param_name:
                        val = child.get_value()
                        if val is not None:
                            return val

        # Fallback: recursive search for param_name anywhere in the module
        for child in module.get_children_recursive():
            if child.short_name == param_name:
                val = child.get_value()
                if val is not None:
                    return val

        # 5. Not found
        _debug_log(f"WARNING: ecu:get('{path}') - parameter not found in module")
        return None

    def ecu_list(self, path: str) -> List[Any]:
        """Get ECU resource list (XDM-G).

        Lookup order:
        1. User-provided ecu_resources dictionary (for testing/overrides)
        2. Module configuration query (from loaded define files)
        3. Return empty list with warning if not found

        Args:
            path: Resource path like 'Adc.ReqSrcClass', 'Adc.HwUnitId', etc.

        Returns:
            List of resource values
        """
        from .renderer import _debug_log

        # 1. Check user-provided resources first
        if path in self.ecu_resources:
            val = self.ecu_resources[path]
            if isinstance(val, list):
                return val
            return [val]

        # 2. Parse path
        parts = path.split('.')
        if len(parts) < 2:
            _debug_log(f"WARNING: ecu:list('{path}') - invalid path format")
            return []

        module_name = parts[0]
        param_name = parts[-1]

        # 3. Try the named module first
        module = self.symbol_table.get_module(module_name)
        if module is not None:
            for child in module.get_children_recursive():
                if child.short_name == param_name:
                    val = child.get_value()
                    if isinstance(val, list):
                        return val
                    if val is not None:
                        return [val]

        # 4. Fallback to Resource module
        res = self.symbol_table.get_module('Resource')
        if res is not None:
            for child in res.get_children_recursive():
                if child.short_name == param_name:
                    val = child.get_value()
                    if isinstance(val, list):
                        return val
                    if val is not None:
                        return [val]

        # 5. Not found
        _debug_log(f"WARNING: ecu:list('{path}') not found in any module, returning empty list")
        return []

    # ========== Bit Manipulation Functions ==========

    def bit_shl(self, value: Any, shift: Any) -> int:
        """Bit shift left operation.

        Args:
            value: The value to shift
            shift: Number of bits to shift left

        Returns:
            value << shift
        """
        int_val = self.num_i(value)
        shift_val = self.num_i(shift)
        return int_val << shift_val

    def bit_shr(self, value: Any, shift: Any) -> int:
        """Bit shift right operation.

        Args:
            value: The value to shift
            shift: Number of bits to shift right

        Returns:
            value >> shift
        """
        int_val = self.num_i(value)
        shift_val = self.num_i(shift)
        return int_val >> shift_val

    def bit_or(self, value1: Any, value2: Any) -> int:
        """Bitwise OR operation.

        Args:
            value1: First operand
            value2: Second operand

        Returns:
            value1 | value2
        """
        int_val1 = self.num_i(value1)
        int_val2 = self.num_i(value2)
        return int_val1 | int_val2

    def bit_and(self, value1: Any, value2: Any) -> int:
        """Bitwise AND operation.

        Args:
            value1: First operand
            value2: Second operand

        Returns:
            value1 & value2
        """
        int_val1 = self.num_i(value1)
        int_val2 = self.num_i(value2)
        return int_val1 & int_val2

    def bit_xor(self, value1: Any, value2: Any) -> int:
        """Bitwise XOR operation.

        Args:
            value1: First operand
            value2: Second operand

        Returns:
            value1 ^ value2
        """
        int_val1 = self.num_i(value1)
        int_val2 = self.num_i(value2)
        return int_val1 ^ int_val2

    def bit_not(self, value: Any, width: int = 32) -> int:
        """Bitwise NOT operation.

        Args:
            value: The value to negate
            width: Bit width for masking (default 32)

        Returns:
            ~value (masked to specified width)
        """
        int_val = self.num_i(value)
        mask = (1 << width) - 1
        return (~int_val) & mask

    # ========== Additional Node Functions ==========

    def node_refvalid(self, path_or_node: Any) -> str:
        """Check if a reference is valid (exists and points to a valid target).

        This function checks whether:
        1. The reference node/path exists
        2. The reference target can be resolved

        Args:
            path_or_node: A reference path string or a reference node

        Returns:
            String 'true' if reference is valid and resolvable, 'false' otherwise.
            Note: Returns string for EB Tresos template compatibility where
            templates use string comparison like: node:refvalid(./ref) = 'true'
        """
        if path_or_node is None:
            return 'false'

        # If it's a string path, try to resolve it
        if isinstance(path_or_node, str):
            # First check if the path itself exists
            if path_or_node.startswith('/'):
                node = self.symbol_table.get_by_path(path_or_node)
            else:
                # Relative path from current context
                # Handle ./ prefix and multi-level paths like ./foo/bar
                rel_path = path_or_node
                if rel_path.startswith('./'):
                    rel_path = rel_path[2:]  # Remove ./ prefix

                current = self.context_stack.current_node()
                if current:
                    # Navigate through path segments
                    node = current
                    for part in rel_path.split('/'):
                        if part and node:
                            node = node.get_child(part)
                else:
                    node = None

            if node is None:
                return 'false'

            # Check if it's a reference and can be resolved
            if hasattr(node, 'node_type') and node.node_type == 'reference':
                target = self.node_ref(node)
                return 'true' if target is not None else 'false'

            # If it's not a reference node, check if the path is valid
            return 'true'

        # If it's a node, check if it's a valid reference
        if hasattr(path_or_node, 'node_type'):
            if path_or_node.node_type == 'reference':
                target = self.node_ref(path_or_node)
                return 'true' if target is not None else 'false'
            # Non-reference node - considered valid
            return 'true'

        # For any other value, return false
        return 'false'

    # ========== Additional Variant Functions ==========

    def variant_size(self) -> int:
        """Get the number of variants defined in the project.

        Per EB Tresos spec: Returns the count of variants available.
        If no variant information is available, returns 0.

        Returns:
            Number of variants (0 if no variants defined)
        """
        # If variant_name returns non-empty, we have at least 1 variant
        if self._variant_name:
            return 1
        return 0



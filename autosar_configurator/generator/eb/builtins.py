"""
Built-in Functions for EB Template Engine

Implements the required function library:
- Node functions: node:ref, node:path, node:name, node:value, node:exists, node:current
- Model functions: as:modconf, as:container
- Number functions: num:i, num:inttohex, num:is_nan, num:round, num:floor, num:ceiling, num:abs
- String functions: string:concat, string:split, string:trim, string:upper, string:lower, string:match,
                   string:starts-with, string:ends-with, string:translate
- Aggregate functions: sum, avg, min, max
- Math functions: round, floor, ceiling, abs
- Format functions: format-number
- XPath compatibility: translate, starts-with, ends-with, document, id, key
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
        self.renderer = None

        # Build function registry
        self._functions = {
            # Node functions
            'node:value': self.node_value,
            'node:name': self.node_name,
            'node:path': self.node_path,
            'node:ref': self.node_ref,
            'node:exists': self.node_exists,
            'node:empty': self.node_empty,
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
            'num:f': self.num_f,                  # Convert to float
            'num:mul': self.num_mul,              # NEW: Point-to-point multiplication
            'num:inttohex': self.num_inttohex,
            'num:hextoint': self.num_hextoint,
            'num:is_nan': self.num_is_nan,
            'num:isnumber': self.num_isnumber,  # NEW: Check if value is a number
            'num:round': self.xpath_round,      # Alias for round()
            'num:floor': self.xpath_floor,      # Alias for floor()
            'num:ceiling': self.xpath_ceiling,  # Alias for ceiling()
            'num:abs': self.xpath_abs,          # Alias for abs()
            'num:max': self.xpath_max,          # Alias for max()
            'num:min': self.xpath_min,          # Alias for min()
            
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
            'string:starts-with': self.xpath_starts_with,    # Alias for starts-with()
            'string:ends-with': self.xpath_ends_with,        # Alias for ends-with()
            'string:translate': self.xpath_translate,        # Alias for translate()
            
            # Text functions (Namespace aliases)
            'text:split': self.string_split,
            'text:join': self.string_join,
            'text:tolower': self.string_lower,
            'text:toupper': self.string_upper,
            'text:replace': self.string_replace,
            'text:replaceAll': self.string_replace,
            'text:contains': self.string_contains,
            'text:grep': self.text_grep,
            'text:match': self.string_match,
            
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

            # XPath position functions
            'position': self.xpath_position,
            'last': self.xpath_last,

            # Aggregate functions (XPath 2.0 / common extensions)
            'sum': self.xpath_sum,
            'avg': self.xpath_avg,
            'min': self.xpath_min,
            'max': self.xpath_max,

            # Math functions
            'round': self.xpath_round,
            'floor': self.xpath_floor,
            'ceiling': self.xpath_ceiling,
            'abs': self.xpath_abs,
            'number': self.xpath_number,

            # Additional string functions
            'translate': self.xpath_translate,
            'starts-with': self.xpath_starts_with,
            'ends-with': self.xpath_ends_with,
            'format-number': self.xpath_format_number,

            # Special XPath functions (limited implementation)
            'document': self.xpath_document,
            'id': self.xpath_id,
            'key': self.xpath_key,

            # Boolean helpers
            'not': self.logical_not,
            'name': self.node_name,
            
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
            'ecu:has': self.ecu_has,
            'ecu:list': self.ecu_list,

            # Bit manipulation functions
            'bit:shl': self.bit_shl,
            'bit:or': self.bit_or,
            'bit:and': self.bit_and,
            'bit:xor': self.bit_xor,
            'bit:not': self.bit_not,
            'bit:shr': self.bit_shr,
            'bit:getbit': self.bit_getbit,
            'bit:bitset': self.bit_bitset,

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
            # If the value is already a primitive (not a path-like string),
            # return it directly. This handles the case where the implicit VALUE
            # rule already extracted the scalar from a parameter node before
            # node:value() is called.
            # Path-like strings contain '/' or start with '.' or are a known child name.
            stripped = node.strip()
            if '/' not in stripped and not stripped.startswith('.'):
                current = self.context_stack.current_node()
                if current and hasattr(current, 'get_child') and current.get_child(stripped) is not None:
                    # It's a child name — resolve it
                    path = node
                    child = current.get_child(stripped)
                    resolved_val = child.get_value() if hasattr(child, 'get_value') else child
                    return resolved_val
                elif stripped.startswith('/'):
                    pass  # absolute path, proceed with resolution below
                else:
                    # Not a child name and not a path — it's already a value
                    return node

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
                    
                    # If simple lookup failed, try XPath evaluation from current context
                    if node is None:
                        try:
                            from . import xpath_engine
                            engine = xpath_engine.XPathEngine(self.symbol_table, self.context_stack, self)
                            result = engine.evaluate(path)
                            if result is not None:
                                # XPath may return list; get first element
                                if isinstance(result, list) and result:
                                    node = result[0]
                                else:
                                    node = result
                        except Exception as e:
                            import logging
                            logging.debug(f"node:value(): XPath evaluation failed for '{path}': {e}")
                            node = None
                else:
                    node = None
        
        if node is None:
            # If resolution failed, log a warning and return empty string
            # Do NOT return the path string as if it were the value - this causes template output errors
            if isinstance(path, str):
                import logging
                logging.warning(f"node:value(): Could not resolve path '{path}' to a node. Returning empty string.")
                return ''  # Return empty string, not the path
            return None
        
        # Robustness: If node is already a value (not a ConfigurationNode), return it
        if not hasattr(node, 'get_value') and not hasattr(node, 'value'):
            return node

        value = node.get_value() if hasattr(node, 'get_value') else node.value

        param_type = getattr(node, 'param_type', None)
        if param_type:
            param_type = param_type.upper()

            # EB Tresos node:value() converts boolean parameters to "true"/"false"
            # strings so that templates can compare: node:value(./Enable) = 'true'
            # EPC files store booleans as integers (1/0), so we must convert here.
            if 'BOOLEAN' in param_type:
                return 'true' if self._parse_boolean(value) else 'false'

            # Reference -> Resolve
            if 'REFERENCE' in param_type or node.node_type == 'reference':
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
        """Get the short name of a node.

        For XDM choice containers (virtual nodes from /AUTOSAR/TOP-LEVEL-PACKAGES/*/ELEMENTS/*),
        returns the choice value (e.g. 'MODULE-DEF') to match EB Tresos behavior.
        """
        if node is None:
            node = self.context_stack.current_node()
        if node is None:
            return ""
        # XDM choice containers report their choice value as name
        xdm_val = getattr(node, '_xdm_choice_value', None)
        if xdm_val:
            return xdm_val
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

            # For relative paths with XPath features (contains /, *, [ etc.),
            # evaluate as XPath expression first to get the actual node
            if ('/' in path_str or '*' in path_str or '[' in path_str) and not path_str.startswith('/AUTOSAR'):
                # Use xpath engine to navigate to the node
                engine = getattr(self.renderer, '_xpath_engine', None) if self.renderer else None
                if engine:
                    node = engine.evaluate(path_str, return_node=True)
                    if node is not None:
                        # Got the node via XPath - now recursively call node_ref
                        # to follow the reference if it's a reference node
                        return self.node_ref(node)

            # For simple names (not starting with /), look within current context first
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
                    for child_node in current.children:
                        # Check if child's definition_ref matches the search term
                        if child_node.definition_ref:
                            def_name = child_node.definition_ref.split('/')[-1]
                            if def_name == path_str:
                                return child_node
                        # Also check if child's short_name starts with the search term
                        # (handles cases like McuModuleConfiguration_0 for McuModuleConfiguration)
                        if child_node.short_name.startswith(path_str + '_') or child_node.short_name == path_str:
                            return child_node

            # Try absolute path resolution via symbol table
            if self.symbol_table:
                res = self.symbol_table.resolve_reference(path_str)
                if res:
                    return res
            else:
                # If no symbol table, try fallback navigation from context
                current = self.context_stack.current_node()
                if current:
                    # For relative paths, try to navigate relative to current
                    parts = path_str.strip('/').split('/')
                    nav_current = current
                    for part in parts:
                        child = nav_current.get_child(part)
                        if child:
                            nav_current = child
                        else:
                            nav_current = None
                            break
                    if nav_current:
                        return nav_current

            return None

        # If it's a node, check if it's a reference type
        # EB Tresos behavior: If called on a non-reference node, usually returns the node itself
        # unless it strictly requires a reference. Given the template usage on containers,
        # we should pass through non-reference nodes.
        if hasattr(path_or_node, 'node_type') and path_or_node.node_type != 'reference':
            # Also check param_type just in case
            param_type = getattr(path_or_node, 'param_type', '')
            if 'REFERENCE' not in str(param_type).upper():
                return path_or_node

        # It is a reference node (or we treat it as one)
        target_path = path_or_node.get_value()
        if not target_path:
             return None

        target_path_str = str(target_path).strip()

        # Try symbol table first
        if self.symbol_table:
            res = self.symbol_table.resolve_reference(target_path_str)
            if res:
                return res

        # Fallback: Navigate from root to find the target node
        # Path format: /Adc/Adc/AdcConfigSet/HWTrigDemo/AN0
        # We need to find AdcConfigSet -> HWTrigDemo -> AN0 in the tree
        current = self.context_stack.current_node()
        if current:
            # Walk up to root
            root = current
            while root.parent:
                root = root.parent

            # Extract path parts and remove leading empty string and duplicates
            parts = [p for p in target_path_str.split('/') if p]
            if not parts:
                return None

            # The path format is typically: Adc, Adc, AdcConfigSet, HWTrigDemo, AN0
            # Skip the redundant Adc (appears twice) and start from AdcConfigSet
            start_idx = 1
            if len(parts) > 2 and parts[0] == parts[1]:
                # Skip both Adc entries and start from the third
                start_idx = 2

            # Navigate from root
            nav_current = root
            for i in range(start_idx, len(parts)):
                part = parts[i]
                child = nav_current.get_child(part)
                if child:
                    nav_current = child
                else:
                    # If direct child not found, search recursively in instance wrappers
                    found = False
                    for c_node in nav_current.children:
                        if c_node.short_name == part:
                            nav_current = c_node
                            found = True
                            break
                        # Check if this is an instance wrapper (e.g., AdcConfigSet) and the target is inside
                        if c_node.node_type == 'container' and c_node.short_name != part:
                            # Try to find the part inside this container
                            inner = c_node.get_child(part)
                            if inner:
                                nav_current = inner
                                found = True
                                break

                    if not found:
                        nav_current = None
                        break

            if nav_current and nav_current != root:
                return nav_current

        # Last resort: Create a stub node for unresolved cross-module references.
        # This handles cases like /EcuC/EcuC/EcucHardware/EcucCoreDefinition_0 where
        # the EcuC config doesn't have the EcucHardware section but Os templates need
        # to resolve node:ref(./OsCoreId)/EcucCoreId to differentiate cores.
        if target_path_str.startswith('/'):
            from .symbol_table import ConfigurationNode
            import re as _re
            parts = [p for p in target_path_str.split('/') if p]
            if parts:
                stub_name = parts[-1]
                stub = ConfigurationNode(
                    short_name=stub_name,
                    node_type='container',
                    path=target_path_str,
                    definition_ref=target_path_str
                )
                # Extract numeric suffix as common parameter values
                # e.g., EcucCoreDefinition_0 -> EcucCoreId=0
                suffix_match = _re.search(r'_(\d+)$', stub_name)
                if suffix_match:
                    idx_val = int(suffix_match.group(1))
                    base_name = _re.sub(r'_\d+$', '', stub_name)
                    # EcucCoreDefinition -> EcucCoreId
                    if 'Core' in base_name:
                        id_param = ConfigurationNode(
                            short_name='EcucCoreId',
                            node_type='parameter',
                            path=f"{target_path_str}/EcucCoreId",
                            value=idx_val
                        )
                        stub.add_child(id_param)
                    # Generic: add an index-based Id parameter
                    generic_id_name = base_name.split('Definition')[0] + 'Id' if 'Definition' in base_name else base_name + 'Id'
                    if not stub.get_child(generic_id_name):
                        generic_param = ConfigurationNode(
                            short_name=generic_id_name,
                            node_type='parameter',
                            path=f"{target_path_str}/{generic_id_name}",
                            value=idx_val
                        )
                        stub.add_child(generic_param)
                return stub

        return None
    
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
            # Handle node lists: check if any node is non-empty
            valid_items = [item for item in path_or_node if not self._is_node_empty(item)]
            return len(valid_items) > 0

        if hasattr(path_or_node, 'short_name') or hasattr(path_or_node, 'node_type'):
            # It's already a node - check if it's "empty" (param with no value or empty ref)
            if self._is_node_empty(path_or_node):
                return False
            return True

        if isinstance(path_or_node, str):
            # Handle XPath descendant syntax // which starts with / but is not a simple absolute path
            if path_or_node.startswith('//'):
                # Treat as XPath expression - fall through to XPath evaluation
                pass
            elif path_or_node.startswith('/'):
                node = self.symbol_table.get_by_path(path_or_node)
                if node is None:
                    return False
                # Check if it's an empty node
                if self._is_node_empty(node):
                    return False
                return True
            
            # Relative path or XPath expression
            current = self.context_stack.current_node()
            # Even if current is None, we might be able to evaluate absolute XPath like //Node
            
            # Check if it's a child name (only for simple relative names)
            if current and not '/' in path_or_node and not '[' in path_or_node:
                child = current.get_child(path_or_node)
                if child is not None:
                    # Check if it's an empty node
                    if self._is_node_empty(child):
                        return False
                    return True
            
            # Check if it's an XPath
            try:
                # Use renderer's xpath engine if available
                engine = getattr(self.renderer, '_xpath_engine', None)
                if not engine:
                    # Fallback if renderer not linked
                    from .xpath_engine import XPathEngine
                    engine = XPathEngine(self.symbol_table, self.context_stack, self)
                
                # For node:exists, we want the NODE, not the value.
                # So we must instruct evaluate() to return the node.
                # But XPathEngine.evaluate() signature varies. 
                # Let's check if we can pass return_node=True or use a specific method.
                # The current implementation of evaluate in xpath_engine.py supports return_node arg.
                res = engine.evaluate(path_or_node, return_node=True)
                
                if res is not None:
                    if isinstance(res, list):
                        # Filter out empty nodes
                        valid_items = [item for item in res if not self._is_node_empty(item)]
                        return len(valid_items) > 0
                    # Single result - check if it's empty
                    if self._is_node_empty(res):
                        return False
                    return True
            except Exception as e:
                pass
                
            return False

        return bool(path_or_node)

    def _is_node_empty(self, node) -> bool:
        """Check if a node represents a missing configuration.
        
        A node is "empty" if:
        1. It's a parameter with no configured value (value is None or empty string).
        2. It's a reference with no target (value is None or empty string).
        """
        if not hasattr(node, 'node_type'):
            return False
            
        # Get the value
        value = node.value if hasattr(node, 'value') else getattr(node, 'value', None)
        
        if node.node_type == 'parameter':
            # Parameters with no value (None) or empty strings are considered non-existent
            return value is None or str(value).strip() == ''
            
        if node.node_type == 'reference':
            # References with no value are empty
            return value is None or str(value).strip() == ''
            
        return False
        
    def node_empty(self, path_or_node) -> bool:
        """Check if a node or path is empty.
        
        This is the functional opposite of node_exists.
        """
        return not self.node_exists(path_or_node)
    
    
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

        # Filter out non-node objects (e.g. strings) that may have crept into the list
        nodes = [n for n in nodes if hasattr(n, 'get_child') or hasattr(n, 'short_name')]
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
            # Guard: if node is not a real node object, return stable fallback
            if not hasattr(node, 'get_child'):
                return (2, '', str(node))
            # Temporarily push node to context for evaluation
            self.context_stack.push(node)
            try:
                inner_expr = sort_expr
                if inner_expr.startswith('node:value(') and inner_expr.endswith(')'):
                    inner_expr = inner_expr[11:-1].strip().strip("'\"")

                # Strip leading ./ if present
                if inner_expr.startswith('./'):
                    inner_expr = inner_expr[2:]

                # Handle common case: node:value(ParamName) or just ParamName
                inner_expr_orig = inner_expr
                val = None

                # Check if this is a complex expression (contains function calls or operators)
                has_functions = '(' in inner_expr or 'num:' in inner_expr or 'text:' in inner_expr or 'string:' in inner_expr

                if inner_expr == '@index':
                    # Document order index
                    val = getattr(node, 'index', getattr(node, 'config_index', 0))
                elif has_functions and self.renderer:
                    # For complex expressions, use renderer's expression evaluator
                    val = self.renderer._evaluate_expression(inner_expr)
                elif '/' not in inner_expr and not '(' in inner_expr:
                    # Simple attribute lookup
                    child = node.get_child(inner_expr) if hasattr(node, 'get_child') else None
                    if child:
                        val = child.get_value()

                if val is None:
                    # Fallback to short_name if value not found, or empty string
                    if inner_expr == 'short_name':
                        val = node.short_name
                    else:
                        # Path traversal logic for complex expressions relative to node
                        if '/' in inner_expr and not has_functions:
                            current = node
                            parts = [p for p in inner_expr.split('/') if p and p != '.']
                            for part in parts:
                                if current:
                                    current = current.get_child(part) if hasattr(current, 'get_child') else None
                            if current:
                                val = current.get_value()

                # Robust sorting key generation
                if val is None:
                    return (2, "", node.short_name)

                # If it's numeric, use numeric sort
                try:
                    if isinstance(val, (int, float)):
                        return (0, float(val), node.short_name)
                    if isinstance(val, str) and val.strip():
                        s = val.strip()
                        # Handle hex
                        if s.startswith('0x') or s.startswith('0X'):
                            return (0, float(int(s, 16)), node.short_name)
                        # Handle decimal
                        if all(c.isdigit() or c in '.-' for c in s):
                            return (0, float(s), node.short_name)
                except:
                    pass

                # Fallback to string sort
                sort_key = (1, str(val), node.short_name)
                return sort_key
            finally:
                self.context_stack.pop()
        
        result = sorted(nodes, key=get_sort_key)
        
        return result

    
    # ========== Model Functions ==========

    def as_modconf(self, module_name: str) -> Optional['ConfigurationNode']:
        """Get a module's root configuration node by name.

        This is the key function for cross-module access.
        Example: as:modconf('Mcu') returns the Mcu module root.
        """
        from .renderer import _debug_log

        if module_name is None:
            return None

        result = self.symbol_table.get_module(module_name)
        if not result:
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
            res = value.get_value()
            if res is None:
                return 0
            return self.num_i(res)
            
        return 0
        if hasattr(value, 'value'):
            return self.num_i(value.value)
        return 0
    
    def num_f(self, value: Any) -> float:
        """Convert value to float (num:f function)"""
        if value is None:
            return 0.0
        if isinstance(value, list):
            if not value: return 0.0
            value = value[0]
            
        if isinstance(value, float):
            return value
        if isinstance(value, (int, bool)):
            return float(value)

        if isinstance(value, str):
            val_stripped = value.strip()
            if not val_stripped:
                return 0.0
            # Handle scientific notation and regular floats
            try:
                return float(val_stripped)
            except ValueError:
                return 0.0

        # If it's a node, get its value
        if hasattr(value, 'get_value'):
            return self.num_f(value.get_value())
        if hasattr(value, 'value'):
            return self.num_f(value.value)
        return 0.0
    
    def num_mul(self, list1: Any, list2: Any) -> Union[List[float], float]:
        """Multiply two values or two lists point-to-point (EB extension)."""
        def to_list(v):
            if isinstance(v, list):
                return v
            return [v]

        l1 = to_list(list1)
        l2 = to_list(list2)
        
        max_len = max(len(l1), len(l2))
        res = []
        for i in range(max_len):
            v1 = self.num_f(l1[i]) if i < len(l1) else 1.0
            v2 = self.num_f(l2[i]) if i < len(l2) else 1.0
            # EB specific: if product is integer-like, return as int
            prod = v1 * v2
            if prod == int(prod):
                res.append(int(prod))
            else:
                res.append(prod)
            
        if len(res) == 1 and not isinstance(list1, list) and not isinstance(list2, list):
            return res[0]
            
        return res
    
    def num_inttohex(self, value: Any, width: int = 0) -> str:
        """Convert integer to hex string."""
        int_val = self.num_i(value)


        if width > 0:
            hex_str = format(int_val, f'0{width}x')
        else:
            hex_str = format(int_val, 'x')
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
        
        # Unwrap list (NodeSet)
        if isinstance(value, list):
            if not value:
                return ''
            value = value[0]

        if hasattr(value, 'get_value'):
            value = value.get_value()
        elif hasattr(value, 'value'):
            value = value.value
        return str(value) if value is not None else ''
    
    def string_concat(self, *args) -> str:
        """Concatenate strings"""
        # Special handling for concat('_', '') to result in '' (empty string)
        # This addresses the issue where variant:name() returns '' for "Default" variant,
        # and template's concat('_', variant:name()) incorrectly produces '_'
        if len(args) == 2 and (args[0] == '_' and (args[1] is None or str(args[1]) == '')) or \
                           ((args[0] is None or str(args[0]) == '') and args[1] == '_'):
            return ""

        return "".join(str(a) if a in (False, 0) or a else "" for a in args)
    
    def string_split(self, s: str, delimiter: str = " ") -> List[str]:
        """Split string by delimiter.

        Behavior varies by delimiter to match EB Tresos:
        - Space delimiter: filter ALL empty strings (handles multiple spaces,
          leading/trailing spaces in space-separated arrays like '2 2 ')
        - Other delimiters: preserve middle empty strings (critical for
          comma-separated data like '0,,4,256' where index positions matter),
          but filter leading and trailing empty strings. Leading empty strings
          are filtered because EB Tresos templates use hardcoded indices
          like text:split(path,'/')[4] assuming no leading empty from paths
          starting with '/'.
        """
        if not isinstance(s, str):
            # For lists (e.g. from num:mul), use Python str() to get "[2, 2]"
            # NOT to_string() which only takes the first element
            if isinstance(s, list):
                s = str(s)
            else:
                s = self.to_string(s)
        res = s.split(delimiter)
        if delimiter == ' ':
            # For space delimiter, filter all empty strings
            res = [x for x in res if x]
        else:
            # For other delimiters: remove leading and trailing empties,
            # but preserve middle empty strings
            while res and res[-1] == '':
                res.pop()
            while res and res[0] == '':
                res.pop(0)
        return res

    def string_join(self, items: Any, separator: str = " ") -> str:
        """Join list elements with a separator (EB Tresos text:join).

        text:join(list, separator) → separator.join(list)
        """
        if isinstance(items, list):
            return separator.join(str(x) for x in items)
        # If not a list, just return as string
        return str(items) if items is not None else ''

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
        """Convert string to lowercase.
        
        Special handling for integers: if the value is a large integer 
        (likely a memory address from ECU resources), convert it to 
        lowercase hex string with 0x prefix.
        """
        if isinstance(s, int):
            # Large integers (> 0xFFFF) are likely memory addresses
            # Convert to hex string for proper template processing
            if s > 0xFFFF:
                return hex(s).lower()
            return str(s).lower()
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
    
    def string_contains(self, s, substring: str) -> bool:
        """Check if string contains substring, or if list contains element.

        In EB Tresos, text:contains(list, value) checks list membership.
        Standard XPath contains(string, substring) checks string containment.
        """
        if isinstance(s, list):
            # EB Tresos text:contains(ecu:list(...), value): list membership
            # Unwrap ConfigurationNode to value if needed
            items_str = []
            for item in s:
                if hasattr(item, 'get_value'):
                    items_str.append(str(item.get_value()))
                else:
                    items_str.append(str(item))
            # Also unwrap substring (may be a ConfigurationNode or list of nodes)
            sub_str = str(substring)
            if hasattr(substring, 'get_value'):
                sub_str = str(substring.get_value())
            elif isinstance(substring, list):
                if len(substring) >= 1:
                    # Use the first value - in correct parent navigation,
                    # ../../../../IntcIntSrcClass should return a single node.
                    # If multiple are returned, use the first (closest match).
                    v = substring[0]
                    sub_str = str(v.get_value()) if hasattr(v, 'get_value') else str(v)
            return sub_str in items_str
        if not isinstance(s, str):
            s = str(s)
        return str(substring) in s
    
    def text_grep(self, items: Any, pattern: str) -> List[str]:
        """Filter list items matching a regex pattern (text:grep).
        
        Args:
            items: List of strings, or a single string (will be treated as list of 1)
            pattern: Regex pattern
            
        Returns:
            List of matching strings
        """
        if items is None:
            return []
            
        # Normalize to list
        if not isinstance(items, list):
            items = [str(items)]
            
        import re
        result = []
        try:
            regex = re.compile(str(pattern))
            for item in items:
                # Unwrap node value if needed
                if hasattr(item, 'get_value'):
                    s = str(item.get_value())
                else:
                    s = str(item)
                    
                if regex.search(s):
                    result.append(s)
        except re.error:
            # Invalid regex, return empty or log error
            pass
            
        if not result:
            return '[]'
            
        return result

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
        # "Default" is our internal placeholder for base configuration without variants
        if self._variant_name == "Default":
            return ""
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

    def xpath_position(self) -> int:
        """XPath position() function - returns current context position.

        In a LOOP or predicate, this returns the 1-based position of the current item.
        The position is set by the XPath engine during iteration.
        """
        if hasattr(self, 'context_stack') and self.context_stack.has_variable('position'):
            return self.context_stack.get_variable('position')
        # Default to 1 if position not set
        return 1

    def xpath_last(self) -> int:
        """XPath last() function - returns the total count of items in current context.

        In a LOOP or predicate, this returns the total number of items being iterated.
        The last value is set by the XPath engine during iteration.
        """
        if hasattr(self, 'context_stack') and self.context_stack.has_variable('last'):
            return self.context_stack.get_variable('last')
        # Default to 1 if last not set
        return 1

    # ========== Aggregate Functions (XPath 2.0 / Extensions) ==========

    def _extract_numeric_values(self, items: Any) -> List[float]:
        """Helper to extract numeric values from items (nodes or values).

        Args:
            items: A node, list of nodes, list of values, or single value

        Returns:
            List of numeric values (floats)
        """
        if items is None:
            return []

        # Normalize to list
        if not isinstance(items, list):
            items = [items]

        values = []
        for item in items:
            # Extract value from node if needed
            if hasattr(item, 'get_value'):
                val = item.get_value()
            elif hasattr(item, 'value'):
                val = item.value
            else:
                val = item

            # Convert to numeric
            if val is None:
                continue
            if isinstance(val, (int, float)):
                values.append(float(val))
            elif isinstance(val, str):
                val_stripped = val.strip()
                if not val_stripped:
                    continue
                # Handle hex
                if val_stripped.lower().startswith('0x'):
                    try:
                        values.append(float(int(val_stripped, 16)))
                    except ValueError:
                        continue
                else:
                    try:
                        values.append(float(val_stripped))
                    except ValueError:
                        continue
            elif isinstance(val, bool):
                values.append(1.0 if val else 0.0)

        return values

    def xpath_sum(self, items: Any) -> float:
        """XPath sum() - Sum of numeric values in a node-set.

        Args:
            items: A node-set or list of numeric values

        Returns:
            Sum of all numeric values (0 if empty)
        """
        values = self._extract_numeric_values(items)
        return sum(values) if values else 0.0

    def xpath_avg(self, items: Any) -> float:
        """XPath avg() - Average of numeric values (XPath 2.0 extension).

        Args:
            items: A node-set or list of numeric values

        Returns:
            Average of all numeric values (0 if empty)
        """
        values = self._extract_numeric_values(items)
        if not values:
            return 0.0
        return sum(values) / len(values)

    def xpath_min(self, items: Any) -> Optional[float]:
        """XPath min() - Minimum numeric value in a node-set.

        Args:
            items: A node-set or list of numeric values

        Returns:
            Minimum value, or None if empty
        """
        values = self._extract_numeric_values(items)
        if not values:
            return None
        return min(values)

    def xpath_max(self, items: Any) -> Optional[float]:
        """XPath max() - Maximum numeric value in a node-set.

        Args:
            items: A node-set or list of numeric values

        Returns:
            Maximum value, or None if empty
        """
        values = self._extract_numeric_values(items)
        if not values:
            return None
        return max(values)

    # ========== Math Functions ==========

    def xpath_round(self, value: Any) -> int:
        """XPath round() - Round to nearest integer.

        Uses "round half away from zero" semantics (XPath standard):
        - round(2.5) = 3
        - round(-2.5) = -3

        Args:
            value: Numeric value to round

        Returns:
            Rounded integer
        """
        if value is None:
            return 0

        # Unwrap node
        if hasattr(value, 'get_value'):
            value = value.get_value()
        elif hasattr(value, 'value'):
            value = value.value

        if isinstance(value, str):
            value = value.strip()
            if value.lower().startswith('0x'):
                try:
                    return int(value, 16)
                except ValueError:
                    return 0
            try:
                value = float(value)
            except ValueError:
                return 0

        if isinstance(value, (int, float)):
            # XPath uses "round half away from zero"
            import math
            if value >= 0:
                return int(math.floor(value + 0.5))
            else:
                return int(math.ceil(value - 0.5))

        return 0

    def xpath_floor(self, value: Any) -> int:
        """XPath floor() - Round down to nearest integer.

        Args:
            value: Numeric value

        Returns:
            Floor of value
        """
        import math

        if value is None:
            return 0

        # Unwrap node
        if hasattr(value, 'get_value'):
            value = value.get_value()
        elif hasattr(value, 'value'):
            value = value.value

        if isinstance(value, str):
            value = value.strip()
            if value.lower().startswith('0x'):
                try:
                    return int(value, 16)
                except ValueError:
                    return 0
            try:
                value = float(value)
            except ValueError:
                return 0

        if isinstance(value, (int, float)):
            return int(math.floor(value))

        return 0

    def xpath_ceiling(self, value: Any) -> int:
        """XPath ceiling() - Round up to nearest integer.

        Args:
            value: Numeric value

        Returns:
            Ceiling of value
        """
        import math

        if value is None:
            return 0

        # Unwrap node
        if hasattr(value, 'get_value'):
            value = value.get_value()
        elif hasattr(value, 'value'):
            value = value.value

        if isinstance(value, str):
            value = value.strip()
            if value.lower().startswith('0x'):
                try:
                    return int(value, 16)
                except ValueError:
                    return 0
            try:
                value = float(value)
            except ValueError:
                return 0

        if isinstance(value, (int, float)):
            return int(math.ceil(value))

        return 0

    def xpath_abs(self, value: Any) -> float:
        """XPath abs() - Absolute value (XPath 2.0).

        Args:
            value: Numeric value

        Returns:
            Absolute value
        """
        if value is None:
            return 0.0

        # Unwrap node
        if hasattr(value, 'get_value'):
            value = value.get_value()
        elif hasattr(value, 'value'):
            value = value.value

        if isinstance(value, str):
            value = value.strip()
            if value.lower().startswith('0x'):
                try:
                    return abs(int(value, 16))
                except ValueError:
                    return 0.0
            try:
                value = float(value)
            except ValueError:
                return 0.0

        if isinstance(value, (int, float)):
            return abs(value)

        return 0.0

    def xpath_number(self, value: Any = None) -> float:
        """XPath number() - Convert a value to a number.

        Args:
            value: Value to convert to number

        Returns:
            Numeric value as float
        """
        if value is None:
            return float('nan')

        # Unwrap node
        if hasattr(value, 'get_value'):
            value = value.get_value()
        elif hasattr(value, 'value'):
            value = value.value

        if isinstance(value, bool):
            return 1.0 if value else 0.0

        if isinstance(value, (int, float)):
            return float(value)

        if isinstance(value, str):
            value = value.strip()
            if value.lower().startswith('0x'):
                try:
                    return float(int(value, 16))
                except ValueError:
                    return float('nan')
            try:
                return float(value)
            except ValueError:
                return float('nan')

        return float('nan')

    # ========== Additional String Functions ==========

    def xpath_translate(self, s: Any, from_chars: str, to_chars: str) -> str:
        """XPath translate() - Character-by-character replacement.

        Each character in 'from_chars' is replaced by the corresponding
        character in 'to_chars'. If 'from_chars' is longer, extra characters
        are deleted.

        Example:
            translate('bar', 'abc', 'ABC') = 'BAr'
            translate('--aaa--', 'abc-', 'ABC') = 'AAA' (- is deleted)

        Args:
            s: Source string
            from_chars: Characters to replace
            to_chars: Replacement characters

        Returns:
            Translated string
        """
        if s is None:
            return ""

        # Unwrap node
        if hasattr(s, 'get_value'):
            s = s.get_value()
        elif hasattr(s, 'value'):
            s = s.value

        s = str(s) if s is not None else ""
        from_chars = str(from_chars) if from_chars else ""
        to_chars = str(to_chars) if to_chars else ""

        # Build translation table
        result = []
        for char in s:
            if char in from_chars:
                idx = from_chars.index(char)
                if idx < len(to_chars):
                    result.append(to_chars[idx])
                # else: character is deleted (from_chars longer than to_chars)
            else:
                result.append(char)

        return ''.join(result)

    def xpath_starts_with(self, s: Any, prefix: str) -> bool:
        """XPath starts-with() - Check if string starts with prefix.

        Args:
            s: Source string
            prefix: Prefix to check

        Returns:
            True if s starts with prefix
        """
        if s is None:
            return prefix == "" or prefix is None

        # Unwrap node
        if hasattr(s, 'get_value'):
            s = s.get_value()
        elif hasattr(s, 'value'):
            s = s.value

        s = str(s) if s is not None else ""
        prefix = str(prefix) if prefix else ""

        return s.startswith(prefix)

    def xpath_ends_with(self, s: Any, suffix: str) -> bool:
        """XPath ends-with() - Check if string ends with suffix (XPath 2.0).

        Args:
            s: Source string
            suffix: Suffix to check

        Returns:
            True if s ends with suffix
        """
        if s is None:
            return suffix == "" or suffix is None

        # Unwrap node
        if hasattr(s, 'get_value'):
            s = s.get_value()
        elif hasattr(s, 'value'):
            s = s.value

        s = str(s) if s is not None else ""
        suffix = str(suffix) if suffix else ""

        return s.endswith(suffix)

    def xpath_format_number(self, number: Any, format_str: str, decimal_format: str = None) -> str:
        """XPath format-number() - Format a number according to a pattern.

        Supports common format patterns:
        - '#' - Digit, zero shows as absent
        - '0' - Digit, zero shows as 0
        - '.' - Decimal separator
        - ',' - Grouping separator
        - '%' - Multiply by 100 and show as percentage

        Examples:
            format-number(1234.5, '#,###.##') = '1,234.5'
            format-number(0.75, '#.00') = '.75'
            format-number(0.75, '0.00') = '0.75'
            format-number(0.5, '#%') = '50%'

        Args:
            number: Number to format
            format_str: Format pattern
            decimal_format: Optional decimal format name (ignored in this impl)

        Returns:
            Formatted number string
        """
        if number is None:
            return ""

        # Unwrap node
        if hasattr(number, 'get_value'):
            number = number.get_value()
        elif hasattr(number, 'value'):
            number = number.value

        # Convert to float
        if isinstance(number, str):
            number = number.strip()
            if number.lower().startswith('0x'):
                try:
                    number = int(number, 16)
                except ValueError:
                    return ""
            else:
                try:
                    number = float(number)
                except ValueError:
                    return ""

        if not isinstance(number, (int, float)):
            return ""

        format_str = str(format_str) if format_str else "#"

        # Handle percentage
        is_percent = '%' in format_str
        if is_percent:
            number = number * 100
            format_str = format_str.replace('%', '')

        # Parse format pattern
        use_grouping = ',' in format_str
        format_str = format_str.replace(',', '')

        # Split into integer and decimal parts
        if '.' in format_str:
            int_fmt, dec_fmt = format_str.split('.', 1)
        else:
            int_fmt = format_str
            dec_fmt = ""

        # Determine decimal places
        dec_places = len(dec_fmt)

        # Format the number
        if dec_places > 0:
            formatted = f"{number:.{dec_places}f}"
        else:
            formatted = str(int(round(number)))

        # Split formatted number
        if '.' in formatted:
            int_part, dec_part = formatted.split('.')
        else:
            int_part = formatted
            dec_part = ""

        # Handle integer format (leading zeros vs optional digits)
        min_int_digits = int_fmt.count('0')
        if min_int_digits > 0 and len(int_part.lstrip('-')) < min_int_digits:
            sign = '-' if int_part.startswith('-') else ''
            int_part = sign + int_part.lstrip('-').zfill(min_int_digits)

        # Add grouping separators
        if use_grouping:
            sign = ''
            if int_part.startswith('-'):
                sign = '-'
                int_part = int_part[1:]
            # Add commas every 3 digits from the right
            int_part = sign + ','.join([
                int_part[max(0, i-3):i]
                for i in range(len(int_part), 0, -3)
            ][::-1])

        # Handle decimal format
        if dec_fmt:
            # Determine min decimal digits (count of '0')
            min_dec_digits = dec_fmt.count('0')
            # Pad or trim decimal part
            if len(dec_part) < min_dec_digits:
                dec_part = dec_part.ljust(min_dec_digits, '0')
            # Strip trailing zeros for '#' positions
            optional_positions = len(dec_fmt) - min_dec_digits
            if optional_positions > 0:
                # Keep at least min_dec_digits
                while len(dec_part) > min_dec_digits and dec_part.endswith('0'):
                    dec_part = dec_part[:-1]
            result = f"{int_part}.{dec_part}" if dec_part else int_part
        else:
            result = int_part

        # Add percent sign back
        if is_percent:
            result += '%'

        return result

    # ========== Special XPath Functions ==========

    def xpath_document(self, uri: Any, base: Any = None) -> Optional[Any]:
        """XPath document() - Load external XML document.

        Note: This is a limited implementation. Full external document
        loading is not supported in this context. Returns None with a warning.

        Args:
            uri: URI of the document to load
            base: Optional base URI for resolution

        Returns:
            None (external documents not supported)
        """
        from .renderer import _debug_log
        _debug_log(f"WARNING: document('{uri}') - external document loading not supported")
        return None

    def xpath_id(self, id_value: Any) -> Optional[Any]:
        """XPath id() - Select element by ID.

        Note: This requires DTD/Schema ID attribute declarations which
        are not available in this AUTOSAR configuration context.
        Falls back to searching for elements with matching short_name.

        Args:
            id_value: ID value to search for (can be space-separated list)

        Returns:
            Matching node(s) or None
        """
        if id_value is None:
            return None

        # Unwrap node
        if hasattr(id_value, 'get_value'):
            id_value = id_value.get_value()
        elif hasattr(id_value, 'value'):
            id_value = id_value.value

        id_str = str(id_value) if id_value else ""
        ids = id_str.split()

        if not ids:
            return None

        # Search for nodes with matching short_name
        results = []
        for module in self.symbol_table.get_all_modules():
            module_node = self.symbol_table.get_module(module)
            if module_node:
                for child in module_node.get_children_recursive():
                    if hasattr(child, 'short_name') and child.short_name in ids:
                        results.append(child)

        if not results:
            return None
        if len(results) == 1:
            return results[0]
        return results

    def xpath_key(self, key_name: str, value: Any) -> Optional[Any]:
        """XPath key() - Select elements using a key defined by xsl:key.

        Note: This requires XSLT key definitions which are not available.
        This is a stub implementation that always returns None.

        Args:
            key_name: Name of the key (as defined in xsl:key)
            value: Value to look up

        Returns:
            None (key definitions not supported)
        """
        from .renderer import _debug_log
        _debug_log(f"WARNING: key('{key_name}', '{value}') - XSLT key definitions not supported")
        return None

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
        for child in node.children:
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

        # Helper: ecu:get always returns scalar/string (not list).
        # Lists are for ecu:list(). If value is a list, join back to
        # space-separated string to match EB Tresos ecu:get() semantics.
        def _as_scalar(val):
            if isinstance(val, list):
                return ' '.join(str(v) for v in val) + ' '
            return val

        # 1. User override (retained for testing)
        # Try exact match first (flat key like "Eth.MaxTxRam")
        if path in self.ecu_resources:
            return _as_scalar(self.ecu_resources[path])
            return _as_scalar(raw)

        # Try nested match (if ecu_resources is structured as {module: {param: val}})
        if '.' in path:
            p_parts = path.split('.')
            curr = self.ecu_resources
            for p in p_parts:
                if isinstance(curr, dict) and p in curr:
                    curr = curr[p]
                else:
                    curr = None
                    break
            if curr is not None:
                return _as_scalar(curr)

        # 2. Parse path "Module.ParamName" or "Module.Container.ParamName"

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
                for child in current.children:
                    if child.short_name == part:
                        current = child
                        found = True
                        break
                if not found:
                    break
            else:
                # Exact path traversal succeeded, look for param in this container
                for child in current.children:
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

    def ecu_has(self, path: str) -> bool:
        """Check if an ECU resource parameter exists.

        Same lookup logic as ecu:get but returns boolean.
        """
        result = self.ecu_get(path)
        return result is not None and result != ''

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

    def bit_getbit(self, value: Any, bit_pos: Any) -> str:
        """Get the value of a specific bit.
        
        Args:
            value: The integer value to check
            bit_pos: The bit position (0-indexed)
            
        Returns:
            'true' if the bit is set, 'false' otherwise
        """
        int_val = self.num_i(value)
        bit_pos_val = self.num_i(bit_pos)
        
        if (int_val >> bit_pos_val) & 1:
            return 'true'
        else:
            return 'false'

    def bit_bitset(self, value: Any, bit_pos: Any) -> int:
        """Sets a specific bit in an integer value.
        
        Args:
            value: The integer value to modify.
            bit_pos: The bit position to set (0-indexed).
            
        Returns:
            The integer with the specified bit set to 1.
        """
        int_val = self.num_i(value)
        bit_pos_val = self.num_i(bit_pos)
        
        return int_val | (1 << bit_pos_val)

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



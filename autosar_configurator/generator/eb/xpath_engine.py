"""
XPath Engine for EB Template Engine

Implements XPath 2.0 subset for AUTOSAR configuration navigation:
- Axes: child:: (default), parent:: (..), descendant:: (//), absolute (/)
- Predicates: [index], [condition], [@attr='value']
- Path navigation against ConfigurationNode tree
"""
import re
import tempfile
import os
from typing import Any, List, Optional, Union, TYPE_CHECKING

# Debug log file path - cross-platform
_DEBUG_LOG_PATH = os.path.join(tempfile.gettempdir(), 'bsw_gen.log')

def _debug_log(msg: str):
    """Helper to write diagnostic logs to a fixed file for worker threads."""
    try:
        with open(_DEBUG_LOG_PATH, 'a') as f:
            f.write(msg + '\n')
    except (IOError, OSError):
        pass  # Silently ignore file write errors in debug logging

if TYPE_CHECKING:
    from .symbol_table import ConfigurationNode, SymbolTable
    from .context import ContextStack


class XPathEngine:
    """XPath-like query engine for ConfigurationNode tree"""
    
    def __init__(self, symbol_table: 'SymbolTable', context_stack: 'ContextStack', function_handler=None):
        self.symbol_table = symbol_table
        self.context_stack = context_stack
        self.function_handler = function_handler
    
    def evaluate(self, xpath: str) -> Any:
        """Evaluate an XPath expression.
        
        Args:
            xpath: XPath expression string
            
        Returns:
            Single node, list of nodes, or None
        """
        xpath = xpath.strip()
        
        # Handle function calls like as:modconf('Mcu')
        if '(' in xpath and ')' in xpath:
            # Check if it is a predicate like [contains(., 'x')] - heuristic
            # If it starts with a function call pattern
            if re.match(r'^[\w:]+\s*\(', xpath):
                return self._evaluate_function(xpath)
        
        # Handle absolute path
        if xpath.startswith('/'):
            return self._evaluate_absolute(xpath)
        
        # Handle current node
        if xpath == '.' or xpath == 'node:current()':
            return self.context_stack.current_node()
        
        # Handle relative path from current context
        # Or variable-based path $Var/child
        if xpath.startswith('$'):
            # Variable reference start
            parts = xpath.split('/', 1)
            var_name = parts[0][1:] # Strip $
            if self.context_stack.has_variable(var_name):
                var_value = self.context_stack.get_variable(var_name)
                # If variable holds a Node (like from node:ref), use it as context
                if hasattr(var_value, 'node_type'):
                    if len(parts) > 1:
                        # Continue navigation relative to this node
                        return self._evaluate_relative(parts[1], var_value)
                    else:
                        return var_value
                else:
                    # Variable holds a primitive value (string, number, bool, list)
                    return var_value
            else:
                # Variable not defined - return None/empty (common when Resource module not loaded)
                return None

        
        return self._evaluate_relative(xpath)
    
    # ... (rest of methods)

    def _evaluate_function(self, expr: str) -> Any:
        """Evaluate function calls in XPath expression"""
        # as:modconf('ModuleName') possibly followed by path or predicates
        match = re.match(r"(?i)as:modconf\s*\(\s*['\"](\w+)['\"]\s*\)(.*)", expr)
        if match:
            module_name = match.group(1)
            rest_path = match.group(2)
            
            # Use function_handler if available to support synthetic fallbacks
            if self.function_handler and hasattr(self.function_handler, 'as_modconf'):
                module = self.function_handler.as_modconf(module_name)
            else:
                module = self.symbol_table.get_module(module_name)
                
            if not module:
                _debug_log(f"DEBUG: as:modconf('{module_name}') - Module NOT FOUND")
                return None
            else:
                _debug_log(f"DEBUG: as:modconf('{module_name}') - Module FOUND")

            
            if rest_path:
                # Handle predicates on the function result itself
                if rest_path.startswith('['):
                    bracket_depth = 0
                    for i, char in enumerate(rest_path):
                        if char == '[': bracket_depth += 1
                        elif char == ']': 
                            bracket_depth -= 1
                            if bracket_depth == 0:
                                pred_str = rest_path[1:i]
                                module_list = self._apply_predicates([module], [pred_str])
                                if not module_list: return None
                                module = module_list[0]
                                rest_path = rest_path[i+1:]
                                break
                    
                if rest_path:
                    # Continue navigation
                    rest_path = rest_path.lstrip('/')
                    if rest_path:
                        segments = self._parse_path(rest_path)
                        return self._navigate_segments(module, segments)
            return module
            
        # count(path)
        if expr.startswith('count(') and expr.endswith(')'):
            inner = expr[6:-1].strip()
            res = self.evaluate(inner)
            if res is None:
                return 0
            if isinstance(res, list):
                return len(res)
            return 1 # Single node
            
        # Generic function handler via callback
        if self.function_handler:
            # Parse function name and arguments (handle nested parens and trailing predicates)
            match = re.match(r"^([\w:]+)\s*\(", expr)
            if match:
                func_name = match.group(1)
                start_args = match.end()
                
                # Find matching close paren
                depth = 1
                args_end = -1
                for i in range(start_args, len(expr)):
                    if expr[i] == '(': depth += 1
                    elif expr[i] == ')': depth -= 1
                    
                    if depth == 0:
                        args_end = i
                        break
            
            if args_end != -1:
                args_str = expr[start_args:args_end].strip()
                rest_path = expr[args_end + 1:].strip()
                
                # Parse arguments properly (comma separated, respecting parens and quotes)
                args = []
                if args_str:
                    arg_depth = 0
                    arg_in_quote = None
                    current_arg = []
                    for char in args_str:
                        if char in ('"', "'"):
                            if arg_in_quote == char: arg_in_quote = None
                            elif arg_in_quote is None: arg_in_quote = char
                        
                        if arg_in_quote is None:
                            if char == '(': arg_depth += 1
                            elif char == ')': arg_depth -= 1
                            elif char == ',' and arg_depth == 0:
                                args.append(''.join(current_arg).strip())
                                current_arg = []
                                continue
                        current_arg.append(char)
                    if current_arg:
                        args.append(''.join(current_arg).strip())
                
                # Evaluate arguments
                evaluated_args = []
                for arg in args:
                    arg = arg.strip()
                    if (arg.startswith('"') and arg.endswith('"')) or \
                       (arg.startswith("'") and arg.endswith("'")):
                        evaluated_args.append(arg[1:-1])
                    else:
                        val = self.evaluate(arg)
                        evaluated_args.append(val)
                
                # Execute function
                result = None
                if func_name == 'as:modconf':
                    # Special handling for standard as:modconf
                    mod_name = evaluated_args[0] if evaluated_args else ""
                    result = self.symbol_table.get_module(mod_name)
                elif self.function_handler and hasattr(self.function_handler, 'call'):
                    result = self.function_handler.call(func_name, *evaluated_args)
                elif callable(self.function_handler):
                    result = self.function_handler(func_name, *evaluated_args)
                
                # Apply trailing predicates/path if present
                if result is not None and rest_path:
                    # Strip leading / from rest_path if it's there
                    if rest_path.startswith('/'):
                        rest_path = rest_path[1:]

                    if rest_path:
                        # Handle predicates [n]
                        if rest_path.startswith('['):
                             # ... existing predicate logic ...
                             bracket_depth = 0
                             for i, char in enumerate(rest_path):
                                 if char == '[': bracket_depth += 1
                                 elif char == ']':
                                     bracket_depth -= 1
                                     if bracket_depth == 0:
                                         pred_str = rest_path[1:i]

                                         # Special handling for simple lists (e.g., from text:split)
                                         # If result is a list of non-node items, handle index directly
                                         if isinstance(result, list) and result and not hasattr(result[0], 'node_type'):
                                             # Try to get numeric index
                                             idx = None
                                             if pred_str.isdigit():
                                                 idx = int(pred_str) - 1  # XPath is 1-indexed
                                             elif '(' in pred_str and ')' in pred_str:
                                                 # Evaluate expression like num:i($ModuleIndex)
                                                 try:
                                                     eval_result = self.evaluate(pred_str)
                                                     if isinstance(eval_result, (int, float)):
                                                         idx = int(eval_result) - 1
                                                 except:
                                                     pass

                                             if idx is not None and 0 <= idx < len(result):
                                                 result = result[idx]
                                             else:
                                                 result = None
                                         else:
                                             # Standard node list handling
                                             res_list = result if isinstance(result, list) else [result]
                                             result = self._apply_predicates(res_list, [pred_str])
                                             # Unwrap if single item
                                             if isinstance(result, list) and len(result) == 1:
                                                 result = result[0]
                                             elif isinstance(result, list) and not result:
                                                 result = None

                                         rest_path = rest_path[i+1:]
                                         break
                        
                        if rest_path:
                             if rest_path.startswith('/'): rest_path = rest_path[1:]
                             if rest_path:
                                 # Only navigate if result is a node (has node_type) or list of nodes
                                 # Don't try to navigate on primitive types like bool, int, str
                                 if hasattr(result, 'node_type') or (isinstance(result, list) and result and hasattr(result[0], 'node_type')):
                                     segments = self._parse_path(rest_path)
                                     return self._navigate_segments(result, segments)
                                 else:
                                     # Cannot navigate on primitive result
                                     return None
                                 
                return result
        
        return None
    
    def _evaluate_absolute(self, xpath: str) -> Any:
        """Evaluate absolute path like /Mcu/McuConfig"""
        # Try direct path lookup
        node = self.symbol_table.get_by_path(xpath)
        if node:
            return node
        
        # Try parsing as module/path
        parts = [p for p in xpath.split('/') if p]
        if not parts:
            return None
        
        # First part might be module name
        module = self.symbol_table.get_module(parts[0])
        if module:
            return self._navigate_path(module, parts[1:])
        
        return None
    
    def _evaluate_relative(self, xpath: str, context_node: Optional['ConfigurationNode'] = None) -> Any:
        """Evaluate relative path from current context"""
        current = context_node or self.context_stack.current_node()
        if not current:
            return None
        
        # Strip leading ./
        if xpath.startswith('./'):
            xpath = xpath[2:]
        
        # Parse path segments with predicates
        segments = self._parse_path(xpath)
        return self._navigate_segments(current, segments)
    
    def _parse_path(self, xpath: str) -> List[dict]:
        """Parse path into segments with optional predicates.
        
        Returns list of {'name': str, 'predicates': list, 'axis': str}
        """
        segments = []
        
        # Handle descendant axis //
        if xpath.startswith('//'):
            xpath = xpath[2:]
            # First segment uses descendant axis
            first_segment_axis = 'descendant'
        else:
            first_segment_axis = 'child'
        
        # Split by / but preserve predicates
        parts = []
        current = ""
        bracket_depth = 0
        
        for char in xpath:
            if char == '[':
                bracket_depth += 1
                current += char
            elif char == ']':
                bracket_depth -= 1
                current += char
            elif char == '/' and bracket_depth == 0:
                if current:
                    parts.append(current)
                current = ""
            else:
                current += char
        if current:
            parts.append(current)
        
        for i, part in enumerate(parts):
            axis = first_segment_axis if i == 0 else 'child'
            
            # Check for parent axis
            if part == '..':
                segments.append({'name': '..', 'predicates': [], 'axis': 'parent'})
                continue
            
            # Parse name and predicates
            name, predicates = self._parse_segment(part)
            segments.append({'name': name, 'predicates': predicates, 'axis': axis})
        
        return segments
    
    def _parse_segment(self, segment: str) -> tuple:
        """Parse a single segment like 'Container[1]' or 'Param[@name="x"]'
        
        Returns (name, list_of_predicates)
        """
        predicates = []
        
        # Find predicates [...]
        match = re.match(r'^([^\[]+)(.*)', segment)
        if not match:
            return segment, []
        
        name = match.group(1)
        predicate_str = match.group(2)
        
        # Extract all predicates
        for pred_match in re.finditer(r'\[([^\]]+)\]', predicate_str):
            predicates.append(pred_match.group(1))
        
        return name, predicates
    
    def _navigate_segments(self, node: 'ConfigurationNode', segments: List[dict]) -> Any:
        """Navigate through path segments from a starting node"""
        # Safety check: ensure node is a valid ConfigurationNode, not a primitive type
        if node is None:
            current = []
        elif hasattr(node, 'node_type'):
            current = [node]
        elif isinstance(node, list):
            # Filter out any non-node items from the list
            current = [n for n in node if hasattr(n, 'node_type')]
        else:
            # Primitive type (bool, int, str) - cannot navigate
            return None

        for segment in segments:
            if not current:
                return None
            
            next_nodes = []
            axis = segment['axis']
            name = segment['name']
            predicates = segment['predicates']
            
            for n in current:
                if axis == 'parent':
                    if n.parent:
                        next_nodes.append(n.parent)
                elif axis == 'descendant':
                    next_nodes.extend(self._find_descendants(n, name))
                else:  # child axis
                    if name == '*':
                        next_nodes.extend(n.get_children_list())
                    elif name == '.':
                        next_nodes.append(n)
                    else:
                        child = n.get_child(name)
                        if child:
                            next_nodes.append(child)
                        else:
                            # Fallback: Case-insensitive lookup (Robustness for CanControllerId vs canControllerId)
                            for c_name, c_node in n.children.items():
                                if c_name.lower() == name.lower():
                                    next_nodes.append(c_node)
                                    child = c_node
                                    break

                            if child:
                                continue

                            # EB Tresos implicit instance traversal:
                            # If we're at a container definition and can't find the child directly,
                            # look inside all instance children (e.g., AdcConfigSet -> AdcConfigSet_0 -> AdcHwUnit)
                            # This supports paths like "AdcConfigSet/AdcHwUnit/*" where AdcHwUnit is under instances
                            for c_name, c_node in n.children.items():
                                # Check if this child is an instance of the current container
                                # (has same definition_ref or name starts with parent's name)
                                is_instance = (
                                    c_node.definition_ref and
                                    (c_node.definition_ref == n.definition_ref or
                                     c_node.definition_ref.endswith(f"/{n.short_name}"))
                                )
                                if is_instance and hasattr(c_node, 'children'):
                                    # Look for the target name inside this instance
                                    instance_child = c_node.get_child(name)
                                    if instance_child:
                                        next_nodes.append(instance_child)

                            # Fallback: check if we have a transparent container issue
                            # e.g. parent 'CanHwFilter' contains child 'CanHwFilter'?
                            # In some ARXMLs, SUB-CONTAINER logic might result in strict nesting
                            # If we didn't find 'CanHwFilterCode' in 'CanHwFilter',
                            # check if 'CanHwFilter' has a child 'CanHwFilter' (sub-container)
                            if n.short_name == 'CanHwFilter' and 'CanHwFilter' in n.children:
                                sub = n.get_child('CanHwFilter')
                                deep_child = sub.get_child(name)
                                if deep_child:
                                    next_nodes.append(deep_child)
                                    # DEBUG: Found via implicit recursion
                                    # print(f"DEBUG_XPATH: Found {name} inside nested {n.short_name}")
                                    continue

                            # EB Tresos behavior: if not found by short_name, match by definition name

                            found_by_def = False
                            for c in n.get_children_list():
                                if c.definition_ref and (c.definition_ref == name or c.definition_ref.endswith(f"/{name}")):
                                    next_nodes.append(c)
                                    found_by_def = True

                            if not found_by_def:
                                pass







            
            # Apply predicates
            current = self._apply_predicates(next_nodes, predicates)
        
        # Return single node or list
        if len(current) == 0:
            return None
        elif len(current) == 1:
            return current[0]
        else:
            return current
    
    def _navigate_path(self, node: 'ConfigurationNode', parts: List[str]) -> Any:
        """Simple path navigation (legacy support)"""
        current = node
        for part in parts:
            if not current:
                return None
            if part == '..':
                current = current.parent
            else:
                current = current.get_child(part)
        return current
    
    def _find_descendants(self, node: 'ConfigurationNode', name: str) -> List['ConfigurationNode']:
        """Find all descendants matching name (// axis)"""
        results = []
        
        for child in node.children.values():
            if name == '*' or child.short_name == name:
                results.append(child)
            results.extend(self._find_descendants(child, name))
        
        return results
    
    def _apply_predicates(self, nodes: List['ConfigurationNode'], predicates: List[str]) -> List['ConfigurationNode']:
        """Apply predicate filters to node list.

        Also handles simple lists (e.g., from text:split) when the predicate is a numeric index.
        """
        result = nodes

        for pred in predicates:
            pred = pred.strip()

            # Numeric index [1], [2], etc.
            if pred.isdigit():
                idx = int(pred) - 1  # XPath is 1-indexed
                if 0 <= idx < len(result):
                    result = [result[idx]]
                else:
                    result = []
                continue

            # last() function
            if pred == 'last()' or pred == 'last':
                result = [result[-1]] if result else []
                continue

            # Try to evaluate the predicate as an expression that returns a number
            # This handles cases like [num:i($ModuleIndex)] used with text:split
            if '(' in pred and ')' in pred:
                try:
                    # Evaluate the predicate expression
                    eval_result = self.evaluate(pred)
                    if isinstance(eval_result, (int, float)):
                        idx = int(eval_result) - 1  # XPath is 1-indexed
                        if 0 <= idx < len(result):
                            result = [result[idx]]
                        else:
                            result = []
                        continue
                except:
                    pass  # Fall through to other predicate handling

            # Attribute filter [@name='value']
            attr_match = re.match(r"@(\w+)\s*=\s*['\"]([^'\"]+)['\"]", pred)
            if attr_match:
                attr_name = attr_match.group(1)
                attr_value = attr_match.group(2)
                result = [n for n in result if self._check_attribute(n, attr_name, attr_value)]
                continue

            # General condition - evaluate as boolean
            result = [n for n in result if self._evaluate_predicate_condition(n, pred)]

        return result
    
    def _check_attribute(self, node: 'ConfigurationNode', attr: str, value: str) -> bool:
        """Check if node has attribute matching value"""
        if attr == 'name':
            return node.short_name == value
        if attr == 'path':
            return node.path == value
        if attr == 'type':
            return node.node_type == value
        
        # Check in children (for parameter-like access)
        child = node.get_child(attr)
        if child:
            return str(child.get_value()) == value
        
        return False
    
    def _evaluate_predicate_condition(self, node: 'ConfigurationNode', condition: str) -> bool:
        """Evaluate a predicate condition in context of a node.
        
        Supports:
        - Simple existence check: [ParamName]
        - Equality: [ParamName = 'Value']
        - Inequality: [ParamName != 'Value']  
        - Numeric comparisons: [ParamName > 5]
        """
        import re
        
        # Check for equality comparison: Name = 'Value' or Name = "Value"
        # Supports ChildName or . (self)
        eq_match = re.match(r"""^\s*([\w.]+)\s*=\s*['"]([^'"]*)['"]\s*$""", condition)
        if eq_match:
            name = eq_match.group(1)
            expected_value = eq_match.group(2)
            
            if name == '.':
                actual_value = node.get_value() if hasattr(node, 'get_value') else node.value
            else:
                child = node.get_child(name)
                if child:
                    actual_value = child.get_value()
                else:
                    return False
            
            # Truthiness normalization
            def to_bool_str(v):
                if v is None: return "false"
                if isinstance(v, bool): return "true" if v else "false"
                s = str(v).lower()
                if s in ('true', '1', 'yes', 'on', 'std_on'): return "true"
                if s in ('false', '0', 'no', 'off', 'std_off'): return "false"
                return s

            if expected_value.lower() in ('true', 'false'):
                return to_bool_str(actual_value) == expected_value.lower()
            
            return str(actual_value) == expected_value

        
        # Check for inequality: ChildName != 'Value'
        neq_match = re.match(r"""^\s*(\w+)\s*!=\s*['"]([^'"]*)['"]\s*$""", condition)
        if neq_match:
            child_name = neq_match.group(1)
            expected_value = neq_match.group(2)
            child = node.get_child(child_name)
            if child:
                actual_value = child.get_value()
                return str(actual_value) != expected_value
            return True  # If child doesn't exist, it's not equal
        
        # Check for numeric comparisons: ChildName > 5, ChildName < 10
        num_match = re.match(r"""^\s*(\w+)\s*([<>]=?)\s*(\d+)\s*$""", condition)
        if num_match:
            child_name = num_match.group(1)
            operator = num_match.group(2)
            compare_value = int(num_match.group(3))
            child = node.get_child(child_name)
            if child:
                try:
                    actual_value = int(child.get_value())
                    if operator == '>':
                        return actual_value > compare_value
                    elif operator == '<':
                        return actual_value < compare_value
                    elif operator == '>=':
                        return actual_value >= compare_value
                    elif operator == '<=':
                        return actual_value <= compare_value
                except (ValueError, TypeError):
                    return False
            return False
        
        # Boolean value check (true/false): ChildName = 'true' or just ChildName
        bool_match = re.match(r"""^\s*(\w+)\s*=\s*['"]?(true|false)['"]?\s*$""", condition, re.IGNORECASE)
        if bool_match:
            child_name = bool_match.group(1)
            expected = bool_match.group(2).lower() == 'true'
            child = node.get_child(child_name)
            if child:
                val = child.get_value()
                if isinstance(val, bool):
                    return val == expected
                return str(val).lower() == str(expected).lower()
            return False
        
        # Simple existence check: [ParamName]
        if hasattr(node, 'get_child'):
            child = node.get_child(condition.strip())
            if child:
                val = child.get_value()
                # Return True if value exists and is truthy
                if val is None:
                    return False
                if isinstance(val, bool):
                    return val
                if isinstance(val, str):
                    return val.lower() not in ('false', '', '0')
                return bool(val)
        
        return False

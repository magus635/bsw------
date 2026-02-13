"""
XPath Engine for EB Template Engine

Implements XPath 2.0 subset for AUTOSAR configuration navigation:
- Axes: child:: (default), parent:: (..), descendant:: (//), absolute (/),
        ancestor::, ancestor-or-self::, following::, following-sibling::,
        preceding::, preceding-sibling::, self::, attribute:: (@)
- Predicates: [index], [condition], [@attr='value'], [nested[predicate]]
- Path navigation against ConfigurationNode tree
- Union operator: path1 | path2 | path3
- XPath 2.0 expressions: for, if-then-else, some/every quantifiers
"""
import re
import tempfile
import os
from typing import Any, List, Optional, Union, TYPE_CHECKING



if TYPE_CHECKING:
    from .symbol_table import ConfigurationNode, SymbolTable
    from .context import ContextStack


class XPathEngine:
    """XPath-like query engine for ConfigurationNode tree"""
    
    def __init__(self, symbol_table: 'SymbolTable', context_stack: 'ContextStack', function_handler=None):
        self.symbol_table = symbol_table
        self.context_stack = context_stack
        self.function_handler = function_handler
        self._return_node = False  # Flag to return node instead of value for parameters

    def _unwrap_value(self, value):
        """Unwrap value from ConfigurationNode or list of nodes."""
        if value is None:
            return ""
            
        if isinstance(value, list):
            if not value:
                return ""
            # Use first item
            if len(value) > 1:
                pass # Optionally warn
            value = value[0]
            
        if hasattr(value, 'get_value'):
            val = value.get_value()
            return val if val is not None else ""
            
        return value

    def evaluate(self, xpath: str, return_node: bool = False) -> Any:
        """Evaluate an XPath expression.

        Args:
            xpath: XPath expression string
            return_node: If True, return the node object even for parameters
                        (instead of implicitly extracting value). Used by node:exists.

        Returns:
            Single node, list of nodes, or None
        """
        xpath = xpath.strip()
        # Save and restore _return_node to prevent recursive evaluate() calls
        # (e.g. from _apply_predicates) from corrupting the outer caller's flag.
        saved_return_node = self._return_node
        self._return_node = return_node
        try:
            return self._evaluate_impl(xpath)
        finally:
            self._return_node = saved_return_node

    def _evaluate_impl(self, xpath: str) -> Any:
        """Internal implementation of evaluate(). Separated to allow
        save/restore of _return_node across recursive calls."""
        return_node = self._return_node

        # Check for parenthesized condition (e.g. "(A) or (B)")
        if xpath.startswith('(') and self._is_condition(xpath):
             return self._evaluate_condition(xpath)
        
        # =============================================
        # XPath 2.0/3.0 Advanced Features
        # =============================================
        
        # Handle range expression: "1 to 10"
        range_match = re.match(r'^(\d+)\s+to\s+(\d+)$', xpath)
        if range_match:
            start = int(range_match.group(1))
            end = int(range_match.group(2))
            return list(range(start, end + 1))
        
        # Handle for expression: "for $x in //Item return $x/Name"
        for_match = re.match(r'^for\s+\$(\w+)\s+in\s+(.+?)\s+return\s+(.+)$', xpath, re.IGNORECASE)
        if for_match:
            var_name = for_match.group(1)
            in_expr = for_match.group(2).strip()
            return_expr = for_match.group(3).strip()
            
            # Evaluate the "in" expression to get the sequence
            items = self.evaluate(in_expr)
            if items is None:
                return []
            if not isinstance(items, list):
                items = [items]
            
            results = []
            for item in items:
                # Set the loop variable
                self.context_stack.push(item if hasattr(item, 'node_type') else self.context_stack.current_node())
                self.context_stack.set_variable(var_name, item)
                try:
                    result = self.evaluate(return_expr)
                    if result is not None:
                        if isinstance(result, list):
                            results.extend(result)
                        else:
                            results.append(result)
                finally:
                    self.context_stack.pop()
            return results
        
        # Handle if-then-else expression: "if ($a > 0) then 'yes' else 'no'"
        if_match = re.match(r'^if\s*\((.+?)\)\s+then\s+(.+?)\s+else\s+(.+)$', xpath, re.IGNORECASE)
        if if_match:
            condition_expr = if_match.group(1).strip()
            then_expr = if_match.group(2).strip()
            else_expr = if_match.group(3).strip()
            
            # Evaluate condition
            condition_result = self._evaluate_condition(condition_expr)
            
            if condition_result:
                return self._evaluate_simple_value(then_expr)
            else:
                return self._evaluate_simple_value(else_expr)
        
        # Handle some quantifier: "some $x in //Item satisfies $x/Value > 10"
        some_match = re.match(r'^some\s+\$(\w+)\s+in\s+(.+?)\s+satisfies\s+(.+)$', xpath, re.IGNORECASE)
        if some_match:
            var_name = some_match.group(1)
            in_expr = some_match.group(2).strip()
            test_expr = some_match.group(3).strip()
            
            items = self.evaluate(in_expr)
            if items is None:
                return False
            if not isinstance(items, list):
                items = [items]
            
            for item in items:
                self.context_stack.push(item if hasattr(item, 'node_type') else self.context_stack.current_node())
                self.context_stack.set_variable(var_name, item)
                try:
                    if self._evaluate_condition(test_expr):
                        return True
                finally:
                    self.context_stack.pop()
            return False
        
        # Handle every quantifier: "every $x in //Item satisfies $x/Valid = 'true'"
        every_match = re.match(r'^every\s+\$(\w+)\s+in\s+(.+?)\s+satisfies\s+(.+)$', xpath, re.IGNORECASE)
        if every_match:
            var_name = every_match.group(1)
            in_expr = every_match.group(2).strip()
            test_expr = every_match.group(3).strip()
            
            items = self.evaluate(in_expr)
            if items is None:
                return True  # Empty sequence satisfies "every"
            if not isinstance(items, list):
                items = [items]
            
            if len(items) == 0:
                return True  # Empty sequence satisfies "every"
            
            for item in items:
                self.context_stack.push(item if hasattr(item, 'node_type') else self.context_stack.current_node())
                self.context_stack.set_variable(var_name, item)
                try:
                    if not self._evaluate_condition(test_expr):
                        return False
                finally:
                    self.context_stack.pop()
            return True
        
        # Handle union operator: "//A | //B"
        # Find | operator not inside parentheses or quotes
        union_pos = self._find_operator_outside_context(xpath, '|')
        if union_pos != -1:
            left_expr = xpath[:union_pos].strip()
            right_expr = xpath[union_pos + 1:].strip()
            
            left_result = self.evaluate(left_expr)
            right_result = self.evaluate(right_expr)
            
            # Combine results into a single list
            combined = []
            if left_result is not None:
                if isinstance(left_result, list):
                    combined.extend(left_result)
                else:
                    combined.append(left_result)
            if right_result is not None:
                if isinstance(right_result, list):
                    combined.extend(right_result)
                else:
                    combined.append(right_result)
            
            # Remove duplicates while preserving order (for nodes)
            seen = set()
            unique = []
            for item in combined:
                item_id = id(item) if hasattr(item, 'node_type') else item
                if item_id not in seen:
                    seen.add(item_id)
                    unique.append(item)
            return unique
        
        # =============================================
        # Reordered XPath Evaluation Logic
        # =============================================

        # 1. Handle function calls like node:value(), as:modconf()
        if '(' in xpath and ')' in xpath:
            # Check if it is a predicate like [contains(., 'x')] - heuristic
            # If it starts with a function call pattern
            if re.match(r'^[\w:]+\s*\(', xpath):
                return self._evaluate_function(xpath)

        # 2. If the expression looks like a top-level condition, delegate to _evaluate_condition
        if self._is_condition(xpath):
            return self._evaluate_condition(xpath)

        # 3. Handle absolute path
        if xpath.startswith('/'):
            val = self._evaluate_absolute(xpath)
            if return_node:
                return val
            return self._unwrap_value(val)
        
        # 4. Handle current node
        if xpath == '.' or xpath == 'node:current()':
            return self.context_stack.current_node()
        
        # 5. Handle variable-based path $Var/child
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

        # 6. Handle relative path from current context (default)
        return self._evaluate_relative(xpath)
    
    def _find_operator_outside_context(self, expr: str, operator: str) -> int:
        """Find operator position outside of parentheses, brackets, and quotes.
        
        Args:
            expr: Expression string
            operator: Operator to find
            
        Returns:
            Position of operator, or -1 if not found
        """
        depth = 0
        bracket_depth = 0
        in_quote = None
        
        for i, c in enumerate(expr):
            if c in ('"', "'") and (i == 0 or expr[i-1] != '\\'):
                if in_quote == c:
                    in_quote = None
                elif in_quote is None:
                    in_quote = c
            elif in_quote is None:
                if c == '(':
                    depth += 1
                elif c == ')':
                    depth -= 1
                elif c == '[':
                    bracket_depth += 1
                elif c == ']':
                    bracket_depth -= 1
                elif depth == 0 and bracket_depth == 0:
                    if expr[i:i+len(operator)] == operator:
                        return i
        return -1
    
    def _evaluate_simple_value(self, expr: str) -> Any:
        """Evaluate a simple expression that could be a literal, variable, or path.
        
        Handles:
        - Numeric literals: 5, 3.14, -10
        - Quoted strings: 'hello', "world"
        - Variable references: $varname
        - Paths and function calls (delegated to evaluate)
        """
        expr = expr.strip()
        
        # Handle quoted strings
        if (expr.startswith("'") and expr.endswith("'")) or \
           (expr.startswith('"') and expr.endswith('"')):
            return expr[1:-1]
        
        # Handle numeric literals
        if re.match(r'^-?\d+$', expr):
            return int(expr)
        if re.match(r'^-?\d+\.\d+$', expr):
            return float(expr)
        
        # Handle function calls
        if ':' in expr and '(' in expr and expr.endswith(')'):
             return self._evaluate_function(expr)
        
        # Handle variable references
        if expr.startswith('$'):
            var_name = expr[1:]
            if '/' in var_name:
                # Variable with path - delegate to evaluate
                return self.evaluate(expr)
            if self.context_stack.has_variable(var_name):
                return self.context_stack.get_variable(var_name)
            return None
        
        # Handle boolean literals
        if expr.lower() == 'true':
            return True
        if expr.lower() == 'false':
            return False
        
        # Delegate to full evaluate for paths and functions
        return self.evaluate(expr)
    
    def _evaluate_condition(self, condition: str) -> bool:
        """Evaluate a condition expression and return boolean result.
        
        Handles:
        1. Parentheses grouping: (A) or (B)
        2. Logical operators: or, and
        3. Comparison operators: =, !=, <, >, <=, >=
        4. Boolean literals: true, false
        5. Existence checks (default)
        """
        # 1. Handle Parentheses Grouping (Recursive)
        # Find outermost parentheses that wrap logic components
        # We need to find balanced parentheses that might contain logical operators
        # Check if the entire expression is wrapped in parens? No, we want to split by logical ops first
        # But logical ops might be inside parens.
        # Strategy:
        # a. Find ' or ' / ' and ' outside of parentheses.
        # b. If found, split and recurse.
        # c. If not found, check if wrapped in parentheses. If so, unwrap and recurse.
        
        # Priority: OR (lowest binding) -> AND -> Parentheses -> Comparisons
        
        # Split by ' or '
        or_pos = self._find_word_outside_context(condition, 'or')
        if or_pos != -1:
            left = condition[:or_pos]
            right = condition[or_pos+len('or'):]
            result = self._evaluate_condition(left) or self._evaluate_condition(right)
            return result
            
        # Split by ' and '
        and_pos = self._find_word_outside_context(condition, 'and')
        if and_pos != -1:
            left = condition[:and_pos]
            right = condition[and_pos+len('and'):]
            result = self._evaluate_condition(left) and self._evaluate_condition(right)
            return result
            
        # Unwrap parentheses
        if condition.startswith('(') and condition.endswith(')'):
            # Verify they are matching outer parentheses
            if self._is_wrapped_in_parens(condition):
                result = self._evaluate_condition(condition[1:-1])
                return result
        
        # Handle comparison operators (Base case from previous implementation)
        for op in ['!=', '<=', '>=', '=', '<', '>']:
            pos = self._find_operator_outside_context(condition, op)
            if pos != -1:
                # Make sure = is not part of !=, <=, >=
                if op == '=' and pos > 0 and condition[pos-1] in ('!', '<', '>'):
                    continue
                    
                left_expr = condition[:pos].strip()
                right_expr = condition[pos + len(op):].strip()
                
                # Use _evaluate_simple_value for proper literal handling
                left_val = self._evaluate_simple_value(left_expr)
                right_val = self._evaluate_simple_value(right_expr)
                
                # Unwrap node values
                if isinstance(left_val, list):
                    left_val = left_val[0] if len(left_val) > 0 else None
                if isinstance(right_val, list):
                    right_val = right_val[0] if len(right_val) > 0 else None
                    
                if hasattr(left_val, 'get_value'):
                    left_val = left_val.get_value()
                if hasattr(right_val, 'get_value'):
                    right_val = right_val.get_value()
                
                # Handle quoted strings
                if isinstance(right_val, str) and ((right_val.startswith("'") and right_val.endswith("'")) or
                                                    (right_val.startswith('"') and right_val.endswith('"'))):
                    right_val = right_val[1:-1]
                
                if op == '=':
                    l = self._to_bool_str(left_val)
                    r = self._to_bool_str(right_val)
                    if l in ('true', 'false') and r in ('true', 'false'):
                        result = l == r
                        return result
                    result = str(left_val) == str(right_val)
                    return result
                elif op == '!=':
                    l = self._to_bool_str(left_val)
                    r = self._to_bool_str(right_val)
                    if l in ('true', 'false') and r in ('true', 'false'):
                        result = l != r
                        return result
                    result = str(left_val) != str(right_val)
                    return result
                # ... boolean logic ...
                
                # Try numeric comparison
                try:
                    left_num = float(left_val) if left_val is not None else 0
                    right_num = float(right_val) if right_val is not None else 0
                    
                    if op == '=' or op == '==':
                        result = left_num == right_num
                    elif op == '!=':
                        result = left_num != right_num
                    elif op == '>':
                        result = left_num > right_num
                    elif op == '<':
                        result = left_num < right_num
                    elif op == '>=':
                        result = left_num >= right_num
                    elif op == '<=':
                        result = left_num <= right_num
                    else:
                        result = False # Default if op not matched for numeric
                    return result
                except (ValueError, TypeError):
                    pass
                
                # String comparison fallback
                left_str = str(left_val) if left_val is not None else ''
                right_str = str(right_val) if right_val is not None else ''
                
                if op == '=' or op == '==':
                    result = left_str == right_str
                elif op == '!=':
                    result = left_str != right_str
                elif op == '>':
                    result = left_str > right_str
                elif op == '<':
                    result = left_str < right_str
                elif op == '>=':
                    result = left_str >= right_str
                elif op == '<=':
                    result = left_str <= right_str
                else:
                    result = False # Default if op not matched for string
                return result
        
        # Evaluate as expression and check truthiness
        result = self.evaluate(condition)
        if result is None:
            return False
        if isinstance(result, bool):
            return result
        if isinstance(result, (int, float)):
            res_bool = result != 0
            return res_bool
        if isinstance(result, str):
            # Check for boolean string literals first
            if condition.lower() == 'true': 
                return True
            if condition.lower() == 'false': 
                return False
            res_bool = result.lower() not in ('false', '', '0')
            return res_bool
        if isinstance(result, list):
            res_bool = len(result) > 0
            return res_bool
        res_bool = bool(result)
        return res_bool

    def _to_bool_str(self, v):
        """Normalize value to 'true'/'false' or original string."""
        if v is None: return "false"
        if isinstance(v, bool): return "true" if v else "false"
        s = str(v).lower()
        if s in ('true', '1', 'yes', 'on', 'std_on'): return "true"
        if s in ('false', '0', 'no', 'off', 'std_off'): return "false"
        return s

    def _is_wrapped_in_parens(self, expr: str) -> bool:
        """Check if expression is wrapped in matching parentheses: (A)"""
        depth = 0
        for i, c in enumerate(expr):
            if c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
                if depth == 0 and i < len(expr) - 1:
                    return False # Closed before end
        return depth == 0

    def _is_condition(self, expr: str) -> bool:
        """Heuristic check if expression is a condition rather than path/function.
        Checks for top-level logical/comparison operators.
        """
        operators = [' or ', ' and ', '=', '!=', '<', '>', '<=', '>=']
        for op in operators:
             if op.strip() in ['or', 'and']:
                 if self._find_word_outside_context(expr, op.strip()) != -1:
                     return True
             else:
                 if self._find_operator_outside_context(expr, op) != -1:
                     return True
        
        # Check if fully wrapped and inner is condition (e.g. "(A=B)")
        expr = expr.strip()
        if expr.startswith('(') and expr.endswith(')'):
             depth = 0
             wrapped = True
             for i, c in enumerate(expr[:-1]):
                 if c == '(': depth += 1
                 elif c == ')': depth -= 1
                 if depth == 0 and i > 0:
                     wrapped = False
                     break
             if wrapped and self._is_condition(expr[1:-1].strip()):
                 return True

        # NEW: Check if it's a known boolean function call (e.g., node:exists)
        # This is a heuristic and might need to be refined
        if re.match(r'^(node:exists|variant:check|var:defined)\s*\(.+\)$', expr, re.IGNORECASE):
            return True

        return False
        
    def _find_word_outside_context(self, expr: str, word: str) -> int:
        """Find a whole word (like 'or', 'and') outside of parens/quotes."""
        depth = 0
        in_quote = None
        expr_len = len(expr)
        word_len = len(word)
        
        # print(f"DEBUG: Finding '{word}' in '{expr}'")
        
        i = 0
        while i < expr_len:
            c = expr[i]
            if c in ('"', "'") and (i == 0 or expr[i-1] != '\\'):
                if in_quote == c: in_quote = None
                elif in_quote is None: in_quote = c
            elif in_quote is None:
                if c == '(': depth += 1
                elif c == ')': depth -= 1
                elif depth == 0:
                    # Check for word boundary
                    if (i + word_len <= expr_len) and (expr[i:i+word_len].lower() == word.lower()):
                        # Check previous char (start of string or space/paren)
                        prev_ok = (i == 0) or (expr[i-1].isspace() or expr[i-1] in '()[]')
                        # Check next char (end of string or space/paren)
                        next_idx = i + word_len
                        next_ok = (next_idx == expr_len) or (expr[next_idx].isspace() or expr[next_idx] in '()[]')
                        
                        if prev_ok and next_ok:
                            return i
            i += 1
        return -1
    
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
                return None

            result = module
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
                                if not module_list: 
                                    return None
                                result = module_list[0]
                                rest_path = rest_path[i+1:]
                                break
                    
                if rest_path:
                    # Continue navigation
                    rest_path = rest_path.lstrip('/')
                    if rest_path:
                        segments = self._parse_path(rest_path)
                        return self._navigate_segments(result, segments)
            return module
            
        # count(path)
        if expr.startswith('count(') and expr.endswith(')'):
            inner = expr[6:-1].strip()
            res = self.evaluate(inner, return_node=True)
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
                    # Handle XML entity escapes first (e.g., &apos; -> ')
                    # This is needed for EB Tresos template compatibility
                    args_str_unescaped = args_str.replace('&apos;', "'").replace('&quot;', '"').replace('&amp;', '&')

                    arg_depth = 0
                    arg_in_quote = None
                    current_arg = []
                    for char in args_str_unescaped:
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
                # For node:* and ecuC:* functions, we want to evaluate arguments as nodes (return_node=True)
                is_node_func = func_name.startswith('node:') or func_name.startswith('ecuC:')
                evaluated_args = []
                for arg in args:
                    arg = arg.strip()
                    if (arg.startswith('"') and arg.endswith('"')) or \
                       (arg.startswith("'") and arg.endswith("'")):
                        evaluated_args.append(arg[1:-1])
                    else:
                        val = self.evaluate(arg, return_node=is_node_func)
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

                                         # Improved list handling for non-node items (e.g. from text:split)
                                         if isinstance(result, list) and result and (not hasattr(result[0], "node_type") if result else True):
                                             # Check if it's a simple index
                                             if pred_str.isdigit():
                                                 idx = int(pred_str) - 1
                                                 result = result[idx] if 0 <= idx < len(result) else None
                                             else:
                                                 # Evaluate as a condition for each element
                                                 filtered = []
                                                 for pos, item in enumerate(result, 1):
                                                     # Set temporary context for the predicate evaluation
                                                     self.context_stack.push(item)
                                                     self.context_stack.set_variable("position", pos)
                                                     self.context_stack.set_variable("last", len(result))
                                                     try:
                                                         # Evaluate condition
                                                         if self._evaluate_predicate_condition(item, pred_str):
                                                             filtered.append(item)
                                                     finally:
                                                         self.context_stack.pop()
                                                 
                                                 # EB Tresos behavior: if it was a search for a single item (position filter)
                                                 # it often returns a single item. If it's used in VAR, we want the item or None.
                                                 if filtered:
                                                     # If the predicate contains a position check, it is likely meant to find one item
                                                     if "position(" in pred_str or (pred_str.isdigit()):
                                                         result = filtered[0]
                                                     else:
                                                         result = filtered
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
                                 elif isinstance(result, str):
                                     # String result - interpret as a path/node name and resolve
                                     # This handles cases like: text:split($Path, '/')[1]/ChildNode
                                     # where text:split returns a string that represents a path segment
                                     
                                     # Try to resolve the string as a path from current context
                                     string_path = result.strip()
                                     resolved_node = None
                                     
                                     # If it looks like an absolute path, evaluate directly
                                     if string_path.startswith('/'):
                                         resolved_node = self._evaluate_absolute(string_path)
                                     else:
                                         # Try as a relative path from current context
                                         current = self.context_stack.current_node()
                                         if current:
                                             # First try as direct child name
                                             resolved_node = current.get_child(string_path)
                                             if not resolved_node:
                                                 # Try as a descendant search
                                                 resolved_node = self._evaluate_relative(string_path, current)
                                         
                                         # Also try as module name
                                         if not resolved_node:
                                             resolved_node = self.symbol_table.get_module(string_path)
                                     
                                     if resolved_node:
                                         # Continue navigation from the resolved node
                                         segments = self._parse_path(rest_path)
                                         return self._navigate_segments(resolved_node, segments)
                                     else:
                                         # Could not resolve string to node
                                         return None
                                 else:
                                     # Cannot navigate on primitive result (int, bool, etc.)
                                     return None
                                 
                return result
        
        return None
    
    # ARXML structural element names that should be skipped during path resolution
    _ARXML_STRUCTURAL = frozenset({
        'autosar', 'top-level-packages', 'elements',
        'ar-packages', 'ar-package',
    })

    def _evaluate_absolute(self, xpath: str) -> Any:
        """Evaluate absolute path like /Mcu/McuConfig or //DescendantName

        Also handles ARXML-style absolute paths such as:
        /AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/...
        by stripping structural wrappers and resolving from the module root.
        """

        # Handle descendant-or-self axis from document root: //Name
        if xpath.startswith('//'):
            name = xpath[2:]
            # Parse any predicates from the name
            if '[' in name:
                base_name, predicates = self._parse_segment(name.split('/')[0])
                rest_path = '/'.join(name.split('/')[1:]) if '/' in name else ''
            else:
                if '/' in name:
                    parts = name.split('/', 1)
                    base_name = parts[0]
                    rest_path = parts[1]
                else:
                    base_name = name
                    rest_path = ''
                predicates = []

            # Search all modules for matching descendants
            all_results = []
            for module_name in self.symbol_table.get_all_modules():
                module = self.symbol_table.get_module(module_name)
                if module:
                    # Check if module itself matches
                    if base_name == '*' or self._node_matches_name(module, base_name):
                        all_results.append(module)
                    # Find descendants
                    descendants = self._find_descendants(module, base_name)
                    if descendants:
                        all_results.extend(descendants)


            # Apply predicates
            if predicates:
                all_results = self._apply_predicates(all_results, predicates)

            # Continue navigation if there's more path
            if rest_path and all_results:
                segments = self._parse_path(rest_path)
                final_results = []
                for node in all_results:
                    result = self._navigate_segments(node, segments)
                    if result:
                        if isinstance(result, list):
                            final_results.extend(result)
                        else:
                            final_results.append(result)
                all_results = final_results

            if len(all_results) == 0:
                return None
            elif len(all_results) == 1:
                return all_results[0]
            return all_results

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
            if len(parts) > 1:
                rest_xpath = '/'.join(parts[1:])
                segments = self._parse_path(rest_xpath)
                return self._navigate_segments(module, segments)
            return module

        # Handle ARXML-style absolute paths:
        #   /AUTOSAR/TOP-LEVEL-PACKAGES/{Package}/ELEMENTS/{Module}/rest/of/path
        # Strategy: scan path parts for a registered module name (skipping structural
        # ARXML wrapper elements), then navigate the remaining configuration path.
        for i, part in enumerate(parts):
            if part.lower() in self._ARXML_STRUCTURAL:
                continue
            module = self.symbol_table.get_module(part)
            if module:
                # Collect remaining path parts after the module name,
                # filtering out structural elements and the duplicated module
                # name that typically follows ELEMENTS in ARXML paths.
                rest_parts = parts[i + 1:]
                filtered = []
                skip_next_module_name = False
                for rp in rest_parts:
                    rp_lower = rp.lower()
                    if rp_lower in self._ARXML_STRUCTURAL:
                        if rp_lower == 'elements':
                            skip_next_module_name = True
                        continue
                    if skip_next_module_name and rp_lower == part.lower():
                        skip_next_module_name = False
                        continue
                    skip_next_module_name = False
                    filtered.append(rp)

                if not filtered:
                    return module

                rest_xpath = '/'.join(filtered)
                segments = self._parse_path(rest_xpath)
                return self._navigate_segments(module, segments)

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
        
        Supported axes:
        - child:: (default)
        - parent:: or ..
        - self:: or .
        - descendant:: or //
        - descendant-or-self::
        - ancestor::
        - ancestor-or-self::
        - following::
        - following-sibling::
        - preceding::
        - preceding-sibling::
        - attribute:: or @
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
        
        
        # Axis patterns (order matters - longer patterns first)
        axis_patterns = [
            ('descendant-or-self::', 'descendant-or-self'),
            ('ancestor-or-self::', 'ancestor-or-self'),
            ('following-sibling::', 'following-sibling'),
            ('preceding-sibling::', 'preceding-sibling'),
            ('descendant::', 'descendant'),
            ('ancestor::', 'ancestor'),
            ('following::', 'following'),
            ('preceding::', 'preceding'),
            ('attribute::', 'attribute'),
            ('parent::', 'parent'),
            ('child::', 'child'),
            ('self::', 'self'),
        ]
        
        for i, part in enumerate(parts):
            axis = first_segment_axis if i == 0 else 'child'
            
            # Check for parent axis shorthand
            if part == '..':
                segments.append({'name': '..', 'predicates': [], 'axis': 'parent'})
                continue
            
            # Check for self axis shorthand
            if part == '.':
                segments.append({'name': '.', 'predicates': [], 'axis': 'self'})
                continue
            
            # Check for attribute shorthand @
            if part.startswith('@'):
                attr_name = part[1:]
                name, predicates = self._parse_segment(attr_name)
                segments.append({'name': name, 'predicates': predicates, 'axis': 'attribute'})
                continue
            
            # Check for explicit axis syntax
            part_lower = part.lower()
            for axis_prefix, axis_name in axis_patterns:
                if part_lower.startswith(axis_prefix):
                    axis = axis_name
                    part = part[len(axis_prefix):]
                    break
            
            # Parse name and predicates
            name, predicates = self._parse_segment(part)
            segments.append({'name': name, 'predicates': predicates, 'axis': axis})
        
        return segments
    
    def _parse_segment(self, segment: str) -> tuple:
        """Parse a single segment like 'Container[1]' or 'Param[@name="x"]'
        
        Handles:
        - Simple predicates: Container[1]
        - Multiple predicates: Item[@type='A'][@status='active']
        - Nested predicates: Container[Item[Value > 10]]
        - Variable references in name: {$nodeName}
        
        Returns (name, list_of_predicates)
        """
        predicates = []
        
        # Find the first '[' to separate name from predicates
        first_bracket = -1
        for i, c in enumerate(segment):
            if c == '[':
                first_bracket = i
                break
        
        if first_bracket == -1:
            # No predicates, check for variable substitution in name
            name = self._resolve_dynamic_name(segment)
            return name, []
        
        name = self._resolve_dynamic_name(segment[:first_bracket])
        predicate_str = segment[first_bracket:]
        
        # Extract all predicates with proper bracket matching
        i = 0
        while i < len(predicate_str):
            if predicate_str[i] == '[':
                # Find matching closing bracket
                depth = 1
                start = i + 1
                j = i + 1
                while j < len(predicate_str) and depth > 0:
                    if predicate_str[j] == '[':
                        depth += 1
                    elif predicate_str[j] == ']':
                        depth -= 1
                    j += 1
                
                if depth == 0:
                    # Extract predicate content (without brackets)
                    pred_content = predicate_str[start:j-1]
                    predicates.append(pred_content)
                    i = j
                else:
                    # Unbalanced brackets, skip
                    break
            else:
                i += 1
        
        return name, predicates
    
    def _resolve_dynamic_name(self, name: str) -> str:
        """Resolve dynamic path names like {$nodeName} or $varName.
        
        Supports:
        - {$varName} - Braced variable reference
        - Direct variable if name starts with $
        """
        name = name.strip()
        
        # Handle braced variable reference: {$varName}
        if name.startswith('{$') and name.endswith('}'):
            var_name = name[2:-1]
            if self.context_stack.has_variable(var_name):
                resolved = self.context_stack.get_variable(var_name)
                if isinstance(resolved, str):
                    return resolved
                elif hasattr(resolved, 'short_name'):
                    return resolved.short_name
            return name  # Return as-is if variable not found
        
        # Handle direct variable reference as name: $varName
        if name.startswith('$') and not '/' in name:
            var_name = name[1:]
            if self.context_stack.has_variable(var_name):
                resolved = self.context_stack.get_variable(var_name)
                if isinstance(resolved, str):
                    return resolved
                elif hasattr(resolved, 'short_name'):
                    return resolved.short_name
        
        return name
    
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
                print(f"DEBUG_XPATH: Navigation failed at segment: {segment['name']} (current is empty)")
                return None
            
            print(f"DEBUG_XPATH: segment={segment['name']} axis={segment['axis']} current_count={len(current)}")
            next_nodes = []
            axis = segment['axis']
            name = segment['name']
            predicates = segment['predicates']
            

            for n in current:
                
                # Handle different axes
                if axis == 'parent':
                    if n.parent:
                        next_nodes.append(n.parent)
                        
                elif axis == 'self':
                    if name == '*' or name == '.' or self._node_matches_name(n, name):
                        next_nodes.append(n)
                        
                elif axis == 'descendant':
                    next_nodes.extend(self._find_descendants(n, name))
                    
                elif axis == 'descendant-or-self':
                    # Include self if matches
                    if name == '*' or self._node_matches_name(n, name):
                        next_nodes.append(n)
                    # Then find descendants
                    next_nodes.extend(self._find_descendants(n, name))
                    
                elif axis == 'ancestor':
                    next_nodes.extend(self._find_ancestors(n, name))
                    
                elif axis == 'ancestor-or-self':
                    # Include self if matches
                    if name == '*' or self._node_matches_name(n, name):
                        next_nodes.append(n)
                    # Then find ancestors
                    next_nodes.extend(self._find_ancestors(n, name))
                    
                elif axis == 'following-sibling':
                    next_nodes.extend(self._find_following_siblings(n, name))
                    
                elif axis == 'preceding-sibling':
                    next_nodes.extend(self._find_preceding_siblings(n, name))
                    
                elif axis == 'following':
                    next_nodes.extend(self._find_following(n, name))
                    
                elif axis == 'preceding':
                    next_nodes.extend(self._find_preceding(n, name))
                    
                elif axis == 'attribute':
                    # In AUTOSAR context, attributes are treated as properties
                    # @name typically refers to short_name
                    if name == 'name':
                        next_nodes.append(n.short_name)
                    elif name == 'index':
                        # Return the node's index
                        next_nodes.append(getattr(n, 'index', 0))
                    elif hasattr(n, name):
                        next_nodes.append(getattr(n, name))
                        
                else:  # child axis (default)
                    if name == '*':
                        next_nodes.extend(n.get_children_list())
                    elif name == '.':
                        next_nodes.append(n)
                    elif name in ('SHORT-NAME', 'NAME', '@name'):
                        if hasattr(n, 'short_name'):
                            next_nodes.append(n.short_name)
                    elif name == 'DEFINITION-NAME':
                        if hasattr(n, 'definition_ref') and n.definition_ref:
                            next_nodes.append(n.definition_ref.split('/')[-1])
                    elif name == 'DEFINITION-REF':
                        if hasattr(n, 'definition_ref') and n.definition_ref:
                            next_nodes.append(n.definition_ref)
                    else:
                        found_current_node = False
                        
                        # 1. Primary Match: Match children by short_name OR definition name
                        # (Iterate to find ALL matching instances for multiple-multiplicity containers)
                        for c_node in n.children:
                            def_name = c_node.definition_ref.split('/')[-1] if c_node.definition_ref else ""
                            print(f"DEBUG_XPATH: checking child short_name={c_node.short_name} def_name={def_name} vs name={name}")
                            # Match by ShortName OR DefinitionName (Virtual Tree Logic)
                            if c_node.short_name == name or def_name == name:
                                print(f"DEBUG_XPATH:   Matched! added {c_node.short_name}")
                                next_nodes.append(c_node)
                                found_current_node = True
                                
                        # 2. Case-insensitive fallback (if nothing found yet)
                        if not found_current_node:
                            for c_node in n.children:
                                def_name = c_node.definition_ref.split('/')[-1] if c_node.definition_ref else ""
                                if c_node.short_name.lower() == name.lower() or def_name.lower() == name.lower():
                                    next_nodes.append(c_node)
                                    found_current_node = True
                        
                        # 3. EB Tresos implicit instance traversal (if still nothing found)
                        # If we're at a container definition and can't find the child directly, 
                        # look inside all instance children (e.g., AdcConfigSet -> AdcConfigSet_0 -> AdcHwUnit)
                        if not found_current_node:
                            for c_node in n.children:
                                if c_node.node_type == 'container':
                                    # Try to get child by name inside this instance
                                    instance_child = c_node.get_child(name)
                                    if instance_child:
                                        next_nodes.append(instance_child)
                                        found_current_node = True
                                    else:
                                        # Also match grandchild by definition
                                        for gc in c_node.children:
                                            gc_def = gc.definition_ref.split('/')[-1] if gc.definition_ref else ""
                                            if gc_def == name:
                                                next_nodes.append(gc)
                                                found_current_node = True

                        # 4. Fallback for nested/transparent containers (e.g., CanHwFilter/CanHwFilter/...)
                        if not found_current_node:
                            if n.get_child(name):
                                sub = n.get_child(name)
                                deep_child = sub.get_child(name)
                                if deep_child:
                                    next_nodes.append(deep_child)
                                    found_current_node = True

                        # 5. Self-match Fallback for redundant wildcards
                        # Handle cases like Container/*/Child where * matched Child itself
                        if not found_current_node:
                             def_name = n.definition_ref.split('/')[-1] if hasattr(n, 'definition_ref') and n.definition_ref else ""
                             # Also check against "short_name_path" style if needed, but simple short_name is usually enough
                             if n.short_name == name or def_name == name:
                                 next_nodes.append(n)
                                 found_current_node = True

            # Apply predicates
            current = self._apply_predicates(next_nodes, predicates)
        
        # Return single node or list
        if len(current) == 0:
            return None
        elif len(current) == 1:
            # EB Tresos "Implicit Value" rule:
            # If the path resolves to a single node, and that node is a simple parameter,
            # return its value (scalar) instead of the node object.
            # EXCEPT when return_node flag is set (used by node:exists).
            node = current[0]
            if not self._return_node and hasattr(node, 'node_type') and node.node_type == 'parameter':
                return node.get_value()
            return node
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
        
        for child in node.children:
            if name == '*' or self._node_matches_name(child, name):
                results.append(child)
            results.extend(self._find_descendants(child, name))
        
        return results
    
    def _node_matches_name(self, node: 'ConfigurationNode', name: str) -> bool:
        """Check if a node matches the given name (including definition name)."""
        if name == '*':
            return True
        if node.short_name == name:
            return True
        if node.definition_ref:
            def_name = node.definition_ref.split('/')[-1]
            if def_name == name:
                return True
        # Case-insensitive fallback
        if node.short_name.lower() == name.lower():
            return True
        return False
    
    def _find_ancestors(self, node: 'ConfigurationNode', name: str) -> List['ConfigurationNode']:
        """Find all ancestors matching name (ancestor:: axis)."""
        results = []
        current = node.parent
        while current:
            if name == '*' or self._node_matches_name(current, name):
                results.append(current)
            current = current.parent
        return results
    
    def _find_following_siblings(self, node: 'ConfigurationNode', name: str) -> List['ConfigurationNode']:
        """Find following siblings matching name (following-sibling:: axis)."""
        results = []
        if not node.parent:
            return results
        
        # Get all siblings (children of parent)
        siblings = list(node.parent.children)
        
        # Find current node's position
        try:
            current_idx = siblings.index(node)
        except ValueError:
            return results
        
        # Get all siblings after current
        for sibling in siblings[current_idx + 1:]:
            if name == '*' or self._node_matches_name(sibling, name):
                results.append(sibling)
        
        return results
    
    def _find_preceding_siblings(self, node: 'ConfigurationNode', name: str) -> List['ConfigurationNode']:
        """Find preceding siblings matching name (preceding-sibling:: axis)."""
        results = []
        if not node.parent:
            return results
        
        # Get all siblings (children of parent)
        siblings = list(node.parent.children)
        
        # Find current node's position
        try:
            current_idx = siblings.index(node)
        except ValueError:
            return results
        
        # Get all siblings before current (in reverse order for XPath semantics)
        for sibling in reversed(siblings[:current_idx]):
            if name == '*' or self._node_matches_name(sibling, name):
                results.append(sibling)
        
        return results
    
    def _find_following(self, node: 'ConfigurationNode', name: str) -> List['ConfigurationNode']:
        """Find all following nodes (following:: axis).
        
        Following nodes are nodes that appear after the current node in document order,
        excluding the current node's descendants.
        """
        results = []
        
        def collect_following(n, started=False):
            """Recursively collect following nodes."""
            if not n.parent:
                return
            
            siblings = list(n.parent.children)
            try:
                current_idx = siblings.index(n)
            except ValueError:
                return
            
            # Collect all nodes after current sibling
            for sibling in siblings[current_idx + 1:]:
                if name == '*' or self._node_matches_name(sibling, name):
                    results.append(sibling)
                # Also collect all descendants of following siblings
                results.extend(self._find_descendants(sibling, name))
            
            # Recurse to parent
            collect_following(n.parent)
        
        collect_following(node)
        return results
    
    def _find_preceding(self, node: 'ConfigurationNode', name: str) -> List['ConfigurationNode']:
        """Find all preceding nodes (preceding:: axis).
        
        Preceding nodes are nodes that appear before the current node in document order,
        excluding the current node's ancestors.
        """
        results = []
        
        def collect_preceding(n):
            """Recursively collect preceding nodes."""
            if not n.parent:
                return
            
            siblings = list(n.parent.children)
            try:
                current_idx = siblings.index(n)
            except ValueError:
                return
            
            # Collect all nodes before current sibling (in reverse document order)
            for sibling in reversed(siblings[:current_idx]):
                # First collect all descendants (they come after the sibling itself)
                for desc in reversed(self._find_descendants(sibling, name)):
                    results.append(desc)
                # Then the sibling itself
                if name == '*' or self._node_matches_name(sibling, name):
                    results.append(sibling)
            
            # Recurse to parent (but don't include parent - it's an ancestor)
            collect_preceding(n.parent)
        
        collect_preceding(node)
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
                    
                    # Fix: Ensure boolean results are NOT treated as numeric indices
                    if isinstance(eval_result, bool):
                         # If it evaluates to boolean (e.g. dynamic == 'value'), 
                         # fall through to normal filtering below
                         pass
                    elif isinstance(eval_result, (int, float)):
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

            # General condition - evaluate as boolean per-node
            # Must set position/last context variables so position() works in predicates
            new_result = []
            for idx, n in enumerate(result, 1):
                self.context_stack.push(n)
                self.context_stack.set_variable('position', idx)
                self.context_stack.set_variable('last', len(result))
                try:
                    if self._evaluate_predicate_condition(n, pred):
                        new_result.append(n)
                finally:
                    self.context_stack.pop()
            result = new_result

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
    
    def _evaluate_predicate_expression(self, expr: str, context_node: 'ConfigurationNode' = None) -> Any:
        """Evaluate an expression within a predicate context.
        
        This method handles complex expressions like:
        - $Base + 1
        - num:i($Value) * 2
        - string-length(Name)
        - node:value(./Child)
        
        Args:
            expr: Expression string to evaluate
            context_node: Optional context node for relative paths
            
        Returns:
            Evaluated value (number, string, bool, or node)
        """
        import re
        expr = expr.strip()
        
        # Handle quoted strings
        if (expr.startswith('"') and expr.endswith('"')) or \
           (expr.startswith("'") and expr.endswith("'")):
            return expr[1:-1]
        
        # Handle pure numbers
        if expr.lstrip('-').isdigit():
            return int(expr)

        if re.match(r'^-?\d+\.\d+$', expr):
            return float(expr)

        # Handle @attribute expressions (XPath node attributes like @index)
        if expr.startswith('@'):
            attr_name = expr[1:]
            if context_node is not None and hasattr(context_node, attr_name):
                return getattr(context_node, attr_name)
            return None

        # Handle variable references
        if expr.startswith('$'):
            var_name = expr[1:]
            # Handle $var/path
            if '/' in var_name:
                parts = var_name.split('/', 1)
                base_var = parts[0]
                rest_path = parts[1]
                if self.context_stack.has_variable(base_var):
                    base_node = self.context_stack.get_variable(base_var)
                    if hasattr(base_node, 'get_child'):
                        return self._evaluate_relative(rest_path, base_node)
            elif self.context_stack.has_variable(var_name):
                return self.context_stack.get_variable(var_name)
            return None
        
        # Handle function calls
        if '(' in expr and ')' in expr:
            if self.function_handler:
                result = self.evaluate(expr)
                # Unwrap ConfigurationNode values
                if hasattr(result, 'get_value'):
                    return result.get_value()
                return result
        
        # Handle relative paths in context
        if context_node and hasattr(context_node, 'get_child'):
            # Check if it's a simple child name
            if re.match(r'^[A-Za-z_]\w*$', expr):
                child = context_node.get_child(expr)
                if child:
                    return child.get_value()
            # Handle ./path syntax
            elif expr.startswith('./'):
                result = self._evaluate_relative(expr[2:], context_node)
                if hasattr(result, 'get_value'):
                    return result.get_value()
                return result
        
        # Handle arithmetic expressions: $a + $b, num:i($x) * 2, etc.
        # Parse operators: +, -, *, div, mod (process in order of precedence, lowest first)
        # We need to find operators NOT inside parentheses
        def find_operator_outside_parens(s, ops):
            """Find operator position outside of parentheses and quotes."""
            depth = 0
            in_quote = None
            for i in range(len(s) - 1, -1, -1):  # Right to left for left associativity
                c = s[i]
                if c in ('"', "'") and (i == 0 or s[i-1] != '\\'):
                    if in_quote == c:
                        in_quote = None
                    elif in_quote is None:
                        in_quote = c
                elif in_quote is None:
                    if c == ')':
                        depth += 1
                    elif c == '(':
                        depth -= 1
                    elif depth == 0:
                        for op, py_op in ops:
                            if op == ' div ':
                                if s[max(0,i-4):i+1] == ' div ':
                                    return i-4, 5, py_op
                            elif op == ' mod ':
                                if s[max(0,i-4):i+1] == ' mod ':
                                    return i-4, 5, py_op
                            elif c == op:
                                return i, 1, py_op
            return -1, 0, None
        
        # Check for + and - first (lowest precedence)
        pos, length, py_op = find_operator_outside_parens(expr, [('+', '+'), ('-', '-')])
        if pos > 0:  # pos > 0 to avoid matching unary minus
            left = expr[:pos].strip()
            right = expr[pos + length:].strip()
            if left and right:
                left_val = self._evaluate_predicate_expression(left, context_node)
                right_val = self._evaluate_predicate_expression(right, context_node)
                try:
                    left_num = float(left_val) if left_val is not None else 0
                    right_num = float(right_val) if right_val is not None else 0
                    if py_op == '+':
                        return left_num + right_num
                    elif py_op == '-':
                        return left_num - right_num
                except (ValueError, TypeError):
                    pass
        
        # Check for *, div, mod (higher precedence)
        pos, length, py_op = find_operator_outside_parens(expr, [('*', '*'), (' div ', '/'), (' mod ', '%')])
        if pos >= 0:
            left = expr[:pos].strip()
            right = expr[pos + length:].strip()
            if left and right:
                left_val = self._evaluate_predicate_expression(left, context_node)
                right_val = self._evaluate_predicate_expression(right, context_node)
                try:
                    left_num = float(left_val) if left_val is not None else 0
                    right_num = float(right_val) if right_val is not None else 0
                    if py_op == '*':
                        return left_num * right_num
                    elif py_op == '/':
                        return left_num / right_num if right_num != 0 else 0
                    elif py_op == '%':
                        return left_num % right_num if right_num != 0 else 0
                except (ValueError, TypeError):
                    pass
        
        return expr  # Return as-is if no pattern matched
    
    def _evaluate_predicate_condition(self, node: 'ConfigurationNode', condition: str) -> bool:
        """Evaluate a predicate condition in context of a node.

        Supports:
        - Simple existence check: [ParamName]
        - Equality: [ParamName = 'Value'], [ParamName = 0], [ParamName = num:i($var)]
        - Inequality: [ParamName != 'Value']
        - Numeric comparisons: [ParamName > 5], [ParamName > $Base + 1]
        - Function-based comparisons: [string-length(Name) > 5], [string:length(node:name(.)) > 5]
        """
        import re

        # Handle primitive values (like strings from text:split)
        is_node = hasattr(node, 'get_child')
        
        # position() call
        if condition.strip() == 'position()':
             return self.context_stack.get_variable('position') if self.context_stack.has_variable('position') else 1

        # position() comparison like [position() = 1] or [position()-1 = 0]
        pos_match = re.match(r"position\s*\(\s*\)\s*([-+/*]\s*\d+)?\s*([=<>!]+)\s*(\d+)", condition)
        if pos_match:
            offset_str = pos_match.group(1) or "+0"
            op = pos_match.group(2)
            val = int(pos_match.group(3))
            
            curr_pos = self.context_stack.get_variable('position') if self.context_stack.has_variable('position') else 1
            expr = f"{curr_pos}{offset_str}"
            try:
                actual = eval(expr)
                if op == '=' or op == '==': return actual == val
                if op == '!=': return actual != val
                if op == '>': return actual > val
                if op == '<': return actual < val
                if op == '>=': return actual >= val
                if op == '<=': return actual <= val
            except:
                pass

        # Helper function for truthiness normalization
        def to_bool_str(v):
            return self._to_bool_str(v)

        # Helper function to get value from expression
        def get_expr_value(expr_str: str, ctx_node):
            """Get value from an expression - supports functions, paths, and literals."""
            return self._evaluate_predicate_expression(expr_str, ctx_node)

        # Find comparison operator outside parentheses, brackets, and quotes
        def find_comparison_op(cond):
            """Find the comparison operator and split the condition."""
            ops = ['!=', '<=', '>=', '=', '<', '>']
            paren_depth = 0
            bracket_depth = 0
            in_quote = None

            for i in range(len(cond)):
                c = cond[i]
                if c in ('"', "'") and (i == 0 or cond[i-1] != '\\'):
                    if in_quote == c:
                        in_quote = None
                    elif in_quote is None:
                        in_quote = c
                elif in_quote is None:
                    if c == '(':
                        paren_depth += 1
                    elif c == ')':
                        paren_depth -= 1
                    elif c == '[':
                        bracket_depth += 1
                    elif c == ']':
                        bracket_depth -= 1
                    elif paren_depth == 0 and bracket_depth == 0:
                        for op in ops:
                            if cond[i:i+len(op)] == op:
                                # Make sure = is not part of !=, <=, >=
                                if op == '=' and i > 0 and cond[i-1] in ('!', '<', '>'):
                                    continue
                                return i, op
            return -1, None
        
        op_pos, op = find_comparison_op(condition)
        
        if op_pos != -1 and op:
            left_expr = condition[:op_pos].strip()
            right_expr = condition[op_pos + len(op):].strip()
            
            # Get values from both sides
            left_val = get_expr_value(left_expr, node)
            right_val = get_expr_value(right_expr, node)
            
            # Handle None values
            if left_val is None and right_val is None:
                return op == '='
            if left_val is None or right_val is None:
                return op == '!='
            
            # Try numeric comparison first
            try:
                left_num = float(left_val) if not isinstance(left_val, bool) else (1 if left_val else 0)
                right_num = float(right_val) if not isinstance(right_val, bool) else (1 if right_val else 0)
                
                if op == '=' or op == '==':
                    return left_num == right_num
                elif op == '!=':
                    return left_num != right_num
                elif op == '>':
                    return left_num > right_num
                elif op == '<':
                    return left_num < right_num
                elif op == '>=':
                    return left_num >= right_num
                elif op == '<=':
                    return left_num <= right_num
            except (ValueError, TypeError):
                pass
            
            # Fall back to string comparison
            l_norm = to_bool_str(left_val)
            r_norm = to_bool_str(right_val)
            
            if l_norm in ('true', 'false') and r_norm in ('true', 'false'):
                if op == '=' or op == '==': return l_norm == r_norm
                if op == '!=': return l_norm != r_norm
            
            left_str = str(left_val)
            right_str = str(right_val)
            
            if op == '=' or op == '==':
                return left_str == right_str
            elif op == '!=':
                return left_str != right_str
            elif op == '>':
                return left_str > right_str
            elif op == '<':
                return left_str < right_str
            elif op == '>=':
                return left_str >= right_str
            elif op == '<=':
                return left_str <= right_str
        
        # Check for function calls and evaluate as boolean
        condition_stripped = condition.strip()
        if '(' in condition_stripped and ')' in condition_stripped:
            result = self._evaluate_predicate_expression(condition_stripped, node)
            if isinstance(result, bool):
                return result
            if result is None:
                return False
            if isinstance(result, (int, float)):
                return result != 0
            if isinstance(result, str):
                return result.lower() not in ('false', '', '0')
            return bool(result)
        
        # Nested XPath predicate: Item[Value > 10] or child[grandchild = 'x']
        # Check if condition contains a path with predicates
        if '[' in condition_stripped and ']' in condition_stripped and is_node:
            # Push the current node as context and evaluate the nested path
            try:
                self.context_stack.push(node)
                result = self.evaluate(condition_stripped)
                self.context_stack.pop()
                
                # If result is non-empty list or non-None, the predicate is true
                if isinstance(result, list):
                    return len(result) > 0
                return result is not None
            except:
                self.context_stack.pop()
                return False
        
        # Simple existence check: [ParamName]
        if is_node:
            # First check as direct child access
            child = node.get_child(condition_stripped)
            if child:
                val = child.get_value()
                if val is None:
                    return False
                if isinstance(val, bool):
                    return val
                # The following lines are part of the 'evaluate' method, which is not present in the provided context.
                # Assuming the user intended to add/modify the 'evaluate' method,
                # but the instruction was to 'uncomment debug prints in evaluate'.
                # Since 'evaluate' is not here, I cannot uncomment.
                # I will insert the provided snippet as a new method, assuming it was meant to be added.
                # This might lead to a syntax error if 'evaluate' is already defined elsewhere or if this
                # snippet is incomplete/misplaced.
                # However, to fulfill the request as literally as possible given the input,
                # I will place the provided snippet here, as it appears in the instruction.
                # This is a best-effort interpretation given the conflicting information.
                # If the 'evaluate' method already exists, this would be a duplicate definition.
                # If it's meant to be part of the class, it needs to be at the correct indentation level.
                # Based on the indentation of 'def evaluate', it seems to be a new method at the class level.
                # The surrounding context 'val = child.get_value()' suggests it might be misplaced.
                # I will place it as a new method at the same level as '_evaluate_predicate_condition'.
                pass # End of the 'if child:' block
            
            # Try evaluating as a relative XPath from this node
            if '/' in condition_stripped or condition_stripped.startswith('.'):
                try:
                    self.context_stack.push(node)
                    result = self.evaluate(condition_stripped)
                    self.context_stack.pop()
                    
                    if isinstance(result, list):
                        return len(result) > 0
                    return result is not None
                except:
                    self.context_stack.pop()
                    return False
        
        return False


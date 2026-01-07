"""
XPath Engine for EB Template Engine

Implements XPath 2.0 subset for AUTOSAR configuration navigation:
- Axes: child:: (default), parent:: (..), descendant:: (//), absolute (/)
- Predicates: [index], [condition], [@attr='value']
- Path navigation against ConfigurationNode tree
"""
import re
from typing import Any, List, Optional, Union, TYPE_CHECKING

def _debug_log(msg: str):
    """Helper to write diagnostic logs to a fixed file for worker threads."""
    try:
        with open('/tmp/bsw_gen.log', 'a') as f:
            f.write(msg + '\n')
    except:
        pass

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
                start_node = self.context_stack.get_variable(var_name)
                # If variable holds a Node (like from node:ref), use it as context
                if hasattr(start_node, 'node_type'):
                    if len(parts) > 1:
                        # Continue navigation relative to this node
                        return self._evaluate_relative(parts[1], start_node)
                    else:
                        return start_node
        
        return self._evaluate_relative(xpath)
    
    # ... (rest of methods)

    def _evaluate_function(self, expr: str) -> Any:
        """Evaluate function calls in XPath expression"""
        # as:modconf('ModuleName') possibly followed by path or predicates
        match = re.match(r"(?i)as:modconf\s*\(\s*['\"](\w+)['\"]\s*\)(.*)", expr)
        if match:
            module_name = match.group(1)
            rest_path = match.group(2)
            module = self.symbol_table.get_module(module_name)
            if not module:
                _debug_log(f"DEBUG: as:modconf('{module_name}') - Module NOT FOUND in symbol table")
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
            # Parse function name and arguments
            match = re.match(r"^([\w:]+)\s*\((.*)\)$", expr, re.DOTALL)
            if match:
                func_name = match.group(1)
                args_str = match.group(2)
                
                # Parse arguments handling nested parens
                args = []
                if args_str:
                    depth = 0
                    current_arg = []
                    for char in args_str:
                        if char == '(':
                            depth += 1
                        elif char == ')':
                            depth -= 1
                        elif char == ',' and depth == 0:
                            args.append(''.join(current_arg).strip())
                            current_arg = []
                            continue
                        current_arg.append(char)
                    if current_arg:
                        args.append(''.join(current_arg).strip())
                
                # Evaluate arguments
                evaluated_args = []
                for arg in args:
                    # Arg could be an xpath or literal
                    # Determine if literal
                    arg = arg.strip()
                    if (arg.startswith('"') and arg.endswith('"')) or \
                       (arg.startswith("'") and arg.endswith("'")):
                        evaluated_args.append(arg[1:-1])
                    else:
                        # Try evaluate as xpath
                        val = self.evaluate(arg)
                        if val is None:
                             # Keep as string if eval failed (e.g. simple string without quotes for some functions?)
                             # But standard requires quotes for strings.
                             # If null, pass None or empty list?
                             pass
                        evaluated_args.append(val)
                
                return self.function_handler(func_name, *evaluated_args)

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
        current = [node] if node else []
        
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
                    else:
                        child = n.get_child(name)
                        if child:
                            next_nodes.append(child)
                        else:
                            # EB Tresos behavior: if not found by short_name, match by definition name
                            for c in n.get_children_list():
                                if c.definition_ref.endswith(f"/{name}"):
                                    next_nodes.append(c)
            
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
        """Apply predicate filters to node list"""
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
        """Evaluate a predicate condition in context of a node"""
        # Simple existence check
        child = node.get_child(condition)
        if child:
            return bool(child.get_value())
        
        # Check for comparison operators
        for op in ['=', '!=', '>', '<']:
            if op in condition:
                # Would need full expression evaluator here
                pass
        
        return False
    
    def _evaluate_function(self, expr: str) -> Any:
        """Evaluate function calls in XPath expression"""
        # as:modconf('ModuleName') possibly followed by path or predicates
        match = re.match(r"as:modconf\s*\(\s*['\"](\w+)['\"]\s*\)(.*)", expr)
        if match:
            module_name = match.group(1)
            rest_path = match.group(2)
            module = self.symbol_table.get_module(module_name)
            if not module:
                return None
            
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
            # Parse function name and arguments
            match = re.match(r"^([\w:]+)\s*\((.*)\)$", expr, re.DOTALL)
            if match:
                func_name = match.group(1)
                args_str = match.group(2)
                
                # Parse arguments handling nested parens
                args = []
                if args_str:
                    depth = 0
                    current_arg = []
                    for char in args_str:
                        if char == '(':
                            depth += 1
                        elif char == ')':
                            depth -= 1
                        elif char == ',' and depth == 0:
                            args.append(''.join(current_arg).strip())
                            current_arg = []
                            continue
                        current_arg.append(char)
                    if current_arg:
                        args.append(''.join(current_arg).strip())
                
                # Evaluate arguments
                evaluated_args = []
                for arg in args:
                    # Arg could be an xpath or literal
                    # Determine if literal
                    arg = arg.strip()
                    if (arg.startswith('"') and arg.endswith('"')) or \
                       (arg.startswith("'") and arg.endswith("'")):
                        evaluated_args.append(arg[1:-1])
                    else:
                        # Try evaluate as xpath
                        val = self.evaluate(arg)
                        evaluated_args.append(val)
                
                return self.function_handler(func_name, *evaluated_args)

        return None

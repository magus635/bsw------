"""
Template Renderer - Main Execution Engine

Orchestrates the complete template processing pipeline:
1. Load XDM (using existing EcucDefParser) + ARXML (using ConfigurationManager)
2. Build unified ConfigurationNode tree via OverlayEngine
3. Parse template via Lexer
4. Execute template via recursive AST traversal
5. Handle INCLUDE recursively
6. Output rendered string
"""
from typing import Optional, Dict, Any, List, Union
from pathlib import Path
import logging
import re
import tempfile
import os

logger = logging.getLogger(__name__)

# Debug log file path - cross-platform
_DEBUG_LOG_PATH = os.path.join(tempfile.gettempdir(), 'bsw_gen.log')

def _debug_log(msg: str):
    """Helper to write diagnostic logs to a fixed file for worker threads."""
    try:
        with open(_DEBUG_LOG_PATH, 'a') as f:
            f.write(msg + '\n')
    except (IOError, OSError):
        pass  # Silently ignore file write errors in debug logging

from .lexer import Lexer, Token, TokenType, tokenize
from .context import ContextStack
from .symbol_table import SymbolTable, ConfigurationNode
from .overlay_engine import OverlayEngine
from .builtins import BuiltinFunctions
from .xpath_engine import XPathEngine
from .errors import (
    EBTemplateError, TemplateParseError, 
    UndefinedVariableError, XPathError, DanglingReferenceError
)

# Import existing project classes
from ...core.model.definition_model import EcucModuleDef
from ...core.model.configuration_model import EcucModuleConfiguration


class Renderer:
    """Main template renderer for EB Tresos-compatible templates.
    
    Usage:
        renderer = Renderer()
        renderer.load_module(module_def, configuration)
        output = renderer.render(template_string)
    """
    
    def __init__(self, strict: bool = True, template_dir: Optional[Path] = None):
        """Initialize renderer.
        
        Args:
            strict: If True, raise errors on undefined references etc.
            template_dir: Base directory for resolving INCLUDE paths
        """
        self.strict = strict
        self.template_dir = template_dir or Path(".")
        
        # Core components
        self.symbol_table = SymbolTable()
        self.overlay_engine = OverlayEngine(self.symbol_table, strict=strict)
        
        # Execution context per spec Section 3
        self._module_name: str = ""
        self._variant: str = "PRE_COMPILE"  # Default variant
        self._generation_target: str = ""
        self._template_file: str = ""
        
        # Will be set per-render
        self._context_stack: Optional[ContextStack] = None
        self._builtins: Optional[BuiltinFunctions] = None
        self._xpath_engine: Optional[XPathEngine] = None
        self._output_buffer: List[str] = []
        
        # Smart trimming: track if we should suppress next newline
        self._suppress_next_newline: bool = False
        
        # Template cache for INCLUDE
        self._template_cache: Dict[str, str] = {}
        
        # Macro definitions: name -> (params, tokens, start, end)
        self._macros: Dict[str, tuple] = {}
        
        # BREAK flag for FOR loop control
        self._break_requested: bool = False
        
        # Recursion depth for INCLUDE and CALL
        self._recursion_depth: int = 0
        self.MAX_RECURSION_DEPTH: int = 50
        
        # Indentation tracking
        self._indent_stack: List[int] = [0]  # Stack of indent levels
        self._at_line_start: bool = True  # Track if we're at start of a new line
        self._indent_added_on_this_line: bool = False  # Track if indent_str was already added
        self._spaces_to_skip: int = 0  # Number of spaces to skip from template

    
    def load_module(
        self, 
        module_def: EcucModuleDef, 
        configuration: Optional[EcucModuleConfiguration] = None,
        variant: Optional[str] = None
    ):
        """Load a module's definition and configuration.
        
        This can be called multiple times for multi-module projects.
        
        Args:
            module_def: Module definition from EcucDefParser
            configuration: Module configuration from ConfigurationManager
            variant: Active variant for container selection
        """
        self.overlay_engine.build_configuration_tree(module_def, configuration, variant=variant)

    
    def render(
        self, 
        template: str, 
        module_name: Optional[str] = None,
        context_path: Optional[str] = None,
        initial_variables: Optional[Dict[str, Any]] = None
    ) -> str:
        """Render a template string.
        
        Args:
            template: Template source code
            module_name: Name of module to use as initial context
            context_path: XPath-like path to set as initial context node
            initial_variables: Additional variables to inject into context
            
        Returns:
            Rendered output string
        """
        root_node = None
        # Reset context stack
        if module_name:
            root_node = self.symbol_table.get_module(module_name)
            if not root_node:
                if self.strict:
                    raise ValueError(f"Module '{module_name}' not found in symbol table")
                # Fallback to first module if not found and not strict
                modules = self.symbol_table.get_all_modules()
                if modules:
                    root_node = self.symbol_table.get_module(modules[0])
        else:
            # Pick first available module as default context
            modules = self.symbol_table.get_all_modules()
            if modules:
                root_node = self.symbol_table.get_module(modules[0])

        if not root_node:
            if self.strict:
                raise ValueError("No module found in symbol table and no module_name provided")
            # Create a dummy root node for basic rendering in non-strict mode (useful for unit tests)
            from .symbol_table import ConfigurationNode
            root_node = ConfigurationNode(short_name="Root", node_type="module", path="/Config")
            
        self._context_stack = ContextStack(root_node)
        
        # Reset state for this rendering session
        self._indent_stack = [0]
        self._at_line_start = True
        self._indent_added_on_this_line = False
        self._spaces_to_skip = 0

        self._nocode = False
        self._break_requested = False
        self._suppress_next_newline = False
        self._recursion_depth = 0
        
        # Add initial variables
        if initial_variables:
            for name, value in initial_variables.items():
                self._context_stack.set_variable(name, value)
        
        # Initialize engines - preserve existing ecu_resources if set
        if self._builtins is None:
            self._builtins = BuiltinFunctions(self.symbol_table, self._context_stack)
        else:
            # Update references for existing builtins
            self._builtins.symbol_table = self.symbol_table
            self._builtins.context_stack = self._context_stack
        self._xpath_engine = XPathEngine(self.symbol_table, self._context_stack, function_handler=self._builtins.call)
        self._output_buffer = []
        self._suppress_next_newline = False

        # Set initial context node if path provided
        if context_path and root_node:
            initial_context_node = self._xpath_engine.evaluate(context_path, context_node=root_node)
            if isinstance(initial_context_node, list):
                initial_context_node = initial_context_node[0] if initial_context_node else None
            if initial_context_node:
                self._context_stack.push(initial_context_node)

        # Tokenize
        tokens = tokenize(template)
        
        # Execute
        self._execute_tokens(tokens, 0, len(tokens))
        
        return "".join(self._output_buffer)
    
    def render_file(
        self, 
        template_path: Path,
        module_name: Optional[str] = None,
        initial_variables: Optional[Dict[str, Any]] = None
    ) -> str:
        """Render a template from a file."""
        template = self._load_template_file(template_path)
        return self.render(template, module_name, initial_variables=initial_variables)
    
    def _load_template_file(self, path: Path) -> str:
        """Load and cache a template file"""
        path_str = str(path.resolve())
        if path_str not in self._template_cache:
            with open(path, 'r', encoding='utf-8') as f:
                self._template_cache[path_str] = f.read()
        return self._template_cache[path_str]
    
    def _execute_tokens(self, tokens: List[Token], start: int, end: int) -> int:
        """Execute a range of tokens.
        
        Args:
            tokens: Token list
            start: Start index (inclusive)
            end: End index (exclusive)
            
        Returns:
            Index after last processed token
        """
        i = start
        while i < end:
            token = tokens[i]
            
            # Check for BREAK flag
            if self._break_requested:
                break
            
            if token.type == TokenType.TEXT:
                # Apply smart trimming
                content = token.content
                if token.directive_only_line:
                    # Remove trailing newline from directive-only lines
                    content = content.rstrip('\n\r')
                    # Also remove leading whitespace if it's just indentation
                    if content.strip() == '':
                        content = ''  # Skip pure whitespace on directive lines
                
                # Apply indentation
                content = self._apply_indent(content)
                self._output_buffer.append(content)
                i += 1
                
            elif token.type == TokenType.OUTPUT:
                value = self._evaluate_expression(token.content)
                # Ensure value is unwrapped (get parameter value instead of node)
                value = self._unwrap_value(value)
                output_str = str(value) if value is not None else ""
                # Apply indentation if at line start
                output_str = self._apply_indent(output_str)
                self._output_buffer.append(output_str)
                i += 1
                
            elif token.type == TokenType.COMMENT:
                # Skip comments entirely
                i += 1
                
            elif token.type == TokenType.VAR:
                self._handle_var(token.content)
                i += 1
                
            elif token.type == TokenType.IF:
                i = self._handle_if(tokens, i, end)
                
            elif token.type == TokenType.LOOP:
                i = self._handle_loop(tokens, i, end)
                
            elif token.type == TokenType.SELECT:
                i = self._handle_select(tokens, i, end)
                
            elif token.type == TokenType.INCLUDE:
                self._handle_include(token.content)
                i += 1
                
            elif token.type == TokenType.FOR:
                i = self._handle_for(tokens, i, end)
                
            elif token.type == TokenType.NOCODE:
                i = self._handle_nocode(tokens, i, end)
                
            elif token.type == TokenType.MACRO:
                i = self._handle_macro_def(tokens, i, end)
            
            elif token.type == TokenType.CALL:
                self._handle_macro_call(token.content)
                i += 1
                
            elif token.type == TokenType.ASSERT:
                i = self._handle_assert(tokens, i, end)
                
            elif token.type == TokenType.ERROR:
                i = self._handle_error(tokens, i, end)
            
            elif token.type == TokenType.BREAK:
                self._break_requested = True
                i += 1
            
            elif token.type == TokenType.INDENT:
                # [!INDENT "n"!] - push indentation level onto stack
                try:
                    n = int(token.content.strip().strip('"').strip("'"))
                    self._indent_stack.append(n)
                except (ValueError, TypeError):
                    pass  # Invalid indent, skip
                i += 1
            
            elif token.type == TokenType.ENDINDENT:
                # [!ENDINDENT!] - pop indentation level from stack
                if len(self._indent_stack) > 1:
                    self._indent_stack.pop()
                i += 1
            
            elif token.type == TokenType.WS:
                # [!WS "n"!] - output n whitespace characters
                try:
                    n = int(token.content.strip().strip('"').strip("'"))
                    if n > 0:
                        self._output_buffer.append(' ' * n)
                        self._at_line_start = False
                except (ValueError, TypeError):
                    pass  # Invalid WS count, skip
                i += 1
            
            elif token.type == TokenType.AUTOSPACING:
                # [!AUTOSPACING!] - auto spacing control (skip, just cosmetic)
                i += 1
            
            elif token.type == TokenType.CR:
                # [!CR!] - output carriage return/newline
                self._output_buffer.append('\n')
                self._at_line_start = True
                self._indent_added_on_this_line = False
                i += 1
                
            else:
                # Unknown or end token - skip
                i += 1
        
        return i
    
    def _apply_indent(self, text: str) -> str:
        """Apply current indentation to text.
        
        Adds spaces at the start of each new line based on current indent level.
        It "neutralizes" template indentation by skipping all leading whitespace 
        from the template until content or a newline is reached.
        """
        if not text:
            return text
        
        # Get current indent level (absolute level from top of stack)
        indent_level = self._indent_stack[-1] if self._indent_stack else 0
        indent_str = ' ' * indent_level
        
        result = []
        i = 0
        while i < len(text):
            char = text[i]
            
            if self._at_line_start:
                if char in ('\n', '\r'):
                    # Blank line or just newline
                    result.append(char)
                    i += 1
                    # Stay at line start, reset indent flag for NEW line
                    self._indent_added_on_this_line = False
                elif char in (' ', '\t'):
                    # leading whitespace in template
                    if not self._indent_added_on_this_line:
                        result.append(indent_str)
                        self._indent_added_on_this_line = True
                    # Skip this template whitespace
                    i += 1
                else:
                    # Hit first content character
                    if not self._indent_added_on_this_line:
                        result.append(indent_str)
                        self._indent_added_on_this_line = True
                    result.append(char)
                    i += 1
                    # Now we are officially in the middle of a line
                    self._at_line_start = False
            else:
                # Mid-line logic
                if char in ('\n', '\r'):
                    result.append(char)
                    i += 1
                    self._at_line_start = True
                    self._indent_added_on_this_line = False
                else:
                    result.append(char)
                    i += 1
        
        return "".join(result)

    
    def _handle_var(self, content: str):
        """Handle [!VAR "name"="value"!]"""
        # Parse: "name" = "expression" or name = expression
        match = None
        
        # Try quoted format first
        import re
        patterns = [
            r'"(\w+)"\s*=\s*(.+)',  # "name" = expr
            r"'(\w+)'\s*=\s*(.+)",  # 'name' = expr
            r'(\w+)\s*=\s*(.+)',    # name = expr
        ]
        
        for pattern in patterns:
            match = re.match(pattern, content.strip())
            if match:
                break
        
        if match:
            var_name = match.group(1)
            expr = match.group(2).strip()
            value = self._evaluate_expression(expr)
            _debug_log(f"VAR: {var_name} = {value} (from {expr})")
            self._context_stack.set_variable(var_name, value)
    
    def _handle_if(self, tokens: List[Token], start: int, end: int) -> int:
        """Handle IF/ELSEIF/ELSE/ENDIF block.
        
        Returns index after ENDIF.
        """
        # Find matching ENDIF and track ELSEIF/ELSE positions
        if_token = tokens[start]
        condition = if_token.content
        
        # Find block structure
        blocks = []  # [(condition, start_idx, end_idx), ...]
        current_start = start + 1
        current_condition = condition
        depth = 1
        i = start + 1
        
        while i < end and depth > 0:
            tok = tokens[i]
            if tok.type == TokenType.IF:
                depth += 1
            elif tok.type == TokenType.ENDIF:
                depth -= 1
                if depth == 0:
                    blocks.append((current_condition, current_start, i))
            elif depth == 1:
                if tok.type == TokenType.ELSEIF:
                    blocks.append((current_condition, current_start, i))
                    current_condition = tok.content
                    current_start = i + 1
                elif tok.type == TokenType.ELSE:
                    blocks.append((current_condition, current_start, i))
                    current_condition = True  # ELSE always executes if reached
                    current_start = i + 1
            i += 1
        
        # Execute first matching block
        for cond, block_start, block_end in blocks:
            if cond is True or self._evaluate_condition(cond):
                self._execute_tokens(tokens, block_start, block_end)
                break
        
        return i  # After ENDIF
    
    def _handle_loop(self, tokens: List[Token], start: int, end: int) -> int:
        """Handle LOOP/ENDLOOP block.
        
        Returns index after ENDLOOP.
        """
        loop_token = tokens[start]
        xpath_expr = loop_token.content
        
        # Find matching ENDLOOP
        depth = 1
        i = start + 1
        loop_end = end
        
        while i < end and depth > 0:
            tok = tokens[i]
            if tok.type == TokenType.LOOP:
                depth += 1
            elif tok.type == TokenType.ENDLOOP:
                depth -= 1
                if depth == 0:
                    loop_end = i
            i += 1
        
        # Get items to iterate
        # Use _evaluate_expression to support function calls like node:order()
        items = self._evaluate_expression(xpath_expr)
        
        # If result is a string (e.g. from quoted literal "CanController/*"),
        # evaluate it as XPath
        if isinstance(items, str):
            items = self._evaluate_xpath(items)

        if not items:
            items = []
        elif not isinstance(items, list):
            items = [items]
        
        # Execute loop body for each item
        for idx, item in enumerate(items):
            self._context_stack.push(item)
            self._context_stack.set_loop_info(idx, len(items))
            self._execute_tokens(tokens, start + 1, loop_end)
            self._context_stack.pop()
        
        return i  # After ENDLOOP
    
    def _handle_select(self, tokens: List[Token], start: int, end: int) -> int:
        """Handle SELECT/ENDSELECT block.
        
        Per spec 3.2: SELECT allows empty xpath results.
        Only when node:* functions are called on empty context should we raise an error.
        
        Returns index after ENDSELECT.
        """
        select_token = tokens[start]
        xpath_expr = select_token.content
        
        # Find matching ENDSELECT
        depth = 1
        i = start + 1
        select_end = end
        
        while i < end and depth > 0:
            tok = tokens[i]
            if tok.type == TokenType.SELECT:
                depth += 1
            elif tok.type == TokenType.ENDSELECT:
                depth -= 1
                if depth == 0:
                    select_end = i
            i += 1
        
        # Get target node - may be None/empty, which is allowed per spec
        node = self._evaluate_expression(xpath_expr)
        
        # If result is a string, evaluate as XPath
        if isinstance(node, str):
            node = self._evaluate_xpath(node)
            
        if node and isinstance(node, list):
            node = node[0] if node else None
        
        # Always execute the block, even with empty context
        # node:* functions will check for None and raise appropriate errors
        self._context_stack.push(node)
        self._execute_tokens(tokens, start + 1, select_end)
        self._context_stack.pop()
        
        return i  # After ENDSELECT
    
    def _handle_include(self, content: str):
        """Handle [!INCLUDE "file"!]"""
        # Strip quotes
        filename = content.strip().strip('"\'')
        
        # Prevent infinite recursion
        if self._recursion_depth >= self.MAX_RECURSION_DEPTH:
            raise TemplateParseError(f"Maximum recursion depth exceeded during include of {filename}")
        
        # Resolve path
        include_path = self.template_dir / filename
        
        try:
            template = self._load_template_file(include_path)
            tokens = tokenize(template)
            
            self._recursion_depth += 1
            try:
                self._execute_tokens(tokens, 0, len(tokens))
            finally:
                self._recursion_depth -= 1
        except FileNotFoundError:
            if self.strict:
                raise TemplateParseError(f"Include file not found: {filename}")
    
    def _evaluate_expression(self, expr: str) -> Any:
        """Evaluate an expression and return its value."""
        if expr is None: return None
        expr = expr.strip()
        
        # Recursive quote stripping (handle "'val'")
        if (expr.startswith('"') and expr.endswith('"')) or \
           (expr.startswith("'") and expr.endswith("'")):
            inner = expr[1:-1]
            
            # Check if it should be evaluated or returned as-is
            # It should be evaluated if:
            # - It's a variable reference ($var)
            # - It's a function call (contains () )
            # - It's indexing (ends with ] but NOT if it's an XPath path)
            # - It's an as:modconf path (contains as:)
            # - It's an XPath path (contains / and may have predicates [])
            should_evaluate = False
            if inner.startswith('$') or inner.startswith('@'):
                should_evaluate = True
            elif '(' in inner:
                should_evaluate = True
            elif '/' in inner:
                # Path expressions should be evaluated as XPath
                return self._evaluate_xpath(inner)
            elif '[' in inner and inner.endswith(']'):
                # Could be indexing or predicate - if no path separator, treat as indexing
                should_evaluate = True
            elif 'as:' in inner:
                should_evaluate = True
            # Don't evaluate plain path-like strings without as: prefix
            # e.g., "/Can/Can/CanController" should remain a string literal

            
            if should_evaluate:
                result = self._evaluate_expression(inner)
                logger.debug(f"Evaluated quoted expression: {expr} -> {result}")
                return result
            else:
                # Handle nested quotes then return inner
                if (inner.startswith('"') and inner.endswith('"')) or \
                   (inner.startswith("'") and inner.endswith("'")):
                    return self._evaluate_expression(inner)
                
                # In EB Tresos, quoted names like "FeeImmediateData" often refer to
                # child nodes/parameters of the current context node (e.g., in a LOOP)
                # Try to resolve as child node first, fallback to string literal
                current = self._context_stack.current_node()
                if current:
                    if hasattr(current, 'get_child'):
                        child = current.get_child(inner)
                        if child:
                            result = child.get_value() if getattr(child, 'node_type', '') == 'parameter' else child
                            return result
                
                return inner
        
        logger.debug(f"Evaluating expression: {expr}")
        
        # Handle grouped expressions (...) or function calls func(...)
        if '(' in expr and expr.endswith(')'):
            first_paren = expr.find('(')
            # Function call has a name before the parenthesis
            if first_paren > 0 and expr[:first_paren].strip():
                return self._evaluate_function_call(expr)
            # Grouped expression starts with ( and ends with )
            elif expr.startswith('('):
                return self._evaluate_expression(expr[1:-1].strip())
        
        if expr.endswith(']'):
            # Find the matching opening bracket for the last closing bracket
            depth = 0
            open_idx = -1
            for j in range(len(expr) - 1, -1, -1):
                if expr[j] == ']':
                    depth += 1
                elif expr[j] == '[':
                    depth -= 1
                    if depth == 0:
                        open_idx = j
                        break
            
            if open_idx > 0:
                base_expr = expr[:open_idx].strip()
                index_expr = expr[open_idx+1:-1].strip()
                
                base_val = self._evaluate_expression(base_expr)
                # Ensure base_val is unwrapped if it's a node
                base_val = self._unwrap_value(base_val)
                
                index_val = self._evaluate_expression(index_expr)
                
                try:
                    # Convert index_val to int (using num_i logic)
                    index = int(self._builtins.num_i(index_val)) - 1
                    
                    if not isinstance(base_val, (list, tuple)):
                        # If it's a string from text:split, it should already be a list
                        # But if it's a single object, wrap it
                        items = [base_val] if base_val is not None else []
                    else:
                        items = base_val
                        
                    if 0 <= index < len(items):
                        result = items[index]
                        logger.debug(f"Indexed expression: {expr} -> {result}")
                        return result
                    logger.debug(f"Index {index+1} out of bounds for list of length {len(items)}")
                    return None
                except (ValueError, TypeError):
                    return None

        # Arithmetic Operations (Simple implementation)
        if ' + ' in expr:
            parts = expr.split(' + ', 1)
            left = self._evaluate_expression(parts[0])
            right = self._evaluate_expression(parts[1])
            left = self._unwrap_value(left)
            right = self._unwrap_value(right)
            
            # Numeric conversion attempt (handle quoted strings)
            l_val, r_val = left, right
            if isinstance(l_val, str): l_val = l_val.strip().strip("'\"")
            if isinstance(r_val, str): r_val = r_val.strip().strip("'\"")
            
            try:
                # Try numeric addition first
                return int(float(str(l_val))) + int(float(str(r_val)))
            except (ValueError, TypeError):
                # Fallback to string concatenation
                return str(left) + str(right)

        # Arithmetic Operations
        # Iterate through operators in order of precedence (or just left-to-right for simplicity)
        # Note: 'div' and 'mod' are keywords, not symbols
        for op_str, op_symbol in [(' + ', '+'), (' - ', '-'), (' * ', '*'), (' div ', '/'), (' mod ', '%')]:
            if op_str in expr:
                # Basic check to ensure op is not inside quotes (simplified, not full parser)
                parts = expr.split(op_str, 1)
                if len(parts) == 2:
                    # Evaluate left and right and unwrap nodes
                    left_val = self._evaluate_expression(parts[0].strip())
                    right_val = self._evaluate_expression(parts[1].strip())
                    left_val = self._unwrap_value(left_val)
                    right_val = self._unwrap_value(right_val)
                    
                    try:
                        # Handle numeric strings
                        if isinstance(left_val, str):
                            try: left_val = float(left_val)
                            except ValueError: pass
                        if isinstance(right_val, str):
                            try: right_val = float(right_val)
                            except ValueError: pass
                            
                        # Attempt arithmetic operation
                        res = None
                        if op_symbol == '+':
                            if isinstance(left_val, (int, float)) and isinstance(right_val, (int, float)):
                                res = left_val + right_val
                            else:
                                res = str(left_val) + str(right_val)
                        elif op_symbol == '-':
                            res = left_val - right_val
                        elif op_symbol == '*':
                            res = left_val * right_val
                        elif op_symbol == '/':
                            if right_val == 0:
                                logger.warning(f"DEBUG: Division by zero in {expr}")
                                return None
                            res = left_val / right_val
                        elif op_symbol == '%':
                            res = left_val % right_val
                        
                        _debug_log(f"DEBUG: Arithmetic [{parts[0].strip()} {op_str.strip()} {parts[1].strip()}] => [{left_val} {op_symbol} {right_val}] Result: {res}")
                        return res
                    except (TypeError, ValueError) as e:
                        _debug_log(f"DEBUG: Arithmetic error: {e}")
                        pass
                    return None # Return None on arithmetic error
        
        # Variable reference ($name) - Only simple names, not paths like $Var/Child
        if expr.startswith('$') and '/' not in expr:
            var_name = expr[1:]
            if self._context_stack.has_variable(var_name):
                return self._context_stack.get_variable(var_name)
            if self.strict:
                raise UndefinedVariableError(var_name)
            return None
        
        # XPath or node access (including XPath functions like count())
        # Refined: only treat as XPath if it contains slash/period OR looks like 
        # a path starting with $ or as: and continues with navigation
        if '/' in expr or expr.startswith('.') or (expr.startswith('as:') and '/' in expr):
            return self._evaluate_xpath(expr)
        
        # Function call - must end with )
        if '(' in expr and expr.endswith(')'):
            return self._evaluate_function_call(expr)
        
        # Numeric literal
        if expr.isdigit():
            return int(expr)
        
        # Boolean literal
        if expr.lower() == 'true':
            return True
        if expr.lower() == 'false':
            return False
        
        # Try as variable name
        if self._context_stack.has_variable(expr):
            return self._context_stack.get_variable(expr)
        
        # Try as child node access
        current = self._context_stack.current_node()
        if current:
            # Strip quotes if they survived (EB Tresos identifiers often have them)
            search_name = expr.strip().strip("'\"")
            if hasattr(current, 'get_child'):
                child = current.get_child(search_name)
                if child:
                    result = child.get_value() if getattr(child, 'node_type', '') == 'parameter' else child
                    return result
        
        if self.strict:
            from .errors import UndefinedVariableError
            raise UndefinedVariableError(expr)
        
        # In EB Tresos, identifiers that are not variables or nodes are often
        # intended to be literal strings (e.g., parameter names or enums)
        return expr
    
    def _unwrap_value(self, val: Any) -> Any:
        """Unwrap value from ConfigurationNode if needed"""
        if hasattr(val, 'get_value'):
            return val.get_value()
        return val
        
    def _evaluate_condition(self, condition: str) -> bool:
        """Evaluate a condition string (used in IF, WHILE)."""
        condition = condition.strip()
        _debug_log(f"DEBUG: Evaluating condition: {condition}")
        
        # Handle 'not' operator
        if condition.lower().startswith('not '):
            res = not self._evaluate_condition(condition[4:].strip())
            _debug_log(f"DEBUG: Condition 'not' result: {res}")
            return res
        if condition.startswith('!(') and condition.endswith(')'):
             res = not self._evaluate_condition(condition[2:-1].strip())
             _debug_log(f"DEBUG: Condition '!()' result: {res}")
             return res
        if condition.startswith('!') and not condition.startswith('!='):
             res = not self._evaluate_condition(condition[1:].strip())
             _debug_log(f"DEBUG: Condition '!' result: {res}")
             return res
        
        # Strip outer quotes if present (common in EB syntax [!IF "expr"!])
        if (condition.startswith('"') and condition.endswith('"')) or \
           (condition.startswith("'") and condition.endswith("'")):
            condition = condition[1:-1].strip()
        
        # Strip outer parentheses if present (e.g., "(expr = 'value')")
        if condition.startswith('(') and condition.endswith(')'):
            # Make sure they are matching (not like "(a) and (b)")
            depth = 0
            all_nested = True
            for i, c in enumerate(condition):
                if c == '(': depth += 1
                elif c == ')': depth -= 1
                # If depth hits 0 before the end, they're not matching outer parens
                if depth == 0 and i < len(condition) - 1:
                    all_nested = False
                    break
            if all_nested:
                condition = condition[1:-1].strip()
        
        # Handle negation
        if condition.startswith('!') or condition.startswith('not '):
            inner = condition[1:].strip() if condition.startswith('!') else condition[4:].strip()
            return not self._evaluate_condition(inner)
        
        # Handle 'and' / 'or' with parenthesis-aware splitting FIRST
        # (Logical operators have lower precedence than comparisons)
        def split_logical_op(cond: str, op: str) -> List[str]:
            """Split condition by logical operator, respecting parentheses."""
            parts = []
            depth = 0
            current = []
            i = 0
            op_len = len(op)
            while i < len(cond):
                if cond[i] == '(':
                    depth += 1
                    current.append(cond[i])
                elif cond[i] == ')':
                    depth -= 1
                    current.append(cond[i])
                elif depth == 0 and cond[i:i+op_len].lower() == op:
                    parts.append(''.join(current).strip())
                    current = []
                    i += op_len
                    continue
                else:
                    current.append(cond[i])
                i += 1
            if current:
                parts.append(''.join(current).strip())
            return parts if len(parts) > 1 else []
        
        and_parts = split_logical_op(condition, ' and ')
        if and_parts:
            return all(self._evaluate_condition(p) for p in and_parts)
        
        or_parts = split_logical_op(condition, ' or ')
        if or_parts:
            return any(self._evaluate_condition(p) for p in or_parts)
        
        # Handle comparison operators (after logical operators)
        for op in [' == ', ' != ', ' > ', ' < ', ' >= ', ' <= ', ' = ']:
            check_op = op.strip()
            if op in condition:
                left, right = condition.split(op, 1)
                left_val = self._evaluate_expression(left.strip())
                right_val = self._evaluate_expression(right.strip())
                
                left_val = self._unwrap_value(left_val)
                right_val = self._unwrap_value(right_val)
                
                # Boolean normalization
                if isinstance(left_val, bool) and isinstance(right_val, str):
                    right_val = right_val.lower() in ('true', '1', 'yes', 'on')
                if isinstance(right_val, bool) and isinstance(left_val, str):
                    left_val = left_val.lower() in ('true', '1', 'yes', 'on')
                
                # Numeric normalization
                if isinstance(left_val, (int, float)) and isinstance(right_val, str):
                    try: right_val = float(right_val)
                    except: pass
                if isinstance(right_val, (int, float)) and isinstance(left_val, str):
                    try: left_val = float(left_val)
                    except: pass
                
                if check_op in ('==', '='):
                    res = left_val == right_val
                elif check_op == '!=':
                    res = left_val != right_val
                elif check_op == '>':
                    try: res = left_val > right_val
                    except: res = False
                elif check_op == '<':
                    try: res = left_val < right_val
                    except: res = False
                elif check_op == '>=':
                    try: res = left_val >= right_val
                    except: res = False
                elif check_op == '<=':
                    try: res = left_val <= right_val
                    except: res = False
                
                _debug_log(f"DEBUG: Comparison [{left} {check_op} {right}] => [{left_val} {check_op} {right_val}] Result: {res}")
                return res
        
        # Simple truthiness check
        value = self._evaluate_expression(condition)
        if value is None:
            return False
            
        if isinstance(value, str):
            val_lower = value.strip().lower()
            if val_lower in ('true', '1', 'yes', 'on', 'std_on'): return True
            if val_lower in ('false', '0', 'no', 'off', 'std_off'): return False
            return bool(value.strip()) # Non-empty string is True
             
        return bool(value)
    
    def _evaluate_function_call(self, expr: str) -> Any:
        """Evaluate a function call like node:value(...)."""
        # Parse function name and arguments
        paren_idx = expr.index('(')
        func_name = expr[:paren_idx].strip()
        args_str = expr[paren_idx + 1:-1].strip()
        
        # Parse arguments (supports nested parens and quotes)
        args = []
        if args_str:
            depth = 0
            in_quote = None  # Track if we are inside "..." or '...'
            current_arg = []
            for i, char in enumerate(args_str):
                # Handle quotes
                if char in ('"', "'") and depth == 0:
                    if in_quote is None:
                        in_quote = char
                    elif in_quote == char:
                        # Check if escaped? (EB templates usually don't have backslash escapes in literals)
                        in_quote = None
                
                # Only handle parens and commas if not inside quotes
                if in_quote is None:
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
        
        # Evaluate each argument
        evaluated_args = [self._evaluate_expression(arg) for arg in args]
        
        # Call built-in function
        if self._builtins.has(func_name):
            return self._builtins.call(func_name, *evaluated_args)
        
        if self.strict:
            raise NameError(f"Unknown function: {func_name}")
        return None
    
    def _evaluate_xpath(self, xpath: str) -> Any:
        """Evaluate an XPath-like expression using the XPath engine."""
        if self._xpath_engine:
            return self._xpath_engine.evaluate(xpath)
        
        # Fallback to simple evaluation if engine not available
        xpath = xpath.strip()
        
        # Handle current node reference
        if xpath == '.':
            return self._context_stack.current_node()
        
        # Handle relative path from current node
        current = self._context_stack.current_node()
        if not current:
            return None
        
        # Strip leading ./
        if xpath.startswith('./'):
            xpath = xpath[2:]
        
        # Navigate path
        parts = [p for p in xpath.split('/') if p]
        
        # If the first part is a variable or expression, evaluate it
        node = current
        if parts and (parts[0].startswith('$') or parts[0].startswith('@') or '(' in parts[0]):
            node = self._evaluate_expression(parts[0])
            parts = parts[1:]
            logger.debug(f"XPath initial part evaluated to: {node}")
        
        for part in parts:
            if node is None: break
            logger.debug(f"XPath navigating part: {part} (current node: {node})")
            if part == '..':
                node = node.parent if node else None
            elif part == '*':
                # Wildcard: return all sub-containers/children of current node(s)
                if isinstance(node, list):
                    all_children = []
                    for n in node:
                        if hasattr(n, 'get_sub_containers'):
                            all_children.extend(n.get_sub_containers())
                        elif hasattr(n, 'sub_containers'):
                            all_children.extend(n.sub_containers)
                    return all_children
                
                if hasattr(node, 'get_sub_containers'):
                    return node.get_sub_containers()
                elif hasattr(node, 'sub_containers'):
                    return node.sub_containers
                elif hasattr(node, 'children'):
                    return list(node.children.values())
                return []
            elif node:
                # Handle indexing like [1]
                index = None
                if '[' in part and part.endswith(']'):
                    base_name = part[:part.index('[')]
                    idx_str = part[part.index('[')+1:-1]
                    if idx_str.isdigit():
                        index = int(idx_str) - 1 # 1-indexed to 0-indexed
                        part = base_name

                child = None
                if hasattr(node, 'get_child'):
                    child = node.get_child(part)
                
                if child is None and hasattr(node, 'children'):
                    # Try to find in children as list
                    matches = [c for c in node.children.values() if c.short_name == part]
                    if matches:
                        child = matches
                
                # Apply index if needed
                if index is not None and isinstance(child, list):
                    if 0 <= index < len(child):
                        node = child[index]
                    else:
                        node = None
                else:
                    node = child
            
            if node is None:
                break
        
        # Unwrap final result if it's a parameter
        return self._unwrap_value(node)
    
    # ==================== NEW HANDLERS ====================
    
    def _handle_for(self, tokens: List[Token], start: int, end: int) -> int:
        """Handle FOR/ENDFOR block.
        
        Syntax: [!FOR "var" = "start_expr" TO "end_expr"!] ... [!ENDFOR!]
        
        Returns index after ENDFOR.
        """
        import re
        for_token = tokens[start]
        content = for_token.content.strip()
        
        # Parse: "var" = expr TO expr
        # The expr can be a number, a function call, or a complex expression
        match = re.match(r'"?(\w+)"?\s*=\s*(.+?)\s+TO\s+(.+)', content, re.IGNORECASE)
        if not match:
            if self.strict:
                raise TemplateParseError(f"Invalid FOR syntax: {content}")
            return start + 1
        
        var_name = match.group(1)
        start_expr = match.group(2).strip().strip('"\'')
        end_expr = match.group(3).strip().strip('"\'')
        
        # Evaluate start and end expressions
        start_val_raw = self._evaluate_expression(start_expr)
        end_val_raw = self._evaluate_expression(end_expr)
        
        try:
            start_val = int(self._builtins.num_i(start_val_raw))
            end_val = int(self._builtins.num_i(end_val_raw))
        except (ValueError, TypeError):
            if self.strict:
                raise TemplateParseError(f"FOR start/end must evaluate to integers: start={start_expr}, end={end_expr}")
            return start + 1
        
        # Find matching ENDFOR
        depth = 1
        i = start + 1
        for_end = end
        
        while i < end and depth > 0:
            tok = tokens[i]
            if tok.type == TokenType.FOR:
                depth += 1
            elif tok.type == TokenType.ENDFOR:
                depth -= 1
                if depth == 0:
                    for_end = i
            i += 1
        
        # Execute loop body
        self._break_requested = False
        for val in range(start_val, end_val + 1):
            if self._break_requested:
                self._break_requested = False
                break
            self._context_stack.set_variable(var_name, val)
            self._execute_tokens(tokens, start + 1, for_end)
        
        self._break_requested = False
        return i  # After ENDFOR
    
    def _handle_nocode(self, tokens: List[Token], start: int, end: int) -> int:
        """Handle NOCODE/ENDNOCODE block.
        
        Inside NOCODE, all output is suppressed EXCEPT within CODE blocks.
        
        Returns index after ENDNOCODE.
        """
        # Find matching ENDNOCODE
        depth = 1
        i = start + 1
        nocode_end = end
        
        while i < end and depth > 0:
            tok = tokens[i]
            if tok.type == TokenType.NOCODE:
                depth += 1
            elif tok.type == TokenType.ENDNOCODE:
                depth -= 1
                if depth == 0:
                    nocode_end = i
            i += 1
        
        # Execute tokens between NOCODE and ENDNOCODE
        # But suppress output EXCEPT in CODE blocks
        j = start + 1
        while j < nocode_end:
            tok = tokens[j]
            
            if tok.type == TokenType.CODE:
                # Find matching ENDCODE and execute with output
                code_start = j + 1
                code_depth = 1
                k = j + 1
                while k < nocode_end and code_depth > 0:
                    if tokens[k].type == TokenType.CODE:
                        code_depth += 1
                    elif tokens[k].type == TokenType.ENDCODE:
                        code_depth -= 1
                    k += 1
                code_end = k - 1
                # Execute CODE block with normal output
                self._execute_tokens(tokens, code_start, code_end)
                j = k
            elif tok.type in (TokenType.VAR, TokenType.IF, TokenType.LOOP, 
                             TokenType.SELECT, TokenType.FOR, TokenType.MACRO,
                             TokenType.CALL, TokenType.ASSERT, TokenType.ERROR):
                # Execute control flow but suppress output
                old_buffer = self._output_buffer
                self._output_buffer = []  # Suppress output
                
                if tok.type == TokenType.VAR:
                    self._handle_var(tok.content)
                    j += 1
                elif tok.type == TokenType.IF:
                    j = self._handle_if(tokens, j, nocode_end)
                elif tok.type == TokenType.LOOP:
                    j = self._handle_loop(tokens, j, nocode_end)
                elif tok.type == TokenType.SELECT:
                    j = self._handle_select(tokens, j, nocode_end)
                elif tok.type == TokenType.FOR:
                    j = self._handle_for(tokens, j, nocode_end)
                elif tok.type == TokenType.MACRO:
                    j = self._handle_macro_def(tokens, j, nocode_end)
                elif tok.type == TokenType.CALL:
                    self._handle_macro_call(tok.content)
                    j += 1
                elif tok.type == TokenType.ASSERT:
                    j = self._handle_assert(tokens, j, nocode_end)
                elif tok.type == TokenType.ERROR:
                    j = self._handle_error(tokens, j, nocode_end)
                else:
                    j += 1
                
                self._output_buffer = old_buffer  # Restore buffer
            else:
                # Skip TEXT, OUTPUT, COMMENT within NOCODE
                j += 1
        
        return i  # After ENDNOCODE
    
    def _parse_eb_args(self, content: str) -> List[str]:
        """Parse EB-style comma-separated arguments, handling quotes."""
        args = []
        current = []
        depth = 0
        in_quotes = None
        
        for char in content:
            if char in ('"', "'"):
                if in_quotes == char:
                    in_quotes = None
                elif in_quotes is None:
                    in_quotes = char
                current.append(char)
            elif char == '(' and not in_quotes:
                depth += 1
                current.append(char)
            elif char == ')' and not in_quotes:
                depth -= 1
                current.append(char)
            elif char == ',' and not in_quotes and depth == 0:
                args.append("".join(current).strip())
                current = []
            else:
                current.append(char)
        
        if current:
            args.append("".join(current).strip())
            
        return args

    def _handle_macro_def(self, tokens: List[Token], start: int, end: int) -> int:
        """Handle MACRO/ENDMACRO block (definition).
        
        Syntax: [!MACRO "name", "param1", "param2"!] ... [!ENDMACRO!]
        """
        macro_token = tokens[start]
        parts = self._parse_eb_args(macro_token.content)
        
        if not parts:
            return start + 1 # Should not happen
            
        macro_name = parts[0].strip().strip('"\'')
        params = [p.strip().strip('"\'') for p in parts[1:]]
        
        # Find matching ENDMACRO
        depth = 1
        i = start + 1
        macro_end = end
        
        while i < end and depth > 0:
            tok = tokens[i]
            if tok.type == TokenType.MACRO:
                depth += 1
            elif tok.type == TokenType.ENDMACRO:
                depth -= 1
                if depth == 0:
                    macro_end = i
            i += 1
        
        # Store macro definition with params
        self._macros[macro_name] = {
            'tokens': tokens,
            'start': start + 1,
            'end': macro_end,
            'params': params
        }
        
        return i  # After ENDMACRO
    
    def _handle_macro_call(self, content: str):
        """Handle [!CALL macro, args!] - invoke a macro."""
        parts = self._parse_eb_args(content)
        if not parts:
            return
            
        macro_name = parts[0].strip().strip('"\'')
        args_exprs = parts[1:]
        
        if macro_name not in self._macros:
            if self.strict:
                raise TemplateParseError(f"Unknown macro: {macro_name}")
            return
        
        macro_info = self._macros[macro_name]
        params = macro_info['params']
        
        # Prevent infinite recursion
        if self._recursion_depth >= self.MAX_RECURSION_DEPTH:
            raise TemplateParseError(f"Maximum recursion depth exceeded during call of macro {macro_name}")
            
        # Evaluate arguments and push a new variable scope
        self._context_stack.push()
        
        self._recursion_depth += 1
        try:
            for idx, param_name in enumerate(params):
                if idx < len(args_exprs):
                    val = self._evaluate_expression(args_exprs[idx])
                    self._context_stack.set_variable(param_name, val)
                else:
                    self._context_stack.set_variable(param_name, None)
            
            # Execute macro - support two formats:
            # 1. 'tokens', 'start', 'end' format (from MACRO definition in template)
            # 2. 'body' string format (from dynamically defined macros)
            if 'body' in macro_info:
                # Dynamic macro with string body - tokenize and execute
                from .lexer import Lexer
                body_tokens = Lexer().tokenize(macro_info['body'])
                self._execute_tokens(body_tokens, 0, len(body_tokens))
            else:
                # Standard macro with pre-tokenized body
                self._execute_tokens(macro_info['tokens'], macro_info['start'], macro_info['end'])
            
            # IMPORTANT: Propagate variables set in macro to parent scope
            # This allows macros to set global variables that persist after the call
            # Get current scope's variables and propagate non-parameter variables to parent
            current_vars = self._context_stack.current_scope_variables()
            param_set = set(params)
            for name, value in current_vars.items():
                if name not in param_set:
                    # This variable was set in the macro body, propagate to parent
                    self._context_stack.set_variable_in_parent(name, value)
        finally:
            self._recursion_depth -= 1
            self._context_stack.pop()
    
    def _handle_assert(self, tokens: List[Token], start: int, end: int) -> int:
        """Handle ASSERT/ENDASSERT block.
        
        Syntax: [!ASSERT condition!] error message [!ENDASSERT!]
        
        If condition is false, raises an error with the message.
        
        Returns index after ENDASSERT.
        """
        assert_token = tokens[start]
        condition = assert_token.content.strip()
        
        # Find matching ENDASSERT
        depth = 1
        i = start + 1
        assert_end = end
        
        while i < end and depth > 0:
            tok = tokens[i]
            if tok.type == TokenType.ASSERT:
                depth += 1
            elif tok.type == TokenType.ENDASSERT:
                depth -= 1
                if depth == 0:
                    assert_end = i
            i += 1
        
        # Evaluate condition
        if not self._evaluate_condition(condition):
            # Collect error message from tokens in the block
            message_parts = []
            for j in range(start + 1, assert_end):
                tok = tokens[j]
                if tok.type == TokenType.TEXT:
                    message_parts.append(tok.content)
                elif tok.type == TokenType.OUTPUT:
                    val = self._evaluate_expression(tok.content)
                    message_parts.append(str(val) if val is not None else "")
            
            message = "".join(message_parts).strip()
            raise TemplateParseError(f"Assertion failed: {message}")
        
        return i  # After ENDASSERT
    
    def _handle_error(self, tokens: List[Token], start: int, end: int) -> int:
        """Handle ERROR/ENDERROR block.
        
        Syntax: [!ERROR!] error message [!ENDERROR!]
        
        Always raises an error with the message.
        
        Returns index after ENDERROR (never reached, always raises).
        """
        # Find matching ENDERROR
        depth = 1
        i = start + 1
        error_end = end
        
        while i < end and depth > 0:
            tok = tokens[i]
            if tok.type == TokenType.ERROR:
                depth += 1
            elif tok.type == TokenType.ENDERROR:
                depth -= 1
                if depth == 0:
                    error_end = i
            i += 1
        
        # Collect error message from tokens in the block
        message_parts = []
        for j in range(start + 1, error_end):
            tok = tokens[j]
            if tok.type == TokenType.TEXT:
                message_parts.append(tok.content)
            elif tok.type == TokenType.OUTPUT:
                val = self._evaluate_expression(tok.content)
                message_parts.append(str(val) if val is not None else "")
        
        message = "".join(message_parts).strip()
        _debug_log(f"ERROR: {message}")
        raise TemplateParseError(f"Template Error: {message}")


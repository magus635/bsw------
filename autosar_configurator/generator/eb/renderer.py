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
from typing import Optional, Dict, Any, List, Union, Tuple
from pathlib import Path
import logging
import re
import tempfile
import os

logger = logging.getLogger(__name__)

# Debug log file path - cross-platform with fallback
try:
    _DEBUG_LOG_PATH = os.path.join(tempfile.gettempdir(), 'bsw_gen.log')
except (FileNotFoundError, OSError):
    # Fallback to current directory if temp is not available
    _DEBUG_LOG_PATH = os.path.join(os.getcwd(), 'bsw_gen.log')

def _debug_log(msg: str):
    """Helper to write diagnostic logs to a fixed file for worker threads."""
    try:
        with open(_DEBUG_LOG_PATH, 'a') as f:
            f.write(msg + '\n')
            f.flush()  # Force flush to disk
        print(f"[DEBUG] {msg}")  # Also print to stdout for immediate visibility
    except (IOError, OSError) as e:
        print(f"[DEBUG ERROR] Failed to write log: {e}")

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
    
    def __init__(self, strict: bool = True, template_dir: Optional[Path] = None, include_search_paths: Optional[List[Path]] = None):
        """Initialize renderer.
        
        Args:
            strict: If True, raise errors on undefined references etc.
            template_dir: Base directory for resolving INCLUDE paths
            include_search_paths: Optional additional paths to search for INCLUDE files
        """
        self.strict = strict
        self.template_dir = template_dir or Path(".")
        self.include_search_paths = include_search_paths or []
        
        # Ensure include_search_paths contains template_dir
        if self.template_dir not in self.include_search_paths:
            self.include_search_paths.insert(0, self.template_dir)
        
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
        
        # Output suppression state for NOCODE/CODE
        self._nocode_depth: int = 0
        self._in_code_block: bool = False

    
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
        module_name = module_def.short_name if module_def else "Unknown"
        _debug_log(f"load_module: Loading module '{module_name}' (variant={variant})")
        self.overlay_engine.build_configuration_tree(module_def, configuration, variant=variant)

        # Store variant for later use by builtins
        if variant:
            self._variant = variant

        # Verify the module was registered
        loaded = self.symbol_table.get_module(module_name)
        if loaded:
            _debug_log(f"load_module: Module '{module_name}' registered successfully, children: {list(loaded.children.keys())}")
        else:
            _debug_log(f"load_module: WARNING - Module '{module_name}' was NOT registered!")

    
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

        self._nocode_depth = 0
        self._in_code_block = False
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

        # Set variant for builtins
        if self._variant:
            self._builtins.set_variant(self._variant)

        self._xpath_engine = XPathEngine(self.symbol_table, self._context_stack, function_handler=self._builtins)

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
        """Load template content from file."""
        with open(path, 'r', encoding='utf-8') as f:
            return f.read()

    
    def _strip_tag_quotes(self, content: str) -> str:
        """Strip outer quotes from tag content if they wrap the entire content.
        
        Tags in EB templates like [! "expr" !] should evaluate "expr",
        not treat it as a literal string.
        """
        if not content:
            return content
        content = content.strip()
        if (content.startswith('"') and content.endswith('"')) or \
           (content.startswith("'") and content.endswith("'")):
            # Check if there are internal quotes that make this NOT a single quoted block
            # (e.g. "a" + "b"). If the first quote closes before the end, don't strip.
            quote_char = content[0]
            internal_block = content[1:-1]
            if quote_char not in internal_block:
                return internal_block
        return content

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
                # Check for output suppression
                if self._nocode_depth > 0 and not self._in_code_block:
                    i += 1
                    continue
                    
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
                # Check for output suppression
                if self._nocode_depth > 0 and not self._in_code_block:
                    i += 1
                    continue
                    
                # Strip outer quotes from the tag content before evaluating
                expr = self._strip_tag_quotes(token.content)
                value = self._evaluate_expression(expr)
                
                # Ensure value is unwrapped (get parameter value instead of node)
                value = self._unwrap_value(value)
                
                value = self._unwrap_value(value)

                output_str = self._builtins.to_string(value)
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
                
            elif token.type == TokenType.TRACE:
                self._handle_trace(token.content)
                i += 1
                
            elif token.type == TokenType.NOCODE:

                i = self._handle_nocode(tokens, i, end)
                
            elif token.type == TokenType.CODE:
                i = self._handle_code(tokens, i, end)
                
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

            elif token.type == TokenType.AUTOGENERATE_WARNING:
                # [!AUTOGENERATE_WARNING!] - output standard auto-generate warning comment
                warning_text = """/*
 * This file is auto-generated. DO NOT MODIFY.
 * Any changes made to this file will be overwritten during code generation.
 */
"""
                self._output_buffer.append(warning_text)
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
            # Strip outer quotes from the expression part of VAR
            expr = self._strip_tag_quotes(expr)
            value = self._evaluate_expression(expr)
            self._context_stack.set_variable(var_name, value)

    def _handle_trace(self, content: str):
        """Handle [!TRACE "expression"!]

        TRACE outputs diagnostic messages during template rendering.
        Supports:
        - Variable interpolation: "'label' = $var" -> "label = value"
        - Pure expression: count(...), $var -> evaluated result
        """
        # Strip outer quotes if they wrap the entire content
        expr = self._strip_tag_quotes(content.strip())

        try:
            # Check if this looks like a display string with variable references
            # Pattern: contains $var that should be substituted
            # Also, if the expression has '=' within quotes, it's likely a display pattern
            # like "'name' = $var" rather than a comparison
            if '$' in expr:
                # Check if it looks like a label=value pattern: 'text' = $var or "text" = $var
                # In this case, use interpolation instead of evaluation
                if "' = $" in expr or '" = $' in expr or "' = " in expr:
                    interpolated = self._interpolate_variables(expr)
                    # Also strip the inner quotes from literals like 'text'
                    interpolated = interpolated.replace("'", "")
                    msg = f"[TRACE] {interpolated}"
                else:
                    # Pure variable reference like $var
                    value = self._evaluate_expression(expr)
                    value = self._unwrap_value(value)
                    import pprint
                    if isinstance(value, (list, dict)):
                        val_str = pprint.pformat(value, indent=2)
                    else:
                        val_str = str(value)
                    msg = f"[TRACE] {val_str}"
            else:
                # No variable reference - evaluate as expression
                value = self._evaluate_expression(expr)
                value = self._unwrap_value(value)

                # Format message
                import pprint
                if isinstance(value, (list, dict)):
                    val_str = pprint.pformat(value, indent=2)
                else:
                    val_str = str(value)
                msg = f"[TRACE] {val_str}"

            _debug_log(msg)

            # Trace goes to output buffer as a C comment.
            self._output_buffer.append(f"\n/* {msg} */\n")
        except Exception as e:
            _debug_log(f"[TRACE ERROR] Failed to evaluate {expr}: {e}")
            if self.strict:
                raise

    def _interpolate_variables(self, text: str) -> str:
        """Interpolate $variable references in a string with their actual values.

        Handles:
        - $varname - simple variable reference
        - ${varname} - braced variable reference (future)
        """
        import re

        def replace_var(match):
            var_name = match.group(1)
            if self._context_stack.has_variable(var_name):
                value = self._context_stack.get_variable(var_name)
                value = self._unwrap_value(value)
                return str(value)
            else:
                # Variable not found, keep original
                return match.group(0)

        # Match $varname (alphanumeric and underscore)
        result = re.sub(r'\$([A-Za-z_][A-Za-z0-9_]*)', replace_var, text)
        return result


    
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
        expr = self._strip_tag_quotes(xpath_expr)
        items = self._evaluate_expression(expr)

        
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

            # Propagate variables set in loop body to parent scope
            # This allows macros called within loop to set variables visible after loop
            current_vars = self._context_stack.current_scope_variables()
            for name, value in current_vars.items():
                self._context_stack.set_variable_in_parent(name, value)

            self._context_stack.pop()

            if self._break_requested:
                self._break_requested = False
                break

        
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
            
        if isinstance(node, list):
            node = node[0] if node else None
        
        # Always execute the block, even with empty context
        # node:* functions will check for None and raise appropriate errors
        self._context_stack.push(node)
        self._execute_tokens(tokens, start + 1, select_end)

        # Propagate variables set in select body to parent scope
        current_vars = self._context_stack.current_scope_variables()
        for name, value in current_vars.items():
            self._context_stack.set_variable_in_parent(name, value)

        self._context_stack.pop()
        
        return i  # After ENDSELECT
    
    def _handle_include(self, content: str):
        """Handle [!INCLUDE "file"!]"""
        # Strip quotes
        filename = content.strip().strip('"\'')
        # Normalize backslashes (Windows style) to forward slashes
        filename = filename.replace('\\', '/')
        
        # Prevent infinite recursion
        if self._recursion_depth >= self.MAX_RECURSION_DEPTH:
            raise TemplateParseError(f"Maximum recursion depth exceeded during include of {filename}")
        
        # Resolve path using search paths
        include_path = None
        for search_path in self.include_search_paths:
            candidate = search_path / filename
            if candidate.exists():
                include_path = candidate
                break
        
        if not include_path:
            # Fallback to current template's directory if available
            if self._template_file:
                parent = Path(self._template_file).parent
                candidate = parent / filename
                if candidate.exists():
                    include_path = candidate
        
        if not include_path:
            if self.strict:
                raise TemplateParseError(f"Include file not found: {filename} (searched in {self.include_search_paths})")
            return

        try:
            template = self._load_template_file(include_path)
            tokens = tokenize(template)
            
            self._recursion_depth += 1
            try:
                self._execute_tokens(tokens, 0, len(tokens))
            finally:
                self._recursion_depth -= 1
        except Exception as e:
            _debug_log(f"ERROR including {filename}: {e}")
            if self.strict:
                raise TemplateParseError(f"Error including {filename}: {e}")

    
    def _evaluate_expression(self, expr: str) -> Any:
        """Evaluate an expression and return its value."""
        if expr is None: return None
        expr = expr.strip()

        # 1. Literal Strings (Handle both '...' and "...")
        if (expr.startswith("'") and expr.endswith("'")) or \
           (expr.startswith('"') and expr.endswith('"')):
            inner = expr[1:-1]
            # Check if the string content looks like a function call or expression
            # that should be evaluated (e.g., "node:name(.)", "num:i(5)")
            # Functions have format: namespace:function(...)
            if ':' in inner and '(' in inner and ')' in inner:
                # This looks like a function call, evaluate it
                return self._evaluate_expression(inner)
            # Check if the string content is a variable reference (starts with $)
            # EB Tresos treats "$var" as a variable reference, not a literal
            if inner.startswith('$'):
                return self._evaluate_expression(inner)
            return inner
        
        # Handle numeric literals explicitly
        try:
            if re.match(r'^-?\d+\.\d+$', expr):
                return float(expr)
            if expr.isdigit() or (expr.startswith('-') and expr[1:].isdigit()):
                return int(expr)
        except: pass

            
        # 2. Variable reference ($name) - only if it's a pure variable (no operators)
        # Check for operators first to avoid matching "$X + 1" as variable "X + 1"
        if expr.startswith('$'):
            var_name = expr[1:]
            # Check if this is a pure variable reference (no operators like + - * / etc.)
            # A pure variable name contains only alphanumeric, underscore, and optionally /
            is_pure_var = all(c.isalnum() or c in '_/' for c in var_name)
            if is_pure_var:
                if '/' in var_name:
                    return self._unwrap_value(self._evaluate_xpath(expr))
                if self._context_stack.has_variable(var_name):
                    return self._context_stack.get_variable(var_name)
                if self.strict:
                    raise UndefinedVariableError(var_name)
                return None
            # else: fall through to operator parsing below

        # 2b. Parenthesized expression - strip outer parentheses and evaluate
        if expr.startswith('(') and expr.endswith(')'):
            # Check if this is a complete parenthesized expression (balanced)
            depth = 0
            is_balanced = True
            for i, char in enumerate(expr):
                if char == '(': depth += 1
                elif char == ')': depth -= 1
                # If depth becomes 0 before the end, parentheses are not balanced
                if depth == 0 and i < len(expr) - 1:
                    is_balanced = False
                    break
            if is_balanced and depth == 0:
                # Strip outer parentheses and evaluate inner expression
                inner = expr[1:-1].strip()
                return self._evaluate_expression(inner)

        # Helper to find operators NOT inside parentheses or brackets
        # For left-associative operators (like div), we need to find the LAST occurrence
        # to ensure (a div b div c) is computed as ((a div b) div c)
        def find_top_level_op(s: str, ops: List[str]) -> Optional[Tuple[str, str, str]]:
            depth = 0
            in_quote = None
            last_found = None  # Track the last found operator position

            for i in range(len(s)):
                char = s[i]
                if char in ('"', "'"):
                    if in_quote == char: in_quote = None
                    elif in_quote is None: in_quote = char
                if in_quote: continue

                if char in ('(', '['): depth += 1
                elif char in (')', ']'): depth -= 1
                elif depth == 0:
                    # Check for operators
                    for op in ops:
                        if s[i:].startswith(op):
                            # SPECIAL CASE: if op is '*', check if it's an XPath wildcard
                            # XPath wildcards often follow '/' or are at start/end of segment
                            if op == '*':
                                prev_char = s[i-1] if i > 0 else None
                                if prev_char == '/':
                                    continue # Skip '/' followed by '*' as it's XPath

                            # Ensure it's not a substring of a larger identifier
                            # if it's a word operator like 'div'
                            stripped_op = op.strip()
                            if stripped_op.isalpha():
                                # For operators with surrounding spaces (like ' div '),
                                # the spaces already serve as word boundaries
                                if op != stripped_op:
                                    # Operator has surrounding spaces, no extra boundary check needed
                                    last_found = (op, s[:i], s[i+len(op):])
                                else:
                                    # Check boundaries if it's a word without spaces
                                    before = s[i-1] if i > 0 else ' '
                                    after = s[i+len(op)] if i+len(op) < len(s) else ' '
                                    if not (before.isalnum() or before == '_') and \
                                       not (after.isalnum() or after == '_'):
                                        last_found = (op, s[:i], s[i+len(op):])
                            else:
                                # For symbol operators like + - * /
                                # SPECIAL CASE: '-' could be part of a function name like 'substring-after'
                                # Check if both sides are alphanumeric (part of identifier)
                                if op == '-':
                                    before = s[i-1] if i > 0 else ' '
                                    after = s[i+1] if i+1 < len(s) else ' '
                                    # If '-' is surrounded by alphanumeric chars, it's likely part of a name
                                    if (before.isalnum() or before == '_') and (after.isalnum() or after == '_'):
                                        continue  # Skip, this is part of a function name
                                last_found = (op, s[:i], s[i+len(op):])

            return last_found

        # 3. Logical Operators (Top-level only, lowest precedence)
        and_parts = self._split_top_level(expr, [' and '])
        if and_parts:
            return all(self._evaluate_condition(p) for p in and_parts)
            
        or_parts = self._split_top_level(expr, [' or '])
        if or_parts:
            return any(self._evaluate_condition(p) for p in or_parts)

        # 4. Arithmetic and Comparison Operations (Top-level only)
        # Split on lowest precedence first
        op_groups = [
            (['==', '!=', '>=', '<=', '>', '<', '='], 'comp'),
            (['+', '-'], 'math'),
            (['*', ' div ', ' mod '], 'math_high')
        ]
        
        for ops, group_type in op_groups:
            found = find_top_level_op(expr, ops)
            if found:
                op, left, right = found
                left_val = self._unwrap_value(self._evaluate_expression(left))
                right_val = self._unwrap_value(self._evaluate_expression(right))
                
                if group_type == 'comp':
                    # Normalized comparison

                    check_op = op.strip()

                    # Truthiness normalization
                    def to_bool(v):
                        if isinstance(v, bool): return v
                        if v is None: return False
                        vs = str(v).lower()
                        return vs in ('true', '1', 'yes', 'on', 'std_on')

                    # Check if either side looks like a boolean value
                    def is_bool_like(v):
                        if isinstance(v, bool): return True
                        if isinstance(v, int) and v in (0, 1): return True
                        if isinstance(v, str):
                            return v.lower() in ('true', 'false', '0', '1', 'yes', 'no', 'on', 'off', 'std_on', 'std_off')
                        return False

                    if check_op in ('==', '='):
                        # Use boolean comparison if either value looks boolean
                        if is_bool_like(left_val) or is_bool_like(right_val):
                            return to_bool(left_val) == to_bool(right_val)
                        return str(left_val) == str(right_val)
                    elif check_op == '!=':
                        if is_bool_like(left_val) or is_bool_like(right_val):
                            return to_bool(left_val) != to_bool(right_val)
                        return str(left_val) != str(right_val)
                    
                    # Numeric comparisons
                    try:
                        l_f = float(left_val)
                        r_f = float(right_val)
                        if check_op == '>': return l_f > r_f
                        if check_op == '<': return l_f < r_f
                        if check_op == '>=': return l_f >= r_f
                        if check_op == '<=': return l_f <= r_f
                    except:
                        return None
                else:
                    # Math operations
                    try:
                        # Helper to convert to number if possible
                        def to_number(v):
                            if isinstance(v, (int, float)):
                                return v
                            if isinstance(v, str):
                                v = v.strip()
                                try:
                                    if '.' in v:
                                        return float(v)
                                    return int(v)
                                except ValueError:
                                    return None
                            return None

                        clean_op = op.strip()
                        if clean_op == '+':
                            # Try numeric addition first
                            l_num = to_number(left_val)
                            r_num = to_number(right_val)
                            if l_num is not None and r_num is not None:
                                return l_num + r_num
                            # Fall back to string concatenation
                            return str(left_val) + str(right_val)

                        l_v = float(left_val) if not isinstance(left_val, (int, float)) else left_val
                        r_v = float(right_val) if not isinstance(right_val, (int, float)) else right_val

                        if clean_op == '-': return l_v - r_v
                        if clean_op == '*': return l_v * r_v
                        if clean_op == 'div': return l_v / r_v if r_v != 0 else None
                        if clean_op == 'mod': return l_v % r_v
                    except:
                        pass
                    return None


        # 4. Function call (Handle explicitly to avoid mixing with XPath)
        # Note: Function names can contain hyphens (e.g., substring-after, substring-before)
        # Also handle function calls with indexing like func(...)[index]
        if re.match(r'^[\w:\-]+\s*\(', expr):
            # Find matching closing parenthesis
            depth = 0
            first_open = expr.find('(')
            close_paren_idx = -1
            for i in range(first_open, len(expr)):
                if expr[i] == '(': depth += 1
                elif expr[i] == ')':
                    depth -= 1
                    if depth == 0:
                        close_paren_idx = i
                        break

            if close_paren_idx >= 0:
                # Check for indexing after function call: func(...)[index]
                if close_paren_idx == len(expr) - 1:
                    # No indexing, just function call
                    return self._evaluate_function_call(expr)
                elif expr[close_paren_idx + 1] == '[':
                    # Has indexing: func(...)[index]
                    # BUT ONLY if it's a simple index and NOTHING ELSE follows
                    # If it's something like func(...)[index]/Path, let XPath engine handle it
                    if expr.endswith(']'):
                        index_part = expr[close_paren_idx + 1:]
                        # If index_part has multiple brackets or slashes, it's a path, not a simple index
                        if not ('/' in index_part or index_part.count('[') > 1):
                            func_part = expr[:close_paren_idx + 1]
                            # Evaluate the function
                            result = self._evaluate_function_call(func_part)

                            # Parse and apply index
                            idx_str = index_part[1:-1]
                            idx_val = None
                            if idx_str.isdigit():
                                idx_val = int(idx_str) - 1  # 1-indexed to 0-indexed
                            else:
                                # Evaluate index expression
                                evaluated = self._evaluate_expression(idx_str)
                                if evaluated is not None:
                                    try:
                                        idx_val = int(evaluated) - 1
                                    except (TypeError, ValueError):
                                        pass

                            if idx_val is not None and isinstance(result, list):
                                if 0 <= idx_val < len(result):
                                    return result[idx_val]
                                return None
                            return result

        # 5. XPath or Node Access
        res = self._evaluate_xpath(expr)
        if res is not None:
            return res


        # 6. Primary Literals
        if expr.isdigit(): return int(expr)
        if expr.lower() == 'true': return True
        if expr.lower() == 'false': return False
        
        # 7. Fallback for undefined identifiers
        if self.strict:
            raise UndefinedVariableError(expr)
            
        if '/' in expr or expr.startswith('.') or '[' in expr:
            return None
            
        if expr.isupper() and len(expr) > 1:
            return expr
            
        return None





    
    def _unwrap_value(self, val: Any) -> Any:
        """Unwrap value from ConfigurationNode if needed.

        In scalar context (e.g., [!expr!] output), when XPath returns multiple nodes,
        we follow XPath string() semantics: return the string value of the FIRST node.

        This prevents outputting Python object representations like:
        [ConfigurationNode(short_name='...', ...)]
        """
        if isinstance(val, list):
            if not val:
                return None
            if len(val) == 1:
                val = val[0]
            else:
                # Multiple nodes in scalar context - follow XPath string() semantics:
                # Use the first node's value (with debug warning for template authors)
                first = val[0]
                if hasattr(first, 'get_value'):
                    _debug_log(f"WARNING: _unwrap_value() received {len(val)} nodes in scalar context. "
                               f"Using first node's value. Path hint: {getattr(first, 'path', 'unknown')}")
                    return first.get_value()
                # For non-node lists (e.g., from text:split), return first element
                return first

        if hasattr(val, 'get_value'):
            return val.get_value()
        return val

        
    def _evaluate_condition(self, condition: str) -> bool:
        """Evaluate a condition string (used in IF, WHILE)."""
        if condition is None: return False
        if isinstance(condition, bool): return condition
        
        condition = self._strip_tag_quotes(condition)
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
        
        # Handle 'and' / 'or' with unified parenthesis-aware splitting
        # (Logical operators have lower precedence than comparisons)
        and_parts = self._split_top_level(condition, [' and '])
        if and_parts:
            return all(self._evaluate_condition(p) for p in and_parts)
        
        or_parts = self._split_top_level(condition, [' or '])
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
                
                # Handle int/bool compared with boolean string ('true'/'false')
                # e.g., 1 = 'true' should be True, 0 = 'true' should be False
                if isinstance(left_val, (int, bool)) and isinstance(right_val, str):
                    if right_val.lower() in ('true', 'false'):
                        left_is_truthy = str(left_val).lower() in ('true', '1', 'yes', 'on')
                        right_is_truthy = right_val.lower() == 'true'
                        left_val = left_is_truthy
                        right_val = right_is_truthy
                
                if isinstance(right_val, (int, bool)) and isinstance(left_val, str):
                    if left_val.lower() in ('true', 'false'):
                        left_is_truthy = left_val.lower() == 'true'
                        right_is_truthy = str(right_val).lower() in ('true', '1', 'yes', 'on')
                        left_val = left_is_truthy
                        right_val = right_is_truthy
                
                # Numeric normalization (only if not already processed as booleans)
                if isinstance(left_val, (int, float)) and isinstance(right_val, str):
                    if right_val.lower() not in ('true', 'false'):
                        try: right_val = float(right_val)
                        except: pass
                if isinstance(right_val, (int, float)) and isinstance(left_val, str):
                    if left_val.lower() not in ('true', 'false'):
                        try: left_val = float(left_val)
                        except: pass

                # Special handling for None/empty values:
                # When comparing None or empty string with a non-empty string,
                # they should NOT be considered equal (to avoid false positives in validation)
                if check_op in ('==', '='):
                    # None vs non-empty string -> False
                    if left_val is None and isinstance(right_val, str) and right_val:
                        _debug_log(f"DEBUG: Comparison [{left} {check_op} {right}] => [None vs non-empty '{right_val}'] Result: False")
                        return False
                    if right_val is None and isinstance(left_val, str) and left_val:
                        _debug_log(f"DEBUG: Comparison [{left} {check_op} {right}] => [non-empty '{left_val}' vs None] Result: False")
                        return False
                    # Empty string vs non-empty string -> False
                    if left_val == '' and isinstance(right_val, str) and right_val and right_val != '':
                        _debug_log(f"DEBUG: Comparison [{left} {check_op} {right}] => [empty '' vs non-empty '{right_val}'] Result: False")
                        return False
                    if right_val == '' and isinstance(left_val, str) and left_val and left_val != '':
                        _debug_log(f"DEBUG: Comparison [{left} {check_op} {right}] => [non-empty '{left_val}' vs empty ''] Result: False")
                        return False
                    # Both empty strings -> False (to avoid false positives in "duplicate" validation)
                    if left_val == '' and right_val == '':
                        _debug_log(f"DEBUG: Comparison [{left} {check_op} {right}] => [both empty ''] Result: False")
                        return False

                # Special handling for != with None values only:
                # When comparing None with a non-empty string using !=,
                # return False to avoid triggering validation errors for unconfigured items
                # NOTE: Do NOT apply this to empty string comparisons - "v" != "" should be True
                if check_op == '!=':
                    # None vs non-empty string with != -> False (treat as "equal" to skip validation)
                    if left_val is None and isinstance(right_val, str) and right_val:
                        _debug_log(f"DEBUG: Comparison [{left} {check_op} {right}] => [None != non-empty] Result: False (skip validation)")
                        return False
                    if right_val is None and isinstance(left_val, str) and left_val:
                        _debug_log(f"DEBUG: Comparison [{left} {check_op} {right}] => [non-empty != None] Result: False (skip validation)")
                        return False

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
            
        return bool(value)
    
    def _split_top_level(self, s: str, ops: List[str]) -> List[str]:
        """Split a string by operators NOT inside parentheses or brackets."""
        parts = []
        depth = 0
        in_quote = None
        current = []
        i = 0
        while i < len(s):
            char = s[i]
            if char in ('"', "'"):
                if in_quote == char: in_quote = None
                elif in_quote is None: in_quote = char
            
            if in_quote is None:
                if char in ('(', '['):
                    depth += 1
                elif char in (')', ']'):
                    depth -= 1
                elif depth == 0:
                    # Check for operators
                    found_op = None
                    for op in ops:
                        if s[i:].lower().startswith(op.lower()):
                            # Special case for word operators: check boundaries
                            # If the operator already has spaces (like ' and '), we don't need extra boundary checks
                            if op.strip().isalpha():
                                if op.startswith(' ') or op.endswith(' '):
                                    found_op = op
                                    break
                                before = s[i-1] if i > 0 else ' '
                                after = s[i+len(op)] if i+len(op) < len(s) else ' '
                                if not (before.isalnum() or before == '_') and \
                                   not (after.isalnum() or after == '_'):
                                    found_op = op
                                    break
                            else:
                                found_op = op
                                break
                    
                    if found_op:
                        parts.append(''.join(current).strip())
                        current = []
                        i += len(found_op)
                        continue
            
            current.append(char)
            i += 1
        
        if current:
            parts.append(''.join(current).strip())
            
        return parts if len(parts) > 1 else []

    def _evaluate_function_call(self, expr: str) -> Any:
        """Evaluate a function call like node:value(...)."""
        # Parse function name and arguments
        paren_idx = expr.find('(')
        if paren_idx == -1: return None
        func_name = expr[:paren_idx].strip()
        args_str = expr[paren_idx + 1:-1].strip()
        
        # Parse arguments (supports nested parens and quotes)
        args = []
        if args_str:
            depth = 0
            in_quote = None
            current_arg = []
            for char in args_str:
                if char in ('"', "'"):
                    if in_quote == char: in_quote = None
                    elif in_quote is None: in_quote = char
                
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
            try:
                res = self._builtins.call(func_name, *evaluated_args)
                return res
            except Exception as e:
                logger.error(f"Error calling function {func_name}: {e}")
                if self.strict: raise
                return None
        
        # Fallback for count() which might be handled by XPath engine but called as function
        if func_name == 'count' and len(evaluated_args) == 1:
             # If it was an XPath string, it's already evaluated to a result
             val = evaluated_args[0]
             if val is None: return 0
             if isinstance(val, list): return len(val)
             return 1

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
                # Handle indexing like [1] or [num:i(1)] or [$var]
                index = None
                if '[' in part and part.endswith(']'):
                    base_name = part[:part.index('[')]
                    idx_str = part[part.index('[')+1:-1]
                    if idx_str.isdigit():
                        index = int(idx_str) - 1 # 1-indexed to 0-indexed
                    else:
                        # Evaluate the index expression
                        idx_val = self._evaluate_expression(idx_str)
                        if idx_val is not None:
                            try:
                                index = int(idx_val) - 1  # 1-indexed to 0-indexed
                            except (TypeError, ValueError):
                                pass
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
        start_expr = self._strip_tag_quotes(match.group(2))
        end_expr = self._strip_tag_quotes(match.group(3))
        
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
        
        # Execute tokens between NOCODE and ENDNOCODE using state
        self._nocode_depth += 1
        try:
            self._execute_tokens(tokens, start + 1, nocode_end)
        finally:
            self._nocode_depth -= 1
            
        return i  # After ENDNOCODE

    def _handle_code(self, tokens: List[Token], start: int, end: int) -> int:
        """Handle CODE/ENDCODE block within NOCODE.
        
        Inside CODE, output suppression from NOCODE is temporarily lifted.
        
        Returns index after ENDCODE.
        """
        # Find matching ENDCODE
        depth = 1
        i = start + 1
        code_end = end
        
        while i < end and depth > 0:
            tok = tokens[i]
            if tok.type == TokenType.CODE:
                depth += 1
            elif tok.type == TokenType.ENDCODE:
                depth -= 1
                if depth == 0:
                    code_end = i
            i += 1
        
        # Execute tokens between CODE and ENDCODE using state
        old_in_code = self._in_code_block
        self._in_code_block = True
        try:
            self._execute_tokens(tokens, start + 1, code_end)
        finally:
            self._in_code_block = old_in_code
            
        return i  # After ENDCODE
    
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
        
        # Parse params - handle both "Name" and "Name" = "Default"
        params = []
        for p in parts[1:]:
            p = p.strip()
            # If it has "=", it's a parameter with default value
            if '=' in p:
                name_part = p.split('=', 1)[0].strip()
                params.append(name_part.strip('"\' '))
            else:
                params.append(p.strip('"\' '))

        
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
            
        # Evaluate arguments
        # Support both positional and named arguments: [!CALL Macro, "123", Param1="456"!]
        self._context_stack.push()
        self._recursion_depth += 1
        
        try:
            # First, evaluate all arguments and separate into positional and named
            pos_args = []
            named_args = {}
            
            for arg_expr in args_exprs:
                arg_expr = arg_expr.strip()

                # Check for named argument: ParamName = Expr or "ParamName" = Expr
                name_match = re.match(r'^\s*["\']?([\w:]+)["\']?\s*=(.*)$', arg_expr)
                if name_match:
                    arg_name = name_match.group(1).strip()
                    arg_val_expr = name_match.group(2).strip()
                    val = self._evaluate_expression(arg_val_expr)
                    # EB Tresos behavior: If the value looks like an XPath path (contains / but not URL-like),
                    # try to evaluate it as XPath to get the actual value at that path
                    if isinstance(val, str) and '/' in val and not val.startswith('http') and not val.startswith('//'):
                        xpath_val = self._evaluate_xpath(val)
                        if xpath_val is not None:
                            val = self._unwrap_value(xpath_val)
                    named_args[arg_name] = val
                else:
                    # Positional
                    val = self._evaluate_expression(arg_expr)
                    # Same XPath evaluation for positional arguments
                    if isinstance(val, str) and '/' in val and not val.startswith('http') and not val.startswith('//'):
                        xpath_val = self._evaluate_xpath(val)
                        if xpath_val is not None:
                            val = self._unwrap_value(xpath_val)
                    pos_args.append(val)
            
            # Map arguments to parameters
            for idx, param_name in enumerate(params):
                if param_name in named_args:
                    # Use named argument
                    self._context_stack.set_variable(param_name, named_args[param_name])
                elif idx < len(pos_args):
                    # Use positional argument
                    self._context_stack.set_variable(param_name, pos_args[idx])
                else:
                    # No value provided, keep default (None or previously set)
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
            # NOTE: EB Tresos templates like CG_ChangeStringListMember depend on
            # parameter variables (like "Object") being propagated back after modification.
            # So we propagate ALL variables, not just non-parameters.
            current_vars = self._context_stack.current_scope_variables()
            for name, value in current_vars.items():
                # Propagate all variables including modified parameters
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
                    message_parts.append(self._builtins.to_string(val))
            
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
                val = self._builtins.to_string(self._evaluate_expression(tok.content))
        
        message = "".join(message_parts).strip()
        _debug_log(f"ERROR: {message}")
        if self.strict:
            raise TemplateParseError(f"Template Error: {message}")
        else:
            # Non-strict: just log warning and continue
            _debug_log(f"WARNING: Template Error suppressed in non-strict mode: {message}")
            # Optionally add a comment in output? No, standard behavior is skip/trace
        
        return i


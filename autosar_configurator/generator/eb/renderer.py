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
from typing import Optional, Dict, Any, List
from pathlib import Path

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
    
    def load_module(
        self, 
        module_def: EcucModuleDef, 
        configuration: Optional[EcucModuleConfiguration] = None
    ):
        """Load a module's definition and configuration.
        
        This can be called multiple times for multi-module projects.
        
        Args:
            module_def: Module definition from EcucDefParser
            configuration: Module configuration from ConfigurationManager
        """
        self.overlay_engine.build_configuration_tree(module_def, configuration)
    
    def render(
        self, 
        template: str, 
        module_name: Optional[str] = None,
        extra_vars: Optional[Dict[str, Any]] = None
    ) -> str:
        """Render a template string.
        
        Args:
            template: Template source code
            module_name: Name of module to use as initial context (optional)
            extra_vars: Additional variables to inject into context
            
        Returns:
            Rendered output string
        """
        # Determine initial context node
        root_node = None
        if module_name:
            root_node = self.symbol_table.get_module(module_name)
        elif self.symbol_table.get_all_modules():
            # Use first module if only one loaded
            modules = self.symbol_table.get_all_modules()
            if len(modules) == 1:
                root_node = self.symbol_table.get_module(modules[0])
        
        # Initialize context
        self._context_stack = ContextStack(root_node)
        self._builtins = BuiltinFunctions(self.symbol_table, self._context_stack)
        self._xpath_engine = XPathEngine(self.symbol_table, self._context_stack)
        self._output_buffer = []
        self._suppress_next_newline = False
        
        # Inject extra variables
        if extra_vars:
            for name, value in extra_vars.items():
                self._context_stack.set_variable(name, value)
        
        # Tokenize
        tokens = tokenize(template)
        
        # Execute
        self._execute_tokens(tokens, 0, len(tokens))
        
        return "".join(self._output_buffer)
    
    def render_file(
        self, 
        template_path: Path,
        module_name: Optional[str] = None,
        extra_vars: Optional[Dict[str, Any]] = None
    ) -> str:
        """Render a template from a file.
        
        Args:
            template_path: Path to template file
            module_name: Module name for initial context
            extra_vars: Additional variables
            
        Returns:
            Rendered output string
        """
        template = self._load_template_file(template_path)
        return self.render(template, module_name, extra_vars)
    
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
            
            if token.type == TokenType.TEXT:
                # Apply smart trimming
                content = token.content
                if token.directive_only_line:
                    # Remove trailing newline from directive-only lines
                    content = content.rstrip('\n\r')
                    # Also remove leading whitespace if it's just indentation
                    if content.strip() == '':
                        content = ''  # Skip pure whitespace on directive lines
                self._output_buffer.append(content)
                i += 1
                
            elif token.type == TokenType.OUTPUT:
                value = self._evaluate_expression(token.content)
                self._output_buffer.append(str(value) if value is not None else "")
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
                
            else:
                # Unknown or end token - skip
                i += 1
        
        return i
    
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
        if isinstance(node, list):
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
        
        # Resolve path
        include_path = self.template_dir / filename
        
        try:
            template = self._load_template_file(include_path)
            tokens = tokenize(template)
            self._execute_tokens(tokens, 0, len(tokens))
        except FileNotFoundError:
            if self.strict:
                raise TemplateParseError(f"Include file not found: {filename}")
    
    def _evaluate_expression(self, expr: str) -> Any:
        """Evaluate an expression and return its value."""
        expr = expr.strip()
        
        # Strip outer quotes for string literals
        if (expr.startswith('"') and expr.endswith('"')) or \
           (expr.startswith("'") and expr.endswith("'")):
            inner = expr[1:-1]
            
            # Check if the inner content is actually a function call or expression
            # that should be evaluated (not just a plain string)
            if '(' in inner and inner.endswith(')'):
                # This is a function call inside quotes - evaluate it
                return self._evaluate_expression(inner)
            elif inner.startswith('$') or inner.startswith('@'):
                # Variable reference inside quotes ($var or @index)
                return self._evaluate_expression(inner)
            else:
                # Plain string literal
                return inner
        
        # Variable reference ($name)
        if expr.startswith('$'):
            var_name = expr[1:]
            if self._context_stack.has_variable(var_name):
                return self._context_stack.get_variable(var_name)
            if self.strict:
                raise UndefinedVariableError(var_name)
            return None
        
        # Function call
        if '(' in expr and expr.endswith(')'):
            return self._evaluate_function_call(expr)
        
        # XPath or node access
        if '/' in expr or expr.startswith('.') or 'as:' in expr:
            return self._evaluate_xpath(expr)
        
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
            child = current.get_child(expr)
            if child:
                return child.get_value() if child.node_type == 'parameter' else child
        
        return expr  # Return as-is
    
    def _evaluate_condition(self, condition: str) -> bool:
        """Evaluate a boolean condition."""
        condition = condition.strip()
        
        # Strip outer quotes if present (common in EB syntax [!IF "expr"!])
        if (condition.startswith('"') and condition.endswith('"')) or \
           (condition.startswith("'") and condition.endswith("'")):
            condition = condition[1:-1].strip()
        
        # Handle negation
        if condition.startswith('!') or condition.startswith('not '):
            inner = condition[1:].strip() if condition.startswith('!') else condition[4:].strip()
            return not self._evaluate_condition(inner)
        
        # Handle comparison operators
        for op in [' == ', ' != ', ' > ', ' < ', ' >= ', ' <= ']:
            if op in condition:
                left, right = condition.split(op, 1)
                left_val = self._evaluate_expression(left.strip())
                right_val = self._evaluate_expression(right.strip())
                
                if op == ' == ':
                    return left_val == right_val
                elif op == ' != ':
                    return left_val != right_val
                elif op == ' > ':
                    return left_val > right_val
                elif op == ' < ':
                    return left_val < right_val
                elif op == ' >= ':
                    return left_val >= right_val
                elif op == ' <= ':
                    return left_val <= right_val
        
        # Handle 'and' / 'or'
        if ' and ' in condition:
            parts = condition.split(' and ')
            return all(self._evaluate_condition(p.strip()) for p in parts)
        if ' or ' in condition:
            parts = condition.split(' or ')
            return any(self._evaluate_condition(p.strip()) for p in parts)
        
        # Simple truthiness check
        value = self._evaluate_expression(condition)
        return bool(value)
    
    def _evaluate_function_call(self, expr: str) -> Any:
        """Evaluate a function call like node:value(...)."""
        # Parse function name and arguments
        paren_idx = expr.index('(')
        func_name = expr[:paren_idx].strip()
        args_str = expr[paren_idx + 1:-1].strip()
        
        # Parse arguments (simplified - doesn't handle nested parens well)
        args = []
        if args_str:
            # Split by comma, but be careful with nested function calls
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
        node = current
        
        for part in parts:
            if part == '..':
                node = node.parent if node else None
            elif node:
                child = node.get_child(part)
                if child:
                    node = child
                else:
                    # Try to find in children as list
                    children = [c for c in node.children.values() if c.short_name == part]
                    node = children if children else None
            
            if node is None:
                break
        
        return node

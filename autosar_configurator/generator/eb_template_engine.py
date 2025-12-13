"""
EB Tresos Compatible Template Engine
Supports [! ... !] syntax and basic XPath-like queries.
"""
import re
from typing import Dict, Any, List, Optional
from ..core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue

class EBToken:
    TEXT = 'TEXT'
    TAG = 'TAG'  # [! ... !]
    
    def __init__(self, type: str, content: str):
        self.type = type
        self.content = content
        
    def __repr__(self):
        return f"Token({self.type}, {repr(self.content)})"

class EBTemplateEngine:
    """Template engine compatible with EB Tresos syntax"""
    
    def __init__(self):
        # Matches [! ... !] blocks, capturing content
        # The ? ungreedy match is important
        self.tag_pattern = re.compile(r'\[!(.*?)!\]', re.DOTALL)
        
    def render(self, template: str, context: Dict[str, Any]) -> str:
        """Render template with given context
        
        Args:
            template: Template string
            context: Dictionary containing 'configuration' (EcucModuleConfiguration) 
                     and other context variables
        
        Returns:
            Rendered string
        """
        tokens = self._tokenize(template)
        return self._parse_and_execute(tokens, context)
        
    def _tokenize(self, template: str) -> List[EBToken]:
        tokens = []
        last_pos = 0
        
        for match in self.tag_pattern.finditer(template):
            # Add text before the tag
            if match.start() > last_pos:
                tokens.append(EBToken(EBToken.TEXT, template[last_pos:match.start()]))
            
            # Add the tag content
            tokens.append(EBToken(EBToken.TAG, match.group(1).strip()))
            last_pos = match.end()
            
        # Add remaining text
        if last_pos < len(template):
            tokens.append(EBToken(EBToken.TEXT, template[last_pos:]))
            
        return tokens

    def _parse_and_execute(self, tokens: List[EBToken], context: Dict[str, Any]) -> str:
        output = []
        i = 0
        
        while i < len(tokens):
            token = tokens[i]
            
            if token.type == EBToken.TEXT:
                output.append(token.content)
                i += 1
            elif token.type == EBToken.TAG:
                command, args = self._parse_tag(token.content)
                
                if command == 'VAR':
                    self._handle_var(args, context)
                    i += 1
                elif command == 'IF':
                    # Find matching ELSE or ENDIF
                    block_content, else_content, new_index = self._find_block_end(tokens, i + 1, 'IF', 'ENDIF', intermediate='ELSE')
                    
                    if self._evaluate_condition(args, context):
                        output.append(self._parse_and_execute(block_content, context))
                    elif else_content is not None:
                        output.append(self._parse_and_execute(else_content, context))
                        
                    i = new_index
                elif command == 'LOOP':
                    block_content, _, new_index = self._find_block_end(tokens, i + 1, 'LOOP', 'ENDLOOP')
                    output.append(self._execute_loop(args, block_content, context))
                    i = new_index
                elif command == '//':
                    # Comment, ignore
                    i += 1
                elif command is None:
                    # Expression output: [!"expression"!]
                    output.append(str(self._evaluate_expression(token.content, context)))
                    i += 1
                else:
                    # Unknown command or just an expression starting with a keyword-like string
                    output.append(str(self._evaluate_expression(token.content, context)))
                    i += 1
                    
        return "".join(output)

    def _parse_tag(self, content: str):
        """Parse tag content to determine command and arguments"""
        # Simple parser: check if it starts with a keyword
        parts = content.split(None, 1)
        if not parts:
            return None, None
            
        keyword = parts[0]
        args = parts[1] if len(parts) > 1 else ""
        
        if keyword in ('IF', 'ELSE', 'ENDIF', 'LOOP', 'ENDLOOP', 'VAR', '//'):
            return keyword, args
            
        # Check for output expression [!"..."]
        # In EB, [!"..."] is output. But sometimes we just get an expression.
        # If it starts with quote, it's likely an output expression
        if content.startswith('"') or content.startswith("'"):
            return None, content
            
        return None, content

    def _find_block_end(self, tokens: List[EBToken], start_index: int, 
                       start_tag: str, end_tag: str, intermediate: str = None):
        """Find the end of a block, handling nesting.
        Returns: (main_block_tokens, else_block_tokens, end_index)
        """
        balance = 1
        main_block = []
        else_block = None
        current_block = main_block
        
        i = start_index
        while i < len(tokens):
            token = tokens[i]
            if token.type == EBToken.TAG:
                cmd, _ = self._parse_tag(token.content)
                
                if cmd == start_tag:
                    balance += 1
                elif cmd == end_tag:
                    balance -= 1
                    if balance == 0:
                        return main_block, else_block, i + 1
                elif intermediate and cmd == intermediate and balance == 1:
                    # Found ELSE at top level
                    current_block = []
                    else_block = current_block
                    i += 1
                    continue
            
            # Append token to current accumulation block (if we are not at end)
            if balance > 0: # Should always be true here if we didn't return
                current_block.append(token)
                
            i += 1
            
        return main_block, else_block, i

    def _handle_var(self, args: str, context: Dict[str, Any]):
        """Handle [!VAR "name" = "value"!]"""
        # Very basic parser for name = value
        if '=' not in args:
            return
            
        name_part, expr_part = args.split('=', 1)
        name = self._strip_quotes(name_part.strip())
        value = self._evaluate_expression(expr_part.strip(), context)
        context[name] = value

    def _execute_loop(self, args: str, block_tokens: List[EBToken], context: Dict[str, Any]) -> str:
        """Handle [!LOOP "expression"!] ... [!ENDLOOP!]"""
        items = self._evaluate_expression(args, context)
        if not isinstance(items, list):
            return ""
            
        output = []
        for item in items:
            # Prepare loop context
            # In EB syntax, the context node changes. 
            # We'll use a special variable '.' to represent current node
            loop_context = context.copy()
            loop_context['.'] = item
            output.append(self._parse_and_execute(block_tokens, loop_context))
            
        return "".join(output)

    def _evaluate_condition(self, condition: str, context: Dict[str, Any]) -> bool:
        """Evaluate boolean condition"""
        val = self._evaluate_expression(condition, context)
        return bool(val)

    def _evaluate_expression(self, expr: str, context: Dict[str, Any]) -> Any:
        """Evaluate XPath-like expression"""
        expr = expr.strip()
        
        # Variable lookup with $
        if expr.startswith('$'):
            var_name = expr[1:]
            return context.get(var_name)
            
        # String literal
        if (expr.startswith('"') and expr.endswith('"')) or \
           (expr.startswith("'") and expr.endswith("'")):
            return expr[1:-1]
            
        # Number literal
        if expr.isdigit():
            return int(expr)
            
        # Basic variable lookup (without $)
        if expr in context:
            return context[expr]
            
        # Handle simple dot access
        if expr == '.':
            return context.get('.')
            
        # XPath: as:modconf('Module')[...]
        if 'as:modconf(' in expr:
            return self._evaluate_xpath(expr, context)
            
        # Functions: node:value(.), node:name(.), num:i(.)
        if expr.startswith('node:') or expr.startswith('num:'):
            return self._evaluate_function(expr, context)

        # Return None for unresolved to treat as False in conditions
        return None

    def _evaluate_xpath(self, expr: str, context: Dict[str, Any]) -> Any:
        """Evaluate as:modconf('Module')[...]/Path/To/Item"""
        # 1. Extract module name
        # Matches as:modconf('Name') or as:modconf("Name")
        prefix_pattern = re.compile(r"as:modconf\(['\"](\w+)['\"]\)")
        match = prefix_pattern.search(expr)
        if not match:
            return None
            
        module_name = match.group(1)
        
        # 2. Get the remaining suffix after the closing parenthesis
        suffix = expr[match.end():].strip()
        
        # 3. Strip optional index [1]
        if suffix.startswith('['):
            close_bracket = suffix.find(']')
            if close_bracket != -1:
                suffix = suffix[close_bracket+1:]
        
        path_suffix = suffix
        
        # Get module configuration from context
        # Context is expected to have 'configuration' object or we look it up
        config = context.get('configuration')
        if not config:
            # Fallback: check if 'modules' dict exists in context
            modules = context.get('modules', {})
            config = modules.get(module_name)
            
        if not config:
            return None
            
        # If no suffix, return the module config object
        if not path_suffix:
            return config
            
        # Traverse path: /Container/SubContainer/Param
        current_node = config
        parts = [p for p in path_suffix.split('/') if p]
        

        for part in parts:
            print(f"DEBUG: Processing part '{part}' against node {type(current_node)}")
            if hasattr(current_node, 'containers'):
                # It's ModuleConfig, find container
                found = False
                for c in current_node.containers:
                    if c.short_name == part:
                        current_node = c
                        found = True
                        break
                if not found:
                    print(f"DEBUG: Container '{part}' not found in {current_node}")
                    return None
            elif hasattr(current_node, 'sub_containers'):
                # It's Container, look in sub-containers or parameters
                # Check parameters first
                print(f"DEBUG: Checking parameters {current_node.parameter_values.keys()}")
                if part in current_node.parameter_values:
                    current_node = current_node.parameter_values[part]
                    print("DEBUG: Found in parameters")
                elif part in current_node.reference_values:
                    current_node = current_node.reference_values[part]
                else:
                    # Check sub-containers
                    found = False
                    for sub in current_node.sub_containers:
                        if sub.short_name == part:
                            current_node = sub
                            found = True
                            break
                    if not found:
                        print(f"DEBUG: Part '{part}' not found in sub-containers or params")
                        return None
            else:
                print(f"DEBUG: Node {current_node} has no containers/sub_containers")
                return None
                
        return current_node

    def _evaluate_function(self, expr: str, context: Dict[str, Any]) -> Any:
        """Evaluate node:value(arg), node:name(arg), etc."""
        # Simple parser: func(arg)
        match = re.match(r"([\w:]+)\((.*)\)", expr)
        if not match:
            return None
            
        func_name = match.group(1)
        arg_expr = match.group(2)
        
        # Evaluate argument
        arg = self._evaluate_expression(arg_expr, context)
        
        if func_name == 'node:value':
            if hasattr(arg, 'value'):
                return arg.value
            return arg
        elif func_name == 'node:name':
            if hasattr(arg, 'short_name'):
                return arg.short_name
            return str(arg)
        elif func_name == 'num:i':
            try:
                if hasattr(arg, 'value'):
                    return int(arg.value)
                return int(arg)
            except (ValueError, TypeError):
                return 0
                
        return None

    def _strip_quotes(self, s: str) -> str:
        if (s.startswith('"') and s.endswith('"')) or \
           (s.startswith("'") and s.endswith("'")):
            return s[1:-1]
        return s

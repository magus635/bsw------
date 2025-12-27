"""
Lightweight Template Engine
Supports basic template features without external dependencies
"""
import re
from typing import Dict, Any, List


class TemplateEngine:
    """Simple template engine for code generation
    
    Supports:
    - Variable substitution: {{ variable }}
    - For loops: {% for item in items %} ... {% endfor %}
    - If conditionals: {% if condition %} ... {% endif %}
    """
    
    def __init__(self):
        # Support variable with optional filter: {{ var | filter }}
        self.var_pattern = re.compile(r'\{\{\s*(.+?)\s*\}\}')
        # Split patterns for manual parsing
        self.for_start_pattern = re.compile(r'\{%\s*for\s+(\w+)\s+in\s+([a-zA-Z_][a-zA-Z0-9_\.]*)\s*%\}')
        self.for_end_pattern = re.compile(r'\{%\s*endfor\s*%\}')
        self.if_pattern = re.compile(r'\{%\s*if\s+(.+?)\s*%\}(.*?)(?:\{%\s*else\s*%\}(.*?))?\{%\s*endif\s*%\}', re.DOTALL)
        
    def render(self, template: str, context: Dict[str, Any]) -> str:
        """Render template with given context
        
        Args:
            template: Template string
            context: Dictionary of variables available to template
            
        Returns:
            Rendered string
        """
        # Process for loops (which also processes variables within loops)
        result = self._process_for_loops(template, context)
        # Process conditionals
        result = self._process_conditionals(result, context)
        # Process any remaining top-level variables
        result = self._process_variables(result, context)
        
        return result
    
    def _process_for_loops(self, template: str, context: Dict[str, Any]) -> str:
        """Process {% for item in items %} loops using manual parsing to handle nesting"""
        result = []
        current_pos = 0
        
        while True:
            # Find next loop start
            match = self.for_start_pattern.search(template, current_pos)
            if not match:
                # No more loops, append remaining text
                result.append(template[current_pos:])
                break
                
            # Append text before loop
            result.append(template[current_pos:match.start()])
            
            # Find balanced end
            loop_info = self._find_balanced_loop_end(template, match)
            if not loop_info:
                # Unbalanced or error, treat as plain text
                result.append(match.group(0))
                current_pos = match.end()
                continue
                
            # Process the loop
            item_name = loop_info['item']
            collection_name = loop_info['collection']
            loop_body = loop_info['body']
            
            # Support dot notation in collection name
            collection = self._get_value(collection_name, context)
            
            if isinstance(collection, (list, tuple)):
                for item in collection:
                    # Create temporary context with loop variable
                    loop_context = context.copy()
                    loop_context[item_name] = item
                    
                    # Recursively process nested loops first
                    rendered_body = self._process_for_loops(loop_body, loop_context)
                    # Then process variables
                    rendered_body = self._process_variables(rendered_body, loop_context)
                    result.append(rendered_body)
            
            # Move past the loop
            current_pos = loop_info['end']
            
        return ''.join(result)

    def _find_balanced_loop_end(self, template: str, start_match) -> Dict[str, Any]:
        """Find the matching end tag for a loop"""
        start_pos = start_match.start()
        content_start = start_match.end()
        
        balance = 1
        current_pos = content_start
        
        while balance > 0:
            next_start = self.for_start_pattern.search(template, current_pos)
            next_end = self.for_end_pattern.search(template, current_pos)
            
            if not next_end:
                return None  # Unbalanced
                
            if next_start and next_start.start() < next_end.start():
                # Found nested start
                balance += 1
                current_pos = next_start.end()
            else:
                # Found end
                balance -= 1
                current_pos = next_end.end()
                end_pos = next_end.start()
                
        return {
            'item': start_match.group(1),
            'collection': start_match.group(2),
            'body': template[content_start:end_pos],
            'end': current_pos
        }
    
    def _process_conditionals(self, template: str, context: Dict[str, Any]) -> str:
        """Process {% if condition %} statements"""
        def replace_conditional(match):
            condition = match.group(1).strip()
            if_block = match.group(2)
            else_block = match.group(3) if match.group(3) else ''
            
            # Evaluate condition
            # Support simple checks: variable, !variable, variable == value
            if self._evaluate_condition(condition, context):
                return if_block
            else:
                return else_block
        
        return self.if_pattern.sub(replace_conditional, template)
    
    def _evaluate_condition(self, condition: str, context: Dict[str, Any]) -> bool:
        """Evaluate a simple condition"""
        # Handle negation
        if condition.startswith('!'):
            var_name = condition[1:].strip()
            value = self._get_value(var_name, context)
            return not bool(value)
        
        # Handle equality check
        if ' == ' in condition:
            left, right = condition.split(' == ', 1)
            left_val = self._get_value(left.strip(), context)
            right_val = self._parse_literal(right.strip())
            return left_val == right_val
        
        # Handle inequality check
        if ' != ' in condition:
            left, right = condition.split(' != ', 1)
            left_val = self._get_value(left.strip(), context)
            right_val = self._parse_literal(right.strip())
            return left_val != right_val
        
        # Simple variable check
        value = self._get_value(condition, context)
        return bool(value)
    
    def _parse_literal(self, value: str) -> Any:
        """Parse a literal value from template"""
        # Try to parse as number
        try:
            if '.' in value:
                return float(value)
            return int(value)
        except ValueError:
            pass
        
        # Check for string literal
        if (value.startswith('"') and value.endswith('"')) or \
           (value.startswith("'") and value.endswith("'")):
            return value[1:-1]
        
        # Return as is
        return value
    
    def _process_variables(self, template: str, context: Dict[str, Any]) -> str:
        """Process {{ variable }} substitutions"""
        def replace_var(match):
            var_name = match.group(1)
            value = self._get_value(var_name, context)
            return str(value) if value is not None else ''
        
        return self.var_pattern.sub(replace_var, template)
    
    def _get_value(self, var_name: str, context: Dict[str, Any]) -> Any:
        """Get value from context, supporting dot notation and filters"""
        # Handle filters first (e.g., var|length or var|upper)
        filter_name = None
        if '|' in var_name:
            var_name, filter_name = var_name.split('|', 1)
            var_name = var_name.strip()
            filter_name = filter_name.strip()
            
        # Handle method calls in dot notation (e.g., var.upper())
        # We simplify by stripping () if present
        parts = [p.replace('()', '') for p in var_name.split('.')]
        value = context
        
        for part in parts:
            if isinstance(value, dict):
                value = value.get(part)
            elif hasattr(value, part):
                value = getattr(value, part)
                # Auto-call if it's a simple method like upper or lower
                if callable(value) and part in ['upper', 'lower']:
                    try:
                        value = value()
                    except:
                        pass
            else:
                value = None
                break
                
        # Apply filters
        if filter_name == 'upper':
            return str(value).upper() if value is not None else ''
        elif filter_name == 'lower':
            return str(value).lower() if value is not None else ''
        elif filter_name == 'length':
            try:
                return len(value) if value is not None else 0
            except:
                return 0
            
        return value


class TemplateLoader:
    """Load templates from files"""
    
    def __init__(self, template_dir: str = None):
        """Initialize loader
        
        Args:
            template_dir: Directory containing template files
        """
        from pathlib import Path
        self.template_dir = Path(template_dir) if template_dir else Path(__file__).parent / 'templates'
        
    def load(self, template_name: str) -> str:
        """Load template file
        
        Args:
            template_name: Name of template file
            
        Returns:
            Template content
        """
        template_path = self.template_dir / template_name
        with open(template_path, 'r', encoding='utf-8') as f:
            return f.read()

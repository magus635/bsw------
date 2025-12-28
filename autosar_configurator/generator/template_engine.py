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
        self.var_pattern = re.compile(r'\{\{\s*(.+?)\s*\}\}')
        self.for_start_pattern = re.compile(r'\{%\s*for\s+([a-zA-Z_0-9,\s]+?)\s+in\s+([a-zA-Z_0-9\.\(\)]+?)\s*%\}')
        self.for_end_pattern = re.compile(r'\{%\s*endfor\s*%\}')
        self.if_start_pattern = re.compile(r'\{%\s*if\s+(.+?)\s*%\}')
        self.else_pattern = re.compile(r'\{%\s*else\s*%\}')
        self.if_end_pattern = re.compile(r'\{%\s*endif\s*%\}')
        
    def render(self, template: str, context: Dict[str, Any]) -> str:
        """Render template with given context"""
        return self.render_content(template, context)
    
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
            loop_vars = loop_info['vars'] # Might be ['item'] or ['key', 'val']
            collection_name = loop_info['collection']
            loop_body = loop_info['body']
            
            # Support .items() in collection name
            is_items = False
            if collection_name.endswith('.items()'):
                collection_name = collection_name[:-8]
                is_items = True
                
            collection = self._get_value(collection_name, context)
            
            if is_items and isinstance(collection, dict):
                items_to_iter = list(collection.items())
            elif isinstance(collection, (list, tuple)):
                items_to_iter = collection
            else:
                items_to_iter = []
            
            for i, item in enumerate(items_to_iter):
                # Create temporary context with loop variables
                loop_context = context.copy()
                
                # Support loop metadata
                loop_context['loop'] = {
                    'index0': i,
                    'index': i + 1,
                    'first': i == 0,
                    'last': i == len(items_to_iter) - 1,
                    'length': len(items_to_iter)
                }

                if is_items and len(loop_vars) >= 2:
                    loop_context[loop_vars[0]] = item[0]
                    loop_context[loop_vars[1]] = item[1]
                else:
                    loop_context[loop_vars[0]] = item
                
                # Recursively process the body with all tags (loops, ifs, vars)
                rendered_body = self.render_content(loop_body, loop_context)
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
        
        # Parse loop variables (could be "item" or "key, val")
        var_part = start_match.group(1).strip()
        vars = [v.strip() for v in var_part.split(',')]
        
        return {
            'vars': vars,
            'collection': start_match.group(2).strip(),
            'body': template[content_start:end_pos],
            'end': current_pos
        }
    
    def _process_conditionals(self, template: str, context: Dict[str, Any]) -> str:
        """Process {% if condition %} statements recursively"""
        result = []
        current_pos = 0
        
        while True:
            match = self.if_start_pattern.search(template, current_pos)
            if not match:
                result.append(template[current_pos:])
                break
                
            # Add text before the if
            result.append(template[current_pos:match.start()])
            
            # Find balanced endif
            if_info = self._find_balanced_if_end(template, match)
            if not if_info:
                # Fallback: treat as normal text if unbalanced
                result.append(template[match.start():match.end()])
                current_pos = match.end()
                continue
                
            # Evaluate condition
            if self._evaluate_condition(if_info['condition'], context):
                # Process the if body (it might have nested tags)
                body = if_info['if_body']
            else:
                # Process the else body
                body = if_info['else_body']
            
            # Recursively process the selected body
            rendered_body = self.render_content(body, context)
            result.append(rendered_body)
            
            current_pos = if_info['end']
            
        return ''.join(result)

    def _find_balanced_if_end(self, template: str, start_match) -> Dict[str, Any]:
        """Find the matching end tag for an if block"""
        content_start = start_match.end()
        
        balance = 1
        current_pos = content_start
        else_pos = None
        else_end = None
        
        while balance > 0:
            next_start = self.if_start_pattern.search(template, current_pos)
            next_else = self.else_pattern.search(template, current_pos)
            next_end = self.if_end_pattern.search(template, current_pos)
            
            if not next_end:
                return None
                
            # Determine which tag comes first
            tags = []
            if next_start: tags.append(('start', next_start))
            if next_else and balance == 1: tags.append(('else', next_else))
            tags.append(('end', next_end))
            
            tags.sort(key=lambda x: x[1].start())
            tag_type, match = tags[0]
            
            if tag_type == 'start':
                balance += 1
                current_pos = match.end()
            elif tag_type == 'else':
                else_pos = match.start()
                else_end = match.end()
                current_pos = match.end()
            else: # end
                balance -= 1
                if balance == 0:
                    end_pos = match.start()
                    current_pos = match.end()
                else:
                    current_pos = match.end()
        
        return {
            'condition': start_match.group(1).strip(),
            'if_body': template[content_start:else_pos if else_pos else end_pos],
            'else_body': template[else_end:end_pos] if else_pos else '',
            'end': current_pos
        }

    def render_content(self, content: str, context: Dict[str, Any]) -> str:
        """Helper to process all tags in a block of content"""
        content = self._process_for_loops(content, context)
        content = self._process_conditionals(content, context)
        content = self._process_variables(content, context)
        return content
    
    def _evaluate_condition(self, condition: str, context: Dict[str, Any]) -> bool:
        """Evaluate a simple condition"""
        condition = condition.strip()
        
        # Handle 'not ' prefix
        is_negated = False
        if condition.startswith('not '):
            is_negated = True
            condition = condition[4:].strip()
        elif condition.startswith('!'):
            is_negated = True
            condition = condition[1:].strip()

        # Handle 'is not None' / 'is None'
        if condition.endswith(' is None'):
            var_name = condition[:-8].strip()
            val = self._get_value(var_name, context)
            result = val is None
        elif condition.endswith(' is not None'):
            var_name = condition[:-12].strip()
            val = self._get_value(var_name, context)
            result = val is not None
        # Handle 'in' check
        elif ' in ' in condition:
            left, right = condition.split(' in ', 1)
            left_val = self._parse_literal(left.strip())
            right_val = self._get_value(right.strip(), context)
            if right_val is None: 
                result = False
            else:
                try:
                    result = left_val in right_val
                except:
                    result = False
        # Handle equality check
        elif ' == ' in condition:
            left, right = condition.split(' == ', 1)
            left_val = self._get_value(left.strip(), context)
            right_val = self._parse_literal(right.strip())
            result = left_val == right_val
        # Handle inequality check
        elif ' != ' in condition:
            left, right = condition.split(' != ', 1)
            left_val = self._get_value(left.strip(), context)
            right_val = self._parse_literal(right.strip())
            result = left_val != right_val
        else:
            # Simple variable check
            value = self._get_value(condition, context)
            result = bool(value)
            
        return not result if is_negated else result
    
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
            elif isinstance(value, (list, tuple)) and part.isdigit():
                idx = int(part)
                value = value[idx] if 0 <= idx < len(value) else None
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
        elif filter_name and filter_name in context and callable(context[filter_name]):
            try:
                return context[filter_name](value)
            except:
                return value
            
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

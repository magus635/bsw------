"""
Custom Validation Rules
Allows users to define validation rules in JSON format using a simple expression language.
"""
import json
import ast
import operator
from typing import Dict, Any, List, Optional, Union
from pathlib import Path

from ..validation_engine import ValidationRule, ValidationResult, ValidationSeverity
from ..model.definition_model import EcucModuleDef
from ..model.configuration_model import EcucModuleConfiguration, EcucContainerValue


class RuleEvaluator:
    """Safe evaluator for rule expressions"""
    
    # Allowed operators
    OPERATORS = {
        ast.Add: operator.add,
        ast.Sub: operator.sub,
        ast.Mult: operator.mul,
        ast.Div: operator.truediv,
        ast.Eq: operator.eq,
        ast.NotEq: operator.ne,
        ast.Lt: operator.lt,
        ast.LtE: operator.le,
        ast.Gt: operator.gt,
        ast.GtE: operator.ge,
        ast.And: lambda x, y: x and y,
        ast.Or: lambda x, y: x or y,
        ast.Not: operator.not_,
        ast.In: lambda x, y: x in y,
        ast.NotIn: lambda x, y: x not in y,
    }
    
    def __init__(self, context: Dict[str, Any]):
        self.context = context
        
    def evaluate(self, expression: str) -> bool:
        """Evaluate a boolean expression against the context"""
        try:
            tree = ast.parse(expression, mode='eval')
            return bool(self._eval_node(tree.body))
        except Exception as e:
            # Wrap evaluation errors
            raise ValueError(f"Evaluation failed for '{expression}': {str(e)}")
            
    def _eval_node(self, node: ast.AST) -> Any:
        """Recursively evaluate AST node"""
        if isinstance(node, ast.Constant):  # Literal values (numbers, strings, bools)
            return node.value
            
        elif isinstance(node, ast.Name):  # Variables
            return self._get_value(node.id)
            
        elif isinstance(node, ast.Attribute):  # Dot notation (container.param)
            # This is a simplification; for now we flatten context or handle simple dot access
            # But ast.Attribute is complex to handle fully recursively without a proper object model in context
            # Let's try to resolve the full name "a.b" from context first
            full_name = self._get_full_name(node)
            return self._get_value(full_name)
            
        elif isinstance(node, ast.UnaryOp):  # Unary operators (not, -)
            op_type = type(node.op)
            if op_type in self.OPERATORS:
                return self.OPERATORS[op_type](self._eval_node(node.operand))
                
        elif isinstance(node, ast.BinOp):  # Binary operators (+, -, *, /)
            op_type = type(node.op)
            if op_type in self.OPERATORS:
                return self.OPERATORS[op_type](self._eval_node(node.left), self._eval_node(node.right))
                
        elif isinstance(node, ast.Compare):  # Comparisons (==, <, >, in)
            left = self._eval_node(node.left)
            for op, comparator in zip(node.ops, node.comparators):
                op_type = type(op)
                if op_type in self.OPERATORS:
                    right = self._eval_node(comparator)
                    if not self.OPERATORS[op_type](left, right):
                        return False
                    left = right  # For chained comparisons
            return True
            
        elif isinstance(node, ast.BoolOp):  # Boolean operators (and, or)
            op_type = type(node.op)
            if op_type in self.OPERATORS:
                values = [self._eval_node(val) for val in node.values]
                # Reduce list using the operator
                result = values[0]
                for val in values[1:]:
                    result = self.OPERATORS[op_type](result, val)
                return result
                
        raise ValueError(f"Unsupported expression node: {type(node).__name__}")

    def _get_full_name(self, node: ast.AST) -> str:
        """Reconstruct full name from Attribute/Name nodes"""
        if isinstance(node, ast.Name):
            return node.id
        elif isinstance(node, ast.Attribute):
            return f"{self._get_full_name(node.value)}.{node.attr}"
        raise ValueError("Invalid attribute access")

    def _get_value(self, name: str) -> Any:
        """Get value from context"""
        # Support nested dictionary access via dot notation in keys
        if name in self.context:
            return self.context[name]
            
        # Also support "param" if context has it
        parts = name.split('.')
        value = self.context
        try:
            for part in parts:
                if isinstance(value, dict):
                    value = value.get(part)
                else:
                    return None
            return value
        except:
            return None


class CustomRule(ValidationRule):
    """Rule defined by user configuration"""
    
    def __init__(self, definition: Dict[str, Any]):
        """Initialize from dictionary definition"""
        super().__init__(
            name=definition.get('name', 'CustomRule'),
            description=definition.get('description', '')
        )
        self.target_container = definition.get('target_container')  # Regex or exact name
        self.check_expression = definition.get('check')
        self.message = definition.get('message', 'Validation failed')
        self.severity = ValidationSeverity(definition.get('severity', 'error').lower())
        
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration) -> ValidationResult:
        result = ValidationResult()
        
        # Iterate over all containers
        for container in configuration.containers:
            self._validate_container_recursive(container, result)
            
        return result
        
    def _validate_container_recursive(self, container: EcucContainerValue, result: ValidationResult):
        """Recursively validate containers"""
        # Check if this container matches the target
        if self._matches_target(container):
            self._evaluate_rule(container, result)
            
        # Recurse
        for sub in container.sub_containers:
            self._validate_container_recursive(sub, result)
            
    def _matches_target(self, container: EcucContainerValue) -> bool:
        """Check if container matches target definition"""
        if not self.target_container:
            return True  # Applies to all? Or maybe none? Let's say all for now, or maybe require target
            
        # Simple exact match on definition short name (last part of ref)
        def_name = container.definition_ref.split('/')[-1]
        
        # Support wildcard *
        if self.target_container == '*':
            return True
            
        return def_name == self.target_container
        
    def _evaluate_rule(self, container: EcucContainerValue, result: ValidationResult):
        """Evaluate the rule against the container"""
        # Build context from container parameters
        context = {}
        for name, param in container.parameter_values.items():
            context[name] = param.value
            
        # Add container metadata
        context['__name__'] = container.short_name
        context['__path__'] = container.get_path()
        
        evaluator = RuleEvaluator(context)
        try:
            # Rule passes if expression evaluates to True
            if not evaluator.evaluate(self.check_expression):
                result.add_message(self._create_message(container))
        except Exception as e:
            # Evaluation error (e.g. missing parameter)
            # We treat this as a failure or ignore? 
            # If a param is missing, maybe the rule doesn't apply?
            # Or maybe it's an error. Let's report it as info/warning for debugging
            pass

    def _create_message(self, container: EcucContainerValue) -> Any:
        """Create validation message"""
        if self.severity == ValidationSeverity.ERROR:
            return self._create_error(self.message, container_path=container.get_path())
        elif self.severity == ValidationSeverity.WARNING:
            return self._create_warning(self.message, container_path=container.get_path())
        else:
            return self._create_info(self.message, container_path=container.get_path())


class RuleLoader:
    """Loads rules from files"""
    
    @staticmethod
    def load_from_file(file_path: Path) -> List[CustomRule]:
        """Load rules from JSON file"""
        with open(file_path, 'r', encoding='utf-8') as f:
            data = json.load(f)
            
        rules = []
        if isinstance(data, list):
            for rule_def in data:
                try:
                    rules.append(CustomRule(rule_def))
                except Exception as e:
                    print(f"Failed to load rule: {e}")
        elif isinstance(data, dict):
             # Single rule or wrapper
             if 'rules' in data:
                 for rule_def in data['rules']:
                     rules.append(CustomRule(rule_def))
             else:
                 rules.append(CustomRule(data))
                 
        return rules

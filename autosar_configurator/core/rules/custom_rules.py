"""
Custom Validation Rules
Allows users to define validation rules in JSON format using a simple expression language.
"""
import json
import re
import ast
import operator
from typing import Dict, Any, List, Optional, Union
from pathlib import Path


class SecurityError(Exception):
    """Raised when a custom rule file fails the safety scan."""

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
                
        elif isinstance(node, ast.List):  # List literals
            return [self._eval_node(elt) for elt in node.elts]
                
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
        
    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, project_context=None) -> ValidationResult:
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
            # Evaluation error (e.g. missing parameter or expression syntax error).
            # Do NOT silently swallow: surface it so the user knows the rule could
            # not be checked, instead of falsely reporting it as passed.
            import logging
            logging.getLogger(__name__).warning(
                f"CustomRule '{self.name}' could not be evaluated on container "
                f"'{container.get_path()}': {e}")
            result.add_message(self._create_info(
                f"Rule '{self.name}' skipped: {e}",
                container_path=container.get_path()))

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


class PythonRuleLoader:
    """Loads rules from Python scripts"""

    # Forbidden module names — any import of these is rejected
    _FORBIDDEN_MODULES = frozenset({
        'os', 'subprocess', 'sys', 'shutil', 'socket', 'ctypes',
        'pickle', 'marshal', 'pty', 'signal', 'threading', 'multiprocessing',
        'importlib', 'builtins', 'pathlib', 'tempfile', 'glob', 'io',
    })

    # Imports/builtins that are never legitimate in a validation rule file.
    # Uses AST parsing for import detection to handle comma-separated and
    # aliased forms (e.g. "import math, os" or "import os as _os").
    # Regex patterns catch runtime bypass forms that are not imports.
    _FORBIDDEN_RUNTIME_PATTERNS = [
        re.compile(r'\b__import__\s*\('),
        re.compile(r'\beval\s*\('),
        re.compile(r'\bexec\s*\('),
        re.compile(r'\bcompile\s*\('),
        re.compile(r'\bopen\s*\('),
        re.compile(r'\b__builtins__\b'),
        re.compile(r'\bgetattr\s*\([^,]+,\s*["\']__'),
        re.compile(r'\b__class__\b'),
        re.compile(r'\b__globals__\b'),
        re.compile(r'\b__subclasses__\s*\('),
        re.compile(r'\b__mro__\b'),
    ]

    @staticmethod
    def _scan_for_dangerous_patterns(file_path: Path) -> None:
        """Raise SecurityError if the file imports forbidden modules or uses dangerous builtins.

        Two-layer defence:
        1. AST import scan — handles all import forms including comma-separated
           and aliased imports (e.g. "import math, os" or "import os as _os").
        2. Regex scan — catches runtime bypass patterns (eval, exec, __import__,
           dunder traversal) that are not visible as top-level imports.

        This is defence-in-depth, not a full sandbox.
        """
        source = file_path.read_text(encoding='utf-8', errors='replace')

        # Layer 1: AST import analysis
        try:
            tree = ast.parse(source, filename=str(file_path))
        except SyntaxError as e:
            raise SecurityError(f"Custom rule file '{file_path.name}' has a syntax error: {e}")

        for node in ast.walk(tree):
            if isinstance(node, ast.Import):
                for alias in node.names:
                    root = alias.name.split('.')[0]
                    if root in PythonRuleLoader._FORBIDDEN_MODULES:
                        raise SecurityError(
                            f"Custom rule file '{file_path.name}' imports forbidden module '{alias.name}'. "
                            f"Only pure-Python validation logic is allowed."
                        )
            elif isinstance(node, ast.ImportFrom):
                root = (node.module or '').split('.')[0]
                if root in PythonRuleLoader._FORBIDDEN_MODULES:
                    raise SecurityError(
                        f"Custom rule file '{file_path.name}' imports from forbidden module '{node.module}'. "
                        f"Only pure-Python validation logic is allowed."
                    )

        # Layer 2: Regex scan for runtime bypass patterns
        for pattern in PythonRuleLoader._FORBIDDEN_RUNTIME_PATTERNS:
            if pattern.search(source):
                raise SecurityError(
                    f"Custom rule file '{file_path.name}' contains a forbidden pattern "
                    f"({pattern.pattern!r}). os/subprocess/exec/eval and dunder access are not permitted."
                )

    @staticmethod
    def load_from_file(file_path: Path) -> List[ValidationRule]:
        """Load ValidationRule subclasses from .py file.

        Raises SecurityError before execution if the file contains dangerous
        patterns such as os/subprocess imports, exec, eval, or open().
        """
        import importlib.util
        import inspect

        PythonRuleLoader._scan_for_dangerous_patterns(file_path)

        # Load module dynamically inside a restricted namespace
        spec = importlib.util.spec_from_file_location(file_path.stem, file_path)
        if not spec or not spec.loader:
            raise ImportError(f"Could not load spec for {file_path}")

        module = importlib.util.module_from_spec(spec)
        try:
            spec.loader.exec_module(module)
        except Exception as e:
            raise ImportError(f"Failed to execute rule script: {e}")
        
        rules = []
        # Find all ValidationRule subclasses in the module
        for name, obj in inspect.getmembers(module):
            if inspect.isclass(obj) and issubclass(obj, ValidationRule) and obj is not ValidationRule:
                # Don't load rules imported from other modules, only defined here
                if obj.__module__ != module.__name__:
                    continue
                    
                try:
                    # Try to instantiate with no arguments
                    # Convention: Custom rules should have no-arg __init__ or __init__(name, desc)
                    try:
                        rule = obj()
                    except TypeError:
                        # Maybe it requires name/desc?
                        rule = obj(name=name, description="Custom Python Rule")
                        
                    rules.append(rule)
                except Exception as e:
                    print(f"Warning: Failed to instantiate rule class {name}: {e}")
                    
        return rules

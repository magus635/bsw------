"""
Generic Resource Mapper
Universal mapping engine that uses rules to map chip resources to AUTOSAR configuration
"""
from dataclasses import dataclass
from enum import Enum
from typing import Dict, List, Any, Optional
import re
import ast
import operator as _op

from .generic_resource import ChipDefinition, GenericResourceDef
from .mapping_rule import (
    MappingRule, ContainerRule, ParameterMapping,
    MappingRuleLoader, get_default_rule_loader
)

# ---------------------------------------------------------------------------
# AST-based safe expression evaluator (replaces eval() in _evaluate_condition)
# Only allows: literals, arithmetic (+−×÷), comparisons, boolean ops (and/or/not).
# Function calls, attribute access, imports, and name lookups are all rejected.
# ---------------------------------------------------------------------------
_SAFE_BINOPS = {
    ast.Add: _op.add, ast.Sub: _op.sub,
    ast.Mult: _op.mul, ast.Div: _op.truediv, ast.FloorDiv: _op.floordiv,
    ast.Mod: _op.mod,
}
_SAFE_CMPOPS = {
    ast.Eq: _op.eq, ast.NotEq: _op.ne,
    ast.Lt: _op.lt, ast.LtE: _op.le,
    ast.Gt: _op.gt, ast.GtE: _op.ge,
}


def _safe_ast_eval(expr: str) -> Any:
    """Evaluate a pure-literal arithmetic/comparison expression via AST (no exec/eval)."""
    def _eval(node):
        if isinstance(node, ast.Expression):
            return _eval(node.body)
        if isinstance(node, ast.Constant):
            return node.value
        if isinstance(node, ast.UnaryOp) and isinstance(node.op, ast.Not):
            return not _eval(node.operand)
        if isinstance(node, ast.UnaryOp) and isinstance(node.op, ast.USub):
            return -_eval(node.operand)
        if isinstance(node, ast.BoolOp):
            values = [_eval(v) for v in node.values]
            if isinstance(node.op, ast.And):
                result = values[0]
                for v in values[1:]:
                    result = result and v
                return result
            if isinstance(node.op, ast.Or):
                result = values[0]
                for v in values[1:]:
                    result = result or v
                return result
        if isinstance(node, ast.BinOp):
            fn = _SAFE_BINOPS.get(type(node.op))
            if fn is None:
                raise ValueError(f"Unsupported operator: {type(node.op).__name__}")
            return fn(_eval(node.left), _eval(node.right))
        if isinstance(node, ast.Compare):
            left = _eval(node.left)
            for cmp_op, comparator in zip(node.ops, node.comparators):
                fn = _SAFE_CMPOPS.get(type(cmp_op))
                if fn is None:
                    raise ValueError(f"Unsupported comparator: {type(cmp_op).__name__}")
                right = _eval(comparator)
                if not fn(left, right):
                    return False
                left = right
            return True
        raise ValueError(f"Unsupported AST node: {type(node).__name__}")

    tree = ast.parse(expr, mode='eval')
    return _eval(tree)


class MappingActionType(Enum):
    """Type of mapping action"""
    CREATE_CONTAINER = "create_container"
    SET_PARAMETER = "set_parameter"
    SET_REFERENCE = "set_reference"


@dataclass
class MappingAction:
    """A single hardware mapping action"""
    action_type: MappingActionType
    module: str
    container_path: str
    parameter_name: Optional[str] = None
    value: Any = None
    description: str = ""

    def __str__(self):
        if self.action_type == MappingActionType.CREATE_CONTAINER:
            return f"[CREATE] {self.container_path}"
        elif self.action_type == MappingActionType.SET_PARAMETER:
            return f"  [SET] {self.parameter_name} = {self.value}"
        else:
            return f"  [REF] {self.parameter_name} -> {self.value}"


@dataclass
class MappingResult:
    """Result of applying mapping actions"""
    applied: int = 0
    skipped: int = 0
    failed: int = 0

    def __str__(self):
        parts = [f"applied={self.applied}"]
        if self.skipped:
            parts.append(f"skipped={self.skipped} (not implemented)")
        if self.failed:
            parts.append(f"failed={self.failed}")
        return ", ".join(parts)

    @property
    def total(self):
        return self.applied + self.skipped + self.failed


class ExpressionEvaluator:
    """Evaluates expressions in mapping rules"""

    def __init__(self, context: Dict[str, Any]):
        """Initialize with a context dictionary

        Args:
            context: Variables available in expressions (resource, user, chip, index, etc.)
        """
        self.context = context

    def evaluate(self, expression: str) -> Any:
        """Evaluate an expression and return the result"""
        if expression is None:
            return None

        # Handle simple variable references
        if expression.startswith('resource.') or expression.startswith('user.') or \
           expression.startswith('chip.') or expression in ('index', 'index1'):
            return self._resolve_path(expression)

        # Handle template strings with {var} placeholders
        if '{' in expression:
            return self._expand_template(expression)

        # Handle Python-like expressions (simple arithmetic, comparisons)
        try:
            return self._eval_expression(expression)
        except Exception:
            return expression

    def evaluate_condition(self, condition: str) -> bool:
        """Evaluate a condition expression and return boolean"""
        if condition is None:
            return True

        try:
            result = self._eval_expression(condition)
            return bool(result)
        except Exception:
            return False

    def _resolve_path(self, path: str) -> Any:
        """Resolve a dotted path to a value"""
        parts = path.split('.')
        value = self.context

        for part in parts:
            if isinstance(value, dict):
                value = value.get(part)
            elif hasattr(value, part):
                value = getattr(value, part)
            elif hasattr(value, 'get_property'):
                value = value.get_property(part)
            else:
                return None

            if value is None:
                return None

        return value

    def _expand_template(self, template: str) -> str:
        """Expand a template string with variable placeholders"""
        def replace_var(match):
            var_path = match.group(1)
            value = self._resolve_path(var_path)
            return str(value) if value is not None else ''

        # Replace {var.path} with actual values
        result = re.sub(r'\{([^}]+)\}', replace_var, template)
        return result

    def _eval_expression(self, expression: str) -> Any:
        """Evaluate a simple expression"""
        # Build a safe evaluation context
        eval_context = {}

        # Add context values
        for key, value in self.context.items():
            if isinstance(value, GenericResourceDef):
                eval_context[key] = {
                    'resource_id': value.resource_id,
                    'resource_type': value.resource_type,
                    'display_name': value.display_name,
                    'properties': value.properties
                }
            elif isinstance(value, dict):
                eval_context[key] = value
            else:
                eval_context[key] = value

        # Flatten for direct access (e.g., "resource.properties.controller_id")
        def get_nested(obj, path):
            parts = path.split('.')
            for part in parts:
                if isinstance(obj, dict):
                    obj = obj.get(part)
                elif hasattr(obj, part):
                    obj = getattr(obj, part)
                else:
                    return None
                if obj is None:
                    return None
            return obj

        # Replace dotted paths with their values in the expression
        def replace_path(match):
            path = match.group(0)
            value = get_nested(eval_context, path)
            if value is None:
                return 'None'
            elif isinstance(value, str):
                # Use repr() so embedded quotes/backslashes cannot alter parse logic.
                return repr(value)
            elif isinstance(value, bool):
                return 'True' if value else 'False'
            else:
                return str(value)

        # Replace paths like resource.properties.controller_id
        modified_expr = re.sub(r'[a-zA-Z_][a-zA-Z0-9_]*(?:\.[a-zA-Z_][a-zA-Z0-9_]*)+', replace_path, expression)

        # Replace simple variable names.  Use repr() for strings so that
        # values containing quotes, backslashes, etc. cannot alter parse logic.
        for key, value in eval_context.items():
            if key in modified_expr and not isinstance(value, (dict, list)):
                if isinstance(value, str):
                    modified_expr = re.sub(rf'\b{key}\b', repr(value), modified_expr)
                elif isinstance(value, bool):
                    modified_expr = re.sub(rf'\b{key}\b', 'True' if value else 'False', modified_expr)
                else:
                    modified_expr = re.sub(rf'\b{key}\b', str(value), modified_expr)

        try:
            return _safe_ast_eval(modified_expr)
        except Exception:
            # Unsupported or invalid expression — treat as falsy rather than
            # returning the raw string (which would be truthy and bypass checks).
            return False


class GenericResourceMapper:
    """Generic resource mapper that uses rules to generate mapping actions"""

    def __init__(self, chip: ChipDefinition, rule_loader: Optional[MappingRuleLoader] = None):
        """Initialize the mapper

        Args:
            chip: Chip definition with resources
            rule_loader: Rule loader instance (uses default if not provided)
        """
        self.chip = chip
        self.rule_loader = rule_loader or get_default_rule_loader()

    def get_available_modules(self) -> List[str]:
        """Get list of modules that can be configured for this chip

        Returns modules that have both:
        - A mapping rule defined
        - Corresponding resources in the chip
        """
        available = []
        for module in self.rule_loader.get_all_modules():
            rule = self.rule_loader.get_rule(module)
            if rule and self.chip.get_resource_count(rule.resource_type) > 0:
                available.append(module)
        return sorted(available)

    def get_module_resource_info(self, module: str) -> Dict[str, Any]:
        """Get resource information for a module

        Returns:
            Dict with resource_type and count
        """
        rule = self.rule_loader.get_rule(module)
        if not rule:
            return {'resource_type': None, 'count': 0, 'resources': []}

        resources = self.chip.get_resources(rule.resource_type)
        return {
            'resource_type': rule.resource_type,
            'count': len(resources),
            'resources': resources
        }

    def generate_mapping(self, module: str, user_config: Dict[str, Any] = None) -> List[MappingAction]:
        """Generate mapping actions for a module

        Args:
            module: Module name (e.g., "Can", "Port")
            user_config: User configuration dict {resource_id: {param: value, ...}}

        Returns:
            List of MappingAction instances
        """
        rule = self.rule_loader.get_rule(module)
        if not rule:
            return []

        user_config = user_config or {}
        actions = []

        # Get resources for this rule
        resources = self.chip.get_resources(rule.resource_type)

        # Generate actions for each resource
        for index, resource in enumerate(resources):
            resource_config = user_config.get(resource.resource_id, {})

            # Check if resource is enabled (default to True)
            if not resource_config.get('enable', True):
                continue

            # Build evaluation context
            context = {
                'resource': resource,
                'user': resource_config,
                'chip': self.chip,
                'index': index,
                'index1': index + 1,
            }

            # Generate actions from container rules
            for container_rule in rule.containers:
                container_actions = self._generate_container_actions(
                    module, container_rule, context
                )
                actions.extend(container_actions)

        return actions

    def _generate_container_actions(
        self,
        module: str,
        container_rule: ContainerRule,
        context: Dict[str, Any]
    ) -> List[MappingAction]:
        """Generate actions for a container rule"""
        actions = []
        evaluator = ExpressionEvaluator(context)

        # Check condition
        if container_rule.condition and not evaluator.evaluate_condition(container_rule.condition):
            return actions

        # Handle iteration
        if container_rule.iterate:
            iterate_value = evaluator.evaluate(container_rule.iterate)
            if iterate_value is None:
                return actions

            for item_index, item in enumerate(iterate_value):
                item_context = context.copy()
                item_context[container_rule.iterate_var] = item
                item_context['item_index'] = item_index

                item_actions = self._generate_single_container_actions(
                    module, container_rule, item_context
                )
                actions.extend(item_actions)
        else:
            actions = self._generate_single_container_actions(module, container_rule, context)

        return actions

    def _generate_single_container_actions(
        self,
        module: str,
        container_rule: ContainerRule,
        context: Dict[str, Any]
    ) -> List[MappingAction]:
        """Generate actions for a single container (no iteration)"""
        actions = []
        evaluator = ExpressionEvaluator(context)

        # Expand container path template
        container_path = evaluator.evaluate(container_rule.path_template)
        if not container_path:
            return actions

        # Create container action
        actions.append(MappingAction(
            action_type=MappingActionType.CREATE_CONTAINER,
            module=module,
            container_path=container_path,
            description=f"Create {container_path}"
        ))

        # Generate parameter actions
        for param in container_rule.parameters:
            param_action = self._generate_parameter_action(
                module, container_path, param, evaluator
            )
            if param_action:
                actions.append(param_action)

        # Generate sub-container actions
        for sub_rule in container_rule.sub_containers:
            sub_context = context.copy()
            sub_context['parent_path'] = container_path

            sub_actions = self._generate_container_actions(module, sub_rule, sub_context)

            # Adjust sub-container paths to be relative to parent
            for action in sub_actions:
                if action.container_path and not action.container_path.startswith(container_path):
                    action.container_path = f"{container_path}/{action.container_path}"

            actions.extend(sub_actions)

        return actions

    def _generate_parameter_action(
        self,
        module: str,
        container_path: str,
        param: ParameterMapping,
        evaluator: ExpressionEvaluator
    ) -> Optional[MappingAction]:
        """Generate action for a single parameter"""
        # Check condition
        if param.condition and not evaluator.evaluate_condition(param.condition):
            return None

        # Determine value
        value = None

        if param.source:
            value = evaluator.evaluate(param.source)

        if param.transform:
            value = evaluator.evaluate(param.transform)

        if value is None and param.default is not None:
            if isinstance(param.default, str) and ('.' in param.default or '{' in param.default):
                value = evaluator.evaluate(param.default)
            else:
                value = param.default

        # Check user override
        user = evaluator.context.get('user', {})
        if param.name in user:
            value = user[param.name]

        if value is None:
            return None

        return MappingAction(
            action_type=MappingActionType.SET_PARAMETER,
            module=module,
            container_path=container_path,
            parameter_name=param.name,
            value=value,
            description=f"Set {param.name} = {value}"
        )

    def apply_actions(self, actions: List[MappingAction], config_manager) -> MappingResult:
        """Apply mapping actions to a configuration manager"""
        result = MappingResult()

        for action in actions:
            try:
                # Skip actions targeted at a different module
                if action.module and hasattr(config_manager, 'module_def'):
                    if config_manager.module_def.short_name != action.module:
                        result.skipped += 1
                        continue

                if action.action_type == MappingActionType.CREATE_CONTAINER:
                    container_def, parent = self._resolve_create_target(
                        action.container_path, config_manager)
                    if container_def is None:
                        result.skipped += 1
                        continue
                    instance_name = action.container_path.split('/')[-1]
                    # Skip if already exists
                    siblings = (parent.sub_containers if parent is not None
                                else config_manager.configuration.containers)
                    if any(c.short_name == instance_name for c in siblings):
                        result.applied += 1  # idempotent — container already there
                        continue
                    config_manager.create_container_instance(
                        container_def, parent=parent, instance_name=instance_name)
                    result.applied += 1

                elif action.action_type == MappingActionType.SET_PARAMETER:
                    container = self._find_container_instance(
                        action.container_path, config_manager)
                    if container is None:
                        result.skipped += 1
                        continue
                    config_manager.set_parameter_value(
                        container, action.parameter_name, action.value)
                    result.applied += 1

                elif action.action_type == MappingActionType.SET_REFERENCE:
                    container = self._find_container_instance(
                        action.container_path, config_manager)
                    if container is None:
                        result.skipped += 1
                        continue
                    container_def = config_manager.get_container_def(container.definition_ref)
                    ref_def_ref = ""
                    if container_def and action.parameter_name in container_def.references:
                        ref_def_ref = container_def.references[action.parameter_name].definition_ref
                    container.set_reference_value(
                        action.parameter_name, action.value, ref_def_ref)
                    result.applied += 1

            except Exception as e:
                print(f"Warning: Failed to apply action {action}: {e}")
                result.failed += 1

        return result

    def _find_container_instance(self, container_path: str, config_manager):
        """Find container instance by DEF-based path (e.g. 'IntcConfig/IntcSource_IRQ0')."""
        parts = container_path.split('/')
        # Match top-level container by definition short_name
        top_name = parts[0]
        current = None
        for c in config_manager.configuration.containers:
            def_tail = c.definition_ref.split('/')[-1] if c.definition_ref else ''
            if c.short_name == top_name or def_tail == top_name:
                current = c
                break
        if current is None:
            return None
        for part in parts[1:]:
            current = next((s for s in current.sub_containers if s.short_name == part), None)
            if current is None:
                return None
        return current

    def _resolve_create_target(self, container_path: str, config_manager):
        """Return (container_def_for_new_container, parent_instance_or_None)."""
        parts = container_path.split('/')
        if len(parts) == 1:
            cdef = config_manager.module_def.get_container_def(parts[0])
            return cdef, None
        parent = self._find_container_instance('/'.join(parts[:-1]), config_manager)
        if parent is None:
            return None, None
        parent_def = config_manager.get_container_def(parent.definition_ref)
        if parent_def is None:
            return None, None
        new_name = parts[-1]
        # Try exact match first, then strip trailing _suffix (instance names often differ from def names)
        sub_def = parent_def.sub_containers.get(new_name)
        if sub_def is None:
            base = new_name.rsplit('_', 1)[0] if '_' in new_name else new_name
            sub_def = parent_def.sub_containers.get(base)
        return sub_def, parent

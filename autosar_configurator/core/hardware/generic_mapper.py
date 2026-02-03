"""
Generic Resource Mapper
Universal mapping engine that uses rules to map chip resources to AUTOSAR configuration
"""
from dataclasses import dataclass
from enum import Enum
from typing import Dict, List, Any, Optional
import re

from .generic_resource import ChipDefinition, GenericResourceDef
from .mapping_rule import (
    MappingRule, ContainerRule, ParameterMapping,
    MappingRuleLoader, get_default_rule_loader
)


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
                return f'"{value}"'
            elif isinstance(value, bool):
                return 'True' if value else 'False'
            else:
                return str(value)

        # Replace paths like resource.properties.controller_id
        modified_expr = re.sub(r'[a-zA-Z_][a-zA-Z0-9_]*(?:\.[a-zA-Z_][a-zA-Z0-9_]*)+', replace_path, expression)

        # Replace simple variable names
        for key, value in eval_context.items():
            if key in modified_expr and not isinstance(value, (dict, list)):
                if isinstance(value, str):
                    modified_expr = re.sub(rf'\b{key}\b', f'"{value}"', modified_expr)
                elif isinstance(value, bool):
                    modified_expr = re.sub(rf'\b{key}\b', 'True' if value else 'False', modified_expr)
                else:
                    modified_expr = re.sub(rf'\b{key}\b', str(value), modified_expr)

        # Evaluate with restricted builtins
        safe_builtins = {
            'True': True, 'False': False, 'None': None,
            'len': len, 'range': range, 'str': str, 'int': int, 'float': float,
            'min': min, 'max': max, 'abs': abs, 'sum': sum,
            'and': lambda a, b: a and b,
            'or': lambda a, b: a or b,
            'not': lambda a: not a,
        }

        try:
            return eval(modified_expr, {"__builtins__": safe_builtins}, {})
        except Exception:
            return expression


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

    def apply_actions(self, actions: List[MappingAction], config_manager) -> int:
        """Apply mapping actions to a configuration manager

        Args:
            actions: List of mapping actions to apply
            config_manager: Configuration manager instance

        Returns:
            Number of successfully applied actions
        """
        applied = 0

        for action in actions:
            try:
                if action.action_type == MappingActionType.CREATE_CONTAINER:
                    # TODO: Implement container creation
                    # config_manager.create_container(action.module, action.container_path)
                    applied += 1

                elif action.action_type == MappingActionType.SET_PARAMETER:
                    # TODO: Implement parameter setting
                    # config_manager.set_parameter(
                    #     action.module, action.container_path,
                    #     action.parameter_name, action.value
                    # )
                    applied += 1

                elif action.action_type == MappingActionType.SET_REFERENCE:
                    # TODO: Implement reference setting
                    applied += 1

            except Exception as e:
                print(f"Warning: Failed to apply action {action}: {e}")

        return applied

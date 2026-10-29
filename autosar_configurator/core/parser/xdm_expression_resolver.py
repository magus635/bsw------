"""
XDM Expression Resolver

Resolves ecu:list('X.Y') and ecu:get('X.Y') expressions from XDM files
using data from .properties files (ChipConstraints).

Does NOT implement full XPath -- only the subset used in XDM metadata:
  - ecu:list('Module.Param')       -> List[str]
  - ecu:get('Module.Param')        -> Any
  - num:i(count(ecu:list(...)))    -> int
  - ecu:list('...')[N]             -> str (1-indexed)
"""

import re
from typing import Any, Dict, List, Optional

from ..model.definition_model import EcucParameterType


def _strip_outer_parens(expr: str) -> str:
    """'(num:i(count(...)))' -> 'num:i(count(...))': only parentheses enclosing the whole text."""
    while expr.startswith("(") and expr.endswith(")"):
        depth = 0
        for i, ch in enumerate(expr):
            depth += ch == "("
            depth -= ch == ")"
            if depth == 0 and i < len(expr) - 1:
                return expr            # the first '(' closes before the end: not enclosing
        expr = expr[1:-1].strip()
    return expr


def typed_value(value: Any, param_type: EcucParameterType) -> Any:
    """A resolved default converted to the parameter's type; the value as it is when it does not convert."""
    if isinstance(value, (list, dict)) or value is None:
        return value
    try:
        if param_type == EcucParameterType.INTEGER:
            if isinstance(value, (bool, int)):
                return int(value)
            text = str(value).strip()
            return int(text) if text.lstrip("+-").isdigit() else int(text, 0)
        if param_type == EcucParameterType.FLOAT:
            return float(value)
        if param_type == EcucParameterType.BOOLEAN:
            return value if isinstance(value, bool) else str(value).strip().lower() in ("true", "1", "yes")
    except (TypeError, ValueError):
        return value
    return str(value) if isinstance(value, (int, float)) and not isinstance(value, bool) else value


def upper_limit(resolved: Any) -> int:
    """A resolved MAX as an upper multiplicity; -1 (unbounded) when it is not a positive whole number."""
    if isinstance(resolved, bool):
        return -1
    if isinstance(resolved, str) and resolved.strip().isdigit():
        resolved = int(resolved.strip())
    return resolved if isinstance(resolved, int) and resolved > 0 else -1


class XdmExpressionResolver:
    """Resolves XDM dynamic expressions using .properties constraint data."""

    def __init__(self, constraints: Dict[str, Any] = None):
        """
        Args:
            constraints: flat dict from ChipConstraints.constraints
                         e.g., {'Adc.HwUnitId': ['SARADC0','SARADC1',...], ...}
        """
        self._constraints = constraints or {}

    def set_constraints(self, constraints: Dict[str, Any]):
        """Update constraint data (e.g., when chip selection changes)."""
        self._constraints = constraints

    def _lookup(self, path: str) -> Any:
        """Value of a key, matched like ecu:get(): exactly first, then ignoring case."""
        value = self._constraints.get(path)
        if value is None:
            lowered = path.lower()
            for key, candidate in self._constraints.items():
                if isinstance(key, str) and key.lower() == lowered:
                    return candidate
        return value

    def resolve_ecu_list(self, path: str) -> List[str]:
        """Resolve ecu:list('path') -> list of strings."""
        value = self._lookup(path)
        if isinstance(value, list):
            return [str(v).strip() for v in value]
        if isinstance(value, str):
            # Properties parser may return comma-separated string
            return [v.strip() for v in value.split(',') if v.strip()]
        if value is not None:
            return [str(value)]
        return []

    def resolve_ecu_get(self, path: str) -> Any:
        """Resolve ecu:get('path') -> value."""
        return self._lookup(path)

    def resolve_expression(self, expr: str) -> Any:
        """
        Resolve a complete XDM expression string.

        Supported patterns:
          - "ecu:list('X.Y')"                    -> List[str]
          - "ecu:list('X.Y')[N]"                 -> str (1-indexed)
          - "ecu:get('X.Y')"                     -> Any
          - "num:i(count(ecu:list('X.Y')))"      -> int
          - Anything else                         -> None (unresolvable)
        """
        if not expr:
            return None

        expr = _strip_outer_parens(expr.strip())

        # Pattern 1: num:i(count(ecu:list('X.Y')))
        m = re.match(
            r"num:i\s*\(\s*count\s*\(\s*ecu:list\s*\(\s*['\"]([^'\"]+)['\"]\s*\)\s*\)\s*\)",
            expr
        )
        if m:
            values = self.resolve_ecu_list(m.group(1))
            return len(values)

        # Pattern 2: ecu:list('X.Y')[N]
        m = re.match(
            r"ecu:list\s*\(\s*['\"]([^'\"]+)['\"]\s*\)\s*\[(\d+)\]",
            expr
        )
        if m:
            path, index = m.group(1), int(m.group(2))
            values = self.resolve_ecu_list(path)
            # XPath is 1-indexed
            if 0 < index <= len(values):
                return values[index - 1]
            return None

        # Pattern 3: ecu:list('X.Y')
        m = re.match(r"ecu:list\s*\(\s*['\"]([^'\"]+)['\"]\s*\)\s*$", expr)
        if m:
            return self.resolve_ecu_list(m.group(1))

        # Pattern 4: ecu:get('X.Y')
        m = re.match(r"ecu:get\s*\(\s*['\"]([^'\"]+)['\"]\s*\)\s*$", expr)
        if m:
            return self.resolve_ecu_get(m.group(1))

        # Unrecognized expression
        return None

    def extract_ecu_path(self, expr: str) -> Optional[str]:
        """Extract the ecu:list/ecu:get path from an expression.

        Returns:
            The path string (e.g., 'Adc.HwUnitId') or None
        """
        if not expr:
            return None
        # Handle simple ecu:list('path')
        m = re.search(r"ecu:(?:list|get)\s*\(\s*['\"]([^'\"]+)['\"]\s*\)", expr)
        if m:
            return m.group(1)
        
        # Handle nested like ecu:list(text:concat('path', ...))
        m = re.search(r"ecu:(?:list|get)\s*\(\s*text:concat\s*\(\s*['\"]([^'\"]+)['\"]", expr)
        return m.group(1) if m else None


def _walk_containers(containers):
    for container in containers:
        yield container
        yield from _walk_containers(getattr(container, "sub_containers", {}).values())


def apply_chip_expressions(module_def, resources: Dict[str, Any]) -> int:
    """Evaluate the chip expressions of ``module_def`` against ``resources``, in place.

    Defaults (converted to the parameter type), enumeration ranges and maximum
    counts follow the given ECU resources; an expression that cannot be
    evaluated leaves the static default, the static options and no upper limit.
    Configured values are not touched.

    Returns:
        Number of defaults, ranges and maximum counts that changed
    """
    resolver = XdmExpressionResolver(resources or {})
    changed = 0
    containers = list(_walk_containers(getattr(module_def, "containers", {}).values()))
    params = list(getattr(module_def, "parameters", {}).values())
    for container in containers:
        params.extend(getattr(container, "parameters", {}).values())
        expr = getattr(container, "upper_multiplicity_expr", None)
        if expr:
            upper = upper_limit(resolver.resolve_expression(expr))
            if upper != container.upper_multiplicity:
                container.upper_multiplicity = upper
                changed += 1
    for param in params:
        if param.default_expr:
            resolved = resolver.resolve_expression(param.default_expr)
            value = typed_value(resolved, param.param_type) if resolved is not None else param.static_default
            if value != param.default_value:
                param.default_value = value
                changed += 1
        if param.range_expr and param.param_type == EcucParameterType.ENUMERATION:
            resolved = resolver.resolve_expression(param.range_expr)
            literals = resolved if isinstance(resolved, list) and resolved else list(param.static_literals or [])
            if literals != list(param.literals or []):
                param.literals = literals
                changed += 1
    return changed

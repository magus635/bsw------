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

    def resolve_ecu_list(self, path: str) -> List[str]:
        """Resolve ecu:list('path') -> list of strings."""
        value = self._constraints.get(path)
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
        return self._constraints.get(path)

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

        expr = expr.strip()

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

"""
EB tresos value semantics for the template engine.

EB evaluates template expressions with JXPath (XPath 1.0) and its own function library:

- XPath numbers are Java Doubles: numeric literals, arithmetic, count(), string-length() ...
  The integer functions (num:i, the *toint conversions, bit:*) return Java Longs.
  The engine uses ``float`` for Double and ``int`` for Long.
- Expression output ([!"expr"!]) and [!VAR!] convert the value with Java toString():
  2.0, 1.0E8, true. Variables always hold strings.
- Configuration node values are strings (the text of the configuration), whatever the
  parameter type.
- Comparisons follow XPath 1.0 section 3.4 (node-sets, then booleans, numbers, strings).

See openspec/changes/align-eb-value-semantics/design.md.
"""
import math
from typing import Any, List


def is_node(value: Any) -> bool:
    return hasattr(value, 'node_type')


def format_double(value: float) -> str:
    """Java Double.toString(): 2.0, 0.5, 1.0E8, 4.0E-8, NaN, Infinity."""
    if math.isnan(value):
        return 'NaN'
    if math.isinf(value):
        return 'Infinity' if value > 0 else '-Infinity'
    if value == 0.0:
        return '-0.0' if math.copysign(1.0, value) < 0 else '0.0'
    abs_val = abs(value)
    sign = '-' if value < 0 else ''
    if abs_val >= 1e7 or abs_val < 1e-3:
        exp = int(math.floor(math.log10(abs_val)))
        mantissa = abs_val / (10.0 ** exp)
        if mantissa >= 10.0:            # log10 rounding at exact powers of ten
            mantissa /= 10.0
            exp += 1
        m_str = f"{mantissa:.15g}"
        if '.' not in m_str:
            m_str += '.0'
        else:
            m_str = m_str.rstrip('0')
            if m_str.endswith('.'):
                m_str += '0'
        return f"{sign}{m_str}E{exp}"
    s = repr(abs_val)
    if 'e' in s or 'E' in s:            # not expected in this range, keep Java-like
        s = f"{abs_val:.17g}"
    if '.' not in s:
        s += '.0'
    return sign + s


def node_text(node: Any) -> str:
    """String value of a configuration node, as EB's data model gives it."""
    if node.node_type == 'parameter':
        value = node.get_value()
        param_type = (getattr(node, 'param_type', '') or '').upper()
        if isinstance(value, bool) or 'BOOLEAN' in param_type:
            if value is None:
                return ''
            return 'true' if str(value).strip().lower() in ('1', 'true', 'yes', 'on') else 'false'
        return scalar_text(value)
    if node.node_type == 'reference':
        return '' if node.value is None else str(node.value)
    # containers / modules: a CHOICE container carries the chosen name as value
    if node.value is not None:
        return str(node.value)
    return node.short_name


def scalar_text(value: Any) -> str:
    """Java toString() of a scalar (None gives the empty string)."""
    if value is None:
        return ''
    if isinstance(value, bool):
        return 'true' if value else 'false'
    if isinstance(value, float):
        return format_double(value)
    return str(value)


def eb_string(value: Any) -> str:
    """Java toString() as used by [!"expr"!] and [!VAR!]: the first node of a node-set."""
    if isinstance(value, (list, tuple)):
        if not value:
            return ''
        value = value[0]
    if is_node(value):
        return node_text(value)
    return scalar_text(value)


def xpath_string(value: Any) -> str:
    """XPath 1.0 string(): an integral number has no fractional part (concat('a', 2.0) = 'a2')."""
    if isinstance(value, (list, tuple)):
        if not value:
            return ''
        value = value[0]
    if is_node(value):
        return node_text(value)
    if isinstance(value, bool):
        return 'true' if value else 'false'
    if isinstance(value, float):
        if math.isnan(value):
            return 'NaN'
        if math.isinf(value):
            return 'Infinity' if value > 0 else '-Infinity'
        if value == int(value):
            return str(int(value))
        return repr(value)
    return scalar_text(value)


def to_number(value: Any) -> float:
    """XPath 1.0 number(); NaN when the value is not a number."""
    if isinstance(value, (list, tuple)):
        if not value:
            return math.nan
        value = value[0]
    if is_node(value):
        value = node_text(value)
    if value is None:
        return math.nan
    if isinstance(value, bool):
        return 1.0 if value else 0.0
    if isinstance(value, (int, float)):
        return float(value)
    try:
        text = str(value).strip()
        if not text or text.lower() in ('nan', 'inf', '-inf', 'infinity', '-infinity'):
            return math.nan
        return float(text)
    except ValueError:
        return math.nan


def to_boolean(value: Any) -> bool:
    """XPath 1.0 boolean()."""
    if isinstance(value, bool):
        return value
    if value is None:
        return False
    if isinstance(value, (list, tuple)):
        return len(value) > 0
    if is_node(value):
        return True
    if isinstance(value, (int, float)):
        return not (value == 0 or (isinstance(value, float) and math.isnan(value)))
    return len(str(value)) > 0


def _is_node_set(value: Any) -> bool:
    """Node-sets: configuration nodes, lists (JXPath treats collections as node-sets), and
    None (an empty selection)."""
    return value is None or is_node(value) or isinstance(value, (list, tuple))


def _members(value: Any) -> List[Any]:
    if value is None:
        return []
    if isinstance(value, (list, tuple)):
        return list(value)
    return [value]


def _member_string(member: Any) -> str:
    return node_text(member) if is_node(member) else scalar_text(member)


def _relational(op: str, a: float, b: float) -> bool:
    if math.isnan(a) or math.isnan(b):
        return False
    if op == '<':
        return a < b
    if op == '>':
        return a > b
    if op == '<=':
        return a <= b
    return a >= b


def _equal_atoms(left: Any, right: Any) -> bool:
    """XPath 1.0 '=' for two values that are not node-sets."""
    if isinstance(left, bool) or isinstance(right, bool):
        return to_boolean(left) == to_boolean(right)
    if isinstance(left, (int, float)) or isinstance(right, (int, float)):
        a, b = to_number(left), to_number(right)
        return not (math.isnan(a) or math.isnan(b)) and a == b
    return scalar_text(left) == scalar_text(right)


def compare(op: str, left: Any, right: Any) -> bool:
    """XPath 1.0 comparison (=, !=, <, >, <=, >=) of two values.

    Values: configuration nodes or lists (node-sets), None (empty node-set), bool,
    int/float (number) and str (string).
    """
    if op == '==':
        op = '='
    left_set, right_set = _is_node_set(left), _is_node_set(right)

    if left_set and right_set:
        if op in ('=', '!='):
            rights = [_member_string(r) for r in _members(right)]
            for l in _members(left):
                ls = _member_string(l)
                for rs in rights:
                    if (ls == rs) == (op == '='):
                        return True
            return False
        rights = [to_number(_member_string(r)) for r in _members(right)]
        return any(_relational(op, to_number(_member_string(l)), r)
                   for l in _members(left) for r in rights)

    if left_set or right_set:
        node_set, other = (left, right) if left_set else (right, left)
        if isinstance(other, bool):
            # node-set and boolean: the node-set as a boolean (non-empty)
            as_bool = to_boolean(_members(node_set))
            if op == '=':
                return as_bool == other
            if op == '!=':
                return as_bool != other
            a, b = (as_bool, other) if left_set else (other, as_bool)
            return _relational(op, to_number(a), to_number(b))
        for member in _members(node_set):
            text = _member_string(member)
            if op in ('=', '!='):
                if isinstance(other, (int, float)):
                    n = to_number(text)
                    equal = not math.isnan(n) and n == float(other)
                else:
                    equal = text == scalar_text(other)
                if equal == (op == '='):
                    return True
            else:
                a, b = (to_number(text), to_number(other)) if left_set else (to_number(other), to_number(text))
                if _relational(op, a, b):
                    return True
        return False

    if op == '=':
        return _equal_atoms(left, right)
    if op == '!=':
        return not _equal_atoms(left, right)
    return _relational(op, to_number(left), to_number(right))


def is_quoted_literal(expr: str) -> bool:
    """True when expr is one string literal: 'abc' or "abc", not 'a' = 'b'."""
    if len(expr) < 2 or expr[0] not in ('"', "'") or expr[-1] != expr[0]:
        return False
    return expr[0] not in expr[1:-1]


def _top_level_arithmetic(expr: str) -> bool:
    """True when expr has an arithmetic operator outside brackets and quotes."""
    depth = 0
    quote = None
    for i, c in enumerate(expr):
        if quote:
            if c == quote:
                quote = None
            continue
        if c in ('"', "'"):
            quote = c
        elif c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
        elif depth == 0:
            if c == '+':
                return True
            if c == '-' and i > 0 and expr[i - 1] in ' )' :
                return True
            if c == '*' and i > 0 and expr[i - 1] not in '/:' and expr[i - 1] != '(':
                # '*' after a step separator is the name test, otherwise multiplication
                return True
            if expr.startswith((' div ', ' mod '), i):
                return True
    return False


def is_path_like(expr: str) -> bool:
    """True when expr is a location path, whose value is a node-set: OsTask/*[...],
    ../Name, $var/Child, node:ref(.)/Child. Literals, plain variables, plain function
    calls and arithmetic are not."""
    import re
    e = expr.strip()
    if not e or is_quoted_literal(e):
        return False
    # 'true' / 'false' without parentheses are location paths (child elements of that name) in
    # XPath, not booleans: node:value(X) = true is false in EB (Os ORTI OsStackMonitoring)
    if re.match(r'^-?\d+(\.\d+)?$', e) or e.startswith('@'):
        return False
    if _top_level_arithmetic(e):
        return False
    for op in ('=', '<', '>', ' and ', ' or '):
        if _top_level_find(e, op):
            return False
    if e.startswith('$'):
        return '/' in e or '[' in e
    m = re.match(r'^[\w:\-]+\s*\(', e)
    if m:
        # a function call is a path only when a step or predicate follows it
        depth = 0
        quote = None
        for i in range(m.end() - 1, len(e)):
            c = e[i]
            if quote:
                if c == quote:
                    quote = None
                continue
            if c in ('"', "'"):
                quote = c
            elif c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
                if depth == 0:
                    rest = e[i + 1:].strip()
                    return rest.startswith(('/', '['))
        return False
    return bool(re.match(r'^(\.{1,2}|/|\*|[A-Za-z_])', e))


def _top_level_find(expr: str, op: str) -> bool:
    depth = 0
    quote = None
    for i, c in enumerate(expr):
        if quote:
            if c == quote:
                quote = None
            continue
        if c in ('"', "'"):
            quote = c
        elif c in '([':
            depth += 1
        elif c in ')]':
            depth -= 1
        elif depth == 0 and expr.startswith(op, i):
            return True
    return False


def to_double_result(value: Any) -> Any:
    """Arithmetic results and XPath numeric functions are Doubles."""
    if isinstance(value, bool) or value is None:
        return value
    if isinstance(value, int):
        return float(value)
    return value

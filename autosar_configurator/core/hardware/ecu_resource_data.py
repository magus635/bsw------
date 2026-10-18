"""
ECU resource data helpers

Shared by the chip YAML loader/exporter, the .properties importer/exporter and
the resolver.  A chip carries its ECU resources as a nested mapping

    {module: {name: value}}

whose flat key ``<module>.<name>`` is identical to the key a ``.properties``
file would use (the module is the text before the first dot).  A value is a
scalar or a list of scalars.  Long lists may be written in index range
notation (``{0-15: 1, 16: 2}``) which is expanded when the chip is loaded.
"""
import re
from typing import Any, Dict, List, Tuple

EcuResources = Dict[str, Dict[str, Any]]

# Lists shorter than this are never written in range notation
RANGE_MIN_LIST_LEN = 16

_RANGE_KEY = re.compile(r'^\s*(\d+)\s*(?:-\s*(\d+))?\s*$')
_SCALAR_TYPES = (str, int, float, bool, type(None))


def _is_scalar(value: Any) -> bool:
    return isinstance(value, _SCALAR_TYPES)


def expand_ranges(flat_key: str, mapping: Any) -> List[Any]:
    """Expand an index range mapping to the full list.

    Args:
        flat_key: Flat key of the entry (used in error messages)
        mapping: ``{"0-15": 1, 16: 2, ...}`` - inclusive ranges or single indexes;
            may also be a sequence of ``(range, value)`` pairs, where a repeated
            range is reported as an overlap

    Raises:
        ValueError: on an invalid key, a non-scalar value, a gap or an overlap
    """
    if not mapping:
        raise ValueError(f"{flat_key}: empty index range mapping")

    runs: List[Tuple[int, int, Any]] = []
    pairs = mapping.items() if isinstance(mapping, dict) else mapping
    for raw_key, value in pairs:
        m = _RANGE_KEY.match(str(raw_key))
        if not m:
            raise ValueError(
                f"{flat_key}: '{raw_key}' is not an index range "
                f"(expected '<first>-<last>' or a single index)")
        first = int(m.group(1))
        last = int(m.group(2)) if m.group(2) is not None else first
        if last < first:
            raise ValueError(f"{flat_key}: range '{raw_key}' ends before it starts")
        if not _is_scalar(value):
            raise ValueError(f"{flat_key}: range '{raw_key}' must map to a scalar value")
        runs.append((first, last, value))

    runs.sort(key=lambda r: (r[0], r[1]))
    result: List[Any] = []
    expected = 0
    for first, last, value in runs:
        if first > expected:
            missing = f"{expected}" if first - expected == 1 else f"{expected}-{first - 1}"
            raise ValueError(f"{flat_key}: index range has a gap, missing index {missing}")
        if first < expected:
            raise ValueError(f"{flat_key}: index range overlaps at index {first}")
        result.extend([value] * (last - first + 1))
        expected = last + 1
    return result


def _same(a: Any, b: Any) -> bool:
    return type(a) is type(b) and a == b


def compress_ranges(values: List[Any]) -> Dict[Any, Any]:
    """Run-length encode a list to the index range notation ``{first-last: v}``."""
    out: Dict[Any, Any] = {}
    start = 0
    for i in range(1, len(values) + 1):
        if i == len(values) or not _same(values[i], values[start]):
            out[start if i - start == 1 else f"{start}-{i - 1}"] = values[start]
            start = i
    return out


def should_compress(values: List[Any]) -> bool:
    """Whether a list is written in range notation: long enough and shorter that way."""
    if len(values) < RANGE_MIN_LIST_LEN or not all(_is_scalar(v) for v in values):
        return False
    return len(compress_ranges(values)) < len(values)


def normalize_value(flat_key: str, value: Any) -> Any:
    """Validate one ECU resource value and expand range notation.

    Raises:
        ValueError: if the value is neither a scalar nor a list of scalars
            (nor a valid index range mapping)
    """
    if _is_scalar(value):
        return value
    if isinstance(value, dict):
        return expand_ranges(flat_key, value)
    if isinstance(value, (list, tuple)):
        for item in value:
            if not _is_scalar(item):
                raise ValueError(f"{flat_key}: list items must be scalars, got {type(item).__name__}")
        return list(value)
    raise ValueError(f"{flat_key}: unsupported value type {type(value).__name__}")


def parse_ecu_resources(data: Any) -> EcuResources:
    """Validate and normalize the ``ecu_resources`` section of a chip YAML.

    Raises:
        ValueError: with a message naming the offending key
    """
    if data is None:
        return {}
    if not isinstance(data, dict):
        raise ValueError("ecu_resources must be a mapping of module -> {name: value}")  # noqa: TRY004 - callers handle ValueError only

    result: EcuResources = {}
    for module, entries in data.items():
        module = str(module)
        if not module or '.' in module:
            raise ValueError(f"ecu_resources: invalid module name '{module}'")
        if not isinstance(entries, dict):
            raise ValueError(f"ecu_resources.{module} must be a mapping of name -> value")  # noqa: TRY004
        params: Dict[str, Any] = {}
        for name, value in entries.items():
            params[str(name)] = normalize_value(f"{module}.{name}", value)
        result[module] = params
    return result


def serialize_value(value: Any) -> Any:
    """Value as it is written to YAML (long lists use range notation)."""
    if isinstance(value, list):
        if should_compress(value):
            return compress_ranges(value)
        return list(value)
    return value


def flatten_ecu_resources(resources: EcuResources) -> Dict[str, Any]:
    """Nested ``{module: {name: value}}`` -> flat ``{"module.name": value}`` (order kept)."""
    flat: Dict[str, Any] = {}
    for module, entries in resources.items():
        for name, value in entries.items():
            flat[f"{module}.{name}"] = list(value) if isinstance(value, list) else value
    return flat


def nest_flat_resources(flat: Dict[str, Any]) -> Tuple[EcuResources, List[str]]:
    """Flat properties dict -> nested ``{module: {name: value}}``.

    A key is grouped by the text before its first dot.  A key without a dot has
    no module and cannot be represented; it is returned in the second element.
    """
    nested: EcuResources = {}
    skipped: List[str] = []
    for key, value in flat.items():
        if '.' not in key:
            skipped.append(key)
            continue
        module, name = key.split('.', 1)
        if not module or not name:
            skipped.append(key)
            continue
        nested.setdefault(module, {})[name] = list(value) if isinstance(value, list) else value
    return nested, skipped


def describe_ecu_resources(resources: EcuResources, max_len: int = 100) -> str:
    """Human-readable listing, one ``Module.name: value`` line per key.

    Long values are shortened and show their element count, so a 992-element
    list stays on one line.  Meant for read-only previews.
    """
    lines: List[str] = []
    for key, value in flatten_ecu_resources(resources).items():
        if isinstance(value, list):
            text = ", ".join(str(v) for v in value)
            if len(text) > max_len:
                text = text[:max_len].rstrip(", ") + f" ... ({len(value)} items)"
            else:
                text = f"{text}  ({len(value)} items)" if len(value) > 1 else text
        else:
            text = str(value)
            if len(text) > max_len:
                text = text[:max_len] + " ..."
        lines.append(f"{key}: {text}")
    return "\n".join(lines)


# --- editing helpers (used by the chip designer's ECU resource page) -----------

PLACEHOLDER = None        # value of an entry that still has to be filled in

_TRUE_FALSE = {"true": True, "yes": True, "on": True, "false": False, "no": False, "off": False}


def infer_scalar(text: str, keep_string: bool = False) -> Any:
    """Typed scalar from entered text, by the same rules as ``.properties`` parsing.

    Hexadecimal and plain integers, floats and booleans are converted; anything
    else stays a string.  Empty text gives the placeholder (None).  With
    ``keep_string`` the text is kept as it is (``007`` stays ``007``).
    """
    text = text.strip()
    if not text:
        return PLACEHOLDER
    if keep_string:
        return text
    if text.lower().startswith("0x"):
        try:
            return int(text, 16)
        except ValueError:
            pass
    try:
        return int(text)
    except ValueError:
        pass
    try:
        return float(text)
    except ValueError:
        pass
    if text.lower() in _TRUE_FALSE:
        return _TRUE_FALSE[text.lower()]
    return text


def value_type_name(value: Any) -> str:
    """Short type name shown next to a value in the editor."""
    if value is None:
        return "empty"
    if isinstance(value, bool):
        return "bool"
    if isinstance(value, int):
        return "int"
    if isinstance(value, float):
        return "float"
    if isinstance(value, list):
        return f"list[{len(value)}]"
    return "string"


def check_module_name(module: str) -> str:
    module = (module or "").strip()
    if not module or "." in module:
        raise ValueError(f"'{module}' is not a valid module name (not empty, no '.')")
    return module


def check_key_name(name: str) -> str:
    name = (name or "").strip()
    if not name:
        raise ValueError("a key name must not be empty")
    return name


def set_entry(resources: EcuResources, module: str, name: str, value: Any) -> None:
    """Create or replace ``module.name``; the value is validated like a loaded one."""
    module, name = check_module_name(module), check_key_name(name)
    resources.setdefault(module, {})[name] = normalize_value(f"{module}.{name}", value)


def delete_entry(resources: EcuResources, module: str, name: str) -> None:
    resources.get(module, {}).pop(name, None)
    if module in resources and not resources[module]:
        del resources[module]


def rename_entry(resources: EcuResources, module: str, old: str, new: str) -> None:
    """Rename a key inside a module, keeping its position; refuses to overwrite."""
    new = check_key_name(new)
    entries = resources[module]
    if new != old and new in entries:
        raise ValueError(f"{module}.{new} already exists")
    resources[module] = {(new if k == old else k): v for k, v in entries.items()}


def rename_module(resources: EcuResources, old: str, new: str) -> None:
    """Rename a module, keeping its position; refuses to merge into an existing one."""
    new = check_module_name(new)
    if new != old and new in resources:
        raise ValueError(f"module {new} already exists")
    renamed = {(new if m == old else m): e for m, e in resources.items()}
    resources.clear()
    resources.update(renamed)


def list_to_range_rows(values: List[Any]) -> List[Tuple[str, Any]]:
    """Rows ``(range text, value)`` of the range view of a list."""
    return [(str(k), v) for k, v in compress_ranges(values).items()]


def range_rows_to_list(flat_key: str, rows: List[Tuple[str, Any]]) -> List[Any]:
    """Full list from range view rows (gap, overlap or bad range raises ValueError)."""
    return expand_ranges(flat_key, list(rows))


def count_placeholders(resources: EcuResources) -> int:
    """Number of entries whose value is still the placeholder."""
    return sum(1 for entries in resources.values() for v in entries.values() if v is PLACEHOLDER)


def parse_selectors(data: Any) -> Dict[str, str]:
    """Validate the ``selectors`` section: ``{"<Module>.<parameter>": "<value>"}``."""
    if data is None:
        return {}
    if not isinstance(data, dict):
        raise ValueError("selectors must be a mapping of '<Module>.<parameter>' -> value")  # noqa: TRY004 - callers handle ValueError only
    result: Dict[str, str] = {}
    for key, value in data.items():
        key = str(key).strip()
        module, _, param = key.partition(".")
        if not module or not param or "." in param:
            raise ValueError(f"selectors: '{key}' is not '<Module>.<parameter>'")
        if not isinstance(value, (str, int)) or isinstance(value, bool) or str(value).strip() == "":
            raise ValueError(f"selectors.{key} must be a non-empty string")
        result[key] = str(value).strip()
    return result

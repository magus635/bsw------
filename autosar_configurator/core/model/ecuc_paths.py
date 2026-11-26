"""Shared ECUC path normalization and prefix-stripping helpers.

Handles DaVinci ``/ActiveEcuC/...`` (including doubled ``/ActiveEcuC/ActiveEcuC/...``
and case variants), legacy ``/Config/...``, EB ``/<Mod>_Config/...`` / ``/<Mod>_Values/...``,
and single-segment package prefixes cleanly without altering non-ECUC foreign paths.
"""

from typing import Collection, Optional


def normalize_ecuc_path(path: str) -> str:
    """Trim whitespace and collapse redundant/trailing slashes."""
    if not isinstance(path, str):
        return ""
    stripped = path.strip()
    if not stripped:
        return ""
    parts = [p for p in stripped.split("/") if p]
    if not parts:
        return ""
    return "/" + "/".join(parts)


def is_active_ecuc_path(path: str) -> bool:
    """Return True when ``path`` begins with one or more ``ActiveEcuC`` segments plus a target."""
    norm = normalize_ecuc_path(path)
    if not norm:
        return False
    parts = norm[1:].split("/")
    idx = 0
    while idx < len(parts) and parts[idx].lower() == "activeecuc":
        idx += 1
    return idx > 0 and idx < len(parts)


def strip_active_ecuc_prefix(path: str) -> str:
    """Strip one or more leading ``ActiveEcuC`` segments (case-insensitive) when a target remains."""
    norm = normalize_ecuc_path(path)
    if not norm:
        return ""
    parts = norm[1:].split("/")
    while len(parts) >= 2 and parts[0].lower() == "activeecuc":
        parts = parts[1:]
    return "/" + "/".join(parts)


def strip_ecuc_prefixes(path: str, known_modules: Optional[Collection[str]] = None) -> str:
    """Strip leading ECU/role/package prefixes from an ECUC path when known."""
    stripped = strip_active_ecuc_prefix(path)
    if not stripped:
        return ""
    parts = stripped[1:].split("/")

    known = set(known_modules) if known_modules else set()
    if len(parts) >= 2 and parts[0] == "Config" and parts[0] not in known:
        parts = parts[1:]
    if (
        len(parts) >= 2
        and (parts[0].endswith("_Config") or parts[0].endswith("_Values"))
        and parts[0] not in known
    ):
        parts = parts[1:]

    if known and len(parts) >= 2:
        if parts[0] not in known and parts[1] in known:
            parts = parts[1:]
        elif len(parts) >= 3 and parts[0] == parts[1] and parts[0] in known:
            parts = parts[1:]

    return "/" + "/".join(parts)


def ecuc_ref_matches_container(ref_value, target_container) -> bool:
    """Return True if ``ref_value`` targets ``target_container`` by pointer or normalized path."""
    if getattr(ref_value, "is_resolved", False) and getattr(ref_value, "target", None) is not None:
        if ref_value.target is target_container:
            return True
        if (
            not getattr(ref_value.target, "_is_module_root_proxy", False)
            and ref_value.target.get_path() == target_container.get_path()
        ):
            return True

    raw = getattr(ref_value, "value_ref", "") or ""
    if not raw:
        return False

    target_path = normalize_ecuc_path(target_container.get_path())
    norm = normalize_ecuc_path(raw)
    if norm == target_path:
        return True

    mod_names = {
        n
        for n in (
            getattr(target_container, "module_name", None),
            getattr(getattr(target_container, "module_config", None), "short_name", None),
        )
        if isinstance(n, str) and n
    }
    if strip_ecuc_prefixes(norm, known_modules=mod_names or None) == target_path:
        return True

    if norm.startswith("/Config/") and target_path.count("/") >= 2:
        target_suffix = target_path.split("/", 2)[2]
        if norm[8:] == target_suffix:
            return True

    return False


def ecuc_ref_targets_module(
    ref_value,
    module_name: str,
    config_short_name: Optional[str] = None,
) -> bool:
    """Return True if ``ref_value`` targets ``module_name`` or ``config_short_name``."""
    names = {n for n in (module_name, config_short_name) if isinstance(n, str) and n}
    if not names:
        return False

    if getattr(ref_value, "is_resolved", False) and getattr(ref_value, "target", None) is not None:
        if getattr(ref_value.target, "module_name", None) in names:
            return True
        tcfg = getattr(ref_value.target, "module_config", None)
        if tcfg is not None and getattr(tcfg, "short_name", None) in names:
            return True

    raw = getattr(ref_value, "value_ref", "") or ""
    if not raw:
        return False

    stripped = strip_ecuc_prefixes(raw, known_modules=names)
    for name in names:
        if stripped == f"/{name}" or stripped.startswith(f"/{name}/"):
            return True
    return False

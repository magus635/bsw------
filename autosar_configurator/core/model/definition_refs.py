"""
Definition references written into configuration files (openspec fix-config-definition-refs).

A value file names the definition of every container, parameter and reference with
DEFINITION-REF: the absolute path of the definition element, /<AR-PACKAGE>/<Module>/...,
and DEST, the element's type. Definitions keep internal paths (/AUTOSAR/EcucDefs/<Module>/
<Container> for top-level containers, <Container>/.../<Name> below them), and values created
in the tool used to copy those. These helpers turn any of the forms into the path relative to
the module, compare definitions independently of the form, and give the absolute path and
the type to write.
"""
from typing import Any, Optional

GENERIC_PARAM_DEST = 'ECUC-PARAMETER-DEF'
CONTAINER_DEST = 'ECUC-PARAM-CONF-CONTAINER-DEF'
CHOICE_CONTAINER_DEST = 'ECUC-CHOICE-CONTAINER-DEF'
REFERENCE_DEST = 'ECUC-REFERENCE-DEF'
CHOICE_REFERENCE_DEST = 'ECUC-CHOICE-REFERENCE-DEF'


def module_relative(ref: Optional[str], module_name: Optional[str] = None) -> str:
    """Path of a definition element relative to its module.

    'OsOS/OsUseArti' stays; '/THA6_ASR21/Os/OsOS/OsUseArti' and
    '/AUTOSAR/EcucDefs/Os/OsOS/OsUseArti' give 'OsOS/OsUseArti' (everything after the first
    segment equal to the module name). Without a module name an absolute path is cut after
    '/AUTOSAR/EcucDefs/<Module>' or else after '/<Package>/<Module>'. The module itself is ''.
    """
    if not ref:
        return ''
    if not ref.startswith('/'):
        return ref.strip('/')
    parts = [p for p in ref.split('/') if p]
    if module_name and module_name in parts:
        return '/'.join(parts[parts.index(module_name) + 1:])
    if parts[:2] == ['AUTOSAR', 'EcucDefs']:
        return '/'.join(parts[3:])
    return '/'.join(parts[2:])


def same_definition(ref_a: Optional[str], ref_b: Optional[str], module_name: Optional[str] = None) -> bool:
    """True when two definition references name the same element, whatever their form."""
    if ref_a == ref_b:
        return True
    if not ref_a or not ref_b:
        return False
    return module_relative(ref_a, module_name) == module_relative(ref_b, module_name)


def module_path(module_def: Any) -> str:
    """The module's path in its definition file (/<AR-PACKAGE>/<Module>)."""
    return getattr(module_def, 'ar_path', '') or getattr(module_def, 'definition_ref', '') \
        or f"/AUTOSAR/EcucDefs/{module_def.short_name}"


def absolute_ref(module_def: Any, ref: Optional[str]) -> str:
    """DEFINITION-REF to write for a definition reference of this module (an empty
    reference, a definition without a path, stays empty)."""
    if not ref:
        return ref or ''
    rel = module_relative(ref, module_def.short_name)
    base = module_path(module_def)
    return f"{base}/{rel}" if rel else base


def needs_repair(module_def: Any, ref: Optional[str]) -> bool:
    """A reference to rewrite: relative, or under another module path than the definition's."""
    if not ref:
        return False
    if not ref.startswith('/'):
        return True
    base = module_path(module_def)
    return not (ref == base or ref.startswith(base + '/'))


def container_dest(container_def: Any) -> str:
    return CHOICE_CONTAINER_DEST if getattr(container_def, 'is_choice', False) else CONTAINER_DEST


def parameter_dest(param_def: Any) -> Optional[str]:
    param_type = getattr(param_def, 'param_type', None)
    return getattr(param_type, 'value', None) or None


def reference_dest(ref_def: Any) -> str:
    return CHOICE_REFERENCE_DEST if getattr(ref_def, 'is_choice_reference', False) else REFERENCE_DEST

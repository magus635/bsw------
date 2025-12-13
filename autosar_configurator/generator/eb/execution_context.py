"""
Execution Context for EB Template Engine

Provides the mandatory execution context objects per spec Section 3:
- ecuC: ECU Configuration root object
- variant: Build variant (PRE_COMPILE / POST_BUILD / LINK_TIME)
- moduleName: Current BSW module name
- generationTarget: Target filename / type
"""
from typing import Optional, Any, Dict, List
from dataclasses import dataclass, field
from enum import Enum


class VariantType(Enum):
    """AUTOSAR configuration variants per spec Section 9"""
    PRE_COMPILE = "PRE_COMPILE"   # All parameters statically expanded
    POST_BUILD = "POST_BUILD"     # Config separated to PBcfg
    LINK_TIME = "LINK_TIME"       # Only interfaces retained


@dataclass
class ExecutionContext:
    """Execution context for template rendering.
    
    Per spec Section 3, this provides:
    - ecuC: ECU Configuration root object
    - variant: Build variant
    - moduleName: Current BSW module name
    - generationTarget: Target filename/type
    """
    # Core context objects (Mandatory per spec)
    module_name: str = ""
    generation_target: str = ""
    variant: VariantType = VariantType.PRE_COMPILE
    
    # Additional context
    output_file: str = ""
    template_file: str = ""
    
    # Custom variables injected into context
    custom_vars: Dict[str, Any] = field(default_factory=dict)
    
    def get_variant_string(self) -> str:
        """Get variant as string for template access"""
        return self.variant.value
    
    def is_pre_compile(self) -> bool:
        """Check if PRE_COMPILE variant"""
        return self.variant == VariantType.PRE_COMPILE
    
    def is_post_build(self) -> bool:
        """Check if POST_BUILD variant"""
        return self.variant == VariantType.POST_BUILD
    
    def is_link_time(self) -> bool:
        """Check if LINK_TIME variant"""
        return self.variant == VariantType.LINK_TIME


@dataclass
class BooleanOutputMode:
    """Defines how Boolean values are output.
    
    Per spec 4.3 AUTOSAR Semantic Mapping:
    - Feature boolean: STD_ON / STD_OFF
    - Runtime boolean: TRUE / FALSE
    
    NOT allowed: true / false (lowercase)
    """
    FEATURE_ON = "STD_ON"
    FEATURE_OFF = "STD_OFF"
    RUNTIME_TRUE = "TRUE"
    RUNTIME_FALSE = "FALSE"


def format_boolean_feature(value: bool) -> str:
    """Format boolean as AUTOSAR feature flag.
    
    Returns STD_ON or STD_OFF per spec 4.3.
    """
    return "STD_ON" if value else "STD_OFF"


def format_boolean_runtime(value: bool) -> str:
    """Format boolean as AUTOSAR runtime value.
    
    Returns TRUE or FALSE per spec 4.3.
    """
    return "TRUE" if value else "FALSE"


def parse_boolean(value: Any) -> bool:
    """Parse a value as boolean."""
    if isinstance(value, bool):
        return value
    if isinstance(value, str):
        return value.lower() in ('true', '1', 'yes', 'on', 'std_on')
    if isinstance(value, (int, float)):
        return bool(value)
    return False

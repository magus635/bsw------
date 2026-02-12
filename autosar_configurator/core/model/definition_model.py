"""
Definition Model - ECUC Definition (DEF) layer
Represents the "blueprint" or "template" from ECUC-DEF ARXML files
"""
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Any
from enum import Enum


class EcucParameterType(Enum):
    """ECUC parameter types"""
    ENUMERATION = "ECUC-ENUMERATION-PARAM-DEF"
    INTEGER = "ECUC-INTEGER-PARAM-DEF"
    FLOAT = "ECUC-FLOAT-PARAM-DEF"
    BOOLEAN = "ECUC-BOOLEAN-PARAM-DEF"
    STRING = "ECUC-STRING-PARAM-DEF"
    FUNCTION = "ECUC-FUNCTION-NAME-DEF"


class ConfigClass:
    """Constants for config class types"""
    PRE_COMPILE = "PRE-COMPILE"
    LINK_TIME = "LINK-TIME"
    POST_BUILD = "POST-BUILD"


class VariantType(Enum):
    """AUTOSAR variant types for parameters"""
    PRECOMPILE = "VARIANT-PRE-COMPILE"
    LINKTIME = "VARIANT-LINK-TIME"
    POSTBUILD = "VARIANT-POST-BUILD"
    POSTBUILD_LOADABLE = "VARIANT-POST-BUILD-LOADABLE"
    POSTBUILD_SELECTABLE = "VARIANT-POST-BUILD-SELECTABLE"


@dataclass
class EcucParameterDef:
    """ECUC Parameter Definition (ECUC-*-PARAM-DEF)
    
    Defines what a parameter CAN be configured to (constraints, type, range)
    """
    short_name: str
    param_type: EcucParameterType
    description: str = ""
    
    # Multiplicity constraints
    lower_multiplicity: int = 0
    upper_multiplicity: int = 1
    
    # Default value
    default_value: Any = None
    
    # Type-specific constraints
    # For ENUMERATION
    literals: Optional[List[str]] = None  # e.g., ["SARADC0", "SARADC1", ...]
    
    # For INTEGER/FLOAT
    min_value: Optional[float] = None  # e.g., 2
    max_value: Optional[float] = None  # e.g., 320
    
    # Metadata
    symbolic_name_value: bool = False
    with_auto: bool = False
    scope: str = "LOCAL"
    origin: str = "AUTOSAR_ECUC"
    
    # Full path for reference
    definition_ref: str = ""  # Will be set during parsing
    
    # Variant support
    variant_type: Optional[VariantType] = None  # Default to None (all variants)

    # Logic Loop attributes (Pre-compile/Link-time/Post-build)
    config_class: Optional[str] = None  # e.g., "PRE-COMPILE"
    config_variant: Optional[str] = None # e.g., "VARIANT-PRE-COMPILE"

    # XDM dynamic expressions (stored for UI tooltip/debug, resolved via .properties)
    default_expr: Optional[str] = None   # e.g., "ecu:list('Adc.RequestSrcPrio')[1]"
    range_expr: Optional[str] = None     # e.g., "ecu:list('Adc.HwUnitId')"
    
    @property
    def is_required(self) -> bool:
        """Check if this parameter is mandatory"""
        return self.lower_multiplicity >= 1

    @property
    def path(self) -> str:
        """Compatibility property for definition_ref"""
        return self.definition_ref


@dataclass
class EcucReferenceDef:
    """ECUC Reference Definition (ECUC-REFERENCE-DEF / ECUC-CHOICE-REFERENCE-DEF)

    Defines a reference to another container (e.g., link to Mcu module).
    For choice references, multiple destination types are allowed.
    """
    short_name: str
    description: str = ""

    # Target specification
    destination_ref: str = ""  # e.g., "/AUTOSAR/EcucDefs/Mcu/McuModuleConfiguration/..."
    destination_type: str = "ECUC-PARAM-CONF-CONTAINER-DEF"

    # Choice reference: multiple allowed destination paths
    choice_destination_refs: list = None  # e.g., ["/AUTOSAR/.../AdcHwUnit", "/AUTOSAR/.../CanController", ...]

    # Multiplicity
    lower_multiplicity: int = 0
    upper_multiplicity: int = 1

    # Metadata
    scope: str = "LOCAL"
    origin: str = "AUTOSAR_ECUC"

    # Full path
    definition_ref: str = ""

    def __post_init__(self):
        if self.choice_destination_refs is None:
            self.choice_destination_refs = []

    @property
    def is_choice_reference(self) -> bool:
        """Check if this is a choice reference (multiple destination types)"""
        return len(self.choice_destination_refs) > 1

    @property
    def is_required(self) -> bool:
        """Check if this reference is mandatory"""
        return self.lower_multiplicity >= 1

    @property
    def path(self) -> str:
        """Compatibility property for definition_ref"""
        return self.definition_ref


@dataclass
class EcucContainerDef:
    """ECUC Container Definition (ECUC-PARAM-CONF-CONTAINER-DEF)
    
    Defines what a container CAN contain (parameters, sub-containers, references)
    """
    short_name: str
    description: str = ""
    
    # Multiplicity constraints (how many instances can be created)
    lower_multiplicity: int = 0
    upper_multiplicity: int = 1  # -1 for unlimited (*)
    
    # Parameters that can be configured
    parameters: Dict[str, EcucParameterDef] = field(default_factory=dict)
    
    # References to other containers
    references: Dict[str, EcucReferenceDef] = field(default_factory=dict)
    
    # Sub-container definitions (nested containers)
    sub_containers: Dict[str, 'EcucContainerDef'] = field(default_factory=dict)
    
    # Metadata
    scope: str = "LOCAL"
    origin: str = "AUTOSAR_ECUC"
    post_build_variant_multiplicity: bool = False

    # Full path for reference
    definition_ref: str = ""

    # XDM dynamic expression for upper multiplicity
    upper_multiplicity_expr: Optional[str] = None  # e.g., "num:i(count(ecu:list('Adc.HwUnitId')))"
    
    @property
    def is_required(self) -> bool:
        """Check if at least one instance is required"""
        return self.lower_multiplicity >= 1
    
    @property
    def is_multiple(self) -> bool:
        """Check if multiple instances are allowed"""
        return self.upper_multiplicity == -1 or self.upper_multiplicity > 1
    
    @property
    def multiplicity_str(self) -> str:
        """Get multiplicity as string (e.g., '1..6', '0..*')"""
        upper = "*" if self.upper_multiplicity == -1 else str(self.upper_multiplicity)
        return f"{self.lower_multiplicity}..{upper}"

    @property
    def path(self) -> str:
        """Compatibility property for definition_ref"""
        return self.definition_ref
    
    def add_parameter(self, param_def: EcucParameterDef):
        """Add a parameter definition"""
        self.parameters[param_def.short_name] = param_def
    
    def add_reference(self, ref_def: EcucReferenceDef):
        """Add a reference definition"""
        self.references[ref_def.short_name] = ref_def
    
    def add_sub_container(self, container_def: 'EcucContainerDef'):
        """Add a sub-container definition"""
        self.sub_containers[container_def.short_name] = container_def


@dataclass
class EcucModuleDef:
    """ECUC Module Definition (ECUC-MODULE-DEF)
    
    Top-level definition of a BSW module (e.g., Adc, Mcu, Port)
    """
    short_name: str  # e.g., "Adc"
    description: str = ""
    
    # Top-level containers
    containers: Dict[str, EcucContainerDef] = field(default_factory=dict)
    
    # Metadata
    admin_data: Dict[str, str] = field(default_factory=dict)
    category: str = ""
    
    # API version info (optional)
    api_service_prefix: str = ""
    
    # Full path
    definition_ref: str = ""
    
    # Default variant for this module
    default_variant: VariantType = VariantType.POSTBUILD

    @property
    def path(self) -> str:
        """Compatibility property for definition_ref"""
        return self.definition_ref
    
    def add_container(self, container_def: EcucContainerDef):
        """Add a top-level container definition"""
        self.containers[container_def.short_name] = container_def
    
    def get_container_def(self, path: str) -> Optional[EcucContainerDef]:
        """Get container definition by path
        
        Args:
            path: e.g., "AdcConfigSet" or "AdcConfigSet/AdcHwUnit"
        """
        parts = path.split('/')
        current = self.containers.get(parts[0])
        
        for part in parts[1:]:
            if current is None:
                return None
            current = current.sub_containers.get(part)
        
        return current

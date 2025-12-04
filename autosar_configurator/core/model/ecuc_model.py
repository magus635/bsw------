"""
ECUC (ECUC - ECU Configuration) specific data models for AUTOSAR
"""
from dataclasses import dataclass, field
from typing import Dict, List, Optional, Any
from .container import Container, Parameter


@dataclass
class EcucReference:
    """ECUC Reference Definition (ECUC-REFERENCE-DEF)"""
    short_name: str
    description: str = ""
    destination_ref: str = ""  # Target path
    destination_type: str = "ECUC-PARAM-CONF-CONTAINER-DEF"
    lower_multiplicity: int = 0
    upper_multiplicity: int = 1
    scope: str = "LOCAL"
    origin: str = "AUTOSAR_ECUC"
    post_build_variant_value: bool = False


@dataclass
class EcucParameter(Parameter):
    """ECUC Parameter Definition with AUTOSAR-specific fields"""
    
    # ECUC parameter type (ECUC-INTEGER-PARAM-DEF, ECUC-ENUMERATION-PARAM-DEF, etc.)
    param_def_type: str = "ECUC-INTEGER-PARAM-DEF"
    
    # For enumeration types
    literals: Optional[List[str]] = None  # Enumeration values list
    
    # Multiplicity constraints
    lower_multiplicity: int = 0
    upper_multiplicity: int = 1
    
    # AUTOSAR metadata
    symbolic_name_value: bool = False
    scope: str = "LOCAL"
    origin: str = "AUTOSAR_ECUC"
    post_build_variant_value: bool = False
    
    # Configuration classes
    value_config_classes: Optional[List[Dict]] = None
    
    def __post_init__(self):
        """Initialize parent class"""
        # Ensure parent Container initialization if not done
        if not hasattr(self, '_observers'):
            super().__post_init__()


@dataclass
class EcucContainer(Container):
    """ECUC Configuration Container with AUTOSAR-specific fields"""
    
    # References dictionary: name -> EcucReference
    references_defs: Dict[str, EcucReference] = field(default_factory=dict)
    
    # Multiplicity constraints
    lower_multiplicity: int = 0
    upper_multiplicity: int = 1  # -1 for unlimited (*)
    
    # ECUC container type
    ecuc_type: str = "ECUC-PARAM-CONF-CONTAINER-DEF"
    
    # AUTOSAR metadata
    scope: str = "LOCAL"
    origin: str = "AUTOSAR_ECUC"
    post_build_variant: bool = False
    post_build_variant_multiplicity: bool = False
    
    # Configuration variant support
    config_class: str = "PRE-COMPILE"  # PRE-COMPILE, POST-BUILD, LINK
    config_variant: str = "VARIANT-POST-BUILD"
    supported_config_variants: List[str] = field(default_factory=list)
    
    # Multiplicity configuration classes
    multiplicity_config_classes: List[Dict] = field(default_factory=list)
    
    def __post_init__(self):
        """Initialize parent class and ECUC specific fields"""
        # Ensure parent Container initialization
        if not hasattr(self, '_observers'):
            super().__post_init__()
        
        # Initialize references_defs if not provided
        if not self.references_defs:
            self.references_defs = {}
    
    def add_reference_def(self, ref_def: EcucReference):
        """Add a reference definition"""
        with self._lock:
            self.references_defs[ref_def.short_name] = ref_def
            self.mark_dirty()
    
    def get_reference_def(self, name: str) -> Optional[EcucReference]:
        """Get reference definition by name"""
        return self.references_defs.get(name)
    
    @property
    def is_required(self) -> bool:
        """Check if this container is required (multiplicity >= 1)"""
        return self.lower_multiplicity >= 1
    
    @property
    def is_multiple(self) -> bool:
        """Check if this container can have multiple instances"""
        return self.upper_multiplicity == -1 or self.upper_multiplicity > 1
    
    @property
    def multiplicity_str(self) -> str:
        """Get multiplicity as string representation"""
        upper = "*" if self.upper_multiplicity == -1 else str(self.upper_multiplicity)
        return f"{self.lower_multiplicity}..{upper}"

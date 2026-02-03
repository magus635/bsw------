"""
Hardware Module - Chip database and resource mapping for AUTOSAR configuration

This module provides:
- ChipDatabase: Manages chip definitions (from YAML or built-in)
- HardwareResourceMapper: Maps chip resources to AUTOSAR configuration (legacy)
- GenericResourceMapper: Generic data-driven mapper using YAML rules
- EcuResourceParser: Parses ECU resources from EB Tresos files
- XdmChipExtractor: Extracts chip definitions from XDM module files
- TresosPropertiesParser: Parses hardware resources from EB Tresos .properties files
"""

# Legacy chip database (primary API for backward compatibility)
from .chip_database import (
    ChipDatabase, ChipDefinition, PortPinDef,
    IntcSourceDef, CanResourceDef, AdcResourceDef, SpiResourceDef
)

# Legacy resource mapper (primary API for backward compatibility)
from .resource_mapper import HardwareResourceMapper, MappingAction, MappingActionType

# New generic resource model (use GenericChipDefinition to avoid confusion)
from .generic_resource import (
    GenericResourceDef,
    ChipDefinition as GenericChipDefinition,
    ChipDefinitionLoader,
    convert_legacy_chip
)

# New mapping rule system
from .mapping_rule import (
    MappingRule,
    ContainerRule,
    ParameterMapping,
    UIConfig,
    UIColumnConfig,
    UIOptionConfig,
    MappingRuleLoader,
    get_default_rule_loader
)

# New generic mapper
from .generic_mapper import (
    GenericResourceMapper,
    MappingAction as GenericMappingAction,
    MappingActionType as GenericMappingActionType,
    ExpressionEvaluator
)

# ECU resource parser
from .ecu_resource_parser import EcuResourceParser, EcuResource, extract_xdm_resources

# XDM chip extractor
from .xdm_chip_extractor import XdmChipExtractor, XdmModuleInfo, extract_chip_from_project

# Tresos properties parser
from .tresos_properties_parser import (
    TresosPropertiesParser, TresosPropertiesFile,
    parse_tresos_properties, find_properties_files,
    build_chip_from_properties
)

__all__ = [
    # Legacy chip database (primary API)
    'ChipDatabase',
    'ChipDefinition',  # This is the legacy version with fixed fields
    'PortPinDef',
    'IntcSourceDef',
    'CanResourceDef',
    'AdcResourceDef',
    'SpiResourceDef',

    # Legacy resource mapper (primary API)
    'HardwareResourceMapper',
    'MappingAction',
    'MappingActionType',

    # New generic resource model
    'GenericResourceDef',
    'GenericChipDefinition',  # New generic version with resources dict
    'ChipDefinitionLoader',
    'convert_legacy_chip',

    # New mapping rule system
    'MappingRule',
    'ContainerRule',
    'ParameterMapping',
    'UIConfig',
    'UIColumnConfig',
    'UIOptionConfig',
    'MappingRuleLoader',
    'get_default_rule_loader',

    # New generic mapper
    'GenericResourceMapper',
    'GenericMappingAction',
    'GenericMappingActionType',
    'ExpressionEvaluator',

    # ECU resource parser
    'EcuResourceParser',
    'EcuResource',
    'extract_xdm_resources',

    # XDM chip extractor
    'XdmChipExtractor',
    'XdmModuleInfo',
    'extract_chip_from_project',

    # Tresos properties parser
    'TresosPropertiesParser',
    'TresosPropertiesFile',
    'parse_tresos_properties',
    'find_properties_files',
    'build_chip_from_properties',
]

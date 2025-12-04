"""
Validation Rules Package

Contains all validation rule implementations organized by category:
- base_rules: Basic parameter and type validation
- structural_rules: Container hierarchy and multiplicity validation
- reference_rules: Reference integrity and dependency checking
- dependency_rules: Dependency and circular dependency detection
"""

from .base_rules import (
    TypeValidationRule,
    RangeValidationRule,
    EnumerationValidationRule,
    RequiredParameterRule
)

from .structural_rules import (
    MultiplicityValidationRule,
)

from .reference_rules import (
    ReferenceIntegrityRule,
    DanglingReferenceRule,
    RequiredReferenceRule
)

from .dependency_rules import (
    CircularDependencyRule,
    DependencyRule
)

__all__ = [
    'TypeValidationRule',
    'RangeValidationRule',
    'EnumerationValidationRule',
    'RequiredParameterRule',
    'MultiplicityValidationRule',
    'ReferenceIntegrityRule',
    'DanglingReferenceRule',
    'RequiredReferenceRule',
    'CircularDependencyRule',
    'DependencyRule',
]


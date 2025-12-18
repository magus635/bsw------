"""
Validation Engine - Core validation framework for ECUC configurations

Provides a flexible, rule-based validation system with:
- Pluggable validation rules
- Categorized results (errors, warnings, info)
- Context-aware validation
"""
from abc import ABC, abstractmethod
from dataclasses import dataclass, field
from typing import List, Optional, Dict, Any
from enum import Enum

from .model.definition_model import EcucModuleDef, EcucContainerDef
from .model.configuration_model import EcucModuleConfiguration, EcucContainerValue


class ValidationSeverity(Enum):
    """Severity levels for validation results"""
    ERROR = "error"      # Blocks configuration from being valid
    WARNING = "warning"  # Non-blocking issue that should be reviewed
    INFO = "info"        # Informational message


@dataclass
class ValidationMessage:
    """Single validation message"""
    severity: ValidationSeverity
    message: str
    rule_name: str
    
    # Location context
    container_path: Optional[str] = None
    parameter_name: Optional[str] = None
    
    # Additional context
    details: Optional[str] = None
    suggested_fix: Optional[str] = None
    
    def __str__(self) -> str:
        """String representation for display"""
        location = ""
        if self.container_path:
            location = f"[{self.container_path}"
            if self.parameter_name:
                location += f".{self.parameter_name}"
            location += "] "
        
        return f"{self.severity.value.upper()}: {location}{self.message}"


@dataclass
class ValidationResult:
    """Complete validation result containing all messages"""
    messages: List[ValidationMessage] = field(default_factory=list)
    
    @property
    def errors(self) -> List[ValidationMessage]:
        """Get only error messages"""
        return [m for m in self.messages if m.severity == ValidationSeverity.ERROR]
    
    @property
    def warnings(self) -> List[ValidationMessage]:
        """Get only warning messages"""
        return [m for m in self.messages if m.severity == ValidationSeverity.WARNING]
    
    @property
    def info_messages(self) -> List[ValidationMessage]:
        """Get only info messages"""
        return [m for m in self.messages if m.severity == ValidationSeverity.INFO]
    
    @property
    def error_count(self) -> int:
        """Count of error messages"""
        return len(self.errors)
    
    @property
    def warning_count(self) -> int:
        """Count of warning messages"""
        return len(self.warnings)
    
    @property
    def is_valid(self) -> bool:
        """Check if configuration is valid (no errors)"""
        return self.error_count == 0
    
    def add_message(self, message: ValidationMessage):
        """Add a validation message"""
        self.messages.append(message)
    
    def merge(self, other: 'ValidationResult'):
        """Merge another validation result into this one"""
        self.messages.extend(other.messages)
    
    def get_summary(self) -> str:
        """Get summary string"""
        return f"Validation: {self.error_count} errors, {self.warning_count} warnings"


class ValidationRule(ABC):
    """Abstract base class for validation rules
    
    Each rule implements a specific validation check and can
    generate multiple validation messages.
    """
    
    def __init__(self, name: str, description: str = ""):
        """Initialize validation rule
        
        Args:
            name: Rule identifier
            description: Human-readable description
        """
        self.name = name
        self.description = description
    
    @abstractmethod
    def validate(self, 
                 module_def: EcucModuleDef,
                 configuration: EcucModuleConfiguration,
                 project_context=None) -> ValidationResult:
        """Execute validation rule
        
        Args:
            module_def: Module definition (template)
            configuration: Configuration to validate
            project_context: Optional WorkspaceProject context for cross-module validation
            
        Returns:
            ValidationResult with messages
        """
        pass
    
    def _create_error(self, message: str, **kwargs) -> ValidationMessage:
        """Helper to create error message"""
        return ValidationMessage(
            severity=ValidationSeverity.ERROR,
            message=message,
            rule_name=self.name,
            **kwargs
        )
    
    def _create_warning(self, message: str, **kwargs) -> ValidationMessage:
        """Helper to create warning message"""
        return ValidationMessage(
            severity=ValidationSeverity.WARNING,
            message=message,
            rule_name=self.name,
            **kwargs
        )
    
    def _create_info(self, message: str, **kwargs) -> ValidationMessage:
        """Helper to create info message"""
        return ValidationMessage(
            severity=ValidationSeverity.INFO,
            message=message,
            rule_name=self.name,
            **kwargs
        )


class ValidationEngine:
    """Main validation engine that coordinates rule execution"""
    
    def __init__(self, 
                 module_def: EcucModuleDef,
                 configuration: EcucModuleConfiguration,
                 project_context=None):
        """Initialize validation engine
        
        Args:
            module_def: Module definition (template)
            configuration: Configuration to validate
            project_context: Optional WorkspaceProject context
        """
        self.module_def = module_def
        self.configuration = configuration
        self.project_context = project_context
        self.rules: List[ValidationRule] = []
    
    def register_rule(self, rule: ValidationRule):
        """Register a validation rule
        
        Args:
            rule: ValidationRule instance
        """
        self.rules.append(rule)
    
    def register_rules(self, rules: List[ValidationRule]):
        """Register multiple validation rules
        
        Args:
            rules: List of ValidationRule instances
        """
        self.rules.extend(rules)
    
    def register_default_rules(self):
        """Register all default validation rules
        
        This will be implemented to add standard rules like:
        - Parameter type validation
        - Range validation
        - Multiplicity validation
        - etc.
        """
        # Import here to avoid circular dependency
        from .rules.base_rules import (
            TypeValidationRule,
            RangeValidationRule,
            EnumerationValidationRule,
            RequiredParameterRule
        )
        from .rules.structural_rules import (
            MultiplicityValidationRule,
        )
        
        # Register basic rules
        self.register_rules([
            TypeValidationRule(),
            RangeValidationRule(),
            EnumerationValidationRule(),
            RequiredParameterRule(),
            MultiplicityValidationRule(),
        ])
        
    def load_custom_rules(self, file_path: str):
        """Load custom rules from a JSON or Python file
        
        Args:
            file_path: Path to the rule file (.json or .py)
        """
        from .rules.custom_rules import RuleLoader, PythonRuleLoader
        from pathlib import Path
        
        path = Path(file_path)
        try:
            if path.suffix.lower() == '.py':
                new_rules = PythonRuleLoader.load_from_file(path)
            else:
                new_rules = RuleLoader.load_from_file(path)
                
            self.register_rules(new_rules)
            return len(new_rules)
        except Exception as e:
            raise ValueError(f"Failed to load custom rules from {path.name}: {str(e)}")
    
    def validate(self) -> ValidationResult:
        """Execute all registered rules and aggregate results
        
        Returns:
            ValidationResult with all messages from all rules
        """
        result = ValidationResult()
        
        for rule in self.rules:
            try:
                # Pass project_context if available
                try:
                    rule_result = rule.validate(self.module_def, self.configuration, project_context=self.project_context)
                except TypeError:
                    # Fallback for rules that don't accept project_context yet
                    rule_result = rule.validate(self.module_def, self.configuration)
                    
                result.merge(rule_result)
            except Exception as e:
                # If a rule fails, add error message but continue
                result.add_message(ValidationMessage(
                    severity=ValidationSeverity.ERROR,
                    message=f"Rule '{rule.name}' failed: {str(e)}",
                    rule_name="ValidationEngine"
                ))
        
        return result
    
    def validate_incremental(self, container: EcucContainerValue) -> ValidationResult:
        """Validate only a specific container (for real-time feedback)
        
        Args:
            container: Container to validate
            
        Returns:
            ValidationResult for this container only
        """
        # Create temporary configuration with only this container
        # This is a simplified version for incremental validation
        result = ValidationResult()
        
        # For now, run all rules but they should filter by container
        # In the future, we can optimize by only running relevant rules
        for rule in self.rules:
            try:
                rule_result = rule.validate(self.module_def, self.configuration)
                # Filter results to only this container path
                container_path = container.get_path()
                for msg in rule_result.messages:
                    if msg.container_path and msg.container_path.startswith(container_path):
                        result.add_message(msg)
            except Exception as e:
                # Ignore rule failures in incremental mode
                pass
        
        return result

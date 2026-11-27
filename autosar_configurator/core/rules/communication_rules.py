"""Cross-module validation rule surfacing CAN communication stack diagnostics."""

from ..communication.service import CommunicationWorkbenchService
from ..model.configuration_model import EcucModuleConfiguration
from ..model.definition_model import EcucModuleDef
from ..validation_engine import (
    ValidationMessage,
    ValidationResult,
    ValidationRule,
    ValidationSeverity,
)

_SEVERITY_MAP = {
    "error": ValidationSeverity.ERROR,
    "warning": ValidationSeverity.WARNING,
    "info": ValidationSeverity.INFO,
}


class CommunicationValidationRule(ValidationRule):
    """Validate cross-module CAN/ComM/CanSM/CanIf/PduR/Com/EcuC consistency once per project."""

    def __init__(self) -> None:
        super().__init__(
            name="CommunicationRule",
            description="Validates CAN communication stack channels, PDU lengths, HandleIds, PduR routing, and signal bit layouts",
        )

    def validate(
        self,
        module_def: EcucModuleDef,
        configuration: EcucModuleConfiguration,
        project_context=None,
    ) -> ValidationResult:
        result = ValidationResult()
        if project_context is None:
            return result

        mod_name = getattr(configuration, "short_name", None) or (
            getattr(module_def, "short_name", None) if module_def is not None else None
        )
        anchor = CommunicationWorkbenchService.anchor_module_for_project(project_context)
        if not anchor or mod_name != anchor:
            return result

        diags = CommunicationWorkbenchService(project_context).collect_diagnostics()
        for diag in diags:
            result.add_message(
                ValidationMessage(
                    severity=_SEVERITY_MAP.get(diag.severity, ValidationSeverity.WARNING),
                    message=diag.message,
                    rule_name=self.name,
                    container_path=diag.container_path,
                    parameter_name=diag.parameter_name,
                    details=f"workbench_tab={diag.workbench_tab}; code={diag.code}",
                    suggested_fix=diag.suggested_fix,
                )
            )
        return result

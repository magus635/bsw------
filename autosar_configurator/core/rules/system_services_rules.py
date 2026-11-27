"""Cross-module validation rule surfacing System Services & Diagnostics issues."""

from ..model.configuration_model import EcucModuleConfiguration
from ..model.definition_model import EcucModuleDef
from ..services.service import SystemServicesWorkbenchService
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


class SystemServicesValidationRule(ValidationRule):
    """Validate EcuM, BswM, Os, Dcm+CanTp, and Det consistency once per project."""

    def __init__(self) -> None:
        super().__init__(
            name="SystemServicesRule",
            description="Validates EcuM init/wakeup, BswM rules/actions, Os cores/tasks/ISRs/stacks, Dcm/CanTp diagnostic chains, and Det consistency",
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
        anchor = SystemServicesWorkbenchService.anchor_module_for_project(project_context)
        if not anchor or mod_name != anchor:
            return result

        diags = SystemServicesWorkbenchService(project_context).collect_diagnostics()
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

"""Cross-module validation rule surfacing RTE/SchM readiness & Stage-3 scheduling issues."""

from ..model.configuration_model import EcucModuleConfiguration
from ..model.definition_model import EcucModuleDef
from ..validation_engine import ValidationMessage, ValidationResult, ValidationRule, ValidationSeverity


_SEVERITY_MAP = {
    "error": ValidationSeverity.ERROR,
    "warning": ValidationSeverity.WARNING,
    "info": ValidationSeverity.INFO,
}


class RteSchmValidationRule(ValidationRule):
    """Validate ``Rte`` BSW instances, SchM ExclusiveAreas, Task mappings, and Stage-3 activations."""

    def __init__(self) -> None:
        super().__init__(
            name="RteSchmRule",
            description="Validates RTE/SchM BSW instances, ExclusiveAreas, Task mappings, and Stage-3 OS activations",
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
        if mod_name != "Rte":
            return result

        from ...generator.rte.workbench_service import RteWorkbenchService

        diags = RteWorkbenchService(project_context).collect_diagnostics()
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

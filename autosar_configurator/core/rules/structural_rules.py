"""
Structural Validation Rules - Container hierarchy and multiplicity validation

These rules validate the structural aspects of the configuration,
including container multiplicity constraints and hierarchy.
"""
from typing import Optional, Dict, List

from ..validation_engine import ValidationRule, ValidationResult
from ..model.definition_model import EcucModuleDef, EcucContainerDef
from ..model.configuration_model import DEFAULT_VARIANT, EcucModuleConfiguration, EcucContainerValue


class MultiplicityValidationRule(ValidationRule):
    """Validate container multiplicity constraints"""
    
    def __init__(self):
        super().__init__(
            name="MultiplicityValidation",
            description="Validates that container instances conform to min/max multiplicity constraints"
        )
    
    @staticmethod
    def _collect_variant_views(configuration: EcucModuleConfiguration, project_context=None) -> List[Optional[str]]:
        """Return variant views to validate independently, or ``[None]`` for single-variant configs."""
        assigned: List[str] = []

        def _walk(containers):
            for c in containers or ():
                c_var = getattr(c, "variant", None)
                if c_var and c_var not in assigned:
                    assigned.append(c_var)
                _walk(getattr(c, "sub_containers", None))

        _walk(configuration.containers)
        proj_variants = list(getattr(project_context, "variants", None) or [])
        if not assigned and len(proj_variants) <= 1:
            return [None]

        views: List[Optional[str]] = []
        for v in proj_variants or [DEFAULT_VARIANT]:
            if v and v not in views:
                views.append(v)
        for v in assigned:
            if v not in views:
                views.append(v)
        return views or [None]

    @staticmethod
    def _visible_in_variant(container: EcucContainerValue, variant: Optional[str]) -> bool:
        if variant is None:
            return True
        c_var = getattr(container, "variant", None)
        return c_var in (None, "") or c_var == variant

    def validate(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, project_context=None) -> ValidationResult:
        from ...generator.eb.enable_conditions import EnableConditionEvaluator

        result = ValidationResult()
        evaluator = EnableConditionEvaluator(module_def, configuration, project_context)
        variant_views = self._collect_variant_views(configuration, project_context)
        is_post_build = str(
            getattr(configuration, "implementation_config_variant", "") or ""
        ).startswith("VARIANT-POST-BUILD")

        # Validate top-level containers
        for container_name, container_def in module_def.containers.items():
            self._validate_top_level_multiplicity(
                container_def, configuration, result, evaluator, variant_views
            )

        # Validate nested containers and post-build variant multiplicity constraints
        for container in configuration.containers:
            self._validate_container_multiplicity(
                container, module_def, configuration, result, evaluator, variant_views, is_post_build
            )

        return result

    def _validate_top_level_multiplicity(self, container_def: EcucContainerDef,
                                         configuration: EcucModuleConfiguration,
                                         result: ValidationResult,
                                         evaluator=None,
                                         variant_views: Optional[List[Optional[str]]] = None):
        """Validate multiplicity of top-level containers"""
        views = variant_views if variant_views is not None else [None]
        matching = [
            c for c in configuration.containers
            if self._definition_refs_match(c.definition_ref, container_def.definition_ref, container_def.short_name)
        ]

        for variant in views:
            count = sum(1 for c in matching if self._visible_in_variant(c, variant))
            details = f"Multiplicity: {container_def.multiplicity_str}"
            if variant is not None:
                details += f" [Variant: {variant}]"

            # Check lower bound
            if count < container_def.lower_multiplicity:
                disabled = (
                    (count == 0 and getattr(container_def, "default_disabled", False))
                    or (evaluator is not None and not evaluator.is_container_enabled(None, container_def))
                )
                if not disabled:
                    result.add_message(self._create_error(
                        f"Container '{container_def.short_name}' requires at least "
                        f"{container_def.lower_multiplicity} instance(s), but only {count} exist",
                        details=details,
                        suggested_fix=f"Add {container_def.lower_multiplicity - count} more instance(s)"
                    ))

            # Check upper bound
            if container_def.upper_multiplicity != -1 and count > container_def.upper_multiplicity:
                result.add_message(self._create_error(
                    f"Container '{container_def.short_name}' allows at most "
                    f"{container_def.upper_multiplicity} instance(s), but {count} exist",
                    details=details,
                    suggested_fix=f"Remove {count - container_def.upper_multiplicity} instance(s)"
                ))

    def _validate_container_multiplicity(self, container: EcucContainerValue,
                                         module_def: EcucModuleDef,
                                         configuration: EcucModuleConfiguration,
                                         result: ValidationResult,
                                         evaluator=None,
                                         variant_views: Optional[List[Optional[str]]] = None,
                                         is_post_build: bool = False):
        """Recursively validate multiplicity of sub-containers"""
        container_def = self._get_container_def(container.definition_ref, module_def)
        if not container_def:
            return

        if (
            is_post_build
            and getattr(container, "variant", None) not in (None, "")
            and not getattr(container_def, "post_build_variant_multiplicity", False)
        ):
            result.add_message(self._create_warning(
                f"Container '{container.short_name}' is assigned to variant '{container.variant}', "
                f"but definition '{container_def.short_name}' has POST-BUILD-VARIANT-MULTIPLICITY=false",
                container_path=container.get_path(),
                details=f"IMPLEMENTATION-CONFIG-VARIANT: {configuration.implementation_config_variant}",
                suggested_fix="Clear the container's variant assignment or use a definition with POST-BUILD-VARIANT-MULTIPLICITY=true",
            ))

        views = variant_views if variant_views is not None else [None]
        applicable_views = [v for v in views if self._visible_in_variant(container, v)]
        if not applicable_views:
            applicable_views = [None]

        # Validate each sub-container definition's multiplicity
        for sub_name, sub_def in container_def.sub_containers.items():
            matching = [
                sc for sc in container.sub_containers
                if self._definition_refs_match(sc.definition_ref, sub_def.definition_ref, sub_def.short_name)
            ]

            for variant in applicable_views:
                count = sum(1 for sc in matching if self._visible_in_variant(sc, variant))
                details = f"Multiplicity: {sub_def.multiplicity_str}"
                if variant is not None:
                    details += f" [Variant: {variant}]"

                # Check lower bound
                if count < sub_def.lower_multiplicity:
                    disabled = (
                        (count == 0 and getattr(sub_def, "default_disabled", False))
                        or (evaluator is not None and not evaluator.is_container_enabled(container, sub_def))
                    )
                    if not disabled:
                        result.add_message(self._create_error(
                            f"Sub-container '{sub_def.short_name}' requires at least "
                            f"{sub_def.lower_multiplicity} instance(s), but only {count} exist",
                            container_path=container.get_path(),
                            details=details,
                            suggested_fix=f"Add {sub_def.lower_multiplicity - count} more instance(s)"
                        ))

                # Check upper bound
                if sub_def.upper_multiplicity != -1 and count > sub_def.upper_multiplicity:
                    result.add_message(self._create_error(
                        f"Sub-container '{sub_def.short_name}' allows at most "
                        f"{sub_def.upper_multiplicity} instance(s), but {count} exist",
                        container_path=container.get_path(),
                        details=details,
                        suggested_fix=f"Remove {count - sub_def.upper_multiplicity} instance(s)"
                    ))

        # Recursively validate sub-containers
        for sub_container in container.sub_containers:
            self._validate_container_multiplicity(
                sub_container, module_def, configuration, result, evaluator, variant_views, is_post_build
            )
    
    def _get_container_def(self, definition_ref: str, module_def: EcucModuleDef) -> Optional[EcucContainerDef]:
        """Get container definition from reference path"""
        if not definition_ref:
            return None

        # Handle relative paths
        if not definition_ref.startswith('/'):
            return module_def.get_container_def(definition_ref)

        from ..model.definition_refs import module_relative

        # Exact prefix match against the module's actual AR path (handles multi-segment vendor packages)
        ar_path = (getattr(module_def, 'ar_path', '') or '').rstrip('/')
        if ar_path and definition_ref.startswith(ar_path + '/'):
            rel_exact = definition_ref[len(ar_path) + 1:]
            if rel_exact:
                hit = module_def.get_container_def(rel_exact)
                if hit is not None:
                    return hit

        rel = module_relative(definition_ref, module_def.short_name)
        if rel:
            hit = module_def.get_container_def(rel)
            if hit is not None:
                return hit

        parts = definition_ref.split('/')
        # Fallback: assume format /Package/Module/Container...
        if len(parts) >= 4:
            relative_path = '/'.join(parts[3:])
            if relative_path:
                return module_def.get_container_def(relative_path)

        return None
    
    def _definition_refs_match(self, config_ref: str, def_ref: str, short_name: str) -> bool:
        """Check if a config definition_ref matches a module definition's definition_ref.

        First tries exact match, then falls back to matching by container short_name
        (last path segment), to handle EB Tresos projects with vendor-specific paths.
        EB Tresos also embeds the instance index in the definition_ref last segment
        (e.g. ``OsCoreIdMappingConfig_0``), so we also try after stripping a
        trailing ``_<digits>`` suffix.
        """
        import re

        # Try exact match first
        if config_ref == def_ref:
            return True

        # Fall back to matching by short_name (last segment of path)
        config_short_name = config_ref.rstrip('/').split('/')[-1] if config_ref else ""
        if config_short_name == short_name:
            return True

        # EB Tresos: strip trailing instance-index suffix (_0, _U12, _Ch1, …)
        stripped = re.sub(r'_\w*\d+$', '', config_short_name)
        return stripped == short_name

"""
EB Tresos Compatible Template Engine
Wrapper around the verified generator.eb.renderer implementation.
"""
from typing import Dict, Any, Optional, Tuple
from pathlib import Path

from ..core.model.configuration_model import EcucModuleConfiguration
from ..core.model.definition_model import (
    EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucReferenceDef, EcucParameterType
)
from .eb.renderer import Renderer

class EBTemplateEngine:
    """
    Template engine compatible with EB Tresos syntax.
    Wraps the robust implementation in autosar_configurator.generator.eb.
    """
    
    def __init__(self, strict: bool = True, template_dir: Optional[Path] = None,
                 include_search_paths: Optional[list] = None,
                 priority_include_paths: Optional[list] = None,
                 include_template_parent: bool = True):
        self.template_dir = template_dir

        # Build include search paths:
        # 1. explicit priority_include_paths (e.g. variant/project overlays)
        # 2. template_dir (and optional parent)
        # 3. include_search_paths (additional fallback directories)
        search_paths = []
        seen = set()

        def _append_unique(path_item) -> None:
            if not path_item:
                return
            p = Path(path_item)
            try:
                key = p.resolve()
            except OSError:
                key = p
            if key not in seen:
                seen.add(key)
                search_paths.append(p)

        for prio in priority_include_paths or []:
            _append_unique(prio)
        if template_dir:
            _append_unique(template_dir)
            if include_template_parent:
                # Add parent directory to allow includes from module root (e.g., from include/ to root)
                _append_unique(Path(template_dir).parent)
        for extra in include_search_paths or []:
            _append_unique(extra)

        self.renderer = Renderer(strict=strict, template_dir=template_dir, include_search_paths=search_paths)
        self.initialized_modules: Dict[str, Any] = {}
        # Result of the definition ENABLE conditions (computed per active variant state)
        self.enable_result = None
        self._enable_result_key = None

    def add_module(
        self,
        module_def: EcucModuleDef,
        configuration: EcucModuleConfiguration,
        variant: Optional[str] = None,
        variant_overrides: Optional[Dict[str, Any]] = None,
    ):
        """Add a module to the engine's symbol table for cross-module access."""
        module_name = module_def.short_name
        ov_sig = (
            tuple(sorted((k, repr(v)) for k, v in variant_overrides.items()))
            if isinstance(variant_overrides, dict) and variant_overrides
            else ()
        )
        state_key = (id(module_def), id(configuration), variant, ov_sig)
        if self.initialized_modules.get(module_name) != state_key:
            self.renderer.load_module(
                module_def, configuration, variant=variant, variant_overrides=variant_overrides
            )
            self.initialized_modules[module_name] = state_key
            self.enable_result = None

    def render(self, template: str, context: Dict[str, Any], ecu_resources: Optional[Dict[str, Any]] = None, template_file: Optional[str] = None) -> str:
        """Render template with given context.
        
        Args:
            template: Template string
            context: Dictionary containing:
                     - 'module_def': EcucModuleDef
                     - 'configuration': EcucModuleConfiguration
                     - 'module_name': optional str
                     - 'all_modules': Optional[Dict[str, Tuple[EcucModuleDef, EcucModuleConfiguration]]]
            ecu_resources: Optional ECU resources dictionary
            template_file: Optional path to the template file
                     
        Returns:
            Rendered string
        """
        # Determine module name for context
        module_name = context.get('module_name')
        if not module_name and context.get('configuration'):
            # Safe access for mocks
            config = context.get('configuration')
            module_name = getattr(config, 'short_name', None)

        # Load all modules if provided, for cross-module lookup
        all_modules = context.get('all_modules', {})
        active_variant = context.get('active_variant')
        variant_overrides = context.get('variant_overrides')
        project_variants = context.get('project_variants')

        # Inject variant state before loading modules and evaluating ENABLE conditions so
        # variant:* functions resolve consistently in both ENABLE expressions and templates.
        eff_variant = active_variant or ""
        eff_variants = [v for v in (project_variants or []) if v]
        self.renderer._variant = eff_variant
        self.renderer._variants = eff_variants
        if hasattr(self.renderer, '_builtins') and self.renderer._builtins:
            self.renderer._builtins.set_variant(eff_variant)
            self.renderer._builtins.set_variants(eff_variants)

        enable_key = (eff_variant, tuple(eff_variants))
        if self._enable_result_key is not None and self._enable_result_key != enable_key:
            # Force clean tree reload because apply_enable_conditions prunes disabled nodes in-place
            self.enable_result = None
            self.initialized_modules.clear()

        if all_modules:
            for m_name, (m_def, m_config) in all_modules.items():
                mod_ov = variant_overrides if m_name == module_name else None
                self.add_module(m_def, m_config, variant=active_variant, variant_overrides=mod_ov)

        # Mark modules that have templates as MODULE-DEFs for XDM enumeration
        template_module_names = context.get('template_module_names')
        if template_module_names:
            for m_name in template_module_names:
                self.renderer.symbol_table.mark_template_module(m_name)

        # Ensure current module is loaded
        module_def = context.get('module_def')
        configuration = context.get('configuration')
        if configuration and module_def:
            self.add_module(
                module_def, configuration, variant=active_variant, variant_overrides=variant_overrides
            )

        # Items whose definition ENABLE condition is false are not visible to templates
        if self.enable_result is None or self._enable_result_key != enable_key:
            from .eb.enable_conditions import apply_enable_conditions
            defs = [m_def for m_def, _ in (all_modules or {}).values()] + [module_def]
            self.enable_result = apply_enable_conditions(
                self.renderer, [d for d in defs if d is not None], ecu_resources)
            self._enable_result_key = enable_key

        # Extract extra variables from context (excluding model objects)
        # Keep 'configuration' if 'module_def' is not present (e.g. mock context in unit tests)
        extra_vars = {k: v for k, v in context.items()
                     if k not in ('module_def', 'module_name') and (k != 'configuration' or not context.get('module_def'))}
        
        # Inject standard Tresos variables if not provided
        if 'moduleReleaseVer' not in extra_vars:
            # Try to get from module_def if available, otherwise default to a safe value
            # For now, we'll use a heuristic or common value
            extra_vars['moduleReleaseVer'] = "AR 4.4.0" 
        if 'moduleSoftwareVer' not in extra_vars:
            extra_vars['moduleSoftwareVer'] = "1.2.0"

        return self.renderer.render(template, module_name=module_name, initial_variables=extra_vars, ecu_resources=ecu_resources, template_file=template_file)

    def render_file(self, template_path: str, context: Dict[str, Any], ecu_resources: Optional[Dict[str, Any]] = None) -> str:
        """Render template from file"""
        with open(template_path, 'r', encoding='utf-8') as f:
            template = f.read()
        return self.render(template, context, ecu_resources=ecu_resources, template_file=template_path)

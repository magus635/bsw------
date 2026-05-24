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
    
    def __init__(self, strict: bool = True, template_dir: Optional[Path] = None):
        self.template_dir = template_dir
        
        # Build include search paths
        search_paths = []
        if template_dir:
            search_paths.append(template_dir)
            # Add parent directory to allow includes from module root (e.g., from include/ to root)
            search_paths.append(template_dir.parent)
            
        self.renderer = Renderer(strict=strict, template_dir=template_dir, include_search_paths=search_paths)
        self.initialized_modules = set()
        
    def add_module(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, variant: Optional[str] = None):
        """Add a module to the engine's symbol table for cross-module access."""
        module_name = module_def.short_name
        
        cache_key = (module_name, variant)
        if cache_key not in self.initialized_modules:
            self.renderer.load_module(module_def, configuration, variant=variant)
            self.initialized_modules.add(cache_key)

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
        
        if all_modules:
            for m_name, (m_def, m_config) in all_modules.items():
                self.add_module(m_def, m_config, variant=active_variant)

        # Mark modules that have templates as MODULE-DEFs for XDM enumeration
        template_module_names = context.get('template_module_names')
        if template_module_names:
            for m_name in template_module_names:
                self.renderer.symbol_table.mark_template_module(m_name)

        # Ensure current module is loaded
        module_def = context.get('module_def')
        configuration = context.get('configuration')
        if configuration and module_def:
            self.add_module(module_def, configuration, variant=active_variant)

            
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

        # Ensure variant is set on renderer before rendering
        # This is needed because each template file may get a fresh EBTemplateEngine
        if active_variant:
            self.renderer._variant = active_variant
            # Also set on builtins if already initialized
            if hasattr(self.renderer, '_builtins') and self.renderer._builtins:
                self.renderer._builtins.set_variant(active_variant)

        return self.renderer.render(template, module_name=module_name, initial_variables=extra_vars, ecu_resources=ecu_resources, template_file=template_file)

    def render_file(self, template_path: str, context: Dict[str, Any], ecu_resources: Optional[Dict[str, Any]] = None) -> str:
        """Render template from file"""
        with open(template_path, 'r', encoding='utf-8') as f:
            template = f.read()
        return self.render(template, context, ecu_resources=ecu_resources, template_file=template_path)

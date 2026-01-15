"""
EB Tresos Compatible Template Engine
Wrapper around the verified generator.eb.renderer implementation.
"""
from typing import Dict, Any, Optional
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
        self.renderer = Renderer(strict=strict, template_dir=template_dir)
        self.initialized_modules = set()
        
    def add_module(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration, variant: Optional[str] = None):
        """Add a module to the engine's symbol table for cross-module access."""
        module_name = module_def.short_name
        # If variant is different, we might need to reload? 
        # For now, if it's already in initialized_modules, we skip.
        # But for variant support, we should allow reloading if variant changes.
        cache_key = (module_name, variant)
        if cache_key not in self.initialized_modules:
            self.renderer.load_module(module_def, configuration, variant=variant)
            self.initialized_modules.add(cache_key)


    def render(self, template: str, context: Dict[str, Any]) -> str:
        """Render template with given context.
        
        Args:
            template: Template string
            context: Dictionary containing:
                     - 'module_def': EcucModuleDef
                     - 'configuration': EcucModuleConfiguration
                     - 'module_name': optional str
                     - 'all_modules': Optional[Dict[str, Tuple[EcucModuleDef, EcucModuleConfiguration]]]
                     
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

        # Ensure current module is loaded
        module_def = context.get('module_def')
        configuration = context.get('configuration')
        if configuration and module_def:
            self.add_module(module_def, configuration, variant=active_variant)

            
        # Extract extra variables from context (excluding model objects)
        extra_vars = {k: v for k, v in context.items() 
                     if k not in ('module_def', 'configuration', 'module_name')}
        
        return self.renderer.render(template, module_name=module_name, initial_variables=extra_vars)

    def render_file(self, template_path: str, context: Dict[str, Any]) -> str:
        """Render template from file"""
        with open(template_path, 'r', encoding='utf-8') as f:
            template = f.read()
        return self.render(template, context)


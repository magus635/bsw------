"""
EB Tresos Compatible Template Engine
Wrapper around the verified generator.eb.renderer implementation.
"""
from typing import Dict, Any, Optional
from pathlib import Path

from ..core.model.configuration_model import EcucModuleConfiguration
from ..core.model.definition_model import EcucModuleDef
from .eb.renderer import Renderer

class EBTemplateEngine:
    """
    Template engine compatible with EB Tresos syntax.
    Wraps the robust implementation in autosar_configurator.generator.eb.
    """
    
    def __init__(self, strict: bool = True):
        self.renderer = Renderer(strict=strict)
        self.initialized = False
        
    def render(self, template: str, context: Dict[str, Any]) -> str:
        """Render template with given context.
        
        Args:
            template: Template string
            context: Dictionary containing:
                     - 'module_def': EcucModuleDef
                     - 'configuration': EcucModuleConfiguration
                     - 'module_name': optional str
                     
        Returns:
            Rendered string
        """
        # Auto-initialize if context provides necessary models
        if not self.initialized:
            module_def = context.get('module_def')
            configuration = context.get('configuration')
            
            if module_def and configuration:
                self.renderer.load_module(module_def, configuration)
                self.initialized = True
        
        # Determine module name for context
        module_name = context.get('module_name')
        if not module_name and context.get('configuration'):
            module_name = context['configuration'].short_name
            
        # Extract extra variables from context (excluding model objects)
        extra_vars = {k: v for k, v in context.items() 
                     if k not in ('module_def', 'configuration', 'module_name')}
        
        # Determine initial variables to pass (mapped to Renderer's expected format if needed)
        # The Renderer.render method supports initial_variables
        
        return self.renderer.render(template, module_name=module_name, initial_variables=extra_vars)

    def render_file(self, template_path: str, context: Dict[str, Any]) -> str:
        """Render template from file"""
        with open(template_path, 'r', encoding='utf-8') as f:
            template = f.read()
        return self.render(template, context)


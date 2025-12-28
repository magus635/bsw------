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
        # Determine module name for context
        module_name = context.get('module_name')
        if not module_name and context.get('configuration'):
            # Safe access for mocks
            config = context.get('configuration')
            module_name = getattr(config, 'short_name', None)

        if not self.initialized:
            module_def = context.get('module_def')
            configuration = context.get('configuration')
            
            if configuration:
                if not module_def:
                    # Create dummy definition if missing (for unit tests)
                    module_def = EcucModuleDef(
                        short_name=module_name or 'Unknown',
                        definition_ref=getattr(configuration, 'definition_ref', '/Def')
                    )
                    # Add structure from configuration to the dummy definition
                    def add_structure(parent_val, parent_def):
                        # Add parameters
                        params = getattr(parent_val, 'parameter_values', {}) or {}
                        if isinstance(params, dict):
                            for name in params:
                                parent_def.add_parameter(EcucParameterDef(
                                    short_name=name,
                                    param_type=EcucParameterType.INTEGER,
                                    definition_ref=f"{parent_def.definition_ref}/{name}"
                                ))
                        
                        # Add references
                        refs = getattr(parent_val, 'reference_values', {}) or {}
                        if isinstance(refs, dict):
                            for name in refs:
                                parent_def.add_reference(EcucReferenceDef(
                                    short_name=name,
                                    definition_ref=f"{parent_def.definition_ref}/{name}",
                                    destination_ref="/Def" # Dummy
                                ))

                        # Add containers/sub-containers
                        containers = getattr(parent_val, 'containers', []) or \
                                     getattr(parent_val, 'sub_containers', []) or \
                                     getattr(parent_val, 'children', [])
                        
                        if isinstance(containers, dict):
                            for name, child in containers.items():
                                if hasattr(child, 'value') and not hasattr(child, 'value_ref'): # parameter
                                    parent_def.add_parameter(EcucParameterDef(
                                        short_name=name,
                                        param_type=EcucParameterType.INTEGER,
                                        definition_ref=f"{parent_def.definition_ref}/{name}"
                                    ))
                                elif hasattr(child, 'value_ref'): # reference
                                    parent_def.add_reference(EcucReferenceDef(
                                        short_name=name,
                                        definition_ref=f"{parent_def.definition_ref}/{name}",
                                        destination_ref="/Def"
                                    ))
                                else:
                                    cont_def = EcucContainerDef(
                                        short_name=name,
                                        definition_ref=f"{parent_def.definition_ref}/{name}"
                                    )
                                    parent_def.add_container(cont_def)
                                    add_structure(child, cont_def)
                        elif isinstance(containers, list):
                            for container in containers:
                                cont_def = EcucContainerDef(
                                    short_name=getattr(container, 'short_name', 'Unknown'),
                                    definition_ref=getattr(container, 'definition_ref', f"{parent_def.definition_ref}/Child")
                                )
                                parent_def.add_container(cont_def)
                                add_structure(container, cont_def)
                    
                    add_structure(configuration, module_def)
                self.renderer.load_module(module_def, configuration)
                self.initialized = True
            
        # Extract extra variables from context (excluding model objects)
        extra_vars = {k: v for k, v in context.items() 
                     if k not in ('module_def', 'configuration', 'module_name')}
        
        return self.renderer.render(template, module_name=module_name, initial_variables=extra_vars)

    def render_file(self, template_path: str, context: Dict[str, Any]) -> str:
        """Render template from file"""
        with open(template_path, 'r', encoding='utf-8') as f:
            template = f.read()
        return self.render(template, context)


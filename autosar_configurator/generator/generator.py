"""
Code Generator
Generates C/C++ code from ECUC configuration
"""
from typing import Dict, Any, List
from pathlib import Path
from ..core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from ..core.model.definition_model import EcucModuleDef
from .template_engine import TemplateEngine, TemplateLoader


class CodeGenerator:
    """Main code generator for AUTOSAR BSW modules"""
    
    def __init__(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration):
        """Initialize generator
        
        Args:
            module_def: Module definition
            configuration: Configuration instance
        """
        self.module_def = module_def
        self.configuration = configuration
        self.template_engine = TemplateEngine()
        self.template_loader = TemplateLoader()
        
    def generate_all(self, output_dir: Path):
        """Generate all code files
        
        Args:
            output_dir: Directory to write generated files
        """
        output_dir = Path(output_dir)
        output_dir.mkdir(parents=True, exist_ok=True)
        
        # Generate configuration header
        self.generate_config_header(output_dir)
        
        # Generate PBcfg source
        self.generate_pbcfg_source(output_dir)
        
    def generate_config_header(self, output_dir: Path):
        """Generate Xxx_Cfg.h file
        
        Args:
            output_dir: Output directory
        """
        module_name = self.configuration.short_name
        
        # Prepare context
        context = self._prepare_context()
        context['header_guard'] = f"{module_name.upper()}_CFG_H"
        
        # Load and render template
        try:
            template = self.template_loader.load('Module_Cfg.h.tpl')
        except FileNotFoundError:
            # Use inline template if file not found
            template = self._get_default_cfg_header_template()
            
        rendered = self.template_engine.render(template, context)
        
        # Write to file
        output_file = output_dir / f"{module_name}_Cfg.h"
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(rendered)
            
    def generate_pbcfg_source(self, output_dir: Path):
        """Generate Xxx_PBcfg.c file
        
        Args:
            output_dir: Output directory
        """
        module_name = self.configuration.short_name
        
        # Prepare context
        context = self._prepare_context()
        
        # Load and render template
        try:
            template = self.template_loader.load('Module_PBcfg.c.tpl')
        except FileNotFoundError:
            template = self._get_default_pbcfg_source_template()
            
        rendered = self.template_engine.render(template, context)
        
        # Write to file
        output_file = output_dir / f"{module_name}_PBcfg.c"
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(rendered)
            
    def _prepare_context(self) -> Dict[str, Any]:
        """Prepare rendering context from configuration
        
        Returns:
            Dictionary with template variables
        """
        context = {
            'module_name': self.configuration.short_name,
            'containers': []
        }
        
        # Add top-level containers
        for container in self.configuration.containers:
            context['containers'].append(self._serialize_container(container))
            
        return context
    
    def _serialize_container(self, container: EcucContainerValue) -> Dict[str, Any]:
        """Serialize container to dict for template
        
        Args:
            container: Container to serialize
            
        Returns:
            Dictionary representation
        """
        result = {
            'name': container.short_name,
            'parameters': [],
            'sub_containers': []
        }
        
        # Add parameters
        for param_name, param_value in container.parameter_values.items():
            result['parameters'].append({
                'name': param_name,
                'value': param_value.value
            })
            
        # Add sub-containers recursively
        for sub in container.sub_containers:
            result['sub_containers'].append(self._serialize_container(sub))
            
        return result
    
    def _get_default_cfg_header_template(self) -> str:
        """Get default configuration header template"""
        return """/**
 * @file {{ module_name }}_Cfg.h
 * @brief Configuration header for {{ module_name }} module
 * 
 * @note Auto-generated file - DO NOT EDIT
 */

#ifndef {{ header_guard }}
#define {{ header_guard }}

/*===========================================================================
 *                              INCLUDES
 *===========================================================================*/
#include "{{ module_name }}.h"

/*===========================================================================
 *                       CONFIGURATION PARAMETERS
 *===========================================================================*/

{% for container in containers %}
/* {{ container.name }} */
{% for param in container.parameters %}
#define {{ module_name }}_{{ container.name }}_{{ param.name }}  {{ param.value }}
{% endfor %}

{% endfor %}

#endif /* {{ header_guard }} */
"""
    
    def _get_default_pbcfg_source_template(self) -> str:
        """Get default PBcfg source template"""
        return """/**
 * @file {{ module_name }}_PBcfg.c
 * @brief Post-Build configuration for {{ module_name }} module
 * 
 * @note Auto-generated file - DO NOT EDIT
 */

/*===========================================================================
 *                              INCLUDES
 *===========================================================================*/
#include "{{ module_name }}_Cfg.h"

/*===========================================================================
 *                     CONFIGURATION STRUCTURES
 *===========================================================================*/

{% for container in containers %}
/* Configuration for {{ container.name }} */
const {{ module_name }}_{{ container.name }}_ConfigType {{ module_name }}_{{ container.name }}_Config = {
{% for param in container.parameters %}
    .{{ param.name }} = {{ param.value }},
{% endfor %}
};

{% endfor %}
"""

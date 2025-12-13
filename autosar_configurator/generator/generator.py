"""
Code Generator
Generates C/C++ code from ECUC configuration using EB Tresos Templates
"""
from typing import Dict, Any, List
from pathlib import Path
from ..core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from ..core.model.definition_model import EcucModuleDef
# from .template_engine import TemplateEngine, TemplateLoader # Legacy
from .eb_template_engine import EBTemplateEngine  # New verified engine


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
        
        # Initialize EB Engine
        self.template_engine = EBTemplateEngine(strict=False) 
        # Note: strict=False for robustness during initial integration
        
    def generate_all(self, output_dir: Path):
        """Generate all code files
        
        Args:
            output_dir: Directory to write generated files
        """
        output_dir = Path(output_dir)
        output_dir.mkdir(parents=True, exist_ok=True)
        
        # In a real EB Tresos flow, the tool renders whatever templates are provided.
        # Here we mimic the previous behavior of generating Cfg.h and PBcfg.c
        # assuming standard template files exist or using default fallback.
        
        self.generate_config_header(output_dir)
        self.generate_pbcfg_source(output_dir)
        
    def generate_config_header(self, output_dir: Path):
        """Generate Xxx_Cfg.h file"""
        module_name = self.configuration.short_name
        
        # Context for EB Engine needs the models
        context = {
            'module_def': self.module_def,
            'configuration': self.configuration,
            'module_name': module_name
        }
        
        # Try to use a template file if it exists
        # In this environment, we might expect templates in a 'templates' dir?
        # For now, we use our Hardcoded Defaults converted to EB Syntax
        # to ensure the app continues to work without external files.
        
        template = self._get_default_cfg_header_template_eb(module_name)
            
        rendered = self.template_engine.render(template, context)
        
        output_file = output_dir / f"{module_name}_Cfg.h"
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(rendered)
            
    def generate_pbcfg_source(self, output_dir: Path):
        """Generate Xxx_PBcfg.c file"""
        module_name = self.configuration.short_name
        
        context = {
            'module_def': self.module_def,
            'configuration': self.configuration,
            'module_name': module_name
        }
        
        template = self._get_default_pbcfg_source_template_eb(module_name)
            
        rendered = self.template_engine.render(template, context)
        
        output_file = output_dir / f"{module_name}_PBcfg.c"
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(rendered)
    
    # --- Default Templates (EB Syntax) ---
    
    def _get_default_cfg_header_template_eb(self, module_name: str) -> str:
        """Get default Cfg header in EB syntax"""
        # A generic dumper of parameters is hard in EB syntax without knowing the structure.
        # But we can iterate the module roughly if we wanted.
        # For safety/simplicity in this fallback, we produce a minimal valid header.
        guard = f"{module_name.upper()}_CFG_H"
        return f"""/**
 * @file {module_name}_Cfg.h
 * @brief Configuration header for {module_name} module
 * @note Auto-generated file by EB Template Engine
 */

#ifndef {guard}
#define {guard}

#include "{module_name}.h"

/* Generic Parameter Dump */
[!LOOP "{module_name}/*"!]
  /* Container: [!"node:name(.)"!] */
  [!LOOP "node:order(./*)"!]
    [!IF "node:isparameter(.)"!]
#define {module_name}_[!"node:name(..)"!]_[!"node:name(.)"!]  [!"node:value(.)"!]
    [!ENDIF!]
  [!ENDLOOP!]
[!ENDLOOP!]

#endif /* {guard} */
"""

    def _get_default_pbcfg_source_template_eb(self, module_name: str) -> str:
        return f"""/**
 * @file {module_name}_PBcfg.c
 * @brief Post-Build configuration for {module_name} module
 */

#include "{module_name}_Cfg.h"

/* Generic Configuration Structure Dump */
/* Note: Functionality limited in generic fallback */
/* Please provide explicit .c.tt template for full generation */
"""


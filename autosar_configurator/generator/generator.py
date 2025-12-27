"""
Code Generator
Generates C/C++ code from ECUC configuration using EB Tresos Templates
Routes parameters to different files based on config_class:
- PRE-COMPILE -> Cfg.h (macro definitions)
- LINK-TIME -> Lcfg.c (const struct members)
- POST-BUILD -> PBcfg.c (PB struct members)

Improvements:
- External template files support
- Variant-aware generation
- Logging for debugging
"""
import hashlib
import json
import logging
from typing import Dict, Any, List, Tuple, Optional
from pathlib import Path
from ..core.model.configuration_model import EcucModuleConfiguration, EcucContainerValue
from ..core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef
from .eb_template_engine import EBTemplateEngine

# Setup logger
logger = logging.getLogger(__name__)


class ConfigClass:
    """Constants for config class types"""
    PRE_COMPILE = "PRE-COMPILE"
    LINK_TIME = "LINK-TIME"
    POST_BUILD = "POST-BUILD"


class CodeGenerator:
    """Main code generator for AUTOSAR BSW modules"""
    
    # Default template directory (relative to this file)
    DEFAULT_TEMPLATE_DIR = Path(__file__).parent / "templates"
    
    def __init__(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration,
                 user_template_dir: Optional[Path] = None, variant_overrides: Optional[Dict[str, Any]] = None):
        """Initialize generator
        
        Args:
            module_def: Module definition
            configuration: Configuration instance
            user_template_dir: Optional user-defined template directory (searched first)
            variant_overrides: Optional dict of param_path -> value for variant-specific values
        """
        self.module_def = module_def
        self.configuration = configuration
        self.user_template_dir = user_template_dir
        self.variant_overrides = variant_overrides or {}
        
        # Initialize EB Engine
        self.template_engine = EBTemplateEngine(strict=False)
        
        logger.info(f"CodeGenerator initialized for module: {configuration.short_name}")
        if user_template_dir:
            logger.info(f"User template directory: {user_template_dir}")
        if variant_overrides:
            logger.info(f"Variant overrides: {len(variant_overrides)} parameters")
    
    def _load_template(self, template_name: str) -> str:
        """Load template from file system.
        
        Search order:
        1. User template directory (if specified)
        2. Built-in templates directory
        
        NOTE: Currently disabled because existing templates use Jinja2 syntax
        which is incompatible with EBTemplateEngine (expects EB Tresos syntax).
        TODO: Convert templates to EB Tresos syntax or use Jinja2 engine for simple templates.
        
        Args:
            template_name: Name of template file (e.g., "Module_Cfg.h.tpl")
            
        Returns:
            Template content as string, or None to use fallback
        """
        # TODO: Enable external templates after syntax conversion
        # For now, always use fallback hardcoded templates
        logger.debug(f"Using fallback template for: {template_name}")
        return None
        
    def generate_all(self, output_dir: Path, force: bool = False, variant: Optional[str] = None) -> bool:
        """Generate all code files based on config_class routing
        
        Args:
            output_dir: Directory to write generated files
            force: Force generation even if fingerprint matches
            variant: Optional variant name for variant-specific output directory
            
        Returns:
            bool: True if files were generated, False if skipped
        """
        output_dir = Path(output_dir)
        
        # Create variant-specific subdirectory if variant specified
        if variant:
            output_dir = output_dir / variant
            logger.info(f"Generating for variant: {variant}")
        
        output_dir.mkdir(parents=True, exist_ok=True)
        
        # 1. Calculate current fingerprint (include variant name)
        current_hash = self._calculate_fingerprint(variant)
        meta_file = output_dir / f".{self.configuration.short_name}.meta"
        
        # 2. Check overlap with previous generation
        if not force and meta_file.exists():
            try:
                with open(meta_file, 'r') as f:
                    meta = json.load(f)
                
                # Check if hash matches and files exist
                if meta.get('hash') == current_hash:
                    # Verify files exist
                    files_exist = True
                    for fname in meta.get('files', []):
                        if not (output_dir / fname).exists():
                            files_exist = False
                            break
                    
                    if files_exist:
                        logger.info(f"Skipping generation - configuration unchanged")
                        return False  # Skip generation
            except Exception as e:
                logger.warning(f"Error reading meta file: {e}")
        
        # 3. Generate files
        generated_files = []
        
        logger.info(f"Generating code for {self.configuration.short_name}...")
        
        self.generate_config_header(output_dir)   # PRE-COMPILE params
        generated_files.append(f"{self.configuration.short_name}_Cfg.h")
        
        self.generate_lcfg_source(output_dir)     # LINK-TIME params
        generated_files.append(f"{self.configuration.short_name}_Lcfg.c")

        self.generate_pbcfg_source(output_dir)    # POST-BUILD params
        generated_files.append(f"{self.configuration.short_name}_PBcfg.c")
        
        # 4. Save new fingerprint
        try:
            with open(meta_file, 'w') as f:
                json.dump({
                    'hash': current_hash,
                    'variant': variant,
                    'timestamp': str(self.configuration.last_saved) if self.configuration.last_saved else '',
                    'files': generated_files
                }, f)
        except Exception as e:
            logger.warning(f"Error writing meta file: {e}")
        
        logger.info(f"Generated {len(generated_files)} files to {output_dir}")
        return True

    def _calculate_fingerprint(self, variant: Optional[str] = None) -> str:
        """Calculate a hash of the current configuration content"""
        # We build a stable string representation of the config
        parts = []
        
        # Add module info
        parts.append(f"Module:{self.configuration.short_name}")
        
        # Add variant info
        if variant:
            parts.append(f"Variant:{variant}")
        
        # Recursively add containers (sorted for stability)
        def process_container(container: EcucContainerValue):
            parts.append(f"C:{container.short_name}")
            
            # Parameters
            for name in sorted(container.parameter_values.keys()):
                val = container.parameter_values[name]
                # Check for variant override
                param_path = f"{container.get_path()}.{name}"
                if param_path in self.variant_overrides:
                    parts.append(f"P:{name}={self.variant_overrides[param_path]}")
                else:
                    parts.append(f"P:{name}={val.value}")
                
            # References
            for name in sorted(container.reference_values.keys()):
                ref = container.reference_values[name]
                parts.append(f"R:{name}={ref.value_ref}")
                
            # Sub-containers
            for sub in container.sub_containers:
                process_container(sub)
                
        # Top level containers
        for container in self.configuration.containers:
            process_container(container)
            
        # Hash the result
        content = "|".join(parts)
        return hashlib.sha256(content.encode('utf-8')).hexdigest()
        
    def _get_params_by_config_class(self, config_class: str) -> List[Tuple[str, str, Any]]:
        """Get parameters filtered by config_class, applying variant overrides
        
        Args:
            config_class: One of PRE-COMPILE, LINK-TIME, POST-BUILD
            
        Returns:
            List of tuples (container_name, param_name, param_value)
        """
        params = []
        
        def collect_from_container(container: EcucContainerValue, container_def: EcucContainerDef, path: str):
            # Iterate over all parameter definitions (to handle default values / overlay)
            # Sort by param name for deterministic output
            for param_name in sorted(container_def.parameters.keys()):
                param_def = container_def.parameters[param_name]
                
                # Check config_class
                param_config_class = param_def.config_class or ConfigClass.PRE_COMPILE
                if param_config_class == config_class:
                    # Check for variant override first
                    param_path = f"{container.get_path()}.{param_name}"
                    if param_path in self.variant_overrides:
                        param_value = self.variant_overrides[param_path]
                    elif param_name in container.parameter_values:
                        param_value = container.parameter_values[param_name].value
                    else:
                        param_value = param_def.default_value
                    
                    if param_value is not None:
                        params.append((path, param_name, param_value))
            
            # Recurse into sub-containers, sorted by definition then short_name for deterministic output
            sub_container_map = {}
            for sub in container.sub_containers:
                base_name = sub.short_name.rsplit('_', 1)[0] if '_' in sub.short_name else sub.short_name
                sub_def = container_def.sub_containers.get(base_name)
                if sub_def:
                    if base_name not in sub_container_map:
                        sub_container_map[base_name] = (sub_def, [])
                    sub_container_map[base_name][1].append(sub)
            
            # Process in sorted definition order
            for base_name in sorted(sub_container_map.keys()):
                sub_def, instances = sub_container_map[base_name]
                for sub in sorted(instances, key=lambda x: x.short_name):
                    collect_from_container(sub, sub_def, f"{path}_{sub.short_name}")
        
        # Iterate all top-level containers in sorted order
        for container in sorted(self.configuration.containers, key=lambda x: x.short_name):
            base_name = container.short_name.rsplit('_', 1)[0] if '_' in container.short_name else container.short_name
            container_def = self.module_def.get_container_def(base_name)
            if container_def:
                collect_from_container(container, container_def, container.short_name)
        
        return params
        
    def _get_references(self) -> List[tuple]:
        """Collect all references from the configuration.
        
        Returns:
            List of tuples (container_path, ref_name, target_path)
        """
        refs = []
        
        def collect_from_container(container: EcucContainerValue, path: str):
            # Collect references
            for ref_name in sorted(container.reference_values.keys()):
                ref_val = container.reference_values[ref_name]
                if ref_val.value_ref:
                    refs.append((path, ref_name, ref_val.value_ref))
            
            # Recurse
            for sub in sorted(container.sub_containers, key=lambda x: x.short_name):
                collect_from_container(sub, f"{path}_{sub.short_name}")
                
        for container in sorted(self.configuration.containers, key=lambda x: x.short_name):
            collect_from_container(container, container.short_name)
            
        return refs

    def resolve_ref(self, ref_path: str) -> str:
        """Resolve a full ARXML path to a C identifier/linkable name.
        Example: /Config/Can/CanConfigSet/CanController_0 -> CAN_CONTROLLER_0
        """
        if not ref_path:
            return "NULL"
        
        parts = ref_path.strip('/').split('/')
        if not parts:
            return "NULL"
            
        name = parts[-1]
        return name.upper()

    def generate_config_header(self, output_dir: Path):
        """Generate Xxx_Cfg.h file with PRE-COMPILE parameters as macros"""
        module_name = self.configuration.short_name
        precompile_params = self._get_params_by_config_class(ConfigClass.PRE_COMPILE)
        references = self._get_references()
        
        context = {
            'module_def': self.module_def,
            'configuration': self.configuration,
            'module_name': module_name,
            'header_guard': f"{module_name.upper()}_CFG_H",
            'precompile_params': precompile_params,
            'references': references,
            'resolve_ref': self.resolve_ref
        }
        
        # Try external template first
        template = self._load_template("Module_Cfg.h.tpl")
        if not template:
            template = self._get_cfg_header_template(module_name)
        
        rendered = self.template_engine.render(template, context)
        
        output_file = output_dir / f"{module_name}_Cfg.h"
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(rendered)
        logger.debug(f"Generated: {output_file}")
            
    def generate_lcfg_source(self, output_dir: Path):
        """Generate Xxx_Lcfg.c file with LINK-TIME parameters as const struct"""
        module_name = self.configuration.short_name
        linktime_params = self._get_params_by_config_class(ConfigClass.LINK_TIME)
        references = self._get_references()
        
        context = {
            'module_def': self.module_def,
            'configuration': self.configuration,
            'module_name': module_name,
            'linktime_params': linktime_params,
            'references': references,
            'resolve_ref': self.resolve_ref
        }
        
        # Try external template first
        template = self._load_template("Module_Lcfg.c.tpl")
        if not template:
            template = self._get_lcfg_source_template(module_name)
        
        rendered = self.template_engine.render(template, context)
        
        output_file = output_dir / f"{module_name}_Lcfg.c"
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(rendered)
        logger.debug(f"Generated: {output_file}")
            
    def generate_pbcfg_source(self, output_dir: Path):
        """Generate Xxx_PBcfg.c file with POST-BUILD parameters"""
        module_name = self.configuration.short_name
        postbuild_params = self._get_params_by_config_class(ConfigClass.POST_BUILD)
        references = self._get_references()
        
        context = {
            'module_def': self.module_def,
            'configuration': self.configuration,
            'module_name': module_name,
            'postbuild_params': postbuild_params,
            'references': references,
            'resolve_ref': self.resolve_ref
        }
        
        # Try external template first
        template = self._load_template("Module_PBcfg.c.tpl")
        if not template:
            template = self._get_pbcfg_source_template(module_name)
        
        rendered = self.template_engine.render(template, context)
        
        output_file = output_dir / f"{module_name}_PBcfg.c"
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(rendered)
        logger.debug(f"Generated: {output_file}")
    
    # --- Fallback Templates (used when external templates not found) ---
    
    def _get_cfg_header_template(self, module_name: str) -> str:
        """Template for Cfg.h - PRE-COMPILE parameters as macros"""
        guard = f"{module_name.upper()}_CFG_H"
        return f"""/**
 * @file {module_name}_Cfg.h
 * @brief Pre-Compile Configuration for {module_name} module
 * @note Auto-generated - PRE-COMPILE parameters only
 */

#ifndef {guard}
#define {guard}

#include "Std_Types.h"

/* --- Pre-Compile Parameters --- */
{{% for path_name_value in precompile_params %}}
#define {{ module_name.upper() }}_{{ path_name_value.1.upper() }}    ({{ path_name_value.2 }})
{{% endfor %}}

/* --- Pre-Compile References --- */
{{% for path_name_target in references %}}
/* Reference from {{ path_name_target.0 }} to {{ path_name_target.2 }} */
#define {{ module_name.upper() }}_{{ path_name_target.1.upper() }}_REF    {{ resolve_ref(path_name_target.2) }}
{{% endfor %}}

#endif /* {guard} */
"""

    def _get_lcfg_source_template(self, module_name: str) -> str:
        """Template for Lcfg.c - LINK-TIME parameters as const struct"""
        return f"""/**
 * @file {module_name}_Lcfg.c
 * @brief Link-Time Configuration for {module_name} module
 */

#include "{module_name}_Cfg.h"
#include "{module_name}_MemMap.h"

#define {module_name.upper()}_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "{module_name}_MemMap.h"

/* Link-Time Parameters Configuration */
CONST({module_name}_ConfigType, {module_name.upper()}_CONST) {module_name}_Config = {{
{{% for path_name_value in linktime_params %}}
    ./* {{ path_name_value.0 }} */{{ path_name_value.1 }} = {{ path_name_value.2 }},
{{% endfor %}}
}};

#define {module_name.upper()}_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "{module_name}_MemMap.h"
"""

    def _get_pbcfg_source_template(self, module_name: str) -> str:
        """Template for PBcfg.c - POST-BUILD parameters"""
        return f"""/**
 * @file {module_name}_PBcfg.c
 * @brief Post-Build Configuration for {module_name} module
 */

#include "{module_name}_Cfg.h"
#include "{module_name}_MemMap.h"

#define {module_name.upper()}_START_SEC_CONFIG_DATA_POSTBUILD
#include "{module_name}_MemMap.h"

/* Post-Build Parameters Configuration */
CONST({module_name}_ConfigType, {module_name.upper()}_CONST) {module_name}_PBConfig = {{
{{% for path_name_value in postbuild_params %}}
    ./* {{ path_name_value.0 }} */{{ path_name_value.1 }} = {{ path_name_value.2 }},
{{% endfor %}}
}};

#define {module_name.upper()}_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "{module_name}_MemMap.h"
"""

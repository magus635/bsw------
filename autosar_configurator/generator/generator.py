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
from ..core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, ConfigClass
from .eb_template_engine import EBTemplateEngine

# Setup logger
logger = logging.getLogger(__name__)




class CodeGenerator:
    """Main code generator for AUTOSAR BSW modules"""
    
    # Default template directory (relative to this file)
    DEFAULT_TEMPLATE_DIR = Path(__file__).parent / "templates"
    
    def __init__(self, module_def: EcucModuleDef, configuration: EcucModuleConfiguration,
                 project_template_dir: Optional[Path] = None,
                 user_template_dir: Optional[Path] = None, 
                 variant_overrides: Optional[Dict[str, Any]] = None,
                 variant_name: Optional[str] = None,
                 all_configurations: Optional[Dict[str, Any]] = None):
        """Initialize generator
        
        Args:
            module_def: Module definition
            configuration: Configuration instance
            project_template_dir: Optional project-specific template directory (highest priority)
            user_template_dir: Optional user-defined template directory (searched after project)
            variant_overrides: Optional dict of param_path -> value for variant-specific values
            variant_name: Optional name of the active variant
            all_configurations: Optional dict of module_name -> (module_def, configuration)
        """
        self.module_def = module_def
        self.configuration = configuration
        self.project_template_dir = project_template_dir
        self.user_template_dir = user_template_dir
        self.variant_overrides = variant_overrides or {}
        self.variant_name = variant_name
        self.all_configurations = all_configurations or {}
        
        # Initialize EB Engine
        self.template_engine = EBTemplateEngine(strict=False)
        
        logger.info(f"CodeGenerator initialized for module: {configuration.short_name if configuration else 'None'}")
        if variant_name:
            logger.info(f"Active variant: {variant_name}")
        if project_template_dir:
            logger.info(f"✅ Project template directory SET: {project_template_dir}")
        else:
            logger.warning(f"⚠️ Project template directory NOT SET - will use builtin templates!")
        if user_template_dir:
            logger.info(f"User template directory: {user_template_dir}")
        if variant_overrides:
            logger.info(f"Variant overrides: {len(variant_overrides)} parameters")
    
    def _load_template(self, template_name: str, module_name: str = None) -> str:
        """Load template from file system with module, project and variant support.
        
        Search order:
        1. Project Variant: project_dir/templates/ModuleName/VariantName/ModuleName_template_name
        2. Project Module: project_dir/templates/ModuleName/ModuleName_template_name
        3. Project Generic: project_dir/templates/template_name
        4. User Variant: user_dir/ModuleName/VariantName/ModuleName_template_name
        5. User Module: user_dir/ModuleName/ModuleName_template_name
        6. User Generic: user_dir/template_name
        7. Built-in Module: templates/ModuleName/ModuleName_template_name
        8. Built-in Generic: templates/template_name
        9. Fallback to hardcoded template (return None)
        
        Args:
            template_name: Name of template file (e.g., "Cfg.h.tpl")
            module_name: Optional module name for module-specific lookup
            
        Returns:
            Template content as string, or None to use fallback
        """
        search_paths = []
        variant = self.variant_name
        
        def find_case_insensitive_dir(parent: Path, target_name: str) -> Optional[Path]:
            """Find directory by name, case-insensitive"""
            if not parent.exists():
                return None
            for item in parent.iterdir():
                if item.is_dir() and item.name.lower() == target_name.lower():
                    return item
            return None
        
        def add_search_paths_for_dir(base_dir: Path, mod_name: str):
            """Add search paths for a base directory, handling case-insensitivity"""
            if not base_dir or not base_dir.exists():
                return
            
            # Try exact match first, then case-insensitive
            module_dir = base_dir / mod_name
            if not module_dir.exists():
                module_dir = find_case_insensitive_dir(base_dir, mod_name)
            
            if module_dir and module_dir.exists():
                if variant:
                    variant_dir = module_dir / variant
                    if not variant_dir.exists():
                        variant_dir = find_case_insensitive_dir(module_dir, variant)
                    if variant_dir:
                        # With .tpl suffix
                        search_paths.append(variant_dir / f"{mod_name}_{template_name}")
                        # Without .tpl suffix (for EB Tresos style templates)
                        if template_name.endswith('.tpl'):
                            search_paths.append(variant_dir / f"{mod_name}_{template_name[:-4]}")
                
                # Module directory
                search_paths.append(module_dir / f"{mod_name}_{template_name}")
                if template_name.endswith('.tpl'):
                    search_paths.append(module_dir / f"{mod_name}_{template_name[:-4]}")
            
            # Generic templates
            search_paths.append(base_dir / f"Module_{template_name}")
        
        # 1. Project templates
        if self.project_template_dir and module_name:
            add_search_paths_for_dir(self.project_template_dir, module_name)
        
        # 2. User templates
        if self.user_template_dir and module_name:
            add_search_paths_for_dir(self.user_template_dir, module_name)
        
        # 3. Built-in templates
        if module_name:
            add_search_paths_for_dir(self.DEFAULT_TEMPLATE_DIR, module_name)
        search_paths.append(self.DEFAULT_TEMPLATE_DIR / f"Module_{template_name}")
        
        # Try each path in order
        for path in search_paths:
            if path.exists():
                logger.info(f"Loading template: {path}")
                return path.read_text(encoding='utf-8')
        
        # No template found, return None to use hardcoded fallback
        logger.debug(f"No external template found for {template_name}, using fallback")
        return None
        
    def generate_all(self, output_dir: Path, force: bool = False, variant: Optional[str] = None) -> bool:
        """Generate all code files by discovering templates in search directories"""
        output_dir = Path(output_dir)
        module_name = self.configuration.short_name
        
        # Prepare output directory
        out_module_dir = output_dir / module_name
        if variant:
            out_module_dir = out_module_dir / variant
            logger.info(f"Generating for variant: {variant}")
        out_module_dir.mkdir(parents=True, exist_ok=True)
        
        # 1. Calculate current fingerprint
        current_hash = self._calculate_fingerprint(variant)
        meta_file = out_module_dir / f".{module_name}.meta"
        
        # 2. Check overlap with previous generation
        if not force and meta_file.exists():
            try:
                with open(meta_file, 'r') as f:
                    meta = json.load(f)
                if meta.get('hash') == current_hash:
                    # Verify all previously generated files still exist
                    if all((out_module_dir / f).exists() for f in meta.get('files', [])):
                        logger.info(f"Skipping generation - configuration unchanged")
                        return False
            except Exception as e:
                logger.warning(f"Error reading meta file: {e}")
        
        # 3. Discover and generate files
        generated_files = []
        
        # Create standard subdirectories
        include_dir = out_module_dir / "include"
        src_dir = out_module_dir / "src"
        include_dir.mkdir(exist_ok=True)
        src_dir.mkdir(exist_ok=True)
        
        logger.info(f"Generating code for {module_name}...")
        
        # Get all templates to process
        template_types = self._discover_template_types(module_name)
        
        for t_type in template_types:
            # Determine output location
            is_header = t_type.lower().endswith('.h')
            target_parent = include_dir if is_header else src_dir
            rel_path = f"{'include' if is_header else 'src'}/{module_name}_{t_type}"
            
            # Generate the file
            if self._generate_single_file(t_type, target_parent):
                generated_files.append(rel_path)
        
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
        
        logger.info(f"Generated {len(generated_files)} files to {out_module_dir}")
        return True

    def _discover_template_types(self, module_name: str) -> List[str]:
        """Find all unique template types (e.g., 'Cfg.h', 'Lcfg.c') for the module
        
        Searches in the following structure:
        - ModuleName/include/ - for header templates (.h)
        - ModuleName/src/ - for source templates (.c)
        - ModuleName/ - for shared files (.m macros) and legacy flat structure
        """
        template_files = set()
        
        def find_case_insensitive_dir(parent: Path, target_name: str) -> Optional[Path]:
            """Find directory by name, case-insensitive"""
            if not parent or not parent.exists():
                return None
            for item in parent.iterdir():
                if item.is_dir() and item.name.lower() == target_name.lower():
                    return item
            return None
        
        def scan_directory_for_templates(directory: Path):
            """Scan a directory for template files"""
            if not directory or not directory.exists() or not directory.is_dir():
                return
            
            # Search for templates with .tpl suffix
            for f in directory.glob(f"{module_name}_*.tpl"):
                t_type = f.name[len(module_name)+1:-4]  # Remove prefix and .tpl
                template_files.add(t_type)
            
            # Also search for EB Tresos style templates without .tpl suffix
            for f in directory.glob(f"{module_name}_*.[ch]"):
                t_type = f.name[len(module_name)+1:]  # Remove prefix, keep extension
                template_files.add(t_type)
            
            # Case-insensitive matching for module name in filename
            for f in directory.iterdir():
                if f.is_file():
                    name_lower = f.name.lower()
                    prefix_lower = f"{module_name}_".lower()
                    if name_lower.startswith(prefix_lower):
                        suffix = f.name[len(module_name)+1:]
                        if suffix.endswith('.tpl'):
                            template_files.add(suffix[:-4])
                        elif suffix.endswith('.c') or suffix.endswith('.h'):
                            template_files.add(suffix)
        
        def add_module_dir(base_dir: Path):
            """Add module directory with case-insensitive matching, supporting include/src subdirs"""
            if not base_dir or not base_dir.exists():
                return
            # Try exact match first, then case-insensitive
            module_dir = base_dir / module_name
            if not module_dir.exists():
                module_dir = find_case_insensitive_dir(base_dir, module_name)
            if module_dir and module_dir.exists():
                # New structure: search in include/ and src/ subdirectories
                include_dir = module_dir / "include"
                src_dir = module_dir / "src"
                
                if include_dir.exists():
                    scan_directory_for_templates(include_dir)
                    logger.debug(f"Scanned include dir: {include_dir}")
                
                if src_dir.exists():
                    scan_directory_for_templates(src_dir)
                    logger.debug(f"Scanned src dir: {src_dir}")
                
                # Legacy/fallback: also scan module root for flat structure
                scan_directory_for_templates(module_dir)
                
                # Handle variants
                if self.variant_name:
                    variant_dir = module_dir / self.variant_name
                    if not variant_dir.exists():
                        variant_dir = find_case_insensitive_dir(module_dir, self.variant_name)
                    if variant_dir:
                        # Variant can also have include/src structure
                        var_include = variant_dir / "include"
                        var_src = variant_dir / "src"
                        if var_include.exists():
                            scan_directory_for_templates(var_include)
                        if var_src.exists():
                            scan_directory_for_templates(var_src)
                        scan_directory_for_templates(variant_dir)
        
        if self.project_template_dir:
            add_module_dir(self.project_template_dir)
        if self.user_template_dir:
            add_module_dir(self.user_template_dir)
        add_module_dir(self.DEFAULT_TEMPLATE_DIR)
        
        # Always include defaults if not found, to trigger fallback logic
        defaults = ["Cfg.h", "Lcfg.c", "PBcfg.c"]
        for d in defaults:
            template_files.add(d)
            
        return sorted(list(template_files))

    def get_template_info(self, module_name: str) -> List[Dict[str, str]]:
        """
        Get info about all templates for a module.
        Returns a list of dicts: [{'type': 'Cfg.h', 'engine': 'EB', 'path': '...'}, ...]
        """
        template_types = self._discover_template_types(module_name)
        results = []
        
        for t_type in template_types:
            template_name = f"{t_type}.tpl"
            # Attempt to load content to check engine
            content = self._load_template(template_name, module_name)
            engine = "Standard"
            source = "Embedded Fallback"
            
            # Determine subdirectory based on type
            is_header = t_type.lower().endswith('.h')
            is_source = t_type.lower().endswith('.c')
            subdir_name = "include" if is_header else ("src" if is_source else None)
            
            # Build search dirs - include/src subdirectories + module root
            search_dirs = []
            base_dirs = []
            if self.project_template_dir:
                base_dirs.append(self.project_template_dir / module_name)
            if self.user_template_dir:
                base_dirs.append(self.user_template_dir / module_name)
            base_dirs.append(self.DEFAULT_TEMPLATE_DIR / module_name)
            
            for base_dir in base_dirs:
                if subdir_name:
                    # Search in include/ or src/ first
                    search_dirs.append(base_dir / subdir_name)
                # Also search in module root (legacy/fallback)
                search_dirs.append(base_dir)
                if self.variant_name:
                    if subdir_name:
                        search_dirs.append(base_dir / self.variant_name / subdir_name)
                    search_dirs.append(base_dir / self.variant_name)

            # Search for both .tpl and non-.tpl files
            found = False
            for d in search_dirs:
                if not d.exists():
                    continue
                # Try with .tpl suffix first
                potential_file = d / f"{module_name}_{template_name}"
                if potential_file.exists():
                    source = str(potential_file)
                    found = True
                    break
                # Try without .tpl suffix (e.g., Can_PBcfg.c)
                potential_file_no_tpl = d / f"{module_name}_{t_type}"
                if potential_file_no_tpl.exists():
                    source = str(potential_file_no_tpl)
                    found = True
                    break

            if content:
                if "[!" in content:
                    engine = "EB"
            
            results.append({
                'type': t_type,
                'engine': engine,
                'path': source
            })
            
        return results

    def _prepare_context(self, variant: Optional[str] = None) -> Dict[str, Any]:
        """Prepare the complete generation context for template engines"""
        module_name = self.configuration.short_name if self.configuration else "Unknown"
        
        return {
            'module_def': self.module_def,
            'configuration': self.configuration,
            'containers': self.configuration.containers if self.configuration else [],
            'module_name': module_name,
            'resolve_ref': self.resolve_ref,
            'active_variant': variant or self.variant_name,
            'enums': self._get_enums(),
            'precompile_params': self._get_params_by_config_class(ConfigClass.PRE_COMPILE) if self.configuration else [],
            'linktime_params': self._get_params_by_config_class(ConfigClass.LINK_TIME) if self.configuration else [],
            'postbuild_params': self._get_params_by_config_class(ConfigClass.POST_BUILD) if self.configuration else [],
            'references': self._get_references() if self.configuration else [],
            'header_guard': f"{module_name.upper()}_CFG_H"
        }

    def _serialize_container_link(self, container: EcucContainerValue) -> Dict[str, Any]:
        """Convert container instance to a dictionary for template context"""
        res = {
            'name': container.short_name,
            'path': container.get_path(),
            'definition': container.definition_ref,
            'parameters': [],
            'references': [],
            'sub_containers': [self._serialize_container_link(s) for s in container.sub_containers]
        }
        
        # Parameters
        for name, val in container.parameter_values.items():
            res['parameters'].append({
                'name': name,
                'value': self._format_value(val.value),
                'raw_value': val.value
            })
            
        # References
        for name, ref in container.reference_values.items():
            res['references'].append({
                'name': name,
                'target': f"&{self.resolve_ref(ref.value_ref)}_Config" if ref.value_ref else "NULL",
                'path': ref.value_ref
            })
            
        return res

    def _format_value(self, value: Any) -> str:
        """Format value for C code output"""
        if value is None:
            return "NULL"
        if isinstance(value, bool):
            return "TRUE" if value else "FALSE"
        if isinstance(value, str):
            # If it looks like an identifier (all caps/numbers/underscore), don't quote it
            # This is a heuristic for enumeration literals
            if value.replace('_', '').isalnum() and (value.isupper() or value[0].isnumeric()):
                return value
            return f'"{value}"'
        return str(value)

    def _generate_single_file(self, template_type: str, output_parent: Path) -> bool:
        """Generate a single file from a template type"""
        module_name = self.configuration.short_name
        
        # Prepare context (same for all types, but filtered params differ)
        context = self._prepare_context()
        context['header_guard'] = f"{module_name.upper()}_{template_type.replace('.', '_').upper()}"
        
        template_name = f"{template_type}.tpl"
        template_content, template_source_dir = self._load_template_with_path(template_name, module_name)
        
        if template_content:
            # Automatic engine selection: EB syntax [! ... !] vs Standard
            if "[!" in template_content:
                logger.debug(f"Detected EB syntax in {template_name}, using EBTemplateEngine")
                # Create engine with template directory for INCLUDE resolution
                eb_engine = EBTemplateEngine(strict=False, template_dir=template_source_dir)
                
                # Add cross-module contexts
                context['all_modules'] = self.all_configurations
                
                try:
                    rendered = eb_engine.render(template_content, context)
                except Exception as e:
                    logger.error(f"CRITICAL ERROR rendering {template_name}: {e}", exc_info=True)
                    return False
            else:
                from .template_engine import TemplateEngine
                engine = TemplateEngine()
                try:
                    rendered = engine.render(template_content, context)
                except Exception as e:
                    logger.error(f"CRITICAL ERROR rendering {template_name}: {e}", exc_info=True)
                    return False

        else:
            # Fallback for standard types only - these hardcoded templates use Standard syntax
            if template_type == "Cfg.h":
                template_content = self._get_cfg_header_template(module_name)
            elif template_type == "Lcfg.c":
                template_content = self._get_lcfg_source_template(module_name)
            elif template_type == "PBcfg.c":
                template_content = self._get_pbcfg_source_template(module_name)
            else:
                logger.warning(f"No template found for {template_type} and no fallback available")
                return False
            
            from .template_engine import TemplateEngine
            engine = TemplateEngine()
            rendered = engine.render(template_content, context)
            
        output_file = output_parent / f"{module_name}_{template_type}"
        with open(output_file, 'w', encoding='utf-8') as f:
            f.write(rendered)
        logger.debug(f"Generated: {output_file}")
        return True
    
    def _load_template_with_path(self, template_name: str, module_name: str = None) -> Tuple[Optional[str], Optional[Path]]:
        """Load template and return both content and source directory.
        
        Searches in the following structure:
        - ModuleName/include/ - for header templates (.h)
        - ModuleName/src/ - for source templates (.c)
        - ModuleName/ - for shared files (.m macros) and legacy flat structure
        
        Returns:
            Tuple of (template_content, source_directory)
        """
        variant = self.variant_name
        
        # Determine subdirectory based on template type
        is_header = template_name.lower().endswith('.h') or template_name.lower().endswith('.h.tpl')
        is_source = template_name.lower().endswith('.c') or template_name.lower().endswith('.c.tpl')
        subdir_name = "include" if is_header else ("src" if is_source else None)
        
        def find_case_insensitive_dir(parent: Path, target_name: str) -> Optional[Path]:
            """Find directory by name, case-insensitive"""
            if not parent.exists():
                return None
            for item in parent.iterdir():
                if item.is_dir() and item.name.lower() == target_name.lower():
                    return item
            return None
        
        def add_search_paths_for_dir(base_dir: Path, mod_name: str, paths_list: list):
            """Add search paths for a base directory, handling case-insensitivity"""
            if not base_dir or not base_dir.exists():
                return
            
            module_dir = base_dir / mod_name
            if not module_dir.exists():
                module_dir = find_case_insensitive_dir(base_dir, mod_name)
            
            if module_dir and module_dir.exists():
                # New structure: search in include/ or src/ subdirectory first
                if subdir_name:
                    subdir = module_dir / subdir_name
                    if subdir.exists():
                        # Variant-specific templates in subdir
                        if variant:
                            variant_subdir = module_dir / variant / subdir_name
                            if variant_subdir.exists():
                                paths_list.append((variant_subdir / f"{mod_name}_{template_name}", variant_subdir))
                                if template_name.endswith('.tpl'):
                                    paths_list.append((variant_subdir / f"{mod_name}_{template_name[:-4]}", variant_subdir))
                        
                        # Module subdir templates
                        paths_list.append((subdir / f"{mod_name}_{template_name}", subdir))
                        if template_name.endswith('.tpl'):
                            paths_list.append((subdir / f"{mod_name}_{template_name[:-4]}", subdir))
                
                # Legacy: also check variant dir and module root
                if variant:
                    variant_dir = module_dir / variant
                    if not variant_dir.exists():
                        variant_dir = find_case_insensitive_dir(module_dir, variant)
                    if variant_dir:
                        paths_list.append((variant_dir / f"{mod_name}_{template_name}", variant_dir))
                        if template_name.endswith('.tpl'):
                            paths_list.append((variant_dir / f"{mod_name}_{template_name[:-4]}", variant_dir))
                
                # Module root (legacy flat structure or shared files)
                paths_list.append((module_dir / f"{mod_name}_{template_name}", module_dir))
                if template_name.endswith('.tpl'):
                    paths_list.append((module_dir / f"{mod_name}_{template_name[:-4]}", module_dir))
            
            paths_list.append((base_dir / f"Module_{template_name}", base_dir))
        
        search_paths = []  # List of (path, source_dir)
        
        if self.project_template_dir and module_name:
            add_search_paths_for_dir(self.project_template_dir, module_name, search_paths)
        if self.user_template_dir and module_name:
            add_search_paths_for_dir(self.user_template_dir, module_name, search_paths)
        if module_name:
            add_search_paths_for_dir(self.DEFAULT_TEMPLATE_DIR, module_name, search_paths)
        search_paths.append((self.DEFAULT_TEMPLATE_DIR / f"Module_{template_name}", self.DEFAULT_TEMPLATE_DIR))
        
        # Debug: Log all search paths
        logger.info(f"Template search for '{template_name}' (module: {module_name}, subdir: {subdir_name}):")
        for path, source_dir in search_paths:
            exists = path.exists()
            logger.info(f"  {'[FOUND]' if exists else '[     ]'} {path}")
        
        for path, source_dir in search_paths:
            if path.exists():
                logger.info(f"Loading template: {path}")
                return path.read_text(encoding='utf-8'), source_dir
        
        logger.debug(f"No external template found for {template_name}, using fallback")
        return None, None

    def _calculate_fingerprint(self, variant: Optional[str] = None, template_types: Optional[List[str]] = None) -> str:
        """Calculate a hash of the current configuration content and templates"""
        import hashlib
        # We build a stable string representation of the config
        parts = []
        
        # Add template info (to detect template changes)
        if template_types:
            for t_type in sorted(template_types):
                content, _ = self._load_template_with_path(f"{t_type}.tpl", self.configuration.short_name)
                if content:
                    parts.append(f"T:{t_type}={hashlib.md5(content.encode('utf-8')).hexdigest()}")
        
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
        
    def _get_params_by_config_class(self, config_class: str) -> List[Dict[str, Any]]:
        """Get parameters filtered by config_class, applying variant overrides"""
        params = []
        
        def collect_from_container(container: EcucContainerValue, container_def: EcucContainerDef, path: str):
            for param_name in sorted(container_def.parameters.keys()):
                param_def = container_def.parameters[param_name]
                
                param_config_class = param_def.config_class or ConfigClass.PRE_COMPILE
                if param_config_class == config_class:
                    param_path = f"{container.get_path()}.{param_name}"
                    if param_path in self.variant_overrides:
                        param_value = self.variant_overrides[param_path]
                    elif param_name in container.parameter_values:
                        param_value = container.parameter_values[param_name].value
                    else:
                        param_value = param_def.default_value
                    
                    if param_value is not None:
                        params.append((path, param_name, param_value))
            
            sub_container_map = {}
            for sub in container.sub_containers:
                base_name = sub.short_name.rsplit('_', 1)[0] if '_' in sub.short_name else sub.short_name
                sub_def = container_def.sub_containers.get(base_name)
                if sub_def:
                    if base_name not in sub_container_map:
                        sub_container_map[base_name] = (sub_def, [])
                    sub_container_map[base_name][1].append(sub)
            
            for base_name in sorted(sub_container_map.keys()):
                sub_def, instances = sub_container_map[base_name]
                for sub in sorted(instances, key=lambda x: x.short_name):
                    collect_from_container(sub, sub_def, f"{path}_{sub.short_name}")
        
        for container in sorted(self.configuration.containers, key=lambda x: x.short_name):
            base_name = container.short_name.rsplit('_', 1)[0] if '_' in container.short_name else container.short_name
            container_def = self.module_def.get_container_def(base_name)
            if container_def:
                collect_from_container(container, container_def, container.short_name)
        
        return params
        
    def _get_references(self) -> List[tuple]:
        """Collect all references from the configuration"""
        refs = []
        def collect_from_container(container: EcucContainerValue, path: str):
            for ref_name in sorted(container.reference_values.keys()):
                ref_val = container.reference_values[ref_name]
                if ref_val.value_ref:
                    refs.append((path, ref_name, ref_val.value_ref))
            for sub in sorted(container.sub_containers, key=lambda x: x.short_name):
                collect_from_container(sub, f"{path}_{sub.short_name}")
        for container in sorted(self.configuration.containers, key=lambda x: x.short_name):
            collect_from_container(container, container.short_name)
        return refs

    def resolve_ref(self, ref_path: str) -> str:
        """Resolve a full ARXML path to a C identifier"""
        if not ref_path: return "NULL"
        parts = [p for p in ref_path.strip('/').split('/') if p != 'Config']
        if not parts: return "NULL"
        return "_".join(parts)

    def _get_enums(self) -> List[Dict[str, Any]]:
        """Extract all enumeration definitions from module definition"""
        from ..core.model.definition_model import EcucParameterType
        enums = []
        # Track seen enums by name and their literal sets for deduplication
        seen_enums = {}  # name -> set(literals)
        logger.debug(f"Extracting enums for module: {self.configuration.short_name}")

        def process_container_def(container_def):
            for param_name, param_def in container_def.parameters.items():
                if param_def.param_type == EcucParameterType.ENUMERATION:
                    literals = param_def.literals or []
                    literal_set = set(literals)
                    
                    if param_def.short_name not in seen_enums:
                        seen_enums[param_def.short_name] = literal_set
                        enums.append({
                            'name': param_def.short_name,
                            'ref': param_def.definition_ref,
                            'literals': literals
                        })
                        logger.debug(f"Added enum: {param_def.short_name} with {len(literals)} literals")
                    else:
                        # If same name exists, check if literals are identical
                        if literal_set == seen_enums[param_def.short_name]:
                            logger.debug(f"Skipping identical duplicate enum: {param_def.short_name}")
                        else:
                            # Warning: name collision with different literals
                            logger.warning(f"Enum name collision with different literals: {param_def.short_name}")
                            # To avoid C compilation error, we might need a suffix, but usually this indicates a DEF issue
                            # For now, we just skip it to avoid redefinition error
            
            for sub_def in container_def.sub_containers.values():
                process_container_def(sub_def)

        if self.module_def:
            logger.debug(f"Module definition found: {self.module_def.short_name}")
            for container_name, container_def in self.module_def.containers.items():
                process_container_def(container_def)
        else:
            logger.warning("No module definition available during enum extraction")
        
        logger.info(f"Extracted {len(enums)} unique enums from definition")
        return enums

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
#define {{{{ module_name.upper() }}}}_{{{{ path_name_value.1.upper() }}}}    ({{{{ path_name_value.2 }}}}) /* {{{{ path_name_value.1 }}}} */
{{% endfor %}}

/* --- Pre-Compile References --- */
{{% for path_name_target in references %}}
/* Reference from {{{{ path_name_target.0 }}}} to {{{{ path_name_target.2 }}}} */
#define {{{{ module_name.upper() }}}}_{{{{ path_name_target.1.upper() }}}}_REF    {{{{ resolve_ref(path_name_target.2) }}}}
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
{{% for container in containers %}}
    /* Container: {{{{ container.short_name }}}} */
    {{% for param_name, param_val in container.parameter_values.items() %}}
        /* Param: {{{{ param_name }}}} = {{{{ param_val.value|upper }}}} */
    {{% endfor %}}
    {{% for ref_name, ref_val in container.reference_values.items() %}}
        /* Ref: {{{{ ref_name }}}} = &{{{{ ref_val.value_ref|resolve_ref }}}}_Config */
    {{% endfor %}}
{{% endfor %}}
}};

#define {module_name.upper()}_STOP_SEC_CONFIG_DATA_POSTBUILD
#include "{module_name}_MemMap.h"
"""

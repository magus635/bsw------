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
from ..core.model.definition_model import EcucModuleDef, EcucContainerDef, EcucParameterDef, EcucParameterType, ConfigClass
from .eb_template_engine import EBTemplateEngine
from ..core.hardware.tresos_properties_parser import TresosPropertiesParser

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
                 all_configurations: Optional[Dict[str, Any]] = None,
                 selected_chip: Optional[str] = None,
                 ecu_resources: Optional[Dict[str, Any]] = None):
        """Initialize generator
        
        Args:
            module_def: Module definition
            configuration: Configuration instance
            project_template_dir: Optional project-specific template directory (highest priority)
            user_template_dir: Optional user-defined template directory (searched after project)
            variant_overrides: Optional dict of param_path -> value for variant-specific values
            variant_name: Optional name of the active variant
            all_configurations: Optional dict of module_name -> (module_def, configuration)
            selected_chip: Optional name of the selected chip variant (filters .properties files)
            ecu_resources: Optional pre-loaded ECU resources (overrides automatic scan)
        """
        self.module_def = module_def
        self.configuration = configuration
        self.project_template_dir = project_template_dir
        self.user_template_dir = user_template_dir
        self.variant_overrides = variant_overrides or {}
        self.variant_name = variant_name
        self.all_configurations = all_configurations or {}
        self.selected_chip = selected_chip
        
        # Load ECU resources from .properties files in the project (if not provided)
        if ecu_resources is not None:
            self.ecu_resources = ecu_resources
        else:
            self.ecu_resources = self._load_ecu_resources()
        
        # Initialize EB Engine
        self.template_engine = EBTemplateEngine(strict=False)
        
        logger.info(f"CodeGenerator initialized for module: {configuration.short_name if configuration else 'None'}")
        if variant_name:
            logger.info(f"Active variant: {variant_name}")
        if project_template_dir:
            logger.debug(f"Project template directory: {project_template_dir}")
        else:
            logger.debug(f"Project template directory not set, using builtin templates")
        if user_template_dir:
            logger.info(f"User template directory: {user_template_dir}")
        if variant_overrides:
            logger.info(f"Variant overrides: {len(variant_overrides)} parameters")

    def _load_ecu_resources(self) -> Dict[str, Any]:
        """Find and load ECU resources from .properties files in the project directory.
        
        If selected_chip is set, only load the matching chip's .properties file.
        """
        ecu_resources = {}
        if not self.project_template_dir:
            return ecu_resources

        # Robust Project Root Detection:
        # Search upwards from project_template_dir until we find a directory 
        # containing 'Def' or 'Define', or we hit the filesystem root.
        project_root = None
        current = self.project_template_dir.resolve()
        # Max search depth 5 to avoid traversing too far up
        for _ in range(5):
            if (current / "Def").exists() or (current / "Define").exists():
                project_root = current
                break
            if current.parent == current: # Root
                break
            current = current.parent
            
        if not project_root:
            # Fallback to parent of templates if templates dir exists in path
            if "templates" in str(self.project_template_dir).lower():
                curr = self.project_template_dir
                while curr.name.lower() != "templates" and curr.parent != curr:
                    curr = curr.parent
                project_root = curr.parent
            else:
                project_root = self.project_template_dir.parent

        logger.info(f"Scanning for ECU resources in project root: {project_root}")
        
        parser = TresosPropertiesParser()
        props_files = []
        
        # Search recursively for .properties files in Def and Define
        try:
            search_dirs = [project_root / "Def", project_root / "Define"]
            
            for def_dir in search_dirs:
                if not def_dir.exists():
                    continue
                
                logger.info(f"Searching for .properties in: {def_dir}")
                # Recursively find all properties files
                all_props = list(def_dir.rglob("*.properties"))
                
                # Filter by selected chip if specified
                if self.selected_chip:
                    # Keep only files that match the selected chip name pattern
                    filtered = []
                    for pf in all_props:
                        # Check if this is a chip resource file (in resource/ directory)
                        if "resource" in str(pf.parent).lower():
                            # Check if filename contains the selected chip identifier
                            if self.selected_chip in pf.stem:
                                filtered.append(pf)
                                logger.info(f"Selected chip file: {pf.name}")
                        else:
                            # Non-resource properties files (like build.properties) are always loaded
                            filtered.append(pf)
                    props_files.extend(filtered)
                else:
                    props_files.extend(all_props)
            
            # also check templates for any embedded properties
            props_files.extend(list(self.project_template_dir.glob("**/*.properties")))
        except Exception as e:
            logger.warning(f"Error scanning for properties files: {e}")

        if not props_files:
            logger.info("No .properties files found for ECU resources.")
            return ecu_resources

        for props_file in props_files:
            try:
                logger.debug(f"Parsing ECU resources from: {props_file}")
                parser.parse_file(props_file)
            except Exception as e:
                logger.warning(f"Failed to parse {props_file}: {e}")

        ecu_resources = parser.get_ecu_resources_dict()
        if ecu_resources:
            logger.info(f"Loaded {len(ecu_resources)} ECU resources from {len(props_files)} files.")

        return ecu_resources

    def _get_template_module_names(self) -> List[str]:
        """Get names of modules that should appear as MODULE-DEF in XDM enumeration
        (i.e., /AUTOSAR/TOP-LEVEL-PACKAGES/*/ELEMENTS/*).

        In EB Tresos, this returns all loaded BSW/MCAL module definitions.
        Infrastructure modules like EcuC (virtual ECU configuration collector)
        are excluded as they are not regular BSW modules.
        """
        # Known AUTOSAR infrastructure / virtual modules that are NOT regular BSW modules
        _INFRASTRUCTURE_MODULES = frozenset({'ecuc', 'ecum', 'bswm', 'det', 'os'})
        return [m_name for m_name in self.all_configurations
                if m_name.lower() not in _INFRASTRUCTURE_MODULES]

    def _load_template(self, template_name: str, module_name: str = None) -> Optional[str]:
        """Load template content, searching across project, user, and default directories.
        
        Args:
            template_name: Name of template (e.g., 'Cfg.h.tpl')
            module_name: Optional module name to narrow search
            
        Returns:
            Template content string or None
        """
        content, _ = self._load_template_with_path(template_name, module_name)
        return content
        
    def generate_all(self, output_dir: Path, force: bool = False, variant: Optional[str] = None) -> bool:
        """Generate all code files by discovering templates in search directories"""
        output_dir = Path(output_dir)
        module_name = self.configuration.short_name

        # Update variant_name if provided - this ensures _prepare_context() gets the correct value
        if variant:
            self.variant_name = variant

        # Prepare output directory
        out_module_dir = output_dir / module_name
        if variant:
            out_module_dir = out_module_dir / variant
            logger.info(f"Generating for variant: {variant}")
        out_module_dir.mkdir(parents=True, exist_ok=True)

        # Discover and generate files
        generated_files = []

        logger.info(f"Generating code for {module_name}...")

        # Get all templates to process
        template_types = self._discover_template_types(module_name)

        for t_info in template_types:
            t_type = t_info['type']
            rel_dir = t_info['rel_dir']
            
            # Deeply nested templates and root templates all preserve their directory structure
            if rel_dir == '.':
                target_parent = out_module_dir
                rel_path = f"{module_name}_{t_type}"
            else:
                target_parent = out_module_dir / rel_dir
                target_parent.mkdir(parents=True, exist_ok=True)
                rel_path = f"{rel_dir}/{module_name}_{t_type}"

            # Generate the file
            if self._generate_single_file(t_info, target_parent):
                generated_files.append(rel_path)

        logger.info(f"Generated {len(generated_files)} files to {out_module_dir}")
        return True

    def _discover_template_types(self, module_name: str) -> List[Dict[str, Any]]:
        """Find all templates and their relative paths
        Returns list of dicts: [
           {'type': 'Cfg.h', 'rel_dir': '.', 'template_name': 'Os_Cfg.h.tpl', 'original_path': '/.../Os_Cfg.h.tpl'},
           {'type': 'alarm_Lcfg.c', 'rel_dir': 'alarm', 'template_name': 'Os_alarm_Lcfg.c', 'original_path': '/.../alarm/Os_alarm_Lcfg.c'},
           ...
        ]
        """
        template_dict = {} # Key: relative path + type

        def scan_directory_recursively(base_dir: Path, is_fallback: bool = False):
            if not base_dir or not base_dir.exists() or not base_dir.is_dir():
                return
                
            dirs_to_scan = []
            
            # 1. Exact or case insensitive module dir
            mod_dir = base_dir / module_name
            if mod_dir.exists():
                dirs_to_scan.append(mod_dir)
            else:
                for item in base_dir.iterdir():
                    if item.is_dir() and item.name.lower() == module_name.lower():
                        dirs_to_scan.append(item)
                        break
                        
            # 2. Variant dir
            if self.variant_name:
                for md in list(dirs_to_scan):
                    var_dir = md / self.variant_name
                    if var_dir.exists():
                        dirs_to_scan.append(var_dir)
                    else:
                        for item in md.iterdir():
                            if item.is_dir() and item.name.lower() == self.variant_name.lower():
                                dirs_to_scan.append(item)
                                break
                                
            for md in dirs_to_scan:
                for f in md.rglob("*"):
                    if not f.is_file():
                        continue
                        
                    if f.suffix.lower() == '.m':
                        continue
                        
                    name_lower = f.name.lower()
                    prefix_lower = f"{module_name}_".lower()
                    
                    if name_lower.startswith(prefix_lower) or name_lower.startswith("module_"):
                        try:
                            rel_path = f.parent.relative_to(md)
                        except ValueError:
                            rel_path = Path('.')
                            
                        rel_dir = str(rel_path).replace('\\', '/')
                        
                        if name_lower.startswith(prefix_lower):
                            suffix = f.name[len(module_name)+1:]
                        else:
                            suffix = f.name[7:] # remove Module_
                            
                        if suffix.endswith('.tpl'):
                            t_type = suffix[:-4]
                        elif suffix.endswith('.c') or suffix.endswith('.h'):
                            t_type = suffix
                        else:
                            continue
                            
                        dedup_key = f"{rel_dir}/{t_type}"
                        if dedup_key not in template_dict:
                            template_dict[dedup_key] = {
                                'type': t_type,
                                'rel_dir': rel_dir,
                                'template_name': f.name,
                                'original_path': str(f.resolve()),
                                'source_dir': str(md.resolve())
                            }

        if self.project_template_dir:
            scan_directory_recursively(self.project_template_dir)
            
        if self.user_template_dir:
            scan_directory_recursively(self.user_template_dir)
            
        scan_directory_recursively(self.DEFAULT_TEMPLATE_DIR, is_fallback=True)
        
        # Add fallbacks for standard templates if they were not found in any directory
        # Note: Per user request, we do NOT generate a default Lcfg.c if it's missing.
        defaults = ["Cfg.h", "PBcfg.c"]
        for d in defaults:
            # Check if this type was found in ANY relative directory
            if not any(v['type'] == d for v in template_dict.values()):
                fallback_key = f"./{d}"
                template_dict[fallback_key] = {
                    'type': d,
                    'rel_dir': '.',
                    'template_name': f"Module_{d}", # dummy name for fallback
                    'original_path': None,          # None triggers string fallback
                    'source_dir': None
                }
                
        # Return uniquely sorted list of actually discovered templates
        unique_templates = {}
        for t in sorted(template_dict.values(), key=lambda x: (x['type'], 0 if x['rel_dir'] != '.' else 1)):
            if t['type'] not in unique_templates:
                unique_templates[t['type']] = t
                
        return sorted(list(unique_templates.values()), key=lambda x: x['type'])

    def get_template_info(self, module_name: str) -> List[Dict[str, str]]:
        """
        Get info about all templates for a module.
        Returns a list of dicts: [{'type': 'Cfg.h', 'engine': 'EB', 'path': '...'}, ...]
        """
        template_types = self._discover_template_types(module_name)
        results = []
        
        for t_info in template_types:
            original_path = t_info.get('original_path')
            engine = "Standard"
            source = original_path if original_path else "Embedded Fallback"
            
            if original_path:
                try:
                    with open(original_path, 'r', encoding='utf-8') as f:
                        if "[!" in f.read(4000): # Check first 4000 bytes
                            engine = "EB"
                except Exception:
                    pass
            
            results.append({
                'type': t_info['type'],
                'engine': engine,
                'path': source
            })
            
        return results

    def _prepare_context(self, variant: Optional[str] = None) -> Dict[str, Any]:
        """Prepare the complete generation context for template engines"""
        module_name = self.configuration.short_name if self.configuration else "Unknown"
        
        context = {
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
            'header_guard': f"{module_name.upper()}_CFG_H",
            'all_modules': self.all_configurations,  # Corrected: Include for cross-module access
            'template_module_names': self._get_template_module_names(),  # Modules with templates (MODULE-DEF)
        }
        
        import datetime
        context['datetime'] = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        
        # Inject standard EB Tresos version variables
        if self.configuration:
            # Try to find version info from CommonPublishedInformation
            rel_major = "4"
            rel_minor = "4"
            rel_patch = "0"
            sw_major = "1"
            sw_minor = "0"
            sw_patch = "0"
            
            pub_info = next((c for c in self.configuration.containers if c.short_name == 'CommonPublishedInformation'), None)
            if pub_info:
                # helper to get param value
                def get_val(item, name, default):
                    # EcucContainerValue uses get_parameter_value or parameter_values
                    try:
                        if hasattr(item, 'get_parameter_value'):
                            val = item.get_parameter_value(name)
                            return str(val) if val is not None else default
                        elif hasattr(item, 'parameter_values') and name in item.parameter_values:
                            val = item.parameter_values[name].value
                            return str(val) if val is not None else default
                        # Also check children dict if present
                        elif hasattr(item, 'children') and name in item.children:
                            val = item.children[name].value
                            return str(val) if val is not None else default
                    except:
                        pass
                    return default
                
                rel_major = get_val(pub_info, 'ArMajorVersion', rel_major)
                rel_minor = get_val(pub_info, 'ArMinorVersion', rel_minor)
                rel_patch = get_val(pub_info, 'ArPatchVersion', rel_patch)
                sw_major = get_val(pub_info, 'SwMajorVersion', sw_major)
                sw_minor = get_val(pub_info, 'SwMinorVersion', sw_minor)
                sw_patch = get_val(pub_info, 'SwPatchVersion', sw_patch)
            
            context['moduleReleaseVer'] = f"AR {rel_major}.{rel_minor}.{rel_patch}"
            context['moduleSoftwareVer'] = f"{sw_major}.{sw_minor}.{sw_patch}"
            # Also add with $ prefix for direct variable lookup if engine supports it
            context['$moduleReleaseVer'] = context['moduleReleaseVer']
            context['$moduleSoftwareVer'] = context['moduleSoftwareVer']
            
        return context

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

    def _generate_single_file(self, t_info: Dict[str, Any], output_parent: Path) -> bool:
        """Generate a single file from a template type"""
        module_name = self.configuration.short_name
        template_type = t_info['type']
        
        # Prepare context
        context = self._prepare_context()
        context['header_guard'] = f"{module_name.upper()}_{template_type.replace('.', '_').upper()}"
        
        template_name = t_info['template_name']
        original_path = t_info.get('original_path')
        template_content = None
        template_source_dir = None
        
        if original_path:
            try:
                with open(original_path, 'r', encoding='utf-8') as f:
                    template_content = f.read()
                template_source_dir = Path(t_info.get('source_dir'))
            except Exception as e:
                logger.error(f"Failed to read template '{original_path}': {e}")
                return False
        
        if template_content:
            # Automatic engine selection: EB syntax [! ... !] vs Standard
            if "[!" in template_content:
                logger.debug(f"Detected EB syntax in {template_name}, using EBTemplateEngine")
                eb_engine = EBTemplateEngine(strict=False, template_dir=template_source_dir)
                context['all_modules'] = self.all_configurations
                try:
                    rendered = eb_engine.render(template_content, context, ecu_resources=self.ecu_resources, template_file=original_path)
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
            # Fallback for standard types only
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
        Now implemented as a wrapper over the new recursive discovery logic.
        """
        mod = module_name or (self.configuration.short_name if self.configuration else "")
        types = self._discover_template_types(mod)
        for t_info in types:
            if t_info['template_name'] == template_name or f"{mod}_{t_info['type']}" == template_name or f"{mod}_{t_info['type']}.tpl" == template_name:
                orig_path = t_info.get('original_path')
                if orig_path:
                    try:
                        with open(orig_path, 'r', encoding='utf-8') as f:
                            return f.read(), Path(t_info.get('source_dir'))
                    except Exception as e:
                        logger.error(f"Error loading {orig_path}: {e}")
        
        logger.debug(f"No external template found for {template_name}, using fallback")
        return None, None

    def _calculate_fingerprint(self, variant: Optional[str] = None, template_types: Optional[List[Dict[str, Any]]] = None) -> str:
        """Calculate a hash of the current configuration content and templates"""
        import hashlib
        # We build a stable string representation of the config
        parts = []
        
        # Add template info (to detect template changes)
        if template_types:
            for t_info in sorted(template_types, key=lambda x: f"{x['rel_dir']}/{x['type']}"):
                orig_path = t_info.get('original_path')
                if orig_path:
                    try:
                        with open(orig_path, 'rb') as f:
                            content = f.read()
                            parts.append(f"T:{t_info['type']}={hashlib.md5(content).hexdigest()}")
                    except:
                        pass
        
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
                        # Format value for C output based on parameter type
                        formatted_value = self._format_param_value_for_c(param_value, param_def)
                        params.append((path, param_name, formatted_value))

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

    def _format_param_value_for_c(self, value: Any, param_def) -> str:
        """Format parameter value for C code output based on parameter type"""
        if value is None:
            return "0"

        # Handle boolean values
        if isinstance(value, bool):
            return "1" if value else "0"

        # Handle string values that might be booleans
        if isinstance(value, str):
            val_lower = value.lower()
            if val_lower in ('true', 'yes', 'on'):
                return "1"
            if val_lower in ('false', 'no', 'off'):
                return "0"

        # Handle enumeration parameters
        if param_def and param_def.param_type == EcucParameterType.ENUMERATION:
            if param_def.literals and isinstance(value, str):
                # Convert enum literal to its index
                try:
                    index = param_def.literals.index(value)
                    return str(index)
                except ValueError:
                    # Literal not found, return as-is (might be already an index)
                    pass

        # Handle integer values
        if isinstance(value, int):
            return str(value)

        # Handle float values
        if isinstance(value, float):
            return f"{value}f"

        # Default: return string representation
        return str(value)
        
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
#define {{{{ module_name.upper() }}}}_{{{{ path_name_value.0.upper() }}}}_{{{{ path_name_value.1.upper() }}}}    ({{{{ path_name_value.2 }}}}) /* {{{{ path_name_value.1 }}}} */
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
    ./* {{{{ path_name_value.0 }}}} */{{{{ path_name_value.1 }}}} = {{{{ path_name_value.2 }}}},
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
    ./* {{{{ path_name_value.0 }}}} */{{{{ path_name_value.1 }}}} = {{{{ path_name_value.2 }}}},
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

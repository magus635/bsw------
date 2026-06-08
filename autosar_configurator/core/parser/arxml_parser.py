"""
ARXML Parser for AUTOSAR configuration files
"""
from lxml import etree
from typing import Optional, Dict, List, Any
from pathlib import Path
import re
from ..model.container import Container, Parameter
from ..model.base import ArxmlElement
from ..model.ecuc_model import EcucContainer, EcucParameter, EcucReference
from ..model.configuration_model import EcucModuleConfiguration, EcucContainerValue


# AUTOSAR element naming convention: uppercase letter followed by uppercase
# letters, digits, and hyphens. Used to reject XPath-injecting tag names.
_VALID_TAG_NAME = re.compile(r'^[A-Z][A-Z0-9-]*$')


class ArxmlParser:
    """Parser for AUTOSAR ARXML files"""

    # AUTOSAR XML namespaces
    NAMESPACES = {
        'ar': 'http://autosar.org/schema/r4.0',
        'xsi': 'http://www.w3.org/2001/XMLSchema-instance'
    }

    def __init__(self, schema_path: Optional[Path] = None):
        """Initialize parser

        Args:
            schema_path: Optional path to AUTOSAR XSD schema for validation
        """
        self.schema_path = schema_path
        self.schema = None
        if schema_path and schema_path.exists():
            self._load_schema()

    def _load_schema(self):
        """Load XSD schema for validation"""
        try:
            # Safe parser to prevent XXE via a malicious XSD
            _safe = etree.XMLParser(resolve_entities=False, no_network=True)
            schema_doc = etree.parse(str(self.schema_path), _safe)
            self.schema = etree.XMLSchema(schema_doc)
        except Exception as e:
            raise ValueError(f"Failed to load schema: {e}")

    def parse_file(self, file_path: Path) -> Container:
        """Parse ARXML file and return root container

        Args:
            file_path: Path to ARXML file

        Returns:
            Root container with parsed content
        """
        if not file_path.exists():
            raise FileNotFoundError(f"File not found: {file_path}")

        try:
            # Safe parser to prevent XXE (disable entity resolution)
            parser = etree.XMLParser(resolve_entities=False, no_network=True)
            tree = etree.parse(str(file_path), parser=parser)

            # Validate against schema if available
            if self.schema:
                if not self.schema.validate(tree):
                    errors = self.schema.error_log
                    raise ValueError(f"Schema validation failed: {errors}")

            root = tree.getroot()

            # Check if this is an AUTOSAR root element
            if 'AUTOSAR' in root.tag:
                # Create a wrapper container and parse all AR-PACKAGES as sub-containers
                root_container = Container(short_name="AUTOSAR")

                # Find AR-PACKAGES element
                ar_packages_elem = self._find_descendant(root, 'AR-PACKAGES')

                if ar_packages_elem is not None:
                    # Parse only immediate AR-PACKAGE elements to avoid duplication
                    ar_packages = self._findall_children(ar_packages_elem, 'AR-PACKAGE')
                    
                    for ar_package in ar_packages:
                        # Parse AR-PACKAGE as a container
                        package_container = self._parse_ar_package(ar_package)
                        if package_container:
                            root_container.add_sub_container(package_container)

                return root_container

            # Otherwise parse as direct container
            return self._parse_container(root)

        except etree.XMLSyntaxError as e:
            raise ValueError(f"XML parsing error: {e}")

    def parse_string(self, xml_string: str) -> Container:
        """Parse ARXML from string

        Args:
            xml_string: XML content as string

        Returns:
            Root container with parsed content
        """
        try:
            # Safe parser to prevent XXE
            parser = etree.XMLParser(resolve_entities=False, no_network=True)
            root = etree.fromstring(xml_string.encode('utf-8'), parser=parser)

            # Check if this is an AUTOSAR root element
            if 'AUTOSAR' in root.tag:
                # Navigate to the first container in AR-PACKAGES/AR-PACKAGE/ELEMENTS
                elements = self._find_descendant(root, 'ELEMENTS')
                if elements is not None:
                    container_elem = self._find_descendant(elements, 'CONTAINER')
                    if container_elem is not None:
                        return self._parse_container(container_elem)

            # Otherwise parse as direct container
            return self._parse_container(root)
        except etree.XMLSyntaxError as e:
            raise ValueError(f"XML parsing error: {e}")

    def _parse_ar_package(self, element: etree._Element) -> Optional[Container]:
        """Parse AR-PACKAGE element into Container

        Args:
            element: AR-PACKAGE XML element to parse

        Returns:
            Parsed Container object representing the package
        """
        # Extract short-name
        short_name = self._get_short_name(element)
        if not short_name:
            short_name = "UnnamedPackage"

        # Create container for the package
        package_container = Container(short_name=short_name)

        # Parse description
        package_container.description = self._get_description(element)

        # Parse elements in the package
        elements = self._find_descendant(element, 'ELEMENTS')

        if elements is not None:
            # Parse only immediate ECUC-MODULE-DEF elements
            for module_def in self._findall_children(elements, 'ECUC-MODULE-DEF'):
                module = self.parse_ecuc_module_def(module_def)
                if module:
                    package_container.add_sub_container(module)
            
            # Parse all containers in elements (direct children only)
            for container_elem in self._findall_children(elements, 'CONTAINER'):
                sub_container = self._parse_container(container_elem)
                if sub_container:
                    package_container.add_sub_container(sub_container)

        # Parse nested AR-PACKAGEs
        ar_packages_elem = self._find_descendant(element, 'AR-PACKAGES')

        if ar_packages_elem is not None:
            # Parse only immediate AR-PACKAGE elements
            for nested_package in self._findall_children(ar_packages_elem, 'AR-PACKAGE'):
                nested_container = self._parse_ar_package(nested_package)
                if nested_container:
                    package_container.add_sub_container(nested_container)

        return package_container

    def _parse_container(self, element: etree._Element) -> Container:
        """Parse XML element into Container

        Args:
            element: XML element to parse

        Returns:
            Parsed Container object
        """
        # Extract short-name
        short_name = self._get_short_name(element)
        if not short_name:
            short_name = "UnnamedContainer"

        # Create container
        container = Container(short_name=short_name)

        # Parse description
        container.description = self._get_description(element)

        # Parse parameters
        param_container = self._find_descendant(element, 'PARAMETERS')

        if param_container is not None:
            for param_elem in self._findall_children(param_container, 'PARAMETER'):
                param = self._parse_parameter(param_elem)
                if param:
                    container.add_parameter(param)

        # Parse sub-containers
        sub_containers_elem = self._find_descendant(element, 'SUB-CONTAINERS')

        if sub_containers_elem is not None:
            for container_elem in self._findall_children(sub_containers_elem, 'CONTAINER'):
                sub_container = self._parse_container(container_elem)
                if sub_container:
                    container.add_sub_container(sub_container)

        # Parse references
        refs_elem = self._find_descendant(element, 'REFERENCES')

        if refs_elem is not None:
            # For references, we just want direct children usually, or specific REFERENCE types
            # iterating over all children to handle unknown tags
            for ref_elem in refs_elem:
                # Basic handling: use tag as name (strip namespace)
                ref_name = etree.QName(ref_elem).localname
                if ref_elem.text:
                    container.references[ref_name] = ref_elem.text

        return container

    def _parse_parameter(self, element: etree._Element) -> Optional[Parameter]:
        """Parse XML element into Parameter

        Args:
            element: XML element to parse

        Returns:
            Parsed Parameter object or None if invalid
        """
        # Extract short-name
        short_name = self._get_short_name(element)
        if not short_name:
            return None

        # Extract type
        type_elem = self._find_descendant(element, 'TYPE')
        value_type = type_elem.text if type_elem is not None else "STRING"
        
        # Extract value based on type
        value = None
        
        if value_type == "ARRAY":
            array_elem = self._find_descendant(element, 'ARRAY-VALUES')
            if array_elem is not None:
                value = []
                for val_elem in self._findall_descendants(array_elem, 'VALUE'):
                    if val_elem.text:
                        value.append(val_elem.text)
        
        elif value_type == "STRUCT":
            struct_elem = self._find_descendant(element, 'STRUCT-VALUES')
            if struct_elem is not None:
                value = {}
                for field_elem in self._findall_descendants(struct_elem, 'STRUCT-VALUE'):
                    name_elem = self._find_descendant(field_elem, 'NAME')
                    val_elem = self._find_descendant(field_elem, 'VALUE')
                    if name_elem is not None and name_elem.text and val_elem is not None:
                        value[name_elem.text] = val_elem.text
                            
        # Fallback to simple value
        if value is None:
            value_elem = self._find_descendant(element, 'VALUE')
            value = value_elem.text if value_elem is not None else None

        # Create parameter
        param = Parameter(
            short_name=short_name,
            value=value,
            value_type=value_type
        )
        
        # Parse content type for arrays
        content_type_elem = self._find_descendant(element, 'CONTENT-TYPE')
        if content_type_elem is not None and content_type_elem.text:
            param.content_type = content_type_elem.text

        # Parse min/max values
        min_elem = self._find_descendant(element, 'MIN-VALUE')
        if min_elem is not None and min_elem.text:
            try:
                param.min_value = float(min_elem.text)
            except ValueError:
                pass

        max_elem = self._find_descendant(element, 'MAX-VALUE')
        if max_elem is not None and max_elem.text:
            try:
                param.max_value = float(max_elem.text)
            except ValueError:
                pass

        # Parse enum values
        enum_elem = self._find_descendant(element, 'ENUM-VALUES')

        if enum_elem is not None:
            enum_values = []
            for val_elem in self._findall_descendants(enum_elem, 'ENUM-VALUE'):
                if val_elem.text and val_elem.text not in enum_values:
                    enum_values.append(val_elem.text)

            if enum_values:
                param.enum_values = enum_values

        # Parse unit
        unit_elem = self._find_descendant(element, 'UNIT')
        if unit_elem is not None and unit_elem.text:
            param.unit = unit_elem.text

        # Parse description
        param.description = self._get_description(element)

        return param

    def extract_module_definitions(self, file_path: Path) -> List[Dict[str, Any]]:
        """Extract module definitions from AUTOSAR ARXML

        Args:
            file_path: Path to ARXML file

        Returns:
            List of module definitions
        """
        if not file_path.exists():
            raise FileNotFoundError(f"File not found: {file_path}")

        # Safe parser to prevent XXE
        parser = etree.XMLParser(resolve_entities=False, no_network=True)
        tree = etree.parse(str(file_path), parser=parser)
        root = tree.getroot()

        modules = []

        # Look for module definitions
        module_defs = self._findall_descendants(root, 'MODULE-DEF')

        for module_def in module_defs:
            short_name = self._get_short_name(module_def)
            if short_name:
                modules.append({
                    'name': short_name,
                    'element': module_def
                })

        return modules
    
    # ========== ECUC-specific parsing methods ==========
    
    def parse_ecuc_module_def(self, element: etree._Element) -> Optional[EcucContainer]:
        """Parse ECUC-MODULE-DEF element into EcucContainer
        
        Args:
            element: ECUC-MODULE-DEF XML element
            
        Returns:
            EcucContainer representing the module definition
        """
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        module = EcucContainer(
            short_name=short_name,
            ecuc_type="ECUC-MODULE-DEF"
        )
        
        # Parse description
        module.description = self._get_description(element)
        
        # Parse CONTAINERS element
        containers_elem = self._find_descendant(element, 'CONTAINERS')
        if containers_elem is not None:
            # Find only immediate container defs
            for cont_def in self._findall_children(containers_elem, 'ECUC-PARAM-CONF-CONTAINER-DEF'):
                sub_container = self._parse_ecuc_container_def(cont_def)
                if sub_container:
                    module.add_sub_container(sub_container)
        
        return module
    
    def _parse_ecuc_container_def(self, element: etree._Element) -> Optional[EcucContainer]:
        """Parse ECUC-PARAM-CONF-CONTAINER-DEF element
        
        Args:
            element: ECUC-PARAM-CONF-CONTAINER-DEF XML element
            
        Returns:
            EcucContainer with full metadata
        """
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        container = EcucContainer(
            short_name=short_name,
            ecuc_type="ECUC-PARAM-CONF-CONTAINER-DEF"
        )
        
        # Parse description
        container.description = self._get_description(element)

        # Parse multiplicity (use direct child lookup to avoid finding sub-container's multiplicity)
        container.lower_multiplicity = self._get_child_int_value(element, 'LOWER-MULTIPLICITY', 0)

        # Check for UPPER-MULTIPLICITY-INFINITE first (AUTOSAR variant for unlimited)
        upper_mult_infinite = self._get_child_text_value(element, 'UPPER-MULTIPLICITY-INFINITE')
        upper_mult = self._get_child_text_value(element, 'UPPER-MULTIPLICITY')

        if upper_mult_infinite and upper_mult_infinite.lower() in ('1', 'true'):
            container.upper_multiplicity = -1
        elif upper_mult == '*':
            container.upper_multiplicity = -1
        else:
            container.upper_multiplicity = int(upper_mult) if upper_mult else 1
        
        # Parse PARAMETERS
        params_elem = self._find_descendant(element, 'PARAMETERS')
        if params_elem is not None:
            # Using direct iteration or findall for generic parameter handling
            # Note: Skip non-element nodes (comments, PIs) where .tag is not a string
            for param_def in params_elem:
                # Check for parameter definition tags (ECUC-*-PARAM-DEF)
                if isinstance(param_def.tag, str) and 'PARAM-DEF' in param_def.tag:
                    param = self._parse_ecuc_parameter_def(param_def)
                    if param:
                        container.add_parameter(param)
        
        # Parse REFERENCES
        refs_elem = self._find_descendant(element, 'REFERENCES')
        if refs_elem is not None:
            # Find all reference defs (support CHOICE, INSTANCE, FOREIGN, etc.)
            for ref_def in refs_elem:
                if isinstance(ref_def.tag, str) and ref_def.tag.split('}')[-1].endswith('REFERENCE-DEF'):
                    ref = self._parse_ecuc_reference_def(ref_def)
                    if ref:
                        container.add_reference_def(ref)
        
        # Parse SUB-CONTAINERS recursively
        sub_conts_elem = self._find_descendant(element, 'SUB-CONTAINERS')
        if sub_conts_elem is not None:
            # Find only immediate sub-container defs
            for sub_cont_def in self._findall_children(sub_conts_elem, 'ECUC-PARAM-CONF-CONTAINER-DEF'):
                sub_container = self._parse_ecuc_container_def(sub_cont_def)
                if sub_container:
                    container.add_sub_container(sub_container)
        
        return container
    
    def _parse_ecuc_parameter_def(self, element: etree._Element) -> Optional[EcucParameter]:
        """Parse ECUC parameter definition element"""
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        # Determine parameter type from tag (localname)
        param_type = etree.QName(element).localname
        
        param = EcucParameter(
            short_name=short_name,
            param_def_type=param_type
        )
        
        # Parse description
        param.description = self._get_description(element)
        
        # Parse multiplicity (use direct child lookup)
        param.lower_multiplicity = self._get_child_int_value(element, 'LOWER-MULTIPLICITY', 0)
        param.upper_multiplicity = self._get_child_int_value(element, 'UPPER-MULTIPLICITY', 1)
        
        # Parse type-specific fields
        if param_type == 'ECUC-ENUMERATION-PARAM-DEF':
            param.value_type = "ENUM"
            # Parse LITERALS
            literals_elem = self._find_descendant(element, 'LITERALS')
            if literals_elem is not None:
                literals = []
                for lit_def in self._findall_descendants(literals_elem, 'ECUC-ENUMERATION-LITERAL-DEF'):
                    lit_name = self._get_short_name(lit_def)
                    if lit_name:
                        literals.append(lit_name)
                param.literals = literals
        
        elif param_type == 'ECUC-INTEGER-PARAM-DEF':
            param.value_type = "INTEGER"
            param.min_value = self._get_int_value(element, 'MIN')
            param.max_value = self._get_int_value(element, 'MAX')
        
        elif param_type == 'ECUC-FLOAT-PARAM-DEF':
            param.value_type = "FLOAT"
            param.min_value = self._get_float_value(element, 'MIN')
            param.max_value = self._get_float_value(element, 'MAX')
        
        elif param_type == 'ECUC-BOOLEAN-PARAM-DEF':
            param.value_type = "BOOLEAN"
        
        elif param_type == 'ECUC-STRING-PARAM-DEF':
            param.value_type = "STRING"
        
        # Parse DEFAULT-VALUE
        default_val = self._get_text_value(element, 'DEFAULT-VALUE')
        if default_val:
            param.value = default_val
        
        # Parse SCOPE
        scope = self._get_text_value(element, 'SCOPE')
        if scope:
            param.scope = scope
        
        # Parse ORIGIN
        origin = self._get_text_value(element, 'ORIGIN')
        if origin:
            param.origin = origin
        
        return param
    
    def _parse_ecuc_reference_def(self, element: etree._Element) -> Optional[EcucReference]:
        """Parse ECUC-REFERENCE-DEF element"""
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        ref = EcucReference(short_name=short_name)
        
        # Parse description
        ref.description = self._get_description(element)
        
        # Parse DESTINATION-REF
        dest_ref_elem = self._find_descendant(element, 'DESTINATION-REF')
        if dest_ref_elem is not None:
            ref.destination_ref = dest_ref_elem.text or ""
            ref.destination_type = dest_ref_elem.get('DEST', 'ECUC-PARAM-CONF-CONTAINER-DEF')
        
        # Parse multiplicity (use direct child lookup)
        ref.lower_multiplicity = self._get_child_int_value(element, 'LOWER-MULTIPLICITY', 0)
        
        upper_mult = self._get_text_value(element, 'UPPER-MULTIPLICITY')
        upper_mult_infinite = self._get_text_value(element, 'UPPER-MULTIPLICITY-INFINITE')
        
        if upper_mult_infinite and upper_mult_infinite.lower() in ('1', 'true'):
            ref.upper_multiplicity = -1
        elif upper_mult == '*':
            ref.upper_multiplicity = -1
        else:
            ref.upper_multiplicity = int(upper_mult) if upper_mult else 1
        
        return ref
    
    def parse_ecuc_configuration_values(self, element: etree._Element) -> Optional[EcucModuleConfiguration]:
        """Parse ECUC-MODULE-CONFIGURATION-VALUES element
        
        Args:
            element: ECUC-MODULE-CONFIGURATION-VALUES XML element
            
        Returns:
            EcucModuleConfiguration object
        """
        short_name = self._get_short_name(element)
        if not short_name:
            return None
            
        # Get definition reference
        definition_ref = self._get_text_value(element, 'DEFINITION-REF') or ""
        
        config = EcucModuleConfiguration(
            short_name=short_name,
            definition_ref=definition_ref
        )

        # Parse IMPLEMENTATION-CONFIG-VARIANT
        variant_text = self._get_text_value(element, 'IMPLEMENTATION-CONFIG-VARIANT')
        if variant_text:
            config.implementation_config_variant = variant_text
        
        # Parse containers
        containers_elem = self._find_descendant(element, 'CONTAINERS')
        if containers_elem is not None:
            # Initialize global definition counts mapping for unique auto-indexing
            if not hasattr(self, '_def_counts'):
                self._def_counts = {}
            # Find only immediate container values
            for container_elem in self._findall_children(containers_elem, 'ECUC-CONTAINER-VALUE'):
                container = self._parse_ecuc_container_value(container_elem)
                if container:
                    # Assign index if not explicitly set in the container
                    if not getattr(container, '_has_explicit_index', False):
                        d_ref = self._normalize_def_ref(container.definition_ref)
                        container.index = self._def_counts.get(d_ref, 0)
                        self._def_counts[d_ref] = container.index + 1
                    config.add_container(container)
                    
        return config

    def _parse_ecuc_container_value(self, element: etree._Element) -> Optional[EcucContainerValue]:
        """Parse ECUC-CONTAINER-VALUE element"""
        short_name = self._get_short_name(element)
        if not short_name:
            return None
            
        # Get definition reference
        definition_ref = self._get_text_value(element, 'DEFINITION-REF') or ""
        
        container = EcucContainerValue(
            short_name=short_name,
            definition_ref=definition_ref
        )

        # Parse UUID attribute if present
        uuid_val = element.get('UUID') or element.get('uuid')
        if uuid_val:
            container.uuid = uuid_val

        # Parse DEFINITION-REF DEST attribute
        def_dest = self._get_def_ref_dest(element)
        if def_dest:
            container.def_dest_type = def_dest
        
        # Normalized def-ref for indexing
        norm_def_ref = self._normalize_def_ref(definition_ref)
        
        # Parse INDEX if present (must be a direct child)
        index_elem = self._find_child(element, 'INDEX')
        if index_elem is not None:
            try:
                container.index = int(index_elem.text)
                container._has_explicit_index = True
            except (ValueError, TypeError):
                pass
        
        # Parse parameters (all types: numerical, textual, enumeration, etc.)
        param_values_elem = self._find_child(element, 'PARAMETER-VALUES')
        if param_values_elem is not None:
            for param_elem in param_values_elem:
                # Check for any tag ending with -PARAM-VALUE
                tag_local = etree.QName(param_elem).localname
                if 'PARAM-VALUE' in tag_local:
                    self._parse_ecuc_parameter_value(param_elem, container)

        # Parse references
        ref_values_elem = self._find_child(element, 'REFERENCE-VALUES')
        if ref_values_elem is not None:
            for ref_elem in ref_values_elem:
                if isinstance(ref_elem.tag, str) and ref_elem.tag.split('}')[-1].endswith('REFERENCE-VALUE'):
                    self._parse_ecuc_reference_value(ref_elem, container)

        # Parse sub-containers
        sub_containers_elem = self._find_child(element, 'SUB-CONTAINERS')
        if sub_containers_elem is not None:
            # Find only immediate sub-container values
            for sub_elem in self._findall_children(sub_containers_elem, 'ECUC-CONTAINER-VALUE'):
                sub_container = self._parse_ecuc_container_value(sub_elem)
                if sub_container:
                    # Assign index if not explicitly set
                    if not getattr(sub_container, '_has_explicit_index', False):
                        sd_ref = self._normalize_def_ref(sub_container.definition_ref)
                        if not hasattr(self, '_def_counts'):
                            self._def_counts = {}
                        sub_container.index = self._def_counts.get(sd_ref, 0)
                        self._def_counts[sd_ref] = sub_container.index + 1
                    
                    sub_container.parent = container
                    container.add_sub_container(sub_container)
                    
        return container

    def _parse_ecuc_parameter_value(self, element: etree._Element, container: EcucContainerValue):
        """Parse parameter value and add to container"""
        # Get definition reference
        definition_ref = self._get_text_value(element, 'DEFINITION-REF') or ""
        if not definition_ref:
            return

        param_name = definition_ref.split('/')[-1]

        # Get DEST attribute from DEFINITION-REF
        dest_type = self._get_def_ref_dest(element)
        
        # Get value
        value = self._get_text_value(element, 'VALUE')

        # Check for INDEX (multi-valued parameters)
        index_text = self._get_text_value(element, 'INDEX')
        
        # Determine if it's numerical (try to convert) if tag implies it
        # Or just try smart conversion based on content?
        # The element tag tells us if it's numerical or textual.
        # Try smart conversion for all parameter values (handle true/false strings)
        if value is not None and isinstance(value, str):
            val_lower = value.strip().lower()
            if val_lower == 'true':
                value = True
            elif val_lower == 'false':
                value = False
            elif dest_type == 'ECUC-BOOLEAN-PARAM-DEF':
                # EB Tresos and other tools sometimes write booleans as numeric 1/0
                # Use the DEST attribute hint to preserve Python bool type identity
                if val_lower == '1':
                    value = True
                elif val_lower == '0':
                    value = False
                
        if 'NUMERICAL-PARAM-VALUE' in element.tag or 'TEXTUAL-PARAM-VALUE' in element.tag or 'ENUMERATION-PARAM-VALUE' in element.tag:
            if value is not None and isinstance(value, str):
                val_stripped = value.strip()
                try:
                    # Integer-looking strings: parse as int directly to preserve
                    # exact 64-bit values (avoid IEEE-754 double precision loss).
                    if val_stripped[:2].lower() == '0x':
                        # Hex literal — must be checked BEFORE the 'e' heuristic
                        # below, because hex nibbles include 'e'/'E' (0xFE, 0xCAFE,
                        # 0xDEAD) which would otherwise be misrouted to float().
                        value = int(val_stripped, 16)
                    elif '.' not in val_stripped and 'e' not in val_stripped.lower():
                        try:
                            # int(.., 0) also handles 0o/0b literals.
                            value = int(val_stripped, 0)
                        except ValueError:
                            # Fall back to base-10 (e.g. leading-zero decimals "010").
                            value = int(val_stripped)
                    else:
                        # Handles 1e-06, 1.0, etc.
                        value = float(val_stripped)
                except (ValueError, TypeError):
                    # Keep as original string
                    pass
                
        if index_text is not None:
            try:
                index_val = int(index_text)
            except (ValueError, TypeError):
                index_val = 0
            container.add_multi_parameter_value(param_name, value, definition_ref, index_val)
            # Set dest_type on the newly added multi-param
            if dest_type and param_name in container.multi_parameter_values:
                container.multi_parameter_values[param_name][-1].dest_type = dest_type
        else:
            container.set_parameter_value(param_name, value, definition_ref)
            # Set dest_type on the parameter
            if dest_type and param_name in container.parameter_values:
                container.parameter_values[param_name].dest_type = dest_type

    def _parse_ecuc_reference_value(self, element: etree._Element, container: EcucContainerValue):
        """Parse reference value and add to container"""
        # Get definition reference
        definition_ref = self._get_text_value(element, 'DEFINITION-REF') or ""
        if not definition_ref:
            return

        ref_name = definition_ref.split('/')[-1]

        # Get DEST attribute from DEFINITION-REF
        dest_type = self._get_def_ref_dest(element)

        # Check for INDEX (multi-valued references)
        index_text = self._get_text_value(element, 'INDEX')

        # Get target reference
        # Standard: VALUE-REF
        target_ref = self._get_text_value(element, 'VALUE-REF')

        # Instance Reference: TARGET-REF inside VALUE-IREF or directly
        if target_ref is None:
            target_ref = self._get_text_value(element, 'TARGET-REF')

        if target_ref is None:
            # Try finding descendant TARGET-REF (for IREF structure)
            iref_target = self._find_descendant(element, 'TARGET-REF')
            if iref_target is not None:
                target_ref = iref_target.text

        if target_ref is None:
            target_ref = ""
        
        # Ensure target_ref is stripped of whitespace properly.
        # This handles cases where target_ref might be None and then set to ""
        # or if it was found but has leading/trailing whitespace.
        target_ref = target_ref.strip()

        # Route to multi-valued or single-valued storage
        if index_text is not None:
            try:
                index_val = int(index_text)
            except (ValueError, TypeError):
                index_val = 0
            container.add_multi_reference_value(ref_name, target_ref, definition_ref, index_val)
            # Set dest_type on the newly added ref
            if dest_type and ref_name in container.multi_reference_values:
                container.multi_reference_values[ref_name][-1].dest_type = dest_type
        else:
            # EB Tresos compatibility: If a reference with the same name already exists,
            # it should be treated as a multi-reference even if INDEX is missing.
            if ref_name in container.reference_values:
                # Move existing single ref to multi-refs
                existing_ref = container.reference_values.pop(ref_name)
                # Ensure it's in the list
                if ref_name not in container.multi_reference_values:
                    container.multi_reference_values[ref_name] = []
                container.multi_reference_values[ref_name].append(existing_ref)
                
                # Add the new one as a multi-ref
                container.add_multi_reference_value(ref_name, target_ref, definition_ref, len(container.multi_reference_values[ref_name]))
                if dest_type:
                    container.multi_reference_values[ref_name][-1].dest_type = dest_type
            elif ref_name in container.multi_reference_values:
                # Already in multi-refs, just append
                container.add_multi_reference_value(ref_name, target_ref, definition_ref, len(container.multi_reference_values[ref_name]))
                if dest_type:
                    container.multi_reference_values[ref_name][-1].dest_type = dest_type
            else:
                # First time seeing this ref name, treat as single
                container.set_reference_value(ref_name, target_ref, definition_ref)
                # Set dest_type on the reference
                if dest_type and ref_name in container.reference_values:
                    container.reference_values[ref_name].dest_type = dest_type

    # Helper methods for Permissive Parsing

    def _find_child(self, element: etree._Element, tag_name: str) -> Optional[etree._Element]:
        """Find first DIRECT child with tag_name, ignoring namespace.

        Unlike _find_descendant, this only searches immediate children,
        preventing accidental matches in nested sub-containers.
        """
        for child in element:
            if isinstance(child.tag, str):
                local_name = child.tag.split('}')[-1] if '}' in child.tag else child.tag
                if local_name == tag_name:
                    return child
        return None

    def _normalize_def_ref(self, def_ref: str) -> str:
        """Strip instance suffixes (e.g., _0, _1) from definition references"""
        if not def_ref:
            return ""
        
        parts = def_ref.split('/')
        if not parts:
            return def_ref
            
        last_segment = parts[-1]
        normalized_last = re.sub(r'_\d+$', '', last_segment)
        
        result = def_ref
        if normalized_last != last_segment:
            result = '/'.join(parts[:-1] + [normalized_last])
        
        # print(f"DEBUG_NORM: {def_ref} -> {result}")
        return result

    def _find_descendant(self, element: etree._Element, tag_name: str) -> Optional[etree._Element]:
        """Find first descendant with tag_name, ignoring namespace"""
        # Guard against XPath injection: tag_name must be an AUTOSAR element name
        if not _VALID_TAG_NAME.match(tag_name):
            raise ValueError(f"Invalid tag_name: {tag_name!r}")
        # 1. Try direct find with namespace (fastest) - Assumes AR namespace
        elem = element.find(f".//ar:{tag_name}", self.NAMESPACES)
        if elem is not None:
            return elem
            
        # 2. Try XPath with local-name (namespace agnostic)
        xpath = f".//*[local-name()='{tag_name}']"
        matches = element.xpath(xpath)
        if matches:
            return matches[0]
            
        return None
        
    def _findall_descendants(self, element: etree._Element, tag_name: str) -> List[etree._Element]:
        """Find all descendants with tag_name, ignoring namespace"""
        # Guard against XPath injection: tag_name must be an AUTOSAR element name
        if not _VALID_TAG_NAME.match(tag_name):
            raise ValueError(f"Invalid tag_name: {tag_name!r}")
        # 1. Try direct find with namespace
        elems = element.findall(f".//ar:{tag_name}", self.NAMESPACES)
        if elems:
            return elems
            
        # 2. XPath local-name
        xpath = f".//*[local-name()='{tag_name}']"
        return element.xpath(xpath)

    def _findall_children(self, element: etree._Element, tag_name: str) -> List[etree._Element]:
        """Find immediate children with tag_name, ignoring namespace"""
        # Guard against XPath injection: tag_name must be an AUTOSAR element name
        if not _VALID_TAG_NAME.match(tag_name):
            raise ValueError(f"Invalid tag_name: {tag_name!r}")
        # 1. Try direct find with namespace
        elems = element.findall(f"ar:{tag_name}", self.NAMESPACES)
        if elems:
            return elems
            
        # 2. XPath local-name
        xpath = f"./*[local-name()='{tag_name}']"
        return element.xpath(xpath)

    def _get_short_name(self, element: etree._Element) -> Optional[str]:
        """Extract SHORT-NAME from element"""
        # SHORT-NAME is typically a direct child
        for child in element:
            if etree.QName(child).localname == 'SHORT-NAME':
                return child.text
        return None
    
    def _get_description(self, element: etree._Element) -> str:
        """Extract DESC/L-2 from element"""
        # Try finding L-2 anywhere
        l2_elem = self._find_descendant(element, 'L-2')
        if l2_elem is not None and l2_elem.text:
            return l2_elem.text
            
        # Fallback to DESC
        desc_elem = self._find_descendant(element, 'DESC')
        if desc_elem is not None and desc_elem.text:
            return desc_elem.text
        
        return ""
    
    def _get_text_value(self, element: etree._Element, tag_name: str) -> Optional[str]:
        """Get text value of a descendant"""
        elem = self._find_descendant(element, tag_name)
        return elem.text if elem is not None else None

    def _get_def_ref_dest(self, element: etree._Element) -> Optional[str]:
        """Get the DEST attribute from DEFINITION-REF element"""
        def_ref_elem = self._find_descendant(element, 'DEFINITION-REF')
        if def_ref_elem is not None:
            return def_ref_elem.get('DEST')
        return None

    def _find_child(self, element: etree._Element, tag_name: str) -> Optional[etree._Element]:
        """Find first immediate child with tag_name, ignoring namespace"""
        children = self._findall_children(element, tag_name)
        return children[0] if children else None

    def _get_child_text_value(self, element: etree._Element, tag_name: str) -> Optional[str]:
        """Get text value of a direct child element only (not descendants)"""
        elem = self._find_child(element, tag_name)
        return elem.text if elem is not None else None

    def _get_child_int_value(self, element: etree._Element, tag_name: str, default: int = 0) -> int:
        """Get integer value of a direct child element only (not descendants)"""
        text = self._get_child_text_value(element, tag_name)
        try:
            return int(text) if text else default
        except ValueError:
            return default

    def _get_int_value(self, element: etree._Element, tag_name: str, default: int = 0) -> int:
        """Get integer value of a descendant"""
        text = self._get_text_value(element, tag_name)
        try:
            return int(text) if text else default
        except ValueError:
            return default
            
    def _get_float_value(self, element: etree._Element, tag_name: str, default: float = 0.0) -> float:
        """Get float value of a descendant"""
        text = self._get_text_value(element, tag_name)
        try:
            return float(text) if text else default
        except ValueError:
            return default

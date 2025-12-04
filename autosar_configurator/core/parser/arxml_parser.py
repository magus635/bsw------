"""
ARXML Parser for AUTOSAR configuration files
"""
from lxml import etree
from typing import Optional, Dict, List, Any
from pathlib import Path
from ..model.container import Container, Parameter
from ..model.base import ArxmlElement
from ..model.ecuc_model import EcucContainer, EcucParameter, EcucReference
from ..model.configuration_model import EcucModuleConfiguration, EcucContainerValue


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
            schema_doc = etree.parse(str(self.schema_path))
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
            tree = etree.parse(str(file_path))

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
                ar_packages_elem = root.find('.//ar:AR-PACKAGES', self.NAMESPACES)
                if ar_packages_elem is None:
                    ar_packages_elem = root.find('.//AR-PACKAGES')

                if ar_packages_elem is not None:
                    # Parse all AR-PACKAGE elements
                    ar_packages = ar_packages_elem.findall('ar:AR-PACKAGE', self.NAMESPACES)
                    if not ar_packages:
                        ar_packages = ar_packages_elem.findall('AR-PACKAGE')

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
            root = etree.fromstring(xml_string.encode('utf-8'))

            # Check if this is an AUTOSAR root element
            if 'AUTOSAR' in root.tag:
                # Navigate to the first container in AR-PACKAGES/AR-PACKAGE/ELEMENTS
                elements = root.find('.//ELEMENTS')
                if elements is not None:
                    container_elem = elements.find('CONTAINER')
                    if container_elem is not None:
                        return self._parse_container(container_elem)

                # Try with namespace
                elements = root.find('.//ar:ELEMENTS', self.NAMESPACES)
                if elements is not None:
                    container_elem = elements.find('ar:CONTAINER', self.NAMESPACES)
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
        short_name_elem = element.find('ar:SHORT-NAME', self.NAMESPACES)
        if short_name_elem is None:
            short_name_elem = element.find('SHORT-NAME')

        short_name = short_name_elem.text if short_name_elem is not None else "UnnamedPackage"

        # Create container for the package
        package_container = Container(short_name=short_name)

        # Parse description
        desc_elem = element.find('ar:DESC', self.NAMESPACES)
        if desc_elem is None:
            desc_elem = element.find('DESC')
        if desc_elem is not None and desc_elem.text:
            package_container.description = desc_elem.text

        # Parse elements in the package
        elements = element.find('ar:ELEMENTS', self.NAMESPACES)
        if elements is None:
            elements = element.find('ELEMENTS')

        if elements is not None:
            # Check for ECUC-MODULE-DEF elements (ECUC structure)
            for module_def in elements.findall('ar:ECUC-MODULE-DEF', self.NAMESPACES):
                ecuc_module = self.parse_ecuc_module_def(module_def)
                if ecuc_module:
                    package_container.add_sub_container(ecuc_module)
            
            # Parse all containers in elements (direct children only)
            for container_elem in elements.findall('ar:CONTAINER', self.NAMESPACES):
                sub_container = self._parse_container(container_elem)
                if sub_container:
                    package_container.add_sub_container(sub_container)

            # Also check without namespace
            for container_elem in elements.findall('CONTAINER'):
                sub_container = self._parse_container(container_elem)
                if sub_container:
                    try:
                        package_container.add_sub_container(sub_container)
                    except ValueError:
                        # Container already exists, skip
                        pass

        # Parse nested AR-PACKAGEs
        ar_packages_elem = element.find('ar:AR-PACKAGES', self.NAMESPACES)
        if ar_packages_elem is None:
            ar_packages_elem = element.find('AR-PACKAGES')

        if ar_packages_elem is not None:
            # Parse all AR-PACKAGE elements (direct children only)
            for nested_package in ar_packages_elem.findall('ar:AR-PACKAGE', self.NAMESPACES):
                nested_container = self._parse_ar_package(nested_package)
                if nested_container:
                    package_container.add_sub_container(nested_container)

            # Also check without namespace
            for nested_package in ar_packages_elem.findall('AR-PACKAGE'):
                nested_container = self._parse_ar_package(nested_package)
                if nested_container:
                    try:
                        package_container.add_sub_container(nested_container)
                    except ValueError:
                        # Container already exists, skip
                        pass

        return package_container

    def _parse_container(self, element: etree._Element) -> Container:
        """Parse XML element into Container

        Args:
            element: XML element to parse

        Returns:
            Parsed Container object
        """
        # Extract short-name
        short_name_elem = element.find('.//ar:SHORT-NAME', self.NAMESPACES)
        if short_name_elem is None:
            short_name_elem = element.find('SHORT-NAME')

        short_name = short_name_elem.text if short_name_elem is not None else "UnnamedContainer"

        # Create container
        container = Container(short_name=short_name)

        # Parse description
        desc_elem = element.find('.//ar:DESC', self.NAMESPACES)
        if desc_elem is None:
            desc_elem = element.find('DESC')
        if desc_elem is not None and desc_elem.text:
            container.description = desc_elem.text

        # Parse parameters
        param_container = element.find('.//ar:PARAMETERS', self.NAMESPACES)
        if param_container is None:
            param_container = element.find('PARAMETERS')

        if param_container is not None:
            for param_elem in param_container.findall('.//ar:PARAMETER', self.NAMESPACES):
                if param_elem is None:
                    continue
                param = self._parse_parameter(param_elem)
                if param:
                    container.add_parameter(param)

            # Also check for parameters without namespace
            for param_elem in param_container.findall('PARAMETER'):
                param = self._parse_parameter(param_elem)
                if param:
                    try:
                        container.add_parameter(param)
                    except ValueError:
                        # Parameter already exists, skip
                        pass

        # Parse sub-containers
        sub_containers_elem = element.find('.//ar:SUB-CONTAINERS', self.NAMESPACES)
        if sub_containers_elem is None:
            sub_containers_elem = element.find('SUB-CONTAINERS')

        if sub_containers_elem is not None:
            for container_elem in sub_containers_elem.findall('.//ar:CONTAINER', self.NAMESPACES):
                if container_elem is None:
                    continue
                sub_container = self._parse_container(container_elem)
                if sub_container:
                    container.add_sub_container(sub_container)

            # Also check for containers without namespace
            for container_elem in sub_containers_elem.findall('CONTAINER'):
                sub_container = self._parse_container(container_elem)
                if sub_container:
                    try:
                        container.add_sub_container(sub_container)
                    except ValueError:
                        # Container already exists, skip
                        pass

        # Parse references
        refs_elem = element.find('.//ar:REFERENCES', self.NAMESPACES)
        if refs_elem is None:
            refs_elem = element.find('REFERENCES')

        if refs_elem is not None:
            for ref_elem in refs_elem:
                ref_name = ref_elem.tag.replace('{' + self.NAMESPACES['ar'] + '}', '')
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
        short_name_elem = element.find('.//ar:SHORT-NAME', self.NAMESPACES)
        if short_name_elem is None:
            short_name_elem = element.find('SHORT-NAME')

        if short_name_elem is None or not short_name_elem.text:
            return None

        short_name = short_name_elem.text

        # Extract type
        type_elem = element.find('.//ar:TYPE', self.NAMESPACES)
        if type_elem is None:
            type_elem = element.find('TYPE')

        value_type = type_elem.text if type_elem is not None else "STRING"
        
        # Extract value based on type
        value = None
        
        if value_type == "ARRAY":
            array_elem = element.find('.//ar:ARRAY-VALUES', self.NAMESPACES)
            if array_elem is None:
                array_elem = element.find('ARRAY-VALUES')
                
            if array_elem is not None:
                value = []
                for val_elem in array_elem.findall('.//ar:VALUE', self.NAMESPACES):
                    if val_elem.text:
                        value.append(val_elem.text)
                # Also check without namespace
                if not value:
                    for val_elem in array_elem.findall('VALUE'):
                        if val_elem.text:
                            value.append(val_elem.text)
        
        elif value_type == "STRUCT":
            struct_elem = element.find('.//ar:STRUCT-VALUES', self.NAMESPACES)
            if struct_elem is None:
                struct_elem = element.find('STRUCT-VALUES')
                
            if struct_elem is not None:
                value = {}
                # Handle namespaced elements
                for field_elem in struct_elem.findall('.//ar:STRUCT-VALUE', self.NAMESPACES):
                    name_elem = field_elem.find('.//ar:NAME', self.NAMESPACES)
                    val_elem = field_elem.find('.//ar:VALUE', self.NAMESPACES)
                    if name_elem is not None and name_elem.text and val_elem is not None:
                        value[name_elem.text] = val_elem.text
                        
                # Handle non-namespaced elements if empty
                if not value:
                    for field_elem in struct_elem.findall('STRUCT-VALUE'):
                        name_elem = field_elem.find('NAME')
                        val_elem = field_elem.find('VALUE')
                        if name_elem is not None and name_elem.text and val_elem is not None:
                            value[name_elem.text] = val_elem.text
                            
        # Fallback to simple value
        if value is None:
            value_elem = element.find('.//ar:VALUE', self.NAMESPACES)
            if value_elem is None:
                value_elem = element.find('VALUE')
            value = value_elem.text if value_elem is not None else None

        # Create parameter
        param = Parameter(
            short_name=short_name,
            value=value,
            value_type=value_type
        )
        
        # Parse content type for arrays
        content_type_elem = element.find('.//ar:CONTENT-TYPE', self.NAMESPACES)
        if content_type_elem is None:
            content_type_elem = element.find('CONTENT-TYPE')
        if content_type_elem is not None and content_type_elem.text:
            param.content_type = content_type_elem.text

        # Parse min/max values
        min_elem = element.find('.//ar:MIN-VALUE', self.NAMESPACES)
        if min_elem is None:
            min_elem = element.find('MIN-VALUE')
        if min_elem is not None and min_elem.text:
            try:
                param.min_value = float(min_elem.text)
            except ValueError:
                pass

        max_elem = element.find('.//ar:MAX-VALUE', self.NAMESPACES)
        if max_elem is None:
            max_elem = element.find('MAX-VALUE')
        if max_elem is not None and max_elem.text:
            try:
                param.max_value = float(max_elem.text)
            except ValueError:
                pass

        # Parse enum values
        enum_elem = element.find('.//ar:ENUM-VALUES', self.NAMESPACES)
        if enum_elem is None:
            enum_elem = element.find('ENUM-VALUES')

        if enum_elem is not None:
            enum_values = []
            for val_elem in enum_elem.findall('.//ar:ENUM-VALUE', self.NAMESPACES):
                if val_elem.text:
                    enum_values.append(val_elem.text)
            # Also check without namespace
            for val_elem in enum_elem.findall('ENUM-VALUE'):
                if val_elem.text and val_elem.text not in enum_values:
                    enum_values.append(val_elem.text)

            if enum_values:
                param.enum_values = enum_values

        # Parse unit
        unit_elem = element.find('.//ar:UNIT', self.NAMESPACES)
        if unit_elem is None:
            unit_elem = element.find('UNIT')
        if unit_elem is not None and unit_elem.text:
            param.unit = unit_elem.text

        # Parse description
        desc_elem = element.find('.//ar:DESC', self.NAMESPACES)
        if desc_elem is None:
            desc_elem = element.find('DESC')
        if desc_elem is not None and desc_elem.text:
            param.description = desc_elem.text

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

        tree = etree.parse(str(file_path))
        root = tree.getroot()

        modules = []

        # Look for module definitions
        module_defs = root.findall('.//ar:MODULE-DEF', self.NAMESPACES)
        if not module_defs:
            module_defs = root.findall('.//MODULE-DEF')

        for module_def in module_defs:
            short_name_elem = module_def.find('.//ar:SHORT-NAME', self.NAMESPACES)
            if short_name_elem is None:
                short_name_elem = module_def.find('SHORT-NAME')

            if short_name_elem is not None and short_name_elem.text:
                modules.append({
                    'name': short_name_elem.text,
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
        containers_elem = element.find('.//ar:CONTAINERS', self.NAMESPACES)
        if containers_elem is not None:
            for cont_def in containers_elem.findall('.//ar:ECUC-PARAM-CONF-CONTAINER-DEF', self.NAMESPACES):
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
        
        # Parse multiplicity
        container.lower_multiplicity = self._get_int_value(element, 'ar:LOWER-MULTIPLICITY', 0)
        upper_mult = self._get_text_value(element, 'ar:UPPER-MULTIPLICITY')
        if upper_mult == '*':
            container.upper_multiplicity = -1
        else:
            container.upper_multiplicity = int(upper_mult) if upper_mult else 1
        
        # Parse PARAMETERS
        params_elem = element.find('.//ar:PARAMETERS', self.NAMESPACES)
        if params_elem is not None:
            for param_def in params_elem:
                param = self._parse_ecuc_parameter_def(param_def)
                if param:
                    container.add_parameter(param)
        
        # Parse REFERENCES
        refs_elem = element.find('.//ar:REFERENCES', self.NAMESPACES)
        if refs_elem is not None:
            for ref_def in refs_elem.findall('.//ar:ECUC-REFERENCE-DEF', self.NAMESPACES):
                ref = self._parse_ecuc_reference_def(ref_def)
                if ref:
                    container.add_reference_def(ref)
        
        # Parse SUB-CONTAINERS recursively
        sub_conts_elem = element.find('.//ar:SUB-CONTAINERS', self.NAMESPACES)
        if sub_conts_elem is not None:
            for sub_cont_def in sub_conts_elem.findall('.//ar:ECUC-PARAM-CONF-CONTAINER-DEF', self.NAMESPACES):
                sub_container = self._parse_ecuc_container_def(sub_cont_def)
                if sub_container:
                    container.add_sub_container(sub_container)
        
        return container
    
    def _parse_ecuc_parameter_def(self, element: etree._Element) -> Optional[EcucParameter]:
        """Parse ECUC parameter definition element
        
        Args:
            element: ECUC parameter element (ECUC-INTEGER-PARAM-DEF, ECUC-ENUMERATION-PARAM-DEF, etc.)
            
        Returns:
            EcucParameter with type-specific metadata
        """
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        # Determine parameter type from tag
        param_type = element.tag.split('}')[-1] if '}' in element.tag else element.tag
        
        param = EcucParameter(
            short_name=short_name,
            param_def_type=param_type
        )
        
        # Parse description
        param.description = self._get_description(element)
        
        # Parse multiplicity
        param.lower_multiplicity = self._get_int_value(element, 'ar:LOWER-MULTIPLICITY', 0)
        param.upper_multiplicity = self._get_int_value(element, 'ar:UPPER-MULTIPLICITY', 1)
        
        # Parse type-specific fields
        if param_type == 'ECUC-ENUMERATION-PARAM-DEF':
            param.value_type = "ENUM"
            # Parse LITERALS
            literals_elem = element.find('.//ar:LITERALS', self.NAMESPACES)
            if literals_elem is not None:
                literals = []
                for lit_def in literals_elem.findall('.//ar:ECUC-ENUMERATION-LITERAL-DEF', self.NAMESPACES):
                    lit_name = self._get_short_name(lit_def)
                    if lit_name:
                        literals.append(lit_name)
                param.literals = literals
        
        elif param_type == 'ECUC-INTEGER-PARAM-DEF':
            param.value_type = "INTEGER"
            param.min_value = self._get_int_value(element, 'ar:MIN')
            param.max_value = self._get_int_value(element, 'ar:MAX')
        
        elif param_type == 'ECUC-FLOAT-PARAM-DEF':
            param.value_type = "FLOAT"
            param.min_value = self._get_float_value(element, 'ar:MIN')
            param.max_value = self._get_float_value(element, 'ar:MAX')
        
        elif param_type == 'ECUC-BOOLEAN-PARAM-DEF':
            param.value_type = "BOOLEAN"
        
        elif param_type == 'ECUC-STRING-PARAM-DEF':
            param.value_type = "STRING"
        
        # Parse DEFAULT-VALUE
        default_val =self._get_text_value(element, 'ar:DEFAULT-VALUE')
        if default_val:
            param.value = default_val
        
        # Parse SCOPE
        scope = self._get_text_value(element, 'ar:SCOPE')
        if scope:
            param.scope = scope
        
        # Parse ORIGIN
        origin = self._get_text_value(element, 'ar:ORIGIN')
        if origin:
            param.origin = origin
        
        return param
    
    def _parse_ecuc_reference_def(self, element: etree._Element) -> Optional[EcucReference]:
        """Parse ECUC-REFERENCE-DEF element
        
        Args:
            element: ECUC-REFERENCE-DEF XML element
            
        Returns:
            EcucReference object
        """
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        ref = EcucReference(short_name=short_name)
        
        # Parse description
        ref.description = self._get_description(element)
        
        # Parse DESTINATION-REF
        dest_ref_elem = element.find('.//ar:DESTINATION-REF', self.NAMESPACES)
        if dest_ref_elem is not None:
            ref.destination_ref = dest_ref_elem.text or ""
            ref.destination_type = dest_ref_elem.get('DEST', 'ECUC-PARAM-CONF-CONTAINER-DEF')
        
        # Parse multiplicity
        ref.lower_multiplicity = self._get_int_value(element, 'ar:LOWER-MULTIPLICITY', 0)
        ref.upper_multiplicity = self._get_int_value(element, 'ar:UPPER-MULTIPLICITY', 1)
        
        return ref
    
    # Helper methods
    
    def _get_short_name(self, element: etree._Element) -> Optional[str]:
        """Extract SHORT-NAME from element"""
        short_name_elem = element.find('ar:SHORT-NAME', self.NAMESPACES)
        if short_name_elem is None:
            short_name_elem = element.find('SHORT-NAME')
        return short_name_elem.text if short_name_elem is not None else None
    
    def _get_description(self, element: etree._Element) -> str:
        """Extract DESC/L-2 from element"""
        desc_elem = element.find('.//ar:DESC/ar:L-2', self.NAMESPACES)
        if desc_elem is None:
            desc_elem = element.find('.//ar:DESC', self.NAMESPACES)
        if desc_elem is None:
            desc_elem = element.find('.//DESC')
        return desc_elem.text if desc_elem is not None and desc_elem.text else ""
    
    def _get_text_value(self, element: etree._Element, xpath: str) -> Optional[str]:
        """Get text value from XPath"""
        elem = element.find(xpath, self.NAMESPACES)
        return elem.text if elem is not None else None
    
    def _get_int_value(self, element: etree._Element, xpath: str, default: int = 0) -> int:
        """Get integer value from XPath"""
        text = self._get_text_value(element, xpath)
        try:
            return int(text) if text else default
        except ValueError:
            return default
    
    def _get_float_value(self, element: etree._Element, xpath: str, default: float = 0.0) -> float:
        """Get float value from XPath"""
        text = self._get_text_value(element, xpath)
        try:
            return float(text) if text else default
        except ValueError:
            return default
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
        def_ref_elem = element.find('.//ar:DEFINITION-REF', self.NAMESPACES)
        if def_ref_elem is None:
            def_ref_elem = element.find('DEFINITION-REF')
            
        definition_ref = def_ref_elem.text if def_ref_elem is not None else ""
        
        config = EcucModuleConfiguration(
            short_name=short_name,
            definition_ref=definition_ref
        )
        
        # Parse containers
        containers_elem = element.find('.//ar:CONTAINERS', self.NAMESPACES)
        if containers_elem is not None:
            for container_elem in containers_elem.findall('ar:ECUC-CONTAINER-VALUE', self.NAMESPACES):
                container = self._parse_ecuc_container_value(container_elem)
                if container:
                    config.add_container(container)
                    
        return config

    def _parse_ecuc_container_value(self, element: etree._Element) -> Optional[EcucContainerValue]:
        """Parse ECUC-CONTAINER-VALUE element"""
        short_name = self._get_short_name(element)
        if not short_name:
            return None
            
        # Get definition reference
        def_ref_elem = element.find('.//ar:DEFINITION-REF', self.NAMESPACES)
        if def_ref_elem is None:
            def_ref_elem = element.find('DEFINITION-REF')
            
        definition_ref = def_ref_elem.text if def_ref_elem is not None else ""
        
        container = EcucContainerValue(
            short_name=short_name,
            definition_ref=definition_ref
        )
        
        # Parse parameters
        param_values_elem = element.find('.//ar:PARAMETER-VALUES', self.NAMESPACES)
        if param_values_elem is not None:
            # Parse numerical values
            for param_elem in param_values_elem.findall('ar:ECUC-NUMERICAL-PARAM-VALUE', self.NAMESPACES):
                self._parse_ecuc_parameter_value(param_elem, container)
                
            # Parse textual values
            for param_elem in param_values_elem.findall('ar:ECUC-TEXTUAL-PARAM-VALUE', self.NAMESPACES):
                self._parse_ecuc_parameter_value(param_elem, container)
                
        # Parse references
        ref_values_elem = element.find('.//ar:REFERENCE-VALUES', self.NAMESPACES)
        if ref_values_elem is not None:
            for ref_elem in ref_values_elem.findall('ar:ECUC-REFERENCE-VALUE', self.NAMESPACES):
                self._parse_ecuc_reference_value(ref_elem, container)
                
        # Parse sub-containers
        sub_containers_elem = element.find('.//ar:SUB-CONTAINERS', self.NAMESPACES)
        if sub_containers_elem is not None:
            for sub_elem in sub_containers_elem.findall('ar:ECUC-CONTAINER-VALUE', self.NAMESPACES):
                sub_container = self._parse_ecuc_container_value(sub_elem)
                if sub_container:
                    container.add_sub_container(sub_container)
                    
        return container

    def _parse_ecuc_parameter_value(self, element: etree._Element, container: EcucContainerValue):
        """Parse parameter value and add to container"""
        # Get definition reference
        def_ref_elem = element.find('.//ar:DEFINITION-REF', self.NAMESPACES)
        if def_ref_elem is None:
            def_ref_elem = element.find('DEFINITION-REF')
            
        if def_ref_elem is None or not def_ref_elem.text:
            return
            
        definition_ref = def_ref_elem.text
        param_name = definition_ref.split('/')[-1]
        
        # Get value
        value_elem = element.find('.//ar:VALUE', self.NAMESPACES)
        if value_elem is None:
            value_elem = element.find('VALUE')
            
        value = value_elem.text if value_elem is not None else None
        
        # Determine if it's numerical (try to convert)
        if element.tag.endswith('ECUC-NUMERICAL-PARAM-VALUE'):
            # Try int, then float, then bool
            try:
                # Check for boolean keywords first
                if value in ('true', '1'):
                    value = True
                elif value in ('false', '0'):
                    value = False
                elif '.' in value:
                    value = float(value)
                else:
                    value = int(value)
            except (ValueError, TypeError):
                pass
                
        container.set_parameter_value(param_name, value, definition_ref)

    def _parse_ecuc_reference_value(self, element: etree._Element, container: EcucContainerValue):
        """Parse reference value and add to container"""
        # Get definition reference
        def_ref_elem = element.find('.//ar:DEFINITION-REF', self.NAMESPACES)
        if def_ref_elem is None:
            def_ref_elem = element.find('DEFINITION-REF')
            
        if def_ref_elem is None or not def_ref_elem.text:
            return
            
        definition_ref = def_ref_elem.text
        ref_name = definition_ref.split('/')[-1]
        
        # Get target reference
        val_ref_elem = element.find('.//ar:VALUE-REF', self.NAMESPACES)
        if val_ref_elem is None:
            val_ref_elem = element.find('VALUE-REF')
            
        target_ref = val_ref_elem.text if val_ref_elem is not None else ""
        
        container.set_reference_value(ref_name, target_ref, definition_ref)

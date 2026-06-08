"""
ARXML Serializer for AUTOSAR configuration files
"""
from lxml import etree
from typing import Optional
from pathlib import Path
from ..model.container import Container, Parameter


class ArxmlSerializer:
    """Serializer for AUTOSAR ARXML files"""

    # AUTOSAR namespace
    AUTOSAR_NS = "http://autosar.org/schema/r4.0"
    XSI_NS = "http://www.w3.org/2001/XMLSchema-instance"

    def __init__(self, use_namespaces: bool = True, pretty_print: bool = True):
        """Initialize serializer

        Args:
            use_namespaces: Whether to use XML namespaces
            pretty_print: Whether to format output with indentation
        """
        self.use_namespaces = use_namespaces
        self.pretty_print = pretty_print

        if use_namespaces:
            self.nsmap = {
                None: self.AUTOSAR_NS,
                'xsi': self.XSI_NS
            }
        else:
            self.nsmap = None

    def serialize_to_file(self, container: Container, file_path: Path, encoding: str = 'utf-8'):
        """Serialize container to ARXML file

        Args:
            container: Container to serialize
            file_path: Output file path
            encoding: File encoding (default: utf-8)
        """
        root = self._create_arxml_root(container)

        tree = etree.ElementTree(root)
        tree.write(
            str(file_path),
            encoding=encoding,
            xml_declaration=True,
            pretty_print=self.pretty_print
        )

    def serialize_to_string(self, container: Container, encoding: str = 'utf-8') -> str:
        """Serialize container to XML string

        Args:
            container: Container to serialize
            encoding: String encoding (default: utf-8)

        Returns:
            XML string
        """
        root = self._create_arxml_root(container)

        return etree.tostring(
            root,
            encoding=encoding,
            xml_declaration=True,
            pretty_print=self.pretty_print
        ).decode(encoding)

    def _create_arxml_root(self, container: Container) -> etree._Element:
        """Create AUTOSAR XML root element

        Args:
            container: Container to serialize

        Returns:
            XML root element
        """
        # Create AUTOSAR root
        root = etree.Element(
            'AUTOSAR',
            nsmap=self.nsmap
        )

        # Add schema location if using namespaces
        if self.use_namespaces:
            root.set(
                f'{{{self.XSI_NS}}}schemaLocation',
                f'{self.AUTOSAR_NS} AUTOSAR_4-4-0.xsd'
            )

        # Create AR-PACKAGES structure
        ar_packages = etree.SubElement(root, 'AR-PACKAGES')
        ar_package = etree.SubElement(ar_packages, 'AR-PACKAGE')

        # Add package short-name
        short_name = etree.SubElement(ar_package, 'SHORT-NAME')
        short_name.text = 'Configuration'

        # Add elements
        elements = etree.SubElement(ar_package, 'ELEMENTS')

        # Serialize container
        container_elem = self._serialize_container(container)
        elements.append(container_elem)

        return root

    def _serialize_container(self, container: Container) -> etree._Element:
        """Serialize Container to XML element

        Args:
            container: Container to serialize

        Returns:
            XML element
        """
        elem = etree.Element('CONTAINER')

        # Add short-name
        short_name = etree.SubElement(elem, 'SHORT-NAME')
        short_name.text = container.short_name

        # Add description if present
        if container.description:
            desc = etree.SubElement(elem, 'DESC')
            desc.text = container.description

        # Add UUID if present
        if container.uuid:
            uuid_elem = etree.SubElement(elem, 'UUID')
            uuid_elem.text = container.uuid

        # Serialize parameters
        if container.parameters:
            params_elem = etree.SubElement(elem, 'PARAMETERS')
            for param in container.parameters.values():
                param_elem = self._serialize_parameter(param)
                params_elem.append(param_elem)

        # Serialize sub-containers
        if container.sub_containers:
            sub_containers_elem = etree.SubElement(elem, 'SUB-CONTAINERS')
            for sub_container in container.sub_containers.values():
                sub_elem = self._serialize_container(sub_container)
                sub_containers_elem.append(sub_elem)

        # Serialize references
        if container.references:
            refs_elem = etree.SubElement(elem, 'REFERENCES')
            for ref_name, ref_value in container.references.items():
                ref_elem = etree.SubElement(refs_elem, ref_name)
                ref_elem.text = ref_value

        # Add multiplicity if not default
        if container.min_multiplicity != 0 or container.max_multiplicity != 1:
            mult_elem = etree.SubElement(elem, 'MULTIPLICITY')

            min_mult = etree.SubElement(mult_elem, 'MIN')
            min_mult.text = str(container.min_multiplicity)

            max_mult = etree.SubElement(mult_elem, 'MAX')
            if container.max_multiplicity == -1:
                max_mult.text = 'UNBOUNDED'
            else:
                max_mult.text = str(container.max_multiplicity)

        return elem

    def _serialize_parameter(self, param: Parameter) -> etree._Element:
        """Serialize Parameter to XML element

        Args:
            param: Parameter to serialize

        Returns:
            XML element
        """
        elem = etree.Element('PARAMETER')

        # Add short-name
        short_name = etree.SubElement(elem, 'SHORT-NAME')
        short_name.text = param.short_name

        # Add description if present
        if param.description:
            desc = etree.SubElement(elem, 'DESC')
            desc.text = param.description

        # Add value
        if param.value is not None:
            if param.value_type == "ARRAY" and isinstance(param.value, list):
                array_elem = etree.SubElement(elem, 'ARRAY-VALUES')
                for item in param.value:
                    val_elem = etree.SubElement(array_elem, 'VALUE')
                    val_elem.text = str(item)
            elif param.value_type == "STRUCT" and isinstance(param.value, dict):
                struct_elem = etree.SubElement(elem, 'STRUCT-VALUES')
                for key, val in param.value.items():
                    field_elem = etree.SubElement(struct_elem, 'STRUCT-VALUE')
                    name_elem = etree.SubElement(field_elem, 'NAME')
                    name_elem.text = key
                    val_elem = etree.SubElement(field_elem, 'VALUE')
                    val_elem.text = str(val)
            else:
                value_elem = etree.SubElement(elem, 'VALUE')
                value_elem.text = str(param.value)

        # Add type
        type_elem = etree.SubElement(elem, 'TYPE')
        type_elem.text = param.value_type
        
        # Add content type for arrays
        if param.value_type == "ARRAY" and param.content_type:
            content_type_elem = etree.SubElement(elem, 'CONTENT-TYPE')
            content_type_elem.text = param.content_type

        # Add min/max values
        if param.min_value is not None:
            min_elem = etree.SubElement(elem, 'MIN-VALUE')
            min_elem.text = str(param.min_value)

        if param.max_value is not None:
            max_elem = etree.SubElement(elem, 'MAX-VALUE')
            max_elem.text = str(param.max_value)

        # Add enum values
        if param.enum_values:
            enum_elem = etree.SubElement(elem, 'ENUM-VALUES')
            for enum_val in param.enum_values:
                val_elem = etree.SubElement(enum_elem, 'ENUM-VALUE')
                val_elem.text = enum_val

        # Add unit
        if param.unit:
            unit_elem = etree.SubElement(elem, 'UNIT')
            unit_elem.text = param.unit

        # Add UUID
        if param.uuid:
            uuid_elem = etree.SubElement(elem, 'UUID')
            uuid_elem.text = param.uuid

        return elem

    def validate_output(self, container: Container, schema_path: Optional[Path] = None) -> bool:
        """Validate serialized output against schema

        Args:
            container: Container to validate
            schema_path: Path to XSD schema

        Returns:
            True if valid, False otherwise
        """
        if not schema_path or not schema_path.exists():
            return True

        try:
            # Load schema with a safe parser to prevent XXE via a malicious XSD
            _safe = etree.XMLParser(resolve_entities=False, no_network=True)
            schema_doc = etree.parse(str(schema_path), _safe)
            schema = etree.XMLSchema(schema_doc)

            # Serialize container
            root = self._create_arxml_root(container)

            # Validate
            return schema.validate(root)

        except Exception:
            return False

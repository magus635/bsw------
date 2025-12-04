"""
ECUC Value Serializer
Serializes EcucModuleConfiguration to ARXML format
"""
from lxml import etree
from typing import Optional
from pathlib import Path
from ..model.configuration_model import (
    EcucModuleConfiguration, 
    EcucContainerValue, 
    EcucParameterValue,
    EcucReferenceValue
)
from ..model.definition_model import EcucParameterType

class EcucValueSerializer:
    """Serializer for ECUC configuration values (VALUE file)"""

    # AUTOSAR namespaces
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

    def serialize_to_file(self, configuration: EcucModuleConfiguration, file_path: Path, encoding: str = 'utf-8'):
        """Serialize configuration to ARXML file
        
        Args:
            configuration: Configuration to serialize
            file_path: Output file path
            encoding: File encoding
        """
        root = self._create_arxml_root(configuration)
        
        tree = etree.ElementTree(root)
        tree.write(
            str(file_path),
            encoding=encoding,
            xml_declaration=True,
            pretty_print=self.pretty_print
        )

    def _create_arxml_root(self, configuration: EcucModuleConfiguration) -> etree._Element:
        """Create AUTOSAR XML root element"""
        # Create AUTOSAR root
        root = etree.Element('AUTOSAR', nsmap=self.nsmap)
        
        if self.use_namespaces:
            root.set(
                f'{{{self.XSI_NS}}}schemaLocation',
                f'{self.AUTOSAR_NS} AUTOSAR_4-4-0.xsd'
            )
            
        # Create AR-PACKAGES structure
        ar_packages = etree.SubElement(root, 'AR-PACKAGES')
        
        # Create package for configuration
        # Usually configuration is stored in a separate package
        ar_package = etree.SubElement(ar_packages, 'AR-PACKAGE')
        
        # Package name (derived from module name + _Config)
        short_name = etree.SubElement(ar_package, 'SHORT-NAME')
        short_name.text = f"{configuration.short_name}_Config"
        
        # Elements
        elements = etree.SubElement(ar_package, 'ELEMENTS')
        
        # Create ECUC-MODULE-CONFIGURATION-VALUES
        module_config = etree.SubElement(elements, 'ECUC-MODULE-CONFIGURATION-VALUES')
        
        # Module config short name
        mod_short_name = etree.SubElement(module_config, 'SHORT-NAME')
        mod_short_name.text = configuration.short_name
        
        # Definition reference
        def_ref = etree.SubElement(module_config, 'DEFINITION-REF', DEST='ECUC-MODULE-DEF')
        def_ref.text = configuration.definition_ref
        
        # Implementation config variant
        variant = etree.SubElement(module_config, 'IMPLEMENTATION-CONFIG-VARIANT')
        variant.text = 'VARIANT-PRE-COMPILE'
        
        # Containers
        containers_elem = etree.SubElement(module_config, 'CONTAINERS')
        
        # Serialize top-level containers
        # Note: configuration.containers only has top-level containers
        for container in configuration.containers:
            self._serialize_container(container, containers_elem)
            
        return root

    def _serialize_container(self, container: EcucContainerValue, parent_elem: etree._Element):
        """Serialize container value"""
        container_elem = etree.SubElement(parent_elem, 'ECUC-CONTAINER-VALUE')
        
        # Short name
        short_name = etree.SubElement(container_elem, 'SHORT-NAME')
        short_name.text = container.short_name
        
        # Definition reference
        def_ref = etree.SubElement(container_elem, 'DEFINITION-REF', DEST='ECUC-PARAM-CONF-CONTAINER-DEF')
        def_ref.text = container.definition_ref
        
        # Parameters - create wrapper once
        if container.parameter_values:
            param_values_elem = etree.SubElement(container_elem, 'PARAMETER-VALUES')
            for param in container.parameter_values.values():
                self._serialize_parameter(param, param_values_elem)
                
        # References - create wrapper once
        if container.reference_values:
            ref_values_elem = etree.SubElement(container_elem, 'REFERENCE-VALUES')
            for ref in container.reference_values.values():
                self._serialize_reference(ref, ref_values_elem)
                
        # Sub-containers
        if container.sub_containers:
            sub_containers_elem = etree.SubElement(container_elem, 'SUB-CONTAINERS')
            for sub_container in container.sub_containers:
                self._serialize_container(sub_container, sub_containers_elem)

    def _serialize_parameter(self, param: EcucParameterValue, param_values_elem: etree._Element):
        """Serialize parameter value
        
        Args:
            param: Parameter value to serialize
            param_values_elem: The PARAMETER-VALUES wrapper element to add to
        """
        # Determine specific element type
        is_numerical = isinstance(param.value, (int, float, bool))
        tag_name = 'ECUC-NUMERICAL-PARAM-VALUE' if is_numerical else 'ECUC-TEXTUAL-PARAM-VALUE'
        
        param_elem = etree.SubElement(param_values_elem, tag_name)
        
        # Definition reference
        def_ref = etree.SubElement(param_elem, 'DEFINITION-REF', DEST='ECUC-PARAMETER-DEF')
        def_ref.text = param.definition_ref
        
        # Value
        value_elem = etree.SubElement(param_elem, 'VALUE')
        
        if isinstance(param.value, bool):
            value_elem.text = 'true' if param.value else 'false'
        else:
            value_elem.text = str(param.value)

    def _serialize_reference(self, ref: EcucReferenceValue, ref_values_elem: etree._Element):
        """Serialize reference value
        
        Args:
            ref: Reference value to serialize  
            ref_values_elem: The REFERENCE-VALUES wrapper element to add to
        """
        ref_elem = etree.SubElement(ref_values_elem, 'ECUC-REFERENCE-VALUE')
        
        # Definition reference
        def_ref = etree.SubElement(ref_elem, 'DEFINITION-REF', DEST='ECUC-REFERENCE-DEF')
        def_ref.text = ref.definition_ref
        
        # Value (Target reference)
        value_elem = etree.SubElement(ref_elem, 'VALUE-REF', DEST='ECUC-CONTAINER-VALUE')
        value_elem.text = ref.value_ref

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

    def export_epc(self, configuration: EcucModuleConfiguration, file_path: Path, encoding: str = 'utf-8'):
        """Export configuration as an EB Tresos-compatible .epc value file.

        Matches the layout EB Tresos itself produces: the AR-PACKAGE short-name
        is the module name (not '{Module}_Config') and the schemaLocation is
        AUTOSAR_00046.xsd. Element structure and ordering are identical to
        serialize_to_file (deterministic: same configuration → same bytes).
        """
        root = self._create_arxml_root(
            configuration,
            package_name=configuration.short_name,
            schema_file='AUTOSAR_00046.xsd',
        )
        tree = etree.ElementTree(root)
        tree.write(
            str(file_path),
            encoding=encoding,
            xml_declaration=True,
            pretty_print=self.pretty_print
        )

    def _create_arxml_root(self, configuration: EcucModuleConfiguration,
                           package_name: Optional[str] = None,
                           schema_file: str = 'AUTOSAR_4-4-0.xsd') -> etree._Element:
        """Create AUTOSAR XML root element"""
        # Create AUTOSAR root
        root = etree.Element('AUTOSAR', nsmap=self.nsmap)

        if self.use_namespaces:
            root.set(
                f'{{{self.XSI_NS}}}schemaLocation',
                f'{self.AUTOSAR_NS} {schema_file}'
            )

        # Create AR-PACKAGES structure
        ar_packages = etree.SubElement(root, 'AR-PACKAGES')

        # Create package for configuration
        # Usually configuration is stored in a separate package
        ar_package = etree.SubElement(ar_packages, 'AR-PACKAGE')

        # Package name (explicit override, preserved original, or derived from module name)
        short_name = etree.SubElement(ar_package, 'SHORT-NAME')
        short_name.text = package_name or configuration.package_name or f"{configuration.short_name}_Config"
        
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
        variant.text = configuration.implementation_config_variant
        
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

        # UUID attribute (preserve from original if present)
        if container.uuid:
            container_elem.set('UUID', container.uuid)
        
        # Short name
        short_name = etree.SubElement(container_elem, 'SHORT-NAME')
        short_name.text = container.short_name
        
        # Definition reference
        container_dest = getattr(container, 'def_dest_type', None) or 'ECUC-PARAM-CONF-CONTAINER-DEF'
        def_ref = etree.SubElement(container_elem, 'DEFINITION-REF', DEST=container_dest)
        def_ref.text = container.definition_ref
        
        # INDEX - only serialize if explicitly set (from original EB file)
        if getattr(container, '_has_explicit_index', False) and container.index is not None:
            index_elem = etree.SubElement(container_elem, 'INDEX')
            index_elem.text = str(container.index)
        
        # Parameters - create wrapper once
        param_values_elem = None
        if container.parameter_values:
            param_values_elem = etree.SubElement(container_elem, 'PARAMETER-VALUES')
            for param in container.parameter_values.values():
                self._serialize_parameter(param, param_values_elem)

        # Multi-valued parameters (with INDEX)
        multi_params = getattr(container, 'multi_parameter_values', None)
        if multi_params:
            if param_values_elem is None:
                param_values_elem = etree.SubElement(container_elem, 'PARAMETER-VALUES')
            for param_name, param_list in multi_params.items():
                for param_val in sorted(param_list, key=lambda p: p.index if p.index is not None else 0):
                    is_numerical = isinstance(param_val.value, (int, float, bool))
                    tag_name = 'ECUC-NUMERICAL-PARAM-VALUE' if is_numerical else 'ECUC-TEXTUAL-PARAM-VALUE'
                    param_elem = etree.SubElement(param_values_elem, tag_name)
                    if param_val.index is not None:
                        index_elem = etree.SubElement(param_elem, 'INDEX')
                        index_elem.text = str(param_val.index)
                    multi_param_dest = getattr(param_val, 'dest_type', None) or 'ECUC-PARAMETER-DEF'
                    def_ref = etree.SubElement(param_elem, 'DEFINITION-REF', DEST=multi_param_dest)
                    def_ref.text = param_val.definition_ref
                    value_elem = etree.SubElement(param_elem, 'VALUE')
                    if isinstance(param_val.value, bool):
                        value_elem.text = 'true' if param_val.value else 'false'
                    else:
                        value_elem.text = str(param_val.value)
                
        # NOTE: unknown parameters (imported values not in the definition)
        # remain inside parameter_values / multi_parameter_values and are
        # therefore written out by the loops above — container.unknown_parameters
        # is only an index of flagged names, never a separate value store.

        # References - create wrapper once
        ref_values_elem = None
        if container.reference_values:
            ref_values_elem = etree.SubElement(container_elem, 'REFERENCE-VALUES')
            for ref in container.reference_values.values():
                self._serialize_reference(ref, ref_values_elem)

        # Multi-valued references (with INDEX)
        multi_refs = getattr(container, 'multi_reference_values', None)
        if multi_refs:
            if ref_values_elem is None:
                ref_values_elem = etree.SubElement(container_elem, 'REFERENCE-VALUES')
            for ref_name, ref_list in multi_refs.items():
                for ref_val in sorted(ref_list, key=lambda r: r.index if r.index is not None else 0):
                    ref_elem = etree.SubElement(ref_values_elem, 'ECUC-REFERENCE-VALUE')
                    if ref_val.index is not None:
                        index_elem = etree.SubElement(ref_elem, 'INDEX')
                        index_elem.text = str(ref_val.index)
                    multi_ref_dest = getattr(ref_val, 'dest_type', None) or 'ECUC-REFERENCE-DEF'
                    def_ref = etree.SubElement(ref_elem, 'DEFINITION-REF', DEST=multi_ref_dest)
                    def_ref.text = ref_val.definition_ref
                    value_elem = etree.SubElement(ref_elem, 'VALUE-REF', DEST='ECUC-CONTAINER-VALUE')
                    value_elem.text = ref_val.value_ref

        # Sub-containers
        if container.sub_containers:
            sub_containers_elem = etree.SubElement(container_elem, 'SUB-CONTAINERS')
            for sub_container in container.sub_containers:
                self._serialize_container(sub_container, sub_containers_elem)

    def _serialize_parameter(self, param: EcucParameterValue, param_values_elem: etree._Element,
                             include_index: bool = False):
        """Serialize parameter value

        Args:
            param: Parameter value to serialize
            param_values_elem: The PARAMETER-VALUES wrapper element to add to
            include_index: Write the INDEX element when param.index is set
        """
        # Determine specific element type
        is_numerical = isinstance(param.value, (int, float, bool))
        tag_name = 'ECUC-NUMERICAL-PARAM-VALUE' if is_numerical else 'ECUC-TEXTUAL-PARAM-VALUE'

        param_elem = etree.SubElement(param_values_elem, tag_name)

        if include_index and param.index is not None:
            index_elem = etree.SubElement(param_elem, 'INDEX')
            index_elem.text = str(param.index)

        # Definition reference
        param_dest = getattr(param, 'dest_type', None) or 'ECUC-PARAMETER-DEF'
        def_ref = etree.SubElement(param_elem, 'DEFINITION-REF', DEST=param_dest)
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
        ref_dest = getattr(ref, 'dest_type', None) or 'ECUC-REFERENCE-DEF'
        def_ref = etree.SubElement(ref_elem, 'DEFINITION-REF', DEST=ref_dest)
        def_ref.text = ref.definition_ref

        # Value (Target reference)
        value_elem = etree.SubElement(ref_elem, 'VALUE-REF', DEST='ECUC-CONTAINER-VALUE')
        value_elem.text = ref.value_ref

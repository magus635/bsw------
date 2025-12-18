"""
ECUC Definition Parser - Specialized parser for ECUC-DEF ARXML files
Parses module/container/parameter definitions (the "blueprint")
"""
from lxml import etree
from typing import Optional, List, Any
from pathlib import Path

from ..model.definition_model import (
    EcucModuleDef,
    EcucContainerDef,
    EcucParameterDef,
    EcucReferenceDef,
    EcucParameterType,
    VariantType
)


class EcucDefParser:
    """Parser for ECUC Definition (ECUC-DEF) ARXML files"""
    
    # AUTOSAR XML namespaces
    NAMESPACES = {
        'ar': 'http://autosar.org/schema/r4.0',
        'xsi': 'http://www.w3.org/2001/XMLSchema-instance'
    }
    
    def __init__(self):
        """Initialize parser"""
        pass
    
    def parse_module_def_file(self, file_path: Path) -> Optional[EcucModuleDef]:
        """Parse ECUC-MODULE-DEF from ARXML file
        
        Args:
            file_path: Path to ECUC-DEF ARXML file
            
        Returns:
            EcucModuleDef object or None if not found
        """
        if not file_path.exists():
            raise FileNotFoundError(f"File not found: {file_path}")
        
        try:
            tree = etree.parse(str(file_path))
            root = tree.getroot()
            
            # Find ECUC-MODULE-DEF element using permissive search
            module_def_elem = self._find_descendant(root, 'ECUC-MODULE-DEF')
            
            if module_def_elem is None:
                # Check if it's a configuration file to give a better error message
                config_elem = self._find_descendant(root, 'ECUC-MODULE-CONFIGURATION-VALUES')
                if config_elem is not None:
                    raise ValueError(
                        f"File contains configuration values (ECUC-MODULE-CONFIGURATION-VALUES), "
                        f"but a module definition (ECUC-MODULE-DEF) was expected. "
                        f"Please select the correct BSW Module Definition file (checking {file_path})."
                    )
                
                raise ValueError(f"No ECUC-MODULE-DEF found in {file_path}")
            
            return self.parse_module_def(module_def_elem)
            
        except etree.XMLSyntaxError as e:
            raise ValueError(f"XML parsing error in {file_path}: {e}")
    
    def parse_module_def(self, element: etree._Element) -> EcucModuleDef:
        """Parse ECUC-MODULE-DEF element
        
        Args:
            element: ECUC-MODULE-DEF XML element
            
        Returns:
            EcucModuleDef object
        """
        short_name = self._get_short_name(element)
        if not short_name:
            raise ValueError("ECUC-MODULE-DEF must have a SHORT-NAME")
        
        module_def = EcucModuleDef(
            short_name=short_name,
            description=self._get_description(element)
        )
        
        # Parse CONTAINERS
        containers_elem = self._find_descendant(element, 'CONTAINERS')
        if containers_elem is not None:
            # Find all container defs
            for container_elem in self._findall_descendants(containers_elem, 'ECUC-PARAM-CONF-CONTAINER-DEF'):
                container_def = self._parse_container_def(container_elem)
                if container_def:
                    # Set full definition reference path
                    container_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_def.short_name}/{container_def.short_name}"
                    module_def.add_container(container_def)
        
        # Set module definition reference
        module_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_def.short_name}"
        
        return module_def
    
    def _parse_container_def(self, element: etree._Element, parent_path: str = "") -> Optional[EcucContainerDef]:
        """Parse ECUC-PARAM-CONF-CONTAINER-DEF element (recursive)"""
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        container_def = EcucContainerDef(
            short_name=short_name,
            description=self._get_description(element)
        )
        
        # Parse multiplicity
        container_def.lower_multiplicity = self._get_int_value(element, 'LOWER-MULTIPLICITY', 0)
        upper_mult_text = self._get_text_value(element, 'UPPER-MULTIPLICITY')
        if upper_mult_text == '*':
            container_def.upper_multiplicity = -1
        else:
            container_def.upper_multiplicity = int(upper_mult_text) if upper_mult_text else 1
            
        # Parse Post-Build Variant Multiplicity
        pb_mult = self._get_text_value(element, 'POST-BUILD-VARIANT-MULTIPLICITY')
        if pb_mult:
            container_def.post_build_variant_multiplicity = (pb_mult.lower() == 'true')
        
        # Build full path
        current_path = f"{parent_path}/{short_name}" if parent_path else short_name
        container_def.definition_ref = current_path
        
        # Parse PARAMETERS
        params_elem = self._find_descendant(element, 'PARAMETERS')
        if params_elem is not None:
            # Iterate over children directly to catch different parameter types
            for param_elem in params_elem:
                if 'PARAM-DEF' in param_elem.tag:
                    param_def = self._parse_parameter_def(param_elem, current_path)
                    if param_def:
                        container_def.add_parameter(param_def)
        
        # Parse REFERENCES
        refs_elem = self._find_descendant(element, 'REFERENCES')
        if refs_elem is not None:
            for ref_elem in self._findall_descendants(refs_elem, 'ECUC-REFERENCE-DEF'):
                ref_def = self._parse_reference_def(ref_elem, current_path)
                if ref_def:
                    container_def.add_reference(ref_def)
        
        # Parse SUB-CONTAINERS (recursive)
        sub_conts_elem = self._find_descendant(element, 'SUB-CONTAINERS')
        if sub_conts_elem is not None:
            for sub_cont_elem in self._findall_descendants(sub_conts_elem, 'ECUC-PARAM-CONF-CONTAINER-DEF'):
                sub_container_def = self._parse_container_def(sub_cont_elem, current_path)
                if sub_container_def:
                    container_def.add_sub_container(sub_container_def)
        
        return container_def
    
    def _parse_parameter_def(self, element: etree._Element, parent_path:str = "") -> Optional[EcucParameterDef]:
        """Parse parameter definition element"""
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        # Determine parameter type from element tag
        # Use local-name to be namespace agnostic
        tag_name = etree.QName(element).localname
        
        try:
            param_type = EcucParameterType(tag_name)
        except ValueError:
            # Unknown type, skip
            return None
        
        param_def = EcucParameterDef(
            short_name=short_name,
            param_type=param_type,
            description=self._get_description(element)
        )
        
        # Parse multiplicity
        param_def.lower_multiplicity = self._get_int_value(element, 'LOWER-MULTIPLICITY', 0)
        param_def.upper_multiplicity = self._get_int_value(element, 'UPPER-MULTIPLICITY', 1)
        
        # Parse DEFAULT-VALUE
        default_val = self._get_text_value(element, 'DEFAULT-VALUE')
        if default_val:
            param_def.default_value = self._convert_value(default_val, param_type)
        
        # Parse type-specific fields
        if param_type == EcucParameterType.ENUMERATION:
            param_def.literals = self._parse_literals(element)
        
        elif param_type == EcucParameterType.INTEGER:
            min_val = self._get_text_value(element, 'MIN')
            max_val = self._get_text_value(element, 'MAX')
            param_def.min_value = int(min_val) if min_val else None
            param_def.max_value = int(max_val) if max_val else None
        
        elif param_type == EcucParameterType.FLOAT:
            min_val = self._get_text_value(element, 'MIN')
            max_val = self._get_text_value(element, 'MAX')
            param_def.min_value = float(min_val) if min_val else None
            param_def.max_value = float(max_val) if max_val else None
        
        # Parse metadata
        scope = self._get_text_value(element, 'SCOPE')
        if scope:
            param_def.scope = scope
        
        origin = self._get_text_value(element, 'ORIGIN')
        if origin:
            param_def.origin = origin
            
        # --- NEW: Logic Loop Attributes (Pre/Link/Post) ---
        # Look for IMPLEMENTATION-CONFIG-CLASSES
        # Structure:
        # <ECUC-PARAM-CONF-CONTAINER-DEF ...>
        #   <PARAMETERS>
        #     <ECUC-INTEGER-PARAM-DEF ...>
        #       <IMPLEMENTATION-CONFIG-CLASSES>
        #         <ECUC-IMPLEMENTATION-CONFIGURATION-CLASS>
        #           <CONFIG-CLASS>PRE-COMPILE</CONFIG-CLASS>
        #           <CONFIG-VARIANT>VARIANT-PRE-COMPILE</CONFIG-VARIANT>
        #         </ECUC-IMPLEMENTATION-CONFIGURATION-CLASS>
        #       </IMPLEMENTATION-CONFIG-CLASSES>
        
        impl_configs = self._find_descendant(element, 'IMPLEMENTATION-CONFIG-CLASSES')
        if impl_configs is not None:
            # We take the first valid config class found, or specific logic if needed.
            # Usually there's one per variant, or one general.
            # Simplified: Find the first one.
            icc_elem = self._find_descendant(impl_configs, 'ECUC-IMPLEMENTATION-CONFIGURATION-CLASS')
            if icc_elem is not None:
                config_class = self._get_text_value(icc_elem, 'CONFIG-CLASS')
                config_variant = self._get_text_value(icc_elem, 'CONFIG-VARIANT')
                
                if config_class:
                    param_def.config_class = config_class
                if config_variant:
                    param_def.config_variant = config_variant
        
        # Set definition reference path
        param_def.definition_ref = f"{parent_path}/{short_name}"
        
        return param_def
    
    def _parse_reference_def(self, element: etree._Element, parent_path: str = "") -> Optional[EcucReferenceDef]:
        """Parse ECUC-REFERENCE-DEF element"""
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        ref_def = EcucReferenceDef(
            short_name=short_name,
            description=self._get_description(element)
        )
        
        # Parse DESTINATION-REF
        dest_ref_elem = self._find_descendant(element, 'DESTINATION-REF')
        if dest_ref_elem is not None:
            ref_def.destination_ref = dest_ref_elem.text or ""
            ref_def.destination_type = dest_ref_elem.get('DEST', 'ECUC-PARAM-CONF-CONTAINER-DEF')
        
        # Parse multiplicity
        ref_def.lower_multiplicity = self._get_int_value(element, 'LOWER-MULTIPLICITY', 0)
        ref_def.upper_multiplicity = self._get_int_value(element, 'UPPER-MULTIPLICITY', 1)
        
        # Set definition reference path
        ref_def.definition_ref = f"{parent_path}/{short_name}"
        
        return ref_def
    
    def _parse_literals(self, element: etree._Element) -> List[str]:
        """Parse enumeration literals"""
        literals = []
        literals_elem = self._find_descendant(element, 'LITERALS')
        if literals_elem is not None:
            for lit_def in self._findall_descendants(literals_elem, 'ECUC-ENUMERATION-LITERAL-DEF'):
                lit_name = self._get_short_name(lit_def)
                if lit_name:
                    literals.append(lit_name)
        return literals
    
    def _convert_value(self, text: str, param_type: EcucParameterType) -> any:
        """Convert text value to appropriate Python type"""
        if param_type == EcucParameterType.INTEGER:
            return int(text)
        elif param_type == EcucParameterType.FLOAT:
            return float(text)
        elif param_type == EcucParameterType.BOOLEAN:
            return text.lower() in ('true', '1', 'yes')
        else:
            return text
    
    # Helper methods for Permissive Parsing
    
    def _find_descendant(self, element: etree._Element, tag_name: str) -> Optional[etree._Element]:
        """Find first descendant with tag_name, ignoring namespace"""
        # 1. Try direct find with namespace (fastest)
        elem = element.find(f".//ar:{tag_name}", self.NAMESPACES)
        if elem is not None:
            return elem
            
        # 2. Try XPath with local-name (slower but namespace agnostic)
        # using XPath to find ANY descendant with local-name matching
        xpath = f".//*[local-name()='{tag_name}']"
        matches = element.xpath(xpath)
        if matches:
            return matches[0]
            
        return None
        
    def _findall_descendants(self, element: etree._Element, tag_name: str) -> List[etree._Element]:
        """Find all descendants with tag_name, ignoring namespace"""
        # 1. Try direct find with namespace
        elems = element.findall(f".//ar:{tag_name}", self.NAMESPACES)
        if elems:
            return elems
            
        # 2. XPath local-name
        xpath = f".//*[local-name()='{tag_name}']"
        return element.xpath(xpath)

    def _get_short_name(self, element: etree._Element) -> Optional[str]:
        """Extract SHORT-NAME from element (direct child)"""
        # SHORT-NAME is usually a direct child
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
        # We need to find the element first, then get its text.
        # _find_descendant looks for tag_name.
        elem = self._find_descendant(element, tag_name)
        return elem.text if elem is not None else None
    
    def _get_int_value(self, element: etree._Element, tag_name: str, default: int = 0) -> int:
        """Get integer value of a descendant"""
        text = self._get_text_value(element, tag_name)
        try:
            return int(text) if text else default
        except ValueError:
            return default

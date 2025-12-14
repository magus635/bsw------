"""
ECUC Definition Parser - Specialized parser for ECUC-DEF ARXML files
Parses module/container/parameter definitions (the "blueprint")
"""
from lxml import etree
from typing import Optional, List
from pathlib import Path

from ..model.definition_model import (
    EcucModuleDef,
    EcucContainerDef,
    EcucParameterDef,
    EcucReferenceDef,
    EcucParameterType
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
        
        tree = etree.parse(str(file_path))
        root = tree.getroot()
        
        # Find ECUC-MODULE-DEF element
        module_def_elem = root.find('.//ar:ECUC-MODULE-DEF', self.NAMESPACES)
        if module_def_elem is None:
            # Check if it's a configuration file to give a better error message
            config_elem = root.find('.//ar:ECUC-MODULE-CONFIGURATION-VALUES', self.NAMESPACES)
            if config_elem is not None:
                raise ValueError(
                    f"File contains configuration values (ECUC-MODULE-CONFIGURATION-VALUES), "
                    f"but a module definition (ECUC-MODULE-DEF) was expected. "
                    f"Please select the correct BSW Module Definition file (checking {file_path})."
                )
            
            raise ValueError(f"No ECUC-MODULE-DEF found in {file_path}")
        
        return self.parse_module_def(module_def_elem)
    
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
        containers_elem = element.find('.//ar:CONTAINERS', self.NAMESPACES)
        if containers_elem is not None:
            for container_elem in containers_elem.findall('ar:ECUC-PARAM-CONF-CONTAINER-DEF', self.NAMESPACES):
                container_def = self._parse_container_def(container_elem)
                if container_def:
                    # Set full definition reference path
                    container_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_def.short_name}/{container_def.short_name}"
                    module_def.add_container(container_def)
        
        # Set module definition reference
        module_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_def.short_name}"
        
        return module_def
    
    def _parse_container_def(self, element: etree._Element, parent_path: str = "") -> Optional[EcucContainerDef]:
        """Parse ECUC-PARAM-CONF-CONTAINER-DEF element (recursive)
        
        Args:
            element: ECUC-PARAM-CONF-CONTAINER-DEF XML element
            parent_path: Parent container path for building full reference
            
        Returns:
            EcucContainerDef object
        """
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        container_def = EcucContainerDef(
            short_name=short_name,
            description=self._get_description(element)
        )
        
        # Parse multiplicity
        container_def.lower_multiplicity = self._get_int_value(element, './/ar:LOWER-MULTIPLICITY', 0)
        upper_mult_text = self._get_text_value(element, './/ar:UPPER-MULTIPLICITY')
        if upper_mult_text == '*':
            container_def.upper_multiplicity = -1
        else:
            container_def.upper_multiplicity = int(upper_mult_text) if upper_mult_text else 1
        
        # Build full path
        current_path = f"{parent_path}/{short_name}" if parent_path else short_name
        container_def.definition_ref = current_path
        
        # Parse PARAMETERS
        params_elem = element.find('.//ar:PARAMETERS', self.NAMESPACES)
        if params_elem is not None:
            for param_elem in params_elem:
                param_def = self._parse_parameter_def(param_elem, current_path)
                if param_def:
                    container_def.add_parameter(param_def)
        
        # Parse REFERENCES
        refs_elem = element.find('.//ar:REFERENCES', self.NAMESPACES)
        if refs_elem is not None:
            for ref_elem in refs_elem.findall('ar:ECUC-REFERENCE-DEF', self.NAMESPACES):
                ref_def = self._parse_reference_def(ref_elem, current_path)
                if ref_def:
                    container_def.add_reference(ref_def)
        
        # Parse SUB-CONTAINERS (recursive)
        sub_conts_elem = element.find('.//ar:SUB-CONTAINERS', self.NAMESPACES)
        if sub_conts_elem is not None:
            for sub_cont_elem in sub_conts_elem.findall('ar:ECUC-PARAM-CONF-CONTAINER-DEF', self.NAMESPACES):
                sub_container_def = self._parse_container_def(sub_cont_elem, current_path)
                if sub_container_def:
                    container_def.add_sub_container(sub_container_def)
        
        return container_def
    
    def _parse_parameter_def(self, element: etree._Element, parent_path:str = "") -> Optional[EcucParameterDef]:
        """Parse parameter definition element
        
        Args:
            element: ECUC-*-PARAM-DEF XML element
            parent_path: Parent container path
            
        Returns:
            EcucParameterDef object
        """
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        # Determine parameter type from element tag
        tag_name = element.tag.split('}')[-1] if '}' in element.tag else element.tag
        
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
        param_def.lower_multiplicity = self._get_int_value(element, './/ar:LOWER-MULTIPLICITY', 0)
        param_def.upper_multiplicity = self._get_int_value(element, './/ar:UPPER-MULTIPLICITY', 1)
        
        # Parse DEFAULT-VALUE
        default_val = self._get_text_value(element, './/ar:DEFAULT-VALUE')
        if default_val:
            param_def.default_value = self._convert_value(default_val, param_type)
        
        # Parse type-specific fields
        if param_type == EcucParameterType.ENUMERATION:
            param_def.literals = self._parse_literals(element)
        
        elif param_type == EcucParameterType.INTEGER:
            min_val = self._get_text_value(element, './/ar:MIN')
            max_val = self._get_text_value(element, './/ar:MAX')
            param_def.min_value = int(min_val) if min_val else None
            param_def.max_value = int(max_val) if max_val else None
        
        elif param_type == EcucParameterType.FLOAT:
            min_val = self._get_text_value(element, './/ar:MIN')
            max_val = self._get_text_value(element, './/ar:MAX')
            param_def.min_value = float(min_val) if min_val else None
            param_def.max_value = float(max_val) if max_val else None
        
        # Parse metadata
        scope = self._get_text_value(element, './/ar:SCOPE')
        if scope:
            param_def.scope = scope
        
        origin = self._get_text_value(element, './/ar:ORIGIN')
        if origin:
            param_def.origin = origin
        
        # Set definition reference path
        param_def.definition_ref = f"{parent_path}/{short_name}"
        
        return param_def
    
    def _parse_reference_def(self, element: etree._Element, parent_path: str = "") -> Optional[EcucReferenceDef]:
        """Parse ECUC-REFERENCE-DEF element
        
        Args:
            element: ECUC-REFERENCE-DEF XML element
            parent_path: Parent container path
            
        Returns:
            EcucReferenceDef object
        """
        short_name = self._get_short_name(element)
        if not short_name:
            return None
        
        ref_def = EcucReferenceDef(
            short_name=short_name,
            description=self._get_description(element)
        )
        
        # Parse DESTINATION-REF
        dest_ref_elem = element.find('.//ar:DESTINATION-REF', self.NAMESPACES)
        if dest_ref_elem is not None:
            ref_def.destination_ref = dest_ref_elem.text or ""
            ref_def.destination_type = dest_ref_elem.get('DEST', 'ECUC-PARAM-CONF-CONTAINER-DEF')
        
        # Parse multiplicity
        ref_def.lower_multiplicity = self._get_int_value(element, './/ar:LOWER-MULTIPLICITY', 0)
        ref_def.upper_multiplicity = self._get_int_value(element, './/ar:UPPER-MULTIPLICITY', 1)
        
        # Set definition reference path
        ref_def.definition_ref = f"{parent_path}/{short_name}"
        
        return ref_def
    
    def _parse_literals(self, element: etree._Element) -> List[str]:
        """Parse enumeration literals from ECUC-ENUMERATION-PARAM-DEF
        
        Args:
            element: ECUC-ENUMERATION-PARAM-DEF element
            
        Returns:
            List of literal values
        """
        literals = []
        literals_elem = element.find('.//ar:LITERALS', self.NAMESPACES)
        if literals_elem is not None:
            for lit_def in literals_elem.findall('ar:ECUC-ENUMERATION-LITERAL-DEF', self.NAMESPACES):
                lit_name = self._get_short_name(lit_def)
                if lit_name:
                    literals.append(lit_name)
        return literals
    
    def _convert_value(self, text: str, param_type: EcucParameterType) -> any:
        """Convert text value to appropriate Python type
        
        Args:
            text: Text value from ARXML
            param_type: Parameter type
            
        Returns:
            Converted value
        """
        if param_type == EcucParameterType.INTEGER:
            return int(text)
        elif param_type == EcucParameterType.FLOAT:
            return float(text)
        elif param_type == EcucParameterType.BOOLEAN:
            return text.lower() in ('true', '1', 'yes')
        else:
            return text
    
    # Helper methods
    
    def _get_short_name(self, element: etree._Element) -> Optional[str]:
        """Extract SHORT-NAME from element"""
        short_name_elem = element.find('ar:SHORT-NAME', self.NAMESPACES)
        return short_name_elem.text if short_name_elem is not None else None
    
    def _get_description(self, element: etree._Element) -> str:
        """Extract DESC/L-2 from element"""
        # Try DESC/L-2 first (multi-language)
        desc_elem = element.find('.//ar:DESC/ar:L-2', self.NAMESPACES)
        if desc_elem is not None and desc_elem.text:
            return desc_elem.text
        
        # Fallback to plain DESC
        desc_elem = element.find('.//ar:DESC', self.NAMESPACES)
        if desc_elem is not None and desc_elem.text:
            return desc_elem.text
        
        return ""
    
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

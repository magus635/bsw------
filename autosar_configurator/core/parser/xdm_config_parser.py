"""
XDM Configuration Parser - Specialized parser for Tresos DataModel 7.0 XDM configuration files
Parses configuration data into EcucModuleConfiguration objects
"""
from lxml import etree
from typing import Optional, List, Any
from pathlib import Path

from ..model.configuration_model import (
    EcucModuleConfiguration,
    EcucContainerValue,
    EcucParameterValue,
    EcucReferenceValue
)
from ..model.definition_model import EcucParameterType


class XdmConfigParser:
    """Parser for EB Tresos XDM Configuration files (datamodel version='7.0')"""
    
    NAMESPACES = {
        'd': 'http://www.tresos.de/_projects/DataModel2/06/data.xsd',
        'a': 'http://www.tresos.de/_projects/DataModel2/16/attribute.xsd',
        'v': 'http://www.tresos.de/_projects/DataModel2/06/schema.xsd'
    }

    def parse_file(self, file_path: Path) -> Optional[EcucModuleConfiguration]:
        """Parse XDM configuration file into EcucModuleConfiguration
        
        Args:
            file_path: Path to XDM configuration file
            
        Returns:
            EcucModuleConfiguration object or None if not an XDM configuration
        """
        if not file_path.exists():
            raise FileNotFoundError(f"File not found: {file_path}")
            
        try:
            _parser = etree.XMLParser(resolve_entities=False, no_network=True)
            tree = etree.parse(str(file_path), _parser)
            root = tree.getroot()
            
            # Find the top-level d:chc which defines the MODULE-CONFIGURATION
            module_config_elem = root.xpath(".//d:chc[@value='MODULE-CONFIGURATION']/d:ctr[@type='MODULE-CONFIGURATION']", namespaces=self.NAMESPACES)
            
            if not module_config_elem:
                return None
                
            module_config_elem = module_config_elem[0]
            
            # The parent of d:ctr is d:chc, which holds the short name of the module
            parent_chc = module_config_elem.getparent()
            short_name = parent_chc.get('name') if parent_chc is not None else "UnknownModule"
            
            config = EcucModuleConfiguration(
                short_name=short_name,
                definition_ref=""  # We might not have the exact definition_ref string in the top level XDM
            )
            
            # Parse DEF attribute for definition_ref
            def_attr = module_config_elem.xpath("./a:a[@name='DEF']/@value", namespaces=self.NAMESPACES)
            if def_attr:
                # e.g. ASPath:/THA6_ASR21/Os -> /THA6_ASR21/Os
                def_ref_str = def_attr[0]
                if def_ref_str.startswith("ASPath:"):
                    def_ref_str = def_ref_str[len("ASPath:"):]
                config.definition_ref = def_ref_str
                
            # Parse child elements (parameters, references, containers, lists)
            self._parse_children(module_config_elem, config)
            
            return config
            
        except etree.XMLSyntaxError as e:
            raise ValueError(f"XML parsing error in {file_path}: {e}")

    def _parse_children(self, parent_elem: etree._Element, parent_obj: Any):
        """Parse child elements of a container (d:ctr, d:chc, or module config)"""
        # We parse elements directly under parent_elem
        for child in parent_elem:
            tag_local = etree.QName(child).localname
            if tag_local == 'var':
                self._parse_parameter(child, parent_obj)
            elif tag_local == 'ref':
                self._parse_reference(child, parent_obj)
            elif tag_local == 'ctr':
                self._parse_container(child, parent_obj)
            elif tag_local == 'chc':
                self._parse_choice(child, parent_obj)
            elif tag_local == 'lst':
                self._parse_list(child, parent_obj)

    def _get_def_ref(self, element: etree._Element, parent_obj: Any, short_name: str) -> str:
        """Construct or extract DEFINITION-REF"""
        # First check a:a[@name='DEF']
        def_attr = element.xpath("./a:a[@name='DEF']/@value", namespaces=self.NAMESPACES)
        if def_attr:
            return def_attr[0].replace("ASPath:", "")
            
        # Fallback constructor: parent's def ref + / + short_name
        parent_def_ref = getattr(parent_obj, 'definition_ref', None)
        if parent_def_ref:
            return f"{parent_def_ref}/{short_name}"
            
        return short_name

    def _parse_parameter(self, element: etree._Element, container: Any, index: Optional[int] = None):
        """Parse d:var element into a parameter value"""
        name = element.get('name')
        if not name:
            return
            
        value = element.get('value')
        
        # In XDM, true/false are often strings, convert them if possible
        if value is not None:
            val_lower = value.strip().lower()
            if val_lower == 'true':
                value = 1
            elif val_lower == 'false':
                value = 0
            else:
                try:
                    # Attempt conversion to float/int
                    f_val = float(value)
                    if '.' not in value and 'e' not in value.lower():
                        value = int(f_val)
                    else:
                        value = f_val
                except ValueError:
                    pass # Keep as string
                    
        def_ref = self._get_def_ref(element, container, name)
        
        if hasattr(container, 'set_parameter_value'):
            if index is not None:
                container.add_multi_parameter_value(name, value, def_ref, index)
            else:
                container.set_parameter_value(name, value, def_ref)

    def _parse_reference(self, element: etree._Element, container: Any, index: Optional[int] = None):
        """Parse d:ref element into a reference value"""
        name = element.get('name')
        value = element.get('value')
        
        if not name or value is None:
            return
            
        if value.startswith("ASPath:"):
            value = value[len("ASPath:"):]
            
        def_ref = self._get_def_ref(element, container, name)
            
        if hasattr(container, 'set_reference_value'):
            if index is not None:
                container.add_multi_reference_value(name, value, def_ref, index)
            # EB Tresos list refs sometimes aren't wrapped in d:lst if it's implicitly a list. 
            # We handle it by checking if it already exists
            elif name in container.reference_values:
                existing_ref = container.reference_values.pop(name)
                # Convert to multi
                if name not in container.multi_reference_values:
                    container.multi_reference_values[name] = []
                container.multi_reference_values[name].append(existing_ref)
                container.add_multi_reference_value(name, value, def_ref, len(container.multi_reference_values[name]))
            elif name in container.multi_reference_values:
                container.add_multi_reference_value(name, value, def_ref, len(container.multi_reference_values[name]))
            else:
                container.set_reference_value(name, value, def_ref)

    def _parse_container(self, element: etree._Element, parent_obj: Any):
        """Parse d:ctr element into a sub-container"""
        name = element.get('name')
        if not name:
            i_type = element.get('type')
            if i_type:
                name = i_type
            else:
                name = "UnknownContainer"
                
        def_ref = self._get_def_ref(element, parent_obj, name)
        
        container = EcucContainerValue(short_name=name, definition_ref=def_ref)
        
        # Process children
        self._parse_children(element, container)
        
        if hasattr(parent_obj, 'add_container'):
            # It's a module config
            parent_obj.add_container(container)
        elif hasattr(parent_obj, 'add_sub_container'):
            # It's another container
            container.parent = parent_obj
            parent_obj.add_sub_container(container)
            
    def _parse_choice(self, element: etree._Element, parent_obj: Any):
        """Parse d:chc element"""
        # In EB Tresos XDM, d:chc acts as a wrapper around the chosen d:ctr or d:var
        # The choice itself has a name, and its value attribute specifies the name of the chosen child
        name = element.get('name')
        chosen_value = element.get('value') # this is the name of the active choice child
        
        if not name:
            return
            
        # Create a container representing the choice node
        def_ref = self._get_def_ref(element, parent_obj, name)
        chc_container = EcucContainerValue(short_name=name, definition_ref=def_ref)
        
        # Find the active child
        active_child = None
        for child in element:
            if child.get('name') == chosen_value:
                active_child = child
                break
                
        if active_child is not None:
            # Parse the active child into the chc_container
            tag_local = etree.QName(active_child).localname
            if tag_local == 'ctr' or tag_local == 'chc':
                # The chosen item is a container. 
                # According to AUTOSAR standard, choice containers just result in 
                # the chosen subcontainer but inside the hierarchy it's nested
                self._parse_container(active_child, chc_container)
            elif tag_local == 'var':
                self._parse_parameter(active_child, chc_container)
            elif tag_local == 'ref':
                self._parse_reference(active_child, chc_container)
            elif tag_local == 'lst':
                self._parse_list(active_child, chc_container)
                
        # Link it to parent
        if hasattr(parent_obj, 'add_container'):
            parent_obj.add_container(chc_container)
        elif hasattr(parent_obj, 'add_sub_container'):
            chc_container.parent = parent_obj
            parent_obj.add_sub_container(chc_container)

    def _parse_list(self, element: etree._Element, parent_obj: Any):
        """Parse d:lst element into multiple parameters, references, or containers"""
        # A list has a name. Its children are unnamed or systematically named items.
        # But in XDM, children usually have names (e.g., OsAppTaskRef_0) or lack names.
        # We pass an index so that parameter/reference parser knows to use multi_* methods.
        
        list_name = element.get('name')
        
        for index, child in enumerate(element):
            tag_local = etree.QName(child).localname
            # If the child doesn't have a name, supply the list name so it maps correctly
            # Wait, in XDM, list items often inherit the list name or have indexed naming.
            # E.g., d:lst name="OsAppTaskRef" -> d:ref (no name attr!)
            if not child.get('name') and list_name:
                child.set('name', list_name)
                
            if tag_local == 'var':
                self._parse_parameter(child, parent_obj, index)
            elif tag_local == 'ref':
                self._parse_reference(child, parent_obj, index)
            elif tag_local == 'ctr':
                # Sub-containers in a list. In EcucModel, sub-containers don't have "multi" arrays.
                # They are just multiple containers with the same definition reference.
                # So we just parse them directly.
                self._parse_container(child, parent_obj)
            elif tag_local == 'chc':
                self._parse_choice(child, parent_obj)


"""
ECUC Definition Parser - Specialized parser for ECUC-DEF ARXML files
Parses module/container/parameter definitions (the "blueprint")
"""
import re
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
        'xsi': 'http://www.w3.org/2001/XMLSchema-instance',
        'd': 'http://www.tresos.de/_projects/DataModel2/06/data.xsd',
        'v': 'http://www.tresos.de/_projects/DataModel2/06/schema.xsd',
        'a': 'http://www.tresos.de/_projects/DataModel2/16/attribute.xsd'
    }
    
    def __init__(self, constraints=None):
        """Initialize parser with optional chip constraints for resolving XDM expressions."""
        from .xdm_expression_resolver import XdmExpressionResolver
        self._resolver = XdmExpressionResolver(constraints or {})
    
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
                # Try XDM format: <d:chc type="AR-ELEMENT" value="MODULE-DEF">
                module_def_elem = root.xpath(".//d:chc[@value='MODULE-DEF']", namespaces=self.NAMESPACES)
                if module_def_elem:
                    module_def_elem = module_def_elem[0]
                else:
                    # Also try direct <v:ctr type="MODULE-DEF">
                    module_def_elem = root.xpath(".//v:ctr[@type='MODULE-DEF']", namespaces=self.NAMESPACES)
                    if module_def_elem:
                        module_def_elem = module_def_elem[0]
                    else:
                        module_def_elem = None

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
            # Find only immediate container defs (not all descendants)
            for container_elem in self._findall_children(containers_elem, 'ECUC-PARAM-CONF-CONTAINER-DEF'):
                container_def = self._parse_container_def(container_elem)
                if container_def:
                    # Set full definition reference path
                    container_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_def.short_name}/{container_def.short_name}"
                    module_def.add_container(container_def)
        else:
            # XDM support: Containers might be direct children or in a nested v:ctr
            # If element is d:chc, the nested v:ctr is the one with containers
            target_container_root = element
            if etree.QName(element).localname == 'chc':
                inner_ctr = element.xpath("v:ctr", namespaces=self.NAMESPACES)
                if inner_ctr:
                    target_container_root = inner_ctr[0]
            
            # Find top-level containers in the target_container_root
            for container_elem in target_container_root.xpath("./v:lst | ./v:ctr", namespaces=self.NAMESPACES):
                tag_local = etree.QName(container_elem).localname
                
                # Extract multiplicity from v:lst if applicable
                lst_lower = None
                lst_upper = None
                if tag_local == 'lst':
                    ns_a = self.NAMESPACES['a']
                    min_da = container_elem.xpath("a:da[@name='MIN']/@value", namespaces={'a': ns_a})
                    max_da = container_elem.xpath("a:da[@name='MAX']/@value", namespaces={'a': ns_a})
                    if min_da:
                        try:
                            lst_lower = int(min_da[0])
                        except ValueError:
                            pass
                    if max_da:
                        try:
                            lst_upper = int(max_da[0])
                        except ValueError:
                            pass
                    else:
                        max_da_elems = container_elem.xpath("a:da[@name='MAX']", namespaces={'a': ns_a})
                        if max_da_elems:
                            da_type = max_da_elems[0].get('type', '')
                            da_expr = max_da_elems[0].get('expr', '')
                            if da_type == 'XPath' and da_expr:
                                resolved = self._resolver.resolve_expression(da_expr)
                                if isinstance(resolved, int) and resolved > 0:
                                    lst_upper = resolved
                                else:
                                    lst_upper = -1
                        else:
                            lst_upper = -1

                # If lst, the actual ctr is inside
                target_elems = [container_elem] if tag_local == 'ctr' else container_elem.xpath("v:ctr", namespaces=self.NAMESPACES)
                for target in target_elems:
                    container_def = self._parse_container_def(target)
                    if container_def:
                        # Apply v:lst multiplicity to container definition
                        if lst_lower is not None:
                            container_def.lower_multiplicity = lst_lower
                        if lst_upper is not None:
                            container_def.upper_multiplicity = lst_upper
                            
                        # Set full definition reference path
                        container_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_def.short_name}/{container_def.short_name}"
                        # Avoid duplicates if already added
                        if container_def.short_name not in module_def.containers:
                            module_def.add_container(container_def)

            # XDM: Parse module-level v:var parameters (e.g. OsResourceSubderivative).
            # These are direct children of the module root, not inside any container.
            # They often have DEFAULT values and may not appear in the ARXML config.
            for var_elem in target_container_root.xpath("./v:var", namespaces=self.NAMESPACES):
                param_def = self._parse_parameter_def(var_elem, parent_path=module_def.short_name)
                if param_def:
                    param_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_def.short_name}/{param_def.short_name}"
                    module_def.parameters[param_def.short_name] = param_def
        
        # Set module definition reference
        module_def.definition_ref = f"/AUTOSAR/EcucDefs/{module_def.short_name}"
        
        return module_def
    
    def _parse_container_def(self, element: etree._Element, parent_path: str = "", is_choice: bool = False) -> Optional[EcucContainerDef]:
        """Parse ECUC-PARAM-CONF-CONTAINER-DEF element (recursive)"""
        short_name = self._get_short_name(element)
        if not short_name:
            return None


        container_def = EcucContainerDef(
            short_name=short_name,
            description=self._get_description(element),
            is_choice=is_choice
        )
        
        # Parse multiplicity (use direct child lookup to avoid finding sub-container's multiplicity)
        container_def.lower_multiplicity = self._get_child_int_value(element, 'LOWER-MULTIPLICITY', 0)

        # Check for UPPER-MULTIPLICITY-INFINITE first (AUTOSAR variant for unlimited)
        upper_mult_infinite = self._get_child_text_value(element, 'UPPER-MULTIPLICITY-INFINITE')
        upper_mult_text = self._get_child_text_value(element, 'UPPER-MULTIPLICITY')

        if upper_mult_infinite and upper_mult_infinite.lower() in ('1', 'true'):
            # UPPER-MULTIPLICITY-INFINITE = 1/true means unlimited (*)
            container_def.upper_multiplicity = -1
        elif upper_mult_text == '*':
            container_def.upper_multiplicity = -1
        else:
            container_def.upper_multiplicity = int(float(upper_mult_text)) if upper_mult_text else 1

        # XDM: multiplicity from a:a attributes (override defaults if present)
        ns_a = self.NAMESPACES['a']
        lower_mult_attr = element.xpath("a:a[@name='LOWER-MULTIPLICITY']/@value", namespaces={'a': ns_a})
        upper_mult_attr = element.xpath("a:a[@name='UPPER-MULTIPLICITY']/@value", namespaces={'a': ns_a})
        if lower_mult_attr:
            try:
                container_def.lower_multiplicity = int(float(lower_mult_attr[0]))
            except ValueError:
                pass
        if upper_mult_attr:
            val = upper_mult_attr[0]
            if val == '*':
                container_def.upper_multiplicity = -1
            else:
                try:
                    container_def.upper_multiplicity = int(float(val))
                except ValueError:
                    pass

        # Parse Post-Build Variant Multiplicity
        pb_mult = self._get_child_text_value(element, 'POST-BUILD-VARIANT-MULTIPLICITY')
        if pb_mult:
            container_def.post_build_variant_multiplicity = (pb_mult.lower() == 'true')
        
        # Build full path
        current_path = f"{parent_path}/{short_name}" if parent_path else short_name
        container_def.definition_ref = current_path
        
        # Parse PARAMETERS (ARXML uses <PARAMETERS>, XDM uses direct children)
        params_elem = self._find_child(element, 'PARAMETERS')
        if params_elem is not None:
            # ARXML: parameters are children of PARAMETERS
            params_to_parse = params_elem.xpath("*")
        else:
            # XDM: parameters are direct children
            params_to_parse = element.xpath("*")
            
        for child in params_to_parse:
            tag_local = etree.QName(child).localname
            # Supports ARXML (ECUC-*-PARAM-DEF, ECUC-FUNCTION-NAME-DEF, ECUC-LINKER-SYMBOL-DEF) and XDM (var)
            if 'PARAM-DEF' in tag_local.upper() or 'FUNCTION-NAME-DEF' in tag_local.upper() or 'LINKER-SYMBOL-DEF' in tag_local.upper() or tag_local == 'var':
                param_def = self._parse_parameter_def(child, current_path)
                if param_def:
                    container_def.add_parameter(param_def)
            # Supports ARXML (ECUC-*-REFERENCE-DEF) and XDM (ref)
            # (Note: In ARXML, these are usually in REFERENCES element, handled separately below)
            elif tag_local == 'ref':
                ref_def = self._parse_reference_def(child, current_path)
                if ref_def:
                    container_def.add_reference(ref_def)
        
        # Parse REFERENCES (only direct children, not descendants)
        refs_elem = self._find_child(element, 'REFERENCES')
        if refs_elem is not None:
            # Find only immediate reference defs (both standard and choice references)
            for ref_elem in self._findall_children(refs_elem, 'ECUC-REFERENCE-DEF'):
                ref_def = self._parse_reference_def(ref_elem, current_path)
                if ref_def:
                    container_def.add_reference(ref_def)
            # Also parse ECUC-CHOICE-REFERENCE-DEF (multi-destination references)
            for ref_elem in self._findall_children(refs_elem, 'ECUC-CHOICE-REFERENCE-DEF'):
                ref_def = self._parse_choice_reference_def(ref_elem, current_path)
                if ref_def:
                    container_def.add_reference(ref_def)
        
        # Parse SUB-CONTAINERS (recursive, only direct children)
        sub_conts_elem = self._find_child(element, 'SUB-CONTAINERS')
        if sub_conts_elem is not None:
            # Find only immediate sub-container defs
            for sub_cont_elem in self._findall_children(sub_conts_elem, 'ECUC-PARAM-CONF-CONTAINER-DEF'):
                sub_container_def = self._parse_container_def(sub_cont_elem, current_path)
                if sub_container_def:
                    container_def.add_sub_container(sub_container_def)
        
            # Also parse ECUC-CHOICE-CONTAINER-DEF (choice containers)
            for sub_cont_elem in self._findall_children(sub_conts_elem, 'ECUC-CHOICE-CONTAINER-DEF'):
                sub_container_def = self._parse_container_def(sub_cont_elem, current_path, is_choice=True)
                if sub_container_def:
                    container_def.add_sub_container(sub_container_def)
        
        # XDM support: Parse sub-containers and multi-references from v:lst/v:ctr/v:chc
        ns_v = self.NAMESPACES['v']
        ns_a = self.NAMESPACES['a']

        # First: handle direct v:var and v:ref children (single-valued, not inside v:lst).
        # This covers cases like <v:ctr name="RegionSelect"><v:ref name="MemoryBlockRef">
        # where the reference belongs directly to the container, not under a list wrapper.
        for var_elem in element.xpath("v:var", namespaces={'v': ns_v}):
            param_def = self._parse_parameter_def(var_elem, current_path)
            if param_def and param_def.short_name not in container_def.parameters:
                container_def.add_parameter(param_def)
        for ref_elem in element.xpath("v:ref", namespaces={'v': ns_v}):
            ref_def_item = self._parse_reference_def(ref_elem, current_path)
            if ref_def_item and ref_def_item.short_name not in container_def.references:
                container_def.add_reference(ref_def_item)

        for sub_elem in element.xpath("v:lst | v:ctr | v:chc", namespaces={'v': ns_v}):
            tag_local = etree.QName(sub_elem).localname
            if tag_local == 'lst':
                # Extract multiplicity from v:lst's a:da MIN/MAX
                min_da = sub_elem.xpath("a:da[@name='MIN']/@value", namespaces={'a': ns_a})
                max_da = sub_elem.xpath("a:da[@name='MAX']/@value", namespaces={'a': ns_a})
                max_da_elems = sub_elem.xpath("a:da[@name='MAX']", namespaces={'a': ns_a})

                lst_lower = None
                lst_upper = None
                lst_upper_expr = None
                if min_da:
                    try: lst_lower = int(min_da[0])
                    except ValueError: pass
                if max_da:
                    try: lst_upper = int(max_da[0])
                    except ValueError: pass
                elif max_da_elems:
                    da_type = max_da_elems[0].get('type', '')
                    da_expr = max_da_elems[0].get('expr', '')
                    if da_type == 'XPath' and da_expr:
                        lst_upper_expr = da_expr
                        resolved = self._resolver.resolve_expression(da_expr)
                        if isinstance(resolved, int) and resolved > 0:
                            lst_upper = resolved
                        else:
                            lst_upper = -1  # unresolvable or 0 -> treat as unbounded

                # Handle v:ctr inside v:lst (multi-container / sub-container)
                ctr_children = sub_elem.xpath("v:ctr", namespaces={'v': ns_v})
                for ctr_child in ctr_children:
                    sub_container_def = self._parse_container_def(ctr_child, current_path)
                    if sub_container_def:
                        # Apply v:lst multiplicity to the container def
                        if lst_lower is not None:
                            sub_container_def.lower_multiplicity = lst_lower
                        if lst_upper is not None:
                            sub_container_def.upper_multiplicity = lst_upper
                        elif not max_da and not max_da_elems:
                             sub_container_def.upper_multiplicity = -1
                        
                        container_def.add_sub_container(sub_container_def)

                # Handle v:var inside v:lst (multi-parameters)
                var_children = sub_elem.xpath("v:var", namespaces={'v': ns_v})
                for var_child in var_children:
                    param_def = self._parse_parameter_def(var_child, current_path)
                    if param_def:
                        if lst_lower is not None:
                            param_def.lower_multiplicity = lst_lower
                        if lst_upper is not None:
                            param_def.upper_multiplicity = lst_upper
                        elif not max_da and not max_da_elems:
                            param_def.upper_multiplicity = -1
                        if param_def.short_name not in container_def.parameters:
                            container_def.add_parameter(param_def)

                # Handle v:ref inside v:lst (multi-references)
                ref_children = sub_elem.xpath("v:ref", namespaces={'v': ns_v})
                for ref_child in ref_children:
                    ref_def = self._parse_reference_def(ref_child, current_path)
                    if ref_def:
                        if lst_lower is not None:
                            ref_def.lower_multiplicity = lst_lower
                        if lst_upper is not None:
                            ref_def.upper_multiplicity = lst_upper
                        elif not max_da and not max_da_elems:
                            ref_def.upper_multiplicity = -1  # no MAX specified -> unbounded
                        if ref_def.short_name not in container_def.references:
                            container_def.add_reference(ref_def)

                # Handle v:ctr inside v:lst (sub-containers with list multiplicity)
                target_elems = sub_elem.xpath("v:ctr", namespaces={'v': ns_v})
                for target in target_elems:
                    sub_container_def = self._parse_container_def(target, current_path)
                    if sub_container_def:
                        if lst_lower is not None:
                            sub_container_def.lower_multiplicity = lst_lower
                        if lst_upper is not None:
                            sub_container_def.upper_multiplicity = lst_upper
                        if lst_upper_expr:
                            sub_container_def.upper_multiplicity_expr = lst_upper_expr
                        if sub_container_def.short_name not in container_def.sub_containers:
                            container_def.add_sub_container(sub_container_def)
            elif tag_local == 'ctr' or tag_local == 'chc':
                sub_container_def = self._parse_container_def(sub_elem, current_path, is_choice=(tag_local == 'chc'))
                if sub_container_def:
                    if sub_container_def.short_name not in container_def.sub_containers:
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
            # Map XDM 'var' to BOOLEAN as a guess, or better, look at type attribute
            if tag_name == 'var':
                xdm_type = element.get('type', '').upper()
                if xdm_type == 'ENUMERATION': param_type = EcucParameterType.ENUMERATION
                elif xdm_type == 'INTEGER': param_type = EcucParameterType.INTEGER
                elif xdm_type == 'FLOAT': param_type = EcucParameterType.FLOAT
                elif xdm_type == 'BOOLEAN': param_type = EcucParameterType.BOOLEAN
                elif xdm_type == 'STRING': param_type = EcucParameterType.STRING
                elif xdm_type == 'FUNCTION-NAME': param_type = EcucParameterType.FUNCTION
                else: param_type = EcucParameterType.STRING # Default
            else:
                param_type = EcucParameterType(tag_name)
        except ValueError:
            # Unknown type, skip
            return None
        
        param_def = EcucParameterDef(
            short_name=short_name,
            param_type=param_type,
            description=self._get_description(element)
        )
        
        # Parse multiplicity (use direct child lookup)
        param_def.lower_multiplicity = self._get_child_int_value(element, 'LOWER-MULTIPLICITY', 0)
        param_def.upper_multiplicity = self._get_child_int_value(element, 'UPPER-MULTIPLICITY', 1)
        
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
            
        # Parse XDM attributes and data attributes (DEFAULT, RANGE, etc.)
        self._parse_xdm_attributes(element, param_def)
        self._parse_xdm_data_attributes(element, param_def, param_type)
            
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
        
        # Look for IMPLEMENTATION-CONFIG-CLASSES or VALUE-CONFIG-CLASSES
        config_container = self._find_descendant(element, 'IMPLEMENTATION-CONFIG-CLASSES') or \
                           self._find_descendant(element, 'VALUE-CONFIG-CLASSES')
        
        if config_container is not None:
            # ARXML structure
            icc_elem = self._find_descendant(config_container, 'ECUC-IMPLEMENTATION-CONFIGURATION-CLASS') or \
                       self._find_descendant(config_container, 'ECUC-VALUE-CONFIGURATION-CLASS')
            if icc_elem is not None:
                config_class = self._get_text_value(icc_elem, 'CONFIG-CLASS')
                config_variant = self._get_text_value(icc_elem, 'CONFIG-VARIANT')
                
                if config_class:
                    param_def.config_class = config_class
                if config_variant:
                    param_def.config_variant = config_variant
        
        # XDM support: Variability in XDM uses different attributes/elements
        if not param_def.config_class:
            # Look for icc:v elements (simplified)
            icc_v = element.xpath(".//icc:v", namespaces={'icc': 'http://www.tresos.de/_projects/DataModel2/08/implconfigclass.xsd'})
            if icc_v:
                param_def.config_class = icc_v[0].get('vclass', '')

        # --- XDM: Parse a:a attributes and a:da data attributes ---
        self._parse_xdm_attributes(element, param_def)
        self._parse_xdm_data_attributes(element, param_def, param_type)

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

        # XDM: destination from <a:da name="REF" value="ASPathDataOfSchema:/.../path"/>
        if not ref_def.destination_ref:
            ns_a = self.NAMESPACES['a']
            ref_da = element.xpath("a:da[@name='REF']/@value", namespaces={'a': ns_a})
            if ref_da:
                raw_ref = ref_da[0]
                if raw_ref.startswith('ASPathDataOfSchema:'):
                    raw_ref = raw_ref[len('ASPathDataOfSchema:'):]
                ref_def.destination_ref = raw_ref
                ref_def.destination_type = 'ECUC-PARAM-CONF-CONTAINER-DEF'

        # XDM: extract a:a attributes for multiplicity, scope, origin
        self._parse_xdm_attributes(element, ref_def)

        # Parse multiplicity (use direct child lookup)
        ref_def.lower_multiplicity = self._get_child_int_value(element, 'LOWER-MULTIPLICITY', 0)
        ref_def.upper_multiplicity = self._get_child_int_value(element, 'UPPER-MULTIPLICITY', 1)

        # Check UPPER-MULTIPLICITY-INFINITE
        infinite_val = self._get_child_text_value(element, 'UPPER-MULTIPLICITY-INFINITE')
        if infinite_val is not None and infinite_val.strip() == '1':
            ref_def.upper_multiplicity = -1  # -1 means infinite

        # Set definition reference path
        ref_def.definition_ref = f"{parent_path}/{short_name}"

        return ref_def

    def _parse_choice_reference_def(self, element: etree._Element, parent_path: str = "") -> Optional[EcucReferenceDef]:
        """Parse ECUC-CHOICE-REFERENCE-DEF element (multi-destination reference).

        Choice references allow pointing to multiple possible container types.
        E.g., ResourceModuleRef can point to AdcHwUnit, CanController, etc.
        """
        short_name = self._get_short_name(element)
        if not short_name:
            return None

        ref_def = EcucReferenceDef(
            short_name=short_name,
            description=self._get_description(element)
        )

        # Parse DESTINATION-REFS (multiple destination references)
        dest_refs_elem = self._find_descendant(element, 'DESTINATION-REFS')
        destination_refs = []
        if dest_refs_elem is not None:
            for dest_ref_elem in self._findall_descendants(dest_refs_elem, 'DESTINATION-REF'):
                dest_text = dest_ref_elem.text
                if dest_text:
                    destination_refs.append(dest_text.strip())

        # Use first destination as primary, store all as choice_destination_refs
        if destination_refs:
            ref_def.destination_ref = destination_refs[0]
            ref_def.destination_type = 'ECUC-PARAM-CONF-CONTAINER-DEF'

        # Store all choice destinations for UI display
        ref_def.choice_destination_refs = destination_refs

        # Parse multiplicity (use direct child lookup)
        ref_def.lower_multiplicity = self._get_child_int_value(element, 'LOWER-MULTIPLICITY', 0)
        ref_def.upper_multiplicity = self._get_child_int_value(element, 'UPPER-MULTIPLICITY', 1)

        # Check UPPER-MULTIPLICITY-INFINITE
        infinite_val = self._get_child_text_value(element, 'UPPER-MULTIPLICITY-INFINITE')
        if infinite_val is not None and infinite_val.strip() == '1':
            ref_def.upper_multiplicity = -1  # -1 means infinite

        # Set definition reference path
        ref_def.definition_ref = f"{parent_path}/{short_name}"

        return ref_def

    def _parse_xdm_attributes(self, element, target_def):
        """Parse a:a attribute elements for SCOPE, ORIGIN, SYMBOLICNAMEVALUE, multiplicity.

        XDM stores these as: <a:a name="SCOPE" value="LOCAL"/>
        """
        ns_a = self.NAMESPACES['a']
        for attr_elem in element.xpath("a:a", namespaces={'a': ns_a}):
            name = attr_elem.get('name', '')
            value = attr_elem.get('value', '')
            if not name:
                continue
            # Some attributes like RANGE/DEFAULT might use 'expr' instead of 'value'
            if not value and not attr_elem.get('expr'):
                # Multiplicity or other simple attributes MUST have value
                if name in ('SCOPE', 'ORIGIN', 'LOWER-MULTIPLICITY', 'UPPER-MULTIPLICITY'):
                    continue
            if name == 'SCOPE':
                target_def.scope = value
            elif name == 'ORIGIN':
                target_def.origin = value
            elif name == 'SYMBOLICNAMEVALUE' and hasattr(target_def, 'symbolic_name_value'):
                target_def.symbolic_name_value = (value.lower() == 'true')
            elif name == 'LOWER-MULTIPLICITY':
                try:
                    target_def.lower_multiplicity = int(float(value))
                except ValueError:
                    pass
            elif name == 'UPPER-MULTIPLICITY':
                if value == '*':
                    target_def.upper_multiplicity = -1
                else:
                    try:
                        target_def.upper_multiplicity = int(float(value))
                    except ValueError:
                        pass
            elif name == 'DEFAULT' and isinstance(target_def, EcucParameterDef):
                da_type = attr_elem.get('type', '')
                da_expr = attr_elem.get('expr', '')
                self._parse_xdm_default(attr_elem, target_def, target_def.param_type, da_type, value, da_expr)
            elif name == 'RANGE' and isinstance(target_def, EcucParameterDef):
                da_type = attr_elem.get('type', '')
                da_expr = attr_elem.get('expr', '')
                self._parse_xdm_range(attr_elem, target_def, target_def.param_type, da_type, da_expr)

    def _parse_xdm_data_attributes(self, element, param_def, param_type):
        """Parse a:da data attribute elements for DEFAULT, RANGE, INVALID."""
        ns_a = self.NAMESPACES['a']
        for da_elem in element.xpath("a:da", namespaces={'a': ns_a}):
            da_name = da_elem.get('name', '')
            da_type = da_elem.get('type', '')
            da_value = da_elem.get('value', '')
            da_expr = da_elem.get('expr', '')

            if da_name == 'DEFAULT':
                self._parse_xdm_default(da_elem, param_def, param_type, da_type, da_value, da_expr)
            elif da_name == 'RANGE':
                self._parse_xdm_range(da_elem, param_def, param_type, da_type, da_expr)
            elif da_name == 'INVALID':
                self._parse_xdm_invalid(da_elem, param_def, param_type, da_type)

    def _parse_xdm_default(self, da_elem, param_def, param_type, da_type, da_value, da_expr):
        """Parse DEFAULT a:da element."""
        if da_type == 'XPath' or da_expr:
            expr = da_expr
            if not expr:
                ns_a = self.NAMESPACES['a']
                tst = da_elem.xpath("a:tst/@expr", namespaces={'a': ns_a})
                if tst:
                    expr = tst[0]
            if expr:
                param_def.default_expr = expr
                resolved = self._resolver.resolve_expression(expr)
                if resolved is not None:
                    param_def.default_value = resolved
        elif da_value and param_def.default_value is None:
            # Static default - only set if not already set by ARXML path
            param_def.default_value = self._convert_value(da_value, param_type)

    def _parse_xdm_range(self, da_elem, param_def, param_type, da_type, da_expr):
        """Parse RANGE a:da element for enumeration literals."""
        ns_a = self.NAMESPACES['a']

        if da_type == 'XPath' or da_expr:
            expr = da_expr or ''
            if not expr:
                tst_elems = da_elem.xpath("a:tst/@expr", namespaces={'a': ns_a})
                if tst_elems:
                    expr = tst_elems[0]
            if expr:
                param_def.range_expr = expr
                resolved = self._resolver.resolve_expression(expr)
                if isinstance(resolved, list) and len(resolved) > 0 and param_type == EcucParameterType.ENUMERATION:
                    param_def.literals = resolved
        else:
            # Static inline: <a:v>VAL1</a:v><a:v>VAL2</a:v>
            values = da_elem.xpath("a:v/text()", namespaces={'a': ns_a})
            if values and param_type == EcucParameterType.ENUMERATION:
                param_def.literals = [v.strip() for v in values if v.strip()]

    def _parse_xdm_invalid(self, da_elem, param_def, param_type, da_type):
        """Parse INVALID a:da element for min/max range constraints."""
        if da_type != 'Range':
            return
        ns_a = self.NAMESPACES['a']
        for tst in da_elem.xpath("a:tst", namespaces={'a': ns_a}):
            expr = tst.get('expr', '')
            if not expr:
                continue
            
            # Match hexadecimal (e.g., 0xFFFFFFFF) or scientific/floating point/integer (e.g., 1.0E-3, 4e-8)
            pattern = r'(0[xX][0-9a-fA-F]+|-?\d+\.?\d*(?:[eE][-+]?\d+)?)'
            m_le = re.match(r'<=\s*' + pattern, expr)
            m_ge = re.match(r'>=\s*' + pattern, expr)
            
            if m_le:
                val_str = m_le.group(1)
                try:
                    val = int(val_str, 16) if val_str.lower().startswith('0x') else float(val_str)
                    if param_type == EcucParameterType.FLOAT:
                        param_def.max_value = float(val)
                    else:
                        param_def.max_value = int(val)
                except ValueError:
                    pass
            elif m_ge:
                val_str = m_ge.group(1)
                try:
                    val = int(val_str, 16) if val_str.lower().startswith('0x') else float(val_str)
                    if param_type == EcucParameterType.FLOAT:
                        param_def.min_value = float(val)
                    else:
                        param_def.min_value = int(val)
                except ValueError:
                    pass

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

    def _findall_children(self, element: etree._Element, tag_name: str) -> List[etree._Element]:
        """Find immediate children with tag_name, ignoring namespace"""
        # 1. Try direct find with namespace
        elems = element.findall(f"ar:{tag_name}", self.NAMESPACES)
        if elems:
            return elems

        # 2. XPath local-name
        xpath = f"./*[local-name()='{tag_name}']"
        return element.xpath(xpath)

    def _find_child(self, element: etree._Element, tag_name: str) -> Optional[etree._Element]:
        """Find first immediate child with tag_name, ignoring namespace"""
        children = self._findall_children(element, tag_name)
        return children[0] if children else None

    def _get_short_name(self, element: etree._Element) -> Optional[str]:
        """Extract SHORT-NAME from element (direct child) or 'name' attribute (XDM)"""
        # 1. Try 'name' attribute (XDM format)
        name_attr = element.get('name')
        if name_attr:
            return name_attr
            
        # 2. Try SHORT-NAME element (ARXML format)
        for child in element:
            if etree.QName(child).localname == 'SHORT-NAME':
                return child.text
        return None
    
    def _get_description(self, element: etree._Element) -> str:
        """Extract DESC/L-2 from element (ARXML) or a:a/DESC attribute (XDM)"""
        # 1. Try XDM format: <a:a name="DESC" value="..." />
        desc_attr = element.xpath("./a:a[@name='DESC']/@value", namespaces={'a': 'http://www.tresos.de/_projects/DataModel2/16/attribute.xsd'})
        if desc_attr:
            return desc_attr[0]
            
        # 2. Try ARXML format: L-2 element
        l2_elem = self._find_descendant(element, 'L-2')
        if l2_elem is not None and l2_elem.text:
            return l2_elem.text
            
        # 3. Fallback to DESC element
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

    def _get_child_text_value(self, element: etree._Element, tag_name: str) -> Optional[str]:
        """Get text value of a direct child element only (not descendants)"""
        elem = self._find_child(element, tag_name)
        return elem.text if elem is not None else None

    def _get_child_int_value(self, element: etree._Element, tag_name: str, default: int = 0) -> int:
        """Get integer value of a direct child element only (not descendants)"""
        text = self._get_child_text_value(element, tag_name)
        try:
            return int(float(text)) if text else default
        except ValueError:
            return default

    def _get_int_value(self, element: etree._Element, tag_name: str, default: int = 0) -> int:
        """Get integer value of a descendant"""
        text = self._get_text_value(element, tag_name)
        try:
            return int(float(text)) if text else default
        except ValueError:
            return default

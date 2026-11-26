"""
ECUC Value Serializer
Serializes EcucModuleConfiguration to ARXML format
"""
from lxml import etree
from typing import Any, Dict, Optional, Set, Tuple
from pathlib import Path
from ..model.configuration_model import (
    DEFAULT_VARIANT,
    normalize_config_variant,
    override_layer,
    EcucModuleConfiguration,
    EcucContainerValue,
    EcucParameterValue,
    EcucReferenceValue,
)
from ..model.definition_model import EcucParameterType

_NO_OVERRIDE = object()

# Parameter definition types whose value is ECUC-TEXTUAL-PARAM-VALUE / -NUMERICAL-
_TEXTUAL_PARAM_DESTS = frozenset({
    'ECUC-ENUMERATION-PARAM-DEF', 'ECUC-STRING-PARAM-DEF', 'ECUC-MULTILINE-STRING-PARAM-DEF',
    'ECUC-FUNCTION-NAME-DEF', 'ECUC-LINKER-SYMBOL-DEF',
})
_NUMERICAL_PARAM_DESTS = frozenset({
    'ECUC-INTEGER-PARAM-DEF', 'ECUC-FLOAT-PARAM-DEF', 'ECUC-BOOLEAN-PARAM-DEF',
})


def _param_value_tag(param: EcucParameterValue) -> str:
    """Element of a parameter value: by its definition type when known (an
    enumeration literal "64" is textual), else by the Python type of the value."""
    dest = getattr(param, 'dest_type', None)
    if dest in _TEXTUAL_PARAM_DESTS:
        return 'ECUC-TEXTUAL-PARAM-VALUE'
    if dest in _NUMERICAL_PARAM_DESTS or isinstance(param.value, (int, float, bool)):
        return 'ECUC-NUMERICAL-PARAM-VALUE'
    return 'ECUC-TEXTUAL-PARAM-VALUE'


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
        # id() of configuration objects left out of the current export (export_epc skip)
        self._skip = frozenset()
        self._emit_container_variant_sdg = True
        self._export_active_variant: Optional[str] = None
        self._export_variant_overrides: Dict[str, Any] = {}

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

    def export_epc(self, configuration: EcucModuleConfiguration, file_path: Path, encoding: str = 'utf-8',
                   skip: Optional[Set[int]] = None, active_variant: Optional[str] = None):
        """Export configuration as an EB Tresos-compatible .epc value file.

        Matches the layout EB Tresos itself produces: the AR-PACKAGE short-name
        is the module name (not '{Module}_Config') and the schemaLocation is
        AUTOSAR_00046.xsd. Element structure and ordering are identical to
        serialize_to_file (deterministic: same configuration → same bytes).

        Args:
            skip: id() of containers / parameter values / reference values to leave
                out, e.g. items whose definition ENABLE condition is false
            active_variant: when provided, filters containers to those visible in
                that variant and materializes its parameter/reference overrides
        """
        self._skip = frozenset(skip or ())
        self._emit_container_variant_sdg = False
        self._export_active_variant = active_variant
        layer = override_layer(active_variant) if active_variant is not None else None
        raw_overrides = (getattr(configuration, 'variant_overrides', None) or {}).get(layer, {}) if layer else {}
        self._export_variant_overrides = dict(raw_overrides) if isinstance(raw_overrides, dict) else {}
        try:
            root = self._create_arxml_root(
                configuration,
                package_name=configuration.short_name,
                schema_file='AUTOSAR_00046.xsd',
            )
        finally:
            self._skip = frozenset()
            self._emit_container_variant_sdg = True
            self._export_active_variant = None
            self._export_variant_overrides = {}
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

        # Module-level parameters (no place for them in AUTOSAR): ADMIN-DATA/SDG,
        # read back by the ARXML parser
        module_params = getattr(configuration, 'parameter_values', {}) or {}
        if module_params:
            from ..parser.arxml_parser import MODULE_PARAMETERS_GID
            admin = etree.SubElement(module_config, 'ADMIN-DATA')
            sdgs = etree.SubElement(admin, 'SDGS')
            sdg = etree.SubElement(sdgs, 'SDG', GID=MODULE_PARAMETERS_GID)
            for name in sorted(module_params):
                sd = etree.SubElement(sdg, 'SD', GID=name)
                value = module_params[name].value
                sd.text = "" if value is None else str(value)
                
        # Definition reference
        def_ref = etree.SubElement(module_config, 'DEFINITION-REF', DEST='ECUC-MODULE-DEF')
        def_ref.text = configuration.definition_ref
        
        # Implementation config variant
        variant = etree.SubElement(module_config, 'IMPLEMENTATION-CONFIG-VARIANT')
        variant.text = normalize_config_variant(configuration.implementation_config_variant)
        
        # Containers
        containers_elem = etree.SubElement(module_config, 'CONTAINERS')
        
        # Serialize top-level containers
        # Note: configuration.containers only has top-level containers
        for container in self._kept_containers(configuration.containers):
            self._serialize_container(container, containers_elem)
            
        return root

    def _container_included_in_export(self, container: EcucContainerValue) -> bool:
        """Return True when ``container`` belongs to ``_export_active_variant`` (or no variant filter)."""
        if self._export_active_variant is None:
            return True
        eff_active = self._export_active_variant or DEFAULT_VARIANT
        c_var = getattr(container, 'variant', None)
        return c_var in (None, "") or c_var == eff_active

    def _kept_containers(self, containers) -> list:
        """Containers not skipped by ``export_epc(skip=...)`` and matching active variant filter."""
        return [c for c in self._kept(containers) if self._container_included_in_export(c)]

    def _resolve_export_override(self, container: EcucContainerValue, key_suffix: str) -> Tuple[bool, Any]:
        """Look up variant override for ``container`` + ``key_suffix`` during active-variant EPC export."""
        if not self._export_variant_overrides:
            return False, None
        full_key = f"{container.get_path()}.{key_suffix}"
        if full_key in self._export_variant_overrides:
            return True, self._export_variant_overrides[full_key]
        if container.parent is None:
            short_key = f"{container.short_name}.{key_suffix}"
            if short_key in self._export_variant_overrides:
                return True, self._export_variant_overrides[short_key]
        return False, None

    def _serialize_container(self, container: EcucContainerValue, parent_elem: etree._Element):
        """Serialize container value"""
        container_elem = etree.SubElement(parent_elem, 'ECUC-CONTAINER-VALUE')

        # UUID attribute (preserve from original if present)
        if container.uuid:
            container_elem.set('UUID', container.uuid)
        
        # Short name
        short_name = etree.SubElement(container_elem, 'SHORT-NAME')
        short_name.text = container.short_name

        # Container-level variant assignment (if set and enabled): ADMIN-DATA/SDG
        if self._emit_container_variant_sdg and getattr(container, 'variant', None):
            from ..parser.arxml_parser import CONTAINER_VARIANT_GID
            admin = etree.SubElement(container_elem, 'ADMIN-DATA')
            sdgs = etree.SubElement(admin, 'SDGS')
            sdg = etree.SubElement(sdgs, 'SDG', GID=CONTAINER_VARIANT_GID)
            sd = etree.SubElement(sdg, 'SD', GID='variant')
            sd.text = str(container.variant)

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
        params = [
            (param_name, param)
            for param_name, param in container.parameter_values.items()
            if id(param) not in self._skip
        ]
        if params:
            param_values_elem = etree.SubElement(container_elem, 'PARAMETER-VALUES')
            for param_name, param in params:
                has_ov, ov_val = self._resolve_export_override(container, param_name)
                self._serialize_parameter(
                    param,
                    param_values_elem,
                    value_override=ov_val if has_ov else _NO_OVERRIDE,
                )

        # Multi-valued parameters (with INDEX)
        multi_params = self._kept_lists(getattr(container, 'multi_parameter_values', None))
        if multi_params:
            if param_values_elem is None:
                param_values_elem = etree.SubElement(container_elem, 'PARAMETER-VALUES')
            for param_name, param_list in multi_params.items():
                has_list_ov, list_ov_val = self._resolve_export_override(container, param_name)
                for idx_pos, param_val in enumerate(sorted(param_list, key=lambda p: p.index if p.index is not None else 0)):
                    eff_idx = param_val.index if param_val.index is not None else idx_pos
                    has_idx_ov, idx_ov_val = self._resolve_export_override(container, f"{param_name}[{eff_idx}]")
                    if has_idx_ov:
                        effective_val = idx_ov_val
                    elif has_list_ov and isinstance(list_ov_val, list) and idx_pos < len(list_ov_val):
                        effective_val = list_ov_val[idx_pos]
                    else:
                        effective_val = param_val.value
                    tag_name = _param_value_tag(param_val)
                    param_elem = etree.SubElement(param_values_elem, tag_name)
                    if param_val.index is not None:
                        index_elem = etree.SubElement(param_elem, 'INDEX')
                        index_elem.text = str(param_val.index)
                    multi_param_dest = getattr(param_val, 'dest_type', None) or 'ECUC-PARAMETER-DEF'
                    def_ref = etree.SubElement(param_elem, 'DEFINITION-REF', DEST=multi_param_dest)
                    def_ref.text = param_val.definition_ref
                    if effective_val is None:
                        continue                    # no value: no <VALUE> (as EB writes it)
                    value_elem = etree.SubElement(param_elem, 'VALUE')
                    if isinstance(effective_val, bool):
                        value_elem.text = 'true' if effective_val else 'false'
                    else:
                        value_elem.text = str(effective_val)
                
        # NOTE: unknown parameters (imported values not in the definition)
        # remain inside parameter_values / multi_parameter_values and are
        # therefore written out by the loops above — container.unknown_parameters
        # is only an index of flagged names, never a separate value store.

        # References - create wrapper once
        ref_values_elem = None
        refs = [
            (ref_name, ref)
            for ref_name, ref in container.reference_values.items()
            if id(ref) not in self._skip
        ]
        if refs:
            ref_values_elem = etree.SubElement(container_elem, 'REFERENCE-VALUES')
            for ref_name, ref in refs:
                has_ov, ov_val = self._resolve_export_override(container, f"ref:{ref_name}")
                self._serialize_reference(
                    ref,
                    ref_values_elem,
                    value_ref_override=ov_val if has_ov else _NO_OVERRIDE,
                )

        # Multi-valued references (with INDEX)
        multi_refs = self._kept_lists(getattr(container, 'multi_reference_values', None))
        if multi_refs:
            if ref_values_elem is None:
                ref_values_elem = etree.SubElement(container_elem, 'REFERENCE-VALUES')
            for ref_name, ref_list in multi_refs.items():
                for ref_val in sorted(ref_list, key=lambda r: r.index if r.index is not None else 0):
                    self._serialize_reference(ref_val, ref_values_elem, include_index=True)

        # Sub-containers
        sub_containers = self._kept_containers(container.sub_containers)
        if sub_containers:
            sub_containers_elem = etree.SubElement(container_elem, 'SUB-CONTAINERS')
            for sub_container in sub_containers:
                self._serialize_container(sub_container, sub_containers_elem)

    def _kept(self, items) -> list:
        """Items not in the export's skip set (see export_epc)."""
        return [item for item in items if id(item) not in self._skip]

    def _kept_lists(self, lists):
        """name -> values without skipped values; names whose values were all skipped go."""
        if not lists:
            return lists
        out = {}
        for name, values in lists.items():
            kept = self._kept(values)
            if kept or not values:
                out[name] = kept
        return out

    def _serialize_parameter(self, param: EcucParameterValue, param_values_elem: etree._Element,
                             include_index: bool = False, value_override: Any = _NO_OVERRIDE):
        """Serialize parameter value

        Args:
            param: Parameter value to serialize
            param_values_elem: The PARAMETER-VALUES wrapper element to add to
            include_index: Write the INDEX element when param.index is set
            value_override: Optional override value replacing param.value for variant export
        """
        effective_value = param.value if value_override is _NO_OVERRIDE else value_override

        # Determine specific element type
        tag_name = _param_value_tag(param)

        param_elem = etree.SubElement(param_values_elem, tag_name)

        if include_index and param.index is not None:
            index_elem = etree.SubElement(param_elem, 'INDEX')
            index_elem.text = str(param.index)

        # Definition reference
        param_dest = getattr(param, 'dest_type', None) or 'ECUC-PARAMETER-DEF'
        def_ref = etree.SubElement(param_elem, 'DEFINITION-REF', DEST=param_dest)
        def_ref.text = param.definition_ref

        if effective_value is None:
            return                              # no value: no <VALUE> (as EB writes it), not "None"

        # Value
        value_elem = etree.SubElement(param_elem, 'VALUE')
        
        if isinstance(effective_value, bool):
            value_elem.text = 'true' if effective_value else 'false'
        else:
            value_elem.text = str(effective_value)

    def _serialize_reference(self, ref: EcucReferenceValue, ref_values_elem: etree._Element,
                             include_index: bool = False,
                             value_ref_override: Any = _NO_OVERRIDE):
        """Serialize reference value (ECUC-REFERENCE-VALUE or ECUC-INSTANCE-REFERENCE-VALUE).

        Args:
            ref: Reference value to serialize
            ref_values_elem: The REFERENCE-VALUES wrapper element to add to
            include_index: Write the INDEX element when ref.index is set
            value_ref_override: Optional override target path for variant export
        """
        effective_ref = ref.value_ref if value_ref_override is _NO_OVERRIDE else value_ref_override
        effective_ref_text = "" if effective_ref is None else str(effective_ref)
        is_iref = bool(
            getattr(ref, 'is_instance_reference', False)
            or getattr(ref, 'dest_type', None) == 'ECUC-INSTANCE-REFERENCE-DEF'
            or getattr(ref, 'context_element_refs', None)
        )
        elem_tag = 'ECUC-INSTANCE-REFERENCE-VALUE' if is_iref else 'ECUC-REFERENCE-VALUE'
        ref_elem = etree.SubElement(ref_values_elem, elem_tag)

        if include_index and ref.index is not None:
            index_elem = etree.SubElement(ref_elem, 'INDEX')
            index_elem.text = str(ref.index)

        # Definition reference
        default_def_dest = 'ECUC-INSTANCE-REFERENCE-DEF' if is_iref else 'ECUC-REFERENCE-DEF'
        ref_dest = getattr(ref, 'dest_type', None) or default_def_dest
        def_ref = etree.SubElement(ref_elem, 'DEFINITION-REF', DEST=ref_dest)
        def_ref.text = ref.definition_ref

        # Value (Target reference)
        val_dest = getattr(ref, 'value_ref_dest', None) or 'ECUC-CONTAINER-VALUE'
        if is_iref:
            iref_elem = etree.SubElement(ref_elem, 'VALUE-IREF')
            for ctx_dest, ctx_path in getattr(ref, 'context_element_refs', None) or []:
                attrs = {'DEST': ctx_dest} if ctx_dest else {}
                ctx_elem = etree.SubElement(iref_elem, 'CONTEXT-ELEMENT-REF', **attrs)
                ctx_elem.text = ctx_path
            target_elem = etree.SubElement(iref_elem, 'TARGET-REF', DEST=val_dest)
            target_elem.text = effective_ref_text
        else:
            value_elem = etree.SubElement(ref_elem, 'VALUE-REF', DEST=val_dest)
            value_elem.text = effective_ref_text

"""Read-only parser indexing SWC types, interfaces, ports, runnables, connectors, and SR mappings."""

from dataclasses import dataclass, field
import logging
from pathlib import Path
from typing import Dict, List, Optional, Tuple
from lxml import etree

logger = logging.getLogger(__name__)

_SWC_TYPE_TAGS = frozenset({
    "APPLICATION-SW-COMPONENT-TYPE",
    "SERVICE-SW-COMPONENT-TYPE",
    "COMPLEX-DEVICE-DRIVER-SW-COMPONENT-TYPE",
    "ECU-ABSTRACTION-SW-COMPONENT-TYPE",
    "SENSOR-ACTUATOR-SW-COMPONENT-TYPE",
    "PARAMETER-SW-COMPONENT-TYPE",
    "NV-BLOCK-SW-COMPONENT-TYPE",
})


def _local(tag) -> str:
    if not isinstance(tag, str):
        return ""
    return tag.rsplit("}", 1)[-1]


def _child_text(elem: Optional[etree._Element], tag_name: str) -> Optional[str]:
    if elem is None:
        return None
    for ch in elem:
        if _local(ch.tag) == tag_name and ch.text:
            text = ch.text.strip()
            if text:
                return text
    return None


def _descendant_text(elem: Optional[etree._Element], tag_name: str) -> Optional[str]:
    if elem is None:
        return None
    for ch in elem.iter():
        if _local(ch.tag) == tag_name and ch.text:
            text = ch.text.strip()
            if text:
                return text
    return None


def _ar_leaf(path: Optional[str]) -> str:
    if not path:
        return ""
    return path.strip().rstrip("/").rsplit("/", 1)[-1]


def _norm_path(path: Optional[str]) -> str:
    return path.strip().rstrip("/") if path else ""


def _ar_path(elem: etree._Element) -> Optional[str]:
    sn = _child_text(elem, "SHORT-NAME")
    if not sn:
        return None
    segments = [sn]
    parent = elem.getparent()
    while parent is not None:
        anc_sn = _child_text(parent, "SHORT-NAME")
        if anc_sn:
            segments.append(anc_sn)
        parent = parent.getparent()
    return "/" + "/".join(reversed(segments))


@dataclass
class StructFieldDef:
    name: str
    type_ref: str = ""
    array_size: Optional[int] = None


@dataclass
class SwcDataType:
    """Indexed AUTOSAR IMPLEMENTATION-DATA-TYPE or APPLICATION-PRIMITIVE-DATA-TYPE descriptor."""

    ar_path: str
    short_name: str
    category: str  # "VALUE" | "TYPE_REFERENCE" | "ARRAY" | "STRUCTURE" | "UNION" | "DATA-REFERENCE" | "APPLICATION"
    base_type_ref: str = ""
    native_decl: str = ""
    impl_type_ref: str = ""
    array_size: Optional[int] = None
    element_type_ref: str = ""
    fields: List[StructFieldDef] = field(default_factory=list)
    compu_literals: List[Tuple[str, int]] = field(default_factory=list)
    source_file: str = ""


@dataclass
class DataElementDef:
    name: str
    ar_path: str
    type_ref: str = ""


@dataclass
class CsArgumentDef:
    name: str
    type_ref: str = ""
    direction: str = "IN"  # "IN" | "OUT" | "INOUT"


@dataclass
class CsOperationDef:
    name: str
    ar_path: str
    arguments: List[CsArgumentDef] = field(default_factory=list)
    has_errors: bool = False


@dataclass
class PortInterfaceData:
    ar_path: str
    short_name: str
    kind: str  # "SR" | "CS" | "MODE"
    is_service: bool = False
    data_elements: Dict[str, DataElementDef] = field(default_factory=dict)
    operations: Dict[str, CsOperationDef] = field(default_factory=dict)
    mode_group_ref: str = ""
    mode_group_name: str = ""


@dataclass
class SwcPortData:
    short_name: str
    ar_path: str
    direction: str  # "P" | "R"
    interface_ref: str = ""
    interface_kind: str = ""  # "SR" | "CS" | "MODE"
    is_service: bool = False
    init_values: Dict[str, str] = field(default_factory=dict)  # data_elem_name -> init_val str
    port_arg_values: List[Tuple[str, str]] = field(default_factory=list)  # (type_ref, literal_val)


@dataclass
class SwcAccessRef:
    port_ref: str
    target_ref: str  # DATA-ELEMENT / OPERATION / MODE ref
    access_kind: str  # "READ" | "WRITE" | "CALL_SYNC" | "CALL_ASYNC" | "MODE_SWITCH" | "MODE_ACCESS"


@dataclass
class SwcRunnableData:
    short_name: str
    ar_path: str
    symbol: str
    can_be_concurrent: bool = False
    reads: List[SwcAccessRef] = field(default_factory=list)
    writes: List[SwcAccessRef] = field(default_factory=list)
    calls: List[SwcAccessRef] = field(default_factory=list)
    mode_switches: List[SwcAccessRef] = field(default_factory=list)
    mode_accesses: List[SwcAccessRef] = field(default_factory=list)
    exclusive_area_refs: List[str] = field(default_factory=list)


@dataclass
class SwcEventData:
    short_name: str
    ar_path: str
    event_kind: str  # "TIMING-EVENT" | "INIT-EVENT" | "OPERATION-INVOKED-EVENT" | "DATA-RECEIVED-EVENT" | "SWC-MODE-SWITCH-EVENT" | ...
    runnable_ref: str = ""
    runnable_symbol: str = ""
    period_sec: Optional[float] = None
    port_ref: str = ""
    operation_ref: str = ""
    data_elem_ref: str = ""


@dataclass
class SwcTypeData:
    ar_path: str
    short_name: str
    category_tag: str
    is_service: bool
    ports: Dict[str, SwcPortData] = field(default_factory=dict)
    runnables: List[SwcRunnableData] = field(default_factory=list)
    events: List[SwcEventData] = field(default_factory=list)
    exclusive_areas: Dict[str, str] = field(default_factory=dict)  # ar_path -> short_name
    source_file: str = ""

    @property
    def runnables_by_path(self) -> Dict[str, SwcRunnableData]:
        return {r.ar_path: r for r in self.runnables}


@dataclass
class SwcPrototypeData:
    short_name: str
    ar_path: str
    type_ref: str = ""
    composition_path: str = ""


@dataclass
class AssemblyConnectorData:
    short_name: str
    provider_comp_ref: str
    provider_port_ref: str
    requester_comp_ref: str
    requester_port_ref: str
    provider_comp_name: str = ""
    provider_port_name: str = ""
    requester_comp_name: str = ""
    requester_port_name: str = ""


@dataclass
class DelegationConnectorData:
    short_name: str
    direction: str  # "P" | "R"
    inner_comp_ref: str
    inner_port_ref: str
    outer_port_ref: str
    inner_comp_name: str = ""
    inner_port_name: str = ""
    outer_port_name: str = ""


@dataclass
class SrSignalMappingData:
    context_comp_ref: str
    context_port_ref: str
    target_data_ref: str
    system_signal_ref: str
    resolved_comp_name: str = ""
    resolved_port_name: str = ""
    resolved_data_element_name: str = ""
    system_signal_name: str = ""


@dataclass
class ModeGroupData:
    ar_path: str
    short_name: str
    modes: List[str] = field(default_factory=list)
    initial_mode: str = ""


class SwcSystemIndex:
    """In-memory read-only index across SWCs, interfaces, data types, connectors, and signals."""

    def __init__(self) -> None:
        self.base_types_by_path: Dict[str, str] = {}
        self.types_by_path: Dict[str, SwcDataType] = {}
        self.types_by_name: Dict[str, SwcDataType] = {}
        self.app_to_impl_type: Dict[str, str] = {}
        self.constants_by_path: Dict[str, str] = {}
        self.compu_methods: Dict[str, List[Tuple[str, int]]] = {}
        self.mode_groups_by_path: Dict[str, ModeGroupData] = {}
        self.interfaces_by_path: Dict[str, PortInterfaceData] = {}
        self.swc_types_by_path: Dict[str, SwcTypeData] = {}
        self.swc_types_by_name: Dict[str, SwcTypeData] = {}
        self.prototypes_by_path: Dict[str, SwcPrototypeData] = {}
        self.prototypes_by_name: Dict[str, SwcPrototypeData] = {}
        self.assembly_connectors: List[AssemblyConnectorData] = []
        self.delegation_connectors: List[DelegationConnectorData] = []
        self.sr_mappings: List[SrSignalMappingData] = []
        self.isignal_to_sys_sig: Dict[str, str] = {}
        self.isig_mapping_to_isig: Dict[str, str] = {}
        self.isig_mapping_to_sys_sig: Dict[str, str] = {}
        self.sys_sig_to_isig_mappings: Dict[str, List[str]] = {}
        self.sr_mapping_by_comp_port: Dict[Tuple[str, str], SrSignalMappingData] = {}
        self.event_by_path: Dict[str, SwcEventData] = {}
        self.event_owner_by_path: Dict[str, SwcTypeData] = {}
        self.source_files: List[str] = []

    def __bool__(self) -> bool:
        return bool(self.swc_types_by_path or self.sr_mappings or self.assembly_connectors)

    @classmethod
    def load_directory(cls, system_dir: Path) -> "SwcSystemIndex":
        """Scan ``system_dir/**/*.arxml`` (excluding BSW ``*_ib_bswmd.arxml``) and finalize."""
        idx = cls()
        root_dir = Path(system_dir)
        if not root_dir.is_dir():
            return idx
        arxml_files = sorted(
            (
                p
                for p in root_dir.rglob("*")
                if p.is_file()
                and p.suffix.lower() == ".arxml"
                and not p.name.lower().endswith("_ib_bswmd.arxml")
            ),
            key=lambda p: p.relative_to(root_dir).as_posix(),
        )
        for p in arxml_files:
            idx.index_file(p, rel_source=p.relative_to(root_dir).as_posix())
        idx.finalize()
        return idx

    def index_file(self, arxml_path: Path, rel_source: Optional[str] = None) -> None:
        source_label = rel_source or Path(arxml_path).as_posix()
        parser = etree.XMLParser(resolve_entities=False, no_network=True)
        try:
            tree = etree.parse(str(arxml_path), parser)
        except (etree.XMLSyntaxError, OSError, ValueError) as exc:
            logger.debug("Skipping unreadable SWC/System ARXML %s: %s", arxml_path, exc)
            return

        root = tree.getroot()
        if root is None:
            return
        if source_label not in self.source_files:
            self.source_files.append(source_label)

        for elem in root.iter():
            tag = _local(elem.tag)
            if not tag:
                continue
            if tag == "SW-BASE-TYPE":
                self._parse_base_type(elem)
            elif tag == "IMPLEMENTATION-DATA-TYPE":
                self._parse_impl_data_type(elem, source_label)
            elif tag in ("APPLICATION-PRIMITIVE-DATA-TYPE", "APPLICATION-RECORD-DATA-TYPE", "APPLICATION-ARRAY-DATA-TYPE"):
                self._parse_app_data_type(elem, source_label)
            elif tag == "DATA-TYPE-MAP":
                app_ref = _norm_path(_descendant_text(elem, "APPLICATION-DATA-TYPE-REF"))
                imp_ref = _norm_path(_descendant_text(elem, "IMPLEMENTATION-DATA-TYPE-REF"))
                if app_ref and imp_ref:
                    self.app_to_impl_type[app_ref] = imp_ref
            elif tag == "CONSTANT-SPECIFICATION":
                self._parse_constant_spec(elem)
            elif tag == "COMPU-METHOD":
                self._parse_compu_method(elem)
            elif tag == "MODE-DECLARATION-GROUP":
                self._parse_mode_group(elem)
            elif tag == "SENDER-RECEIVER-INTERFACE":
                self._parse_sr_interface(elem)
            elif tag == "CLIENT-SERVER-INTERFACE":
                self._parse_cs_interface(elem)
            elif tag == "MODE-SWITCH-INTERFACE":
                self._parse_mode_interface(elem)
            elif tag in _SWC_TYPE_TAGS:
                self._parse_swc_type(elem, tag, source_label)
            elif tag == "COMPOSITION-SW-COMPONENT-TYPE":
                self._parse_composition(elem)
            elif tag in ("SENDER-RECEIVER-TO-SIGNAL-MAPPING", "SENDER-RECEIVER-TO-SIGNAL-GROUP-MAPPING"):
                self._parse_sr_mapping(elem)
            elif tag == "I-SIGNAL":
                p = _norm_path(_ar_path(elem))
                sys_ref = _norm_path(_descendant_text(elem, "SYSTEM-SIGNAL-REF"))
                if p and sys_ref:
                    self.isignal_to_sys_sig[p] = sys_ref
            elif tag == "I-SIGNAL-TO-I-PDU-MAPPING":
                p = _norm_path(_ar_path(elem))
                iref = _norm_path(_descendant_text(elem, "I-SIGNAL-REF") or _descendant_text(elem, "I-SIGNAL-GROUP-REF"))
                if p and iref:
                    self.isig_mapping_to_isig[p] = iref

    def finalize(self) -> None:
        # Resolve I-SIGNAL-TO-I-PDU-MAPPING -> SYSTEM-SIGNAL
        for mpath, isig_path in self.isig_mapping_to_isig.items():
            sys_sig = self.isignal_to_sys_sig.get(isig_path)
            if not sys_sig and isig_path:
                sys_sig = isig_path
            if sys_sig:
                self.isig_mapping_to_sys_sig[mpath] = sys_sig
                self.sys_sig_to_isig_mappings.setdefault(sys_sig, []).append(mpath)

        # Link delegation connectors (outer composition port -> inner SWC prototype + port)
        deleg_by_outer: Dict[str, DelegationConnectorData] = {}
        for dc in self.delegation_connectors:
            dc.inner_comp_name = _ar_leaf(dc.inner_comp_ref)
            dc.inner_port_name = _ar_leaf(dc.inner_port_ref)
            dc.outer_port_name = _ar_leaf(dc.outer_port_ref)
            if dc.outer_port_ref:
                deleg_by_outer[_norm_path(dc.outer_port_ref)] = dc

        # Resolve SR signal mappings
        self.sr_mapping_by_comp_port.clear()
        for m in self.sr_mappings:
            deleg = deleg_by_outer.get(_norm_path(m.context_port_ref))
            if deleg is not None:
                m.resolved_comp_name = deleg.inner_comp_name
                m.resolved_port_name = deleg.inner_port_name
            else:
                m.resolved_comp_name = _ar_leaf(m.context_comp_ref)
                m.resolved_port_name = _ar_leaf(m.context_port_ref)
            m.resolved_data_element_name = _ar_leaf(m.target_data_ref)
            m.system_signal_name = _ar_leaf(m.system_signal_ref)
            if m.resolved_comp_name and m.resolved_port_name:
                self.sr_mapping_by_comp_port[(m.resolved_comp_name, m.resolved_port_name)] = m

        # Populate assembly connector leaf names & resolve interface kinds/mode group names on SWC ports
        for ac in self.assembly_connectors:
            ac.provider_comp_name = _ar_leaf(ac.provider_comp_ref)
            ac.provider_port_name = _ar_leaf(ac.provider_port_ref)
            ac.requester_comp_name = _ar_leaf(ac.requester_comp_ref)
            ac.requester_port_name = _ar_leaf(ac.requester_port_ref)

        for iface in self.interfaces_by_path.values():
            if iface.kind == "MODE" and iface.mode_group_ref:
                mg = self.mode_groups_by_path.get(_norm_path(iface.mode_group_ref))
                if mg is not None:
                    iface.mode_group_name = mg.short_name

        for swc in self.swc_types_by_path.values():
            for port in swc.ports.values():
                iface = self.interfaces_by_path.get(_norm_path(port.interface_ref))
                if iface is not None:
                    port.interface_kind = iface.kind
                    port.is_service = iface.is_service
            run_map = swc.runnables_by_path
            for ev in swc.events:
                r = run_map.get(_norm_path(ev.runnable_ref))
                if r is not None:
                    ev.runnable_symbol = r.symbol or r.short_name
                elif ev.runnable_ref:
                    ev.runnable_symbol = _ar_leaf(ev.runnable_ref)

    def resolve_impl_type(self, type_ref: Optional[str]) -> Optional[SwcDataType]:
        ref = _norm_path(type_ref)
        if not ref:
            return None
        if ref in self.app_to_impl_type:
            ref = self.app_to_impl_type[ref]
        dt = self.types_by_path.get(ref)
        if dt is None:
            dt = self.types_by_name.get(_ar_leaf(ref))
        return dt

    def resolve_c_type_name(self, type_ref: Optional[str], fallback: str = "uint8") -> str:
        if not type_ref:
            return fallback
        dt = self.resolve_impl_type(type_ref)
        if dt is not None:
            if dt.category == "TYPE_REFERENCE" and dt.impl_type_ref:
                leaf_impl = _ar_leaf(dt.impl_type_ref)
                # Preserve named typedef unless pointing directly to a SwcDataType we generate
                return dt.short_name or leaf_impl or fallback
            if dt.category == "VALUE" and dt.native_decl:
                return dt.short_name or dt.native_decl
            return dt.short_name or fallback
        leaf = _ar_leaf(type_ref)
        return leaf or fallback

    def resolve_swc_type_for_instance(self, instance_ref: Optional[str], fallback_name: str = "") -> Optional[SwcTypeData]:
        norm = _norm_path(instance_ref)
        proto = self.prototypes_by_path.get(norm)
        if proto is None and norm:
            proto = self.prototypes_by_name.get(_ar_leaf(norm))
        if proto is None and fallback_name:
            proto = self.prototypes_by_name.get(fallback_name)
        if proto is not None and proto.type_ref:
            swc = self.swc_types_by_path.get(_norm_path(proto.type_ref))
            if swc is not None:
                return swc
            swc = self.swc_types_by_name.get(_ar_leaf(proto.type_ref))
            if swc is not None:
                return swc
        for cand in (_ar_leaf(norm), fallback_name):
            if cand and cand in self.swc_types_by_name:
                return self.swc_types_by_name[cand]
            base = cand[:-4] if cand.endswith("_swc") else cand
            if base and base in self.swc_types_by_name:
                return self.swc_types_by_name[base]
        return None

    def resolve_system_signal_for_com_ref(self, com_sys_ref: Optional[str]) -> str:
        """Resolve ComSystemTemplateSystemSignalRef (`/PDU/...` or `/Signal/...`) to normalized `/Signal/...`."""
        norm = _norm_path(com_sys_ref)
        if not norm:
            return ""
        if norm in self.isig_mapping_to_sys_sig:
            return self.isig_mapping_to_sys_sig[norm]
        if norm in self.isignal_to_sys_sig:
            return self.isignal_to_sys_sig[norm]
        return norm

    # ------------------------------------------------------------------
    # XML Parsers
    # ------------------------------------------------------------------

    def _parse_base_type(self, elem: etree._Element) -> None:
        p = _norm_path(_ar_path(elem))
        decl = _child_text(elem, "NATIVE-DECLARATION") or _child_text(elem, "SHORT-NAME")
        if p and decl:
            self.base_types_by_path[p] = decl

    def _parse_impl_data_type(self, elem: etree._Element, source_file: str) -> None:
        p = _norm_path(_ar_path(elem))
        sn = _child_text(elem, "SHORT-NAME")
        if not p or not sn:
            return
        cat = (_child_text(elem, "CATEGORY") or "VALUE").upper()
        base_ref = _norm_path(_descendant_text(elem, "BASE-TYPE-REF"))
        impl_ref = _norm_path(_descendant_text(elem, "IMPLEMENTATION-DATA-TYPE-REF"))
        native = self.base_types_by_path.get(base_ref, _ar_leaf(base_ref)) if base_ref else ""

        array_size: Optional[int] = None
        elem_type_ref = ""
        fields: List[StructFieldDef] = []
        sub_el = next((ch for ch in elem if _local(ch.tag) == "SUB-ELEMENTS"), None)
        if sub_el is not None:
            for item in sub_el:
                if _local(item.tag) != "IMPLEMENTATION-DATA-TYPE-ELEMENT":
                    continue
                fname = _child_text(item, "SHORT-NAME") or ""
                fref = _norm_path(_descendant_text(item, "IMPLEMENTATION-DATA-TYPE-REF") or _descendant_text(item, "BASE-TYPE-REF"))
                asize_raw = _descendant_text(item, "ARRAY-SIZE")
                asize: Optional[int] = None
                if asize_raw and asize_raw.isdigit():
                    asize = int(asize_raw)
                if cat == "ARRAY":
                    array_size = asize
                    elem_type_ref = fref
                elif fname:
                    fields.append(StructFieldDef(name=fname, type_ref=fref, array_size=asize))

        dt = SwcDataType(
            ar_path=p,
            short_name=sn,
            category=cat,
            base_type_ref=base_ref,
            native_decl=native,
            impl_type_ref=impl_ref,
            array_size=array_size,
            element_type_ref=elem_type_ref,
            fields=fields,
            source_file=source_file,
        )
        self.types_by_path[p] = dt
        self.types_by_name.setdefault(sn, dt)

    def _parse_app_data_type(self, elem: etree._Element, source_file: str) -> None:
        p = _norm_path(_ar_path(elem))
        sn = _child_text(elem, "SHORT-NAME")
        if not p or not sn:
            return
        dt = SwcDataType(ar_path=p, short_name=sn, category="APPLICATION", source_file=source_file)
        self.types_by_path[p] = dt
        self.types_by_name.setdefault(sn, dt)

    def _parse_constant_spec(self, elem: etree._Element) -> None:
        p = _norm_path(_ar_path(elem))
        if not p:
            return
        val = _descendant_text(elem, "VALUE")
        if val is not None:
            self.constants_by_path[p] = val

    def _parse_compu_method(self, elem: etree._Element) -> None:
        p = _norm_path(_ar_path(elem))
        if not p:
            return
        literals: List[Tuple[str, int]] = []
        for cs in elem.iter():
            if _local(cs.tag) == "COMPU-SCALE":
                sym = _child_text(cs, "SYMBOL") or _descendant_text(cs, "SHORT-LABEL")
                lim = _descendant_text(cs, "LOWER-LIMIT")
                if sym and lim is not None:
                    try:
                        literals.append((sym, int(lim, 0)))
                    except ValueError:
                        pass
        if literals:
            self.compu_methods[p] = literals

    def _parse_mode_group(self, elem: etree._Element) -> None:
        p = _norm_path(_ar_path(elem))
        sn = _child_text(elem, "SHORT-NAME")
        if not p or not sn:
            return
        modes: List[str] = []
        for md in elem.iter():
            if _local(md.tag) == "MODE-DECLARATION":
                msn = _child_text(md, "SHORT-NAME")
                if msn and msn not in modes:
                    modes.append(msn)
        init_ref = _child_text(elem, "INITIAL-MODE-REF")
        self.mode_groups_by_path[p] = ModeGroupData(
            ar_path=p, short_name=sn, modes=modes, initial_mode=_ar_leaf(init_ref)
        )

    def _parse_sr_interface(self, elem: etree._Element) -> None:
        p = _norm_path(_ar_path(elem))
        sn = _child_text(elem, "SHORT-NAME")
        if not p or not sn:
            return
        is_srv = (_child_text(elem, "IS-SERVICE") or "false").lower() == "true"
        elems: Dict[str, DataElementDef] = {}
        de_parent = next((ch for ch in elem if _local(ch.tag) == "DATA-ELEMENTS"), None)
        if de_parent is not None:
            for de in de_parent:
                if _local(de.tag) != "VARIABLE-DATA-PROTOTYPE":
                    continue
                dsn = _child_text(de, "SHORT-NAME")
                dp = _norm_path(_ar_path(de))
                tref = _norm_path(_child_text(de, "TYPE-TREF"))
                if dsn and dp:
                    elems[dsn] = DataElementDef(name=dsn, ar_path=dp, type_ref=tref)
        self.interfaces_by_path[p] = PortInterfaceData(
            ar_path=p, short_name=sn, kind="SR", is_service=is_srv, data_elements=elems
        )

    def _parse_cs_interface(self, elem: etree._Element) -> None:
        p = _norm_path(_ar_path(elem))
        sn = _child_text(elem, "SHORT-NAME")
        if not p or not sn:
            return
        is_srv = (_child_text(elem, "IS-SERVICE") or "false").lower() == "true"
        ops: Dict[str, CsOperationDef] = {}
        ops_el = next((ch for ch in elem if _local(ch.tag) == "OPERATIONS"), None)
        if ops_el is not None:
            for op in ops_el:
                if _local(op.tag) != "CLIENT-SERVER-OPERATION":
                    continue
                osn = _child_text(op, "SHORT-NAME")
                op_path = _norm_path(_ar_path(op))
                if not osn or not op_path:
                    continue
                args: List[CsArgumentDef] = []
                args_el = next((ch for ch in op if _local(ch.tag) == "ARGUMENTS"), None)
                if args_el is not None:
                    for arg in args_el:
                        if _local(arg.tag) != "ARGUMENT-DATA-PROTOTYPE":
                            continue
                        asn = _child_text(arg, "SHORT-NAME")
                        tref = _norm_path(_child_text(arg, "TYPE-TREF"))
                        d = (_child_text(arg, "DIRECTION") or "IN").upper()
                        if asn:
                            args.append(CsArgumentDef(name=asn, type_ref=tref, direction=d))
                has_err = next((ch for ch in op if _local(ch.tag) == "POSSIBLE-ERROR-REFS" and len(ch) > 0), None) is not None
                ops[osn] = CsOperationDef(name=osn, ar_path=op_path, arguments=args, has_errors=has_err)
        self.interfaces_by_path[p] = PortInterfaceData(
            ar_path=p, short_name=sn, kind="CS", is_service=is_srv, operations=ops
        )

    def _parse_mode_interface(self, elem: etree._Element) -> None:
        p = _norm_path(_ar_path(elem))
        sn = _child_text(elem, "SHORT-NAME")
        if not p or not sn:
            return
        is_srv = (_child_text(elem, "IS-SERVICE") or "false").lower() == "true"
        mg_ref = _norm_path(_descendant_text(elem, "MODE-GROUP-REF") or _descendant_text(elem, "TYPE-TREF"))
        self.interfaces_by_path[p] = PortInterfaceData(
            ar_path=p, short_name=sn, kind="MODE", is_service=is_srv, mode_group_ref=mg_ref
        )

    def _extract_init_value(self, com_spec: etree._Element) -> Optional[str]:
        init_el = next((ch for ch in com_spec if _local(ch.tag) == "INIT-VALUE"), None)
        if init_el is None:
            return None
        cref = _descendant_text(init_el, "CONSTANT-REF")
        if cref and _norm_path(cref) in self.constants_by_path:
            return self.constants_by_path[_norm_path(cref)]
        val = _descendant_text(init_el, "VALUE")
        return val

    def _parse_swc_type(self, elem: etree._Element, category_tag: str, source_file: str) -> None:
        p = _norm_path(_ar_path(elem))
        sn = _child_text(elem, "SHORT-NAME")
        if not p or not sn:
            return

        ports: Dict[str, SwcPortData] = {}
        ports_el = next((ch for ch in elem if _local(ch.tag) == "PORTS"), None)
        if ports_el is not None:
            for port_el in ports_el:
                ptag = _local(port_el.tag)
                if ptag not in ("P-PORT-PROTOTYPE", "R-PORT-PROTOTYPE"):
                    continue
                psn = _child_text(port_el, "SHORT-NAME")
                pp = _norm_path(_ar_path(port_el))
                if not psn or not pp:
                    continue
                direction = "P" if ptag == "P-PORT-PROTOTYPE" else "R"
                iref = _norm_path(
                    _child_text(port_el, "PROVIDED-INTERFACE-TREF")
                    or _child_text(port_el, "REQUIRED-INTERFACE-TREF")
                )
                init_vals: Dict[str, str] = {}
                for cs_tag in ("NONQUEUED-SENDER-COM-SPEC", "NONQUEUED-RECEIVER-COM-SPEC"):
                    for cs in port_el.iter():
                        if _local(cs.tag) == cs_tag:
                            de_ref = _child_text(cs, "DATA-ELEMENT-REF")
                            iv = self._extract_init_value(cs)
                            if de_ref and iv is not None:
                                init_vals[_ar_leaf(de_ref)] = iv
                ports[psn] = SwcPortData(
                    short_name=psn, ar_path=pp, direction=direction, interface_ref=iref, init_values=init_vals
                )

        runnables: List[SwcRunnableData] = []
        events: List[SwcEventData] = []
        eas: Dict[str, str] = {}

        ib = next(
            (ch for ch in elem.iter() if _local(ch.tag) == "SWC-INTERNAL-BEHAVIOR"),
            None,
        )
        if ib is not None:
            for ea in ib.iter():
                if _local(ea.tag) == "EXCLUSIVE-AREA":
                    ep = _norm_path(_ar_path(ea))
                    esn = _child_text(ea, "SHORT-NAME")
                    if ep and esn:
                        eas[ep] = esn

            # Port-defined argument values (used heavily by ServiceComponents such as ComM, NvM, Det)
            for pao in ib.iter():
                if _local(pao.tag) != "PORT-API-OPTION":
                    continue
                pref_leaf = _ar_leaf(_child_text(pao, "PORT-REF"))
                if pref_leaf and pref_leaf in ports:
                    for pav in pao.iter():
                        if _local(pav.tag) == "PORT-DEFINED-ARGUMENT-VALUE":
                            vt_ref = _norm_path(_child_text(pav, "VALUE-TYPE-TREF"))
                            v_text = _descendant_text(pav, "VALUE")
                            if v_text is not None:
                                ports[pref_leaf].port_arg_values.append((vt_ref, v_text))

            runs_el = next((ch for ch in ib if _local(ch.tag) == "RUNNABLES"), None)
            if runs_el is not None:
                for rel in runs_el:
                    if _local(rel.tag) != "RUNNABLE-ENTITY":
                        continue
                    rsn = _child_text(rel, "SHORT-NAME")
                    rp = _norm_path(_ar_path(rel))
                    if not rsn or not rp:
                        continue
                    sym = _child_text(rel, "SYMBOL") or rsn
                    conc = (_child_text(rel, "CAN-BE-INVOKED-CONCURRENTLY") or "false").lower() == "true"

                    def _collect_var_access(container_tags: Tuple[str, ...], kind_lbl: str) -> List[SwcAccessRef]:
                        out: List[SwcAccessRef] = []
                        for ctag in container_tags:
                            c_el = next((ch for ch in rel if _local(ch.tag) == ctag), None)
                            if c_el is None:
                                continue
                            for va in c_el:
                                pr = _norm_path(_descendant_text(va, "PORT-PROTOTYPE-REF"))
                                dr = _norm_path(_descendant_text(va, "TARGET-DATA-PROTOTYPE-REF"))
                                if pr and dr:
                                    out.append(SwcAccessRef(port_ref=pr, target_ref=dr, access_kind=kind_lbl))
                        return out

                    reads = _collect_var_access(("DATA-READ-ACCESSS", "DATA-RECEIVE-POINT-BY-ARGUMENTS", "DATA-RECEIVE-POINT-BY-VALUES"), "READ")
                    writes = _collect_var_access(("DATA-WRITE-ACCESSS", "DATA-SEND-POINTS"), "WRITE")

                    calls: List[SwcAccessRef] = []
                    scp_el = next((ch for ch in rel if _local(ch.tag) == "SERVER-CALL-POINTS"), None)
                    if scp_el is not None:
                        for cp in scp_el:
                            ct = _local(cp.tag)
                            if ct not in ("SYNCHRONOUS-SERVER-CALL-POINT", "ASYNCHRONOUS-SERVER-CALL-POINT"):
                                continue
                            pr = _norm_path(_descendant_text(cp, "CONTEXT-R-PORT-REF"))
                            opr = _norm_path(_descendant_text(cp, "TARGET-REQUIRED-OPERATION-REF"))
                            if pr and opr:
                                ck = "CALL_SYNC" if "SYNCHRONOUS" in ct and not ct.startswith("A") else "CALL_ASYNC"
                                calls.append(SwcAccessRef(port_ref=pr, target_ref=opr, access_kind=ck))

                    mswitches: List[SwcAccessRef] = []
                    ms_el = next((ch for ch in rel if _local(ch.tag) == "MODE-SWITCH-POINTS"), None)
                    if ms_el is not None:
                        for mp in ms_el:
                            pr = _norm_path(_descendant_text(mp, "CONTEXT-P-PORT-REF"))
                            mr = _norm_path(_descendant_text(mp, "MODE-GROUP-DECLARATION-REF"))
                            if pr:
                                mswitches.append(SwcAccessRef(port_ref=pr, target_ref=mr, access_kind="MODE_SWITCH"))

                    maccesses: List[SwcAccessRef] = []
                    ma_el = next((ch for ch in rel if _local(ch.tag) == "MODE-ACCESS-POINTS"), None)
                    if ma_el is not None:
                        for mp in ma_el:
                            pr = _norm_path(_descendant_text(mp, "CONTEXT-R-PORT-REF") or _descendant_text(mp, "CONTEXT-P-PORT-REF"))
                            mr = _norm_path(_descendant_text(mp, "MODE-GROUP-DECLARATION-REF"))
                            if pr:
                                maccesses.append(SwcAccessRef(port_ref=pr, target_ref=mr, access_kind="MODE_ACCESS"))

                    ea_refs: List[str] = []
                    ce_el = next((ch for ch in rel if _local(ch.tag) == "CAN-ENTER-EXCLUSIVE-AREA-REFS"), None)
                    if ce_el is not None:
                        for r in ce_el:
                            if r.text and r.text.strip():
                                ea_refs.append(_norm_path(r.text))

                    runnables.append(
                        SwcRunnableData(
                            short_name=rsn,
                            ar_path=rp,
                            symbol=sym,
                            can_be_concurrent=conc,
                            reads=reads,
                            writes=writes,
                            calls=calls,
                            mode_switches=mswitches,
                            mode_accesses=maccesses,
                            exclusive_area_refs=ea_refs,
                        )
                    )

            ev_el = next((ch for ch in ib if _local(ch.tag) == "EVENTS"), None)
            if ev_el is not None:
                for ev in ev_el:
                    ev_sn = _child_text(ev, "SHORT-NAME")
                    ev_p = _norm_path(_ar_path(ev))
                    if not ev_sn or not ev_p:
                        continue
                    rref = _norm_path(_child_text(ev, "START-ON-EVENT-REF"))
                    p_raw = _child_text(ev, "PERIOD")
                    period: Optional[float] = None
                    if p_raw is not None:
                        try:
                            period = float(p_raw)
                        except ValueError:
                            period = None
                    port_ref = _norm_path(
                        _descendant_text(ev, "CONTEXT-P-PORT-REF")
                        or _descendant_text(ev, "CONTEXT-R-PORT-REF")
                    )
                    op_ref = _norm_path(_descendant_text(ev, "TARGET-PROVIDED-OPERATION-REF"))
                    data_ref = _norm_path(_descendant_text(ev, "TARGET-DATA-ELEMENT-REF"))
                    ev_obj = SwcEventData(
                        short_name=ev_sn,
                        ar_path=ev_p,
                        event_kind=_local(ev.tag),
                        runnable_ref=rref,
                        period_sec=period,
                        port_ref=port_ref,
                        operation_ref=op_ref,
                        data_elem_ref=data_ref,
                    )
                    events.append(ev_obj)
                    self.event_by_path[ev_p] = ev_obj

        swc = SwcTypeData(
            ar_path=p,
            short_name=sn,
            category_tag=category_tag,
            is_service=(category_tag == "SERVICE-SW-COMPONENT-TYPE"),
            ports=ports,
            runnables=runnables,
            events=events,
            exclusive_areas=eas,
            source_file=source_file,
        )
        self.swc_types_by_path[p] = swc
        self.swc_types_by_name.setdefault(sn, swc)
        for ev in events:
            self.event_owner_by_path[ev.ar_path] = swc

    def _parse_composition(self, elem: etree._Element) -> None:
        comp_path = _norm_path(_ar_path(elem)) or ""
        comps_el = next((ch for ch in elem if _local(ch.tag) == "COMPONENTS"), None)
        if comps_el is not None:
            for ch in comps_el:
                if _local(ch.tag) != "SW-COMPONENT-PROTOTYPE":
                    continue
                psn = _child_text(ch, "SHORT-NAME")
                pp = _norm_path(_ar_path(ch))
                tref = _norm_path(_child_text(ch, "TYPE-TREF"))
                if psn and pp:
                    proto = SwcPrototypeData(
                        short_name=psn, ar_path=pp, type_ref=tref, composition_path=comp_path
                    )
                    self.prototypes_by_path[pp] = proto
                    self.prototypes_by_name.setdefault(psn, proto)

        conns_el = next((ch for ch in elem if _local(ch.tag) == "CONNECTORS"), None)
        if conns_el is None:
            return
        for ch in conns_el:
            ctag = _local(ch.tag)
            csn = _child_text(ch, "SHORT-NAME") or ""
            if ctag == "ASSEMBLY-SW-CONNECTOR":
                prov_el = next((x for x in ch if _local(x.tag) == "PROVIDER-IREF"), None)
                req_el = next((x for x in ch if _local(x.tag) == "REQUESTER-IREF"), None)
                p_comp = _norm_path(_descendant_text(prov_el, "CONTEXT-COMPONENT-REF"))
                p_port = _norm_path(_descendant_text(prov_el, "TARGET-P-PORT-REF"))
                r_comp = _norm_path(_descendant_text(req_el, "CONTEXT-COMPONENT-REF"))
                r_port = _norm_path(_descendant_text(req_el, "TARGET-R-PORT-REF"))
                if p_port and r_port:
                    self.assembly_connectors.append(
                        AssemblyConnectorData(
                            short_name=csn,
                            provider_comp_ref=p_comp,
                            provider_port_ref=p_port,
                            requester_comp_ref=r_comp,
                            requester_port_ref=r_port,
                        )
                    )
            elif ctag == "DELEGATION-SW-CONNECTOR":
                in_el = next((x for x in ch if _local(x.tag) == "INNER-PORT-IREF"), None)
                in_comp = _norm_path(_descendant_text(in_el, "CONTEXT-COMPONENT-REF"))
                in_p = _norm_path(_descendant_text(in_el, "TARGET-P-PORT-REF"))
                in_r = _norm_path(_descendant_text(in_el, "TARGET-R-PORT-REF"))
                out_p = _norm_path(_child_text(ch, "OUTER-PORT-REF"))
                direction = "P" if in_p else "R"
                in_port = in_p or in_r
                if in_comp and in_port and out_p:
                    self.delegation_connectors.append(
                        DelegationConnectorData(
                            short_name=csn,
                            direction=direction,
                            inner_comp_ref=in_comp,
                            inner_port_ref=in_port,
                            outer_port_ref=out_p,
                        )
                    )

    def _parse_sr_mapping(self, elem: etree._Element) -> None:
        comp_ref = _norm_path(_descendant_text(elem, "CONTEXT-COMPONENT-REF"))
        port_ref = _norm_path(_descendant_text(elem, "CONTEXT-PORT-REF"))
        data_ref = _norm_path(_descendant_text(elem, "TARGET-DATA-PROTOTYPE-REF"))
        sys_ref = _norm_path(
            _child_text(elem, "SYSTEM-SIGNAL-REF") or _child_text(elem, "SYSTEM-SIGNAL-GROUP-REF")
        )
        if port_ref and sys_ref:
            self.sr_mappings.append(
                SrSignalMappingData(
                    context_comp_ref=comp_ref,
                    context_port_ref=port_ref,
                    target_data_ref=data_ref,
                    system_signal_ref=sys_ref,
                )
            )

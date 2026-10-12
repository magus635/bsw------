"""templates/Os/Os_Arti.arxml rendered with a synthetic THA6-style Os configuration.

Checks the openspec change add-os-arti-description-template (phase 1):
schema validity, conformance to definitions/Arti/Arti_ParamDef.arxml, ID rules,
per-core description, OsUseArti switch, and reference resolution in a workspace.
"""
import shutil
from pathlib import Path

import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser
from autosar_configurator.core.workspace_manager import WorkspaceProject
from autosar_configurator.generator.generator import CodeGenerator

from .os_arti_fixture import ISRS, TASKS, build_os_config

etree = pytest.importorskip("lxml.etree")

ROOT = Path(__file__).resolve().parents[2]
TEMPLATE = ROOT / "templates" / "Os" / "Os_Arti.arxml"
ARTI_DEF = ROOT / "definitions" / "Arti" / "Arti_ParamDef.arxml"
APP_COMMON = ROOT / "doc" / "ARTI" / "Os_AppCommon.m"
XSD = ROOT / "doc" / "ARTI" / "AUTOSAR_00047.xsd"
NS = {"a": "http://autosar.org/schema/r4.0"}
A = "{http://autosar.org/schema/r4.0}"


def _render(tmp_path, use_arti=True, n_cores=2, logical_ids=None, with_macros=True):
    module_def, mgr = build_os_config(use_arti=use_arti, n_cores=n_cores, logical_ids=logical_ids)
    tpl_dir = tmp_path / "tpl" / "Os"
    tpl_dir.mkdir(parents=True)
    shutil.copy(TEMPLATE, tpl_dir / TEMPLATE.name)
    if with_macros:
        shutil.copy(APP_COMMON, tpl_dir / APP_COMMON.name)  # the template includes the Os plugin's macros
    gen = CodeGenerator(module_def, mgr.configuration, project_template_dir=tmp_path / "tpl")
    assert gen.generate_all(tmp_path / "out") is True
    out = tmp_path / "out" / "Os" / "Os_Arti.arxml"
    return out, etree.parse(str(out)).getroot(), mgr


@pytest.fixture
def rendered(tmp_path):
    return _render(tmp_path)


def _sn(el):
    return el.findtext("a:SHORT-NAME", namespaces=NS)


def _def(el):
    return el.findtext("a:DEFINITION-REF", namespaces=NS)


def _containers(root, def_suffix):
    return [c for c in root.iter(A + "ECUC-CONTAINER-VALUE") if _def(c).endswith("/" + def_suffix)]


def _param(container, name):
    for p in container.xpath("a:PARAMETER-VALUES/*", namespaces=NS):
        if _def(p).endswith("/" + name):
            return p.findtext("a:VALUE", namespaces=NS)
    return None


def _ref(container, name):
    for r in container.xpath("a:REFERENCE-VALUES/*", namespaces=NS):
        if _def(r).endswith("/" + name):
            return r.findtext("a:VALUE-REF", namespaces=NS)
    return None


def test_renders_without_unimplemented_functions(tmp_path, caplog):
    """Portability guard: every function the template uses exists in the configurator's engine."""
    with caplog.at_level("WARNING"):
        _render(tmp_path)
    assert not [r for r in caplog.records if "unimplemented" in r.getMessage()]


# --------------------------------------------------------------------------- schema / definition

@pytest.mark.skipif(not XSD.exists(), reason="AUTOSAR_00047.xsd not present")
@pytest.mark.parametrize("use_arti", [True, False])
def test_output_is_schema_valid(tmp_path, use_arti):
    _, root, _ = _render(tmp_path, use_arti=use_arti)
    schema = etree.XMLSchema(etree.parse(str(XSD)))
    assert schema.validate(root), schema.error_log


def _def_index():
    """definition path -> (element tag, element) for every DEF in the Arti ParamDef"""
    tree = etree.parse(str(ARTI_DEF))
    index = {}

    def walk(el, path):
        for child in el:
            if not isinstance(child.tag, str):
                continue
            name = child.findtext("a:SHORT-NAME", namespaces=NS)
            tag = etree.QName(child).localname
            if name and (tag.endswith("-DEF") or tag == "ECUC-MODULE-DEF"):
                p = f"{path}/{name}"
                index[p] = (tag, child)
                walk(child, p)
            else:
                walk(child, path)

    walk(tree.getroot(), "/AUTOSAR/EcucDefs")
    return {k: v for k, v in index.items() if k.startswith("/AUTOSAR/EcucDefs/Arti")}


def _mult(def_el):
    lo = int(def_el.findtext("a:LOWER-MULTIPLICITY", default="0", namespaces=NS))
    inf = def_el.findtext("a:UPPER-MULTIPLICITY-INFINITE", namespaces=NS) == "true"
    up = None if inf else int(def_el.findtext("a:UPPER-MULTIPLICITY", default="1", namespaces=NS))
    return lo, up


def test_output_conforms_to_arti_definition(rendered):
    """Every DEFINITION-REF exists with the right kind; multiplicities hold; mandatory items are present."""
    _, root, _ = rendered
    defs = _def_index()
    problems = []
    for c in root.iter(A + "ECUC-CONTAINER-VALUE"):
        cdef = _def(c)
        if cdef not in defs:
            problems.append(f"unknown container def {cdef}")
            continue
        cdef_el = defs[cdef][1]
        used = {}
        for item in c.xpath("a:PARAMETER-VALUES/* | a:REFERENCE-VALUES/*", namespaces=NS):
            d = item.find("a:DEFINITION-REF", NS)
            if d.text not in defs:
                problems.append(f"{_sn(c)}: unknown def {d.text}")
                continue
            if d.get("DEST") != defs[d.text][0]:
                problems.append(f"{_sn(c)}: {d.text} DEST {d.get('DEST')} != {defs[d.text][0]}")
            used[d.text] = used.get(d.text, 0) + 1
        for sub in c.xpath("a:SUB-CONTAINERS/a:ECUC-CONTAINER-VALUE", namespaces=NS):
            used[_def(sub)] = used.get(_def(sub), 0) + 1
        # every direct child definition of this container: check multiplicity
        for path, (tag, el) in defs.items():
            if path.rsplit("/", 1)[0] != cdef or tag == "ECUC-ENUMERATION-LITERAL-DEF":
                continue
            lo, up = _mult(el)
            n = used.get(path, 0)
            if n < lo:
                problems.append(f"{_sn(c)}: missing mandatory {path.rsplit('/', 1)[1]}")
            if up is not None and n > up:
                problems.append(f"{_sn(c)}: {path.rsplit('/', 1)[1]} x{n} > {up}")
    assert not problems, "\n".join(problems)


def test_internal_and_os_references_point_to_existing_containers_of_the_right_type(rendered):
    _, root, mgr = rendered
    defs = _def_index()
    arti = {}

    def collect(el, path):
        for c in el.xpath("a:CONTAINERS/a:ECUC-CONTAINER-VALUE | a:SUB-CONTAINERS/a:ECUC-CONTAINER-VALUE",
                          namespaces=NS):
            p = f"{path}/{_sn(c)}"
            arti[p] = _def(c)
            collect(c, p)

    collect(root.find(".//a:ECUC-MODULE-CONFIGURATION-VALUES", NS), "/Arti/Arti")
    os_names = {c.short_name: c.definition_ref for c in mgr.configuration.containers}

    problems = []
    for r in root.iter(A + "ECUC-REFERENCE-VALUE"):
        ref_def = defs[r.findtext("a:DEFINITION-REF", namespaces=NS)][1]
        allowed = [d.text for d in ref_def.xpath("a:DESTINATION-REF | a:DESTINATION-REFS/a:DESTINATION-REF",
                                                 namespaces=NS)]
        target = r.findtext("a:VALUE-REF", namespaces=NS)
        if target.startswith("/Arti/Arti/"):
            target_def = arti.get(target)
        elif target.startswith("/Os/Os/"):
            target_def = os_names.get(target.rsplit("/", 1)[1])
        elif target.startswith("/EcuC/"):
            target_def = "/AUTOSAR/EcucDefs/EcuC/EcucHardware/EcucCoreDefinition"  # EcuC not in this fixture
        else:
            target_def = None
        if target_def is None:
            problems.append(f"dangling {target}")
        elif target_def not in allowed:
            problems.append(f"{target}: {target_def} not in {allowed}")
    assert not problems, "\n".join(problems)


# --------------------------------------------------------------------------- content

def test_task_and_isr_ids_follow_the_orti_rule(rendered):
    """A2: TaskType = OsTask/@index, ISRType = OsIsr/@index; TypeMap inputs agree."""
    _, root, _ = rendered
    tasks = {_sn(c): int(_param(c, "ArtiOsTaskInstanceId")) for c in _containers(root, "ArtiOsTaskInstance")}
    assert tasks == {name: i for i, (name, *_r) in enumerate(TASKS)}
    isrs = {_sn(c): int(_param(c, "ArtiOsIsrInstanceId")) for c in _containers(root, "ArtiOsIsrInstance")}
    assert isrs == {name: i for i, (name, *_r) in enumerate(ISRS)}

    tm = {_sn(t): t for t in _containers(root, "ArtiParameterTypeMap")}
    task_pairs = {_sn(p): int(_param(p, "ArtiParameterTypeMapPairInput"))
                  for p in tm["TM_TaskId"].xpath("a:SUB-CONTAINERS/*", namespaces=NS)}
    assert task_pairs == {**tasks, "NO_TASK": len(TASKS)}
    isr2_pairs = {_sn(p): int(_param(p, "ArtiParameterTypeMapPairInput"))
                  for p in tm["TM_Isr2Id"].xpath("a:SUB-CONTAINERS/*", namespaces=NS)}
    # CATEGORY_1 ISRs are not in the ISR2 map; NO_ISR = INVALID_ISR = count of all ISRs (kernel Os_isr_Cfg.h)
    assert isr2_pairs == {"Isr_Timer0": 0, "Isr_Timer1": 2, "NO_ISR": len(ISRS)}


def test_category1_isr_has_no_stack_or_context(rendered):
    """The kernel only defines <name>_stack / <name>_ContextInfo for Tasks and CATEGORY_2 ISRs."""
    _, root, _ = rendered
    names = {_sn(c) for c in root.iter(A + "ECUC-CONTAINER-VALUE")}
    for name, cat, *_ in ISRS:
        has = {f"{name}_stack", f"{name}_ContextInfo", f"E_{name}_StackBase", f"E_{name}_Context"} & names
        assert bool(has) == (cat == "CATEGORY_2"), name


def test_type_map_inputs_fit_16_bit(rendered):
    """ECUC_Arti_00024: inputs used by hooks must be 0..65535; keep the maps within it.

    TM_LockedByResource and TM_ObjectOwner are exempt: their "none" input is 0xFFFFFFFF as in ORTI, and no
    hook uses them.
    """
    _, root, _ = rendered
    for tm in _containers(root, "ArtiParameterTypeMap"):
        if _sn(tm) in ("TM_LockedByResource", "TM_ObjectOwner"):
            continue
        for p in tm.xpath("a:SUB-CONTAINERS/*", namespaces=NS):
            value = _param(p, "ArtiParameterTypeMapPairInput")
            if value is not None:
                assert 0 <= int(value) <= 65535, (_sn(tm), _sn(p))


@pytest.mark.parametrize("n_cores", [1, 2, 4])
def test_one_core_instance_per_os_core(tmp_path, n_cores):
    _, root, _ = _render(tmp_path, n_cores=n_cores)
    cores = _containers(root, "ArtiHardwareCoreInstance")
    assert [int(_param(c, "ArtiHardwareCoreInstanceCoreId")) for c in cores] == list(range(n_cores))
    exprs = {_sn(e): _param(e, "ArtiExpressionString") for e in _containers(root, "ArtiExpression")}
    for i, core in enumerate(cores):
        assert _ref(core, "ArtiHardwareCoreInstanceCurrentTaskRef") == f"/Arti/Arti/ArtiValues/IP_Core{i}_RunningTask"
        assert exprs[f"E_Core{i}_RunningTask"] == f"Os_OrtiRunningData[{i}].RunningTaskType"
        assert _ref(core, "ArtiHardwareCoreInstanceEcucCoreRef") == f"/EcuC/EcuC/EcucHardware/EcucCoreDefinition_{i}"


def test_core_index_follows_logical_core_id(tmp_path):
    """Os_OrtiRunningData[] is indexed by the logical core id (EcucCoreId), not OsPhysicalCoreId."""
    _, root, _ = _render(tmp_path, logical_ids={0: 3, 1: 2})
    cores = _containers(root, "ArtiHardwareCoreInstance")
    assert sorted(int(_param(c, "ArtiHardwareCoreInstanceCoreId")) for c in cores) == [2, 3]
    exprs = {_sn(e): _param(e, "ArtiExpressionString") for e in _containers(root, "ArtiExpression")}
    assert exprs["E_Core3_RunningTask"] == "Os_OrtiRunningData[3].RunningTaskType"
    assert exprs["E_Core2_RunningIsr"] == "Os_OrtiRunningData[2].RunningISRType"


def test_current_application_is_read_from_the_kernel(rendered):
    """A3: per-core Os_AppRunningTimeData_Core<N>.Current_ApplicationID, decoded to the application name."""
    _, root, _ = rendered
    exprs = {_sn(e): _param(e, "ArtiExpressionString") for e in _containers(root, "ArtiExpression")}
    cores = _containers(root, "ArtiHardwareCoreInstance")
    for i, core in enumerate(cores):
        assert exprs[f"E_Core{i}_CurrentApplication"] == f"Os_AppRunningTimeData_Core{i}.Current_ApplicationID"
        assert _ref(core, "ArtiHardwareCoreInstanceCurrentApplicationRef") ==             f"/Arti/Arti/ArtiValues/IP_Core{i}_CurrentApplication"
    tm = {_sn(t): t for t in _containers(root, "ArtiParameterTypeMap")}
    pairs = {_sn(p): (int(_param(p, "ArtiParameterTypeMapPairInput")), _param(p, "ArtiParameterTypeMapPairOutput"))
             for p in tm["TM_ApplicationId"].xpath("a:SUB-CONTAINERS/*", namespaces=NS)}
    assert pairs == {"App_Core0": (0, "App_Core0"), "App_Core1": (1, "App_Core1"),
                     "NO_APPLICATION": (2, "NO_APPLICATION")}


def test_address_expressions_are_xml_escaped_once(rendered):
    """'&' must reach the debugger as '&', i.e. be written exactly once as '&amp;' in the file."""
    out, root, _ = rendered
    exprs = {_sn(e): _param(e, "ArtiExpressionString") for e in _containers(root, "ArtiExpression")}
    assert exprs["E_Task_A_StackBase"] == "&Task_A_stack[0]"
    assert exprs["E_Isr_Timer0_Context"] == "&Isr_Timer0_ContextInfo"
    assert "&amp;amp;" not in out.read_text(encoding="utf-8")


def test_standard_task_state_model(rendered):
    _, root, _ = rendered
    (states,) = _containers(root, "ArtiStates")
    assert _param(states, "ArtiStatesTaskEnhanced") == "false"


def test_arti_disabled_emits_empty_document(tmp_path):
    _, root, _ = _render(tmp_path, use_arti=False)
    assert etree.QName(root).localname == "AUTOSAR"
    assert root.find(".//a:ECUC-MODULE-CONFIGURATION-VALUES", NS) is None


# --------------------------------------------------------------------------- tool import

def test_output_imports_into_workspace_and_references_resolve(rendered):
    """Task 3.4: load as the Arti module next to Os; every reference resolves."""
    out, _, os_mgr = rendered
    arti_def = EcucDefParser().parse_module_def_file(ARTI_DEF)
    arti_mgr = ConfigurationManager(arti_def)
    arti_mgr.load_configuration(out)

    project = WorkspaceProject("arti_check")
    project.module_managers = {"Os": os_mgr, "Arti": arti_mgr}
    resolved, errors = project.resolve_all_references()
    unresolved = [e for e in project.get_all_resolution_errors() if "/EcuC/" not in str(e)]
    assert resolved > 0
    assert not unresolved, "\n".join(str(e) for e in unresolved[:20])


# --------------------------------------------------------------------------- ORTI parity (generic components)

def _pairs(root, tm_name):
    """{pair short name: (input, output string, output ref, input expression ref)} of one type map."""
    (tm,) = [t for t in _containers(root, "ArtiParameterTypeMap") if _sn(t) == tm_name]
    out = {}
    for p in tm.xpath("a:SUB-CONTAINERS/*", namespaces=NS):
        inp = _param(p, "ArtiParameterTypeMapPairInput")
        out[_sn(p)] = (int(inp) if inp is not None else None,
                       _param(p, "ArtiParameterTypeMapPairOutput"),
                       _ref(p, "ArtiParameterTypeMapPairOutputRef"),
                       _ref(p, "ArtiParameterTypeMapPairInputExpressionRef"))
    return out


def test_generic_type_maps_follow_the_orti_enumerations(rendered):
    _, root, _ = rendered
    assert {k: v[:2] for k, v in _pairs(root, "TM_TaskType").items()} == {
        "BASIC": (0, "BASIC"), "EXTENDED": (1, "EXTENDED")}
    assert {v[0]: v[1] for v in _pairs(root, "TM_AlarmAction").values()} == {
        0: "ALARM_ACTIVATETASK", 1: "ALARM_SETEVENT", 2: "ALARM_CALLBACK", 3: "ALARM_INCREMENTCOUNTER"}
    assert {v[0]: v[1] for v in _pairs(root, "TM_SpinlockLockMethod").values()} == {
        0: "LOCK_ALL_INTERRUPTS", 1: "LOCK_CAT2_INTERRUPTS", 2: "LOCK_NOTHING", 3: "LOCK_WITH_RES_SCHEDULER"}
    st = _pairs(root, "TM_ScheduleTableState")
    assert [st[k][0] for k in ("STOPPED", "NEXT", "WAITING", "RUNNING", "RUNNING_AND_SYNCHRONOUS")] == [0, 1, 2, 3, 4]
    assert st["RUNNING"][2] == "/Arti/Arti/ArtiValues/ArtiStates/S_SchedTableRunning"
    sp = _pairs(root, "TM_SpinlockState")
    assert (sp["UNLOCKED"][0], sp["LOCKED"][0]) == (0, 1)
    assert sp["LOCKED"][2] == "/Arti/Arti/ArtiValues/ArtiStates/S_SpinlockLocked"
    nxt = _pairs(root, "TM_ScheduleTableNext")
    assert nxt["Sch_Main"][:2] == (0, "Sch_Main") and nxt["NONE"][:2] == (255, "-")


def test_lock_type_maps_decode_resource_addresses(rendered):
    """ORTI LOCKED: the value is &Os_LockConfig_<resource>; 'none' is 0 for tasks/ISRs, 0xFFFFFFFF otherwise."""
    _, root, _ = rendered
    exprs = {_sn(e): _param(e, "ArtiExpressionString") for e in _containers(root, "ArtiExpression")}
    assert exprs["E_LockAddr_Res_Shared"] == "&Os_LockConfig_Res_Shared"
    for tm, none in (("TM_LockedByTask", 0), ("TM_LockedByResource", 0xFFFFFFFF)):
        pairs = _pairs(root, tm)
        assert pairs["Res_Shared"][1:] == ("Res_Shared", None, "/Arti/Arti/ArtiValues/E_LockAddr_Res_Shared")
        assert pairs["NONE"][:2] == (none, "-")


def test_every_os_object_has_one_generic_instance(rendered):
    _, root, _ = rendered
    instances = {_param(c, "ArtiGenericComponentInstanceName") for c in _containers(root, "ArtiGenericComponentInstance")}
    expected = {t[0] for t in TASKS} | {i[0] for i in ISRS} | {"Alarm_10ms", "Res_Shared", "Event_Wake",
                                                                 "Sch_Main", "Spin_Shared", "OsConfig"}
    assert instances == expected


def test_owner_object_numbers_count_every_object_of_the_previous_application(rendered):
    """App_Core0 holds 2 tasks, 2 ISRs, a counter, an alarm, a schedule table and 3 hook objects (kernel
    application: OsErrorHook + OsStartupHook + 1) = 10 objects, so App_Core1 starts at 10. CATEGORY_1 ISRs take
    a number but get no name."""
    _, root, _ = rendered
    owner = {v[1]: v[0] for v in _pairs(root, "TM_ObjectOwner").values()}
    assert owner == {"Task Task_A": 0, "Task Task_B": 1, "ISR Isr_Timer0": 2,
                     "Task Task_C": 10, "ISR Isr_Timer1": 12, "-": 0xFFFFFFFF}


def test_owner_expressions_and_generic_parameters(rendered):
    _, root, _ = rendered
    exprs = {_sn(e): _param(e, "ArtiExpressionString") for e in _containers(root, "ArtiExpression")}
    assert exprs["E_Res_Shared_RESOURCE_OWNER"] == "Os_Res_Shared_RunningData.OwnerObjectID"
    assert exprs["E_Spin_Shared_SPINLOCK_OWNER"] == "Os_Spin_Shared_RunningData.OwnerObjectID"


def test_owner_type_map_is_left_out_when_the_os_macros_are_missing(tmp_path):
    """Without Os_AppCommon.m the include is silent; wrong object numbers must not be emitted."""
    _, root, _ = _render(tmp_path, with_macros=False)
    assert not [t for t in _containers(root, "ArtiParameterTypeMap") if _sn(t) == "TM_ObjectOwner"]
    owner_params = [c for c in _containers(root, "ArtiGenericComponentClassParameter")
                    if _param(c, "ArtiGenericComponentClassParameterName") in ("RESOURCE_OWNER", "SPINLOCK_OWNER")]
    assert owner_params and all(_ref(c, "ArtiGenericComponentClassParameterTypeMapRef") is None for c in owner_params)

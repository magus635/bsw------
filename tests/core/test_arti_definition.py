"""Tests for definitions/Arti/Arti_ParamDef.arxml (AUTOSAR ARTI module definition).

Expected values come from SWS ARTI R24-11 chapter 10 and SWS OS R21-11 section 10.4.
"""
from pathlib import Path

import pytest

from autosar_configurator.core.config_manager import ConfigurationManager
from autosar_configurator.core.parser.ecuc_def_parser import EcucDefParser

ROOT = Path(__file__).resolve().parents[2]
DEF_FILE = ROOT / "definitions" / "Arti" / "Arti_ParamDef.arxml"
XSD_FILE = ROOT / "doc" / "ARTI" / "AUTOSAR_00047.xsd"


@pytest.fixture(scope="module")
def module_def():
    return EcucDefParser().parse_module_def_file(DEF_FILE)


def test_top_level_containers(module_def):
    assert module_def.short_name == "Arti"
    assert module_def.definition_ref == "/AUTOSAR/EcucDefs/Arti"
    assert set(module_def.containers) == {"ArtiGeneric", "ArtiHardware", "ArtiOs", "ArtiValues"}


def test_arti_values_children(module_def):
    values = module_def.containers["ArtiValues"]
    assert set(values.sub_containers) == {
        "ArtiConstant", "ArtiExpression", "ArtiHook", "ArtiObjectClassParameter",
        "ArtiObjectInstanceParameter", "ArtiParameterTypeMap", "ArtiStates",
    }


def test_arti_hook_parameters(module_def):
    hook = module_def.containers["ArtiValues"].sub_containers["ArtiHook"]
    mandatory = {"ArtiHookClass", "ArtiHookContext", "ArtiHookEventName", "ArtiHookInstance"}
    optional = {"ArtiHookAssociatedFunction", "ArtiHookFileName"}
    assert set(hook.parameters) == mandatory | optional
    for name in mandatory:
        assert hook.parameters[name].lower_multiplicity == 1
    for name in optional:
        assert hook.parameters[name].lower_multiplicity == 0
    # Both type-map references are optional (0..1) in the specification.
    for name in ("ArtiHookEventParameterTypeRef", "ArtiHookInstanceParameterTypeRef"):
        ref = hook.references[name]
        assert (ref.lower_multiplicity, ref.upper_multiplicity) == (0, 1)
        assert ref.destination_ref.endswith("/ArtiValues/ArtiParameterTypeMap")


def test_type_map_pair(module_def):
    type_map = module_def.containers["ArtiValues"].sub_containers["ArtiParameterTypeMap"]
    pair = type_map.sub_containers["ArtiParameterTypeMapPair"]
    assert pair.lower_multiplicity == 1
    assert pair.upper_multiplicity == -1
    pair_input = pair.parameters["ArtiParameterTypeMapPairInput"]
    # The 0..65535 limit applies only when used by an ArtiHook; the definition itself is 64 bit.
    assert (pair_input.min_value, pair_input.max_value) == (0, 18446744073709551615)
    out_ref = pair.references["ArtiParameterTypeMapPairOutputRef"]
    assert len(out_ref.choice_destination_refs) == 9
    assert "/AUTOSAR/EcucDefs/Arti/ArtiOs/ArtiOsTaskInstance" in out_ref.choice_destination_refs
    assert "/AUTOSAR/EcucDefs/Os/OsAppMode" in out_ref.choice_destination_refs


def test_task_state_literals(module_def):
    states = module_def.containers["ArtiValues"].sub_containers["ArtiStates"]
    assert states.parameters["ArtiStatesTaskEnhanced"].lower_multiplicity == 1
    literals = states.sub_containers["ArtiStatesTaskState"].parameters["ArtiStatesTaskStateEnum"].literals
    assert literals == [
        "ArtiTaskStateActivated", "ArtiTaskStatePreempted", "ArtiTaskStateReady", "ArtiTaskStateReleased",
        "ArtiTaskStateRunning", "ArtiTaskStateSuspended", "ArtiTaskStateWaiting",
    ]


def test_unbounded_references_are_read_as_infinite(module_def):
    """UPPER-MULTIPLICITY-INFINITE=true must give 0..* (-1), also for references."""
    inst_param = module_def.containers["ArtiGeneric"].sub_containers[
        "ArtiGenericComponentInstance"].sub_containers["ArtiGenericComponentInstanceParameter"]
    arti_os = module_def.containers["ArtiOs"]
    refs = [
        inst_param.references["ArtiGenericComponentInstanceParameterClassParameterRef"],
        arti_os.references["ArtiOsGenericComponentRef"],
        arti_os.sub_containers["ArtiOsInstance"].references["ArtiOsInstanceHookRef"],
    ]
    for ref in refs:
        assert (ref.lower_multiplicity, ref.upper_multiplicity) == (0, -1), ref.short_name


def test_arti_os_is_flat(module_def):
    """Class and Instance containers are siblings under ArtiOs, not nested."""
    arti_os = module_def.containers["ArtiOs"]
    assert len(arti_os.sub_containers) == 16
    task_class = arti_os.sub_containers["ArtiOsTaskClass"]
    task_inst = arti_os.sub_containers["ArtiOsTaskInstance"]
    assert not task_class.sub_containers
    assert task_inst.parameters["ArtiOsTaskInstanceId"].lower_multiplicity == 1
    assert task_inst.references["ArtiOsTaskInstanceEcucRef"].destination_ref == "/AUTOSAR/EcucDefs/Os/OsTask"


def _classes(xml_text, container_name):
    """CONFIG-CLASS/CONFIG-VARIANT pairs of the ECUC-*-DEF whose SHORT-NAME is container_name."""
    from lxml import etree
    ns = {"a": "http://autosar.org/schema/r4.0"}
    root = etree.fromstring(xml_text.encode("utf-8"))
    node = root.xpath(f"//a:SHORT-NAME[text()='{container_name}']/..", namespaces=ns)[0]
    return [(c.findtext("a:CONFIG-CLASS", namespaces=ns), c.findtext("a:CONFIG-VARIANT", namespaces=ns))
            for c in node.xpath("a:MULTIPLICITY-CONFIG-CLASSES/*", namespaces=ns)]


def test_configuration_classes_follow_the_pdfs():
    pytest.importorskip("lxml")
    text = DEF_FILE.read_text(encoding="utf-8")
    # SWS ARTI: "Pre-compile time X All Variants"
    assert _classes(text, "ArtiHook") == [
        ("PRE-COMPILE", "VARIANT-PRE-COMPILE"), ("PRE-COMPILE", "VARIANT-LINK-TIME"), ("PRE-COMPILE", "VARIANT-POST-BUILD")]
    # SWS OS: ArtiHardware supports post-build, ArtiOs supports link-time
    assert _classes(text, "ArtiHardware") == [("PRE-COMPILE", "VARIANT-PRE-COMPILE"), ("POST-BUILD", "VARIANT-POST-BUILD")]
    assert _classes(text, "ArtiOsTaskInstance") == [("PRE-COMPILE", "VARIANT-PRE-COMPILE"), ("LINK", "VARIANT-LINK-TIME")]


def test_spec_ids_unique_and_complete():
    """Each ECUC_Arti_xxxxx id appears once: 158 definitions (ARTI chapter 10 minus ArtiRte, plus SWS OS 10.4)."""
    import re
    ids = re.findall(r"<!-- (ECUC_Arti_\d+) -->", DEF_FILE.read_text(encoding="utf-8"))
    assert len(ids) == len(set(ids)), "duplicate ECUC id"
    assert len(ids) == 158
    for spot in ("ECUC_Arti_00012", "ECUC_Arti_00024", "ECUC_Arti_00032", "ECUC_Arti_00092", "ECUC_Arti_00178"):
        assert spot in ids


@pytest.mark.skipif(not XSD_FILE.exists(), reason="AUTOSAR_00047.xsd not present")
def test_definition_is_schema_valid():
    lxml_etree = pytest.importorskip("lxml.etree")
    xml_xsd = XSD_FILE.parent / "xml.xsd"
    if not xml_xsd.exists():
        pytest.skip("xml.xsd (imported by AUTOSAR xsd) not present")
    schema = lxml_etree.XMLSchema(lxml_etree.parse(str(XSD_FILE)))
    schema.assertValid(lxml_etree.parse(str(DEF_FILE)))


def test_configuration_round_trip(module_def, tmp_path):
    manager = ConfigurationManager(module_def)
    values_def = module_def.containers["ArtiValues"]
    values = manager.create_container_instance(values_def, None, "ArtiValues")

    type_map_def = values_def.sub_containers["ArtiParameterTypeMap"]
    type_map = manager.create_container_instance(type_map_def, values, "ArtiParameterTypeMap_TaskId")
    pair = manager.create_container_instance(type_map_def.sub_containers["ArtiParameterTypeMapPair"], type_map, "Pair0")
    manager.set_parameter_value(pair, "ArtiParameterTypeMapPairInput", 3)
    manager.set_parameter_value(pair, "ArtiParameterTypeMapPairOutput", "Task_A")

    hook = manager.create_container_instance(values_def.sub_containers["ArtiHook"], values, "ArtiHook_Start")
    for name, value in {
        "ArtiHookClass": "AR_CP_OS_TASK", "ArtiHookContext": "NOSUSP",
        "ArtiHookEventName": "OsTask_Start", "ArtiHookInstance": "Os",
    }.items():
        manager.set_parameter_value(hook, name, value)

    target = tmp_path / "Arti_cfg.arxml"
    manager.save_configuration(target)

    reloaded = ConfigurationManager(module_def)
    reloaded.load_configuration(target)
    top = {c.short_name: c for c in reloaded.configuration.containers}
    assert set(top) == {"ArtiValues"}
    children = {c.short_name: c for c in top["ArtiValues"].sub_containers}
    assert set(children) == {"ArtiParameterTypeMap_TaskId", "ArtiHook_Start"}
    loaded_pair = children["ArtiParameterTypeMap_TaskId"].sub_containers[0]
    assert loaded_pair.parameter_values["ArtiParameterTypeMapPairInput"].value == 3
    assert children["ArtiHook_Start"].parameter_values["ArtiHookEventName"].value == "OsTask_Start"

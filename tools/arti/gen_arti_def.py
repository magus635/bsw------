"""Generate definitions/Arti/Arti_ParamDef.arxml.

Run from the repository root:  python -m tools.arti.gen_arti_def [output.arxml]

Sources: AUTOSAR CP SWS ARTI R24-11 chapter 10 (this file) and SWS OS R21-11
section 10.4 (gen_arti_os.py).

Emitted: ArtiGeneric, ArtiValues (SWS ARTI) and ArtiHardware, ArtiOs (SWS OS).
Not emitted: ArtiRte (filled by the RTE generator, not part of the OS delivery).
"""
import json
import sys
from pathlib import Path
from xml.sax.saxutils import escape

SPEC = json.loads((Path(__file__).with_name("arti_spec.json")).read_text(encoding="utf-8"))

BASE = "/AUTOSAR/EcucDefs/Arti"
VARIANTS = ["VARIANT-PRE-COMPILE", "VARIANT-LINK-TIME", "VARIANT-POST-BUILD"]


def ind(n):
    return "  " * n


def tag(n, name, text):
    return f"{ind(n)}<{name}>{escape(str(text))}</{name}>\n"


def _expand(entries):
    """[(class, variant)] from the PDF -> [(class, variant)], 'All Variants' = every variant the module supports."""
    out = []
    for cls, variant in entries:
        for v in (VARIANTS if variant == "All Variants" else [variant]):
            out.append((cls, v))
    return out


def cfg_classes(n, kind, name):
    entries = _expand(SPEC.get(name, {}).get("mc" if kind == "mult" else "vc", []))
    if not entries:
        return ""
    outer = "MULTIPLICITY-CONFIG-CLASSES" if kind == "mult" else "VALUE-CONFIG-CLASSES"
    inner = "ECUC-MULTIPLICITY-CONFIGURATION-CLASS" if kind == "mult" else "ECUC-VALUE-CONFIGURATION-CLASS"
    s = f"{ind(n)}<{outer}>\n"
    for cls, v in entries:
        s += f"{ind(n+1)}<{inner}>\n"
        s += tag(n + 2, "CONFIG-CLASS", cls)
        s += tag(n + 2, "CONFIG-VARIANT", v)
        s += f"{ind(n+1)}</{inner}>\n"
    s += f"{ind(n)}</{outer}>\n"
    return s


def head(n, name, desc, lo, hi, ecuc_id):
    spec = SPEC.get(name, {})
    expected = spec.get("mult") or spec.get("container_mult")
    actual = [lo, -1 if hi == "*" else hi]
    if expected and expected != actual:
        raise ValueError(f"{name}: multiplicity {actual} differs from the specification {expected}")
    s = tag(n, "SHORT-NAME", name)
    s += f"{ind(n)}<DESC>\n{ind(n+1)}<L-2 L=\"EN\">{escape(desc)}</L-2>\n{ind(n)}</DESC>\n"
    s += f"{ind(n)}<!-- {ecuc_id} -->\n"
    s += tag(n, "LOWER-MULTIPLICITY", lo)
    if hi == "*":
        s += tag(n, "UPPER-MULTIPLICITY-INFINITE", "true")
    else:
        s += tag(n, "UPPER-MULTIPLICITY", hi)
    return s


def param_tail(n, scope, name):
    """Order follows ECUC-DEFINITION-ELEMENT / ECUC-COMMON-ATTRIBUTES in the AUTOSAR schema."""
    spec = SPEC.get(name, {})
    s = tag(n, "SCOPE", spec.get("scope") or scope)
    s += cfg_classes(n, "mult", name)
    s += tag(n, "ORIGIN", "AUTOSAR_ECUC")
    if spec.get("pbm") is not None:
        s += tag(n, "POST-BUILD-VARIANT-MULTIPLICITY", str(spec["pbm"]).lower())
    s += tag(n, "POST-BUILD-VARIANT-VALUE", str(bool(spec.get("pbv"))).lower())
    s += cfg_classes(n, "value", name)
    return s


def string_param(n, name, desc, lo, hi, eid, scope="ECU"):
    s = f"{ind(n)}<ECUC-STRING-PARAM-DEF>\n" + head(n + 1, name, desc, lo, hi, eid)
    s += param_tail(n + 1, scope, name) + f"{ind(n)}</ECUC-STRING-PARAM-DEF>\n"
    return s


def func_param(n, name, desc, lo, hi, eid, scope="LOCAL"):
    s = f"{ind(n)}<ECUC-FUNCTION-NAME-DEF>\n" + head(n + 1, name, desc, lo, hi, eid)
    s += param_tail(n + 1, scope, name) + f"{ind(n)}</ECUC-FUNCTION-NAME-DEF>\n"
    return s


def bool_param(n, name, desc, lo, hi, eid, scope="LOCAL"):
    s = f"{ind(n)}<ECUC-BOOLEAN-PARAM-DEF>\n" + head(n + 1, name, desc, lo, hi, eid)
    s += param_tail(n + 1, scope, name) + f"{ind(n)}</ECUC-BOOLEAN-PARAM-DEF>\n"
    return s


def int_param(n, name, desc, lo, hi, eid, mn, mx, scope="ECU"):
    s = f"{ind(n)}<ECUC-INTEGER-PARAM-DEF>\n" + head(n + 1, name, desc, lo, hi, eid)
    s += param_tail(n + 1, scope, name)
    s += tag(n + 1, "MAX", mx) + tag(n + 1, "MIN", mn)
    s += f"{ind(n)}</ECUC-INTEGER-PARAM-DEF>\n"
    return s


def enum_param(n, name, desc, lo, hi, eid, literals, scope="LOCAL"):
    s = f"{ind(n)}<ECUC-ENUMERATION-PARAM-DEF>\n" + head(n + 1, name, desc, lo, hi, eid)
    s += param_tail(n + 1, scope, name)
    s += f"{ind(n+1)}<LITERALS>\n"
    for lit in literals:
        s += f"{ind(n+2)}<ECUC-ENUMERATION-LITERAL-DEF>\n{tag(n+3, 'SHORT-NAME', lit)}{ind(n+2)}</ECUC-ENUMERATION-LITERAL-DEF>\n"
    s += f"{ind(n+1)}</LITERALS>\n{ind(n)}</ECUC-ENUMERATION-PARAM-DEF>\n"
    return s


def ref(n, name, desc, lo, hi, eid, dest, scope="ECU"):
    s = f"{ind(n)}<ECUC-REFERENCE-DEF>\n" + head(n + 1, name, desc, lo, hi, eid)
    s += param_tail(n + 1, scope, name)
    s += f'{ind(n+1)}<DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{dest}</DESTINATION-REF>\n'
    s += f"{ind(n)}</ECUC-REFERENCE-DEF>\n"
    return s


def choice_ref(n, name, desc, lo, hi, eid, dests, scope="ECU"):
    s = f"{ind(n)}<ECUC-CHOICE-REFERENCE-DEF>\n" + head(n + 1, name, desc, lo, hi, eid)
    s += param_tail(n + 1, scope, name) + f"{ind(n+1)}<DESTINATION-REFS>\n"
    for d in dests:
        s += f'{ind(n+2)}<DESTINATION-REF DEST="ECUC-PARAM-CONF-CONTAINER-DEF">{d}</DESTINATION-REF>\n'
    s += f"{ind(n+1)}</DESTINATION-REFS>\n{ind(n)}</ECUC-CHOICE-REFERENCE-DEF>\n"
    return s


def foreign_ref(n, name, desc, lo, hi, eid, dest_type, scope="LOCAL"):
    s = f"{ind(n)}<ECUC-FOREIGN-REFERENCE-DEF>\n" + head(n + 1, name, desc, lo, hi, eid)
    s += param_tail(n + 1, scope, name)
    s += tag(n + 1, "DESTINATION-TYPE", dest_type) + f"{ind(n)}</ECUC-FOREIGN-REFERENCE-DEF>\n"
    return s


def container(n, name, desc, lo, hi, eid, params="", refs="", subs=""):
    s = f"{ind(n)}<ECUC-PARAM-CONF-CONTAINER-DEF>\n" + head(n + 1, name, desc, lo, hi, eid)
    s += cfg_classes(n + 1, "mult", name)
    s += tag(n + 1, "POST-BUILD-VARIANT-MULTIPLICITY", str(bool(SPEC.get(name, {}).get("pbm"))).lower())
    s += tag(n + 1, "REQUIRES-INDEX", "false")
    if params:
        s += f"{ind(n+1)}<PARAMETERS>\n{params}{ind(n+1)}</PARAMETERS>\n"
    if refs:
        s += f"{ind(n+1)}<REFERENCES>\n{refs}{ind(n+1)}</REFERENCES>\n"
    if subs:
        s += f"{ind(n+1)}<SUB-CONTAINERS>\n{subs}{ind(n+1)}</SUB-CONTAINERS>\n"
    s += f"{ind(n)}</ECUC-PARAM-CONF-CONTAINER-DEF>\n"
    return s


# ---------------------------------------------------------------- ArtiGeneric
G = BASE + "/ArtiGeneric"
V = BASE + "/ArtiValues"
N = 6  # indent level of module's children


def build_generic():
    cls_param = container(
        N + 3, "ArtiGenericComponentClassParameter", "Parameter definition of a class.", 0, "*", "ECUC_Arti_00045",
        params=string_param(N + 5, "ArtiGenericComponentClassParameterName", "Name of the parameter.", 1, 1, "ECUC_Arti_00046"),
        refs=ref(N + 5, "ArtiGenericComponentClassParameterTypeMapRef",
                 "Refers to a parameter type to interpret the parameter value.", 0, 1, "ECUC_Arti_00053",
                 V + "/ArtiParameterTypeMap"))
    cls = container(
        N + 1, "ArtiGenericComponentClass",
        'The class definition describes the layout of the object (similar to a "class" definition in C++).',
        0, "*", "ECUC_Arti_00043",
        params=string_param(N + 3, "ArtiGenericComponentClassName", "Name of the class.", 1, 1, "ECUC_Arti_00044"),
        subs=cls_param)
    inst_param = container(
        N + 3, "ArtiGenericComponentInstanceParameter", "Parameter definition of an instance.", 0, "*", "ECUC_Arti_00051",
        refs=(
            ref(N + 5, "ArtiGenericComponentInstanceParameterClassParameterRef",
                "Refers to an ArtiGenericComponentClassParameter that defines this parameter.", 0, "*", "ECUC_Arti_00047",
                G + "/ArtiGenericComponentClass/ArtiGenericComponentClassParameter")
            + ref(N + 5, "ArtiGenericComponentInstanceParameterConstantRef",
                  "Refers to an ArtiConstant that represents the value of this parameter.", 0, 1, "ECUC_Arti_00040",
                  V + "/ArtiConstant")
            + ref(N + 5, "ArtiGenericComponentInstanceParameterExpressionRef",
                  "Refers to an ArtiExpression that evaluates the value of this parameter.", 0, 1, "ECUC_Arti_00041",
                  V + "/ArtiExpression")
            + ref(N + 5, "ArtiGenericComponentInstanceParameterHookRef",
                  "Refers to a hook that records this parameter.", 0, 1, "ECUC_Arti_00052", V + "/ArtiHook")))
    inst = container(
        N + 1, "ArtiGenericComponentInstance", "The instance definition describes a specific instantiated object.",
        0, "*", "ECUC_Arti_00049",
        params=string_param(N + 3, "ArtiGenericComponentInstanceName", "Name of the instance.", 1, 1, "ECUC_Arti_00050"),
        refs=ref(N + 3, "ArtiGenericComponentInstanceClassRef",
                 "Refers to a ArtGenericClass of which this object is instantiated.", 1, 1, "ECUC_Arti_00048",
                 G + "/ArtiGenericComponentClass"),
        subs=inst_param)
    return container(
        N - 1 + 0, "ArtiGeneric",
        "The ArtiGeneric container contains definitions for generic objects, i.e. not belonging to a standard AUTOSAR module.",
        0, 1, "ECUC_Arti_00042", subs=cls + inst)


# ---------------------------------------------------------------- ArtiValues
def build_values():
    n = N + 1
    constant = container(
        n, "ArtiConstant", "This container holds a constant value.", 0, "*", "ECUC_Arti_00006",
        params=string_param(n + 2, "ArtiConstantString", "This is the constant value for a specific parameter.", 1, 1,
                            "ECUC_Arti_00008"))
    expression = container(
        n, "ArtiExpression",
        "This container holds a C like expression that a debugger can evaluate. This is similar to what is already done in ORTI.",
        0, "*", "ECUC_Arti_00009",
        params=string_param(n + 2, "ArtiExpressionString",
                            "This string represents a C like expression that a debugger can evaluate.", 1, 1,
                            "ECUC_Arti_00011"))
    hook_params = (
        func_param(n + 2, "ArtiHookAssociatedFunction", "Name of the C function that is associated with this hook.", 0, 1,
                   "ECUC_Arti_00180")
        + string_param(n + 2, "ArtiHookClass",
                       "Name of the (schedule) class of macros. Classes can be one of the predefined classes or user defined.",
                       1, 1, "ECUC_Arti_00013")
        + string_param(n + 2, "ArtiHookContext",
                       'Name of the execution context. One of NOSUSP, SPRVSR, or USER. See also chapter "ARTI Tracing Macro".',
                       1, 1, "ECUC_Arti_00014")
        + string_param(n + 2, "ArtiHookEventName",
                       "The name of the event as defined for a particular class, or an arbitrary name for generic classes.",
                       1, 1, "ECUC_Arti_00015")
        + string_param(n + 2, "ArtiHookFileName",
                       "File name (possibly with path) where this ArtiHook is implemented.", 0, 1, "ECUC_Arti_00181")
        + string_param(n + 2, "ArtiHookInstance", "Name of an instance of the (schedule) class.", 1, 1, "ECUC_Arti_00017"))
    hook_refs = (
        foreign_ref(n + 2, "ArtiHookEntryRef",
                    "Reference to the BswModuleEntry that describes the parameters of this hook.", 0, 1,
                    "ECUC_Arti_00179", "BSW-MODULE-ENTRY")
        + ref(n + 2, "ArtiHookEventParameterTypeRef", "Refers to a parameter type to interpret the hook event number.",
              0, 1, "ECUC_Arti_00016", V + "/ArtiParameterTypeMap")
        + ref(n + 2, "ArtiHookInstanceParameterTypeRef",
              "Refers to a parameter type to interpret the hook instance number.", 0, 1, "ECUC_Arti_00018",
              V + "/ArtiParameterTypeMap"))
    hook = container(n, "ArtiHook", "This container represents an ARTI hook that is present in the module.", 0, "*",
                     "ECUC_Arti_00012", params=hook_params, refs=hook_refs)
    obj_class = container(
        n, "ArtiObjectClassParameter", "This container represents a parameter of an Arti object class definition.",
        0, "*", "ECUC_Arti_00020",
        refs=ref(n + 2, "ArtiObjectClassParameterTypeMapRef",
                 "Refers to a parameter type to interpret the instance parameter value.", 0, 1, "ECUC_Arti_00028",
                 V + "/ArtiParameterTypeMap"))
    obj_inst = container(
        n, "ArtiObjectInstanceParameter", "This container represents a parameter of an Arti object instance.",
        0, "*", "ECUC_Arti_00021",
        refs=(ref(n + 2, "ArtiObjectInstanceParameterConstantRef",
                  "Refers to a constant representing the value of this parameter.", 0, 1, "ECUC_Arti_00007",
                  V + "/ArtiConstant")
              + ref(n + 2, "ArtiObjectInstanceParameterExpressionRef",
                    "Refers to an expression that evaluates the value of this parameter.", 0, 1, "ECUC_Arti_00010",
                    V + "/ArtiExpression")
              + ref(n + 2, "ArtiObjectInstanceParameterHookRef", "Refers to a hook that records this parameter.",
                    0, 1, "ECUC_Arti_00019", V + "/ArtiHook")))
    # OutputRef destinations: only the ones defined in SWS ARTI itself are listed.
    # ArtiOs*Instance and OsAppMode (SWS_OS) are intentionally absent -- see header comment.
    pair_params = (
        int_param(n + 4, "ArtiParameterTypeMapPairInput",
                  'The numerical value given by a parameter to translate. When used with ArtiHooks, this parameter is mandatory (multiplicity 1) and its value is limited to the range of 0..65535. This parameter may be used to map the values given by "instanceParameter" and/or the "eventParameter" of the ARTI_TRACE macro.',
                  0, 1, "ECUC_Arti_00024", 0, "18446744073709551615")
        + string_param(n + 4, "ArtiParameterTypeMapPairOutput", "The string to display for the Input value.", 0, 1,
                       "ECUC_Arti_00026"))
    pair_refs = (
        ref(n + 4, "ArtiParameterTypeMapPairInputExpressionRef",
            "Refers to an expression that evaluates to a numerical value to translate.", 0, 1, "ECUC_Arti_00025",
            V + "/ArtiExpression")
        + choice_ref(n + 4, "ArtiParameterTypeMapPairOutputRef",
                     "Choice Reference to ArtiOsTaskInstance, ArtiOsIsrInstance, ArtiStatesTaskState, OsAppMode, ArtiOsContextInstance, or ArtiOsStackInstance.",
                     0, 1, "ECUC_Arti_00027",
                     [BASE + "/ArtiOs/ArtiOsContextInstance",
                      BASE + "/ArtiOs/ArtiOsIsrInstance",
                      BASE + "/ArtiOs/ArtiOsStackInstance",
                      BASE + "/ArtiOs/ArtiOsTaskInstance",
                      V + "/ArtiStates/ArtiStatesScheduleTableState",
                      V + "/ArtiStates/ArtiStatesSpinlockOwnerType",
                      V + "/ArtiStates/ArtiStatesSpinlockState",
                      V + "/ArtiStates/ArtiStatesTaskState",
                      "/AUTOSAR/EcucDefs/Os/OsAppMode"]))
    pair = container(
        n + 2, "ArtiParameterTypeMapPair",
        "A key/value pair to map a parameter value to a display string and/or an Arti or EcuC object.", 1, "*",
        "ECUC_Arti_00023", params=pair_params, refs=pair_refs)
    typemap = container(
        n, "ArtiParameterTypeMap",
        "A map of key/value pairs to map a parameter value to a display string and/or an Arti or EcuC object.",
        0, "*", "ECUC_Arti_00022", subs=pair)

    def state(name, eid_c, eid_p, desc, lits, pname):
        return container(
            n + 2, name, desc, 0, "*", eid_c,
            params=enum_param(n + 4, pname, f"{name} choice of the states.", 1, 1, eid_p, lits))

    states_subs = (
        state("ArtiStatesScheduleTableState", "ECUC_Arti_00205", "ECUC_Arti_00206",
              "Each state used by the OsScheduleTable has to be listed as ArtiStatesScheduleTableState parameter with a choice of the states.",
              ["ArtiScheduleTableStateNext", "ArtiScheduleTableStateRunning",
               "ArtiScheduleTableStateRunningAndSynchronous", "ArtiScheduleTableStateStopped",
               "ArtiScheduleTableStateWaiting"], "ArtiStatesScheduleTableStateEnum")
        + state("ArtiStatesSpinlockOwnerType", "ECUC_Arti_00207", "ECUC_Arti_00208",
                "Each owner type used by the OsSpinlock has to be listed as ArtiStatesSpinlockOwnerType parameter with a choice of the states.",
                ["ArtiSpinlockOwnerTypeIsr2", "ArtiSpinlockOwnerTypeTask"], "ArtiStatesSpinlockOwnerTypeEnum")
        + state("ArtiStatesSpinlockState", "ECUC_Arti_00209", "ECUC_Arti_00210",
                "Each state used by the OsSpinlock has to be listed as ArtiStatesSpinlockState parameter with a choice of the states.",
                ["ArtiSpinlockStateLocked", "ArtiSpinlockStateUnlocked"], "ArtiStatesSpinlockStateEnum")
        + state("ArtiStatesTaskState", "ECUC_Arti_00030", "ECUC_Arti_00033",
                "Each state used by the OS has to be listed as ArtiStatesTaskState Parameter with a choice of the states.",
                ["ArtiTaskStateActivated", "ArtiTaskStatePreempted", "ArtiTaskStateReady", "ArtiTaskStateReleased",
                 "ArtiTaskStateRunning", "ArtiTaskStateSuspended", "ArtiTaskStateWaiting"], "ArtiStatesTaskStateEnum"))
    states = container(
        n, "ArtiStates", "This container contains all states of tasks, isrs... that the EcuC uses.", 0, "*",
        "ECUC_Arti_00029",
        params=bool_param(n + 2, "ArtiStatesTaskEnhanced",
                          'Set to true, if the OS provides an "enhanced" state model with "READY" split to "Activated", "Preempted", "Released".',
                          1, 1, "ECUC_Arti_00032"),
        subs=states_subs)
    return container(
        N - 1 + 0, "ArtiValues",
        "The ArtiValues container collects all parameter values for ARTI that are filled by the generators (OS, RTE, ...)",
        0, "*", "ECUC_Arti_00002",
        subs=constant + expression + hook + obj_class + obj_inst + typemap + states)


def main(out):
    from tools.arti.gen_arti_os import build_hardware, build_os
    body = build_generic() + build_hardware() + build_os() + build_values()
    xml = f'''<?xml version="1.0" encoding="UTF-8"?>
<!--
  Arti_ParamDef.arxml: ECUC parameter definition of the AUTOSAR "Arti" module.

  Source : AUTOSAR CP R24-11, SWS ARTI (Document ID 923), chapter 10.
           Every container/parameter carries its ECUC_Arti_xxxxx id in a comment.
  Scope  : ArtiGeneric, ArtiValues (SWS ARTI R24-11 chapter 10) and
           ArtiHardware, ArtiOs (SWS OS R21-11 section 10.4, which is where
           those two containers are specified).
  NOT included on purpose: ArtiRte (filled by the RTE generator, not part of
           the OS delivery).
  Notes  : Descriptions are shortened from the specifications.
           The path of EcucCoreDefinition (ArtiHardwareCoreInstanceEcucCoreRef)
           is assumed: SWS OS names the type but gives no path.
           Multiplicities, configuration classes, post-build flags and scopes
           come from the PDF tables (tools/arti/arti_spec.json, extracted by
           tools/arti/extract_arti_spec.py); generation fails if a multiplicity
           written in the generator disagrees with them.
  Validated against doc/ARTI/AUTOSAR_00047.xsd.
-->
<AUTOSAR xmlns="http://autosar.org/schema/r4.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://autosar.org/schema/r4.0 AUTOSAR_00047.xsd">
  <AR-PACKAGES>
    <AR-PACKAGE>
      <SHORT-NAME>AUTOSAR</SHORT-NAME>
      <AR-PACKAGES>
        <AR-PACKAGE>
          <SHORT-NAME>EcucDefs</SHORT-NAME>
          <ELEMENTS>
            <ECUC-MODULE-DEF>
              <SHORT-NAME>Arti</SHORT-NAME>
              <DESC>
                <L-2 L="EN">The Arti Module serves as a superordinate container collecting all information and parameters concerning ARTI.</L-2>
              </DESC>
              <!-- ECUC_Arti_00001 -->
              <LOWER-MULTIPLICITY>0</LOWER-MULTIPLICITY>
              <UPPER-MULTIPLICITY>1</UPPER-MULTIPLICITY>
              <POST-BUILD-VARIANT-SUPPORT>true</POST-BUILD-VARIANT-SUPPORT>
              <SUPPORTED-CONFIG-VARIANTS>
                <SUPPORTED-CONFIG-VARIANT>VARIANT-LINK-TIME</SUPPORTED-CONFIG-VARIANT>
                <SUPPORTED-CONFIG-VARIANT>VARIANT-POST-BUILD</SUPPORTED-CONFIG-VARIANT>
                <SUPPORTED-CONFIG-VARIANT>VARIANT-PRE-COMPILE</SUPPORTED-CONFIG-VARIANT>
              </SUPPORTED-CONFIG-VARIANTS>
              <CONTAINERS>
{body}              </CONTAINERS>
            </ECUC-MODULE-DEF>
          </ELEMENTS>
        </AR-PACKAGE>
      </AR-PACKAGES>
    </AR-PACKAGE>
  </AR-PACKAGES>
</AUTOSAR>
'''
    with open(out, "w", encoding="utf-8", newline="\n") as f:
        f.write(xml)


if __name__ == "__main__":
    from pathlib import Path
    default = Path(__file__).resolve().parents[2] / "definitions" / "Arti" / "Arti_ParamDef.arxml"
    main(sys.argv[1] if len(sys.argv) > 1 else str(default))

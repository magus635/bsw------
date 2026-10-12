"""ORTI parity of templates/Os/Os_Arti.arxml (openspec change add-arti-orti-parity).

Renders the reference ORTI (doc/ARTI/Os_Trace.orti: the plugin's Os_Trace_Core0.ORTI with its
KOIL syntax defects fixed, same content) and the ARTI template from the same Os configuration,
then checks that every ORTI object attribute has an ARTI counterpart carrying the same
expression / value.

Coverage rule for one ORTI attribute (kind, name, attr, value): some ARTI ArtiExpressionString or
ArtiConstantString equals `value`, and, except for the OS block, the ARTI container that holds it
has the object's name in its SHORT-NAME. A few attributes are carried by standard ARTI parameters
instead (ALT_EVIDENCE). Gaps are tracked as (kind, attr) pairs:

- EXCEPTIONS: gaps accepted for good (documented in design.md D5/D6).
- KNOWN_GAPS: gaps still to close; the list may only shrink. An entry that is no longer a gap
  must be removed, so the list always describes the real state.
"""
import re
import shutil
from pathlib import Path

import pytest

from autosar_configurator.generator.generator import CodeGenerator

from .os_arti_fixture import build_os_config
from .test_orti_template import APP_COMMON_STUB, TEMPLATE as ORTI_TEMPLATE

etree = pytest.importorskip("lxml.etree")

ROOT = Path(__file__).resolve().parents[2]
ARTI_TEMPLATE = ROOT / "templates" / "Os" / "Os_Arti.arxml"
NS = {"a": "http://autosar.org/schema/r4.0"}

# Accepted differences, see openspec/changes/add-arti-orti-parity/design.md D5, D6.
EXCEPTIONS = {
    ("RESOURCE", "RESOURCE_OWNER"),   # ObjectID numbering via Os_AppCommon.m: follow-up change
    ("SPINLOCK", "SPINLOCK_OWNER"),   # same
}

# Gaps still to close. Shrinks as the phases of the change are implemented.
KNOWN_GAPS = set()

# ORTI emits STACK / CONTEXT / LOCKED for CATEGORY_1 ISRs, but the kernel only defines <name>_stack,
# <name>_ContextInfo and <name>_RunningData for Tasks and CATEGORY_2 ISRs (plugin
# context/Os_context_Lcfg.c, isr/Os_isr_Lcfg.c), so those ORTI entries reference symbols that do
# not exist. ARTI deliberately leaves them out.
CAT1_ISR_SKIPPED = {"STACK", "CONTEXT", "LOCKED"}

# The ARTI string is shared between objects, so it carries no object name.
NAME_AGNOSTIC = {("STACK", "FILLPATTERN")}

# ORTI attributes that ARTI carries in a standard parameter: (kind, attr) -> ARTI parameter name
ALT_EVIDENCE = {
    ("ISR", "CATEGORY"): "ArtiOsIsrInstanceCategory",
    ("STACK", "STACKDIRECTION"): "ArtiOsStackInstanceDirection",
    ("OS", "COREID"): "ArtiHardwareCoreInstanceCoreId",
    ("ALARM", "COUNTER"): "ArtiOsAlarmInstanceCounter",
}


def _render(tmp_path, template, extra=None):
    module_def, mgr = build_os_config()
    tpl_dir = tmp_path / "tpl" / "Os"
    tpl_dir.mkdir(parents=True)
    shutil.copy(template, tpl_dir / template.name)
    for name, text in (extra or {}).items():
        (tpl_dir / name).write_text(text, encoding="utf-8")
    gen = CodeGenerator(module_def, mgr.configuration, project_template_dir=tmp_path / "tpl")
    assert gen.generate_all(tmp_path / "out") is True
    return (tmp_path / "out" / "Os" / template.name).read_text(encoding="utf-8")


def orti_attributes(text):
    """[(kind, name, attr, value)] of the instance section (after the IMPLEMENTATION block)."""
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = text[text.index("OS THA6xxx"):]
    found = []
    for m in re.finditer(r"^(\w+)\s+(\S+)\s*\{(.*?)^\};", text, flags=re.S | re.M):
        kind, name, body = m.groups()
        for a in re.finditer(r'^\s*(\w+)\s*=\s*"(.*?)"\s*;', body, flags=re.M):
            found.append((kind, name, a.group(1), a.group(2)))
    return found


def arti_evidence(xml_text):
    """Strings/params of the ARTI output used to look up ORTI attributes."""
    root = etree.fromstring(xml_text.encode("utf-8"))
    strings = []   # (container SHORT-NAME, string)
    params = {}    # parameter short name -> set of values
    pairs = {}     # type map short name -> set of (input) values
    for c in root.iter("{%s}ECUC-CONTAINER-VALUE" % NS["a"]):
        sn = c.findtext("a:SHORT-NAME", namespaces=NS)
        for p in c.xpath("a:PARAMETER-VALUES/*", namespaces=NS):
            d = p.findtext("a:DEFINITION-REF", namespaces=NS).rsplit("/", 1)[-1]
            v = (p.findtext("a:VALUE", namespaces=NS) or "").strip()
            if d in ("ArtiExpressionString", "ArtiConstantString"):
                strings.append((sn, v))
            params.setdefault(d, set()).add(v)
    for tm in root.iter("{%s}ECUC-CONTAINER-VALUE" % NS["a"]):
        if tm.findtext("a:DEFINITION-REF", namespaces=NS).endswith("/ArtiParameterTypeMap"):
            name = tm.findtext("a:SHORT-NAME", namespaces=NS)
            for p in tm.xpath("a:SUB-CONTAINERS/*/a:PARAMETER-VALUES/*", namespaces=NS):
                if p.findtext("a:DEFINITION-REF", namespaces=NS).endswith("PairInput"):
                    pairs.setdefault(name, set()).add(p.findtext("a:VALUE", namespaces=NS).strip())
    return strings, params, pairs


def find_gaps(tmp_path):
    orti = orti_attributes(_render(tmp_path / "orti", ORTI_TEMPLATE, {"Os_AppCommon.m": APP_COMMON_STUB}))
    strings, params, pairs = arti_evidence(_render(tmp_path / "arti", ARTI_TEMPLATE))
    categories = {n: v for k, n, a, v in orti if k == "ISR" and a == "CATEGORY"}
    gaps = []
    for kind, name, attr, value in orti:
        obj = name[: -len("_stack")] if kind == "STACK" and name.endswith("_stack") else name
        if kind == "ISR" and attr in CAT1_ISR_SKIPPED and categories.get(name) == "CATEGORY_1":
            continue
        if kind == "STACK" and categories.get(obj) == "CATEGORY_1":
            continue
        if (kind, attr) in ALT_EVIDENCE:
            ok = value in params.get(ALT_EVIDENCE[(kind, attr)], set())
        elif (kind, attr) == ("TASK", "PRIORITY"):          # ORTI ENUM key = task index
            ok = value in pairs.get("TM_TaskPriority", set())
        else:
            agnostic = kind in ("OS", "OS_CONFIG") or (kind, attr) in NAME_AGNOSTIC
            ok = any(s == value and (agnostic or obj in sn) for sn, s in strings)
        if not ok:
            gaps.append((kind, name, attr, value))
    return orti, gaps


@pytest.fixture(scope="module")
def parity(tmp_path_factory):
    return find_gaps(tmp_path_factory.mktemp("parity"))


def test_reference_orti_is_parsed(parity):
    orti, _ = parity
    kinds = {k for k, *_ in orti}
    assert {"OS", "TASK", "STACK", "ISR", "ALARM", "RESOURCE", "EVENT", "SPINLOCK",
            "SCHEDULETABLE", "OS_CONFIG"} <= kinds
    assert len(orti) > 60


def test_no_new_gaps(parity):
    _, gaps = parity
    actual = {(k, a) for k, _, a, _ in gaps} - EXCEPTIONS
    new = sorted(actual - KNOWN_GAPS)
    assert not new, f"ORTI attributes without an ARTI counterpart: {new}"


def test_known_gaps_are_current(parity):
    """Closed gaps must be removed from KNOWN_GAPS so the list shows the real state."""
    _, gaps = parity
    actual = {(k, a) for k, _, a, _ in gaps} - EXCEPTIONS
    closed = sorted(KNOWN_GAPS - actual)
    assert not closed, f"gaps already closed, remove from KNOWN_GAPS: {closed}"


def test_exceptions_are_real_gaps(parity):
    _, gaps = parity
    actual = {(k, a) for k, _, a, _ in gaps}
    assert EXCEPTIONS <= actual, "an exception is no longer a gap: remove it from EXCEPTIONS"

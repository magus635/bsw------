"""doc/ARTI/Os_Trace.orti (THA6 ORTI 2.2 template) renders to syntactically sound KOIL.

The template includes Os_AppCommon.m from the THA6 Os plugin, which is not in this
repository; a stub providing the two macros it calls is written next to it.
The check is a KOIL subset: balanced brackets, comma-separated ENUM items without a
trailing comma, and every attribute assignment terminated by ';'.
"""
import re
import shutil
from pathlib import Path

import pytest

from autosar_configurator.generator.generator import CodeGenerator

from .os_arti_fixture import build_os_config

ROOT = Path(__file__).resolve().parents[2]
TEMPLATE = ROOT / "doc" / "ARTI" / "Os_Trace.orti"

APP_COMMON_STUB = """\
[!MACRO "Os_Calculate_IocCallBack_ObjectCount", "AppID" = "", "IocCbkObjectIDCount" = ""!][!//
[!VAR "IocCbkObjectIDCount" = "0"!][!//
[!ENDMACRO!][!//
[!MACRO "Os_Calculate_Hook_ObjectCount", "AppID" = "", "HookObjectIDCount" = ""!][!//
[!VAR "HookObjectIDCount" = "0"!][!//
[!ENDMACRO!][!//
"""


def koil_problems(text):
    """Return a list of syntax problems in an ORTI/KOIL text (subset check)."""
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    problems = []

    depth = {"{": 0, "[": 0}
    pairs = {"}": "{", "]": "["}
    for n, line in enumerate(text.splitlines(), 1):
        for ch in re.sub(r'"[^"]*"', '""', line):
            if ch in depth:
                depth[ch] += 1
            elif ch in pairs:
                depth[pairs[ch]] -= 1
                if depth[pairs[ch]] < 0:
                    problems.append(f"line {n}: unbalanced '{ch}'")
    problems += [f"unclosed '{k}'" for k, v in depth.items() if v > 0]

    # ENUM item lists: items separated by commas, no trailing comma.
    # Quoted strings are masked (same length) so "&x_stack[0]" does not look like a list.
    masked = re.sub(r'"[^"]*"', lambda s: '"' + "x" * (len(s.group()) - 2) + '"', text)
    for m in re.finditer(r"\[([^\[\]]*)\]", masked):
        body = text[m.start(1):m.end(1)]
        items = [l.strip() for l in body.splitlines() if l.strip()]
        line_no = text.count("\n", 0, m.start()) + 1
        for i, item in enumerate(items):
            last = i == len(items) - 1
            if not last and not item.endswith(","):
                problems.append(f"ENUM at line {line_no}: missing ',' after {item!r}")
            if last and item.endswith(","):
                problems.append(f"ENUM at line {line_no}: trailing ',' after {item!r}")

    # attribute assignments outside ENUM lists end with ';' (list bodies blanked, line count kept)
    outside = re.sub(r"\[[^\[\]]*\]", lambda b: "[" + "\n" * b.group().count("\n") + "]", masked)
    original = text.splitlines()
    for n, line in enumerate(outside.splitlines(), 1):
        if re.match(r"^\s*\w+\s*=\s*\S", line) and not line.rstrip().endswith(";"):
            problems.append(f"line {n}: assignment without ';': {original[n - 1].strip()!r}")
    return problems


def _render(tmp_path):
    module_def, mgr = build_os_config()
    tpl_dir = tmp_path / "tpl" / "Os"
    tpl_dir.mkdir(parents=True)
    shutil.copy(TEMPLATE, tpl_dir / TEMPLATE.name)
    (tpl_dir / "Os_AppCommon.m").write_text(APP_COMMON_STUB, encoding="utf-8")
    gen = CodeGenerator(module_def, mgr.configuration, project_template_dir=tmp_path / "tpl")
    assert gen.generate_all(tmp_path / "out") is True
    return (tmp_path / "out" / "Os" / TEMPLATE.name).read_text(encoding="utf-8")


def test_checker_catches_the_known_defect_kinds():
    bad = '''IMPLEMENTATION X {
    OS {
        ENUM "t" [
            "A" = 0,
        ] COREID, "c";
        ENUM "p" [
            "R" = "&r"
            "-" = 0
        ] LOCKED, "l";
    }, "OS";
};
RESOURCE R {
    PRIORITY_TYPE = "x"
    PRIORITY = "y";
};
'''
    found = "\n".join(koil_problems(bad))
    assert "trailing ','" in found
    assert "missing ','" in found
    assert "PRIORITY_TYPE" in found


def test_rendered_orti_is_syntactically_sound(tmp_path):
    out = _render(tmp_path)
    assert 'KOIL = "2.2";' in out
    problems = koil_problems(out)
    assert not problems, "\n".join(problems)


COND = "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsResourceSubderivative = '{}'"


@pytest.mark.parametrize("derivative, cores", [("Os_THA6206", 2), ("Os_THA6412", 4), ("other", 1)])
def test_core_id_enum_per_derivative(tmp_path, derivative, cores):
    """The synthetic Os config has no OsResourceSubderivative, so the derivative tests are
    forced to true/false in a copy of the template to render each COREID branch."""
    src = TEMPLATE.read_text(encoding="utf-8")
    for d in ("Os_THA6206", "Os_THA6412"):
        src = src.replace(COND.format(d), "1 = 1" if d == derivative else "1 = 0")
    patched = tmp_path / "patched" / TEMPLATE.name
    patched.parent.mkdir()
    patched.write_text(src, encoding="utf-8")

    module_def, mgr = build_os_config()
    tpl_dir = tmp_path / "tpl" / "Os"
    tpl_dir.mkdir(parents=True)
    shutil.copy(patched, tpl_dir / TEMPLATE.name)
    (tpl_dir / "Os_AppCommon.m").write_text(APP_COMMON_STUB, encoding="utf-8")
    assert CodeGenerator(module_def, mgr.configuration,
                         project_template_dir=tmp_path / "tpl").generate_all(tmp_path / "out")
    out = (tmp_path / "out" / "Os" / TEMPLATE.name).read_text(encoding="utf-8")

    body = re.search(r'ENUM "CoreIdType" \[(.*?)\] COREID', out, re.S).group(1)
    assert re.findall(r'"OS_CORE_ID_(\d)" = (\d)', body) == [(str(i), str(i)) for i in range(cores)]
    assert not koil_problems(f"X {{ ENUM \"t\" [{body}] COREID, \"c\"; }};")


@pytest.mark.parametrize("var", ["MaxTask", "MaxIsr"])
def test_counters_initialised_before_use(var):
    """EB aborts on an undefined variable; the configurator silently reads it as 0,
    so this is checked statically: the [!VAR!] initialisation precedes the first use."""
    src = TEMPLATE.read_text(encoding="utf-8")
    init = src.find(f'[!VAR "{var}" = "0"!]')
    first_use = src.find(f"${var}")
    assert init != -1, f"{var} is never initialised to 0"
    assert init < first_use


def test_no_cat2_isr_still_defines_no_isr(tmp_path):
    """$MaxIsr must have a value even when no CATEGORY_2 ISR exists."""
    module_def, mgr = build_os_config()
    for c in list(mgr.configuration.containers):
        if c.definition_ref.endswith("/OsIsr"):
            c.set_parameter_value("OsIsrCategory", "CATEGORY_1",
                                  module_def.containers["OsIsr"].parameters["OsIsrCategory"].definition_ref)
    tpl_dir = tmp_path / "tpl" / "Os"
    tpl_dir.mkdir(parents=True)
    shutil.copy(TEMPLATE, tpl_dir / TEMPLATE.name)
    (tpl_dir / "Os_AppCommon.m").write_text(APP_COMMON_STUB, encoding="utf-8")
    assert CodeGenerator(module_def, mgr.configuration,
                         project_template_dir=tmp_path / "tpl").generate_all(tmp_path / "out")
    out = (tmp_path / "out" / "Os" / TEMPLATE.name).read_text(encoding="utf-8")
    assert re.search(r'"NO_ISR" = "0"', out), re.search(r'"NO_ISR"[^\n]*', out)

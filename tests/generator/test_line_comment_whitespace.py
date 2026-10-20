"""Whitespace around [!// line comments and [!INDENT!], as EB tresos writes it (checked against
EB's own Os output: Os_kernel_Lcfg.c, Os_isr_Cfg.h, Os_resource_Lcfg.c, Os_counter_Cfg.h)."""
from autosar_configurator.generator.eb.renderer import Renderer


def _render(template: str) -> str:
    return Renderer(strict=False).render(template)


def test_line_after_endindent_keeps_its_indentation():
    # Os_kernel_Lcfg.c: "[!ENDINDENT!][!//" followed by "    }," -> EB writes "    },"
    out = _render('{\n    {\n[!INDENT "8"!][!//\n        A,\n[!ENDINDENT!][!//\n    },\n};\n')
    assert out == '{\n    {\n        A,\n    },\n};\n'


def test_bare_line_comment_joins_lines_a_comment_with_text_does_not():
    assert _render('A[!//\nB\n') == 'AB\n'
    assert _render('A[!// note\nB\n') == 'A\nB\n'
    # "[!//" followed only by spaces is a comment too: the line break stays
    assert _render('A[!//   \nB\n') == 'A\nB\n'


def test_indentation_before_a_directive_after_line_comment_is_layout():
    # Os_isr_Cfg.h: "#define X ([!//" + indented directive lines + the value
    out = _render('#define X ([!//\n    [!VAR "a" = "5"!][!//\n        [!IF "1 = 1"!][!//\n[!"num:i($a)"!]UL)[!//\n    [!ENDIF!][!//\n\n')
    assert out == '#define X (5UL)\n'


def test_inside_indent_line_after_line_comment_loses_its_indentation_mid_line():
    # Os_resource_Lcfg.c: "[!"..."!]UL[!//" then "        ," on the next template line -> "0UL,"
    out = _render('[!INDENT "4"!][!//\n        [!"num:i(0)"!]UL[!//\n            ,\n        [!"num:i(1)"!]UL\n[!ENDINDENT!][!//\n')
    assert out == '    0UL,\n    1UL\n'


def test_var_line_does_not_swallow_the_next_lines_blank_line():
    # Os_counter_Cfg.h / Os_application_Cfg.h: "[!VAR ...!][!//" followed by an empty template line
    assert _render('A\n[!VAR "x" = "1"!][!//\n\nB\n') == 'A\n\nB\n'
    # a VAR line without [!// still drops its own line break
    assert _render('A\n[!VAR "x" = "1"!]\nB\n') == 'A\nB\n'


def test_var_line_with_comment_keeps_its_line_break():
    # Os_timingprotection_Lcfg.c: "[!VAR ...!][!//   " keeps the line break (EB writes the blank line)
    assert _render('A\n[!VAR "x" = "1"!][!//   \nB\n') == 'A\n\nB\n'

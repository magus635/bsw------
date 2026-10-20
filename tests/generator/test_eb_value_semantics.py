"""EB tresos value semantics (openspec align-eb-value-semantics, spec eb-template-value-semantics).

Expected values are what EB tresos 27.0.0 gives: its JXPath library and template commands
(ExpressionCommand / VarCommand / ForCommand) were run and decompiled for the design."""
import math

import pytest

from autosar_configurator.generator.eb import values as ebv
from autosar_configurator.generator.eb.renderer import Renderer
from autosar_configurator.generator.eb.symbol_table import ConfigurationNode


def _r(template: str) -> str:
    return Renderer(strict=False).render(template)


# ---- EB number types ------------------------------------------------------------------------

@pytest.mark.parametrize("expr, expected", [
    ("1+1", "2.0"),
    ("2 * 3", "6.0"),
    ("0", "0.0"),
    ("100000000", "1.0E8"),
    ("7 div 2", "3.5"),
    ("7 mod 2", "1.0"),
    ("num:i(1+1)", "2"),
    ("num:i('0x10')", "16"),
    ("bit:or(1, 2)", "3"),
    ("string-length('ab')", "2.0"),
    ("num:f(5)", "5.0"),
])
def test_number_types_and_output(expr, expected):
    assert _r('[!"' + expr + '"!]') == expected


def test_count_is_a_double():
    assert _r("[!VAR \"L\" = \"text:split('a,b,c', ',')\"!][!\"count($L)\"!]") == "3.0"


# ---- EB string conversion -------------------------------------------------------------------

@pytest.mark.parametrize("expr, expected", [
    ("1 < 2", "true"),
    ("1 > 2", "false"),
    ("concat('a', 1+1)", "a2"),          # XPath string(): no fractional part
    ("concat('a', 0.5)", "a0.5"),
    ("string(1+1)", "2"),
])
def test_string_conversion(expr, expected):
    assert _r('[!"' + expr + '"!]') == expected


# ---- variables hold strings -----------------------------------------------------------------

def test_numeric_literal_variable():
    assert _r('[!VAR "a" = "5"!][!"$a"!]') == "5.0"


def test_string_literal_variable():
    assert _r('[!VAR "a" = "\'5\'"!][!"$a"!]') == "5"


def test_integer_variable_keeps_its_decimal_text():
    assert _r('[!VAR "a" = "num:i(5)"!][!"$a"!]') == "5"
    assert _r('[!VAR "a" = "num:i(5)"!][!IF "$a = \'5\'"!]T[!ENDIF!]') == "T"


def test_boolean_variable():
    assert _r('[!VAR "a" = "1 < 2"!][!"$a"!]') == "true"


def test_loop_variable():
    assert _r('[!FOR "i" = "0" TO "1"!][!"$i"!],[!ENDFOR!]') == "0,1,"


def test_loop_variable_still_counts():
    assert _r('[!FOR "i" = "1" TO "3"!][!"num:i($i * 2)"!],[!ENDFOR!]') == "2,4,6,"


# ---- XPath 1.0 comparison -------------------------------------------------------------------

def _if(template_before: str, cond: str) -> str:
    return _r(template_before + '[!IF "' + cond + '"!]T[!ELSE!]F[!ENDIF!]')


def test_two_variables_compare_as_strings():
    # Os_task_Cfg.h: CeilingPriority = "0" is "0.0", the FOR counter is "0"
    assert _r('[!VAR "CeilingPriority" = "0"!][!FOR "i" = "0" TO "0"!]'
              '[!IF "$CeilingPriority = $i"!]T[!ELSE!]F[!ENDIF!][!ENDFOR!]') == "F"


def test_variable_and_number_literal_compare_as_numbers():
    assert _if('[!VAR "a" = "0"!]', "$a = 0") == "T"
    assert _if('[!VAR "a" = "5"!]', "$a > 4") == "T"


def test_variable_and_string_literal_compare_as_strings():
    assert _if('[!VAR "a" = "5"!]', "$a = '5'") == "F"
    assert _if('[!VAR "a" = "5"!]', "$a = '5.0'") == "T"


def test_bare_true_is_a_path_not_a_boolean():
    # Os ORTI: node:value(./OsOS/OsStackMonitoring) = true is always false in EB
    assert _if('[!VAR "a" = "\'true\'"!]', "$a = true") == "F"
    assert _if('[!VAR "a" = "\'true\'"!]', "$a = true()") == "T"


def test_quoted_string_literals():
    assert _r("[!\"'0.0' = '0'\"!]") == "false"
    assert _r("[!\"'0.0' = 0\"!]") == "true"


def test_string_variable_predicate_is_a_boolean():
    # [$i] with a string $i keeps every item (the first one prints); a number selects that position
    loop = "[!FOR \"i\" = \"2\" TO \"2\"!]{}[!ENDFOR!]"
    assert _r(loop.format("[!\"text:split('a,b,c', ',')[num:i($i)]\"!]")) == "b"
    assert _r(loop.format("[!\"text:split('a,b,c', ',')[$i]\"!]")) == "a"


# ---- values.compare on configuration nodes ---------------------------------------------------

def _param(name, value, param_type="INTEGER"):
    return ConfigurationNode(short_name=name, node_type="parameter", path=f"/M/{name}",
                             value=value, param_type=param_type)


def test_node_values_compare_by_their_text():
    prio = _param("OsTaskPriority", 1)
    assert ebv.compare("=", prio, 1.0)              # node and number: numbers
    assert ebv.compare("=", prio, "1")              # node and string: strings
    assert not ebv.compare("=", prio, "1.0")
    assert ebv.compare("=", [_param("A", 2), prio], 1.0)    # any node of the node-set
    assert not ebv.compare("=", None, "x")          # an empty node-set equals nothing
    assert not ebv.compare("!=", None, "x")


def test_boolean_node_text():
    assert ebv.node_text(_param("B", True, "BOOLEAN")) == "true"
    assert ebv.node_text(_param("B", "0", "BOOLEAN")) == "false"
    assert ebv.compare("=", _param("B", 1, "BOOLEAN"), "true")


def test_format_double():
    assert ebv.format_double(2.0) == "2.0"
    assert ebv.format_double(1e8) == "1.0E8"
    assert ebv.format_double(1e7) == "1.0E7"
    assert ebv.format_double(0.0005) == "5.0E-4"
    assert ebv.format_double(math.nan) == "NaN"


@pytest.mark.parametrize("expr, path_like", [
    ("OsTask/*[OsTaskPriority = $i]", True),
    ("../OsTaskPriority", True),
    ("$x/OsTaskPriority", True),
    ("node:ref(./OsTaskResourceRef)/OsResourceProperty", True),
    ("as:modconf('Os')[1]/OsTask", True),
    ("$x", False),
    ("'abc'", False),
    ("5", False),
    ("$a + 1", False),
    ("num:i($a)", False),
    ("count(OsTask/*)", False),
])
def test_is_path_like(expr, path_like):
    assert ebv.is_path_like(expr) is path_like

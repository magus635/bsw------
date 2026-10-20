"""XPath 1.0 comparison semantics of the EB renderer (openspec align-eb-value-semantics): a number
on one side compares numbers, two strings compare as strings, empty selections equal nothing,
'or' binds looser than 'and', an index past the end of a list selects nothing, and a boolean
prints as Java does (true / false)."""
import pytest

from autosar_configurator.generator.eb.renderer import Renderer

LIST = "[!VAR \"L\" = \"'0,100,1,0,'\"!][!VAR \"S\" = \"','\"!][!VAR \"i\" = \"2\"!]"


def _eval(expr: str) -> str:
    return Renderer(strict=False).render(LIST + '[!"' + expr + '"!]')


@pytest.mark.parametrize("expr, expected", [
    ("text:split($L, $S)[2] = 0", "false"),        # '100' is not 0
    ("text:split($L, $S)[2] = 100", "true"),
    ("text:split($L, $S)[1] = 100", "false"),      # '0' is not 100
    ("'0xFFFFFFFF' = 0", "false"),                 # Os ceiling priority of a RES_SCHEDULER-linked resource
    ("'01' = 1", "true"),
    ("1 = 1.0", "true"),
])
def test_numbers_compare_as_numbers(expr, expected):
    assert _eval(expr) == expected


@pytest.mark.parametrize("expr, expected", [
    ("'01' = '1'", "false"),                       # two strings compare as strings
    ("'0.0' = '0'", "false"),
    ("'0.0' = 0", "true"),
    ("1 = 'true'", "false"),                       # 'true' is not a number
    ("0 != 'true'", "true"),
])
def test_strings_compare_as_strings(expr, expected):
    assert _eval(expr) == expected


def test_empty_selection_equals_nothing():
    assert _eval("text:split('', $S) = 0") == "false"
    assert _eval("text:split($L, $S)[5] = 0") == "false"
    assert _eval("text:split($L, $S)[5] != 0") == "false"


def test_index_past_the_end_selects_nothing():
    assert _eval("text:split($L, $S)[5]") == ""
    assert _eval("text:split($L, $S)[4]") == "0"


def test_or_binds_looser_than_and():
    assert _eval("1 = 1 or 2 = 3 and 1 = 0") == "true"     # 1=1 or (2=3 and 1=0)
    assert _eval("1 = 0 or 1 = 1 and 2 = 3") == "false"    # 1=0 or (1=1 and 2=3)


@pytest.mark.parametrize("expr, expected", [
    ("1 != 2", "true"),                            # '!=' is one operator, not '!' and '='
    ("3 != 3", "false"),
    ("3 >= 3", "true"),
    ("2 <= 1", "false"),
])
def test_two_character_operators(expr, expected):
    assert _eval(expr) == expected


def _if(cond: str) -> str:
    return Renderer(strict=False).render(LIST + '[!IF "' + cond + '"!]T[!ELSE!]F[!ENDIF!]')


def test_or_binds_looser_than_and_in_conditions():
    assert _if("1 = 1 or 2 = 3 and 1 = 0") == "T"
    assert _if("1 = 0 or 1 = 1 and 2 = 3") == "F"
    assert _if("1 = 0 and 2 = 3 or 1 = 1") == "T"         # (1=0 and 2=3) or 1=1


def test_position_predicate_on_ordered_list():
    # Os ORTI: num:order(text:split(list))[position() = $i+1] picks one priority
    assert _eval("num:order(text:split($L, $S))[position() = $i+1] = 100") == "true"
    assert _eval("num:order(text:split($L, $S))[position() = $i+1] = 0") == "false"

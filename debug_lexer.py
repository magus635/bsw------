import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
from autosar_configurator.generator.eb.lexer import Lexer

template = """/**
 * @file Adc_EB_Test.h
 * EB Syntax Test
 */
[!VAR "TotalHW"="0"!]
[!LOOP "AdcConfigSet/AdcHwUnit"!][!//]
    [!VAR "TotalHW"="$TotalHW + 1"!]
    #define ADC_HW_UNIT_[!"node:name(.)"!]    [!"node:value(./AdcHwUnitId)"!]
[!ENDLOOP!]

#define ADC_TOTAL_HW_UNITS    [!"$TotalHW"!]
"""

lexer = Lexer()
tokens = lexer.tokenize(template)
for i, t in enumerate(tokens):
    print(f"{i}: {t.type.name} at {t.line}:{t.column} | Content: {repr(t.content)}")

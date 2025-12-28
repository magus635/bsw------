/**
 * @file Adc_EB_Test.h
 * EB Syntax Test
 */
[!VAR "TotalHW"="0"!]
[!LOOP "AdcConfigSet/AdcHwUnit"!][!//!]
    [!VAR "TotalHW"="$TotalHW + 1"!]
    #define ADC_HW_UNIT_[!"node:name(.)"!]    [!"node:value(./AdcHwUnitId)"!]
[!ENDLOOP!]

#define ADC_TOTAL_HW_UNITS    [!"$TotalHW"!]

/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_counter_Cfg.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Genaration Time       : [!"$datetime"!]
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_COUNTER_CFG_H_
#define OS_COUNTER_CFG_H_


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "common.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCounter"!][!//
[!VAR "Software" = "0"!][!//
[!VAR "HRTimer" = "0"!][!//
[!VAR "FRTimer" = "0"!][!//
[!VAR "PITimer" = "0"!][!//
[!LOOP "node:order(./*,'@index')"!][!//
    [!IF "./OsCounterType = 'SOFTWARE'"!][!//
        [!VAR "Software" = "$Software + 1"!][!//
    [!ELSEIF "./OsTimerHighResolution = 'true'"!][!//
        [!VAR "HRTimer" = "$HRTimer + 1"!][!//
    [!ELSEIF "node:ref(OsTimerTypeIsrRef)/OsIsrPriority = 27 or 
        node:ref(OsTimerTypeIsrRef)/OsIsrPriority = 30"!][!//
        [!VAR "FRTimer" = "$FRTimer + 1"!][!//
    [!ELSE!][!//
        [!VAR "PITimer" = "$PITimer + 1"!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "num:i($Software) = 0"!][!//
#define   OS_CFG_COUNTER_SOFTWARE_USED           (STD_OFF)
[!ELSE!][!//
#define   OS_CFG_COUNTER_SOFTWARE_USED           (STD_ON)
[!ENDIF!][!//

[!IF "num:i($HRTimer) = 0"!][!//
#define   OS_CFG_COUNTER_HRTTIMER_USED           (STD_OFF)
[!ELSE!][!//
#define   OS_CFG_COUNTER_HRTTIMER_USED           (STD_ON)
[!ENDIF!][!//

[!IF "num:i($FRTimer) = 0"!][!//
#define   OS_CFG_COUNTER_FRTTIMER_USED           (STD_OFF)
[!ELSE!][!//
#define   OS_CFG_COUNTER_FRTTIMER_USED           (STD_ON)
[!ENDIF!][!//

[!IF "num:i($PITimer) = 0"!][!//
#define   OS_CFG_COUNTER_PITTIMER_USED           (STD_OFF)
[!ELSE!][!//
#define   OS_CFG_COUNTER_PITTIMER_USED           (STD_ON)
[!ENDIF!][!//

[!LOOP "node:order(./*,'@index')"!][!//
    [!VAR "TotalObjects" = "0"!][!//
    [!VAR "CounterName" = "node:name(.)"!][!//
    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsAlarm/*, '@index')"!][!//
        [!IF "$CounterName = node:name(node:ref(./OsAlarmCounterRef))"!][!//
            [!VAR "TotalObjects" = "$TotalObjects + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//

    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsScheduleTable/*, '@index')"!][!//
        [!IF "$CounterName = node:name(node:ref(./OsScheduleTableCounterRef))"!][!//
            [!VAR "TotalObjects" = "$TotalObjects + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
#define   OS_CFG_COUNTER_NUM_[!"text:toupper($CounterName)"!]_OBJECTS    ([!"num:i($TotalObjects)"!]u)
[!ENDLOOP!][!//

[!LOOP "node:order(./*,'@index')"!][!//
#define   [!"text:toupper(node:name(.))"!]                            ([!"./@index"!]u)
[!ENDLOOP!][!//
#define   OS_COUNTER_TOTAL_NUM                   ([!"num:i(count(./*))"!]u)
#define   INVALID_COUNTER                        OS_COUNTER_TOTAL_NUM

#define   OS_COUNTER_MAX_OBJECT_EXECS_PER_LOCK   (4u)

[!LOOP "node:order(./*,'@index')"!][!//
    [!IF "OsCounterType = 'HARDWARE'"!][!//
        [!VAR "Multiple" = "0"!][!//
        [!VAR "RoundNumerater" = "0"!][!//
        [!VAR "RoundDenominator" = "1"!][!//
        [!IF "(OsSecondsPerTick * 1000000000) > 0"!][!//
            [!VAR "Multiple" = "num:i(OsSecondsPerTick * 1000000000)"!][!//
            [!VAR "RoundNumerater" = "0"!][!//
            [!VAR "RoundDenominator" = "1"!][!//
        [!ELSE!][!//
            [!FOR "i" = "0" TO "string-length(OsSecondsPerTick * 1000000000)"!][!//
                [!VAR "RoundDenominator" = "$RoundDenominator * 10"!][!//
                [!IF "(OsSecondsPerTick * 1000000000 * $RoundDenominator) >= 1"!][!//
                    [!BREAK!][!//
                [!ENDIF!]
            [!ENDFOR!][!//
            [!VAR "Multiple" = "num:i(floor(OsSecondsPerTick * 1000000000 * $RoundDenominator))"!][!//
            [!VAR "RoundNumerater" = "num:i($RoundDenominator div 2)"!][!//
        [!ENDIF!][!//
        #define OS_TICKS2NS_[!"node:name(.)"!](x)   ((uint32)(((((uint32)(x)) * [!"$Multiple"!]) + [!"num:i($RoundNumerater)"!]) / [!"num:i($RoundDenominator)"!]))
        [!IF "($Multiple div 1000) >= 1"!][!//
            [!VAR "Multiple" = "num:i($Multiple div 1000)"!][!//
            [!VAR "RoundNumerater" = "0"!][!//
            [!VAR "RoundDenominator" = "1"!][!//
        [!ELSE!][!//
            [!VAR "RoundDenominator" = "1"!][!//
            [!FOR "i" = "0" TO "string-length(OsSecondsPerTick * 1000000)"!][!//
                [!VAR "RoundDenominator" = "$RoundDenominator * 10"!][!//
                [!IF "(OsSecondsPerTick * 1000000 * $RoundDenominator) >= 1"!][!//
                    [!BREAK!][!//
                [!ENDIF!]
            [!ENDFOR!][!//
            [!VAR "Multiple" = "num:i(floor(OsSecondsPerTick * 1000000 * $RoundDenominator))"!][!//
            [!VAR "RoundNumerater" = "num:i($RoundDenominator div 2)"!][!//
        [!ENDIF!][!//
        #define OS_TICKS2US_[!"node:name(.)"!](x)   ((uint32)(((((uint32)(x)) * [!"$Multiple"!]) + [!"num:i($RoundNumerater)"!]) / [!"num:i($RoundDenominator)"!]))
        [!IF "($Multiple div 1000) >= 1"!][!//
            [!VAR "Multiple" = "num:i($Multiple div 1000)"!][!//
            [!VAR "RoundNumerater" = "0"!][!//
            [!VAR "RoundDenominator" = "1"!][!//
        [!ELSE!][!//
            [!VAR "RoundDenominator" = "1"!][!//
            [!FOR "i" = "0" TO "string-length(OsSecondsPerTick * 1000)"!][!//
                [!VAR "RoundDenominator" = "$RoundDenominator * 10"!][!//
                [!IF "(OsSecondsPerTick * 1000 * $RoundDenominator) >= 1"!][!//
                    [!BREAK!][!//
                [!ENDIF!]
            [!ENDFOR!][!//
            [!VAR "Multiple" = "num:i(floor(OsSecondsPerTick * 1000 * $RoundDenominator))"!][!//
            [!VAR "RoundNumerater" = "num:i($RoundDenominator div 2)"!][!//
        [!ENDIF!][!//
        #define OS_TICKS2MS_[!"node:name(.)"!](x)   ((uint32)(((((uint32)(x)) * [!"$Multiple"!]) + [!"num:i($RoundNumerater)"!]) / [!"num:i($RoundDenominator)"!]))
        [!IF "($Multiple div 1000) >= 1"!][!//
            [!VAR "Multiple" = "num:i($Multiple div 1000)"!][!//
            [!VAR "RoundNumerater" = "0"!][!//
            [!VAR "RoundDenominator" = "1"!][!//
        [!ELSE!][!//
            [!VAR "RoundDenominator" = "1"!][!//
            [!FOR "i" = "0" TO "string-length(OsSecondsPerTick * 1)"!][!//
                [!VAR "RoundDenominator" = "$RoundDenominator * 10"!][!//
                [!IF "(OsSecondsPerTick * 1 * $RoundDenominator) >= 1"!][!//
                    [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!VAR "Multiple" = "num:i(floor(OsSecondsPerTick * 1 * $RoundDenominator))"!][!//
            [!VAR "RoundNumerater" = "num:i($RoundDenominator div 2)"!][!//
        [!ENDIF!][!//
        #define OS_TICKS2SEC_[!"node:name(.)"!](x)   ((uint32)(((((uint32)(x)) * [!"$Multiple"!]) + [!"num:i($RoundNumerater)"!]) / [!"num:i($RoundDenominator)"!]))

    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/




#endif /* OS_COUNTER_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_counter_Cfg.h                                                               **
****************************************************************************************************/


/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timer_Lcfg.c
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


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_timer_Lcfg.h"
#include "Os_timer_hal.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Type Definitions                                                **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Structure Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'OsPhysicalCoreId')"!][!//
        [!VAR "CurrentPhysicalCoreId" = "OsPhysicalCoreId"!][!//
        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
            [!VAR "IsTrusted" = "node:value(./OsTrusted)"!][!//
            [!LOOP "node:order(./OsAppCounterRef/*,'@index')"!][!//
                [!IF "node:value(node:ref(.)/OsCounterType) = 'SOFTWARE'"!][!//
                [!ELSEIF "node:value(node:ref(.)/OsTimerHighResolution) = 'false'"!][!//
                [!ELSE!][!//
                    [!IF "$IsTrusted = 'true'"!][!//
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i($CurrentPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                    [!ELSE!][!//
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i($CurrentPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                    [!ENDIF!][!//
                    [!IF "num:i(node:ref(node:ref(.)/OsTimerTypeIsrRef)/OsIsrInterruptSource) = 30"!][!//
                        static Os_TimerHrtRunningDataType OsTimer_Hal_[!"node:name(node:ref(.))"!]RunningData;
                    [!ELSE!][!//
                        static Os_TimerHrtRunningDataType OsTimer_Hal_[!"node:name(node:ref(.))"!]RunningData;
                    [!ENDIF!][!//
                    [!IF "$IsTrusted = 'true'"!][!//
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i($CurrentPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                    [!ELSE!][!//
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i($CurrentPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                    [!ENDIF!][!//

                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCounter"!][!//
[!LOOP "node:order(./*,'@index')"!][!//
    [!IF "node:value(./OsCounterType) = 'SOFTWARE'"!][!//
    [!ELSEIF "node:value(./OsTimerHighResolution) = 'false'"!]
        [!IF "node:ref(./OsTimerTypeIsrRef)/OsIsrInterruptSource = 30"!][!//
        const Os_TimerFrtHwConfigType OsTimer_Hal_[!"node:name(.)"!]HwCfg =
        {
            [!INDENT "4"!][!//
            OsTimer_Hal_EL1PhyTimerInit,                   /* Init */
            OsTimer_Hal_EL1PhyTimerAckInterrupt,           /* AckInterrupt */
            OsTimer_Hal_EL1PhyTimerGetCounterRegValue,     /* GetCounterRegValue  */
            OsTimer_Hal_EL1PhyTimerGetCompareRegValue,     /* GetCompareRegValue  */ 
            OsTimer_Hal_EL1PhyTimerSetCompareRegValue,     /* SetCompareRegValue  */
            30ul,                                          /* IsrID */
            [!"num:i(./OsCounterTicksPerBase)"!]ul,                                       /* Period */
            0x7FFFFFFFFFFFFFFFul,                          /* MaxCounterRegisterValue */
            0x7FFFFFFFul                                   /* MaxDifferenceValue */
            [!ENDINDENT!][!//
        };
        [!ELSEIF "num:i(node:ref(./OsTimerTypeIsrRef)/OsIsrInterruptSource) = 27"!][!//
        const Os_TimerFrtHwConfigType OsTimer_Hal_[!"node:name(.)"!]HwCfg =
        {
            [!INDENT "4"!][!//
            OsTimer_Hal_EL1VirtTimerInit,                   /* Init */
            OsTimer_Hal_EL1VirtTimerAckInterrupt,           /* AckInterrupt */
            OsTimer_Hal_EL1VirtTimerGetCounterRegValue,     /* GetCounterRegValue  */
            OsTimer_Hal_EL1VirtTimerGetCompareRegValue,     /* GetCompareRegValue  */ 
            OsTimer_Hal_EL1VirtTimerSetCompareRegValue,     /* SetCompareRegValue  */
            27ul,                                          /* IsrID */
            [!"num:i(./OsCounterTicksPerBase)"!]ul,                                       /* Period */
            0x7FFFFFFFFFFFFFFFul,                          /* MaxCounterRegisterValue */
            0x7FFFFFFFul                                  /* MaxDifferenceValue */
            [!ENDINDENT!][!//
        };
        [!ELSE!][!//
        const Os_TimerPitHwConfigType OsTimer_Hal_[!"node:name(.)"!]HwCfg =
        {
            [!INDENT "4"!][!//
            OsTimer_Hal_[!"node:name(.)"!]Init,                       /* Init */
            OsTimer_Hal_[!"node:name(.)"!]AckAndReloadInterrupt,  /* PitAckAndReloadInterrupt  */ 
            [!"num:i(node:ref(./OsTimerTypeIsrRef)/OsIsrInterruptSource)"!]ul,                            /* IsrID */
            [!"num:i(./OsCounterTicksPerBase)"!]ul                       /* Period */
            [!ENDINDENT!][!//
        };        
        [!ENDIF!][!//
    [!ELSE!][!//
        [!IF "num:i(node:ref(./OsTimerTypeIsrRef)/OsIsrInterruptSource) = 30"!][!//
        const Os_TimerHrtHwConfigType OsTimer_Hal_[!"node:name(.)"!]HwCfg =
        {
            [!INDENT "4"!][!//
            OsTimer_Hal_EL1PhyTimerInit,                   /* Init */
            OsTimer_Hal_EL1PhyTimerAckInterrupt,           /* AckInterrupt */
            OsTimer_Hal_EL1PhyTimerGetCounterRegValue,     /* GetCounterRegValue  */
            OsTimer_Hal_EL1PhyTimerGetCompareRegValue,     /* GetCompareRegValue  */ 
            OsTimer_Hal_EL1PhyTimerSetCompareRegValue,     /* SetCompareRegValue  */
            30ul,                                          /* IsrID */
            0x7FFFFFFFFFFFFFFFul,                          /* MaxCounterRegisterValue */
            0x7FFFFFFFul,                                  /* MaxDifferenceValue */
            &OsTimer_Hal_[!"node:name(.)"!]RunningData      /* RunningData */
            [!ENDINDENT!][!//
        };
        [!ELSE!][!//
        const Os_TimerHrtHwConfigType OsTimer_Hal_[!"node:name(.)"!]HwCfg =
        {
            [!INDENT "4"!][!//
            OsTimer_Hal_EL1VirtTimerInit,                   /* Init */
            OsTimer_Hal_EL1VirtTimerAckInterrupt,           /* AckInterrupt */
            OsTimer_Hal_EL1VirtTimerGetCounterRegValue,     /* GetCounterRegValue  */
            OsTimer_Hal_EL1VirtTimerGetCompareRegValue,     /* GetCompareRegValue  */ 
            OsTimer_Hal_EL1VirtTimerSetCompareRegValue,     /* SetCompareRegValue  */
            27ul,                                           /* IsrID */
            0x7FFFFFFFFFFFFFFFul,                           /* MaxCounterRegisterValue */
            0x7FFFFFFFul,                                   /* MaxDifferenceValue */
            &OsTimer_Hal_[!"node:name(.)"!]RunningData      /* RunningData */
            [!ENDINDENT!][!//
        };
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//

[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/






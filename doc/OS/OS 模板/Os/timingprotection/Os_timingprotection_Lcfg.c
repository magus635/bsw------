/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timingprotection_Lcfg.c
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
#include "Os_timingprotection_types.h"
#include "Os_timingprotection_Cfg.h"
#include "Os_timingprotection_Lcfg.h"
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
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
        [!VAR "CurrentCoreID" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//   
        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
        [!IF "$CurrentCoreID = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
        #define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h" 
            [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1])"!][!//
                    [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskExecutionBudget)"!][!//
                        static Os_TpBudgetRunningDataType   Os_[!"node:name(node:ref(.))"!]ExecutionBudgetData;
                    [!ENDIF!][!//
                    [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskAllInterruptLockBudget)"!][!//
                        static Os_TpBudgetRunningDataType   Os_[!"node:name(node:ref(.))"!]LockAllInterruptBudgetData;
                    [!ENDIF!][!//
                    [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskResourceLock/*[1])"!][!//
                        [!LOOP "node:order(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskResourceLock/*,'@index')"!][!//
                            static Os_TpBudgetRunningDataType   Os_[!"node:name(./../../../..)"!]Lock[!"node:name(node:ref(./OsTaskResourceLockResourceRef))"!]BudgetData;
                        [!ENDLOOP!][!//
                    [!ENDIF!][!//
                    [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskOsInterruptLockBudget)"!][!//
                        static Os_TpBudgetRunningDataType   Os_[!"node:name(node:ref(.))"!]LockOsInterruptBudgetData;
                    [!ENDIF!][!//
                    static Os_TpObjectRunningDataType   Os_[!"node:name(node:ref(.))"!]TimingProtectionRunningData;
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        #define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h"
        [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
        [!VAR "CurrentCoreID" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
        [!IF "$CurrentCoreID = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
            [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
            [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1])"!][!//
        #define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./../../OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h"
                [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrExecutionBudget)"!][!//
                    static Os_TpBudgetRunningDataType   Os_[!"node:name(node:ref(.))"!]ExecutionBudgetData;
                [!ENDIF!][!//
                [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrAllInterruptLockBudget)"!][!//
                    static Os_TpBudgetRunningDataType   Os_[!"node:name(node:ref(.))"!]LockAllInterruptBudgetData;
                [!ENDIF!][!//
                [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrResourceLock/*[1])"!][!//
                    [!LOOP "node:order(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrResourceLock/*,'@index')"!][!//
                        static Os_TpBudgetRunningDataType   Os_[!"node:name(./../../../..)"!]Lock[!"node:name(node:ref(./OsIsrResourceLockResourceRef))"!]BudgetData;
                    [!ENDLOOP!][!//
                [!ENDIF!][!//
                [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrOsInterruptLockBudget)"!][!//
                    static Os_TpBudgetRunningDataType   Os_[!"node:name(node:ref(.))"!]LockOsInterruptBudgetData;
                [!ENDIF!][!//
                static Os_TpObjectRunningDataType   Os_[!"node:name(node:ref(.))"!]TimingProtectionRunningData;
        #define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./../../OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h"
            [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,"@index")"!][!//
        [!LOOP "node:order(./OsAppTaskRef/*,"@index")"!][!//
        [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1])"!][!//
        [!VAR "OsSecondsPerTick" = "node:value(node:ref(node:ref(./../../OsApplicationCoreRef)/OsTpCounterRef)/OsSecondsPerTick)"!][!//
            [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskResourceLock/*[1])"!][!//
                [!LOOP "node:order(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskResourceLock/*,"@index")"!][!//
                    static const Os_TpBudgetConfigType Os_[!"node:name(./../../../..)"!][!"node:name(node:ref(./OsTaskResourceLockResourceRef))"!]BudgetConfig =
                    {
                        [!INDENT "4"!][!//
                        TP_MONITOR_LOCK, /* Type */
                        [!"num:i(node:value(./OsTaskResourceLockBudget) div $OsSecondsPerTick)"!],          /* Budget */
                        &Os_[!"node:name(./../../../..)"!]Lock[!"node:name(node:ref(./OsTaskResourceLockResourceRef))"!]BudgetData
                        [!ENDINDENT!][!//
                    };

                    static const Os_TpReSourceBudgetConfigType Os_[!"node:name(./../../../..)"!][!"node:name(node:ref(./OsTaskResourceLockResourceRef))"!]TpConfig =
                    {
                        [!INDENT "4"!][!//
                        [!"node:ref(./OsTaskResourceLockResourceRef)/@index"!],  /* ResourceID */
                        &Os_[!"node:name(./../../../..)"!][!"node:name(node:ref(./OsTaskResourceLockResourceRef))"!]BudgetConfig
                        [!ENDINDENT!][!//
                    };

                [!ENDLOOP!][!//
                static const Os_TpReSourceBudgetConfigRefType Os_[!"node:name(node:ref(.))"!]ResourceTpConfig[[!"num:i(count(.) + 1)"!]] =
                {
                    [!INDENT "4"!][!//
                    [!LOOP "node:order(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskResourceLock/*,"@index")"!][!//
                    &Os_[!"node:name(./../../../..)"!][!"node:name(node:ref(./OsTaskResourceLockResourceRef))"!]TpConfig,
                    [!ENDLOOP!][!//
                    NULL_PTR,
                    [!ENDINDENT!][!//
                };
            [!ENDIF!][!//

            static const Os_TpObjectConfigType Os_[!"node:name(node:ref(.))"!]TpConfig =
            {
                [!INDENT "4"!][!//
                [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskTimeFrame)"!][!//
                    [!"num:i(node:value(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskTimeFrame) div $OsSecondsPerTick)"!]U,                                 
                [!ELSE!][!//
                    0U,                            
                [!ENDIF!][!//
                {
                    [!INDENT "8"!][!//
                    [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskExecutionBudget)"!][!//
                        TP_MONITOR_EXECUTION,
                        [!"num:i(node:value(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskExecutionBudget) div $OsSecondsPerTick)"!]U,
                        &Os_[!"node:name(node:ref(.))"!]ExecutionBudgetData
                    [!ELSE!][!//
                        TP_MONITOR_NONE,
                        0U,
                        NULL_PTR
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                },
                {
                    [!INDENT "8"!][!//
                    [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskAllInterruptLockBudget)"!][!//
                        TP_MONITOR_LOCK,
                        [!"num:i(node:value(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskAllInterruptLockBudget) div $OsSecondsPerTick)"!]U,
                        &Os_[!"node:name(node:ref(.))"!]LockAllInterruptBudgetData
                    [!ELSE!][!//
                        TP_MONITOR_NONE,
                        0U,
                        NULL_PTR
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                },
                {
                    [!INDENT "8"!][!//
                    [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskOsInterruptLockBudget)"!][!//
                        TP_MONITOR_LOCK,
                        [!"num:i(node:value(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskOsInterruptLockBudget) div $OsSecondsPerTick)"!]U,
                        &Os_[!"node:name(node:ref(.))"!]LockOsInterruptBudgetData
                    [!ELSE!][!//
                        TP_MONITOR_NONE,
                        0U, 
                        NULL_PTR
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                },
                [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1]/OsTaskResourceLock/*[1])"!][!//
                    &Os_[!"node:name(node:ref(.))"!]ResourceTpConfig[0],
                [!ELSE!][!//
                    NULL_PTR,
                [!ENDIF!][!//
                    &Os_[!"node:name(node:ref(.))"!]TimingProtectionRunningData
                [!ENDINDENT!][!//
            };

        [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,"@index")"!][!//
        [!LOOP "node:order(./OsAppIsrRef/*,"@index")"!][!//
        [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1])"!][!//
        [!VAR "OsSecondsPerTick" = "node:value(node:ref(node:ref(./../../OsApplicationCoreRef)/OsTpCounterRef)/OsSecondsPerTick)"!][!//
            [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrResourceLock/*[1])"!][!//
                [!LOOP "node:order(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrResourceLock/*,"@index")"!][!//
                    static const Os_TpBudgetConfigType Os_[!"node:name(./../../../..)"!][!"node:name(node:ref(./OsIsrResourceLockResourceRef))"!]BudgetConfig =
                    {
                        [!INDENT "4"!][!//
                        TP_MONITOR_LOCK, /* Type */
                        [!"num:i(node:value(./OsIsrResourceLockBudget) div $OsSecondsPerTick)"!],          /* Budget */
                        &Os_[!"node:name(./../../../..)"!]Lock[!"node:name(node:ref(./OsIsrResourceLockResourceRef))"!]BudgetData
                        [!ENDINDENT!][!//
                    };

                    static const Os_TpReSourceBudgetConfigType Os_[!"node:name(./../../../..)"!][!"node:name(node:ref(./OsIsrResourceLockResourceRef))"!]TpConfig =
                    {
                        [!INDENT "4"!][!//
                        [!"node:ref(./OsIsrResourceLockResourceRef)/@index"!],  /* ResourceID */
                        &Os_[!"node:name(./../../../..)"!][!"node:name(node:ref(./OsIsrResourceLockResourceRef))"!]BudgetConfig
                        [!ENDINDENT!][!//
                    };

                [!ENDLOOP!][!//
                static const Os_TpReSourceBudgetConfigRefType Os_[!"node:name(node:ref(.))"!]ResourceTpConfig[[!"num:i(count(.) + 1)"!]] =
                {
                    [!INDENT "4"!][!//
                    [!LOOP "node:order(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrResourceLock/*,"@index")"!][!//
                    &Os_[!"node:name(./../../../..)"!][!"node:name(node:ref(./OsIsrResourceLockResourceRef))"!]TpConfig,
                    [!ENDLOOP!][!//
                    NULL_PTR,
                    [!ENDINDENT!][!//
                };
            [!ENDIF!][!//

            static const Os_TpObjectConfigType Os_[!"node:name(node:ref(.))"!]TpConfig =
            {
                [!INDENT "4"!][!//
                [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrTimeFrame)"!][!//
                    [!"num:i(node:value(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrTimeFrame) div $OsSecondsPerTick)"!]U,                                 
                [!ELSE!][!//
                    0U,                         
                [!ENDIF!][!//
                {
                    [!INDENT "8"!][!//
                    [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrExecutionBudget)"!][!//
                        TP_MONITOR_EXECUTION,
                        [!"num:i(node:value(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrExecutionBudget) div $OsSecondsPerTick)"!]U,
                        &Os_[!"node:name(node:ref(.))"!]ExecutionBudgetData
                    [!ELSE!][!//
                        TP_MONITOR_NONE,
                        0U,
                        NULL_PTR
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                },
                {
                    [!INDENT "8"!][!//
                    [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrAllInterruptLockBudget)"!][!//
                        TP_MONITOR_LOCK,
                        [!"num:i(node:value(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrAllInterruptLockBudget) div $OsSecondsPerTick)"!]U,
                        &Os_[!"node:name(node:ref(.))"!]LockAllInterruptBudgetData
                    [!ELSE!][!//
                        TP_MONITOR_NONE,
                        0U,
                        NULL_PTR
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                },
                {
                    [!INDENT "8"!][!//
                    [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrOsInterruptLockBudget)"!][!//
                        TP_MONITOR_LOCK,
                        [!"num:i(node:value(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrOsInterruptLockBudget) div $OsSecondsPerTick)"!]U,
                        &Os_[!"node:name(node:ref(.))"!]LockOsInterruptBudgetData
                    [!ELSE!][!//
                        TP_MONITOR_NONE,
                        0U, 
                        NULL_PTR
                    [!ENDIF!][!//
                    [!ENDINDENT!][!//
                },
                [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1]/OsIsrResourceLock/*[1])"!][!//
                    &Os_[!"node:name(node:ref(.))"!]ResourceTpConfig[0],
                [!ELSE!][!//
                    NULL_PTR,
                [!ENDIF!][!//
                    &Os_[!"node:name(node:ref(.))"!]TimingProtectionRunningData
                [!ENDINDENT!][!//
            };

        [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//


[!VAR "TotalTpUsedNumber" = "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,"@index")"!][!//
        [!LOOP "node:order(./OsAppTaskRef/*,"@index")"!][!//
            [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1])"!][!//
                [!VAR "TotalTpUsedNumber" = "$TotalTpUsedNumber + 1"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!LOOP "node:order(./OsAppIsrRef/*,"@index")"!][!//
            [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1])"!][!//
                [!VAR "TotalTpUsedNumber" = "$TotalTpUsedNumber + 1"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
[!IF "$TotalTpUsedNumber != 0"!][!//
CONSTP2CONST(Os_TpObjectConfigType, TYPEDEF, OS_CONST) Os_TimingProection_ObjSet[TOTAL_TPUSED_NUM] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(./*,"@index")"!][!//
        [!LOOP "node:order(./OsAppTaskRef/*,"@index")"!][!//
            [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1])"!][!//
                &Os_[!"node:name(node:ref(.))"!]TpConfig,
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!LOOP "node:order(./OsAppIsrRef/*,"@index")"!][!//
            [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1])"!][!//
                &Os_[!"node:name(node:ref(.))"!]TpConfig,
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Global Constant Definitions                                            **
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






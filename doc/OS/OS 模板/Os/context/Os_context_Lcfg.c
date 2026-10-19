/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_context_Lcfg.c
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
#include "Os_context_Cfg.h"
#include "Os_context_Lcfg.h"
#include "Os_mpu_Lcfg.h"
#include "Os_task.h"
#include "Os_isr.h"
#include "Os_ioc.h"
#include "Os_ioc_Lcfg.h"
#include "Os_counter.h"
#include "Os_isr_Lcfg.h"
#include "Os_hook.h"
#include "Os_kernel.h"
#include "Os_hook_Lcfg.h"
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

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "ErrorHookFlag"="'false'"!][!//
[!VAR "StartupHookFlag"="'false'"!][!//
[!VAR "ShutdownHookFlag"="'false'"!][!//
[!VAR "ProtectionHookFlag"="'false'"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
        [!VAR "CurrentCoreID" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
#define OS_START_SEC_STACKCFG_QM_CORE[!"num:i(./OsPhysicalCoreId)"!]_32
#include "Os_memmap.h" 
        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
                [!IF "num:i($CurrentCoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                    [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                        static uint32 [!"node:name(node:ref(.))"!]_stack[[!"num:i(node:value(node:ref(.)/TaskStackSize) div 4)"!]];
                    [!ENDLOOP!][!//
                    [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
                    [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                        static uint32 [!"node:name(node:ref(.))"!]_stack[[!"num:i(node:value(node:ref(.)/IsrStackSize) div 4)"!]];
                    [!ENDIF!][!//
                    [!ENDLOOP!][!//
                    [!VAR "CurrentContextAppID"="./@index"!][!//
                    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIoc/*/OsIocCommunication/*,'@index')"!][!//
                    [!VAR "CurrentIocName" = "node:name(.)"!][!//
                        [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
                            [!IF "(node:value(./OsIocReceiveCallbackEnable) = 'true') and ($CurrentContextAppID = num:i(node:ref(./OsIocReceivingOsApplicationRef)/@index))"!][!//
                                static uint32 [!"$CurrentIocName"!]_[!"node:name(.)"!]_stack[[!"num:i(node:value(./IocStackSize) div 4)"!]];
                            [!ENDIF!][!//
                        [!ENDLOOP!][!//
                    [!ENDLOOP!][!//
                    [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
                        [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                            [!VAR "ErrorHookFlag"="'true'"!][!//
                        [!ENDIF!][!//
                        [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                            [!VAR "StartupHookFlag"="'true'"!][!//
                        [!ENDIF!][!//
                        [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                            [!VAR "ShutdownHookFlag"="'true'"!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                            [!VAR "ErrorHookFlag"="'true'"!][!//
                        [!ENDIF!][!//
                        [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                            [!VAR "StartupHookFlag"="'true'"!][!//
                        [!ENDIF!][!//
                        [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                            [!VAR "ShutdownHookFlag"="'true'"!][!//
                        [!ENDIF!][!//
                        [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                            [!VAR "ProtectionHookFlag"="'true'"!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$ErrorHookFlag = 'true'"!][!//
            static uint32 OsCore[!"num:i($CurrentCoreID)"!]_ErrorHook_stack[[!"num:i(node:value(./OsCoreHookStackConfig/OsErrorHookSize) div 4)"!]];
        [!ENDIF!][!//
        [!IF "$StartupHookFlag = 'true'"!][!//
            static uint32 OsCore[!"num:i($CurrentCoreID)"!]_StartupHook_stack[[!"num:i(node:value(./OsCoreHookStackConfig/OsStartupHookSize) div 4)"!]];
        [!ENDIF!][!//
        [!IF "$ShutdownHookFlag = 'true'"!][!//
            static uint32 OsCore[!"num:i($CurrentCoreID)"!]_ShutdownHook_stack[[!"num:i(node:value(./OsCoreHookStackConfig/OsShutdownHookSize) div 4)"!]];
        [!ENDIF!][!//
        [!IF "$ProtectionHookFlag = 'true'"!][!//
            static uint32 OsCore[!"num:i($CurrentCoreID)"!]_ProtectionHook_stack[[!"num:i(node:value(./OsCoreHookStackConfig/OsProtectionHookSize) div 4)"!]];
        [!ENDIF!][!//
            static uint32 OsCore[!"num:i($CurrentCoreID)"!]_StartOsInitFunction_stack[256];
#define OS_STOP_SEC_STACKCFG_QM_CORE[!"num:i(./OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"

        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
                [!IF "num:i($CurrentCoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                    [!IF "node:value(./OsTrusted) = 'true'"!][!//
        #define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h"
                    [!ELSE!][!//
        #define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h" 
                    [!ENDIF!][!//
                    [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                        static Os_Hal_ContextFrame [!"node:name(node:ref(.))"!]_ContextInfo;
                        static Os_Hal_ContextRunningDataType [!"node:name(node:ref(.))"!]_ContextRunningData;
                    [!ENDLOOP!][!//
                    [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
                    [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                        static Os_Hal_ContextFrame [!"node:name(node:ref(.))"!]_ContextInfo;
                        static Os_Hal_ContextRunningDataType [!"node:name(node:ref(.))"!]_ContextRunningData;
                    [!ENDIF!][!//
                    [!ENDLOOP!][!//
                    [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
                        [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                            static Os_Hal_ContextFrame [!"node:name(.)"!]_ErrorHook_ContextInfo;
                            static Os_Hal_ContextRunningDataType [!"node:name(.)"!]_ErrorHook_ContextRunningData;
                        [!ENDIF!][!//
                        [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                            static Os_Hal_ContextFrame [!"node:name(.)"!]_StartupHook_ContextInfo;
                            static Os_Hal_ContextRunningDataType [!"node:name(.)"!]_StartupHook_ContextRunningData;
                        [!ENDIF!][!//
                        [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                            static Os_Hal_ContextFrame [!"node:name(.)"!]_ShutdownHook_ContextInfo;
                            static Os_Hal_ContextRunningDataType [!"node:name(.)"!]_ShutdownHook_ContextRunningData;
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                            static Os_Hal_ContextFrame OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ErrorHook_ContextInfo;
                            static Os_Hal_ContextRunningDataType OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ErrorHook_ContextRunningData;
                        [!ENDIF!][!//
                        [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                            static Os_Hal_ContextFrame OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartupHook_ContextInfo;
                            static Os_Hal_ContextRunningDataType OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartupHook_ContextRunningData;
                        [!ENDIF!][!//
                        [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                            static Os_Hal_ContextFrame OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ShutdownHook_ContextInfo;
                            static Os_Hal_ContextRunningDataType OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ShutdownHook_ContextRunningData;
                        [!ENDIF!][!//
                        [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                            static Os_Hal_ContextFrame OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ProtectionHook_ContextInfo;
                            static Os_Hal_ContextRunningDataType OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ProtectionHook_ContextRunningData;
                        [!ENDIF!][!//
                            static Os_Hal_ContextFrame OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_ContextInfo;
                            static Os_Hal_ContextRunningDataType OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_ContextRunningData;
                    [!ENDIF!][!//
                    [!VAR "CurrentContextAppID"="./@index"!][!//
                    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIoc/*/OsIocCommunication/*,'@index')"!][!//
                    [!VAR "CurrentIocName" = "node:name(.)"!][!//
                        [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
                            [!IF "(node:value(./OsIocReceiveCallbackEnable) = 'true') and ($CurrentContextAppID = num:i(node:ref(./OsIocReceivingOsApplicationRef)/@index))"!][!//
                                static Os_Hal_ContextFrame [!"$CurrentIocName"!]_[!"node:name(.)"!]_ContextInfo;
                            [!ENDIF!][!//
                        [!ENDLOOP!][!//
                    [!ENDLOOP!][!//
                    [!IF "node:value(./OsTrusted) = 'true'"!][!//
        #define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h"
                    [!ELSE!][!//
        #define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
        #include "Os_memmap.h" 
                    [!ENDIF!][!//
                [!ENDIF!][!//
                
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
[!VAR "TimeProtectionID" = "0"!][!//
[!VAR "MemoryProtection" = "0"!][!//
[!VAR "AccessCheck" = "0"!][!//
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
        [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
            static const Os_ContextType [!"node:name(node:ref(.))"!]_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&[!"node:name(node:ref(.))"!]_stack[0],               /* StackTopAddr */
                (uint32)&[!"node:name(node:ref(.))"!]_stack[[!"num:i(node:value(node:ref(.)/TaskStackSize) div 4)"!]],            /* StackBottomAddr */
                (uint32)&Task_[!"node:name(node:ref(.))"!],               /* EntryFunction */
                (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
                [!IF "node:value(../../../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                0x0,                              /* InterruptSetting */
                [!ELSE!][!//
                [!IF "node:value(../../OsTrusted) = 'true'"!]OS_CONTEXT_SYS_MODE[!ELSE!]OS_CONTEXT_USER_MODE[!ENDIF!],                           /* ProgramSetting */
                0xF8,                           /* InterruptSetting */
                [!ENDIF!][!//
                &[!"node:name(node:ref(.))"!]_ContextInfo,
                [!IF "count(node:ref(.)/OsTaskMemoryProtection/*) != 0"!][!//
                    &OsMpu_ConfigSet_ObjectRefs[[!"num:i($MemoryProtection)"!]],
                    [!VAR "MemoryProtection" = "$MemoryProtection + 1"!][!//
                [!ELSE!][!//
                    NULL_PTR,
                [!ENDIF!][!//
                [!IF "count(node:ref(.)/OsTaskAccessCheck/*) != 0"!][!//
                    &OsMpu_AccessCheck_ObjectRefs[[!"num:i($AccessCheck)"!]],
                    [!VAR "AccessCheck" = "$AccessCheck + 1"!][!//
                [!ELSE!][!//
                    NULL_PTR,
                [!ENDIF!][!//
                [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1])"!][!//
                    &Os_TimingProection_ObjSet[[!"num:i($TimeProtectionID)"!]],
                    [!VAR "TimeProtectionID" = "$TimeProtectionID + 1"!][!//
                [!ELSE!][!//
                    NULL_PTR,
                [!ENDIF!][!//
                &[!"node:name(node:ref(.))"!]_ContextRunningData
                [!ENDINDENT!][!//
            };
        [!ENDLOOP!][!//
        [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
        [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
            static const Os_ContextType [!"node:name(node:ref(.))"!]_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&[!"node:name(node:ref(.))"!]_stack[0],               /* StackTopAddr */
                (uint32)&[!"node:name(node:ref(.))"!]_stack[[!"num:i(node:value(node:ref(.)/IsrStackSize) div 4)"!]],            /* StackBottomAddr */
                [!IF "not(node:empty(node:ref(.)/OsIsrHandler))"!][!//
                (uint32)&[!"node:value(node:ref(.)/OsIsrHandler)"!],            /* EntryFunction */
                [!ELSE!][!//
                (uint32)0,                    /* EntryFunction */
                [!ENDIF!][!//
                [!IF "node:value(node:ref(.)/IsCrossCoreServiceCallIsr) = 'true'"!][!//
                    (uint32)&OsIsr_PostServiceCallISR,               /* ReturnFunction */
                [!ELSE!][!//
                    (uint32)&OsIsr_PostISR,               /* ReturnFunction */
                [!ENDIF!][!//
                [!IF "node:value(../../../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                [!"num:i(node:value(node:ref(.)/OsIsrPriority))"!]UL << 5,            /* InterruptSetting */
                [!ELSE!][!//
                [!IF "node:value(../../OsTrusted) = 'true'"!]OS_CONTEXT_SYS_MODE[!ELSE!]OS_CONTEXT_USER_MODE[!ENDIF!],                         /* ProgramSetting */
                [!"num:i(node:value(node:ref(.)/OsIsrPriority))"!]UL << 3,            /* InterruptSetting */
                [!ENDIF!][!//
                &[!"node:name(node:ref(.))"!]_ContextInfo,
                [!IF "count(node:ref(.)/OsIsrMemoryProtection/*) != 0"!][!//
                    &OsMpu_ConfigSet_ObjectRefs[[!"num:i($MemoryProtection)"!]],
                    [!VAR "MemoryProtection" = "$MemoryProtection + 1"!][!//
                [!ELSE!][!//
                    NULL_PTR,
                [!ENDIF!][!//
                [!IF "count(node:ref(.)/OsIsrAccessCheck/*) != 0"!][!//
                    &OsMpu_AccessCheck_ObjectRefs[[!"num:i($AccessCheck)"!]],
                    [!VAR "AccessCheck" = "$AccessCheck + 1"!][!//
                [!ELSE!][!//
                    NULL_PTR,
                [!ENDIF!][!//
                [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1])"!][!//
                    &Os_TimingProection_ObjSet[[!"num:i($TimeProtectionID)"!]],
                    [!VAR "TimeProtectionID" = "$TimeProtectionID + 1"!][!//
                [!ELSE!][!//
                    NULL_PTR,
                [!ENDIF!][!//
                &[!"node:name(node:ref(.))"!]_ContextRunningData
                [!ENDINDENT!][!//
            };
        [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
            static const Os_ContextType [!"node:name(.)"!]_ErrorHook_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ErrorHook_stack[0],               /* StackTopAddr */
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ErrorHook_stack[[!"num:i(node:value(node:ref(./OsApplicationCoreRef)/OsCoreHookStackConfig/OsErrorHookSize) div 4)"!]],            /* StackBottomAddr */
                (uint32)&ErrorHook_[!"node:name(.)"!],            /* EntryFunction */
                (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
                [!IF "node:value(../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 5,            /* InterruptSetting */ 
                [!ELSE!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!]OS_CONTEXT_SYS_MODE[!ELSE!]OS_CONTEXT_USER_MODE[!ENDIF!],                         /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */    
                [!ENDIF!][!//
                &[!"node:name(.)"!]_ErrorHook_ContextInfo,
                NULL_PTR,
                NULL_PTR,
                NULL_PTR,
                &[!"node:name(.)"!]_ErrorHook_ContextRunningData
                [!ENDINDENT!][!//
            };
            [!ENDIF!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
            static const Os_ContextType [!"node:name(.)"!]_StartupHook_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartupHook_stack[0],               /* StackTopAddr */
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartupHook_stack[[!"num:i(node:value(node:ref(./OsApplicationCoreRef)/OsCoreHookStackConfig/OsErrorHookSize) div 4)"!]],            /* StackBottomAddr */
                (uint32)&StartupHook_[!"node:name(.)"!],            /* EntryFunction */
                (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
                [!IF "node:value(../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 5,            /* InterruptSetting */ 
                [!ELSE!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!]OS_CONTEXT_SYS_MODE[!ELSE!]OS_CONTEXT_USER_MODE[!ENDIF!],                         /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
                [!ENDIF!][!//
                &[!"node:name(.)"!]_StartupHook_ContextInfo,
                NULL_PTR,
                NULL_PTR,
                NULL_PTR,
                &[!"node:name(.)"!]_StartupHook_ContextRunningData
                [!ENDINDENT!][!//
            };
            [!ENDIF!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
            static const Os_ContextType [!"node:name(.)"!]_ShutdownHook_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ShutdownHook_stack[0],               /* StackTopAddr */
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ShutdownHook_stack[[!"num:i(node:value(node:ref(./OsApplicationCoreRef)/OsCoreHookStackConfig/OsErrorHookSize) div 4)"!]],            /* StackBottomAddr */
                (uint32)&ShutdownHook_[!"node:name(.)"!],            /* EntryFunction */
                (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
                [!IF "node:value(../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 5,            /* InterruptSetting */ 
                [!ELSE!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!]OS_CONTEXT_SYS_MODE[!ELSE!]OS_CONTEXT_USER_MODE[!ENDIF!],                         /* ProgramSetting */
                0,            /* InterruptSetting */
                [!ENDIF!][!//
                &[!"node:name(.)"!]_ShutdownHook_ContextInfo,
                NULL_PTR,
                NULL_PTR,
                NULL_PTR,
                &[!"node:name(.)"!]_ShutdownHook_ContextRunningData
                [!ENDINDENT!][!//
            };
            [!ENDIF!][!//
        [!ELSE!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
            static const Os_ContextType Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_ErrorHook_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ErrorHook_stack[0],               /* StackTopAddr */
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ErrorHook_stack[[!"num:i(node:value(node:ref(./OsApplicationCoreRef)/OsCoreHookStackConfig/OsErrorHookSize) div 4)"!]],            /* StackBottomAddr */
                (uint32)&ErrorHook,            /* EntryFunction */
                (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
                [!IF "node:value(../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 5,            /* InterruptSetting */ 
                [!ELSE!][!//
                OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
                [!ENDIF!][!//
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ErrorHook_ContextInfo,
                NULL_PTR,
                NULL_PTR,
                NULL_PTR,
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ErrorHook_ContextRunningData
                [!ENDINDENT!][!//
            };
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
            static const Os_ContextType Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_StartupHook_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartupHook_stack[0],               /* StackTopAddr */
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartupHook_stack[[!"num:i(node:value(node:ref(./OsApplicationCoreRef)/OsCoreHookStackConfig/OsErrorHookSize) div 4)"!]],            /* StackBottomAddr */
                (uint32)&StartupHook,            /* EntryFunction */
                (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
                [!IF "node:value(../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 5,            /* InterruptSetting */ 
                [!ELSE!][!//
                OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
                [!ENDIF!][!//
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartupHook_ContextInfo,
                NULL_PTR,
                NULL_PTR,
                NULL_PTR,
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartupHook_ContextRunningData
                [!ENDINDENT!][!//
            };
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
            static const Os_ContextType Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_ShutdownHook_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ShutdownHook_stack[0],               /* StackTopAddr */
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ShutdownHook_stack[[!"num:i(node:value(node:ref(./OsApplicationCoreRef)/OsCoreHookStackConfig/OsErrorHookSize) div 4)"!]],            /* StackBottomAddr */
                (uint32)&ShutdownHook,            /* EntryFunction */
                (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
                [!IF "node:value(../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                0,            /* InterruptSetting */        
                [!ELSE!][!//
                OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
                0,            /* InterruptSetting */
                [!ENDIF!][!//
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ShutdownHook_ContextInfo,
                NULL_PTR,
                NULL_PTR,
                NULL_PTR,
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ShutdownHook_ContextRunningData
                [!ENDINDENT!][!//
            };
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
            static const Os_ContextType Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_ProtectionHook_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ProtectionHook_stack[0],               /* StackTopAddr */
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ProtectionHook_stack[[!"num:i(node:value(node:ref(./OsApplicationCoreRef)/OsCoreHookStackConfig/OsErrorHookSize) div 4)"!]],            /* StackBottomAddr */
                (uint32)&ProtectionHook,            /* EntryFunction */
                (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
                [!IF "node:value(../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                0,            /* InterruptSetting */        
                [!ELSE!][!//
                OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
                0,            /* InterruptSetting */
                [!ENDIF!][!//
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ProtectionHook_ContextInfo,
                NULL_PTR,
                NULL_PTR,
                NULL_PTR,
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_ProtectionHook_ContextRunningData
                [!ENDINDENT!][!//
            };
            [!ENDIF!][!//

            static const Os_ContextType Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_Context_Config =
            {
                [!INDENT "4"!][!//
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_stack[0],               /* StackTopAddr */
                (uint32)&OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_stack[256],            /* StackBottomAddr */
                (uint32)&OsKernel_StartOs_InitFunction,            /* EntryFunction */
                (uint32)0,                                         /* ReturnFunction */
                [!IF "node:value(../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                0,                                       /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 5,            /* InterruptSetting */ 
                [!ELSE!][!//
                OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
                OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
                [!ENDIF!][!//
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_ContextInfo,
                NULL_PTR,
                NULL_PTR,
                NULL_PTR,
                &OsCore[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_ContextRunningData
                [!ENDINDENT!][!//
            };

        [!ENDIF!][!//
        [!VAR "CurrentContextAppID"="./@index"!][!//
        [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIoc/*/OsIocCommunication/*,'@index')"!][!//
            [!VAR "CurrentIocName" = "node:name(.)"!][!//
            [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
                [!IF "(node:value(./OsIocReceiveCallbackEnable) = 'true') and ($CurrentContextAppID = num:i(node:ref(./OsIocReceivingOsApplicationRef)/@index))"!][!//
                static const Os_ContextType [!"$CurrentIocName"!]_[!"node:name(.)"!]_Context_Config =
                {
                    [!INDENT "4"!][!//
                    (uint32)&[!"$CurrentIocName"!]_[!"node:name(.)"!]_stack[0],               /* StackTopAddr */
                    (uint32)&[!"$CurrentIocName"!]_[!"node:name(.)"!]_stack[[!"num:i(node:value(./IocStackSize) div 4)"!]],            /* StackBottomAddr */
                    (uint32)&[!"node:value(./OsIocReceiverPullCB)"!],            /* EntryFunction */
                    (uint32)&OsIoc_CallbackReturn,               /* ReturnFunction */
                    [!IF "node:value(node:ref(./OsIocReceivingOsApplicationRef)/OsTrusted) = 'true'"!]OS_CONTEXT_SYS_MODE[!ELSE!]OS_CONTEXT_USER_MODE[!ENDIF!],                         /* ProgramSetting */
                    OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
                    &[!"$CurrentIocName"!]_[!"node:name(.)"!]_ContextInfo,
                    NULL_PTR,
                    NULL_PTR,
                    NULL_PTR,
                    NULL_PTR
                    [!ENDINDENT!][!//
                };
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
[!VAR "CntObjectID"="0"!][!//
[!VAR "CntObjectID" = "$CntObjectID + 1"!][!//
[!INDENT "0"!][!//
const Os_ContextConfigType Os_ContextConfigSet =
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
            [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
                [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                    &[!"node:name(node:ref(.))"!]_Context_Config,
                [!ENDLOOP!][!//
                [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
                [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                    &[!"node:name(node:ref(.))"!]_Context_Config,
                [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
                    [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                        &[!"node:name(.)"!]_ErrorHook_Context_Config,
                    [!ENDIF!][!//
                    [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                        &[!"node:name(.)"!]_StartupHook_Context_Config,
                    [!ENDIF!][!//
                    [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                        &[!"node:name(.)"!]_ShutdownHook_Context_Config,
                    [!ENDIF!][!//
                [!ELSE!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                        &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_ErrorHook_Context_Config,
                    [!ENDIF!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                        &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_StartupHook_Context_Config,
                    [!ENDIF!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                        &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_ShutdownHook_Context_Config,
                    [!ENDIF!][!//
                    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                        &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]KernelApp[!"./@index"!]_ProtectionHook_Context_Config,
                    [!ENDIF!][!//
                        &Core[!"num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!]_StartOsInitFunction_Context_Config,
                [!ENDIF!][!//
                [!VAR "CurrentContextAppID"="./@index"!][!//
                [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIoc/*/OsIocCommunication/*,'@index')"!][!//
                [!VAR "CurrentIocName" = "node:name(.)"!][!//
                    [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
                        [!IF "(node:value(./OsIocReceiveCallbackEnable) = 'true') and ($CurrentContextAppID = num:i(node:ref(./OsIocReceivingOsApplicationRef)/@index))"!][!//
                            &[!"$CurrentIocName"!]_[!"node:name(.)"!]_Context_Config,
                        [!ENDIF!][!//
                    [!ENDLOOP!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ENDSELECT!][!//
        NULL_PTR
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/



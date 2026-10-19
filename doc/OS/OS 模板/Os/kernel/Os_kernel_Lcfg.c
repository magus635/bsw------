/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_kernel_Lcfg.c
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
#include "Os_kernel_Lcfg.h"
#include "Os_kernel_Cfg.h"
#include "Os_isr_Cfg.h"
#include "Os_counter_Cfg.h"
#include "Os_application_Lcfg.h"
#include "Os_spinlock_Cfg.h"
#include "Os_timingprotection_Lcfg.h"
#include "Os_task_Cfg.h"
#include "Os_hook_Lcfg.h"
#include "Os_mpu_Lcfg.h"
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
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(./OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
static Os_ApplicationRunningTimeDataType Os_AppRunningTimeData_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!];
static Os_SchedulerType Os_SchedulerProperty_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!];
static Os_HookDynamicType Os_HookRunningData_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!];
[!IF "node:exists(./OsTpCounterRef)"!][!//
static Os_TpRunningDataType Os_TimingProtection_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]RunningData;
[!ENDIF!][!//
static boolean AlarmCallbackIndication_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!];
static Os_CoreRunningDataType Os_KernelRunningData_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!];
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(./OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"

    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!VAR "Separator" = "','"!][!//
[!VAR "CoreID" = "0"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig/*, '@index')"!][!//
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(./OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
    [!VAR "CoreID" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
    [!VAR "PriorityCountList" = "''"!][!//
    [!VAR "EveryPriorityCountList" = "''"!][!//
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!IF "num:i($CoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
            [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                [!VAR "EveryPriorityCountList" = "concat($EveryPriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!VAR "PriorityIncludecomma" = "concat($Separator, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!IF "contains($PriorityCountList, $PriorityIncludecomma)"!][!//
                [!ELSE!][!//
                    [!VAR "PriorityCountList" = "concat($PriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!VAR "Total_Priority" = "num:i(count(text:split($PriorityCountList, $Separator)))"!][!//
    [!FOR "i" = "0" TO "$Total_Priority - 1"!][!//
    static TaskType Priority[!"$i"!]_Buffer_Core[!"$CoreID"!][PRIORITY[!"$i"!]_CORE[!"$CoreID"!]_QUEUESIZE];
    [!ENDFOR!][!//
    static Os_FifoQueueType FifoQueue_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!][TASK_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_TOTAL_PRIORITY];
    static uint32 TotalPriority_LowerList_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!][TASK_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_TOTAL_PRIORITY/32U + 1U];
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(./OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"

[!ENDLOOP!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "Separator" = "','"!][!//
[!VAR "CurrentAppObjectCnt"="0"!][!//
[!VAR "TaskObjectID" = "0"!][!//
[!VAR "CoreID" = "0"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig/*, '@index')"!][!//
    [!VAR "CoreID" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
    [!VAR "PriorityCountList" = "''"!][!//
    [!VAR "EveryPriorityCountList" = "''"!][!//
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!IF "num:i($CoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
            [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                [!VAR "EveryPriorityCountList" = "concat($EveryPriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!VAR "PriorityIncludecomma" = "concat($Separator, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!IF "contains($PriorityCountList, $PriorityIncludecomma)"!][!//
                [!ELSE!][!//
                    [!VAR "PriorityCountList" = "concat($PriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!VAR "Total_Priority" = "num:i(count(text:split($PriorityCountList, $Separator)))"!][!//
    static const TaskRefType TotalPriBuffer_Core[!"$CoreID"!][TASK_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_TOTAL_PRIORITY] =
    {
    [!FOR "i" = "0" TO "$Total_Priority - 1"!][!//
        [!INDENT "4"!][!//
        [!IF "$i = $Total_Priority - 1"!][!//
            &Priority[!"$i"!]_Buffer_Core[!"$CoreID"!][0]
        [!ELSE!][!//
            &Priority[!"$i"!]_Buffer_Core[!"$CoreID"!][0],
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    [!ENDFOR!][!//
    };
[!ENDLOOP!][!//
[!ENDSELECT!][!//

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "CurrentAppObjectCnt"="0"!][!//
[!VAR "TaskObjectID" = "0"!][!//
[!VAR "CoreID" = "0"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig/*, '@index')"!][!//
    [!VAR "CoreID" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
    [!VAR "PriorityCountList" = "''"!][!//
    [!VAR "EveryPriorityCountList" = "''"!][!//
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!IF "num:i($CoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
            [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                [!VAR "EveryPriorityCountList" = "concat($EveryPriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!VAR "PriorityIncludecomma" = "concat($Separator, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!IF "contains($PriorityCountList, $PriorityIncludecomma)"!][!//
                [!ELSE!][!//
                    [!VAR "PriorityCountList" = "concat($PriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!VAR "Total_Priority" = "num:i(count(text:split($PriorityCountList, $Separator)))"!][!//
    static const uint32 QueueSizeConfig_Core[!"$CoreID"!][TASK_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_TOTAL_PRIORITY] =
    {
    [!FOR "i" = "0" TO "$Total_Priority - 1"!][!//
        [!INDENT "4"!][!//
        [!IF "$i = $Total_Priority - 1"!][!//
            PRIORITY[!"$i"!]_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_QUEUESIZE
        [!ELSE!][!//
            PRIORITY[!"$i"!]_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_QUEUESIZE,
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    [!ENDFOR!][!//
    };
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
static const Os_CorenCfg_Type Os_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_CfgSet =
{
    [!INDENT "4"!][!//
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_APPLICATION_COUNT_NUMBER,         /* ApplicationCount */
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_APPLICATION_START_NUMBER,         /* ApplicationID_StartNum */
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_CONTEXT_COUNT_NUMBER,             /* ContextCount */
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_CONTEXT_START_NUMBER,             /* Context_StartNum */
    (uint32)OS_ISR_TOTAL_NUM,                 /* ISRCountNum */
    (uint32)OS_COUNTER_TOTAL_NUM,             /* CounterCountNum */
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_TPOBJECT_COUNT_NUMBER,            /* TpObjCount */
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_TPOBJECT_START_NUMBER,            /* TpObj_StartNum */
    [!IF "node:exists(./OsTpCounterRef)"!][!//
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_TPOBJECT_USED_COUNTERID,          /* TpObj_UsedCounterID */
    [!ELSE!][!//
    0xFFFFFFFFUL, /* Invaild_TpObj_UsedCounterID */
    [!ENDIF!][!//
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_MPU_CORE_REGION_MAX_NUMBER,       /* MPCoreRegionMaxNum */
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_MPU_APP_REGION_MAX_NUMBER,        /* MPAppRegionMaxNum */   
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_MPU_OBJECT_REGION_MAX_NUMBER,     /* MPObjectRegionMaxNum */
    (uint32)TASK_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_TOTAL_PRIORITY,
    (TaskType)IDLE_TASK_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!],
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_STARTOS_INITFUNCTION_OBJECT_NUMBER,     /* StartOSInitFunctionObjNum */
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_KERNEL_APPLICATION_NUMBER,        /* KernelApplicationNum */
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_RESOURCE_COUNT_NUMBER,           /* Resource_Count */
    (uint32)OS_KERNEL_CORE[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]_RESOURCE_START_NUMBER,           /* Resource_StartNum */
    &Os_KernelRunningData_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!],
    &Os_AppRunningTimeData_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!],
    &Os_SchedulerProperty_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!],
    &Os_HookRunningData_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!],
    [!IF "node:exists(./OsTpCounterRef)"!][!//
    &Os_TimingProtection_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]RunningData,
    [!ELSE!][!//
    NULL_PTR,   
    [!ENDIF!][!//
    &TotalPriBuffer_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!][0],
    &QueueSizeConfig_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!][0],
    &TotalPriority_LowerList_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!][0],
    &FifoQueue_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!][0],
    &Os_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]Hooks,
    &AlarmCallbackIndication_Core[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!],
    [!IF "count(./OsCoreMemoryProtection/*) != 0"!][!//
    &OsMpu_ConfigSetCore[!"num:i(node:ref(./OsCoreId)/EcucCoreId)"!]
    [!ELSE!][!//
    NULL_PTR   
    [!ENDIF!][!//    
    [!ENDINDENT!][!//
};
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

static const CoreIdType OsKernel_CoreIDMapList[OS_KERNEL_MAX_CORE_NUM] =
{
[!INDENT "4"!][!//
[!FOR "CurrentCorePhysicalID" = "0" TO "num:i(ecu:get('OsResource.NumOfCores') - 1)"!][!//
    [!VAR "CurrentCoreLogicalID"="num:i(0)"!][!//
    [!VAR "CoreExistsFlag"="'false'"!][!//
    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig/*,'@index')"!][!//
        [!IF "num:i($CurrentCorePhysicalID) = num:i(./OsPhysicalCoreId)"!][!//
            [!VAR "CurrentCoreLogicalID"="num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
            [!VAR "CoreExistsFlag"="'true'"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$CoreExistsFlag= 'true'"!][!//
        OS_CORE_ID_[!"num:i($CurrentCoreLogicalID)"!],
    [!ELSE!][!//
        OS_CORE_ID_INVAILD_NUM,
    [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//
};

CONST(Os_ConfigType, OS_CONST) Os_ConfigSet = 
{
    {
[!INDENT "8"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/EcuC/ELEMENTS/EcuC/EcucHardware/EcucCoreDefinition"!][!//
    [!LOOP "node:order(./*,'num:i(./EcucCoreId)')"!][!//
        [!VAR "CurrentCoreID"="num:i(./EcucCoreId)"!][!//
        [!VAR "CoreExistsFlag"="'false'"!][!//
        [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig/*,'@index')"!][!//
            [!IF "num:i($CurrentCoreID) = num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
                [!VAR "CoreExistsFlag"="'true'"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!IF "$CoreExistsFlag= 'true'"!][!//
        &Os_Core[!"num:i(./@index)"!]_CfgSet,
    [!ELSE!][!//
        NULL_PTR,
    [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
    },
    &OsKernel_CoreIDMapList[0],
    OS_KERNEL_COMBINE_COREID_MASK,
    (uint32)OS_SPINLOCK_TOTAL_NUM                                /* Spinlock total number */    
};



/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/






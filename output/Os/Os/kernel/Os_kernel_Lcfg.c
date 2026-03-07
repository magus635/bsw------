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
*   Genaration Time       : 2026-03-05 20:16:14
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
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_ApplicationRunningTimeDataType Os_AppRunningTimeData_Core0;
static Os_SchedulerType Os_SchedulerProperty_Core0;
static Os_HookDynamicType Os_HookRunningData_Core0;
static Os_TpRunningDataType Os_TimingProtection_Core0RunningData;
static boolean AlarmCallbackIndication_Core0;
static Os_CoreRunningDataType Os_KernelRunningData_Core0;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static Os_ApplicationRunningTimeDataType Os_AppRunningTimeData_Core1;
static Os_SchedulerType Os_SchedulerProperty_Core1;
static Os_HookDynamicType Os_HookRunningData_Core1;
static Os_TpRunningDataType Os_TimingProtection_Core1RunningData;
static boolean AlarmCallbackIndication_Core1;
static Os_CoreRunningDataType Os_KernelRunningData_Core1;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static TaskType Priority0_Buffer_Core0[PRIORITY0_CORE0_QUEUESIZE];
static TaskType Priority1_Buffer_Core0[PRIORITY1_CORE0_QUEUESIZE];
static TaskType Priority2_Buffer_Core0[PRIORITY2_CORE0_QUEUESIZE];
static TaskType Priority3_Buffer_Core0[PRIORITY3_CORE0_QUEUESIZE];
static TaskType Priority4_Buffer_Core0[PRIORITY4_CORE0_QUEUESIZE];
static TaskType Priority5_Buffer_Core0[PRIORITY5_CORE0_QUEUESIZE];
static TaskType Priority6_Buffer_Core0[PRIORITY6_CORE0_QUEUESIZE];
static TaskType Priority7_Buffer_Core0[PRIORITY7_CORE0_QUEUESIZE];
static TaskType Priority8_Buffer_Core0[PRIORITY8_CORE0_QUEUESIZE];
static Os_FifoQueueType FifoQueue_Core0[TASK_CORE0_TOTAL_PRIORITY];
static uint32 TotalPriority_LowerList_Core0[TASK_CORE0_TOTAL_PRIORITY/32U + 1U];
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static TaskType Priority0_Buffer_Core1[PRIORITY0_CORE1_QUEUESIZE];
static TaskType Priority1_Buffer_Core1[PRIORITY1_CORE1_QUEUESIZE];
static TaskType Priority2_Buffer_Core1[PRIORITY2_CORE1_QUEUESIZE];
static TaskType Priority3_Buffer_Core1[PRIORITY3_CORE1_QUEUESIZE];
static TaskType Priority4_Buffer_Core1[PRIORITY4_CORE1_QUEUESIZE];
static TaskType Priority5_Buffer_Core1[PRIORITY5_CORE1_QUEUESIZE];
static TaskType Priority6_Buffer_Core1[PRIORITY6_CORE1_QUEUESIZE];
static Os_FifoQueueType FifoQueue_Core1[TASK_CORE1_TOTAL_PRIORITY];
static uint32 TotalPriority_LowerList_Core1[TASK_CORE1_TOTAL_PRIORITY/32U + 1U];
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
static const TaskRefType TotalPriBuffer_Core0[TASK_CORE0_TOTAL_PRIORITY] =
{
    &Priority0_Buffer_Core0[0],
    &Priority1_Buffer_Core0[0],
    &Priority2_Buffer_Core0[0],
    &Priority3_Buffer_Core0[0],
    &Priority4_Buffer_Core0[0],
    &Priority5_Buffer_Core0[0],
    &Priority6_Buffer_Core0[0],
    &Priority7_Buffer_Core0[0],
    &Priority8_Buffer_Core0[0]
};
static const TaskRefType TotalPriBuffer_Core1[TASK_CORE1_TOTAL_PRIORITY] =
{
    &Priority0_Buffer_Core1[0],
    &Priority1_Buffer_Core1[0],
    &Priority2_Buffer_Core1[0],
    &Priority3_Buffer_Core1[0],
    &Priority4_Buffer_Core1[0],
    &Priority5_Buffer_Core1[0],
    &Priority6_Buffer_Core1[0]
};
static const uint32 QueueSizeConfig_Core0[TASK_CORE0_TOTAL_PRIORITY] =
{
    PRIORITY0_CORE0_QUEUESIZE,
    PRIORITY1_CORE0_QUEUESIZE,
    PRIORITY2_CORE0_QUEUESIZE,
    PRIORITY3_CORE0_QUEUESIZE,
    PRIORITY4_CORE0_QUEUESIZE,
    PRIORITY5_CORE0_QUEUESIZE,
    PRIORITY6_CORE0_QUEUESIZE,
    PRIORITY7_CORE0_QUEUESIZE,
    PRIORITY8_CORE0_QUEUESIZE
};
static const uint32 QueueSizeConfig_Core1[TASK_CORE1_TOTAL_PRIORITY] =
{
    PRIORITY0_CORE0_QUEUESIZE,
    PRIORITY1_CORE1_QUEUESIZE,
    PRIORITY2_CORE0_QUEUESIZE,
    PRIORITY3_CORE0_QUEUESIZE,
    PRIORITY4_CORE0_QUEUESIZE,
    PRIORITY5_CORE0_QUEUESIZE,
    PRIORITY6_CORE0_QUEUESIZE
};
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
static const Os_CorenCfg_Type Os_Core0_CfgSet =
{
    (uint32)OS_KERNEL_CORE0_APPLICATION_COUNT_NUMBER,         /* ApplicationCount */
    (uint32)OS_KERNEL_CORE0_APPLICATION_START_NUMBER,         /* ApplicationID_StartNum */
    (uint32)OS_KERNEL_CORE0_CONTEXT_COUNT_NUMBER,             /* ContextCount */
    (uint32)OS_KERNEL_CORE0_CONTEXT_START_NUMBER,             /* Context_StartNum */
    (uint32)OS_ISR_TOTAL_NUM,                 /* ISRCountNum */
    (uint32)OS_COUNTER_TOTAL_NUM,             /* CounterCountNum */
    (uint32)OS_KERNEL_CORE0_TPOBJECT_COUNT_NUMBER,            /* TpObjCount */
    (uint32)OS_KERNEL_CORE0_TPOBJECT_START_NUMBER,            /* TpObj_StartNum */
    (uint32)OS_KERNEL_CORE0_TPOBJECT_USED_COUNTERID,          /* TpObj_UsedCounterID */
    (uint32)OS_KERNEL_CORE0_MPU_CORE_REGION_MAX_NUMBER,       /* MPCoreRegionMaxNum */
    (uint32)OS_KERNEL_CORE0_MPU_APP_REGION_MAX_NUMBER,        /* MPAppRegionMaxNum */   
    (uint32)OS_KERNEL_CORE0_MPU_OBJECT_REGION_MAX_NUMBER,     /* MPObjectRegionMaxNum */
    (uint32)TASK_CORE0_TOTAL_PRIORITY,
    (TaskType)IDLE_TASK_CORE0,
    (uint32)OS_KERNEL_CORE0_STARTOS_INITFUNCTION_OBJECT_NUMBER,     /* StartOSInitFunctionObjNum */
    (uint32)OS_KERNEL_CORE0_KERNEL_APPLICATION_NUMBER,        /* KernelApplicationNum */
    (uint32)OS_KERNEL_CORE0_RESOURCE_COUNT_NUMBER,           /* Resource_Count */
    (uint32)OS_KERNEL_CORE0_RESOURCE_START_NUMBER,           /* Resource_StartNum */
    &Os_KernelRunningData_Core0,
    &Os_AppRunningTimeData_Core0,
    &Os_SchedulerProperty_Core0,
    &Os_HookRunningData_Core0,
    &Os_TimingProtection_Core0RunningData,
    &TotalPriBuffer_Core0[0],
    &QueueSizeConfig_Core0[0],
    &TotalPriority_LowerList_Core0[0],
    &FifoQueue_Core0[0],
    &Os_Core0Hooks,
    &AlarmCallbackIndication_Core0,
    &OsMpu_ConfigSetCore0
};
static const Os_CorenCfg_Type Os_Core1_CfgSet =
{
    (uint32)OS_KERNEL_CORE1_APPLICATION_COUNT_NUMBER,         /* ApplicationCount */
    (uint32)OS_KERNEL_CORE1_APPLICATION_START_NUMBER,         /* ApplicationID_StartNum */
    (uint32)OS_KERNEL_CORE1_CONTEXT_COUNT_NUMBER,             /* ContextCount */
    (uint32)OS_KERNEL_CORE1_CONTEXT_START_NUMBER,             /* Context_StartNum */
    (uint32)OS_ISR_TOTAL_NUM,                 /* ISRCountNum */
    (uint32)OS_COUNTER_TOTAL_NUM,             /* CounterCountNum */
    (uint32)OS_KERNEL_CORE1_TPOBJECT_COUNT_NUMBER,            /* TpObjCount */
    (uint32)OS_KERNEL_CORE1_TPOBJECT_START_NUMBER,            /* TpObj_StartNum */
    (uint32)OS_KERNEL_CORE1_TPOBJECT_USED_COUNTERID,          /* TpObj_UsedCounterID */
    (uint32)OS_KERNEL_CORE1_MPU_CORE_REGION_MAX_NUMBER,       /* MPCoreRegionMaxNum */
    (uint32)OS_KERNEL_CORE1_MPU_APP_REGION_MAX_NUMBER,        /* MPAppRegionMaxNum */   
    (uint32)OS_KERNEL_CORE1_MPU_OBJECT_REGION_MAX_NUMBER,     /* MPObjectRegionMaxNum */
    (uint32)TASK_CORE1_TOTAL_PRIORITY,
    (TaskType)IDLE_TASK_CORE1,
    (uint32)OS_KERNEL_CORE1_STARTOS_INITFUNCTION_OBJECT_NUMBER,     /* StartOSInitFunctionObjNum */
    (uint32)OS_KERNEL_CORE1_KERNEL_APPLICATION_NUMBER,        /* KernelApplicationNum */
    (uint32)OS_KERNEL_CORE1_RESOURCE_COUNT_NUMBER,           /* Resource_Count */
    (uint32)OS_KERNEL_CORE1_RESOURCE_START_NUMBER,           /* Resource_StartNum */
    &Os_KernelRunningData_Core1,
    &Os_AppRunningTimeData_Core1,
    &Os_SchedulerProperty_Core1,
    &Os_HookRunningData_Core1,
    &Os_TimingProtection_Core1RunningData,
    &TotalPriBuffer_Core1[0],
    &QueueSizeConfig_Core1[0],
    &TotalPriority_LowerList_Core1[0],
    &FifoQueue_Core1[0],
    &Os_Core1Hooks,
    &AlarmCallbackIndication_Core1,
    &OsMpu_ConfigSetCore1
};

static const CoreIdType OsKernel_CoreIDMapList[OS_KERNEL_MAX_CORE_NUM] =
{
    OS_CORE_ID_0,
};

CONST(Os_ConfigType, OS_CONST) Os_ConfigSet = 
{
    {
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






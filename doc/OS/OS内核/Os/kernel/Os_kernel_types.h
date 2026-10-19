/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_kernel_types.h
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
#ifndef OS_KERNEL_TYPES_H_
#define OS_KERNEL_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_kernel_Cfg.h"
#include "Os_application_types.h"
#include "Os_task_types.h"
#include "Os_ioc_types.h"
#include "Os_hook_types.h"
#include "Os_isr_types.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef P2VAR(Os_ApplicationRunningTimeDataType, TYPEDEF, OS_VAR) Os_ApplicationRunningTimeDataTypeRef;
typedef P2VAR(Os_SchedulerType, TYPEDEF, OS_VAR) Os_SchedulerTypeRef;
typedef P2VAR(Os_HookDynamicType, TYPEDEF, OS_VAR) Os_HookDynamicTypeRef;
typedef P2VAR(Os_TpRunningDataType, TYPEDEF, OS_VAR) Os_TpRunningDataTypeRef;
typedef P2CONST(Os_CoreHooksType, TYPEDEF, OS_VAR) Os_CoreHooksTypeRef;
typedef P2VAR(Os_FifoQueueType, TYPEDEF, OS_VAR) Os_FifoQueueTypeRef;
typedef CONSTP2CONST(Os_HalCoreMpuConfigType, TYPEDEF, OS_VAR) Os_HalCoreMpuConfigRefType;
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    OS_CORE_NO_STARTED = 0,
    OS_CORE_STARTED
} OsKernel_CoreStatusType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/

typedef struct
{
    OsKernel_CoreStatusType Status;
    /*  */
    IdleModeType IdleStatus;
}Os_CoreRunningDataType;

typedef struct
{
    /* The numbers of applications of this core. */
    uint32 AppCount;    
    /* Start application ID of this core*/
    uint32 AppID_StartNum;      
    /* The total Context numbers of this core. */
    uint32 ContextCount;
    /* The start Index of Context list array for this core.*/
    uint32 Context_StartNum;
    /* The total ISR numbers of this core. */
    uint32 ISRCount;
    /* The total counter numbers of this core */
    uint32 CounterCount;
    /* The total timing protection number of this core */
    uint32 TpObject_Count;
    /* The start Index of timing protection of this core.  */
    uint32 TpObject_StartNum;
    /* The counterID used for timing protection of this core */
    uint32 TpUsedCounterID;
    /* The MP Regions used for core setting */
    uint32 MPCoreRegionMaxNum;
    /* The max MP Regions used for applications of this core */
    uint32 MPAppRegionMaxNum;
    /* The max MP Regions used for Object of this core.*/
    uint32 MPObjectRegionMaxNum;
    /* The number of Task priority Level of this core.  */
    uint32 TaskTotalPriority;
    /* Idle Task ID of this core.  */
    TaskType CoreIdleTask;
    /* ObjectID of OsKernel_StartOs_InitFunction thread. */
    uint32 StartOSInitFunctionObjNum;
    /* Kernel/system application ID  */
    uint32 KernelApplicationNum;
    /* The total resource number of this core */
    uint32 Resource_Count;
    /* The start Index of resource of this core */
    uint32 Resource_StartNum;
    /* Core running data.   */
    P2VAR(Os_CoreRunningDataType, TYPEDEF, OS_VAR) CoreRunData;
    /* Indication the current core application dynamic data config list point array. */
    Os_ApplicationRunningTimeDataTypeRef AppRunDataArrayRef;
    /* Pointer of scheduler running data.  */
    Os_SchedulerTypeRef SchedulerRunDataRef;
    /* Pointer of hook running data */
    Os_HookDynamicTypeRef HookRunDataRef;
    /* Pointer of timing protection running data. */
    Os_TpRunningDataTypeRef TpRunDataRef;
    /* Pointer to the address of array which contains every task priority level buffer address. */
    P2CONST(TaskRefType, TYPEDEF, OS_CONST) TaskPriBufferRef;
    /* Pointer of Task Priority level array which contains priority size. */
    P2CONST(uint32, TYPEDEF, OS_CONST) TaskQueueSizeRef;
    /* Pointer to the address of bit array which indicates task priority level used at this core.*/
    P2VAR(uint32, TYPEDEF, OS_VAR) TaskPriorityLevelBitArrayRef;
    /* Pointer to the address of FIFO Queue array of this core.  */
    Os_FifoQueueTypeRef TaskFifoQueueRef;
    /* Pointer of running data of core hook.  */
    Os_CoreHooksTypeRef CoreHookRef;
    /* Pointer to buffer which indicates system is running Alarm callback or not  */
    P2VAR(boolean, TYPEDEF, OS_VAR) AlarmCallbackFlagRef;
    /* Pointer of MPU settings of this core. */
    Os_HalCoreMpuConfigRefType MpuConfigSetRef;
} Os_CorenCfg_Type;

typedef struct
{
    /* */
    P2CONST(Os_CorenCfg_Type, TYPEDEF, OS_CONST) CoreConfigPtr[OS_KERNEL_TOTAL_USED_NUM];
    /* */
    P2CONST(CoreIdType, TYPEDEF, OS_CONST) CoreIDListPtr;
    /* */
    uint32 CombineCoreIDMask;
    /*   */
    uint32 Spinlock_CountNum;

} Os_ConfigType;

#endif /* OS_KERNEL_TYPES_H */

/****************************************************************************************************
**     End of File: Os_kernel_types.h                                                              **
****************************************************************************************************/


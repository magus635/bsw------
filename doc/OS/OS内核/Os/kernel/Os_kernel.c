/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_kernel.c
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

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os.h"
#include "Os_application.h"
#include "Os_task.h"
#include "Os_kernel.h"
#include "Os_kernel_Lcfg.h"
#include "Os_context_Lcfg.h"
#include "Os_compiler_types.h"
#include "Os_mpu.h"
#include "Os_isr.h"
#include "Os_isr_Lcfg.h"
#include "Os_hook.h"
#include "Os_hook_Lcfg.h"
#include "Os_counter.h"
#include "Os_counter_Lcfg.h"
#include "Os_mpu_Lcfg.h"
#include "Os_timingprotection.h"
#include "Os_spinlock.h"
#include "Os_context.h"
#include "Os_ioc.h"
#include "Os_resource.h"
#include "Os_services.h"
#include "Os_orti.h"
#include "Os_ArtiHooks.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"

static volatile AppModeType OsKernel_StartOS_OsMode;
static volatile uint32 OsKernel_StartCore_SyncPoint_1;
static volatile uint32 OsKernel_StartOS_AppModeCheck_SyncPoint;
static volatile uint32 OsKernel_StartOS_InitStartupHook_SyncPoint;
static volatile uint32 OsKernel_StartOS_AppStart_SyncPoint;
static volatile uint32 OsKernel_ShutdownAllCores_SyncPoint;

#define OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsKernel_ShutdownOSProcessing
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : Error. Error Number.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsKernel_ShutdownOSProcessing
(
    StatusType Error
);

/****************************************************************************************************
*   Function Name           : OsKernel_Internal_ShutdownOS
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : Error. Error Number.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsKernel_Internal_ShutdownOS
(
    StatusType Error
);

/****************************************************************************************************
*   Function Name           : OsKernel_Internal_ShutdownAllCores
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : Error. Error Number.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsKernel_Internal_ShutdownAllCores
(
    StatusType Error
);

/****************************************************************************************************
*   Function Name           : OsKernel_Internal_GetNumberOfActivatedCores
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Number of Activated Cores.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(uint32, OS_CODE) OsKernel_Internal_GetNumberOfActivatedCores
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_Internal_isOsStarted
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : boolean. TRUE indicates Core has started.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, OS_CODE) OsKernel_Internal_isOsStarted
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_Internal_ControlIdle
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : CoreID. CoreID
*                           : IdleMode.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType. E_OK indicate success.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsKernel_Internal_ControlIdle
(
    CoreIdType CoreID,
    IdleModeType IdleMode
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
static FUNC(void, OS_CODE) OsKernel_Internal_ShutdownOS
(
    StatusType Error
)
{
    OsOrti_ServiceStart(0xFE);

    if((OsKernel_GetCurrentRunningContext() & OS_CALL_SHUTDOWNOS) == 0UL)
    {
        /*    */
        OsHook_CallProtectionHook(E_OS_CALLEVEL);
    }
    else if(TRUE == OsApp_CheckCurrentAppIsTrusted())
    {
        /* Processing shutdown action */
        OsKernel_ShutdownOS(Error);
    }
    else
    {
        /*[SWS_Os_00054]*/
        /* do nothing  */
    }

    OsOrti_ServiceEnd(0xFE);
}

static FUNC(void, OS_CODE) OsKernel_Internal_ShutdownAllCores
(
    StatusType Error
)
{
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    uint32 LoopID;
    CoreIdType CoreID;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_SHUTDOWNALLCORES);
    OS_ARTI_SC_BEGIN(ShutdownAllCores, Error);

    if(OsService_ExtendedErrorCheck((OsKernel_GetCurrentRunningContext() & OS_CALL_SHUTDOWNOS) == 0UL))
    {
        /*    */
        OsHook_CallProtectionHook(E_OS_CALLEVEL);
    }
    else if(TRUE == OsApp_CheckCurrentAppIsTrusted())
    {
        for(LoopID = 0u; LoopID < OS_KERNEL_MAX_CORE_NUM; LoopID++)
        {
            CoreID = Os_ConfigSet.CoreIDListPtr[LoopID];

            if(CoreID != OS_CORE_ID_INVAILD_NUM)
            {
                /* Cross core service call */
                ServiceCallCfg.ServiceId = OS_SERVICEID_SHUTDOWNALLCORES;
                ServiceCallCfg.EntryAddress = (uint32)OsKernel_ShutdownAllCores;
                ServiceCallCfg.TargetCoreId = Os_ConfigSet.CoreIDListPtr[CoreID];
                ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)((uint32)Error);
                ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
                ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();

                (void)OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            }
        }

        OsKernel_ShutdownAllCores(Error);
    }
    else
    {
        /*[SWS_Os_00054]*/
        /* do nothing  */
    }

    OsOrti_ServiceEnd(OS_SERVICEID_SHUTDOWNALLCORES);
}

static FUNC(void, OS_CODE) OsKernel_ShutdownOSProcessing
(
    StatusType Error
)
{
    CoreIdType CoreID;
    uint32 LoopID;
    P2CONST(Os_CorenCfg_Type, TYPEDEF, OS_CONST) CoreCfgPtr;

    CoreID = Os_Inf_GetCoreId();
    CoreCfgPtr = Os_ConfigSet.CoreConfigPtr[CoreID];

    /* 7.9.6.1 Synchronized shutdown concept  [SWS_Os_00586] [SWS_Os_00588]  */
    /* Check whether the core is started or not. */
    if(OS_CORE_STARTED == Os_ConfigSet.CoreConfigPtr[CoreID]->CoreRunData->Status)
    {
        /*DeInit all OsApplications at this core.*/
        for(LoopID = CoreCfgPtr->AppID_StartNum;
                LoopID < CoreCfgPtr->AppID_StartNum + CoreCfgPtr->AppCount; LoopID++)
        {
            OsApp_ApplicationDeInit((ApplicationType)LoopID);
        }
        /*Call OsApplication ShutdownHook.*/
        for(LoopID = CoreCfgPtr->AppID_StartNum;
                LoopID < CoreCfgPtr->AppID_StartNum + CoreCfgPtr->AppCount; LoopID++)
        {
            OsHook_CallAppShutdownHook(Error,(ApplicationType)LoopID);
        }
    }
}

static FUNC(uint32, OS_CODE) OsKernel_Internal_GetNumberOfActivatedCores
(
    void
)
{
    uint32 ActivatedCoresNumber;
    uint32 LoopID;
    CoreIdType CoreID;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETNUMBEROFACTIVATEDCORES);
    OS_ARTI_SC_BEGIN(GetNumberOfActivatedCores, 0U);

    ActivatedCoresNumber = 0UL;

    for(LoopID = 0u; LoopID < OS_KERNEL_MAX_CORE_NUM; LoopID++)
    {
        CoreID = Os_ConfigSet.CoreIDListPtr[LoopID];

        if(CoreID != OS_CORE_ID_INVAILD_NUM)
        {
            if(OS_CORE_STARTED == Os_ConfigSet.CoreConfigPtr[CoreID]->CoreRunData->Status)
            {
                ActivatedCoresNumber++;
            }
        }
    }

    OS_ARTI_SC_END(GetNumberOfActivatedCores, ActivatedCoresNumber);
    OsOrti_ServiceEnd(OS_SERVICEID_GETNUMBEROFACTIVATEDCORES);

    return ActivatedCoresNumber;
}

static FUNC(boolean, OS_CODE) OsKernel_Internal_isOsStarted
(
    void
)
{
    boolean result;
    CoreIdType CoreID;

    OsOrti_ServiceStart(OS_SERVICEID_ISOSSTARTED);

    CoreID = Os_Inf_GetCoreId();

    if(OS_CORE_STARTED == Os_ConfigSet.CoreConfigPtr[CoreID]->CoreRunData->Status)
    {
        result = TRUE;
    }
    else
    {
        result = FALSE;
    }

    OsOrti_ServiceEnd(OS_SERVICEID_ISOSSTARTED);

    return result;
}

static FUNC(StatusType, OS_CODE) OsKernel_Internal_ControlIdle
(
    CoreIdType CoreID,
    IdleModeType IdleMode
)
{
    StatusType result;
    CoreIdType CurrentCoreID;
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_CONTROLIDLE);
    OS_ARTI_SC_BEGIN(ControlIdle, CoreID);

    CurrentCoreID = Os_Inf_GetCoreId();

    if(OsService_ExtendedErrorCheck((CoreID >= OS_KERNEL_MAX_CORE_NUM) ||
            (OS_CORE_ID_INVAILD_NUM == Os_ConfigSet.CoreIDListPtr[CoreID])))
    {

        /* SWS_Os_00676 Core ID is invalid */
        result = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck((OsKernel_GetCurrentRunningContext() & OS_CALL_TERMINATEAPPLICATION) == 0UL))
    {
        /*  */
        result = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        result = E_OS_DISABLEDINT;
    }
    else
    {
        if(CoreID == CurrentCoreID)
        {
            result = OsKernel_ControlIdle(CoreID,IdleMode);
        }
        else
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_CONTROLIDLE;
            ServiceCallCfg.EntryAddress = (uint32)OsKernel_ControlIdle;
            ServiceCallCfg.TargetCoreId = Os_ConfigSet.CoreIDListPtr[CoreID];
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)((uint32)CoreID);
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)IdleMode;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();

            result = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }
    }

    if(E_OK != result)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_CONTROLIDLE, (InputParaType)((uint32)CoreID), (InputParaType)IdleMode);
        OsHook_CallErrorHook(result);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(ControlIdle, result);
    OsOrti_ServiceEnd(OS_SERVICEID_CONTROLIDLE);

    return result;
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(void, OS_CODE) CodeFreeze
(
    void
)
{
    while(1);
};

FUNC(Os_ApplicationRunningTimeDataTypeRef, OS_CODE) OsKernel_GetCurrentCoreAppDataInfo
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->AppRunDataArrayRef;
}

FUNC(Os_SchedulerTypeRef, OS_CODE) OsKernel_GetCurrentCoreSchedulerDataInfo
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->SchedulerRunDataRef;
}

FUNC(Os_HookDynamicTypeRef, OS_CODE) OsKernel_GetCurrentCoreHookDataInfo
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->HookRunDataRef;
}

FUNC(Os_TpRunningDataTypeRef, OS_CODE) OsKernel_GetCurrentCoreTpDataInfo
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->TpRunDataRef;
}

FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreMaxCoreMpRegionNum
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->MPCoreRegionMaxNum;
}

FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreMaxAppMpRegionNum
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->MPAppRegionMaxNum;
}

FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreMaxObjectMpRegionNum
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->MPObjectRegionMaxNum;
}

FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreTotalTaskPriorityNum
(
    void
)
{
    CoreIdType CoreID;
    /*Get logical coreID.*/
    CoreID = Os_Inf_GetCoreId();
    /*Get Task Priority Level Setting of current Core */
    return Os_ConfigSet.CoreConfigPtr[CoreID]->TaskTotalPriority;
}

FUNC(TaskRefType, OS_CODE) OsKernel_GetCurrentCoreTaskPriBufferPtr
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return (TaskRefType)Os_ConfigSet.CoreConfigPtr[CoreID]->TaskPriBufferRef;
}

FUNC(P2CONST(uint32, TYPEDEF, OS_CONST), OS_CODE) OsKernel_GetCurrentCoreTaskQueueSizePtr
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->TaskQueueSizeRef;
}

FUNC(P2VAR(uint32, TYPEDEF, OS_VAR), OS_CODE) OsKernel_GetCurrentCoreAddressofBitArray
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->TaskPriorityLevelBitArrayRef;
}

FUNC(Os_FifoQueueTypeRef, OS_CODE) OsKernel_GetCurrentCoreTaskFifoQueuePtr
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->TaskFifoQueueRef;
}

FUNC(Os_CoreHooksTypeRef, OS_CODE) OsKernel_GetCurrentCoreHooksInfoPtr
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->CoreHookRef;
}

FUNC(P2VAR(boolean, TYPEDEF, OS_VAR), OS_CODE) OsKernel_GetCurrentCoreAlarmCallbackFlagPtr
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->AlarmCallbackFlagRef;
}

FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreKernelAppID
(
    void
)
{
    CoreIdType CoreID;

    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->KernelApplicationNum;
}

FUNC(uint32, OS_CODE) OsKernel_GetCurrentRunningContext
(
    void
)
{
    P2VAR(boolean, TYPEDEF, OS_VAR) UnderAlarmCallback;
    P2VAR(Os_HookDynamicType, TYPEDEF, OS_VAR) Os_HookDynPtr;
    uint32 RunningContext;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) CurrentObjectInfo;

    CurrentObjectInfo = OsApp_GetCurrent_ObjectInfo();
    Os_HookDynPtr = OsKernel_GetCurrentCoreHookDataInfo();
    UnderAlarmCallback = OsKernel_GetCurrentCoreAlarmCallbackFlagPtr();

    RunningContext = 0UL;

    if(Os_HookDynPtr->PreTaskHookIndication)
    {
        RunningContext = OS_CONTEXT_PRETASKHOOK;
    }
    else if(Os_HookDynPtr->PostTaskHookIndication)
    {
        RunningContext = OS_CONTEXT_POSTTASKHOOK;
    }
    else if(TRUE == *UnderAlarmCallback)
    {
        RunningContext = OS_CONTEXT_ALARMCALLBACK;
    }
    else if(CurrentObjectInfo->ObjectType == OBJECT_KERNELHOOK || (CurrentObjectInfo->ObjectType == OBJECT_APPHOOK))
    {
        if(ERRORHOOK == (CurrentObjectInfo->AppObjIDInfo & OBJECTID_MASK))
        {
            RunningContext = OS_CONTEXT_ERRORHOOK;
        }
        else if(STARTUPHOOK == (CurrentObjectInfo->AppObjIDInfo & OBJECTID_MASK))
        {
            RunningContext = OS_CONTEXT_STARTUPHOOK;
        }
        else if(SHUTDOWNHOOK == (CurrentObjectInfo->AppObjIDInfo & OBJECTID_MASK))
        {
            RunningContext = OS_CONTEXT_SHUTDOWNHOOK;
        }
        else
        {
            RunningContext = OS_CONTEXT_PROTECTIONHOOK;
        }
    }
    else if(CurrentObjectInfo->ObjectType == OBJECT_APPIOCCALLBACK)
    {
        RunningContext = OS_CONTEXT_IOCCALLBACK;
    }
    else if(CurrentObjectInfo->ObjectType == OBJECT_TASK)
    {
        RunningContext = OS_CONTEXT_TASK;
    }
    else if(CurrentObjectInfo->ObjectType == OBJECT_ISR)
    {
        if(OS_INTERRUPTTYPE_CAT2 == OsIsr_GetCategory(CurrentObjectInfo->AppObjIDInfo & OBJECTID_MASK))
        {
            RunningContext = OS_CONTEXT_ISR2;
        }
        else
        {
            RunningContext = OS_CONTEXT_ISR1;
        }
    }
    else
    {
        CodeFreeze();
    }

    return RunningContext;
}

FUNC(TaskType, OS_CODE) OsKernel_GetCoreIdleTask
(
    void
)
{
    CoreIdType CoreID;
    CoreID = Os_Inf_GetCoreId();

    return Os_ConfigSet.CoreConfigPtr[CoreID]->CoreIdleTask;
}

FUNC(boolean, OS_CODE) OsKernel_CheckObjectBelongToCurrentCore
(
    uint32 ObjectID
)
{
    CoreIdType PhysicalCoreID;
    CoreIdType TargetCoreID;
    boolean result;

    PhysicalCoreID = Os_Inf_CompilerGetCoreID();
    TargetCoreID = (CoreIdType)((OsApp_GetSpecific_ObjectInfo(ObjectID)->AppObjIDInfo & COREID_MASK) >> 24u);

    if(PhysicalCoreID == TargetCoreID)
    {
        result = TRUE;
    }
    else
    {
        result = FALSE;
    }

    return result;
}

FUNC(StatusType, OS_CODE) OsKernel_ControlIdle
(
    CoreIdType CoreID,
    IdleModeType IdleMode
)
{
    Os_ConfigSet.CoreConfigPtr[CoreID]->CoreRunData->IdleStatus = IdleMode;

    return E_OK;
}

FUNC(void, OS_CODE) OsKernel_ShutdownOS
(
    StatusType Error
)
{
    Os_IsrLevelType Level;

    Level = 0u;
    /*   */
    OsIsr_SuspendISR(&Level);
    /*   */
    OsKernel_ShutdownOSProcessing(Error);
    /*   */
    OsHook_CallCoreShutdownHook(Error);

    CodeFreeze();
}

FUNC(void, OS_CODE) OsKernel_ShutdownAllCores
(
    StatusType Error
)
{
    Os_IsrLevelType Level;
#if(OS_KERNEL_TOTAL_USED_NUM > 1u)
    CoreIdType CoreID;
    CoreID = Os_Inf_GetCoreId();
#endif
    Level = 0u;
    /*   */
    OsIsr_SuspendISR(&Level);

    OsKernel_ShutdownOSProcessing(Error);

    /*[SWS_Os_00587]*/
#if(OS_KERNEL_TOTAL_USED_NUM > 1u)
    /* Get spinlock . */
    OsSpinlock_GetInternalSpinlock(SHUTDOWN_SYN_SPINLOCK);
    /* Set SyncPoint by CoreID Mask */
    OsKernel_ShutdownAllCores_SyncPoint |= (1UL << CoreID);
    /* Release spinlock */
    OsSpinlock_ReleaseInternalSpinlock(SHUTDOWN_SYN_SPINLOCK);
    /* Sync multicore . */
    while(OsKernel_ShutdownAllCores_SyncPoint != Os_ConfigSet.CombineCoreIDMask);
#endif

    OsHook_CallCoreShutdownHook(Error);

    CodeFreeze();
}

FUNC(void, OS_CODE) OsKernel_StartOs_InitFunction
(
    void
)
{
    CoreIdType CoreID;
    uint32 LoopID;
    P2CONST(Os_CorenCfg_Type, TYPEDEF, OS_CONST) CoreCfgPtr;

    CoreID = Os_Inf_GetCoreId();
    CoreCfgPtr = Os_ConfigSet.CoreConfigPtr[CoreID];

    /*[SWS_Os_00579] [SWS_Os_00580] All cores that belong to the AUTOSAR system shall be synchronized
     * within the StartOS before the global StartupHook is calledAll cores that belong to the AUTOSAR system
     * shall be synchronized within the StartOS before the global StartupHook is called*/
#if(OS_KERNEL_TOTAL_USED_NUM > 1u)
    /* Get spinlock to change start app mode. */
    OsSpinlock_GetInternalSpinlock(STARTUP_SYN_SPINLOCK);
    /* Set SyncPoint by CoreID Mask */
    OsKernel_StartOS_InitStartupHook_SyncPoint |= (1UL << CoreID);
    /* Release spinlock */
    OsSpinlock_ReleaseInternalSpinlock(STARTUP_SYN_SPINLOCK);
    /* Sync multicore to Init StartupHook and AppStartupHook. */
    while(OsKernel_StartOS_InitStartupHook_SyncPoint != Os_ConfigSet.CombineCoreIDMask);
#endif
    /* [SWS_Os_00581] */
    OsHook_CallCoreStartupHook();

    for(LoopID = CoreCfgPtr->AppID_StartNum;
            LoopID < CoreCfgPtr->AppID_StartNum + CoreCfgPtr->AppCount; LoopID++)
    {
        OsHook_CallAppStartupHook((ApplicationType)LoopID);
    }
    for(LoopID = 0u;LoopID < CoreCfgPtr->CounterCount; LoopID++)
    {
        OsCounter_Start((CounterType)LoopID);
    }

#if(OS_KERNEL_TOTAL_USED_NUM > 1u)
    /* Get spinlock to change start app mode. */
    OsSpinlock_GetInternalSpinlock(STARTUP_SYN_SPINLOCK);
    /* Set SyncPoint by CoreID Mask */
    OsKernel_StartOS_AppStart_SyncPoint |= (1UL << CoreID);
    Os_Inf_Isync();
    /* Release spinlock */
    OsSpinlock_ReleaseInternalSpinlock(STARTUP_SYN_SPINLOCK);
    /* Sync multicore to start Application and call OsTask_DoScheduling. */
    while(OsKernel_StartOS_AppStart_SyncPoint != Os_ConfigSet.CombineCoreIDMask);
#endif

    OsTask_DoScheduling(NOT_SAVING_CONTEXT);
}

FUNC(void, OS_CODE) Os_PreInit
(
    void
)
{
    uint32 LoopID;
    CoreIdType CoreID;
    CoreIdType PhysicalCoreID;
    P2CONST(Os_CorenCfg_Type, TYPEDEF, OS_CONST) CoreCfgPtr;

    CoreID = Os_Inf_GetCoreId();
    PhysicalCoreID = Os_Inf_CompilerGetCoreID();
    CoreCfgPtr = Os_ConfigSet.CoreConfigPtr[CoreID];
    /* Initialize Scheduler   */
    OsTask_SchedulerInit();
    /* Initialize MPU   */
    if (NULL_PTR != CoreCfgPtr->MpuConfigSetRef)
    {
        OsMpu_InitCore(CoreCfgPtr->MpuConfigSetRef->CoreMpuCfg);
    }
    /* Initialize Hook. */
    OsHook_InitHook();
    /* Initialize TP Memory. */
    OsTp_InitMemory(CoreCfgPtr->TpUsedCounterID);

    if(OS_CORE_ID_MASTER == CoreID)
    {
        /* Get spinlock. Use spinlock to protect cross core variable access.  */
        OsSpinlock_GetInternalSpinlock(STARTUP_SYN_SPINLOCK);
#if 0
        OsKernel_StartOS_OsMode = DONOTCARE;
        OsKernel_StartOS_AppModeCheck_SyncPoint = 0UL;
        OsKernel_StartOS_InitStartupHook_SyncPoint = 0UL;
        OsKernel_StartOS_AppStart_SyncPoint = 0UL;
        OsKernel_StartCore_SyncPoint_1 = 0UL;
        OsKernel_ShutdownAllCores_SyncPoint = 0UL;
#endif
        /* Release spinlock */
        OsSpinlock_ReleaseInternalSpinlock(STARTUP_SYN_SPINLOCK);

        /* Initialize Cross Core Services environment. */
        OsIoc_InterCoreServiceCallInit();

        /* Initialize spinlock used in system. */
        for(LoopID = 0; LoopID < Os_ConfigSet.Spinlock_CountNum; LoopID++)
        {
            /*    */
            OsSpinlock_SpinlockInit((SpinlockIdType)LoopID);
        }
    }

    /* Initialize current core running data. */
    CoreCfgPtr->CoreRunData->Status = OS_CORE_NO_STARTED;

    CoreCfgPtr->AppRunDataArrayRef->Current_RunningObjectID = CoreCfgPtr->StartOSInitFunctionObjNum;
    CoreCfgPtr->AppRunDataArrayRef->Current_ApplicationID = CoreCfgPtr->KernelApplicationNum;
    CoreCfgPtr->AppRunDataArrayRef->Current_Config_ApplicationID = CoreCfgPtr->KernelApplicationNum;
    CoreCfgPtr->AppRunDataArrayRef->TrustFunctionIsCalled = FALSE;

    /*Initialize OsApplication status to APPLICATION_TERMINATED */
    for(LoopID = CoreCfgPtr->AppID_StartNum;
            LoopID < CoreCfgPtr->AppID_StartNum + CoreCfgPtr->AppCount; LoopID++)
    {
        OsApp_SetAppTerminateStatus((ApplicationType)LoopID);
    }

    /*Initialize Task/ISR2/Hook Context.*/
    for(LoopID = CoreCfgPtr->Context_StartNum;
            LoopID < CoreCfgPtr->Context_StartNum + CoreCfgPtr->ContextCount; LoopID++)
    {
        /* Init current task Context Info before task doing schduler */
        OsContext_InitMemory(LoopID);
    }

    /* Install Interrupter */
    for(LoopID = 0;LoopID < CoreCfgPtr->ISRCount; LoopID++)
    {
        if(PhysicalCoreID == (CoreIdType)Os_IsrConfigSet[LoopID]->IsrHwConfig.coreID)
        {
            OsIsr_InstallInterrupt(LoopID);
        }
    }

    /*Initialize Resource.*/
    for(LoopID = CoreCfgPtr->Resource_StartNum;
            LoopID < CoreCfgPtr->Resource_StartNum + CoreCfgPtr->Resource_Count; LoopID++)
    {
        OsResource_ResourceInit(LoopID);
    }
    Os_Inf_Isync();
}

/****************************************************************************************************
**                          AUTOSAR Function Definitions                                           **
****************************************************************************************************/
FUNC(void, OS_CODE) StartOS
(
    AppModeType Mode
)
{
    CoreIdType CoreID;
    CoreIdType PhysicalCoreID;
    uint32 LoopID;
    P2CONST(Os_CorenCfg_Type, TYPEDEF, OS_CONST) CoreCfgPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) NextObjectInfo;
    Os_IsrLevelType Level;

    CoreID = Os_Inf_GetCoreId();
    PhysicalCoreID = Os_Inf_CompilerGetCoreID();
    CoreCfgPtr = Os_ConfigSet.CoreConfigPtr[CoreID];
    Level = 0u;

    /* ORTI Use */
    OsOrti_OrtiInit(Mode);
    {
        OS_ARTI_SC_DECL
        OS_ARTI_SC_BEGIN(StartOS, Mode);
    }

    /* Suspend OS to context switch to OsKernel_StartOs_InitFunction. */
    OsIsr_SuspendISR2(&Level);

#if(OS_KERNEL_TOTAL_USED_NUM > 1u)
    /* Cores that are activated with StartCore but do not call StartOS may cause the system to hang  */
    while(((OsKernel_StartCore_SyncPoint_1 & Os_ConfigSet.CombineCoreIDMask) & (1UL << CoreID)) == 0UL);

    /* Get spinlock to change start app mode. */
    OsSpinlock_GetInternalSpinlock(STARTUP_SYN_SPINLOCK);
    /* Merge the all core app mode */
    OsKernel_StartOS_OsMode |= Mode;
    /* Set SyncPoint by CoreID Mask */
    OsKernel_StartOS_AppModeCheck_SyncPoint |= (1UL << CoreID);
    Os_Inf_Isync();
    /* Release spinlock */
    OsSpinlock_ReleaseInternalSpinlock(STARTUP_SYN_SPINLOCK);

    /* Sync multicore to merge app mode for checking out whether correctly set or not. */
    while(OsKernel_StartOS_AppModeCheck_SyncPoint != Os_ConfigSet.CombineCoreIDMask);

    /* Check the app mode is correct or not.  */
    if((DONOTCARE == OsKernel_StartOS_OsMode) || 
        (OsKernel_StartOS_OsMode != (1UL << (31UL - Os_Inf_clz(OsKernel_StartOS_OsMode)))))
    {
        /*Os_ErrKernelPanic*/
        CodeFreeze();
    }

#endif

    CoreCfgPtr->CoreRunData->Status = OS_CORE_STARTED;
    CoreCfgPtr->CoreRunData->IdleStatus = IDLE_NO_HALT;

    /* Init all Counter before Application init to avoid the alarm and scheduletable init before counter. */
    for(LoopID = 0;LoopID < CoreCfgPtr->CounterCount; LoopID++)
    {
        /* Get counter objectid from configset array, then get coreid from objectlist and check it. */
        if(PhysicalCoreID == ((OsApp_GetSpecific_ObjectInfo(Os_CounterConfigSet[LoopID]->ObjectID)->AppObjIDInfo & COREID_MASK) >> 24u))
        {
            OsCounter_Init((CounterType)LoopID);
        }
    }

    for(LoopID = CoreCfgPtr->TpObject_StartNum;
            LoopID < CoreCfgPtr->TpObject_StartNum + CoreCfgPtr->TpObject_Count; LoopID++)
    {
        OsTp_Init(LoopID);
    }

    for(LoopID = CoreCfgPtr->AppID_StartNum;
            LoopID < CoreCfgPtr->AppID_StartNum + CoreCfgPtr->AppCount; LoopID++)
    {
        OsApp_ApplicationInit((ApplicationType)LoopID,Mode);
    }

    OsOrti_ServiceEnd(OS_SERVICEID_STARTOS);
    /* specified startup Hook.*/
    NextObjectInfo = OsApp_GetSpecific_ObjectInfo(CoreCfgPtr->StartOSInitFunctionObjNum);

    /* running OsKernel_StartOs_InitFunction object.*/
    Os_Hal_ContextSwitch(NextObjectInfo,NextObjectInfo,NOT_SAVING_CONTEXT);

    OsIsr_ResumeISR(Level);
}

FUNC(void, OS_CODE) StartCore
(
    CoreIdType CoreID,
    StatusType* Status
)
{

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_STARTCORE);
    OS_ARTI_SC_BEGIN(StartCore, CoreID);

    if((OsKernel_StartCore_SyncPoint_1 & (1UL << CoreID)) != 0UL)
    {
        /* SWS_Os_00679 */
        *Status = E_OS_STATE;
    }
    else if(OS_CORE_STARTED == Os_ConfigSet.CoreConfigPtr[CoreID]->CoreRunData->Status)
    {
        /* SWS_Os_00678 */
        *Status = E_OS_ACCESS;
    }
    else if((CoreID >= OS_KERNEL_MAX_CORE_NUM) ||
            (OS_CORE_ID_INVAILD_NUM == Os_ConfigSet.CoreIDListPtr[CoreID]))
    {

        /* SWS_Os_00676 Core ID is invalid */
        *Status = E_OS_ID;
    }
    else
    {
#if(OS_KERNEL_TOTAL_USED_NUM > 1u)
        /* Get spinlock to change start app mode. */
        OsSpinlock_GetInternalSpinlock(STARTUP_SYN_SPINLOCK);
        /* Set SyncPoint by CoreID Mask */
        OsKernel_StartCore_SyncPoint_1 |= (1UL << CoreID);
        /* Release spinlock */
        Os_Inf_Isync();
        OsSpinlock_ReleaseInternalSpinlock(STARTUP_SYN_SPINLOCK);
#endif
        *Status = E_OK;
    }

    OS_ARTI_SC_END(StartCore, *Status);
    OsOrti_ServiceEnd(OS_SERVICEID_STARTCORE);
}

FUNC(CoreIdType, OS_CODE) GetCoreID
(
    void
)
{

    CoreIdType CoreID;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        OsOrti_ServiceStart(OS_SERVICEID_GETCOREID);

        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(GetCoreID, 0U);
            CoreID = Os_Inf_GetCoreId();
            OS_ARTI_SC_END(GetCoreID, CoreID);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        OsOrti_ServiceStart(OS_SERVICEID_GETCOREID);
        /* Get Logic CoreID.*/
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(GetCoreID, 0U);
            CoreID = Os_Inf_GetCoreId();
            OS_ARTI_SC_END(GetCoreID, CoreID);
        }
    }

    OsOrti_ServiceEnd(OS_SERVICEID_GETCOREID);

    return CoreID;
}

FUNC(void, OS_CODE) ShutdownOS
(
    StatusType Error
)
{

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(ShutdownOS, Error);
            OsKernel_Internal_ShutdownOS(Error);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(ShutdownOS, Error);
            OsKernel_Internal_ShutdownOS(Error);
        }
    }

}

FUNC(void, OS_CODE) ShutdownAllCores 
(
    StatusType Error
)
{

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        OsKernel_Internal_ShutdownAllCores(Error);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        OsKernel_Internal_ShutdownAllCores(Error);
    }

}

FUNC(StatusType, OS_CODE) ControlIdle
(
    CoreIdType CoreID,
    IdleModeType IdleMode
)
{
    StatusType result;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        result = OsKernel_Internal_ControlIdle(CoreID,IdleMode);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        result = OsKernel_Internal_ControlIdle(CoreID,IdleMode);
    }

    return result;
}

FUNC(uint32, OS_CODE) GetNumberOfActivatedCores 
(
    void
)
{
    uint32 ActivateCoresNum;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        ActivateCoresNum = OsKernel_Internal_GetNumberOfActivatedCores();
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        ActivateCoresNum = OsKernel_Internal_GetNumberOfActivatedCores();
    }

    return ActivateCoresNum;
}

FUNC(AppModeType, OS_CODE) GetActiveApplicationMode
(
    void
)
{
    AppModeType ActiveAppMode;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        OsOrti_ServiceStart(OS_SERVICEID_GETACTIVATEAPPLICATIONMODE);
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(GetActiveApplicationMode, 0U);
            ActiveAppMode = OsKernel_StartOS_OsMode;
            OS_ARTI_SC_END(GetActiveApplicationMode, ActiveAppMode);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        OsOrti_ServiceStart(OS_SERVICEID_GETACTIVATEAPPLICATIONMODE);
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(GetActiveApplicationMode, 0U);
            ActiveAppMode = OsKernel_StartOS_OsMode;
            OS_ARTI_SC_END(GetActiveApplicationMode, ActiveAppMode);
        }
    }

    OsOrti_ServiceEnd(OS_SERVICEID_GETACTIVATEAPPLICATIONMODE);

    return ActiveAppMode;
}

FUNC(boolean, OS_CODE) isOsStarted
(
    void
)
{
    boolean result;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        result = OsKernel_Internal_isOsStarted();
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        result = OsKernel_Internal_isOsStarted();
    }

    return result;
}

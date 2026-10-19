/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_alarm.c
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
#include "Os_alarm.h"
#include "Os_hook.h"
#include "Os_kernel.h"
#include "Os_alarm_Lcfg.h"
#include "Os_application.h"
#include "Os.h"
#include "Os_isr.h"
#include "Os_event.h"
#include "Os_counter.h"
#include "Os_compiler_types.h"
#include "Os_ioc.h"
#include "Os_services.h"
#include "Os_orti.h"
#include "Os_ArtiHooks.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

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
*   Function Name           : OsAlarm_Internal_GetAlarmBase
*   Service ID              : None.
*   Description             : Get Alarm Base under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(StatusType, OS_CODE) OsAlarm_Internal_GetAlarmBase
(
    AlarmType AlarmID,
    AlarmBaseRefType Info
);

/****************************************************************************************************
*   Function Name           : OsAlarm_Internal_GetAlarm
*   Service ID              : None.
*   Description             : Get Alarm under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(StatusType, OS_CODE) OsAlarm_Internal_GetAlarm
(
    AlarmType AlarmID,
    TickRefType Tick
);

/****************************************************************************************************
*   Function Name           : OsAlarm_Internal_SetRelAlarm
*   Service ID              : None.
*   Description             : Set Relative Alarm under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(StatusType, OS_CODE) OsAlarm_Internal_SetRelAlarm
(
    AlarmType AlarmID,
    TickType Increment,
    TickType Cycle
);

/****************************************************************************************************
*   Function Name           : OsAlarm_Internal_SetAbsAlarm
*   Service ID              : None.
*   Description             : Set Absolute Alarm under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(StatusType, OS_CODE) OsAlarm_Internal_SetAbsAlarm
(
    AlarmType AlarmID,
    TickType Increment,
    TickType Cycle
);

/****************************************************************************************************
*   Function Name           : OsAlarm_Internal_CancelAlarm
*   Service ID              : None.
*   Description             : Cancel Alarm under kernel
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(StatusType, OS_CODE) OsAlarm_Internal_CancelAlarm
(
    AlarmType AlarmID
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
FUNC(StatusType, OS_CODE) OsAlarm_Internal_GetAlarmBase
(
    AlarmType AlarmID,
    AlarmBaseRefType Info
)
{
    StatusType Status;
    Os_IsrLevelType Level;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETALARMBASE);
    OS_ARTI_SC_BEGIN(GetAlarmBase, AlarmID);

    Status = E_OK;

    if(OsService_ExtendedErrorCheck(TOTAL_ALARM_NUM <= AlarmID))
    {
        /* Alarm <AlarmID> is invalid */
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETALARMBASE))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(NULL_PTR == Info))
    {
        Status = E_OS_ILLEGAL_ADDRESS;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID) ||
            (TRUE != OsApp_CheckObjectAppIsAccessiable(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID)))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        /* Using Info as inout Parameter */
        Status = OsAlarm_GetAlarmBase(AlarmID, Info);
    }
    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_GETALARMBASE, (InputParaType)AlarmID, (InputParaType)Info);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(GetAlarmBase, (E_OK == Status) ? (uint32)(Info) : OS_ARTI_SC_INVALID);
    OsOrti_ServiceEnd(OS_SERVICEID_GETALARMBASE);
    return Status;
}

FUNC(StatusType, OS_CODE) OsAlarm_Internal_GetAlarm
(
    AlarmType AlarmID,
    TickRefType Tick
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETALARM);
    OS_ARTI_SC_BEGIN(GetAlarm, AlarmID);

    Status = E_OK;

    if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETALARM)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if(OsService_ExtendedErrorCheck(TOTAL_ALARM_NUM <= AlarmID))
    {
        /* Alarm <AlarmID> is invalid */
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if (OsService_ExtendedErrorCheck(NULL_PTR == Tick))
    {
        Status = E_OS_ILLEGAL_ADDRESS;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID) ||
            (TRUE != OsApp_CheckObjectAppIsAccessiable(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID)))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            Status = OsAlarm_GetAlarm(AlarmID, Tick);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_GETALARM;
            ServiceCallCfg.EntryAddress = (uint32)OsAlarm_GetAlarm;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)AlarmID;
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)Tick;
            ServiceCallCfg.OutputParmMask = OS_IOC_OUTPUT_PARM1_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            *Tick = (TickType)ServiceCallCfg.OutParameter.OutParm[0];
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_GETALARM, (InputParaType)AlarmID, (InputParaType)Tick);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(GetAlarm, (E_OK == Status) ? (uint32)(*Tick) : OS_ARTI_SC_INVALID);
    OsOrti_ServiceEnd(OS_SERVICEID_GETALARM);

    return Status;
}

FUNC(StatusType, OS_CODE) OsAlarm_Internal_SetRelAlarm
(
    AlarmType AlarmID,
    TickType Increment,
    TickType Cycle
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_SETRELALARM);
    OS_ARTI_SC_BEGIN(SetRelAlarm, AlarmID);

    Status = E_OK;

    if(OsService_ExtendedErrorCheck(TOTAL_ALARM_NUM <= AlarmID))
    {
        /* Alarm <AlarmID> is invalid */
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_SETRELALARM)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID) ||
            (TRUE != OsApp_CheckObjectAppIsAccessiable(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID)))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            Status = OsAlarm_SetRelAlarm(AlarmID, Increment, Cycle);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_SETRELALARM;
            ServiceCallCfg.EntryAddress = (uint32)OsAlarm_SetRelAlarm;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)AlarmID;
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)Increment;
            ServiceCallCfg.ParameterIn[2] = (Os_ServiceCallInputType)Cycle;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterThree(OS_SERVICEID_SETRELALARM, (InputParaType)AlarmID, (InputParaType)Increment, (InputParaType)Cycle);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(SetRelAlarm, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_SETRELALARM);

    return Status;
}

FUNC(StatusType, OS_CODE) OsAlarm_Internal_SetAbsAlarm
(
    AlarmType AlarmID,
    TickType Start,
    TickType Cycle
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_SETABSALARM);
    OS_ARTI_SC_BEGIN(SetAbsAlarm, AlarmID);

    Status = E_OK;

    if(OsService_ExtendedErrorCheck(TOTAL_ALARM_NUM <= AlarmID))
    {
        /* Alarm <AlarmID> is invalid */
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_SETABSALARM)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID) ||
            (TRUE != OsApp_CheckObjectAppIsAccessiable(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID)))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            Status = OsAlarm_SetAbsAlarm(AlarmID, Start, Cycle);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_SETABSALARM;
            ServiceCallCfg.EntryAddress = (uint32)OsAlarm_SetAbsAlarm;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)AlarmID;
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)Start;
            ServiceCallCfg.ParameterIn[2] = (Os_ServiceCallInputType)Cycle;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterThree(OS_SERVICEID_SETABSALARM, (InputParaType)AlarmID, (InputParaType)Start, (InputParaType)Cycle);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(SetAbsAlarm, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_SETABSALARM);

    return Status;
}

FUNC(StatusType, OS_CODE) OsAlarm_Internal_CancelAlarm
(
    AlarmType AlarmID
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    Status = E_OK;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_CANCELALARM);
    OS_ARTI_SC_BEGIN(CancelAlarm, AlarmID);

    if(OsService_ExtendedErrorCheck(TOTAL_ALARM_NUM <= AlarmID))
    {
        /* Alarm <AlarmID> is invalid */
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_CANCELALARM)))
    {
        /* Call at interrupt level */
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if(TRUE != OsApp_CheckObjectAccessingAppMask(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID) ||
            (TRUE != OsApp_CheckObjectAppIsAccessiable(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID)))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            Status = OsAlarm_CancelAlarm(AlarmID);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /* Cross core service call */
            ServiceCallCfg.ServiceId = OS_SERVICEID_CANCELALARM;
            ServiceCallCfg.EntryAddress = (uint32)OsAlarm_CancelAlarm;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(Os_AlarmConfigSet.AlarmConfigPtr[AlarmID]->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)AlarmID;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_CANCELALARM, (InputParaType)AlarmID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(CancelAlarm, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_CANCELALARM);

    return Status;
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* OSEK 13.6.3.1 GetAlarmBase */
FUNC(StatusType, OS_CODE) GetAlarmBase
(
    AlarmType AlarmID,
    AlarmBaseRefType Info
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsAlarm_Internal_GetAlarmBase(AlarmID, Info);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsAlarm_Internal_GetAlarmBase(AlarmID, Info);
    }

    return Status;
}

/* OSEK 13.6.3.2 GetAlarm */
FUNC(StatusType, OS_CODE) GetAlarm
(
    AlarmType AlarmID,
    TickRefType Tick
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsAlarm_Internal_GetAlarm(AlarmID, Tick);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsAlarm_Internal_GetAlarm(AlarmID, Tick);
    }

    return Status;
}

/* OSEK 13.6.3.3 SetRelAlarm */
FUNC(StatusType, OS_CODE) SetRelAlarm
(
    AlarmType AlarmID,
    TickType Increment,
    TickType Cycle
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsAlarm_Internal_SetRelAlarm(AlarmID, Increment, Cycle);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsAlarm_Internal_SetRelAlarm(AlarmID, Increment, Cycle);
    }

    return Status;
}

/* OSEK 13.6.3.4 SetAbsAlarm */
FUNC(StatusType, OS_CODE) SetAbsAlarm
(
    AlarmType AlarmID,
    TickType Start,
    TickType Cycle
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsAlarm_Internal_SetAbsAlarm(AlarmID, Start, Cycle);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsAlarm_Internal_SetAbsAlarm(AlarmID, Start, Cycle);
    }

    return Status;
}

/* OSEK 13.6.3.4 SetAbsAlarm */
FUNC(StatusType, OS_CODE) CancelAlarm
(
    AlarmType AlarmID
)
{
    StatusType Status;
    Status = E_OK;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        Status = OsAlarm_Internal_CancelAlarm(AlarmID);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        Status = OsAlarm_Internal_CancelAlarm(AlarmID);
    }

    return Status;
}

FUNC(void, OS_CODE) OsAlarm_AlarmInit
(
    AlarmType AlarmID,
    AppModeType AppMode
)
{
    P2CONST(Os_AlarmConstType, TYPEDEF, OS_CONST) AlarmConPtr;
    P2VAR(Os_AlarmDynamicType, TYPEDEF,OS_VAR)  AlarmDynPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST)  AlarmObjectPtr;

    /* Get Alarm Constant Information pointer */
    AlarmConPtr = Os_AlarmConfigSet.AlarmConfigPtr[AlarmID];
    /* Get Alarm Dynamic Information pointer */
    AlarmDynPtr = AlarmConPtr->Os_AlarmRunningData;
    /* Get Alarm Os_AppObjectType */
    AlarmObjectPtr = OsApp_GetSpecific_ObjectInfo(AlarmConPtr->ObjectID);

    if(AppMode & AlarmConPtr->AutoStartInfo.AutoStart)
    {
        /* Initialize Alarm Dynamic Value */
        AlarmDynPtr->State = ALARM_ENABLED;
        AlarmDynPtr->Cycle = AlarmConPtr->AutoStartInfo.Cycle;
        *(AlarmObjectPtr->ObjectDataInfo.NodeInfo->ExpTime) = AlarmConPtr->AutoStartInfo.Start;

        /* Add Alarm according to different Settings */
        if(ALARM_REL == AlarmConPtr->AutoStartInfo.ActivationType)
        {
            OsCounter_AddRelObject(AlarmObjectPtr);
        }
        else
        {
            OsCounter_AddAbsObject(AlarmObjectPtr);
        }
    }
    else
    {
        /* Set Alarm Dynamic to Default */
        AlarmDynPtr->State = ALARM_DISABLED;
        AlarmDynPtr->Cycle = 0;
    }
}

FUNC(void, OS_CODE)OsAlarm_DoAlarm
(
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) AlarmObjectPtr
)
{
    StatusType Status;
    AlarmType AlarmID;
    P2CONST(Os_AlarmConstType, TYPEDEF, OS_CONST) AlarmConPtr;
    P2VAR(Os_AlarmDynamicType, TYPEDEF,OS_VAR) AlarmDynPtr;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    Status = E_OK;
    /* Get the Specific alarm ID */
    AlarmID = AlarmObjectPtr->AppObjIDInfo & OBJECTID_MASK;
    /* Get Alarm Constant Information pointer */
    AlarmConPtr = Os_AlarmConfigSet.AlarmConfigPtr[AlarmID];
    /* Get Alarm Dynamic Information pointer */
    AlarmDynPtr = AlarmConPtr->Os_AlarmRunningData;

    boolean* AlarmCallbackFlag;

    AlarmCallbackFlag = OsKernel_GetCurrentCoreAlarmCallbackFlagPtr();

    switch(AlarmConPtr->ActionType)
    {
        case ALARM_ACTIVATETASK:
            if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(OsTask_GetTaskConst(AlarmConPtr->ActionInfo.TaskID)->ObjectID))
            {
                /* Internal Activate Task on core */
                Status = OsTask_ActivateTask(AlarmConPtr->ActionInfo.TaskID);
            }
            else
            {
                /* Cross core service call */
                ServiceCallCfg.ServiceId = OS_SERVICEID_ACTIVATETASK;
                ServiceCallCfg.EntryAddress = (uint32)OsTask_ActivateTask;
                ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(AlarmConPtr->ActionInfo.TaskID)->ObjectID);
                ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)AlarmConPtr->ActionInfo.TaskID;
                ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
                ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
                Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            }
            break;
        case ALARM_SETEVENT:
            if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(OsTask_GetTaskConst(AlarmConPtr->ActionInfo.TaskID)->ObjectID))
            {
                Status = OsEvent_SetEvent(AlarmConPtr->ActionInfo.TaskID, AlarmConPtr->ActionInfo.EventMask);
            }
            else
            {
                /* Cross core service call */
                ServiceCallCfg.ServiceId = OS_SERVICEID_SETEVENT;
                ServiceCallCfg.EntryAddress = (uint32)OsEvent_SetEvent;
                ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(AlarmConPtr->ActionInfo.TaskID)->ObjectID);
                ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)AlarmConPtr->ActionInfo.TaskID;
                ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)AlarmConPtr->ActionInfo.EventMask;
                ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
                ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
                Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            }

            break;
        case ALARM_CALLBACK:
            *AlarmCallbackFlag = TRUE;
            AlarmConPtr->ActionInfo.AlarmCallback();
            *AlarmCallbackFlag = FALSE;
            break;
        case ALARM_INCREMENTCOUNTER:
            OsCounter_IncrementCounter(AlarmConPtr->ActionInfo.CounterID, FALSE);
            break;
        default:
            CodeFreeze();
            break;
    }

    if(0 != AlarmDynPtr->Cycle)
    {
        *(AlarmObjectPtr->ObjectDataInfo.NodeInfo->ExpTime) = AlarmDynPtr->Cycle;
        /* If alarm is Cyclic Set the next Alarm */
        OsCounter_AddRelObject(AlarmObjectPtr);
    }
    else
    {
        /* if not cyclic set to disable */
        AlarmDynPtr->State = ALARM_DISABLED;
    }

    if(E_OK != Status)
    {
        OsHook_SetErrorParameterZero(OS_SERVICEID_DOALARM);
        OsHook_CallErrorHook(Status);
    }
}

FUNC(StatusType, OS_CODE) OsAlarm_GetAlarm
(
    AlarmType AlarmID,
    TickRefType Tick
)
{
    StatusType Status;
    P2VAR(Os_AlarmDynamicType, TYPEDEF,OS_VAR) AlarmDynPtr;
    P2CONST(Os_AlarmConstType, TYPEDEF, OS_CONST) AlarmConPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) AlarmObjectPtr;

    Status = E_OK;
    /* Get Alarm Constant Information pointer */
    AlarmConPtr = Os_AlarmConfigSet.AlarmConfigPtr[AlarmID];
    /* Get Alarm Dynamic Information pointer */
    AlarmDynPtr = AlarmConPtr->Os_AlarmRunningData;
    /* Get Alarm Os_AppObjectType */
    AlarmObjectPtr = OsApp_GetSpecific_ObjectInfo(AlarmConPtr->ObjectID);

    if(ALARM_DISABLED == AlarmDynPtr->State)
    {
        /* Alarm <AlarmID> is not used */
        Status = E_OS_NOFUNC;
    }
    else
    {
        /* Get Alarm Expiration Tick */
        Status = OsCounter_GetObjectRelTick(AlarmObjectPtr, Tick);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) OsAlarm_GetAlarmBase
(
    AlarmType AlarmID,
    AlarmBaseRefType Info
)
{
    StatusType Status;
    P2CONST(Os_AlarmConstType, TYPEDEF, OS_CONST) AlarmConPtr;
    P2CONST(Os_CounterAttributeConfigType, TYPEDEF, OS_CONST) CounterAttrPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) AlarmObjectPtr;

    Status = E_OK;
    /* Get Alarm Constant Information pointer */
    AlarmConPtr = Os_AlarmConfigSet.AlarmConfigPtr[AlarmID];
    AlarmObjectPtr = OsApp_GetSpecific_ObjectInfo(AlarmConPtr->ObjectID);

    CounterAttrPtr = OsCounter_GetBaseInfo(AlarmObjectPtr->ObjectDataInfo.NodeInfo->CounterID);
    Info->MaxAllowedValue = CounterAttrPtr->MaxAllowedCountValue;
    Info->MinCycle = CounterAttrPtr->MinCycle;
    Info->TicksPerBase = CounterAttrPtr->TicksPerBase;

    return Status;
}

FUNC(StatusType, OS_CODE) OsAlarm_CancelAlarm
(
    AlarmType AlarmID
)
{
    StatusType Status;
    P2CONST(Os_AlarmConstType, TYPEDEF, OS_CONST) AlarmConPtr;
    P2VAR(Os_AlarmDynamicType, TYPEDEF,OS_VAR) AlarmDynPtr;
    P2CONST(Os_AppObjectType, TYPEDEF,OS_VAR) AlarmObjectPtr;

    Status = E_OK;
    /* Get Alarm Constant Information pointer */
    AlarmConPtr = Os_AlarmConfigSet.AlarmConfigPtr[AlarmID];
    /* Get Alarm Dynamic Information pointer */
    AlarmDynPtr = AlarmConPtr->Os_AlarmRunningData;
    /* Get Alarm Os_AppObjectType */
    AlarmObjectPtr = OsApp_GetSpecific_ObjectInfo(AlarmConPtr->ObjectID);

    if(ALARM_DISABLED == AlarmDynPtr->State)
    {
        /* Alarm <AlarmID> not in use */
        Status = E_OS_NOFUNC;
    }
    else
    {
        /* Change State to disable and set cycle to 0 */
        AlarmDynPtr->State = ALARM_DISABLED;
        AlarmDynPtr->Cycle = 0;
        /* Remove alarm from job */
        Status = OsCounter_RemoveObject(AlarmObjectPtr);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) OsAlarm_SetRelAlarm
(
    AlarmType AlarmID,
    TickType Increment,
    TickType Cycle
)
{
    StatusType Status;
    P2CONST(Os_AlarmConstType, TYPEDEF, OS_CONST) AlarmConPtr;
    P2VAR(Os_AlarmDynamicType, TYPEDEF,OS_VAR) AlarmDynPtr;
    P2CONST(Os_AppObjectType, TYPEDEF,OS_CONST) AlarmObjectPtr;
    P2CONST(Os_CounterAttributeConfigType, TYPEDEF, OS_CONST) CounterAttrPtr;

    Status = E_OK;
    /* Get Alarm Constant Information pointer */
    AlarmConPtr = Os_AlarmConfigSet.AlarmConfigPtr[AlarmID];
    /* Get Alarm Dynamic Information pointer */
    AlarmDynPtr = AlarmConPtr->Os_AlarmRunningData;
    /* Get Alarm Os_AppObjectType */
    AlarmObjectPtr = OsApp_GetSpecific_ObjectInfo(AlarmConPtr->ObjectID);
    CounterAttrPtr = OsCounter_GetBaseInfo(AlarmObjectPtr->ObjectDataInfo.NodeInfo->CounterID);

    if(ALARM_DISABLED != AlarmDynPtr->State)
    {
        /* Alarm <AlarmID> is already in use */
        Status = E_OS_STATE;
    }
    else if(OsService_ExtendedErrorCheck((CounterAttrPtr->MaxAllowedCountValue <= Increment) || (0 == Increment)))
    {
        /* Value of <increment> outside of the admissible limits (lower than zero or greater than maxallowedvalue) */
        Status = E_OS_VALUE;
    }
    else if(OsService_ExtendedErrorCheck((0 != Cycle)&&((Cycle > CounterAttrPtr->MaxAllowedCountValue)||(Cycle < CounterAttrPtr->MinCycle))))
    {
        /* Value of <cycle> unequal to 0 and outside of the admissible counter limits
         (less than mincycle or greater than maxallowedvalue) */
        Status = E_OS_VALUE;
    }
    else
    {
        /* Change the Alarm State and Cycle Value */
        AlarmDynPtr->State = ALARM_ENABLED;
        AlarmDynPtr->Cycle = Cycle;
        /* Add Rel Alarm to job */
        *(AlarmObjectPtr->ObjectDataInfo.NodeInfo->ExpTime) = Increment;
        OsCounter_AddRelObject(AlarmObjectPtr);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) OsAlarm_SetAbsAlarm
(
    AlarmType AlarmID,
    TickType Start,
    TickType Cycle
)
{
    StatusType Status;
    P2CONST(Os_AlarmConstType, TYPEDEF, OS_CONST) AlarmConPtr;
    P2VAR(Os_AlarmDynamicType, TYPEDEF,OS_VAR) AlarmDynPtr;
    P2CONST(Os_AppObjectType, TYPEDEF,OS_CONST) AlarmObjectPtr;
    P2CONST(Os_CounterAttributeConfigType, TYPEDEF, OS_CONST) CounterAttrPtr;

    Status = E_OK;
    /* Get Alarm Constant Information pointer */
    AlarmConPtr = Os_AlarmConfigSet.AlarmConfigPtr[AlarmID];
    /* Get Alarm Dynamic Information pointer */
    AlarmDynPtr = AlarmConPtr->Os_AlarmRunningData;
    /* Get Alarm Os_AppObjectType */
    AlarmObjectPtr = OsApp_GetSpecific_ObjectInfo(AlarmConPtr->ObjectID);
    CounterAttrPtr = OsCounter_GetBaseInfo(AlarmObjectPtr->ObjectDataInfo.NodeInfo->CounterID);

    if(ALARM_DISABLED != AlarmDynPtr->State)
    {
        /* Alarm <AlarmID> is already in use */
        Status = E_OS_STATE;
    }
    else if(OsService_ExtendedErrorCheck(CounterAttrPtr->MaxAllowedCountValue < Start))
    {
        /* Value of <start> outside of the admissible limits (lower than zero or greater than maxallowedvalue) */
        Status = E_OS_VALUE;
    }
    else if(OsService_ExtendedErrorCheck((0 != Cycle)&&((Cycle > CounterAttrPtr->MaxAllowedCountValue)||(Cycle < CounterAttrPtr->MinCycle))))
    {
        /* Value of <cycle> unequal to 0 and outside of the admissible counter limits
         (less than mincycle or greater than maxallowedvalue) */
        Status = E_OS_VALUE;
    }
    else
    {
        /* Change the Alarm State and Cycle Value */
        AlarmDynPtr->State = ALARM_ENABLED;
        AlarmDynPtr->Cycle = Cycle;
        *(AlarmObjectPtr->ObjectDataInfo.NodeInfo->ExpTime) = Start;
        /* Add Abs Alarm to job */
        OsCounter_AddAbsObject(AlarmObjectPtr);
    }

    return Status;
}

FUNC(void, OS_CODE)OsAlarm_AlarmDeinit
(
    AlarmType AlarmID
)
{
    P2VAR(Os_AlarmDynamicType, TYPEDEF,OS_VAR) AlarmDynPtr;
    P2CONST(Os_AlarmConstType, TYPEDEF, OS_CONST) AlarmConPtr;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) AlarmObjectPtr;

    /* Get Alarm Constant Information pointer */
    AlarmConPtr = Os_AlarmConfigSet.AlarmConfigPtr[AlarmID];
    AlarmObjectPtr = OsApp_GetSpecific_ObjectInfo(AlarmConPtr->ObjectID);
    /* Get Alarm Dynamic Information pointer */
    AlarmDynPtr = AlarmConPtr->Os_AlarmRunningData;
    if(AlarmDynPtr->State == ALARM_ENABLED)
    {
        AlarmDynPtr->State = ALARM_DISABLED;
        AlarmDynPtr->Cycle = 0;
        OsCounter_RemoveObject(AlarmObjectPtr);
    }

}

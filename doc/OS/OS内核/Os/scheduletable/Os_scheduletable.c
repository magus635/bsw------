/****************************************************************************************************
 *
 ****************************************************************************************************/

/****************************************************************************************************
 *   FileName              : Os_scheduletable.c
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
 *   V0.1.0   1-July-2024    Pony(00412)                           Add Initial Code
 ****************************************************************************************************/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_isr.h"
#include "Os_hook.h"
#include "Os_event.h"
#include "Os_kernel.h"
#include "Os_counter.h"
#include "Os_application.h"
#include "Os_scheduletable_types.h"
#include "Os_scheduletable_Lcfg.h"
#include "Os_scheduletable.h"
#include "Os_ioc.h"
#include "Os_services.h"
#include "Os.h"
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
 *   Function Name           : OsSchT_Internal_Reset
 *   Service ID              : None.
 *   Description             : Reset the schedule table data.
 *   Parameters in           : SchT: The pointer of schedule table to be started
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : None.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, OS_CODE) OsSchT_Internal_Reset
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_SetToCounter
 *   Service ID              : None.
 *   Description             : Set the tick value to counter.
 *   Parameters in           : SchT: The pointer of schedule table to be started
 *                             Offset: Number of ticks on the counter
 *                             SetType: The type of tick value to be set:relative or absolute
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : None.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, OS_CODE) OsSchT_Internal_SetToCounter
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType Offset, OsSchT_SetCounterType SetType
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_StarteRel
 *   Service ID              : None.
 *   Description             : Starts the processing of a schedule table at "Offset" relative to the "Now" value on
 *                             the underlying counter.
 *   Parameters in           : SchT: The ID of schedule table to be started
 *                             Offset: Number of ticks on the counter before the the schedule table processing is started
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSchT_Internal_StartRel
(
    ScheduleTableType SchTID, TickType Offset
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_StarteAbs
 *   Service ID              : None.
 *   Description             : Starts the processing of a schedule table at an absolute value "Start" on the
 *                              underlying counter.
 *   Parameters in           : SchT: The ID of schedule table to be started
 *                             Start: Absolute counter tick value at which the schedule table is started
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSchT_Internal_StartAbs
(
    ScheduleTableType SchTID,
    TickType Start
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_Stop
 *   Service ID              : None.
 *   Description             : Cancels the processing of a schedule table immediately at any point while the
 *                             schedule table is running.
 *   Parameters in           : SchTID: The ID of schedule table to be started
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSchT_Internal_Stop
(
    ScheduleTableType SchTID
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_Next
 *   Service ID              : None.
 *   Description             : Switches the processing from one schedule table to another schedule table.
 *   Parameters in           : SchT_From: Currently processed schedule table ID
 *                             SchT_To: The ID of Schedule table  that provides its series of expire points
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSchT_Internal_Next
(
    ScheduleTableType SchT_From,
    ScheduleTableType SchT_To
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_StartSynchron
 *   Service ID              : None.
 *   Description             : Starts an explicitly synchronized schedule table synchronously.
 *   Parameters in           : SchTID: The ID of schedule table to be started
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSchT_Internal_StartSynchron
(
    ScheduleTableType SchTID
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_Sync
 *   Service ID              : None.
 *   Description             : Provides the schedule table with a synchronization count and start synchronization.
 *   Parameters in           : SchTID: The ID of schedule table to be synchronized
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSchT_Internal_Sync
(
    ScheduleTableType SchTID,
    TickType Value
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_SetAsync
 *   Service ID              : None.
 *   Description             : Stops synchronization of a schedule table.
 *   Parameters in           : SchTID: The pointer of schedule table to be requested
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSchT_Internal_SetAsync
(
    ScheduleTableType SchTID
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_GetStatus
 *   Service ID              : None.
 *   Description             : Queries the state of a schedule table .
 *   Parameters in           : SchTID: The pointer of schedule table to be requested
 *   Parameters inout        : None.
 *   Parameters out          : ScheduleStatus: Reference to ScheduleTableStatusType.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSchT_Internal_GetStatus
(
    ScheduleTableType SchTID,
    ScheduleTableStatusRefType ScheduleStatus
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_GetSchTRef
 *   Service ID              : None.
 *   Description             : Queries the state of a schedule table .
 *   Parameters in           : SchTID: Schedule table to be requested
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST), OS_CODE) OsSchT_Internal_GetSchTRef
(
    ScheduleTableType SchTID
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_GetNextSchTOffset
 *   Service ID              : None.
 *   Description             : Get the offset value of last EP in current schedule table  .
 *   Parameters in           : SchT: The pointer of schedule table to be requested.
 *                             NextSchT: The pointer of next schedule table to be requested.
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(TickType, OS_CODE) OsSchT_Internal_GetNextSchTOffset
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) NextSchT
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_GetNextEPOffset
 *   Service ID              : None.
 *   Description             : Get the offset value of next EP in current schedule table.
 *   Parameters in           : SchT: The pointer of schedule table to be requested.
 *                             CurrentEP: The current processed EP.
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(TickType, OS_CODE) OsSchT_Internal_GetNextEPOffset
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    uint32 CurrentEP
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_GetFirstEPOffset
 *   Service ID              : None.
 *   Description             : Get the offset value of from last EP to first EP in repeating schedule table .
 *   Parameters in           : SchT: The pointer of schedule table to be requested.
 *                             CurrentEP: The current processed EP.
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(TickType, OS_CODE) OsSchT_Internal_GetFirstEPOffset
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    uint32 CurrentEP
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_CalNextSyncEP
 *   Service ID              : None.
 *   Description             : Calculate the next sync EP position .
 *   Parameters in           : SchT: The pointer of schedule table to be requested.
 *                             SyncTick: The sync tick value.
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, OS_CODE) OsSchT_Internal_CalNextSyncEP
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType SyncTick
);

/****************************************************************************************************
 *   Function Name           : OsSchT_Internal_CheckSyncProcess
 *   Service ID              : None.
 *   Description             : Check whether the sync competed or not .
 *   Parameters in           : SchT: The pointer of schedule table to be requested.
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : StatusType.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsSchT_Internal_CheckSyncProcess
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT
);

/****************************************************************************************************
 *   Function Name           : OsSchT_StarteRel
 *   Service ID              : None.
 *   Description             : Starts the processing of a schedule table at "Offset" relative to the "Now" value on
 *                             the underlying counter.
 *   Parameters in           : SchT: The ID of schedule table to be started
 *                             Offset: Number of ticks on the counter before the the schedule table processing is started
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : None.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, OS_CODE) OsSchT_StartRel
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType Offset
);

/****************************************************************************************************
 *   Function Name           : OsSchT_StarteAbs
 *   Service ID              : None.
 *   Description             : Starts the processing of a schedule table at an absolute value "Start" on the
 *                              underlying counter.
 *   Parameters in           : SchT: The ID of schedule table to be started
 *                             Start: Absolute counter tick value at which the schedule table is started
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : None.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, OS_CODE) OsSchT_StartAbs
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType Start
);

/****************************************************************************************************
 *   Function Name           : OsSchT_StartSynchron
 *   Service ID              : None.
 *   Description             : Starts an explicitly synchronized schedule table synchronously.
 *   Parameters in           : SchT: The pointer of schedule table to be started
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : None.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, OS_CODE) OsSchT_StartSynchron
(
        P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

static FUNC(void, OS_CODE) OsSchT_Internal_SetToCounter
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType Offset, OsSchT_SetCounterType SetType
)
{
    uint32 ObjectID;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_VAR)
    SchTObjectPtr;

    ObjectID = SchT->ObjectID;
    /*Get the object information by object ID*/
    SchTObjectPtr = OsApp_GetSpecific_ObjectInfo(ObjectID);

    /* Add offset timer value  to counter */
    *(SchTObjectPtr->ObjectDataInfo.NodeInfo->ExpTime) = Offset;
    if (SCHEDULTTABLE_SET_RELATIVE == SetType)
    {
        /*relative counter*/
        OsCounter_AddRelObject(SchTObjectPtr);
    }
    else
    {
        /*absolute counter*/
        OsCounter_AddAbsObject(SchTObjectPtr);
    }
}

static FUNC(void, OS_CODE) OsSchT_StartRel
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType Offset
)
{
    TickType InitialOffset;

    /*get the initial offset of the first expire point*/
    InitialOffset = SchT->OsScheduleTableExpiryPoint[0]->OsScheduleTblExpPointOffset;
    InitialOffset += Offset;
    /*set the relative value to counter */
    OsSchT_Internal_SetToCounter(SchT, InitialOffset, SCHEDULTTABLE_SET_RELATIVE);

    /*update the schedule table to running */
    SchT->RunningData->State = SCHEDULETABLE_RUNNING;

}

static FUNC(StatusType, OS_CODE) OsSchT_StartSchTRel
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType Offset
)
{

    StatusType Status;

    P2CONST(Os_CounterAttributeConfigType, TYPEDEF, OS_CONST)  CounterCfg;

    if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_STARTSCHEDULETABLEREL)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if (TRUE != OsApp_CheckObjectAccessingAppMask(SchT->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(TRUE != OsApp_CheckObjectAppIsAccessiable(SchT->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(OsService_ExtendedErrorCheck(SCHEDULETABLE_STOPPED != SchT->RunningData->State) )
    {
        Status = E_OS_STATE;
    }
    else if(Offset == 0)
    {
        Status = E_OS_VALUE;
    }
    else if(OsService_ExtendedErrorCheck(SCHEDULTTABLE_SYNC_IMPLICIT == SchT->OsScheduleTableSync.OsScheduleTblSyncStrategy ))
    {
        Status = E_OS_ID;
    }
    else
    {
        CounterCfg = OsCounter_GetBaseInfo(SchT->CounterID);
        if(OsService_ExtendedErrorCheck(Offset >(CounterCfg->MaxAllowedCountValue-SchT->OsScheduleTableExpiryPoint[0]->OsScheduleTblExpPointOffset)))
        {
            Status = E_OS_VALUE;
        }
        else
        {
            /*set relative offset to counter*/
            OsSchT_StartRel(SchT,Offset);
            Status = E_OK;
        }
    }
    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_StartRel
(
    ScheduleTableType SchTID, TickType Offset
)
{

    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_STARTSCHEDULETABLEREL);
    OS_ARTI_SC_BEGIN(StartScheduleTableRel, SchTID);

    if (OsService_ExtendedErrorCheck(SchTID >= OS_SCHT_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else if(OsService_ExtendedErrorCheck(0 == Offset))
    {
         Status = E_OS_VALUE;
    }
    else
    {
        SchT = OsSchT_Internal_GetSchTRef(SchTID);

        if (TRUE == OsKernel_CheckObjectBelongToCurrentCore(SchT->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            /* Internal Start schedule relative */
            Status = OsSchT_StartSchTRel(SchT, Offset);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /*Cross-Core*/
            ServiceCallCfg.ServiceId = OS_SERVICEID_STARTSCHEDULETABLEREL;
            ServiceCallCfg.EntryAddress = (uint32)OsSchT_StartSchTRel;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(SchT->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)SchT;
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)Offset;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }

    }

    /*Error processing */
    if (E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_STARTSCHEDULETABLEREL, (InputParaType)SchTID, (InputParaType)Offset);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(StartScheduleTableRel, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_STARTSCHEDULETABLEREL);

    return Status;
}

static FUNC(void, OS_CODE) OsSchT_StartAbs
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType Start
)
{
    TickType InitialOffset;

    InitialOffset = SchT->OsScheduleTableExpiryPoint[0]->OsScheduleTblExpPointOffset;
    InitialOffset += Start;

     OsSchT_Internal_SetToCounter(SchT, InitialOffset, SCHEDULTTABLE_SET_ABSOLUTE);

    /*for implicitly synchronized ScheduleTable */
    if (SCHEDULTTABLE_SYNC_EXPLICIT == SchT->OsScheduleTableSync.OsScheduleTblSyncStrategy)
    {
        SchT->RunningData->State = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
    }
    /*for a non-synchronized / Explicitly synchronized ScheduleTable*/
    else
    {
        SchT->RunningData->State = SCHEDULETABLE_RUNNING;
    }

}

static FUNC(StatusType, OS_CODE) OsSchT_StartSchTAbs
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType Start
)
{
    StatusType Status;

    P2CONST(Os_CounterAttributeConfigType, TYPEDEF, OS_CONST)  CounterAttrCfg;

    if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_STARTSCHEDULETABLEABS)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if (TRUE != OsApp_CheckObjectAccessingAppMask(SchT->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(TRUE != OsApp_CheckObjectAppIsAccessiable(SchT->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(OsService_ExtendedErrorCheck(SCHEDULETABLE_STOPPED != SchT->RunningData->State))
    {
        Status = E_OS_STATE;
    }
    else
    {

        CounterAttrCfg = OsCounter_GetBaseInfo(SchT->CounterID);
        if(OsService_ExtendedErrorCheck(Start > CounterAttrCfg->MaxAllowedCountValue))
        {
           Status = E_OS_VALUE;
        }
        else
        {
            OsSchT_StartAbs(SchT,Start);
            Status = E_OK;
        }
    }
    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_StartAbs
(
    ScheduleTableType SchTID,
    TickType Start
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_STARTSCHEDULETABLEABS);
    OS_ARTI_SC_BEGIN(StartScheduleTableAbs, SchTID);

    if (OsService_ExtendedErrorCheck(SchTID >= OS_SCHT_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else
    {
        SchT = OsSchT_Internal_GetSchTRef(SchTID);
        if (TRUE == OsKernel_CheckObjectBelongToCurrentCore(SchT->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            /* Internal Start schedule absolute */
            Status = OsSchT_StartSchTAbs(SchT, Start);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /*Cross-Core*/
            ServiceCallCfg.ServiceId = OS_SERVICEID_STARTSCHEDULETABLEABS;
            ServiceCallCfg.EntryAddress = (uint32)OsSchT_StartSchTAbs;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(SchT->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)SchT;
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)Start;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }
    }

    /*Error processing */
    if (E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_STARTSCHEDULETABLEABS, (InputParaType)SchTID, (InputParaType)Start);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(StartScheduleTableAbs, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_STARTSCHEDULETABLEABS);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_Stop
(
    P2CONST(OsSchT_ConfigType, TYPEDEF,    OS_CONST) SchT
)
{
    P2CONST(Os_AppObjectType, TYPEDEF, OS_VAR)
    SchTObjectPtr;
    StatusType Status;
    uint32 ObjectID;
    P2VAR(OsSchT_Type, TYPEDEF, OS_VAR_NOINIT)
    RunningData;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)
    PreSchT;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)
    NextSchT;

    if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_STOPSCHEDULETABLE)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if (TRUE != OsApp_CheckObjectAccessingAppMask(SchT->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(TRUE != OsApp_CheckObjectAppIsAccessiable(SchT->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(OsService_ExtendedErrorCheck(SCHEDULETABLE_STOPPED == SchT->RunningData->State))
    {
        Status = E_OS_NOFUNC;
    }
    else
    {

        RunningData = SchT->RunningData;

        ObjectID = SchT->ObjectID;
        SchTObjectPtr = OsApp_GetSpecific_ObjectInfo(ObjectID);

        /* Remove ScheduleTable from Counter */
        Status = OsCounter_RemoveObject(SchTObjectPtr);

        /*The current has not been started, then reset the previous schedule table information */
        if (RunningData->State == SCHEDULETABLE_NEXT)
        {
            ObjectID = RunningData->PreSchTID;
            PreSchT = OsSchT_Internal_GetSchTRef(ObjectID);
            /*remove the current schedule table from previous table*/
            PreSchT->RunningData->NextSchTID = SHCT_ID_MASK;
        }

        /*The schedule table has next table, then clear the relationship between current schedule and next schedule table */
        if (RunningData->NextSchTID != SHCT_ID_MASK)
        {

            NextSchT = OsSchT_Internal_GetSchTRef(RunningData->NextSchTID);
            /*Stop the next schedule table */
            NextSchT->RunningData->State = SCHEDULETABLE_STOPPED;
            NextSchT->RunningData->PreSchTID = SHCT_ID_MASK;
            RunningData->NextSchTID = SHCT_ID_MASK;
        }

        /* Set the schedule state to stop */

        OsSchT_Internal_Reset(SchT);
        Status = E_OK;
    }
    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_Stop
(
    ScheduleTableType SchTID
)
{

    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_STOPSCHEDULETABLE);
    OS_ARTI_SC_BEGIN(StopScheduleTable, SchTID);

    if (OsService_ExtendedErrorCheck(SchTID >= OS_SCHT_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else
    {
        SchT = OsSchT_Internal_GetSchTRef(SchTID);
        if (TRUE == OsKernel_CheckObjectBelongToCurrentCore(SchT->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            /* Internal Stop schedule */
            Status = OsSchT_Stop(SchT);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /*Cross-Core*/
            ServiceCallCfg.ServiceId = OS_SERVICEID_STOPSCHEDULETABLE;
            ServiceCallCfg.EntryAddress = (uint32)OsSchT_Stop;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(SchT->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)SchT;
            ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
        }

    }

    /*Error processing */
    if (E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_STOPSCHEDULETABLE, (InputParaType)SchTID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(StopScheduleTable, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_STOPSCHEDULETABLE);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_Next
(
    ScheduleTableType SchT_From_ID,
    ScheduleTableType SchT_To_ID
)
{
    StatusType Status;
    P2VAR(OsSchT_Type, TYPEDEF, OS_VAR_NOINIT)   Dyn_From;
    P2VAR(OsSchT_Type, TYPEDEF, OS_VAR_NOINIT)   Dyn_To;
    P2VAR(OsSchT_Type, TYPEDEF, OS_VAR_NOINIT)   dyn_Next;
    Os_IsrLevelType Level;

    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT_From;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT_To;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_NEXTSCHEDULETABLE);
    OS_ARTI_SC_BEGIN(NextScheduleTable, SchT_To_ID);

    if (OsService_ExtendedErrorCheck(SchT_From_ID >= OS_SCHT_TOTAL_NUM || SchT_To_ID >= OS_SCHT_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_NEXTSCHEDULETABLE)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        SchT_From = OsSchT_Internal_GetSchTRef(SchT_From_ID);
        SchT_To = OsSchT_Internal_GetSchTRef(SchT_To_ID);

        if((TRUE != OsApp_CheckObjectAccessingAppMask(SchT_To->ObjectID))||
           (TRUE != OsApp_CheckObjectAccessingAppMask(SchT_From->ObjectID)))
        {
            Status = E_OS_ACCESS;
        }
        else if((TRUE != OsApp_CheckObjectAppIsAccessiable(SchT_To->ObjectID))||
                (TRUE != OsApp_CheckObjectAppIsAccessiable(SchT_From->ObjectID)))
        {
            Status = E_OS_ACCESS;
        }
        else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
        {
            Status = E_OS_DISABLEDINT;
        }
        else if(OsService_ExtendedErrorCheck(SCHEDULETABLE_STOPPED != SchT_To->RunningData->State))
        {
            Status = E_OS_STATE;
        }
        else if(OsService_ExtendedErrorCheck(SchT_To->CounterID != SchT_From->CounterID))
        {
            Status = E_OS_ID;
        }
        else if(OsService_ExtendedErrorCheck(SCHEDULETABLE_STOPPED == SchT_From->RunningData->State ||
                SCHEDULETABLE_NEXT == SchT_From->RunningData->State))
        {
            Status = E_OS_NOFUNC;
        }
        else if(OsService_ExtendedErrorCheck(SchT_To->OsScheduleTableSync.OsScheduleTblSyncStrategy != SchT_From->OsScheduleTableSync.OsScheduleTblSyncStrategy))
        {
            Status = E_OS_ID;
        }
        else if((OsService_ExtendedErrorCheck(!OsKernel_CheckObjectBelongToCurrentCore(SchT_To->ObjectID)))
                ||(OsService_ExtendedErrorCheck(!OsKernel_CheckObjectBelongToCurrentCore(SchT_From->ObjectID))))
        {
            Status = E_OS_CORE;
        }
        else
        {
            Dyn_From = SchT_From->RunningData;
            Dyn_To = SchT_To->RunningData;

            /*[SWS_Os_00324] If the next table has existed , at same times it is not the setting table and it is not himself*/
            if ((Dyn_From->NextSchTID != SHCT_ID_MASK) && (Dyn_From->NextSchTID != (SchT_From->SchTID & SHCT_ID_MASK)))
            {
                dyn_Next = OsSchT_Internal_GetSchTRef(SchT_From->RunningData->NextSchTID)->RunningData;
                dyn_Next->State = SCHEDULETABLE_STOPPED;
            }

            /*reset the next schedule table and set state to NEXT*/
            OsSchT_Internal_Reset(SchT_To);
            Dyn_To->State = SCHEDULETABLE_NEXT;

            /*create a link between the two table */
            Dyn_From->NextSchTID = SchT_To->SchTID & SHCT_ID_MASK;
            Dyn_To->PreSchTID = SchT_From->SchTID & SHCT_ID_MASK;

            Status = E_OK;
        }
    }

    if (E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_NEXTSCHEDULETABLE, (InputParaType)SchT_From_ID, (InputParaType)SchT_To_ID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(NextScheduleTable, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_NEXTSCHEDULETABLE);

    return Status;
}

static FUNC(void, OS_CODE) OsSchT_StartSynchron
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT
)
{
    OsSchT_Internal_Reset(SchT);
    /*set the schedule table state for first sync */
    SchT->RunningData->State = SCHEDULETABLE_WAITING;
    SchT->RunningData->Deviation = 0;
    SchT->RunningData->NeedSync = FALSE;

}
static FUNC(StatusType, OS_CODE) OsSchT_Internal_StartSynchron
(
        ScheduleTableType SchTID
)
{

    StatusType Status;
    Os_IsrLevelType Level;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_STARTSCHEDULETABLESYNCHRON);
    OS_ARTI_SC_BEGIN(StartScheduleTableSynchron, SchTID);

    if (OsService_ExtendedErrorCheck(SchTID >= OS_SCHT_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_STARTSCHEDULETABLESYNC)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {

        SchT = OsSchT_Internal_GetSchTRef(SchTID);
        if (TRUE != OsApp_CheckObjectAccessingAppMask(SchT->ObjectID))
        {
            Status = E_OS_ACCESS;
        }
        else if(TRUE != OsApp_CheckObjectAppIsAccessiable(SchT->ObjectID))
        {
            Status = E_OS_ACCESS;
        }
        else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
        {
            Status = E_OS_DISABLEDINT;
        }
        else if(OsService_ExtendedErrorCheck(SchT->RunningData->State != SCHEDULETABLE_STOPPED))
        {
            Status = E_OS_STATE;
        }
        else if(OsService_ExtendedErrorCheck(SchT->OsScheduleTableSync.OsScheduleTblSyncStrategy != SCHEDULTTABLE_SYNC_EXPLICIT))
        {
            Status = E_OS_ID;
        }
        else if(OsService_ExtendedErrorCheck(!OsKernel_CheckObjectBelongToCurrentCore(SchT->ObjectID)))
        {
            Status = E_OS_CORE;
        }
        else
        {
            OsSchT_StartSynchron(SchT);
            Status = E_OK;
        }
    }

    /*Error processing */
    if (E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_STARTSCHEDULETABLESYNCHRON, (InputParaType)SchTID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(StartScheduleTableSynchron, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_STARTSCHEDULETABLESYNCHRON);

    return Status;
}

static FUNC(void, OS_CODE) OsSchT_Internal_CalNextSyncEP
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    TickType SyncTick
)
{
    uint32 CurrentEP;
    uint32 ObjectID;
    TickType CounterNowTick;
    TickType NextEPStamp;
    TickType NextSysPointPos;
    TickType NextEPPosition;
    sint32    PositionTbl;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_VAR)
    SchTObjectPtr;
    P2CONST(Os_CounterAttributeConfigType, TYPEDEF, OS_CONST)
    CounterAttr;

    ObjectID = SchT->ObjectID;
    SchTObjectPtr = OsApp_GetSpecific_ObjectInfo(ObjectID);

    CurrentEP = SchT->RunningData->CurrentEP;
    /*The current EP has not arrived, so record the EP position */
    NextEPPosition = SchT->OsScheduleTableExpiryPoint[CurrentEP]->OsScheduleTblExpPointOffset;

    /*Get current EP the tick value in the counter*/
    NextEPStamp = (TickType)(*(SchTObjectPtr->ObjectDataInfo.NodeInfo->ExpTime));
    /*Get the 'Now' tick value*/
    OsCounter_GetCounterValue(SchT->CounterID, &CounterNowTick);

    CounterAttr = OsCounter_GetBaseInfo(SchT->CounterID);

    /*Compare the two value in counter to calculate the current position in schedule table */
    /*Calculate the Now in the position of schedule*/
    if (NextEPStamp < CounterNowTick)
    {
        PositionTbl = NextEPPosition - (CounterAttr->MaxAllowedCountValue + 1u + NextEPStamp - CounterNowTick);
        SchT->RunningData->Deviation = CounterAttr->MaxAllowedCountValue + 1u + NextEPStamp - CounterNowTick;
    }
    else
    {
        PositionTbl = NextEPPosition - (NextEPStamp - CounterNowTick);
        SchT->RunningData->Deviation = NextEPStamp - CounterNowTick;
    }

    /*Get the position in schedule table*/
    /*PositionTbl may be less 0 , so the data format should be defined to sint32*/
    if (PositionTbl > (sint32)SchT->OsScheduleTableDuration)
    {
        /*minus the duration */
        PositionTbl = PositionTbl% SchT->OsScheduleTableDuration;
    }
    else if (PositionTbl < 0)
    {
        PositionTbl += SchT->OsScheduleTableDuration;
    }
    else
    {
        // do nothing
    }

    /*Get the next system point position */
    NextSysPointPos = PositionTbl + SyncTick;
    if (NextSysPointPos >= SchT->OsScheduleTableDuration)
    {
        NextSysPointPos -= SchT->OsScheduleTableDuration;
    }
    SchT->RunningData->NextSysPointPos = NextSysPointPos;
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_UpdateNextSyncEP
(
        P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
        TickType SyncTick,
        P2VAR(TickType, TYPEDEF, OS_VAR) NextOffsetRef
)
{
    uint32 CurrentEP;
    StatusType Status;
    Os_TickDiffType Deviation;
    TickType Adjustment;
    TickType NextOffset;
    TickType EPMaxLengthen;
    TickType EPMaxShorten;
    TickType NextSysPointPos;
    TickType CfgEPPosition;

    CurrentEP = SchT->RunningData->CurrentEP;

    /*Get next offset and next EP configuration adjust value*/
    if (CurrentEP < (SchT->EPCount - 1))
    {
        /*if the EP is not the last point in the schedule table, the offset is the diff between two points*/
        NextOffset = OsSchT_Internal_GetNextEPOffset(SchT, CurrentEP);
        CfgEPPosition = SchT->OsScheduleTableExpiryPoint[CurrentEP]->OsScheduleTblExpPointOffset;
        EPMaxLengthen = SchT->OsScheduleTableExpiryPoint[CurrentEP + 1]->OsScheduleTblAdjustableExpPoint.OsScheduleTableMaxLengthen;
        EPMaxShorten = SchT->OsScheduleTableExpiryPoint[CurrentEP + 1]->OsScheduleTblAdjustableExpPoint.OsScheduleTableMaxShorten;
        SchT->RunningData->CurrentEP++;
    }
    else
    {
        /*if the EP is  the last point in the schedule table  the offset is the diff between the last points and the initial pointer*/
        NextOffset = OsSchT_Internal_GetFirstEPOffset(SchT, CurrentEP);
        CfgEPPosition = SchT->OsScheduleTableExpiryPoint[CurrentEP]->OsScheduleTblExpPointOffset;
        EPMaxLengthen = SchT->OsScheduleTableExpiryPoint[0]->OsScheduleTblAdjustableExpPoint.OsScheduleTableMaxLengthen;
        EPMaxShorten = SchT->OsScheduleTableExpiryPoint[0]->OsScheduleTblAdjustableExpPoint.OsScheduleTableMaxShorten;
        SchT->RunningData->CurrentEP = 0;
    }

    /*calculate the deviation value between actual tick and sync tick*/
    Deviation = CfgEPPosition - SyncTick;
    SchT->RunningData->Deviation = Deviation;

    /*[SWS_Os_00421] set the next EP to expire delay + Minimum(MaxLengthen, Deviation) ticks from the current expire point.*/
    if (Deviation > 0)
    {
        /*minimum(MaxLengthen, Deviation)*/
        if (Deviation < EPMaxLengthen)
        {
            /*the adjusted value is Deviation*/
            Adjustment = Deviation;
        }
        else
        {
            /*the adjusted value is Max Length */
            Adjustment = EPMaxLengthen;
        }
        /*delay + minimum(MaxLengthen, Deviation)*/
        NextOffset += Adjustment;
    }
    /*[SWS_Os_00420] set the next EP to expire delay - Minimum(MaxShorten, Deviation) ticks*/
    else
    {
        /*Minimum(MaxShorten, Deviation)*/
        Deviation = (TickType)(-(Os_TickDiffType)Deviation);
        if (Deviation < EPMaxShorten)
        {
            /*the adjusted value is Deviation*/
            Adjustment = Deviation;
        }
        else
        {
            /*the adjusted value is Max shorten */
            Adjustment = EPMaxShorten;
        }
        /*delay - minimum(MaxShorten, Deviation)*/
        NextOffset -= Adjustment;
    }

    *NextOffsetRef = NextOffset;

    /*calculate the next sync point */
    NextSysPointPos = NextOffset + SyncTick;
    if (NextSysPointPos >= SchT->OsScheduleTableDuration)
    {
        NextSysPointPos -= SchT->OsScheduleTableDuration;
    }
    /*record next sync point for next EP  */
    SchT->RunningData->NextSysPointPos = NextSysPointPos;

    Status = E_OK;
    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_CheckSyncProcess
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT
)
{
    boolean LessThreshold;
    StatusType Status;

    if (TRUE == SchT->RunningData->NeedSync)
    {
        if (SchT->RunningData->Deviation >= 0u)
        {
            LessThreshold = (boolean)(SchT->RunningData->Deviation <= (Os_TickDiffType)SchT->OsScheduleTableSync.OsScheduleTblExplicitPrecision);
        }
        else
        {
            LessThreshold = (boolean)(-SchT->RunningData->Deviation <= (Os_TickDiffType)SchT->OsScheduleTableSync.OsScheduleTblExplicitPrecision);
        }
        /*Reach the precision threshold value*/
        if (LessThreshold == TRUE)
        {
            /*sync complete*/
            SchT->RunningData->NeedSync = FALSE;
            SchT->RunningData->State = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
        }
        else
        {
            /*Continue to sync */
            SchT->RunningData->NeedSync = TRUE;
            SchT->RunningData->State = SCHEDULETABLE_RUNNING;
        }
    }
    Status = E_OK;
    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_Sync
(
    ScheduleTableType SchTID,
    TickType SyncTick
)
{
    StatusType Status;
    TickType CurrentTick;
    TickType Offset;
    Os_IsrLevelType Level;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_SYNCSCHEDULETABLE);
    OS_ARTI_SC_BEGIN(SyncScheduleTable, SchTID);

    if (OsService_ExtendedErrorCheck(SchTID >= OS_SCHT_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_SETSCHEDULETABLESYNC)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else
    {
        SchT = OsSchT_Internal_GetSchTRef(SchTID);
        if (TRUE != OsApp_CheckObjectAccessingAppMask(SchT->ObjectID))
        {
            Status = E_OS_ACCESS;
        }
        else if(TRUE != OsApp_CheckObjectAppIsAccessiable(SchT->ObjectID))
        {
            Status = E_OS_ACCESS;
        }
        else if(OsService_ExtendedErrorCheck(!OsKernel_CheckObjectBelongToCurrentCore(SchT->ObjectID)))
        {
            Status = E_OS_CORE;
        }
        else if(OsService_ExtendedErrorCheck(SchT->OsScheduleTableSync.OsScheduleTblSyncStrategy != SCHEDULTTABLE_SYNC_EXPLICIT))
        {
            Status = E_OS_ID;
        }
        else if(OsService_ExtendedErrorCheck(SyncTick > SchT->OsScheduleTableDuration))
        {
            Status = E_OS_VALUE;
        }
        else if(OsService_ExtendedErrorCheck(SCHEDULETABLE_STOPPED == SchT->RunningData->State||SCHEDULETABLE_NEXT == SchT->RunningData->State))
        {
            Status = E_OS_VALUE;
        }
        else
        {
            Status = E_OK;
            /*The first time execute sync*/
            if (SCHEDULETABLE_WAITING == SchT->RunningData->State)
            {
                SchT->RunningData->Deviation = 0;
                OsSchT_Internal_Reset(SchT);

                OsCounter_GetCounterValue(SchT->CounterID, &CurrentTick);

                /*The tick value is duration - Synctick + initial offset*/
                //Offset = SchT->OsScheduleTableDuration - SyncTick;
                Offset = SyncTick;
                Offset += SchT->OsScheduleTableExpiryPoint[0]->OsScheduleTblExpPointOffset;

                /*Set the relative tick to counter and start to count */
                if(Offset>SchT->OsScheduleTableDuration)
                {
                    Offset = Offset%SchT->OsScheduleTableDuration;
                }
                OsSchT_Internal_SetToCounter(SchT, Offset, SCHEDULTTABLE_SET_RELATIVE);
                SchT->RunningData->State = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
                SchT->RunningData->CurrentEP = 0;
                SchT->RunningData->NeedSync = FALSE;
            }
            else if (SCHEDULETABLE_RUNNING == SchT->RunningData->State || SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS == SchT->RunningData->State)
            {

                /*The flag to sync will be check in callback function of schedule table*/
                SchT->RunningData->NeedSync = TRUE;

                /*disable the interrupt*/
                OsIsr_SuspendISR(&Level);
                /*Get sync tick when the next EP  , and then start sync */
                OsSchT_Internal_CalNextSyncEP(SchT, SyncTick);
                OsSchT_Internal_CheckSyncProcess(SchT);
                OsIsr_ResumeISR(Level);
            }
            else
            {
                Status = E_NOT_OK;
            }
        }
    }

    /*Error processing*/
    if (E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_SYNCSCHEDULETABLE, (InputParaType)SchTID, (InputParaType)SyncTick);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(SyncScheduleTable, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_SYNCSCHEDULETABLE);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_SetAsync
(
    ScheduleTableType SchTID
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_SETSCHEDULETABLEASYNC);
    OS_ARTI_SC_BEGIN(SetScheduleTableAsync, SchTID);

    if (OsService_ExtendedErrorCheck(SchTID >= OS_SCHT_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_SETSCHEDULETABLESYNC)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else
    {

        SchT = OsSchT_Internal_GetSchTRef(SchTID);
        if (TRUE != OsApp_CheckObjectAccessingAppMask(SchT->ObjectID))
        {
            Status = E_OS_ACCESS;
        }
        else if(TRUE != OsApp_CheckObjectAppIsAccessiable(SchT->ObjectID))
        {
            Status = E_OS_ACCESS;
        }
        else if(OsService_ExtendedErrorCheck(SchT->OsScheduleTableSync.OsScheduleTblSyncStrategy != SCHEDULTTABLE_SYNC_EXPLICIT))
        {
            Status = E_OS_ID;
        }
        else if(OsService_ExtendedErrorCheck(!OsKernel_CheckObjectBelongToCurrentCore(SchT->ObjectID)))
        {
            Status = E_OS_CORE;
        }
        else if(OsService_ExtendedErrorCheck(SCHEDULETABLE_STOPPED == SchT->RunningData->State ||
                SCHEDULETABLE_NEXT == SchT->RunningData->State   ||
                SCHEDULETABLE_WAITING == SchT->RunningData->State))
        {
            Status = E_OS_STATE;
        }
        else
        {
            if (SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS == SchT->RunningData->State ||
                SCHEDULETABLE_RUNNING == SchT->RunningData->State)
            {
                SchT->RunningData->State = SCHEDULETABLE_RUNNING;
                Status = E_OK;
            }
            /*[SWS_Os_00483] SCHEDULETABLE_STOPPED, SCHEDULETABLE_NEXT or SCHEULETABLE_WAITING shall return E_OS_STATE*/
            else
            {
                Status = E_OS_STATE;
            }
            SchT->RunningData->NeedSync = FALSE;
        }
    }

    /*Error processing*/
    if (E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_SETSCHEDULETABLEASYNC, (InputParaType)SchTID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(SetScheduleTableAsync, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_SETSCHEDULETABLEASYNC);

    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_GetStatus
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    ScheduleTableStatusRefType ScheduleStatus
)
{
    StatusType Status;

    if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_GETSCHEDULETABLESTATUS)))
    {
        Status = E_OS_CALLEVEL;
    }
    else if (OsService_ExtendedErrorCheck(TRUE == OsIsr_IsSuspendIsr()))
    {
        Status = E_OS_DISABLEDINT;
    }
    else if (TRUE != OsApp_CheckObjectAccessingAppMask(SchT->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else if(TRUE != OsApp_CheckObjectAppIsAccessiable(SchT->ObjectID))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        /*The schedule table is not in running or running sync state*/
        if (SchT->RunningData->State < SCHEDULETABLE_RUNNING)
        {
            /* return the current state*/
            *ScheduleStatus = (ScheduleTableStatusType)(SchT->RunningData->State);
        }
        else
        {
            /*Check the sync strategy  */
            switch (SchT->OsScheduleTableSync.OsScheduleTblSyncStrategy)
            {
                /*None sync strategy */
                case SCHEDULTTABLE_SYNC_NONE:
                {
                    *ScheduleStatus = SCHEDULETABLE_RUNNING;
                    break;
                }

                /* sync strategy is implicit */
                case SCHEDULTTABLE_SYNC_IMPLICIT:
                {
                    *ScheduleStatus = SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS;
                    break;
                }

                /* sync strategy is explicit */
                case SCHEDULTTABLE_SYNC_EXPLICIT:
                {

                    *ScheduleStatus = (ScheduleTableStatusType)(SchT->RunningData->State);
                    break;
                }

                default:
                    Status = E_OK;
                    break;
            }
        }
        Status = E_OK;
    }

    return Status;
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_GetStatus
(
    ScheduleTableType SchTID,
    ScheduleTableStatusRefType ScheduleStatus
)
{

    StatusType Status;
    Os_IsrLevelType Level;
    Os_IocInterCoreServiceCallType ServiceCallCfg;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_GETSCHEDULETABLESTATUS);
    OS_ARTI_SC_BEGIN(GetScheduleTableStatus, SchTID);

    if (OsService_ExtendedErrorCheck(SchTID >= OS_SCHT_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else
    {
        SchT = OsSchT_Internal_GetSchTRef(SchTID);
        if (TRUE == OsKernel_CheckObjectBelongToCurrentCore(SchT->ObjectID))
        {
            OsIsr_SuspendISR(&Level);
            /* Internal Get schedule Status */
            Status = OsSchT_GetStatus(SchT, ScheduleStatus);
            OsIsr_ResumeISR(Level);
        }
        else
        {
            /*Cross-Core*/
            ServiceCallCfg.ServiceId = OS_SERVICEID_GETSCHEDULETABLESTATUS;
            ServiceCallCfg.EntryAddress = (uint32)OsSchT_GetStatus;
            ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(SchT->ObjectID);
            ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)SchT;
            ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)ScheduleStatus;
            ServiceCallCfg.OutputParmMask = OS_IOC_OUTPUT_PARM1_MASK;
            ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
            Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            *ScheduleStatus = (ScheduleTableStatusType)ServiceCallCfg.OutParameter.OutParm[0];
        }
    }

    /*Error processing*/
    if (E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_GETSCHEDULETABLESTATUS, (InputParaType)SchTID, (InputParaType)ScheduleStatus);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(GetScheduleTableStatus, (E_OK == Status) ? (uint32)(*ScheduleStatus) : OS_ARTI_SC_INVALID);
    OsOrti_ServiceEnd(OS_SERVICEID_GETSCHEDULETABLESTATUS);

    return Status;
}

static FUNC(void, OS_CODE) OsSchT_Internal_Reset
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT
)
{
    /*Reset the schedule table data*/
    SchT->RunningData->CurrentEP = 0;
    SchT->RunningData->State = SCHEDULETABLE_STOPPED;
    SchT->RunningData->PreSchTID = SHCT_ID_MASK;
    SchT->RunningData->NextSchTID = SHCT_ID_MASK;
    SchT->RunningData->NeedStop = FALSE;
}

static FUNC(P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST), OS_CODE) OsSchT_Internal_GetSchTRef
(
    ScheduleTableType SchTID
)
{
    if(OsService_ExtendedErrorCheck(SchTID<OS_SCHT_TOTAL_NUM))
    {
        /*return the schedule table data information*/
        return Os_SchTConfigSet[SchTID];
    }
    else
    {
        return NULL_PTR;
    }
}

static FUNC(StatusType, OS_CODE) OsSchT_Internal_EPAction
(
    P2CONST(OsSchT_ExPoConfigType, TYPEDEF, OS_CONST) EP
)
{
    Os_StatusType Status;
    TaskType TaskID;
    uint32 CountNum;
    uint32 EventMask;
    Os_IocInterCoreServiceCallType ServiceCallCfg;

    /*The action include activate task ,then activate each task*/
    if (EP->TaskCount > 0)
    {
        for (CountNum = 0; CountNum < EP->TaskCount; CountNum++)
        {
            /*loop to activate task*/
            TaskID = EP->OsScheduleTableActivateTaskRef[CountNum];
            if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(OsTask_GetTaskConst(TaskID)->ObjectID))
            {
                /* Internal Activate Task on core */
                Status = OsTask_ActivateTask(TaskID);
            }
            else
            {
                /* Cross core service call */
                ServiceCallCfg.ServiceId = OS_SERVICEID_ACTIVATETASK;
                ServiceCallCfg.EntryAddress = (uint32)OsTask_ActivateTask;
                ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
                ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
                ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
                ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
                Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            }

            if(E_OK != Status)
            {
                OsHook_SetErrorParameterZero(OS_SERVICEID_ACTIVATETASK);
                OsHook_CallErrorHook(Status);
            }
        }
    }

    /*The action include set event ,then set event to corresponding task */
    if (EP->EventCount > 0)
    {
        for (CountNum = 0; CountNum < EP->EventCount; CountNum++)
        {
            /*loop to Set event to task*/
            TaskID = EP->OsScheduleTableSetEventRef[CountNum].OsSchTTask;
            EventMask = EP->OsScheduleTableSetEventRef[CountNum].OsSchTEventMask;
            if(TRUE == OsKernel_CheckObjectBelongToCurrentCore(OsTask_GetTaskConst(TaskID)->ObjectID))
            {
                Status = OsEvent_SetEvent(TaskID, EventMask);
            }
            else
            {
                /* Cross core service call */
                ServiceCallCfg.ServiceId = OS_SERVICEID_SETEVENT;
                ServiceCallCfg.EntryAddress = (uint32)OsEvent_SetEvent;
                ServiceCallCfg.TargetCoreId = OsApp_GetPhysicalCoreIDFromObjectInfo(OsTask_GetTaskConst(TaskID)->ObjectID);
                ServiceCallCfg.ParameterIn[0] = (Os_ServiceCallInputType)TaskID;
                ServiceCallCfg.ParameterIn[1] = (Os_ServiceCallInputType)EventMask;
                ServiceCallCfg.OutputParmMask = OS_IOC_NO_OUTPUT_PARM_MASK;
                ServiceCallCfg.ServiceType = OS_IOC_SERVICECALL_SYNC_UNHANDLED | OsApp_GetCurrent_ObjectID();
                Status = OsIoc_CrossCoreServiceCall(&ServiceCallCfg);
            }
            if(E_OK != Status)
            {
                OsHook_SetErrorParameterZero(OS_SERVICEID_SETEVENT);
                OsHook_CallErrorHook(Status);
            }
        }
    }

    return Status;
}

static FUNC(TickType, OS_CODE) OsSchT_Internal_GetNextEPOffset
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    uint32 CurrentEP
)
{
    TickType NextOffset;

    /*Next EP offset value subtract the current EP offset value */
    NextOffset = SchT->OsScheduleTableExpiryPoint[CurrentEP + 1]->OsScheduleTblExpPointOffset - SchT->OsScheduleTableExpiryPoint[CurrentEP]->OsScheduleTblExpPointOffset;
    return NextOffset;
}

static FUNC(TickType, OS_CODE) OsSchT_Internal_GetFirstEPOffset
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    uint32 CurrentEP
)
{
    TickType NextOffset;

    /*The remain offset tick value of the last EP */
    NextOffset = SchT->OsScheduleTableDuration - SchT->OsScheduleTableExpiryPoint[CurrentEP]->OsScheduleTblExpPointOffset;

    /*Plus the initial offset tick value of the first EP*/
    NextOffset += SchT->OsScheduleTableExpiryPoint[0]->OsScheduleTblExpPointOffset;
    return NextOffset;
}

static FUNC(TickType, OS_CODE) OsSchT_Internal_GetNextSchTOffset
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) NextSchT
)
{
    TickType NextOffset;
    uint32 CurrentEP;

    CurrentEP = SchT->RunningData->CurrentEP;
    /*The remain offset tick value of the last EP in the current schedule table*/
    NextOffset = SchT->OsScheduleTableDuration - SchT->OsScheduleTableExpiryPoint[CurrentEP]->OsScheduleTblExpPointOffset;

    /*Plus the initial offset tick value of the first EP in the next schedule table  */
    NextOffset += NextSchT->OsScheduleTableExpiryPoint[0]->OsScheduleTblExpPointOffset;
    return NextOffset;
}

static FUNC(P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST), OS_CODE) OsSchT_Internal_ProcessNextEP
(
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST) SchT,
    uint32 CurrentEP, P2VAR(TickType, TYPEDEF, OS_VAR) NextOffset
)
{
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)
    CurSchT;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)
    NextSchT;

    CurSchT = NULL_PTR;

    /*current schedule table not finish*/
    if (CurrentEP < (SchT->EPCount - 1))
    {
        *NextOffset = OsSchT_Internal_GetNextEPOffset(SchT, SchT->RunningData->CurrentEP);
        SchT->RunningData->CurrentEP++;
        CurSchT = SchT;
    }
    /* The current EP is the last EP in the current schedule table*/
    else
    {
        /*no next schedule */
        if (SHCT_ID_MASK == SchT->RunningData->NextSchTID)
        {
            /*The schedule is repeated */
            if (TRUE == SchT->OsScheduleTableRepeating)
            {
                /*get initial offset of the schedule table*/
                *NextOffset = OsSchT_Internal_GetFirstEPOffset(SchT, SchT->RunningData->CurrentEP);
                SchT->RunningData->CurrentEP = 0;
                CurSchT = SchT;
            }
            /*one single shot table*/
            else
            {
                /*stop the schedule table*/
                SchT->RunningData->NeedStop = TRUE;
                /*set offset tick value to 0*/
                *NextOffset = SchT->OsScheduleTableDuration - SchT->OsScheduleTableExpiryPoint[CurrentEP]->OsScheduleTblExpPointOffset;
                CurSchT = SchT;
            }
        }
        /*has the next schedule table*/
        else
        {

            /*change to the next schedule table */
            NextSchT = OsSchT_Internal_GetSchTRef(SchT->RunningData->NextSchTID);
            /*Get the next schedule table first offset value*/
            *NextOffset = OsSchT_Internal_GetNextSchTOffset(SchT, NextSchT);

            /*set next schedule table state and return the current Schedule table to next table*/
            NextSchT->RunningData->State = SCHEDULETABLE_RUNNING;
            NextSchT->RunningData->CurrentEP = 0;
            SchT->RunningData->State = SCHEDULETABLE_STOPPED;
            CurSchT = NextSchT;
        }
    }
    return CurSchT;
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

FUNC(void, OS_CODE)
OsSchedT_DoSchedulTable
(
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) Object
)
{
    uint32 SchTID;
    TickType NextOffset;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)
    SchT;
    P2CONST(OsSchT_ExPoConfigType, TYPEDEF, OS_CONST)
    EP;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)
    CurSchT;

    SchTID = Object->AppObjIDInfo & OBJECTID_MASK;
    SchT = OsSchT_Internal_GetSchTRef(SchTID);
    NextOffset = 0;

    if(TRUE == SchT->RunningData->NeedStop)
    {
        OsSchT_Internal_Reset(SchT);
    }
    else
    {
        EP = (SchT->OsScheduleTableExpiryPoint[SchT->RunningData->CurrentEP]);
        /*Process the EP action :activate task or set event */
        OsSchT_Internal_EPAction(EP);

        /*If the schedule need sync ,then do the sync process */
        if (SchT->RunningData->NeedSync == TRUE)
        {
            CurSchT = SchT;
            /*update the sync point position in schedule and get the next offset value*/
            OsSchT_Internal_UpdateNextSyncEP(SchT, SchT->RunningData->NextSysPointPos, &NextOffset);
            /*Check whether the sync process has been complete or continue to sync*/
            OsSchT_Internal_CheckSyncProcess(SchT);
        }
        else
        {
            /*otherwise, get the next EP offset tick value directly */
            CurSchT = OsSchT_Internal_ProcessNextEP(SchT, SchT->RunningData->CurrentEP, &NextOffset);
        }

        if ((NextOffset != 0U) && (NULL_PTR != CurSchT))
        {
            /*Check the offset should be in the range duration*/
            if(NextOffset>CurSchT->OsScheduleTableDuration)
            {
                NextOffset = NextOffset % CurSchT->OsScheduleTableDuration;
            }
            (void)OsSchT_Internal_SetToCounter(CurSchT, NextOffset, SCHEDULTTABLE_SET_RELATIVE);
        }
    }
}

FUNC(StatusType, OS_CODE)StartScheduleTableRel
(
    ScheduleTableType SchTID,
    TickType Offset
)
{
    StatusType Status;

    if (IsNeedSysTrap())
    {
        Os_Inf_TrapToSystemMode(); // switch to system mode.
        Status = OsSchT_Internal_StartRel(SchTID, Offset);
        Os_Inf_TrapToUserMode(); // switch to user mode.
    }
    else
    {
        Status = OsSchT_Internal_StartRel(SchTID, Offset);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)StartScheduleTableAbs
(
    ScheduleTableType SchTID,
    TickType Start
)
{
    StatusType Status;

    if (IsNeedSysTrap())
    {
        Os_Inf_TrapToSystemMode(); // switch to system mode.
        Status = OsSchT_Internal_StartAbs(SchTID, Start);
        Os_Inf_TrapToUserMode(); // switch to user mode.
    }
    else
    {
        Status = OsSchT_Internal_StartAbs(SchTID, Start);

    }

    return Status;
}

FUNC(StatusType, OS_CODE)StopScheduleTable
(
    ScheduleTableType SchTID
)
{
    StatusType Status;

    if (IsNeedSysTrap())
    {
        Os_Inf_TrapToSystemMode(); // switch to system mode.
        Status = OsSchT_Internal_Stop(SchTID);
        Os_Inf_TrapToUserMode(); // switch to user mode.
    }
    else
    {
        Status = OsSchT_Internal_Stop(SchTID);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)NextScheduleTable
(
    ScheduleTableType SchTID_From_ID,
    ScheduleTableType SchTID_To_ID
)
{
    StatusType Status;

    if (IsNeedSysTrap())
    {
        Os_Inf_TrapToSystemMode(); // switch to system mode.
        Status = OsSchT_Internal_Next(SchTID_From_ID, SchTID_To_ID);
        Os_Inf_TrapToUserMode(); // switch to user mode.
    }
    else
    {
        Status = OsSchT_Internal_Next(SchTID_From_ID, SchTID_To_ID);
    }

    return Status;
}

FUNC(StatusType, OS_CODE)StartScheduleTableSynchron
(
    ScheduleTableType SchTID
)
{
    StatusType Status;

    if (IsNeedSysTrap())
    {
        Os_Inf_TrapToSystemMode(); // switch to system mode.
        Status = OsSchT_Internal_StartSynchron(SchTID);
        Os_Inf_TrapToUserMode(); // switch to user mode.
    }
    else
    {
        Status = OsSchT_Internal_StartSynchron(SchTID);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) SyncScheduleTable
(
    ScheduleTableType SchTID, TickType Value
)
{
    StatusType Status;

    if (IsNeedSysTrap())
    {
        Os_Inf_TrapToSystemMode(); // switch to system mode.
        Status = OsSchT_Internal_Sync(SchTID, Value);
        Os_Inf_TrapToUserMode(); // switch to user mode.
    }
    else
    {
        Status = OsSchT_Internal_Sync(SchTID, Value);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) SetScheduleTableAsync
(
    ScheduleTableType SchTID
)
{
    StatusType Status;

    if (IsNeedSysTrap())
    {
        Os_Inf_TrapToSystemMode(); // switch to system mode.
        Status = OsSchT_Internal_SetAsync(SchTID);
        Os_Inf_TrapToUserMode(); // switch to user mode.
    }
    else
    {
        Status = OsSchT_Internal_SetAsync(SchTID);
    }

    return Status;
}

FUNC(StatusType, OS_CODE) GetScheduleTableStatus
(
    ScheduleTableType SchTID,
    ScheduleTableStatusRefType ScheduleStatus
)
{
    StatusType Status;

    if (IsNeedSysTrap())
    {
        Os_Inf_TrapToSystemMode(); // switch to system mode.
        Status = OsSchT_Internal_GetStatus(SchTID, ScheduleStatus);
        Os_Inf_TrapToUserMode(); // switch to user mode.
    }
    else
    {
        Status = OsSchT_Internal_GetStatus(SchTID, ScheduleStatus);
    }

    return Status;
}

FUNC(void, OS_CODE) OsSchT_Init
(
    ScheduleTableType SchTID,
    AppModeType AppMode
)
{
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)
    SchT;
    P2CONST(OsSchT_AutostartConfigType, TYPEDEF, OS_CONST)
    AutoConfigPtr;

    SchT = OsSchT_Internal_GetSchTRef(SchTID);
    OsSchT_Internal_Reset(SchT);
    AutoConfigPtr = &SchT->OsScheduleTableAutostart;

    if ((AutoConfigPtr->OsScheduleTableAppModeRef & AppMode) == AppMode)
    {
        /*Check Schedule table Auto start type */
        switch (AutoConfigPtr->OsScheduleTableAutostartType)
        {
        case SCHEDULTTABLE_AUTOSTART_RELATIVE:
            OsSchT_StartRel(SchT,AutoConfigPtr->OsScheduleTableStartValue);
            break;

        case SCHEDULTTABLE_AUTOSTART_SYNCHRON:
            OsSchT_StartSynchron(SchT);
            break;

        case SCHEDULTTABLE_AUTOSTART_ABSOLUTE:
            OsSchT_StartAbs(SchT, AutoConfigPtr->OsScheduleTableStartValue);
            break;

        case SCHEDULTTABLE_AUTOSTART_NONE:
        default:
            break;
        }
    }
}

FUNC(StatusType, OS_CODE)OsSchT_DeInit
(
    ScheduleTableType SchTID
)
{
    StatusType Status;
    uint32 ObjectID;
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST)   SchTObjectPtr;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)   SchT;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)   PreSchT;
    P2CONST(OsSchT_ConfigType, TYPEDEF, OS_CONST)   NextSchT;

    SchT = OsSchT_Internal_GetSchTRef(SchTID);
    OsSchT_Internal_Reset(SchT);
    ObjectID = SchT->ObjectID;
    SchTObjectPtr = OsApp_GetSpecific_ObjectInfo(ObjectID);

    /*The current Schedule table is in state NEXT */
    if (SCHEDULETABLE_NEXT == SchT->RunningData->State)
    {
        /*Change the previous Schedule table next ID to invalid*/
        PreSchT = OsSchT_Internal_GetSchTRef(SchT->RunningData->PreSchTID);
        PreSchT->RunningData->NextSchTID = SHCT_ID_MASK;
    }
    /*The current ScheT is in running state*/
    else if (SCHEDULETABLE_RUNNING == SchT->RunningData->State || SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS == SchT->RunningData->State)
    {
        /*remove schedule table from counter*/
        Status = OsCounter_RemoveObject(SchTObjectPtr);

        /*if the current SchT has next SchT , stop change the next SchT */
        if (SchT->RunningData->NextSchTID != SHCT_ID_MASK)
        {
            NextSchT = OsSchT_Internal_GetSchTRef(SchT->RunningData->NextSchTID);
            /*Stop the next schedule table */
            NextSchT->RunningData->State = SCHEDULETABLE_STOPPED;
            NextSchT->RunningData->PreSchTID = SHCT_ID_MASK;
            SchT->RunningData->NextSchTID = SHCT_ID_MASK;
        }
    }
    else
    {
        // do nothing
    }

    SchT->RunningData->State = SCHEDULETABLE_STOPPED;
    OsSchT_Internal_Reset(SchT);
    Status = E_OK;
    return Status;
}

/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_hook.h
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
#ifndef OS_HOOK_H_
#define OS_HOOK_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_GeneralTypes.h"
#include "Os_application_types.h"
#include "Os_kernel.h"
#include "Os_hook_types.h"
#include "Os_hook_Cfg.h"
#include "Os_alarm_types.h"
#include "Os_task_types.h"
#include "Os_task.h"
#include "Os_scheduletable_types.h"
#include "Os_resource_types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define OsHook_SetErrorParameterZero(SerivceID)                                                           \
do {                                                                                                     \
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.ServiceID = (Os_ServiceType)SerivceID;         \
} while(0)

#define OsHook_SetErrorParameterOne(SerivceID, Parameter0)                                                \
do {                                                                                                     \
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.ServiceID = (Os_ServiceType)SerivceID;         \
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0] = (InputParaType)Parameter0;\
} while(0)

#define OsHook_SetErrorParameterTwo(SerivceID, Parameter0, Parameter1)                                       \
do {                                                                                                     \
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.ServiceID = (Os_ServiceType)SerivceID;         \
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0] = (InputParaType)Parameter0;\
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1] = (InputParaType)Parameter1;\
} while(0)

#define OsHook_SetErrorParameterThree(SerivceID, Parameter0, Parameter1, Parameter2)                        \
do {                                                                                                     \
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.ServiceID = (Os_ServiceType)SerivceID;         \
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0] = (InputParaType)Parameter0;\
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1] = (InputParaType)Parameter1;\
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2] = (InputParaType)Parameter2;\
} while(0)

#define OsHook_SetErrorParameterFour(SerivceID, Parameter0, Parameter1, Parameter2, Parameter3)               \
do {                                                                                                     \
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.ServiceID = (Os_ServiceType)SerivceID;         \
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0] = (InputParaType)Parameter0;\
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1] = (InputParaType)Parameter1;\
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2] = (InputParaType)Parameter2;\
    OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[3] = (InputParaType)Parameter3;\
} while(0)

#if (STD_ON == OSUSEPARAMETERACCESS)
#define OSErrorGetServiceId()                OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.ServiceID
#endif

#if (STD_ON == OSUSEGETSERVICEID)
#define OSError_DisableInterruptSource_ISRID                                                            \
       (ISRType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_EnableInterruptSource_ISRID                                                             \
       (ISRType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_EnableInterruptSource_ClearPending                                                      \
       OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ClearPendingInterrupt_ISRID                                                             \
       (ISRType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_CallTrustedFunction_FunctionIndex                                                       \
       (TrustedFunctionIndexType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_CallTrustedFunction_FunctionParams                                                      \
       (TrustedFunctionParameterRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_StartScheduleTableRel_ScheduleTableID                                                   \
       (ScheduleTableType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_StartScheduleTableRel_Offset                                                            \
       (TickType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_StartScheduleTableAbs_ScheduleTableID                                                   \
       (ScheduleTableType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_StartScheduleTableAbs_Start                                                             \
       (TickType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_StopScheduleTable_ScheduleTableID                                                       \
       (ScheduleTableType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_NextScheduleTable_ScheduleTableID_From                                                  \
       (ScheduleTableType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_NextScheduleTable_ScheduleTableID_To                                                    \
       (ScheduleTableType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_StartScheduleTableSynchron_ScheduleTableID                                              \
       (ScheduleTableType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_SyncScheduleTable_ScheduleTableID                                                       \
       (ScheduleTableType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_SyncScheduleTable_Value                                                                 \
       (TickType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_SetScheduleTableAsync_ScheduleTableID                                                   \
       (ScheduleTableID)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetScheduleTableStatus_ScheduleTableID                                                  \
       (ScheduleTableID)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetScheduleTableStatus_ScheduleStatus                                                   \
       (ScheduleTableStatusRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_IncrementCounter_CounterID                                                              \
       (CounterType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetCounterValue_CounterID                                                               \
       (CounterType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetCounterValue_Value                                                                   \
       (TickRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_GetElapsedValue_CounterID                                                               \
       (CounterType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetElapsedValue_Value                                                                   \
       (TickRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_GetElapsedValue_ElapsedValue                                                            \
       (TickRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_TerminateApplication_Application                                                        \
       (ApplicationType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_TerminateApplication_RestartOption                                                      \
       (RestartType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_GetApplicationState_Application                                                         \
       (ApplicationType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetApplicationState_Value                                                               \
       (ApplicationStateRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_GetSpinlock_SpinlockId                                                                  \
       (SpinlockIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ReleaseSpinlock_SpinlockId                                                              \
       (SpinlockIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_TryToGetSpinlock_SpinlockId                                                             \
       (SpinlockIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_TryToGetSpinlock_Success                                                                \
       (P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR))OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ControlIdle_CoreID                                                                      \
       (CoreIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ControlIdle_IdleMode                                                                    \
       (IdleModeType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ActivateTask_TaskID                                                                     \
       (TaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ChainTask_TaskID                                                                        \
       (TaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ActivateTaskAsyn_TaskID                                                                 \
       (TaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetTaskID_TaskID                                                                        \
       (TaskRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetTaskState_TaskID                                                                     \
       (TaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetTaskState_State                                                                      \
       (TaskStateRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_SetEvent_TaskID                                                                         \
       (TaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_SetEvent_Mask                                                                           \
       (EventMaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_SetEventAsyn_TaskID                                                                     \
       (TaskRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_SetEventAsyn_Mask                                                                       \
       (EventMaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ClearEvent_Mask                                                                         \
       (EventMaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetEvent_TaskID                                                                         \
       (TaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetEvent_Mask                                                                           \
       (EventMaskRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_WaitEvent_Mask                                                                          \
       (EventMaskType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetAlarmBase_AlarmID                                                                    \
       (AlarmType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetAlarmBase_Info                                                                       \
       (AlarmBaseRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_GetAlarm_AlarmID                                                                        \
       (AlarmType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetAlarm_Tick                                                                           \
       (TickRefType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_SetRelAlarm_AlarmID                                                                     \
       (AlarmType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_SetRelAlarm_increment                                                                   \
       (TickType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_SetRelAlarm_cycle                                                                       \
       (TickType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_SetAbsAlarm_AlarmID                                                                     \
       (AlarmType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_SetAbsAlarm_start                                                                       \
       (TickType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_SetAbsAlarm_cycle                                                                       \
       (TickType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_CancelAlarm_AlarmID                                                                     \
       (AlarmType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_GetResource_ResID                                                                       \
       (ResourceType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ReleaseResource_ResID                                                                   \
       (ResourceType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ReadPeripheral8_Area                                                                    \
       (AreaIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ReadPeripheral8_Address                                                                 \
       (const uint8*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ReadPeripheral8_ReadValue                                                               \
       (uint8*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_ReadPeripheral16_Area                                                                   \
       (AreaIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ReadPeripheral16_Address                                                                \
       (const uint16*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ReadPeripheral16_ReadValue                                                              \
       (uint16*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_ReadPeripheral32_Area                                                                   \
       (AreaIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ReadPeripheral32_Address                                                                \
       (const uint32*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ReadPeripheral32_ReadValue                                                              \
       (uint32*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_WritePeripheral8_Area                                                                   \
       (AreaIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_WritePeripheral8_Address                                                                \
       (uint8*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_WritePeripheral8_WriteValue                                                             \
       (uint8)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_WritePeripheral16_Area                                                                  \
       (AreaIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_WritePeripheral16_Address                                                               \
       (uint16*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_WritePeripheral16_WriteValue                                                            \
       (uint16)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_WritePeripheral32_Area                                                                  \
       (AreaIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_WritePeripheral32_Address                                                               \
       (uint32*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_WritePeripheral32_WriteValue                                                            \
       (uint32)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_ModifyPeripheral8_Area                                                                  \
       (AreaIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ModifyPeripheral8_Address                                                               \
       (uint8*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ModifyPeripheral8_Clearmask                                                             \
       (uint8)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_ModifyPeripheral8_Setmask                                                               \
       (uint8)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[3]

#define OSError_ModifyPeripheral16_Area                                                                 \
       (AreaIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ModifyPeripheral16_Address                                                              \
       (uint16*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ModifyPeripheral16_Clearmask                                                            \
       (uint16)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_ModifyPeripheral16_Setmask                                                              \
       (uint16)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[3]

#define OSError_ModifyPeripheral32_Area                                                                 \
       (AreaIdType)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[0]

#define OSError_ModifyPeripheral32_Address                                                              \
       (uint32*)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[1]

#define OSError_ModifyPeripheral32_Clearmask                                                            \
       (uint32)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[2]

#define OSError_ModifyPeripheral32_Setmask                                                              \
       (uint32)OsKernel_GetCurrentCoreHookDataInfo()->ErrorDetailInfo.InputParameter[3]
#endif

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
/****************************************************************************************************
*   Function Name           : OsHook_CallErrorHook
*   Service ID              : None.
*   Description             : Internally call Errorhook
*   Parameters in           : Error:
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_CallErrorHook
(
    StatusType Error
);
/****************************************************************************************************
*   Function Name           : OsHook_CallProtectionHook
*   Service ID              : None.
*   Description             : System call ProtectionHook
*   Parameters in           : FatalError: fatal error code
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_CallProtectionHook
(
    StatusType FatalError
);

/****************************************************************************************************
*   Function Name           : OsHook_CallCoreStartupHook
*   Service ID              : None.
*   Description             : Use to Call Core start up hook.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_CallCoreStartupHook
(
    void
);

/****************************************************************************************************
*   Function Name           : OsHook_CallAppStartupHook
*   Service ID              : None.
*   Description             : Use to Call App StartUp hook.
*   Parameters in           : AppID: Application Id index.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_CallAppStartupHook
(
    uint32 AppID
);

/****************************************************************************************************
*   Function Name           : OsHook_CallPostTaskHook
*   Service ID              : None.
*   Description             : Use to Call post task hook.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_CallPostTaskHook
(
    void
);

/****************************************************************************************************
*   Function Name           : OsHook_CallPreTaskHook
*   Service ID              : None.
*   Description             : Use to Call pre task hook.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_CallPreTaskHook
(
    void
);

/****************************************************************************************************
*   Function Name           : OsHook_CallCoreShutdownHook
*   Service ID              : None.
*   Description             : Use to Call Core Shutdown hook
*   Parameters in           : FatalError: fatal error code.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_CallCoreShutdownHook
(
    StatusType FatalError
);

/****************************************************************************************************
*   Function Name           : OsHook_CallAppShutdownHook
*   Service ID              : None.
*   Description             : Use to Call Application Shutdown hook
*   Parameters in           : FatalError: fatal error code.
*                           : AppID: Application Id index.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_CallAppShutdownHook
(
    StatusType FatalError,
    uint32 AppID
);

/****************************************************************************************************
*   Function Name           : OsHook_Hookreturn
*   Service ID              : None.
*   Description             : Hook return is called when hook is finished
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_Hookreturn
(
     void
);

/****************************************************************************************************
*   Function Name           : OsHook_InitHook
*   Service ID              : None.
*   Description             : Init Hook is called in OS Initialization
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_InitHook
(
    void
);

/****************************************************************************************************
*   Function Name           : OsHook_UnHandledException
*   Service ID              : None.
*   Description             : Process unhandled Exception.
*   Parameters in           : ExceptionAddress: Exception Address.
*                           : SupervisorMode: Exception occurs at Supervisor mode.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_UnHandledException
(
    uint32 ExceptionAddress,
    boolean SupervisorMode
);

/****************************************************************************************************
*   Function Name           : OsHook_MemAccessException
*   Service ID              : None.
*   Description             : Process memory Access Exception.
*   Parameters in           : ExceptionAddress: Exception Address.
*                           : SupervisorMode: Exception occurs at Supervisor mode.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsHook_MemAccessException
(
    uint32 ExceptionAddress,
    boolean SupervisorMode
);

/****************************************************************************************************
*   Function Name           : GetErrorInformation
*   Service ID              : None.
*   Description             : GetDetailed error information
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) GetErrorInformation
(
    P2VAR(Os_HookErrorDetail, TYPEDEF, OS_VAR)
);

#endif /* OS_HOOK_H_ */

/****************************************************************************************************
**     End of File: Os_hook.h                                                                     **
****************************************************************************************************/


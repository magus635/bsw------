/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_alarm.h
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
#ifndef OS_ALARM_H_
#define OS_ALARM_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_alarm_types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

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
*   Function Name           : OsAlarm_AlarmInit
*   Service ID              : None.
*   Description             : Initialize Alarm
*   Parameters in           : AlarmID: the Alarm to add to be initialized
*                           : AppMode: The running app mode
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsAlarm_AlarmInit
(
    AlarmType AlarmID,
    AppModeType AppMode
);

/****************************************************************************************************
*   Function Name           : OsAlarm_AlarmDeinit
*   Service ID              : None.
*   Description             : DeInitialize Alarm
*   Parameters in           : AlarmID: the Alarm to add to be initialized
*                           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE)OsAlarm_AlarmDeinit
(
    AlarmType AlarmID
);

/****************************************************************************************************
*   Function Name           : OsAlarm_DoAlarm
*   Service ID              : None.
*   Description             : Callback for Do alarm
*   Parameters in           : AlarmObjectPtr
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE)OsAlarm_DoAlarm
(
    P2CONST(Os_AppObjectType, TYPEDEF, OS_CONST) AlarmObjectPtr
);

/****************************************************************************************************
*   Function Name           : OsAlarm_CancelAlarm
*   Service ID              : None.
*   Description             : Cancel Alarm on local core
*   Parameters in           : AlarmObjectPtr
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsAlarm_CancelAlarm
(
    AlarmType AlarmID
);

/****************************************************************************************************
*   Function Name           : OsAlarm_GetAlarm
*   Service ID              : None.
*   Description             : Get Alarm on local core
*   Parameters in           : AlarmID
*                           : Tick
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsAlarm_GetAlarm
(
    AlarmType AlarmID,
    TickRefType Tick
);

/****************************************************************************************************
*   Function Name           : OsAlarm_GetAlarmBase
*   Service ID              : None.
*   Description             : Get Alarm on local core
*   Parameters in           : AlarmID
*                           : Info
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsAlarm_GetAlarmBase
(
    AlarmType AlarmID,
    AlarmBaseRefType Info
);

/****************************************************************************************************
*   Function Name           : OsAlarm_SetRelAlarm
*   Service ID              : None.
*   Description             : Get Alarm on local core
*   Parameters in           : AlarmID
*                           : Increment
*                           : Cycle
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsAlarm_SetRelAlarm
(
    AlarmType AlarmID,
    TickType Increment,
    TickType Cycle
);

/****************************************************************************************************
*   Function Name           : OsAlarm_SetAbsAlarm
*   Service ID              : None.
*   Description             : Get Alarm on local core
*   Parameters in           : AlarmID
*                           : Start
*                           : Cycle
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsAlarm_SetAbsAlarm
(
    AlarmType AlarmID,
    TickType Start,
    TickType Cycle
);

#endif /* OS_ALARM_H_ */

/****************************************************************************************************
**     End of File: Os_alarm.h                                                                      **
****************************************************************************************************/


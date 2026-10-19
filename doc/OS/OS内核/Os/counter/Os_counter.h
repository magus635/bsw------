/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_counter.h
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
#ifndef OS_COUNTER_H_
#define OS_COUNTER_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Compiler.h"
#include "Os_counter_types.h"
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
*   Function Name           : OsCounter_Init
*   Service ID              : None.
*   Description             : Initialize related counter dataBase.
*   Parameters in           : CounterID. Indicate which counter is to be initialized.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsCounter_Init
(
    CounterType CounterID
);

/****************************************************************************************************
*   Function Name           : OsCounter_Start
*   Service ID              : None.
*   Description             : Start related counter.
*   Parameters in           : CounterID. Indicate which counter is to be started.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : Called after OsCounter_Init.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsCounter_Start
(
    CounterType CounterID
);

/****************************************************************************************************
*   Function Name           : OsCounter_AddAbsObject
*   Service ID              : None.
*   Description             : Add a ScheduleTable/Alarm object to counter queue with absolute tick.
*   Parameters in           : Object. Pointer of Alarm/Schedule object structure
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsCounter_AddAbsObject
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) Object
);

/****************************************************************************************************
*   Function Name           : OsCounter_AddRelObject
*   Service ID              : None.
*   Description             : Add a ScheduleTable/Alarm object to counter queue with related tick.
*   Parameters in           : Object. Pointer of Alarm/Schedule object structure.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsCounter_AddRelObject
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) Object
);

/****************************************************************************************************
*   Function Name           : OsCounter_RemoveObject
*   Service ID              : None.
*   Description             : Remove a specified Alarm/ScheduleTable from counter queue.
*   Parameters in           : Object. Pointer of Alarm/Schedule object structure.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType. E_OK indicates success and others indicate failure.
*   Preconditions           : Called after OsCounter_Init.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsCounter_RemoveObject
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) Object
);

/****************************************************************************************************
*   Function Name           : OsCounter_GetObjectRelTick
*   Service ID              : None.
*   Description             : Get tick difference of the Object between node expiration tick and current tick.
*   Parameters in           : Object. Pointer of Alarm/Schedule object structure.
*   Parameters in           : None:
*   Parameters inout        : None.
*   Parameters out          : Tick. Refer to store the tick difference of object.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType. E_OK indicates success and others indicate failure.
*   Preconditions           : Called after OsCounter_Init.
*   AUTOSAR_Requirement     Tick: None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsCounter_GetObjectRelTick
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) Object,
    TickRefType     Tick
);

/****************************************************************************************************
*   Function Name           : OsCounter_IncrementCounter
*   Service ID              : None.
*   Description             : Increase specified counter count value.
*   Parameters in           : CounterID. Counter identification.
*                           : DoSchedule. whether do task schedule. Set to FALSE
*   Parameters inout        : None.
*   Parameters out          : None
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : Called after OsCounter_Init.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsCounter_IncrementCounter
(
    CounterType CounterID,
    boolean     DoSchedule
);

/****************************************************************************************************
*   Function Name           : OsCounter_GetCounterValue
*   Service ID              : None.
*   Description             : Get specified counter count value.
*   Parameters in           : CounterID. Counter identification.
*   Parameters inout        : None.
*   Parameters out          : Value. store counter value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : Called after OsCounter_Init.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) OsCounter_GetCounterValue
(
    CounterType CounterID,
    TickRefType Value
);

/****************************************************************************************************
*   Function Name           : OsCounter_GetElapsedValue
*   Service ID              : None.
*   Description             : Get specified counter elapsed value.
*   Parameters in           : CounterID. Counter identification.
*   Parameters inout        : Value. Base tick for input and store current counter tick for output
*   Parameters out          : ElapsedValue. Store elapsed ticks between current count and input value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType. E_OK indicates success and others indicate failure.
*   Preconditions           : Called after OsCounter_Init.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(StatusType, OS_CODE) OsCounter_GetElapsedValue
(
    CounterType CounterID,
    TickRefType Value,
    TickRefType ElapsedValue
);

/****************************************************************************************************
*   Function Name           : OsCounter_GetBaseInfo
*   Service ID              : None.
*   Description             : Get counter basic information.
*   Parameters in           : CounterID. Counter identification.
*   Parameters inout        : None
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Os_CounterAttributeConfigType. Pointer of counter basic information.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(P2CONST(Os_CounterAttributeConfigType, AUTOMATIC, OS_CONST), OS_CODE) OsCounter_GetBaseInfo
(
    CounterType CounterID
);

/****************************************************************************************************
*   Function Name           : Isr_OsCounter_PfrtService
*   Service ID              : None.
*   Description             : Interrupt service of counter which is drove by period free running timer.
*   Parameters in           : None.
*   Parameters inout        : None
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern ISR(OsCounter_PfrtService);

/****************************************************************************************************
*   Function Name           : Isr_OsCounter_PitService
*   Service ID              : None.
*   Description             : Interrupt service of counter which is drove by period interrupt timer.
*   Parameters in           : None.
*   Parameters inout        : None
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern ISR(OsCounter_PitService);

/****************************************************************************************************
*   Function Name           : Isr_OsCounter_HrtService
*   Service ID              : None.
*   Description             : Interrupt service of counter which is drove by high resolution timer.
*   Parameters in           : None.
*   Parameters inout        : None
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern ISR(OsCounter_HrtService);

#endif /* OS_COUNTER_H_ */

/****************************************************************************************************
**     End of File: Os_counter.h                                                                   **
****************************************************************************************************/


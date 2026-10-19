/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os.h
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
#ifndef OS_H_
#define OS_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_task_types.h"
#include "Os_GeneralTypes.h"
#include "Os_isr_types.h"
#include "Os_resource_types.h"
#include "Os_event_types.h"
#include "Os_alarm_types.h"
#include "Os_hook_types.h"
#include "Os_mpu_types.h"
#include "Os_spinlock_types.h"
#include "Os_scheduletable_types.h"
#include "Os_services_types.h"
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
*   Function Name           : ActivateTask
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ActivateTask
(
    TaskType TaskID
);
/****************************************************************************************************
*   Function Name           : ActivateTaskAsyn
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) ActivateTaskAsyn
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : TerminateTask
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) TerminateTask
(
    void
);

/****************************************************************************************************
*   Function Name           : ChainTask
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ChainTask
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : Schedule
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) Schedule
(
    void
);

/****************************************************************************************************
*   Function Name           : GetTaskID
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetTaskID
(
    TaskRefType TaskID
);

/****************************************************************************************************
*   Function Name           : GetTaskState
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetTaskState
(
    TaskType TaskID,
    TaskStateRefType State
);

/****************************************************************************************************
*   Function Name           : SetEvent
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) SetEvent
(
        TaskType TaskID,
        EventMaskType Mask
);

/****************************************************************************************************
*   Function Name           : SetEventAsyn
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) SetEventAsyn
(
        TaskType TaskID,
        EventMaskType Mask
);

/****************************************************************************************************
*   Function Name           : ClearEvent
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ClearEvent
(
        EventMaskType Mask
);

/****************************************************************************************************
*   Function Name           : GetEvent
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetEvent
(
        TaskType TaskID,
        EventMaskRefType Event
);

/****************************************************************************************************
*   Function Name           : WaitEvent
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) WaitEvent
(
        EventMaskType Mask
);

/****************************************************************************************************
*   Function Name           : GetAlarmBase
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetAlarmBase
(
        AlarmType AlarmID,
        AlarmBaseRefType Info
);

/****************************************************************************************************
*   Function Name           : GetAlarm
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetAlarm
(
        AlarmType AlarmID,
        TickRefType Tick
);

/****************************************************************************************************
*   Function Name           : SetRelAlarm
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) SetRelAlarm
(
        AlarmType AlarmID,
        TickType Increment,
        TickType Cycle
);

/****************************************************************************************************
*   Function Name           : SetAbsAlarm
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) SetAbsAlarm
(
        AlarmType AlarmID,
        TickType Start,
        TickType Cycle
);

/****************************************************************************************************
*   Function Name           : CancelAlarm
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) CancelAlarm
(
        AlarmType AlarmID
);

/****************************************************************************************************
*   Function Name           : EnableAllInterrupts
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) EnableAllInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : DisableAllInterrupts
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) DisableAllInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : ResumeAllInterrupts
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) ResumeAllInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : SuspendAllInterrupts
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) SuspendAllInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : ResumeOSInterrupts
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) ResumeOSInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : SuspendOSInterrupts
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) SuspendOSInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : GetISRID
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : SWS_Os_00511
****************************************************************************************************/
extern FUNC(ISRType, OS_CODE) GetISRID
(
    void
);

/****************************************************************************************************
*   Function Name           : DisableInterruptSource
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : SWS_Os_91019
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) DisableInterruptSource
(
    ISRType ISRID
);

/****************************************************************************************************
*   Function Name           : EnableInterruptSource
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : SWS_Os_91020
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) EnableInterruptSource
(
    ISRType ISRID,
    boolean ClearPending
);

/****************************************************************************************************
*   Function Name           : ClearPendingInterrupt
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : SWS_Os_91021
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ClearPendingInterrupt
(
    ISRType ISRID
);

/****************************************************************************************************
*   Function Name           : CheckISRMemoryAccess
*   Service ID              : 0x03.
*   Description             : This service checks if a memory region is write/read/execute accessible and also returns
*                             information if the memory region is part of the stack space.
*   Parameters in           : ISRID:ISR reference
*                             Address: Start of memory area
*                             Size: Size of memory area .
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : OsAccess_RightType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00512].
****************************************************************************************************/
extern FUNC(OsAccess_RightType, OS_CODE) CheckISRMemoryAccess
(
    ISRType ISRID,
    MemoryStartAddressType Address,
    MemorySizeType Size
);

/****************************************************************************************************
*   Function Name           : CheckTaskMemoryAccess
*   Service ID              : 0x04.
*   Description             : This service checks if a memory region is write/read/execute accessible and also returns
*                             information if the memory region is part of the stack space.
*   Parameters in           : TaskID:Task reference
*                             Address: Start of memory area
*                             Size: Size of memory area .
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : OsAccess_RightType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00513].
****************************************************************************************************/
extern FUNC(OsAccess_RightType, OS_CODE) CheckTaskMemoryAccess
(
    TaskType TaskID,
    MemoryStartAddressType Address,
    MemorySizeType Size
);

/****************************************************************************************************
*   Function Name           : ReadPeripheral8
*   Service ID              : 0x28.
*   Description             : This service returns the content of a given memory location (<Address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address: memory address
*   Parameters inout        : None.
*   Parameters out          : ReadValue :content of the given memory location (<Address>) .
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_91013] Definition of API function ReadPeripheral8.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ReadPeripheral8
(
    AreaIdType Area,
    const uint8* Address,
    uint8* ReadValue
);

/****************************************************************************************************
*   Function Name           : ReadPeripheral16
*   Service ID              : 0x29.
*   Description             : This service returns the content of a given memory location (<Address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address: memory address
*   Parameters inout        : None.
*   Parameters out          : ReadValue :content of the given memory location (<Address>) .
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_91015] Definition of API function ReadPeripheral16.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ReadPeripheral16 
(
    AreaIdType Area,
    const uint16* Address,
    uint16* ReadValue
);

/****************************************************************************************************
*   Function Name           : ReadPeripheral32
*   Service ID              : 0x2a.
*   Description             : This service returns the content of a given memory location (<Address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address: memory address
*   Parameters inout        : None.
*   Parameters out          : ReadValue :content of the given memory location (<Address>) .
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_91014] Definition of API function ReadPeripheral32.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ReadPeripheral32 
(
    AreaIdType Area,
    const uint32* Address,
    uint32* ReadValue
);

/****************************************************************************************************
*   Function Name           : WritePeripheral8
*   Service ID              : 0x2b.
*   Description             : This service writes the <value> to a given memory location (<memory address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             WriteValue :value to be written at the memory address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_91010] Definition of API function WritePeripheral8.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) WritePeripheral8 
(
    AreaIdType Area,
    uint8* Address,
    uint8 WriteValue
);

/****************************************************************************************************
*   Function Name           : WritePeripheral16
*   Service ID              : 0x2c.
*   Description             : This service writes the <value> to a given memory location (<memory address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             WriteValue :value to be written at the memory address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_91012] Definition of API function WritePeripheral16 .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) WritePeripheral16 
(
    AreaIdType Area,
    uint16* Address,
    uint16 WriteValue
);

/****************************************************************************************************
*   Function Name           : WritePeripheral32
*   Service ID              : 0x2d.
*   Description             : This service writes the <value> to a given memory location (<memory address>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             WriteValue :value to be written at the memory address
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_91011] Definition of API function WritePeripheral32 .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) WritePeripheral32 
(
    AreaIdType Area,
    uint32* Address,
    uint32 WriteValue
);

/****************************************************************************************************
*   Function Name           : ModifyPeripheral8
*   Service ID              : 0x2e.
*   Description             : This service modifies a given memory location (<memory address>) with the formula:
*                              <Address> = ((*<Address> & <clearmask>) | <setmask>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             Clearmask :memory address will be modified by an bit-AND
*                             Setmask :memory address will be modified by an bit-OR
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_91016] Definition of API function ModifyPeripheral8 .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ModifyPeripheral8 
(
    AreaIdType Area,
    uint8* Address,
    uint8 Clearmask,
    uint8 Setmask
);

/****************************************************************************************************
*   Function Name           : ModifyPeripheral16
*   Service ID              : 0x35.
*   Description             : This service modifies a given memory location (<memory address>) with the formula:
*                              <Address> = ((*<Address> & <clearmask>) | <setmask>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             Clearmask :memory address will be modified by an bit-AND
*                             Setmask :memory address will be modified by an bit-OR
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_91018] Definition of API function ModifyPeripheral16 .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ModifyPeripheral16 
(
    AreaIdType Area,
    uint16* Address,
    uint16 Clearmask,
    uint16 Setmask
);

/****************************************************************************************************
*   Function Name           : ModifyPeripheral32
*   Service ID              : 0x2f.
*   Description             : This service modifies a given memory location (<memory address>) with the formula:
*                              <Address> = ((*<Address> & <clearmask>) | <setmask>).
*   Parameters in           : Area :hardware peripheral area reference
*                             Address :memory address
*                             Clearmask :memory address will be modified by an bit-AND
*                             Setmask :memory address will be modified by an bit-OR
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_91017] Definition of API function ModifyPeripheral32 .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ModifyPeripheral32 
(
    AreaIdType Area,
    uint32* Address,
    uint32 Clearmask,
    uint32 Setmask
);

/****************************************************************************************************
*   Function Name           : StartOS
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) StartOS
(
    AppModeType Mode
);

/****************************************************************************************************
*   Function Name           : ShutdownOS
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) ShutdownOS
(
    StatusType Error
);

/****************************************************************************************************
*   Function Name           : StartCore
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) StartCore 
(
    CoreIdType CoreID,
    StatusType* Status
);

/****************************************************************************************************
*   Function Name           : ShutdownAllCores
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) ShutdownAllCores 
(
    StatusType Error
);

/****************************************************************************************************
*   Function Name           : ControlIdle
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ControlIdle
(
    CoreIdType CoreID,
    IdleModeType IdleMode
);

/****************************************************************************************************
*   Function Name           : GetNumberOfActivatedCores
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) GetNumberOfActivatedCores 
(
    void
);

/****************************************************************************************************
*   Function Name           : GetActiveApplicationMode
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(AppModeType, OS_CODE) GetActiveApplicationMode
(
    void
);

/****************************************************************************************************
*   Function Name           : isOsStarted
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) isOsStarted
(
    void
);

/****************************************************************************************************
*   Function Name           : GetCoreID
*   Service ID              : 0x16.
*   Description             : The function returns a unique core identifier.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00674].
****************************************************************************************************/
extern FUNC(CoreIdType, OS_CODE) GetCoreID
(
    void
);

/****************************************************************************************************
*   Function Name           : GetApplicationID
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(ApplicationType, OS_CODE) GetApplicationID
(
    void
);

/****************************************************************************************************
*   Function Name           : GetCurrentApplicationID
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(ApplicationType, OS_CODE) GetCurrentApplicationID
(
    void
);

/****************************************************************************************************
*   Function Name           : CheckObjectOwnership
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(ApplicationType, OS_CODE) CheckObjectOwnership
(
    ObjectTypeType ObjectType,
    uint32 ObjectID
);

/****************************************************************************************************
*   Function Name           : CheckObjectAccess
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(ObjectAccessType, OS_CODE) CheckObjectAccess
(
    ApplicationType ApplID,
    ObjectTypeType ObjectType,
    uint32 ObjectID
);

/****************************************************************************************************
*   Function Name           : GetApplicationState
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetApplicationState
(
    ApplicationType Application,
    ApplicationStateRefType Value
);

/****************************************************************************************************
*   Function Name           : TerminateApplication
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) TerminateApplication
(
    ApplicationType Application,
    RestartType RestartOption
);

/****************************************************************************************************
*   Function Name           : AllowAccess
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) AllowAccess
(
    void
);

/****************************************************************************************************
*   Function Name           : CallTrustedFunction
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType .
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) CallTrustedFunction
(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
);

/****************************************************************************************************
*   Function Name           : StartScheduleTableRel
*   Service ID              : 0x07.
*   Description             : This service starts the processing of a schedule table at "Offset" relative to the "Now" value on
*                             the underlying counter.
*   Parameters in           : ScheduleTableID :Schedule table to be started
*                             Offset :Number of ticks on the counter before the the schedule table processing is started
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00347] Definition of API function StartScheduleTableRel .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) StartScheduleTableRel
(
    ScheduleTableType ScheduleTableID,
    TickType Offset
);

/****************************************************************************************************
*   Function Name           : StartScheduleTableAbs
*   Service ID              : 0x08.
*   Description             : This service starts the processing of a schedule table at an absolute value "Start" on the
*                             underlying counter.
*   Parameters in           : ScheduleTableID :Schedule table to be started
*                             Start :Absolute counter tick value at which the schedule table is started
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00358] Definition of API function StartScheduleTableAbs .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) StartScheduleTableAbs
(
    ScheduleTableType ScheduleTableID,
    TickType Start
);

/****************************************************************************************************
*   Function Name           : StopScheduleTable
*   Service ID              : 0x09.
*   Description             : This service cancels the processing of a schedule table immediately at any point while the
*                             schedule table is running.
*   Parameters in           : ScheduleTableID :Schedule table to be stopped
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00006] Definition of API function StopScheduleTable .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) StopScheduleTable
(
    ScheduleTableType ScheduleTableID
);

/****************************************************************************************************
*   Function Name           : NextScheduleTable
*   Service ID              : 0x0a.
*   Description             : This service switches the processing from one schedule table to another schedule table.
*   Parameters in           : ScheduleTableID_From :Currently processed schedule table
*                             ScheduleTableID_To :Schedule table that provides its series of expiry points
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00191] Definition of API function NextScheduleTable .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) NextScheduleTable
(
    ScheduleTableType ScheduleTableID_From,
    ScheduleTableType ScheduleTableID_To
);

/****************************************************************************************************
*   Function Name           : StartScheduleTableSynchron
*   Service ID              : 0x0b.
*   Description             : This service starts an explicitly synchronized schedule table synchronously.
*   Parameters in           : ScheduleTableID :Schedule table to be started
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00201] Definition of API function StartScheduleTableSynchron .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) StartScheduleTableSynchron
(
    ScheduleTableType ScheduleTableID
);

/****************************************************************************************************
*   Function Name           : SyncScheduleTable
*   Service ID              : 0x0c.
*   Description             : This service provides the schedule table with a synchronization count and start synchronization .
*   Parameters in           : ScheduleTableID :Schedule table to be synchronized
*                             Value :The current value of the synchronization counter
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00199] Definition of API function SyncScheduleTable .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) SyncScheduleTable
(
    ScheduleTableType ScheduleTableID,
    TickType Value
);

/****************************************************************************************************
*   Function Name           : SetScheduleTableAsync
*   Service ID              : 0x0d.
*   Description             : This service stops synchronization of a schedule table.
*   Parameters in           : ScheduleTableID :Schedule table for which status is requested
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00422] Definition of API function SetScheduleTableAsync .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) SetScheduleTableAsync
(
    ScheduleTableType ScheduleTableID
);

/****************************************************************************************************
*   Function Name           : GetScheduleTableStatus
*   Service ID              : 0x0e.
*   Description             : This service queries the state of a schedule table (also with respect to synchronization).
*   Parameters in           : ScheduleTableID :Schedule table for which status is requested
*   Parameters inout        : None.
*   Parameters out          : ScheduleStatus :Reference to ScheduleTableStatusType.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00227] Definition of API function GetScheduleTableStatus .
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetScheduleTableStatus
(
    ScheduleTableType ScheduleTableID,
    ScheduleTableStatusRefType ScheduleStatus
);

/****************************************************************************************************
*   Function Name           : IncrementCounter
*   Service ID              : None.
*   Description             : Increments a software counter
*   Parameters in           : CounterID. Counter to be incremented
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : E_OK indicates success and others indicates failure.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) IncrementCounter
(
    CounterType CounterID
);

/****************************************************************************************************
*   Function Name           : GetCounterValue
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : CounterID. Counter to be read.
*   Parameters inout        : None.
*   Parameters out          : Value: Contains the current tick value of the CounterID
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : E_OK indicates success and others indicates failure.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetCounterValue
(
    CounterType CounterID,
    TickRefType Value
);

/****************************************************************************************************
*   Function Name           : GetElapsedValue
*   Service ID              : None.
*   Description             : Get the number of tick between current tick value and previous read tick value.
*   Parameters in           : CounterID. Counter to be read.
*   Parameters inout        : Value. As an Input parameter, it contains a previously read Tick Value,
*                                    As an Output parameter, it contains the current tick value of CounterID.
*   Parameters out          : ElapsedValue. the difference between current Tick value and previously read tick.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : E_OK indicates success and others indicates failure.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetElapsedValue
(
    CounterType CounterID,
    TickRefType Value,
    TickRefType ElapsedValue
);

/****************************************************************************************************
*   Function Name           : GetResource
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetResource
(
   ResourceType ResID
);

/****************************************************************************************************
*   Function Name           : ReleaseResource
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ReleaseResource
(
    ResourceType ResID
);

/****************************************************************************************************
*   Function Name           : GetSpinlock
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : SWS_Os_00686
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) GetSpinlock
(
    SpinlockIdType SpinlockId
);

/****************************************************************************************************
*   Function Name           : TryToGetSpinlock
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : SWS_Os_00703
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) TryToGetSpinlock
(
    SpinlockIdType SpinlockId,
    P2VAR(TryToGetSpinlockType, AUTOMATIC, OS_VAR) Success
);

/****************************************************************************************************
*   Function Name           : ReleaseSpinlock
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : SWS_Os_00695
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) ReleaseSpinlock
(
    SpinlockIdType SpinlockId
);


extern FUNC(StatusType, OS_CODE) Os_InitialEnableInterruptSources(boolean ClearPending);
extern FUNC(void, OS_CODE) Os_Init(void);
extern FUNC(void, OS_CODE) Os_InitMemory(void);

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void);

#endif /* OS_H_*/

/****************************************************************************************************
**     End of File: Os.h                                                                      **
****************************************************************************************************/


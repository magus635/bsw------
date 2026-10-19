/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timer_hal.h
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
#ifndef OS_TIMER_HAL_H_
#define OS_TIMER_HAL_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Compiler.h"
#include "Os_timer_types.h"

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
/* EL1 physical timer operations.*/
/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1PhyTimerInit
*   Service ID              : None.
*   Description             : Initialize EL1 physical timer. Get EL1 physical counter value as start
*                             time at this function.
*   Parameters in           : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerInit(void);

/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1PhyTimerSetCompareRegValue
*   Service ID              : None.
*   Description             : Set compare register value of EL1 physical timer.
*   Parameters in           : Value: Value to be set to compare register.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerSetCompareRegValue(Os_TickType Value);

/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1PhyTimerGetCompareRegValue
*   Service ID              : None.
*   Description             : Get compare register value of EL1 physical timer.
*   Parameters in           : None.
*   Parameters out          : Value: Refer to store compare register value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerGetCompareRegValue(Os_TickRefType Value);

/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1PhyTimerGetCounterRegValue
*   Service ID              : None.
*   Description             : Get counter register value of EL1 physical timer.
*   Parameters in           : None.
*   Parameters out          : Value: Refer to store counter register value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerGetCounterRegValue(Os_TickRefType Value);

/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1PhyTimerAckInterrupt
*   Service ID              : None.
*   Description             : Acknowledge EL1 physical timer interrupt.
*   Parameters in           : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerAckInterrupt(void);

/* EL1 Virtual timer operations.*/
/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1VirtTimerInit
*   Service ID              : None.
*   Description             : Initialize EL1 virtual timer. Get EL1 virtual counter value as start time.
*                             at this function.
*   Parameters in           : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerInit(void);

/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1VirtTimerSetCompareRegValue
*   Service ID              : None.
*   Description             : Set compare register value of EL1 virtual timer.
*   Parameters in           : Value: Value to be set to compare register.
*   Parameters out          : None
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerSetCompareRegValue(Os_TickType Value);

/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1VirtTimerGetCompareRegValue
*   Service ID              : None.
*   Description             : Get compare register value of EL1 virtual timer.
*   Parameters in           : None.
*   Parameters out          : Value: Pointer to store compare register value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerGetCompareRegValue(Os_TickRefType Value);

/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1VirtTimerGetCounterRegValue
*   Service ID              : None.
*   Description             : Get counter register value of EL1 virtual timer.
*   Parameters in           : None.
*   Parameters out          : Value: Pointer to store counter register value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerGetCounterRegValue(Os_TickRefType Value);

/****************************************************************************************************
*   Function Name           : OsTimer_Hal_EL1VirtTimerAckInterrupt
*   Service ID              : None.
*   Description             : Acknowledge EL1 virtual timer interrupt.
*   Parameters in           : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerAckInterrupt(void);

/****************************************************************************************************
*   Function Name           : OsTimer_Hal_TriggerInterrupt
*   Service ID              : None.
*   Description             : Trigger software interrupt according to IsrID.
*   Parameters in           : IsrID: Interrupt service request number.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Hal_TriggerInterrupt(uint32 IsrID);

#endif /* OS_TIMER_HAL_H_ */

/****************************************************************************************************
**     End of File: Os_timer_hal.h                                                               **
****************************************************************************************************/


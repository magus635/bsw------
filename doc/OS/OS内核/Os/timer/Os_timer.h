/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timer.h
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
#ifndef OS_TIMER_H_
#define OS_TIMER_H_

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
/****************************************************************************************************
*   Function Name           : OsTimer_Init
*   Service ID              : None.
*   Description             : Initialize specified Timer.
*   Parameters in           : HwCfg: Pointer of Hardware Timer Configuration
*   Parameters inout        : None.
*   Parameters out          : None
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Init
(
    P2CONST(Os_CounterHwConfigType, TYPEDEF, OS_CONST) HwCfg
);

/****************************************************************************************************
*   Function Name           : OsTimer_Start
*   Service ID              : None.
*   Description             : Start Timer and Enable Timer Interrupt.
*   Parameters in           : HwCfg: Pointer of Hardware Timer Configuration
*   Parameters inout        : None.
*   Parameters out          : None
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_Start
(
    P2CONST(Os_CounterHwConfigType, TYPEDEF, OS_CONST) HwCfg
);

/****************************************************************************************************
*   Function Name           : OsTimer_FrtAckInterrupt
*   Service ID              : None.
*   Description             : Acknowledge Free Running Interrupt.
*   Parameters in           : FrtCfg: Pointer of Free Running Timer Configuration.
*   Parameters inout        : None.
*   Parameters out          : None
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_FrtAckInterrupt
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST) FrtCfg
);

/****************************************************************************************************
*   Function Name           : OsTimer_PfrtCalNextTickCompareValue
*   Service ID              : None.
*   Description             : Calculate the next tick compare value of free running timer.
*   Parameters in           : FrtCfg: Pointer of free running timer configuration.
*   Parameters inout        : CompareValue. As input parameter, it stores current compare value.
*                              As output parameter, it stores next interrupt compare value.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_PfrtCalNextTickCompareValue
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST) FrtCfg,
    Os_TickRefType CompareValue
);

/****************************************************************************************************
*   Function Name           : OsTimer_PfrtSetNextTickCompareValue
*   Service ID              : None.
*   Description             : Set next tick compare register value and do software interrupt if timeout.
*   Parameters in           : FrtCfg: Pointer of free running timer configuration.
*   Parameters in           : CompareRegValue. Value will be set to compare register of FRT.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_PfrtSetNextTickCompareValue
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST) FrtCfg,
    Os_TickType CompareRegValue
);

/****************************************************************************************************
*   Function Name           : OsTimer_PfrtGetCounterRegValue
*   Service ID              : None.
*   Description             : Get counter register value of free running timer.
*   Parameters in           : FrtCfg: Pointer of free running timer configuration.
*   Parameters out          : CompareRegValue: Pointer to save counter register value of FRT.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_PfrtGetCounterRegValue
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST) FrtCfg,
    Os_TickRefType CompareRegValue
);

/****************************************************************************************************
*   Function Name           : OsTimer_PitAckAndReloadInterrupt
*   Service ID              : None.
*   Description             : Acknowledge interrupt of period interrupt timer and reload period.
*   Parameters in           : PitCfg: Pointer of period interrupt timer configuration.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_PitAckAndReloadInterrupt
(
    P2CONST(Os_TimerPitHwConfigType, TYPEDEF, OS_CONST) PitCfg
);

/****************************************************************************************************
*   Function Name           : OsTimer_HrtAckInterrupt
*   Service ID              : None.
*   Description             : Acknowledge High resolution timer interrupt.
*   Parameters in           : HrtCfg: Pointer of high resolution timer configuration.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_HrtAckInterrupt
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)   HrtCfg
);
/****************************************************************************************************
*   Function Name           : OsTimer_HrtSetCompareRegValue
*   Service ID              : None.
*   Description             : Set high resolution timer compare register value.
*   Parameters in           : HrtCfg: Pointer of high resolution timer configuration.
*   Parameters in           : CompareRegValue. Compare register value to be set.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_HrtSetCompareRegValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickType CompareRegValue
);

/****************************************************************************************************
*   Function Name           : OsTimer_HrtGetCompareRegValue
*   Service ID              : None.
*   Description             : Get high resolution timer compare register value.
*   Parameters in           : HrtCfg: Pointer of high resolution timer configuration.
*   Parameters out          : CompareRegValue. Pointer to store compare register value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_HrtGetCompareRegValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickRefType CompareRegValue
);
/****************************************************************************************************
*   Function Name           : OsTimer_HrtGetCounterRegValue
*   Service ID              : None.
*   Description             : Get high resolution timer counter register value.
*   Parameters in           : HrtCfg: Pointer of high resolution timer configuration.
*   Parameters out          : CounterRegValue. Pointer to store counter register value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_HrtGetCounterRegValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickRefType CounterRegValue
);
/****************************************************************************************************
*   Function Name           : OsTimer_HrtGetCompareValue
*   Service ID              : None.
*   Description             : Get high resolution timer Compare value.
*   Parameters in           : HrtCfg: Pointer of high resolution timer configuration.
*   Parameters out          : CompareValue. Pointer to store compare value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_HrtGetCompareValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickRefType CompareValue
);

/****************************************************************************************************
*   Function Name           : OsTimer_HrtGetCurrentValue
*   Service ID              : None.
*   Description             : Get high resolution timer current value.
*   Parameters in           : HrtCfg: Pointer of high resolution timer configuration.
*   Parameters out          : Value. Pointer to store Hrt timer current value.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTimer_HrtGetCurrentValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickRefType Value
);

/****************************************************************************************************
*   Function Name           : OsTimer_HrtReachedLimitedTime
*   Service ID              : None.
*   Description             : Get high resolution timer current value.
*   Parameters in           : HrtCfg: Pointer of high resolution timer configuration.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : TRUE indicates reach HRT limited Time.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsTimer_HrtReachedLimitedTime
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)   HrtCfg
);
/****************************************************************************************************
*   Function Name           : OsTimer_HrtIsFutureValue
*   Service ID              : None.
*   Description             : Judget Hrt timer before/After ReferenceValue.
*   Parameters in           : HrtCfg: Pointer of high resolution timer configuration.
*   Parameters in           : Value: time value of HRT timer.
*   Parameters in           : ReferenceValue: RefereceValue of HRT timer.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : TRUE indicates Value is the future time to ReferenceValue.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsTimer_HrtIsFutureValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)   HrtCfg,
    Os_TickType   Value,
    Os_TickType   ReferenceValue
);
#endif /* OS_TIMER_H_ */

/****************************************************************************************************
**     End of File: Os_timer.h                                                                   **
****************************************************************************************************/


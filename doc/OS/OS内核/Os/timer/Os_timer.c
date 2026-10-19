/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timer.c
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
#include "Os_GeneralTypes.h"
#include "Os_timer_types.h"
#include "Os_timer_hal.h"
#include "Os_timer.h"
#include "Os_isr.h"
#include "Os_counter_Lcfg.h"
#include "Os_application.h"
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
#define OS_START_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"
/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsTimer_Internal_IsFutureValue
*   Service ID              : None.
*   Description             : Judge Value is later RefValue or not.
*   Parameters in           : MaxDifferenceValue : MaxDifferenceValue is used to process overflow case.
*   Parameters in           : Value :  Compared Value.
*   Parameters in           : ReferenceValue : Reference Value.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : TRUE indicates Value is later than RefValue
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, OS_CODE) OsTimer_Internal_IsFutureValue
(
    Os_TickType MaxDifferenceValue,
    Os_TickType Value,
    Os_TickType ReferenceValue
);

/****************************************************************************************************
*   Function Name           : OsTimer_Internal_FrtInit
*   Service ID              : None.
*   Description             : Initialize Free Running Timer.
*   Parameters in           : FrtCfg : Pointer of Free Running Timer Configuration.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTimer_Internal_FrtInit
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST) FrtCfg
);

/****************************************************************************************************
*   Function Name           : OsTimer_Internal_HrtInit
*   Service ID              : None.
*   Description             : Initialize High Resolution Timer.
*   Parameters in           : HrtCfg : Pointer of High Resolution Timer Configuration.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTimer_Internal_HrtInit
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST) HrtCfg
);

/****************************************************************************************************
*   Function Name           : OsTimer_Internal_PitInit
*   Service ID              : None.
*   Description             : Initialize Period Interrupt Timer.
*   Parameters in           : HrtCfg : Pointer of Period Interrupt Timer Configuration.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTimer_Internal_PitInit
(
    P2CONST(Os_TimerPitHwConfigType, TYPEDEF, OS_CONST)   PitCfg
);

/****************************************************************************************************
*   Function Name           : OsTimer_Internal_HrtStart
*   Service ID              : None.
*   Description             : Start HRT Timer.
*   Parameters in           : HrtCfg : Pointer of High resolution Timer Configuration.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTimer_Internal_HrtStart
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST) HrtCfg
);

static FUNC(boolean, OS_CODE) OsTimer_Internal_IsFutureValue
(
    Os_TickType MaxDifferenceValue,
    Os_TickType Value,
    Os_TickType ReferenceValue
)
{
    boolean Result;
    Os_TickType Difference;
    if (Value > ReferenceValue)
    {
        Difference = Value - ReferenceValue;
        Result = (boolean)(Difference <= MaxDifferenceValue);
    }
    else if (Value < ReferenceValue)
    {
        Difference = ReferenceValue - Value;
        Result = (boolean)(Difference > MaxDifferenceValue);
    }
    else
    {
        Result = FALSE;
    }
    return Result;
}

static FUNC(void, OS_CODE) OsTimer_Internal_FrtInit
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST) FrtCfg
)
{
}

static FUNC(void, OS_CODE) OsTimer_Internal_PitInit
(
    P2CONST(Os_TimerPitHwConfigType, TYPEDEF, OS_CONST)   PitCfg
)
{
}

static FUNC(void, OS_CODE) OsTimer_Internal_HrtInit
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST) HrtCfg
)
{
    P2VAR(Os_TimerHrtRunningDataType,TYPEDEF, OS_VAR) RunningData;
    RunningData = HrtCfg->RunningData;
    RunningData->Compare = 0ul;
    RunningData->ZeroTimeStamp = 0ul;
    RunningData->Value = 0ul;
    HrtCfg->GetCounterRegValue(&RunningData->LastCounterValue);
}

static FUNC(void, OS_CODE) OsTimer_Internal_FrtStart
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST) FrtCfg
)
{
    FrtCfg->Init();
}

static FUNC(void, OS_CODE) OsTimer_Internal_PitStart
(
    P2CONST(Os_TimerPitHwConfigType, TYPEDEF, OS_CONST) PitCfg
)
{
    PitCfg->Init(PitCfg->Period);
}

static FUNC(void, OS_CODE) OsTimer_Internal_HrtStart
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST) HrtCfg
)
{
    Os_TickType ZeroTick;
    /*initialize HrtTimer.*/
    HrtCfg->Init();
    /*Get Counter Value as timer ZeroTick. */
    HrtCfg->GetCounterRegValue(&ZeroTick);
    HrtCfg->RunningData->Value = 0;
    HrtCfg->RunningData->ZeroTimeStamp = ZeroTick;
    HrtCfg->RunningData->LastCounterValue = ZeroTick;
    if (0 != HrtCfg->RunningData->Compare)
    {
        OsTimer_HrtSetCompareRegValue(HrtCfg, HrtCfg->RunningData->Compare);
    }
}
/****************************************************************************************************
**                          End Private Function Definitions                                       **
****************************************************************************************************/
FUNC(void, OS_CODE) OsTimer_Init
(
    P2CONST(Os_CounterHwConfigType, TYPEDEF, OS_CONST)   HwCfg
)
{
    switch(HwCfg->HwTimerType)
    {
        case TIMER_DRIVER_PITTIMER:
            OsTimer_Internal_PitInit(HwCfg->TimerCfg.PitCfg);
            break;
        case TIMER_DRIVER_FRTTIMER:
            OsTimer_Internal_FrtInit(HwCfg->TimerCfg.FrtCfg);
            break;
        case TIMER_DRIVER_HRTTIMER:
            OsTimer_Internal_HrtInit(HwCfg->TimerCfg.HrtCfg);
            break;
        default:
            break;
    }
}

FUNC(void, OS_CODE) OsTimer_Start
(
    P2CONST(Os_CounterHwConfigType, TYPEDEF, OS_CONST)   HwCfg
)
{
    switch(HwCfg->HwTimerType)
    {
        case TIMER_DRIVER_PITTIMER:
            OsTimer_Internal_PitStart(HwCfg->TimerCfg.PitCfg);
            break;
        case TIMER_DRIVER_FRTTIMER:
            OsTimer_Internal_FrtStart(HwCfg->TimerCfg.FrtCfg);
            break;
        case TIMER_DRIVER_HRTTIMER:
            OsTimer_Internal_HrtStart(HwCfg->TimerCfg.HrtCfg);
            break;
        default:
            break;
    }
}

FUNC(void, OS_CODE) OsTimer_FrtAckInterrupt
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST)   FrtCfg
)
{
    FrtCfg->AckInterrupt();
}

FUNC(void, OS_CODE) OsTimer_PfrtGetCounterRegValue
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST)  PfrtCfg,
    Os_TickRefType CompareRegValue
)
{
    PfrtCfg->GetCounterRegValue(CompareRegValue);
}

FUNC(void, OS_CODE) OsTimer_PitAckAndReloadInterrupt
(
    P2CONST(Os_TimerPitHwConfigType, TYPEDEF, OS_CONST)   PitCfg
)
{
    PitCfg->PitAckAndReloadInterrupt();
}

FUNC(void, OS_CODE) OsTimer_PfrtCalNextTickCompareValue
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST)  FrtCfg,
    Os_TickRefType CompareValue
)
{
    if (FrtCfg->MaxCounterRegisterValue - *CompareValue > FrtCfg->Period)
    {
        *CompareValue = *CompareValue + FrtCfg->Period;
    }
    else
    {
        *CompareValue = *CompareValue - FrtCfg->MaxCounterRegisterValue - 1
                + FrtCfg->Period;
    }
}

FUNC(void, OS_CODE) OsTimer_PfrtSetNextTickCompareValue
(
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST)  FrtCfg,
    Os_TickType CompareRegValue
)
{
    Os_TickType CounterRegValue;

    /*Set Compare Register Value for next Tick Interrupt.*/
    FrtCfg->SetCompareRegValue(CompareRegValue);
    /*Get Current Counter Value.*/
    FrtCfg->GetCounterRegValue(&CounterRegValue);

    /*Normally CompareRegValue should larger than CounterRegValue,  otherwise,
     * it indicates time overflow and we should trigger software Interrupt. */
    if (!OsTimer_Internal_IsFutureValue(FrtCfg->MaxDifferenceValue, CompareRegValue, CounterRegValue))
    {
        OsTimer_Hal_TriggerInterrupt(FrtCfg->InterruptSourceID);
    }
}

FUNC(void, OS_CODE) OsTimer_HrtAckInterrupt
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)   HrtCfg
)
{
    HrtCfg->AckInterrupt();
}

FUNC(void, OS_CODE) OsTimer_HrtGetCounterRegValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickRefType CounterRegValue
)
{
    HrtCfg->GetCounterRegValue(CounterRegValue);
}

FUNC(void, OS_CODE) OsTimer_HrtGetCompareRegValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickRefType CompareValue
)
{
    HrtCfg->GetCompareRegValue(CompareValue);
}

FUNC(void, OS_CODE) OsTimer_HrtSetCompareRegValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickType CompareRegValue
)
{
    Os_TickType Now;
    Os_TickType CorrectExpTime;

    HrtCfg->RunningData->Compare = CompareRegValue;
    CorrectExpTime = HrtCfg->RunningData->ZeroTimeStamp + CompareRegValue;
    HrtCfg->SetCompareRegValue(CorrectExpTime);
    OsTimer_HrtGetCurrentValue(HrtCfg, &Now);
    if (!OsTimer_Internal_IsFutureValue(HrtCfg->MaxDifferenceValue, CompareRegValue, Now))
    {
        OsTimer_Hal_TriggerInterrupt(HrtCfg->InterruptSourceID);
    }
}

FUNC(void, OS_CODE) OsTimer_HrtGetCompareValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickRefType CompareValue
)
{
    *CompareValue = HrtCfg->RunningData->Compare;
}

FUNC(void, OS_CODE) OsTimer_HrtGetCurrentValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg,
    Os_TickRefType Value
)
{
    Os_TickType Now;
    Os_TickType ElapsedTime;

    /*Get current counter register value.*/
    HrtCfg->GetCounterRegValue(&Now);

    /*Process overflow cases.*/
    ElapsedTime = Now - HrtCfg->RunningData->LastCounterValue;
    HrtCfg->RunningData->LastCounterValue = Now;
    HrtCfg->RunningData->Value += ElapsedTime;
    *Value = HrtCfg->RunningData->Value;
}

FUNC(boolean, OS_CODE) OsTimer_HrtReachedLimitedTime
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)   HrtCfg
)
{
    return TRUE;
}

FUNC(boolean, OS_CODE) OsTimer_HrtIsFutureValue
(
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)   HrtCfg,
    Os_TickType   Value,
    Os_TickType   ReferenceValue
)
{
    Os_TickType MaxDifferenceValue;

    MaxDifferenceValue = HrtCfg->MaxDifferenceValue;
    return OsTimer_Internal_IsFutureValue(MaxDifferenceValue, Value, ReferenceValue);
}
#define OS_STOP_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"

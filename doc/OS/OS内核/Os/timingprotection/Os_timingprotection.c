/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timeprotection.c
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
#include "Os_timingprotection_types.h"
#include "Os_timingprotection_Lcfg.h"
#include "Os_timingprotection_Cfg.h"
#include "Os_timingprotection.h"
#include "Os_isr.h"
#include "Os_application.h"
#include "Os_hook.h"
#include "Os_counter_Cfg.h"
#include "Os_counter_types.h"
#include "Os_counter_Lcfg.h"
#include "Os_timer.h"

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
#if (0 != TOTAL_TPUSED_NUM)
/****************************************************************************************************
*   Function Name           : OsTp_Internal_GetCoreConfig
*   Service ID              : None.
*   Description             : Get current core TP configuration pointer.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Pointer of current core configuration.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Os_TpRunningDataTypeRef, OS_CODE) OsTp_Internal_GetCoreConfig
(
    void
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_GetCounterCfgInfo
*   Service ID              : None.
*   Description             : Get TP counter configuration pointer by counterID.
*   Parameters in           : CounterID. CounterID used for TP.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Pointer of counter configuration.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(P2CONST(Os_CounterConfigType, AUTOMATIC, OS_CONST), OS_CODE) OsTp_Internal_GetCounterCfgInfo
(
    uint32 CounterID
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_GetHrtTimerCfg
*   Service ID              : None.
*   Description             : Get Timer configuration pointer by counterID.
*   Parameters in           : CounterID. CounterID used for TP.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Pointer of timer configuration.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST), OS_CODE) OsTp_Internal_GetHrtTimerCfg
(
    uint32 CounterID
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_AddTick
*   Service ID              : None.
*   Description             : Do two parameter addition.
*   Parameters in           : TpConfig. Pointer of TP configuration.
*   Parameters in           : Tick. One addition parameter
*   Parameters in           : Value. Another additon paramter
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Addition result of two parameters.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Os_TickType, OS_CODE) OsTp_Internal_AddTick
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    Os_TickType Tick,
    Os_TickType Value
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_SubTick
*   Service ID              : None.
*   Description             : Do subtraction for TP.
*   Parameters in           : TpConfig. Pointer of TP configuration
*   Parameters in           : Value. minuend
*   Parameters in           : ReferenceValue. subtrahend
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Addition result of two parameters.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Os_TickType, OS_CODE) OsTp_Internal_SubTick
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    Os_TickType Value,
    Os_TickType ReferenceValue
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_GetElapsedTimeStamp
*   Service ID              : None.
*   Description             : Get Tp Elapsed Time from OsTp_Init.
*   Parameters in           : TpConfig. Pointer of TP configuration
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Elapsed time of this Task/ISR2 used.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Os_TickType, OS_CODE)OsTp_Internal_GetElapsedTimeStamp
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_ProcessTimingProtection
*   Service ID              : None.
*   Description             : Process TP conditions.
*   Parameters in           : TpConfig. Pointer of TP configuration
*   Parameters in           : CurrentObjectTpCfg. pointer of Task/ISR2 Tp configuration which trigger TP.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Elapsed time of this Task/ISR2 used.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTp_Internal_ProcessTimingProtection
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_Resume
*   Service ID              : None.
*   Description             : Resume Specified Task/ISR2 TP.
*   Parameters in           : TpConfig. Pointer of TP configuration
*   Parameters in           : Now. Current Time
*   Parameters in           : Remain. Remain Time of TP.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE)OsTp_Internal_Resume
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    Os_TickType Now,
    Os_TickType Remain
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_Suspend
*   Service ID              : None.
*   Description             : Suspend Specified Task/ISR2 TP.
*   Parameters in           : TpConfig. Pointer of TP configuration
*   Parameters in           : CurrentObjectTpCfg. Current task/ISR2 TP configuration.
*   Parameters in           : Now. Current Time
*   Parameters in           : DeadLine. End Time of TP for given task/SIR2.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE)OsTp_Internal_Suspend
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg,
    Os_TickType Now,
    Os_TickType DeadLine
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_StartBudget
*   Service ID              : None.
*   Description             : Start Specified Task/ISR2 TP.
*   Parameters in           : TpConfig. Pointer of TP configuration
*   Parameters in           : CurrentObjectTpCfg. Current task/ISR2 TP configuration.
*   Parameters in           : Budget. Pointer of budget configuration to be started.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTp_Internal_StartBudget
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg,
    P2CONST(Os_TpBudgetConfigType, AUTOMATIC, OS_CONST) Budget
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_StopBudget
*   Service ID              : None.
*   Description             : Stop Specified Task/ISR2 TP.
*   Parameters in           : TpConfig. Pointer of TP configuration
*   Parameters in           : CurrentObjectTpCfg. Current task/ISR2 TP configuration.
*   Parameters in           : Budget. Pointer of budget configuration to be stopped.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsTp_Internal_StopBudget
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg,
    P2CONST(Os_TpBudgetConfigType, AUTOMATIC, OS_CONST) Budget
);

/****************************************************************************************************
*   Function Name           : OsTp_Internal_GetResourceBudget
*   Service ID              : None.
*   Description             : Get the pointer of Resource budget by ResourceID.
*   Parameters in           : CurrentObjectTpCfg. Current task/ISR2 TP configuration.
*   Parameters in           : ResourceID. ResourceID of specified Resource.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : the pointer of Resource budget configuration
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(P2CONST(Os_TpBudgetConfigType, TYPEDEF, OS_CONST), OS_CODE) OsTp_Internal_GetResourceBudget
(
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg,
    uint32 ResourceID
);

static FUNC(Os_TpRunningDataTypeRef, OS_CODE) OsTp_Internal_GetCoreConfig
(
    void
)
{
    return OsKernel_GetCurrentCoreTpDataInfo();
}

static FUNC(P2CONST(Os_CounterConfigType, AUTOMATIC, OS_CONST), OS_CODE) OsTp_Internal_GetCounterCfgInfo
(
    uint32 CounterID
)
{
    P2CONST(Os_CounterConfigType, AUTOMATIC, OS_CONST) CounterCfg;

    if (CounterID < OS_COUNTER_TOTAL_NUM)
    {
        CounterCfg = Os_CounterConfigSet[CounterID];
    }
    else
    {
        /*panic here.*/
        CounterCfg = NULL_PTR;
        while(1);
    }

    return CounterCfg;
}

static FUNC(P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST), OS_CODE) OsTp_Internal_GetHrtTimerCfg
(
    uint32 CounterID
)
{
    P2CONST(Os_TimerHrtHwConfigType, AUTOMATIC, OS_CONST) HrtHwCfg;

    if (CounterID < OS_COUNTER_TOTAL_NUM)
    {
        HrtHwCfg = Os_CounterConfigSet[CounterID]->HwCfg->TimerCfg.HrtCfg;
    }
    else
    {
        /*panic here.*/
        HrtHwCfg = NULL_PTR;
        while(1);
    }

    return HrtHwCfg;
}

static FUNC(Os_TickType, OS_CODE) OsTp_Internal_AddTick
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    Os_TickType Tick,
    Os_TickType Value
)
{
    Os_TickType ReturnValue;
    Os_TickType MaxAllowedValue;
    P2CONST(Os_CounterConfigType, AUTOMATIC, OS_CONST) CounterCfg;

    CounterCfg = OsTp_Internal_GetCounterCfgInfo(TpConfig->CounterID);
    MaxAllowedValue = CounterCfg->HwCfg->TimerCfg.HrtCfg->MaxCounterRegisterValue;

    if (Tick > MaxAllowedValue - Value)
    {
        ReturnValue = Tick - MaxAllowedValue - 1 + Value;
    }
    else
    {
        ReturnValue = Tick + Value;
    }
    return ReturnValue;
}

static FUNC(Os_TickType, OS_CODE) OsTp_Internal_SubTick
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    Os_TickType Value,
    Os_TickType ReferenceValue
)
{
    Os_TickType ReturnValue;
    Os_TickType MaxAllowedValue;
    P2CONST(Os_CounterConfigType, AUTOMATIC, OS_CONST) CounterCfg;

    CounterCfg = OsTp_Internal_GetCounterCfgInfo(TpConfig->CounterID);
    MaxAllowedValue = CounterCfg->HwCfg->TimerCfg.HrtCfg->MaxCounterRegisterValue;

    if (Value >= ReferenceValue)
    {
        ReturnValue = Value - ReferenceValue;
    }
    else
    {
        ReturnValue = MaxAllowedValue - ReferenceValue + Value + 1;
    }
    return ReturnValue;
}

static FUNC(Os_TickType, OS_CODE)OsTp_Internal_GetElapsedTimeStamp
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig
)
{
    Os_TickType Now;
    Os_TickType ElapsedTick;
    P2VAR(Os_TpRunningDataType, TYPEDEF, OS_VAR) RunningData;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg;

    RunningData = TpConfig;
    HrtCfg = OsTp_Internal_GetHrtTimerCfg(TpConfig->CounterID);

    OsTimer_HrtGetCurrentValue(HrtCfg, &Now);
    ElapsedTick = Now - RunningData->LastCounterValue;
    RunningData->LastCounterValue = Now;
    RunningData->ElapsedTimeStamp += ElapsedTick;
    return RunningData->ElapsedTimeStamp;
}

static FUNC(void, OS_CODE) OsTp_Internal_ProcessTimingProtection
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg
)
{
    Os_TickType Now;
    Os_TickType DeadLine;
    Os_TickType CompareValue;
    Os_TickType MaxAllowedValue;
    Os_TpMonitorType Reason;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST) HrtCfg;
    P2CONST(Os_CounterConfigType, AUTOMATIC, OS_CONST) CounterCfg;

    CounterCfg = OsTp_Internal_GetCounterCfgInfo(TpConfig->CounterID);
    HrtCfg = CounterCfg->HwCfg->TimerCfg.HrtCfg;

    /*Add passed time to Elapsed TimeStamp.*/
    (void)OsTp_Internal_GetElapsedTimeStamp(TpConfig);
    /*Get DeadLine of TP.*/
    OsTimer_HrtGetCompareValue(HrtCfg, &DeadLine);
    /*Get current time.*/
    OsTimer_HrtGetCurrentValue(HrtCfg, &Now);
    /*Now is larger than DeadLine. Trigger TP.*/
    if (!OsTimer_HrtIsFutureValue(HrtCfg, DeadLine, Now))
    {
        Reason = CurrentObjectTpCfg->RunningData->BugdetList->MonitorType;
        /*Delay process for trusted function.*/
        if (CurrentObjectTpCfg->RunningData->DelayLevel > 0)
        {
            if (TP_MONITOR_NONE != CurrentObjectTpCfg->RunningData->Reason)
            {
                /*update protection error.*/
                CurrentObjectTpCfg->RunningData->Reason = Reason;
            }

            /*Set a compare value to far away current time to avoid frequently activate TP ISR.*/
            MaxAllowedValue = CounterCfg->CounterAttr.MaxAllowedCountValue;
            CurrentObjectTpCfg->RunningData->BugdetList->RunningData->RemainBudget = MaxAllowedValue;
            CompareValue = OsTp_Internal_AddTick(TpConfig, DeadLine, MaxAllowedValue);
            OsTimer_HrtSetCompareRegValue(HrtCfg, CompareValue);
        }
        else if (TP_MONITOR_EXECUTION == Reason)
        {
            /*Trigger Execution ProtectionHook.*/
            OsHook_CallProtectionHook(E_OS_PROTECTION_TIME);
        }
        else if (TP_MONITOR_LOCK == Reason)
        {
            /*Trigger Lock ProtectionHook.*/
            OsHook_CallProtectionHook(E_OS_PROTECTION_LOCKED);
        }
        else
        {
            /*Panic Here.*/
            while(1);
        }
    }
}

static FUNC(void, OS_CODE)OsTp_Internal_Resume
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    Os_TickType Now,
    Os_TickType Remain
)
{
    Os_TickType CompareRegValue;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg;
    /*Resume TP time.*/
    HrtCfg = OsTp_Internal_GetHrtTimerCfg(TpConfig->CounterID);
    CompareRegValue = OsTp_Internal_AddTick(TpConfig, Now, Remain);
    OsTimer_HrtSetCompareRegValue(HrtCfg, CompareRegValue);
}

static FUNC(void, OS_CODE)OsTp_Internal_Suspend
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg,
    Os_TickType Now,
    Os_TickType DeadLine
)
{
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg;
    /*Stop TP time. calculate remainder time of TP.*/
    HrtCfg = OsTp_Internal_GetHrtTimerCfg(TpConfig->CounterID);
    if (OsTimer_HrtIsFutureValue(HrtCfg, DeadLine, Now))
    {
        CurrentObjectTpCfg->RunningData->BugdetList->RunningData->RemainBudget =
                   OsTp_Internal_SubTick(TpConfig, DeadLine, Now);
    }
    else
    {
        CurrentObjectTpCfg->RunningData->BugdetList->RunningData->RemainBudget = 0;
    }
}

static FUNC(void, OS_CODE) OsTp_Internal_StartBudget
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg,
    P2CONST(Os_TpBudgetConfigType, AUTOMATIC, OS_CONST) Budget
)
{
    Os_TickType Now;
    Os_TickType DeadLine;
    Os_TickType Remain;
    Os_IsrLevelType Level;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg;

    OsIsr_SuspendISR(&Level);
    Now = OsTp_Internal_GetElapsedTimeStamp(TpConfig);

    /*There has started Timing Protection items.*/
    if(NULL_PTR != CurrentObjectTpCfg->RunningData->BugdetList)
    {
        HrtCfg = OsTp_Internal_GetHrtTimerCfg(TpConfig->CounterID);
        OsTimer_HrtGetCompareValue(HrtCfg, &DeadLine);
        Remain = OsTp_Internal_SubTick(TpConfig, DeadLine, Now);
        /*add CurrentObjectTpCfg TP to BugdetList if Budget is less than remain */
        if (Budget->Budget < Remain)
        {
            CurrentObjectTpCfg->RunningData->BugdetList->RunningData->RemainBudget = Remain;
            Budget->RunningData->Previous = CurrentObjectTpCfg->RunningData->BugdetList;
            CurrentObjectTpCfg->RunningData->BugdetList = Budget;
            OsTp_Internal_Resume(TpConfig, Now, Budget->Budget);
        }
    }
    else
    {
        /*There doesn't start Tp item, Add Budget to BugdetList.*/
        Budget->RunningData->Previous = NULL_PTR;
        CurrentObjectTpCfg->RunningData->BugdetList = Budget;
        OsTp_Internal_Resume(TpConfig, Now, Budget->Budget);
    }

    OsIsr_ResumeISR(Level);
}

static FUNC(void, OS_CODE) OsTp_Internal_StopBudget
(
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig,
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg,
    P2CONST(Os_TpBudgetConfigType, AUTOMATIC, OS_CONST) Budget
)
{
    Os_TickType Now;
    Os_TickType Remain;
    Os_TickType DeadLine;
    Os_TickType StartTick;
    Os_TickType ElpasedTick;
    Os_IsrLevelType Level;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg;

    OsIsr_SuspendISR(&Level);
    /*Current Task/ISR2 started TP.*/
    if (NULL_PTR != CurrentObjectTpCfg->RunningData->BugdetList)
    {
        /*change to the NextObjectTpCfg TP item.*/
        CurrentObjectTpCfg->RunningData->BugdetList =
            CurrentObjectTpCfg->RunningData->BugdetList->RunningData->Previous;
        if (NULL_PTR != CurrentObjectTpCfg->RunningData->BugdetList)
        {
            Now = OsTp_Internal_GetElapsedTimeStamp(TpConfig);
            HrtCfg = OsTp_Internal_GetHrtTimerCfg(TpConfig->CounterID);
            OsTimer_HrtGetCompareValue(HrtCfg, &DeadLine);
            /*Calculate Previous Budget Start time.*/
            StartTick = OsTp_Internal_SubTick(TpConfig, DeadLine, Budget->Budget);
            /*Get Previous Budget Running time.*/
            ElpasedTick = OsTp_Internal_SubTick(TpConfig, Now, StartTick);
            /*Calculate Next Budget Remain time.*/
            if (CurrentObjectTpCfg->RunningData->BugdetList->RunningData->RemainBudget > ElpasedTick)
            {
                Remain = CurrentObjectTpCfg->RunningData->BugdetList->RunningData->RemainBudget - ElpasedTick;
            }
            else
            {
                Remain = 0;
            }

            OsTp_Internal_Resume(TpConfig, Now, Remain);
        }
    }
    OsIsr_ResumeISR(Level);
}

static FUNC(P2CONST(Os_TpBudgetConfigType, TYPEDEF, OS_CONST), OS_CODE) OsTp_Internal_GetResourceBudget
(
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg,
    uint32 ResourceID
)
{
    uint32 Index;
    P2CONST(Os_TpBudgetConfigType, TYPEDEF, OS_CONST) ResourceBudgetCfg;
    P2CONST(Os_TpReSourceBudgetConfigType, TYPEDEF, OS_CONST) ResourceTpCfg;

    ResourceBudgetCfg = NULL_PTR;
    if (NULL_PTR != CurrentObjectTpCfg->LockResourceBudgetsCfg)
    {
        Index = 0;
        while (1)
        {
            /*Get Pointer of ResourceTpCfg*/
            ResourceTpCfg = CurrentObjectTpCfg->LockResourceBudgetsCfg[Index];
            if (NULL_PTR == ResourceTpCfg)
            {
                /*All elements has been searched. finished searching.*/
                break;
            }
            else if (ResourceID == ResourceTpCfg->ReSourceID)
            {
                /*Match the ResourceID, find related Budget Cfg Pointer.*/
                ResourceBudgetCfg = ResourceTpCfg->BugdetCfg;
                break;
            }
            else
            {
                Index++;
            }
        }
    }
    return ResourceBudgetCfg;
}
#endif /*End OS_KERNEL_SUPPORT_SC2*/
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

FUNC(void, OS_CODE) OsTp_InitMemory
(
    uint32 TpObjUsedCounterID
)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpCoreRunDataConfig;

    TpCoreRunDataConfig = OsTp_Internal_GetCoreConfig();
    /*If core doesn't support TP. this pointer should be NULL_PTR.*/
    if (NULL_PTR != TpCoreRunDataConfig)
    {
        TpCoreRunDataConfig->ElapsedTimeStamp = 0u;
        TpCoreRunDataConfig->LastCounterValue = 0u;
        TpCoreRunDataConfig->CounterID = TpObjUsedCounterID;
    }
#endif
}

FUNC(void, OS_CODE) OsTp_Init
(
    uint32 TpObjetID
)
{
#if (0 != TOTAL_TPUSED_NUM)
    /* Initilaize Spcified Task/ISR2 BudgetConfig.  */
    OsTp_InitObject(Os_TimingProection_ObjSet[TpObjetID]);
#endif
}

FUNC(void, OS_CODE) OsTp_InitObject
(
    P2CONST(Os_TpObjectConfigType, TYPEDEF, OS_VAR) TaskTpConfig
)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig;
    P2VAR(Os_TpObjectRunningDataType, TYPEDEF, OS_VAR_NOINIT) RunningData;

    TpConfig = OsTp_Internal_GetCoreConfig();
    if (NULL_PTR != TpConfig && NULL_PTR != TaskTpConfig)
    {
        RunningData = TaskTpConfig->RunningData;
        RunningData->DelayLevel = 0;
        RunningData->BugdetList = NULL_PTR;
        RunningData->Reason = TP_MONITOR_NONE;
        /*Initialize BugdetList to ExecutionBudget if Task/ISR2 configured ExecutionBudget */
        if (TP_MONITOR_EXECUTION == TaskTpConfig->ExecutionBudget.MonitorType)
        {
            TaskTpConfig->ExecutionBudget.RunningData->Previous = NULL_PTR;
            RunningData->BugdetList = &(TaskTpConfig->ExecutionBudget);
            RunningData->BugdetList->RunningData->RemainBudget =
                    RunningData->BugdetList->Budget;
        }

        if (TaskTpConfig->TimeFrame > 0)
        {
            /*Initialize TimeFrame to elapsed time.*/
            RunningData->TimeFrameLimit = OsTp_Internal_GetElapsedTimeStamp(TpConfig);
        }
    }
#endif
}

FUNC(void, OS_CODE) OsTp_Start(void)
{
}

/*Suspend Current Task/ISR2 TP time and Resume Next Task/ISR2 TP time.*/
FUNC(void, OS_CODE)OsTp_Switch
(
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) CurrentObjectTpCfgPtr,
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) NextObjectTpCfgPtr
)
{
#if (0 != TOTAL_TPUSED_NUM)
    Os_TickType Now;
    Os_TickType DeadLine;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg;
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST)  TpConfig;

    TpConfig = OsTp_Internal_GetCoreConfig();
    /*This Core Enable Timing Protection.*/
    if (NULL_PTR != TpConfig)
    {
        HrtCfg = OsTp_Internal_GetHrtTimerCfg(TpConfig->CounterID);
        OsTimer_HrtGetCurrentValue(HrtCfg, &Now);
        OsTimer_HrtGetCompareValue(HrtCfg, &DeadLine);

        /*NextObjectTpCfg Task Configured TP and Has budget in monitoring. Resume Next Task/ISR2 TP time.*/
        if ((NULL_PTR != NextObjectTpCfgPtr) && (NULL_PTR != (*NextObjectTpCfgPtr)->RunningData->BugdetList))
        {
            OsTp_Internal_Resume(TpConfig, Now,
                    (*NextObjectTpCfgPtr)->RunningData->BugdetList->RunningData->RemainBudget);
        }

        /*record TP Object.*/
        if(NULL_PTR != NextObjectTpCfgPtr)
        {
            TpConfig->MonitoredObjectCfg = *NextObjectTpCfgPtr;
        }
        else
        {
            TpConfig->MonitoredObjectCfg = NULL_PTR;
        }

        /*Record Previous TP Object.*/
        if (NULL_PTR != CurrentObjectTpCfgPtr)
        {
            TpConfig->PreviousMonitoredObjectCfg = *CurrentObjectTpCfgPtr;
        }
        else
        {
            TpConfig->PreviousMonitoredObjectCfg = NULL_PTR;
        }

        /*Current Task Configured TP. Suspend Current Task/ISR2 TP time.*/
        if (NULL_PTR != CurrentObjectTpCfgPtr && NULL_PTR != (*CurrentObjectTpCfgPtr)->RunningData->BugdetList)
        {
            OsTp_Internal_Suspend(TpConfig, *CurrentObjectTpCfgPtr, Now, DeadLine);
        }
   }
#endif
}

/*Reset Current Task/ISR2 TP time and Resume Next Task/ISR2 TP  time.*/
FUNC(void, OS_CODE)OsTp_ResetAndResume
(
    P2CONST(Os_TpObjectConfigTypeRef, AUTOMATIC, OS_CONST) CurrentObjectTpCfgPtr,
    P2CONST(Os_TpObjectConfigTypeRef, AUTOMATIC, OS_CONST) NextObjectTpCfgPtr
)
{
#if (0 != TOTAL_TPUSED_NUM)
    Os_TickType Now;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)  HrtCfg;
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST)  TpConfig;

    TpConfig = OsTp_Internal_GetCoreConfig();
    /*Current Core Enable Timing Protection.*/
    if (NULL_PTR != TpConfig)
    {
        /* CurrentObjectTpCfg Task/ISR2 started Timing Protection, Reset Value.*/
        if ((NULL_PTR != CurrentObjectTpCfgPtr)
            && (NULL_PTR != (*CurrentObjectTpCfgPtr)->RunningData->BugdetList))
        {
            (*CurrentObjectTpCfgPtr)->RunningData->BugdetList->RunningData->RemainBudget =
                (*CurrentObjectTpCfgPtr)->RunningData->BugdetList->Budget;
        }

        /*Resume NextObjectTpCfg Timing Protection.*/
        if (NULL_PTR != NextObjectTpCfgPtr
            && NULL_PTR != (*NextObjectTpCfgPtr)->RunningData->BugdetList)
        {
            HrtCfg = OsTp_Internal_GetHrtTimerCfg(TpConfig->CounterID);
            OsTimer_HrtGetCurrentValue(HrtCfg, &Now);
            OsTp_Internal_Resume(TpConfig, Now,
                (*NextObjectTpCfgPtr)->RunningData->BugdetList->RunningData->RemainBudget);
        }

        /*Record Monitored,PreviousMonitored Budget Object.*/
        if (NULL_PTR != NextObjectTpCfgPtr)
        {
            TpConfig->MonitoredObjectCfg = *NextObjectTpCfgPtr;
        }
        else
        {
            TpConfig->MonitoredObjectCfg = NULL_PTR;
        }

        if (NULL_PTR != CurrentObjectTpCfgPtr)
        {
            TpConfig->PreviousMonitoredObjectCfg = *CurrentObjectTpCfgPtr;
        }
        else
        {
            TpConfig->PreviousMonitoredObjectCfg = NULL_PTR;
        }
    }
#endif
}

/*Reset Current task TP configuration and resume TP time when Task changed from Waiting to Ready state.*/
FUNC(void, OS_CODE) OsTp_ResetAfterWait
(
    P2CONST(Os_TpObjectConfigTypeRef, AUTOMATIC, OS_CONST) CurrentObjectTpCfgPtr
)
{
#if (0 != TOTAL_TPUSED_NUM)
    Os_TickType Now;
    Os_TickType RemainBudget;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST) HrtCfg;
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST)   TpConfig;

    TpConfig = OsTp_Internal_GetCoreConfig();
    /*This Core Enable Timing Protection.*/
    if (NULL_PTR != TpConfig)
    {
        /*Current Task/ISR2 configured Tp and Started TP.*/
        if (NULL_PTR != CurrentObjectTpCfgPtr && NULL_PTR != (*CurrentObjectTpCfgPtr)->RunningData->BugdetList)
        {
            /*Current Task/ISR2 still has remain. Reset Value and resume TP.*/
            if ((*CurrentObjectTpCfgPtr)->RunningData->BugdetList->RunningData->RemainBudget > 0)
            {
                /*Reset Budget value.*/
                RemainBudget = (*CurrentObjectTpCfgPtr)->RunningData->BugdetList->Budget;
                (*CurrentObjectTpCfgPtr)->RunningData->BugdetList->RunningData->RemainBudget = RemainBudget;
                /*Resume Taks/ISR2 TP.*/
                HrtCfg = OsTp_Internal_GetHrtTimerCfg(TpConfig->CounterID);
                OsTimer_HrtGetCurrentValue(HrtCfg, &Now);
                OsTp_Internal_Resume(TpConfig, Now, RemainBudget);
            }
        }
    }
#endif
}

FUNC(boolean, OS_CODE) OsTp_PassTimeFrameCheck
(
    P2CONST(Os_TpObjectConfigTypeRef, AUTOMATIC, OS_CONST)  CurrentObjectTpCfgPtr
)
{
    boolean Passed = TRUE;
#if (0 != TOTAL_TPUSED_NUM)
    Os_TickType ElapsedTick;
    Os_IsrLevelType Level;
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST)  TpConfig;

    Passed = TRUE;
    TpConfig = OsTp_Internal_GetCoreConfig();
    /*Core configured Timing Protection.*/
    if ((NULL_PTR != TpConfig)&&(NULL_PTR != CurrentObjectTpCfgPtr))
    {
        /* Task/ISR2 configure TP TimeFrame.*/
        if ((*CurrentObjectTpCfgPtr)->TimeFrame != 0)
        {
            OsIsr_SuspendISR(&Level);
            ElapsedTick = OsTp_Internal_GetElapsedTimeStamp(TpConfig);
            /*Elapsed Time less than TimeFrameLimit, Trigger TimeFrame ProtectionHook.*/
            if ((*CurrentObjectTpCfgPtr)->RunningData->TimeFrameLimit > ElapsedTick)
            {
                /*Trigger Time Frame Error.*/
                Passed = FALSE;
                OsHook_CallProtectionHook(E_OS_PROTECTION_ARRIVAL);
            }
            else
            {
                /*calculate TimeFrame time.*/
                (*CurrentObjectTpCfgPtr)->RunningData->TimeFrameLimit =
                        ElapsedTick + (*CurrentObjectTpCfgPtr)->TimeFrame;
            }

            OsIsr_ResumeISR(Level);
        }
    }
#endif
    return Passed;
}

FUNC(void, OS_CODE) OsTp_StartLockAllInterrupt(void)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig;
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg;

    TpConfig = OsTp_Internal_GetCoreConfig();
    if (NULL_PTR != TpConfig)
    {
        /*Get Current Task/ISR2 Budget configuration.*/
        CurrentObjectTpCfg = TpConfig->MonitoredObjectCfg;
        if ((NULL_PTR != CurrentObjectTpCfg)
            && (TP_MONITOR_LOCK == CurrentObjectTpCfg->LockAllInterruptBudget.MonitorType))
        {
            /*start LockAllInterruptBudget monitor if necessary.*/
            OsTp_Internal_StartBudget(TpConfig, CurrentObjectTpCfg,
                    &(CurrentObjectTpCfg->LockAllInterruptBudget));
        }
    }
#endif
}

FUNC(void, OS_CODE)OsTp_StopLockAllInterrupt(void)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg;
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig;

    TpConfig = OsTp_Internal_GetCoreConfig();
    if (NULL_PTR != TpConfig)
    {
        /*Get Current Task/ISR2 Budget configuration.*/
        CurrentObjectTpCfg = TpConfig->MonitoredObjectCfg;
        if ((NULL_PTR != CurrentObjectTpCfg)
            && (TP_MONITOR_LOCK == CurrentObjectTpCfg->LockAllInterruptBudget.MonitorType))
        {
            /*Stop LockAllInterruptBudget monitor and pop previousMontioredBudgetCfg
             * to monitor if necessary.*/
            OsTp_Internal_StopBudget(TpConfig, CurrentObjectTpCfg,
                    &(CurrentObjectTpCfg->LockAllInterruptBudget));
        }
    }
#endif
}

FUNC(void, OS_CODE) OsTp_StartLockOsInterrupt(void)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg;
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig;

    TpConfig = OsTp_Internal_GetCoreConfig();
    if (NULL_PTR != TpConfig)
    {
        /*Get Current Task/ISR2 Budget configuration.*/
        CurrentObjectTpCfg = TpConfig->MonitoredObjectCfg;
        if (NULL_PTR != CurrentObjectTpCfg
            && (TP_MONITOR_LOCK == CurrentObjectTpCfg->LockOsInterruptBudget.MonitorType))
        {
            /*start LosOsInterruptBudget monitor if necessary.*/
            OsTp_Internal_StartBudget(TpConfig, CurrentObjectTpCfg,
                    &(CurrentObjectTpCfg->LockOsInterruptBudget));
        }
    }
#endif
}

FUNC(void, OS_CODE) OsTp_StopLockOsInterrupt(void)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg;
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig;

    TpConfig = OsTp_Internal_GetCoreConfig();
    if (NULL_PTR != TpConfig)
    {
        /*Get Current Task/ISR2 Budget configuration.*/
        CurrentObjectTpCfg = TpConfig->MonitoredObjectCfg;
        if (NULL_PTR != CurrentObjectTpCfg
            && (TP_MONITOR_LOCK == CurrentObjectTpCfg->LockOsInterruptBudget.MonitorType))
        {
            /*Stop LockOsInterruptBudget monitor and pop previousMontioredBudgetCfg
             * to monitor if necessary.*/
            OsTp_Internal_StopBudget(TpConfig, CurrentObjectTpCfg,
                    &(CurrentObjectTpCfg->LockOsInterruptBudget));
        }
    }
#endif
}

FUNC(void, OS_CODE) OsTp_StartLockResource
(
    P2CONST(Os_TpObjectConfigTypeRef, AUTOMATIC, OS_CONST) CurrentObjectTpCfgPtr,
    ResourceType ResourceID
)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig;
    P2CONST(Os_TpBudgetConfigType, TYPEDEF, OS_CONST) resourceBudget;

    TpConfig = OsTp_Internal_GetCoreConfig();
    if ((NULL_PTR != TpConfig) && (NULL_PTR != CurrentObjectTpCfgPtr))
    {
        /*Get Current Task/ISR2 Resource Budget configuration pointer by ResourceID.*/
        resourceBudget = OsTp_Internal_GetResourceBudget(*CurrentObjectTpCfgPtr, ResourceID);
        if (NULL_PTR != resourceBudget)
        {
            /*Start ResourceBudget Monitor if necessary.*/
            OsTp_Internal_StartBudget(TpConfig, *CurrentObjectTpCfgPtr, resourceBudget);
        }
    }
#endif
}

FUNC(void, OS_CODE) OsTp_StopLockResource
(
    P2CONST(Os_TpObjectConfigTypeRef, AUTOMATIC, OS_CONST) CurrentObjectTpCfgPtr,
    ResourceType ResourceID
)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig;
    P2CONST(Os_TpBudgetConfigType, TYPEDEF, OS_CONST) resourceBudget;

    TpConfig = OsTp_Internal_GetCoreConfig();
    if ((NULL_PTR != TpConfig) && (NULL_PTR != CurrentObjectTpCfgPtr))
    {
        /*Get Current Task/ISR2 Resource Budget configuration pointer by ResourceID.*/
        resourceBudget = OsTp_Internal_GetResourceBudget(*CurrentObjectTpCfgPtr, ResourceID);
        if (NULL_PTR != resourceBudget)
        {
            /*Start ResourceBudget Monitor.*/
           OsTp_Internal_StopBudget(TpConfig, *CurrentObjectTpCfgPtr, resourceBudget);
        }
    }
#endif
}

FUNC(void, OS_CODE) OsTp_StartDelay(void)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig;
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg;

    TpConfig = OsTp_Internal_GetCoreConfig();
    if (NULL_PTR != TpConfig)
    {
        CurrentObjectTpCfg = TpConfig->MonitoredObjectCfg;
        CurrentObjectTpCfg->RunningData->DelayLevel++;
    }
#endif
}

FUNC(void, OS_CODE) OsTp_StopDelay(void)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpConfig;
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) CurrentObjectTpCfg;

    TpConfig = OsTp_Internal_GetCoreConfig();
    if (NULL_PTR != TpConfig)
    {
        CurrentObjectTpCfg = TpConfig->MonitoredObjectCfg;
        CurrentObjectTpCfg->RunningData->DelayLevel--;
        if (0 == CurrentObjectTpCfg->RunningData->DelayLevel)
        {
            if (TP_MONITOR_EXECUTION == CurrentObjectTpCfg->RunningData->Reason)
            {
                OsHook_CallProtectionHook(E_OS_PROTECTION_TIME);
            }
            else if (TP_MONITOR_LOCK == CurrentObjectTpCfg->RunningData->Reason)
            {
                OsHook_CallProtectionHook(E_OS_PROTECTION_LOCKED);
            }
            else if (TP_MONITOR_NONE == CurrentObjectTpCfg->RunningData->Reason)
            {
                /* do nothing here.*/
            }
            else
            {
                /*Panic here.*/
                //Os_ErrKernelPanic(OS_STATUS_PANIC_SWITCH_CASE_DEFAULT);
            }
        }
    }
#endif
}

FUNC(void, OS_CODE)OsTp_KillObject
(
    P2CONST(Os_TpObjectConfigTypeRef, AUTOMATIC, OS_CONST) CurrentObjectTpCfgPtr
)
{
#if (0 != TOTAL_TPUSED_NUM)
    P2VAR(Os_TpObjectRunningDataType, TYPEDEF, OS_VAR_NOINIT)  RunningData;

    if (NULL_PTR != CurrentObjectTpCfgPtr)
    {
        RunningData = (*CurrentObjectTpCfgPtr)->RunningData;
        RunningData->DelayLevel = 0;
        RunningData->BugdetList = NULL_PTR;
        RunningData->Reason = TP_MONITOR_NONE;
        /*Initialize BugdetList and RemainBudget if Task/ISR2 Configured ExecutionBudget.*/
        if (TP_MONITOR_EXECUTION == (*CurrentObjectTpCfgPtr)->ExecutionBudget.MonitorType)
        {
            (*CurrentObjectTpCfgPtr)->ExecutionBudget.RunningData->Previous = NULL_PTR;
            RunningData->BugdetList = &((*CurrentObjectTpCfgPtr)->ExecutionBudget);
            RunningData->BugdetList->RunningData->RemainBudget =
                    RunningData->BugdetList->Budget;
        }
    }
#endif
}

ISR(TimingProtectionService)
{
#if (0 != TOTAL_TPUSED_NUM)
    Os_TickType CompareValue;
    boolean ReachHrtLimitedTime;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST) HrtCfg;
    P2CONST(Os_CounterConfigType, AUTOMATIC, OS_CONST) CounterCfg;
    P2VAR(Os_TpRunningDataType, AUTOMATIC, OS_CONST) TpCoreConfig;
    P2CONST(Os_TpObjectConfigType, AUTOMATIC, OS_CONST) MonitoredObjectTpCfg;

    /*Get control structure pointer*/
    TpCoreConfig = OsTp_Internal_GetCoreConfig();
    CounterCfg = OsTp_Internal_GetCounterCfgInfo(TpCoreConfig->CounterID);
    HrtCfg = CounterCfg->HwCfg->TimerCfg.HrtCfg;

    /*Acknowledge Timing Protection Interrupt.*/
    OsTimer_HrtAckInterrupt(HrtCfg);

    /*Judge HRT timer whether reached limited time.*/
    ReachHrtLimitedTime = OsTimer_HrtReachedLimitedTime(HrtCfg);
    if (ReachHrtLimitedTime)
    {
        MonitoredObjectTpCfg = TpCoreConfig->PreviousMonitoredObjectCfg;
        if ((NULL_PTR != MonitoredObjectTpCfg) && (NULL_PTR != MonitoredObjectTpCfg->RunningData->BugdetList))
        {
            /*process TP cases.*/
            OsTp_Internal_ProcessTimingProtection(TpCoreConfig, MonitoredObjectTpCfg);
        }
        else
        {
            /*Set CompareValue far away from Current time.*/
            CompareValue = OsTp_Internal_GetElapsedTimeStamp(TpCoreConfig);
            CompareValue += CounterCfg->CounterAttr.MaxAllowedCountValue;
            OsTimer_HrtSetCompareRegValue(HrtCfg, CompareValue);
        }
    }
    else
    {
        /*Update HRT Timer according to logical compare Value. */
        OsTimer_HrtGetCompareValue(HrtCfg, &CompareValue);
        OsTimer_HrtSetCompareRegValue(HrtCfg, CompareValue);
    }
#endif
}
#define OS_STOP_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"

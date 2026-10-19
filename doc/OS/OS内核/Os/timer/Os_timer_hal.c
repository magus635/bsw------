/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timer_hal.c
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
#include "Compiler.h"
#include "Os_compiler_types.h"
#include "Os_timer_hal.h"
#include "basetimer_hal.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define TIMER_INIT_VALUE     (0x7FFFFFFFul)

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
**                          Private Function Definitions                                           **
****************************************************************************************************/
#define OS_START_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/*Enable physical timer and unmask interrupt*/
#define CNTPCTL_REG_VAL                         (1u)
#define CNTVCTL_REG_VAL                         (1u)

/*Trigger Interrupt according to ISRID.*/
FUNC(void, OS_CODE) OsTimer_Hal_TriggerInterrupt(uint32 IsrID)
{
    uint32 CoreID;
    uint32 ImpCbar;
    uint32 Redistributor_IspendRegister;
    uint32 Distributor_IspendRegisterBase;

    Os_Inf_GetCP(15, 1, ImpCbar, 15, 3, 0);
    if (IsrID < 32)
    {
        CoreID = Os_Inf_CompilerGetCoreID();
        Redistributor_IspendRegister = ImpCbar + (CoreID & 0x3ul) * (0x20000ul) + 0x110200ul;
        *((uint32*)Redistributor_IspendRegister) = (1ul) << IsrID;
    }
    else
    {
        Distributor_IspendRegisterBase = ImpCbar + 0x0200ul;
        Distributor_IspendRegisterBase += (IsrID / 32) * 4;
        *((uint32*)Distributor_IspendRegisterBase) = (1ul) << (IsrID & 0x1Ful);
    }
}

/* Following 5 functions are used for El1 physical timer. */
FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerInit(void)
{
    Os_TickType Value;
    uint32   CNTPCtlReg;
    /*Set CNTP_CVAL to 0x7FFFFFFF(physical CompareValue to 0x7FFFFFFF).*/
    Os_Inf_GetCP64(15, 0, Value, 14); /*Get EL1 physical counter Register value.*/
    Value += TIMER_INIT_VALUE; /*Initial compare Register to a bigger value */
    Os_Inf_SetCP64(15, 2, Value, 14);
    /*Set CNTPCTL to 1. Enable physical timer and unmask interrupt.*/
    CNTPCtlReg = CNTPCTL_REG_VAL;
    Os_Inf_SetCP(15, 0, CNTPCtlReg, 14, 2, 1);
}

FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerSetCompareRegValue(Os_TickType Value)
{
    Os_Inf_SetCP64(15, 2, Value, 14);
}

FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerGetCompareRegValue(Os_TickRefType Value)
{
     Os_Inf_GetCP64(15, 2, *Value, 14);
}

FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerGetCounterRegValue(Os_TickRefType Value)
{
    Os_Inf_GetCP64(15, 0, *Value, 14);
}

FUNC(void, OS_CODE) OsTimer_Hal_EL1PhyTimerAckInterrupt(void)
{
}

/* Following 5 functions are used for EL1 virtual timer.*/
FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerInit(void)
{
    Os_TickType Value;
    uint32   CNTVCtlReg;
    /*Set CNTV_CVAL to 0(virtual compareValue to 0x7FFFFFFF).*/
    Os_Inf_GetCP64(15, 1, Value, 14); /*Get Virtual Counter Register Value.*/
    Value += TIMER_INIT_VALUE; /*Initial compare Register to a bigger value */
    Os_Inf_SetCP64(15, 3, Value, 14);
    /*Set CNTV_CTL to 1. enable virtual timer and unmask interrupt.*/
    CNTVCtlReg = CNTVCTL_REG_VAL;
    Os_Inf_SetCP(15, 0, CNTVCtlReg, 14, 3, 1);
}

FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerSetCompareRegValue(Os_TickType Value)
{
    Os_Inf_SetCP64(15, 3, Value, 14);
}

FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerGetCompareRegValue(Os_TickRefType Value)
{
    Os_Inf_GetCP64(15, 3, *Value, 14);
}

FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerGetCounterRegValue(Os_TickRefType Value)
{
    Os_Inf_GetCP64(15, 1, *Value, 14);
}

FUNC(void, OS_CODE) OsTimer_Hal_EL1VirtTimerAckInterrupt(void)
{
}
#define OS_STOP_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"

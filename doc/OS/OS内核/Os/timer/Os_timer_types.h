/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timer_types.h
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
#ifndef OS_TIMER_TYPES_H_
#define OS_TIMER_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_GeneralTypes.h"
#include "Compiler.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
typedef uint64          Os_TickType;
typedef Os_TickType*    Os_TickRefType;

/*This function should start timer and enable timer interrupt*/
typedef P2FUNC(void, OS_CODE, OsTimer_Hal_Init)(void);

/*This function should acknowledge interrupt timer*/
typedef P2FUNC(void, OS_CODE, OsTimer_Hal_AckInterrupt)(void);

/*This function should get counter register value of timer*/
typedef P2FUNC(void, OS_CODE, OsTimer_Hal_GetCounterRegValue)(Os_TickRefType Value);

/*This function should get compare register value of timer*/
typedef P2FUNC(void, OS_CODE, OsTimer_Hal_GetCompareRegValue)(Os_TickRefType Value);

/*This function should set compare register value of timer to specified value*/
typedef P2FUNC(void, OS_CODE, OsTimer_Hal_SetCompareRegValue)(Os_TickType Value);

/*This function should start timer. set timer period and enable timer interrupt*/
typedef P2FUNC(void, OS_CODE, OsTimer_Hal_PitInit)(uint32 BasePerTick);

/*This function should acknowledge timer interrupt and reload period*/
typedef P2FUNC(void, OS_CODE, OsTimer_Hal_PitAckAndReLoadInterrupt)(void);

typedef enum
{
    TIMER_DRIVER_PITTIMER     = 1,
    TIMER_DRIVER_FRTTIMER     = 2,
    TIMER_DRIVER_HRTTIMER     = 3,
} Os_TimerDriverType;

typedef struct
{
    Os_TickType                  Value;     /*How many tick has elpased from Start.*/
    Os_TickType                  Compare;   /*Which Tick to trigger the firstly counter callback*/
    Os_TickType                  LastCounterValue; /* record previous counter value*/
    Os_TickType                  ZeroTimeStamp; /*counter register value when OsCounter_Start is called.*/
} Os_TimerHrtRunningDataType;

typedef struct
{
    OsTimer_Hal_Init                Init;
    OsTimer_Hal_AckInterrupt        AckInterrupt;
    OsTimer_Hal_GetCounterRegValue  GetCounterRegValue;
    OsTimer_Hal_GetCompareRegValue  GetCompareRegValue;
    OsTimer_Hal_SetCompareRegValue  SetCompareRegValue;
    uint32                          InterruptSourceID;
    /*Timer Period. indicates by timer clk number.*/
    uint32                          Period;
    /*Max Counter Register Value of FRT Timer.*/
    Os_TickType                     MaxCounterRegisterValue;
    /*Max Difference value when Judge Counter Timer before/After.
     * Normally it is set to MaxCounterRegisterValue/2. */
    Os_TickType                     MaxDifferenceValue;
} Os_TimerFrtHwConfigType;

typedef struct
{
    OsTimer_Hal_PitInit                   Init;
    OsTimer_Hal_PitAckAndReLoadInterrupt  PitAckAndReloadInterrupt;
    uint32                                IsrID;
    uint32                                Period;
} Os_TimerPitHwConfigType;

typedef struct
{
    OsTimer_Hal_Init                     Init;
    OsTimer_Hal_AckInterrupt             AckInterrupt;
    OsTimer_Hal_GetCounterRegValue       GetCounterRegValue;
    OsTimer_Hal_GetCompareRegValue       GetCompareRegValue;
    OsTimer_Hal_SetCompareRegValue       SetCompareRegValue;
    uint32                               InterruptSourceID;
    /*Max Counter Register Value of HRT Timer.*/
    Os_TickType                          MaxCounterRegisterValue;
    /*Max Difference value when Judge Counter Timer before/After.
     * Normally it is set to MaxCounterRegisterValue/2. */
    Os_TickType                          MaxDifferenceValue;
    P2VAR(Os_TimerHrtRunningDataType,TYPEDEF, OS_VAR) RunningData;
} Os_TimerHrtHwConfigType;

typedef union
{
    P2CONST(Os_TimerPitHwConfigType, TYPEDEF, OS_CONST)   PitCfg;
    P2CONST(Os_TimerFrtHwConfigType, TYPEDEF, OS_CONST)   FrtCfg;
    P2CONST(Os_TimerHrtHwConfigType, TYPEDEF, OS_CONST)   HrtCfg;
} Os_TimerCfg;

typedef struct
{
    Os_TimerDriverType                                        HwTimerType;
    Os_TimerCfg                                               TimerCfg;
} Os_CounterHwConfigType;

#endif /* OS_TIMER_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_timer_types.h                                                             **
****************************************************************************************************/


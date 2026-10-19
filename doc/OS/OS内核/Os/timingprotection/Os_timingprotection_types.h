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
#ifndef OS_TIMINGPROTECTION_TYPES_H_
#define OS_TIMINGPROTECTION_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_GeneralTypes.h"
#include "Compiler.h"
#include "Os_timer_types.h"
#include "Os_timingprotection_types.h"
#include "Os_timingprotection_Cfg.h"
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
struct Os_TpBudgetRunningDataType_Tag;
typedef struct Os_TpBudgetRunningDataType_Tag    Os_TpBudgetRunningDataType;
typedef uint8                                    Os_TpDelayLevelType;

typedef enum
{
    TP_MONITOR_NONE,
    TP_MONITOR_EXECUTION,
    TP_MONITOR_LOCK,
} Os_TpMonitorType;

typedef struct
{
    Os_TpMonitorType                                           MonitorType;
    Os_TickType                                                Budget;
    P2VAR(Os_TpBudgetRunningDataType, TYPEDEF, OS_VAR_NOINIT)  RunningData;
} Os_TpBudgetConfigType;

struct Os_TpBudgetRunningDataType_Tag
{
    Os_TickType                                          RemainBudget;
    P2CONST(Os_TpBudgetConfigType, TYPEDEF, OS_CONST)    Previous;
};

typedef P2CONST(Os_TpBudgetConfigType, TYPEDEF, OS_CONST) Os_TpBudgetConfigRefType;

typedef struct
{
    Os_TickType                                        TimeFrameLimit;
    Os_TpDelayLevelType                                DelayLevel;
    P2CONST(Os_TpBudgetConfigType, TYPEDEF, OS_CONST)  BugdetList;
    Os_TpMonitorType                                   Reason;
} Os_TpObjectRunningDataType;

typedef struct
{
    uint32 ReSourceID;
    P2CONST(Os_TpBudgetConfigType, TYPEDEF, OS_CONST)  BugdetCfg;
} Os_TpReSourceBudgetConfigType;

typedef P2CONST(Os_TpReSourceBudgetConfigType, TYPEDEF, OS_CONST) Os_TpReSourceBudgetConfigRefType;

typedef struct
{
    Os_TickType                                                TimeFrame;
    Os_TpBudgetConfigType                                      ExecutionBudget;
    Os_TpBudgetConfigType                                      LockAllInterruptBudget;
    Os_TpBudgetConfigType                                      LockOsInterruptBudget;
    P2CONST(Os_TpReSourceBudgetConfigRefType, TYPEDEF, OS_CONST)  LockResourceBudgetsCfg;
    P2VAR(Os_TpObjectRunningDataType, TYPEDEF, OS_VAR)         RunningData;
} Os_TpObjectConfigType;

typedef P2CONST(Os_TpObjectConfigType, TYPEDEF, OS_CONST)  Os_TpObjectConfigTypeRef;

typedef struct
{
    /* TP Os_CounterConfigType CounterID. */
    uint32 CounterID;
    Os_TickType                                        ElapsedTimeStamp;  /*Current Object Running Time*/
    Os_TickType                                        LastCounterValue;  /*Time Stamp for Last visiting Counter.*/
    P2CONST(Os_TpObjectConfigType, TYPEDEF, OS_VAR)    PreviousMonitoredObjectCfg;
    P2CONST(Os_TpObjectConfigType, TYPEDEF, OS_VAR)    MonitoredObjectCfg; /*Current Monitored Task/ISR2 configuration.*/
} Os_TpRunningDataType;

#endif /* OS_TIMINGPROTECTION_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_timingprotection_types.h                                                             **
****************************************************************************************************/


/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_counter_types.h
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
#ifndef OS_COUNTER_TYPES_H_
#define OS_COUNTER_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_GeneralTypes.h"
#include "Os_application_types.h"
#include "Compiler.h"
#include "Os_timer_types.h"

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
struct Os_CounterNodeQueueDataType_Tag;
typedef struct Os_CounterNodeQueueDataType_Tag  Os_CounterNodeQueueDataType;

typedef enum
{
    COUNTER_DRIVER_SOFTERWARE   = 0,
    COUNTER_DRIVER_HARDWARE     = 1,
} Os_CounterDriverType;

/*This type is used for Software Timer*/
typedef struct
{
    /* add CounterValue per tick.*/
    Os_TickType  CountValue;
    /* the first Object occurs time.*/
    Os_TickType  CompareValue;
}Os_CounterRunningDataType;

typedef P2VAR(Os_CounterRunningDataType, TYPEDEF, OS_VAR) Os_CounterRunningDataRefType;

typedef struct
{
    Os_CounterRunningDataType  Base;
    /* store next Tick interrupt occurs value.*/
    Os_TickType  CompareRegValue;
} Os_CounterFrtRunningDataType;

struct Os_CounterNodeQueueDataType_Tag
{
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_VAR)            Object;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR)     Next;
};

typedef struct
{
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR)      UsedQueue;
    P2VAR(Os_CounterNodeQueueDataType, TYPEDEF, OS_VAR)      FreeQueue;
}Os_CounterNodeQueueType;

typedef struct
{
    uint32                                                    Size;
    P2CONST(Os_CounterNodeQueueDataType, TYPEDEF, OS_CONST)   FreeQueueHead;
}Os_CounterQueueMemConfigType;

typedef struct
{
    /*Maximum possible allowed value of the system counter in ticks.*/
    TickType                                                  MaxAllowedCountValue;
    /*Max difference when Judge counter Value After/Before.
     * Normally it is set to MaxAllowedCountValue/2. */
    TickType                                                  MaxDifferenceValue;
    /*specifies the minimum allowed number of counter ticks for a cyclic alarm
     * linked to the counter.*/
    TickType                                                  MinCycle;
    /*Clk Numbers Per Tick. set to 1 if it is Software Counter.*/
    uint32                                                    TicksPerBase;
}Os_CounterAttributeConfigType;

typedef struct
{
    Os_CounterAttributeConfigType                             CounterAttr;
    uint32                                                    ObjectID;
    Os_CounterDriverType                                      DriverType;
    P2VAR(Os_CounterNodeQueueType, TYPEDEF, OS_VAR)           NodeQueue;
    P2VAR(Os_CounterRunningDataType, TYPEDEF, OS_VAR)         RunningData;
    P2CONST(Os_CounterQueueMemConfigType, TYPEDEF, OS_CONST)  QueueMemCfg;
    P2CONST(Os_CounterHwConfigType, TYPEDEF, OS_CONST)        HwCfg;
}Os_CounterConfigType;

#endif /* OS_COUNTER_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_counter_types.h                                                             **
****************************************************************************************************/


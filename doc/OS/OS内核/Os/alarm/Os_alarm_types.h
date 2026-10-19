/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_alarm_types.h
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
#ifndef OS_ALARM_TYPES_H_
#define OS_ALARM_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_task_types.h"
#include "Os_event_types.h"
#include "Os_counter_types.h"
#include "Os_alarm_Cfg.h"
#include "Os_GeneralTypes.h"
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    ALARM_ENABLED,
    ALARM_DISABLED
}AlarmState;

typedef enum
{
    ALARM_ACTIVATETASK = 0,
    ALARM_SETEVENT,
    ALARM_CALLBACK,
    ALARM_INCREMENTCOUNTER
}Os_AlarmActionType;

typedef enum
{
    ALARM_REL = 0,
    ALARM_ABS
}Os_AlarmActivationType;

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef P2FUNC(void, OS_CODE, AlarmCallbackType)(void);

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
typedef struct
{
    TickType MaxAllowedValue;
    TickType TicksPerBase;
    TickType MinCycle;
}AlarmBaseType;

typedef AlarmBaseType* AlarmBaseRefType;

typedef struct
{
    TaskType TaskID;
    EventMaskType EventMask;
    CounterType CounterID;
    AlarmCallbackType AlarmCallback;
}Os_AlarmActionInfoType;

typedef struct
{
    uint32 AutoStart;
    Os_AlarmActivationType ActivationType;
    TickType Start;
    TickType Cycle;
}Os_AlarmAutoStartInfoType;

typedef struct
{
    TickType Cycle;
    AlarmState State;
}Os_AlarmDynamicType;

typedef struct
{
    uint32 ObjectID;
    Os_AlarmActionType ActionType;
    Os_AlarmActionInfoType ActionInfo;
    Os_AlarmAutoStartInfoType AutoStartInfo;
    P2VAR(Os_AlarmDynamicType, TYPEDEF, OS_VAR) Os_AlarmRunningData;
}Os_AlarmConstType;

typedef struct
{
    P2CONST(Os_AlarmConstType, TYPEDEF, OS_CONST) AlarmConfigPtr[TOTAL_ALARM_NUM + 1];
}Os_AlarmConfigType;

#endif /* OS_ALARM_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_alarm_types.h                                                               **
****************************************************************************************************/


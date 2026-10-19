/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_scheduletable_types.h
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
*  V0.1.0   1-July-2024    Pony(00412)                           Add Initial Code
****************************************************************************************************/
#ifndef OS_SCHEDULETABLE_TYPES_H_
#define OS_SCHEDULETABLE_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "datatypes.h"
#include "Compiler.h"
#include "Os_event_types.h"
#include "Os_GeneralTypes.h"
#include "Os_task_types.h"
#include "Os_scheduletable_Cfg.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/*Schedule Table ID */

typedef uint32 ScheduleTableType;

#define SHCT_ID_MASK  0xFF
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    SCHEDULETABLE_STOPPED                 = 0,
    SCHEDULETABLE_NEXT                    = 1,
    SCHEDULETABLE_WAITING                 = 2,
    SCHEDULETABLE_RUNNING                 = 3,
    SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS = 4
} ScheduleTableStatusType;

typedef ScheduleTableStatusType *ScheduleTableStatusRefType;

/*[ECUC_Os_00056] This specifies the type of the autostart for the schedule table*/
typedef enum
{
    SCHEDULTTABLE_AUTOSTART_NONE = 0, /*no autostart*/
    SCHEDULTTABLE_AUTOSTART_ABSOLUTE = 1, /*startup with the StartScheduleTableAbs() service*/
    SCHEDULTTABLE_AUTOSTART_RELATIVE  = 2,  /*startup with the StartScheduleTableRel() service*/
    SCHEDULTTABLE_AUTOSTART_SYNCHRON  = 3,  /*startup with the StartScheduleTableSynchron() service*/
}OsSchT_AutostartModeType;

typedef enum
{
    SCHEDULTTABLE_SET_ABSOLUTE = 1,
    SCHEDULTTABLE_SET_RELATIVE  = 2,

}OsSchT_SetCounterType;

typedef enum
{
    /*The schedule table is driven by an OS counter but processing needs to be synchronized with a
    different counter which is not an OS counter object*/
    SCHEDULTTABLE_SYNC_EXPLICIT = 1,

    /*The counter driving the schedule table is the counter with which synchronization  is required */
    SCHEDULTTABLE_SYNC_IMPLICIT = 2,

    /*No support for synchronization */
    SCHEDULTTABLE_SYNC_NONE   = 3,

}OsSchT_SyncType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/

typedef struct Os_SchTAutostartConfigType_Tag
{
    /*[ECUC_Os_00056] the type of the autostart for the schedule table*/
    OsSchT_AutostartModeType OsScheduleTableAutostartType;
    /*[ECUC_Os_00057] autostart tick value when the schedule table starts*/
    TickType OsScheduleTableStartValue;
    /*[ECUC_Os_00058]  which application modes the schedule table should be started during startup */
    AppModeType OsScheduleTableAppModeRef;
}OsSchT_AutostartConfigType;

typedef struct 
{
    /*[ECUC_Os_00069] The maximum positive adjustment that can be made to the expiry point offset (in ticks) */
    TickType  OsScheduleTableMaxLengthen;

    /*[ECUC_Os_00070] The maximum negative adjustment that can be made to the expiry point offset (in ticks)   */
    TickType OsScheduleTableMaxShorten;

}OsSchT_AdjustableExpPoint;

typedef struct
{
    /*[ECUC_Os_00060]  */
    EventMaskType OsSchTEventMask;

    /*[ECUC_Os_00061] */
    TaskType OsSchTTask;

}OsSchT_EPActionEventType;

typedef struct 
{
    /*[ECUC_Os_00062] The offset from zero (in ticks) at which the expiry point is to be processed */
    TickType  OsScheduleTblExpPointOffset;

    /* The number of tasks: Tasks[TaskCount] */
    uint32 TaskCount;
    /*Reference to task that will be activated by action */
    P2CONST(TaskType, AUTOMATIC, OS_CONST) OsScheduleTableActivateTaskRef;

    /* The number of events */
    uint32 EventCount;

    /* [ECUC_Os_00060] Reference to event that will be set by action */
    P2CONST(OsSchT_EPActionEventType, AUTOMATIC, OS_CONST) OsScheduleTableSetEventRef;

    /*[ECUC_Os_00068] Adjustable expiry point*/
    OsSchT_AdjustableExpPoint OsScheduleTblAdjustableExpPoint;
}OsSchT_ExPoConfigType;

typedef struct 
{
    /*[[ECUC_Os_00064] This configuration is only valid if the explicit synchronization is used */
    TickType  OsScheduleTblExplicitPrecision;

    /*[ECUC_Os_00065] AUTOSAR OS provides support for synchronization in two ways: explicit and implicit  */
    OsSchT_SyncType OsScheduleTblSyncStrategy;

}OsSchT_SyncConfigType;

typedef struct
{
    uint32 CurrentEP;     /*Current EP position ,start from 0*/
    Os_TickDiffType Deviation; /*The deviation between the actual position and sync position */
    TickType NextSysPointPos;    /*The position of next sync point */
    ScheduleTableStatusType State;
    uint8 NextSchTID;          /* Next schedule table ID*/
    uint8 PreSchTID;          /*Previous schedule table ID*/
    uint8 NeedSync;           /* sync complete or continue to sync*/
    uint8 NeedStop;        /* To indicate the schedule table need to stop*/
}OsSchT_Type;

typedef P2CONST(OsSchT_ExPoConfigType, TYPEDEF, OS_CONST) OsSchT_ExPoConfigRefType;

typedef struct 
{
    /*The RunningData data*/
    P2VAR(OsSchT_Type, TYPEDEF, OS_VAR) RunningData;

    /*[ECUC_Os_00053] the modulus of the schedule table (in ticks)*/
    TickType OsScheduleTableDuration ;

    /*[ECUC_Os_00144] Schedule table is single-shot or repeating*/
    boolean OsScheduleTableRepeating;

    /*The Object ID for this Schedule Table */
    uint32 ObjectID;

    /*The Counter ID for this Schedule Table */
    CounterType CounterID;

    /*The  ID for this Schedule Table */
    uint32 SchTID;

    /*[ECUC_Os_00145] contains a reference to the counter which drives the schedule table*/
    //OsScheduleTableCounterRef;

    /*[ECUC_Os_00054] Reference to applications which have an access to this object*/
    //uint32 OsSchTblAccessingApplication;

    /*[ECUC_Os_00335] specifies if and how the schedule table is started on startup of the Operating System*/
    OsSchT_AutostartConfigType OsScheduleTableAutostart;

    /*The EP count */
    uint32 EPCount;

    /*[ECUC_Os_00143] The point on a Schedule Table at which the OS activates tasks and/or sets events */
    P2CONST(OsSchT_ExPoConfigRefType, AUTOMATIC, OS_CONST) OsScheduleTableExpiryPoint;
    /*[ECUC_Os_00063]  specifies the synchronization parameters of the schedule table*/
    OsSchT_SyncConfigType OsScheduleTableSync;

}OsSchT_ConfigType;

#endif /* OS_SCHEDULETABLE_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_scheduletable_types.h                                                        **
****************************************************************************************************/


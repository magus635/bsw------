/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_scheduletable_Lcfg.c
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
*   Genaration Time       : 2026-03-01 08:11:34
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
#include "Compiler.h"
#include "Os_scheduletable_types.h"
#include "Os_scheduletable_Lcfg.h"
#include "Os_scheduletable_Cfg.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Type Definitions                                                **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Structure Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static OsSchT_Type Os_OsScheduleTable_0_RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static OsSchT_Type Os_OsScheduleTable_1_RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static const TaskType Os_OsScheduleTable_0_OsScheduleTableExpiryPoint_0_Tasks[OS_OSSCHEDULETABLE_0_OSSCHEDULETABLEEXPIRYPOINT_0_TASKS] =
{
    0UL,     /* Task */
};

static const OsSchT_EPActionEventType Os_OsScheduleTable_0_OsScheduleTableExpiryPoint_0_Events[OS_OSSCHEDULETABLE_0_OSSCHEDULETABLEEXPIRYPOINT_0_EVENTS] =
{
    {
        1UL,        /* OsScheduleTableSetEventRef */
        0UL        /* OsScheduleTableSetEventTaskRef */
    },
};

static const OsSchT_ExPoConfigType Os_OsScheduleTable_0_OsScheduleTableExpiryPoint_0 =
{
    20UL,       /* OsScheduleTableExpPointOffset */
    OS_OSSCHEDULETABLE_0_OSSCHEDULETABLEEXPIRYPOINT_0_TASKS,        /* TaskCount */
    &Os_OsScheduleTable_0_OsScheduleTableExpiryPoint_0_Tasks[0],        /* OsScheduleTableActivateTaskRef */
    OS_OSSCHEDULETABLE_0_OSSCHEDULETABLEEXPIRYPOINT_0_EVENTS,        /* EventCount */
    &Os_OsScheduleTable_0_OsScheduleTableExpiryPoint_0_Events[0],        /* OsScheduleTableSetEventRef */
    {
        ((TickType)0UL),        /* OsScheduleTableMaxLengthen */
        ((TickType)0UL)        /* OsScheduleTableMaxShorten */
    }
};

static const OsSchT_ExPoConfigRefType Os_OsScheduleTable_0_EPRefs[OS_OSSCHEDULETABLE_0_EP_COUNT] =
{
    (OsSchT_ExPoConfigRefType)&Os_OsScheduleTable_0_OsScheduleTableExpiryPoint_0,
};

static const OsSchT_ConfigType Os_SchT_OsScheduleTable_0_Config =
{
    &Os_OsScheduleTable_0_RunningData,     /* Dyn */
    ((uint64)100),        /* OsScheduleTableDuration */
    1,       /* OsScheduleTableRepeating */
    25UL,      /* ObjectID */
    0UL,       /* CounterID */
    0UL,     /* SchTID */
    /* OsScheduleTableAutostart */
    {
        SCHEDULTTABLE_AUTOSTART_RELATIVE,       /* OsScheduleTableAutostartType */
        1ULL,       /* OsScheduleTableStartValue */
        OSDEFAULTAPPMODE | 
    },
    OS_OSSCHEDULETABLE_0_EP_COUNT,       /* EPCount */
    Os_OsScheduleTable_0_EPRefs,       /* OsSchT_ExPoConfigRefType */
    /* OsScheduleTableSync */
    {
        0,        /* OsScheduleTblExplicitPrecision */
        SCHEDULTTABLE_SYNC_NONE      /* OsScheduleTblSyncStrategy */
    }
};

static const TaskType Os_OsScheduleTable_1_OsScheduleTableExpiryPoint_0_Tasks[OS_OSSCHEDULETABLE_1_OSSCHEDULETABLEEXPIRYPOINT_0_TASKS] =
{
    0UL,     /* Task */
};

static const OsSchT_ExPoConfigType Os_OsScheduleTable_1_OsScheduleTableExpiryPoint_0 =
{
    35UL,       /* OsScheduleTableExpPointOffset */
    OS_OSSCHEDULETABLE_1_OSSCHEDULETABLEEXPIRYPOINT_0_TASKS,        /* TaskCount */
    &Os_OsScheduleTable_1_OsScheduleTableExpiryPoint_0_Tasks[0],        /* OsScheduleTableActivateTaskRef */
    OS_OSSCHEDULETABLE_1_OSSCHEDULETABLEEXPIRYPOINT_0_EVENTS,        /* EventCount */
    NULL_PTR,       /* OsScheduleTableSetEventRef */
    {
        ((TickType)0UL),        /* OsScheduleTableMaxLengthen */
        ((TickType)0UL)        /* OsScheduleTableMaxShorten */
    }
};

static const OsSchT_EPActionEventType Os_OsScheduleTable_1_OsScheduleTableExpiryPoint_1_Events[OS_OSSCHEDULETABLE_1_OSSCHEDULETABLEEXPIRYPOINT_1_EVENTS] =
{
    {
        4UL,        /* OsScheduleTableSetEventRef */
        0UL        /* OsScheduleTableSetEventTaskRef */
    },
};

static const OsSchT_ExPoConfigType Os_OsScheduleTable_1_OsScheduleTableExpiryPoint_1 =
{
    60UL,       /* OsScheduleTableExpPointOffset */
    OS_OSSCHEDULETABLE_1_OSSCHEDULETABLEEXPIRYPOINT_1_TASKS,        /* TaskCount */
    NULL_PTR,       /* OsScheduleTableActivateTaskRef */
    OS_OSSCHEDULETABLE_1_OSSCHEDULETABLEEXPIRYPOINT_1_EVENTS,        /* EventCount */
    &Os_OsScheduleTable_1_OsScheduleTableExpiryPoint_1_Events[0],        /* OsScheduleTableSetEventRef */
    {
        ((TickType)0UL),        /* OsScheduleTableMaxLengthen */
        ((TickType)0UL)        /* OsScheduleTableMaxShorten */
    }
};

static const OsSchT_ExPoConfigRefType Os_OsScheduleTable_1_EPRefs[OS_OSSCHEDULETABLE_1_EP_COUNT] =
{
    (OsSchT_ExPoConfigRefType)&Os_OsScheduleTable_1_OsScheduleTableExpiryPoint_0,
    (OsSchT_ExPoConfigRefType)&Os_OsScheduleTable_1_OsScheduleTableExpiryPoint_1,
};

static const OsSchT_ConfigType Os_SchT_OsScheduleTable_1_Config =
{
    &Os_OsScheduleTable_1_RunningData,     /* Dyn */
    ((uint64)100),        /* OsScheduleTableDuration */
    1,       /* OsScheduleTableRepeating */
    56UL,      /* ObjectID */
    0UL,       /* CounterID */
    0UL,     /* SchTID */
    /* OsScheduleTableAutostart */
    {
        SCHEDULTTABLE_AUTOSTART_RELATIVE,       /* OsScheduleTableAutostartType */
        10ULL,       /* OsScheduleTableStartValue */
        OSALLRUNNINGMODE | 
    },
    OS_OSSCHEDULETABLE_1_EP_COUNT,       /* EPCount */
    Os_OsScheduleTable_1_EPRefs,       /* OsSchT_ExPoConfigRefType */
    /* OsScheduleTableSync */
    {
        0,        /* OsScheduleTblExplicitPrecision */
        SCHEDULTTABLE_SYNC_NONE      /* OsScheduleTblSyncStrategy */
    }
};

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
CONSTP2CONST(OsSchT_ConfigType, AUTOMATIC, OS_CONST) Os_SchTConfigSet[OS_SCHT_TOTAL_NUM] =
{
    &Os_SchT_OsScheduleTable_0_Config,
    &Os_SchT_OsScheduleTable_1_Config,
};
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

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/






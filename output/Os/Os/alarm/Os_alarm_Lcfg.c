/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_alarm_Lcfg.c
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
*   Genaration Time       : 2026-03-05 20:04:58
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
#include "Os_alarm_Lcfg.h"
#include "Os_alarm.h"
#include "Os_counter_Cfg.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Type Definitions                                                **
****************************************************************************************************/
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_AlarmDynamicType OsAlarm_0_RunningData;
static Os_AlarmDynamicType OsAlarm_1_RunningData;
static Os_AlarmDynamicType OsAlarm_2_RunningData;
static Os_AlarmDynamicType OsAlarm_6_RunningData;
static Os_AlarmDynamicType OsAlarm_7_RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h" 
static Os_AlarmDynamicType OsAlarm_3_RunningData;
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_AlarmDynamicType OsAlarm_4_RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static Os_AlarmDynamicType OsAlarm_5_RunningData;
static Os_AlarmDynamicType OsAlarm_8_RunningData;
static Os_AlarmDynamicType OsAlarm_9_RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"

/****************************************************************************************************
**                          Private Structure Definitions                                           **
****************************************************************************************************/
const Os_AlarmConstType Alarm_OsAlarm_0_ConfigRef =
{
    20UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_REL,           /* ActivationType */
        10UL,                     /* Start */
        100UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_0_RunningData
}; 
const Os_AlarmConstType Alarm_OsAlarm_1_ConfigRef =
{
    21UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_REL,           /* ActivationType */
        20UL,                     /* Start */
        80UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_1_RunningData
}; 
const Os_AlarmConstType Alarm_OsAlarm_2_ConfigRef =
{
    22UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_REL,           /* ActivationType */
        22UL,                     /* Start */
        80UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_2_RunningData
}; 
const Os_AlarmConstType Alarm_OsAlarm_6_ConfigRef =
{
    23UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_REL,           /* ActivationType */
        10UL,                     /* Start */
        50UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_6_RunningData
}; 
const Os_AlarmConstType Alarm_OsAlarm_7_ConfigRef =
{
    24UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_REL,           /* ActivationType */
        20UL,                     /* Start */
        50UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_7_RunningData
}; 
const Os_AlarmConstType Alarm_OsAlarm_3_ConfigRef =
{
    32UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_REL,           /* ActivationType */
        5UL,                     /* Start */
        10UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_3_RunningData
}; 
const Os_AlarmConstType Alarm_OsAlarm_4_ConfigRef =
{
    36UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_ABS,           /* ActivationType */
        60UL,                     /* Start */
        0UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_4_RunningData
}; 
const Os_AlarmConstType Alarm_OsAlarm_5_ConfigRef =
{
    53UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_REL,           /* ActivationType */
        20UL,                     /* Start */
        80UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_5_RunningData
}; 
const Os_AlarmConstType Alarm_OsAlarm_8_ConfigRef =
{
    54UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_REL,           /* ActivationType */
        10UL,                     /* Start */
        100UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_8_RunningData
}; 
const Os_AlarmConstType Alarm_OsAlarm_9_ConfigRef =
{
    55UL,                                   /* ObjectID */
    },                       /* AlarmActionInfo */
    {
        OSALLRUNNINGMODE,              /* AutoStart */
        ALARM_REL,           /* ActivationType */
        30UL,                     /* Start */
        200UL                      /* Cycle*/
    },                        /* AutoStartInfo */
    &OsAlarm_9_RunningData
}; 

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
const Os_AlarmConfigType Os_AlarmConfigSet =
{
    {
                &Alarm_OsAlarm_0_ConfigRef,
        &Alarm_OsAlarm_1_ConfigRef,
        &Alarm_OsAlarm_2_ConfigRef,
        &Alarm_OsAlarm_3_ConfigRef,
        &Alarm_OsAlarm_4_ConfigRef,
        &Alarm_OsAlarm_5_ConfigRef,
        &Alarm_OsAlarm_6_ConfigRef,
        &Alarm_OsAlarm_7_ConfigRef,
        &Alarm_OsAlarm_8_ConfigRef,
        &Alarm_OsAlarm_9_ConfigRef,
        NULL_PTR
}
};
/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/






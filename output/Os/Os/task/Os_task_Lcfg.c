/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_task_Lcfg.c
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
*   Genaration Time       : 2026-03-05 20:16:18
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
#include "Os_task_types.h"
#include "Os_task_Lcfg.h"
#include "Os_task.h"
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
static Os_TaskDynamicType Idle_Task_Core0_RunningData;
static Os_TaskDynamicType Task1_RunningData;
static Os_TaskDynamicType Task5_RunningData;
static Os_TaskDynamicType Task6_RunningData;
static Os_TaskDynamicType Default_Init_Task_RunningData;
static Os_TaskDynamicType Task2_RunningData;
static Os_TaskDynamicType Task3_RunningData;
static Os_TaskDynamicType Task8_RunningData;
static Os_TaskDynamicType Task16_RunningData;
static Os_TaskDynamicType Task17_RunningData;
static Os_TaskDynamicType Task18_RunningData;
static Os_TaskDynamicType Task19_RunningData;
static Os_TaskDynamicType Task20_RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h" 
static Os_TaskDynamicType Task4_RunningData;
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"        

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h" 
static Os_TaskDynamicType Task7_RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h" 
static Os_TaskDynamicType Default_Init_Task_Core1_RunningData;
static Os_TaskDynamicType Idle_Task_Core1_RunningData;
static Os_TaskDynamicType Task0_Core1_RunningData;
static Os_TaskDynamicType Task9_Core1_RunningData;
static Os_TaskDynamicType Task10_Core1_RunningData;
static Os_TaskDynamicType Task12_Core1_RunningData;
static Os_TaskDynamicType Task11_Core1_RunningData;
static Os_TaskDynamicType Task13_Core1_RunningData;
static Os_TaskDynamicType Task14_Core1_RunningData;
static Os_TaskDynamicType Task15_Core1_RunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
static const Os_TaskConstType Task_Idle_Task_Core0_ConfigRef =
{
    0UL,        /* ObjectID */
    0UL,        /* HomePriority */
    0UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Idle_Task_Core0_RunningData
};

static const Os_TaskConstType Task_Task1_ConfigRef =
{
    1UL,        /* ObjectID */
    1UL,        /* HomePriority */
    1UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task1_RunningData
};

static const Os_TaskConstType Task_Task5_ConfigRef =
{
    2UL,        /* ObjectID */
    4UL,        /* HomePriority */
    4UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task5_RunningData
};

static const Os_TaskConstType Task_Task6_ConfigRef =
{
    3UL,        /* ObjectID */
    3UL,        /* HomePriority */
    3UL,        /* RunningPriority */
    0UL,       /* AutoStart */
    100,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task6_RunningData
};

static const Os_TaskConstType Task_Default_Init_Task_ConfigRef =
{
    4UL,        /* ObjectID */
    8UL,        /* HomePriority */
    0xFFFFFFFFUL,   /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Default_Init_Task_RunningData
};

static const Os_TaskConstType Task_Task2_ConfigRef =
{
    5UL,        /* ObjectID */
    6UL,        /* HomePriority */
    6UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task2_RunningData
};

static const Os_TaskConstType Task_Task3_ConfigRef =
{
    6UL,        /* ObjectID */
    1UL,        /* HomePriority */
    1UL,        /* RunningPriority */
    OSTRUSTAPP01MODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    TRUE,        /* IsExtended */
    &Task3_RunningData
};

static const Os_TaskConstType Task_Task8_ConfigRef =
{
    7UL,        /* ObjectID */
    5UL,        /* HomePriority */
    5UL,        /* RunningPriority */
    0UL,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task8_RunningData
};

static const Os_TaskConstType Task_Task16_ConfigRef =
{
    8UL,        /* ObjectID */
    4UL,        /* HomePriority */
    4UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    TRUE,        /* IsExtended */
    &Task16_RunningData
};

static const Os_TaskConstType Task_Task17_ConfigRef =
{
    9UL,        /* ObjectID */
    3UL,        /* HomePriority */
    3UL,        /* RunningPriority */
    0UL,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task17_RunningData
};

static const Os_TaskConstType Task_Task18_ConfigRef =
{
    10UL,        /* ObjectID */
    1UL,        /* HomePriority */
    1UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task18_RunningData
};

static const Os_TaskConstType Task_Task19_ConfigRef =
{
    11UL,        /* ObjectID */
    1UL,        /* HomePriority */
    1UL,        /* RunningPriority */
    0UL,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task19_RunningData
};

static const Os_TaskConstType Task_Task20_ConfigRef =
{
    12UL,        /* ObjectID */
    1UL,        /* HomePriority */
    1UL,        /* RunningPriority */
    0UL,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task20_RunningData
};

static const Os_TaskConstType Task_Task4_ConfigRef =
{
    30UL,        /* ObjectID */
    2UL,        /* HomePriority */
    2UL,        /* RunningPriority */
    OSDEFAULTAPPMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task4_RunningData
};

static const Os_TaskConstType Task_Task7_ConfigRef =
{
    33UL,        /* ObjectID */
    7UL,        /* HomePriority */
    7UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    TRUE,        /* IsExtended */
    &Task7_RunningData
};

static const Os_TaskConstType Task_Default_Init_Task_Core1_ConfigRef =
{
    37UL,        /* ObjectID */
    6UL,        /* HomePriority */
    0xFFFFFFFFUL,   /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Default_Init_Task_Core1_RunningData
};

static const Os_TaskConstType Task_Idle_Task_Core1_ConfigRef =
{
    38UL,        /* ObjectID */
    0UL,        /* HomePriority */
    0UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Idle_Task_Core1_RunningData
};

static const Os_TaskConstType Task_Task0_Core1_ConfigRef =
{
    39UL,        /* ObjectID */
    1UL,        /* HomePriority */
    1UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task0_Core1_RunningData
};

static const Os_TaskConstType Task_Task9_Core1_ConfigRef =
{
    40UL,        /* ObjectID */
    3UL,        /* HomePriority */
    3UL,        /* RunningPriority */
    OSDEFAULTAPPMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    TRUE,        /* IsExtended */
    &Task9_Core1_RunningData
};

static const Os_TaskConstType Task_Task10_Core1_ConfigRef =
{
    41UL,        /* ObjectID */
    2UL,        /* HomePriority */
    2UL,        /* RunningPriority */
    0UL,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task10_Core1_RunningData
};

static const Os_TaskConstType Task_Task12_Core1_ConfigRef =
{
    42UL,        /* ObjectID */
    5UL,        /* HomePriority */
    5UL,        /* RunningPriority */
    OSDEFAULTAPPMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    TRUE,        /* IsExtended */
    &Task12_Core1_RunningData
};

static const Os_TaskConstType Task_Task11_Core1_ConfigRef =
{
    43UL,        /* ObjectID */
    4UL,        /* HomePriority */
    4UL,        /* RunningPriority */
    OSDEFAULTAPPMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task11_Core1_RunningData
};

static const Os_TaskConstType Task_Task13_Core1_ConfigRef =
{
    44UL,        /* ObjectID */
    3UL,        /* HomePriority */
    3UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    TRUE,        /* IsExtended */
    &Task13_Core1_RunningData
};

static const Os_TaskConstType Task_Task14_Core1_ConfigRef =
{
    45UL,        /* ObjectID */
    2UL,        /* HomePriority */
    2UL,        /* RunningPriority */
    0UL,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task14_Core1_RunningData
};

static const Os_TaskConstType Task_Task15_Core1_ConfigRef =
{
    46UL,        /* ObjectID */
    1UL,        /* HomePriority */
    1UL,        /* RunningPriority */
    OSALLRUNNINGMODE,       /* AutoStart */
    1,        /* MaxActivationCount */
    FALSE,        /* IsExtended */
    &Task15_Core1_RunningData
};


/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

const Os_TaskConfigType Os_TaskConfigSet =
{
    {
        &Task_Idle_Task_Core0_ConfigRef,
        &Task_Idle_Task_Core1_ConfigRef,
        &Task_Task1_ConfigRef,
        &Task_Task2_ConfigRef,
        &Task_Task3_ConfigRef,
        &Task_Task4_ConfigRef,
        &Task_Task5_ConfigRef,
        &Task_Task6_ConfigRef,
        &Task_Task7_ConfigRef,
        &Task_Default_Init_Task_ConfigRef,
        &Task_Default_Init_Task_Core1_ConfigRef,
        &Task_Task0_Core1_ConfigRef,
        &Task_Task8_ConfigRef,
        &Task_Task9_Core1_ConfigRef,
        &Task_Task10_Core1_ConfigRef,
        &Task_Task11_Core1_ConfigRef,
        &Task_Task12_Core1_ConfigRef,
        &Task_Task13_Core1_ConfigRef,
        &Task_Task14_Core1_ConfigRef,
        &Task_Task15_Core1_ConfigRef,
        &Task_Task16_ConfigRef,
        &Task_Task17_ConfigRef,
        &Task_Task18_ConfigRef,
        &Task_Task19_ConfigRef,
        &Task_Task20_ConfigRef,
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

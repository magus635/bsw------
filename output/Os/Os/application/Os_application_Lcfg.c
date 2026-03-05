/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_application_Lcfg.c
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
#include "Os_application_Cfg.h"
#include "Os_application_Lcfg.h"
#include "Os_context_Lcfg.h"
#include "Os_hook_types.h"
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
static ApplicationStateType OsApplication_0_StatusCfg;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h" 
static ApplicationStateType OsApplication_1_StatusCfg;
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static ApplicationStateType OsApplication_2_StatusCfg;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static TickType Application0_NodeRunningData[APPLICATION0_ALARM_SCHEDULETABLE_NUMBER];
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static TickType Application1_NodeRunningData[APPLICATION1_ALARM_SCHEDULETABLE_NUMBER];
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static TickType Application2_NodeRunningData[APPLICATION2_ALARM_SCHEDULETABLE_NUMBER];
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_AppObjectRefType Core0_PreviousObjectInfoPtr0;
static Os_AppObjectRefType Core0_PreviousObjectInfoPtr1;
static Os_AppObjectRefType Core0_PreviousObjectInfoPtr2;
static Os_AppObjectRefType Core0_PreviousObjectInfoPtr3;
static Os_AppObjectRefType Core0_PreviousObjectInfoPtr4;
static Os_AppObjectRefType Core0_PreviousObjectInfoPtr5;
static Os_AppObjectRefType Core0_PreviousObjectInfoPtr6;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_AppObjectRefType Core0_PreviousObjectInfoPtr7;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_AppObjectRefType Core0_PreviousObjectInfoPtr8;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static ApplicationStateType OsApplication_3_StatusCfg;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static TickType Application3_NodeRunningData[APPLICATION3_ALARM_SCHEDULETABLE_NUMBER];
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static Os_AppObjectRefType Core1_PreviousObjectInfoPtr9;
static Os_AppObjectRefType Core1_PreviousObjectInfoPtr10;
static Os_AppObjectRefType Core1_PreviousObjectInfoPtr11;
static Os_AppObjectRefType Core1_PreviousObjectInfoPtr12;
static Os_AppObjectRefType Core1_PreviousObjectInfoPtr13;
static Os_AppObjectRefType Core1_PreviousObjectInfoPtr14;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static Os_AppObjectRefType Core1_PreviousObjectInfoPtr15;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
static const Os_NodeConfigType Application0_NodeConfig[APPLICATION0_ALARM_SCHEDULETABLE_NUMBER] =
{
    {
        0UL,               /* CounterID */
        &Application0_NodeRunningData[0]        /* &NodeInfo */
    },
    {
        1UL,               /* CounterID */
        &Application0_NodeRunningData[1]        /* &NodeInfo */
    },
    {
        1UL,               /* CounterID */
        &Application0_NodeRunningData[2]        /* &NodeInfo */
    },
    {
        4UL,               /* CounterID */
        &Application0_NodeRunningData[3]        /* &NodeInfo */
    },
    {
        4UL,               /* CounterID */
        &Application0_NodeRunningData[4]        /* &NodeInfo */
    },
    {
        1UL,               /* CounterID */
        &Application0_NodeRunningData[5]        /* &NodeInfo */
    },
};
static const Os_NodeConfigType Application1_NodeConfig[APPLICATION1_ALARM_SCHEDULETABLE_NUMBER] =
{
    {
        4UL,               /* CounterID */
        &Application1_NodeRunningData[0]        /* &NodeInfo */
    },
};
static const Os_NodeConfigType Application2_NodeConfig[APPLICATION2_ALARM_SCHEDULETABLE_NUMBER] =
{
    {
        3UL,               /* CounterID */
        &Application2_NodeRunningData[0]        /* &NodeInfo */
    },
};
static const Os_NodeConfigType Application3_NodeConfig[APPLICATION3_ALARM_SCHEDULETABLE_NUMBER] =
{
    {
        5UL,               /* CounterID */
        &Application3_NodeRunningData[0]        /* &NodeInfo */
    },
    {
        7UL,               /* CounterID */
        &Application3_NodeRunningData[1]        /* &NodeInfo */
    },
    {
        7UL,               /* CounterID */
        &Application3_NodeRunningData[2]        /* &NodeInfo */
    },
    {
        5UL,               /* CounterID */
        &Application3_NodeRunningData[3]        /* &NodeInfo */
    },
};
static const Os_AppObjectType Application_ObjectConfiglist[TOTALNUM_OF_OBJECT] = 
{
    /* Current Application is App0  */
    {
        (uint32)0,                 /* ObjectIDIndex */
        0UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_0: AppObjIDInfo0 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[0]    /* &Idle_Task_Core0_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Idle_Task_Core0 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)1,                 /* ObjectIDIndex */
        2UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_2: AppObjIDInfo1 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[1]    /* &Task1_Context_Config */
        },
        (uint32)0x00000009UL,                        /* Task1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)2,                 /* ObjectIDIndex */
        6UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_6: AppObjIDInfo2 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[2]    /* &Task5_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Task5 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)3,                 /* ObjectIDIndex */
        7UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_7: AppObjIDInfo3 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[3]    /* &Task6_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Task6 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)4,                 /* ObjectIDIndex */
        9UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_9: AppObjIDInfo4 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[4]    /* &Default_Init_Task_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Default_Init_Task access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)5,                 /* ObjectIDIndex */
        3UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_3: AppObjIDInfo5 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[5]    /* &Task2_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Task2 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)6,                 /* ObjectIDIndex */
        4UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_4: AppObjIDInfo6 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[6]    /* &Task3_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Task3 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)7,                 /* ObjectIDIndex */
        12UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_12: AppObjIDInfo7 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[7]    /* &Task8_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Task8 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)8,                 /* ObjectIDIndex */
        20UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_20: AppObjIDInfo8 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[8]    /* &Task16_Context_Config */
        },
        (uint32)0x00000009UL,                        /* Task16 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)9,                 /* ObjectIDIndex */
        21UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_21: AppObjIDInfo9 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[9]    /* &Task17_Context_Config */
        },
        (uint32)0x00000009UL,                        /* Task17 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)10,                 /* ObjectIDIndex */
        22UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_22: AppObjIDInfo10 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[10]    /* &Task18_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Task18 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)11,                 /* ObjectIDIndex */
        23UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_23: AppObjIDInfo11 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[11]    /* &Task19_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Task19 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)12,                 /* ObjectIDIndex */
        24UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* TaskID_24: AppObjIDInfo12 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[12]    /* &Task20_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Task20 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)13,                 /* ObjectIDIndex */
        1UL|APPLICATION0_ID_MASK|APPLICATION_COUNTER1_ID_MASK,   /* ISRID_1: AppObjIDInfo13 */
        OBJECT_ISR,                                 /* ObjectType: ISR */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[13]    /* &Os_IsrCfg_SystemTimer_Context_Config */
        },
        (uint32)0x00000000UL,                        /* Os_IsrCfg_SystemTimer access application bit mask. */
        &Core0_PreviousObjectInfoPtr0       /* Os_AppObjectRefType* */
    },
    {
        (uint32)14,                 /* ObjectIDIndex */
        0UL|APPLICATION0_ID_MASK|APPLICATION_COUNTER2_ID_MASK,   /* ISRID_2: AppObjIDInfo14 */
        OBJECT_ISR,                                 /* ObjectType: ISR */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[14]    /* &Os_IsrCfg_VirtualTimer_Context_Config */
        },
        (uint32)0x00000000UL,                        /* Os_IsrCfg_VirtualTimer access application bit mask. */
        &Core0_PreviousObjectInfoPtr1       /* Os_AppObjectRefType* */
    },
    {
        (uint32)15,                 /* ObjectIDIndex */
        4UL|APPLICATION0_ID_MASK|APPLICATION_COUNTER_INVALID_ID_MASK,    /* ISRID_4: AppObjIDInfo15 */
        OBJECT_ISR,                                 /* ObjectType: ISR */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[15]    /* &OsIsr_BaseTimer1_Context_Config */
        },
        (uint32)0x00000001UL,                        /* OsIsr_BaseTimer1 access application bit mask. */
        &Core0_PreviousObjectInfoPtr2       /* Os_AppObjectRefType* */
    },
    {
        (uint32)16,                 /* ObjectIDIndex */
        6UL|APPLICATION0_ID_MASK|APPLICATION_COUNTER_INVALID_ID_MASK,    /* ISRID_6: AppObjIDInfo16 */
        OBJECT_ISR,                                 /* ObjectType: ISR */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[16]    /* &OsIsr_0_Context_Config */
        },
        (uint32)0x00000000UL,                        /* OsIsr_0 access application bit mask. */
        &Core0_PreviousObjectInfoPtr3       /* Os_AppObjectRefType* */
    },
    {
        (uint32)17,                 /* ObjectIDIndex */
        0UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Counter_0: AppObjIDInfo17 */
        OBJECT_COUNTER,                             /* ObjectType: Counter */
        {
            NULL_PTR                                    /* &NULL_PTR */
        },
        (uint32)0x00000001UL,                        /* OsCounter_Software access application bit mask. */                
        NULL_PTR
    },
    {
        (uint32)18,                 /* ObjectIDIndex */
        1UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Counter_1: AppObjIDInfo18 */
        OBJECT_COUNTER,                             /* ObjectType: Counter */
        {
            NULL_PTR                                    /* &NULL_PTR */
        },
        (uint32)0x00000003UL,                        /* OsCounter_SystemTick access application bit mask. */                
        NULL_PTR
    },
    {
        (uint32)19,                 /* ObjectIDIndex */
        2UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Counter_2: AppObjIDInfo19 */
        OBJECT_COUNTER,                             /* ObjectType: Counter */
        {
            NULL_PTR                                    /* &NULL_PTR */
        },
        (uint32)0x00000001UL,                        /* OsCounter_Hrt access application bit mask. */                
        NULL_PTR
    },
    {
        (uint32)20,                 /* ObjectIDIndex */
        0UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Alarm_0: AppObjIDInfo20 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application0_NodeConfig[0]                 /* &NodeInfo */ 
        },
        (uint32)0x00000001UL,                        /* OsAlarm_0 access application bit mask. */                  
        NULL_PTR
    },
    {
        (uint32)21,                 /* ObjectIDIndex */
        1UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Alarm_1: AppObjIDInfo21 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application0_NodeConfig[1]                 /* &NodeInfo */ 
        },
        (uint32)0x00000009UL,                        /* OsAlarm_1 access application bit mask. */                  
        NULL_PTR
    },
    {
        (uint32)22,                 /* ObjectIDIndex */
        2UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Alarm_2: AppObjIDInfo22 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application0_NodeConfig[2]                 /* &NodeInfo */ 
        },
        (uint32)0x00000001UL,                        /* OsAlarm_2 access application bit mask. */                  
        NULL_PTR
    },
    {
        (uint32)23,                 /* ObjectIDIndex */
        6UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Alarm_6: AppObjIDInfo23 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application0_NodeConfig[3]                 /* &NodeInfo */ 
        },
        (uint32)0x00000001UL,                        /* OsAlarm_6 access application bit mask. */                  
        NULL_PTR
    },
    {
        (uint32)24,                 /* ObjectIDIndex */
        7UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Alarm_7: AppObjIDInfo24 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application0_NodeConfig[4]                 /* &NodeInfo */ 
        },
        (uint32)0x00000001UL,                        /* OsAlarm_7 access application bit mask. */                  
        NULL_PTR
    },
    {
        (uint32)25,                 /* ObjectIDIndex */
        0UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* ScheduleTable_0: AppObjIDInfo25 */
        OBJECT_SCHEDULETABLE,                       /* ObjectType: ScheduleTable */
        {
            .NodeInfo = &Application0_NodeConfig[5]                 /* &NodeInfo */
        },
        (uint32)0x00000009UL,                        /* OsScheduleTable_0 access application bit mask. */                 
        NULL_PTR
    },
    {
        (uint32)26,                 /* ObjectIDIndex */
        (uint32)ERRORHOOK|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Core0KernelApp0ErrorHook: AppObjIDInfo26 */
        OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[17]    /* &Core0KernelApp0_ErrorHook_Context_Config */
        },
        (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
        &Core0_PreviousObjectInfoPtr4       /* Os_AppObjectRefType* */
    },
    {
        (uint32)27,                 /* ObjectIDIndex */
        (uint32)STARTUPHOOK|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Core0KernelApp0StartupHook: AppObjIDInfo27 */
        OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[18]    /* &Core0KernelApp0_StartupHook_Context_Config */
        },
        (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
        &Core0_PreviousObjectInfoPtr5      /* Os_AppObjectRefType* */
    },
    {
        (uint32)28,                 /* ObjectIDIndex */
        (uint32)PROTECTIONHOOK|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Core0KernelApp0ProtectionHook: AppObjIDInfo28 */
        OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[19]   /* &Core0KernelApp0_ProtectionHook_Context_Config */
        },
        (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
        &Core0_PreviousObjectInfoPtr6       /* Os_AppObjectRefType* */
    },
    {
        (uint32)29,                 /* ObjectIDIndex */
        0UL|APPLICATION0_ID_MASK|CORE0_ID_MASK,                   /* Core0_StartOsInitFunction_Context_Config: AppObjIDInfo29 */
        OBJECT_STARTOSINITFUNCTION,                          /* ObjectType: OBJECT_STARTOSINITFUNCTION */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[20]   /* &Core0_StartOsInitFunction_Context_Config */
        },
        (uint32)0x00000000UL,                        /* StartOS Init function don't care the accessing app mask */
        &Core0_PreviousObjectInfoPtr7       /* Os_AppObjectRefType* */
    },                
    /* Current Application is App1  */
    {
        (uint32)30,                 /* ObjectIDIndex */
        5UL|APPLICATION1_ID_MASK|CORE0_ID_MASK,                   /* TaskID_5: AppObjIDInfo30 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[21]    /* &Task4_Context_Config */
        },
        (uint32)0x00000003UL,                        /* Task4 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)31,                 /* ObjectIDIndex */
        4UL|APPLICATION1_ID_MASK|CORE0_ID_MASK,                   /* Counter_4: AppObjIDInfo31 */
        OBJECT_COUNTER,                             /* ObjectType: Counter */
        {
            NULL_PTR                                    /* &NULL_PTR */
        },
        (uint32)0x00000001UL,                        /* OsCounter_Software2 access application bit mask. */                
        NULL_PTR
    },
    {
        (uint32)32,                 /* ObjectIDIndex */
        3UL|APPLICATION1_ID_MASK|CORE0_ID_MASK,                   /* Alarm_3: AppObjIDInfo32 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application1_NodeConfig[0]                 /* &NodeInfo */ 
        },
        (uint32)0x00000001UL,                        /* OsAlarm_3 access application bit mask. */                  
        NULL_PTR
    },
    /* Current Application is App2  */
    {
        (uint32)33,                 /* ObjectIDIndex */
        8UL|APPLICATION2_ID_MASK|CORE0_ID_MASK,                   /* TaskID_8: AppObjIDInfo33 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[22]    /* &Task7_Context_Config */
        },
        (uint32)0x00000005UL,                        /* Task7 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)34,                 /* ObjectIDIndex */
        2UL|APPLICATION2_ID_MASK|APPLICATION_COUNTER3_ID_MASK,   /* ISRID_3: AppObjIDInfo34 */
        OBJECT_ISR,                                 /* ObjectType: ISR */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[23]    /* &Os_IsrCfg_BaseTimer0_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Os_IsrCfg_BaseTimer0 access application bit mask. */
        &Core0_PreviousObjectInfoPtr8       /* Os_AppObjectRefType* */
    },
    {
        (uint32)35,                 /* ObjectIDIndex */
        3UL|APPLICATION2_ID_MASK|CORE0_ID_MASK,                   /* Counter_3: AppObjIDInfo35 */
        OBJECT_COUNTER,                             /* ObjectType: Counter */
        {
            NULL_PTR                                    /* &NULL_PTR */
        },
        (uint32)0x00000004UL,                        /* OsCounter_Pit access application bit mask. */                
        NULL_PTR
    },
    {
        (uint32)36,                 /* ObjectIDIndex */
        4UL|APPLICATION2_ID_MASK|CORE0_ID_MASK,                   /* Alarm_4: AppObjIDInfo36 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application2_NodeConfig[0]                 /* &NodeInfo */ 
        },
        (uint32)0x00000005UL,                        /* OsAlarm_4 access application bit mask. */                  
        NULL_PTR
    },
    /* Current Application is App3  */
    {
        (uint32)37,                 /* ObjectIDIndex */
        10UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_10: AppObjIDInfo37 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[24]    /* &Default_Init_Task_Core1_Context_Config */
        },
        (uint32)0x00000008UL,                        /* Default_Init_Task_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)38,                 /* ObjectIDIndex */
        1UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_1: AppObjIDInfo38 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[25]    /* &Idle_Task_Core1_Context_Config */
        },
        (uint32)0x00000001UL,                        /* Idle_Task_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)39,                 /* ObjectIDIndex */
        11UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_11: AppObjIDInfo39 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[26]    /* &Task0_Core1_Context_Config */
        },
        (uint32)0x00000008UL,                        /* Task0_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)40,                 /* ObjectIDIndex */
        13UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_13: AppObjIDInfo40 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[27]    /* &Task9_Core1_Context_Config */
        },
        (uint32)0x00000008UL,                        /* Task9_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)41,                 /* ObjectIDIndex */
        14UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_14: AppObjIDInfo41 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[28]    /* &Task10_Core1_Context_Config */
        },
        (uint32)0x00000008UL,                        /* Task10_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)42,                 /* ObjectIDIndex */
        16UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_16: AppObjIDInfo42 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[29]    /* &Task12_Core1_Context_Config */
        },
        (uint32)0x00000008UL,                        /* Task12_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)43,                 /* ObjectIDIndex */
        15UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_15: AppObjIDInfo43 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[30]    /* &Task11_Core1_Context_Config */
        },
        (uint32)0x00000008UL,                        /* Task11_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)44,                 /* ObjectIDIndex */
        17UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_17: AppObjIDInfo44 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[31]    /* &Task13_Core1_Context_Config */
        },
        (uint32)0x00000009UL,                        /* Task13_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)45,                 /* ObjectIDIndex */
        18UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_18: AppObjIDInfo45 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[32]    /* &Task14_Core1_Context_Config */
        },
        (uint32)0x00000009UL,                        /* Task14_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)46,                 /* ObjectIDIndex */
        19UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* TaskID_19: AppObjIDInfo46 */
        OBJECT_TASK,                                /* ObjectType: Task */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[33]    /* &Task15_Core1_Context_Config */
        },
        (uint32)0x00000009UL,                        /* Task15_Core1 access application bit mask. */
        NULL_PTR
    },
    {
        (uint32)47,                 /* ObjectIDIndex */
        3UL|APPLICATION3_ID_MASK|APPLICATION_COUNTER5_ID_MASK,   /* ISRID_5: AppObjIDInfo47 */
        OBJECT_ISR,                                 /* ObjectType: ISR */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[34]    /* &Os_IsrCfg_SystemTimer_Core1_Context_Config */
        },
        (uint32)0x00000000UL,                        /* Os_IsrCfg_SystemTimer_Core1 access application bit mask. */
        &Core1_PreviousObjectInfoPtr9       /* Os_AppObjectRefType* */
    },
    {
        (uint32)48,                 /* ObjectIDIndex */
        5UL|APPLICATION3_ID_MASK|APPLICATION_COUNTER6_ID_MASK,   /* ISRID_6: AppObjIDInfo48 */
        OBJECT_ISR,                                 /* ObjectType: ISR */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[35]    /* &OsIsr_IsrCfg_VirtualTimer_Core1_Context_Config */
        },
        (uint32)0x00000008UL,                        /* OsIsr_IsrCfg_VirtualTimer_Core1 access application bit mask. */
        &Core1_PreviousObjectInfoPtr10       /* Os_AppObjectRefType* */
    },
    {
        (uint32)49,                 /* ObjectIDIndex */
        7UL|APPLICATION3_ID_MASK|APPLICATION_COUNTER_INVALID_ID_MASK,    /* ISRID_7: AppObjIDInfo49 */
        OBJECT_ISR,                                 /* ObjectType: ISR */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[36]    /* &OsIsr_1_Context_Config */
        },
        (uint32)0x00000000UL,                        /* OsIsr_1 access application bit mask. */
        &Core1_PreviousObjectInfoPtr11       /* Os_AppObjectRefType* */
    },
    {
        (uint32)50,                 /* ObjectIDIndex */
        5UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Counter_5: AppObjIDInfo50 */
        OBJECT_COUNTER,                             /* ObjectType: Counter */
        {
            NULL_PTR                                    /* &NULL_PTR */
        },
        (uint32)0x00000008UL,                        /* OsCounter_SystemTick_Core1 access application bit mask. */                
        NULL_PTR
    },
    {
        (uint32)51,                 /* ObjectIDIndex */
        6UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Counter_6: AppObjIDInfo51 */
        OBJECT_COUNTER,                             /* ObjectType: Counter */
        {
            NULL_PTR                                    /* &NULL_PTR */
        },
        (uint32)0x00000008UL,                        /* OsCounter_Hrt_Core1 access application bit mask. */                
        NULL_PTR
    },
    {
        (uint32)52,                 /* ObjectIDIndex */
        7UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Counter_7: AppObjIDInfo52 */
        OBJECT_COUNTER,                             /* ObjectType: Counter */
        {
            NULL_PTR                                    /* &NULL_PTR */
        },
        (uint32)0x00000008UL,                        /* OsCounter_Software_Core1 access application bit mask. */                
        NULL_PTR
    },
    {
        (uint32)53,                 /* ObjectIDIndex */
        5UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Alarm_5: AppObjIDInfo53 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application3_NodeConfig[0]                 /* &NodeInfo */ 
        },
        (uint32)0x00000008UL,                        /* OsAlarm_5 access application bit mask. */                  
        NULL_PTR
    },
    {
        (uint32)54,                 /* ObjectIDIndex */
        8UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Alarm_8: AppObjIDInfo54 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application3_NodeConfig[1]                 /* &NodeInfo */ 
        },
        (uint32)0x00000008UL,                        /* OsAlarm_8 access application bit mask. */                  
        NULL_PTR
    },
    {
        (uint32)55,                 /* ObjectIDIndex */
        9UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Alarm_9: AppObjIDInfo55 */
        OBJECT_ALARM,                               /* ObjectType: Alarm */
        {
            .NodeInfo = &Application3_NodeConfig[2]                 /* &NodeInfo */ 
        },
        (uint32)0x00000008UL,                        /* OsAlarm_9 access application bit mask. */                  
        NULL_PTR
    },
    {
        (uint32)56,                 /* ObjectIDIndex */
        1UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* ScheduleTable_1: AppObjIDInfo56 */
        OBJECT_SCHEDULETABLE,                       /* ObjectType: ScheduleTable */
        {
            .NodeInfo = &Application3_NodeConfig[3]                 /* &NodeInfo */
        },
        (uint32)0x00000008UL,                        /* OsScheduleTable_1 access application bit mask. */                 
        NULL_PTR
    },
    {
        (uint32)57,                 /* ObjectIDIndex */
        (uint32)ERRORHOOK|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Core1KernelApp3ErrorHook: AppObjIDInfo57 */
        OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[37]    /* &Core1KernelApp3_ErrorHook_Context_Config */
        },
        (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
        &Core1_PreviousObjectInfoPtr12       /* Os_AppObjectRefType* */
    },
    {
        (uint32)58,                 /* ObjectIDIndex */
        (uint32)STARTUPHOOK|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Core1KernelApp3StartupHook: AppObjIDInfo58 */
        OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[38]    /* &Core1KernelApp3_StartupHook_Context_Config */
        },
        (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
        &Core1_PreviousObjectInfoPtr13      /* Os_AppObjectRefType* */
    },
    {
        (uint32)59,                 /* ObjectIDIndex */
        (uint32)PROTECTIONHOOK|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Core1KernelApp3ProtectionHook: AppObjIDInfo59 */
        OBJECT_KERNELHOOK,                          /* ObjectType: OBJECT_KERNELHOOK */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[39]   /* &Core1KernelApp3_ProtectionHook_Context_Config */
        },
        (uint32)0x00000000UL,                        /* Hooks don't care the accessing app mask */
        &Core1_PreviousObjectInfoPtr14       /* Os_AppObjectRefType* */
    },
    {
        (uint32)60,                 /* ObjectIDIndex */
        0UL|APPLICATION3_ID_MASK|CORE1_ID_MASK,                   /* Core1_StartOsInitFunction_Context_Config: AppObjIDInfo60 */
        OBJECT_STARTOSINITFUNCTION,                          /* ObjectType: OBJECT_STARTOSINITFUNCTION */
        {
            .ObjectContextInfoPtr = &Os_ContextConfigSet.ContextConfigPtr[40]   /* &Core1_StartOsInitFunction_Context_Config */
        },
        (uint32)0x00000000UL,                        /* StartOS Init function don't care the accessing app mask */
        &Core1_PreviousObjectInfoPtr15       /* Os_AppObjectRefType* */
    },                
};
static const Os_ApplicationConfigType OsApplication_0_ConfigRef = 
{
    (uint32)0UL,                                   /* ApplicationID */
    (uint32)0UL,                                   /* Logical Core ID */
    (uint32)0UL,                                   /* Physical Core ID */    
    (uint32)APPLICATION0_OBJECT_START_NUMBER,      /* application0 ObjectID start number of ObjectID_StartNum */    
    (uint32)APPLICATION0_OBJECTCOUNT_NUMBER,       /* ObjectCount */
    INVALID_TASK,                                                    /* RestartTask */
    TRUE,                                   /* AppIsTrusted */
    TRUE,                 /* OsTrustedApplicationDelayTimingViolationCall */
    &OsApplication_0_StatusCfg
};
static const Os_ApplicationConfigType OsApplication_1_ConfigRef = 
{
    (uint32)1UL,                                   /* ApplicationID */
    (uint32)0UL,                                   /* Logical Core ID */
    (uint32)0UL,                                   /* Physical Core ID */    
    (uint32)APPLICATION1_OBJECT_START_NUMBER,      /* application0 ObjectID start number of ObjectID_StartNum */    
    (uint32)APPLICATION1_OBJECTCOUNT_NUMBER,       /* ObjectCount */
    INVALID_TASK,                                                    /* RestartTask */
    FALSE,                                   /* AppIsTrusted */
    TRUE,                 /* OsTrustedApplicationDelayTimingViolationCall */
    &OsApplication_1_StatusCfg
};
static const Os_ApplicationConfigType OsApplication_2_ConfigRef = 
{
    (uint32)2UL,                                   /* ApplicationID */
    (uint32)0UL,                                   /* Logical Core ID */
    (uint32)0UL,                                   /* Physical Core ID */    
    (uint32)APPLICATION2_OBJECT_START_NUMBER,      /* application0 ObjectID start number of ObjectID_StartNum */    
    (uint32)APPLICATION2_OBJECTCOUNT_NUMBER,       /* ObjectCount */
    INVALID_TASK,                                                    /* RestartTask */
    TRUE,                                   /* AppIsTrusted */
    FALSE,                 /* OsTrustedApplicationDelayTimingViolationCall */
    &OsApplication_2_StatusCfg
};
static const Os_ApplicationConfigType OsApplication_3_ConfigRef = 
{
    (uint32)3UL,                                   /* ApplicationID */
    (uint32)1UL,                                   /* Logical Core ID */
    (uint32)1UL,                                   /* Physical Core ID */    
    (uint32)APPLICATION3_OBJECT_START_NUMBER,      /* application0 ObjectID start number of ObjectID_StartNum */    
    (uint32)APPLICATION3_OBJECTCOUNT_NUMBER,       /* ObjectCount */
    INVALID_TASK,                                                    /* RestartTask */
    TRUE,                                   /* AppIsTrusted */
    TRUE,                 /* OsTrustedApplicationDelayTimingViolationCall */
    &OsApplication_3_StatusCfg
};
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
const Os_AppConfigType Os_AppConfigSet = 
{
    {
        &OsApplication_0_ConfigRef,
        &OsApplication_1_ConfigRef,
        &OsApplication_2_ConfigRef,
        &OsApplication_3_ConfigRef,
    },
    &Application_ObjectConfiglist[0]        /* ObjectRef */
};
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/



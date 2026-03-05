/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timingprotection_Lcfg.c
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
*   Genaration Time       : 2026-03-05 20:05:10
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
#include "Os_timingprotection_types.h"
#include "Os_timingprotection_Cfg.h"
#include "Os_timingprotection_Lcfg.h"
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
static Os_TpBudgetRunningDataType   Os_Task1ExecutionBudgetData;
static Os_TpBudgetRunningDataType   Os_Task1LockAllInterruptBudgetData;
static Os_TpBudgetRunningDataType   Os_OsLockOsResource_0BudgetData;
static Os_TpBudgetRunningDataType   Os_Task1LockOsInterruptBudgetData;
static Os_TpObjectRunningDataType   Os_Task1TimingProtectionRunningData;
static Os_TpBudgetRunningDataType   Os_Task5ExecutionBudgetData;
static Os_TpBudgetRunningDataType   Os_Task5LockAllInterruptBudgetData;
static Os_TpBudgetRunningDataType   Os_OsLockOsResource_1BudgetData;
static Os_TpBudgetRunningDataType   Os_Task5LockOsInterruptBudgetData;
static Os_TpObjectRunningDataType   Os_Task5TimingProtectionRunningData;
static Os_TpBudgetRunningDataType   Os_Task2ExecutionBudgetData;
static Os_TpBudgetRunningDataType   Os_Task2LockAllInterruptBudgetData;
static Os_TpBudgetRunningDataType   Os_Task2LockOsInterruptBudgetData;
static Os_TpObjectRunningDataType   Os_Task2TimingProtectionRunningData;
static Os_TpBudgetRunningDataType   Os_Task3ExecutionBudgetData;
static Os_TpBudgetRunningDataType   Os_Task3LockAllInterruptBudgetData;
static Os_TpBudgetRunningDataType   Os_Task3LockOsInterruptBudgetData;
static Os_TpObjectRunningDataType   Os_Task3TimingProtectionRunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h" 
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h" 
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h" 
static Os_TpBudgetRunningDataType   Os_Task12_Core1ExecutionBudgetData;
static Os_TpBudgetRunningDataType   Os_Task12_Core1LockAllInterruptBudgetData;
static Os_TpBudgetRunningDataType   Os_OsLockOsResource_2BudgetData;
static Os_TpBudgetRunningDataType   Os_Task12_Core1LockOsInterruptBudgetData;
static Os_TpObjectRunningDataType   Os_Task12_Core1TimingProtectionRunningData;
static Os_TpBudgetRunningDataType   Os_Task11_Core1ExecutionBudgetData;
static Os_TpBudgetRunningDataType   Os_Task11_Core1LockAllInterruptBudgetData;
static Os_TpBudgetRunningDataType   Os_Task11_Core1LockOsInterruptBudgetData;
static Os_TpObjectRunningDataType   Os_Task11_Core1TimingProtectionRunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_TpBudgetRunningDataType   Os_OsIsr_BaseTimer1ExecutionBudgetData;
static Os_TpBudgetRunningDataType   Os_OsIsr_BaseTimer1LockAllInterruptBudgetData;
static Os_TpBudgetRunningDataType   Os_OsIsr_BaseTimer1LockOsInterruptBudgetData;
static Os_TpObjectRunningDataType   Os_OsIsr_BaseTimer1TimingProtectionRunningData;
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
static const Os_TpBudgetConfigType Os_OsOsResource_0BudgetConfig =
{
    TP_MONITOR_LOCK, /* Type */
    75000,          /* Budget */
    &Os_OsLockOsResource_0BudgetData
};

static const Os_TpReSourceBudgetConfigType Os_OsOsResource_0TpConfig =
{
    0,  /* ResourceID */
    &Os_OsOsResource_0BudgetConfig
};

static const Os_TpReSourceBudgetConfigRefType Os_Task1ResourceTpConfig[2] =
{
    &Os_OsOsResource_0TpConfig,
    NULL_PTR,
};

static const Os_TpObjectConfigType Os_Task1TpConfig =
{
    52499U,                                 
    {
        TP_MONITOR_EXECUTION,
        200000U,
        &Os_Task1ExecutionBudgetData
    },
    {
        TP_MONITOR_LOCK,
        150000U,
        &Os_Task1LockAllInterruptBudgetData
    },
    {
        TP_MONITOR_LOCK,
        100000U,
        &Os_Task1LockOsInterruptBudgetData
    },
    &Os_Task1ResourceTpConfig[0],
    &Os_Task1TimingProtectionRunningData
};

static const Os_TpBudgetConfigType Os_OsOsResource_1BudgetConfig =
{
    TP_MONITOR_LOCK, /* Type */
    77500,          /* Budget */
    &Os_OsLockOsResource_1BudgetData
};

static const Os_TpReSourceBudgetConfigType Os_OsOsResource_1TpConfig =
{
    1,  /* ResourceID */
    &Os_OsOsResource_1BudgetConfig
};

static const Os_TpReSourceBudgetConfigRefType Os_Task5ResourceTpConfig[2] =
{
    &Os_OsOsResource_1TpConfig,
    NULL_PTR,
};

static const Os_TpObjectConfigType Os_Task5TpConfig =
{
    62500U,                                 
    {
        TP_MONITOR_EXECUTION,
        0U,
        &Os_Task5ExecutionBudgetData
    },
    {
        TP_MONITOR_LOCK,
        150000U,
        &Os_Task5LockAllInterruptBudgetData
    },
    {
        TP_MONITOR_LOCK,
        100000U,
        &Os_Task5LockOsInterruptBudgetData
    },
    &Os_Task5ResourceTpConfig[0],
    &Os_Task5TimingProtectionRunningData
};


static const Os_TpObjectConfigType Os_Task2TpConfig =
{
    55000U,                                 
    {
        TP_MONITOR_EXECUTION,
        200000U,
        &Os_Task2ExecutionBudgetData
    },
    {
        TP_MONITOR_LOCK,
        150000U,
        &Os_Task2LockAllInterruptBudgetData
    },
    {
        TP_MONITOR_LOCK,
        0U,
        &Os_Task2LockOsInterruptBudgetData
    },
    NULL_PTR,
    &Os_Task2TimingProtectionRunningData
};


static const Os_TpObjectConfigType Os_Task3TpConfig =
{
    57500U,                                 
    {
        TP_MONITOR_EXECUTION,
        200000U,
        &Os_Task3ExecutionBudgetData
    },
    {
        TP_MONITOR_LOCK,
        0U,
        &Os_Task3LockAllInterruptBudgetData
    },
    {
        TP_MONITOR_LOCK,
        100000U,
        &Os_Task3LockOsInterruptBudgetData
    },
    NULL_PTR,
    &Os_Task3TimingProtectionRunningData
};

static const Os_TpBudgetConfigType Os_OsOsResource_2BudgetConfig =
{
    TP_MONITOR_LOCK, /* Type */
    80000,          /* Budget */
    &Os_OsLockOsResource_2BudgetData
};

static const Os_TpReSourceBudgetConfigType Os_OsOsResource_2TpConfig =
{
    2,  /* ResourceID */
    &Os_OsOsResource_2BudgetConfig
};

static const Os_TpReSourceBudgetConfigRefType Os_Task12_Core1ResourceTpConfig[2] =
{
    &Os_OsOsResource_2TpConfig,
    NULL_PTR,
};

static const Os_TpObjectConfigType Os_Task12_Core1TpConfig =
{
    72500U,                                 
    {
        TP_MONITOR_EXECUTION,
        200000U,
        &Os_Task12_Core1ExecutionBudgetData
    },
    {
        TP_MONITOR_LOCK,
        0U,
        &Os_Task12_Core1LockAllInterruptBudgetData
    },
    {
        TP_MONITOR_LOCK,
        100000U,
        &Os_Task12_Core1LockOsInterruptBudgetData
    },
    &Os_Task12_Core1ResourceTpConfig[0],
    &Os_Task12_Core1TimingProtectionRunningData
};


static const Os_TpObjectConfigType Os_Task11_Core1TpConfig =
{
    51999U,                                 
    {
        TP_MONITOR_EXECUTION,
        202499U,
        &Os_Task11_Core1ExecutionBudgetData
    },
    {
        TP_MONITOR_LOCK,
        150000U,
        &Os_Task11_Core1LockAllInterruptBudgetData
    },
    {
        TP_MONITOR_LOCK,
        100000U,
        &Os_Task11_Core1LockOsInterruptBudgetData
    },
    NULL_PTR,
    &Os_Task11_Core1TimingProtectionRunningData
};


static const Os_TpObjectConfigType Os_OsIsr_BaseTimer1TpConfig =
{
    64999U,                                 
    {
        TP_MONITOR_EXECUTION,
        200000U,
        &Os_OsIsr_BaseTimer1ExecutionBudgetData
    },
    {
        TP_MONITOR_LOCK,
        100000U,
        &Os_OsIsr_BaseTimer1LockAllInterruptBudgetData
    },
    {
        TP_MONITOR_LOCK,
        150000U,
        &Os_OsIsr_BaseTimer1LockOsInterruptBudgetData
    },
    NULL_PTR,
    &Os_OsIsr_BaseTimer1TimingProtectionRunningData
};

CONSTP2CONST(Os_TpObjectConfigType, TYPEDEF, OS_CONST) Os_TimingProection_ObjSet[TOTAL_TPUSED_NUM] =
{
    &Os_Task1TpConfig,
    &Os_Task5TpConfig,
    &Os_Task2TpConfig,
    &Os_Task3TpConfig,
    &Os_OsIsr_BaseTimer1TpConfig,
    &Os_Task12_Core1TpConfig,
    &Os_Task11_Core1TpConfig,
};

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






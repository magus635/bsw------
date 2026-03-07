/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_resource_Lcfg.c
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
*   Genaration Time       : 2026-03-05 20:16:15
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
#include "Os_lock.h"
#include "Os_resource_Cfg.h"
#include "Os_resource_Lcfg.h"
#include "Os_resource_types.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Type Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Structure Definitions                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define OS_START_SEC_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_ResourceRunningDataType Os_OsResource_0_RunningData;
static Os_LockConfigType Os_LockConfig_OsResource_0;
static Os_ResourceRunningDataType Os_OsResource_1_RunningData;
static Os_LockConfigType Os_LockConfig_OsResource_1;
static Os_ResourceRunningDataType Os_Core0ResSchedulerResource_RunningData;
static Os_LockConfigType Os_LockConfig_Core0ResSchedulerResource;
#define OS_STOP_SEC_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static Os_ResourceRunningDataType Os_OsResource_2_RunningData;
static Os_LockConfigType Os_LockConfig_OsResource_2;
static Os_ResourceRunningDataType Os_Core1ResSchedulerResource_RunningData;
static Os_LockConfigType Os_LockConfig_Core1ResSchedulerResource;
#define OS_STOP_SEC_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
static const uint32 Os_OsResource_0_AccessObjectIdList[OS_RESOURCE_OSRESOURCE_0_ACCESS_OBJECT_NUM] =
{
    1UL,
    2UL
};

static const uint32 Os_OsResource_1_AccessObjectIdList[OS_RESOURCE_OSRESOURCE_1_ACCESS_OBJECT_NUM] =
{
    2UL
};

static const uint32 Os_OsResource_2_AccessObjectIdList[OS_RESOURCE_OSRESOURCE_2_ACCESS_OBJECT_NUM] =
{
    40UL,
    41UL,
    42UL
};

static const uint32 Os_Core0ResSchedulerResource_AccessObjectIdList[OS_RESOURCE_CORE0_RESSCHEDULER_ACCESS_OBJECT_NUM] =
{
    0UL,
    1UL,
    2UL,
    3UL,
    4UL,
    5UL,
    6UL,
    7UL,
    8UL,
    9UL,
    10UL,
    11UL,
    12UL,
    30UL,
    33UL
};

static const uint32 Os_Core1ResSchedulerResource_AccessObjectIdList[OS_RESOURCE_CORE1_RESSCHEDULER_ACCESS_OBJECT_NUM] =
{
    37UL,
    38UL,
    39UL,
    40UL,
    41UL,
    42UL,
    43UL,
    44UL,
    45UL,
    46UL
};

static const Os_ResourceConfigType Os_ResourceConfig_OsResource_0 =
{
    0UL,                     /* ResID */
    OS_RESOURCETYPE_STANDARD,    /* ResourceType */
    4UL,                   /* CeilingPriority */
    OS_RESOURCE_INVALID_CEILING,                /* CeilingIsrLevel */
    &Os_LockConfig_OsResource_0,                  /* Lock */
    /* AccessObjectList */
    {
        Os_OsResource_0_AccessObjectIdList,
        OS_RESOURCE_OSRESOURCE_0_ACCESS_OBJECT_NUM
    },
    &Os_OsResource_0_RunningData              /* RunningData */
};

static const Os_ResourceConfigType Os_ResourceConfig_OsResource_1 =
{
    1UL,                     /* ResID */
    OS_RESOURCETYPE_STANDARD,    /* ResourceType */
    4UL,                   /* CeilingPriority */
    OS_RESOURCE_INVALID_CEILING,                /* CeilingIsrLevel */
    &Os_LockConfig_OsResource_1,                  /* Lock */
    /* AccessObjectList */
    {
        Os_OsResource_1_AccessObjectIdList,
        OS_RESOURCE_OSRESOURCE_1_ACCESS_OBJECT_NUM
    },
    &Os_OsResource_1_RunningData              /* RunningData */
};

static const Os_ResourceConfigType Os_ResourceConfig_Core0ResSchedulerResource =
{
    2UL,                     /* ResID */
    OS_RESOURCETYPE_STANDARD,   /* ResourceType */
    0xFFFFFFFFUL,                   /* CeilingPriority */
    OS_RESOURCE_INVALID_CEILING,                /* CeilingIsrLevel */
    &Os_LockConfig_Core0ResSchedulerResource,                  /* Lock */
    {
        Os_Core0ResSchedulerResource_AccessObjectIdList,
        OS_RESOURCE_CORE0_RESSCHEDULER_ACCESS_OBJECT_NUM
    },
    &Os_Core0ResSchedulerResource_RunningData              /* RunningData */
};

static const Os_ResourceConfigType Os_ResourceConfig_OsResource_2 =
{
    3UL,                     /* ResID */
    OS_RESOURCETYPE_STANDARD,    /* ResourceType */
    5UL,                   /* CeilingPriority */
    OS_RESOURCE_INVALID_CEILING,                /* CeilingIsrLevel */
    &Os_LockConfig_OsResource_2,                  /* Lock */
    /* AccessObjectList */
    {
        Os_OsResource_2_AccessObjectIdList,
        OS_RESOURCE_OSRESOURCE_2_ACCESS_OBJECT_NUM
    },
    &Os_OsResource_2_RunningData              /* RunningData */
};

static const Os_ResourceConfigType Os_ResourceConfig_Core1ResSchedulerResource =
{
    4UL,                     /* ResID */
    OS_RESOURCETYPE_STANDARD,   /* ResourceType */
    0xFFFFFFFFUL,                   /* CeilingPriority */
    OS_RESOURCE_INVALID_CEILING,                /* CeilingIsrLevel */
    &Os_LockConfig_Core1ResSchedulerResource,                  /* Lock */
    {
        Os_Core1ResSchedulerResource_AccessObjectIdList,
        OS_RESOURCE_CORE1_RESSCHEDULER_ACCESS_OBJECT_NUM
    },
    &Os_Core1ResSchedulerResource_RunningData              /* RunningData */
};

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
const Os_ResourceConfigRefType Os_ResourceConfigSet[OS_RESOURCE_TOTAL_NUM + 1U] = 
{
    &Os_ResourceConfig_OsResource_0,
    &Os_ResourceConfig_OsResource_1,
    &Os_ResourceConfig_Core0ResSchedulerResource,
    &Os_ResourceConfig_OsResource_2,
    &Os_ResourceConfig_Core1ResSchedulerResource,
    NULL_PTR
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






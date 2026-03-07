/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_spinlock_Lcfg.c
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
*   Genaration Time       : 2026-03-05 20:16:16
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
#include "Os_spinlock_Cfg.h"
#include "Os_spinlock_Lcfg.h"
#include "Os_spinlock_types.h"
#include "Os_application_Cfg.h"
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
#define OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"
static Os_SpinlockLockType Os_LockStatus_OsSpinlock_0;
static Os_SpinlockLockType Os_LockStatus_StartupSynSpinlock;
static Os_SpinlockLockType Os_LockStatus_ShutdownSynSpinlock;

static Os_LockConfigType Os_LockConfig_OsSpinlock_0;
static Os_SpinlockRunningDataType Os_OsSpinlock_0_RunningData;
#define OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
static const Os_SpinlockConfigType Os_SpinlockConfig_OsSpinlock_0 =
{
    0UL,                     /* SpinlockId */
    &Os_LockStatus_OsSpinlock_0,  /* LockStatus */
    &Os_LockConfig_OsSpinlock_0,    /* Lock */
    LOCK_NOTHING,         /* OsSpinlockLockMethod */
    0UL,            /* SpinlockSuccessorID */
    0UL,         /* SpinlockSuccesorListID */
    0x9UL,         /* AccessApplicationIdMask */
    &Os_OsSpinlock_0_RunningData                   /* SpinlockRunningData */
};

static const Os_SpinlockConfigType Os_SpinlockConfig_StartupSynSpinlock = 
{
        1UL,                     /* SpinlockId */
    &Os_LockStatus_StartupSynSpinlock,  /* LockStatus */
    NULL_PTR,                   /* Lock */
    LOCK_NOTHING,         /* OsSpinlockLockMethod */
    0UL,            /* SpinlockSuccessorID */
    0UL,         /* SpinlockSuccesorListID */
    0UL,         /* AccessApplicationIdMask */
    NULL_PTR            /* SpinlockRunningData */
};

static const Os_SpinlockConfigType Os_SpinlockConfig_ShutdownSynSpinlock = 
{
        2UL,                     /* SpinlockId */
    &Os_LockStatus_ShutdownSynSpinlock,  /* LockStatus */
    NULL_PTR,                   /* Lock */
    LOCK_NOTHING,         /* OsSpinlockLockMethod */
    0UL,            /* SpinlockSuccessorID */
    0UL,         /* SpinlockSuccesorListID */
    0UL,         /* AccessApplicationIdMask */
    NULL_PTR            /* SpinlockRunningData */
};
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
const Os_SpinlockConfigRefType Os_SpinlockConfigSet[OS_SPINLOCK_TOTAL_NUM] = 
{
    &Os_SpinlockConfig_OsSpinlock_0,
    &Os_SpinlockConfig_StartupSynSpinlock,
    &Os_SpinlockConfig_ShutdownSynSpinlock
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






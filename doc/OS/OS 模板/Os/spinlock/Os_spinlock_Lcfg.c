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
*   Genaration Time       : [!"$datetime"!]
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
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
#define OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"
[!LOOP "node:order(./OsSpinlock/*,'@index')"!][!//
static Os_SpinlockLockType Os_LockStatus_[!"node:name(.)"!];
[!ENDLOOP!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
    [!VAR "CurrentIocName" = "node:name(.)"!][!//
    [!VAR "IocSpinlockIsNeeded" = "'false'"!][!//
    [!VAR "SenderCoreId" = "0"!][!//
    [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
        [!IF "@index = 0"!][!//
            [!VAR "SenderCoreId" = "node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
        [!ELSE!][!//
            [!IF "$SenderCoreId != node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                [!VAR "IocSpinlockIsNeeded" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$IocSpinlockIsNeeded = 'false'"!][!//
        [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
            [!IF "$SenderCoreId != node:ref(node:ref(OsIocReceivingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                [!VAR "IocSpinlockIsNeeded" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDIF!][!//
    [!IF "$IocSpinlockIsNeeded = 'true'"!][!//
        static Os_SpinlockLockType Os_LockStatus_[!"$CurrentIocName"!];
    [!ENDIF!][!//
[!ENDLOOP!][!//
static Os_SpinlockLockType Os_LockStatus_StartupSynSpinlock;
static Os_SpinlockLockType Os_LockStatus_ShutdownSynSpinlock;

[!LOOP "node:order(./OsSpinlock/*,'@index')"!][!//
static Os_LockConfigType Os_LockConfig_[!"node:name(.)"!];
[!ENDLOOP!][!//

[!LOOP "node:order(./OsSpinlock/*,'@index')"!][!//
static Os_SpinlockRunningDataType Os_[!"node:name(.)"!]_RunningData;
[!ENDLOOP!][!//
#define OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "CurrentSpinlockCnt" = "0"!][!//
[!VAR "TotalSpinlockCnt" = "count(./OsSpinlock/*)"!][!//
[!LOOP "node:order(./OsSpinlock/*,'@index')"!][!//
[!VAR "SuccessorId" = "0"!][!//
[!VAR "FirstSuccessorIndex" ="$CurrentSpinlockCnt"!][!//
[!VAR "SpinlockAccessApplicationMask" = "0"!][!//
static const Os_SpinlockConfigType Os_SpinlockConfig_[!"node:name(.)"!] =
{
    [!INDENT "4"!][!//
    [!"@index"!]UL,                     /* SpinlockId */
    &Os_LockStatus_[!"node:name(.)"!],  /* LockStatus */
    &Os_LockConfig_[!"node:name(.)"!],    /* Lock */
    [!"OsSpinlockLockMethod"!],         /* OsSpinlockLockMethod */
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!VAR "ExitLoop" = "'false'"!][!//
    [!FOR "i" = "1" TO "$TotalSpinlockCnt"!][!//
        [!VAR "LoopCount" = "0"!][!//
        [!LOOP "node:order(./OsSpinlock/*,'@index')"!][!//
            [!VAR "LoopCount" = "$LoopCount + 1"!][!//
            [!IF "num:i($CurrentSpinlockCnt) != @index"!][!//
                [!IF "node:refexists(OsSpinlockSuccessor)"!][!//
                    [!IF "node:pos(node:ref(OsSpinlockSuccessor)) = $FirstSuccessorIndex"!][!//
                        [!VAR "SuccessorId" = "$SuccessorId + 1"!][!//
                        [!VAR "FirstSuccessorIndex" = "@index"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!IF "$LoopCount = $TotalSpinlockCnt"!][!//
                [!VAR "ExitLoop" = "'true'"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$ExitLoop = 'true'"!][!//
            [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
    [!ENDSELECT!][!//
    [!VAR "CurrentSpinlockCnt" = "$CurrentSpinlockCnt + 1"!][!//
    [!"num:i($SuccessorId)"!]UL,            /* SpinlockSuccessorID */
    [!"num:i($FirstSuccessorIndex)"!]UL,         /* SpinlockSuccesorListID */
    [!LOOP "node:order(./OsSpinlockAccessingApplication/*,'@index')"!][!//
        [!VAR "SpinlockAccessApplicationMask" = "bit:or(num:i($SpinlockAccessApplicationMask), bit:shl(num:i(1), node:pos(node:ref(.))))"!][!//
    [!ENDLOOP!][!//
    [!"num:inttohex(num:i($SpinlockAccessApplicationMask))"!]UL,         /* AccessApplicationIdMask */
    &Os_[!"node:name(.)"!]_RunningData                   /* SpinlockRunningData */
    [!ENDINDENT!][!//
};

[!ENDLOOP!][!//
[!VAR "IocSpinlockNum" = "0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
    [!VAR "CurrentIocName" = "node:name(.)"!][!//
    [!VAR "IocSpinlockIsNeeded" = "'false'"!][!//
    [!VAR "SenderCoreId" = "0"!][!//
    [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
        [!IF "@index = 0"!][!//
            [!VAR "SenderCoreId" = "node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
        [!ELSE!][!//
            [!IF "$SenderCoreId != node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                [!VAR "IocSpinlockNum" = "$IocSpinlockNum + 1"!][!//
                [!VAR "IocSpinlockIsNeeded" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$IocSpinlockIsNeeded = 'false'"!][!//
        [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
            [!IF "$SenderCoreId != node:ref(node:ref(OsIocReceivingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                [!VAR "IocSpinlockNum" = "$IocSpinlockNum + 1"!][!//
                [!VAR "IocSpinlockIsNeeded" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDIF!][!//
    [!IF "$IocSpinlockIsNeeded = 'true'"!][!//
static const Os_SpinlockConfigType Os_SpinlockConfig_[!"$CurrentIocName"!]Spinlock = 
{
    [!INDENT "4"!][!//
    [!"num:i($TotalSpinlockCnt + $IocSpinlockNum)"!]UL,                     /* SpinlockId */
    &Os_LockStatus_[!"$CurrentIocName"!],    /* LockStatus */
    NULL_PTR,                   /* Lock */
    LOCK_NOTHING,         /* OsSpinlockLockMethod */
    0UL,            /* SpinlockSuccessorID */
    0UL,         /* SpinlockSuccesorListID */
    0UL,         /* AccessApplicationIdMask */
    NULL_PTR            /* SpinlockRunningData */
    [!ENDINDENT!][!//
};

    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
static const Os_SpinlockConfigType Os_SpinlockConfig_StartupSynSpinlock = 
{
    [!INDENT "4"!][!//
    [!"num:i($TotalSpinlockCnt)"!]UL,                     /* SpinlockId */
    &Os_LockStatus_StartupSynSpinlock,  /* LockStatus */
    NULL_PTR,                   /* Lock */
    LOCK_NOTHING,         /* OsSpinlockLockMethod */
    0UL,            /* SpinlockSuccessorID */
    0UL,         /* SpinlockSuccesorListID */
    0UL,         /* AccessApplicationIdMask */
    NULL_PTR            /* SpinlockRunningData */
    [!ENDINDENT!][!//
};

static const Os_SpinlockConfigType Os_SpinlockConfig_ShutdownSynSpinlock = 
{
    [!INDENT "4"!][!//
    [!"num:i($TotalSpinlockCnt + 1)"!]UL,                     /* SpinlockId */
    &Os_LockStatus_ShutdownSynSpinlock,  /* LockStatus */
    NULL_PTR,                   /* Lock */
    LOCK_NOTHING,         /* OsSpinlockLockMethod */
    0UL,            /* SpinlockSuccessorID */
    0UL,         /* SpinlockSuccesorListID */
    0UL,         /* AccessApplicationIdMask */
    NULL_PTR            /* SpinlockRunningData */
    [!ENDINDENT!][!//
};
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
const Os_SpinlockConfigRefType Os_SpinlockConfigSet[OS_SPINLOCK_TOTAL_NUM] = 
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(./OsSpinlock/*,'@index')"!][!//
    &Os_SpinlockConfig_[!"node:name(.)"!],
    [!ENDLOOP!][!//
    [!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
        [!VAR "CurrentIocName" = "node:name(.)"!][!//
        [!VAR "IocSpinlockIsNeeded" = "'false'"!][!//
        [!VAR "SenderCoreId" = "0"!][!//
        [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
            [!IF "@index = 0"!][!//
                [!VAR "SenderCoreId" = "node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
            [!ELSE!][!//
                [!IF "$SenderCoreId != node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                    [!VAR "IocSpinlockIsNeeded" = "'true'"!][!//
                    [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$IocSpinlockIsNeeded = 'false'"!][!//
            [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
                [!IF "$SenderCoreId != node:ref(node:ref(OsIocReceivingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                    [!VAR "IocSpinlockIsNeeded" = "'true'"!][!//
                    [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
        [!IF "$IocSpinlockIsNeeded = 'true'"!][!//
    &Os_SpinlockConfig_[!"$CurrentIocName"!]Spinlock,
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    &Os_SpinlockConfig_StartupSynSpinlock,
    &Os_SpinlockConfig_ShutdownSynSpinlock
    [!ENDINDENT!][!//
};
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/






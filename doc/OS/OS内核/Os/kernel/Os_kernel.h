/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_kernel.h
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
#ifndef OS_KERNEL_H_
#define OS_KERNEL_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_kernel_Lcfg.h"
#include "Os_compiler_types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define OS_CONTEXT_TASK                         ((uint32)1 << 0)
#define OS_CONTEXT_ISR2                         ((uint32)1 << 1)
#define OS_CONTEXT_ERRORHOOK                    ((uint32)1 << 2)
#define OS_CONTEXT_PRETASKHOOK                  ((uint32)1 << 3)
#define OS_CONTEXT_POSTTASKHOOK                 ((uint32)1 << 4)
#define OS_CONTEXT_STARTUPHOOK                  ((uint32)1 << 5)
#define OS_CONTEXT_SHUTDOWNHOOK                 ((uint32)1 << 6)
#define OS_CONTEXT_ALARMCALLBACK                ((uint32)1 << 7)
#define OS_CONTEXT_PROTECTIONHOOK               ((uint32)1 << 8)
#define OS_CONTEXT_IOCCALLBACK                  ((uint32)1 << 9)
#define OS_CONTEXT_ISR1                         ((uint32)1 << 10)

#define OS_CALL_ACTIVATETASK                    (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_ACTIVATETASKASYN                (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_TERMINATETASK                   (uint32)(OS_CONTEXT_TASK)
#define OS_CALL_CHAINTASK                       (uint32)(OS_CONTEXT_TASK)
#define OS_CALL_SCHEDULE                        (uint32)(OS_CONTEXT_TASK)
#define OS_CALL_GETTASKID                       (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ERRORHOOK |     \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |    \
                                                OS_CONTEXT_PROTECTIONHOOK | OS_CONTEXT_ISR2)
#define OS_CALL_GETTASKSTATE                    (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ERRORHOOK |     \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |    \
                                                OS_CONTEXT_ISR2)
#define OS_CALL_DISABLEALLINTERRUPTS            (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |          \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK     \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |    \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK |    \
                                                OS_CONTEXT_ALARMCALLBACK | OS_CONTEXT_PROTECTIONHOOK | \
                                                OS_CONTEXT_ISR1)
#define OS_CALL_ENABLEALLINTERRUPTS             (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |           \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK      \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |     \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK |     \
                                                OS_CONTEXT_ALARMCALLBACK | OS_CONTEXT_PROTECTIONHOOK | \
                                                OS_CONTEXT_ISR1)
#define OS_CALL_SUSPENDALLINTERRUPTS            (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |           \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK      \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |     \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK |     \
                                                OS_CONTEXT_ALARMCALLBACK | OS_CONTEXT_PROTECTIONHOOK | \
                                                OS_CONTEXT_ISR1)
#define OS_CALL_RESUMEALLINTERRUPTS             (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |           \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK      \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |     \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK |     \
                                                OS_CONTEXT_ALARMCALLBACK | OS_CONTEXT_PROTECTIONHOOK | \
                                                OS_CONTEXT_ISR1)
#define OS_CALL_SUSPENDOSINTERRUPTS             (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |           \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK |    \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |     \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK |     \
                                                OS_CONTEXT_ALARMCALLBACK | OS_CONTEXT_PROTECTIONHOOK |    \
                                                OS_CONTEXT_ISR1)
#define OS_CALL_RESUMEOSINTERRUPTS              (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |           \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK |    \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK  |    \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK  |    \
                                                OS_CONTEXT_ALARMCALLBACK | OS_CONTEXT_PROTECTIONHOOK |    \
                                                OS_CONTEXT_ISR1)
#define OS_CALL_GETRESOURCE                     (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_RELEASERESOURCE                 (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_SETEVENT                        (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_SETEVENTASYN                    (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_CLEAREVENT                      (uint32)(OS_CONTEXT_TASK)
#define OS_CALL_GETEVENT                        (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |            \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_PRETASKHOOK  |    \
                                                OS_CONTEXT_POSTTASKHOOK)
#define OS_CALL_WAITEVENT                       (uint32)(OS_CONTEXT_TASK)
#define OS_CALL_GETALARMBASE                    (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |            \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_PRETASKHOOK    |  \
                                                OS_CONTEXT_POSTTASKHOOK)
#define OS_CALL_GETALARM                        (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |            \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_PRETASKHOOK    |  \
                                                OS_CONTEXT_POSTTASKHOOK)
#define OS_CALL_SETRELALARM                     (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_SETABSALARM                     (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_CANCELALARM                     (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_GETACTIVEAPPLICATIONMODE        (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2            \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_PRETASKHOOK     \
                                                OS_CONTEXT_POSTTASKHOOK | OS_CONTEXT_STARTUPHOOK      \
                                                OS_CONTEXT_SHUTDOWNHOOK)
#define OS_CALL_SHUTDOWNOS                      (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |          \
                                                OS_CONTEXT_ERRORHOOK | OS_CONTEXT_STARTUPHOOK)
#define OS_CALL_GETAPPLICATIONID                (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |          \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK  |  \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |    \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK |    \
                                                OS_CONTEXT_PROTECTIONHOOK)
#define OS_CALL_GETISRID                        (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2         |  \
                                                OS_CONTEXT_ERRORHOOK |    OS_CONTEXT_PROTECTIONHOOK)
#define OS_CALL_CALLTRUSTEDFUNCTION             (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_CHECKISRMEMORYACCESS            (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2         |  \
                                                OS_CONTEXT_ERRORHOOK | OS_CONTEXT_PROTECTIONHOOK)
#define OS_CALL_CHECKTASKMEMORYACCESS           (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2         |  \
                                                OS_CONTEXT_ERRORHOOK | OS_CONTEXT_PROTECTIONHOOK)
#define OS_CALL_CHECKOBJECTACCESS               (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2         |  \
                                                OS_CONTEXT_ERRORHOOK | OS_CONTEXT_PROTECTIONHOOK)
#define OS_CALL_CHECKOBJECTOWNERSHIP            (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2         |  \
                                                OS_CONTEXT_ERRORHOOK | OS_CONTEXT_PROTECTIONHOOK)
#define OS_CALL_STARTSCHEDULETABLEREL           (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_STARTSCHEDULETABLEABS           (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_STOPSCHEDULETABLE               (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_NEXTSCHEDULETABLE               (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_STARTSCHEDULETABLESYNC            (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_SYNCSCHEDULETABLE               (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_GETSCHEDULETABLESTATUS             (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_SETSCHEDULETABLESYNC            (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_INCREMENTCOUNTER                (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_GETCOUNTERVALUE                 (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_GETELAPSEDVALUE                 (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_TERMINATEAPPLICATION            (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |            \
                                                OS_CONTEXT_ERRORHOOK)
#define OS_CALL_ALLOWACCESS                     (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_GETAPPLICATIONSTATE             (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |            \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK     | \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |      \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK |      \
                                                OS_CONTEXT_PROTECTIONHOOK)
#define OS_CALL_ALLOWACCESS                     (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_CONTROLIDLE                     (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_GETCURRENTAPPLICATIONID         (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |            \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK     | \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |      \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK |      \
                                                OS_CONTEXT_PROTECTIONHOOK)
#define OS_CALL_READPERIPHERAL8                 (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_READPERIPHERAL16                (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_READPERIPHERAL32                (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_WRITEPERIPHERAL8                (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_WRITEPERIPHERAL16               (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_WRITEPERIPHERAL32               (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_MODIFYPERIPHERAL8               (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_MODIFYPERIPHERAL16              (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_MODIFYPERIPHERAL32              (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_DISABLEINTERRUPTSOURCE          (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_ENABLEINTERRUPTSOURCE           (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_CLEARPENDINGINTERRUPT           (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_ISOSSTARTED                     (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |            \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK       \
                                                OS_CONTEXT_PRETASKHOOK | OS_CONTEXT_POSTTASKHOOK |      \
                                                OS_CONTEXT_STARTUPHOOK | OS_CONTEXT_SHUTDOWNHOOK |      \
                                                OS_CONTEXT_ALARMCALLBACK | OS_CONTEXT_PROTECTIONHOOK |    \
                                                OS_CONTEXT_ISR1)

#define OS_CALL_GETSPINLOCK                     (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_RELEASESPINLOCK                 (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_TRYTOGETSPINLOCK                (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)

#define OS_CALL_GETNUMBEROFACTIVATEDCORES       (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2)
#define OS_CALL_SHUTDOWNALLCORES                (uint32)(OS_CONTEXT_TASK | OS_CONTEXT_ISR2 |            \
                                                OS_CONTEXT_ERRORHOOK |     OS_CONTEXT_STARTUPHOOK)

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/
LOCAL_FORCEINLINE CoreIdType Os_Inf_GetCoreId(void)
{
    CoreIdType Physical_CoreID;

    Physical_CoreID = Os_Inf_CompilerGetCoreID();

    return Os_ConfigSet.CoreIDListPtr[Physical_CoreID];
}
/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : CodeFreeze
*   Service ID              : None.
*   Description             : Freeze current core.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) CodeFreeze
(
    void
);
/****************************************************************************************************
*   Function Name           : Os_PreInit
*   Service ID              : None.
*   Description             : Called before StartOS for preparing to start OS.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_PreInit
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreAppDataInfo
*   Service ID              : None.
*   Description             : Get current core application data Information.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Pointer of running application running data structure.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_ApplicationRunningTimeDataTypeRef, OS_CODE) OsKernel_GetCurrentCoreAppDataInfo
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreSchedulerDataInfo
*   Service ID              : None.
*   Description             : Get current core scheduler data information.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Pointer of scheduler running data structure.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_SchedulerTypeRef, OS_CODE) OsKernel_GetCurrentCoreSchedulerDataInfo
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreHookDataInfo
*   Service ID              : None.
*   Description             : Get current core hook data information.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Pointer of hook running data structure.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_HookDynamicTypeRef, OS_CODE) OsKernel_GetCurrentCoreHookDataInfo
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreTpDataInfo
*   Service ID              : None.
*   Description             : Get current core timing protection data information.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Pointer of TP Data structure.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_TpRunningDataTypeRef, OS_CODE) OsKernel_GetCurrentCoreTpDataInfo
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreMaxCoreMpRegionNum
*   Service ID              : None.
*   Description             : Get Max MP region number of current core.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Max MP region number of current core.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreMaxCoreMpRegionNum
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreMaxAppMpRegionNum
*   Service ID              : None.
*   Description             : Get Max number of application MP regions of current core.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Max number of application MP regions of current core.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreMaxAppMpRegionNum
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreMaxObjectMpRegionNum
*   Service ID              : None.
*   Description             : Get max number of MPU regions of current core object.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : max number of MPU regions of current core object.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreMaxObjectMpRegionNum
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreTotalTaskPriorityNum
*   Service ID              : None.
*   Description             : Get the number of priority level of current core.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : The total priority level of current core.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreTotalTaskPriorityNum
(
    void
);
/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreTaskPriBufferPtr
*   Service ID              : None.
*   Description             : Get the address of array which contains every task priority level
*                           : buffer address.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : The address of array which contains every task priority level buffer
*                           ??oaddress
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(TaskRefType, OS_CODE) OsKernel_GetCurrentCoreTaskPriBufferPtr
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreTaskQueueSizePtr
*   Service ID              : None.
*   Description             : Get the address of array which contains priority level queue size
*                           : of current core.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Array address which contains priority level queue size.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(P2CONST(uint32, TYPEDEF, OS_CONST), OS_CODE) OsKernel_GetCurrentCoreTaskQueueSizePtr
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreAddressofBitArray
*   Service ID              : None.
*   Description             : Get the address of BitArray which contains task priority level of
*                           : current core.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : The address of BitArray which contains task priority level of current core.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(P2VAR(uint32, TYPEDEF, OS_VAR), OS_CODE) OsKernel_GetCurrentCoreAddressofBitArray
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreTaskFifoQueuePtr
*   Service ID              : None
*   Description             : Get the address of FIFO queue array.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : the address of FIFO queue array.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_FifoQueueTypeRef, OS_CODE) OsKernel_GetCurrentCoreTaskFifoQueuePtr
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreHooksInfoPtr
*   Service ID              : Get the address of running hook info of current core.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Pointer of hook information.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_CoreHooksTypeRef, OS_CODE) OsKernel_GetCurrentCoreHooksInfoPtr
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreAlarmCallbackFlagPtr
*   Service ID              : None.
*   Description             : Get the Buffer Pointer which content is used to indicate OS is running
*                           : at Alarm callback or not.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Buffer Pointer.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(P2VAR(boolean, TYPEDEF, OS_VAR), OS_CODE) OsKernel_GetCurrentCoreAlarmCallbackFlagPtr
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentCoreKernelAppID
*   Service ID              : None.
*   Description             : Get the kernel(system) application ID of current core.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Kernel(system) Application ID.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) OsKernel_GetCurrentCoreKernelAppID
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCurrentRunningContext
*   Service ID              : None.
*   Description             : Get the running context environment of current core.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : The running context environment of current core.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) OsKernel_GetCurrentRunningContext
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_GetCoreIdleTask
*   Service ID              : None.
*   Description             : Get Idle Task ID of current core.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Current core idle task ID.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(TaskType, OS_CODE) OsKernel_GetCoreIdleTask
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_CheckObjectBelongToCurrentCore
*   Service ID              : None.
*   Description             : Check the specified object is assigned to current core or not.
*   Parameters in           : ObjectID.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : TRUE indicates specified object is assigned to current core .
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsKernel_CheckObjectBelongToCurrentCore
(
    uint32 ObjectID
);

/****************************************************************************************************
*   Function Name           : OsKernel_StartOs_InitFunction
*   Service ID              : None.
*   Description             : The First thread of OS.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsKernel_StartOs_InitFunction
(
    void
);

/****************************************************************************************************
*   Function Name           : OsKernel_ControlIdle
*   Service ID              : None.
*   Description             : Control core enter idle state.
*   Parameters in           : CoreID.
*                           : IdleMode. Idle Mode
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType. E_OK indicates success and others failure
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsKernel_ControlIdle
(
    CoreIdType CoreID,
    IdleModeType IdleMode
);

/****************************************************************************************************
*   Function Name           : OsKernel_ShutdownOS
*   Service ID              : None.
*   Description             : Shut down current core.
*   Parameters in           : Error. Error reason
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsKernel_ShutdownOS
(
    StatusType Error
);

/****************************************************************************************************
*   Function Name           : OsKernel_ShutdownAllCores
*   Service ID              : None.
*   Description             : Shut down all AutoSar core.
*   Parameters in           : Error. Error reason.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsKernel_ShutdownAllCores
(
    StatusType Error
);
#endif /* OS_KERNEL_H_ */

/****************************************************************************************************
**     End of File: Os_kernel.h                                                                    **
****************************************************************************************************/


/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_isr.h
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
#ifndef OS_ISR_H_
#define OS_ISR_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_isr_types.h"
#include "Compiler.h"
#include "Os_kernel.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsIsr_ResumeAllInterrupts
*   Service ID              : None.
*   Description             : Internal function of ResumeAllInterrupts.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_ResumeAllInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIsr_SuspendAllInterrupts
*   Service ID              : None.
*   Description             : Internal function of SuspendAllInterrupts.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_SuspendAllInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIsr_ResumeOSInterrupts
*   Service ID              : None.
*   Description             : Internal function of ResumeOSInterrupts.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_ResumeOSInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIsr_SuspendOSInterrupts
*   Service ID              : None.
*   Description             : Internal function of SuspendOSInterrupts.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_SuspendOSInterrupts
(
    void
);
/****************************************************************************************************
*   Function Name           : OsIsr_InstallInterrupt
*   Service ID              : None.
*   Description             : Install specific isr.
*   Parameters in           : IsrIndex: ID of isr to be installed.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_InstallInterrupt
(
    ISRType IsrIndex
);

/****************************************************************************************************
*   Function Name           : OsIsr_InterruptHandler
*   Service ID              : None.
*   Description             : Global isr handler of OS.
*   Parameters in           : NextIntID: Hardware id of next interrupt.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_InterruptHandler
(
    uint32 NextIntID
);

/****************************************************************************************************
*   Function Name           : OsIsr_UndefinedISR
*   Service ID              : None.
*   Description             : Handles an error that triggers an uninstalled interrupt.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_UndefinedISR
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIsr_PreISR
*   Service ID              : None.
*   Description             : Processing function before execute isr handler.
*   Parameters in           : NextIsr: Pointer to configuration of next isr.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_PreISR
(
    Os_IsrConfigRefType NextIsr
);

/****************************************************************************************************
*   Function Name           : OsIsr_PostISR
*   Service ID              : None.
*   Description             : Post-processing function after isr handler.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_PostISR
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIsr_PostServiceCallISR
*   Service ID              : None.
*   Description             : Post-processing function after a cross-core service call isr.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_PostServiceCallISR
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIsr_IsrInit
*   Service ID              : None.
*   Description             : Initialize an isr.
*   Parameters in           : IsrCount: ID of isr to be intialized.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_IsrInit
(
    uint32 IsrCount
);

/****************************************************************************************************
*   Function Name           : OsIsr_ResetIntApiCount
*   Service ID              : None.
*   Description             : Clear the isr service counter.
*   Parameters in           : ObjectId: Object id of the owner of current service counter.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_ResetIntApiCount
(
    uint32 ObjectId
);

/****************************************************************************************************
*   Function Name           : OsIsr_SuspendISR
*   Service ID              : None.
*   Description             : Suspend all interrupt(ISR1/ISR2/TP ISR).
*   Parameters in           : None.
*   Parameters inout        : Level: Pointer to var to record current isr level.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_SuspendISR
(
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) Level
);

/****************************************************************************************************
*   Function Name           : OsIsr_SuspendISR2
*   Service ID              : None.
*   Description             : Suspend ISR2.
*   Parameters in           : None.
*   Parameters inout        : Level: Pointer to var to record current isr level.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_SuspendISR2
(
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) Level
);

/****************************************************************************************************
*   Function Name           : OsIsr_ResumeISR
*   Service ID              : None.
*   Description             : Resume isr level.
*   Parameters in           : Level: Isr level to be restored.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_ResumeISR
(
    Os_IsrLevelType Level
);

/****************************************************************************************************
*   Function Name           : OsIsr_GetISRID
*   Service ID              : None.
*   Description             : Internal function of GetISR.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : ISRType: Isr id.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(ISRType, OS_CODE) OsIsr_GetISRID
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIsr_IsSuspendIsr
*   Service ID              : None.
*   Description             : Check if current object has suspended isr.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : boolean: TRUE: Has suspended. FALSE: No suspend.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsIsr_IsSuspendIsr
(
   void
);

/****************************************************************************************************
*   Function Name           : OsIsr_SaveAndIncreaseLevel
*   Service ID              : None.
*   Description             : Save current isr level and increase level to a specific value.
*   Parameters in           : NextLevel: Level to be set.
*   Parameters inout        : None.
*   Parameters out          : CurrentLevel: Pointer to var to store current isr level.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_SaveAndIncreaseLevel
(
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) CurrentLevel,
    Os_IsrLevelType NextLevel
);

/****************************************************************************************************
*   Function Name           : OsIsr_GetLockList
*   Service ID              : None.
*   Description             : Get lock FIFO of specific isr.
*   Parameters in           : ISRID: Isr id.
*   Parameters inout        : None.
*   Parameters out          : LockListPtr: Pointer to lock FIFO type var.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_GetLockList
(
    ISRType ISRID,
    P2P2VAR(Os_LockConfigRefType, TYPEDEF, OS_VAR) LockListPtr
);

/****************************************************************************************************
*   Function Name           : OsIsr_GetSpinLockList
*   Service ID              : None.
*   Description             : Get spinlock FIFO of specific isr.
*   Parameters in           : ISRID: Isr id.
*   Parameters inout        : None.
*   Parameters out          : SpinLockListPtr: Pointer to spinlock FIFO type var.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_GetSpinLockList
(
    ISRType ISRID,
    P2P2VAR(Os_SpinlockConfigRefType, TYPEDEF, OS_VAR) SpinLockListPtr
);

/****************************************************************************************************
*   Function Name           : OsIsr_GetCategory
*   Service ID              : None.
*   Description             : Get category of specific isr.
*   Parameters in           : ISRID: Isr id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : Os_InterruptType: OS_INTERRUPTTYPE_CAT1 or OS_INTERRUPTTYPE_CAT2.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_InterruptType, OS_CODE) OsIsr_GetCategory
(
    ISRType ISRID
);

/****************************************************************************************************
*   Function Name           : OsIsr_GetPriroity
*   Service ID              : None.
*   Description             : Get priority of specific isr.
*   Parameters in           : ISRID: Isr id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : uint32: Priority of isr.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) OsIsr_GetPriroity
(
    ISRType ISRID
);

/****************************************************************************************************
*   Function Name           : OsIsr_IsrDeInit
*   Service ID              : None.
*   Description             : Deinitialize specific isr.
*   Parameters in           : ISRID: Isr id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_IsrDeInit
(
    ISRType ISRID
);

/****************************************************************************************************
*   Function Name           : OsIsr_TriggerSoftwareInterrupt
*   Service ID              : None.
*   Description             : Trigger a software interrupt.
*   Parameters in           : IntId: Hardware id of software interrupt.
                              TargetCoreId: Core id which received this interrupt.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_TriggerSoftwareInterrupt
(
    uint32 IntId,
    uint32 TargetCoreId
);

/****************************************************************************************************
*   Function Name           : OsIsr_GetOwnerCoreId
*   Service ID              : None.
*   Description             : Get owner core id of specific isr.
*   Parameters in           : ISRID: Isr id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) OsIsr_GetOwnerCoreId
(
    ISRType ISRID
);

#endif /* OS_ISR_H_ */

/****************************************************************************************************
**     End of File: Os_isr.h                                                                      **
****************************************************************************************************/


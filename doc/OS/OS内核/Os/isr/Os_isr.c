/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_isr.c
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

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os.h"
#include "Os_isr.h"
#include "Os_isr_hal.h"
#include "Os_isr_Lcfg.h"
#include "Os_compiler_types.h"
#include "Os_task.h"
#include "Os_ioc.h"
#include "Os_application.h"
#include "Os_application_types.h"
#include "Os_timingprotection.h"
#include "Os_kernel.h"
#include "Os_lock.h"
#include "Os_hook.h"
#include "Os_context.h"
#include "Os_context_Lcfg.h"
#include "Os_ioc_Lcfg.h"
#include "compilertypes.h"
#include "Os_services.h"
#include "Os_orti.h"
#include "Os_ArtiHooks.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define OS_ISR_SUSPEND_ALL  (1U)
#define OS_ISR_SUSPEND_OS   (0U)
#define OS_ISR_RESUME_ALL   (1U)
#define OS_ISR_RESUME_OS    (0U)
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

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsIsr_Internal_EnableAllInterrupts
*   Service ID              : None.
*   Description             : Internal function of EnableAllInterrupts.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsIsr_Internal_EnableAllInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIsr_Internal_DisableAllInterrupts
*   Service ID              : None.
*   Description             : Internal function of DisableAllInterrupts.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsIsr_Internal_DisableAllInterrupts
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIsr_Internal_DisableInterruptSource
*   Service ID              : None.
*   Description             : Internal function of DisableInterruptSource.
*   Parameters in           : ISRID: Isr id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsIsr_Internal_DisableInterruptSource
(
    ISRType ISRID
);

/****************************************************************************************************
*   Function Name           : OsIsr_Internal_EnableInterruptSource
*   Service ID              : None.
*   Description             : Internal function of EnableInterruptSource.
*   Parameters in           : ISRID: Isr id.
                              ClearPending: If clear pending flag of specific isr.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsIsr_Internal_EnableInterruptSource
(
    ISRType ISRID,
    boolean ClearPending
);

/****************************************************************************************************
*   Function Name           : OsIsr_Internal_ClearPendingInterrupt
*   Service ID              : None.
*   Description             : Clear pending flag of specific isr.
*   Parameters in           : ISRID: Isr id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(StatusType, OS_CODE) OsIsr_Internal_ClearPendingInterrupt
(
    ISRType ISRID
);

/****************************************************************************************************
*   Function Name           : OsIsr_Internal_RecordSuspendIsr
*   Service ID              : None.
*   Description             : Record suspend os/all service order.
*   Parameters in           : SuspendType: OS_ISR_SUSPEND_ALL or OS_ISR_SUSPEND_OS
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsIsr_Internal_RecordSuspendIsr
(
    uint32 SuspendType
);

/****************************************************************************************************
*   Function Name           : OsIsr_Internal_OrderCheck
*   Service ID              : None.
*   Description             : Check suspend/resume order.
*   Parameters in           : ResumeType: OS_ISR_RESUME_ALL or OS_ISR_RESUME_OS.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : boolean: Result.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, OS_CODE) OsIsr_Internal_OrderCheck
(
    uint32 ResumeType
);

/****************************************************************************************************
*   Function Name           : OsIsr_Internal_GetServiceCallIsrSourceCore
*   Service ID              : None.
*   Description             : Get id of core which send cross-core service call isr.
*   Parameters in           : ISRID: Isr id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(CoreIdType, OS_CODE) OsIsr_Internal_GetServiceCallIsrSourceCore
(
    ISRType ISRID
);
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
static FUNC(void, OS_CODE) OsIsr_Internal_EnableAllInterrupts
(
    void
)
{
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetCurrent_ObjectInfo()->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    /* If DisableAllInterrupts wasn't called before */
    if(FALSE == IntApiCountPtr->IsrDisableAll)
    {
        /* Protection hook */
        OsHook_CallProtectionHook(E_OS_SYS_API_ERROR);
    }
    else
    {
        /* Reset DisableAll flag */
        IntApiCountPtr->IsrDisableAll = FALSE;
        /* [SWS_Os_00591] The OS service EnableAllInterrupts shall only affect the core on which it is called. */
        /* Resume isr level */
        OsIsr_Hal_SetLevel(IntApiCountPtr->PreviousIsr1Level);
        /* Stop TP record */
        OsTp_StopLockAllInterrupt();
        /* Inform trace */

    }
}

static FUNC(void, OS_CODE) OsIsr_Internal_DisableAllInterrupts
(
    void
)
{
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetCurrent_ObjectInfo()->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    /* DisableAllInterrupts/SuspendAllInterrupts/SuspendOsInterrupts can not be called before */
    if(TRUE == OsIsr_IsSuspendIsr())
    {
        /* Protection hook */
        OsHook_CallProtectionHook(E_OS_SYS_API_ERROR);
    }
    else
    {
        /* Start TP record */
        OsTp_StartLockAllInterrupt();
        /* [SWS_Os_00590] The OS service DisableAllInterrupts shall only affect the core on which it is called. */
        /* Save current isr level */
        OsIsr_Hal_GetLevel(&IntApiCountPtr->PreviousIsr1Level);
        /* Disable isr1/isr2 except tp */
        OsIsr_Hal_SetLevel(OS_ISR_CAT1_DISABLE_LEVEL);
        /* Inform trace */

        /* Set flag */
        IntApiCountPtr->IsrDisableAll = TRUE;
    }
}

static FUNC(StatusType, OS_CODE) OsIsr_Internal_DisableInterruptSource
(
    ISRType ISRID
)
{
    StatusType Status;
    uint32 IntID;
    CoreIdType CoreID;
    Os_IsrLevelType Level;

    IntID = Os_IsrConfigSet[ISRID]->IsrHwConfig.intID;
    CoreID = Os_IsrConfigSet[ISRID]->IsrHwConfig.coreID;
    if(OsService_ExtendedErrorCheck(ISRID >= OS_ISR_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    /* Check context */
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_DISABLEINTERRUPTSOURCE)))
    {
        Status = E_OS_CALLEVEL;
    }
    /* [SWS_Os_00808] This Api is only used for cat2 isr */
    else if(OsService_ExtendedErrorCheck(Os_IsrConfigSet[ISRID]->IntType != OS_INTERRUPTTYPE_CAT2))
    {
        Status = E_OS_SYS_API_ERROR;
    }
    /* [SWS_Os_91020] Check if calling app is the owner of isr */
    else if(OsService_ServiceProtectionErrorCheck(OsApp_GetCurrentApplicationID() == ((OsApp_GetCurrent_ObjectInfo()->AppObjIDInfo & APPLICATIONID_MASK) >> 16)))
    {
        Status = E_OS_ACCESS;
    }
    /* [SWS_Os_00809] If the isr is already disabled, return E_OS_NOFUNC */
    else if(OsService_ExtendedErrorCheck(FALSE == OsIsr_Hal_IsEnable(IntID, CoreID)))
    {
        Status = E_OS_NOFUNC;
    }
    else
    {
        Status = E_OK;
        /* [SWS_Os_00812] DisableInterruptSource shall disable the requested 
           interrupt source by modifying the interrupt controller registers. */
        OsIsr_Hal_DisableInterruptSource(IntID, CoreID);
    }

    /* [SWS_Os_00810] If the Operating System detects an error, the OS shall call the ErrorHook */
    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_DISABLEINTERRUPTSOURCE, (InputParaType)ISRID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    return Status;
}

static FUNC(StatusType, OS_CODE) OsIsr_Internal_EnableInterruptSource
(
    ISRType ISRID,
    boolean ClearPending
)
{
    StatusType Status;
    uint32 IntID;
    CoreIdType CoreID;
    Os_IsrLevelType Level;

    IntID = Os_IsrConfigSet[ISRID]->IsrHwConfig.intID;
    CoreID = Os_IsrConfigSet[ISRID]->IsrHwConfig.coreID;
    if(OsService_ExtendedErrorCheck(ISRID >= OS_ISR_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    /* Check context */
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_ENABLEINTERRUPTSOURCE)))
    {
        Status = E_OS_CALLEVEL;
    }
    /* [SWS_Os_00808] This Api is only used for cat2 isr */
    else if(OsService_ExtendedErrorCheck(Os_IsrConfigSet[ISRID]->IntType != OS_INTERRUPTTYPE_CAT2))
    {
        Status = E_OS_SYS_API_ERROR;
    }
    /* [SWS_Os_91020] Check if calling app is the owner of isr */
    else if(OsService_ServiceProtectionErrorCheck(OsApp_GetCurrentApplicationID() == ((OsApp_GetCurrent_ObjectInfo()->AppObjIDInfo & APPLICATIONID_MASK) >> 16)))
    {
        Status = E_OS_ACCESS;
    }
    /* [SWS_Os_00809] If the isr is already enabled, return E_OS_NOFUNC */
    else if(OsService_ExtendedErrorCheck(TRUE == OsIsr_Hal_IsEnable(IntID, CoreID)))
    {
        Status = E_OS_NOFUNC;
    }
    else
    {
        Status = E_OK;
        /* [SWS_Os_00811] EnableInterruptSource shall enable the requested interrupt
           source by modifying the interrupt controller registers. Additionally it shall clear
           the interrupt pending flag. */
        /* If need to clear pending flag */
        if(TRUE == ClearPending)
        {
            OsIsr_Hal_ClearPendingInterrupt(IntID, CoreID);
        }
        OsIsr_Hal_EnableInterruptSource(IntID, CoreID);
    }

    /* [SWS_Os_00810] If the Operating System detects an error, the OS shall call the ErrorHook */
    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_ENABLEINTERRUPTSOURCE,
                (InputParaType)ISRID,
                (InputParaType)((uint32)ClearPending));
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    return Status;
}

static FUNC(StatusType, OS_CODE) OsIsr_Internal_ClearPendingInterrupt
(
    ISRType ISRID
)
{
    StatusType Status;
    uint32 IntID;
    CoreIdType CoreID;
    Os_IsrLevelType Level;

    if(OsService_ExtendedErrorCheck(ISRID >= OS_ISR_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    /* Check context */
    else if(OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_CLEARPENDINGINTERRUPT)))
    {
        Status = E_OS_CALLEVEL;
    }
    /* [SWS_Os_00808] This Api is only used for cat2 isr */
    else if(OsService_ExtendedErrorCheck(Os_IsrConfigSet[ISRID]->IntType != OS_INTERRUPTTYPE_CAT2))
    {
        Status = E_OS_SYS_API_ERROR;
    }
    /* [SWS_Os_91020] Check if calling app is the owner of isr */
    else if(OsService_ServiceProtectionErrorCheck(OsApp_GetCurrentApplicationID() == ((OsApp_GetCurrent_ObjectInfo()->AppObjIDInfo & APPLICATIONID_MASK) >> 16)))
    {
        Status = E_OS_ACCESS;
    }
    else
    {
        Status = E_OK;
        IntID = Os_IsrConfigSet[ISRID]->IsrHwConfig.intID;
        CoreID = Os_IsrConfigSet[ISRID]->IsrHwConfig.coreID;
        /* [SWS_Os_00813][SWS_Os_00814] ClearPendingInterrupt shall clear the interrupt
           pending flag by modifying the respective interrupt controller registers. */
        OsIsr_Hal_ClearPendingInterrupt(IntID, CoreID);
    }

    if(E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterOne(OS_SERVICEID_CLEARPENDINGINTERRUPT, (InputParaType)ISRID);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    return Status;
}

static FUNC(void, OS_CODE) OsIsr_Internal_RecordSuspendIsr
(
    uint32 SuspendType
)
{
    uint32 SuspendCount;
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetCurrent_ObjectInfo()->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    SuspendCount = IntApiCountPtr->SuspendAllCount + IntApiCountPtr->SuspendOsCount;
    if(SuspendCount >= 32U)
    {
        /* Error */
        OsHook_CallProtectionHook(E_OS_SYS_API_ERROR);
    }
    else
    {
        if(SuspendType == OS_ISR_SUSPEND_ALL)
        {
            IntApiCountPtr->SuspendIsrBitArray |= (1U << SuspendCount);
        }
        else if(SuspendType == OS_ISR_SUSPEND_OS)
        {
            IntApiCountPtr->SuspendIsrBitArray &= ~(1U << SuspendCount);
        }
        else
        {
            /* Do nothing */
        }
    }
}

static FUNC(boolean, OS_CODE) OsIsr_Internal_OrderCheck
(
    uint32 ResumeType
)
{
    uint32 SuspendCount;
    boolean res;
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetCurrent_ObjectInfo()->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    SuspendCount = IntApiCountPtr->SuspendAllCount + IntApiCountPtr->SuspendOsCount;
    if(ResumeType == OS_ISR_RESUME_ALL)
    {
        res = ((IntApiCountPtr->SuspendIsrBitArray >> SuspendCount) & 1UL) == OS_ISR_SUSPEND_ALL;
    }
    else if(ResumeType == OS_ISR_RESUME_OS)
    {
        res = ((IntApiCountPtr->SuspendIsrBitArray >> SuspendCount) & 1UL) == OS_ISR_SUSPEND_OS;
    }
    else
    {
        res = FALSE;
    }
    return res;
}

static FUNC(CoreIdType, OS_CODE) OsIsr_Internal_GetServiceCallIsrSourceCore
(
    ISRType ISRID
)
{
    CoreIdType CurrentCoreId;
    uint32 IntId;

    CurrentCoreId = Os_Inf_CompilerGetCoreID();
    IntId = Os_IsrConfigSet[ISRID]->IsrHwConfig.intID;
    return CurrentCoreId > IntId ? IntId : (IntId + 1UL);
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(void, OS_CODE) EnableAllInterrupts
(
    void
)
{
    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(EnableAllInterrupts, 0U);
            OsIsr_Internal_EnableAllInterrupts();
            OS_ARTI_SC_END(EnableAllInterrupts, 0U);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(EnableAllInterrupts, 0U);
            OsIsr_Internal_EnableAllInterrupts();
            OS_ARTI_SC_END(EnableAllInterrupts, 0U);
        }
    }
}

FUNC(void, OS_CODE) DisableAllInterrupts
(
    void
)
{
    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(DisableAllInterrupts, 0U);
            OsIsr_Internal_DisableAllInterrupts();
            OS_ARTI_SC_END(DisableAllInterrupts, 0U);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(DisableAllInterrupts, 0U);
            OsIsr_Internal_DisableAllInterrupts();
            OS_ARTI_SC_END(DisableAllInterrupts, 0U);
        }
    }
}

FUNC(void, OS_CODE) ResumeAllInterrupts
(
    void
)
{
    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(ResumeAllInterrupts, 0U);
            OsIsr_ResumeAllInterrupts();
            OS_ARTI_SC_END(ResumeAllInterrupts, 0U);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(ResumeAllInterrupts, 0U);
            OsIsr_ResumeAllInterrupts();
            OS_ARTI_SC_END(ResumeAllInterrupts, 0U);
        }
    }
}

FUNC(void, OS_CODE) SuspendAllInterrupts
(
    void
)
{
    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(SuspendAllInterrupts, 0U);
            OsIsr_SuspendAllInterrupts();
            OS_ARTI_SC_END(SuspendAllInterrupts, 0U);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(SuspendAllInterrupts, 0U);
            OsIsr_SuspendAllInterrupts();
            OS_ARTI_SC_END(SuspendAllInterrupts, 0U);
        }
    }
}

FUNC(void, OS_CODE) ResumeOSInterrupts
(
    void
)
{
    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(ResumeOSInterrupts, 0U);
            OsIsr_ResumeOSInterrupts();
            OS_ARTI_SC_END(ResumeOSInterrupts, 0U);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(ResumeOSInterrupts, 0U);
            OsIsr_ResumeOSInterrupts();
            OS_ARTI_SC_END(ResumeOSInterrupts, 0U);
        }
    }
}

FUNC(void, OS_CODE) SuspendOSInterrupts
(
    void
)
{
    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(SuspendOSInterrupts, 0U);
            OsIsr_SuspendOSInterrupts();
            OS_ARTI_SC_END(SuspendOSInterrupts, 0U);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(SuspendOSInterrupts, 0U);
            OsIsr_SuspendOSInterrupts();
            OS_ARTI_SC_END(SuspendOSInterrupts, 0U);
        }
    }
}

FUNC(ISRType, OS_CODE) GetISRID
(
    void
)
{
    ISRType ISRID;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(GetISRID, 0U);
            ISRID = OsIsr_GetISRID();
            OS_ARTI_SC_END(GetISRID, ISRID);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(GetISRID, 0U);
            ISRID = OsIsr_GetISRID();
            OS_ARTI_SC_END(GetISRID, ISRID);
        }
    }
    return ISRID;
}

FUNC(StatusType, OS_CODE) DisableInterruptSource
(
    ISRType ISRID
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(DisableInterruptSource, ISRID);
            Status = OsIsr_Internal_DisableInterruptSource(ISRID);
            OS_ARTI_SC_END(DisableInterruptSource, Status);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(DisableInterruptSource, ISRID);
            Status = OsIsr_Internal_DisableInterruptSource(ISRID);
            OS_ARTI_SC_END(DisableInterruptSource, Status);
        }
    }

    return Status;
}

FUNC(StatusType, OS_CODE) EnableInterruptSource
(
    ISRType ISRID,
    boolean ClearPending
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(EnableInterruptSource, ISRID);
            Status = OsIsr_Internal_EnableInterruptSource(ISRID, ClearPending);
            OS_ARTI_SC_END(EnableInterruptSource, Status);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(EnableInterruptSource, ISRID);
            Status = OsIsr_Internal_EnableInterruptSource(ISRID, ClearPending);
            OS_ARTI_SC_END(EnableInterruptSource, Status);
        }
    }

    return Status;
}

FUNC(StatusType, OS_CODE) ClearPendingInterrupt
(
    ISRType ISRID
)
{
    StatusType Status;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(ClearPendingInterrupt, ISRID);
            Status = OsIsr_Internal_ClearPendingInterrupt(ISRID);
            OS_ARTI_SC_END(ClearPendingInterrupt, Status);
        }
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        {
            OS_ARTI_SC_DECL
            OS_ARTI_SC_BEGIN(ClearPendingInterrupt, ISRID);
            Status = OsIsr_Internal_ClearPendingInterrupt(ISRID);
            OS_ARTI_SC_END(ClearPendingInterrupt, Status);
        }
    }

    return Status;
}

FUNC(void, OS_CODE) OsIsr_ResumeAllInterrupts
(
    void
)
{
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetCurrent_ObjectInfo()->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    /* If SuspendAllInterrups wasn't called before */
    if(0U == IntApiCountPtr->SuspendAllCount)
    {
        /* Protection hook */
        OsHook_CallProtectionHook(E_OS_SYS_API_ERROR);
    }
    else
    {
        IntApiCountPtr->SuspendAllCount--;
        /* Check suspend/resume order */
        if(OsIsr_Internal_OrderCheck(OS_ISR_RESUME_ALL) == FALSE)
        {
            /* Error */
            OsHook_SetErrorParameterZero(OS_SERVICEID_RESUMEALLINTERRUPTS);
            OsHook_CallErrorHook(E_OS_SYS_API_ERROR);
        }
        else
        {
            /* If there is no nesting call */
            if(0U == IntApiCountPtr->SuspendAllCount)
            {
                /* [SWS_Os_00593] The OS service ResumeAllInterrupts shall only affect the
                   core on which it is called. */
                /* Resume isr level to previously saved value */
                OsIsr_Hal_SetLevel(IntApiCountPtr->PreviousIsr1Level);
                /* Stop TP record */
                OsTp_StopLockAllInterrupt();

                /* Inform trace */

            }
        }
    }
}

FUNC(void, OS_CODE) OsIsr_SuspendAllInterrupts
(
    void
)
{
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetCurrent_ObjectInfo()->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    /* DisableAllInterrupts cannot be called before */
    if(TRUE == IntApiCountPtr->IsrDisableAll)
    {
        /* Protection hook */
        OsHook_CallProtectionHook(E_OS_SYS_API_ERROR);
    }
    else
    {
        /* Call this funciton for the first time */
        if(0U == IntApiCountPtr->SuspendAllCount)
        {
            /* Start TP record */
            OsTp_StartLockAllInterrupt();
            /* Save current isr level */
            OsIsr_Hal_GetLevel(&IntApiCountPtr->PreviousIsr1Level);
            /* [SWS_Os_00592] The OS service SuspendAllInterrupts shall only affect the
               core on which it is called. */
            /* Disable isr1/isr2 except tp */
            OsIsr_Hal_SetLevel(OS_ISR_CAT1_DISABLE_LEVEL);
            /* Inform trace */

        }
        /* Record current SuspendAll operation */
        OsIsr_Internal_RecordSuspendIsr(OS_ISR_SUSPEND_ALL);
        /* Record the call */
        IntApiCountPtr->SuspendAllCount++;
    }
}

FUNC(void, OS_CODE) OsIsr_ResumeOSInterrupts
(
    void
)
{
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetCurrent_ObjectInfo()->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    /* SuspendOsInterrupts should be called before this function */
    if(0U == IntApiCountPtr->SuspendOsCount)
    {
        /* Protection hook */
        OsHook_CallProtectionHook(E_OS_SYS_API_ERROR);
    }
    else
    {
        IntApiCountPtr->SuspendOsCount--;
        /* Check suspend/resume order */
        if(OsIsr_Internal_OrderCheck(OS_ISR_RESUME_OS) == FALSE)
        {
            /* Error */
            OsHook_SetErrorParameterZero(OS_SERVICEID_RESUMEOSINTERRUPTS);
            OsHook_CallErrorHook(E_OS_SYS_API_ERROR);
        }
        else
        {
            /* If there is no nesting call */
            if(0U == IntApiCountPtr->SuspendOsCount)
            {
                /* [SWS_Os_00595] The OS service ResumeOSInterrupts shall only affect the core
                   on which it is called. */
                OsIsr_Hal_SetLevel(IntApiCountPtr->PreviousIsr2Level);
                /* Stop TP record */
                OsTp_StopLockOsInterrupt();

                /* Inform trace */

            }
        }
    }
}

FUNC(void, OS_CODE) OsIsr_SuspendOSInterrupts
(
    void
)
{
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetCurrent_ObjectInfo()->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    /* DisableAllInterrupts cannot be called before */
    if(TRUE == IntApiCountPtr->IsrDisableAll)
    {
        /* Protection hook */
        OsHook_CallProtectionHook(E_OS_SYS_API_ERROR);
    }
    else
    {
        /* Call this function for the first time */
        if(0U == IntApiCountPtr->SuspendOsCount)
        {
            /* Start TP record */
            OsTp_StartLockOsInterrupt();
            /* Save current isr level */
            OsIsr_Hal_GetLevel(&IntApiCountPtr->PreviousIsr2Level);
            /* [SWS_Os_00594] The OS service SuspendOSInterrupts shall only affect the
               core on which it is called. */
            /* Disable isr2 */
            OsIsr_Hal_SetLevel(OS_ISR_CAT2_DISABLE_LEVEL);
            /* Inform trace */

        }
        /* Record current SuspendOs operation */
        OsIsr_Internal_RecordSuspendIsr(OS_ISR_SUSPEND_OS);
        /* Record the call */
        IntApiCountPtr->SuspendOsCount++;
    }
}

FUNC(void, OS_CODE) OsIsr_InstallInterrupt
(
    ISRType IsrIndex
)
{
    OsIsr_Hal_InstallIsr(&(Os_IsrConfigSet[IsrIndex]->IsrHwConfig));
}

FUNC(void, OS_CODE) OsIsr_InterruptHandler
(
    uint32 NextIntID
)
{
    CoreIdType CoreID;
    Os_IsrConfigRefType NextIsr = NULL_PTR;

    CoreID = Os_Inf_CompilerGetCoreID();
    /* SGI/PPI */
    if(NextIntID < OS_ISR_MIN_SPI_ID)
    {
        NextIsr = Os_Cores_InternalIntVecTable[CoreID][NextIntID];
    }
    /* SPI */
    else if(NextIntID <= OS_ISR_MAX_SPI_ID)
    {
        NextIsr = Os_PeripheralIntVecTable[NextIntID - OS_ISR_MIN_SPI_ID];
    }
    else
    {
        /* Do nothing */
    }
    /* If there is no isr configured */
    if(NextIsr == NULL_PTR)
    {
        /* Enter undefined isr handler */
        OsIsr_UndefinedISR();
    }
    else
    {
        switch (NextIsr->IntType)
        {
            case OS_INTERRUPTTYPE_CAT1:
            {
                /* Go to isr handler directly */
                ((void(*)(void))NextIsr->InterruptHandlerAddress)();
                OsIsr_Hal_EndOfInterrupt(NextIntID, CoreID);
                break;
            }
            case OS_INTERRUPTTYPE_CAT2:
            {
                /* Go to pre-process function */
                OsIsr_PreISR(NextIsr);
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

FUNC(void, OS_CODE) OsIsr_UndefinedISR
(
    void
)
{
    OsHook_CallProtectionHook(E_OS_SYS_UNDEFINED_IRQ);
}

#if (OS_ARTI_TRACE_CAT2ISR == STD_ON)
/****************************************************************************************************
*   ARTI Cat2 ISR events (openspec add-arti-hook-tracing, design D5), interrupts suspended (NOSUSP).
*   The kernel does not see when the interrupt became pending: Activate is reported together with Start.
****************************************************************************************************/
static FUNC(void, OS_CODE) OsIsr_Internal_ArtiStart
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) InterruptedObject,
    ISRType IsrID
)
{
    CoreIdType ArtiCore;
    ISRType InterruptedIsr;

    ArtiCore = Os_Inf_GetCoreId();
    if(OBJECT_ISR == InterruptedObject->ObjectType)
    {
        /* Nested ISR2: the interrupted ISR2 is preempted (an interrupted task keeps its state) */
        InterruptedIsr = InterruptedObject->AppObjIDInfo & OBJECTID_MASK;
        Os_IsrConfigSet[InterruptedIsr]->IsrRunningData->ArtiState = OS_ARTI_ISR_PREEMPTED;
        OS_ARTI_ISR2_PREEMPT(ArtiCore, InterruptedIsr);
    }
    Os_IsrConfigSet[IsrID]->IsrRunningData->ArtiState = OS_ARTI_ISR_RUNNING;
    OS_ARTI_ISR2_ACTIVATE(ArtiCore, IsrID);
    OS_ARTI_ISR2_START(ArtiCore, IsrID);
}

/* Before the rescheduling of the ISR exit, so that Stop precedes the task events it causes */
static FUNC(void, OS_CODE) OsIsr_Internal_ArtiStop
(
    ISRType IsrID,
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) InterruptedObject
)
{
    CoreIdType ArtiCore;
    ISRType InterruptedIsr;

    ArtiCore = Os_Inf_GetCoreId();
    Os_IsrConfigSet[IsrID]->IsrRunningData->ArtiState = OS_ARTI_ISR_INACTIVE;
    OS_ARTI_ISR2_STOP(ArtiCore, IsrID);
    if(OBJECT_ISR == InterruptedObject->ObjectType)
    {
        InterruptedIsr = InterruptedObject->AppObjIDInfo & OBJECTID_MASK;
        Os_IsrConfigSet[InterruptedIsr]->IsrRunningData->ArtiState = OS_ARTI_ISR_RUNNING;
        OS_ARTI_ISR2_RESUME(ArtiCore, InterruptedIsr);
    }
}
#endif

FUNC(void, OS_CODE) OsIsr_PreISR
(
    Os_IsrConfigRefType NextIsr
)
{
    Os_IsrLevelType SuspendLevel;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) NextObject;
    P2VAR(Os_Hal_ServiceContextFrame, AUTOMATIC, OS_VAR) NextServiceContext;
    P2CONST(Os_IocInterCoreServiceChannelCfgType, AUTOMATIC, OS_CONST) ServiceChannelCfg;
    uint32 TargetCoreId;

    /* Suspend interrupt and save current interrupt level */
    OsIsr_SuspendISR(&SuspendLevel);

    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    NextObject = OsApp_GetSpecific_ObjectInfo(NextIsr->ObjectID);

    /* If TP check is passed */
    if(OsTp_PassTimeFrameCheck((*(NextObject->ObjectDataInfo.ObjectContextInfoPtr))->TpInfoPtr))
    {
        /* Task was interrupted */
        if(OBJECT_TASK == CurrentObject->ObjectType)
        {
            OsTask_LeaveTaskLevel();
        }
        OsOrti_ChangeIsr(NextObject->AppObjIDInfo & OBJECTID_MASK);
#if (OS_ARTI_TRACE_CAT2ISR == STD_ON)
        OsIsr_Internal_ArtiStart(CurrentObject, NextIsr->ISRID);
#endif
        /* Set CurrentObject to next ISR */
        OsApp_ChangeCurrent_AppInfo(NextIsr->ObjectID);
        /* If is cross core service call isr */
        if(NextIsr->isCrossCore)
        {
            TargetCoreId = NextIsr->IsrHwConfig.coreID;
            ServiceChannelCfg = OsIoc_GetIocServiceChannelCfgPtr(OsIsr_Internal_GetServiceCallIsrSourceCore(NextIsr->ISRID), TargetCoreId);
            /* Get service context from FIFO */
            NextServiceContext = &ServiceChannelCfg->ServiceContextBuffer[ServiceChannelCfg->RunningData->ReadIndex];
            Os_Hal_ServiceContextInit(*(NextObject->ObjectDataInfo.ObjectContextInfoPtr), NextServiceContext);
            Os_Hal_ServiceContextSwitch(NextObject, CurrentObject, NextServiceContext);
        }
        else
        {
            /* Config context of next ISR */
            Os_Hal_ContextInit(*(NextObject->ObjectDataInfo.ObjectContextInfoPtr),
                    (*(NextObject->ObjectDataInfo.ObjectContextInfoPtr))->ContextInfoPtr);
            /* Switch context */
            Os_Hal_ContextSwitch(NextObject, CurrentObject, SAVING_CONTEXT);
        }
    }
    else
    {
        /* End the interrupt and do not handle it */
        OsIsr_Hal_EndOfInterrupt(NextIsr->IsrHwConfig.intID, NextIsr->IsrHwConfig.coreID);
    }
    /* Resume interrupt level of context to previously saved value */
    OsIsr_ResumeISR(SuspendLevel);
}

FUNC(void, OS_CODE) OsIsr_PostISR
(
    void
)
{
    ISRType CurrentISRID;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) PreviousObject;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    StatusType ErrorStatus;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
    }

    /* Suspend interrupt */
    OsIsr_Hal_SetLevel(OS_ISR_TP_DISABLE_LEVEL);

    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    CurrentISRID = CurrentObject->AppObjIDInfo & OBJECTID_MASK;

    ErrorStatus = E_OK;

    /* [SWS_Os_00369] ISR resource/lock check: release what the ISR still holds */
    if(Os_IsrConfigSet[CurrentISRID]->IsrRunningData->LockList != NULL_PTR)
    {
        /* The kind of the last lock taken decides the error; ClearLockList empties the list, so ask first */
        if(Os_IsrConfigSet[CurrentISRID]->IsrRunningData->LockList->LockType == OS_LOCKTYPE_RESOURCE)
        {
            ErrorStatus = E_OS_RESOURCE;
        }
        else
        {
            ErrorStatus = E_OS_SPINLOCK;
        }
        OsLock_ClearLockList(&Os_IsrConfigSet[CurrentISRID]->IsrRunningData->LockList);
    }
    /* [SWS_Os_00368] Interrupt lock check */
    else if(OsIsr_IsSuspendIsr())
    {
        OsIsr_ResumeISR(Os_IsrConfigSet[CurrentISRID]->IsrHwConfig.priority);
        OsIsr_ResetIntApiCount(CurrentObject->ObjectIDIndex);
        ErrorStatus = E_OS_DISABLEDINT;
    }
    else
    {
        /* Nothing to repair */
    }

    if(E_OK != ErrorStatus)
    {
        OsHook_SetErrorParameterZero(OS_SERVICEID_POSTISR);
        OsHook_CallErrorHook(ErrorStatus);
        /* Back from the hook, the ISR runs with the interrupt level it had when it left for the hook
           (lowered to the ISR priority after an interrupt lock error): suspend again, then end the ISR */
        OsIsr_Hal_SetLevel(OS_ISR_TP_DISABLE_LEVEL);
    }

    /* End the ISR: normally, and after the error handling above */
    {
        /* End current interrupt */
        OsIsr_Hal_EndOfInterrupt(Os_IsrConfigSet[CurrentISRID]->IsrHwConfig.intID, Os_IsrConfigSet[CurrentISRID]->IsrHwConfig.coreID);

        OsOrti_ChangeIsr(INVALID_ISR);
        /* Get interrupted object structure */
        PreviousObject = OsApp_GetPrevious_ObjectInfo();
#if (OS_ARTI_TRACE_CAT2ISR == STD_ON)
        OsIsr_Internal_ArtiStop(CurrentISRID, PreviousObject);
#endif
        /* If interrupted object is task */
        if(PreviousObject->ObjectType == OBJECT_TASK)
        {
            /* Reschedule */
            OsTask_DoScheduling(NOT_SAVING_CONTEXT);
        }
        /* Resume ISR2/HOOK */
        else
        {
            OsOrti_ChangeIsr(PreviousObject->AppObjIDInfo & OBJECTID_MASK);
            /* Set current object to interrupted object */
            OsApp_ChangeCurrent_AppInfo(PreviousObject->ObjectIDIndex);
            /* Switch context to interrupted object */
            Os_Hal_ContextSwitch(PreviousObject, CurrentObject, NOT_SAVING_CONTEXT);
        }
    }
}

FUNC(void, OS_CODE) OsIsr_PostServiceCallISR
(
    void
)
{
    ISRType CurrentISRID;
    uint32 Status;
    uint32 CurrentCoreId;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) PreviousObject;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObject;
    P2VAR(Os_Hal_ServiceContextFrame, AUTOMATIC, OS_VAR) NextServiceContext;
    P2CONST(Os_IocInterCoreServiceChannelCfgType, AUTOMATIC, OS_CONST) ServiceChannelCfg;

    /* Read return value from register R0 */
    Os_Inf_GetFunctionReturnValue(Status);

    /* Suspend interrupt */
    OsIsr_Hal_SetLevel(OS_ISR_TP_DISABLE_LEVEL);

    /* Get current isr info */
    CurrentObject = OsApp_GetCurrent_ObjectInfo();
    CurrentISRID = CurrentObject->AppObjIDInfo & OBJECTID_MASK;
    CurrentCoreId = Os_IsrConfigSet[CurrentISRID]->IsrHwConfig.coreID;

    ServiceChannelCfg = OsIoc_GetIocServiceChannelCfgPtr(OsIsr_Internal_GetServiceCallIsrSourceCore(CurrentISRID), CurrentCoreId);
    /* Record return value of service */
    ServiceChannelCfg->ServiceContextBuffer[ServiceChannelCfg->RunningData->ReadIndex].ReturnVal = Status;
    Os_Inf_Dsync();
    /* Index increment */
    ServiceChannelCfg->RunningData->ReadIndex = (ServiceChannelCfg->RunningData->ReadIndex + 1) % ServiceChannelCfg->BufferLength;

    /* If there is no unhandled service in FIFO */
    if(ServiceChannelCfg->RunningData->WriteIndex == ServiceChannelCfg->RunningData->ReadIndex)
    {
        /* End current interrupt */
        OsIsr_Hal_EndOfInterrupt(Os_IsrConfigSet[CurrentISRID]->IsrHwConfig.intID, Os_IsrConfigSet[CurrentISRID]->IsrHwConfig.coreID);
        /* Get interrupted object structure */
        PreviousObject = OsApp_GetPrevious_ObjectInfo();
#if (OS_ARTI_TRACE_CAT2ISR == STD_ON)
        /* Last queued service handled: the service ISR2 ends */
        OsIsr_Internal_ArtiStop(CurrentISRID, PreviousObject);
#endif

        /* If interrupted object is task */
        if(PreviousObject->ObjectType == OBJECT_TASK)
        {
            OsOrti_ChangeIsr(INVALID_ISR);
            /* Reschedule */
            OsTask_DoScheduling(NOT_SAVING_CONTEXT);
        }
        /* Resume ISR2/HOOK */
        else
        {
            OsOrti_ChangeIsr(PreviousObject->AppObjIDInfo & OBJECTID_MASK);
            /* Set current object to interrupted object */
            OsApp_ChangeCurrent_AppInfo(PreviousObject->ObjectIDIndex);
            /* Switch context to interrupted object */
            Os_Hal_ContextSwitch(PreviousObject, CurrentObject, NOT_SAVING_CONTEXT);
        }
    }
    /* If there is new service to be handled */
    else
    {
        /* Clear pending of this isr */
        OsIsr_Hal_ClearPendingInterrupt(Os_IsrConfigSet[CurrentISRID]->IsrHwConfig.intID, CurrentCoreId);
        /* Get context of next service */
        NextServiceContext = &ServiceChannelCfg->ServiceContextBuffer[ServiceChannelCfg->RunningData->ReadIndex];
        Os_Hal_ServiceContextInit(*(CurrentObject->ObjectDataInfo.ObjectContextInfoPtr), NextServiceContext);
        Os_Hal_ServiceContextSwitch_Asm(NextServiceContext, NULL_PTR);
    }
}

FUNC(void, OS_CODE) OsIsr_IsrInit
(
    uint32 IsrCount
)
{
    if(Os_IsrConfigSet[IsrCount]->IntType == OS_INTERRUPTTYPE_CAT2)
    {
        /* Initialize members of isrDyn */
        Os_IsrConfigSet[IsrCount]->IsrRunningData->LockList = NULL_PTR;
        Os_IsrConfigSet[IsrCount]->IsrRunningData->SpinlockOccupied = NULL_PTR;
    }
}

FUNC(void, OS_CODE) OsIsr_ResetIntApiCount
(
    uint32 ObjectId
)
{
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetSpecific_ObjectInfo(ObjectId)->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    IntApiCountPtr->IsrDisableAll = FALSE;
    IntApiCountPtr->SuspendAllCount = 0UL;
    IntApiCountPtr->SuspendOsCount = 0UL;
    IntApiCountPtr->PreviousIsr1Level = 0UL;
    IntApiCountPtr->PreviousIsr2Level = 0UL;
    IntApiCountPtr->SuspendIsrBitArray = 0UL;
}

FUNC(void, OS_CODE) OsIsr_SuspendISR
(
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) Level
)
{
    /* Get current interrupt level */
    OsIsr_Hal_GetLevel(Level);
    /* Disable interrupt upto tp isr */
    OsIsr_Hal_SetLevel(OS_ISR_TP_DISABLE_LEVEL);
}

FUNC(void, OS_CODE) OsIsr_SuspendISR2
(
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) Level
)
{
    /* Get current interrupt level */
    OsIsr_Hal_GetLevel(Level);
    /* Disable interrupt upto tp isr */
    OsIsr_Hal_SetLevel(OS_ISR_CAT2_DISABLE_LEVEL);
}

FUNC(void, OS_CODE) OsIsr_ResumeISR
(
    Os_IsrLevelType Level
)
{
    OsIsr_Hal_SetLevel(Level);
}

FUNC(ISRType, OS_CODE) OsIsr_GetISRID
(
    void
)
{
    ISRType ISRID;
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) PreviousObject;

    /* [SWS_Os_00264] If its caller is not a category 2 ISR (or Hook routines called inside
       a category 2 ISR), GetISRID shall return INVALID_ISR. */
    ISRID = INVALID_ISR;
    if(OsKernel_GetCurrentRunningContext() & OS_CALL_GETISRID)
    {
        /* [SWS_Os_00263] If called from category 2 ISR (or Hook routines called inside a
           category 2 ISR), GetISRID shall return the identifier of the currently executing ISR. */
        if(OsApp_GetCurrent_ObjectInfo()->ObjectType == OBJECT_ISR)
        {
            ISRID = OsApp_GetCurrent_ObjectInfo()->AppObjIDInfo & OBJECTID_MASK;
        }
        else if((OsApp_GetCurrent_ObjectInfo()->ObjectType == OBJECT_APPHOOK) ||
                (OsApp_GetCurrent_ObjectInfo()->ObjectType == OBJECT_KERNELHOOK))
        {
            PreviousObject = *(OsApp_GetCurrent_ObjectInfo()->PreviousObjectInfoRef);
            while((PreviousObject->ObjectType != OBJECT_TASK) && (PreviousObject->ObjectType != OBJECT_ISR))
            {
                PreviousObject = *PreviousObject->PreviousObjectInfoRef;
            }
            if(PreviousObject->ObjectType == OBJECT_ISR)
            {
                ISRID = PreviousObject->AppObjIDInfo & OBJECTID_MASK;
            }
        }
        else
        {
            /* Do nothing */
        }
    }

    return ISRID;
}

FUNC(boolean, OS_CODE) OsIsr_IsSuspendIsr
(
   void
)
{
    P2VAR(Os_IsrRunningDataType, TYPEDEF, OS_VAR) IntApiCountPtr;

    IntApiCountPtr = &(*OsApp_GetCurrent_ObjectInfo()->ObjectDataInfo.ObjectContextInfoPtr)->ContextRunningDataPtr->IsrRunningData;
    return (IntApiCountPtr->IsrDisableAll | IntApiCountPtr->SuspendAllCount | IntApiCountPtr->SuspendOsCount) != 0;
}

FUNC(void, OS_CODE) OsIsr_SaveAndIncreaseLevel
(
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) CurrentLevel,
    Os_IsrLevelType NextLevel
)
{
    OsIsr_Hal_GetLevel(CurrentLevel);
    OsIsr_Hal_SetLevel(NextLevel);
}

FUNC(void, OS_CODE) OsIsr_GetLockList
(
    ISRType ISRID,
    P2P2VAR(Os_LockConfigRefType, TYPEDEF, OS_VAR) LockListPtr
)
{
    *LockListPtr = &Os_IsrConfigSet[ISRID]->IsrRunningData->LockList;
}

FUNC(void, OS_CODE) OsIsr_GetSpinLockList
(
    ISRType ISRID,
    P2P2VAR(Os_SpinlockConfigRefType, TYPEDEF, OS_VAR) SpinLockListPtr
)
{
    *SpinLockListPtr = &Os_IsrConfigSet[ISRID]->IsrRunningData->SpinlockOccupied;
}

FUNC(Os_InterruptType, OS_CODE) OsIsr_GetCategory
(
    ISRType ISRID
)
{
    return Os_IsrConfigSet[ISRID]->IntType;
}

FUNC(uint32, OS_CODE) OsIsr_GetPriroity
(
    ISRType ISRID
)
{
    return Os_IsrConfigSet[ISRID]->IsrHwConfig.priority;
}

FUNC(void, OS_CODE) OsIsr_IsrDeInit
(
    ISRType ISRID
)
{
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) ObjectInfo;

    ObjectInfo = OsApp_GetSpecific_ObjectInfo(Os_IsrConfigSet[ISRID]->ObjectID);
    OsIsr_Hal_DisableInterruptSource(Os_IsrConfigSet[ISRID]->IsrHwConfig.intID, Os_IsrConfigSet[ISRID]->IsrHwConfig.coreID);
    if(Os_IsrConfigSet[ISRID]->IntType == OS_INTERRUPTTYPE_CAT2)
    {
        OsLock_ClearLockList(&Os_IsrConfigSet[ISRID]->IsrRunningData->LockList);
        OsIoc_ClearSyncServiceCallFlag(Os_IsrConfigSet[ISRID]->ObjectID);
        OsIsr_ResetIntApiCount(Os_IsrConfigSet[ISRID]->ObjectID);
        /* Tp reset */
        OsTp_KillObject((*ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr)->TpInfoPtr);
        if(Os_IsrConfigSet[ISRID]->ObjectID != OsApp_GetCurrent_ObjectID())
        {
            /* Set context pc to return address */
            Os_Hal_ContextAbort(*ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr,
                                (*ObjectInfo->ObjectDataInfo.ObjectContextInfoPtr)->ContextInfoPtr);
        }
    }
}

FUNC(void, OS_CODE) OsIsr_TriggerSoftwareInterrupt
(
    uint32 IntId,
    uint32 TargetCoreId
)
{
    OsIsr_Hal_TriggerSoftwareInterrupt(IntId, TargetCoreId);
}

FUNC(uint32, OS_CODE) OsIsr_GetOwnerCoreId
(
    ISRType ISRID
)
{
    return Os_IsrConfigSet[ISRID]->IsrHwConfig.coreID;
}

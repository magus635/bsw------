/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_context.c
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
#include "Os_context.h"
#include "Os_context_Cfg.h"
#include "Os_context_Lcfg.h"
#include "Os_compiler_types.h"
#include "Os_mpu.h"
#include "Os_mpu_Cfg.h"
#include "Os_timingprotection.h"
#include "Os_kernel_Cfg.h"
#include "Os_hook.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

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
 *   Function Name           : OsContext_Internal_ContextInit
 *   Service ID              : None.
 *   Description             : Initialize the Context .
 *   Parameters in           : Config: The content data of the context
 *   Parameters inout        : Context: The register list for context
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : None.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, OS_CODE) OsContext_Internal_ContextInit
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context
);

/****************************************************************************************************
 *   Function Name           : OsContext_Internal_ContextAbort
 *   Service ID              : None.
 *   Description             : Get the abort Context .
 *   Parameters in           : Config: The content data of the context
 *                           : Context: The register list for context
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : None.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/

static FUNC(void, OS_CODE) OsContext_Internal_ContextAbort
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context
);

/****************************************************************************************************
 *   Function Name           : OsContext_StackOverflowCheck
 *   Service ID              : None.
 *   Description             : Initialize the Context .
 *   Parameters in           : StackTopPtr: The pointer to the stack top
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : None.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/

static FUNC(void, OS_CODE) OsContext_StackOverflowCheck
(
    P2VAR(uint32, AUTOMATIC, OS_VAR_NOINIT) StackTopPtr
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
static FUNC(void, OS_CODE) OsContext_Internal_ContextInit
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context
)
{
    Context->Spsr     = Config->ProgramSetting;
    Context->Icc_pmr  = Config->InterruptSetting;
    Context->Sp_usr   = Config->StackBottomAddr;
    Context->Lr_usr   = Config->ReturnFunction;
    Context->Lr       = (uint32)(&Os_Hal_StartNewThread);            /* Use Macro */
    Context->R0       = 0;
    Context->R4       = Config->EntryFunction;
    Context->R5       = Config->ReturnFunction;
    Context->R6       = 0;
    Context->R7       = 0;
    Context->R8       = 0;
    Context->R9       = 0;
    Context->R10      = 0;
}

static FUNC(void, OS_CODE) OsContext_Internal_ContextAbort(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context)
{

    Context->Spsr = Config->ProgramSetting;
    /*Context->Icc_pmr  = Config->InterruptSetting;*/
    Context->Sp_usr = Config->StackBottomAddr;
    Context->Lr_usr = Config->ReturnFunction;
    Context->Lr = (uint32)(&Os_Hal_StartNewThread); /* Use Macro */
    Context->R0 = 0;
    Context->R4 = Config->ReturnFunction;
    Context->R5 = Config->ReturnFunction;
    Context->R6 = 0;
    Context->R7 = 0;
    Context->R8 = 0;
    Context->R9 = 0;
    Context->R10 = 0;
    /*Get Current PMR Value.*/
    Os_Inf_GetCP(15, 0, Context->Icc_pmr, 4, 6, 0);
}

static FUNC(void, OS_CODE) OsContext_StackOverflowCheck(
    P2VAR(uint32, AUTOMATIC, OS_VAR_NOINIT) StackTopPtr)
{
    if (NULL_PTR == StackTopPtr)
    {
        OsHook_CallProtectionHook(E_OS_STACKFAULT);
    }
    else
    {
        if (*StackTopPtr != OS_CONTEXT_STACK_MONITORING_FILL_PATTERN)
        {
            OsHook_CallProtectionHook(E_OS_STACKFAULT);
        }
    }
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(void, OS_CODE)
OsContext_InitMemory(
    uint32 ContextID)
{
#if (OS_CONTEXT_STACK_MONITORING == STD_ON)
    P2VAR(uint32, AUTOMATIC, OS_VAR_NOINIT)
    StackTopPtr;

    StackTopPtr = (uint32*)Os_ContextConfigSet.ContextConfigPtr[ContextID]->StackTopAddr;
    *StackTopPtr = (uint32)OS_CONTEXT_STACK_MONITORING_FILL_PATTERN;

#endif
    OsContext_Internal_ContextInit(Os_ContextConfigSet.ContextConfigPtr[ContextID],
                                   Os_ContextConfigSet.ContextConfigPtr[ContextID]->ContextInfoPtr);
    Os_ContextConfigSet.ContextConfigPtr[ContextID]->ContextRunningDataPtr->IsrRunningData.IsrDisableAll = FALSE;
    Os_ContextConfigSet.ContextConfigPtr[ContextID]->ContextRunningDataPtr->IsrRunningData.SuspendAllCount = 0UL;
    Os_ContextConfigSet.ContextConfigPtr[ContextID]->ContextRunningDataPtr->IsrRunningData.SuspendOsCount = 0UL;
    Os_ContextConfigSet.ContextConfigPtr[ContextID]->ContextRunningDataPtr->IsrRunningData.SuspendIsrBitArray = 0UL;
    Os_ContextConfigSet.ContextConfigPtr[ContextID]->ContextRunningDataPtr->IsrRunningData.PreviousIsr1Level = 0UL;
    Os_ContextConfigSet.ContextConfigPtr[ContextID]->ContextRunningDataPtr->IsrRunningData.PreviousIsr2Level = 0UL;
}

FUNC(void, OS_CODE)Os_Hal_ContextSwitch
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) NextObjInfo,
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObjInfo,
    Os_SchedulingChoiceType Choice
)
{
    uint32 CpsrValue;
    P2CONST(Os_ContextType, TYPEDEF, OS_CONST)
    NextContext;
    P2CONST(Os_ContextType, TYPEDEF, OS_CONST)
    CurrentContext;
    P2VAR(Os_Hal_ContextFrame, TYPEDEF, OS_VAR)
    CurrentTaskInfo;
#if (OS_CONTEXT_STACK_MONITORING == STD_ON)
    P2VAR(uint32, AUTOMATIC, OS_VAR_NOINIT)
    StackTopPtr;
#endif

    CurrentTaskInfo = NULL_PTR;
    NextContext = *(NextObjInfo->ObjectDataInfo.ObjectContextInfoPtr);
    CurrentContext = *(CurrentObjInfo->ObjectDataInfo.ObjectContextInfoPtr);

#if (OS_CONTEXT_STACK_MONITORING == STD_ON)
    StackTopPtr = (uint32 *)(CurrentContext->StackTopAddr);
    OsContext_StackOverflowCheck(StackTopPtr);
#endif

    CpsrValue = Os_Inf_GetCPSR_AndDisableIRQ();
    /* TP only used for Task/ISR2 Object. */
    if (((OBJECT_TASK == NextObjInfo->ObjectType) || (OBJECT_ISR == NextObjInfo->ObjectType)) && ((OBJECT_TASK == CurrentObjInfo->ObjectType) || (OBJECT_ISR == CurrentObjInfo->ObjectType)))
    {
        if (SAVING_CONTEXT == Choice)
        {
            OsTp_Switch(CurrentContext->TpInfoPtr, NextContext->TpInfoPtr);
        }
        else
        {
            OsTp_ResetAndResume(CurrentContext->TpInfoPtr, NextContext->TpInfoPtr);
        }
    }

    if(SAVING_CONTEXT == Choice)
    {
        CurrentTaskInfo = CurrentContext->ContextInfoPtr;
    }

#ifdef OS_KERNEL_SUPPORT_SC3
    OsMpu_SwitchStack(NextContext);
    Os_Hal_ContextMpuSwitch_Asm(NextContext->ContextInfoPtr, CurrentTaskInfo);
#else
    Os_Hal_ContextSwitch_Asm(NextContext->ContextInfoPtr, CurrentTaskInfo);
#endif

    Os_Inf_RestoreCPSR(CpsrValue);
}

FUNC(void, OS_CODE) Os_Hal_ContextInit
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context
)
{
    OsContext_Internal_ContextInit(Config, Context);
}

FUNC(void, OS_CODE) Os_Hal_ContextAbort
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context
)
{
    OsContext_Internal_ContextAbort(Config, Context);
}

FUNC(void, OS_CODE) Os_Hal_ContextSetParam
(
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context,
    P2VAR(void, AUTOMATIC, OS_INTERNAL_VAR) Parameter
)
{
    Context->R0 = (uint32)Parameter;
}

FUNC(void, OS_CODE) Os_Hal_ServiceContextInit
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ServiceContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context
)
{
    Context->Spsr     = Config->ProgramSetting;
    Context->Icc_pmr  = Config->InterruptSetting;
    Context->Sp_usr   = Config->StackBottomAddr;
    Context->Lr_usr   = Config->ReturnFunction;
    Context->Lr       = (uint32)(&Os_Hal_StartNewThread);            /* Use Macro */
    Context->R5       = Config->ReturnFunction;
}

FUNC(void, OS_CODE) Os_Hal_ServiceContextSwitch
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) NextObjInfo,
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObjInfo,
    P2VAR(Os_Hal_ServiceContextFrame, AUTOMATIC, OS_INTERNAL_VAR) NextServiceContext
)
{
    uint32 CpsrValue;
    P2CONST(Os_ContextType, TYPEDEF, OS_CONST) NextContext;
    P2CONST(Os_ContextType, TYPEDEF, OS_CONST) CurrentContext;

    NextContext = *(NextObjInfo->ObjectDataInfo.ObjectContextInfoPtr);
    CurrentContext = *(CurrentObjInfo->ObjectDataInfo.ObjectContextInfoPtr);

    CpsrValue = Os_Inf_GetCPSR_AndDisableIRQ();
    OsTp_Switch(CurrentContext->TpInfoPtr, NextContext->TpInfoPtr);
    OsMpu_SwitchStack(NextContext);

    Os_Hal_ServiceContextSwitch_Asm(NextServiceContext, CurrentContext->ContextInfoPtr);
    Os_Inf_RestoreCPSR(CpsrValue);
}

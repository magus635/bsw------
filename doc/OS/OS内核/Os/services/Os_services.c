/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_services.c
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
#include "Os_services_Cfg.h"
#include "Os_services_Lcfg.h"
#include "Os_kernel.h"
#include "Os_services_types.h"
#include "Os_services.h"
#include "Os_application.h"
#include "Os_isr.h"
#include "Os_hook.h"
#include "Os_mpu.h"
#include "Os_timingprotection.h"
#include "Os_orti.h"
#include "Os_ArtiHooks.h"
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
**                          Private Constant Definitions                                           **
****************************************************************************************************/

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
 *   Function Name           : OsService_Internal_CallTrustedFunction
 *   Service ID              : None.
 *   Description             : A (trusted or non-trusted) OS-Application uses this service to call a trusted function.
 *   Parameters in           : FunctionIndex: Index of the function to be called
 *                              FunctionParams:Pointer to the parameters for the function
 *   Parameters inout        : None.
 *   Parameters out          : None.
 *   Sync/Async              : Synchronous.
 *   Reentrancy              : Non-Reentrant.
 *   Return value            : None.
 *   Preconditions           : None.
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/

static FUNC(StatusType, OS_CODE) OsService_Internal_CallTrustedFunction
(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
)
{
    StatusType Status;
    Os_IsrLevelType Level;
    P2CONST(OsServices_TFConfigType, AUTOMATIC, OS_CONST) ServiceTF;
    ApplicationType CallerAppId;
    boolean hasTpDelay;
    CoreIdType LocalCoreID;
    CoreIdType DestCoreID;
    ApplicationType TrustAppID;
    ApplicationStateType State;
    uint32 TaskCurPriority;

    OS_ARTI_SC_DECL
    OsOrti_ServiceStart(OS_SERVICEID_CALLTRUSTEDFUNCTION);
    OS_ARTI_SC_BEGIN(CallTrustedFunction, FunctionIndex);

    /*Check the parameter out of the range*/
    if (OsService_ExtendedErrorCheck(FunctionIndex >= OS_SERVICE_FUNC_TOTAL_NUM))
    {
        Status = E_OS_ID;
    }
    else if (OsService_ExtendedErrorCheck(!(OsKernel_GetCurrentRunningContext() & OS_CALL_CALLTRUSTEDFUNCTION)))
    {
        Status = E_OS_CALLEVEL;
    }
    else
    {
        /*Get the Trusted Function content */
        ServiceTF = OsServices_TrustedFunctionRefs[FunctionIndex].OsServices_TF;
        if(NULL_PTR == ServiceTF)
        {
            Status = E_OS_ID;
        }
        else
        {
            State = APPLICATION_TERMINATED;
            TrustAppID = ServiceTF->ApplicationID;
            DestCoreID = OsApp_GetOwnerCoreID(TrustAppID);
            LocalCoreID = Os_Inf_GetCoreId();
            OsApp_GetApplicationState(TrustAppID,&State) ;

            if(OsService_ExtendedErrorCheck(State != APPLICATION_ACCESSIBLE ))
            {
                Status = E_OS_ACCESS;
            }
            else if(OsService_ExtendedErrorCheck(DestCoreID != LocalCoreID))
            {
                Status = E_OS_ACCESS;
            }
            else
            {
                /*Suspend the interrupt*/
                OsIsr_SuspendISR(&Level);

                /*[SWS_Os_00563] increase the task priority */
                OsTask_LevelUpTaskPriority(0xFFFFFFFFUL, &TaskCurPriority);

                CallerAppId = OsKernel_GetCurrentCoreAppDataInfo()->Current_ApplicationID;
                hasTpDelay = OsApp_GetCurrentAppTpDelay();

                /*[SWS_Os_00797] Change the current Application ID to Trusted Function */
                OsApp_SetCurrent_ConfigApplicationID(ServiceTF->ApplicationID);

                OsKernel_GetCurrentCoreAppDataInfo()->TrustFunctionIsCalled = TRUE;
                /*[SWS_Os_00565] delay any TP errors until the CallTrustedFunction returns to Application*/
                if(TRUE == hasTpDelay)
                {
                    OsTp_StartDelay();
                }

                /*Switch to the MPU of Trusted function Service*/
                if(CallerAppId != ServiceTF->ApplicationID)
                {
                    OsMpu_AppSwitchTo(ServiceTF->ApplicationID);
                }
                /*Resume the interrupt*/
                OsIsr_ResumeISR(Level);

                /*Call the defined Trust Function */
                ServiceTF->Callback(FunctionIndex,FunctionParams);

                /*Suspend the interrupt*/
                OsIsr_SuspendISR(&Level);
                /*Restore the current Application ID to Caller Application */
                OsApp_SetCurrent_ConfigApplicationID(CallerAppId);

                /*Restore the MPU to Caller application */
                if(CallerAppId != ServiceTF->ApplicationID)
                {
                    OsMpu_AppSwitchTo(CallerAppId);
                }

                OsKernel_GetCurrentCoreAppDataInfo()->TrustFunctionIsCalled = FALSE;

                /*Restore the current application ID*/
                OsApp_SetCurrent_ConfigApplicationID(CallerAppId);

                /*TP start again*/
                if(TRUE == hasTpDelay)
                {
                    OsTp_StopDelay();
                }

                OsTask_LevelDownTaskPriority(TaskCurPriority);
                /*Resume the interrupt*/
                OsIsr_ResumeISR(Level);
                Status = E_OK;
            }
        }

    }
    if (E_OK != Status)
    {
        OsIsr_SuspendISR(&Level);
        OsHook_SetErrorParameterTwo(OS_SERVICEID_CALLTRUSTEDFUNCTION, (InputParaType)FunctionIndex, (InputParaType)FunctionParams);
        OsHook_CallErrorHook(Status);
        OsIsr_ResumeISR(Level);
    }

    OS_ARTI_SC_END(CallTrustedFunction, Status);
    OsOrti_ServiceEnd(OS_SERVICEID_CALLTRUSTEDFUNCTION);

    return Status;

}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

FUNC(StatusType, OS_CODE) CallTrustedFunction
(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FunctionParams
)
{
    StatusType result;

    if(IsNeedSysTrap())
    {
        /* Switch to system mode */
        Os_Inf_TrapToSystemMode();
        /*   */
        result = OsService_Internal_CallTrustedFunction(FunctionIndex,FunctionParams);
        /* Switch back to user mode */
        Os_Inf_TrapToUserMode();
    }
    else
    {
        result = OsService_Internal_CallTrustedFunction(FunctionIndex,FunctionParams);
    }

    return result;

}

FUNC(void, OS_CODE) TRUSTED_Func1
(
    TrustedFunctionIndexType FunctionIndex,
    TrustedFunctionParameterRefType FuncParam
)
{

}

FUNC(boolean, OS_CODE) OsService_ExtendedErrorCheck
(
    boolean Condition
)
{
    boolean result;
#if(OS_STATUS_EXTENDED == STD_ON)
    {
        result = Condition;
    }
#else
    {
        result = FALSE;
    }
#endif
    return result;
}

FUNC(boolean, OS_CODE) OsService_ServiceProtectionErrorCheck
(
    boolean Condition
)
{
    boolean result;
#if(OS_SERVICE_PROTECTION == STD_ON)
    {
        result = Condition;
    }
#else
    {
        result = FALSE;
    }
#endif
    return result;
}

/****************************************************************************************************
**                          AUTOSAR Function Definitions                                           **
****************************************************************************************************/


/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_orti.c
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
**                                  Includes                                                       **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_kernel.h"
#include "Os_orti.h"
#include "Os_task_types.h"
#include "Os_isr_types.h"

#include "Os.h"
#include "Os_services.h"

#include "Os_task_Cfg.h"
#include "Os_isr_Cfg.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
Os_OrtiType Os_OrtiRunningData[OS_KERNEL_MAX_CORE_NUM];
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
**                          Global Function Definitions                                            **
****************************************************************************************************/

FUNC(void ,OS_CODE)OsOrti_OrtiInit
(
    AppModeType AppMode
)
{
#if OS_STATUS_USEARTI == STD_ON
    CoreIdType CurrentCoreID;
    CurrentCoreID = Os_Inf_GetCoreId();

    Os_OrtiRunningData[CurrentCoreID].CurrentAppMode = AppMode;
    Os_OrtiRunningData[CurrentCoreID].LastError = E_OK;
    Os_OrtiRunningData[CurrentCoreID].RunningISRType = INVALID_ISR;
    Os_OrtiRunningData[CurrentCoreID].RunningTaskType = INVALID_TASK;
    Os_OrtiRunningData[CurrentCoreID].ServiceId = 0x1A2;
#endif
}

FUNC(void ,OS_CODE)OsOrti_ServiceStart
(
    Os_ServiceType ServiceId
)
{
#if OS_STATUS_USEARTI == STD_ON
    CoreIdType CurrentCoreID;
    CurrentCoreID = Os_Inf_GetCoreId();

    Os_OrtiRunningData[CurrentCoreID].ServiceId = ServiceId*2+3;
#endif
}

FUNC(void ,OS_CODE)OsOrti_ServiceEnd
(
    Os_ServiceType ServiceId
)
{
#if OS_STATUS_USEARTI == STD_ON
    CoreIdType CurrentCoreID;
    CurrentCoreID = Os_Inf_GetCoreId();

    Os_OrtiRunningData[CurrentCoreID].ServiceId &= ServiceId*2+2;
#endif
}

FUNC(void ,OS_CODE)OsOrti_TaskStart
(
    TaskType TaskID
)
{
#if OS_STATUS_USEARTI == STD_ON
    CoreIdType CurrentCoreID;
    CurrentCoreID = Os_Inf_GetCoreId();
    Os_OrtiRunningData[CurrentCoreID].RunningTaskType = TaskID;
#endif
}

FUNC(void ,OS_CODE)OsOrti_TaskEnd
(
    void
)
{
#if OS_STATUS_USEARTI == STD_ON
    CoreIdType CurrentCoreID;
    CurrentCoreID = Os_Inf_GetCoreId();

    Os_OrtiRunningData[CurrentCoreID].RunningTaskType = INVALID_TASK;
#endif
}

FUNC(void ,OS_CODE)OsOrti_ChangeIsr
(
    ISRType IsrID
)
{
#if OS_STATUS_USEARTI == STD_ON
    CoreIdType CurrentCoreID;
    CurrentCoreID = Os_Inf_GetCoreId();

    Os_OrtiRunningData[CurrentCoreID].RunningISRType = IsrID;
#endif
}

FUNC(void ,OS_CODE)OsOrti_SetLastError
(
    StatusType Error
)
{
#if OS_STATUS_USEARTI == STD_ON
    CoreIdType CurrentCoreID;
    CurrentCoreID = Os_Inf_GetCoreId();

    Os_OrtiRunningData[CurrentCoreID].LastError = Error;
#endif
}


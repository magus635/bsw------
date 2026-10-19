/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_orti.h
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
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_ORTI_H
#define OS_ORTI_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "datatypes.h"
#include "Compiler.h"
#include "Os_orti_types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
extern Os_OrtiType Os_OrtiRunningData[OS_KERNEL_MAX_CORE_NUM];

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
*   Function Name           : OsOrti_OrtiInit
*   Service ID              : None.
*   Description             : Orti Data Initialization
*   Parameters in           : CurrentAppMode: Current Running App Mode
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void ,OS_CODE)OsOrti_OrtiInit
(
    AppModeType CurrentAppMode
);

/****************************************************************************************************
*   Function Name           : OsOrti_ServiceStart
*   Service ID              : None.
*   Description             : Orti Service begin
*   Parameters in           : ServiceId: Service Start
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void ,OS_CODE)OsOrti_ServiceStart
(
    Os_ServiceType ServiceId
);

/****************************************************************************************************
*   Function Name           : OsOrti_ServiceEnd
*   Service ID              : None.
*   Description             : Orti Service end
*   Parameters in           : ServiceId: Service Start
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void ,OS_CODE)OsOrti_ServiceEnd
(
    Os_ServiceType ServiceId
);

/****************************************************************************************************
*   Function Name           : OsOrti_TaskStart
*   Service ID              : None.
*   Description             : Orti Task start
*   Parameters in           : TaskID: Current task id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void ,OS_CODE)OsOrti_TaskStart
(
    TaskType TaskID
);

/****************************************************************************************************
*   Function Name           : OsOrti_ServiceEnd
*   Service ID              : None.
*   Description             : Orit Task end
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void ,OS_CODE)OsOrti_TaskEnd
(
    void
);

/****************************************************************************************************
*   Function Name           : OsOrti_ChangeIsr
*   Service ID              : None.
*   Description             : Orit Change Running Isr
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void ,OS_CODE)OsOrti_ChangeIsr
(
    ISRType IsrID
);

/****************************************************************************************************
*   Function Name           : OsOrti_SetLastError
*   Service ID              : None.
*   Description             : Orti record the last error returned by an OS service
*   Parameters in           : Error: The error status passed to the error hook.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void ,OS_CODE)OsOrti_SetLastError
(
    StatusType Error
);

#endif /* OS_ORTI_H_ */

/****************************************************************************************************
**     End of File: Os_orti.h                                                                      **
****************************************************************************************************/


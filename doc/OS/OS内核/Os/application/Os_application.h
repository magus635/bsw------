/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_application.h
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
*  V0.1.0   28-May-2024    Pony(00412)                           Add Initial Code
****************************************************************************************************/
#ifndef OS_APPLICATION_H_
#define OS_APPLICATION_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_application_types.h"
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
*   Function Name           : OsApp_ApplicationInit
*   Service ID              : None.
*   Description             : Only used in CallTrustedFunction to updata the current Config AppID ID..
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsApp_ApplicationInit
(
    ApplicationType ApplicationID,
    AppModeType Mode
);

/****************************************************************************************************
*   Function Name           : OsApp_ApplicationDeInit
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsApp_ApplicationDeInit
(
    ApplicationType ApplicationID
);

/****************************************************************************************************
*   Function Name           : OsApp_SetAppTerminateStatus
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsApp_SetAppTerminateStatus
(
    ApplicationType ApplicationID
);
/****************************************************************************************************
*   Function Name           : OsApp_ChangeCurrent_AppInfo
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsApp_ChangeCurrent_AppInfo
(
    uint32 TargetObjectID
);
/****************************************************************************************************
*   Function Name           : OsApp_GetCurrent_ObjectInfo
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(uint32, OS_CODE) OsApp_GetCurrent_ObjectID
(
    void
);
/****************************************************************************************************
*   Function Name           : OsApp_GetCurrent_ObjectInfo
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_AppObjectRefType, OS_CODE) OsApp_GetCurrent_ObjectInfo
(
    void
);

/****************************************************************************************************
*   Function Name           : OsApp_GetCurrent_ObjectInfo
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_AppObjectRefType, OS_CODE) OsApp_GetPrevious_ObjectInfo
(
    void
);

/****************************************************************************************************
*   Function Name           : OsApp_GetSpecific_ObjectInfo
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(Os_AppObjectRefType, OS_CODE) OsApp_GetSpecific_ObjectInfo
(
    uint32 ObjectID
);

/****************************************************************************************************
*   Function Name           : OsApp_GetOwnerCoreID
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(CoreIdType, OS_CODE) OsApp_GetOwnerCoreID
(
    uint32 ApplicationID
);

/****************************************************************************************************
*   Function Name           : OsApp_GetCurrentApplicationID
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(ApplicationType, OS_CODE) OsApp_GetCurrentApplicationID
(
    void
);

/****************************************************************************************************
*   Function Name           : OsApp_CheckObjectAccessingAppMask
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsApp_CheckObjectAccessingAppMask
(
    uint32 ObjectID
);

/****************************************************************************************************
*   Function Name           : OsApp_CheckObjectAccessingAppMask
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsApp_CheckObjectAppIsAccessiable
(
    uint32 ObjectID
);

/****************************************************************************************************
*   Function Name           : OsApp_CheckCurrentAppIsTrusted
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsApp_CheckCurrentAppIsTrusted
(
    void
);

/****************************************************************************************************
*   Function Name           : OsApp_CheckTrustedFunctionIsCalled
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsApp_CheckTrustedFunctionIsCalled
(
    void
);

/****************************************************************************************************
*   Function Name           : OsApp_TerminateApplication
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsApp_TerminateApplication
(
    ApplicationType Application,
    RestartType RestartOption
);

/****************************************************************************************************
*   Function Name           : OsApp_CheckObjectAccessingAppMask
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(CoreIdType, OS_CODE) OsApp_GetPhysicalCoreIDFromObjectInfo
(
    uint32 ObjectID
);

/****************************************************************************************************
*   Function Name           : OsApp_GetApplicationState
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsApp_GetApplicationState
(
    ApplicationType Application,
    ApplicationStateRefType Value
);

/****************************************************************************************************
*   Function Name           : OsApp_GetApplicationState
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(TaskType, OS_CODE) OsApp_GetAppRestartTaskID
(
    ApplicationType ApplicationID
);

/****************************************************************************************************
*   Function Name           : OsApp_SetCurrent_ConfigApplicationID
*   Service ID              : None.
*   Description             : Only used in CallTrustedFunction to update the current Config AppID ID.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/

extern FUNC(void, OS_CODE) OsApp_SetCurrent_ConfigApplicationID
(
    ApplicationType ApplicationID
);

/****************************************************************************************************
*   Function Name           : OsApp_GetCurrentAppTpDelay
*   Service ID              : None.
*   Description             : Get current application timing protection delay flag.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/

extern FUNC(boolean, OS_CODE) OsApp_GetCurrentAppTpDelay
(
    void
);

/****************************************************************************************************
**     End of File: Os_application.h                                                               **
****************************************************************************************************/

#endif /* OS_APPLICATION_H_ */

/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_lock.h
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
#ifndef OS_LOCK_H_
#define OS_LOCK_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_GeneralTypes.h"
#include "Os_compiler_types.h"
#include "Os_lock_types.h"
#include "Os_application_types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define OS_LOCK_FREE ((void*)0xFFFFFFFFUL)
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
*   Function Name           : OsLock_ListPush
*   Service ID              : None.
*   Description             : Push a lock into nesting recording FIFO.
*   Parameters in           : LockListPtr: Pointer to FIFO.
                              LockRef: Pointer to lock to be pushed.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) OsLock_ListPush
(
    P2VAR(Os_LockConfigRefType, TYPEDEF, OS_VAR) LockListPtr,
    Os_LockConfigRefType LockRef
);

/****************************************************************************************************
*   Function Name           : OsLock_ListPop
*   Service ID              : None.
*   Description             : Pop a lock from nesting recording FIFO.
*   Parameters in           : LockListPtr: Pointer to FIFO.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) OsLock_ListPop
(
    P2VAR(Os_LockConfigRefType, TYPEDEF, OS_VAR) LockListPtr
);

/****************************************************************************************************
*   Function Name           : OsLock_ClearLockList
*   Service ID              : None.
*   Description             : Clear FIFO.
*   Parameters in           : LockListPtr: Pointer to FIFO.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) OsLock_ClearLockList
(
    P2VAR(Os_LockConfigRefType, TYPEDEF, OS_VAR) LockListPtr
);

#endif /* OS_LOCK_H_ */

/****************************************************************************************************
**     End of File: Os_resource.h                                                                  **
****************************************************************************************************/


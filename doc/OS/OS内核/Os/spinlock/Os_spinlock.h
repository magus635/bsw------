/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_spinlock.h
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
#ifndef OS_SPINLOCK_H_
#define OS_SPINLOCK_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_GeneralTypes.h"
#include "Os_spinlock_types.h"

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
*   Function Name           : OsSpinlock_SpinlockInit
*   Service ID              : None.
*   Description             : Initialize spinlock running datas.
*   Parameters in           : SpinlockId: ID of spinlock to be initialized.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsSpinlock_SpinlockInit
(
    SpinlockIdType SpinlockId
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_GetInternalSpinlock
*   Service ID              : None.
*   Description             : Get internal spinlock eg. startup/shutdown/ioc etc. withou error detect.
*   Parameters in           : SpinlockId: ID of internal spinlock to get.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsSpinlock_GetInternalSpinlock
(
    SpinlockIdType SpinlockId
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_ReleaseInternalSpinlock
*   Service ID              : None.
*   Description             : Release internal spinlock eg. startup/shutdown/ioc etc. withou error detect.
*   Parameters in           : SpinlockId: ID of internal spinlock to release.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsSpinlock_ReleaseInternalSpinlock
(
    SpinlockIdType SpinlockId
);

/****************************************************************************************************
*   Function Name           : OsSpinlock_SpinlockDeInit
*   Service ID              : None.
*   Description             : Deinitialize spinlock.
*   Parameters in           : SpinlockId: ID of spinlock to be deinit.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsSpinlock_SpinlockDeInit
(
    SpinlockIdType SpinlockId
);
#endif /* OS_SPINLOCK_H_ */

/****************************************************************************************************
**     End of File: Os_spinlock.h                                                                  **
****************************************************************************************************/


/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_mpu.h
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
#ifndef OS_MPU_H_
#define OS_MPU_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "common.h"
#include "Compiler.h"
#include "Os_context_types.h"
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
*   Function Name           : OsMpu_InitCore
*   Service ID              : None.
*   Description             : To initialize the Core MPU, which is used to protect the memory regions of the global core.
*   Parameters in           : CoreConfig: The core MPU region config.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsMpu_InitCore
(
    P2CONST(Os_MpuConfigType, AUTOMATIC, OS_CONST) CoreMpuCfg
);

/****************************************************************************************************
*   Function Name           : OsMpu_ObjectSwitchTo
*   Service ID              : None.
*   Description             : Switch to the next MPU region config.
*   Parameters in           : NextObjectMpuCfg: The next switch MPU config.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsMpu_ObjectSwitchTo
(
    P2VAR(Os_MpuConfigContextRefType, TYPEDEF, OS_VAR) NextObjectMpuCfg
);

/****************************************************************************************************
*   Function Name           : OsMpu_SwitchStack
*   Service ID              : None.
*   Description             : Switch the next task stack.
*   Parameters in           : Os_ContextInfo: The next task context information.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsMpu_SwitchStack
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_CONST)Os_ContextInfo
);

/****************************************************************************************************
*   Function Name           : OsMpu_AppSwitchTo
*   Service ID              : None.
*   Description             : Switch the next application MPU regions.
*   Parameters in           : AppID: The next application ID.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsMpu_AppSwitchTo
(
    ApplicationType AppID
);

/****************************************************************************************************
*   Function Name           : OsMpu_DisableObjectRegion
*   Service ID              : None.
*   Description             : Disable application and task MPU regions.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsMpu_DisableObjectRegion
(
    void
);

/****************************************************************************************************
*   Function Name           : OsMpu_IsMpuStackEnable
*   Service ID              : None.
*   Description             : Check whether MPU stack has been Enable.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsMpu_IsMpuStackEnable
(
    void
);
/****************************************************************************************************
*   Macro Name              : OSMEMORY_IS_READABLE
*   Service ID              : None.
*   Description             : Check whether the memory is readable or not .
*   Parameters in           : Address: The address of the checked memory.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
# define OSMEMORY_IS_READABLE(Address) ( ((uint32)(Address)) & ((uint32)(OS_MEM_ACCESS_READ)) )

/****************************************************************************************************
*   Macro Name              : OSMEMORY_IS_WRITEABLE
*   Service ID              : None.
*   Description             : Check whether the memory is writeable or not .
*   Parameters in           : Address: The address of the checked memory.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
# define OSMEMORY_IS_WRITEABLE(Address) ( ((uint32)(Address)) & ((uint32)(OS_MEM_ACCESS_WRITE)) )

/****************************************************************************************************
*   Macro Name              : OSMEMORY_IS_EXECUTABLE
*   Service ID              : None.
*   Description             : Check whether the memory is executable or not .
*   Parameters in           : Address: The address of the checked memory.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
# define OSMEMORY_IS_EXECUTABLE(Address) ( ((uint32)(Address)) & ((uint32)(OS_MEM_ACCESS_EXECUTE)) )

/****************************************************************************************************
*   Macro Name              : OSMEMORY_IS_STACKSPACE
*   Service ID              : None.
*   Description             : Check whether the memory is stack space or not .
*   Parameters in           : Address: The address of the checked memory.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
# define OSMEMORY_IS_STACKSPACE(Address) ( ((uint32)(Address)) & ((uint32)(OS_MEM_ACCESS_STACK)) )

#endif /* OS_MPU_H_ */

/****************************************************************************************************
**     End of File: Os_mpu.h                                                                      **
****************************************************************************************************/


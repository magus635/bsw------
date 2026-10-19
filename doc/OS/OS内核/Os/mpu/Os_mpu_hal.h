/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_mpu_hal.h
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
#ifndef OS_MPU_HAL_H_
#define OS_MPU_HAL_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "datatypes.h"
#include "Compiler.h"

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
*   Function Name           : OsMpu_Hal_CoreInit
*   Service ID              : None.
*   Description             : To initialize the Core MPU, which is used to protect the memory regions of the global core.
*                             It is called during the initialization of the core.
*   Parameters in           : CoreConfig: The core MPU region config.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsMpu_Hal_CoreInit(P2CONST(Os_MpuConfigType , TYPEDEF, OS_CONST) CoreConfig);

/****************************************************************************************************
*   Function Name           : OsMpu_Hal_MpuSwitch
*   Service ID              : None.
*   Description             : Switch to the destinaton MPU region config.
*   Parameters in           : MpuConfig: The next switch MPU config.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/

extern FUNC(void, OS_CODE)OsMpu_Hal_MpuSwitch(P2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST) MpuConfig
);

/****************************************************************************************************
*   Function Name           : OsMpu_Hal_SetStack
*   Service ID              : None.
*   Description             : Switch to the Object MPU stack config.
*   Parameters in           : MpuConfig: The next Object stack MPU config.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsMpu_Hal_SetStack(P2CONST(Os_MpuConfigType , TYPEDEF, OS_CONST) StackConfig );

/****************************************************************************************************
*   Function Name           : OsMpu_Hal_DisableRegion
*   Service ID              : None.
*   Description             : Disable the specific region.
*   Parameters in           : RegionIndex: The regin index
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsMpu_Hal_DisableRegions(uint32 RegionIndex);
#endif /* OS_MPU_HAL_H_ */

/****************************************************************************************************
**     End of File: Os_mpu_hal.h                                                                   **
****************************************************************************************************/


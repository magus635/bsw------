/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_isr_hal.h
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
#ifndef OS_ISR_HAL_H_
#define OS_ISR_HAL_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Compiler.h"
#include "Os_GeneralTypes.h"
#include "Os_isr_types.h"
#include "Os_kernel.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define OS_ISR_MAX_SPI_ID   (991U)
#define OS_ISR_MIN_SPI_ID   (32U)
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
*   Function Name           : OsIsr_Hal_GetLevel
*   Service ID              : None.
*   Description             : Get current isr level.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : Level: Pointer to level var.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_Hal_GetLevel
(
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) Level
);

/****************************************************************************************************
*   Function Name           : OsIsr_Hal_SetLevel
*   Service ID              : None.
*   Description             : Set isr level.
*   Parameters in           : Level: Level to be set.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_Hal_SetLevel
(
    Os_IsrLevelType Level
);

/****************************************************************************************************
*   Function Name           : OsIsr_Hal_DisableInterruptSource
*   Service ID              : None.
*   Description             : Disable isr in hardware interrupt controller.
*   Parameters in           : IntID: Interrupt hardware id.
                              CoreID: Core id of specific interrupt.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_Hal_DisableInterruptSource
(
    uint32 IntID,
    CoreIdType CoreID
);

/****************************************************************************************************
*   Function Name           : OsIsr_Hal_EnableInterruptSource
*   Service ID              : None.
*   Description             : Enable isr in hardware interrupt controller.
*   Parameters in           : IntID: Interrupt hardware id.
                              CoreID: Core id of specific interrupt.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_Hal_EnableInterruptSource
(
    uint32 IntID,
    CoreIdType CoreID
);

/****************************************************************************************************
*   Function Name           : OsIsr_Hal_ClearPendingInterrupt
*   Service ID              : None.
*   Description             : Clear pending flag in hardware interrupt controller.
*   Parameters in           : IntID: Interrupt hardware id.
                              CoreID: Core id of specific interrupt.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_Hal_ClearPendingInterrupt
(
    uint32 IntID,
    CoreIdType CoreID
);

/****************************************************************************************************
*   Function Name           : OsIsr_Hal_IsEnable
*   Service ID              : None.
*   Description             : Check if specific isr is enabled in interrupt controller.
*   Parameters in           : IntID: Interrupt hardware id.
                              CoreID: Core id of specific interrupt.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsIsr_Hal_IsEnable
(
    uint32 IntID,
    CoreIdType CoreID
);

/****************************************************************************************************
*   Function Name           : OsIsr_Hal_EndOfInterrupt
*   Service ID              : None.
*   Description             : Set interrupt to inactive.
*   Parameters in           : IntID: Interrupt hardware id.
                              CoreID: Core id of specific interrupt.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_Hal_EndOfInterrupt
(
    uint32 IntID,
    CoreIdType CoreID
);

/****************************************************************************************************
*   Function Name           : OsIsr_Hal_InstallIsr
*   Service ID              : None.
*   Description             : Install interrupt.
*   Parameters in           : IsrHwConfig: Interrupt hardware configuration.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_Hal_InstallIsr
(
    P2CONST(Os_Isr_Hal_ConfigType, AUTOMATIC, OS_CONST) IsrHwConfig
);

/****************************************************************************************************
*   Function Name           : OsIsr_Hal_TriggerSoftwareInterrupt
*   Service ID              : None.
*   Description             : Trigger software interrupt.
*   Parameters in           : IntId: Hardware interrupt id.
                              TargetCoreId: Owner core id of software interrupt.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIsr_Hal_TriggerSoftwareInterrupt
(
    uint32 IntId,
    uint32 TargetCoreId
);

#endif /* OS_ISR_HAL_H_ */

/****************************************************************************************************
**     End of File: Os_isr_hal.h                                                                   **
****************************************************************************************************/


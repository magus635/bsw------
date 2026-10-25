/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all ISR functions of DFlash Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Fls_Irq.h"
#include "Fls.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#if ((defined(FLS_USE_INTERRUPTS)) && (STD_ON == FLS_USE_INTERRUPTS))
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
#include "Fls_MemMap.h"

/****************************************************************************************************
*   Function Name           : Fls_DFlash_ISR
*
*   Service ID              : None.
*
*   Description             : This function is DFlash interrupt handler.
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.                                                 
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, FLS_PUBLIC_CODE) Fls_DFlash_ISR
(
    void
)
{
    /* Locate the interrupt service routine in Fls_Irq.c. [SWS_Fls_00233] */
    /* Call to Flash Interrupt function */
    Fls_Flash_ISRHandler();
}

/****************************************************************************************************
*   Function Name           : Fls_PFlash_ISR
*
*   Service ID              : None.
*
*   Description             : This function is DFlash interrupt handler.
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.                                                 
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, FLS_PUBLIC_CODE) Fls_PFlash_ISR
(
    void
)
{
    /* Locate the interrupt service routine in Fls_Irq.c. [SWS_Fls_00233] */
    /* Call to Flash Interrupt function */
    Fls_Flash_ISRHandler();
}
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Fls_MemMap.h"
#endif /* ((defined(FLS_USE_INTERRUPTS)) && (STD_ON \== FLS_USE_INTERRUPTS)) */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


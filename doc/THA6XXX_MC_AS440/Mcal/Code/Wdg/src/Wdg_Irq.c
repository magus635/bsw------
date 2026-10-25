/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Wdg_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : This file contains all ISR functions of Wdg Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright \(c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Wdg_Irq_c_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Wdg_Irq_c_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Wdg_Irq.h"
#include "Wdg.h"
#include "Mcall_Cfg.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/* #Violation: Wdg_Irq_c_REF_1 */
#define WDG_START_SEC_CODE_ASIL_D_GLOBAL
#include "Wdg_MemMap.h"

/****************************************************************************************************
*   Function Name           : Wdg_WDG0_Refresh_ISR
*
*   Service ID              : None.
*
*   Description             : This function is Core0 Wdg device interrupt handler.
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
FUNC(void, WDG_PUBLIC_CODE) Wdg_WDG0_Refresh_ISR
(
    void
)
{
    /* Call to BaseTimer Interrupt function */
    Wdg_RefreshTimer_ISRHandler();
}

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
*   Function Name           : Wdg_WDG1_Refresh_ISR
*
*   Service ID              : None.
*
*   Description             : This function is Core1 Wdg device interrupt handler.
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
FUNC(void, WDG_PUBLIC_CODE) Wdg_WDG1_Refresh_ISR
(
    void
)
{
    /* Call to BaseTimer Interrupt function */
    Wdg_RefreshTimer_ISRHandler();
}
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
/****************************************************************************************************
*   Function Name           : Wdg_WDG2_Refresh_ISR
*
*   Service ID              : None.
*
*   Description             : This function is Core2 Wdg device interrupt handler.
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
FUNC(void, WDG_PUBLIC_CODE) Wdg_WDG2_Refresh_ISR
(
    void
)
{
    /* Call to BaseTimer Interrupt function */
    Wdg_RefreshTimer_ISRHandler();
}

/****************************************************************************************************
*   Function Name           : Wdg_WDG3_Refresh_ISR
*
*   Service ID              : None.
*
*   Description             : This function is Core3 Wdg device interrupt handler.
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
FUNC(void, WDG_PUBLIC_CODE) Wdg_WDG3_Refresh_ISR
(
    void
)
{
    /* Call to BaseTimer Interrupt function */
    Wdg_RefreshTimer_ISRHandler();
}
#endif /* (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

/* #Violation: Wdg_Irq_c_REF_1 */
#define WDG_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Wdg_Irq_c_REF_2 */
#include "Wdg_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Wdg_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : This file contains all ISR function declarations of Wdg Driver
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
*#Wdg_Irq_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef WDG_IRQ_H_
#define WDG_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Wdg.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Wdg_Irq_h_REF_1 */
#define WDG_START_SEC_CODE_ASIL_D_GLOBAL
#include "Wdg_MemMap.h"

extern FUNC(void, WDG_PUBLIC_CODE) Wdg_WDG0_Refresh_ISR
(
    void
);

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern FUNC(void, WDG_PUBLIC_CODE) Wdg_WDG1_Refresh_ISR
(
    void
);
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
extern FUNC(void, WDG_PUBLIC_CODE) Wdg_WDG2_Refresh_ISR
(
    void
);

extern FUNC(void, WDG_PUBLIC_CODE) Wdg_WDG3_Refresh_ISR
(
    void
);
#endif /* (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

/* #Violation: Wdg_Irq_h_REF_1 */
#define WDG_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Wdg_MemMap.h"

#endif /* WDG_IRQ_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all ISR function declarations of DFlash Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Fls_Irq_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*/

#ifndef FLS_IRQ_H_
#define FLS_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcall.h"
#include "Fls_Cfg.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Fls_Irq_h_REF_1 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
#include "Fls_MemMap.h"
#if (FLS_USE_INTERRUPTS == STD_ON)
extern FUNC(void, FLS_PUBLIC_CODE) Fls_DFlash_ISR
(
    void
);

FUNC(void, FLS_PUBLIC_CODE) Fls_PFlash_ISR
(
    void
);
#endif /* FLS_USE_INTERRUPTS == STD_ON */
/* #Violation: Fls_Irq_h_REF_1 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Fls_MemMap.h"

#endif /* FLS_IRQ_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


/****************************************************************************************************
*   FileName              : Msc_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MSC
*
*   brief                 : This file contains all ISR functions of Spi Driver
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
*
*#Msc_Irq_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef MSC_IRQ_H_
#define MSC_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Compiler.h"
#include "Mcall_Cfg.h"
/****************************************************************************************************
**                                 Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Msc_Irq_h_REF_1 */
#define MSC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Msc_MemMap.h"

#if ((MCAL_PROCESSOR_CAT ==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern FUNC(void, MSC_PUBLIC_CODE) MSC0_SR0_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC0_SR1_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC0_SR2_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC0_SR3_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC0_SR4_ISR
(
    void
);
#endif /* (MCAL_PROCESSOR_CAT \==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
extern FUNC(void, MSC_PUBLIC_CODE) MSC1_SR0_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC1_SR1_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC1_SR2_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC1_SR3_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC1_SR4_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC2_SR0_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC2_SR1_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC2_SR2_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC2_SR3_ISR
(
    void
);

extern FUNC(void, MSC_PUBLIC_CODE) MSC2_SR4_ISR
(
    void
);
#endif /* MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516 */

/* #Violation: Msc_Irq_h_REF_1 */
#define MSC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Msc_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
#endif /* MSC_IRQ_H_ */

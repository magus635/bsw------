/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Icu_Irq.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GTM-TIM
 *
 *   brief                 : This file contains all functions of Icu Driver
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
*#Icu_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Icu_h_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the
* driver must be placed.
*
*/

#ifndef ICU_IRQ_H_
#define ICU_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* #Violation: Icu_h_REF_1 */
#define ICU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Icu_h_REF_2 */
#include "Icu_MemMap.h"
/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern void ICU_GTM_TIM00_CH00_ISR
(
    void
);

extern void ICU_GTM_TIM00_CH01_ISR
(
    void
);

extern void ICU_GTM_TIM00_CH02_ISR
(
    void
);

extern void ICU_GTM_TIM00_CH03_ISR
(
    void
);

extern void ICU_GTM_TIM00_CH04_ISR
(
    void
);

extern void ICU_GTM_TIM00_CH05_ISR
(
    void
);

extern void ICU_GTM_TIM00_CH06_ISR
(
    void
);

extern void ICU_GTM_TIM00_CH07_ISR
(
    void
);

extern void ICU_GTM_TIM01_CH00_ISR
(
    void
);

extern void ICU_GTM_TIM01_CH01_ISR
(
    void
);

extern void ICU_GTM_TIM01_CH02_ISR
(
    void
);

extern void ICU_GTM_TIM01_CH03_ISR
(
    void
);

extern void ICU_GTM_TIM01_CH04_ISR
(
    void
);

extern void ICU_GTM_TIM01_CH05_ISR
(
    void
);

extern void ICU_GTM_TIM01_CH06_ISR
(
    void
);

extern void ICU_GTM_TIM01_CH07_ISR
(
    void
);
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)) 
extern void ICU_GTM_TIM02_CH00_ISR
(
    void
);

extern void ICU_GTM_TIM02_CH01_ISR
(
    void
);

extern void ICU_GTM_TIM02_CH02_ISR
(
    void
);

extern void ICU_GTM_TIM02_CH03_ISR
(
    void
);

extern void ICU_GTM_TIM02_CH04_ISR
(
    void
);

extern void ICU_GTM_TIM02_CH05_ISR
(
    void
);

extern void ICU_GTM_TIM02_CH06_ISR
(
    void
);

extern void ICU_GTM_TIM02_CH07_ISR
(
    void
);
#endif
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern void ICU_GTM_TIM03_CH00_ISR
(
    void
);

extern void ICU_GTM_TIM03_CH01_ISR
(
    void
);

extern void ICU_GTM_TIM03_CH02_ISR
(
    void
);

extern void ICU_GTM_TIM03_CH03_ISR
(
    void
);

extern void ICU_GTM_TIM03_CH04_ISR
(
    void
);

extern void ICU_GTM_TIM03_CH05_ISR
(
    void
);

extern void ICU_GTM_TIM03_CH06_ISR
(
    void
);

extern void ICU_GTM_TIM03_CH07_ISR
(
    void
);

extern void ICU_GTM_TIM04_CH00_ISR
(
    void
);

extern void ICU_GTM_TIM04_CH01_ISR
(
    void
);

extern void ICU_GTM_TIM04_CH02_ISR
(
    void
);

extern void ICU_GTM_TIM04_CH03_ISR
(
    void
);

extern void ICU_GTM_TIM04_CH04_ISR
(
    void
);

extern void ICU_GTM_TIM04_CH05_ISR
(
    void
);

extern void ICU_GTM_TIM04_CH06_ISR
(
    void
);

extern void ICU_GTM_TIM04_CH07_ISR
(
    void
);

extern void ICU_GTM_TIM05_CH00_ISR
(
    void
);

extern void ICU_GTM_TIM05_CH01_ISR
(
    void
);

extern void ICU_GTM_TIM05_CH02_ISR
(
    void
);

extern void ICU_GTM_TIM05_CH03_ISR
(
    void
);

extern void ICU_GTM_TIM05_CH04_ISR
(
    void
);

extern void ICU_GTM_TIM05_CH05_ISR
(
    void
);

extern void ICU_GTM_TIM05_CH06_ISR
(
    void
);

extern void ICU_GTM_TIM05_CH07_ISR
(
    void
);

extern void ICU_GTM_TIM06_CH00_ISR
(
    void
);

extern void ICU_GTM_TIM06_CH01_ISR
(
    void
);

extern void ICU_GTM_TIM06_CH02_ISR
(
    void
);

extern void ICU_GTM_TIM06_CH03_ISR
(
    void
);

extern void ICU_GTM_TIM06_CH04_ISR
(
    void
);

extern void ICU_GTM_TIM06_CH05_ISR
(
    void
);

extern void ICU_GTM_TIM06_CH06_ISR
(
    void
);

extern void ICU_GTM_TIM06_CH07_ISR
(
    void
);

extern void ICU_GTM_TIM07_CH00_ISR
(
    void
);

extern void ICU_GTM_TIM07_CH01_ISR
(
    void
);

extern void ICU_GTM_TIM07_CH02_ISR
(
    void
);

extern void ICU_GTM_TIM07_CH03_ISR
(
    void
);

extern void ICU_GTM_TIM07_CH04_ISR
(
    void
);

extern void ICU_GTM_TIM07_CH05_ISR
(
    void
);

extern void ICU_GTM_TIM07_CH06_ISR
(
    void
);

extern void ICU_GTM_TIM07_CH07_ISR
(
    void
);
#endif
/* #Violation: Icu_h_REF_1 */
#define ICU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Icu_h_REF_2 */
#include "Icu_MemMap.h"

#endif /* ICU_IRQ_H_ */

/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/

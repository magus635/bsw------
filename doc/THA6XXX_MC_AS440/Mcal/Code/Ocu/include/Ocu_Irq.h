/****************************************************************************************************
 *
 ***************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Ocu_Irq.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GTM-ATOM
 *
 *   brief                 : This file contains all functions of Ocu Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ***************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Ocu_Irq_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef OCU_IRQ_H_
#define OCU_IRQ_H_

/****************************************************************************************************
 **                          Includes                                                              **
 ***************************************************************************************************/

#include "Mcall.h"

/****************************************************************************************************
 **                          Global Function Definitions                                           **
 ***************************************************************************************************/
/* #Violation: Ocu_Irq_h_REF_1*/
#define OCU_START_SEC_CODE_ASIL_D_GLOBAL
#include "Ocu_MemMap.h"

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM0_CH00_CH01_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM0_CH02_CH03_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM0_CH04_CH05_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM0_CH06_CH07_ISR
(
    void
);

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM1_CH00_CH01_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM1_CH02_CH03_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM1_CH04_CH05_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM1_CH06_CH07_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM2_CH00_CH01_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM2_CH02_CH03_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM2_CH04_CH05_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM2_CH06_CH07_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM3_CH00_CH01_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM3_CH02_CH03_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM3_CH04_CH05_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM3_CH06_CH07_ISR
(
    void
);
#endif /* (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM4_CH00_CH01_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM4_CH02_CH03_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM4_CH04_CH05_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM4_CH06_CH07_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM5_CH00_CH01_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM5_CH02_CH03_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM5_CH04_CH05_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM5_CH06_CH07_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM6_CH00_CH01_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM6_CH02_CH03_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM6_CH04_CH05_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM6_CH06_CH07_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM7_CH00_CH01_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM7_CH02_CH03_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM7_CH04_CH05_ISR
(
    void
);

extern FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM7_CH06_CH07_ISR
(
    void
);
#endif /* MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516 */

/* #Violation: Ocu_Irq_h_REF_1*/
#define OCU_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Ocu_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
#endif /* OCU_IRQ_H_ */

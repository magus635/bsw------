/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Pwm_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
*
*   brief                 : This file contains all ISR function declarations of PWM Driver
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
*#Pwm_Irq_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef PWM_IRQ_H_
#define PWM_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Compiler.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Pwm_Irq_h_REF_1 */
#define PWM_START_SEC_CODE_ASIL_D_GLOBAL
#include "Pwm_MemMap.h"

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH00_CH01_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH02_CH03_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH04_CH05_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH06_CH07_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH08_CH09_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH10_CH11_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH12_CH13_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH14_CH15_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH00_CH01_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH02_CH03_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH04_CH05_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH06_CH07_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH08_CH09_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH10_CH11_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH12_CH13_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH14_CH15_ISR
(
    void
);

#if ((MCAL_PROCESSOR_CAT ==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH00_CH01_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH02_CH03_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH04_CH05_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH06_CH07_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH08_CH09_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH10_CH11_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH12_CH13_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH14_CH15_ISR
(
    void
);
#endif /* (MCAL_PROCESSOR_CAT \==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH00_CH01_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH02_CH03_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH04_CH05_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH06_CH07_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH08_CH09_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH10_CH11_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH12_CH13_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH14_CH15_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH00_CH01_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH02_CH03_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH04_CH05_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH06_CH07_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH08_CH09_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH10_CH11_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH12_CH13_ISR
(
    void
);

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH14_CH15_ISR
(
    void
);
#endif /* MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516 */

extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM0_CH00_CH01_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM0_CH02_CH03_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM0_CH04_CH05_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM0_CH06_CH07_ISR
(
    void
);

#if ((MCAL_PROCESSOR_CAT ==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM1_CH00_CH01_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM1_CH02_CH03_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM1_CH04_CH05_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM1_CH06_CH07_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM2_CH00_CH01_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM2_CH02_CH03_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM2_CH04_CH05_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM2_CH06_CH07_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM3_CH00_CH01_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM3_CH02_CH03_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM3_CH04_CH05_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM3_CH06_CH07_ISR
(
    void
);
#endif /* (MCAL_PROCESSOR_CAT \==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM4_CH00_CH01_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM4_CH02_CH03_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM4_CH04_CH05_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM4_CH06_CH07_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM5_CH00_CH01_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM5_CH02_CH03_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM5_CH04_CH05_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM5_CH06_CH07_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM6_CH00_CH01_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM6_CH02_CH03_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM6_CH04_CH05_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM6_CH06_CH07_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM7_CH00_CH01_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM7_CH02_CH03_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM7_CH04_CH05_ISR
(
    void
);
extern FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM7_CH06_CH07_ISR
(
    void
);
#endif /* CAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516 */

/* #Violation: Pwm_Irq_h_REF_1 */
#define PWM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Pwm_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
#endif /* PWM_IRQ_H_ */

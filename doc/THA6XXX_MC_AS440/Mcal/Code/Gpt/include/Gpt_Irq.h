/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Gpt_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, BASETIMER
*
*   brief                 : This file contains all ISR function declarations of GPt Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
/*
*
*#Gpt_Irq_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/
#ifndef GPT_IRQ_H_
#define GPT_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Compiler.h"
#include "Mcall_Cfg.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Gpt_Irq_h_REF_1 */
#define GPT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Gpt_MemMap.h"

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH00_CH01_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH02_CH03_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH04_CH05_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH06_CH07_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH08_CH09_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH10_CH11_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH12_CH13_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH14_CH15_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH00_CH01_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH02_CH03_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH04_CH05_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH06_CH07_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH08_CH09_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH10_CH11_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH12_CH13_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH14_CH15_ISR
(
    void
);
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH00_CH01_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH02_CH03_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH04_CH05_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH06_CH07_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH08_CH09_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH10_CH11_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH12_CH13_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH14_CH15_ISR
(
    void
);
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH00_CH01_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH02_CH03_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH04_CH05_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH06_CH07_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH08_CH09_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH10_CH11_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH12_CH13_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH14_CH15_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH00_CH01_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH02_CH03_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH04_CH05_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH06_CH07_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH08_CH09_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH10_CH11_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH12_CH13_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH14_CH15_ISR
(
    void
);
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
extern FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_0_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_1_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_2_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_3_ISR
(
    void
);
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)) 
extern FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_4_ISR
(
    void
);

extern FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_5_ISR
(
    void
);
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */

/* #Violation: Gpt_Irq_h_REF_1 */
#define GPT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Gpt_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
#endif /* GPT_IRQ_H_ */

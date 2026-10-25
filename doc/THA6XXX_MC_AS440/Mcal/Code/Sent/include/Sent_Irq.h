/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Sent_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SARADC
*
*   brief                 : This file contains all ISR function declarations of Sent Driver
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
*#Sent_Irq_h_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Sent_Irq_h_REF_2::MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*/

#ifndef SENT_IRQ_H_
#define SENT_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Sent_Cfg.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Sent_Irq_h_REF_2 */
#define SENT_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Sent_Irq_h_REF_1 */
#include "Sent_MemMap.h" 
#if (defined(SENT_INST0_CHAN0) && (SENT_INST0_CHAN0 == STD_ON))
void Sent_RxChan0_ISR(void);
void Sent_ErrChan0_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN1) && (SENT_INST0_CHAN1 == STD_ON))
void Sent_RxChan1_ISR(void);
void Sent_ErrChan1_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN2) && (SENT_INST0_CHAN2 == STD_ON))
void Sent_RxChan2_ISR(void);
void Sent_ErrChan2_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN3) && (SENT_INST0_CHAN3 == STD_ON))
void Sent_RxChan3_ISR(void);
void Sent_ErrChan3_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN4) && (SENT_INST0_CHAN4 == STD_ON))
void Sent_RxChan4_ISR(void);
void Sent_ErrChan4_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN5) && (SENT_INST0_CHAN5 == STD_ON))
void Sent_RxChan5_ISR(void);
void Sent_ErrChan5_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN6) && (SENT_INST0_CHAN6 == STD_ON))
void Sent_RxChan6_ISR(void);
void Sent_ErrChan6_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN7) && (SENT_INST0_CHAN7 == STD_ON))
void Sent_RxChan7_ISR(void);
void Sent_ErrChan7_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN8) && (SENT_INST0_CHAN8 == STD_ON))
void Sent_RxChan8_ISR(void);
void Sent_ErrChan8_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN9) && (SENT_INST0_CHAN9 == STD_ON))
void Sent_RxChan9_ISR(void);
void Sent_ErrChan9_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN10) &&  (SENT_INST0_CHAN10 == STD_ON))
void Sent_RxChan10_ISR(void);
void Sent_ErrChan10_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN11) &&  (SENT_INST0_CHAN11 == STD_ON))
void Sent_RxChan11_ISR(void);
void Sent_ErrChan11_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN12) &&  (SENT_INST0_CHAN12 == STD_ON))
void Sent_RxChan12_ISR(void);
void Sent_ErrChan12_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN13) &&  (SENT_INST0_CHAN13 == STD_ON))
void Sent_RxChan13_ISR(void);
void Sent_ErrChan13_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN14) &&  (SENT_INST0_CHAN14 == STD_ON))
void Sent_RxChan14_ISR(void);
void Sent_ErrChan14_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN15) &&  (SENT_INST0_CHAN15 == STD_ON))
void Sent_RxChan15_ISR(void);
void Sent_ErrChan15_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN16) &&  (SENT_INST0_CHAN16 == STD_ON))
void Sent_RxChan16_ISR(void);
void Sent_ErrChan16_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN17) &&  (SENT_INST0_CHAN17 == STD_ON))
void Sent_RxChan17_ISR(void);
void Sent_ErrChan17_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN18) &&  (SENT_INST0_CHAN18 == STD_ON))
void Sent_RxChan18_ISR(void);
void Sent_ErrChan18_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN19) &&  (SENT_INST0_CHAN19 == STD_ON))
void Sent_RxChan19_ISR(void);
void Sent_ErrChan19_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN20) &&  (SENT_INST0_CHAN20 == STD_ON))
void Sent_RxChan20_ISR(void);
void Sent_ErrChan20_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN21) &&  (SENT_INST0_CHAN21 == STD_ON))
void Sent_RxChan21_ISR(void);
void Sent_ErrChan21_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN22) &&  (SENT_INST0_CHAN22 == STD_ON))
void Sent_RxChan22_ISR(void);
void Sent_ErrChan22_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN23) &&  (SENT_INST0_CHAN23 == STD_ON))
void Sent_RxChan23_ISR(void);
void Sent_ErrChan23_ISR(void);
#endif

#if (defined(SENT_INST0_CHAN24) &&  (SENT_INST0_CHAN24 == STD_ON))
void Sent_RxChan24_ISR(void);
void Sent_ErrChan24_ISR(void);
#endif
/* #Violation: Sent_Irq_h_REF_2 */
#define SENT_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Sent_Irq_h_REF_1 */
#include "Sent_MemMap.h" 

#endif /* SENT_IRQ_H_ */

/****************************************************************************************************
 **                          End of File                                                            *
 ***************************************************************************************************/


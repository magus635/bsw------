/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Sent_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SENT
*
*   brief                 : This file contains all ISR functions of Sent Driver
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
*#Sent_Irq_c_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Sent_Irq_c_REF_2:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#Sent_Irq_c_REF_3:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* Include SENT header file  */
#include "Sent.h"
#include "Sent_Irq.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Sent_Irq_c_REF_3 */
#define SENT_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Sent_Irq_c_REF_1 */
#include "Sent_MemMap.h" 

#if (defined(SENT_INST0_CHAN0) && (SENT_INST0_CHAN0 == STD_ON))
void Sent_RxChan0_ISR(void)
{
    Sent_Receive_ISRHandler(0U);
}

/******************************************************************************
** Syntax : void Sent_ErrChanx_ISR(void)                                      **
**                                                                           **
** Service ID:       NA                                                      **
**                                                                           **
** Sync/Async:       Synchronous                                             **
**                                                                           **
** Reentrancy:       reentrant                                               **
**                                                                           **
** Parameters (in):  none                                                    **
**                                                                           **
** Parameters (out): none                                                    **
**                                                                           **
** Return value:     none                                                    **
**                                                                           **
** Description : Service for SENT Interrupt Node x that generate errors.     **
**                                                                           **
******************************************************************************/
void Sent_ErrChan0_ISR(void)
{
    Sent_Error_ISRHandler(0U);
}
#endif /* (defined(SENT_INST0_CHAN0) && (SENT_INST0_CHAN0 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN1) && (SENT_INST0_CHAN1 == STD_ON))
void Sent_RxChan1_ISR(void)
{
    Sent_Receive_ISRHandler(1U);
}
void Sent_ErrChan1_ISR(void)
{
    Sent_Error_ISRHandler(1U);
}
#endif /* (defined(SENT_INST0_CHAN1) && (SENT_INST0_CHAN1 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN2) && (SENT_INST0_CHAN2 == STD_ON))
void Sent_RxChan2_ISR(void)
{
    Sent_Receive_ISRHandler(2U);
}

void Sent_ErrChan2_ISR(void)
{
    Sent_Error_ISRHandler(2U);
}
#endif /* (defined(SENT_INST0_CHAN2) && (SENT_INST0_CHAN2 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN3) && (SENT_INST0_CHAN3 == STD_ON))
void Sent_RxChan3_ISR(void)
{
    Sent_Receive_ISRHandler(3U);
}
void Sent_ErrChan3_ISR(void)
{
    Sent_Error_ISRHandler(3U);
}
#endif /* (defined(SENT_INST0_CHAN3) && (SENT_INST0_CHAN3 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN4) && (SENT_INST0_CHAN4 == STD_ON))
void Sent_RxChan4_ISR(void)
{
    Sent_Receive_ISRHandler(4U);
}
void Sent_ErrChan4_ISR(void)
{
    Sent_Error_ISRHandler(4U);
}
#endif /* (defined(SENT_INST0_CHAN4) && (SENT_INST0_CHAN4 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN5) && (SENT_INST0_CHAN5 == STD_ON))
/* #Violation: Sent_Irq_c_REF_2 */
void Sent_RxChan5_ISR(void)
{
    Sent_Receive_ISRHandler(5U);
}
/* #Violation: Sent_Irq_c_REF_2 */
void Sent_ErrChan5_ISR(void)
{
    Sent_Error_ISRHandler(5U);
}
#endif /* (defined(SENT_INST0_CHAN5) && (SENT_INST0_CHAN5 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN6) && (SENT_INST0_CHAN6 == STD_ON))
void Sent_RxChan6_ISR(void)
{
    Sent_Receive_ISRHandler(6U);
}
void Sent_ErrChan6_ISR(void)
{
    Sent_Error_ISRHandler(6U);
}
#endif /* (defined(SENT_INST0_CHAN6) && (SENT_INST0_CHAN6 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN7) && (SENT_INST0_CHAN7 == STD_ON))
/* #Violation: Sent_Irq_c_REF_2 */
void Sent_RxChan7_ISR(void)
{
    Sent_Receive_ISRHandler(7U);
}
/* #Violation: Sent_Irq_c_REF_2 */
void Sent_ErrChan7_ISR(void)
{
    Sent_Error_ISRHandler(7U);
}
#endif /* (defined(SENT_INST0_CHAN7) && (SENT_INST0_CHAN7 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN8) && (SENT_INST0_CHAN8 == STD_ON))
void Sent_RxChan8_ISR(void)
{
    Sent_Receive_ISRHandler(8U);
}
void Sent_ErrChan8_ISR(void)
{
    Sent_Error_ISRHandler(8);
}
#endif /* (defined(SENT_INST0_CHAN8) && (SENT_INST0_CHAN8 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN9) && (SENT_INST0_CHAN9 == STD_ON))
/* #Violation: Sent_Irq_c_REF_2 */
void Sent_RxChan9_ISR(void)
{
    Sent_Receive_ISRHandler(9U);
}
/* #Violation: Sent_Irq_c_REF_2 */
void Sent_ErrChan9_ISR(void)
{
    Sent_Error_ISRHandler(9U);
}
#endif /* (defined(SENT_INST0_CHAN9) && (SENT_INST0_CHAN9 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN10) && (SENT_INST0_CHAN10 == STD_ON))
void Sent_RxChan10_ISR(void)
{
    Sent_Receive_ISRHandler(10U);
}

void Sent_ErrChan10_ISR(void)
{
    Sent_Error_ISRHandler(10U);
}
#endif /* (defined(SENT_INST0_CHAN10) && (SENT_INST0_CHAN10 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN11) && (SENT_INST0_CHAN11 == STD_ON))
void Sent_RxChan11_ISR(void)
{
    Sent_Receive_ISRHandler(11U);
}

void Sent_ErrChan11_ISR(void)
{
    Sent_Error_ISRHandler(11U);
}
#endif /* (defined(SENT_INST0_CHAN11) && (SENT_INST0_CHAN11 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN12) && (SENT_INST0_CHAN12 == STD_ON))
void Sent_RxChan12_ISR(void)
{
    Sent_Receive_ISRHandler(12U);
}

void Sent_ErrChan12_ISR(void)
{
    Sent_Error_ISRHandler(12U);
}
#endif /* (defined(SENT_INST0_CHAN12) && (SENT_INST0_CHAN12 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN13) && (SENT_INST0_CHAN13 == STD_ON))
void Sent_RxChan13_ISR(void)
{
    Sent_Receive_ISRHandler(13U);
}

void Sent_ErrChan13_ISR(void)
{
    Sent_Error_ISRHandler(13U);
}
#endif /* (defined(SENT_INST0_CHAN13) && (SENT_INST0_CHAN13 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN14) && (SENT_INST0_CHAN14 == STD_ON))
void Sent_RxChan14_ISR(void)
{
    Sent_Receive_ISRHandler(14U);
}

void Sent_ErrChan14_ISR(void)
{
    Sent_Error_ISRHandler(14U);
}
#endif /* (defined(SENT_INST0_CHAN14) && (SENT_INST0_CHAN14 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN15) && (SENT_INST0_CHAN15 == STD_ON))
void Sent_RxChan15_ISR(void)
{
    Sent_Receive_ISRHandler(15U);
}
void Sent_ErrChan15_ISR(void)
{
    Sent_Error_ISRHandler(15U);
}
#endif /* (defined(SENT_INST0_CHAN15) && (SENT_INST0_CHAN15 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN16) && (SENT_INST0_CHAN16 == STD_ON))
void Sent_RxChan16_ISR(void)
{
    Sent_Receive_ISRHandler(16U);
}
void Sent_ErrChan16_ISR(void)
{
    Sent_Error_ISRHandler(16U);
}
#endif /* (defined(SENT_INST0_CHAN16) && (SENT_INST0_CHAN16 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN17) && (SENT_INST0_CHAN17 == STD_ON))
void Sent_RxChan17_ISR(void)
{
    Sent_Receive_ISRHandler(17U);
}

void Sent_ErrChan17_ISR(void)
{
    Sent_Error_ISRHandler(17U);
}
#endif /* (defined(SENT_INST0_CHAN17) && (SENT_INST0_CHAN17 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN18) && (SENT_INST0_CHAN18 == STD_ON))
void Sent_RxChan18_ISR(void)
{
    Sent_Receive_ISRHandler(18U);
}

void Sent_ErrChan18_ISR(void)
{
    Sent_Error_ISRHandler(18U);
}
#endif /* (defined(SENT_INST0_CHAN18) && (SENT_INST0_CHAN18 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN19) && (SENT_INST0_CHAN19 == STD_ON))
void Sent_RxChan19_ISR(void)
{
    Sent_Receive_ISRHandler(19U);
}

void Sent_ErrChan19_ISR(void)
{
    Sent_Error_ISRHandler(19U);
}
#endif /* (defined(SENT_INST0_CHAN19) && (SENT_INST0_CHAN19 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN20) && (SENT_INST0_CHAN20 == STD_ON))
void Sent_RxChan20_ISR(void)
{
    Sent_Receive_ISRHandler(20U);
}

void Sent_ErrChan20_ISR(void)
{
    Sent_Error_ISRHandler(20U);
}
#endif /* (defined(SENT_INST0_CHAN20) && (SENT_INST0_CHAN20 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN21) && (SENT_INST0_CHAN21 == STD_ON))
void Sent_RxChan21_ISR(void)
{
    Sent_Receive_ISRHandler(21U);
}

void Sent_ErrChan21_ISR(void)
{
    Sent_Error_ISRHandler(21U);
}
#endif /* (defined(SENT_INST0_CHAN21) && (SENT_INST0_CHAN21 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN22) && (SENT_INST0_CHAN22 == STD_ON))
void Sent_RxChan22_ISR(void)
{
    Sent_Receive_ISRHandler(22U);
}

void Sent_ErrChan22_ISR(void)
{
    Sent_Error_ISRHandler(22U);
}
#endif /* (defined(SENT_INST0_CHAN22) && (SENT_INST0_CHAN22 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN23) && (SENT_INST0_CHAN23 == STD_ON))
void Sent_RxChan23_ISR(void)
{
    Sent_Receive_ISRHandler(23U);
}

void Sent_ErrChan23_ISR(void)
{
    Sent_Error_ISRHandler(23U);
}
#endif /* (defined(SENT_INST0_CHAN23) && (SENT_INST0_CHAN23 \== STD_ON)) */

#if (defined(SENT_INST0_CHAN24) && (SENT_INST0_CHAN24 == STD_ON))
void Sent_RxChan24_ISR(void)
{
    Sent_Receive_ISRHandler(24U);
}
void Sent_ErrChan24_ISR(void)
{
    Sent_Error_ISRHandler(24U);
}
#endif /* (defined(SENT_INST0_CHAN24) && (SENT_INST0_CHAN24 \== STD_ON)) */

/* #Violation: Sent_Irq_c_REF_3 */
#define SENT_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Sent_Irq_c_REF_1 */
#include "Sent_MemMap.h" 

/****************************************************************************************************
 **                          End of File                                                            *
 ***************************************************************************************************/


/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Adc_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SARADC
*
*   brief                 : This file contains all ISR functions of Adc Driver
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
*#Adc_Irq_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Adc_Irq_c_REF_2:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Adc_Irq.h"
#include "Adc_Cfg.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Adc_Irq_c_REF_2 */
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"

#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE == STD_ON))
/****************************************************************************************************
*   Function Name           : ADCmSRn_FUNC(void, ADC_PUBLIC_CODE) m = ADC HW unit number
(
    void
)
*
*   Service ID              : None.
*
*   Description             : These functions are for interrupt service of SARADC request Queuing.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
#if (defined(ADC_HWUNIT_ADC0) && (ADC_HWUNIT_ADC0 == 0U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC0) && (ADC_HWUNIT_INT_EN_SARADC0 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC0_RS0) && (ADC_HWUNIT_INT_EN_SARADC0_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC0SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC0, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC0_RS0) && (ADC_HWUNIT_INT_EN_SARADC0_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC0_RS1) && (ADC_HWUNIT_INT_EN_SARADC0_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC0SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC0, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC0_RS1) && (ADC_HWUNIT_INT_EN_SARADC0_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC0_RS2) && (ADC_HWUNIT_INT_EN_SARADC0_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC0SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC0, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC0_RS2) && (ADC_HWUNIT_INT_EN_SARADC0_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC0) && (ADC_HWUNIT_INT_EN_SARADC0 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC0) && (ADC_HWUNIT_ADC0 == 0U)) */

#if (defined(ADC_HWUNIT_ADC1) && (ADC_HWUNIT_ADC1 == 1U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC1) && (ADC_HWUNIT_INT_EN_SARADC1 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC1_RS0) && (ADC_HWUNIT_INT_EN_SARADC1_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC1SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC1, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC1_RS0) && (ADC_HWUNIT_INT_EN_SARADC1_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC1_RS1) && (ADC_HWUNIT_INT_EN_SARADC1_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC1SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC1, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC1_RS1) && (ADC_HWUNIT_INT_EN_SARADC1_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC1_RS2) && (ADC_HWUNIT_INT_EN_SARADC1_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC1SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC1, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC1_RS2) && (ADC_HWUNIT_INT_EN_SARADC1_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC1) && (ADC_HWUNIT_INT_EN_SARADC1 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC1) && (ADC_HWUNIT_ADC1 == 1U)) */

#if (defined(ADC_HWUNIT_ADC2) && (ADC_HWUNIT_ADC2 == 2U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC2) && (ADC_HWUNIT_INT_EN_SARADC2 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC2_RS0) && (ADC_HWUNIT_INT_EN_SARADC2_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC2SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC2, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC2_RS0) && (ADC_HWUNIT_INT_EN_SARADC2_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC2_RS1) && (ADC_HWUNIT_INT_EN_SARADC2_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC2SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC2, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC2_RS1) && (ADC_HWUNIT_INT_EN_SARADC2_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC2_RS2) && (ADC_HWUNIT_INT_EN_SARADC2_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC2SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC2, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC2_RS2) && (ADC_HWUNIT_INT_EN_SARADC2_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC2) && (ADC_HWUNIT_INT_EN_SARADC2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC2) && (ADC_HWUNIT_ADC2 == 2U)) */

#if (defined(ADC_HWUNIT_ADC3) && (ADC_HWUNIT_ADC3 == 3U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC3) && (ADC_HWUNIT_INT_EN_SARADC3 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC3_RS0) && (ADC_HWUNIT_INT_EN_SARADC3_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC3SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC3, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC3_RS0) && (ADC_HWUNIT_INT_EN_SARADC3_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC3_RS1) && (ADC_HWUNIT_INT_EN_SARADC3_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC3SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC3, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC3_RS1) && (ADC_HWUNIT_INT_EN_SARADC3_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC3_RS2) && (ADC_HWUNIT_INT_EN_SARADC3_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC3SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC3, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC3_RS2) && (ADC_HWUNIT_INT_EN_SARADC3_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC3) && (ADC_HWUNIT_INT_EN_SARADC3 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC3) && (ADC_HWUNIT_ADC3 == 3U)) */

#if (defined(ADC_HWUNIT_ADC4) && (ADC_HWUNIT_ADC4 == 4U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC4) && (ADC_HWUNIT_INT_EN_SARADC4 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC4_RS0) && (ADC_HWUNIT_INT_EN_SARADC4_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC4SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC4, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC4_RS0) && (ADC_HWUNIT_INT_EN_SARADC4_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC4_RS1) && (ADC_HWUNIT_INT_EN_SARADC4_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC4SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC4, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC4_RS1) && (ADC_HWUNIT_INT_EN_SARADC4_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC4_RS2) && (ADC_HWUNIT_INT_EN_SARADC4_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC4SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC4, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC4_RS2) && (ADC_HWUNIT_INT_EN_SARADC4_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC4) && (ADC_HWUNIT_INT_EN_SARADC4 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC4) && (ADC_HWUNIT_ADC4 == 4U)) */

#if (defined(ADC_HWUNIT_ADC5) && (ADC_HWUNIT_ADC5 == 5U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC5) && (ADC_HWUNIT_INT_EN_SARADC5 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC5_RS0) && (ADC_HWUNIT_INT_EN_SARADC5_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC5SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC5, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC5_RS0) && (ADC_HWUNIT_INT_EN_SARADC5_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC5_RS1) && (ADC_HWUNIT_INT_EN_SARADC5_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC5SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC5, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC5_RS1) && (ADC_HWUNIT_INT_EN_SARADC5_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC5_RS2) && (ADC_HWUNIT_INT_EN_SARADC5_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC5SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC5, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC5_RS2) && (ADC_HWUNIT_INT_EN_SARADC5_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC5) && (ADC_HWUNIT_INT_EN_SARADC5 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC5) && (ADC_HWUNIT_ADC5 == 5U)) */

#if (defined(ADC_HWUNIT_ADC6) && (ADC_HWUNIT_ADC6 == 6U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC6) && (ADC_HWUNIT_INT_EN_SARADC6 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC6_RS0) && (ADC_HWUNIT_INT_EN_SARADC6_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC6SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC6, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC6_RS0) && (ADC_HWUNIT_INT_EN_SARADC6_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC6_RS1) && (ADC_HWUNIT_INT_EN_SARADC6_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC6SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC6, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC6_RS1) && (ADC_HWUNIT_INT_EN_SARADC6_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC6_RS2) && (ADC_HWUNIT_INT_EN_SARADC6_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC6SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC6, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC6_RS2) && (ADC_HWUNIT_INT_EN_SARADC6_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC6) && (ADC_HWUNIT_INT_EN_SARADC6 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC6) && (ADC_HWUNIT_ADC6 == 6U)) */

#if (defined(ADC_HWUNIT_ADC7) && (ADC_HWUNIT_ADC7 == 7U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC7) && (ADC_HWUNIT_INT_EN_SARADC7 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC7_RS0) && (ADC_HWUNIT_INT_EN_SARADC7_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC7SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC7, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC7_RS0) && (ADC_HWUNIT_INT_EN_SARADC7_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC7_RS1) && (ADC_HWUNIT_INT_EN_SARADC7_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC7SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC7, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC7_RS1) && (ADC_HWUNIT_INT_EN_SARADC7_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC7_RS2) && (ADC_HWUNIT_INT_EN_SARADC7_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC7SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC7, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC7_RS2) && (ADC_HWUNIT_INT_EN_SARADC7_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC7) && (ADC_HWUNIT_INT_EN_SARADC7 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC7) && (ADC_HWUNIT_ADC7 == 7U)) */

#if (defined(ADC_HWUNIT_ADC8) && (ADC_HWUNIT_ADC8 == 8U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC8) && (ADC_HWUNIT_INT_EN_SARADC8 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC8_RS0) && (ADC_HWUNIT_INT_EN_SARADC8_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC8SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC8, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC8_RS0) && (ADC_HWUNIT_INT_EN_SARADC8_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC8_RS1) && (ADC_HWUNIT_INT_EN_SARADC8_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC8SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC8, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC8_RS1) && (ADC_HWUNIT_INT_EN_SARADC8_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC8_RS2) && (ADC_HWUNIT_INT_EN_SARADC8_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC8SR2_ISR
(
    void
)
{

    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC8, SARADC_REQUESTSOURCE_QUEUE2);

}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC8_RS2) && (ADC_HWUNIT_INT_EN_SARADC8_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC8) && (ADC_HWUNIT_INT_EN_SARADC8 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC8) && (ADC_HWUNIT_ADC8 == 8U)) */

#if (defined(ADC_HWUNIT_ADC9) && (ADC_HWUNIT_ADC9 == 9U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC9) && (ADC_HWUNIT_INT_EN_SARADC9 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC9_RS0) && (ADC_HWUNIT_INT_EN_SARADC9_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC9SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC9, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC9_RS0) && (ADC_HWUNIT_INT_EN_SARADC9_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC9_RS1) && (ADC_HWUNIT_INT_EN_SARADC9_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC9SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC9, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC9_RS1) && (ADC_HWUNIT_INT_EN_SARADC9_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC9_RS2) && (ADC_HWUNIT_INT_EN_SARADC9_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC9SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC9, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC9_RS2) && (ADC_HWUNIT_INT_EN_SARADC9_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC9) && (ADC_HWUNIT_INT_EN_SARADC9 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC9) && (ADC_HWUNIT_ADC9 == 9U)) */

#if (defined(ADC_HWUNIT_ADC10) && (ADC_HWUNIT_ADC10 == 10U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC10) && (ADC_HWUNIT_INT_EN_SARADC10 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC10_RS0) && (ADC_HWUNIT_INT_EN_SARADC10_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC10SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC10, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC10_RS0) && (ADC_HWUNIT_INT_EN_SARADC10_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC10_RS1) && (ADC_HWUNIT_INT_EN_SARADC10_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC10SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC10, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC10_RS1) && (ADC_HWUNIT_INT_EN_SARADC10_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC10_RS2) && (ADC_HWUNIT_INT_EN_SARADC10_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC10SR2_ISR
(
    void
)
{

    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC10, SARADC_REQUESTSOURCE_QUEUE2);

}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC10_RS2) && (ADC_HWUNIT_INT_EN_SARADC10_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC10) && (ADC_HWUNIT_INT_EN_SARADC10 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC10) && (ADC_HWUNIT_ADC10 == 10U)) */

#if (defined(ADC_HWUNIT_ADC11) && (ADC_HWUNIT_ADC11 == 11U))
#if (defined(ADC_HWUNIT_INT_EN_SARADC11) && (ADC_HWUNIT_INT_EN_SARADC11 == STD_ON))
#if (defined(ADC_HWUNIT_INT_EN_SARADC11_RS0) && (ADC_HWUNIT_INT_EN_SARADC11_RS0 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC11SR0_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC11, SARADC_REQUESTSOURCE_QUEUE0);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC11_RS0) && (ADC_HWUNIT_INT_EN_SARADC11_RS0 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC11_RS1) && (ADC_HWUNIT_INT_EN_SARADC11_RS1 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC11SR1_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC11, SARADC_REQUESTSOURCE_QUEUE1);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC11_RS1) && (ADC_HWUNIT_INT_EN_SARADC11_RS1 == STD_ON)) */

#if (defined(ADC_HWUNIT_INT_EN_SARADC11_RS2) && (ADC_HWUNIT_INT_EN_SARADC11_RS2 == STD_ON))
FUNC(void, ADC_PUBLIC_CODE) Adc_ADC11SR2_ISR
(
    void
)
{
    Adc_QueueRequest_ISRHandler(ADC_HWUNIT_ADC11, SARADC_REQUESTSOURCE_QUEUE2);
}
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC11_RS2) && (ADC_HWUNIT_INT_EN_SARADC11_RS2 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_INT_EN_SARADC11) && (ADC_HWUNIT_INT_EN_SARADC11 == STD_ON)) */
#endif /* \(defined(ADC_HWUNIT_ADC11) && (ADC_HWUNIT_ADC11 == 11U)) */

#endif /* \((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE == STD_ON)) */

/* #Violation: Adc_Irq_c_REF_2 */
#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Adc_Irq_c_REF_1 */
#include "Adc_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

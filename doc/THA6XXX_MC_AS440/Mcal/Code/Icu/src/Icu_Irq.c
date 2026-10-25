/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Icu_Irq.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GTM-TIM
 *
 *   brief                 : This file contains all ISR functions of Icu Driver
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
*#Icu_Irq_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Icu_Irq_c_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Icu_Irq_c_REF_3:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Icu.h"
#include "Icu_Irq.h"
#include "Mcall_Cfg.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_2 */
#define ICU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Icu_Irq_c_REF_1 */
#include "Icu_MemMap.h"
/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM00_CH00_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM0_CH0.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM00_CH00_ISR(void)
{
    Icu_Tim_ISRHandler(0U, 0U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM00_CH01_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM0_CH1.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM00_CH01_ISR(void)
{
    Icu_Tim_ISRHandler(0U, 1U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM00_CH02_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM0_CH2.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM00_CH02_ISR(void)
{
    Icu_Tim_ISRHandler(0U, 2U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM00_CH03_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM0_CH3.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM00_CH03_ISR(void)
{
    Icu_Tim_ISRHandler(0U, 3U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM00_CH04_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM0_CH4.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM00_CH04_ISR(void)
{
    Icu_Tim_ISRHandler(0U, 4U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM00_CH05_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM0_CH5.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM00_CH05_ISR(void)
{
    Icu_Tim_ISRHandler(0U, 5U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM00_CH06_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM0_CH6.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM00_CH06_ISR(void)
{
    Icu_Tim_ISRHandler(0U, 6U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM00_CH07_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM0_CH7.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM00_CH07_ISR(void)
{
    Icu_Tim_ISRHandler(0U, 7U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM01_CH00_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM1_CH0.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM01_CH00_ISR(void)
{
    Icu_Tim_ISRHandler(1U, 0U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM01_CH01_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM1_CH1.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM01_CH01_ISR(void)
{
    Icu_Tim_ISRHandler(1U, 1U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM01_CH02_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM1_CH2.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM01_CH02_ISR(void)
{
    Icu_Tim_ISRHandler(1U, 2U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM01_CH03_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM1_CH3.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM01_CH03_ISR(void)
{
    Icu_Tim_ISRHandler(1U, 3U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM01_CH04_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM1_CH4.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM01_CH04_ISR(void)
{
    Icu_Tim_ISRHandler(1U, 4U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM01_CH05_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM1_CH5.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM01_CH05_ISR(void)
{
    Icu_Tim_ISRHandler(1U, 5U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM01_CH06_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM1_CH6.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM01_CH06_ISR(void)
{
    Icu_Tim_ISRHandler(1U, 6U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM01_CH07_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM1_CH7.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM01_CH07_ISR(void)
{
    Icu_Tim_ISRHandler(1U, 7U);
}

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)) 
/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM02_CH00_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM2_CH0.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM02_CH00_ISR(void)
{
    Icu_Tim_ISRHandler(2U, 0U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM02_CH01_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM2_CH1.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM02_CH01_ISR(void)
{
    Icu_Tim_ISRHandler(2U, 1U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM02_CH02_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM2_CH2.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM02_CH02_ISR(void)
{
    Icu_Tim_ISRHandler(2U, 2U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM02_CH03_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM2_CH3.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM02_CH03_ISR(void)
{
    Icu_Tim_ISRHandler(2U, 3U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM02_CH04_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM2_CH4.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM02_CH04_ISR(void)
{
    Icu_Tim_ISRHandler(2U, 4U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM02_CH05_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM2_CH5.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM02_CH05_ISR(void)
{
    Icu_Tim_ISRHandler(2U, 5U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM02_CH06_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM2_CH6.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM02_CH06_ISR(void)
{
    Icu_Tim_ISRHandler(2U, 6U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM02_CH07_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM2_CH7.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM02_CH07_ISR(void)
{
    Icu_Tim_ISRHandler(2U, 7U);
}
#endif
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM03_CH00_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM3_CH0.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM03_CH00_ISR(void)
{
    Icu_Tim_ISRHandler(3U, 0U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM03_CH01_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM3_CH1.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM03_CH01_ISR(void)
{
    Icu_Tim_ISRHandler(3U, 1U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM03_CH02_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM3_CH2.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM03_CH02_ISR(void)
{
    Icu_Tim_ISRHandler(3U, 2U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM03_CH03_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM3_CH3.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM03_CH03_ISR(void)
{
    Icu_Tim_ISRHandler(3U, 3U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM03_CH04_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM3_CH4.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM03_CH04_ISR(void)
{
    Icu_Tim_ISRHandler(3U, 4U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM03_CH05_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM3_CH5.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM03_CH05_ISR(void)
{
    Icu_Tim_ISRHandler(3U, 5U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM03_CH06_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM3_CH6.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM03_CH06_ISR(void)
{
    Icu_Tim_ISRHandler(3U, 6U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM03_CH07_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM3_CH7.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM03_CH07_ISR(void)
{
    Icu_Tim_ISRHandler(3U, 7U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM04_CH00_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM4_CH0.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM04_CH00_ISR(void)
{
    Icu_Tim_ISRHandler(4U, 0U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM04_CH01_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM4_CH1.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM04_CH01_ISR(void)
{
    Icu_Tim_ISRHandler(4U, 1U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM04_CH02_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM4_CH2.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM04_CH02_ISR(void)
{
    Icu_Tim_ISRHandler(4U, 2U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM04_CH03_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM4_CH3.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM04_CH03_ISR(void)
{
    Icu_Tim_ISRHandler(4U, 3U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM04_CH04_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM4_CH4.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM04_CH04_ISR(void)
{
    Icu_Tim_ISRHandler(4U, 4U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM04_CH05_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM4_CH5.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM04_CH05_ISR(void)
{
    Icu_Tim_ISRHandler(4U, 5U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM04_CH06_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM4_CH6.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM04_CH06_ISR(void)
{
    Icu_Tim_ISRHandler(4U, 6U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM04_CH07_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM4_CH7.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM04_CH07_ISR(void)
{
    Icu_Tim_ISRHandler(4U, 7U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM05_CH00_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM5_CH0.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM05_CH00_ISR(void)
{
    Icu_Tim_ISRHandler(5U, 0U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM05_CH01_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM5_CH1.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM05_CH01_ISR(void)
{
    Icu_Tim_ISRHandler(5U, 1U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM05_CH02_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM5_CH2.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM05_CH02_ISR(void)
{
    Icu_Tim_ISRHandler(5U, 2U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM05_CH03_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM5_CH3.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM05_CH03_ISR(void)
{
    Icu_Tim_ISRHandler(5U, 3U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM05_CH04_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM5_CH4.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM05_CH04_ISR(void)
{
    Icu_Tim_ISRHandler(5U, 4U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM05_CH05_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM5_CH5.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM05_CH05_ISR(void)
{
    Icu_Tim_ISRHandler(5U, 5U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM05_CH06_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM5_CH6.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM05_CH06_ISR(void)
{
    Icu_Tim_ISRHandler(5U, 6U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM05_CH07_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM5_CH7.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM05_CH07_ISR(void)
{
    Icu_Tim_ISRHandler(5U, 7U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM06_CH00_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM6_CH0.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM06_CH00_ISR(void)
{
    Icu_Tim_ISRHandler(6U, 0U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM06_CH01_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM6_CH1.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM06_CH01_ISR(void)
{
    Icu_Tim_ISRHandler(6U, 1U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM06_CH02_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM6_CH2.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM06_CH02_ISR(void)
{
    Icu_Tim_ISRHandler(6U, 2U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM06_CH03_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM6_CH3.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM06_CH03_ISR(void)
{
    Icu_Tim_ISRHandler(6U, 3U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM06_CH04_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM6_CH4.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM06_CH04_ISR(void)
{
    Icu_Tim_ISRHandler(6U, 4U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM06_CH05_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM6_CH5.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM06_CH05_ISR(void)
{
    Icu_Tim_ISRHandler(6U, 5U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM06_CH06_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM6_CH6.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM06_CH06_ISR(void)
{
    Icu_Tim_ISRHandler(6U, 6U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM06_CH07_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM6_CH7.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM06_CH07_ISR(void)
{
    Icu_Tim_ISRHandler(6U, 7U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM07_CH00_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM7_CH0.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM07_CH00_ISR(void)
{
    Icu_Tim_ISRHandler(7U, 0U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM07_CH01_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM7_CH1.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM07_CH01_ISR(void)
{
    Icu_Tim_ISRHandler(7U, 1U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM07_CH02_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM7_CH2.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM07_CH02_ISR(void)
{
    Icu_Tim_ISRHandler(7U, 2U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM07_CH03_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM7_CH3.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM07_CH03_ISR(void)
{
    Icu_Tim_ISRHandler(7U, 3U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM07_CH04_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM7_CH4.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM07_CH04_ISR(void)
{
    Icu_Tim_ISRHandler(7U, 4U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM07_CH05_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM7_CH5.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM07_CH05_ISR(void)
{
    Icu_Tim_ISRHandler(7U, 5U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM07_CH06_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM7_CH6.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM07_CH06_ISR(void)
{
    Icu_Tim_ISRHandler(7U, 6U);
}

/****************************************************************************************************
 *   Function Name           : ICU_GTM_TIM07_CH07_ISR(void)
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of ICU channel based on 
 *                             TIM7_CH7.
 *
 *   Parameters in           : 
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Icu_Irq_c_REF_3 */
void ICU_GTM_TIM07_CH07_ISR(void)
{
    Icu_Tim_ISRHandler(7U, 7U);
}
#endif
/* #Violation: Icu_Irq_c_REF_2 */
#define ICU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Icu_Irq_c_REF_1 */
#include "Icu_MemMap.h"
/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/

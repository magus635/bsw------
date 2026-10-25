/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Gpt_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, BASETIMER
*
*   brief                 : This file contains all ISR functions of Gpt Driver
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
*#Gpt_Irq_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Gpt_Irq_c_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Gpt_Irq_c_REF_3:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* SWS_Gpt_00261 */
#include"Gpt.h"
#include "Gpt_Irq.h"
#include "Mcall_Cfg.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_2 */
#define GPT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Gpt_MemMap.h"
/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM0_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM0_CH00 and/or TOM0_CH01.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM0_CH00 and/or TOM0_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH00_CH01_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(0U, 0U);

    Gpt_Gtm_ISRHandler(0U, 1U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM0_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM0_CH02 and/or TOM0_CH03.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM0_CH02 and/or TOM0_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH02_CH03_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(0U, 2U);

    Gpt_Gtm_ISRHandler(0U, 3U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM0_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM0_CH04 and/or TOM0_CH05.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM0_CH04 and/or TOM0_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH04_CH05_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(0U, 4U);

    Gpt_Gtm_ISRHandler(0U, 5U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM0_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM0_CH06 and/or TOM0_CH07.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM0_CH06 and/or TOM0_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH06_CH07_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(0U, 6U);

    Gpt_Gtm_ISRHandler(0U, 7U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM0_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM0_CH08 and/or TOM0_CH09.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM0_CH08 and/or TOM0_CH09 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH08_CH09_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(0U, 8U);

    Gpt_Gtm_ISRHandler(0U, 9U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM0_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM0_CH10 and/or TOM0_CH11.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM0_CH10 and/or TOM0_CH11 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH10_CH11_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(0U, 10U);

    Gpt_Gtm_ISRHandler(0U, 11U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM0_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM0_CH12 and/or TOM0_CH13.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM0_CH12 and/or TOM0_CH13 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH12_CH13_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(0U, 12U);

    Gpt_Gtm_ISRHandler(0U, 13U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM0_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM0_CH14 and/or TOM0_CH15.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM0_CH14 and/or TOM0_CH15 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM0_CH14_CH15_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(0U, 14U);

    Gpt_Gtm_ISRHandler(0U, 15U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM1_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM1_CH00 and/or TOM1_CH01.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM1_CH00 and/or TOM1_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH00_CH01_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(1U, 0U);

    Gpt_Gtm_ISRHandler(1U, 1U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM1_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM1_CH02 and/or TOM1_CH03.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM1_CH02 and/or TOM1_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH02_CH03_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(1U, 2U);

    Gpt_Gtm_ISRHandler(1U, 3U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM1_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM1_CH04 and/or TOM1_CH05.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM1_CH04 and/or TOM1_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH04_CH05_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(1U, 4U);

    Gpt_Gtm_ISRHandler(1U, 5U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM1_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM1_CH06 and/or TOM1_CH07.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM1_CH06 and/or TOM1_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH06_CH07_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(1U, 6U);

    Gpt_Gtm_ISRHandler(1U, 7U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM1_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM1_CH08 and/or TOM1_CH09.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM1_CH08 and/or TOM1_CH09 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH08_CH09_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(1U, 8U);

    Gpt_Gtm_ISRHandler(1U, 9U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM1_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM1_CH10 and/or TOM1_CH11.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM1_CH10 and/or TOM1_CH11 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH10_CH11_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(1U, 10U);

    Gpt_Gtm_ISRHandler(1U, 11U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM1_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM1_CH12 and/or TOM1_CH13.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM1_CH12 and/or TOM1_CH13 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH12_CH13_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(1U, 12U);

    Gpt_Gtm_ISRHandler(1U, 13U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM1_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM1_CH14 and/or TOM1_CH15.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM1_CH14 and/or TOM1_CH15 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM1_CH14_CH15_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(1U, 14U);

    Gpt_Gtm_ISRHandler(1U, 15U);
}
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM2_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM2_CH00 and/or TOM2_CH01.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM2_CH00 and/or TOM2_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH00_CH01_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(2U, 0U);

    Gpt_Gtm_ISRHandler(2U, 1U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM2_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM2_CH02 and/or TOM2_CH03.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM2_CH02 and/or TOM2_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH02_CH03_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(2U, 2U);

    Gpt_Gtm_ISRHandler(2U, 3U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM2_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM2_CH04 and/or TOM2_CH05.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM2_CH04 and/or TOM2_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH04_CH05_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(2U, 4U);

    Gpt_Gtm_ISRHandler(2U, 5U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM2_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM2_CH06 and/or TOM2_CH07.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM2_CH06 and/or TOM2_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH06_CH07_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(2U, 6U);

    Gpt_Gtm_ISRHandler(2U, 7U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM2_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM2_CH08 and/or TOM2_CH09.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM2_CH08 and/or TOM2_CH09 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH08_CH09_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(2U, 8U);

    Gpt_Gtm_ISRHandler(2U, 9U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM2_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM2_CH10 and/or TOM2_CH11.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM2_CH10 and/or TOM2_CH11 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH10_CH11_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(2U, 10U);

    Gpt_Gtm_ISRHandler(2U, 11U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM2_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM2_CH12 and/or TOM2_CH13.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM2_CH12 and/or TOM2_CH13 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH12_CH13_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(2U, 12U);

    Gpt_Gtm_ISRHandler(2U, 13U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM2_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM2_CH14 and/or TOM2_CH15.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM2_CH14 and/or TOM2_CH15 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM2_CH14_CH15_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(2U, 14U);

    Gpt_Gtm_ISRHandler(2U, 15U);
}
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM3_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM3_CH00 and/or TOM3_CH01.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM3_CH00 and/or TOM3_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH00_CH01_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(3U, 0U);

    Gpt_Gtm_ISRHandler(3U, 1U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM3_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM3_CH02 and/or TOM3_CH03.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM3_CH02 and/or TOM3_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH02_CH03_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(3U, 2U);

    Gpt_Gtm_ISRHandler(3U, 3U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM3_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM3_CH04 and/or TOM3_CH05.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM3_CH04 and/or TOM3_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH04_CH05_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(3U, 4U);

    Gpt_Gtm_ISRHandler(3U, 5U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM3_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM3_CH06 and/or TOM3_CH07.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM3_CH06 and/or TOM3_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH06_CH07_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(3U, 6U);

    Gpt_Gtm_ISRHandler(3U, 7U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM3_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM3_CH08 and/or TOM3_CH09.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM3_CH08 and/or TOM3_CH09 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH08_CH09_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(3U, 8U);

    Gpt_Gtm_ISRHandler(3U, 9U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM3_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM3_CH10 and/or TOM3_CH11.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM3_CH10 and/or TOM3_CH11 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH10_CH11_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(3U, 10U);

    Gpt_Gtm_ISRHandler(3U, 11U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM3_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM3_CH12 and/or TOM3_CH13.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM3_CH12 and/or TOM3_CH13 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH12_CH13_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(3U, 12U);

    Gpt_Gtm_ISRHandler(3U, 13U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM3_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM3_CH14 and/or TOM3_CH15.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM3_CH14 and/or TOM3_CH15 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM3_CH14_CH15_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(3U, 14U);

    Gpt_Gtm_ISRHandler(3U, 15U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM4_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM4_CH00 and/or TOM4_CH01.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM4_CH00 and/or TOM4_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH00_CH01_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(4U, 0U);

    Gpt_Gtm_ISRHandler(4U, 1U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM4_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM4_CH02 and/or TOM4_CH03.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM4_CH02 and/or TOM4_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH02_CH03_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(4U, 2U);

    Gpt_Gtm_ISRHandler(4U, 3U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM4_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM4_CH04 and/or TOM4_CH05.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM4_CH04 and/or TOM4_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH04_CH05_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(4U, 4U);

    Gpt_Gtm_ISRHandler(4U, 5U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM4_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM4_CH06 and/or TOM4_CH07.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM4_CH06 and/or TOM4_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH06_CH07_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(4U, 6U);

    Gpt_Gtm_ISRHandler(4U, 7U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM4_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM4_CH08 and/or TOM4_CH09.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM4_CH08 and/or TOM4_CH09 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH08_CH09_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(4U, 8U);

    Gpt_Gtm_ISRHandler(4U, 9U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM4_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM4_CH10 and/or TOM4_CH11.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM4_CH10 and/or TOM4_CH11 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH10_CH11_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(4U, 10U);

    Gpt_Gtm_ISRHandler(4U, 11U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM4_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM4_CH12 and/or TOM4_CH13.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM4_CH12 and/or TOM4_CH13 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH12_CH13_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(4U, 12U);

    Gpt_Gtm_ISRHandler(4U, 13U);
}

/****************************************************************************************************
 *   Function Name           : GPT_GTM_TOM4_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on 
 *                             TOM4_CH14 and/or TOM4_CH15.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of TOM4_CH14 and/or TOM4_CH15 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_GTM_TOM4_CH14_CH15_ISR
(
    void
)
{
    Gpt_Gtm_ISRHandler(4U, 14U);

    Gpt_Gtm_ISRHandler(4U, 15U);
}
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
/****************************************************************************************************
 *   Function Name           : GPT_BASETIMER_0_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on BASETIMER_0.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of BASETIMER_0 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_0_ISR
(
    void
)
{
  Gpt_Basetimer_ISRHandler(0U);
}
/****************************************************************************************************
 *   Function Name           : GPT_BASETIMER_1_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on BASETIMER_1.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of BASETIMER_1 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_1_ISR
(
    void
)
{
  Gpt_Basetimer_ISRHandler(1U);
}
/****************************************************************************************************
 *   Function Name           : GPT_BASETIMER_2_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on BASETIMER_2.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of BASETIMER_2 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_2_ISR
(
    void
)
{
  Gpt_Basetimer_ISRHandler(2U);
}
/****************************************************************************************************
 *   Function Name           : GPT_BASETIMER_3_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on BASETIMER_3.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of BASETIMER_3 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_3_ISR
(
    void
)
{
  Gpt_Basetimer_ISRHandler(3U);
}
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)) 
/****************************************************************************************************
 *   Function Name           : GPT_BASETIMER_4_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on BASETIMER_4.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of BASETIMER_4 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_4_ISR
(
    void
)
{
  Gpt_Basetimer_ISRHandler(4U);
}
/****************************************************************************************************
 *   Function Name           : GPT_BASETIMER_5_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of GPT channel based on BASETIMER_5.
 *
 *   Parameters in           : void.
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
 *   Preconditions           : The interrupt of BASETIMER_5 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Gpt_Irq_c_REF_3 */
FUNC(void, GPT_PUBLIC_CODE) GPT_BASETIMER_5_ISR
(
    void
)
{
  Gpt_Basetimer_ISRHandler(5U);
}
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
/* #Violation: Gpt_Irq_c_REF_2 */
#define GPT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Gpt_Irq_c_REF_1 */
#include "Gpt_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


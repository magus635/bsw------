/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Pwm_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
*
*   brief                 : This file contains all ISR functions of PWM Driver
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
*#Pwm_Irq_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Pwm_Irq_c_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Pwm_Irq_c_REF_3:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* SWS_Pwm_70075:
 * Pwm_Irq.c shall include Pwm.h */
#include "Pwm.h"
#include "Pwm_Irq.h"
#include "Mcall_Cfg.h"


/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_2 */
#define PWM_START_SEC_CODE_ASIL_D_GLOBAL
#include "Pwm_MemMap.h"

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM0_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of TOM0_CH00 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 0U);
    /* Handle the interrupt of TOM0_CH01 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM0_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of TOM0_CH02 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 2U);
    /* Handle the interrupt of TOM0_CH03 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM0_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of TOM0_CH04 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 4U);
    /* Handle the interrupt of TOM0_CH05 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM0_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of TOM0_CH06 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 6U);
    /* Handle the interrupt of TOM0_CH07 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM0_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH08_CH09_ISR
(
    void
)
{
    /* Handle the interrupt of TOM0_CH08 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 8U);
    /* Handle the interrupt of TOM0_CH09 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 9U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM0_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH10_CH11_ISR
(
    void
)
{
    /* Handle the interrupt of TOM0_CH10 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 10U);
    /* Handle the interrupt of TOM0_CH11 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 11U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM0_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH12_CH13_ISR
(
    void
)
{
    /* Handle the interrupt of TOM0_CH12 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 12U);
    /* Handle the interrupt of TOM0_CH13 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 13U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM0_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM0_CH14_CH15_ISR
(
    void
)
{
    /* Handle the interrupt of TOM0_CH14 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 14U);
    /* Handle the interrupt of TOM0_CH15 */
    Pwm_DutyPeriod_ISRHandler(0U, 0U, 15U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM1_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of TOM1_CH00 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 0U);
    /* Handle the interrupt of TOM1_CH01 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM1_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of TOM1_CH02 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 2U);
    /* Handle the interrupt of TOM1_CH03 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM1_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of TOM1_CH04 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 4U);
    /* Handle the interrupt of TOM1_CH05 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM1_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of TOM1_CH06 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 6U);
    /* Handle the interrupt of TOM1_CH07 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM1_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH08_CH09_ISR
(
    void
)
{
    /* Handle the interrupt of TOM1_CH08 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 8U);
    /* Handle the interrupt of TOM1_CH09 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 9U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM1_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH10_CH11_ISR
(
    void
)
{
    /* Handle the interrupt of TOM1_CH10 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 10U);
    /* Handle the interrupt of TOM1_CH11 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 11U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM1_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH12_CH13_ISR
(
    void
)
{
    /* Handle the interrupt of TOM1_CH12 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 12U);
    /* Handle the interrupt of TOM1_CH13 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 13U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM1_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM1_CH14_CH15_ISR
(
    void
)
{
    /* Handle the interrupt of TOM1_CH14 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 14U);
    /* Handle the interrupt of TOM1_CH15 */
    Pwm_DutyPeriod_ISRHandler(0U, 1U, 15U);
}
#if ((MCAL_PROCESSOR_CAT ==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM2_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of TOM2_CH00 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 0U);
    /* Handle the interrupt of TOM2_CH01 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM2_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of TOM2_CH02 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 2U);
    /* Handle the interrupt of TOM2_CH03 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM2_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of TOM2_CH04 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 4U);
    /* Handle the interrupt of TOM2_CH05 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM2_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of TOM2_CH06 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 6U);
    /* Handle the interrupt of TOM2_CH07 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM2_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH08_CH09_ISR
(
    void
)
{
    /* Handle the interrupt of TOM2_CH08 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 8U);
    /* Handle the interrupt of TOM2_CH09 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 9U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM2_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH10_CH11_ISR
(
    void
)
{
    /* Handle the interrupt of TOM2_CH10 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 10U);
    /* Handle the interrupt of TOM2_CH11 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 11U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM2_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH12_CH13_ISR
(
    void
)
{
    /* Handle the interrupt of TOM2_CH12 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 12U);
    /* Handle the interrupt of TOM2_CH13 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 13U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM2_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM2_CH14_CH15_ISR
(
    void
)
{
    /* Handle the interrupt of TOM2_CH14 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 14U);
    /* Handle the interrupt of TOM2_CH15 */
    Pwm_DutyPeriod_ISRHandler(0U, 2U, 15U);
}
#endif /* (MCAL_PROCESSOR_CAT \==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM3_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of TOM3_CH00 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 0U);
    /* Handle the interrupt of TOM3_CH01 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM3_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of TOM3_CH02 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 2U);
    /* Handle the interrupt of TOM3_CH03 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM3_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of TOM3_CH04 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 4U);
    /* Handle the interrupt of TOM3_CH05 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM3_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of TOM3_CH06 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 6U);
    /* Handle the interrupt of TOM3_CH07 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM3_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH08_CH09_ISR
(
    void
)
{
    /* Handle the interrupt of TOM3_CH08 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 8U);
    /* Handle the interrupt of TOM3_CH09 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 9U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM3_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH10_CH11_ISR
(
    void
)
{
    /* Handle the interrupt of TOM3_CH10 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 10U);
    /* Handle the interrupt of TOM3_CH11 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 11U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM3_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH12_CH13_ISR
(
    void
)
{
    /* Handle the interrupt of TOM3_CH12 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 12U);
    /* Handle the interrupt of TOM3_CH13 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 13U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM3_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM3_CH14_CH15_ISR
(
    void
)
{
    /* Handle the interrupt of TOM3_CH14 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 14U);
    /* Handle the interrupt of TOM3_CH15 */
    Pwm_DutyPeriod_ISRHandler(0U, 3U, 15U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM4_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of TOM4_CH00 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 0U);
    /* Handle the interrupt of TOM4_CH01 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM4_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of TOM4_CH02 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 2U);
    /* Handle the interrupt of TOM4_CH03 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM4_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of TOM4_CH04 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 4U);
    /* Handle the interrupt of TOM4_CH05 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM4_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of TOM4_CH06 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 6U);
    /* Handle the interrupt of TOM4_CH07 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM4_CH08_CH09_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH08_CH09_ISR
(
    void
)
{
    /* Handle the interrupt of TOM4_CH08 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 8U);
    /* Handle the interrupt of TOM4_CH09 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 9U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM4_CH10_CH11_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH10_CH11_ISR
(
    void
)
{
    /* Handle the interrupt of TOM4_CH10 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 10U);
    /* Handle the interrupt of TOM4_CH11 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 11U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM4_CH12_CH13_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH12_CH13_ISR
(
    void
)
{
    /* Handle the interrupt of TOM4_CH12 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 12U);
    /* Handle the interrupt of TOM4_CH13 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 13U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_TOM4_CH14_CH15_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
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
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_TOM4_CH14_CH15_ISR
(
    void
)
{
    /* Handle the interrupt of TOM4_CH14 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 14U);
    /* Handle the interrupt of TOM4_CH15 */
    Pwm_DutyPeriod_ISRHandler(0U, 4U, 15U);
}
#endif /* MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516 */

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM0_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM0_CH00 and/or ATOM0_CH01.
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
 *   Preconditions           : The interrupt of ATOM0_CH00 and/or ATOM0_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM0_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM0_CH00 */
    Pwm_DutyPeriod_ISRHandler(1U, 0U, 0U);
    /* Handle the interrupt of ATOM0_CH01 */
    Pwm_DutyPeriod_ISRHandler(1U, 0U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM0_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM0_CH02 and/or ATOM0_CH03.
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
 *   Preconditions           : The interrupt of ATOM0_CH02 and/or ATOM0_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM0_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM0_CH02 */
    Pwm_DutyPeriod_ISRHandler(1U, 0U, 2U);
    /* Handle the interrupt of ATOM0_CH03 */
    Pwm_DutyPeriod_ISRHandler(1U, 0U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM0_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM0_CH04 and/or ATOM0_CH05.
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
 *   Preconditions           : The interrupt of ATOM0_CH04 and/or ATOM0_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM0_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM0_CH04 */
    Pwm_DutyPeriod_ISRHandler(1U, 0U, 4U);
    /* Handle the interrupt of ATOM0_CH05 */
    Pwm_DutyPeriod_ISRHandler(1U, 0U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM0_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM0_CH06 and/or ATOM0_CH07.
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
 *   Preconditions           : The interrupt of ATOM0_CH06 and/or ATOM0_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM0_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM0_CH06 */
    Pwm_DutyPeriod_ISRHandler(1U, 0U, 6U);
    /* Handle the interrupt of ATOM0_CH07 */
    Pwm_DutyPeriod_ISRHandler(1U, 0U, 7U);
}

#if ((MCAL_PROCESSOR_CAT ==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM1_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM1_CH00 and/or ATOM1_CH01.
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
 *   Preconditions           : The interrupt of ATOM1_CH00 and/or ATOM1_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM1_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM1_CH00 */
    Pwm_DutyPeriod_ISRHandler(1U, 1U, 0U);
    /* Handle the interrupt of ATOM1_CH01 */
    Pwm_DutyPeriod_ISRHandler(1U, 1U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM1_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM1_CH02 and/or ATOM1_CH03.
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
 *   Preconditions           : The interrupt of ATOM1_CH02 and/or ATOM1_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM1_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM1_CH02 */
    Pwm_DutyPeriod_ISRHandler(1U, 1U, 2U);
    /* Handle the interrupt of ATOM1_CH03 */
    Pwm_DutyPeriod_ISRHandler(1U, 1U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM1_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM1_CH04 and/or ATOM1_CH05.
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
 *   Preconditions           : The interrupt of ATOM1_CH04 and/or ATOM1_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM1_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM1_CH04 */
    Pwm_DutyPeriod_ISRHandler(1U, 1U, 4U);
    /* Handle the interrupt of ATOM1_CH05 */
    Pwm_DutyPeriod_ISRHandler(1U, 1U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM1_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM1_CH06 and/or ATOM1_CH07.
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
 *   Preconditions           : The interrupt of ATOM1_CH06 and/or ATOM1_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM1_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM1_CH06 */
    Pwm_DutyPeriod_ISRHandler(1U, 1U, 6U);
    /* Handle the interrupt of ATOM1_CH07 */
    Pwm_DutyPeriod_ISRHandler(1U, 1U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM2_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM2_CH00 and/or ATOM2_CH01.
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
 *   Preconditions           : The interrupt of ATOM2_CH00 and/or ATOM2_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM2_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM2_CH00 */
    Pwm_DutyPeriod_ISRHandler(1U, 2U, 0U);
    /* Handle the interrupt of ATOM2_CH01 */
    Pwm_DutyPeriod_ISRHandler(1U, 2U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM2_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM2_CH02 and/or ATOM2_CH03.
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
 *   Preconditions           : The interrupt of ATOM2_CH02 and/or ATOM2_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM2_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM2_CH02 */
    Pwm_DutyPeriod_ISRHandler(1U, 2U, 2U);
    /* Handle the interrupt of ATOM2_CH03 */
    Pwm_DutyPeriod_ISRHandler(1U, 2U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM2_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM2_CH04 and/or ATOM2_CH05.
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
 *   Preconditions           : The interrupt of ATOM2_CH04 and/or ATOM2_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM2_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM2_CH04 */
    Pwm_DutyPeriod_ISRHandler(1U, 2U, 4U);
    /* Handle the interrupt of ATOM2_CH05 */
    Pwm_DutyPeriod_ISRHandler(1U, 2U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM2_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM2_CH06 and/or ATOM2_CH07.
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
 *   Preconditions           : The interrupt of ATOM2_CH06 and/or ATOM2_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM2_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM2_CH06 */
    Pwm_DutyPeriod_ISRHandler(1U, 2U, 6U);
    /* Handle the interrupt of ATOM2_CH07 */
    Pwm_DutyPeriod_ISRHandler(1U, 2U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM3_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM3_CH00 and/or ATOM3_CH01.
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
 *   Preconditions           : The interrupt of ATOM3_CH00 and/or ATOM3_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM3_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM3_CH00 */
    Pwm_DutyPeriod_ISRHandler(1U, 3U, 0U);
    /* Handle the interrupt of ATOM3_CH01 */
    Pwm_DutyPeriod_ISRHandler(1U, 3U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM3_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM3_CH02 and/or ATOM3_CH03.
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
 *   Preconditions           : The interrupt of ATOM3_CH02 and/or ATOM3_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM3_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM3_CH02 */
    Pwm_DutyPeriod_ISRHandler(1U, 3U, 2U);
    /* Handle the interrupt of ATOM3_CH03 */
    Pwm_DutyPeriod_ISRHandler(1U, 3U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM3_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM3_CH04 and/or ATOM3_CH05.
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
 *   Preconditions           : The interrupt of ATOM3_CH04 and/or ATOM3_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM3_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM3_CH04 */
    Pwm_DutyPeriod_ISRHandler(1U, 3U, 4U);
    /* Handle the interrupt of ATOM3_CH05 */
    Pwm_DutyPeriod_ISRHandler(1U, 3U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM3_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM3_CH06 and/or ATOM3_CH07.
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
 *   Preconditions           : The interrupt of ATOM3_CH06 and/or ATOM3_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM3_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM3_CH06 */
    Pwm_DutyPeriod_ISRHandler(1U, 3U, 6U);
    /* Handle the interrupt of ATOM3_CH07 */
    Pwm_DutyPeriod_ISRHandler(1U, 3U, 7U);
}
#endif /* (MCAL_PROCESSOR_CAT \==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM4_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM4_CH00 and/or ATOM4_CH01.
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
 *   Preconditions           : The interrupt of ATOM4_CH00 and/or ATOM4_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM4_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM4_CH00 */
    Pwm_DutyPeriod_ISRHandler(1U, 4U, 0U);
    /* Handle the interrupt of ATOM4_CH01 */
    Pwm_DutyPeriod_ISRHandler(1U, 4U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM4_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM4_CH02 and/or ATOM4_CH03.
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
 *   Preconditions           : The interrupt of ATOM4_CH02 and/or ATOM4_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM4_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM4_CH02 */
    Pwm_DutyPeriod_ISRHandler(1U, 4U, 2U);
    /* Handle the interrupt of ATOM4_CH03 */
    Pwm_DutyPeriod_ISRHandler(1U, 4U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM4_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM4_CH04 and/or ATOM4_CH05.
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
 *   Preconditions           : The interrupt of ATOM4_CH04 and/or ATOM4_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM4_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM4_CH04 */
    Pwm_DutyPeriod_ISRHandler(1U, 4U, 4U);
    /* Handle the interrupt of ATOM4_CH05 */
    Pwm_DutyPeriod_ISRHandler(1U, 4U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM4_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM4_CH06 and/or ATOM4_CH07.
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
 *   Preconditions           : The interrupt of ATOM4_CH06 and/or ATOM4_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM4_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM4_CH06 */
    Pwm_DutyPeriod_ISRHandler(1U, 4U, 6U);
    /* Handle the interrupt of ATOM4_CH07 */
    Pwm_DutyPeriod_ISRHandler(1U, 4U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM5_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM5_CH00 and/or ATOM5_CH01.
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
 *   Preconditions           : The interrupt of ATOM5_CH00 and/or ATOM5_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM5_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM5_CH00 */
    Pwm_DutyPeriod_ISRHandler(1U, 5U, 0U);
    /* Handle the interrupt of ATOM5_CH01 */
    Pwm_DutyPeriod_ISRHandler(1U, 5U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM5_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM5_CH02 and/or ATOM5_CH03.
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
 *   Preconditions           : The interrupt of ATOM5_CH02 and/or ATOM5_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM5_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM5_CH02 */
    Pwm_DutyPeriod_ISRHandler(1U, 5U, 2U);
    /* Handle the interrupt of ATOM5_CH03 */
    Pwm_DutyPeriod_ISRHandler(1U, 5U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM5_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM5_CH04 and/or ATOM5_CH05.
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
 *   Preconditions           : The interrupt of ATOM5_CH04 and/or ATOM5_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM5_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM5_CH04 */
    Pwm_DutyPeriod_ISRHandler(1U, 5U, 4U);
    /* Handle the interrupt of ATOM5_CH05 */
    Pwm_DutyPeriod_ISRHandler(1U, 5U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM5_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM5_CH06 and/or ATOM5_CH07.
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
 *   Preconditions           : The interrupt of ATOM5_CH06 and/or ATOM5_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM5_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM5_CH06 */
    Pwm_DutyPeriod_ISRHandler(1U, 5U, 6U);
    /* Handle the interrupt of ATOM5_CH07 */
    Pwm_DutyPeriod_ISRHandler(1U, 5U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM6_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM6_CH00 and/or ATOM6_CH01.
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
 *   Preconditions           : The interrupt of ATOM6_CH00 and/or ATOM6_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM6_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM6_CH00 */
    Pwm_DutyPeriod_ISRHandler(1U, 6U, 0U);
    /* Handle the interrupt of ATOM6_CH01 */
    Pwm_DutyPeriod_ISRHandler(1U, 6U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM6_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM6_CH02 and/or ATOM6_CH03.
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
 *   Preconditions           : The interrupt of ATOM6_CH02 and/or ATOM6_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM6_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM6_CH02 */
    Pwm_DutyPeriod_ISRHandler(1U, 6U, 2U);
    /* Handle the interrupt of ATOM6_CH03 */
    Pwm_DutyPeriod_ISRHandler(1U, 6U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM6_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM6_CH04 and/or ATOM6_CH05.
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
 *   Preconditions           : The interrupt of ATOM6_CH04 and/or ATOM6_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM6_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM6_CH04 */
    Pwm_DutyPeriod_ISRHandler(1U, 6U, 4U);
    /* Handle the interrupt of ATOM6_CH05 */
    Pwm_DutyPeriod_ISRHandler(1U, 6U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM6_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM6_CH06 and/or ATOM6_CH07.
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
 *   Preconditions           : The interrupt of ATOM6_CH06 and/or ATOM6_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM6_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM6_CH06 */
    Pwm_DutyPeriod_ISRHandler(1U, 6U, 6U);
    /* Handle the interrupt of ATOM6_CH07 */
    Pwm_DutyPeriod_ISRHandler(1U, 6U, 7U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM7_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM7_CH00 and/or ATOM7_CH01.
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
 *   Preconditions           : The interrupt of ATOM7_CH00 and/or ATOM7_CH01 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM7_CH00_CH01_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM7_CH00 */
    Pwm_DutyPeriod_ISRHandler(1U, 7U, 0U);
    /* Handle the interrupt of ATOM7_CH01 */
    Pwm_DutyPeriod_ISRHandler(1U, 7U, 1U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM7_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM7_CH02 and/or ATOM7_CH03.
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
 *   Preconditions           : The interrupt of ATOM7_CH02 and/or ATOM7_CH03 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM7_CH02_CH03_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM7_CH02 */
    Pwm_DutyPeriod_ISRHandler(1U, 7U, 2U);
    /* Handle the interrupt of ATOM7_CH03 */
    Pwm_DutyPeriod_ISRHandler(1U, 7U, 3U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM7_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM7_CH04 and/or ATOM7_CH05.
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
 *   Preconditions           : The interrupt of ATOM7_CH04 and/or ATOM7_CH05 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM7_CH04_CH05_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM7_CH04 */
    Pwm_DutyPeriod_ISRHandler(1U, 7U, 4U);
    /* Handle the interrupt of ATOM7_CH05 */
    Pwm_DutyPeriod_ISRHandler(1U, 7U, 5U);
}

/****************************************************************************************************
 *   Function Name           : PWM_GTM_ATOM7_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of PWM channel based on 
 *                             ATOM7_CH06 and/or ATOM7_CH07.
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
 *   Preconditions           : The interrupt of ATOM7_CH06 and/or ATOM7_CH07 are(is) enabled
 *                             and the interrupt are(is) triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Pwm_Irq_c_REF_3 */
FUNC(void, PWM_PUBLIC_CODE) PWM_GTM_ATOM7_CH06_CH07_ISR
(
    void
)
{
    /* Handle the interrupt of ATOM7_CH06 */
    Pwm_DutyPeriod_ISRHandler(1U, 7U, 6U);
    /* Handle the interrupt of ATOM7_CH07 */
    Pwm_DutyPeriod_ISRHandler(1U, 7U, 7U);
}
#endif /* CAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516 */

/* #Violation: Pwm_Irq_c_REF_2 */
#define PWM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Pwm_Irq_c_REF_1 */
#include "Pwm_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


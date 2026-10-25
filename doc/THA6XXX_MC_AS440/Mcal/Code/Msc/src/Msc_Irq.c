/****************************************************************************************************
*   FileName              : Msc_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MSC
*
*   brief                 : This file contains all ISR functions of Spi Driver
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
*#Msc_Irq_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Msc_Irq_c_REF_2:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Msc.h"
#include "Msc_Irq.h"
#include "Mcall_Cfg.h"
/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#define MSC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Msc_Irq_c_REF_1 */
#include "Msc_MemMap.h"

#if ((MCAL_PROCESSOR_CAT ==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
 *   Function Name           : MSC0_SR0_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node0.
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
 *   Preconditions           : The interrupt of Msc0 service node0 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC0_SR0_ISR
(
    void
)
{
    Msc_ISRHandler(0U, 0U);
}

/****************************************************************************************************
 *   Function Name           : MSC0_SR1_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node1.
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
 *   Preconditions           : The interrupt of Msc0 service node1 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC0_SR1_ISR
(
    void
)
{
    Msc_ISRHandler(0U, 1U);
}

/****************************************************************************************************
 *   Function Name           : MSC0_SR2_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node2.
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
 *   Preconditions           : The interrupt of Msc0 service node2 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC0_SR2_ISR
(
    void
)
{
    Msc_ISRHandler(0U, 2U);
}

/****************************************************************************************************
 *   Function Name           : MSC0_SR3_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node3.
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
 *   Preconditions           : The interrupt of Msc0 service node3 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC0_SR3_ISR
(
    void
)
{
    Msc_ISRHandler(0U, 3U);
}

/****************************************************************************************************
 *   Function Name           : MSC0_SR4_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node4.
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
 *   Preconditions           : The interrupt of Msc0 service node4 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC0_SR4_ISR
(
    void
)
{
    Msc_ISRHandler(0U, 4U);
}
#endif /* (MCAL_PROCESSOR_CAT \==MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
/****************************************************************************************************
 *   Function Name           : MSC1_SR0_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node0.
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
 *   Preconditions           : The interrupt of Msc1 service node0 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC1_SR0_ISR
(
    void
)
{
    Msc_ISRHandler(1U, 0U);
}

/****************************************************************************************************
 *   Function Name           : MSC1_SR1_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node1.
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
 *   Preconditions           : The interrupt of Msc1 service node1 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC1_SR1_ISR
(
    void
)
{
    Msc_ISRHandler(1U, 1U);
}

/****************************************************************************************************
 *   Function Name           : MSC1_SR2_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node2.
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
 *   Preconditions           : The interrupt of Msc1 service node2 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC1_SR2_ISR
(
    void
)
{
    Msc_ISRHandler(1U, 2U);
}

/****************************************************************************************************
 *   Function Name           : MSC1_SR3_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node3.
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
 *   Preconditions           : The interrupt of Msc1 service node3 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC1_SR3_ISR
(
    void
)
{
    Msc_ISRHandler(1U, 3U);
}

/****************************************************************************************************
 *   Function Name           : MSC1_SR4_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node4.
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
 *   Preconditions           : The interrupt of Msc1 service node4 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC1_SR4_ISR
(
    void
)
{
    Msc_ISRHandler(1U, 4U);
}

/****************************************************************************************************
 *   Function Name           : MSC2_SR0_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node0.
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
 *   Preconditions           : The interrupt of Msc2 service node0 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC2_SR0_ISR
(
    void
)
{
    Msc_ISRHandler(2U, 0U);
}

/****************************************************************************************************
 *   Function Name           : MSC2_SR1_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node1.
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
 *   Preconditions           : The interrupt of Msc2 service node1 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC2_SR1_ISR
(
    void
)
{
    Msc_ISRHandler(2U, 1U);
}

/****************************************************************************************************
 *   Function Name           : MSC2_SR2_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node2.
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
 *   Preconditions           : The interrupt of Msc2 service node2 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC2_SR2_ISR
(
    void
)
{
    Msc_ISRHandler(2U, 2U);
}

/****************************************************************************************************
 *   Function Name           : MSC2_SR3_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node3.
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
 *   Preconditions           : The interrupt of Msc2 service node3 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC2_SR3_ISR
(
    void
)
{
    Msc_ISRHandler(2U, 3U);
}

/****************************************************************************************************
 *   Function Name           : MSC2_SR4_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of Msc0 interrupt service node4.
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
 *   Preconditions           : The interrupt of Msc2 service node4 is enabled
 *                             and the interrupt is triggered.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Msc_Irq_c_REF_2 */
FUNC(void, MSC_PUBLIC_CODE) MSC2_SR4_ISR
(
    void
)
{
    Msc_ISRHandler(2U, 4U);
}
#endif /* MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516 */

#define MSC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Msc_Irq_c_REF_1 */
#include "Msc_MemMap.h"

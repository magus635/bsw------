/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Ocu_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                 : This file contains all ISR functions of OCU Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Ocu_Irq_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Ocu_Irq_c_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Ocu_Irq_c_REF_3:MISRAC2012-Rule-2.1; 
* Justification: Reserved API for user access.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Ocu_Irq.h"
/* SWS_Ocu_00008:
 * Ocu_PBcfg.c shall include Ocu.h */
#include "Ocu.h"
#include "Mcall_Cfg.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Ocu_Irq_c_REF_2*/
#define OCU_START_SEC_CODE_ASIL_D_GLOBAL
#include "Ocu_MemMap.h"

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM0_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM0_CH00_CH01_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(0U, 0U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(0U, 1U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM0_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM0_CH02_CH03_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(0U, 2U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(0U, 3U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM0_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM0_CH04_CH05_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(0U, 4U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(0U, 5U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM0_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM0_CH06_CH07_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(0U, 6U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(0U, 7U);
}

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM1_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM1_CH00_CH01_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(1U, 0U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(1U, 1U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM1_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM1_CH02_CH03_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(1U, 2U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(1U, 3U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM1_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM1_CH04_CH05_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(1U, 4U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(1U, 5U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM1_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM1_CH06_CH07_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(1U, 6U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(1U, 7U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM2_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM2_CH00_CH01_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(2U, 0U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(2U, 1U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM2_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM2_CH02_CH03_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(2U, 2U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(2U, 3U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM2_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM2_CH04_CH05_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(2U, 4U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(2U, 5U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM2_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM2_CH06_CH07_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(2U, 6U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(2U, 7U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM3_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM3_CH00_CH01_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(3U, 0U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(3U, 1U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM3_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM3_CH02_CH03_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(3U, 2U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(3U, 3U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM3_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM3_CH04_CH05_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(3U, 4U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(3U, 5U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM3_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM3_CH06_CH07_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(3U, 6U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(3U, 7U);
}
#endif /* (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM4_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM4_CH00_CH01_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(4U, 0U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(4U, 1U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM4_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM4_CH02_CH03_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(4U, 2U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(4U, 3U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM4_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM4_CH04_CH05_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(4U, 4U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(4U, 5U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM4_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM4_CH06_CH07_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(4U, 6U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(4U, 7U);
}
/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM5_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM5_CH00_CH01_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(5U, 0U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(5U, 1U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM5_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM5_CH02_CH03_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(5U, 2U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(5U, 3U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM5_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM5_CH04_CH05_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(5U, 4U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(5U, 5U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM5_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM5_CH06_CH07_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(5U, 6U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(5U, 7U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM6_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM6_CH00_CH01_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(6U, 0U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(6U, 1U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM6_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM6_CH02_CH03_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(6U, 2U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(6U, 3U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM6_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM6_CH04_CH05_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(6U, 4U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(6U, 5U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM6_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM6_CH06_CH07_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(6U, 6U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(6U, 7U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM7_CH00_CH01_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM7_CH00_CH01_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(7U, 0U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(7U, 1U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM7_CH02_CH03_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM7_CH02_CH03_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(7U, 2U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(7U, 3U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM7_CH04_CH05_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM7_CH04_CH05_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(7U, 4U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(7U, 5U);
}

/****************************************************************************************************
 *   Function Name           : OCU_GTM_ATOM7_CH06_CH07_ISR
 *
 *   Service ID              : None.
 *
 *   Description             : This API is the ISR function of OCU channel based on 
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
/* #Violation: Ocu_Irq_c_REF_3 */
FUNC(void, OCU_PUBLIC_CODE) OCU_GTM_ATOM7_CH06_CH07_ISR
(
    void
)
{
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(7U, 6U);
    Ocu_Gtm_Atom_CompareMatch_ISRHandler(7U, 7U);
}
#endif /* MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516 */
/* #Violation: Ocu_Irq_c_REF_2*/
#define OCU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Ocu_Irq_c_REF_1*/
#include "Ocu_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


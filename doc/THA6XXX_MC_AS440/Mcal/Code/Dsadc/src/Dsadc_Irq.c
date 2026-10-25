/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dsadc_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DSADC
*
*   brief                 : This file contains all ISR functions of Dsadc Driver
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
*#Dsadc_Irq_c_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the
*   driver must be placed.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dsadc_Irq.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dsadc_MemMap.h"

/****************************************************************************************************
*   Function Name           : Dsadc_DSADCmSRn<m = HW unit identifier, n = A(Auxiliary) or M(Main)>
*
*   Service ID              : None
*
*   Description             : Interrupt routine entry of DSADC auxiliary or Main channel service
*                               request.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : None.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
#if (defined(DSADC_HWUNIT_DSADC0) && (DSADC_HWUNIT_DSADC0 == 0U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC0) && (DSADC_HWUNIT_INT_EN_DSADC0 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC0) && (DSADC_HWUNIT_AUX_INT_EN_DSADC0 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC0SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC0);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC0) && (DSADC_HWUNIT_AUX_INT_EN_DSADC0 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC0SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC0);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC0) && (DSADC_HWUNIT_INT_EN_DSADC0 == STD_ON)) */
#endif /* \(defined(DSADC_HWUNIT_DSADC0) && (DSADC_HWUNIT_DSADC0 == 0U)) */

#if (defined(DSADC_HWUNIT_DSADC1) && (DSADC_HWUNIT_DSADC1 == 1U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC1) && (DSADC_HWUNIT_INT_EN_DSADC1 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC1) && (DSADC_HWUNIT_AUX_INT_EN_DSADC1 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC1SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC1);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC1) && (DSADC_HWUNIT_AUX_INT_EN_DSADC1 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC1SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC1);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC1) && (DSADC_HWUNIT_INT_EN_DSADC1 == STD_ON)) */
#endif /* defined(DSADC_HWUNIT_DSADC1) */

#if (defined(DSADC_HWUNIT_DSADC2) && (DSADC_HWUNIT_DSADC2 == 2U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC2) && (DSADC_HWUNIT_INT_EN_DSADC2 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC2) && (DSADC_HWUNIT_AUX_INT_EN_DSADC2 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC2SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC2);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC2) && (DSADC_HWUNIT_AUX_INT_EN_DSADC2 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC2SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC2);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC2) && (DSADC_HWUNIT_INT_EN_DSADC2 == STD_ON)) */
#endif /* \(defined(DSADC_HWUNIT_DSADC2) && (DSADC_HWUNIT_DSADC2 == 2U)) */

#if (defined(DSADC_HWUNIT_DSADC3) && (DSADC_HWUNIT_DSADC3 == 3U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC3) && (DSADC_HWUNIT_INT_EN_DSADC3 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC3) && (DSADC_HWUNIT_AUX_INT_EN_DSADC3 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC3SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC3);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC3) && (DSADC_HWUNIT_AUX_INT_EN_DSADC3 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC3SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC3);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC3) && (DSADC_HWUNIT_INT_EN_DSADC3 == STD_ON)) */
#endif /* \(defined(DSADC_HWUNIT_DSADC3) && (DSADC_HWUNIT_DSADC3 == 3U)) */

#if (defined(DSADC_HWUNIT_DSADC4) && (DSADC_HWUNIT_DSADC4 == 4U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC4) && (DSADC_HWUNIT_INT_EN_DSADC4 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC4) && (DSADC_HWUNIT_AUX_INT_EN_DSADC4 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC4SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC4);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC4) && (DSADC_HWUNIT_AUX_INT_EN_DSADC4 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC4SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC4);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC4) && (DSADC_HWUNIT_INT_EN_DSADC4 == STD_ON)) */
#endif /* \(defined(DSADC_HWUNIT_DSADC4) && (DSADC_HWUNIT_DSADC4 == 4U)) */

#if (defined(DSADC_HWUNIT_DSADC5) && (DSADC_HWUNIT_DSADC5 == 5U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC5) && (DSADC_HWUNIT_INT_EN_DSADC5 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC5) && (DSADC_HWUNIT_AUX_INT_EN_DSADC5 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC5SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC5);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC5) && (DSADC_HWUNIT_AUX_INT_EN_DSADC5 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC5SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC5);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC5) && (DSADC_HWUNIT_INT_EN_DSADC5 == STD_ON)) */
#endif /* \(defined(DSADC_HWUNIT_DSADC5) && (DSADC_HWUNIT_DSADC5 == 5U)) */

#if (defined(DSADC_HWUNIT_DSADC6) && (DSADC_HWUNIT_DSADC6 == 6U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC6) && (DSADC_HWUNIT_INT_EN_DSADC6 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC6) && (DSADC_HWUNIT_AUX_INT_EN_DSADC6 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC6SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC6);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC6) && (DSADC_HWUNIT_AUX_INT_EN_DSADC6 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC6SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC6);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC6) && (DSADC_HWUNIT_INT_EN_DSADC6 == STD_ON)) */
#endif /* \(defined(DSADC_HWUNIT_DSADC6) && (DSADC_HWUNIT_DSADC6 == 6U)) */

#if (defined(DSADC_HWUNIT_DSADC7) && (DSADC_HWUNIT_DSADC7 == 7U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC7) && (DSADC_HWUNIT_INT_EN_DSADC7 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC7) && (DSADC_HWUNIT_AUX_INT_EN_DSADC7 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC7SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC7);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC7) && (DSADC_HWUNIT_AUX_INT_EN_DSADC7 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC7SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC7);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC7) && (DSADC_HWUNIT_INT_EN_DSADC7 == STD_ON)) */
#endif /* \(defined(DSADC_HWUNIT_DSADC7) && (DSADC_HWUNIT_DSADC7 == 7U)) */

#if (defined(DSADC_HWUNIT_DSADC8) && (DSADC_HWUNIT_DSADC8 == 8U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC8) && (DSADC_HWUNIT_INT_EN_DSADC8 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC8) && (DSADC_HWUNIT_AUX_INT_EN_DSADC8 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC8SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC8);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC8) && (DSADC_HWUNIT_AUX_INT_EN_DSADC8 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC8SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC8);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC8) && (DSADC_HWUNIT_INT_EN_DSADC8 == STD_ON)) */
#endif /* \(defined(DSADC_HWUNIT_DSADC8) && (DSADC_HWUNIT_DSADC8 == 8U)) */

#if (defined(DSADC_HWUNIT_DSADC9) && (DSADC_HWUNIT_DSADC9 == 9U))
#if (defined(DSADC_HWUNIT_INT_EN_DSADC9) && (DSADC_HWUNIT_INT_EN_DSADC9 == STD_ON))
#if (defined(DSADC_HWUNIT_AUX_INT_EN_DSADC9) && (DSADC_HWUNIT_AUX_INT_EN_DSADC9 == STD_ON))
FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC9SRA_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    Dsadc_AuxiliaryChannel_ISRHandler(DSADC_HWUNIT_DSADC9);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE  == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_AUX_INT_EN_DSADC9) && (DSADC_HWUNIT_AUX_INT_EN_DSADC9 == STD_ON)) */

FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DSADC9SRM_ISR
(
    void
)
{
#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
    Dsadc_MainChannel_ISRHandler(DSADC_HWUNIT_DSADC9);
#endif /* \(DSADC_CFG_INTERRUPT_MODE  == STD_ON) */
}
#endif /* \(defined(DSADC_HWUNIT_INT_EN_DSADC9) && (DSADC_HWUNIT_INT_EN_DSADC9 == STD_ON)) */
#endif /* \(defined(DSADC_HWUNIT_DSADC9) && (DSADC_HWUNIT_DSADC9 == 9U)) */

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dsadc_Irq_c_REF_1 */
#include "Dsadc_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

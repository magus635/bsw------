/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Lin_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
*
*   brief                 : This file contains internal functions of Lin Driver
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
*#Lin_Irq_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#Lin_Irq_c_REF_2:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
* driver must be placed.
*
*#Lin_Irq_c_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Lin.h"
#include "Lin_Irq.h"
#include "Lin_Cfg.h"
#include "Mcall_Cfg.h"
/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Lin_Irq_c_REF_3 */
#define LIN_START_SEC_CODE_ASIL_D_GLOBAL
#include "Lin_MemMap.h"
/****************************************************************************************************
*   Function Name           : Lin_Asix_Recv_ISR
*
*   Service ID              : None.
*
*   Description             : Received Interrupt service handler function.
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
/* \[SWS_Lin_00156] The Lin module shall ensure that all unused interrupts are 
disabled. */
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
#ifdef LIN_HWUNIT_CHANNEL0
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi0_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(0U);
}
#endif/* LIN_HWUNIT_CHANNEL0 */

#ifdef LIN_HWUNIT_CHANNEL1
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi1_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(1U);
}
#endif/* LIN_HWUNIT_CHANNEL1 */

#ifdef LIN_HWUNIT_CHANNEL2
/* #Violation: Lin_Irq_c_REF_1 */ 
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi2_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(2U);
}
#endif/* LIN_HWUNIT_CHANNEL2 */

#ifdef LIN_HWUNIT_CHANNEL3
/* #Violation: Lin_Irq_c_REF_1 */ 
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi3_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(3U);
}
#endif/* LIN_HWUNIT_CHANNEL3 */

#ifdef LIN_HWUNIT_CHANNEL4
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi4_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(4U);
}
#endif/* LIN_HWUNIT_CHANNEL4 */

#ifdef LIN_HWUNIT_CHANNEL5
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi5_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(5U);
}
#endif/* LIN_HWUNIT_CHANNEL5 */

#ifdef LIN_HWUNIT_CHANNEL6
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi6_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(6U);
}
#endif/* LIN_HWUNIT_CHANNEL6 */

#ifdef LIN_HWUNIT_CHANNEL7
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi7_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(7U);
}
#endif/* LIN_HWUNIT_CHANNEL7 */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL8
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi8_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(8U);
}
#endif/* LIN_HWUNIT_CHANNEL8 */

#ifdef LIN_HWUNIT_CHANNEL9
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi9_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(9U);
}
#endif/* LIN_HWUNIT_CHANNEL9 */

#ifdef LIN_HWUNIT_CHANNEL10
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi10_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(10U);
}
#endif/* LIN_HWUNIT_CHANNEL10 */

#ifdef LIN_HWUNIT_CHANNEL11
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi11_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(11U);
}
#endif/* LIN_HWUNIT_CHANNEL11 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL12
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi12_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(12U);
}
#endif/* LIN_HWUNIT_CHANNEL12 */

#ifdef LIN_HWUNIT_CHANNEL13
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi13_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(13U);
}
#endif/* LIN_HWUNIT_CHANNEL13 */

#ifdef LIN_HWUNIT_CHANNEL14
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi14_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(14U);
}
#endif/* LIN_HWUNIT_CHANNEL14 */

#ifdef LIN_HWUNIT_CHANNEL15
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi15_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(15U);
}
#endif/* LIN_HWUNIT_CHANNEL15 */

#ifdef LIN_HWUNIT_CHANNEL16
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi16_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(16U);
}
#endif/* LIN_HWUNIT_CHANNEL16 */

#ifdef LIN_HWUNIT_CHANNEL17
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi17_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(17U);
}
#endif/* LIN_HWUNIT_CHANNEL17 */

#ifdef LIN_HWUNIT_CHANNEL18
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi18_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(18U);
}
#endif/* LIN_HWUNIT_CHANNEL18 */

#ifdef LIN_HWUNIT_CHANNEL19
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi19_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(19U);
}
#endif/* LIN_HWUNIT_CHANNEL19 */

#ifdef LIN_HWUNIT_CHANNEL20
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi20_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(20U);
}
#endif/* LIN_HWUNIT_CHANNEL20 */

#ifdef LIN_HWUNIT_CHANNEL21
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi21_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(21U);
}
#endif/* LIN_HWUNIT_CHANNEL21 */

#ifdef LIN_HWUNIT_CHANNEL22
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi22_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(22U);
}
#endif/* LIN_HWUNIT_CHANNEL22 */

#ifdef LIN_HWUNIT_CHANNEL23
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi23_Recv_ISR
(
    void
)
{
    Lin_AsiRecv_ISRHandler(23U);
}
#endif/* LIN_HWUNIT_CHANNEL23 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

/****************************************************************************************************
*   Function Name           : Lin_Asix_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : Received Interrupt service handler function.
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
/* \[SWS_Lin_00156] The Lin module shall ensure that all unused interrupts are
disabled. */
#if (LIN_SLAVE_MODE_USED == STD_ON)
#ifdef LIN_HWUNIT_CHANNEL0
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi0_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(0U);
}
#endif/* LIN_HWUNIT_CHANNEL0 */

#ifdef LIN_HWUNIT_CHANNEL1
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi1_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(1U);
}
#endif/* LIN_HWUNIT_CHANNEL1 */

#ifdef LIN_HWUNIT_CHANNEL2
/* #Violation: Lin_Irq_c_REF_1 */ 
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi2_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(2U);
}
#endif/* LIN_HWUNIT_CHANNEL2 */

#ifdef LIN_HWUNIT_CHANNEL3
/* #Violation: Lin_Irq_c_REF_1 */ 
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi3_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(3U);
}
#endif/* LIN_HWUNIT_CHANNEL3 */

#ifdef LIN_HWUNIT_CHANNEL4
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi4_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(4U);
}
#endif/* LIN_HWUNIT_CHANNEL4 */

#ifdef LIN_HWUNIT_CHANNEL5
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi5_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(5U);
}
#endif/* LIN_HWUNIT_CHANNEL5 */

#ifdef LIN_HWUNIT_CHANNEL6
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi6_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(6U);
}
#endif/* LIN_HWUNIT_CHANNEL6 */

#ifdef LIN_HWUNIT_CHANNEL7
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi7_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(7U);
}
#endif/* LIN_HWUNIT_CHANNEL7 */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL8
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi8_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(8U);
}
#endif/* LIN_HWUNIT_CHANNEL8 */

#ifdef LIN_HWUNIT_CHANNEL9
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi9_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(9U);
}
#endif/* LIN_HWUNIT_CHANNEL9 */

#ifdef LIN_HWUNIT_CHANNEL10
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi10_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(10U);
}
#endif/* LIN_HWUNIT_CHANNEL10 */

#ifdef LIN_HWUNIT_CHANNEL11
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi11_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(11U);
}
#endif/* LIN_HWUNIT_CHANNEL11 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL12
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi12_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(12U);
}
#endif/* LIN_HWUNIT_CHANNEL12 */

#ifdef LIN_HWUNIT_CHANNEL13
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi13_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(13U);
}
#endif/* LIN_HWUNIT_CHANNEL13 */

#ifdef LIN_HWUNIT_CHANNEL14
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi14_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(14U);
}
#endif/* LIN_HWUNIT_CHANNEL14 */

#ifdef LIN_HWUNIT_CHANNEL15
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi15_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(15U);
}
#endif/* LIN_HWUNIT_CHANNEL15 */

#ifdef LIN_HWUNIT_CHANNEL16
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi16_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(16U);
}
#endif/* LIN_HWUNIT_CHANNEL16 */

#ifdef LIN_HWUNIT_CHANNEL17
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi17_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(17U);
}
#endif/* LIN_HWUNIT_CHANNEL17 */

#ifdef LIN_HWUNIT_CHANNEL18
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi18_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(18U);
}
#endif/* LIN_HWUNIT_CHANNEL18 */

#ifdef LIN_HWUNIT_CHANNEL19
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi19_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(19U);
}
#endif/* LIN_HWUNIT_CHANNEL19 */

#ifdef LIN_HWUNIT_CHANNEL20
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi20_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(20U);
}
#endif/* LIN_HWUNIT_CHANNEL20 */

#ifdef LIN_HWUNIT_CHANNEL21
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi21_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(21U);
}
#endif/* LIN_HWUNIT_CHANNEL21 */

#ifdef LIN_HWUNIT_CHANNEL22
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi22_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(22U);
}
#endif/* LIN_HWUNIT_CHANNEL22 */

#ifdef LIN_HWUNIT_CHANNEL23
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi23_Tx_ISR
(
    void
)
{
    Lin_AsiTx_ISRHandler(23U);
}
#endif /* LIN_HWUNIT_CHANNEL23 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
#endif/* #if (LIN_SLAVE_MODE_USED  \== STD_ON) */
/****************************************************************************************************
*   Function Name           : Lin_Asix_Error_ISR
*
*   Service ID              : None.
*
*   Description             : Asix Error interrupt.
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
#ifdef LIN_HWUNIT_CHANNEL0
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi0_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(0U);
}
#endif/* LIN_HWUNIT_CHANNEL0 */

#ifdef LIN_HWUNIT_CHANNEL1
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi1_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(1U);
}
#endif/* LIN_HWUNIT_CHANNEL1 */

#ifdef LIN_HWUNIT_CHANNEL2
/* #Violation: Lin_Irq_c_REF_1 */ 
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi2_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(2U);
}
#endif/* LIN_HWUNIT_CHANNEL2 */

#ifdef LIN_HWUNIT_CHANNEL3
/* #Violation: Lin_Irq_c_REF_1 */ 
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi3_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(3U);
}
#endif/* LIN_HWUNIT_CHANNEL3 */

#ifdef LIN_HWUNIT_CHANNEL4
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi4_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(4U);
}
#endif/* LIN_HWUNIT_CHANNEL4 */

#ifdef LIN_HWUNIT_CHANNEL5
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi5_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(5U);
}
#endif/* LIN_HWUNIT_CHANNEL5 */

#ifdef LIN_HWUNIT_CHANNEL6
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi6_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(6U);
}
#endif/* LIN_HWUNIT_CHANNEL6 */

#ifdef LIN_HWUNIT_CHANNEL7
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi7_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(7U);
}
#endif/* LIN_HWUNIT_CHANNEL7 */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL8
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi8_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(8U);
}
#endif/* LIN_HWUNIT_CHANNEL8 */

#ifdef LIN_HWUNIT_CHANNEL9
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi9_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(9U);
}
#endif/* LIN_HWUNIT_CHANNEL9 */

#ifdef LIN_HWUNIT_CHANNEL10
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi10_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(10U);
}
#endif/* LIN_HWUNIT_CHANNEL10 */

#ifdef LIN_HWUNIT_CHANNEL11
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi11_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(11U);
}
#endif/* LIN_HWUNIT_CHANNEL11 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL12
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi12_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(12U);
}
#endif/* LIN_HWUNIT_CHANNEL12 */

#ifdef LIN_HWUNIT_CHANNEL13
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi13_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(13U);
}
#endif/* LIN_HWUNIT_CHANNEL13 */

#ifdef LIN_HWUNIT_CHANNEL14
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi14_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(14U);
}
#endif/* LIN_HWUNIT_CHANNEL14 */

#ifdef LIN_HWUNIT_CHANNEL15
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi15_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(15U);
}
#endif/* LIN_HWUNIT_CHANNEL15 */

#ifdef LIN_HWUNIT_CHANNEL16
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi16_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(16U);
}
#endif/* LIN_HWUNIT_CHANNEL16 */

#ifdef LIN_HWUNIT_CHANNEL17
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi17_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(17U);
}
#endif/* LIN_HWUNIT_CHANNEL17 */

#ifdef LIN_HWUNIT_CHANNEL18
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi18_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(18U);
}
#endif/* LIN_HWUNIT_CHANNEL18 */

#ifdef LIN_HWUNIT_CHANNEL19
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi19_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(19U);
}
#endif/* LIN_HWUNIT_CHANNEL19 */

#ifdef LIN_HWUNIT_CHANNEL20
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi20_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(20U);
}
#endif/* LIN_HWUNIT_CHANNEL20 */

#ifdef LIN_HWUNIT_CHANNEL21
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi21_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(21U);
}
#endif/* LIN_HWUNIT_CHANNEL21 */

#ifdef LIN_HWUNIT_CHANNEL22
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi22_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(22U);
}
#endif/* LIN_HWUNIT_CHANNEL22 */

#ifdef LIN_HWUNIT_CHANNEL23
FUNC(void, LIN_PUBLIC_CODE) Lin_Asi23_Error_ISR
(
    void
)
{
    Lin_Error_ISRHandler(23U);
}
#endif/* LIN_HWUNIT_CHANNEL23 */
#endif /* (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */

/* #Violation: Lin_Irq_c_REF_3*/
#define LIN_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Lin_Irq_c_REF_2 */ 
#include "Lin_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

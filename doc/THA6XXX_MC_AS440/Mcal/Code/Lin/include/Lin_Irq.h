/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Lin_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
*
*   brief                 : This file contains all type definitions of Lin Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/**************************************************************************************************/
#ifndef LIN_IRQ_H_
#define LIN_IRQ_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Lin_Cfg.h"
#include "Lin_GeneralTypes.h"
#include "Mcall.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
#ifdef LIN_HWUNIT_CHANNEL0
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi0_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL0 */

#ifdef LIN_HWUNIT_CHANNEL1
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi1_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL1 */

#ifdef LIN_HWUNIT_CHANNEL2
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi2_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL2 */

#ifdef LIN_HWUNIT_CHANNEL3
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi3_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL3 */

#ifdef LIN_HWUNIT_CHANNEL4
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi4_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL4 */

#ifdef LIN_HWUNIT_CHANNEL5
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi5_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL5 */

#ifdef LIN_HWUNIT_CHANNEL6
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi6_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL6 */

#ifdef LIN_HWUNIT_CHANNEL7
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi7_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL7 */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL8
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi8_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL8 */

#ifdef LIN_HWUNIT_CHANNEL9
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi9_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL9 */

#ifdef LIN_HWUNIT_CHANNEL10
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi10_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL10 */

#ifdef LIN_HWUNIT_CHANNEL11
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi11_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL11 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL12
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi12_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL12 */

#ifdef LIN_HWUNIT_CHANNEL13
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi13_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL13 */

#ifdef LIN_HWUNIT_CHANNEL14
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi14_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL14 */

#ifdef LIN_HWUNIT_CHANNEL15
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi15_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL15 */

#ifdef LIN_HWUNIT_CHANNEL16
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi16_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL16 */

#ifdef LIN_HWUNIT_CHANNEL17
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi17_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL17 */

#ifdef LIN_HWUNIT_CHANNEL18
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi18_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL18 */

#ifdef LIN_HWUNIT_CHANNEL19
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi19_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL19 */

#ifdef LIN_HWUNIT_CHANNEL20
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi20_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL20 */

#ifdef LIN_HWUNIT_CHANNEL21
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi21_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL21 */

#ifdef LIN_HWUNIT_CHANNEL22
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi22_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL22 */

#ifdef LIN_HWUNIT_CHANNEL23
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi23_Recv_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL23 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */

#if (LIN_SLAVE_MODE_USED == STD_ON)
#ifdef LIN_HWUNIT_CHANNEL0
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi0_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL0 */

#ifdef LIN_HWUNIT_CHANNEL1
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi1_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL1 */

#ifdef LIN_HWUNIT_CHANNEL2
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi2_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL2 */

#ifdef LIN_HWUNIT_CHANNEL3
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi3_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL3 */

#ifdef LIN_HWUNIT_CHANNEL4
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi4_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL4 */

#ifdef LIN_HWUNIT_CHANNEL5
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi5_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL5 */

#ifdef LIN_HWUNIT_CHANNEL6
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi6_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL6 */

#ifdef LIN_HWUNIT_CHANNEL7
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi7_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL7 */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL8
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi8_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL8 */

#ifdef LIN_HWUNIT_CHANNEL9
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi9_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL9 */

#ifdef LIN_HWUNIT_CHANNEL10
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi10_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL10 */

#ifdef LIN_HWUNIT_CHANNEL11
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi11_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL11 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL12
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi12_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL12 */

#ifdef LIN_HWUNIT_CHANNEL13
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi13_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL13 */

#ifdef LIN_HWUNIT_CHANNEL14
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi14_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL14 */

#ifdef LIN_HWUNIT_CHANNEL15
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi15_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL15 */

#ifdef LIN_HWUNIT_CHANNEL16
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi16_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL16 */

#ifdef LIN_HWUNIT_CHANNEL17
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi17_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL17 */

#ifdef LIN_HWUNIT_CHANNEL18
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi18_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL18 */

#ifdef LIN_HWUNIT_CHANNEL19
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi19_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL19 */

#ifdef LIN_HWUNIT_CHANNEL20
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi20_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL20 */

#ifdef LIN_HWUNIT_CHANNEL21
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi21_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL21 */

#ifdef LIN_HWUNIT_CHANNEL22
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi22_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL22 */

#ifdef LIN_HWUNIT_CHANNEL23
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi23_Tx_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL23 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */
#endif/* #if (LIN_SLAVE_MODE_USED  \== STD_ON) */


#ifdef LIN_HWUNIT_CHANNEL0
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi0_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL0 */

#ifdef LIN_HWUNIT_CHANNEL1
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi1_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL1 */

#ifdef LIN_HWUNIT_CHANNEL2
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi2_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL2 */

#ifdef LIN_HWUNIT_CHANNEL3
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi3_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL3 */

#ifdef LIN_HWUNIT_CHANNEL4
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi4_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL4 */

#ifdef LIN_HWUNIT_CHANNEL5
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi5_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL5 */

#ifdef LIN_HWUNIT_CHANNEL6
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi6_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL6 */

#ifdef LIN_HWUNIT_CHANNEL7
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi7_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL7 */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL8
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi8_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL8 */

#ifdef LIN_HWUNIT_CHANNEL9
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi9_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL9 */

#ifdef LIN_HWUNIT_CHANNEL10
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi10_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL10 */

#ifdef LIN_HWUNIT_CHANNEL11
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi11_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL11 */
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA610X_LFBGA180) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
#ifdef LIN_HWUNIT_CHANNEL12
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi12_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL12 */

#ifdef LIN_HWUNIT_CHANNEL13
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi13_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL13 */

#ifdef LIN_HWUNIT_CHANNEL14
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi14_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL14 */

#ifdef LIN_HWUNIT_CHANNEL15
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi15_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL15 */

#ifdef LIN_HWUNIT_CHANNEL16
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi16_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL16 */

#ifdef LIN_HWUNIT_CHANNEL17
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi17_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL17 */

#ifdef LIN_HWUNIT_CHANNEL18
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi18_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL18 */

#ifdef LIN_HWUNIT_CHANNEL19
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi19_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL19 */

#ifdef LIN_HWUNIT_CHANNEL20
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi20_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL20 */

#ifdef LIN_HWUNIT_CHANNEL21
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi21_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL21 */

#ifdef LIN_HWUNIT_CHANNEL22
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi22_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL22 */

#ifdef LIN_HWUNIT_CHANNEL23
extern FUNC(void, LIN_PUBLIC_CODE) Lin_Asi23_Error_ISR
(
    void
);
#endif/* LIN_HWUNIT_CHANNEL23 */
#endif /* (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516) */
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */

#endif /* _LIN_IRQ_H_ */

/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/

/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Uart_Irq.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : ASI
 *
 *   brief                 : This file contains all type definitions of UART Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
****************************************************************************************************/


/**************************************************************************************************/
#ifndef UART_IRQ_H_
#define UART_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Uart.h"


/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#ifdef UART_USED_RX_INTC_ASI0
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi0_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI0 */

#ifdef UART_USED_TX_INTC_ASI0
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi0_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI0 */

#ifdef UART_USED_ERROR_INTC_ASI0
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi0_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI0 */


#ifdef UART_USED_RX_INTC_ASI1
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi1_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI1 */

#ifdef UART_USED_TX_INTC_ASI1
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi1_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI1 */

#ifdef UART_USED_ERROR_INTC_ASI1
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi1_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI1 */


#ifdef UART_USED_RX_INTC_ASI2
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi2_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI2 */

#ifdef UART_USED_TX_INTC_ASI2
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi2_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI2 */

#ifdef UART_USED_ERROR_INTC_ASI2
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi2_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI2 */


#ifdef UART_USED_RX_INTC_ASI3
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi3_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI3 */

#ifdef UART_USED_TX_INTC_ASI3
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi3_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI3 */

#ifdef UART_USED_ERROR_INTC_ASI3
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi3_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI3 */


#ifdef UART_USED_RX_INTC_ASI4
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi4_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI4 */

#ifdef UART_USED_TX_INTC_ASI4
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi4_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI4 */

#ifdef UART_USED_ERROR_INTC_ASI4
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi4_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI4 */


#ifdef UART_USED_RX_INTC_ASI5
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi5_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI5 */

#ifdef UART_USED_TX_INTC_ASI5
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi5_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI5 */

#ifdef UART_USED_ERROR_INTC_ASI5
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi5_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI5 */


#ifdef UART_USED_RX_INTC_ASI6
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi6_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI6 */

#ifdef UART_USED_TX_INTC_ASI6
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi6_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI6 */

#ifdef UART_USED_ERROR_INTC_ASI6
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi6_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI6 */


#ifdef UART_USED_RX_INTC_ASI7
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi7_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI7 */

#ifdef UART_USED_TX_INTC_ASI7
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi7_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI7 */

#ifdef UART_USED_ERROR_INTC_ASI7
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi7_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI7 */

#ifdef UART_USED_RX_INTC_ASI8
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi8_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI8 */

#ifdef UART_USED_TX_INTC_ASI8
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi8_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI8 */

#ifdef UART_USED_ERROR_INTC_ASI8
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi8_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI8 */

#ifdef UART_USED_RX_INTC_ASI9
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi9_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI9 */

#ifdef UART_USED_TX_INTC_ASI9
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi9_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI9 */

#ifdef UART_USED_ERROR_INTC_ASI9
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi9_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI9 */

#ifdef UART_USED_RX_INTC_ASI10
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi10_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI10 */

#ifdef UART_USED_TX_INTC_ASI10
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi10_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI10 */

#ifdef UART_USED_ERROR_INTC_ASI10
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi10_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI10 */

#ifdef UART_USED_RX_INTC_ASI11
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi11_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI11 */

#ifdef UART_USED_TX_INTC_ASI11
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi11_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI11 */

#ifdef UART_USED_ERROR_INTC_ASI11
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi11_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI11 */

#ifdef UART_USED_RX_INTC_ASI12
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi12_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI12 */

#ifdef UART_USED_TX_INTC_ASI12
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi12_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI12 */

#ifdef UART_USED_ERROR_INTC_ASI12
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi12_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI12 */

#ifdef UART_USED_RX_INTC_ASI13
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi13_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI13 */

#ifdef UART_USED_TX_INTC_ASI13
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi13_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI13 */

#ifdef UART_USED_ERROR_INTC_ASI13
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi13_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI13 */

#ifdef UART_USED_RX_INTC_ASI14
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi14_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI14 */

#ifdef UART_USED_TX_INTC_ASI14
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi14_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI14 */

#ifdef UART_USED_ERROR_INTC_ASI14
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi14_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI14 */

#ifdef UART_USED_RX_INTC_ASI15
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi15_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI15 */

#ifdef UART_USED_TX_INTC_ASI15
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi15_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI15 */

#ifdef UART_USED_ERROR_INTC_ASI15
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi15_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI15 */

#ifdef UART_USED_RX_INTC_ASI16
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi16_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI16 */

#ifdef UART_USED_TX_INTC_ASI16
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi16_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI16 */

#ifdef UART_USED_ERROR_INTC_ASI16
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi16_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI16 */

#ifdef UART_USED_RX_INTC_ASI17
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi17_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI17 */

#ifdef UART_USED_TX_INTC_ASI17
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi17_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI17 */

#ifdef UART_USED_ERROR_INTC_ASI17
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi17_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI17 */

#ifdef UART_USED_RX_INTC_ASI18
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi18_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI18 */

#ifdef UART_USED_TX_INTC_ASI18
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi18_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI18 */

#ifdef UART_USED_ERROR_INTC_ASI18
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi18_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI18 */

#ifdef UART_USED_RX_INTC_ASI19
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi19_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI19 */

#ifdef UART_USED_TX_INTC_ASI19
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi19_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI19 */

#ifdef UART_USED_ERROR_INTC_ASI19
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi19_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI19 */

#ifdef UART_USED_RX_INTC_ASI20
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi20_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI20 */

#ifdef UART_USED_TX_INTC_ASI20
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi20_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI20 */

#ifdef UART_USED_ERROR_INTC_ASI20
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi20_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI20 */

#ifdef UART_USED_RX_INTC_ASI21
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi21_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI21 */

#ifdef UART_USED_TX_INTC_ASI21
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi21_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI21 */

#ifdef UART_USED_ERROR_INTC_ASI21
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi21_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI21 */

#ifdef UART_USED_RX_INTC_ASI22
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi22_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI22 */

#ifdef UART_USED_TX_INTC_ASI22
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi22_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI22 */

#ifdef UART_USED_ERROR_INTC_ASI22
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi22_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI22 */

#ifdef UART_USED_RX_INTC_ASI23
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi23_Rx_ISR
(
    void
);
#endif /* UART_USED_RX_INTC_ASI23 */

#ifdef UART_USED_TX_INTC_ASI23
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi23_Tx_ISR
(
    void
);
#endif /* UART_USED_TX_INTC_ASI23 */

#ifdef UART_USED_ERROR_INTC_ASI23
extern FUNC(void, UART_PUBLIC_CODE) Uart_Asi23_Error_ISR
(
    void
);
#endif /* UART_USED_ERROR_INTC_ASI23 */


#endif /* UART_IRQ_H_ */
/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/

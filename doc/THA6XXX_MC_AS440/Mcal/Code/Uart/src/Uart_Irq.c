/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Uart_Irq.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : ASI
 *
 *   brief                 : This file contains internal functions of Uart Driver
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
*#Uart_Irq_c_REF_1:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Uart_Irq.h"
/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Uart_Irq_c_REF_1 */
#define UART_START_SEC_CODE_ASIL_D_GLOBAL
#include "Uart_MemMap.h"

#ifdef UART_USED_RX_INTC_ASI0
/****************************************************************************************************
*   Function Name           : Uart_Asi0_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI0 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi0_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(0U);
}
#endif /* UART_USED_RX_INTC_ASI0 */
#ifdef UART_USED_TX_INTC_ASI0
/****************************************************************************************************
*   Function Name           : Uart_Asi0_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI0 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi0_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(0U);
}
#endif /* UART_USED_TX_INTC_ASI0 */
#ifdef UART_USED_ERROR_INTC_ASI0
/****************************************************************************************************
*   Function Name           : Uart_Asi0_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI0 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi0_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(0U);
}
#endif /* UART_USED_ERROR_INTC_ASI0 */


#ifdef UART_USED_RX_INTC_ASI1
/****************************************************************************************************
*   Function Name           : Uart_Asi1_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI1 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi1_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(1U);
}
#endif /* UART_USED_RX_INTC_ASI1 */
#ifdef UART_USED_TX_INTC_ASI1
/****************************************************************************************************
r*   Function Name           : Uart_Asi1_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI1 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi1_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(1U);
}
#endif /* UART_USED_TX_INTC_ASI1 */
#ifdef UART_USED_ERROR_INTC_ASI1
/****************************************************************************************************
*   Function Name           : Uart_Asi1_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI1 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi1_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(1U);
}
#endif /* UART_USED_ERROR_INTC_ASI1 */


#ifdef UART_USED_RX_INTC_ASI2
/****************************************************************************************************
*   Function Name           : Uart_Asi2_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI2 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi2_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(2U);
}
#endif /* UART_USED_RX_INTC_ASI2 */
#ifdef UART_USED_TX_INTC_ASI2
/****************************************************************************************************
*   Function Name           : Uart_Asi2_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI2 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi2_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(2U);
}
#endif /* UART_USED_TX_INTC_ASI2 */
#ifdef UART_USED_ERROR_INTC_ASI2
/****************************************************************************************************
*   Function Name           : Uart_Asi2_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI2 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi2_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(2U);
}
#endif /* UART_USED_ERROR_INTC_ASI2 */


#ifdef UART_USED_RX_INTC_ASI3
/****************************************************************************************************
*   Function Name           : Uart_Asi3_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI3 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi3_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(3U);
}
#endif /* UART_USED_RX_INTC_ASI3 */
#ifdef UART_USED_TX_INTC_ASI3
/****************************************************************************************************
*   Function Name           : Uart_Asi3_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI3 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi3_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(3U);
}
#endif /* UART_USED_TX_INTC_ASI3 */
#ifdef UART_USED_ERROR_INTC_ASI3
/****************************************************************************************************
*   Function Name           : Uart_Asi3_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI3 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi3_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(3U);
}
#endif /* UART_USED_ERROR_INTC_ASI3 */


#ifdef UART_USED_RX_INTC_ASI4
/****************************************************************************************************
*   Function Name           : Uart_Asi4_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI4 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi4_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(4U);
}
#endif /* UART_USED_RX_INTC_ASI4 */
#ifdef UART_USED_TX_INTC_ASI4
/****************************************************************************************************
*   Function Name           : Uart_Asi4_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI4 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi4_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(4U);
}
#endif /* UART_USED_TX_INTC_ASI4 */
#ifdef UART_USED_ERROR_INTC_ASI4
/****************************************************************************************************
*   Function Name           : Uart_Asi4_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI4 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi4_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(4U);
}
#endif /* UART_USED_ERROR_INTC_ASI4 */


#ifdef UART_USED_RX_INTC_ASI5
/****************************************************************************************************
*   Function Name           : Uart_Asi5_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI5 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi5_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(5U);
}
#endif /* UART_USED_RX_INTC_ASI5 */
#ifdef UART_USED_TX_INTC_ASI5
/****************************************************************************************************
*   Function Name           : Uart_Asi5_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI5 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi5_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(5U);
}
#endif /* UART_USED_TX_INTC_ASI5 */
#ifdef UART_USED_ERROR_INTC_ASI5
/****************************************************************************************************
*   Function Name           : Uart_Asi5_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI5 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi5_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(5U);
}
#endif /* UART_USED_ERROR_INTC_ASI5 */


#ifdef UART_USED_RX_INTC_ASI6
/****************************************************************************************************
*   Function Name           : Uart_Asi6_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI6 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi6_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(6U);
}
#endif /* UART_USED_RX_INTC_ASI6 */
#ifdef UART_USED_TX_INTC_ASI6
/****************************************************************************************************
*   Function Name           : Uart_Asi6_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI6 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi6_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(6U);
}
#endif /* UART_USED_TX_INTC_ASI6 */
#ifdef UART_USED_ERROR_INTC_ASI6
/****************************************************************************************************
*   Function Name           : Uart_Asi6_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI6 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi6_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(6U);
}
#endif /* UART_USED_ERROR_INTC_ASI6 */


#ifdef UART_USED_RX_INTC_ASI7
/****************************************************************************************************
*   Function Name           : Uart_Asi7_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI7 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi7_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(7U);
}
#endif /* UART_USED_RX_INTC_ASI7 */
#ifdef UART_USED_TX_INTC_ASI7
/****************************************************************************************************
*   Function Name           : Uart_Asi7_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI7 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi7_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(7U);
}
#endif /* UART_USED_TX_INTC_ASI7 */
#ifdef UART_USED_ERROR_INTC_ASI7
/****************************************************************************************************
*   Function Name           : Uart_Asi7_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI7 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi7_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(7U);
}
#endif /* UART_USED_ERROR_INTC_ASI7 */

#ifdef UART_USED_RX_INTC_ASI8
/****************************************************************************************************
*   Function Name           : Uart_Asi8_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI8 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi8_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(8U);
}
#endif /* UART_USED_RX_INTC_ASI8 */
#ifdef UART_USED_TX_INTC_ASI8
/****************************************************************************************************
*   Function Name           : Uart_Asi8_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI8 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi8_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(8U);
}
#endif /* UART_USED_TX_INTC_ASI8 */
#ifdef UART_USED_ERROR_INTC_ASI8
/****************************************************************************************************
*   Function Name           : Uart_Asi8_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI8 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi8_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(8U);
}
#endif /* UART_USED_ERROR_INTC_ASI8 */

#ifdef UART_USED_RX_INTC_ASI9
/****************************************************************************************************
*   Function Name           : Uart_Asi9_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI9 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi9_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(9U);
}
#endif /* UART_USED_RX_INTC_ASI9 */
#ifdef UART_USED_TX_INTC_ASI9
/****************************************************************************************************
*   Function Name           : Uart_Asi9_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI9 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi9_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(9U);
}
#endif /* UART_USED_TX_INTC_ASI9 */
#ifdef UART_USED_ERROR_INTC_ASI9
/****************************************************************************************************
*   Function Name           : Uart_Asi9_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI9 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi9_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(9U);
}
#endif /* UART_USED_ERROR_INTC_ASI9 */

#ifdef UART_USED_RX_INTC_ASI10
/****************************************************************************************************
*   Function Name           : Uart_Asi10_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI10 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi10_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(10U);
}
#endif /* UART_USED_RX_INTC_ASI10 */
#ifdef UART_USED_TX_INTC_ASI10
/****************************************************************************************************
*   Function Name           : Uart_Asi10_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI10 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi10_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(10U);
}
#endif /* UART_USED_TX_INTC_ASI10 */
#ifdef UART_USED_ERROR_INTC_ASI10
/****************************************************************************************************
*   Function Name           : Uart_Asi10_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI10 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi10_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(10U);
}
#endif /* UART_USED_ERROR_INTC_ASI10 */

#ifdef UART_USED_RX_INTC_ASI11
/****************************************************************************************************
*   Function Name           : Uart_Asi11_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI11 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi11_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(11U);
}
#endif /* UART_USED_RX_INTC_ASI11 */
#ifdef UART_USED_TX_INTC_ASI11
/****************************************************************************************************
*   Function Name           : Uart_Asi11_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI11 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi11_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(11U);
}
#endif /* UART_USED_TX_INTC_ASI11 */
#ifdef UART_USED_ERROR_INTC_ASI11
/****************************************************************************************************
*   Function Name           : Uart_Asi11_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI11 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi11_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(11U);
}
#endif /* UART_USED_ERROR_INTC_ASI11 */

#ifdef UART_USED_RX_INTC_ASI12
/****************************************************************************************************
*   Function Name           : Uart_Asi12_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI12 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi12_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(12U);
}
#endif /* UART_USED_RX_INTC_ASI12 */
#ifdef UART_USED_TX_INTC_ASI12
/****************************************************************************************************
*   Function Name           : Uart_Asi12_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI12 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi12_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(12U);
}
#endif /* UART_USED_TX_INTC_ASI12 */
#ifdef UART_USED_ERROR_INTC_ASI12
/****************************************************************************************************
*   Function Name           : Uart_Asi12_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI12 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi12_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(12U);
}
#endif /* UART_USED_ERROR_INTC_ASI12 */

#ifdef UART_USED_RX_INTC_ASI13
/****************************************************************************************************
*   Function Name           : Uart_Asi13_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI13 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi13_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(13U);
}
#endif /* UART_USED_RX_INTC_ASI13 */
#ifdef UART_USED_TX_INTC_ASI13
/****************************************************************************************************
*   Function Name           : Uart_Asi13_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI13 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi13_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(13U);
}
#endif /* UART_USED_TX_INTC_ASI13 */
#ifdef UART_USED_ERROR_INTC_ASI13
/****************************************************************************************************
*   Function Name           : Uart_Asi13_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI13 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi13_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(13U);
}
#endif /* UART_USED_ERROR_INTC_ASI13 */

#ifdef UART_USED_RX_INTC_ASI14
/****************************************************************************************************
*   Function Name           : Uart_Asi14_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI14 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi14_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(14U);
}
#endif /* UART_USED_RX_INTC_ASI14 */
#ifdef UART_USED_TX_INTC_ASI14
/****************************************************************************************************
*   Function Name           : Uart_Asi14_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI14 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi14_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(14U);
}
#endif /* UART_USED_TX_INTC_ASI14 */
#ifdef UART_USED_ERROR_INTC_ASI14
/****************************************************************************************************
*   Function Name           : Uart_Asi14_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI14 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi14_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(14U);
}
#endif /* UART_USED_ERROR_INTC_ASI14 */

#ifdef UART_USED_RX_INTC_ASI15
/****************************************************************************************************
*   Function Name           : Uart_Asi15_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI15 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi15_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(15U);
}
#endif /* UART_USED_RX_INTC_ASI15 */
#ifdef UART_USED_TX_INTC_ASI15
/****************************************************************************************************
*   Function Name           : Uart_Asi15_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI15 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi15_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(15U);
}
#endif /* UART_USED_TX_INTC_ASI15 */
#ifdef UART_USED_ERROR_INTC_ASI15
/****************************************************************************************************
*   Function Name           : Uart_Asi15_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI15 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi15_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(15U);
}
#endif /* UART_USED_ERROR_INTC_ASI15 */

#ifdef UART_USED_RX_INTC_ASI16
/****************************************************************************************************
*   Function Name           : Uart_Asi16_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI16 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi16_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(16U);
}
#endif /* UART_USED_RX_INTC_ASI16 */
#ifdef UART_USED_TX_INTC_ASI16
/****************************************************************************************************
*   Function Name           : Uart_Asi16_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI16 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi16_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(16U);
}
#endif /* UART_USED_TX_INTC_ASI16 */
#ifdef UART_USED_ERROR_INTC_ASI16
/****************************************************************************************************
*   Function Name           : Uart_Asi16_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI16 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi16_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(16U);
}
#endif /* UART_USED_ERROR_INTC_ASI16 */

#ifdef UART_USED_RX_INTC_ASI17
/****************************************************************************************************
*   Function Name           : Uart_Asi17_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI17 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi17_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(17U);
}
#endif /* UART_USED_RX_INTC_ASI17 */
#ifdef UART_USED_TX_INTC_ASI17
/****************************************************************************************************
*   Function Name           : Uart_Asi17_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI17 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi17_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(17U);
}
#endif /* UART_USED_TX_INTC_ASI17 */
#ifdef UART_USED_ERROR_INTC_ASI17
/****************************************************************************************************
*   Function Name           : Uart_Asi17_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI17 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi17_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(17U);
}
#endif /* UART_USED_ERROR_INTC_ASI17 */

#ifdef UART_USED_RX_INTC_ASI18
/****************************************************************************************************
*   Function Name           : Uart_Asi18_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI18 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi18_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(18U);
}
#endif /* UART_USED_RX_INTC_ASI18 */
#ifdef UART_USED_TX_INTC_ASI18
/****************************************************************************************************
*   Function Name           : Uart_Asi18_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI18 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi18_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(18U);
}
#endif /* UART_USED_TX_INTC_ASI18 */
#ifdef UART_USED_ERROR_INTC_ASI18
/****************************************************************************************************
*   Function Name           : Uart_Asi18_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI18 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi18_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(18U);
}
#endif /* UART_USED_ERROR_INTC_ASI18 */

#ifdef UART_USED_RX_INTC_ASI19
/****************************************************************************************************
*   Function Name           : Uart_Asi19_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI19 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi19_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(19U);
}
#endif /* UART_USED_RX_INTC_ASI19 */
#ifdef UART_USED_TX_INTC_ASI19
/****************************************************************************************************
*   Function Name           : Uart_Asi19_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI19 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi19_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(19U);
}
#endif /* UART_USED_TX_INTC_ASI19 */
#ifdef UART_USED_ERROR_INTC_ASI19
/****************************************************************************************************
*   Function Name           : Uart_Asi19_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI19 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi19_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(19U);
}
#endif /* UART_USED_ERROR_INTC_ASI19 */

#ifdef UART_USED_RX_INTC_ASI20
/****************************************************************************************************
*   Function Name           : Uart_Asi20_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI20 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi20_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(20U);
}
#endif /* UART_USED_RX_INTC_ASI20 */
#ifdef UART_USED_TX_INTC_ASI20
/****************************************************************************************************
*   Function Name           : Uart_Asi20_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI20 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi20_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(20U);
}
#endif /* UART_USED_TX_INTC_ASI20 */
#ifdef UART_USED_ERROR_INTC_ASI20
/****************************************************************************************************
*   Function Name           : Uart_Asi20_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI20 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi20_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(20U);
}
#endif /* UART_USED_ERROR_INTC_ASI20 */

#ifdef UART_USED_RX_INTC_ASI21
/****************************************************************************************************
*   Function Name           : Uart_Asi21_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI21 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi21_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(21U);
}
#endif /* UART_USED_RX_INTC_ASI21 */
#ifdef UART_USED_TX_INTC_ASI21
/****************************************************************************************************
*   Function Name           : Uart_Asi21_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI21 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi21_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(21U);
}
#endif /* UART_USED_TX_INTC_ASI21 */
#ifdef UART_USED_ERROR_INTC_ASI21
/****************************************************************************************************
*   Function Name           : Uart_Asi21_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI21 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi21_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(21U);
}
#endif /* UART_USED_ERROR_INTC_ASI21 */

#ifdef UART_USED_RX_INTC_ASI22
/****************************************************************************************************
*   Function Name           : Uart_Asi22_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI22 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi22_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(22U);
}
#endif /* UART_USED_RX_INTC_ASI22 */
#ifdef UART_USED_TX_INTC_ASI22
/****************************************************************************************************
*   Function Name           : Uart_Asi22_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI22 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi22_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(22U);
}
#endif /* UART_USED_TX_INTC_ASI22 */
#ifdef UART_USED_ERROR_INTC_ASI22
/****************************************************************************************************
*   Function Name           : Uart_Asi22_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI22 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi22_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(22U);
}
#endif /* UART_USED_ERROR_INTC_ASI22 */

#ifdef UART_USED_RX_INTC_ASI23
/****************************************************************************************************
*   Function Name           : Uart_Asi23_Rx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI23 receive interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi23_Rx_ISR
(
    void
)
{
    Uart_Rx_ISRHandler(23U);
}
#endif /* UART_USED_RX_INTC_ASI23 */
#ifdef UART_USED_TX_INTC_ASI23
/****************************************************************************************************
*   Function Name           : Uart_Asi23_Tx_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI23 transmit interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi23_Tx_ISR
(
    void
)
{
    Uart_Tx_ISRHandler(23U);
}
#endif /* UART_USED_TX_INTC_ASI23 */
#ifdef UART_USED_ERROR_INTC_ASI23
/****************************************************************************************************
*   Function Name           : Uart_Asi23_Error_ISR
*
*   Service ID              : None.
*
*   Description             : These function is the ASI23 error interrupt service entry function.
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
*   Preconditions           : UART uses interrupt mode for transmission.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, UART_PUBLIC_CODE) Uart_Asi23_Error_ISR
(
    void
)
{
    Uart_Error_ISRHandler(23U);
}
#endif /* UART_USED_ERROR_INTC_ASI23 */

/* #Violation: Uart_Irq_c_REF_1 */
#define UART_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Uart_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

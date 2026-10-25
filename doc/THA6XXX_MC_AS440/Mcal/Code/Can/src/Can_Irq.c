/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Can_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MCAN
*
*   brief                 : This file contains all ISR functions of Can Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                         Coding Rule Violations                                                  **
****************************************************************************************************/
/*
*#Violation Summary
*
*#Can_Irq_c_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Can_Irq_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Can.h"
#include "Can_Irq.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Can_Irq_c_REF_1 */
#define CAN_START_SEC_CODE_ASIL_D_GLOBAL
#include "Can_MemMap.h"
/***************************************************************************************************/
/******************************Controller00*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_00_RX_INTERRUPT)) && (CAN_CONTROLLER_00_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_00_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_00_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_00_RX_INTERRUPT)) && (CAN_CONTROLLER_00_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_00_TX_INTERRUPT)) && (CAN_CONTROLLER_00_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_00_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_00_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_00_TX_INTERRUPT)) && (CAN_CONTROLLER_00_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_00_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_00_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_00_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_00_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_00_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_00_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_00_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_00_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_00_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_00_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_00_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_00_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller01*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_01_RX_INTERRUPT)) && (CAN_CONTROLLER_01_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_01_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_01_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_01_RX_INTERRUPT)) && (CAN_CONTROLLER_01_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_01_TX_INTERRUPT)) && (CAN_CONTROLLER_01_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_01_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_01_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_01_TX_INTERRUPT)) && (CAN_CONTROLLER_01_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_01_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_01_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_01_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_01_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_01_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_01_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_01_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_01_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_01_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_01_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_01_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_01_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller02*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_02_RX_INTERRUPT)) && (CAN_CONTROLLER_02_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_02_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_02_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_02_RX_INTERRUPT)) && (CAN_CONTROLLER_02_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_02_TX_INTERRUPT)) && (CAN_CONTROLLER_02_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_02_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_02_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_02_TX_INTERRUPT)) && (CAN_CONTROLLER_02_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_02_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_02_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_02_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_02_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_02_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_02_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_02_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_02_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_02_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_02_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_02_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_02_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller10*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_10_RX_INTERRUPT)) && (CAN_CONTROLLER_10_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_10_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_10_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_10_RX_INTERRUPT)) && (CAN_CONTROLLER_10_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_10_TX_INTERRUPT)) && (CAN_CONTROLLER_10_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_10_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_10_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_10_TX_INTERRUPT)) && (CAN_CONTROLLER_10_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_10_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_10_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_10_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_10_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_10_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_10_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_10_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_10_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_10_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_10_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_10_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_10_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller11*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_11_RX_INTERRUPT)) && (CAN_CONTROLLER_11_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_11_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_11_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_11_RX_INTERRUPT)) && (CAN_CONTROLLER_11_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_11_TX_INTERRUPT)) && (CAN_CONTROLLER_11_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_11_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_11_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_11_TX_INTERRUPT)) && (CAN_CONTROLLER_11_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_11_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_11_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_11_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_11_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_11_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_11_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_11_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_11_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_11_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_11_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_11_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_11_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller12*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_12_RX_INTERRUPT)) && (CAN_CONTROLLER_12_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_12_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_12_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_12_RX_INTERRUPT)) && (CAN_CONTROLLER_12_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_12_TX_INTERRUPT)) && (CAN_CONTROLLER_12_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_12_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_12_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_12_TX_INTERRUPT)) && (CAN_CONTROLLER_12_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_12_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_12_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_12_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_12_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_12_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_12_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_12_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_12_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_12_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_12_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_12_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_12_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller20*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_20_RX_INTERRUPT)) && (CAN_CONTROLLER_20_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_20_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_20_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_20_RX_INTERRUPT)) && (CAN_CONTROLLER_20_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_20_TX_INTERRUPT)) && (CAN_CONTROLLER_20_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_20_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_20_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_20_TX_INTERRUPT)) && (CAN_CONTROLLER_20_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_20_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_20_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_20_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_20_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_20_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_20_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_20_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_20_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_20_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_20_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_20_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_20_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller21*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_21_RX_INTERRUPT)) && (CAN_CONTROLLER_21_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_21_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_21_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_21_RX_INTERRUPT)) && (CAN_CONTROLLER_21_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_21_TX_INTERRUPT)) && (CAN_CONTROLLER_21_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_21_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_21_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_21_TX_INTERRUPT)) && (CAN_CONTROLLER_21_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_21_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_21_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_21_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_21_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_21_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_21_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_21_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_21_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_21_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_21_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_21_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_21_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller22*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_22_RX_INTERRUPT)) && (CAN_CONTROLLER_22_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_22_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_22_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_22_RX_INTERRUPT)) && (CAN_CONTROLLER_22_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_22_TX_INTERRUPT)) && (CAN_CONTROLLER_22_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_22_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_22_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_22_TX_INTERRUPT)) && (CAN_CONTROLLER_22_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_22_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_22_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_22_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_22_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_22_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_22_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_22_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_22_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_22_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_22_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_22_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_22_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller30*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_30_RX_INTERRUPT)) && (CAN_CONTROLLER_30_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_30_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_30_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_30_RX_INTERRUPT)) && (CAN_CONTROLLER_30_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_30_TX_INTERRUPT)) && (CAN_CONTROLLER_30_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_30_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_30_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_30_TX_INTERRUPT)) && (CAN_CONTROLLER_30_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_30_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_30_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_30_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_30_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_30_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_30_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_30_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_30_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_30_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_30_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_30_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_30_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller31*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_31_RX_INTERRUPT)) && (CAN_CONTROLLER_31_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_31_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_31_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_31_RX_INTERRUPT)) && (CAN_CONTROLLER_31_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_31_TX_INTERRUPT)) && (CAN_CONTROLLER_31_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_31_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_31_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_31_TX_INTERRUPT)) && (CAN_CONTROLLER_31_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_31_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_31_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_31_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_31_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_31_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_31_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_31_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_31_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_31_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_31_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_31_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_31_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller32*********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_32_RX_INTERRUPT)) && (CAN_CONTROLLER_32_RX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_32_RX_ISR(void)
{
    Can_MB_IRQHandler(CAN_CONTROLLER_32_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_32_RX_INTERRUPT)) && (CAN_CONTROLLER_32_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_32_TX_INTERRUPT)) && (CAN_CONTROLLER_32_TX_INTERRUPT == STD_ON))
void CAN_CONTROLLER_32_TX_ISR(void)
{
    Can_TxEvent_IRQHandler(CAN_CONTROLLER_32_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_32_TX_INTERRUPT)) && (CAN_CONTROLLER_32_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_32_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_32_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_32_BUSOFF_ISR(void)
{
    Can_BusOff_IRQHandler(CAN_CONTROLLER_32_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_32_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_32_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_32_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_32_RXFIFO_INTERRUPT == STD_ON))
void CAN_CONTROLLER_32_RXFIFO_ISR(void)
{
    Can_RXFIFO_IRQHandler(CAN_CONTROLLER_32_LOGIC_ID);
}
#endif /* ((defined(CAN_CONTROLLER_32_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_32_RXFIFO_INTERRUPT \== STD_ON)) */

/* #Violation: Can_Irq_c_REF_1 */
#define CAN_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Can_Irq_c_REF_2 */
#include "Can_MemMap.h"

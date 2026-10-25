/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Can_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MCAN
*
*   brief                 : This file contains all function declarations of Can Driver
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
*#Can_Irq_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*/

#ifndef CAN_INCLUDE_CAN_IRQ_H_
#define CAN_INCLUDE_CAN_IRQ_H_
/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "Can_Cfg.h"
#include "Mcall.h"
/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/

/***************************************************************************************************
*                               Extern Data Declaration
***************************************************************************************************/

/***************************************************************************************************
*                               Extern Function Declaration
***************************************************************************************************/
/* #Violation: Can_Irq_h_REF_1*/
#define CAN_START_SEC_CODE_ASIL_D_GLOBAL
#include "Can_MemMap.h"

/***************************************************************************************************/
/******************************Controller00**********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_00_RX_INTERRUPT)) && (CAN_CONTROLLER_00_RX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_00_RX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_00_RX_INTERRUPT)) && (CAN_CONTROLLER_00_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_00_TX_INTERRUPT)) && (CAN_CONTROLLER_00_TX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_00_TX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_00_TX_INTERRUPT)) && (CAN_CONTROLLER_00_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_00_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_00_BUSOFF_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_00_BUSOFF_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_00_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_00_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_00_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_00_RXFIFO_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_00_RXFIFO_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_00_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_00_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller01**********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_01_RX_INTERRUPT)) && (CAN_CONTROLLER_01_RX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_01_RX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_01_RX_INTERRUPT)) && (CAN_CONTROLLER_01_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_01_TX_INTERRUPT)) && (CAN_CONTROLLER_01_TX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_01_TX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_01_TX_INTERRUPT)) && (CAN_CONTROLLER_01_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_01_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_01_BUSOFF_INTERRUPT == STD_ON))
void CAN_CONTROLLER_01_BUSOFF_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_01_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_01_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_01_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_01_RXFIFO_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_01_RXFIFO_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_01_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_01_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller02**********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_02_RX_INTERRUPT)) && (CAN_CONTROLLER_02_RX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_02_RX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_02_RX_INTERRUPT)) && (CAN_CONTROLLER_02_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_02_TX_INTERRUPT)) && (CAN_CONTROLLER_02_TX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_02_TX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_02_TX_INTERRUPT)) && (CAN_CONTROLLER_02_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_02_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_02_BUSOFF_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_02_BUSOFF_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_02_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_02_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_02_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_02_RXFIFO_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_02_RXFIFO_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_02_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_02_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller10**********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_10_RX_INTERRUPT)) && (CAN_CONTROLLER_10_RX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_10_RX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_10_RX_INTERRUPT)) && (CAN_CONTROLLER_10_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_10_TX_INTERRUPT)) && (CAN_CONTROLLER_10_TX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_10_TX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_10_TX_INTERRUPT)) && (CAN_CONTROLLER_10_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_10_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_10_BUSOFF_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_10_BUSOFF_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_10_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_10_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_10_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_10_RXFIFO_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_10_RXFIFO_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_10_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_10_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller11**********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_11_RX_INTERRUPT)) && (CAN_CONTROLLER_11_RX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_11_RX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_11_RX_INTERRUPT)) && (CAN_CONTROLLER_11_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_11_TX_INTERRUPT)) && (CAN_CONTROLLER_11_TX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_11_TX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_11_TX_INTERRUPT)) && (CAN_CONTROLLER_11_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_11_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_11_BUSOFF_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_11_BUSOFF_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_11_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_11_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_11_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_11_RXFIFO_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_11_RXFIFO_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_11_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_11_RXFIFO_INTERRUPT \== STD_ON)) */

/***************************************************************************************************/
/******************************Controller12**********************************************************/
/***************************************************************************************************/
#if ((defined(CAN_CONTROLLER_12_RX_INTERRUPT)) && (CAN_CONTROLLER_12_RX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_12_RX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_12_RX_INTERRUPT)) && (CAN_CONTROLLER_12_RX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_12_TX_INTERRUPT)) && (CAN_CONTROLLER_12_TX_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_12_TX_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_12_TX_INTERRUPT)) && (CAN_CONTROLLER_12_TX_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_12_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_12_BUSOFF_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_12_BUSOFF_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_12_BUSOFF_INTERRUPT)) && (CAN_CONTROLLER_12_BUSOFF_INTERRUPT \== STD_ON)) */

#if ((defined(CAN_CONTROLLER_12_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_12_RXFIFO_INTERRUPT == STD_ON))
extern void CAN_CONTROLLER_12_RXFIFO_ISR(void);
#endif /* ((defined(CAN_CONTROLLER_12_RXFIFO_INTERRUPT)) && (CAN_CONTROLLER_12_RXFIFO_INTERRUPT \== STD_ON)) */

/* #Violation: Can_Irq_h_REF_1*/
#define CAN_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Can_MemMap.h"
#endif /* CAN_INCLUDE_CAN_IRQ_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

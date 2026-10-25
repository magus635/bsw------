/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Eth_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Ethernet
*
*   brief                 : This file contains all ISR function declarations of Ethernet Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef ETH_IRQ_H
#define ETH_IRQ_H

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Eth_Cfg.h"
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

#if (ETH_ENA_TX_INT == STD_ON)
extern void Eth_TX_Ctrl0_Channel0_ISR(void) ;
extern void Eth_TX_Ctrl0_Channel1_ISR(void) ;
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern void Eth_TX_Ctrl0_Channel2_ISR(void) ;
extern void Eth_TX_Ctrl0_Channel3_ISR(void) ;
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
#endif /* (ETH_ENA_TX_INT  \== STD_ON) */

#if (ETH_ENA_RX_INT == STD_ON)
extern void Eth_RX_Ctrl0_Channel0_ISR(void) ;
extern void Eth_RX_Ctrl0_Channel1_ISR(void) ;
#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
extern void Eth_RX_Ctrl0_Channel2_ISR(void) ;
extern void Eth_RX_Ctrl0_Channel3_ISR(void) ;
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
#endif /* (ETH_ENA_RX_INT \== STD_ON)) */

#endif /* ETH_IRQ_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

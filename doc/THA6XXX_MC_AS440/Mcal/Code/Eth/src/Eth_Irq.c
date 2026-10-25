/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Eth_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Ethernet
*
*   brief                 : This file contains all ISR functions of Ethernet Driver
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
*#Eth_Irq_c_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the
*driver must be placed.
*
*#Eth_Irq_c_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
 */
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Eth_Irq.h"
#include "Mcall_Cfg.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Eth_Irq_c_REF_2*/
#define ETH_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Eth_Irq_c_REF_1*/
#include "Eth_MemMap.h"

extern FUNC(void, ETH_FAST_CODE) Eth_TX_ISRHandler(uint8 CtrlIdx, uint8 ChannelId);
extern FUNC(void, ETH_FAST_CODE) Eth_RX_ISRHandler(uint8 CtrlIdx, uint8 ChannelId);
#if (ETH_ENA_TX_INT == STD_ON)
/****************************************************************************************************
*   Function Name           : Eth_TX_Ctrl0_Channel0_ISR
*
*   Service ID              : None.
*
*   Description             : This function processes controller 0 's channel 0
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
void Eth_TX_Ctrl0_Channel0_ISR(void)
{
    Eth_TX_ISRHandler(0U, 0U);
}

/****************************************************************************************************
*   Function Name           : Eth_TX_Ctrl0_Channel1_ISR
*
*   Service ID              : None.
*
*   Description             : This function processes controller 0 's dma channel 1
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
void Eth_TX_Ctrl0_Channel1_ISR(void)
{
    Eth_TX_ISRHandler(0U, 1U);
}

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
*   Function Name           : Eth_TX_Ctrl0_Channel2_ISR
*
*   Service ID              : None.
*
*   Description             : This function processes controller 0 's dma channel 2
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
void Eth_TX_Ctrl0_Channel2_ISR(void)
{
    Eth_TX_ISRHandler(0U, 2U);
}

/****************************************************************************************************
*   Function Name           : Eth_TX_Ctrl0_Channel3_ISR
*
*   Service ID              : None.
*
*   Description             : This function processes controller 0 's dma channel 3
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
void Eth_TX_Ctrl0_Channel3_ISR(void)
{
    Eth_TX_ISRHandler(0U, 3U);
}
#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
#endif /* (ETH_ENA_TX_INT  \== STD_ON) */

#if (ETH_ENA_RX_INT == STD_ON)
/****************************************************************************************************
*   Function Name           : Eth_RX_Ctrl0_Channel0_ISR
*
*   Service ID              : None.
*
*   Description             : This function processes controller 0 's channel 0
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
void Eth_RX_Ctrl0_Channel0_ISR(void) 
{
    Eth_RX_ISRHandler(0U, 0U);
}
/****************************************************************************************************
*   Function Name           : Eth_RX_Ctrl0_Channel1_ISR
*
*   Service ID              : None.
*
*   Description             : This function processes controller 0 's channel 1
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
void Eth_RX_Ctrl0_Channel1_ISR(void) 
{
    Eth_RX_ISRHandler(0U, 1U);
}

#if ((MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516))
/****************************************************************************************************
*   Function Name           : Eth_RX_Ctrl0_Channel2_ISR
*
*   Service ID              : None.
*
*   Description             : This function processes controller 0 's channel 2
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
void Eth_RX_Ctrl0_Channel2_ISR(void) 
{
    Eth_RX_ISRHandler(0U, 2U);
}
/****************************************************************************************************
*   Function Name           : Eth_RX_Ctrl0_Channel3_ISR
*
*   Service ID              : None.
*
*   Description             : This function processes controller 0 's channel 3
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
void Eth_RX_Ctrl0_Channel3_ISR(void) 
{
    Eth_RX_ISRHandler(0U, 3U);
}

#endif /* ((MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6206_LFBGA292) || (MCAL_PROCESSOR_CAT \== MCAL_PROCESSOR_THA6412_BGA516)) */
#endif /* (ETH_ENA_RX_INT  \== STD_ON) */

/* #Violation: Eth_Irq_c_REF_2 */
#define ETH_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Eth_Irq_c_REF_1*/
#include "Eth_MemMap.h"
/*******************************************************************************
**                      End of File                           **
*******************************************************************************/

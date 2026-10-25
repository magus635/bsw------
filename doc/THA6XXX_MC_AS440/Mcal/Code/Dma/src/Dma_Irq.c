/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dma_Irq.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DMA
*
*   brief                 : This file contains all ISR functions of Dma Driver
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
*#Dma_Irq_c_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the
*   driver must be placed.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dma_Irq.h"
#include "Mcall_Cfg.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dma_MemMap.h"

#if (DMA_CFG_INTERRUPT_EN == STD_ON)
/****************************************************************************************************
*   Function Name           : Dma_Dma<m>Channel<n>_ISR(<m> = DMA HW unit number,
*                                                      <n> = Physical channel number)
*
*   Service ID              : None.
*
*   Description             : Interrupt routine entry for each DMA channel.
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
#if (defined(DMA_HWUNIT_DMA0) && (DMA_HWUNIT_DMA0 == 0U))
/* DMA0 used */

#if (defined(DMA_DMA0_PHYCHANNEL0) && (DMA_DMA0_PHYCHANNEL0 == 0U))
#if (defined(DMA_CFG_DMA0_CHANNEL0_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 0. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel0_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL0_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL0_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL0_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL0_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL0_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL0_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL0_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL0_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL0_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL0_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL0_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL0_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL0_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL0) && (DMA_DMA0_PHYCHANNEL0 == 0U)) */

#if (defined(DMA_DMA0_PHYCHANNEL1) && (DMA_DMA0_PHYCHANNEL1 == 1U))
#if (defined(DMA_CFG_DMA0_CHANNEL1_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 1. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel1_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL1_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL1_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL1_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL1_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL1_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL1_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL1_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL1_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL1_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL1_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL1_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL1_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL1_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL1) && (DMA_DMA0_PHYCHANNEL1 == 1U)) */

#if (defined(DMA_DMA0_PHYCHANNEL2) && (DMA_DMA0_PHYCHANNEL2 == 2U))
#if (defined(DMA_CFG_DMA0_CHANNEL2_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 2. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel2_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL2_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL2_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL2_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL2_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL2_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL2_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL2_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL2_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL2_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL2_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL2_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL2_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL2_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL2) && (DMA_DMA0_PHYCHANNEL2 == 2U)) */

#if (defined(DMA_DMA0_PHYCHANNEL3) && (DMA_DMA0_PHYCHANNEL3 == 3U))
#if (defined(DMA_CFG_DMA0_CHANNEL3_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 3. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel3_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL3_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL3_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL3_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL3_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL3_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL3_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL3_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL3_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL3_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL3_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL3_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL3_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL3_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL3) && (DMA_DMA0_PHYCHANNEL3 == 3U)) */

#if (defined(DMA_DMA0_PHYCHANNEL4) && (DMA_DMA0_PHYCHANNEL4 == 4U))
#if (defined(DMA_CFG_DMA0_CHANNEL4_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 4. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel4_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL4_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL4_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL4_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL4_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL4_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL4_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL4_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL4_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL4_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL4_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL4_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL4_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL4_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL4) && (DMA_DMA0_PHYCHANNEL4 == 4U)) */

#if (defined(DMA_DMA0_PHYCHANNEL5) && (DMA_DMA0_PHYCHANNEL5 == 5U))
#if (defined(DMA_CFG_DMA0_CHANNEL5_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 5. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel5_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL5_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL5_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL5_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL5_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL5_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL5_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL5_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL5_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL5_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL5_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL5_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL5_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL5_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL5) && (DMA_DMA0_PHYCHANNEL5 == 5U)) */

#if (defined(DMA_DMA0_PHYCHANNEL6) && (DMA_DMA0_PHYCHANNEL6 == 6U))
#if (defined(DMA_CFG_DMA0_CHANNEL6_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 6. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel6_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL6_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL6_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL6_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL6_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL6_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL6_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL6_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL6_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL6_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL6_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL6_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL6_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL6_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL6) && (DMA_DMA0_PHYCHANNEL6 == 6U)) */

#if (defined(DMA_DMA0_PHYCHANNEL7) && (DMA_DMA0_PHYCHANNEL7 == 7U))
#if (defined(DMA_CFG_DMA0_CHANNEL7_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 7. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel7_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL7_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL7_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL7_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL7_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL7_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL7_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL7_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL7_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL7_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL7_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL7_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL7_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL7_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL7) && (DMA_DMA0_PHYCHANNEL7 == 7U)) */

#if (defined(DMA_DMA0_PHYCHANNEL8) && (DMA_DMA0_PHYCHANNEL8 == 8U))
#if (defined(DMA_CFG_DMA0_CHANNEL8_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 8. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel8_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL8_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL8_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL8_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL8_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL8_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL8_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL8_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL8_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL8_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL8_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL8_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL8_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL8_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL8) && (DMA_DMA0_PHYCHANNEL8 == 8U)) */

#if (defined(DMA_DMA0_PHYCHANNEL9) && (DMA_DMA0_PHYCHANNEL9 == 9U))
#if (defined(DMA_CFG_DMA0_CHANNEL9_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 9. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel9_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL9_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL9_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL9_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL9_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL9_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL9_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL9_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL9_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL9_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL9_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL9_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL9_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL9_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL9) && (DMA_DMA0_PHYCHANNEL9 == 9U)) */

#if (defined(DMA_DMA0_PHYCHANNEL10) && (DMA_DMA0_PHYCHANNEL10 == 10U))
#if (defined(DMA_CFG_DMA0_CHANNEL10_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 10. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel10_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL10_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL10_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL10_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL10_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL10_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL10_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL10_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL10_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL10_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL10_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL10_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL10_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL10_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL10) && (DMA_DMA0_PHYCHANNEL10 == 10U)) */

#if (defined(DMA_DMA0_PHYCHANNEL11) && (DMA_DMA0_PHYCHANNEL11 == 11U))
#if (defined(DMA_CFG_DMA0_CHANNEL11_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 11. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel11_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL11_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL11_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL11_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL11_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL11_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL11_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL11_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL11_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL11_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL11_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL11_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL11_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL11_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL11) && (DMA_DMA0_PHYCHANNEL11 == 11U)) */

#if (defined(DMA_DMA0_PHYCHANNEL12) && (DMA_DMA0_PHYCHANNEL12 == 12U))
#if (defined(DMA_CFG_DMA0_CHANNEL12_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 12. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel12_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL12_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL12_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL12_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL12_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL12_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL12_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL12_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL12_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL12_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL12_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL12_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL12_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL12_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL12) && (DMA_DMA0_PHYCHANNEL12 == 12U)) */

#if (defined(DMA_DMA0_PHYCHANNEL13) && (DMA_DMA0_PHYCHANNEL13 == 13U))
#if (defined(DMA_CFG_DMA0_CHANNEL13_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 13. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel13_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL13_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL13_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL13_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL13_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL13_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL13_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL13_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL13_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL13_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL13_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL13_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL13_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL13_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL13) && (DMA_DMA0_PHYCHANNEL13 == 13U)) */

#if (defined(DMA_DMA0_PHYCHANNEL14) && (DMA_DMA0_PHYCHANNEL14 == 14U))
#if (defined(DMA_CFG_DMA0_CHANNEL14_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 14. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel14_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL14_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL14_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL14_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL14_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL14_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL14_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL14_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL14_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL14_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL14_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL14_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL14_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL14_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL14) && (DMA_DMA0_PHYCHANNEL14 == 14U)) */

#if (defined(DMA_DMA0_PHYCHANNEL15) && (DMA_DMA0_PHYCHANNEL15 == 15U))
#if (defined(DMA_CFG_DMA0_CHANNEL15_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA0 physical channel 15. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel15_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL15_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL15_TC_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL15_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL15_RTC_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL15_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL15_ERROR_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL15_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL15_SRC_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL15_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL15_DEST_CB_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA0_CHANNEL15_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA0, DMA_DMA0_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL15_PATTERN_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL15_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL15) && (DMA_DMA0_PHYCHANNEL15 == 15U)) */

#endif /* \(defined(DMA_HWUNIT_DMA0) && (DMA_HWUNIT_DMA0 == 0U)) */

#if (defined(DMA_HWUNIT_DMA1) && (DMA_HWUNIT_DMA1 == 1U))
/* DMA1 used */

#if (defined(DMA_DMA1_PHYCHANNEL0) && (DMA_DMA1_PHYCHANNEL0 == 0U))
#if (defined(DMA_CFG_DMA1_CHANNEL0_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 0. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel0_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL0_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL0_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL0_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL0_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL0_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL0_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL0_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL0_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL0_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL0_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL0_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL0_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL0_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL0) && (DMA_DMA1_PHYCHANNEL0 == 0U)) */

#if (defined(DMA_DMA1_PHYCHANNEL1) && (DMA_DMA1_PHYCHANNEL1 == 1U))
#if (defined(DMA_CFG_DMA1_CHANNEL1_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 1. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel1_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL1_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL1_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL1_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL1_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL1_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL1_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL1_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL1_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL1_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL1_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL1_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL1_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL1_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL1) && (DMA_DMA1_PHYCHANNEL1 == 1U)) */

#if (defined(DMA_DMA1_PHYCHANNEL2) && (DMA_DMA1_PHYCHANNEL2 == 2U))
#if (defined(DMA_CFG_DMA1_CHANNEL2_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 2. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel2_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL2_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL2_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL2_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL2_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL2_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL2_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL2_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL2_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL2_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL2_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL2_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL2_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL2_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL2) && (DMA_DMA1_PHYCHANNEL2 == 2U)) */

#if (defined(DMA_DMA1_PHYCHANNEL3) && (DMA_DMA1_PHYCHANNEL3 == 3U))
#if (defined(DMA_CFG_DMA1_CHANNEL3_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 3. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel3_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL3_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL3_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL3_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL3_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL3_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL3_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL3_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL3_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL3_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL3_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL3_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL3_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL3_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL3) && (DMA_DMA1_PHYCHANNEL3 == 3U)) */

#if (defined(DMA_DMA1_PHYCHANNEL4) && (DMA_DMA1_PHYCHANNEL4 == 4U))
#if (defined(DMA_CFG_DMA1_CHANNEL4_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 4. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel4_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL4_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL4_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL4_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL4_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL4_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL4_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL4_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL4_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL4_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL4_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL4_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL4_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL4_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL4) && (DMA_DMA1_PHYCHANNEL4 == 4U)) */

#if (defined(DMA_DMA1_PHYCHANNEL5) && (DMA_DMA1_PHYCHANNEL5 == 5U))
#if (defined(DMA_CFG_DMA1_CHANNEL5_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 5. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel5_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL5_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL5_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL5_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL5_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL5_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL5_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL5_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL5_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL5_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL5_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL5_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL5_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL5_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL5) && (DMA_DMA1_PHYCHANNEL5 == 5U)) */

#if (defined(DMA_DMA1_PHYCHANNEL6) && (DMA_DMA1_PHYCHANNEL6 == 6U))
#if (defined(DMA_CFG_DMA1_CHANNEL6_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 6. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel6_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL6_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL6_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL6_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL6_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL6_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL6_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL6_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL6_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL6_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL6_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL6_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL6_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL6_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL6) && (DMA_DMA1_PHYCHANNEL6 == 6U)) */

#if (defined(DMA_DMA1_PHYCHANNEL7) && (DMA_DMA1_PHYCHANNEL7 == 7U))
#if (defined(DMA_CFG_DMA1_CHANNEL7_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 7. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel7_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL7_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL7_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL7_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL7_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL7_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL7_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL7_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL7_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL7_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL7_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL7_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL7_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL7_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL7) && (DMA_DMA1_PHYCHANNEL7 == 7U)) */

#if (defined(DMA_DMA1_PHYCHANNEL8) && (DMA_DMA1_PHYCHANNEL8 == 8U))
#if (defined(DMA_CFG_DMA1_CHANNEL8_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 8. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel8_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL8_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL8_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL8_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL8_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL8_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL8_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL8_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL8_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL8_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL8_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL8_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL8_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL8_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL8) && (DMA_DMA1_PHYCHANNEL8 == 8U)) */

#if (defined(DMA_DMA1_PHYCHANNEL9) && (DMA_DMA1_PHYCHANNEL9 == 9U))
#if (defined(DMA_CFG_DMA1_CHANNEL9_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 9. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel9_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL9_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL9_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL9_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL9_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL9_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL9_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL9_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL9_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL9_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL9_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL9_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL9_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL9_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL9) && (DMA_DMA1_PHYCHANNEL9 == 9U)) */

#if (defined(DMA_DMA1_PHYCHANNEL10) && (DMA_DMA1_PHYCHANNEL10 == 10U))
#if (defined(DMA_CFG_DMA1_CHANNEL10_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 10. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel10_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL10_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL10_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL10_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL10_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL10_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL10_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL10_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL10_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL10_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL10_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL10_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL10_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL10_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL10) && (DMA_DMA1_PHYCHANNEL10 == 10U)) */

#if (defined(DMA_DMA1_PHYCHANNEL11) && (DMA_DMA1_PHYCHANNEL11 == 11U))
#if (defined(DMA_CFG_DMA1_CHANNEL11_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 11. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel11_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL11_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL11_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL11_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL11_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL11_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL11_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL11_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL11_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL11_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL11_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL11_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL11_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL11_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL11) && (DMA_DMA1_PHYCHANNEL11 == 11U)) */

#if (defined(DMA_DMA1_PHYCHANNEL12) && (DMA_DMA1_PHYCHANNEL12 == 12U))
#if (defined(DMA_CFG_DMA1_CHANNEL12_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 12. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel12_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL12_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL12_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL12_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL12_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL12_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL12_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL12_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL12_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL12_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL12_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL12_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL12_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL12_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL12) && (DMA_DMA1_PHYCHANNEL12 == 12U)) */

#if (defined(DMA_DMA1_PHYCHANNEL13) && (DMA_DMA1_PHYCHANNEL13 == 13U))
#if (defined(DMA_CFG_DMA1_CHANNEL13_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 13. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel13_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL13_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL13_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL13_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL13_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL13_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL13_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL13_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL13_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL13_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL13_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL13_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL13_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL13_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL13) && (DMA_DMA1_PHYCHANNEL13 == 13U)) */

#if (defined(DMA_DMA1_PHYCHANNEL14) && (DMA_DMA1_PHYCHANNEL14 == 14U))
#if (defined(DMA_CFG_DMA1_CHANNEL14_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 14. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel14_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL14_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL14_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL14_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL14_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL14_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL14_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL14_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL14_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL14_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL14_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL14_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL14_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL14_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL14) && (DMA_DMA1_PHYCHANNEL14 == 14U)) */

#if (defined(DMA_DMA1_PHYCHANNEL15) && (DMA_DMA1_PHYCHANNEL15 == 15U))
#if (defined(DMA_CFG_DMA1_CHANNEL15_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 15. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel15_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL15_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL15_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL15_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL15_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL15_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL15_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL15_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL15_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL15_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL15_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL15_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL15_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL15_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL15) && (DMA_DMA1_PHYCHANNEL15 == 15U)) */

#if (defined(DMA_DMA1_PHYCHANNEL16) && (DMA_DMA1_PHYCHANNEL16 == 16U))
#if (defined(DMA_CFG_DMA1_CHANNEL16_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 16. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel16_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL16_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL16_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL16_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL16_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL16_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL16_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL16_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL16_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL16_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL16_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL16_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL16_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL16_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL16) && (DMA_DMA1_PHYCHANNEL16 == 16U)) */

#if (defined(DMA_DMA1_PHYCHANNEL17) && (DMA_DMA1_PHYCHANNEL17 == 17U))
#if (defined(DMA_CFG_DMA1_CHANNEL17_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 17. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel17_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL17_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL17_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL17_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL17_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL17_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL17_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL17_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL17_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL17_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL17_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL17_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL17_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL17_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL17) && (DMA_DMA1_PHYCHANNEL17 == 17U)) */

#if (defined(DMA_DMA1_PHYCHANNEL18) && (DMA_DMA1_PHYCHANNEL18 == 18U))
#if (defined(DMA_CFG_DMA1_CHANNEL18_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 18. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel18_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL18_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL18_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL18_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL18_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL18_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL18_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL18_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL18_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL18_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL18_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL18_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL18_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL18_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL18) && (DMA_DMA1_PHYCHANNEL18 == 18U)) */

#if (defined(DMA_DMA1_PHYCHANNEL19) && (DMA_DMA1_PHYCHANNEL19 == 19U))
#if (defined(DMA_CFG_DMA1_CHANNEL19_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 19. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel19_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL19_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL19_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL19_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL19_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL19_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL19_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL19_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL19_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL19_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL19_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL19_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL19_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL19_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL19) && (DMA_DMA1_PHYCHANNEL19 == 19U)) */

#if (defined(DMA_DMA1_PHYCHANNEL20) && (DMA_DMA1_PHYCHANNEL20 == 20U))
#if (defined(DMA_CFG_DMA1_CHANNEL20_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 20. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel20_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL20_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL20_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL20_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL20_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL20_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL20_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL20_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL20_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL20_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL20_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL20_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL20_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL20_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL20) && (DMA_DMA1_PHYCHANNEL20 == 20U)) */

#if (defined(DMA_DMA1_PHYCHANNEL21) && (DMA_DMA1_PHYCHANNEL21 == 21U))
#if (defined(DMA_CFG_DMA1_CHANNEL21_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 21. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel21_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL21_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL21_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL21_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL21_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL21_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL21_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL21_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL21_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL21_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL21_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL21_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL21_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL21_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL21) && (DMA_DMA1_PHYCHANNEL21 == 21U)) */

#if (defined(DMA_DMA1_PHYCHANNEL22) && (DMA_DMA1_PHYCHANNEL22 == 22U))
#if (defined(DMA_CFG_DMA1_CHANNEL22_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 22. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel22_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL22_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL22_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL22_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL22_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL22_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL22_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL22_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL22_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL22_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL22_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL22_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL22_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL22_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL22) && (DMA_DMA1_PHYCHANNEL22 == 22U)) */

#if (defined(DMA_DMA1_PHYCHANNEL23) && (DMA_DMA1_PHYCHANNEL23 == 23U))
#if (defined(DMA_CFG_DMA1_CHANNEL23_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 23. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel23_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL23_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL23_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL23_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL23_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL23_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL23_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL23_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL23_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL23_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL23_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL23_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL23_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL23_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL23) && (DMA_DMA1_PHYCHANNEL23 == 23U)) */

#if (defined(DMA_DMA1_PHYCHANNEL24) && (DMA_DMA1_PHYCHANNEL24 == 24U))
#if (defined(DMA_CFG_DMA1_CHANNEL24_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 24. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel24_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL24_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL24_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL24_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL24_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL24_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL24_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL24_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL24_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL24_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL24_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL24_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL24_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL24_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL24) && (DMA_DMA1_PHYCHANNEL24 == 24U)) */

#if (defined(DMA_DMA1_PHYCHANNEL25) && (DMA_DMA1_PHYCHANNEL25 == 25U))
#if (defined(DMA_CFG_DMA1_CHANNEL25_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 25. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel25_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL25_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL25_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL25_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL25_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL25_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL25_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL25_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL25_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL25_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL25_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL25_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL25_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL25_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL25) && (DMA_DMA1_PHYCHANNEL25 == 25U)) */

#if (defined(DMA_DMA1_PHYCHANNEL26) && (DMA_DMA1_PHYCHANNEL26 == 26U))
#if (defined(DMA_CFG_DMA1_CHANNEL26_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 26. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel26_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL26_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL26_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL26_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL26_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL26_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL26_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL26_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL26_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL26_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL26_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL26_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL26_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL26_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL26) && (DMA_DMA1_PHYCHANNEL26 == 26U)) */

#if (defined(DMA_DMA1_PHYCHANNEL27) && (DMA_DMA1_PHYCHANNEL27 == 27U))
#if (defined(DMA_CFG_DMA1_CHANNEL27_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 27. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel27_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL27_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL27_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL27_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL27_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL27_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL27_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL27_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL27_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL27_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL27_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL27_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL27_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL27_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL27) && (DMA_DMA1_PHYCHANNEL27 == 27U)) */

#if (defined(DMA_DMA1_PHYCHANNEL28) && (DMA_DMA1_PHYCHANNEL28 == 28U))
#if (defined(DMA_CFG_DMA1_CHANNEL28_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 28. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel28_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL28_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL28_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL28_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL28_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL28_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL28_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL28_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL28_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL28_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL28_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL28_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL28_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL28_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL28) && (DMA_DMA1_PHYCHANNEL28 == 28U)) */

#if (defined(DMA_DMA1_PHYCHANNEL29) && (DMA_DMA1_PHYCHANNEL29 == 29U))
#if (defined(DMA_CFG_DMA1_CHANNEL29_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 29. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel29_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL29_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL29_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL29_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL29_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL29_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL29_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL29_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL29_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL29_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL29_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL29_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL29_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL29_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL29) && (DMA_DMA1_PHYCHANNEL29 == 29U)) */

#if (defined(DMA_DMA1_PHYCHANNEL30) && (DMA_DMA1_PHYCHANNEL30 == 30U))
#if (defined(DMA_CFG_DMA1_CHANNEL30_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 30. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel30_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL30_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL30_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL30_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL30_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL30_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL30_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL30_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL30_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL30_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL30_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL30_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL30_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL30_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL30) && (DMA_DMA1_PHYCHANNEL30 == 30U)) */

#if (defined(DMA_DMA1_PHYCHANNEL31) && (DMA_DMA1_PHYCHANNEL31 == 31U))
#if (defined(DMA_CFG_DMA1_CHANNEL31_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 31. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel31_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL31_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL31_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL31_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL31_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL31_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL31_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL31_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL31_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL31_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL31_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL31_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL31_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL31_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL31) && (DMA_DMA1_PHYCHANNEL31 == 31U)) */

#if (defined(DMA_DMA1_PHYCHANNEL32) && (DMA_DMA1_PHYCHANNEL32 == 32U))
#if (defined(DMA_CFG_DMA1_CHANNEL32_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 32. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel32_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL32_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL32_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL32_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL32_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL32_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL32_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL32_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL32_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL32_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL32_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL32_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL32_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL32_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL32) && (DMA_DMA1_PHYCHANNEL32 == 32U)) */

#if (defined(DMA_DMA1_PHYCHANNEL33) && (DMA_DMA1_PHYCHANNEL33 == 33U))
#if (defined(DMA_CFG_DMA1_CHANNEL33_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 33. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel33_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL33_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL33_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL33_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL33_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL33_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL33_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL33_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL33_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL33_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL33_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL33_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL33_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL33_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL33) && (DMA_DMA1_PHYCHANNEL33 == 33U)) */

#if (defined(DMA_DMA1_PHYCHANNEL34) && (DMA_DMA1_PHYCHANNEL34 == 34U))
#if (defined(DMA_CFG_DMA1_CHANNEL34_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 34. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel34_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL34_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL34_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL34_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL34_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL34_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL34_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL34_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL34_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL34_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL34_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL34_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL34_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL34_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL34) && (DMA_DMA1_PHYCHANNEL34 == 34U)) */

#if (defined(DMA_DMA1_PHYCHANNEL35) && (DMA_DMA1_PHYCHANNEL35 == 35U))
#if (defined(DMA_CFG_DMA1_CHANNEL35_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 35. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel35_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL35_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL35_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL35_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL35_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL35_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL35_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL35_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL35_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL35_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL35_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL35_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL35_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL35_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL35) && (DMA_DMA1_PHYCHANNEL35 == 35U)) */

#if (defined(DMA_DMA1_PHYCHANNEL36) && (DMA_DMA1_PHYCHANNEL36 == 36U))
#if (defined(DMA_CFG_DMA1_CHANNEL36_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 36. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel36_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL36_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL36_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL36_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL36_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL36_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL36_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL36_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL36_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL36_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL36_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL36_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL36_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL36_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL36) && (DMA_DMA1_PHYCHANNEL36 == 36U)) */

#if (defined(DMA_DMA1_PHYCHANNEL37) && (DMA_DMA1_PHYCHANNEL37 == 37U))
#if (defined(DMA_CFG_DMA1_CHANNEL37_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 37. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel37_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL37_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL37_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL37_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL37_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL37_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL37_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL37_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL37_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL37_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL37_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL37_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL37_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL37_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL37) && (DMA_DMA1_PHYCHANNEL37 == 37U)) */

#if (defined(DMA_DMA1_PHYCHANNEL38) && (DMA_DMA1_PHYCHANNEL38 == 38U))
#if (defined(DMA_CFG_DMA1_CHANNEL38_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 38. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel38_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL38_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL38_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL38_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL38_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL38_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL38_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL38_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL38_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL38_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL38_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL38_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL38_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL38_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL38) && (DMA_DMA1_PHYCHANNEL38 == 38U)) */

#if (defined(DMA_DMA1_PHYCHANNEL39) && (DMA_DMA1_PHYCHANNEL39 == 39U))
#if (defined(DMA_CFG_DMA1_CHANNEL39_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 39. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel39_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL39_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL39_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL39_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL39_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL39_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL39_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL39_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL39_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL39_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL39_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL39_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL39_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL39_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL39) && (DMA_DMA1_PHYCHANNEL39 == 39U)) */

#if (defined(DMA_DMA1_PHYCHANNEL40) && (DMA_DMA1_PHYCHANNEL40 == 40U))
#if (defined(DMA_CFG_DMA1_CHANNEL40_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 40. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel40_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL40_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL40_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL40_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL40_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL40_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL40_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL40_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL40_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL40_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL40_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL40_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL40_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL40_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL40) && (DMA_DMA1_PHYCHANNEL40 == 40U)) */

#if (defined(DMA_DMA1_PHYCHANNEL41) && (DMA_DMA1_PHYCHANNEL41 == 41U))
#if (defined(DMA_CFG_DMA1_CHANNEL41_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 41. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel41_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL41_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL41_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL41_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL41_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL41_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL41_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL41_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL41_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL41_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL41_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL41_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL41_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL41_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL41) && (DMA_DMA1_PHYCHANNEL41 == 41U)) */

#if (defined(DMA_DMA1_PHYCHANNEL42) && (DMA_DMA1_PHYCHANNEL42 == 42U))
#if (defined(DMA_CFG_DMA1_CHANNEL42_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 42. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel42_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL42_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL42_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL42_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL42_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL42_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL42_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL42_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL42_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL42_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL42_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL42_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL42_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL42_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL42) && (DMA_DMA1_PHYCHANNEL42 == 42U)) */

#if (defined(DMA_DMA1_PHYCHANNEL43) && (DMA_DMA1_PHYCHANNEL43 == 43U))
#if (defined(DMA_CFG_DMA1_CHANNEL43_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 43. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel43_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL43_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL43_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL43_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL43_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL43_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL43_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL43_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL43_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL43_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL43_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL43_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL43_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL43_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL43) && (DMA_DMA1_PHYCHANNEL43 == 43U)) */

#if (defined(DMA_DMA1_PHYCHANNEL44) && (DMA_DMA1_PHYCHANNEL44 == 44U))
#if (defined(DMA_CFG_DMA1_CHANNEL44_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 44. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel44_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL44_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL44);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL44_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL44_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL44);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL44_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL44_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL44);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL44_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL44_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL44);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL44_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL44_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL44);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL44_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL44_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL44);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL44_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL44_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL44) && (DMA_DMA1_PHYCHANNEL44 == 44U)) */

#if (defined(DMA_DMA1_PHYCHANNEL45) && (DMA_DMA1_PHYCHANNEL45 == 45U))
#if (defined(DMA_CFG_DMA1_CHANNEL45_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 45. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel45_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL45_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL45);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL45_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL45_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL45);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL45_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL45_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL45);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL45_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL45_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL45);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL45_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL45_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL45);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL45_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL45_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL45);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL45_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL45_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL45) && (DMA_DMA1_PHYCHANNEL45 == 45U)) */

#if (defined(DMA_DMA1_PHYCHANNEL46) && (DMA_DMA1_PHYCHANNEL46 == 46U))
#if (defined(DMA_CFG_DMA1_CHANNEL46_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 46. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel46_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL46_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL46);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL46_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL46_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL46);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL46_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL46_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL46);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL46_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL46_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL46);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL46_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL46_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL46);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL46_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL46_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL46);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL46_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL46_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL46) && (DMA_DMA1_PHYCHANNEL46 == 46U)) */

#if (defined(DMA_DMA1_PHYCHANNEL47) && (DMA_DMA1_PHYCHANNEL47 == 47U))
#if (defined(DMA_CFG_DMA1_CHANNEL47_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 47. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel47_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL47_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL47);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL47_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL47_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL47);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL47_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL47_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL47);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL47_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL47_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL47);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL47_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL47_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL47);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL47_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL47_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL47);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL47_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL47_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL47) && (DMA_DMA1_PHYCHANNEL47 == 47U)) */

#if (defined(DMA_DMA1_PHYCHANNEL48) && (DMA_DMA1_PHYCHANNEL48 == 48U))
#if (defined(DMA_CFG_DMA1_CHANNEL48_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 48. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel48_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL48_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL48);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL48_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL48_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL48);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL48_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL48_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL48);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL48_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL48_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL48);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL48_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL48_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL48);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL48_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL48_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL48);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL48_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL48_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL48) && (DMA_DMA1_PHYCHANNEL48 == 48U)) */

#if (defined(DMA_DMA1_PHYCHANNEL49) && (DMA_DMA1_PHYCHANNEL49 == 49U))
#if (defined(DMA_CFG_DMA1_CHANNEL49_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 49. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel49_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL49_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL49);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL49_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL49_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL49);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL49_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL49_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL49);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL49_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL49_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL49);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL49_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL49_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL49);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL49_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL49_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL49);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL49_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL49_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL49) && (DMA_DMA1_PHYCHANNEL49 == 49U)) */

#if (defined(DMA_DMA1_PHYCHANNEL50) && (DMA_DMA1_PHYCHANNEL50 == 50U))
#if (defined(DMA_CFG_DMA1_CHANNEL50_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 50. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel50_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL50_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL50);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL50_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL50_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL50);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL50_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL50_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL50);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL50_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL50_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL50);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL50_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL50_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL50);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL50_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL50_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL50);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL50_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL50_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL50) && (DMA_DMA1_PHYCHANNEL50 == 50U)) */

#if (defined(DMA_DMA1_PHYCHANNEL51) && (DMA_DMA1_PHYCHANNEL51 == 51U))
#if (defined(DMA_CFG_DMA1_CHANNEL51_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 51. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel51_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL51_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL51);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL51_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL51_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL51);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL51_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL51_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL51);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL51_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL51_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL51);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL51_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL51_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL51);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL51_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL51_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL51);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL51_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL51_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL51) && (DMA_DMA1_PHYCHANNEL51 == 51U)) */

#if (defined(DMA_DMA1_PHYCHANNEL52) && (DMA_DMA1_PHYCHANNEL52 == 52U))
#if (defined(DMA_CFG_DMA1_CHANNEL52_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 52. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel52_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL52_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL52);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL52_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL52_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL52);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL52_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL52_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL52);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL52_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL52_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL52);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL52_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL52_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL52);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL52_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL52_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL52);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL52_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL52_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL52) && (DMA_DMA1_PHYCHANNEL52 == 52U)) */

#if (defined(DMA_DMA1_PHYCHANNEL53) && (DMA_DMA1_PHYCHANNEL53 == 53U))
#if (defined(DMA_CFG_DMA1_CHANNEL53_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 53. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel53_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL53_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL53);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL53_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL53_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL53);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL53_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL53_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL53);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL53_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL53_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL53);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL53_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL53_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL53);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL53_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL53_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL53);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL53_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL53_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL53) && (DMA_DMA1_PHYCHANNEL53 == 53U)) */

#if (defined(DMA_DMA1_PHYCHANNEL54) && (DMA_DMA1_PHYCHANNEL54 == 54U))
#if (defined(DMA_CFG_DMA1_CHANNEL54_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 54. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel54_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL54_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL54);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL54_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL54_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL54);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL54_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL54_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL54);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL54_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL54_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL54);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL54_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL54_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL54);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL54_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL54_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL54);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL54_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL54_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL54) && (DMA_DMA1_PHYCHANNEL54 == 54U)) */

#if (defined(DMA_DMA1_PHYCHANNEL55) && (DMA_DMA1_PHYCHANNEL55 == 55U))
#if (defined(DMA_CFG_DMA1_CHANNEL55_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 55. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel55_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL55_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL55);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL55_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL55_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL55);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL55_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL55_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL55);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL55_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL55_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL55);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL55_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL55_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL55);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL55_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL55_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL55);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL55_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL55_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL55) && (DMA_DMA1_PHYCHANNEL55 == 55U)) */

#if (defined(DMA_DMA1_PHYCHANNEL56) && (DMA_DMA1_PHYCHANNEL56 == 56U))
#if (defined(DMA_CFG_DMA1_CHANNEL56_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 56. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel56_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL56_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL56);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL56_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL56_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL56);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL56_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL56_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL56);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL56_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL56_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL56);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL56_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL56_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL56);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL56_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL56_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL56);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL56_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL56_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL56) && (DMA_DMA1_PHYCHANNEL56 == 56U)) */

#if (defined(DMA_DMA1_PHYCHANNEL57) && (DMA_DMA1_PHYCHANNEL57 == 57U))
#if (defined(DMA_CFG_DMA1_CHANNEL57_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 57. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel57_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL57_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL57);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL57_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL57_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL57);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL57_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL57_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL57);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL57_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL57_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL57);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL57_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL57_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL57);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL57_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL57_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL57);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL57_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL57_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL57) && (DMA_DMA1_PHYCHANNEL57 == 57U)) */

#if (defined(DMA_DMA1_PHYCHANNEL58) && (DMA_DMA1_PHYCHANNEL58 == 58U))
#if (defined(DMA_CFG_DMA1_CHANNEL58_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 58. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel58_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL58_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL58);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL58_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL58_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL58);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL58_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL58_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL58);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL58_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL58_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL58);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL58_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL58_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL58);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL58_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL58_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL58);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL58_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL58_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL58) && (DMA_DMA1_PHYCHANNEL58 == 58U)) */

#if (defined(DMA_DMA1_PHYCHANNEL59) && (DMA_DMA1_PHYCHANNEL59 == 59U))
#if (defined(DMA_CFG_DMA1_CHANNEL59_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 59. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel59_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL59_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL59);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL59_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL59_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL59);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL59_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL59_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL59);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL59_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL59_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL59);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL59_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL59_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL59);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL59_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL59_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL59);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL59_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL59_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL59) && (DMA_DMA1_PHYCHANNEL59 == 59U)) */

#if (defined(DMA_DMA1_PHYCHANNEL60) && (DMA_DMA1_PHYCHANNEL60 == 60U))
#if (defined(DMA_CFG_DMA1_CHANNEL60_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 60. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel60_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL60_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL60);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL60_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL60_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL60);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL60_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL60_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL60);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL60_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL60_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL60);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL60_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL60_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL60);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL60_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL60_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL60);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL60_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL60_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL60) && (DMA_DMA1_PHYCHANNEL60 == 60U)) */

#if (defined(DMA_DMA1_PHYCHANNEL61) && (DMA_DMA1_PHYCHANNEL61 == 61U))
#if (defined(DMA_CFG_DMA1_CHANNEL61_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 61. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel61_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL61_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL61);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL61_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL61_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL61);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL61_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL61_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL61);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL61_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL61_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL61);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL61_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL61_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL61);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL61_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL61_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL61);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL61_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL61_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL61) && (DMA_DMA1_PHYCHANNEL61 == 61U)) */

#if (defined(DMA_DMA1_PHYCHANNEL62) && (DMA_DMA1_PHYCHANNEL62 == 62U))
#if (defined(DMA_CFG_DMA1_CHANNEL62_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 62. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel62_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL62_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL62);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL62_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL62_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL62);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL62_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL62_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL62);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL62_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL62_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL62);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL62_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL62_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL62);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL62_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL62_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL62);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL62_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL62_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL62) && (DMA_DMA1_PHYCHANNEL62 == 62U)) */

#if (defined(DMA_DMA1_PHYCHANNEL63) && (DMA_DMA1_PHYCHANNEL63 == 63U))
#if (defined(DMA_CFG_DMA1_CHANNEL63_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 63. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel63_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL63_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL63);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL63_TC_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL63_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL63);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL63_RTC_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL63_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL63);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL63_ERROR_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL63_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL63);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL63_SRC_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL63_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL63);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL63_DEST_CB_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA1_CHANNEL63_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA1, DMA_DMA1_PHYCHANNEL63);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL63_PATTERN_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL63_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL63) && (DMA_DMA1_PHYCHANNEL63 == 63U)) */

#endif /* \(defined(DMA_HWUNIT_DMA1) && (DMA_HWUNIT_DMA1 == 1U)) */

#if (defined(DMA_HWUNIT_DMA2) && (DMA_HWUNIT_DMA2 == 2U))
/* DMA2 used */

#if (defined(DMA_DMA2_PHYCHANNEL0) && (DMA_DMA2_PHYCHANNEL0 == 0U))
#if (defined(DMA_CFG_DMA2_CHANNEL0_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 0. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel0_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL0_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL0_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL0_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL0_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL0_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL0_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL0_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL0_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL0_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL0_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL0_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL0_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL0_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL0) && (DMA_DMA2_PHYCHANNEL0 == 0U)) */

#if (defined(DMA_DMA2_PHYCHANNEL1) && (DMA_DMA2_PHYCHANNEL1 == 1U))
#if (defined(DMA_CFG_DMA2_CHANNEL1_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 1. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel1_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL1_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL1_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL1_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL1_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL1_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL1_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL1_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL1_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL1_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL1_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL1_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL1_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL1_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL1) && (DMA_DMA2_PHYCHANNEL1 == 1U)) */

#if (defined(DMA_DMA2_PHYCHANNEL2) && (DMA_DMA2_PHYCHANNEL2 == 2U))
#if (defined(DMA_CFG_DMA2_CHANNEL2_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 2. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel2_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL2_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL2_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL2_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL2_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL2_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL2_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL2_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL2_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL2_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL2_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL2_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL2_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL2_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL2) && (DMA_DMA2_PHYCHANNEL2 == 2U)) */

#if (defined(DMA_DMA2_PHYCHANNEL3) && (DMA_DMA2_PHYCHANNEL3 == 3U))
#if (defined(DMA_CFG_DMA2_CHANNEL3_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 3. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel3_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL3_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL3_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL3_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL3_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL3_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL3_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL3_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL3_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL3_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL3_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL3_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL3_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL3_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL3) && (DMA_DMA2_PHYCHANNEL3 == 3U)) */

#if (defined(DMA_DMA2_PHYCHANNEL4) && (DMA_DMA2_PHYCHANNEL4 == 4U))
#if (defined(DMA_CFG_DMA2_CHANNEL4_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 4. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel4_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL4_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL4_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL4_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL4_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL4_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL4_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL4_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL4_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL4_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL4_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL4_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL4_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL4_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL4) && (DMA_DMA2_PHYCHANNEL4 == 4U)) */

#if (defined(DMA_DMA2_PHYCHANNEL5) && (DMA_DMA2_PHYCHANNEL5 == 5U))
#if (defined(DMA_CFG_DMA2_CHANNEL5_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 5. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel5_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL5_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL5_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL5_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL5_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL5_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL5_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL5_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL5_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL5_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL5_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL5_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL5_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL5_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL5) && (DMA_DMA2_PHYCHANNEL5 == 5U)) */

#if (defined(DMA_DMA2_PHYCHANNEL6) && (DMA_DMA2_PHYCHANNEL6 == 6U))
#if (defined(DMA_CFG_DMA2_CHANNEL6_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 6. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel6_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL6_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL6_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL6_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL6_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL6_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL6_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL6_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL6_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL6_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL6_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL6_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL6_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL6_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL6) && (DMA_DMA2_PHYCHANNEL6 == 6U)) */

#if (defined(DMA_DMA2_PHYCHANNEL7) && (DMA_DMA2_PHYCHANNEL7 == 7U))
#if (defined(DMA_CFG_DMA2_CHANNEL7_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 7. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel7_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL7_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL7_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL7_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL7_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL7_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL7_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL7_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL7_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL7_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL7_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL7_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL7_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL7_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL7) && (DMA_DMA2_PHYCHANNEL7 == 7U)) */

#if (defined(DMA_DMA2_PHYCHANNEL8) && (DMA_DMA2_PHYCHANNEL8 == 8U))
#if (defined(DMA_CFG_DMA2_CHANNEL8_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 8. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel8_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL8_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL8_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL8_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL8_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL8_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL8_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL8_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL8_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL8_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL8_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL8_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL8_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL8_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL8) && (DMA_DMA2_PHYCHANNEL8 == 8U)) */

#if (defined(DMA_DMA2_PHYCHANNEL9) && (DMA_DMA2_PHYCHANNEL9 == 9U))
#if (defined(DMA_CFG_DMA2_CHANNEL9_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 9. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel9_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL9_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL9_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL9_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL9_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL9_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL9_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL9_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL9_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL9_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL9_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL9_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL9_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL9_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL9) && (DMA_DMA2_PHYCHANNEL9 == 9U)) */

#if (defined(DMA_DMA2_PHYCHANNEL10) && (DMA_DMA2_PHYCHANNEL10 == 10U))
#if (defined(DMA_CFG_DMA2_CHANNEL10_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 10. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel10_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL10_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL10_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL10_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL10_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL10_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL10_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL10_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL10_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL10_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL10_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL10_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL10_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL10_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL10) && (DMA_DMA2_PHYCHANNEL10 == 10U)) */

#if (defined(DMA_DMA2_PHYCHANNEL11) && (DMA_DMA2_PHYCHANNEL11 == 11U))
#if (defined(DMA_CFG_DMA2_CHANNEL11_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 11. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel11_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL11_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL11_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL11_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL11_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL11_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL11_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL11_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL11_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL11_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL11_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL11_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL11_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL11_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL11) && (DMA_DMA2_PHYCHANNEL11 == 11U)) */

#if (defined(DMA_DMA2_PHYCHANNEL12) && (DMA_DMA2_PHYCHANNEL12 == 12U))
#if (defined(DMA_CFG_DMA2_CHANNEL12_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 12. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel12_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL12_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL12_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL12_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL12_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL12_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL12_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL12_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL12_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL12_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL12_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL12_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL12_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL12_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL12) && (DMA_DMA2_PHYCHANNEL12 == 12U)) */

#if (defined(DMA_DMA2_PHYCHANNEL13) && (DMA_DMA2_PHYCHANNEL13 == 13U))
#if (defined(DMA_CFG_DMA2_CHANNEL13_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 13. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel13_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL13_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL13_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL13_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL13_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL13_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL13_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL13_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL13_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL13_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL13_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL13_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL13_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL13_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL13) && (DMA_DMA2_PHYCHANNEL13 == 13U)) */

#if (defined(DMA_DMA2_PHYCHANNEL14) && (DMA_DMA2_PHYCHANNEL14 == 14U))
#if (defined(DMA_CFG_DMA2_CHANNEL14_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 14. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel14_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL14_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL14_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL14_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL14_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL14_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL14_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL14_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL14_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL14_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL14_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL14_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL14_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL14_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL14) && (DMA_DMA2_PHYCHANNEL14 == 14U)) */

#if (defined(DMA_DMA2_PHYCHANNEL15) && (DMA_DMA2_PHYCHANNEL15 == 15U))
#if (defined(DMA_CFG_DMA2_CHANNEL15_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 15. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel15_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL15_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL15_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL15_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL15_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL15_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL15_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL15_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL15_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL15_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL15_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL15_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL15_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL15_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL15) && (DMA_DMA2_PHYCHANNEL15 == 15U)) */

#if (defined(DMA_DMA2_PHYCHANNEL16) && (DMA_DMA2_PHYCHANNEL16 == 16U))
#if (defined(DMA_CFG_DMA2_CHANNEL16_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 16. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel16_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL16_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL16_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL16_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL16_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL16_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL16_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL16_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL16_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL16_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL16_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL16_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL16_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL16_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL16) && (DMA_DMA2_PHYCHANNEL16 == 16U)) */

#if (defined(DMA_DMA2_PHYCHANNEL17) && (DMA_DMA2_PHYCHANNEL17 == 17U))
#if (defined(DMA_CFG_DMA2_CHANNEL17_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 17. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel17_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL17_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL17_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL17_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL17_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL17_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL17_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL17_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL17_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL17_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL17_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL17_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL17_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL17_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL17) && (DMA_DMA2_PHYCHANNEL17 == 17U)) */

#if (defined(DMA_DMA2_PHYCHANNEL18) && (DMA_DMA2_PHYCHANNEL18 == 18U))
#if (defined(DMA_CFG_DMA2_CHANNEL18_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 18. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel18_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL18_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL18_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL18_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL18_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL18_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL18_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL18_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL18_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL18_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL18_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL18_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL18_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL18_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL18) && (DMA_DMA2_PHYCHANNEL18 == 18U)) */

#if (defined(DMA_DMA2_PHYCHANNEL19) && (DMA_DMA2_PHYCHANNEL19 == 19U))
#if (defined(DMA_CFG_DMA2_CHANNEL19_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 19. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel19_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL19_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL19_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL19_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL19_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL19_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL19_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL19_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL19_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL19_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL19_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL19_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL19_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL19_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL19) && (DMA_DMA2_PHYCHANNEL19 == 19U)) */

#if (defined(DMA_DMA2_PHYCHANNEL20) && (DMA_DMA2_PHYCHANNEL20 == 20U))
#if (defined(DMA_CFG_DMA2_CHANNEL20_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 20. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel20_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL20_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL20_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL20_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL20_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL20_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL20_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL20_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL20_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL20_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL20_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL20_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL20_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL20_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL20) && (DMA_DMA2_PHYCHANNEL20 == 20U)) */

#if (defined(DMA_DMA2_PHYCHANNEL21) && (DMA_DMA2_PHYCHANNEL21 == 21U))
#if (defined(DMA_CFG_DMA2_CHANNEL21_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 21. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel21_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL21_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL21_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL21_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL21_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL21_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL21_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL21_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL21_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL21_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL21_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL21_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL21_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL21_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL21) && (DMA_DMA2_PHYCHANNEL21 == 21U)) */

#if (defined(DMA_DMA2_PHYCHANNEL22) && (DMA_DMA2_PHYCHANNEL22 == 22U))
#if (defined(DMA_CFG_DMA2_CHANNEL22_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 22. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel22_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL22_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL22_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL22_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL22_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL22_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL22_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL22_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL22_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL22_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL22_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL22_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL22_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL22_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL22) && (DMA_DMA2_PHYCHANNEL22 == 22U)) */

#if (defined(DMA_DMA2_PHYCHANNEL23) && (DMA_DMA2_PHYCHANNEL23 == 23U))
#if (defined(DMA_CFG_DMA2_CHANNEL23_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA2 physical channel 23. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel23_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL23_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL23_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL23_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL23_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL23_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL23_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL23_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL23_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL23_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL23_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL23_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL23_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL23_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL23) && (DMA_DMA2_PHYCHANNEL23 == 23U)) */


#if (defined(DMA_DMA2_PHYCHANNEL24) && (DMA_DMA2_PHYCHANNEL24 == 24U))
#if (defined(DMA_CFG_DMA2_CHANNEL24_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 24. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel24_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL24_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL24_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL24_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL24_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL24_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL24_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL24_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL24_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL24_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL24_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL24_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL24);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL24_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL24_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL24) && (DMA_DMA2_PHYCHANNEL24 == 24U)) */

#if (defined(DMA_DMA2_PHYCHANNEL25) && (DMA_DMA2_PHYCHANNEL25 == 25U))
#if (defined(DMA_CFG_DMA2_CHANNEL25_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 25. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel25_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL25_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL25_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL25_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL25_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL25_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL25_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL25_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL25_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL25_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL25_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL25_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL25);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL25_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL25_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL25) && (DMA_DMA2_PHYCHANNEL25 == 25U)) */

#if (defined(DMA_DMA2_PHYCHANNEL26) && (DMA_DMA2_PHYCHANNEL26 == 26U))
#if (defined(DMA_CFG_DMA2_CHANNEL26_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 26. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel26_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL26_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL26_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL26_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL26_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL26_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL26_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL26_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL26_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL26_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL26_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL26_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL26);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL26_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL26_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL26) && (DMA_DMA2_PHYCHANNEL26 == 26U)) */

#if (defined(DMA_DMA2_PHYCHANNEL27) && (DMA_DMA2_PHYCHANNEL27 == 27U))
#if (defined(DMA_CFG_DMA2_CHANNEL27_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 27. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel27_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL27_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL27_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL27_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL27_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL27_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL27_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL27_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL27_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL27_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL27_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL27_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL27);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL27_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL27_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL27) && (DMA_DMA2_PHYCHANNEL27 == 27U)) */

#if (defined(DMA_DMA2_PHYCHANNEL28) && (DMA_DMA2_PHYCHANNEL28 == 28U))
#if (defined(DMA_CFG_DMA2_CHANNEL28_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 28. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel28_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL28_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL28_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL28_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL28_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL28_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL28_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL28_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL28_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL28_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL28_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL28_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL28);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL28_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL28_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL28) && (DMA_DMA2_PHYCHANNEL28 == 28U)) */

#if (defined(DMA_DMA2_PHYCHANNEL29) && (DMA_DMA2_PHYCHANNEL29 == 29U))
#if (defined(DMA_CFG_DMA2_CHANNEL29_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 29. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel29_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL29_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL29_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL29_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL29_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL29_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL29_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL29_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL29_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL29_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL29_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL29_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL29);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL29_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL29_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL29) && (DMA_DMA2_PHYCHANNEL29 == 29U)) */

#if (defined(DMA_DMA2_PHYCHANNEL30) && (DMA_DMA2_PHYCHANNEL30 == 30U))
#if (defined(DMA_CFG_DMA2_CHANNEL30_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 30. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel30_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL30_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL30_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL30_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL30_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL30_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL30_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL30_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL30_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL30_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL30_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL30_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL30);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL30_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL30_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL30) && (DMA_DMA2_PHYCHANNEL30 == 30U)) */

#if (defined(DMA_DMA2_PHYCHANNEL31) && (DMA_DMA2_PHYCHANNEL31 == 31U))
#if (defined(DMA_CFG_DMA2_CHANNEL31_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 31. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel31_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL31_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL31_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL31_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL31_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL31_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL31_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL31_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL31_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL31_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL31_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL31_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL31);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL31_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL31_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL31) && (DMA_DMA2_PHYCHANNEL31 == 31U)) */

#if (defined(DMA_DMA2_PHYCHANNEL32) && (DMA_DMA2_PHYCHANNEL32 == 32U))
#if (defined(DMA_CFG_DMA2_CHANNEL32_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 32. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel32_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL32_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL32_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL32_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL32_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL32_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL32_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL32_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL32_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL32_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL32_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL32_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL32);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL32_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL32_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL32) && (DMA_DMA2_PHYCHANNEL32 == 32U)) */

#if (defined(DMA_DMA2_PHYCHANNEL33) && (DMA_DMA2_PHYCHANNEL33 == 33U))
#if (defined(DMA_CFG_DMA2_CHANNEL33_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 33. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel33_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL33_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL33_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL33_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL33_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL33_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL33_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL33_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL33_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL33_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL33_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL33_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL33);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL33_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL33_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL33) && (DMA_DMA2_PHYCHANNEL33 == 33U)) */

#if (defined(DMA_DMA2_PHYCHANNEL34) && (DMA_DMA2_PHYCHANNEL34 == 34U))
#if (defined(DMA_CFG_DMA2_CHANNEL34_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 34. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel34_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL34_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL34_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL34_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL34_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL34_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL34_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL34_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL34_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL34_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL34_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL34_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL34);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL34_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL34_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL34) && (DMA_DMA2_PHYCHANNEL34 == 34U)) */

#if (defined(DMA_DMA2_PHYCHANNEL35) && (DMA_DMA2_PHYCHANNEL35 == 35U))
#if (defined(DMA_CFG_DMA2_CHANNEL35_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 35. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel35_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL35_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL35_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL35_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL35_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL35_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL35_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL35_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL35_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL35_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL35_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL35_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL35);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL35_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL35_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL35) && (DMA_DMA2_PHYCHANNEL35 == 35U)) */

#if (defined(DMA_DMA2_PHYCHANNEL36) && (DMA_DMA2_PHYCHANNEL36 == 36U))
#if (defined(DMA_CFG_DMA2_CHANNEL36_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 36. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel36_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL36_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL36_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL36_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL36_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL36_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL36_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL36_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL36_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL36_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL36_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL36_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL36);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL36_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL36_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL36) && (DMA_DMA2_PHYCHANNEL36 == 36U)) */

#if (defined(DMA_DMA2_PHYCHANNEL37) && (DMA_DMA2_PHYCHANNEL37 == 37U))
#if (defined(DMA_CFG_DMA2_CHANNEL37_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 37. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel37_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL37_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL37_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL37_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL37_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL37_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL37_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL37_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL37_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL37_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL37_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL37_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL37);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL37_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL37_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL37) && (DMA_DMA2_PHYCHANNEL37 == 37U)) */

#if (defined(DMA_DMA2_PHYCHANNEL38) && (DMA_DMA2_PHYCHANNEL38 == 38U))
#if (defined(DMA_CFG_DMA2_CHANNEL38_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 38. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel38_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL38_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL38_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL38_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL38_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL38_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL38_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL38_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL38_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL38_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL38_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL38_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL38);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL38_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL38_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL38) && (DMA_DMA2_PHYCHANNEL38 == 38U)) */

#if (defined(DMA_DMA2_PHYCHANNEL39) && (DMA_DMA2_PHYCHANNEL39 == 39U))
#if (defined(DMA_CFG_DMA2_CHANNEL39_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 39. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel39_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL39_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL39_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL39_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL39_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL39_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL39_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL39_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL39_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL39_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL39_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL39_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL39);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL39_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL39_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL39) && (DMA_DMA2_PHYCHANNEL39 == 39U)) */

#if (defined(DMA_DMA2_PHYCHANNEL40) && (DMA_DMA2_PHYCHANNEL40 == 40U))
#if (defined(DMA_CFG_DMA2_CHANNEL40_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 40. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel40_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL40_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL40_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL40_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL40_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL40_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL40_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL40_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL40_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL40_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL40_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL40_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL40);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL40_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL40_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL40) && (DMA_DMA2_PHYCHANNEL40 == 40U)) */

#if (defined(DMA_DMA2_PHYCHANNEL41) && (DMA_DMA2_PHYCHANNEL41 == 41U))
#if (defined(DMA_CFG_DMA2_CHANNEL41_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 41. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel41_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL41_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL41_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL41_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL41_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL41_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL41_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL41_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL41_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL41_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL41_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL41_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL41);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL41_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL41_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL41) && (DMA_DMA2_PHYCHANNEL41 == 41U)) */

#if (defined(DMA_DMA2_PHYCHANNEL42) && (DMA_DMA2_PHYCHANNEL42 == 42U))
#if (defined(DMA_CFG_DMA2_CHANNEL42_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 42. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel42_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL42_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL42_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL42_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL42_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL42_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL42_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL42_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL42_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL42_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL42_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL42_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL42);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL42_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL42_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL42) && (DMA_DMA2_PHYCHANNEL42 == 42U)) */

#if (defined(DMA_DMA2_PHYCHANNEL43) && (DMA_DMA2_PHYCHANNEL43 == 43U))
#if (defined(DMA_CFG_DMA2_CHANNEL43_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA1 physical channel 43. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel43_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL43_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL43_TC_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL43_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL43_RTC_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL43_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL43_ERROR_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL43_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL43_SRC_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL43_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL43_DEST_CB_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA2_CHANNEL43_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA2, DMA_DMA2_PHYCHANNEL43);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL43_PATTERN_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL43_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL43) && (DMA_DMA2_PHYCHANNEL43 == 43U)) */

#endif /* \(defined(DMA_HWUNIT_DMA2) && (DMA_HWUNIT_DMA2 == 2U)) */

#if (defined(DMA_HWUNIT_DMA3) && (DMA_HWUNIT_DMA3 == 3U))
/* DMA3 used */

#if (defined(DMA_DMA3_PHYCHANNEL0) && (DMA_DMA3_PHYCHANNEL0 == 0U))
#if (defined(DMA_CFG_DMA3_CHANNEL0_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 0. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel0_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL0_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL0_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL0_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL0_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL0_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL0_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL0_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL0_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL0_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL0_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL0_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL0);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL0_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL0_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL0) && (DMA_DMA3_PHYCHANNEL0 == 0U)) */

#if (defined(DMA_DMA3_PHYCHANNEL1) && (DMA_DMA3_PHYCHANNEL1 == 1U))
#if (defined(DMA_CFG_DMA3_CHANNEL1_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 1. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel1_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL1_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL1_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL1_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL1_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL1_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL1_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL1_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL1_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL1_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL1_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL1_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL1);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL1_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL1_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL1) && (DMA_DMA3_PHYCHANNEL1 == 1U)) */

#if (defined(DMA_DMA3_PHYCHANNEL2) && (DMA_DMA3_PHYCHANNEL2 == 2U))
#if (defined(DMA_CFG_DMA3_CHANNEL2_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 2. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel2_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL2_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL2_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL2_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL2_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL2_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL2_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL2_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL2_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL2_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL2_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL2_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL2);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL2_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL2_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL2) && (DMA_DMA3_PHYCHANNEL2 == 2U)) */

#if (defined(DMA_DMA3_PHYCHANNEL3) && (DMA_DMA3_PHYCHANNEL3 == 3U))
#if (defined(DMA_CFG_DMA3_CHANNEL3_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 3. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel3_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL3_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL3_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL3_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL3_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL3_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL3_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL3_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL3_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL3_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL3_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL3_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL3);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL3_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL3_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL3) && (DMA_DMA3_PHYCHANNEL3 == 3U)) */

#if (defined(DMA_DMA3_PHYCHANNEL4) && (DMA_DMA3_PHYCHANNEL4 == 4U))
#if (defined(DMA_CFG_DMA3_CHANNEL4_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 4. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel4_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL4_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL4_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL4_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL4_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL4_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL4_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL4_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL4_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL4_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL4_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL4_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL4);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL4_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL4_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL4) && (DMA_DMA3_PHYCHANNEL4 == 4U)) */

#if (defined(DMA_DMA3_PHYCHANNEL5) && (DMA_DMA3_PHYCHANNEL5 == 5U))
#if (defined(DMA_CFG_DMA3_CHANNEL5_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 5. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel5_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL5_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL5_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL5_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL5_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL5_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL5_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL5_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL5_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL5_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL5_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL5_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL5);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL5_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL5_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL5) && (DMA_DMA3_PHYCHANNEL5 == 5U)) */

#if (defined(DMA_DMA3_PHYCHANNEL6) && (DMA_DMA3_PHYCHANNEL6 == 6U))
#if (defined(DMA_CFG_DMA3_CHANNEL6_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 6. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel6_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL6_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL6_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL6_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL6_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL6_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL6_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL6_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL6_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL6_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL6_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL6_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL6);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL6_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL6_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL6) && (DMA_DMA3_PHYCHANNEL6 == 6U)) */

#if (defined(DMA_DMA3_PHYCHANNEL7) && (DMA_DMA3_PHYCHANNEL7 == 7U))
#if (defined(DMA_CFG_DMA3_CHANNEL7_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 7. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel7_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL7_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL7_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL7_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL7_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL7_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL7_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL7_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL7_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL7_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL7_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL7_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL7);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL7_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL7_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL7) && (DMA_DMA3_PHYCHANNEL7 == 7U)) */

#if (defined(DMA_DMA3_PHYCHANNEL8) && (DMA_DMA3_PHYCHANNEL8 == 8U))
#if (defined(DMA_CFG_DMA3_CHANNEL8_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 8. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel8_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL8_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL8_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL8_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL8_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL8_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL8_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL8_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL8_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL8_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL8_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL8_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL8);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL8_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL8_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL8) && (DMA_DMA3_PHYCHANNEL8 == 8U)) */

#if (defined(DMA_DMA3_PHYCHANNEL9) && (DMA_DMA3_PHYCHANNEL9 == 9U))
#if (defined(DMA_CFG_DMA3_CHANNEL9_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 9. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel9_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL9_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL9_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL9_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL9_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL9_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL9_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL9_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL9_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL9_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL9_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL9_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL9);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL9_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL9_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL9) && (DMA_DMA3_PHYCHANNEL9 == 9U)) */

#if (defined(DMA_DMA3_PHYCHANNEL10) && (DMA_DMA3_PHYCHANNEL10 == 10U))
#if (defined(DMA_CFG_DMA3_CHANNEL10_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 10. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel10_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL10_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL10_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL10_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL10_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL10_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL10_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL10_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL10_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL10_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL10_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL10_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL10);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL10_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL10_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL10) && (DMA_DMA3_PHYCHANNEL10 == 10U)) */

#if (defined(DMA_DMA3_PHYCHANNEL11) && (DMA_DMA3_PHYCHANNEL11 == 11U))
#if (defined(DMA_CFG_DMA3_CHANNEL11_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 11. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel11_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL11_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL11_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL11_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL11_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL11_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL11_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL11_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL11_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL11_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL11_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL11_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL11);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL11_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL11_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL11) && (DMA_DMA3_PHYCHANNEL11 == 11U)) */

#if (defined(DMA_DMA3_PHYCHANNEL12) && (DMA_DMA3_PHYCHANNEL12 == 12U))
#if (defined(DMA_CFG_DMA3_CHANNEL12_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 12. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel12_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL12_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL12_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL12_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL12_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL12_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL12_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL12_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL12_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL12_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL12_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL12_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL12);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL12_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL12_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL12) && (DMA_DMA3_PHYCHANNEL12 == 12U)) */

#if (defined(DMA_DMA3_PHYCHANNEL13) && (DMA_DMA3_PHYCHANNEL13 == 13U))
#if (defined(DMA_CFG_DMA3_CHANNEL13_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 13. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel13_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL13_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL13_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL13_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL13_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL13_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL13_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL13_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL13_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL13_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL13_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL13_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL13);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL13_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL13_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL13) && (DMA_DMA3_PHYCHANNEL13 == 13U)) */

#if (defined(DMA_DMA3_PHYCHANNEL14) && (DMA_DMA3_PHYCHANNEL14 == 14U))
#if (defined(DMA_CFG_DMA3_CHANNEL14_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 14. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel14_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL14_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL14_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL14_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL14_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL14_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL14_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL14_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL14_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL14_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL14_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL14_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL14);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL14_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL14_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL14) && (DMA_DMA3_PHYCHANNEL14 == 14U)) */

#if (defined(DMA_DMA3_PHYCHANNEL15) && (DMA_DMA3_PHYCHANNEL15 == 15U))
#if (defined(DMA_CFG_DMA3_CHANNEL15_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 15. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel15_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL15_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL15_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL15_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL15_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL15_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL15_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL15_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL15_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL15_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL15_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL15_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL15);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL15_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL15_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL15) && (DMA_DMA3_PHYCHANNEL15 == 15U)) */

#if (defined(DMA_DMA3_PHYCHANNEL16) && (DMA_DMA3_PHYCHANNEL16 == 16U))
#if (defined(DMA_CFG_DMA3_CHANNEL16_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 16. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel16_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL16_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL16_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL16_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL16_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL16_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL16_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL16_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL16_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL16_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL16_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL16_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL16);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL16_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL16_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL16) && (DMA_DMA3_PHYCHANNEL16 == 16U)) */

#if (defined(DMA_DMA3_PHYCHANNEL17) && (DMA_DMA3_PHYCHANNEL17 == 17U))
#if (defined(DMA_CFG_DMA3_CHANNEL17_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 17. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel17_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL17_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL17_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL17_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL17_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL17_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL17_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL17_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL17_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL17_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL17_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL17_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL17);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL17_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL17_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL17) && (DMA_DMA3_PHYCHANNEL17 == 17U)) */

#if (defined(DMA_DMA3_PHYCHANNEL18) && (DMA_DMA3_PHYCHANNEL18 == 18U))
#if (defined(DMA_CFG_DMA3_CHANNEL18_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 18. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel18_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL18_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL18_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL18_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL18_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL18_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL18_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL18_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL18_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL18_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL18_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL18_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL18);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL18_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL18_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL18) && (DMA_DMA3_PHYCHANNEL18 == 18U)) */

#if (defined(DMA_DMA3_PHYCHANNEL19) && (DMA_DMA3_PHYCHANNEL19 == 19U))
#if (defined(DMA_CFG_DMA3_CHANNEL19_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 19. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel19_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL19_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL19_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL19_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL19_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL19_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL19_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL19_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL19_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL19_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL19_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL19_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL19);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL19_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL19_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL19) && (DMA_DMA3_PHYCHANNEL19 == 19U)) */

#if (defined(DMA_DMA3_PHYCHANNEL20) && (DMA_DMA3_PHYCHANNEL20 == 20U))
#if (defined(DMA_CFG_DMA3_CHANNEL20_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 20. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel20_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL20_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL20_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL20_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL20_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL20_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL20_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL20_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL20_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL20_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL20_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL20_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL20);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL20_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL20_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL20) && (DMA_DMA3_PHYCHANNEL20 == 20U)) */

#if (defined(DMA_DMA3_PHYCHANNEL21) && (DMA_DMA3_PHYCHANNEL21 == 21U))
#if (defined(DMA_CFG_DMA3_CHANNEL21_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 21. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel21_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL21_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL21_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL21_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL21_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL21_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL21_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL21_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL21_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL21_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL21_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL21_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL21);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL21_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL21_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL21) && (DMA_DMA3_PHYCHANNEL21 == 21U)) */

#if (defined(DMA_DMA3_PHYCHANNEL22) && (DMA_DMA3_PHYCHANNEL22 == 22U))
#if (defined(DMA_CFG_DMA3_CHANNEL22_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 22. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel22_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL22_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL22_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL22_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL22_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL22_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL22_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL22_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL22_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL22_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL22_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL22_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL22);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL22_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL22_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL22) && (DMA_DMA3_PHYCHANNEL22 == 22U)) */

#if (defined(DMA_DMA3_PHYCHANNEL23) && (DMA_DMA3_PHYCHANNEL23 == 23U))
#if (defined(DMA_CFG_DMA3_CHANNEL23_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_INT_EN == STD_ON))
/* The entry of the interrupt service function for DMA3 physical channel 23. */
FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel23_ISR
(
    void
)
{
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL23_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_TC_INT_EN == STD_ON))
    /* Terminal count interrupt handler */
    Dma_TerminalCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL23_TC_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_TC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_TC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL23_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_RTC_INT_EN == STD_ON))
    /* Remaining transfer count interrupt handler */
    Dma_RemainingCount_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL23_RTC_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_RTC_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL23_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_ERROR_INT_EN == STD_ON))
    /* Error interrupt handler */
    Dma_Error_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL23_ERROR_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_ERROR_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL23_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_SRC_CB_INT_EN == STD_ON))
    /* Source circular buffer rollback interrupt handler */
    Dma_SrcCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL23_SRC_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_SRC_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL23_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_DEST_CB_INT_EN == STD_ON))
    /* Destination circular buffer rollback interrupt handler */
    Dma_DestCircBufRb_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL23_DEST_CB_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_DEST_CB_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN  == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
#if (defined(DMA_CFG_DMA3_CHANNEL23_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_PATTERN_INT_EN == STD_ON))
    /* Data pattern matched interrupt handler */
    Dma_PatternMatch_ISRHandler(DMA_HWUNIT_DMA3, DMA_DMA3_PHYCHANNEL23);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL23_PATTERN_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_PATTERN_INT_EN == STD_ON)) */
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN  == STD_ON) */
}
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL23_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL23) && (DMA_DMA3_PHYCHANNEL23 == 23U)) */

#endif /* \(defined(DMA_HWUNIT_DMA3) && (DMA_HWUNIT_DMA3 == 3U)) */


#endif /* \(DMA_CFG_INTERRUPT_EN  == STD_ON) */

#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Dma_Irq_c_REF_1 */
#include "Dma_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

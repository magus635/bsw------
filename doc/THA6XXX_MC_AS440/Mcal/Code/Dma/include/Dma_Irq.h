/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dma_Irq.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DMA
*
*   brief                 : This file contains all ISR function declarations of Dma Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

#ifndef DMA_IRQ_H_
#define DMA_IRQ_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dma.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dma_MemMap.h"

#if (DMA_CFG_INTERRUPT_EN == STD_ON)

#if (defined(DMA_HWUNIT_DMA0) && (DMA_HWUNIT_DMA0 == 0U))

#if (defined(DMA_DMA0_PHYCHANNEL0) && (DMA_DMA0_PHYCHANNEL0 == 0U))
#if (defined(DMA_CFG_DMA0_CHANNEL0_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel0_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL0_INT_EN) && (DMA_CFG_DMA0_CHANNEL0_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL0) && (DMA_DMA0_PHYCHANNEL0 == 0U)) */

#if (defined(DMA_DMA0_PHYCHANNEL1) && (DMA_DMA0_PHYCHANNEL1 == 1U))
#if (defined(DMA_CFG_DMA0_CHANNEL1_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel1_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL1_INT_EN) && (DMA_CFG_DMA0_CHANNEL1_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL1) && (DMA_DMA0_PHYCHANNEL1 == 1U)) */

#if (defined(DMA_DMA0_PHYCHANNEL2) && (DMA_DMA0_PHYCHANNEL2 == 2U))
#if (defined(DMA_CFG_DMA0_CHANNEL2_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel2_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL2_INT_EN) && (DMA_CFG_DMA0_CHANNEL2_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL2) && (DMA_DMA0_PHYCHANNEL2 == 2U)) */

#if (defined(DMA_DMA0_PHYCHANNEL3) && (DMA_DMA0_PHYCHANNEL3 == 3U))
#if (defined(DMA_CFG_DMA0_CHANNEL3_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel3_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL3_INT_EN) && (DMA_CFG_DMA0_CHANNEL3_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL3) && (DMA_DMA0_PHYCHANNEL3 == 3U)) */

#if (defined(DMA_DMA0_PHYCHANNEL4) && (DMA_DMA0_PHYCHANNEL4 == 4U))
#if (defined(DMA_CFG_DMA0_CHANNEL4_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel4_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL4_INT_EN) && (DMA_CFG_DMA0_CHANNEL4_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL4) && (DMA_DMA0_PHYCHANNEL4 == 4U)) */

#if (defined(DMA_DMA0_PHYCHANNEL5) && (DMA_DMA0_PHYCHANNEL5 == 5U))
#if (defined(DMA_CFG_DMA0_CHANNEL5_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel5_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL5_INT_EN) && (DMA_CFG_DMA0_CHANNEL5_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL5) && (DMA_DMA0_PHYCHANNEL5 == 5U)) */

#if (defined(DMA_DMA0_PHYCHANNEL6) && (DMA_DMA0_PHYCHANNEL6 == 6U))
#if (defined(DMA_CFG_DMA0_CHANNEL6_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel6_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL6_INT_EN) && (DMA_CFG_DMA0_CHANNEL6_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL6) && (DMA_DMA0_PHYCHANNEL6 == 6U)) */

#if (defined(DMA_DMA0_PHYCHANNEL7) && (DMA_DMA0_PHYCHANNEL7 == 7U))
#if (defined(DMA_CFG_DMA0_CHANNEL7_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel7_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL7_INT_EN) && (DMA_CFG_DMA0_CHANNEL7_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL7) && (DMA_DMA0_PHYCHANNEL7 == 7U)) */

#if (defined(DMA_DMA0_PHYCHANNEL8) && (DMA_DMA0_PHYCHANNEL8 == 8U))
#if (defined(DMA_CFG_DMA0_CHANNEL8_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel8_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL8_INT_EN) && (DMA_CFG_DMA0_CHANNEL8_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL8) && (DMA_DMA0_PHYCHANNEL8 == 8U)) */

#if (defined(DMA_DMA0_PHYCHANNEL9) && (DMA_DMA0_PHYCHANNEL9 == 9U))
#if (defined(DMA_CFG_DMA0_CHANNEL9_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel9_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL9_INT_EN) && (DMA_CFG_DMA0_CHANNEL9_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL9) && (DMA_DMA0_PHYCHANNEL9 == 9U)) */

#if (defined(DMA_DMA0_PHYCHANNEL10) && (DMA_DMA0_PHYCHANNEL10 == 10U))
#if (defined(DMA_CFG_DMA0_CHANNEL10_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel10_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL10_INT_EN) && (DMA_CFG_DMA0_CHANNEL10_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL10) && (DMA_DMA0_PHYCHANNEL10 == 10U)) */

#if (defined(DMA_DMA0_PHYCHANNEL11) && (DMA_DMA0_PHYCHANNEL11 == 11U))
#if (defined(DMA_CFG_DMA0_CHANNEL11_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel11_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL11_INT_EN) && (DMA_CFG_DMA0_CHANNEL11_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL11) && (DMA_DMA0_PHYCHANNEL11 == 11U)) */

#if (defined(DMA_DMA0_PHYCHANNEL12) && (DMA_DMA0_PHYCHANNEL12 == 12U))
#if (defined(DMA_CFG_DMA0_CHANNEL12_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel12_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL12_INT_EN) && (DMA_CFG_DMA0_CHANNEL12_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL12) && (DMA_DMA0_PHYCHANNEL12 == 12U)) */

#if (defined(DMA_DMA0_PHYCHANNEL13) && (DMA_DMA0_PHYCHANNEL13 == 13U))
#if (defined(DMA_CFG_DMA0_CHANNEL13_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel13_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL13_INT_EN) && (DMA_CFG_DMA0_CHANNEL13_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL13) && (DMA_DMA0_PHYCHANNEL13 == 13U)) */

#if (defined(DMA_DMA0_PHYCHANNEL14) && (DMA_DMA0_PHYCHANNEL14 == 14U))
#if (defined(DMA_CFG_DMA0_CHANNEL14_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel14_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL14_INT_EN) && (DMA_CFG_DMA0_CHANNEL14_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL14) && (DMA_DMA0_PHYCHANNEL14 == 14U)) */

#if (defined(DMA_DMA0_PHYCHANNEL15) && (DMA_DMA0_PHYCHANNEL15 == 15U))
#if (defined(DMA_CFG_DMA0_CHANNEL15_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma0Channel15_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA0_CHANNEL15_INT_EN) && (DMA_CFG_DMA0_CHANNEL15_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA0_PHYCHANNEL15) && (DMA_DMA0_PHYCHANNEL15 == 15U)) */

#endif /* \(defined(DMA_HWUNIT_DMA0) && (DMA_HWUNIT_DMA0 == 0U)) */

#if (defined(DMA_HWUNIT_DMA1) && (DMA_HWUNIT_DMA1 == 1U))

#if (defined(DMA_DMA1_PHYCHANNEL0) && (DMA_DMA1_PHYCHANNEL0 == 0U))
#if (defined(DMA_CFG_DMA1_CHANNEL0_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel0_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL0_INT_EN) && (DMA_CFG_DMA1_CHANNEL0_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL0) && (DMA_DMA1_PHYCHANNEL0 == 0U)) */

#if (defined(DMA_DMA1_PHYCHANNEL1) && (DMA_DMA1_PHYCHANNEL1 == 1U))
#if (defined(DMA_CFG_DMA1_CHANNEL1_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel1_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL1_INT_EN) && (DMA_CFG_DMA1_CHANNEL1_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL1) && (DMA_DMA1_PHYCHANNEL1 == 1U)) */

#if (defined(DMA_DMA1_PHYCHANNEL2) && (DMA_DMA1_PHYCHANNEL2 == 2U))
#if (defined(DMA_CFG_DMA1_CHANNEL2_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel2_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL2_INT_EN) && (DMA_CFG_DMA1_CHANNEL2_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL2) && (DMA_DMA1_PHYCHANNEL2 == 2U)) */

#if (defined(DMA_DMA1_PHYCHANNEL3) && (DMA_DMA1_PHYCHANNEL3 == 3U))
#if (defined(DMA_CFG_DMA1_CHANNEL3_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel3_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL3_INT_EN) && (DMA_CFG_DMA1_CHANNEL3_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL3) && (DMA_DMA1_PHYCHANNEL3 == 3U)) */

#if (defined(DMA_DMA1_PHYCHANNEL4) && (DMA_DMA1_PHYCHANNEL4 == 4U))
#if (defined(DMA_CFG_DMA1_CHANNEL4_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel4_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL4_INT_EN) && (DMA_CFG_DMA1_CHANNEL4_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL4) && (DMA_DMA1_PHYCHANNEL4 == 4U)) */

#if (defined(DMA_DMA1_PHYCHANNEL5) && (DMA_DMA1_PHYCHANNEL5 == 5U))
#if (defined(DMA_CFG_DMA1_CHANNEL5_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel5_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL5_INT_EN) && (DMA_CFG_DMA1_CHANNEL5_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL5) && (DMA_DMA1_PHYCHANNEL5 == 5U)) */

#if (defined(DMA_DMA1_PHYCHANNEL6) && (DMA_DMA1_PHYCHANNEL6 == 6U))
#if (defined(DMA_CFG_DMA1_CHANNEL6_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel6_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL6_INT_EN) && (DMA_CFG_DMA1_CHANNEL6_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL6) && (DMA_DMA1_PHYCHANNEL6 == 6U)) */

#if (defined(DMA_DMA1_PHYCHANNEL7) && (DMA_DMA1_PHYCHANNEL7 == 7U))
#if (defined(DMA_CFG_DMA1_CHANNEL7_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel7_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL7_INT_EN) && (DMA_CFG_DMA1_CHANNEL7_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL7) && (DMA_DMA1_PHYCHANNEL7 == 7U)) */

#if (defined(DMA_DMA1_PHYCHANNEL8) && (DMA_DMA1_PHYCHANNEL8 == 8U))
#if (defined(DMA_CFG_DMA1_CHANNEL8_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel8_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL8_INT_EN) && (DMA_CFG_DMA1_CHANNEL8_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL8) && (DMA_DMA1_PHYCHANNEL8 == 8U)) */

#if (defined(DMA_DMA1_PHYCHANNEL9) && (DMA_DMA1_PHYCHANNEL9 == 9U))
#if (defined(DMA_CFG_DMA1_CHANNEL9_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel9_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL9_INT_EN) && (DMA_CFG_DMA1_CHANNEL9_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL9) && (DMA_DMA1_PHYCHANNEL9 == 9U)) */

#if (defined(DMA_DMA1_PHYCHANNEL10) && (DMA_DMA1_PHYCHANNEL10 == 10U))
#if (defined(DMA_CFG_DMA1_CHANNEL10_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel10_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL10_INT_EN) && (DMA_CFG_DMA1_CHANNEL10_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL10) && (DMA_DMA1_PHYCHANNEL10 == 10U)) */

#if (defined(DMA_DMA1_PHYCHANNEL11) && (DMA_DMA1_PHYCHANNEL11 == 11U))
#if (defined(DMA_CFG_DMA1_CHANNEL11_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel11_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL11_INT_EN) && (DMA_CFG_DMA1_CHANNEL11_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL11) && (DMA_DMA1_PHYCHANNEL11 == 11U)) */

#if (defined(DMA_DMA1_PHYCHANNEL12) && (DMA_DMA1_PHYCHANNEL12 == 12U))
#if (defined(DMA_CFG_DMA1_CHANNEL12_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel12_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL12_INT_EN) && (DMA_CFG_DMA1_CHANNEL12_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL12) && (DMA_DMA1_PHYCHANNEL12 == 12U)) */

#if (defined(DMA_DMA1_PHYCHANNEL13) && (DMA_DMA1_PHYCHANNEL13 == 13U))
#if (defined(DMA_CFG_DMA1_CHANNEL13_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel13_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL13_INT_EN) && (DMA_CFG_DMA1_CHANNEL13_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL13) && (DMA_DMA1_PHYCHANNEL13 == 13U)) */

#if (defined(DMA_DMA1_PHYCHANNEL14) && (DMA_DMA1_PHYCHANNEL14 == 14U))
#if (defined(DMA_CFG_DMA1_CHANNEL14_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel14_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL14_INT_EN) && (DMA_CFG_DMA1_CHANNEL14_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL14) && (DMA_DMA1_PHYCHANNEL14 == 14U)) */

#if (defined(DMA_DMA1_PHYCHANNEL15) && (DMA_DMA1_PHYCHANNEL15 == 15U))
#if (defined(DMA_CFG_DMA1_CHANNEL15_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel15_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL15_INT_EN) && (DMA_CFG_DMA1_CHANNEL15_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL15) && (DMA_DMA1_PHYCHANNEL15 == 15U)) */

#if (defined(DMA_DMA1_PHYCHANNEL16) && (DMA_DMA1_PHYCHANNEL16 == 16U))
#if (defined(DMA_CFG_DMA1_CHANNEL16_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel16_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL16_INT_EN) && (DMA_CFG_DMA1_CHANNEL16_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL16) && (DMA_DMA1_PHYCHANNEL16 == 16U)) */

#if (defined(DMA_DMA1_PHYCHANNEL17) && (DMA_DMA1_PHYCHANNEL17 == 17U))
#if (defined(DMA_CFG_DMA1_CHANNEL17_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel17_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL17_INT_EN) && (DMA_CFG_DMA1_CHANNEL17_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL17) && (DMA_DMA1_PHYCHANNEL17 == 17U)) */

#if (defined(DMA_DMA1_PHYCHANNEL18) && (DMA_DMA1_PHYCHANNEL18 == 18U))
#if (defined(DMA_CFG_DMA1_CHANNEL18_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel18_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL18_INT_EN) && (DMA_CFG_DMA1_CHANNEL18_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL18) && (DMA_DMA1_PHYCHANNEL18 == 18U)) */

#if (defined(DMA_DMA1_PHYCHANNEL19) && (DMA_DMA1_PHYCHANNEL19 == 19U))
#if (defined(DMA_CFG_DMA1_CHANNEL19_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel19_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL19_INT_EN) && (DMA_CFG_DMA1_CHANNEL19_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL19) && (DMA_DMA1_PHYCHANNEL19 == 19U)) */

#if (defined(DMA_DMA1_PHYCHANNEL20) && (DMA_DMA1_PHYCHANNEL20 == 20U))
#if (defined(DMA_CFG_DMA1_CHANNEL20_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel20_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL20_INT_EN) && (DMA_CFG_DMA1_CHANNEL20_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL20) && (DMA_DMA1_PHYCHANNEL20 == 20U)) */

#if (defined(DMA_DMA1_PHYCHANNEL21) && (DMA_DMA1_PHYCHANNEL21 == 21U))
#if (defined(DMA_CFG_DMA1_CHANNEL21_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel21_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL21_INT_EN) && (DMA_CFG_DMA1_CHANNEL21_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL21) && (DMA_DMA1_PHYCHANNEL21 == 21U)) */

#if (defined(DMA_DMA1_PHYCHANNEL22) && (DMA_DMA1_PHYCHANNEL22 == 22U))
#if (defined(DMA_CFG_DMA1_CHANNEL22_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel22_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL22_INT_EN) && (DMA_CFG_DMA1_CHANNEL22_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL22) && (DMA_DMA1_PHYCHANNEL22 == 22U)) */

#if (defined(DMA_DMA1_PHYCHANNEL23) && (DMA_DMA1_PHYCHANNEL23 == 23U))
#if (defined(DMA_CFG_DMA1_CHANNEL23_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel23_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL23_INT_EN) && (DMA_CFG_DMA1_CHANNEL23_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL23) && (DMA_DMA1_PHYCHANNEL23 == 23U)) */

#if (defined(DMA_DMA1_PHYCHANNEL24) && (DMA_DMA1_PHYCHANNEL24 == 24U))
#if (defined(DMA_CFG_DMA1_CHANNEL24_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel24_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL24_INT_EN) && (DMA_CFG_DMA1_CHANNEL24_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL24) && (DMA_DMA1_PHYCHANNEL24 == 24U)) */

#if (defined(DMA_DMA1_PHYCHANNEL25) && (DMA_DMA1_PHYCHANNEL25 == 25U))
#if (defined(DMA_CFG_DMA1_CHANNEL25_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel25_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL25_INT_EN) && (DMA_CFG_DMA1_CHANNEL25_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL25) && (DMA_DMA1_PHYCHANNEL25 == 25U)) */

#if (defined(DMA_DMA1_PHYCHANNEL26) && (DMA_DMA1_PHYCHANNEL26 == 26U))
#if (defined(DMA_CFG_DMA1_CHANNEL26_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel26_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL26_INT_EN) && (DMA_CFG_DMA1_CHANNEL26_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL26) && (DMA_DMA1_PHYCHANNEL26 == 26U)) */

#if (defined(DMA_DMA1_PHYCHANNEL27) && (DMA_DMA1_PHYCHANNEL27 == 27U))
#if (defined(DMA_CFG_DMA1_CHANNEL27_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel27_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL27_INT_EN) && (DMA_CFG_DMA1_CHANNEL27_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL27) && (DMA_DMA1_PHYCHANNEL27 == 27U)) */

#if (defined(DMA_DMA1_PHYCHANNEL28) && (DMA_DMA1_PHYCHANNEL28 == 28U))
#if (defined(DMA_CFG_DMA1_CHANNEL28_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel28_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL28_INT_EN) && (DMA_CFG_DMA1_CHANNEL28_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL28) && (DMA_DMA1_PHYCHANNEL28 == 28U)) */

#if (defined(DMA_DMA1_PHYCHANNEL29) && (DMA_DMA1_PHYCHANNEL29 == 29U))
#if (defined(DMA_CFG_DMA1_CHANNEL29_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel29_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL29_INT_EN) && (DMA_CFG_DMA1_CHANNEL29_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL29) && (DMA_DMA1_PHYCHANNEL29 == 29U)) */

#if (defined(DMA_DMA1_PHYCHANNEL30) && (DMA_DMA1_PHYCHANNEL30 == 30U))
#if (defined(DMA_CFG_DMA1_CHANNEL30_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel30_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL30_INT_EN) && (DMA_CFG_DMA1_CHANNEL30_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL30) && (DMA_DMA1_PHYCHANNEL30 == 30U)) */

#if (defined(DMA_DMA1_PHYCHANNEL31) && (DMA_DMA1_PHYCHANNEL31 == 31U))
#if (defined(DMA_CFG_DMA1_CHANNEL31_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel31_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL31_INT_EN) && (DMA_CFG_DMA1_CHANNEL31_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL31) && (DMA_DMA1_PHYCHANNEL31 == 31U)) */

#if (defined(DMA_DMA1_PHYCHANNEL32) && (DMA_DMA1_PHYCHANNEL32 == 32U))
#if (defined(DMA_CFG_DMA1_CHANNEL32_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel32_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL32_INT_EN) && (DMA_CFG_DMA1_CHANNEL32_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL32) && (DMA_DMA1_PHYCHANNEL32 == 32U)) */

#if (defined(DMA_DMA1_PHYCHANNEL33) && (DMA_DMA1_PHYCHANNEL33 == 33U))
#if (defined(DMA_CFG_DMA1_CHANNEL33_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel33_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL33_INT_EN) && (DMA_CFG_DMA1_CHANNEL33_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL33) && (DMA_DMA1_PHYCHANNEL33 == 33U)) */

#if (defined(DMA_DMA1_PHYCHANNEL34) && (DMA_DMA1_PHYCHANNEL34 == 34U))
#if (defined(DMA_CFG_DMA1_CHANNEL34_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel34_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL34_INT_EN) && (DMA_CFG_DMA1_CHANNEL34_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL34) && (DMA_DMA1_PHYCHANNEL34 == 34U)) */

#if (defined(DMA_DMA1_PHYCHANNEL35) && (DMA_DMA1_PHYCHANNEL35 == 35U))
#if (defined(DMA_CFG_DMA1_CHANNEL35_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel35_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL35_INT_EN) && (DMA_CFG_DMA1_CHANNEL35_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL35) && (DMA_DMA1_PHYCHANNEL35 == 35U)) */

#if (defined(DMA_DMA1_PHYCHANNEL36) && (DMA_DMA1_PHYCHANNEL36 == 36U))
#if (defined(DMA_CFG_DMA1_CHANNEL36_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel36_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL36_INT_EN) && (DMA_CFG_DMA1_CHANNEL36_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL36) && (DMA_DMA1_PHYCHANNEL36 == 36U)) */

#if (defined(DMA_DMA1_PHYCHANNEL37) && (DMA_DMA1_PHYCHANNEL37 == 37U))
#if (defined(DMA_CFG_DMA1_CHANNEL37_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel37_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL37_INT_EN) && (DMA_CFG_DMA1_CHANNEL37_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL37) && (DMA_DMA1_PHYCHANNEL37 == 37U)) */

#if (defined(DMA_DMA1_PHYCHANNEL38) && (DMA_DMA1_PHYCHANNEL38 == 38U))
#if (defined(DMA_CFG_DMA1_CHANNEL38_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel38_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL38_INT_EN) && (DMA_CFG_DMA1_CHANNEL38_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL38) && (DMA_DMA1_PHYCHANNEL38 == 38U)) */

#if (defined(DMA_DMA1_PHYCHANNEL39) && (DMA_DMA1_PHYCHANNEL39 == 39U))
#if (defined(DMA_CFG_DMA1_CHANNEL39_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel39_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL39_INT_EN) && (DMA_CFG_DMA1_CHANNEL39_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL39) && (DMA_DMA1_PHYCHANNEL39 == 39U)) */

#if (defined(DMA_DMA1_PHYCHANNEL40) && (DMA_DMA1_PHYCHANNEL40 == 40U))
#if (defined(DMA_CFG_DMA1_CHANNEL40_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel40_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL40_INT_EN) && (DMA_CFG_DMA1_CHANNEL40_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL40) && (DMA_DMA1_PHYCHANNEL40 == 40U)) */

#if (defined(DMA_DMA1_PHYCHANNEL41) && (DMA_DMA1_PHYCHANNEL41 == 41U))
#if (defined(DMA_CFG_DMA1_CHANNEL41_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel41_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL41_INT_EN) && (DMA_CFG_DMA1_CHANNEL41_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL41) && (DMA_DMA1_PHYCHANNEL41 == 41U)) */

#if (defined(DMA_DMA1_PHYCHANNEL42) && (DMA_DMA1_PHYCHANNEL42 == 42U))
#if (defined(DMA_CFG_DMA1_CHANNEL42_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel42_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL42_INT_EN) && (DMA_CFG_DMA1_CHANNEL42_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL42) && (DMA_DMA1_PHYCHANNEL42 == 42U)) */

#if (defined(DMA_DMA1_PHYCHANNEL43) && (DMA_DMA1_PHYCHANNEL43 == 43U))
#if (defined(DMA_CFG_DMA1_CHANNEL43_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel43_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL43_INT_EN) && (DMA_CFG_DMA1_CHANNEL43_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL43) && (DMA_DMA1_PHYCHANNEL43 == 43U)) */

#if (defined(DMA_DMA1_PHYCHANNEL44) && (DMA_DMA1_PHYCHANNEL44 == 44U))
#if (defined(DMA_CFG_DMA1_CHANNEL44_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel44_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL44_INT_EN) && (DMA_CFG_DMA1_CHANNEL44_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL44) && (DMA_DMA1_PHYCHANNEL44 == 44U)) */

#if (defined(DMA_DMA1_PHYCHANNEL45) && (DMA_DMA1_PHYCHANNEL45 == 45U))
#if (defined(DMA_CFG_DMA1_CHANNEL45_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel45_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL45_INT_EN) && (DMA_CFG_DMA1_CHANNEL45_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL45) && (DMA_DMA1_PHYCHANNEL45 == 45U)) */

#if (defined(DMA_DMA1_PHYCHANNEL46) && (DMA_DMA1_PHYCHANNEL46 == 46U))
#if (defined(DMA_CFG_DMA1_CHANNEL46_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel46_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL46_INT_EN) && (DMA_CFG_DMA1_CHANNEL46_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL46) && (DMA_DMA1_PHYCHANNEL46 == 46U)) */

#if (defined(DMA_DMA1_PHYCHANNEL47) && (DMA_DMA1_PHYCHANNEL47 == 47U))
#if (defined(DMA_CFG_DMA1_CHANNEL47_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel47_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL47_INT_EN) && (DMA_CFG_DMA1_CHANNEL47_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL47) && (DMA_DMA1_PHYCHANNEL47 == 47U)) */

#if (defined(DMA_DMA1_PHYCHANNEL48) && (DMA_DMA1_PHYCHANNEL48 == 48U))
#if (defined(DMA_CFG_DMA1_CHANNEL48_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel48_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL48_INT_EN) && (DMA_CFG_DMA1_CHANNEL48_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL48) && (DMA_DMA1_PHYCHANNEL48 == 48U)) */

#if (defined(DMA_DMA1_PHYCHANNEL49) && (DMA_DMA1_PHYCHANNEL49 == 49U))
#if (defined(DMA_CFG_DMA1_CHANNEL49_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel49_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL49_INT_EN) && (DMA_CFG_DMA1_CHANNEL49_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL49) && (DMA_DMA1_PHYCHANNEL49 == 49U)) */

#if (defined(DMA_DMA1_PHYCHANNEL50) && (DMA_DMA1_PHYCHANNEL50 == 50U))
#if (defined(DMA_CFG_DMA1_CHANNEL50_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel50_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL50_INT_EN) && (DMA_CFG_DMA1_CHANNEL50_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL50) && (DMA_DMA1_PHYCHANNEL50 == 50U)) */

#if (defined(DMA_DMA1_PHYCHANNEL51) && (DMA_DMA1_PHYCHANNEL51 == 51U))
#if (defined(DMA_CFG_DMA1_CHANNEL51_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel51_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL51_INT_EN) && (DMA_CFG_DMA1_CHANNEL51_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL51) && (DMA_DMA1_PHYCHANNEL51 == 51U)) */

#if (defined(DMA_DMA1_PHYCHANNEL52) && (DMA_DMA1_PHYCHANNEL52 == 52U))
#if (defined(DMA_CFG_DMA1_CHANNEL52_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel52_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL52_INT_EN) && (DMA_CFG_DMA1_CHANNEL52_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL52) && (DMA_DMA1_PHYCHANNEL52 == 52U)) */

#if (defined(DMA_DMA1_PHYCHANNEL53) && (DMA_DMA1_PHYCHANNEL53 == 53U))
#if (defined(DMA_CFG_DMA1_CHANNEL53_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel53_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL53_INT_EN) && (DMA_CFG_DMA1_CHANNEL53_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL53) && (DMA_DMA1_PHYCHANNEL53 == 53U)) */

#if (defined(DMA_DMA1_PHYCHANNEL54) && (DMA_DMA1_PHYCHANNEL54 == 54U))
#if (defined(DMA_CFG_DMA1_CHANNEL54_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel54_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL54_INT_EN) && (DMA_CFG_DMA1_CHANNEL54_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL54) && (DMA_DMA1_PHYCHANNEL54 == 54U)) */

#if (defined(DMA_DMA1_PHYCHANNEL55) && (DMA_DMA1_PHYCHANNEL55 == 55U))
#if (defined(DMA_CFG_DMA1_CHANNEL55_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel55_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL55_INT_EN) && (DMA_CFG_DMA1_CHANNEL55_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL55) && (DMA_DMA1_PHYCHANNEL55 == 55U)) */

#if (defined(DMA_DMA1_PHYCHANNEL56) && (DMA_DMA1_PHYCHANNEL56 == 56U))
#if (defined(DMA_CFG_DMA1_CHANNEL56_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel56_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL56_INT_EN) && (DMA_CFG_DMA1_CHANNEL56_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL56) && (DMA_DMA1_PHYCHANNEL56 == 56U)) */

#if (defined(DMA_DMA1_PHYCHANNEL57) && (DMA_DMA1_PHYCHANNEL57 == 57U))
#if (defined(DMA_CFG_DMA1_CHANNEL57_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel57_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL57_INT_EN) && (DMA_CFG_DMA1_CHANNEL57_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL57) && (DMA_DMA1_PHYCHANNEL57 == 57U)) */

#if (defined(DMA_DMA1_PHYCHANNEL58) && (DMA_DMA1_PHYCHANNEL58 == 58U))
#if (defined(DMA_CFG_DMA1_CHANNEL58_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel58_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL58_INT_EN) && (DMA_CFG_DMA1_CHANNEL58_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL58) && (DMA_DMA1_PHYCHANNEL58 == 58U)) */

#if (defined(DMA_DMA1_PHYCHANNEL59) && (DMA_DMA1_PHYCHANNEL59 == 59U))
#if (defined(DMA_CFG_DMA1_CHANNEL59_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel59_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL59_INT_EN) && (DMA_CFG_DMA1_CHANNEL59_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL59) && (DMA_DMA1_PHYCHANNEL59 == 59U)) */

#if (defined(DMA_DMA1_PHYCHANNEL60) && (DMA_DMA1_PHYCHANNEL60 == 60U))
#if (defined(DMA_CFG_DMA1_CHANNEL60_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel60_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL60_INT_EN) && (DMA_CFG_DMA1_CHANNEL60_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL60) && (DMA_DMA1_PHYCHANNEL60 == 60U)) */

#if (defined(DMA_DMA1_PHYCHANNEL61) && (DMA_DMA1_PHYCHANNEL61 == 61U))
#if (defined(DMA_CFG_DMA1_CHANNEL61_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel61_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL61_INT_EN) && (DMA_CFG_DMA1_CHANNEL61_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL61) && (DMA_DMA1_PHYCHANNEL61 == 61U)) */

#if (defined(DMA_DMA1_PHYCHANNEL62) && (DMA_DMA1_PHYCHANNEL62 == 62U))
#if (defined(DMA_CFG_DMA1_CHANNEL62_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel62_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL62_INT_EN) && (DMA_CFG_DMA1_CHANNEL62_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL62) && (DMA_DMA1_PHYCHANNEL62 == 62U)) */

#if (defined(DMA_DMA1_PHYCHANNEL63) && (DMA_DMA1_PHYCHANNEL63 == 63U))
#if (defined(DMA_CFG_DMA1_CHANNEL63_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma1Channel63_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA1_CHANNEL63_INT_EN) && (DMA_CFG_DMA1_CHANNEL63_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA1_PHYCHANNEL63) && (DMA_DMA1_PHYCHANNEL63 == 63U)) */

#endif /* \(defined(DMA_HWUNIT_DMA1) && (DMA_HWUNIT_DMA1 == 1U)) */

#if (defined(DMA_HWUNIT_DMA2) && (DMA_HWUNIT_DMA2 == 2U))

#if (defined(DMA_DMA2_PHYCHANNEL0) && (DMA_DMA2_PHYCHANNEL0 == 0U))
#if (defined(DMA_CFG_DMA2_CHANNEL0_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel0_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL0_INT_EN) && (DMA_CFG_DMA2_CHANNEL0_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL0) && (DMA_DMA2_PHYCHANNEL0 == 0U)) */

#if (defined(DMA_DMA2_PHYCHANNEL1) && (DMA_DMA2_PHYCHANNEL1 == 1U))
#if (defined(DMA_CFG_DMA2_CHANNEL1_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel1_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL1_INT_EN) && (DMA_CFG_DMA2_CHANNEL1_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL1) && (DMA_DMA2_PHYCHANNEL1 == 1U)) */

#if (defined(DMA_DMA2_PHYCHANNEL2) && (DMA_DMA2_PHYCHANNEL2 == 2U))
#if (defined(DMA_CFG_DMA2_CHANNEL2_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel2_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL2_INT_EN) && (DMA_CFG_DMA2_CHANNEL2_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL2) && (DMA_DMA2_PHYCHANNEL2 == 2U)) */

#if (defined(DMA_DMA2_PHYCHANNEL3) && (DMA_DMA2_PHYCHANNEL3 == 3U))
#if (defined(DMA_CFG_DMA2_CHANNEL3_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel3_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL3_INT_EN) && (DMA_CFG_DMA2_CHANNEL3_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL3) && (DMA_DMA2_PHYCHANNEL3 == 3U)) */

#if (defined(DMA_DMA2_PHYCHANNEL4) && (DMA_DMA2_PHYCHANNEL4 == 4U))
#if (defined(DMA_CFG_DMA2_CHANNEL4_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel4_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL4_INT_EN) && (DMA_CFG_DMA2_CHANNEL4_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL4) && (DMA_DMA2_PHYCHANNEL4 == 4U)) */

#if (defined(DMA_DMA2_PHYCHANNEL5) && (DMA_DMA2_PHYCHANNEL5 == 5U))
#if (defined(DMA_CFG_DMA2_CHANNEL5_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel5_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL5_INT_EN) && (DMA_CFG_DMA2_CHANNEL5_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL5) && (DMA_DMA2_PHYCHANNEL5 == 5U)) */

#if (defined(DMA_DMA2_PHYCHANNEL6) && (DMA_DMA2_PHYCHANNEL6 == 6U))
#if (defined(DMA_CFG_DMA2_CHANNEL6_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel6_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL6_INT_EN) && (DMA_CFG_DMA2_CHANNEL6_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL6) && (DMA_DMA2_PHYCHANNEL6 == 6U)) */

#if (defined(DMA_DMA2_PHYCHANNEL7) && (DMA_DMA2_PHYCHANNEL7 == 7U))
#if (defined(DMA_CFG_DMA2_CHANNEL7_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel7_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL7_INT_EN) && (DMA_CFG_DMA2_CHANNEL7_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL7) && (DMA_DMA2_PHYCHANNEL7 == 7U)) */

#if (defined(DMA_DMA2_PHYCHANNEL8) && (DMA_DMA2_PHYCHANNEL8 == 8U))
#if (defined(DMA_CFG_DMA2_CHANNEL8_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel8_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL8_INT_EN) && (DMA_CFG_DMA2_CHANNEL8_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL8) && (DMA_DMA2_PHYCHANNEL8 == 8U)) */

#if (defined(DMA_DMA2_PHYCHANNEL9) && (DMA_DMA2_PHYCHANNEL9 == 9U))
#if (defined(DMA_CFG_DMA2_CHANNEL9_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel9_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL9_INT_EN) && (DMA_CFG_DMA2_CHANNEL9_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL9) && (DMA_DMA2_PHYCHANNEL9 == 9U)) */

#if (defined(DMA_DMA2_PHYCHANNEL10) && (DMA_DMA2_PHYCHANNEL10 == 10U))
#if (defined(DMA_CFG_DMA2_CHANNEL10_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel10_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL10_INT_EN) && (DMA_CFG_DMA2_CHANNEL10_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL10) && (DMA_DMA2_PHYCHANNEL10 == 10U)) */

#if (defined(DMA_DMA2_PHYCHANNEL11) && (DMA_DMA2_PHYCHANNEL11 == 11U))
#if (defined(DMA_CFG_DMA2_CHANNEL11_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel11_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL11_INT_EN) && (DMA_CFG_DMA2_CHANNEL11_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL11) && (DMA_DMA2_PHYCHANNEL11 == 11U)) */

#if (defined(DMA_DMA2_PHYCHANNEL12) && (DMA_DMA2_PHYCHANNEL12 == 12U))
#if (defined(DMA_CFG_DMA2_CHANNEL12_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel12_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL12_INT_EN) && (DMA_CFG_DMA2_CHANNEL12_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL12) && (DMA_DMA2_PHYCHANNEL12 == 12U)) */

#if (defined(DMA_DMA2_PHYCHANNEL13) && (DMA_DMA2_PHYCHANNEL13 == 13U))
#if (defined(DMA_CFG_DMA2_CHANNEL13_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel13_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL13_INT_EN) && (DMA_CFG_DMA2_CHANNEL13_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL13) && (DMA_DMA2_PHYCHANNEL13 == 13U)) */

#if (defined(DMA_DMA2_PHYCHANNEL14) && (DMA_DMA2_PHYCHANNEL14 == 14U))
#if (defined(DMA_CFG_DMA2_CHANNEL14_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel14_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL14_INT_EN) && (DMA_CFG_DMA2_CHANNEL14_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL14) && (DMA_DMA2_PHYCHANNEL14 == 14U)) */

#if (defined(DMA_DMA2_PHYCHANNEL15) && (DMA_DMA2_PHYCHANNEL15 == 15U))
#if (defined(DMA_CFG_DMA2_CHANNEL15_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel15_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL15_INT_EN) && (DMA_CFG_DMA2_CHANNEL15_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL15) && (DMA_DMA2_PHYCHANNEL15 == 15U)) */

#if (defined(DMA_DMA2_PHYCHANNEL16) && (DMA_DMA2_PHYCHANNEL16 == 16U))
#if (defined(DMA_CFG_DMA2_CHANNEL16_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel16_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL16_INT_EN) && (DMA_CFG_DMA2_CHANNEL16_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL16) && (DMA_DMA2_PHYCHANNEL16 == 16U)) */

#if (defined(DMA_DMA2_PHYCHANNEL17) && (DMA_DMA2_PHYCHANNEL17 == 17U))
#if (defined(DMA_CFG_DMA2_CHANNEL17_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel17_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL17_INT_EN) && (DMA_CFG_DMA2_CHANNEL17_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL17) && (DMA_DMA2_PHYCHANNEL17 == 17U)) */

#if (defined(DMA_DMA2_PHYCHANNEL18) && (DMA_DMA2_PHYCHANNEL18 == 18U))
#if (defined(DMA_CFG_DMA2_CHANNEL18_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel18_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL18_INT_EN) && (DMA_CFG_DMA2_CHANNEL18_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL18) && (DMA_DMA2_PHYCHANNEL18 == 18U)) */

#if (defined(DMA_DMA2_PHYCHANNEL19) && (DMA_DMA2_PHYCHANNEL19 == 19U))
#if (defined(DMA_CFG_DMA2_CHANNEL19_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel19_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL19_INT_EN) && (DMA_CFG_DMA2_CHANNEL19_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL19) && (DMA_DMA2_PHYCHANNEL19 == 19U)) */

#if (defined(DMA_DMA2_PHYCHANNEL20) && (DMA_DMA2_PHYCHANNEL20 == 20U))
#if (defined(DMA_CFG_DMA2_CHANNEL20_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel20_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL20_INT_EN) && (DMA_CFG_DMA2_CHANNEL20_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL20) && (DMA_DMA2_PHYCHANNEL20 == 20U)) */

#if (defined(DMA_DMA2_PHYCHANNEL21) && (DMA_DMA2_PHYCHANNEL21 == 21U))
#if (defined(DMA_CFG_DMA2_CHANNEL21_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel21_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL21_INT_EN) && (DMA_CFG_DMA2_CHANNEL21_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL21) && (DMA_DMA2_PHYCHANNEL21 == 21U)) */

#if (defined(DMA_DMA2_PHYCHANNEL22) && (DMA_DMA2_PHYCHANNEL22 == 22U))
#if (defined(DMA_CFG_DMA2_CHANNEL22_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel22_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL22_INT_EN) && (DMA_CFG_DMA2_CHANNEL22_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL22) && (DMA_DMA2_PHYCHANNEL22 == 22U)) */

#if (defined(DMA_DMA2_PHYCHANNEL23) && (DMA_DMA2_PHYCHANNEL23 == 23U))
#if (defined(DMA_CFG_DMA2_CHANNEL23_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel23_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL23_INT_EN) && (DMA_CFG_DMA2_CHANNEL23_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL23) && (DMA_DMA2_PHYCHANNEL23 == 23U)) */

#if (defined(DMA_DMA2_PHYCHANNEL24) && (DMA_DMA2_PHYCHANNEL24 == 24U))
#if (defined(DMA_CFG_DMA2_CHANNEL24_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel24_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL24_INT_EN) && (DMA_CFG_DMA2_CHANNEL24_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL24) && (DMA_DMA2_PHYCHANNEL24 == 24U)) */

#if (defined(DMA_DMA2_PHYCHANNEL25) && (DMA_DMA2_PHYCHANNEL25 == 25U))
#if (defined(DMA_CFG_DMA2_CHANNEL25_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel25_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL25_INT_EN) && (DMA_CFG_DMA2_CHANNEL25_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL25) && (DMA_DMA2_PHYCHANNEL25 == 25U)) */

#if (defined(DMA_DMA2_PHYCHANNEL26) && (DMA_DMA2_PHYCHANNEL26 == 26U))
#if (defined(DMA_CFG_DMA2_CHANNEL26_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel26_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL26_INT_EN) && (DMA_CFG_DMA2_CHANNEL26_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL26) && (DMA_DMA2_PHYCHANNEL26 == 26U)) */

#if (defined(DMA_DMA2_PHYCHANNEL27) && (DMA_DMA2_PHYCHANNEL27 == 27U))
#if (defined(DMA_CFG_DMA2_CHANNEL27_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel27_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL27_INT_EN) && (DMA_CFG_DMA2_CHANNEL27_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL27) && (DMA_DMA2_PHYCHANNEL27 == 27U)) */

#if (defined(DMA_DMA2_PHYCHANNEL28) && (DMA_DMA2_PHYCHANNEL28 == 28U))
#if (defined(DMA_CFG_DMA2_CHANNEL28_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel28_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL28_INT_EN) && (DMA_CFG_DMA2_CHANNEL28_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL28) && (DMA_DMA2_PHYCHANNEL28 == 28U)) */

#if (defined(DMA_DMA2_PHYCHANNEL29) && (DMA_DMA2_PHYCHANNEL29 == 29U))
#if (defined(DMA_CFG_DMA2_CHANNEL29_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel29_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL29_INT_EN) && (DMA_CFG_DMA2_CHANNEL29_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL29) && (DMA_DMA2_PHYCHANNEL29 == 29U)) */

#if (defined(DMA_DMA2_PHYCHANNEL30) && (DMA_DMA2_PHYCHANNEL30 == 30U))
#if (defined(DMA_CFG_DMA2_CHANNEL30_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel30_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL30_INT_EN) && (DMA_CFG_DMA2_CHANNEL30_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL30) && (DMA_DMA2_PHYCHANNEL30 == 30U)) */

#if (defined(DMA_DMA2_PHYCHANNEL31) && (DMA_DMA2_PHYCHANNEL31 == 31U))
#if (defined(DMA_CFG_DMA2_CHANNEL31_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel31_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL31_INT_EN) && (DMA_CFG_DMA2_CHANNEL31_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL31) && (DMA_DMA2_PHYCHANNEL31 == 31U)) */

#if (defined(DMA_DMA2_PHYCHANNEL32) && (DMA_DMA2_PHYCHANNEL32 == 32U))
#if (defined(DMA_CFG_DMA2_CHANNEL32_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel32_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL32_INT_EN) && (DMA_CFG_DMA2_CHANNEL32_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL32) && (DMA_DMA2_PHYCHANNEL32 == 32U)) */

#if (defined(DMA_DMA2_PHYCHANNEL33) && (DMA_DMA2_PHYCHANNEL33 == 33U))
#if (defined(DMA_CFG_DMA2_CHANNEL33_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel33_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL33_INT_EN) && (DMA_CFG_DMA2_CHANNEL33_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL33) && (DMA_DMA2_PHYCHANNEL33 == 33U)) */

#if (defined(DMA_DMA2_PHYCHANNEL34) && (DMA_DMA2_PHYCHANNEL34 == 34U))
#if (defined(DMA_CFG_DMA2_CHANNEL34_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel34_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL34_INT_EN) && (DMA_CFG_DMA2_CHANNEL34_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL34) && (DMA_DMA2_PHYCHANNEL34 == 34U)) */

#if (defined(DMA_DMA2_PHYCHANNEL35) && (DMA_DMA2_PHYCHANNEL35 == 35U))
#if (defined(DMA_CFG_DMA2_CHANNEL35_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel35_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL35_INT_EN) && (DMA_CFG_DMA2_CHANNEL35_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL35) && (DMA_DMA2_PHYCHANNEL35 == 35U)) */

#if (defined(DMA_DMA2_PHYCHANNEL36) && (DMA_DMA2_PHYCHANNEL36 == 36U))
#if (defined(DMA_CFG_DMA2_CHANNEL36_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel36_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL36_INT_EN) && (DMA_CFG_DMA2_CHANNEL36_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL36) && (DMA_DMA2_PHYCHANNEL36 == 36U)) */

#if (defined(DMA_DMA2_PHYCHANNEL37) && (DMA_DMA2_PHYCHANNEL37 == 37U))
#if (defined(DMA_CFG_DMA2_CHANNEL37_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel37_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL37_INT_EN) && (DMA_CFG_DMA2_CHANNEL37_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL37) && (DMA_DMA2_PHYCHANNEL37 == 37U)) */

#if (defined(DMA_DMA2_PHYCHANNEL38) && (DMA_DMA2_PHYCHANNEL38 == 38U))
#if (defined(DMA_CFG_DMA2_CHANNEL38_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel38_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL38_INT_EN) && (DMA_CFG_DMA2_CHANNEL38_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL38) && (DMA_DMA2_PHYCHANNEL38 == 38U)) */

#if (defined(DMA_DMA2_PHYCHANNEL39) && (DMA_DMA2_PHYCHANNEL39 == 39U))
#if (defined(DMA_CFG_DMA2_CHANNEL39_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel39_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL39_INT_EN) && (DMA_CFG_DMA2_CHANNEL39_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL39) && (DMA_DMA2_PHYCHANNEL39 == 39U)) */

#if (defined(DMA_DMA2_PHYCHANNEL40) && (DMA_DMA2_PHYCHANNEL40 == 40U))
#if (defined(DMA_CFG_DMA2_CHANNEL40_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel40_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL40_INT_EN) && (DMA_CFG_DMA2_CHANNEL40_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL40) && (DMA_DMA2_PHYCHANNEL40 == 40U)) */

#if (defined(DMA_DMA2_PHYCHANNEL41) && (DMA_DMA2_PHYCHANNEL41 == 41U))
#if (defined(DMA_CFG_DMA2_CHANNEL41_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel41_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL41_INT_EN) && (DMA_CFG_DMA2_CHANNEL41_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL41) && (DMA_DMA2_PHYCHANNEL41 == 41U)) */

#if (defined(DMA_DMA2_PHYCHANNEL42) && (DMA_DMA2_PHYCHANNEL42 == 42U))
#if (defined(DMA_CFG_DMA2_CHANNEL42_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel42_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL42_INT_EN) && (DMA_CFG_DMA2_CHANNEL42_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL42) && (DMA_DMA2_PHYCHANNEL42 == 42U)) */

#if (defined(DMA_DMA2_PHYCHANNEL43) && (DMA_DMA2_PHYCHANNEL43 == 43U))
#if (defined(DMA_CFG_DMA2_CHANNEL43_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma2Channel43_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA2_CHANNEL43_INT_EN) && (DMA_CFG_DMA2_CHANNEL43_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA2_PHYCHANNEL43) && (DMA_DMA2_PHYCHANNEL43 == 43U)) */

#endif /* \(defined(DMA_HWUNIT_DMA2) && (DMA_HWUNIT_DMA2 == 2U)) */

#if (defined(DMA_HWUNIT_DMA3) && (DMA_HWUNIT_DMA3 == 3U))

#if (defined(DMA_DMA3_PHYCHANNEL0) && (DMA_DMA3_PHYCHANNEL0 == 0U))
#if (defined(DMA_CFG_DMA3_CHANNEL0_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel0_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL0_INT_EN) && (DMA_CFG_DMA3_CHANNEL0_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL0) && (DMA_DMA3_PHYCHANNEL0 == 0U)) */

#if (defined(DMA_DMA3_PHYCHANNEL1) && (DMA_DMA3_PHYCHANNEL1 == 1U))
#if (defined(DMA_CFG_DMA3_CHANNEL1_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel1_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL1_INT_EN) && (DMA_CFG_DMA3_CHANNEL1_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL1) && (DMA_DMA3_PHYCHANNEL1 == 1U)) */

#if (defined(DMA_DMA3_PHYCHANNEL2) && (DMA_DMA3_PHYCHANNEL2 == 2U))
#if (defined(DMA_CFG_DMA3_CHANNEL2_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel2_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL2_INT_EN) && (DMA_CFG_DMA3_CHANNEL2_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL2) && (DMA_DMA3_PHYCHANNEL2 == 2U)) */

#if (defined(DMA_DMA3_PHYCHANNEL3) && (DMA_DMA3_PHYCHANNEL3 == 3U))
#if (defined(DMA_CFG_DMA3_CHANNEL3_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel3_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL3_INT_EN) && (DMA_CFG_DMA3_CHANNEL3_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL3) && (DMA_DMA3_PHYCHANNEL3 == 3U)) */

#if (defined(DMA_DMA3_PHYCHANNEL4) && (DMA_DMA3_PHYCHANNEL4 == 4U))
#if (defined(DMA_CFG_DMA3_CHANNEL4_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel4_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL4_INT_EN) && (DMA_CFG_DMA3_CHANNEL4_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL4) && (DMA_DMA3_PHYCHANNEL4 == 4U)) */

#if (defined(DMA_DMA3_PHYCHANNEL5) && (DMA_DMA3_PHYCHANNEL5 == 5U))
#if (defined(DMA_CFG_DMA3_CHANNEL5_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel5_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL5_INT_EN) && (DMA_CFG_DMA3_CHANNEL5_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL5) && (DMA_DMA3_PHYCHANNEL5 == 5U)) */

#if (defined(DMA_DMA3_PHYCHANNEL6) && (DMA_DMA3_PHYCHANNEL6 == 6U))
#if (defined(DMA_CFG_DMA3_CHANNEL6_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel6_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL6_INT_EN) && (DMA_CFG_DMA3_CHANNEL6_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL6) && (DMA_DMA3_PHYCHANNEL6 == 6U)) */

#if (defined(DMA_DMA3_PHYCHANNEL7) && (DMA_DMA3_PHYCHANNEL7 == 7U))
#if (defined(DMA_CFG_DMA3_CHANNEL7_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel7_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL7_INT_EN) && (DMA_CFG_DMA3_CHANNEL7_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL7) && (DMA_DMA3_PHYCHANNEL7 == 7U)) */

#if (defined(DMA_DMA3_PHYCHANNEL8) && (DMA_DMA3_PHYCHANNEL8 == 8U))
#if (defined(DMA_CFG_DMA3_CHANNEL8_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel8_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL8_INT_EN) && (DMA_CFG_DMA3_CHANNEL8_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL8) && (DMA_DMA3_PHYCHANNEL8 == 8U)) */

#if (defined(DMA_DMA3_PHYCHANNEL9) && (DMA_DMA3_PHYCHANNEL9 == 9U))
#if (defined(DMA_CFG_DMA3_CHANNEL9_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel9_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL9_INT_EN) && (DMA_CFG_DMA3_CHANNEL9_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL9) && (DMA_DMA3_PHYCHANNEL9 == 9U)) */

#if (defined(DMA_DMA3_PHYCHANNEL10) && (DMA_DMA3_PHYCHANNEL10 == 10U))
#if (defined(DMA_CFG_DMA3_CHANNEL10_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel10_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL10_INT_EN) && (DMA_CFG_DMA3_CHANNEL10_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL10) && (DMA_DMA3_PHYCHANNEL10 == 10U)) */

#if (defined(DMA_DMA3_PHYCHANNEL11) && (DMA_DMA3_PHYCHANNEL11 == 11U))
#if (defined(DMA_CFG_DMA3_CHANNEL11_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel11_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL11_INT_EN) && (DMA_CFG_DMA3_CHANNEL11_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL11) && (DMA_DMA3_PHYCHANNEL11 == 11U)) */

#if (defined(DMA_DMA3_PHYCHANNEL12) && (DMA_DMA3_PHYCHANNEL12 == 12U))
#if (defined(DMA_CFG_DMA3_CHANNEL12_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel12_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL12_INT_EN) && (DMA_CFG_DMA3_CHANNEL12_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL12) && (DMA_DMA3_PHYCHANNEL12 == 12U)) */

#if (defined(DMA_DMA3_PHYCHANNEL13) && (DMA_DMA3_PHYCHANNEL13 == 13U))
#if (defined(DMA_CFG_DMA3_CHANNEL13_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel13_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL13_INT_EN) && (DMA_CFG_DMA3_CHANNEL13_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL13) && (DMA_DMA3_PHYCHANNEL13 == 13U)) */

#if (defined(DMA_DMA3_PHYCHANNEL14) && (DMA_DMA3_PHYCHANNEL14 == 14U))
#if (defined(DMA_CFG_DMA3_CHANNEL14_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel14_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL14_INT_EN) && (DMA_CFG_DMA3_CHANNEL14_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL14) && (DMA_DMA3_PHYCHANNEL14 == 14U)) */

#if (defined(DMA_DMA3_PHYCHANNEL15) && (DMA_DMA3_PHYCHANNEL15 == 15U))
#if (defined(DMA_CFG_DMA3_CHANNEL15_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel15_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL15_INT_EN) && (DMA_CFG_DMA3_CHANNEL15_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL15) && (DMA_DMA3_PHYCHANNEL15 == 15U)) */

#if (defined(DMA_DMA3_PHYCHANNEL16) && (DMA_DMA3_PHYCHANNEL16 == 16U))
#if (defined(DMA_CFG_DMA3_CHANNEL16_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel16_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL16_INT_EN) && (DMA_CFG_DMA3_CHANNEL16_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL16) && (DMA_DMA3_PHYCHANNEL16 == 16U)) */

#if (defined(DMA_DMA3_PHYCHANNEL17) && (DMA_DMA3_PHYCHANNEL17 == 17U))
#if (defined(DMA_CFG_DMA3_CHANNEL17_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel17_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL17_INT_EN) && (DMA_CFG_DMA3_CHANNEL17_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL17) && (DMA_DMA3_PHYCHANNEL17 == 17U)) */

#if (defined(DMA_DMA3_PHYCHANNEL18) && (DMA_DMA3_PHYCHANNEL18 == 18U))
#if (defined(DMA_CFG_DMA3_CHANNEL18_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel18_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL18_INT_EN) && (DMA_CFG_DMA3_CHANNEL18_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL18) && (DMA_DMA3_PHYCHANNEL18 == 18U)) */

#if (defined(DMA_DMA3_PHYCHANNEL19) && (DMA_DMA3_PHYCHANNEL19 == 19U))
#if (defined(DMA_CFG_DMA3_CHANNEL19_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel19_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL19_INT_EN) && (DMA_CFG_DMA3_CHANNEL19_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL19) && (DMA_DMA3_PHYCHANNEL19 == 19U)) */

#if (defined(DMA_DMA3_PHYCHANNEL20) && (DMA_DMA3_PHYCHANNEL20 == 20U))
#if (defined(DMA_CFG_DMA3_CHANNEL20_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel20_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL20_INT_EN) && (DMA_CFG_DMA3_CHANNEL20_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL20) && (DMA_DMA3_PHYCHANNEL20 == 20U)) */

#if (defined(DMA_DMA3_PHYCHANNEL21) && (DMA_DMA3_PHYCHANNEL21 == 21U))
#if (defined(DMA_CFG_DMA3_CHANNEL21_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel21_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL21_INT_EN) && (DMA_CFG_DMA3_CHANNEL21_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL21) && (DMA_DMA3_PHYCHANNEL21 == 21U)) */

#if (defined(DMA_DMA3_PHYCHANNEL22) && (DMA_DMA3_PHYCHANNEL22 == 22U))
#if (defined(DMA_CFG_DMA3_CHANNEL22_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel22_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL22_INT_EN) && (DMA_CFG_DMA3_CHANNEL22_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL22) && (DMA_DMA3_PHYCHANNEL22 == 22U)) */

#if (defined(DMA_DMA3_PHYCHANNEL23) && (DMA_DMA3_PHYCHANNEL23 == 23U))
#if (defined(DMA_CFG_DMA3_CHANNEL23_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_INT_EN == STD_ON))
extern FUNC(void, DMA_PUBLIC_CODE) Dma_Dma3Channel23_ISR
(
    void
);
#endif /* \(defined(DMA_CFG_DMA3_CHANNEL23_INT_EN) && (DMA_CFG_DMA3_CHANNEL23_INT_EN == STD_ON)) */
#endif /* \(defined(DMA_DMA3_PHYCHANNEL23) && (DMA_DMA3_PHYCHANNEL23 == 23U)) */

#endif /* \(defined(DMA_HWUNIT_DMA3) && (DMA_HWUNIT_DMA3 == 3U)) */


#endif /* \(DMA_CFG_INTERRUPT_EN  == STD_ON) */

#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dma_MemMap.h"

#endif /* \DMA_IRQ_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

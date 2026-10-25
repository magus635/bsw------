/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    intc_hal.h
 * Author:      01369
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/

/*
*#Violation Summary
*
*#intc_hal_h_REF_1:MISRAC2012-Dir-1.1; MISRAC2012-Dir-1.2; MISRAC2012-Dir-4.2;
* Justification: Inline assembly for CPU-specific operations.
*
*#intc_hal_h_REF_2:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity.
*
*#intc_hal_h_REF_3:MISRAC2012-Rule-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#intc_hal_h_REF_4:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#intc_hal_h_REF_5:MISRAC2012-Rule-10.5;
* Justification: Limitation of Coretex-R52+ Core; Boolean can only be representes as unit8.
*
*#intc_hal_h_REF_6:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#intc_hal_h_REF_7:MISRAC2012-Rule-2.7;
* Justification: The parameter have used in this function.
*
*/

#ifndef INTC_HAL_H_
#define INTC_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Trigger methods of interrupt */
/* Trigger interrupt is valid at high-level */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_TRIGGERMETHOD_LEVEL (0U)
/* Trigger interrupt is valid at rising edge-triggered */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_TRIGGERMETHOD_EDGE (1U)

/* Identification of two kinds of interrupt */
/* The coressponding interrupt is in Group 0 (FIQ) */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTERRUPTGROUP_FIQ (0U)
/* The coressponding interrupt is in Group 1 (IRQ) */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTERRUPTGROUP_IRQ (1U)
/* Maximun value of priority */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_MAX_PRIORITY (31U)


/* Interrupt ID number */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_0 (0U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_1 (1U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_2 (2U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_3 (3U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_4 (4U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_5 (5U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_6 (6U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_7 (7U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_8 (8U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_9 (9U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_10 (10U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_11 (11U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_12 (12U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_13 (13U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_14 (14U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SGI_15 (15U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GIPC_INT_0 (16U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GIPC_INT_1 (17U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GIPC_INT_2 (18U)


/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GIPC0_INT_0              INTC_INTID_GIPC_INT_0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GIPC0_INT_1              INTC_INTID_GIPC_INT_1
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GIPC0_INT_2              INTC_INTID_GIPC_INT_2

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GIPC1_INT_0              (19U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GIPC1_INT_1              (20U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GIPC1_INT_2              (21U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DEBUG_COMM_CH_INT        (22U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_PMU_OVERFLOW_INT         (23U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CROSS_TRIGGER_INT        (24U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_VCPU_MAINTENANCE_INT     (25U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_HYP_TIMER_INT            (26U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_VITUAL_TIMER_INT         (27U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_PHYSICAL_TIMER_INT       (30U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CPUWDT_INT_0 (32U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CPUWDT_E_INT (33U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CPUWDT_INT_1 (34U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CPUWDT0_INT_0 INTC_INTID_CPUWDT_INT_0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CPUWDT0_E_INT INTC_INTID_CPUWDT_E_INT
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CPUWDT0_INT_1 INTC_INTID_CPUWDT_INT_1


#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_PMC_TE_INT          (35U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SAFEWDT_INT_0 (36U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SAFEWDT_E_INT (37U)

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CPUWDT1_INT_0 (38U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CPUWDT1_INT_1 (39U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MAINCORE_COMMRX0 (40U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MAINCORE_COMMTX0 (41U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MAINCORE_COMMRX1 (42U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MAINCORE_COMMTX1 (43U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MAINCORE_BTCM_ERR_0 (44U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MAINCORE_BTCM_ERR_1 (45U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER0_COMMRX0 INTC_INTID_MAINCORE_COMMRX0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER0_COMMTX0 INTC_INTID_MAINCORE_COMMTX0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER0_COMMRX1 INTC_INTID_MAINCORE_COMMRX1
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER0_COMMTX1 INTC_INTID_MAINCORE_COMMTX1

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER0_BTCM_ERR_0 INTC_INTID_MAINCORE_BTCM_ERR_0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER0_BTCM_ERR_1 INTC_INTID_MAINCORE_BTCM_ERR_1

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER1_COMMRX0 (46U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER1_COMMTX0 (47U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER1_COMMRX1 (48U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER1_COMMTX1 (49U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER1_BTCM_ERR_0 (50U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_CLUSTER1_BTCM_ERR_1 (51U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_RCC_WARM_RESET_INT  (52U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_PWRC_INT            (53U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_PWRC_CORE_SLEEP_INT (55U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE0_0 (56U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE0_1 (57U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE0_2 (58U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE0_3 (59U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE1_0 (89U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE1_1 (90U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE1_2 (91U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE1_3 (92U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE00_0 INTC_INTID_SOFT_INT_CORE0_0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE00_1 INTC_INTID_SOFT_INT_CORE0_1
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE00_2 INTC_INTID_SOFT_INT_CORE0_2
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE00_3 INTC_INTID_SOFT_INT_CORE0_3

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE01_0 INTC_INTID_SOFT_INT_CORE1_0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE01_1 INTC_INTID_SOFT_INT_CORE1_1
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE01_2 INTC_INTID_SOFT_INT_CORE1_2
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE01_3 INTC_INTID_SOFT_INT_CORE1_3

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE10_0 INTC_INTID_SOFT_INT_CORE0_0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE10_1 INTC_INTID_SOFT_INT_CORE0_1
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE10_2 INTC_INTID_SOFT_INT_CORE0_2
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE10_3 INTC_INTID_SOFT_INT_CORE0_3

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE11_0 INTC_INTID_SOFT_INT_CORE1_0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE11_1 INTC_INTID_SOFT_INT_CORE1_1
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE11_2 INTC_INTID_SOFT_INT_CORE1_2
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SOFT_INT_CORE11_3 INTC_INTID_SOFT_INT_CORE1_3


/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SAC_INT_0 (62U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SAC_INT_1 (63U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SAC_INT_2 (64U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SAC_INT_3 (65U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_OVC_INT_0 (68U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_OVC_INT_1 (69U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_OVC0_INT_0 INTC_INTID_OVC_INT_0
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_OVC0_INT_1 INTC_INTID_OVC_INT_1

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_OVC1_INT_0 (70U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_OVC1_INT_1 (71U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_SBD_INT            (72U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_SBD_PERCH_TX_INT_0 (73U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_SBD_PERCH_TX_INT_1 (74U)
/* #Violation: intc_hal_h_REF_4 */

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined (THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_SBD_PERCH_TX_INT_2 (75U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_SBD_PERCH_TX_INT_3 (76U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_SBD_PERCH_RX_INT_0 (77U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_SBD_PERCH_RX_INT_1 (78U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined (THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_SBD_PERCH_RX_INT_2 (79U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_SBD_PERCH_RX_INT_3 (80U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ETH_LPI_INT      (81U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_0 (95U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_1 (96U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_2 (97U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_3 (98U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined (THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_4 (99U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_5 (100U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_6 (101U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_7 (102U)
#endif

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_8 (103U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_9 (104U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_10 (105U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_11 (106U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_12 (107U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_13 (108U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_14 (287U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AXI_DMA_CH_INT_15 (288U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_0 (115U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_1 (116U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_2 (117U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_3 (118U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_4 (119U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_5 (120U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_6 (121U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_7 (122U)

#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_8 (123U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_9 (124U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_10 (125U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_11 (126U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_12 (127U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_13 (128U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_14 (217U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_15 (218U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_16 (219U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_17 (220U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_18 (221U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_19 (222U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_20 (223U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_21 (224U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_22 (225U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_23 (226U)
#endif

#if defined(THA6_THA6104)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_24 (163U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_25 (164U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_26 (165U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_27 (166U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_28 (167U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_29 (168U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_30 (169U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_31 (170U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_32 (171U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_33 (172U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_34 (173U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_35 (174U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_36 (175U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_37 (176U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_38 (177U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_39 (178U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_40 (179U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_41 (180U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_42 (181U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB2_DMA_CH_INT_43 (182U)
#endif


#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined (THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_0 (129U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_1 (130U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_2 (131U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_3 (132U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_4 (133U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_5 (134U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_6 (135U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_7 (136U)
#endif


#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_8 (137U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_9 (138U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_10 (139U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_11 (140U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_12 (141U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_13 (142U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_14 (277U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_15 (278U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_16 (279U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_17 (280U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_18 (281U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_19 (282U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_20 (283U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_21 (284U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_22 (285U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB3_DMA_CH_INT_23 (286U)
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined (THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_0 (149U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_1 (150U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_2 (151U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_3 (152U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_4 (153U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_5 (154U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_6 (155U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_7 (156U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_8 (157U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_9 (158U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_10 (159U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_11 (160U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_12 (161U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_13 (162U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_14 (163U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_15 (164U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_16 (165U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_17 (166U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_18 (167U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_19 (168U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_20 (169U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_21 (170U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_22 (171U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_23 (172U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_24 (173U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_25 (174U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_26 (175U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_27 (176U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_28 (177U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_29 (178U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_30 (179U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_31 (180U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_32 (181U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_33 (182U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_34 (183U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_35 (184U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_36 (185U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_37 (186U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_38 (187U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_39 (188U)
#endif

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_40 (189U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_41 (190U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_42 (191U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_43 (192U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_44 (193U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_45 (194U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_46 (199U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_47 (200U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_48 (201U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_49 (202U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_50 (203U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_51 (204U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_52 (205U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_53 (206U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_54 (207U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_55 (208U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_56 (209U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_57 (210U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_58 (211U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_59 (212U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_60 (213U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_61 (214U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_62 (215U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_AHB1_DMA_CH_INT_63 (216U)
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6104) || defined (THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_PFLASH0_FINISH (195U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_PFLASH0_ERROR  (196U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_PFLASH1_FINISH (197U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_PFLASH1_ERROR  (198U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_DFLASH0_FINISH (227U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_DFLASH0_ERROR  (228U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_PASSWORD_ERROR (234U)
#endif

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM0_PFLS_INT_0 (195U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM0_PFLS_INT_1 (196U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM0_PFLS_INT_2 (197U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM0_PFLS_INT_3 (198U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_DFLS_INT_0 (227U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_DFLS_INT_1 (228U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM_DFLS_INT_2 (234U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM1_PFLS_INT_0 (229U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM1_PFLS_INT_1 (230U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM1_PFLS_INT_2 (231U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM1_PFLS_INT_3 (232U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_NVM1_DFLS_INT (665U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_HSM_IRQ_0 (235U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_HSM_IRQ_1 (236U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_HSM_IRQ_2 (237U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_HSM_IRQ_3 (238U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_HSM_IRQ_4 (239U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_HSM_IRQ_5 (240U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_BASETIMER0_INT (246U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_BASETIMER1_INT (247U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_BASETIMER2_INT (248U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_BASETIMER3_INT (249U)

#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined (THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_BASETIMER4_INT (250U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_BASETIMER5_INT (251U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_MCAN2_INT_0 (252U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_MCAN2_INT_1 (253U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_MCAN1_INT_0 (254U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_MCAN1_INT_1 (255U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_MCAN0_INT_0 (256U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_MCAN0_INT_1 (257U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_DMU0_INT    (258U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_DMU1_INT    (259U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_DMU2_INT    (260U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_0 (261U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_1 (262U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_2 (263U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_3 (264U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_4 (265U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_5 (266U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_6 (267U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_7 (268U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_8 (269U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_9 (270U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_10 (271U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_11 (272U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_12 (273U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_13 (274U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_14 (275U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP0_INT_ROUTE_15 (276U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_MCAN2_INT_0 (293U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_MCAN2_INT_1 (294U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_MCAN1_INT_0 (295U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_MCAN1_INT_1 (296U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_MCAN0_INT_0 (297U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_MCAN0_INT_1 (298U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_DMU0_INT (299U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_DMU1_INT (300U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_DMU2_INT (301U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_0 (302U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_1 (303U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_2 (304U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_3 (305U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_4 (306U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_5 (307U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_6 (308U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_7 (309U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_8 (310U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_9 (311U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_10 (312U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_11 (313U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_12 (314U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_13 (315U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_14 (316U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP1_INT_ROUTE_15 (317U)

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_MCAN2_INT_0 (318U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_MCAN2_INT_1 (319U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_MCAN1_INT_0 (320U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_MCAN1_INT_1 (321U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_MCAN0_INT_0 (322U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_MCAN0_INT_1 (323U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_DMU0_INT (324U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_DMU1_INT (325U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_DMU2_INT (326U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_0 (327U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_1 (328U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_2 (329U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_3 (330U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_4 (331U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_5 (332U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_6 (333U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_7 (334U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_8 (335U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_9 (336U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_10 (337U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_11 (338U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_12 (339U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_13 (340U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_14 (341U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP2_INT_ROUTE_15 (342U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_MCAN2_INT_0 (343U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_MCAN2_INT_1 (344U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_MCAN1_INT_0 (345U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_MCAN1_INT_1 (346U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_MCAN0_INT_0 (347U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_MCAN0_INT_1 (348U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_DMU0_INT (349U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_DMU1_INT (350U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_DMU2_INT (351U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_0 (352U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_1 (353U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_2 (354U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_3 (355U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_4 (356U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_5 (357U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_6 (358U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_7 (359U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_8 (360U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_9 (361U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_10 (362U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_11 (363U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_12 (364U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_13 (365U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_14 (366U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MCAN_TOP3_INT_ROUTE_15 (367U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC0_SR_0 (377U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC0_SR_1 (378U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC0_SR_2 (379U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC0_SR_3 (380U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC1_SR_0 (383U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC1_SR_1 (384U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC1_SR_2 (385U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC1_SR_3 (386U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC2_SR_0 (389U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC2_SR_1 (390U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC2_SR_2 (391U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC2_SR_3 (392U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC3_SR_0 (395U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC3_SR_1 (396U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC3_SR_2 (397U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC3_SR_3 (398U)

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC4_SR_0 (413U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC4_SR_1 (414U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC4_SR_2 (415U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC4_SR_3 (416U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC5_SR_0 (417U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC5_SR_1 (418U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC5_SR_2 (419U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC5_SR_3 (420U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC6_SR_0 (421U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC6_SR_1 (422U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC6_SR_2 (423U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC6_SR_3 (424U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC7_SR_0 (381U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC7_SR_1 (382U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC7_SR_2 (387U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC7_SR_3 (388U)
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D) 
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC8_SR_0 (401U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC8_SR_1 (402U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC8_SR_2 (403U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC8_SR_3 (404U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC9_SR_0 (407U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC9_SR_1 (408U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC9_SR_2 (409U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC9_SR_3 (410U)
#endif

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC10_SR_0 (393U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC10_SR_1 (394U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC10_SR_2 (399U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC10_SR_3 (400U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC11_SR_0 (405U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC11_SR_1 (406U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC11_SR_2 (411U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SARADC11_SR_3 (412U)
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined (THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_FC0_INT (425U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_FC1_INT (427U)
#endif

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_FC2_INT (426U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_FC3_INT (428U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MISC_C0_SR_0 (431U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MISC_C0_SR_1 (432U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MISC_C0_SR_2 (433U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MISC_C0_SR_3 (434U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MISC_C1_SR_0 (435U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MISC_C1_SR_1 (436U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MISC_C1_SR_2 (437U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MISC_C1_SR_3 (438U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC0_SRA (439U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC0_SRM (440U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC1_SRA (441U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC1_SRM (442U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC2_SRA (443U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC2_SRM (444U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC3_SRA (445U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC3_SRM (446U)
/* #Violation: intc_hal_h_REF_4 */
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_RDC0_RES_INT_0 (449U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_RDC0_RES_INT_1 (450U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_RDC0_RES_INT_2 (451U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_RDC1_RES_INT_0 (452U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_RDC1_RES_INT_1 (453U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_RDC1_RES_INT_2 (454U)
#endif

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC4_SRA (471U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC4_SRM (472U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC5_SRA (480U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC5_SRM (481U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC6_SRA (489U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC6_SRM (490U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC7_SRA (498U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC7_SRM (499U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC8_SRA (507U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC8_SRM (508U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC9_SRA (516U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_DSADC9_SRM (517U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_TSENSOR0_INT (455U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_TSENSOR1_INT (457U)

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_PSI5_IRQ (459U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ECRC_INT      (463U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI0_TX_INT  (464U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI0_RX_INT  (465U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI0_ERR_INT (466U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI0_PT_INT  (467U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI0_U_INT   (468U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI0_SEF_INT (470U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI1_TX_INT  (473U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI1_RX_INT  (474U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI1_ERR_INT (475U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI1_PT_INT  (476U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI1_U_INT   (477U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI1_SEF_INT (479U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI2_TX_INT  (482U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI2_RX_INT  (483U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI2_ERR_INT (484U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI2_PT_INT  (485U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI2_U_INT   (486U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI2_SEF_INT (488U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI3_TX_INT  (491U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI3_RX_INT  (492U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI3_ERR_INT (493U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI3_PT_INT  (494U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI3_U_INT   (495U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI3_SEF_INT (497U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI4_TX_INT  (500U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI4_RX_INT  (501U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI4_ERR_INT (502U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI4_PT_INT  (503U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI4_U_INT   (504U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI4_SEF_INT (506U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI5_TX_INT  (509U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI5_RX_INT  (510U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI5_ERR_INT (511U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI5_PT_INT  (512U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI5_U_INT   (513U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI5_SEF_INT (515U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI6_TX_INT  (518U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI6_RX_INT  (519U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI6_ERR_INT (520U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI6_PT_INT  (521U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI6_U_INT   (522U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI6_SEF_INT (524U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI7_TX_INT  (527U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI7_RX_INT  (528U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI7_ERR_INT (529U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI7_PT_INT  (530U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI7_U_INT   (531U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI7_SEF_INT (533U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI8_TX_INT  (536U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI8_RX_INT  (537U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI8_ERR_INT (538U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI8_PT_INT  (539U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI8_U_INT   (540U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ESPI8_SEF_INT (542U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC0_SR_0 (552U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC0_SR_1 (553U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC0_SR_2 (554U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC0_SR_3 (555U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC0_SR_4 (556U)
#endif

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC1_SR_0 (557U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC1_SR_1 (558U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC1_SR_2 (559U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC1_SR_3 (560U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC1_SR_4 (561U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC2_SR_0 (562U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC2_SR_1 (563U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC2_SR_2 (564U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC2_SR_3 (565U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_MSC2_SR_4 (566U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT0_RX_ERROR (572U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT0_RX_VALID (573U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT1_RX_ERROR (576U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT1_RX_VALID (577U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT2_RX_ERROR (580U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT2_RX_VALID (581U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT3_RX_ERROR (584U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT3_RX_VALID (585U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT4_RX_ERROR (588U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT4_RX_VALID (589U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT5_RX_ERROR (592U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT5_RX_VALID (593U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT6_RX_ERROR (596U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT6_RX_VALID (597U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT7_RX_ERROR (600U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT7_RX_VALID (601U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT8_RX_ERROR (604U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT8_RX_VALID (605U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT9_RX_ERROR (608U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT9_RX_VALID (609U)
#endif

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT10_RX_ERROR (610U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT10_RX_VALID (611U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT11_RX_ERROR (612U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT11_RX_VALID (613U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT12_RX_ERROR (614U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT12_RX_VALID (615U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT13_RX_ERROR (616U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT13_RX_VALID (617U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT14_RX_ERROR (618U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT14_RX_VALID (619U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT15_RX_ERROR (620U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT15_RX_VALID (621U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT16_RX_ERROR (574U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT16_RX_VALID (575U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT17_RX_ERROR (578U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT17_RX_VALID (579U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT18_RX_ERROR (582U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT18_RX_VALID (583U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT19_RX_ERROR (586U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT19_RX_VALID (587U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT20_RX_ERROR (590U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT20_RX_VALID (591U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT21_RX_ERROR (594U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT21_RX_VALID (595U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT22_RX_ERROR (598U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT22_RX_VALID (599U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT23_RX_ERROR (602U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT23_RX_VALID (603U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT24_RX_ERROR (606U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_SENT24_RX_VALID (607U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_I2C0_IT_ERROR (622U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_I2C0_IT_EVENT (623U)

#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_I2C1_IT_ERROR (624U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_I2C1_IT_EVENT (625U)
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_QSPI_INT (630U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI0_IPI_INT_RX  (631U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI0_IPI_INT_TX  (632U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI0_IPI_INT_ERR (633U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI0_IPI_INT_ALL (634U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI1_IPI_INT_RX  (636U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI1_IPI_INT_TX  (637U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI1_IPI_INT_ERR (638U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI1_IPI_INT_ALL (639U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI2_IPI_INT_RX  (641U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI2_IPI_INT_TX  (642U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI2_IPI_INT_ERR (643U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI2_IPI_INT_ALL (644U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI3_IPI_INT_RX  (646U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI3_IPI_INT_TX  (647U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI3_IPI_INT_ERR (648U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI3_IPI_INT_ALL (649U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI4_IPI_INT_RX  (651U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI4_IPI_INT_TX  (652U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI4_IPI_INT_ERR (653U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI4_IPI_INT_ALL (654U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI5_IPI_INT_RX  (656U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI5_IPI_INT_TX  (657U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI5_IPI_INT_ERR (658U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI5_IPI_INT_ALL (659U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI6_IPI_INT_RX  (661U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI6_IPI_INT_TX  (662U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI6_IPI_INT_ERR (663U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI6_IPI_INT_ALL (664U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI7_IPI_INT_RX  (666U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI7_IPI_INT_TX  (667U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI7_IPI_INT_ERR (668U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI7_IPI_INT_ALL (669U)

#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI8_IPI_INT_RX  (109U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI8_IPI_INT_TX  (110U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI8_IPI_INT_ERR (111U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI8_IPI_INT_ALL (112U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI9_IPI_INT_RX  (113U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI9_IPI_INT_TX  (114U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI9_IPI_INT_ERR (143U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI9_IPI_INT_ALL (144U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI10_IPI_INT_RX  (145U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI10_IPI_INT_TX  (146U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI10_IPI_INT_ERR (147U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI10_IPI_INT_ALL (148U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI11_IPI_INT_RX  (242U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI11_IPI_INT_TX  (243U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI11_IPI_INT_ERR (244U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI11_IPI_INT_ALL (245U)
#endif

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI12_IPI_INT_RX  (289U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI12_IPI_INT_TX  (290U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI12_IPI_INT_ERR (291U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI12_IPI_INT_ALL (292U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI13_IPI_INT_RX  (368U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI13_IPI_INT_TX  (369U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI13_IPI_INT_ERR (370U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI13_IPI_INT_ALL (371U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI14_IPI_INT_RX  (372U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI14_IPI_INT_TX  (373U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI14_IPI_INT_ERR (374U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI14_IPI_INT_ALL (375U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI15_IPI_INT_RX  (429U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI15_IPI_INT_TX  (430U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI15_IPI_INT_ERR (655U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI15_IPI_INT_ALL (660U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI16_IPI_INT_RX  (447U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI16_IPI_INT_TX  (448U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI16_IPI_INT_ERR (449U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI16_IPI_INT_ALL (450U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI17_IPI_INT_RX  (451U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI17_IPI_INT_TX  (452U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI17_IPI_INT_ERR (453U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI17_IPI_INT_ALL (454U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI18_IPI_INT_RX  (543U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI18_IPI_INT_TX  (544U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI18_IPI_INT_ERR (545U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI18_IPI_INT_ALL (546U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI19_IPI_INT_RX  (547U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI19_IPI_INT_TX  (548U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI19_IPI_INT_ERR (549U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI19_IPI_INT_ALL (550U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI20_IPI_INT_RX  (567U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI20_IPI_INT_TX  (568U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI20_IPI_INT_ERR (569U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI20_IPI_INT_ALL (570U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI21_IPI_INT_RX  (626U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI21_IPI_INT_TX  (627U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI21_IPI_INT_ERR (628U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI21_IPI_INT_ALL (629U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI22_IPI_INT_RX  (679U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI22_IPI_INT_TX  (680U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI22_IPI_INT_ERR (681U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI22_IPI_INT_ALL (682U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI23_IPI_INT_RX  (683U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI23_IPI_INT_TX  (684U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI23_IPI_INT_ERR (685U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_ASI23_IPI_INT_ALL (686U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_EXTI_IOUT0 (671U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_EXTI_IOUT1 (672U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_EXTI_IOUT2 (673U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_EXTI_IOUT3 (674U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_EXTI_IOUT4 (675U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_EXTI_IOUT5 (676U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_EXTI_IOUT6 (677U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_EXTI_IOUT7 (678U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS5_IRQ_5 (66U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS5_IRQ_6 (67U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS5_IRQ_7 (82U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS6_IRQ_0 (83U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS6_IRQ_1 (84U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS6_IRQ_2 (85U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS6_IRQ_3 (86U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS6_IRQ_4 (87U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS6_IRQ_5 (88U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS6_IRQ_6 (233U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS6_IRQ_7 (241U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS7_IRQ_0 (376U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS7_IRQ_1 (456U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS7_IRQ_2 (458U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS7_IRQ_3 (525U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS7_IRQ_4 (526U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS7_IRQ_5 (534U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS7_IRQ_6 (535U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS7_IRQ_7 (551U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS4_S_IRQ (571U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS5_S_IRQ (635U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS6_S_IRQ (640U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS7_S_IRQ (645U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCSW_ORED_INT (650U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ERR_IRQ (687U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_CMP_IRQ (688U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_AEI_IRQ (689U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ARU_IRQ_0 (690U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ARU_IRQ_1 (691U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ARU_IRQ_2 (692U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_BRC_IRQ   (693U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_SPE_IRQ_0 (694U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_SPE_IRQ_1 (695U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_SPE_IRQ_2 (696U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM0_IRQ_0 (697U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM0_IRQ_1 (698U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM0_IRQ_2 (699U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM0_IRQ_3 (700U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM0_IRQ_4 (701U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM0_IRQ_5 (702U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM0_IRQ_6 (703U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM0_IRQ_7 (704U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM1_IRQ_0 (705U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM1_IRQ_1 (706U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM1_IRQ_2 (707U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM1_IRQ_3 (708U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM1_IRQ_4 (709U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM1_IRQ_5 (710U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM1_IRQ_6 (711U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM1_IRQ_7 (712U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM2_IRQ_0 (713U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM2_IRQ_1 (714U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM2_IRQ_2 (715U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM2_IRQ_3 (716U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM2_IRQ_4 (717U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM2_IRQ_5 (718U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM2_IRQ_6 (719U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_PSM2_IRQ_7 (720U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_0 (721U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_1 (722U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_2 (723U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_3 (724U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_4 (725U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_5 (726U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_6 (727U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_7 (728U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_8 (729U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_9 (730U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_10 (731U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_11 (732U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_12 (733U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_13 (734U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_14 (735U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_15 (736U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_16 (737U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_17 (738U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_18 (739U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_19 (740U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_20 (741U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_21 (742U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_22 (743U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_23 (744U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_24 (745U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_25 (746U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_DPLL_IRQ_26 (747U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM0_IRQ_0 (748U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM0_IRQ_1 (749U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM0_IRQ_2 (750U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM0_IRQ_3 (751U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM0_IRQ_4 (752U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM0_IRQ_5 (753U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM0_IRQ_6 (754U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM0_IRQ_7 (755U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM1_IRQ_0 (756U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM1_IRQ_1 (757U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM1_IRQ_2 (758U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM1_IRQ_3 (759U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM1_IRQ_4 (760U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM1_IRQ_5 (761U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM1_IRQ_6 (762U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM1_IRQ_7 (763U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM2_IRQ_0 (764U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM2_IRQ_1 (765U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM2_IRQ_2 (766U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM2_IRQ_3 (767U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM2_IRQ_4 (768U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM2_IRQ_5 (769U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM2_IRQ_6 (770U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM2_IRQ_7 (771U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM0_IRQ_0 (772U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM0_IRQ_1 (773U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM0_IRQ_2 (774U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM0_IRQ_3 (775U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM0_IRQ_4 (776U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM0_IRQ_5 (777U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM0_IRQ_6 (778U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM0_IRQ_7 (779U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM1_IRQ_0 (780U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM1_IRQ_1 (781U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM1_IRQ_2 (782U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM1_IRQ_3 (783U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM1_IRQ_4 (784U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM1_IRQ_5 (785U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM1_IRQ_6 (786U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM1_IRQ_7 (787U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM2_IRQ_0 (788U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM2_IRQ_1 (789U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM2_IRQ_2 (790U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM2_IRQ_3 (791U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM2_IRQ_4 (792U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM2_IRQ_5 (793U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM2_IRQ_6 (794U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM2_IRQ_7 (795U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM0_IRQ_0 (796U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM0_IRQ_1 (797U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM0_IRQ_2 (798U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM0_IRQ_3 (799U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM1_IRQ_0 (800U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM1_IRQ_1 (801U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM1_IRQ_2 (802U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM1_IRQ_3 (803U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM2_IRQ_0 (804U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM2_IRQ_1 (805U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM2_IRQ_2 (806U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM2_IRQ_3 (807U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM3_IRQ_0 (808U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM3_IRQ_1 (809U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM3_IRQ_2 (810U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM3_IRQ_3 (811U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO1_IRQ_0 (812U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO1_IRQ_1 (813U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO1_IRQ_2 (814U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO1_IRQ_3 (815U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO1_IRQ_4 (816U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO1_IRQ_5 (817U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO1_IRQ_6 (818U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO1_IRQ_7 (819U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO2_IRQ_0 (820U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO2_IRQ_1 (821U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO2_IRQ_2 (822U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO2_IRQ_3 (823U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO2_IRQ_4 (824U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO2_IRQ_5 (825U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO2_IRQ_6 (826U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO2_IRQ_7 (827U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO3_IRQ_0 (828U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO3_IRQ_1 (829U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO3_IRQ_2 (830U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO3_IRQ_3 (831U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO3_IRQ_4 (832U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO3_IRQ_5 (833U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO3_IRQ_6 (834U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO3_IRQ_7 (835U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_IRQ_0 (836U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_IRQ_1 (837U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_IRQ_2 (838U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_IRQ_3 (839U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_IRQ_4 (840U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_IRQ_5 (841U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_IRQ_6 (842U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_IRQ_7 (843U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_IRQ_0 (844U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_IRQ_1 (845U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_IRQ_2 (846U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_IRQ_3 (847U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_IRQ_4 (848U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_IRQ_5 (849U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_IRQ_6 (850U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_IRQ_7 (851U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_IRQ_0 (852U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_IRQ_1 (853U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_IRQ_2 (854U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_IRQ_3 (855U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_IRQ_4 (856U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_IRQ_5 (857U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_IRQ_6 (858U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_IRQ_7 (859U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_IRQ_0 (860U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_IRQ_1 (861U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_IRQ_2 (862U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_IRQ_3 (863U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_IRQ_4 (864U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_IRQ_5 (865U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_IRQ_6 (866U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_IRQ_7 (867U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_S_IRQ_0 (868U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_S_IRQ_1 (869U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_S_IRQ_2 (870U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_S_IRQ_3 (871U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_S_IRQ_4 (872U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_S_IRQ_5 (873U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_S_IRQ_6 (874U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS0_S_IRQ_7 (875U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_S_IRQ_0 (876U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_S_IRQ_1 (877U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_S_IRQ_2 (878U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_S_IRQ_3 (879U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_S_IRQ_4 (880U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_S_IRQ_5 (881U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_S_IRQ_6 (882U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS1_S_IRQ_7 (883U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_S_IRQ_0 (884U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_S_IRQ_1 (885U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_S_IRQ_2 (886U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_S_IRQ_3 (887U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_S_IRQ_4 (888U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_S_IRQ_5 (889U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_S_IRQ_6 (890U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS2_S_IRQ_7 (891U)

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_S_IRQ_0 (892U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_S_IRQ_1 (893U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_S_IRQ_2 (894U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_S_IRQ_3 (895U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_S_IRQ_4 (896U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_S_IRQ_5 (897U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_S_IRQ_6 (898U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS3_S_IRQ_7 (899U)
#endif

/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCSW_INT_0 (900U)

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCSW_INT_1 (901U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCSW_INT_2 (902U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCSW_INT_3 (903U)
#endif

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_SPE3_IRQ   (904U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */    
#define INTC_INTID_GTM_TIM3_IRQ_0 (905U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM3_IRQ_1 (906U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM3_IRQ_2 (907U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM3_IRQ_3 (908U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM3_IRQ_4 (909U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM3_IRQ_5 (910U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM3_IRQ_6 (911U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM3_IRQ_7 (912U)

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM4_IRQ_0 (913U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM4_IRQ_1 (914U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM4_IRQ_2 (915U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM4_IRQ_3 (916U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM4_IRQ_4 (917U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM4_IRQ_5 (918U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM4_IRQ_6 (919U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM4_IRQ_7 (920U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM5_IRQ_0 (921U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM5_IRQ_1 (922U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM5_IRQ_2 (923U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM5_IRQ_3 (924U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM5_IRQ_4 (925U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM5_IRQ_5 (926U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM5_IRQ_6 (927U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM5_IRQ_7 (928U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM6_IRQ_0 (929U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM6_IRQ_1 (930U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM6_IRQ_2 (931U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM6_IRQ_3 (932U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM6_IRQ_4 (933U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM6_IRQ_5 (934U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM6_IRQ_6 (935U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM6_IRQ_7 (936U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM7_IRQ_0 (937U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM7_IRQ_1 (938U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM7_IRQ_2 (939U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM7_IRQ_3 (940U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM7_IRQ_4 (941U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM7_IRQ_5 (942U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM7_IRQ_6 (943U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIM7_IRQ_7 (944U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM3_IRQ_0 (945U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM3_IRQ_1 (946U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM3_IRQ_2 (947U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM3_IRQ_3 (948U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM3_IRQ_4 (949U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM3_IRQ_5 (950U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM3_IRQ_6 (951U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM3_IRQ_7 (952U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM4_IRQ_0 (953U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM4_IRQ_1 (954U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM4_IRQ_2 (955U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM4_IRQ_3 (956U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM4_IRQ_4 (957U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM4_IRQ_5 (958U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM4_IRQ_6 (959U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TOM4_IRQ_7 (960U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM4_IRQ_0 (961U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM4_IRQ_1 (962U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM4_IRQ_2 (963U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM4_IRQ_3 (964U)

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM5_IRQ_0 (965U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM5_IRQ_1 (966U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM5_IRQ_2 (967U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM5_IRQ_3 (968U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM6_IRQ_0 (969U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM6_IRQ_1 (970U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM6_IRQ_2 (971U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM6_IRQ_3 (972U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM7_IRQ_0 (973U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM7_IRQ_1 (974U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM7_IRQ_2 (975U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_ATOM7_IRQ_3 (976U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO4_G_IRQ  (977U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_TIO5_G_IRQ  (978U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS4_IRQ_0  (979U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS4_IRQ_1  (980U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS4_IRQ_2  (981U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS4_IRQ_3  (982U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS4_IRQ_4  (983U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS4_IRQ_5  (984U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS4_IRQ_6  (985U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS4_IRQ_7  (986U) 

/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS5_IRQ_0  (987U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS5_IRQ_1  (988U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS5_IRQ_2  (989U)
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS5_IRQ_3  (990U) 
/* THA6412 only */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_MCS5_IRQ_4  (991U) 

/* INTC alarm status */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN0_REDUNDANCY   (0x1U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN1_REDUNDANCY   (0x2U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN2_REDUNDANCY   (0x4U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN3_REDUNDANCY   (0x8U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN4_REDUNDANCY   (0x10U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN5_REDUNDANCY   (0x20U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN6_REDUNDANCY   (0x40U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN7_REDUNDANCY   (0x80U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT0_REDUNDANCY  (0x100U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT1_REDUNDANCY  (0x200U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT2_REDUNDANCY  (0x400U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT3_REDUNDANCY  (0x800U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT4_REDUNDANCY  (0x1000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT5_REDUNDANCY  (0x2000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT6_REDUNDANCY  (0x4000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT7_REDUNDANCY  (0x8000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SETINTEN_REDUNDANCY  (0x10000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SE_ILLEGAL_ACCESS    (0x20000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF0_REDUNDANCY     (0x40000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF1_REDUNDANCY     (0x80000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF2_REDUNDANCY     (0x100000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF3_REDUNDANCY     (0x200000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF4_REDUNDANCY     (0x400000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF5_REDUNDANCY     (0x800000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF6_REDUNDANCY     (0x1000000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF7_REDUNDANCY     (0x2000000U)

#if defined(THA6_THA6412)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN8_REDUNDANCY    (0x1U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN9_REDUNDANCY    (0x2U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN10_REDUNDANCY   (0x4U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN11_REDUNDANCY   (0x8U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN12_REDUNDANCY   (0x10U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN13_REDUNDANCY   (0x20U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN14_REDUNDANCY   (0x40U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMFEN15_REDUNDANCY   (0x80U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT8_REDUNDANCY   (0x100U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT9_REDUNDANCY   (0x200U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT10_REDUNDANCY  (0x400U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT11_REDUNDANCY  (0x800U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT12_REDUNDANCY  (0x1000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT13_REDUNDANCY  (0x2000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT14_REDUNDANCY  (0x4000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SOFTINT15_REDUNDANCY  (0x8000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF8_REDUNDANCY      (0x40000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF9_REDUNDANCY      (0x80000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF10_REDUNDANCY     (0x100000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF11_REDUNDANCY     (0x200000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF12_REDUNDANCY     (0x400000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF13_REDUNDANCY     (0x800000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF14_REDUNDANCY     (0x1000000U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SEMF15_REDUNDANCY     (0x2000000U)
#endif

/* INTC alarm clear types */
/* Clear the redundant alarm status bits of SEMFENx Register */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_CLEAR_SEMFEN_SEMF      (0x1U)
/* Clear the redundant alarm status bits of SOFTINTx Register */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_CLEAR_SOFTINT          (0x2U)
/* Clear the redundant alarm status bits of SETINTEN Register */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_CLEAR_SETINTEN          (0x4U)
/* Clear the alarm status caused by illegal access to SE protected Registers */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_CLEAR_SE_ILLEGAL_ACCESS (0x8U)

/* INTC alarm set types */
/* Enable SEMFEN and SEMF redundant alarm */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SET_SEMFEN_SEMF      (0x1U)
/* Enable SOFTINT redundant alarm */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SET_SOFTINT          (0x2U)
/* Enable SETINTEN redundant alarm */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_ALARM_SET_SETINTEN         (0x4U)

/* GTM INTC ID LEVEDGSEL9 and LEVEDGSEL10 register */
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_LEVEDGSEL9_0     (0xFU)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_LEVEDGSEL9_1     (0x2U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_LEVEDGSEL10_0    (0x9U)
/* #Violation: intc_hal_h_REF_4 */
#define INTC_INTID_GTM_LEVEDGSEL10_1    (0x2U)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Type Definitions
 *********************************************************************************************************************/
typedef uint16 Intc_IntID;
typedef uint8 Intc_InterruptGroup;
typedef uint8 Intc_TriggerMethod;
/* defined interrupt routine prototype.*/
typedef void (*IntHandler)(void);

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* INTC Error flag */
typedef enum
{
    INTC_ERRORFLAG_SUCCESS = 0U, /* The operation is success */
    INTC_ERRORFLAG_FAILURE,      /* The operation is Failure */
    INTC_ERRORFLAG_SET_HANDLER_FAIL, /* Process handling failed. */
    INTC_ERRORFLAG_REPEAT, /* Repeat operation */
    INTC_ERRORFLAG_ATOMIC_BUSY /* The atomic lock is being occupied */
} Intc_ErrorFlag;

/* Define interrupt target core */
typedef enum
{
    INTC_TARGET_CORE0 = 0U,  /* Interrupt target core0 */
    INTC_TARGET_CORE1,       /* Interrupt target core1, it is active in THA6206 and THA6412, reserved in THA6104 */
    INTC_TARGET_CORE2,       /* Interrupt target core2, it is active in THA6412, reserved in THA6104 and THA6206 */
    INTC_TARGET_CORE3,       /* Interrupt target core3, it is active in THA6412, reserved in THA6104 and THA6206 */
    INTC_TARGET_CORE0_CORE1, /* Interrupt target core0 and core1, it is active in THA6206 and THA6412, reserved in THA6104 */
    INTC_TARGET_CORE2_CORE3  /* Interrupt target core2 and core3, it is active in THA6412, reserved in THA6104 and THA6206 */
} Intc_TargetCore;


/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Initialization configuration structure for interrupt */
/* #Violation: intc_hal_h_REF_3 */
/* #Violation: intc_hal_h_REF_6 */
typedef struct
{
    uint8 priority;                   /* Priority of interrupt */
    Intc_InterruptGroup group;        /* Group of interrupt, FIQ or IRQ */
    Intc_TriggerMethod triggerMethod; /* Trigger method, level or edge */
    boolean enable;                   /* Enable interrupt */
    Intc_IntID intID;                 /* Interrupt ID */
    IntHandler handler;               /* Interrupt handler */
} Intc_InterruptConfig;

#define INTC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Intc_MemMap.h"
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
 /**********************************************************************************************************************
 * Function:     Intc_Register_ReadBack_Check
 * Description:  Register read back check
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        state: Original state
 *               expect: The value expected to be written
 *               value: The value actually written
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/03/10    01369     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Intc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);

/**********************************************************************************************************************
 * Function:     Intc_Hal_SetPriorityMask
 * Description:  Set the CPU interface priority mask value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        priorityThreshold: Priority threshold. Interrupts whose priority is less than or equal to the
 *                                           threshold are masked.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/05/15    01200      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Intc_Hal_SetPriorityMask(uint32 priorityThreshold);

/**********************************************************************************************************************
 * Function:     Intc_Hal_GetPriorityMask
 * Description:  Get the CPU interface priority mask value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       pCurPriorityMask: Variable to get the current priority mask value
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/05/15    01200      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Intc_Hal_GetPriorityMask(uint32* pCurPriorityMask);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
 #define INTC_REG_CHECK
#if defined(INTC_REG_CHECK)
LOCAL_FORCEINLINE boolean Intc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret = FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Intc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/* #Violation: intc_hal_h_REF_2 */
 LOCAL_FORCEINLINE void Intc_Hal_SetPriorityMask(uint32 priorityThreshold)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the priority mask is in the normal range */
    /* #Violation: intc_hal_h_REF_5 */
    Assert((boolean)(priorityThreshold <= INTC_MAX_PRIORITY));
#endif /* INPUT_ARG_DETECT */
    
    /* Set priority mask: MCR p15,0,<Rt>,c4,c6,0.Writes the value of priorityThreshold to the corresponding system
       control register ICC_PMR of <Coprocessor 15, 0, c4, c6, 0> */
    /* Set priority mask */
    /* #Violation: intc_hal_h_REF_1 */
    SET_CP(15, 0, priorityThreshold << 3U, 4, 6, 0);
}

/* #Violation: intc_hal_h_REF_2 */
LOCAL_FORCEINLINE void Intc_Hal_GetPriorityMask(uint32* pCurPriorityMask)
{
    uint32 priorityMask;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check pointer */
    /* #Violation: intc_hal_h_REF_5 */
    Assert((boolean)(NULL_PTR != pCurPriorityMask));
#endif /* INPUT_ARG_DETECT */

    /* Get priority mask: MRC p15,0,<Rt>,c4,c6,0.Read the value of the corresponding system control register ICC_PMR
       of <Coprocessor 15, 0, c4, c6, 0> */
    /* Get priority mask */   
    /* #Violation: intc_hal_h_REF_1 */
    GET_CP(15, 0, priorityMask, 4, 6, 0);
    *pCurPriorityMask = priorityMask >> 3U;
}
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Intc_Hal_InstallInterrupt
 * Description:  Initialize INTC and install interrupt.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pIntList: Interrupt configuration structure array
 *               intSum: The number of interrupts to install
 *               pIntTblBaseAddr: Interrupt table base address
 * Inout:        None
 * Output:       None
 * Return:       Intc_ErrorFlag: Error indicating flag
 * Others:       If this API need to install software interrupt. It is recommended that users use the locking mechanism to protect this API.
 * History:
 *  Date          Author    Modified
 *  2023/05/15    01200      Create
 *********************************************************************************************************************/
extern Intc_ErrorFlag Intc_Hal_InstallInterrupt(const Intc_InterruptConfig *const pIntList, uint32 intSum, IntHandler* pIntTblBaseAddr);

/**********************************************************************************************************************
 * Function:     Intc_Hal_EnableInterrupt
 * Description:  Enable an interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intID: The INTID of interrupt
 * Inout:        None
 * Output:       None
 * Return:       Intc_ErrorFlag: Error indicating flag
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/05/15    01200      Create
 *  2023/06/06    01200      Change return value from void to Intc_ErrorFlag
 *********************************************************************************************************************/
extern Intc_ErrorFlag Intc_Hal_EnableInterrupt(Intc_IntID intID);

/**********************************************************************************************************************
 * Function:     Intc_Hal_DisableInterrupt
 * Description:  Disable an interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intID: The INTID of interrupt
 * Inout:        None
 * Output:       None
 * Return:       Intc_ErrorFlag: Error indicating flag
 * Others:       This function only used in the Master core
 * History:
 *  Date          Author    Modified
 *  2023/05/15    01200      Create
 *  2023/06/06    01200      Change return value from void to Intc_ErrorFlag
 *********************************************************************************************************************/
extern Intc_ErrorFlag Intc_Hal_DisableInterrupt(Intc_IntID intID);

/**********************************************************************************************************************
 * Function:     Intc_Hal_SetMinGroupPriority
 * Description:  Set the min group priority of FIQ and IRQ
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        fiqGroupMinPriority: FIQ min group priority: 31, 15, 7, 3, 1, 0;
 *                                    Corresponding min subpriority: 0, 1, 3, 7, 15, 31;
 *               irqGroupMinPriority: IRQ min group priority: 31, 15, 7, 3, 1;
 *                                    Corresponding min subpriority: 0, 1, 3, 7, 15;
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/11    01200      Create
 *********************************************************************************************************************/
extern void Intc_Hal_SetMinGroupPriority(uint32 fiqGroupMinPriority, uint32 irqGroupMinPriority);

/**********************************************************************************************************************
 * Function:     Intc_Hal_GenerateSoftwareInterrupt
 * Description:  Generate a Cluster Software Interrupt from a core to the target core(s)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intID: The INTID of interrupt
 *               targetCore: The target core(s) of the software interrupt.
 * Inout:        None
 * Output:       None
 * Return:       Intc_ErrorFlag: Error indicating flag
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/05/15    01200      Create
 *********************************************************************************************************************/
extern Intc_ErrorFlag Intc_Hal_GenerateSoftwareInterrupt(Intc_IntID intID, Intc_TargetCore targetCore);

/**********************************************************************************************************************
 * Function:     Intc_Hal_ClearSpiSoftwareInterrupt
 * Description:  Clear SPI Software Interrupt after interrupt handler finish.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intID: The INTID of interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/05/15    01200      Create
 *********************************************************************************************************************/
extern boolean Intc_Hal_ClearSpiSoftwareInterrupt(Intc_IntID intID);

/**********************************************************************************************************************
 * Function:     Intc_Hal_GetAlarmStatus
 * Description:  Get the status of alarm in INTC module
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        index: Alarm index to be checked. 0-can get the SEMF0~7, SETINTEN, SOFTINT0~7 and SEMFEN0~7 multibit
 *                                                  redundancy alarm and SE status.
 *                                                 1-can get the SEMF8~15,  SOFTINT8~15 and SEMFEN8~15 multibit
 *                                                  redundancy alarm status.
 * Inout:        None
 * Output:       None
 * Return:       uint32: Alarm status.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01200      Create
 *********************************************************************************************************************/
extern uint32 Intc_Hal_GetAlarmStatus(uint32 index);

/**********************************************************************************************************************
 * Function:     Intc_Hal_ClearAlarmStatus
 * Description:  Clear the status of alarm in INTC module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        alarmClear: Alarm(s) to be cleared, the arange value are [0, 0xF]
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/19    01200      Create
 *********************************************************************************************************************/
extern boolean Intc_Hal_ClearAlarmStatus(uint32 alarmClear);

/**********************************************************************************************************************
 * Function:     Intc_Hal_SetAlarmStatus
 * Description:  Set alarm in INTC module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        alarm: Alarm(s) to be set, the rang value are [0, 0x7].
 * Inout:        None
 * Output:       None
 * Return:       boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/08/11    01200      Create
 *********************************************************************************************************************/
extern boolean Intc_Hal_SetAlarmStatus(uint32 alarm);


#define INTC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Intc_MemMap.h"

#endif /* INTC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

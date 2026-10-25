/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    tha6412_cfg.h
 * Author:      00930
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains 6412 Chip module number and module base address definition, resource-related macro
 *              definition, etc
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #tha6412_cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: Reserved macros for upper layer application.
*
* #tha6412_cfg_h_REF_2:MISRAC2012-Dir-4.9; 
* Justification: Function like macro are used to reduce code complexity.
*/
#ifndef THA6412_CFG_H_
#define THA6412_CFG_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* INTC */
/* The largest number of GIC modules on the chip */
/* #Violation: tha6412_cfg_h_REF_1 */
#define MAX_GIC_NUM (2U)

/* INTC module base address define */
#define INTC_BASE_ADDR (0xB0040000U)
#define GIC0_BASE_ADDR  (0xF0000000U)
#define GIC1_BASE_ADDR  (0xF0200000U)

/* INTC GTM MAX ID*/
/* #Violation: tha6412_cfg_h_REF_1 */
#define INTC_INTID_GTM_MAXID (991U)

/* MAX CORE ID */
/* #Violation: tha6412_cfg_h_REF_1 */
#define INTC_CORE_MAXID (3U) 

/* Check Soft INTID */
/* #Violation: tha6412_cfg_h_REF_1 */
#define INTC_CHECK_SPISOFT_INTID(intID) ((((intID <= INTC_INTID_SOFT_INT_CORE0_3) && \
                                          (intID >= INTC_INTID_SOFT_INT_CORE0_0))|| \
                                          ((intID <= INTC_INTID_SOFT_INT_CORE1_3) && \
                                          (intID >= INTC_INTID_SOFT_INT_CORE1_0))) ? 1U : 0U)

/* INTC Object define */
#define INTC_HAL ((INTC_MODULE *)INTC_BASE_ADDR)
/* GIC Object */
#define GIC0 ((INTC_GIC_MODULE *)GIC0_BASE_ADDR)
#define GIC1 ((INTC_GIC_MODULE *)GIC1_BASE_ADDR)

/* SAC */
/* SAC module base address define */
#define SAC_BASE_ADDRESS (0xC0040400U)
#define SAC_STDBY_BASE_ADDRESS (0xD0060C00U)

/* SAC Object define */
#define SAC ((SAC_MODULE *)SAC_BASE_ADDRESS)
#define SAC_STDBY ((SAC_STDBY_MODULE *)SAC_STDBY_BASE_ADDRESS)

/* Check SAC reserved group */
/* #Violation: tha6412_cfg_h_REF_1 */
#define SAC_RESERVED_GROUP_CHECK(alarmGroup)  (((uint32)(alarmGroup) < 22U) ? 1U : 0U)

/* SAC bit filed "NIMSEL" num */
/* #Violation: tha6412_cfg_h_REF_1 */
#define SAC_NMISEL_BITNUM   (15U)

/* ITMUINIT */
/* Base address of ITMUINIT module for LLPP */
/* #Violation: tha6412_cfg_h_REF_1 */
#define ITMUINIT_BASE_ADDRESS (0xB0330C00U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define ITMUINIT ((ITMUINIT_MODULE *)ITMUINIT_BASE_ADDRESS)

/* RCC */
/* RCC module base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_BASE_ADDR 0xC0000000U
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_CLOCK_OFFSET_ADDR 0x10U
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_RESET_OFFSET_ADDR 0x0800U
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_STB_BASE_ADDR 0xD0060400U
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_STBRESET_OFFSET_ADDR 0x0200U

/* RCC Object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_CLOCK ((RCC_CLOCK_MODULE *)(RCC_BASE_ADDR + RCC_CLOCK_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_RESET ((RCC_RESET_MODULE *)(RCC_BASE_ADDR + RCC_RESET_OFFSET_ADDR))
/* RCC STB Object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_STBCLOCK ((RCC_STBCLOCK_MODULE *)RCC_STB_BASE_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_STBRESET ((RCC_STBRESET_MODULE *)(RCC_STB_BASE_ADDR + RCC_STBRESET_OFFSET_ADDR))

/* RCC_CLK_SOURCE_HSE indicates HSE clock frequency */
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_CLK_SOURCE_HSE (20000000U)
/* RCC_CLK_SOURCE_HSI indicates HSI clock frequency */
/* #Violation: tha6412_cfg_h_REF_1 */
#define RCC_CLK_SOURCE_HSI (100000000U)

/* BUSPROT */
/* #Violation: tha6412_cfg_h_REF_1 */
#define BUSPROT_BASE_ADDRESS (0xC0000000U) /* Base address of BUSPROT module */

/* ECRC */
#define ECRC_BASE_ADDR (0xC0140000U)    /* ECRC module base address */
/* ECRC Object */
#define ECRC ((ECRC_MODULE *)ECRC_BASE_ADDR)

/* PWRC */
#define PWRC_BASE_ADDRESS (0xC0004000U) /* Base address of PWRC module */
#define PWRCSTBY_BASE_ADDRESS (0xD0060000U) /* Base address of PWRCSTBY module */
/* PWRC and PWRCSTB Object */
#define PWRC ((PWRC_MODULE *)PWRC_BASE_ADDRESS)
#define PWRCSTB ((PWRCSTB_MODULE *)PWRCSTBY_BASE_ADDRESS)

/* ETH */
/* ETH module base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define ETH_BASE_ADDR (0xC00BC000U)
/* ETH Object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define ETH ((ETH_MODULE *)ETH_BASE_ADDR)
/* Check support interface mode */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_ETH_PHY_INTERFACE_MODE(mode)(((ETH_PHY_INTERFACE_MII == (mode)) || (ETH_PHY_INTERFACE_RMII == (mode)) || \
                                            (ETH_PHY_INTERFACE_RGMII == (mode))) ? (1U) : (0U))
/* Check support line speed */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_ETH_LINE_SPEED(speed)(((ETH_LINESPEED_10M == (speed)) || (ETH_LINESPEED_100M == (speed)) || \
                                     (ETH_LINESPEED_1000M == (speed))) ? (1U) : (0U))
/* Check ETH channel number */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_ETH_CHANNEL(channelID) (((uint32)(channelID) < 4U) ? 1U : 0U)
/* Check the number of ETH Tx\Rx channels */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_ETH_NUMCH(numchannels) (((uint32)(numchannels) <= 4U) ? 1U : 0U)
/* Check ETH Tx DMA channel\Queue ID */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_ETH_TX_DMACH_QUEUE_ID(channelID) (((uint32)(channelID) < 4U) ? 1U : 0U)

/*BASETIMER module base address*/
/* #Violation: tha6412_cfg_h_REF_1 */
#define DUALTIMER0_BASE_ADDRESS (0xD0070000UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define DUALTIMER1_BASE_ADDRESS (0xD0098000UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define DUALTIMER2_BASE_ADDRESS (0xD00b8000UL)

/* basetimer0 object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define BASETIMER0 ((BASETIMER_MODULE *)DUALTIMER0_BASE_ADDRESS)
/* basetimer1 object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define BASETIMER1 ((BASETIMER_MODULE *)(DUALTIMER0_BASE_ADDRESS + 0x20U))
/* basetimer2 object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define BASETIMER2 ((BASETIMER_MODULE *)DUALTIMER1_BASE_ADDRESS)
/* basetimer3 object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define BASETIMER3 ((BASETIMER_MODULE *)(DUALTIMER1_BASE_ADDRESS + 0x20U))
/* basetimer4 object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define BASETIMER4 ((BASETIMER_MODULE *)DUALTIMER2_BASE_ADDRESS)
/* basetimer5 object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define BASETIMER5 ((BASETIMER_MODULE *)(DUALTIMER2_BASE_ADDRESS + 0x20U))
/* Check BASETIMER base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_BASETIMER_BASE(pTimer)                                                                                      \
(((pTimer) == BASETIMER0) ? (1U) : (((pTimer) == BASETIMER1) ? (1U) : (((pTimer) == BASETIMER2) ? (1U) :            \
(((pTimer) == BASETIMER3) ? (1U) : (((pTimer) == BASETIMER4) ? (1U) : (((pTimer) == BASETIMER5) ? (1U) : (0U)))))))


#define     STM_BASE_ADDRESS    (0xC0060800U)
#define     STM0             ((STM_MODULE *) STM_BASE_ADDRESS)

/* #Violation: tha6412_cfg_h_REF_1 */
#define RDC0_BASE_ADDR (0xB0003804UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define RDC1_BASE_ADDR (0xB0013804UL)

/* #Violation: tha6412_cfg_h_REF_1 */
#define RDC0 ((RDC_MODULE *)RDC0_BASE_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define RDC1 ((RDC_MODULE *)RDC1_BASE_ADDR)

/* Check RDC base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_RDC_BASE(pRdc) (((pRdc) == RDC0) ? (1U) : (((pRdc) == RDC1) ? (1U) : (0U)))

/*SARADC Base Address*/
#define SARADC_BASE_ADDRESS0 (0xB0000000U)
#define SARADC0 ((SARADC_MODULE *)SARADC_BASE_ADDRESS0)

#define SARADC_BASE_ADDRESS1 (0xB0000400U)
#define SARADC1 ((SARADC_MODULE *)SARADC_BASE_ADDRESS1)

#define SARADC_BASE_ADDRESS2 (0xB0000800U)
#define SARADC2 ((SARADC_MODULE *)SARADC_BASE_ADDRESS2)

#define SARADC_BASE_ADDRESS3 (0xB0000C00U)
#define SARADC3 ((SARADC_MODULE *)SARADC_BASE_ADDRESS3)

#define SARADC_BASE_ADDRESS4 (0xB0300000U)
#define SARADC4 ((SARADC_MODULE *)SARADC_BASE_ADDRESS4)

#define SARADC_BASE_ADDRESS5 (0xB0300400U)
#define SARADC5 ((SARADC_MODULE *)SARADC_BASE_ADDRESS5)

#define SARADC_BASE_ADDRESS6 (0xB0300800U)
#define SARADC6 ((SARADC_MODULE *)SARADC_BASE_ADDRESS6)

#define SARADC_BASE_ADDRESS7 (0xB0300C00U)
#define SARADC7 ((SARADC_MODULE *)SARADC_BASE_ADDRESS7)

#define SARADC_BASE_ADDRESS8 (0xB0010000U)
#define SARADC8 ((SARADC_MODULE *)SARADC_BASE_ADDRESS8)

#define SARADC_BASE_ADDRESS9 (0xB0010400U)
#define SARADC9 ((SARADC_MODULE *)SARADC_BASE_ADDRESS9)

#define SARADC_BASE_ADDRESS10 (0xB0010800U)
#define SARADC10 ((SARADC_MODULE *)SARADC_BASE_ADDRESS10)

/* #Violation: tha6412_cfg_h_REF_1 */
#define SARADC_BASE_ADDRESS11 (0xB0010C00U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SARADC11 ((SARADC_MODULE *)SARADC_BASE_ADDRESS11)

/* Check SARADC base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_SARADC_BASE(pSaradc)                                                                                        \
(((pSaradc) == SARADC0) ? 1U : (((pSaradc) == SARADC1) ? 1U : (((pSaradc) == SARADC2) ? 1U :                                          \
(((pSaradc) == SARADC3) ? 1U : (((pSaradc) == SARADC4) ? 1U : (((pSaradc) == SARADC5) ? 1U :                                          \
(((pSaradc) == SARADC6) ? 1U : (((pSaradc) == SARADC7) ? 1U : (((pSaradc) == SARADC8) ? 1U :                                          \
(((pSaradc) == SARADC9) ? 1U : (((pSaradc) == SARADC10) ? 1U : (((pSaradc) == SARADC11) ? 1U : 0U))))))))))))

/* Get SARADC RCC reset number */
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_SARADC_RCC_RST_NUM(pSaradc)                                                     \
                                (((pSaradc) == SARADC0) ? RCC_MODULERST_SARADC0 :           \
                                (((pSaradc) == SARADC1) ? RCC_MODULERST_SARADC1 :           \
                                (((pSaradc) == SARADC2) ? RCC_MODULERST_SARADC2 :           \
                                (((pSaradc) == SARADC3) ? RCC_MODULERST_SARADC3 :           \
                                (((pSaradc) == SARADC4) ? RCC_MODULERST_SARADC4 :           \
                                (((pSaradc) == SARADC5) ? RCC_MODULERST_SARADC5 :           \
                                (((pSaradc) == SARADC6) ? RCC_MODULERST_SARADC6 :           \
                                (((pSaradc) == SARADC7) ? RCC_MODULERST_SARADC7 :           \
                                (((pSaradc) == SARADC8) ? RCC_MODULERST_SARADC8 :           \
                                (((pSaradc) == SARADC9) ? RCC_MODULERST_SARADC9 :           \
                                (((pSaradc) == SARADC10) ? RCC_MODULERST_SARADC10 : RCC_MODULERST_SARADC11)))))))))))

/* Check SARADC channel number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CHECK_SARADC_CHANNEL_CHECK(channelID)  (((uint32)(channelID) < 12U) ? 1U : 0U)
/* SARADC channel number */
#define SARADC_CHANNEL_NUM  (12U)

/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC_COMMON_BASE_ADDRESS 0xB0002080U /* DSADC common register address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC0_BASE_ADDRESS 0xB0002000U       /* DSADC0 base register address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC1_BASE_ADDRESS 0xB0002400U       /* DSADC1 base register address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC2_BASE_ADDRESS 0xB0012000U       /* DSADC2 base register address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC3_BASE_ADDRESS 0xB0012400U       /* DSADC3 base register address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC4_BASE_ADDRESS 0xB0002800U       /* DSADC4 base register address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC5_BASE_ADDRESS 0xB0002C00U       /* DSADC5 base register address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC6_BASE_ADDRESS 0xB0012800U       /* DSADC6 base register address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC7_BASE_ADDRESS 0xB0012C00U       /* DSADC7 base register address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC8_BASE_ADDRESS 0xB0301000U       /* DSADC8 base register address */
/* #Violation: tha6412_cfg_h_REF_1 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC9_BASE_ADDRESS 0xB0301400U       /* DSADC9 base register address */

/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC0 ((DSADC_MODULE *)(DSADC0_BASE_ADDRESS))                    /* Define point to DSADC0 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC1 ((DSADC_MODULE *)(DSADC1_BASE_ADDRESS))                    /* Define point to DSADC1 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC2 ((DSADC_MODULE *)(DSADC2_BASE_ADDRESS))                    /* Define point to DSADC2 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC3 ((DSADC_MODULE *)(DSADC3_BASE_ADDRESS))                    /* Define point to DSADC3 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC4 ((DSADC_MODULE *)(DSADC4_BASE_ADDRESS))                    /* Define point to DSADC4 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC5 ((DSADC_MODULE *)(DSADC5_BASE_ADDRESS))                    /* Define point to DSADC5 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC6 ((DSADC_MODULE *)(DSADC6_BASE_ADDRESS))                    /* Define point to DSADC6 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC7 ((DSADC_MODULE *)(DSADC7_BASE_ADDRESS))                    /* Define point to DSADC7 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC8 ((DSADC_MODULE *)(DSADC8_BASE_ADDRESS))                    /* Define point to DSADC8 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC9 ((DSADC_MODULE *)(DSADC9_BASE_ADDRESS))                    /* Define point to DSADC9 base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC_COMMON_MODULE ((DSADC_COMMON *)(DSADC_COMMON_BASE_ADDRESS)) /* Define point to DSADC common base address */

/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC_MAIN_CHANNEL_MAX 0x40000U        /* DSADC main channel max value */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC_AUX_CHANNEL_MAX  0x100000U       /* DSADC auxiliary channel max value */
/* #Violation: tha6412_cfg_h_REF_1 */
#define DSADC_MODULE_MAX       0x400U          /* DSADC MODUE max value */

/** \brief  DSADC module ID*/
/* DSADC 0 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC0_MODULE                                   ((uint32)1U << 0U)
/* DSADC 1 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC1_MODULE                                   ((uint32)1U << 1U)
/* DSADC 2 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC2_MODULE                                   ((uint32)1U << 2U)
/* DSADC 3 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC3_MODULE                                   ((uint32)1U << 3U)
/* DSADC 4 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC4_MODULE                                   ((uint32)1U << 4U)
/* DSADC 5 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC5_MODULE                                   ((uint32)1U << 5U)
/* DSADC 6 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC6_MODULE                                   ((uint32)1U << 6U)
/* DSADC 7 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC7_MODULE                                   ((uint32)1U << 7U)
/* DSADC 8 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC8_MODULE                                   ((uint32)1U << 8U)
/* DSADC 9 . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC9_MODULE                                   ((uint32)1U << 9U)

/** \brief  DSADC module main channel ID*/
/* DSADC 0 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC0_MAIN_CHANNEL                                   ((uint32)1U << 0U)
/* DSADC 1 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC1_MAIN_CHANNEL                                   ((uint32)1U << 1U)
/* DSADC 2 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC2_MAIN_CHANNEL                                   ((uint32)1U << 2U)
/* DSADC 3 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC3_MAIN_CHANNEL                                   ((uint32)1U << 3U)
/* DSADC 4 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC4_MAIN_CHANNEL                                   ((uint32)1U << 4U)
/* DSADC 5 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC5_MAIN_CHANNEL                                   ((uint32)1U << 5U)
/* DSADC 6 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC6_MAIN_CHANNEL                                   ((uint32)1U << 6U)
/* DSADC 7 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC7_MAIN_CHANNEL                                   ((uint32)1U << 7U)
/* DSADC 8 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC8_MAIN_CHANNEL                                   ((uint32)1U << 16U)
/* DSADC 9 main channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC9_MAIN_CHANNEL                                   ((uint32)1U << 17U)

/** \brief  DSADC module auxiliary channel ID*/
/* DSADC 0 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC0_AUX_CHANNEL                                   ((uint32)1U << 8U)
/* DSADC 1 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC1_AUX_CHANNEL                                   ((uint32)1U << 9U)
/* DSADC 2 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC2_AUX_CHANNEL                                   ((uint32)1U << 10U)
/* DSADC 3 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC3_AUX_CHANNEL                                   ((uint32)1U << 11U)
/* DSADC 4 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC4_AUX_CHANNEL                                   ((uint32)1U << 12U)
/* DSADC 5 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC5_AUX_CHANNEL                                   ((uint32)1U << 13U)
/* DSADC 6 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC6_AUX_CHANNEL                                   ((uint32)1U << 14U)
/* DSADC 7 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC7_AUX_CHANNEL                                   ((uint32)1U << 15U)
/* DSADC 8 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC8_AUX_CHANNEL                                   ((uint32)1U << 18U)
/* DSADC 9 auxiliary channel . */
/* #Violation: tha6412_cfg_h_REF_1 */
#define    DSADC9_AUX_CHANNEL                                   ((uint32)1U << 19U)


/* Check DSADC base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_DSADC_BASE(pDsadc)                                                                                            \
(((pDsadc) == DSADC0) ? 1U :                                                                                                  \
(((pDsadc) == DSADC1) ? 1U : (((pDsadc) == DSADC2) ? 1U : (((pDsadc) == DSADC3) ? 1U :                                          \
(((pDsadc) == DSADC4) ? 1U : (((pDsadc) == DSADC5) ? 1U : (((pDsadc) == DSADC6) ? 1U :                                          \
(((pDsadc) == DSADC7) ? 1U : (((pDsadc) == DSADC8) ? 1U : (((pDsadc) == DSADC9) ? 1U : 0U))))))))))


/* Get DSADC RCC reset number */
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_DSADC_RCC_RST_NUM(pDsadc)                                                    \
                                (((pDsadc) == DSADC0) ? RCC_MODULERST_DSADC0 :           \
                                (((pDsadc) == DSADC1) ? RCC_MODULERST_DSADC1 :           \
                                (((pDsadc) == DSADC2) ? RCC_MODULERST_DSADC2 :           \
                                (((pDsadc) == DSADC3) ? RCC_MODULERST_DSADC3 :           \
                                (((pDsadc) == DSADC4) ? RCC_MODULERST_DSADC4 :           \
                                (((pDsadc) == DSADC5) ? RCC_MODULERST_DSADC5 :           \
                                (((pDsadc) == DSADC6) ? RCC_MODULERST_DSADC6 :           \
                                (((pDsadc) == DSADC7) ? RCC_MODULERST_DSADC7 :           \
                                (((pDsadc) == DSADC8) ? RCC_MODULERST_DSADC8 : RCC_MODULERST_DSADC9)))))))))

/* Get DSADC module number */
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_DSADC_MODULE_NUM(pDsadc)                               \
                                (((pDsadc) == DSADC0) ? 0U :   \
                                (((pDsadc) == DSADC1) ? 1U :   \
                                (((pDsadc) == DSADC2) ? 2U :   \
                                (((pDsadc) == DSADC3) ? 3U :   \
                                (((pDsadc) == DSADC4) ? 4U :   \
                                (((pDsadc) == DSADC5) ? 5U :   \
                                (((pDsadc) == DSADC6) ? 6U :   \
                                (((pDsadc) == DSADC7) ? 7U :   \
                                (((pDsadc) == DSADC8) ? 8U : 9U)))))))))


/* GTM base address */
#define GTM_BASE_ADDR         (0x94800000U)
#define GTM_WRAPPER_BASE_ADDR (0xC0005000U)
/* GTM object */
#define GTM_HAL          ((GTM_MODULE *)GTM_BASE_ADDR)
/* GTM WRAPPER object */
#define GTM_WRAP    ((GTM_WRAPPER *)GTM_WRAPPER_BASE_ADDR)
/* GTM Cluster number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_CLUSTER_NUM (8U)
/* GTM submodule number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_ATOM_NUM  (8U)         /* ATOM module number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_TOM_NUM   (5U)         /* TOM module number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_ATOM_CH_NUM  (8U)      /* ATOM module channel number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_TOM_CH_NUM   (16U)     /* TOM module channel number */
/* GTM WRAPPER MUX number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_DMAL2_MUX_MSK (0x7FU)  /* GTM to DMA level2 MUX mask */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_DSADC_IN_MUX_NUM (6U)  /* DSADC to GTM MUX number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_DSADC_OUT_MUX_NUM (4U) /* GTM to DSADC MUX number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_DSADC_NUM     (10U)    /* DSADC module number */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GTM_TOUT_NUM  (271U)       /* GTM to GPIO TOUT number */

/* DMA */
/* DMA module base address define */
#define DMA0_BASE_ADDR (0xC00B4000U)
#define DMA1_BASE_ADDR (0xB0030000U)
#define DMA2_BASE_ADDR (0xC00B8000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define DMA3_BASE_ADDR (0xD0030000U)
/* DMA Object define */
#define DMA0 ((DMA_MODULE *)DMA0_BASE_ADDR)
#define DMA1 ((DMA_MODULE *)DMA1_BASE_ADDR)
#define DMA2 ((DMA_MODULE *)DMA2_BASE_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define DMA3 ((DMA_MODULE *)DMA3_BASE_ADDR)
/* The number of DMA module channel*/
#define DMA0_CH_NUM 16U
#define DMA1_CH_NUM 64U
#define DMA2_CH_NUM 24U
#define DMA3_CH_NUM 24U
/* DMA global request lower bound*/
#define DMA0_GREQ_LOWER_BOUND 9U
#define DMA1_GREQ_LOWER_BOUND 103U
#define DMA2_GREQ_LOWER_BOUND 26U
#define DMA3_GREQ_LOWER_BOUND 37U
/* The number of DMA global request */
#define DMA0_GREQ_NUM 32U
#define DMA1_GREQ_NUM 8U
#define DMA2_GREQ_NUM 8U
#define DMA3_GREQ_NUM 8U
/* The number of DMA request MUX ID */
#define DMA0_GREQ_MUXID 31U
#define DMA1_GREQ_MUXID 7U
#define DMA2_GREQ_MUXID 7U
#define DMA3_GREQ_MUXID 7U
/* Check DMA base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_DMA_BASE(pDma)     (((pDma) == DMA0 ) ? 1U : \
                              (((pDma) == DMA1 ) ? 1U : \
                              (((pDma) == DMA2 ) ? 1U : \
                              (((pDma) == DMA3 ) ? 1U : 0U))))
/* Check DMA base address and channel number */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_DMA_CH_ID(pDma, chId) ((((pDma) == DMA0) && ((chId) < DMA0_CH_NUM)) ? 1U : \
                                    ((((pDma) == DMA1) && ((chId) < DMA1_CH_NUM)) ? 1U : \
                                    ((((pDma) == DMA2) && ((chId) < DMA2_CH_NUM)) ? 1U : \
                                    ((((pDma) == DMA3) && ((chId) < DMA3_CH_NUM)) ? 1U : 0U))))
/* Get DMA global request lower bound */
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_DMA_REQ_NUM(pDma) (((pDma) == DMA0) ? DMA0_GREQ_LOWER_BOUND : \
                              (((pDma) == DMA1) ? DMA1_GREQ_LOWER_BOUND : \
                              (((pDma) == DMA2) ? DMA2_GREQ_LOWER_BOUND : DMA3_GREQ_LOWER_BOUND)))
/* Get DMA global request number */
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_DMA_GREQ_NUM(pDma) (((pDma) == DMA0) ? DMA0_GREQ_NUM : \
                               (((pDma) == DMA1) ? DMA1_GREQ_NUM : \
                               (((pDma) == DMA2) ? DMA2_GREQ_NUM : DMA3_GREQ_NUM)))
/* Get DMA RCC reset number */
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_DMA_RCC_RST_NUM(pDma) (((pDma) == DMA0) ? RCC_MODULERST_DMA0 : \
                                  (((pDma) == DMA1) ? RCC_MODULERST_DMA1 : \
                                  (((pDma) == DMA2) ? RCC_MODULERST_DMA2 : RCC_MODULERST_DMA3)))
/* Get DMA max channel */
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_DMA_MAX_CH(pDma)     (((pDma) == DMA0) ? DMA0_CH_NUM : \
                                  (((pDma) == DMA1) ? DMA1_CH_NUM : \
                                  (((pDma) == DMA2) ? DMA2_CH_NUM : DMA3_CH_NUM)))
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_DMA_MAX_MUXREQ(pDma)     (((pDma) == DMA0) ? DMA0_GREQ_MUXID : \
                                  (((pDma) == DMA1) ? DMA1_GREQ_MUXID : \
                                  (((pDma) == DMA2) ? DMA2_GREQ_MUXID : DMA3_GREQ_MUXID)))

/* FC */
/* FC module base address define */
#define FC0_BASE_ADDR (0xB0003000U)
#define FC1_BASE_ADDR (0xB0013000U)
#define FC2_BASE_ADDR (0xB0301800U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define FC3_BASE_ADDR (0xB0301C00U)
/* FC Object define */
#define FC0 ((FC_MODULE *)FC0_BASE_ADDR)
#define FC1 ((FC_MODULE *)FC1_BASE_ADDR)
#define FC2 ((FC_MODULE *)FC2_BASE_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define FC3 ((FC_MODULE *)FC3_BASE_ADDR)
/* Check FC base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_FC_BASE(pFc) (((pFc) == FC0) ? 1U : (((pFc) == FC1) ? 1U : (((pFc) == FC2) ? 1U : (((pFc) == FC3) ? 1U : 0U))))
/* Get FC RCC reset number */
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_FC_RCC_RST_NUM(pFc) (((pFc) == FC0) ? RCC_MODULERST_FC0 : \
                                (((pFc) == FC1) ? RCC_MODULERST_FC1 : \
                                (((pFc) == FC2) ? RCC_MODULERST_FC2 : RCC_MODULERST_FC3)))


/* GIPC */
/* GIPC module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GIPC0_BASE_ADDR (0xC0060C00U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define GIPC1_BASE_ADDR (0xC0061000U)

/* GIPC Object define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GIPC0 ((GIPC_MODULE *)GIPC0_BASE_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define GIPC1 ((GIPC_MODULE *)GIPC1_BASE_ADDR)
/* Check GIPC base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_GIPC_BASE(pGipc)  (((pGipc) == GIPC0) ? 1U : \
                                              (((pGipc) == GIPC1) ? 1U : 0U))

/* ES */
/* ES module LLPP interface base address define */
#define ES_BASE_ADDR (0xB0350000U)
/* ES Object define */
#define ES ((ES_MODULE *)ES_BASE_ADDR)


/* EXTI */
/* EXTI module LLPP interface base address define */
#define EXTI_BASE_ADDRESS (0xC000460CU)
/* EXTI Object define */
#define EXTI ((EXTI_MODULE *)EXTI_BASE_ADDRESS)

/* FLASH */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_CLUSTER_NUM  (2U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_PFLASH_NUM_PER_CLUSTER   (2U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_MAX_CLOCK (400000000U)

/* PFLASH Internal address to Device address offset */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_PFLASH_INTERNALTODEVICE_ADDR_OFFSET (0x88400000U)

/* PFLASH Internal address mask value */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_PFLASH_INTERNALADDR_MASKVALUE (0xFF000000ULL)

/* PFLASH Internal address compare value */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_PFLASH_INTERNALADDR_COMPVALUE (0x08000000ULL)

/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STO0_FACTOR (1000000U) /* flash sto0 desired value (1us) */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STO1_DESIRE (120U)     /* flash sto1 desired value 120ns */

/* FLASH Features*/
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DFLASH_PWORD_SIZE                 (16U)           /*smallest unit that can be programmed in the Dflash */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DFLASH_MAX_PWORD_SIZE             (128U)          /*maximum unit that can be programmed in the Dflash */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DFLASH_SECTOR_SIZE                (512U * FLASH_DFLASH_PWORD_SIZE)  /* bytes per sector in the Dflash*/
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DFLASH_SECTOR_NUM                 (64U)            /* sector number in the Dflash*/

/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_PFLASH_PWORD_SIZE                 (32U)           /*smallest unit that can be programmed in the Pflash */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_PFLASH_MAX_PWORD_SIZE             (256U)          /*maximum unit that can be programmed in the Pflash */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_PFLASH_SECTOR_SIZE                (512U * FLASH_PFLASH_PWORD_SIZE) /* bytes per sector in the Pflash*/
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_PFLASH_SECTOR_NUM                 (192U)          /* sector number in the Pflash*/
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_PFLASH_SECTOR_NUM_INBLOCK         (8U)          /* sector number in the Blcok*/

/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_START_ADDR          (0x94000000U)   /* Start address of the DFLASH */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_END_ADDR            (0x9407FFFFU)   /* End address of the DFLASH */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_INFO0_START_ADDR    (0x94400000U)   /* Start address of the DFLASH INFO 0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_INFO0_END_ADDR      (0x94407FFFU)   /* End address of the DFLASH INFO 0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_START_ADDR          (0x90400000U)   /* Start address of the PFLASH0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_END_ADDR            (0x906FFFFFU)   /* End address of the PFLASH0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_INFO0_START_ADDR    (0x91C00000U)   /* Start address of the PFLASH0 INFO 0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_INFO0_END_ADDR      (0x91C03FFFU)   /* End address of the PDFLASH0 INFO 0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_START_ADDR          (0x90700000U)   /* Start address of the PFLASH1 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_END_ADDR            (0x909FFFFFU)   /* End address of the PFLASH1 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_INFO0_START_ADDR    (0x91C04000U)   /* Start address of the PFLASH1 INFO 0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_INFO0_END_ADDR      (0x91C07FFFU)   /* End address of the PDFLASH1 INFO 0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH2_START_ADDR          (0x90A00000U)   /* Start address of the PFLASH2 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH2_END_ADDR            (0x90CFFFFFU)   /* End address of the PFLASH2 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH2_INFO0_START_ADDR    (0x91C08000U)   /* Start address of the PFLASH2 INFO 0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH2_INFO0_END_ADDR      (0x91C0BFFFU)   /* End address of the PDFLASH2 INFO 0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH3_START_ADDR          (0x90D00000U)   /* Start address of the PFLASH3 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH3_END_ADDR            (0x90FFFFFFU)   /* End address of the PFLASH3 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH3_INFO0_START_ADDR    (0x91C0C000U)   /* Start address of the PFLASH3 INFO 0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH3_INFO0_END_ADDR      (0x91C0FFFFU)   /* End address of the PDFLASH3 INFO 0 */

/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_ERSF_MSK     (0x1)       /* Erase Finished Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_ERSE_MSK     (0x2)       /* Erase Error Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_PROGF_MSK    (0x4)       /* Program Finished Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_PROGE_MSK    (0x8)       /* Program Error Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_ECF_MSK       (0x10)      /* Erase Check Finished Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_ECSTS_MSK    (0x20)      /* Erase Check Result Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_CF_MSK       (0x100)     /* Cancel Finish Redundancy Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_CDF_MSK      (0x400)     /* Cancel Finish Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_ESQE_MSK     (0x10000)   /* Erase Sequence Error Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_MISAE_MSK    (0x40000)   /* Program Miss Align Error Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_POVT_MSK     (0x100000)  /* Program Overtime Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_ERSBUSY_MSK  (0x1000000) /* FLASH Current Erase Operation Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_PROGBUSY_MSK (0x2000000) /* FLASH Current Program Operation Status */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_STS_ECBUSY_MSK   (0x4000000) /* FLASH Current Erase Check Operation Status */

/* #Violation: tha6412_cfg_h_REF_2 */
#define DFLASH_CALCULATE_RDT(uClockFreq) ((float32)(((3e-8) * ((float64)(uClockFreq))) - 2.0f))
/* #Violation: tha6412_cfg_h_REF_2 */
#define PFLASH_CALCULATE_RDT(uClockFreq) ((float32)(((2.5e-8) * ((float64)(uClockFreq))) - 2.0f))

/* #Violation: tha6412_cfg_h_REF_1 */
#define CHECK_DFLASH_INFO_ADD 1U

#if (CHECK_DFLASH_INFO_ADD == 1U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_INFO_START_ADDR     FLASH_DEVICE_DFLASH0_INFO0_START_ADDR
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_INFO_END_ADDR       FLASH_DEVICE_DFLASH0_INFO0_END_ADDR

/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_DFLASH_ADDRESS(addr)   (  ((  ((addr) <= FLASH_DEVICE_DFLASH0_END_ADDR) && \
                                            ((addr) >= FLASH_DEVICE_DFLASH0_START_ADDR)) || \
                                         (  ((addr) <= FLASH_DEVICE_DFLASH0_INFO_END_ADDR) && \
                                            ((addr) >= FLASH_DEVICE_DFLASH0_INFO_START_ADDR)) \
                                        ) ? 1U : 0U)

#elif (CHECK_DFLASH_INFO_ADD == 0U)

/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_DFLASH_ADDRESS(addr)     ((((addr) <= FLASH_DEVICE_DFLASH0_END_ADDR) && \
                                        ((addr) >= FLASH_DEVICE_DFLASH0_START_ADDR)) ? \
                                        1U : 0U)

#endif

/* FLASH module base address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_CLUSTER0_BASE_ADDRESS (0xC0100000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_CLUSTER1_BASE_ADDRESS (0xC0140C00U)

/* #Violation: tha6412_cfg_h_REF_2 */
#define FLASH_GET_COMMON_STS_FROM_PININPUT(pPININPUT) \
                            (((pPININPUT) == FLASH_CLUSTER0_PININPUT) ? FLASH_CLUSTER0_STS : FLASH_CLUSTER1_STS)

/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_PFLASH_INFO_ADD 1U

#if (CHECK_PFLASH_INFO_ADD == 1U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_INFO_START_ADDR     FLASH_DEVICE_PFLASH0_INFO0_START_ADDR
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_INFO_END_ADDR       FLASH_DEVICE_PFLASH0_INFO0_END_ADDR
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_INFO_START_ADDR     FLASH_DEVICE_PFLASH1_INFO0_START_ADDR
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_INFO_END_ADDR       FLASH_DEVICE_PFLASH1_INFO0_END_ADDR
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH2_INFO_START_ADDR     FLASH_DEVICE_PFLASH2_INFO0_START_ADDR
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH2_INFO_END_ADDR       FLASH_DEVICE_PFLASH2_INFO0_END_ADDR
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH3_INFO_START_ADDR     FLASH_DEVICE_PFLASH3_INFO0_START_ADDR
/* #Violation: tha6412_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH3_INFO_END_ADDR       FLASH_DEVICE_PFLASH3_INFO0_END_ADDR

#endif

/* #Violation: tha6412_cfg_h_REF_1 */
#define GET_PFLASH_CTR_FROM_ADDR(addr) \
                            ((((addr) >= FLASH_DEVICE_PFLASH0_START_ADDR) && ((addr) <= FLASH_DEVICE_PFLASH0_END_ADDR)) ? FLASH_PFLASH0_CTR : \
                            ((((addr) >= FLASH_DEVICE_PFLASH1_START_ADDR) && ((addr) <= FLASH_DEVICE_PFLASH1_END_ADDR)) ? FLASH_PFLASH1_CTR : \
                            ((((addr) >= FLASH_DEVICE_PFLASH2_START_ADDR) && ((addr) <= FLASH_DEVICE_PFLASH2_END_ADDR)) ? FLASH_PFLASH2_CTR : \
                            ((((addr) >= FLASH_DEVICE_PFLASH3_START_ADDR) && ((addr) <= FLASH_DEVICE_PFLASH3_END_ADDR)) ? FLASH_PFLASH3_CTR : (FLASH_CTR_MODULE *)NULL_PTR))))

/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_PFLASH_STS_FROM_CTR(pCTR) \
                            (((pCTR) == FLASH_PFLASH0_CTR) ? FLASH_PFLASH0_STS : \
                            (((pCTR) == FLASH_PFLASH1_CTR) ? FLASH_PFLASH1_STS : \
                            (((pCTR) == FLASH_PFLASH2_CTR) ? FLASH_PFLASH2_STS : FLASH_PFLASH3_STS)))
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_PFLASH_MSK_FROM_CTR(pCTR) \
                            (((pCTR) == FLASH_PFLASH0_CTR) ? FLASH_PFLASH0_MSK : \
                            (((pCTR) == FLASH_PFLASH1_CTR) ? FLASH_PFLASH1_MSK : \
                            (((pCTR) == FLASH_PFLASH2_CTR) ? FLASH_PFLASH2_MSK : FLASH_PFLASH3_MSK)))
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_CLUSTER_CTR(index) \
                          (((index) == 0U) ? FLASH_CLUSTER0_CTR : FLASH_CLUSTER1_CTR)
/* #Violation: tha6412_cfg_h_REF_2 */
#define GET_BUFCFG_FROM_CLUSTER(culster)  (FLASH_COMMON_BUFCFG_MODULE*)(((uint32)culster) + FLASH_COMMON_PF0BUFCFG_OFFSET)

/* CPUWDT */
/* CPUWDT module base address define */
#define CPUWDT_BASE_ADDR (0xB0370000U)
/* CPUWDT Object define */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CPUWDT(coreId) ((CPUWDT_MODULE *)(CPUWDT_BASE_ADDR + (0x400U * (uint32)(coreId))))

/* SAFEWDT */
/* SAFEWDT module base address define */
#define SAFEWDT_BASE_ADDR (0xC0040800U)
/* SAFEWDT Object define */
#define SAFEWDT_HAL ((SAFEWDT_MODULE *)SAFEWDT_BASE_ADDR)

/* ESPI */
/* ESPI0 module base address define */
#define ESPI0_BASE_ADDRESS (0xB0380000U)
/* ESPI1 module base address define */
#define ESPI1_BASE_ADDRESS (0xB0380400U)
/* ESPI2 module base address define */
#define ESPI2_BASE_ADDRESS (0xB0380800U)
/* ESPI3 module base address define */
#define ESPI3_BASE_ADDRESS (0xB0400000U)
/* ESPI4 module base address define */
#define ESPI4_BASE_ADDRESS (0xB0400400U)
/* ESPI5 module base address define */
#define ESPI5_BASE_ADDRESS (0xB03B0000U)
/* ESPI6 module base address define */
#define ESPI6_BASE_ADDRESS (0xB03B0400U)
/* ESPI7 module base address define */
#define ESPI7_BASE_ADDRESS (0xB03B0800U)
/* ESPI8 module base address define */
#define ESPI8_BASE_ADDRESS (0xB03B0C00U)
/* ESPI0 Object define */
#define ESPI0 ((ESPI_MODULE *)ESPI0_BASE_ADDRESS)
/* ESPI1 Object define */
#define ESPI1 ((ESPI_MODULE *)ESPI1_BASE_ADDRESS)
/* ESPI2 Object define */
#define ESPI2 ((ESPI_MODULE *)ESPI2_BASE_ADDRESS)
/* ESPI3 Object define */
#define ESPI3 ((ESPI_MODULE *)ESPI3_BASE_ADDRESS)
/* ESPI4 Object define */
#define ESPI4 ((ESPI_MODULE *)ESPI4_BASE_ADDRESS)
/* ESPI5 Object define */
#define ESPI5 ((ESPI_MODULE *)ESPI5_BASE_ADDRESS)
/* ESPI6 Object define */
#define ESPI6 ((ESPI_MODULE *)ESPI6_BASE_ADDRESS)
/* ESPI7 Object define */
#define ESPI7 ((ESPI_MODULE *)ESPI7_BASE_ADDRESS)
/* ESPI8 Object define */
#define ESPI8 ((ESPI_MODULE *)ESPI8_BASE_ADDRESS)
/* Check ESPI base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_ESPI_BASE(pEspi)                                                                                      \
(((pEspi) == ESPI0) ? 1U : (((pEspi) == ESPI1) ? 1U : (((pEspi) == ESPI2) ? 1U :                                          \
(((pEspi) == ESPI3) ? 1U : (((pEspi) == ESPI4) ? 1U : (((pEspi) == ESPI5) ? 1U :                                          \
(((pEspi) == ESPI6) ? 1U : (((pEspi) == ESPI7) ? 1U : (((pEspi) == ESPI8) ? 1U : 0U)))))))))

/* #Violation: tha6412_cfg_h_REF_2 */
#define ESPI_GET_RCC_RST_NUM(pEspi) \
                                     (((ESPI0 == (pEspi))  ? RCC_MODULERST_ESPI0 :  \
                                     ((ESPI1 == (pEspi))  ? RCC_MODULERST_ESPI1 :  \
                                     ((ESPI2 == (pEspi))  ? RCC_MODULERST_ESPI2 :  \
                                     ((ESPI3 == (pEspi))  ? RCC_MODULERST_ESPI3 :  \
                                     ((ESPI4 == (pEspi))  ? RCC_MODULERST_ESPI4 :  \
                                     ((ESPI5 == (pEspi))  ? RCC_MODULERST_ESPI5 :  \
                                     ((ESPI6 == (pEspi))  ? RCC_MODULERST_ESPI6 :  \
                                     ((ESPI7 == (pEspi))  ? RCC_MODULERST_ESPI7 :  \
                                     ((ESPI8 == (pEspi)) ? RCC_MODULERST_ESPI8 : RCC_MODULERST_MAX))))))))))
/* PSI5 */
/* PSI5 module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_BASE_ADDRESS (0xB0302000U)
/* PSI5 Object define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5 (volatile PSI5_MODULE*)(PSI5_BASE_ADDRESS)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CHECK_PSI5_BASE(pPsi5)((pPsi5) == PSI5 ? 1U : 0U)

/* Base address of PSI5 Txfifo0 module */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_TXFIFO0_ADDRESS (0xB030203CU)
/* Base address of PSI5 Rxfifo0 module */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_RXFIFO0_ADDRESS (0xB0302040U)
/* Base address of PSI5 Txfifo1 module */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_TXFIFO1_ADDRESS (0xB0302070U)
/* Base address of PSI5 Rxfifo1 module */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_RXFIFO1_ADDRESS (0xB0302074U)
/* Base address of PSI5 Txfifo2 module */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_TXFIFO2_ADDRESS (0xB03020A4U)
/* Base address of PSI5 Rxfifo2 module */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_RXFIFO2_ADDRESS (0xB03020A8U)
/* Base address of PSI5 Txfifo3 module */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_TXFIFO3_ADDRESS (0xB03020D8U)
/* Base address of PSI5 Rxfifo3 module */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_RXFIFO3_ADDRESS (0xB03020DCU)

/* Request number of Txch0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_CH0_TX_REQNUMBER (207U)
/* Request number of Rxch0 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_CH0_RX_REQNUMBER (209U)
/* Request number of Txch1 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_CH1_TX_REQNUMBER (211U)
/* Request number of Rxch1 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_CH1_RX_REQNUMBER (213U)
/* Request number of Txch2 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_CH2_TX_REQNUMBER (215U)
/* Request number of Rxch2 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_CH2_RX_REQNUMBER (217U)
/* Request number of Txch3 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_CH3_TX_REQNUMBER (219U)
/* Request number of Rxch3 */
/* #Violation: tha6412_cfg_h_REF_1 */
#define PSI5_CH3_RX_REQNUMBER (221U)


/* OVC */
/* OVC0 module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC0_BASE_ADDR (0xC00C4000U)
/* OVC0 Object define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC0 ((OVC_MODULE *)OVC0_BASE_ADDR)
/* OVC1 module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC1_BASE_ADDR (0xC00C6000U)
/* OVC1 Object define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC1 ((OVC_MODULE *)OVC1_BASE_ADDR)
/* Check OVC base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_OVC_BASE(pOvc)  (((pOvc) == OVC0) || ((pOvc) == OVC1))
/* Check OVC coreID */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CHECK_OVC_CORE(id) (((id) < 2U) ? 1U : 0U)

/* Target address : Memory domain Program Flash0 via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_PF0_START_ADDR (0x40400000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_PF0_END_ADDR (0x406FFFFFU)

/* Target address : Device domain Program Flash0 via MBUS AXI Slave start address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_PF0_START_ADDR (0x90400000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_PF0_END_ADDR (0x906FFFFFU)

/* Target address : Memory domain Program Flash1 via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_PF1_START_ADDR (0x40700000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_PF1_END_ADDR (0x409FFFFFU)

/* Target address : Device domain Program Flash1 via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_PF1_START_ADDR (0x90700000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_PF1_END_ADDR (0x909FFFFFU)

/* Target address : Memory domain Program Flash1 via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_PF2_START_ADDR (0x40A00000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_PF2_END_ADDR (0x40CFFFFFU)

/* Target address : Device domain Program Flash1 via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_PF2_START_ADDR (0x90A00000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_PF2_END_ADDR (0x90CFFFFFU)

/* Target address : Memory domain Program Flash1 via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_PF3_START_ADDR (0x40D00000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_PF3_END_ADDR (0x40FFFFFFU)

/* Target address : Device domain Program Flash1 via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_PF3_START_ADDR (0x90D00000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_PF3_END_ADDR (0x90FFFFFFU)

/* Target address : Memory domain Data Flash via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_DF_START_ADDR (0x44000000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_DF_END_ADDR (0x4407FFFFU)

/* Target address : Memory domain Data Flash NVR via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_DF_INFO0_START_ADDR (0x44400000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_DF_INFO0_END_ADDR (0x44407FFFU)

/* Target address : Memory domain Data Flash NVR_CFG via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_DF_INFO1_START_ADDR (0x44408000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_DF_INFO1_END_ADDR (0x44409FFFU)

/* Target address : Device domain Data Flash via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_DF_START_ADDR (0x94000000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_DF_END_ADDR (0x9407FFFFU)

/* Target address : Device domain Data Flash NVR via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_DF_INFO0_START_ADDR (0x94400000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_DF_INFO0_END_ADDR (0x94407FFFU)

/* Target address : Device domain Data Flash NVR_CFG via MBUS AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_DF_INFO1_START_ADDR (0x94408000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_DF_INFO1_END_ADDR (0x94409FFFU)

/* Overlay address: Memory domain CPU0 ATCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU0_ATCM_START_ADDR (0x30000000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU0_ATCM_END_ADDR (0x3000FFFFU)

/* Overlay address: Memory domain CPU0 BTCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU0_BTCM_START_ADDR (0x30100000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU0_BTCM_END_ADDR (0x3013BFFFU)

/* Overlay address: Memory domain CPU0 CTCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU0_CTCM_START_ADDR (0x30200000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU0_CTCM_END_ADDR (0x3020FFFFU)

/* Overlay address: Memory domain CPU1 ATCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU1_ATCM_START_ADDR (0x30400000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU1_ATCM_END_ADDR (0x3040FFFFU)

/* Overlay address: Memory domain CPU1 BTCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU1_BTCM_START_ADDR (0x30500000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU1_BTCM_END_ADDR (0x3053BFFFU)

/* Overlay address: Memory domain CPU1 CTCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU1_CTCM_START_ADDR (0x30600000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU1_CTCM_END_ADDR (0x3060FFFFU)

/* Overlay address: Memory domain CPU2 ATCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU2_ATCM_START_ADDR (0x31000000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU2_ATCM_END_ADDR (0x3100FFFFU)
/* Overlay address: Memory domain CPU2 BTCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU2_BTCM_START_ADDR (0x31100000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU2_BTCM_END_ADDR (0x31117FFFU)
/* Overlay address: Memory domain CPU2 CTCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU2_CTCM_START_ADDR (0x31200000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU2_CTCM_END_ADDR (0x3120FFFFU)

/* Overlay address: Memory domain CPU3 ATCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU3_ATCM_START_ADDR (0x31400000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU3_ATCM_END_ADDR (0x3140FFFFU)
/* Overlay address: Memory domain CPU3 BTCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU3_BTCM_START_ADDR (0x31500000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU3_BTCM_END_ADDR (0x31517FFFU)
/* Overlay address: Memory domain CPU3 CTCM via AXI Slave address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU3_CTCM_START_ADDR (0x31600000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MEM_CPU3_CTCM_END_ADDR (0x3160FFFFU)

/* Overlay address: Main domain GMU0 start address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MAIN_GMU0_START_ADDR (0x10000000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MAIN_GMU0_END_ADDR (0x1001FFFFU)

/* Overlay address: Main domain GMU1 start address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MAIN_GMU1_START_ADDR (0x10020000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_MAIN_GMU1_END_ADDR (0x1003FFFFU)

/* Overlay address: Device domain GMU0 start address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_GMU0_START_ADDR (0x82000000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_GMU0_END_ADDR (0x8201FFFFU)

/* Overlay address: Device domain GMU1 start address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_GMU1_START_ADDR (0x82020000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define OVC_DEV_GMU1_END_ADDR (0x8203FFFFU)

/* check if an address is within any of the defined memory regions */
/* #Violation: tha6412_cfg_h_REF_2 */
#define OVC_CHECK_TARGET_ADDRESS_REGION(Taradd) \
( (((Taradd) >= OVC_MEM_PF0_START_ADDR) && ((Taradd) <= OVC_MEM_PF0_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_PF0_START_ADDR) && ((Taradd) <= OVC_DEV_PF0_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_PF1_START_ADDR) && ((Taradd) <= OVC_MEM_PF1_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_PF1_START_ADDR) && ((Taradd) <= OVC_DEV_PF1_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_PF2_START_ADDR) && ((Taradd) <= OVC_MEM_PF2_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_PF2_START_ADDR) && ((Taradd) <= OVC_DEV_PF2_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_PF3_START_ADDR) && ((Taradd) <= OVC_MEM_PF3_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_PF3_START_ADDR) && ((Taradd) <= OVC_DEV_PF3_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_DF_START_ADDR) && ((Taradd) <= OVC_MEM_DF_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_DF_INFO0_START_ADDR) && ((Taradd) <= OVC_MEM_DF_INFO0_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_DF_INFO1_START_ADDR) && ((Taradd) <= OVC_MEM_DF_INFO1_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_DF_START_ADDR) && ((Taradd) <= OVC_DEV_DF_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_DF_INFO0_START_ADDR) && ((Taradd) <= OVC_DEV_DF_INFO0_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_DF_INFO1_START_ADDR) && ((Taradd) <= OVC_DEV_DF_INFO1_END_ADDR)) )

/* #Violation: tha6412_cfg_h_REF_2 */
#define OVC_CHECK_OVERLAY_ADDRESS_REGION(Oveadd) \
( (((Oveadd) >= OVC_MEM_CPU0_ATCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU0_ATCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU0_BTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU0_BTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU0_CTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU0_CTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU1_ATCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU1_ATCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU1_BTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU1_BTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU1_CTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU1_CTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU2_ATCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU2_ATCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU2_BTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU2_BTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU2_CTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU2_CTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU3_ATCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU3_ATCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU3_BTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU3_BTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU3_CTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU3_CTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MAIN_GMU0_START_ADDR) && ((Oveadd) <= OVC_MAIN_GMU0_END_ADDR)) || \
 (((Oveadd) >= OVC_DEV_GMU0_START_ADDR) && ((Oveadd) <= OVC_DEV_GMU0_END_ADDR)) ||\
 (((Oveadd) >= OVC_MAIN_GMU1_START_ADDR) && ((Oveadd) <= OVC_MAIN_GMU1_END_ADDR)) || \
 (((Oveadd) >= OVC_DEV_GMU1_START_ADDR) && ((Oveadd) <= OVC_DEV_GMU1_END_ADDR)) )



/* TSENSOR */
/* TSENSOR0 module base address define */
#define TSENSOR0_BASE_ADDRESS (0xC00E0000U)
/* TSENSOR0 module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define TSENSOR1_BASE_ADDRESS (0xC00E0400U)
/* TSENSOR0 Object define */
#define TSENSOR0 ((TSENSOR_MODULE *)TSENSOR0_BASE_ADDRESS)
/* TSENSOR0 Object define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define TSENSOR1 ((TSENSOR_MODULE *)TSENSOR1_BASE_ADDRESS)
/* Check TSENSOR base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_TSENSOR_BASE(pTsensor) (((pTsensor) == TSENSOR0) ? 1U : (((pTsensor) == TSENSOR1) ? 1U : 0U))

/* MSC */
/* MSC0 module base address define */
#define MSC0_BASE_ADDR (0xD0044000U)
/* MSC1 module base address define */
#define MSC1_BASE_ADDR (0xC0140400U)
/* MSC2 module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define MSC2_BASE_ADDR (0xC0140800U)
/* MSC0 Object define */
#define MSC0_HAL ((MSC_MODULE *)MSC0_BASE_ADDR)
/* MSC1 Object define */
#define MSC1_HAL ((MSC_MODULE *)MSC1_BASE_ADDR)
/* MSC2 Object define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define MSC2_HAL ((MSC_MODULE *)MSC2_BASE_ADDR)
/* Check MSC base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_MSC_BASE(pMsc) (((pMsc) == MSC0_HAL) ? 1U : (((pMsc) == MSC1_HAL) ? 1U : (((pMsc) == MSC2_HAL) ? 1U : 0U)))

/* I2C */
/* I2C module base address define */
#define I2C_BASE_ADDR (0xD009A000U)
/* I2C Object define */
#define I2C0 ((I2C_MODULE *)(I2C_BASE_ADDR + 0x0U))
/* I2C Object define */
#define I2C1 ((I2C_MODULE *)(I2C_BASE_ADDR + 0x400U))
/* Check I2C base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_I2C_BASE(pI2c) (((pI2c) == I2C0) ? 1U : (((pI2c) == I2C1) ? 1U : 0U))

/* CAN */

/* The largest number of CAN modules on the chip */
/* #Violation: tha6412_cfg_h_REF_1 */
#define MAX_CAN_NUM (4U)

/* CAN module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN0_BASE_ADDR              (0xC0090000UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN1_BASE_ADDR              (0xD0000000UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN2_BASE_ADDR              (0xC0200000UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN3_BASE_ADDR              (0xD00E0000UL)

/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN0_BASE_LLPP_ADDR          (0xB0390000UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN1_BASE_LLPP_ADDR          (0xB03E0000UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN2_BASE_LLPP_ADDR          (0xB03C0000UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN3_BASE_LLPP_ADDR          (0xB0420000UL)

/* CAN Object define--AXIM bus access and communication */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN0                         ((CAN_MODULE *)CAN0_BASE_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN1                         ((CAN_MODULE *)CAN1_BASE_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN2                         ((CAN_MODULE *)CAN2_BASE_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN3                         ((CAN_MODULE *)CAN3_BASE_ADDR)

/* CAN Object define--LLPP bus access and communication */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN0_LLPP                     ((CAN_MODULE *)CAN0_BASE_LLPP_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN1_LLPP                     ((CAN_MODULE *)CAN1_BASE_LLPP_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN2_LLPP                     ((CAN_MODULE *)CAN2_BASE_LLPP_ADDR)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN3_LLPP                     ((CAN_MODULE *)CAN3_BASE_LLPP_ADDR)

/* CAN node offset address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN_NODE0_OFFSET_ADDR         (0x00000000UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN_NODE1_OFFSET_ADDR         (0x00001800UL)
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN_NODE2_OFFSET_ADDR         (0x00003000UL)

/* CAN00/01/02 node object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN00                         ((CAN_NODE *)(CAN0_BASE_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN01                         ((CAN_NODE *)(CAN0_BASE_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN02                         ((CAN_NODE *)(CAN0_BASE_ADDR + CAN_NODE2_OFFSET_ADDR))

/* CAN10/11/12 node object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN10                         ((CAN_NODE *)(CAN1_BASE_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN11                         ((CAN_NODE *)(CAN1_BASE_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN12                         ((CAN_NODE *)(CAN1_BASE_ADDR + CAN_NODE2_OFFSET_ADDR))

/* CAN20/21/22 node object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN20                         ((CAN_NODE *)(CAN2_BASE_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN21                         ((CAN_NODE *)(CAN2_BASE_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN22                         ((CAN_NODE *)(CAN2_BASE_ADDR + CAN_NODE2_OFFSET_ADDR))

/* CAN30/31/22 node object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN30                         ((CAN_NODE *)(CAN3_BASE_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN31                         ((CAN_NODE *)(CAN3_BASE_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN32                         ((CAN_NODE *)(CAN3_BASE_ADDR + CAN_NODE2_OFFSET_ADDR))

/* CAN00/01/02 node object */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN00_LLPP                     ((CAN_NODE *)(CAN0_BASE_LLPP_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN01_LLPP                     ((CAN_NODE *)(CAN0_BASE_LLPP_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN02_LLPP                     ((CAN_NODE *)(CAN0_BASE_LLPP_ADDR + CAN_NODE2_OFFSET_ADDR))
                                                            
/* CAN10/11/12 node    object */     
/* #Violation: tha6412_cfg_h_REF_1 */       
#define CAN10_LLPP                     ((CAN_NODE *)(CAN1_BASE_LLPP_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN11_LLPP                     ((CAN_NODE *)(CAN1_BASE_LLPP_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN12_LLPP                     ((CAN_NODE *)(CAN1_BASE_LLPP_ADDR + CAN_NODE2_OFFSET_ADDR))
                                                            
/* CAN20/21/22 node object */  
/* #Violation: tha6412_cfg_h_REF_1 */          
#define CAN20_LLPP                     ((CAN_NODE *)(CAN2_BASE_LLPP_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN21_LLPP                     ((CAN_NODE *)(CAN2_BASE_LLPP_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN22_LLPP                     ((CAN_NODE *)(CAN2_BASE_LLPP_ADDR + CAN_NODE2_OFFSET_ADDR))
                                                            
/* CAN30/31/22 node object */     
/* #Violation: tha6412_cfg_h_REF_1 */       
#define CAN30_LLPP                     ((CAN_NODE *)(CAN3_BASE_LLPP_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN31_LLPP                     ((CAN_NODE *)(CAN3_BASE_LLPP_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN32_LLPP                     ((CAN_NODE *)(CAN3_BASE_LLPP_ADDR + CAN_NODE2_OFFSET_ADDR))

/* Get node index in CAN module */
/* #Violation: tha6412_cfg_h_REF_1 */
#define CAN_NODE_MAX_IN_MODULE      (3U)
/* #Violation: tha6412_cfg_h_REF_2 */
#define CAN_NODE_INDEX(pNode)       (((((uint32)(pNode) & (0x0000FF00UL)) == CAN_NODE0_OFFSET_ADDR) ? 0U : \
                                     ((((uint32)(pNode) & (0x0000FF00UL)) == CAN_NODE1_OFFSET_ADDR) ? 1U : \
                                     ((((uint32)(pNode) & (0x0000FF00UL)) == CAN_NODE2_OFFSET_ADDR) ? 2U : 0xFFFFFFFFU))))


/* Check CAN node base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_CANNODE_BASE(pNode)                                                                                         \
(((pNode) == CAN00) ? 1U : (((pNode) == CAN01) ? 1U : (((pNode) == CAN02) ? 1U :                                          \
(((pNode) == CAN10) ? 1U : (((pNode) == CAN11) ? 1U : (((pNode) == CAN12) ? 1U :                                          \
(((pNode) == CAN20) ? 1U : (((pNode) == CAN21) ? 1U : (((pNode) == CAN22) ? 1U :                                          \
(((pNode) == CAN30) ? 1U : (((pNode) == CAN31) ? 1U : (((pNode) == CAN32) ? 1U :                                          \
(((pNode) == CAN00_LLPP) ? 1U : (((pNode) == CAN01_LLPP) ? 1U : (((pNode) == CAN02_LLPP) ? 1U :                           \
(((pNode) == CAN10_LLPP) ? 1U : (((pNode) == CAN11_LLPP) ? 1U : (((pNode) == CAN12_LLPP) ? 1U :                           \
(((pNode) == CAN20_LLPP) ? 1U : (((pNode) == CAN21_LLPP) ? 1U : (((pNode) == CAN22_LLPP) ? 1U :                           \
(((pNode) == CAN30_LLPP) ? 1U : (((pNode) == CAN31_LLPP) ? 1U : (((pNode) == CAN32_LLPP) ? 1U : 0U))))))))))))))))))))))))

/* SENT */
/* SENT module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR0         (0xD0090000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR1         (0xD0090400U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR2         (0xD0090800U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR3         (0xD0090C00U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR4         (0xD0091000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR5         (0xD00B0000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR6         (0xD00B0400U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR7         (0xD00B0800U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR8         (0xD00B0C00U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR9         (0xD00B1000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR10        (0xD0071000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR11        (0xD0071400U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR12        (0xD0071800U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR13        (0xD0071C00U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR14        (0xD0072000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR15        (0xD00D0000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR16        (0xD00D0400U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR17        (0xD00D0800U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR18        (0xD00D0C00U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR19        (0xD00D1000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR20        (0xD00D1400U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR21        (0xD00D1800U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR22        (0xD00D1C00U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR23        (0xD00D2000U)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_BASE_ADDR24        (0xD00D2400U)

/* SENT Object define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT0             ((SENT_MODULE *)SENT_BASE_ADDR0)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT1             ((SENT_MODULE *)SENT_BASE_ADDR1)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT2             ((SENT_MODULE *)SENT_BASE_ADDR2)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT3             ((SENT_MODULE *)SENT_BASE_ADDR3)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT4             ((SENT_MODULE *)SENT_BASE_ADDR4)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT5             ((SENT_MODULE *)SENT_BASE_ADDR5)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT6             ((SENT_MODULE *)SENT_BASE_ADDR6)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT7             ((SENT_MODULE *)SENT_BASE_ADDR7)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT8             ((SENT_MODULE *)SENT_BASE_ADDR8)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT9             ((SENT_MODULE *)SENT_BASE_ADDR9)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT10            ((SENT_MODULE *)SENT_BASE_ADDR10)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT11            ((SENT_MODULE *)SENT_BASE_ADDR11)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT12            ((SENT_MODULE *)SENT_BASE_ADDR12)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT13            ((SENT_MODULE *)SENT_BASE_ADDR13)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT14            ((SENT_MODULE *)SENT_BASE_ADDR14)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT15            ((SENT_MODULE *)SENT_BASE_ADDR15)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT16            ((SENT_MODULE *)SENT_BASE_ADDR16)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT17            ((SENT_MODULE *)SENT_BASE_ADDR17)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT18            ((SENT_MODULE *)SENT_BASE_ADDR18)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT19            ((SENT_MODULE *)SENT_BASE_ADDR19)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT20            ((SENT_MODULE *)SENT_BASE_ADDR20)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT21            ((SENT_MODULE *)SENT_BASE_ADDR21)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT22            ((SENT_MODULE *)SENT_BASE_ADDR22)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT23            ((SENT_MODULE *)SENT_BASE_ADDR23)
/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT24            ((SENT_MODULE *)SENT_BASE_ADDR24)

/* #Violation: tha6412_cfg_h_REF_1 */
#define SENT_GET_RCC_RST_NUM(pSentModule) \
                                    (((SENT0 == (pSentModule))  ? RCC_MODULERST_SENT0 :  \
                                     ((SENT1 == (pSentModule))  ? RCC_MODULERST_SENT1 :  \
                                     ((SENT2 == (pSentModule))  ? RCC_MODULERST_SENT2 :  \
                                     ((SENT3 == (pSentModule))  ? RCC_MODULERST_SENT3 :  \
                                     ((SENT4 == (pSentModule))  ? RCC_MODULERST_SENT4 :  \
                                     ((SENT5 == (pSentModule))  ? RCC_MODULERST_SENT5 :  \
                                     ((SENT6 == (pSentModule))  ? RCC_MODULERST_SENT6 :  \
                                     ((SENT7 == (pSentModule))  ? RCC_MODULERST_SENT7 :  \
                                     ((SENT8 == (pSentModule))  ? RCC_MODULERST_SENT8 :  \
                                     ((SENT9 == (pSentModule))  ? RCC_MODULERST_SENT9 :  \
                                     ((SENT10 == (pSentModule))  ? RCC_MODULERST_SENT10 :  \
                                     ((SENT11 == (pSentModule))  ? RCC_MODULERST_SENT11 :  \
                                     ((SENT12 == (pSentModule))  ? RCC_MODULERST_SENT12 :  \
                                     ((SENT13 == (pSentModule))  ? RCC_MODULERST_SENT13 :  \
                                     ((SENT14 == (pSentModule))  ? RCC_MODULERST_SENT14 :  \
                                     ((SENT15 == (pSentModule))  ? RCC_MODULERST_SENT15 :  \
                                     ((SENT16 == (pSentModule))  ? RCC_MODULERST_SENT16 :  \
                                     ((SENT17 == (pSentModule))  ? RCC_MODULERST_SENT17 :  \
                                     ((SENT18 == (pSentModule))  ? RCC_MODULERST_SENT18 :  \
                                     ((SENT19 == (pSentModule))  ? RCC_MODULERST_SENT19 :  \
                                     ((SENT20 == (pSentModule))  ? RCC_MODULERST_SENT20 :  \
                                     ((SENT21 == (pSentModule))  ? RCC_MODULERST_SENT21 :  \
                                     ((SENT22 == (pSentModule))  ? RCC_MODULERST_SENT22 :  \
                                     ((SENT23 == (pSentModule))  ? RCC_MODULERST_SENT23 :  \
                                     ((SENT24 == (pSentModule))  ? RCC_MODULERST_SENT24 :  RCC_MODULERST_MAX))))))))))))))))))))))))))
                                  
/* SENT-Check the legality of the module */
/* #Violation: tha6412_cfg_h_REF_2 */
#define SENT_CHECK_MODULE(pSentModule) \
                                    (((SENT0 == (pSentModule))  || (SENT1 == (pSentModule))  || (SENT2 == (pSentModule))  || \
                                      (SENT3 == (pSentModule))  || (SENT4 == (pSentModule))  || (SENT5 == (pSentModule))  || \
                                      (SENT6 == (pSentModule))  || (SENT7 == (pSentModule))  || (SENT8 == (pSentModule))  || \
                                      (SENT9 == (pSentModule))  || (SENT10 == (pSentModule)) || (SENT11 == (pSentModule)) || \
                                      (SENT12 == (pSentModule)) || (SENT13 == (pSentModule)) || (SENT14 == (pSentModule)) || \
                                      (SENT15 == (pSentModule)) || (SENT16 == (pSentModule)) || (SENT17 == (pSentModule)) || \
                                      (SENT18 == (pSentModule)) || (SENT19 == (pSentModule)) || (SENT20 == (pSentModule)) || \
                                      (SENT21 == (pSentModule)) || (SENT22 == (pSentModule)) || (SENT23 == (pSentModule)) || \
                                      (SENT24 == (pSentModule))) ? 1U : 0U)


/* ASI module base address */
#define ASI0_BASE_ADDR                (0xD0080000U)
#define ASI1_BASE_ADDR                 (0xD0080400U)
#define ASI2_BASE_ADDR                 (0xD0080800U)
#define ASI3_BASE_ADDR                 (0xD0080C00U)
#define ASI4_BASE_ADDR                 (0xD00A0000U)
#define ASI5_BASE_ADDR                 (0xD00A0400U)
#define ASI6_BASE_ADDR                 (0xD00A0800U)
#define ASI7_BASE_ADDR                 (0xD00A0C00U)
#define ASI8_BASE_ADDR                 (0xD0081000U)
#define ASI9_BASE_ADDR                 (0xD0081400U)
#define ASI10_BASE_ADDR                (0xD0081800U)
#define ASI11_BASE_ADDR                (0xD00A1000U)
#define ASI12_BASE_ADDR                (0xD00A1400U)
#define ASI13_BASE_ADDR                (0xD00A1800U)
#define ASI14_BASE_ADDR                (0xD00A1C00U)
#define ASI15_BASE_ADDR                (0xD00A2000U)
#define ASI16_BASE_ADDR                (0xD00C0000U)
#define ASI17_BASE_ADDR                (0xD00C0400U)
#define ASI18_BASE_ADDR                (0xD00C0800U)
#define ASI19_BASE_ADDR                (0xD00C0C00U)
#define ASI20_BASE_ADDR                (0xD00C1000U)
#define ASI21_BASE_ADDR                (0xD00C1400U)
#define ASI22_BASE_ADDR                (0xD00C1800U)
#define ASI23_BASE_ADDR                (0xD00C1C00U)

/* ASI Object */
#define ASI0                          ((ASI_MODULE *)(ASI0_BASE_ADDR))
#define ASI1                          ((ASI_MODULE *)(ASI1_BASE_ADDR))
#define ASI2                          ((ASI_MODULE *)(ASI2_BASE_ADDR))
#define ASI3                          ((ASI_MODULE *)(ASI3_BASE_ADDR))
#define ASI4                          ((ASI_MODULE *)(ASI4_BASE_ADDR))
#define ASI5                          ((ASI_MODULE *)(ASI5_BASE_ADDR))
#define ASI6                          ((ASI_MODULE *)(ASI6_BASE_ADDR))
#define ASI7                          ((ASI_MODULE *)(ASI7_BASE_ADDR))
#define ASI8                          ((ASI_MODULE *)(ASI8_BASE_ADDR))
#define ASI9                          ((ASI_MODULE *)(ASI9_BASE_ADDR))
#define ASI10                         ((ASI_MODULE *)(ASI10_BASE_ADDR))
#define ASI11                         ((ASI_MODULE *)(ASI11_BASE_ADDR))
#define ASI12                         ((ASI_MODULE *)(ASI12_BASE_ADDR))
#define ASI13                         ((ASI_MODULE *)(ASI13_BASE_ADDR))
#define ASI14                         ((ASI_MODULE *)(ASI14_BASE_ADDR))
#define ASI15                         ((ASI_MODULE *)(ASI15_BASE_ADDR))
#define ASI16                         ((ASI_MODULE *)(ASI16_BASE_ADDR))
#define ASI17                         ((ASI_MODULE *)(ASI17_BASE_ADDR))
#define ASI18                         ((ASI_MODULE *)(ASI18_BASE_ADDR))
#define ASI19                         ((ASI_MODULE *)(ASI19_BASE_ADDR))
#define ASI20                         ((ASI_MODULE *)(ASI20_BASE_ADDR))
#define ASI21                         ((ASI_MODULE *)(ASI21_BASE_ADDR))
#define ASI22                         ((ASI_MODULE *)(ASI22_BASE_ADDR))
#define ASI23                         ((ASI_MODULE *)(ASI23_BASE_ADDR))

/* ASI-Check the legality of the module */
/* #Violation: tha6412_cfg_h_REF_2 */
#define ASI_GET_RCC_RST_NUM(pAsiModule) \
                                    (((ASI0 == (pAsiModule))  ? RCC_MODULERST_ASI0 :  \
                                     ((ASI1 == (pAsiModule))  ? RCC_MODULERST_ASI1 :  \
                                     ((ASI2 == (pAsiModule))  ? RCC_MODULERST_ASI2 :  \
                                     ((ASI3 == (pAsiModule))  ? RCC_MODULERST_ASI3 :  \
                                     ((ASI4 == (pAsiModule))  ? RCC_MODULERST_ASI4 :  \
                                     ((ASI5 == (pAsiModule))  ? RCC_MODULERST_ASI5 :  \
                                     ((ASI6 == (pAsiModule))  ? RCC_MODULERST_ASI6 :  \
                                     ((ASI7 == (pAsiModule))  ? RCC_MODULERST_ASI7 :  \
                                     ((ASI8 == (pAsiModule))  ? RCC_MODULERST_ASI8 :  \
                                     ((ASI9 == (pAsiModule))  ? RCC_MODULERST_ASI9 :  \
                                     ((ASI10 == (pAsiModule)) ? RCC_MODULERST_ASI10 : \
                                     ((ASI11 == (pAsiModule)) ? RCC_MODULERST_ASI11 : \
                                     ((ASI12 == (pAsiModule)) ? RCC_MODULERST_ASI12 : \
                                     ((ASI13 == (pAsiModule)) ? RCC_MODULERST_ASI13 : \
                                     ((ASI14 == (pAsiModule)) ? RCC_MODULERST_ASI14 : \
                                     ((ASI15 == (pAsiModule)) ? RCC_MODULERST_ASI15 : \
                                     ((ASI16 == (pAsiModule)) ? RCC_MODULERST_ASI16 : \
                                     ((ASI17 == (pAsiModule)) ? RCC_MODULERST_ASI17 : \
                                     ((ASI18 == (pAsiModule)) ? RCC_MODULERST_ASI18 : \
                                     ((ASI19 == (pAsiModule)) ? RCC_MODULERST_ASI19 : \
                                     ((ASI20 == (pAsiModule)) ? RCC_MODULERST_ASI20 : \
                                     ((ASI21 == (pAsiModule)) ? RCC_MODULERST_ASI21 : \
                                     ((ASI22 == (pAsiModule)) ? RCC_MODULERST_ASI22 : \
                                     ((ASI23 == (pAsiModule)) ? RCC_MODULERST_ASI23 : RCC_MODULERST_MAX)))))))))))))))))))))))))
                                      
/* IOM */
/* IOM module base address */
#define IOM_BASE_ADDR (0xB0058000U)
/* IOM module base address */
#define IOM ((IOM_MODULE*)IOM_BASE_ADDR)

/* GMU */
/* GMU0 module base address define */
#define GMU0_BASE_ADDR (0xC0060000U)
/* GMU1 module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GMU1_BASE_ADDR (0xC0061400U)
/* GMU0 Object define */
#define GMU0 ((GMU_MODULE *)GMU0_BASE_ADDR)
/* GMU1 Object define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GMU1 ((GMU_MODULE *)GMU1_BASE_ADDR)
/* GMU MEMSTS Register offset address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GMU_MEMSTS_OFFSET_ADDR (0x20)
/* Check GMU base address */
/* #Violation: tha6412_cfg_h_REF_2 */
#define CHECK_GMU_BASE(pGmu) (((pGmu) == GMU0) ? 1U : (((pGmu) == GMU1) ? 1U : 0U))
/* Get gmu clock number */
/* #Violation: tha6412_cfg_h_REF_2 */
#define GMU_RCC_MODULECLK_NUM(pGmu) (((GMU_MODULE *)(pGmu) == GMU0) ? RCC_MODULECLKTYPE_GMU0CLK : RCC_MODULECLKTYPE_GMU1CLK)

/* GMU group number check */
/* #Violation: tha6412_cfg_h_REF_1 */
#define GMU_GROUP_NUMBER_CHECK(Group) (((uint32)(Group) <= 2U) ? 1U : 0U)

/* LMU */
/* LMU1 module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define LMU1_BASE_ADDR (0xB0060000)
/* LMU2 module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define LMU2_BASE_ADDR (0xC0060400)
/* LMU3 module base address define */
/* #Violation: tha6412_cfg_h_REF_1 */
#define LMU3_BASE_ADDR (0xD0050000)
/* LMU MEMSTS Register offset address */
/* #Violation: tha6412_cfg_h_REF_1 */
#define LMU_MEMSTS_OFFSET_ADDR (0x24)


/* PORT */
/* PORT base address define */
#define PORT_P00_BASE_ADDRESS 0xB0050000U   /* P00 base address */
#define PORT_P01_BASE_ADDRESS 0xB0050100U   /* P01 base address */
#define PORT_P02_BASE_ADDRESS 0xB0050200U   /* P02 base address */
#define PORT_P10_BASE_ADDRESS 0xB0050A00U   /* P10 base address */
#define PORT_P11_BASE_ADDRESS 0xB0050B00U   /* P11 base address */
#define PORT_P12_BASE_ADDRESS 0xB0050C00U   /* P12 base address */
#define PORT_P13_BASE_ADDRESS 0xB0050D00U   /* P13 base address */
#define PORT_P14_BASE_ADDRESS 0xB0050E00U   /* P14 base address */
#define PORT_P15_BASE_ADDRESS 0xB0050F00U   /* P15 base address */
#define PORT_P20_BASE_ADDRESS 0xB0051400U   /* P20 base address */
#define PORT_P21_BASE_ADDRESS 0xB0051500U   /* P21 base address */
#define PORT_P22_BASE_ADDRESS 0xB0051600U   /* P22 base address */
#define PORT_P23_BASE_ADDRESS 0xB0051700U   /* P23 base address */
#define PORT_P24_BASE_ADDRESS 0xB0051800U   /* P24 base address */
#define PORT_P25_BASE_ADDRESS 0xB0051900U   /* P25 base address */
#define PORT_P26_BASE_ADDRESS 0xB0051A00U   /* P26 base address */
#define PORT_P30_BASE_ADDRESS 0xB0051E00U   /* P30 base address */
#define PORT_P31_BASE_ADDRESS 0xB0051F00U   /* P31 base address */
#define PORT_P32_BASE_ADDRESS 0xB0052000U   /* P32 base address */
#define PORT_P33_BASE_ADDRESS 0xB0052100U   /* P33 base address */
#define PORT_P34_BASE_ADDRESS 0xB0052200U   /* P34 base address */
#define PORT_P40_BASE_ADDRESS 0xB0052800U   /* P40 base address */
#define PORT_P41_BASE_ADDRESS 0xB0052900U   /* P41 base address */
#define PORT_ESR_BASE_ADDRESS 0xB0052A00U   /* ESR base address */
#define PORT_RXMUX_BASE_ADDRESS 0xB0053000U /* RXMUX base address */

/* PORT Module Object */
#define PORT_MODULE_P00 ((PORT_MODULE *)PORT_P00_BASE_ADDRESS)            /* P00 object */
#define PORT_MODULE_P01 ((PORT_MODULE *)PORT_P01_BASE_ADDRESS)            /* P01 object */
#define PORT_MODULE_P02 ((PORT_MODULE *)PORT_P02_BASE_ADDRESS)            /* P02 object */
#define PORT_MODULE_P10 ((PORT_MODULE *)PORT_P10_BASE_ADDRESS)            /* P10 object */
#define PORT_MODULE_P11 ((PORT_MODULE *)PORT_P11_BASE_ADDRESS)            /* P11 object */
#define PORT_MODULE_P12 ((PORT_MODULE *)PORT_P12_BASE_ADDRESS)            /* P12 object */
#define PORT_MODULE_P13 ((PORT_MODULE *)PORT_P13_BASE_ADDRESS)            /* P13 object */
#define PORT_MODULE_P14 ((PORT_MODULE *)PORT_P14_BASE_ADDRESS)            /* P14 object */
#define PORT_MODULE_P15 ((PORT_MODULE *)PORT_P15_BASE_ADDRESS)            /* P15 object */
#define PORT_MODULE_P20 ((PORT_MODULE *)PORT_P20_BASE_ADDRESS)            /* P20 object */
#define PORT_MODULE_P21 ((PORT_MODULE *)PORT_P21_BASE_ADDRESS)            /* P21 object */
#define PORT_MODULE_P22 ((PORT_MODULE *)PORT_P22_BASE_ADDRESS)            /* P22 object */
#define PORT_MODULE_P23 ((PORT_MODULE *)PORT_P23_BASE_ADDRESS)            /* P23 object */
#define PORT_MODULE_P24 ((PORT_MODULE *)PORT_P24_BASE_ADDRESS)            /* P24 object */
#define PORT_MODULE_P25 ((PORT_MODULE *)PORT_P25_BASE_ADDRESS)            /* P25 object */
#define PORT_MODULE_P26 ((PORT_MODULE *)PORT_P26_BASE_ADDRESS)            /* P26 object */
#define PORT_MODULE_P30 ((PORT_MODULE *)PORT_P30_BASE_ADDRESS)            /* P30 object */
#define PORT_MODULE_P31 ((PORT_MODULE *)PORT_P31_BASE_ADDRESS)            /* P31 object */
#define PORT_MODULE_P32 ((PORT_MODULE *)PORT_P32_BASE_ADDRESS)            /* P32 object */
#define PORT_MODULE_P33 ((PORT_MODULE *)PORT_P33_BASE_ADDRESS)            /* P33 object */
#define PORT_MODULE_P34 ((PORT_MODULE *)PORT_P34_BASE_ADDRESS)            /* P34 object */
#define PORT_MODULE_P40 ((PORT_MODULE *)PORT_P40_BASE_ADDRESS)            /* P40 object */
#define PORT_MODULE_P41 ((PORT_MODULE *)PORT_P41_BASE_ADDRESS)            /* P41 object */
#define PORT_PESR ((PORT_ESR_MODULE *)PORT_ESR_BASE_ADDRESS)       /* ESR object */
#define PORT_PRXMUX ((PORT_RXMUX_MODULE *)PORT_RXMUX_BASE_ADDRESS) /* RXMUX object */

/* PORT RXMUX Module count */
#define PORT_RXMUX_MODU_CNT        34U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_RXMUX_CAN_CNT         4U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_RXMUX_I2C_CNT         2U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_RXMUX_ASI_CNT         24U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_RXMUX_SENT_CNT     25U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_RXMUX_SENT_SPC_CNT 10U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_RXMUX_PSI5_CNT     4U

/* PORT PIN */
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_PIN_INDEX_0 0U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_PIN_INDEX_1 1U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_PIN_INDEX_2 2U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_PIN_INDEX_3 3U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_PIN_INDEX_4 4U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_PIN_INDEX_5 5U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_PIN_INDEX_6 6U
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_PIN_INDEX_7 7U

/* PORT RXMUX Module Check */
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_CHECK_CAN(canId)         (((canId) < (PORT_RXMUX_CAN_CNT)) ? 1U : 0U)
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_CHECK_I2C(i2cId)         (((i2cId) < (PORT_RXMUX_I2C_CNT)) ? 1U : 0U)
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_CHECK_ASI(asiId)         (((asiId) < (PORT_RXMUX_ASI_CNT) * 4U) ? 1U : 0U)
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_CHECK_SENT(sentId)     (((sentId) < (PORT_RXMUX_SENT_CNT) * 4U) ? 1U : 0U)
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_CHECK_SENT_SPC(sentId) (((sentId) < (PORT_RXMUX_SENT_SPC_CNT) * 4U) ? 1U : 0U)
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_CHECK_PSI5(psi5Id)     (((psi5Id) < (PORT_RXMUX_PSI5_CNT) * 4U) ? 1U : 0U)
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_CHECK_LVDS(port,pin)    ((((PORT_MODULE_P13 == (port)) && ((PORT_PIN_INDEX_0 == (pin)) || (PORT_PIN_INDEX_1 == (pin)) || \
                                      (PORT_PIN_INDEX_2 == (pin)) || (PORT_PIN_INDEX_3 == (pin)) || (PORT_PIN_INDEX_4 == (pin)) || \
                                      (PORT_PIN_INDEX_5 == (pin)) || (PORT_PIN_INDEX_6 == (pin)) || (PORT_PIN_INDEX_7 == (pin)))) || \
                                      ((PORT_MODULE_P22 == (port)) && \
                                      ((PORT_PIN_INDEX_0 == (pin)) || (PORT_PIN_INDEX_1 == (pin)) || (PORT_PIN_INDEX_2 == (pin)) || \
                                      (PORT_PIN_INDEX_3 == (pin))))))

/* PORT RXMUX Module number */
#define PORT_RXMUX_ASIID_16 64U
#define PORT_RXMUX_ASIID_15 60U
#define PORT_RXMUX_ASIID_8  32U
#define PORT_RXMUX_ASIID_7  28U

#define PORT_RXMUX_CANID_0  0U
#define PORT_RXMUX_CANID_1  1U
#define PORT_RXMUX_CANID_2  2U

#define PORT_RXMUX_I2CID_0  0U

#define PORT_RXMUX_SENTID_24 96U
#define PORT_RXMUX_SENTID_23 92U
#define PORT_RXMUX_SENTID_16 64U
#define PORT_RXMUX_SENTID_15 60U
#define PORT_RXMUX_SENTID_8  32U
#define PORT_RXMUX_SENTID_7  28U

/* The PORT RXMUX module index */
/* ASI */
#define PORT_RXMUX_ASIISEL1_INDEX 27U       /* RXMUX ASIISEL1 index */
#define PORT_RXMUX_ASIISEL2_INDEX 28U       /* RXMUX ASIISEL2 index */
#define PORT_RXMUX_ASIISEL0_INDEX 6U        /* RXMUX ASIISEL index */

/* CAN */
#define PORT_RXMUX_CAN0ISEL_INDEX 0U        /* RXMUX CAN0ISEL index */
#define PORT_RXMUX_CAN1ISEL_INDEX 1U        /* RXMUX CAN1ISEL index */
#define PORT_RXMUX_CAN2ISEL_INDEX 23U       /* RXMUX CAN2ISEL index */
#define PORT_RXMUX_CAN3ISEL_INDEX 24U       /* RXMUX CAN3ISEL index */

/* I2C */
#define PORT_RXMUX_I2C0ISEL_INDEX 5U        /* RXMUX I2C0ISEL index */
#define PORT_RXMUX_I2C1ISEL_INDEX 26U       /* RXMUX I2C1ISEL index */

/* SENT */
#define PORT_RXMUX_SENTISEL0_INDEX 16U      /* RXMUX SENTISEL0 index */
#define PORT_RXMUX_SENTISEL8_INDEX 17U      /* RXMUX SENTISEL8 index */
#define PORT_RXMUX_SENTISEL16_INDEX 29U     /* RXMUX SENTISEL16 index */
#define PORT_RXMUX_SENTISEL24_INDEX 30U     /* RXMUX SENTISEL24 index */

/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_GET_ASI_INDEX(asiId)   (((PORT_RXMUX_ASIID_15) < (asiId)) ? (PORT_RXMUX_ASIISEL2_INDEX) : \
                                     (((PORT_RXMUX_ASIID_7) < (asiId)) ? (PORT_RXMUX_ASIISEL1_INDEX) : (PORT_RXMUX_ASIISEL0_INDEX)))
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_GET_ASI_OFFSET(asiId)  (((PORT_RXMUX_ASIID_15) < (asiId)) ? ((asiId) - PORT_RXMUX_ASIID_16) : \
                                     (((PORT_RXMUX_ASIID_7) < (asiId)) ? ((asiId) - PORT_RXMUX_ASIID_8) : (asiId)))

/* #Violation: tha6412_cfg_h_REF_2 */                                   
#define PORT_GET_CAN_INDEX(canId)   (((PORT_RXMUX_CANID_0) == (canId)) ? (PORT_RXMUX_CAN0ISEL_INDEX) : \
                                     (((PORT_RXMUX_CANID_1) == (canId)) ? (PORT_RXMUX_CAN1ISEL_INDEX) : \
                                     (((PORT_RXMUX_CANID_2) == (canId)) ? (PORT_RXMUX_CAN2ISEL_INDEX) : (PORT_RXMUX_CAN3ISEL_INDEX))))
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_GET_I2C_INDEX(i2cId)   (((PORT_RXMUX_I2CID_0) == (i2cId)) ? (PORT_RXMUX_I2C0ISEL_INDEX) : (PORT_RXMUX_I2C1ISEL_INDEX))
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_GET_SENT_INDEX(sentId)   (((PORT_RXMUX_SENTID_23) < (sentId)) ? (PORT_RXMUX_SENTISEL24_INDEX) : \
                                       (((PORT_RXMUX_SENTID_15) < (sentId)) ? (PORT_RXMUX_SENTISEL16_INDEX) : \
                                       (((PORT_RXMUX_SENTID_7) < (sentId)) ? (PORT_RXMUX_SENTISEL8_INDEX) : (PORT_RXMUX_SENTISEL0_INDEX))))
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_GET_SENT_OFFSET(sentId)   (((PORT_RXMUX_SENTID_23) < (sentId)) ? ((sentId) - (PORT_RXMUX_SENTID_24)) : \
                                       (((PORT_RXMUX_SENTID_15) < (sentId)) ? ((sentId) - (PORT_RXMUX_SENTID_16)) : \
                                       (((PORT_RXMUX_SENTID_7) < (sentId)) ? ((sentId) - (PORT_RXMUX_SENTID_8)) : (sentId))))
/* #Violation: tha6412_cfg_h_REF_2 */
#define PORT_GET_SENT_SPC_OFFSET(sentId) (((PORT_RXMUX_SENTID_7) < (sentId)) ? ((sentId) - (PORT_RXMUX_SENTID_8)) : (sentId))

#endif /* THA6412_CFG_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

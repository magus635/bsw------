/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    tha6104_cfg.h
 * Author:      00976
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains 6104 Chip module number and module base address definition, resource-related macro
 *              definition, etc
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#tha6104_cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: Compiler macro is defined and used followed AUTOSAR standard rule.
*
*#tha6104_cfg_h_REF_2:MISRAC2012-Dir-4.9; 
* Justification: Function like macro are used to reduce code complexity.
*/
#ifndef THA6104_CFG_H_
#define THA6104_CFG_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* INTC */
/* The largest number of GIC modules on the chip */
/* #Violation: tha6104_cfg_h_REF_1 */
#define MAX_GIC_NUM (1U)

/* INTC module base address define */
#define INTC_BASE_ADDR (0xB0040000U)
#define GIC0_BASE_ADDR  (0xF0000000U)

/* INTC GTM MAX ID*/
/* #Violation: tha6104_cfg_h_REF_1 */
#define INTC_INTID_GTM_MAXID (900U)

/* MAX CORE ID */
/* #Violation: tha6104_cfg_h_REF_1 */
#define INTC_CORE_MAXID (0U)

/* Check Soft INTID */
/* #Violation: tha6104_cfg_h_REF_1 */
#define INTC_CHECK_SPISOFT_INTID(intID) (((intID <= INTC_INTID_SOFT_INT_CORE0_3) && \
                                        (intID >= INTC_INTID_SOFT_INT_CORE0_0)) ? 1U : 0U)

/* INTC Object define */
#define INTC_HAL ((INTC_MODULE *)INTC_BASE_ADDR)
/* GIC Object */
#define GIC0 ((INTC_GIC_MODULE *)GIC0_BASE_ADDR)

/* SAC */
/* SAC module base address define */
#define SAC_BASE_ADDRESS (0xC0040400U)
#define SAC_STDBY_BASE_ADDRESS (0xD0060C00U)

/* SAC Object define */
#define SAC ((SAC_MODULE *)SAC_BASE_ADDRESS)
#define SAC_STDBY ((SAC_STDBY_MODULE *)SAC_STDBY_BASE_ADDRESS)

/* Check SAC reserved group */
/* #Violation: tha6104_cfg_h_REF_1 */
#define SAC_RESERVED_GROUP_CHECK(alarmGroup)  (((uint32)(alarmGroup) == 3U) ? 0U : 1U)

/* SAC alarm group 3 resreved in THA6104 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define SAC_RESERVED_GROUP  (3U)

/* SAC bit filed "NIMSEL" num */
/* #Violation: tha6104_cfg_h_REF_1 */
#define SAC_NMISEL_BITNUM   (3U)

/* ITMUINIT */
/* Base address of ITMUINIT module for LLPP */
/* #Violation: tha6104_cfg_h_REF_1 */
#define ITMUINIT_BASE_ADDRESS (0xC0020C00U) /* Base address of ITMUINIT module */
/* #Violation: tha6104_cfg_h_REF_1 */
#define ITMUINIT ((ITMUINIT_MODULE *)ITMUINIT_BASE_ADDRESS)

/* RCC */
/* RCC module base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_BASE_ADDR 0xC0000000U
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_CLOCK_OFFSET_ADDR 0x10U
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_RESET_OFFSET_ADDR 0x0800U
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_STB_BASE_ADDR 0xD0060400U
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_STBRESET_OFFSET_ADDR 0x0200U

/* RCC Object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_CLOCK ((RCC_CLOCK_MODULE *)(RCC_BASE_ADDR + RCC_CLOCK_OFFSET_ADDR))
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_RESET ((RCC_RESET_MODULE *)(RCC_BASE_ADDR + RCC_RESET_OFFSET_ADDR))
/* RCC STB Object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_STBCLOCK ((RCC_STBCLOCK_MODULE *)RCC_STB_BASE_ADDR)
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_STBRESET ((RCC_STBRESET_MODULE *)(RCC_STB_BASE_ADDR + RCC_STBRESET_OFFSET_ADDR))

/* RCC_CLK_SOURCE_HSE indicates HSE clock frequency */
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_CLK_SOURCE_HSE (20000000U)
/* RCC_CLK_SOURCE_HSI indicates HSI clock frequency */
/* #Violation: tha6104_cfg_h_REF_1 */
#define RCC_CLK_SOURCE_HSI (100000000U)

/* BUSPROT */
/* #Violation: tha6104_cfg_h_REF_1 */
#define BUSPROT_BASE_ADDRESS (0xC0000000U) /* Base address of BUSPROT module */

/* ECRC */
#define ECRC_BASE_ADDR (0xC0140000U)    /* ECRC module base address */
/* ECRC Object */
#define ECRC ((ECRC_MODULE *)ECRC_BASE_ADDR)

/* PWRC */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PWRC_BASE_ADDRESS (0xC0004000U) /* Base address of PWRC module */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PWRCSTBY_BASE_ADDRESS (0xD0060000U) /* Base address of PWRCSTBY module */
/* PWRC and PWRCSTB Object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PWRC ((PWRC_MODULE *)PWRC_BASE_ADDRESS)
/* #Violation: tha6104_cfg_h_REF_1 */
#define PWRCSTB ((PWRCSTB_MODULE *)PWRCSTBY_BASE_ADDRESS)

/* ETH */
/* ETH module base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define ETH_BASE_ADDR (0xC00BC000U)
/* ETH Object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define ETH ((ETH_MODULE *)ETH_BASE_ADDR)
/* Check support interface mode */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_ETH_PHY_INTERFACE_MODE(mode)(((ETH_PHY_INTERFACE_MII == (mode))) ? (1U) : (0U))
/* Check support line speed */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_ETH_LINE_SPEED(speed)(((ETH_LINESPEED_10M == (speed))) ? (1U) : (0U))
/* Check ETH channel number */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_ETH_CHANNEL(channelID) (((uint32)(channelID) < 2U) ? 1U : 0U)
/* Check the number of ETH Tx\Rx channels */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_ETH_NUMCH(numchannels) (((uint32)(numchannels) <= 2U) ? 1U : 0U)
/* Check ETH Tx DMA channel\Queue ID */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_ETH_TX_DMACH_QUEUE_ID(channelID) (((uint32)(channelID) < 2U) ? 1U : 0U)

/*BASETIMER module base address*/
/* #Violation: tha6104_cfg_h_REF_1 */
#define DUALTIMER0_BASE_ADDRESS (0xD0070000UL)
/* #Violation: tha6104_cfg_h_REF_1 */
#define DUALTIMER1_BASE_ADDRESS (0xD0098000UL)
/* #Violation: tha6104_cfg_h_REF_1 */
#define DUALTIMER2_BASE_ADDRESS (0xD00b8000UL)

/* basetimer0 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define BASETIMER0 ((BASETIMER_MODULE *)DUALTIMER0_BASE_ADDRESS)
/* basetimer1 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define BASETIMER1 ((BASETIMER_MODULE *)(DUALTIMER0_BASE_ADDRESS + 0x20U))
/* basetimer2 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define BASETIMER2 ((BASETIMER_MODULE *)DUALTIMER1_BASE_ADDRESS)
/* basetimer3 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define BASETIMER3 ((BASETIMER_MODULE *)(DUALTIMER1_BASE_ADDRESS + 0x20U))
/* basetimer4 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define BASETIMER4 ((BASETIMER_MODULE *)DUALTIMER2_BASE_ADDRESS)
/* basetimer5 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define BASETIMER5 ((BASETIMER_MODULE *)(DUALTIMER2_BASE_ADDRESS + 0x20U))
/* Check BASETIMER base address */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_BASETIMER_BASE(pTimer)                                  \
(((pTimer) == BASETIMER0) ? (1U) : (((pTimer) == BASETIMER1) ? (1U) :         \
(((pTimer) == BASETIMER2) ? (1U) : (((pTimer) == BASETIMER3) ? (1U) : (0U)))))


#define     STM_BASE_ADDRESS    (0xC0060800U)
#define     STM0             ((STM_MODULE *) STM_BASE_ADDRESS)

/*SARADC Base Address*/
#define SARADC_BASE_ADDRESS0 (0xB0000000U)
#define SARADC0 ((SARADC_MODULE *)SARADC_BASE_ADDRESS0)

#define SARADC_BASE_ADDRESS1 (0xB0000400U)
#define SARADC1 ((SARADC_MODULE *)SARADC_BASE_ADDRESS1)

#define SARADC_BASE_ADDRESS2 (0xB0000800U)
#define SARADC2 ((SARADC_MODULE *)SARADC_BASE_ADDRESS2)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SARADC_BASE_ADDRESS3 (0xB0000C00U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SARADC3 ((SARADC_MODULE *)SARADC_BASE_ADDRESS3)

/* Check SARADC base address */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_SARADC_BASE(pSaradc)                                                     \
(((pSaradc) == SARADC0) ? 1U : (((pSaradc) == SARADC1) ? 1U : (((pSaradc) == SARADC2) ? 1U : \
(((pSaradc) == SARADC3) ? 1U : 0U))))

/* Get SARADC RCC reset number */
/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_SARADC_RCC_RST_NUM(pSaradc)                                                     \
                                (((pSaradc) == SARADC0) ? RCC_MODULERST_SARADC0 :           \
                                (((pSaradc) == SARADC1) ? RCC_MODULERST_SARADC1 :           \
                                (((pSaradc) == SARADC2) ? RCC_MODULERST_SARADC2 : RCC_MODULERST_SARADC3)))

/* Check SARADC channel number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CHECK_SARADC_CHANNEL_CHECK(channelID)  ((((uint32)(channelID)) < 16U) ? 1U : 0U)
/* SARADC channel number */
#define SARADC_CHANNEL_NUM  (16U)

/* GTM base address */
#define GTM_BASE_ADDR         (0x94800000U)
#define GTM_WRAPPER_BASE_ADDR (0xC0005000U)
/* GTM object */
#define GTM_HAL          ((GTM_MODULE *)GTM_BASE_ADDR)
/* GTM WRAPPER object */
#define GTM_WRAP    ((GTM_WRAPPER *)GTM_WRAPPER_BASE_ADDR)
/* GTM cluster number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_CLUSTER_NUM (2U)
/* GTM submodule number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_ATOM_NUM  (1U)         /* ATOM module number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_TOM_NUM   (2U)         /* TOM module number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_ATOM_CH_NUM  (8U)      /* ATOM module channel number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_TOM_CH_NUM   (16U)     /* TOM module channel number */
/* GTM WRAPPER MUX number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_DMAL2_MUX_MSK (0x7FU)  /* GTM to DMA level2 MUX mask */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_DSADC_IN_MUX_NUM (0U)  /* DSADC to GTM MUX number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_DSADC_OUT_MUX_NUM (0U) /* GTM to DSADC MUX number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_DSADC_NUM     (0U)     /* DSADC module number */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GTM_TOUT_NUM  (125U)       /* GTM to GPIO TOUT number */

/* DMA */
/* DMA module base address define */
#define DMA0_BASE_ADDR (0xC00B4000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define DMA2_BASE_ADDR (0xC00B8000U)

/* DMA Object define */
#define DMA0 ((DMA_MODULE *)DMA0_BASE_ADDR)
/* #Violation: tha6104_cfg_h_REF_1 */
#define DMA2 ((DMA_MODULE *)DMA2_BASE_ADDR)

/* DMA global request lower bound */
#define DMA0_CH_NUM 4U
#define DMA2_CH_NUM 44U

/* DMA global request lower bound */
#define DMA0_GREQ_LOWER_BOUND 9U
#define DMA2_GREQ_LOWER_BOUND 26U

/* The number of DMA global request */
#define DMA0_GREQ_NUM 16U
#define DMA2_GREQ_NUM 4U

/* The number of DMA request MUX ID */
#define DMA0_GREQ_MUXID 15U
#define DMA2_GREQ_MUXID 3U

/* Check DMA base address */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_DMA_BASE(pDma)  (((pDma) == DMA0) ? 1U : \
                              (((pDma) == DMA2) ? 1U : 0U))
/* Check DMA base address and channel number */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_DMA_CH_ID(pDma, chId) ((((pDma) == DMA0) && ((chId) < DMA0_CH_NUM)) ? 1U : \
                                    ((((pDma) == DMA2) && ((chId) < DMA2_CH_NUM)) ? 1U : 0U))
/* Get DMA global request lower bound */
/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_DMA_REQ_NUM(pDma) (((pDma) == DMA0) ? DMA0_GREQ_LOWER_BOUND : DMA2_GREQ_LOWER_BOUND)
/* Get DMA global request number */
/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_DMA_GREQ_NUM(pDma) (((pDma) == DMA0) ? DMA0_GREQ_NUM : DMA2_GREQ_NUM)

/* Get DMA RCC reset number */
/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_DMA_RCC_RST_NUM(pDma) (((pDma) == DMA0) ? RCC_MODULERST_DMA0 : RCC_MODULERST_DMA2)
/* Get DMA max channel */
/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_DMA_MAX_CH(pDma)     (((pDma) == DMA0) ? DMA0_CH_NUM : DMA2_CH_NUM)
/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_DMA_MAX_MUXREQ(pDma)     (((pDma) == DMA0) ? DMA0_GREQ_MUXID : DMA2_GREQ_MUXID)

/* ES */
/* ES module base address define */
#define ES_BASE_ADDR (0xC0040000U)
/* ES Object define */
#define ES ((ES_MODULE *)ES_BASE_ADDR)

/* EXTI */
/* EXTI module base address define */
#define EXTI_BASE_ADDRESS (0xC000460CU)
/* EXTI Object define */
#define EXTI ((EXTI_MODULE *)EXTI_BASE_ADDRESS)

/* FLASH */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_CLUSTER_NUM  (1U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_PFLASH_NUM_PER_CLUSTER   (2U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_MAX_CLOCK (150000000U)

/* PFLASH Internal address to Device address offset */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_PFLASH_INTERNALTODEVICE_ADDR_OFFSET (0x88400000U)

/* PFLASH Internal address mask value */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_PFLASH_INTERNALADDR_MASKVALUE (0xFFC00000ULL)

/* PFLASH Internal address compare value */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_PFLASH_INTERNALADDR_COMPVALUE (0x08000000ULL)

/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STO0_FACTOR (1000000U) /* flash sto0 desired value(1us) */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STO1_DESIRE (70U)     /* flash sto1 desired value70ns */

/* FLASH Features*/
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DFLASH_PWORD_SIZE                 (16U)           /*smallest unit that can be programmed in the Dflash */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DFLASH_MAX_PWORD_SIZE             (128U)          /*maximum unit that can be programmed in the Dflash */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DFLASH_SECTOR_SIZE                (64U * FLASH_DFLASH_PWORD_SIZE)  /* bytes per sector in the Dflash*/
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DFLASH_SECTOR_NUM                 (256U)            /* sector number in the Dflash*/

/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_PFLASH_PWORD_SIZE                 (64U)           /*smallest unit that can be programmed in the Pflash */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_PFLASH_MAX_PWORD_SIZE             (256U)          /*maximum unit that can be programmed in the Pflash */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_PFLASH_SECTOR_SIZE                (128U * FLASH_PFLASH_PWORD_SIZE) /* bytes per sector in the Pflash*/
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_PFLASH_SECTOR_NUM                 (256U)          /* sector number in the Pflash*/
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_PFLASH_SECTOR_NUM_INBLOCK         (16U)          /* sector number in the Blcok*/

/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_START_ADDR           (0x94000000U)   /* Start address of the DFLASH */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_END_ADDR             (0x9403FFFFU)   /* End address of the DFLASH */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_INFO0_START_ADDR     (0x94400000U)   /* Start address of the DFLASH INFO0 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_INFO0_END_ADDR       (0x94403FFFU)   /* End address of the DFLASH INFO0 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_START_ADDR           (0x90400000U)   /* Start address of the PFLASH0 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_END_ADDR             (0x905FFFFFU)   /* End address of the PFLASH0 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_INFO0_START_ADDR     (0x91C00000U)   /* Start address of the PFLASH0 INFO0 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_INFO0_END_ADDR       (0x91C03FFFU)   /* End address of the PFLASH0 INFO0 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_START_ADDR           (0x90600000U)   /* Start address of the PFLASH1 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_END_ADDR             (0x907FFFFFU)   /* End address of the PFLASH1 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_INFO0_START_ADDR     (0x91C04000U)   /* Start address of the PFLASH1 INFO0 */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_INFO0_END_ADDR       (0x91C07FFFU)   /* End address of the PFLASH1 INFO0 */

/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_ERSF_MSK     (0x1)       /* Erase Finished Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_ERSE_MSK     (0x2)       /* Erase Error Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_PROGF_MSK    (0x4)       /* Program Finished Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_PROGE_MSK    (0x8)       /* Program Error Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_ECF_MSK       (0x10)      /* Erase Check Finished Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_ECSTS_MSK    (0x20)      /* Erase Check Result Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_CF_MSK       (0x100)     /* Cancel Finish Redundancy Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_CDF_MSK      (0x400)     /* Cancel Finish Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_ESQE_MSK     (0x10000)   /* Erase Sequence Error Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_MISAE_MSK    (0x40000)   /* Program Miss Align Error Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_POVT_MSK     (0x100000)  /* Program Overtime Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_ERSBUSY_MSK  (0x1000000) /* FLASH Current Erase Operation Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_PROGBUSY_MSK (0x2000000) /* FLASH Current Program Operation Status */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_STS_ECBUSY_MSK   (0x4000000) /* FLASH Current Erase Check Operation Status */

/* #Violation: tha6104_cfg_h_REF_2 */
#define DFLASH_CALCULATE_RDT(uClockFreq) ((float32)((((float32)(uClockFreq) / 1000000.0f * 4.0f) / 100.0f) - 2.0f))
/* #Violation: tha6104_cfg_h_REF_2 */
#define PFLASH_CALCULATE_RDT(uClockFreq) ((float32)((((float32)(uClockFreq) / 1000000.0f * 8.0f) / 300.0f) - 2.0f))

/* #Violation: tha6104_cfg_h_REF_1 */
#define CHECK_DFLASH_INFO_ADD 1U

#if (CHECK_DFLASH_INFO_ADD == 1U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_INFO_START_ADDR     FLASH_DEVICE_DFLASH0_INFO0_START_ADDR
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_DFLASH0_INFO_END_ADDR       FLASH_DEVICE_DFLASH0_INFO0_END_ADDR
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_DFLASH_ADDRESS(addr)   (  ((  ((addr) <= FLASH_DEVICE_DFLASH0_END_ADDR) && \
                                            ((addr) >= FLASH_DEVICE_DFLASH0_START_ADDR)) || \
                                         (  ((addr) <= FLASH_DEVICE_DFLASH0_INFO_END_ADDR) && \
                                            ((addr) >= FLASH_DEVICE_DFLASH0_INFO_START_ADDR)) \
                                        ) ? 1U : 0U)

#elif (CHECK_DFLASH_INFO_ADD == 0U)
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_DFLASH_ADDRESS(addr)     ((((addr) <= FLASH_DEVICE_DFLASH0_END_ADDR) && \
                                        ((addr) >= FLASH_DEVICE_DFLASH0_START_ADDR)) ? \
                                        1U : 0U)

#endif


/* FLASH module base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_CLUSTER0_BASE_ADDRESS (0xC0100000U)
/* #Violation: tha6104_cfg_h_REF_2 */
#define FLASH_GET_COMMON_STS_FROM_PININPUT(pPININPUT) (FLASH_CLUSTER0_STS)

/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_PFLASH_INFO_ADD 1U

#if (CHECK_PFLASH_INFO_ADD == 1U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_INFO_START_ADDR     FLASH_DEVICE_PFLASH0_INFO0_START_ADDR
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH0_INFO_END_ADDR       FLASH_DEVICE_PFLASH0_INFO0_END_ADDR

/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_INFO_START_ADDR     FLASH_DEVICE_PFLASH1_INFO0_START_ADDR
/* #Violation: tha6104_cfg_h_REF_1 */
#define FLASH_DEVICE_PFLASH1_INFO_END_ADDR       FLASH_DEVICE_PFLASH1_INFO0_END_ADDR

#endif

/* #Violation: tha6104_cfg_h_REF_1 */
#define GET_PFLASH_CTR_FROM_ADDR(addr) \
                            ((((addr) >= FLASH_DEVICE_PFLASH0_START_ADDR)&&((addr) <= FLASH_DEVICE_PFLASH0_END_ADDR)) ? FLASH_PFLASH0_CTR : \
                            ((((addr) >= FLASH_DEVICE_PFLASH1_START_ADDR)&&((addr) <= FLASH_DEVICE_PFLASH1_END_ADDR)) ? FLASH_PFLASH1_CTR : (FLASH_CTR_MODULE *)NULL_PTR))

/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_PFLASH_STS_FROM_CTR(pCTR) \
                                      (((pCTR) == FLASH_PFLASH0_CTR) ? FLASH_PFLASH0_STS : FLASH_PFLASH1_STS)
/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_PFLASH_MSK_FROM_CTR(pCTR) \
                            (((pCTR) == FLASH_PFLASH0_CTR) ? FLASH_PFLASH0_MSK : FLASH_PFLASH1_MSK)
/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_CLUSTER_CTR(index) (FLASH_CLUSTER0_CTR)
/* #Violation: tha6104_cfg_h_REF_2 */
#define GET_BUFCFG_FROM_CLUSTER(culster)  (FLASH_COMMON_BUFCFG_MODULE*)(((uint32)culster) + FLASH_COMMON_PF0BUFCFG_OFFSET)

/* CPUWDT */
/* CPUWDT module base address define */
#define CPUWDT_BASE_ADDR (0xC0070000U)
/* CPUWDT Object define */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CPUWDT(coreId) ((CPUWDT_MODULE *)(CPUWDT_BASE_ADDR + (0x400U * (uint32)(coreId))))

/* SAFEWDT */
/* SAFEWDT module base address define */
#define SAFEWDT_BASE_ADDR (0xC0040800U)
/* SAFEWDT Object define */
#define SAFEWDT_HAL ((SAFEWDT_MODULE *)SAFEWDT_BASE_ADDR)

/* ESPI */
/* ESPI0 module base address define */
#define ESPI0_BASE_ADDRESS (0xC0080000U)
/* ESPI1 module base address define */
#define ESPI1_BASE_ADDRESS (0xC0080400U)
/* ESPI2 module base address define */
#define ESPI2_BASE_ADDRESS (0xC0080800U)
/* ESPI3 module base address define */
#define ESPI3_BASE_ADDRESS (0xD0020000U)
/* ESPI4 module base address define */
#define ESPI4_BASE_ADDRESS (0xD0020400U)
/* ESPI5 module base address define */
#define ESPI5_BASE_ADDRESS (0xC0600000U)
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
/* Check ESPI base address */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_ESPI_BASE(pEspi)                                                                                      \
(((pEspi) == ESPI0) ? 1U : (((pEspi) == ESPI1) ? 1U : (((pEspi) == ESPI2) ? 1U :                                          \
(((pEspi) == ESPI3) ? 1U : (((pEspi) == ESPI4) ? 1U : (((pEspi) == ESPI5) ? 1U : 0U))))))
/* #Violation: tha6104_cfg_h_REF_2 */
#define ESPI_GET_RCC_RST_NUM(pEspi) \
                                    (((ESPI0 == (pEspi))  ? RCC_MODULERST_ESPI0 :  \
                                    ((ESPI1 == (pEspi))  ? RCC_MODULERST_ESPI1 :  \
                                    ((ESPI2 == (pEspi))  ? RCC_MODULERST_ESPI2 :  \
                                    ((ESPI3 == (pEspi))  ? RCC_MODULERST_ESPI3 :  \
                                    ((ESPI4 == (pEspi))  ? RCC_MODULERST_ESPI4 :  \
                                    ((ESPI5 == (pEspi)) ? RCC_MODULERST_ESPI5 : RCC_MODULERST_MAX)))))))

/* OVC */
/* OVC module base address define */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_BASE_ADDR (0xC00C4000U)
/* OVC Object define */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC0 ((OVC_MODULE *)OVC_BASE_ADDR)
/* Check OVC base address */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_OVC_BASE(pOvc) ((pOvc) == OVC0)
/* Check OVC coreID */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CHECK_OVC_CORE(id) (((id) < 1U) ? 1U : 0U)

/* Target address : Memory domain Program Flash0 via MBUS AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_PF0_START_ADDR (0x40400000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_PF0_END_ADDR (0x405FFFFFU)

/* Target address : Device domain Program Flash0 via MBUS AXI Slave start address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_PF0_START_ADDR (0x90400000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_PF0_END_ADDR (0x905FFFFFU)

/* Target address : Memory domain Program Flash1 via MBUS AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_PF1_START_ADDR (0x40600000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_PF1_END_ADDR (0x407FFFFFU)

/* Target address : Device domain Program Flash1 via MBUS AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_PF1_START_ADDR (0x90600000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_PF1_END_ADDR (0x907FFFFFU)

/* Target address : Memory domain Data Flash via MBUS AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_DF_START_ADDR (0x44000000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_DF_END_ADDR (0x4403FFFFU)

/* Target address : Memory domain Data Flash NVR via MBUS AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_DF_INFO0_START_ADDR (0x44400000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_DF_INFO0_END_ADDR (0x44403FFFU)

/* Target address : Memory domain Data Flash NVR_CFG via MBUS AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_DF_INFO1_START_ADDR (0x44408000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_DF_INFO1_END_ADDR (0x44408FFFU)

/* Target address : Device domain Data Flash via MBUS AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_DF_START_ADDR (0x94000000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_DF_END_ADDR (0x9403FFFFU)

/* Target address : Device domain Data Flash NVR via MBUS AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_DF_INFO0_START_ADDR (0x94400000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_DF_INFO0_END_ADDR (0x94403FFFU)

/* Target address : Device domain Data Flash NVR_CFG via MBUS AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_DF_INFO1_START_ADDR (0x94408000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_DF_INFO1_END_ADDR (0x94408FFFU)

/* Overlay address: Memory domain CPU0 ATCM via AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_CPU0_ATCM_START_ADDR (0x30000000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_CPU0_ATCM_END_ADDR (0x30007FFFU)

/* Overlay address: Memory domain CPU0 BTCM via AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_CPU0_BTCM_START_ADDR (0x30100000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_CPU0_BTCM_END_ADDR (0x3013FFFFU)

/* Overlay address: Memory domain CPU0 CTCM via AXI Slave address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_CPU0_CTCM_START_ADDR (0x30200000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MEM_CPU0_CTCM_END_ADDR (0x3021FFFFU)

/* Overlay address: Main domain GMU0 start address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MAIN_GMU0_START_ADDR (0x10000000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_MAIN_GMU0_END_ADDR (0x10013FFFU)

/* Overlay address: Device domain GMU0 start address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_GMU0_START_ADDR (0x82000000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define OVC_DEV_GMU0_END_ADDR (0x82013FFFU)

/* check if an address is within any of the defined memory regions */
/* #Violation: tha6104_cfg_h_REF_2 */
#define OVC_CHECK_TARGET_ADDRESS_REGION(Taradd) \
( (((Taradd) >= OVC_MEM_PF0_START_ADDR) && ((Taradd) <= OVC_MEM_PF0_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_PF0_START_ADDR) && ((Taradd) <= OVC_DEV_PF0_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_PF1_START_ADDR) && ((Taradd) <= OVC_MEM_PF1_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_PF1_START_ADDR) && ((Taradd) <= OVC_DEV_PF1_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_DF_START_ADDR) && ((Taradd) <= OVC_MEM_DF_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_DF_INFO0_START_ADDR) && ((Taradd) <= OVC_MEM_DF_INFO0_END_ADDR)) || \
 (((Taradd) >= OVC_MEM_DF_INFO1_START_ADDR) && ((Taradd) <= OVC_MEM_DF_INFO1_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_DF_START_ADDR) && ((Taradd) <= OVC_DEV_DF_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_DF_INFO0_START_ADDR) && ((Taradd) <= OVC_DEV_DF_INFO0_END_ADDR)) || \
 (((Taradd) >= OVC_DEV_DF_INFO1_START_ADDR) && ((Taradd) <= OVC_DEV_DF_INFO1_END_ADDR)) )

/* #Violation: tha6104_cfg_h_REF_2 */
#define OVC_CHECK_OVERLAY_ADDRESS_REGION(Oveadd) \
( (((Oveadd) >= OVC_MEM_CPU0_ATCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU0_ATCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU0_BTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU0_BTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MEM_CPU0_CTCM_START_ADDR) && ((Oveadd) <= OVC_MEM_CPU0_CTCM_END_ADDR)) || \
 (((Oveadd) >= OVC_MAIN_GMU0_START_ADDR) && ((Oveadd) <= OVC_MAIN_GMU0_END_ADDR)) || \
 (((Oveadd) >= OVC_DEV_GMU0_START_ADDR) && ((Oveadd) <= OVC_DEV_GMU0_END_ADDR)) )

/* TSENSOR */
/* TSENSOR0 module base address define */
#define TSENSOR0_BASE_ADDRESS (0xC00E0000U)
/* TSENSOR0 module base address define */
/* #Violation: tha6104_cfg_h_REF_1 */
#define TSENSOR1_BASE_ADDRESS (0xC00E0400U)
/* TSENSOR0 Object define */
#define TSENSOR0 ((TSENSOR_MODULE *)TSENSOR0_BASE_ADDRESS)
/* TSENSOR0 Object define */
/* #Violation: tha6104_cfg_h_REF_1 */
#define TSENSOR1 ((TSENSOR_MODULE *)TSENSOR1_BASE_ADDRESS)
/* Check TSENSOR base address */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_TSENSOR_BASE(pTsensor) (((pTsensor) == TSENSOR0) ? 1U : (((pTsensor) == TSENSOR1) ? 1U : 0U))

/* MSC */
/* Check MSC base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CHECK_MSC_BASE(pMsc) (0U)

/* I2C */
/* I2C module base address define */
#define I2C_BASE_ADDR (0xD009A000U)
/* I2C Object define */
#define I2C0 ((I2C_MODULE *)(I2C_BASE_ADDR + 0x0U))
/* I2C Object define */
/* #Violation: tha6104_cfg_h_REF_1 */
#define I2C1 ((I2C_MODULE *)(I2C_BASE_ADDR + 0x400U))
/* Check I2C base address */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_I2C_BASE(pI2c) (((pI2c) == I2C0) ? 1U : (((pI2c) == I2C1) ? 1U : 0U))

/* CAN */
/* CAN module base address define */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN0_BASE_ADDR                (0xC0090000UL)
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN1_BASE_ADDR                (0xD0000000UL)

/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN0_BASE_LLPP_ADDR          (0xB0390000UL)
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN1_BASE_LLPP_ADDR          (0xB03E0000UL)

/* CAN Object define--AXIM bus access and communication */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN0                         ((CAN_MODULE *)CAN0_BASE_ADDR)
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN1                         ((CAN_MODULE *)CAN1_BASE_ADDR)

/* CAN Object define--LLPP bus access and communication */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN0_LLPP                     ((CAN_MODULE *)CAN0_BASE_LLPP_ADDR)
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN1_LLPP                     ((CAN_MODULE *)CAN1_BASE_LLPP_ADDR)

/* CAN node offset address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN_NODE0_OFFSET_ADDR         (0x00000000UL)
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN_NODE1_OFFSET_ADDR         (0x00001800UL)
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN_NODE2_OFFSET_ADDR         (0x00003000UL)
    
/* CAN00/01/02 node object */    
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN00                         ((CAN_NODE *)(CAN0_BASE_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN01                         ((CAN_NODE *)(CAN0_BASE_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN02                         ((CAN_NODE *)(CAN0_BASE_ADDR + CAN_NODE2_OFFSET_ADDR))
                        
/* CAN10/11/12 node object */    
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN10                         ((CAN_NODE *)(CAN1_BASE_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN11                         ((CAN_NODE *)(CAN1_BASE_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN12                         ((CAN_NODE *)(CAN1_BASE_ADDR + CAN_NODE2_OFFSET_ADDR))

/* CAN00/01/02 node object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN00_LLPP                     ((CAN_NODE *)(CAN0_BASE_LLPP_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN01_LLPP                     ((CAN_NODE *)(CAN0_BASE_LLPP_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN02_LLPP                     ((CAN_NODE *)(CAN0_BASE_LLPP_ADDR + CAN_NODE2_OFFSET_ADDR))
                                                            
/* CAN10/11/12 node    object */     
/* #Violation: tha6104_cfg_h_REF_1 */       
#define CAN10_LLPP                     ((CAN_NODE *)(CAN1_BASE_LLPP_ADDR + CAN_NODE0_OFFSET_ADDR))
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN11_LLPP                     ((CAN_NODE *)(CAN1_BASE_LLPP_ADDR + CAN_NODE1_OFFSET_ADDR))
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN12_LLPP                     ((CAN_NODE *)(CAN1_BASE_LLPP_ADDR + CAN_NODE2_OFFSET_ADDR))

/* Get node index in CAN module */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CAN_NODE_MAX_IN_MODULE      (3U)
/* #Violation: tha6104_cfg_h_REF_2 */
#define CAN_NODE_INDEX(pNode)       (((((uint32)(pNode) & (0x0000FF00UL)) == CAN_NODE0_OFFSET_ADDR) ? 0U : \
                                     ((((uint32)(pNode) & (0x0000FF00UL)) == CAN_NODE1_OFFSET_ADDR) ? 1U : \
                                     ((((uint32)(pNode) & (0x0000FF00UL)) == CAN_NODE2_OFFSET_ADDR) ? 2U : 0xFFFFFFFFU))))

/* Check CAN node base address */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_CANNODE_BASE(pNode)                                                                                        \
(((pNode) == CAN00) ? 1U : (((pNode) == CAN01) ? 1U : (((pNode) == CAN02) ? 1U :                                         \
(((pNode) == CAN10) ? 1U : (((pNode) == CAN11) ? 1U : (((pNode) == CAN12) ? 1U :                                         \
(((pNode) == CAN00_LLPP) ? 1U : (((pNode) == CAN01_LLPP) ? 1U : (((pNode) == CAN02_LLPP) ? 1U :                          \
(((pNode) == CAN10_LLPP) ? 1U : (((pNode) == CAN11_LLPP) ? 1U : (((pNode) == CAN12_LLPP) ? 1U : 0U))))))))))))

/* SENT */
/* SENT module base address define */
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT_BASE_ADDR0             (0xD0090000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT_BASE_ADDR1             (0xD0090400U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT_BASE_ADDR2             (0xD0090800U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT_BASE_ADDR3             (0xD0090C00U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT_BASE_ADDR4             (0xD0091000U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT_BASE_ADDR5             (0xD00B0000U)
    
/* SENT Object define */    
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT0                       ((SENT_MODULE *)SENT_BASE_ADDR0)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT1                       ((SENT_MODULE *)SENT_BASE_ADDR1)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT2                       ((SENT_MODULE *)SENT_BASE_ADDR2)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT3                       ((SENT_MODULE *)SENT_BASE_ADDR3)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT4                       ((SENT_MODULE *)SENT_BASE_ADDR4)
/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT5                       ((SENT_MODULE *)SENT_BASE_ADDR5)

/* #Violation: tha6104_cfg_h_REF_1 */
#define SENT_GET_RCC_RST_NUM(pSentModule) \
                                    (((SENT0 == (pSentModule))  ? RCC_MODULERST_SENT0 :  \
                                     ((SENT1 == (pSentModule))  ? RCC_MODULERST_SENT1 :  \
                                     ((SENT2 == (pSentModule))  ? RCC_MODULERST_SENT2 :  \
                                     ((SENT3 == (pSentModule))  ? RCC_MODULERST_SENT3 :  \
                                     ((SENT4 == (pSentModule))  ? RCC_MODULERST_SENT4 :  \
                                     ((SENT5 == (pSentModule))  ? RCC_MODULERST_SENT5 :  RCC_MODULERST_MAX)))))))
    
/* SENT-Check the legality of the module */
/* #Violation: tha6104_cfg_h_REF_2 */
#define SENT_CHECK_MODULE(pSentModule) \
                                    (((SENT0 == (pSentModule))  || (SENT1 == (pSentModule))  || (SENT2 == (pSentModule))  || \
                                      (SENT3 == (pSentModule))  || (SENT4 == (pSentModule))  || (SENT5 == (pSentModule))) ? 1U : 0U)
                                      
/* ASI */    
/* ASI module base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define ASI_BASE_ADDR                   (0xD0080000U)
#define ASI0_BASE_ADDR                  (0xD0080000U)
#define ASI1_BASE_ADDR                  (0xD0080400U)
#define ASI2_BASE_ADDR                  (0xD0080800U)
#define ASI3_BASE_ADDR                  (0xD0080C00U)
#define ASI4_BASE_ADDR                  (0xD00A0000U)
#define ASI5_BASE_ADDR                  (0xD00A0400U)
#define ASI6_BASE_ADDR                  (0xD00A0800U)
#define ASI7_BASE_ADDR                  (0xD00A0C00U)
#define ASI8_BASE_ADDR                  (0xD0081000U)
#define ASI9_BASE_ADDR                  (0xD0081400U)
#define ASI10_BASE_ADDR                 (0xD0081800U)
#define ASI11_BASE_ADDR                 (0xD00A1000U)
            
/* ASI Object */    
#define ASI0                         ((ASI_MODULE *)(ASI0_BASE_ADDR))
#define ASI1                         ((ASI_MODULE *)(ASI1_BASE_ADDR))
#define ASI2                         ((ASI_MODULE *)(ASI2_BASE_ADDR))
#define ASI3                         ((ASI_MODULE *)(ASI3_BASE_ADDR))
#define ASI4                         ((ASI_MODULE *)(ASI4_BASE_ADDR))
#define ASI5                         ((ASI_MODULE *)(ASI5_BASE_ADDR))
#define ASI6                         ((ASI_MODULE *)(ASI6_BASE_ADDR))
#define ASI7                         ((ASI_MODULE *)(ASI7_BASE_ADDR))
#define ASI8                         ((ASI_MODULE *)(ASI8_BASE_ADDR))
#define ASI9                         ((ASI_MODULE *)(ASI9_BASE_ADDR))
#define ASI10                         ((ASI_MODULE *)(ASI10_BASE_ADDR))
#define ASI11                         ((ASI_MODULE *)(ASI11_BASE_ADDR))
/* #Violation: tha6104_cfg_h_REF_2 */               
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
                                     ((ASI11 == (pAsiModule)) ? RCC_MODULERST_ASI11 : RCC_MODULERST_MAX)))))))))))))

/* IOM */
/* IOM module base address */
#define IOM_BASE_ADDR (0xB0058000U)
/* IOM module base address */
#define IOM ((IOM_MODULE*)IOM_BASE_ADDR)

/* GMU */
/* GMU0 module base address define */
#define GMU0_BASE_ADDR (0xC0060000U)
/* GMU0 Object define */
#define GMU0 ((GMU_MODULE *)GMU0_BASE_ADDR)
/* GMU MEMSTS Register offset address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GMU_MEMSTS_OFFSET_ADDR (0x20)

/* Check GMU base address */
/* #Violation: tha6104_cfg_h_REF_2 */
#define CHECK_GMU_BASE(pGmu) (((pGmu) == GMU0) ? 1U : 0U)
/* Get gmu clock number */
/* #Violation: tha6104_cfg_h_REF_2 */
#define GMU_RCC_MODULECLK_NUM(pDma) (((pDma) == GMU0) ? RCC_MODULECLKTYPE_GMU0CLK : ((Rcc_ModuleClkType)0U))

/* GMU group number check */
/* #Violation: tha6104_cfg_h_REF_1 */
#define GMU_GROUP_NUMBER_CHECK(Group) (((uint32)(Group) <= 3U) ? 1U : 0U)

/* LMU */
/* LMU2 module base address define */
/* #Violation: tha6104_cfg_h_REF_1 */
#define LMU2_BASE_ADDR (0xC0060400)
/* LMU MEMSTS Register offset address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define LMU_MEMSTS_OFFSET_ADDR (0x24)

/* PORT */
/* PORT base address define */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P00_BASE_ADDRESS 0xB0050000U   /* P00 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P02_BASE_ADDRESS 0xB0050200U   /* P02 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P10_BASE_ADDRESS 0xB0050A00U   /* P10 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P11_BASE_ADDRESS 0xB0050B00U   /* P11 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P13_BASE_ADDRESS 0xB0050D00U   /* P13 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P14_BASE_ADDRESS 0xB0050E00U   /* P14 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P15_BASE_ADDRESS 0xB0050F00U   /* P15 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P20_BASE_ADDRESS 0xB0051400U   /* P20 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P21_BASE_ADDRESS 0xB0051500U   /* P21 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P22_BASE_ADDRESS 0xB0051600U   /* P22 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P23_BASE_ADDRESS 0xB0051700U   /* P23 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P32_BASE_ADDRESS 0xB0052000U   /* P32 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P33_BASE_ADDRESS 0xB0052100U   /* P33 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P34_BASE_ADDRESS 0xB0052200U   /* P34 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P40_BASE_ADDRESS 0xB0052800U   /* P40 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_P41_BASE_ADDRESS 0xB0052900U   /* P41 base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_ESR_BASE_ADDRESS 0xB0052A00U   /* ESR base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_RXMUX_BASE_ADDRESS 0xB0053000U /* RXMUX base address */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_RXMUX_EXTI_BASE_ADDRESS (0xB00530F8U) /* RXMUX EXTI base address */

/* PORT Module Object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P00 ((PORT_MODULE *)PORT_P00_BASE_ADDRESS)            /* P00 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P02 ((PORT_MODULE *)PORT_P02_BASE_ADDRESS)            /* P02 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P10 ((PORT_MODULE *)PORT_P10_BASE_ADDRESS)            /* P10 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P11 ((PORT_MODULE *)PORT_P11_BASE_ADDRESS)            /* P11 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P13 ((PORT_MODULE *)PORT_P13_BASE_ADDRESS)            /* P13 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P14 ((PORT_MODULE *)PORT_P14_BASE_ADDRESS)            /* P14 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P15 ((PORT_MODULE *)PORT_P15_BASE_ADDRESS)            /* P15 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P20 ((PORT_MODULE *)PORT_P20_BASE_ADDRESS)            /* P20 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P21 ((PORT_MODULE *)PORT_P21_BASE_ADDRESS)            /* P21 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P22 ((PORT_MODULE *)PORT_P22_BASE_ADDRESS)            /* P22 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P23 ((PORT_MODULE *)PORT_P23_BASE_ADDRESS)            /* P23 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P32 ((PORT_MODULE *)PORT_P32_BASE_ADDRESS)            /* P32 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P33 ((PORT_MODULE *)PORT_P33_BASE_ADDRESS)            /* P33 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P34 ((PORT_MODULE *)PORT_P34_BASE_ADDRESS)            /* P34 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P40 ((PORT_MODULE *)PORT_P40_BASE_ADDRESS)            /* P40 object */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_MODULE_P41 ((PORT_MODULE *)PORT_P41_BASE_ADDRESS)            /* P41 object */
#define PORT_PESR ((PORT_ESR_MODULE *)PORT_ESR_BASE_ADDRESS)              /* ESR object */
#define PORT_PRXMUX ((PORT_RXMUX_MODULE *)PORT_RXMUX_BASE_ADDRESS)        /* RXMUX object */
#define PORT_PRXMUX_EXTI ((RXMUX_INSEL *)PORT_RXMUX_EXTI_BASE_ADDRESS)    /* EXTI MUX object */

/* PORT RXMUX Module count */
#define PORT_RXMUX_MODU_CNT 35U
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_RXMUX_CAN_CNT 2U
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_RXMUX_I2C_CNT 2U
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_RXMUX_ASI_CNT 12U
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_RXMUX_SENT_CNT 6U
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_RXMUX_PSI5_CNT 0U

/* PORT RXMUX Module Check */
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_CHECK_CAN(canId)               (((canId) < (PORT_RXMUX_CAN_CNT)) ? 1U : 0U)
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_CHECK_I2C(i2cId)               (((i2cId) < (PORT_RXMUX_I2C_CNT)) ? 1U : 0U)
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_CHECK_ASI(asiId)               (((asiId) < ((PORT_RXMUX_ASI_CNT) * 4U)) ? 1U : 0U)
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_CHECK_SENT(sentId)           (((sentId) < ((PORT_RXMUX_SENT_CNT) * 4U)) ? 1U : 0U)
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_CHECK_SENT_SPC(sentId)       (((sentId) < ((PORT_RXMUX_SENT_CNT) * 4U)) ? 1U : 0U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_CHECK_PSI5(psi5Id)           (0U)
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_CHECK_LVDS(port,pin)          (0U)

/* PORT RXMUX Module number */
#define PORT_RXMUX_ASIID_7  28U
#define PORT_RXMUX_ASIID_8  32U
#define PORT_RXMUX_CANID_0  0U
#define PORT_RXMUX_I2CID_0  0U

/* The PORT RXMUX module index */
/* ASI */
#define PORT_RXMUX_ASIISEL1_INDEX 27U       /* RXMUX ASIISEL1 index */
#define PORT_RXMUX_ASIISEL0_INDEX 6U        /* RXMUX ASIISEL index */

/* CAN */
#define PORT_RXMUX_CAN0ISEL_INDEX 0U        /* RXMUX CAN0ISEL index */
#define PORT_RXMUX_CAN1ISEL_INDEX 1U        /* RXMUX CAN1ISEL index */

/* I2C */
#define PORT_RXMUX_I2C0ISEL_INDEX 5U        /* RXMUX I2C0ISEL index */
#define PORT_RXMUX_I2C1ISEL_INDEX 26U       /* RXMUX I2C1ISEL index */

/* SENT */
#define PORT_RXMUX_SENTISEL0_INDEX 16U      /* RXMUX SENTISEL0 index */
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_GET_ASI_INDEX(asiId)     ((((PORT_RXMUX_ASIID_7) < (asiId)) ? (PORT_RXMUX_ASIISEL1_INDEX) : (PORT_RXMUX_ASIISEL0_INDEX)))      
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_GET_ASI_OFFSET(asiId)    ((((PORT_RXMUX_ASIID_7) < (asiId)) ? ((asiId) - PORT_RXMUX_ASIID_8) : (asiId)))   
/* #Violation: tha6104_cfg_h_REF_2 */                         
#define PORT_GET_CAN_INDEX(canId)     (((PORT_RXMUX_CANID_0) == (canId)) ? (PORT_RXMUX_CAN0ISEL_INDEX) : (PORT_RXMUX_CAN1ISEL_INDEX))
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_GET_I2C_INDEX(i2cId)     (((PORT_RXMUX_I2CID_0) == (i2cId)) ? (PORT_RXMUX_I2C0ISEL_INDEX) : (PORT_RXMUX_I2C1ISEL_INDEX))
#define PORT_GET_SENT_INDEX(sentId)   (PORT_RXMUX_SENTISEL0_INDEX)
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_GET_SENT_OFFSET(sentId)   (sentId)
/* #Violation: tha6104_cfg_h_REF_2 */
#define PORT_GET_SENT_SPC_OFFSET(sentId)   (sentId)
/* Check IOM input pin select index */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_CHECK_IOM_INPUT_SELECT(iomPin, inputSel) ((((13U == (iomPin)) && ((inputSel) <= 1U))) || \
                                                       (((14U == (iomPin)) && ((inputSel) <= 1U))) || \
                                                       (((15U == (iomPin)) && ((inputSel) <= 1U))))
/* Check EXTI input pin select index */
/* #Violation: tha6104_cfg_h_REF_1 */
#define PORT_CHECK_EXTI_INPUT_SELECT(extiPin, inputSel) ((((0U == (extiPin)) && ((inputSel) <= 1U))))

/* PWRC */
#define PWRC_BASE_ADDRESS (0xC0004000U) /* Base address of PWRC module */
#define PWRCSTBY_BASE_ADDRESS (0xD0060000U) /* Base address of PWRCSTBY module */
/* PWRC and PWRCSTB Object */
#define PWRC ((PWRC_MODULE *)PWRC_BASE_ADDRESS)
#define PWRCSTB ((PWRCSTB_MODULE *)PWRCSTBY_BASE_ADDRESS)


/* GIPC(just for compile) */
/* #Violation: tha6104_cfg_h_REF_1 */
#define CHECK_GIPC_BASE(pGipc) (0U)
#endif /* THA6104_CFG_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

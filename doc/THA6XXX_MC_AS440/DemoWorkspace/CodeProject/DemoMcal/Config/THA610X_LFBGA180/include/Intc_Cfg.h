/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Intc_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Intc
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Intc_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Intc_Cfg_h_REF_2:CertC-PRE00-C;
* Justification:Function like macros are used to reduce code complexity.
*
*/

/**************************************************************************************************/
#ifndef INTC_CFG_H_
#define INTC_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define INTC_CFG_AR_RELEASE_MAJOR_VERSION                      (4U)
#define INTC_CFG_AR_RELEASE_MINOR_VERSION                      (4U)
#define INTC_CFG_AR_RELEASE_REVISION_VERSION                   (0U)

#define INTC_CFG_SW_MAJOR_VERSION                              (1U)
#define INTC_CFG_SW_MINOR_VERSION                              (2U)
#define INTC_CFG_SW_PATCH_VERSION                              (0U)

#define INTC_CFG_VENDOR_ID                                     (175U)
#define INTC_CFG_MODULE_ID                                      (255U)

/*
Configuration: IntcDevErrorDetect
- if Selected, DET is Enabled 
- if Deselected, DET is Disabled 
*/
#define INTC_DEV_ERROR_DETECT                                  (STD_ON)


/*
Configuration: IntcVersionInfoApi
- if Selected, Function Intc_GetVersionInfo is Enabled 
- if Deselected, Function Intc_GetVersionInfo is Disabled 
*/
#define INTC_CFG_VERSION_INFO_API                              (STD_ON)

/* Software generate interrupt enabled or disabled */
#define INTC_CFG_SGI_INT_EN                                    (STD_ON)

/* Configuration parameter count */
#define INTC_CONFIGSET_CNT                                     (1U)

/* Total number of configured internal interrupt sources(SGI and PPI) in Core0 */
#define INTC_CFG_INTSRC_NUM_CORE0                              (65U)
/* Total number of configured internal interrupt sources(SGI and PPI) in Core1 */
#define INTC_CFG_INTSRC_NUM_CORE1                              (0U)
/* Total number of configured internal interrupt sources(SGI and PPI) */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_INTSRC_NUM                                    (65U)

/* The interrupt priority configuration */
#define INTC_FIQ_MIN_PRIORITY                                  (31U)
#define INTC_IRQ_MIN_PRIORITY                                  (31U)

/* The interrupt enable status of each module */
/* GIC_SGI interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_GIC_SGI_INTSRC_EN                                   (STD_ON)
/* GIC_PPI interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_GIC_PPI_INTSRC_EN                                   (STD_OFF)
/* CPUWDT interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_CPUWDT_INTSRC_EN                                   (STD_ON)
/* SAFEWDT interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_SAFEWDT_INTSRC_EN                                   (STD_OFF)
/* CLUSTER interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_CLUSTER_INTSRC_EN                                   (STD_OFF)
/* RCC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_RCC_INTSRC_EN                                   (STD_OFF)
/* PWRC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_PWRC_INTSRC_EN                                   (STD_OFF)
/* INTC_SOFTINT interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_INTC_SOFTINT_INTSRC_EN                                   (STD_ON)
/* SAC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_SAC_INTSRC_EN                                   (STD_OFF)
/* OVC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_OVC_INTSRC_EN                                   (STD_OFF)
/* ETH interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_ETH_INTSRC_EN                                   (STD_ON)
/* DMA interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_DMA_INTSRC_EN                                   (STD_ON)
/* NVM interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_NVM_INTSRC_EN                                   (STD_ON)
/* HSM interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_HSM_INTSRC_EN                                   (STD_OFF)
/* BASETIM interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_BASETIM_INTSRC_EN                                   (STD_ON)
/* CAN interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_CAN_INTSRC_EN                                   (STD_ON)
/* SARADC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_SARADC_INTSRC_EN                                   (STD_ON)
/* SARADC_FC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_SARADC_FC_INTSRC_EN                                   (STD_OFF)
/* TSENSOR interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_TSENSOR_INTSRC_EN                                   (STD_OFF)
/* ECRC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_ECRC_INTSRC_EN                                   (STD_OFF)
/* ESPI interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_ESPI_INTSRC_EN                                   (STD_ON)
/* SENT interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_SENT_INTSRC_EN                                   (STD_ON)
/* I2C interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_I2C_INTSRC_EN                                   (STD_OFF)
/* ASI interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_ASI_INTSRC_EN                                   (STD_ON)
/* EXTI interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_EXTI_INTSRC_EN                                   (STD_OFF)
/* GTM interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_GTM_INTSRC_EN                                   (STD_ON)

/* Core mask for generate software interrupt */
/* Represent core0 for generate the SGI interrupt */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_GENSGI_CORE0                                      (0x01U)
/* Represent core1 for generate the SGI interrupt */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_GENSGI_CORE1                                      (0x02U)

/* All cores mask for generate software interrupt(SGI) */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_GENSGI_CORE_MASK                                  (0x03U)

/* Configuration: Interrupt source enable status */
/* Interrupt source 0 enabled: CPU0_SGI0 */
#define INTC_CFG_INTSRC0_CORE0_EN                              (STD_ON)
/* Interrupt source 0 category: CPU0_SGI0 */
#define INTC_CFG_INTSRC0_CORE0_CAT                             (INTC_SRC_TYPE_CAT1)
/* Interrupt source 0 notification: CPU0_SGI0 */
#define INTC_CFG_INTSRC0_CORE0_NOTIF_EN                        (STD_ON) 
/* Notification function for interrupt source 0: CPU0_SGI0 */
extern void Demo_Core0Sgi0Notification(void);
#define Intc_Irq_NotifCore0IntSrc0()                           Demo_Core0Sgi0Notification()

/* Interrupt source 32 enabled: CPU0WDT_INT */
#define INTC_CFG_INTSRC32_EN                                   (STD_ON)
/* Interrupt source 32 category: CPU0WDT_INT */
#define INTC_CFG_INTSRC32_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 32 notification: CPU0WDT_INT */
#define INTC_CFG_INTSRC32_NOTIF_EN                             (STD_OFF)

/* Interrupt source 56 enabled: INTC_CPU0SOFTINT0 */
#define INTC_CFG_INTSRC56_CORE0_EN                              (STD_ON)
/* Interrupt source 56 category: INTC_CPU0SOFTINT0 */
#define INTC_CFG_INTSRC56_CORE0_CAT                             (INTC_SRC_TYPE_CAT1)
/* Interrupt source 56 notification: INTC_CPU0SOFTINT0 */
#define INTC_CFG_INTSRC56_CORE0_NOTIF_EN                        (STD_ON) 
/* Notification function for interrupt source 56: INTC_CPU0SOFTINT0 */
extern void Demo_Core0Spi56Notification(void);
#define Intc_Irq_NotifCore0IntSrc56()                           Demo_Core0Spi56Notification()

/* Interrupt source 73 enabled: SBD_PERCH_TX_INT0 */
#define INTC_CFG_INTSRC73_EN                                   (STD_ON)
/* Interrupt source 73 category: SBD_PERCH_TX_INT0 */
#define INTC_CFG_INTSRC73_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 73 notification: SBD_PERCH_TX_INT0 */
#define INTC_CFG_INTSRC73_NOTIF_EN                             (STD_OFF)

/* Interrupt source 77 enabled: SBD_PERCH_RX_INT0 */
#define INTC_CFG_INTSRC77_EN                                   (STD_ON)
/* Interrupt source 77 category: SBD_PERCH_RX_INT0 */
#define INTC_CFG_INTSRC77_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 77 notification: SBD_PERCH_RX_INT0 */
#define INTC_CFG_INTSRC77_NOTIF_EN                             (STD_OFF)

/* Interrupt source 95 enabled: DMA0_CH_INT0 */
#define INTC_CFG_INTSRC95_EN                                   (STD_ON)
/* Interrupt source 95 category: DMA0_CH_INT0 */
#define INTC_CFG_INTSRC95_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 95 notification: DMA0_CH_INT0 */
#define INTC_CFG_INTSRC95_NOTIF_EN                             (STD_OFF)

/* Interrupt source 96 enabled: DMA0_CH_INT1 */
#define INTC_CFG_INTSRC96_EN                                   (STD_ON)
/* Interrupt source 96 category: DMA0_CH_INT1 */
#define INTC_CFG_INTSRC96_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 96 notification: DMA0_CH_INT1 */
#define INTC_CFG_INTSRC96_NOTIF_EN                             (STD_OFF)

/* Interrupt source 97 enabled: DMA0_CH_INT2 */
#define INTC_CFG_INTSRC97_EN                                   (STD_ON)
/* Interrupt source 97 category: DMA0_CH_INT2 */
#define INTC_CFG_INTSRC97_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 97 notification: DMA0_CH_INT2 */
#define INTC_CFG_INTSRC97_NOTIF_EN                             (STD_OFF)

/* Interrupt source 98 enabled: DMA0_CH_INT3 */
#define INTC_CFG_INTSRC98_EN                                   (STD_ON)
/* Interrupt source 98 category: DMA0_CH_INT3 */
#define INTC_CFG_INTSRC98_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 98 notification: DMA0_CH_INT3 */
#define INTC_CFG_INTSRC98_NOTIF_EN                             (STD_OFF)

/* Interrupt source 117 enabled: DMA2_CH_INT2 */
#define INTC_CFG_INTSRC117_EN                                   (STD_ON)
/* Interrupt source 117 category: DMA2_CH_INT2 */
#define INTC_CFG_INTSRC117_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 117 notification: DMA2_CH_INT2 */
#define INTC_CFG_INTSRC117_NOTIF_EN                             (STD_OFF)

/* Interrupt source 118 enabled: DMA2_CH_INT3 */
#define INTC_CFG_INTSRC118_EN                                   (STD_ON)
/* Interrupt source 118 category: DMA2_CH_INT3 */
#define INTC_CFG_INTSRC118_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 118 notification: DMA2_CH_INT3 */
#define INTC_CFG_INTSRC118_NOTIF_EN                             (STD_OFF)

/* Interrupt source 119 enabled: DMA2_CH_INT4 */
#define INTC_CFG_INTSRC119_EN                                   (STD_ON)
/* Interrupt source 119 category: DMA2_CH_INT4 */
#define INTC_CFG_INTSRC119_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 119 notification: DMA2_CH_INT4 */
#define INTC_CFG_INTSRC119_NOTIF_EN                             (STD_OFF)

/* Interrupt source 120 enabled: DMA2_CH_INT5 */
#define INTC_CFG_INTSRC120_EN                                   (STD_ON)
/* Interrupt source 120 category: DMA2_CH_INT5 */
#define INTC_CFG_INTSRC120_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 120 notification: DMA2_CH_INT5 */
#define INTC_CFG_INTSRC120_NOTIF_EN                             (STD_OFF)

/* Interrupt source 121 enabled: DMA2_CH_INT6 */
#define INTC_CFG_INTSRC121_EN                                   (STD_ON)
/* Interrupt source 121 category: DMA2_CH_INT6 */
#define INTC_CFG_INTSRC121_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 121 notification: DMA2_CH_INT6 */
#define INTC_CFG_INTSRC121_NOTIF_EN                             (STD_OFF)

/* Interrupt source 122 enabled: DMA2_CH_INT7 */
#define INTC_CFG_INTSRC122_EN                                   (STD_ON)
/* Interrupt source 122 category: DMA2_CH_INT7 */
#define INTC_CFG_INTSRC122_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 122 notification: DMA2_CH_INT7 */
#define INTC_CFG_INTSRC122_NOTIF_EN                             (STD_OFF)

/* Interrupt source 123 enabled: DMA2_CH_INT8 */
#define INTC_CFG_INTSRC123_EN                                   (STD_ON)
/* Interrupt source 123 category: DMA2_CH_INT8 */
#define INTC_CFG_INTSRC123_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 123 notification: DMA2_CH_INT8 */
#define INTC_CFG_INTSRC123_NOTIF_EN                             (STD_OFF)

/* Interrupt source 124 enabled: DMA2_CH_INT9 */
#define INTC_CFG_INTSRC124_EN                                   (STD_ON)
/* Interrupt source 124 category: DMA2_CH_INT9 */
#define INTC_CFG_INTSRC124_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 124 notification: DMA2_CH_INT9 */
#define INTC_CFG_INTSRC124_NOTIF_EN                             (STD_OFF)

/* Interrupt source 127 enabled: DMA2_CH_INT12 */
#define INTC_CFG_INTSRC127_EN                                   (STD_ON)
/* Interrupt source 127 category: DMA2_CH_INT12 */
#define INTC_CFG_INTSRC127_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 127 notification: DMA2_CH_INT12 */
#define INTC_CFG_INTSRC127_NOTIF_EN                             (STD_OFF)

/* Interrupt source 128 enabled: DMA2_CH_INT13 */
#define INTC_CFG_INTSRC128_EN                                   (STD_ON)
/* Interrupt source 128 category: DMA2_CH_INT13 */
#define INTC_CFG_INTSRC128_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 128 notification: DMA2_CH_INT13 */
#define INTC_CFG_INTSRC128_NOTIF_EN                             (STD_OFF)

/* Interrupt source 217 enabled: DMA2_CH_INT14 */
#define INTC_CFG_INTSRC217_EN                                   (STD_ON)
/* Interrupt source 217 category: DMA2_CH_INT14 */
#define INTC_CFG_INTSRC217_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 217 notification: DMA2_CH_INT14 */
#define INTC_CFG_INTSRC217_NOTIF_EN                             (STD_OFF)

/* Interrupt source 218 enabled: DMA2_CH_INT15 */
#define INTC_CFG_INTSRC218_EN                                   (STD_ON)
/* Interrupt source 218 category: DMA2_CH_INT15 */
#define INTC_CFG_INTSRC218_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 218 notification: DMA2_CH_INT15 */
#define INTC_CFG_INTSRC218_NOTIF_EN                             (STD_OFF)

/* Interrupt source 219 enabled: DMA2_CH_INT16 */
#define INTC_CFG_INTSRC219_EN                                   (STD_ON)
/* Interrupt source 219 category: DMA2_CH_INT16 */
#define INTC_CFG_INTSRC219_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 219 notification: DMA2_CH_INT16 */
#define INTC_CFG_INTSRC219_NOTIF_EN                             (STD_OFF)

/* Interrupt source 227 enabled: DFLASH0_FINISH */
#define INTC_CFG_INTSRC227_EN                                   (STD_ON)
/* Interrupt source 227 category: DFLASH0_FINISH */
#define INTC_CFG_INTSRC227_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 227 notification: DFLASH0_FINISH */
#define INTC_CFG_INTSRC227_NOTIF_EN                             (STD_OFF)

/* Interrupt source 246 enabled: BASETIM0_INT */
#define INTC_CFG_INTSRC246_EN                                   (STD_ON)
/* Interrupt source 246 category: BASETIM0_INT */
#define INTC_CFG_INTSRC246_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 246 notification: BASETIM0_INT */
#define INTC_CFG_INTSRC246_NOTIF_EN                             (STD_OFF)

/* Interrupt source 248 enabled: BASETIM2_INT */
#define INTC_CFG_INTSRC248_EN                                   (STD_ON)
/* Interrupt source 248 category: BASETIM2_INT */
#define INTC_CFG_INTSRC248_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 248 notification: BASETIM2_INT */
#define INTC_CFG_INTSRC248_NOTIF_EN                             (STD_OFF)

/* Interrupt source 265 enabled: CAN0_ROUTE4 */
#define INTC_CFG_INTSRC265_EN                                   (STD_ON)
/* Interrupt source 265 category: CAN0_ROUTE4 */
#define INTC_CFG_INTSRC265_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 265 notification: CAN0_ROUTE4 */
#define INTC_CFG_INTSRC265_NOTIF_EN                             (STD_OFF)

/* Interrupt source 268 enabled: CAN0_ROUTE7 */
#define INTC_CFG_INTSRC268_EN                                   (STD_ON)
/* Interrupt source 268 category: CAN0_ROUTE7 */
#define INTC_CFG_INTSRC268_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 268 notification: CAN0_ROUTE7 */
#define INTC_CFG_INTSRC268_NOTIF_EN                             (STD_OFF)

/* Interrupt source 377 enabled: SARADC0_G0SR0 */
#define INTC_CFG_INTSRC377_EN                                   (STD_ON)
/* Interrupt source 377 category: SARADC0_G0SR0 */
#define INTC_CFG_INTSRC377_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 377 notification: SARADC0_G0SR0 */
#define INTC_CFG_INTSRC377_NOTIF_EN                             (STD_OFF)

/* Interrupt source 378 enabled: SARADC0_G0SR1 */
#define INTC_CFG_INTSRC378_EN                                   (STD_ON)
/* Interrupt source 378 category: SARADC0_G0SR1 */
#define INTC_CFG_INTSRC378_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 378 notification: SARADC0_G0SR1 */
#define INTC_CFG_INTSRC378_NOTIF_EN                             (STD_OFF)

/* Interrupt source 379 enabled: SARADC0_G0SR2 */
#define INTC_CFG_INTSRC379_EN                                   (STD_ON)
/* Interrupt source 379 category: SARADC0_G0SR2 */
#define INTC_CFG_INTSRC379_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 379 notification: SARADC0_G0SR2 */
#define INTC_CFG_INTSRC379_NOTIF_EN                             (STD_OFF)

/* Interrupt source 383 enabled: SARADC1_G1SR0 */
#define INTC_CFG_INTSRC383_EN                                   (STD_ON)
/* Interrupt source 383 category: SARADC1_G1SR0 */
#define INTC_CFG_INTSRC383_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 383 notification: SARADC1_G1SR0 */
#define INTC_CFG_INTSRC383_NOTIF_EN                             (STD_OFF)

/* Interrupt source 384 enabled: SARADC1_G1SR1 */
#define INTC_CFG_INTSRC384_EN                                   (STD_ON)
/* Interrupt source 384 category: SARADC1_G1SR1 */
#define INTC_CFG_INTSRC384_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 384 notification: SARADC1_G1SR1 */
#define INTC_CFG_INTSRC384_NOTIF_EN                             (STD_OFF)

/* Interrupt source 385 enabled: SARADC1_G1SR2 */
#define INTC_CFG_INTSRC385_EN                                   (STD_ON)
/* Interrupt source 385 category: SARADC1_G1SR2 */
#define INTC_CFG_INTSRC385_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 385 notification: SARADC1_G1SR2 */
#define INTC_CFG_INTSRC385_NOTIF_EN                             (STD_OFF)

/* Interrupt source 389 enabled: SARADC2_G2SR0 */
#define INTC_CFG_INTSRC389_EN                                   (STD_ON)
/* Interrupt source 389 category: SARADC2_G2SR0 */
#define INTC_CFG_INTSRC389_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 389 notification: SARADC2_G2SR0 */
#define INTC_CFG_INTSRC389_NOTIF_EN                             (STD_OFF)

/* Interrupt source 390 enabled: SARADC2_G2SR1 */
#define INTC_CFG_INTSRC390_EN                                   (STD_ON)
/* Interrupt source 390 category: SARADC2_G2SR1 */
#define INTC_CFG_INTSRC390_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 390 notification: SARADC2_G2SR1 */
#define INTC_CFG_INTSRC390_NOTIF_EN                             (STD_OFF)

/* Interrupt source 391 enabled: SARADC2_G2SR2 */
#define INTC_CFG_INTSRC391_EN                                   (STD_ON)
/* Interrupt source 391 category: SARADC2_G2SR2 */
#define INTC_CFG_INTSRC391_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 391 notification: SARADC2_G2SR2 */
#define INTC_CFG_INTSRC391_NOTIF_EN                             (STD_OFF)

/* Interrupt source 395 enabled: SARADC3_G3SR0 */
#define INTC_CFG_INTSRC395_EN                                   (STD_ON)
/* Interrupt source 395 category: SARADC3_G3SR0 */
#define INTC_CFG_INTSRC395_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 395 notification: SARADC3_G3SR0 */
#define INTC_CFG_INTSRC395_NOTIF_EN                             (STD_OFF)

/* Interrupt source 396 enabled: SARADC3_G3SR1 */
#define INTC_CFG_INTSRC396_EN                                   (STD_ON)
/* Interrupt source 396 category: SARADC3_G3SR1 */
#define INTC_CFG_INTSRC396_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 396 notification: SARADC3_G3SR1 */
#define INTC_CFG_INTSRC396_NOTIF_EN                             (STD_OFF)

/* Interrupt source 397 enabled: SARADC3_G3SR2 */
#define INTC_CFG_INTSRC397_EN                                   (STD_ON)
/* Interrupt source 397 category: SARADC3_G3SR2 */
#define INTC_CFG_INTSRC397_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 397 notification: SARADC3_G3SR2 */
#define INTC_CFG_INTSRC397_NOTIF_EN                             (STD_OFF)

/* Interrupt source 465 enabled: ESPI0_RX_INT */
#define INTC_CFG_INTSRC465_EN                                   (STD_ON)
/* Interrupt source 465 category: ESPI0_RX_INT */
#define INTC_CFG_INTSRC465_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 465 notification: ESPI0_RX_INT */
#define INTC_CFG_INTSRC465_NOTIF_EN                             (STD_OFF)

/* Interrupt source 466 enabled: ESPI0_ERR_INT */
#define INTC_CFG_INTSRC466_EN                                   (STD_ON)
/* Interrupt source 466 category: ESPI0_ERR_INT */
#define INTC_CFG_INTSRC466_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 466 notification: ESPI0_ERR_INT */
#define INTC_CFG_INTSRC466_NOTIF_EN                             (STD_OFF)

/* Interrupt source 501 enabled: ESPI4_RX_INT */
#define INTC_CFG_INTSRC501_EN                                   (STD_ON)
/* Interrupt source 501 category: ESPI4_RX_INT */
#define INTC_CFG_INTSRC501_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 501 notification: ESPI4_RX_INT */
#define INTC_CFG_INTSRC501_NOTIF_EN                             (STD_OFF)

/* Interrupt source 502 enabled: ESPI4_ERR_INT */
#define INTC_CFG_INTSRC502_EN                                   (STD_ON)
/* Interrupt source 502 category: ESPI4_ERR_INT */
#define INTC_CFG_INTSRC502_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 502 notification: ESPI4_ERR_INT */
#define INTC_CFG_INTSRC502_NOTIF_EN                             (STD_OFF)

/* Interrupt source 580 enabled: SENT2_RX_ERROR */
#define INTC_CFG_INTSRC580_EN                                   (STD_ON)
/* Interrupt source 580 category: SENT2_RX_ERROR */
#define INTC_CFG_INTSRC580_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 580 notification: SENT2_RX_ERROR */
#define INTC_CFG_INTSRC580_NOTIF_EN                             (STD_OFF)

/* Interrupt source 581 enabled: SENT2_RX_VALID */
#define INTC_CFG_INTSRC581_EN                                   (STD_ON)
/* Interrupt source 581 category: SENT2_RX_VALID */
#define INTC_CFG_INTSRC581_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 581 notification: SENT2_RX_VALID */
#define INTC_CFG_INTSRC581_NOTIF_EN                             (STD_OFF)

/* Interrupt source 584 enabled: SENT3_RX_ERROR */
#define INTC_CFG_INTSRC584_EN                                   (STD_ON)
/* Interrupt source 584 category: SENT3_RX_ERROR */
#define INTC_CFG_INTSRC584_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 584 notification: SENT3_RX_ERROR */
#define INTC_CFG_INTSRC584_NOTIF_EN                             (STD_OFF)

/* Interrupt source 585 enabled: SENT3_RX_VALID */
#define INTC_CFG_INTSRC585_EN                                   (STD_ON)
/* Interrupt source 585 category: SENT3_RX_VALID */
#define INTC_CFG_INTSRC585_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 585 notification: SENT3_RX_VALID */
#define INTC_CFG_INTSRC585_NOTIF_EN                             (STD_OFF)

/* Interrupt source 588 enabled: SENT4_RX_ERROR */
#define INTC_CFG_INTSRC588_EN                                   (STD_ON)
/* Interrupt source 588 category: SENT4_RX_ERROR */
#define INTC_CFG_INTSRC588_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 588 notification: SENT4_RX_ERROR */
#define INTC_CFG_INTSRC588_NOTIF_EN                             (STD_OFF)

/* Interrupt source 589 enabled: SENT4_RX_VALID */
#define INTC_CFG_INTSRC589_EN                                   (STD_ON)
/* Interrupt source 589 category: SENT4_RX_VALID */
#define INTC_CFG_INTSRC589_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 589 notification: SENT4_RX_VALID */
#define INTC_CFG_INTSRC589_NOTIF_EN                             (STD_OFF)

/* Interrupt source 592 enabled: SENT5_RX_ERROR */
#define INTC_CFG_INTSRC592_EN                                   (STD_ON)
/* Interrupt source 592 category: SENT5_RX_ERROR */
#define INTC_CFG_INTSRC592_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 592 notification: SENT5_RX_ERROR */
#define INTC_CFG_INTSRC592_NOTIF_EN                             (STD_OFF)

/* Interrupt source 593 enabled: SENT5_RX_VALID */
#define INTC_CFG_INTSRC593_EN                                   (STD_ON)
/* Interrupt source 593 category: SENT5_RX_VALID */
#define INTC_CFG_INTSRC593_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 593 notification: SENT5_RX_VALID */
#define INTC_CFG_INTSRC593_NOTIF_EN                             (STD_OFF)

/* Interrupt source 641 enabled: ASI2_RX */
#define INTC_CFG_INTSRC641_EN                                   (STD_ON)
/* Interrupt source 641 category: ASI2_RX */
#define INTC_CFG_INTSRC641_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 641 notification: ASI2_RX */
#define INTC_CFG_INTSRC641_NOTIF_EN                             (STD_OFF)

/* Interrupt source 643 enabled: ASI2_ERROR */
#define INTC_CFG_INTSRC643_EN                                   (STD_ON)
/* Interrupt source 643 category: ASI2_ERROR */
#define INTC_CFG_INTSRC643_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 643 notification: ASI2_ERROR */
#define INTC_CFG_INTSRC643_NOTIF_EN                             (STD_OFF)

/* Interrupt source 656 enabled: ASI5_RX */
#define INTC_CFG_INTSRC656_EN                                   (STD_ON)
/* Interrupt source 656 category: ASI5_RX */
#define INTC_CFG_INTSRC656_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 656 notification: ASI5_RX */
#define INTC_CFG_INTSRC656_NOTIF_EN                             (STD_OFF)

/* Interrupt source 657 enabled: ASI5_TX */
#define INTC_CFG_INTSRC657_EN                                   (STD_ON)
/* Interrupt source 657 category: ASI5_TX */
#define INTC_CFG_INTSRC657_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 657 notification: ASI5_TX */
#define INTC_CFG_INTSRC657_NOTIF_EN                             (STD_OFF)

/* Interrupt source 658 enabled: ASI5_ERROR */
#define INTC_CFG_INTSRC658_EN                                   (STD_ON)
/* Interrupt source 658 category: ASI5_ERROR */
#define INTC_CFG_INTSRC658_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 658 notification: ASI5_ERROR */
#define INTC_CFG_INTSRC658_NOTIF_EN                             (STD_OFF)

/* Interrupt source 748 enabled: GTM_TIM0_INT0 */
#define INTC_CFG_INTSRC748_EN                                   (STD_ON)
/* Interrupt source 748 category: GTM_TIM0_INT0 */
#define INTC_CFG_INTSRC748_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 748 notification: GTM_TIM0_INT0 */
#define INTC_CFG_INTSRC748_NOTIF_EN                             (STD_OFF)

/* Interrupt source 753 enabled: GTM_TIM0_INT5 */
#define INTC_CFG_INTSRC753_EN                                   (STD_ON)
/* Interrupt source 753 category: GTM_TIM0_INT5 */
#define INTC_CFG_INTSRC753_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 753 notification: GTM_TIM0_INT5 */
#define INTC_CFG_INTSRC753_NOTIF_EN                             (STD_OFF)

/* Interrupt source 755 enabled: GTM_TIM0_INT7 */
#define INTC_CFG_INTSRC755_EN                                   (STD_ON)
/* Interrupt source 755 category: GTM_TIM0_INT7 */
#define INTC_CFG_INTSRC755_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 755 notification: GTM_TIM0_INT7 */
#define INTC_CFG_INTSRC755_NOTIF_EN                             (STD_OFF)

/* Interrupt source 756 enabled: GTM_TIM1_INT0 */
#define INTC_CFG_INTSRC756_EN                                   (STD_ON)
/* Interrupt source 756 category: GTM_TIM1_INT0 */
#define INTC_CFG_INTSRC756_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 756 notification: GTM_TIM1_INT0 */
#define INTC_CFG_INTSRC756_NOTIF_EN                             (STD_OFF)

/* Interrupt source 772 enabled: GTM_TOM0_INT0 */
#define INTC_CFG_INTSRC772_EN                                   (STD_ON)
/* Interrupt source 772 category: GTM_TOM0_INT0 */
#define INTC_CFG_INTSRC772_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 772 notification: GTM_TOM0_INT0 */
#define INTC_CFG_INTSRC772_NOTIF_EN                             (STD_OFF)

/* Interrupt source 777 enabled: GTM_TOM0_INT5 */
#define INTC_CFG_INTSRC777_EN                                   (STD_ON)
/* Interrupt source 777 category: GTM_TOM0_INT5 */
#define INTC_CFG_INTSRC777_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 777 notification: GTM_TOM0_INT5 */
#define INTC_CFG_INTSRC777_NOTIF_EN                             (STD_OFF)

/* Interrupt source 784 enabled: GTM_TOM1_INT4 */
#define INTC_CFG_INTSRC784_EN                                   (STD_ON)
/* Interrupt source 784 category: GTM_TOM1_INT4 */
#define INTC_CFG_INTSRC784_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 784 notification: GTM_TOM1_INT4 */
#define INTC_CFG_INTSRC784_NOTIF_EN                             (STD_OFF)

/* Interrupt source 796 enabled: GTM_ATOM0_INT0 */
#define INTC_CFG_INTSRC796_EN                                   (STD_ON)
/* Interrupt source 796 category: GTM_ATOM0_INT0 */
#define INTC_CFG_INTSRC796_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 796 notification: GTM_ATOM0_INT0 */
#define INTC_CFG_INTSRC796_NOTIF_EN                             (STD_OFF)

/* Interrupt source 819 enabled: GTM_TIO1_INT7 */
#define INTC_CFG_INTSRC819_EN                                   (STD_ON)
/* Interrupt source 819 category: GTM_TIO1_INT7 */
#define INTC_CFG_INTSRC819_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 819 notification: GTM_TIO1_INT7 */
#define INTC_CFG_INTSRC819_NOTIF_EN                             (STD_OFF)


/****************************************************************************************************
**                          Interrupt ID Macro Definition                                          **
****************************************************************************************************/
/* Internal interrupt source(SGI or PPI): INTID 0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI0                                   (0U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI0_CORE0                               (0U)
#ifndef INTC_INTSRC_NUM_0
#define INTC_INTSRC_NUM_0                                     (0U)
#endif /* INTC_INTSRC_NUM_0 */
/* Internal interrupt source(SGI or PPI): INTID 1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI1                                   (1U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI1_CORE0                               (1U)
#ifndef INTC_INTSRC_NUM_1
#define INTC_INTSRC_NUM_1                                     (1U)
#endif /* INTC_INTSRC_NUM_1 */
/* Internal interrupt source(SGI or PPI): INTID 2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI2                                   (2U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI2_CORE0                               (2U)
#ifndef INTC_INTSRC_NUM_2
#define INTC_INTSRC_NUM_2                                     (2U)
#endif /* INTC_INTSRC_NUM_2 */
/* Internal interrupt source(SGI or PPI): INTID 3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI3                                   (3U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI3_CORE0                               (3U)
#ifndef INTC_INTSRC_NUM_3
#define INTC_INTSRC_NUM_3                                     (3U)
#endif /* INTC_INTSRC_NUM_3 */
/* Internal interrupt source(SGI or PPI): INTID 4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI4                                   (4U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI4_CORE0                               (4U)
#ifndef INTC_INTSRC_NUM_4
#define INTC_INTSRC_NUM_4                                     (4U)
#endif /* INTC_INTSRC_NUM_4 */
/* Internal interrupt source(SGI or PPI): INTID 5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI5                                   (5U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI5_CORE0                               (5U)
#ifndef INTC_INTSRC_NUM_5
#define INTC_INTSRC_NUM_5                                     (5U)
#endif /* INTC_INTSRC_NUM_5 */
/* Internal interrupt source(SGI or PPI): INTID 6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI6                                   (6U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI6_CORE0                               (6U)
#ifndef INTC_INTSRC_NUM_6
#define INTC_INTSRC_NUM_6                                     (6U)
#endif /* INTC_INTSRC_NUM_6 */
/* Internal interrupt source(SGI or PPI): INTID 7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI7                                   (7U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI7_CORE0                               (7U)
#ifndef INTC_INTSRC_NUM_7
#define INTC_INTSRC_NUM_7                                     (7U)
#endif /* INTC_INTSRC_NUM_7 */
/* Internal interrupt source(SGI or PPI): INTID 8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI8                                   (8U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI8_CORE0                               (8U)
#ifndef INTC_INTSRC_NUM_8
#define INTC_INTSRC_NUM_8                                     (8U)
#endif /* INTC_INTSRC_NUM_8 */
/* Internal interrupt source(SGI or PPI): INTID 9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI9                                   (9U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI9_CORE0                               (9U)
#ifndef INTC_INTSRC_NUM_9
#define INTC_INTSRC_NUM_9                                     (9U)
#endif /* INTC_INTSRC_NUM_9 */
/* Internal interrupt source(SGI or PPI): INTID 10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI10                                   (10U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI10_CORE0                               (10U)
#ifndef INTC_INTSRC_NUM_10
#define INTC_INTSRC_NUM_10                                     (10U)
#endif /* INTC_INTSRC_NUM_10 */
/* Internal interrupt source(SGI or PPI): INTID 11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI11                                   (11U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI11_CORE0                               (11U)
#ifndef INTC_INTSRC_NUM_11
#define INTC_INTSRC_NUM_11                                     (11U)
#endif /* INTC_INTSRC_NUM_11 */
/* Internal interrupt source(SGI or PPI): INTID 12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI12                                   (12U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI12_CORE0                               (12U)
#ifndef INTC_INTSRC_NUM_12
#define INTC_INTSRC_NUM_12                                     (12U)
#endif /* INTC_INTSRC_NUM_12 */
/* Internal interrupt source(SGI or PPI): INTID 13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI13                                   (13U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI13_CORE0                               (13U)
#ifndef INTC_INTSRC_NUM_13
#define INTC_INTSRC_NUM_13                                     (13U)
#endif /* INTC_INTSRC_NUM_13 */
/* Internal interrupt source(SGI or PPI): INTID 14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI14                                   (14U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI14_CORE0                               (14U)
#ifndef INTC_INTSRC_NUM_14
#define INTC_INTSRC_NUM_14                                     (14U)
#endif /* INTC_INTSRC_NUM_14 */
/* Internal interrupt source(SGI or PPI): INTID 15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI15                                   (15U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_SGI15_CORE0                               (15U)
#ifndef INTC_INTSRC_NUM_15
#define INTC_INTSRC_NUM_15                                     (15U)
#endif /* INTC_INTSRC_NUM_15 */
/* Internal interrupt source(SGI or PPI): INTID 22 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_DBGCCI                                   (22U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_DBGCCI_CORE0                               (22U)
#ifndef INTC_INTSRC_NUM_22
#define INTC_INTSRC_NUM_22                                     (22U)
#endif /* INTC_INTSRC_NUM_22 */
/* Internal interrupt source(SGI or PPI): INTID 23 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_PMCOINT                                   (23U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_PMCOINT_CORE0                               (23U)
#ifndef INTC_INTSRC_NUM_23
#define INTC_INTSRC_NUM_23                                     (23U)
#endif /* INTC_INTSRC_NUM_23 */
/* Internal interrupt source(SGI or PPI): INTID 24 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_CTIINT                                   (24U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_CTIINT_CORE0                               (24U)
#ifndef INTC_INTSRC_NUM_24
#define INTC_INTSRC_NUM_24                                     (24U)
#endif /* INTC_INTSRC_NUM_24 */
/* Internal interrupt source(SGI or PPI): INTID 25 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_VCPUIMINT                                   (25U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_VCPUIMINT_CORE0                               (25U)
#ifndef INTC_INTSRC_NUM_25
#define INTC_INTSRC_NUM_25                                     (25U)
#endif /* INTC_INTSRC_NUM_25 */
/* Internal interrupt source(SGI or PPI): INTID 26 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_HTINT                                   (26U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_HTINT_CORE0                               (26U)
#ifndef INTC_INTSRC_NUM_26
#define INTC_INTSRC_NUM_26                                     (26U)
#endif /* INTC_INTSRC_NUM_26 */
/* Internal interrupt source(SGI or PPI): INTID 27 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_VTINT                                   (27U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_VTINT_CORE0                               (27U)
#ifndef INTC_INTSRC_NUM_27
#define INTC_INTSRC_NUM_27                                     (27U)
#endif /* INTC_INTSRC_NUM_27 */
/* Internal interrupt source(SGI or PPI): INTID 30 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_NSPTINT                                   (30U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_NSPTINT_CORE0                               (30U)
#ifndef INTC_INTSRC_NUM_30
#define INTC_INTSRC_NUM_30                                     (30U)
#endif /* INTC_INTSRC_NUM_30 */
/* External interrupt source(SPI): INTID 32 - CPU0WDT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0WDT_INT                                   (32U)
#ifndef INTC_INTSRC_NUM_32        
#define INTC_INTSRC_NUM_32                                     (32U)
#endif /* INTC_INTSRC_NUM_32 */
/* External interrupt source(SPI): INTID 33 - CPUWDT_ENDINIT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPUWDT_ENDINIT                                   (33U)
#ifndef INTC_INTSRC_NUM_33        
#define INTC_INTSRC_NUM_33                                     (33U)
#endif /* INTC_INTSRC_NUM_33 */
/* External interrupt source(SPI): INTID 34 - CPU1WDT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1WDT_INT                                   (34U)
#ifndef INTC_INTSRC_NUM_34        
#define INTC_INTSRC_NUM_34                                     (34U)
#endif /* INTC_INTSRC_NUM_34 */
/* External interrupt source(SPI): INTID 36 - SAFEWDT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAFEWDT_INT                                   (36U)
#ifndef INTC_INTSRC_NUM_36        
#define INTC_INTSRC_NUM_36                                     (36U)
#endif /* INTC_INTSRC_NUM_36 */
/* External interrupt source(SPI): INTID 37 - SAFEWDT_ENDINIT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAFEWDT_ENDINIT                                   (37U)
#ifndef INTC_INTSRC_NUM_37        
#define INTC_INTSRC_NUM_37                                     (37U)
#endif /* INTC_INTSRC_NUM_37 */
/* External interrupt source(SPI): INTID 40 - CLUSTER_COMMRX0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CLUSTER_COMMRX0                                   (40U)
#ifndef INTC_INTSRC_NUM_40        
#define INTC_INTSRC_NUM_40                                     (40U)
#endif /* INTC_INTSRC_NUM_40 */
/* External interrupt source(SPI): INTID 41 - CLUSTER_COMMTX0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CLUSTER_COMMTX0                                   (41U)
#ifndef INTC_INTSRC_NUM_41        
#define INTC_INTSRC_NUM_41                                     (41U)
#endif /* INTC_INTSRC_NUM_41 */
/* External interrupt source(SPI): INTID 52 - RCC_WARMRESET */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_RCC_WARMRESET                                   (52U)
#ifndef INTC_INTSRC_NUM_52        
#define INTC_INTSRC_NUM_52                                     (52U)
#endif /* INTC_INTSRC_NUM_52 */
/* External interrupt source(SPI): INTID 53 - PWRC_VOLCURESR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PWRC_VOLCURESR_INT                                   (53U)
#ifndef INTC_INTSRC_NUM_53        
#define INTC_INTSRC_NUM_53                                     (53U)
#endif /* INTC_INTSRC_NUM_53 */
/* External interrupt source(SPI): INTID 55 - PWRC_CORESLEEP_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PWRC_CORESLEEP_INT                                   (55U)
#ifndef INTC_INTSRC_NUM_55        
#define INTC_INTSRC_NUM_55                                     (55U)
#endif /* INTC_INTSRC_NUM_55 */
/* Internal interrupt source(SGI or PPI): INTID 56 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU0SOFTINT0                                   (56U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU0SOFTINT0_CORE0                               (56U)
#ifndef INTC_INTSRC_NUM_56
#define INTC_INTSRC_NUM_56                                     (56U)
#endif /* INTC_INTSRC_NUM_56 */
/* Internal interrupt source(SGI or PPI): INTID 57 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU0SOFTINT1                                   (57U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU0SOFTINT1_CORE0                               (57U)
#ifndef INTC_INTSRC_NUM_57
#define INTC_INTSRC_NUM_57                                     (57U)
#endif /* INTC_INTSRC_NUM_57 */
/* Internal interrupt source(SGI or PPI): INTID 58 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU0SOFTINT2                                   (58U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU0SOFTINT2_CORE0                               (58U)
#ifndef INTC_INTSRC_NUM_58
#define INTC_INTSRC_NUM_58                                     (58U)
#endif /* INTC_INTSRC_NUM_58 */
/* Internal interrupt source(SGI or PPI): INTID 59 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU0SOFTINT3                                   (59U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU0SOFTINT3_CORE0                               (59U)
#ifndef INTC_INTSRC_NUM_59
#define INTC_INTSRC_NUM_59                                     (59U)
#endif /* INTC_INTSRC_NUM_59 */
/* External interrupt source(SPI): INTID 62 - SAC_IRQ0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAC_IRQ0                                   (62U)
#ifndef INTC_INTSRC_NUM_62        
#define INTC_INTSRC_NUM_62                                     (62U)
#endif /* INTC_INTSRC_NUM_62 */
/* External interrupt source(SPI): INTID 63 - SAC_IRQ1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAC_IRQ1                                   (63U)
#ifndef INTC_INTSRC_NUM_63        
#define INTC_INTSRC_NUM_63                                     (63U)
#endif /* INTC_INTSRC_NUM_63 */
/* External interrupt source(SPI): INTID 64 - SAC_IRQ2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAC_IRQ2                                   (64U)
#ifndef INTC_INTSRC_NUM_64        
#define INTC_INTSRC_NUM_64                                     (64U)
#endif /* INTC_INTSRC_NUM_64 */
/* External interrupt source(SPI): INTID 65 - SAC_IRQ3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAC_IRQ3                                   (65U)
#ifndef INTC_INTSRC_NUM_65        
#define INTC_INTSRC_NUM_65                                     (65U)
#endif /* INTC_INTSRC_NUM_65 */
/* External interrupt source(SPI): INTID 68 - OVC_CPU0_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_OVC_CPU0_INT                                   (68U)
#ifndef INTC_INTSRC_NUM_68        
#define INTC_INTSRC_NUM_68                                     (68U)
#endif /* INTC_INTSRC_NUM_68 */
/* External interrupt source(SPI): INTID 72 - SBD_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SBD_INT                                   (72U)
#ifndef INTC_INTSRC_NUM_72        
#define INTC_INTSRC_NUM_72                                     (72U)
#endif /* INTC_INTSRC_NUM_72 */
/* External interrupt source(SPI): INTID 73 - SBD_PERCH_TX_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SBD_PERCH_TX_INT0                                   (73U)
#ifndef INTC_INTSRC_NUM_73        
#define INTC_INTSRC_NUM_73                                     (73U)
#endif /* INTC_INTSRC_NUM_73 */
/* External interrupt source(SPI): INTID 74 - SBD_PERCH_TX_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SBD_PERCH_TX_INT1                                   (74U)
#ifndef INTC_INTSRC_NUM_74        
#define INTC_INTSRC_NUM_74                                     (74U)
#endif /* INTC_INTSRC_NUM_74 */
/* External interrupt source(SPI): INTID 77 - SBD_PERCH_RX_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SBD_PERCH_RX_INT0                                   (77U)
#ifndef INTC_INTSRC_NUM_77        
#define INTC_INTSRC_NUM_77                                     (77U)
#endif /* INTC_INTSRC_NUM_77 */
/* External interrupt source(SPI): INTID 78 - SBD_PERCH_RX_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SBD_PERCH_RX_INT1                                   (78U)
#ifndef INTC_INTSRC_NUM_78        
#define INTC_INTSRC_NUM_78                                     (78U)
#endif /* INTC_INTSRC_NUM_78 */
/* External interrupt source(SPI): INTID 81 - LPI */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_LPI                                   (81U)
#ifndef INTC_INTSRC_NUM_81        
#define INTC_INTSRC_NUM_81                                     (81U)
#endif /* INTC_INTSRC_NUM_81 */
/* External interrupt source(SPI): INTID 95 - DMA0_CH_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT0                                   (95U)
#ifndef INTC_INTSRC_NUM_95        
#define INTC_INTSRC_NUM_95                                     (95U)
#endif /* INTC_INTSRC_NUM_95 */
/* External interrupt source(SPI): INTID 96 - DMA0_CH_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT1                                   (96U)
#ifndef INTC_INTSRC_NUM_96        
#define INTC_INTSRC_NUM_96                                     (96U)
#endif /* INTC_INTSRC_NUM_96 */
/* External interrupt source(SPI): INTID 97 - DMA0_CH_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT2                                   (97U)
#ifndef INTC_INTSRC_NUM_97        
#define INTC_INTSRC_NUM_97                                     (97U)
#endif /* INTC_INTSRC_NUM_97 */
/* External interrupt source(SPI): INTID 98 - DMA0_CH_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT3                                   (98U)
#ifndef INTC_INTSRC_NUM_98        
#define INTC_INTSRC_NUM_98                                     (98U)
#endif /* INTC_INTSRC_NUM_98 */
/* External interrupt source(SPI): INTID 115 - DMA2_CH_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT0                                   (115U)
#ifndef INTC_INTSRC_NUM_115        
#define INTC_INTSRC_NUM_115                                     (115U)
#endif /* INTC_INTSRC_NUM_115 */
/* External interrupt source(SPI): INTID 116 - DMA2_CH_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT1                                   (116U)
#ifndef INTC_INTSRC_NUM_116        
#define INTC_INTSRC_NUM_116                                     (116U)
#endif /* INTC_INTSRC_NUM_116 */
/* External interrupt source(SPI): INTID 117 - DMA2_CH_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT2                                   (117U)
#ifndef INTC_INTSRC_NUM_117        
#define INTC_INTSRC_NUM_117                                     (117U)
#endif /* INTC_INTSRC_NUM_117 */
/* External interrupt source(SPI): INTID 118 - DMA2_CH_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT3                                   (118U)
#ifndef INTC_INTSRC_NUM_118        
#define INTC_INTSRC_NUM_118                                     (118U)
#endif /* INTC_INTSRC_NUM_118 */
/* External interrupt source(SPI): INTID 119 - DMA2_CH_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT4                                   (119U)
#ifndef INTC_INTSRC_NUM_119        
#define INTC_INTSRC_NUM_119                                     (119U)
#endif /* INTC_INTSRC_NUM_119 */
/* External interrupt source(SPI): INTID 120 - DMA2_CH_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT5                                   (120U)
#ifndef INTC_INTSRC_NUM_120        
#define INTC_INTSRC_NUM_120                                     (120U)
#endif /* INTC_INTSRC_NUM_120 */
/* External interrupt source(SPI): INTID 121 - DMA2_CH_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT6                                   (121U)
#ifndef INTC_INTSRC_NUM_121        
#define INTC_INTSRC_NUM_121                                     (121U)
#endif /* INTC_INTSRC_NUM_121 */
/* External interrupt source(SPI): INTID 122 - DMA2_CH_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT7                                   (122U)
#ifndef INTC_INTSRC_NUM_122        
#define INTC_INTSRC_NUM_122                                     (122U)
#endif /* INTC_INTSRC_NUM_122 */
/* External interrupt source(SPI): INTID 123 - DMA2_CH_INT8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT8                                   (123U)
#ifndef INTC_INTSRC_NUM_123        
#define INTC_INTSRC_NUM_123                                     (123U)
#endif /* INTC_INTSRC_NUM_123 */
/* External interrupt source(SPI): INTID 124 - DMA2_CH_INT9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT9                                   (124U)
#ifndef INTC_INTSRC_NUM_124        
#define INTC_INTSRC_NUM_124                                     (124U)
#endif /* INTC_INTSRC_NUM_124 */
/* External interrupt source(SPI): INTID 125 - DMA2_CH_INT10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT10                                   (125U)
#ifndef INTC_INTSRC_NUM_125        
#define INTC_INTSRC_NUM_125                                     (125U)
#endif /* INTC_INTSRC_NUM_125 */
/* External interrupt source(SPI): INTID 126 - DMA2_CH_INT11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT11                                   (126U)
#ifndef INTC_INTSRC_NUM_126        
#define INTC_INTSRC_NUM_126                                     (126U)
#endif /* INTC_INTSRC_NUM_126 */
/* External interrupt source(SPI): INTID 127 - DMA2_CH_INT12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT12                                   (127U)
#ifndef INTC_INTSRC_NUM_127        
#define INTC_INTSRC_NUM_127                                     (127U)
#endif /* INTC_INTSRC_NUM_127 */
/* External interrupt source(SPI): INTID 128 - DMA2_CH_INT13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT13                                   (128U)
#ifndef INTC_INTSRC_NUM_128        
#define INTC_INTSRC_NUM_128                                     (128U)
#endif /* INTC_INTSRC_NUM_128 */
/* External interrupt source(SPI): INTID 163 - DMA2_CH_INT24 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT24                                   (163U)
#ifndef INTC_INTSRC_NUM_163        
#define INTC_INTSRC_NUM_163                                     (163U)
#endif /* INTC_INTSRC_NUM_163 */
/* External interrupt source(SPI): INTID 164 - DMA2_CH_INT25 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT25                                   (164U)
#ifndef INTC_INTSRC_NUM_164        
#define INTC_INTSRC_NUM_164                                     (164U)
#endif /* INTC_INTSRC_NUM_164 */
/* External interrupt source(SPI): INTID 165 - DMA2_CH_INT26 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT26                                   (165U)
#ifndef INTC_INTSRC_NUM_165        
#define INTC_INTSRC_NUM_165                                     (165U)
#endif /* INTC_INTSRC_NUM_165 */
/* External interrupt source(SPI): INTID 166 - DMA2_CH_INT27 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT27                                   (166U)
#ifndef INTC_INTSRC_NUM_166        
#define INTC_INTSRC_NUM_166                                     (166U)
#endif /* INTC_INTSRC_NUM_166 */
/* External interrupt source(SPI): INTID 167 - DMA2_CH_INT28 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT28                                   (167U)
#ifndef INTC_INTSRC_NUM_167        
#define INTC_INTSRC_NUM_167                                     (167U)
#endif /* INTC_INTSRC_NUM_167 */
/* External interrupt source(SPI): INTID 168 - DMA2_CH_INT29 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT29                                   (168U)
#ifndef INTC_INTSRC_NUM_168        
#define INTC_INTSRC_NUM_168                                     (168U)
#endif /* INTC_INTSRC_NUM_168 */
/* External interrupt source(SPI): INTID 169 - DMA2_CH_INT30 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT30                                   (169U)
#ifndef INTC_INTSRC_NUM_169        
#define INTC_INTSRC_NUM_169                                     (169U)
#endif /* INTC_INTSRC_NUM_169 */
/* External interrupt source(SPI): INTID 170 - DMA2_CH_INT31 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT31                                   (170U)
#ifndef INTC_INTSRC_NUM_170        
#define INTC_INTSRC_NUM_170                                     (170U)
#endif /* INTC_INTSRC_NUM_170 */
/* External interrupt source(SPI): INTID 171 - DMA2_CH_INT32 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT32                                   (171U)
#ifndef INTC_INTSRC_NUM_171        
#define INTC_INTSRC_NUM_171                                     (171U)
#endif /* INTC_INTSRC_NUM_171 */
/* External interrupt source(SPI): INTID 172 - DMA2_CH_INT33 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT33                                   (172U)
#ifndef INTC_INTSRC_NUM_172        
#define INTC_INTSRC_NUM_172                                     (172U)
#endif /* INTC_INTSRC_NUM_172 */
/* External interrupt source(SPI): INTID 173 - DMA2_CH_INT34 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT34                                   (173U)
#ifndef INTC_INTSRC_NUM_173        
#define INTC_INTSRC_NUM_173                                     (173U)
#endif /* INTC_INTSRC_NUM_173 */
/* External interrupt source(SPI): INTID 174 - DMA2_CH_INT35 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT35                                   (174U)
#ifndef INTC_INTSRC_NUM_174        
#define INTC_INTSRC_NUM_174                                     (174U)
#endif /* INTC_INTSRC_NUM_174 */
/* External interrupt source(SPI): INTID 175 - DMA2_CH_INT36 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT36                                   (175U)
#ifndef INTC_INTSRC_NUM_175        
#define INTC_INTSRC_NUM_175                                     (175U)
#endif /* INTC_INTSRC_NUM_175 */
/* External interrupt source(SPI): INTID 176 - DMA2_CH_INT37 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT37                                   (176U)
#ifndef INTC_INTSRC_NUM_176        
#define INTC_INTSRC_NUM_176                                     (176U)
#endif /* INTC_INTSRC_NUM_176 */
/* External interrupt source(SPI): INTID 177 - DMA2_CH_INT38 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT38                                   (177U)
#ifndef INTC_INTSRC_NUM_177        
#define INTC_INTSRC_NUM_177                                     (177U)
#endif /* INTC_INTSRC_NUM_177 */
/* External interrupt source(SPI): INTID 178 - DMA2_CH_INT39 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT39                                   (178U)
#ifndef INTC_INTSRC_NUM_178        
#define INTC_INTSRC_NUM_178                                     (178U)
#endif /* INTC_INTSRC_NUM_178 */
/* External interrupt source(SPI): INTID 179 - DMA2_CH_INT40 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT40                                   (179U)
#ifndef INTC_INTSRC_NUM_179        
#define INTC_INTSRC_NUM_179                                     (179U)
#endif /* INTC_INTSRC_NUM_179 */
/* External interrupt source(SPI): INTID 180 - DMA2_CH_INT41 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT41                                   (180U)
#ifndef INTC_INTSRC_NUM_180        
#define INTC_INTSRC_NUM_180                                     (180U)
#endif /* INTC_INTSRC_NUM_180 */
/* External interrupt source(SPI): INTID 181 - DMA2_CH_INT42 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT42                                   (181U)
#ifndef INTC_INTSRC_NUM_181        
#define INTC_INTSRC_NUM_181                                     (181U)
#endif /* INTC_INTSRC_NUM_181 */
/* External interrupt source(SPI): INTID 182 - DMA2_CH_INT43 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT43                                   (182U)
#ifndef INTC_INTSRC_NUM_182        
#define INTC_INTSRC_NUM_182                                     (182U)
#endif /* INTC_INTSRC_NUM_182 */
/* External interrupt source(SPI): INTID 217 - DMA2_CH_INT14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT14                                   (217U)
#ifndef INTC_INTSRC_NUM_217        
#define INTC_INTSRC_NUM_217                                     (217U)
#endif /* INTC_INTSRC_NUM_217 */
/* External interrupt source(SPI): INTID 218 - DMA2_CH_INT15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT15                                   (218U)
#ifndef INTC_INTSRC_NUM_218        
#define INTC_INTSRC_NUM_218                                     (218U)
#endif /* INTC_INTSRC_NUM_218 */
/* External interrupt source(SPI): INTID 219 - DMA2_CH_INT16 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT16                                   (219U)
#ifndef INTC_INTSRC_NUM_219        
#define INTC_INTSRC_NUM_219                                     (219U)
#endif /* INTC_INTSRC_NUM_219 */
/* External interrupt source(SPI): INTID 220 - DMA2_CH_INT17 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT17                                   (220U)
#ifndef INTC_INTSRC_NUM_220        
#define INTC_INTSRC_NUM_220                                     (220U)
#endif /* INTC_INTSRC_NUM_220 */
/* External interrupt source(SPI): INTID 221 - DMA2_CH_INT18 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT18                                   (221U)
#ifndef INTC_INTSRC_NUM_221        
#define INTC_INTSRC_NUM_221                                     (221U)
#endif /* INTC_INTSRC_NUM_221 */
/* External interrupt source(SPI): INTID 222 - DMA2_CH_INT19 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT19                                   (222U)
#ifndef INTC_INTSRC_NUM_222        
#define INTC_INTSRC_NUM_222                                     (222U)
#endif /* INTC_INTSRC_NUM_222 */
/* External interrupt source(SPI): INTID 223 - DMA2_CH_INT20 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT20                                   (223U)
#ifndef INTC_INTSRC_NUM_223        
#define INTC_INTSRC_NUM_223                                     (223U)
#endif /* INTC_INTSRC_NUM_223 */
/* External interrupt source(SPI): INTID 224 - DMA2_CH_INT21 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT21                                   (224U)
#ifndef INTC_INTSRC_NUM_224        
#define INTC_INTSRC_NUM_224                                     (224U)
#endif /* INTC_INTSRC_NUM_224 */
/* External interrupt source(SPI): INTID 225 - DMA2_CH_INT22 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT22                                   (225U)
#ifndef INTC_INTSRC_NUM_225        
#define INTC_INTSRC_NUM_225                                     (225U)
#endif /* INTC_INTSRC_NUM_225 */
/* External interrupt source(SPI): INTID 226 - DMA2_CH_INT23 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA2_CH_INT23                                   (226U)
#ifndef INTC_INTSRC_NUM_226        
#define INTC_INTSRC_NUM_226                                     (226U)
#endif /* INTC_INTSRC_NUM_226 */
/* External interrupt source(SPI): INTID 195 - PFLASH0_FINISH */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PFLASH0_FINISH                                   (195U)
#ifndef INTC_INTSRC_NUM_195        
#define INTC_INTSRC_NUM_195                                     (195U)
#endif /* INTC_INTSRC_NUM_195 */
/* External interrupt source(SPI): INTID 196 - PFLASH0_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PFLASH0_ERROR                                   (196U)
#ifndef INTC_INTSRC_NUM_196        
#define INTC_INTSRC_NUM_196                                     (196U)
#endif /* INTC_INTSRC_NUM_196 */
/* External interrupt source(SPI): INTID 197 - PFLASH1_FINISH */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PFLASH1_FINISH                                   (197U)
#ifndef INTC_INTSRC_NUM_197        
#define INTC_INTSRC_NUM_197                                     (197U)
#endif /* INTC_INTSRC_NUM_197 */
/* External interrupt source(SPI): INTID 198 - PFLASH1_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PFLASH1_ERROR                                   (198U)
#ifndef INTC_INTSRC_NUM_198        
#define INTC_INTSRC_NUM_198                                     (198U)
#endif /* INTC_INTSRC_NUM_198 */
/* External interrupt source(SPI): INTID 227 - DFLASH0_FINISH */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DFLASH0_FINISH                                   (227U)
#ifndef INTC_INTSRC_NUM_227        
#define INTC_INTSRC_NUM_227                                     (227U)
#endif /* INTC_INTSRC_NUM_227 */
/* External interrupt source(SPI): INTID 228 - DFLASH0_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DFLASH0_ERROR                                   (228U)
#ifndef INTC_INTSRC_NUM_228        
#define INTC_INTSRC_NUM_228                                     (228U)
#endif /* INTC_INTSRC_NUM_228 */
/* External interrupt source(SPI): INTID 234 - PASSWORD_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PASSWORD_ERROR                                   (234U)
#ifndef INTC_INTSRC_NUM_234        
#define INTC_INTSRC_NUM_234                                     (234U)
#endif /* INTC_INTSRC_NUM_234 */
/* External interrupt source(SPI): INTID 235 - HSM2HOST_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_HSM2HOST_INT0                                   (235U)
#ifndef INTC_INTSRC_NUM_235        
#define INTC_INTSRC_NUM_235                                     (235U)
#endif /* INTC_INTSRC_NUM_235 */
/* External interrupt source(SPI): INTID 236 - HSM2HOST_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_HSM2HOST_INT1                                   (236U)
#ifndef INTC_INTSRC_NUM_236        
#define INTC_INTSRC_NUM_236                                     (236U)
#endif /* INTC_INTSRC_NUM_236 */
/* External interrupt source(SPI): INTID 237 - HSM2HOST_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_HSM2HOST_INT2                                   (237U)
#ifndef INTC_INTSRC_NUM_237        
#define INTC_INTSRC_NUM_237                                     (237U)
#endif /* INTC_INTSRC_NUM_237 */
/* External interrupt source(SPI): INTID 238 - HSM2HOST_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_HSM2HOST_INT3                                   (238U)
#ifndef INTC_INTSRC_NUM_238        
#define INTC_INTSRC_NUM_238                                     (238U)
#endif /* INTC_INTSRC_NUM_238 */
/* External interrupt source(SPI): INTID 239 - HSM_WDT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_HSM_WDT_INT                                   (239U)
#ifndef INTC_INTSRC_NUM_239        
#define INTC_INTSRC_NUM_239                                     (239U)
#endif /* INTC_INTSRC_NUM_239 */
/* External interrupt source(SPI): INTID 240 - HSM_MUX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_HSM_MUX_INT                                   (240U)
#ifndef INTC_INTSRC_NUM_240        
#define INTC_INTSRC_NUM_240                                     (240U)
#endif /* INTC_INTSRC_NUM_240 */
/* External interrupt source(SPI): INTID 246 - BASETIM0_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_BASETIM0_INT                                   (246U)
#ifndef INTC_INTSRC_NUM_246        
#define INTC_INTSRC_NUM_246                                     (246U)
#endif /* INTC_INTSRC_NUM_246 */
/* External interrupt source(SPI): INTID 247 - BASETIM1_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_BASETIM1_INT                                   (247U)
#ifndef INTC_INTSRC_NUM_247        
#define INTC_INTSRC_NUM_247                                     (247U)
#endif /* INTC_INTSRC_NUM_247 */
/* External interrupt source(SPI): INTID 248 - BASETIM2_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_BASETIM2_INT                                   (248U)
#ifndef INTC_INTSRC_NUM_248        
#define INTC_INTSRC_NUM_248                                     (248U)
#endif /* INTC_INTSRC_NUM_248 */
/* External interrupt source(SPI): INTID 249 - BASETIM3_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_BASETIM3_INT                                   (249U)
#ifndef INTC_INTSRC_NUM_249        
#define INTC_INTSRC_NUM_249                                     (249U)
#endif /* INTC_INTSRC_NUM_249 */
/* External interrupt source(SPI): INTID 252 - CAN02_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN02_INT0                                   (252U)
#ifndef INTC_INTSRC_NUM_252        
#define INTC_INTSRC_NUM_252                                     (252U)
#endif /* INTC_INTSRC_NUM_252 */
/* External interrupt source(SPI): INTID 253 - CAN02_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN02_INT1                                   (253U)
#ifndef INTC_INTSRC_NUM_253        
#define INTC_INTSRC_NUM_253                                     (253U)
#endif /* INTC_INTSRC_NUM_253 */
/* External interrupt source(SPI): INTID 254 - CAN01_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN01_INT0                                   (254U)
#ifndef INTC_INTSRC_NUM_254        
#define INTC_INTSRC_NUM_254                                     (254U)
#endif /* INTC_INTSRC_NUM_254 */
/* External interrupt source(SPI): INTID 255 - CAN01_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN01_INT1                                   (255U)
#ifndef INTC_INTSRC_NUM_255        
#define INTC_INTSRC_NUM_255                                     (255U)
#endif /* INTC_INTSRC_NUM_255 */
/* External interrupt source(SPI): INTID 256 - CAN00_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN00_INT0                                   (256U)
#ifndef INTC_INTSRC_NUM_256        
#define INTC_INTSRC_NUM_256                                     (256U)
#endif /* INTC_INTSRC_NUM_256 */
/* External interrupt source(SPI): INTID 257 - CAN00_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN00_INT1                                   (257U)
#ifndef INTC_INTSRC_NUM_257        
#define INTC_INTSRC_NUM_257                                     (257U)
#endif /* INTC_INTSRC_NUM_257 */
/* External interrupt source(SPI): INTID 258 - CAN0_DMU0_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_DMU0_INT                                   (258U)
#ifndef INTC_INTSRC_NUM_258        
#define INTC_INTSRC_NUM_258                                     (258U)
#endif /* INTC_INTSRC_NUM_258 */
/* External interrupt source(SPI): INTID 259 - CAN0_DMU1_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_DMU1_INT                                   (259U)
#ifndef INTC_INTSRC_NUM_259        
#define INTC_INTSRC_NUM_259                                     (259U)
#endif /* INTC_INTSRC_NUM_259 */
/* External interrupt source(SPI): INTID 260 - CAN0_DMU2_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_DMU2_INT                                   (260U)
#ifndef INTC_INTSRC_NUM_260        
#define INTC_INTSRC_NUM_260                                     (260U)
#endif /* INTC_INTSRC_NUM_260 */
/* External interrupt source(SPI): INTID 261 - CAN0_ROUTE0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE0                                   (261U)
#ifndef INTC_INTSRC_NUM_261        
#define INTC_INTSRC_NUM_261                                     (261U)
#endif /* INTC_INTSRC_NUM_261 */
/* External interrupt source(SPI): INTID 262 - CAN0_ROUTE1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE1                                   (262U)
#ifndef INTC_INTSRC_NUM_262        
#define INTC_INTSRC_NUM_262                                     (262U)
#endif /* INTC_INTSRC_NUM_262 */
/* External interrupt source(SPI): INTID 263 - CAN0_ROUTE2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE2                                   (263U)
#ifndef INTC_INTSRC_NUM_263        
#define INTC_INTSRC_NUM_263                                     (263U)
#endif /* INTC_INTSRC_NUM_263 */
/* External interrupt source(SPI): INTID 264 - CAN0_ROUTE3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE3                                   (264U)
#ifndef INTC_INTSRC_NUM_264        
#define INTC_INTSRC_NUM_264                                     (264U)
#endif /* INTC_INTSRC_NUM_264 */
/* External interrupt source(SPI): INTID 265 - CAN0_ROUTE4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE4                                   (265U)
#ifndef INTC_INTSRC_NUM_265        
#define INTC_INTSRC_NUM_265                                     (265U)
#endif /* INTC_INTSRC_NUM_265 */
/* External interrupt source(SPI): INTID 266 - CAN0_ROUTE5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE5                                   (266U)
#ifndef INTC_INTSRC_NUM_266        
#define INTC_INTSRC_NUM_266                                     (266U)
#endif /* INTC_INTSRC_NUM_266 */
/* External interrupt source(SPI): INTID 267 - CAN0_ROUTE6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE6                                   (267U)
#ifndef INTC_INTSRC_NUM_267        
#define INTC_INTSRC_NUM_267                                     (267U)
#endif /* INTC_INTSRC_NUM_267 */
/* External interrupt source(SPI): INTID 268 - CAN0_ROUTE7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE7                                   (268U)
#ifndef INTC_INTSRC_NUM_268        
#define INTC_INTSRC_NUM_268                                     (268U)
#endif /* INTC_INTSRC_NUM_268 */
/* External interrupt source(SPI): INTID 269 - CAN0_ROUTE8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE8                                   (269U)
#ifndef INTC_INTSRC_NUM_269        
#define INTC_INTSRC_NUM_269                                     (269U)
#endif /* INTC_INTSRC_NUM_269 */
/* External interrupt source(SPI): INTID 270 - CAN0_ROUTE9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE9                                   (270U)
#ifndef INTC_INTSRC_NUM_270        
#define INTC_INTSRC_NUM_270                                     (270U)
#endif /* INTC_INTSRC_NUM_270 */
/* External interrupt source(SPI): INTID 271 - CAN0_ROUTE10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE10                                   (271U)
#ifndef INTC_INTSRC_NUM_271        
#define INTC_INTSRC_NUM_271                                     (271U)
#endif /* INTC_INTSRC_NUM_271 */
/* External interrupt source(SPI): INTID 272 - CAN0_ROUTE11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE11                                   (272U)
#ifndef INTC_INTSRC_NUM_272        
#define INTC_INTSRC_NUM_272                                     (272U)
#endif /* INTC_INTSRC_NUM_272 */
/* External interrupt source(SPI): INTID 273 - CAN0_ROUTE12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE12                                   (273U)
#ifndef INTC_INTSRC_NUM_273        
#define INTC_INTSRC_NUM_273                                     (273U)
#endif /* INTC_INTSRC_NUM_273 */
/* External interrupt source(SPI): INTID 274 - CAN0_ROUTE13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE13                                   (274U)
#ifndef INTC_INTSRC_NUM_274        
#define INTC_INTSRC_NUM_274                                     (274U)
#endif /* INTC_INTSRC_NUM_274 */
/* External interrupt source(SPI): INTID 275 - CAN0_ROUTE14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE14                                   (275U)
#ifndef INTC_INTSRC_NUM_275        
#define INTC_INTSRC_NUM_275                                     (275U)
#endif /* INTC_INTSRC_NUM_275 */
/* External interrupt source(SPI): INTID 276 - CAN0_ROUTE15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN0_ROUTE15                                   (276U)
#ifndef INTC_INTSRC_NUM_276        
#define INTC_INTSRC_NUM_276                                     (276U)
#endif /* INTC_INTSRC_NUM_276 */
/* External interrupt source(SPI): INTID 293 - CAN12_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN12_INT0                                   (293U)
#ifndef INTC_INTSRC_NUM_293        
#define INTC_INTSRC_NUM_293                                     (293U)
#endif /* INTC_INTSRC_NUM_293 */
/* External interrupt source(SPI): INTID 294 - CAN12_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN12_INT1                                   (294U)
#ifndef INTC_INTSRC_NUM_294        
#define INTC_INTSRC_NUM_294                                     (294U)
#endif /* INTC_INTSRC_NUM_294 */
/* External interrupt source(SPI): INTID 295 - CAN11_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN11_INT0                                   (295U)
#ifndef INTC_INTSRC_NUM_295        
#define INTC_INTSRC_NUM_295                                     (295U)
#endif /* INTC_INTSRC_NUM_295 */
/* External interrupt source(SPI): INTID 296 - CAN11_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN11_INT1                                   (296U)
#ifndef INTC_INTSRC_NUM_296        
#define INTC_INTSRC_NUM_296                                     (296U)
#endif /* INTC_INTSRC_NUM_296 */
/* External interrupt source(SPI): INTID 297 - CAN10_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN10_INT0                                   (297U)
#ifndef INTC_INTSRC_NUM_297        
#define INTC_INTSRC_NUM_297                                     (297U)
#endif /* INTC_INTSRC_NUM_297 */
/* External interrupt source(SPI): INTID 298 - CAN10_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN10_INT1                                   (298U)
#ifndef INTC_INTSRC_NUM_298        
#define INTC_INTSRC_NUM_298                                     (298U)
#endif /* INTC_INTSRC_NUM_298 */
/* External interrupt source(SPI): INTID 299 - CAN1_DMU0_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_DMU0_INT                                   (299U)
#ifndef INTC_INTSRC_NUM_299        
#define INTC_INTSRC_NUM_299                                     (299U)
#endif /* INTC_INTSRC_NUM_299 */
/* External interrupt source(SPI): INTID 300 - CAN1_DMU1_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_DMU1_INT                                   (300U)
#ifndef INTC_INTSRC_NUM_300        
#define INTC_INTSRC_NUM_300                                     (300U)
#endif /* INTC_INTSRC_NUM_300 */
/* External interrupt source(SPI): INTID 301 - CAN1_DMU2_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_DMU2_INT                                   (301U)
#ifndef INTC_INTSRC_NUM_301        
#define INTC_INTSRC_NUM_301                                     (301U)
#endif /* INTC_INTSRC_NUM_301 */
/* External interrupt source(SPI): INTID 302 - CAN1_ROUTE0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE0                                   (302U)
#ifndef INTC_INTSRC_NUM_302        
#define INTC_INTSRC_NUM_302                                     (302U)
#endif /* INTC_INTSRC_NUM_302 */
/* External interrupt source(SPI): INTID 303 - CAN1_ROUTE1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE1                                   (303U)
#ifndef INTC_INTSRC_NUM_303        
#define INTC_INTSRC_NUM_303                                     (303U)
#endif /* INTC_INTSRC_NUM_303 */
/* External interrupt source(SPI): INTID 304 - CAN1_ROUTE2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE2                                   (304U)
#ifndef INTC_INTSRC_NUM_304        
#define INTC_INTSRC_NUM_304                                     (304U)
#endif /* INTC_INTSRC_NUM_304 */
/* External interrupt source(SPI): INTID 305 - CAN1_ROUTE3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE3                                   (305U)
#ifndef INTC_INTSRC_NUM_305        
#define INTC_INTSRC_NUM_305                                     (305U)
#endif /* INTC_INTSRC_NUM_305 */
/* External interrupt source(SPI): INTID 306 - CAN1_ROUTE4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE4                                   (306U)
#ifndef INTC_INTSRC_NUM_306        
#define INTC_INTSRC_NUM_306                                     (306U)
#endif /* INTC_INTSRC_NUM_306 */
/* External interrupt source(SPI): INTID 307 - CAN1_ROUTE5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE5                                   (307U)
#ifndef INTC_INTSRC_NUM_307        
#define INTC_INTSRC_NUM_307                                     (307U)
#endif /* INTC_INTSRC_NUM_307 */
/* External interrupt source(SPI): INTID 308 - CAN1_ROUTE6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE6                                   (308U)
#ifndef INTC_INTSRC_NUM_308        
#define INTC_INTSRC_NUM_308                                     (308U)
#endif /* INTC_INTSRC_NUM_308 */
/* External interrupt source(SPI): INTID 309 - CAN1_ROUTE7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE7                                   (309U)
#ifndef INTC_INTSRC_NUM_309        
#define INTC_INTSRC_NUM_309                                     (309U)
#endif /* INTC_INTSRC_NUM_309 */
/* External interrupt source(SPI): INTID 310 - CAN1_ROUTE8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE8                                   (310U)
#ifndef INTC_INTSRC_NUM_310        
#define INTC_INTSRC_NUM_310                                     (310U)
#endif /* INTC_INTSRC_NUM_310 */
/* External interrupt source(SPI): INTID 311 - CAN1_ROUTE9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE9                                   (311U)
#ifndef INTC_INTSRC_NUM_311        
#define INTC_INTSRC_NUM_311                                     (311U)
#endif /* INTC_INTSRC_NUM_311 */
/* External interrupt source(SPI): INTID 312 - CAN1_ROUTE10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE10                                   (312U)
#ifndef INTC_INTSRC_NUM_312        
#define INTC_INTSRC_NUM_312                                     (312U)
#endif /* INTC_INTSRC_NUM_312 */
/* External interrupt source(SPI): INTID 313 - CAN1_ROUTE11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE11                                   (313U)
#ifndef INTC_INTSRC_NUM_313        
#define INTC_INTSRC_NUM_313                                     (313U)
#endif /* INTC_INTSRC_NUM_313 */
/* External interrupt source(SPI): INTID 314 - CAN1_ROUTE12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE12                                   (314U)
#ifndef INTC_INTSRC_NUM_314        
#define INTC_INTSRC_NUM_314                                     (314U)
#endif /* INTC_INTSRC_NUM_314 */
/* External interrupt source(SPI): INTID 315 - CAN1_ROUTE13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE13                                   (315U)
#ifndef INTC_INTSRC_NUM_315        
#define INTC_INTSRC_NUM_315                                     (315U)
#endif /* INTC_INTSRC_NUM_315 */
/* External interrupt source(SPI): INTID 316 - CAN1_ROUTE14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE14                                   (316U)
#ifndef INTC_INTSRC_NUM_316        
#define INTC_INTSRC_NUM_316                                     (316U)
#endif /* INTC_INTSRC_NUM_316 */
/* External interrupt source(SPI): INTID 317 - CAN1_ROUTE15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN1_ROUTE15                                   (317U)
#ifndef INTC_INTSRC_NUM_317        
#define INTC_INTSRC_NUM_317                                     (317U)
#endif /* INTC_INTSRC_NUM_317 */
/* External interrupt source(SPI): INTID 377 - SARADC0_G0SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC0_G0SR0                                   (377U)
#ifndef INTC_INTSRC_NUM_377        
#define INTC_INTSRC_NUM_377                                     (377U)
#endif /* INTC_INTSRC_NUM_377 */
/* External interrupt source(SPI): INTID 378 - SARADC0_G0SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC0_G0SR1                                   (378U)
#ifndef INTC_INTSRC_NUM_378        
#define INTC_INTSRC_NUM_378                                     (378U)
#endif /* INTC_INTSRC_NUM_378 */
/* External interrupt source(SPI): INTID 379 - SARADC0_G0SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC0_G0SR2                                   (379U)
#ifndef INTC_INTSRC_NUM_379        
#define INTC_INTSRC_NUM_379                                     (379U)
#endif /* INTC_INTSRC_NUM_379 */
/* External interrupt source(SPI): INTID 380 - SARADC0_G0SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC0_G0SR3                                   (380U)
#ifndef INTC_INTSRC_NUM_380        
#define INTC_INTSRC_NUM_380                                     (380U)
#endif /* INTC_INTSRC_NUM_380 */
/* External interrupt source(SPI): INTID 383 - SARADC1_G1SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC1_G1SR0                                   (383U)
#ifndef INTC_INTSRC_NUM_383        
#define INTC_INTSRC_NUM_383                                     (383U)
#endif /* INTC_INTSRC_NUM_383 */
/* External interrupt source(SPI): INTID 384 - SARADC1_G1SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC1_G1SR1                                   (384U)
#ifndef INTC_INTSRC_NUM_384        
#define INTC_INTSRC_NUM_384                                     (384U)
#endif /* INTC_INTSRC_NUM_384 */
/* External interrupt source(SPI): INTID 385 - SARADC1_G1SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC1_G1SR2                                   (385U)
#ifndef INTC_INTSRC_NUM_385        
#define INTC_INTSRC_NUM_385                                     (385U)
#endif /* INTC_INTSRC_NUM_385 */
/* External interrupt source(SPI): INTID 386 - SARADC1_G1SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC1_G1SR3                                   (386U)
#ifndef INTC_INTSRC_NUM_386        
#define INTC_INTSRC_NUM_386                                     (386U)
#endif /* INTC_INTSRC_NUM_386 */
/* External interrupt source(SPI): INTID 389 - SARADC2_G2SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC2_G2SR0                                   (389U)
#ifndef INTC_INTSRC_NUM_389        
#define INTC_INTSRC_NUM_389                                     (389U)
#endif /* INTC_INTSRC_NUM_389 */
/* External interrupt source(SPI): INTID 390 - SARADC2_G2SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC2_G2SR1                                   (390U)
#ifndef INTC_INTSRC_NUM_390        
#define INTC_INTSRC_NUM_390                                     (390U)
#endif /* INTC_INTSRC_NUM_390 */
/* External interrupt source(SPI): INTID 391 - SARADC2_G2SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC2_G2SR2                                   (391U)
#ifndef INTC_INTSRC_NUM_391        
#define INTC_INTSRC_NUM_391                                     (391U)
#endif /* INTC_INTSRC_NUM_391 */
/* External interrupt source(SPI): INTID 392 - SARADC2_G2SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC2_G2SR3                                   (392U)
#ifndef INTC_INTSRC_NUM_392        
#define INTC_INTSRC_NUM_392                                     (392U)
#endif /* INTC_INTSRC_NUM_392 */
/* External interrupt source(SPI): INTID 395 - SARADC3_G3SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC3_G3SR0                                   (395U)
#ifndef INTC_INTSRC_NUM_395        
#define INTC_INTSRC_NUM_395                                     (395U)
#endif /* INTC_INTSRC_NUM_395 */
/* External interrupt source(SPI): INTID 396 - SARADC3_G3SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC3_G3SR1                                   (396U)
#ifndef INTC_INTSRC_NUM_396        
#define INTC_INTSRC_NUM_396                                     (396U)
#endif /* INTC_INTSRC_NUM_396 */
/* External interrupt source(SPI): INTID 397 - SARADC3_G3SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC3_G3SR2                                   (397U)
#ifndef INTC_INTSRC_NUM_397        
#define INTC_INTSRC_NUM_397                                     (397U)
#endif /* INTC_INTSRC_NUM_397 */
/* External interrupt source(SPI): INTID 398 - SARADC3_G3SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC3_G3SR3                                   (398U)
#ifndef INTC_INTSRC_NUM_398        
#define INTC_INTSRC_NUM_398                                     (398U)
#endif /* INTC_INTSRC_NUM_398 */
/* External interrupt source(SPI): INTID 431 - SAR_FC_C0SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAR_FC_C0SR0                                   (431U)
#ifndef INTC_INTSRC_NUM_431        
#define INTC_INTSRC_NUM_431                                     (431U)
#endif /* INTC_INTSRC_NUM_431 */
/* External interrupt source(SPI): INTID 432 - SAR_FC_C0SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAR_FC_C0SR1                                   (432U)
#ifndef INTC_INTSRC_NUM_432        
#define INTC_INTSRC_NUM_432                                     (432U)
#endif /* INTC_INTSRC_NUM_432 */
/* External interrupt source(SPI): INTID 433 - SAR_FC_C0SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAR_FC_C0SR2                                   (433U)
#ifndef INTC_INTSRC_NUM_433        
#define INTC_INTSRC_NUM_433                                     (433U)
#endif /* INTC_INTSRC_NUM_433 */
/* External interrupt source(SPI): INTID 434 - SAR_FC_C0SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAR_FC_C0SR3                                   (434U)
#ifndef INTC_INTSRC_NUM_434        
#define INTC_INTSRC_NUM_434                                     (434U)
#endif /* INTC_INTSRC_NUM_434 */
/* External interrupt source(SPI): INTID 435 - SAR_FC_C1SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAR_FC_C1SR0                                   (435U)
#ifndef INTC_INTSRC_NUM_435        
#define INTC_INTSRC_NUM_435                                     (435U)
#endif /* INTC_INTSRC_NUM_435 */
/* External interrupt source(SPI): INTID 436 - SAR_FC_C1SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAR_FC_C1SR1                                   (436U)
#ifndef INTC_INTSRC_NUM_436        
#define INTC_INTSRC_NUM_436                                     (436U)
#endif /* INTC_INTSRC_NUM_436 */
/* External interrupt source(SPI): INTID 437 - SAR_FC_C1SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAR_FC_C1SR2                                   (437U)
#ifndef INTC_INTSRC_NUM_437        
#define INTC_INTSRC_NUM_437                                     (437U)
#endif /* INTC_INTSRC_NUM_437 */
/* External interrupt source(SPI): INTID 438 - SAR_FC_C1SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SAR_FC_C1SR3                                   (438U)
#ifndef INTC_INTSRC_NUM_438        
#define INTC_INTSRC_NUM_438                                     (438U)
#endif /* INTC_INTSRC_NUM_438 */
/* External interrupt source(SPI): INTID 455 - TSENSOR0_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_TSENSOR0_INT                                   (455U)
#ifndef INTC_INTSRC_NUM_455        
#define INTC_INTSRC_NUM_455                                     (455U)
#endif /* INTC_INTSRC_NUM_455 */
/* External interrupt source(SPI): INTID 457 - TSENSOR1_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_TSENSOR1_INT                                   (457U)
#ifndef INTC_INTSRC_NUM_457        
#define INTC_INTSRC_NUM_457                                     (457U)
#endif /* INTC_INTSRC_NUM_457 */
/* External interrupt source(SPI): INTID 463 - ECRC_ERROR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ECRC_ERROR_INT                                   (463U)
#ifndef INTC_INTSRC_NUM_463        
#define INTC_INTSRC_NUM_463                                     (463U)
#endif /* INTC_INTSRC_NUM_463 */
/* External interrupt source(SPI): INTID 464 - ESPI0_TX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI0_TX_INT                                   (464U)
#ifndef INTC_INTSRC_NUM_464        
#define INTC_INTSRC_NUM_464                                     (464U)
#endif /* INTC_INTSRC_NUM_464 */
/* External interrupt source(SPI): INTID 465 - ESPI0_RX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI0_RX_INT                                   (465U)
#ifndef INTC_INTSRC_NUM_465        
#define INTC_INTSRC_NUM_465                                     (465U)
#endif /* INTC_INTSRC_NUM_465 */
/* External interrupt source(SPI): INTID 466 - ESPI0_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI0_ERR_INT                                   (466U)
#ifndef INTC_INTSRC_NUM_466        
#define INTC_INTSRC_NUM_466                                     (466U)
#endif /* INTC_INTSRC_NUM_466 */
/* External interrupt source(SPI): INTID 467 - ESPI0_PT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI0_PT_INT                                   (467U)
#ifndef INTC_INTSRC_NUM_467        
#define INTC_INTSRC_NUM_467                                     (467U)
#endif /* INTC_INTSRC_NUM_467 */
/* External interrupt source(SPI): INTID 468 - ESPI0_U_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI0_U_INT                                   (468U)
#ifndef INTC_INTSRC_NUM_468        
#define INTC_INTSRC_NUM_468                                     (468U)
#endif /* INTC_INTSRC_NUM_468 */
/* External interrupt source(SPI): INTID 469 - ESPI0_HC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI0_HC_INT                                   (469U)
#ifndef INTC_INTSRC_NUM_469        
#define INTC_INTSRC_NUM_469                                     (469U)
#endif /* INTC_INTSRC_NUM_469 */
/* External interrupt source(SPI): INTID 470 - ESPI0_SEF_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI0_SEF_INT                                   (470U)
#ifndef INTC_INTSRC_NUM_470        
#define INTC_INTSRC_NUM_470                                     (470U)
#endif /* INTC_INTSRC_NUM_470 */
/* External interrupt source(SPI): INTID 473 - ESPI1_TX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI1_TX_INT                                   (473U)
#ifndef INTC_INTSRC_NUM_473        
#define INTC_INTSRC_NUM_473                                     (473U)
#endif /* INTC_INTSRC_NUM_473 */
/* External interrupt source(SPI): INTID 474 - ESPI1_RX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI1_RX_INT                                   (474U)
#ifndef INTC_INTSRC_NUM_474        
#define INTC_INTSRC_NUM_474                                     (474U)
#endif /* INTC_INTSRC_NUM_474 */
/* External interrupt source(SPI): INTID 475 - ESPI1_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI1_ERR_INT                                   (475U)
#ifndef INTC_INTSRC_NUM_475        
#define INTC_INTSRC_NUM_475                                     (475U)
#endif /* INTC_INTSRC_NUM_475 */
/* External interrupt source(SPI): INTID 476 - ESPI1_PT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI1_PT_INT                                   (476U)
#ifndef INTC_INTSRC_NUM_476        
#define INTC_INTSRC_NUM_476                                     (476U)
#endif /* INTC_INTSRC_NUM_476 */
/* External interrupt source(SPI): INTID 477 - ESPI1_U_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI1_U_INT                                   (477U)
#ifndef INTC_INTSRC_NUM_477        
#define INTC_INTSRC_NUM_477                                     (477U)
#endif /* INTC_INTSRC_NUM_477 */
/* External interrupt source(SPI): INTID 478 - ESPI1_HC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI1_HC_INT                                   (478U)
#ifndef INTC_INTSRC_NUM_478        
#define INTC_INTSRC_NUM_478                                     (478U)
#endif /* INTC_INTSRC_NUM_478 */
/* External interrupt source(SPI): INTID 479 - ESPI1_SEF_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI1_SEF_INT                                   (479U)
#ifndef INTC_INTSRC_NUM_479        
#define INTC_INTSRC_NUM_479                                     (479U)
#endif /* INTC_INTSRC_NUM_479 */
/* External interrupt source(SPI): INTID 482 - ESPI2_TX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI2_TX_INT                                   (482U)
#ifndef INTC_INTSRC_NUM_482        
#define INTC_INTSRC_NUM_482                                     (482U)
#endif /* INTC_INTSRC_NUM_482 */
/* External interrupt source(SPI): INTID 483 - ESPI2_RX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI2_RX_INT                                   (483U)
#ifndef INTC_INTSRC_NUM_483        
#define INTC_INTSRC_NUM_483                                     (483U)
#endif /* INTC_INTSRC_NUM_483 */
/* External interrupt source(SPI): INTID 484 - ESPI2_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI2_ERR_INT                                   (484U)
#ifndef INTC_INTSRC_NUM_484        
#define INTC_INTSRC_NUM_484                                     (484U)
#endif /* INTC_INTSRC_NUM_484 */
/* External interrupt source(SPI): INTID 485 - ESPI2_PT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI2_PT_INT                                   (485U)
#ifndef INTC_INTSRC_NUM_485        
#define INTC_INTSRC_NUM_485                                     (485U)
#endif /* INTC_INTSRC_NUM_485 */
/* External interrupt source(SPI): INTID 486 - ESPI2_U_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI2_U_INT                                   (486U)
#ifndef INTC_INTSRC_NUM_486        
#define INTC_INTSRC_NUM_486                                     (486U)
#endif /* INTC_INTSRC_NUM_486 */
/* External interrupt source(SPI): INTID 487 - ESPI2_HC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI2_HC_INT                                   (487U)
#ifndef INTC_INTSRC_NUM_487        
#define INTC_INTSRC_NUM_487                                     (487U)
#endif /* INTC_INTSRC_NUM_487 */
/* External interrupt source(SPI): INTID 488 - ESPI2_SEF_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI2_SEF_INT                                   (488U)
#ifndef INTC_INTSRC_NUM_488        
#define INTC_INTSRC_NUM_488                                     (488U)
#endif /* INTC_INTSRC_NUM_488 */
/* External interrupt source(SPI): INTID 491 - ESPI3_TX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI3_TX_INT                                   (491U)
#ifndef INTC_INTSRC_NUM_491        
#define INTC_INTSRC_NUM_491                                     (491U)
#endif /* INTC_INTSRC_NUM_491 */
/* External interrupt source(SPI): INTID 492 - ESPI3_RX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI3_RX_INT                                   (492U)
#ifndef INTC_INTSRC_NUM_492        
#define INTC_INTSRC_NUM_492                                     (492U)
#endif /* INTC_INTSRC_NUM_492 */
/* External interrupt source(SPI): INTID 493 - ESPI3_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI3_ERR_INT                                   (493U)
#ifndef INTC_INTSRC_NUM_493        
#define INTC_INTSRC_NUM_493                                     (493U)
#endif /* INTC_INTSRC_NUM_493 */
/* External interrupt source(SPI): INTID 494 - ESPI3_PT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI3_PT_INT                                   (494U)
#ifndef INTC_INTSRC_NUM_494        
#define INTC_INTSRC_NUM_494                                     (494U)
#endif /* INTC_INTSRC_NUM_494 */
/* External interrupt source(SPI): INTID 495 - ESPI3_U_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI3_U_INT                                   (495U)
#ifndef INTC_INTSRC_NUM_495        
#define INTC_INTSRC_NUM_495                                     (495U)
#endif /* INTC_INTSRC_NUM_495 */
/* External interrupt source(SPI): INTID 496 - ESPI3_HC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI3_HC_INT                                   (496U)
#ifndef INTC_INTSRC_NUM_496        
#define INTC_INTSRC_NUM_496                                     (496U)
#endif /* INTC_INTSRC_NUM_496 */
/* External interrupt source(SPI): INTID 497 - ESPI3_SEF_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI3_SEF_INT                                   (497U)
#ifndef INTC_INTSRC_NUM_497        
#define INTC_INTSRC_NUM_497                                     (497U)
#endif /* INTC_INTSRC_NUM_497 */
/* External interrupt source(SPI): INTID 500 - ESPI4_TX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI4_TX_INT                                   (500U)
#ifndef INTC_INTSRC_NUM_500        
#define INTC_INTSRC_NUM_500                                     (500U)
#endif /* INTC_INTSRC_NUM_500 */
/* External interrupt source(SPI): INTID 501 - ESPI4_RX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI4_RX_INT                                   (501U)
#ifndef INTC_INTSRC_NUM_501        
#define INTC_INTSRC_NUM_501                                     (501U)
#endif /* INTC_INTSRC_NUM_501 */
/* External interrupt source(SPI): INTID 502 - ESPI4_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI4_ERR_INT                                   (502U)
#ifndef INTC_INTSRC_NUM_502        
#define INTC_INTSRC_NUM_502                                     (502U)
#endif /* INTC_INTSRC_NUM_502 */
/* External interrupt source(SPI): INTID 503 - ESPI4_PT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI4_PT_INT                                   (503U)
#ifndef INTC_INTSRC_NUM_503        
#define INTC_INTSRC_NUM_503                                     (503U)
#endif /* INTC_INTSRC_NUM_503 */
/* External interrupt source(SPI): INTID 504 - ESPI4_U_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI4_U_INT                                   (504U)
#ifndef INTC_INTSRC_NUM_504        
#define INTC_INTSRC_NUM_504                                     (504U)
#endif /* INTC_INTSRC_NUM_504 */
/* External interrupt source(SPI): INTID 505 - ESPI4_HC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI4_HC_INT                                   (505U)
#ifndef INTC_INTSRC_NUM_505        
#define INTC_INTSRC_NUM_505                                     (505U)
#endif /* INTC_INTSRC_NUM_505 */
/* External interrupt source(SPI): INTID 506 - ESPI4_SEF_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI4_SEF_INT                                   (506U)
#ifndef INTC_INTSRC_NUM_506        
#define INTC_INTSRC_NUM_506                                     (506U)
#endif /* INTC_INTSRC_NUM_506 */
/* External interrupt source(SPI): INTID 509 - ESPI5_TX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI5_TX_INT                                   (509U)
#ifndef INTC_INTSRC_NUM_509        
#define INTC_INTSRC_NUM_509                                     (509U)
#endif /* INTC_INTSRC_NUM_509 */
/* External interrupt source(SPI): INTID 510 - ESPI5_RX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI5_RX_INT                                   (510U)
#ifndef INTC_INTSRC_NUM_510        
#define INTC_INTSRC_NUM_510                                     (510U)
#endif /* INTC_INTSRC_NUM_510 */
/* External interrupt source(SPI): INTID 511 - ESPI5_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI5_ERR_INT                                   (511U)
#ifndef INTC_INTSRC_NUM_511        
#define INTC_INTSRC_NUM_511                                     (511U)
#endif /* INTC_INTSRC_NUM_511 */
/* External interrupt source(SPI): INTID 512 - ESPI5_PT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI5_PT_INT                                   (512U)
#ifndef INTC_INTSRC_NUM_512        
#define INTC_INTSRC_NUM_512                                     (512U)
#endif /* INTC_INTSRC_NUM_512 */
/* External interrupt source(SPI): INTID 513 - ESPI5_U_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI5_U_INT                                   (513U)
#ifndef INTC_INTSRC_NUM_513        
#define INTC_INTSRC_NUM_513                                     (513U)
#endif /* INTC_INTSRC_NUM_513 */
/* External interrupt source(SPI): INTID 514 - ESPI5_HC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI5_HC_INT                                   (514U)
#ifndef INTC_INTSRC_NUM_514        
#define INTC_INTSRC_NUM_514                                     (514U)
#endif /* INTC_INTSRC_NUM_514 */
/* External interrupt source(SPI): INTID 515 - ESPI5_SEF_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI5_SEF_INT                                   (515U)
#ifndef INTC_INTSRC_NUM_515        
#define INTC_INTSRC_NUM_515                                     (515U)
#endif /* INTC_INTSRC_NUM_515 */
/* External interrupt source(SPI): INTID 572 - SENT0_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT0_RX_ERROR                                   (572U)
#ifndef INTC_INTSRC_NUM_572        
#define INTC_INTSRC_NUM_572                                     (572U)
#endif /* INTC_INTSRC_NUM_572 */
/* External interrupt source(SPI): INTID 573 - SENT0_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT0_RX_VALID                                   (573U)
#ifndef INTC_INTSRC_NUM_573        
#define INTC_INTSRC_NUM_573                                     (573U)
#endif /* INTC_INTSRC_NUM_573 */
/* External interrupt source(SPI): INTID 576 - SENT1_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT1_RX_ERROR                                   (576U)
#ifndef INTC_INTSRC_NUM_576        
#define INTC_INTSRC_NUM_576                                     (576U)
#endif /* INTC_INTSRC_NUM_576 */
/* External interrupt source(SPI): INTID 577 - SENT1_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT1_RX_VALID                                   (577U)
#ifndef INTC_INTSRC_NUM_577        
#define INTC_INTSRC_NUM_577                                     (577U)
#endif /* INTC_INTSRC_NUM_577 */
/* External interrupt source(SPI): INTID 580 - SENT2_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT2_RX_ERROR                                   (580U)
#ifndef INTC_INTSRC_NUM_580        
#define INTC_INTSRC_NUM_580                                     (580U)
#endif /* INTC_INTSRC_NUM_580 */
/* External interrupt source(SPI): INTID 581 - SENT2_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT2_RX_VALID                                   (581U)
#ifndef INTC_INTSRC_NUM_581        
#define INTC_INTSRC_NUM_581                                     (581U)
#endif /* INTC_INTSRC_NUM_581 */
/* External interrupt source(SPI): INTID 584 - SENT3_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT3_RX_ERROR                                   (584U)
#ifndef INTC_INTSRC_NUM_584        
#define INTC_INTSRC_NUM_584                                     (584U)
#endif /* INTC_INTSRC_NUM_584 */
/* External interrupt source(SPI): INTID 585 - SENT3_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT3_RX_VALID                                   (585U)
#ifndef INTC_INTSRC_NUM_585        
#define INTC_INTSRC_NUM_585                                     (585U)
#endif /* INTC_INTSRC_NUM_585 */
/* External interrupt source(SPI): INTID 588 - SENT4_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT4_RX_ERROR                                   (588U)
#ifndef INTC_INTSRC_NUM_588        
#define INTC_INTSRC_NUM_588                                     (588U)
#endif /* INTC_INTSRC_NUM_588 */
/* External interrupt source(SPI): INTID 589 - SENT4_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT4_RX_VALID                                   (589U)
#ifndef INTC_INTSRC_NUM_589        
#define INTC_INTSRC_NUM_589                                     (589U)
#endif /* INTC_INTSRC_NUM_589 */
/* External interrupt source(SPI): INTID 592 - SENT5_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT5_RX_ERROR                                   (592U)
#ifndef INTC_INTSRC_NUM_592        
#define INTC_INTSRC_NUM_592                                     (592U)
#endif /* INTC_INTSRC_NUM_592 */
/* External interrupt source(SPI): INTID 593 - SENT5_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT5_RX_VALID                                   (593U)
#ifndef INTC_INTSRC_NUM_593        
#define INTC_INTSRC_NUM_593                                     (593U)
#endif /* INTC_INTSRC_NUM_593 */
/* External interrupt source(SPI): INTID 622 - I2C0_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_I2C0_ERR_INT                                   (622U)
#ifndef INTC_INTSRC_NUM_622        
#define INTC_INTSRC_NUM_622                                     (622U)
#endif /* INTC_INTSRC_NUM_622 */
/* External interrupt source(SPI): INTID 623 - I2C0_EVENT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_I2C0_EVENT_INT                                   (623U)
#ifndef INTC_INTSRC_NUM_623        
#define INTC_INTSRC_NUM_623                                     (623U)
#endif /* INTC_INTSRC_NUM_623 */
/* External interrupt source(SPI): INTID 624 - I2C1_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_I2C1_ERR_INT                                   (624U)
#ifndef INTC_INTSRC_NUM_624        
#define INTC_INTSRC_NUM_624                                     (624U)
#endif /* INTC_INTSRC_NUM_624 */
/* External interrupt source(SPI): INTID 625 - I2C1_EVENT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_I2C1_EVENT_INT                                   (625U)
#ifndef INTC_INTSRC_NUM_625        
#define INTC_INTSRC_NUM_625                                     (625U)
#endif /* INTC_INTSRC_NUM_625 */
/* External interrupt source(SPI): INTID 631 - ASI0_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI0_RX                                   (631U)
#ifndef INTC_INTSRC_NUM_631        
#define INTC_INTSRC_NUM_631                                     (631U)
#endif /* INTC_INTSRC_NUM_631 */
/* External interrupt source(SPI): INTID 632 - ASI0_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI0_TX                                   (632U)
#ifndef INTC_INTSRC_NUM_632        
#define INTC_INTSRC_NUM_632                                     (632U)
#endif /* INTC_INTSRC_NUM_632 */
/* External interrupt source(SPI): INTID 633 - ASI0_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI0_ERROR                                   (633U)
#ifndef INTC_INTSRC_NUM_633        
#define INTC_INTSRC_NUM_633                                     (633U)
#endif /* INTC_INTSRC_NUM_633 */
/* External interrupt source(SPI): INTID 634 - ASI0_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI0_ALL                                   (634U)
#ifndef INTC_INTSRC_NUM_634        
#define INTC_INTSRC_NUM_634                                     (634U)
#endif /* INTC_INTSRC_NUM_634 */
/* External interrupt source(SPI): INTID 636 - ASI1_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI1_RX                                   (636U)
#ifndef INTC_INTSRC_NUM_636        
#define INTC_INTSRC_NUM_636                                     (636U)
#endif /* INTC_INTSRC_NUM_636 */
/* External interrupt source(SPI): INTID 637 - ASI1_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI1_TX                                   (637U)
#ifndef INTC_INTSRC_NUM_637        
#define INTC_INTSRC_NUM_637                                     (637U)
#endif /* INTC_INTSRC_NUM_637 */
/* External interrupt source(SPI): INTID 638 - ASI1_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI1_ERROR                                   (638U)
#ifndef INTC_INTSRC_NUM_638        
#define INTC_INTSRC_NUM_638                                     (638U)
#endif /* INTC_INTSRC_NUM_638 */
/* External interrupt source(SPI): INTID 639 - ASI1_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI1_ALL                                   (639U)
#ifndef INTC_INTSRC_NUM_639        
#define INTC_INTSRC_NUM_639                                     (639U)
#endif /* INTC_INTSRC_NUM_639 */
/* External interrupt source(SPI): INTID 641 - ASI2_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI2_RX                                   (641U)
#ifndef INTC_INTSRC_NUM_641        
#define INTC_INTSRC_NUM_641                                     (641U)
#endif /* INTC_INTSRC_NUM_641 */
/* External interrupt source(SPI): INTID 642 - ASI2_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI2_TX                                   (642U)
#ifndef INTC_INTSRC_NUM_642        
#define INTC_INTSRC_NUM_642                                     (642U)
#endif /* INTC_INTSRC_NUM_642 */
/* External interrupt source(SPI): INTID 643 - ASI2_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI2_ERROR                                   (643U)
#ifndef INTC_INTSRC_NUM_643        
#define INTC_INTSRC_NUM_643                                     (643U)
#endif /* INTC_INTSRC_NUM_643 */
/* External interrupt source(SPI): INTID 644 - ASI2_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI2_ALL                                   (644U)
#ifndef INTC_INTSRC_NUM_644        
#define INTC_INTSRC_NUM_644                                     (644U)
#endif /* INTC_INTSRC_NUM_644 */
/* External interrupt source(SPI): INTID 646 - ASI3_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI3_RX                                   (646U)
#ifndef INTC_INTSRC_NUM_646        
#define INTC_INTSRC_NUM_646                                     (646U)
#endif /* INTC_INTSRC_NUM_646 */
/* External interrupt source(SPI): INTID 647 - ASI3_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI3_TX                                   (647U)
#ifndef INTC_INTSRC_NUM_647        
#define INTC_INTSRC_NUM_647                                     (647U)
#endif /* INTC_INTSRC_NUM_647 */
/* External interrupt source(SPI): INTID 648 - ASI3_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI3_ERROR                                   (648U)
#ifndef INTC_INTSRC_NUM_648        
#define INTC_INTSRC_NUM_648                                     (648U)
#endif /* INTC_INTSRC_NUM_648 */
/* External interrupt source(SPI): INTID 649 - ASI3_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI3_ALL                                   (649U)
#ifndef INTC_INTSRC_NUM_649        
#define INTC_INTSRC_NUM_649                                     (649U)
#endif /* INTC_INTSRC_NUM_649 */
/* External interrupt source(SPI): INTID 651 - ASI4_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI4_RX                                   (651U)
#ifndef INTC_INTSRC_NUM_651        
#define INTC_INTSRC_NUM_651                                     (651U)
#endif /* INTC_INTSRC_NUM_651 */
/* External interrupt source(SPI): INTID 652 - ASI4_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI4_TX                                   (652U)
#ifndef INTC_INTSRC_NUM_652        
#define INTC_INTSRC_NUM_652                                     (652U)
#endif /* INTC_INTSRC_NUM_652 */
/* External interrupt source(SPI): INTID 653 - ASI4_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI4_ERROR                                   (653U)
#ifndef INTC_INTSRC_NUM_653        
#define INTC_INTSRC_NUM_653                                     (653U)
#endif /* INTC_INTSRC_NUM_653 */
/* External interrupt source(SPI): INTID 654 - ASI4_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI4_ALL                                   (654U)
#ifndef INTC_INTSRC_NUM_654        
#define INTC_INTSRC_NUM_654                                     (654U)
#endif /* INTC_INTSRC_NUM_654 */
/* External interrupt source(SPI): INTID 656 - ASI5_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI5_RX                                   (656U)
#ifndef INTC_INTSRC_NUM_656        
#define INTC_INTSRC_NUM_656                                     (656U)
#endif /* INTC_INTSRC_NUM_656 */
/* External interrupt source(SPI): INTID 657 - ASI5_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI5_TX                                   (657U)
#ifndef INTC_INTSRC_NUM_657        
#define INTC_INTSRC_NUM_657                                     (657U)
#endif /* INTC_INTSRC_NUM_657 */
/* External interrupt source(SPI): INTID 658 - ASI5_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI5_ERROR                                   (658U)
#ifndef INTC_INTSRC_NUM_658        
#define INTC_INTSRC_NUM_658                                     (658U)
#endif /* INTC_INTSRC_NUM_658 */
/* External interrupt source(SPI): INTID 659 - ASI5_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI5_ALL                                   (659U)
#ifndef INTC_INTSRC_NUM_659        
#define INTC_INTSRC_NUM_659                                     (659U)
#endif /* INTC_INTSRC_NUM_659 */
/* External interrupt source(SPI): INTID 661 - ASI6_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI6_RX                                   (661U)
#ifndef INTC_INTSRC_NUM_661        
#define INTC_INTSRC_NUM_661                                     (661U)
#endif /* INTC_INTSRC_NUM_661 */
/* External interrupt source(SPI): INTID 662 - ASI6_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI6_TX                                   (662U)
#ifndef INTC_INTSRC_NUM_662        
#define INTC_INTSRC_NUM_662                                     (662U)
#endif /* INTC_INTSRC_NUM_662 */
/* External interrupt source(SPI): INTID 663 - ASI6_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI6_ERROR                                   (663U)
#ifndef INTC_INTSRC_NUM_663        
#define INTC_INTSRC_NUM_663                                     (663U)
#endif /* INTC_INTSRC_NUM_663 */
/* External interrupt source(SPI): INTID 664 - ASI6_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI6_ALL                                   (664U)
#ifndef INTC_INTSRC_NUM_664        
#define INTC_INTSRC_NUM_664                                     (664U)
#endif /* INTC_INTSRC_NUM_664 */
/* External interrupt source(SPI): INTID 666 - ASI7_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI7_RX                                   (666U)
#ifndef INTC_INTSRC_NUM_666        
#define INTC_INTSRC_NUM_666                                     (666U)
#endif /* INTC_INTSRC_NUM_666 */
/* External interrupt source(SPI): INTID 667 - ASI7_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI7_TX                                   (667U)
#ifndef INTC_INTSRC_NUM_667        
#define INTC_INTSRC_NUM_667                                     (667U)
#endif /* INTC_INTSRC_NUM_667 */
/* External interrupt source(SPI): INTID 668 - ASI7_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI7_ERROR                                   (668U)
#ifndef INTC_INTSRC_NUM_668        
#define INTC_INTSRC_NUM_668                                     (668U)
#endif /* INTC_INTSRC_NUM_668 */
/* External interrupt source(SPI): INTID 669 - ASI7_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI7_ALL                                   (669U)
#ifndef INTC_INTSRC_NUM_669        
#define INTC_INTSRC_NUM_669                                     (669U)
#endif /* INTC_INTSRC_NUM_669 */
/* External interrupt source(SPI): INTID 109 - ASI8_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI8_RX                                   (109U)
#ifndef INTC_INTSRC_NUM_109        
#define INTC_INTSRC_NUM_109                                     (109U)
#endif /* INTC_INTSRC_NUM_109 */
/* External interrupt source(SPI): INTID 110 - ASI8_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI8_TX                                   (110U)
#ifndef INTC_INTSRC_NUM_110        
#define INTC_INTSRC_NUM_110                                     (110U)
#endif /* INTC_INTSRC_NUM_110 */
/* External interrupt source(SPI): INTID 111 - ASI8_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI8_ERROR                                   (111U)
#ifndef INTC_INTSRC_NUM_111        
#define INTC_INTSRC_NUM_111                                     (111U)
#endif /* INTC_INTSRC_NUM_111 */
/* External interrupt source(SPI): INTID 112 - ASI8_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI8_ALL                                   (112U)
#ifndef INTC_INTSRC_NUM_112        
#define INTC_INTSRC_NUM_112                                     (112U)
#endif /* INTC_INTSRC_NUM_112 */
/* External interrupt source(SPI): INTID 113 - ASI9_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI9_RX                                   (113U)
#ifndef INTC_INTSRC_NUM_113        
#define INTC_INTSRC_NUM_113                                     (113U)
#endif /* INTC_INTSRC_NUM_113 */
/* External interrupt source(SPI): INTID 114 - ASI9_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI9_TX                                   (114U)
#ifndef INTC_INTSRC_NUM_114        
#define INTC_INTSRC_NUM_114                                     (114U)
#endif /* INTC_INTSRC_NUM_114 */
/* External interrupt source(SPI): INTID 143 - ASI9_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI9_ERROR                                   (143U)
#ifndef INTC_INTSRC_NUM_143        
#define INTC_INTSRC_NUM_143                                     (143U)
#endif /* INTC_INTSRC_NUM_143 */
/* External interrupt source(SPI): INTID 144 - ASI9_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI9_ALL                                   (144U)
#ifndef INTC_INTSRC_NUM_144        
#define INTC_INTSRC_NUM_144                                     (144U)
#endif /* INTC_INTSRC_NUM_144 */
/* External interrupt source(SPI): INTID 145 - ASI10_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI10_RX                                   (145U)
#ifndef INTC_INTSRC_NUM_145        
#define INTC_INTSRC_NUM_145                                     (145U)
#endif /* INTC_INTSRC_NUM_145 */
/* External interrupt source(SPI): INTID 146 - ASI10_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI10_TX                                   (146U)
#ifndef INTC_INTSRC_NUM_146        
#define INTC_INTSRC_NUM_146                                     (146U)
#endif /* INTC_INTSRC_NUM_146 */
/* External interrupt source(SPI): INTID 147 - ASI10_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI10_ERROR                                   (147U)
#ifndef INTC_INTSRC_NUM_147        
#define INTC_INTSRC_NUM_147                                     (147U)
#endif /* INTC_INTSRC_NUM_147 */
/* External interrupt source(SPI): INTID 148 - ASI10_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI10_ALL                                   (148U)
#ifndef INTC_INTSRC_NUM_148        
#define INTC_INTSRC_NUM_148                                     (148U)
#endif /* INTC_INTSRC_NUM_148 */
/* External interrupt source(SPI): INTID 242 - ASI11_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI11_RX                                   (242U)
#ifndef INTC_INTSRC_NUM_242        
#define INTC_INTSRC_NUM_242                                     (242U)
#endif /* INTC_INTSRC_NUM_242 */
/* External interrupt source(SPI): INTID 243 - ASI11_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI11_TX                                   (243U)
#ifndef INTC_INTSRC_NUM_243        
#define INTC_INTSRC_NUM_243                                     (243U)
#endif /* INTC_INTSRC_NUM_243 */
/* External interrupt source(SPI): INTID 244 - ASI11_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI11_ERROR                                   (244U)
#ifndef INTC_INTSRC_NUM_244        
#define INTC_INTSRC_NUM_244                                     (244U)
#endif /* INTC_INTSRC_NUM_244 */
/* External interrupt source(SPI): INTID 245 - ASI11_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI11_ALL                                   (245U)
#ifndef INTC_INTSRC_NUM_245        
#define INTC_INTSRC_NUM_245                                     (245U)
#endif /* INTC_INTSRC_NUM_245 */
/* External interrupt source(SPI): INTID 671 - EXTI0_IOUT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_EXTI0_IOUT0                                   (671U)
#ifndef INTC_INTSRC_NUM_671        
#define INTC_INTSRC_NUM_671                                     (671U)
#endif /* INTC_INTSRC_NUM_671 */
/* External interrupt source(SPI): INTID 672 - EXTI0_IOUT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_EXTI0_IOUT1                                   (672U)
#ifndef INTC_INTSRC_NUM_672        
#define INTC_INTSRC_NUM_672                                     (672U)
#endif /* INTC_INTSRC_NUM_672 */
/* External interrupt source(SPI): INTID 673 - EXTI0_IOUT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_EXTI0_IOUT2                                   (673U)
#ifndef INTC_INTSRC_NUM_673        
#define INTC_INTSRC_NUM_673                                     (673U)
#endif /* INTC_INTSRC_NUM_673 */
/* External interrupt source(SPI): INTID 674 - EXTI0_IOUT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_EXTI0_IOUT3                                   (674U)
#ifndef INTC_INTSRC_NUM_674        
#define INTC_INTSRC_NUM_674                                     (674U)
#endif /* INTC_INTSRC_NUM_674 */
/* External interrupt source(SPI): INTID 675 - EXTI0_IOUT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_EXTI0_IOUT4                                   (675U)
#ifndef INTC_INTSRC_NUM_675        
#define INTC_INTSRC_NUM_675                                     (675U)
#endif /* INTC_INTSRC_NUM_675 */
/* External interrupt source(SPI): INTID 676 - EXTI0_IOUT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_EXTI0_IOUT5                                   (676U)
#ifndef INTC_INTSRC_NUM_676        
#define INTC_INTSRC_NUM_676                                     (676U)
#endif /* INTC_INTSRC_NUM_676 */
/* External interrupt source(SPI): INTID 677 - EXTI0_IOUT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_EXTI0_IOUT6                                   (677U)
#ifndef INTC_INTSRC_NUM_677        
#define INTC_INTSRC_NUM_677                                     (677U)
#endif /* INTC_INTSRC_NUM_677 */
/* External interrupt source(SPI): INTID 678 - EXTI0_IOUT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_EXTI0_IOUT7                                   (678U)
#ifndef INTC_INTSRC_NUM_678        
#define INTC_INTSRC_NUM_678                                     (678U)
#endif /* INTC_INTSRC_NUM_678 */
/* External interrupt source(SPI): INTID 687 - GTM_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ERR_INT                                   (687U)
#ifndef INTC_INTSRC_NUM_687        
#define INTC_INTSRC_NUM_687                                     (687U)
#endif /* INTC_INTSRC_NUM_687 */
/* External interrupt source(SPI): INTID 688 - GTM_CMP_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_CMP_INT                                   (688U)
#ifndef INTC_INTSRC_NUM_688        
#define INTC_INTSRC_NUM_688                                     (688U)
#endif /* INTC_INTSRC_NUM_688 */
/* External interrupt source(SPI): INTID 689 - GTM_AEI_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_AEI_INT                                   (689U)
#ifndef INTC_INTSRC_NUM_689        
#define INTC_INTSRC_NUM_689                                     (689U)
#endif /* INTC_INTSRC_NUM_689 */
/* External interrupt source(SPI): INTID 690 - GTM_ARU_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ARU_INT0                                   (690U)
#ifndef INTC_INTSRC_NUM_690        
#define INTC_INTSRC_NUM_690                                     (690U)
#endif /* INTC_INTSRC_NUM_690 */
/* External interrupt source(SPI): INTID 691 - GTM_ARU_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ARU_INT1                                   (691U)
#ifndef INTC_INTSRC_NUM_691        
#define INTC_INTSRC_NUM_691                                     (691U)
#endif /* INTC_INTSRC_NUM_691 */
/* External interrupt source(SPI): INTID 692 - GTM_ARU_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ARU_INT2                                   (692U)
#ifndef INTC_INTSRC_NUM_692        
#define INTC_INTSRC_NUM_692                                     (692U)
#endif /* INTC_INTSRC_NUM_692 */
/* External interrupt source(SPI): INTID 693 - GTM_BRC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_BRC_INT                                   (693U)
#ifndef INTC_INTSRC_NUM_693        
#define INTC_INTSRC_NUM_693                                     (693U)
#endif /* INTC_INTSRC_NUM_693 */
/* External interrupt source(SPI): INTID 694 - GTM_SPE0_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_SPE0_INT                                   (694U)
#ifndef INTC_INTSRC_NUM_694        
#define INTC_INTSRC_NUM_694                                     (694U)
#endif /* INTC_INTSRC_NUM_694 */
/* External interrupt source(SPI): INTID 695 - GTM_SPE1_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_SPE1_INT                                   (695U)
#ifndef INTC_INTSRC_NUM_695        
#define INTC_INTSRC_NUM_695                                     (695U)
#endif /* INTC_INTSRC_NUM_695 */
/* External interrupt source(SPI): INTID 697 - GTM_PSM0_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM0_INT0                                   (697U)
#ifndef INTC_INTSRC_NUM_697        
#define INTC_INTSRC_NUM_697                                     (697U)
#endif /* INTC_INTSRC_NUM_697 */
/* External interrupt source(SPI): INTID 698 - GTM_PSM0_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM0_INT1                                   (698U)
#ifndef INTC_INTSRC_NUM_698        
#define INTC_INTSRC_NUM_698                                     (698U)
#endif /* INTC_INTSRC_NUM_698 */
/* External interrupt source(SPI): INTID 699 - GTM_PSM0_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM0_INT2                                   (699U)
#ifndef INTC_INTSRC_NUM_699        
#define INTC_INTSRC_NUM_699                                     (699U)
#endif /* INTC_INTSRC_NUM_699 */
/* External interrupt source(SPI): INTID 700 - GTM_PSM0_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM0_INT3                                   (700U)
#ifndef INTC_INTSRC_NUM_700        
#define INTC_INTSRC_NUM_700                                     (700U)
#endif /* INTC_INTSRC_NUM_700 */
/* External interrupt source(SPI): INTID 701 - GTM_PSM0_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM0_INT4                                   (701U)
#ifndef INTC_INTSRC_NUM_701        
#define INTC_INTSRC_NUM_701                                     (701U)
#endif /* INTC_INTSRC_NUM_701 */
/* External interrupt source(SPI): INTID 702 - GTM_PSM0_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM0_INT5                                   (702U)
#ifndef INTC_INTSRC_NUM_702        
#define INTC_INTSRC_NUM_702                                     (702U)
#endif /* INTC_INTSRC_NUM_702 */
/* External interrupt source(SPI): INTID 703 - GTM_PSM0_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM0_INT6                                   (703U)
#ifndef INTC_INTSRC_NUM_703        
#define INTC_INTSRC_NUM_703                                     (703U)
#endif /* INTC_INTSRC_NUM_703 */
/* External interrupt source(SPI): INTID 704 - GTM_PSM0_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM0_INT7                                   (704U)
#ifndef INTC_INTSRC_NUM_704        
#define INTC_INTSRC_NUM_704                                     (704U)
#endif /* INTC_INTSRC_NUM_704 */
/* External interrupt source(SPI): INTID 748 - GTM_TIM0_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM0_INT0                                   (748U)
#ifndef INTC_INTSRC_NUM_748        
#define INTC_INTSRC_NUM_748                                     (748U)
#endif /* INTC_INTSRC_NUM_748 */
/* External interrupt source(SPI): INTID 749 - GTM_TIM0_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM0_INT1                                   (749U)
#ifndef INTC_INTSRC_NUM_749        
#define INTC_INTSRC_NUM_749                                     (749U)
#endif /* INTC_INTSRC_NUM_749 */
/* External interrupt source(SPI): INTID 750 - GTM_TIM0_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM0_INT2                                   (750U)
#ifndef INTC_INTSRC_NUM_750        
#define INTC_INTSRC_NUM_750                                     (750U)
#endif /* INTC_INTSRC_NUM_750 */
/* External interrupt source(SPI): INTID 751 - GTM_TIM0_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM0_INT3                                   (751U)
#ifndef INTC_INTSRC_NUM_751        
#define INTC_INTSRC_NUM_751                                     (751U)
#endif /* INTC_INTSRC_NUM_751 */
/* External interrupt source(SPI): INTID 752 - GTM_TIM0_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM0_INT4                                   (752U)
#ifndef INTC_INTSRC_NUM_752        
#define INTC_INTSRC_NUM_752                                     (752U)
#endif /* INTC_INTSRC_NUM_752 */
/* External interrupt source(SPI): INTID 753 - GTM_TIM0_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM0_INT5                                   (753U)
#ifndef INTC_INTSRC_NUM_753        
#define INTC_INTSRC_NUM_753                                     (753U)
#endif /* INTC_INTSRC_NUM_753 */
/* External interrupt source(SPI): INTID 754 - GTM_TIM0_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM0_INT6                                   (754U)
#ifndef INTC_INTSRC_NUM_754        
#define INTC_INTSRC_NUM_754                                     (754U)
#endif /* INTC_INTSRC_NUM_754 */
/* External interrupt source(SPI): INTID 755 - GTM_TIM0_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM0_INT7                                   (755U)
#ifndef INTC_INTSRC_NUM_755        
#define INTC_INTSRC_NUM_755                                     (755U)
#endif /* INTC_INTSRC_NUM_755 */
/* External interrupt source(SPI): INTID 756 - GTM_TIM1_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM1_INT0                                   (756U)
#ifndef INTC_INTSRC_NUM_756        
#define INTC_INTSRC_NUM_756                                     (756U)
#endif /* INTC_INTSRC_NUM_756 */
/* External interrupt source(SPI): INTID 757 - GTM_TIM1_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM1_INT1                                   (757U)
#ifndef INTC_INTSRC_NUM_757        
#define INTC_INTSRC_NUM_757                                     (757U)
#endif /* INTC_INTSRC_NUM_757 */
/* External interrupt source(SPI): INTID 758 - GTM_TIM1_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM1_INT2                                   (758U)
#ifndef INTC_INTSRC_NUM_758        
#define INTC_INTSRC_NUM_758                                     (758U)
#endif /* INTC_INTSRC_NUM_758 */
/* External interrupt source(SPI): INTID 759 - GTM_TIM1_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM1_INT3                                   (759U)
#ifndef INTC_INTSRC_NUM_759        
#define INTC_INTSRC_NUM_759                                     (759U)
#endif /* INTC_INTSRC_NUM_759 */
/* External interrupt source(SPI): INTID 760 - GTM_TIM1_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM1_INT4                                   (760U)
#ifndef INTC_INTSRC_NUM_760        
#define INTC_INTSRC_NUM_760                                     (760U)
#endif /* INTC_INTSRC_NUM_760 */
/* External interrupt source(SPI): INTID 761 - GTM_TIM1_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM1_INT5                                   (761U)
#ifndef INTC_INTSRC_NUM_761        
#define INTC_INTSRC_NUM_761                                     (761U)
#endif /* INTC_INTSRC_NUM_761 */
/* External interrupt source(SPI): INTID 762 - GTM_TIM1_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM1_INT6                                   (762U)
#ifndef INTC_INTSRC_NUM_762        
#define INTC_INTSRC_NUM_762                                     (762U)
#endif /* INTC_INTSRC_NUM_762 */
/* External interrupt source(SPI): INTID 763 - GTM_TIM1_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM1_INT7                                   (763U)
#ifndef INTC_INTSRC_NUM_763        
#define INTC_INTSRC_NUM_763                                     (763U)
#endif /* INTC_INTSRC_NUM_763 */
/* External interrupt source(SPI): INTID 772 - GTM_TOM0_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM0_INT0                                   (772U)
#ifndef INTC_INTSRC_NUM_772        
#define INTC_INTSRC_NUM_772                                     (772U)
#endif /* INTC_INTSRC_NUM_772 */
/* External interrupt source(SPI): INTID 773 - GTM_TOM0_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM0_INT1                                   (773U)
#ifndef INTC_INTSRC_NUM_773        
#define INTC_INTSRC_NUM_773                                     (773U)
#endif /* INTC_INTSRC_NUM_773 */
/* External interrupt source(SPI): INTID 774 - GTM_TOM0_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM0_INT2                                   (774U)
#ifndef INTC_INTSRC_NUM_774        
#define INTC_INTSRC_NUM_774                                     (774U)
#endif /* INTC_INTSRC_NUM_774 */
/* External interrupt source(SPI): INTID 775 - GTM_TOM0_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM0_INT3                                   (775U)
#ifndef INTC_INTSRC_NUM_775        
#define INTC_INTSRC_NUM_775                                     (775U)
#endif /* INTC_INTSRC_NUM_775 */
/* External interrupt source(SPI): INTID 776 - GTM_TOM0_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM0_INT4                                   (776U)
#ifndef INTC_INTSRC_NUM_776        
#define INTC_INTSRC_NUM_776                                     (776U)
#endif /* INTC_INTSRC_NUM_776 */
/* External interrupt source(SPI): INTID 777 - GTM_TOM0_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM0_INT5                                   (777U)
#ifndef INTC_INTSRC_NUM_777        
#define INTC_INTSRC_NUM_777                                     (777U)
#endif /* INTC_INTSRC_NUM_777 */
/* External interrupt source(SPI): INTID 778 - GTM_TOM0_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM0_INT6                                   (778U)
#ifndef INTC_INTSRC_NUM_778        
#define INTC_INTSRC_NUM_778                                     (778U)
#endif /* INTC_INTSRC_NUM_778 */
/* External interrupt source(SPI): INTID 779 - GTM_TOM0_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM0_INT7                                   (779U)
#ifndef INTC_INTSRC_NUM_779        
#define INTC_INTSRC_NUM_779                                     (779U)
#endif /* INTC_INTSRC_NUM_779 */
/* External interrupt source(SPI): INTID 780 - GTM_TOM1_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM1_INT0                                   (780U)
#ifndef INTC_INTSRC_NUM_780        
#define INTC_INTSRC_NUM_780                                     (780U)
#endif /* INTC_INTSRC_NUM_780 */
/* External interrupt source(SPI): INTID 781 - GTM_TOM1_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM1_INT1                                   (781U)
#ifndef INTC_INTSRC_NUM_781        
#define INTC_INTSRC_NUM_781                                     (781U)
#endif /* INTC_INTSRC_NUM_781 */
/* External interrupt source(SPI): INTID 782 - GTM_TOM1_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM1_INT2                                   (782U)
#ifndef INTC_INTSRC_NUM_782        
#define INTC_INTSRC_NUM_782                                     (782U)
#endif /* INTC_INTSRC_NUM_782 */
/* External interrupt source(SPI): INTID 783 - GTM_TOM1_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM1_INT3                                   (783U)
#ifndef INTC_INTSRC_NUM_783        
#define INTC_INTSRC_NUM_783                                     (783U)
#endif /* INTC_INTSRC_NUM_783 */
/* External interrupt source(SPI): INTID 784 - GTM_TOM1_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM1_INT4                                   (784U)
#ifndef INTC_INTSRC_NUM_784        
#define INTC_INTSRC_NUM_784                                     (784U)
#endif /* INTC_INTSRC_NUM_784 */
/* External interrupt source(SPI): INTID 785 - GTM_TOM1_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM1_INT5                                   (785U)
#ifndef INTC_INTSRC_NUM_785        
#define INTC_INTSRC_NUM_785                                     (785U)
#endif /* INTC_INTSRC_NUM_785 */
/* External interrupt source(SPI): INTID 786 - GTM_TOM1_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM1_INT6                                   (786U)
#ifndef INTC_INTSRC_NUM_786        
#define INTC_INTSRC_NUM_786                                     (786U)
#endif /* INTC_INTSRC_NUM_786 */
/* External interrupt source(SPI): INTID 787 - GTM_TOM1_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM1_INT7                                   (787U)
#ifndef INTC_INTSRC_NUM_787        
#define INTC_INTSRC_NUM_787                                     (787U)
#endif /* INTC_INTSRC_NUM_787 */
/* External interrupt source(SPI): INTID 796 - GTM_ATOM0_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM0_INT0                                   (796U)
#ifndef INTC_INTSRC_NUM_796        
#define INTC_INTSRC_NUM_796                                     (796U)
#endif /* INTC_INTSRC_NUM_796 */
/* External interrupt source(SPI): INTID 797 - GTM_ATOM0_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM0_INT1                                   (797U)
#ifndef INTC_INTSRC_NUM_797        
#define INTC_INTSRC_NUM_797                                     (797U)
#endif /* INTC_INTSRC_NUM_797 */
/* External interrupt source(SPI): INTID 798 - GTM_ATOM0_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM0_INT2                                   (798U)
#ifndef INTC_INTSRC_NUM_798        
#define INTC_INTSRC_NUM_798                                     (798U)
#endif /* INTC_INTSRC_NUM_798 */
/* External interrupt source(SPI): INTID 799 - GTM_ATOM0_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM0_INT3                                   (799U)
#ifndef INTC_INTSRC_NUM_799        
#define INTC_INTSRC_NUM_799                                     (799U)
#endif /* INTC_INTSRC_NUM_799 */
/* External interrupt source(SPI): INTID 812 - GTM_TIO1_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO1_INT0                                   (812U)
#ifndef INTC_INTSRC_NUM_812        
#define INTC_INTSRC_NUM_812                                     (812U)
#endif /* INTC_INTSRC_NUM_812 */
/* External interrupt source(SPI): INTID 813 - GTM_TIO1_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO1_INT1                                   (813U)
#ifndef INTC_INTSRC_NUM_813        
#define INTC_INTSRC_NUM_813                                     (813U)
#endif /* INTC_INTSRC_NUM_813 */
/* External interrupt source(SPI): INTID 814 - GTM_TIO1_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO1_INT2                                   (814U)
#ifndef INTC_INTSRC_NUM_814        
#define INTC_INTSRC_NUM_814                                     (814U)
#endif /* INTC_INTSRC_NUM_814 */
/* External interrupt source(SPI): INTID 815 - GTM_TIO1_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO1_INT3                                   (815U)
#ifndef INTC_INTSRC_NUM_815        
#define INTC_INTSRC_NUM_815                                     (815U)
#endif /* INTC_INTSRC_NUM_815 */
/* External interrupt source(SPI): INTID 816 - GTM_TIO1_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO1_INT4                                   (816U)
#ifndef INTC_INTSRC_NUM_816        
#define INTC_INTSRC_NUM_816                                     (816U)
#endif /* INTC_INTSRC_NUM_816 */
/* External interrupt source(SPI): INTID 817 - GTM_TIO1_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO1_INT5                                   (817U)
#ifndef INTC_INTSRC_NUM_817        
#define INTC_INTSRC_NUM_817                                     (817U)
#endif /* INTC_INTSRC_NUM_817 */
/* External interrupt source(SPI): INTID 818 - GTM_TIO1_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO1_INT6                                   (818U)
#ifndef INTC_INTSRC_NUM_818        
#define INTC_INTSRC_NUM_818                                     (818U)
#endif /* INTC_INTSRC_NUM_818 */
/* External interrupt source(SPI): INTID 819 - GTM_TIO1_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO1_INT7                                   (819U)
#ifndef INTC_INTSRC_NUM_819        
#define INTC_INTSRC_NUM_819                                     (819U)
#endif /* INTC_INTSRC_NUM_819 */
/* External interrupt source(SPI): INTID 836 - GTM_MCS0_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_INT0                                   (836U)
#ifndef INTC_INTSRC_NUM_836        
#define INTC_INTSRC_NUM_836                                     (836U)
#endif /* INTC_INTSRC_NUM_836 */
/* External interrupt source(SPI): INTID 837 - GTM_MCS0_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_INT1                                   (837U)
#ifndef INTC_INTSRC_NUM_837        
#define INTC_INTSRC_NUM_837                                     (837U)
#endif /* INTC_INTSRC_NUM_837 */
/* External interrupt source(SPI): INTID 838 - GTM_MCS0_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_INT2                                   (838U)
#ifndef INTC_INTSRC_NUM_838        
#define INTC_INTSRC_NUM_838                                     (838U)
#endif /* INTC_INTSRC_NUM_838 */
/* External interrupt source(SPI): INTID 839 - GTM_MCS0_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_INT3                                   (839U)
#ifndef INTC_INTSRC_NUM_839        
#define INTC_INTSRC_NUM_839                                     (839U)
#endif /* INTC_INTSRC_NUM_839 */
/* External interrupt source(SPI): INTID 840 - GTM_MCS0_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_INT4                                   (840U)
#ifndef INTC_INTSRC_NUM_840        
#define INTC_INTSRC_NUM_840                                     (840U)
#endif /* INTC_INTSRC_NUM_840 */
/* External interrupt source(SPI): INTID 841 - GTM_MCS0_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_INT5                                   (841U)
#ifndef INTC_INTSRC_NUM_841        
#define INTC_INTSRC_NUM_841                                     (841U)
#endif /* INTC_INTSRC_NUM_841 */
/* External interrupt source(SPI): INTID 842 - GTM_MCS0_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_INT6                                   (842U)
#ifndef INTC_INTSRC_NUM_842        
#define INTC_INTSRC_NUM_842                                     (842U)
#endif /* INTC_INTSRC_NUM_842 */
/* External interrupt source(SPI): INTID 843 - GTM_MCS0_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_INT7                                   (843U)
#ifndef INTC_INTSRC_NUM_843        
#define INTC_INTSRC_NUM_843                                     (843U)
#endif /* INTC_INTSRC_NUM_843 */
/* External interrupt source(SPI): INTID 868 - GTM_MCS0_S_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_S_INT0                                   (868U)
#ifndef INTC_INTSRC_NUM_868        
#define INTC_INTSRC_NUM_868                                     (868U)
#endif /* INTC_INTSRC_NUM_868 */
/* External interrupt source(SPI): INTID 869 - GTM_MCS0_S_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_S_INT1                                   (869U)
#ifndef INTC_INTSRC_NUM_869        
#define INTC_INTSRC_NUM_869                                     (869U)
#endif /* INTC_INTSRC_NUM_869 */
/* External interrupt source(SPI): INTID 870 - GTM_MCS0_S_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_S_INT2                                   (870U)
#ifndef INTC_INTSRC_NUM_870        
#define INTC_INTSRC_NUM_870                                     (870U)
#endif /* INTC_INTSRC_NUM_870 */
/* External interrupt source(SPI): INTID 871 - GTM_MCS0_S_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_S_INT3                                   (871U)
#ifndef INTC_INTSRC_NUM_871        
#define INTC_INTSRC_NUM_871                                     (871U)
#endif /* INTC_INTSRC_NUM_871 */
/* External interrupt source(SPI): INTID 872 - GTM_MCS0_S_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_S_INT4                                   (872U)
#ifndef INTC_INTSRC_NUM_872        
#define INTC_INTSRC_NUM_872                                     (872U)
#endif /* INTC_INTSRC_NUM_872 */
/* External interrupt source(SPI): INTID 873 - GTM_MCS0_S_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_S_INT5                                   (873U)
#ifndef INTC_INTSRC_NUM_873        
#define INTC_INTSRC_NUM_873                                     (873U)
#endif /* INTC_INTSRC_NUM_873 */
/* External interrupt source(SPI): INTID 874 - GTM_MCS0_S_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_S_INT6                                   (874U)
#ifndef INTC_INTSRC_NUM_874        
#define INTC_INTSRC_NUM_874                                     (874U)
#endif /* INTC_INTSRC_NUM_874 */
/* External interrupt source(SPI): INTID 875 - GTM_MCS0_S_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS0_S_INT7                                   (875U)
#ifndef INTC_INTSRC_NUM_875        
#define INTC_INTSRC_NUM_875                                     (875U)
#endif /* INTC_INTSRC_NUM_875 */
/* External interrupt source(SPI): INTID 900 - GTM_WRAPPER_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_WRAPPER_INT0                                   (900U)
#ifndef INTC_INTSRC_NUM_900        
#define INTC_INTSRC_NUM_900                                     (900U)
#endif /* INTC_INTSRC_NUM_900 */

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

#endif /* INTC_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

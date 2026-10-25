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
#define INTC_CFG_INTSRC_NUM_CORE0                              (69U)
/* Total number of configured internal interrupt sources(SGI and PPI) in Core1 */
#define INTC_CFG_INTSRC_NUM_CORE1                              (22U)
/* Total number of configured internal interrupt sources(SGI and PPI) in Core2 */
#define INTC_CFG_INTSRC_NUM_CORE2                              (3U)
/* Total number of configured internal interrupt sources(SGI and PPI) in Core3 */
#define INTC_CFG_INTSRC_NUM_CORE3                              (3U)
/* Total number of configured internal interrupt sources(SGI and PPI) */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_INTSRC_NUM                                    (97U)

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
/* PMC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_PMC_INTSRC_EN                                   (STD_OFF)
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
/* FC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_FC_INTSRC_EN                                   (STD_OFF)
/* SARADC_FC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_SARADC_FC_INTSRC_EN                                   (STD_OFF)
/* DSADC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_DSADC_INTSRC_EN                                   (STD_ON)
/* TSENSOR interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_TSENSOR_INTSRC_EN                                   (STD_OFF)
/* PSI5 interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_PSI5_INTSRC_EN                                   (STD_OFF)
/* ECRC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_ECRC_INTSRC_EN                                   (STD_OFF)
/* ESPI interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_ESPI_INTSRC_EN                                   (STD_ON)
/* MSC interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_MSC_INTSRC_EN                                   (STD_ON)
/* SENT interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_SENT_INTSRC_EN                                   (STD_ON)
/* I2C interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_I2C_INTSRC_EN                                   (STD_OFF)
/* QSPI interrupt enabled */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_CFG_QSPI_INTSRC_EN                                   (STD_OFF)
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
/* Represent core2 for generate the SGI interrupt */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_GENSGI_CORE2                                      (0x04U)
/* Represent core3 for generate the SGI interrupt */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_GENSGI_CORE3                                      (0x08U)

/* All cores mask for generate software interrupt(SGI) */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_GENSGI_CORE_MASK                                  (0x0fU)

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

/* Interrupt source 0 enabled: CPU1_SGI0 */
#define INTC_CFG_INTSRC0_CORE1_EN                              (STD_ON)
/* Interrupt source 0 category: CPU1_SGI0 */
#define INTC_CFG_INTSRC0_CORE1_CAT                             (INTC_SRC_TYPE_CAT1)
/* Interrupt source 0 notification: CPU1_SGI0 */
#define INTC_CFG_INTSRC0_CORE1_NOTIF_EN                        (STD_ON) 
/* Notification function for interrupt source 0: CPU1_SGI0 */
extern void Demo_Core1Sgi0Notification(void);
#define Intc_Irq_NotifCore1IntSrc0()                           Demo_Core1Sgi0Notification()

/* Interrupt source 0 enabled: CPU2_SGI0 */
#define INTC_CFG_INTSRC0_CORE2_EN                              (STD_ON)
/* Interrupt source 0 category: CPU2_SGI0 */
#define INTC_CFG_INTSRC0_CORE2_CAT                             (INTC_SRC_TYPE_CAT1)
/* Interrupt source 0 notification: CPU2_SGI0 */
#define INTC_CFG_INTSRC0_CORE2_NOTIF_EN                        (STD_ON) 
/* Notification function for interrupt source 0: CPU2_SGI0 */
extern void Demo_Core2Sgi0Notification(void);
#define Intc_Irq_NotifCore2IntSrc0()                           Demo_Core2Sgi0Notification()

/* Interrupt source 0 enabled: CPU3_SGI0 */
#define INTC_CFG_INTSRC0_CORE3_EN                              (STD_ON)
/* Interrupt source 0 category: CPU3_SGI0 */
#define INTC_CFG_INTSRC0_CORE3_CAT                             (INTC_SRC_TYPE_CAT1)
/* Interrupt source 0 notification: CPU3_SGI0 */
#define INTC_CFG_INTSRC0_CORE3_NOTIF_EN                        (STD_ON) 
/* Notification function for interrupt source 0: CPU3_SGI0 */
extern void Demo_Core3Sgi0Notification(void);
#define Intc_Irq_NotifCore3IntSrc0()                           Demo_Core3Sgi0Notification()

/* Interrupt source 32 enabled: CPU0WDT_INT */
#define INTC_CFG_INTSRC32_EN                                   (STD_ON)
/* Interrupt source 32 category: CPU0WDT_INT */
#define INTC_CFG_INTSRC32_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 32 notification: CPU0WDT_INT */
#define INTC_CFG_INTSRC32_NOTIF_EN                             (STD_OFF)

/* Interrupt source 34 enabled: CPU1WDT_INT */
#define INTC_CFG_INTSRC34_EN                                   (STD_ON)
/* Interrupt source 34 category: CPU1WDT_INT */
#define INTC_CFG_INTSRC34_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 34 notification: CPU1WDT_INT */
#define INTC_CFG_INTSRC34_NOTIF_EN                             (STD_OFF)

/* Interrupt source 38 enabled: CPU2WDT_INT */
#define INTC_CFG_INTSRC38_EN                                   (STD_ON)
/* Interrupt source 38 category: CPU2WDT_INT */
#define INTC_CFG_INTSRC38_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 38 notification: CPU2WDT_INT */
#define INTC_CFG_INTSRC38_NOTIF_EN                             (STD_OFF)

/* Interrupt source 39 enabled: CPU3WDT_INT */
#define INTC_CFG_INTSRC39_EN                                   (STD_ON)
/* Interrupt source 39 category: CPU3WDT_INT */
#define INTC_CFG_INTSRC39_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 39 notification: CPU3WDT_INT */
#define INTC_CFG_INTSRC39_NOTIF_EN                             (STD_OFF)

/* Interrupt source 56 enabled: INTC_CPU0SOFTINT0 */
#define INTC_CFG_INTSRC56_CORE0_EN                              (STD_ON)
/* Interrupt source 56 category: INTC_CPU0SOFTINT0 */
#define INTC_CFG_INTSRC56_CORE0_CAT                             (INTC_SRC_TYPE_CAT1)
/* Interrupt source 56 notification: INTC_CPU0SOFTINT0 */
#define INTC_CFG_INTSRC56_CORE0_NOTIF_EN                        (STD_ON) 
/* Notification function for interrupt source 56: INTC_CPU0SOFTINT0 */
extern void Demo_Core0Spi56Notification(void);
#define Intc_Irq_NotifCore0IntSrc56()                           Demo_Core0Spi56Notification()

/* Interrupt source 89 enabled: INTC_CPU1SOFTINT0 */
#define INTC_CFG_INTSRC89_CORE1_EN                              (STD_ON)
/* Interrupt source 89 category: INTC_CPU1SOFTINT0 */
#define INTC_CFG_INTSRC89_CORE1_CAT                             (INTC_SRC_TYPE_CAT1)
/* Interrupt source 89 notification: INTC_CPU1SOFTINT0 */
#define INTC_CFG_INTSRC89_CORE1_NOTIF_EN                        (STD_ON) 
/* Notification function for interrupt source 89: INTC_CPU1SOFTINT0 */
extern void Demo_Core1Spi89Notification(void);
#define Intc_Irq_NotifCore1IntSrc89()                           Demo_Core1Spi89Notification()

/* Interrupt source 56 enabled: INTC_CPU2SOFTINT0 */
#define INTC_CFG_INTSRC56_CORE2_EN                              (STD_ON)
/* Interrupt source 56 category: INTC_CPU2SOFTINT0 */
#define INTC_CFG_INTSRC56_CORE2_CAT                             (INTC_SRC_TYPE_CAT1)
/* Interrupt source 56 notification: INTC_CPU2SOFTINT0 */
#define INTC_CFG_INTSRC56_CORE2_NOTIF_EN                        (STD_ON) 
/* Notification function for interrupt source 56: INTC_CPU2SOFTINT0 */
extern void Demo_Core2Spi56Notification(void);
#define Intc_Irq_NotifCore2IntSrc56()                           Demo_Core2Spi56Notification()

/* Interrupt source 89 enabled: INTC_CPU3SOFTINT0 */
#define INTC_CFG_INTSRC89_CORE3_EN                              (STD_ON)
/* Interrupt source 89 category: INTC_CPU3SOFTINT0 */
#define INTC_CFG_INTSRC89_CORE3_CAT                             (INTC_SRC_TYPE_CAT1)
/* Interrupt source 89 notification: INTC_CPU3SOFTINT0 */
#define INTC_CFG_INTSRC89_CORE3_NOTIF_EN                        (STD_ON) 
/* Notification function for interrupt source 89: INTC_CPU3SOFTINT0 */
extern void Demo_Core3Spi89Notification(void);
#define Intc_Irq_NotifCore3IntSrc89()                           Demo_Core3Spi89Notification()

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

/* Interrupt source 99 enabled: DMA0_CH_INT4 */
#define INTC_CFG_INTSRC99_EN                                   (STD_ON)
/* Interrupt source 99 category: DMA0_CH_INT4 */
#define INTC_CFG_INTSRC99_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 99 notification: DMA0_CH_INT4 */
#define INTC_CFG_INTSRC99_NOTIF_EN                             (STD_OFF)

/* Interrupt source 149 enabled: DMA1_CH_INT0 */
#define INTC_CFG_INTSRC149_EN                                   (STD_ON)
/* Interrupt source 149 category: DMA1_CH_INT0 */
#define INTC_CFG_INTSRC149_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 149 notification: DMA1_CH_INT0 */
#define INTC_CFG_INTSRC149_NOTIF_EN                             (STD_OFF)

/* Interrupt source 115 enabled: DMA2_CH_INT0 */
#define INTC_CFG_INTSRC115_EN                                   (STD_ON)
/* Interrupt source 115 category: DMA2_CH_INT0 */
#define INTC_CFG_INTSRC115_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 115 notification: DMA2_CH_INT0 */
#define INTC_CFG_INTSRC115_NOTIF_EN                             (STD_OFF)

/* Interrupt source 118 enabled: DMA2_CH_INT3 */
#define INTC_CFG_INTSRC118_EN                                   (STD_ON)
/* Interrupt source 118 category: DMA2_CH_INT3 */
#define INTC_CFG_INTSRC118_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 118 notification: DMA2_CH_INT3 */
#define INTC_CFG_INTSRC118_NOTIF_EN                             (STD_OFF)

/* Interrupt source 129 enabled: DMA3_CH_INT0 */
#define INTC_CFG_INTSRC129_EN                                   (STD_ON)
/* Interrupt source 129 category: DMA3_CH_INT0 */
#define INTC_CFG_INTSRC129_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 129 notification: DMA3_CH_INT0 */
#define INTC_CFG_INTSRC129_NOTIF_EN                             (STD_OFF)

/* Interrupt source 130 enabled: DMA3_CH_INT1 */
#define INTC_CFG_INTSRC130_EN                                   (STD_ON)
/* Interrupt source 130 category: DMA3_CH_INT1 */
#define INTC_CFG_INTSRC130_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 130 notification: DMA3_CH_INT1 */
#define INTC_CFG_INTSRC130_NOTIF_EN                             (STD_OFF)

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

/* Interrupt source 247 enabled: BASETIM1_INT */
#define INTC_CFG_INTSRC247_EN                                   (STD_ON)
/* Interrupt source 247 category: BASETIM1_INT */
#define INTC_CFG_INTSRC247_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 247 notification: BASETIM1_INT */
#define INTC_CFG_INTSRC247_NOTIF_EN                             (STD_OFF)

/* Interrupt source 248 enabled: BASETIM2_INT */
#define INTC_CFG_INTSRC248_EN                                   (STD_ON)
/* Interrupt source 248 category: BASETIM2_INT */
#define INTC_CFG_INTSRC248_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 248 notification: BASETIM2_INT */
#define INTC_CFG_INTSRC248_NOTIF_EN                             (STD_OFF)

/* Interrupt source 249 enabled: BASETIM3_INT */
#define INTC_CFG_INTSRC249_EN                                   (STD_ON)
/* Interrupt source 249 category: BASETIM3_INT */
#define INTC_CFG_INTSRC249_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 249 notification: BASETIM3_INT */
#define INTC_CFG_INTSRC249_NOTIF_EN                             (STD_OFF)

/* Interrupt source 250 enabled: BASETIM4_INT */
#define INTC_CFG_INTSRC250_EN                                   (STD_ON)
/* Interrupt source 250 category: BASETIM4_INT */
#define INTC_CFG_INTSRC250_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 250 notification: BASETIM4_INT */
#define INTC_CFG_INTSRC250_NOTIF_EN                             (STD_OFF)

/* Interrupt source 251 enabled: BASETIM5_INT */
#define INTC_CFG_INTSRC251_EN                                   (STD_ON)
/* Interrupt source 251 category: BASETIM5_INT */
#define INTC_CFG_INTSRC251_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 251 notification: BASETIM5_INT */
#define INTC_CFG_INTSRC251_NOTIF_EN                             (STD_OFF)

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

/* Interrupt source 401 enabled: SARADC8_G3SR0 */
#define INTC_CFG_INTSRC401_EN                                   (STD_ON)
/* Interrupt source 401 category: SARADC8_G3SR0 */
#define INTC_CFG_INTSRC401_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 401 notification: SARADC8_G3SR0 */
#define INTC_CFG_INTSRC401_NOTIF_EN                             (STD_OFF)

/* Interrupt source 402 enabled: SARADC8_G3SR1 */
#define INTC_CFG_INTSRC402_EN                                   (STD_ON)
/* Interrupt source 402 category: SARADC8_G3SR1 */
#define INTC_CFG_INTSRC402_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 402 notification: SARADC8_G3SR1 */
#define INTC_CFG_INTSRC402_NOTIF_EN                             (STD_OFF)

/* Interrupt source 403 enabled: SARADC8_G3SR2 */
#define INTC_CFG_INTSRC403_EN                                   (STD_ON)
/* Interrupt source 403 category: SARADC8_G3SR2 */
#define INTC_CFG_INTSRC403_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 403 notification: SARADC8_G3SR2 */
#define INTC_CFG_INTSRC403_NOTIF_EN                             (STD_OFF)

/* Interrupt source 407 enabled: SARADC9_G3SR0 */
#define INTC_CFG_INTSRC407_EN                                   (STD_ON)
/* Interrupt source 407 category: SARADC9_G3SR0 */
#define INTC_CFG_INTSRC407_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 407 notification: SARADC9_G3SR0 */
#define INTC_CFG_INTSRC407_NOTIF_EN                             (STD_OFF)

/* Interrupt source 408 enabled: SARADC9_G3SR1 */
#define INTC_CFG_INTSRC408_EN                                   (STD_ON)
/* Interrupt source 408 category: SARADC9_G3SR1 */
#define INTC_CFG_INTSRC408_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 408 notification: SARADC9_G3SR1 */
#define INTC_CFG_INTSRC408_NOTIF_EN                             (STD_OFF)

/* Interrupt source 409 enabled: SARADC9_G3SR2 */
#define INTC_CFG_INTSRC409_EN                                   (STD_ON)
/* Interrupt source 409 category: SARADC9_G3SR2 */
#define INTC_CFG_INTSRC409_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 409 notification: SARADC9_G3SR2 */
#define INTC_CFG_INTSRC409_NOTIF_EN                             (STD_OFF)

/* Interrupt source 439 enabled: DSADC0_SRA */
#define INTC_CFG_INTSRC439_EN                                   (STD_ON)
/* Interrupt source 439 category: DSADC0_SRA */
#define INTC_CFG_INTSRC439_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 439 notification: DSADC0_SRA */
#define INTC_CFG_INTSRC439_NOTIF_EN                             (STD_OFF)

/* Interrupt source 440 enabled: DSADC0_SRM */
#define INTC_CFG_INTSRC440_EN                                   (STD_ON)
/* Interrupt source 440 category: DSADC0_SRM */
#define INTC_CFG_INTSRC440_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 440 notification: DSADC0_SRM */
#define INTC_CFG_INTSRC440_NOTIF_EN                             (STD_OFF)

/* Interrupt source 441 enabled: DSADC1_SRA */
#define INTC_CFG_INTSRC441_EN                                   (STD_ON)
/* Interrupt source 441 category: DSADC1_SRA */
#define INTC_CFG_INTSRC441_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 441 notification: DSADC1_SRA */
#define INTC_CFG_INTSRC441_NOTIF_EN                             (STD_OFF)

/* Interrupt source 442 enabled: DSADC1_SRM */
#define INTC_CFG_INTSRC442_EN                                   (STD_ON)
/* Interrupt source 442 category: DSADC1_SRM */
#define INTC_CFG_INTSRC442_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 442 notification: DSADC1_SRM */
#define INTC_CFG_INTSRC442_NOTIF_EN                             (STD_OFF)

/* Interrupt source 443 enabled: DSADC2_SRA */
#define INTC_CFG_INTSRC443_EN                                   (STD_ON)
/* Interrupt source 443 category: DSADC2_SRA */
#define INTC_CFG_INTSRC443_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 443 notification: DSADC2_SRA */
#define INTC_CFG_INTSRC443_NOTIF_EN                             (STD_OFF)

/* Interrupt source 444 enabled: DSADC2_SRM */
#define INTC_CFG_INTSRC444_EN                                   (STD_ON)
/* Interrupt source 444 category: DSADC2_SRM */
#define INTC_CFG_INTSRC444_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 444 notification: DSADC2_SRM */
#define INTC_CFG_INTSRC444_NOTIF_EN                             (STD_OFF)

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

/* Interrupt source 483 enabled: ESPI2_RX_INT */
#define INTC_CFG_INTSRC483_EN                                   (STD_ON)
/* Interrupt source 483 category: ESPI2_RX_INT */
#define INTC_CFG_INTSRC483_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 483 notification: ESPI2_RX_INT */
#define INTC_CFG_INTSRC483_NOTIF_EN                             (STD_OFF)

/* Interrupt source 484 enabled: ESPI2_ERR_INT */
#define INTC_CFG_INTSRC484_EN                                   (STD_ON)
/* Interrupt source 484 category: ESPI2_ERR_INT */
#define INTC_CFG_INTSRC484_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 484 notification: ESPI2_ERR_INT */
#define INTC_CFG_INTSRC484_NOTIF_EN                             (STD_OFF)

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

/* Interrupt source 538 enabled: ESPI8_ERR_INT */
#define INTC_CFG_INTSRC538_EN                                   (STD_ON)
/* Interrupt source 538 category: ESPI8_ERR_INT */
#define INTC_CFG_INTSRC538_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 538 notification: ESPI8_ERR_INT */
#define INTC_CFG_INTSRC538_NOTIF_EN                             (STD_OFF)

/* Interrupt source 552 enabled: MSC0_SR0 */
#define INTC_CFG_INTSRC552_EN                                   (STD_ON)
/* Interrupt source 552 category: MSC0_SR0 */
#define INTC_CFG_INTSRC552_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 552 notification: MSC0_SR0 */
#define INTC_CFG_INTSRC552_NOTIF_EN                             (STD_OFF)

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

/* Interrupt source 596 enabled: SENT6_RX_ERROR */
#define INTC_CFG_INTSRC596_EN                                   (STD_ON)
/* Interrupt source 596 category: SENT6_RX_ERROR */
#define INTC_CFG_INTSRC596_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 596 notification: SENT6_RX_ERROR */
#define INTC_CFG_INTSRC596_NOTIF_EN                             (STD_OFF)

/* Interrupt source 597 enabled: SENT6_RX_VALID */
#define INTC_CFG_INTSRC597_EN                                   (STD_ON)
/* Interrupt source 597 category: SENT6_RX_VALID */
#define INTC_CFG_INTSRC597_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 597 notification: SENT6_RX_VALID */
#define INTC_CFG_INTSRC597_NOTIF_EN                             (STD_OFF)

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

/* Interrupt source 646 enabled: ASI3_RX */
#define INTC_CFG_INTSRC646_EN                                   (STD_ON)
/* Interrupt source 646 category: ASI3_RX */
#define INTC_CFG_INTSRC646_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 646 notification: ASI3_RX */
#define INTC_CFG_INTSRC646_NOTIF_EN                             (STD_OFF)

/* Interrupt source 648 enabled: ASI3_ERROR */
#define INTC_CFG_INTSRC648_EN                                   (STD_ON)
/* Interrupt source 648 category: ASI3_ERROR */
#define INTC_CFG_INTSRC648_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 648 notification: ASI3_ERROR */
#define INTC_CFG_INTSRC648_NOTIF_EN                             (STD_OFF)

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

/* Interrupt source 749 enabled: GTM_TIM0_INT1 */
#define INTC_CFG_INTSRC749_EN                                   (STD_ON)
/* Interrupt source 749 category: GTM_TIM0_INT1 */
#define INTC_CFG_INTSRC749_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 749 notification: GTM_TIM0_INT1 */
#define INTC_CFG_INTSRC749_NOTIF_EN                             (STD_OFF)

/* Interrupt source 750 enabled: GTM_TIM0_INT2 */
#define INTC_CFG_INTSRC750_EN                                   (STD_ON)
/* Interrupt source 750 category: GTM_TIM0_INT2 */
#define INTC_CFG_INTSRC750_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 750 notification: GTM_TIM0_INT2 */
#define INTC_CFG_INTSRC750_NOTIF_EN                             (STD_OFF)

/* Interrupt source 751 enabled: GTM_TIM0_INT3 */
#define INTC_CFG_INTSRC751_EN                                   (STD_ON)
/* Interrupt source 751 category: GTM_TIM0_INT3 */
#define INTC_CFG_INTSRC751_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 751 notification: GTM_TIM0_INT3 */
#define INTC_CFG_INTSRC751_NOTIF_EN                             (STD_OFF)

/* Interrupt source 752 enabled: GTM_TIM0_INT4 */
#define INTC_CFG_INTSRC752_EN                                   (STD_ON)
/* Interrupt source 752 category: GTM_TIM0_INT4 */
#define INTC_CFG_INTSRC752_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 752 notification: GTM_TIM0_INT4 */
#define INTC_CFG_INTSRC752_NOTIF_EN                             (STD_OFF)

/* Interrupt source 753 enabled: GTM_TIM0_INT5 */
#define INTC_CFG_INTSRC753_EN                                   (STD_ON)
/* Interrupt source 753 category: GTM_TIM0_INT5 */
#define INTC_CFG_INTSRC753_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 753 notification: GTM_TIM0_INT5 */
#define INTC_CFG_INTSRC753_NOTIF_EN                             (STD_OFF)

/* Interrupt source 764 enabled: GTM_TIM2_INT0 */
#define INTC_CFG_INTSRC764_EN                                   (STD_ON)
/* Interrupt source 764 category: GTM_TIM2_INT0 */
#define INTC_CFG_INTSRC764_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 764 notification: GTM_TIM2_INT0 */
#define INTC_CFG_INTSRC764_NOTIF_EN                             (STD_OFF)

/* Interrupt source 765 enabled: GTM_TIM2_INT1 */
#define INTC_CFG_INTSRC765_EN                                   (STD_ON)
/* Interrupt source 765 category: GTM_TIM2_INT1 */
#define INTC_CFG_INTSRC765_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 765 notification: GTM_TIM2_INT1 */
#define INTC_CFG_INTSRC765_NOTIF_EN                             (STD_OFF)

/* Interrupt source 772 enabled: GTM_TOM0_INT0 */
#define INTC_CFG_INTSRC772_EN                                   (STD_ON)
/* Interrupt source 772 category: GTM_TOM0_INT0 */
#define INTC_CFG_INTSRC772_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 772 notification: GTM_TOM0_INT0 */
#define INTC_CFG_INTSRC772_NOTIF_EN                             (STD_OFF)

/* Interrupt source 773 enabled: GTM_TOM0_INT1 */
#define INTC_CFG_INTSRC773_EN                                   (STD_ON)
/* Interrupt source 773 category: GTM_TOM0_INT1 */
#define INTC_CFG_INTSRC773_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 773 notification: GTM_TOM0_INT1 */
#define INTC_CFG_INTSRC773_NOTIF_EN                             (STD_OFF)

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

/* Interrupt source 798 enabled: GTM_ATOM0_INT2 */
#define INTC_CFG_INTSRC798_EN                                   (STD_ON)
/* Interrupt source 798 category: GTM_ATOM0_INT2 */
#define INTC_CFG_INTSRC798_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 798 notification: GTM_ATOM0_INT2 */
#define INTC_CFG_INTSRC798_NOTIF_EN                             (STD_OFF)

/* Interrupt source 800 enabled: GTM_ATOM1_INT0 */
#define INTC_CFG_INTSRC800_EN                                   (STD_ON)
/* Interrupt source 800 category: GTM_ATOM1_INT0 */
#define INTC_CFG_INTSRC800_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 800 notification: GTM_ATOM1_INT0 */
#define INTC_CFG_INTSRC800_NOTIF_EN                             (STD_OFF)

/* Interrupt source 801 enabled: GTM_ATOM1_INT1 */
#define INTC_CFG_INTSRC801_EN                                   (STD_ON)
/* Interrupt source 801 category: GTM_ATOM1_INT1 */
#define INTC_CFG_INTSRC801_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 801 notification: GTM_ATOM1_INT1 */
#define INTC_CFG_INTSRC801_NOTIF_EN                             (STD_OFF)

/* Interrupt source 802 enabled: GTM_ATOM1_INT2 */
#define INTC_CFG_INTSRC802_EN                                   (STD_ON)
/* Interrupt source 802 category: GTM_ATOM1_INT2 */
#define INTC_CFG_INTSRC802_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 802 notification: GTM_ATOM1_INT2 */
#define INTC_CFG_INTSRC802_NOTIF_EN                             (STD_OFF)

/* Interrupt source 819 enabled: GTM_TIO1_INT7 */
#define INTC_CFG_INTSRC819_EN                                   (STD_ON)
/* Interrupt source 819 category: GTM_TIO1_INT7 */
#define INTC_CFG_INTSRC819_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 819 notification: GTM_TIO1_INT7 */
#define INTC_CFG_INTSRC819_NOTIF_EN                             (STD_OFF)

/* Interrupt source 820 enabled: GTM_TIO2_INT0 */
#define INTC_CFG_INTSRC820_EN                                   (STD_ON)
/* Interrupt source 820 category: GTM_TIO2_INT0 */
#define INTC_CFG_INTSRC820_CAT                                  (INTC_SRC_TYPE_CAT1)
/* Interrupt source 820 notification: GTM_TIO2_INT0 */
#define INTC_CFG_INTSRC820_NOTIF_EN                             (STD_OFF)


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
/* Internal interrupt source(SGI or PPI): INTID 0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI0                                   (0U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI0_CORE1                               (0U)
#ifndef INTC_INTSRC_NUM_0
#define INTC_INTSRC_NUM_0                                     (0U)
#endif /* INTC_INTSRC_NUM_0 */
/* Internal interrupt source(SGI or PPI): INTID 1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI1                                   (1U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI1_CORE1                               (1U)
#ifndef INTC_INTSRC_NUM_1
#define INTC_INTSRC_NUM_1                                     (1U)
#endif /* INTC_INTSRC_NUM_1 */
/* Internal interrupt source(SGI or PPI): INTID 2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI2                                   (2U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI2_CORE1                               (2U)
#ifndef INTC_INTSRC_NUM_2
#define INTC_INTSRC_NUM_2                                     (2U)
#endif /* INTC_INTSRC_NUM_2 */
/* Internal interrupt source(SGI or PPI): INTID 3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI3                                   (3U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI3_CORE1                               (3U)
#ifndef INTC_INTSRC_NUM_3
#define INTC_INTSRC_NUM_3                                     (3U)
#endif /* INTC_INTSRC_NUM_3 */
/* Internal interrupt source(SGI or PPI): INTID 4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI4                                   (4U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI4_CORE1                               (4U)
#ifndef INTC_INTSRC_NUM_4
#define INTC_INTSRC_NUM_4                                     (4U)
#endif /* INTC_INTSRC_NUM_4 */
/* Internal interrupt source(SGI or PPI): INTID 5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI5                                   (5U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI5_CORE1                               (5U)
#ifndef INTC_INTSRC_NUM_5
#define INTC_INTSRC_NUM_5                                     (5U)
#endif /* INTC_INTSRC_NUM_5 */
/* Internal interrupt source(SGI or PPI): INTID 6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI6                                   (6U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI6_CORE1                               (6U)
#ifndef INTC_INTSRC_NUM_6
#define INTC_INTSRC_NUM_6                                     (6U)
#endif /* INTC_INTSRC_NUM_6 */
/* Internal interrupt source(SGI or PPI): INTID 7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI7                                   (7U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI7_CORE1                               (7U)
#ifndef INTC_INTSRC_NUM_7
#define INTC_INTSRC_NUM_7                                     (7U)
#endif /* INTC_INTSRC_NUM_7 */
/* Internal interrupt source(SGI or PPI): INTID 8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI8                                   (8U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI8_CORE1                               (8U)
#ifndef INTC_INTSRC_NUM_8
#define INTC_INTSRC_NUM_8                                     (8U)
#endif /* INTC_INTSRC_NUM_8 */
/* Internal interrupt source(SGI or PPI): INTID 9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI9                                   (9U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI9_CORE1                               (9U)
#ifndef INTC_INTSRC_NUM_9
#define INTC_INTSRC_NUM_9                                     (9U)
#endif /* INTC_INTSRC_NUM_9 */
/* Internal interrupt source(SGI or PPI): INTID 10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI10                                   (10U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI10_CORE1                               (10U)
#ifndef INTC_INTSRC_NUM_10
#define INTC_INTSRC_NUM_10                                     (10U)
#endif /* INTC_INTSRC_NUM_10 */
/* Internal interrupt source(SGI or PPI): INTID 11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI11                                   (11U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI11_CORE1                               (11U)
#ifndef INTC_INTSRC_NUM_11
#define INTC_INTSRC_NUM_11                                     (11U)
#endif /* INTC_INTSRC_NUM_11 */
/* Internal interrupt source(SGI or PPI): INTID 12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI12                                   (12U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI12_CORE1                               (12U)
#ifndef INTC_INTSRC_NUM_12
#define INTC_INTSRC_NUM_12                                     (12U)
#endif /* INTC_INTSRC_NUM_12 */
/* Internal interrupt source(SGI or PPI): INTID 13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI13                                   (13U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI13_CORE1                               (13U)
#ifndef INTC_INTSRC_NUM_13
#define INTC_INTSRC_NUM_13                                     (13U)
#endif /* INTC_INTSRC_NUM_13 */
/* Internal interrupt source(SGI or PPI): INTID 14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI14                                   (14U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI14_CORE1                               (14U)
#ifndef INTC_INTSRC_NUM_14
#define INTC_INTSRC_NUM_14                                     (14U)
#endif /* INTC_INTSRC_NUM_14 */
/* Internal interrupt source(SGI or PPI): INTID 15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI15                                   (15U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_SGI15_CORE1                               (15U)
#ifndef INTC_INTSRC_NUM_15
#define INTC_INTSRC_NUM_15                                     (15U)
#endif /* INTC_INTSRC_NUM_15 */
/* Internal interrupt source(SGI or PPI): INTID 0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI0                                   (0U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI0_CORE2                               (0U)
#ifndef INTC_INTSRC_NUM_0
#define INTC_INTSRC_NUM_0                                     (0U)
#endif /* INTC_INTSRC_NUM_0 */
/* Internal interrupt source(SGI or PPI): INTID 1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI1                                   (1U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI1_CORE2                               (1U)
#ifndef INTC_INTSRC_NUM_1
#define INTC_INTSRC_NUM_1                                     (1U)
#endif /* INTC_INTSRC_NUM_1 */
/* Internal interrupt source(SGI or PPI): INTID 2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI2                                   (2U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI2_CORE2                               (2U)
#ifndef INTC_INTSRC_NUM_2
#define INTC_INTSRC_NUM_2                                     (2U)
#endif /* INTC_INTSRC_NUM_2 */
/* Internal interrupt source(SGI or PPI): INTID 3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI3                                   (3U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI3_CORE2                               (3U)
#ifndef INTC_INTSRC_NUM_3
#define INTC_INTSRC_NUM_3                                     (3U)
#endif /* INTC_INTSRC_NUM_3 */
/* Internal interrupt source(SGI or PPI): INTID 4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI4                                   (4U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI4_CORE2                               (4U)
#ifndef INTC_INTSRC_NUM_4
#define INTC_INTSRC_NUM_4                                     (4U)
#endif /* INTC_INTSRC_NUM_4 */
/* Internal interrupt source(SGI or PPI): INTID 5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI5                                   (5U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI5_CORE2                               (5U)
#ifndef INTC_INTSRC_NUM_5
#define INTC_INTSRC_NUM_5                                     (5U)
#endif /* INTC_INTSRC_NUM_5 */
/* Internal interrupt source(SGI or PPI): INTID 6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI6                                   (6U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI6_CORE2                               (6U)
#ifndef INTC_INTSRC_NUM_6
#define INTC_INTSRC_NUM_6                                     (6U)
#endif /* INTC_INTSRC_NUM_6 */
/* Internal interrupt source(SGI or PPI): INTID 7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI7                                   (7U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI7_CORE2                               (7U)
#ifndef INTC_INTSRC_NUM_7
#define INTC_INTSRC_NUM_7                                     (7U)
#endif /* INTC_INTSRC_NUM_7 */
/* Internal interrupt source(SGI or PPI): INTID 8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI8                                   (8U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI8_CORE2                               (8U)
#ifndef INTC_INTSRC_NUM_8
#define INTC_INTSRC_NUM_8                                     (8U)
#endif /* INTC_INTSRC_NUM_8 */
/* Internal interrupt source(SGI or PPI): INTID 9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI9                                   (9U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI9_CORE2                               (9U)
#ifndef INTC_INTSRC_NUM_9
#define INTC_INTSRC_NUM_9                                     (9U)
#endif /* INTC_INTSRC_NUM_9 */
/* Internal interrupt source(SGI or PPI): INTID 10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI10                                   (10U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI10_CORE2                               (10U)
#ifndef INTC_INTSRC_NUM_10
#define INTC_INTSRC_NUM_10                                     (10U)
#endif /* INTC_INTSRC_NUM_10 */
/* Internal interrupt source(SGI or PPI): INTID 11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI11                                   (11U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI11_CORE2                               (11U)
#ifndef INTC_INTSRC_NUM_11
#define INTC_INTSRC_NUM_11                                     (11U)
#endif /* INTC_INTSRC_NUM_11 */
/* Internal interrupt source(SGI or PPI): INTID 12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI12                                   (12U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI12_CORE2                               (12U)
#ifndef INTC_INTSRC_NUM_12
#define INTC_INTSRC_NUM_12                                     (12U)
#endif /* INTC_INTSRC_NUM_12 */
/* Internal interrupt source(SGI or PPI): INTID 13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI13                                   (13U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI13_CORE2                               (13U)
#ifndef INTC_INTSRC_NUM_13
#define INTC_INTSRC_NUM_13                                     (13U)
#endif /* INTC_INTSRC_NUM_13 */
/* Internal interrupt source(SGI or PPI): INTID 14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI14                                   (14U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI14_CORE2                               (14U)
#ifndef INTC_INTSRC_NUM_14
#define INTC_INTSRC_NUM_14                                     (14U)
#endif /* INTC_INTSRC_NUM_14 */
/* Internal interrupt source(SGI or PPI): INTID 15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI15                                   (15U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_SGI15_CORE2                               (15U)
#ifndef INTC_INTSRC_NUM_15
#define INTC_INTSRC_NUM_15                                     (15U)
#endif /* INTC_INTSRC_NUM_15 */
/* Internal interrupt source(SGI or PPI): INTID 0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI0                                   (0U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI0_CORE3                               (0U)
#ifndef INTC_INTSRC_NUM_0
#define INTC_INTSRC_NUM_0                                     (0U)
#endif /* INTC_INTSRC_NUM_0 */
/* Internal interrupt source(SGI or PPI): INTID 1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI1                                   (1U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI1_CORE3                               (1U)
#ifndef INTC_INTSRC_NUM_1
#define INTC_INTSRC_NUM_1                                     (1U)
#endif /* INTC_INTSRC_NUM_1 */
/* Internal interrupt source(SGI or PPI): INTID 2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI2                                   (2U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI2_CORE3                               (2U)
#ifndef INTC_INTSRC_NUM_2
#define INTC_INTSRC_NUM_2                                     (2U)
#endif /* INTC_INTSRC_NUM_2 */
/* Internal interrupt source(SGI or PPI): INTID 3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI3                                   (3U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI3_CORE3                               (3U)
#ifndef INTC_INTSRC_NUM_3
#define INTC_INTSRC_NUM_3                                     (3U)
#endif /* INTC_INTSRC_NUM_3 */
/* Internal interrupt source(SGI or PPI): INTID 4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI4                                   (4U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI4_CORE3                               (4U)
#ifndef INTC_INTSRC_NUM_4
#define INTC_INTSRC_NUM_4                                     (4U)
#endif /* INTC_INTSRC_NUM_4 */
/* Internal interrupt source(SGI or PPI): INTID 5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI5                                   (5U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI5_CORE3                               (5U)
#ifndef INTC_INTSRC_NUM_5
#define INTC_INTSRC_NUM_5                                     (5U)
#endif /* INTC_INTSRC_NUM_5 */
/* Internal interrupt source(SGI or PPI): INTID 6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI6                                   (6U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI6_CORE3                               (6U)
#ifndef INTC_INTSRC_NUM_6
#define INTC_INTSRC_NUM_6                                     (6U)
#endif /* INTC_INTSRC_NUM_6 */
/* Internal interrupt source(SGI or PPI): INTID 7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI7                                   (7U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI7_CORE3                               (7U)
#ifndef INTC_INTSRC_NUM_7
#define INTC_INTSRC_NUM_7                                     (7U)
#endif /* INTC_INTSRC_NUM_7 */
/* Internal interrupt source(SGI or PPI): INTID 8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI8                                   (8U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI8_CORE3                               (8U)
#ifndef INTC_INTSRC_NUM_8
#define INTC_INTSRC_NUM_8                                     (8U)
#endif /* INTC_INTSRC_NUM_8 */
/* Internal interrupt source(SGI or PPI): INTID 9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI9                                   (9U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI9_CORE3                               (9U)
#ifndef INTC_INTSRC_NUM_9
#define INTC_INTSRC_NUM_9                                     (9U)
#endif /* INTC_INTSRC_NUM_9 */
/* Internal interrupt source(SGI or PPI): INTID 10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI10                                   (10U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI10_CORE3                               (10U)
#ifndef INTC_INTSRC_NUM_10
#define INTC_INTSRC_NUM_10                                     (10U)
#endif /* INTC_INTSRC_NUM_10 */
/* Internal interrupt source(SGI or PPI): INTID 11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI11                                   (11U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI11_CORE3                               (11U)
#ifndef INTC_INTSRC_NUM_11
#define INTC_INTSRC_NUM_11                                     (11U)
#endif /* INTC_INTSRC_NUM_11 */
/* Internal interrupt source(SGI or PPI): INTID 12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI12                                   (12U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI12_CORE3                               (12U)
#ifndef INTC_INTSRC_NUM_12
#define INTC_INTSRC_NUM_12                                     (12U)
#endif /* INTC_INTSRC_NUM_12 */
/* Internal interrupt source(SGI or PPI): INTID 13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI13                                   (13U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI13_CORE3                               (13U)
#ifndef INTC_INTSRC_NUM_13
#define INTC_INTSRC_NUM_13                                     (13U)
#endif /* INTC_INTSRC_NUM_13 */
/* Internal interrupt source(SGI or PPI): INTID 14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI14                                   (14U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI14_CORE3                               (14U)
#ifndef INTC_INTSRC_NUM_14
#define INTC_INTSRC_NUM_14                                     (14U)
#endif /* INTC_INTSRC_NUM_14 */
/* Internal interrupt source(SGI or PPI): INTID 15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI15                                   (15U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_SGI15_CORE3                               (15U)
#ifndef INTC_INTSRC_NUM_15
#define INTC_INTSRC_NUM_15                                     (15U)
#endif /* INTC_INTSRC_NUM_15 */
/* Internal interrupt source(SGI or PPI): INTID 16 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT0                                   (16U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT0_CORE0                               (16U)
#ifndef INTC_INTSRC_NUM_16
#define INTC_INTSRC_NUM_16                                     (16U)
#endif /* INTC_INTSRC_NUM_16 */
/* Internal interrupt source(SGI or PPI): INTID 17 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT1                                   (17U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT1_CORE0                               (17U)
#ifndef INTC_INTSRC_NUM_17
#define INTC_INTSRC_NUM_17                                     (17U)
#endif /* INTC_INTSRC_NUM_17 */
/* Internal interrupt source(SGI or PPI): INTID 18 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT2                                   (18U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT2_CORE0                               (18U)
#ifndef INTC_INTSRC_NUM_18
#define INTC_INTSRC_NUM_18                                     (18U)
#endif /* INTC_INTSRC_NUM_18 */
/* Internal interrupt source(SGI or PPI): INTID 19 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT0                                   (19U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT0_CORE0                               (19U)
#ifndef INTC_INTSRC_NUM_19
#define INTC_INTSRC_NUM_19                                     (19U)
#endif /* INTC_INTSRC_NUM_19 */
/* Internal interrupt source(SGI or PPI): INTID 20 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT1                                   (20U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT1_CORE0                               (20U)
#ifndef INTC_INTSRC_NUM_20
#define INTC_INTSRC_NUM_20                                     (20U)
#endif /* INTC_INTSRC_NUM_20 */
/* Internal interrupt source(SGI or PPI): INTID 21 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT2                                   (21U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT2_CORE0                               (21U)
#ifndef INTC_INTSRC_NUM_21
#define INTC_INTSRC_NUM_21                                     (21U)
#endif /* INTC_INTSRC_NUM_21 */
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
/* Internal interrupt source(SGI or PPI): INTID 16 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC0INT0                                   (16U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC0INT0_CORE1                               (16U)
#ifndef INTC_INTSRC_NUM_16
#define INTC_INTSRC_NUM_16                                     (16U)
#endif /* INTC_INTSRC_NUM_16 */
/* Internal interrupt source(SGI or PPI): INTID 17 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC0INT1                                   (17U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC0INT1_CORE1                               (17U)
#ifndef INTC_INTSRC_NUM_17
#define INTC_INTSRC_NUM_17                                     (17U)
#endif /* INTC_INTSRC_NUM_17 */
/* Internal interrupt source(SGI or PPI): INTID 18 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC0INT2                                   (18U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC0INT2_CORE1                               (18U)
#ifndef INTC_INTSRC_NUM_18
#define INTC_INTSRC_NUM_18                                     (18U)
#endif /* INTC_INTSRC_NUM_18 */
/* Internal interrupt source(SGI or PPI): INTID 19 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC1INT0                                   (19U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC1INT0_CORE1                               (19U)
#ifndef INTC_INTSRC_NUM_19
#define INTC_INTSRC_NUM_19                                     (19U)
#endif /* INTC_INTSRC_NUM_19 */
/* Internal interrupt source(SGI or PPI): INTID 20 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC1INT1                                   (20U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC1INT1_CORE1                               (20U)
#ifndef INTC_INTSRC_NUM_20
#define INTC_INTSRC_NUM_20                                     (20U)
#endif /* INTC_INTSRC_NUM_20 */
/* Internal interrupt source(SGI or PPI): INTID 21 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC1INT2                                   (21U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_GIPC1INT2_CORE1                               (21U)
#ifndef INTC_INTSRC_NUM_21
#define INTC_INTSRC_NUM_21                                     (21U)
#endif /* INTC_INTSRC_NUM_21 */
/* Internal interrupt source(SGI or PPI): INTID 22 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_DBGCCI                                   (22U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_DBGCCI_CORE1                               (22U)
#ifndef INTC_INTSRC_NUM_22
#define INTC_INTSRC_NUM_22                                     (22U)
#endif /* INTC_INTSRC_NUM_22 */
/* Internal interrupt source(SGI or PPI): INTID 23 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_PMCOINT                                   (23U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_PMCOINT_CORE1                               (23U)
#ifndef INTC_INTSRC_NUM_23
#define INTC_INTSRC_NUM_23                                     (23U)
#endif /* INTC_INTSRC_NUM_23 */
/* Internal interrupt source(SGI or PPI): INTID 24 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_CTIINT                                   (24U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_CTIINT_CORE1                               (24U)
#ifndef INTC_INTSRC_NUM_24
#define INTC_INTSRC_NUM_24                                     (24U)
#endif /* INTC_INTSRC_NUM_24 */
/* Internal interrupt source(SGI or PPI): INTID 25 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_VCPUIMINT                                   (25U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_VCPUIMINT_CORE1                               (25U)
#ifndef INTC_INTSRC_NUM_25
#define INTC_INTSRC_NUM_25                                     (25U)
#endif /* INTC_INTSRC_NUM_25 */
/* Internal interrupt source(SGI or PPI): INTID 26 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_HTINT                                   (26U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_HTINT_CORE1                               (26U)
#ifndef INTC_INTSRC_NUM_26
#define INTC_INTSRC_NUM_26                                     (26U)
#endif /* INTC_INTSRC_NUM_26 */
/* Internal interrupt source(SGI or PPI): INTID 27 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_VTINT                                   (27U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_VTINT_CORE1                               (27U)
#ifndef INTC_INTSRC_NUM_27
#define INTC_INTSRC_NUM_27                                     (27U)
#endif /* INTC_INTSRC_NUM_27 */
/* Internal interrupt source(SGI or PPI): INTID 30 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_NSPTINT                                   (30U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_NSPTINT_CORE1                               (30U)
#ifndef INTC_INTSRC_NUM_30
#define INTC_INTSRC_NUM_30                                     (30U)
#endif /* INTC_INTSRC_NUM_30 */
/* Internal interrupt source(SGI or PPI): INTID 16 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC0INT0                                   (16U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC0INT0_CORE2                               (16U)
#ifndef INTC_INTSRC_NUM_16
#define INTC_INTSRC_NUM_16                                     (16U)
#endif /* INTC_INTSRC_NUM_16 */
/* Internal interrupt source(SGI or PPI): INTID 17 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC0INT1                                   (17U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC0INT1_CORE2                               (17U)
#ifndef INTC_INTSRC_NUM_17
#define INTC_INTSRC_NUM_17                                     (17U)
#endif /* INTC_INTSRC_NUM_17 */
/* Internal interrupt source(SGI or PPI): INTID 18 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC0INT2                                   (18U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC0INT2_CORE2                               (18U)
#ifndef INTC_INTSRC_NUM_18
#define INTC_INTSRC_NUM_18                                     (18U)
#endif /* INTC_INTSRC_NUM_18 */
/* Internal interrupt source(SGI or PPI): INTID 19 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC1INT0                                   (19U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC1INT0_CORE2                               (19U)
#ifndef INTC_INTSRC_NUM_19
#define INTC_INTSRC_NUM_19                                     (19U)
#endif /* INTC_INTSRC_NUM_19 */
/* Internal interrupt source(SGI or PPI): INTID 20 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC1INT1                                   (20U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC1INT1_CORE2                               (20U)
#ifndef INTC_INTSRC_NUM_20
#define INTC_INTSRC_NUM_20                                     (20U)
#endif /* INTC_INTSRC_NUM_20 */
/* Internal interrupt source(SGI or PPI): INTID 21 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC1INT2                                   (21U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_GIPC1INT2_CORE2                               (21U)
#ifndef INTC_INTSRC_NUM_21
#define INTC_INTSRC_NUM_21                                     (21U)
#endif /* INTC_INTSRC_NUM_21 */
/* Internal interrupt source(SGI or PPI): INTID 22 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_DBGCCI                                   (22U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_DBGCCI_CORE2                               (22U)
#ifndef INTC_INTSRC_NUM_22
#define INTC_INTSRC_NUM_22                                     (22U)
#endif /* INTC_INTSRC_NUM_22 */
/* Internal interrupt source(SGI or PPI): INTID 23 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_PMCOINT                                   (23U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_PMCOINT_CORE2                               (23U)
#ifndef INTC_INTSRC_NUM_23
#define INTC_INTSRC_NUM_23                                     (23U)
#endif /* INTC_INTSRC_NUM_23 */
/* Internal interrupt source(SGI or PPI): INTID 24 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_CTIINT                                   (24U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_CTIINT_CORE2                               (24U)
#ifndef INTC_INTSRC_NUM_24
#define INTC_INTSRC_NUM_24                                     (24U)
#endif /* INTC_INTSRC_NUM_24 */
/* Internal interrupt source(SGI or PPI): INTID 25 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_VCPUIMINT                                   (25U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_VCPUIMINT_CORE2                               (25U)
#ifndef INTC_INTSRC_NUM_25
#define INTC_INTSRC_NUM_25                                     (25U)
#endif /* INTC_INTSRC_NUM_25 */
/* Internal interrupt source(SGI or PPI): INTID 26 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_HTINT                                   (26U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_HTINT_CORE2                               (26U)
#ifndef INTC_INTSRC_NUM_26
#define INTC_INTSRC_NUM_26                                     (26U)
#endif /* INTC_INTSRC_NUM_26 */
/* Internal interrupt source(SGI or PPI): INTID 27 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_VTINT                                   (27U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_VTINT_CORE2                               (27U)
#ifndef INTC_INTSRC_NUM_27
#define INTC_INTSRC_NUM_27                                     (27U)
#endif /* INTC_INTSRC_NUM_27 */
/* Internal interrupt source(SGI or PPI): INTID 30 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_NSPTINT                                   (30U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_NSPTINT_CORE2                               (30U)
#ifndef INTC_INTSRC_NUM_30
#define INTC_INTSRC_NUM_30                                     (30U)
#endif /* INTC_INTSRC_NUM_30 */
/* Internal interrupt source(SGI or PPI): INTID 16 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT0                                   (16U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT0_CORE3                               (16U)
#ifndef INTC_INTSRC_NUM_16
#define INTC_INTSRC_NUM_16                                     (16U)
#endif /* INTC_INTSRC_NUM_16 */
/* Internal interrupt source(SGI or PPI): INTID 17 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT1                                   (17U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT1_CORE3                               (17U)
#ifndef INTC_INTSRC_NUM_17
#define INTC_INTSRC_NUM_17                                     (17U)
#endif /* INTC_INTSRC_NUM_17 */
/* Internal interrupt source(SGI or PPI): INTID 18 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT2                                   (18U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC0INT2_CORE3                               (18U)
#ifndef INTC_INTSRC_NUM_18
#define INTC_INTSRC_NUM_18                                     (18U)
#endif /* INTC_INTSRC_NUM_18 */
/* Internal interrupt source(SGI or PPI): INTID 19 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT0                                   (19U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT0_CORE3                               (19U)
#ifndef INTC_INTSRC_NUM_19
#define INTC_INTSRC_NUM_19                                     (19U)
#endif /* INTC_INTSRC_NUM_19 */
/* Internal interrupt source(SGI or PPI): INTID 20 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT1                                   (20U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT1_CORE3                               (20U)
#ifndef INTC_INTSRC_NUM_20
#define INTC_INTSRC_NUM_20                                     (20U)
#endif /* INTC_INTSRC_NUM_20 */
/* Internal interrupt source(SGI or PPI): INTID 21 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT2                                   (21U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_GIPC1INT2_CORE3                               (21U)
#ifndef INTC_INTSRC_NUM_21
#define INTC_INTSRC_NUM_21                                     (21U)
#endif /* INTC_INTSRC_NUM_21 */
/* Internal interrupt source(SGI or PPI): INTID 22 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_DBGCCI                                   (22U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_DBGCCI_CORE3                               (22U)
#ifndef INTC_INTSRC_NUM_22
#define INTC_INTSRC_NUM_22                                     (22U)
#endif /* INTC_INTSRC_NUM_22 */
/* Internal interrupt source(SGI or PPI): INTID 23 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_PMCOINT                                   (23U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_PMCOINT_CORE3                               (23U)
#ifndef INTC_INTSRC_NUM_23
#define INTC_INTSRC_NUM_23                                     (23U)
#endif /* INTC_INTSRC_NUM_23 */
/* Internal interrupt source(SGI or PPI): INTID 24 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_CTIINT                                   (24U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_CTIINT_CORE3                               (24U)
#ifndef INTC_INTSRC_NUM_24
#define INTC_INTSRC_NUM_24                                     (24U)
#endif /* INTC_INTSRC_NUM_24 */
/* Internal interrupt source(SGI or PPI): INTID 25 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_VCPUIMINT                                   (25U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_VCPUIMINT_CORE3                               (25U)
#ifndef INTC_INTSRC_NUM_25
#define INTC_INTSRC_NUM_25                                     (25U)
#endif /* INTC_INTSRC_NUM_25 */
/* Internal interrupt source(SGI or PPI): INTID 26 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_HTINT                                   (26U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_HTINT_CORE3                               (26U)
#ifndef INTC_INTSRC_NUM_26
#define INTC_INTSRC_NUM_26                                     (26U)
#endif /* INTC_INTSRC_NUM_26 */
/* Internal interrupt source(SGI or PPI): INTID 27 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_VTINT                                   (27U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_VTINT_CORE3                               (27U)
#ifndef INTC_INTSRC_NUM_27
#define INTC_INTSRC_NUM_27                                     (27U)
#endif /* INTC_INTSRC_NUM_27 */
/* Internal interrupt source(SGI or PPI): INTID 30 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_NSPTINT                                   (30U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_NSPTINT_CORE3                               (30U)
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
/* External interrupt source(SPI): INTID 38 - CPU2WDT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2WDT_INT                                   (38U)
#ifndef INTC_INTSRC_NUM_38        
#define INTC_INTSRC_NUM_38                                     (38U)
#endif /* INTC_INTSRC_NUM_38 */
/* External interrupt source(SPI): INTID 39 - CPU3WDT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3WDT_INT                                   (39U)
#ifndef INTC_INTSRC_NUM_39        
#define INTC_INTSRC_NUM_39                                     (39U)
#endif /* INTC_INTSRC_NUM_39 */
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
/* External interrupt source(SPI): INTID 35 - PMC_TEINT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PMC_TEINT                                   (35U)
#ifndef INTC_INTSRC_NUM_35        
#define INTC_INTSRC_NUM_35                                     (35U)
#endif /* INTC_INTSRC_NUM_35 */
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
/* External interrupt source(SPI): INTID 42 - CLUSTER_COMMRX1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CLUSTER_COMMRX1                                   (42U)
#ifndef INTC_INTSRC_NUM_42        
#define INTC_INTSRC_NUM_42                                     (42U)
#endif /* INTC_INTSRC_NUM_42 */
/* External interrupt source(SPI): INTID 43 - CLUSTER_COMMTX1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CLUSTER_COMMTX1                                   (43U)
#ifndef INTC_INTSRC_NUM_43        
#define INTC_INTSRC_NUM_43                                     (43U)
#endif /* INTC_INTSRC_NUM_43 */
/* External interrupt source(SPI): INTID 44 - CPU0_BTCMACER */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU0_BTCMACER                                   (44U)
#ifndef INTC_INTSRC_NUM_44        
#define INTC_INTSRC_NUM_44                                     (44U)
#endif /* INTC_INTSRC_NUM_44 */
/* External interrupt source(SPI): INTID 45 - CPU1_BTCMACER */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU1_BTCMACER                                   (45U)
#ifndef INTC_INTSRC_NUM_45        
#define INTC_INTSRC_NUM_45                                     (45U)
#endif /* INTC_INTSRC_NUM_45 */
/* External interrupt source(SPI): INTID 46 - CLUSTER1_COMMRX0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CLUSTER1_COMMRX0                                   (46U)
#ifndef INTC_INTSRC_NUM_46        
#define INTC_INTSRC_NUM_46                                     (46U)
#endif /* INTC_INTSRC_NUM_46 */
/* External interrupt source(SPI): INTID 47 - CLUSTER1_COMMTX0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CLUSTER1_COMMTX0                                   (47U)
#ifndef INTC_INTSRC_NUM_47        
#define INTC_INTSRC_NUM_47                                     (47U)
#endif /* INTC_INTSRC_NUM_47 */
/* External interrupt source(SPI): INTID 48 - CLUSTER1_COMMRX1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CLUSTER1_COMMRX1                                   (48U)
#ifndef INTC_INTSRC_NUM_48        
#define INTC_INTSRC_NUM_48                                     (48U)
#endif /* INTC_INTSRC_NUM_48 */
/* External interrupt source(SPI): INTID 49 - CLUSTER1_COMMTX1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CLUSTER1_COMMTX1                                   (49U)
#ifndef INTC_INTSRC_NUM_49        
#define INTC_INTSRC_NUM_49                                     (49U)
#endif /* INTC_INTSRC_NUM_49 */
/* External interrupt source(SPI): INTID 50 - CPU2_BTCMACER */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU2_BTCMACER                                   (50U)
#ifndef INTC_INTSRC_NUM_50        
#define INTC_INTSRC_NUM_50                                     (50U)
#endif /* INTC_INTSRC_NUM_50 */
/* External interrupt source(SPI): INTID 51 - CPU3_BTCMACER */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CPU3_BTCMACER                                   (51U)
#ifndef INTC_INTSRC_NUM_51        
#define INTC_INTSRC_NUM_51                                     (51U)
#endif /* INTC_INTSRC_NUM_51 */
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
/* Internal interrupt source(SGI or PPI): INTID 89 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU1SOFTINT0                                   (89U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU1SOFTINT0_CORE1                               (89U)
#ifndef INTC_INTSRC_NUM_89
#define INTC_INTSRC_NUM_89                                     (89U)
#endif /* INTC_INTSRC_NUM_89 */
/* Internal interrupt source(SGI or PPI): INTID 90 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU1SOFTINT1                                   (90U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU1SOFTINT1_CORE1                               (90U)
#ifndef INTC_INTSRC_NUM_90
#define INTC_INTSRC_NUM_90                                     (90U)
#endif /* INTC_INTSRC_NUM_90 */
/* Internal interrupt source(SGI or PPI): INTID 91 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU1SOFTINT2                                   (91U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU1SOFTINT2_CORE1                               (91U)
#ifndef INTC_INTSRC_NUM_91
#define INTC_INTSRC_NUM_91                                     (91U)
#endif /* INTC_INTSRC_NUM_91 */
/* Internal interrupt source(SGI or PPI): INTID 92 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU1SOFTINT3                                   (92U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU1SOFTINT3_CORE1                               (92U)
#ifndef INTC_INTSRC_NUM_92
#define INTC_INTSRC_NUM_92                                     (92U)
#endif /* INTC_INTSRC_NUM_92 */
/* Internal interrupt source(SGI or PPI): INTID 56 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU2SOFTINT0                                   (56U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU2SOFTINT0_CORE2                               (56U)
#ifndef INTC_INTSRC_NUM_56
#define INTC_INTSRC_NUM_56                                     (56U)
#endif /* INTC_INTSRC_NUM_56 */
/* Internal interrupt source(SGI or PPI): INTID 57 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU2SOFTINT1                                   (57U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU2SOFTINT1_CORE2                               (57U)
#ifndef INTC_INTSRC_NUM_57
#define INTC_INTSRC_NUM_57                                     (57U)
#endif /* INTC_INTSRC_NUM_57 */
/* Internal interrupt source(SGI or PPI): INTID 58 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU2SOFTINT2                                   (58U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU2SOFTINT2_CORE2                               (58U)
#ifndef INTC_INTSRC_NUM_58
#define INTC_INTSRC_NUM_58                                     (58U)
#endif /* INTC_INTSRC_NUM_58 */
/* Internal interrupt source(SGI or PPI): INTID 59 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU2SOFTINT3                                   (59U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU2SOFTINT3_CORE2                               (59U)
#ifndef INTC_INTSRC_NUM_59
#define INTC_INTSRC_NUM_59                                     (59U)
#endif /* INTC_INTSRC_NUM_59 */
/* Internal interrupt source(SGI or PPI): INTID 89 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU3SOFTINT0                                   (89U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU3SOFTINT0_CORE3                               (89U)
#ifndef INTC_INTSRC_NUM_89
#define INTC_INTSRC_NUM_89                                     (89U)
#endif /* INTC_INTSRC_NUM_89 */
/* Internal interrupt source(SGI or PPI): INTID 90 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU3SOFTINT1                                   (90U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU3SOFTINT1_CORE3                               (90U)
#ifndef INTC_INTSRC_NUM_90
#define INTC_INTSRC_NUM_90                                     (90U)
#endif /* INTC_INTSRC_NUM_90 */
/* Internal interrupt source(SGI or PPI): INTID 91 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU3SOFTINT2                                   (91U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU3SOFTINT2_CORE3                               (91U)
#ifndef INTC_INTSRC_NUM_91
#define INTC_INTSRC_NUM_91                                     (91U)
#endif /* INTC_INTSRC_NUM_91 */
/* Internal interrupt source(SGI or PPI): INTID 92 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU3SOFTINT3                                   (92U)   
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_INTC_CPU3SOFTINT3_CORE3                               (92U)
#ifndef INTC_INTSRC_NUM_92
#define INTC_INTSRC_NUM_92                                     (92U)
#endif /* INTC_INTSRC_NUM_92 */
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
/* External interrupt source(SPI): INTID 69 - OVC_CPU1_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_OVC_CPU1_INT                                   (69U)
#ifndef INTC_INTSRC_NUM_69        
#define INTC_INTSRC_NUM_69                                     (69U)
#endif /* INTC_INTSRC_NUM_69 */
/* External interrupt source(SPI): INTID 70 - OVC_CPU2_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_OVC_CPU2_INT                                   (70U)
#ifndef INTC_INTSRC_NUM_70        
#define INTC_INTSRC_NUM_70                                     (70U)
#endif /* INTC_INTSRC_NUM_70 */
/* External interrupt source(SPI): INTID 71 - OVC_CPU3_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_OVC_CPU3_INT                                   (71U)
#ifndef INTC_INTSRC_NUM_71        
#define INTC_INTSRC_NUM_71                                     (71U)
#endif /* INTC_INTSRC_NUM_71 */
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
/* External interrupt source(SPI): INTID 75 - SBD_PERCH_TX_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SBD_PERCH_TX_INT2                                   (75U)
#ifndef INTC_INTSRC_NUM_75        
#define INTC_INTSRC_NUM_75                                     (75U)
#endif /* INTC_INTSRC_NUM_75 */
/* External interrupt source(SPI): INTID 76 - SBD_PERCH_TX_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SBD_PERCH_TX_INT3                                   (76U)
#ifndef INTC_INTSRC_NUM_76        
#define INTC_INTSRC_NUM_76                                     (76U)
#endif /* INTC_INTSRC_NUM_76 */
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
/* External interrupt source(SPI): INTID 79 - SBD_PERCH_RX_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SBD_PERCH_RX_INT2                                   (79U)
#ifndef INTC_INTSRC_NUM_79        
#define INTC_INTSRC_NUM_79                                     (79U)
#endif /* INTC_INTSRC_NUM_79 */
/* External interrupt source(SPI): INTID 80 - SBD_PERCH_RX_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SBD_PERCH_RX_INT3                                   (80U)
#ifndef INTC_INTSRC_NUM_80        
#define INTC_INTSRC_NUM_80                                     (80U)
#endif /* INTC_INTSRC_NUM_80 */
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
/* External interrupt source(SPI): INTID 99 - DMA0_CH_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT4                                   (99U)
#ifndef INTC_INTSRC_NUM_99        
#define INTC_INTSRC_NUM_99                                     (99U)
#endif /* INTC_INTSRC_NUM_99 */
/* External interrupt source(SPI): INTID 100 - DMA0_CH_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT5                                   (100U)
#ifndef INTC_INTSRC_NUM_100        
#define INTC_INTSRC_NUM_100                                     (100U)
#endif /* INTC_INTSRC_NUM_100 */
/* External interrupt source(SPI): INTID 101 - DMA0_CH_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT6                                   (101U)
#ifndef INTC_INTSRC_NUM_101        
#define INTC_INTSRC_NUM_101                                     (101U)
#endif /* INTC_INTSRC_NUM_101 */
/* External interrupt source(SPI): INTID 102 - DMA0_CH_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT7                                   (102U)
#ifndef INTC_INTSRC_NUM_102        
#define INTC_INTSRC_NUM_102                                     (102U)
#endif /* INTC_INTSRC_NUM_102 */
/* External interrupt source(SPI): INTID 103 - DMA0_CH_INT8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT8                                   (103U)
#ifndef INTC_INTSRC_NUM_103        
#define INTC_INTSRC_NUM_103                                     (103U)
#endif /* INTC_INTSRC_NUM_103 */
/* External interrupt source(SPI): INTID 104 - DMA0_CH_INT9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT9                                   (104U)
#ifndef INTC_INTSRC_NUM_104        
#define INTC_INTSRC_NUM_104                                     (104U)
#endif /* INTC_INTSRC_NUM_104 */
/* External interrupt source(SPI): INTID 105 - DMA0_CH_INT10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT10                                   (105U)
#ifndef INTC_INTSRC_NUM_105        
#define INTC_INTSRC_NUM_105                                     (105U)
#endif /* INTC_INTSRC_NUM_105 */
/* External interrupt source(SPI): INTID 106 - DMA0_CH_INT11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT11                                   (106U)
#ifndef INTC_INTSRC_NUM_106        
#define INTC_INTSRC_NUM_106                                     (106U)
#endif /* INTC_INTSRC_NUM_106 */
/* External interrupt source(SPI): INTID 107 - DMA0_CH_INT12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT12                                   (107U)
#ifndef INTC_INTSRC_NUM_107        
#define INTC_INTSRC_NUM_107                                     (107U)
#endif /* INTC_INTSRC_NUM_107 */
/* External interrupt source(SPI): INTID 108 - DMA0_CH_INT13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT13                                   (108U)
#ifndef INTC_INTSRC_NUM_108        
#define INTC_INTSRC_NUM_108                                     (108U)
#endif /* INTC_INTSRC_NUM_108 */
/* External interrupt source(SPI): INTID 287 - DMA0_CH_INT14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT14                                   (287U)
#ifndef INTC_INTSRC_NUM_287        
#define INTC_INTSRC_NUM_287                                     (287U)
#endif /* INTC_INTSRC_NUM_287 */
/* External interrupt source(SPI): INTID 288 - DMA0_CH_INT15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA0_CH_INT15                                   (288U)
#ifndef INTC_INTSRC_NUM_288        
#define INTC_INTSRC_NUM_288                                     (288U)
#endif /* INTC_INTSRC_NUM_288 */
/* External interrupt source(SPI): INTID 149 - DMA1_CH_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT0                                   (149U)
#ifndef INTC_INTSRC_NUM_149        
#define INTC_INTSRC_NUM_149                                     (149U)
#endif /* INTC_INTSRC_NUM_149 */
/* External interrupt source(SPI): INTID 150 - DMA1_CH_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT1                                   (150U)
#ifndef INTC_INTSRC_NUM_150        
#define INTC_INTSRC_NUM_150                                     (150U)
#endif /* INTC_INTSRC_NUM_150 */
/* External interrupt source(SPI): INTID 151 - DMA1_CH_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT2                                   (151U)
#ifndef INTC_INTSRC_NUM_151        
#define INTC_INTSRC_NUM_151                                     (151U)
#endif /* INTC_INTSRC_NUM_151 */
/* External interrupt source(SPI): INTID 152 - DMA1_CH_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT3                                   (152U)
#ifndef INTC_INTSRC_NUM_152        
#define INTC_INTSRC_NUM_152                                     (152U)
#endif /* INTC_INTSRC_NUM_152 */
/* External interrupt source(SPI): INTID 153 - DMA1_CH_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT4                                   (153U)
#ifndef INTC_INTSRC_NUM_153        
#define INTC_INTSRC_NUM_153                                     (153U)
#endif /* INTC_INTSRC_NUM_153 */
/* External interrupt source(SPI): INTID 154 - DMA1_CH_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT5                                   (154U)
#ifndef INTC_INTSRC_NUM_154        
#define INTC_INTSRC_NUM_154                                     (154U)
#endif /* INTC_INTSRC_NUM_154 */
/* External interrupt source(SPI): INTID 155 - DMA1_CH_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT6                                   (155U)
#ifndef INTC_INTSRC_NUM_155        
#define INTC_INTSRC_NUM_155                                     (155U)
#endif /* INTC_INTSRC_NUM_155 */
/* External interrupt source(SPI): INTID 156 - DMA1_CH_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT7                                   (156U)
#ifndef INTC_INTSRC_NUM_156        
#define INTC_INTSRC_NUM_156                                     (156U)
#endif /* INTC_INTSRC_NUM_156 */
/* External interrupt source(SPI): INTID 157 - DMA1_CH_INT8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT8                                   (157U)
#ifndef INTC_INTSRC_NUM_157        
#define INTC_INTSRC_NUM_157                                     (157U)
#endif /* INTC_INTSRC_NUM_157 */
/* External interrupt source(SPI): INTID 158 - DMA1_CH_INT9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT9                                   (158U)
#ifndef INTC_INTSRC_NUM_158        
#define INTC_INTSRC_NUM_158                                     (158U)
#endif /* INTC_INTSRC_NUM_158 */
/* External interrupt source(SPI): INTID 159 - DMA1_CH_INT10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT10                                   (159U)
#ifndef INTC_INTSRC_NUM_159        
#define INTC_INTSRC_NUM_159                                     (159U)
#endif /* INTC_INTSRC_NUM_159 */
/* External interrupt source(SPI): INTID 160 - DMA1_CH_INT11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT11                                   (160U)
#ifndef INTC_INTSRC_NUM_160        
#define INTC_INTSRC_NUM_160                                     (160U)
#endif /* INTC_INTSRC_NUM_160 */
/* External interrupt source(SPI): INTID 161 - DMA1_CH_INT12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT12                                   (161U)
#ifndef INTC_INTSRC_NUM_161        
#define INTC_INTSRC_NUM_161                                     (161U)
#endif /* INTC_INTSRC_NUM_161 */
/* External interrupt source(SPI): INTID 162 - DMA1_CH_INT13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT13                                   (162U)
#ifndef INTC_INTSRC_NUM_162        
#define INTC_INTSRC_NUM_162                                     (162U)
#endif /* INTC_INTSRC_NUM_162 */
/* External interrupt source(SPI): INTID 163 - DMA1_CH_INT14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT14                                   (163U)
#ifndef INTC_INTSRC_NUM_163        
#define INTC_INTSRC_NUM_163                                     (163U)
#endif /* INTC_INTSRC_NUM_163 */
/* External interrupt source(SPI): INTID 164 - DMA1_CH_INT15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT15                                   (164U)
#ifndef INTC_INTSRC_NUM_164        
#define INTC_INTSRC_NUM_164                                     (164U)
#endif /* INTC_INTSRC_NUM_164 */
/* External interrupt source(SPI): INTID 165 - DMA1_CH_INT16 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT16                                   (165U)
#ifndef INTC_INTSRC_NUM_165        
#define INTC_INTSRC_NUM_165                                     (165U)
#endif /* INTC_INTSRC_NUM_165 */
/* External interrupt source(SPI): INTID 166 - DMA1_CH_INT17 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT17                                   (166U)
#ifndef INTC_INTSRC_NUM_166        
#define INTC_INTSRC_NUM_166                                     (166U)
#endif /* INTC_INTSRC_NUM_166 */
/* External interrupt source(SPI): INTID 167 - DMA1_CH_INT18 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT18                                   (167U)
#ifndef INTC_INTSRC_NUM_167        
#define INTC_INTSRC_NUM_167                                     (167U)
#endif /* INTC_INTSRC_NUM_167 */
/* External interrupt source(SPI): INTID 168 - DMA1_CH_INT19 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT19                                   (168U)
#ifndef INTC_INTSRC_NUM_168        
#define INTC_INTSRC_NUM_168                                     (168U)
#endif /* INTC_INTSRC_NUM_168 */
/* External interrupt source(SPI): INTID 169 - DMA1_CH_INT20 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT20                                   (169U)
#ifndef INTC_INTSRC_NUM_169        
#define INTC_INTSRC_NUM_169                                     (169U)
#endif /* INTC_INTSRC_NUM_169 */
/* External interrupt source(SPI): INTID 170 - DMA1_CH_INT21 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT21                                   (170U)
#ifndef INTC_INTSRC_NUM_170        
#define INTC_INTSRC_NUM_170                                     (170U)
#endif /* INTC_INTSRC_NUM_170 */
/* External interrupt source(SPI): INTID 171 - DMA1_CH_INT22 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT22                                   (171U)
#ifndef INTC_INTSRC_NUM_171        
#define INTC_INTSRC_NUM_171                                     (171U)
#endif /* INTC_INTSRC_NUM_171 */
/* External interrupt source(SPI): INTID 172 - DMA1_CH_INT23 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT23                                   (172U)
#ifndef INTC_INTSRC_NUM_172        
#define INTC_INTSRC_NUM_172                                     (172U)
#endif /* INTC_INTSRC_NUM_172 */
/* External interrupt source(SPI): INTID 173 - DMA1_CH_INT24 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT24                                   (173U)
#ifndef INTC_INTSRC_NUM_173        
#define INTC_INTSRC_NUM_173                                     (173U)
#endif /* INTC_INTSRC_NUM_173 */
/* External interrupt source(SPI): INTID 174 - DMA1_CH_INT25 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT25                                   (174U)
#ifndef INTC_INTSRC_NUM_174        
#define INTC_INTSRC_NUM_174                                     (174U)
#endif /* INTC_INTSRC_NUM_174 */
/* External interrupt source(SPI): INTID 175 - DMA1_CH_INT26 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT26                                   (175U)
#ifndef INTC_INTSRC_NUM_175        
#define INTC_INTSRC_NUM_175                                     (175U)
#endif /* INTC_INTSRC_NUM_175 */
/* External interrupt source(SPI): INTID 176 - DMA1_CH_INT27 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT27                                   (176U)
#ifndef INTC_INTSRC_NUM_176        
#define INTC_INTSRC_NUM_176                                     (176U)
#endif /* INTC_INTSRC_NUM_176 */
/* External interrupt source(SPI): INTID 177 - DMA1_CH_INT28 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT28                                   (177U)
#ifndef INTC_INTSRC_NUM_177        
#define INTC_INTSRC_NUM_177                                     (177U)
#endif /* INTC_INTSRC_NUM_177 */
/* External interrupt source(SPI): INTID 178 - DMA1_CH_INT29 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT29                                   (178U)
#ifndef INTC_INTSRC_NUM_178        
#define INTC_INTSRC_NUM_178                                     (178U)
#endif /* INTC_INTSRC_NUM_178 */
/* External interrupt source(SPI): INTID 179 - DMA1_CH_INT30 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT30                                   (179U)
#ifndef INTC_INTSRC_NUM_179        
#define INTC_INTSRC_NUM_179                                     (179U)
#endif /* INTC_INTSRC_NUM_179 */
/* External interrupt source(SPI): INTID 180 - DMA1_CH_INT31 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT31                                   (180U)
#ifndef INTC_INTSRC_NUM_180        
#define INTC_INTSRC_NUM_180                                     (180U)
#endif /* INTC_INTSRC_NUM_180 */
/* External interrupt source(SPI): INTID 181 - DMA1_CH_INT32 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT32                                   (181U)
#ifndef INTC_INTSRC_NUM_181        
#define INTC_INTSRC_NUM_181                                     (181U)
#endif /* INTC_INTSRC_NUM_181 */
/* External interrupt source(SPI): INTID 182 - DMA1_CH_INT33 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT33                                   (182U)
#ifndef INTC_INTSRC_NUM_182        
#define INTC_INTSRC_NUM_182                                     (182U)
#endif /* INTC_INTSRC_NUM_182 */
/* External interrupt source(SPI): INTID 183 - DMA1_CH_INT34 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT34                                   (183U)
#ifndef INTC_INTSRC_NUM_183        
#define INTC_INTSRC_NUM_183                                     (183U)
#endif /* INTC_INTSRC_NUM_183 */
/* External interrupt source(SPI): INTID 184 - DMA1_CH_INT35 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT35                                   (184U)
#ifndef INTC_INTSRC_NUM_184        
#define INTC_INTSRC_NUM_184                                     (184U)
#endif /* INTC_INTSRC_NUM_184 */
/* External interrupt source(SPI): INTID 185 - DMA1_CH_INT36 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT36                                   (185U)
#ifndef INTC_INTSRC_NUM_185        
#define INTC_INTSRC_NUM_185                                     (185U)
#endif /* INTC_INTSRC_NUM_185 */
/* External interrupt source(SPI): INTID 186 - DMA1_CH_INT37 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT37                                   (186U)
#ifndef INTC_INTSRC_NUM_186        
#define INTC_INTSRC_NUM_186                                     (186U)
#endif /* INTC_INTSRC_NUM_186 */
/* External interrupt source(SPI): INTID 187 - DMA1_CH_INT38 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT38                                   (187U)
#ifndef INTC_INTSRC_NUM_187        
#define INTC_INTSRC_NUM_187                                     (187U)
#endif /* INTC_INTSRC_NUM_187 */
/* External interrupt source(SPI): INTID 188 - DMA1_CH_INT39 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT39                                   (188U)
#ifndef INTC_INTSRC_NUM_188        
#define INTC_INTSRC_NUM_188                                     (188U)
#endif /* INTC_INTSRC_NUM_188 */
/* External interrupt source(SPI): INTID 189 - DMA1_CH_INT40 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT40                                   (189U)
#ifndef INTC_INTSRC_NUM_189        
#define INTC_INTSRC_NUM_189                                     (189U)
#endif /* INTC_INTSRC_NUM_189 */
/* External interrupt source(SPI): INTID 190 - DMA1_CH_INT41 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT41                                   (190U)
#ifndef INTC_INTSRC_NUM_190        
#define INTC_INTSRC_NUM_190                                     (190U)
#endif /* INTC_INTSRC_NUM_190 */
/* External interrupt source(SPI): INTID 191 - DMA1_CH_INT42 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT42                                   (191U)
#ifndef INTC_INTSRC_NUM_191        
#define INTC_INTSRC_NUM_191                                     (191U)
#endif /* INTC_INTSRC_NUM_191 */
/* External interrupt source(SPI): INTID 192 - DMA1_CH_INT43 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT43                                   (192U)
#ifndef INTC_INTSRC_NUM_192        
#define INTC_INTSRC_NUM_192                                     (192U)
#endif /* INTC_INTSRC_NUM_192 */
/* External interrupt source(SPI): INTID 193 - DMA1_CH_INT44 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT44                                   (193U)
#ifndef INTC_INTSRC_NUM_193        
#define INTC_INTSRC_NUM_193                                     (193U)
#endif /* INTC_INTSRC_NUM_193 */
/* External interrupt source(SPI): INTID 194 - DMA1_CH_INT45 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT45                                   (194U)
#ifndef INTC_INTSRC_NUM_194        
#define INTC_INTSRC_NUM_194                                     (194U)
#endif /* INTC_INTSRC_NUM_194 */
/* External interrupt source(SPI): INTID 199 - DMA1_CH_INT46 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT46                                   (199U)
#ifndef INTC_INTSRC_NUM_199        
#define INTC_INTSRC_NUM_199                                     (199U)
#endif /* INTC_INTSRC_NUM_199 */
/* External interrupt source(SPI): INTID 200 - DMA1_CH_INT47 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT47                                   (200U)
#ifndef INTC_INTSRC_NUM_200        
#define INTC_INTSRC_NUM_200                                     (200U)
#endif /* INTC_INTSRC_NUM_200 */
/* External interrupt source(SPI): INTID 201 - DMA1_CH_INT48 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT48                                   (201U)
#ifndef INTC_INTSRC_NUM_201        
#define INTC_INTSRC_NUM_201                                     (201U)
#endif /* INTC_INTSRC_NUM_201 */
/* External interrupt source(SPI): INTID 202 - DMA1_CH_INT49 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT49                                   (202U)
#ifndef INTC_INTSRC_NUM_202        
#define INTC_INTSRC_NUM_202                                     (202U)
#endif /* INTC_INTSRC_NUM_202 */
/* External interrupt source(SPI): INTID 203 - DMA1_CH_INT50 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT50                                   (203U)
#ifndef INTC_INTSRC_NUM_203        
#define INTC_INTSRC_NUM_203                                     (203U)
#endif /* INTC_INTSRC_NUM_203 */
/* External interrupt source(SPI): INTID 204 - DMA1_CH_INT51 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT51                                   (204U)
#ifndef INTC_INTSRC_NUM_204        
#define INTC_INTSRC_NUM_204                                     (204U)
#endif /* INTC_INTSRC_NUM_204 */
/* External interrupt source(SPI): INTID 205 - DMA1_CH_INT52 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT52                                   (205U)
#ifndef INTC_INTSRC_NUM_205        
#define INTC_INTSRC_NUM_205                                     (205U)
#endif /* INTC_INTSRC_NUM_205 */
/* External interrupt source(SPI): INTID 206 - DMA1_CH_INT53 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT53                                   (206U)
#ifndef INTC_INTSRC_NUM_206        
#define INTC_INTSRC_NUM_206                                     (206U)
#endif /* INTC_INTSRC_NUM_206 */
/* External interrupt source(SPI): INTID 207 - DMA1_CH_INT54 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT54                                   (207U)
#ifndef INTC_INTSRC_NUM_207        
#define INTC_INTSRC_NUM_207                                     (207U)
#endif /* INTC_INTSRC_NUM_207 */
/* External interrupt source(SPI): INTID 208 - DMA1_CH_INT55 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT55                                   (208U)
#ifndef INTC_INTSRC_NUM_208        
#define INTC_INTSRC_NUM_208                                     (208U)
#endif /* INTC_INTSRC_NUM_208 */
/* External interrupt source(SPI): INTID 209 - DMA1_CH_INT56 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT56                                   (209U)
#ifndef INTC_INTSRC_NUM_209        
#define INTC_INTSRC_NUM_209                                     (209U)
#endif /* INTC_INTSRC_NUM_209 */
/* External interrupt source(SPI): INTID 210 - DMA1_CH_INT57 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT57                                   (210U)
#ifndef INTC_INTSRC_NUM_210        
#define INTC_INTSRC_NUM_210                                     (210U)
#endif /* INTC_INTSRC_NUM_210 */
/* External interrupt source(SPI): INTID 211 - DMA1_CH_INT58 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT58                                   (211U)
#ifndef INTC_INTSRC_NUM_211        
#define INTC_INTSRC_NUM_211                                     (211U)
#endif /* INTC_INTSRC_NUM_211 */
/* External interrupt source(SPI): INTID 212 - DMA1_CH_INT59 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT59                                   (212U)
#ifndef INTC_INTSRC_NUM_212        
#define INTC_INTSRC_NUM_212                                     (212U)
#endif /* INTC_INTSRC_NUM_212 */
/* External interrupt source(SPI): INTID 213 - DMA1_CH_INT60 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT60                                   (213U)
#ifndef INTC_INTSRC_NUM_213        
#define INTC_INTSRC_NUM_213                                     (213U)
#endif /* INTC_INTSRC_NUM_213 */
/* External interrupt source(SPI): INTID 214 - DMA1_CH_INT61 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT61                                   (214U)
#ifndef INTC_INTSRC_NUM_214        
#define INTC_INTSRC_NUM_214                                     (214U)
#endif /* INTC_INTSRC_NUM_214 */
/* External interrupt source(SPI): INTID 215 - DMA1_CH_INT62 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT62                                   (215U)
#ifndef INTC_INTSRC_NUM_215        
#define INTC_INTSRC_NUM_215                                     (215U)
#endif /* INTC_INTSRC_NUM_215 */
/* External interrupt source(SPI): INTID 216 - DMA1_CH_INT63 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA1_CH_INT63                                   (216U)
#ifndef INTC_INTSRC_NUM_216        
#define INTC_INTSRC_NUM_216                                     (216U)
#endif /* INTC_INTSRC_NUM_216 */
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
/* External interrupt source(SPI): INTID 129 - DMA3_CH_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT0                                   (129U)
#ifndef INTC_INTSRC_NUM_129        
#define INTC_INTSRC_NUM_129                                     (129U)
#endif /* INTC_INTSRC_NUM_129 */
/* External interrupt source(SPI): INTID 130 - DMA3_CH_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT1                                   (130U)
#ifndef INTC_INTSRC_NUM_130        
#define INTC_INTSRC_NUM_130                                     (130U)
#endif /* INTC_INTSRC_NUM_130 */
/* External interrupt source(SPI): INTID 131 - DMA3_CH_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT2                                   (131U)
#ifndef INTC_INTSRC_NUM_131        
#define INTC_INTSRC_NUM_131                                     (131U)
#endif /* INTC_INTSRC_NUM_131 */
/* External interrupt source(SPI): INTID 132 - DMA3_CH_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT3                                   (132U)
#ifndef INTC_INTSRC_NUM_132        
#define INTC_INTSRC_NUM_132                                     (132U)
#endif /* INTC_INTSRC_NUM_132 */
/* External interrupt source(SPI): INTID 133 - DMA3_CH_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT4                                   (133U)
#ifndef INTC_INTSRC_NUM_133        
#define INTC_INTSRC_NUM_133                                     (133U)
#endif /* INTC_INTSRC_NUM_133 */
/* External interrupt source(SPI): INTID 134 - DMA3_CH_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT5                                   (134U)
#ifndef INTC_INTSRC_NUM_134        
#define INTC_INTSRC_NUM_134                                     (134U)
#endif /* INTC_INTSRC_NUM_134 */
/* External interrupt source(SPI): INTID 135 - DMA3_CH_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT6                                   (135U)
#ifndef INTC_INTSRC_NUM_135        
#define INTC_INTSRC_NUM_135                                     (135U)
#endif /* INTC_INTSRC_NUM_135 */
/* External interrupt source(SPI): INTID 136 - DMA3_CH_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT7                                   (136U)
#ifndef INTC_INTSRC_NUM_136        
#define INTC_INTSRC_NUM_136                                     (136U)
#endif /* INTC_INTSRC_NUM_136 */
/* External interrupt source(SPI): INTID 137 - DMA3_CH_INT8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT8                                   (137U)
#ifndef INTC_INTSRC_NUM_137        
#define INTC_INTSRC_NUM_137                                     (137U)
#endif /* INTC_INTSRC_NUM_137 */
/* External interrupt source(SPI): INTID 138 - DMA3_CH_INT9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT9                                   (138U)
#ifndef INTC_INTSRC_NUM_138        
#define INTC_INTSRC_NUM_138                                     (138U)
#endif /* INTC_INTSRC_NUM_138 */
/* External interrupt source(SPI): INTID 139 - DMA3_CH_INT10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT10                                   (139U)
#ifndef INTC_INTSRC_NUM_139        
#define INTC_INTSRC_NUM_139                                     (139U)
#endif /* INTC_INTSRC_NUM_139 */
/* External interrupt source(SPI): INTID 140 - DMA3_CH_INT11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT11                                   (140U)
#ifndef INTC_INTSRC_NUM_140        
#define INTC_INTSRC_NUM_140                                     (140U)
#endif /* INTC_INTSRC_NUM_140 */
/* External interrupt source(SPI): INTID 141 - DMA3_CH_INT12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT12                                   (141U)
#ifndef INTC_INTSRC_NUM_141        
#define INTC_INTSRC_NUM_141                                     (141U)
#endif /* INTC_INTSRC_NUM_141 */
/* External interrupt source(SPI): INTID 142 - DMA3_CH_INT13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT13                                   (142U)
#ifndef INTC_INTSRC_NUM_142        
#define INTC_INTSRC_NUM_142                                     (142U)
#endif /* INTC_INTSRC_NUM_142 */
/* External interrupt source(SPI): INTID 277 - DMA3_CH_INT14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT14                                   (277U)
#ifndef INTC_INTSRC_NUM_277        
#define INTC_INTSRC_NUM_277                                     (277U)
#endif /* INTC_INTSRC_NUM_277 */
/* External interrupt source(SPI): INTID 278 - DMA3_CH_INT15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT15                                   (278U)
#ifndef INTC_INTSRC_NUM_278        
#define INTC_INTSRC_NUM_278                                     (278U)
#endif /* INTC_INTSRC_NUM_278 */
/* External interrupt source(SPI): INTID 279 - DMA3_CH_INT16 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT16                                   (279U)
#ifndef INTC_INTSRC_NUM_279        
#define INTC_INTSRC_NUM_279                                     (279U)
#endif /* INTC_INTSRC_NUM_279 */
/* External interrupt source(SPI): INTID 280 - DMA3_CH_INT17 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT17                                   (280U)
#ifndef INTC_INTSRC_NUM_280        
#define INTC_INTSRC_NUM_280                                     (280U)
#endif /* INTC_INTSRC_NUM_280 */
/* External interrupt source(SPI): INTID 281 - DMA3_CH_INT18 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT18                                   (281U)
#ifndef INTC_INTSRC_NUM_281        
#define INTC_INTSRC_NUM_281                                     (281U)
#endif /* INTC_INTSRC_NUM_281 */
/* External interrupt source(SPI): INTID 282 - DMA3_CH_INT19 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT19                                   (282U)
#ifndef INTC_INTSRC_NUM_282        
#define INTC_INTSRC_NUM_282                                     (282U)
#endif /* INTC_INTSRC_NUM_282 */
/* External interrupt source(SPI): INTID 283 - DMA3_CH_INT20 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT20                                   (283U)
#ifndef INTC_INTSRC_NUM_283        
#define INTC_INTSRC_NUM_283                                     (283U)
#endif /* INTC_INTSRC_NUM_283 */
/* External interrupt source(SPI): INTID 284 - DMA3_CH_INT21 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT21                                   (284U)
#ifndef INTC_INTSRC_NUM_284        
#define INTC_INTSRC_NUM_284                                     (284U)
#endif /* INTC_INTSRC_NUM_284 */
/* External interrupt source(SPI): INTID 285 - DMA3_CH_INT22 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT22                                   (285U)
#ifndef INTC_INTSRC_NUM_285        
#define INTC_INTSRC_NUM_285                                     (285U)
#endif /* INTC_INTSRC_NUM_285 */
/* External interrupt source(SPI): INTID 286 - DMA3_CH_INT23 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DMA3_CH_INT23                                   (286U)
#ifndef INTC_INTSRC_NUM_286        
#define INTC_INTSRC_NUM_286                                     (286U)
#endif /* INTC_INTSRC_NUM_286 */
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
/* External interrupt source(SPI): INTID 229 - PFLASH2_FINISH */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PFLASH2_FINISH                                   (229U)
#ifndef INTC_INTSRC_NUM_229        
#define INTC_INTSRC_NUM_229                                     (229U)
#endif /* INTC_INTSRC_NUM_229 */
/* External interrupt source(SPI): INTID 230 - PFLASH2_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PFLASH2_ERROR                                   (230U)
#ifndef INTC_INTSRC_NUM_230        
#define INTC_INTSRC_NUM_230                                     (230U)
#endif /* INTC_INTSRC_NUM_230 */
/* External interrupt source(SPI): INTID 231 - PFLASH3_FINISH */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PFLASH3_FINISH                                   (231U)
#ifndef INTC_INTSRC_NUM_231        
#define INTC_INTSRC_NUM_231                                     (231U)
#endif /* INTC_INTSRC_NUM_231 */
/* External interrupt source(SPI): INTID 232 - PFLASH3_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PFLASH3_ERROR                                   (232U)
#ifndef INTC_INTSRC_NUM_232        
#define INTC_INTSRC_NUM_232                                     (232U)
#endif /* INTC_INTSRC_NUM_232 */
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
/* External interrupt source(SPI): INTID 250 - BASETIM4_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_BASETIM4_INT                                   (250U)
#ifndef INTC_INTSRC_NUM_250        
#define INTC_INTSRC_NUM_250                                     (250U)
#endif /* INTC_INTSRC_NUM_250 */
/* External interrupt source(SPI): INTID 251 - BASETIM5_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_BASETIM5_INT                                   (251U)
#ifndef INTC_INTSRC_NUM_251        
#define INTC_INTSRC_NUM_251                                     (251U)
#endif /* INTC_INTSRC_NUM_251 */
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
/* External interrupt source(SPI): INTID 318 - CAN22_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN22_INT0                                   (318U)
#ifndef INTC_INTSRC_NUM_318        
#define INTC_INTSRC_NUM_318                                     (318U)
#endif /* INTC_INTSRC_NUM_318 */
/* External interrupt source(SPI): INTID 319 - CAN22_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN22_INT1                                   (319U)
#ifndef INTC_INTSRC_NUM_319        
#define INTC_INTSRC_NUM_319                                     (319U)
#endif /* INTC_INTSRC_NUM_319 */
/* External interrupt source(SPI): INTID 320 - CAN21_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN21_INT0                                   (320U)
#ifndef INTC_INTSRC_NUM_320        
#define INTC_INTSRC_NUM_320                                     (320U)
#endif /* INTC_INTSRC_NUM_320 */
/* External interrupt source(SPI): INTID 321 - CAN21_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN21_INT1                                   (321U)
#ifndef INTC_INTSRC_NUM_321        
#define INTC_INTSRC_NUM_321                                     (321U)
#endif /* INTC_INTSRC_NUM_321 */
/* External interrupt source(SPI): INTID 322 - CAN20_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN20_INT0                                   (322U)
#ifndef INTC_INTSRC_NUM_322        
#define INTC_INTSRC_NUM_322                                     (322U)
#endif /* INTC_INTSRC_NUM_322 */
/* External interrupt source(SPI): INTID 323 - CAN20_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN20_INT1                                   (323U)
#ifndef INTC_INTSRC_NUM_323        
#define INTC_INTSRC_NUM_323                                     (323U)
#endif /* INTC_INTSRC_NUM_323 */
/* External interrupt source(SPI): INTID 324 - CAN2_DMU0_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_DMU0_INT                                   (324U)
#ifndef INTC_INTSRC_NUM_324        
#define INTC_INTSRC_NUM_324                                     (324U)
#endif /* INTC_INTSRC_NUM_324 */
/* External interrupt source(SPI): INTID 325 - CAN2_DMU1_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_DMU1_INT                                   (325U)
#ifndef INTC_INTSRC_NUM_325        
#define INTC_INTSRC_NUM_325                                     (325U)
#endif /* INTC_INTSRC_NUM_325 */
/* External interrupt source(SPI): INTID 326 - CAN2_DMU2_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_DMU2_INT                                   (326U)
#ifndef INTC_INTSRC_NUM_326        
#define INTC_INTSRC_NUM_326                                     (326U)
#endif /* INTC_INTSRC_NUM_326 */
/* External interrupt source(SPI): INTID 327 - CAN2_ROUTE0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE0                                   (327U)
#ifndef INTC_INTSRC_NUM_327        
#define INTC_INTSRC_NUM_327                                     (327U)
#endif /* INTC_INTSRC_NUM_327 */
/* External interrupt source(SPI): INTID 328 - CAN2_ROUTE1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE1                                   (328U)
#ifndef INTC_INTSRC_NUM_328        
#define INTC_INTSRC_NUM_328                                     (328U)
#endif /* INTC_INTSRC_NUM_328 */
/* External interrupt source(SPI): INTID 329 - CAN2_ROUTE2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE2                                   (329U)
#ifndef INTC_INTSRC_NUM_329        
#define INTC_INTSRC_NUM_329                                     (329U)
#endif /* INTC_INTSRC_NUM_329 */
/* External interrupt source(SPI): INTID 330 - CAN2_ROUTE3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE3                                   (330U)
#ifndef INTC_INTSRC_NUM_330        
#define INTC_INTSRC_NUM_330                                     (330U)
#endif /* INTC_INTSRC_NUM_330 */
/* External interrupt source(SPI): INTID 331 - CAN2_ROUTE4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE4                                   (331U)
#ifndef INTC_INTSRC_NUM_331        
#define INTC_INTSRC_NUM_331                                     (331U)
#endif /* INTC_INTSRC_NUM_331 */
/* External interrupt source(SPI): INTID 332 - CAN2_ROUTE5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE5                                   (332U)
#ifndef INTC_INTSRC_NUM_332        
#define INTC_INTSRC_NUM_332                                     (332U)
#endif /* INTC_INTSRC_NUM_332 */
/* External interrupt source(SPI): INTID 333 - CAN2_ROUTE6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE6                                   (333U)
#ifndef INTC_INTSRC_NUM_333        
#define INTC_INTSRC_NUM_333                                     (333U)
#endif /* INTC_INTSRC_NUM_333 */
/* External interrupt source(SPI): INTID 334 - CAN2_ROUTE7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE7                                   (334U)
#ifndef INTC_INTSRC_NUM_334        
#define INTC_INTSRC_NUM_334                                     (334U)
#endif /* INTC_INTSRC_NUM_334 */
/* External interrupt source(SPI): INTID 335 - CAN2_ROUTE8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE8                                   (335U)
#ifndef INTC_INTSRC_NUM_335        
#define INTC_INTSRC_NUM_335                                     (335U)
#endif /* INTC_INTSRC_NUM_335 */
/* External interrupt source(SPI): INTID 336 - CAN2_ROUTE9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE9                                   (336U)
#ifndef INTC_INTSRC_NUM_336        
#define INTC_INTSRC_NUM_336                                     (336U)
#endif /* INTC_INTSRC_NUM_336 */
/* External interrupt source(SPI): INTID 337 - CAN2_ROUTE10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE10                                   (337U)
#ifndef INTC_INTSRC_NUM_337        
#define INTC_INTSRC_NUM_337                                     (337U)
#endif /* INTC_INTSRC_NUM_337 */
/* External interrupt source(SPI): INTID 338 - CAN2_ROUTE11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE11                                   (338U)
#ifndef INTC_INTSRC_NUM_338        
#define INTC_INTSRC_NUM_338                                     (338U)
#endif /* INTC_INTSRC_NUM_338 */
/* External interrupt source(SPI): INTID 339 - CAN2_ROUTE12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE12                                   (339U)
#ifndef INTC_INTSRC_NUM_339        
#define INTC_INTSRC_NUM_339                                     (339U)
#endif /* INTC_INTSRC_NUM_339 */
/* External interrupt source(SPI): INTID 340 - CAN2_ROUTE13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE13                                   (340U)
#ifndef INTC_INTSRC_NUM_340        
#define INTC_INTSRC_NUM_340                                     (340U)
#endif /* INTC_INTSRC_NUM_340 */
/* External interrupt source(SPI): INTID 341 - CAN2_ROUTE14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE14                                   (341U)
#ifndef INTC_INTSRC_NUM_341        
#define INTC_INTSRC_NUM_341                                     (341U)
#endif /* INTC_INTSRC_NUM_341 */
/* External interrupt source(SPI): INTID 342 - CAN2_ROUTE15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN2_ROUTE15                                   (342U)
#ifndef INTC_INTSRC_NUM_342        
#define INTC_INTSRC_NUM_342                                     (342U)
#endif /* INTC_INTSRC_NUM_342 */
/* External interrupt source(SPI): INTID 343 - CAN32_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN32_INT0                                   (343U)
#ifndef INTC_INTSRC_NUM_343        
#define INTC_INTSRC_NUM_343                                     (343U)
#endif /* INTC_INTSRC_NUM_343 */
/* External interrupt source(SPI): INTID 344 - CAN32_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN32_INT1                                   (344U)
#ifndef INTC_INTSRC_NUM_344        
#define INTC_INTSRC_NUM_344                                     (344U)
#endif /* INTC_INTSRC_NUM_344 */
/* External interrupt source(SPI): INTID 345 - CAN31_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN31_INT0                                   (345U)
#ifndef INTC_INTSRC_NUM_345        
#define INTC_INTSRC_NUM_345                                     (345U)
#endif /* INTC_INTSRC_NUM_345 */
/* External interrupt source(SPI): INTID 346 - CAN31_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN31_INT1                                   (346U)
#ifndef INTC_INTSRC_NUM_346        
#define INTC_INTSRC_NUM_346                                     (346U)
#endif /* INTC_INTSRC_NUM_346 */
/* External interrupt source(SPI): INTID 347 - CAN30_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN30_INT0                                   (347U)
#ifndef INTC_INTSRC_NUM_347        
#define INTC_INTSRC_NUM_347                                     (347U)
#endif /* INTC_INTSRC_NUM_347 */
/* External interrupt source(SPI): INTID 348 - CAN30_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN30_INT1                                   (348U)
#ifndef INTC_INTSRC_NUM_348        
#define INTC_INTSRC_NUM_348                                     (348U)
#endif /* INTC_INTSRC_NUM_348 */
/* External interrupt source(SPI): INTID 349 - CAN3_DMU0_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_DMU0_INT                                   (349U)
#ifndef INTC_INTSRC_NUM_349        
#define INTC_INTSRC_NUM_349                                     (349U)
#endif /* INTC_INTSRC_NUM_349 */
/* External interrupt source(SPI): INTID 350 - CAN3_DMU1_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_DMU1_INT                                   (350U)
#ifndef INTC_INTSRC_NUM_350        
#define INTC_INTSRC_NUM_350                                     (350U)
#endif /* INTC_INTSRC_NUM_350 */
/* External interrupt source(SPI): INTID 351 - CAN3_DMU2_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_DMU2_INT                                   (351U)
#ifndef INTC_INTSRC_NUM_351        
#define INTC_INTSRC_NUM_351                                     (351U)
#endif /* INTC_INTSRC_NUM_351 */
/* External interrupt source(SPI): INTID 352 - CAN3_ROUTE0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE0                                   (352U)
#ifndef INTC_INTSRC_NUM_352        
#define INTC_INTSRC_NUM_352                                     (352U)
#endif /* INTC_INTSRC_NUM_352 */
/* External interrupt source(SPI): INTID 353 - CAN3_ROUTE1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE1                                   (353U)
#ifndef INTC_INTSRC_NUM_353        
#define INTC_INTSRC_NUM_353                                     (353U)
#endif /* INTC_INTSRC_NUM_353 */
/* External interrupt source(SPI): INTID 354 - CAN3_ROUTE2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE2                                   (354U)
#ifndef INTC_INTSRC_NUM_354        
#define INTC_INTSRC_NUM_354                                     (354U)
#endif /* INTC_INTSRC_NUM_354 */
/* External interrupt source(SPI): INTID 355 - CAN3_ROUTE3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE3                                   (355U)
#ifndef INTC_INTSRC_NUM_355        
#define INTC_INTSRC_NUM_355                                     (355U)
#endif /* INTC_INTSRC_NUM_355 */
/* External interrupt source(SPI): INTID 356 - CAN3_ROUTE4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE4                                   (356U)
#ifndef INTC_INTSRC_NUM_356        
#define INTC_INTSRC_NUM_356                                     (356U)
#endif /* INTC_INTSRC_NUM_356 */
/* External interrupt source(SPI): INTID 357 - CAN3_ROUTE5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE5                                   (357U)
#ifndef INTC_INTSRC_NUM_357        
#define INTC_INTSRC_NUM_357                                     (357U)
#endif /* INTC_INTSRC_NUM_357 */
/* External interrupt source(SPI): INTID 358 - CAN3_ROUTE6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE6                                   (358U)
#ifndef INTC_INTSRC_NUM_358        
#define INTC_INTSRC_NUM_358                                     (358U)
#endif /* INTC_INTSRC_NUM_358 */
/* External interrupt source(SPI): INTID 359 - CAN3_ROUTE7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE7                                   (359U)
#ifndef INTC_INTSRC_NUM_359        
#define INTC_INTSRC_NUM_359                                     (359U)
#endif /* INTC_INTSRC_NUM_359 */
/* External interrupt source(SPI): INTID 360 - CAN3_ROUTE8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE8                                   (360U)
#ifndef INTC_INTSRC_NUM_360        
#define INTC_INTSRC_NUM_360                                     (360U)
#endif /* INTC_INTSRC_NUM_360 */
/* External interrupt source(SPI): INTID 361 - CAN3_ROUTE9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE9                                   (361U)
#ifndef INTC_INTSRC_NUM_361        
#define INTC_INTSRC_NUM_361                                     (361U)
#endif /* INTC_INTSRC_NUM_361 */
/* External interrupt source(SPI): INTID 362 - CAN3_ROUTE10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE10                                   (362U)
#ifndef INTC_INTSRC_NUM_362        
#define INTC_INTSRC_NUM_362                                     (362U)
#endif /* INTC_INTSRC_NUM_362 */
/* External interrupt source(SPI): INTID 363 - CAN3_ROUTE11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE11                                   (363U)
#ifndef INTC_INTSRC_NUM_363        
#define INTC_INTSRC_NUM_363                                     (363U)
#endif /* INTC_INTSRC_NUM_363 */
/* External interrupt source(SPI): INTID 364 - CAN3_ROUTE12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE12                                   (364U)
#ifndef INTC_INTSRC_NUM_364        
#define INTC_INTSRC_NUM_364                                     (364U)
#endif /* INTC_INTSRC_NUM_364 */
/* External interrupt source(SPI): INTID 365 - CAN3_ROUTE13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE13                                   (365U)
#ifndef INTC_INTSRC_NUM_365        
#define INTC_INTSRC_NUM_365                                     (365U)
#endif /* INTC_INTSRC_NUM_365 */
/* External interrupt source(SPI): INTID 366 - CAN3_ROUTE14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE14                                   (366U)
#ifndef INTC_INTSRC_NUM_366        
#define INTC_INTSRC_NUM_366                                     (366U)
#endif /* INTC_INTSRC_NUM_366 */
/* External interrupt source(SPI): INTID 367 - CAN3_ROUTE15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_CAN3_ROUTE15                                   (367U)
#ifndef INTC_INTSRC_NUM_367        
#define INTC_INTSRC_NUM_367                                     (367U)
#endif /* INTC_INTSRC_NUM_367 */
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
/* External interrupt source(SPI): INTID 413 - SARADC4_G3SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC4_G3SR0                                   (413U)
#ifndef INTC_INTSRC_NUM_413        
#define INTC_INTSRC_NUM_413                                     (413U)
#endif /* INTC_INTSRC_NUM_413 */
/* External interrupt source(SPI): INTID 414 - SARADC4_G3SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC4_G3SR1                                   (414U)
#ifndef INTC_INTSRC_NUM_414        
#define INTC_INTSRC_NUM_414                                     (414U)
#endif /* INTC_INTSRC_NUM_414 */
/* External interrupt source(SPI): INTID 415 - SARADC4_G3SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC4_G3SR2                                   (415U)
#ifndef INTC_INTSRC_NUM_415        
#define INTC_INTSRC_NUM_415                                     (415U)
#endif /* INTC_INTSRC_NUM_415 */
/* External interrupt source(SPI): INTID 416 - SARADC4_G3SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC4_G3SR3                                   (416U)
#ifndef INTC_INTSRC_NUM_416        
#define INTC_INTSRC_NUM_416                                     (416U)
#endif /* INTC_INTSRC_NUM_416 */
/* External interrupt source(SPI): INTID 417 - SARADC5_G3SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC5_G3SR0                                   (417U)
#ifndef INTC_INTSRC_NUM_417        
#define INTC_INTSRC_NUM_417                                     (417U)
#endif /* INTC_INTSRC_NUM_417 */
/* External interrupt source(SPI): INTID 418 - SARADC5_G3SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC5_G3SR1                                   (418U)
#ifndef INTC_INTSRC_NUM_418        
#define INTC_INTSRC_NUM_418                                     (418U)
#endif /* INTC_INTSRC_NUM_418 */
/* External interrupt source(SPI): INTID 419 - SARADC5_G3SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC5_G3SR2                                   (419U)
#ifndef INTC_INTSRC_NUM_419        
#define INTC_INTSRC_NUM_419                                     (419U)
#endif /* INTC_INTSRC_NUM_419 */
/* External interrupt source(SPI): INTID 420 - SARADC5_G3SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC5_G3SR3                                   (420U)
#ifndef INTC_INTSRC_NUM_420        
#define INTC_INTSRC_NUM_420                                     (420U)
#endif /* INTC_INTSRC_NUM_420 */
/* External interrupt source(SPI): INTID 421 - SARADC6_G3SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC6_G3SR0                                   (421U)
#ifndef INTC_INTSRC_NUM_421        
#define INTC_INTSRC_NUM_421                                     (421U)
#endif /* INTC_INTSRC_NUM_421 */
/* External interrupt source(SPI): INTID 422 - SARADC6_G3SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC6_G3SR1                                   (422U)
#ifndef INTC_INTSRC_NUM_422        
#define INTC_INTSRC_NUM_422                                     (422U)
#endif /* INTC_INTSRC_NUM_422 */
/* External interrupt source(SPI): INTID 423 - SARADC6_G3SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC6_G3SR2                                   (423U)
#ifndef INTC_INTSRC_NUM_423        
#define INTC_INTSRC_NUM_423                                     (423U)
#endif /* INTC_INTSRC_NUM_423 */
/* External interrupt source(SPI): INTID 424 - SARADC6_G3SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC6_G3SR3                                   (424U)
#ifndef INTC_INTSRC_NUM_424        
#define INTC_INTSRC_NUM_424                                     (424U)
#endif /* INTC_INTSRC_NUM_424 */
/* External interrupt source(SPI): INTID 381 - SARADC7_G3SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC7_G3SR0                                   (381U)
#ifndef INTC_INTSRC_NUM_381        
#define INTC_INTSRC_NUM_381                                     (381U)
#endif /* INTC_INTSRC_NUM_381 */
/* External interrupt source(SPI): INTID 382 - SARADC7_G3SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC7_G3SR1                                   (382U)
#ifndef INTC_INTSRC_NUM_382        
#define INTC_INTSRC_NUM_382                                     (382U)
#endif /* INTC_INTSRC_NUM_382 */
/* External interrupt source(SPI): INTID 387 - SARADC7_G3SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC7_G3SR2                                   (387U)
#ifndef INTC_INTSRC_NUM_387        
#define INTC_INTSRC_NUM_387                                     (387U)
#endif /* INTC_INTSRC_NUM_387 */
/* External interrupt source(SPI): INTID 388 - SARADC7_G3SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC7_G3SR3                                   (388U)
#ifndef INTC_INTSRC_NUM_388        
#define INTC_INTSRC_NUM_388                                     (388U)
#endif /* INTC_INTSRC_NUM_388 */
/* External interrupt source(SPI): INTID 401 - SARADC8_G3SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC8_G3SR0                                   (401U)
#ifndef INTC_INTSRC_NUM_401        
#define INTC_INTSRC_NUM_401                                     (401U)
#endif /* INTC_INTSRC_NUM_401 */
/* External interrupt source(SPI): INTID 402 - SARADC8_G3SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC8_G3SR1                                   (402U)
#ifndef INTC_INTSRC_NUM_402        
#define INTC_INTSRC_NUM_402                                     (402U)
#endif /* INTC_INTSRC_NUM_402 */
/* External interrupt source(SPI): INTID 403 - SARADC8_G3SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC8_G3SR2                                   (403U)
#ifndef INTC_INTSRC_NUM_403        
#define INTC_INTSRC_NUM_403                                     (403U)
#endif /* INTC_INTSRC_NUM_403 */
/* External interrupt source(SPI): INTID 404 - SARADC8_G3SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC8_G3SR3                                   (404U)
#ifndef INTC_INTSRC_NUM_404        
#define INTC_INTSRC_NUM_404                                     (404U)
#endif /* INTC_INTSRC_NUM_404 */
/* External interrupt source(SPI): INTID 407 - SARADC9_G3SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC9_G3SR0                                   (407U)
#ifndef INTC_INTSRC_NUM_407        
#define INTC_INTSRC_NUM_407                                     (407U)
#endif /* INTC_INTSRC_NUM_407 */
/* External interrupt source(SPI): INTID 408 - SARADC9_G3SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC9_G3SR1                                   (408U)
#ifndef INTC_INTSRC_NUM_408        
#define INTC_INTSRC_NUM_408                                     (408U)
#endif /* INTC_INTSRC_NUM_408 */
/* External interrupt source(SPI): INTID 409 - SARADC9_G3SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC9_G3SR2                                   (409U)
#ifndef INTC_INTSRC_NUM_409        
#define INTC_INTSRC_NUM_409                                     (409U)
#endif /* INTC_INTSRC_NUM_409 */
/* External interrupt source(SPI): INTID 410 - SARADC9_G3SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC9_G3SR3                                   (410U)
#ifndef INTC_INTSRC_NUM_410        
#define INTC_INTSRC_NUM_410                                     (410U)
#endif /* INTC_INTSRC_NUM_410 */
/* External interrupt source(SPI): INTID 393 - SARADC10_G3SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC10_G3SR0                                   (393U)
#ifndef INTC_INTSRC_NUM_393        
#define INTC_INTSRC_NUM_393                                     (393U)
#endif /* INTC_INTSRC_NUM_393 */
/* External interrupt source(SPI): INTID 394 - SARADC10_G3SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC10_G3SR1                                   (394U)
#ifndef INTC_INTSRC_NUM_394        
#define INTC_INTSRC_NUM_394                                     (394U)
#endif /* INTC_INTSRC_NUM_394 */
/* External interrupt source(SPI): INTID 399 - SARADC10_G3SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC10_G3SR2                                   (399U)
#ifndef INTC_INTSRC_NUM_399        
#define INTC_INTSRC_NUM_399                                     (399U)
#endif /* INTC_INTSRC_NUM_399 */
/* External interrupt source(SPI): INTID 400 - SARADC10_G3SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC10_G3SR3                                   (400U)
#ifndef INTC_INTSRC_NUM_400        
#define INTC_INTSRC_NUM_400                                     (400U)
#endif /* INTC_INTSRC_NUM_400 */
/* External interrupt source(SPI): INTID 405 - SARADC11_G3SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC11_G3SR0                                   (405U)
#ifndef INTC_INTSRC_NUM_405        
#define INTC_INTSRC_NUM_405                                     (405U)
#endif /* INTC_INTSRC_NUM_405 */
/* External interrupt source(SPI): INTID 406 - SARADC11_G3SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC11_G3SR1                                   (406U)
#ifndef INTC_INTSRC_NUM_406        
#define INTC_INTSRC_NUM_406                                     (406U)
#endif /* INTC_INTSRC_NUM_406 */
/* External interrupt source(SPI): INTID 411 - SARADC11_G3SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC11_G3SR2                                   (411U)
#ifndef INTC_INTSRC_NUM_411        
#define INTC_INTSRC_NUM_411                                     (411U)
#endif /* INTC_INTSRC_NUM_411 */
/* External interrupt source(SPI): INTID 412 - SARADC11_G3SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SARADC11_G3SR3                                   (412U)
#ifndef INTC_INTSRC_NUM_412        
#define INTC_INTSRC_NUM_412                                     (412U)
#endif /* INTC_INTSRC_NUM_412 */
/* External interrupt source(SPI): INTID 425 - FC0_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_FC0_INT                                   (425U)
#ifndef INTC_INTSRC_NUM_425        
#define INTC_INTSRC_NUM_425                                     (425U)
#endif /* INTC_INTSRC_NUM_425 */
/* External interrupt source(SPI): INTID 427 - FC1_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_FC1_INT                                   (427U)
#ifndef INTC_INTSRC_NUM_427        
#define INTC_INTSRC_NUM_427                                     (427U)
#endif /* INTC_INTSRC_NUM_427 */
/* External interrupt source(SPI): INTID 426 - FC2_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_FC2_INT                                   (426U)
#ifndef INTC_INTSRC_NUM_426        
#define INTC_INTSRC_NUM_426                                     (426U)
#endif /* INTC_INTSRC_NUM_426 */
/* External interrupt source(SPI): INTID 428 - FC3_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_FC3_INT                                   (428U)
#ifndef INTC_INTSRC_NUM_428        
#define INTC_INTSRC_NUM_428                                     (428U)
#endif /* INTC_INTSRC_NUM_428 */
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
/* External interrupt source(SPI): INTID 439 - DSADC0_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC0_SRA                                   (439U)
#ifndef INTC_INTSRC_NUM_439        
#define INTC_INTSRC_NUM_439                                     (439U)
#endif /* INTC_INTSRC_NUM_439 */
/* External interrupt source(SPI): INTID 440 - DSADC0_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC0_SRM                                   (440U)
#ifndef INTC_INTSRC_NUM_440        
#define INTC_INTSRC_NUM_440                                     (440U)
#endif /* INTC_INTSRC_NUM_440 */
/* External interrupt source(SPI): INTID 441 - DSADC1_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC1_SRA                                   (441U)
#ifndef INTC_INTSRC_NUM_441        
#define INTC_INTSRC_NUM_441                                     (441U)
#endif /* INTC_INTSRC_NUM_441 */
/* External interrupt source(SPI): INTID 442 - DSADC1_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC1_SRM                                   (442U)
#ifndef INTC_INTSRC_NUM_442        
#define INTC_INTSRC_NUM_442                                     (442U)
#endif /* INTC_INTSRC_NUM_442 */
/* External interrupt source(SPI): INTID 443 - DSADC2_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC2_SRA                                   (443U)
#ifndef INTC_INTSRC_NUM_443        
#define INTC_INTSRC_NUM_443                                     (443U)
#endif /* INTC_INTSRC_NUM_443 */
/* External interrupt source(SPI): INTID 444 - DSADC2_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC2_SRM                                   (444U)
#ifndef INTC_INTSRC_NUM_444        
#define INTC_INTSRC_NUM_444                                     (444U)
#endif /* INTC_INTSRC_NUM_444 */
/* External interrupt source(SPI): INTID 445 - DSADC3_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC3_SRA                                   (445U)
#ifndef INTC_INTSRC_NUM_445        
#define INTC_INTSRC_NUM_445                                     (445U)
#endif /* INTC_INTSRC_NUM_445 */
/* External interrupt source(SPI): INTID 446 - DSADC3_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC3_SRM                                   (446U)
#ifndef INTC_INTSRC_NUM_446        
#define INTC_INTSRC_NUM_446                                     (446U)
#endif /* INTC_INTSRC_NUM_446 */
/* External interrupt source(SPI): INTID 471 - DSADC4_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC4_SRA                                   (471U)
#ifndef INTC_INTSRC_NUM_471        
#define INTC_INTSRC_NUM_471                                     (471U)
#endif /* INTC_INTSRC_NUM_471 */
/* External interrupt source(SPI): INTID 472 - DSADC4_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC4_SRM                                   (472U)
#ifndef INTC_INTSRC_NUM_472        
#define INTC_INTSRC_NUM_472                                     (472U)
#endif /* INTC_INTSRC_NUM_472 */
/* External interrupt source(SPI): INTID 480 - DSADC5_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC5_SRA                                   (480U)
#ifndef INTC_INTSRC_NUM_480        
#define INTC_INTSRC_NUM_480                                     (480U)
#endif /* INTC_INTSRC_NUM_480 */
/* External interrupt source(SPI): INTID 481 - DSADC5_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC5_SRM                                   (481U)
#ifndef INTC_INTSRC_NUM_481        
#define INTC_INTSRC_NUM_481                                     (481U)
#endif /* INTC_INTSRC_NUM_481 */
/* External interrupt source(SPI): INTID 489 - DSADC6_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC6_SRA                                   (489U)
#ifndef INTC_INTSRC_NUM_489        
#define INTC_INTSRC_NUM_489                                     (489U)
#endif /* INTC_INTSRC_NUM_489 */
/* External interrupt source(SPI): INTID 490 - DSADC6_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC6_SRM                                   (490U)
#ifndef INTC_INTSRC_NUM_490        
#define INTC_INTSRC_NUM_490                                     (490U)
#endif /* INTC_INTSRC_NUM_490 */
/* External interrupt source(SPI): INTID 498 - DSADC7_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC7_SRA                                   (498U)
#ifndef INTC_INTSRC_NUM_498        
#define INTC_INTSRC_NUM_498                                     (498U)
#endif /* INTC_INTSRC_NUM_498 */
/* External interrupt source(SPI): INTID 499 - DSADC7_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC7_SRM                                   (499U)
#ifndef INTC_INTSRC_NUM_499        
#define INTC_INTSRC_NUM_499                                     (499U)
#endif /* INTC_INTSRC_NUM_499 */
/* External interrupt source(SPI): INTID 507 - DSADC8_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC8_SRA                                   (507U)
#ifndef INTC_INTSRC_NUM_507        
#define INTC_INTSRC_NUM_507                                     (507U)
#endif /* INTC_INTSRC_NUM_507 */
/* External interrupt source(SPI): INTID 508 - DSADC8_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC8_SRM                                   (508U)
#ifndef INTC_INTSRC_NUM_508        
#define INTC_INTSRC_NUM_508                                     (508U)
#endif /* INTC_INTSRC_NUM_508 */
/* External interrupt source(SPI): INTID 516 - DSADC9_SRA */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC9_SRA                                   (516U)
#ifndef INTC_INTSRC_NUM_516        
#define INTC_INTSRC_NUM_516                                     (516U)
#endif /* INTC_INTSRC_NUM_516 */
/* External interrupt source(SPI): INTID 517 - DSADC9_SRM */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_DSADC9_SRM                                   (517U)
#ifndef INTC_INTSRC_NUM_517        
#define INTC_INTSRC_NUM_517                                     (517U)
#endif /* INTC_INTSRC_NUM_517 */
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
/* External interrupt source(SPI): INTID 459 - PSI5INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_PSI5INT                                   (459U)
#ifndef INTC_INTSRC_NUM_459        
#define INTC_INTSRC_NUM_459                                     (459U)
#endif /* INTC_INTSRC_NUM_459 */
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
/* External interrupt source(SPI): INTID 518 - ESPI6_TX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI6_TX_INT                                   (518U)
#ifndef INTC_INTSRC_NUM_518        
#define INTC_INTSRC_NUM_518                                     (518U)
#endif /* INTC_INTSRC_NUM_518 */
/* External interrupt source(SPI): INTID 519 - ESPI6_RX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI6_RX_INT                                   (519U)
#ifndef INTC_INTSRC_NUM_519        
#define INTC_INTSRC_NUM_519                                     (519U)
#endif /* INTC_INTSRC_NUM_519 */
/* External interrupt source(SPI): INTID 520 - ESPI6_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI6_ERR_INT                                   (520U)
#ifndef INTC_INTSRC_NUM_520        
#define INTC_INTSRC_NUM_520                                     (520U)
#endif /* INTC_INTSRC_NUM_520 */
/* External interrupt source(SPI): INTID 521 - ESPI6_PT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI6_PT_INT                                   (521U)
#ifndef INTC_INTSRC_NUM_521        
#define INTC_INTSRC_NUM_521                                     (521U)
#endif /* INTC_INTSRC_NUM_521 */
/* External interrupt source(SPI): INTID 522 - ESPI6_U_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI6_U_INT                                   (522U)
#ifndef INTC_INTSRC_NUM_522        
#define INTC_INTSRC_NUM_522                                     (522U)
#endif /* INTC_INTSRC_NUM_522 */
/* External interrupt source(SPI): INTID 523 - ESPI6_HC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI6_HC_INT                                   (523U)
#ifndef INTC_INTSRC_NUM_523        
#define INTC_INTSRC_NUM_523                                     (523U)
#endif /* INTC_INTSRC_NUM_523 */
/* External interrupt source(SPI): INTID 524 - ESPI6_SEF_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI6_SEF_INT                                   (524U)
#ifndef INTC_INTSRC_NUM_524        
#define INTC_INTSRC_NUM_524                                     (524U)
#endif /* INTC_INTSRC_NUM_524 */
/* External interrupt source(SPI): INTID 527 - ESPI7_TX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI7_TX_INT                                   (527U)
#ifndef INTC_INTSRC_NUM_527        
#define INTC_INTSRC_NUM_527                                     (527U)
#endif /* INTC_INTSRC_NUM_527 */
/* External interrupt source(SPI): INTID 528 - ESPI7_RX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI7_RX_INT                                   (528U)
#ifndef INTC_INTSRC_NUM_528        
#define INTC_INTSRC_NUM_528                                     (528U)
#endif /* INTC_INTSRC_NUM_528 */
/* External interrupt source(SPI): INTID 529 - ESPI7_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI7_ERR_INT                                   (529U)
#ifndef INTC_INTSRC_NUM_529        
#define INTC_INTSRC_NUM_529                                     (529U)
#endif /* INTC_INTSRC_NUM_529 */
/* External interrupt source(SPI): INTID 530 - ESPI7_PT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI7_PT_INT                                   (530U)
#ifndef INTC_INTSRC_NUM_530        
#define INTC_INTSRC_NUM_530                                     (530U)
#endif /* INTC_INTSRC_NUM_530 */
/* External interrupt source(SPI): INTID 531 - ESPI7_U_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI7_U_INT                                   (531U)
#ifndef INTC_INTSRC_NUM_531        
#define INTC_INTSRC_NUM_531                                     (531U)
#endif /* INTC_INTSRC_NUM_531 */
/* External interrupt source(SPI): INTID 532 - ESPI7_HC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI7_HC_INT                                   (532U)
#ifndef INTC_INTSRC_NUM_532        
#define INTC_INTSRC_NUM_532                                     (532U)
#endif /* INTC_INTSRC_NUM_532 */
/* External interrupt source(SPI): INTID 533 - ESPI7_SEF_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI7_SEF_INT                                   (533U)
#ifndef INTC_INTSRC_NUM_533        
#define INTC_INTSRC_NUM_533                                     (533U)
#endif /* INTC_INTSRC_NUM_533 */
/* External interrupt source(SPI): INTID 536 - ESPI8_TX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI8_TX_INT                                   (536U)
#ifndef INTC_INTSRC_NUM_536        
#define INTC_INTSRC_NUM_536                                     (536U)
#endif /* INTC_INTSRC_NUM_536 */
/* External interrupt source(SPI): INTID 537 - ESPI8_RX_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI8_RX_INT                                   (537U)
#ifndef INTC_INTSRC_NUM_537        
#define INTC_INTSRC_NUM_537                                     (537U)
#endif /* INTC_INTSRC_NUM_537 */
/* External interrupt source(SPI): INTID 538 - ESPI8_ERR_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI8_ERR_INT                                   (538U)
#ifndef INTC_INTSRC_NUM_538        
#define INTC_INTSRC_NUM_538                                     (538U)
#endif /* INTC_INTSRC_NUM_538 */
/* External interrupt source(SPI): INTID 539 - ESPI8_PT_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI8_PT_INT                                   (539U)
#ifndef INTC_INTSRC_NUM_539        
#define INTC_INTSRC_NUM_539                                     (539U)
#endif /* INTC_INTSRC_NUM_539 */
/* External interrupt source(SPI): INTID 540 - ESPI8_U_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI8_U_INT                                   (540U)
#ifndef INTC_INTSRC_NUM_540        
#define INTC_INTSRC_NUM_540                                     (540U)
#endif /* INTC_INTSRC_NUM_540 */
/* External interrupt source(SPI): INTID 541 - ESPI8_HC_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI8_HC_INT                                   (541U)
#ifndef INTC_INTSRC_NUM_541        
#define INTC_INTSRC_NUM_541                                     (541U)
#endif /* INTC_INTSRC_NUM_541 */
/* External interrupt source(SPI): INTID 542 - ESPI8_SEF_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ESPI8_SEF_INT                                   (542U)
#ifndef INTC_INTSRC_NUM_542        
#define INTC_INTSRC_NUM_542                                     (542U)
#endif /* INTC_INTSRC_NUM_542 */
/* External interrupt source(SPI): INTID 552 - MSC0_SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC0_SR0                                   (552U)
#ifndef INTC_INTSRC_NUM_552        
#define INTC_INTSRC_NUM_552                                     (552U)
#endif /* INTC_INTSRC_NUM_552 */
/* External interrupt source(SPI): INTID 553 - MSC0_SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC0_SR1                                   (553U)
#ifndef INTC_INTSRC_NUM_553        
#define INTC_INTSRC_NUM_553                                     (553U)
#endif /* INTC_INTSRC_NUM_553 */
/* External interrupt source(SPI): INTID 554 - MSC0_SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC0_SR2                                   (554U)
#ifndef INTC_INTSRC_NUM_554        
#define INTC_INTSRC_NUM_554                                     (554U)
#endif /* INTC_INTSRC_NUM_554 */
/* External interrupt source(SPI): INTID 555 - MSC0_SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC0_SR3                                   (555U)
#ifndef INTC_INTSRC_NUM_555        
#define INTC_INTSRC_NUM_555                                     (555U)
#endif /* INTC_INTSRC_NUM_555 */
/* External interrupt source(SPI): INTID 556 - MSC0_SR4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC0_SR4                                   (556U)
#ifndef INTC_INTSRC_NUM_556        
#define INTC_INTSRC_NUM_556                                     (556U)
#endif /* INTC_INTSRC_NUM_556 */
/* External interrupt source(SPI): INTID 557 - MSC1_SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC1_SR0                                   (557U)
#ifndef INTC_INTSRC_NUM_557        
#define INTC_INTSRC_NUM_557                                     (557U)
#endif /* INTC_INTSRC_NUM_557 */
/* External interrupt source(SPI): INTID 558 - MSC1_SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC1_SR1                                   (558U)
#ifndef INTC_INTSRC_NUM_558        
#define INTC_INTSRC_NUM_558                                     (558U)
#endif /* INTC_INTSRC_NUM_558 */
/* External interrupt source(SPI): INTID 559 - MSC1_SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC1_SR2                                   (559U)
#ifndef INTC_INTSRC_NUM_559        
#define INTC_INTSRC_NUM_559                                     (559U)
#endif /* INTC_INTSRC_NUM_559 */
/* External interrupt source(SPI): INTID 560 - MSC1_SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC1_SR3                                   (560U)
#ifndef INTC_INTSRC_NUM_560        
#define INTC_INTSRC_NUM_560                                     (560U)
#endif /* INTC_INTSRC_NUM_560 */
/* External interrupt source(SPI): INTID 561 - MSC1_SR4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC1_SR4                                   (561U)
#ifndef INTC_INTSRC_NUM_561        
#define INTC_INTSRC_NUM_561                                     (561U)
#endif /* INTC_INTSRC_NUM_561 */
/* External interrupt source(SPI): INTID 562 - MSC2_SR0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC2_SR0                                   (562U)
#ifndef INTC_INTSRC_NUM_562        
#define INTC_INTSRC_NUM_562                                     (562U)
#endif /* INTC_INTSRC_NUM_562 */
/* External interrupt source(SPI): INTID 563 - MSC2_SR1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC2_SR1                                   (563U)
#ifndef INTC_INTSRC_NUM_563        
#define INTC_INTSRC_NUM_563                                     (563U)
#endif /* INTC_INTSRC_NUM_563 */
/* External interrupt source(SPI): INTID 564 - MSC2_SR2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC2_SR2                                   (564U)
#ifndef INTC_INTSRC_NUM_564        
#define INTC_INTSRC_NUM_564                                     (564U)
#endif /* INTC_INTSRC_NUM_564 */
/* External interrupt source(SPI): INTID 565 - MSC2_SR3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC2_SR3                                   (565U)
#ifndef INTC_INTSRC_NUM_565        
#define INTC_INTSRC_NUM_565                                     (565U)
#endif /* INTC_INTSRC_NUM_565 */
/* External interrupt source(SPI): INTID 566 - MSC2_SR4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_MSC2_SR4                                   (566U)
#ifndef INTC_INTSRC_NUM_566        
#define INTC_INTSRC_NUM_566                                     (566U)
#endif /* INTC_INTSRC_NUM_566 */
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
/* External interrupt source(SPI): INTID 596 - SENT6_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT6_RX_ERROR                                   (596U)
#ifndef INTC_INTSRC_NUM_596        
#define INTC_INTSRC_NUM_596                                     (596U)
#endif /* INTC_INTSRC_NUM_596 */
/* External interrupt source(SPI): INTID 597 - SENT6_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT6_RX_VALID                                   (597U)
#ifndef INTC_INTSRC_NUM_597        
#define INTC_INTSRC_NUM_597                                     (597U)
#endif /* INTC_INTSRC_NUM_597 */
/* External interrupt source(SPI): INTID 600 - SENT7_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT7_RX_ERROR                                   (600U)
#ifndef INTC_INTSRC_NUM_600        
#define INTC_INTSRC_NUM_600                                     (600U)
#endif /* INTC_INTSRC_NUM_600 */
/* External interrupt source(SPI): INTID 601 - SENT7_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT7_RX_VALID                                   (601U)
#ifndef INTC_INTSRC_NUM_601        
#define INTC_INTSRC_NUM_601                                     (601U)
#endif /* INTC_INTSRC_NUM_601 */
/* External interrupt source(SPI): INTID 604 - SENT8_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT8_RX_ERROR                                   (604U)
#ifndef INTC_INTSRC_NUM_604        
#define INTC_INTSRC_NUM_604                                     (604U)
#endif /* INTC_INTSRC_NUM_604 */
/* External interrupt source(SPI): INTID 605 - SENT8_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT8_RX_VALID                                   (605U)
#ifndef INTC_INTSRC_NUM_605        
#define INTC_INTSRC_NUM_605                                     (605U)
#endif /* INTC_INTSRC_NUM_605 */
/* External interrupt source(SPI): INTID 608 - SENT9_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT9_RX_ERROR                                   (608U)
#ifndef INTC_INTSRC_NUM_608        
#define INTC_INTSRC_NUM_608                                     (608U)
#endif /* INTC_INTSRC_NUM_608 */
/* External interrupt source(SPI): INTID 609 - SENT9_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT9_RX_VALID                                   (609U)
#ifndef INTC_INTSRC_NUM_609        
#define INTC_INTSRC_NUM_609                                     (609U)
#endif /* INTC_INTSRC_NUM_609 */
/* External interrupt source(SPI): INTID 610 - SENT10_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT10_RX_ERROR                                   (610U)
#ifndef INTC_INTSRC_NUM_610        
#define INTC_INTSRC_NUM_610                                     (610U)
#endif /* INTC_INTSRC_NUM_610 */
/* External interrupt source(SPI): INTID 611 - SENT10_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT10_RX_VALID                                   (611U)
#ifndef INTC_INTSRC_NUM_611        
#define INTC_INTSRC_NUM_611                                     (611U)
#endif /* INTC_INTSRC_NUM_611 */
/* External interrupt source(SPI): INTID 612 - SENT11_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT11_RX_ERROR                                   (612U)
#ifndef INTC_INTSRC_NUM_612        
#define INTC_INTSRC_NUM_612                                     (612U)
#endif /* INTC_INTSRC_NUM_612 */
/* External interrupt source(SPI): INTID 613 - SENT11_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT11_RX_VALID                                   (613U)
#ifndef INTC_INTSRC_NUM_613        
#define INTC_INTSRC_NUM_613                                     (613U)
#endif /* INTC_INTSRC_NUM_613 */
/* External interrupt source(SPI): INTID 614 - SENT12_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT12_RX_ERROR                                   (614U)
#ifndef INTC_INTSRC_NUM_614        
#define INTC_INTSRC_NUM_614                                     (614U)
#endif /* INTC_INTSRC_NUM_614 */
/* External interrupt source(SPI): INTID 615 - SENT12_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT12_RX_VALID                                   (615U)
#ifndef INTC_INTSRC_NUM_615        
#define INTC_INTSRC_NUM_615                                     (615U)
#endif /* INTC_INTSRC_NUM_615 */
/* External interrupt source(SPI): INTID 616 - SENT13_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT13_RX_ERROR                                   (616U)
#ifndef INTC_INTSRC_NUM_616        
#define INTC_INTSRC_NUM_616                                     (616U)
#endif /* INTC_INTSRC_NUM_616 */
/* External interrupt source(SPI): INTID 617 - SENT13_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT13_RX_VALID                                   (617U)
#ifndef INTC_INTSRC_NUM_617        
#define INTC_INTSRC_NUM_617                                     (617U)
#endif /* INTC_INTSRC_NUM_617 */
/* External interrupt source(SPI): INTID 618 - SENT14_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT14_RX_ERROR                                   (618U)
#ifndef INTC_INTSRC_NUM_618        
#define INTC_INTSRC_NUM_618                                     (618U)
#endif /* INTC_INTSRC_NUM_618 */
/* External interrupt source(SPI): INTID 619 - SENT14_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT14_RX_VALID                                   (619U)
#ifndef INTC_INTSRC_NUM_619        
#define INTC_INTSRC_NUM_619                                     (619U)
#endif /* INTC_INTSRC_NUM_619 */
/* External interrupt source(SPI): INTID 620 - SENT15_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT15_RX_ERROR                                   (620U)
#ifndef INTC_INTSRC_NUM_620        
#define INTC_INTSRC_NUM_620                                     (620U)
#endif /* INTC_INTSRC_NUM_620 */
/* External interrupt source(SPI): INTID 621 - SENT15_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT15_RX_VALID                                   (621U)
#ifndef INTC_INTSRC_NUM_621        
#define INTC_INTSRC_NUM_621                                     (621U)
#endif /* INTC_INTSRC_NUM_621 */
/* External interrupt source(SPI): INTID 574 - SENT16_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT16_RX_ERROR                                   (574U)
#ifndef INTC_INTSRC_NUM_574        
#define INTC_INTSRC_NUM_574                                     (574U)
#endif /* INTC_INTSRC_NUM_574 */
/* External interrupt source(SPI): INTID 575 - SENT16_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT16_RX_VALID                                   (575U)
#ifndef INTC_INTSRC_NUM_575        
#define INTC_INTSRC_NUM_575                                     (575U)
#endif /* INTC_INTSRC_NUM_575 */
/* External interrupt source(SPI): INTID 578 - SENT17_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT17_RX_ERROR                                   (578U)
#ifndef INTC_INTSRC_NUM_578        
#define INTC_INTSRC_NUM_578                                     (578U)
#endif /* INTC_INTSRC_NUM_578 */
/* External interrupt source(SPI): INTID 579 - SENT17_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT17_RX_VALID                                   (579U)
#ifndef INTC_INTSRC_NUM_579        
#define INTC_INTSRC_NUM_579                                     (579U)
#endif /* INTC_INTSRC_NUM_579 */
/* External interrupt source(SPI): INTID 582 - SENT18_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT18_RX_ERROR                                   (582U)
#ifndef INTC_INTSRC_NUM_582        
#define INTC_INTSRC_NUM_582                                     (582U)
#endif /* INTC_INTSRC_NUM_582 */
/* External interrupt source(SPI): INTID 583 - SENT18_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT18_RX_VALID                                   (583U)
#ifndef INTC_INTSRC_NUM_583        
#define INTC_INTSRC_NUM_583                                     (583U)
#endif /* INTC_INTSRC_NUM_583 */
/* External interrupt source(SPI): INTID 586 - SENT19_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT19_RX_ERROR                                   (586U)
#ifndef INTC_INTSRC_NUM_586        
#define INTC_INTSRC_NUM_586                                     (586U)
#endif /* INTC_INTSRC_NUM_586 */
/* External interrupt source(SPI): INTID 587 - SENT19_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT19_RX_VALID                                   (587U)
#ifndef INTC_INTSRC_NUM_587        
#define INTC_INTSRC_NUM_587                                     (587U)
#endif /* INTC_INTSRC_NUM_587 */
/* External interrupt source(SPI): INTID 590 - SENT20_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT20_RX_ERROR                                   (590U)
#ifndef INTC_INTSRC_NUM_590        
#define INTC_INTSRC_NUM_590                                     (590U)
#endif /* INTC_INTSRC_NUM_590 */
/* External interrupt source(SPI): INTID 591 - SENT20_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT20_RX_VALID                                   (591U)
#ifndef INTC_INTSRC_NUM_591        
#define INTC_INTSRC_NUM_591                                     (591U)
#endif /* INTC_INTSRC_NUM_591 */
/* External interrupt source(SPI): INTID 594 - SENT21_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT21_RX_ERROR                                   (594U)
#ifndef INTC_INTSRC_NUM_594        
#define INTC_INTSRC_NUM_594                                     (594U)
#endif /* INTC_INTSRC_NUM_594 */
/* External interrupt source(SPI): INTID 595 - SENT21_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT21_RX_VALID                                   (595U)
#ifndef INTC_INTSRC_NUM_595        
#define INTC_INTSRC_NUM_595                                     (595U)
#endif /* INTC_INTSRC_NUM_595 */
/* External interrupt source(SPI): INTID 598 - SENT22_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT22_RX_ERROR                                   (598U)
#ifndef INTC_INTSRC_NUM_598        
#define INTC_INTSRC_NUM_598                                     (598U)
#endif /* INTC_INTSRC_NUM_598 */
/* External interrupt source(SPI): INTID 599 - SENT22_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT22_RX_VALID                                   (599U)
#ifndef INTC_INTSRC_NUM_599        
#define INTC_INTSRC_NUM_599                                     (599U)
#endif /* INTC_INTSRC_NUM_599 */
/* External interrupt source(SPI): INTID 602 - SENT23_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT23_RX_ERROR                                   (602U)
#ifndef INTC_INTSRC_NUM_602        
#define INTC_INTSRC_NUM_602                                     (602U)
#endif /* INTC_INTSRC_NUM_602 */
/* External interrupt source(SPI): INTID 603 - SENT23_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT23_RX_VALID                                   (603U)
#ifndef INTC_INTSRC_NUM_603        
#define INTC_INTSRC_NUM_603                                     (603U)
#endif /* INTC_INTSRC_NUM_603 */
/* External interrupt source(SPI): INTID 606 - SENT24_RX_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT24_RX_ERROR                                   (606U)
#ifndef INTC_INTSRC_NUM_606        
#define INTC_INTSRC_NUM_606                                     (606U)
#endif /* INTC_INTSRC_NUM_606 */
/* External interrupt source(SPI): INTID 607 - SENT24_RX_VALID */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_SENT24_RX_VALID                                   (607U)
#ifndef INTC_INTSRC_NUM_607        
#define INTC_INTSRC_NUM_607                                     (607U)
#endif /* INTC_INTSRC_NUM_607 */
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
/* External interrupt source(SPI): INTID 630 - QSPI0_INTERRUPT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_QSPI0_INTERRUPT                                   (630U)
#ifndef INTC_INTSRC_NUM_630        
#define INTC_INTSRC_NUM_630                                     (630U)
#endif /* INTC_INTSRC_NUM_630 */
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
/* External interrupt source(SPI): INTID 289 - ASI12_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI12_RX                                   (289U)
#ifndef INTC_INTSRC_NUM_289        
#define INTC_INTSRC_NUM_289                                     (289U)
#endif /* INTC_INTSRC_NUM_289 */
/* External interrupt source(SPI): INTID 290 - ASI12_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI12_TX                                   (290U)
#ifndef INTC_INTSRC_NUM_290        
#define INTC_INTSRC_NUM_290                                     (290U)
#endif /* INTC_INTSRC_NUM_290 */
/* External interrupt source(SPI): INTID 291 - ASI12_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI12_ERROR                                   (291U)
#ifndef INTC_INTSRC_NUM_291        
#define INTC_INTSRC_NUM_291                                     (291U)
#endif /* INTC_INTSRC_NUM_291 */
/* External interrupt source(SPI): INTID 292 - ASI12_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI12_ALL                                   (292U)
#ifndef INTC_INTSRC_NUM_292        
#define INTC_INTSRC_NUM_292                                     (292U)
#endif /* INTC_INTSRC_NUM_292 */
/* External interrupt source(SPI): INTID 368 - ASI13_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI13_RX                                   (368U)
#ifndef INTC_INTSRC_NUM_368        
#define INTC_INTSRC_NUM_368                                     (368U)
#endif /* INTC_INTSRC_NUM_368 */
/* External interrupt source(SPI): INTID 369 - ASI13_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI13_TX                                   (369U)
#ifndef INTC_INTSRC_NUM_369        
#define INTC_INTSRC_NUM_369                                     (369U)
#endif /* INTC_INTSRC_NUM_369 */
/* External interrupt source(SPI): INTID 370 - ASI13_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI13_ERROR                                   (370U)
#ifndef INTC_INTSRC_NUM_370        
#define INTC_INTSRC_NUM_370                                     (370U)
#endif /* INTC_INTSRC_NUM_370 */
/* External interrupt source(SPI): INTID 371 - ASI13_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI13_ALL                                   (371U)
#ifndef INTC_INTSRC_NUM_371        
#define INTC_INTSRC_NUM_371                                     (371U)
#endif /* INTC_INTSRC_NUM_371 */
/* External interrupt source(SPI): INTID 372 - ASI14_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI14_RX                                   (372U)
#ifndef INTC_INTSRC_NUM_372        
#define INTC_INTSRC_NUM_372                                     (372U)
#endif /* INTC_INTSRC_NUM_372 */
/* External interrupt source(SPI): INTID 373 - ASI14_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI14_TX                                   (373U)
#ifndef INTC_INTSRC_NUM_373        
#define INTC_INTSRC_NUM_373                                     (373U)
#endif /* INTC_INTSRC_NUM_373 */
/* External interrupt source(SPI): INTID 374 - ASI14_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI14_ERROR                                   (374U)
#ifndef INTC_INTSRC_NUM_374        
#define INTC_INTSRC_NUM_374                                     (374U)
#endif /* INTC_INTSRC_NUM_374 */
/* External interrupt source(SPI): INTID 375 - ASI14_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI14_ALL                                   (375U)
#ifndef INTC_INTSRC_NUM_375        
#define INTC_INTSRC_NUM_375                                     (375U)
#endif /* INTC_INTSRC_NUM_375 */
/* External interrupt source(SPI): INTID 429 - ASI15_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI15_RX                                   (429U)
#ifndef INTC_INTSRC_NUM_429        
#define INTC_INTSRC_NUM_429                                     (429U)
#endif /* INTC_INTSRC_NUM_429 */
/* External interrupt source(SPI): INTID 430 - ASI15_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI15_TX                                   (430U)
#ifndef INTC_INTSRC_NUM_430        
#define INTC_INTSRC_NUM_430                                     (430U)
#endif /* INTC_INTSRC_NUM_430 */
/* External interrupt source(SPI): INTID 655 - ASI15_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI15_ERROR                                   (655U)
#ifndef INTC_INTSRC_NUM_655        
#define INTC_INTSRC_NUM_655                                     (655U)
#endif /* INTC_INTSRC_NUM_655 */
/* External interrupt source(SPI): INTID 660 - ASI15_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI15_ALL                                   (660U)
#ifndef INTC_INTSRC_NUM_660        
#define INTC_INTSRC_NUM_660                                     (660U)
#endif /* INTC_INTSRC_NUM_660 */
/* External interrupt source(SPI): INTID 447 - ASI16_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI16_RX                                   (447U)
#ifndef INTC_INTSRC_NUM_447        
#define INTC_INTSRC_NUM_447                                     (447U)
#endif /* INTC_INTSRC_NUM_447 */
/* External interrupt source(SPI): INTID 448 - ASI16_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI16_TX                                   (448U)
#ifndef INTC_INTSRC_NUM_448        
#define INTC_INTSRC_NUM_448                                     (448U)
#endif /* INTC_INTSRC_NUM_448 */
/* External interrupt source(SPI): INTID 449 - ASI16_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI16_ERROR                                   (449U)
#ifndef INTC_INTSRC_NUM_449        
#define INTC_INTSRC_NUM_449                                     (449U)
#endif /* INTC_INTSRC_NUM_449 */
/* External interrupt source(SPI): INTID 450 - ASI16_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI16_ALL                                   (450U)
#ifndef INTC_INTSRC_NUM_450        
#define INTC_INTSRC_NUM_450                                     (450U)
#endif /* INTC_INTSRC_NUM_450 */
/* External interrupt source(SPI): INTID 451 - ASI17_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI17_RX                                   (451U)
#ifndef INTC_INTSRC_NUM_451        
#define INTC_INTSRC_NUM_451                                     (451U)
#endif /* INTC_INTSRC_NUM_451 */
/* External interrupt source(SPI): INTID 452 - ASI17_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI17_TX                                   (452U)
#ifndef INTC_INTSRC_NUM_452        
#define INTC_INTSRC_NUM_452                                     (452U)
#endif /* INTC_INTSRC_NUM_452 */
/* External interrupt source(SPI): INTID 453 - ASI17_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI17_ERROR                                   (453U)
#ifndef INTC_INTSRC_NUM_453        
#define INTC_INTSRC_NUM_453                                     (453U)
#endif /* INTC_INTSRC_NUM_453 */
/* External interrupt source(SPI): INTID 454 - ASI17_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI17_ALL                                   (454U)
#ifndef INTC_INTSRC_NUM_454        
#define INTC_INTSRC_NUM_454                                     (454U)
#endif /* INTC_INTSRC_NUM_454 */
/* External interrupt source(SPI): INTID 543 - ASI18_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI18_RX                                   (543U)
#ifndef INTC_INTSRC_NUM_543        
#define INTC_INTSRC_NUM_543                                     (543U)
#endif /* INTC_INTSRC_NUM_543 */
/* External interrupt source(SPI): INTID 544 - ASI18_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI18_TX                                   (544U)
#ifndef INTC_INTSRC_NUM_544        
#define INTC_INTSRC_NUM_544                                     (544U)
#endif /* INTC_INTSRC_NUM_544 */
/* External interrupt source(SPI): INTID 545 - ASI18_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI18_ERROR                                   (545U)
#ifndef INTC_INTSRC_NUM_545        
#define INTC_INTSRC_NUM_545                                     (545U)
#endif /* INTC_INTSRC_NUM_545 */
/* External interrupt source(SPI): INTID 546 - ASI18_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI18_ALL                                   (546U)
#ifndef INTC_INTSRC_NUM_546        
#define INTC_INTSRC_NUM_546                                     (546U)
#endif /* INTC_INTSRC_NUM_546 */
/* External interrupt source(SPI): INTID 547 - ASI19_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI19_RX                                   (547U)
#ifndef INTC_INTSRC_NUM_547        
#define INTC_INTSRC_NUM_547                                     (547U)
#endif /* INTC_INTSRC_NUM_547 */
/* External interrupt source(SPI): INTID 548 - ASI19_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI19_TX                                   (548U)
#ifndef INTC_INTSRC_NUM_548        
#define INTC_INTSRC_NUM_548                                     (548U)
#endif /* INTC_INTSRC_NUM_548 */
/* External interrupt source(SPI): INTID 549 - ASI19_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI19_ERROR                                   (549U)
#ifndef INTC_INTSRC_NUM_549        
#define INTC_INTSRC_NUM_549                                     (549U)
#endif /* INTC_INTSRC_NUM_549 */
/* External interrupt source(SPI): INTID 550 - ASI19_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI19_ALL                                   (550U)
#ifndef INTC_INTSRC_NUM_550        
#define INTC_INTSRC_NUM_550                                     (550U)
#endif /* INTC_INTSRC_NUM_550 */
/* External interrupt source(SPI): INTID 567 - ASI20_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI20_RX                                   (567U)
#ifndef INTC_INTSRC_NUM_567        
#define INTC_INTSRC_NUM_567                                     (567U)
#endif /* INTC_INTSRC_NUM_567 */
/* External interrupt source(SPI): INTID 568 - ASI20_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI20_TX                                   (568U)
#ifndef INTC_INTSRC_NUM_568        
#define INTC_INTSRC_NUM_568                                     (568U)
#endif /* INTC_INTSRC_NUM_568 */
/* External interrupt source(SPI): INTID 569 - ASI20_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI20_ERROR                                   (569U)
#ifndef INTC_INTSRC_NUM_569        
#define INTC_INTSRC_NUM_569                                     (569U)
#endif /* INTC_INTSRC_NUM_569 */
/* External interrupt source(SPI): INTID 570 - ASI20_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI20_ALL                                   (570U)
#ifndef INTC_INTSRC_NUM_570        
#define INTC_INTSRC_NUM_570                                     (570U)
#endif /* INTC_INTSRC_NUM_570 */
/* External interrupt source(SPI): INTID 626 - ASI21_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI21_RX                                   (626U)
#ifndef INTC_INTSRC_NUM_626        
#define INTC_INTSRC_NUM_626                                     (626U)
#endif /* INTC_INTSRC_NUM_626 */
/* External interrupt source(SPI): INTID 627 - ASI21_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI21_TX                                   (627U)
#ifndef INTC_INTSRC_NUM_627        
#define INTC_INTSRC_NUM_627                                     (627U)
#endif /* INTC_INTSRC_NUM_627 */
/* External interrupt source(SPI): INTID 628 - ASI21_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI21_ERROR                                   (628U)
#ifndef INTC_INTSRC_NUM_628        
#define INTC_INTSRC_NUM_628                                     (628U)
#endif /* INTC_INTSRC_NUM_628 */
/* External interrupt source(SPI): INTID 629 - ASI21_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI21_ALL                                   (629U)
#ifndef INTC_INTSRC_NUM_629        
#define INTC_INTSRC_NUM_629                                     (629U)
#endif /* INTC_INTSRC_NUM_629 */
/* External interrupt source(SPI): INTID 679 - ASI22_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI22_RX                                   (679U)
#ifndef INTC_INTSRC_NUM_679        
#define INTC_INTSRC_NUM_679                                     (679U)
#endif /* INTC_INTSRC_NUM_679 */
/* External interrupt source(SPI): INTID 680 - ASI22_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI22_TX                                   (680U)
#ifndef INTC_INTSRC_NUM_680        
#define INTC_INTSRC_NUM_680                                     (680U)
#endif /* INTC_INTSRC_NUM_680 */
/* External interrupt source(SPI): INTID 681 - ASI22_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI22_ERROR                                   (681U)
#ifndef INTC_INTSRC_NUM_681        
#define INTC_INTSRC_NUM_681                                     (681U)
#endif /* INTC_INTSRC_NUM_681 */
/* External interrupt source(SPI): INTID 682 - ASI22_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI22_ALL                                   (682U)
#ifndef INTC_INTSRC_NUM_682        
#define INTC_INTSRC_NUM_682                                     (682U)
#endif /* INTC_INTSRC_NUM_682 */
/* External interrupt source(SPI): INTID 683 - ASI23_RX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI23_RX                                   (683U)
#ifndef INTC_INTSRC_NUM_683        
#define INTC_INTSRC_NUM_683                                     (683U)
#endif /* INTC_INTSRC_NUM_683 */
/* External interrupt source(SPI): INTID 684 - ASI23_TX */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI23_TX                                   (684U)
#ifndef INTC_INTSRC_NUM_684        
#define INTC_INTSRC_NUM_684                                     (684U)
#endif /* INTC_INTSRC_NUM_684 */
/* External interrupt source(SPI): INTID 685 - ASI23_ERROR */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI23_ERROR                                   (685U)
#ifndef INTC_INTSRC_NUM_685        
#define INTC_INTSRC_NUM_685                                     (685U)
#endif /* INTC_INTSRC_NUM_685 */
/* External interrupt source(SPI): INTID 686 - ASI23_ALL */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_ASI23_ALL                                   (686U)
#ifndef INTC_INTSRC_NUM_686        
#define INTC_INTSRC_NUM_686                                     (686U)
#endif /* INTC_INTSRC_NUM_686 */
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
/* External interrupt source(SPI): INTID 66 - GTM_MCS5_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS5_INT5                                   (66U)
#ifndef INTC_INTSRC_NUM_66        
#define INTC_INTSRC_NUM_66                                     (66U)
#endif /* INTC_INTSRC_NUM_66 */
/* External interrupt source(SPI): INTID 67 - GTM_MCS5_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS5_INT6                                   (67U)
#ifndef INTC_INTSRC_NUM_67        
#define INTC_INTSRC_NUM_67                                     (67U)
#endif /* INTC_INTSRC_NUM_67 */
/* External interrupt source(SPI): INTID 82 - GTM_MCS5_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS5_INT7                                   (82U)
#ifndef INTC_INTSRC_NUM_82        
#define INTC_INTSRC_NUM_82                                     (82U)
#endif /* INTC_INTSRC_NUM_82 */
/* External interrupt source(SPI): INTID 83 - GTM_MCS6_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS6_INT0                                   (83U)
#ifndef INTC_INTSRC_NUM_83        
#define INTC_INTSRC_NUM_83                                     (83U)
#endif /* INTC_INTSRC_NUM_83 */
/* External interrupt source(SPI): INTID 84 - GTM_MCS6_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS6_INT1                                   (84U)
#ifndef INTC_INTSRC_NUM_84        
#define INTC_INTSRC_NUM_84                                     (84U)
#endif /* INTC_INTSRC_NUM_84 */
/* External interrupt source(SPI): INTID 85 - GTM_MCS6_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS6_INT2                                   (85U)
#ifndef INTC_INTSRC_NUM_85        
#define INTC_INTSRC_NUM_85                                     (85U)
#endif /* INTC_INTSRC_NUM_85 */
/* External interrupt source(SPI): INTID 86 - GTM_MCS6_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS6_INT3                                   (86U)
#ifndef INTC_INTSRC_NUM_86        
#define INTC_INTSRC_NUM_86                                     (86U)
#endif /* INTC_INTSRC_NUM_86 */
/* External interrupt source(SPI): INTID 87 - GTM_MCS6_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS6_INT4                                   (87U)
#ifndef INTC_INTSRC_NUM_87        
#define INTC_INTSRC_NUM_87                                     (87U)
#endif /* INTC_INTSRC_NUM_87 */
/* External interrupt source(SPI): INTID 88 - GTM_MCS6_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS6_INT5                                   (88U)
#ifndef INTC_INTSRC_NUM_88        
#define INTC_INTSRC_NUM_88                                     (88U)
#endif /* INTC_INTSRC_NUM_88 */
/* External interrupt source(SPI): INTID 233 - GTM_MCS6_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS6_INT6                                   (233U)
#ifndef INTC_INTSRC_NUM_233        
#define INTC_INTSRC_NUM_233                                     (233U)
#endif /* INTC_INTSRC_NUM_233 */
/* External interrupt source(SPI): INTID 241 - GTM_MCS6_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS6_INT7                                   (241U)
#ifndef INTC_INTSRC_NUM_241        
#define INTC_INTSRC_NUM_241                                     (241U)
#endif /* INTC_INTSRC_NUM_241 */
/* External interrupt source(SPI): INTID 376 - GTM_MCS7_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS7_INT0                                   (376U)
#ifndef INTC_INTSRC_NUM_376        
#define INTC_INTSRC_NUM_376                                     (376U)
#endif /* INTC_INTSRC_NUM_376 */
/* External interrupt source(SPI): INTID 456 - GTM_MCS7_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS7_INT1                                   (456U)
#ifndef INTC_INTSRC_NUM_456        
#define INTC_INTSRC_NUM_456                                     (456U)
#endif /* INTC_INTSRC_NUM_456 */
/* External interrupt source(SPI): INTID 458 - GTM_MCS7_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS7_INT2                                   (458U)
#ifndef INTC_INTSRC_NUM_458        
#define INTC_INTSRC_NUM_458                                     (458U)
#endif /* INTC_INTSRC_NUM_458 */
/* External interrupt source(SPI): INTID 525 - GTM_MCS7_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS7_INT3                                   (525U)
#ifndef INTC_INTSRC_NUM_525        
#define INTC_INTSRC_NUM_525                                     (525U)
#endif /* INTC_INTSRC_NUM_525 */
/* External interrupt source(SPI): INTID 526 - GTM_MCS7_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS7_INT4                                   (526U)
#ifndef INTC_INTSRC_NUM_526        
#define INTC_INTSRC_NUM_526                                     (526U)
#endif /* INTC_INTSRC_NUM_526 */
/* External interrupt source(SPI): INTID 534 - GTM_MCS7_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS7_INT5                                   (534U)
#ifndef INTC_INTSRC_NUM_534        
#define INTC_INTSRC_NUM_534                                     (534U)
#endif /* INTC_INTSRC_NUM_534 */
/* External interrupt source(SPI): INTID 535 - GTM_MCS7_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS7_INT6                                   (535U)
#ifndef INTC_INTSRC_NUM_535        
#define INTC_INTSRC_NUM_535                                     (535U)
#endif /* INTC_INTSRC_NUM_535 */
/* External interrupt source(SPI): INTID 551 - GTM_MCS7_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS7_INT7                                   (551U)
#ifndef INTC_INTSRC_NUM_551        
#define INTC_INTSRC_NUM_551                                     (551U)
#endif /* INTC_INTSRC_NUM_551 */
/* External interrupt source(SPI): INTID 571 - GTM_MCS4_S_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS4_S_INT                                   (571U)
#ifndef INTC_INTSRC_NUM_571        
#define INTC_INTSRC_NUM_571                                     (571U)
#endif /* INTC_INTSRC_NUM_571 */
/* External interrupt source(SPI): INTID 635 - GTM_MCS5_S_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS5_S_INT                                   (635U)
#ifndef INTC_INTSRC_NUM_635        
#define INTC_INTSRC_NUM_635                                     (635U)
#endif /* INTC_INTSRC_NUM_635 */
/* External interrupt source(SPI): INTID 640 - GTM_MCS6_S_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS6_S_INT                                   (640U)
#ifndef INTC_INTSRC_NUM_640        
#define INTC_INTSRC_NUM_640                                     (640U)
#endif /* INTC_INTSRC_NUM_640 */
/* External interrupt source(SPI): INTID 645 - GTM_MCS7_S_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS7_S_INT                                   (645U)
#ifndef INTC_INTSRC_NUM_645        
#define INTC_INTSRC_NUM_645                                     (645U)
#endif /* INTC_INTSRC_NUM_645 */
/* External interrupt source(SPI): INTID 650 - GTM_MCSW_S_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCSW_S_INT                                   (650U)
#ifndef INTC_INTSRC_NUM_650        
#define INTC_INTSRC_NUM_650                                     (650U)
#endif /* INTC_INTSRC_NUM_650 */
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
/* External interrupt source(SPI): INTID 696 - GTM_SPE2_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_SPE2_INT                                   (696U)
#ifndef INTC_INTSRC_NUM_696        
#define INTC_INTSRC_NUM_696                                     (696U)
#endif /* INTC_INTSRC_NUM_696 */
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
/* External interrupt source(SPI): INTID 705 - GTM_PSM1_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM1_INT0                                   (705U)
#ifndef INTC_INTSRC_NUM_705        
#define INTC_INTSRC_NUM_705                                     (705U)
#endif /* INTC_INTSRC_NUM_705 */
/* External interrupt source(SPI): INTID 706 - GTM_PSM1_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM1_INT1                                   (706U)
#ifndef INTC_INTSRC_NUM_706        
#define INTC_INTSRC_NUM_706                                     (706U)
#endif /* INTC_INTSRC_NUM_706 */
/* External interrupt source(SPI): INTID 707 - GTM_PSM1_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM1_INT2                                   (707U)
#ifndef INTC_INTSRC_NUM_707        
#define INTC_INTSRC_NUM_707                                     (707U)
#endif /* INTC_INTSRC_NUM_707 */
/* External interrupt source(SPI): INTID 708 - GTM_PSM1_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM1_INT3                                   (708U)
#ifndef INTC_INTSRC_NUM_708        
#define INTC_INTSRC_NUM_708                                     (708U)
#endif /* INTC_INTSRC_NUM_708 */
/* External interrupt source(SPI): INTID 709 - GTM_PSM1_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM1_INT4                                   (709U)
#ifndef INTC_INTSRC_NUM_709        
#define INTC_INTSRC_NUM_709                                     (709U)
#endif /* INTC_INTSRC_NUM_709 */
/* External interrupt source(SPI): INTID 710 - GTM_PSM1_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM1_INT5                                   (710U)
#ifndef INTC_INTSRC_NUM_710        
#define INTC_INTSRC_NUM_710                                     (710U)
#endif /* INTC_INTSRC_NUM_710 */
/* External interrupt source(SPI): INTID 711 - GTM_PSM1_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM1_INT6                                   (711U)
#ifndef INTC_INTSRC_NUM_711        
#define INTC_INTSRC_NUM_711                                     (711U)
#endif /* INTC_INTSRC_NUM_711 */
/* External interrupt source(SPI): INTID 712 - GTM_PSM1_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM1_INT7                                   (712U)
#ifndef INTC_INTSRC_NUM_712        
#define INTC_INTSRC_NUM_712                                     (712U)
#endif /* INTC_INTSRC_NUM_712 */
/* External interrupt source(SPI): INTID 713 - GTM_PSM2_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM2_INT0                                   (713U)
#ifndef INTC_INTSRC_NUM_713        
#define INTC_INTSRC_NUM_713                                     (713U)
#endif /* INTC_INTSRC_NUM_713 */
/* External interrupt source(SPI): INTID 714 - GTM_PSM2_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM2_INT1                                   (714U)
#ifndef INTC_INTSRC_NUM_714        
#define INTC_INTSRC_NUM_714                                     (714U)
#endif /* INTC_INTSRC_NUM_714 */
/* External interrupt source(SPI): INTID 715 - GTM_PSM2_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM2_INT2                                   (715U)
#ifndef INTC_INTSRC_NUM_715        
#define INTC_INTSRC_NUM_715                                     (715U)
#endif /* INTC_INTSRC_NUM_715 */
/* External interrupt source(SPI): INTID 716 - GTM_PSM2_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM2_INT3                                   (716U)
#ifndef INTC_INTSRC_NUM_716        
#define INTC_INTSRC_NUM_716                                     (716U)
#endif /* INTC_INTSRC_NUM_716 */
/* External interrupt source(SPI): INTID 717 - GTM_PSM2_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM2_INT4                                   (717U)
#ifndef INTC_INTSRC_NUM_717        
#define INTC_INTSRC_NUM_717                                     (717U)
#endif /* INTC_INTSRC_NUM_717 */
/* External interrupt source(SPI): INTID 718 - GTM_PSM2_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM2_INT5                                   (718U)
#ifndef INTC_INTSRC_NUM_718        
#define INTC_INTSRC_NUM_718                                     (718U)
#endif /* INTC_INTSRC_NUM_718 */
/* External interrupt source(SPI): INTID 719 - GTM_PSM2_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM2_INT6                                   (719U)
#ifndef INTC_INTSRC_NUM_719        
#define INTC_INTSRC_NUM_719                                     (719U)
#endif /* INTC_INTSRC_NUM_719 */
/* External interrupt source(SPI): INTID 720 - GTM_PSM2_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_PSM2_INT7                                   (720U)
#ifndef INTC_INTSRC_NUM_720        
#define INTC_INTSRC_NUM_720                                     (720U)
#endif /* INTC_INTSRC_NUM_720 */
/* External interrupt source(SPI): INTID 721 - GTM_DPLL_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT0                                   (721U)
#ifndef INTC_INTSRC_NUM_721        
#define INTC_INTSRC_NUM_721                                     (721U)
#endif /* INTC_INTSRC_NUM_721 */
/* External interrupt source(SPI): INTID 722 - GTM_DPLL_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT1                                   (722U)
#ifndef INTC_INTSRC_NUM_722        
#define INTC_INTSRC_NUM_722                                     (722U)
#endif /* INTC_INTSRC_NUM_722 */
/* External interrupt source(SPI): INTID 723 - GTM_DPLL_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT2                                   (723U)
#ifndef INTC_INTSRC_NUM_723        
#define INTC_INTSRC_NUM_723                                     (723U)
#endif /* INTC_INTSRC_NUM_723 */
/* External interrupt source(SPI): INTID 724 - GTM_DPLL_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT3                                   (724U)
#ifndef INTC_INTSRC_NUM_724        
#define INTC_INTSRC_NUM_724                                     (724U)
#endif /* INTC_INTSRC_NUM_724 */
/* External interrupt source(SPI): INTID 725 - GTM_DPLL_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT4                                   (725U)
#ifndef INTC_INTSRC_NUM_725        
#define INTC_INTSRC_NUM_725                                     (725U)
#endif /* INTC_INTSRC_NUM_725 */
/* External interrupt source(SPI): INTID 726 - GTM_DPLL_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT5                                   (726U)
#ifndef INTC_INTSRC_NUM_726        
#define INTC_INTSRC_NUM_726                                     (726U)
#endif /* INTC_INTSRC_NUM_726 */
/* External interrupt source(SPI): INTID 727 - GTM_DPLL_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT6                                   (727U)
#ifndef INTC_INTSRC_NUM_727        
#define INTC_INTSRC_NUM_727                                     (727U)
#endif /* INTC_INTSRC_NUM_727 */
/* External interrupt source(SPI): INTID 728 - GTM_DPLL_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT7                                   (728U)
#ifndef INTC_INTSRC_NUM_728        
#define INTC_INTSRC_NUM_728                                     (728U)
#endif /* INTC_INTSRC_NUM_728 */
/* External interrupt source(SPI): INTID 729 - GTM_DPLL_INT8 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT8                                   (729U)
#ifndef INTC_INTSRC_NUM_729        
#define INTC_INTSRC_NUM_729                                     (729U)
#endif /* INTC_INTSRC_NUM_729 */
/* External interrupt source(SPI): INTID 730 - GTM_DPLL_INT9 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT9                                   (730U)
#ifndef INTC_INTSRC_NUM_730        
#define INTC_INTSRC_NUM_730                                     (730U)
#endif /* INTC_INTSRC_NUM_730 */
/* External interrupt source(SPI): INTID 731 - GTM_DPLL_INT10 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT10                                   (731U)
#ifndef INTC_INTSRC_NUM_731        
#define INTC_INTSRC_NUM_731                                     (731U)
#endif /* INTC_INTSRC_NUM_731 */
/* External interrupt source(SPI): INTID 732 - GTM_DPLL_INT11 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT11                                   (732U)
#ifndef INTC_INTSRC_NUM_732        
#define INTC_INTSRC_NUM_732                                     (732U)
#endif /* INTC_INTSRC_NUM_732 */
/* External interrupt source(SPI): INTID 733 - GTM_DPLL_INT12 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT12                                   (733U)
#ifndef INTC_INTSRC_NUM_733        
#define INTC_INTSRC_NUM_733                                     (733U)
#endif /* INTC_INTSRC_NUM_733 */
/* External interrupt source(SPI): INTID 734 - GTM_DPLL_INT13 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT13                                   (734U)
#ifndef INTC_INTSRC_NUM_734        
#define INTC_INTSRC_NUM_734                                     (734U)
#endif /* INTC_INTSRC_NUM_734 */
/* External interrupt source(SPI): INTID 735 - GTM_DPLL_INT14 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT14                                   (735U)
#ifndef INTC_INTSRC_NUM_735        
#define INTC_INTSRC_NUM_735                                     (735U)
#endif /* INTC_INTSRC_NUM_735 */
/* External interrupt source(SPI): INTID 736 - GTM_DPLL_INT15 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT15                                   (736U)
#ifndef INTC_INTSRC_NUM_736        
#define INTC_INTSRC_NUM_736                                     (736U)
#endif /* INTC_INTSRC_NUM_736 */
/* External interrupt source(SPI): INTID 737 - GTM_DPLL_INT16 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT16                                   (737U)
#ifndef INTC_INTSRC_NUM_737        
#define INTC_INTSRC_NUM_737                                     (737U)
#endif /* INTC_INTSRC_NUM_737 */
/* External interrupt source(SPI): INTID 738 - GTM_DPLL_INT17 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT17                                   (738U)
#ifndef INTC_INTSRC_NUM_738        
#define INTC_INTSRC_NUM_738                                     (738U)
#endif /* INTC_INTSRC_NUM_738 */
/* External interrupt source(SPI): INTID 739 - GTM_DPLL_INT18 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT18                                   (739U)
#ifndef INTC_INTSRC_NUM_739        
#define INTC_INTSRC_NUM_739                                     (739U)
#endif /* INTC_INTSRC_NUM_739 */
/* External interrupt source(SPI): INTID 740 - GTM_DPLL_INT19 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT19                                   (740U)
#ifndef INTC_INTSRC_NUM_740        
#define INTC_INTSRC_NUM_740                                     (740U)
#endif /* INTC_INTSRC_NUM_740 */
/* External interrupt source(SPI): INTID 741 - GTM_DPLL_INT20 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT20                                   (741U)
#ifndef INTC_INTSRC_NUM_741        
#define INTC_INTSRC_NUM_741                                     (741U)
#endif /* INTC_INTSRC_NUM_741 */
/* External interrupt source(SPI): INTID 742 - GTM_DPLL_INT21 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT21                                   (742U)
#ifndef INTC_INTSRC_NUM_742        
#define INTC_INTSRC_NUM_742                                     (742U)
#endif /* INTC_INTSRC_NUM_742 */
/* External interrupt source(SPI): INTID 743 - GTM_DPLL_INT22 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT22                                   (743U)
#ifndef INTC_INTSRC_NUM_743        
#define INTC_INTSRC_NUM_743                                     (743U)
#endif /* INTC_INTSRC_NUM_743 */
/* External interrupt source(SPI): INTID 744 - GTM_DPLL_INT23 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT23                                   (744U)
#ifndef INTC_INTSRC_NUM_744        
#define INTC_INTSRC_NUM_744                                     (744U)
#endif /* INTC_INTSRC_NUM_744 */
/* External interrupt source(SPI): INTID 745 - GTM_DPLL_INT24 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT24                                   (745U)
#ifndef INTC_INTSRC_NUM_745        
#define INTC_INTSRC_NUM_745                                     (745U)
#endif /* INTC_INTSRC_NUM_745 */
/* External interrupt source(SPI): INTID 746 - GTM_DPLL_INT25 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT25                                   (746U)
#ifndef INTC_INTSRC_NUM_746        
#define INTC_INTSRC_NUM_746                                     (746U)
#endif /* INTC_INTSRC_NUM_746 */
/* External interrupt source(SPI): INTID 747 - GTM_DPLL_INT26 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_DPLL_INT26                                   (747U)
#ifndef INTC_INTSRC_NUM_747        
#define INTC_INTSRC_NUM_747                                     (747U)
#endif /* INTC_INTSRC_NUM_747 */
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
/* External interrupt source(SPI): INTID 764 - GTM_TIM2_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM2_INT0                                   (764U)
#ifndef INTC_INTSRC_NUM_764        
#define INTC_INTSRC_NUM_764                                     (764U)
#endif /* INTC_INTSRC_NUM_764 */
/* External interrupt source(SPI): INTID 765 - GTM_TIM2_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM2_INT1                                   (765U)
#ifndef INTC_INTSRC_NUM_765        
#define INTC_INTSRC_NUM_765                                     (765U)
#endif /* INTC_INTSRC_NUM_765 */
/* External interrupt source(SPI): INTID 766 - GTM_TIM2_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM2_INT2                                   (766U)
#ifndef INTC_INTSRC_NUM_766        
#define INTC_INTSRC_NUM_766                                     (766U)
#endif /* INTC_INTSRC_NUM_766 */
/* External interrupt source(SPI): INTID 767 - GTM_TIM2_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM2_INT3                                   (767U)
#ifndef INTC_INTSRC_NUM_767        
#define INTC_INTSRC_NUM_767                                     (767U)
#endif /* INTC_INTSRC_NUM_767 */
/* External interrupt source(SPI): INTID 768 - GTM_TIM2_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM2_INT4                                   (768U)
#ifndef INTC_INTSRC_NUM_768        
#define INTC_INTSRC_NUM_768                                     (768U)
#endif /* INTC_INTSRC_NUM_768 */
/* External interrupt source(SPI): INTID 769 - GTM_TIM2_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM2_INT5                                   (769U)
#ifndef INTC_INTSRC_NUM_769        
#define INTC_INTSRC_NUM_769                                     (769U)
#endif /* INTC_INTSRC_NUM_769 */
/* External interrupt source(SPI): INTID 770 - GTM_TIM2_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM2_INT6                                   (770U)
#ifndef INTC_INTSRC_NUM_770        
#define INTC_INTSRC_NUM_770                                     (770U)
#endif /* INTC_INTSRC_NUM_770 */
/* External interrupt source(SPI): INTID 771 - GTM_TIM2_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM2_INT7                                   (771U)
#ifndef INTC_INTSRC_NUM_771        
#define INTC_INTSRC_NUM_771                                     (771U)
#endif /* INTC_INTSRC_NUM_771 */
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
/* External interrupt source(SPI): INTID 788 - GTM_TOM2_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM2_INT0                                   (788U)
#ifndef INTC_INTSRC_NUM_788        
#define INTC_INTSRC_NUM_788                                     (788U)
#endif /* INTC_INTSRC_NUM_788 */
/* External interrupt source(SPI): INTID 789 - GTM_TOM2_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM2_INT1                                   (789U)
#ifndef INTC_INTSRC_NUM_789        
#define INTC_INTSRC_NUM_789                                     (789U)
#endif /* INTC_INTSRC_NUM_789 */
/* External interrupt source(SPI): INTID 790 - GTM_TOM2_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM2_INT2                                   (790U)
#ifndef INTC_INTSRC_NUM_790        
#define INTC_INTSRC_NUM_790                                     (790U)
#endif /* INTC_INTSRC_NUM_790 */
/* External interrupt source(SPI): INTID 791 - GTM_TOM2_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM2_INT3                                   (791U)
#ifndef INTC_INTSRC_NUM_791        
#define INTC_INTSRC_NUM_791                                     (791U)
#endif /* INTC_INTSRC_NUM_791 */
/* External interrupt source(SPI): INTID 792 - GTM_TOM2_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM2_INT4                                   (792U)
#ifndef INTC_INTSRC_NUM_792        
#define INTC_INTSRC_NUM_792                                     (792U)
#endif /* INTC_INTSRC_NUM_792 */
/* External interrupt source(SPI): INTID 793 - GTM_TOM2_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM2_INT5                                   (793U)
#ifndef INTC_INTSRC_NUM_793        
#define INTC_INTSRC_NUM_793                                     (793U)
#endif /* INTC_INTSRC_NUM_793 */
/* External interrupt source(SPI): INTID 794 - GTM_TOM2_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM2_INT6                                   (794U)
#ifndef INTC_INTSRC_NUM_794        
#define INTC_INTSRC_NUM_794                                     (794U)
#endif /* INTC_INTSRC_NUM_794 */
/* External interrupt source(SPI): INTID 795 - GTM_TOM2_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM2_INT7                                   (795U)
#ifndef INTC_INTSRC_NUM_795        
#define INTC_INTSRC_NUM_795                                     (795U)
#endif /* INTC_INTSRC_NUM_795 */
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
/* External interrupt source(SPI): INTID 800 - GTM_ATOM1_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM1_INT0                                   (800U)
#ifndef INTC_INTSRC_NUM_800        
#define INTC_INTSRC_NUM_800                                     (800U)
#endif /* INTC_INTSRC_NUM_800 */
/* External interrupt source(SPI): INTID 801 - GTM_ATOM1_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM1_INT1                                   (801U)
#ifndef INTC_INTSRC_NUM_801        
#define INTC_INTSRC_NUM_801                                     (801U)
#endif /* INTC_INTSRC_NUM_801 */
/* External interrupt source(SPI): INTID 802 - GTM_ATOM1_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM1_INT2                                   (802U)
#ifndef INTC_INTSRC_NUM_802        
#define INTC_INTSRC_NUM_802                                     (802U)
#endif /* INTC_INTSRC_NUM_802 */
/* External interrupt source(SPI): INTID 803 - GTM_ATOM1_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM1_INT3                                   (803U)
#ifndef INTC_INTSRC_NUM_803        
#define INTC_INTSRC_NUM_803                                     (803U)
#endif /* INTC_INTSRC_NUM_803 */
/* External interrupt source(SPI): INTID 804 - GTM_ATOM2_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM2_INT0                                   (804U)
#ifndef INTC_INTSRC_NUM_804        
#define INTC_INTSRC_NUM_804                                     (804U)
#endif /* INTC_INTSRC_NUM_804 */
/* External interrupt source(SPI): INTID 805 - GTM_ATOM2_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM2_INT1                                   (805U)
#ifndef INTC_INTSRC_NUM_805        
#define INTC_INTSRC_NUM_805                                     (805U)
#endif /* INTC_INTSRC_NUM_805 */
/* External interrupt source(SPI): INTID 806 - GTM_ATOM2_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM2_INT2                                   (806U)
#ifndef INTC_INTSRC_NUM_806        
#define INTC_INTSRC_NUM_806                                     (806U)
#endif /* INTC_INTSRC_NUM_806 */
/* External interrupt source(SPI): INTID 807 - GTM_ATOM2_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM2_INT3                                   (807U)
#ifndef INTC_INTSRC_NUM_807        
#define INTC_INTSRC_NUM_807                                     (807U)
#endif /* INTC_INTSRC_NUM_807 */
/* External interrupt source(SPI): INTID 808 - GTM_ATOM3_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM3_INT0                                   (808U)
#ifndef INTC_INTSRC_NUM_808        
#define INTC_INTSRC_NUM_808                                     (808U)
#endif /* INTC_INTSRC_NUM_808 */
/* External interrupt source(SPI): INTID 809 - GTM_ATOM3_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM3_INT1                                   (809U)
#ifndef INTC_INTSRC_NUM_809        
#define INTC_INTSRC_NUM_809                                     (809U)
#endif /* INTC_INTSRC_NUM_809 */
/* External interrupt source(SPI): INTID 810 - GTM_ATOM3_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM3_INT2                                   (810U)
#ifndef INTC_INTSRC_NUM_810        
#define INTC_INTSRC_NUM_810                                     (810U)
#endif /* INTC_INTSRC_NUM_810 */
/* External interrupt source(SPI): INTID 811 - GTM_ATOM3_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM3_INT3                                   (811U)
#ifndef INTC_INTSRC_NUM_811        
#define INTC_INTSRC_NUM_811                                     (811U)
#endif /* INTC_INTSRC_NUM_811 */
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
/* External interrupt source(SPI): INTID 820 - GTM_TIO2_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO2_INT0                                   (820U)
#ifndef INTC_INTSRC_NUM_820        
#define INTC_INTSRC_NUM_820                                     (820U)
#endif /* INTC_INTSRC_NUM_820 */
/* External interrupt source(SPI): INTID 821 - GTM_TIO2_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO2_INT1                                   (821U)
#ifndef INTC_INTSRC_NUM_821        
#define INTC_INTSRC_NUM_821                                     (821U)
#endif /* INTC_INTSRC_NUM_821 */
/* External interrupt source(SPI): INTID 822 - GTM_TIO2_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO2_INT2                                   (822U)
#ifndef INTC_INTSRC_NUM_822        
#define INTC_INTSRC_NUM_822                                     (822U)
#endif /* INTC_INTSRC_NUM_822 */
/* External interrupt source(SPI): INTID 823 - GTM_TIO2_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO2_INT3                                   (823U)
#ifndef INTC_INTSRC_NUM_823        
#define INTC_INTSRC_NUM_823                                     (823U)
#endif /* INTC_INTSRC_NUM_823 */
/* External interrupt source(SPI): INTID 824 - GTM_TIO2_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO2_INT4                                   (824U)
#ifndef INTC_INTSRC_NUM_824        
#define INTC_INTSRC_NUM_824                                     (824U)
#endif /* INTC_INTSRC_NUM_824 */
/* External interrupt source(SPI): INTID 825 - GTM_TIO2_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO2_INT5                                   (825U)
#ifndef INTC_INTSRC_NUM_825        
#define INTC_INTSRC_NUM_825                                     (825U)
#endif /* INTC_INTSRC_NUM_825 */
/* External interrupt source(SPI): INTID 826 - GTM_TIO2_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO2_INT6                                   (826U)
#ifndef INTC_INTSRC_NUM_826        
#define INTC_INTSRC_NUM_826                                     (826U)
#endif /* INTC_INTSRC_NUM_826 */
/* External interrupt source(SPI): INTID 827 - GTM_TIO2_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO2_INT7                                   (827U)
#ifndef INTC_INTSRC_NUM_827        
#define INTC_INTSRC_NUM_827                                     (827U)
#endif /* INTC_INTSRC_NUM_827 */
/* External interrupt source(SPI): INTID 828 - GTM_TIO3_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO3_INT0                                   (828U)
#ifndef INTC_INTSRC_NUM_828        
#define INTC_INTSRC_NUM_828                                     (828U)
#endif /* INTC_INTSRC_NUM_828 */
/* External interrupt source(SPI): INTID 829 - GTM_TIO3_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO3_INT1                                   (829U)
#ifndef INTC_INTSRC_NUM_829        
#define INTC_INTSRC_NUM_829                                     (829U)
#endif /* INTC_INTSRC_NUM_829 */
/* External interrupt source(SPI): INTID 830 - GTM_TIO3_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO3_INT2                                   (830U)
#ifndef INTC_INTSRC_NUM_830        
#define INTC_INTSRC_NUM_830                                     (830U)
#endif /* INTC_INTSRC_NUM_830 */
/* External interrupt source(SPI): INTID 831 - GTM_TIO3_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO3_INT3                                   (831U)
#ifndef INTC_INTSRC_NUM_831        
#define INTC_INTSRC_NUM_831                                     (831U)
#endif /* INTC_INTSRC_NUM_831 */
/* External interrupt source(SPI): INTID 832 - GTM_TIO3_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO3_INT4                                   (832U)
#ifndef INTC_INTSRC_NUM_832        
#define INTC_INTSRC_NUM_832                                     (832U)
#endif /* INTC_INTSRC_NUM_832 */
/* External interrupt source(SPI): INTID 833 - GTM_TIO3_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO3_INT5                                   (833U)
#ifndef INTC_INTSRC_NUM_833        
#define INTC_INTSRC_NUM_833                                     (833U)
#endif /* INTC_INTSRC_NUM_833 */
/* External interrupt source(SPI): INTID 834 - GTM_TIO3_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO3_INT6                                   (834U)
#ifndef INTC_INTSRC_NUM_834        
#define INTC_INTSRC_NUM_834                                     (834U)
#endif /* INTC_INTSRC_NUM_834 */
/* External interrupt source(SPI): INTID 835 - GTM_TIO3_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO3_INT7                                   (835U)
#ifndef INTC_INTSRC_NUM_835        
#define INTC_INTSRC_NUM_835                                     (835U)
#endif /* INTC_INTSRC_NUM_835 */
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
/* External interrupt source(SPI): INTID 844 - GTM_MCS1_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_INT0                                   (844U)
#ifndef INTC_INTSRC_NUM_844        
#define INTC_INTSRC_NUM_844                                     (844U)
#endif /* INTC_INTSRC_NUM_844 */
/* External interrupt source(SPI): INTID 845 - GTM_MCS1_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_INT1                                   (845U)
#ifndef INTC_INTSRC_NUM_845        
#define INTC_INTSRC_NUM_845                                     (845U)
#endif /* INTC_INTSRC_NUM_845 */
/* External interrupt source(SPI): INTID 846 - GTM_MCS1_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_INT2                                   (846U)
#ifndef INTC_INTSRC_NUM_846        
#define INTC_INTSRC_NUM_846                                     (846U)
#endif /* INTC_INTSRC_NUM_846 */
/* External interrupt source(SPI): INTID 847 - GTM_MCS1_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_INT3                                   (847U)
#ifndef INTC_INTSRC_NUM_847        
#define INTC_INTSRC_NUM_847                                     (847U)
#endif /* INTC_INTSRC_NUM_847 */
/* External interrupt source(SPI): INTID 848 - GTM_MCS1_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_INT4                                   (848U)
#ifndef INTC_INTSRC_NUM_848        
#define INTC_INTSRC_NUM_848                                     (848U)
#endif /* INTC_INTSRC_NUM_848 */
/* External interrupt source(SPI): INTID 849 - GTM_MCS1_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_INT5                                   (849U)
#ifndef INTC_INTSRC_NUM_849        
#define INTC_INTSRC_NUM_849                                     (849U)
#endif /* INTC_INTSRC_NUM_849 */
/* External interrupt source(SPI): INTID 850 - GTM_MCS1_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_INT6                                   (850U)
#ifndef INTC_INTSRC_NUM_850        
#define INTC_INTSRC_NUM_850                                     (850U)
#endif /* INTC_INTSRC_NUM_850 */
/* External interrupt source(SPI): INTID 851 - GTM_MCS1_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_INT7                                   (851U)
#ifndef INTC_INTSRC_NUM_851        
#define INTC_INTSRC_NUM_851                                     (851U)
#endif /* INTC_INTSRC_NUM_851 */
/* External interrupt source(SPI): INTID 852 - GTM_MCS2_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_INT0                                   (852U)
#ifndef INTC_INTSRC_NUM_852        
#define INTC_INTSRC_NUM_852                                     (852U)
#endif /* INTC_INTSRC_NUM_852 */
/* External interrupt source(SPI): INTID 853 - GTM_MCS2_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_INT1                                   (853U)
#ifndef INTC_INTSRC_NUM_853        
#define INTC_INTSRC_NUM_853                                     (853U)
#endif /* INTC_INTSRC_NUM_853 */
/* External interrupt source(SPI): INTID 854 - GTM_MCS2_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_INT2                                   (854U)
#ifndef INTC_INTSRC_NUM_854        
#define INTC_INTSRC_NUM_854                                     (854U)
#endif /* INTC_INTSRC_NUM_854 */
/* External interrupt source(SPI): INTID 855 - GTM_MCS2_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_INT3                                   (855U)
#ifndef INTC_INTSRC_NUM_855        
#define INTC_INTSRC_NUM_855                                     (855U)
#endif /* INTC_INTSRC_NUM_855 */
/* External interrupt source(SPI): INTID 856 - GTM_MCS2_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_INT4                                   (856U)
#ifndef INTC_INTSRC_NUM_856        
#define INTC_INTSRC_NUM_856                                     (856U)
#endif /* INTC_INTSRC_NUM_856 */
/* External interrupt source(SPI): INTID 857 - GTM_MCS2_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_INT5                                   (857U)
#ifndef INTC_INTSRC_NUM_857        
#define INTC_INTSRC_NUM_857                                     (857U)
#endif /* INTC_INTSRC_NUM_857 */
/* External interrupt source(SPI): INTID 858 - GTM_MCS2_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_INT6                                   (858U)
#ifndef INTC_INTSRC_NUM_858        
#define INTC_INTSRC_NUM_858                                     (858U)
#endif /* INTC_INTSRC_NUM_858 */
/* External interrupt source(SPI): INTID 859 - GTM_MCS2_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_INT7                                   (859U)
#ifndef INTC_INTSRC_NUM_859        
#define INTC_INTSRC_NUM_859                                     (859U)
#endif /* INTC_INTSRC_NUM_859 */
/* External interrupt source(SPI): INTID 860 - GTM_MCS3_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_INT0                                   (860U)
#ifndef INTC_INTSRC_NUM_860        
#define INTC_INTSRC_NUM_860                                     (860U)
#endif /* INTC_INTSRC_NUM_860 */
/* External interrupt source(SPI): INTID 861 - GTM_MCS3_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_INT1                                   (861U)
#ifndef INTC_INTSRC_NUM_861        
#define INTC_INTSRC_NUM_861                                     (861U)
#endif /* INTC_INTSRC_NUM_861 */
/* External interrupt source(SPI): INTID 862 - GTM_MCS3_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_INT2                                   (862U)
#ifndef INTC_INTSRC_NUM_862        
#define INTC_INTSRC_NUM_862                                     (862U)
#endif /* INTC_INTSRC_NUM_862 */
/* External interrupt source(SPI): INTID 863 - GTM_MCS3_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_INT3                                   (863U)
#ifndef INTC_INTSRC_NUM_863        
#define INTC_INTSRC_NUM_863                                     (863U)
#endif /* INTC_INTSRC_NUM_863 */
/* External interrupt source(SPI): INTID 864 - GTM_MCS3_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_INT4                                   (864U)
#ifndef INTC_INTSRC_NUM_864        
#define INTC_INTSRC_NUM_864                                     (864U)
#endif /* INTC_INTSRC_NUM_864 */
/* External interrupt source(SPI): INTID 865 - GTM_MCS3_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_INT5                                   (865U)
#ifndef INTC_INTSRC_NUM_865        
#define INTC_INTSRC_NUM_865                                     (865U)
#endif /* INTC_INTSRC_NUM_865 */
/* External interrupt source(SPI): INTID 866 - GTM_MCS3_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_INT6                                   (866U)
#ifndef INTC_INTSRC_NUM_866        
#define INTC_INTSRC_NUM_866                                     (866U)
#endif /* INTC_INTSRC_NUM_866 */
/* External interrupt source(SPI): INTID 867 - GTM_MCS3_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_INT7                                   (867U)
#ifndef INTC_INTSRC_NUM_867        
#define INTC_INTSRC_NUM_867                                     (867U)
#endif /* INTC_INTSRC_NUM_867 */
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
/* External interrupt source(SPI): INTID 876 - GTM_MCS1_S_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_S_INT0                                   (876U)
#ifndef INTC_INTSRC_NUM_876        
#define INTC_INTSRC_NUM_876                                     (876U)
#endif /* INTC_INTSRC_NUM_876 */
/* External interrupt source(SPI): INTID 877 - GTM_MCS1_S_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_S_INT1                                   (877U)
#ifndef INTC_INTSRC_NUM_877        
#define INTC_INTSRC_NUM_877                                     (877U)
#endif /* INTC_INTSRC_NUM_877 */
/* External interrupt source(SPI): INTID 878 - GTM_MCS1_S_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_S_INT2                                   (878U)
#ifndef INTC_INTSRC_NUM_878        
#define INTC_INTSRC_NUM_878                                     (878U)
#endif /* INTC_INTSRC_NUM_878 */
/* External interrupt source(SPI): INTID 879 - GTM_MCS1_S_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_S_INT3                                   (879U)
#ifndef INTC_INTSRC_NUM_879        
#define INTC_INTSRC_NUM_879                                     (879U)
#endif /* INTC_INTSRC_NUM_879 */
/* External interrupt source(SPI): INTID 880 - GTM_MCS1_S_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_S_INT4                                   (880U)
#ifndef INTC_INTSRC_NUM_880        
#define INTC_INTSRC_NUM_880                                     (880U)
#endif /* INTC_INTSRC_NUM_880 */
/* External interrupt source(SPI): INTID 881 - GTM_MCS1_S_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_S_INT5                                   (881U)
#ifndef INTC_INTSRC_NUM_881        
#define INTC_INTSRC_NUM_881                                     (881U)
#endif /* INTC_INTSRC_NUM_881 */
/* External interrupt source(SPI): INTID 882 - GTM_MCS1_S_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_S_INT6                                   (882U)
#ifndef INTC_INTSRC_NUM_882        
#define INTC_INTSRC_NUM_882                                     (882U)
#endif /* INTC_INTSRC_NUM_882 */
/* External interrupt source(SPI): INTID 883 - GTM_MCS1_S_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS1_S_INT7                                   (883U)
#ifndef INTC_INTSRC_NUM_883        
#define INTC_INTSRC_NUM_883                                     (883U)
#endif /* INTC_INTSRC_NUM_883 */
/* External interrupt source(SPI): INTID 884 - GTM_MCS2_S_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_S_INT0                                   (884U)
#ifndef INTC_INTSRC_NUM_884        
#define INTC_INTSRC_NUM_884                                     (884U)
#endif /* INTC_INTSRC_NUM_884 */
/* External interrupt source(SPI): INTID 885 - GTM_MCS2_S_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_S_INT1                                   (885U)
#ifndef INTC_INTSRC_NUM_885        
#define INTC_INTSRC_NUM_885                                     (885U)
#endif /* INTC_INTSRC_NUM_885 */
/* External interrupt source(SPI): INTID 886 - GTM_MCS2_S_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_S_INT2                                   (886U)
#ifndef INTC_INTSRC_NUM_886        
#define INTC_INTSRC_NUM_886                                     (886U)
#endif /* INTC_INTSRC_NUM_886 */
/* External interrupt source(SPI): INTID 887 - GTM_MCS2_S_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_S_INT3                                   (887U)
#ifndef INTC_INTSRC_NUM_887        
#define INTC_INTSRC_NUM_887                                     (887U)
#endif /* INTC_INTSRC_NUM_887 */
/* External interrupt source(SPI): INTID 888 - GTM_MCS2_S_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_S_INT4                                   (888U)
#ifndef INTC_INTSRC_NUM_888        
#define INTC_INTSRC_NUM_888                                     (888U)
#endif /* INTC_INTSRC_NUM_888 */
/* External interrupt source(SPI): INTID 889 - GTM_MCS2_S_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_S_INT5                                   (889U)
#ifndef INTC_INTSRC_NUM_889        
#define INTC_INTSRC_NUM_889                                     (889U)
#endif /* INTC_INTSRC_NUM_889 */
/* External interrupt source(SPI): INTID 890 - GTM_MCS2_S_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_S_INT6                                   (890U)
#ifndef INTC_INTSRC_NUM_890        
#define INTC_INTSRC_NUM_890                                     (890U)
#endif /* INTC_INTSRC_NUM_890 */
/* External interrupt source(SPI): INTID 891 - GTM_MCS2_S_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS2_S_INT7                                   (891U)
#ifndef INTC_INTSRC_NUM_891        
#define INTC_INTSRC_NUM_891                                     (891U)
#endif /* INTC_INTSRC_NUM_891 */
/* External interrupt source(SPI): INTID 892 - GTM_MCS3_S_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_S_INT0                                   (892U)
#ifndef INTC_INTSRC_NUM_892        
#define INTC_INTSRC_NUM_892                                     (892U)
#endif /* INTC_INTSRC_NUM_892 */
/* External interrupt source(SPI): INTID 893 - GTM_MCS3_S_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_S_INT1                                   (893U)
#ifndef INTC_INTSRC_NUM_893        
#define INTC_INTSRC_NUM_893                                     (893U)
#endif /* INTC_INTSRC_NUM_893 */
/* External interrupt source(SPI): INTID 894 - GTM_MCS3_S_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_S_INT2                                   (894U)
#ifndef INTC_INTSRC_NUM_894        
#define INTC_INTSRC_NUM_894                                     (894U)
#endif /* INTC_INTSRC_NUM_894 */
/* External interrupt source(SPI): INTID 895 - GTM_MCS3_S_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_S_INT3                                   (895U)
#ifndef INTC_INTSRC_NUM_895        
#define INTC_INTSRC_NUM_895                                     (895U)
#endif /* INTC_INTSRC_NUM_895 */
/* External interrupt source(SPI): INTID 896 - GTM_MCS3_S_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_S_INT4                                   (896U)
#ifndef INTC_INTSRC_NUM_896        
#define INTC_INTSRC_NUM_896                                     (896U)
#endif /* INTC_INTSRC_NUM_896 */
/* External interrupt source(SPI): INTID 897 - GTM_MCS3_S_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_S_INT5                                   (897U)
#ifndef INTC_INTSRC_NUM_897        
#define INTC_INTSRC_NUM_897                                     (897U)
#endif /* INTC_INTSRC_NUM_897 */
/* External interrupt source(SPI): INTID 898 - GTM_MCS3_S_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_S_INT6                                   (898U)
#ifndef INTC_INTSRC_NUM_898        
#define INTC_INTSRC_NUM_898                                     (898U)
#endif /* INTC_INTSRC_NUM_898 */
/* External interrupt source(SPI): INTID 899 - GTM_MCS3_S_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS3_S_INT7                                   (899U)
#ifndef INTC_INTSRC_NUM_899        
#define INTC_INTSRC_NUM_899                                     (899U)
#endif /* INTC_INTSRC_NUM_899 */
/* External interrupt source(SPI): INTID 900 - GTM_WRAPPER_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_WRAPPER_INT0                                   (900U)
#ifndef INTC_INTSRC_NUM_900        
#define INTC_INTSRC_NUM_900                                     (900U)
#endif /* INTC_INTSRC_NUM_900 */
/* External interrupt source(SPI): INTID 901 - GTM_WRAPPER_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_WRAPPER_INT1                                   (901U)
#ifndef INTC_INTSRC_NUM_901        
#define INTC_INTSRC_NUM_901                                     (901U)
#endif /* INTC_INTSRC_NUM_901 */
/* External interrupt source(SPI): INTID 902 - GTM_WRAPPER_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_WRAPPER_INT2                                   (902U)
#ifndef INTC_INTSRC_NUM_902        
#define INTC_INTSRC_NUM_902                                     (902U)
#endif /* INTC_INTSRC_NUM_902 */
/* External interrupt source(SPI): INTID 903 - GTM_WRAPPER_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_WRAPPER_INT3                                   (903U)
#ifndef INTC_INTSRC_NUM_903        
#define INTC_INTSRC_NUM_903                                     (903U)
#endif /* INTC_INTSRC_NUM_903 */
/* External interrupt source(SPI): INTID 904 - GTM_SPE3_INT */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_SPE3_INT                                   (904U)
#ifndef INTC_INTSRC_NUM_904        
#define INTC_INTSRC_NUM_904                                     (904U)
#endif /* INTC_INTSRC_NUM_904 */
/* External interrupt source(SPI): INTID 905 - GTM_TIM3_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM3_INT0                                   (905U)
#ifndef INTC_INTSRC_NUM_905        
#define INTC_INTSRC_NUM_905                                     (905U)
#endif /* INTC_INTSRC_NUM_905 */
/* External interrupt source(SPI): INTID 906 - GTM_TIM3_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM3_INT1                                   (906U)
#ifndef INTC_INTSRC_NUM_906        
#define INTC_INTSRC_NUM_906                                     (906U)
#endif /* INTC_INTSRC_NUM_906 */
/* External interrupt source(SPI): INTID 907 - GTM_TIM3_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM3_INT2                                   (907U)
#ifndef INTC_INTSRC_NUM_907        
#define INTC_INTSRC_NUM_907                                     (907U)
#endif /* INTC_INTSRC_NUM_907 */
/* External interrupt source(SPI): INTID 908 - GTM_TIM3_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM3_INT3                                   (908U)
#ifndef INTC_INTSRC_NUM_908        
#define INTC_INTSRC_NUM_908                                     (908U)
#endif /* INTC_INTSRC_NUM_908 */
/* External interrupt source(SPI): INTID 909 - GTM_TIM3_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM3_INT4                                   (909U)
#ifndef INTC_INTSRC_NUM_909        
#define INTC_INTSRC_NUM_909                                     (909U)
#endif /* INTC_INTSRC_NUM_909 */
/* External interrupt source(SPI): INTID 910 - GTM_TIM3_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM3_INT5                                   (910U)
#ifndef INTC_INTSRC_NUM_910        
#define INTC_INTSRC_NUM_910                                     (910U)
#endif /* INTC_INTSRC_NUM_910 */
/* External interrupt source(SPI): INTID 911 - GTM_TIM3_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM3_INT6                                   (911U)
#ifndef INTC_INTSRC_NUM_911        
#define INTC_INTSRC_NUM_911                                     (911U)
#endif /* INTC_INTSRC_NUM_911 */
/* External interrupt source(SPI): INTID 912 - GTM_TIM3_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM3_INT7                                   (912U)
#ifndef INTC_INTSRC_NUM_912        
#define INTC_INTSRC_NUM_912                                     (912U)
#endif /* INTC_INTSRC_NUM_912 */
/* External interrupt source(SPI): INTID 913 - GTM_TIM4_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM4_INT0                                   (913U)
#ifndef INTC_INTSRC_NUM_913        
#define INTC_INTSRC_NUM_913                                     (913U)
#endif /* INTC_INTSRC_NUM_913 */
/* External interrupt source(SPI): INTID 914 - GTM_TIM4_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM4_INT1                                   (914U)
#ifndef INTC_INTSRC_NUM_914        
#define INTC_INTSRC_NUM_914                                     (914U)
#endif /* INTC_INTSRC_NUM_914 */
/* External interrupt source(SPI): INTID 915 - GTM_TIM4_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM4_INT2                                   (915U)
#ifndef INTC_INTSRC_NUM_915        
#define INTC_INTSRC_NUM_915                                     (915U)
#endif /* INTC_INTSRC_NUM_915 */
/* External interrupt source(SPI): INTID 916 - GTM_TIM4_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM4_INT3                                   (916U)
#ifndef INTC_INTSRC_NUM_916        
#define INTC_INTSRC_NUM_916                                     (916U)
#endif /* INTC_INTSRC_NUM_916 */
/* External interrupt source(SPI): INTID 917 - GTM_TIM4_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM4_INT4                                   (917U)
#ifndef INTC_INTSRC_NUM_917        
#define INTC_INTSRC_NUM_917                                     (917U)
#endif /* INTC_INTSRC_NUM_917 */
/* External interrupt source(SPI): INTID 918 - GTM_TIM4_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM4_INT5                                   (918U)
#ifndef INTC_INTSRC_NUM_918        
#define INTC_INTSRC_NUM_918                                     (918U)
#endif /* INTC_INTSRC_NUM_918 */
/* External interrupt source(SPI): INTID 919 - GTM_TIM4_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM4_INT6                                   (919U)
#ifndef INTC_INTSRC_NUM_919        
#define INTC_INTSRC_NUM_919                                     (919U)
#endif /* INTC_INTSRC_NUM_919 */
/* External interrupt source(SPI): INTID 920 - GTM_TIM4_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM4_INT7                                   (920U)
#ifndef INTC_INTSRC_NUM_920        
#define INTC_INTSRC_NUM_920                                     (920U)
#endif /* INTC_INTSRC_NUM_920 */
/* External interrupt source(SPI): INTID 921 - GTM_TIM5_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM5_INT0                                   (921U)
#ifndef INTC_INTSRC_NUM_921        
#define INTC_INTSRC_NUM_921                                     (921U)
#endif /* INTC_INTSRC_NUM_921 */
/* External interrupt source(SPI): INTID 922 - GTM_TIM5_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM5_INT1                                   (922U)
#ifndef INTC_INTSRC_NUM_922        
#define INTC_INTSRC_NUM_922                                     (922U)
#endif /* INTC_INTSRC_NUM_922 */
/* External interrupt source(SPI): INTID 923 - GTM_TIM5_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM5_INT2                                   (923U)
#ifndef INTC_INTSRC_NUM_923        
#define INTC_INTSRC_NUM_923                                     (923U)
#endif /* INTC_INTSRC_NUM_923 */
/* External interrupt source(SPI): INTID 924 - GTM_TIM5_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM5_INT3                                   (924U)
#ifndef INTC_INTSRC_NUM_924        
#define INTC_INTSRC_NUM_924                                     (924U)
#endif /* INTC_INTSRC_NUM_924 */
/* External interrupt source(SPI): INTID 925 - GTM_TIM5_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM5_INT4                                   (925U)
#ifndef INTC_INTSRC_NUM_925        
#define INTC_INTSRC_NUM_925                                     (925U)
#endif /* INTC_INTSRC_NUM_925 */
/* External interrupt source(SPI): INTID 926 - GTM_TIM5_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM5_INT5                                   (926U)
#ifndef INTC_INTSRC_NUM_926        
#define INTC_INTSRC_NUM_926                                     (926U)
#endif /* INTC_INTSRC_NUM_926 */
/* External interrupt source(SPI): INTID 927 - GTM_TIM5_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM5_INT6                                   (927U)
#ifndef INTC_INTSRC_NUM_927        
#define INTC_INTSRC_NUM_927                                     (927U)
#endif /* INTC_INTSRC_NUM_927 */
/* External interrupt source(SPI): INTID 928 - GTM_TIM5_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM5_INT7                                   (928U)
#ifndef INTC_INTSRC_NUM_928        
#define INTC_INTSRC_NUM_928                                     (928U)
#endif /* INTC_INTSRC_NUM_928 */
/* External interrupt source(SPI): INTID 929 - GTM_TIM6_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM6_INT0                                   (929U)
#ifndef INTC_INTSRC_NUM_929        
#define INTC_INTSRC_NUM_929                                     (929U)
#endif /* INTC_INTSRC_NUM_929 */
/* External interrupt source(SPI): INTID 930 - GTM_TIM6_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM6_INT1                                   (930U)
#ifndef INTC_INTSRC_NUM_930        
#define INTC_INTSRC_NUM_930                                     (930U)
#endif /* INTC_INTSRC_NUM_930 */
/* External interrupt source(SPI): INTID 931 - GTM_TIM6_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM6_INT2                                   (931U)
#ifndef INTC_INTSRC_NUM_931        
#define INTC_INTSRC_NUM_931                                     (931U)
#endif /* INTC_INTSRC_NUM_931 */
/* External interrupt source(SPI): INTID 932 - GTM_TIM6_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM6_INT3                                   (932U)
#ifndef INTC_INTSRC_NUM_932        
#define INTC_INTSRC_NUM_932                                     (932U)
#endif /* INTC_INTSRC_NUM_932 */
/* External interrupt source(SPI): INTID 933 - GTM_TIM6_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM6_INT4                                   (933U)
#ifndef INTC_INTSRC_NUM_933        
#define INTC_INTSRC_NUM_933                                     (933U)
#endif /* INTC_INTSRC_NUM_933 */
/* External interrupt source(SPI): INTID 934 - GTM_TIM6_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM6_INT5                                   (934U)
#ifndef INTC_INTSRC_NUM_934        
#define INTC_INTSRC_NUM_934                                     (934U)
#endif /* INTC_INTSRC_NUM_934 */
/* External interrupt source(SPI): INTID 935 - GTM_TIM6_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM6_INT6                                   (935U)
#ifndef INTC_INTSRC_NUM_935        
#define INTC_INTSRC_NUM_935                                     (935U)
#endif /* INTC_INTSRC_NUM_935 */
/* External interrupt source(SPI): INTID 936 - GTM_TIM6_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM6_INT7                                   (936U)
#ifndef INTC_INTSRC_NUM_936        
#define INTC_INTSRC_NUM_936                                     (936U)
#endif /* INTC_INTSRC_NUM_936 */
/* External interrupt source(SPI): INTID 937 - GTM_TIM7_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM7_INT0                                   (937U)
#ifndef INTC_INTSRC_NUM_937        
#define INTC_INTSRC_NUM_937                                     (937U)
#endif /* INTC_INTSRC_NUM_937 */
/* External interrupt source(SPI): INTID 938 - GTM_TIM7_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM7_INT1                                   (938U)
#ifndef INTC_INTSRC_NUM_938        
#define INTC_INTSRC_NUM_938                                     (938U)
#endif /* INTC_INTSRC_NUM_938 */
/* External interrupt source(SPI): INTID 939 - GTM_TIM7_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM7_INT2                                   (939U)
#ifndef INTC_INTSRC_NUM_939        
#define INTC_INTSRC_NUM_939                                     (939U)
#endif /* INTC_INTSRC_NUM_939 */
/* External interrupt source(SPI): INTID 940 - GTM_TIM7_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM7_INT3                                   (940U)
#ifndef INTC_INTSRC_NUM_940        
#define INTC_INTSRC_NUM_940                                     (940U)
#endif /* INTC_INTSRC_NUM_940 */
/* External interrupt source(SPI): INTID 941 - GTM_TIM7_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM7_INT4                                   (941U)
#ifndef INTC_INTSRC_NUM_941        
#define INTC_INTSRC_NUM_941                                     (941U)
#endif /* INTC_INTSRC_NUM_941 */
/* External interrupt source(SPI): INTID 942 - GTM_TIM7_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM7_INT5                                   (942U)
#ifndef INTC_INTSRC_NUM_942        
#define INTC_INTSRC_NUM_942                                     (942U)
#endif /* INTC_INTSRC_NUM_942 */
/* External interrupt source(SPI): INTID 943 - GTM_TIM7_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM7_INT6                                   (943U)
#ifndef INTC_INTSRC_NUM_943        
#define INTC_INTSRC_NUM_943                                     (943U)
#endif /* INTC_INTSRC_NUM_943 */
/* External interrupt source(SPI): INTID 944 - GTM_TIM7_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIM7_INT7                                   (944U)
#ifndef INTC_INTSRC_NUM_944        
#define INTC_INTSRC_NUM_944                                     (944U)
#endif /* INTC_INTSRC_NUM_944 */
/* External interrupt source(SPI): INTID 945 - GTM_TOM3_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM3_INT0                                   (945U)
#ifndef INTC_INTSRC_NUM_945        
#define INTC_INTSRC_NUM_945                                     (945U)
#endif /* INTC_INTSRC_NUM_945 */
/* External interrupt source(SPI): INTID 946 - GTM_TOM3_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM3_INT1                                   (946U)
#ifndef INTC_INTSRC_NUM_946        
#define INTC_INTSRC_NUM_946                                     (946U)
#endif /* INTC_INTSRC_NUM_946 */
/* External interrupt source(SPI): INTID 947 - GTM_TOM3_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM3_INT2                                   (947U)
#ifndef INTC_INTSRC_NUM_947        
#define INTC_INTSRC_NUM_947                                     (947U)
#endif /* INTC_INTSRC_NUM_947 */
/* External interrupt source(SPI): INTID 948 - GTM_TOM3_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM3_INT3                                   (948U)
#ifndef INTC_INTSRC_NUM_948        
#define INTC_INTSRC_NUM_948                                     (948U)
#endif /* INTC_INTSRC_NUM_948 */
/* External interrupt source(SPI): INTID 949 - GTM_TOM3_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM3_INT4                                   (949U)
#ifndef INTC_INTSRC_NUM_949        
#define INTC_INTSRC_NUM_949                                     (949U)
#endif /* INTC_INTSRC_NUM_949 */
/* External interrupt source(SPI): INTID 950 - GTM_TOM3_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM3_INT5                                   (950U)
#ifndef INTC_INTSRC_NUM_950        
#define INTC_INTSRC_NUM_950                                     (950U)
#endif /* INTC_INTSRC_NUM_950 */
/* External interrupt source(SPI): INTID 951 - GTM_TOM3_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM3_INT6                                   (951U)
#ifndef INTC_INTSRC_NUM_951        
#define INTC_INTSRC_NUM_951                                     (951U)
#endif /* INTC_INTSRC_NUM_951 */
/* External interrupt source(SPI): INTID 952 - GTM_TOM3_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM3_INT7                                   (952U)
#ifndef INTC_INTSRC_NUM_952        
#define INTC_INTSRC_NUM_952                                     (952U)
#endif /* INTC_INTSRC_NUM_952 */
/* External interrupt source(SPI): INTID 953 - GTM_TOM4_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM4_INT0                                   (953U)
#ifndef INTC_INTSRC_NUM_953        
#define INTC_INTSRC_NUM_953                                     (953U)
#endif /* INTC_INTSRC_NUM_953 */
/* External interrupt source(SPI): INTID 954 - GTM_TOM4_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM4_INT1                                   (954U)
#ifndef INTC_INTSRC_NUM_954        
#define INTC_INTSRC_NUM_954                                     (954U)
#endif /* INTC_INTSRC_NUM_954 */
/* External interrupt source(SPI): INTID 955 - GTM_TOM4_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM4_INT2                                   (955U)
#ifndef INTC_INTSRC_NUM_955        
#define INTC_INTSRC_NUM_955                                     (955U)
#endif /* INTC_INTSRC_NUM_955 */
/* External interrupt source(SPI): INTID 956 - GTM_TOM4_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM4_INT3                                   (956U)
#ifndef INTC_INTSRC_NUM_956        
#define INTC_INTSRC_NUM_956                                     (956U)
#endif /* INTC_INTSRC_NUM_956 */
/* External interrupt source(SPI): INTID 957 - GTM_TOM4_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM4_INT4                                   (957U)
#ifndef INTC_INTSRC_NUM_957        
#define INTC_INTSRC_NUM_957                                     (957U)
#endif /* INTC_INTSRC_NUM_957 */
/* External interrupt source(SPI): INTID 958 - GTM_TOM4_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM4_INT5                                   (958U)
#ifndef INTC_INTSRC_NUM_958        
#define INTC_INTSRC_NUM_958                                     (958U)
#endif /* INTC_INTSRC_NUM_958 */
/* External interrupt source(SPI): INTID 959 - GTM_TOM4_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM4_INT6                                   (959U)
#ifndef INTC_INTSRC_NUM_959        
#define INTC_INTSRC_NUM_959                                     (959U)
#endif /* INTC_INTSRC_NUM_959 */
/* External interrupt source(SPI): INTID 960 - GTM_TOM4_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TOM4_INT7                                   (960U)
#ifndef INTC_INTSRC_NUM_960        
#define INTC_INTSRC_NUM_960                                     (960U)
#endif /* INTC_INTSRC_NUM_960 */
/* External interrupt source(SPI): INTID 961 - GTM_ATOM4_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM4_INT0                                   (961U)
#ifndef INTC_INTSRC_NUM_961        
#define INTC_INTSRC_NUM_961                                     (961U)
#endif /* INTC_INTSRC_NUM_961 */
/* External interrupt source(SPI): INTID 962 - GTM_ATOM4_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM4_INT1                                   (962U)
#ifndef INTC_INTSRC_NUM_962        
#define INTC_INTSRC_NUM_962                                     (962U)
#endif /* INTC_INTSRC_NUM_962 */
/* External interrupt source(SPI): INTID 963 - GTM_ATOM4_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM4_INT2                                   (963U)
#ifndef INTC_INTSRC_NUM_963        
#define INTC_INTSRC_NUM_963                                     (963U)
#endif /* INTC_INTSRC_NUM_963 */
/* External interrupt source(SPI): INTID 964 - GTM_ATOM4_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM4_INT3                                   (964U)
#ifndef INTC_INTSRC_NUM_964        
#define INTC_INTSRC_NUM_964                                     (964U)
#endif /* INTC_INTSRC_NUM_964 */
/* External interrupt source(SPI): INTID 965 - GTM_ATOM5_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM5_INT0                                   (965U)
#ifndef INTC_INTSRC_NUM_965        
#define INTC_INTSRC_NUM_965                                     (965U)
#endif /* INTC_INTSRC_NUM_965 */
/* External interrupt source(SPI): INTID 966 - GTM_ATOM5_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM5_INT1                                   (966U)
#ifndef INTC_INTSRC_NUM_966        
#define INTC_INTSRC_NUM_966                                     (966U)
#endif /* INTC_INTSRC_NUM_966 */
/* External interrupt source(SPI): INTID 967 - GTM_ATOM5_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM5_INT2                                   (967U)
#ifndef INTC_INTSRC_NUM_967        
#define INTC_INTSRC_NUM_967                                     (967U)
#endif /* INTC_INTSRC_NUM_967 */
/* External interrupt source(SPI): INTID 968 - GTM_ATOM5_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM5_INT3                                   (968U)
#ifndef INTC_INTSRC_NUM_968        
#define INTC_INTSRC_NUM_968                                     (968U)
#endif /* INTC_INTSRC_NUM_968 */
/* External interrupt source(SPI): INTID 969 - GTM_ATOM6_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM6_INT0                                   (969U)
#ifndef INTC_INTSRC_NUM_969        
#define INTC_INTSRC_NUM_969                                     (969U)
#endif /* INTC_INTSRC_NUM_969 */
/* External interrupt source(SPI): INTID 970 - GTM_ATOM6_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM6_INT1                                   (970U)
#ifndef INTC_INTSRC_NUM_970        
#define INTC_INTSRC_NUM_970                                     (970U)
#endif /* INTC_INTSRC_NUM_970 */
/* External interrupt source(SPI): INTID 971 - GTM_ATOM6_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM6_INT2                                   (971U)
#ifndef INTC_INTSRC_NUM_971        
#define INTC_INTSRC_NUM_971                                     (971U)
#endif /* INTC_INTSRC_NUM_971 */
/* External interrupt source(SPI): INTID 972 - GTM_ATOM6_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM6_INT3                                   (972U)
#ifndef INTC_INTSRC_NUM_972        
#define INTC_INTSRC_NUM_972                                     (972U)
#endif /* INTC_INTSRC_NUM_972 */
/* External interrupt source(SPI): INTID 973 - GTM_ATOM7_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM7_INT0                                   (973U)
#ifndef INTC_INTSRC_NUM_973        
#define INTC_INTSRC_NUM_973                                     (973U)
#endif /* INTC_INTSRC_NUM_973 */
/* External interrupt source(SPI): INTID 974 - GTM_ATOM7_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM7_INT1                                   (974U)
#ifndef INTC_INTSRC_NUM_974        
#define INTC_INTSRC_NUM_974                                     (974U)
#endif /* INTC_INTSRC_NUM_974 */
/* External interrupt source(SPI): INTID 975 - GTM_ATOM7_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM7_INT2                                   (975U)
#ifndef INTC_INTSRC_NUM_975        
#define INTC_INTSRC_NUM_975                                     (975U)
#endif /* INTC_INTSRC_NUM_975 */
/* External interrupt source(SPI): INTID 976 - GTM_ATOM7_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_ATOM7_INT3                                   (976U)
#ifndef INTC_INTSRC_NUM_976        
#define INTC_INTSRC_NUM_976                                     (976U)
#endif /* INTC_INTSRC_NUM_976 */
/* External interrupt source(SPI): INTID 977 - GTM_TIO4_INT0_7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO4_INT0_7                                   (977U)
#ifndef INTC_INTSRC_NUM_977        
#define INTC_INTSRC_NUM_977                                     (977U)
#endif /* INTC_INTSRC_NUM_977 */
/* External interrupt source(SPI): INTID 978 - GTM_TIO5_INT0_7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_TIO5_INT0_7                                   (978U)
#ifndef INTC_INTSRC_NUM_978        
#define INTC_INTSRC_NUM_978                                     (978U)
#endif /* INTC_INTSRC_NUM_978 */
/* External interrupt source(SPI): INTID 979 - GTM_MCS4_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS4_INT0                                   (979U)
#ifndef INTC_INTSRC_NUM_979        
#define INTC_INTSRC_NUM_979                                     (979U)
#endif /* INTC_INTSRC_NUM_979 */
/* External interrupt source(SPI): INTID 980 - GTM_MCS4_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS4_INT1                                   (980U)
#ifndef INTC_INTSRC_NUM_980        
#define INTC_INTSRC_NUM_980                                     (980U)
#endif /* INTC_INTSRC_NUM_980 */
/* External interrupt source(SPI): INTID 981 - GTM_MCS4_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS4_INT2                                   (981U)
#ifndef INTC_INTSRC_NUM_981        
#define INTC_INTSRC_NUM_981                                     (981U)
#endif /* INTC_INTSRC_NUM_981 */
/* External interrupt source(SPI): INTID 982 - GTM_MCS4_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS4_INT3                                   (982U)
#ifndef INTC_INTSRC_NUM_982        
#define INTC_INTSRC_NUM_982                                     (982U)
#endif /* INTC_INTSRC_NUM_982 */
/* External interrupt source(SPI): INTID 983 - GTM_MCS4_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS4_INT4                                   (983U)
#ifndef INTC_INTSRC_NUM_983        
#define INTC_INTSRC_NUM_983                                     (983U)
#endif /* INTC_INTSRC_NUM_983 */
/* External interrupt source(SPI): INTID 984 - GTM_MCS4_INT5 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS4_INT5                                   (984U)
#ifndef INTC_INTSRC_NUM_984        
#define INTC_INTSRC_NUM_984                                     (984U)
#endif /* INTC_INTSRC_NUM_984 */
/* External interrupt source(SPI): INTID 985 - GTM_MCS4_INT6 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS4_INT6                                   (985U)
#ifndef INTC_INTSRC_NUM_985        
#define INTC_INTSRC_NUM_985                                     (985U)
#endif /* INTC_INTSRC_NUM_985 */
/* External interrupt source(SPI): INTID 986 - GTM_MCS4_INT7 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS4_INT7                                   (986U)
#ifndef INTC_INTSRC_NUM_986        
#define INTC_INTSRC_NUM_986                                     (986U)
#endif /* INTC_INTSRC_NUM_986 */
/* External interrupt source(SPI): INTID 987 - GTM_MCS5_INT0 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS5_INT0                                   (987U)
#ifndef INTC_INTSRC_NUM_987        
#define INTC_INTSRC_NUM_987                                     (987U)
#endif /* INTC_INTSRC_NUM_987 */
/* External interrupt source(SPI): INTID 988 - GTM_MCS5_INT1 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS5_INT1                                   (988U)
#ifndef INTC_INTSRC_NUM_988        
#define INTC_INTSRC_NUM_988                                     (988U)
#endif /* INTC_INTSRC_NUM_988 */
/* External interrupt source(SPI): INTID 989 - GTM_MCS5_INT2 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS5_INT2                                   (989U)
#ifndef INTC_INTSRC_NUM_989        
#define INTC_INTSRC_NUM_989                                     (989U)
#endif /* INTC_INTSRC_NUM_989 */
/* External interrupt source(SPI): INTID 990 - GTM_MCS5_INT3 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS5_INT3                                   (990U)
#ifndef INTC_INTSRC_NUM_990        
#define INTC_INTSRC_NUM_990                                     (990U)
#endif /* INTC_INTSRC_NUM_990 */
/* External interrupt source(SPI): INTID 991 - GTM_MCS5_INT4 */
/* #Violation: Intc_Cfg_h_REF_1 */
#define INTC_INTSRC_GTM_MCS5_INT4                                   (991U)
#ifndef INTC_INTSRC_NUM_991        
#define INTC_INTSRC_NUM_991                                     (991U)
#endif /* INTC_INTSRC_NUM_991 */

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

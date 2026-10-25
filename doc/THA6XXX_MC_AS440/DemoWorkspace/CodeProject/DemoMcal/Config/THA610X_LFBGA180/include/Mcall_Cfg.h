/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Mcall_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : None
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
*#Mcall_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/

/***************************************************************************************************/
#ifndef MCALL_CFG_H_
#define MCALL_CFG_H_

/****************************************************************************************************
*                            Global Macro Definitions
****************************************************************************************************/
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define RESOURCE_CFG_AR_RELEASE_MAJOR_VERSION                  (4U)
#define RESOURCE_CFG_AR_RELEASE_MINOR_VERSION                  (4U)
#define RESOURCE_CFG_AR_RELEASE_REVISION_VERSION               (0U)

#define RESOURCE_CFG_SW_MAJOR_VERSION                          (1U)
#define RESOURCE_CFG_SW_MINOR_VERSION                          (2U)
#define RESOURCE_CFG_SW_PATCH_VERSION                          (0U)

#define RESOURCE_CFG_VENDOR_ID                                 (175U)


/* Core Mask for CORE0 */
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_CORE0_MASK                                        (0x00000000U)
/* Core Mask for CORE1 */
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_CORE1_MASK                                        (0x00000001U)

/* Core mask, flag which cores used */
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_USED_CORE_MASK                                    (0x00000000U)

/* THA6 Processor family */
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_PROCESSOR_THA6206_LFBGA292                                 (0U)
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_PROCESSOR_THA6412_BGA516                                 (1U)
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_PROCESSOR_THA610X_LFBGA180                                 (2U)
/* Used processor is  MODULE-CONFIGURATION */
#define MCAL_PROCESSOR_CAT                                     (MCAL_PROCESSOR_THA610X_LFBGA180)

/* Macro for the master Core */
#define MCAL_MASTER_CORE                                       (MCAL_CORE0)

/* Total number of cores */
#define MCAL_NUMBER_OF_CORES                                   (2U)

/* Number of cores used */
/* #Violation: Mcall_Cfg_h_REF_1 */
#define MCAL_CFG_NUMBER_OF_USED_CORES                          (1U)

/* CORE0 used */
#ifndef MCAL_CFG_ENABLE_CORE0
#define MCAL_CFG_ENABLE_CORE0                                  (STD_ON)
#endif /* \ifndef MCAL_CFG_ENABLE_CORE0 */
/* CORE1 used */
#ifndef MCAL_CFG_ENABLE_CORE1
#define MCAL_CFG_ENABLE_CORE1                                  (STD_OFF)
#endif /* \ifndef MCAL_CFG_ENABLE_CORE1 */

/* MCAL module 'Adc' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_ADC_USED                             (STD_ON)
/* MCAL module 'Adc' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_ADC_EN                               (STD_ON)

/* MCAL module 'Can' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_CAN_USED                             (STD_ON)
/* MCAL module 'Can' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_CAN_EN                               (STD_ON)

/* MCAL module 'Dem' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_DEM_USED                             (STD_ON)
/* MCAL module 'Dem' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_DEM_EN                               (STD_ON)

/* MCAL module 'Dio' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_DIO_USED                             (STD_ON)
/* MCAL module 'Dio' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_DIO_EN                               (STD_ON)

/* MCAL module 'Dma' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_DMA_USED                             (STD_ON)
/* MCAL module 'Dma' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_DMA_EN                               (STD_ON)

/* MCAL module 'Eth' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_ETH_USED                             (STD_ON)
/* MCAL module 'Eth' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_ETH_EN                               (STD_ON)

/* MCAL module 'Fee' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_FEE_USED                             (STD_ON)
/* MCAL module 'Fee' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_FEE_EN                               (STD_ON)

/* MCAL module 'Fls' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_FLS_USED                             (STD_ON)
/* MCAL module 'Fls' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_FLS_EN                               (STD_ON)

/* MCAL module 'Gpt' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_GPT_USED                             (STD_ON)
/* MCAL module 'Gpt' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_GPT_EN                               (STD_ON)

/* MCAL module 'I2c' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_I2C_USED                             (STD_ON)
/* MCAL module 'I2c' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_I2C_EN                               (STD_ON)

/* MCAL module 'Icu' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_ICU_USED                             (STD_ON)
/* MCAL module 'Icu' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_ICU_EN                               (STD_ON)

/* MCAL module 'Intc' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_INTC_USED                             (STD_ON)
/* MCAL module 'Intc' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_INTC_EN                               (STD_ON)

/* MCAL module 'Iom' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_IOM_USED                             (STD_ON)
/* MCAL module 'Iom' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_IOM_EN                               (STD_ON)

/* MCAL module 'Lin' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_LIN_USED                             (STD_ON)
/* MCAL module 'Lin' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_LIN_EN                               (STD_ON)

/* MCAL module 'Mcu' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_MCU_USED                             (STD_ON)
/* MCAL module 'Mcu' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_MCU_EN                               (STD_ON)

/* MCAL module 'Ocu' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_OCU_USED                             (STD_ON)
/* MCAL module 'Ocu' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_OCU_EN                               (STD_ON)

/* MCAL module 'Port' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_PORT_USED                             (STD_ON)
/* MCAL module 'Port' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_PORT_EN                               (STD_ON)

/* MCAL module 'Pwm' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_PWM_USED                             (STD_ON)
/* MCAL module 'Pwm' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_PWM_EN                               (STD_ON)

/* MCAL module 'Resource' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_RESOURCE_USED                             (STD_ON)
/* MCAL module 'Resource' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_RESOURCE_EN                               (STD_ON)

/* MCAL module 'Sent' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_SENT_USED                             (STD_ON)
/* MCAL module 'Sent' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_SENT_EN                               (STD_ON)

/* MCAL module 'Spi' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_SPI_USED                             (STD_ON)
/* MCAL module 'Spi' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_SPI_EN                               (STD_ON)

/* MCAL module 'Uart' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_UART_USED                             (STD_ON)
/* MCAL module 'Uart' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_UART_EN                               (STD_ON)

/* MCAL module 'Wdg' Added */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_WDG_USED                             (STD_ON)
/* MCAL module 'Wdg' Enabled/Disabled */
/* #Violation: Mcall_Cfg_h_REF_1*/
#define MCAL_MODULE_CFG_WDG_EN                               (STD_ON)




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

#endif /* MCALL_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

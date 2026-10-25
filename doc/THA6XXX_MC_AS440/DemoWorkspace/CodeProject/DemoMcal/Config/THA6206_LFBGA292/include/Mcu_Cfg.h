/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Mcu_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Rcc,PWRC
*
*   brief                 : This file contains all configuration declarations of Mcu Driver
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
*#Mcu_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.  
*/
#ifndef MCU_CFG_H_
#define MCU_CFG_H_
/****************************************************************************************************
*                               Include Section
****************************************************************************************************/
/****************************************************************************************************
*                               Resource used
****************************************************************************************************/
#define MCU_INSTANCE_ID_VALUE                                     (0U)
/* ECUC_Mcu_00172 Total number of RAM sector configured */
#define MCU_NUM_RAM_SECTORS                                       (3U)
/* Total number of Clock Setting configured */
#define MCU_NUM_CLOCK_SETTING                                     (1U)
/* ECUC_Mcu_00171 Total number of Power Mode configured */
/* \[SWS_Mcu_00165]
 * be configured in the configuration set of the MCU module */
/* #Violation: Mcu_Cfg_h_REF_1*/
#define MCU_NUM_MODE_CONFIG                                       (1U)
/* The number of basetimer source */
#define MCU_NUM_BASETIMER                                         (6U)
#define MCU_RESET_CONFIG_NUM                                      (7U)
/****************************************************************************************************
*                               API  Enable/Disable
****************************************************************************************************/
/* Required variables */
/* ECUC_Mcu_00166 */
#define MCU_DEV_ERROR_DETECT                                         (STD_ON)
#define MCU_DEV_RUNTIME_ERROR_DETECT                                 (STD_ON)
#define MCU_SAFETY_ENABLE                                            (STD_ON)

/* ECUC_Mcu_00181 */
#define MCU_GET_RAM_STATE_API                                        (STD_OFF)
#define MCU_CLR_COLD_RESET_STAT_API                                  (STD_OFF)

/* ECUC_Mcu_00168 */
#define MCU_VERSION_INFO_API                                         (STD_ON)

/* ECUC_Mcu_00167 */
#define MCU_PERFORM_RESET_API                                        (STD_ON)


/* ECUC_Mcu_00182 */
#define MCU_INIT_CLOCK                                               (STD_ON)

/* ECUC_Mcu_00180 */
#define MCU_NO_PLL                                                   (STD_OFF)

#define MCU_RSTSOURCE_TIMEOUT_VALUE                                    (400U)
#define MCU_CONFIG_COUNT                                             (1U)
#define MCU_DEM_REPORT_ERROR_STATUS                                  (STD_OFF)


  
#ifndef McuConf_McuModeSettingConf_McuModeSettingConf_0
#define McuConf_McuModeSettingConf_McuModeSettingConf_0              (0U)
#endif
/* Clock Setting ID */
  
#ifndef McuConf_McuClockSettingConfig_McuClockSettingConfig_0
  #define McuConf_McuClockSettingConfig_McuClockSettingConfig_0      (0U)
#endif
/* Ram Section Config ID */
    
#ifndef McuConf_McuRamSectorSettingConf_ATCM
  #define McuConf_McuRamSectorSettingConf_ATCM                        (0U)
#endif
    
#ifndef McuConf_McuRamSectorSettingConf_CTCM
  #define McuConf_McuRamSectorSettingConf_CTCM                        (1U)
#endif
    
#ifndef McuConf_McuRamSectorSettingConf_GMU
  #define McuConf_McuRamSectorSettingConf_GMU                        (2U)
#endif
  
/* ResetReason Config */
#ifndef McuConf_McuResetReasonConf_MCU_POWER_ON_RESET
  #define McuConf_McuResetReasonConf_MCU_POWER_ON_RESET  (23U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RESET_UNDEFINED
  #define McuConf_McuResetReasonConf_MCU_RESET_UNDEFINED  (25U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_CPU0WARMRST
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_CPU0WARMRST  (7U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_CPU1WARMRST
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_CPU1WARMRST  (8U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_ESR0
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_ESR0  (0U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_ESR1
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_ESR1  (1U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_HSMAPP
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_HSMAPP  (18U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_HSMSYS
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_HSMSYS  (19U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_IST
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_IST  (17U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_MUTITYPE
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_MUTITYPE  (24U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_PORSTPIN
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_PORSTPIN  (16U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_RSTREASON_SAC
  #define McuConf_McuResetReasonConf_MCU_RSTREASON_SAC  (2U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_SW_RESET
  #define McuConf_McuResetReasonConf_MCU_SW_RESET  (3U)
#endif
#ifndef McuConf_McuResetReasonConf_MCU_WATCHDOG_RESET
  #define McuConf_McuResetReasonConf_MCU_WATCHDOG_RESET  (4U)
#endif
/****************************************************************************************************
*                               Function Prototypes
****************************************************************************************************/
/****************************************************************************************************
*                               Version Information
****************************************************************************************************/
#define MCU_CFG_VENDOR_ID                                             (175U)
#define MCU_CFG_MODULE_ID                                             (101U)
#define MCU_CFG_AR_RELEASE_MAJOR_VERSION                              (4U)
#define MCU_CFG_AR_RELEASE_MINOR_VERSION                              (4U)
#define MCU_CFG_AR_RELEASE_REVISION_VERSION                           (0U)
#define MCU_CFG_SW_MAJOR_VERSION                                      (1U)
#define MCU_CFG_SW_MINOR_VERSION                                      (2U)
/* #Violation: Mcu_Cfg_h_REF_1*/
#define MCU_CFG_SW_PATCH_VERSION                                      (0U)

#endif /* \#ifndef MCU_CFG_H_ */

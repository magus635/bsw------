/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Adc_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : SARADC
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
*#Adc_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*/

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define ADC_CFG_AR_RELEASE_MAJOR_VERSION                   (4U)
#define ADC_CFG_AR_RELEASE_MINOR_VERSION                   (4U)
#define ADC_CFG_AR_RELEASE_REVISION_VERSION                (0U)

#define ADC_CFG_SW_MAJOR_VERSION                           (1U)
#define ADC_CFG_SW_MINOR_VERSION                           (2U)
#define ADC_CFG_SW_PATCH_VERSION                           (0U)
#define ADC_CFG_VENDOR_ID                                  (175U)
#define ADC_CFG_MODULE_ID                                  (123U)

#define ADC_CONFIG_COUNT                                   (1U)
/*
Configuration: AdcSafetyDetect
- if Selected, Safety Error Check is Enabled 
- if Deselected, Safety Error Check is Disabled 
*/
#define ADC_SAFETY_ENABLE                                  (STD_ON)

/* Maximum resolution possible */
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_MAX_CHANNEL_RESOLUTION                         ((uint8)12)

/* ADC_CHANNEL_VALUESIGNED:  unsigned */
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_CHANNEL_VALUESIGNED                            (STD_OFF)
    
/* 
  Information whether the first channel of an ADC Channel group can be
  configured (FALSE) or is fixed (TRUE) to a value determined by the ADC HW Unit 
*/
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_GROUP_FIRST_CHANNEL_FIXED                      (STD_OFF)
    
/*
Configuration: AdcDevErrorDetect
- if STD_ON, DET is Enabled 
- if STD_OFF,DET is Disabled 
*/
#define ADC_DEV_ERROR_DETECT                               (STD_ON)
    
/* 
Configuration: AdcVersionInfoApi
- if STD_ON, VersionInfo API is Enabled 
- if STD_OFF, VersionInfo API is Disabled 
*/
#define ADC_VERSION_INFO_API                               (STD_ON)
    
/* 
Configuration: AdcLowPowerStatesSupport
- if STD_ON, Power State API is Enabled 
- if STD_OFF, Power State API is Disabled 
*/
#define ADC_POWER_STATE_SUPPORTED                          (STD_OFF)

/* 
Configuration: AdcGroupResultHandlingImplementation
- Conversion result handling method
*/
#define ADC_RESULT_HANDLING_INTERRUPT_MODE                 (0U)
#define ADC_RESULT_HANDLING_POLLING_MODE                   (1U) 
#define ADC_RESULT_HANDLING_DMA_MODE                       (2U)

#define ADC_INTERRUPT_MODE_ENABLE                          (STD_ON)
#define ADC_POLLING_MODE_ENABLE                            (STD_ON)
#define ADC_DMA_MODE_ENABLE                                (STD_ON)

/* 
Configuration: AdcStartupCalibration
- if STD_ON, Adc_StartupCalibration is called in Adc_Init 
- if STD_OFF, Adc_StartupCalibration is not called in Adc_Init
*/
#define ADC_STARTUP_CALIBRATION                            (STD_ON)
    
/*
Configuration: AdcDeInitApi
- if STD_ON, DeInit API is Enabled 
- if STD_OFF, DeInit API is Disabled 
*/
#define ADC_DEINIT_API                                     (STD_ON)
    
/* Configuration: AdcEnableStartStopGroupApi
Start/Stop Group conversion API configuration 
- if STD_ON, Start/Stop Group conversion API is Enabled 
- if STD_OFF, Start/Stop Group conversion API is Disabled 
*/
#define ADC_ENABLE_START_STOP_GROUP_API                    (STD_ON)
    
/* 
Configuration: AdcHwTriggerApi
- if STD_ON, Adc HW Trigger API is Enabled 
- if STD_OFF, Adc HW Trigger API is Disabled 
*/
#define ADC_HW_TRIGGER_API                                 (STD_ON)
    
/* 
Configuration: AdcReadGroupApi
- if STD_ON, Adc_ReadGroup API is Enabled 
- if STD_OFF, Adc_ReadGroup API is Disabled 
*/
#define ADC_READ_GROUP_API                                 (STD_ON)
    
/* 
Configuration: AdcGrpNotifCapability
- if STD_ON, Adc Notification capability is Enabled 
- if STD_OFF, Adc Notification capability is Disabled 
*/
#define ADC_GRP_NOTIF_CAPABILITY                           (STD_ON)
    
/* 
Configuration: AdcEnableLimitCheck
- if STD_ON, Limit checking is Enabled
- if STD_OFF, Limit checking is Disabled 
*/
#define ADC_ENABLE_LIMIT_CHECK                             (STD_ON)
    
/* 
Configuration: AdcSyncConvEnable
- if STD_ON, HW Sync group is Enabled
- if STD_OFF, HW Sync group is Disabled 
*/
#define ADC_HW_SYNC_CONV_GROUP_EN                          (STD_ON)
    
/* 
Configuration: AdcResultAlignment
Determines the ADC result alignment
- ADC_ALIGN_LEFT: left alignment
- ADC_ALIGN_RIGHT: right alignment
*/
#define ADC_RESULT_ALIGNMENT                               (ADC_ALIGN_RIGHT)

/* 
Configuration: AdcPriorityImplementation
Determines the type of prioritization mechanism
- ADC_PRIORITY_HW, Hardware priority mechanism is available only
- ADC_PRIORITY_HW_SW, Hardware and software priority mechanism is available
- ADC_PRIORITY_NONE, priority mechanism is not available
*/
#define ADC_PRIORITY_IMPLEMENTATION                        (ADC_PRIORITY_NONE)

/*
  SWS_Adc_00522.
  Options for the Priority Mechanism supported in ADC Driver
*/
/* Priority mechanism is not available */
#define ADC_PRIORITY_NONE                                  (0U)
/* Hardware priority mechanism is available only */
#define ADC_PRIORITY_HW                                    (1U)
/* Hardware and software priority mechanism is available */
#define ADC_PRIORITY_HW_SW                                 (2U) 


/* 
Configuration: ADC_ENABLE_QUEUING
Determines, if the queuing mechanism is active in case of priority mechanism 
disabled.
Note: If priority mechanism is enabled, queuing mechanism is always active 
and the parameter ADC_ENABLE_QUEUING is not evaluated.
- if STD_ON, Queuing mechanism in no priority is Enabled 
- if STD_OFF, Queuing mechanism in no priority is Disabled 
*/
#define ADC_ENABLE_QUEUING                                 (STD_OFF)
    
/* Number of ADC Kernels in the selected microcontroller */
#define ADC_MAX_KERNELS                                    (10U)

/* Configuration Options: ADC_HWUNIT_ID */
#define ADC_HWUNIT_ADC0                                    (0)
#define ADC_HWUNIT_ADC1                                    (1)
#define ADC_HWUNIT_ADC2                                    (2)
#define ADC_HWUNIT_ADC3                                    (3)
#define ADC_HWUNIT_ADC8                                    (8)
#define ADC_HWUNIT_ADC9                                    (9)

/* Configuration: ADC_TOTAL_GROUPS_COREx(x=0~2) 
It is the configured groups of all HW unit in each core.
*/
/* Total configured groups number in Core0 */
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_TOTAL_GROUPS_CORE0                             (11U)
/* Total configured groups number in Core1 */
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_TOTAL_GROUPS_CORE1                             (5U)

/* 
It is the configured groups in each ADC HW unit.
*/
/* Configured groups for SARADC0 */
#define ADC_CFG_GROUPS_HWUNIT_ADC0                         (4U)
/* Configured groups for SARADC1 */
#define ADC_CFG_GROUPS_HWUNIT_ADC1                         (3U)
/* Configured groups for SARADC2 */
#define ADC_CFG_GROUPS_HWUNIT_ADC2                         (5U)
/* Configured groups for SARADC8 */
#define ADC_CFG_GROUPS_HWUNIT_ADC8                         (4U)

/* Macro indicating the total number of request sources used by the driver */
#define ADC_REQSRC_COUNT                                   (3U)

/* ADC HW unit mapped to Core0 */
#define ADC_MAX_HWUNIT_TO_CORE0                            (3U)
/* ADC HW unit mapped to Core1 */
#define ADC_MAX_HWUNIT_TO_CORE1                            (1U)

/* Interrupt enabled flag */
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC0                           (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC0_RS0                       (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC0_RS1                       (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC0_RS2                       (STD_OFF)

/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC1                           (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC1_RS0                       (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC1_RS1                       (STD_OFF)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC1_RS2                       (STD_OFF)

/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC2                           (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC2_RS0                       (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC2_RS1                       (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC2_RS2                       (STD_ON)

/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC8                           (STD_OFF)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC8_RS0                       (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC8_RS1                       (STD_ON)
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_SARADC8_RS2                       (STD_OFF)

/* CHANNEL SYMBOLIC NAME */
/* Channel 'AN0', Pin is AN0: 
    Logical channel ID: 0 
    Hwunit ID: 0
    Physical Channel ID: 0 */
#ifndef AdcConf_AdcChannel_SignalName_AN0 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN0              (0x00U)
#endif /* AdcConf_AdcChannel_SignalName_AN0 */

/* Channel 'AN1', Pin is AN1: 
    Logical channel ID: 1 
    Hwunit ID: 0
    Physical Channel ID: 1 */
#ifndef AdcConf_AdcChannel_SignalName_AN1 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN1              (0x01U)
#endif /* AdcConf_AdcChannel_SignalName_AN1 */

/* Channel 'AN2', Pin is AN2: 
    Logical channel ID: 2 
    Hwunit ID: 0
    Physical Channel ID: 2 */
#ifndef AdcConf_AdcChannel_SignalName_AN2 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN2              (0x02U)
#endif /* AdcConf_AdcChannel_SignalName_AN2 */

/* Channel 'AN3', Pin is AN3: 
    Logical channel ID: 3 
    Hwunit ID: 0
    Physical Channel ID: 3 */
#ifndef AdcConf_AdcChannel_SignalName_AN3 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN3              (0x03U)
#endif /* AdcConf_AdcChannel_SignalName_AN3 */

/* Channel 'AN4', Pin is AN4: 
    Logical channel ID: 4 
    Hwunit ID: 0
    Physical Channel ID: 4 */
#ifndef AdcConf_AdcChannel_SignalName_AN4 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN4              (0x04U)
#endif /* AdcConf_AdcChannel_SignalName_AN4 */

/* Channel 'AN5', Pin is AN5: 
    Logical channel ID: 5 
    Hwunit ID: 0
    Physical Channel ID: 5 */
#ifndef AdcConf_AdcChannel_SignalName_AN5 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN5              (0x05U)
#endif /* AdcConf_AdcChannel_SignalName_AN5 */

/* Channel 'AN6', Pin is AN6: 
    Logical channel ID: 6 
    Hwunit ID: 0
    Physical Channel ID: 6 */
#ifndef AdcConf_AdcChannel_SignalName_AN6 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN6              (0x06U)
#endif /* AdcConf_AdcChannel_SignalName_AN6 */

/* Channel 'AN7', Pin is AN7: 
    Logical channel ID: 7 
    Hwunit ID: 0
    Physical Channel ID: 7 */
#ifndef AdcConf_AdcChannel_SignalName_AN7 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN7              (0x07U)
#endif /* AdcConf_AdcChannel_SignalName_AN7 */

/* Channel 'AN8', Pin is AN8: 
    Logical channel ID: 0 
    Hwunit ID: 1
    Physical Channel ID: 0 */
#ifndef AdcConf_AdcChannel_SignalName_AN8 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN8              (0x10U)
#endif /* AdcConf_AdcChannel_SignalName_AN8 */

/* Channel 'AN9', Pin is AN9: 
    Logical channel ID: 1 
    Hwunit ID: 1
    Physical Channel ID: 1 */
#ifndef AdcConf_AdcChannel_SignalName_AN9 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN9              (0x11U)
#endif /* AdcConf_AdcChannel_SignalName_AN9 */

/* Channel 'AN10', Pin is AN10: 
    Logical channel ID: 2 
    Hwunit ID: 1
    Physical Channel ID: 2 */
#ifndef AdcConf_AdcChannel_SignalName_AN10 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN10              (0x12U)
#endif /* AdcConf_AdcChannel_SignalName_AN10 */

/* Channel 'AN11', Pin is AN11: 
    Logical channel ID: 3 
    Hwunit ID: 1
    Physical Channel ID: 3 */
#ifndef AdcConf_AdcChannel_SignalName_AN11 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN11              (0x13U)
#endif /* AdcConf_AdcChannel_SignalName_AN11 */

/* Channel 'AN12', Pin is AN12: 
    Logical channel ID: 4 
    Hwunit ID: 1
    Physical Channel ID: 4 */
#ifndef AdcConf_AdcChannel_SignalName_AN12 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN12              (0x14U)
#endif /* AdcConf_AdcChannel_SignalName_AN12 */

/* Channel 'AN13', Pin is AN13: 
    Logical channel ID: 5 
    Hwunit ID: 1
    Physical Channel ID: 5 */
#ifndef AdcConf_AdcChannel_SignalName_AN13 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN13              (0x15U)
#endif /* AdcConf_AdcChannel_SignalName_AN13 */

/* Channel 'AN14', Pin is AN14: 
    Logical channel ID: 6 
    Hwunit ID: 1
    Physical Channel ID: 6 */
#ifndef AdcConf_AdcChannel_SignalName_AN14 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN14              (0x16U)
#endif /* AdcConf_AdcChannel_SignalName_AN14 */

/* Channel 'AN15', Pin is AN15: 
    Logical channel ID: 7 
    Hwunit ID: 1
    Physical Channel ID: 7 */
#ifndef AdcConf_AdcChannel_SignalName_AN15 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN15              (0x17U)
#endif /* AdcConf_AdcChannel_SignalName_AN15 */

/* Channel 'AN16', Pin is AN16: 
    Logical channel ID: 0 
    Hwunit ID: 2
    Physical Channel ID: 0 */
#ifndef AdcConf_AdcChannel_SignalName_AN16 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN16              (0x20U)
#endif /* AdcConf_AdcChannel_SignalName_AN16 */

/* Channel 'AN17', Pin is AN17: 
    Logical channel ID: 1 
    Hwunit ID: 2
    Physical Channel ID: 1 */
#ifndef AdcConf_AdcChannel_SignalName_AN17 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN17              (0x21U)
#endif /* AdcConf_AdcChannel_SignalName_AN17 */

/* Channel 'AN18', Pin is AN18: 
    Logical channel ID: 2 
    Hwunit ID: 2
    Physical Channel ID: 2 */
#ifndef AdcConf_AdcChannel_SignalName_AN18 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN18              (0x22U)
#endif /* AdcConf_AdcChannel_SignalName_AN18 */

/* Channel 'AN19', Pin is AN19: 
    Logical channel ID: 3 
    Hwunit ID: 2
    Physical Channel ID: 3 */
#ifndef AdcConf_AdcChannel_SignalName_AN19 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN19              (0x23U)
#endif /* AdcConf_AdcChannel_SignalName_AN19 */

/* Channel 'AN20', Pin is AN20: 
    Logical channel ID: 4 
    Hwunit ID: 2
    Physical Channel ID: 4 */
#ifndef AdcConf_AdcChannel_SignalName_AN20 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN20              (0x24U)
#endif /* AdcConf_AdcChannel_SignalName_AN20 */

/* Channel 'AN21', Pin is AN21: 
    Logical channel ID: 5 
    Hwunit ID: 2
    Physical Channel ID: 5 */
#ifndef AdcConf_AdcChannel_SignalName_AN21 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN21              (0x25U)
#endif /* AdcConf_AdcChannel_SignalName_AN21 */

/* Channel 'AN22', Pin is AN22: 
    Logical channel ID: 6 
    Hwunit ID: 2
    Physical Channel ID: 6 */
#ifndef AdcConf_AdcChannel_SignalName_AN22 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN22              (0x26U)
#endif /* AdcConf_AdcChannel_SignalName_AN22 */

/* Channel 'AN23', Pin is AN23: 
    Logical channel ID: 7 
    Hwunit ID: 2
    Physical Channel ID: 7 */
#ifndef AdcConf_AdcChannel_SignalName_AN23 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN23              (0x27U)
#endif /* AdcConf_AdcChannel_SignalName_AN23 */

/* Channel 'AN32', Pin is AN32_P40_4: 
    Logical channel ID: 0 
    Hwunit ID: 8
    Physical Channel ID: 0 */
#ifndef AdcConf_AdcChannel_SignalName_AN32 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN32              (0x80U)
#endif /* AdcConf_AdcChannel_SignalName_AN32 */

/* Channel 'AN33', Pin is AN33_P40_5: 
    Logical channel ID: 1 
    Hwunit ID: 8
    Physical Channel ID: 1 */
#ifndef AdcConf_AdcChannel_SignalName_AN33 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN33              (0x81U)
#endif /* AdcConf_AdcChannel_SignalName_AN33 */

/* Channel 'AN35', Pin is AN35: 
    Logical channel ID: 2 
    Hwunit ID: 8
    Physical Channel ID: 3 */
#ifndef AdcConf_AdcChannel_SignalName_AN35 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN35              (0x83U)
#endif /* AdcConf_AdcChannel_SignalName_AN35 */

/* Channel 'AN36', Pin is AN36_P40_6: 
    Logical channel ID: 3 
    Hwunit ID: 8
    Physical Channel ID: 4 */
#ifndef AdcConf_AdcChannel_SignalName_AN36 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN36              (0x84U)
#endif /* AdcConf_AdcChannel_SignalName_AN36 */

/* Channel 'AN37', Pin is AN37_P40_7: 
    Logical channel ID: 4 
    Hwunit ID: 8
    Physical Channel ID: 5 */
#ifndef AdcConf_AdcChannel_SignalName_AN37 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN37              (0x85U)
#endif /* AdcConf_AdcChannel_SignalName_AN37 */

/* Channel 'AN38', Pin is AN38_P40_8: 
    Logical channel ID: 5 
    Hwunit ID: 8
    Physical Channel ID: 6 */
#ifndef AdcConf_AdcChannel_SignalName_AN38 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN38              (0x86U)
#endif /* AdcConf_AdcChannel_SignalName_AN38 */

/* Channel 'AN39', Pin is AN39_P40_9: 
    Logical channel ID: 6 
    Hwunit ID: 8
    Physical Channel ID: 7 */
#ifndef AdcConf_AdcChannel_SignalName_AN39 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN39              (0x87U)
#endif /* AdcConf_AdcChannel_SignalName_AN39 */

/* Channel 'AN34', Pin is AN34: 
    Logical channel ID: 7 
    Hwunit ID: 8
    Physical Channel ID: 2 */
#ifndef AdcConf_AdcChannel_SignalName_AN34 /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_AN34              (0x82U)
#endif /* AdcConf_AdcChannel_SignalName_AN34 */

/* CHANNEL SYMBOLIC NAME */
/* ADC Channel 'AN0' ID in HWTrigDemo: 0 */
#ifndef AdcConf_AdcChannel_AN0 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN0              ((Adc_ChannelType)0)
#endif /* AdcConf_AdcChannel_AN0 */

/* ADC Channel 'AN1' ID in HWTrigDemo: 1 */
#ifndef AdcConf_AdcChannel_AN1 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN1              ((Adc_ChannelType)1)
#endif /* AdcConf_AdcChannel_AN1 */

/* ADC Channel 'AN2' ID in HWTrigDemo: 2 */
#ifndef AdcConf_AdcChannel_AN2 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN2              ((Adc_ChannelType)2)
#endif /* AdcConf_AdcChannel_AN2 */

/* ADC Channel 'AN3' ID in HWTrigDemo: 3 */
#ifndef AdcConf_AdcChannel_AN3 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN3              ((Adc_ChannelType)3)
#endif /* AdcConf_AdcChannel_AN3 */

/* ADC Channel 'AN4' ID in HWTrigDemo: 4 */
#ifndef AdcConf_AdcChannel_AN4 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN4              ((Adc_ChannelType)4)
#endif /* AdcConf_AdcChannel_AN4 */

/* ADC Channel 'AN5' ID in HWTrigDemo: 5 */
#ifndef AdcConf_AdcChannel_AN5 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN5              ((Adc_ChannelType)5)
#endif /* AdcConf_AdcChannel_AN5 */

/* ADC Channel 'AN6' ID in HWTrigDemo: 6 */
#ifndef AdcConf_AdcChannel_AN6 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN6              ((Adc_ChannelType)6)
#endif /* AdcConf_AdcChannel_AN6 */

/* ADC Channel 'AN7' ID in HWTrigDemo: 7 */
#ifndef AdcConf_AdcChannel_AN7 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN7              ((Adc_ChannelType)7)
#endif /* AdcConf_AdcChannel_AN7 */

/* ADC Channel 'AN8' ID in DmaTransferDemo: 0 */
#ifndef AdcConf_AdcChannel_AN8 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN8              ((Adc_ChannelType)0)
#endif /* AdcConf_AdcChannel_AN8 */

/* ADC Channel 'AN9' ID in DmaTransferDemo: 1 */
#ifndef AdcConf_AdcChannel_AN9 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN9              ((Adc_ChannelType)1)
#endif /* AdcConf_AdcChannel_AN9 */

/* ADC Channel 'AN10' ID in DmaTransferDemo: 2 */
#ifndef AdcConf_AdcChannel_AN10 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN10              ((Adc_ChannelType)2)
#endif /* AdcConf_AdcChannel_AN10 */

/* ADC Channel 'AN11' ID in DmaTransferDemo: 3 */
#ifndef AdcConf_AdcChannel_AN11 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN11              ((Adc_ChannelType)3)
#endif /* AdcConf_AdcChannel_AN11 */

/* ADC Channel 'AN12' ID in DmaTransferDemo: 4 */
#ifndef AdcConf_AdcChannel_AN12 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN12              ((Adc_ChannelType)4)
#endif /* AdcConf_AdcChannel_AN12 */

/* ADC Channel 'AN13' ID in DmaTransferDemo: 5 */
#ifndef AdcConf_AdcChannel_AN13 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN13              ((Adc_ChannelType)5)
#endif /* AdcConf_AdcChannel_AN13 */

/* ADC Channel 'AN14' ID in DmaTransferDemo: 6 */
#ifndef AdcConf_AdcChannel_AN14 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN14              ((Adc_ChannelType)6)
#endif /* AdcConf_AdcChannel_AN14 */

/* ADC Channel 'AN15' ID in DmaTransferDemo: 7 */
#ifndef AdcConf_AdcChannel_AN15 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN15              ((Adc_ChannelType)7)
#endif /* AdcConf_AdcChannel_AN15 */

/* ADC Channel 'AN16' ID in SWTrigDemo: 0 */
#ifndef AdcConf_AdcChannel_AN16 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN16              ((Adc_ChannelType)0)
#endif /* AdcConf_AdcChannel_AN16 */

/* ADC Channel 'AN17' ID in SWTrigDemo: 1 */
#ifndef AdcConf_AdcChannel_AN17 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN17              ((Adc_ChannelType)1)
#endif /* AdcConf_AdcChannel_AN17 */

/* ADC Channel 'AN18' ID in SWTrigDemo: 2 */
#ifndef AdcConf_AdcChannel_AN18 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN18              ((Adc_ChannelType)2)
#endif /* AdcConf_AdcChannel_AN18 */

/* ADC Channel 'AN19' ID in SWTrigDemo: 3 */
#ifndef AdcConf_AdcChannel_AN19 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN19              ((Adc_ChannelType)3)
#endif /* AdcConf_AdcChannel_AN19 */

/* ADC Channel 'AN20' ID in SWTrigDemo: 4 */
#ifndef AdcConf_AdcChannel_AN20 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN20              ((Adc_ChannelType)4)
#endif /* AdcConf_AdcChannel_AN20 */

/* ADC Channel 'AN21' ID in SWTrigDemo: 5 */
#ifndef AdcConf_AdcChannel_AN21 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN21              ((Adc_ChannelType)5)
#endif /* AdcConf_AdcChannel_AN21 */

/* ADC Channel 'AN22' ID in SWTrigDemo: 6 */
#ifndef AdcConf_AdcChannel_AN22 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN22              ((Adc_ChannelType)6)
#endif /* AdcConf_AdcChannel_AN22 */

/* ADC Channel 'AN23' ID in SWTrigDemo: 7 */
#ifndef AdcConf_AdcChannel_AN23 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN23              ((Adc_ChannelType)7)
#endif /* AdcConf_AdcChannel_AN23 */

/* ADC Channel 'AN32' ID in PollingModeDemo: 0 */
#ifndef AdcConf_AdcChannel_AN32 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN32              ((Adc_ChannelType)0)
#endif /* AdcConf_AdcChannel_AN32 */

/* ADC Channel 'AN33' ID in PollingModeDemo: 1 */
#ifndef AdcConf_AdcChannel_AN33 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN33              ((Adc_ChannelType)1)
#endif /* AdcConf_AdcChannel_AN33 */

/* ADC Channel 'AN35' ID in PollingModeDemo: 2 */
#ifndef AdcConf_AdcChannel_AN35 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN35              ((Adc_ChannelType)2)
#endif /* AdcConf_AdcChannel_AN35 */

/* ADC Channel 'AN36' ID in PollingModeDemo: 3 */
#ifndef AdcConf_AdcChannel_AN36 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN36              ((Adc_ChannelType)3)
#endif /* AdcConf_AdcChannel_AN36 */

/* ADC Channel 'AN37' ID in PollingModeDemo: 4 */
#ifndef AdcConf_AdcChannel_AN37 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN37              ((Adc_ChannelType)4)
#endif /* AdcConf_AdcChannel_AN37 */

/* ADC Channel 'AN38' ID in PollingModeDemo: 5 */
#ifndef AdcConf_AdcChannel_AN38 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN38              ((Adc_ChannelType)5)
#endif /* AdcConf_AdcChannel_AN38 */

/* ADC Channel 'AN39' ID in PollingModeDemo: 6 */
#ifndef AdcConf_AdcChannel_AN39 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN39              ((Adc_ChannelType)6)
#endif /* AdcConf_AdcChannel_AN39 */

/* ADC Channel 'AN34' ID in PollingModeDemo: 7 */
#ifndef AdcConf_AdcChannel_AN34 /* to prevent double declaration */
#define AdcConf_AdcChannel_AN34              ((Adc_ChannelType)7)
#endif /* AdcConf_AdcChannel_AN34 */

/* GROUP SYMBOLIC NAME */
/* ADC Group 'GroupHwTrig' ID in HWTrigDemo: 0 */
#ifndef AdcConf_AdcGroup_GroupHwTrig /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupHwTrig                ((Adc_GroupType)0)
#endif /* AdcConf_AdcGroup_GroupHwTrig */

/* ADC Group 'GroupHwTrigStreaming' ID in HWTrigDemo: 1 */
#ifndef AdcConf_AdcGroup_GroupHwTrigStreaming /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupHwTrigStreaming                ((Adc_GroupType)1)
#endif /* AdcConf_AdcGroup_GroupHwTrigStreaming */

/* ADC Group 'GroupHwResultAccumulation' ID in HWTrigDemo: 2 */
#ifndef AdcConf_AdcGroup_GroupHwResultAccumulation /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupHwResultAccumulation                ((Adc_GroupType)2)
#endif /* AdcConf_AdcGroup_GroupHwResultAccumulation */

/* ADC Group 'GroupSyncConv' ID in HWTrigDemo: 3 */
#ifndef AdcConf_AdcGroup_GroupSyncConv /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupSyncConv                ((Adc_GroupType)3)
#endif /* AdcConf_AdcGroup_GroupSyncConv */

/* ADC Group 'GroupSwTrig' ID in DmaTransferDemo: 32 */
#ifndef AdcConf_AdcGroup_GroupSwTrig /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupSwTrig                ((Adc_GroupType)32)
#endif /* AdcConf_AdcGroup_GroupSwTrig */

/* ADC Group 'GroupSwTrig_DmaLinkedList' ID in DmaTransferDemo: 33 */
#ifndef AdcConf_AdcGroup_GroupSwTrig_DmaLinkedList /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupSwTrig_DmaLinkedList                ((Adc_GroupType)33)
#endif /* AdcConf_AdcGroup_GroupSwTrig_DmaLinkedList */

/* ADC Group 'GroupSwTrig_ResRegConf' ID in DmaTransferDemo: 34 */
#ifndef AdcConf_AdcGroup_GroupSwTrig_ResRegConf /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupSwTrig_ResRegConf                ((Adc_GroupType)34)
#endif /* AdcConf_AdcGroup_GroupSwTrig_ResRegConf */

/* ADC Group 'GroupContinuous' ID in SWTrigDemo: 64 */
#ifndef AdcConf_AdcGroup_GroupContinuous /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupContinuous                ((Adc_GroupType)64)
#endif /* AdcConf_AdcGroup_GroupContinuous */

/* ADC Group 'GroupLimitCheck' ID in SWTrigDemo: 65 */
#ifndef AdcConf_AdcGroup_GroupLimitCheck /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupLimitCheck                ((Adc_GroupType)65)
#endif /* AdcConf_AdcGroup_GroupLimitCheck */

/* ADC Group 'GroupOneShot' ID in SWTrigDemo: 66 */
#ifndef AdcConf_AdcGroup_GroupOneShot /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupOneShot                ((Adc_GroupType)66)
#endif /* AdcConf_AdcGroup_GroupOneShot */

/* ADC Group 'GroupStreaming' ID in SWTrigDemo: 67 */
#ifndef AdcConf_AdcGroup_GroupStreaming /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupStreaming                ((Adc_GroupType)67)
#endif /* AdcConf_AdcGroup_GroupStreaming */

/* ADC Group 'GroupSwResultAccumulation' ID in SWTrigDemo: 68 */
#ifndef AdcConf_AdcGroup_GroupSwResultAccumulation /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupSwResultAccumulation                ((Adc_GroupType)68)
#endif /* AdcConf_AdcGroup_GroupSwResultAccumulation */

/* ADC Group 'GroupHwPolling' ID in PollingModeDemo: 256 */
#ifndef AdcConf_AdcGroup_GroupHwPolling /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupHwPolling                ((Adc_GroupType)256)
#endif /* AdcConf_AdcGroup_GroupHwPolling */

/* ADC Group 'GroupHwStreaming' ID in PollingModeDemo: 257 */
#ifndef AdcConf_AdcGroup_GroupHwStreaming /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupHwStreaming                ((Adc_GroupType)257)
#endif /* AdcConf_AdcGroup_GroupHwStreaming */

/* ADC Group 'GroupSwPolling' ID in PollingModeDemo: 258 */
#ifndef AdcConf_AdcGroup_GroupSwPolling /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupSwPolling                ((Adc_GroupType)258)
#endif /* AdcConf_AdcGroup_GroupSwPolling */

/* ADC Group 'GroupSwStreaming' ID in PollingModeDemo: 259 */
#ifndef AdcConf_AdcGroup_GroupSwStreaming /* to prevent double declaration */
#define AdcConf_AdcGroup_GroupSwStreaming                ((Adc_GroupType)259)
#endif /* AdcConf_AdcGroup_GroupSwStreaming */

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
#endif  /* ADC_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

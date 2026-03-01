/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Sent_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : SENT
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
*#Sent_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*/

#ifndef SENT_CFG_H_
#define SENT_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* AUTOSAR specification version numbers */
#define SENT_CFG_AR_RELEASE_MAJOR_VERSION  (4U)
#define SENT_CFG_AR_RELEASE_MINOR_VERSION  (4U)
#define SENT_CFG_AR_RELEASE_PATCH_VERSION  (0U)


/* Vendor specific implementation version information */
#define SENT_CFG_SW_MAJOR_VERSION              (1U)
#define SENT_CFG_SW_MINOR_VERSION              (2U)
#define SENT_CFG_SW_PATCH_VERSION              (0U)

#define SENT_CFG_VENDOR_ID                 (175U)
#define SENT_CFG_MODULE_ID                 (255U)

/*
Container : SentGeneralConfiguration
*/
/*
The following macros will enable or disable a particular feature
in SENT module.
Set the macro to ON to enable the feature and OFF to disable the same.
*/
/*
Configuration: SENT_SAFETY_ENABLE
Preprocessor switch for enabling the safety development error detection and
reporting.
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
*/
#define SENT_SAFETY_ENABLE  (STD_ON)
/*
Configuration: SENT_DEV_ERROR_DETECT
Preprocessor switch for enabling the development error detection and
reporting.
- if STD_ON, DET is Enabled
- if STD_OFF,DET is Disabled
*/
#define SENT_DEV_ERROR_DETECT  (STD_ON)
/* Configuration: SENT_DEINIT_API
Sent_DeInit API configuration
- if STD_ON, DeInit API is Enabled
- if STD_OFF, DeInit API is Disabled
*/
#define SENT_DEINIT_API        (STD_ON)

/* Configuration: SENT_VERSION_INFO_API
Version Information API configuration
- if STD_ON, VersionInfo API is Enabled
- if STD_OFF, VersionInfo API is Disabled
*/
#define SENT_VERSION_INFO_API  (STD_ON)

/* Configuration: SENT_SPC_USED
SENT SPC Feature configuration
- if STD_ON, SPC feature is Enabled
- if STD_OFF, SPC feature is Disabled
*/
#define SENT_SPC_USED         (STD_ON)

/* Configuration: SENT_HW_MAX_CHANNELS
Maximum number of SENT physical channels supported
*/
#define SENT_HW_MAX_CHANNELS   (10U)

/* Configuration: SENT MODULE INSTANCE ID */
/* #Violation: Sent_Cfg_h_REF_1 */
#define SENT_INSTANCE_ID       ((uint8)0)

/* Total no. of config sets */
/* #Violation: Sent_Cfg_h_REF_1 */
#define SENT_CONFIG_COUNT    (1U)


/* Configuration: Resource
The configuration contains allocation of Sent channels across cores.
- if STD_ON, atleast one sent channel is configured in the core.
- if STD_OFF, no sent channels are configured in the core. */

/* #Violation: Sent_Cfg_h_REF_1 */
#define SENT_CONFIGURED_CORE0                              (STD_ON)

/* #Violation: Sent_Cfg_h_REF_1 */
#define SENT_CONFIGURED_CORE1                              (STD_ON)


/*
Configuration:Max channels configured for Sent, max channels are same across
variants.
*/

/* Sent Max Channels macro */
#define SENT_MAX_CHANNELS_CONFIGURED         ((Sent_ChannelIdxType)6)
/* Number of Cores confgiured for Sent */
/* #Violation: Sent_Cfg_h_REF_1 */
#define MASTER_CORE_ID           0U
/* #Violation: Sent_Cfg_h_REF_1 */
#define SENT_CHANNEL_COUNT_CORE1           3U

/* #Violation: Sent_Cfg_h_REF_1 */
#define SENT_CHANNEL_COUNT_CORE0       4U
/* #Violation: Sent_Cfg_h_REF_1 */
#define SENT_MAX_CHANNELS_MASTER_CORE     4U
/* The physical sent channels used. */
#define SENT_INST0_CHAN0                  (STD_OFF)
#define SENT_INST0_CHAN1                  (STD_OFF)
#define SENT_INST0_CHAN2                  (STD_ON)
#define SENT_INST0_CHAN3                  (STD_ON)
#define SENT_INST0_CHAN4                  (STD_OFF)
#define SENT_INST0_CHAN5                  (STD_ON)
#define SENT_INST0_CHAN6                  (STD_ON)
#define SENT_INST0_CHAN7                  (STD_ON)
#define SENT_INST0_CHAN8                  (STD_OFF)
#define SENT_INST0_CHAN9                  (STD_ON)

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
#endif  /* SENT_CFG_H */
/****************************************************************************************************
 **                          End of File                                                            *
 ***************************************************************************************************/


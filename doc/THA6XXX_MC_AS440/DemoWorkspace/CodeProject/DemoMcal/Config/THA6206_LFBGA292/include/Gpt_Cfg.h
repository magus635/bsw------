/****************************************************************************************************
*   FileName              : Gpt_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, BASETIMER
*
*   brief                 : This file contains all post-build parameters in GPT Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx  
*           
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Gpt_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#ifndef GPT_CFG_H_
#define GPT_CFG_H_

/****************************************************************************************************
**                               Version Information                                               **
****************************************************************************************************/
/* AUTOSAR release version information */
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION                             (4U)
#define GPT_CFG_AR_RELEASE_MINOR_VERSION                             (4U)
#define GPT_CFG_AR_RELEASE_REVISION_VERSION                          (0U)
/* GPT module software release version information */
#define GPT_CFG_SW_MAJOR_VERSION                                     (1U)
#define GPT_CFG_SW_MINOR_VERSION                                     (2U)
#define GPT_CFG_SW_PATCH_VERSION                                     (0U)
/* Vendor ID */
#define GPT_CFG_VENDOR_ID                                            (175U)
#define GPT_CFG_MODULE_ID                                            (100U)

/****************************************************************************************************
**                                   API Information                                               **
****************************************************************************************************/
/*
Configuration: GPT_GET_VERSION_INFO_API
Adds/removes the service Gpt_GetVersionInfo() from the code
- if STD_ON, Gpt_GetVersionInfo() can be used
- if STD_OFF, Gpt_GetVersionInfo() can not be used
*/
#define GPT_GET_VERSION_INFO_API                                     (STD_ON)
/*
Configuration: GPT_DE_INIT_API
Adds/removes the service Gpt_DeInit() from the code
- if STD_ON, Gpt_DeInit() can be used
- if STD_OFF, Gpt_DeInit() can not be used
*/
#define GPT_DE_INIT_API                                              (STD_ON)
/*
Configuration: GPT_TIME_ELAPSED_API
Adds/removes the service Gpt_GetTimeElapsed() from the code
- if STD_ON, Gpt_GetTimeElapsed() can be used
- if STD_OFF, Gpt_GetTimeElapsed() can not be used
*/
#define GPT_TIME_ELAPSED_API                                         (STD_ON)
/*
Configuration: GPT_TIME_REMAINING_API
Adds/removes the service Gpt_GetTimeRemaining() from the code
- if STD_ON, Gpt_GetTimeRemaining() can be used
- if STD_OFF, Gpt_GetTimeRemaining() can not be used
*/
#define GPT_TIME_REMAINING_API                                       (STD_ON)
/*
Configuration: GPT_ENABLE_DISABLE_NOTIFICATION_API
Adds/removes the service Gpt_EnableNotification() and Gpt_DisableNotification
from the code
- if STD_ON, Gpt_EnableNotification() and Gpt_DisableNotification  can be used
- if STD_OFF, Gpt_EnableNotification() and Gpt_DisableNotification  can not be
used
*/
#define GPT_ENABLE_DISABLE_NOTIFICATION_API                          (STD_ON)
/*
Configuration: GPT_WAKEUP_FUNCTIONALITY_API
Adds/removes the service Gpt_SetMode(), Gpt_EnableWakeup(),
Gpt_DisableWakeup() and Gpt_CheckWakeup() from the code
- if STD_ON, Gpt_SetMode(), Gpt_EnableWakeup(), Gpt_DisableWakeup() and
Gpt_CheckWakeup() can be used
- if STD_OFF, Gpt_SetMode(), Gpt_EnableWakeup(), Gpt_DisableWakeup() and
Gpt_CheckWakeup() can not be used
*/
#define GPT_WAKEUP_FUNCTIONALITY_API                                 (STD_OFF)

/*******************************************************************************
**                          Gpt Channel Symbolic Names                        **
*******************************************************************************/
/* Gpt Channel Symbolic Name for Channel Configuration. */
/* Symbolic Name of GptChannelConfiguration_0 */
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_0
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_0  \
((Gpt_ChannelType)0U)
#endif

/* Symbolic Name of GptChannelConfiguration_1 */
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_1
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_1  \
((Gpt_ChannelType)1U)
#endif

/* Symbolic Name of GptChannelConfiguration_2 */
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_2
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_2  \
((Gpt_ChannelType)2U)
#endif

/* Symbolic Name of GptChannelConfiguration_3 */
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_3
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_3  \
((Gpt_ChannelType)3U)
#endif

/* Symbolic Name of GptChannelConfiguration_6 */
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_6
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_6  \
((Gpt_ChannelType)4U)
#endif

/* Symbolic Name of GptChannelConfiguration_7 */
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_7
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_7  \
((Gpt_ChannelType)5U)
#endif

/* Symbolic Name of GptChannelConfiguration_8 */
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_8
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_8  \
((Gpt_ChannelType)6U)
#endif

/* Symbolic Name of GptChannelConfiguration_9 */
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_9
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_9  \
((Gpt_ChannelType)7U)
#endif

/* Symbolic Name of GptChannelConfiguration_10 */
#ifndef GptConf_GptChannelConfiguration_GptChannelConfiguration_10
#define GptConf_GptChannelConfiguration_GptChannelConfiguration_10  \
((Gpt_ChannelType)8U)
#endif

/* Symbolic Name of GptForMcu_SetMode */
#ifndef GptConf_GptChannelConfiguration_GptForMcu_SetMode
#define GptConf_GptChannelConfiguration_GptForMcu_SetMode  \
((Gpt_ChannelType)9U)
#endif


/****************************************************************************************************
**                          Functional Control Information                                         **
****************************************************************************************************/
/*
Configuration: GPT_DEV_ERROR_DETECT
Preprocessor switch to enable/disable the development error detection and
reporting.
- if STD_ON, Enable development error detection
- if STD_OFF, Disable development error detection
*/
#define GPT_DEV_ERROR_DETECT                                         (STD_ON)
/*
Configuration: GPT_REPORT_WAKEUP_SOURCE
Preprocessor switch to enable/disable the wakeup source report.
- if STD_ON, Enable the wakeup source report.
- if STD_OFF, Disable the wakeup source report.
*/
/* #Violation: Gpt_Cfg_h_REF_1 */
#define GPT_REPORT_WAKEUP_SOURCE                                     (STD_OFF)

/*
Configuration: GPT_PREDEF_TIMER_100US_32BIT_EN
Preprocessor switch to enable/disable the GPT Predefine Timer 100us 32bit.
- if STD_ON, Enable 100us 32bit predefine timer
- if STD_OFF, Disable 100us 32bit predefine timer
*/
#define GPT_PREDEF_TIMER_100US_32BIT_EN                              (STD_ON)    
#define GPT_PREDEF_TIMER_1US_16BIT_EN                                (STD_OFF)
#define GPT_PREDEF_TIMER_1US_24BIT_EN                                (STD_OFF)
#define GPT_PREDEF_TIMER_1US_32BIT_EN                                (STD_ON)

/* Type of predefine timer 1Us */
#define GPT_PREDEFTIMER_1US_TYPE                                     (GPT_PREDEF_TIMER_1US_32BIT)

/* GPT channel mapped to Core0 */
#define GPT_MAX_CHANNEL_TO_CORE0                                     (6U)
/* GPT channel mapped to Core1 */
#define GPT_MAX_CHANNEL_TO_CORE1                                     (4U)
/* GPT channel mapped to Core2 */
#define GPT_MAX_CHANNEL_TO_CORE2                                     (0U)
/* GPT channel mapped to Core3 */
#define GPT_MAX_CHANNEL_TO_CORE3                                     (0U)
/* Number of channels configured as regular channel */
#define GPT_MAX_CHANNELS                                             (10U)
/* Safety check enable status */
#define GPT_SAFETY_ENABLE                                            (STD_ON)

#endif /* GPT_CFG_H_ */

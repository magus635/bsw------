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
[!NOCODE!][!//
[!INCLUDE "Gpt.m"!][!//
[!ENDNOCODE!][!//

[!INDENT "0"!][!//
/****************************************************************************************************
**                               Version Information                                               **
****************************************************************************************************/
[!AUTOSPACING!]
/* AUTOSAR release version information */
#define GPT_CFG_AR_RELEASE_MAJOR_VERSION                             ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define GPT_CFG_AR_RELEASE_MINOR_VERSION                             ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define GPT_CFG_AR_RELEASE_REVISION_VERSION                          ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)
/* GPT module software release version information */
#define GPT_CFG_SW_MAJOR_VERSION                                     ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define GPT_CFG_SW_MINOR_VERSION                                     ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define GPT_CFG_SW_PATCH_VERSION                                     ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)
/* Vendor ID */
#define GPT_CFG_VENDOR_ID                                            ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define GPT_CFG_MODULE_ID                                            ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/****************************************************************************************************
**                                   API Information                                               **
****************************************************************************************************/
/*
Configuration: GPT_GET_VERSION_INFO_API
Adds/removes the service Gpt_GetVersionInfo() from the code
- if STD_ON, Gpt_GetVersionInfo() can be used
- if STD_OFF, Gpt_GetVersionInfo() can not be used
*/
#define GPT_GET_VERSION_INFO_API                                     ([!//
    [!IF "GptConfigurationOfOptApiServices/GptVersionInfoApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
/*
Configuration: GPT_DE_INIT_API
Adds/removes the service Gpt_DeInit() from the code
- if STD_ON, Gpt_DeInit() can be used
- if STD_OFF, Gpt_DeInit() can not be used
*/
#define GPT_DE_INIT_API                                              ([!//
    [!IF "GptConfigurationOfOptApiServices/GptDeinitApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
/*
Configuration: GPT_TIME_ELAPSED_API
Adds/removes the service Gpt_GetTimeElapsed() from the code
- if STD_ON, Gpt_GetTimeElapsed() can be used
- if STD_OFF, Gpt_GetTimeElapsed() can not be used
*/
#define GPT_TIME_ELAPSED_API                                         ([!//
    [!IF "GptConfigurationOfOptApiServices/GptTimeElapsedApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
/*
Configuration: GPT_TIME_REMAINING_API
Adds/removes the service Gpt_GetTimeRemaining() from the code
- if STD_ON, Gpt_GetTimeRemaining() can be used
- if STD_OFF, Gpt_GetTimeRemaining() can not be used
*/
#define GPT_TIME_REMAINING_API                                       ([!//
    [!IF "GptConfigurationOfOptApiServices/GptTimeRemainingApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
/*
Configuration: GPT_ENABLE_DISABLE_NOTIFICATION_API
Adds/removes the service Gpt_EnableNotification() and Gpt_DisableNotification
from the code
- if STD_ON, Gpt_EnableNotification() and Gpt_DisableNotification  can be used
- if STD_OFF, Gpt_EnableNotification() and Gpt_DisableNotification  can not be
used
*/
#define GPT_ENABLE_DISABLE_NOTIFICATION_API                          ([!//
    [!IF "GptConfigurationOfOptApiServices/GptEnableDisableNotificationApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
/*
Configuration: GPT_WAKEUP_FUNCTIONALITY_API
Adds/removes the service Gpt_SetMode(), Gpt_EnableWakeup(),
Gpt_DisableWakeup() and Gpt_CheckWakeup() from the code
- if STD_ON, Gpt_SetMode(), Gpt_EnableWakeup(), Gpt_DisableWakeup() and
  Gpt_CheckWakeup() can be used
- if STD_OFF, Gpt_SetMode(), Gpt_EnableWakeup(), Gpt_DisableWakeup() and
  Gpt_CheckWakeup() can not be used
*/
#define GPT_WAKEUP_FUNCTIONALITY_API                                 ([!//
    [!IF "GptConfigurationOfOptApiServices/GptWakeupFunctionalityApi = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

/*******************************************************************************
**                          Gpt Channel Symbolic Names                        **
*******************************************************************************/
/* Gpt Channel Symbolic Name for Channel Configuration. */
[!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
  [!IF "GptTimerChannelUsage = 'GPT_TIMER_CHANNEL_NORMAL'"!][!//
/* Symbolic Name of [!"@name"!] */
#ifndef GptConf_GptChannelConfiguration_[!"@name"!]
#define GptConf_GptChannelConfiguration_[!"@name"!]  \
((Gpt_ChannelType)[!"./GptChannelId"!]U)
#endif

  [!ENDIF!][!//
[!ENDLOOP!][!//  

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
#define GPT_DEV_ERROR_DETECT                                         ([!//
    [!IF "GptDriverConfiguration/GptDevErrorDetect = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )
/*
Configuration: GPT_REPORT_WAKEUP_SOURCE
Preprocessor switch to enable/disable the wakeup source report.
- if STD_ON, Enable the wakeup source report.
- if STD_OFF, Disable the wakeup source report.
*/
/* #Violation: Gpt_Cfg_h_REF_1 */
#define GPT_REPORT_WAKEUP_SOURCE                                     ([!//
    [!IF "GptDriverConfiguration/GptReportWakeupSource = 'true'"!][!//
      STD_ON[!//
    [!ELSE!][!//
      STD_OFF[!//
    [!ENDIF!][!//
    )

/*
Configuration: GPT_PREDEF_TIMER_100US_32BIT_EN
Preprocessor switch to enable/disable the GPT Predefine Timer 100us 32bit.
- if STD_ON, Enable 100us 32bit predefine timer
- if STD_OFF, Disable 100us 32bit predefine timer
*/
[!VAR "GptPredefTimer100us" = "GptDriverConfiguration/GptPredefTimer100us32bitEnable"!][!//
  [!IF "$GptPredefTimer100us = 'true'"!][!//
      #define GPT_PREDEF_TIMER_100US_32BIT_EN                              (STD_ON)    [!//
  [!ELSE!][!//
      #define GPT_PREDEF_TIMER_100US_32BIT_EN                              (STD_OFF)    [!//
  [!ENDIF!][!//

      [!VAR "GptPredefTimer1us" = "GptDriverConfiguration/GptPredefTimer1usEnablingGrade"!][!//
      [!IF "$GptPredefTimer1us = 'GPT_PREDEF_TIMER_1US_DISABLED'"!][!//
        #define GPT_PREDEF_TIMER_1US_16BIT_EN                                (STD_OFF)
        #define GPT_PREDEF_TIMER_1US_24BIT_EN                                (STD_OFF)
        #define GPT_PREDEF_TIMER_1US_32BIT_EN                                (STD_OFF)
      [!ELSEIF "$GptPredefTimer1us = 'GPT_PREDEF_TIMER_1US_16BIT_ENABLED'"!][!//
        #define GPT_PREDEF_TIMER_1US_16BIT_EN                                (STD_ON)
        #define GPT_PREDEF_TIMER_1US_24BIT_EN                                (STD_OFF)
        #define GPT_PREDEF_TIMER_1US_32BIT_EN                                (STD_OFF)
      [!ELSEIF "$GptPredefTimer1us = 'GPT_PREDEF_TIMER_1US_16_24BIT_ENABLED'"!][!//
        #define GPT_PREDEF_TIMER_1US_16BIT_EN                                (STD_OFF)
        #define GPT_PREDEF_TIMER_1US_24BIT_EN                                (STD_ON)
        #define GPT_PREDEF_TIMER_1US_32BIT_EN                                (STD_OFF)
      [!ELSEIF "$GptPredefTimer1us = 'GPT_PREDEF_TIMER_1US_16_24_32BIT_ENABLED'"!][!//
        #define GPT_PREDEF_TIMER_1US_16BIT_EN                                (STD_OFF)
        #define GPT_PREDEF_TIMER_1US_24BIT_EN                                (STD_OFF)
        #define GPT_PREDEF_TIMER_1US_32BIT_EN                                (STD_ON)
      [!ENDIF!][!//
         [!NOCODE!][!//
        [!IF "contains($GptPredefTimer1us, 'ENABLED')"!][!//
          [!VAR "GptPredefTimer1usStat" = "'true'"!][!//
        [!ELSE!][!//
          [!VAR "GptPredefTimer1usStat" = "'false'"!][!//
        [!ENDIF!][!//
      [!ENDNOCODE!][!//
[!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*[./GptTimerChannelUsage != 'GPT_TIMER_CHANNEL_NORMAL'], 'GptChannelId')"!][!//
  [!VAR "ChannelUsage" = "./GptTimerChannelUsage"!][!//
  [!IF "contains($ChannelUsage, '1US')"!][!//
    [!/* Find 1us channel type */!][!//
    [!IF "contains($ChannelUsage,'16BIT')"!][!//
      [!VAR "Predef1USType" = "'GPT_PREDEF_TIMER_1US_16BIT'"!][!//
    [!ELSEIF "contains($ChannelUsage,'24BIT')"!][!//
      [!VAR "Predef1USType" = "'GPT_PREDEF_TIMER_1US_24BIT'"!][!//
    [!ELSE!][!//
      [!VAR "Predef1USType" = "'GPT_PREDEF_TIMER_1US_32BIT'"!][!//
    [!ENDIF!][!//
    [!BREAK!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//

[!IF "'GPT_PREDEF_TIMER_1US_DISABLED' != GptDriverConfiguration/GptPredefTimer1usEnablingGrade"!][!//
/* Type of predefine timer 1Us */
#define GPT_PREDEFTIMER_1US_TYPE                                     ([!"$Predef1USType"!])
[!ENDIF!][!//

/* GPT channel mapped to Core0 */
#define GPT_MAX_CHANNEL_TO_CORE0                                     ([!"num:i($GptChannelMappedCore0)"!]U)
/* GPT channel mapped to Core1 */
#define GPT_MAX_CHANNEL_TO_CORE1                                     ([!"num:i($GptChannelMappedCore1)"!]U)
/* GPT channel mapped to Core2 */
#define GPT_MAX_CHANNEL_TO_CORE2                                     ([!"num:i($GptChannelMappedCore2)"!]U)
/* GPT channel mapped to Core3 */
#define GPT_MAX_CHANNEL_TO_CORE3                                     ([!"num:i($GptChannelMappedCore3)"!]U)
[!VAR "NormalChannelNumbers" = "0"!][!//
[!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
  [!VAR "TimerChannelUsage" = "./GptTimerChannelUsage"!][!//
  [!IF "contains($TimerChannelUsage, 'NORMAL')"!][!//
    [!VAR "NormalChannelNumbers" = "$NormalChannelNumbers + 1"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
/* Number of channels configured as regular channel */
#define GPT_MAX_CHANNELS                                             ([!"num:i($NormalChannelNumbers)"!]U)
[!ENDINDENT!][!//
/* Safety check enable status */
#define GPT_SAFETY_ENABLE                                            ([!//
[!IF "GptDriverConfiguration/GptSafetyErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

#endif /* GPT_CFG_H_ */

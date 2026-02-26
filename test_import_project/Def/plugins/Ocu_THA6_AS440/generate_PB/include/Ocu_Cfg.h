/****************************************************************************************************
*   FileName              : Ocu_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                 : This file contains all configuration declarations of OCU Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Ocu_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#ifndef OCU_CFG_H
#define OCU_CFG_H
[!NOCODE!][!//
[!INCLUDE "Ocu.m"!][!//
[!ENDNOCODE!][!//
[!INDENT "0"!][!//
  [!SELECT "as:modconf('Ocu')[1]"!][!// 

/****************************************************************************************************
**                                  Version Information                                            **
*****************************************************************************************************/
[!AUTOSPACING!][!//
/* AUTOSAR release version information */
#define OCU_CFG_AR_RELEASE_MAJOR_VERSION                             ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define OCU_CFG_AR_RELEASE_MINOR_VERSION                             ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define OCU_CFG_AR_RELEASE_REVISION_VERSION                          ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)
/* OCU module release version information */
#define OCU_CFG_SW_MAJOR_VERSION                                     ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define OCU_CFG_SW_MINOR_VERSION                                     ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define OCU_CFG_SW_PATCH_VERSION                                     ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)
/* Vendor ID */
#define OCU_CFG_VENDOR_ID                                            ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
/* Module ID */
#define OCU_CFG_MODULE_ID                                            ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/****************************************************************************************************
**                                   API Information                                               **
****************************************************************************************************/
/*
Configuration: OCU_DE_INIT_API
Adds/removes Ocu_DeInit API 
from the code 
- if STD_ON, Ocu_DeInit is enabled
- if STD_OFF, Ocu_DeInit is disabled
*/
#define OCU_DE_INIT_API                                              ([!//
[!IF "OcuConfigurationOfOptionalApis/OcuDeInitApi = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: OCU_SET_PIN_ACTION_API
Adds/removes Set Pin Action API from the code 
- if STD_ON, Ocu_SetPinAction is enabled
- if STD_OFF, Ocu_SetPinAction is disabled
*/
#define OCU_SET_PIN_ACTION_API                                       ([!//
[!IF "OcuConfigurationOfOptionalApis/OcuSetPinActionApi = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: OCU_SET_PIN_STATE_API
Adds/removes Set Pin State API from the code 
- if STD_ON, Ocu_SetPinState is enabled
- if STD_OFF, Ocu_SetPinState is disabled
*/
#define OCU_SET_PIN_STATE_API                                        ([!//
[!IF "OcuConfigurationOfOptionalApis/OcuSetPinStateApi = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: OCU_GET_COUNTER_API
Adds/removes Get Counter API from the code 
- if STD_ON, Ocu_GetCounter is enabled
- if STD_OFF, Ocu_GetCounter is disabled
*/
#define OCU_GET_COUNTER_API                                          ([!//
[!IF "OcuConfigurationOfOptionalApis/OcuGetCounterApi = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: OCU_SET_ABSOLUTE_THRESHOLD_API
Adds/removes Set Absolute Threshold API from the code 
- if STD_ON, Ocu_SetAbsoluteThreshold is enabled
- if STD_OFF, Ocu_SetAbsoluteThreshold is disabled
*/
#define OCU_SET_ABSOLUTE_THRESHOLD_API                               ([!//
[!IF "OcuConfigurationOfOptionalApis/OcuSetAbsoluteThresholdApi = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: OCU_SET_RELATIVE_THRESHOLD_API
Adds/removes Set Relative Threshold API from the code 
- if STD_ON, Ocu_SetRelativeThreshold is enabled
- if STD_OFF, Ocu_SetRelativeThreshold is disabled
*/
#define OCU_SET_RELATIVE_THRESHOLD_API                               ([!//
[!IF "OcuConfigurationOfOptionalApis/OcuSetRelativeThresholdApi = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: OCU_VERSION_INFO_API
Adds/removes Get Version Info API from the code 
- if STD_ON, Ocu_GetVersionInfo is enabled
- if STD_OFF, Ocu_GetVersionInfo is disabled
*/
#define OCU_VERSION_INFO_API                                         ([!//
[!IF "OcuConfigurationOfOptionalApis/OcuVersionInfoApi = 'true'"!][!//
  STD_ON[!//
[!ELSE!][!//
  STD_OFF[!//
[!ENDIF!][!//
)

/****************************************************************************************************
**                          Ocu Channel Symbolic Names                                             **
****************************************************************************************************/
/* Ocu Channel ID Macro for Channel Configuration. */
[!SELECT "as:modconf('Ocu')[1]/OcuConfigSet/OcuChannel"!][!//
[!LOOP "node:order(./*, 'OcuChannelId')"!][!//
#ifndef OcuConf_OcuChannel_[!"@name"!]
#define OcuConf_OcuChannel_[!"@name"!]  \
((Ocu_ChannelType)[!"./OcuChannelId"!]U)
#endif

[!ENDLOOP!][!//  
[!ENDSELECT!][!//

/****************************************************************************************************
**                          Function features control                                              **
****************************************************************************************************/
/* Notification supported */
#define OCU_NOTIFICATION_SUPPORTED                                   ([!//
[!IF "OcuConfigurationOfOptionalApis/OcuNotificationSupported = 'true'"!][!//
      STD_ON[!//
[!ELSE!][!//
      STD_OFF[!//
[!ENDIF!][!//
    )
/* Development error detect */
#define OCU_DEV_ERROR_DETECT                                         ([!//
[!IF "OcuGeneral/OcuDevErrorDetect = 'true'"!][!//
      STD_ON[!//
[!ELSE!][!//
      STD_OFF[!//
[!ENDIF!][!//
    )
/* Safty enable */
#define OCU_SAFETY_ENABLE                                            ([!//
[!IF "OcuGeneral/OcuSafetyErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/* Ocu runtime error detect */
/* #Violation: Ocu_Cfg_h_REF_1 */
#define OCU_RUNTIME_ERROR_DETECT                                     (STD_ON)
/* OCU channel mapped to Core0 */
#define OCU_MAX_CHANNEL_TO_CORE0                                     ([!"num:i($OcuChannelMappedCore0)"!]U)
/* OCU channel mapped to Core1 */
#define OCU_MAX_CHANNEL_TO_CORE1                                     ([!"num:i($OcuChannelMappedCore1)"!]U)
/* OCU channel mapped to Core2 */
#define OCU_MAX_CHANNEL_TO_CORE2                                     ([!"num:i($OcuChannelMappedCore2)"!]U)
/* OCU channel mapped to Core3 */
#define OCU_MAX_CHANNEL_TO_CORE3                                     ([!"num:i($OcuChannelMappedCore3)"!]U)
/* The number of all OCU channel */
#define OCU_MAX_CHANNELS                                             ([!"num:i(num:i($OcuChannelMappedCore0) + num:i($OcuChannelMappedCore1) + num:i($OcuChannelMappedCore2) + num:i($OcuChannelMappedCore3))"!]U)
/* The maximum id of OCU channel */
/* #Violation: Ocu_Cfg_h_REF_1 */
#define OCU_MAX_CHANNEL_ID                                           ([!"num:i(num:i($OcuChannelMappedCore0) + num:i($OcuChannelMappedCore1) + num:i($OcuChannelMappedCore2) + num:i($OcuChannelMappedCore3) - num:i(1))"!]U)

  [!ENDSELECT!][!//
[!ENDINDENT!]
#endif  /* OCU_CFG_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


[!CODE!][!//
[!AUTOSPACING!]
/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Icu_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TIM
*
*   brief                 : This file contains all post-build parameters in ICU Driver
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
*
*#Icu_Cfg_h_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for different configurations.
*
*#Icu_Cfg_h_REF_3:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef ICU_CFG_H_
#define ICU_CFG_H_
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Icu_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
/* AUTOSAR release version information */
#define ICU_CFG_AR_RELEASE_MAJOR_VERSION                          ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define ICU_CFG_AR_RELEASE_MINOR_VERSION                          ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define ICU_CFG_AR_RELEASE_REVISION_VERSION                       ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

/* Module Software version information */
#define ICU_CFG_SW_MAJOR_VERSION                                  ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define ICU_CFG_SW_MINOR_VERSION                                  ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define ICU_CFG_SW_PATCH_VERSION                                  ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)
/* #Violation: Msc_Cfg_h_REF_1 */

#define ICU_CFG_VENDOR_ID                                         ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define ICU_CFG_MODULE_ID                                         ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/*
Configuration: ICU_DE_INIT_API
Adds/removes Icu_DeInit API 
from the code 
- if STD_ON, Icu_DeInit is enabled
- if STD_OFF, Icu_DeInit is disabled
*/
[!IF "IcuOptionalApis/IcuDeInitApi = 'true'"!]
#define ICU_DE_INIT_API                                           (STD_ON)
[!ELSE!]
#define ICU_DE_INIT_API                                           (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_GET_VERSION_INFO_API
Adds/removes Icu_GetVersionInfo API 
from the code 
- if STD_ON, Icu_GetVersionInfo is enabled
- if STD_OFF, Icu_GetVersionInfo is disabled
*/
[!IF "IcuOptionalApis/IcuGetVersionInfoApi = 'true'"!]
#define ICU_GET_VERSION_INFO_API                                  (STD_ON)
[!ELSE!]
#define ICU_GET_VERSION_INFO_API                                  (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_SET_MODE_API
Adds/removes Icu_SetMode API 
from the code 
- if STD_ON, Icu_SetMode is enabled
- if STD_OFF, Icu_SetMode is disabled
*/
[!IF "IcuOptionalApis/IcuSetModeApi = 'true'"!]
#define ICU_SET_MODE_API                                          (STD_ON)
[!ELSE!]
#define ICU_SET_MODE_API                                          (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_DISABLE_WAKEUP_API
Adds/removes Icu_DisableWakeup API 
from the code 
- if STD_ON, Icu_DisableWakeup is enabled
- if STD_OFF, Icu_DisableWakeup is disabled
*/
[!IF "IcuOptionalApis/IcuDisableWakeupApi = 'true'"!]
#define ICU_DISABLE_WAKEUP_API                                    (STD_ON)
[!ELSE!]
#define ICU_DISABLE_WAKEUP_API                                    (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_ENABLE_WAKEUP_API
Adds/removes Icu_EnableWakeup API 
from the code 
- if STD_ON, Icu_EnableWakeup is enabled
- if STD_OFF, Icu_EnableWakeup is disabled
*/
[!IF "IcuOptionalApis/IcuEnableWakeupApi = 'true'"!]
#define ICU_ENABLE_WAKEUP_API                                     (STD_ON) 
[!ELSE!]
#define ICU_ENABLE_WAKEUP_API                                     (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_WAKEUP_FUNCTIONALITY_API
Adds/removes the service Icu_CheckWakeup() 
from the code 
- if ON, the service Icu_CheckWakeup() is enabled
- if OFF, the service Icu_CheckWakeup() is disabled
*/
[!IF "IcuOptionalApis/IcuWakeupFunctionalityApi = 'true'"!]
#define ICU_WAKEUP_FUNCTIONALITY_API                              (STD_ON) 
[!ELSE!]
#define ICU_WAKEUP_FUNCTIONALITY_API                              (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_GET_INPUT_STATE_API
Adds/removes Icu_GetInputState API 
from the code 
- if STD_ON, Icu_GetInputState is enabled
- if STD_OFF, Icu_GetInputState is disabled
*/
[!IF "IcuOptionalApis/IcuGetInputStateApi  = 'true'"!]
#define ICU_GET_INPUT_STATE_API                                   (STD_ON) 
[!ELSE!]
#define ICU_GET_INPUT_STATE_API                                   (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_EDGE_COUNT_API
Adds/removes Edge Count Measurement APIs 
from the code 
- if STD_ON, Icu_EnableEdgeCount, Icu_DisableEdgeCount
Icu_ResetEdgeCount, Icu_GetEdgeNumbers is enabled
- if STD_OFF, Icu_EnableEdgeCount, Icu_DisableEdgeCount
Icu_ResetEdgeCount, Icu_GetEdgeNumbers is disabled
*/
[!IF "IcuOptionalApis/IcuEdgeCountApi = 'true'"!]
#define ICU_EDGE_COUNT_API                                        (STD_ON) 
[!ELSE!]
#define ICU_EDGE_COUNT_API                                        (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_EDGE_DETECT_API
Adds/removes Edge Detect APIs 
from the code 
- if STD_ON, Edge Detection functionality is enabled
- if STD_OFF, Edge Detection functionality is disabled
*/

[!IF "IcuOptionalApis/IcuEdgeDetectApi = 'true'"!]
#define ICU_EDGE_DETECT_API                                       (STD_ON) 
[!ELSE!]
#define ICU_EDGE_DETECT_API                                       (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_SIGNAL_MEASUREMENT_API
Adds/removes Signal Measurement APIs 
from the code 
- if STD_ON, Icu_StartSignalMeasurement, Icu_StopSignalMeasurement
are enabled
- if STD_OFF, Icu_StartSignalMeasurement, Icu_StopSignalMeasurement
are disabled
*/
[!IF "IcuOptionalApis/IcuSignalMeasurementApi = 'true'"!]
#define ICU_SIGNAL_MEASUREMENT_API                                (STD_ON) 
[!ELSE!]
#define ICU_SIGNAL_MEASUREMENT_API                                (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_TIMESTAMP_API
Adds / removes all services related to the timestamping functionality
- if STD_ON, Icu_StartTimestamp, Icu_StopTimestamp, Icu_GetTimestampIndex
are enabled
- if STD_OFF, Icu_StartTimestamp, Icu_StopTimestamp, Icu_GetTimestampIndex
are disabled
*/
[!IF "IcuOptionalApis/IcuTimestampApi  = 'true'"!]
#define ICU_TIMESTAMP_API                                         (STD_ON) 
[!ELSE!]
#define ICU_TIMESTAMP_API                                         (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_GET_TIME_ELAPSED_API
Adds/removes Icu_GetTimeElapsed API 
from the code 
- if STD_ON, Icu_GetTimeElapsed is enabled
- if STD_OFF, Icu_GetTimeElapsed is disabled
*/
[!IF "IcuOptionalApis/IcuGetTimeElapsedApi = 'true'"!]
#define ICU_GET_TIME_ELAPSED_API                                  (STD_ON) 
[!ELSE!]
#define ICU_GET_TIME_ELAPSED_API                                  (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_GET_DUTY_CYCLE_VALUES_API
Adds/removes Icu_GetDutyCycleValues API 
from the code 
- if STD_ON, Icu_GetDutyCycleValues is enabled
- if STD_OFF, Icu_GetDutyCycleValues is disabled
*/
[!IF "IcuOptionalApis/IcuGetDutyCycleValuesApi   = 'true'"!]
#define ICU_GET_DUTY_CYCLE_VALUES_API                             (STD_ON) 
[!ELSE!]
#define ICU_GET_DUTY_CYCLE_VALUES_API                             (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_DEV_ERROR_DETECT
Adds/removes the Development Error Detection 
from the code 
- if STD_ON, Development Error Detection is enabled
- if STD_OFF, Development Error Detection is disabled
*/
[!IF "IcuGeneral/IcuDevErrorDetect = 'true'"!]
#define ICU_DEV_ERROR_DETECT                                      (STD_ON) 
[!ELSE!]
#define ICU_DEV_ERROR_DETECT                                      (STD_OFF)
[!ENDIF!]


/*
Configuration: ICU_DEV_RUNTIME_ERROR_DETECT
Adds/removes the Runtime Error Detect
from the code 
- if STD_ON, Runtime Error Detect is enabled
- if STD_OFF, Runtime Error Detect is disabled
*/
#define ICU_DEV_RUNTIME_ERROR_DETECT                              (STD_ON) 

/*
Configuration: ICU_ALREADY_INIT_DET_CHECK
Pre-processor switch to enable/disable the initialization Development Error Detection features.
- if STD_ON, Enable the initialization Development Error Detection features.
- if STD_OFF, Disable the initialization Development Error Detection features.
*/
[!IF "IcuGeneral/IcuAlreadyInitDetCheck   = 'true'"!]
#define ICU_ALREADY_INIT_DET_CHECK                                (STD_ON) 
[!ELSE!]
#define ICU_ALREADY_INIT_DET_CHECK                                (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_REPORT_WAKEUP_SOURCE
Preprocessor switch to enable/disable the wakeup source reporting
- if STD_ON, Reports wakeup to higher layer
- if STD_OFF, Reporting is switched off
*/
[!IF "IcuGeneral/IcuReportWakeupSource = 'true'"!]
#define ICU_REPORT_WAKEUP_SOURCE                                  (STD_ON) 
[!ELSE!]
#define ICU_REPORT_WAKEUP_SOURCE                                  (STD_OFF)
[!ENDIF!]

/*
Configuration: ICU_REPORT_WAKEUP_SOURCE
Preprocessor switch to enable/disable the check for notification repeatedly enable or disable
- if STD_ON, Enable the check for notification repeatedly enable or disable
- if STD_OFF, Disable the check for notification repeatedly enable or disable
*/
[!IF "IcuGeneral/IcuAlreadyEnableDisableDetCheck  = 'true'"!]
#define ICU_ALREADY_ENABLEDISABLE_DET_CHECK                       (STD_ON) 
[!ELSE!]
#define ICU_ALREADY_ENABLEDISABLE_DET_CHECK                       (STD_OFF)
[!ENDIF!]

#define ICU_CNTOFL_COUNTER                                        (0x1000000U)
/* #Violation: Icu_Cfg_h_REF_2 */
#define ICU_MEASUREMENT_PRO_PERIOD                                (0x02U)
/* #Violation: Icu_Cfg_h_REF_2 */
#define ICU_MEASUREMENT_PRO_DUTY_CYCLE                            (0x05U)
#define ICU_MEASUREMENT_PRO_HIGH_TIME                             (0x01U)
#define ICU_MEASUREMENT_PRO_LOW_TIME                              (0x00U)

/*******************************************************************************
**                          Icu Channel Symbolic Names                        **
*******************************************************************************/
[!LOOP "IcuConfigSet/IcuChannel/*"!][!//
/* Symbolic name for [!"@name"!]*/
/* #Violation: Icu_Cfg_h_REF_3 */
#define IcuConf_IcuChannel_[!"node:name(.)"!]                                   ([!"./IcuChannelId"!]U)

[!ENDLOOP!][!//                          
[!//

/* ICU channel mapped to Core0 */
#define ICU_MAX_CHANNEL_TO_CORE0[!WS "42"!]([!"num:i($IcuChannelMappedCore0)"!]U)
/* ICU channel mapped to Core1 */
#define ICU_MAX_CHANNEL_TO_CORE1[!WS "42"!]([!"num:i($IcuChannelMappedCore1)"!]U)
/* ICU channel mapped to Core2 */  
#define ICU_MAX_CHANNEL_TO_CORE2[!WS "42"!]([!"num:i($IcuChannelMappedCore2)"!]U)
/* ICU channel mapped to Core3 */
#define ICU_MAX_CHANNEL_TO_CORE3[!WS "42"!]([!"num:i($IcuChannelMappedCore3)"!]U)
/* ICU channel total number */
/* Total number of the configurated channel */
#define ICU_TOTAL_CHANNEL_NUMBER[!WS "42"!]([!"num:i(count(IcuConfigSet/IcuChannel/*))"!]U)[!CR!][!//
/*
Configuration: ICU_SAFETY_ENABLE
Preprocessor switch to enable/disable the safety function.
- if STD_ON, Enable the safety function
- if STD_OFF, Disable the safety function
*/
#define ICU_SAFETY_ENABLE                 ([!//
[!IF "IcuGeneral/IcuSafetyErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

#endif /* ICU_CFG_H_ */

[!ENDCODE!]
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

[!CODE!][!//
[!AUTOSPACING!]
/****************************************************************************************************
*   FileName              : Pwm_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
*
*   brief                 : This file contains all configuration declarations of PWM Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved
*
****************************************************************************************************/
/*
*#Violation Summary
*#Pwm_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef PWM_CFG_H_
#define PWM_CFG_H_
[!NOCODE!][!//
[!INCLUDE "Pwm_Cfg.m"!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          Version Information                                                    **
****************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_CFG_AR_RELEASE_MAJOR_VERSION                             ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define PWM_CFG_AR_RELEASE_MINOR_VERSION                             ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define PWM_CFG_AR_RELEASE_REVISION_VERSION                          ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

/* Module software version information */
#define PWM_CFG_SW_MAJOR_VERSION                                     ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define PWM_CFG_SW_MINOR_VERSION                                     ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define PWM_CFG_SW_PATCH_VERSION                                     ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define PWM_CFG_VENDOR_ID                                            ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define PWM_CFG_MODULE_ID                                            ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/****************************************************************************************************
**                          API Information                                                        **
****************************************************************************************************/
/*
Configuration: PWM_DE_INIT_API
Configuration of Pwm_DeInit API
Adds/removes the service Pwm_DeInit() 
from the code 
- if STD_ON, Pwm_DeInit() can be used
- if STD_OFF, Pwm_DeInit() cannot be used
*/
[!IF "PwmConfigurationOfOptApiServices/PwmDeInitApi = 'true'"!][!//
#define PWM_DE_INIT_API                                              (STD_ON)
[!ELSE!][!//
#define PWM_DE_INIT_API                                              (STD_OFF)
[!ENDIF!][!//
/*
Configuration: PWM_SET_DUTY_CYCLE_API
Configuration of PWM_SET_DUTY_CYCLE_API
Adds/removes the service Pwm_SetDutyCycle() 
from the code 
- if STD_ON, Pwm_SetDutyCycle() can be used
- if STD_OFF,Pwm_SetDutyCycle() cannot be used
*/
[!IF "PwmConfigurationOfOptApiServices/PwmSetDutyCycle = 'true'"!][!//
#define PWM_SET_DUTY_CYCLE_API                                       (STD_ON)
[!ELSE!][!//
#define PWM_SET_DUTY_CYCLE_API                                       (STD_OFF)
[!ENDIF!][!//
[!IF "PwmConfigurationOfOptApiServices/PwmSetPeriodAndDuty = 'true'"!][!//
[!VAR "Pwm_VariableChannelNum" = "0"!][!//
[!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId ')"!][!//
  [!IF "node:exists(./PwmChannelClass) and ./PwmChannelClass = 'PWM_VARIABLE_PERIOD'"!][!//
    [!VAR "Pwm_VariableChannelNum" = "$Pwm_VariableChannelNum+1"!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$Pwm_VariableChannelNum = 0"!][!//
  [!ERROR!][!//
    121-00-09-ERROR: PwmConfigurationOfOptApiServices/PwmSetPeriodAndDuty is enabled, but there is no variable period channel.
  [!ENDERROR!][!//
[!ENDIF!][!//
/*
Configuration: PWM_SET_PERIOD_AND_DUTY_API
Configuration of PWM_SET_PERIOD_AND_DUTY_API
Adds/removes the service Pwm_SetPeriodAndDuty() 
from the code 
- if STD_ON, Pwm_SetPeriodAndDuty() can be used
- if STD_OFF,Pwm_SetPeriodAndDuty() cannot be used
*/
#define PWM_SET_PERIOD_AND_DUTY_API                                  (STD_ON)
[!ELSE!][!//
#define PWM_SET_PERIOD_AND_DUTY_API                                  (STD_OFF)
[!ENDIF!][!//
/*
Configuration: PWM_SET_OUTPUT_TO_IDLE_API
Configuration of PWM_SET_OUTPUT_TO_IDLE_API
Adds/removes the service Pwm_SetOutputToIdle() 
from the code 
- if STD_ON, Pwm_SetOutputToIdle() can be used
- if STD_OFF,Pwm_SetOutputToIdle() cannot be used
*/
[!IF "PwmConfigurationOfOptApiServices/PwmSetOutputToIdle = 'true'"!][!//
#define PWM_SET_OUTPUT_TO_IDLE_API                                   (STD_ON)
[!ELSE!][!//
#define PWM_SET_OUTPUT_TO_IDLE_API                                   (STD_OFF)
[!ENDIF!][!//
/*
Configuration: PWM_VERSION_INFO_API
Adds/removes the service Pwm_GetVersionInfo() 
from the code 
- if STD_ON, Pwm_GetVersionInfo() can be used
- if STD_OFF, Pwm_GetVersionInfo() cannot be used
*/
[!IF "PwmConfigurationOfOptApiServices/PwmVersionInfoApi = 'true'"!][!//
#define PWM_VERSION_INFO_API                                         (STD_ON)
[!ELSE!][!//
#define PWM_VERSION_INFO_API                                         (STD_OFF)
[!ENDIF!][!//
/*
Configuration: PWM_GET_OUTPUT_STATE_API
Configuration of PWM_GET_OUTPUT_STATE_API
Adds/removes the service Pwm_GetOutputState() 
from the code 
- if STD_ON, Pwm_GetOutputState() can be used
- if STD_OFF, Pwm_GetOutputState() cannot be used
*/
[!IF "PwmConfigurationOfOptApiServices/PwmGetOutputState  = 'true'"!][!//
#define PWM_GET_OUTPUT_STATE_API                                     (STD_ON)
[!ELSE!][!//
#define PWM_GET_OUTPUT_STATE_API                                     (STD_OFF)
[!ENDIF!][!//
                    

/*******************************************************************************
**                          Pwm Channel Symbolic Names                        **
*******************************************************************************/
/* Pwm Channel ID Enumerations for Channel Configuration. */
[!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId ')"!][!//
#ifndef PwmConf_PwmChannel_[!"@name"!]
#define PwmConf_PwmChannel_[!"@name"!]  \
((Pwm_ChannelType)[!"./PwmChannelId"!]U)
#endif

[!ENDLOOP!][!//  

/****************************************************************************************************
**                          Function control                                                       **
****************************************************************************************************/
[!IF "PwmGeneral/PwmDevErrorDetect   = 'true'"!][!//
/* Development error trace is enabled */
#define PWM_DEV_ERROR_DETECT                                         (STD_ON)
[!ELSE!][!//
/* Development error trace is disabled */
#define PWM_DEV_ERROR_DETECT                                         (STD_OFF)
[!ENDIF!][!//
[!IF "./PwmGeneral/PwmDutyShiftInTicks  = 'true'"!][!//
/* The unit of duty cycle and shift value is tick, both configuration and API */
#define PWM_DUTY_SHIFT_IN_TICKS                                      (STD_ON)
[!ELSE!][!//
/* The unit of duty cycle and shift value is percent, both configuration and API.
 * 0x00 ~ 0x8000 means 0% ~ 100%. */
#define PWM_DUTY_SHIFT_IN_TICKS                                      (STD_OFF)
[!ENDIF!][!//
[!IF "./PwmGeneral/PwmHandleShiftByOffset  = 'true'"!][!//
/* The waveform phase shift is achieved by the initial counter offset */
#define PWM_HANDLE_SHIFT_BY_OFFSET                                   (STD_ON)
[!ELSE!][!//
/* The waveform phase shift is achieved by the trigger mechanism of hardware */
#define PWM_HANDLE_SHIFT_BY_OFFSET                                   (STD_OFF)
[!ENDIF!][!//
[!IF "PwmGeneral/PwmNotificationSupported  = 'true'"!][!//
/* Notification function is enabled */
#define PWM_NOTIFICATION_SUPPORTED                                   (STD_ON)
[!ELSE!][!//
/* Notification function is disabled */
#define PWM_NOTIFICATION_SUPPORTED                                   (STD_OFF)
[!ENDIF!][!//
[!IF "PwmGeneral/PwmEnable0Or100DutyHandle = 'true' and PwmGeneral/PwmNotificationSupported = 'true'"!][!//
/* Special handling for interrupts at 0% or 100% duty cycle has been enabled */
#define PWM_0_100_INTERRUPT_HANDLE                                   (STD_ON)
[!ELSE!][!//
/* Special handling for interrupts at 0% or 100% duty cycle has been disabled */
#define PWM_0_100_INTERRUPT_HANDLE                                   (STD_OFF)
[!ENDIF!][!//

/* PWM channel mapped to Core0 */
#define PWM_MAX_CHANNEL_TO_CORE0                                     ([!"num:i($PwmChannelMappedCore0)"!]U)
/* PWM channel mapped to Core1 */
#define PWM_MAX_CHANNEL_TO_CORE1                                     ([!"num:i($PwmChannelMappedCore1)"!]U)
/* PWM channel mapped to Core2 */
#define PWM_MAX_CHANNEL_TO_CORE2                                     ([!"num:i($PwmChannelMappedCore2)"!]U)
/* PWM channel mapped to Core3 */
#define PWM_MAX_CHANNEL_TO_CORE3                                     ([!"num:i($PwmChannelMappedCore3)"!]U)
[!VAR "ChannelNumbers" = "0"!][!//
[!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId ')"!][!//
    [!VAR "ChannelNumbers" = "$ChannelNumbers + 1"!][!//
[!ENDLOOP!][!//
/* Number of channels. */
#define PWM_MAX_CHANNELS                                             ([!"num:i($ChannelNumbers)"!]U)
/* The maximum id number of channel. */
#define PWM_MAX_CHANNEL_ID_CONFIGURED                                ([!"num:i(num:i($ChannelNumbers) -1)"!]U)
[!ENDCODE!]
/* Safety check enable status */
#define PWM_SAFETY_ENABLE                                            ([!//
[!IF "PwmGeneral/PwmSafetyErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

#endif /* PWM_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

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

/****************************************************************************************************
**                          Version Information                                                    **
****************************************************************************************************/
/* AUTOSAR release version information */
#define PWM_CFG_AR_RELEASE_MAJOR_VERSION                             (4U)
#define PWM_CFG_AR_RELEASE_MINOR_VERSION                             (4U)
#define PWM_CFG_AR_RELEASE_REVISION_VERSION                          (0U)

/* Module software version information */
#define PWM_CFG_SW_MAJOR_VERSION                                     (1U)
#define PWM_CFG_SW_MINOR_VERSION                                     (2U)
#define PWM_CFG_SW_PATCH_VERSION                                     (0U)

#define PWM_CFG_VENDOR_ID                                            (175U)
#define PWM_CFG_MODULE_ID                                            (121U)

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
#define PWM_DE_INIT_API                                              (STD_ON)
/*
Configuration: PWM_SET_DUTY_CYCLE_API
Configuration of PWM_SET_DUTY_CYCLE_API
Adds/removes the service Pwm_SetDutyCycle() 
from the code 
- if STD_ON, Pwm_SetDutyCycle() can be used
- if STD_OFF,Pwm_SetDutyCycle() cannot be used
*/
#define PWM_SET_DUTY_CYCLE_API                                       (STD_ON)
/*
Configuration: PWM_SET_PERIOD_AND_DUTY_API
Configuration of PWM_SET_PERIOD_AND_DUTY_API
Adds/removes the service Pwm_SetPeriodAndDuty() 
from the code 
- if STD_ON, Pwm_SetPeriodAndDuty() can be used
- if STD_OFF,Pwm_SetPeriodAndDuty() cannot be used
*/
#define PWM_SET_PERIOD_AND_DUTY_API                                  (STD_ON)
/*
Configuration: PWM_SET_OUTPUT_TO_IDLE_API
Configuration of PWM_SET_OUTPUT_TO_IDLE_API
Adds/removes the service Pwm_SetOutputToIdle() 
from the code 
- if STD_ON, Pwm_SetOutputToIdle() can be used
- if STD_OFF,Pwm_SetOutputToIdle() cannot be used
*/
#define PWM_SET_OUTPUT_TO_IDLE_API                                   (STD_ON)
/*
Configuration: PWM_VERSION_INFO_API
Adds/removes the service Pwm_GetVersionInfo() 
from the code 
- if STD_ON, Pwm_GetVersionInfo() can be used
- if STD_OFF, Pwm_GetVersionInfo() cannot be used
*/
#define PWM_VERSION_INFO_API                                         (STD_ON)
/*
Configuration: PWM_GET_OUTPUT_STATE_API
Configuration of PWM_GET_OUTPUT_STATE_API
Adds/removes the service Pwm_GetOutputState() 
from the code 
- if STD_ON, Pwm_GetOutputState() can be used
- if STD_OFF, Pwm_GetOutputState() cannot be used
*/
#define PWM_GET_OUTPUT_STATE_API                                     (STD_ON)
                    

/*******************************************************************************
**                          Pwm Channel Symbolic Names                        **
*******************************************************************************/
/* Pwm Channel ID Enumerations for Channel Configuration. */
#ifndef PwmConf_PwmChannel_PwmChannel_0
#define PwmConf_PwmChannel_PwmChannel_0  \
((Pwm_ChannelType)0U)
#endif

#ifndef PwmConf_PwmChannel_PwmChannel_1
#define PwmConf_PwmChannel_PwmChannel_1  \
((Pwm_ChannelType)1U)
#endif

#ifndef PwmConf_PwmChannel_PwmChannel_2
#define PwmConf_PwmChannel_PwmChannel_2  \
((Pwm_ChannelType)2U)
#endif

#ifndef PwmConf_PwmChannel_PwmChannel_3
#define PwmConf_PwmChannel_PwmChannel_3  \
((Pwm_ChannelType)3U)
#endif

#ifndef PwmConf_PwmChannel_PwmChannel_4
#define PwmConf_PwmChannel_PwmChannel_4  \
((Pwm_ChannelType)4U)
#endif

#ifndef PwmConf_PwmChannel_PwmChannel_5
#define PwmConf_PwmChannel_PwmChannel_5  \
((Pwm_ChannelType)5U)
#endif

#ifndef PwmConf_PwmChannel_PwmChannel_6
#define PwmConf_PwmChannel_PwmChannel_6  \
((Pwm_ChannelType)6U)
#endif

#ifndef PwmConf_PwmChannel_PwmChannel_7
#define PwmConf_PwmChannel_PwmChannel_7  \
((Pwm_ChannelType)7U)
#endif

#ifndef PwmConf_PwmChannel_ICU_DEMO
#define PwmConf_PwmChannel_ICU_DEMO  \
((Pwm_ChannelType)8U)
#endif

#ifndef PwmConf_PwmChannel_PwmChannel_8
#define PwmConf_PwmChannel_PwmChannel_8  \
((Pwm_ChannelType)9U)
#endif

#ifndef PwmConf_PwmChannel_PwmChannel_9
#define PwmConf_PwmChannel_PwmChannel_9  \
((Pwm_ChannelType)10U)
#endif

#ifndef PwmConf_PwmChannel_PwmToDsadc
#define PwmConf_PwmChannel_PwmToDsadc  \
((Pwm_ChannelType)11U)
#endif


/****************************************************************************************************
**                          Function control                                                       **
****************************************************************************************************/
/* Development error trace is enabled */
#define PWM_DEV_ERROR_DETECT                                         (STD_ON)
/* The unit of duty cycle and shift value is tick, both configuration and API */
#define PWM_DUTY_SHIFT_IN_TICKS                                      (STD_ON)
/* The waveform phase shift is achieved by the trigger mechanism of hardware */
#define PWM_HANDLE_SHIFT_BY_OFFSET                                   (STD_OFF)
/* Notification function is enabled */
#define PWM_NOTIFICATION_SUPPORTED                                   (STD_ON)
/* Special handling for interrupts at 0% or 100% duty cycle has been enabled */
#define PWM_0_100_INTERRUPT_HANDLE                                   (STD_ON)

/* PWM channel mapped to Core0 */
#define PWM_MAX_CHANNEL_TO_CORE0                                     (8U)
/* PWM channel mapped to Core1 */
#define PWM_MAX_CHANNEL_TO_CORE1                                     (4U)
/* PWM channel mapped to Core2 */
#define PWM_MAX_CHANNEL_TO_CORE2                                     (0U)
/* PWM channel mapped to Core3 */
#define PWM_MAX_CHANNEL_TO_CORE3                                     (0U)
/* Number of channels. */
#define PWM_MAX_CHANNELS                                             (12U)
/* The maximum id number of channel. */
#define PWM_MAX_CHANNEL_ID_CONFIGURED                                (11U)
/* Safety check enable status */
#define PWM_SAFETY_ENABLE                                            (STD_ON)

#endif /* PWM_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

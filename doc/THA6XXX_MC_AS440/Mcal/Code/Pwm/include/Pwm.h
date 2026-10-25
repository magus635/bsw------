/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Pwm.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
*
*   brief                 : This file contains all function declarations of Pwm Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
/*
*
*#Pwm_h_REF_1:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Pwm_h_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef MCAL_PWM_PWM_H_
#define MCAL_PWM_PWM_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* SWS_Pwm_00094 */
#include "Std_Types.h"
#include "Pwm_Cfg.h"
#include "Mcall.h"
#include "Pwm_GeneralTypes.h"
#include "Pwm_Version.h"
#include "Pwm_PBcfg.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#if (PWM_DUTY_SHIFT_IN_TICKS == STD_OFF)
/* Maximum percentage duty cycle value */
#define PWM_MAX_DUTYCYCLE_PERCENT             (0x8000U)
#endif /* (PWM_DUTY_SHIFT_IN_TICKS \== STD_OFF) */
/* Maximum duty cycle value of tom based channel in ticks */
#define PWM_MAX_DUTYCYCLE_TICKS_TOM           (0xFFFFU)
/* Maximum duty cycle value of atom based channel in ticks */
#define PWM_MAX_DUTYCYCLE_TICKS_ATOM          (0xFFFFFFU)
/* Maximum period value of atom based channel in ticks */
#define PWM_MAX_PERIOD_TICKS_TOM              (0xFFFFU)
/* Maximum period value of atom based channel in ticks */
#define PWM_MAX_PERIOD_TICKS_ATOM             (0xFFFFFFU)

/* Service Id of Pwm_Init */
#define PWM_INIT_SID                         (0x00U)
/* Service Id of Pwm_DeInit */
#define PWM_DEINIT_SID                       (0x01U)
/* Service Id of Pwm_SetDutyCycle */
#define PWM_SET_DUTYCYCLE_SID                (0x02U)
/* Service Id of Pwm_SetPeriodAndDuty */
#define PWM_SET_PERIODANDDUTY_SID            (0x03U)
/* Service Id of Pwm_SetOutputToIdle */
#define PWM_SET_OUTPUTTOIDLE_SID             (0x04U)
/* Service Id of Pwm_GetOutputState */
#define PWM_GET_OUTPUTSTATE_SID              (0x05U)
/* Service Id of Pwm_DisableNotification */
#define PWM_DISABLENOTIFICATION_SID          (0x06U)
/* Service Id of Pwm_EnableNotification */
#define PWM_ENABLENOTIFICATION_SID           (0x07U)
/* Service Id of Pwm_GetVersionInfo */
#define PWM_GET_VERSION_INFO_SID             (0x08U)
/* Extend SID */
/* Service Id of Pwm_DutyPeriod_ISRHandler */
#define PWM_ISR_SID                          (0x0FU)

/* SWS_Pwm_00201: Error Types */
/* Pwm_Init API called with wrong parameter */
#define PWM_E_INIT_FAILED                    (0x10U)/* 16 */
/* When PWM APIs are invoked before PWM Module Initialization */
#define PWM_E_UNINIT                         (0x11U)/* 17 */
/* When PWM APIs are invoked with invalid channel identifier */
#define PWM_E_PARAM_CHANNEL                  (0x12U)/* 18 */
/* Invoking the PWM APIs on PWM channel configured as Fixed period */
#define PWM_E_PERIOD_UNCHANGEABLE            (0x13U)/* 19 */
/* Pwm_Init API called when PWM module is already initialized */
#define PWM_E_ALREADY_INITIALIZED            (0x14U)/* 20 */
/* Pwm_GetVersionInfo is called with a NULL parameter */
#define PWM_E_PARAM_POINTER                  (0x15U)/* 21 */
/*
 * When PWM APIs Pwm_SetDutyCycle and Pwm_SetPeriodAndDuty are invoked with
 * invalid parameter values
 */
#define PWM_E_PARAM_VALUE                    (0xF3U)/* 243 */
/*
 * When Notification is not configured for channel invoked by
 * Pwm_DisableNotification and Pwm_EnableNotification APIs
 */
#define PWM_E_NOTIFY_NOTCONFIG               (0xF4U)/* 244 */
/* Report DET PWM module not configured for current Core */
#define PWM_E_CORE_NOT_CONFIGURED            (0xE0U)/* 224 */
/* PWM channel is not allocated to current core */
#define PWM_E_CORE_CHANNEL_MISMATCH          (0xE1U)/* 225 */
#define PWM_E_SAFETY_CHECK_FAILED            (0xE2)/* 226 */


/*****************************************************************************************************
**                          Global Variables                                                        **
*****************************************************************************************************/


/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Pwm_h_REF_2 */
#define PWM_START_SEC_CODE_ASIL_D_GLOBAL
#include "Pwm_MemMap.h"

extern FUNC(void, PWM_PUBLIC_CODE) Pwm_Init
(
    P2CONST(Pwm_ConfigType, PWM_VAR, PWM_APPL_CONST) ConfigPtr
);

#if (PWM_DE_INIT_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_DeInit
(
    void
);
#endif /* (PWM_DE_INIT_API  \== STD_ON) */

#if (PWM_SET_DUTY_CYCLE_API == STD_ON)

extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SetDutyCycle
(
    Pwm_ChannelType ChannelNumber,
    Pwm_DutyCycleType DutyCycle
);

#endif /* (PWM_SET_DUTY_CYCLE_API  \== STD_ON) */

#if (PWM_SET_PERIOD_AND_DUTY_API == STD_ON)

extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SetPeriodAndDuty
(
    Pwm_ChannelType ChannelNumber,
    Pwm_PeriodType Period,
    Pwm_DutyCycleType DutyCycle
);

#endif /* (PWM_SET_PERIOD_AND_DUTY_API  \== STD_ON) */

#if (PWM_SET_OUTPUT_TO_IDLE_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_SetOutputToIdle
(
    Pwm_ChannelType ChannelNumber
);
#endif /* (PWM_SET_OUTPUT_TO_IDLE_API  \== STD_ON) */

#if (PWM_GET_OUTPUT_STATE_API == STD_ON)
extern FUNC(Pwm_OutputStateType, PWM_PUBLIC_CODE) Pwm_GetOutputState
(
    Pwm_ChannelType ChannelNumber
);
#endif /* (PWM_GET_OUTPUT_STATE_API  \== STD_ON) */

#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_DisableNotification
(
    Pwm_ChannelType ChannelNumber
);

extern FUNC(void, PWM_PUBLIC_CODE) Pwm_EnableNotification
(
    Pwm_ChannelType ChannelNumber,
    Pwm_EdgeNotificationType Notification
);
#endif /* (PWM_NOTIFICATION_SUPPORTED  \== STD_ON) */

extern FUNC(void, PWM_PRIVATE_CODE) Pwm_DutyPeriod_ISRHandler
(
    uint8 Module, 
    uint8 ModuleIndex, 
    uint8 Channel
);

#if (PWM_VERSION_INFO_API == STD_ON)
extern FUNC(void, PWM_PUBLIC_CODE) Pwm_GetVersionInfo
(
    /* #Violation: Pwm_h_REF_1 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, PWM_APPL_DATA)VersionInfoPtr
);
#endif /*(PWM_VERSION_INFO_API \== STD_ON)*/

/* #Violation: Pwm_h_REF_2 */
#define PWM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Pwm_MemMap.h"

#endif /* PWM_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


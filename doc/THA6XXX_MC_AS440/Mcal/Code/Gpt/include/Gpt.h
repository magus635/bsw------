/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Gpt.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, BASETIMER
*
*   brief                 : This file contains all function declarations of Gpt Driver
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
*#Gpt_h_REF_1:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Gpt_h_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/
#ifndef MCAL_GPT_GPT_H_
#define MCAL_GPT_GPT_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* SWS_Gpt_00293 */
#include "Gpt_Cfg.h"
#include "Gpt_GeneralTypes.h"
#include "Gpt_Version.h"
#include "Gpt_PBcfg.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/*
 * GPT Service Id
*/

/* Service Id of Gpt_GetVersionInfo */
#define GPT_GET_VERSION_INFO_SID                (0x00U)/* 0 */
/* Service Id of Gpt_Init */
#define GPT_INIT_SID                            (0x01U)/* 1 */
/* Service Id of Gpt_DeInit */
#define GPT_DEINIT_SID                          (0x02U)/* 2 */
/* Service Id of Gpt_GetTimeElapsed */
#define GPT_GET_TIME_ELAPSED_SID                (0x03U)/* 3 */
/* Service Id of Gpt_GetTimeRemaining */
#define GPT_GET_TIME_REMAINING_SID              (0x04U)/* 4 */
/* Service Id of Gpt_StartTimer */
#define GPT_START_TIMER_SID                     (0x05U)/* 5 */
/* Service Id of Gpt_StopTimer */
#define GPT_STOP_TIMER_SID                      (0x06U)/* 6 */
/* Service Id of Gpt_EnableNotification */
#define GPT_ENABLE_NOTIFY_SID                   (0x07U)/* 7 */
/* Service Id of Gpt_DisableNotification */
#define GPT_DISABLE_NOTIFY_SID                  (0x08U)/* 8 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/* Service Id of Gpt_SetMode */
#define GPT_SET_MODE_SID                        (0x09U)/* 9 */
/* Service Id of Gpt_DisableWakeup */
#define GPT_DISABLE_WAKEUP_SID                  (0x0AU)/* 10 */
/* Service Id of Gpt_EnableWakeup */
#define GPT_ENABLE_WAKEUP_SID                   (0x0BU)/* 11 */
/* Service Id of Gpt_CheckWakeup */
#define GPT_CHECK_WAKEUP_SID                    (0x0CU)/* 12 */
#endif /* GPT_WAKEUP_FUNCTIONALITY_API \== STD_ON */
#endif /* (GPT_DEV_ERROR_DETECT \== STD_ON) */
/* Service Id of Gpt_GetPredefTiemrValue */
#define GPT_SID_GET_PREDEFTIMERVALUE_SID        (0x0DU)/* 13 */
/* API Service ID for Gpt_Gtm_ISRHandler() */
#define GPT_SID_GTM_ISRHANDLER_SID              (0x0FU)/* 15 */
/* API Service ID for Gpt_Basetimer_ISRHandler() */
#define GPT_SID_BASETIMER_ISRHANDLER_SID        (0xA0U)/* 16 */

/*
 * GPT Development Number
*/
/* DET code to report uninitialized state */
#define GPT_E_UNINIT                      (0x0AU)/* 10 */
/* DET code to report Timer is already running */
#define GPT_E_BUSY                        (0x0BU)/* 11 */
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
#if (GPT_DEV_ERROR_DETECT == STD_ON)
/* DET code to report Timer is in invalid mode */
#define GPT_E_MODE                        (0x0CU)/* 12 */
#endif /* GPT_DEV_ERROR_DETECT == STD_ON */
#endif /* GPT_WAKEUP_FUNCTIONALITY_API == STD_ON */
/* DET code to report Timer already Initialized */
#define GPT_E_ALREADY_INITIALIZED         (0x0DU)/* 13 */
/* DET code to report invalid Channel Identifier */
#define GPT_E_PARAM_CHANNEL               (0x14U)/* 20 */
/* DET code to report invalid timer value */
#define GPT_E_PARAM_VALUE                 (0x15U)/* 21 */
/* DET code to report Gpt_Init called with NULL as parameter */
#define GPT_E_PARAM_POINTER               (0x16U)/* 22 */
/* DET code to report the parameter PredefTimer is invalid */
#define GPT_E_PARAM_PREDEF_TIMER          (0x17U)/* 23 */
#if (GPT_DEV_ERROR_DETECT == STD_ON)
#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
/* DET code to report the parameter Mode is invalid */
#define GPT_E_PARAM_MODE                  (0x1FU)/* 31 */
#endif /* GPT_WAKEUP_FUNCTIONALITY_API \== STD_ON */
#endif /* (GPT_DEV_ERROR_DETECT \== STD_ON) */


/* DET code to report that the operation of getting lock is failed  */
#define GPT_E_LOCK_TIMEOUT                (0xA0U)/* 160 */
/*  channel the notification is already disabled */
#define GPT_E_ALREADY_DISABLED            (0xF1U)/* 241 */
/* channel for which the notification is already enabled */
#define GPT_E_ALREADY_ENABLED             (0xF2U)/* 242 */
/* Report DET PWM module not configured for current Core */
#define GPT_E_CORE_NOT_CONFIGURED         (0xE0U)/* 224 */
/* PWM channel is not allocated to current core */
#define GPT_E_CORE_CHANNEL_MISMATCH       (0xE1U)/* 225 */
/* Safety check function failed */
#define GPT_E_SAFETY_CHECK_FAILED         (0xE2)/* 226 */

/****************************************************************************************************
**                                     basic Macros                                                **
****************************************************************************************************/
/* The bit position in global variable Gpt_PredefTimerStatus, which indicates the initialization 
 * status of Predef timer */
#define GPT_PREDEFTIMER_STATUS_MASK       (0x01U)
/* Flag variable is set */
#define GPT_FLAG_SET                      ((uint32)0x01U)
/* Mask the core status in variable */
#define GPT_CORE_STATUS_MASK              ((uint32)0X1EU)
/* Indicates the Predef timer is not initialized */
#define GPT_PREDEFTIMER_UNINITIALIZED     (0x00U)
/* The bit position in global variable Gpt_PredefTimerStatus, which indicates the initialization 
 * status of all core */
#define GPT_CORESTATUS_POS                ((uint32)0x01U)
/* Indicates all core are not initialized */
#define GPT_ALLCORE_UNITIALIZED           (0x00U)
/*****************************************************************************************************
**                      Global Variables
*****************************************************************************************************/


/****************************************************************************************************
**                          Global Macros Declarations                                           **
****************************************************************************************************/
/* Indicate the enable status of the predef timer */
#define GPT_PREDEFTIMER_EN             ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON) || \
                                        (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
                                        (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON) || \
                                        (GPT_PREDEF_TIMER_100US_32BIT_EN == STD_ON))
/* Indicate the enable status of the 1us predef timer */
#define GPT_PREDEFTIMER_1US_EN         ((GPT_PREDEF_TIMER_1US_16BIT_EN == STD_ON) || \
                                        (GPT_PREDEF_TIMER_1US_24BIT_EN == STD_ON) || \
                                        (GPT_PREDEF_TIMER_1US_32BIT_EN == STD_ON))
/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Gpt_h_REF_2 */
#define GPT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Gpt_MemMap.h"

#if (GPT_GET_VERSION_INFO_API == STD_ON)

extern FUNC(void, GPT_PUBLIC_CODE) Gpt_GetVersionInfo
(
    /* #Violation: Gpt_h_REF_1 */
    P2VAR(Std_VersionInfoType,AUTOMATIC, GPT_APPL_DATA) VersionInfoPtr
);
#endif /*(GPT_VERSION_INFO_API \== STD_ON)*/

extern FUNC(void, GPT_PUBLIC_CODE) Gpt_Init
(
    P2CONST(Gpt_ConfigType, AUTOMATIC, GPT_APPL_CONST) ConfigPtr
);

#if (GPT_DE_INIT_API == STD_ON)
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_DeInit
(
    void
);
#endif /* GPT_DE_INIT_API == STD_ON */

#if (GPT_TIME_ELAPSED_API == STD_ON)
extern FUNC(Gpt_ValueType, GPT_PUBLIC_CODE) Gpt_GetTimeElapsed
(
    Gpt_ChannelType Channel
);
#endif /* GPT_TIME_ELAPSED_API == STD_ON */

#if (GPT_TIME_REMAINING_API == STD_ON)
extern FUNC(Gpt_ValueType, GPT_PUBLIC_CODE) Gpt_GetTimeRemaining
(
    Gpt_ChannelType Channel
);
#endif /* GPT_TIME_REMAINING_API == STD_ON */

#if (GPT_PREDEFTIMER_EN == STD_ON)
extern FUNC(Std_ReturnType, GPT_PUBLIC_CODE) Gpt_GetPredefTimerValue
(
    Gpt_PredefTimerType PredefTimer,
    /* #Violation: Gpt_h_REF_1 */
    P2VAR(uint32, AUTOMATIC, GPT_APPL_DATA) TimeValuePtr
); 
#endif /* GPT_PREDEFTIMER_EN == STD_ON */

extern FUNC(void, GPT_PUBLIC_CODE) Gpt_StartTimer
(
    Gpt_ChannelType Channel, Gpt_ValueType Value
);

extern FUNC(void, GPT_PUBLIC_CODE) Gpt_StopTimer
(
    Gpt_ChannelType Channel
);

#if (GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON )
extern FUNC(void, GPT_PUBLIC_CODE) Gpt_EnableNotification
(
    Gpt_ChannelType Channel
);

extern FUNC(void, GPT_PUBLIC_CODE) Gpt_DisableNotification
(
    Gpt_ChannelType Channel
);
#endif /* GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON */

#if (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON)
FUNC(void, GPT_PUBLIC_CODE) Gpt_SetMode
(
    Gpt_ModeType  Mode
);

FUNC(void, GPT_PUBLIC_CODE) Gpt_DisableWakeup
(
    Gpt_ChannelType Channel
);

FUNC(void, GPT_PUBLIC_CODE) Gpt_EnableWakeup
(
    Gpt_ChannelType Channel
);

FUNC(void, GPT_PUBLIC_CODE) Gpt_CheckWakeup
(
    EcuM_WakeupSourceType WakeupSource
);
#endif /* (GPT_WAKEUP_FUNCTIONALITY_API  \== STD_ON) */

extern FUNC(void, GPT_PUBLIC_CODE)Gpt_Gtm_ISRHandler
(
    uint8 ModuleIndex, 
    uint8 Channel
);

extern FUNC(void, GPT_PUBLIC_CODE)Gpt_Basetimer_ISRHandler
(
    uint8 HwChannel
);

/* #Violation: Gpt_h_REF_2 */
#define GPT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Gpt_MemMap.h"

#endif /* GPT_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

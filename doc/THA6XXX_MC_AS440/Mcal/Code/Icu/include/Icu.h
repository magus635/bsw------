/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Icu.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GTM-TIM
 *
 *   brief                 : This file contains all functions of Icu Driver
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
*#Icu_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers
*
*#Icu_h_REF_2:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*/

#ifndef ICU_H_
#define ICU_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* \[SWS_Icu_00245]*/
#include "Icu_Cfg.h"
#include "Icu_GeneralTypes.h"
#include "Icu_Version.h"
#include "Icu_PBcfg.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* Service ID of Icu_Init */
#define ICU_INIT_SID                     (0U) /* 0x00 */

/* Service ID of Icu_DeInit */
#define ICU_DEINIT_SID                   (1U) /* 0x01 */

#if (ICU_SET_MODE_API == STD_ON)
/* Service ID of Icu_SetMode */
#define ICU_SET_MODE_SID                 (2U) /* 0x02 */
#endif /* (ICU_SET_MODE_API \== STD_ON) */

#if (ICU_DISABLE_WAKEUP_API == STD_ON)
/* Service ID of Icu_DisableWakeup */
#define ICU_DISABLE_WAKEUP_SID           (3U) /* 0x03 */
#endif /* (ICU_DISABLE_WAKEUP_API \== STD_ON) */

#if (ICU_ENABLE_WAKEUP_API == STD_ON)
/* Service ID of Icu_EnableWakeup */
#define ICU_ENABLE_WAKEUP_SID            (4U) /* 0x04 */
#endif /* (ICU_ENABLE_WAKEUP_API \== STD_ON) */

/* Service ID of Icu_SetActivationCondition */
#define ICU_SET_ACTIVATION_CONDITION_SID (5U) /* 0x05 */

/* Service ID of Icu_DisableNotification */
#define ICU_DISABLE_NOTIFICATION_SID     (6U) /* 0x06 */

/* Service ID of Icu_EnableNotification */
#define ICU_ENABLE_NOTIFICATION_SID      (7U) /* 0x07 */

/* Service ID of Icu_GetInputState */
#define ICU_GET_INPUT_STATE_SID          (8U) /* 0x08 */

/* Service ID of Icu_StartTimestamp */
#define ICU_START_TIMESTAMP_SID          (9U) /* 0x09 */
/* \[SWS_Icu_00382] Development Error Types */
/* Service ID of Icu_StopTimestamp */
#define ICU_STOP_TIMESTAMP_SID           (10U) /* 0x0a */

/* Service ID of Icu_GetTimestampIndex */
#define ICU_GET_TIMESTAMP_INDEX_SID      (11U) /* 0x0b */

/* Service ID of Icu_ResetEdgeCount */
#define ICU_RESET_EDGE_COUNT_SID         (12U) /* 0x0c */

/* Service ID of Icu_EnableEdgeCount */
#define ICU_ENABLE_EDGE_COUNT_SID        (13U) /* 0x0d */

/* Service ID of Icu_DisableEdgeCount */
#define ICU_DISABLE_EDGE_COUNT_SID       (14U) /* 0x0e */

/* Service ID of Icu_GetEdgeNumbers */
#define ICU_GET_EDGE_NUMBERS_SID         (15U) /* 0x0f */

/* Service ID of Icu_GetTimeElapsed */
#define ICU_GET_TIME_ELAPSED_SID         (16U) /* 0x10 */

/* Service ID of Icu_GetDutyCycleValues */
#define ICU_GET_DUTY_CYCLE_VALUES_SID    (17U) /* 0x11 */

/* Service ID of Icu_GetVersionInfo */
#define ICU_GET_VERSION_INFO_SID         (18U) /* 0x12 */

/* Service ID of Icu_StartSignalMeasurement */
#define ICU_START_SIGNAL_MEASUREMENT_SID (19U) /* 0x13 */

/* Service ID of Icu_StopSignalMeasurement */
#define ICU_STOP_SIGNAL_MEASUREMENT_SID  (20U) /* 0x14 */

#if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
/* Service ID of Icu_CheckWakeup */
#define ICU_CHECK_WAKEUP_SID             (21U) /* 0x15 */
#endif /* (ICU_WAKEUP_FUNCTIONALITY_API \== STD_ON) */

/* Service ID of Icu_EnableEdgeDetection */
#define ICU_ENABLE_EDGE_DETECTION_SID    (22U) /* 0x16 */

/* Service ID of Icu_DisableEdgeDetection */
#define ICU_DISABLE_EDGE_DETECTION_SID   (23U) /* 0x17 */

/* other */
/* Service ID of Icu_Tim_ISRHandler */
#define ICU_SID_ISR                      (48U) /* 0x30 */

/* Service ID of Icu_EnableMultiEdgeDetection */
#define ICU_ENABLE_MULTI_EDGE_DETECTION_SID  (49U) /* 0x31 */


/* \[SWS_Icu_00382] Development Error Types*/
/* DET code to report that  API IS called with invalid pointer */
#define ICU_E_PARAM_POINTER              (10U) /* 0x0a */

/* DET code to report that API service used with an invalid Channel Identifier */
#define ICU_E_PARAM_CHANNEL              (11U) /* 0x0b */

/* DET code to report that API service used with an invalid or not feasible activation */
#define ICU_E_PARAM_ACTIVATION           (12U) /* 0x0c */

/* DET code to report that Init function failed */
#define ICU_E_INIT_FAILED                (13U) /* 0x0d */

/* DET code to report that API service used with an invalid buffer size. */
#define ICU_E_PARAM_BUFFER_SIZE          (14U) /* 0x0e */

#if (ICU_SET_MODE_API == STD_ON)
/* DET code to report that API service Icu_SetMode used with invalid mode */
#define ICU_E_PARAM_MODE                 (15U) /* 0x0f */
#endif /* (ICU_SET_MODE_API \== STD_ON) */

/* DET code to report that API service used without module initialization. */
#define ICU_E_UNINIT                     (20U) /* 0x14 */

#if (ICU_SET_MODE_API == STD_ON)
/* DET code to report that the API Icu_SetMode used during a running operation.*/
#define ICU_E_BUSY_OPERATION             (22U) /* 0x16 */
#endif /* (ICU_SET_MODE_API \== STD_ON) */


/* DET code to report that ICU is already initialized when Icu_Init() is called */
#define ICU_E_ALREADY_INITIALIZED        (23U) /* 0x17 */

/* DET code to report that API Icu_StartTimeStamp is called and the parameter NotifyInterval is invalid (e.g <1) */
#define ICU_E_PARAM_NOTIFY_INTERVAL      (24U) /* 0x18 */

/* DET code to report that the API Icu_GetVersionInfo invoked with a null pointer */
#define ICU_E_PARAM_VINFO                (25U) /* 0x19 */


/* extend Errors */
/* Report DET ICU module not configured for current Core */
#define ICU_E_CORE_NOT_CONFIGURED        (241U) /* 0xF1 */
/* ICU channel is not allocated to current core */
#define ICU_E_CORE_CHANNEL_MISMATCH      (242U) /* 0xF2 */
/* Icu_DisableNotification is invoked when notification is already disabled.*/
#define ICU_E_ALREADY_DISABLED           (244U) /* 0xF4 */
/* Icu_EnableNotification is invoked when notification is already enabled */
#define ICU_E_ALREADY_ENABLED            (245U) /* 0xF5 */
/*Edge num is zero in API Icu_EnableMultiEdgeDetection*/
#define ICU_E_ERROR_EDGE_NUMBER          (246U) /* 0xF6 */
/*operate normal api in sleep mode*/
#define ICU_E_INVALID_MODE               (247U) /* 0xF7 */
/* Safety check failed */
#define ICU_E_SAFETY_CHECK_FAILED        (248U)
#define ICU_E_GETLOCK_FAILED             (249U)

/* RUN TIME ERROR */
/* API Icu_StopTimestamp used on a channel which was not started or already stopped */
#define ICU_E_NOT_STARTED                 (21U) /* 0x15 */
#define ICU_E_STARTED                     (240U) /* 0xF0 */




/*****************************************************************************************************
**                      Global Variables
*****************************************************************************************************/


/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Icu_h_REF_1 */
#define ICU_START_SEC_CODE_ASIL_D_GLOBAL
#include "Icu_MemMap.h"

extern FUNC(void, ICU_CODE) Icu_Init
(
    P2CONST(Icu_ConfigType, AUTOMATIC, ICU_CONFIG_DATA) ConfigPtr
);
#if (ICU_DE_INIT_API == STD_ON)
extern FUNC(void, ICU_CODE) Icu_DeInit
(
    void
);
#endif /* (ICU_DE_INIT_API  \== STD_ON) */

extern FUNC(void, ICU_CODE) Icu_SetActivationCondition
(
    Icu_ChannelType Channel, 
    Icu_ActivationType Activation
);
extern FUNC(void, ICU_CODE) Icu_DisableNotification
(
    Icu_ChannelType Channel
);

extern FUNC(void, ICU_CODE) Icu_EnableNotification
(
    Icu_ChannelType Channel
);

#if (ICU_GET_INPUT_STATE_API == STD_ON)
extern FUNC(Icu_InputStateType, ICU_CODE) Icu_GetInputState
(
    Icu_ChannelType Channel
);
#endif /* (ICU_GET_INPUT_STATE_API  \== STD_ON) */

#if (ICU_TIMESTAMP_API == STD_ON)
extern FUNC(void, ICU_CODE) Icu_StartTimestamp
(
    Icu_ChannelType Channel,
/* #Violation: Icu_h_REF_2 */
    P2VAR(Icu_ValueType, AUTOMATIC, ICU_APPL_DATA) BufferPtr,
    uint16 BufferSize,
    uint16 NotifyInterval
);

extern FUNC(void, ICU_CODE) Icu_StopTimestamp
(
    Icu_ChannelType Channel
);

extern FUNC(Icu_IndexType, ICU_CODE) Icu_GetTimestampIndex
(
    Icu_ChannelType Channel
);
#endif /* (ICU_TIMESTAMP_API  \== STD_ON) */

#if (ICU_EDGE_COUNT_API == STD_ON)
extern FUNC(void, ICU_CODE) Icu_ResetEdgeCount
(
    Icu_ChannelType Channel
);

extern FUNC(void, ICU_CODE) Icu_EnableEdgeCount
(
    Icu_ChannelType Channel
);

extern FUNC(void, ICU_CODE) Icu_DisableEdgeCount
(
    Icu_ChannelType     Channel
);

extern FUNC(Icu_EdgeNumberType, ICU_CODE) Icu_GetEdgeNumbers
(
    Icu_ChannelType Channel
);

#endif /* (ICU_EDGE_COUNT_API  \== STD_ON) */

#if (ICU_EDGE_DETECT_API == STD_ON)
extern FUNC(void, ICU_CODE) Icu_EnableEdgeDetection
(
    Icu_ChannelType Channel
);
extern FUNC(void, ICU_CODE) Icu_DisableEdgeDetection
(
    Icu_ChannelType Channel
);
extern FUNC(void, ICU_CODE) Icu_EnableMultiEdgeDetection
(
    Icu_ChannelType Channel, 
    uint32 EdgeCount
);
#endif /* (ICU_EDGE_DETECT_API  \== STD_ON) */

#if (ICU_SIGNAL_MEASUREMENT_API == STD_ON)

extern FUNC(void, ICU_CODE) Icu_StartSignalMeasurement
(
    Icu_ChannelType Channel
);

extern FUNC(void, ICU_CODE) Icu_StopSignalMeasurement
(
    Icu_ChannelType Channel
);

#endif /* (ICU_SIGNAL_MEASUREMENT_API  \== STD_ON) */

#if (ICU_GET_TIME_ELAPSED_API == STD_ON)
extern FUNC(Icu_ValueType, ICU_CODE) Icu_GetTimeElapsed
(
    Icu_ChannelType Channel
);
#endif /* (ICU_GET_TIME_ELAPSED_API  \== STD_ON) */

#if (ICU_GET_DUTY_CYCLE_VALUES_API == STD_ON)
extern FUNC(void, ICU_CODE) Icu_GetDutyCycleValues
(
    Icu_ChannelType Channel, 
/* #Violation: Icu_h_REF_2 */
    P2VAR(Icu_DutyCycleType, AUTOMATIC, ICU_APPL_DATA) DutyCycleValues
);
#endif /* (ICU_GET_DUTY_CYCLE_VALUES_API  \== STD_ON) */

#if (ICU_GET_VERSION_INFO_API == STD_ON)

extern FUNC(void, ICU_CODE) Icu_GetVersionInfo
(
/* #Violation: Icu_h_REF_2 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, ICU_APPL_DATA) versioninfo
);
#endif /* (ICU_GET_VERSION_INFO_API  \== STD_ON) */

extern FUNC(void, ICU_FAST_CODE) Icu_Tim_ISRHandler
(
  uint8 ModuleIndex,  
  uint8 Channel
);

#if (ICU_ENABLE_WAKEUP_API == STD_ON)

void Icu_EnableWakeup
(
    Icu_ChannelType Channel
);
#endif /* (ICU_ENABLE_WAKEUP_API  \== STD_ON) */ 

#if (ICU_WAKEUP_FUNCTIONALITY_API == STD_ON)
void Icu_CheckWakeup
(
    EcuM_WakeupSourceType WakeupSource
);
#endif /* ((ICU_WAKEUP_FUNCTIONALITY_API  \== STD_ON) */
#if (ICU_DISABLE_WAKEUP_API == STD_ON)
void Icu_DisableWakeup
(
    Icu_ChannelType Channel
);
#endif /* (ICU_DISABLE_WAKEUP_API  \== STD_ON) */ 
#if (ICU_SET_MODE_API == STD_ON)
void Icu_SetMode
(
    Icu_ModeType Mode
);
#endif /* (ICU_SET_MODE_API  \== STD_ON) */ 


/* #Violation: Icu_h_REF_1 */
#define ICU_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Icu_MemMap.h"

#endif /* ICU_H_ */

/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/

/****************************************************************************************************
 *
 ***************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Ocu.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GTM-ATOM
 *
 *   brief                 : This file contains all function declarations of Ocu Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ***************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/

#ifndef OCU_H_
#define OCU_H_

/****************************************************************************************************
 **                          Includes                                                              **
 ***************************************************************************************************/
/* SWS_Ocu_00002:
 * Ocu.h shall include Ocu_Cfg.h */
#include "Ocu_Cfg.h"
#include "Ocu_PBcfg.h"
/* SWS_Ocu_00003:
 * Ocu.h shall include Std_Types.h */
#include "Std_Types.h"
#include "Ocu_GeneralTypes.h"
#include "Ocu_Version.h"
/*****************************************************************************************************
 **                      Global Variables                                                           **
 ****************************************************************************************************/

/****************************************************************************************************
 **                          Global Macro Definitions                                              **
 ****************************************************************************************************/
/* The channel counter range of atom */
#define OCU_ATOM_COUNTER_RANGE_MASK               (0xFFFFFFU)
/* The border of tbu to judge past and future */
#define OCU_TBU_BORDER_PAST_FUTURE                (0x800000U)

/* Development error values */
/* API service used without module initialization */
#define OCU_E_UNINIT                              ((uint8)0x02U)
/* API service used with an invalid channel Identifier  */
#define OCU_E_PARAM_INVALID_CHANNEL               ((uint8)0x03U)
/* API service used with an invalid pin state */
#define OCU_E_PARAM_INVALID_STATE                 ((uint8)0x04U)
/* API service used with invalid pin action */
#define OCU_E_PARAM_INVALID_ACTION                ((uint8)0x05U)
/* API service used when no notification function is configured */
#define OCU_E_NO_VALID_NOTIF                      ((uint8)0x06U)
/* Init function: Ocu_Init called while driver already initialized */
#define OCU_E_ALREADY_INITIALIZED                 ((uint8)0x07U)
/* API service called with invalid pointer */
#define OCU_E_PARAM_POINTER                       ((uint8)0x08U)
/* API Service Ocu_StartChannel called on a RUNNING channel */
#define OCU_E_BUSY                                ((uint8)0x09U)
/* API Service used on a channel with no pin */
#define OCU_E_PARAM_NO_PIN                        ((uint8)0x0AU)
/* API Service used with NULL  pointer */
#define OCU_E_INIT_FAILED                         ((uint8)0x0BU)

/* Extend Errors */
/* Report DET OCU channel not configured for current Core */
#define OCU_E_CORE_NOT_CONFIGURED                 ((uint8)0xE0U)
/* OCU channel is not allocated to current core */
#define OCU_E_CORE_CHANNEL_MISMATCH               ((uint8)0xE1U)
/* API service used with wrong Reference values */
#define OCU_E_PARAM_REF_VALUE                     ((uint8)0xE2U)
/* API service used with wrong compare values */
#define OCU_E_PARAM_COMPARE_VALUE                 ((uint8)0xE3U)
/* API Service write register error */
#define OCU_E_WRITE_REGISTER                      ((uint8)0xE4U)

/* API Service ID's */
/* API Service ID for Ocu_Init() */
#define OCU_SID_INIT                              (0x00U)
/* API Service ID for Ocu_DeInit() */
#define OCU_SID_DEINIT                            (0x01U)
/* API Service ID for Ocu_StartChannel() */
#define OCU_SID_STARTCHANNEL                      (0x02U)
/* API Service ID for Ocu_StopChannel() */
#define OCU_SID_STOPCHANNEL                       (0x03U)
/* API Service ID for Ocu_SetPinState() */
#define OCU_SID_SETPINSTATE                       (0x04U)
/* API Service ID for Ocu_SetPinAction() */
#define OCU_SID_SETPINACTION                      (0x05U)
/* API Service ID for Ocu_GetCounter() */
#define OCU_SID_GETCOUNTER                        (0x06U)
/* API Service ID for Ocu_SetAbsoluteThreshold() */
#define OCU_SID_SETABSOLUTETHRESHOLD              (0x07U)
/* API Service ID for Ocu_SetRelativeThreshold() */
#define OCU_SID_SETRELATIVETHRESHOLD              (0x08U)
/* API Service ID for Ocu_GetVersionInfo */
#define OCU_SID_GETVERSIONINFO                    (0x09U)
/* API Service ID for Ocu_DisableNotification() */
#define OCU_SID_DISABLENOTIFICATION               (0x0AU)
/* API Service ID for Ocu_EnableNotification() */
#define OCU_SID_ENABLENOTIFICATION                (0x0BU)

/* API Service ID for Isr based on GTM-ATOM */
#define OCU_SID_GTM_ATOM_COMPAREMATCH_ISHANDLER   (0xE0U)


/****************************************************************************************************
 **                          Global Function Declarations                                           **
 ****************************************************************************************************/
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_Init
(
    P2CONST(Ocu_ConfigType, OCU_VAR, OCU_APPL_CONST) ConfigPtr
);

#if (OCU_DE_INIT_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_DeInit
(
    void
);
#endif

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_EnableNotification
(
    Ocu_ChannelType ChannelNumber
);
#endif

#if (OCU_NOTIFICATION_SUPPORTED == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_DisableNotification
(
    Ocu_ChannelType ChannelNumber
);
#endif

#if (OCU_SET_PIN_ACTION_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_SetPinAction
(
    Ocu_ChannelType ChannelNumber,
    Ocu_PinActionType OutputAction
);
#endif

#if (OCU_SET_PIN_STATE_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_SetPinState
(
    Ocu_ChannelType ChannelNumber,
    Ocu_PinStateType PinState
);
#endif

extern FUNC(void, OCU_PUBLIC_CODE) Ocu_StartChannel 
(
    Ocu_ChannelType ChannelNumber
);

extern FUNC(void, OCU_PUBLIC_CODE) Ocu_StopChannel 
(
    Ocu_ChannelType ChannelNumber
);

#if (OCU_GET_COUNTER_API == STD_ON)
extern FUNC(Ocu_ValueType, OCU_PUBLIC_CODE) Ocu_GetCounter 
(
    Ocu_ChannelType ChannelNumber
);
#endif

#if (OCU_SET_ABSOLUTE_THRESHOLD_API == STD_ON)
extern FUNC(Ocu_ReturnType, OCU_PUBLIC_CODE) Ocu_SetAbsoluteThreshold
(
    Ocu_ChannelType ChannelNumber,
    Ocu_ValueType ReferenceValue,
    Ocu_ValueType AbsoluteValue
);
#endif

#if (OCU_SET_RELATIVE_THRESHOLD_API == STD_ON)
extern FUNC(Ocu_ReturnType, OCU_PUBLIC_CODE) Ocu_SetRelativeThreshold
(
    Ocu_ChannelType ChannelNumber,
    Ocu_ValueType RelativeValue
);
#endif

#if (OCU_VERSION_INFO_API == STD_ON)
extern FUNC(void, OCU_PUBLIC_CODE) Ocu_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, OCU_APPL_DATA) VersionInfoPtr
);
#endif /* (OCU_VERSION_INFO_API  \== STD_ON) */

extern FUNC(void, OCU_PUBLIC_CODE) Ocu_Gtm_Atom_CompareMatch_ISRHandler
(
    uint8 ModuleIndex,  
    uint8 Channel
);

/****************************************************************************************************
 **                          End of File                                                            **
 ****************************************************************************************************/

#endif /* OCU_H_ */

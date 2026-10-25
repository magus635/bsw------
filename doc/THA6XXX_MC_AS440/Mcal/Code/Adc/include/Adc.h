/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Adc.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SARADC
*
*   brief                 : This file contains all function declarations of Adc Driver
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
*#Adc_h_REF_1:MISRAC2012-Rule-20.7; 
* Justification:Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Adc_h_REF_2:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/

#ifndef ADC_H_
#define ADC_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Adc_Cfg.h"
#include "Adc_PBcfg.h"
#include "Adc_GeneralTypes.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Development error values */
/* AUTOSAR DET ID */
/* service is called without Adc Driver initialization */
#define ADC_E_UNINIT                               ((uint8)0x0A)
/* Start service is called while conversion is on going */
#define ADC_E_BUSY                                 ((uint8)0x0B)
/* Stop service is called while no conversion is on going */
#define ADC_E_IDLE                                 ((uint8)0x0C)
/* Initialization service called twice without deinit */
#define ADC_E_ALREADY_INITIALIZED                  ((uint8)0x0D)
/* Initialization service is called with configPtr as NULL */
#define ADC_E_PARAM_CONFIG                         ((uint8)0x0E)
/* Service is called with NULL_PTR  */
#define ADC_E_PARAM_POINTER                        ((uint8)0x14)
/* Service is called with invalid group ID  */
#define ADC_E_PARAM_GROUP                          ((uint8)0x15)
/* Service is called for a group with wrong conversion mode */
#define ADC_E_WRONG_CONV_MODE                      ((uint8)0x16)
/* Service is called for a group with wrong trigger source */
#define ADC_E_WRONG_TRIGG_SRC                      ((uint8)0x17)
/* Enable/disable notification function for a group whose configuration set has
 * no notification available */
#define ADC_E_NOTIF_CAPABILITY                     ((uint8)0x18)
/* Conversion request service is called before initializing the result buffer */
#define ADC_E_BUFFER_UNINIT                        ((uint8)0x19)

#if (ADC_POWER_STATE_SUPPORTED == STD_ON)
/* One or more ADC group/channel not in IDLE state */
#define ADC_E_NOT_DISENGAGED                       ((uint8)0x1A)
/* Unsupported power state request */
#define ADC_E_POWER_STATE_NOT_SUPPORTED            ((uint8)0x1B)
/* Requested power state can not be reached directly */
#define ADC_E_TRANSITION_NOT_POSSIBLE              ((uint8)0x1C)
/* ADC not prepared for target power state */
#define ADC_E_PERIPHERAL_NOT_PREPARED              ((uint8)0x1D)
#endif /* \(ADC_POWER_STATE_SUPPORTED == STD_ON) */


/* Non-AUTOSAR DET ID */
/* DET ID of API Adc_SetupResultBuffer(), Adc_ReadGroup(), Adc_GetStreamLastPointer()
 * be called with DMA mode */
#define ADC_E_DMA_CHANNEL_ENABLED                  ((uint8)0x20)
/* Service is called with enable the manual result register configuration */
#define ADC_E_MANUAL_RESREG_ENABLED                ((uint8)0x21)

/* No HW unit configuration for specified core */
#define ADC_E_CORE_NOT_CONFIGURED                  ((uint8)0xE0)
/* ADC HwUnit is not allocated to current core */
#define ADC_E_CORE_HWUNIT_MISMATCH                 ((uint8)0xE1)

#if (ADC_SAFETY_ENABLE == STD_ON)
#define ADC_E_REG_CHECK_FAIL                       ((uint8)0xF1)
#endif /* (STD_ON \== ADC_SAFETY_ENABLE) */

/* AUTOSAR service ID */
/* API Service ID for Adc_Init() */
#define ADC_SID_INIT                               ((uint8)0x00)

#if (ADC_DEINIT_API == STD_ON)
/* API Service ID for Adc_DeInit() */
#define ADC_SID_DEINIT                             ((uint8)0x01)
#endif /* (ADC_DEINIT_API  \== STD_ON) */

/* API Service ID for Adc_StartGroupConversion() */
#define ADC_SID_START_GROUP_CONVERSION             ((uint8)0x02)
/* API Service ID for Adc_StopGroupConversion() */
#define ADC_SID_STOP_GROUP_CONVERSION              ((uint8)0x03)
/* API Service ID for Adc_ReadGroup() */
#define ADC_SID_READ_GROUP                         ((uint8)0x04)
/* API Service ID for Adc_EnableHardwareTrigger() */
#define ADC_SID_ENABLE_HARDWARE_TRIGGER            ((uint8)0x05)
/* API Service ID for Adc_DisableHardwareTrigger() */
#define ADC_SID_DISABLE_HARDWARE_TRIGGER           ((uint8)0x06)
/* API Service ID for Adc_EnableGroupNotification() */
#define ADC_SID_ENABLE_GROUP_NOTIFICATION          ((uint8)0x07)
/* API Service ID for Adc_DisableGroupNotification() */
#define ADC_SID_DISABLE_GROUP_NOTIFICATION         ((uint8)0x08)
/* API Service ID for Adc_GetGroupStatus() */
#define ADC_SID_GET_GROUP_STATUS                   ((uint8)0x09)
/* API Service ID for Adc_GetVersionInfo() */
#define ADC_SID_GET_VERSION_INFO                   ((uint8)0x0A)
/* API Service ID for Adc_GetStreamLastPointer() */
#define ADC_SID_GET_STREAM_LAST_POINTER            ((uint8)0x0B)
/* API Service ID for Adc_SetupResultBuffer() */
#define ADC_SID_SETUP_RESULT_BUFFER                ((uint8)0x0C)

#if (ADC_POWER_STATE_SUPPORTED == STD_ON)
/* API Service ID for Adc_SetPowerState() */
#define ADC_SID_SET_POWER_STATE                    ((uint8)0x10)
/* API Service ID for Adc_GetCurrentPowerState() */
#define ADC_SID_GET_CURRENT_POWER_STATE            ((uint8)0x11)
/* API Service ID for Adc_GetTargetPowerState() */
#define ADC_SID_GET_TARGET_POWER_STATE             ((uint8)0x12)
/* API Service ID for Adc_PreparePowerState() */
#define ADC_SID_PREPARE_POWER_STATE                ((uint8)0x13)
#endif /* \(ADC_POWER_STATE_SUPPORTED == STD_ON) */

/* API service ID for request queue interrupt */
#define ADC_SID_REQ_QUEUE_ISR                      ((uint8)0xE0)


/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/* #Violation: Adc_h_REF_2*/
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"

extern FUNC(void, ADC_PUBLIC_CODE) Adc_Init
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) ConfigPtr
);

#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
extern FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_SetupResultBuffer
(
    Adc_GroupType Group,
    /* #Violation: Adc_h_REF_1*/
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr
);
#endif /* ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE \== STD_ON)) */

#if (ADC_DEINIT_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DeInit
(
    void
);
#endif /* (ADC_DEINIT_API  \== STD_ON) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_StartGroupConversion
(
    Adc_GroupType Group
);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API  \== STD_ON) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_StopGroupConversion
(
    Adc_GroupType Group
);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API  \== STD_ON) */

#if (ADC_READ_GROUP_API == STD_ON)
#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
extern FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_ReadGroup
(
    Adc_GroupType Group,
    /* #Violation: Adc_h_REF_1*/
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) DataBufferPtr
);
#endif /* ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE \== STD_ON)) */
#endif /* (ADC_READ_GROUP_API  \== STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_EnableHardwareTrigger
(
    Adc_GroupType Group
);
#endif /* (ADC_HW_TRIGGER_API  \== STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DisableHardwareTrigger
(
    Adc_GroupType Group
);
#endif /* (ADC_HW_TRIGGER_API  \== STD_ON) */

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_EnableGroupNotification
(
    Adc_GroupType Group
);
#endif /* (ADC_GRP_NOTIF_CAPABILITY  \== STD_ON) */

#if (ADC_GRP_NOTIF_CAPABILITY == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_DisableGroupNotification
(
    Adc_GroupType Group
);
#endif /* (ADC_GRP_NOTIF_CAPABILITY  \== STD_ON) */

extern FUNC(Adc_StatusType, ADC_PUBLIC_CODE) Adc_GetGroupStatus
(
    Adc_GroupType Group
);

#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE == STD_ON))
extern FUNC(Adc_StreamNumSampleType, ADC_PUBLIC_CODE) Adc_GetStreamLastPointer
(
    Adc_GroupType Group,
    /* #Violation: Adc_h_REF_1*/
    P2P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) PtrToSamplePtr
);
#endif /* ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_POLLING_MODE_ENABLE \== STD_ON)) */

#if (ADC_VERSION_INFO_API == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Adc_GetVersionInfo
(
    /* #Violation: Adc_h_REF_1*/
    P2VAR(Std_VersionInfoType , AUTOMATIC, ADC_APPL_DATA) VersionInfoPtr
);
#endif /* (ADC_VERSION_INFO_API  \== STD_ON) */

#if (ADC_POWER_STATE_SUPPORTED == STD_ON)
extern FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_SetPowerState
(
    P2VAR(Adc_PowerStateRequestResultType, AUTOMATIC, ADC_APPL_DATA) ResultPtr
);

extern FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_GetCurrentPowerState
(
    P2VAR(Adc_PowerStateType, AUTOMATIC, ADC_APPL_DATA) CurrentPowerState,
    P2VAR(Adc_PowerStateRequestResultType, AUTOMATIC, ADC_APPL_DATA) ResultPtr
);

extern FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_GetTargetPowerState
(
    P2VAR(Adc_PowerStateType, AUTOMATIC, ADC_APPL_DATA) TargetPowerState,
    P2VAR(Adc_PowerStateRequestResultType, AUTOMATIC, ADC_APPL_DATA) ResultPtr
);

extern FUNC(Std_ReturnType, ADC_PUBLIC_CODE) Adc_PreparePowerState
(
    Adc_PowerStateType PowerState,
    P2VAR(Adc_PowerStateRequestResultType, AUTOMATIC, ADC_APPL_DATA) ResultPtr
);
#endif /* (ADC_POWER_STATE_SUPPORTED  \== STD_ON) */

#if ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE == STD_ON))
extern FUNC(void, ADC_PUBLIC_CODE) Adc_QueueRequest_ISRHandler
(
    Adc_HwUnitType PhyHwUnitId,
    Saradc_RequestSource ReqSrc
);
#endif /* ((ADC_INTERRUPT_MODE_ENABLE == STD_ON) || (ADC_DMA_MODE_ENABLE \== STD_ON)) */
/* #Violation: Adc_h_REF_2 */
#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"

#endif /* ADC_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dsadc.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DSADC
*
*   brief                 : This file contains all function declarations of Dsadc Driver
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
*#Dsadc_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Dsadc_h_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for different configurations.
*
*#Dsadc_h_REF_3:MISRAC2012-Rule-20.7;
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*/

#ifndef DSADC_H_
#define DSADC_H_

/****************************************************************************************************
*                               Include
****************************************************************************************************/
#include "Dsadc_GeneralTypes.h"
#include "Dsadc_Cfg.h"
#include "Dsadc_PBcfg.h"

/****************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/*Development errors*/
#if (DSADC_DEV_ERROR_DETECT == STD_ON)

/* Service is called without Dsadc Driver initialization */
#define DSADC_E_UNINIT                                     ((uint8)0x0AU)
/* Start service is called while conversion is on going */
#define DSADC_E_BUSY                                       ((uint8)0x0BU)
/* Stop service is called while no conversion is on going */
#define DSADC_E_IDLE                                       ((uint8)0x0CU)
/* Initialization service called twice without deinit */
#define DSADC_E_ALREADY_INITIALIZED                        ((uint8)0x0DU)
/* Initialization service is called with configPtr as NULL */
#define DSADC_E_PARAM_CONFIG                               ((uint8)0x0EU)
/* Master core is not initialized when slave call Dsadc_Init */
#define DSADC_E_MASTER_CORE_UNINITIALIZE                   ((uint8)0x10U)
/* There are slave cores that have not been de-initialized when call Dsadc_DeInit */
#define DSADC_E_SLAVE_CORE_INITIALIZED                     ((uint8)0x11U)
/* Service is called with NULL_PTR  */
#define DSADC_E_PARAM_POINTER                              ((uint8)0x14U)
/* Service is called with wrong channel identifier */
#define DSADC_E_PARAM_CHANNEL                              ((uint8)0x15U)
/* Service is called while conversion is in calibration process */
/* #Violation: Dsadc_h_REF_1 */
#define DSADC_E_CALIBRATION                                ((uint8)0x16U)
/* Enable/disable notification function for a channel whose configuration set has
 * no notification available */
#define DSADC_E_NOTIF_CAPABILITY                           ((uint8)0x17U)
/* Conversion request service is called before initializing the result buffer */
#define DSADC_E_BUFFER_UNINIT                              ((uint8)0x18U)

/* Service is called with DMA mode */
#define DSADC_E_DMA_ENABLED                                ((uint8)0x1AU)
/* Service is called with single access mode */
#define DSADC_E_SINGLE_ENABLED                             ((uint8)0x1BU)

/* Service is called when timestamp is not supported */
#define DSADC_E_TIMESTAMP_NOT_SUPPORTED                    ((uint8)0x1CU)

/* Service is called when auxiliary filter chain is not enabled */
#define DSADC_E_AUX_FILTER_DISABLED                        ((uint8)0x1DU)
/* Service is called when auxiliary filter conversion result acquisition is disabled */
/* #Violation: Dsadc_h_REF_1 */
#define DSADC_E_AUX_RESULT_DISABLED                        ((uint8)0x1EU)

/* Service is called while carrier signal generator is opened */
/* #Violation: Dsadc_h_REF_1 */
#define DSADC_E_CARRIER_ALREADY_OPENDED                    ((uint8)0x20U)
/* Service is called while carrier signal generator is closed */
/* #Violation: Dsadc_h_REF_1 */
#define DSADC_E_CARRIER_ALREADY_CLOSED                     ((uint8)0x21U)
/* Service is called while carrier signal generator is not configured */
/* #Violation: Dsadc_h_REF_1 */
#define DSADC_E_CARRIER_DISABLED                           ((uint8)0x22U)

/* No HW unit configuration for specified core */
#define DSADC_E_CORE_NOT_CONFIGURED                        ((uint8)0xE0U)
/* DSADC HwUnit is not allocated to current core */
#define DSADC_E_CORE_HWUNIT_MISMATCH                       ((uint8)0xE1U)

#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */


#if (DSADC_SAFETY_ENABLE == STD_ON)
/* Safety check error */
#define DSADC_E_SAFETY_CHECK_FAILED                        ((uint8)0xE2U)
#endif /* \(DSADC_SAFETY_ENABLE == STD_ON) */


/* AUTOSAR service ID */
/* API Service ID for Dsadc_Init() */
#define DSADC_SID_INIT                                     ((uint8)0x00U)
/* API service ID for Dsadc_DeInit() */
#define DSADC_SID_DEINIT                                   ((uint8)0x01U)
/* API service ID for Dsadc_SetupBuffer() */
#define DSADC_SID_SETUPRESULTBUFFER                        ((uint8)0x02U)
/* API service ID for Dsadc_StartConversion() */
#define DSADC_SID_STARTCONVERSION                          ((uint8)0x03U)
/* API service ID for Dsadc_StopConversion() */
#define DSADC_SID_STOPCONVERSION                           ((uint8)0x04U)
/* API service ID for Dsadc_GetStreamLastPointer() */
#define DSADC_SID_GETSTREAMLASTPOINTER                     ((uint8)0x05U)
/* API service ID for Dsadc_GetChannelStatus() */
#define DSADC_SID_GETSTATUS                                ((uint8)0x06U)
/* API service ID for Dsadc_StartCarrierSignal() */
/* #Violation: Dsadc_h_REF_1 */
#define DSADC_SID_STARTCARRIERSIGNAL                       ((uint8)0x09U)
/* API service ID for Dsadc_StopCarrierSignal() */
/* #Violation: Dsadc_h_REF_1 */
#define DSADC_SID_STOPCARRIERSIGNAL                        ((uint8)0x0AU)
/* API service ID for Dsadc_GetTimestamp() */
#define DSADC_SID_GETTIMESTAMP                             ((uint8)0x0BU)
/* API service ID for Dsadc_EnableNotification() */
#define DSADC_SID_ENABLENOTIFICATION                       ((uint8)0x0CU)
/* API service ID for Dsadc_DisableNotification() */
#define DSADC_SID_DISABLENOTIFICATION                      ((uint8)0x0DU)
/* API service ID for Dsadc_GetVersionInfo() */
#define DSADC_SID_GETVERSIONINFO                           ((uint8)0x0EU)
/* API service ID for Dsadc_SetCarrierSyncParam() */
/* #Violation: Dsadc_h_REF_1 */
#define DSADC_SID_SETCARRIERSYNCPARAM                      ((uint8)0x10U)
/* API service ID for Dsadc_GetCarrierDelayValue() */
/* #Violation: Dsadc_h_REF_1 */
#define DSADC_SID_GETCARRIERDELAYVALUE                     ((uint8)0x11U)

/* API service ID for Dsadc_AuxiliaryChannel_ISRHandler() */
#define DSADC_SID_AUXCHANNEL_ISR                           ((uint8)0xE0U)
/* API service ID for Dsadc_MainAuxiliaryChannel_ISRHandler() */
#define DSADC_SID_MAINCHANNEL_ISR                          ((uint8)0xE1U)



/* Macros for carrier wave signal */
/* No carrier signal output */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_CARRIER_STOPPED                              (DSADC_WAVESELECT_NONE)
/* Sine wave output */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_CARRIER_SINE                                 (DSADC_WAVESELECT_SINE)
/* Triangle wave output */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_CARRIER_TRIANGLE                             (DSADC_WAVESELECT_TRIANGULAR)
/* Square wave output */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_CARRIER_SQUARE                               (DSADC_WAVESELECT_SQUARE)

/* Macros for gain */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_INPUT_GAIN_0dB                               (DSADC_PGAGAIN_0DB)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_INPUT_GAIN_6dB                               (DSADC_PGAGAIN_6DB)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_INPUT_GAIN_12dB                              (DSADC_PGAGAIN_12DB)

/* Macros for input multiplexer trigger mode  */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_INPUTMUX_CTRL_SW                         (DSADC_INPUTMULTIPLEXERTRIGGERMODE_SOFTWARE)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_INPUTMUX_CTRL_RISING_EDGE                (DSADC_INPUTMULTIPLEXERTRIGGERMODE_RISING)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_INPUTMUX_CTRL_FALLING_EDGE               (DSADC_INPUTMULTIPLEXERTRIGGERMODE_FALLING)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_INPUTMUX_CTRL_BOTH_EDGES                 (DSADC_INPUTMULTIPLEXERTRIGGERMODE_BOTH)

/* Macros for timestamp trigger edges */
/* No timestamp trigger */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_TIMESTAMP_TRIG_NONE                      (DSADC_TIMESTAMPTRIGGERMODE_NONE)
/* Timestamp is triggered by rising edge */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_TIMESTAMP_TRIG_RISING_EDGE               (DSADC_TIMESTAMPTRIGGERMODE_RISING)
/* Timestamp is triggered by falling edge */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_TIMESTAMP_TRIG_FALLING_EDGE              (DSADC_TIMESTAMPTRIGGERMODE_FALLING)
/* Timestamp is triggered by both edges */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_TIMESTAMP_TRIG_BOTH_EDGES                (DSADC_TIMESTAMPTRIGGERMODE_BOTH)

/* Macros for service Request */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_GATE_NONE                                (DSADC_SERVICEREQUEST_NONE)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_GATE_HIGH_LEVEL                          (DSADC_SERVICEREQUEST_HIGH)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_GATE_LOW_LEVEL                           (DSADC_SERVICEREQUEST_LOW)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_DATA_FIFO_THRESHOLD                      (DSADC_SERVICEREQUEST_FIFOTHRESHOLD)

/* Macros for filter offset compensation */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_OFFSET_COMP_FILTER_DISABLE               (DSADC_FILTEROFFSETCOMPENSATION_0)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_OFFSET_COMP_FILTER_CUTOFF_RATE_1         (DSADC_FILTEROFFSETCOMPENSATION_1)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_OFFSET_COMP_FILTER_CUTOFF_RATE_2         (DSADC_FILTEROFFSETCOMPENSATION_2)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_OFFSET_COMP_FILTER_CUTOFF_RATE_3         (DSADC_FILTEROFFSETCOMPENSATION_3)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_OFFSET_COMP_FILTER_CUTOFF_RATE_4         (DSADC_FILTEROFFSETCOMPENSATION_4)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_OFFSET_COMP_FILTER_CUTOFF_RATE_5         (DSADC_FILTEROFFSETCOMPENSATION_5)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_OFFSET_COMP_FILTER_CUTOFF_RATE_6         (DSADC_FILTEROFFSETCOMPENSATION_6)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_OFFSET_COMP_FILTER_CUTOFF_RATE_7         (DSADC_FILTEROFFSETCOMPENSATION_7)

/* Carrier output normal (cos(A)) */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_NORMAL_MODE                              (FALSE)
/* Carrier output reverse (cos(-A))*/
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_BIT_REVERSE_MODE                         (TRUE)

/* Macros for enable and disable */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_ENABLE                                   (1U)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_DISABLE                                  (0U)

/* Macro for limit checking interrupt event enable flags */
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_LIMITCHECKING_ABOVE_UPPER                ((uint8)DSADC_AUXILIARY_SAUL_INTERRUPT)
/* #Violation: Dsadc_h_REF_2 */
#define DSADC_LIMITCHECKING_BELOW_LOWER                ((uint8)DSADC_AUXILIARY_SBUL_INTERRUPT)


/****************************************************************************************************
*                               Extern Data Declaration
****************************************************************************************************/

/****************************************************************************************************
*                               Extern Function Declaration
****************************************************************************************************/
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dsadc_MemMap.h"

extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_Init
(
    CONSTP2CONST(Dsadc_ConfigType, AUTOMATIC, DSADC_APPL_CONST) ConfigPtr
);

#if (DSADC_CFG_DEINIT_API == STD_ON)
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DeInit
(
    void
);
#endif /* \(ADC_DEINIT_API == STD_ON) */

#if ((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE == STD_ON))
extern FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_SetupResultBuffer
(
    Dsadc_ChannelType Channel,
    /* #Violation: Dsadc_h_REF_3 */
    CONSTP2VAR(Dsadc_ResultType, AUTOMATIC, DSADC_APPL_DATA) DataBufferPtr
);
#endif /* \((DSADC_CFG_INTERRUPT_MODE == STD_ON) || (DSADC_CFG_POLLING_MODE== STD_ON)) */

extern FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_StartConversion
(
    Dsadc_ChannelType Channel
);

extern FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_StopConversion
(
    Dsadc_ChannelType Channel
);

#if (DSADC_CFG_GETSTREAMLASTPOINTER_API == STD_ON)
extern FUNC(Dsadc_NumSampleType, DSADC_PUBLIC_CODE) Dsadc_GetStreamLastPointer
(
    Dsadc_ChannelType Channel,
    /* #Violation: Dsadc_h_REF_3 */
    P2P2VAR(Dsadc_ResultType, AUTOMATIC, DSADC_APPL_DATA) const PtrToSamplePtr
);
#endif /* \(DSADC_CFG_GETSTREAMLASTPOINTER_API == STD_ON) */


extern FUNC(Dsadc_StatusType, DSADC_PUBLIC_CODE) Dsadc_GetChannelStatus
(
    Dsadc_ChannelType Channel,
    Dsadc_ConvChannelType ConvChannel
);

extern FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_StartCarrierSignal
(
    void
);

extern FUNC(Std_ReturnType, DSADC_PUBLIC_CODE) Dsadc_StopCarrierSignal
(
    void
);

#if (DSADC_CFG_SET_CARRIER_SYNC_PARAM_API == STD_ON)
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_SetCarrierSyncParam
(
    P2CONST(Dsadc_CarrierSyncConfigType, AUTOMATIC, DSADC_APPL_CONST) CarrierSyncParamPtr
);
#endif /* \(DSADC_CFG_SET_CARRIER_SYNC_PARAM_API == STD_ON) */

#if (DSADC_CFG_GET_CARRIER_SYNC_DELAY_API == STD_ON)
extern FUNC(uint8, DSADC_PUBLIC_CODE) Dsadc_GetCarrierDelayValue
(
    void
);
#endif /* \(DSADC_CFG_GET_CARRIER_SYNC_DELAY_API == STD_ON) */

#if (DSADC_CFG_TIMESTAMP_ENABLE == STD_ON)
extern FUNC(Dsadc_TimestampType, DSADC_PUBLIC_CODE) Dsadc_GetTimestamp
(
    Dsadc_ChannelType Channel
);
#endif /* \(DSADC_CFG_TIMESTAMP_ENABLE == STD_ON) */

#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_EnableNotification
(
    Dsadc_ChannelType Channel
);

extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_DisableNotification
(
    Dsadc_ChannelType Channel
);
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */

#if (DSADC_CFG_VERSION_INFO_API == STD_ON)
extern FUNC(void, INTC_PUBLIC_CODE) Dsadc_GetVersionInfo
(
    /* #Violation: Dsadc_h_REF_3 */
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, DSADC_APPL_DATA) VersionInfoPtr
);
#endif /* \(DSADC_CFG_VERSION_INFO_API == STD_ON) */

#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
extern FUNC(void, DSADC_PUBLIC_CODE) Dsadc_AuxiliaryChannel_ISRHandler
(
    Dsadc_HWUnitType HwUnitId
);
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
#endif /* \(DSADC_CFG_INTERRUPT_MODE == STD_ON) */

#if (DSADC_CFG_INTERRUPT_MODE == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Dsadc_MainChannel_ISRHandler
(
    Dsadc_HWUnitType HwUnitId
);
#endif /* \(DSADC_CFG_INTERRUPT_MODE == STD_ON) */

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dsadc_MemMap.h"

#endif /* \DSADC_H_ */

/****************************************************************************************************
**                      End of File
****************************************************************************************************/

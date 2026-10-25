/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Adc_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : SARADC
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Dsadc_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef DSADC_CFG_H_
#define DSADC_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

#define DSADC_CFG_AR_RELEASE_MAJOR_VERSION                   (4U)
#define DSADC_CFG_AR_RELEASE_MINOR_VERSION                   (4U)
#define DSADC_CFG_AR_RELEASE_REVISION_VERSION                (0U)

#define DSADC_CFG_SW_MAJOR_VERSION                           (1U)
#define DSADC_CFG_SW_MINOR_VERSION                           (2U)
#define DSADC_CFG_SW_PATCH_VERSION                           (0U)

#define DSADC_CFG_VENDOR_ID                                  (175U)
#define DSADC_CFG_MODULE_ID                                  (255U)


/* Total configuration sets */
#define DSADC_CONFIGSET_CNT                                  (1U)

/*
Configuration: DsadcSafetyErrorDetect
- if Selected, Safety Error Check is Enabled 
- if Deselected, Safety Error Check is Disabled 
*/
#define DSADC_SAFETY_ENABLE                                  (STD_ON)

/*
Configuration: DsadcDevErrorDetect
- if Selected, DET is Enabled 
- if Deselected, DET is Disabled 
*/
#define DSADC_DEV_ERROR_DETECT                               (STD_ON)

/*
Configuration: DsadcDeInitApi
- if Selected, DeInit() API is Enabled 
- if Deselected, DeInit() API is Disabled 
*/
#define DSADC_CFG_DEINIT_API                                 (STD_ON)

/*
Configuration: DsadcDemEventParameterRefs
- if Selected, DEM is Enabled 
- if Deselected, DEM is Disabled 
*/
#define DSADC_DEM_ERROR_REPORT_STATUS                        (STD_OFF)

/*
Configuration: DsadcGetStreamLastPointerApi
- if Selected, Dsadc_GetStreamLastPointer() is Enabled 
- if Deselected, Dsadc_GetStreamLastPointer() is Disabled 
*/
#define DSADC_CFG_GETSTREAMLASTPOINTER_API                   (STD_ON)

/*
Configuration: DsadcVersionInfoApi
- if Selected, Dsadc_GetVersion() is Enabled 
- if Deselected, Dsadc_GetVersion() is Disabled 
*/
#define DSADC_CFG_VERSION_INFO_API                           (STD_ON)

/*
Configuration: DsadcNotifCapability
- if Selected, Notification is Enabled 
- if Deselected, Notification is Disabled 
*/
#define DSADC_CFG_NOTIF_CAPABILITY                           (STD_ON)

/*
Configuration: DsadcTimestampEnable
- if Selected, Notification is Enabled 
- if Deselected, Notification is Disabled 
*/
#define DSADC_CFG_TIMESTAMP_ENABLE                           (STD_ON)

/*
Configuration: DsadcTimestampEnable
- if Selected, Timestamp is Enabled 
- if Deselected, Timestamp is Disabled 
*/
#define DSADC_CFG_CLOCKSYNC_ENABLE                           (DSADC_ENABLE)

/*
Configuration: DsadcIntegratorEnable
- if Selected, Integrator is Enabled 
- if Deselected, Integrator is Disabled 
*/
#define DSADC_CFG_INTEGRATOR_ENABLE                          (DSADC_ENABLE)

/*
Configuration: DsadcAuxLimitCheckingEnable
- if Selected, Auxiliary conversion limit checking is Enabled 
- if Deselected, Auxiliary conversion limit checking is Disabled 
*/
#define DSADC_CFG_LIMIT_CHECKING_ENABLE                      (STD_ON)

/*
Configuration: DsadcAuxiliaryFilterChainEnable
- if Selected, Auxiliary filter is Enabled 
- if Deselected, Auxiliary filter is Disabled 
*/
#define DSADC_CFG_AUX_FILTER_ENABLE                          (STD_ON)

/*
Configuration: DsadcSetCarrierSyncParamApi
- if Selected, Dsadc_SetCarrierSyncValue() is Enabled 
- if Deselected, Dsadc_SetCarrierSyncValue() is Disabled 
*/
#define DSADC_CFG_SET_CARRIER_SYNC_PARAM_API                 (STD_OFF)

/*
Configuration: DsadcGetCarrierDelayValueApi
- if Selected, Dsadc_GetCarrierDelayValue() is Enabled 
- if Deselected, Dsadc_GetCarrierDelayValue() is Disabled 
*/
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_CFG_GET_CARRIER_SYNC_DELAY_API                 (STD_OFF)

/*
Configuration: DsadcInitSyncEnableHWUnit
*/
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_CFG_INIT_SYNC_ENABLE_HWUNIT                    (STD_ON)

/* Total HW units */
#define DSADC_TOTAL_HWUNIT                                   (4U)
/* Total logical channels */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_TOTAL_CHANNEL                                  (DSADC_TOTAL_HWUNIT)
/* HW unit IDs */
#define DSADC_HWUNIT_DSADC0                                  (0U)
#define DSADC_HWUNIT_DSADC1                                  (1U)
#define DSADC_HWUNIT_DSADC2                                  (2U)
#define DSADC_HWUNIT_DSADC3                                  (3U)

/* Interrupt enabled flag */
/* DSADC0 main filter chain interrupt enabled */
#define DSADC_HWUNIT_INT_EN_DSADC0                           (STD_ON)
/* DSADC0 auxiliary filter chain interrupt enabled */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_HWUNIT_AUX_INT_EN_DSADC0                       (STD_ON)
/* DSADC1 main filter chain interrupt enabled */
#define DSADC_HWUNIT_INT_EN_DSADC1                           (STD_ON)
/* DSADC1 auxiliary filter chain interrupt enabled */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_HWUNIT_AUX_INT_EN_DSADC1                       (STD_ON)
/* DSADC2 main filter chain interrupt enabled */
#define DSADC_HWUNIT_INT_EN_DSADC2                           (STD_ON)
/* DSADC2 auxiliary filter chain interrupt disabled */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_HWUNIT_AUX_INT_EN_DSADC2                       (STD_OFF)
/* DSADC3 main filter chain interrupt disabled */
#define DSADC_HWUNIT_INT_EN_DSADC3                           (STD_OFF)
/* DSADC3 auxiliary filter chain interrupt disabled */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_HWUNIT_AUX_INT_EN_DSADC3                       (STD_OFF)

/* Macro for number of HW units(and channels) mapped to each core */
/* The number of hardware units allocated to core0 */
#define DSADC_MAX_HWUNIT_TO_CORE0                            (4U)
/* The number of channels allocated to core0 */
#define DSADC_MAX_CHANNEL_TO_CORE0                           (DSADC_MAX_HWUNIT_TO_CORE0)
/* The number of hardware units allocated to core1 */
#define DSADC_MAX_HWUNIT_TO_CORE1                            (0U)
/* The number of channels allocated to core1 */
#define DSADC_MAX_CHANNEL_TO_CORE1                           (DSADC_MAX_HWUNIT_TO_CORE1)
/* Total number of channels */
#define DSADC_CFG_TOTAL_CHANNELS                             (4U)

/* Macro for channel result handling mode */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_RESULT_HANDLING_INTERRUPT_MODE                 (0U)
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_RESULT_HANDLING_POLLING_MODE                   (1U)
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_RESULT_HANDLING_DMA_MODE                       (2U)

/* Macro for enable the DMA mode */
#define DSADC_CFG_DMA_MODE                                   (STD_ON)
/* Macro for enable the interrupt mode */
#define DSADC_CFG_INTERRUPT_MODE                             (STD_ON)
/* Macro for enable the polling mode */
#define DSADC_CFG_POLLING_MODE                               (STD_OFF)

/****************************************************************************************************
**                          Macro definition of logical channel ID                                 **
****************************************************************************************************/
/* Channel ID0(SingleInt): DSADC0 */
#ifndef DsadcConf_DsadcChannel_SingleInt
#define DsadcConf_DsadcChannel_SingleInt             ((Dsadc_ChannelType)0)
#endif /* DsadcConf_DsadcChannel_SingleInt */

/* Channel ID1(StreamingLinear): DSADC1 */
#ifndef DsadcConf_DsadcChannel_StreamingLinear
#define DsadcConf_DsadcChannel_StreamingLinear             ((Dsadc_ChannelType)1)
#endif /* DsadcConf_DsadcChannel_StreamingLinear */

/* Channel ID2(StreamingCircular): DSADC2 */
#ifndef DsadcConf_DsadcChannel_StreamingCircular
#define DsadcConf_DsadcChannel_StreamingCircular             ((Dsadc_ChannelType)2)
#endif /* DsadcConf_DsadcChannel_StreamingCircular */

/* Channel ID3(SingleDma): DSADC3 */
#ifndef DsadcConf_DsadcChannel_SingleDma
#define DsadcConf_DsadcChannel_SingleDma             ((Dsadc_ChannelType)3)
#endif /* DsadcConf_DsadcChannel_SingleDma */


/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#endif  /* DSADC_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

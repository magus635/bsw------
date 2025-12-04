/**
 * @file Adc_PBcfg.c
 * @brief Post-Build configuration for Adc module
 * 
 * @note Auto-generated file - DO NOT EDIT
 */

/*===========================================================================
 *                              INCLUDES
 *===========================================================================*/
#include "Adc_Cfg.h"

/*===========================================================================
 *                     CONFIGURATION STRUCTURES
 *===========================================================================*/


/* Configuration for AdcConfigSet */
const Adc_AdcConfigSet_ConfigType Adc_AdcConfigSet_Config = {

    .AdcHwUnitId = SARADC0,

    .AdcPrescale = 14,

    .AdcRequestSource0Prio = LOWEST,

    .AdcRequestSource1Prio = LOWEST,

    .AdcRequestSource2Prio = LOWEST,

    .AdcResolution = BITS_12,

    .AdcKernelChSampleTime = 2,

    .AdcRefVoltsrcHigh = REF_VOLTAGE_VAREF,

    .AdcRefVoltsrcLow = REF_VOLTAGE_GND,

    .AdcResultHandlingImplementation = INTERRUPT_MODE,

    .AdcSyncConvMode = ADC_STANDALONE,

};


/* Configuration for AdcGeneral */
const Adc_AdcGeneral_ConfigType Adc_AdcGeneral_Config = {

    .AdcDevErrorDetect = False,

    .AdcDeInitApi = True,

    .AdcEnableLimitCheck = False,

    .AdcEnableQueuing = False,

    .AdcEnableStartStopGroupApi = True,

    .AdcGrpNotifCapability = False,

    .AdcHwTriggerApi = False,

    .AdcLowPowerStatesSupport = False,

    .AdcPowerStateAsynchTransitionMode = False,

    .AdcStartupCalibration = False,

    .AdcReadGroupApi = True,

    .AdcSyncConvEnable = False,

    .AdcPriorityImplementation = ADC_PRIORITY_NONE,

    .AdcResultAlignment = ADC_ALIGN_RIGHT,

    .AdcVersionInfoApi = False,

};


/* Configuration for AdcPublishedInformation */
const Adc_AdcPublishedInformation_ConfigType Adc_AdcPublishedInformation_Config = {

    .AdcChannelValueSigned = False,

    .AdcGroupFirstChannelFixed = False,

    .AdcMaxChannelResolution = 12,

};


/* Configuration for CommonPublishedInformation */
const Adc_CommonPublishedInformation_ConfigType Adc_CommonPublishedInformation_Config = {

    .ArReleaseMajorVersion = 4,

    .ArReleaseMinorVersion = 2,

    .ArReleaseRevisionVersion = 2,

    .ModuleId = 123,

    .SwMajorVersion = 1,

    .SwMinorVersion = 0,

    .SwPatchVersion = 0,

    .VendorId = 175,

};



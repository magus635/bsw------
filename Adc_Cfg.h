/**
 * @file Adc_Cfg.h
 * @brief Configuration header for Adc module
 * 
 * @note Auto-generated file - DO NOT EDIT
 */

#ifndef ADC_CFG_H
#define ADC_CFG_H

/*===========================================================================
 *                              INCLUDES
 *===========================================================================*/
#include "Adc.h"

/*===========================================================================
 *                       CONFIGURATION PARAMETERS
 *===========================================================================*/


/* AdcConfigSet */

#define Adc_AdcConfigSet_AdcHwUnitId  SARADC0

#define Adc_AdcConfigSet_AdcPrescale  14

#define Adc_AdcConfigSet_AdcRequestSource0Prio  LOWEST

#define Adc_AdcConfigSet_AdcRequestSource1Prio  LOWEST

#define Adc_AdcConfigSet_AdcRequestSource2Prio  LOWEST

#define Adc_AdcConfigSet_AdcResolution  BITS_12

#define Adc_AdcConfigSet_AdcKernelChSampleTime  2

#define Adc_AdcConfigSet_AdcRefVoltsrcHigh  REF_VOLTAGE_VAREF

#define Adc_AdcConfigSet_AdcRefVoltsrcLow  REF_VOLTAGE_GND

#define Adc_AdcConfigSet_AdcResultHandlingImplementation  INTERRUPT_MODE

#define Adc_AdcConfigSet_AdcSyncConvMode  ADC_STANDALONE



/* AdcGeneral */

#define Adc_AdcGeneral_AdcDevErrorDetect  False

#define Adc_AdcGeneral_AdcDeInitApi  True

#define Adc_AdcGeneral_AdcEnableLimitCheck  False

#define Adc_AdcGeneral_AdcEnableQueuing  False

#define Adc_AdcGeneral_AdcEnableStartStopGroupApi  True

#define Adc_AdcGeneral_AdcGrpNotifCapability  False

#define Adc_AdcGeneral_AdcHwTriggerApi  False

#define Adc_AdcGeneral_AdcLowPowerStatesSupport  False

#define Adc_AdcGeneral_AdcPowerStateAsynchTransitionMode  False

#define Adc_AdcGeneral_AdcStartupCalibration  False

#define Adc_AdcGeneral_AdcReadGroupApi  True

#define Adc_AdcGeneral_AdcSyncConvEnable  False

#define Adc_AdcGeneral_AdcPriorityImplementation  ADC_PRIORITY_NONE

#define Adc_AdcGeneral_AdcResultAlignment  ADC_ALIGN_RIGHT

#define Adc_AdcGeneral_AdcVersionInfoApi  False



/* AdcPublishedInformation */

#define Adc_AdcPublishedInformation_AdcChannelValueSigned  False

#define Adc_AdcPublishedInformation_AdcGroupFirstChannelFixed  False

#define Adc_AdcPublishedInformation_AdcMaxChannelResolution  12



/* CommonPublishedInformation */

#define Adc_CommonPublishedInformation_ArReleaseMajorVersion  4

#define Adc_CommonPublishedInformation_ArReleaseMinorVersion  2

#define Adc_CommonPublishedInformation_ArReleaseRevisionVersion  2

#define Adc_CommonPublishedInformation_ModuleId  123

#define Adc_CommonPublishedInformation_SwMajorVersion  1

#define Adc_CommonPublishedInformation_SwMinorVersion  0

#define Adc_CommonPublishedInformation_SwPatchVersion  0

#define Adc_CommonPublishedInformation_VendorId  175




#endif /* ADC_CFG_H */

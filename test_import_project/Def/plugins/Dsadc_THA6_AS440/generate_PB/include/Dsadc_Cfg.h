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

[!NOCODE!][!//
[!INCLUDE "Dsadc_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
#ifndef DSADC_CFG_H_
#define DSADC_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!SELECT "as:modconf('Dsadc')[1]"!][!//

#define DSADC_CFG_AR_RELEASE_MAJOR_VERSION                   ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define DSADC_CFG_AR_RELEASE_MINOR_VERSION                   ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define DSADC_CFG_AR_RELEASE_REVISION_VERSION                ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define DSADC_CFG_SW_MAJOR_VERSION                           ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define DSADC_CFG_SW_MINOR_VERSION                           ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define DSADC_CFG_SW_PATCH_VERSION                           ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define DSADC_CFG_VENDOR_ID                                  ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define DSADC_CFG_MODULE_ID                                  ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)


/* Total configuration sets */
#define DSADC_CONFIGSET_CNT                                  (1U)

/*
Configuration: DsadcSafetyErrorDetect
- if Selected, Safety Error Check is Enabled 
- if Deselected, Safety Error Check is Disabled 
*/
#define DSADC_SAFETY_ENABLE                                  [!IF "DsadcGeneral/DsadcSafetyErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DsadcDevErrorDetect
- if Selected, DET is Enabled 
- if Deselected, DET is Disabled 
*/
#define DSADC_DEV_ERROR_DETECT                               [!IF "DsadcGeneral/DsadcDevErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DsadcDeInitApi
- if Selected, DeInit() API is Enabled 
- if Deselected, DeInit() API is Disabled 
*/
#define DSADC_CFG_DEINIT_API                                 [!IF "DsadcGeneral/DsadcDeInitApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DsadcDemEventParameterRefs
- if Selected, DEM is Enabled 
- if Deselected, DEM is Disabled 
*/
[!IF "not(node:exists(DsadcDemEventParameterRefs/DSADC_E_FIFO_FAILURE))"!][!//
#define DSADC_DEM_ERROR_REPORT_STATUS                        (STD_OFF)
[!ELSE!][!//
#define DSADC_DEM_ERROR_REPORT_STATUS                        (STD_ON)
/* DEM error code */
#define DSADC_E_FIFO_FAILURE                                 ((Dem_EventIdType)DemConf_DemEventParameter_[!"node:name(node:ref(DsadcDemEventParameterRefs/DSADC_E_FIFO_FAILURE))"!])
[!ENDIF!][!//

/*
Configuration: DsadcGetStreamLastPointerApi
- if Selected, Dsadc_GetStreamLastPointer() is Enabled 
- if Deselected, Dsadc_GetStreamLastPointer() is Disabled 
*/
#define DSADC_CFG_GETSTREAMLASTPOINTER_API                   [!IF "DsadcGeneral/DsadcGetStreamLastPointerApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DsadcVersionInfoApi
- if Selected, Dsadc_GetVersion() is Enabled 
- if Deselected, Dsadc_GetVersion() is Disabled 
*/
#define DSADC_CFG_VERSION_INFO_API                           [!IF "DsadcGeneral/DsadcVersionInfoApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DsadcNotifCapability
- if Selected, Notification is Enabled 
- if Deselected, Notification is Disabled 
*/
#define DSADC_CFG_NOTIF_CAPABILITY                           [!IF "DsadcGeneral/DsadcNotifCapability = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DsadcTimestampEnable
- if Selected, Notification is Enabled 
- if Deselected, Notification is Disabled 
*/
#define DSADC_CFG_TIMESTAMP_ENABLE                           [!IF "DsadcGeneral/DsadcTimestampEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DsadcTimestampEnable
- if Selected, Timestamp is Enabled 
- if Deselected, Timestamp is Disabled 
*/
#define DSADC_CFG_CLOCKSYNC_ENABLE                           [!IF "DsadcGeneral/DsadcClockSyncEnable = 'true'"!](DSADC_ENABLE)[!ELSE!](DSADC_DISABLE)[!ENDIF!]

/*
Configuration: DsadcIntegratorEnable
- if Selected, Integrator is Enabled 
- if Deselected, Integrator is Disabled 
*/
#define DSADC_CFG_INTEGRATOR_ENABLE                          [!IF "DsadcGeneral/DsadcIntegratorEnable = 'true'"!](DSADC_ENABLE)[!ELSE!](DSADC_DISABLE)[!ENDIF!]

/*
Configuration: DsadcAuxLimitCheckingEnable
- if Selected, Auxiliary conversion limit checking is Enabled 
- if Deselected, Auxiliary conversion limit checking is Disabled 
*/
[!IF "DsadcGeneral/DsadcAuxiliaryFilterChainEnable = 'true'"!][!//
#define DSADC_CFG_LIMIT_CHECKING_ENABLE                      [!IF "DsadcGeneral/DsadcAuxLimitCheckingEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
[!ELSE!][!//
#define DSADC_CFG_LIMIT_CHECKING_ENABLE                      (STD_OFF)
[!ENDIF!][!//

/*
Configuration: DsadcAuxiliaryFilterChainEnable
- if Selected, Auxiliary filter is Enabled 
- if Deselected, Auxiliary filter is Disabled 
*/
#define DSADC_CFG_AUX_FILTER_ENABLE                          [!IF "DsadcGeneral/DsadcAuxiliaryFilterChainEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

[!CALL "CG_GeneDsadcCarrierEnableStatus"!][!//
/*
Configuration: DsadcSetCarrierSyncParamApi
- if Selected, Dsadc_SetCarrierSyncValue() is Enabled 
- if Deselected, Dsadc_SetCarrierSyncValue() is Disabled 
*/
#define DSADC_CFG_SET_CARRIER_SYNC_PARAM_API                 [!IF "$Var_IsCarrierSyncParamApiEnabled = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DsadcGetCarrierDelayValueApi
- if Selected, Dsadc_GetCarrierDelayValue() is Enabled 
- if Deselected, Dsadc_GetCarrierDelayValue() is Disabled 
*/
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_CFG_GET_CARRIER_SYNC_DELAY_API                 [!IF "$Var_IsCarrierDelayApiEnabled = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DsadcInitSyncEnableHWUnit
*/
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_CFG_INIT_SYNC_ENABLE_HWUNIT                    [!IF "DsadcGeneral/DsadcInitSyncEnableHWUnit = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* Total HW units */
#define DSADC_TOTAL_HWUNIT                                   ([!"num:i(count(ecu:list('Dsadc.HwUnitList')))"!]U)
/* Total logical channels */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_TOTAL_CHANNEL                                  (DSADC_TOTAL_HWUNIT)
/* HW unit IDs */
[!INDENT "0"!][!//
[!FOR "Var_HwUnitID" = "num:i(0)" TO "num:i(count(ecu:list('Dsadc.HwUnitList')) - 1)"!][!//
#define DSADC_HWUNIT_DSADC[!"num:i($Var_HwUnitID)"!]                                  ([!"text:split(ecu:list('Dsadc.HwUnitList')[num:i($Var_HwUnitID + 1)], 'DSADC')[1]"!]U)
[!ENDFOR!][!//
[!ENDINDENT!][!//

/* Interrupt enabled flag */
[!INDENT "0"!][!//
[!LOOP "node:order(DsadcConfigSet/DsadcChannel/*, './DsadcHwUnitId')"!][!//
    [!IF "./DsadcResultHandlingImplementation = 'DSADC_INTERRUPT_MODE'"!][!//
/* [!"./DsadcHwUnitId"!] main filter chain interrupt enabled */
#define DSADC_HWUNIT_INT_EN_[!"./DsadcHwUnitId"!]                           (STD_ON)
        [!IF "./DsadcChAuxiliaryFilterChainEnable = 'true'"!][!//
/* [!"./DsadcHwUnitId"!] auxiliary filter chain interrupt enabled */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_HWUNIT_AUX_INT_EN_[!"./DsadcHwUnitId"!]                       (STD_ON)
        [!ELSE!][!//
/* [!"./DsadcHwUnitId"!] auxiliary filter chain interrupt disabled */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_HWUNIT_AUX_INT_EN_[!"./DsadcHwUnitId"!]                       (STD_OFF)
        [!ENDIF!][!//
    [!ELSE!][!//
/* [!"./DsadcHwUnitId"!] main filter chain interrupt disabled */
#define DSADC_HWUNIT_INT_EN_[!"./DsadcHwUnitId"!]                           (STD_OFF)
/* [!"./DsadcHwUnitId"!] auxiliary filter chain interrupt disabled */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_HWUNIT_AUX_INT_EN_[!"./DsadcHwUnitId"!]                       (STD_OFF)
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//

/* Macro for number of HW units(and channels) mapped to each core */
[!INDENT "0"!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "CoreUsedForDsadcChannelFlg" = "num:i(0)"!][!//
    [!IF "$Var_CoreIdx = num:i(0)"!][!//
        [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore0)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
        [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore1)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
        [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore2)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
        [!VAR "CoreUsedForDsadcChannelFlg" = "num:i($DsadcChannelMappedCore3)"!][!//
    [!ENDIF!][!//
/* The number of hardware units allocated to core[!"num:i($Var_CoreIdx)"!] */
#define DSADC_MAX_HWUNIT_TO_CORE[!"num:i($Var_CoreIdx)"!]                            ([!"num:i($CoreUsedForDsadcChannelFlg)"!]U)
/* The number of channels allocated to core[!"num:i($Var_CoreIdx)"!] */
#define DSADC_MAX_CHANNEL_TO_CORE[!"num:i($Var_CoreIdx)"!]                           (DSADC_MAX_HWUNIT_TO_CORE[!"num:i($Var_CoreIdx)"!])
[!ENDFOR!][!//
/* Total number of channels */
#define DSADC_CFG_TOTAL_CHANNELS                             ([!"num:i(count(DsadcConfigSet/DsadcChannel/*))"!]U)
[!ENDINDENT!][!//

/* Macro for channel result handling mode */
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_RESULT_HANDLING_INTERRUPT_MODE                 (0U)
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_RESULT_HANDLING_POLLING_MODE                   (1U)
/* #Violation: Dsadc_Cfg_h_REF_1 */
#define DSADC_RESULT_HANDLING_DMA_MODE                       (2U)

/* Macro for enable the DMA mode */
#define DSADC_CFG_DMA_MODE                                   [!IF "$Var_DMAModeFlag = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/* Macro for enable the interrupt mode */
#define DSADC_CFG_INTERRUPT_MODE                             [!IF "$Var_InterruptModeFlag = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/* Macro for enable the polling mode */
#define DSADC_CFG_POLLING_MODE                               [!IF "$Var_PollingModeFlag = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/****************************************************************************************************
**                          Macro definition of logical channel ID                                 **
****************************************************************************************************/
[!CALL "CG_GeneDsadcLogicalChannelID"!][!//

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
[!ENDSELECT!][!//
#endif  /* DSADC_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

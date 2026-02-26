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
*#Adc_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*/

#ifndef ADC_CFG_H_
#define ADC_CFG_H_

[!NOCODE!][!//
[!INCLUDE "Adc_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define ADC_CFG_AR_RELEASE_MAJOR_VERSION                   ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define ADC_CFG_AR_RELEASE_MINOR_VERSION                   ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define ADC_CFG_AR_RELEASE_REVISION_VERSION                ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define ADC_CFG_SW_MAJOR_VERSION                           ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define ADC_CFG_SW_MINOR_VERSION                           ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define ADC_CFG_SW_PATCH_VERSION                           ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)
#define ADC_CFG_VENDOR_ID                                  ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define ADC_CFG_MODULE_ID                                  ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

#define ADC_CONFIG_COUNT                                   (1U)
/*
Configuration: AdcSafetyDetect
- if Selected, Safety Error Check is Enabled 
- if Deselected, Safety Error Check is Disabled 
*/
#define ADC_SAFETY_ENABLE                                  [!IF "AdcGeneral/AdcSafetyErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

[!SELECT "as:modconf('Adc')[1]"!][!//
/* Maximum resolution possible */
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_MAX_CHANNEL_RESOLUTION                         ((uint8)[!"AdcPublishedInformation/AdcMaxChannelResolution"!])

/* ADC_CHANNEL_VALUESIGNED:  unsigned */
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_CHANNEL_VALUESIGNED                            [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcPublishedInformation/AdcChannelValueSigned"!][!//

/* 
  Information whether the first channel of an ADC Channel group can be
  configured (FALSE) or is fixed (TRUE) to a value determined by the ADC HW Unit 
*/
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_GROUP_FIRST_CHANNEL_FIXED                      [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcPublishedInformation/AdcGroupFirstChannelFixed"!][!//

/*
Configuration: AdcDevErrorDetect
- if STD_ON, DET is Enabled 
- if STD_OFF,DET is Disabled 
*/
#define ADC_DEV_ERROR_DETECT                               [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcDevErrorDetect"!][!//

/* 
Configuration: AdcVersionInfoApi
- if STD_ON, VersionInfo API is Enabled 
- if STD_OFF, VersionInfo API is Disabled 
*/
#define ADC_VERSION_INFO_API                               [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcVersionInfoApi"!][!//

/* 
Configuration: AdcLowPowerStatesSupport
- if STD_ON, Power State API is Enabled 
- if STD_OFF, Power State API is Disabled 
*/
#define ADC_POWER_STATE_SUPPORTED                          [!//
[!IF "node:exists(AdcGeneral/AdcLowPowerStatesSupport) = 'true'"!][!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcLowPowerStatesSupport"!][!//
[!ELSE!][!//
(STD_OFF)
[!ENDIF!][!//

/* 
Configuration: AdcGroupResultHandlingImplementation
- Conversion result handling method
*/
#define ADC_RESULT_HANDLING_INTERRUPT_MODE                 (0U)
#define ADC_RESULT_HANDLING_POLLING_MODE                   (1U) 
#define ADC_RESULT_HANDLING_DMA_MODE                       (2U)

[!CALL "Adc_HwUnitResultHandlingMethodEnStatus"!][!//
#define ADC_INTERRUPT_MODE_ENABLE                          ([!"$Var_InterruptModeEn"!])
#define ADC_POLLING_MODE_ENABLE                            ([!"$Var_PollingModeEn"!])
#define ADC_DMA_MODE_ENABLE                                ([!"$Var_DmaModeEn"!])

/* 
Configuration: AdcStartupCalibration
- if STD_ON, Adc_StartupCalibration is called in Adc_Init 
- if STD_OFF, Adc_StartupCalibration is not called in Adc_Init
*/
#define ADC_STARTUP_CALIBRATION                            [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcStartupCalibration"!][!//

/*
Configuration: AdcDeInitApi
- if STD_ON, DeInit API is Enabled 
- if STD_OFF, DeInit API is Disabled 
*/
#define ADC_DEINIT_API                                     [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcDeInitApi"!][!//

/* Configuration: AdcEnableStartStopGroupApi
Start/Stop Group conversion API configuration 
- if STD_ON, Start/Stop Group conversion API is Enabled 
- if STD_OFF, Start/Stop Group conversion API is Disabled 
*/
#define ADC_ENABLE_START_STOP_GROUP_API                    [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcEnableStartStopGroupApi"!][!//

/* 
Configuration: AdcHwTriggerApi
- if STD_ON, Adc HW Trigger API is Enabled 
- if STD_OFF, Adc HW Trigger API is Disabled 
*/
#define ADC_HW_TRIGGER_API                                 [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcHwTriggerApi"!][!//

/* 
Configuration: AdcReadGroupApi
- if STD_ON, Adc_ReadGroup API is Enabled 
- if STD_OFF, Adc_ReadGroup API is Disabled 
*/
#define ADC_READ_GROUP_API                                 [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcReadGroupApi"!][!//

/* 
Configuration: AdcGrpNotifCapability
- if STD_ON, Adc Notification capability is Enabled 
- if STD_OFF, Adc Notification capability is Disabled 
*/
#define ADC_GRP_NOTIF_CAPABILITY                           [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcGrpNotifCapability"!][!//

/* 
Configuration: AdcEnableLimitCheck
- if STD_ON, Limit checking is Enabled
- if STD_OFF, Limit checking is Disabled 
*/
#define ADC_ENABLE_LIMIT_CHECK                             [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcEnableLimitCheck"!][!//

/* 
Configuration: AdcSyncConvEnable
- if STD_ON, HW Sync group is Enabled
- if STD_OFF, HW Sync group is Disabled 
*/
#define ADC_HW_SYNC_CONV_GROUP_EN                          [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcSyncConvEnable"!][!//

/* 
Configuration: AdcResultAlignment
Determines the ADC result alignment
- ADC_ALIGN_LEFT: left alignment
- ADC_ALIGN_RIGHT: right alignment
*/
#define ADC_RESULT_ALIGNMENT                               ([!"AdcGeneral/AdcResultAlignment"!])

/* 
Configuration: AdcPriorityImplementation
Determines the type of prioritization mechanism
- ADC_PRIORITY_HW, Hardware priority mechanism is available only
- ADC_PRIORITY_HW_SW, Hardware and software priority mechanism is available
- ADC_PRIORITY_NONE, priority mechanism is not available
*/
#define ADC_PRIORITY_IMPLEMENTATION                        ([!"AdcGeneral/AdcPriorityImplementation"!])

/*
  SWS_Adc_00522.
  Options for the Priority Mechanism supported in ADC Driver
*/
/* Priority mechanism is not available */
#define ADC_PRIORITY_NONE                                  (0U)
/* Hardware priority mechanism is available only */
#define ADC_PRIORITY_HW                                    (1U)
/* Hardware and software priority mechanism is available */
#define ADC_PRIORITY_HW_SW                                 (2U) 

[!/* Since ADC_PRIORITY_HW_SW has no meaning in case of AdcEnableStartStopGroupApi disabled, throw error */!][!//
[!IF "AdcGeneral/AdcEnableStartStopGroupApi = 'false'"!][!//
[!ASSERT "(AdcGeneral/AdcPriorityImplementation != 'ADC_PRIORITY_HW_SW')"!][!//
Cfg ERROR: The priority can not be ADC_PRIORITY_HW_SW when 'AdcEnableStartStopGroupApi' is false.
[!ENDASSERT!][!//
[!ASSERT "(AdcGeneral/AdcEnableQueuing = 'false' or AdcGeneral/AdcPriorityImplementation != 'ADC_PRIORITY_NONE')"!][!//
Cfg ERROR: AdcEnableQueuing can not be set to true when 'AdcEnableStartStopGroupApi' is false.
[!ENDASSERT!][!//
[!ENDIF!][!//

/* 
Configuration: ADC_ENABLE_QUEUING
Determines, if the queuing mechanism is active in case of priority mechanism 
disabled.
Note: If priority mechanism is enabled, queuing mechanism is always active 
and the parameter ADC_ENABLE_QUEUING is not evaluated.
- if STD_ON, Queuing mechanism in no priority is Enabled 
- if STD_OFF, Queuing mechanism in no priority is Disabled 
*/
[!IF "(AdcGeneral/AdcEnableStartStopGroupApi = 'true') and (AdcGeneral/AdcPriorityImplementation = 'ADC_PRIORITY_NONE')"!][!//
#define ADC_ENABLE_QUEUING                                 [!//
[!CALL "CG_ConfigSwitch","nodeval" = "AdcGeneral/AdcEnableQueuing"!][!//
[!ELSE!][!// If Priority is other than PRIORITY_NONE
#define ADC_ENABLE_QUEUING                                 (STD_OFF)
[!ENDIF!][!//

/* Number of ADC Kernels in the selected microcontroller */
#define ADC_MAX_KERNELS                                    ([!"num:i(ecu:get('Adc.MaxControllers'))"!]U)

[!INDENT "0"!][!//
/* Configuration Options: ADC_HWUNIT_ID */
[!FOR "Var_HwUnitID" = "num:i(0)" TO "num:i(count(ecu:list('Adc.HwUnitId')) - 1)"!][!//
    [!FOR "AdcHwUnitIdx" = "num:i($Var_HwUnitID)" TO "num:i(ecu:get('Adc.MaxControllers') - 1)"!][!//
       [!IF "ecu:list('Adc.HwUnitId')[num:i($Var_HwUnitID + 1)] = concat('SARADC', num:i($AdcHwUnitIdx))"!][!//
#define ADC_HWUNIT_ADC[!"$AdcHwUnitIdx"!]                                    ([!"$AdcHwUnitIdx"!])
            [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//

/* Configuration: ADC_TOTAL_GROUPS_COREx(x=0~[!"num:i(ecu:get('Resource.NumOfCores'))"!]) 
It is the configured groups of all HW unit in each core.
*/
[!INDENT "0"!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!NOCODE!][!//
        [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i(0)"!][!//
        [!VAR "TotalGroups"= "num:i(0)"!][!//
        [!IF "$Var_CoreIdx = num:i(0)"!][!//
            [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore0)"!][!//
        [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
            [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore1)"!][!//
        [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
            [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore2)"!][!//
        [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
            [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore3)"!][!//
        [!ENDIF!][!//
        [!IF "num:i($CoreUsedForAdcHwUnitFlg) != num:i(0)"!][!//
            [!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'AdcHwUnitId')"!][!//
            [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
            [!IF "num:i($AdcHwUnitMappedCoreId) = $Var_CoreIdx"!][!//
                [!VAR "TotalGroups"= "$TotalGroups + num:i(count(./AdcGroup/*))"!][!//
            [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDNOCODE!][!//
/* Total configured groups number in Core[!"$Var_CoreIdx"!] */
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_TOTAL_GROUPS_CORE[!"$Var_CoreIdx"!]                             ([!"num:i($TotalGroups)"!]U)
[!ENDFOR!][!//
[!ENDINDENT!][!//

/* 
It is the configured groups in each ADC HW unit.
*/
[!INDENT "0"!][!//
[!VAR "AdcGroupsNum" = "num:i(0)"!][!//
[!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'AdcHwUnitId')"!][!//
    [!VAR "AdcHWUnitIndex" = "num:i(text:split(./AdcHwUnitId, 'SARADC')[1])"!][!//
    [!VAR "AdcGroupsNum" = "num:i(count(./AdcGroup/*))"!][!//
/* Configured groups for SARADC[!"$AdcHWUnitIndex"!] */
#define ADC_CFG_GROUPS_HWUNIT_ADC[!"$AdcHWUnitIndex"!]                         ([!"num:i($AdcGroupsNum)"!]U)
[!ENDLOOP!][!//
[!ENDINDENT!][!//
    
/* Macro indicating the total number of request sources used by the driver */
#define ADC_REQSRC_COUNT                                   ([!"num:i(ecu:get('Adc.ReqSrcCount'))"!]U)

[!INDENT "0"!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i(0)"!][!//
    [!IF "$Var_CoreIdx = num:i(0)"!][!//
        [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore0)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
        [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore1)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
        [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore2)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
        [!VAR "CoreUsedForAdcHwUnitFlg" = "num:i($AdcHwUnitMappedCore3)"!][!//
    [!ENDIF!][!//
    /* ADC HW unit mapped to Core[!"num:i($Var_CoreIdx)"!] */
    #define ADC_MAX_HWUNIT_TO_CORE[!"num:i($Var_CoreIdx)"!]                            ([!"num:i($CoreUsedForAdcHwUnitFlg)"!]U)
[!ENDFOR!][!//
[!ENDINDENT!][!//

/* Interrupt enabled flag */
[!INDENT "0"!][!//
[!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, './AdcHwUnitId')"!][!//
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_[!"./AdcHwUnitId"!]                           ([!IF "(./AdcResultHandlingImplementation = 'INTERRUPT_MODE') or (./AdcResultHandlingImplementation = 'DMA_MODE')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
    [!VAR "Var_RequestSrc0EnFlg" = "'false'"!][!//
    [!VAR "Var_RequestSrc1EnFlg" = "'false'"!][!//
    [!VAR "Var_RequestSrc2EnFlg" = "'false'"!][!//
    [!LOOP "./AdcGroup/*"!][!//
        [!IF "./AdcGroupRequestSource = 'REQUESTSOURCE_QUEUE0'"!][!//
            [!VAR "Var_RequestSrc0EnFlg" = "'true'"!][!//
        [!ELSEIF "./AdcGroupRequestSource = 'REQUESTSOURCE_QUEUE1'"!][!//
            [!VAR "Var_RequestSrc1EnFlg" = "'true'"!][!//
        [!ELSEIF "./AdcGroupRequestSource = 'REQUESTSOURCE_QUEUE2'"!][!//
            [!VAR "Var_RequestSrc2EnFlg" = "'true'"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_[!"./AdcHwUnitId"!]_RS0                       ([!IF "$Var_RequestSrc0EnFlg = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_[!"./AdcHwUnitId"!]_RS1                       ([!IF "$Var_RequestSrc1EnFlg = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/* #Violation: Adc_Cfg_h_REF_1 */
#define ADC_HWUNIT_INT_EN_[!"./AdcHwUnitId"!]_RS2                       ([!IF "$Var_RequestSrc2EnFlg = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

[!ENDLOOP!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/* CHANNEL SYMBOLIC NAME */
[!SELECT "AdcConfigSet"!][!//
    [!LOOP "node:order(./AdcHwUnit/*, 'AdcHwUnitId')"!][!//
        [!VAR "Var_HwUnitId" = "text:split(./AdcHwUnitId, 'SARADC')[1]"!][!//
        [!LOOP "node:order(./AdcChannel/*, './AdcChannelId')"!][!//
            [!VAR "EcuListName" = "concat('Adc.AdcChannels_Adc', $Var_HwUnitId)"!][!//
            [!/* Find the channel ID through the channel name */!][!//
            [!CALL "CG_FindHwUnitChannelID", "ChannelListName" = "$EcuListName", "ChannelName" = "./AdcAnChannelNum"!][!//
            [!VAR "ChannelNumber" = "$ChannelPosition"!][!//
/* Channel '[!"node:name(.)"!]', Pin is [!"./AdcAnChannelNum"!]: 
    [!WS "4"!]Logical channel ID: [!"./AdcChannelId"!] 
    [!WS "4"!]Hwunit ID: [!"$Var_HwUnitId"!]
    [!WS "4"!]Physical Channel ID: [!"$ChannelNumber"!] */
#ifndef AdcConf_AdcChannel_SignalName_[!"node:name(.)"!] /* to prevent double declaration */
/* #Violation: Adc_Cfg_h_REF_1 */
#define AdcConf_AdcChannel_SignalName_[!"node:name(.)"!]              ([!"num:inttohex(bit:or(bit:shl($Var_HwUnitId, 4) , num:i($ChannelNumber)), 2)"!]U)
#endif /* AdcConf_AdcChannel_SignalName_[!"node:name(.)"!] */

        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/* CHANNEL SYMBOLIC NAME */
[!SELECT "AdcConfigSet"!][!//
    [!LOOP "node:order(./AdcHwUnit/*, 'AdcHwUnitId')"!][!//
        [!VAR "AdcHwUnitName" = "node:name(.)"!][!//
        [!LOOP "node:order(./AdcChannel/*, './AdcChannelId')"!][!//
/* ADC Channel '[!"node:name(.)"!]' ID in [!"$AdcHwUnitName"!]: [!"AdcChannelId"!] */
#ifndef AdcConf_AdcChannel_[!"node:name(.)"!] /* to prevent double declaration */
#define AdcConf_AdcChannel_[!"node:name(.)"!]              ((Adc_ChannelType)[!"./AdcChannelId"!])
#endif /* AdcConf_AdcChannel_[!"node:name(.)"!] */

        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/* GROUP SYMBOLIC NAME */
[!SELECT "AdcConfigSet"!][!//
    [!LOOP "node:order(./AdcHwUnit/*, 'AdcHwUnitId')"!][!//
        [!VAR "AdcHwUnitName" = "node:name(.)"!][!//
        [!LOOP "node:order(./AdcGroup/*, './AdcGroupId')"!][!//
/* ADC Group '[!"node:name(.)"!]' ID in [!"$AdcHwUnitName"!]: [!"./AdcGroupId"!] */
#ifndef AdcConf_AdcGroup_[!"node:name(.)"!] /* to prevent double declaration */
#define AdcConf_AdcGroup_[!"node:name(.)"!]                ((Adc_GroupType)[!"./AdcGroupId"!])
#endif /* AdcConf_AdcGroup_[!"node:name(.)"!] */

         [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
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
[!ENDSELECT!][!//
#endif  /* ADC_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

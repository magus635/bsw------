[!NOCODE!][!//
/****************************************************************************************************
* 
****************************************************************************************************/
/****************************************************************************************************
*   FileName             : Adc_Cfg_Common.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Adc
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

[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!][!//
[!IF "not(var:defined('ADC_M'))"!][!//
[!VAR "ADC_M"="'true'"!][!//

[!/* Macro to get the internal channel ID of specified HW unit */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindHwUnitChannelID", "ChannelListName" = "", "ChannelName" = ""!][!//
    [!VAR "ChannelPosition" = "num:i(0)"!][!//
    [!LOOP "ecu:list($ChannelListName)"!][!//
        [!IF "$ChannelName != node:current()"!][!//
            [!VAR "ChannelPosition" = "num:i($ChannelPosition + 1)"!][!//
        [!ELSE!][!//
            [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to generate configuration switch Values ON/OFF based on configuration true/false */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_ConfigSwitch", "nodeval" = ""!][!//
    [!IF "$nodeval = 'true'"!][!//
        (STD_ON)
    [!ELSE!][!//
        (STD_OFF)
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to generates ticks for the GTM timer */!][!//
[!INDENT "0"!][!//
[!MACRO "Adc_ConfigGetGtmParams", "GtmChannelRef"= "", "GtmTimePeriod"="", "GtmTimerContainer"="",
"GtmClockRef"="", "GtmTimerTicks"="", "GtmTimerType"="", "GtmTimerModNo"="", "GtmTimerChNo"=""!][!//
    [!NOCODE!][!//
        [!VAR "GtmTimerType" = "substring-after(substring-before(text:split(($GtmChannelRef),'/')[6],'_'),'Gtm')"!]
        [!VAR "GtmTimerType" = "text:toupper($GtmTimerType)"!]
        [!VAR "GtmTimerModNo" = "text:split(($GtmChannelRef),'/')[6]"!]
        [!VAR "GtmTimerModNo" = "text:split($GtmTimerModNo,'_')[2]"!]
        [!VAR "GtmTimerChNo" = "text:split($GtmChannelRef,'Channel_')[2]"!]
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!MACRO "Adc_HwUnitResultHandlingMethodEnStatus"!][!//
[!VAR "Var_InterruptModeEn" = "'STD_OFF'"!][!//
[!VAR "Var_PollingModeEn" = "'STD_OFF'"!][!//
[!VAR "Var_DmaModeEn" = "'STD_OFF'"!][!//
[!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'AdcHwUnitId')"!][!//
    [!IF "./AdcResultHandlingImplementation = 'DMA_MODE'"!][!//
        [!VAR "Var_DmaModeEn" = "'STD_ON'"!][!//
    [!ELSEIF "./AdcResultHandlingImplementation = 'POLLING_MODE'"!][!//
        [!VAR "Var_PollingModeEn" = "'STD_ON'"!][!//
    [!ELSE!][!//
        [!VAR "Var_InterruptModeEn" = "'STD_ON'"!][!//
    [!ENDIF!][!//
    [!IF "$Var_DmaModeEn = 'STD_ON' and $Var_PollingModeEn = 'STD_ON' and $Var_InterruptModeEn = 'STD_ON'"!][!//
        [!BREAK!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to generates the value to be configured in BOUND register */!][!//
[!INDENT "0"!][!//
[!MACRO "Adc_GeneConfigBoundVal", "ChannelRangeSelect"= "", "ChannelHighLimit" ="", "ChannelLowLimit"= "", "ConvResolution" = ""!][!//
    [!NOCODE!][!//
    [!IF "$ConvResolution = '12'"!][!//
        [!VAR "AdcResolutionMaxVal" = "num:i(4095)"!][!//
    [!ELSEIF "$ConvResolution = '10'"!][!//
        [!VAR "AdcResolutionMaxVal" = "num:i(1023)"!][!//
    [!ELSEIF "$ConvResolution = '8'"!][!//
        [!VAR "AdcResolutionMaxVal" = "num:i(255)"!][!//
    [!ENDIF!][!//
    [!VAR "AdcBoundLowVal" = "num:i(0)"!][!//
    [!VAR "AdcBoundHighVal" = "num:i(0)"!][!//
    [!/* Generate the boundary values based on the High Limit, Low Limit and range selection criteria[/cover] */!][!//
    [!IF "$ChannelRangeSelect = 'ADC_RANGE_ALWAYS'"!][!//
        [!VAR "AdcBoundLowVal" = "num:i(0)"!][!//
        [!VAR "AdcBoundHighVal" = "num:i($AdcResolutionMaxVal)"!][!//
    [!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_BETWEEN'"!][!//
        [!VAR "AdcBoundLowVal" = "num:i($ChannelLowLimit + 1)"!][!//
        [!VAR "AdcBoundHighVal" = "num:i($ChannelHighLimit)"!][!//
    [!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_NOT_BETWEEN'"!][!//
        [!VAR "AdcBoundLowVal" = "num:i($ChannelLowLimit+1)"!][!//
        [!VAR "AdcBoundHighVal" = "num:i($ChannelHighLimit)"!][!//
    [!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_NOT_OVER_HIGH'"!][!//
        [!VAR "AdcBoundLowVal" = "num:i(0)"!][!//
        [!VAR "AdcBoundHighVal" = "num:i($ChannelHighLimit)"!][!//
    [!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_NOT_UNDER_LOW'"!][!//
            [!VAR "AdcBoundLowVal" = "num:i($ChannelLowLimit + 1)"!][!//
        [!VAR "AdcBoundHighVal" = "num:i($AdcResolutionMaxVal)"!][!//
    [!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_OVER_HIGH'"!][!//
        [!VAR "AdcBoundLowVal" = "num:i(0)"!][!//
        [!VAR "AdcBoundHighVal" = "num:i($ChannelHighLimit + 1)"!][!//
    [!ELSEIF "$ChannelRangeSelect = 'ADC_RANGE_UNDER_LOW'"!][!//
        [!VAR "AdcBoundLowVal" = "num:i($ChannelLowLimit+1)"!][!//
        [!VAR "AdcBoundHighVal" = "num:i($AdcResolutionMaxVal)"!][!//
    [!ENDIF!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to find the core to which the hardware unit is mapped */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName" = ""!][!//
    [!VAR "ModuleName" = "'ADC'"!][!//
    [!VAR "AdcHwUnitMappedCoreId" = "num:i(0)"!][!//
    [!VAR "AdcHwUnitMappedFlag" = "'false'"!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
    [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!VAR "Resource_CoreId" = "./ResourceCoreId"!][!//
        [!VAR "Resource_CoreEnable" = "./ResourceCoreEnable"!][!//
        [!IF "$Resource_CoreEnable = 'true'"!][!//
            [!LOOP "ResourceAllocation/*"!][!//
                [!IF "./ResourceModule = $ModuleName"!][!//
                    [!IF "node:refvalid(./ResourceModuleRef) = 'true'"!][!//
                        [!VAR "ModuleIndex" = "num:i(count(text:split(./ResourceModuleRef, '/')))"!][!//
                        [!VAR "Resource_ModuleName" = "text:split(./ResourceModuleRef, '/')[num:i($ModuleIndex)]"!][!//
                        [!IF "$AdcHwUnitName = $Resource_ModuleName"!][!//
                            [!VAR "AdcHwUnitMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "AdcHwUnitMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            ERROR: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$AdcHwUnitMappedFlag = 'false'"!][!//
        [!/* If not allocated the Adc HwUnit to any core then will default allocate it to core0 */!][!//
        [!VAR "AdcHwUnitMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to find which core used for Adc HW unit */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindTotalNumAdcHwUnitMappedToCorex"!][!//
    [!VAR "AdcHwUnitMappedCore0" = "num:i(0)"!][!//
    [!VAR "AdcHwUnitMappedCore1" = "num:i(0)"!][!//
    [!VAR "AdcHwUnitMappedCore2" = "num:i(0)"!][!//
    [!VAR "AdcHwUnitMappedCore3" = "num:i(0)"!][!//
    [!LOOP "node:order(AdcConfigSet/AdcHwUnit/*, 'AdcHwUnitId')"!][!//
        [!CALL "CG_FindAdcHwUnitMappedCoreId", "AdcHwUnitName"="node:name(.)"!][!//
        [!IF "num:i($AdcHwUnitMappedCoreId) = num:i(0)"!][!//
            [!VAR "AdcHwUnitMappedCore0" = "num:i($AdcHwUnitMappedCore0 + 1)"!][!//
        [!ELSEIF "num:i($AdcHwUnitMappedCoreId) = num:i(1)"!][!//
            [!VAR "AdcHwUnitMappedCore1" = "num:i($AdcHwUnitMappedCore1 + 1)"!][!//
        [!ELSEIF "num:i($AdcHwUnitMappedCoreId) = num:i(2)"!][!//
            [!VAR "AdcHwUnitMappedCore2" = "num:i($AdcHwUnitMappedCore2 + 1)"!][!//
        [!ELSEIF "num:i($AdcHwUnitMappedCoreId) = num:i(3)"!][!//
            [!VAR "AdcHwUnitMappedCore3" = "num:i($AdcHwUnitMappedCore3 + 1)"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "CG_FindTotalNumAdcHwUnitMappedToCorex"!][!//

[!ENDIF!][!// IF "not(var:defined('ADC_M'))
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

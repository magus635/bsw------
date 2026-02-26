[!NOCODE!][!//
/****************************************************************************************************
* 
****************************************************************************************************/
/****************************************************************************************************
*   FileName             : Dsadc_Cfg_Common.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : DSADC
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

[!IF "not(var:defined('DSADC_CFG_COMMON_M'))"!][!//
[!VAR "DSADC_CFG_COMMON_M" = "'true'"!][!//

[!/* Macro to find the core to which the DSADC channel is mapped */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindDsadcChannelMappedCoreId", "DsadcChannelName" = ""!][!//
    [!VAR "ModuleName" = "'DSADC'"!][!//
    [!VAR "DsadcChannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "DsadcChannelMappedFlag" = "'false'"!][!//
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
                        [!IF "$DsadcChannelName = $Resource_ModuleName"!][!//
                            [!VAR "DsadcChannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "DsadcChannelMappedFlag" = "'true'"!][!//
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
    [!IF "$DsadcChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the DSADC channel to any core then will default allocated to core0 */!][!//
        [!VAR "DsadcChannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to find which core used for DSADC HW unit */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindTotalNumDsadcChannelMappedToCorex"!][!//
    [!VAR "DsadcChannelMappedCore0" = "num:i(0)"!][!//
    [!VAR "DsadcChannelMappedCore1" = "num:i(0)"!][!//
    [!VAR "DsadcChannelMappedCore2" = "num:i(0)"!][!//
    [!VAR "DsadcChannelMappedCore3" = "num:i(0)"!][!//
    [!LOOP "node:order(DsadcConfigSet/DsadcChannel/*, 'DsadcChannelId')"!][!//
        [!CALL "CG_FindDsadcChannelMappedCoreId", "DsadcChannelName"="node:name(.)"!][!//
        [!IF "num:i($DsadcChannelMappedCoreId) = num:i(0)"!][!//
            [!VAR "DsadcChannelMappedCore0" = "num:i($DsadcChannelMappedCore0 + 1)"!][!//
        [!ELSEIF "num:i($DsadcChannelMappedCoreId) = num:i(1)"!][!//
            [!VAR "DsadcChannelMappedCore1" = "num:i($DsadcChannelMappedCore1 + 1)"!][!//
        [!ELSEIF "num:i($DsadcChannelMappedCoreId) = num:i(2)"!][!//
            [!VAR "DsadcChannelMappedCore2" = "num:i($DsadcChannelMappedCore2 + 1)"!][!//
        [!ELSEIF "num:i($DsadcChannelMappedCoreId) = num:i(3)"!][!//
            [!VAR "DsadcChannelMappedCore3" = "num:i($DsadcChannelMappedCore3 + 1)"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "CG_FindTotalNumDsadcChannelMappedToCorex"!][!//

[!/* Macro to judge the result handling mode and access mode */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDsadcRsltHdlAndAccessMode"!][!//
    [!VAR "Var_DMAModeFlag" = "'false'"!][!//
    [!VAR "Var_InterruptModeFlag" = "'false'"!][!//
    [!VAR "Var_PollingModeFlag" = "'false'"!][!//
    [!LOOP "node:order(DsadcConfigSet/DsadcChannel/*, 'DsadcChannelId')"!][!//
        [!IF "./DsadcResultHandlingImplementation = 'DSADC_INTERRUPT_MODE'"!][!//
            [!VAR "Var_InterruptModeFlag" = "'true'"!][!//
        [!ELSEIF "./DsadcResultHandlingImplementation = 'DSADC_POLLING_MODE'"!][!//
            [!VAR "Var_PollingModeFlag" = "'true'"!][!//
        [!ELSE!][!//
            [!VAR "Var_DMAModeFlag" = "'true'"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "CG_GeneDsadcRsltHdlAndAccessMode"!][!//

[!/* Macro to judge whether the carrier is enabled */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDsadcCarrierEnableStatus"!][!//
    [!VAR "Var_IsCarrierEnabled" = "'false'"!][!//
    [!VAR "Var_IsCarrierDelayApiEnabled" = "'false'"!][!//
    [!VAR "Var_IsCarrierSyncParamApiEnabled" = "'false'"!][!//
    [!SELECT "as:modconf('Dsadc')[1]/DsadcConfigSet/DsadcCarrierGenerator/*[1]"!][!//
        [!IF "./DsadcCarrierSignalMode != 'DSADC_CARRIER_STOPPED'"!][!//
            [!VAR "Var_IsCarrierEnabled" = "'true'"!][!//
            [!IF "./DsadcSetCarrierSyncParamApi = 'true'"!][!//
                [!VAR "Var_IsCarrierSyncParamApiEnabled" = "'true'"!][!//
            [!ENDIF!][!//
            [!IF "./DsadcGetCarrierDelayValueApi = 'true'"!][!//
                [!VAR "Var_IsCarrierDelayApiEnabled" = "'true'"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to judge whether the auxiliary filter chain is enabled */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDsadcAuxFltrEnableBits"!][!//
    [!VAR "Var_AuxFltrEnBits" = "num:i(0)"!][!//
    [!LOOP "as:modconf('Dsadc')[1]/DsadcConfigSet/DsadcChannel/*"!][!//
        [!VAR "Var_HWUnitNumber" = "text:split(./DsadcHwUnitId, 'DSADC')[1]"!][!//
        [!IF "node:exists(DsadcChAuxiliaryFilterChainEnable) and (./DsadcChAuxiliaryFilterChainEnable = 'true')"!][!//
            [!IF "num:i($Var_HWUnitNumber) >= num:i(8)"!][!//
                [!VAR "Var_AuxFltrEnBits" = "bit:or($Var_AuxFltrEnBits, bit:shl(1, num:i($Var_HWUnitNumber + 10)))"!][!//
            [!ELSE!][!//
                [!VAR "Var_AuxFltrEnBits" = "bit:or($Var_AuxFltrEnBits, bit:shl(1, $Var_HWUnitNumber + 8))"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to judge whether the common voltage is enabled */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDsadcCommonVoltEnableStatus"!][!//
    [!VAR "Var_CommonVoltEnables" = "'false'"!][!//
    [!LOOP "as:modconf('Dsadc')[1]/DsadcConfigSet/DsadcChannel/*"!][!//
        [!IF "(./DsadcModulatorConfig/*[1]/DsadcNegativeInputLine = 'DSADC_NEG_INPUT_COMM_MODE_VOLT') or 
              (./DsadcModulatorConfig/*[1]/DsadcPositiveInputLine = 'DSADC_POS_INPUT_COMM_MODE_VOLT')"!][!//
              [!VAR "Var_CommonVoltEnables" = "'true'"!][!//
              [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the logical channel ID */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDsadcLogicalChannelID"!][!//
    [!LOOP "node:order(as:modconf('Dsadc')[1]/DsadcConfigSet/DsadcChannel/*, './DsadcChannelId')"!][!//
/* Channel ID[!"./DsadcChannelId"!]([!"node:name(.)"!]): [!"./DsadcHwUnitId"!] */
#ifndef DsadcConf_DsadcChannel_[!"node:name(.)"!]
#define DsadcConf_DsadcChannel_[!"node:name(.)"!]             ((Dsadc_ChannelType)[!"./DsadcChannelId"!])
#endif /* DsadcConf_DsadcChannel_[!"node:name(.)"!] */

    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!MACRO "CG_GeneDsadc1InputPin"!][!//
    [!VAR "Var_Dsadc1InputPin" = "num:i(255)"!][!//
    [!IF "text:contains(node:value(as:modconf('Resource')[1]/ResourceGeneral/ResourceSubderivative), 'THA6412')"!][!//
        [!LOOP "node:order(DsadcConfigSet/DsadcChannel/*, './DsadcHwUnitId')"!][!//
            [!IF "./DsadcHwUnitId = 'DSADC1'"!][!//
                [!IF "./DsadcModulatorConfig/*[1]/DsadcInputMuxInitPin = 'DSADC_INPUT_PIN_A'"!][!//
                    [!VAR "Var_Dsadc1InputPin" = "num:i(0)"!][!//
                [!ELSEIF "./DsadcModulatorConfig/*[1]/DsadcInputMuxInitPin = 'DSADC_INPUT_PIN_B'"!][!//
                    [!VAR "Var_Dsadc1InputPin" = "num:i(1)"!][!//
                [!ELSEIF "./DsadcModulatorConfig/*[1]/DsadcInputMuxInitPin = 'DSADC_INPUT_PIN_C'"!][!//
                    [!VAR "Var_Dsadc1InputPin" = "num:i(2)"!][!//
                [!ELSE!][!//
                    [!VAR "Var_Dsadc1InputPin" = "num:i(3)"!][!//
                [!ENDIF!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!ENDIF!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

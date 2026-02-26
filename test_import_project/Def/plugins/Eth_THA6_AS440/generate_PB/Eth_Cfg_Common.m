[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Eth_Cfg_Common.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : ASI
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*   Build Version        : Cortex-R52+/THA6xxx
*
*    Copyright (c) 2021, Beijing Tongfang Microelectroics Co., Ltd.
*
*   History:
*   2021-12-31 by Hx
*     1. Original version 0.1
*
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('ETH_CFG_COMMON_M'))"!]
[!VAR "ETH_CFG_COMMON_M"="'true'"!]

[!INDENT "0"!][!//
[!/* To find the CoreId according to the Eth channel */!][!//
[!MACRO "CG_FindEthChannelMappedCoreId", "EthChId" = ""!][!//
    [!VAR "ModuleName" = "'ETH'"!][!//
    [!VAR "EthchannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "EthChannelMappedFlag" = "'false'"!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
    [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!VAR "Resource_CoreId" = "./ResourceCoreId"!][!//
        [!VAR "Resource_CoreEnable" = "./ResourceCoreEnable"!][!//
        [!IF "$Resource_CoreEnable = 'true'"!][!//
            [!LOOP "ResourceAllocation/*"!][!//
                [!IF "./ResourceModule = $ModuleName"!][!//
                    [!IF "node:refvalid(./ResourceModuleRef) = 'true'"!][!//
                        [!VAR "index" = "num:i(count(text:split(./ResourceModuleRef, '/')))"!][!//
                        [!VAR "Resource_ModuleName" = "text:split(./ResourceModuleRef, '/')[num:i($index)]"!][!//
                        [!IF "$EthChId = $Resource_ModuleName"!][!//
                            [!VAR "EthchannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "EthChannelMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                             Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$EthChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the Eth channel to any core will default allocate to core0 */!][!//
        [!VAR "EthchannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//


[!/* Find which core used for Eth channel */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindTotalNumEthChannelMappedToCorex"!][!//
    [!VAR "EthChannelMappedCore0" = "0"!][!//
    [!VAR "EthChannelMappedCore1" = "0"!][!//
    [!VAR "EthChannelMappedCore2" = "0"!][!//
    [!VAR "EthChannelMappedCore3" = "0"!][!//
    [!VAR "EthChannelMappedCore4" = "0"!][!//
    [!LOOP "EthConfigSet/EthCtrlConfig/*"!][!//
        [!CALL "CG_FindEthChannelMappedCoreId", "EthChId"="node:name(.)"!][!//
        [!IF "$EthchannelMappedCoreId = num:i(0)"!][!//
            [!VAR "EthChannelMappedCore0" = "$EthChannelMappedCore0 + 1"!][!//
        [!ELSEIF "$EthchannelMappedCoreId = num:i(1)"!][!//
            [!VAR "EthChannelMappedCore1" = "$EthChannelMappedCore1 + 1"!][!//
        [!ELSEIF "$EthchannelMappedCoreId = num:i(2)"!][!//
            [!VAR "EthChannelMappedCore2" = "$EthChannelMappedCore2 + 1"!][!//
        [!ELSEIF "$EthchannelMappedCoreId = num:i(3)"!][!//
            [!VAR "EthChannelMappedCore3" = "$EthChannelMappedCore3 + 1"!][!//
        [!ELSEIF "$EthchannelMappedCoreId = num:i(4)"!][!//
            [!VAR "EthChannelMappedCore4" = "$EthChannelMappedCore4 + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "CG_FindTotalNumEthChannelMappedToCorex"!]

[!ENDIF!][!// avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//

[!MACRO "EthDemProcess"!][!//
[!NOCODE!]
  [!VAR "TotalConfig" = "num:i(count(EthConfigSet/*))"!][!//
  [!VAR "EthDemEnabled" = "num:i(0)"!][!//
  [!FOR "ConfigId" = "num:i(1)" TO "num:i($TotalConfig)"!][!//
    [!SELECT "EthConfigSet/*[num:i($ConfigId)]"!][!//
      [!FOR "ControllerId" = "num:i(0)" TO "num:i(0)"!][!//
        [!IF "node:exists(EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]) = 'true'"!]
          [!SELECT "EthCtrlConfig/*[EthCtrlIdx = num:i($ControllerId)]"!][!//
            [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ACCESS/*[1]) != '' )"!][!//
              [!VAR "EthDemEnabled" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_RX_FRAMES_LOST/*[1]) != '' )"!][!//
              [!VAR "EthDemEnabled" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_CRC/*[1]) != '' )"!][!//
              [!VAR "EthDemEnabled" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_UNDERSIZEFRAME/*[1]) != '' )"!][!//
              [!VAR "EthDemEnabled" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_OVERSIZEFRAME/*[1]) != '' )"!][!//
              [!VAR "EthDemEnabled" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_ALIGNMENT/*[1]) != '' )"!][!//
              [!VAR "EthDemEnabled" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_SINGLECOLLISION/*[1]) != '' )"!][!//
              [!VAR "EthDemEnabled" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_MULTIPLECOLLISION/*[1]) != '' )"!][!//
              [!VAR "EthDemEnabled" = "num:i(1)"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) = 'true') and (node:value(./EthDemEventParameterRefs/*[1]/ETH_E_LATECOLLISION/*[1]) != '' )"!][!//
              [!VAR "EthDemEnabled" = "num:i(1)"!][!//
            [!ENDIF!][!//
          [!ENDSELECT!][!//
        [!ENDIF!][!//
      [!ENDFOR!][!//
    [!ENDSELECT!][!//
  [!ENDFOR!][!//
[!ENDNOCODE!]
[!ENDMACRO!][!//




[!/*
/*******************************************************************************
**                                                                            **
** Copyright (C) TMC Technologies (2019)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to TMC       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Sent.m                                                        **
**                                                                            **
**  VERSION   : 3.0.0                                                         **
**                                                                            **
**  DATE      : 2019-05-31                                                    **
**                                                                            **
**  BSW MODULE DESCRIPTION : NA                                               **
**                                                                            **
**  VARIANT   : Variant PB                                                    **
**                                                                            **
**  PLATFORM  : TMC THA6X                                              **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : TMC Technologies                                         **
**                                                                            **
**  DESCRIPTION  : Code template macro file for Sent Driver                   **
**                                                                            **
**  SPECIFICATION(S) : NA                                                     **
**                                                                            **
**  MAY BE CHANGED BY USER : no                                               **
**                                                                            **
*******************************************************************************/
********************************************************************************
**                       Includes                                             **
*****************************************************************************/!]
[!//
/******************************************************************************/
[!/* *** multiple inclusion protection*** */!][!//
[!IF "not(var:defined('Sent_M'))"!][!//
[!VAR "Sent_M"="'true'"!][!//
[!AUTOSPACING!][!//
/*******************************************************************************
** Name             : CG_ConfigSwitch                                         **
**                                                                            **
** Description      : Macro to generate configuration switch Values ON/OFF    **
**                    based on configuration true/false                       **
**                                                                            **
*******************************************************************************/
[!MACRO "CG_ConfigSwitch", "MacInputVal" = ""!][!//
  [!IF "$MacInputVal = 'true'"!][!//
    (STD_ON)[!//
  [!ELSE!][!//
    (STD_OFF)[!//
  [!ENDIF!]
[!ENDMACRO!]

/*******************************************************************************
** Name             : Sent_GenerateModuleMap                                    **
**                                                                            **
** Description      : Macro to generate core-channel mappings for a module    **
**                                                                            **
*******************************************************************************/
/* Macro to generate module map. consist of core to channel mapping */
[!MACRO "Sent_GenerateModuleMap", "Module" = ""!][!//
[!NOCODE!][!//
    [!VAR "CGCoreUsed" = "''"!][!//
    [!VAR "CGAllocatedCores" = "''"!][!//
    [!VAR "CGAllocatedChannelMap" = "''"!][!//
    [!VAR "CGCoreMap" = "''"!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
      [!VAR "CGMasterCoreId_Extract" = "substring(node:value(ResourceCoreConfigSet/ResourceMasterCore),5,1)"!][!//
      [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!VAR "CGCoreID" = "./ResourceCoreId"!][!//
        [!LOOP "ResourceAllocation/*"!][!//
          [!IF "$Module = ./ResourceModule"!][!//
            [!IF "node:refvalid(./ResourceModuleRef)"!]
              [!VAR "index" = "num:i(count(text:split(./ResourceModuleRef, '/')))"!][!//
              [!VAR "ResourceName" = "text:split(./ResourceModuleRef, '/')[num:i($index)]"!][!//
              [!VAR "CGCoreMap" = "text:toupper(concat($CGCoreMap, $CGCoreID, '_', $ResourceName, ','))"!][!//
              [!VAR "CGAllocatedChannelMap" = "text:toupper(concat($CGAllocatedChannelMap, $ResourceName, ','))"!][!//
              [!IF "not(contains(text:split($CGCoreUsed), $CGCoreID))"!]
                [!VAR "CGCoreUsed" = "concat($CGCoreUsed, $CGCoreID, ',')"!][!//
                [!VAR "CGAllocatedCores" = "concat($CGAllocatedCores,$CGCoreID,',')"!][!//
              [!ENDIF!][!//
            [!ELSE!][!//
              [!WARNING!][!//
                Warning: The resource [!"node:value(./ResourceModuleRef)"!] does not exists.
              [!ENDWARNING!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
      [!ENDLOOP!][!//
    [!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
/*******************************************************************************
** Name             : Sent_ValidateChAllocation                                **
**                                                                            **
** Description      : Macro to validate if a channel is allocated to the core **
**                                                                            **
** Pre-requisite    : Sent_GenerateModuleMap macro should be called before     **
**                    calling this macro                                      **
*******************************************************************************/
[!MACRO "Sent_ValidateChAllocation", "CoreNumber" = "", "Channel" = ""!][!//
[!NOCODE!][!//
    [!VAR "CGAllocationResult" = "'FALSE'"!][!//
    [!VAR "ChanAllocation" = "num:i(1)"!]
    [!VAR "CGChannelPattern" = "text:toupper(concat('CORE', num:i($CoreNumber), '_', $Channel))"!][!//
      [!IF "text:contains( text:split($CGCoreMap,','), $CGChannelPattern )"!][!//
        [!VAR "CGAllocationResult" = "'TRUE'"!][!//
      [!ELSEIF "not(text:contains( text:split($CGAllocatedChannelMap,','), text:toupper($Channel)))"!][!//
        [!IF "num:i($CGMasterCoreId_Extract) = (num:i($CoreNumber))"!][!//
          [!VAR "CGAllocationResult" = "'TRUE'"!][!//
          [!VAR "ChanAllocation" = "num:i(0)"!][!//
        [!ENDIF!][!//
        [!ENDIF!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//

/*******************************************************************************
** Name             : Sent_PrintMasterCoreID                                     **
**                                                                            **
** Description      : Macro to get master core ID                             **
**                                                                            **
** Pre-requisite    : NA                                                      **
*******************************************************************************/
/* Macro to get master core ID */
[!MACRO "Sent_PrintMasterCoreID"!][!//
  [!NOCODE!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
      [!CODE!][!//
        [!INDENT "0"!][!//
            /* #Violation: Sent_Cfg_h_REF_1 */
            #define MASTER_CORE_ID           [!"$CGMasterCoreId_Extract"!]U
        [!ENDINDENT!][!//
      [!ENDCODE!][!//
    [!ENDSELECT!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!][!//
/*******************************************************************************
** Name             : Sent_CG_GetCore                                          **
**                                                                            **
** Description      : Macro to get the core to which the channel is assigned  **
**                                                                            **
** Pre-requisite    : CG_GenerateModuleMap macro should be called before      **
**                    calling this macro                                      **
*******************************************************************************/
[!MACRO "Sent_CG_GetCore", "channel" = ""!][!//
  [!NOCODE!]
    [!IF "(text:contains( text:split($CGAllocatedChannelMap,','), text:toupper($Channel)))"!]
      [!VAR "CGCoreIndexPos" = "num:i(text:indexOf(text:split($CGCoreMap), concat(text:toupper($Channel),',')) - 2)"!]
      [!VAR "CGCoreId_Extract" = "num:i(substring( $CGCoreMap, $CGCoreIndexPos, num:i(1)))"!]
    [!ELSE!]
      [!VAR "CGCoreId_Extract" = "num:i($CGMasterCoreId_Extract)"!]
    [!ENDIF!]
  [!ENDNOCODE!]
[!ENDMACRO!]]
/*******************************************************************************
** Name             : CG_ALTI_Value                                           **
**                                                                            **
** Description      : Macro to retrieve the value in OutMac_ALTI variable     **
**                    based on the MacInputVal value                          **
**                                                                            **
*******************************************************************************/
[!MACRO "CG_ALTI_Value", "MacInputVal" = ""!][!//
  [!NOCODE!]
  [!//
    [!IF "$MacInputVal = 'SENT_ALT_INPUT0'"!][!//
      [!VAR "OutMac_ALTI" = "num:i(0)"!]
    [!ELSEIF "$MacInputVal = 'SENT_ALT_INPUT1'"!][!//
      [!VAR "OutMac_ALTI" = "num:i(1)"!]
    [!ELSEIF "$MacInputVal = 'SENT_ALT_INPUT2'"!][!//
      [!VAR "OutMac_ALTI" = "num:i(2)"!]
    [!ELSEIF "$MacInputVal = 'SENT_ALT_INPUT3'"!][!//
      [!VAR "OutMac_ALTI" = "num:i(3)"!]
    [!ELSE!][!//
      [!ERROR"Config Error: Wrong Channel Pin Select."!]
    [!ENDIF!]
  [!ENDNOCODE!]
[!ENDMACRO!]
/*******************************************************************************
** Name             : Sent_GetMasterCoreID                                     **
**                                                                            **
** Description      : Macro to get master core ID                             **
**                                                                            **
** Pre-requisite    : NA                                                      **
*******************************************************************************/
/*Macro to get master core ID*/
[!MACRO "Sent_GetMasterCoreID"!][!//
[!NOCODE!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
      [!VAR "CGMasterCoreId" = "node:value(ResourceCoreConfigSet/ResourceMasterCore)"!][!//
    [!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!]
[!/*****************************************************************************
MACRO: Sent_CGCalculateTotalChannelPerCore
Macro to calculate and generate code for count of total number of channels per core.
******************************************************************************/!]
[!MACRO "Sent_CGCalculateTotalChannelPerCore"!][!//
  [!NOCODE!]
    [!SELECT "as:modconf('Resource')[1]"!][!//
      [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!VAR "TotalChannelPerCore"="num:i(0)"!][!//
        [!VAR "CGCoreID" = "./ResourceCoreId"!][!//
        [!LOOP "ResourceAllocation/*"!][!//
          [!IF "$Module = ./ResourceModule"!][!//
            [!IF "node:refvalid(./ResourceModuleRef) = 'true'"!][!//
              [!VAR "TotalChannelPerCore"="$TotalChannelPerCore + num:i(1)"!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!VAR "index1" = "(substring-after($CGCoreID, 'E'))"!]
        [!IF "num:i($CGMasterCoreId_Extract) !=(num:i($index1))"!]
          [!CODE!]
            [!INDENT "0"!][!//
               /* #Violation: Sent_Cfg_h_REF_1 */
               #define SENT_CHANNEL_COUNT_[!"($CGCoreID)"!]           [!"num:i($TotalChannelPerCore)"!]U
            [!ENDINDENT!][!//
          [!ENDCODE!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDSELECT!][!//
  [!ENDNOCODE!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
MACRO: Sent_CGCalculateChannelMasterCore
Macro to calculate and generate code for count of total number of channels of master core.
******************************************************************************/!]
[!MACRO "Sent_CGCalculateChannelMasterCore"!][!//
[!NOCODE!]
    [!SELECT "as:modconf('Sent')[1]"!][!//
      [!VAR "TotalConfig" = "num:i(count(SentConfigSet/*))"!][!//
      [!FOR "SentId" ="num:i(1)" TO "(num:i($TotalConfig))"!][!//
        [!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//
          [!FOR "CoreId" = "num:i(0)" TO "num:i(ecu:get('Mcu.NoOfCoreAvailable')) - num:i(1)"!][!//
            [!VAR "TempCoreId" = "concat('CORE',$CoreId)"!][!//
            [!CALL "Sent_GetMasterCoreID"!][!//
            [!IF "(text:contains( text:split($CGAllocatedCores,','), $TempCoreId)) or ($CGMasterCoreId = $TempCoreId)"!][!//
              [!CALL "Sent_GenerateModuleMap", "Module" = "'SENT'"!][!//
              [!VAR "MasterChannelsCore" = "num:i(0)"!][!//
              [!VAR "TotalChannels" = "num:i(0)"!][!//
              [!VAR "TotalChannels" = "num:i(count(SentChannelConfigSet/*))"!][!//
              [!FOR "Channel" = "num:i(0)" TO "num:i($TotalChannels)"!][!//
                [!SELECT "node:SentChannelConfigSet/*[num:i($Channel)]"!][!//
                  [!VAR "NodeName" = "node:name(.)"!][!//
                  [!CALL "Sent_ValidateChAllocation", "CoreNumber" = "$CoreId", "Channel" = "$NodeName"!][!//
                  [!IF "$CGAllocationResult = 'TRUE'"!][!//
                    [!VAR "MasterChannelsCore" = "$MasterChannelsCore + num:i(1)"!][!//
                  [!ENDIF!][!//
                [!ENDSELECT!][!//
              [!ENDFOR!][!//
              [!CODE!][!//
                [!IF "num:i($CGMasterCoreId_Extract) = (num:i($CoreId))"!]
                  /* #Violation: Sent_Cfg_h_REF_1 */
                  #define SENT_CHANNEL_COUNT_CORE[!"($CoreId)"!]       [!"num:i($MasterChannelsCore)"!]U
                  /* #Violation: Sent_Cfg_h_REF_1 */
                  #define SENT_MAX_CHANNELS_MASTER_CORE     [!"num:i($MasterChannelsCore)"!]U
                [!ENDIF!][!//
              [!ENDCODE!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDSELECT!][!//
      [!ENDFOR!][!//
    [!ENDSELECT!][!//
[!ENDNOCODE!]
[!ENDMACRO!]
[!/*****************************************************************************
MACRO: Sent_CGChanPhysicalID
Macro to calculate the physical ID of the channels.
******************************************************************************/!]
[!MACRO "Sent_CGChanPhysicalID"!][!//
  [!SELECT "as:modconf('Sent')[1]"!][!//
    [!SELECT "SentConfigSet/*[num:i($SentId)]"!][!//
      [!VAR "Sent_ChannelPhysicalIndex" = "0"!][!//
      [!FOR "Sent_ChCounterIndex1" = "0" TO "$TotalChannels - 1"!][!//
        [!VAR "Sent_ChannelPhysicalIndex" = "concat($Sent_ChannelPhysicalIndex,',',$Sent_ChCounterIndex1)"!]
      [!ENDFOR!][!//
    [!ENDSELECT!][!//
  [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
MACRO: Sent_CGChannelConfig
Macro to fetch channel according to the core.
******************************************************************************/!]
[!MACRO "Sent_CGChannelConfig"!][!//
  [!SELECT "as:modconf('ResourceM')[1]"!][!//
    [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
      [!LOOP "ResourceMAllocation/*"!][!//
        [!IF "node:refvalid(./ResourceMResourceRef)"!][!//
          [!VAR "index" = "num:i(count(text:split(./ResourceMResourceRef, '/')))"!][!//
          [!VAR "ResourceName" = "text:split(./ResourceMResourceRef, '/')[num:i($index)]"!][!//
          [!VAR "channel"="substring-after($ResourceName, '_')"!]
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!/*****************************************************************************
MACRO: Sent_CGConfigId
Macro to fetch channel index according to the core.
******************************************************************************/!]
[!MACRO "Sent_CGConfigId","CoreNumber" = ""!][!//
  [!SELECT "as:modconf('ResourceM')[1]"!][!//
    [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
      [!LOOP "ResourceMAllocation/*"!][!//
        [!IF "node:refvalid(./ResourceMResourceRef)"!][!//
          [!VAR "refchannelid" = "(node:name((./ResourceMResourceRef)))"!][!//
          printf[!"$refchannelid"!]
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDLOOP!][!//
  [!ENDSELECT!][!//
[!ENDMACRO!][!//

[!/*****************************************************************************
MACRO: Sent_resource
Macro to fetch channels according to the core.
******************************************************************************/!]
[!MACRO "Sent_resource","CoreNumber" = ""!][!//
  [!SELECT "as:modconf('Resource')[1]"!][!//
    [!VAR "CGMasterCoreId_Extract" = "substring(node:value(ResourceCoreConfigSet/ResourceMasterCore),5,1)"!][!//
    [!IF "node:value(ResourceMMcalConfig/*[1]/ResourceMSingleCore) = 'false'"!]
      [!LOOP "ResourceMMcalConfig/*[1]/ResourceMMcalCore/*"!][!//
        [!VAR "CGCoreID" = "./ResourceMCoreID"!][!//
        [!LOOP "ResourceMAllocation/*"!][!//
          [!VAR "CGAllocatedResources" = "concat($CGAllocatedResources, $ResourceName, '#,')"!][!//
          [!IF "contains($CGAllocatedResources, $ex)"!][!//[!//
            [!VAR "Result" = "'TRUE'"!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
      [!ENDLOOP!] [!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDIF!][!// IF "not(var:defined('Sent_M'))

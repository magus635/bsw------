[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Gpt.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : GTM-TOM, BASETIMER
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('GPT_M'))"!]
[!VAR "GPT_M"="'true'"!]

[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Resource')[1]))"!][!//
[!ERROR!][!//
  100-00-01-ERROR: Resource module is not added to the project.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

[!NOCODE!][!//
[!SELECT "as:modconf('Resource')[1]"!][!//
[!/* Find the master core */!][!//
[!VAR "Resource_MasterCore" = "node:value(ResourceCoreConfigSet/ResourceMasterCore)"!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//



[!INDENT "0"!][!//
/*******************************************************************************
** Name           : CG_FindGptChannelMappedCoreId                             **
**                                                                            **
** Description    : This macro to get the channel mapping core                **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!/* To find the CoreId according to the GPT channel */!][!//
[!MACRO "CG_FindGptChannelMappedCoreId", "GptChId" = ""!][!//
    [!VAR "ModuleName" = "'GPT'"!][!//
    [!VAR "GptchannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "GptChannelMappedFlag" = "'false'"!][!//
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
                        [!IF "$GptChId = $Resource_ModuleName"!][!//
                            [!VAR "GptchannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "GptChannelMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            100-00-02-ERROR: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$GptChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the GPT channel to any core will default allocate to core0 */!][!//
        [!VAR "GptchannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Find which core used for GPT channel */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindTotalNumGptChannelMappedToCorex"!][!//
    [!VAR "GptChannelMappedCore0" = "0"!][!//
    [!VAR "GptChannelMappedCore1" = "0"!][!//
    [!VAR "GptChannelMappedCore2" = "0"!][!//
    [!VAR "GptChannelMappedCore3" = "0"!][!//
    [!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
        [!IF "./GptTimerChannelUsage = 'GPT_TIMER_CHANNEL_NORMAL'"!][!//
        [!CALL "CG_FindGptChannelMappedCoreId", "GptChId"="node:name(.)"!][!//
        [!IF "$GptchannelMappedCoreId = num:i(0)"!][!//
            [!VAR "GptChannelMappedCore0" = "$GptChannelMappedCore0 + 1"!][!//
        [!ELSEIF "$GptchannelMappedCoreId = num:i(1)"!][!//
            [!VAR "GptChannelMappedCore1" = "$GptChannelMappedCore1 + 1"!][!//
        [!ELSEIF "$GptchannelMappedCoreId = num:i(2)"!][!//
            [!VAR "GptChannelMappedCore2" = "$GptChannelMappedCore2 + 1"!][!//
        [!ELSEIF "$GptchannelMappedCoreId = num:i(3)"!][!//
            [!VAR "GptChannelMappedCore3" = "$GptChannelMappedCore3 + 1"!][!//
        [!ENDIF!][!//
        [!ENDIF!]
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "CG_FindTotalNumGptChannelMappedToCorex"!]

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : GPT_GetHWTimerIndex                                       **
**                                                                            **
** Description    : This macro to get the hardware channel index              **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "GPT_GetHWTimerIndex", "TimerString" = ""!][!//
  [!VAR "GtmTimerNo" = "node:ref($TimerString)/ModuleId"!][!//
  [!VAR "GtmChannelNo" = "node:ref($TimerString)/ChannelId"!][!//
  [!VAR "Timer" = "concat('GTM_TOM_INDEX_', $GtmTimerNo)"!][!//
  [!VAR "Channel" = "concat('GTM_TOM_CH_INDEX_', $GtmChannelNo)"!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//


[!INDENT "0"!][!//
/*******************************************************************************
** Name           : GPT_IsHwUnitExists                                        **
**                                                                            **
** Description    : This macro is used to check whthere the GTM or basetimer  **
**                  is used.                                                  **
**                                                                            **
*******************************************************************************/
[!MACRO "GPT_IsHwUnitUsed"!][!//
  [!VAR "Gpt_GTMChannelUsedNumber" = "0"!][!//
  [!VAR "Gpt_BaseTimerUsedNumber" = "0"!][!//
  [!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
    [!IF "node:value(GptTimerChannelUsage) = 'GPT_TIMER_CHANNEL_NORMAL' and ./GptAssignedHwUnit = 'GTM' "!][!//
      [!VAR "Gpt_GTMChannelUsedNumber" = "$Gpt_GTMChannelUsedNumber + num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "node:value(GptTimerChannelUsage) = 'GPT_TIMER_CHANNEL_NORMAL' and ./GptAssignedHwUnit = 'BASETIMER' "!][!//
      [!VAR "Gpt_BaseTimerUsedNumber" = "$Gpt_BaseTimerUsedNumber + num:i(1)"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "GPT_IsHwUnitUsed"!][!//


[!ENDIF!][!// avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//


[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Ocu.m
*
*   Platform             : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!]
[!IF "not(var:defined('OCU_CFG_COMMON_M'))"!]
[!VAR "OCU_CFG_COMMON_M"="'true'"!]

[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Resource')[1]))"!][!//
[!ERROR!][!//
    125-00-00-ERROR: Resource module is not added to the project.
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : CG_FindOcuChannelMappedCoreId                             **
**                                                                            **
** Description    : Find which core used for Ocu channel                      **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!/* To find the CoreId according to the OCU channel */!][!//
[!MACRO "CG_FindOcuChannelMappedCoreId", "OcuChId" = ""!][!//
    [!VAR "ModuleName" = "'OCU'"!][!//
    [!VAR "OcuchannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "OcuChannelMappedFlag" = "'false'"!][!//
    [!VAR "OcuchannelMappedRequestCoreId" = "num:i(0)"!][!//
    [!VAR "OcuChannelMappedRequestFlag" = "'false'"!][!//
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
                        [!IF "$OcuChId = $Resource_ModuleName"!][!//
                            [!VAR "OcuchannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "OcuChannelMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            125-00-01-ERROR: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$OcuChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the OCU channel to any core will default allocate to core0 */!][!//
        [!VAR "OcuchannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Find which core used for Ocu channel */!][!//
[!INDENT "0"!][!//
/*******************************************************************************
** Name           : CG_FindTotalNumOcuChannelMappedToCorex                    **
**                                                                            **
** Description    : Find which core used for Ocu channel                      **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "CG_FindTotalNumOcuChannelMappedToCorex"!][!//
    [!VAR "OcuChannelMappedCore0" = "num:i(0)"!][!//
    [!VAR "OcuChannelMappedCore1" = "num:i(0)"!][!//
    [!VAR "OcuChannelMappedCore2" = "num:i(0)"!][!//
    [!VAR "OcuChannelMappedCore3" = "num:i(0)"!][!//
    [!LOOP "node:order(OcuConfigSet/OcuChannel/*, 'OcuChannelId')"!][!//
        [!CALL "CG_FindOcuChannelMappedCoreId", "OcuChId"="node:name(.)"!][!//
        [!IF "$OcuchannelMappedCoreId = num:i(0)"!][!//
            [!VAR "OcuChannelMappedCore0" = "$OcuChannelMappedCore0 + num:i(1)"!][!//
        [!ELSEIF "$OcuchannelMappedCoreId = num:i(1)"!][!//
            [!VAR "OcuChannelMappedCore1" = "$OcuChannelMappedCore1 + num:i(1)"!][!//
        [!ELSEIF "$OcuchannelMappedCoreId = num:i(2)"!][!//
            [!VAR "OcuChannelMappedCore2" = "$OcuChannelMappedCore2 + num:i(1)"!][!//
        [!ELSEIF "$OcuchannelMappedCoreId = num:i(3)"!][!//
            [!VAR "OcuChannelMappedCore3" = "$OcuChannelMappedCore3 + num:i(1)"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "CG_FindTotalNumOcuChannelMappedToCorex"!]


[!INDENT "0"!][!//
/*******************************************************************************
** Name           : OCU_GetHWTimerIndex                                       **
**                                                                            **
** Description    : This macro to get the hardware channel index              **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "OCU_GetHWTimerIndex", "Channel" = ""!][!//
[!VAR "PinusedPath" = "concat($Channel, '/OcuOuptutPinUsed')"!][!//
[!VAR "PinusedFlag" = "node:value($PinusedPath)"!][!//
[!VAR "TimerUsed" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
[!VAR "GtmTimerNo" = "node:ref($TimerUsed)/ModuleId"!][!//
[!VAR "GtmChannelNo" = "node:ref($TimerUsed)/ChannelId"!][!//
[!VAR "TimerModule" = "'GTM_OUTPUT_MODULE_ATOM'"!][!//
[!VAR "Timer" = "concat('GTM_ATOM_INDEX_', $GtmTimerNo)"!][!//
[!VAR "Channel" = "concat('GTM_ATOM_CH_INDEX_', $GtmChannelNo)"!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Find ocu interface used channel configuration  */!][!//
[!INDENT "0"!][!//
/*******************************************************************************
** Name           : Ocu_FindOcuHWGtmAtomChannelConfig                         **
**                                                                            **
** Description    : Find hardware channel configuration which is based        **
**                  on GTM-ATOM                                               **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "Ocu_FindOcuHWGtmAtomChannelConfig", "Channel"=""!][!//
[!/* Find channel clock source and time base */!][!//
[!VAR "TimerClockSelectPath" = "concat($Channel, '/GtmTimerOutputModuleConfiguration/*[1]/GtmTimerClockSelect')"!][!//
[!VAR "TimerClock" = "node:value($TimerClockSelectPath)"!][!//
[!/* if clock is tbu */!][!//
[!VAR "TimerClockNo" = "text:split($TimerClock, 'GTM_TBU_TS')[1]"!][!//
[!IF "$TimerClockNo = 0"!]
  [!VAR "HWTimeBase" = "'GTM_ATOM_TIMEBASE_TS1'"!][!//
  [!VAR "MCALTimeBase" = "'GTM_TBU_CH_TS0'"!][!//
[!ELSE!][!//
  [!VAR "HWTimeBase" = "concat('GTM_ATOM_TIMEBASE_TS', $TimerClockNo)"!][!//
  [!VAR "MCALTimeBase" = "concat('GTM_TBU_CH_TS', $TimerClockNo)"!][!//
[!ENDIF!][!//
[!VAR "HWClockSrc" = "'GTM_ATOM_CH_CLKSRC_CMUCLK0'"!][!//
[!/* Find channel signal level */!][!//
[!VAR "PinusedPath" = "concat($Channel, '/OcuOuptutPinUsed')"!][!//
[!VAR "PinusedFlag" = "node:value($PinusedPath)"!][!//
[!IF "$PinusedFlag = 'true'"!][!//
    [!VAR "ChannelPinlevelPath" = "concat($Channel, '/OcuOutputPinDefaultState')"!][!//
    [!VAR "Pinlevel" = "node:ref($ChannelPinlevelPath)/*[1]"!][!//
    [!VAR "PinTemp" = "text:split($Pinlevel, 'OCU_')[last()]"!][!//
    [!/*In somc mode, sl complete the output status */!][!//
    [!VAR "HWPinlevel" = "concat('GTM_SIGNALSTATE_', $PinTemp)"!][!//
[!ELSE!][!//
    [!VAR "HWPinlevel" = "'GTM_SIGNALSTATE_LOW'"!][!//
[!ENDIF!][!//
[!/* Find channel output behavior */!][!//
[!VAR "DefaultThresholdPath" = "concat($Channel, '/OcuDefaultThreshold')"!][!//
[!VAR "DefaultThreshold" = "node:value($DefaultThresholdPath)"!][!//
[!VAR "HWCompareValue" = "num:i($DefaultThreshold)"!][!//
[!/* This parameter will be actually calculated in the API Ocu_StartChannel */!][!//
[!VAR "HWSomcSL" = "'GTM_OCU_SLCTRL_NOCHANGE'"!][!//
[!IF "$TimerClockNo = 0"!][!//
    [!VAR "HWSomc" = "'GTM_SOMCCTRL_CCU0TS0'"!][!//default value is to compare with tbus0
    [!VAR "HWCompareValue0" = "num:i($DefaultThreshold)"!][!//
    [!VAR "HWCompareValue1" = "num:i(0)"!][!//
[!ELSE!][!//
    [!VAR "HWSomc" = "'GTM_SOMCCTRL_CCU1TS12'"!][!//default value is to compare with tbus1/tbus2
    [!VAR "HWCompareValue0" = "num:i(0)"!][!//
    [!VAR "HWCompareValue1" = "num:i($DefaultThreshold)"!][!//
[!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Find ocu interface used channel configuration  */!][!//
[!INDENT "0"!][!//
/*******************************************************************************
** Name           : Ocu_FindOcuChannelConfig                                **
**                                                                            **
** Description    : Find ocu interface used channel configuration             **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "Ocu_FindOcuChannelConfig", "Channel"=""!][!//
[!/* Find channel mode */!][!//
[!VAR "PinusedFlag" = "./OcuOuptutPinUsed"!][!//
[!IF "$PinusedFlag = 'true'"!][!//
    [!VAR "MCALChMode" = "'OCU_COMPARE_EVENT_PIN'"!][!//
    [!VAR "MCALPinused" = "'TRUE'"!][!//
[!ELSE!][!//
    [!VAR "MCALPinused" = "'FALSE'"!][!//
    [!IF "node:exists(./OcuHardwareTriggeredAdc/*[1])"!]
        [!VAR "MCALChMode" = "'OCU_COMPARE_EVENT_ADC'"!][!//
    [!ELSE!][!//
        [!VAR "MCALChMode" = "'OCU_COMPARE_EVENT_DMA'"!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!/* Find channel id */!][!//
[!VAR "MCALChannelId" = "./OcuChannelId"!][!//
[!/* Find channel max value */!][!//
[!VAR "MCALChannelMaxValue" = "./OcuMaxCounterValue"!][!//
[!/* Find channel default compare value */!][!//
[!VAR "MCALChannelDefaultThreshold" = "./OcuDefaultThreshold"!][!//
[!VAR "MCALHWClass" = "'OCU_HW_GTM_ATOM'"!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Find ocu hardware class of logic channel */!][!//
[!INDENT "0"!][!//
/*******************************************************************************
** Name           : Ocu_FindOcuHWClass                                        **
**                                                                            **
** Description    : Find ocu hardware class of logic channel                  **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "Ocu_FindOcuHWClass"!][!//
[!VAR "OCU_HWGtmAtomUsed" = "'FALSE'"!][!//
[!SELECT "as:modconf('Ocu')[1]/OcuConfigSet/OcuChannel"!][!//
  [!LOOP "node:order(./*, 'OcuChannelId')"!][!//
    [!VAR "OCU_TimerUsed" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
    [!IF "contains($OCU_TimerUsed, 'GtmAtom')"!][!//
      [!VAR "OCU_HWGtmAtomUsed" = "'TRUE'"!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "Ocu_FindOcuHWClass"!][!//

[!/* Find the ocu channel number of logic channel */!][!//
[!INDENT "0"!][!//
/*******************************************************************************
** Name           : Ocu_FindOcuHWClassNumber                                  **
**                                                                            **
** Description    : Find the ocu channel number of logic channel              **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "Ocu_FindOcuHWClassNumber"!][!//
[!VAR "OCU_HWGtmAtomNumber" = "0"!][!//
[!SELECT "as:modconf('Ocu')[1]/OcuConfigSet/OcuChannel"!][!//
  [!LOOP "node:order(./*, 'OcuChannelId')"!][!//
    [!VAR "OCU_TimerUsed" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
    [!VAR "OCU_HWGtmAtomNumber" = "$OCU_HWGtmAtomNumber + num:i(1)"!][!//
  [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "Ocu_FindOcuHWClassNumber"!][!//

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : Ocu_GetWrapperConfigInfo                                  **
**                                                                            **
** Description    : This function is used to get Gtm wrapper configuration    **
**                                                                            **
*******************************************************************************/
[!MACRO "Ocu_GetWrapperConfigInfo", "ModuleName" = "", "ModuleId" = "", "ChannelId" = ""!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Mcu/ELEMENTS/Mcu/GtmConfiguration/*[1]"!][!//
[!IF "./Atom/*/AtomChannel/*[./AtomChannelOutput/AtomId = num:i($ModuleId) and ./AtomChannelOutput/ChannelId  = num:i($ChannelId)]/AtomChannelOutput/GTM_Atom_Negative_Support = 'true'"!][!//
    [!VAR "ToutCfg" = "./Atom/*/AtomChannel/*[./AtomChannelOutput/AtomId = num:i($ModuleId) and ./AtomChannelOutput/ChannelId  = num:i($ChannelId)]/AtomChannelOutput/AtomChannelNegativePortPinSelect"!][!//
[!ELSE!][!//
    [!VAR "ToutCfg" = "./Atom/*/AtomChannel/*[./AtomChannelOutput/AtomId = num:i($ModuleId) and ./AtomChannelOutput/ChannelId  = num:i($ChannelId)]/AtomChannelOutput/AtomChannelPortPinSelect"!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

/*******************************End of functions*******************************/
[!ENDIF!][!// avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : OCU_GetATOMIndex                                          **
**                                                                            **
** Description    : This macro to get the hardware channel index              **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "OCU_GetATOMIndex", "ChannelRef" = ""!][!//
    [!IF "node:exists(node:ref($ChannelRef)/GtmAtomChannel)"!][!//
        [!VAR "TimerType" = "'GTM_OUTPUT_MODULE_ATOM'"!][!//
    [!ELSE!][!//
        [!VAR "TimerType" = "'GTM_OUTPUT_MODULE_TOM'"!][!//
    [!ENDIF!][!//
    [!VAR "GtmTimerNo" = "node:ref($ChannelRef)/ModuleId"!][!//
    [!VAR "GtmChannelNo" = "node:ref($ChannelRef)/ChannelId"!][!//
    [!VAR "Timer" = "concat('GTM_OCU_MODULE_INDEX_', $GtmTimerNo)"!][!//
    [!VAR "Channel" = "concat('GTM_OCU_CH_INDEX_', $GtmChannelNo)"!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//


/****************************************************************************************************
*   FileName              : Gpt_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, BASETIMER
*
*   brief                 : This file contains all post-build parameters in GPT Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*           
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
****************************************************************************************************/
/*
*#Violation Summary
*
*#Gpt_PBcfg_c_REF_1:MISRAC2012-Rule-11.4; 
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Gpt_PBcfg_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
* driver must be placed.
*
*#Gpt_PBcfg_c_REF_3:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*#Gpt_PBcfg_c_REF_4:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

[!NOCODE!][!//
[!INCLUDE "Gpt.m"!][!//
[!ENDNOCODE!][!//
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#include "Gpt.h"
#include "Gpt_Cfg.h"

/****************************************************************************************************
**                          GLOBAL VARIABLES                                                       **
****************************************************************************************************/

/****************************************************************************************************
**                          Configurations                                                         **
****************************************************************************************************/

[!INDENT "0"!][!//
[!AUTOSPACING!][!//
[!VAR "GptNotificationList" = "''"!][!//
[!VAR "GptNotifChannelMapping" = "''"!][!//
[!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
  [!IF "node:exists(GptNotification/*[1])"!][!//
    [!IF "not(num:isnumber(GptNotification/*[1]))"!][!//
      [!VAR "Notification" = "GptNotification/*[1]"!][!//
      [!IF "not(contains(text:split($GptNotificationList), $Notification))"!][!//
          [!VAR "GptNotificationList" = "concat($GptNotificationList , $Notification, '#,')"!][!//
      [!ENDIF!][!//
        [!VAR "GptNotifChannelMapping" = "concat($GptNotifChannelMapping , $Notification, '#', node:name(.), ',')"!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!//
/* Notification Function Declarations */
[!LOOP "text:split($GptNotificationList, ',')"!][!//
extern void [!"text:replace( (.), '#', '' )"!](void);
[!ENDLOOP!][!//

/****************************************************************************************************
********                    Low level driver configurations                                  ********
****************************************************************************************************/

/****************************************************************************************************
**              Low level driver configurations of the channel based on GTM                        **
****************************************************************************************************/
[!IF "$Gpt_GTMChannelUsedNumber != num:i(0)"!][!//
[!AUTOSPACING!][!//
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"

/* #Violation: Gpt_PBcfg_c_REF_3 */
static const Gpt_GtmConfigType Gpt_GtmChannelConfig[[!"num:i($Gpt_GTMChannelUsedNumber)"!]U] =
{
[!VAR "Cnt0" = "0"!][!//
[!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
  [!IF "./GptAssignedHwUnit = 'GTM'"!]
    [!NOCODE!][!//
    [!/* Get channel clock source */!][!//
    [!VAR "Gpt_ChannelClock" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerClockSelect"!][!//
    [!VAR "Gpt_ChannelClockNo" = "text:split($Gpt_ChannelClock, 'CMU_FXCLK')[1]"!][!//
    [!VAR "Gpt_ChannelClock" = "concat('GTM_TOM_CH_CLKSRC_CMUFXCLK',$Gpt_ChannelClockNo)"!][!//
    [!/* Get channel index */!][!//
    [!VAR "TimerUsed" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
    [!CALL "GPT_GetHWTimerIndex", "TimerString" = "$TimerUsed"!][!//
    [!/* Get channel count mode */!][!//
    [!VAR "Gpt_ChannelOneShot" = "'TRUE'"!][!//
    [!IF "node:value(GptChannelMode) = 'GPT_CH_MODE_CONTINUOUS'"!][!//
        [!VAR "Gpt_ChannelOneShot" = "'FALSE'"!][!//
    [!ENDIF!][!//
    [!ENDNOCODE!][!//
    [!IF "GptTimerChannelUsage = 'GPT_TIMER_CHANNEL_NORMAL'"!][!//
      [!IF "$Cnt0 != num:i(0)"!][!//
        [!INDENT "0"!][!//
        ,
        [!ENDINDENT!][!//
      [!ENDIF!][!//
      [!CODE!][!//
      [!VAR "Cnt0" = "1"!][!//
      [!INDENT "4"!][!//
      /* [!"@name"!] low level driver configuration */
      {
        [!INDENT "8"!][!//
        /* Channel Hardware index */
        {
          [!INDENT "12"!][!//
          /* GTM Submodule Id */
          (uint8)GTM_OUTPUT_MODULE_TOM,
          /* Low level timer module Id */
          (uint8)[!"$Timer"!],
          /* Group index, only used for TIO module */
          0U,
          /* Low level timer channel Id */
          (uint8)[!"$Channel"!]
          [!ENDINDENT!][!//
        },
        /* Channel Hardware Configuration */
        {
          [!INDENT "12"!][!//
          /* Channel Clock Source, the current frequency is [!"node:value(GptChannelTickFrequency)"!]Hz */
          [!"$Gpt_ChannelClock"!],
          /* Channel Interrupt Signal Level */
          GTM_IRQMODE_LEVEL,
          /* Channel Output Trigger Signal */
          GTM_TOM_CH_TRIGOUT_FORWARD,
          /*Channel Timer One-Shot Mode */
          [!"$Gpt_ChannelOneShot"!],    
          /*Channel Interrupt Control */
          FALSE
          [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
      }[!//
      [!ENDINDENT!][!//
      [!ENDCODE!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//

};

/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
[!ENDIF!][!//

/****************************************************************************************************
**              Low level driver configurations of the channel based on Base Timer                 **
****************************************************************************************************/
[!IF "$Gpt_BaseTimerUsedNumber != num:i(0)"!][!//
[!AUTOSPACING!][!//
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"

/* #Violation: Gpt_PBcfg_c_REF_3 */
static const Gpt_BasetimerConfigType Gpt_BasetimerChannelConfig[[!"num:i($Gpt_BaseTimerUsedNumber)"!]U] =
{
[!VAR "Cnt0" = "0"!][!//
[!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
  [!IF "./GptAssignedHwUnit = 'BASETIMER' and GptTimerChannelUsage = 'GPT_TIMER_CHANNEL_NORMAL'"!][!//
    [!NOCODE!][!//
    [!/* Get interface object of hal */!][!//
    [!VAR "Gpt_BasetimerObject" = "./BaseTimerUsed"!][!//
    [!/* Get channel mode and calculate the hardware mdoe */!][!//
    [!IF "./GptChannelMode = 'GPT_CH_MODE_CONTINUOUS'"!][!//
      [!VAR "Gpt_BasetimerMode" = "'BASETIMER_MODE_PERIODIC'"!][!//
    [!ELSEIF "./GptChannelMode = 'GPT_CH_MODE_ONESHOT'"!][!//
      [!VAR "Gpt_BasetimerMode" = "'BASETIMER_MODE_ONESHOT'"!][!//
    [!ENDIF!][!//
    [!/* This is used to add ',' correctly */!][!//
    [!ENDNOCODE!][!//
    [!IF "$Cnt0 != num:i(0)"!][!//
      [!INDENT "0"!][!//
      ,
      [!ENDINDENT!][!//
    [!ENDIF!][!//
    [!VAR "Cnt0" = "1"!][!//
    [!CODE!][!//
    [!INDENT "4"!][!//
    /* [!"@name"!] */
    {
      [!INDENT "8"!][!//
      /* Base timer object */
      /* #Violation: Gpt_PBcfg_c_REF_1 */
      [!"$Gpt_BasetimerObject"!],
      /* Channel Configuration */
      {
        [!INDENT "12"!][!//
        /* Specifies the counter size */
        BASETIMER_SIZE_32BITS,
        /* Specifies the initial counter value */
        0U,
        /* Specifies the counter mode */
        [!"$Gpt_BasetimerMode"!]
        [!ENDINDENT!][!//
      }
      [!ENDINDENT!][!//
    }[!//
    [!ENDINDENT!][!//
    [!ENDCODE!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//

};

/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
[!ENDIF!][!//

/****************************************************************************************************
**                               MCAL driver configurations                                        **
****************************************************************************************************/
[!FOR "CoreIndex" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - num:i(1))"!][!//
  [!IF "$CoreIndex = num:i(0) and num:i($GptChannelMappedCore0) > num:i(0)"!][!//
    [!VAR "GptChannelMappedCore" = "'true'"!][!//
    [!VAR "GptChannelMappedCoreNum" = "$GptChannelMappedCore0"!][!//
  [!ELSEIF "$CoreIndex = num:i(1) and num:i($GptChannelMappedCore1) > num:i(0)"!][!//
    [!VAR "GptChannelMappedCore" = "'true'"!][!//
    [!VAR "GptChannelMappedCoreNum" = "$GptChannelMappedCore1"!][!//
  [!ELSEIF "$CoreIndex = num:i(2) and num:i($GptChannelMappedCore2) > num:i(0)"!][!//
    [!VAR "GptChannelMappedCore" = "'true'"!][!//
    [!VAR "GptChannelMappedCoreNum" = "$GptChannelMappedCore2"!][!//
  [!ELSEIF "$CoreIndex = num:i(3) and num:i($GptChannelMappedCore3) > num:i(0)"!][!//
    [!VAR "GptChannelMappedCore" = "'true'"!][!//
    [!VAR "GptChannelMappedCoreNum" = "$GptChannelMappedCore3"!][!//
  [!ELSE!][!//
    [!VAR "GptChannelMappedCore" = "'false'"!][!//
    [!VAR "GptChannelMappedCoreNum" = "num:i(0)"!][!//
  [!ENDIF!][!//
[!IF "$GptChannelMappedCore = 'true'"!][!//
/****************************************************************************************************
**                                  Core[!"$CoreIndex"!]       configurations                                     **
****************************************************************************************************/
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
static const Gpt_ChConfigType Gpt_Core[!"$CoreIndex"!]ChannelConfig[GPT_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
{
[!VAR "Cnt0" = "0"!][!//
[!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
  [!IF "GptTimerChannelUsage = 'GPT_TIMER_CHANNEL_NORMAL'"!][!//
    [!CALL "CG_FindGptChannelMappedCoreId", "GptChId"="node:name(.)"!][!//
    [!IF "$GptchannelMappedCoreId = num:i($CoreIndex)"!][!//
    [!NOCODE!][!//
      [!VAR "GptEBChannelId" = "GptChannelId"!][!//
      [!VAR "GptChannelMaxTick" = "GptChannelTickValueMax"!][!//
      [!IF "node:empty(./GptNotification/*[1])"!][!//
        [!VAR "Gpt_ChannelNotification" = "'NULL_PTR'"!][!//
      [!ELSE!][!//
        [!VAR "Gpt_ChannelNotification" = "./GptNotification/*[1]"!][!//
      [!ENDIF!][!//
      [!/* Get hardware class of this channel */!][!//
      [!IF "./GptAssignedHwUnit   = 'GTM'"!][!//
        [!VAR "Gpt_ChannelHwUnit" = "'GPT_HW_GTM'"!][!//
      [!ELSEIF "./GptAssignedHwUnit   = 'BASETIMER'"!][!//
        [!VAR "Gpt_ChannelHwUnit" = "'GPT_HW_BASETIMER'"!][!//
      [!ENDIF!][!//
      [!/* Get wakeup enable status of this channel */!][!//
      [!IF "node:exists(./GptEnableWakeup) and ./GptEnableWakeup = 'true'"!][!//
        [!VAR "Gpt_WakeupEnable" = "'TRUE'"!][!//
      [!ELSE!][!//
        [!VAR "Gpt_WakeupEnable" = "'FALSE'"!][!//
      [!ENDIF!][!//
      [!/* Get channel wakeup info */!][!//
      [!VAR "WakeupInfo" = "num:i(0)"!][!//
      [!IF "node:value(../../../GptDriverConfiguration/GptReportWakeupSource) = 'true' and node:value(./GptEnableWakeup) = 'true'"!][!//
        [!IF "node:exists(./GptWakeupConfiguration/*[1]/GptWakeupSourceRef) and string-length(./GptWakeupConfiguration/*[1]/GptWakeupSourceRef) > 0"!][!//
          [!VAR "WakeupInfo" = "node:ref(node:path(node:ref(./GptWakeupConfiguration/*[1]/GptWakeupSourceRef)))/EcuMWakeupSourceId"!][!//
        [!ELSE!][!//
          [!WARNING!][!//
            [!"@name"!]: GptWakeupSourceRef is not valid, default wakeup id '0' is generated.
          [!ENDWARNING!][!//
        [!ENDIF!]
      [!ENDIF!][!//
      [!ENDNOCODE!][!//
      [!IF "$Cnt0 != num:i(0)"!][!//
,
      [!ENDIF!][!//
      [!CODE!]
      [!VAR "Cnt0" = "1"!][!//
    /* [!"@name"!] */
    {
        /* Channel Id */
        [!"$GptEBChannelId"!]U,
        /* Wakeup enable state */
        [!"$Gpt_WakeupEnable"!],
        /* Maximum tick */
        [!"num:inttohex($GptChannelMaxTick)"!]U,
        /* Notification function pointer */
        [!"$Gpt_ChannelNotification"!],
        /* Wakeup information to EcuM_SetWakeupEvent */
        [!"$WakeupInfo"!],
        /* Hardware class of logic channel */
        [!"$Gpt_ChannelHwUnit"!]
    }[!//
      [!ENDCODE!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//

};

/* GPT channels configuration of core[!"$CoreIndex"!] */
static const Gpt_CoreConfigType Gpt_CoreConfigCore[!"$CoreIndex"!] =
{
    /* Number of core[!"$CoreIndex"!] maximum channels */
    [!"num:i($GptChannelMappedCoreNum)"!]U,
    /*Channel configuration*/
    &Gpt_Core[!"$CoreIndex"!]ChannelConfig[0]
};
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
[!ENDIF!][!//
[!ENDFOR!][!//

[!IF "$Gpt_GTMChannelUsedNumber != num:i(0) or  $Gpt_BaseTimerUsedNumber != num:i(0) "!][!//
    /* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
[!AUTOSPACING!][!//
/* This array is used for mapping Gpt Channel to the Core 
 * and mapping the hardware configuration to logic channel */
static const Gpt_MappingType Gpt_ChannelToCoreMap[GPT_MAX_CHANNELS] =
{
[!VAR "Cnt" = "0"!][!//
[!VAR "ChannelToCore0Num" = "0"!][!//
[!VAR "ChannelToCore1Num" = "0"!][!//
[!VAR "ChannelToCore2Num" = "0"!][!//
[!VAR "ChannelToCore3Num" = "0"!][!//
[!VAR "Gpt_GtmNumber" = "-1"!][!//
[!VAR "Gpt_BasetimerNumber" = "-1"!][!//
[!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
    [!IF "GptTimerChannelUsage = 'GPT_TIMER_CHANNEL_NORMAL'"!][!//
        [!NOCODE!][!//
        [!VAR "GtmTimer" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
        [!CALL "CG_FindGptChannelMappedCoreId", "GptChId"="node:name(.)"!][!//
        [!IF "$GptchannelMappedCoreId = num:i(0)"!][!//
             [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore0Num)"!][!//
             [!VAR "ChannelToCore0Num" = "num:i($ChannelToCore0Num) + 1"!][!//
        [!ELSEIF "$GptchannelMappedCoreId = num:i(1)"!][!//
             [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore1Num)"!][!//
             [!VAR "ChannelToCore1Num" = "num:i($ChannelToCore1Num) + 1"!][!//
        [!ELSEIF "$GptchannelMappedCoreId = num:i(2)"!][!//
             [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore2Num)"!][!//
             [!VAR "ChannelToCore2Num" = "num:i($ChannelToCore2Num) + 1"!][!//
        [!ELSEIF "$GptchannelMappedCoreId = num:i(3)"!][!//
             [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore3Num)"!][!//
             [!VAR "ChannelToCore3Num" = "num:i($ChannelToCore3Num) + 1"!][!//
        [!ENDIF!][!//
        [!VAR "ChannelCoreNum" = "concat('MCAL_CORE', $GptchannelMappedCoreId)"!][!//
        [!/* Compute the hardware configuration index */!][!//
        [!IF "./GptAssignedHwUnit = 'GTM'"!][!//
          [!VAR "Gpt_GtmNumber" = "$Gpt_GtmNumber + num:i(1)"!][!//
          [!VAR "Gpt_HwCfgIndex" = "num:i($Gpt_GtmNumber)"!][!//
        [!ELSEIF "./GptAssignedHwUnit = 'BASETIMER'"!][!//
          [!VAR "Gpt_BasetimerNumber" = "$Gpt_BasetimerNumber + num:i(1)"!][!//
          [!VAR "Gpt_HwCfgIndex" = "num:i($Gpt_BasetimerNumber)"!][!//
        [!ENDIF!][!//
        [!ENDNOCODE!][!//
        [!CODE!][!//
        [!IF "$Cnt != num:i(0)"!][!//
,
        [!ENDIF!][!//
        [!VAR "Cnt" = "1"!]
    /* [!"@name"!] */
    {
        /* Core number */
        (uint8)[!"$ChannelCoreNum"!], 
        /* Channel index in specific core */
        [!"$ChannelToCoreNumIndex"!]U,
        /* Hardware configuration mapping index */
        [!"$Gpt_HwCfgIndex"!]U
    }[!//
       [!ENDCODE!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//

};[!// End of core mapping
/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
[!ENDIF!][!//

/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
[!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*[contains(./GptTimerChannelUsage,'1US')], 'GptChannelId')"!][!//
  [!/* Find 1us hardware channel type */!][!//
  [!IF "./GptAssignedHwUnit = 'GTM'"!][!//
    [!VAR "Predef1USHwClass" = "'GPT_PREDEF_TIMER_HW_GTM'"!][!//
  [!ELSEIF "./GptAssignedHwUnit = 'BASETIMER'"!][!//
    [!VAR "Predef1USHwClass" = "'GPT_PREDEF_TIMER_HW_BASETIMER'"!][!//
    [!VAR "Predef1USBasetimerIndex" = "./BaseTimerUsed"!][!//
  [!ENDIF!][!//
  [!BREAK!][!//
[!ENDLOOP!][!//

/* Mapping the hardware channel(GTM-TOM) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Gpt_PBcfg_c_REF_3 */
static const uint8 Gpt_HwTomChannelMap[[!"num:i(ecu:get('Gtm.NumberOfTomModules') * ecu:get('Gtm.NumberOfTomChannels'))"!]U] =
{
[!VAR "LastChannel" = "concat(num:i(ecu:get('Gtm.NumberOfTomModules') - 1), num:i(ecu:get('Gtm.NumberOfTomChannels') - 1))"!][!//
[!FOR "ModeleIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfTomModules') - 1)"!][!//
  [!FOR "ChIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfTomChannels') - 1)"!][!//
      [!VAR "CurrentHwChannel" = "concat($ModeleIndex, $ChIndex)"!][!//
      [!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
        [!VAR "LogicChannelId" = "'0xFF'"!][!//
        [!IF "./GptAssignedHwUnit   = 'GTM' and not(contains(./GptTimerChannelUsage, 'GPT_PREDEF_TIMER'))"!][!//
          [!VAR "TimerUsed" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
          [!CALL "GPT_GetHWTimerIndex", "TimerString" = "$TimerUsed"!][!//
          [!VAR "LogicHwChannel" = "concat($GtmTimerNo, $GtmChannelNo)"!][!//
          [!IF "$CurrentHwChannel = $LogicHwChannel"!][!//
            [!VAR "LogicChannelId" = "./GptChannelId"!][!//
            [!BREAK!]
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
      /* TOM[!"$ModeleIndex"!]_CH[!"$ChIndex"!] */
      [!IF "$CurrentHwChannel != $LastChannel"!][!//
      [!"$LogicChannelId"!]U,
      [!ELSE!]
      [!"$LogicChannelId"!]U
      [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDFOR!][!//
};

/* Mapping the hardware channel(BASETIMER) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Gpt_PBcfg_c_REF_3 */
static const uint8 Gpt_HwBasetimerChannelMap[[!"num:i(ecu:get('Basetimer.MaxHwUnit'))"!]U] =
{
[!VAR "LastChannel" = "ecu:list('Basetimer.HwUnitList')[last()]"!][!//
[!FOR "ModeleIndex" = "num:i(0)" TO "num:i(ecu:get('Basetimer.MaxHwUnit') - 1)"!][!//
  [!VAR "CurrentHwChannel" = "ecu:list('Basetimer.HwUnitList')[num:i($ModeleIndex+1)]"!][!//
  [!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*, 'GptChannelId')"!][!//
    [!VAR "LogicChannelId" = "'0xFF'"!][!//
    [!IF "./GptAssignedHwUnit   = 'BASETIMER' and not(contains(./GptTimerChannelUsage, 'GPT_PREDEF_TIMER'))"!][!//
      [!VAR "LogicHwChannel" = "./BaseTimerUsed"!][!//
      [!IF "$CurrentHwChannel = $LogicHwChannel"!][!//
        [!VAR "LogicChannelId" = "./GptChannelId"!][!//
        [!BREAK!]
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  /* [!"$CurrentHwChannel"!] */
  [!IF "$CurrentHwChannel != $LastChannel"!][!//
  [!"$LogicChannelId"!]U,
  [!ELSE!]
  [!"$LogicChannelId"!]U
  [!ENDIF!][!//
[!ENDFOR!][!//
};

[!VAR "Predef1USBasetimerIndex" = "'NULL_PTR'"!][!//
[!VAR "GptPredefTimer1us" = "GptDriverConfiguration/GptPredefTimer1usEnablingGrade"!][!//
[!IF "$GptPredefTimer1us != 'GPT_PREDEF_TIMER_1US_DISABLED'"!][!//
  [!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*[./GptTimerChannelUsage != 'GPT_TIMER_CHANNEL_NORMAL'], 'GptChannelId')"!][!//
    [!VAR "ChannelUsage" = "./GptTimerChannelUsage"!][!//
    [!IF "contains($ChannelUsage, '1US')"!][!//
        [!VAR "Predef1USBasetimerIndex" = "./BaseTimerUsed"!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDIF!][!//
[!VAR "Predef100USBasetimerIndex" = "'NULL_PTR'"!][!//
[!VAR "GptPredefTimer100us" = "GptDriverConfiguration/GptPredefTimer100us32bitEnable"!][!//
[!IF "$GptPredefTimer100us = 'true'"!][!//
  [!LOOP "node:order(GptChannelConfigSet/GptChannelConfiguration/*[./GptTimerChannelUsage != 'GPT_TIMER_CHANNEL_NORMAL'], 'GptChannelId')"!][!//
    [!VAR "ChannelUsage" = "./GptTimerChannelUsage"!][!//
    [!IF "contains($ChannelUsage, '100US')"!][!//
      [!VAR "Predef100USBasetimerIndex" = "./BaseTimerUsed"!][!//
      [!BREAK!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDIF!][!//

/* Configuration parameters */
[!IF "variant:name() != ''"!][!//
const Gpt_ConfigType Gpt_ConfigSet_[!"variant:name()"!][1U] =
[!ELSE!][!//
const Gpt_ConfigType Gpt_ConfigSet[1U] =
[!ENDIF!][!//
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
[!VAR "Cnt0" = "num:i(0)"!][!//
[!FOR "CoreIndex" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - num:i(1))"!][!//
  [!IF "$CoreIndex = num:i(0)"!][!//
    [!VAR "GptChannelMappedCoreNum" = "$GptChannelMappedCore0"!][!//
  [!ELSEIF "$CoreIndex = num:i(1)"!][!//
    [!VAR "GptChannelMappedCoreNum" = "$GptChannelMappedCore1"!][!//
  [!ELSEIF "$CoreIndex = num:i(2)"!][!//
    [!VAR "GptChannelMappedCoreNum" = "$GptChannelMappedCore2"!][!//
  [!ELSEIF "$CoreIndex = num:i(3)"!][!//
    [!VAR "GptChannelMappedCoreNum" = "$GptChannelMappedCore3"!][!//
  [!ELSE!][!//
    [!VAR "GptChannelMappedCoreNum" = "num:i(0)"!][!//
  [!ENDIF!][!//
    [!/* Add ,  */!][!//
  [!IF "$Cnt0 != num:i(0)"!][!//
  [!CODE!][!//
,
  [!ENDCODE!][!//
  [!ENDIF!][!//
  [!VAR "Cnt0" = "1"!][!//
  [!IF "$GptChannelMappedCoreNum != num:i(0)"!][!//
            /* GPT channels configuration's pointer of core[!"$CoreIndex"!] */
            &Gpt_CoreConfigCore[!"$CoreIndex"!][!//
  [!ELSE!][!//
            /* GPT channels configuration's pointer of core[!"$CoreIndex"!] */
            NULL_PTR[!//
  [!ENDIF!][!//
[!ENDFOR!][!//
            [!ENDINDENT!][!//

        },
        /* Table for relationship between channel ID in specified core and GPT channel ID */
[!IF "$Gpt_GTMChannelUsedNumber != num:i(0) or  $Gpt_BaseTimerUsedNumber != num:i(0) "!][!//
          &Gpt_ChannelToCoreMap[0U],
[!ELSE!][!//
        NULL_PTR,
[!ENDIF!][!//
        /* Hardware configuration for channel based on GTM */
[!IF "$Gpt_GTMChannelUsedNumber != num:i(0)"!][!//
        &Gpt_GtmChannelConfig[0U],
[!ELSE!][!//
        NULL_PTR,
[!ENDIF!][!//
        /* Hardware configuration for channel based on base timer */
[!IF "$Gpt_BaseTimerUsedNumber != num:i(0)"!][!//
        &Gpt_BasetimerChannelConfig[0U],
[!ELSE!][!//
        NULL_PTR,
[!ENDIF!][!//
        {
            [!INDENT "12"!][!//
            /* Pointer to GTM-TOM channel mapping with logic channel */
            &Gpt_HwTomChannelMap[0U],
            /* Pointer to BASETIMER channel mapping with logic channel */
            &Gpt_HwBasetimerChannelMap[0U]
            [!ENDINDENT!][!//
        },
        {
            [!INDENT "12"!][!//
            /* Pointer to 1us predef timer base address */
            /* #Violation: Gpt_PBcfg_c_REF_1 */
            [!"$Predef1USBasetimerIndex"!],
            /* Pointer to 100us predef timer base address */
            /* #Violation: Gpt_PBcfg_c_REF_1 */
            [!"$Predef100USBasetimerIndex"!]
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};

/* #Violation: Gpt_PBcfg_c_REF_4 */
#define GPT_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Gpt_PBcfg_c_REF_2 */
#include "Gpt_MemMap.h"
/****************************************************************************************************
*   FileName              : Pwm_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-TOM, GTM-ATOM
*
*   brief                 : This file contains all post-build parameters in PWM Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
* 
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
/*
*#Violation Summary
*
*#Pwm_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Pwm_PBcfg_c_REF_2:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Pwm_PBcfg_c_REF_3:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
* 
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!NOCODE!][!//
[!AUTOSPACING!]
[!INCLUDE "Pwm_Cfg.m"!][!//
[!ENDNOCODE!][!//
/* SWS_Pwm_60075:
 *  Pwm_PBcfg.c shall include Pwm.h. */
#include "Pwm.h"
#include "Pwm_GeneralTypes.h"
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* Declare the notification functions */              
[!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId')"!][!//
  [!IF "(node:exists(./PwmNotification))and((./PwmNotification)!="")"!][!//
extern void [!"./PwmNotification"!](void);
  [!ENDIF!][!//
[!ENDLOOP!][!//


[!FOR "CoreIndex" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - num:i(1))"!][!//
  [!IF "$CoreIndex = num:i(0) and num:i($PwmChannelMappedCore0) > num:i(0)"!][!//
    [!VAR "PwmChannelMappedCore" = "'true'"!][!//
    [!VAR "PwmChannelMappedCoreNum" = "$PwmChannelMappedCore0"!][!//
  [!ELSEIF "$CoreIndex = num:i(1) and num:i($PwmChannelMappedCore1) > num:i(0)"!][!//
    [!VAR "PwmChannelMappedCore" = "'true'"!][!//
    [!VAR "PwmChannelMappedCoreNum" = "$PwmChannelMappedCore1"!][!//
  [!ELSEIF "$CoreIndex = num:i(2) and num:i($PwmChannelMappedCore2) > num:i(0)"!][!//
    [!VAR "PwmChannelMappedCore" = "'true'"!][!//
    [!VAR "PwmChannelMappedCoreNum" = "$PwmChannelMappedCore2"!][!//
  [!ELSEIF "$CoreIndex = num:i(3) and num:i($PwmChannelMappedCore3) > num:i(0)"!][!//
    [!VAR "PwmChannelMappedCore" = "'true'"!][!//
    [!VAR "PwmChannelMappedCoreNum" = "$PwmChannelMappedCore3"!][!//
  [!ELSE!][!//
    [!VAR "PwmChannelMappedCore" = "'false'"!][!//
    [!VAR "PwmChannelMappedCoreNum" = "num:i(0)"!][!//
  [!ENDIF!][!//
[!IF "$PwmChannelMappedCore = 'true'"!][!//
/****************************************************************************************************
**                                  Core[!"$CoreIndex"!]       configurations                                     **
****************************************************************************************************/
/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"
[!NOCODE!][!//
[!VAR "OutputsModuleNum" = "num:i(0)"!][!//
[!FOR "ModuleIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfTomModules') - num:i(1))"!][!//
  [!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId')"!][!//
    [!CALL "PWM_GetHWTimerIndex", "ChannelRef" = "./PwmChannelSelection"!][!//
    [!IF "$TimerType = 'GTM_OUTPUT_MODULE_TOM'"!][!//
      [!CALL "CG_FindPwmChannelMappedCoreId", "PwmChId"="node:name(.)"!][!//
      [!IF "$PwmchannelMappedCoreId = num:i($CoreIndex)"!][!//
        [!IF "$GtmTimerNo = num:i($ModuleIndex)"!][!//
            [!VAR "OutputsModuleNum" = "$OutputsModuleNum + num:i(1)"!][!//
            [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDFOR!][!//
[!FOR "ModuleIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfAtomModules') - num:i(1))"!][!//
  [!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId')"!][!//
    [!CALL "PWM_GetHWTimerIndex", "ChannelRef" = "./PwmChannelSelection"!][!//
    [!IF "$TimerType = 'GTM_OUTPUT_MODULE_ATOM'"!][!//
      [!CALL "CG_FindPwmChannelMappedCoreId", "PwmChId"="node:name(.)"!][!//
      [!IF "$PwmchannelMappedCoreId = num:i($CoreIndex)"!][!//
        [!IF "$GtmTimerNo = num:i($ModuleIndex)"!][!//
            [!VAR "OutputsModuleNum" = "$OutputsModuleNum + num:i(1)"!][!//
            [!BREAK!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//

[!IF "./PwmGeneral/PwmHandleShiftByOffset  = 'true'"!][!//
/* #Violation: Pwm_PBcfg_c_REF_2 */
static const Pwm_ChannelsOutputCfgType Pwm_ChannelsOutCore[!"$CoreIndex"!][[!"num:i($OutputsModuleNum)"!]U] =
{
[!VAR "Cnt0" = "num:i(0)"!][!//
[!VAR "OutputsModuleNum" = "num:i(0)"!][!//
[!FOR "ModuleIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfTomModules') - num:i(1))"!][!//
[!NOCODE!][!//
[!VAR "OutputsCfg" = "num:i(0)"!][!//
  [!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId')"!][!//
    [!CALL "PWM_GetHWTimerIndex", "ChannelRef" = "./PwmChannelSelection"!][!//
    [!IF "$TimerType = 'GTM_OUTPUT_MODULE_TOM'"!][!//
      [!CALL "CG_FindPwmChannelMappedCoreId", "PwmChId"="node:name(.)"!][!//
      [!IF "$PwmchannelMappedCoreId = num:i($CoreIndex)"!][!//
        [!IF "$GtmTimerNo = num:i($ModuleIndex)"!][!//
          [!IF "num:i($GtmChannelNo) > num:i(7)"!][!//
              [!VAR "OutputsCfg" = "bit:or($OutputsCfg, bit:shl(num:i(1),(num:i($GtmChannelNo) + num:i(8))))"!][!//
          [!ELSE!][!//
              [!VAR "OutputsCfg" = "bit:or($OutputsCfg, bit:shl(num:i(1),num:i($GtmChannelNo)))"!][!//
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!/* Current timer is checked complete, generate the output configuration for this core when it's not euqal to 0 */!][!//
[!ENDNOCODE!][!//
  [!IF "num:i($OutputsCfg) != num:i(0)"!][!//
    [!VAR "OutputsCfgNot" = "bit:not($OutputsCfg)"!][!//
    [!VAR "OutputsCfgNot" = "bit:and($OutputsCfgNot, num:i(16711935))"!][!//
    [!VAR "OutputsCfgNot" = "bit:shl($OutputsCfgNot,num:i(8))"!][!//
    [!VAR "OutputsCfg" = "bit:or($OutputsCfg, $OutputsCfgNot)"!][!//
[!IF "$Cnt0 != num:i(0)"!][!//
,
[!ENDIF!][!//
[!VAR "Cnt0" = "$Cnt0 + num:i(1)"!][!//
  /* Tom[!"$ModuleIndex"!] multiple channels output configuration */
  {
    /* Module number */
    [!"num:i($ModuleIndex)"!]U,
    /* Hardware channel type */
    GTM_OUTPUT_MODULE_TOM,
    /* Hardware channel index */
    [!"num:inttohex(bit:and($OutputsCfg, num:i(4294967295)))"!]U
  }[!//
  [!VAR "OutputsModuleNum" = "$OutputsModuleNum + num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//
[!FOR "ModuleIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfAtomModules') - num:i(1))"!][!//
[!NOCODE!][!//
[!VAR "OutputsCfg" = "num:i(0)"!][!//
  [!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId')"!][!//
    [!CALL "PWM_GetHWTimerIndex", "ChannelRef" = "./PwmChannelSelection"!][!//
    [!IF "$TimerType = 'GTM_OUTPUT_MODULE_ATOM'"!][!//
      [!CALL "CG_FindPwmChannelMappedCoreId", "PwmChId"="node:name(.)"!][!//
      [!IF "$PwmchannelMappedCoreId = num:i($CoreIndex)"!][!//
        [!IF "$GtmTimerNo = num:i($ModuleIndex)"!][!//
          [!VAR "OutputsCfg" = "bit:or($OutputsCfg, bit:shl(num:i(1),num:i($GtmChannelNo)))"!][!//
        [!ENDIF!][!//
      [!ENDIF!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!/* Current timer is checked complete, generate the output configuration for this core when it's not euqal to 0 */!][!//
[!ENDNOCODE!][!//
  [!IF "num:i($OutputsCfg) != num:i(0)"!][!//
    [!VAR "OutputsCfg" = "bit:or($OutputsCfg, bit:shl(bit:not($OutputsCfg),num:i(8)))"!][!//
[!IF "$Cnt0 != num:i(0)"!][!//
,
[!ENDIF!][!//
[!VAR "Cnt0" = "$Cnt0 + num:i(1)"!][!//
  /* Atom[!"$ModuleIndex"!] multiple channels output configuration */
  {
    /* Module number */
    [!"num:i($ModuleIndex)"!]U,
    /* Hardware channel type */
    GTM_OUTPUT_MODULE_ATOM,
    /* Hardware channel index */
    [!"num:inttohex(bit:and($OutputsCfg, num:i(65535)))"!]U
  }[!//
  [!VAR "OutputsModuleNum" = "$OutputsModuleNum + num:i(1)"!][!//
  [!ENDIF!][!//
[!ENDFOR!][!//

};
[!ENDIF!][!//


static const Pwm_ChConfigType Pwm_Core[!"$CoreIndex"!]ChannelConfig[PWM_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
{
[!NOCODE!][!//
[!VAR "Cnt0" = "0"!][!//
[!VAR "ChannelDutyTicks" = "num:i(0)"!][!//
[!VAR "ChannelPeriodTicks" = "num:i(0)"!][!//
[!VAR "PwmShiftByOffset" = "PwmGeneral/PwmHandleShiftByOffset"!][!//

[!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId')"!][!//
    [!CALL "CG_FindPwmChannelMappedCoreId", "PwmChId"="node:name(.)"!][!//
    [!/* Handle the channel allocated to core[!"$CoreIndex"!] */!][!//
    [!IF "$PwmchannelMappedCoreId = num:i($CoreIndex)"!][!//
        [!VAR "ChannelClockSrc" = "''"!][!//
        [!VAR "PwmEBChannelId" = "PwmChannelId"!][!//
        [!IF "./PwmIdleState = 'PWM_HIGH'"!][!//
            [!VAR "PwmIdleLevel" = "'GTM_SIGNALSTATE_HIGH'"!][!//
        [!ELSE!][!//
            [!VAR "PwmIdleLevel" = "'GTM_SIGNALSTATE_LOW'"!][!//
        [!ENDIF!][!//
        [!/* Find the channel class */!][!//
        [!IF "node:exists(PwmChannelClass)"!][!//
            [!VAR "PwmChannelType" = "./PwmChannelClass"!][!//
        [!ELSE!][!//
            [!VAR "PwmChannelType" = "'PWM_FIXED_PERIOD'"!][!// 
        [!ENDIF!][!//
        [!/* Find the channel notification function */!][!//
        [!IF "(node:exists(./PwmNotification))and((./PwmNotification)!="")"!][!//
            [!VAR "PwmNotifyfunction" = "./PwmNotification"!][!//
        [!ELSE!]
            [!VAR "PwmNotifyfunction" = "'NULL_PTR'"!][!//
        [!ENDIF!][!//
        [!VAR "ChannelPeriod" = "num:i(0)"!]
        [!VAR "PwmDutyCycle" = "num:i(0)"!]
        [!VAR "HWCounterOffset" = "num:i(0)"!]
        [!VAR "ChannelResetSource" = "''"!][!//
        [!CALL "PWM_GetHWConfigInfo"!][!//
        [!/* Find the channel polarity */!][!//
        [!IF "./PwmPolarity = 'PWM_HIGH'"!][!//
            [!VAR "PwmSignalLevel" = "'GTM_SIGNALSTATE_HIGH'"!][!//
        [!ELSE!][!//
            [!VAR "PwmSignalLevel" = "'GTM_SIGNALSTATE_LOW'"!][!//
        [!ENDIF!][!//
        [!/* Find the channel control, output control and mechanism */!][!//
        [!IF "$PwmShiftByOffset = 'false'"!][!//         
            [!VAR "PwmImmediate" = "'TRUE'"!][!//
            [!VAR "PwmChannelEnable" = "'TRUE'"!][!//
            [!VAR "PwmOutputEnable" = "'TRUE'"!][!//
        [!ELSE!][!//
            [!VAR "PwmImmediate" = "'FALSE'"!][!//
            [!VAR "PwmChannelEnable" = "'FALSE'"!][!//
            [!VAR "PwmOutputEnable" = "'FALSE'"!][!//
        [!ENDIF!][!//
        [!/* Find the channel coherent control */!][!//
        [!VAR "PwmCoherentControl" = "as:modconf('Pwm')[1]/PwmGeneral/PwmChannelCoherentSelection"!][!//
        [!IF "$PwmCoherentControl = 'true'"!][!//
            [!IF "./PwmCoherentUpdate = 'true'"!][!//
                [!VAR "PwmChannelCoherent" = "'TRUE'"!][!//
            [!ELSE!][!//
                [!VAR "PwmChannelCoherent" = "'FALSE'"!][!//
            [!ENDIF!][!//
        [!ELSE!][!//
            [!VAR "PwmDutyUpdateControl" = "as:modconf('Pwm')[1]/PwmGeneral/PwmDutycycleUpdatedEndperiod"!][!//
            [!VAR "PwmPeriodUpdateControl" = "as:modconf('Pwm')[1]/PwmGeneral/PwmPeriodUpdatedEndperiod"!][!//
            [!IF "$PwmDutyUpdateControl = 'true' or $PwmPeriodUpdateControl = 'true'"!][!//
                [!VAR "PwmChannelCoherent" = "'TRUE'"!][!//
            [!ELSE!][!//
                [!VAR "PwmChannelCoherent" = "'FALSE'"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
        [!/* Find the channel trigerout signal */!][!//
        [!VAR "PwmChannelId" = "./PwmChannelId"!][!//
        [!IF "node:exists(PwmChannelClass) = 'false' or ./PwmChannelClass = 'PWM_FIXED_PERIOD'"!][!//
            [!SELECT "as:modconf('Pwm')[1]/PwmChannelConfigSet/PwmChannel"!][!//
                [!LOOP "node:order(./*, 'PwmChannelId ')"!][!//
                    [!IF "node:exists(PwmChannelClass) = 'true' and ./PwmChannelClass != 'PWM_FIXED_PERIOD' and ./PwmChannelClass != 'PWM_VARIABLE_PERIOD'"!][!//                
                        [!VAR "PwmRefChannel" = "./PwmReferenceChannel"!][!//
                        [!IF "node:ref($PwmRefChannel)/PwmChannelId = $PwmChannelId"!][!//
                            [!VAR "ChannelTrigout" = "'GTM_PWM_TRIGOUT_GENERATE'"!][!//
                                [!IF "as:modconf('Pwm')[1]/PwmGeneral/PwmRefChannelOutputAhead = 'true'"!][!//
                                    [!VAR "HWCounterOffset" = "$HWPeriod"!][!//
                                [!ENDIF!][!//
                            [!BREAK!][!//
                        [!ELSE!][!//
                            [!VAR "ChannelTrigout" = "'GTM_PWM_TRIGOUT_FORWARD'"!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!VAR "ChannelTrigout" = "'GTM_PWM_TRIGOUT_FORWARD'"!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDSELECT!][!//
        [!ELSE!][!//
            [!VAR "ChannelTrigout" = "'GTM_PWM_TRIGOUT_FORWARD'"!][!//
        [!ENDIF!][!//

        [!/* Add ,  */!][!//
        [!IF "$Cnt0 != num:i(0)"!][!//
        [!CODE!][!//
,
        [!ENDCODE!][!//
        [!ENDIF!][!//
        [!VAR "Cnt0" = "1"!][!//
        [!INDENT "4"!][!//
        [!CODE!][!//
    {
        [!INDENT "8"!][!//
        /* Channel Id*/
        [!"$PwmEBChannelId"!]U,
        /* Idle State Level */
        [!"$PwmIdleLevel"!],
        /* Channel Class */
        [!"$PwmChannelType"!],
        /* Period */
        [!"$ChannelPeriodTicks"!]U,
        /* Duty Cycle */
        [!"$ChannelDutyTicks"!]U,
        /* Shift value */
        [!"$ShiftValueTick"!]U,
        /* Notification Function Pointer */
        [!"$PwmNotifyfunction"!],
        {
        [!ENDINDENT!][!//
        [!ENDCODE!][!//
        [!VAR "TimerType" = "''"!][!//
        [!VAR "Timer" = "''"!][!//
        [!VAR "Channel" = "''"!][!//
        [!CALL "PWM_GetHWTimerIndex", "ChannelRef" = "./PwmChannelSelection"!][!//
        [!INDENT "12"!][!//
        [!CODE!][!//
            {
                [!INDENT "16"!][!//
                /* Hardware Channel Type */
                (uint8)[!"$TimerType"!],
                /* Hardware Timer Module Index */
                (uint8)[!"$Timer"!],
                /* Group index, only used for TIO module */
                0U,
                /* Hardware Channel Index */
                (uint8)[!"$Channel"!]
                [!ENDINDENT!][!//
            },
            {
                [!INDENT "16"!][!//
                /* Clock Source */
                [!"$ChannelClockSrc"!],
                /* Actual Period */
                [!"$HWPeriod"!]U,
                /* Actual Duty Cycle */
                [!"$HWDuty"!]U,
                /* Initial Counter Shift */
                [!"$HWCounterOffset"!]U,
                {
                    [!INDENT "20"!][!//
                    /* The high resolution feature */
                    FALSE,
                    /* High resolution micro-steps for period */
                    0U,
                    /* High resolution micro-steps for pulse width */
                    0U
                    [!ENDINDENT!][!//
                },
                /* Channel Counter Reset Source */
                [!"$ChannelResetSource"!],
                /* Signal Level */
                [!"$PwmSignalLevel"!],
                {
                    [!INDENT "20"!][!//
                    /* CCU0 Trigger Interrupt */
                    FALSE,
                    /* CCU1 Trigger Interrupt */
                    FALSE,
                    /* Interrupt Mode */
                    GTM_IRQMODE_LEVEL
                    [!ENDINDENT!][!//
                },
                /* Trigger Output Signal Select */
                [!"$ChannelTrigout"!],
                /*PWM channel count mode*/
                GTM_PWM_COUNTMODE_UP,
                /* Update Mechanism */
                [!"$PwmChannelCoherent"!],
                /* Channel Control */
                [!"$PwmChannelEnable"!],
                /* Channel Output Control */
                [!"$PwmOutputEnable"!],
                /* Update Immediate Control */
                [!"$PwmImmediate"!]
                [!ENDINDENT!][!//
            }   
        [!ENDCODE!][!//
        [!ENDINDENT!]
        [!INDENT "8"!][!//  
        [!CODE!][!//            
        }
        [!ENDCODE!][!//  
        [!ENDINDENT!]
        [!INDENT "4"!][!// 
        [!CODE!][!// 
    }[!//
    [!ENDCODE!][!//  
    [!ENDINDENT!]
    [!ENDINDENT!]
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDNOCODE!][!//

};

/* PWM channels configuration of core[!"$CoreIndex"!] */
static const Pwm_CoreConfigType Pwm_CoreConfigCore[!"$CoreIndex"!] =
{
    /* Number of core[!"$CoreIndex"!] maximum channels */
    [!"num:i($PwmChannelMappedCoreNum)"!]U,
    /*Channel configuration*/
    &Pwm_Core[!"$CoreIndex"!]ChannelConfig[0],
    [!IF "./PwmGeneral/PwmHandleShiftByOffset  = 'true'"!][!//
    {
        /* Multiple channels output configuration */
        &Pwm_ChannelsOutCore[!"$CoreIndex"!][0],
        /* The number of modules that need to be output at the same time */
        [!"num:i($OutputsModuleNum)"!]U
    }
    [!ENDIF!][!//
};

/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"
[!ENDIF!][!//
[!ENDFOR!][!//


[!AUTOSPACING!][!//
/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"
/* This array is used for mapping Pwm Channel to the Core. */
static const Pwm_MappingType Pwm_ChannelToCoreMap[PWM_MAX_CHANNELS] =
{
[!VAR "Cnt" = "0"!][!//
[!VAR "ChannelToCore0Num" = "0"!][!//
[!VAR "ChannelToCore1Num" = "0"!][!//
[!VAR "ChannelToCore2Num" = "0"!][!//
[!VAR "ChannelToCore3Num" = "0"!][!//
[!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId')"!][!//
    [!CALL "CG_FindPwmChannelMappedCoreId", "PwmChId"="node:name(.)"!][!//
    [!IF "$PwmchannelMappedCoreId = num:i(0)"!][!//
          [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore0Num)"!][!//
          [!VAR "ChannelToCore0Num" = "num:i($ChannelToCore0Num) + 1"!][!//
    [!ELSEIF "$PwmchannelMappedCoreId = num:i(1)"!][!//
          [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore1Num)"!][!//
          [!VAR "ChannelToCore1Num" = "num:i($ChannelToCore1Num) + 1"!][!//
    [!ELSEIF "$PwmchannelMappedCoreId = num:i(2)"!][!//
          [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore2Num)"!][!//
          [!VAR "ChannelToCore2Num" = "num:i($ChannelToCore2Num) + 1"!][!//
    [!ELSEIF "$PwmchannelMappedCoreId = num:i(3)"!][!//
          [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore3Num)"!][!//
          [!VAR "ChannelToCore3Num" = "num:i($ChannelToCore3Num) + 1"!][!//
    [!ENDIF!][!//
    [!VAR "ChannelCoreNum" = "concat('MCAL_CORE', $PwmchannelMappedCoreId)"!][!//
    [!CODE!][!//
    [!IF "$Cnt != num:i(0)"!][!//
,
    [!ENDIF!][!//
    [!VAR "Cnt" = "1"!]
    /* [!"@name"!] */
    {
        /* Core number */
        (Mcal_CoreType)[!"$ChannelCoreNum"!], 
        /* Channel index */
        [!"$ChannelToCoreNumIndex"!]U
    }[!//
    [!ENDCODE!][!//
[!ENDLOOP!][!//

};[!// End of core mapping

/* Mapping the hardware channel(GTM-TOM) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Pwm_PBcfg_c_REF_2 */
static const uint8 Pwm_HwTomChannelMap[[!"num:i(ecu:get('Gtm.NumberOfTomModules') * ecu:get('Gtm.NumberOfTomChannels'))"!]U] =
{
[!VAR "LastChannel" = "concat(num:i(ecu:get('Gtm.NumberOfTomModules') - 1), num:i(ecu:get('Gtm.NumberOfTomChannels') - 1))"!][!//
[!FOR "ModeleIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfTomModules') - 1)"!][!//
  [!FOR "ChIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfTomChannels') - 1)"!][!//
      [!VAR "CurrentHwChannel" = "concat($ModeleIndex, $ChIndex)"!][!//
      [!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId')"!][!//
        [!VAR "LogicChannelId" = "'0xFF'"!][!//
        [!VAR "TimerType" = "''"!][!//
        [!VAR "Timer" = "''"!][!//
        [!VAR "Channel" = "''"!][!//
        [!CALL "PWM_GetHWTimerIndex", "ChannelRef" = "./PwmChannelSelection"!][!//
        [!IF "$TimerType = 'GTM_OUTPUT_MODULE_TOM'"!][!//
          [!VAR "LogicHwChannel" = "concat($GtmTimerNo, $GtmChannelNo)"!][!//
          [!IF "$CurrentHwChannel = $LogicHwChannel"!][!//
            [!VAR "LogicChannelId" = "./PwmChannelId"!][!//
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

/* Mapping the hardware channel(GTM-ATOM) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Pwm_PBcfg_c_REF_2 */
static const uint8 Pwm_HwAtomChannelMap[[!"num:i(ecu:get('Gtm.NumberOfAtomModules') * ecu:get('Gtm.NumberOfAtomChannels'))"!]U] =
{
[!VAR "LastChannel" = "concat(num:i(ecu:get('Gtm.NumberOfAtomModules') - 1), num:i(ecu:get('Gtm.NumberOfAtomChannels') - 1))"!][!//
[!FOR "ModeleIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfAtomModules') - 1)"!][!//
  [!FOR "ChIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfAtomChannels') - 1)"!][!//
      [!VAR "CurrentHwChannel" = "concat($ModeleIndex, $ChIndex)"!][!//
      [!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId')"!][!//
        [!VAR "LogicChannelId" = "'0xFF'"!][!//
        [!VAR "TimerType" = "''"!][!//
        [!VAR "Timer" = "''"!][!//
        [!VAR "Channel" = "''"!][!//
        [!CALL "PWM_GetHWTimerIndex", "ChannelRef" = "./PwmChannelSelection"!][!//
        [!IF "$TimerType = 'GTM_OUTPUT_MODULE_ATOM'"!][!//
          [!VAR "LogicHwChannel" = "concat($GtmTimerNo, $GtmChannelNo)"!][!//
          [!IF "$CurrentHwChannel = $LogicHwChannel"!][!//
            [!VAR "LogicChannelId" = "./PwmChannelId"!][!//
            [!BREAK!]
          [!ENDIF!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    /* ATOM[!"$ModeleIndex"!]_CH[!"$ChIndex"!] */
    [!IF "$CurrentHwChannel != $LastChannel"!][!//
    [!"$LogicChannelId"!]U,
    [!ELSE!]
    [!"$LogicChannelId"!]U
    [!ENDIF!][!//
  [!ENDFOR!][!//
[!ENDFOR!][!//
};

/* Configuration parameters */
[!IF "variant:name() != ''"!][!//
const Pwm_ConfigType Pwm_ConfigSet_[!"variant:name()"!][1U] =
[!ELSE!][!//
const Pwm_ConfigType Pwm_ConfigSet[1U] =
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
    [!VAR "PwmChannelMappedCoreNum" = "$PwmChannelMappedCore0"!][!//
  [!ELSEIF "$CoreIndex = num:i(1)"!][!//
    [!VAR "PwmChannelMappedCoreNum" = "$PwmChannelMappedCore1"!][!//
  [!ELSEIF "$CoreIndex = num:i(2)"!][!//
    [!VAR "PwmChannelMappedCoreNum" = "$PwmChannelMappedCore2"!][!//
  [!ELSEIF "$CoreIndex = num:i(3)"!][!//
    [!VAR "PwmChannelMappedCoreNum" = "$PwmChannelMappedCore3"!][!//
  [!ELSE!][!//
    [!VAR "PwmChannelMappedCoreNum" = "num:i(0)"!][!//
  [!ENDIF!][!//
    [!/* Add ,  */!][!//
  [!IF "$Cnt0 != num:i(0)"!][!//
  [!CODE!][!//
,
  [!ENDCODE!][!//
  [!ENDIF!][!//
  [!VAR "Cnt0" = "1"!][!//
  [!IF "$PwmChannelMappedCoreNum != num:i(0)"!][!//
            /* PWM channels configuration's pointer of core[!"$CoreIndex"!] */
            &Pwm_CoreConfigCore[!"$CoreIndex"!][!//
  [!ELSE!][!//
            /* PWM channels configuration's pointer of core[!"$CoreIndex"!] */
            NULL_PTR[!//
  [!ENDIF!][!//
[!ENDFOR!][!//
            [!ENDINDENT!][!//

        },
        /* Table for relationship between channel ID in specified core and PWM channel ID */
        &Pwm_ChannelToCoreMap[0U],
        /* Pointer to hardware channel mapping with logic channel */
        {
          [!INDENT "12"!][!//
            /* Pointer to GTM-TOM channel mapping with logic channel */
            &Pwm_HwTomChannelMap[0U],
            /* Pointer to GTM-ATOM channel mapping with logic channel */
            &Pwm_HwAtomChannelMap[0U]
          [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};
/* #Violation: Pwm_PBcfg_c_REF_3 */
#define PWM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Pwm_PBcfg_c_REF_1 */
#include "Pwm_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Pwm_Cfg.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : GTM-TOM, GTM-ATOM
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
[!/* avoid multiple inclusion */!][!// 
[!IF "not(var:defined('PWM_CFG_M'))"!][!// 
[!VAR "PWM_CFG_M"="'true'"!][!// 

[!NOCODE!][!//
[!IF "not(node:exists(as:modconf('Resource')[1]))"!][!//
[!ERROR!][!//
    121-00-00-ERROR: Resource module is not added to the project.
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
** Name           : PWM_GetHWTimerIndex                                       **
**                                                                            **
** Description    : This macro to get the hardware channel index              **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "PWM_GetHWTimerIndex", "ChannelRef" = ""!][!//
    [!IF "node:exists(node:ref($ChannelRef)/GtmAtomChannel)"!][!//
        [!VAR "TimerType" = "'GTM_OUTPUT_MODULE_ATOM'"!][!//
    [!ELSE!][!//
        [!VAR "TimerType" = "'GTM_OUTPUT_MODULE_TOM'"!][!//
    [!ENDIF!][!//
    [!VAR "GtmTimerNo" = "node:ref($ChannelRef)/ModuleId"!][!//
    [!VAR "GtmChannelNo" = "node:ref($ChannelRef)/ChannelId"!][!//
    [!VAR "Timer" = "concat('GTM_PWM_MODULE_INDEX_', $GtmTimerNo)"!][!//
    [!VAR "Channel" = "concat('GTM_PWM_CH_INDEX_', $GtmChannelNo)"!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : Pwm_ConfigurationValidCheck                               **
**                                                                            **
** Description    : This macro to check the configuration vaild.              **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!/* To find the CoreId according to the Pwm channel */!][!//
[!MACRO "Pwm_ConfigurationValidCheck"!][!//
[!SELECT "as:modconf('Pwm')[1]/PwmChannelConfigSet/PwmChannel"!][!//
[!/* To ensure the shift channel has reference channel */!][!//
[!LOOP "node:order(./*, 'PwmChannelId ')"!][!//
    [!IF "node:exists(PwmChannelClass) = 'true' and (./PwmChannelClass = 'PWM_FIXED_PERIOD_SHIFTED' or ./PwmChannelClass = 'PWM_FIXED_PERIOD_CENTER_ALIGNED')"!][!//
        [!/* To check if the  PwmReferenceChannel is vaild */!][!//
        [!IF "node:ref(./PwmReferenceChannel)/PwmChannelClass = 'PWM_FIXED_PERIOD'"!][!//
            [!/* To check the channel order, reference channel id must be less than shift channel */!][!//
            [!VAR "ShiftChannelId" = "./PwmChannelId"!][!//
            [!VAR "ReferenceChannelId" = "node:ref(./PwmReferenceChannel)/PwmChannelId"!][!//
            [!IF "$ShiftChannelId < $ReferenceChannelId"!][!//
                [!//[!ERROR!][!//
                   [!// ERROR: The reference channel id of [!"node:name(.)"!] must be less than [!"node:name(.)"!].
                [!//  [!ENDERROR!][!//
            [!ELSEIF "$ShiftChannelId = $ReferenceChannelId"!][!//
                [!ERROR!][!//
                    121-00-01-ERROR: The reference channel of [!"node:name(.)"!] cannot be itself.
                [!ENDERROR!][!//
            [!ELSE!][!//
                [!/* To check if the both reference channel and shift channel are from the same hardware. */!][!//
                [!VAR "ShiftChannelSelect" = "./PwmChannelSelection"!][!//
                [!VAR "ReferenceChannelIdSelect" = "node:ref(./PwmReferenceChannel)/PwmChannelSelection"!][!//
                [!IF "not((node:exists(node:ref($ShiftChannelSelect)/GtmAtomChannel) and node:exists(node:ref($ReferenceChannelIdSelect)/GtmAtomChannel)) or (node:exists(node:ref($ShiftChannelSelect)/GtmTomChannel) and node:exists(node:ref($ReferenceChannelIdSelect)/GtmTomChannel)))"!][!//
                    [!ERROR!][!//
                        121-00-02-ERROR:  [!"node:name(.)"!], the both reference channel and shift channel must be from the same hardware.
                    [!ENDERROR!][!//
                [!ELSE!][!//From the same hardware
                    [!/* To check the hardware channel order, reference channel index must be less than shift channel */!][!//
                    [!VAR "GtmTimer" = "''"!][!//
                    [!VAR "GtmChannel" = "''"!][!//
                    [!CALL "PWM_GetHWTimerIndex", "ChannelRef" = "./PwmChannelSelection"!][!//
                      [!VAR "ShiftimerNo" = "$GtmTimerNo"!][!//
                      [!VAR "ShiftChannelNo" = "$GtmChannelNo"!][!//
                    [!/* Get the reference channel timer index and channel index. */!]
                    [!SELECT "node:ref(./PwmReferenceChannel)"!][!//
                        [!CALL "PWM_GetHWTimerIndex", "ChannelRef" = "./PwmChannelSelection"!][!//
                        [!VAR "RefTimerNo" = "$GtmTimerNo"!][!//
                        [!VAR "RefChannelNo" = "$GtmChannelNo"!][!//
                    [!ENDSELECT!][!//
                    [!IF "$ShiftimerNo < $RefTimerNo"!]
                        [!ERROR!][!//
                            121-00-03-ERROR: The reference hardware timer module index must be less than the [!"node:name(.)"!].
                        [!ENDERROR!][!//
                    [!ELSEIF "$RefTimerNo = $ShiftimerNo"!][!//
                        [!IF "$RefChannelNo >= $ShiftChannelNo"!]
                            [!IF "$RefTimerNo != 0"!]
                                [!ERROR!][!//
                                    121-00-13-ERROR: The reference hardware channel index must be less than the [!"node:name(.)"!].
                                [!ENDERROR!][!//
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!/* Timer module and channel is valid */!]
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ELSE!][!//
            [!ERROR!][!//
                121-00-04-ERROR: The PwmReferenceChannel of [!"node:name(.)"!] must be the type of PWM_FIXED_PERIOD .
            [!ENDERROR!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "Pwm_ConfigurationValidCheck"!][!// 

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : CG_FindPwmChannelMappedCoreId                             **
**                                                                            **
** Description    : This macro to get the core of channel                     **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!/* To find the CoreId according to the Pwm channel */!][!//
[!MACRO "CG_FindPwmChannelMappedCoreId", "PwmChId" = ""!][!//
    [!VAR "ModuleName" = "'PWM'"!][!//
    [!VAR "PwmchannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "PwmChannelMappedFlag" = "'false'"!][!//
    [!VAR "PwmchannelMappedRequestCoreId" = "num:i(0)"!][!//
    [!VAR "PwmChannelMappedRequestFlag" = "'false'"!][!//
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
                        [!IF "$PwmChId = $Resource_ModuleName"!][!//
                            [!VAR "PwmchannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "PwmChannelMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            121-00-05-ERROR: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$PwmChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the Pwm channel to any core will default allocate to core0 */!][!//
        [!VAR "PwmchannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Find which core used for Pwm channel */!][!//
[!INDENT "0"!][!//
/*******************************************************************************
** Name           : CG_FindTotalNumPwmChannelMappedToCorex                    **
**                                                                            **
** Description    : Find which core used for Pwm channel                      **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "CG_FindTotalNumPwmChannelMappedToCorex"!][!//
    [!VAR "PwmChannelMappedCore0" = "0"!][!//
    [!VAR "PwmChannelMappedCore1" = "0"!][!//
    [!VAR "PwmChannelMappedCore2" = "0"!][!//
    [!VAR "PwmChannelMappedCore3" = "0"!][!//
    [!LOOP "node:order(PwmChannelConfigSet/PwmChannel/*, 'PwmChannelId ')"!][!//
        [!CALL "CG_FindPwmChannelMappedCoreId", "PwmChId"="node:name(.)"!][!//
        [!IF "$PwmchannelMappedCoreId = num:i(0)"!][!//
            [!VAR "PwmChannelMappedCore0" = "$PwmChannelMappedCore0 + 1"!][!//
        [!ELSEIF "$PwmchannelMappedCoreId = num:i(1)"!][!//
            [!VAR "PwmChannelMappedCore1" = "$PwmChannelMappedCore1 + 1"!][!//
        [!ELSEIF "$PwmchannelMappedCoreId = num:i(2)"!][!//
            [!VAR "PwmChannelMappedCore2" = "$PwmChannelMappedCore2 + 1"!][!//
        [!ELSEIF "$PwmchannelMappedCoreId = num:i(3)"!][!//
            [!VAR "PwmChannelMappedCore3" = "$PwmChannelMappedCore3 + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "CG_FindTotalNumPwmChannelMappedToCorex"!][!// 

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : CG_ComputeDutyAndPeriodInTicks                            **
**                                                                            **
** Description    : Compute the duty and period in ticks.                     **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "CG_ComputeDutyAndPeriodInTicks"!][!//  
    [!IF "node:exists(./PwmChannelClass)"!][!//
        [!VAR "ChannelClass" = "./PwmChannelClass"!][!//
    [!ELSE!][!//
        [!VAR "ChannelClass" = "'PWM_FIXED_PERIOD'"!][!//
    [!ENDIF!][!//
    [!VAR "PwmClockRef" = "./PwmMcuClockReferencePoint"!][!//
    [!VAR "McuClockReference" = "node:value(node:ref($PwmClockRef)/McuClockReferenceSelect)"!][!//  
    [!/* Find the Period */!][!//
    [!IF "$ChannelClass = 'PWM_FIXED_PERIOD_SHIFTED' or $ChannelClass = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
        [!VAR "PwmRefChannel" = "./PwmReferenceChannel"!][!//
        [!VAR "ChannelPeriod"= "node:value(node:ref($PwmRefChannel)/PwmPeriodDefault)"!][!//
    [!ELSE!][!//
        [!VAR "ChannelPeriod" = "./PwmPeriodDefault"!][!//
    [!ENDIF!][!//
    [!VAR "PwmMcuClockReferencePointFrequence"= "node:value(node:ref($PwmClockRef)/CmuClockReferencePointFrequency)"!][!//
    [!/* Handle the channel based on GTM-TOM */!][!//
    [!IF "node:exists(node:ref(PwmChannelSelection)/GtmTomChannel)"!][!//
        [!IF "$McuClockReference != 'CMU_FXCLK'"!][!//
            [!ERROR!][!//
                121-00-06-ERROR: Invalid clock source of [!"node:name(.)"!], the reference clock of PWM channel based on TOM must be CMU_FXCLK.
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!/* Find the channel clock source and the frequency based on GTM-TOM */!][!//
        [!IF "./PwmClockSrc = 'CMU_FXCLK0'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUFXCLK0'"!][!//  
        [!ELSEIF "./PwmClockSrc = 'CMU_FXCLK1'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUFXCLK1'"!][!//  
            [!VAR "PwmMcuClockReferencePointFrequence" = "$PwmMcuClockReferencePointFrequence div 16"!][!//
        [!ELSEIF "./PwmClockSrc = 'CMU_FXCLK2'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUFXCLK2'"!][!//  
            [!VAR "PwmMcuClockReferencePointFrequence" = "$PwmMcuClockReferencePointFrequence div 256"!][!//
        [!ELSEIF "./PwmClockSrc = 'CMU_FXCLK3'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUFXCLK3'"!][!//  
            [!VAR "PwmMcuClockReferencePointFrequence" = "$PwmMcuClockReferencePointFrequence div 4096"!][!//
        [!ELSEIF "./PwmClockSrc = 'CMU_FXCLK4'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUFXCLK4'"!][!//  
            [!VAR "PwmMcuClockReferencePointFrequence" = "$PwmMcuClockReferencePointFrequence div 65536"!][!//
        [!ENDIF!][!//
        [!VAR "ChannelPeriodTicks" = "num:i($PwmMcuClockReferencePointFrequence * $ChannelPeriod)"!][!//
        [!IF "$ChannelPeriodTicks > num:i(65535)"!][!//
            [!ERROR!][!//
                121-00-07-ERROR:The channel hardware counter based on the channel clock frequency and PwmPeriodDefault is bigger than 65535. 
            [!ENDERROR!][!//
        [!ENDIF!][!//
    [!ELSE!][!//Handle the channel based on GTM-ATOM
        [!IF "not(contains($McuClockReference, 'CMU_CLK'))"!][!//
            [!ERROR!][!//
                121-00-08-ERROR: Invalid clock source of [!"node:name(.)"!], the reference clock of PWM channel based on ATOM must be CMU_CLK[x], x=0-7.
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!VAR "ChannelPeriodTicks" = "num:i($PwmMcuClockReferencePointFrequence * $ChannelPeriod)"!][!//
        [!IF "$ChannelPeriodTicks > num:i(16777215)"!][!//
            [!ERROR!][!//
                121-00-07-ERROR:The channel hardware counter based on the channel clock frequency and PwmPeriodDefault is bigger than 16777215. 
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!/* Find the channel clock source based on GTM-ATOM */!][!//
        [!IF "$McuClockReference = 'CMU_CLK0'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUCLK0'"!][!//  
        [!ELSEIF "$McuClockReference = 'CMU_CLK1'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUCLK1'"!][!//  
        [!ELSEIF "$McuClockReference = 'CMU_CLK2'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUCLK2'"!][!//  
        [!ELSEIF "$McuClockReference = 'CMU_CLK3'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUCLK3'"!][!//  
        [!ELSEIF "$McuClockReference = 'CMU_CLK4'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUCLK4'"!][!//  
        [!ELSEIF "$McuClockReference = 'CMU_CLK5'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUCLK5'"!][!//  
        [!ELSEIF "$McuClockReference = 'CMU_CLK6'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUCLK6'"!][!//  
        [!ELSEIF "$McuClockReference = 'CMU_CLK7'"!][!//
            [!VAR "ChannelClockSrc" = "'GTM_PWM_CLOCK_CMUCLK7'"!][!//  
        [!ENDIF!][!//
    [!ENDIF!][!//
    [!/* Find the channel duty cycle */!][!//
    [!VAR "ShiftTick" = "as:modconf('Pwm')[1]/PwmGeneral/PwmDutyShiftInTicks"!][!//
    [!IF "$ShiftTick = 'true'"!][!//
        [!VAR "ShiftInticksFlag" = "num:i(1)"!][!//
        [!VAR "ChannelDutyTicks" = "./PwmDutycycleDefault"!][!//
    [!ELSE!][!//
        [!VAR "ShiftInticksFlag" = "num:i(0)"!][!//
        [!VAR "ChannelDutyTicks" = "bit:shr((num:i(./PwmDutycycleDefault) * num:i($ChannelPeriodTicks)),15)"!][!//
    [!ENDIF!][!//
    [!IF "$ChannelPeriodTicks < $ChannelDutyTicks"!][!//
      [!ERROR!][!//
            121-00-12-ERROR:[[!"node:name(.)"!]]: The period is smaller than the duty cycle, please increase the period or decrease the duty cycle.
      [!ENDERROR!][!//
    [!ENDIF!][!//

[!ENDMACRO!][!//
[!ENDINDENT!][!//
[!ENDIF!][!// 

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : PWM_GetHWConfigInfo                                       **
**                                                                            **
** Description    : This macro to get the hardware channel configuration.     **
**                                                                            **
**                                                                            **
*******************************************************************************/
[!MACRO "PWM_GetHWConfigInfo"!][!//
    [!CALL "CG_ComputeDutyAndPeriodInTicks"!][!//  
    [!IF "node:exists(node:ref(./PwmChannelSelection)/GtmAtomChannel)"!][!//
        [!VAR "ChannelMaxCounter" = "num:i(16777215)"!][!//
    [!ELSE!][!// 
        [!VAR "ChannelMaxCounter" = "num:i(65535)"!][!//
    [!ENDIF!][!//  
    [!VAR "PwmDutyCycle" = "num:i($ChannelDutyTicks)"!][!// 
    [!VAR "ChannelPeriod" = "num:i($ChannelPeriodTicks)"!][!// 
    [!/*Find the channel shift value */!][!//
    [!IF "$ChannelClass = 'PWM_FIXED_PERIOD_SHIFTED'"!][!//
        [!VAR "ShiftValue" = "./PwmShiftValue"!][!// 
        [!IF "$ShiftInticksFlag = num:i(0)"!][!//Shift in percent, 0x0000-0x8000  = 0% - 100%
            [!VAR "ShiftValueTick" = "num:i(bit:shr((num:i($ShiftValue) * num:i($ChannelPeriod)),15))"!][!//
        [!ELSE!][!//Shift in ticks
            [!VAR "ShiftValueTick" = "num:i($ShiftValue)"!][!//
        [!ENDIF!][!// 
    [!ELSEIF "$ChannelClass = 'PWM_FIXED_PERIOD_CENTER_ALIGNED'"!][!//
        [!VAR "ShiftValueTick" = "num:i(($ChannelPeriod - $PwmDutyCycle) div num:i(2))"!][!// 
    [!ELSE!][!// 
        [!VAR "ShiftValueTick" = "num:i(0)"!][!// 
    [!ENDIF!][!// 
    [!IF "node:exists(./PwmChannelClass)"!][!//
        [!VAR "ChannelClass" = "./PwmChannelClass"!][!//
    [!ELSE!][!//
        [!VAR "ChannelClass" = "'PWM_FIXED_PERIOD'"!][!//
    [!ENDIF!][!//
    [!VAR "ShiftHandle" = "as:modconf('Pwm')[1]/PwmGeneral/PwmHandleShiftByOffset"!][!//
    [!IF "$ChannelClass = 'PWM_FIXED_PERIOD' or $ChannelClass = 'PWM_VARIABLE_PERIOD'"!][!// Fixed period and varible period
        [!VAR "ChannelResetSource" = "'GTM_PWM_RESETEVENT_ONCM0'"!][!//
        [!VAR "HWDuty" = "num:i($PwmDutyCycle)"!][!//
        [!VAR "HWPeriod" = "num:i($ChannelPeriod)"!][!//
        [!VAR "HWCounterOffset" = "num:i(0)"!][!//
    [!ELSE!][!//
        [!IF "($ShiftHandle = 'false') or ($ChannelClass = 'PWM_FIXED_PERIOD_CENTER_ALIGNED')"!][!//
            [!VAR "ChannelResetSource" = "'GTM_PWM_RESETEVENT_ONTRIGGER'"!][!//
            [!IF "$PwmDutyCycle = num:i(0)"!][!//
                [!VAR "HWDuty" = "num:i(2)"!][!//
                [!VAR "HWPeriod" = "num:i($ChannelMaxCounter)"!][!//
                [!VAR "HWCounterOffset" = "num:i(0)"!][!//
            [!ELSEIF "$PwmDutyCycle = $ChannelPeriod"!]
                [!VAR "HWDuty" = "num:i($ChannelMaxCounter)"!][!//
                [!VAR "HWPeriod" = "num:i(0)"!][!//
                [!VAR "HWCounterOffset" = "num:i(0)"!][!//
            [!ELSE!][!// 
                [!VAR "TempValue" = "(num:i($ShiftValueTick) + $PwmDutyCycle) mod $ChannelPeriod"!][!//
                [!IF "$TempValue < num:i(2)"!][!//
                    [!ERROR!][!//
                        the calculated CM1 is less than 2 and CM0 is greater than CM1 in type PWM_FIXED_PERIOD_CENTER_ALIGNED or PWM_FIXED_PERIOD_SHIFTED , it will lead to waveform abnormalities. GTM ERRATA 517. This issue can be resolved by increasing or decreasing the PwmShiftValue by 2 ticks. node name [!"node:name(.)"!]
                    [!ENDERROR!][!//
                [!ENDIF!][!//
                [!VAR "HWDuty" = "num:i($TempValue)"!][!//
                [!VAR "HWPeriod" = "num:i($ShiftValueTick)"!][!//
                [!VAR "HWCounterOffset" = "num:i(0)"!][!//
            [!ENDIF!][!//
        [!ELSE!][!//Shift by offset
            [!VAR "ChannelResetSource" = "'GTM_PWM_RESETEVENT_ONCM0'"!][!//
            [!IF "$PwmDutyCycle = num:i(0)"!][!//
                [!VAR "HWCounterOffset" = "num:i(0)"!][!//
            [!ELSE!][!// 
                [!VAR "HWCounterOffset" = "num:i(num:i($ChannelPeriod) - num:i($ShiftValueTick))"!][!//
            [!ENDIF!][!// 
            [!VAR "HWDuty" = "$PwmDutyCycle"!][!//
            [!VAR "HWPeriod" = "$ChannelPeriod"!][!//
        [!ENDIF!][!// 
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/*******************************************************************************
** Name           : Pwm_GetWrapperConfigInfo                                  **
**                                                                            **
** Description    : This function is used to get Gtm wrapper configuration    **
**                                                                            **
*******************************************************************************/
[!MACRO "Pwm_GetWrapperConfigInfo", "ModuleName" = "", "ModuleId" = "", "ChannelId" = ""!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Mcu/ELEMENTS/Mcu/GtmConfiguration/*[1]"!][!//
[!IF "$ModuleName = 'Tom'"!][!//
  [!IF "./Tom/*/TomChannel/*[./TomChannelOutput/TomId = num:i($ModuleId) and ./TomChannelOutput/ChannelId  = num:i($ChannelId)]/TomChannelOutput/GTM_Tom_Negative_Support = 'true'"!][!//
    [!VAR "ToutCfg" = "./Tom/*/TomChannel/*[./TomChannelOutput/TomId = num:i($ModuleId) and ./TomChannelOutput/ChannelId  = num:i($ChannelId)]/TomChannelOutput/TomChannelNegativePortPinSelect"!][!//
  [!ELSE!][!//
    [!VAR "ToutCfg" = "./Tom/*/TomChannel/*[./TomChannelOutput/TomId = num:i($ModuleId) and ./TomChannelOutput/ChannelId  = num:i($ChannelId)]/TomChannelOutput/TomChannelPortPinSelect"!][!//
  [!ENDIF!][!//
[!ELSE!][!//
  [!IF "./Atom/*/AtomChannel/*[./AtomChannelOutput/AtomId = num:i($ModuleId) and ./AtomChannelOutput/ChannelId  = num:i($ChannelId)]/AtomChannelOutput/GTM_Atom_Negative_Support = 'true'"!][!//
    [!VAR "ToutCfg" = "./Atom/*/AtomChannel/*[./AtomChannelOutput/AtomId = num:i($ModuleId) and ./AtomChannelOutput/ChannelId  = num:i($ChannelId)]/AtomChannelOutput/AtomChannelNegativePortPinSelect"!][!//
  [!ELSE!][!//
    [!VAR "ToutCfg" = "./Atom/*/AtomChannel/*[./AtomChannelOutput/AtomId = num:i($ModuleId) and ./AtomChannelOutput/ChannelId  = num:i($ChannelId)]/AtomChannelOutput/AtomChannelPortPinSelect"!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!ENDNOCODE!]



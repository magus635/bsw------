[!CODE!][!//
/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Iom_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : This file contains all configurations of IOM Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Iom_PBCfg_c_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Iom_PBCfg_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Iom_PBCfg_c_REF_3:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Iom_PBCfg_c_REF_4:MISRAC2012-Rule-10.5; 
* Justification: Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*/

[!ENDCODE!][!//
[!NOCODE!][!//
[!INCLUDE "Iom.m"!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Iom.h"

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
/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Iom_MemMap.h"
[!SELECT "as:modconf('Iom')"!][!//
[!VAR "ModuleIndex" = "num:i(1)"!][!//
[!VAR "TotalConfig" = "num:i(1)"!][!//
[!VAR "LPUCount" = "num:i(count(IomModuleConfiguration/IomLPUConfiguration/*))"!][!//
[!VAR "GTMCounter" = "1"!][!//
[!VAR "Exor" = "0"!][!//
[!FOR "exorIndex" = "0" TO "7"!][!//
[!VAR "ExorEN" = "concat('IomModuleConfiguration/IomGtmConfiguration/IomGtmInput', $exorIndex)"!][!//
[!VAR "ExorENstr" = "node:value($ExorEN)"!][!//
[!IF "$ExorENstr = 'IOM_ENABLE_GTM_INPUT'"!][!//
[!VAR "Exor" = "num:i($Exor) + num:i($GTMCounter)"!][!//
[!ENDIF!][!//
[!VAR "GTMCounter" = "num:i($GTMCounter) * 2"!][!//
[!ENDFOR!][!//
[!VAR "EMUCounterRecording" = "0"!][!//
[!VAR "FilterTimeMax" = "0"!][!//
[!VAR "FilterTimeMin" = "16777215"!][!//
[!VAR "EventWinTimeMax" = "0"!][!//
[!VAR "EventWinTimeMin" = "16777215"!][!//
/* #Violation: Iom_PBCfg_c_REF_3 */
static const Iom_LpuConfigType Iom_LPUConfiguration[[!"$LPUCount"!]] =
{
[!FOR "LPUIndex" = "0" TO "(num:i($LPUCount)- 1)"!][!//
[!INDENT "4"!][!//
{
[!SELECT "IomModuleConfiguration/IomLPUConfiguration/*[($LPUIndex) + num:i(1)]"!][!//
[!NOCODE!][!//
  [!VAR "LPUInvReferSignalVal" = "./IomLPUInvReferSignal"!][!//
  [!VAR "LPUInvMonSignalVal" = "./IomLPUInvMonSignal"!][!//
  [!VAR "IomLPUEventSrcSelectVal" = "./IomLPUEventSrcSelect"!][!//
  [!VAR "LPURunModeVal" = "./IomLPURunMode"!][!//
  [!VAR "LPUEventWinSelectVal" = "./IomLPUEventWinSelect"!][!//
  [!VAR "LPUInvEventWinVal" = "./IomLPUInvEventWin"!][!//
  [!VAR "LPUEveActEdgeSelVal" = "./IomLPUEveActiveEdgeSelect"!][!//
  [!VAR "LPUEveWinActEdgeSelVal" = "./IomLPUEveWinActiveEdgeSelect"!][!//
  [!VAR "LPUUnitNoVal" = "./IomLPUUnitNo"!][!//
  [!VAR "LPUMonInputSelVal" = "substring-after(./IomLPUMonInputSel,'CH')"!][!//
  [!VAR "LPURefInputSelVal" = "substring-after(./IomLPURefInputSel,'CH')"!][!//
[!ENDNOCODE!][!//
            [!INDENT "8"!][!//
            /* LPU channel [!"$LPUUnitNoVal"!] */ 
            IOM_LPUID_[!"$LPUUnitNoVal"!],
            /* LPU event source and edge triggering configuration */
            {
              [!INDENT "12"!][!//
              [!"./IomLPUEventSrcSelect"!],
              [!"./IomLPUEveActiveEdgeSelect"!]
              [!ENDINDENT!][!//
            },
            /* LPU eventWindow configuration */
            {
              [!INDENT "12"!][!//
              /* LPU eventWindow source */
              [!"./IomLPUEventWinSelect"!],
              /* LPU eventWindow edge triggering */
              [!"./IomLPUEveWinActiveEdgeSelect"!],
              /* LPU eventWindow running mode */
              [!"./IomLPURunMode"!],
              /* Whether to invert the event window */
              [!IF "./IomLPUInvEventWin = 'false'"!][!//
                FALSE,
              [!ELSE!][!//
                TRUE,
              [!ENDIF!][!//
              /* The time the event window lasts */
              [!"./IomLPUEventWinTime"!]U,
              [!IF "num:i($EventWinTimeMax) < num:i(./IomLPUEventWinTime)"!][!//
                [!VAR "EventWinTimeMax" = "num:i(./IomLPUEventWinTime)"!][!//
              [!ENDIF!][!//
              [!IF "num:i($EventWinTimeMin) > num:i(./IomLPUEventWinTime)"!][!//
                [!VAR "EventWinTimeMin" = "num:i(./IomLPUEventWinTime)"!][!//
              [!ENDIF!][!//
              [!ENDINDENT!][!//
            },
            [!IF "node:exists(../../IomPPUConfiguration/*[IomPPUUnitNo = num:i($LPUMonInputSelVal)])"!][!//
            [!SELECT "../../IomPPUConfiguration/*[IomPPUUnitNo = num:i($LPUMonInputSelVal)]"!][!//
            {
                /* LPU Monitor input configuration */
              [!INDENT "12"!][!//
                {
                  [!INDENT "16"!][!//
                  /* Monitor signal prescaler counter threshold */
                  [!"num:i(num:i(./IomPPUPrescalerCompareVal) + 1)"!]U,
                  /* Monitor signal filter mode */
                  (Iom_PpuFilterMode)[!"./IomPPUFilterMode"!],
                  /* Monitor signal filter time */
                  [!"./IomPPUFilterTime"!]U,
                  /* Reset timer or not with delay debounce mode */
                  FALSE
                  [!ENDINDENT!][!//
                },
              /* LPU Monitor signal source */
              (Iom_MonInput)[!"./IomPPUMonInputSel"!],
              /* Whether the LPU Monitor signal inverted */
              [!IF "$LPUInvMonSignalVal = 'false'"!][!//
                FALSE
              [!ELSE!][!//
                TRUE
              [!ENDIF!][!//
              [!ENDINDENT!][!//
            },
            [!ENDSELECT!][!//
            [!ELSE!][!//
                [!ERROR!][!//
                  255-01-01-ERROR: The source of the LPU monitor signal is inconsistent with the PPU.
                [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "node:exists(../../IomPPUConfiguration/*[IomPPUUnitNo = num:i($LPURefInputSelVal)])"!][!//
            [!SELECT "../../IomPPUConfiguration/*[IomPPUUnitNo = num:i($LPURefInputSelVal)]"!][!//
            {
                /* LPU reference input configuration */
              [!INDENT "12"!][!//
                {
                  [!INDENT "16"!][!//
                  /* Reference signal prescaler counter threshold */
                  [!"num:i(num:i(./IomPPUPrescalerCompareVal) + 1)"!]U,
                  /* Reference signal filter mode */
                  (Iom_PpuFilterMode)[!"./IomPPUFilterMode"!],
                  /* Reference signal filter time */
                  [!"./IomPPUFilterTime"!]U,
                  /* Reset timer or not with delay debounce mode */
                  FALSE
                  [!ENDINDENT!][!//
                },
              /* LPU Reference signal source */
              (Iom_RefInput)[!"./IomPPUReferInputSel"!],
              /* XOR usage */
              [!"num:i($Exor)"!]U,
              /* Whether the LPU Monitor signal inverted */
              [!IF "$LPUInvReferSignalVal = 'false'"!][!//
                FALSE
              [!ELSE!][!//
                TRUE
              [!ENDIF!][!//
              [!ENDINDENT!][!//
            },
            [!ENDSELECT!][!//
            [!ELSE!][!//
                [!ERROR!][!//
                  255-01-02-ERROR: The source of the LPU reference signal is inconsistent with the PPU.
                [!ENDERROR!][!//
            [!ENDIF!][!//
            {
              /* EMU configuration */
              [!INDENT "12"!][!//
              /* Which EMU counter is selected for the LPU channel */
                [!"./IomLPUchannelInputEMUSel"!],
              /* EMU counter threshold */
                [!IF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_NOCOUNTER'"!][!//
                  [!VAR "Counter" = "1"!][!//
                  [!IF "./IomLPUUnitNo = 0"!][!//
                    [!VAR "EMUCounterRecording" = "num:i($EMUCounterRecording) + 1"!][!//
                  [!ELSE!][!//
                    [!FOR "EMURecordingIndex" = "1" TO "./IomLPUUnitNo"!][!//
                      [!VAR "Counter" = "num:i($Counter) * 2"!][!//
                    [!ENDFOR!][!//
                    [!VAR "EMUCounterRecording" = "num:i($EMUCounterRecording) + num:i($Counter)"!][!//
                  [!ENDIF!][!//
                [!ELSE!][!//
                  [!VAR "Counter" = "32768"!][!//
                  [!FOR "EMURecordingIndex" = "0" TO "substring-after(substring-after(./IomLPUchannelInputEMUSel,'_'),'_')"!][!//
                    [!VAR "Counter" = "num:i($Counter) * 2"!][!//
                  [!ENDFOR!][!//
                  [!VAR "EMUCounterRecording" = "num:i($EMUCounterRecording) + num:i($Counter)"!][!//
                [!ENDIF!][!//
                [!IF "../../IomEMUConfiguration/IomEventCombModCount/BlockEventOutputRunTime = 'true'"!][!//
                  IOM_EVENTCOUNTERTHRESHOLD_DISABLE
                [!ELSE!][!//
                  [!IF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_NOCOUNTER'"!][!//
                    IOM_EVENTCOUNTERTHRESHOLD_1
                  [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_0'"!][!//
                    [!"../../IomEMUConfiguration/IomEventCombModCount/IomEMUThreshold0"!]
                  [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_1'"!][!//
                    [!"../../IomEMUConfiguration/IomEventCombModCount/IomEMUThreshold1"!]
                  [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_2'"!][!//
                    [!"../../IomEMUConfiguration/IomEventCombModCount/IomEMUThreshold2"!]
                  [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_3'"!][!//
                    [!"../../IomEMUConfiguration/IomEventCombModCount/IomEMUThreshold3"!]
                  [!ENDIF!][!//
                [!ENDIF!][!//
              [!ENDINDENT!][!//
            }
            [!ENDINDENT!][!//
[!ENDSELECT!][!//
        }[!IF "($LPUIndex)!=(num:i($LPUCount)- 1)"!],[!ENDIF!]
[!ENDINDENT!][!//
[!ENDFOR!][!//
}; 

/* #Violation: Iom_PBCfg_c_REF_3 */
static const Iom_EmuCombinerType Iom_EMUCombinerCfg[[!"$LPUCount"!]] =
{
[!FOR "LPUIndex" = "0" TO "(num:i($LPUCount)- 1)"!][!//
[!INDENT "4"!][!//
  {
    [!INDENT "8"!][!//
    [!SELECT "IomModuleConfiguration/IomLPUConfiguration/*[($LPUIndex) + num:i(1)]"!][!//
    [!IF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_NOCOUNTER'"!][!//
      /* #Violation: Iom_PBCfg_c_REF_4 */
      (Iom_EventCounterChannel)0xFF,
    [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_0'"!][!//
      IOM_EVENTCOUNTERCHANNEL_0,
    [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_1'"!][!//
      IOM_EVENTCOUNTERCHANNEL_1,
    [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_2'"!][!//
      IOM_EVENTCOUNTERCHANNEL_2,
    [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_3'"!][!//
      IOM_EVENTCOUNTERCHANNEL_3,
    [!ENDIF!][!//
    IOM_LPUID_[!"num:i(./IomLPUUnitNo)"!],
    [!IF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_NOCOUNTER'"!][!//
      IOM_EVENTCOUNTERTHRESHOLD_DISABLE
    [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_0'"!][!//
      [!"../../IomEMUConfiguration/IomEventCombModCount/IomEMUThreshold0"!]
    [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_1'"!][!//
      [!"../../IomEMUConfiguration/IomEventCombModCount/IomEMUThreshold1"!]
    [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_2'"!][!//
      [!"../../IomEMUConfiguration/IomEventCombModCount/IomEMUThreshold2"!]
    [!ELSEIF "./IomLPUchannelInputEMUSel = 'IOM_EVENTCOUNTERCHANNEL_3'"!][!//
      [!"../../IomEMUConfiguration/IomEventCombModCount/IomEMUThreshold3"!]
    [!ENDIF!][!//
    [!ENDSELECT!][!//
    [!ENDINDENT!][!//
  }[!IF "($LPUIndex)!=(num:i($LPUCount)- 1)"!],[!ENDIF!]
  [!ENDINDENT!][!//
[!ENDFOR!][!//
};
/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Iom_PBCfg_c_REF_2 */
#include "Iom_MemMap.h"

/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Iom_PBCfg_c_REF_2 */
#include "Iom_MemMap.h"
[!IF "variant:name() != ''"!][!//
const Iom_ConfigType Iom_ConfigSet_[!"variant:name()"!][1U] =
[!ELSE!][!//
const Iom_ConfigType Iom_ConfigSet[1U] =
[!ENDIF!][!//
{
    {
        /* LPU channel configuration */
        &Iom_LPUConfiguration[0U],
        /* EMU combined channel logging */
        [!"num:i($EMUCounterRecording)"!]U,
        /* EMU combined channel configuration */
        &Iom_EMUCombinerCfg[0U],
        /* Iom Clock divide factor */
        ([!"IomModuleConfiguration/IomClkConfiguration/IomClkConfiguration"!]U)
    }
};

/* #Violation: Iom_PBCfg_c_REF_1 */
#define IOM_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Iom_PBCfg_c_REF_2 */
#include "Iom_MemMap.h"
[!ENDSELECT!][!//
 
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
  

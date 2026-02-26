
/****************************************************************************************************
*   FileName              : Ocu_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                 : This file contains all post-build parameters in OCU Driver
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
*#Ocu_PBCfg_c_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#Ocu_PBCfg_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Ocu_PBCfg_c_REF_3:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Ocu_PBCfg_c_REF_4:CertC-DCL06-C; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!NOCODE!][!//
[!AUTOSPACING!]
[!INCLUDE "Ocu.m"!][!//
[!ENDNOCODE!][!//
/* SWS_Ocu_00007:
 * Ocu_PBcfg.c shall include Ocu.h */
#include "Ocu.h"
#include "Ocu_GeneralTypes.h"
#include "Ocu_Cfg.h"
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
[!LOOP "node:order(OcuConfigSet/OcuChannel/*, 'OcuChannelId')"!][!//
    [!IF "node:exists(./OcuNotification/*[1])"!][!//
        [!VAR "MCALNotification" = "./OcuNotification/*[1]"!][!//
/* [!"@name"!] notification */
extern void [!"$MCALNotification"!](void);
    [!ENDIF!][!//
[!ENDLOOP!][!//


/****************************************************************************************************
**              Low level driver configurations of the channel based on GTM-ATOM                   **
****************************************************************************************************/
/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"

[!IF "$OCU_HWGtmAtomUsed = 'TRUE'"!][!//
/* The hardware configuration of all logic channel based on GTM-ATOM */
/* #Violation: Ocu_PBCfg_c_REF_3 */
/* #Violation: Ocu_PBCfg_c_REF_4 */
static const Ocu_HWGtmAtomConfigType Ocu_HWGtmAtomChannelsConfig[[!"num:i($OCU_HWGtmAtomNumber)"!]U] = 
{
[!VAR "Cnt0" = "0"!][!//
[!SELECT "as:modconf('Ocu')[1]/OcuConfigSet/OcuChannel"!][!//
[!LOOP "node:order(./*, 'OcuChannelId')"!][!//
  [!VAR "OCU_TimerUsed" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
  [!IF "contains($OCU_TimerUsed, 'GtmAtom')"!][!//
    [!VAR "ClockSelect" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerClockSelect"!][!//
        [!IF "$Cnt0 != num:i(0)"!][!//
        [!CODE!][!//
,
        [!ENDCODE!][!//
        [!ENDIF!][!//
        [!VAR "Cnt0" = "1"!][!//
    /* [!"@name"!] configuration */
    {
        /* The low level interface index */
        {
            [!NOCODE!][!//
            [!CALL "OCU_GetHWTimerIndex", "Channel" = "node:path(.)"!][!//
            [!ENDNOCODE!][!//
            /* Hardware Channel Type */
            (uint8)[!"$TimerModule"!],
            /* Hardware Timer Module Index */
            (uint8)[!"$Timer"!],
            /* Group index, only used for TIO module */
            0U,
            /* Hardware Channel Index */
            (uint8)[!"$Channel"!]
        },
        /* The low level configuration */
        {
            [!NOCODE!][!//
            [!CALL "Ocu_FindOcuHWGtmAtomChannelConfig", "Channel" = "node:path(.)"!][!//
            [!ENDNOCODE!][!//
            /* Clock source */
            [!"$HWClockSrc"!],
            /* Timer base */
            [!"$HWTimeBase"!],
            /* Signal level */
            [!"$HWPinlevel"!],
            {
                /* Somc sl control */
                [!"$HWSomcSL"!],
                /* Somc control */
                [!"$HWSomc"!]
            },
            {
                /* CCU0 interrupt control */
                FALSE,
                /* CCU1 interrupt control */
                FALSE,
                /* Interrupt level mode */
                GTM_IRQMODE_LEVEL
            },
            /* Compare value0 */
            [!"$HWCompareValue0"!]U,
            /* Compare value1 */
            [!"$HWCompareValue1"!]U
        },
        /* Abstract time base */
        [!"$MCALTimeBase"!]
    }[!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//

};
[!ENDIF!][!//

/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"


/****************************************************************************************************
**                               MCAL driver configurations                                        **
****************************************************************************************************/
[!FOR "CoreIndex" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - num:i(1))"!][!//
  [!IF "$CoreIndex = num:i(0) and num:i($OcuChannelMappedCore0) > num:i(0)"!][!//
    [!VAR "OcuChannelMappedCore" = "'true'"!][!//
    [!VAR "OcuChannelMappedCoreNum" = "$OcuChannelMappedCore0"!][!//
  [!ELSEIF "$CoreIndex = num:i(1) and num:i($OcuChannelMappedCore1) > num:i(0)"!][!//
    [!VAR "OcuChannelMappedCore" = "'true'"!][!//
    [!VAR "OcuChannelMappedCoreNum" = "$OcuChannelMappedCore1"!][!//
  [!ELSEIF "$CoreIndex = num:i(2) and num:i($OcuChannelMappedCore2) > num:i(0)"!][!//
    [!VAR "OcuChannelMappedCore" = "'true'"!][!//
    [!VAR "OcuChannelMappedCoreNum" = "$OcuChannelMappedCore2"!][!//
  [!ELSEIF "$CoreIndex = num:i(3) and num:i($OcuChannelMappedCore3) > num:i(0)"!][!//
    [!VAR "OcuChannelMappedCore" = "'true'"!][!//
    [!VAR "OcuChannelMappedCoreNum" = "$OcuChannelMappedCore3"!][!//
  [!ELSE!][!//
    [!VAR "OcuChannelMappedCore" = "'false'"!][!//
    [!VAR "OcuChannelMappedCoreNum" = "num:i(0)"!][!//
  [!ENDIF!][!//
[!IF "$OcuChannelMappedCore = 'true'"!][!//
/****************************************************************************************************
**                                  Core[!"$CoreIndex"!]       configurations                                     **
****************************************************************************************************/
/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"
static const Ocu_ChConfigType Ocu_Core[!"$CoreIndex"!]ChannelConfig[OCU_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
{
[!VAR "Cnt0" = "num:i(0)"!][!//
[!VAR "CntPinsued" = "num:i(0)"!][!//
[!VAR "CntNonPinsued" = "num:i(0)"!][!//
[!SELECT "as:modconf('Ocu')[1]/OcuConfigSet/OcuChannel"!][!//
[!LOOP "node:order(./*, 'OcuChannelId')"!][!//
    [!CALL "CG_FindOcuChannelMappedCoreId", "OcuChId"="node:name(.)"!][!//
    [!IF "$OcuchannelMappedCoreId = num:i($CoreIndex)"!][!//
        [!IF "$Cnt0 != num:i(0)"!][!//
        [!CODE!][!//
,
        [!ENDCODE!][!//
        [!ENDIF!][!//
        [!VAR "Cnt0" = "num:i(1)"!][!//
    /* [!"@name"!] configuration */
    {
    [!NOCODE!][!//
    [!CALL "Ocu_FindOcuChannelConfig", "Channel" = "node:path(.)"!][!//
    [!VAR "EventValue" = "num:i(0)"!][!//
    [!IF "./OcuOuptutPinUsed  = 'true'"!][!//
        [!VAR "EventValue" = "$EventValue + num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "count(./OcuHardwareTriggeredAdc/*) != num:i(0)"!][!//
        [!VAR "EventValue" = "$EventValue + num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "node:exists(./OcuHardwareTriggeredDMA) and count(./OcuHardwareTriggeredDMA/*) != num:i(0)"!][!//
        [!VAR "EventValue" = "$EventValue + num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "$EventValue = num:i(0)"!][!//
        [!ERROR!][!//
        125-00-02-ERROR: Channel[!"$MCALChannelId"!] - The compare matching event of channel includes PIN operation, adc trigger or DMA handle, please select one of them.
        [!ENDERROR!][!//
    [!ELSEIF "$EventValue != num:i(1)"!][!//
        [!ERROR!][!//
        125-00-03-ERROR: Channel[!"$MCALChannelId"!] - The compare matching event of channel can only be one of PIN operation, adc trigger or DMA handle, please just select one of them..
        [!ENDERROR!][!//
    [!ENDIF!][!//
    [!ENDNOCODE!][!//
        /* Channel Id */
        [!"$MCALChannelId"!]U,
        /* Channel Maximum Value  */
        [!"$MCALChannelMaxValue"!]U,
        /* Notification pointer */
        [!IF "node:exists(./OcuNotification/*)"!][!//
            [!VAR "MCALNotification" = "./OcuNotification/*[1]"!][!//
        [!"$MCALNotification"!],
        [!ELSE!][!//
        NULL_PTR,
        [!ENDIF!][!//
        /* Output event class */
        [!"$MCALChMode"!],
        /* Default compare value */
        [!"$MCALChannelDefaultThreshold"!]U,
        /* The hardware class of the logic ocu channel */
        [!"$MCALHWClass"!]
    }[!//
    [!IF "$MCALPinused = 'TRUE'"!][!//
        [!VAR "CntPinsued" = "$CntPinsued + num:i(1)"!][!//
    [!ENDIF!][!//
    [!IF "$MCALPinused = 'FALSE'"!][!//
        [!VAR "CntNonPinsued" = "$CntNonPinsued + num:i(1)"!][!//
    [!ENDIF!][!//
    [!ENDIF!][!//
  [!CALL "OCU_GetHWTimerIndex", "Channel" = "node:path(.)"!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//

};

/* OCU channels configuration of core[!"$CoreIndex"!] */
static const Ocu_CoreConfigType Ocu_CoreConfigCore[!"$CoreIndex"!] =
{
    /* Number of core[!"$CoreIndex"!] maximum channels */
    [!"num:i($OcuChannelMappedCoreNum)"!]U,
    /*Channel configuration*/
    &Ocu_Core[!"$CoreIndex"!]ChannelConfig[0]
};

/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"
[!ENDIF!][!//
[!ENDFOR!][!//


/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"


/* This array is used for mapping Ocu Channel to the Core. */
static const Ocu_MappingType Ocu_ChannelToCoreMap[OCU_MAX_CHANNELS] =
{
[!VAR "Cnt" = "0"!][!//
[!VAR "ChannelToCore0Num" = "0"!][!//
[!VAR "ChannelToCore1Num" = "0"!][!//
[!VAR "ChannelToCore2Num" = "0"!][!//
[!VAR "ChannelToCore3Num" = "0"!][!//
[!VAR "Ocu_GtmAtomIndex" = "-1"!][!//
[!VAR "Ocu_GtmTioIndex" = "-1"!][!//
[!VAR "Ocu_HWMappingIndex" = "0"!][!//
[!SELECT "as:modconf('Ocu')[1]/OcuConfigSet/OcuChannel"!][!//
[!LOOP "node:order(./*, 'OcuChannelId')"!][!//
[!NOCODE!][!//
    [!CALL "CG_FindOcuChannelMappedCoreId", "OcuChId"="node:name(.)"!][!//
    [!IF "$OcuchannelMappedCoreId = num:i(0)"!][!//
          [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore0Num)"!][!//
          [!VAR "ChannelToCore0Num" = "num:i($ChannelToCore0Num) + 1"!][!//
    [!ELSEIF "$OcuchannelMappedCoreId = num:i(1)"!][!//
          [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore1Num)"!][!//
          [!VAR "ChannelToCore1Num" = "num:i($ChannelToCore1Num) + 1"!][!//
    [!ELSEIF "$OcuchannelMappedCoreId = num:i(2)"!][!//
          [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore2Num)"!][!//
          [!VAR "ChannelToCore2Num" = "num:i($ChannelToCore2Num) + 1"!][!//
    [!ELSEIF "$OcuchannelMappedCoreId = num:i(3)"!][!//
          [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore3Num)"!][!//
          [!VAR "ChannelToCore3Num" = "num:i($ChannelToCore3Num) + 1"!][!//
    [!ENDIF!][!//
    [!VAR "ChannelCoreNum" = "concat('MCAL_CORE', $OcuchannelMappedCoreId)"!][!//
    [!/* Compute the hardware configuration index */!][!//
    [!VAR "OCU_TimerUsed" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
    [!VAR "Ocu_GtmAtomIndex" = "$Ocu_GtmAtomIndex + num:i(1)"!][!//
    [!VAR "Ocu_HWMappingIndex" = "$Ocu_GtmAtomIndex"!][!//
[!ENDNOCODE!][!//
    [!CODE!][!//
    [!IF "$Cnt != num:i(0)"!][!//
,
    [!ENDIF!][!//
    [!VAR "Cnt" = "1"!]
    /* [!"@name"!] */
    {
        /* Core number */
        (Mcal_CoreType)[!"$ChannelCoreNum"!], 
        /* Channel Index */
        [!"$ChannelToCoreNumIndex"!]U,
        /* Hardware configuration mapping index */
        [!"num:i($Ocu_HWMappingIndex)"!]U
    }[!//
    [!ENDCODE!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//

};[!// End of core mapping

/* Mapping the hardware channel(GTM-ATOM) index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Ocu_PBCfg_c_REF_3 */
static const uint8 Ocu_HwAtomChannelMap[[!"num:i(ecu:get('Gtm.NumberOfAtomModules') * ecu:get('Gtm.NumberOfAtomChannels'))"!]U] =
{
[!VAR "LastChannel" = "concat(num:i(ecu:get('Gtm.NumberOfAtomModules') - 1), num:i(ecu:get('Gtm.NumberOfAtomChannels') - 1))"!][!//
[!FOR "ModeleIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfAtomModules') - 1)"!][!//
  [!FOR "ChIndex" = "num:i(0)" TO "num:i(ecu:get('Gtm.NumberOfAtomChannels') - 1)"!][!//
      [!VAR "CurrentHwChannel" = "concat($ModeleIndex, $ChIndex)"!][!//
      [!LOOP "node:order(OcuConfigSet/OcuChannel/*, 'OcuChannelId')"!][!//
        [!VAR "LogicChannelId" = "'0xFF'"!][!//
        [!VAR "TimerType" = "''"!][!//
        [!VAR "Timer" = "''"!][!//
        [!VAR "Channel" = "''"!][!//
        [!CALL "OCU_GetATOMIndex", "ChannelRef" = "./GtmTimerOutputModuleConfiguration/*[1]/GtmTimerUsed"!][!//
        [!IF "$TimerType = 'GTM_OUTPUT_MODULE_ATOM'"!][!//
          [!VAR "LogicHwChannel" = "concat($GtmTimerNo, $GtmChannelNo)"!][!//
          [!IF "$CurrentHwChannel = $LogicHwChannel"!][!//
            [!VAR "LogicChannelId" = "./OcuChannelId"!][!//
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
/* #Violation: Ocu_PBCfg_c_REF_3 */
[!IF "variant:name() != ''"!][!//
const Ocu_ConfigType Ocu_ConfigSet_[!"variant:name()"!][1U] =
[!ELSE!][!//
const Ocu_ConfigType Ocu_ConfigSet[1U] =
[!ENDIF!][!//
{
    {
        {
[!VAR "Cnt0" = "num:i(0)"!][!//
[!FOR "CoreIndex" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - num:i(1))"!][!//
[!NOCODE!][!//
  [!IF "$CoreIndex = num:i(0)"!][!//
    [!VAR "OcuChannelMappedCoreNum" = "$OcuChannelMappedCore0"!][!//
  [!ELSEIF "$CoreIndex = num:i(1)"!][!//
    [!VAR "OcuChannelMappedCoreNum" = "$OcuChannelMappedCore1"!][!//
  [!ELSEIF "$CoreIndex = num:i(2)"!][!//
    [!VAR "OcuChannelMappedCoreNum" = "$OcuChannelMappedCore2"!][!//
  [!ELSEIF "$CoreIndex = num:i(3)"!][!//
    [!VAR "OcuChannelMappedCoreNum" = "$OcuChannelMappedCore3"!][!//
  [!ELSE!][!//
    [!VAR "OcuChannelMappedCoreNum" = "num:i(0)"!][!//
  [!ENDIF!][!//
  [!/* Add ,  */!][!//
[!ENDNOCODE!][!//
  [!IF "$Cnt0 != num:i(0)"!][!//
  [!CODE!][!//
,
  [!ENDCODE!][!//
  [!ENDIF!][!//
  [!VAR "Cnt0" = "1"!][!//
  [!IF "$OcuChannelMappedCoreNum != num:i(0)"!][!//
            /* OCU channels configuration's pointer of core[!"$CoreIndex"!] */
            &Ocu_CoreConfigCore[!"$CoreIndex"!][!//
  [!ELSE!][!//
            /* OCU channels configuration's pointer of core[!"$CoreIndex"!] */
            NULL_PTR[!//
  [!ENDIF!][!//
[!ENDFOR!][!//

        },
        /* Table for relationship between channel ID in specified core and OCU channel ID */
        &Ocu_ChannelToCoreMap[0U],
        /* Configuration for hardware channel which is GtmAtom */
        [!IF "$OCU_HWGtmAtomUsed = 'TRUE'"!][!//
        &Ocu_HWGtmAtomChannelsConfig[0U],
        [!ELSE!][!//
        NULL_PTR,
        [!ENDIF!][!//
        /* Pointer to GTM-ATOM channel mapping with logic channel */
        &Ocu_HwAtomChannelMap[0U],
    }
};

/* #Violation: Ocu_PBCfg_c_REF_1*/
#define OCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Ocu_PBCfg_c_REF_2*/
#include "Ocu_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Msc_PBcfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MSC
*
*   brief                 : This file contains all post-build parameters in Msc Driver
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
*#Msc_PBcfg_c_REF_1:MISRAC2012-Rule-11.4; 
* Justification: Casting a pointer to an integral type to obtain its address.
*
*#Msc_PBcfg_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
* driver must be placed.
*
*#Msc_PBcfg_c_REF_3:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*#Msc_PBcfg_c_REF_4:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Msc.m"!][!//
[!ENDNOCODE!][!//
[!CODE!][!//
#include "Msc.h"
#include "Msc_Cfg.h"
#include "Msc_GeneralTypes.h"
#include "Mcall.h"
#include "msc_hal.h"
[!ENDCODE!][!//
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
[!INDENT "0"!][!//
[!VAR "NotificationFlag" = "'false'"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
[!/*Data frame*/!][!//
[!IF "node:exists(./MscTxConfiguration/MscDataFrameConfiguration/MscDataFrameIntService)"!][!//
/* [!"@name"!] Data frame notification function extern */
extern void [!"node:value(./MscTxConfiguration/MscDataFrameConfiguration/MscDataFrameNotification)"!](void);
[!ENDIF!][!//
[!/* Command frame*/!][!//
[!IF "node:exists(./MscTxConfiguration/MscCmdFrameConfiguration/MscCmdFrameIntService)"!][!//
/* [!"@name"!] Command frame notification function extern */
extern void [!"node:value(./MscTxConfiguration/MscCmdFrameConfiguration/MscCmdFrameNotification)"!](void);
[!ENDIF!][!//
[!IF "node:exists(./MscTxConfiguration/MscTimeFrameConfiguration/MscTimeFrameIntService)"!][!//
/* [!"@name"!] Time frame notification function extern */ 
extern void [!"node:value(./MscTxConfiguration/MscTimeFrameConfiguration/MscTimeFrameNotification)"!](void);
[!ENDIF!][!//
[!IF "node:exists(./MscRxConfiguration/MscRxFrameIntService)"!][!//
/* [!"@name"!] Receive data notification function extern */
extern void [!"node:value(./MscRxConfiguration/MscRxFrameNotification)"!](void);
[!ENDIF!][!//
[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigurationOfOptApiServices/Msc_StartRxTimeoutAPI)='true' and 
      node:exists(./MscRxConfiguration/MscTimeoutConfiguration/MscUpTimeoutIntService)"!][!//
/* [!"@name"!] Upstream timeout notification function extern */
extern void [!"node:value(./MscRxConfiguration/MscTimeoutConfiguration/MscUpTimeoutNotification)"!](void);
[!ENDIF!][!//

[!ENDLOOP!][!//

[!ENDINDENT!][!//

/****************************************************************************************************
**                          Configurations                                                         **
****************************************************************************************************/
/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */

[!INDENT "0"!][!//
/* Module configuration: 
 * Including clock, upstream, downstream and interrupt */
/* #Violation: Msc_PBcfg_c_REF_3 */
static const Msc_ModuleConfig Msc_ModuleConfiguration[[!"num:i(count(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*))"!]U] = 
{
[!VAR "Cnt0" = "0"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
    [!IF "$Cnt0 != num:i(0)"!][!//
,
    [!ENDIF!][!//
    [!VAR "Cnt0" = "1"!][!//
    [!INDENT "4"!][!//
    /* [!"@name"!] configuration */
    {
        [!INDENT "8"!][!//
        /* Clock configuration */
        {
[!NOCODE!][!//
[!SELECT "./MscClockConfiguration"!][!//
[!VAR "BaudRate" = "num:i(node:value(MscSerialOutputFrequency))"!][!//
[!VAR "DividerMode" = "node:value(MscClockDividerMode)"!][!//
[!VAR "UpDivider" = "concat('MSC_UPDIV_', num:i(text:split(MscUpstreamDivider, 'MSC_UPDIV_')[last()] * 2))"!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
            [!INDENT "12"!][!//
            /* Baud rate */
            [!"$BaudRate"!]U,
            /* Clock divider mode */
            [!"$DividerMode"!]
            [!ENDINDENT!][!//
        },
        /* Upstream configuration */
        {
[!NOCODE!][!//
[!SELECT "./MscRxConfiguration"!][!//
[!VAR "RxFrameType" = "node:value(MscRxFrameType)"!][!//
[!VAR "ParityMode" = "node:value(MscRxParityType)"!][!//
[!IF "node:exists(MscRxFrameIntService)"!][!//
    [!VAR "ServiceDelay" = "node:value(MscRxIntDelayEnabled)"!][!//
[!ELSE!][!//
    [!VAR "ServiceDelay" = "'MSC_REQDELAY_NODELAY'"!][!//
[!ENDIF!][!//
[!VAR "RxClockSignalType" = "node:value(./MscRxSignalTypeConfiguration/MscRxClockSignalType)"!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
            [!INDENT "12"!][!//
            /* Upstream channel division */
            [!"$UpDivider"!],
            /* Upstream channel frame type */
            [!"$RxFrameType"!],
            /* Parity mode */
            [!"$ParityMode"!],
            /* Service request delay */
            [!"$ServiceDelay"!],
            /* SDI polarity */
            [!"$RxClockSignalType"!]
            [!ENDINDENT!][!//
        },
        /* Downstream configuration */
        {
[!NOCODE!][!//
[!SELECT "./MscTxConfiguration"!][!//
    [!VAR "DataFrameTxMode" = "node:value(MscDataFrameTxMode)"!][!//
    [!VAR "CmdFrameLenNumber" = "node:value(./MscCmdFrameConfiguration/MscCmdFrameLen)"!][!//
    [!VAR "CmdFrameLen" = "concat('MSC_CFLENGTH_',$CmdFrameLenNumber)"!][!//
    [!VAR "DataFrameSrlLenNumber" = "node:value(./MscDataFrameConfiguration/MscDataFrameSrlLen)"!][!//
    [!VAR "DataFrameSrlLen" = "concat('MSC_DFLENGTH_',$DataFrameSrlLenNumber)"!][!//
    [!VAR "DataFrameSrhLenNumber" = "node:value(./MscDataFrameConfiguration/MscDataFrameSrhLen)"!][!//
    [!VAR "DataFrameSrhLen" = "concat('MSC_DFLENGTH_',$DataFrameSrhLenNumber)"!][!//
    [!VAR "PassivePhaseLenNumber" = "node:value(./MscDataFrameConfiguration/MscPassivePhaseLen)"!][!//
    [!VAR "PassivePhaseLen" = "concat('MSC_DFPPL_',$PassivePhaseLenNumber)"!][!//
    [!VAR "SelectionBitHighEnable" = "node:value(./MscDataFrameConfiguration/MscSelectionBitHighEnable)"!][!//
    [!VAR "SelectionBitLowEnable" = "node:value(./MscDataFrameConfiguration/MscSelectionBitLowEnable)"!][!//
    [!VAR "ActivateClock" = "node:value(./MscTxSignalTypeConfiguration/MscActivateClock)"!][!//
    [!VAR "TxChipSelectSignalType" = "node:value(./MscTxSignalTypeConfiguration/MscTxChipSelectSignalType)"!][!//
    [!IF "./MscDataFrameTxMode = 'MSC_TRANSMODE_DATAREPETITION'"!][!//
        [!VAR "PassiveTimeFrameNumberLength" = "node:value(MscPassiveTimeFrameNumber)"!][!//
        [!VAR "PassiveTimeFrameNumber" = "concat('MSC_PTFCOUNT_',$PassiveTimeFrameNumberLength)"!][!//
        [!VAR "CDCMode" = "node:value(MscCDCMode)"!][!//
    [!ELSE!][!//
        [!VAR "PassiveTimeFrameNumber" = "'MSC_PTFCOUNT_0'"!][!//
        [!VAR "CDCMode" = "'MSC_CDCMODE_ENABLED'"!][!//
    [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
            [!INDENT "12"!][!//
            /* Transmission mode */
            [!"$DataFrameTxMode"!],
            /* Command frames length */
            [!"$CmdFrameLen"!],
            /* Data frames srl length */
            [!"$DataFrameSrlLen"!],
            /* Data frames srh length */
            [!"$DataFrameSrhLen"!],
            /* Passive phase length of data frames */
            [!"$PassivePhaseLen"!],
            /* SRL active phase selection bit */
            [!"$SelectionBitLowEnable"!],
            /* SRH active phase selection bit */
            [!"$SelectionBitHighEnable"!],
            /* Clock active phase */
            [!"$ActivateClock"!],
            /* CSLP polarity */
            [!"$TxChipSelectSignalType"!],
            /* Number of passive time frames in data repetition mode */
            [!"$PassiveTimeFrameNumber"!],
            /* Command-data-command in data repetition mode */
            MSC_CDCMODE_DISABLED,
            /* Data source configuration */
            {
[!NOCODE!][!//
[!SELECT "./MscTxConfiguration/MscDataFrameConfiguration/MscDataBitLowConfiguration"!][!//
[!VAR "SrlSourceSelection" = "num:i(0)"!][!//
[!VAR "SrlSourceSelectionTemp" = "num:i(0)"!][!//
[!VAR "SrlBitNumber" = "num:i(count(./*))"!][!//
[!VAR "EmergencyValue" = "num:i(0)"!][!//
[!VAR "SrlEmergency" = "num:i(0)"!][!//
[!VAR "SrhEmergency" = "num:i(0)"!][!//
[!VAR "SrhEmergencyTemp" = "num:i(0)"!][!//
[!VAR "SrlEmergencyTemp" = "num:i(0)"!][!//
[!VAR "SrhEmergencyTemp" = "num:i(0)"!][!//
[!LOOP "./*"!][!//
    [!VAR "DataBitIndex" = "num:i(node:value(./MscDataBitIndex))"!][!//
    [!IF "./MscDataBitSrc = 'SRC_GTMSIGNAL'"!][!//
        [!VAR "SrlSourceSelectionTemp" = "num:i(bit:shl(2,(num:i(2) * $DataBitIndex)))"!][!//
    [!ELSEIF "./MscDataBitSrc = 'SRC_GTMSIGNAL_INVERTED'"!][!//
        [!VAR "SrlSourceSelectionTemp" = "num:i(bit:shl(3,(num:i(2) * $DataBitIndex)))"!][!//
    [!ENDIF!][!//
    [!VAR "SrlSourceSelection" = "num:i(bit:or($SrlSourceSelection, $SrlSourceSelectionTemp))"!][!//
    [!IF "node:exists(MscEmergencyStopEnable) and ./MscEmergencyStopEnable = 'true'"!][!//
        [!VAR "SrlEmergencyTemp" = "num:i(bit:shl(1,$DataBitIndex))"!][!//
    [!ENDIF!][!//
    [!VAR "SrlEmergency" = "num:i(bit:or($SrlEmergency, $SrlEmergencyTemp))"!][!//
[!ENDLOOP!][!//
    [!VAR "SrlSourceSelection" = "num:inttohex($SrlSourceSelection)"!][!//
[!ENDSELECT!][!//
[!SELECT "./MscTxConfiguration/MscDataFrameConfiguration/MscDataBitHighConfiguration"!][!//
[!VAR "SrhSourceSelection" = "num:i(0)"!][!//
[!VAR "SrhSourceSelectionTemp" = "num:i(0)"!][!//
[!VAR "SrhBitNumber" = "num:i(count(./*))"!][!//
[!LOOP "./*"!][!//
    [!VAR "DataBitIndex" = "num:i(node:value(./MscDataBitIndex))"!][!//
    [!IF "./MscDataBitSrc = 'SRC_GTMSIGNAL'"!][!//
        [!VAR "SrhSourceSelectionTemp" = "num:i(bit:shl(2,(num:i(2) * $DataBitIndex)))"!][!//
    [!ELSEIF "./MscDataBitSrc = 'SRC_GTMSIGNAL_INVERTED'"!][!//
        [!VAR "SrhSourceSelectionTemp" = "num:i(bit:shl(3,(num:i(2) * $DataBitIndex)))"!][!//
    [!ENDIF!][!//
    [!VAR "SrhSourceSelection" = "num:i(bit:or($SrhSourceSelection, $SrhSourceSelectionTemp))"!][!//
    [!IF "node:exists(MscEmergencyStopEnable) and ./MscEmergencyStopEnable = 'true'"!][!//
        [!VAR "SrhEmergencyTemp" = "num:i(bit:shl(1,$DataBitIndex))"!][!//
    [!ENDIF!][!//
    [!VAR "SrhEmergency" = "num:i(bit:or($SrhEmergency, $SrhEmergencyTemp))"!][!//
[!ENDLOOP!][!//
    [!VAR "SrhSourceSelection" = "num:inttohex($SrhSourceSelection)"!][!//
    [!VAR "EmergencyValue" = "num:i(bit:or($SrlEmergency, bit:shl($SrhEmergency,16)))"!][!//
    [!VAR "EmergencyValue" = "num:inttohex($EmergencyValue)"!][!//
[!ENDSELECT!][!//
[!/*Pin Injection*/!][!//
[!SELECT "./MscTxConfiguration/MscPinInjectConfiguration"!][!//
    [!IF "node:exists(MscPin0InjectionPos)"!][!//
        [!VAR "Pin0InjectionEnable" = "'MSC_INJEN_ENABLED'"!][!//
        [!VAR "Pin0InjectionPos" = "num:i(MscPin0InjectionPos)"!][!//
    [!ELSE!][!//
        [!VAR "Pin0InjectionEnable" = "'MSC_INJEN_DISABLED'"!][!//    
        [!VAR "Pin0InjectionPos" = "num:i(0)"!][!//
    [!ENDIF!][!//
    [!IF "node:exists(MscPin1InjectionPos)"!][!//
        [!VAR "Pin1InjectionEnable" = "'MSC_INJEN_ENABLED'"!][!//
        [!VAR "Pin1InjectionPos" = "num:i(MscPin1InjectionPos)"!][!//
    [!ELSE!][!//
        [!VAR "Pin1InjectionEnable" = "'MSC_INJEN_DISABLED'"!][!//    
        [!VAR "Pin1InjectionPos" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
                [!INDENT "16"!][!//
                /* SRL data source selection */
                [!"$SrlSourceSelection"!]U,
                /* SRH data source selection */
                [!"$SrhSourceSelection"!]U,
                /* Emergency stop enable bits */
                [!"$EmergencyValue"!]U,
                /* Injection enable pin 0 */
                [!"$Pin0InjectionEnable"!],
                /* Injection position pin 0 */
                MSC_INJPOS_[!"$Pin0InjectionPos"!],
                /* Injection enable pin 1 */
                [!"$Pin1InjectionEnable"!],
                /* Injection position pin 1 */
                MSC_INJPOS_[!"$Pin1InjectionPos"!]
                [!ENDINDENT!][!//
            },
            /* Downstream channel enable control */
            MSC_DOWNSTREAMEN_ENABLED
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!//
    [!ENDINDENT!][!//
[!ENDLOOP!][!//
};
[!ENDINDENT!][!//

/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */



[!FOR "CoreIndex" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - num:i(1))"!][!//
[!NOCODE!][!//
  [!IF "$CoreIndex = num:i(0) and num:i($MscChannelMappedCore0) > num:i(0)"!][!//
    [!VAR "MscChannelMappedCore" = "'true'"!][!//
    [!VAR "MscChannelMappedCoreNum" = "$MscChannelMappedCore0"!][!//
  [!ELSEIF "$CoreIndex = num:i(1) and num:i($MscChannelMappedCore1) > num:i(0)"!][!//
    [!VAR "MscChannelMappedCore" = "'true'"!][!//
    [!VAR "MscChannelMappedCoreNum" = "$MscChannelMappedCore1"!][!//
  [!ELSEIF "$CoreIndex = num:i(2) and num:i($MscChannelMappedCore2) > num:i(0)"!][!//
    [!VAR "MscChannelMappedCore" = "'true'"!][!//
    [!VAR "MscChannelMappedCoreNum" = "$MscChannelMappedCore2"!][!//
  [!ELSEIF "$CoreIndex = num:i(3) and num:i($MscChannelMappedCore3) > num:i(0)"!][!//
    [!VAR "MscChannelMappedCore" = "'true'"!][!//
    [!VAR "MscChannelMappedCoreNum" = "$MscChannelMappedCore3"!][!//
  [!ELSE!][!//
    [!VAR "MscChannelMappedCore" = "'false'"!][!//
    [!VAR "MscChannelMappedCoreNum" = "num:i(0)"!][!//
  [!ENDIF!][!//
[!ENDNOCODE!][!//
[!IF "$MscChannelMappedCore = 'true'"!][!//
/****************************************************************************************************
**                                  Core[!"$CoreIndex"!]       configurations                                     **
****************************************************************************************************/
/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
#include "Msc_MemMap.h"
[!VAR "NotificationFlag" = "num:i(0)"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
    [!CALL "Msc_FindChannelMappedCoreId", "MscChId"="node:name(.)"!][!//
    [!IF "(node:exists(./MscTxConfiguration/MscDataFrameConfiguration/MscDataFrameIntService) or
        node:exists(./MscTxConfiguration/MscCmdFrameConfiguration/MscCmdFrameIntService) or
        node:exists(./MscTxConfiguration/MscTimeFrameConfiguration/MscTimeFrameIntService) or
        node:exists(./MscRxConfiguration/MscRxFrameIntService) or
        node:exists(./MscRxConfiguration/MscRxFrameIntService/MscTimeoutConfiguration/MscUpTimeoutIntService)) and
        $MscChannelMappedCoreId = $CoreIndex"!][!//
        [!VAR "NotificationFlag" = "num:i($NotificationFlag + num:i(1))"!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$NotificationFlag != num:i(0)"!][!//
[!INDENT "0"!][!//
/* Interrupt configuration of core[!"$CoreIndex"!] */
/* #Violation: Msc_PBcfg_c_REF_3 */
static const Msc_IntConfigType Msc_Core[!"$CoreIndex"!]InterruptConfig[[!"$NotificationFlag"!]U] =
{
[!VAR "Cnt0" = "0"!][!//
[!VAR "IntFlag" = "'false'"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
    [!VAR "IntFlag" = "'false'"!][!//
    [!CALL "Msc_FindChannelMappedCoreId", "MscChId"="node:name(.)"!][!//
    [!IF "(node:exists(./MscTxConfiguration/MscDataFrameConfiguration/MscDataFrameIntService) or
        node:exists(./MscTxConfiguration/MscCmdFrameConfiguration/MscCmdFrameIntService) or
        node:exists(./MscTxConfiguration/MscTimeFrameConfiguration/MscTimeFrameIntService) or
        node:exists(./MscRxConfiguration/MscRxFrameIntService) or
        node:exists(./MscRxConfiguration/MscRxFrameIntService/MscTimeoutConfiguration/MscUpTimeoutIntService)) and
        num:i($MscChannelMappedCoreId) = num:i($CoreIndex)"!][!//
    [!IF "$Cnt0 != num:i(0)"!][!//
,
    [!ENDIF!][!//
    [!VAR "Cnt0" = "1"!][!//
    [!INDENT "4"!][!//
    /* [!"@name"!] interrupt configuration */
    {
        [!INDENT "8"!][!//
        {
[!VAR "RxIntType" = "'MSC_RDITYPE_RECEIVE'"!][!//
[!VAR "RxService" = "'MSC_INTRNODE_SR0'"!][!//
[!VAR "TimeFrameService" = "'MSC_INTRNODE_SR0'"!][!//
[!VAR "CmdFrameService" = "'MSC_INTRNODE_SR0'"!][!//
[!VAR "DataFrameService" = "'MSC_INTRNODE_SR0'"!][!//
[!VAR "DataFrameType" = "'MSC_DFINTERRUPT_LASTBIT'"!][!//
[!VAR "TimeoutService" = "'MSC_ALINTRNODE_SR0'"!][!//
[!VAR "IntEnPara" = "''"!][!//
[!NOCODE!][!//
[!SELECT "./MscRxConfiguration"!][!//
[!IF "node:exists(MscRxFrameIntService)"!][!//
    [!VAR "RxIntType" = "node:value(MscRxFrameIntType)"!][!//
    [!VAR "RxService" = "node:value(MscRxFrameIntService)"!][!//
    [!VAR "IntEnPara" = "'MSC_INTR_ENABLE_FLAG_RX'"!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!SELECT "./MscTxConfiguration/MscTimeFrameConfiguration"!][!//
[!IF "node:exists(MscTimeFrameIntService)"!][!//
    [!VAR "TimeFrameService" = "node:value(MscTimeFrameIntService)"!][!//
    [!IF "$IntEnPara != ''"!][!//
      [!VAR "IntEnPara" = "concat($IntEnPara, '|MSC_INTR_ENABLE_FLAG_TF')"!][!//
    [!ELSE!][!//
      [!VAR "IntEnPara" = "'MSC_INTR_ENABLE_FLAG_TF'"!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!SELECT "./MscTxConfiguration/MscCmdFrameConfiguration"!][!//
[!IF "node:exists(MscCmdFrameIntService)"!][!//
    [!VAR "CmdFrameService" = "node:value(MscCmdFrameIntService)"!][!//
    [!IF "$IntEnPara != ''"!][!//
      [!VAR "IntEnPara" = "concat($IntEnPara, '|MSC_INTR_ENABLE_FLAG_CF')"!][!//
    [!ELSE!][!//
      [!VAR "IntEnPara" = "'MSC_INTR_ENABLE_FLAG_CF'"!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!SELECT "./MscTxConfiguration/MscDataFrameConfiguration"!][!//
[!IF "node:exists(MscDataFrameIntService)"!][!//
    [!VAR "DataFrameService" = "node:value(MscDataFrameIntService)"!][!//
    [!VAR "DataFrameType" = "node:value(MscDataFrameIntType)"!][!//
    [!IF "$IntEnPara != ''"!][!//
      [!VAR "IntEnPara" = "concat($IntEnPara, '|MSC_INTR_ENABLE_FLAG_DF')"!][!//
    [!ELSE!][!//
      [!VAR "IntEnPara" = "'MSC_INTR_ENABLE_FLAG_DF'"!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!SELECT "./MscRxConfiguration/MscTimeoutConfiguration"!][!//
[!IF "node:exists(./MscRxConfiguration/MscTimeoutConfiguration/MscUpTimeoutIntService)"!][!//
    [!VAR "TimeoutService" = "node:value(MscUpTimeoutIntService)"!][!//
    [!IF "$IntEnPara != ''"!][!//
      [!VAR "IntEnPara" = "concat($IntEnPara, '|MSC_INTR_ENABLE_FLAG_RX')"!][!//
    [!ELSE!][!//
      [!VAR "IntEnPara" = "'MSC_INTR_ENABLE_FLAG_RX'"!][!//
    [!ENDIF!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
            [!INDENT "12"!][!//
            /* Receive data interrupt type */
            [!"$RxIntType"!],
            /* Receive data interrupt service */
            [!"$RxService"!],
            /* Time frame interrupt service */
            [!"$TimeFrameService"!],
            /* Command frame interrupt service */
            [!"$CmdFrameService"!],
            /* Data frame interrupt service */
            [!"$DataFrameService"!],
            /* Data frame interrupt type */
            [!"$DataFrameType"!]
            [!ENDINDENT!][!//
        },
[!NOCODE!][!//
[!SELECT "./MscTxConfiguration"!][!//
[!/*Command frame*/!][!//
[!IF "node:exists(./MscCmdFrameConfiguration/MscCmdFrameIntService)"!][!//
    [!VAR "CmdFrameNotification" = "node:value(./MscCmdFrameConfiguration/MscCmdFrameNotification)"!][!//
[!ELSE!][!//
    [!VAR "CmdFrameNotification" = "'NULL_PTR'"!][!//
[!ENDIF!][!//
[!/*Time frame*/!][!//
[!IF "node:exists(./MscTimeFrameConfiguration/MscTimeFrameIntService)"!][!//
    [!VAR "TimeFrameNotification" = "node:value(./MscTimeFrameConfiguration/MscTimeFrameNotification)"!][!//
[!ELSE!][!//
    [!VAR "TimeFrameNotification" = "'NULL_PTR'"!][!//
[!ENDIF!][!//
[!/*Data frame*/!][!//
[!IF "node:exists(./MscDataFrameConfiguration/MscDataFrameIntService)"!][!//
    [!VAR "DataFrameNotification" = "node:value(./MscDataFrameConfiguration/MscDataFrameNotification)"!][!//
[!ELSE!][!//
    [!VAR "DataFrameNotification" = "'NULL_PTR'"!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
        /* Interrupt notification function configuration */
        {
            [!INDENT "12"!][!//
            /* Data frame notification function pointer */
            [!"$DataFrameNotification"!],
            /* Command frame notification function pointer */
            [!"$CmdFrameNotification"!],
            /* Time frame notification function pointer */
            [!"$TimeFrameNotification"!],
            /* Receive data notification function pointer */
[!SELECT "./MscRxConfiguration"!][!//
[!IF "node:exists(./MscRxFrameIntService)"!][!//
            [!"node:value(./MscRxFrameNotification)"!]
[!ELSE!][!//
            NULL_PTR
[!ENDIF!][!//
[!ENDSELECT!][!//
            [!ENDINDENT!][!//
        },
        /* Interrupt enable parameter */
        (uint32)([!"$IntEnPara"!])
    [!ENDINDENT!][!//
    }[!//
    [!ENDINDENT!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//

};
[!ENDINDENT!][!//
[!ENDIF!][!//

[!VAR "TimeoutFlag" = "num:i(0)"!][!//
[!IF "/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigurationOfOptApiServices/Msc_StartRxTimeoutAPI = 'true'"!][!//
    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
        [!CALL "Msc_FindChannelMappedCoreId", "MscChId"="node:name(.)"!][!//
        [!SELECT "./MscRxConfiguration"!][!//
        [!IF "node:exists(./MscTimeoutConfiguration) = 'true' and $MscChannelMappedCoreId = $CoreIndex"!][!//
            [!VAR "TimeoutFlag" = "num:i($TimeoutFlag + num:i(1))"!][!//
        [!ENDIF!][!//
        [!ENDSELECT!][!//
    [!ENDLOOP!][!//
[!ENDIF!][!//

[!IF "$TimeoutFlag != num:i(0)"!][!//
[!INDENT "0"!][!//

/* Timeout configuration
    *  TimeutValue = BitTime*2^(MscUpstreamTimeoutPrescalar + 1) * (MscUpstreamTimeoutValue + 1)
    *  TimeutValue:Time of timeout
    *  BitTime:Time it takes to transmit 1 bit, it's equal to (1/Upstream Baud Rate) */
/* #Violation: Msc_PBcfg_c_REF_3 */
static const Msc_TimeoutConfigType Msc_Core[!"$CoreIndex"!]TimeoutConfig[[!"$TimeoutFlag"!]U] = 
{
[!VAR "Cnt0" = "0"!][!//
[!VAR "Index" = "0"!][!//
[!VAR "PrescalarValue" = "1"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
  [!CALL "Msc_FindChannelMappedCoreId", "MscChId"="node:name(.)"!][!//
  [!VAR "ChannelName" = "@name"!][!//
  [!SELECT "./MscRxConfiguration"!][!//
  [!IF "node:exists(./MscTimeoutConfiguration) and $MscChannelMappedCoreId = $CoreIndex"!][!//
    [!VAR "UpstreamTimeoutPrescalar" = "./MscTimeoutConfiguration/MscUpstreamTimeoutPrescalar"!][!//
    [!VAR "UpstreamTimeoutValue" = "./MscTimeoutConfiguration/MscUpstreamTimeoutValue"!][!//
    [!IF "node:exists(MscTimeoutConfiguration/MscUpTimeoutIntService)"!][!//
        [!VAR "TimeoutService" = "node:value(./MscTimeoutConfiguration/MscUpTimeoutIntService)"!][!//
    [!ELSE!][!//
        [!VAR "TimeoutService" = "'MSC_ALINTRNODE_SR0'"!][!//
    [!ENDIF!][!//
    [!FOR "$Index" = "num:i(0)" TO "num:i($UpstreamTimeoutPrescalar)"!][!//
        [!VAR "$PrescalarValue" = "num:i($PrescalarValue*2)"!][!//
    [!ENDFOR!]
    [!IF "$Cnt0 != num:i(0)"!][!//
,
    [!ENDIF!][!//
    [!VAR "Cnt0" = "1"!][!//
    [!INDENT "4"!][!//
    /* [!"$ChannelName"!] timeout configuration */
    {
        [!INDENT "8"!][!//
         /* Current channel timeout value is 
          *  TimeutValue = ([!"num:i(../MscClockConfiguration/MscSerialOutputFrequency)"!]Hz)*2^([!"$UpstreamTimeoutValue"!] + 1) * ([!"$UpstreamTimeoutPrescalar"!] + 1)s
          *              = [!"1000000*(bit:shl(1, ($UpstreamTimeoutValue + 1))) * (($UpstreamTimeoutPrescalar) + 1) div num:i(../MscClockConfiguration/MscSerialOutputFrequency) "!]us
          */
        {
            [!INDENT "12"!][!//
            /* Timeout value(MscUpstreamTimeoutValue) */
            MSC_TIMEOUTVALUE_[!"num:i($UpstreamTimeoutValue+1)"!],
            /* Timeout prescalar(MscUpstreamTimeoutPrescalar) */
            MSC_TIMEOUTPRESCALER_[!"num:i($PrescalarValue)"!],
            /* Timeout service node */
            [!"$TimeoutService"!]
            [!ENDINDENT!][!//
        },
        /* Upstream timeout notification function pointer */
[!IF "node:exists(./MscTimeoutConfiguration/MscUpTimeoutIntService)"!][!//
        [!"./MscTimeoutConfiguration/MscUpTimeoutNotification"!]
[!ELSE!][!//
        NULL_PTR
[!ENDIF!][!//
        [!ENDINDENT!][!//
    }[!//
    [!ENDINDENT!][!//
  [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ENDLOOP!][!//

};
[!ENDINDENT!][!//
[!ENDIF!][!//

[!INDENT "0"!][!//
/* Channel configuration of core[!"$CoreIndex"!] */
static const Msc_ChConfigType Msc_Core[!"$CoreIndex"!]ChannelConfig[MSC_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]] =
{
[!VAR "Cnt" = "0"!][!//
[!VAR "TimeoutCfgIndex" = "-1"!][!//
[!VAR "IntConfigIndex" = "num:i(0)"!][!//
[!VAR "TimeoutConfigIndex" = "'false'"!][!//
[!VAR "NotifFlag" = "'false'"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
    [!VAR "NotifFlag" = "'false'"!][!//
    [!IF "node:exists(./MscTxConfiguration/MscDataFrameConfiguration/MscDataFrameIntService) or
        node:exists(./MscTxConfiguration/MscCmdFrameConfiguration/MscCmdFrameIntService) or
        node:exists(./MscTxConfiguration/MscTimeFrameConfiguration/MscTimeFrameIntService) or
        node:exists(./MscRxConfiguration/MscRxFrameIntService)"!][!//
        [!VAR "NotifFlag" = "'true'"!][!//
    [!ENDIF!][!//
    [!VAR "TimeoutFlag" = "'false'"!][!//
    [!IF "node:exists(./MscRxConfiguration/MscTimeoutConfiguration)"!][!//
        [!VAR "TimeoutCfgIndex" = "$TimeoutCfgIndex + num:i(1)"!][!//
        [!VAR "TimeoutFlag" = "'true'"!][!//
    [!ENDIF!][!//
    [!CALL "Msc_FindChannelMappedCoreId", "MscChId"="node:name(.)"!][!//
        [!IF "$MscChannelMappedCoreId = $CoreIndex"!][!//
        [!IF "$Cnt != num:i(0)"!][!//
,
        [!ENDIF!][!//
        [!VAR "Cnt" = "1"!][!//
        [!INDENT "4"!][!//
        /* [!"@name"!] channel configuration */
        {
            [!INDENT "8"!][!//
            /* Hardware module pointer */
            /* #Violation: Msc_PBcfg_c_REF_1 */
            [!"concat('MSC', text:split(./MscHWUnitMapping, '_')[last()])"!]_HAL,
            /* #Violation: Msc_PBcfg_c_REF_1 */
            /* Module configuration pointer */
            &Msc_ModuleConfiguration[[!"@index"!]U],
            /* Interrupt configuration pointer */
            [!IF "$NotifFlag = 'true'"!][!//
            &Msc_Core[!"$CoreIndex"!]InterruptConfig[[!"$IntConfigIndex"!]U],
            [!VAR "IntConfigIndex" = "num:i($IntConfigIndex + num:i(1))"!][!//
            [!ELSE!][!//
            NULL_PTR,
            [!ENDIF!][!//
            /* Timeout configuration pointer */
            [!IF "/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigurationOfOptApiServices/Msc_StartRxTimeoutAPI = 'true'
                  and $TimeoutFlag = 'true'"!][!//
            &Msc_Core[!"$CoreIndex"!]TimeoutConfig[0U]
            [!ELSE!][!//
            NULL_PTR
            [!ENDIF!][!//          
            [!ENDINDENT!][!//
        }[!//
        [!ENDINDENT!][!//
        [!ENDIF!][!//
[!ENDLOOP!][!//

};
[!ENDINDENT!][!//

/* MSC channels configuration of core[!"$CoreIndex"!] */
static const Msc_CoreConfigType Msc_CoreConfigCore[!"$CoreIndex"!] =
{
    /* Number of core[!"$CoreIndex"!] maximum channels */
    [!"num:i($MscChannelMappedCoreNum)"!]U,
    /* Channel configuration*/
    &Msc_Core[!"$CoreIndex"!]ChannelConfig[0U]
};

#define MSC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */
[!ENDIF!][!//
[!ENDFOR!]

/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */

/* This array is used for mapping Msc Channel to the Core */
[!AUTOSPACING!][!//
static const Msc_MappingType Msc_ChannelToCoreMap[MSC_TOTAL_CHANNEL_NUMBER] =
{
[!VAR "Cnt" = "0"!][!//
[!VAR "ChannelToCore0Num" = "0"!][!//
[!VAR "ChannelToCore1Num" = "0"!][!//
[!VAR "ChannelToCore2Num" = "0"!][!//
[!VAR "ChannelToCore3Num" = "0"!][!//
[!VAR "Msc_GtmNumber" = "-1"!][!//

[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
        [!NOCODE!][!//
        [!CALL "Msc_FindChannelMappedCoreId", "MscChId"="node:name(.)"!][!//
        [!IF "$MscChannelMappedCoreId = num:i(0)"!][!//
             [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore0Num)"!][!//
             [!VAR "ChannelToCore0Num" = "num:i($ChannelToCore0Num) + 1"!][!//
        [!ELSEIF "$MscChannelMappedCoreId = num:i(1)"!][!//
             [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore1Num)"!][!//
             [!VAR "ChannelToCore1Num" = "num:i($ChannelToCore1Num) + 1"!][!//
        [!ELSEIF "$MscChannelMappedCoreId = num:i(2)"!][!//
             [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore2Num)"!][!//
             [!VAR "ChannelToCore2Num" = "num:i($ChannelToCore2Num) + 1"!][!//
        [!ELSEIF "$MscChannelMappedCoreId = num:i(3)"!][!//
             [!VAR "ChannelToCoreNumIndex" = "num:i($ChannelToCore3Num)"!][!//
             [!VAR "ChannelToCore3Num" = "num:i($ChannelToCore3Num) + 1"!][!//
        [!ENDIF!][!//
        [!VAR "ChannelCoreNum" = "concat('MCAL_CORE', $MscChannelMappedCoreId)"!][!//
        [!ENDNOCODE!][!//
        [!CODE!][!//
        [!IF "$Cnt != num:i(0)"!][!//
,
        [!ENDIF!][!//
        [!VAR "Cnt" = "1"!]
    /* [!"@name"!]: No.[!"$ChannelToCoreNumIndex"!] channel of [!"$ChannelCoreNum"!] */
    {
        /* Core number */
        (uint8)[!"$ChannelCoreNum"!], 
        /* Channel index in specific core */
        [!"$ChannelToCoreNumIndex"!]U
    }[!//
       [!ENDCODE!][!//
[!ENDLOOP!][!//

};[!// End of core mapping

/* Mapping the hardware channel index and logic channel index.
 * Index of array is hardware index, the data of the index is logic channel */
/* #Violation: Msc_PBcfg_c_REF_3 */
static const uint8 Msc_HwChannelMap[[!"num:i(ecu:get('Msc.MaxHwUnit'))"!]U] =
{
[!VAR "LastChannel" = "ecu:list('Msc.HwUnitList')[last()]"!][!//
[!VAR "LogicChannelIndex" = "num:i(0)"!][!//
[!FOR "ModeleIndex" = "num:i(0)" TO "num:i(ecu:get('Msc.MaxHwUnit') - 1)"!][!//
  [!VAR "CurrentHwChannel" = "ecu:list('Msc.HwUnitList')[num:i($ModeleIndex+1)]"!][!//
  [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
    [!VAR "LogicChannelId" = "'0xFF'"!][!//
      [!VAR "LogicHwChannel" = "./MscHWUnitMapping"!][!//
        [!IF "$CurrentHwChannel = $LogicHwChannel"!][!//
          [!VAR "LogicChannelId" = "num:i($LogicChannelIndex)"!][!//
          [!VAR "LogicChannelIndex" = "num:i($LogicChannelIndex) + 1"!][!//
          [!BREAK!]
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

/* Configuration parameters for driver to initialize */
[!IF "variant:name() != ''"!][!//
const Msc_ConfigType Msc_ConfigSet_[!"variant:name()"!][1U] =
[!ELSE!][!//
const Msc_ConfigType Msc_ConfigSet[1U] =
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
    [!VAR "MscChannelMappedCoreNum" = "$MscChannelMappedCore0"!][!//
  [!ELSEIF "$CoreIndex = num:i(1)"!][!//
    [!VAR "MscChannelMappedCoreNum" = "$MscChannelMappedCore1"!][!//
  [!ELSEIF "$CoreIndex = num:i(2)"!][!//
    [!VAR "MscChannelMappedCoreNum" = "$MscChannelMappedCore2"!][!//
  [!ELSEIF "$CoreIndex = num:i(3)"!][!//
    [!VAR "MscChannelMappedCoreNum" = "$MscChannelMappedCore3"!][!//
  [!ELSE!][!//
    [!VAR "MscChannelMappedCoreNum" = "num:i(0)"!][!//
  [!ENDIF!][!//
    [!/* Add ,  */!][!//
  [!IF "$Cnt0 != num:i(0)"!][!//
  [!CODE!][!//
,
  [!ENDCODE!][!//
  [!ENDIF!][!//
  [!VAR "Cnt0" = "1"!][!//
  [!IF "$MscChannelMappedCoreNum != num:i(0)"!][!//
            /* MSC channels configuration's pointer of core[!"$CoreIndex"!] */
            &Msc_CoreConfigCore[!"$CoreIndex"!][!//
  [!ELSE!][!//
            /* MSC channels configuration's pointer of core[!"$CoreIndex"!] */
            NULL_PTR[!//
  [!ENDIF!][!//
[!ENDFOR!][!//
            [!ENDINDENT!][!//

        },
        /* Table for relationship between channel ID in specified core and MSC channel ID */
        &Msc_ChannelToCoreMap[0U],
        /* Pointer to MSC hardware channel mapping with logic channel */
        &Msc_HwChannelMap[0U]
        [!ENDINDENT!][!//

    }
    [!ENDINDENT!][!//
};

/* #Violation: Msc_PBcfg_c_REF_4 */
#define MSC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Msc_MemMap.h"
/* #Violation: Msc_PBcfg_c_REF_2 */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

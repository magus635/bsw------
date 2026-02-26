/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Can_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : MCAN
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "ComStack_Types.h"
#include "Can_GeneralTypes.h"
#include "Can_Cfg.h"
#include "Can.h"
/***************************************************************************************************
*                               Local Macros
****************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Can_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
[!/* Call the function of CG_FindTotalNumCanControllerMappedToCorex to count the number of controller map to core*/!][!//
[!CALL "CG_FindTotalNumCanControllerMappedToCorex"!][!//
[!/* Call the function of CG_FindTotalHohNumMappedToCorex to count the number of Hoh map to core*/!][!//
[!CALL "CG_FindTotalHohNumMappedToCorex"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!VAR "ControllerNumMapToCorex" = "num:i(substring-after(text:split($CanControllerMappedToCorex)[num:i($CoreIndex + 1)], ':'))"!][!//
[!IF "num:i($ControllerNumMapToCorex) != num:i(65535)"!][!//
[!VAR "HRHNumMapToCorex" = "num:i(substring-after(text:split($TotalHRHNumToCorex)[num:i($CoreIndex + 1)], ':'))"!][!//
[!VAR "HTHNumMapToCorex" = "num:i(substring-after(text:split($TotalHTHNumToCorex)[num:i($CoreIndex + 1)], ':'))"!][!//
[!VAR "HOHNumMapToCorex" = "num:i(substring-after(text:split($TotalHOHNumToCorex)[num:i($CoreIndex + 1)], ':'))"!][!//
/* Hardware object mapped to Core[!"$CoreIndex"!] */
#define CAN_USED_HRH_MB_MAX_NUM_TO_CORE[!"$CoreIndex"!]             ([!IF "num:i($HRHNumMapToCorex) = num:i(65535)"!]0[!ELSE!][!"num:i($HRHNumMapToCorex + 1)"!][!ENDIF!]U)
#define CAN_USED_HTH_MB_MAX_NUM_TO_CORE[!"$CoreIndex"!]             ([!IF "num:i($HTHNumMapToCorex) = num:i(65535)"!]0[!ELSE!][!"num:i($HTHNumMapToCorex + 1)"!][!ENDIF!]U)
[!ENDIF!][!//
[!ENDFOR!][!//

/***************************************************************************************************
*                               Local Variables
****************************************************************************************************/
[!//
[!VAR "MaxModules" = "num:i(ecu:get('Can.MaxModules'))"!][!//
[!VAR "MaxNodes" = "num:i(ecu:get('Can.MaxNodes'))"!][!//
[!VAR "MaxCore" = "num:i(ecu:get('Mcu.NoOfCoreAvailable'))"!][!//
[!VAR "NoOfSidFilt" = "num:i(0)"!][!//
[!VAR "NoOfXidFilt" = "num:i(0)"!][!//
[!VAR "NoOfTxObj" = "num:i(0)"!][!//
[!VAR "NoOfRxObj" = "num:i(0)"!][!//
[!VAR "NoOfTxPollObj" = "num:i(0)"!][!//
[!VAR "NoOfRxPollObj" = "num:i(0)"!][!//
[!VAR "FDNodesPresent" = "num:i(0)"!][!//
[!VAR "RXFIFO0UsedStatus" = "num:i(0)"!][!//
[!VAR "RXFIFO1UsedStatus" = "num:i(0)"!][!//
[!/* Recording FLSSA of the same Moudle to avoid assigning nodes under the same Moudle to logic failures of different cores*/!][!//
[!VAR "FLSSAToCanModule" = "''"!][!//
[!FOR "ModuleIndex" = "0" TO "num:i(ecu:get('Can.MaxModules') - 1)"!][!//
  [!VAR "BaseRamAddress" = "ecu:get(text:join(concat('Can.MCAN',string($ModuleIndex),'BASERAM')))"!][!//
  [!VAR "FLSSAToCanModule" = "concat($FLSSAToCanModule, $ModuleIndex, ':',text:tolower($BaseRamAddress),' ')"!][!//
[!ENDFOR!][!//
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/***************************************************************************************************
*                               Local Constants
****************************************************************************************************/
#define CAN_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"
[!INDENT "0"!][!//
[!IF "num:i(count(CanConfigSet/CanHardwareObject/*[CanObjectType = 'RECEIVE'])) != 0"!][!//
/***************************************************************************************************
*                        Hardware Filter Configurations
****************************************************************************************************/
static CONST(CanHwFilterType, CAN_CONST) Can_HwFilter_CfgSet[[!"num:i(count(CanConfigSet/CanHardwareObject/*[CanObjectType = 'RECEIVE']))"!]U]=
{
[!VAR "RxFIFOCount" = "num:i(0)"!][!//
[!VAR "LastCfgCntrlId" = "num:i(0)"!][!//
[!VAR "RxDedicatedbuffIndex" = "num:i(0)"!][!//
    [!INDENT "4"!][!//
        [!LOOP "node:order(CanConfigSet/CanHardwareObject/*,'node:value(CanObjectId)')"!][!//
            [!IF "CanObjectType = 'RECEIVE'"!][!//
              [!VAR "HwControllerId" = "num:i(node:ref(./CanControllerRef)/CanControllerId)"!][!//
              [!IF "$LastCfgCntrlId != $HwControllerId"!][!//
                [!VAR "RxFIFOCount" = "num:i(0)"!][!//
              [!ENDIF!][!//
              [!VAR "LastCfgCntrlId" = "num:i($HwControllerId)"!][!//
            /* Controller Descriptor of [!"node:name(.)"!]*/
            {
                [!INDENT "8"!][!//
                    [!IF "CanIdType = 'MIXED' and ./CanHwFilter/CanHwFilterCode != 0 and CanObjectType = 'RECEIVE'"!][!//
                      [!IF "./CanHwFilter/CanHwFilterCode < 262144 or ./CanHwFilter/CanHwFilterCode > 536608768"!][!//
                        [!ERROR!][!//
                        080-00-06-ERROR:The CanHwObjectId[!"node:value(CanObjectId)"!]: 
                        The value of CanHwFilterMask and CanHwFilterCode shall be within range 0x0 and 0x40000 to 0x1FFC0000 value If the CanIdType is MIXED.
                        [!ENDERROR!][!//
                      [!ENDIF!][!//
                    [!ENDIF!][!//
                    CAN_FILTER_ID_TYPE_[!"CanIdType"!],  /* FilterType */
                    [!CALL "CG_CalculateFilternumber", "CanCtrlId"="num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
                    (uint8)[!"num:i($RxStdFilterindex)"!]U,                    /* StandardFilterIndex,invalid when extended frames */
                    (uint8)[!"num:i($RxExtFilterindex)"!]U,                    /* ExtendedFilterIndex,invalid when standard frames */
                    (uint32)[!"num:inttohex(CanHwFilter/CanHwFilterCode)"!]U,               /* CanHwFilterCode */
                    (uint32)[!"num:inttohex(CanHwFilter/CanHwFilterMask)"!]U,               /* CanHwFilterMask */
                    [!IF "CanHwObjectCount = '1'"!][!//
                     (uint8)CAN_FILTERELECFG_STORE_RXBUFFER,
                     (uint8)CAN_FILTERTYPE_CLASSIC,
                     (uint8)CAN_RX_BUFFER[!"num:i($RxBufferOffset)"!],
                    [!ELSE!][!//
                      [!CALL "CG_CalculateRxFifoNumber", "CanCtrlId"="num:i(node:ref(CanControllerRef)/CanControllerId)"!]
                      [!IF "$RxFifoNumber = '0'"!][!//
                        (uint8)CAN_FILTERELECFG_STORE_FIFO0,
                        (uint8)CAN_FILTERTYPE_CLASSIC,
                        (uint8)CAN_RX_FIFO0,
                      [!ELSEIF "$RxFifoNumber = '1'"!][!//
                        (uint8)CAN_FILTERELECFG_STORE_FIFO1,
                        (uint8)CAN_FILTERTYPE_CLASSIC,
                        (uint8)CAN_RX_FIFO1,
                      [!ELSE!][!//
                        [!ERROR!][!//
                        080-00-07-ERROR: More than 2 RxFIFOs,should less than 2.
                        [!ENDERROR!][!//
                      [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDINDENT!][!//
            },
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//
[!INDENT "0"!][!//
/***************************************************************************************************
*                       Hardware Object(s) Configurations
****************************************************************************************************/
/**
 * +---------------------------------------+---------+-------+-----------+
 * |                                       | POLLING | MIXED | INTERRUPT |
 * +---------------------------------------+---------+-------+-----------+
 * | CanHardwareObjectUsesPolling  = TRUE  |   O     |  O    |    X      |
 * | CanHardwareObjectUsesPolling  = FALSE |   O     |  X    |    X      |
 * +---------------------------------------+---------+-------+-----------+
 */
static CONST(Can_HardwareObjectType, CAN_CONST) Can_HardwareObj_MBCfgSet[CAN_USED_HOH_MB_MAX_NUM] =
{
[!INDENT "4"!][!//
    [!VAR "HwFilterPtrCount" = "num:i(0)"!][!//
    [!LOOP "node:order(CanConfigSet/CanHardwareObject/*,'node:value(CanObjectId)')"!][!//
    /*[!"node:name(.)"!]*/
    {
        [!INDENT "8"!][!//
            (Can_HandleType)[!"CanHandleType"!]_CAN,   /*HandleType*/
        [!IF "node:exists(CanHwObjectCount)"!][!//
            (uint16)[!"num:i(CanHwObjectCount)"!]U,                 /*CanHwObjectCount*/
        [!ELSE!][!//
            (uint16)1U,
        [!ENDIF!][!//
        [!IF "node:exists(CanHwFIFOThreshold)"!][!//
          (uint16)[!"num:i(CanHwFIFOThreshold)"!]U,                 /*CanHwFIFOThreshold*/
        [!ELSE!][!//
          (uint16)1U,
        [!ENDIF!][!//
          CANID_TYPE_[!"CanIdType"!],        /*CanFrameIdType*/
          (uint16)[!"num:i(CanObjectId)"!]U,                 /*Hardware Object ID*/
          (Can_ObjectType)CAN_[!"CanObjectType"!],/*Object_Type*/
        [!IF "num:i(count(//CanConfigSet/CanHardwareObject/*[CanTriggerTransmitEnable = 'true'])) > 0"!][!//
            (boolean)[!IF "CanTriggerTransmitEnable = 'true'"!]TRUE,[!ELSE!]FALSE,[!ENDIF!] /*CanTriggerTransmitEnable*/
        [!ENDIF!][!//
        [!IF "CanObjectType = 'RECEIVE'"!]
            [!IF "node:ref(CanControllerRef)/CanRxProcessing = 'INTERRUPT'"!]
              (boolean)FALSE,[!WS "13"!]/*Porcessing:[!"node:value(node:ref(CanControllerRef)/CanRxProcessing)"!]*/
            [!ELSEIF "node:ref(CanControllerRef)/CanRxProcessing = 'POLLING'"!][!//
              (boolean)TRUE,[!WS "13"!]/*Porcessing:[!"node:value(node:ref(CanControllerRef)/CanRxProcessing)"!]*/
            [!ELSE!][!//
              (boolean)[!IF "CanHardwareObjectUsesPolling = 'true'"!]TRUE,[!ELSE!]FALSE,[!ENDIF!][!WS "13"!]/*Porcessing:[!"node:value(node:ref(CanControllerRef)/CanRxProcessing)"!]*/
            [!ENDIF!]
        [!ELSE!][!//
            [!IF "node:ref(CanControllerRef)/CanTxProcessing = 'INTERRUPT'"!]
              (boolean)FALSE,[!WS "13"!]/*Porcessing:[!"node:value(node:ref(CanControllerRef)/CanTxProcessing)"!]*/
            [!ELSEIF "node:ref(CanControllerRef)/CanTxProcessing = 'POLLING'"!][!//
              (boolean)TRUE,[!WS "13"!]/*Porcessing:[!"node:value(node:ref(CanControllerRef)/CanTxProcessing)"!]*/
            [!ELSE!][!//
              (boolean)[!IF "CanHardwareObjectUsesPolling = 'true'"!]TRUE,[!ELSE!]FALSE,[!ENDIF!][!WS "13"!]/*Porcessing:[!"node:value(node:ref(CanControllerRef)/CanTxProcessing)"!]*/
            [!ENDIF!]
        [!ENDIF!]
        [!SELECT "node:ref(CanControllerRef)"!][!//
            [!IF "(node:exists(CanFDSupport)) and (CanFDSupport = 'true')"!][!//
                [!VAR "CanFD_Enabled" = "1"!][!//
            [!ELSE!][!//
                [!VAR "CanFD_Enabled" = "0"!][!//
            [!ENDIF!][!//
            (uint8)[!"num:i(CanControllerId)"!]U,                  /* ControllerId - based on the order from CanController list */
        [!ENDSELECT!][!//
        [!IF "(num:i(count(../../CanController/*[CanFDSupport ='true'])) > 0)"!][!//
            [!IF "node:exists(CanFdPaddingValue)"!][!//
                (boolean)TRUE,             /*FdPaddingEnable Only Enable in Tx MB*/
                (uint8)[!"num:inttohex(CanFdPaddingValue)"!]U,               /*CanFdPaddingValue*/
            [!ELSE!][!//
                (boolean)FALSE,             /*FdPaddingEnable Only Enable in Tx MB*/
                (uint8)0xFFU,               /*Invalid CanFdPaddingValue*/
            [!ENDIF!][!//
        [!ENDIF!][!//        
        [!IF "node:refexists(CanMainFunctionRWPeriodRef)"!][!//
            [!SELECT "node:ref(CanMainFunctionRWPeriodRef)"!][!//
                (uint8)[!"@index"!]U,                  /* CanMainFuncRWPeriodRef handle reference is from [!"node:name(.)"!] */
            [!ENDSELECT!][!//
        [!ELSE!][!//
            (uint8)0U,                  /* CanMainFuncRWPeriodRef handle configured for INTERRUPT mode, reference not used */
        [!ENDIF!][!//
        [!INDENT "8"!][!//
        [!IF "CanObjectType = 'TRANSMIT'"!][!//
          NULL_PTR,    /* HwFilterPtr */
          [!IF "CanHwObjectCount = '1'"!][!//
            [!CALL "CG_CalculateDedicatedBuffElementIndex", "CanCtrlId"="num:i(node:ref(CanControllerRef)/CanControllerId)"!]
            [!"num:i($TxDedicatedBuffIndex)"!]U,                 /* Tx Buffer Elements Index */
            (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
          [!ELSE!][!//
            [!CALL "CG_CalculateTxFifoElementIndex", "CanCtrlId"="num:i(node:ref(CanControllerRef)/CanControllerId)"!]
            [!"num:i($TxFiFoQueueElementIndex)"!]U,                 /* Tx Queue Elements Index,In case of mixed configurations where dedicated Tx Buffers are combined with a Tx FIFO
                                                                      or a Tx Queue, the Put and Get Indices indicate the number of the Tx Buffer starting with the first dedicated Tx Buffers. */
            (Can_MsgRamType)CAN_MSG_QUEUE, /* MsgRamType */
          [!ENDIF!][!//
        [!ELSEIF "CanObjectType = 'RECEIVE'"!][!//
          &Can_HwFilter_CfgSet[[!"num:i($HwFilterPtrCount)"!]],    /* HwFilterPtr */
          [!VAR "HwFilterPtrCount" = "num:i($HwFilterPtrCount + 1)"!][!//
          [!IF "CanHwObjectCount = '1'"!][!//
            [!CALL "CG_CalculateDedicatedBuffElementIndex", "CanCtrlId"="num:i(node:ref(CanControllerRef)/CanControllerId)"!]
            [!"num:i($RxDedicatedBuffIndex)"!]U,                         /* Rx Buffer Elements Index */
            (Can_MsgRamType)CAN_MSG_DED_BUFFER, /* MsgRamType */
          [!ELSE!][!//
            [!CALL "CG_CalculateRxFifoNumber", "CanCtrlId"="num:i(node:ref(CanControllerRef)/CanControllerId)"!]
            [!IF "$RxFifoNumber = '0'"!][!//
              0U, /* RxFIFO0 Elements Index,The starting Elements Index of each Controller's RxFIFO must be 0 */
              (Can_MsgRamType)CAN_MSG_FIFO0, /* MsgRamType */
            [!ELSE!][!//
              0U, /* RxFIFO1 Elements Index,The starting Elements Index of each Controller's RxFIFO must be 0 */
              (Can_MsgRamType)CAN_MSG_FIFO1, /* MsgRamType */  
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ELSEIF "CanObjectType != 'RECEIVE' and CanObjectType != 'TRANSMIT'"!][!//
          [!ERROR!][!//
            080-00-08-ERROR: The CanObjectType shall be configured with 'RECEIVE' or 'TRANSMIT'.
          [!ENDERROR!][!//        
        [!ENDIF!][!//
        [!ENDINDENT!][!//
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
[!ENDINDENT!][!//
};
[!ENDINDENT!][!//
#define CAN_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"
[!/* Call the function of CG_FindTotalNumCanControllerMappedToCorex to count the number of controller map to core*/!][!//
[!CALL "CG_FindTotalNumCanControllerMappedToCorex"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores')) - 1"!][!//
[!INDENT "0"!][!//
/***************************************************************************************************
*                       CAN CONTROLLER(s) OF CORE[!"$CoreIndex"!] CONFIGURATIONS START
****************************************************************************************************/
[!/* Get the total number of resources corresponding to the current CoreId in CanControllerMappedToCorex */!][!//
[!VAR "ControllerNumMapToCorex" = "num:i(substring-after(text:split($CanControllerMappedToCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
[!IF "num:i($ControllerNumMapToCorex) != num:i(65535)"!][!//
#define CAN_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
#include "Can_MemMap.h"
[!INDENT "0"!][!//
/***************************************************************************************************
*                       HardwareObject Mapping List
****************************************************************************************************/
static const Can_HwHandleType Can_HohToCfgSetCore[!"$CoreIndex"!][CAN_USED_HOH_MB_MAX_NUM_TO_CORE[!"$CoreIndex"!]] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(CanConfigSet/CanHardwareObject/*, './CanObjectId')"!][!//
        [!CALL "CG_FindCanHardwareObjectIdMappedCoreId", "CanHwObjName"="node:name(.)"!][!//
        [!IF "$CanHardwareObjectIdMappedCoreId = num:i($CoreIndex)"!][!//
            [!"./CanObjectId"!]U,     /* The index of HardwareObject[!"node:value(CanObjectId)"!](assigned to Core[!"$CoreIndex"!]) in HardwareObject list */
        [!ENDIF!][!//
    [!ENDLOOP!][!// 
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!LOOP "node:order(CanConfigSet/CanController/*,'node:value(./CanControllerId)')"!][!//
    [!VAR "ControllerId" = "num:i(./CanControllerId)"!][!//
    [!VAR "RxBufferCount" = "num:i(0)"!][!//
    [!VAR "RxFIFOCount" = "num:i(0)"!][!//
    [!VAR "TxBufferAndFIFOCount" = "num:i(0)"!][!//
    [!CALL "CG_FindCanControllerMappedCoreId", "CanControllerName"="node:name(.)"!][!//
    [!IF "$CanControllerMappedCoreId = num:i($CoreIndex)"!][!//
        [!LOOP "node:order(../../CanHardwareObject/*,'node:value(node:ref(./CanControllerRef)/CanControllerId)')"!][!//
            [!VAR "CurrentControllerId" = "node:value(node:ref(./CanControllerRef)/CanControllerId)"!][!//
            [!IF "$ControllerId = $CurrentControllerId and ./CanObjectType = 'RECEIVE' and ./CanHwObjectCount = num:i(1)"!][!//
                [!VAR "RxBufferCount" = "num:i($RxBufferCount + 1)"!][!//
            [!ENDIF!][!//
            [!IF "$ControllerId = $CurrentControllerId and ./CanObjectType = 'RECEIVE' and ./CanHwObjectCount > num:i(1)"!][!//
                [!VAR "RxFIFOCount" = "num:i($RxFIFOCount + 1)"!][!//
            [!ENDIF!][!//
            [!IF "$ControllerId = $CurrentControllerId and ./CanObjectType = 'TRANSMIT'"!][!//
                [!VAR "TxBufferAndFIFOCount" = "num:i($TxBufferAndFIFOCount + 1)"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$RxBufferCount != num:i(0)"!][!//
            static const uint8 Can_RxBufferIndexToHwObjectId[!"$ControllerId"!][[!"$RxBufferCount"!]U]=
            {
                [!INDENT "4"!][!//
                [!VAR "LoopCount" = "num:i(0)"!][!//
                [!LOOP "node:order(../../CanHardwareObject/*,'./CanObjectId')"!][!//
                    [!VAR "CurrentControllerId" = "node:value(node:ref(./CanControllerRef)/CanControllerId)"!][!//
                    [!IF "$ControllerId = $CurrentControllerId and ./CanObjectType = 'RECEIVE' and ./CanHwObjectCount = num:i(1)"!][!//
                        [!VAR "LoopCount" = "num:i($LoopCount + 1)"!][!//
                        [!"num:i(./CanObjectId)"!]U[!IF "$LoopCount != $RxBufferCount"!],[!ELSE!][!WS!][!ENDIF!]    /* The index of HardwareObject[!"node:value(CanObjectId)"!] with dedicated buffer (assigned to Core[!"$CoreIndex"!] Controller[!"$ControllerId"!]) in HardwareObject list */
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!ENDINDENT!][!//
            };
        [!ENDIF!][!//
        [!IF "$RxFIFOCount != num:i(0)"!][!//
            static const uint8 Can_RxFifoIndexToHwObjectId[!"$ControllerId"!][[!"$RxFIFOCount"!]U]=
            {
                [!INDENT "4"!][!//
                [!VAR "LoopCount" = "num:i(0)"!][!//
                [!LOOP "node:order(../../CanHardwareObject/*,'./CanObjectId')"!][!//
                    [!VAR "CurrentControllerId" = "node:value(node:ref(./CanControllerRef)/CanControllerId)"!][!//
                    [!IF "$ControllerId = $CurrentControllerId and ./CanObjectType = 'RECEIVE' and ./CanHwObjectCount > num:i(1)"!][!//
                        [!VAR "LoopCount" = "num:i($LoopCount + 1)"!][!//
                        [!"num:i(./CanObjectId)"!]U[!IF "$LoopCount != $RxFIFOCount"!],[!ELSE!][!WS!][!ENDIF!]    /* The index of HardwareObject[!"node:value(CanObjectId)"!] with FIFO (assigned to Core[!"$CoreIndex"!] Controller[!"$ControllerId"!]) in HardwareObject list */
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!ENDINDENT!][!//
            };
        [!ENDIF!][!//
        [!IF "$TxBufferAndFIFOCount != num:i(0)"!][!//
            static const uint8 CanTxBufferAndFIFOIndexToHwObjectId[!"$ControllerId"!][[!"$TxBufferAndFIFOCount"!]U]=
            {
                [!INDENT "4"!][!//
                [!VAR "LoopCount" = "num:i(0)"!][!//
                [!LOOP "node:order(../../CanHardwareObject/*,'./CanObjectId')"!][!//
                    [!VAR "CurrentControllerId" = "node:value(node:ref(./CanControllerRef)/CanControllerId)"!][!//
                    [!IF "$ControllerId = $CurrentControllerId and ./CanObjectType = 'TRANSMIT'"!][!//
                        [!VAR "LoopCount" = "num:i($LoopCount + 1)"!][!//
                        [!"num:i(./CanObjectId)"!]U[!IF "$LoopCount != $TxBufferAndFIFOCount"!],[!ELSE!][!WS!][!ENDIF!]    /* The index of HardwareObject[!"node:value(CanObjectId)"!] with buffer and FIFO (assigned to Core[!"$CoreIndex"!] Controller[!"$ControllerId"!]) in HardwareObject list */
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!ENDINDENT!][!//
            };
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "node:order(CanConfigSet/CanController/*,'node:value(CanControllerId)')"!][!//
[!CALL "CG_FindCanControllerMappedCoreId", "CanControllerName"="node:name(.)"!][!//
[!IF "$CanControllerMappedCoreId = num:i($CoreIndex)"!][!//
[!INDENT "0"!][!//
[!IF "(node:exists(CanFDSupport) and (CanFDSupport ='true')) and ((num:i(count(./CanControllerBaudrateConfig/*/CanControllerFdBaudrateConfig))) != '0')"!][!//
/***************************************************************************************************
*                        [!"CanHardwareChannel"!] CanFD Baudrate Configurations
****************************************************************************************************/
static CONST(Can_ControllerFdBaudrateType, CAN_CONST) Can_FDBaudrateCfgSet_Controller[!"CanControllerId"!][[!"num:i(count(./CanControllerBaudrateConfig/*/CanControllerFdBaudrateConfig))"!]U]=
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(CanControllerBaudrateConfig/*,'node:value(CanControllerBaudRateConfigID)')"!][!//
    [!IF "node:exists(CanControllerFdBaudrateConfig)"!][!//
    {
        [!INDENT "8"!][!//
        [!SELECT "CanControllerFdBaudrateConfig"!][!//
        [!IF "(CanControllerTxBitRateSwitch ='true')"!][!//
        (boolean)TRUE, /*CanControllerTxBitRateSwitch*/
        [!ELSE!][!//
        (boolean)FALSE,/*CanControllerTxBitRateSwitch*/
        [!ENDIF!][!//
          (uint16)[!"num:i(CanControllerFdBaudRate)"!]U, /*ControllerFdBaudRate in kbps*/
        {
          [!INDENT "12"!][!//
          (uint32)[!"num:i(CanControllerSyncJumpWidth)"!]U, /*ControllerSyncJumpWidth*/
          (uint32)[!"num:i(CanControllerFdBaudRatePRESDIV)"!]U, /*ControllerFdBaudRatePRESDIV*/
          (uint32)[!"num:i(CanControllerPropSeg + CanControllerSeg1)"!]U, /*ControllerPropSeg+ControllerSeg1*/
          (uint32)[!"num:i(CanControllerSeg2)"!]U, /*ControllerSeg2*/
          [!ENDINDENT!][!//
        [!IF "node:exists(CanControllerSspOffset)"!][!//
          [!INDENT "12"!][!//
          (uint8)[!"num:i(CanControllerSspOffset)"!], /*CanControllerSspOffset*/
          (uint8)0U, /*compFilterWindow*/
          [!ENDINDENT!][!//
        },
        (boolean)TRUE,/*CanControllerSspOffset*/
        [!ELSE!][!//
          [!INDENT "12"!][!//
          (uint8)0U, /*CanControllerSspOffset*/
          (uint8)0U, /*compFilterWindow*/
          [!ENDINDENT!][!//
        },
        (boolean)FALSE, /*CanControllerSspOffset*/                        
        [!ENDIF!][!//
        [!ENDSELECT!][!//
        [!ENDINDENT!][!//
    },
    [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!LOOP "node:order(CanConfigSet/CanController/*,'node:value(CanControllerId)')"!][!//
[!CALL "CG_FindCanControllerMappedCoreId", "CanControllerName"="node:name(.)"!][!//
[!IF "$CanControllerMappedCoreId = num:i($CoreIndex)"!][!//
[!INDENT "0"!][!//
/***************************************************************************************************
*                        [!"CanHardwareChannel"!] Can Baudrate Configurations
****************************************************************************************************/
static CONST(Can_ControllerBaudrateType, CAN_CONST) Can_BaudrateCfgSet_Controller[!"CanControllerId"!][[!"num:i(count(./CanControllerBaudrateConfig/*))"!]U]=
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(CanControllerBaudrateConfig/*,'node:value(CanControllerBaudRateConfigID)')"!][!//
    {
        [!INDENT "8"!][!//
            (uint16)[!"num:i(CanControllerBaudRate)"!]U, /*ControllerBaudRate in kbps*/
        [!IF "node:exists(//CanGeneral/CanSetBaudrateApi) and (//CanGeneral/CanSetBaudrateApi ='true')"!][!//
            [!IF "node:value(./CanControllerBaudRateConfigID) >= num:i(count(../*))"!][!//
                [!ERROR!][!//
                    080-00-19-ERROR: CanControllerBaudRateConfigID should start from 0 and be numbered consecutively, in CanControllerId = [!"node:value(../../CanControllerId)"!][!//
                [!ENDERROR!][!//
            [!ENDIF!][!//
            (uint16)[!"num:i(CanControllerBaudRateConfigID)"!]U, /*ControllerBaudRateConfigID */
        [!ENDIF!][!//
        {
            [!INDENT "12"!][!//
            (uint16)[!"num:i(CanControllerSyncJumpWidth)"!]U, /*ControllerSyncJumpWidth*/
            (uint16)[!"num:i(CanControllerPRESDIV)"!]U, /*ControllerPRESDIV*/
            (uint8)[!"num:i(CanControllerPropSeg+CanControllerSeg1)"!]U, /*CanControllerPropSeg+CanControllerSeg1*/
            (uint8)[!"num:i(CanControllerSeg2)"!]U, /*ControllerSeg2*/
            [!ENDINDENT!][!//
        },
        [!IF "$CanFD_Controller_Supported = 1"!][!//
            [!IF "(node:exists(../../CanFDSupport) and (../../CanFDSupport ='true')) and (node:exists(CanControllerFdBaudrateConfig))"!][!//
                &Can_FDBaudrateCfgSet_Controller[!"../../CanControllerId"!][[!"CanControllerBaudRateConfigID"!]] /*ControllerFdDefaultConfig*/
            [!ELSE!][!//
                NULL_PTR /*ControllerFdDefaultConfig*/
            [!ENDIF!][!//
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    },
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
/***************************************************************************************************
*                        Message RAM Configurations
****************************************************************************************************/
static CONST(Can_ControllerMsgRAMConfigType, CAN_CONST) Can_ControllerMsgRAMMapConfigCore[!"$CoreIndex"!][CAN_USED_CONTROLLER_MAX_NUM_TO_CORE[!"$CoreIndex"!]]=
{
[!VAR "IndexCnt" = "num:i(0)"!][!//
[!VAR "FirstNodeInModule" = "num:i(0)"!][!//
[!VAR "ControllerChannelToIdMap" = "''"!][!//
[!/* Traverse each controller */!][!//
[!LOOP "node:order(CanConfigSet/CanController/*, 'node:value(./CanHardwareChannel)')"!][!//
    [!CALL "CG_FindCanControllerMappedCoreId", "CanControllerName"="node:name(.)"!][!//
    [!IF "$CanControllerMappedCoreId = num:i($CoreIndex)"!][!//
        [!VAR "NoOfTxDedBuff"    = "num:i(0)"!][!//
        [!VAR "NoOfRxDedBuff"    = "num:i(0)"!][!//
        [!VAR "SizeOfTxQue"      = "num:i(0)"!][!//
        [!VAR "RxFIFOCount"      = "num:i(0)"!][!//
        [!VAR "TxQueueCount"     = "num:i(0)"!][!//
        [!VAR "SizeOfRxFIFO1"    = "num:i(0)"!][!//
        [!VAR "SizeOfRxFIFO0"    = "num:i(0)"!][!//
        [!VAR "RxFIFO1Threshold" = "num:i(0)"!][!//
        [!VAR "RxFIFO0Threshold" = "num:i(0)"!][!//
        [!VAR "NoOfSIDTemp"      = "num:i(0)"!][!//
        [!VAR "NoOfXIDTemp"      = "num:i(0)"!][!//
        [!VAR "CurrentController"= "node:value(./CanHardwareChannel)"!][!//
        [!VAR "TempControllerId" = "$CurrentController"!][!//
        [!/* Traverse each HOH object */!][!//
        [!LOOP "node:order(../../CanHardwareObject/*, 'node:value(node:ref(./CanControllerRef)/CanHardwareChannel)')"!][!//
          [!/* Only process the Hoh matched the same controller */!][!//
          [!IF "$CurrentController = node:value(node:ref(./CanControllerRef)/CanHardwareChannel)"!][!//
            [!CALL "CG_CalculateHardwareChannel", "Channel"="node:value(node:ref(./CanControllerRef)/CanHardwareChannel)"!][!//
            [!/* Update the FLSSA with fix address when first controller in same module */!][!//
            [!VAR "FLSSA" = "num:hextoint(substring-after(text:split($FLSSAToCanModule)[num:i($ResHardwareModule + 1)],':'))"!][!//
            [!/* Count the usage of each controller */!][!//
            [!VAR "HwControllerId" = "num:i(node:ref(CanControllerRef)/CanControllerId)"!][!//
            [!IF "CanObjectType = 'TRANSMIT' and CanHwObjectCount = '1' "!][!//
              [!VAR "NoOfTxDedBuff" = "num:i($NoOfTxDedBuff+1)"!][!//
            [!ENDIF!][!//
            [!IF "CanObjectType = 'TRANSMIT' and CanHwObjectCount > '1' and CanHwObjectCount < '33' "!][!//
              [!VAR "SizeOfTxQue" = "num:i(CanHwObjectCount)"!][!//
              [!IF "$TxQueueCount > '0' "!][!//
                [!ERROR!][!//
                  080-00-09-ERROR: The Cancontroller [!"$HwControllerId"!] is configured with more than <1> HTH with the CanHwObjectCount is greater than value <1>.This type of configuration is allowed for
                  a specific controller is limited with <1> since controller is supported with one TxQueue.
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!VAR "TxQueueCount" = "num:i($TxQueueCount+1)"!][!//
            [!ENDIF!][!//
            [!IF "CanObjectType = 'RECEIVE' and CanHwObjectCount = '1' "!][!//
              [!VAR "NoOfRxDedBuff" = "num:i($NoOfRxDedBuff+1)"!][!//
            [!ENDIF!][!//
            [!IF "CanObjectType = 'RECEIVE' and CanHwObjectCount > '1' "!][!//
              [!IF "$RxFIFOCount > '1' "!][!//
                [!ERROR!][!//
                  080-00-07-ERROR: The Cancontroller[!"$HwControllerId"!] is configured with more than <2> HRH which contains the CanHwObjectCount is greater than value <1>.This type of configuration is allowed for
                  a specific controller is limited with <2> since controller is supported with 2 RXFIFOs only.
                [!ENDERROR!][!//
              [!ENDIF!][!//
              [!IF "$RxFIFOCount = '1' "!][!//
                [!VAR "SizeOfRxFIFO1" = "num:i(CanHwObjectCount)"!][!//
                [!VAR "RxFIFO1Threshold" = "num:i(CanHwFIFOThreshold)"!][!//
                [!VAR "RxFIFOCount" = "num:i($RxFIFOCount+1)"!][!//
              [!ENDIF!][!//
              [!IF "$RxFIFOCount = '0' "!][!//
                [!VAR "SizeOfRxFIFO0" = "num:i(CanHwObjectCount)"!][!//
                [!VAR "RxFIFO0Threshold" = "num:i(CanHwFIFOThreshold)"!][!//
                [!VAR "RxFIFOCount" = "num:i($RxFIFOCount+1)"!][!//
              [!ENDIF!][!//
            [!ENDIF!][!//
            [!IF "CanObjectType = 'RECEIVE'"!][!//
                [!IF "CanIdType = 'STANDARD' or CanIdType = 'MIXED' "!][!//
                  [!VAR "NoOfSIDTemp" = "num:i($NoOfSIDTemp+1)"!][!//
                [!ENDIF!][!//
                [!IF "CanIdType = 'EXTENDED' or CanIdType = 'MIXED' "!][!//
                  [!VAR "NoOfXIDTemp" = "num:i($NoOfXIDTemp+1)"!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
          [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$SizeOfRxFIFO1 < $RxFIFO1Threshold "!][!//
        [!ERROR!][!//
          080-00-11-ERROR: The configurtion value of CanHwFIFOThreshold of HRH refernced by Cancontroller [!"$TempControllerId"!] is wrong.The value of CanHwFIFOThreshold
          shall be less than or equal with CanHwObjectCount.
        [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "$SizeOfRxFIFO0 < $RxFIFO0Threshold "!][!//
          [!ERROR!][!//
            080-00-12-ERROR: The configurtion value of CanHwFIFOThreshold of HRH refernced by Cancontroller [!"$TempControllerId"!] is wrong.The value of CanHwFIFOThreshold
            shall be less than or equal with CanHwObjectCount.
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "$NoOfSIDTemp > 128 "!][!//
          [!ERROR!][!//
            080-00-13-ERROR: The toatl number of standard message filter elements configuration for controller [!"$TempControllerId"!] is greater than limit value <128>
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "$NoOfXIDTemp > 64 "!][!//
          [!ERROR!][!//
            080-00-14-ERROR: The total number of Extended message filter elements configuration for controller [!"$TempControllerId"!] is greater than limit value <64>
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "$NoOfRxDedBuff > 64 "!][!//
          [!ERROR!][!//
            080-00-15-ERROR: The total number of HRH configuration for the controller [!"$TempControllerId"!] is greater than limit value <64>
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "$NoOfTxDedBuff > 32 "!][!//
          [!ERROR!][!//
            080-00-16-ERROR: The total number of HTH is configured for the controller [!"$TempControllerId"!]is greater than limit value <32>
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "(($NoOfTxDedBuff+$SizeOfTxQue) > 64 )"!][!//
          [!ERROR!][!//
            080-00-17-ERROR: The total number of Hardware objects (sum of all HTH CanHwObjectCount) used by the controller[!"$TempControllerId"!] is greater than limit value <32>
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!VAR "MsgRAMElementSize" = "num:i(4)"!][!//
        [!IF "$CanFD_Controller_Supported = 1"!][!//
          [!VAR "ControllerBRConfigTemp" = "num:i(count(./CanControllerBaudrateConfig/*))"!][!//
          [!FOR "BaudrateIndx" = "1" TO "$ControllerBRConfigTemp"!][!//
            [!IF "(node:exists(./CanControllerBaudrateConfig/*[position()=$BaudrateIndx]/CanControllerFdBaudrateConfig))"!][!//
              [!VAR "MsgRAMElementSize" = "num:i(18)"!][!//
            [!ENDIF!][!//
          [!ENDFOR!][!//
        [!ENDIF!][!//
        [!VAR "FLESA" = "num:i($FLSSA) + (num:i($NoOfSIDTemp)   * num:i(4)) "!][!//
        [!VAR "F0SA"  = "num:i($FLESA) + (num:i($NoOfXIDTemp)   * num:i(2) * num:i(4)) "!][!//
        [!VAR "F1SA"  = "num:i($F0SA)  + (num:i($SizeOfRxFIFO0) * num:i($MsgRAMElementSize) * num:i(4)) "!][!//
        [!VAR "RBSA"  = "num:i($F1SA)  + (num:i($SizeOfRxFIFO1) * num:i($MsgRAMElementSize) * num:i(4)) "!][!//
        [!VAR "EFSA"  = "num:i($RBSA)  + (num:i($NoOfRxDedBuff) * num:i($MsgRAMElementSize) * num:i(4)) "!][!//
        [!VAR "TBSA"  = "num:i($EFSA)  + ((num:i($NoOfTxDedBuff)+num:i($SizeOfTxQue)) * num:i(2) * num:i(4)) "!][!//
        [!VAR "NODEENDADDRESS" = "num:i($TBSA) +((num:i($NoOfTxDedBuff) + num:i($SizeOfTxQue)) * num:i($MsgRAMElementSize) * num:i(4)) "!][!//
        [!IF "$NODEENDADDRESS > num:hextoint(ecu:get(text:join(concat('Can.MCAN',string($ResHardwareModule),'ENDRAM'))))"!][!//
          [!ERROR!][!//
            080-00-18-ERROR: MCM_CAN is configured to use more MessageRAM than allowed for CAN Kernel [!"$ResHardwareModule"!] in the CanControllerId [!"$TempControllerId"!]
          [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "$IndexCnt > '0'"!][!//
          [!AUTOSPACING!],
        [!ENDIF!][!//
        [!AUTOSPACING!]
        [!INDENT "4"!][!//
        [!VAR "ControllerChannelToIdMap" = "concat($ControllerChannelToIdMap, ./CanHardwareChannel, ':', $IndexCnt, '; ')"!][!//
        [!VAR "IndexCnt" = "num:i($IndexCnt+1)"!][!//
        {
          [!INDENT "8"!][!//
          /* Start Address of each section within the Message RAM */
          {
            [!INDENT "12"!][!//
              /* [!"$CurrentController"!] Message RAM Start Address :[!"num:inttohex($FLSSA)"!] */
            [!IF "$NoOfSIDTemp > 0 "!][!//
              [!"num:inttohex($FLSSA)"!]U,     /* Standard Filter List Start Address #[!"num:i($NoOfSIDTemp)"!] */
            [!ELSE!][!//
              0x00000000U,     /* Standard Filter List Start Address #[!"num:i($NoOfSIDTemp)"!] */
            [!ENDIF!][!//
            [!IF "$NoOfXIDTemp > 0 "!][!//
              [!"num:inttohex($FLESA)"!]U,     /* Extended Filter List Start Address #[!"num:i($NoOfXIDTemp)"!] */
            [!ELSE!][!//
              0x00000000U,     /* Extended Filter List Start Address #[!"num:i($NoOfXIDTemp)"!] */
            [!ENDIF!][!//
            [!IF "$SizeOfRxFIFO0 > 0 "!][!//
              [!"num:inttohex($F0SA)"!]U,     /* Rx FIFO 0 Start Address #[!"num:i($SizeOfRxFIFO0)"!] */
            [!ELSE!][!//
              0x00000000U,     /* Rx FIFO 0 Start Address #[!"num:i($SizeOfRxFIFO0)"!] */
            [!ENDIF!][!//
            [!IF "$SizeOfRxFIFO1 > 0 "!][!//
              [!"num:inttohex($F1SA)"!]U,     /* Rx FIFO 1 Start Address #[!"num:i($SizeOfRxFIFO1)"!] */
            [!ELSE!][!//
              0x00000000U,     /* Rx FIFO 1 Start Address #[!"num:i($SizeOfRxFIFO1)"!] */
            [!ENDIF!][!//
            [!IF "$NoOfRxDedBuff > 0 "!][!//
              [!"num:inttohex($RBSA)"!]U,     /* Rx Buffer Start Address #[!"num:i($NoOfRxDedBuff)"!] */
            [!ELSE!][!//
              0x00000000U,     /* Rx Buffer Start Address #[!"num:i($NoOfRxDedBuff)"!] */
            [!ENDIF!][!//
            [!ENDINDENT!][!//
            [!INDENT "12"!][!//
            [!IF "($NoOfTxDedBuff+$TxQueueCount) > 0"!][!//
              [!"num:inttohex($EFSA)"!]U,     /* Tx Event FIFO Start Address #[!"num:i($TxQueueCount)"!] */
              [!"num:inttohex($TBSA)"!]U      /* Tx Buffers Start Address #[!"num:i($NoOfTxDedBuff)"!] */
              /* [!"$CurrentController"!] Message RAM End Address :[!"num:inttohex($NODEENDADDRESS)"!] */
              [!INDENT "8"!][!//
          },
              [!ENDINDENT!][!//
            [!ELSE!][!//
            0x00000000U,     /* Tx Event FIFO Start Address #[!"num:i($TxQueueCount)"!] */
            0x00000000U      /* Tx Buffers Start Address #[!"num:i($NoOfTxDedBuff)"!] */
            /* [!"$CurrentController"!] Message RAM End Address :[!"num:inttohex($NODEENDADDRESS)"!] */
            [!INDENT "8"!][!//
          },
            [!ENDINDENT!][!//
            [!ENDIF!][!//
        [!ENDINDENT!][!//
        [!ENDINDENT!][!//
        [!INDENT "8"!][!//
        {
          [!INDENT "12"!][!//
          (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 0 operating mode */
          (uint8)CAN_RXFIFOMODE_BLOCKING, /* Rx FIFO 1 operating mode */
          [!"num:inttohex($RxFIFO0Threshold)"!]U,                    /* RxFIFO0Threshold */
          [!"num:inttohex($RxFIFO1Threshold)"!]U,                    /* RxFIFO1Threshold */
          [!IF "node:exists(CanFDSupport) and CanFDSupport = 'true'"!][!//
              (uint8)CAN_DATAFIELDSIZE_64,    /* RX FIFO 0 data field size */
              (uint8)CAN_DATAFIELDSIZE_64,    /* RX FIFO 1 data field size */
              (uint8)CAN_DATAFIELDSIZE_64,    /* Rx buffer data field size */
          [!ELSE!][!//
              (uint8)CAN_DATAFIELDSIZE_8,     /* RX FIFO 0 data field size */
              (uint8)CAN_DATAFIELDSIZE_8,     /* RX FIFO 1 data field size */
              (uint8)CAN_DATAFIELDSIZE_8,     /* Rx Buffer data field size */
          [!ENDIF!][!//
              [!"num:inttohex($NoOfRxDedBuff)"!]U,                    /* Number of Dedicated Rx Buffer elements */
              [!"num:inttohex($SizeOfRxFIFO0)"!]U,                    /* Number of Rx FIFO0 Elements */
              [!"num:inttohex($SizeOfRxFIFO1)"!]U                     /* Number of Rx FIFO1 Elements */
              [!VAR "NumOfRxFIFO"    = "num:i(0)"!][!//
              [!IF "num:i($SizeOfRxFIFO1) != num:i(0)"!][!//
                [!VAR "NumOfRxFIFO"    = "num:i(2)"!][!//
              [!ELSEIF "num:i($SizeOfRxFIFO0) != num:i(0)"!]
                [!VAR "NumOfRxFIFO"    = "num:i(1)"!][!//
              [!ELSE!]
                [!VAR "NumOfRxFIFO"    = "num:i(0)"!][!//
              [!ENDIF!][!//
          [!ENDINDENT!][!//
        },
        {
          [!INDENT "12"!][!//
            (uint8)CAN_TX_FIFO_OPERATION,   /* Tx FIFO/Queue Mode */
          [!IF "node:exists(CanFDSupport) and CanFDSupport = 'true'"!][!//
            (uint8)CAN_DATAFIELDSIZE_64,    /* Tx buffer data field size */
          [!ELSE!][!//
            (uint8)CAN_DATAFIELDSIZE_8,     /* Tx buffer data field size */
          [!ENDIF!][!//
            [!"num:inttohex($NoOfTxDedBuff)"!]U,                    /* Number of Dedicated Tx Buffers */
            [!"num:inttohex($SizeOfTxQue)"!]U,                    /* Number of Tx Buffers used for Tx FIFO/Queue */
            [!"num:inttohex($NoOfTxDedBuff+$SizeOfTxQue)"!]U,                    /* Number of Tx Event FIFO elements */
            0x0U                     /* Tx event FIFO water mark level */
            [!VAR "NumOfHth"    = "num:i(0)"!][!//
            [!IF "num:i($SizeOfTxQue) != num:i(0)"!][!//
            [!VAR "NumOfHth"    = "num:i($NoOfTxDedBuff + 1)"!][!//
            [!ELSE!]
            [!VAR "NumOfHth"    = "num:i($NoOfTxDedBuff)"!][!//
            [!ENDIF!][!//
          [!ENDINDENT!][!//
        },
        {
          [!INDENT "12"!][!//
          (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with standard id */
          (uint8)CAN_REJECT_REMOTE,           /* SWS_Can_00237:reject the remote frames with extended id */
          (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching extended message ID */
          (uint8)CAN_NOMATCHINGFRAME_REJECT,  /* Reject the non-matching standard message ID */
          [!"num:inttohex($NoOfSIDTemp)"!]U,                        /* Number of standard Message ID filters. */
          [!"num:inttohex($NoOfXIDTemp)"!]U,                        /* Number of extended Message ID filters */
          [!ENDINDENT!][!//
        },
        [!"$NoOfRxDedBuff"!]U,                                   /* Total number of RX buffer used */
        [!"$NumOfRxFIFO"!]U,                                   /* Total number of RX FIFO used */
        [!"$NumOfHth"!]U,                                   /* Total number of Hth */
        [!IF "$NoOfRxDedBuff != num:i(0)"!][!//
            &Can_RxBufferIndexToHwObjectId[!"node:value(./CanControllerId)"!][0],   /* Rx dedicated buffer index list */
        [!ELSE!][!//
            NULL_PTR,
        [!ENDIF!][!//
        [!IF "$NumOfRxFIFO != num:i(0)"!][!//
            &Can_RxFifoIndexToHwObjectId[!"node:value(./CanControllerId)"!][0],     /* Rx FIFO index list */
        [!ELSE!][!//
            NULL_PTR,
        [!ENDIF!][!//
        [!IF "$NumOfHth != num:i(0)"!][!//
            &CanTxBufferAndFIFOIndexToHwObjectId[!"node:value(./CanControllerId)"!][0]   /* Hth index list */
        [!ELSE!][!//
            NULL_PTR
        [!ENDIF!][!//
        [!ENDINDENT!][!//
        }[!//
        [!ENDINDENT!][!//
        [!VAR "NoOfSidFilt" = "num:i($NoOfSidFilt + $NoOfSIDTemp)"!][!//
        [!VAR "NoOfXidFilt" = "num:i($NoOfXidFilt + $NoOfXIDTemp)"!][!//
        [!VAR "NoOfTxObj" = "num:i($NoOfTxObj + $NoOfTxDedBuff + $TxQueueCount)"!][!//
        [!VAR "NoOfRxObj" = "num:i($NoOfRxObj + $NoOfRxDedBuff + $RXFIFO0UsedStatus + $RXFIFO1UsedStatus)"!][!//
        [!/* Update the FLSSA with end address of the previous controller in same module */!][!//
        [!VAR "FLSSAToCanModule" = "text:replace($FLSSAToCanModule, text:tolower(num:inttohex($FLSSA)), text:tolower(num:inttohex($NODEENDADDRESS)))"!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//

};
[!INDENT "0"!][!//
/***************************************************************************************************
*                        Can Controller(s) General Configurations
****************************************************************************************************/
static CONST(Can_ControllerConfigType, CAN_CONST) Can_ControllerCfgSetCore[!"$CoreIndex"!][CAN_USED_CONTROLLER_MAX_NUM_TO_CORE[!"$CoreIndex"!]] =
{
    [!INDENT "4"!][!//
    [!VAR "TempConfigIndex" = "num:i(0)"!]
        [!LOOP "node:order(CanConfigSet/CanController/*,'node:value(CanControllerId)')"!][!//
        [!CALL "CG_FindCanControllerMappedCoreId", "CanControllerName"="node:name(.)"!][!//
        [!IF "$CanControllerMappedCoreId = num:i($CoreIndex)"!][!//
            /*Can Controller[!"CanControllerId"!] Configuration*/
            {
                [!INDENT "8"!][!//
                    (Can_ProcessingType)CAN_[!"node:value(CanBusoffProcessing)"!],[!WS "6"!]/*BusoffProcessing*/
                    (boolean)[!IF "CanControllerActivation = 'true'"!]TRUE,[!ELSE!]FALSE,[!ENDIF!][!WS "20"!]/*Activation*/
                    (uint8)[!"node:value(CanHardwareChannel)"!],[!WS "9"!]/*PhysicalID*/
                    (CAN_NODE*)[!"node:value(CanHardwareChannel)"!]_BASE_ADDRESS,[!WS "9"!]/*Physical Address*/
                    (uint8)[!"node:value(CanControllerId)"!]U,[!WS "24"!]/*LogicalID*/
                    (Can_ProcessingType)CAN_[!"node:value(CanRxProcessing)"!],[!WS "6"!]/*RxProcessing*/
                    (Can_ProcessingType)CAN_[!"node:value(CanTxProcessing)"!],[!WS "6"!]/*TxProcessing*/
                [!IF "$Can_Wakeup_Controller_Supported = 1"!][!//
                    [!IF "CanWakeupSupport = 'true'"!][!//
                        (Can_ProcessingType)CAN_[!"node:value(CanWakeupProcessing)"!],[!WS "6"!]/*WakeupProcessing*/
                        (boolean)TRUE,[!WS "20"!]/*WakeupSupport*/
                        [!IF "node:exists(CanWakeupSourceRef)"!][!//
                            (uint32)ECUM_CAN_WAKEUPSOURCEID[!"CanControllerId"!],  /*WakeupSourceId*/
                        [!ELSE!][!//
                            (uint32)0xFFFFFFFFU,[!WS "14"!]/*Invalid WakeupSourceId*/
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        (Can_ProcessingType)CAN_[!"node:value(CanWakeupProcessing)"!],[!WS "6"!]/*WakeupProcessing*/
                        (boolean)FALSE,[!WS "19"!]/*WakeupSupport*/
                        (uint32)0xFFFFFFFFU,[!WS "14"!]/*Invalid WakeupSourceId*/
                    [!ENDIF!][!//
                [!ENDIF!][!//
                [!VAR "InterruptControllerId" = "./CanControllerId"!]
                [!VAR "InterruptFlag" = "'false'"!]
                [!/* Find controller mode is interrupt or mixed */!][!//
                [!IF "(node:value(./CanBusoffProcessing) = 'INTERRUPT') or (node:value(./CanRxProcessing) = 'INTERRUPT') or
                      (node:value(./CanTxProcessing) = 'INTERRUPT') or (node:value(./CanWakeupProcessing) = 'INTERRUPT')"!][!//
                      [!VAR "InterruptFlag" = "'true'"!][!//
                [!ELSE!][!//
                    [!IF "node:value(./CanRxProcessing) = 'MIXED' or node:value(CanTxProcessing) = 'MIXED'"!][!//
                        [!LOOP "node:order(../../CanHardwareObject/*,'node:value(CanObjectId)')"!][!//
                            [!IF "node:value(node:ref(./CanControllerRef)/CanControllerId) = $InterruptControllerId"!][!//
                                [!IF "node:exists(CanHardwareObjectUsesPolling) and node:value(CanHardwareObjectUsesPolling) = 'true'"!][!//
                                    [!VAR "InterruptFlag" = "'false'"!][!//
                                [!ELSE!][!//
                                    [!VAR "InterruptFlag" = "'true'"!][!//
                                    [!BREAK!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ENDLOOP!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
                [!IF "$InterruptFlag = 'true'"!][!//
                    (Can_InterruptStateType)CAN_INTERRUPT_ACTIVE,[!WS "8"!]/*InterruptState*/
                [!ELSE!][!//
                    (Can_InterruptStateType)CAN_INTERRUPT_DOWN,[!WS "8"!]/*InterruptState*/
                [!ENDIF!][!//
                [!IF "$CanFD_Controller_Supported = 1"!][!//
                    (boolean)[!IF "CanFDSupport = 'true'"!]TRUE,[!ELSE!]FALSE,[!ENDIF!][!WS "23"!]/*CanFDSupport*/
                [!ENDIF!][!//
                [!VAR "defaultbaudrateref" = "node:path(node:ref(CanControllerDefaultBaudrate))"!][!//
                [!VAR "defaultbaudrateindex" = "0"!][!//
                    [!LOOP "CanControllerBaudrateConfig/*"!][!//
                        [!IF "$defaultbaudrateref = node:path(.)"!][!//
                            (uint8)[!"num:i($defaultbaudrateindex)"!]U,[!WS "28"!]/*DefaultBaudrate*/
                        [!BREAK!][!//
                        [!ENDIF!][!//
                    [!VAR "defaultbaudrateindex" = "$defaultbaudrateindex + 1"!][!//
                    [!ENDLOOP!][!//
                    &Can_BaudrateCfgSet_Controller[!"CanControllerId"!][0],[!WS "3"!]/*BaudrateCfg*/
                    (uint8)[!"num:i(count(./CanControllerBaudrateConfig/*))"!]U,[!WS "30"!]/*NumberofBaudrate*/
                    [!VAR "TempConfigIndex" = "substring-before(substring-after($ControllerChannelToIdMap, concat(./CanHardwareChannel, ':')),';')"!][!//
                    &Can_ControllerMsgRAMMapConfigCore[!"$CoreIndex"!][[!"num:i($TempConfigIndex)"!]]  /*MsgRAM map to Controller list*/
                [!ENDINDENT!][!//
            },
        [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
/***************************************************************************************************
*                       Can Controller Usage Informations
****************************************************************************************************/
static const Can_CoreConfigType Can_CoreConfigCore[!"$CoreIndex"!] =
{
    [!INDENT "4"!][!//
    (Can_IdType)CAN_USED_CONTROLLER_MAX_NUM_TO_CORE[!"$CoreIndex"!],       /* Maximum number of the Controller(assigned to the core[!"$CoreIndex"!]) */
    &Can_ControllerCfgSetCore[!"$CoreIndex"!][0],                          /* Can configuration information of core[!"$CoreIndex"!] */
    (Can_HwHandleType)CAN_USED_HRH_MB_MAX_NUM_TO_CORE[!"$CoreIndex"!],     /* Maximum number of the HRH(assigned to the core[!"$CoreIndex"!]) */
    (Can_HwHandleType)CAN_USED_HTH_MB_MAX_NUM_TO_CORE[!"$CoreIndex"!],     /* Maximum number of the HTH(assigned to the core[!"$CoreIndex"!]) */
    (Can_HwHandleType)CAN_USED_HOH_MB_MAX_NUM_TO_CORE[!"$CoreIndex"!],     /* Maximum number of the HOH(assigned to the core[!"$CoreIndex"!]) */
    &Can_HohToCfgSetCore[!"$CoreIndex"!][0]                                /* Hardware object index at Hardware Object Config Sets list */
    [!ENDINDENT!][!//
};

#define CAN_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
#include "Can_MemMap.h"
[!ENDIF!][!//
[!ENDINDENT!][!//
/***************************************************************************************************
*                       CAN CONTROLLER(s) OF CORE[!"$CoreIndex"!] CONFIGURATIONS STOP
****************************************************************************************************/

[!ENDFOR!][!//

#define CAN_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"
/***************************************************************************************************
*                       Can Controller Allocation Mapping List
****************************************************************************************************/
static const Mcal_CoreType Can_ControllerMapList[CAN_USED_CONTROLLER_MAX_NUM] =
{
    [!INDENT "4"!][!//
    [!VAR "Count" = "num:i(count(CanConfigSet/CanController/*))"!][!//
    [!LOOP "node:order(CanConfigSet/CanController/*, './CanControllerId')"!][!//
    [!CALL "CG_FindCanControllerMappedCoreId", "CanControllerName"="node:name(.)"!][!//
        [!VAR "Count" = "num:i($Count - 1)"!][!//
        MCAL_CORE[!"$CanControllerMappedCoreId"!][!IF "$Count != num:i(0)"!],[!ELSE!][!WS!][!ENDIF!]    /* Controller<[!"node:value(CanControllerId)"!]>(assigned to Core<[!"$CanControllerMappedCoreId"!]>)*/
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//  
};

/***************************************************************************************************
*                       Can Controller Index Mapping List
*   CanControllerId                              Can_ControllerGlobalStatus_Corei/
*                                                Can_ControllerCfgSetCorei
*   +-----------------------+                    +-------+
*   | CanController0(Core0) |   -------------->  |   0   |
*   +-----------------------+                    +-------+
*   | CanController1(Core0) |   -------------->  |   1   |
*   +-----------------------+                    +-------+
*   | CanController2(Core1) |   -------------->  |   0   |
*   +-----------------------+                    +-------+
*   | CanController3(Core2) |   -------------->  |   0   |
*   +-----------------------+                    +-------+
****************************************************************************************************/
[!INDENT "0"!][!//
[!/* This array is used for mapping Can Controller to the Core. Array index is 
Can Controller -> array member is index of Can_ControllerToCoreMap,[x=0~4]*/!][!//
static const uint8 Can_ControllerToCoreMap[CAN_USED_CONTROLLER_MAX_NUM] =
{
    [!INDENT "4"!][!//
    [!/* Create an initial string based on the number of cores: Store in the form of a key-value pair CoreId: The number of resources allocated to the current core (recorded starting from 0) */!][!//
    [!/* ControllerNumToCorex-->>Core0Id:ResourcesNumber ... CorexId:ResourcesNumber-->>0:65535 1:65535 2:65535 3:65535 */!][!//
    [!VAR "ControllerNumToCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
        [!VAR "ControllerNumToCorex" = "concat($ControllerNumToCorex, $CoreIndex, ':65535 ')"!][!//
    [!ENDFOR!][!//
    [!VAR "LoopCount" = "num:i(count(CanConfigSet/CanController/*))"!][!//
    [!LOOP "node:order(CanConfigSet/CanController/*, './CanControllerId')"!][!//
        [!CALL "CG_FindCanControllerMappedCoreId", "CanControllerName"="node:name(.)"!][!//
        [!CALL "CG_ChangeStringListMember", "Object"="$ControllerNumToCorex", "Index" = "$CanControllerMappedCoreId", "Count" = "1"!][!//
        [!VAR "ControllerNumToCorex" = "$Object"!][!//
        [!VAR "LoopCount" = "num:i($LoopCount - 1)"!][!//
        [!"num:i($Value)"!]U[!IF "$LoopCount != num:i(0)"!],[!ELSE!][!WS!][!ENDIF!] /* Controller<[!"./CanControllerId"!]>(assigned to Core[!"$CanControllerMappedCoreId"!]) in Controller list index <[!"num:i($Value)"!]> */
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
[!INDENT "0"!][!//

/***************************************************************************************************
*                       Hardware Object Status Mapping List
*
*   CanObjectId(CanHwObjectCount)                  Can_MBGlobalStatus_Corei
*   +-------------------------+                    +-------+
*   | ID0(CanHwObjectCount=1) |   -------------->  |   0   |
*   +-------------------------+                    +-------+
*   | ID1(CanHwObjectCount=3) |   -------------->  |   1   |
*   +-------------------------+                    +-------+
*   | ID2(CanHwObjectCount=1) |   ---------        |   2   |
*   +-------------------------+            |       +-------+
*   | ID3(CanHwObjectCount=2) |   ------   |       |   3   |
*   +-------------------------+         |  |       +-------+
*                                       |   ---->  |   4   | 
*                                       |          +-------+
*                                        ------->  |   5   | 
*                                                  +-------+
*   
****************************************************************************************************/
static const uint16 Can_HwObjectToCoreIndexMap[CAN_USED_HOH_MB_MAX_NUM] =
{
    [!INDENT "4"!][!//
    [!VAR "HardwareObjectNumToCorex" = "''"!][!//
    [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!/* We need to obtain the value before accumulation, so the initial value needs to be set to 0.*/!][!//
        [!VAR "HardwareObjectNumToCorex" = "concat($HardwareObjectNumToCorex, $CoreIndex, ':0 ')"!][!//
    [!ENDFOR!][!//
    [!VAR "LoopCount" = "num:i(count(CanConfigSet/CanHardwareObject/*))"!][!//
    [!LOOP "node:order(CanConfigSet/CanHardwareObject/*, './CanObjectId')"!][!//
        [!CALL "CG_FindCanHardwareObjectIdMappedCoreId", "CanHwObjName"="node:name(.)"!][!//
        [!CALL "CG_ChangeStringListMember", "Object"="$HardwareObjectNumToCorex", "Index" = "$CanHardwareObjectIdMappedCoreId", "Count" = "node:value(./CanHwObjectCount)"!][!//
        [!VAR "HardwareObjectNumToCorex" = "$Object"!][!//
        [!VAR "LoopCount" = "num:i($LoopCount - 1)"!][!//
        [!"num:i($ValueCountBefore)"!]U[!IF "$LoopCount != num:i(0)"!],[!ELSE!][!WS!][!ENDIF!] /* CanObjectId<[!"./CanObjectId"!]> CanHwObjectCount=[!"./CanHwObjectCount"!] in (assigned to Core[!"$CanHardwareObjectIdMappedCoreId"!]) Can_MBGlobalStatus_Corei index */
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
/***************************************************************************************************
*                       Can Driver Configuration Set
****************************************************************************************************/
[!INDENT "0"!][!//
[!IF "variant:name() != ''"!][!//
const Can_ConfigType Can_ConfigSet_[!"variant:name()"!][CAN_CONFIG_COUNT] =
[!ELSE!][!//
const Can_ConfigType Can_ConfigSet[CAN_CONFIG_COUNT] =
[!ENDIF!][!//
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        /* CanController Config Sets of all cores */
        {
            [!INDENT "12"!][!//
            [!/* Call the function of CG_FindTotalNumCanControllerMappedToCorex to count the number of controller map to core*/!][!//
            [!CALL "CG_FindTotalNumCanControllerMappedToCorex"!][!//
            [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                [!VAR "ControllerNumMapToCorex" = "num:i(substring-after(text:split($CanControllerMappedToCorex)[num:i($CoreIndex + 1)], ':'))"!][!//
                [!IF "num:i($ControllerNumMapToCorex) != num:i(65535)"!][!//
                    &Can_CoreConfigCore[!"$CoreIndex"!][!IF "$CoreIndex != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ELSE!][!WS "1"!][!ENDIF!][!WS "9"!]/* Can Controller configuration of Core[!"$CoreIndex"!] */
                [!ELSE!][!//
                    NULL_PTR[!IF "$CoreIndex != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ELSE!][!WS "1"!][!ENDIF!][!WS "21"!]/* Can Controller configuration of Core[!"$CoreIndex"!] */
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        },
        &Can_HardwareObj_MBCfgSet[0],     /* Hardware Object Config Sets of all cores */
        &Can_ControllerToCoreMap[0],      /* Mapping can controller ID to global controller status of each core */
        &Can_HwObjectToCoreIndexMap[0],   /* Mapping hardware object ID to global mailbox status of each core */
        &Can_ControllerMapList[0]         /* Mapping can controller ID to CoreID */
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//
#define CAN_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Can_MemMap.h"


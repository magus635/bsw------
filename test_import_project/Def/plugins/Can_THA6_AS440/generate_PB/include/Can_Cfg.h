/**************************************************************************************************
*
***************************************************************************************************/

/**************************************************************************************************
*   FileName             : Can_Cfg.h
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
[!NOCODE!][!//
[!INCLUDE "Can_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
/**************************************************************************************************/
#ifndef CAN_CFG_H
#define CAN_CFG_H
/***************************************************************************************************
*                            Global Definitions and Macros
****************************************************************************************************/

/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define CAN_CFG_H_AR_RELEASE_MAJOR_VERSION           ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define CAN_CFG_H_AR_RELEASE_MINOR_VERSION           ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define CAN_CFG_H_AR_RELEASE_REVISION_VERSION        ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define CAN_CFG_H_SW_MAJOR_VERSION                   ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define CAN_CFG_H_SW_MINOR_VERSION                   ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define CAN_CFG_H_SW_PATCH_VERSION                   ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define CAN_CFG_H_VENDOR_ID                          ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define CAN_CFG_H_MODULE_ID                          (80U)       /* 0x50U */
/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
[!LOOP "node:order(CanConfigSet/CanController/*, './CanControllerId')"!][!//
[!IF "CanControllerId < num:i(ecu:get('Can.MaxModules')*ecu:get('Can.MaxNodes'))"!][!//
/*The Macros CAN_CONTROLLER_XX defines logical ID corresponding to hardware unit */
#define [!"node:value(./CanHardwareChannel)"!] [!WS "28"!]([!"num:i(num:i(substring(./CanHardwareChannel,16,1))*ecu:get('Can.MaxNodes') + num:i(substring(./CanHardwareChannel,17,1)))"!]U)
#define CAN_CONTROLLER_[!"substring(./CanHardwareChannel,16,2)"!]_LOGIC_ID [!WS "19"!]([!"node:value(./CanControllerId)"!]U)
#define [!"node:value(./CanHardwareChannel)"!]_BASE_ADDRESS [!WS "15"!](CAN[!"substring(./CanHardwareChannel,16,2)"!])
[!VAR "CurrentInterruptStateFlgforMacros" = "1"!][!//
[!/* Loop mailbox in current controller */!][!//
[!LOOP "node:order(CanConfigSet/CanHardwareObject/*,'node:value(CanObjectId)')"!][!//
  [!IF "node:value(node:ref(./CanControllerRef)/CanControllerId) = CanControllerId"!][!//
    [!/* Check whether the mailbox has disable the CanHardwareObjectUsesPolling option or not select the CanHardwareObjectUsesPolling */!][!//
      [!IF "node:exist(CanHardwareObjectUsesPolling)"!][!//
          [!IF "node:value(CanHardwareObjectUsesPolling) = 'false'"!][!//
              [!VAR "CurrentInterruptStateFlgforMacros" = "1"!][!//
          [!ENDIF!][!//
      [!ELSE!][!//
              [!VAR "CurrentInterruptStateFlgforMacros" = "1"!][!//
      [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDLOOP!][!//
#define [!"node:value(./CanHardwareChannel)"!]_TX_INTERRUPT [!WS "15"!][!IF "(CanTxProcessing = 'INTERRUPT') or ((CanTxProcessing = 'MIXED') and (num:i($CurrentInterruptStateFlgforMacros) = '1'))"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define [!"node:value(./CanHardwareChannel)"!]_RX_INTERRUPT [!WS "15"!][!IF "(CanRxProcessing = 'INTERRUPT') or ((CanRxProcessing = 'MIXED') and (num:i($CurrentInterruptStateFlgforMacros) = '1'))"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define [!"node:value(./CanHardwareChannel)"!]_BUSOFF_INTERRUPT [!WS "11"!][!IF "CanBusoffProcessing = 'INTERRUPT'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define [!"node:value(./CanHardwareChannel)"!]_WAKEUP_INTERRUPT [!WS "11"!][!IF "CanWakeupProcessing = 'INTERRUPT'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define [!"node:value(./CanHardwareChannel)"!]_RXFIFO_INTERRUPT [!WS "11"!][!IF "(CanRxProcessing = 'INTERRUPT') or ((CanRxProcessing = 'MIXED') and (num:i($CurrentInterruptStateFlgforMacros) = '1'))"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
/***************************************************************************************************
*                            Functional Configuration
****************************************************************************************************/
/*Safety Error Tracer*/
#define CAN_SAFETY_ENABLE                            [!IF "CanGeneral/CanSafetyErrorDetect = 'true'"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*ECUC_Can_00106*/
#define CAN_VERSION_INFO_API                         [!IF "CanGeneral/CanVersionInfoApi = 'true'"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*ECUC_Can_00064*/
#define CAN_DEV_ERROR_DETECT                         [!IF "CanGeneral/CanDevErrorDetect = 'true'"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*SWS_Can_00416*/
#define CAN_EXTENED_ID_SUPPORT                       [!IF "(num:i(count(CanConfigSet/CanHardwareObject/*[CanIdType != 'STANDARD'])) > 0)"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*SWS_CAN_00495,ECUC_Can_00483*/
#define CAN_PUBLIC_ICOM_SUPPORT                      [!IF "CanGeneral/CanPublicIcomSupport = 'true'"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*ECUC_Can_00330*/
#define CAN_WAKEUP_SUPPORT                           [!IF "$Can_Wakeup_Controller_Supported = 1"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*ECUC_Can_00466*/
#define CAN_CHECK_WAKEUP_API_SUPPORT                 [!IF "("$WakeUp_Support_Flag = 1") and (num:i(count(CanConfigSet/CanController/*[CanWakeupFunctionalityAPI = 'true'])) > 0)"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*ECUC_Can_00482*/
#define CAN_SET_BAUDRATE_API                         [!IF "node:exists(CanGeneral/CanSetBaudrateApi) and (CanGeneral/CanSetBaudrateApi ='true')"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*ECUC_Can_00486*/
#define CAN_TRIGGER_TRANSMIT_SUPPORT                 [!IF "num:i(count(CanConfigSet/CanHardwareObject/*[CanTriggerTransmitEnable = 'true'])) > 0"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*ECUC_Can_00431*/
#define CAN_OS_COUNTER_SUPPORTED                     [!IF "node:exists(CanGeneral/CanOsCounterRef) and (CanGeneral/CanOSCounterSupport ='true')"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*ECUC_Can_00095*/
#define CAN_MULTIPLEXED_TRANSMISSION                 [!IF "CanGeneral/CanMultiplexedTransmission = 'true'"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/*SWS_Can_00443*/
#define CAN_LPDU_CALLOUT_FUNCTION_SUPPORT            [!IF "node:exists(CanGeneral/CanLPduReceiveCalloutFunction) and (normalize-space(CanGeneral/CanLPduReceiveCalloutFunction) != 'NULL_PTR')"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
/* Configure the callback function before sending data */
#define CAN_LPDU_TX_CALLOUT_FUNCTION_SUPPORT         [!IF "node:exists(CanGeneral/CanLPduTransmitCalloutFunction) and (normalize-space(CanGeneral/CanLPduTransmitCalloutFunction) != 'NULL_PTR')"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
[!IF "node:exists(CanGeneral/CanMainFunctionBusoffPeriod)"!][!//
/*ECUC_Can_00355*/
#define CAN_MAINFUNCTION_BUSOFF_PERIOD               [!WS "0"!][!SELECT "CanGeneral"!]([!"num:i(CanMainFunctionBusoffPeriod*1000)"!]U)[!ENDSELECT!][!CR!][!//
[!ENDIF!][!//
/*ECUC_Can_00376*/
#define CAN_MAINFUNCTION_MODE_PERIOD                 [!WS "0"!][!SELECT "CanGeneral"!]([!"num:i(CanMainFunctionModePeriod*1000)"!]U)[!ENDSELECT!][!CR!][!//
[!IF "node:exists(CanGeneral/CanMainFunctionWakeupPeriod)"!][!//
/*ECUC_Can_00357*/
#define CAN_MAINFUNCTION_WAKEUP_PERIOD               [!WS "0"!][!SELECT "CanGeneral"!]([!"num:i(CanMainFunctionWakeupPeriod*1000)"!]U)[!ENDSELECT!][!CR!][!//
[!ENDIF!][!//
[!NOCODE!][!//
/*
*   CAN_TIMEOUT_DURATION : The Timeout duration is in ms unit. The real vaule is second unit.
*   CAN_TIMEOUT_OS_COUNTER_ID: The refernce OS counter ID.
*   CAN_TIMEOUT_OS_TIMERCOUNTER_US: The vaule of OS count 1us. 
*/
[!ENDNOCODE!][!//
[!IF "node:exists(CanGeneral/CanOsCounterRef) and (CanGeneral/CanOSCounterSupport ='true')"!][!//
/*ECUC_Can_00113*/
#define CAN_TIMEOUT_DURATION                         [!SELECT "CanGeneral"!]([!"num:i(CanTimeoutDuration*1000000)"!]UL)[!ENDSELECT!][!CR!][!//
/*ECUC_Can_00431*/
#define CAN_TIMEOUT_OS_COUNTER_ID                    (SystemTimer_Core0)
#define CAN_TIMEOUT_OS_TIMERCOUNTER_US               (OS_TICKS2US_SystemTimer_Core0(1U))
#define CAN_TIMEOUT_MAX_TIME                         (CAN_TIMEOUT_DURATION * CAN_TIMEOUT_OS_TIMERCOUNTER_US)
[!ELSE!][!//
#define CAN_TIMEOUT_LOOP_TIME                        [!SELECT "CanGeneral"!]([!"num:i(CanTimeoutLoopTime*1000000)"!]ULL)[!ENDSELECT!][!CR!][!//
[!ENDIF!][!//
[!IF "node:exists(CanGeneral/CanLPduReceiveCalloutFunction) and (normalize-space(CanGeneral/CanLPduReceiveCalloutFunction) != 'NULL_PTR')"!][!//
/*ECUC_Can_00434*/
#define CAN_LPDU_RECEIVE_CALLOUT_FUNCTION(Hrh,CanId,CanDlc,CanSduPtr)   \
                                [!"normalize-space(CanGeneral/CanLPduReceiveCalloutFunction)"!](Hrh,CanId,CanDlc,CanSduPtr)
[!ENDIF!][!//
[!IF "node:exists(CanGeneral/CanLPduTransmitCalloutFunction) and (normalize-space(CanGeneral/CanLPduTransmitCalloutFunction) != 'NULL_PTR')"!][!//

/* Redefine the function name of can transmit callback function */
#define CAN_LPDU_TRANSMIT_CALLOUT_FUNCTION(CanId, PduInfoPtr) \
                            [!"normalize-space(CanGeneral/CanLPduTransmitCalloutFunction)"!](CanId, PduInfoPtr)
[!ENDIF!][!//
/***************************************************************************************************
*                            User Definition Configuration
****************************************************************************************************/
#define CANFD_MODE_SUPPORT                           [!IF "$CanFD_Controller_Supported = 1"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_NOACK_ERR_SUPPORTED                      [!IF "CanGeneral/CanNoAckErrSupport = 'true'"!][!//
(STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_RXFIFO_POLLING_SUPPORT        [!WS "0"!][!IF "$RXFIFO_POLL_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_RXFIFO_INTERRUPT_SUPPORT      [!WS "0"!][!IF "$RXFIFO_INT_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_RX_POLLING_SUPPORT            [!WS "0"!][!IF "$RX_POLL_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_RX_INTERRUPT_SUPPORT          [!WS "0"!][!IF "$RX_INT_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_TX_POLLING_SUPPORT            [!WS "0"!][!IF "$TX_POLL_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_TX_INTERRUPT_SUPPORT          [!WS "0"!][!IF "$TX_INT_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_BUSOFF_POLLING_SUPPORT        [!WS "0"!][!IF "$BUSOFF_POLL_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_BUSOFF_INTERRUPT_SUPPORT      [!WS "0"!][!IF "$BUSOFF_INT_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_WAKEUP_POLLING_SUPPORT        [!WS "0"!][!IF "$WAKEUP_POLL_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//
#define CAN_CONTROLLER_WAKEUP_INTERRUPT_SUPPORT      [!WS "0"!][!IF "$WAKEUP_INT_FLAG = 1"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!CR!][!//

#define CAN_CONFIG_COUNT                             (1U)
#define CAN_USED_CONTROLLER_MAX_NUM                  ([!"num:i(count(CanConfigSet/CanController/*))"!]U)[!CR!][!//
#define CAN_USED_HOH_MB_MAX_NUM                      ([!"num:i(count(CanConfigSet/CanHardwareObject/*))"!]U)[!CR!][!//
#define CAN_NUMBER_OF_MAINFUNCTION_RW_PERIOD         ([!"num:i(count(CanGeneral/CanMainFunctionRWPeriods/*))"!]U)
#define CANFD_MODE_MAX_PAYLOAD_LENGTH                (64U)
#define CAN_STANDARD_MAX_PAYLOAD_LENGTH              (8U)

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
[!VAR "HOHUsedElementsNumToCorex" = "num:i(substring-after(text:split($TotalHOHUsedElementsNumToCorex)[num:i($CoreIndex + 1)], ':'))"!][!//
/* CAN Controller mapped to Core[!"$CoreIndex"!] */
#define CAN_USED_CONTROLLER_MAX_NUM_TO_CORE[!"$CoreIndex"!]         ([!IF "num:i($ControllerNumMapToCorex) = num:i(65535)"!]0[!ELSE!][!"num:i($ControllerNumMapToCorex + 1)"!][!ENDIF!]U)
#define CAN_USED_HOH_MB_MAX_NUM_TO_CORE[!"$CoreIndex"!]             ([!IF "num:i($HOHNumMapToCorex) = num:i(65535)"!]0[!ELSE!][!"num:i($HOHNumMapToCorex + 1)"!][!ENDIF!]U)
#define CAN_USED_HOH_ELEMENTS_MAX_NUM_TO_CORE[!"$CoreIndex"!]       ([!IF "num:i($HOHUsedElementsNumToCorex) = num:i(65535)"!]0[!ELSE!][!"num:i($HOHUsedElementsNumToCorex + 1)"!][!ENDIF!]U)
[!ENDIF!][!//
[!ENDFOR!][!//

/*
  Configuration: CanController Name
  Generate the macro definition for CanController name.
*/
[!LOOP "node:order(CanConfigSet/CanController/*, './CanControllerId')"!][!//
#ifndef CanConf_[!"node:name(..)"!]_[!"node:name(.)"!]
#define CanConf_[!"node:name(..)"!]_[!"node:name(.)"!][!WS "9"!]([!"node:value(./CanControllerId)"!]U)
#endif  /* CanConf_[!"node:name(..)"!]_[!"node:name(.)"!] */

[!ENDLOOP!][!//

/*
  Configuration: CanHardwareObject Name
  Generate the macro definition for CanHardwareObject name.
*/
[!LOOP "node:order(CanConfigSet/CanHardwareObject/*, './CanObjectId')"!][!//
#ifndef CanConf_[!"node:name(..)"!]_[!"node:name(.)"!]
#define CanConf_[!"node:name(..)"!]_[!"node:name(.)"!][!WS "10"!]((Can_HwHandleType)[!"num:i(./CanObjectId)"!]U)
#endif  /* CanConf_[!"node:name(..)"!]_[!"node:name(.)"!] */

[!ENDLOOP!]
/***************************************************************************************************
*                               Function Prototypes
***************************************************************************************************/
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : Can_MainFunction_Read_<CanMainFunctionRWPeriods.ShortName>
*
*   Service ID              : 0x08.
*
*   Description             : This function performs the polling of RX indications when
*                             Can_RxProcessing is set to POLLING.
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00226
****************************************************************************************************/
[!SELECT "as:modconf('Can')[1]/CanGeneral"!][!//
[!VAR "HwObjindx" = "num:i(0)"!][!//
[!VAR "HwObjMaxIndx" = "num:i(count(./CanMainFunctionRWPeriods/*))"!][!//
[!IF "$HwObjMaxIndx > 1"!][!//
[!FOR "HwObjindx" = "0" TO "$HwObjMaxIndx - 1"!][!//
/****************************************************************************************************
  MISRA C:2012 Rule 5.1:
  External identifi ers shall be distinct,In C99 the minimum requirement is that the first 31
  characters of external identifiers are significant.
****************************************************************************************************/
#define Can_MainFunction_Read_[!"$HwObjindx"!]()      Can_MainFunction_CommonRead([!"$HwObjindx"!]U)
[!ENDFOR!][!//
[!ENDIF!][!//

/****************************************************************************************************
*   Function Name           : Can_MainFunction_Read_<CanMainFunctionRWPeriods.ShortName>
*
*   Service ID              : 0x08.
*
*   Description             : This function performs the polling of RX indications when
*                             Can_RxProcessing is set to POLLING.
*                     
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : CAN_Driver must be uninitialized.
*
*   AUTOSAR_Requirement     : SWS_Can_00226
****************************************************************************************************/
[!VAR "HwObjMaxIndx" = "num:i(count(./CanMainFunctionRWPeriods/*))"!][!//
[!IF "$HwObjMaxIndx>1"!][!//
[!FOR "HwObjindx" = "0" TO "$HwObjMaxIndx - 1"!][!//
/****************************************************************************************************
  MISRA C:2012 Rule 5.1:
  External identifi ers shall be distinct,In C99 the minimum requirement is that the first 31
  characters of external identifiers are significant.
****************************************************************************************************/
#define Can_MainFunction_Write_[!"$HwObjindx"!]()      Can_MainFunction_CommonWrite([!"$HwObjindx"!]U)
[!ENDFOR!][!//
[!ENDIF!][!//
[!ENDSELECT!][!//

#endif /* CAN_CFG_H */

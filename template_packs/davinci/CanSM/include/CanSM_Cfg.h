[!SELECT "as:modconf('CanSM')[1]"!][!//
[!IF "not(node:exists(CanSMGeneral))"!][!ERROR "CanSMGeneral container is missing in CanSM configuration"!][!ENDIF!][!//
[!VAR "dummyKind" = "'SelfAssignment'"!][!//
[!IF "node:exists(as:modconf('vSet')[1]/vSetGeneral/vSetDummyStatementKind)"!][!//
[!VAR "dummyKind" = "node:value(as:modconf('vSet')[1]/vSetGeneral/vSetDummyStatementKind)"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral)"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/DummyStatement) and node:value(as:modconf('EcuC')[1]/EcucGeneral/DummyStatement) = 'false'"!][!//
[!VAR "dummyKind" = "'None'"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/DummyStatementKind)"!][!//
[!VAR "dummyKind" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/DummyStatementKind)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "atomicBitAccess" = "'STD_OFF'"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/AtomicBitAccessInBitfield) and node:value(as:modconf('EcuC')[1]/EcucGeneral/AtomicBitAccessInBitfield) = 'true'"!][!//
[!VAR "atomicBitAccess" = "'STD_ON'"!][!//
[!ENDIF!][!//
[!VAR "atomicVarAccess" = "'32u'"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/AtomicVariableAccess)"!][!//
[!VAR "avaVal" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/AtomicVariableAccess)"!][!//
[!IF "$avaVal = 'Atomic8BitAccess'"!][!//
[!VAR "atomicVarAccess" = "'8u'"!][!//
[!ELSEIF "$avaVal = 'Atomic16BitAccess'"!][!//
[!VAR "atomicVarAccess" = "'16u'"!][!//
[!ELSEIF "$avaVal = 'Atomic32BitAccess'"!][!//
[!VAR "atomicVarAccess" = "'32u'"!][!//
[!ELSEIF "$avaVal = 'Atomic64BitAccess'"!][!//
[!VAR "atomicVarAccess" = "'64u'"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "bitOrder" = "'LSB_to_MSB'"!][!//
[!IF "node:exists(as:modconf('vSet')[1]/vSetPlatform/vSetBitOrder)"!][!//
[!VAR "bitOrder" = "node:value(as:modconf('vSet')[1]/vSetPlatform/vSetBitOrder)"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/BitOrder)"!][!//
[!VAR "bitOrder" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/BitOrder)"!][!//
[!ENDIF!][!//
[!VAR "cansmProcessor" = "'CANSM_PROCESSOR_TONGXIN_THA6206'"!][!//
[!IF "ecu:has('CanSM.Processor')"!][!//
[!VAR "cansmProcessor" = "ecu:get('CanSM.Processor')"!][!//
[!ENDIF!][!//
[!VAR "cansmCompiler" = "'CANSM_COMP_LLVMHIGHTEC'"!][!//
[!IF "ecu:has('CanSM.Compiler')"!][!//
[!VAR "cansmCompiler" = "ecu:get('CanSM.Compiler')"!][!//
[!ENDIF!][!//
[!VAR "mainPeriod" = "0.01"!][!//
[!IF "node:exists(CanSMGeneral/CanSMMainFunctionTimePeriod) and (number(node:value(CanSMGeneral/CanSMMainFunctionTimePeriod)) > 0)"!][!//
[!VAR "mainPeriod" = "number(node:value(CanSMGeneral/CanSMMainFunctionTimePeriod))"!][!//
[!ENDIF!][!//
[!VAR "repMax" = "num:i(10)"!][!//
[!IF "node:exists(CanSMConfiguration/CanSMModeRequestRepetitionMax)"!][!//
[!VAR "repMax" = "num:i(node:value(CanSMConfiguration/CanSMModeRequestRepetitionMax))"!][!//
[!ENDIF!][!//
[!VAR "repTimeTicks" = "num:i(10)"!][!//
[!IF "node:exists(CanSMConfiguration/CanSMModeRequestRepetitionTime)"!][!//
[!VAR "repTimeTicks" = "num:i(round(number(node:value(CanSMConfiguration/CanSMModeRequestRepetitionTime)) div $mainPeriod))"!][!//
[!ENDIF!][!//
[!VAR "devErrDetect" = "'STD_ON'"!][!//
[!IF "node:exists(CanSMGeneral/CanSMDevErrorDetect) and (node:value(CanSMGeneral/CanSMDevErrorDetect) != 'true')"!][!//
[!VAR "devErrDetect" = "'STD_OFF'"!][!//
[!ENDIF!][!//
[!VAR "numChannels" = "num:i(0)"!][!//
[!IF "node:exists(CanSMConfiguration/CanSMManagerNetwork)"!][!//
[!VAR "numChannels" = "num:i(count(CanSMConfiguration/CanSMManagerNetwork/*))"!][!//
[!ENDIF!][!//
[!VAR "effChannels" = "$numChannels"!][!//
[!IF "$effChannels < 1"!][!//
[!VAR "effChannels" = "num:i(1)"!][!//
[!ENDIF!][!//
[!VAR "anyTrcv" = "'false'"!][!//
[!VAR "anyPolling" = "'false'"!][!//
[!VAR "singleBorCnt" = "num:i(5)"!][!//
[!VAR "singleBorL1" = "num:i(100)"!][!//
[!VAR "singleBorL2" = "num:i(300)"!][!//
[!VAR "singleBorTx" = "num:i(500)"!][!//
[!VAR "singleCtrlId" = "num:i(0)"!][!//
[!VAR "singleNetHandle" = "num:i(0)"!][!//
[!VAR "singleTrcvId" = "num:i(0)"!][!//
[!VAR "singleHasTrcv" = "'false'"!][!//
[!VAR "singlePolling" = "'false'"!][!//
[!VAR "chIdx" = "num:i(0)"!][!//
[!IF "node:exists(CanSMConfiguration/CanSMManagerNetwork)"!][!//
[!LOOP "CanSMConfiguration/CanSMManagerNetwork/*"!][!//
[!VAR "chBorCnt" = "num:i(5)"!][!//
[!IF "node:exists(CanSMBorCounterL1ToL2)"!][!VAR "chBorCnt" = "num:i(node:value(CanSMBorCounterL1ToL2))"!][!ENDIF!][!//
[!VAR "chBorL1" = "num:i(100)"!][!//
[!IF "node:exists(CanSMBorTimeL1)"!][!VAR "chBorL1" = "num:i(round(number(node:value(CanSMBorTimeL1)) div $mainPeriod))"!][!ENDIF!][!//
[!VAR "chBorL2" = "num:i(300)"!][!//
[!IF "node:exists(CanSMBorTimeL2)"!][!VAR "chBorL2" = "num:i(round(number(node:value(CanSMBorTimeL2)) div $mainPeriod))"!][!ENDIF!][!//
[!VAR "chBorTx" = "num:i(500)"!][!//
[!IF "node:exists(CanSMBorTimeTxEnsured)"!][!VAR "chBorTx" = "num:i(round(number(node:value(CanSMBorTimeTxEnsured)) div $mainPeriod))"!][!ENDIF!][!//
[!VAR "chPoll" = "'false'"!][!//
[!IF "node:exists(CanSMBorTxConfirmationPolling) and (node:value(CanSMBorTxConfirmationPolling) = 'true')"!][!//
[!VAR "chPoll" = "'true'"!][!//
[!VAR "anyPolling" = "'true'"!][!//
[!ENDIF!][!//
[!VAR "chCtrlId" = "num:i($chIdx)"!][!//
[!IF "node:exists(CanSMController/*[1]/CanSMControllerId) and (node:refvalid(CanSMController/*[1]/CanSMControllerId) = 'true')"!][!//
[!IF "node:exists(node:ref(CanSMController/*[1]/CanSMControllerId)/CanIfCtrlId)"!][!//
[!VAR "chCtrlId" = "num:i(node:value(node:ref(CanSMController/*[1]/CanSMControllerId)/CanIfCtrlId))"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "chNetHandle" = "num:i($chIdx)"!][!//
[!IF "node:exists(CanSMComMNetworkHandleRef) and (node:refvalid(CanSMComMNetworkHandleRef) = 'true')"!][!//
[!IF "node:exists(node:ref(CanSMComMNetworkHandleRef)/ComMChannelId)"!][!//
[!VAR "chNetHandle" = "num:i(node:value(node:ref(CanSMComMNetworkHandleRef)/ComMChannelId))"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "chHasTrcv" = "'false'"!][!//
[!VAR "chTrcvId" = "num:i(0)"!][!//
[!IF "node:exists(CanSMTransceiverId) and (node:refvalid(CanSMTransceiverId) = 'true')"!][!//
[!VAR "chHasTrcv" = "'true'"!][!//
[!VAR "anyTrcv" = "'true'"!][!//
[!IF "node:exists(node:ref(CanSMTransceiverId)/CanIfTrcvId)"!][!//
[!VAR "chTrcvId" = "num:i(node:value(node:ref(CanSMTransceiverId)/CanIfTrcvId))"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "$chIdx = 0"!][!//
[!VAR "singleBorCnt" = "$chBorCnt"!][!//
[!VAR "singleBorL1" = "$chBorL1"!][!//
[!VAR "singleBorL2" = "$chBorL2"!][!//
[!VAR "singleBorTx" = "$chBorTx"!][!//
[!VAR "singleCtrlId" = "$chCtrlId"!][!//
[!VAR "singleNetHandle" = "$chNetHandle"!][!//
[!VAR "singleTrcvId" = "$chTrcvId"!][!//
[!VAR "singleHasTrcv" = "$chHasTrcv"!][!//
[!VAR "singlePolling" = "$chPoll"!][!//
[!ENDIF!][!//
[!VAR "chIdx" = "num:i($chIdx + 1)"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  This file is part of the AUTOSAR BSW Configurator generated output.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  LICENSE
 *  -------------------------------------------------------------------------------------------------------------------
 *            Module: CanSM
 *           Program: MSR_Vector_SLP4
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CanSM_Cfg.h
 *********************************************************************************************************************/

#if !defined (CANSM_CFG_H)
# define CANSM_CFG_H

/* -----------------------------------------------------------------------------
    &&&~ Includes
 ----------------------------------------------------------------------------- */

#include "CanSM_Int.h"

/* -----------------------------------------------------------------------------
    &&&~ Precompile Defines
 ----------------------------------------------------------------------------- */

#define CANSM_VERSION_INFO_API                [!IF "node:exists(CanSMGeneral/CanSMVersionInfoApi) and (node:value(CanSMGeneral/CanSMVersionInfoApi) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define CANSM_BOR_CHECK_LEVEL                 [!IF "node:exists(CanSMGeneral/CanSMBorCheckLevel) and (node:value(CanSMGeneral/CanSMBorCheckLevel) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_BUSOFF_DELAY_FUNCTION           [!IF "node:exists(CanSMGeneral/CanSMBusOffDelayFunction) and (node:value(CanSMGeneral/CanSMBusOffDelayFunction) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_BUSOFF_END_INDICATION           [!IF "node:exists(CanSMGeneral/CanSMBusOffEndIndication) and (node:value(CanSMGeneral/CanSMBusOffEndIndication) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_CHANGE_BAUDRATE_API             [!IF "node:exists(CanSMGeneral/CanSmChangeBaudrateApi) and (node:value(CanSMGeneral/CanSmChangeBaudrateApi) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_SET_BAUDRATE_API                [!IF "node:exists(CanSMGeneral/CanSMSetBaudrateApi) and (node:value(CanSMGeneral/CanSMSetBaudrateApi) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_ECU_PASSIVE_MODE                [!IF "node:exists(CanSMGeneral/CanSMEcuPassiveMode) and (node:value(CanSMGeneral/CanSMEcuPassiveMode) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_PREVENT_BUSSLEEP_AT_STARTUP     [!IF "node:exists(CanSMGeneral/CanSMPreventBusSleepAtStartUp) and (node:value(CanSMGeneral/CanSMPreventBusSleepAtStartUp) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_SWIFT_TX_TIMEOUT_RECOVERY       [!IF "node:exists(CanSMGeneral/CanSMSwiftTxTimeoutRecovery) and (node:value(CanSMGeneral/CanSMSwiftTxTimeoutRecovery) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_EXPANDED_TX_TIMEOUT_RECOVERY    [!IF "node:exists(CanSMGeneral/CanSMExpandedTxTimeoutRecovery) and (node:value(CanSMGeneral/CanSMExpandedTxTimeoutRecovery) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_EXTENDED_RAM_CHECK              [!IF "node:exists(CanSMGeneral/CanSMExtendedRamCheck) and (node:value(CanSMGeneral/CanSMExtendedRamCheck) = 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]


/* -----------------------------------------------------------------------------
    &&&~ Defines
 ----------------------------------------------------------------------------- */

#ifndef CANSM_DEV_ERROR_DETECT
#define CANSM_DEV_ERROR_DETECT [!"$devErrDetect"!]
#endif
#ifndef CANSM_DEV_ERROR_REPORT
#define CANSM_DEV_ERROR_REPORT [!"$devErrDetect"!]
#endif
[!IF "$dummyKind = 'SelfAssignment'"!][!//
#ifndef CANSM_USE_DUMMY_STATEMENT
#define CANSM_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CANSM_DUMMY_STATEMENT
#define CANSM_DUMMY_STATEMENT(v) (v)=(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
#ifndef CANSM_DUMMY_STATEMENT_CONST
#define CANSM_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
[!ELSEIF "$dummyKind = 'VoidCast'"!][!//
#ifndef CANSM_USE_DUMMY_STATEMENT
#define CANSM_USE_DUMMY_STATEMENT STD_ON /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CANSM_DUMMY_STATEMENT
#define CANSM_DUMMY_STATEMENT(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
#ifndef CANSM_DUMMY_STATEMENT_CONST
#define CANSM_DUMMY_STATEMENT_CONST(v) (void)(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
[!ELSE!][!//
#ifndef CANSM_USE_DUMMY_STATEMENT
#define CANSM_USE_DUMMY_STATEMENT STD_OFF /* /MICROSAR/vSet/vSetGeneral/vSetDummyStatementKind */
#endif
#ifndef CANSM_DUMMY_STATEMENT
#define CANSM_DUMMY_STATEMENT(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
#ifndef CANSM_DUMMY_STATEMENT_CONST
#define CANSM_DUMMY_STATEMENT_CONST(v) /* PRQA S 3453 */ /* MD_MSR_FctLikeMacro */
#endif
[!ENDIF!][!//
#ifndef CANSM_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CANSM_ATOMIC_BIT_ACCESS_IN_BITFIELD [!"$atomicBitAccess"!] /* /MICROSAR/EcuC/EcucGeneral/AtomicBitAccessInBitfield */
#endif
#ifndef CANSM_ATOMIC_VARIABLE_ACCESS
#define CANSM_ATOMIC_VARIABLE_ACCESS [!"$atomicVarAccess"!] /* /MICROSAR/EcuC/EcucGeneral/AtomicVariableAccess */
#endif
#ifndef [!"$cansmProcessor"!]
#define [!"$cansmProcessor"!]
#endif
#ifndef [!"$cansmCompiler"!]
#define [!"$cansmCompiler"!]
#endif
#ifndef CANSM_GEN_GENERATOR_MSR
#define CANSM_GEN_GENERATOR_MSR
#endif
[!IF "$bitOrder = 'MSB_to_LSB'"!][!//
#ifndef CANSM_CPUTYPE_BITORDER_MSB2LSB
#define CANSM_CPUTYPE_BITORDER_MSB2LSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
[!ELSE!][!//
#ifndef CANSM_CPUTYPE_BITORDER_LSB2MSB
#define CANSM_CPUTYPE_BITORDER_LSB2MSB /* /MICROSAR/vSet/vSetPlatform/vSetBitOrder */
#endif
[!ENDIF!][!//
#ifndef CANSM_CONFIGURATION_VARIANT_PRECOMPILE
#define CANSM_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CANSM_CONFIGURATION_VARIANT_LINKTIME
#define CANSM_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CANSM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CANSM_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CANSM_CONFIGURATION_VARIANT
#define CANSM_CONFIGURATION_VARIANT CANSM_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CANSM_POSTBUILD_VARIANT_SUPPORT
#define CANSM_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

/* \trace SPEC-634 */
# define  CanSM_Dem_ReportErrorEvent(Index, eventStatus )


/* \trace SPEC-11294 */
#define CANSM_CFG_MAJOR_VERSION               (8u)
#define CANSM_CFG_MINOR_VERSION               (0u)


/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/**
  \defgroup  DataAccessMacros  Data Access Macros
  \brief  generated data access macros to abstract the generated data from the code to read and write CONST or VAR data.
  \{
*/
  /* PRQA S 3453 Macros_3453 */  /* MD_MSR_FctLikeMacro */
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
/**
  \defgroup  CanSMPCGetRootDataMacros  CanSM Get Root Data Macros (PRE_COMPILE)
  \brief  These macros are used to get data pointers of root data.
  \{
*/
#define CanSM_GetFinalMagicNumberOfPCConfig()
#define CanSM_GetInitDataHashCodeOfPCConfig()
/**
  \}
*/

/**
  \defgroup  CanSMPCGetConstantDuplicatedRootDataMacros  CanSM Get Constant Duplicated Root Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated by constance root data elements.
  \{
*/
#define CanSM_GetChannelConfigOfPCConfig()                                                          CanSM_ChannelConfig
#define CanSM_GetChannelVarRecordOfPCConfig()                                                       CanSM_ChannelVarRecord
#define CanSM_GetModeRequestRepetitionMaxOfPCConfig()                                               [!"$repMax"!]u
#define CanSM_GetModeRequestRepetitionTimeOfPCConfig()                                              [!"$repTimeTicks"!]u
#define CanSM_GetSizeOfChannelConfigOfPCConfig()                                                    [!"$effChannels"!]u
#define CanSM_GetSizeOfChannelVarRecordOfPCConfig()                                                 CanSM_GetSizeOfChannelConfigOfPCConfig()
/**
  \}
*/

/**
  \defgroup  CanSMPCGetDataMacros  CanSM Get Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read CONST and VAR data.
  \{
*/
[!IF "$effChannels > 1"!][!//
[!IF "$anyPolling = 'true'"!][!//
#define CanSM_IsBor_Tx_Confirmation_PollingOfChannelConfig(Index)                                   ((CanSM_GetChannelConfigOfPCConfig()[(Index)].Bor_Tx_Confirmation_PollingOfChannelConfig) != FALSE)
[!ELSE!][!//
#define CanSM_IsBor_Tx_Confirmation_PollingOfChannelConfig(Index)
[!ENDIF!][!//
[!ELSE!][!//
[!IF "$singlePolling = 'true'"!][!//
#define CanSM_IsBor_Tx_Confirmation_PollingOfChannelConfig(Index)                                   (((TRUE)) != FALSE)
[!ELSE!][!//
#define CanSM_IsBor_Tx_Confirmation_PollingOfChannelConfig(Index)
[!ENDIF!][!//
[!ENDIF!][!//
#define CanSM_IsPartial_Network_Trcv_SupportOfChannelConfig(Index)
#define CanSM_IsPartial_Network_Wakeup_FilterOfChannelConfig(Index)
#define CanSM_IsProdErrorDetect_BusOff_OfChannelConfig(Index)
#define CanSM_IsProdErrorDetect_ModeRequest_OfChannelConfig(Index)
#define CanSM_IsTrcv_InActive_AtAll_NonPNCannelsOfChannelConfig(Index)
#define CanSM_GetChannelVarRecord(Index)                                                            (CanSM_GetChannelVarRecordOfPCConfig()[(Index)])
/**
  \}
*/

/**
  \defgroup  CanSMPCGetDeduplicatedDataMacros  CanSM Get Deduplicated Data Macros (PRE_COMPILE)
  \brief  These macros can be used to read deduplicated data elements.
  \{
*/
[!IF "$effChannels > 1"!][!//
#define CanSM_GetBorCounterL1ToL2OfChannelConfig(Index)                                             (CanSM_GetChannelConfigOfPCConfig()[(Index)].BorCounterL1ToL2OfChannelConfig)
#define CanSM_GetBorTimeL1OfChannelConfig(Index)                                                    (CanSM_GetChannelConfigOfPCConfig()[(Index)].BorTimeL1OfChannelConfig)
#define CanSM_GetBorTimeL2OfChannelConfig(Index)                                                    (CanSM_GetChannelConfigOfPCConfig()[(Index)].BorTimeL2OfChannelConfig)
#define CanSM_GetBorTimeTxEnsuredOfChannelConfig(Index)                                             (CanSM_GetChannelConfigOfPCConfig()[(Index)].BorTimeTxEnsuredOfChannelConfig)
#define CanSM_GetControllerIdOfChannelConfig(Index)                                                 (CanSM_GetChannelConfigOfPCConfig()[(Index)].ControllerIdOfChannelConfig)
#define CanSM_GetDemEventId_BusOff_OfChannelConfig(Index)                                           (CanSM_GetChannelConfigOfPCConfig()[(Index)].DemEventId_BusOff_OfChannelConfig)
#define CanSM_GetDemEventId_ModeRequest_OfChannelConfig(Index)                                      (CanSM_GetChannelConfigOfPCConfig()[(Index)].DemEventId_ModeRequest_OfChannelConfig)
#define CanSM_GetNetworkHandleOfChannelConfig(Index)                                                (CanSM_GetChannelConfigOfPCConfig()[(Index)].NetworkHandleOfChannelConfig)
[!IF "$anyTrcv = 'true'"!][!//
#define CanSM_GetTransceiverIdOfChannelConfig(Index)                                                (CanSM_GetChannelConfigOfPCConfig()[(Index)].TransceiverIdOfChannelConfig)
#define CanSM_IsTransceiver_Channel_SupportOfChannelConfig(Index)                                   ((CanSM_GetChannelConfigOfPCConfig()[(Index)].Transceiver_Channel_SupportOfChannelConfig) != FALSE)
[!ELSE!][!//
#define CanSM_GetTransceiverIdOfChannelConfig(Index)
#define CanSM_IsTransceiver_Channel_SupportOfChannelConfig(Index)
[!ENDIF!][!//
[!ELSE!][!//
#define CanSM_GetBorCounterL1ToL2OfChannelConfig(Index)                                             [!"$singleBorCnt"!]u
#define CanSM_GetBorTimeL1OfChannelConfig(Index)                                                    [!"$singleBorL1"!]u
#define CanSM_GetBorTimeL2OfChannelConfig(Index)                                                    [!"$singleBorL2"!]u
#define CanSM_GetBorTimeTxEnsuredOfChannelConfig(Index)                                             [!"$singleBorTx"!]u
#define CanSM_GetControllerIdOfChannelConfig(Index)                                                 [!"$singleCtrlId"!]u
#define CanSM_GetDemEventId_BusOff_OfChannelConfig(Index)                                           0xFFu
#define CanSM_GetDemEventId_ModeRequest_OfChannelConfig(Index)                                      0xFFu
#define CanSM_GetNetworkHandleOfChannelConfig(Index)                                                [!"$singleNetHandle"!]u
[!IF "$singleHasTrcv = 'true'"!][!//
#define CanSM_GetTransceiverIdOfChannelConfig(Index)                                                [!"$singleTrcvId"!]u
#define CanSM_IsTransceiver_Channel_SupportOfChannelConfig(Index)                                   (((TRUE)) != FALSE)
[!ELSE!][!//
#define CanSM_GetTransceiverIdOfChannelConfig(Index)
#define CanSM_IsTransceiver_Channel_SupportOfChannelConfig(Index)
[!ENDIF!][!//
[!ENDIF!][!//
#define CanSM_GetFinalMagicNumber()
#define CanSM_GetInitDataHashCode()
#define CanSM_GetModeRequestRepetitionMax()                                                         CanSM_GetModeRequestRepetitionMaxOfPCConfig()
#define CanSM_GetModeRequestRepetitionTime()                                                        CanSM_GetModeRequestRepetitionTimeOfPCConfig()
#define CanSM_GetSizeOfChannelConfig()                                                              CanSM_GetSizeOfChannelConfigOfPCConfig()
#define CanSM_GetSizeOfChannelVarRecord()                                                           CanSM_GetSizeOfChannelVarRecordOfPCConfig()
/**
  \}
*/

/**
  \defgroup  CanSMPCSetDataMacros  CanSM Set Data Macros (PRE_COMPILE)
  \brief  These macros can be used to write data.
  \{
*/
#define CanSM_SetChannelVarRecord(Index, Value)                                                     CanSM_GetChannelVarRecordOfPCConfig()[(Index)] = (Value)
/**
  \}
*/

/**
  \defgroup  CanSMPCGetAddressOfDataMacros  CanSM Get Address Of Data Macros (PRE_COMPILE)
  \brief  These macros can be used to get the data addresses.
  \{
*/
#define CanSM_GetAddrChannelVarRecord(Index)                                                        (&CanSM_GetChannelVarRecord(Index))
/**
  \}
*/

/**
  \defgroup  CanSMPCHasMacros  CanSM Has Macros (PRE_COMPILE)
  \brief  These macros can be used to detect at runtime a deactivated piece of information.
  \{
*/
#define CanSM_HasChannelConfig()                                                                    (TRUE != FALSE)
#define CanSM_HasBorCounterL1ToL2OfChannelConfig()                                                  (TRUE != FALSE)
#define CanSM_HasBorTimeL1OfChannelConfig()                                                         (TRUE != FALSE)
#define CanSM_HasBorTimeL2OfChannelConfig()                                                         (TRUE != FALSE)
#define CanSM_HasBorTimeTxEnsuredOfChannelConfig()                                                  (TRUE != FALSE)
#define CanSM_HasBor_Tx_Confirmation_PollingOfChannelConfig()[!IF "$anyPolling = 'true'"!]                                        (TRUE != FALSE)[!ENDIF!]
#define CanSM_HasControllerIdOfChannelConfig()                                                      (TRUE != FALSE)
#define CanSM_HasDemEventId_BusOff_OfChannelConfig()                                                (TRUE != FALSE)
#define CanSM_HasDemEventId_ModeRequest_OfChannelConfig()                                           (TRUE != FALSE)
#define CanSM_HasNetworkHandleOfChannelConfig()                                                     (TRUE != FALSE)
#define CanSM_HasPartial_Network_Trcv_SupportOfChannelConfig()
#define CanSM_HasPartial_Network_Wakeup_FilterOfChannelConfig()
#define CanSM_HasProdErrorDetect_BusOff_OfChannelConfig()
#define CanSM_HasProdErrorDetect_ModeRequest_OfChannelConfig()
#define CanSM_HasTransceiverIdOfChannelConfig()[!IF "$anyTrcv = 'true'"!]                                                     (TRUE != FALSE)[!ENDIF!]
#define CanSM_HasTransceiver_Channel_SupportOfChannelConfig()[!IF "$anyTrcv = 'true'"!]                                       (TRUE != FALSE)[!ENDIF!]
#define CanSM_HasTrcv_InActive_AtAll_NonPNCannelsOfChannelConfig()
#define CanSM_HasChannelVarRecord()                                                                 (TRUE != FALSE)
#define CanSM_HasFinalMagicNumber()
#define CanSM_HasInitDataHashCode()
#define CanSM_HasModeRequestRepetitionMax()                                                         (TRUE != FALSE)
#define CanSM_HasModeRequestRepetitionTime()                                                        (TRUE != FALSE)
#define CanSM_HasSizeOfChannelConfig()                                                              (TRUE != FALSE)
#define CanSM_HasSizeOfChannelVarRecord()                                                           (TRUE != FALSE)
#define CanSM_HasPCConfig()                                                                         (TRUE != FALSE)
#define CanSM_HasChannelConfigOfPCConfig()                                                          (TRUE != FALSE)
#define CanSM_HasChannelVarRecordOfPCConfig()                                                       (TRUE != FALSE)
#define CanSM_HasFinalMagicNumberOfPCConfig()
#define CanSM_HasInitDataHashCodeOfPCConfig()
#define CanSM_HasModeRequestRepetitionMaxOfPCConfig()                                               (TRUE != FALSE)
#define CanSM_HasModeRequestRepetitionTimeOfPCConfig()                                              (TRUE != FALSE)
#define CanSM_HasSizeOfChannelConfigOfPCConfig()                                                    (TRUE != FALSE)
#define CanSM_HasSizeOfChannelVarRecordOfPCConfig()                                                 (TRUE != FALSE)
/**
  \}
*/

/**
  \defgroup  CanSMPCIncrementDataMacros  CanSM Increment Data Macros (PRE_COMPILE)
  \brief  These macros can be used to increment VAR data with numerical nature.
  \{
*/
#define CanSM_IncChannelVarRecord(Index)                                                            CanSM_GetChannelVarRecord(Index)++
/**
  \}
*/

/**
  \defgroup  CanSMPCDecrementDataMacros  CanSM Decrement Data Macros (PRE_COMPILE)
  \brief  These macros can be used to decrement VAR data with numerical nature.
  \{
*/
#define CanSM_DecChannelVarRecord(Index)                                                            CanSM_GetChannelVarRecord(Index)--
/**
  \}
*/

/**
  \defgroup  CanSMPCAddDataMacros  CanSM Add Data Macros (PRE_COMPILE)
  \brief  These macros can be used to add VAR data with numerical nature.
  \{
*/
#define CanSM_AddChannelVarRecord(Index, Value)                                                     CanSM_SetChannelVarRecord(Index, (CanSM_GetChannelVarRecord(Index) + Value))
/**
  \}
*/

/**
  \defgroup  CanSMPCSubstractDataMacros  CanSM Substract Data Macros (PRE_COMPILE)
  \brief  These macros can be used to substract VAR data with numerical nature.
  \{
*/
#define CanSM_SubChannelVarRecord(Index, Value)                                                     CanSM_SetChannelVarRecord(Index, (CanSM_GetChannelVarRecord(Index) - Value))
/**
  \}
*/

  /* PRQA L:Macros_3453 */
/**
  \}
*/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
/**
  \defgroup  CanSMPCDataSwitches  CanSM Data Switches  (PRE_COMPILE)
  \brief  These defines are used to deactivate data and their processing.
  \{
*/
#define CANSM_CHANNELCONFIG                                                                         STD_ON
#define CANSM_BORCOUNTERL1TOL2OFCHANNELCONFIG                                                       STD_ON
#define CANSM_BORTIMEL1OFCHANNELCONFIG                                                              STD_ON
#define CANSM_BORTIMEL2OFCHANNELCONFIG                                                              STD_ON
#define CANSM_BORTIMETXENSUREDOFCHANNELCONFIG                                                       STD_ON
#define CANSM_BOR_TX_CONFIRMATION_POLLINGOFCHANNELCONFIG                                            [!IF "$anyPolling = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_CONTROLLERIDOFCHANNELCONFIG                                                           STD_ON
#define CANSM_DEMEVENTID_BUSOFF_OFCHANNELCONFIG                                                     STD_ON
#define CANSM_DEMEVENTID_MODEREQUEST_OFCHANNELCONFIG                                                STD_ON
#define CANSM_NETWORKHANDLEOFCHANNELCONFIG                                                          STD_ON
#define CANSM_PARTIAL_NETWORK_TRCV_SUPPORTOFCHANNELCONFIG                                           STD_OFF
#define CANSM_PARTIAL_NETWORK_WAKEUP_FILTEROFCHANNELCONFIG                                          STD_OFF
#define CANSM_PRODERRORDETECT_BUSOFF_OFCHANNELCONFIG                                                STD_OFF
#define CANSM_PRODERRORDETECT_MODEREQUEST_OFCHANNELCONFIG                                           STD_OFF
#define CANSM_TRANSCEIVERIDOFCHANNELCONFIG                                                          [!IF "$anyTrcv = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_TRANSCEIVER_CHANNEL_SUPPORTOFCHANNELCONFIG                                            [!IF "$anyTrcv = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_TRCV_INACTIVE_ATALL_NONPNCANNELSOFCHANNELCONFIG                                       STD_OFF
#define CANSM_CHANNELVARRECORD                                                                      STD_ON
#define CANSM_FINALMAGICNUMBER                                                                      STD_OFF
#define CANSM_INITDATAHASHCODE                                                                      STD_OFF
#define CANSM_MODEREQUESTREPETITIONMAX                                                              STD_ON
#define CANSM_MODEREQUESTREPETITIONTIME                                                             STD_ON
#define CANSM_SIZEOFCHANNELCONFIG                                                                   STD_ON
#define CANSM_SIZEOFCHANNELVARRECORD                                                                STD_ON
#define CANSM_PCCONFIG                                                                              STD_ON
#define CANSM_CHANNELCONFIGOFPCCONFIG                                                               STD_ON
#define CANSM_CHANNELVARRECORDOFPCCONFIG                                                            STD_ON
#define CANSM_FINALMAGICNUMBEROFPCCONFIG                                                            STD_OFF
#define CANSM_INITDATAHASHCODEOFPCCONFIG                                                            STD_OFF
#define CANSM_MODEREQUESTREPETITIONMAXOFPCCONFIG                                                    STD_ON
#define CANSM_MODEREQUESTREPETITIONTIMEOFPCCONFIG                                                   STD_ON
#define CANSM_SIZEOFCHANNELCONFIGOFPCCONFIG                                                         STD_ON
#define CANSM_SIZEOFCHANNELVARRECORDOFPCCONFIG                                                      STD_ON
/**
  \}
*/

/**
  \defgroup  CanSMPCNoReferenceDefines  CanSM No Reference Defines (PRE_COMPILE)
  \brief  These defines are used to indicate unused indexes in data relations.
  \{
*/
#define CANSM_NO_BORCOUNTERL1TOL2OFCHANNELCONFIG                                                    255u
#define CANSM_NO_BORTIMEL1OFCHANNELCONFIG                                                           255u
#define CANSM_NO_BORTIMEL2OFCHANNELCONFIG                                                           65535u
#define CANSM_NO_BORTIMETXENSUREDOFCHANNELCONFIG                                                    65535u
#define CANSM_NO_CONTROLLERIDOFCHANNELCONFIG                                                        255u
#define CANSM_NO_NETWORKHANDLEOFCHANNELCONFIG                                                       255u
#define CANSM_NO_TRANSCEIVERIDOFCHANNELCONFIG                                                       255u
/**
  \}
*/

/**
  \defgroup  CanSMPCIsDefDefines  CanSM Is Define Defines (PRE_COMPILE)
  \brief  These defines are used to check if data elements in tables are always defined with the same value.
  \{
*/
[!IF "$effChannels > 1"!][!//
#define CANSM_ISDEF_BORCOUNTERL1TOL2OFCHANNELCONFIG                                                 STD_OFF
#define CANSM_ISDEF_BORTIMEL1OFCHANNELCONFIG                                                        STD_OFF
#define CANSM_ISDEF_BORTIMEL2OFCHANNELCONFIG                                                        STD_OFF
#define CANSM_ISDEF_BORTIMETXENSUREDOFCHANNELCONFIG                                                 STD_OFF
#define CANSM_ISDEF_BOR_TX_CONFIRMATION_POLLINGOFCHANNELCONFIG                                      STD_OFF
#define CANSM_ISDEF_CONTROLLERIDOFCHANNELCONFIG                                                     STD_OFF
#define CANSM_ISDEF_DEMEVENTID_BUSOFF_OFCHANNELCONFIG                                               STD_OFF
#define CANSM_ISDEF_DEMEVENTID_MODEREQUEST_OFCHANNELCONFIG                                          STD_OFF
#define CANSM_ISDEF_NETWORKHANDLEOFCHANNELCONFIG                                                    STD_OFF
#define CANSM_ISDEF_PARTIAL_NETWORK_TRCV_SUPPORTOFCHANNELCONFIG                                     STD_OFF
#define CANSM_ISDEF_PARTIAL_NETWORK_WAKEUP_FILTEROFCHANNELCONFIG                                    STD_OFF
#define CANSM_ISDEF_PRODERRORDETECT_BUSOFF_OFCHANNELCONFIG                                          STD_OFF
#define CANSM_ISDEF_PRODERRORDETECT_MODEREQUEST_OFCHANNELCONFIG                                     STD_OFF
#define CANSM_ISDEF_TRANSCEIVERIDOFCHANNELCONFIG                                                    STD_OFF
#define CANSM_ISDEF_TRANSCEIVER_CHANNEL_SUPPORTOFCHANNELCONFIG                                      STD_OFF
#define CANSM_ISDEF_TRCV_INACTIVE_ATALL_NONPNCANNELSOFCHANNELCONFIG                                 STD_OFF
#define CANSM_ISDEF_CHANNELCONFIGOFPCCONFIG                                                         STD_ON
#define CANSM_ISDEF_CHANNELVARRECORDOFPCCONFIG                                                      STD_ON
#define CANSM_ISDEF_FINALMAGICNUMBEROFPCCONFIG                                                      STD_OFF
#define CANSM_ISDEF_INITDATAHASHCODEOFPCCONFIG                                                      STD_OFF
[!ELSE!][!//
#define CANSM_ISDEF_BORCOUNTERL1TOL2OFCHANNELCONFIG                                                 STD_ON
#define CANSM_ISDEF_BORTIMEL1OFCHANNELCONFIG                                                        STD_ON
#define CANSM_ISDEF_BORTIMEL2OFCHANNELCONFIG                                                        STD_ON
#define CANSM_ISDEF_BORTIMETXENSUREDOFCHANNELCONFIG                                                 STD_ON
#define CANSM_ISDEF_BOR_TX_CONFIRMATION_POLLINGOFCHANNELCONFIG                                      [!IF "$singlePolling = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_ISDEF_CONTROLLERIDOFCHANNELCONFIG                                                     STD_ON
#define CANSM_ISDEF_DEMEVENTID_BUSOFF_OFCHANNELCONFIG                                               STD_ON
#define CANSM_ISDEF_DEMEVENTID_MODEREQUEST_OFCHANNELCONFIG                                          STD_ON
#define CANSM_ISDEF_NETWORKHANDLEOFCHANNELCONFIG                                                    STD_ON
#define CANSM_ISDEF_PARTIAL_NETWORK_TRCV_SUPPORTOFCHANNELCONFIG                                     STD_OFF
#define CANSM_ISDEF_PARTIAL_NETWORK_WAKEUP_FILTEROFCHANNELCONFIG                                    STD_OFF
#define CANSM_ISDEF_PRODERRORDETECT_BUSOFF_OFCHANNELCONFIG                                          STD_OFF
#define CANSM_ISDEF_PRODERRORDETECT_MODEREQUEST_OFCHANNELCONFIG                                     STD_OFF
#define CANSM_ISDEF_TRANSCEIVERIDOFCHANNELCONFIG                                                    [!IF "$singleHasTrcv = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_ISDEF_TRANSCEIVER_CHANNEL_SUPPORTOFCHANNELCONFIG                                      [!IF "$singleHasTrcv = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANSM_ISDEF_TRCV_INACTIVE_ATALL_NONPNCANNELSOFCHANNELCONFIG                                 STD_OFF
#define CANSM_ISDEF_CHANNELCONFIGOFPCCONFIG                                                         STD_ON
#define CANSM_ISDEF_CHANNELVARRECORDOFPCCONFIG                                                      STD_ON
#define CANSM_ISDEF_FINALMAGICNUMBEROFPCCONFIG                                                      STD_OFF
#define CANSM_ISDEF_INITDATAHASHCODEOFPCCONFIG                                                      STD_OFF
[!ENDIF!][!//
/**
  \}
*/

/**
  \defgroup  CanSMPCEqualsAlwaysToDefines  CanSM Equals Always To Defines (PRE_COMPILE)
  \brief  If all values in a CONST array or an element in a CONST array of structs are equal, the define contains the always equals value.
  \{
*/
[!IF "$effChannels > 1"!][!//
#define CANSM_EQ2_BORCOUNTERL1TOL2OFCHANNELCONFIG
#define CANSM_EQ2_BORTIMEL1OFCHANNELCONFIG
#define CANSM_EQ2_BORTIMEL2OFCHANNELCONFIG
#define CANSM_EQ2_BORTIMETXENSUREDOFCHANNELCONFIG
#define CANSM_EQ2_BOR_TX_CONFIRMATION_POLLINGOFCHANNELCONFIG
#define CANSM_EQ2_CONTROLLERIDOFCHANNELCONFIG
#define CANSM_EQ2_DEMEVENTID_BUSOFF_OFCHANNELCONFIG
#define CANSM_EQ2_DEMEVENTID_MODEREQUEST_OFCHANNELCONFIG
#define CANSM_EQ2_NETWORKHANDLEOFCHANNELCONFIG
#define CANSM_EQ2_PARTIAL_NETWORK_TRCV_SUPPORTOFCHANNELCONFIG
#define CANSM_EQ2_PARTIAL_NETWORK_WAKEUP_FILTEROFCHANNELCONFIG
#define CANSM_EQ2_PRODERRORDETECT_BUSOFF_OFCHANNELCONFIG
#define CANSM_EQ2_PRODERRORDETECT_MODEREQUEST_OFCHANNELCONFIG
#define CANSM_EQ2_TRANSCEIVERIDOFCHANNELCONFIG
#define CANSM_EQ2_TRANSCEIVER_CHANNEL_SUPPORTOFCHANNELCONFIG
#define CANSM_EQ2_TRCV_INACTIVE_ATALL_NONPNCANNELSOFCHANNELCONFIG
[!ELSE!][!//
#define CANSM_EQ2_BORCOUNTERL1TOL2OFCHANNELCONFIG                                                   [!"$singleBorCnt"!]u
#define CANSM_EQ2_BORTIMEL1OFCHANNELCONFIG                                                          [!"$singleBorL1"!]u
#define CANSM_EQ2_BORTIMEL2OFCHANNELCONFIG                                                          [!"$singleBorL2"!]u
#define CANSM_EQ2_BORTIMETXENSUREDOFCHANNELCONFIG                                                   [!"$singleBorTx"!]u
#define CANSM_EQ2_BOR_TX_CONFIRMATION_POLLINGOFCHANNELCONFIG[!IF "$singlePolling = 'true'"!]                                        TRUE[!ENDIF!]
#define CANSM_EQ2_CONTROLLERIDOFCHANNELCONFIG                                                       [!"$singleCtrlId"!]u
#define CANSM_EQ2_DEMEVENTID_BUSOFF_OFCHANNELCONFIG                                                 0xFFu
#define CANSM_EQ2_DEMEVENTID_MODEREQUEST_OFCHANNELCONFIG                                            0xFFu
#define CANSM_EQ2_NETWORKHANDLEOFCHANNELCONFIG                                                      [!"$singleNetHandle"!]u
#define CANSM_EQ2_PARTIAL_NETWORK_TRCV_SUPPORTOFCHANNELCONFIG
#define CANSM_EQ2_PARTIAL_NETWORK_WAKEUP_FILTEROFCHANNELCONFIG
#define CANSM_EQ2_PRODERRORDETECT_BUSOFF_OFCHANNELCONFIG
#define CANSM_EQ2_PRODERRORDETECT_MODEREQUEST_OFCHANNELCONFIG
#define CANSM_EQ2_TRANSCEIVERIDOFCHANNELCONFIG[!IF "$singleHasTrcv = 'true'"!]                                                      [!"$singleTrcvId"!]u[!ENDIF!]
#define CANSM_EQ2_TRANSCEIVER_CHANNEL_SUPPORTOFCHANNELCONFIG[!IF "$singleHasTrcv = 'true'"!]                                        TRUE[!ENDIF!]
#define CANSM_EQ2_TRCV_INACTIVE_ATALL_NONPNCANNELSOFCHANNELCONFIG
[!ENDIF!][!//
#define CANSM_EQ2_CHANNELCONFIGOFPCCONFIG                                                           CanSM_ChannelConfig
#define CANSM_EQ2_CHANNELVARRECORDOFPCCONFIG                                                        CanSM_ChannelVarRecord
#define CANSM_EQ2_FINALMAGICNUMBEROFPCCONFIG
#define CANSM_EQ2_INITDATAHASHCODEOFPCCONFIG
/**
  \}
*/

/**
  \defgroup  CanSMPCSymbolicInitializationPointers  CanSM Symbolic Initialization Pointers (PRE_COMPILE)
  \brief  Symbolic initialization pointers to be used in the call of a preinit or init function.
  \{
*/
#define CanSM_Config_Ptr                                                                            NULL_PTR
/**
  \}
*/

/**
  \defgroup  CanSMPCInitializationSymbols  CanSM Initialization Symbols (PRE_COMPILE)
  \brief  Symbolic initialization pointers which may be used in the call of a preinit or init function.
  \{
*/
#define CanSM_Config                                                                                NULL_PTR
/**
  \}
*/

/**
  \defgroup  CanSMPCGeneral  CanSM General (PRE_COMPILE)
  \brief  General constant defines not associated with a group of defines.
  \{
*/
#define CANSM_CHECK_INIT_POINTER                                                                    STD_OFF
#define CANSM_FINAL_MAGIC_NUMBER                                                                    0x8C1Eu
#define CANSM_INDIVIDUAL_POSTBUILD                                                                  STD_OFF
#define CANSM_INIT_DATA                                                                             CANSM_CONST
#define CANSM_INIT_DATA_HASH_CODE                                                                   337218771
#define CANSM_USE_ECUM_BSW_ERROR_HOOK                                                               STD_OFF
#define CANSM_USE_INIT_POINTER                                                                      STD_OFF
/**
  \}
*/


/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL SIMPLE DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**
  \defgroup  CanSMPCIterableTypes  CanSM Iterable Types (PRE_COMPILE)
  \brief  These type definitions are used to iterate over an array with least processor cycles for variable access as possible.
  \{
*/
typedef uint8 CanSM_SizeOfChannelConfigType;
typedef uint8 CanSM_SizeOfChannelVarRecordType;
typedef uint8_least CanSM_ChannelConfigIterType;
typedef CanSM_ChannelConfigIterType CanSM_ChannelVarRecordIterType;
/**
  \}
*/

/**
  \defgroup  CanSMPCValueTypes  CanSM Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value based data representations.
  \{
*/
typedef uint8 CanSM_BorCounterL1ToL2OfChannelConfigType;
typedef uint8 CanSM_BorTimeL1OfChannelConfigType;
typedef uint16 CanSM_BorTimeL2OfChannelConfigType;
typedef uint16 CanSM_BorTimeTxEnsuredOfChannelConfigType;
typedef uint8 CanSM_ControllerIdOfChannelConfigType;
typedef uint8 CanSM_NetworkHandleOfChannelConfigType;
typedef uint8 CanSM_TransceiverIdOfChannelConfigType;
typedef boolean CanSM_Transceiver_Channel_SupportOfChannelConfigType;
typedef uint8 CanSM_ModeRequestRepetitionMaxType;
typedef uint8 CanSM_ModeRequestRepetitionTimeType;
/**
  \}
*/

/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL COMPLEX DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
/**
  \defgroup  CanSMPCStructTypes  CanSM Struct Types (PRE_COMPILE)
  \brief  These type definitions are used for structured data representations.
  \{
*/
[!IF "$effChannels > 1"!][!//
typedef struct sCanSM_ChannelConfigType
{
  CanSM_BorTimeL2OfChannelConfigType BorTimeL2OfChannelConfig;
  CanSM_BorTimeTxEnsuredOfChannelConfigType BorTimeTxEnsuredOfChannelConfig;
  CanSM_BorCounterL1ToL2OfChannelConfigType BorCounterL1ToL2OfChannelConfig;
  CanSM_BorTimeL1OfChannelConfigType BorTimeL1OfChannelConfig;
[!IF "$anyPolling = 'true'"!][!//
  boolean Bor_Tx_Confirmation_PollingOfChannelConfig;
[!ENDIF!][!//
  CanSM_ControllerIdOfChannelConfigType ControllerIdOfChannelConfig;
  uint8 DemEventId_BusOff_OfChannelConfig;
  uint8 DemEventId_ModeRequest_OfChannelConfig;
  CanSM_NetworkHandleOfChannelConfigType NetworkHandleOfChannelConfig;
[!IF "$anyTrcv = 'true'"!][!//
  CanSM_TransceiverIdOfChannelConfigType TransceiverIdOfChannelConfig;
  CanSM_Transceiver_Channel_SupportOfChannelConfigType Transceiver_Channel_SupportOfChannelConfig;
[!ENDIF!][!//
} CanSM_ChannelConfigType;
[!ELSE!][!//
typedef struct sCanSM_ChannelConfigType
{
  uint8 CanSM_ChannelConfigNeverUsed;
} CanSM_ChannelConfigType;
[!ENDIF!][!//
/**
  \}
*/

/**
  \defgroup  CanSMPCRootPointerTypes  CanSM Root Pointer Types (PRE_COMPILE)
  \brief  These type definitions are used to point from the config struct to the data instances.
  \{
*/
typedef P2CONST(CanSM_ChannelConfigType, TYPEDEF, CANSM_CONST) CanSM_ChannelConfigPtrType;
typedef P2VAR(CanSM_ChannelVarRecordType, TYPEDEF, CANSM_VAR_NO_INIT) CanSM_ChannelVarRecordPtrType;
/**
  \}
*/

/**
  \defgroup  CanSMPCRootValueTypes  CanSM Root Value Types (PRE_COMPILE)
  \brief  These type definitions are used for value representations in root arrays.
  \{
*/
typedef struct sCanSM_PCConfigType
{
  uint8 CanSM_PCConfigNeverUsed;
} CanSM_PCConfigType;

typedef CanSM_PCConfigType CanSM_ConfigType;
/**
  \}
*/


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
[!IF "$effChannels > 1"!][!//
#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanSM_ChannelConfigType, CANSM_CONST) CanSM_ChannelConfig[[!"$effChannels"!]];
#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!ENDIF!][!//
#define CANSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanSM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(CanSM_ChannelVarRecordType, CANSM_VAR_NO_INIT) CanSM_ChannelVarRecord[[!"$effChannels"!]];
#define CANSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanSM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */


#endif  /* CANSM_CFG_H */
[!ENDSELECT!]

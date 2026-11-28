[!SELECT "as:modconf('CanIf')[1]"!][!//
[!IF "not(node:exists(CanIfPrivateCfg)) or not(node:exists(CanIfPublicCfg))"!][!ERROR "CanIfPrivateCfg or CanIfPublicCfg missing in CanIf configuration"!][!ENDIF!][!//
[!VAR "dummyKind" = "'SelfAssignment'"!][!//
[!IF "node:exists(as:modconf('vSet')[1]/vSetGeneral/vSetDummyStatementKind)"!][!//
[!VAR "dummyKind" = "node:value(as:modconf('vSet')[1]/vSetGeneral/vSetDummyStatementKind)"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral)"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/DummyStatement) and node:value(as:modconf('EcuC')[1]/EcucGeneral/DummyStatement) = 'false'"!][!//
[!VAR "dummyKind" = "'None'"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/DummyStatementKind)"!][!VAR "dummyKind" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/DummyStatementKind)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "atomicBitAccess" = "'STD_OFF'"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/AtomicBitAccessInBitfield) and node:value(as:modconf('EcuC')[1]/EcucGeneral/AtomicBitAccessInBitfield) = 'true'"!][!VAR "atomicBitAccess" = "'STD_ON'"!][!ENDIF!][!//
[!VAR "atomicVarAccess" = "'32u'"!][!//
[!IF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/AtomicVariableAccess)"!][!//
[!VAR "avaVal" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/AtomicVariableAccess)"!][!//
[!IF "$avaVal = 'Atomic8BitAccess'"!][!VAR "atomicVarAccess" = "'8u'"!][!//
[!ELSEIF "$avaVal = 'Atomic16BitAccess'"!][!VAR "atomicVarAccess" = "'16u'"!][!//
[!ELSEIF "$avaVal = 'Atomic32BitAccess'"!][!VAR "atomicVarAccess" = "'32u'"!][!//
[!ELSEIF "$avaVal = 'Atomic64BitAccess'"!][!VAR "atomicVarAccess" = "'64u'"!][!ENDIF!][!//
[!ENDIF!][!//
[!VAR "bitOrder" = "'LSB_to_MSB'"!][!//
[!IF "node:exists(as:modconf('vSet')[1]/vSetPlatform/vSetBitOrder)"!][!VAR "bitOrder" = "node:value(as:modconf('vSet')[1]/vSetPlatform/vSetBitOrder)"!][!//
[!ELSEIF "node:exists(as:modconf('EcuC')[1]/EcucGeneral/BitOrder)"!][!VAR "bitOrder" = "node:value(as:modconf('EcuC')[1]/EcucGeneral/BitOrder)"!][!ENDIF!][!//
[!VAR "canifProcessor" = "'CANIF_PROCESSOR_TONGXIN_THA6206'"!][!//
[!IF "ecu:has('CanIf.Processor')"!][!VAR "canifProcessor" = "ecu:get('CanIf.Processor')"!][!ENDIF!][!//
[!VAR "canifCompiler" = "'CANIF_COMP_LLVMHIGHTEC'"!][!//
[!IF "ecu:has('CanIf.Compiler')"!][!VAR "canifCompiler" = "ecu:get('CanIf.Compiler')"!][!ENDIF!][!//
[!VAR "trcvVendorId" = "'30'"!][!//
[!VAR "trcvVendorInfix" = "'Tle9255'"!][!//
[!IF "node:exists(as:modconf('CanTrcv')[1]/CommonPublishedInformation/VendorApiInfix)"!][!//
[!VAR "vInf" = "string:trim(node:value(as:modconf('CanTrcv')[1]/CommonPublishedInformation/VendorApiInfix))"!][!//
[!IF "string-length($vInf) > 0"!][!VAR "trcvVendorInfix" = "$vInf"!][!ENDIF!][!//
[!IF "node:exists(as:modconf('CanTrcv')[1]/CommonPublishedInformation/VendorId)"!][!VAR "trcvVendorId" = "string(num:i(node:value(as:modconf('CanTrcv')[1]/CommonPublishedInformation/VendorId)))"!][!ENDIF!][!//
[!ENDIF!][!//
[!VAR "trcvPrefix" = "concat('CanTrcv_', $trcvVendorId, '_', $trcvVendorInfix)"!][!//
[!VAR "canifTrcvCbPrefix" = "concat('CanIf_', $trcvVendorId, '_', $trcvVendorInfix)"!][!//
[!VAR "txBuffering" = "'STD_OFF'"!][!//
[!IF "node:exists(CanIfPublicCfg/CanIfPublicTxBuffering) and node:value(CanIfPublicCfg/CanIfPublicTxBuffering) = 'true'"!][!VAR "txBuffering" = "'STD_ON'"!][!ENDIF!][!//
[!VAR "prioByCanId" = "'STD_OFF'"!][!//
[!IF "node:exists(CanIfPrivateCfg/CanIfTxBufferPrioByCanIdSupport) and node:value(CanIfPrivateCfg/CanIfTxBufferPrioByCanIdSupport) = 'true'"!][!VAR "prioByCanId" = "'STD_ON'"!][!ENDIF!][!//
[!VAR "trcvHandling" = "'STD_OFF'"!][!//
[!IF "node:exists(CanIfPrivateCfg/CanIfTransceiverHandling) and node:value(CanIfPrivateCfg/CanIfTransceiverHandling) = 'true'"!][!VAR "trcvHandling" = "'STD_ON'"!][!ENDIF!][!//
[!VAR "devErr" = "'STD_ON'"!][!//
[!IF "node:exists(CanIfPublicCfg/CanIfPublicDevErrorDetect) and node:value(CanIfPublicCfg/CanIfPublicDevErrorDetect) != 'true'"!][!VAR "devErr" = "'STD_OFF'"!][!ENDIF!][!//
[!VAR "numCtrls" = "num:i(count(CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*))"!][!//
[!IF "$numCtrls < 1"!][!VAR "numCtrls" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numTrcvs" = "num:i(count(CanIfTrcvDrvCfg/*/CanIfTrcvCfg/*))"!][!//
[!VAR "effTrcvs" = "$numTrcvs"!][!//
[!IF "$effTrcvs < 1"!][!VAR "effTrcvs" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numBuffers" = "num:i(count(CanIfInitCfg/CanIfBufferCfg/*))"!][!//
[!IF "$numBuffers < 1"!][!VAR "numBuffers" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numHth" = "num:i(count(CanIfInitCfg/CanIfInitHohCfg/*/CanIfHthCfg/*))"!][!//
[!VAR "numHrh" = "num:i(count(CanIfInitCfg/CanIfInitHohCfg/*/CanIfHrhCfg/*))"!][!//
[!VAR "numMailboxes" = "num:i($numHth + $numHrh)"!][!//
[!IF "$numMailboxes < 1"!][!VAR "numMailboxes" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numRxPdus" = "num:i(count(CanIfInitCfg/CanIfRxPduCfg/*))"!][!//
[!VAR "effRxPdus" = "$numRxPdus"!][!//
[!IF "$effRxPdus < 1"!][!VAR "effRxPdus" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numTxPdus" = "num:i(count(CanIfInitCfg/CanIfTxPduCfg/*))"!][!//
[!IF "$numTxPdus < 1"!][!VAR "numTxPdus" = "num:i(1)"!][!ENDIF!][!//
[!VAR "rxCbkList" = "'|'"!][!//
[!VAR "rxCbkCount" = "num:i(1)"!][!//
[!IF "node:exists(CanIfInitCfg/CanIfRxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfRxPduCfg/*, 'CanIfRxPduId')"!][!//
[!IF "node:exists(CanIfRxPduUserRxIndicationName)"!][!//
[!VAR "fn" = "string:trim(node:value(CanIfRxPduUserRxIndicationName))"!][!//
[!IF "string-length($fn) > 0 and not(contains($rxCbkList, concat('|', $fn, '|')))"!][!//
[!VAR "rxCbkList" = "concat($rxCbkList, $fn, '|')"!][!//
[!VAR "rxCbkCount" = "num:i($rxCbkCount + 1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!VAR "txCbkList" = "'|'"!][!//
[!VAR "txCbkCount" = "num:i(1)"!][!//
[!IF "node:exists(CanIfInitCfg/CanIfTxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfTxPduCfg/*, 'CanIfTxPduId')"!][!//
[!IF "node:exists(CanIfTxPduUserTxConfirmationName)"!][!//
[!VAR "fn" = "string:trim(node:value(CanIfTxPduUserTxConfirmationName))"!][!//
[!IF "string-length($fn) > 0 and not(contains($txCbkList, concat('|', $fn, '|')))"!][!//
[!VAR "txCbkList" = "concat($txCbkList, $fn, '|')"!][!//
[!VAR "txCbkCount" = "num:i($txCbkCount + 1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!VAR "txFlagsWords" = "num:i(($numTxPdus + 31) div 32)"!][!//
[!IF "$txFlagsWords < 1"!][!VAR "txFlagsWords" = "num:i(1)"!][!ENDIF!][!//
#if !defined(CANIF_CFG_H)
#define CANIF_CFG_H

#include "Can.h"

#define CANIF_CFG5_VERSION                                 0x0700u
#define CANIF_CFG5_RELEASE_VERSION                         0x00u
#define IF_ASRIFCAN_GENTOOL_CFG5_MAJOR_VERSION             0x07u
#define IF_ASRIFCAN_GENTOOL_CFG5_MINOR_VERSION             0x00u
#define IF_ASRIFCAN_GENTOOL_CFG5_PATCH_VERSION             0x00u
#define CANIF_CFG5_GENERATOR_COMPATIBILITY_VERSION         0x0212u

#define CANIF_TRANSMIT_BUFFER                              [!"$txBuffering"!]
#define CANIF_TRANSMIT_BUFFER_PRIO_BY_CANID                [!"$prioByCanId"!]
#define CANIF_TRANSMIT_BUFFER_FIFO                         [!IF "node:exists(CanIfPrivateCfg/CanIfTxBufferFifoSupport) and node:value(CanIfPrivateCfg/CanIfTxBufferFifoSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_STATIC_FD_TXQUEUE                            [!IF "node:exists(CanIfPrivateCfg/CanIfStaticFdTxBufferSupport) and node:value(CanIfPrivateCfg/CanIfStaticFdTxBufferSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_WAKEUP_SUPPORT                               [!IF "node:exists(CanIfPrivateCfg/CanIfWakeupSupport) and node:value(CanIfPrivateCfg/CanIfWakeupSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_WAKEUP_VALIDATION                            STD_OFF
#define CANIF_WAKEUP_VALID_ALL_RX_MSGS                     STD_OFF
#define CANIF_WAKEUP_VALID_ONLY_NM_RX_MSGS                 STD_OFF
#define CANIF_CANDRV_WAKEUP_HANDLING                       STD_OFF
#define CANIF_DEV_ERROR_DETECT                             [!"$devErr"!]
#define CANIF_DEV_ERROR_REPORT                             [!"$devErr"!]
#define CANIF_TRANSMIT_CANCELLATION                        [!IF "node:exists(CanIfCtrlDrvCfg/*[1]/CanIfCtrlDrvTxCancellation) and node:value(CanIfCtrlDrvCfg/*[1]/CanIfCtrlDrvTxCancellation) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_CANCEL_SUPPORT_API                           [!IF "node:exists(CanIfPublicCfg/CanIfPublicCancelTransmitSupport) and node:value(CanIfPublicCfg/CanIfPublicCancelTransmitSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_VERSION_INFO_API                             [!IF "node:exists(CanIfPublicCfg/CanIfPublicVersionInfoApi) and node:value(CanIfPublicCfg/CanIfPublicVersionInfoApi) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_DLC_CHECK                                    [!IF "not(node:exists(CanIfPrivateCfg/CanIfPrivateDlcCheck)) or node:value(CanIfPrivateCfg/CanIfPrivateDlcCheck) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SUPPORT_NMOSEK_INDICATION                    [!IF "node:exists(CanIfPrivateCfg/CanIfSupportNmOsek) and node:value(CanIfPrivateCfg/CanIfSupportNmOsek) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_TRCV_HANDLING                                [!"$trcvHandling"!]
#define CANIF_TRCV_MAPPING                                 [!IF "node:exists(CanIfPrivateCfg/CanIfTransceiverMapping) and node:value(CanIfPrivateCfg/CanIfTransceiverMapping) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_PN_TRCV_HANDLING                             [!IF "node:exists(CanIfPublicCfg/CanIfPnTrcvHandlingSupport) and node:value(CanIfPublicCfg/CanIfPnTrcvHandlingSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_EXTENDEDID_SUPPORT                           [!IF "not(node:exists(CanIfPrivateCfg/CanIfSupportExtendedIds)) or node:value(CanIfPrivateCfg/CanIfSupportExtendedIds) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SETDYNAMICTXID_API                           [!IF "node:exists(CanIfPublicCfg/CanIfPublicSetDynamicTxIdApi) and node:value(CanIfPublicCfg/CanIfPublicSetDynamicTxIdApi) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SETDYNAMICRXID_API                           [!IF "node:exists(CanIfPublicCfg/CanIfPublicSetDynamicRxIdApi) and node:value(CanIfPublicCfg/CanIfPublicSetDynamicRxIdApi) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_PN_WU_TX_PDU_FILTER                          [!IF "node:exists(CanIfPublicCfg/CanIfPnWakeupTxPduFilterSupport) and node:value(CanIfPublicCfg/CanIfPnWakeupTxPduFilterSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_PUBLIC_TX_CONFIRM_POLLING_SUPPORT            [!IF "node:exists(CanIfPublicCfg/CanIfPublicTxConfirmPollingSupport) and node:value(CanIfPublicCfg/CanIfPublicTxConfirmPollingSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_RX_INDICATION_TYPE_I_IS_USED                 STD_OFF
#define CANIF_RX_INDICATION_TYPE_IV_IS_USED                STD_OFF
#define CANIF_CHANGE_BAUDRATE_SUPPORT                      STD_OFF
#define CANIF_SET_BAUDRATE_API                             STD_OFF
#define CANIF_META_DATA_RX_SUPPORT                         STD_OFF
#define CANIF_META_DATA_TX_SUPPORT                         STD_OFF
#define CANIF_J1939_DYN_ADDR_SUPPORT                       CANIF_J1939_DYN_ADDR_DISABLED
#define CANIF_MULTIPLE_CANDRV_SUPPORT                      [!IF "node:exists(CanIfPublicCfg/CanIfPublicMultipleDrvSupport) and node:value(CanIfPublicCfg/CanIfPublicMultipleDrvSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_RX_SEARCH_CONSIDER_MSG_TYPE                  [!IF "node:exists(CanIfPrivateCfg/CanIfRxSearchConsiderMsgType) and node:value(CanIfPrivateCfg/CanIfRxSearchConsiderMsgType) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_ECUC_SAFE_BSW_CHECKS                         [!IF "node:exists(CanIfPublicCfg/CanIfSafeBswChecks) and node:value(CanIfPublicCfg/CanIfSafeBswChecks) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_EXTENDED_RAM_CHECK_SUPPORT                   STD_OFF
#define CANIF_DATA_CHECKSUM_RX_SUPPORT                     [!IF "node:exists(CanIfPrivateCfg/CanIfDataChecksumRxSupport) and node:value(CanIfPrivateCfg/CanIfDataChecksumRxSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_DATA_CHECKSUM_TX_SUPPORT                     [!IF "node:exists(CanIfPrivateCfg/CanIfDataChecksumTxSupport) and node:value(CanIfPrivateCfg/CanIfDataChecksumTxSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SET_PDU_RECEPTION_MODE_SUPPORT               [!IF "node:exists(CanIfPrivateCfg/CanIfSetPduReceptionModeSupport) and node:value(CanIfPrivateCfg/CanIfSetPduReceptionModeSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_BUS_MIRRORING_SUPPORT                        [!IF "node:exists(CanIfPublicCfg/CanIfBusMirroringSupport) and node:value(CanIfPublicCfg/CanIfBusMirroringSupport) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_ENABLE_SECURITY_EVENT_REPORTING              [!IF "node:exists(CanIfPublicCfg/CanIfEnableSecurityEventReporting) and node:value(CanIfPublicCfg/CanIfEnableSecurityEventReporting) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SUPPORT_MULTIPARTITION                       [!IF "node:exists(CanIfPublicCfg/CanIfSupportMultipartition) and node:value(CanIfPublicCfg/CanIfSupportMultipartition) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SUPPORT_CAN_XL                               [!IF "node:exists(CanIfPrivateCfg/CanIfSupportCanXL) and node:value(CanIfPrivateCfg/CanIfSupportCanXL) = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define CANIF_SUPPRESS_EXTENDED_VERSION_CHECK

[!IF "$dummyKind = 'SelfAssignment'"!][!//
#ifndef CANIF_USE_DUMMY_STATEMENT
#define CANIF_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef CANIF_DUMMY_STATEMENT
#define CANIF_DUMMY_STATEMENT(v) (v)=(v)
#endif
#ifndef CANIF_DUMMY_STATEMENT_CONST
#define CANIF_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
[!ELSEIF "$dummyKind = 'VoidCast'"!][!//
#ifndef CANIF_USE_DUMMY_STATEMENT
#define CANIF_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef CANIF_DUMMY_STATEMENT
#define CANIF_DUMMY_STATEMENT(v) (void)(v)
#endif
#ifndef CANIF_DUMMY_STATEMENT_CONST
#define CANIF_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
[!ELSE!][!//
#ifndef CANIF_USE_DUMMY_STATEMENT
#define CANIF_USE_DUMMY_STATEMENT STD_OFF
#endif
#ifndef CANIF_DUMMY_STATEMENT
#define CANIF_DUMMY_STATEMENT(v)
#endif
#ifndef CANIF_DUMMY_STATEMENT_CONST
#define CANIF_DUMMY_STATEMENT_CONST(v)
#endif
[!ENDIF!][!//
#ifndef CANIF_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CANIF_ATOMIC_BIT_ACCESS_IN_BITFIELD [!"$atomicBitAccess"!]
#endif
#ifndef CANIF_ATOMIC_VARIABLE_ACCESS
#define CANIF_ATOMIC_VARIABLE_ACCESS [!"$atomicVarAccess"!]
#endif
#ifndef [!"$canifProcessor"!]
#define [!"$canifProcessor"!]
#endif
#ifndef [!"$canifCompiler"!]
#define [!"$canifCompiler"!]
#endif
#ifndef CANIF_GEN_GENERATOR_MSR
#define CANIF_GEN_GENERATOR_MSR
#endif
[!IF "$bitOrder = 'MSB_to_LSB'"!][!//
#ifndef CANIF_CPUTYPE_BITORDER_MSB2LSB
#define CANIF_CPUTYPE_BITORDER_MSB2LSB
#endif
[!ELSE!][!//
#ifndef CANIF_CPUTYPE_BITORDER_LSB2MSB
#define CANIF_CPUTYPE_BITORDER_LSB2MSB
#endif
[!ENDIF!][!//
#ifndef CANIF_CONFIGURATION_VARIANT_PRECOMPILE
#define CANIF_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CANIF_CONFIGURATION_VARIANT_LINKTIME
#define CANIF_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CANIF_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CANIF_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CANIF_CONFIGURATION_VARIANT
#define CANIF_CONFIGURATION_VARIANT CANIF_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CANIF_POSTBUILD_VARIANT_SUPPORT
#define CANIF_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#define CANIF_CPU_TYPE_SET_IN_ECUC_MODULE                  CPU_TYPE_32

#define CANIF_SUPPORT_CANDRV_EQC_MSRC                      STD_OFF
#define CANIF_SUPPORT_CANDRV_EQC_AR_403                    STD_OFF
#define CANIF_SUPPORT_CANDRV_EQC_AR_421                    STD_OFF
#define CANIF_SUPPORT_CANDRV_EQC_AR_431                    STD_ON
#define CANIF_SUPPORT_CANDRV_EQC_AR_431_OR_MSRC            STD_ON
#define CANIF_SUPPORT_CANDRV_EQC_AR_403_OR_AR_421          STD_OFF
#define CANIF_SUPPORT_CANDRV_EQC_AR_403_OR_AR_421_OR_MSRC  STD_OFF

#define CANIF_SEARCH_ALGORITHM                             CANIF_LINEAR
#define CANIF_CONFIG_VARIANT                               CANIF_CFGVAR_PRECOMPILETIME

typedef uint8 CanIf_TxBufferSizeType;

#include "CanIf_Types.h"

#define CANIF_XCFG                                         CANIF_CONST
#define CANIF_VAR_XCFG_NOINIT                              CANIF_VAR_NOINIT

#define CanIf_TxPduHnd_INVALID                             0xFFu
#define CanIf_RxPduHnd_INVALID                             0xFFu

#define CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID                                                             1u
#define CANIF_TXBUFFER_HANDLINGTYPE_FIFO                                                                    2u
#define CANIF_TXBUFFER_HANDLINGTYPE_NONE                                                                    3u

/* Symbolic Name Values: Controllers */
[!LOOP "node:order(CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*, 'CanIfCtrlId')"!][!//
#define CanIfConf_CanIfCtrlCfg_[!"node:name(.)"!]                                              [!"num:i(node:value(CanIfCtrlId))"!]u
[!ENDLOOP!][!//

/* Symbolic Name Values: Transceivers */
[!LOOP "node:order(CanIfTrcvDrvCfg/*/CanIfTrcvCfg/*, 'CanIfTrcvId')"!][!//
#define CanIfConf_CanIfTrcvCfg_[!"node:name(.)"!]                                                         [!"num:i(node:value(CanIfTrcvId))"!]u
[!ENDLOOP!][!//

[!IF "$trcvHandling = 'STD_ON'"!][!//
#define CanTrcv_SetOpMode                                  [!"$trcvPrefix"!]_SetOpMode
#define CanTrcv_GetOpMode                                  [!"$trcvPrefix"!]_GetOpMode
#define CanTrcv_GetBusWuReason                             [!"$trcvPrefix"!]_GetBusWuReason
#define CanTrcv_SetWakeupMode                              [!"$trcvPrefix"!]_SetWakeupMode
#define CanTrcv_CheckWakeup                                [!"$trcvPrefix"!]_CheckWakeup
[!ENDIF!][!//

/* Tx PDU Handles */
[!IF "node:exists(CanIfInitCfg/CanIfTxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfTxPduCfg/*, 'CanIfTxPduId')"!][!//
#define CanIfTxPduHnd_[!"node:name(.)"!]                                [!"num:i(node:value(CanIfTxPduId))"!]u
[!ENDLOOP!][!//
[!ENDIF!][!//

/* Rx PDU Handles (per upper layer 0-based) */
[!VAR "ulLog" = "'|'"!][!//
[!IF "node:exists(CanIfInitCfg/CanIfRxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfRxPduCfg/*, 'CanIfRxPduId')"!][!//
[!VAR "ul" = "'PDUR'"!][!//
[!IF "node:exists(CanIfRxPduUserRxIndicationUL)"!][!VAR "ul" = "string:trim(node:value(CanIfRxPduUserRxIndicationUL))"!][!ENDIF!][!//
[!VAR "ulTag" = "concat($ul, '|')"!][!//
[!VAR "ulCnt" = "num:i((string:length($ulLog) - string:length(text:replace($ulLog, $ulTag, ''))) div string:length($ulTag))"!][!//
[!VAR "ulLog" = "concat($ulLog, $ulTag)"!][!//
#define CanIfRxPduHnd_[!"node:name(.)"!]                          [!"$ulCnt"!]u
[!ENDLOOP!][!//
[!ENDIF!][!//

/* Symbolic Name Values: Tx/Rx PDUs */
[!IF "node:exists(CanIfInitCfg/CanIfTxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfTxPduCfg/*, 'CanIfTxPduId')"!][!//
#define CanIfConf_CanIfTxPduCfg_[!"node:name(.)"!]                      [!"num:i(node:value(CanIfTxPduId))"!]u
[!ENDLOOP!][!//
[!ENDIF!][!//
[!IF "node:exists(CanIfInitCfg/CanIfRxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfRxPduCfg/*, 'CanIfRxPduId')"!][!//
#define CanIfConf_CanIfRxPduCfg_[!"node:name(.)"!]                [!"num:i(node:value(CanIfRxPduId))"!]u
[!ENDLOOP!][!//
[!ENDIF!][!//

#define CanIf_RxIndication(Mailbox, PduInfoPtr)                                                     CanIf_RxIndicationAsr403(((Mailbox)->Hoh), (Mailbox)->CanId, (uint8)((PduInfoPtr)->SduLength), (P2CONST(uint8, AUTOMATIC, CANIF_CBK_DRV_VAR))((PduInfoPtr)->SduDataPtr))
#define CanIf_ControllerModeIndication(ControllerId, ControllerMode)                                (CanIf_ControllerModeIndicationAr431((ControllerId), (ControllerMode)))
#define [!"$canifTrcvCbPrefix"!]_TrcvModeIndication(TransceiverId, TransceiverMode)                         (CanIf_TrcvModeIndication((TransceiverId), (TransceiverMode)))

#define CANIF_MASKCODE_RANGE_FLAG                                                                   0x20000000u
#define CANIF_FD_FLAG                                                                               0x40000000u
#define CANIF_FD_FLAG_MASKOUT                                                                       0xBFFFFFFFu
#define CANIF_FD_FLAG_SHIFTPOS                                                                      30u
#define CANIF_STOP_FLAG                                                                             0x40000000u
#define CANIF_RANGE_FLAG                                                                            0x20000000u
#define CANIF_STOP_RANGE_FLAG                                                                       0x60000000u
#define CANIF_STOP_RANGE_FLAG_MASKOUT                                                               0x9FFFFFFFu


/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL CONSTANT MACROS
**********************************************************************************************************************/
#define CANIF_BUSOFFNOTIFICATIONFCTPTR                                                              STD_ON
#define CANIF_CANCONTROLLERIDUPTOLOWMAP                                                             STD_OFF
#define CANIF_CANDRVEQCARVERSIONOFCANCONTROLLERIDUPTOLOWMAP                                         STD_OFF
#define CANIF_CANDRVFCTTBLIDXOFCANCONTROLLERIDUPTOLOWMAP                                            STD_OFF
#define CANIF_CANDRVFCTTBLUSEDOFCANCONTROLLERIDUPTOLOWMAP                                           STD_OFF
#define CANIF_CONTROLLEROFCANCONTROLLERIDUPTOLOWMAP                                                 STD_OFF
#define CANIF_CANDRVFCTTBL                                                                          STD_OFF
#define CANIF_CHANGEBAUDRATEFCTOFCANDRVFCTTBL                                                       STD_OFF
#define CANIF_CHECKBAUDRATEFCTOFCANDRVFCTTBL                                                        STD_OFF
#define CANIF_CHECKWAKEUPFCTOFCANDRVFCTTBL                                                          STD_OFF
#define CANIF_GETCONTROLLERERRORSTATEFCTOFCANDRVFCTTBL                                              STD_OFF
#define CANIF_GETCONTROLLERRXERRORCOUNTEROFCANDRVFCTTBL                                             STD_OFF
#define CANIF_GETCONTROLLERTXERRORCOUNTEROFCANDRVFCTTBL                                             STD_OFF
#define CANIF_RAMCHECKENABLECONTROLLERFCTOFCANDRVFCTTBL                                             STD_OFF
#define CANIF_RAMCHECKENABLEMAILBOXFCTOFCANDRVFCTTBL                                                STD_OFF
#define CANIF_RAMCHECKEXECUTEFCTOFCANDRVFCTTBL                                                      STD_OFF
#define CANIF_SETBAUDRATEFCTOFCANDRVFCTTBL                                                          STD_OFF
#define CANIF_SETCONTROLLERMODEFCTOFCANDRVFCTTBL                                                    STD_OFF
#define CANIF_WRITEFCTOFCANDRVFCTTBL                                                                STD_OFF
#define CANIF_XLWRITEOFCANDRVFCTTBL                                                                 STD_OFF
#define CANIF_CANIFCTRLID2MAPPEDTXBUFFERSCONFIG                                                     STD_ON
#define CANIF_INVALIDHNDOFCANIFCTRLID2MAPPEDTXBUFFERSCONFIG                                         STD_OFF
#define CANIF_MAPPEDTXBUFFERSCONFIGENDIDXOFCANIFCTRLID2MAPPEDTXBUFFERSCONFIG                        STD_ON
#define CANIF_MAPPEDTXBUFFERSCONFIGSTARTIDXOFCANIFCTRLID2MAPPEDTXBUFFERSCONFIG                      STD_ON
#define CANIF_CANTRCVFCTTBL                                                                         STD_OFF
#define CANIF_CHECKWAKEFLAGFCTOFCANTRCVFCTTBL                                                       STD_OFF
#define CANIF_CHECKWAKEUPFCTOFCANTRCVFCTTBL                                                         STD_OFF
#define CANIF_CLEARTRCVWUFFLAGFCTOFCANTRCVFCTTBL                                                    STD_OFF
#define CANIF_GETBUSWUREASONFCTOFCANTRCVFCTTBL                                                      STD_OFF
#define CANIF_GETOPMODEFCTOFCANTRCVFCTTBL                                                           STD_OFF
#define CANIF_SETOPMODEFCTOFCANTRCVFCTTBL                                                           STD_OFF
#define CANIF_SETWAKEUPMODEFCTOFCANTRCVFCTTBL                                                       STD_OFF
#define CANIF_CTRLCONFIG                                                                            STD_OFF
#define CANIF_FEATUREPNWUTXPDUFILTERENABLEDOFCTRLCONFIG                                             STD_OFF
#define CANIF_J1939DYNADDROFFSETOFCTRLCONFIG                                                        STD_OFF
#define CANIF_J1939DYNADDRSUPPORTOFCTRLCONFIG                                                       STD_OFF
#define CANIF_RXDHRANDOMNUMBER1OFCTRLCONFIG                                                         STD_OFF
#define CANIF_RXDHRANDOMNUMBER2OFCTRLCONFIG                                                         STD_OFF
#define CANIF_RXPDUCONFIGCANXLRXPDUSSDT3ENDIDXOFCTRLCONFIG                                          STD_OFF
#define CANIF_RXPDUCONFIGCANXLRXPDUSSDT3STARTIDXOFCTRLCONFIG                                        STD_OFF
#define CANIF_RXPDUCONFIGCANXLRXPDUSSDT3USEDOFCTRLCONFIG                                            STD_OFF
#define CANIF_RXPDUCONFIGCANXLRXPDUSSDTNOT3ENDIDXOFCTRLCONFIG                                       STD_OFF
#define CANIF_RXPDUCONFIGCANXLRXPDUSSDTNOT3STARTIDXOFCTRLCONFIG                                     STD_OFF
#define CANIF_RXPDUCONFIGCANXLRXPDUSSDTNOT3USEDOFCTRLCONFIG                                         STD_OFF
#define CANIF_CTRLMODEINDICATIONFCTPTR                                                              STD_ON
#define CANIF_CTRLSTATES                                                                            STD_ON
#define CANIF_CTRLMODEOFCTRLSTATES                                                                  STD_ON
#define CANIF_PDUMODEOFCTRLSTATES                                                                   STD_ON
#define CANIF_DYNRXID                                                                               STD_OFF
#define CANIF_FINALMAGICNUMBER                                                                      STD_OFF
#define CANIF_GENERATORCOMPATIBILITYVERSION                                                         STD_ON
#define CANIF_GENERATORVERSION                                                                      STD_ON
#define CANIF_HXHOFFSET                                                                             STD_OFF
#define CANIF_INITDATAHASHCODE                                                                      STD_OFF
#define CANIF_MAILBOXCONFIG                                                                         STD_ON
#define CANIF_CTRLSTATESIDXOFMAILBOXCONFIG                                                          STD_ON
#define CANIF_MAILBOXTYPEOFMAILBOXCONFIG                                                            STD_ON
#define CANIF_PDUIDFIRSTOFMAILBOXCONFIG                                                             STD_ON
#define CANIF_PDUIDLASTOFMAILBOXCONFIG                                                              STD_ON
#define CANIF_TXBUFFERCFGIDXOFMAILBOXCONFIG                                                         STD_ON
#define CANIF_TXBUFFERCFGOFMAILBOXCONFIG                                                            STD_ON
#define CANIF_TXBUFFERCFGUSEDOFMAILBOXCONFIG                                                        STD_ON
#define CANIF_TXBUFFERHANDLINGTYPEOFMAILBOXCONFIG                                                   STD_ON
#define CANIF_MAPPEDTXBUFFERSCONFIG                                                                 STD_ON
#define CANIF_MAILBOXCONFIGIDXOFMAPPEDTXBUFFERSCONFIG                                               STD_ON
#define CANIF_MAXTRCVHANDLEIDPLUSONE                                                                STD_ON
#define CANIF_NUMOFCANXLRXPDUS                                                                      STD_OFF
#define CANIF_NUMOFNONCANXLRXPDUS                                                                   STD_OFF
#define CANIF_PDURXMODE                                                                             STD_OFF
#define CANIF_RXDHADJUST                                                                            STD_OFF
#define CANIF_RXINDICATIONFCTLIST                                                                   STD_ON
#define CANIF_RXINDICATIONFCTOFRXINDICATIONFCTLIST                                                  STD_ON
#define CANIF_RXINDICATIONLAYOUTOFRXINDICATIONFCTLIST                                               STD_ON
#define CANIF_RXPDUCANXLPROPS                                                                       STD_OFF
#define CANIF_ACCEPTANCEFIELDOFRXPDUCANXLPROPS                                                      STD_OFF
#define CANIF_PRIORITYIDOFRXPDUCANXLPROPS                                                           STD_OFF
#define CANIF_SDUTYPEOFRXPDUCANXLPROPS                                                              STD_OFF
#define CANIF_VCIDOFRXPDUCANXLPROPS                                                                 STD_OFF
#define CANIF_RXPDUCONFIG                                                                           [!IF "$numRxPdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_CANIFRXPDUIDOFRXPDUCONFIG                                                             STD_OFF
#define CANIF_HASMETADATAITEMCANID32OFRXPDUCONFIG                                                   STD_OFF
#define CANIF_ISCANNMRXPDUOFRXPDUCONFIG                                                             STD_OFF
#define CANIF_ISDATACHECKSUMRXPDUOFRXPDUCONFIG                                                      STD_OFF
#define CANIF_MSGTYPEOFRXPDUCONFIG                                                                  STD_OFF
#define CANIF_RXINDICATIONFCTLISTIDXOFRXPDUCONFIG                                                   [!IF "$numRxPdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_RXPDUCANIDOFRXPDUCONFIG                                                               [!IF "$numRxPdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_RXPDUCANXLPROPSIDXOFRXPDUCONFIG                                                       STD_OFF
#define CANIF_RXPDUCANXLPROPSUSEDOFRXPDUCONFIG                                                      STD_OFF
#define CANIF_RXPDUDLCOFRXPDUCONFIG                                                                 [!IF "$numRxPdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_RXPDUMASKOFRXPDUCONFIG                                                                [!IF "$numRxPdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_UPPERPDUIDOFRXPDUCONFIG                                                               [!IF "$numRxPdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SIZEOFCANIFCTRLID2MAPPEDTXBUFFERSCONFIG                                               STD_ON
#define CANIF_SIZEOFCTRLSTATES                                                                      STD_ON
#define CANIF_SIZEOFMAILBOXCONFIG                                                                   STD_ON
#define CANIF_SIZEOFMAPPEDTXBUFFERSCONFIG                                                           STD_ON
#define CANIF_SIZEOFRXINDICATIONFCTLIST                                                             STD_ON
#define CANIF_SIZEOFRXPDUCONFIG                                                                     STD_ON
#define CANIF_SIZEOFTRCVTOCTRLMAP                                                                   [!IF "$numTrcvs > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SIZEOFTXBUFFERPRIOBYCANIDBASE                                                         STD_ON
#define CANIF_SIZEOFTXBUFFERPRIOBYCANIDCONFIG                                                       STD_ON
#define CANIF_SIZEOFTXCONFIRMATIONFCTLIST                                                           STD_ON
#define CANIF_SIZEOFTXPDUCONFIG                                                                     STD_ON
#define CANIF_SIZEOFTXPDUQUEUEINDEX                                                                 STD_ON
#define CANIF_SIZEOFTXQUEUE                                                                         STD_ON
#define CANIF_SIZEOFTXQUEUEFLAGS                                                                    STD_ON
#define CANIF_TRANSCEIVERUPTOLOWMAP                                                                 STD_OFF
#define CANIF_CANTRCVFCTTBLIDXOFTRANSCEIVERUPTOLOWMAP                                               STD_OFF
#define CANIF_TRANSCEIVEROFTRANSCEIVERUPTOLOWMAP                                                    STD_OFF
#define CANIF_TRANSCEIVERUPTOUPPERMAP                                                               STD_OFF
#define CANIF_TRCVMODEINDICATIONFCTPTR                                                              STD_ON
#define CANIF_TRCVTOCTRLMAP                                                                         [!IF "$numTrcvs > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_TXBUFFERFIFOCONFIG                                                                    STD_OFF
#define CANIF_SIZEOFONEPAYLOADELOFTXBUFFERFIFOCONFIG                                                STD_OFF
#define CANIF_TXBUFFERPRIOBYCANIDBASE                                                               STD_ON
#define CANIF_TXBUFFERPRIOBYCANIDCONFIG                                                             STD_ON
#define CANIF_BITPOS2TXPDUIDOFFSETOFTXBUFFERPRIOBYCANIDCONFIG                                       STD_ON
#define CANIF_TXBUFFERPRIOBYCANIDBASEIDXOFTXBUFFERPRIOBYCANIDCONFIG                                 STD_ON
#define CANIF_TXQUEUEFLAGSENDIDXOFTXBUFFERPRIOBYCANIDCONFIG                                         STD_ON
#define CANIF_TXQUEUEFLAGSSTARTIDXOFTXBUFFERPRIOBYCANIDCONFIG                                       STD_ON
#define CANIF_TXCONFIRMATIONFCTLIST                                                                 STD_ON
#define CANIF_TXPDUCANXLPROPS                                                                       STD_OFF
#define CANIF_ACCEPTANCEFIELDOFTXPDUCANXLPROPS                                                      STD_OFF
#define CANIF_CANXLHTHOFTXPDUCANXLPROPS                                                             STD_OFF
#define CANIF_PRIORITYIDOFTXPDUCANXLPROPS                                                           STD_OFF
#define CANIF_SDUTYPEOFTXPDUCANXLPROPS                                                              STD_OFF
#define CANIF_VCIDOFTXPDUCANXLPROPS                                                                 STD_OFF
#define CANIF_TXPDUCONFIG                                                                           STD_ON
#define CANIF_CANIDOFTXPDUCONFIG                                                                    STD_ON
#define CANIF_CANIDTXMASKOFTXPDUCONFIG                                                              STD_OFF
#define CANIF_CTRLSTATESIDXOFTXPDUCONFIG                                                            STD_ON
#define CANIF_HASMETADATAITEMCANID32OFTXPDUCONFIG                                                   STD_OFF
#define CANIF_ISDATACHECKSUMTXPDUOFTXPDUCONFIG                                                      STD_OFF
#define CANIF_ISPNWUTXPDUOFTXPDUCONFIG                                                              STD_OFF
#define CANIF_ISTXPDUTRUNCATIONOFTXPDUCONFIG                                                        STD_ON
#define CANIF_MAILBOXCONFIGIDXOFTXPDUCONFIG                                                         STD_ON
#define CANIF_TXCONFIRMATIONFCTLISTIDXOFTXPDUCONFIG                                                 STD_ON
#define CANIF_TXPDUCANXLPROPSIDXOFTXPDUCONFIG                                                       STD_OFF
#define CANIF_TXPDUCANXLPROPSUSEDOFTXPDUCONFIG                                                      STD_OFF
#define CANIF_TXPDULENGTHOFTXPDUCONFIG                                                              STD_ON
#define CANIF_UPPERLAYERTXPDUIDOFTXPDUCONFIG                                                        STD_ON
#define CANIF_TXPDUQUEUEINDEX                                                                       STD_ON
#define CANIF_TXQUEUEIDXOFTXPDUQUEUEINDEX                                                           STD_ON
#define CANIF_TXQUEUEUSEDOFTXPDUQUEUEINDEX                                                          STD_ON
#define CANIF_TXPDUSTATIC2DYNAMICINDIRECTION                                                        STD_OFF
#define CANIF_TXQUEUE                                                                               STD_ON
#define CANIF_TXQUEUEFLAGS                                                                          STD_ON
#define CANIF_TXQUEUEINDEX2DATASTARTSTOP                                                            STD_OFF
#define CANIF_ULRXPDUID2INTERNALRXPDUID                                                             STD_OFF
#define CANIF_RXPDUCONFIGIDXOFULRXPDUID2INTERNALRXPDUID                                             STD_OFF
#define CANIF_RXPDUCONFIGUSEDOFULRXPDUID2INTERNALRXPDUID                                            STD_OFF
#define CANIF_ULTXPDUID2INTERNALTXPDUID                                                             STD_OFF
#define CANIF_WAKEUPCONFIG                                                                          STD_OFF
#define CANIF_CONTROLLERIDOFWAKEUPCONFIG                                                            STD_OFF
#define CANIF_WAKEUPSOURCEOFWAKEUPCONFIG                                                            STD_OFF
#define CANIF_WAKEUPTARGETADDRESSOFWAKEUPCONFIG                                                     STD_OFF
#define CANIF_WAKEUPTARGETMODULEOFWAKEUPCONFIG                                                      STD_OFF
#define CANIF_PCCONFIG                                                                              STD_ON
#define CANIF_BUSOFFNOTIFICATIONFCTPTROFPCCONFIG                                                    STD_ON
#define CANIF_CANIFCTRLID2MAPPEDTXBUFFERSCONFIGOFPCCONFIG                                           STD_ON
#define CANIF_CTRLMODEINDICATIONFCTPTROFPCCONFIG                                                    STD_ON
#define CANIF_CTRLSTATESOFPCCONFIG                                                                  STD_ON
#define CANIF_FINALMAGICNUMBEROFPCCONFIG                                                            STD_OFF
#define CANIF_GENERATORCOMPATIBILITYVERSIONOFPCCONFIG                                               STD_ON
#define CANIF_GENERATORVERSIONOFPCCONFIG                                                            STD_ON
#define CANIF_INITDATAHASHCODEOFPCCONFIG                                                            STD_OFF
#define CANIF_MAILBOXCONFIGOFPCCONFIG                                                               STD_ON
#define CANIF_MAPPEDTXBUFFERSCONFIGOFPCCONFIG                                                       STD_ON
#define CANIF_MAXTRCVHANDLEIDPLUSONEOFPCCONFIG                                                      STD_ON
#define CANIF_NUMOFCANXLRXPDUSOFPCCONFIG                                                            STD_OFF
#define CANIF_NUMOFNONCANXLRXPDUSOFPCCONFIG                                                         STD_OFF
#define CANIF_RXINDICATIONFCTLISTOFPCCONFIG                                                         STD_ON
#define CANIF_RXPDUCONFIGOFPCCONFIG                                                                 [!IF "$numRxPdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SIZEOFCANIFCTRLID2MAPPEDTXBUFFERSCONFIGOFPCCONFIG                                     STD_ON
#define CANIF_SIZEOFCTRLSTATESOFPCCONFIG                                                            STD_ON
#define CANIF_SIZEOFMAILBOXCONFIGOFPCCONFIG                                                         STD_ON
#define CANIF_SIZEOFMAPPEDTXBUFFERSCONFIGOFPCCONFIG                                                 STD_ON
#define CANIF_SIZEOFRXINDICATIONFCTLISTOFPCCONFIG                                                   STD_ON
#define CANIF_SIZEOFRXPDUCONFIGOFPCCONFIG                                                           STD_ON
#define CANIF_SIZEOFTRCVTOCTRLMAPOFPCCONFIG                                                         [!IF "$numTrcvs > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_SIZEOFTXBUFFERPRIOBYCANIDBASEOFPCCONFIG                                               STD_ON
#define CANIF_SIZEOFTXBUFFERPRIOBYCANIDCONFIGOFPCCONFIG                                             STD_ON
#define CANIF_SIZEOFTXCONFIRMATIONFCTLISTOFPCCONFIG                                                 STD_ON
#define CANIF_SIZEOFTXPDUCONFIGOFPCCONFIG                                                           STD_ON
#define CANIF_SIZEOFTXPDUQUEUEINDEXOFPCCONFIG                                                       STD_ON
#define CANIF_SIZEOFTXQUEUEFLAGSOFPCCONFIG                                                          STD_ON
#define CANIF_SIZEOFTXQUEUEOFPCCONFIG                                                               STD_ON
#define CANIF_TRCVMODEINDICATIONFCTPTROFPCCONFIG                                                    STD_ON
#define CANIF_TRCVTOCTRLMAPOFPCCONFIG                                                               [!IF "$numTrcvs > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_TXBUFFERPRIOBYCANIDBASEOFPCCONFIG                                                     STD_ON
#define CANIF_TXBUFFERPRIOBYCANIDCONFIGOFPCCONFIG                                                   STD_ON
#define CANIF_TXCONFIRMATIONFCTLISTOFPCCONFIG                                                       STD_ON
#define CANIF_TXPDUCONFIGOFPCCONFIG                                                                 STD_ON
#define CANIF_TXPDUQUEUEINDEXOFPCCONFIG                                                             STD_ON
#define CANIF_TXQUEUEFLAGSOFPCCONFIG                                                                STD_ON
#define CANIF_TXQUEUEOFPCCONFIG                                                                     STD_ON

#define CANIF_MIN_TXQUEUEFLAGS                                                                      0u
#define CANIF_MAX_TXQUEUEFLAGS                                                                      4294967295u
#define CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG                                                      255u
#define CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX                                                        255u
#define CANIF_EXISTS_TXBUFFERPRIOBYCANIDCONFIG_TXBUFFERCFGOFMAILBOXCONFIG                           STD_ON
#define CANIF_EXISTS_NO_TXBUFFERCFGOFMAILBOXCONFIG                                                  STD_ON
#define CANIF_TXBUFFERPRIOBYCANIDCONFIG_TXBUFFERCFGOFMAILBOXCONFIG                                  0x00u
#define CANIF_NO_TXBUFFERCFGOFMAILBOXCONFIG                                                         0xFFu

#define CANIF_ISDEF_MAPPEDTXBUFFERSCONFIGENDIDXOFCANIFCTRLID2MAPPEDTXBUFFERSCONFIG                  STD_OFF
#define CANIF_ISDEF_MAPPEDTXBUFFERSCONFIGSTARTIDXOFCANIFCTRLID2MAPPEDTXBUFFERSCONFIG                STD_OFF
#define CANIF_ISDEF_CTRLSTATESIDXOFMAILBOXCONFIG                                                    STD_OFF
#define CANIF_ISDEF_MAILBOXTYPEOFMAILBOXCONFIG                                                      STD_OFF
#define CANIF_ISDEF_PDUIDFIRSTOFMAILBOXCONFIG                                                       STD_OFF
#define CANIF_ISDEF_PDUIDLASTOFMAILBOXCONFIG                                                        STD_OFF
#define CANIF_ISDEF_TXBUFFERCFGIDXOFMAILBOXCONFIG                                                   STD_OFF
#define CANIF_ISDEF_TXBUFFERCFGOFMAILBOXCONFIG                                                      STD_OFF
#define CANIF_ISDEF_TXBUFFERCFGUSEDOFMAILBOXCONFIG                                                  STD_OFF
#define CANIF_ISDEF_TXBUFFERHANDLINGTYPEOFMAILBOXCONFIG                                             STD_OFF
#define CANIF_ISDEF_MAILBOXCONFIGIDXOFMAPPEDTXBUFFERSCONFIG                                         STD_OFF
#define CANIF_ISDEF_RXINDICATIONFCTOFRXINDICATIONFCTLIST                                            STD_OFF
#define CANIF_ISDEF_RXINDICATIONLAYOUTOFRXINDICATIONFCTLIST                                         STD_OFF
#define CANIF_ISDEF_RXINDICATIONFCTLISTIDXOFRXPDUCONFIG                                             STD_OFF
#define CANIF_ISDEF_RXPDUCANIDOFRXPDUCONFIG                                                         STD_OFF
#define CANIF_ISDEF_RXPDUDLCOFRXPDUCONFIG                                                           STD_OFF
#define CANIF_ISDEF_RXPDUMASKOFRXPDUCONFIG                                                          STD_OFF
#define CANIF_ISDEF_UPPERPDUIDOFRXPDUCONFIG                                                         STD_OFF
#define CANIF_ISDEF_TRCVTOCTRLMAP                                                                   STD_OFF
#define CANIF_ISDEF_BITPOS2TXPDUIDOFFSETOFTXBUFFERPRIOBYCANIDCONFIG                                 STD_OFF
#define CANIF_ISDEF_TXBUFFERPRIOBYCANIDBASEIDXOFTXBUFFERPRIOBYCANIDCONFIG                           STD_OFF
#define CANIF_ISDEF_TXQUEUEFLAGSENDIDXOFTXBUFFERPRIOBYCANIDCONFIG                                   STD_OFF
#define CANIF_ISDEF_TXQUEUEFLAGSSTARTIDXOFTXBUFFERPRIOBYCANIDCONFIG                                 STD_OFF
#define CANIF_ISDEF_TXCONFIRMATIONFCTLIST                                                           STD_OFF
#define CANIF_ISDEF_CANIDOFTXPDUCONFIG                                                              STD_OFF
#define CANIF_ISDEF_CTRLSTATESIDXOFTXPDUCONFIG                                                      STD_OFF
#define CANIF_ISDEF_ISTXPDUTRUNCATIONOFTXPDUCONFIG                                                  STD_OFF
#define CANIF_ISDEF_MAILBOXCONFIGIDXOFTXPDUCONFIG                                                   STD_OFF
#define CANIF_ISDEF_TXCONFIRMATIONFCTLISTIDXOFTXPDUCONFIG                                           STD_OFF
#define CANIF_ISDEF_TXPDULENGTHOFTXPDUCONFIG                                                        STD_OFF
#define CANIF_ISDEF_UPPERLAYERTXPDUIDOFTXPDUCONFIG                                                  STD_OFF
#define CANIF_ISDEF_TXQUEUEIDXOFTXPDUQUEUEINDEX                                                     STD_OFF
#define CANIF_ISDEF_TXQUEUEUSEDOFTXPDUQUEUEINDEX                                                    STD_OFF
#define CANIF_ISDEF_BUSOFFNOTIFICATIONFCTPTROFPCCONFIG                                              STD_ON
#define CANIF_ISDEF_CANIFCTRLID2MAPPEDTXBUFFERSCONFIGOFPCCONFIG                                     STD_ON
#define CANIF_ISDEF_CTRLMODEINDICATIONFCTPTROFPCCONFIG                                              STD_ON
#define CANIF_ISDEF_CTRLSTATESOFPCCONFIG                                                            STD_ON
#define CANIF_ISDEF_MAILBOXCONFIGOFPCCONFIG                                                         STD_ON
#define CANIF_ISDEF_MAPPEDTXBUFFERSCONFIGOFPCCONFIG                                                 STD_ON
#define CANIF_ISDEF_RXINDICATIONFCTLISTOFPCCONFIG                                                   STD_ON
#define CANIF_ISDEF_RXPDUCONFIGOFPCCONFIG                                                           [!IF "$numRxPdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_ISDEF_TRCVMODEINDICATIONFCTPTROFPCCONFIG                                              STD_ON
#define CANIF_ISDEF_TRCVTOCTRLMAPOFPCCONFIG                                                         [!IF "$numTrcvs > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANIF_ISDEF_TXBUFFERPRIOBYCANIDBASEOFPCCONFIG                                               STD_ON
#define CANIF_ISDEF_TXBUFFERPRIOBYCANIDCONFIGOFPCCONFIG                                             STD_ON
#define CANIF_ISDEF_TXCONFIRMATIONFCTLISTOFPCCONFIG                                                 STD_ON
#define CANIF_ISDEF_TXPDUCONFIGOFPCCONFIG                                                           STD_ON
#define CANIF_ISDEF_TXPDUQUEUEINDEXOFPCCONFIG                                                       STD_ON
#define CANIF_ISDEF_TXQUEUEFLAGSOFPCCONFIG                                                          STD_ON
#define CANIF_ISDEF_TXQUEUEOFPCCONFIG                                                               STD_ON

#define CANIF_EQ2_MAPPEDTXBUFFERSCONFIGENDIDXOFCANIFCTRLID2MAPPEDTXBUFFERSCONFIG
#define CANIF_EQ2_MAPPEDTXBUFFERSCONFIGSTARTIDXOFCANIFCTRLID2MAPPEDTXBUFFERSCONFIG
#define CANIF_EQ2_CTRLSTATESIDXOFMAILBOXCONFIG
#define CANIF_EQ2_MAILBOXTYPEOFMAILBOXCONFIG
#define CANIF_EQ2_PDUIDFIRSTOFMAILBOXCONFIG
#define CANIF_EQ2_PDUIDLASTOFMAILBOXCONFIG
#define CANIF_EQ2_TXBUFFERCFGIDXOFMAILBOXCONFIG
#define CANIF_EQ2_TXBUFFERCFGOFMAILBOXCONFIG
#define CANIF_EQ2_TXBUFFERCFGUSEDOFMAILBOXCONFIG
#define CANIF_EQ2_TXBUFFERHANDLINGTYPEOFMAILBOXCONFIG
#define CANIF_EQ2_MAILBOXCONFIGIDXOFMAPPEDTXBUFFERSCONFIG
#define CANIF_EQ2_RXINDICATIONFCTOFRXINDICATIONFCTLIST
#define CANIF_EQ2_RXINDICATIONLAYOUTOFRXINDICATIONFCTLIST
#define CANIF_EQ2_RXINDICATIONFCTLISTIDXOFRXPDUCONFIG
#define CANIF_EQ2_RXPDUCANIDOFRXPDUCONFIG
#define CANIF_EQ2_RXPDUDLCOFRXPDUCONFIG
#define CANIF_EQ2_RXPDUMASKOFRXPDUCONFIG
#define CANIF_EQ2_UPPERPDUIDOFRXPDUCONFIG
#define CANIF_EQ2_TRCVTOCTRLMAP
#define CANIF_EQ2_BITPOS2TXPDUIDOFFSETOFTXBUFFERPRIOBYCANIDCONFIG
#define CANIF_EQ2_TXBUFFERPRIOBYCANIDBASEIDXOFTXBUFFERPRIOBYCANIDCONFIG
#define CANIF_EQ2_TXQUEUEFLAGSENDIDXOFTXBUFFERPRIOBYCANIDCONFIG
#define CANIF_EQ2_TXQUEUEFLAGSSTARTIDXOFTXBUFFERPRIOBYCANIDCONFIG
#define CANIF_EQ2_TXCONFIRMATIONFCTLIST
#define CANIF_EQ2_CANIDOFTXPDUCONFIG
#define CANIF_EQ2_CTRLSTATESIDXOFTXPDUCONFIG
#define CANIF_EQ2_ISTXPDUTRUNCATIONOFTXPDUCONFIG
#define CANIF_EQ2_MAILBOXCONFIGIDXOFTXPDUCONFIG
#define CANIF_EQ2_TXCONFIRMATIONFCTLISTIDXOFTXPDUCONFIG
#define CANIF_EQ2_TXPDULENGTHOFTXPDUCONFIG
#define CANIF_EQ2_UPPERLAYERTXPDUIDOFTXPDUCONFIG
#define CANIF_EQ2_TXQUEUEIDXOFTXPDUQUEUEINDEX
#define CANIF_EQ2_TXQUEUEUSEDOFTXPDUQUEUEINDEX
#define CANIF_EQ2_BUSOFFNOTIFICATIONFCTPTROFPCCONFIG                                                (&(CanIf_BusOffNotificationFctPtr))
#define CANIF_EQ2_CANIFCTRLID2MAPPEDTXBUFFERSCONFIGOFPCCONFIG                                       CanIf_CanIfCtrlId2MappedTxBuffersConfig
#define CANIF_EQ2_CTRLMODEINDICATIONFCTPTROFPCCONFIG                                                (&(CanIf_CtrlModeIndicationFctPtr))
#define CANIF_EQ2_CTRLSTATESOFPCCONFIG                                                              CanIf_CtrlStates.raw
#define CANIF_EQ2_MAILBOXCONFIGOFPCCONFIG                                                           CanIf_MailBoxConfig
#define CANIF_EQ2_MAPPEDTXBUFFERSCONFIGOFPCCONFIG                                                   CanIf_MappedTxBuffersConfig
#define CANIF_EQ2_RXINDICATIONFCTLISTOFPCCONFIG                                                     CanIf_RxIndicationFctList
#define CANIF_EQ2_RXPDUCONFIGOFPCCONFIG                                                             CanIf_RxPduConfig
#define CANIF_EQ2_TRCVMODEINDICATIONFCTPTROFPCCONFIG                                                (&(CanIf_TrcvModeIndicationFctPtr))
#define CANIF_EQ2_TRCVTOCTRLMAPOFPCCONFIG                                                           CanIf_TrcvToCtrlMap
#define CANIF_EQ2_TXBUFFERPRIOBYCANIDBASEOFPCCONFIG                                                 CanIf_TxBufferPrioByCanIdBase.raw
#define CANIF_EQ2_TXBUFFERPRIOBYCANIDCONFIGOFPCCONFIG                                               CanIf_TxBufferPrioByCanIdConfig
#define CANIF_EQ2_TXCONFIRMATIONFCTLISTOFPCCONFIG                                                   CanIf_TxConfirmationFctList
#define CANIF_EQ2_TXPDUCONFIGOFPCCONFIG                                                             CanIf_TxPduConfig
#define CANIF_EQ2_TXPDUQUEUEINDEXOFPCCONFIG                                                         CanIf_TxPduQueueIndex
#define CANIF_EQ2_TXQUEUEFLAGSOFPCCONFIG                                                            CanIf_TxQueueFlags.raw
#define CANIF_EQ2_TXQUEUEOFPCCONFIG                                                                 CanIf_TxQueue.raw

#define CanIf_Config_Ptr                                                                            NULL_PTR
#define CanIf_Config                                                                                NULL_PTR

#define CANIF_CHECK_INIT_POINTER                                                                    STD_OFF
#define CANIF_FINAL_MAGIC_NUMBER                                                                    0x3C1Eu
#define CANIF_INDIVIDUAL_POSTBUILD                                                                  STD_OFF
#define CANIF_INIT_DATA                                                                             CANIF_CONST
#define CANIF_INIT_DATA_HASH_CODE                                                                   -713533440
#define CANIF_USE_ECUM_BSW_ERROR_HOOK                                                               STD_OFF
#define CANIF_USE_INIT_POINTER                                                                      STD_OFF

#define CANIF_PBCONFIG                                                                              STD_OFF
#define CANIF_LTCONFIGIDXOFPBCONFIG                                                                 STD_OFF
#define CANIF_PCCONFIGIDXOFPBCONFIG                                                                 STD_OFF


/**********************************************************************************************************************
  GLOBAL FUNCTION MACROS
**********************************************************************************************************************/
#define CanIf_GetBusOffNotificationFctPtrOfPCConfig()                                               (&(CanIf_BusOffNotificationFctPtr))
#define CanIf_GetCanIfCtrlId2MappedTxBuffersConfigOfPCConfig()                                      CanIf_CanIfCtrlId2MappedTxBuffersConfig
#define CanIf_GetCtrlModeIndicationFctPtrOfPCConfig()                                               (&(CanIf_CtrlModeIndicationFctPtr))
#define CanIf_GetCtrlStatesOfPCConfig()                                                             CanIf_CtrlStates.raw
#define CanIf_GetGeneratorCompatibilityVersionOfPCConfig()                                          0x0212u
#define CanIf_GetGeneratorVersionOfPCConfig()                                                       0x00070000u
#define CanIf_GetMailBoxConfigOfPCConfig()                                                          CanIf_MailBoxConfig
#define CanIf_GetMappedTxBuffersConfigOfPCConfig()                                                  CanIf_MappedTxBuffersConfig
#define CanIf_GetMaxTrcvHandleIdPlusOneOfPCConfig()                                                 [!"$numTrcvs"!]u
#define CanIf_GetRxIndicationFctListOfPCConfig()                                                    CanIf_RxIndicationFctList
#define CanIf_GetRxPduConfigOfPCConfig()                                                            CanIf_RxPduConfig
#define CanIf_GetSizeOfCanIfCtrlId2MappedTxBuffersConfigOfPCConfig()                                [!"$numCtrls"!]u
#define CanIf_GetSizeOfCtrlStatesOfPCConfig()                                                       [!"$numCtrls"!]u
#define CanIf_GetSizeOfMailBoxConfigOfPCConfig()                                                    [!"$numMailboxes"!]u
#define CanIf_GetSizeOfMappedTxBuffersConfigOfPCConfig()                                            [!"$numBuffers"!]u
#define CanIf_GetSizeOfRxIndicationFctListOfPCConfig()                                              [!"$rxCbkCount"!]u
#define CanIf_GetSizeOfRxPduConfigOfPCConfig()                                                      [!"$numRxPdus"!]u
#define CanIf_GetSizeOfTrcvToCtrlMapOfPCConfig()                                                    [!"$numTrcvs"!]u
#define CanIf_GetSizeOfTxBufferPrioByCanIdBaseOfPCConfig()                                          [!"$numBuffers"!]u
#define CanIf_GetSizeOfTxBufferPrioByCanIdConfigOfPCConfig()                                        [!"$numBuffers"!]u
#define CanIf_GetSizeOfTxConfirmationFctListOfPCConfig()                                            [!"$txCbkCount"!]u
#define CanIf_GetSizeOfTxPduConfigOfPCConfig()                                                      [!"$numTxPdus"!]u
#define CanIf_GetSizeOfTxPduQueueIndexOfPCConfig()                                                  [!"$numTxPdus"!]u
#define CanIf_GetSizeOfTxQueueFlagsOfPCConfig()                                                     [!"$txFlagsWords"!]u
#define CanIf_GetSizeOfTxQueueOfPCConfig()                                                          [!"$numTxPdus"!]u
#define CanIf_GetTrcvModeIndicationFctPtrOfPCConfig()                                               (&(CanIf_TrcvModeIndicationFctPtr))
#define CanIf_GetTrcvToCtrlMapOfPCConfig()                                                          CanIf_TrcvToCtrlMap
#define CanIf_GetTxBufferPrioByCanIdBaseOfPCConfig()                                                CanIf_TxBufferPrioByCanIdBase.raw
#define CanIf_GetTxBufferPrioByCanIdConfigOfPCConfig()                                              CanIf_TxBufferPrioByCanIdConfig
#define CanIf_GetTxConfirmationFctListOfPCConfig()                                                  CanIf_TxConfirmationFctList
#define CanIf_GetTxPduConfigOfPCConfig()                                                            CanIf_TxPduConfig
#define CanIf_GetTxPduQueueIndexOfPCConfig()                                                        CanIf_TxPduQueueIndex
#define CanIf_GetTxQueueFlagsOfPCConfig()                                                           CanIf_TxQueueFlags.raw
#define CanIf_GetTxQueueOfPCConfig()                                                                CanIf_TxQueue.raw

#define CanIf_GetBusOffNotificationFctPtr()                                                         ((*(CanIf_GetBusOffNotificationFctPtrOfPCConfig())))
#define CanIf_GetMappedTxBuffersConfigEndIdxOfCanIfCtrlId2MappedTxBuffersConfig(Index)              (CanIf_GetCanIfCtrlId2MappedTxBuffersConfigOfPCConfig()[(Index)].MappedTxBuffersConfigEndIdxOfCanIfCtrlId2MappedTxBuffersConfig)
#define CanIf_GetMappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig(Index)            (CanIf_GetCanIfCtrlId2MappedTxBuffersConfigOfPCConfig()[(Index)].MappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig)
#define CanIf_GetCtrlModeIndicationFctPtr()                                                         ((*(CanIf_GetCtrlModeIndicationFctPtrOfPCConfig())))
#define CanIf_GetCtrlModeOfCtrlStates(Index)                                                        (CanIf_GetCtrlStatesOfPCConfig()[(Index)].CtrlModeOfCtrlStates)
#define CanIf_GetPduModeOfCtrlStates(Index)                                                         (CanIf_GetCtrlStatesOfPCConfig()[(Index)].PduModeOfCtrlStates)
#define CanIf_GetCtrlStatesIdxOfMailBoxConfig(Index)                                                (CanIf_GetMailBoxConfigOfPCConfig()[(Index)].CtrlStatesIdxOfMailBoxConfig)
#define CanIf_GetMailBoxTypeOfMailBoxConfig(Index)                                                  (CanIf_GetMailBoxConfigOfPCConfig()[(Index)].MailBoxTypeOfMailBoxConfig)
#define CanIf_GetPduIdFirstOfMailBoxConfig(Index)                                                   (CanIf_GetMailBoxConfigOfPCConfig()[(Index)].PduIdFirstOfMailBoxConfig)
#define CanIf_GetPduIdLastOfMailBoxConfig(Index)                                                    (CanIf_GetMailBoxConfigOfPCConfig()[(Index)].PduIdLastOfMailBoxConfig)
#define CanIf_GetTxBufferCfgIdxOfMailBoxConfig(Index)                                               (CanIf_GetMailBoxConfigOfPCConfig()[(Index)].TxBufferCfgIdxOfMailBoxConfig)
#define CanIf_GetTxBufferCfgOfMailBoxConfig(Index)                                                  (CanIf_GetMailBoxConfigOfPCConfig()[(Index)].TxBufferCfgOfMailBoxConfig)
#define CanIf_GetTxBufferHandlingTypeOfMailBoxConfig(Index)                                         (CanIf_GetMailBoxConfigOfPCConfig()[(Index)].TxBufferHandlingTypeOfMailBoxConfig)
#define CanIf_GetMailBoxConfigIdxOfMappedTxBuffersConfig(Index)                                     (CanIf_GetMappedTxBuffersConfigOfPCConfig()[(Index)].MailBoxConfigIdxOfMappedTxBuffersConfig)
#define CanIf_GetRxIndicationFctOfRxIndicationFctList(Index)                                        (CanIf_GetRxIndicationFctListOfPCConfig()[(Index)].RxIndicationFctOfRxIndicationFctList)
#define CanIf_GetRxIndicationLayoutOfRxIndicationFctList(Index)                                     (CanIf_GetRxIndicationFctListOfPCConfig()[(Index)].RxIndicationLayoutOfRxIndicationFctList)
#define CanIf_GetRxIndicationFctListIdxOfRxPduConfig(Index)                                         (CanIf_GetRxPduConfigOfPCConfig()[(Index)].RxIndicationFctListIdxOfRxPduConfig)
#define CanIf_GetRxPduCanIdOfRxPduConfig(Index)                                                     (CanIf_GetRxPduConfigOfPCConfig()[(Index)].RxPduCanIdOfRxPduConfig)
#define CanIf_GetRxPduDlcOfRxPduConfig(Index)                                                       (CanIf_GetRxPduConfigOfPCConfig()[(Index)].RxPduDlcOfRxPduConfig)
#define CanIf_GetRxPduMaskOfRxPduConfig(Index)                                                      (CanIf_GetRxPduConfigOfPCConfig()[(Index)].RxPduMaskOfRxPduConfig)
#define CanIf_GetUpperPduIdOfRxPduConfig(Index)                                                     (CanIf_GetRxPduConfigOfPCConfig()[(Index)].UpperPduIdOfRxPduConfig)
#define CanIf_GetTrcvModeIndicationFctPtr()                                                         ((*(CanIf_GetTrcvModeIndicationFctPtrOfPCConfig())))
#define CanIf_GetTrcvToCtrlMap(Index)                                                               (CanIf_GetTrcvToCtrlMapOfPCConfig()[(Index)])
#define CanIf_GetTxBufferPrioByCanIdBase(Index)                                                     (CanIf_GetTxBufferPrioByCanIdBaseOfPCConfig()[(Index)])
#define CanIf_GetBitPos2TxPduIdOffsetOfTxBufferPrioByCanIdConfig(Index)                             (CanIf_GetTxBufferPrioByCanIdConfigOfPCConfig()[(Index)].BitPos2TxPduIdOffsetOfTxBufferPrioByCanIdConfig)
#define CanIf_GetTxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdConfig(Index)                       (CanIf_GetTxBufferPrioByCanIdConfigOfPCConfig()[(Index)].TxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdConfig)
#define CanIf_GetTxQueueFlagsEndIdxOfTxBufferPrioByCanIdConfig(Index)                               (CanIf_GetTxBufferPrioByCanIdConfigOfPCConfig()[(Index)].TxQueueFlagsEndIdxOfTxBufferPrioByCanIdConfig)
#define CanIf_GetTxQueueFlagsStartIdxOfTxBufferPrioByCanIdConfig(Index)                             (CanIf_GetTxBufferPrioByCanIdConfigOfPCConfig()[(Index)].TxQueueFlagsStartIdxOfTxBufferPrioByCanIdConfig)
#define CanIf_GetTxConfirmationFctList(Index)                                                       (CanIf_GetTxConfirmationFctListOfPCConfig()[(Index)])
#define CanIf_GetCanIdOfTxPduConfig(Index)                                                          (CanIf_GetTxPduConfigOfPCConfig()[(Index)].CanIdOfTxPduConfig)
#define CanIf_GetCtrlStatesIdxOfTxPduConfig(Index)                                                  (CanIf_GetTxPduConfigOfPCConfig()[(Index)].CtrlStatesIdxOfTxPduConfig)
#define CanIf_IsIsTxPduTruncationOfTxPduConfig(Index)                                               ((CanIf_GetTxPduConfigOfPCConfig()[(Index)].IsTxPduTruncationOfTxPduConfig) != FALSE)
#define CanIf_GetMailBoxConfigIdxOfTxPduConfig(Index)                                               (CanIf_GetTxPduConfigOfPCConfig()[(Index)].MailBoxConfigIdxOfTxPduConfig)
#define CanIf_GetTxConfirmationFctListIdxOfTxPduConfig(Index)                                       (CanIf_GetTxPduConfigOfPCConfig()[(Index)].TxConfirmationFctListIdxOfTxPduConfig)
#define CanIf_GetTxPduLengthOfTxPduConfig(Index)                                                    (CanIf_GetTxPduConfigOfPCConfig()[(Index)].TxPduLengthOfTxPduConfig)
#define CanIf_GetUpperLayerTxPduIdOfTxPduConfig(Index)                                              (CanIf_GetTxPduConfigOfPCConfig()[(Index)].UpperLayerTxPduIdOfTxPduConfig)
#define CanIf_GetTxQueueIdxOfTxPduQueueIndex(Index)                                                 (CanIf_GetTxPduQueueIndexOfPCConfig()[(Index)].TxQueueIdxOfTxPduQueueIndex)
#define CanIf_GetTxQueue(Index)                                                                     (CanIf_GetTxQueueOfPCConfig()[(Index)])
#define CanIf_GetTxQueueFlags(Index)                                                                (CanIf_GetTxQueueFlagsOfPCConfig()[(Index)])
#define CanIf_GetGeneratorCompatibilityVersion()                                                    CanIf_GetGeneratorCompatibilityVersionOfPCConfig()
#define CanIf_GetGeneratorVersion()                                                                 CanIf_GetGeneratorVersionOfPCConfig()
#define CanIf_IsTxBufferCfgUsedOfMailBoxConfig(Index)                                               (((boolean)(CanIf_GetTxBufferCfgIdxOfMailBoxConfig(Index) != CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG)) != FALSE)
#define CanIf_GetMaxTrcvHandleIdPlusOne()                                                           CanIf_GetMaxTrcvHandleIdPlusOneOfPCConfig()
#define CanIf_GetSizeOfCanIfCtrlId2MappedTxBuffersConfig()                                          CanIf_GetSizeOfCanIfCtrlId2MappedTxBuffersConfigOfPCConfig()
#define CanIf_GetSizeOfCtrlStates()                                                                 CanIf_GetSizeOfCtrlStatesOfPCConfig()
#define CanIf_GetSizeOfMailBoxConfig()                                                              CanIf_GetSizeOfMailBoxConfigOfPCConfig()
#define CanIf_GetSizeOfMappedTxBuffersConfig()                                                      CanIf_GetSizeOfMappedTxBuffersConfigOfPCConfig()
#define CanIf_GetSizeOfRxIndicationFctList()                                                        CanIf_GetSizeOfRxIndicationFctListOfPCConfig()
#define CanIf_GetSizeOfRxPduConfig()                                                                CanIf_GetSizeOfRxPduConfigOfPCConfig()
#define CanIf_GetSizeOfTrcvToCtrlMap()                                                              CanIf_GetSizeOfTrcvToCtrlMapOfPCConfig()
#define CanIf_GetSizeOfTxBufferPrioByCanIdBase()                                                    CanIf_GetSizeOfTxBufferPrioByCanIdBaseOfPCConfig()
#define CanIf_GetSizeOfTxBufferPrioByCanIdConfig()                                                  CanIf_GetSizeOfTxBufferPrioByCanIdConfigOfPCConfig()
#define CanIf_GetSizeOfTxConfirmationFctList()                                                      CanIf_GetSizeOfTxConfirmationFctListOfPCConfig()
#define CanIf_GetSizeOfTxPduConfig()                                                                CanIf_GetSizeOfTxPduConfigOfPCConfig()
#define CanIf_GetSizeOfTxPduQueueIndex()                                                            CanIf_GetSizeOfTxPduQueueIndexOfPCConfig()
#define CanIf_GetSizeOfTxQueue()                                                                    CanIf_GetSizeOfTxQueueOfPCConfig()
#define CanIf_GetSizeOfTxQueueFlags()                                                               CanIf_GetSizeOfTxQueueFlagsOfPCConfig()
#define CanIf_IsTxQueueUsedOfTxPduQueueIndex(Index)                                                 (((boolean)(CanIf_GetTxQueueIdxOfTxPduQueueIndex(Index) != CANIF_NO_TXQUEUEIDXOFTXPDUQUEUEINDEX)) != FALSE)

#define CanIf_SetCtrlModeOfCtrlStates(Index, Value)                                                 CanIf_GetCtrlStatesOfPCConfig()[(Index)].CtrlModeOfCtrlStates = (Value)
#define CanIf_SetPduModeOfCtrlStates(Index, Value)                                                  CanIf_GetCtrlStatesOfPCConfig()[(Index)].PduModeOfCtrlStates = (Value)
#define CanIf_SetTxBufferPrioByCanIdBase(Index, Value)                                              CanIf_GetTxBufferPrioByCanIdBaseOfPCConfig()[(Index)] = (Value)
#define CanIf_SetTxQueue(Index, Value)                                                              CanIf_GetTxQueueOfPCConfig()[(Index)] = (Value)
#define CanIf_SetTxQueueFlags(Index, Value)                                                         CanIf_GetTxQueueFlagsOfPCConfig()[(Index)] = (Value)

#define CanIf_HasBusOffNotificationFctPtr()                                                         (TRUE != FALSE)
#define CanIf_HasCanIfCtrlId2MappedTxBuffersConfig()                                                (TRUE != FALSE)
#define CanIf_HasMappedTxBuffersConfigEndIdxOfCanIfCtrlId2MappedTxBuffersConfig()                   (TRUE != FALSE)
#define CanIf_HasMappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig()                 (TRUE != FALSE)
#define CanIf_HasCtrlModeIndicationFctPtr()                                                         (TRUE != FALSE)
#define CanIf_HasCtrlStates()                                                                       (TRUE != FALSE)
#define CanIf_HasCtrlModeOfCtrlStates()                                                             (TRUE != FALSE)
#define CanIf_HasPduModeOfCtrlStates()                                                              (TRUE != FALSE)
#define CanIf_HasGeneratorCompatibilityVersion()                                                    (TRUE != FALSE)
#define CanIf_HasGeneratorVersion()                                                                 (TRUE != FALSE)
#define CanIf_HasMailBoxConfig()                                                                    (TRUE != FALSE)
#define CanIf_HasCtrlStatesIdxOfMailBoxConfig()                                                     (TRUE != FALSE)
#define CanIf_HasMailBoxTypeOfMailBoxConfig()                                                       (TRUE != FALSE)
#define CanIf_HasPduIdFirstOfMailBoxConfig()                                                        (TRUE != FALSE)
#define CanIf_HasPduIdLastOfMailBoxConfig()                                                         (TRUE != FALSE)
#define CanIf_HasTxBufferCfgIdxOfMailBoxConfig()                                                    (TRUE != FALSE)
#define CanIf_HasTxBufferCfgOfMailBoxConfig()                                                       (TRUE != FALSE)
#define CanIf_HasTxBufferCfgUsedOfMailBoxConfig()                                                   (TRUE != FALSE)
#define CanIf_HasTxBufferHandlingTypeOfMailBoxConfig()                                              (TRUE != FALSE)
#define CanIf_HasMappedTxBuffersConfig()                                                            (TRUE != FALSE)
#define CanIf_HasMailBoxConfigIdxOfMappedTxBuffersConfig()                                          (TRUE != FALSE)
#define CanIf_HasMaxTrcvHandleIdPlusOne()                                                           (TRUE != FALSE)
#define CanIf_HasRxIndicationFctList()                                                              (TRUE != FALSE)
#define CanIf_HasRxIndicationFctOfRxIndicationFctList()                                             (TRUE != FALSE)
#define CanIf_HasRxIndicationLayoutOfRxIndicationFctList()                                          (TRUE != FALSE)
#define CanIf_HasRxPduConfig()                                                                      [!IF "$numRxPdus > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasRxIndicationFctListIdxOfRxPduConfig()                                              [!IF "$numRxPdus > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasRxPduCanIdOfRxPduConfig()                                                          [!IF "$numRxPdus > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasRxPduDlcOfRxPduConfig()                                                            [!IF "$numRxPdus > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasRxPduMaskOfRxPduConfig()                                                           [!IF "$numRxPdus > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasUpperPduIdOfRxPduConfig()                                                          [!IF "$numRxPdus > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasSizeOfCanIfCtrlId2MappedTxBuffersConfig()                                          (TRUE != FALSE)
#define CanIf_HasSizeOfCtrlStates()                                                                 (TRUE != FALSE)
#define CanIf_HasSizeOfMailBoxConfig()                                                              (TRUE != FALSE)
#define CanIf_HasSizeOfMappedTxBuffersConfig()                                                      (TRUE != FALSE)
#define CanIf_HasSizeOfRxIndicationFctList()                                                        (TRUE != FALSE)
#define CanIf_HasSizeOfRxPduConfig()                                                                (TRUE != FALSE)
#define CanIf_HasSizeOfTrcvToCtrlMap()                                                              [!IF "$numTrcvs > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasSizeOfTxBufferPrioByCanIdBase()                                                    (TRUE != FALSE)
#define CanIf_HasSizeOfTxBufferPrioByCanIdConfig()                                                  (TRUE != FALSE)
#define CanIf_HasSizeOfTxConfirmationFctList()                                                      (TRUE != FALSE)
#define CanIf_HasSizeOfTxPduConfig()                                                                (TRUE != FALSE)
#define CanIf_HasSizeOfTxPduQueueIndex()                                                            (TRUE != FALSE)
#define CanIf_HasSizeOfTxQueue()                                                                    (TRUE != FALSE)
#define CanIf_HasSizeOfTxQueueFlags()                                                               (TRUE != FALSE)
#define CanIf_HasTrcvModeIndicationFctPtr()                                                         (TRUE != FALSE)
#define CanIf_HasTrcvToCtrlMap()                                                                    [!IF "$numTrcvs > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasTxBufferPrioByCanIdBase()                                                          (TRUE != FALSE)
#define CanIf_HasTxBufferPrioByCanIdConfig()                                                        (TRUE != FALSE)
#define CanIf_HasBitPos2TxPduIdOffsetOfTxBufferPrioByCanIdConfig()                                  (TRUE != FALSE)
#define CanIf_HasTxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdConfig()                            (TRUE != FALSE)
#define CanIf_HasTxQueueFlagsEndIdxOfTxBufferPrioByCanIdConfig()                                    (TRUE != FALSE)
#define CanIf_HasTxQueueFlagsStartIdxOfTxBufferPrioByCanIdConfig()                                  (TRUE != FALSE)
#define CanIf_HasTxConfirmationFctList()                                                            (TRUE != FALSE)
#define CanIf_HasTxPduConfig()                                                                      (TRUE != FALSE)
#define CanIf_HasCanIdOfTxPduConfig()                                                               (TRUE != FALSE)
#define CanIf_HasCtrlStatesIdxOfTxPduConfig()                                                       (TRUE != FALSE)
#define CanIf_HasIsTxPduTruncationOfTxPduConfig()                                                   (TRUE != FALSE)
#define CanIf_HasMailBoxConfigIdxOfTxPduConfig()                                                    (TRUE != FALSE)
#define CanIf_HasTxConfirmationFctListIdxOfTxPduConfig()                                            (TRUE != FALSE)
#define CanIf_HasTxPduLengthOfTxPduConfig()                                                         (TRUE != FALSE)
#define CanIf_HasUpperLayerTxPduIdOfTxPduConfig()                                                   (TRUE != FALSE)
#define CanIf_HasTxPduQueueIndex()                                                                  (TRUE != FALSE)
#define CanIf_HasTxQueueIdxOfTxPduQueueIndex()                                                      (TRUE != FALSE)
#define CanIf_HasTxQueueUsedOfTxPduQueueIndex()                                                     (TRUE != FALSE)
#define CanIf_HasTxQueue()                                                                          (TRUE != FALSE)
#define CanIf_HasTxQueueFlags()                                                                     (TRUE != FALSE)
#define CanIf_HasPCConfig()                                                                         (TRUE != FALSE)
#define CanIf_HasBusOffNotificationFctPtrOfPCConfig()                                               (TRUE != FALSE)
#define CanIf_HasCanIfCtrlId2MappedTxBuffersConfigOfPCConfig()                                      (TRUE != FALSE)
#define CanIf_HasCtrlModeIndicationFctPtrOfPCConfig()                                               (TRUE != FALSE)
#define CanIf_HasCtrlStatesOfPCConfig()                                                             (TRUE != FALSE)
#define CanIf_HasGeneratorCompatibilityVersionOfPCConfig()                                          (TRUE != FALSE)
#define CanIf_HasGeneratorVersionOfPCConfig()                                                       (TRUE != FALSE)
#define CanIf_HasMailBoxConfigOfPCConfig()                                                          (TRUE != FALSE)
#define CanIf_HasMappedTxBuffersConfigOfPCConfig()                                                  (TRUE != FALSE)
#define CanIf_HasMaxTrcvHandleIdPlusOneOfPCConfig()                                                 (TRUE != FALSE)
#define CanIf_HasRxIndicationFctListOfPCConfig()                                                    (TRUE != FALSE)
#define CanIf_HasRxPduConfigOfPCConfig()                                                            [!IF "$numRxPdus > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasSizeOfCanIfCtrlId2MappedTxBuffersConfigOfPCConfig()                                (TRUE != FALSE)
#define CanIf_HasSizeOfCtrlStatesOfPCConfig()                                                       (TRUE != FALSE)
#define CanIf_HasSizeOfMailBoxConfigOfPCConfig()                                                    (TRUE != FALSE)
#define CanIf_HasSizeOfMappedTxBuffersConfigOfPCConfig()                                            (TRUE != FALSE)
#define CanIf_HasSizeOfRxIndicationFctListOfPCConfig()                                              (TRUE != FALSE)
#define CanIf_HasSizeOfRxPduConfigOfPCConfig()                                                      (TRUE != FALSE)
#define CanIf_HasSizeOfTrcvToCtrlMapOfPCConfig()                                                    [!IF "$numTrcvs > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasSizeOfTxBufferPrioByCanIdBaseOfPCConfig()                                          (TRUE != FALSE)
#define CanIf_HasSizeOfTxBufferPrioByCanIdConfigOfPCConfig()                                        (TRUE != FALSE)
#define CanIf_HasSizeOfTxConfirmationFctListOfPCConfig()                                            (TRUE != FALSE)
#define CanIf_HasSizeOfTxPduConfigOfPCConfig()                                                      (TRUE != FALSE)
#define CanIf_HasSizeOfTxPduQueueIndexOfPCConfig()                                                  (TRUE != FALSE)
#define CanIf_HasSizeOfTxQueueFlagsOfPCConfig()                                                     (TRUE != FALSE)
#define CanIf_HasSizeOfTxQueueOfPCConfig()                                                          (TRUE != FALSE)
#define CanIf_HasTrcvModeIndicationFctPtrOfPCConfig()                                               (TRUE != FALSE)
#define CanIf_HasTrcvToCtrlMapOfPCConfig()                                                          [!IF "$numTrcvs > 0"!](TRUE != FALSE)[!ELSE!](FALSE != FALSE)[!ENDIF!]
#define CanIf_HasTxBufferPrioByCanIdBaseOfPCConfig()                                                (TRUE != FALSE)
#define CanIf_HasTxBufferPrioByCanIdConfigOfPCConfig()                                              (TRUE != FALSE)
#define CanIf_HasTxConfirmationFctListOfPCConfig()                                                  (TRUE != FALSE)
#define CanIf_HasTxPduConfigOfPCConfig()                                                            (TRUE != FALSE)
#define CanIf_HasTxPduQueueIndexOfPCConfig()                                                        (TRUE != FALSE)
#define CanIf_HasTxQueueFlagsOfPCConfig()                                                           (TRUE != FALSE)
#define CanIf_HasTxQueueOfPCConfig()                                                                (TRUE != FALSE)

#define CanIf_IncCtrlModeOfCtrlStates(Index)                                                        CanIf_GetCtrlModeOfCtrlStates(Index)++
#define CanIf_IncPduModeOfCtrlStates(Index)                                                         CanIf_GetPduModeOfCtrlStates(Index)++
#define CanIf_IncTxQueueFlags(Index)                                                                CanIf_GetTxQueueFlags(Index)++
#define CanIf_DecCtrlModeOfCtrlStates(Index)                                                        CanIf_GetCtrlModeOfCtrlStates(Index)--
#define CanIf_DecPduModeOfCtrlStates(Index)                                                         CanIf_GetPduModeOfCtrlStates(Index)--
#define CanIf_DecTxQueueFlags(Index)                                                                CanIf_GetTxQueueFlags(Index)--
#define CanIf_AddCtrlModeOfCtrlStates(Index, Value)                                                 CanIf_SetCtrlModeOfCtrlStates(Index, (CanIf_GetCtrlModeOfCtrlStates(Index) + Value))
#define CanIf_AddPduModeOfCtrlStates(Index, Value)                                                  CanIf_SetPduModeOfCtrlStates(Index, (CanIf_GetPduModeOfCtrlStates(Index) + Value))
#define CanIf_AddTxQueueFlags(Index, Value)                                                         CanIf_SetTxQueueFlags(Index, (CanIf_GetTxQueueFlags(Index) + Value))
#define CanIf_SubCtrlModeOfCtrlStates(Index, Value)                                                 CanIf_SetCtrlModeOfCtrlStates(Index, (CanIf_GetCtrlModeOfCtrlStates(Index) - Value))
#define CanIf_SubPduModeOfCtrlStates(Index, Value)                                                  CanIf_SetPduModeOfCtrlStates(Index, (CanIf_GetPduModeOfCtrlStates(Index) - Value))
#define CanIf_SubTxQueueFlags(Index, Value)                                                         CanIf_SetTxQueueFlags(Index, (CanIf_GetTxQueueFlags(Index) - Value))


/**********************************************************************************************************************
  GLOBAL DATA TYPES AND STRUCTURES
**********************************************************************************************************************/
typedef uint8_least CanIf_CanIfCtrlId2MappedTxBuffersConfigIterType;
typedef uint8_least CanIf_CtrlStatesIterType;
typedef uint8_least CanIf_MailBoxConfigIterType;
typedef uint8_least CanIf_MappedTxBuffersConfigIterType;
typedef uint8_least CanIf_RxIndicationFctListIterType;
typedef uint8_least CanIf_RxPduConfigIterType;
typedef uint8_least CanIf_TrcvToCtrlMapIterType;
typedef uint8_least CanIf_TxBufferPrioByCanIdBaseIterType;
typedef uint8_least CanIf_TxBufferPrioByCanIdConfigIterType;
typedef uint8_least CanIf_TxConfirmationFctListIterType;
typedef uint8_least CanIf_TxPduConfigIterType;
typedef uint8_least CanIf_TxPduQueueIndexIterType;
typedef uint8_least CanIf_TxQueueIterType;
typedef uint8_least CanIf_TxQueueFlagsIterType;

typedef uint8 CanIf_MappedTxBuffersConfigEndIdxOfCanIfCtrlId2MappedTxBuffersConfigType;
typedef uint8 CanIf_MappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfigType;
typedef uint16 CanIf_GeneratorCompatibilityVersionType;
typedef uint32 CanIf_GeneratorVersionType;
typedef uint8 CanIf_CtrlStatesIdxOfMailBoxConfigType;
typedef uint8 CanIf_PduIdFirstOfMailBoxConfigType;
typedef uint8 CanIf_PduIdLastOfMailBoxConfigType;
typedef uint8 CanIf_TxBufferCfgIdxOfMailBoxConfigType;
typedef uint8 CanIf_TxBufferCfgOfMailBoxConfigType;
typedef boolean CanIf_TxBufferCfgUsedOfMailBoxConfigType;
typedef uint8 CanIf_TxBufferHandlingTypeOfMailBoxConfigType;
typedef uint8 CanIf_MailBoxConfigIdxOfMappedTxBuffersConfigType;
typedef uint8 CanIf_MaxTrcvHandleIdPlusOneType;
typedef uint8 CanIf_RxIndicationFctListIdxOfRxPduConfigType;
typedef uint16 CanIf_RxPduCanIdOfRxPduConfigType;
typedef uint8 CanIf_RxPduDlcOfRxPduConfigType;
typedef uint32 CanIf_RxPduMaskOfRxPduConfigType;
typedef PduIdType CanIf_UpperPduIdOfRxPduConfigType;
typedef uint8 CanIf_SizeOfCanIfCtrlId2MappedTxBuffersConfigType;
typedef uint8 CanIf_SizeOfCtrlStatesType;
typedef uint8 CanIf_SizeOfMailBoxConfigType;
typedef uint8 CanIf_SizeOfMappedTxBuffersConfigType;
typedef uint8 CanIf_SizeOfRxIndicationFctListType;
typedef uint8 CanIf_SizeOfRxPduConfigType;
typedef uint8 CanIf_SizeOfTrcvToCtrlMapType;
typedef uint8 CanIf_SizeOfTxBufferPrioByCanIdBaseType;
typedef uint8 CanIf_SizeOfTxBufferPrioByCanIdConfigType;
typedef uint8 CanIf_SizeOfTxConfirmationFctListType;
typedef uint8 CanIf_SizeOfTxPduConfigType;
typedef uint8 CanIf_SizeOfTxPduQueueIndexType;
typedef uint8 CanIf_SizeOfTxQueueType;
typedef uint8 CanIf_SizeOfTxQueueFlagsType;
typedef uint8 CanIf_TrcvToCtrlMapType;
typedef uint8 CanIf_BitPos2TxPduIdOffsetOfTxBufferPrioByCanIdConfigType;
typedef uint8 CanIf_TxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdConfigType;
typedef uint8 CanIf_TxQueueFlagsEndIdxOfTxBufferPrioByCanIdConfigType;
typedef uint8 CanIf_TxQueueFlagsStartIdxOfTxBufferPrioByCanIdConfigType;
typedef uint16 CanIf_CanIdOfTxPduConfigType;
typedef uint8 CanIf_CtrlStatesIdxOfTxPduConfigType;
typedef boolean CanIf_IsTxPduTruncationOfTxPduConfigType;
typedef uint8 CanIf_MailBoxConfigIdxOfTxPduConfigType;
typedef uint8 CanIf_TxConfirmationFctListIdxOfTxPduConfigType;
typedef uint8 CanIf_TxPduLengthOfTxPduConfigType;
typedef PduIdType CanIf_UpperLayerTxPduIdOfTxPduConfigType;
typedef uint8 CanIf_TxQueueIdxOfTxPduQueueIndexType;
typedef boolean CanIf_TxQueueUsedOfTxPduQueueIndexType;
typedef uint32 CanIf_TxQueueFlagsType;

typedef struct sCanIf_CanIfCtrlId2MappedTxBuffersConfigType
{
  CanIf_MappedTxBuffersConfigEndIdxOfCanIfCtrlId2MappedTxBuffersConfigType MappedTxBuffersConfigEndIdxOfCanIfCtrlId2MappedTxBuffersConfig;
  CanIf_MappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfigType MappedTxBuffersConfigStartIdxOfCanIfCtrlId2MappedTxBuffersConfig;
} CanIf_CanIfCtrlId2MappedTxBuffersConfigType;

typedef struct sCanIf_CtrlStatesType
{
  CanIf_ControllerModeType CtrlModeOfCtrlStates;
  CanIf_PduGetModeType PduModeOfCtrlStates;
} CanIf_CtrlStatesType;

typedef struct sCanIf_MailBoxConfigType
{
  CanIf_CtrlStatesIdxOfMailBoxConfigType CtrlStatesIdxOfMailBoxConfig;
  CanIf_PduIdFirstOfMailBoxConfigType PduIdFirstOfMailBoxConfig;
  CanIf_PduIdLastOfMailBoxConfigType PduIdLastOfMailBoxConfig;
  CanIf_TxBufferCfgOfMailBoxConfigType TxBufferCfgOfMailBoxConfig;
  CanIf_TxBufferCfgIdxOfMailBoxConfigType TxBufferCfgIdxOfMailBoxConfig;
  CanIf_TxBufferHandlingTypeOfMailBoxConfigType TxBufferHandlingTypeOfMailBoxConfig;
  CanIf_MailBoxTypeType MailBoxTypeOfMailBoxConfig;
} CanIf_MailBoxConfigType;

typedef struct sCanIf_MappedTxBuffersConfigType
{
  CanIf_MailBoxConfigIdxOfMappedTxBuffersConfigType MailBoxConfigIdxOfMappedTxBuffersConfig;
} CanIf_MappedTxBuffersConfigType;

typedef struct sCanIf_RxIndicationFctListType
{
  CanIf_RxIndicationFctType RxIndicationFctOfRxIndicationFctList;
  CanIf_RxIndicationLayoutType RxIndicationLayoutOfRxIndicationFctList;
} CanIf_RxIndicationFctListType;

typedef struct sCanIf_RxPduConfigType
{
  CanIf_RxPduMaskOfRxPduConfigType RxPduMaskOfRxPduConfig;
  CanIf_RxPduCanIdOfRxPduConfigType RxPduCanIdOfRxPduConfig;
  CanIf_UpperPduIdOfRxPduConfigType UpperPduIdOfRxPduConfig;
  CanIf_RxIndicationFctListIdxOfRxPduConfigType RxIndicationFctListIdxOfRxPduConfig;
  CanIf_RxPduDlcOfRxPduConfigType RxPduDlcOfRxPduConfig;
} CanIf_RxPduConfigType;

typedef struct sCanIf_TxBufferPrioByCanIdConfigType
{
  CanIf_BitPos2TxPduIdOffsetOfTxBufferPrioByCanIdConfigType BitPos2TxPduIdOffsetOfTxBufferPrioByCanIdConfig;
  CanIf_TxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdConfigType TxBufferPrioByCanIdBaseIdxOfTxBufferPrioByCanIdConfig;
  CanIf_TxQueueFlagsEndIdxOfTxBufferPrioByCanIdConfigType TxQueueFlagsEndIdxOfTxBufferPrioByCanIdConfig;
  CanIf_TxQueueFlagsStartIdxOfTxBufferPrioByCanIdConfigType TxQueueFlagsStartIdxOfTxBufferPrioByCanIdConfig;
} CanIf_TxBufferPrioByCanIdConfigType;

typedef struct sCanIf_TxPduConfigType
{
  CanIf_CanIdOfTxPduConfigType CanIdOfTxPduConfig;
  CanIf_UpperLayerTxPduIdOfTxPduConfigType UpperLayerTxPduIdOfTxPduConfig;
  CanIf_IsTxPduTruncationOfTxPduConfigType IsTxPduTruncationOfTxPduConfig;
  CanIf_CtrlStatesIdxOfTxPduConfigType CtrlStatesIdxOfTxPduConfig;
  CanIf_MailBoxConfigIdxOfTxPduConfigType MailBoxConfigIdxOfTxPduConfig;
  CanIf_TxConfirmationFctListIdxOfTxPduConfigType TxConfirmationFctListIdxOfTxPduConfig;
  CanIf_TxPduLengthOfTxPduConfigType TxPduLengthOfTxPduConfig;
} CanIf_TxPduConfigType;

typedef struct sCanIf_TxPduQueueIndexType
{
  CanIf_TxQueueIdxOfTxPduQueueIndexType TxQueueIdxOfTxPduQueueIndex;
} CanIf_TxPduQueueIndexType;

typedef struct CanIf_CtrlStatesStructSTag
{
[!IF "node:exists(CanIfCtrlDrvCfg/*/CanIfCtrlCfg)"!][!//
[!LOOP "node:order(CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*, 'CanIfCtrlId')"!][!//
  CanIf_CtrlStatesType [!"node:name(.)"!];
[!ENDLOOP!][!//
[!ELSE!][!//
  CanIf_CtrlStatesType Ctrl_0;
[!ENDIF!][!//
} CanIf_CtrlStatesStructSType;

typedef struct CanIf_TxBufferPrioByCanIdBaseStructSTag
{
[!IF "node:exists(CanIfInitCfg/CanIfBufferCfg)"!][!//
[!LOOP "CanIfInitCfg/CanIfBufferCfg/*"!][!//
  CanIf_TxBufferPrioByCanIdBaseType [!"node:name(.)"!];
[!ENDLOOP!][!//
[!ELSE!][!//
  CanIf_TxBufferPrioByCanIdBaseType Buffer_0;
[!ENDIF!][!//
} CanIf_TxBufferPrioByCanIdBaseStructSType;

typedef struct CanIf_TxQueueStructSTag
{
[!IF "node:exists(CanIfInitCfg/CanIfTxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfTxPduCfg/*, 'CanIfTxPduId')"!][!//
  CanIf_TxPrioByCanIdType [!"node:name(.)"!];
[!ENDLOOP!][!//
[!ELSE!][!//
  CanIf_TxPrioByCanIdType TxPdu_0;
[!ENDIF!][!//
} CanIf_TxQueueStructSType;

typedef struct CanIf_TxQueueFlagsStructSTag
{
[!IF "node:exists(CanIfInitCfg/CanIfBufferCfg)"!][!//
[!LOOP "CanIfInitCfg/CanIfBufferCfg/*"!][!//
  CanIf_TxQueueFlagsType [!"node:name(.)"!];
[!ENDLOOP!][!//
[!ELSE!][!//
  CanIf_TxQueueFlagsType Buffer_0;
[!ENDIF!][!//
} CanIf_TxQueueFlagsStructSType;

typedef union CanIf_CtrlStatesUTag
{
  CanIf_CtrlStatesType raw[[!"$numCtrls"!]];
  CanIf_CtrlStatesStructSType str;
} CanIf_CtrlStatesUType;

typedef union CanIf_TxBufferPrioByCanIdBaseUTag
{
  CanIf_TxBufferPrioByCanIdBaseType raw[[!"$numBuffers"!]];
  CanIf_TxBufferPrioByCanIdBaseStructSType str;
} CanIf_TxBufferPrioByCanIdBaseUType;

typedef union CanIf_TxQueueUTag
{
  CanIf_TxPrioByCanIdType raw[[!"$numTxPdus"!]];
  CanIf_TxQueueStructSType str;
} CanIf_TxQueueUType;

typedef union CanIf_TxQueueFlagsUTag
{
  CanIf_TxQueueFlagsType raw[[!"$txFlagsWords"!]];
  CanIf_TxQueueFlagsStructSType str;
} CanIf_TxQueueFlagsUType;

typedef P2CONST(CanIf_BusOffNotificationFctType, TYPEDEF, CANIF_CONST) CanIf_BusOffNotificationFctPtrPtrType;
typedef P2CONST(CanIf_CanIfCtrlId2MappedTxBuffersConfigType, TYPEDEF, CANIF_CONST) CanIf_CanIfCtrlId2MappedTxBuffersConfigPtrType;
typedef P2CONST(CanIf_CtrlModeIndicationFctType, TYPEDEF, CANIF_CONST) CanIf_CtrlModeIndicationFctPtrPtrType;
typedef P2VAR(CanIf_CtrlStatesType, TYPEDEF, CANIF_VAR_NOINIT) CanIf_CtrlStatesPtrType;
typedef P2CONST(CanIf_MailBoxConfigType, TYPEDEF, CANIF_CONST) CanIf_MailBoxConfigPtrType;
typedef P2CONST(CanIf_MappedTxBuffersConfigType, TYPEDEF, CANIF_CONST) CanIf_MappedTxBuffersConfigPtrType;
typedef P2CONST(CanIf_RxIndicationFctListType, TYPEDEF, CANIF_CONST) CanIf_RxIndicationFctListPtrType;
typedef P2CONST(CanIf_RxPduConfigType, TYPEDEF, CANIF_CONST) CanIf_RxPduConfigPtrType;
typedef P2CONST(CanIf_TrcvModeIndicationFctType, TYPEDEF, CANIF_CONST) CanIf_TrcvModeIndicationFctPtrPtrType;
typedef P2CONST(CanIf_TrcvToCtrlMapType, TYPEDEF, CANIF_CONST) CanIf_TrcvToCtrlMapPtrType;
typedef P2VAR(CanIf_TxBufferPrioByCanIdBaseType, TYPEDEF, CANIF_VAR_NOINIT) CanIf_TxBufferPrioByCanIdBasePtrType;
typedef P2CONST(CanIf_TxBufferPrioByCanIdConfigType, TYPEDEF, CANIF_CONST) CanIf_TxBufferPrioByCanIdConfigPtrType;
typedef P2CONST(CanIf_TxConfirmationFctType, TYPEDEF, CANIF_CONST) CanIf_TxConfirmationFctListPtrType;
typedef P2CONST(CanIf_TxPduConfigType, TYPEDEF, CANIF_CONST) CanIf_TxPduConfigPtrType;
typedef P2CONST(CanIf_TxPduQueueIndexType, TYPEDEF, CANIF_CONST) CanIf_TxPduQueueIndexPtrType;
typedef P2VAR(CanIf_TxPrioByCanIdType, TYPEDEF, CANIF_VAR_NOINIT) CanIf_TxQueuePtrType;
typedef P2VAR(CanIf_TxQueueFlagsType, TYPEDEF, CANIF_VAR_NOINIT) CanIf_TxQueueFlagsPtrType;

typedef struct sCanIf_PCConfigType
{
  uint8 CanIf_PCConfigNeverUsed;
} CanIf_PCConfigType;

typedef CanIf_PCConfigType CanIf_ConfigType;


/**********************************************************************************************************************
  GLOBAL DATA PROTOTYPES
**********************************************************************************************************************/
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_BusOffNotificationFctType, CANIF_CONST) CanIf_BusOffNotificationFctPtr;
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_CanIfCtrlId2MappedTxBuffersConfigType, CANIF_CONST) CanIf_CanIfCtrlId2MappedTxBuffersConfig[[!"$numCtrls"!]];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_CtrlModeIndicationFctType, CANIF_CONST) CanIf_CtrlModeIndicationFctPtr;
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_MailBoxConfigType, CANIF_CONST) CanIf_MailBoxConfig[[!"$numMailboxes"!]];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_MappedTxBuffersConfigType, CANIF_CONST) CanIf_MappedTxBuffersConfig[[!"$numBuffers"!]];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_RxIndicationFctListType, CANIF_CONST) CanIf_RxIndicationFctList[[!"$rxCbkCount"!]];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!IF "$numRxPdus > 0"!][!//
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_RxPduConfigType, CANIF_CONST) CanIf_RxPduConfig[[!"$numRxPdus"!]];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!ENDIF!][!//
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_TrcvModeIndicationFctType, CANIF_CONST) CanIf_TrcvModeIndicationFctPtr;
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!IF "$numTrcvs > 0"!][!//
#define CANIF_START_SEC_CONST_8BIT
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_TrcvToCtrlMapType, CANIF_CONST) CanIf_TrcvToCtrlMap[[!"$effTrcvs"!]];
#define CANIF_STOP_SEC_CONST_8BIT
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!ENDIF!][!//
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_TxBufferPrioByCanIdConfigType, CANIF_CONST) CanIf_TxBufferPrioByCanIdConfig[[!"$numBuffers"!]];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_TxConfirmationFctType, CANIF_CONST) CanIf_TxConfirmationFctList[[!"$txCbkCount"!]];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_TxPduConfigType, CANIF_CONST) CanIf_TxPduConfig[[!"$numTxPdus"!]];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(CanIf_TxPduQueueIndexType, CANIF_CONST) CanIf_TxPduQueueIndex[[!"$numTxPdus"!]];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(CanIf_CtrlStatesUType, CANIF_VAR_NOINIT) CanIf_CtrlStates;
#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(CanIf_TxBufferPrioByCanIdBaseUType, CANIF_VAR_NOINIT) CanIf_TxBufferPrioByCanIdBase;
#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(CanIf_TxQueueUType, CANIF_VAR_NOINIT) CanIf_TxQueue;
#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_VAR_NOINIT_32BIT
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern VAR(CanIf_TxQueueFlagsUType, CANIF_VAR_NOINIT) CanIf_TxQueueFlags;
#define CANIF_STOP_SEC_VAR_NOINIT_32BIT
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* CANIF_CFG_H */
[!ENDSELECT!]

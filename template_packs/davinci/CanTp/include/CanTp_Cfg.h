[!AUTOSPACING!]
[!/* Vector MICROSAR CanTp_Cfg.h CSL Template */!]
#if !defined(CANTP_CFG_H)
#define CANTP_CFG_H

#include "ComStack_Types.h"

[!VAR "mainPeriod" = "0.005"!][!//
[!IF "node:exists(as:modconf('CanTp')[1]/CanTpConfig/CanTpMainFunctionPeriod)"!][!//
[!VAR "mainPeriod" = "as:modconf('CanTp')[1]/CanTpConfig/CanTpMainFunctionPeriod"!][!//
[!ENDIF!][!//
[!VAR "taskCycleMs" = "num:i(round($mainPeriod * 1000))"!][!//
[!IF "$taskCycleMs <= 0"!][!VAR "taskCycleMs" = "5"!][!ENDIF!][!//
[!/* Compute General Flags */!][!//
[!VAR "versionInfoApi" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpVersionInfoApi"!][!//
[!VAR "devErrorDetect" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpDevErrorDetect"!][!//
[!VAR "tcEnabled" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpTc"!][!//
[!VAR "rcEnabled" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpRc"!][!//
[!VAR "paddingActive" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpPaddingActive"!][!//
[!VAR "havePaddingByte" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpHavePaddingByte"!][!//
[!VAR "paddingByteHex" = "'0xCCu'"!][!//
[!IF "node:exists(as:modconf('CanTp')[1]/CanTpGeneral/CanTpPaddingByte)"!][!//
[!VAR "paddingByteHex" = "concat('0x', text:toupper(substring(num:inttohex(num:i(as:modconf('CanTp')[1]/CanTpGeneral/CanTpPaddingByte), 2), 3)), 'u')"!][!//
[!ENDIF!][!//
[!VAR "splitMain" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpEnableSplitMainFunction"!][!//
[!VAR "stdAddr" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpSupportStandardAddressing"!][!//
[!VAR "extAddr" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpSupportExtendedAddressing"!][!//
[!VAR "mix11Addr" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpSupportMixed11Addressing"!][!//
[!VAR "mix29Addr" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpSupportMixed29Addressing"!][!//
[!VAR "normFixedAddr" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpSupportNormalFixedAddressing"!][!//
[!VAR "custAddr" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpSupportCustomAddressing"!][!//
[!VAR "onlyFirstFc" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpUseOnlyFirstFc"!][!//
[!VAR "chgParamApi" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpChangeParameterApi"!][!//
[!VAR "readParamApi" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpReadParameterApi"!][!//
[!VAR "onlyNotifyInformed" = "as:modconf('CanTp')[1]/CanTpGeneral/CanTpOnlyNotifyInformedAppl"!][!//
[!/* Compute Rx/Tx aggregate properties */!][!//
[!VAR "maxFrameLen" = "8"!][!//
[!VAR "hasPhysRx" = "'false'"!][!//
[!VAR "hasFuncRx" = "'false'"!][!//
[!VAR "hasPhysTx" = "'false'"!][!//
[!VAR "hasFuncTx" = "'false'"!][!//
[!VAR "firstNarTick" = "7"!][!//
[!VAR "firstNbrTick" = "11"!][!//
[!VAR "firstNcrTick" = "31"!][!//
[!VAR "firstStMinTick" = "10"!][!//
[!VAR "rxIdxTmp" = "0"!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpRxNSduId)], 'num:i(CanTpRxNSduId)')"!][!//
  [!IF "node:exists(CanTpRxDl) and num:i(CanTpRxDl) > $maxFrameLen"!][!VAR "maxFrameLen" = "num:i(CanTpRxDl)"!][!ENDIF!][!//
  [!IF "CanTpRxTaType = 'CANTP_PHYSICAL'"!][!VAR "hasPhysRx" = "'true'"!][!ENDIF!][!//
  [!IF "CanTpRxTaType = 'CANTP_FUNCTIONAL'"!][!VAR "hasFuncRx" = "'true'"!][!ENDIF!][!//
  [!IF "$rxIdxTmp = 0"!][!//
    [!IF "node:exists(CanTpNar)"!][!VAR "firstNarTick" = "num:i(round(CanTpNar div $mainPeriod) + 1)"!][!ENDIF!][!//
    [!IF "node:exists(CanTpNbr)"!][!VAR "firstNbrTick" = "num:i(round(CanTpNbr div $mainPeriod) + 1)"!][!ENDIF!][!//
    [!IF "node:exists(CanTpNcr)"!][!VAR "firstNcrTick" = "num:i(round(CanTpNcr div $mainPeriod) + 1)"!][!ENDIF!][!//
    [!IF "node:exists(CanTpSTmin)"!][!VAR "firstStMinTick" = "num:i(round(CanTpSTmin * 1000))"!][!ENDIF!][!//
  [!ENDIF!][!//
  [!VAR "rxIdxTmp" = "$rxIdxTmp + 1"!][!//
[!ENDLOOP!][!//
[!VAR "numRxSdus" = "$rxIdxTmp"!][!//
[!VAR "firstNasTick" = "7"!][!//
[!VAR "firstNbsTick" = "19"!][!//
[!VAR "firstNcsTick" = "21"!][!//
[!VAR "firstTxCanIdHex" = "'0x000007DFu'"!][!//
[!VAR "firstLoLayerTxPduSym" = "'0u'"!][!//
[!VAR "firstPduRTxSduSym" = "'0u'"!][!//
[!VAR "firstRxFcPduSym" = "'CANTP_INVALID_HDL'"!][!//
[!VAR "firstTxPduCfmSym" = "'CANTP_INVALID_HDL'"!][!//
[!VAR "firstTxCancel" = "'FALSE'"!][!//
[!VAR "firstTxAddrFmt" = "'CANTP_NORMAL_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG'"!][!//
[!VAR "firstTxTaType" = "'CANTP_PHYSICAL_TXTATYPEOFTXSDUCFG'"!][!//
[!VAR "txIdxTmp" = "0"!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpTxNSduId)], 'num:i(CanTpTxNSduId)')"!][!//
  [!IF "node:exists(CanTpTxDl) and num:i(CanTpTxDl) > $maxFrameLen"!][!VAR "maxFrameLen" = "num:i(CanTpTxDl)"!][!ENDIF!][!//
  [!IF "CanTpTxTaType = 'CANTP_PHYSICAL'"!][!VAR "hasPhysTx" = "'true'"!][!ENDIF!][!//
  [!IF "CanTpTxTaType = 'CANTP_FUNCTIONAL'"!][!VAR "hasFuncTx" = "'true'"!][!ENDIF!][!//
  [!IF "$txIdxTmp = 0"!][!//
    [!IF "node:exists(CanTpNas)"!][!VAR "firstNasTick" = "num:i(round(CanTpNas div $mainPeriod) + 1)"!][!ENDIF!][!//
    [!IF "node:exists(CanTpNbs)"!][!VAR "firstNbsTick" = "num:i(round(CanTpNbs div $mainPeriod) + 1)"!][!ENDIF!][!//
    [!IF "node:exists(CanTpNcs)"!][!VAR "firstNcsTick" = "num:i(round(CanTpNcs div $mainPeriod) + 1)"!][!ENDIF!][!//
    [!IF "node:exists(CanTpTc) and CanTpTc = 'true'"!][!VAR "firstTxCancel" = "'TRUE'"!][!ENDIF!][!//
    [!VAR "txSduRef" = "CanTpTxNSduRef"!][!//
    [!VAR "txNpduRef" = "''"!][!//
    [!IF "node:exists(*[node:exists(CanTpTxNPduConfirmationPduId)])"!][!//
      [!VAR "txNpduRef" = "*[node:exists(CanTpTxNPduConfirmationPduId)]/CanTpTxNPduRef"!][!//
      [!VAR "firstTxPduCfmSym" = "concat('CanTpConf_CanTpTxNPdu_', node:name(*[node:exists(CanTpTxNPduConfirmationPduId)]))"!]
    [!ENDIF!][!//
    [!IF "node:exists(*[node:exists(CanTpRxFcNPduId)])"!][!//
      [!VAR "firstRxFcPduSym" = "concat('CanTpConf_CanTpRxFcNPdu_', node:name(*[node:exists(CanTpRxFcNPduId)]))"!]
    [!ENDIF!][!//
    [!IF "node:exists(as:modconf('CanIf'))"!][!//
      [!LOOP "as:modconf('CanIf')[1]/CanIfInitCfg/*[CanIfTxPduRef = $txNpduRef]"!][!//
        [!VAR "firstLoLayerTxPduSym" = "concat('CanIfConf_CanIfTxPduCfg_', @name)"!][!//
        [!IF "node:exists(CanIfTxPduCanId)"!][!//
          [!VAR "firstTxCanIdHex" = "concat('0x', text:toupper(substring(num:inttohex(num:i(CanIfTxPduCanId), 8), 3)), 'u')"!][!//
        [!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDIF!][!//
    [!IF "node:exists(as:modconf('PduR'))"!][!//
      [!LOOP "as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRDestPduRef = $txSduRef]"!][!//
        [!VAR "firstPduRTxSduSym" = "concat('PduRConf_PduRDestPdu_', @name)"!][!//
      [!ENDLOOP!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
  [!VAR "txIdxTmp" = "$txIdxTmp + 1"!][!//
[!ENDLOOP!][!//
[!VAR "numTxSdus" = "$txIdxTmp"!][!//
[!VAR "maxPayloadLen" = "num:i($maxFrameLen - 1)"!][!//
[!VAR "supportCanFd" = "'false'"!][!//
[!IF "$maxFrameLen > 8"!][!VAR "supportCanFd" = "'true'"!][!ENDIF!][!//
[!VAR "numRxNPdus" = "count(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpRxNPduId)])"!][!//
[!IF "$numRxNPdus = 0"!][!VAR "numRxNPdus" = "$numRxSdus"!][!ENDIF!][!//
[!VAR "numTxPduMaps" = "$numTxSdus"!][!//

#ifndef CANTP_USE_DUMMY_STATEMENT
#define CANTP_USE_DUMMY_STATEMENT STD_ON
#endif
#ifndef CANTP_DUMMY_STATEMENT
#define CANTP_DUMMY_STATEMENT(v) (v)=(v)
#endif
#ifndef CANTP_DUMMY_STATEMENT_CONST
#define CANTP_DUMMY_STATEMENT_CONST(v) (void)(v)
#endif
#ifndef CANTP_ATOMIC_BIT_ACCESS_IN_BITFIELD
#define CANTP_ATOMIC_BIT_ACCESS_IN_BITFIELD STD_OFF
#endif
#ifndef CANTP_ATOMIC_VARIABLE_ACCESS
#define CANTP_ATOMIC_VARIABLE_ACCESS 32u
#endif
#ifndef CANTP_PROCESSOR_TONGXIN_THA6206
#define CANTP_PROCESSOR_TONGXIN_THA6206
#endif
#ifndef CANTP_COMP_LLVMHIGHTEC
#define CANTP_COMP_LLVMHIGHTEC
#endif
#ifndef CANTP_GEN_GENERATOR_MSR
#define CANTP_GEN_GENERATOR_MSR
#endif
#ifndef CANTP_CPUTYPE_BITORDER_LSB2MSB
#define CANTP_CPUTYPE_BITORDER_LSB2MSB
#endif
#ifndef CANTP_CONFIGURATION_VARIANT_PRECOMPILE
#define CANTP_CONFIGURATION_VARIANT_PRECOMPILE 1
#endif
#ifndef CANTP_CONFIGURATION_VARIANT_LINKTIME
#define CANTP_CONFIGURATION_VARIANT_LINKTIME 2
#endif
#ifndef CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE
#define CANTP_CONFIGURATION_VARIANT_POSTBUILD_LOADABLE 3
#endif
#ifndef CANTP_CONFIGURATION_VARIANT
#define CANTP_CONFIGURATION_VARIANT CANTP_CONFIGURATION_VARIANT_PRECOMPILE
#endif
#ifndef CANTP_POSTBUILD_VARIANT_SUPPORT
#define CANTP_POSTBUILD_VARIANT_SUPPORT STD_OFF
#endif

#define CANTP_CFG_GEN_MAJOR_VERSION                                            7u
#define CANTP_CFG_GEN_MINOR_VERSION                                            0u
#define CANTP_CFG_GEN_PATCH_VERSION                                            2u

#define CANTP_VERSION_INFO_API                                                 [!IF "$versionInfoApi = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_DEV_ERROR_DETECT                                                 [!IF "$devErrorDetect = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_DEV_ERROR_REPORT                                                 [!IF "$devErrorDetect = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TC                                                               [!IF "$tcEnabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_RC                                                               [!IF "$rcEnabled = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_INVALID_HDL                                                      ((PduIdType) 255u)
#define CANTP_TASK_CYCLE                                                       [!"num:i($taskCycleMs)"!]u
#define CANTP_MAX_FRAME_LENGTH                                                 [!"num:i($maxFrameLen)"!]u
#define CANTP_MAX_PAYLOAD_LENGTH                                               [!"num:i($maxPayloadLen)"!]u
#define CANTP_MAX_SDU_METADATA_LENGTH                                          0u
#define CANTP_NUM_RX_CHANNELS                                                  CanTp_GetSizeOfRxState()
#define CANTP_NUM_RX_SDUS                                                      [!"num:i($numRxSdus)"!]
#define CANTP_NUM_TX_CHANNELS                                                  CanTp_GetSizeOfTxState()
#define CANTP_NUM_TX_SDUS                                                      [!"num:i($numTxSdus)"!]
#define CANTP_PDU_METADATA_LENGTH                                              4u
#define CANTP_SIZEOF_PDULENGTHTYPE                                             2

#define CanTpSinglePartitionMemory                                             0u

#define CANTP_MODE_FULL_DUPLEX                                                 1u
#define CANTP_MODE_HALF_DUPLEX                                                 0u
#define CANTP_TATYPE_FUNCTIONAL                                                1u
#define CANTP_TATYPE_PHYSICAL                                                  0u
#define CANTP_ADDRESS_FORMAT_CUSTOM                                            5u
#define CANTP_ADDRESS_FORMAT_EXTENDED                                          1u
#define CANTP_ADDRESS_FORMAT_MIXED11                                           2u
#define CANTP_ADDRESS_FORMAT_MIXED29                                           4u
#define CANTP_ADDRESS_FORMAT_NORMALFIXED                                       3u
#define CANTP_ADDRESS_FORMAT_STANDARD                                          0u
#define CANTP_CANTYPE_CAN20                                                    0u
#define CANTP_CANTYPE_CANFD                                                    1u

#define CANTP_GENERATOR_COMPATIBILITY_VERSION                                  0x000C8E46u
#define CANTP_CAN20_PADDING_ACTIVE                                             [!IF "$paddingActive = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_HAVE_PADDING_BYTE                                                [!IF "$havePaddingByte = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_PADDING_PATTERN                                                  [!"$paddingByteHex"!]
#define CANTP_DYN_CHANNEL_ASSIGNMENT                                           STD_OFF
#define CANTP_STANDARD_ADDRESSING                                              [!IF "$stdAddr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXTENDED_ADDRESSING                                              [!IF "$extAddr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_MIXED11_ADDRESSING                                               [!IF "$mix11Addr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_MIXED29_ADDRESSING                                               [!IF "$mix29Addr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_NORMALFIXED_ADDRESSING                                           [!IF "$normFixedAddr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_CUSTOM_ADDRESSING                                                [!IF "$custAddr = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SINGLE_RX_BUFFER_OPTIMIZED                                       STD_OFF
#define CANTP_RXTX_MAINFUNCTION_API                                            [!IF "$splitMain = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_CONSTANT_BS                                                      STD_ON
#define CANTP_REJECT_FC_WITH_RES_STMIN                                         STD_OFF
#define CANTP_USE_ONLY_FIRST_FC                                                [!IF "$onlyFirstFc = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_ENABLE_CHANGE_PARAM                                              [!IF "$chgParamApi = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_ENABLE_READ_PARAM                                                [!IF "$readParamApi = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_ONLY_NOTIFY_INFORMED_APPL                                        [!IF "$onlyNotifyInformed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TRANSMIT_QUEUE                                                   STD_OFF
#define CANTP_SUPPORT_MULTI_PARTITION                                          STD_OFF
#define CANTP_SUPPORT_LONG_FF                                                  STD_OFF
#define CANTP_PDUR_API_AR_VERSION                                              0x412
#define CANTP_SYNC_TRANSMIT                                                    STD_OFF
#define CANTP_SUPPORT_CANFD                                                    [!IF "$supportCanFd = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_STMIN_BY_APPL                                                    STD_OFF
#define CANTP_DCM_REQUEST_DETECT                                               STD_OFF
#define CANTP_GENERIC_CONNECTIONS                                              STD_OFF
#define CANTP_NON_STRICT_LENGTHCHECK                                           STD_OFF
#define CanTp_ApplStartSeparationTime
#define CANTP_LOLAYER_CANIF                                                    STD_ON
#define CANTP_LOLAYER_TC                                                       STD_OFF
#define CanTp_CanIfCancelTransmit(Dir, ConnId, PduId)
#define CanTp_CanIfTransmit(Dir, ConnId, PduId, Data)                          (CanIf_Transmit((PduId),(Data)))

/* Symbolic Name Handles */
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpRxNSduId)], 'num:i(CanTpRxNSduId)')"!][!//
#define CanTpConf_CanTpRxNSdu_[!"@name"!] [!"num:i(CanTpRxNSduId)"!]u
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpTxNSduId)], 'num:i(CanTpTxNSduId)')"!][!//
#define CanTpConf_CanTpTxNSdu_[!"@name"!] [!"num:i(CanTpTxNSduId)"!]u
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpRxFcNPduId)], 'num:i(CanTpRxFcNPduId)')"!][!//
#define CanTpConf_CanTpRxFcNPdu_[!"@name"!] [!"num:i(CanTpRxFcNPduId)"!]u
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpRxNPduId)], 'num:i(CanTpRxNPduId)')"!][!//
#define CanTpConf_CanTpRxNPdu_[!"@name"!] [!"num:i(CanTpRxNPduId)"!]u
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpTxFcNPduConfirmationPduId)], 'num:i(CanTpTxFcNPduConfirmationPduId)')"!][!//
#define CanTpConf_CanTpTxFcNPdu_[!"@name"!] [!"num:i(CanTpTxFcNPduConfirmationPduId)"!]u
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpTxNPduConfirmationPduId)], 'num:i(CanTpTxNPduConfirmationPduId)')"!][!//
#define CanTpConf_CanTpTxNPdu_[!"@name"!] [!"num:i(CanTpTxNPduConfirmationPduId)"!]u
[!ENDLOOP!][!//

/* CSL Precompile Data Switches */
#define CANTP_CALCBS                                                                                STD_ON
#define CANTP_COMPATIBILITYVERSION                                                                  STD_ON
#define CANTP_DYNFCPARAMETERS                                                                       STD_OFF
#define CANTP_FINALMAGICNUMBER                                                                      STD_OFF
#define CANTP_INITDATAHASHCODE                                                                      STD_OFF
#define CANTP_LOLAYERFCTS                                                                           STD_OFF
#define CANTP_CANCELTRANSMITFCTOFLOLAYERFCTS                                                        STD_OFF
#define CANTP_TRANSMITFCTOFLOLAYERFCTS                                                              STD_OFF
#define CANTP_METADATAGETTERADDRESS_EXTENSION_8                                                     STD_OFF
#define CANTP_METADATAGETTERCAN_ID_32                                                               STD_OFF
#define CANTP_METADATAGETTERSOURCE_ADDRESS_16                                                       STD_OFF
#define CANTP_METADATAGETTERTARGET_ADDRESS_16                                                       STD_OFF
#define CANTP_METADATASETTERADDRESS_EXTENSION_8                                                     STD_OFF
#define CANTP_METADATASETTERCAN_ID_32                                                               STD_OFF
#define CANTP_METADATASETTERSOURCE_ADDRESS_16                                                       STD_OFF
#define CANTP_METADATASETTERTARGET_ADDRESS_16                                                       STD_OFF
#define CANTP_PARTITIONIDENTIFIERS                                                                  STD_ON
#define CANTP_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS                                            STD_ON
#define CANTP_PARTITIONSNVOFPARTITIONIDENTIFIERS                                                    STD_ON
#define CANTP_PARTITIONLOOKUPTABLE                                                                  STD_OFF
#define CANTP_OSAPPLICATIONTOCANTPOFPARTITIONLOOKUPTABLE                                            STD_OFF
#define CANTP_RXCHANNELMAP                                                                          STD_OFF
#define CANTP_RXPDU2RXSDUIND                                                                        STD_ON
#define CANTP_RXPDU2TXSDUIND                                                                        [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_RXPDUMAP                                                                              STD_ON
#define CANTP_ADDRESSINGFORMATOFRXPDUMAP                                                            STD_ON
#define CANTP_GENERICCONNECTIONOFRXPDUMAP                                                           STD_ON
#define CANTP_METADATAGETTERCAN_ID_32IDXOFRXPDUMAP                                                  STD_OFF
#define CANTP_METADATAGETTERCAN_ID_32USEDOFRXPDUMAP                                                 STD_OFF
#define CANTP_PDUMETADATAOFRXPDUMAP                                                                 STD_ON
#define CANTP_RXPDU2RXSDUENDIDXOFRXPDUMAP                                                           STD_ON
#define CANTP_RXPDU2RXSDUPARTITIONIDXOFRXPDUMAP                                                     STD_ON
#define CANTP_RXPDU2RXSDUSTARTIDXOFRXPDUMAP                                                         STD_ON
#define CANTP_RXPDU2RXSDUUSEDOFRXPDUMAP                                                             STD_ON
#define CANTP_RXPDU2TXSDUENDIDXOFRXPDUMAP                                                           STD_ON
#define CANTP_RXPDU2TXSDUPARTITIONIDXOFRXPDUMAP                                                     STD_ON
#define CANTP_RXPDU2TXSDUSTARTIDXOFRXPDUMAP                                                         STD_ON
#define CANTP_RXPDU2TXSDUUSEDOFRXPDUMAP                                                             STD_ON
#define CANTP_RXSDUCFG                                                                              STD_ON
#define CANTP_BLOCKSIZEOFRXSDUCFG                                                                   STD_ON
#define CANTP_CANTYPEOFRXSDUCFG                                                                     STD_ON
#define CANTP_CHANNELMODEOFRXSDUCFG                                                                 STD_ON
#define CANTP_GENERICCONNECTIONOFRXSDUCFG                                                           STD_ON
#define CANTP_LOLAYERFCTSIDXOFRXSDUCFG                                                              STD_OFF
#define CANTP_LOLAYERTXFCPDUIDOFRXSDUCFG                                                            STD_ON
#define CANTP_METADATAGETTERADDRESS_EXTENSION_8IDXOFRXSDUCFG                                        STD_OFF
#define CANTP_METADATAGETTERADDRESS_EXTENSION_8USEDOFRXSDUCFG                                       STD_OFF
#define CANTP_METADATASETTERADDRESS_EXTENSION_8IDXOFRXSDUCFG                                        STD_OFF
#define CANTP_METADATASETTERADDRESS_EXTENSION_8USEDOFRXSDUCFG                                       STD_OFF
#define CANTP_METADATASETTERCAN_ID_32IDXOFRXSDUCFG                                                  STD_OFF
#define CANTP_METADATASETTERCAN_ID_32USEDOFRXSDUCFG                                                 STD_OFF
#define CANTP_METADATASETTERSOURCE_ADDRESS_16IDXOFRXSDUCFG                                          STD_OFF
#define CANTP_METADATASETTERSOURCE_ADDRESS_16USEDOFRXSDUCFG                                         STD_OFF
#define CANTP_METADATASETTERTARGET_ADDRESS_16IDXOFRXSDUCFG                                          STD_OFF
#define CANTP_METADATASETTERTARGET_ADDRESS_16USEDOFRXSDUCFG                                         STD_OFF
#define CANTP_NAROFRXSDUCFG                                                                         STD_ON
#define CANTP_NBROFRXSDUCFG                                                                         STD_ON
#define CANTP_NCROFRXSDUCFG                                                                         STD_ON
#define CANTP_PDUMETADATAOFRXSDUCFG                                                                 STD_OFF
#define CANTP_PDURRXSDUIDOFRXSDUCFG                                                                 STD_ON
#define CANTP_RXADDRESSOFRXSDUCFG                                                                   STD_ON
#define CANTP_RXADDRESSINGFORMATOFRXSDUCFG                                                          STD_ON
#define CANTP_RXMAXPAYLOADLENGTHOFRXSDUCFG                                                          STD_ON
#define CANTP_RXPADDINGACTIVATIONOFRXSDUCFG                                                         STD_ON
#define CANTP_RXPDUIDOFRXSDUCFG                                                                     STD_ON
#define CANTP_RXPDUMAPIDXOFRXSDUCFG                                                                 STD_ON
#define CANTP_RXPDUMAPUSEDOFRXSDUCFG                                                                STD_ON
#define CANTP_RXTATYPEOFRXSDUCFG                                                                    STD_ON
#define CANTP_RXWFTMAXOFRXSDUCFG                                                                    STD_ON
#define CANTP_STMINOFRXSDUCFG                                                                       STD_ON
#define CANTP_SDUMETADATALENGTHOFRXSDUCFG                                                           STD_ON
#define CANTP_TXFCADDRESSOFRXSDUCFG                                                                 STD_ON
#define CANTP_TXFCPDUCONFIRMATIONPDUIDOFRXSDUCFG                                                    STD_ON
#define CANTP_TXPDUMAPIDXOFRXSDUCFG                                                                 STD_ON
#define CANTP_TXPDUMAPUSEDOFRXSDUCFG                                                                STD_ON
#define CANTP_TXSDUCFGIDXOFRXSDUCFG                                                                 STD_ON
#define CANTP_TXSDUCFGUSEDOFRXSDUCFG                                                                STD_ON
#define CANTP_UPLAYERFCTSRXFCTPTRIDXOFRXSDUCFG                                                      STD_OFF
#define CANTP_UPLAYERFCTSRXFCTPTRUSEDOFRXSDUCFG                                                     STD_OFF
#define CANTP_RXSDUSNV2HDL                                                                          STD_ON
#define CANTP_INVALIDHNDOFRXSDUSNV2HDL                                                              STD_OFF
#define CANTP_RXNSDUHDLIDXOFRXSDUSNV2HDL                                                            STD_ON
#define CANTP_RXNSDUHDLPARTITIONIDXOFRXSDUSNV2HDL                                                   STD_ON
#define CANTP_RXNSDUHDLUSEDOFRXSDUSNV2HDL                                                           STD_ON
#define CANTP_RXSTATE                                                                               STD_ON
#define CANTP_SIZEOFCALCBS                                                                          STD_ON
#define CANTP_SIZEOFDYNFCPARAMETERS                                                                 STD_OFF
#define CANTP_SIZEOFLOLAYERFCTS                                                                     STD_OFF
#define CANTP_SIZEOFMETADATAGETTERADDRESS_EXTENSION_8                                               STD_OFF
#define CANTP_SIZEOFMETADATAGETTERCAN_ID_32                                                         STD_OFF
#define CANTP_SIZEOFMETADATAGETTERSOURCE_ADDRESS_16                                                 STD_OFF
#define CANTP_SIZEOFMETADATAGETTERTARGET_ADDRESS_16                                                 STD_OFF
#define CANTP_SIZEOFMETADATASETTERADDRESS_EXTENSION_8                                               STD_OFF
#define CANTP_SIZEOFMETADATASETTERCAN_ID_32                                                         STD_OFF
#define CANTP_SIZEOFMETADATASETTERSOURCE_ADDRESS_16                                                 STD_OFF
#define CANTP_SIZEOFMETADATASETTERTARGET_ADDRESS_16                                                 STD_OFF
#define CANTP_SIZEOFPARTITIONIDENTIFIERS                                                            STD_ON
#define CANTP_SIZEOFPARTITIONLOOKUPTABLE                                                            STD_OFF
#define CANTP_SIZEOFRXCHANNELMAP                                                                    STD_OFF
#define CANTP_SIZEOFRXPDU2RXSDUIND                                                                  STD_ON
#define CANTP_SIZEOFRXPDU2TXSDUIND                                                                  [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFRXPDUMAP                                                                        STD_ON
#define CANTP_SIZEOFRXSDUCFG                                                                        STD_ON
#define CANTP_SIZEOFRXSDUSNV2HDL                                                                    STD_ON
#define CANTP_SIZEOFRXSTATE                                                                         STD_ON
#define CANTP_SIZEOFTXCHANNELMAP                                                                    STD_OFF
#define CANTP_SIZEOFTXPDU2RXSDUIND                                                                  [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXPDU2TXSDUIND                                                                  [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXPDUMAP                                                                        [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXQUEUE                                                                         STD_OFF
#define CANTP_SIZEOFTXSDUCFG                                                                        [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXSDUSNV2HDL                                                                    [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXSEMAPHORES                                                                    [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXSTATE                                                                         [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFUPLAYERFCTSRXFCTPTR                                                             STD_OFF
#define CANTP_SIZEOFUPLAYERFCTSTXFCTPTR                                                             STD_OFF
#define CANTP_TXCHANNELMAP                                                                          STD_OFF
#define CANTP_TXPDU2RXSDUIND                                                                        [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TXPDU2TXSDUIND                                                                        [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TXPDUMAP                                                                              [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_CANIDOFTXPDUMAP                                                                       STD_ON
#define CANTP_MASKOFTXPDUMAP                                                                        STD_ON
#define CANTP_METADATASETTERCAN_ID_32IDXOFTXPDUMAP                                                  STD_OFF
#define CANTP_METADATASETTERCAN_ID_32USEDOFTXPDUMAP                                                 STD_OFF
#define CANTP_TXPDU2RXSDUENDIDXOFTXPDUMAP                                                           STD_ON
#define CANTP_TXPDU2RXSDUPARTITIONIDXOFTXPDUMAP                                                     STD_ON
#define CANTP_TXPDU2RXSDUSTARTIDXOFTXPDUMAP                                                         STD_ON
#define CANTP_TXPDU2RXSDUUSEDOFTXPDUMAP                                                             STD_ON
#define CANTP_TXPDU2TXSDUENDIDXOFTXPDUMAP                                                           STD_ON
#define CANTP_TXPDU2TXSDUPARTITIONIDXOFTXPDUMAP                                                     STD_ON
#define CANTP_TXPDU2TXSDUSTARTIDXOFTXPDUMAP                                                         STD_ON
#define CANTP_TXPDU2TXSDUUSEDOFTXPDUMAP                                                             STD_ON
#define CANTP_TXQUEUE                                                                               STD_OFF
#define CANTP_TXSDUCFG                                                                              [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_CANTYPEOFTXSDUCFG                                                                     STD_ON
#define CANTP_CHANNELMODEOFTXSDUCFG                                                                 STD_ON
#define CANTP_LOLAYERFCTSIDXOFTXSDUCFG                                                              STD_OFF
#define CANTP_LOLAYERTXPDUIDOFTXSDUCFG                                                              STD_ON
#define CANTP_METADATAGETTERADDRESS_EXTENSION_8IDXOFTXSDUCFG                                        STD_OFF
#define CANTP_METADATAGETTERADDRESS_EXTENSION_8USEDOFTXSDUCFG                                       STD_OFF
#define CANTP_METADATAGETTERCAN_ID_32IDXOFTXSDUCFG                                                  STD_OFF
#define CANTP_METADATAGETTERCAN_ID_32USEDOFTXSDUCFG                                                 STD_OFF
#define CANTP_METADATAGETTERSOURCE_ADDRESS_16IDXOFTXSDUCFG                                          STD_OFF
#define CANTP_METADATAGETTERSOURCE_ADDRESS_16USEDOFTXSDUCFG                                         STD_OFF
#define CANTP_METADATAGETTERTARGET_ADDRESS_16IDXOFTXSDUCFG                                          STD_OFF
#define CANTP_METADATAGETTERTARGET_ADDRESS_16USEDOFTXSDUCFG                                         STD_OFF
#define CANTP_METADATASETTERADDRESS_EXTENSION_8IDXOFTXSDUCFG                                        STD_OFF
#define CANTP_METADATASETTERADDRESS_EXTENSION_8USEDOFTXSDUCFG                                       STD_OFF
#define CANTP_METADATASETTERSOURCE_ADDRESS_16IDXOFTXSDUCFG                                          STD_OFF
#define CANTP_METADATASETTERSOURCE_ADDRESS_16USEDOFTXSDUCFG                                         STD_OFF
#define CANTP_METADATASETTERTARGET_ADDRESS_16IDXOFTXSDUCFG                                          STD_OFF
#define CANTP_METADATASETTERTARGET_ADDRESS_16USEDOFTXSDUCFG                                         STD_OFF
#define CANTP_NASOFTXSDUCFG                                                                         STD_ON
#define CANTP_NBSOFTXSDUCFG                                                                         STD_ON
#define CANTP_NCSOFTXSDUCFG                                                                         STD_ON
#define CANTP_PDUMETADATAOFTXSDUCFG                                                                 STD_OFF
#define CANTP_PDURTXSDUIDOFTXSDUCFG                                                                 STD_ON
#define CANTP_RXFCADDRESSOFTXSDUCFG                                                                 STD_ON
#define CANTP_RXFCPDUIDOFTXSDUCFG                                                                   STD_ON
#define CANTP_RXPDUMAPIDXOFTXSDUCFG                                                                 STD_ON
#define CANTP_RXPDUMAPUSEDOFTXSDUCFG                                                                STD_ON
#define CANTP_RXSDUCFGIDXOFTXSDUCFG                                                                 STD_ON
#define CANTP_RXSDUCFGUSEDOFTXSDUCFG                                                                STD_ON
#define CANTP_SDUMETADATALENGTHOFTXSDUCFG                                                           STD_ON
#define CANTP_TRANSMITCANCELLATIONOFTXSDUCFG                                                        STD_ON
#define CANTP_TXADDRESSOFTXSDUCFG                                                                   STD_ON
#define CANTP_TXADDRESSINGFORMATOFTXSDUCFG                                                          STD_ON
#define CANTP_TXMAXPAYLOADLENGTHOFTXSDUCFG                                                          STD_ON
#define CANTP_TXPADDINGACTIVATIONOFTXSDUCFG                                                         STD_ON
#define CANTP_TXPDUCONFIRMATIONPDUIDOFTXSDUCFG                                                      STD_ON
#define CANTP_TXPDUMAPIDXOFTXSDUCFG                                                                 STD_ON
#define CANTP_TXPDUMAPUSEDOFTXSDUCFG                                                                STD_ON
#define CANTP_TXTATYPEOFTXSDUCFG                                                                    STD_ON
#define CANTP_UPLAYERFCTSTXFCTPTRIDXOFTXSDUCFG                                                      STD_OFF
#define CANTP_UPLAYERFCTSTXFCTPTRUSEDOFTXSDUCFG                                                     STD_OFF
#define CANTP_TXSDUSNV2HDL                                                                          [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_INVALIDHNDOFTXSDUSNV2HDL                                                              STD_OFF
#define CANTP_TXNSDUHDLIDXOFTXSDUSNV2HDL                                                            STD_ON
#define CANTP_TXNSDUHDLPARTITIONIDXOFTXSDUSNV2HDL                                                   STD_ON
#define CANTP_TXNSDUHDLUSEDOFTXSDUSNV2HDL                                                           STD_ON
#define CANTP_TXSEMAPHORES                                                                          [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TXSTATE                                                                               [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_UPLAYERFCTSRXFCTPTR                                                                   STD_OFF
#define CANTP_UPLAYERFCTSTXFCTPTR                                                                   STD_OFF
#define CANTP_PCCONFIG                                                                              STD_ON
#define CANTP_FINALMAGICNUMBEROFPCCONFIG                                                            STD_OFF
#define CANTP_INITDATAHASHCODEOFPCCONFIG                                                            STD_OFF
#define CANTP_PCPARTITIONCONFIGOFPCCONFIG                                                           STD_ON
#define CANTP_PARTITIONIDENTIFIERSOFPCCONFIG                                                        STD_ON
#define CANTP_SIZEOFPARTITIONIDENTIFIERSOFPCCONFIG                                                  STD_ON
#define CANTP_PCPARTITIONCONFIG                                                                     STD_ON
#define CANTP_CALCBSOFPCPARTITIONCONFIG                                                             STD_ON
#define CANTP_COMPATIBILITYVERSIONOFPCPARTITIONCONFIG                                               STD_ON
#define CANTP_RXPDU2RXSDUINDOFPCPARTITIONCONFIG                                                     STD_ON
#define CANTP_RXPDU2TXSDUINDOFPCPARTITIONCONFIG                                                     [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_RXPDUMAPOFPCPARTITIONCONFIG                                                           STD_ON
#define CANTP_RXSDUCFGOFPCPARTITIONCONFIG                                                           STD_ON
#define CANTP_RXSDUSNV2HDLOFPCPARTITIONCONFIG                                                       STD_ON
#define CANTP_RXSTATEOFPCPARTITIONCONFIG                                                            STD_ON
#define CANTP_SIZEOFCALCBSOFPCPARTITIONCONFIG                                                       STD_ON
#define CANTP_SIZEOFDYNFCPARAMETERSOFPCPARTITIONCONFIG                                              STD_OFF
#define CANTP_SIZEOFLOLAYERFCTSOFPCPARTITIONCONFIG                                                  STD_OFF
#define CANTP_SIZEOFMETADATAGETTERADDRESS_EXTENSION_8OFPCPARTITIONCONFIG                            STD_OFF
#define CANTP_SIZEOFMETADATAGETTERCAN_ID_32OFPCPARTITIONCONFIG                                      STD_OFF
#define CANTP_SIZEOFMETADATAGETTERSOURCE_ADDRESS_16OFPCPARTITIONCONFIG                              STD_OFF
#define CANTP_SIZEOFMETADATAGETTERTARGET_ADDRESS_16OFPCPARTITIONCONFIG                              STD_OFF
#define CANTP_SIZEOFMETADATASETTERADDRESS_EXTENSION_8OFPCPARTITIONCONFIG                            STD_OFF
#define CANTP_SIZEOFMETADATASETTERCAN_ID_32OFPCPARTITIONCONFIG                                      STD_OFF
#define CANTP_SIZEOFMETADATASETTERSOURCE_ADDRESS_16OFPCPARTITIONCONFIG                              STD_OFF
#define CANTP_SIZEOFMETADATASETTERTARGET_ADDRESS_16OFPCPARTITIONCONFIG                              STD_OFF
#define CANTP_SIZEOFPARTITIONLOOKUPTABLEOFPCPARTITIONCONFIG                                         STD_OFF
#define CANTP_SIZEOFRXCHANNELMAPOFPCPARTITIONCONFIG                                                 STD_OFF
#define CANTP_SIZEOFRXPDU2RXSDUINDOFPCPARTITIONCONFIG                                               STD_ON
#define CANTP_SIZEOFRXPDU2TXSDUINDOFPCPARTITIONCONFIG                                               [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFRXPDUMAPOFPCPARTITIONCONFIG                                                     STD_ON
#define CANTP_SIZEOFRXSDUCFGOFPCPARTITIONCONFIG                                                     STD_ON
#define CANTP_SIZEOFRXSDUSNV2HDLOFPCPARTITIONCONFIG                                                 STD_ON
#define CANTP_SIZEOFRXSTATEOFPCPARTITIONCONFIG                                                      STD_ON
#define CANTP_SIZEOFTXCHANNELMAPOFPCPARTITIONCONFIG                                                 STD_OFF
#define CANTP_SIZEOFTXPDU2RXSDUINDOFPCPARTITIONCONFIG                                               [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXPDU2TXSDUINDOFPCPARTITIONCONFIG                                               [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXPDUMAPOFPCPARTITIONCONFIG                                                     [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXQUEUEOFPCPARTITIONCONFIG                                                      STD_OFF
#define CANTP_SIZEOFTXSDUCFGOFPCPARTITIONCONFIG                                                     [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXSDUSNV2HDLOFPCPARTITIONCONFIG                                                 [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXSEMAPHORESOFPCPARTITIONCONFIG                                                 [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFTXSTATEOFPCPARTITIONCONFIG                                                      [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_SIZEOFUPLAYERFCTSRXFCTPTROFPCPARTITIONCONFIG                                          STD_OFF
#define CANTP_SIZEOFUPLAYERFCTSTXFCTPTROFPCPARTITIONCONFIG                                          STD_OFF
#define CANTP_TXPDU2RXSDUINDOFPCPARTITIONCONFIG                                                     [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TXPDU2TXSDUINDOFPCPARTITIONCONFIG                                                     [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TXPDUMAPOFPCPARTITIONCONFIG                                                           [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TXSDUCFGOFPCPARTITIONCONFIG                                                           [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TXSDUSNV2HDLOFPCPARTITIONCONFIG                                                       [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TXSEMAPHORESOFPCPARTITIONCONFIG                                                       [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_TXSTATEOFPCPARTITIONCONFIG                                                            [!IF "$numTxSdus > 0"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

/* Min / Max / NoValue Macros */
#define CANTP_MIN_CALCBS                                                                            0u
#define CANTP_MAX_CALCBS                                                                            255u
#define CANTP_NO_RXPDU2RXSDUENDIDXOFRXPDUMAP                                                        255u
#define CANTP_NO_RXPDU2RXSDUPARTITIONIDXOFRXPDUMAP                                                  255u
#define CANTP_NO_RXPDU2RXSDUSTARTIDXOFRXPDUMAP                                                      255u
#define CANTP_NO_RXPDU2TXSDUENDIDXOFRXPDUMAP                                                        255u
#define CANTP_NO_RXPDU2TXSDUPARTITIONIDXOFRXPDUMAP                                                  255u
#define CANTP_NO_RXPDU2TXSDUSTARTIDXOFRXPDUMAP                                                      255u
#define CANTP_NO_RXPDUMAPIDXOFRXSDUCFG                                                              255u
#define CANTP_NO_TXPDUMAPIDXOFRXSDUCFG                                                              255u
#define CANTP_NO_TXSDUCFGIDXOFRXSDUCFG                                                              255u
#define CANTP_NO_RXNSDUHDLIDXOFRXSDUSNV2HDL                                                         255u
#define CANTP_NO_RXNSDUHDLPARTITIONIDXOFRXSDUSNV2HDL                                                255u
#define CANTP_NO_TXPDU2RXSDUENDIDXOFTXPDUMAP                                                        255u
#define CANTP_NO_TXPDU2RXSDUPARTITIONIDXOFTXPDUMAP                                                  255u
#define CANTP_NO_TXPDU2RXSDUSTARTIDXOFTXPDUMAP                                                      255u
#define CANTP_NO_TXPDU2TXSDUENDIDXOFTXPDUMAP                                                        255u
#define CANTP_NO_TXPDU2TXSDUPARTITIONIDXOFTXPDUMAP                                                  255u
#define CANTP_NO_TXPDU2TXSDUSTARTIDXOFTXPDUMAP                                                      255u
#define CANTP_NO_RXPDUMAPIDXOFTXSDUCFG                                                              255u
#define CANTP_NO_RXSDUCFGIDXOFTXSDUCFG                                                              255u
#define CANTP_NO_TXPDUMAPIDXOFTXSDUCFG                                                              255u
#define CANTP_NO_TXNSDUHDLIDXOFTXSDUSNV2HDL                                                         255u
#define CANTP_NO_TXNSDUHDLPARTITIONIDXOFTXSDUSNV2HDL                                                255u

/* Exists & Enum Value Macros */
#define CANTP_EXISTS_NORMAL_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                   STD_ON
#define CANTP_EXISTS_EXTENDED_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                 STD_OFF
#define CANTP_EXISTS_MIXED11_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                  STD_OFF
#define CANTP_EXISTS_NORMALFIXED_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                              STD_OFF
#define CANTP_EXISTS_MIXED29_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                  STD_OFF
#define CANTP_EXISTS_CUSTOM_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                   STD_OFF
#define CANTP_EXISTS_CAN20_CANTYPEOFRXSDUCFG                                                        [!IF "$supportCanFd = 'false'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_CANFD_CANTYPEOFRXSDUCFG                                                        [!IF "$supportCanFd = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_HALF_DUPLEX_CHANNELMODEOFRXSDUCFG                                              STD_OFF
#define CANTP_EXISTS_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG                                              STD_ON
#define CANTP_EXISTS_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                                 STD_ON
#define CANTP_EXISTS_EXTENDED_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                               STD_OFF
#define CANTP_EXISTS_MIXED11_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                                STD_OFF
#define CANTP_EXISTS_NORMALFIXED_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                            STD_OFF
#define CANTP_EXISTS_MIXED29_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                                STD_OFF
#define CANTP_EXISTS_CUSTOM_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                                 STD_OFF
#define CANTP_EXISTS_PHYSICAL_RXTATYPEOFRXSDUCFG                                                    [!IF "$hasPhysRx = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_FUNCTIONAL_RXTATYPEOFRXSDUCFG                                                  [!IF "$hasFuncRx = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_CANFD_PHYSICAL_RXTATYPEOFRXSDUCFG                                              [!IF "$hasPhysRx = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_CANFD_FUNCTIONAL_RXTATYPEOFRXSDUCFG                                            [!IF "$hasFuncRx = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_CAN20_CANTYPEOFTXSDUCFG                                                        [!IF "$supportCanFd = 'false'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_CANFD_CANTYPEOFTXSDUCFG                                                        [!IF "$supportCanFd = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_HALF_DUPLEX_CHANNELMODEOFTXSDUCFG                                              STD_OFF
#define CANTP_EXISTS_FULL_DUPLEX_CHANNELMODEOFTXSDUCFG                                              STD_ON
#define CANTP_EXISTS_NORMAL_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                                 STD_ON
#define CANTP_EXISTS_EXTENDED_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                               STD_OFF
#define CANTP_EXISTS_MIXED11_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                                STD_OFF
#define CANTP_EXISTS_NORMALFIXED_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                            STD_OFF
#define CANTP_EXISTS_MIXED29_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                                STD_OFF
#define CANTP_EXISTS_CUSTOM_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                                 STD_OFF
#define CANTP_EXISTS_PHYSICAL_TXTATYPEOFTXSDUCFG                                                    [!IF "$hasPhysTx = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_FUNCTIONAL_TXTATYPEOFTXSDUCFG                                                  [!IF "$hasFuncTx = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_CANFD_PHYSICAL_TXTATYPEOFTXSDUCFG                                              [!IF "$hasPhysTx = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]
#define CANTP_EXISTS_CANFD_FUNCTIONAL_TXTATYPEOFTXSDUCFG                                            [!IF "$hasFuncTx = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!]

#define CANTP_NORMAL_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP                                          0x00u
#define CANTP_CAN20_CANTYPEOFRXSDUCFG                                                               0x00u
#define CANTP_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG                                                     0x01u
#define CANTP_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG                                        0x00u
#define CANTP_PHYSICAL_RXTATYPEOFRXSDUCFG                                                           0x00u
#define CANTP_FUNCTIONAL_RXTATYPEOFRXSDUCFG                                                         0x01u
#define CANTP_CANFD_PHYSICAL_RXTATYPEOFRXSDUCFG                                                     0x00u
#define CANTP_CANFD_FUNCTIONAL_RXTATYPEOFRXSDUCFG                                                   0x01u
#define CANTP_CAN20_CANTYPEOFTXSDUCFG                                                               0x00u
#define CANTP_FULL_DUPLEX_CHANNELMODEOFTXSDUCFG                                                     0x01u
#define CANTP_NORMAL_ADDRESSING_TXADDRESSINGFORMATOFTXSDUCFG                                        0x00u
#define CANTP_PHYSICAL_TXTATYPEOFTXSDUCFG                                                           0x00u
#define CANTP_CANFD_PHYSICAL_TXTATYPEOFTXSDUCFG                                                     0x00u

/* ISDEF Macros */
#define CANTP_ISDEF_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS                                      STD_OFF
#define CANTP_ISDEF_PARTITIONSNVOFPARTITIONIDENTIFIERS                                              STD_OFF
#define CANTP_ISDEF_RXPDU2RXSDUIND                                                                  STD_OFF
#define CANTP_ISDEF_RXPDU2TXSDUIND                                                                  STD_ON
#define CANTP_ISDEF_ADDRESSINGFORMATOFRXPDUMAP                                                      STD_ON
#define CANTP_ISDEF_GENERICCONNECTIONOFRXPDUMAP                                                     STD_ON
#define CANTP_ISDEF_PDUMETADATAOFRXPDUMAP                                                           STD_ON
#define CANTP_ISDEF_RXPDU2RXSDUENDIDXOFRXPDUMAP                                                     STD_OFF
#define CANTP_ISDEF_RXPDU2RXSDUPARTITIONIDXOFRXPDUMAP                                               STD_ON
#define CANTP_ISDEF_RXPDU2RXSDUSTARTIDXOFRXPDUMAP                                                   STD_OFF
#define CANTP_ISDEF_RXPDU2RXSDUUSEDOFRXPDUMAP                                                       STD_ON
#define CANTP_ISDEF_RXPDU2TXSDUENDIDXOFRXPDUMAP                                                     STD_OFF
#define CANTP_ISDEF_RXPDU2TXSDUPARTITIONIDXOFRXPDUMAP                                               STD_OFF
#define CANTP_ISDEF_RXPDU2TXSDUSTARTIDXOFRXPDUMAP                                                   STD_OFF
#define CANTP_ISDEF_RXPDU2TXSDUUSEDOFRXPDUMAP                                                       STD_OFF
#define CANTP_ISDEF_BLOCKSIZEOFRXSDUCFG                                                             STD_OFF
#define CANTP_ISDEF_CANTYPEOFRXSDUCFG                                                               STD_ON
#define CANTP_ISDEF_CHANNELMODEOFRXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_GENERICCONNECTIONOFRXSDUCFG                                                     STD_ON
#define CANTP_ISDEF_LOLAYERTXFCPDUIDOFRXSDUCFG                                                      STD_OFF
#define CANTP_ISDEF_NAROFRXSDUCFG                                                                   STD_ON
#define CANTP_ISDEF_NBROFRXSDUCFG                                                                   STD_ON
#define CANTP_ISDEF_NCROFRXSDUCFG                                                                   STD_ON
#define CANTP_ISDEF_PDURRXSDUIDOFRXSDUCFG                                                           STD_OFF
#define CANTP_ISDEF_RXADDRESSOFRXSDUCFG                                                             STD_ON
#define CANTP_ISDEF_RXADDRESSINGFORMATOFRXSDUCFG                                                    STD_ON
#define CANTP_ISDEF_RXMAXPAYLOADLENGTHOFRXSDUCFG                                                    STD_ON
#define CANTP_ISDEF_RXPADDINGACTIVATIONOFRXSDUCFG                                                   STD_ON
#define CANTP_ISDEF_RXPDUIDOFRXSDUCFG                                                               STD_OFF
#define CANTP_ISDEF_RXPDUMAPIDXOFRXSDUCFG                                                           STD_OFF
#define CANTP_ISDEF_RXPDUMAPUSEDOFRXSDUCFG                                                          STD_ON
#define CANTP_ISDEF_RXTATYPEOFRXSDUCFG                                                              STD_OFF
#define CANTP_ISDEF_RXWFTMAXOFRXSDUCFG                                                              STD_OFF
#define CANTP_ISDEF_STMINOFRXSDUCFG                                                                 STD_ON
#define CANTP_ISDEF_SDUMETADATALENGTHOFRXSDUCFG                                                     STD_ON
#define CANTP_ISDEF_TXFCADDRESSOFRXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_TXFCPDUCONFIRMATIONPDUIDOFRXSDUCFG                                              STD_OFF
#define CANTP_ISDEF_TXPDUMAPIDXOFRXSDUCFG                                                           STD_OFF
#define CANTP_ISDEF_TXPDUMAPUSEDOFRXSDUCFG                                                          STD_OFF
#define CANTP_ISDEF_TXSDUCFGIDXOFRXSDUCFG                                                           STD_OFF
#define CANTP_ISDEF_TXSDUCFGUSEDOFRXSDUCFG                                                          STD_OFF
#define CANTP_ISDEF_RXNSDUHDLIDXOFRXSDUSNV2HDL                                                      STD_OFF
#define CANTP_ISDEF_RXNSDUHDLPARTITIONIDXOFRXSDUSNV2HDL                                             STD_ON
#define CANTP_ISDEF_RXNSDUHDLUSEDOFRXSDUSNV2HDL                                                     STD_ON
#define CANTP_ISDEF_TXPDU2RXSDUIND                                                                  STD_ON
#define CANTP_ISDEF_TXPDU2TXSDUIND                                                                  STD_ON
#define CANTP_ISDEF_CANIDOFTXPDUMAP                                                                 STD_ON
#define CANTP_ISDEF_MASKOFTXPDUMAP                                                                  STD_ON
#define CANTP_ISDEF_TXPDU2RXSDUENDIDXOFTXPDUMAP                                                     STD_ON
#define CANTP_ISDEF_TXPDU2RXSDUPARTITIONIDXOFTXPDUMAP                                               STD_ON
#define CANTP_ISDEF_TXPDU2RXSDUSTARTIDXOFTXPDUMAP                                                   STD_ON
#define CANTP_ISDEF_TXPDU2RXSDUUSEDOFTXPDUMAP                                                       STD_ON
#define CANTP_ISDEF_TXPDU2TXSDUENDIDXOFTXPDUMAP                                                     STD_ON
#define CANTP_ISDEF_TXPDU2TXSDUPARTITIONIDXOFTXPDUMAP                                               STD_ON
#define CANTP_ISDEF_TXPDU2TXSDUSTARTIDXOFTXPDUMAP                                                   STD_ON
#define CANTP_ISDEF_TXPDU2TXSDUUSEDOFTXPDUMAP                                                       STD_ON
#define CANTP_ISDEF_CANTYPEOFTXSDUCFG                                                               STD_ON
#define CANTP_ISDEF_CHANNELMODEOFTXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_LOLAYERTXPDUIDOFTXSDUCFG                                                        STD_ON
#define CANTP_ISDEF_NASOFTXSDUCFG                                                                   STD_ON
#define CANTP_ISDEF_NBSOFTXSDUCFG                                                                   STD_ON
#define CANTP_ISDEF_NCSOFTXSDUCFG                                                                   STD_ON
#define CANTP_ISDEF_PDURTXSDUIDOFTXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_RXFCADDRESSOFTXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_RXFCPDUIDOFTXSDUCFG                                                             STD_ON
#define CANTP_ISDEF_RXPDUMAPIDXOFTXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_RXPDUMAPUSEDOFTXSDUCFG                                                          STD_ON
#define CANTP_ISDEF_RXSDUCFGIDXOFTXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_RXSDUCFGUSEDOFTXSDUCFG                                                          STD_ON
#define CANTP_ISDEF_SDUMETADATALENGTHOFTXSDUCFG                                                     STD_ON
#define CANTP_ISDEF_TRANSMITCANCELLATIONOFTXSDUCFG                                                  STD_ON
#define CANTP_ISDEF_TXADDRESSOFTXSDUCFG                                                             STD_ON
#define CANTP_ISDEF_TXADDRESSINGFORMATOFTXSDUCFG                                                    STD_ON
#define CANTP_ISDEF_TXMAXPAYLOADLENGTHOFTXSDUCFG                                                    STD_ON
#define CANTP_ISDEF_TXPADDINGACTIVATIONOFTXSDUCFG                                                   STD_ON
#define CANTP_ISDEF_TXPDUCONFIRMATIONPDUIDOFTXSDUCFG                                                STD_ON
#define CANTP_ISDEF_TXPDUMAPIDXOFTXSDUCFG                                                           STD_ON
#define CANTP_ISDEF_TXPDUMAPUSEDOFTXSDUCFG                                                          STD_ON
#define CANTP_ISDEF_TXTATYPEOFTXSDUCFG                                                              STD_ON
#define CANTP_ISDEF_TXNSDUHDLIDXOFTXSDUSNV2HDL                                                      STD_ON
#define CANTP_ISDEF_TXNSDUHDLPARTITIONIDXOFTXSDUSNV2HDL                                             STD_ON
#define CANTP_ISDEF_TXNSDUHDLUSEDOFTXSDUSNV2HDL                                                     STD_ON
#define CANTP_ISDEF_PCPARTITIONCONFIGOFPCCONFIG                                                     STD_ON
#define CANTP_ISDEF_PARTITIONIDENTIFIERSOFPCCONFIG                                                  STD_ON
#define CANTP_ISDEF_CALCBSOFPCPARTITIONCONFIG                                                       STD_ON
#define CANTP_ISDEF_RXPDU2RXSDUINDOFPCPARTITIONCONFIG                                               STD_ON
#define CANTP_ISDEF_RXPDU2TXSDUINDOFPCPARTITIONCONFIG                                               STD_ON
#define CANTP_ISDEF_RXPDUMAPOFPCPARTITIONCONFIG                                                     STD_ON
#define CANTP_ISDEF_RXSDUCFGOFPCPARTITIONCONFIG                                                     STD_ON
#define CANTP_ISDEF_RXSDUSNV2HDLOFPCPARTITIONCONFIG                                                 STD_ON
#define CANTP_ISDEF_RXSTATEOFPCPARTITIONCONFIG                                                      STD_ON
#define CANTP_ISDEF_TXPDU2RXSDUINDOFPCPARTITIONCONFIG                                               STD_ON
#define CANTP_ISDEF_TXPDU2TXSDUINDOFPCPARTITIONCONFIG                                               STD_ON
#define CANTP_ISDEF_TXPDUMAPOFPCPARTITIONCONFIG                                                     STD_ON
#define CANTP_ISDEF_TXSDUCFGOFPCPARTITIONCONFIG                                                     STD_ON
#define CANTP_ISDEF_TXSDUSNV2HDLOFPCPARTITIONCONFIG                                                 STD_ON
#define CANTP_ISDEF_TXSEMAPHORESOFPCPARTITIONCONFIG                                                 STD_ON
#define CANTP_ISDEF_TXSTATEOFPCPARTITIONCONFIG                                                      STD_ON

/* EQ2 Constant Macros */
#define CANTP_EQ2_PCPARTITIONCONFIGIDXOFPARTITIONIDENTIFIERS
#define CANTP_EQ2_PARTITIONSNVOFPARTITIONIDENTIFIERS
#define CANTP_EQ2_RXPDU2RXSDUIND
#define CANTP_EQ2_RXPDU2TXSDUIND                                                                    0u
#define CANTP_EQ2_ADDRESSINGFORMATOFRXPDUMAP                                                        CANTP_NORMAL_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP
#define CANTP_EQ2_GENERICCONNECTIONOFRXPDUMAP                                                       FALSE
#define CANTP_EQ2_PDUMETADATAOFRXPDUMAP                                                             FALSE
#define CANTP_EQ2_RXPDU2RXSDUENDIDXOFRXPDUMAP
#define CANTP_EQ2_RXPDU2RXSDUPARTITIONIDXOFRXPDUMAP                                                 0u
#define CANTP_EQ2_RXPDU2RXSDUSTARTIDXOFRXPDUMAP
#define CANTP_EQ2_RXPDU2RXSDUUSEDOFRXPDUMAP                                                         TRUE
#define CANTP_EQ2_RXPDU2TXSDUENDIDXOFRXPDUMAP
#define CANTP_EQ2_RXPDU2TXSDUPARTITIONIDXOFRXPDUMAP
#define CANTP_EQ2_RXPDU2TXSDUSTARTIDXOFRXPDUMAP
#define CANTP_EQ2_RXPDU2TXSDUUSEDOFRXPDUMAP
#define CANTP_EQ2_BLOCKSIZEOFRXSDUCFG
#define CANTP_EQ2_CANTYPEOFRXSDUCFG                                                                 CANTP_CAN20_CANTYPEOFRXSDUCFG
#define CANTP_EQ2_CHANNELMODEOFRXSDUCFG                                                             CANTP_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG
#define CANTP_EQ2_GENERICCONNECTIONOFRXSDUCFG                                                       FALSE
#define CANTP_EQ2_LOLAYERTXFCPDUIDOFRXSDUCFG
#define CANTP_EQ2_NAROFRXSDUCFG                                                                     [!"num:i($firstNarTick)"!]u
#define CANTP_EQ2_NBROFRXSDUCFG                                                                     [!"num:i($firstNbrTick)"!]u
#define CANTP_EQ2_NCROFRXSDUCFG                                                                     [!"num:i($firstNcrTick)"!]u
#define CANTP_EQ2_PDURRXSDUIDOFRXSDUCFG
#define CANTP_EQ2_RXADDRESSOFRXSDUCFG                                                               255u
#define CANTP_EQ2_RXADDRESSINGFORMATOFRXSDUCFG                                                      CANTP_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG
#define CANTP_EQ2_RXMAXPAYLOADLENGTHOFRXSDUCFG                                                      [!"num:i($maxPayloadLen)"!]u
#define CANTP_EQ2_RXPADDINGACTIVATIONOFRXSDUCFG                                                     TRUE
#define CANTP_EQ2_RXPDUIDOFRXSDUCFG
#define CANTP_EQ2_RXPDUMAPIDXOFRXSDUCFG
#define CANTP_EQ2_RXPDUMAPUSEDOFRXSDUCFG                                                            TRUE
#define CANTP_EQ2_RXTATYPEOFRXSDUCFG
#define CANTP_EQ2_RXWFTMAXOFRXSDUCFG
#define CANTP_EQ2_STMINOFRXSDUCFG                                                                   [!"num:i($firstStMinTick)"!]u
#define CANTP_EQ2_SDUMETADATALENGTHOFRXSDUCFG                                                       0u
#define CANTP_EQ2_TXFCADDRESSOFRXSDUCFG                                                             255u
#define CANTP_EQ2_TXFCPDUCONFIRMATIONPDUIDOFRXSDUCFG
#define CANTP_EQ2_TXPDUMAPIDXOFRXSDUCFG
#define CANTP_EQ2_TXPDUMAPUSEDOFRXSDUCFG
#define CANTP_EQ2_TXSDUCFGIDXOFRXSDUCFG
#define CANTP_EQ2_TXSDUCFGUSEDOFRXSDUCFG
#define CANTP_EQ2_RXNSDUHDLIDXOFRXSDUSNV2HDL
#define CANTP_EQ2_RXNSDUHDLPARTITIONIDXOFRXSDUSNV2HDL                                               0u
#define CANTP_EQ2_RXNSDUHDLUSEDOFRXSDUSNV2HDL                                                       TRUE
#define CANTP_EQ2_TXPDU2RXSDUIND                                                                    0u
#define CANTP_EQ2_TXPDU2TXSDUIND                                                                    0u
#define CANTP_EQ2_CANIDOFTXPDUMAP                                                                   [!"$firstTxCanIdHex"!]
#define CANTP_EQ2_MASKOFTXPDUMAP                                                                    0xFFFFFFFFu
#define CANTP_EQ2_TXPDU2RXSDUENDIDXOFTXPDUMAP                                                       [!"num:i($numTxSdus)"!]u
#define CANTP_EQ2_TXPDU2RXSDUPARTITIONIDXOFTXPDUMAP                                                 0u
#define CANTP_EQ2_TXPDU2RXSDUSTARTIDXOFTXPDUMAP                                                     0u
#define CANTP_EQ2_TXPDU2RXSDUUSEDOFTXPDUMAP                                                         TRUE
#define CANTP_EQ2_TXPDU2TXSDUENDIDXOFTXPDUMAP                                                       [!"num:i($numTxSdus)"!]u
#define CANTP_EQ2_TXPDU2TXSDUPARTITIONIDXOFTXPDUMAP                                                 0u
#define CANTP_EQ2_TXPDU2TXSDUSTARTIDXOFTXPDUMAP                                                     0u
#define CANTP_EQ2_TXPDU2TXSDUUSEDOFTXPDUMAP                                                         TRUE
#define CANTP_EQ2_CANTYPEOFTXSDUCFG                                                                 CANTP_CAN20_CANTYPEOFTXSDUCFG
#define CANTP_EQ2_CHANNELMODEOFTXSDUCFG                                                             CANTP_FULL_DUPLEX_CHANNELMODEOFTXSDUCFG
#define CANTP_EQ2_LOLAYERTXPDUIDOFTXSDUCFG                                                          [!"$firstLoLayerTxPduSym"!]
#define CANTP_EQ2_NASOFTXSDUCFG                                                                     [!"num:i($firstNasTick)"!]u
#define CANTP_EQ2_NBSOFTXSDUCFG                                                                     [!"num:i($firstNbsTick)"!]u
#define CANTP_EQ2_NCSOFTXSDUCFG                                                                     [!"num:i($firstNcsTick)"!]u
#define CANTP_EQ2_PDURTXSDUIDOFTXSDUCFG                                                             [!"$firstPduRTxSduSym"!]
#define CANTP_EQ2_RXFCADDRESSOFTXSDUCFG                                                             255u
#define CANTP_EQ2_RXFCPDUIDOFTXSDUCFG                                                               [!"$firstRxFcPduSym"!]
#define CANTP_EQ2_RXPDUMAPIDXOFTXSDUCFG                                                             0u
#define CANTP_EQ2_RXPDUMAPUSEDOFTXSDUCFG                                                            TRUE
#define CANTP_EQ2_RXSDUCFGIDXOFTXSDUCFG                                                             0u
#define CANTP_EQ2_RXSDUCFGUSEDOFTXSDUCFG                                                            TRUE
#define CANTP_EQ2_SDUMETADATALENGTHOFTXSDUCFG                                                       0u
#define CANTP_EQ2_TRANSMITCANCELLATIONOFTXSDUCFG                                                    [!"$firstTxCancel"!]
#define CANTP_EQ2_TXADDRESSOFTXSDUCFG                                                               255u
#define CANTP_EQ2_TXADDRESSINGFORMATOFTXSDUCFG                                                      [!"$firstTxAddrFmt"!]
#define CANTP_EQ2_TXMAXPAYLOADLENGTHOFTXSDUCFG                                                      [!"num:i($maxPayloadLen)"!]u
#define CANTP_EQ2_TXPADDINGACTIVATIONOFTXSDUCFG                                                     TRUE
#define CANTP_EQ2_TXPDUCONFIRMATIONPDUIDOFTXSDUCFG                                                  [!"$firstTxPduCfmSym"!]
#define CANTP_EQ2_TXPDUMAPIDXOFTXSDUCFG                                                             0u
#define CANTP_EQ2_TXPDUMAPUSEDOFTXSDUCFG                                                            TRUE
#define CANTP_EQ2_TXTATYPEOFTXSDUCFG                                                                [!"$firstTxTaType"!]
#define CANTP_EQ2_TXNSDUHDLIDXOFTXSDUSNV2HDL                                                        0u
#define CANTP_EQ2_TXNSDUHDLPARTITIONIDXOFTXSDUSNV2HDL                                               0u
#define CANTP_EQ2_TXNSDUHDLUSEDOFTXSDUSNV2HDL                                                       TRUE
#define CANTP_EQ2_PCPARTITIONCONFIGOFPCCONFIG                                                       CanTp_PCPartitionConfig
#define CANTP_EQ2_PARTITIONIDENTIFIERSOFPCCONFIG                                                    CanTp_PartitionIdentifiers
#define CANTP_EQ2_CALCBSOFPCPARTITIONCONFIG                                                         CanTp_CalcBS
#define CANTP_EQ2_RXPDU2RXSDUINDOFPCPARTITIONCONFIG                                                 CanTp_RxPdu2RxSduInd
#define CANTP_EQ2_RXPDU2TXSDUINDOFPCPARTITIONCONFIG                                                 CanTp_RxPdu2TxSduInd
#define CANTP_EQ2_RXPDUMAPOFPCPARTITIONCONFIG                                                       CanTp_RxPduMap
#define CANTP_EQ2_RXSDUCFGOFPCPARTITIONCONFIG                                                       CanTp_RxSduCfg
#define CANTP_EQ2_RXSDUSNV2HDLOFPCPARTITIONCONFIG                                                   CanTp_RxSduSnv2Hdl
#define CANTP_EQ2_RXSTATEOFPCPARTITIONCONFIG                                                        CanTp_RxState
#define CANTP_EQ2_TXPDU2RXSDUINDOFPCPARTITIONCONFIG                                                 CanTp_TxPdu2RxSduInd
#define CANTP_EQ2_TXPDU2TXSDUINDOFPCPARTITIONCONFIG                                                 CanTp_TxPdu2TxSduInd
#define CANTP_EQ2_TXPDUMAPOFPCPARTITIONCONFIG                                                       CanTp_TxPduMap
#define CANTP_EQ2_TXSDUCFGOFPCPARTITIONCONFIG                                                       CanTp_TxSduCfg
#define CANTP_EQ2_TXSDUSNV2HDLOFPCPARTITIONCONFIG                                                   CanTp_TxSduSnv2Hdl
#define CANTP_EQ2_TXSEMAPHORESOFPCPARTITIONCONFIG                                                   CanTp_TxSemaphores
#define CANTP_EQ2_TXSTATEOFPCPARTITIONCONFIG                                                        CanTp_TxState

#define CanTp_Config_Ptr                                                                            NULL_PTR
#define CanTp_Config                                                                                NULL_PTR
#define CANTP_CHECK_INIT_POINTER                                                                    STD_OFF
#define CANTP_FINAL_MAGIC_NUMBER                                                                    0x231Eu
#define CANTP_INDIVIDUAL_POSTBUILD                                                                  STD_OFF
#define CANTP_INIT_DATA                                                                             CANTP_CONST
#define CANTP_INIT_DATA_HASH_CODE                                                                   835452236
#define CANTP_USE_ECUM_BSW_ERROR_HOOK                                                               STD_OFF
#define CANTP_USE_INIT_POINTER                                                                      STD_OFF
#define CanTp_PartitionIndexOfCSLForCanTpSinglePartitionMemory                                      0u

/* CSL PCConfig / PCPartitionConfig Accessors */
#define CanTp_GetPartitionIdentifiersOfPCConfig()                                                   CanTp_PartitionIdentifiers
#define CanTp_GetSizeOfPartitionIdentifiersOfPCConfig()                                             1u
#define CanTp_GetCalcBSOfPCPartitionConfig(partitionIndex)                                          CanTp_CalcBS
#define CanTp_GetCompatibilityVersionOfPCPartitionConfig(partitionIndex)                            822854u
#define CanTp_GetRxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)                                  CanTp_RxPdu2RxSduInd
#define CanTp_GetRxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)                                  CanTp_RxPdu2TxSduInd
#define CanTp_GetRxPduMapOfPCPartitionConfig()                                                      CanTp_RxPduMap
#define CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)                                        CanTp_RxSduCfg
#define CanTp_GetRxSduSnv2HdlOfPCPartitionConfig()                                                  CanTp_RxSduSnv2Hdl
#define CanTp_GetRxStateOfPCPartitionConfig(partitionIndex)                                         CanTp_RxState
#define CanTp_GetSizeOfCalcBSOfPCPartitionConfig(partitionIndex)                                    [!"num:i($numRxSdus)"!]u
#define CanTp_GetSizeOfRxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)                            [!"num:i($numRxNPdus)"!]u
#define CanTp_GetSizeOfRxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)                            [!"num:i($numTxSdus)"!]u
#define CanTp_GetSizeOfRxPduMapOfPCPartitionConfig()                                                [!"num:i($numRxNPdus)"!]u
#define CanTp_GetSizeOfRxSduCfgOfPCPartitionConfig(partitionIndex)                                  [!"num:i($numRxSdus)"!]u
#define CanTp_GetSizeOfRxSduSnv2HdlOfPCPartitionConfig()                                            [!"num:i($numRxSdus)"!]u
#define CanTp_GetSizeOfRxStateOfPCPartitionConfig(partitionIndex)                                   [!"num:i($numRxSdus)"!]u
#define CanTp_GetSizeOfTxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)                            [!"num:i($numTxSdus)"!]u
#define CanTp_GetSizeOfTxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)                            [!"num:i($numTxSdus)"!]u
#define CanTp_GetSizeOfTxPduMapOfPCPartitionConfig()                                                [!"num:i($numTxPduMaps)"!]u
#define CanTp_GetSizeOfTxSduCfgOfPCPartitionConfig(partitionIndex)                                  [!"num:i($numTxSdus)"!]u
#define CanTp_GetSizeOfTxSduSnv2HdlOfPCPartitionConfig()                                            [!"num:i($numTxSdus)"!]u
#define CanTp_GetSizeOfTxSemaphoresOfPCPartitionConfig(partitionIndex)                              [!"num:i($numTxSdus)"!]u
#define CanTp_GetSizeOfTxStateOfPCPartitionConfig(partitionIndex)                                   [!"num:i($numTxSdus)"!]u
#define CanTp_GetTxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)                                  CanTp_TxPdu2RxSduInd
#define CanTp_GetTxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)                                  CanTp_TxPdu2TxSduInd
#define CanTp_GetTxPduMapOfPCPartitionConfig()                                                      CanTp_TxPduMap
#define CanTp_GetTxSduCfgOfPCPartitionConfig(partitionIndex)                                        CanTp_TxSduCfg
#define CanTp_GetTxSduSnv2HdlOfPCPartitionConfig()                                                  CanTp_TxSduSnv2Hdl
#define CanTp_GetTxSemaphoresOfPCPartitionConfig(partitionIndex)                                    CanTp_TxSemaphores
#define CanTp_GetTxStateOfPCPartitionConfig(partitionIndex)                                         CanTp_TxState

/* CSL Data Getters */
#define CanTp_GetCalcBS(Index, partitionIndex)                                                      (CanTp_GetCalcBSOfPCPartitionConfig(partitionIndex)[(Index)])
#define CanTp_GetPCPartitionConfigIdxOfPartitionIdentifiers(Index)                                  (CanTp_GetPartitionIdentifiersOfPCConfig()[(Index)].PCPartitionConfigIdxOfPartitionIdentifiers)
#define CanTp_GetPartitionSNVOfPartitionIdentifiers(Index)                                          (CanTp_GetPartitionIdentifiersOfPCConfig()[(Index)].PartitionSNVOfPartitionIdentifiers)
#define CanTp_GetRxPdu2RxSduInd(Index, partitionIndex)                                              (CanTp_GetRxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)[(Index)])
#define CanTp_GetRxPdu2RxSduEndIdxOfRxPduMap(Index)                                                 (CanTp_GetRxPduMapOfPCPartitionConfig()[(Index)].RxPdu2RxSduEndIdxOfRxPduMap)
#define CanTp_GetRxPdu2RxSduStartIdxOfRxPduMap(Index)                                               (CanTp_GetRxPduMapOfPCPartitionConfig()[(Index)].RxPdu2RxSduStartIdxOfRxPduMap)
#define CanTp_GetRxPdu2TxSduEndIdxOfRxPduMap(Index)                                                 (CanTp_GetRxPduMapOfPCPartitionConfig()[(Index)].RxPdu2TxSduEndIdxOfRxPduMap)
#define CanTp_GetRxPdu2TxSduPartitionIdxOfRxPduMap(Index)                                           (CanTp_GetRxPduMapOfPCPartitionConfig()[(Index)].RxPdu2TxSduPartitionIdxOfRxPduMap)
#define CanTp_GetRxPdu2TxSduStartIdxOfRxPduMap(Index)                                               (CanTp_GetRxPduMapOfPCPartitionConfig()[(Index)].RxPdu2TxSduStartIdxOfRxPduMap)
#define CanTp_GetBlockSizeOfRxSduCfg(Index, partitionIndex)                                         (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].BlockSizeOfRxSduCfg)
#define CanTp_GetLoLayerTxFcPduIdOfRxSduCfg(Index, partitionIndex)                                  (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].LoLayerTxFcPduIdOfRxSduCfg)
#define CanTp_GetPduRRxSduIdOfRxSduCfg(Index, partitionIndex)                                       (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].PduRRxSduIdOfRxSduCfg)
#define CanTp_GetRxPduIdOfRxSduCfg(Index, partitionIndex)                                           (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].RxPduIdOfRxSduCfg)
#define CanTp_GetRxPduMapIdxOfRxSduCfg(Index, partitionIndex)                                       (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].RxPduMapIdxOfRxSduCfg)
#define CanTp_GetRxTaTypeOfRxSduCfg(Index, partitionIndex)                                          (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].RxTaTypeOfRxSduCfg)
#define CanTp_GetRxWftMaxOfRxSduCfg(Index, partitionIndex)                                          (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].RxWftMaxOfRxSduCfg)
#define CanTp_GetTxFcPduConfirmationPduIdOfRxSduCfg(Index, partitionIndex)                          (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].TxFcPduConfirmationPduIdOfRxSduCfg)
#define CanTp_GetTxPduMapIdxOfRxSduCfg(Index, partitionIndex)                                       (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].TxPduMapIdxOfRxSduCfg)
#define CanTp_GetTxSduCfgIdxOfRxSduCfg(Index, partitionIndex)                                       (CanTp_GetRxSduCfgOfPCPartitionConfig(partitionIndex)[(Index)].TxSduCfgIdxOfRxSduCfg)
#define CanTp_GetRxNSduHdlIdxOfRxSduSnv2Hdl(Index)                                                  (CanTp_GetRxSduSnv2HdlOfPCPartitionConfig()[(Index)].RxNSduHdlIdxOfRxSduSnv2Hdl)
#define CanTp_GetRxState(Index, partitionIndex)                                                     (CanTp_GetRxStateOfPCPartitionConfig(partitionIndex)[(Index)])
#define CanTp_GetTxSemaphores(Index, partitionIndex)                                                (CanTp_GetTxSemaphoresOfPCPartitionConfig(partitionIndex)[(Index)])
#define CanTp_GetTxState(Index, partitionIndex)                                                     (CanTp_GetTxStateOfPCPartitionConfig(partitionIndex)[(Index)])
#define CanTp_GetCompatibilityVersion(partitionIndex)                                               CanTp_GetCompatibilityVersionOfPCPartitionConfig(partitionIndex)
#define CanTp_GetRxPdu2TxSduInd(Index, partitionIndex)                                              0u
#define CanTp_GetAddressingFormatOfRxPduMap(Index)                                                  CANTP_NORMAL_ADDRESSING_ADDRESSINGFORMATOFRXPDUMAP
#define CanTp_IsGenericConnectionOfRxPduMap(Index)                                                  (((FALSE)) != FALSE)
#define CanTp_IsPduMetadataOfRxPduMap(Index)                                                        (((FALSE)) != FALSE)
#define CanTp_GetRxPdu2RxSduPartitionIdxOfRxPduMap(Index)                                           0u
#define CanTp_IsRxPdu2RxSduUsedOfRxPduMap(Index)                                                    (((TRUE)) != FALSE)
#define CanTp_IsRxPdu2TxSduUsedOfRxPduMap(Index)                                                    (((boolean)(CanTp_GetRxPdu2TxSduStartIdxOfRxPduMap(Index) != CANTP_NO_RXPDU2TXSDUSTARTIDXOFRXPDUMAP)) != FALSE)
#define CanTp_GetCanTypeOfRxSduCfg(Index, partitionIndex)                                           CANTP_CAN20_CANTYPEOFRXSDUCFG
#define CanTp_GetChannelModeOfRxSduCfg(Index, partitionIndex)                                       CANTP_FULL_DUPLEX_CHANNELMODEOFRXSDUCFG
#define CanTp_IsGenericConnectionOfRxSduCfg(Index, partitionIndex)                                  (((FALSE)) != FALSE)
#define CanTp_GetNArOfRxSduCfg(Index, partitionIndex)                                               CANTP_EQ2_NAROFRXSDUCFG
#define CanTp_GetNBrOfRxSduCfg(Index, partitionIndex)                                               CANTP_EQ2_NBROFRXSDUCFG
#define CanTp_GetNCrOfRxSduCfg(Index, partitionIndex)                                               CANTP_EQ2_NCROFRXSDUCFG
#define CanTp_GetRxAddressOfRxSduCfg(Index, partitionIndex)                                         255u
#define CanTp_GetRxAddressingFormatOfRxSduCfg(Index, partitionIndex)                                CANTP_NORMAL_ADDRESSING_RXADDRESSINGFORMATOFRXSDUCFG
#define CanTp_GetRxMaxPayloadLengthOfRxSduCfg(Index, partitionIndex)                                CANTP_EQ2_RXMAXPAYLOADLENGTHOFRXSDUCFG
#define CanTp_IsRxPaddingActivationOfRxSduCfg(Index, partitionIndex)                                (((TRUE)) != FALSE)
#define CanTp_IsRxPduMapUsedOfRxSduCfg(Index, partitionIndex)                                       (((TRUE)) != FALSE)
#define CanTp_GetSTminOfRxSduCfg(Index, partitionIndex)                                             CANTP_EQ2_STMINOFRXSDUCFG
#define CanTp_GetSduMetadataLengthOfRxSduCfg(Index, partitionIndex)                                 0u
#define CanTp_GetTxFcAddressOfRxSduCfg(Index, partitionIndex)                                       255u
#define CanTp_IsTxPduMapUsedOfRxSduCfg(Index, partitionIndex)                                       (((boolean)(CanTp_GetTxPduMapIdxOfRxSduCfg(((Index)), (partitionIndex)) != CANTP_NO_TXPDUMAPIDXOFRXSDUCFG)) != FALSE)
#define CanTp_IsTxSduCfgUsedOfRxSduCfg(Index, partitionIndex)                                       (((boolean)(CanTp_GetTxSduCfgIdxOfRxSduCfg(((Index)), (partitionIndex)) != CANTP_NO_TXSDUCFGIDXOFRXSDUCFG)) != FALSE)
#define CanTp_GetRxNSduHdlPartitionIdxOfRxSduSnv2Hdl(Index)                                         0u
#define CanTp_IsRxNSduHdlUsedOfRxSduSnv2Hdl(Index)                                                  (((TRUE)) != FALSE)
#define CanTp_GetSizeOfCalcBS(partitionIndex)                                                       CanTp_GetSizeOfCalcBSOfPCPartitionConfig(partitionIndex)
#define CanTp_GetSizeOfPartitionIdentifiers()                                                       CanTp_GetSizeOfPartitionIdentifiersOfPCConfig()
#define CanTp_GetSizeOfRxPdu2RxSduInd(partitionIndex)                                               CanTp_GetSizeOfRxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)
#define CanTp_GetSizeOfRxPdu2TxSduInd(partitionIndex)                                               CanTp_GetSizeOfRxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)
#define CanTp_GetSizeOfRxPduMap()                                                                   CanTp_GetSizeOfRxPduMapOfPCPartitionConfig()
#define CanTp_GetSizeOfRxSduCfg(partitionIndex)                                                     CanTp_GetSizeOfRxSduCfgOfPCPartitionConfig(partitionIndex)
#define CanTp_GetSizeOfRxSduSnv2Hdl()                                                               CanTp_GetSizeOfRxSduSnv2HdlOfPCPartitionConfig()
#define CanTp_GetSizeOfRxState(partitionIndex)                                                      CanTp_GetSizeOfRxStateOfPCPartitionConfig(partitionIndex)
#define CanTp_GetSizeOfTxPdu2RxSduInd(partitionIndex)                                               CanTp_GetSizeOfTxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)
#define CanTp_GetSizeOfTxPdu2TxSduInd(partitionIndex)                                               CanTp_GetSizeOfTxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)
#define CanTp_GetSizeOfTxPduMap()                                                                   CanTp_GetSizeOfTxPduMapOfPCPartitionConfig()
#define CanTp_GetSizeOfTxSduCfg(partitionIndex)                                                     CanTp_GetSizeOfTxSduCfgOfPCPartitionConfig(partitionIndex)
#define CanTp_GetSizeOfTxSduSnv2Hdl()                                                               CanTp_GetSizeOfTxSduSnv2HdlOfPCPartitionConfig()
#define CanTp_GetSizeOfTxSemaphores(partitionIndex)                                                 CanTp_GetSizeOfTxSemaphoresOfPCPartitionConfig(partitionIndex)
#define CanTp_GetSizeOfTxState(partitionIndex)                                                      CanTp_GetSizeOfTxStateOfPCPartitionConfig(partitionIndex)
#define CanTp_GetTxPdu2RxSduInd(Index, partitionIndex)                                              0u
#define CanTp_GetTxPdu2TxSduInd(Index, partitionIndex)                                              0u
#define CanTp_GetCanIdOfTxPduMap(Index)                                                             CANTP_EQ2_CANIDOFTXPDUMAP
#define CanTp_GetMaskOfTxPduMap(Index)                                                              CANTP_EQ2_MASKOFTXPDUMAP
#define CanTp_GetTxPdu2RxSduEndIdxOfTxPduMap(Index)                                                 CANTP_EQ2_TXPDU2RXSDUENDIDXOFTXPDUMAP
#define CanTp_GetTxPdu2RxSduPartitionIdxOfTxPduMap(Index)                                           CANTP_EQ2_TXPDU2RXSDUPARTITIONIDXOFTXPDUMAP
#define CanTp_GetTxPdu2RxSduStartIdxOfTxPduMap(Index)                                               CANTP_EQ2_TXPDU2RXSDUSTARTIDXOFTXPDUMAP
#define CanTp_IsTxPdu2RxSduUsedOfTxPduMap(Index)                                                    (((TRUE)) != FALSE)
#define CanTp_GetTxPdu2TxSduEndIdxOfTxPduMap(Index)                                                 CANTP_EQ2_TXPDU2TXSDUENDIDXOFTXPDUMAP
#define CanTp_GetTxPdu2TxSduPartitionIdxOfTxPduMap(Index)                                           CANTP_EQ2_TXPDU2TXSDUPARTITIONIDXOFTXPDUMAP
#define CanTp_GetTxPdu2TxSduStartIdxOfTxPduMap(Index)                                               CANTP_EQ2_TXPDU2TXSDUSTARTIDXOFTXPDUMAP
#define CanTp_IsTxPdu2TxSduUsedOfTxPduMap(Index)                                                    (((TRUE)) != FALSE)
#define CanTp_GetCanTypeOfTxSduCfg(Index, partitionIndex)                                           CANTP_EQ2_CANTYPEOFTXSDUCFG
#define CanTp_GetChannelModeOfTxSduCfg(Index, partitionIndex)                                       CANTP_EQ2_CHANNELMODEOFTXSDUCFG
#define CanTp_GetLoLayerTxPduIdOfTxSduCfg(Index, partitionIndex)                                    CANTP_EQ2_LOLAYERTXPDUIDOFTXSDUCFG
#define CanTp_GetNAsOfTxSduCfg(Index, partitionIndex)                                               CANTP_EQ2_NASOFTXSDUCFG
#define CanTp_GetNBsOfTxSduCfg(Index, partitionIndex)                                               CANTP_EQ2_NBSOFTXSDUCFG
#define CanTp_GetNCsOfTxSduCfg(Index, partitionIndex)                                               CANTP_EQ2_NCSOFTXSDUCFG
#define CanTp_GetPduRTxSduIdOfTxSduCfg(Index, partitionIndex)                                       CANTP_EQ2_PDURTXSDUIDOFTXSDUCFG
#define CanTp_GetRxFcAddressOfTxSduCfg(Index, partitionIndex)                                       CANTP_EQ2_RXFCADDRESSOFTXSDUCFG
#define CanTp_GetRxFcPduIdOfTxSduCfg(Index, partitionIndex)                                         CANTP_EQ2_RXFCPDUIDOFTXSDUCFG
#define CanTp_GetRxPduMapIdxOfTxSduCfg(Index, partitionIndex)                                       CANTP_EQ2_RXPDUMAPIDXOFTXSDUCFG
#define CanTp_IsRxPduMapUsedOfTxSduCfg(Index, partitionIndex)                                       (((TRUE)) != FALSE)
#define CanTp_GetRxSduCfgIdxOfTxSduCfg(Index, partitionIndex)                                       CANTP_EQ2_RXSDUCFGIDXOFTXSDUCFG
#define CanTp_IsRxSduCfgUsedOfTxSduCfg(Index, partitionIndex)                                       (((TRUE)) != FALSE)
#define CanTp_GetSduMetadataLengthOfTxSduCfg(Index, partitionIndex)                                 0u
#define CanTp_IsTransmitCancellationOfTxSduCfg(Index, partitionIndex)                               (((CANTP_EQ2_TRANSMITCANCELLATIONOFTXSDUCFG)) != FALSE)
#define CanTp_GetTxAddressOfTxSduCfg(Index, partitionIndex)                                         255u
#define CanTp_GetTxAddressingFormatOfTxSduCfg(Index, partitionIndex)                                CANTP_EQ2_TXADDRESSINGFORMATOFTXSDUCFG
#define CanTp_GetTxMaxPayloadLengthOfTxSduCfg(Index, partitionIndex)                                CANTP_EQ2_TXMAXPAYLOADLENGTHOFTXSDUCFG
#define CanTp_IsTxPaddingActivationOfTxSduCfg(Index, partitionIndex)                                (((TRUE)) != FALSE)
#define CanTp_GetTxPduConfirmationPduIdOfTxSduCfg(Index, partitionIndex)                            CANTP_EQ2_TXPDUCONFIRMATIONPDUIDOFTXSDUCFG
#define CanTp_GetTxPduMapIdxOfTxSduCfg(Index, partitionIndex)                                       0u
#define CanTp_IsTxPduMapUsedOfTxSduCfg(Index, partitionIndex)                                       (((TRUE)) != FALSE)
#define CanTp_GetTxTaTypeOfTxSduCfg(Index, partitionIndex)                                          CANTP_EQ2_TXTATYPEOFTXSDUCFG
#define CanTp_GetTxNSduHdlIdxOfTxSduSnv2Hdl(Index)                                                  0u
#define CanTp_GetTxNSduHdlPartitionIdxOfTxSduSnv2Hdl(Index)                                         0u
#define CanTp_IsTxNSduHdlUsedOfTxSduSnv2Hdl(Index)                                                  (((TRUE)) != FALSE)

/* CSL Setters, Address Getters, Has, Inc, Dec, Add, Sub Macros */
#define CanTp_SetCalcBS(Index, Value, partitionIndex)                                               CanTp_GetCalcBSOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define CanTp_SetRxState(Index, Value, partitionIndex)                                              CanTp_GetRxStateOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define CanTp_SetTxSemaphores(Index, Value, partitionIndex)                                         CanTp_GetTxSemaphoresOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define CanTp_SetTxState(Index, Value, partitionIndex)                                              CanTp_GetTxStateOfPCPartitionConfig(partitionIndex)[(Index)] = (Value)
#define CanTp_GetAddrCalcBS(Index, partitionIndex)                                                  (&CanTp_GetCalcBS(((Index)), (partitionIndex)))
#define CanTp_GetAddrRxState(Index, partitionIndex)                                                 (&CanTp_GetRxState(((Index)), (partitionIndex)))
#define CanTp_GetAddrTxSemaphores(Index, partitionIndex)                                            (&CanTp_GetTxSemaphores(((Index)), (partitionIndex)))
#define CanTp_GetAddrTxState(Index, partitionIndex)                                                 (&CanTp_GetTxState(((Index)), (partitionIndex)))
#define CanTp_HasCalcBS(partitionIndex)                                                             (TRUE != FALSE)
#define CanTp_HasCompatibilityVersion(partitionIndex)                                               (TRUE != FALSE)
#define CanTp_HasPartitionIdentifiers()                                                             (TRUE != FALSE)
#define CanTp_HasPCPartitionConfigIdxOfPartitionIdentifiers()                                       (TRUE != FALSE)
#define CanTp_HasPartitionSNVOfPartitionIdentifiers()                                               (TRUE != FALSE)
#define CanTp_HasRxPdu2RxSduInd(partitionIndex)                                                     (TRUE != FALSE)
#define CanTp_HasRxPdu2TxSduInd(partitionIndex)                                                     (TRUE != FALSE)
#define CanTp_HasRxPduMap()                                                                         (TRUE != FALSE)
#define CanTp_HasAddressingFormatOfRxPduMap()                                                       (TRUE != FALSE)
#define CanTp_HasGenericConnectionOfRxPduMap()                                                      (TRUE != FALSE)
#define CanTp_HasPduMetadataOfRxPduMap()                                                            (TRUE != FALSE)
#define CanTp_HasRxPdu2RxSduEndIdxOfRxPduMap()                                                      (TRUE != FALSE)
#define CanTp_HasRxPdu2RxSduPartitionIdxOfRxPduMap()                                                (TRUE != FALSE)
#define CanTp_HasRxPdu2RxSduStartIdxOfRxPduMap()                                                    (TRUE != FALSE)
#define CanTp_HasRxPdu2RxSduUsedOfRxPduMap()                                                        (TRUE != FALSE)
#define CanTp_HasRxPdu2TxSduEndIdxOfRxPduMap()                                                      (TRUE != FALSE)
#define CanTp_HasRxPdu2TxSduPartitionIdxOfRxPduMap()                                                (TRUE != FALSE)
#define CanTp_HasRxPdu2TxSduStartIdxOfRxPduMap()                                                    (TRUE != FALSE)
#define CanTp_HasRxPdu2TxSduUsedOfRxPduMap()                                                        (TRUE != FALSE)
#define CanTp_HasRxSduCfg(partitionIndex)                                                           (TRUE != FALSE)
#define CanTp_HasBlockSizeOfRxSduCfg(partitionIndex)                                                (TRUE != FALSE)
#define CanTp_HasCanTypeOfRxSduCfg(partitionIndex)                                                  (TRUE != FALSE)
#define CanTp_HasChannelModeOfRxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasGenericConnectionOfRxSduCfg(partitionIndex)                                        (TRUE != FALSE)
#define CanTp_HasLoLayerTxFcPduIdOfRxSduCfg(partitionIndex)                                         (TRUE != FALSE)
#define CanTp_HasNArOfRxSduCfg(partitionIndex)                                                      (TRUE != FALSE)
#define CanTp_HasNBrOfRxSduCfg(partitionIndex)                                                      (TRUE != FALSE)
#define CanTp_HasNCrOfRxSduCfg(partitionIndex)                                                      (TRUE != FALSE)
#define CanTp_HasPduRRxSduIdOfRxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasRxAddressOfRxSduCfg(partitionIndex)                                                (TRUE != FALSE)
#define CanTp_HasRxAddressingFormatOfRxSduCfg(partitionIndex)                                       (TRUE != FALSE)
#define CanTp_HasRxMaxPayloadLengthOfRxSduCfg(partitionIndex)                                       (TRUE != FALSE)
#define CanTp_HasRxPaddingActivationOfRxSduCfg(partitionIndex)                                      (TRUE != FALSE)
#define CanTp_HasRxPduIdOfRxSduCfg(partitionIndex)                                                  (TRUE != FALSE)
#define CanTp_HasRxPduMapIdxOfRxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasRxPduMapUsedOfRxSduCfg(partitionIndex)                                             (TRUE != FALSE)
#define CanTp_HasRxTaTypeOfRxSduCfg(partitionIndex)                                                 (TRUE != FALSE)
#define CanTp_HasRxWftMaxOfRxSduCfg(partitionIndex)                                                 (TRUE != FALSE)
#define CanTp_HasSTminOfRxSduCfg(partitionIndex)                                                    (TRUE != FALSE)
#define CanTp_HasSduMetadataLengthOfRxSduCfg(partitionIndex)                                        (TRUE != FALSE)
#define CanTp_HasTxFcAddressOfRxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasTxFcPduConfirmationPduIdOfRxSduCfg(partitionIndex)                                 (TRUE != FALSE)
#define CanTp_HasTxPduMapIdxOfRxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasTxPduMapUsedOfRxSduCfg(partitionIndex)                                             (TRUE != FALSE)
#define CanTp_HasTxSduCfgIdxOfRxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasTxSduCfgUsedOfRxSduCfg(partitionIndex)                                             (TRUE != FALSE)
#define CanTp_HasRxSduSnv2Hdl()                                                                     (TRUE != FALSE)
#define CanTp_HasRxNSduHdlIdxOfRxSduSnv2Hdl()                                                       (TRUE != FALSE)
#define CanTp_HasRxNSduHdlPartitionIdxOfRxSduSnv2Hdl()                                              (TRUE != FALSE)
#define CanTp_HasRxNSduHdlUsedOfRxSduSnv2Hdl()                                                      (TRUE != FALSE)
#define CanTp_HasRxState(partitionIndex)                                                            (TRUE != FALSE)
#define CanTp_HasSizeOfCalcBS(partitionIndex)                                                       (TRUE != FALSE)
#define CanTp_HasSizeOfPartitionIdentifiers()                                                       (TRUE != FALSE)
#define CanTp_HasSizeOfRxPdu2RxSduInd(partitionIndex)                                               (TRUE != FALSE)
#define CanTp_HasSizeOfRxPdu2TxSduInd(partitionIndex)                                               (TRUE != FALSE)
#define CanTp_HasSizeOfRxPduMap()                                                                   (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduCfg(partitionIndex)                                                     (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduSnv2Hdl()                                                               (TRUE != FALSE)
#define CanTp_HasSizeOfRxState(partitionIndex)                                                      (TRUE != FALSE)
#define CanTp_HasSizeOfTxPdu2RxSduInd(partitionIndex)                                               (TRUE != FALSE)
#define CanTp_HasSizeOfTxPdu2TxSduInd(partitionIndex)                                               (TRUE != FALSE)
#define CanTp_HasSizeOfTxPduMap()                                                                   (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduCfg(partitionIndex)                                                     (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduSnv2Hdl()                                                               (TRUE != FALSE)
#define CanTp_HasSizeOfTxSemaphores(partitionIndex)                                                 (TRUE != FALSE)
#define CanTp_HasSizeOfTxState(partitionIndex)                                                      (TRUE != FALSE)
#define CanTp_HasTxPdu2RxSduInd(partitionIndex)                                                     (TRUE != FALSE)
#define CanTp_HasTxPdu2TxSduInd(partitionIndex)                                                     (TRUE != FALSE)
#define CanTp_HasTxPduMap()                                                                         (TRUE != FALSE)
#define CanTp_HasCanIdOfTxPduMap()                                                                  (TRUE != FALSE)
#define CanTp_HasMaskOfTxPduMap()                                                                   (TRUE != FALSE)
#define CanTp_HasTxPdu2RxSduEndIdxOfTxPduMap()                                                      (TRUE != FALSE)
#define CanTp_HasTxPdu2RxSduPartitionIdxOfTxPduMap()                                                (TRUE != FALSE)
#define CanTp_HasTxPdu2RxSduStartIdxOfTxPduMap()                                                    (TRUE != FALSE)
#define CanTp_HasTxPdu2RxSduUsedOfTxPduMap()                                                        (TRUE != FALSE)
#define CanTp_HasTxPdu2TxSduEndIdxOfTxPduMap()                                                      (TRUE != FALSE)
#define CanTp_HasTxPdu2TxSduPartitionIdxOfTxPduMap()                                                (TRUE != FALSE)
#define CanTp_HasTxPdu2TxSduStartIdxOfTxPduMap()                                                    (TRUE != FALSE)
#define CanTp_HasTxPdu2TxSduUsedOfTxPduMap()                                                        (TRUE != FALSE)
#define CanTp_HasTxSduCfg(partitionIndex)                                                           (TRUE != FALSE)
#define CanTp_HasCanTypeOfTxSduCfg(partitionIndex)                                                  (TRUE != FALSE)
#define CanTp_HasChannelModeOfTxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasLoLayerTxPduIdOfTxSduCfg(partitionIndex)                                           (TRUE != FALSE)
#define CanTp_HasNAsOfTxSduCfg(partitionIndex)                                                      (TRUE != FALSE)
#define CanTp_HasNBsOfTxSduCfg(partitionIndex)                                                      (TRUE != FALSE)
#define CanTp_HasNCsOfTxSduCfg(partitionIndex)                                                      (TRUE != FALSE)
#define CanTp_HasPduRTxSduIdOfTxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasRxFcAddressOfTxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasRxFcPduIdOfTxSduCfg(partitionIndex)                                                (TRUE != FALSE)
#define CanTp_HasRxPduMapIdxOfTxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasRxPduMapUsedOfTxSduCfg(partitionIndex)                                             (TRUE != FALSE)
#define CanTp_HasRxSduCfgIdxOfTxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasRxSduCfgUsedOfTxSduCfg(partitionIndex)                                             (TRUE != FALSE)
#define CanTp_HasSduMetadataLengthOfTxSduCfg(partitionIndex)                                        (TRUE != FALSE)
#define CanTp_HasTransmitCancellationOfTxSduCfg(partitionIndex)                                     (TRUE != FALSE)
#define CanTp_HasTxAddressOfTxSduCfg(partitionIndex)                                                (TRUE != FALSE)
#define CanTp_HasTxAddressingFormatOfTxSduCfg(partitionIndex)                                       (TRUE != FALSE)
#define CanTp_HasTxMaxPayloadLengthOfTxSduCfg(partitionIndex)                                       (TRUE != FALSE)
#define CanTp_HasTxPaddingActivationOfTxSduCfg(partitionIndex)                                      (TRUE != FALSE)
#define CanTp_HasTxPduConfirmationPduIdOfTxSduCfg(partitionIndex)                                   (TRUE != FALSE)
#define CanTp_HasTxPduMapIdxOfTxSduCfg(partitionIndex)                                              (TRUE != FALSE)
#define CanTp_HasTxPduMapUsedOfTxSduCfg(partitionIndex)                                             (TRUE != FALSE)
#define CanTp_HasTxTaTypeOfTxSduCfg(partitionIndex)                                                 (TRUE != FALSE)
#define CanTp_HasTxSduSnv2Hdl()                                                                     (TRUE != FALSE)
#define CanTp_HasTxNSduHdlIdxOfTxSduSnv2Hdl()                                                       (TRUE != FALSE)
#define CanTp_HasTxNSduHdlPartitionIdxOfTxSduSnv2Hdl()                                              (TRUE != FALSE)
#define CanTp_HasTxNSduHdlUsedOfTxSduSnv2Hdl()                                                      (TRUE != FALSE)
#define CanTp_HasTxSemaphores(partitionIndex)                                                       (TRUE != FALSE)
#define CanTp_HasTxState(partitionIndex)                                                            (TRUE != FALSE)
#define CanTp_HasPCConfig()                                                                         (TRUE != FALSE)
#define CanTp_HasPCPartitionConfigOfPCConfig()                                                      (TRUE != FALSE)
#define CanTp_HasPartitionIdentifiersOfPCConfig()                                                   (TRUE != FALSE)
#define CanTp_HasSizeOfPartitionIdentifiersOfPCConfig()                                             (TRUE != FALSE)
#define CanTp_HasPCPartitionConfig()                                                                (TRUE != FALSE)
#define CanTp_HasCalcBSOfPCPartitionConfig(partitionIndex)                                          (TRUE != FALSE)
#define CanTp_HasCompatibilityVersionOfPCPartitionConfig(partitionIndex)                            (TRUE != FALSE)
#define CanTp_HasRxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)                                  (TRUE != FALSE)
#define CanTp_HasRxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)                                  (TRUE != FALSE)
#define CanTp_HasRxPduMapOfPCPartitionConfig()                                                      (TRUE != FALSE)
#define CanTp_HasRxSduCfgOfPCPartitionConfig(partitionIndex)                                        (TRUE != FALSE)
#define CanTp_HasRxSduSnv2HdlOfPCPartitionConfig()                                                  (TRUE != FALSE)
#define CanTp_HasRxStateOfPCPartitionConfig(partitionIndex)                                         (TRUE != FALSE)
#define CanTp_HasSizeOfCalcBSOfPCPartitionConfig(partitionIndex)                                    (TRUE != FALSE)
#define CanTp_HasSizeOfRxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)                            (TRUE != FALSE)
#define CanTp_HasSizeOfRxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)                            (TRUE != FALSE)
#define CanTp_HasSizeOfRxPduMapOfPCPartitionConfig()                                                (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduCfgOfPCPartitionConfig(partitionIndex)                                  (TRUE != FALSE)
#define CanTp_HasSizeOfRxSduSnv2HdlOfPCPartitionConfig()                                            (TRUE != FALSE)
#define CanTp_HasSizeOfRxStateOfPCPartitionConfig(partitionIndex)                                   (TRUE != FALSE)
#define CanTp_HasSizeOfTxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)                            (TRUE != FALSE)
#define CanTp_HasSizeOfTxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)                            (TRUE != FALSE)
#define CanTp_HasSizeOfTxPduMapOfPCPartitionConfig()                                                (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduCfgOfPCPartitionConfig(partitionIndex)                                  (TRUE != FALSE)
#define CanTp_HasSizeOfTxSduSnv2HdlOfPCPartitionConfig()                                            (TRUE != FALSE)
#define CanTp_HasSizeOfTxSemaphoresOfPCPartitionConfig(partitionIndex)                              (TRUE != FALSE)
#define CanTp_HasSizeOfTxStateOfPCPartitionConfig(partitionIndex)                                   (TRUE != FALSE)
#define CanTp_HasTxPdu2RxSduIndOfPCPartitionConfig(partitionIndex)                                  (TRUE != FALSE)
#define CanTp_HasTxPdu2TxSduIndOfPCPartitionConfig(partitionIndex)                                  (TRUE != FALSE)
#define CanTp_HasTxPduMapOfPCPartitionConfig()                                                      (TRUE != FALSE)
#define CanTp_HasTxSduCfgOfPCPartitionConfig(partitionIndex)                                        (TRUE != FALSE)
#define CanTp_HasTxSduSnv2HdlOfPCPartitionConfig()                                                  (TRUE != FALSE)
#define CanTp_HasTxSemaphoresOfPCPartitionConfig(partitionIndex)                                    (TRUE != FALSE)
#define CanTp_HasTxStateOfPCPartitionConfig(partitionIndex)                                         (TRUE != FALSE)
#define CanTp_IncCalcBS(Index, partitionIndex)                                                      CanTp_GetCalcBS(((Index)), (partitionIndex))++
#define CanTp_IncRxState(Index, partitionIndex)                                                     CanTp_GetRxState(((Index)), (partitionIndex))++
#define CanTp_IncTxSemaphores(Index, partitionIndex)                                                CanTp_GetTxSemaphores(((Index)), (partitionIndex))++
#define CanTp_IncTxState(Index, partitionIndex)                                                     CanTp_GetTxState(((Index)), (partitionIndex))++
#define CanTp_DecCalcBS(Index, partitionIndex)                                                      CanTp_GetCalcBS(((Index)), (partitionIndex))--
#define CanTp_DecRxState(Index, partitionIndex)                                                     CanTp_GetRxState(((Index)), (partitionIndex))--
#define CanTp_DecTxSemaphores(Index, partitionIndex)                                                CanTp_GetTxSemaphores(((Index)), (partitionIndex))--
#define CanTp_DecTxState(Index, partitionIndex)                                                     CanTp_GetTxState(((Index)), (partitionIndex))--
#define CanTp_AddCalcBS(Index, Value, partitionIndex)                                               CanTp_SetCalcBS(Index, (CanTp_GetCalcBS(((Index)), (partitionIndex)) + Value), partitionIndex)
#define CanTp_AddRxState(Index, Value, partitionIndex)                                              CanTp_SetRxState(Index, (CanTp_GetRxState(((Index)), (partitionIndex)) + Value), partitionIndex)
#define CanTp_AddTxSemaphores(Index, Value, partitionIndex)                                         CanTp_SetTxSemaphores(Index, (CanTp_GetTxSemaphores(((Index)), (partitionIndex)) + Value), partitionIndex)
#define CanTp_AddTxState(Index, Value, partitionIndex)                                              CanTp_SetTxState(Index, (CanTp_GetTxState(((Index)), (partitionIndex)) + Value), partitionIndex)
#define CanTp_SubCalcBS(Index, Value, partitionIndex)                                               CanTp_SetCalcBS(Index, (CanTp_GetCalcBS(((Index)), (partitionIndex)) - Value), partitionIndex)
#define CanTp_SubRxState(Index, Value, partitionIndex)                                              CanTp_SetRxState(Index, (CanTp_GetRxState(((Index)), (partitionIndex)) - Value), partitionIndex)
#define CanTp_SubTxSemaphores(Index, Value, partitionIndex)                                         CanTp_SetTxSemaphores(Index, (CanTp_GetTxSemaphores(((Index)), (partitionIndex)) - Value), partitionIndex)
#define CanTp_SubTxState(Index, Value, partitionIndex)                                              CanTp_SetTxState(Index, (CanTp_GetTxState(((Index)), (partitionIndex)) - Value), partitionIndex)
#define CANTP_LTCONFIG                                                                              STD_OFF
#define CANTP_LTPARTITIONCONFIGOFLTCONFIG                                                           STD_OFF
#define CANTP_LTPARTITIONCONFIG                                                                     STD_OFF
#define CANTP_PBCONFIG                                                                              STD_OFF
#define CANTP_LTCONFIGIDXOFPBCONFIG                                                                 STD_OFF
#define CANTP_PBPARTITIONCONFIGOFPBCONFIG                                                           STD_OFF
#define CANTP_PCCONFIGIDXOFPBCONFIG                                                                 STD_OFF
#define CANTP_PBPARTITIONCONFIG                                                                     STD_OFF

#endif /* CANTP_CFG_H */

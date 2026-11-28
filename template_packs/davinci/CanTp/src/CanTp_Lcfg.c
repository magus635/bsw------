[!AUTOSPACING!]
[!/* Vector MICROSAR CanTp_Lcfg.c CSL Template */!]
#define CANTP_LCFG_SOURCE

#include "CanTp_Lcfg.h"
#if (CANTP_LOLAYER_CANIF == STD_ON)
# include "CanIf.h"
#endif
#include "PduR_CanTp.h"

[!VAR "numRxSdus" = "count(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpRxNSduId)])"!][!//
[!VAR "numTxSdus" = "count(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpTxNSduId)])"!][!//
[!VAR "numRxNPdus" = "count(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpRxNPduId)])"!][!//
[!IF "$numRxNPdus = 0"!][!VAR "numRxNPdus" = "$numRxSdus"!][!ENDIF!][!//

#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"
#if(CANTP_USE_INIT_POINTER == STD_ON)
P2CONST(CanTp_PBConfigType, CANTP_VAR_CLEARED, CANTP_PBCFG) CanTp_ConfigDataPtr = (P2CONST(CanTp_PBConfigType, CANTP_VAR_CLEARED, CANTP_PBCFG))NULL_PTR;
#endif
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"
VAR(boolean, CANTP_VAR_NO_INIT) CanTp_PreInitialized;
#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
CONST(CanTp_PartitionIdentifiersType, CANTP_CONST) CanTp_PartitionIdentifiers[1] = {
  {  CanTpSinglePartitionMemory, 0u }
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "CanTp_MemMap.h"
CONST(CanTp_RxPdu2RxSduIndType, CANTP_CONST) CanTp_RxPdu2RxSduInd[[!"num:i($numRxNPdus)"!]] = {
[!VAR "rxPduIndIdx" = "0"!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpRxNPduId)], 'num:i(CanTpRxNPduId)')"!][!//
[!VAR "rxSduIdx" = "num:i(../CanTpRxNSduId)"!][!//
[!VAR "sep" = "','"!][!IF "$rxPduIndIdx + 1 >= $numRxNPdus"!][!VAR "sep" = ""!][!ENDIF!][!//
  [!"num:i($rxSduIdx)"!]u[!"$sep"!]
[!VAR "rxPduIndIdx" = "$rxPduIndIdx + 1"!][!//
[!ENDLOOP!][!//
};
#define CANTP_STOP_SEC_CONST_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
CONST(CanTp_RxPduMapType, CANTP_CONST) CanTp_RxPduMap[[!"num:i($numRxNPdus)"!]] = {
[!VAR "rxMapIdx" = "0"!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpRxNPduId)], 'num:i(CanTpRxNPduId)')"!][!//
[!VAR "rxNPduRef" = "CanTpRxNPduRef"!][!//
[!VAR "rxStartIdx" = "num:i($rxMapIdx)"!][!//
[!VAR "rxEndIdx" = "num:i($rxMapIdx + 1)"!][!//
[!VAR "txStart" = "'CANTP_NO_RXPDU2TXSDUSTARTIDXOFRXPDUMAP'"!][!//
[!VAR "txEnd" = "'CANTP_NO_RXPDU2TXSDUENDIDXOFRXPDUMAP'"!][!//
[!VAR "txPart" = "'CANTP_NO_RXPDU2TXSDUPARTITIONIDXOFRXPDUMAP'"!][!//
[!VAR "matchedTxFc" = "'false'"!][!//
[!VAR "txFcSearchIdx" = "0"!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpTxNSduId)], 'num:i(CanTpTxNSduId)')"!][!//
  [!IF "node:exists(*[node:exists(CanTpRxFcNPduId)]) and *[node:exists(CanTpRxFcNPduId)]/CanTpRxFcNPduRef = $rxNPduRef and $matchedTxFc = 'false'"!][!//
    [!VAR "txStart" = "concat(num:i($txFcSearchIdx), 'u')"!][!//
    [!VAR "txEnd" = "concat(num:i($txFcSearchIdx + 1), 'u')"!][!//
    [!VAR "txPart" = "'0u'"!][!//
    [!VAR "matchedTxFc" = "'true'"!][!//
  [!ENDIF!][!//
  [!VAR "txFcSearchIdx" = "$txFcSearchIdx + 1"!][!//
[!ENDLOOP!][!//
[!VAR "sep" = "','"!][!IF "$rxMapIdx + 1 >= $numRxNPdus"!][!VAR "sep" = ""!][!ENDIF!][!//
  { [!"num:i($rxEndIdx)"!]u, [!"num:i($rxStartIdx)"!]u, [!"$txEnd"!], [!"$txPart"!], [!"$txStart"!] }[!"$sep"!]
[!VAR "rxMapIdx" = "$rxMapIdx + 1"!][!//
[!ENDLOOP!][!//
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
CONST(CanTp_RxSduCfgType, CANTP_CONST) CanTp_RxSduCfg[[!"num:i($numRxSdus)"!]] = {
[!VAR "rxCfgIdx" = "0"!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpRxNSduId)], 'num:i(CanTpRxNSduId)')"!][!//
[!VAR "loLayerTxFc" = "'CANTP_INVALID_HDL'"!][!//
[!VAR "txFcCfmSym" = "'CANTP_INVALID_HDL'"!][!//
[!VAR "txPduMapIdx" = "'CANTP_NO_TXPDUMAPIDXOFRXSDUCFG'"!][!//
[!VAR "txSduCfgIdx" = "'CANTP_NO_TXSDUCFGIDXOFRXSDUCFG'"!][!//
[!IF "node:exists(*[node:exists(CanTpTxFcNPduConfirmationPduId)])"!][!//
  [!VAR "txFcRef" = "*[node:exists(CanTpTxFcNPduConfirmationPduId)]/CanTpTxFcNPduRef"!][!//
  [!VAR "txFcCfmSym" = "concat('CanTpConf_CanTpTxFcNPdu_', node:name(*[node:exists(CanTpTxFcNPduConfirmationPduId)]))"!][!//
  [!IF "node:exists(as:modconf('CanIf'))"!][!//
    [!LOOP "as:modconf('CanIf')[1]/CanIfInitCfg/*[CanIfTxPduRef = $txFcRef]"!][!//
      [!VAR "loLayerTxFc" = "concat('CanIfConf_CanIfTxPduCfg_', @name)"!][!//
    [!ENDLOOP!][!//
  [!ELSE!][!//
    [!VAR "loLayerTxFc" = "'0u'"!][!//
  [!ENDIF!][!//
  [!VAR "tSearchIdx" = "0"!][!//
  [!VAR "foundTxMatch" = "'false'"!][!//
  [!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpTxNSduId)], 'num:i(CanTpTxNSduId)')"!][!//
    [!IF "node:exists(*[node:exists(CanTpTxNPduConfirmationPduId)]) and *[node:exists(CanTpTxNPduConfirmationPduId)]/CanTpTxNPduRef = $txFcRef and $foundTxMatch = 'false'"!][!//
      [!VAR "txPduMapIdx" = "concat(num:i($tSearchIdx), 'u')"!][!//
      [!VAR "txSduCfgIdx" = "concat(num:i($tSearchIdx), 'u')"!][!//
      [!VAR "foundTxMatch" = "'true'"!][!//
    [!ENDIF!][!//
    [!VAR "tSearchIdx" = "$tSearchIdx + 1"!][!//
  [!ENDLOOP!][!//
[!ENDIF!][!//
[!VAR "rxSduRef" = "CanTpRxNSduRef"!][!//
[!VAR "pdurRxSduSym" = "concat(num:i(CanTpRxNSduId), 'u')"!][!//
[!IF "node:exists(as:modconf('PduR'))"!][!//
  [!LOOP "as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRSrcPduRef = $rxSduRef]"!][!//
    [!VAR "pdurRxSduSym" = "concat('PduRConf_PduRSrcPdu_', @name)"!][!//
  [!ENDLOOP!][!//
[!ENDIF!][!//
[!VAR "rxNPduSym" = "'CANTP_INVALID_HDL'"!][!//
[!VAR "rxNPduIdCur" = "num:i($rxCfgIdx)"!][!//
[!IF "node:exists(*[node:exists(CanTpRxNPduId)])"!][!//
  [!VAR "rxNPduSym" = "concat('CanTpConf_CanTpRxNPdu_', node:name(*[node:exists(CanTpRxNPduId)]))"!]
  [!VAR "rxNPduIdCur" = "num:i(*[node:exists(CanTpRxNPduId)]/CanTpRxNPduId)"!][!//
[!ENDIF!][!//
[!VAR "bsVal" = "8"!][!IF "node:exists(CanTpBs)"!][!VAR "bsVal" = "num:i(CanTpBs)"!][!ENDIF!][!//
[!VAR "wftVal" = "15"!][!IF "node:exists(CanTpRxWftMax)"!][!VAR "wftVal" = "num:i(CanTpRxWftMax)"!][!ENDIF!][!//
[!VAR "taTypeMacro" = "'CANTP_PHYSICAL_RXTATYPEOFRXSDUCFG'"!][!//
[!IF "CanTpRxTaType = 'CANTP_FUNCTIONAL'"!][!VAR "taTypeMacro" = "'CANTP_FUNCTIONAL_RXTATYPEOFRXSDUCFG'"!][!ENDIF!][!//
[!VAR "rxMapRefIdx" = "num:i($rxCfgIdx)"!][!//
[!VAR "searchMapIdx" = "0"!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*/*[node:exists(CanTpRxNPduId)], 'num:i(CanTpRxNPduId)')"!][!//
  [!IF "num:i(CanTpRxNPduId) = $rxNPduIdCur"!][!VAR "rxMapRefIdx" = "num:i($searchMapIdx)"!][!ENDIF!][!//
  [!VAR "searchMapIdx" = "$searchMapIdx + 1"!][!//
[!ENDLOOP!][!//
[!VAR "sep" = "','"!][!IF "$rxCfgIdx + 1 >= $numRxSdus"!][!VAR "sep" = ""!][!ENDIF!][!//
  { [!"$loLayerTxFc"!], [!"$pdurRxSduSym"!], [!"$rxNPduSym"!], [!"$txFcCfmSym"!], [!"num:i($bsVal)"!]u, [!"num:i($rxMapRefIdx)"!]u, [!"$taTypeMacro"!], [!"num:i($wftVal)"!]u, [!"$txPduMapIdx"!], [!"$txSduCfgIdx"!] }[!"$sep"!]
[!VAR "rxCfgIdx" = "$rxCfgIdx + 1"!][!//
[!ENDLOOP!][!//
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
CONST(CanTp_RxSduSnv2HdlType, CANTP_CONST) CanTp_RxSduSnv2Hdl[[!"num:i($numRxSdus)"!]] = {
[!VAR "snvIdx" = "0"!][!//
[!LOOP "node:order(as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpRxNSduId)], 'num:i(CanTpRxNSduId)')"!][!//
[!VAR "sep" = "','"!][!IF "$snvIdx + 1 >= $numRxSdus"!][!VAR "sep" = ""!][!ENDIF!][!//
  { [!"num:i($snvIdx)"!]u }[!"$sep"!]
[!VAR "snvIdx" = "$snvIdx + 1"!][!//
[!ENDLOOP!][!//
};
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_NO_INIT_8
#include "CanTp_MemMap.h"
VAR(CanTp_CalcBSType, CANTP_VAR_NO_INIT) CanTp_CalcBS[[!"num:i($numRxSdus)"!]];
#define CANTP_STOP_SEC_VAR_NO_INIT_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"
VAR(CanTp_RxStateType, CANTP_VAR_NO_INIT) CanTp_RxState[[!"num:i($numRxSdus)"!]];
#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"

[!IF "$numTxSdus > 0"!][!//
#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"
VAR(CanTp_TxSemaphoreType, CANTP_VAR_NO_INIT) CanTp_TxSemaphores[[!"num:i($numTxSdus)"!]];
#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"
VAR(CanTp_TxStateType, CANTP_VAR_NO_INIT) CanTp_TxState[[!"num:i($numTxSdus)"!]];
#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanTp_MemMap.h"
[!ENDIF!][!//

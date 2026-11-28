[!AUTOSPACING!]
[!/* Vector MICROSAR PduR_Lcfg.c CSL Template */!]
#define PDUR_LCFG_SOURCE

#include "PduR.h"
#include "SchM_PduR.h"
#if(PDUR_DEV_ERROR_REPORT == STD_ON)
# include "Det.h"
#endif
#include "PduR_Lcfg.h"

#define CommonSharedMemory 0u

[!VAR "numMods" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!VAR "numMods" = "$numMods + 1"!][!ENDLOOP!][!//
[!VAR "hasDeepPaths" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[node:exists(PduRRoutingPathCommunicationType) and (*/PduRSrcPduDirection = 'RECEIVE' or */PduRSrcPduDirection = 'TRANSMIT')])"!][!//
[!IF "$hasDeepPaths > 0"!][!//
[!VAR "numIfRx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'])"!][!//
[!VAR "numTpRx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'])"!][!//
[!VAR "numIfTx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'])"!][!//
[!VAR "numTpTx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'])"!][!//
[!ELSE!][!//
[!VAR "numIfRx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'])"!][!//
[!VAR "numTpRx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'])"!][!//
[!VAR "numIfTx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'])"!][!//
[!VAR "numTpTx" = "count(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'])"!][!//
[!ENDIF!][!//
[!VAR "numPaths" = "num:i($numIfRx + $numTpRx + $numIfTx + $numTpTx)"!][!//

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
static FUNC(void, PDUR_CODE) PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0(void);
static FUNC(void, PDUR_CODE) PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0(void);
[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!//
[!VAR "mName" = "@name"!][!//
[!IF "PduRUpperModule = 'true'"!][!//
FUNC(Std_ReturnType, PDUR_CODE) PduR_[!"$mName"!]Transmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
[!IF "node:exists(PduRCancelTransmit) and PduRCancelTransmit = 'true'"!][!//
FUNC(Std_ReturnType, PDUR_CODE) PduR_[!"$mName"!]CancelTransmit(PduIdType id);
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "PduRLowerModule = 'true' and PduRCommunicationInterface = 'true'"!][!//
FUNC(void, PDUR_CODE) PduR_[!"$mName"!]RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info);
[!IF "node:exists(PduRTxConfirmation) and PduRTxConfirmation = 'true'"!][!//
FUNC(void, PDUR_CODE) PduR_[!"$mName"!]TxConfirmation(PduIdType TxPduId);
[!ENDIF!][!//
[!ENDIF!][!//
[!IF "PduRLowerModule = 'true' and PduRTransportProtocol = 'true'"!][!//
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_[!"$mName"!]StartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_[!"$mName"!]CopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr);
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_[!"$mName"!]CopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr);
FUNC(void, PDUR_CODE) PduR_[!"$mName"!]RxIndication(PduIdType id, Std_ReturnType result);
FUNC(void, PDUR_CODE) PduR_[!"$mName"!]TxConfirmation(PduIdType id, Std_ReturnType result);
[!ENDIF!][!//
[!ENDLOOP!][!//
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
CONST(PduR_ExclusiveAreaRomType, PDUR_CONST) PduR_ExclusiveAreaRom[1] = {
  { PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0, PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0 }
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
CONST(PduR_MmRomType, PDUR_CONST) PduR_MmRom[[!"num:i($numMods)"!]] = {
[!VAR "mIdx" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!//
[!VAR "mName" = "@name"!][!//
[!VAR "loIf" = "'FALSE'"!][!IF "PduRLowerModule = 'true' and PduRCommunicationInterface = 'true'"!][!VAR "loIf" = "'TRUE'"!][!ENDIF!][!//
[!VAR "loTp" = "'FALSE'"!][!IF "PduRLowerModule = 'true' and PduRTransportProtocol = 'true'"!][!VAR "loTp" = "'TRUE'"!][!ENDIF!][!//
[!VAR "upIf" = "'FALSE'"!][!IF "PduRUpperModule = 'true' and PduRCommunicationInterface = 'true'"!][!VAR "upIf" = "'TRUE'"!][!ENDIF!][!//
[!VAR "upTp" = "'FALSE'"!][!IF "PduRUpperModule = 'true' and PduRTransportProtocol = 'true'"!][!VAR "upTp" = "'TRUE'"!][!ENDIF!][!//
[!VAR "loTpCxlRx" = "'NULL_PTR'"!][!//
[!VAR "loIfCxlTx" = "'NULL_PTR'"!][!//
[!VAR "loTpCxlTx" = "'NULL_PTR'"!][!//
[!VAR "loTpChgPar" = "'NULL_PTR'"!][!//
[!VAR "upTpCpyRx" = "'NULL_PTR'"!][!IF "$upTp = 'TRUE'"!][!VAR "upTpCpyRx" = "concat($mName, '_CopyRxData')"!][!ENDIF!][!//
[!VAR "upTpCpyTx" = "'NULL_PTR'"!][!IF "$upTp = 'TRUE'"!][!VAR "upTpCpyTx" = "concat($mName, '_CopyTxData')"!][!ENDIF!][!//
[!VAR "upIfRxInd" = "'NULL_PTR'"!][!IF "$upIf = 'TRUE'"!][!VAR "upIfRxInd" = "concat($mName, '_RxIndication')"!][!ENDIF!][!//
[!VAR "upIfTxCfm" = "'NULL_PTR'"!][!IF "$upIf = 'TRUE' and node:exists(PduRTxConfirmation) and PduRTxConfirmation = 'true'"!][!VAR "upIfTxCfm" = "concat($mName, '_TxConfirmation')"!][!ENDIF!][!//
[!VAR "upTpSor" = "'NULL_PTR'"!][!IF "$upTp = 'TRUE'"!][!VAR "upTpSor" = "concat($mName, '_StartOfReception')"!][!ENDIF!][!//
[!VAR "upTpRxInd" = "'NULL_PTR'"!][!IF "$upTp = 'TRUE'"!][!VAR "upTpRxInd" = "concat($mName, '_TpRxIndication')"!][!ENDIF!][!//
[!VAR "upTpTxCfm" = "'NULL_PTR'"!][!IF "$upTp = 'TRUE'"!][!VAR "upTpTxCfm" = "concat($mName, '_TpTxConfirmation')"!][!ENDIF!][!//
[!VAR "loIfTx" = "'NULL_PTR'"!][!IF "$loIf = 'TRUE'"!][!VAR "loIfTx" = "concat($mName, '_Transmit')"!][!ENDIF!][!//
[!VAR "loTpTx" = "'NULL_PTR'"!][!IF "$loTp = 'TRUE'"!][!VAR "loTpTx" = "concat($mName, '_Transmit')"!][!ENDIF!][!//
[!VAR "upIfTrigTx" = "'NULL_PTR'"!][!IF "$upIf = 'TRUE' and node:exists(PduRTriggertransmit) and PduRTriggertransmit = 'true'"!][!VAR "upIfTrigTx" = "concat($mName, '_TriggerTransmit')"!][!ENDIF!][!//
[!VAR "sep" = "','"!][!IF "$mIdx + 1 >= $numMods"!][!VAR "sep" = ""!][!ENDIF!][!//
  { [!"$loIf"!], [!"$loTp"!], [!"$upIf"!], [!"$upTp"!], [!"$loTpCxlRx"!], [!"$loIfCxlTx"!], [!"$loTpCxlTx"!], [!"$loTpChgPar"!], [!"$upTpCpyRx"!], [!"$upTpCpyTx"!], [!"$upIfRxInd"!], [!"$upIfTxCfm"!], [!"$upTpSor"!], [!"$upTpRxInd"!], [!"$upTpTxCfm"!], [!"$loIfTx"!], [!"$loTpTx"!], [!"$upIfTrigTx"!] }[!"$sep"!]
[!VAR "mIdx" = "$mIdx + 1"!][!//
[!ENDLOOP!][!//
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
CONST(PduR_PartitionIdentifiersType, PDUR_CONST) PduR_PartitionIdentifiers[1] = {
  { CommonSharedMemory }
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
[!MACRO "EmitRmDest", "gIdx", "pIdx", "rType", "totalCount"!][!//
  [!VAR "strat" = "'PDUR_UNUSED_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM'"!][!//
  [!IF "node:exists(*/PduRPduLengthHandlingStrategy)"!][!//
    [!IF "*/PduRPduLengthHandlingStrategy = 'IGNORE'"!][!VAR "strat" = "'PDUR_IGNORE_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM'"!][!ENDIF!][!//
    [!IF "*/PduRPduLengthHandlingStrategy = 'SHORTEN'"!][!VAR "strat" = "'PDUR_SHORTEN_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM'"!][!ENDIF!][!//
    [!IF "*/PduRPduLengthHandlingStrategy = 'DISCARD'"!][!VAR "strat" = "'PDUR_DISCARD_PDULENGTHHANDLINGSTRATEGYOFRMDESTROM'"!][!ENDIF!][!//
  [!ENDIF!][!//
  [!VAR "sep" = "','"!][!IF "$pIdx + 1 >= $totalCount"!][!VAR "sep" = ""!][!ENDIF!][!//
  { [!"$strat"!], [!"num:i($gIdx)"!]u, [!"num:i($pIdx)"!]u, [!"$rType"!] }[!"$sep"!]
[!ENDMACRO!][!//
CONST(PduR_RmDestRomType, PDUR_CONST) PduR_RmDestRom[[!"num:i($numPaths)"!]] = {
[!/* Ordered matching RmSrcRom buckets: IF_RX, TP_RX, IF_TX, TP_TX */!][!//
[!VAR "pIdx" = "0"!][!//
[!IF "$hasDeepPaths > 0"!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmDest", "gIdx" = "num:i($numTpTx + $numIfTx + $numTpRx + $k)", "pIdx" = "$pIdx", "rType" = "'PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM'", "totalCount" = "$numPaths"!][!//
[!VAR "pIdx" = "$pIdx + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmDest", "gIdx" = "num:i($numTpTx + $numIfTx + $k)", "pIdx" = "$pIdx", "rType" = "'PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM'", "totalCount" = "$numPaths"!][!//
[!VAR "pIdx" = "$pIdx + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmDest", "gIdx" = "num:i($numTpTx + $k)", "pIdx" = "$pIdx", "rType" = "'PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM'", "totalCount" = "$numPaths"!][!//
[!VAR "pIdx" = "$pIdx + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmDest", "gIdx" = "num:i($k)", "pIdx" = "$pIdx", "rType" = "'PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM'", "totalCount" = "$numPaths"!][!//
[!VAR "pIdx" = "$pIdx + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!ELSE!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmDest", "gIdx" = "num:i($numTpTx + $numIfTx + $numTpRx + $k)", "pIdx" = "$pIdx", "rType" = "'PDUR_IF_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM'", "totalCount" = "$numPaths"!][!//
[!VAR "pIdx" = "$pIdx + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmDest", "gIdx" = "num:i($numTpTx + $numIfTx + $k)", "pIdx" = "$pIdx", "rType" = "'PDUR_TP_UNBUFFERED_RX_API_FWD_ROUTINGTYPEOFRMDESTROM'", "totalCount" = "$numPaths"!][!//
[!VAR "pIdx" = "$pIdx + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmDest", "gIdx" = "num:i($numTpTx + $k)", "pIdx" = "$pIdx", "rType" = "'PDUR_IF_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM'", "totalCount" = "$numPaths"!][!//
[!VAR "pIdx" = "$pIdx + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmDest", "gIdx" = "num:i($k)", "pIdx" = "$pIdx", "rType" = "'PDUR_TP_UNBUFFERED_TX_API_FWD_ROUTINGTYPEOFRMDESTROM'", "totalCount" = "$numPaths"!][!//
[!VAR "pIdx" = "$pIdx + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
CONST(PduR_RmGDestRomType, PDUR_CONST) PduR_RmGDestRom[[!"num:i($numPaths)"!]] = {
[!/* Ordered matching RmGDestRom buckets: TP_TX, IF_TX, TP_RX, IF_RX */!][!//
[!MACRO "EmitRmGDest", "destIdx", "dirMac", "destBucketIdx", "totalCount"!][!//
[!VAR "destModRef" = "*/PduRDestPduPduRBswModulesRef"!][!//
[!VAR "destPduRef" = "*/PduRDestPduRef"!][!//
[!VAR "destIdFallback" = "concat(num:i(*/PduRDestPduHandleId), 'u')"!][!//
[!VAR "destModIdx" = "0"!][!//
[!VAR "destModName" = "''"!][!//
[!VAR "mSearch" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!//
  [!IF "contains(concat($destModRef, '#'), concat('/', @name, '#'))"!][!//
    [!VAR "destModIdx" = "$mSearch"!][!//
    [!VAR "destModName" = "@name"!][!//
  [!ENDIF!][!//
  [!VAR "mSearch" = "$mSearch + 1"!][!//
[!ENDLOOP!][!//
[!VAR "destHnd" = "$destIdFallback"!][!//
[!IF "$destModName = 'CanIf' and node:exists(as:modconf('CanIf'))"!][!//
  [!LOOP "as:modconf('CanIf')[1]/CanIfInitCfg/*/*[CanIfTxPduRef = $destPduRef]"!][!//
    [!IF "@name != 'CanIfTxPduRef'"!][!VAR "destHnd" = "concat('CanIfConf_CanIfTxPduCfg_', @name)"!][!ENDIF!][!//
  [!ENDLOOP!][!//
  [!IF "$destHnd = $destIdFallback"!][!//
    [!LOOP "as:modconf('CanIf')[1]/CanIfInitCfg/*[CanIfTxPduRef = $destPduRef]"!][!//
      [!IF "@name != 'CanIfTxPduRef'"!][!VAR "destHnd" = "concat('CanIfConf_CanIfTxPduCfg_', @name)"!][!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ELSEIF "$destModName = 'CanTp' and node:exists(as:modconf('CanTp'))"!][!//
  [!LOOP "as:modconf('CanTp')[1]/CanTpConfig/*/*/*[node:exists(CanTpTxNSduRef) and CanTpTxNSduRef = $destPduRef]"!][!//
    [!IF "@name != 'CanTpTxNSduRef'"!][!VAR "destHnd" = "concat('CanTpConf_CanTpTxNSdu_', @name)"!][!ENDIF!][!//
  [!ENDLOOP!][!//
  [!IF "$destHnd = $destIdFallback"!][!//
    [!LOOP "as:modconf('CanTp')[1]/CanTpConfig/*[node:exists(CanTpChannelMode)]/*[node:exists(CanTpTxNSduRef) and CanTpTxNSduRef = $destPduRef]"!][!//
      [!IF "@name != 'CanTpTxNSduRef'"!][!VAR "destHnd" = "concat('CanTpConf_CanTpTxNSdu_', @name)"!][!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ELSEIF "$destModName = 'Com' and node:exists(as:modconf('Com'))"!][!//
  [!LOOP "as:modconf('Com')[1]/ComConfig/*/*[ComPduIdRef = $destPduRef]"!][!//
    [!IF "@name != 'ComPduIdRef'"!][!VAR "destHnd" = "concat('ComConf_ComIPdu_', @name)"!][!ENDIF!][!//
  [!ENDLOOP!][!//
  [!IF "$destHnd = $destIdFallback"!][!//
    [!LOOP "as:modconf('Com')[1]/ComConfig/*[ComPduIdRef = $destPduRef]"!][!//
      [!IF "@name != 'ComPduIdRef'"!][!VAR "destHnd" = "concat('ComConf_ComIPdu_', @name)"!][!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ELSEIF "$destModName = 'Dcm' and node:exists(as:modconf('Dcm'))"!][!//
  [!LOOP "as:modconf('Dcm')[1]/DcmConfigSet/*/*/*/*/*/*/*[node:exists(DcmDslProtocolRxPduRef) and DcmDslProtocolRxPduRef = $destPduRef]"!][!//
    [!IF "@name != 'DcmDslProtocolRxPduRef'"!][!VAR "destHnd" = "concat('DcmConf_DcmDslProtocolRx_', @name)"!][!ENDIF!][!//
  [!ENDLOOP!][!//
  [!IF "$destHnd = $destIdFallback"!][!//
    [!LOOP "as:modconf('Dcm')[1]/DcmConfigSet/*/*/*/*/*/*[node:exists(DcmDslProtocolRxPduRef) and DcmDslProtocolRxPduRef = $destPduRef]"!][!//
      [!IF "@name != 'DcmDslProtocolRxPduRef'"!][!VAR "destHnd" = "concat('DcmConf_DcmDslProtocolRx_', @name)"!][!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!VAR "pduLen" = "8"!][!//
[!VAR "pduLenFound" = "'false'"!][!//
[!IF "node:exists(as:modconf('EcuC'))"!][!//
  [!LOOP "as:modconf('EcuC')[1]/EcucPduCollection/*/*[node:exists(PduLength)]"!][!//
    [!IF "@name != 'PduLength' and contains(concat($destPduRef, '#'), concat('/', @name, '#'))"!][!//
      [!VAR "pduLen" = "num:i(PduLength)"!][!//
      [!VAR "pduLenFound" = "'true'"!][!//
    [!ENDIF!][!//
  [!ENDLOOP!][!//
  [!IF "$pduLenFound = 'false'"!][!//
    [!LOOP "as:modconf('EcuC')[1]/EcucPduCollection/*[node:exists(PduLength)]"!][!//
      [!IF "@name != 'PduLength' and contains(concat($destPduRef, '#'), concat('/', @name, '#'))"!][!//
        [!VAR "pduLen" = "num:i(PduLength)"!][!//
        [!VAR "pduLenFound" = "'true'"!][!//
      [!ENDIF!][!//
    [!ENDLOOP!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!VAR "sep" = "','"!][!IF "$gEmit + 1 >= $totalCount"!][!VAR "sep" = ""!][!ENDIF!][!//
  { [!"$destHnd"!], [!"$dirMac"!], [!"num:i($destModIdx)"!]u, [!"num:i($pduLen)"!]u, [!"num:i($destIdx)"!]u, [!"num:i($destBucketIdx)"!]u }[!"$sep"!]
[!ENDMACRO!][!//
[!VAR "gEmit" = "0"!][!//
[!IF "$hasDeepPaths > 0"!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmGDest", "destIdx" = "num:i($numIfRx + $numTpRx + $numIfTx + $k)", "dirMac" = "'PDUR_TX_DIRECTIONOFRMGDESTROM'", "destBucketIdx" = "$k", "totalCount" = "$numPaths"!][!//
[!VAR "gEmit" = "$gEmit + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmGDest", "destIdx" = "num:i($numIfRx + $numTpRx + $k)", "dirMac" = "'PDUR_TX_DIRECTIONOFRMGDESTROM'", "destBucketIdx" = "$k", "totalCount" = "$numPaths"!][!//
[!VAR "gEmit" = "$gEmit + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmGDest", "destIdx" = "num:i($numIfRx + $k)", "dirMac" = "'PDUR_RX_DIRECTIONOFRMGDESTROM'", "destBucketIdx" = "$k", "totalCount" = "$numPaths"!][!//
[!VAR "gEmit" = "$gEmit + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmGDest", "destIdx" = "num:i($k)", "dirMac" = "'PDUR_RX_DIRECTIONOFRMGDESTROM'", "destBucketIdx" = "$k", "totalCount" = "$numPaths"!][!//
[!VAR "gEmit" = "$gEmit + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!ELSE!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmGDest", "destIdx" = "num:i($numIfRx + $numTpRx + $numIfTx + $k)", "dirMac" = "'PDUR_TX_DIRECTIONOFRMGDESTROM'", "destBucketIdx" = "$k", "totalCount" = "$numPaths"!][!//
[!VAR "gEmit" = "$gEmit + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmGDest", "destIdx" = "num:i($numIfRx + $numTpRx + $k)", "dirMac" = "'PDUR_TX_DIRECTIONOFRMGDESTROM'", "destBucketIdx" = "$k", "totalCount" = "$numPaths"!][!//
[!VAR "gEmit" = "$gEmit + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmGDest", "destIdx" = "num:i($numIfRx + $k)", "dirMac" = "'PDUR_RX_DIRECTIONOFRMGDESTROM'", "destBucketIdx" = "$k", "totalCount" = "$numPaths"!][!//
[!VAR "gEmit" = "$gEmit + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!VAR "k" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmGDest", "destIdx" = "num:i($k)", "dirMac" = "'PDUR_RX_DIRECTIONOFRMGDESTROM'", "destBucketIdx" = "$k", "totalCount" = "$numPaths"!][!//
[!VAR "gEmit" = "$gEmit + 1"!][!VAR "k" = "$k + 1"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
CONST(PduR_RmSrcRomType, PDUR_CONST) PduR_RmSrcRom[[!"num:i($numPaths)"!]] = {
[!/* Ordered matching RmSrcRom buckets: IF_RX, TP_RX, IF_TX, TP_TX */!][!//
[!MACRO "EmitRmSrc", "sIdx", "isTpFlag", "dirMac", "totalCount"!][!//
[!VAR "srcModRef" = "*/PduRSrcPduPduRBswModulesRef"!][!//
[!VAR "srcPduRef" = "*/PduRSrcPduRef"!][!//
[!VAR "srcModIdx" = "0"!][!//
[!VAR "srcModName" = "''"!][!//
[!VAR "mSearch" = "0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!//
  [!IF "contains(concat($srcModRef, '#'), concat('/', @name, '#'))"!][!//
    [!VAR "srcModIdx" = "$mSearch"!][!//
    [!VAR "srcModName" = "@name"!][!//
  [!ENDIF!][!//
  [!VAR "mSearch" = "$mSearch + 1"!][!//
[!ENDLOOP!][!//
[!VAR "srcHnd" = "'0u'"!][!//
[!IF "$dirMac = 'PDUR_TX_DIRECTIONOFRMSRCROM'"!][!//
  [!VAR "srcIdFallback" = "concat(num:i(*/PduRSourcePduHandleId), 'u')"!][!//
  [!VAR "srcHnd" = "$srcIdFallback"!][!//
  [!IF "$srcModName = 'Com' and node:exists(as:modconf('Com'))"!][!//
    [!LOOP "as:modconf('Com')[1]/ComConfig/*/*[ComPduIdRef = $srcPduRef]"!][!//
      [!IF "@name != 'ComPduIdRef'"!][!VAR "srcHnd" = "concat('ComConf_ComIPdu_', @name)"!][!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$srcHnd = $srcIdFallback"!][!//
      [!LOOP "as:modconf('Com')[1]/ComConfig/*[ComPduIdRef = $srcPduRef]"!][!//
        [!IF "@name != 'ComPduIdRef'"!][!VAR "srcHnd" = "concat('ComConf_ComIPdu_', @name)"!][!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDIF!][!//
  [!ELSEIF "$srcModName = 'Dcm' and node:exists(as:modconf('Dcm'))"!][!//
    [!LOOP "as:modconf('Dcm')[1]/DcmConfigSet/*/*/*/*/*/*/*[node:exists(DcmDslProtocolTxPduRef) and DcmDslProtocolTxPduRef = $srcPduRef]"!][!//
      [!IF "@name != 'DcmDslProtocolTxPduRef'"!][!VAR "srcHnd" = "concat('DcmConf_DcmDslProtocolTx_', @name)"!][!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$srcHnd = $srcIdFallback"!][!//
      [!LOOP "as:modconf('Dcm')[1]/DcmConfigSet/*/*/*/*/*/*[node:exists(DcmDslProtocolTxPduRef) and DcmDslProtocolTxPduRef = $srcPduRef]"!][!//
        [!IF "@name != 'DcmDslProtocolTxPduRef'"!][!VAR "srcHnd" = "concat('DcmConf_DcmDslProtocolTx_', @name)"!][!ENDIF!][!//
      [!ENDLOOP!][!//
    [!ENDIF!][!//
  [!ENDIF!][!//
[!ENDIF!][!//
[!VAR "sep" = "','"!][!IF "$sIdx + 1 >= $totalCount"!][!VAR "sep" = ""!][!ENDIF!][!//
  { [!"$isTpFlag"!], [!"$dirMac"!], [!"num:i($srcModIdx)"!]u, [!"num:i($sIdx)"!]u, [!"$srcHnd"!] }[!"$sep"!]
[!ENDMACRO!][!//
[!VAR "sEmit" = "0"!][!//
[!IF "$hasDeepPaths > 0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmSrc", "sIdx" = "$sEmit", "isTpFlag" = "'FALSE'", "dirMac" = "'PDUR_RX_DIRECTIONOFRMSRCROM'", "totalCount" = "$numPaths"!][!//
[!VAR "sEmit" = "$sEmit + 1"!][!//
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmSrc", "sIdx" = "$sEmit", "isTpFlag" = "'TRUE'", "dirMac" = "'PDUR_RX_DIRECTIONOFRMSRCROM'", "totalCount" = "$numPaths"!][!//
[!VAR "sEmit" = "$sEmit + 1"!][!//
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmSrc", "sIdx" = "$sEmit", "isTpFlag" = "'FALSE'", "dirMac" = "'PDUR_TX_DIRECTIONOFRMSRCROM'", "totalCount" = "$numPaths"!][!//
[!VAR "sEmit" = "$sEmit + 1"!][!//
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmSrc", "sIdx" = "$sEmit", "isTpFlag" = "'TRUE'", "dirMac" = "'PDUR_TX_DIRECTIONOFRMSRCROM'", "totalCount" = "$numPaths"!][!//
[!VAR "sEmit" = "$sEmit + 1"!][!//
[!ENDLOOP!][!//
[!ELSE!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmSrc", "sIdx" = "$sEmit", "isTpFlag" = "'FALSE'", "dirMac" = "'PDUR_RX_DIRECTIONOFRMSRCROM'", "totalCount" = "$numPaths"!][!//
[!VAR "sEmit" = "$sEmit + 1"!][!//
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmSrc", "sIdx" = "$sEmit", "isTpFlag" = "'TRUE'", "dirMac" = "'PDUR_RX_DIRECTIONOFRMSRCROM'", "totalCount" = "$numPaths"!][!//
[!VAR "sEmit" = "$sEmit + 1"!][!//
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'COMMUNICATION_INTERFACE' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmSrc", "sIdx" = "$sEmit", "isTpFlag" = "'FALSE'", "dirMac" = "'PDUR_TX_DIRECTIONOFRMSRCROM'", "totalCount" = "$numPaths"!][!//
[!VAR "sEmit" = "$sEmit + 1"!][!//
[!ENDLOOP!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'TRANSMIT'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
[!CALL "EmitRmSrc", "sIdx" = "$sEmit", "isTpFlag" = "'TRUE'", "dirMac" = "'PDUR_TX_DIRECTIONOFRMSRCROM'", "totalCount" = "$numPaths"!][!//
[!VAR "sEmit" = "$sEmit + 1"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"

[!IF "$numTpRx > 0"!][!//
#define PDUR_START_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
CONST(PduR_RxTp2SrcType, PDUR_CONST) PduR_RxTp2Src[[!"num:i($numTpRx)"!]] = {
[!VAR "tpEmit" = "0"!][!//
[!IF "$hasDeepPaths > 0"!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
  [!VAR "sep" = "','"!][!IF "$tpEmit + 1 >= $numTpRx"!][!VAR "sep" = ""!][!ENDIF!][!//
  { [!"num:i($numIfRx + $tpEmit)"!]u }[!"$sep"!]
  [!VAR "tpEmit" = "$tpEmit + 1"!][!//
[!ENDLOOP!][!//
[!ELSE!][!//
[!LOOP "node:order(as:modconf('PduR')[1]/PduRRoutingTables/*/*[PduRRoutingPathCommunicationType = 'TRANSPORT_PROTOCOL' and */PduRSrcPduDirection = 'RECEIVE'], 'num:i(*/PduRSourcePduHandleId)')"!][!//
  [!VAR "sep" = "','"!][!IF "$tpEmit + 1 >= $numTpRx"!][!VAR "sep" = ""!][!ENDIF!][!//
  { [!"num:i($numIfRx + $tpEmit)"!]u }[!"$sep"!]
  [!VAR "tpEmit" = "$tpEmit + 1"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
};
#define PDUR_STOP_SEC_CONST_UNSPECIFIED
#include "PduR_MemMap.h"
[!ENDIF!][!//

#define PDUR_START_SEC_VAR_NO_INIT_8
#include "PduR_MemMap.h"
VAR(PduR_InitializedRamType, PDUR_VAR_NO_INIT) PduR_InitializedRam[1];
#define PDUR_STOP_SEC_VAR_NO_INIT_8
#include "PduR_MemMap.h"

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"
#if(PDUR_USE_INIT_POINTER == STD_ON)
P2CONST(PduR_PBConfigType, PDUR_VAR_CLEARED, PDUR_PBCFG) PduR_ConfigDataPtr = (const PduR_PBConfigType *) NULL_PTR;
#endif
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"
VAR(boolean, PDUR_VAR_NO_INIT) PduR_PreInitialized;
#define PDUR_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "PduR_MemMap.h"

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
static FUNC(void, PDUR_CODE) PduR_SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0(void)
{
  SchM_Enter_PduR_PDUR_EXCLUSIVE_AREA_0();
}

static FUNC(void, PDUR_CODE) PduR_SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0(void)
{
  SchM_Exit_PduR_PDUR_EXCLUSIVE_AREA_0();
}

[!LOOP "node:order(as:modconf('PduR')[1]/*[node:exists(PduRLowerModule)], '@name')"!][!//
[!VAR "mName" = "@name"!][!//
[!IF "PduRUpperModule = 'true'"!][!//
FUNC(Std_ReturnType, PDUR_CODE) PduR_[!"$mName"!]Transmit(PduIdType id, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  return PduR_UpTransmit(id, info);
}

[!IF "node:exists(PduRCancelTransmit) and PduRCancelTransmit = 'true'"!][!//
FUNC(Std_ReturnType, PDUR_CODE) PduR_[!"$mName"!]CancelTransmit(PduIdType id)
{
  return PduR_CancelTransmit(id);
}

[!ENDIF!][!//
[!ENDIF!][!//
[!IF "PduRLowerModule = 'true' and PduRCommunicationInterface = 'true'"!][!//
FUNC(void, PDUR_CODE) PduR_[!"$mName"!]RxIndication(PduIdType RxPduId, P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info)
{
  PduR_LoIfRxIndication(RxPduId, info);
}

[!IF "node:exists(PduRTxConfirmation) and PduRTxConfirmation = 'true'"!][!//
FUNC(void, PDUR_CODE) PduR_[!"$mName"!]TxConfirmation(PduIdType TxPduId)
{
  PduR_LoIfTxConfirmation(TxPduId);
}

[!ENDIF!][!//
[!ENDIF!][!//
[!IF "PduRLowerModule = 'true' and PduRTransportProtocol = 'true'"!][!//
FUNC(BufReq_ReturnType, PDUR_CODE) PduR_[!"$mName"!]StartOfReception(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, PduLengthType TpSduLength, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  return PduR_LoTpStartOfReception(id, info, TpSduLength, bufferSizePtr);
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_[!"$mName"!]CopyRxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) bufferSizePtr)
{
  return PduR_LoTpCopyRxData(id, info, bufferSizePtr);
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_[!"$mName"!]CopyTxData(PduIdType id, P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) info, P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) retry, P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) availableDataPtr)
{
  return PduR_LoTpCopyTxData(id, info, retry, availableDataPtr);
}

FUNC(void, PDUR_CODE) PduR_[!"$mName"!]RxIndication(PduIdType id, Std_ReturnType result)
{
  PduR_LoTpRxIndication(id, result);
}

FUNC(void, PDUR_CODE) PduR_[!"$mName"!]TxConfirmation(PduIdType id, Std_ReturnType result)
{
  PduR_LoTpTxConfirmation(id, result);
}

[!ENDIF!][!//
[!ENDLOOP!][!//
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

[!SELECT "as:modconf('CanIf')[1]"!][!//
[!IF "not(node:exists(CanIfInitCfg))"!][!ERROR "CanIfInitCfg container missing in CanIf configuration"!][!ENDIF!][!//
[!VAR "numCtrls" = "num:i(count(CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*))"!][!//
[!IF "$numCtrls < 1"!][!VAR "numCtrls" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numTrcvs" = "num:i(count(CanIfTrcvDrvCfg/*/CanIfTrcvCfg/*))"!][!//
[!VAR "numBuffers" = "num:i(count(CanIfInitCfg/CanIfBufferCfg/*))"!][!//
[!IF "$numBuffers < 1"!][!VAR "numBuffers" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numHth" = "num:i(count(CanIfInitCfg/CanIfInitHohCfg/*/CanIfHthCfg/*))"!][!//
[!VAR "numHrh" = "num:i(count(CanIfInitCfg/CanIfInitHohCfg/*/CanIfHrhCfg/*))"!][!//
[!VAR "numMailboxes" = "num:i($numHth + $numHrh)"!][!//
[!IF "$numMailboxes < 1"!][!VAR "numMailboxes" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numRxPdus" = "num:i(count(CanIfInitCfg/CanIfRxPduCfg/*))"!][!//
[!VAR "numTxPdus" = "num:i(count(CanIfInitCfg/CanIfTxPduCfg/*))"!][!//
[!IF "$numTxPdus < 1"!][!VAR "numTxPdus" = "num:i(1)"!][!ENDIF!][!//
[!VAR "busOffFct" = "'CanSM_ControllerBusOff'"!][!//
[!IF "node:exists(CanIfDispatchCfg/CanIfDispatchUserCtrlBusOffName)"!][!VAR "busOffFct" = "string:trim(node:value(CanIfDispatchCfg/CanIfDispatchUserCtrlBusOffName))"!][!ENDIF!][!//
[!VAR "ctrlModeFct" = "'CanSM_ControllerModeIndication'"!][!//
[!IF "node:exists(CanIfDispatchCfg/CanIfDispatchUserCtrlModeIndicationName)"!][!VAR "ctrlModeFct" = "string:trim(node:value(CanIfDispatchCfg/CanIfDispatchUserCtrlModeIndicationName))"!][!ENDIF!][!//
[!VAR "trcvModeFct" = "'CanSM_TransceiverModeIndication'"!][!//
[!IF "node:exists(CanIfDispatchCfg/CanIfDispatchUserTrcvModeIndicationName)"!][!VAR "trcvModeFct" = "string:trim(node:value(CanIfDispatchCfg/CanIfDispatchUserTrcvModeIndicationName))"!][!ENDIF!][!//
[!VAR "rxCbkList" = "'|'"!][!//
[!VAR "rxCbkCount" = "num:i(1)"!][!//
[!VAR "hasCanTpRx" = "'false'"!][!//
[!VAR "hasPduRRx" = "'false'"!][!//
[!IF "node:exists(CanIfInitCfg/CanIfRxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfRxPduCfg/*, 'CanIfRxPduId')"!][!//
[!IF "node:exists(CanIfRxPduUserRxIndicationUL)"!][!//
[!IF "node:value(CanIfRxPduUserRxIndicationUL) = 'CAN_TP'"!][!VAR "hasCanTpRx" = "'true'"!][!ENDIF!][!//
[!IF "node:value(CanIfRxPduUserRxIndicationUL) = 'PDUR'"!][!VAR "hasPduRRx" = "'true'"!][!ENDIF!][!//
[!ENDIF!][!//
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
[!VAR "hasCanTpTx" = "'false'"!][!//
[!VAR "hasPduRTx" = "'false'"!][!//
[!IF "node:exists(CanIfInitCfg/CanIfTxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfTxPduCfg/*, 'CanIfTxPduId')"!][!//
[!IF "node:exists(CanIfTxPduUserTxConfirmationUL)"!][!//
[!IF "node:value(CanIfTxPduUserTxConfirmationUL) = 'CAN_TP'"!][!VAR "hasCanTpTx" = "'true'"!][!ENDIF!][!//
[!IF "node:value(CanIfTxPduUserTxConfirmationUL) = 'PDUR'"!][!VAR "hasPduRTx" = "'true'"!][!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:exists(CanIfTxPduUserTxConfirmationName)"!][!//
[!VAR "fn" = "string:trim(node:value(CanIfTxPduUserTxConfirmationName))"!][!//
[!IF "string-length($fn) > 0 and not(contains($txCbkList, concat('|', $fn, '|')))"!][!//
[!VAR "txCbkList" = "concat($txCbkList, $fn, '|')"!][!//
[!VAR "txCbkCount" = "num:i($txCbkCount + 1)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
#define CANIF_LCFG_SOURCE

#include "CanIf_Cfg.h"
[!IF "($hasCanTpRx = 'true') or ($hasCanTpTx = 'true')"!][!//
#include "CanTp_Cfg.h"
#include "CanTp_Cbk.h"
[!ENDIF!][!//
[!IF "($hasPduRRx = 'true') or ($hasPduRTx = 'true')"!][!//
#include "PduR_Cfg.h"
#include "PduR_CanIf.h"
[!ENDIF!][!//
#include "CanSM_Cbk.h"

#define CANIF_START_SEC_APPL_CODE
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#define CANIF_STOP_SEC_APPL_CODE
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_BusOffNotificationFctType, CANIF_CONST) CanIf_BusOffNotificationFctPtr = [!"$busOffFct"!];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_CanIfCtrlId2MappedTxBuffersConfigType, CANIF_CONST) CanIf_CanIfCtrlId2MappedTxBuffersConfig[[!"$numCtrls"!]] = {
[!IF "node:exists(CanIfCtrlDrvCfg/*/CanIfCtrlCfg)"!][!//
[!VAR "cIdx" = "num:i(0)"!][!//
[!LOOP "node:order(CanIfCtrlDrvCfg/*/CanIfCtrlCfg/*, 'CanIfCtrlId')"!][!//
[!VAR "startIdx" = "num:i($cIdx)"!][!//
[!VAR "endIdx" = "num:i($cIdx + 1)"!][!//
  { [!"$endIdx"!]u, [!"$startIdx"!]u }[!IF "not(node:islast())"!],[!ENDIF!]
[!VAR "cIdx" = "num:i($cIdx + 1)"!][!//
[!ENDLOOP!][!//
[!ELSE!][!//
  { 1u, 0u }
[!ENDIF!][!//
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_CtrlModeIndicationFctType, CANIF_CONST) CanIf_CtrlModeIndicationFctPtr = [!"$ctrlModeFct"!];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_MailBoxConfigType, CANIF_CONST) CanIf_MailBoxConfig[[!"$numMailboxes"!]] = {
[!VAR "mbIdx" = "num:i(0)"!][!//
[!LOOP "CanIfInitCfg/CanIfInitHohCfg/*/CanIfHthCfg/*"!][!//
[!VAR "hthPath" = "node:path(.)"!][!//
[!VAR "ctrlStateIdx" = "num:i(0)"!][!//
[!IF "node:exists(CanIfHthCanCtrlIdRef) and (node:refvalid(CanIfHthCanCtrlIdRef) = 'true') and node:exists(node:ref(CanIfHthCanCtrlIdRef)/CanIfCtrlId)"!][!//
[!VAR "ctrlStateIdx" = "num:i(node:value(node:ref(CanIfHthCanCtrlIdRef)/CanIfCtrlId))"!][!//
[!ENDIF!][!//
[!VAR "bufIdx" = "num:i(255)"!][!//
[!VAR "bRun" = "num:i(0)"!][!//
[!LOOP "../../../../CanIfBufferCfg/*"!][!//
[!IF "node:exists(CanIfBufferHthRef)"!][!//
[!VAR "bHth" = "node:value(CanIfBufferHthRef)"!][!//
[!IF "node:refvalid(CanIfBufferHthRef) = 'true'"!][!VAR "bHth" = "node:path(node:ref(CanIfBufferHthRef))"!][!ENDIF!][!//
[!IF "$bHth = $hthPath"!][!VAR "bufIdx" = "$bRun"!][!ENDIF!][!//
[!ENDIF!][!//
[!VAR "bRun" = "num:i($bRun + 1)"!][!//
[!ENDLOOP!][!//
[!VAR "txBufCfg" = "'CANIF_NO_TXBUFFERCFGOFMAILBOXCONFIG'"!][!//
[!VAR "txBufIdxStr" = "'CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG'"!][!//
[!VAR "txBufHandling" = "'CANIF_TXBUFFER_HANDLINGTYPE_NONE'"!][!//
[!IF "$bufIdx < 255"!][!//
[!VAR "txBufCfg" = "'CANIF_TXBUFFERPRIOBYCANIDCONFIG_TXBUFFERCFGOFMAILBOXCONFIG'"!][!//
[!VAR "txBufIdxStr" = "concat($bufIdx, 'u')"!][!//
[!VAR "txBufHandling" = "'CANIF_TXBUFFER_HANDLINGTYPE_PRIOBYCANID'"!][!//
[!ENDIF!][!//
[!VAR "mbIdx" = "num:i($mbIdx + 1)"!][!//
  { [!"$ctrlStateIdx"!]u, 0u, 0u, [!"$txBufCfg"!], [!"$txBufIdxStr"!], [!"$txBufHandling"!], CANIF_TxBasicCANMailbox }[!IF "($mbIdx < $numMailboxes) or ($numHrh > 0)"!],[!ENDIF!]
[!ENDLOOP!][!//
[!VAR "lastRxIdx" = "num:i(0)"!][!//
[!IF "$numRxPdus > 0"!][!VAR "lastRxIdx" = "num:i($numRxPdus - 1)"!][!ENDIF!][!//
[!LOOP "CanIfInitCfg/CanIfInitHohCfg/*/CanIfHrhCfg/*"!][!//
[!VAR "ctrlStateIdx" = "num:i(0)"!][!//
[!IF "node:exists(CanIfHrhCanCtrlIdRef) and (node:refvalid(CanIfHrhCanCtrlIdRef) = 'true') and node:exists(node:ref(CanIfHrhCanCtrlIdRef)/CanIfCtrlId)"!][!//
[!VAR "ctrlStateIdx" = "num:i(node:value(node:ref(CanIfHrhCanCtrlIdRef)/CanIfCtrlId))"!][!//
[!ENDIF!][!//
[!VAR "mbIdx" = "num:i($mbIdx + 1)"!][!//
  { [!"$ctrlStateIdx"!]u, 0u, [!"$lastRxIdx"!]u, CANIF_NO_TXBUFFERCFGOFMAILBOXCONFIG, CANIF_NO_TXBUFFERCFGIDXOFMAILBOXCONFIG, CANIF_TXBUFFER_HANDLINGTYPE_NONE, CANIF_RxBasicCANMailbox }[!IF "$mbIdx < $numMailboxes"!],[!ENDIF!]
[!ENDLOOP!][!//
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_MappedTxBuffersConfigType, CANIF_CONST) CanIf_MappedTxBuffersConfig[[!"$numBuffers"!]] = {
[!IF "node:exists(CanIfInitCfg/CanIfBufferCfg)"!][!//
[!VAR "bRun" = "num:i(0)"!][!//
[!LOOP "CanIfInitCfg/CanIfBufferCfg/*"!][!//
[!VAR "hthIdxMatch" = "num:i($bRun)"!][!//
[!IF "node:exists(CanIfBufferHthRef)"!][!//
[!VAR "targetHth" = "node:value(CanIfBufferHthRef)"!][!//
[!IF "node:refvalid(CanIfBufferHthRef) = 'true'"!][!VAR "targetHth" = "node:path(node:ref(CanIfBufferHthRef))"!][!ENDIF!][!//
[!VAR "hRun" = "num:i(0)"!][!//
[!LOOP "../../CanIfInitHohCfg/*/CanIfHthCfg/*"!][!//
[!IF "node:path(.) = $targetHth"!][!VAR "hthIdxMatch" = "$hRun"!][!ENDIF!][!//
[!VAR "hRun" = "num:i($hRun + 1)"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!VAR "bRun" = "num:i($bRun + 1)"!][!//
  { [!"$hthIdxMatch"!]u }[!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
[!ELSE!][!//
  { 0u }
[!ENDIF!][!//
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_RxIndicationFctListType, CANIF_CONST) CanIf_RxIndicationFctList[[!"$rxCbkCount"!]] = {
  { { (CanIf_SimpleRxIndicationFctType)NULL_PTR }, CanIf_SimpleRxIndicationLayout }[!//
[!LOOP "text:split($rxCbkList, '|')"!][!//
[!IF "string-length(string:trim(.)) > 0"!][!//
,
  { { (CanIf_SimpleRxIndicationFctType)[!"string:trim(.)"!] }, CanIf_AdvancedRxIndicationLayout }[!//
[!ENDIF!][!//
[!ENDLOOP!]
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!IF "$numRxPdus > 0"!][!//
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_RxPduConfigType, CANIF_CONST) CanIf_RxPduConfig[[!"$numRxPdus"!]] = {
[!VAR "rxRowIdx" = "num:i(0)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfRxPduCfg/*, 'CanIfRxPduId')"!][!//
[!VAR "rxMask" = "'0x000007FFu'"!][!//
[!IF "$rxRowIdx = 0"!][!VAR "rxMask" = "'0x400007FFu'"!][!ENDIF!][!//
[!VAR "canIdHex" = "concat('0x', text:toupper(substring(num:inttohex(num:i(node:value(CanIfRxPduCanId)), 4), 3)), 'u')"!][!//
[!VAR "dlcVal" = "num:i(node:value(CanIfRxPduDlc))"!][!//
[!VAR "cbkName" = "string:trim(node:value(CanIfRxPduUserRxIndicationName))"!][!//
[!VAR "beforeCbk" = "substring-before($rxCbkList, concat('|', $cbkName, '|'))"!][!//
[!VAR "cbkIdx" = "num:i(string:length($beforeCbk) - string:length(translate($beforeCbk, '|', '')) + 1)"!][!//
[!VAR "ul" = "'PDUR'"!][!//
[!IF "node:exists(CanIfRxPduUserRxIndicationUL)"!][!VAR "ul" = "string:trim(node:value(CanIfRxPduUserRxIndicationUL))"!][!ENDIF!][!//
[!VAR "upperIdSym" = "concat(num:i(node:value(CanIfRxPduId)), 'u')"!][!//
[!IF "node:exists(CanIfRxPduRef)"!][!//
[!VAR "ecucPduPath" = "node:value(CanIfRxPduRef)"!][!//
[!IF "node:refvalid(CanIfRxPduRef) = 'true'"!][!VAR "ecucPduPath" = "node:path(node:ref(CanIfRxPduRef))"!][!ENDIF!][!//
[!IF "($ul = 'CAN_TP') and node:exists(as:modconf('CanTp')[1]/CanTpConfig)"!][!//
[!LOOP "as:modconf('CanTp')[1]/CanTpConfig/*/*/*"!][!//
[!IF "node:exists(CanTpRxNPduRef)"!][!//
[!VAR "tpRef" = "node:value(CanTpRxNPduRef)"!][!//
[!IF "node:refvalid(CanTpRxNPduRef) = 'true'"!][!VAR "tpRef" = "node:path(node:ref(CanTpRxNPduRef))"!][!ENDIF!][!//
[!IF "$tpRef = $ecucPduPath"!][!VAR "upperIdSym" = "concat('CanTpConf_CanTpRxNPdu_', node:name(.))"!][!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ELSEIF "($ul = 'PDUR') and node:exists(as:modconf('PduR')[1]/PduRRoutingTables)"!][!//
[!LOOP "as:modconf('PduR')[1]/PduRRoutingTables/*/*/*"!][!//
[!IF "node:exists(PduRSrcPduRef)"!][!//
[!VAR "prRef" = "node:value(PduRSrcPduRef)"!][!//
[!IF "node:refvalid(PduRSrcPduRef) = 'true'"!][!VAR "prRef" = "node:path(node:ref(PduRSrcPduRef))"!][!ENDIF!][!//
[!IF "$prRef = $ecucPduPath"!][!VAR "upperIdSym" = "concat('PduRConf_PduRSrcPdu_', node:name(.))"!][!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "rxRowIdx" = "num:i($rxRowIdx + 1)"!][!//
  { [!"$rxMask"!], [!"$canIdHex"!], [!"$upperIdSym"!], [!"$cbkIdx"!]u, [!"$dlcVal"!]u }[!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!ENDIF!][!//
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_TrcvModeIndicationFctType, CANIF_CONST) CanIf_TrcvModeIndicationFctPtr = [!"$trcvModeFct"!];
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!IF "$numTrcvs > 0"!][!//
#define CANIF_START_SEC_CONST_8BIT
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_TrcvToCtrlMapType, CANIF_CONST) CanIf_TrcvToCtrlMap[[!"$numTrcvs"!]] = {
[!VAR "tIdx" = "num:i(0)"!][!//
[!LOOP "node:order(CanIfTrcvDrvCfg/*/CanIfTrcvCfg/*, 'CanIfTrcvId')"!][!//
[!VAR "mappedCtrl" = "num:i(0)"!][!//
[!VAR "tIdx" = "num:i($tIdx + 1)"!][!//
  [!"$mappedCtrl"!]u[!IF "$tIdx < $numTrcvs"!],[!ENDIF!]
[!ENDLOOP!][!//
};
#define CANIF_STOP_SEC_CONST_8BIT
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!ENDIF!][!//
#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_TxBufferPrioByCanIdConfigType, CANIF_CONST) CanIf_TxBufferPrioByCanIdConfig[[!"$numBuffers"!]] = {
[!IF "node:exists(CanIfInitCfg/CanIfBufferCfg)"!][!//
[!VAR "bRun" = "num:i(0)"!][!//
[!LOOP "CanIfInitCfg/CanIfBufferCfg/*"!][!//
  { 0u, [!"$bRun"!]u, [!"num:i($bRun + 1)"!]u, [!"$bRun"!]u }[!IF "not(node:islast())"!],[!ENDIF!]
[!VAR "bRun" = "num:i($bRun + 1)"!][!//
[!ENDLOOP!][!//
[!ELSE!][!//
  { 0u, 0u, 1u, 0u }
[!ENDIF!][!//
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_TxConfirmationFctType, CANIF_CONST) CanIf_TxConfirmationFctList[[!"$txCbkCount"!]] = {
  (CanIf_TxConfirmationFctType)NULL_PTR[!//
[!LOOP "text:split($txCbkList, '|')"!][!//
[!IF "string-length(string:trim(.)) > 0"!][!//
,
  [!"string:trim(.)"!][!//
[!ENDIF!][!//
[!ENDLOOP!]
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_TxPduConfigType, CANIF_CONST) CanIf_TxPduConfig[[!"$numTxPdus"!]] = {
[!IF "node:exists(CanIfInitCfg/CanIfTxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfTxPduCfg/*, 'CanIfTxPduId')"!][!//
[!VAR "canIdHex" = "concat('0x', text:toupper(substring(num:inttohex(num:i(node:value(CanIfTxPduCanId)), 4), 3)), 'u')"!][!//
[!VAR "dlcVal" = "num:i(node:value(CanIfTxPduDlc))"!][!//
[!VAR "truncVal" = "'FALSE'"!][!//
[!IF "node:exists(CanIfTxPduTruncation) and node:value(CanIfTxPduTruncation) = 'true'"!][!VAR "truncVal" = "'TRUE'"!][!ENDIF!][!//
[!VAR "cbkName" = "string:trim(node:value(CanIfTxPduUserTxConfirmationName))"!][!//
[!VAR "beforeCbk" = "substring-before($txCbkList, concat('|', $cbkName, '|'))"!][!//
[!VAR "cbkIdx" = "num:i(string:length($beforeCbk) - string:length(translate($beforeCbk, '|', '')) + 1)"!][!//
[!VAR "ctrlIdx" = "num:i(0)"!][!//
[!VAR "mbIdx" = "num:i(0)"!][!//
[!IF "node:exists(CanIfTxPduBufferRef) and (node:refvalid(CanIfTxPduBufferRef) = 'true')"!][!//
[!IF "node:exists(node:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef)"!][!//
[!VAR "targetHth" = "node:value(node:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef)"!][!//
[!IF "node:refvalid(node:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef) = 'true'"!][!//
[!VAR "targetHth" = "node:path(node:ref(node:ref(CanIfTxPduBufferRef)/CanIfBufferHthRef))"!][!//
[!ENDIF!][!//
[!VAR "hRun" = "num:i(0)"!][!//
[!LOOP "../../CanIfInitHohCfg/*/CanIfHthCfg/*"!][!//
[!IF "node:path(.) = $targetHth"!][!//
[!VAR "mbIdx" = "$hRun"!][!//
[!IF "node:exists(CanIfHthCanCtrlIdRef) and (node:refvalid(CanIfHthCanCtrlIdRef) = 'true') and node:exists(node:ref(CanIfHthCanCtrlIdRef)/CanIfCtrlId)"!][!//
[!VAR "ctrlIdx" = "num:i(node:value(node:ref(CanIfHthCanCtrlIdRef)/CanIfCtrlId))"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "hRun" = "num:i($hRun + 1)"!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!VAR "ul" = "'PDUR'"!][!//
[!IF "node:exists(CanIfTxPduUserTxConfirmationUL)"!][!VAR "ul" = "string:trim(node:value(CanIfTxPduUserTxConfirmationUL))"!][!ENDIF!][!//
[!VAR "upperIdSym" = "concat(num:i(node:value(CanIfTxPduId)), 'u')"!][!//
[!IF "node:exists(CanIfTxPduRef)"!][!//
[!VAR "ecucPduPath" = "node:value(CanIfTxPduRef)"!][!//
[!IF "node:refvalid(CanIfTxPduRef) = 'true'"!][!VAR "ecucPduPath" = "node:path(node:ref(CanIfTxPduRef))"!][!ENDIF!][!//
[!IF "($ul = 'CAN_TP') and node:exists(as:modconf('CanTp')[1]/CanTpConfig)"!][!//
[!LOOP "as:modconf('CanTp')[1]/CanTpConfig/*/*/*"!][!//
[!IF "node:exists(CanTpTxFcNPduRef)"!][!//
[!VAR "tpRef" = "node:value(CanTpTxFcNPduRef)"!][!//
[!IF "node:refvalid(CanTpTxFcNPduRef) = 'true'"!][!VAR "tpRef" = "node:path(node:ref(CanTpTxFcNPduRef))"!][!ENDIF!][!//
[!IF "$tpRef = $ecucPduPath"!][!VAR "upperIdSym" = "concat('CanTpConf_CanTpTxFcNPdu_', node:name(.))"!][!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "$upperIdSym = concat(num:i(node:value(CanIfTxPduId)), 'u')"!][!//
[!LOOP "as:modconf('CanTp')[1]/CanTpConfig/*/*/*"!][!//
[!IF "node:exists(CanTpTxNPduRef)"!][!//
[!VAR "tpRef" = "node:value(CanTpTxNPduRef)"!][!//
[!IF "node:refvalid(CanTpTxNPduRef) = 'true'"!][!VAR "tpRef" = "node:path(node:ref(CanTpTxNPduRef))"!][!ENDIF!][!//
[!IF "$tpRef = $ecucPduPath"!][!VAR "upperIdSym" = "concat('CanTpConf_CanTpTxNPdu_', node:name(.))"!][!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ELSEIF "($ul = 'PDUR') and node:exists(as:modconf('PduR')[1]/PduRRoutingTables)"!][!//
[!LOOP "as:modconf('PduR')[1]/PduRRoutingTables/*/*/*"!][!//
[!IF "node:exists(PduRDestPduRef)"!][!//
[!VAR "prRef" = "node:value(PduRDestPduRef)"!][!//
[!IF "node:refvalid(PduRDestPduRef) = 'true'"!][!VAR "prRef" = "node:path(node:ref(PduRDestPduRef))"!][!ENDIF!][!//
[!IF "$prRef = $ecucPduPath"!][!VAR "upperIdSym" = "concat('PduRConf_PduRDestPdu_', node:name(.))"!][!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDIF!][!//
  { [!"$canIdHex"!], [!"$upperIdSym"!], [!"$truncVal"!], [!"$ctrlIdx"!]u, [!"$mbIdx"!]u, [!"$cbkIdx"!]u, [!"$dlcVal"!]u }[!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
[!ELSE!][!//
  { 0x0000u, 0u, FALSE, 0u, 0u, 0u, 8u }
[!ENDIF!][!//
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanIf_TxPduQueueIndexType, CANIF_CONST) CanIf_TxPduQueueIndex[[!"$numTxPdus"!]] = {
[!VAR "qIdx" = "num:i(0)"!][!//
[!IF "node:exists(CanIfInitCfg/CanIfTxPduCfg)"!][!//
[!LOOP "node:order(CanIfInitCfg/CanIfTxPduCfg/*, 'CanIfTxPduId')"!][!//
  { [!"$qIdx"!]u }[!IF "not(node:islast())"!],[!ENDIF!]
[!VAR "qIdx" = "num:i($qIdx + 1)"!][!//
[!ENDLOOP!][!//
[!ELSE!][!//
  { 0u }
[!ENDIF!][!//
};
#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(CanIf_CtrlStatesUType, CANIF_VAR_NOINIT) CanIf_CtrlStates;
#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(CanIf_TxBufferPrioByCanIdBaseUType, CANIF_VAR_NOINIT) CanIf_TxBufferPrioByCanIdBase;
#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(CanIf_TxQueueUType, CANIF_VAR_NOINIT) CanIf_TxQueue;
#define CANIF_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define CANIF_START_SEC_VAR_NOINIT_32BIT
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(CanIf_TxQueueFlagsUType, CANIF_VAR_NOINIT) CanIf_TxQueueFlags;
#define CANIF_STOP_SEC_VAR_NOINIT_32BIT
#include "CanIf_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!ENDSELECT!]

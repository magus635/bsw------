[!SELECT "as:modconf('CanSM')[1]"!][!//
[!IF "not(node:exists(CanSMGeneral))"!][!ERROR "CanSMGeneral container is missing in CanSM configuration"!][!ENDIF!][!//
[!VAR "mainPeriod" = "0.01"!][!//
[!IF "node:exists(CanSMGeneral/CanSMMainFunctionTimePeriod) and (number(node:value(CanSMGeneral/CanSMMainFunctionTimePeriod)) > 0)"!][!//
[!VAR "mainPeriod" = "number(node:value(CanSMGeneral/CanSMMainFunctionTimePeriod))"!][!//
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
[!IF "node:exists(CanSMConfiguration/CanSMManagerNetwork)"!][!//
[!LOOP "CanSMConfiguration/CanSMManagerNetwork/*"!][!//
[!IF "node:exists(CanSMBorTxConfirmationPolling) and (node:value(CanSMBorTxConfirmationPolling) = 'true')"!][!//
[!VAR "anyPolling" = "'true'"!][!//
[!ENDIF!][!//
[!IF "node:exists(CanSMTransceiverId) and (node:refvalid(CanSMTransceiverId) = 'true')"!][!//
[!VAR "anyTrcv" = "'true'"!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
/**********************************************************************************************************************
 *  COPYRIGHT
 *  -------------------------------------------------------------------------------------------------------------------
 *  \verbatim
 *  This file is part of the AUTOSAR BSW Configurator generated output.
 *  \endverbatim
 *  -------------------------------------------------------------------------------------------------------------------
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: CanSM_Lcfg.c
 *            Module: CanSM
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *********************************************************************************************************************/

#define CANSM_LCFG_C

/* -----------------------------------------------------------------------------
    &&&~ Includes
 ----------------------------------------------------------------------------- */

#include "CanSM_EcuM.h"

[!IF "$effChannels > 1"!][!//
#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(CanSM_ChannelConfigType, CANSM_CONST) CanSM_ChannelConfig[[!"$effChannels"!]] = {
[!VAR "chIdx" = "num:i(0)"!][!//
[!LOOP "CanSMConfiguration/CanSMManagerNetwork/*"!][!//
[!VAR "chBorCnt" = "num:i(5)"!][!//
[!IF "node:exists(CanSMBorCounterL1ToL2)"!][!VAR "chBorCnt" = "num:i(node:value(CanSMBorCounterL1ToL2))"!][!ENDIF!][!//
[!VAR "chBorL1" = "num:i(100)"!][!//
[!IF "node:exists(CanSMBorTimeL1)"!][!VAR "chBorL1" = "num:i(round(number(node:value(CanSMBorTimeL1)) div $mainPeriod))"!][!ENDIF!][!//
[!VAR "chBorL2" = "num:i(300)"!][!//
[!IF "node:exists(CanSMBorTimeL2)"!][!VAR "chBorL2" = "num:i(round(number(node:value(CanSMBorTimeL2)) div $mainPeriod))"!][!ENDIF!][!//
[!VAR "chBorTx" = "num:i(500)"!][!//
[!IF "node:exists(CanSMBorTimeTxEnsured)"!][!VAR "chBorTx" = "num:i(round(number(node:value(CanSMBorTimeTxEnsured)) div $mainPeriod))"!][!ENDIF!][!//
[!VAR "chPoll" = "'FALSE'"!][!//
[!IF "node:exists(CanSMBorTxConfirmationPolling) and (node:value(CanSMBorTxConfirmationPolling) = 'true')"!][!VAR "chPoll" = "'TRUE'"!][!ENDIF!][!//
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
[!VAR "chHasTrcv" = "'FALSE'"!][!//
[!VAR "chTrcvId" = "num:i(0)"!][!//
[!IF "node:exists(CanSMTransceiverId) and (node:refvalid(CanSMTransceiverId) = 'true')"!][!//
[!VAR "chHasTrcv" = "'TRUE'"!][!//
[!IF "node:exists(node:ref(CanSMTransceiverId)/CanIfTrcvId)"!][!//
[!VAR "chTrcvId" = "num:i(node:value(node:ref(CanSMTransceiverId)/CanIfTrcvId))"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
  { [!"$chBorL2"!]u, [!"$chBorTx"!]u, [!"$chBorCnt"!]u, [!"$chBorL1"!]u, [!IF "$anyPolling = 'true'"!][!"$chPoll"!], [!ENDIF!][!"$chCtrlId"!]u, 0xFFu, 0xFFu, [!"$chNetHandle"!]u[!IF "$anyTrcv = 'true'"!], [!"$chTrcvId"!]u, [!"$chHasTrcv"!][!ENDIF!] }[!IF "not(node:islast())"!],[!ENDIF!]
[!VAR "chIdx" = "num:i($chIdx + 1)"!][!//
[!ENDLOOP!][!//
};
#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!ENDIF!][!//
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
#define CANSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanSM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(CanSM_ChannelVarRecordType, CANSM_VAR_NO_INIT) CanSM_ChannelVarRecord[[!"$effChannels"!]];
#define CANSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "CanSM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!ENDSELECT!]

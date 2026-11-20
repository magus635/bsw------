[!SELECT "as:modconf('Det')[1]"!][!//
[!IF "not(node:exists(DetGeneral))"!][!ERROR "DetGeneral container is missing in Det configuration"!][!ENDIF!][!//
[!VAR "errorHookCount" = "num:i(0)"!][!//
[!VAR "runtimeCalloutCount" = "num:i(0)"!][!//
[!VAR "transientCalloutCount" = "num:i(0)"!][!//
[!IF "node:exists(DetNotification)"!][!//
[!VAR "errorHookCount" = "num:i(count(DetNotification/DetErrorHook/*))"!][!//
[!VAR "runtimeCalloutCount" = "num:i(count(DetNotification/DetReportRuntimeErrorCallout/*))"!][!//
[!VAR "transientCalloutCount" = "num:i(count(DetNotification/DetReportTransientFaultCallout/*))"!][!//
[!ENDIF!][!//
/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *              File: Det_Cfg.c
 *            Module: Det
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *********************************************************************************************************************/

#define DET_CFG_SOURCE

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Det.h"


/**********************************************************************************************************************
 * GLOBAL DATA
 *********************************************************************************************************************/
/**********************************************************************************************************************
  CONFIGURATION CLASS: PRE_COMPILE
  SECTION: GLOBAL DATA
**********************************************************************************************************************/
[!IF "($errorHookCount > 0) or ($runtimeCalloutCount > 0) or ($transientCalloutCount > 0)"!][!//
#define DET_START_SEC_CONST_UNSPECIFIED
#include "Det_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!IF "$errorHookCount > 0"!][!//
CONST(Det_CalloutTableType, DET_CONST) Det_ErrorHookTable[[!"$errorHookCount"!]] = {
[!LOOP "DetNotification/DetErrorHook/*"!][!//
  [!"string:trim(node:value(.))"!][!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
};
[!ENDIF!][!//
[!IF "$runtimeCalloutCount > 0"!][!//
CONST(Det_CalloutTableType, DET_CONST) Det_RuntimeErrorCalloutTable[[!"$runtimeCalloutCount"!]] = {
[!LOOP "DetNotification/DetReportRuntimeErrorCallout/*"!][!//
  [!"string:trim(node:value(.))"!][!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
};
[!ENDIF!][!//
[!IF "$transientCalloutCount > 0"!][!//
CONST(Det_CalloutTableType, DET_CONST) Det_TransientFaultCalloutTable[[!"$transientCalloutCount"!]] = {
[!LOOP "DetNotification/DetReportTransientFaultCallout/*"!][!//
  [!"string:trim(node:value(.))"!][!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
};
[!ENDIF!][!//

#define DET_STOP_SEC_CONST_UNSPECIFIED
#include "Det_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!ENDIF!][!//

[!ENDSELECT!]

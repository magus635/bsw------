[!SELECT "as:modconf('EcuM')[1]"!][!//
[!IF "not(node:exists(EcuMConfiguration))"!][!ERROR "EcuMConfiguration container is missing in EcuM configuration"!][!ENDIF!][!//
[!VAR "partCount" = "num:i(count(EcuMConfiguration/EcuMFlexConfiguration/EcuMPartitionRef/*))"!][!//
[!VAR "wkCount" = "num:i(count(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource/*))"!][!//
[!VAR "effWkCount" = "$wkCount"!][!//
[!IF "$effWkCount = 0"!][!VAR "effWkCount" = "num:i(1)"!][!ENDIF!][!//
[!VAR "comMRefCount" = "num:i(0)"!][!//
[!IF "node:exists(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource)"!][!//
[!LOOP "EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource/*"!][!//
[!IF "node:exists(EcuMComMChannelRef) and (node:refvalid(EcuMComMChannelRef) = 'true')"!][!//
[!VAR "comMRefCount" = "num:i($comMRefCount + 1)"!][!//
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
 *              File: EcuM_Cfg.c
 *            Module: EcuM
 *         Generator: AUTOSAR BSW Configurator (EB Template)
 *********************************************************************************************************************/

#include "EcuM_Cbk.h"

#define ECUM_PRIVATE_CFG_PARTLY_INCLUDE
#include "EcuM_PrivateCfg.h"
#undef ECUM_PRIVATE_CFG_PARTLY_INCLUDE

#if((ECUM_CHANNELOFCOMMCHANNELREFS == STD_ON) || (ECUM_PNCOFCOMMPNCREFS == STD_ON) || (ECUM_SUPPORT_COMM == STD_ON))
#include "ComM.h"
#endif

#if !defined (ECUM_LOCAL)
# define ECUM_LOCAL static
#endif

#if !defined (ECUM_LOCAL_INLINE)
# define ECUM_LOCAL_INLINE LOCAL_INLINE
#endif


/**********************************************************************************************************************
 *  LOCAL DATA PROTOTYPES
 *********************************************************************************************************************/
[!IF "$partCount = 0"!][!//
#define ECUM_START_SEC_VAR_PARTITION_SYSTEMAPPLICATION_OSCORE0_NOCACHE_NO_INIT_32
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
ECUM_LOCAL VAR(EcuM_CoreStatusType, ECUM_VAR_NO_INIT) EcuM_CoreStatus_SystemApplication_OsCore0;
#define ECUM_STOP_SEC_VAR_PARTITION_SYSTEMAPPLICATION_OSCORE0_NOCACHE_NO_INIT_32
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!ELSE!][!//
[!LOOP "EcuMConfiguration/EcuMFlexConfiguration/EcuMPartitionRef/*"!][!//
[!VAR "partPath" = "node:value(.)"!][!//
[!VAR "appName" = "'SystemApplication_OsCore0'"!][!//
[!IF "node:refvalid(.) = 'true'"!][!//
[!VAR "partPath" = "node:path(node:ref(.))"!][!//
[!VAR "appName" = "node:name(node:ref(.))"!][!//
[!ELSE!][!//
[!VAR "pParts" = "text:split($partPath, '/')"!][!//
[!IF "count($pParts) > 0"!][!VAR "appName" = "$pParts[position() = count($pParts)]"!][!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:exists(as:modconf('Os')[1]/OsApplication)"!][!//
[!LOOP "as:modconf('Os')[1]/OsApplication/*"!][!//
[!IF "node:exists(OsAppEcucPartitionRef)"!][!//
[!VAR "osPartPath" = "node:value(OsAppEcucPartitionRef)"!][!//
[!IF "node:refvalid(OsAppEcucPartitionRef) = 'true'"!][!//
[!VAR "osPartPath" = "node:path(node:ref(OsAppEcucPartitionRef))"!][!//
[!ENDIF!][!//
[!IF "$osPartPath = $partPath"!][!//
[!VAR "appName" = "node:name(.)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!VAR "appUpper" = "text:toupper($appName)"!][!//
#define ECUM_START_SEC_VAR_PARTITION_[!"$appUpper"!]_NOCACHE_NO_INIT_32
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
ECUM_LOCAL VAR(EcuM_CoreStatusType, ECUM_VAR_NO_INIT) EcuM_CoreStatus_[!"$appName"!];
#define ECUM_STOP_SEC_VAR_PARTITION_[!"$appUpper"!]_NOCACHE_NO_INIT_32
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!ENDLOOP!][!//
[!ENDIF!][!//


/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
[!IF "$comMRefCount > 1"!][!//
#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(EcuM_ComMChannelRefsType, ECUM_CONST) EcuM_ComMChannelRefs[[!"$comMRefCount"!]] = {
[!VAR "cmIdx" = "num:i(0)"!][!//
[!LOOP "node:order(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource/*, 'EcuMWakeupSourceId')"!][!//
[!IF "node:exists(EcuMComMChannelRef) and (node:refvalid(EcuMComMChannelRef) = 'true')"!][!//
[!VAR "cmIdx" = "num:i($cmIdx + 1)"!][!//
  { ComMConf_ComMChannel_[!"node:name(node:ref(EcuMComMChannelRef))"!] }[!IF "$cmIdx < $comMRefCount"!],[!ENDIF!]
[!ENDIF!][!//
[!ENDLOOP!][!//
};
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

[!ENDIF!][!//
#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!IF "$partCount = 0"!][!//
CONST(EcuM_CoreStatusArrayType, ECUM_CONST) EcuM_CoreStatus[1] = {
   &EcuM_CoreStatus_SystemApplication_OsCore0
};
[!ELSE!][!//
CONST(EcuM_CoreStatusArrayType, ECUM_CONST) EcuM_CoreStatus[[!"$partCount"!]] = {
[!LOOP "EcuMConfiguration/EcuMFlexConfiguration/EcuMPartitionRef/*"!][!//
[!VAR "partPath" = "node:value(.)"!][!//
[!VAR "appName" = "'SystemApplication_OsCore0'"!][!//
[!IF "node:refvalid(.) = 'true'"!][!//
[!VAR "partPath" = "node:path(node:ref(.))"!][!//
[!VAR "appName" = "node:name(node:ref(.))"!][!//
[!ELSE!][!//
[!VAR "pParts" = "text:split($partPath, '/')"!][!//
[!IF "count($pParts) > 0"!][!VAR "appName" = "$pParts[position() = count($pParts)]"!][!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:exists(as:modconf('Os')[1]/OsApplication)"!][!//
[!LOOP "as:modconf('Os')[1]/OsApplication/*"!][!//
[!IF "node:exists(OsAppEcucPartitionRef)"!][!//
[!VAR "osPartPath" = "node:value(OsAppEcucPartitionRef)"!][!//
[!IF "node:refvalid(OsAppEcucPartitionRef) = 'true'"!][!//
[!VAR "osPartPath" = "node:path(node:ref(OsAppEcucPartitionRef))"!][!//
[!ENDIF!][!//
[!IF "$osPartPath = $partPath"!][!//
[!VAR "appName" = "node:name(.)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
   &EcuM_CoreStatus_[!"$appName"!][!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
};
[!ENDIF!][!//
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(EcuM_DriverInitOneType, ECUM_CONST) EcuM_DriverInitOne[1] = {
  { EcuM_AL_DriverInitOne }
};
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!IF "$partCount = 0"!][!//
CONST(EcuM_PartitionDataType, ECUM_CONST) EcuM_PartitionData[1] = {
  { SystemApplication_OsCore0 }
};
[!ELSE!][!//
CONST(EcuM_PartitionDataType, ECUM_CONST) EcuM_PartitionData[[!"$partCount"!]] = {
[!LOOP "node:order(EcuMConfiguration/EcuMFlexConfiguration/EcuMPartitionRef/*, 'node:value(.)')"!][!//
[!VAR "partPath" = "node:value(.)"!][!//
[!VAR "appName" = "'SystemApplication_OsCore0'"!][!//
[!IF "node:refvalid(.) = 'true'"!][!//
[!VAR "partPath" = "node:path(node:ref(.))"!][!//
[!VAR "appName" = "node:name(node:ref(.))"!][!//
[!ELSE!][!//
[!VAR "pParts" = "text:split($partPath, '/')"!][!//
[!IF "count($pParts) > 0"!][!VAR "appName" = "$pParts[position() = count($pParts)]"!][!ENDIF!][!//
[!ENDIF!][!//
[!IF "node:exists(as:modconf('Os')[1]/OsApplication)"!][!//
[!LOOP "as:modconf('Os')[1]/OsApplication/*"!][!//
[!IF "node:exists(OsAppEcucPartitionRef)"!][!//
[!VAR "osPartPath" = "node:value(OsAppEcucPartitionRef)"!][!//
[!IF "node:refvalid(OsAppEcucPartitionRef) = 'true'"!][!//
[!VAR "osPartPath" = "node:path(node:ref(OsAppEcucPartitionRef))"!][!//
[!ENDIF!][!//
[!IF "$osPartPath = $partPath"!][!//
[!VAR "appName" = "node:name(.)"!][!//
[!ENDIF!][!//
[!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
  { [!"$appName"!] }[!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
};
[!ENDIF!][!//
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!IF "$wkCount = 0"!][!//
CONST(EcuM_WakeupSourceListType, ECUM_CONST) EcuM_WakeupSourceList[1] = {
  { 0u }
};
[!ELSE!][!//
CONST(EcuM_WakeupSourceListType, ECUM_CONST) EcuM_WakeupSourceList[[!"$wkCount"!]] = {
[!VAR "cmRunIdx" = "num:i(0)"!][!//
[!LOOP "node:order(EcuMConfiguration/EcuMCommonConfiguration/EcuMWakeupSource/*, 'EcuMWakeupSourceId')"!][!//
[!IF "$comMRefCount > 0"!][!//
[!IF "node:exists(EcuMComMChannelRef) and (node:refvalid(EcuMComMChannelRef) = 'true')"!][!//
[!VAR "endIdx" = "num:i($cmRunIdx + 1)"!][!//
  { [!"$endIdx"!]u, [!"$cmRunIdx"!]u }[!IF "not(node:islast())"!],[!ENDIF!]
[!VAR "cmRunIdx" = "$endIdx"!][!//
[!ELSE!][!//
  { ECUM_NO_COMMCHANNELREFSENDIDXOFWAKEUPSOURCELIST, ECUM_NO_COMMCHANNELREFSSTARTIDXOFWAKEUPSOURCELIST }[!IF "not(node:islast())"!],[!ENDIF!]
[!ENDIF!][!//
[!ELSE!][!//
  { 0u }[!IF "not(node:islast())"!],[!ENDIF!]
[!ENDIF!][!//
[!ENDLOOP!][!//
};
[!ENDIF!][!//
#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define ECUM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(EcuM_StateType, ECUM_VAR_NO_INIT) EcuM_ModuleState;
#define ECUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "EcuM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!ENDSELECT!]

[!SELECT "as:modconf('ComM')[1]"!][!//
[!IF "not(node:exists(ComMConfigSet))"!][!ERROR "ComMConfigSet container missing in ComM configuration"!][!ENDIF!][!//
[!VAR "numChannels" = "num:i(count(ComMConfigSet/ComMChannel/*))"!][!//
[!IF "$numChannels < 1"!][!VAR "numChannels" = "num:i(1)"!][!ENDIF!][!//
[!VAR "numUsers" = "num:i(count(ComMConfigSet/ComMUser/*))"!][!//
[!VAR "effUsers" = "$numUsers"!][!//
[!IF "$effUsers < 1"!][!VAR "effUsers" = "num:i(1)"!][!ENDIF!][!//
[!VAR "ecuGroupClassHex" = "'0x03'"!][!//
[!IF "node:exists(ComMGeneral/ComMEcuGroupClassification)"!][!//
[!VAR "ecuGroupClassHex" = "num:inttohex(num:i(node:value(ComMGeneral/ComMEcuGroupClassification)), 2)"!][!//
[!ENDIF!][!//
#define CCL_ASR_COMM_LCFG_MODULE

#include "ComM_Private_Cfg.h"
#include "CanSM_ComM.h"
#include "CanSM.h"
#include "Det.h"
#include "Rte_ComM.h"
# include "ComM_Lcfg.h"

#if defined( COMM_LOCAL )
#else
# define COMM_LOCAL static
#endif

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(ComM_ChannelType, COMM_CONST) ComM_Channel[[!"$numChannels"!]] = {
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!//
[!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
  { CanSM_GetCurrentComMode, CanSM_RequestComMode }[!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
[!ELSE!][!//
  { CanSM_GetCurrentComMode, CanSM_RequestComMode }
[!ENDIF!][!//
};
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(ComM_PartitionIdentifiersType, COMM_CONST) ComM_PartitionIdentifiers[1] = {
  { COMM_SINGLEPARTITION, 0u }
};
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(ComM_UserType, COMM_CONST) ComM_User[[!"$effUsers"!]] = {
[!IF "node:exists(ComMConfigSet/ComMUser)"!][!//
[!LOOP "node:order(ComMConfigSet/ComMUser/*, 'ComMUserIdentifier')"!][!//
  { FALSE }[!IF "not(node:islast())"!],[!ENDIF!]
[!ENDLOOP!][!//
[!ELSE!][!//
  { FALSE }
[!ENDIF!][!//
};
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(ComM_ActiveComModeUType, COMM_VAR_NO_INIT) ComM_ActiveComMode;
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(ComM_BusComModeReqUType, COMM_VAR_NO_INIT) ComM_BusComModeReq;
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(ComM_BusSmStateUType, COMM_VAR_NO_INIT) ComM_BusSmState;
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(ComM_ComAllowedUType, COMM_VAR_NO_INIT) ComM_ComAllowed;
#define COMM_STOP_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(ComM_DcmRequestActiveUType, COMM_VAR_NO_INIT) ComM_DcmRequestActive;
#define COMM_STOP_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NOCACHE_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
volatile VAR(ComM_EcuMWakeUpIndicatedType, COMM_VAR_NO_INIT) ComM_EcuMWakeUpIndicated[[!"$numChannels"!]];
#define COMM_STOP_SEC_VAR_NOCACHE_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(ComM_InhibitionType, COMM_NVM_DATA_NO_INIT) ComM_Inhibition;
#define COMM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(ComM_InitStatusType, COMM_VAR_NO_INIT) ComM_InitStatus;
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NOCACHE_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
volatile VAR(ComM_NmStartUpIndicatedType, COMM_VAR_NO_INIT) ComM_NmStartUpIndicated[[!"$numChannels"!]];
#define COMM_STOP_SEC_VAR_NOCACHE_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(ComM_PostInitializedType, COMM_VAR_NO_INIT) ComM_PostInitialized[1];
#define COMM_STOP_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
VAR(ComM_UserReqFullComType, COMM_VAR_NO_INIT) ComM_UserReqFullCom[[!"$effUsers"!]];
#define COMM_STOP_SEC_VAR_NO_INIT_8
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#if (COMM_USE_INIT_POINTER == STD_ON)
# define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
P2CONST( ComM_ConfigType, AUTOMATIC, COMM_INIT_DATA ) ComM_ConfigPtr = NULL_PTR;
# define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
CONST(ComM_InhibitionStatusType, COMM_CONST) ComM_ECUGroupClassInit = [!"$ecuGroupClassHex"!];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!//
[!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
FUNC(void, COMM_CODE) ComM_MainFunction_[!"num:i(node:value(ComMChannelId))"!](void)
{
  ComM_MainFunction((NetworkHandleType)[!"num:i(node:value(ComMChannelId))"!] );
}
[!ENDLOOP!][!//
[!ELSE!][!//
FUNC(void, COMM_CODE) ComM_MainFunction_0(void)
{
  ComM_MainFunction((NetworkHandleType)0 );
}
[!ENDIF!][!//

FUNC(void, COMM_CODE) ComM_CurrentChannelRequestInit( void )
{
}

FUNC(void, COMM_CODE) ComM_CurrentChannelRequestNotification( NetworkHandleType Channel, ComM_SizeOfFullComRequestersType numberOfRequesters )
{
  COMM_DUMMY_STATEMENT(Channel);
  COMM_DUMMY_STATEMENT(numberOfRequesters);
}
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!ENDSELECT!]

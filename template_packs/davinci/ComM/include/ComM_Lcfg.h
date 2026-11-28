[!SELECT "as:modconf('ComM')[1]"!][!//
#if !defined(COMM_LCFG_H)
#define COMM_LCFG_H

#include "ComM_Cfg.h"

#if (COMM_USE_INIT_POINTER == STD_ON)
# define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern P2CONST(ComM_ConfigType, AUTOMATIC, COMM_INIT_DATA) ComM_ConfigPtr;
# define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
#endif

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
extern CONST(ComM_InhibitionStatusType, COMM_CONST) ComM_ECUGroupClassInit;
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#define COMM_START_SEC_CODE
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */
[!IF "node:exists(ComMConfigSet/ComMChannel)"!][!//
[!LOOP "node:order(ComMConfigSet/ComMChannel/*, 'ComMChannelId')"!][!//
extern FUNC(void, COMM_CODE) ComM_MainFunction_[!"num:i(node:value(ComMChannelId))"!](void);
[!ENDLOOP!][!//
[!ELSE!][!//
extern FUNC(void, COMM_CODE) ComM_MainFunction_0(void);
[!ENDIF!][!//
extern FUNC( void, COMM_CODE ) ComM_MainFunction( NetworkHandleType Channel );
extern FUNC(void, COMM_CODE) ComM_CurrentChannelRequestInit( void );
extern FUNC(void, COMM_CODE) ComM_CurrentChannelRequestNotification( NetworkHandleType Channel, ComM_SizeOfFullComRequestersType numberOfRequesters );
#define COMM_STOP_SEC_CODE
#include "ComM_MemMap.h" /* PRQA S 5087 */ /* MD_MSR_MemMap */

#endif /* COMM_LCFG_H */
[!ENDSELECT!]

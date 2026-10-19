/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_timeprotection.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_TIMINGPROTECTION_H_
#define OS_TIMINGPROTECTION_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_GeneralTypes.h"
#include "Compiler.h"
#include "Os_timingprotection_types.h"
#include "Os_resource_types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsTp_InitMemory
*   Service ID              : None.
*   Description             : Initialize TP module memory.
*   Parameters in           : TpObjUsedCounterID, CounterID used for TP.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_InitMemory
(
    uint32 TpObjUsedCounterID
);
/****************************************************************************************************
*   Function Name           : OsTp_Init
*   Service ID              : None.
*   Description             : Initialize Tp module.
*   Parameters in           : TpObjetID.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_Init
(
    uint32 TpObjetID
);
/****************************************************************************************************
*   Function Name           : OsTp_Start
*   Service ID              : None.
*   Description             : Start TP module.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_Start(void);

/****************************************************************************************************
*   Function Name           : OsTp_InitObject
*   Service ID              : None.
*   Description             : Initialize Task/ISR2 TP control structure.
*   Parameters in           : CurrentObjectTpCfg. pointer of TP configuration structure.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_InitObject
(
    P2CONST(Os_TpObjectConfigType, TYPEDEF, OS_VAR) CurrentObjectTpCfg
);

/****************************************************************************************************
*   Function Name           : OsTp_Switch
*   Service ID              : None.
*   Description             : Suspend Current TP and Resume Next TP.
*   Parameters in           : CurrentObjectTpCfgPtr. pointer of Current Object TP configuration.
*   Parameters in           : NextObjectTpCfgPtr. pointer of Next Object TP configuration.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE)OsTp_Switch
(
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) CurrentObjectTpCfgPtr,
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) NextObjectTpCfgPtr
);
/****************************************************************************************************
*   Function Name           : OsTp_ResetAndResume
*   Service ID              : None.
*   Description             : Reset Current TP and Resume Next TP.
*   Parameters in           : CurrentObjectTpCfgPtr. pointer of Current Object TP configuration.
*   Parameters in           : NextObjectTpCfgPtr. pointer of Next Object TP configuration.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE)OsTp_ResetAndResume
(
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) CurrentObjectTpCfgPtr,
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) NextObjectTpCfgPtr
);

/****************************************************************************************************
*   Function Name           : OsTp_ResetAfterWait
*   Service ID              : None.
*   Description             : Reset Current TP When Task state changed from WAITING to READY.
*   Parameters in           : CurrentObjectTpCfgPtr. pointer of Current Object TP configuration.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_ResetAfterWait
(
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) CurrentObjectTpCfgPtr
);
/****************************************************************************************************
*   Function Name           : OsTp_PassTimeFrameCheck
*   Service ID              : None.
*   Description             : Check Specified Object whether pass TimeFrame check.
*   Parameters in           : CurrentObjectTpCfgPtr. pointer of Current Object TP configuration.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : TRUE indicates CurrentObject pass Time Frame check. Others indicate FAIL.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(boolean, OS_CODE) OsTp_PassTimeFrameCheck
(
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) CurrentObjectTpCfgPtr
);
/****************************************************************************************************
*   Function Name           : OsTp_StartLockResource
*   Service ID              : None.
*   Description             : Start Lock Resource TP.
*   Parameters in           : CurrentObjectTpCfgPtr. pointer of Current Object TP configuration.
*   Parameters in           : ResourceID. ResourceID which to start LockResource TP.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_StartLockResource
(
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) CurrentObjectTpCfgPtr,
    ResourceType ResourceID
);
/****************************************************************************************************
*   Function Name           : OsTp_StopLockResource
*   Service ID              : None.
*   Description             : Stop Lock Resource TP.
*   Parameters in           : CurrentObjectTpCfgPtr. pointer of Current Object TP configuration.
*   Parameters in           : ResourceID. ResourceID which to start LockResource TP.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_StopLockResource
(
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) CurrentObjectTpCfgPtr,
    ResourceType ResourceID
);
/****************************************************************************************************
*   Function Name           : OsTp_StartDelay
*   Service ID              : None.
*   Description             : Start Delay TP for Trusted Function Call.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_StartDelay(void);
/****************************************************************************************************
*   Function Name           : OsTp_StopDelay
*   Service ID              : None.
*   Description             : Stop Delay TP for Trusted Function Call.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_StopDelay(void);
/****************************************************************************************************
*   Function Name           : OsTp_StartLockAllInterrupt
*   Service ID              : None.
*   Description             : Start Lock All Interrupt TP.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_StartLockAllInterrupt(void);
/****************************************************************************************************
*   Function Name           : OsTp_StopLockAllInterrupt
*   Service ID              : None.
*   Description             : Stop Lock All Interrupt TP.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE)OsTp_StopLockAllInterrupt(void);
/****************************************************************************************************
*   Function Name           : OsTp_StartLockOsInterrupt
*   Service ID              : None.
*   Description             : Start Lock Os Interrupt TP.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_StartLockOsInterrupt(void);
/****************************************************************************************************
*   Function Name           : OsTp_StopLockOsInterrupt
*   Service ID              : None.
*   Description             : Stop Lock Os Interrupt TP.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsTp_StopLockOsInterrupt(void);
/****************************************************************************************************
*   Function Name           : OsTp_KillObject
*   Service ID              : None.
*   Description             : Reset Specified TP configuration when Task/ISR2 is killed.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE)OsTp_KillObject
(
    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_VAR) CurrentObjectTpCfgPtr
);

/****************************************************************************************************
*   Function Name           : Isr_TimingProtectionService
*   Service ID              : None.
*   Description             : Interrupt Service Routine for Timing Protection.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern ISR(TimingProtectionService);

#endif /* OS_TIMEPROTECTION_H_ */

/****************************************************************************************************
**     End of File: Os_timingprotection.h                                                                   **
****************************************************************************************************/


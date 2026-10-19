/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_context.h
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
#ifndef OS_CONTEXT_H_
#define OS_CONTEXT_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Platform_Types.h"
#include "compilertypes.h"
#include "Os_context_types.h"
#include "Os_task_types.h"
#include "Os_application_types.h"
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
*   Function Name           : Os_Hal_ContextInit
*   Service ID              : None.
*   Description             : Initial Task/ISR/Hook/IOC context.
*   Parameters in           : Config. Pointer to Task/ISR/Hook/IOC configuration.
*   Parameters inout        : None.
*   Parameters out          : Context. Pointer of Task/ISR/Hook/IOC Context info.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_ContextInit
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context
);

/****************************************************************************************************
*   Function Name           : Os_Hal_ContextAbort
*   Service ID              : None.
*   Description             : Abort context switch.
*   Parameters in           : Config. Pointer to Task/ISR/Hook/IOC configuration.
*   Parameters inout        : None.
*   Parameters out          : Context. Pointer of Task/ISR/Hook/IOC Context info.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_ContextAbort
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context
);

/****************************************************************************************************
*   Function Name           : OsContext_InitMemory
*   Service ID              : None.
*   Description             : Initialize Specified context.
*   Parameters in           : ContextID. context index of ContextConfigPtr array.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsContext_InitMemory
(
    uint32 ContextID
);

/****************************************************************************************************
*   Function Name           : Os_Hal_ContextSetParam
*   Service ID              : None.
*   Description             : Set Parameter for Context entry function.
*   Parameters in           : ContextID. context index of ContextConfigPtr array.
*                           : Parameter. Parameter transferred to context entry function
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_ContextSetParam
(
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context,
    P2VAR(void, AUTOMATIC, OS_INTERNAL_VAR) Parameter
);

/****************************************************************************************************
*   Function Name           : Os_Hal_ContextSwitch_Asm
*   Service ID              : None.
*   Description             : Do context switch with assembly language.
*   Parameters in           : NextTaskInfo. system switch to NextTaskInfo context.
*   Parameters inout        : None.
*   Parameters out          : CurrentTaskInfo. NULL_PTR indicates no saving current context, others
*                             indicates saving current context to CurrentTaskInfo.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_ContextSwitch_Asm
(
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) NextTaskInfo,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) CurrentTaskInfo
);

/****************************************************************************************************
*   Function Name           : Os_Hal_ContextMpuSwitch_Asm
*   Service ID              : None.
*   Description             : Do context and MPU switch with assembly language.
*   Parameters in           : NextTaskInfo. system switch to NextTaskInfo context.
*   Parameters inout        : None.
*   Parameters out          : CurrentTaskInfo. NULL_PTR indicates no saving current context, others
*                             indicates saving current context to CurrentTaskInfo..
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_ContextMpuSwitch_Asm
(
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) NextTaskInfo,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) CurrentTaskInfo
);

/****************************************************************************************************
*   Function Name           : Os_Hal_ContextSwitch
*   Service ID              : None.
*   Description             : Do context switch and related action(such as TP switch/MPU switch).
*   Parameters in           : NextObjInfo. Pointer of next Object information.
*                           : Choice. choice of saving current context or not.
*   Parameters inout        : None.
*   Parameters out          : CurrentObjInfo. Pointer of current object information.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_ContextSwitch
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) NextObjInfo,
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObjInfo,
    Os_SchedulingChoiceType   Choice
);

/****************************************************************************************************
*   Function Name           : Os_Hal_ServiceContextInit
*   Service ID              : None.
*   Description             : Initialize service context.
*   Parameters in           : Config. Pointer of service context configuration.
*   Parameters inout        : None.
*   Parameters out          : Context. Pointer to service context.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_ServiceContextInit
(
    P2CONST(Os_ContextType, AUTOMATIC, OS_INTERNAL_VAR) Config,
    P2VAR(Os_Hal_ServiceContextFrame, AUTOMATIC, OS_INTERNAL_VAR) Context
);

/****************************************************************************************************
*   Function Name           : Os_Hal_ServiceContextSwitch
*   Service ID              : None.
*   Description             : Do service context switch.
*   Parameters in           : NextObjInfo. Pointer of next Object information.
*                           : CurrentObjInfo. Pointer of current Object information.
*                           : NextServiceContext. Pointer of service context
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_ServiceContextSwitch
(
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) NextObjInfo,
    P2CONST(Os_AppObjectType, AUTOMATIC, OS_CONST) CurrentObjInfo,
    P2VAR(Os_Hal_ServiceContextFrame, AUTOMATIC, OS_INTERNAL_VAR) NextServiceContext
);

/****************************************************************************************************
*   Function Name           : Os_Hal_ServiceContextSwitch_Asm
*   Service ID              : None.
*   Description             : Implement service context switch with assemble language.
*   Parameters in           : NextTaskInfo. Pointer of next context information.
*                           : CurrentTaskInfo. Pointer of current context information.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_ServiceContextSwitch_Asm
(
    P2VAR(Os_Hal_ServiceContextFrame, AUTOMATIC, OS_INTERNAL_VAR) NextTaskInfo,
    P2VAR(Os_Hal_ContextFrame, AUTOMATIC, OS_INTERNAL_VAR) CurrentTaskInfo
);

/****************************************************************************************************
*   Function Name           : Os_Hal_StartNewThread
*   Service ID              : None.
*   Description             : Temporary function during starting up Task/Hook/ISR2/IOC.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) Os_Hal_StartNewThread(void);
#endif /* OS_CONTEXT_H_ */

/****************************************************************************************************
**     End of File: Os_context.h                                                                   **
****************************************************************************************************/

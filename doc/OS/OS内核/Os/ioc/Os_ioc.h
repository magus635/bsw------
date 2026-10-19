/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_ioc.h
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
#ifndef OS_IOC_H_
#define OS_IOC_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Compiler.h"
#include "Os_ioc_types.h"
#include "Os_isr.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define IOC_E_OK                        ((Std_ReturnType)0)
#define IOC_E_LIMIT                     ((Std_ReturnType)130)
#define IOC_E_LENGTH                    ((Std_ReturnType)130)
#define IOC_E_LOST_DATA                 ((Std_ReturnType)64)
#define IOC_E_NO_DATA                   ((Std_ReturnType)131)
#define IOC_E_NO_DATA_AND_LOST_DATA     (IOC_E_NO_DATA | IOC_E_LOST_DATA)
#define IOC_E_OK_AND_LOST_DATA          (IOC_E_OK | IOC_E_LOST_DATA)

#define OS_IOC_NO_OUTPUT_PARM_MASK      (0x0UL)
#define OS_IOC_OUTPUT_PARM0_MASK        (0x1UL)
#define OS_IOC_OUTPUT_PARM1_MASK        (0x2UL)
#define OS_IOC_OUTPUT_PARM2_MASK        (0x4UL)
#define OS_IOC_OUTPUT_PARM3_MASK        (0x8UL)
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
*   Function Name           : IocInit
*   Service ID              : None.
*   Description             : Initialize ioc channel.
*   Parameters in           : IocID: Ioc id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : SWS_Os_91026
****************************************************************************************************/
extern FUNC(void, OS_CODE) IocInit
(
    uint32 IocID
);

/****************************************************************************************************
*   Function Name           : OsIoc_CallbackReturn
*   Service ID              : None.
*   Description             : Post-processing function when return from ioc callback.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIoc_CallbackReturn
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIoc_CallbackDeInit
*   Service ID              : None.
*   Description             : Deinitialize ioc callback.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIoc_CallbackDeInit
(
    uint32 ObjectId
);

/****************************************************************************************************
*   Function Name           : OsIoc_ApplicationAccessCheck
*   Service ID              : None.
*   Description             : Check if current app can access ioc channel.
*   Parameters in           : ApplicationMask: App id mask of apps which can access the specific ioc channel.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsIoc_ApplicationAccessCheck
(
    uint32 ApplicationMask
);

/****************************************************************************************************
*   Function Name           : OsIoc_GetLock
*   Service ID              : None.
*   Description             : Start critical section.
*   Parameters in           : IocChannel: Ioc channel configuration.
                              Level: Isr level if needs interrupt lock.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIoc_GetLock
(
    P2CONST(Os_IocConfigType, AUTOMATIC, OS_CONST) IocChannel,
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) Level
);

/****************************************************************************************************
*   Function Name           : OsIoc_ReleaseLock
*   Service ID              : None.
*   Description             : End critical section.
*   Parameters in           : IocChannel: Ioc channel configuration.
                              Level: Isr level if needs interrupt lock.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIoc_ReleaseLock
(
    P2CONST(Os_IocConfigType, AUTOMATIC, OS_CONST) IocChannel,
    Os_IsrLevelType Level
);

/****************************************************************************************************
*   Function Name           : OsIoc_CallCallback
*   Service ID              : None.
*   Description             : Call ioc callback function.
*   Parameters in           : Callback: Configuration of callback.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsIoc_CallCallback
(
    P2CONST(Os_IocCallbackConfigType, AUTOMATIC, OS_CONST) Callback
);

/****************************************************************************************************
*   Function Name           : OsIoc_CrossCoreServiceCall
*   Service ID              : None.
*   Description             : Trigger cross-core service call.
*   Parameters in           : ServiceCallCfg: Service call configuration.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : StatusType: Error code.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(StatusType, OS_CODE) OsIoc_CrossCoreServiceCall
(
    Os_IocInterCoreServiceCallType* ServiceCallCfg
);

/****************************************************************************************************
*   Function Name           : OsIoc_GetIocServiceChannelCfgPtr
*   Service ID              : None.
*   Description             : Get service call channel configuration.
*   Parameters in           : SourcePhysicalCore: Sender physical core id of cross-core service call.
                              TargetPhysicalCore: Receiver physical core id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : P2CONST(Os_IocInterCoreServiceChannelCfgType, AUTOMATIC, OS_CONST): Channel configuration.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(P2CONST(Os_IocInterCoreServiceChannelCfgType, AUTOMATIC, OS_CONST), OS_CODE) OsIoc_GetIocServiceChannelCfgPtr
(
    CoreIdType SourcePhysicalCore,
    CoreIdType TargetPhysicalCore
);

/****************************************************************************************************
*   Function Name           : OsIoc_InterCoreServiceCallInit
*   Service ID              : None.
*   Description             : Service call channel init.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIoc_InterCoreServiceCallInit
(
    void
);

/****************************************************************************************************
*   Function Name           : OsIoc_ClearSyncServiceCallFlag
*   Service ID              : None.
*   Description             : Clear sync service call waiting flag in specific object.
*   Parameters in           : ObjectId: Object id.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
extern FUNC(void, OS_CODE) OsIoc_ClearSyncServiceCallFlag
(
    uint32 ObjectId
);

#endif /* OS_IOC_H_ */
/****************************************************************************************************
**     End of File: Os_ioc.h                                                                     **
****************************************************************************************************/

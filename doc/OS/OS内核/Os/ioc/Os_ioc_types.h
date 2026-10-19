/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_ioc_types.h
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
#ifndef OS_IOC_TYPES_H_
#define OS_IOC_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "datatypes.h"
#include "Compiler.h"
#include "Os_GeneralTypes.h"
#include "Os_spinlock_types.h"
#include "Os_kernel_Cfg.h"
#include "Os_context_types.h"
#include "Os_ioc_Cfg.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef P2FUNC(void, OS_CODE, Os_IocInitDataFuncType)
(
    void
);
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    OS_IOCTYPE_QUEUED,
    OS_IOCTYPE_UNQUEUED
}Os_IocType;

typedef enum
{
    OS_IOCLOCKTYPE_NONE,
    OS_IOCLOCKTYPE_INTERRUPTLOCK,
    OS_IOCLOCKTYPE_SPINLOCK,
    OS_IOCLOCKTYPE_ALL
}Os_IocLockType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
typedef struct
{
    uint32 WriteIndex;
    uint32 ReadIndex;
    uint32 DataLostCount;
    uint32 DataLostCountRecord;
    /* Record next receive channel in case of N:1 queued no callback */
    uint32 NextReceiveChannel;
}Os_IocRunningDataType;

typedef struct
{
    uint32 ObjectID;
    CoreIdType CoreID;
}Os_IocCallbackConfigType;

typedef struct
{
    /* IOC ID */
    uint32 IocID;
    /* IOC type */
    Os_IocType Type;
    /* Applications mask of sender apps */
    uint32 SenderApplication;
    /* Applications mask of receiver apps */
    uint32 RecevierAppliaction;
    /* Receive channel number */
    uint32 ReceiveChannelNum;
    /* The spinlock that IOC uses, if needed */
    SpinlockIdType SpinLock;
    /* Callback function number. Greater than 1, only in case of N:M */
    uint32 CallbackCount;
    /* The lock IOC used */
    Os_IocLockType LockType;
    /* The Ioc data used when system running */
    P2VAR(Os_IocRunningDataType, AUTOMATIC, OS_VAR) IocRunningData;
    /* Initialization function for each buffer if there is an initial value */
    Os_IocInitDataFuncType InitDataFunc;
    /* Pointer to callbacks */
    P2CONST(Os_IocCallbackConfigType, TYPEDEF, OS_CONST) IocCallbacks;
    P2VAR(boolean, AUTOMATIC, OS_VAR) CallbackIsUsed;
}Os_IocConfigType;

typedef struct
{
    uint32 WriteIndex;
    uint32 ReadIndex;
    uint32 ResultIndex;
}Os_IocInterCoreServiceCallRunningDataType;

typedef struct
{
    P2VAR(void, AUTOMATIC, OS_VAR) OutParm[OS_IOC_SERVICE_CALL_PARM_OUT_MAX_NUM];
}Os_IocInterCoreServiceCallParamOutType;

typedef struct
{
    Os_ServiceType ServiceId;
    /* Entry address of cross core service */
    uint32 EntryAddress;
    uint32 TargetCoreId;
    /* Input parameter of service */
    Os_ServiceCallInputType ParameterIn[OS_IOC_SERVICE_CALL_PARM_IN_MAX_NUM];
    /* Variable which save the output parameter of receiver */
    Os_IocInterCoreServiceCallParamOutType OutParameter;
    /* Mask to indicate which input parameter is ouput type */
    uint32 OutputParmMask;
    /* Synchronous or Asynchronous */
    uint32 ServiceType;
}Os_IocInterCoreServiceCallType;

typedef struct
{
    /* Pointer to context FIFO */
    P2VAR(Os_Hal_ServiceContextFrame, AUTOMATIC, OS_VAR) ServiceContextBuffer;
    /* Buffer length of context FIFO */
    uint32 BufferLength;
    P2VAR(Os_IocInterCoreServiceCallRunningDataType, AUTOMATIC, OS_VAR) RunningData;
    /* Software Interrupt id of this channel.
       Ex: For core0, 0 is interrupt from core1; 1 is from core2. Etc. */
    uint32 IntId;
    /* Pointer to output parameter FIFO. One FIFO per channel */
    P2VAR(Os_IocInterCoreServiceCallParamOutType, AUTOMATIC, OS_VAR) ParameterOut;
}Os_IocInterCoreServiceChannelCfgType;

typedef struct
{
    P2CONST(Os_IocInterCoreServiceChannelCfgType, TYPEDEF, OS_CONST) CoreServiceChannelCfgList[OS_KERNEL_MAX_CORE_NUM];
}Os_IocInterCoreServiceChannelCfgRefType;

#endif /* OS_IOC_TYPES_H_ */
/****************************************************************************************************
**     End of File: Os_ioc_types.h                                                                **
****************************************************************************************************/

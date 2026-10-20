/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_ioc_Lcfg.c
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
*   Genaration Time       : [!"$datetime"!]
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
[!//
[!NOCODE!][!//
[!INCLUDE "Os_AppCommon.m"!][!//
[!ENDNOCODE!][!//
[!//

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_ioc_Lcfg.h"
#include "Os_kernel_Cfg.h"
#include "common.h"
#include "Os_context_types.h"
#include "Os_spinlock_Cfg.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/****************************************************************************************************
**                          Private Type Definitions                                                **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Structure Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
[!VAR "HasInitValue" = "'false'"!][!//
    [!IF "count(OsIocBufferLength/*) = 0"!][!//
        [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
            [!IF "not(node:empty(OsIocInitValue))"!][!//
                [!VAR "HasInitValue" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$HasInitValue = 'true'"!][!//
static FUNC(void, OS_CODE) OsIoc_[!"node:name(.)"!]_InitData
(
    [!INDENT "4"!][!//
    void
    [!ENDINDENT!][!//
);
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!IF "count(./OsIoc/*/OsIocCommunication/*) > 0"!][!//
#define OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
    [!IF "count(OsIocBufferLength/*) = 0"!][!//
        [!IF "count(OsIocDataProperties/*) = 1"!][!//
            [!"node:value(OsIocDataProperties/*/OsIocDataTypeRef)"!] OsIoc_[!"node:name(.)"!]_Buffer;
        [!ELSE!][!//
            [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
                [!"node:value(OsIocDataTypeRef)"!] OsIoc_[!"node:name(../..)"!]_Buffer_[!"@index"!];
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ELSE!][!//
        [!IF "count(OsIocDataProperties/*) > 1"!][!//
            [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
                [!"node:value(OsIocDataTypeRef)"!] OsIoc_[!"node:name(../..)"!]_Buffer_[!"@index"!][OS_IOC_[!"text:toupper(node:name(../..))"!]_BUFFER_SIZE];
            [!ENDLOOP!][!//
        [!ELSE!][!//
            [!IF "(OsIocReceiverProperties/*/OsIocReceiveCallbackEnable = 'false') and (count(OsIocSenderProperties/*) > 1)"!][!//
                [!"node:value(OsIocDataProperties/*/OsIocDataTypeRef)"!] OsIoc_[!"node:name(.)"!]_Buffer[OS_IOC_[!"text:toupper(node:name(.))"!]_RECEIVE_CHANNEL_NUM][OS_IOC_[!"text:toupper(node:name(.))"!]_BUFFER_SIZE];
            [!ELSE!][!//
                [!"node:value(OsIocDataProperties/*/OsIocDataTypeRef)"!] OsIoc_[!"node:name(.)"!]_Buffer[OS_IOC_[!"text:toupper(node:name(.))"!]_BUFFER_SIZE];
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
    [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
        [!IF "OsIocReceiveCallbackEnable = 'true'"!][!//
            boolean OsIoc_[!"node:name(../..)"!]_CallbackIsUsed;
            [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//

[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
    [!IF "count(OsIocBufferLength/*) > 0"!][!//
        [!IF "node:value(./OsIocReceiverProperties/*/OsIocReceiveCallbackEnable) = 'true'"!][!//
            Os_IocRunningDataType Os_Ioc_[!"node:name(.)"!]_RunningData;
        [!ELSE!][!//
            Os_IocRunningDataType Os_Ioc_[!"node:name(.)"!]_RunningData[OS_IOC_[!"text:toupper(node:name(.))"!]_RECEIVE_CHANNEL_NUM];
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
#define OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!IF "count(./OsCoreIdMappingConfig/*) > 1"!][!//
#define OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"

[!LOOP "node:order(./OsCoreIdMappingConfig/*,'OsPhysicalCoreId')"!][!//
[!VAR "CurrentCoreId" = "./OsPhysicalCoreId"!][!//
    [!LOOP "node:order(./OsCoreServiceCall/*,'@index')"!][!//
    [!VAR "TargetCoreId" = "node:value(node:ref(./OsReceiverCore)/OsPhysicalCoreId)"!][!//
Os_Hal_ServiceContextFrame Os_Ioc_Core[!"$CurrentCoreId"!]ToCore[!"$TargetCoreId"!]ServiceCallBuffer[OS_IOC_CORE[!"$CurrentCoreId"!]_TO_CORE[!"$TargetCoreId"!]_SERVICECALL_BUFFER_LENGTH];
Os_IocInterCoreServiceCallRunningDataType Os_Ioc_Core[!"$CurrentCoreId"!]ToCore[!"$TargetCoreId"!]ServiceCallRunningData;
Os_IocInterCoreServiceCallParamOutType Os_Ioc_Core[!"$CurrentCoreId"!]ToCore[!"$TargetCoreId"!]ParameterOut[OS_IOC_CORE[!"$CurrentCoreId"!]_TO_CORE[!"$TargetCoreId"!]_SERVICECALL_BUFFER_LENGTH];

    [!ENDLOOP!][!//
[!ENDLOOP!][!//
#define OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
#include "Os_memmap.h"
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//
/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
[!VAR "ObjectId" = "0"!][!//
[!VAR "CurrentIocName" = "node:name(.)"!][!//
[!VAR "IocCallbackCount" = "0"!][!//
    [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
        [!IF "OsIocReceiveCallbackEnable = 'true'"!][!//
            [!VAR "IocCallbackCount" = "$IocCallbackCount + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$IocCallbackCount > 0"!][!//
static const Os_IocCallbackConfigType [!"$CurrentIocName"!]_CallbackCfg[OS_IOC_[!"text:toupper($CurrentIocName)"!]_CALLBACK_NUM] = 
{
    [!INDENT "4"!][!//
    [!VAR "Count" = "0"!][!//
    [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
        [!VAR "Count" = "$Count + 1"!][!//
        [!VAR "ReceiverAppId" = "node:ref(./OsIocReceivingOsApplicationRef)/@index"!][!//
        [!IF "OsIocReceiveCallbackEnable = 'true'"!][!//
    {
        [!INDENT "8"!][!//
        [!CALL "Os_Calculate_IocCallBack_ObjectId", "CurrentIocName"= "$CurrentIocName", "ReceiverAppId" = "$ReceiverAppId", "ObjectId" = "$ObjectId"!][!//
        [!"num:i($ObjectId)"!]UL,            /* Object ID */
        OS_CORE_ID_[!"node:ref(node:ref(./OsIocReceivingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!]     /* CoreID */
        [!ENDINDENT!][!//
    }[!IF "$Count < $IocCallbackCount"!],[!ENDIF!]
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};

    [!ENDIF!][!//
[!ENDLOOP!][!//
#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
[!ENDINDENT!][!//
[!ENDSELECT!][!//
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
[!VAR "CurrentIocName" = "node:name(.)"!][!//
const Os_IocConfigType Os_IocConfig_[!"$CurrentIocName"!] =
{
    [!INDENT "4"!][!//
    [!"@index"!],                               /* IocID */
    [!IF "count(OsIocBufferLength/*) = 0"!][!//
        OS_IOCTYPE_UNQUEUED,                /* Type */
    [!ELSE!][!//
        OS_IOCTYPE_QUEUED,                  /* Type */
    [!ENDIF!][!//
    [!VAR "IocSenderAppId" = "0"!][!//
    [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
        [!VAR "IocSenderAppId" = "bit:or(num:i($IocSenderAppId), bit:shl(num:i(1), num:i(node:ref(OsIocSendingOsApplicationRef)/@index)))"!][!//
    [!ENDLOOP!][!//
    [!"num:inttohex(num:i($IocSenderAppId))"!]UL,               /* SenderApplication */
    [!VAR "IocReceiverAppId" = "0"!][!//
    [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
        [!VAR "IocReceiverAppId" = "bit:or(num:i($IocReceiverAppId), bit:shl(num:i(1), num:i(node:ref(OsIocReceivingOsApplicationRef)/@index)))"!][!//
    [!ENDLOOP!][!//
    [!"num:inttohex(num:i($IocReceiverAppId))"!]UL,               /* ReceiverApplication */
    [!IF "count(OsIocBufferLength/*) = 0"!][!//
        1,                                  /* ReceiveChannelNum */
    [!ELSE!][!//
        OS_IOC_[!"text:toupper($CurrentIocName)"!]_RECEIVE_CHANNEL_NUM,                /* ReceiveChannelNum */
    [!ENDIF!][!//
    [!VAR "IocSpinlock" = "'false'"!][!//
    [!VAR "IocInterruptLock" = "'false'"!][!//
    [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
        [!IF "@index = 0"!][!//
            [!VAR "SenderCoreId" = "node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
        [!ELSE!][!//
            [!IF "$SenderCoreId != node:ref(node:ref(OsIocSendingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                [!VAR "IocSpinlock" = "'true'"!][!//
            [!ELSE!][!//
                [!VAR "IocInterruptLock" = "'true'"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
        [!LOOP "node:order(../../OsIocReceiverProperties/*,'@index')"!][!//
            [!IF "$SenderCoreId != node:ref(node:ref(OsIocReceivingOsApplicationRef)/OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                [!VAR "IocSpinlock" = "'true'"!][!//
            [!ELSE!][!//
                [!VAR "IocInterruptLock" = "'true'"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!IF "$IocSpinlock = 'true'"!][!//
        [!"text:toupper($CurrentIocName)"!]_SPINLOCK,           /* SpinLock */
    [!ELSE!][!//
        OS_INVALID_SPINLOCK,                           /* SpinLock */
    [!ENDIF!][!//
    OS_IOC_[!"text:toupper($CurrentIocName)"!]_CALLBACK_NUM,    /* CallbackCount */
    [!IF "($IocInterruptLock = 'false') and ($IocSpinlock = 'false')"!][!//
        OS_IOCLOCKTYPE_NONE,                /* LockType */
    [!ELSEIF "($IocInterruptLock = 'true') and ($IocSpinlock = 'false')"!][!//
        OS_IOCLOCKTYPE_INTERRUPTLOCK,       /* LockType */
    [!ELSEIF "($IocInterruptLock = 'false') and ($IocSpinlock = 'true')"!][!//
        OS_IOCLOCKTYPE_SPINLOCK,            /* LockType */
    [!ELSE!][!//
        OS_IOCLOCKTYPE_ALL,                 /* LockType */
    [!ENDIF!][!//
    [!IF "count(OsIocBufferLength/*) = 0"!][!//
        NULL_PTR,                           /* IocRunningData */
    [!ELSE!][!//
        [!IF "node:value(./OsIocReceiverProperties/*/OsIocReceiveCallbackEnable) = 'true'"!][!//
            &Os_Ioc_[!"$CurrentIocName"!]_RunningData,         /* IocRunningData */
        [!ELSE!][!//
            Os_Ioc_[!"$CurrentIocName"!]_RunningData,         /* IocRunningData */
        [!ENDIF!][!//
    [!ENDIF!][!//
    [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
        [!IF "not(node:empty(OsIocInitValue))"!][!//
            &OsIoc_[!"$CurrentIocName"!]_InitData,                /* InitDataFuncList */
            [!BREAK!][!//
        [!ELSEIF "node:islast(.)"!][!//
            NULL_PTR,                           /* InitDataFuncList */
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!VAR "IocCallbackCount" = "0"!][!//
    [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
        [!IF "OsIocReceiveCallbackEnable = 'true'"!][!//
            [!VAR "IocCallbackCount" = "$IocCallbackCount + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$IocCallbackCount > 0"!][!//
        [!"$CurrentIocName"!]_CallbackCfg,          /* IocCallbacks */
        &OsIoc_[!"$CurrentIocName"!]_CallbackIsUsed  /* CallbackIsUsed */
    [!ELSE!][!//
        NULL_PTR,                           /* IocCallbacks */
        NULL_PTR                            /* CallbackIsUsed */
    [!ENDIF!][!//
    [!ENDINDENT!][!//
};

[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!IF "count(./OsCoreIdMappingConfig/*) > 1"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'OsPhysicalCoreId')"!][!//
[!VAR "CurrentCoreId" = "./OsPhysicalCoreId"!][!//
    [!LOOP "node:order(./OsCoreServiceCall/*,'@index')"!][!//
    [!VAR "TargetCoreId" = "node:value(node:ref(./OsReceiverCore)/OsPhysicalCoreId)"!][!//
static const Os_IocInterCoreServiceChannelCfgType Os_Ioc_Core[!"$CurrentCoreId"!]ToCore[!"$TargetCoreId"!]ServiceChannelCfg =
{
    [!INDENT "4"!][!//
    Os_Ioc_Core[!"$CurrentCoreId"!]ToCore[!"$TargetCoreId"!]ServiceCallBuffer,       /* ServiceContextBuffer */
    OS_IOC_CORE[!"$CurrentCoreId"!]_TO_CORE[!"$TargetCoreId"!]_SERVICECALL_BUFFER_LENGTH,        /* BufferLength */
    &Os_Ioc_Core[!"$CurrentCoreId"!]ToCore[!"$TargetCoreId"!]ServiceCallRunningData,       /* RunningData */
    [!IF "$CurrentCoreId > $TargetCoreId"!][!//
    [!"num:i($TargetCoreId)"!]UL,                                         /* IntId */
    [!ELSE!][!//
    [!"num:i($TargetCoreId - 1)"!]UL,                                         /* IntId */
    [!ENDIF!][!//
    Os_Ioc_Core[!"$CurrentCoreId"!]ToCore[!"$TargetCoreId"!]ParameterOut
    [!ENDINDENT!][!//
};

    [!ENDLOOP!][!//
[!ENDLOOP!][!//
const Os_IocInterCoreServiceChannelCfgRefType Os_IocServiceChannelCfgRef[OS_KERNEL_MAX_CORE_NUM] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'OsPhysicalCoreId')"!][!//
    [!VAR "CurrentCoreId" = "./OsPhysicalCoreId"!][!//
    /* Physical core[!"$CurrentCoreId"!] to other cores channels */
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "CoreCount" = "0" TO "ecu:get('OsResource.NumOfCores') - 1"!][!//
                [!IF "$CurrentCoreId = $CoreCount"!][!//
                    NULL_PTR[!IF "$CoreCount < ecu:get('OsResource.NumOfCores') - 1"!],[!ENDIF!]
                [!ELSE!][!//
                    &Os_Ioc_Core[!"$CurrentCoreId"!]ToCore[!"$CoreCount"!]ServiceChannelCfg[!IF "$CoreCount < ecu:get('OsResource.NumOfCores') - 1"!],[!ENDIF!]
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "not(node:islast(.))"!],[!ENDIF!]
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ELSE!][!//
const Os_IocInterCoreServiceChannelCfgRefType Os_IocServiceChannelCfgRef[OS_KERNEL_MAX_CORE_NUM] =
{
    [!INDENT "4"!][!//
    [!FOR "LoopCount" = "0" TO "ecu:get('OsResource.NumOfCores') - 1"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "CoreCount" = "0" TO "ecu:get('OsResource.NumOfCores') - 1"!][!//
                NULL_PTR[!IF "$CoreCount < ecu:get('OsResource.NumOfCores') - 1"!],[!ENDIF!]
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
        }
        [!ENDINDENT!][!//
    }[!IF "$LoopCount < ecu:get('OsResource.NumOfCores') - 1"!],[!ENDIF!]
    [!ENDFOR!][!//
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//

#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

CONSTP2CONST(Os_IocConfigType, AUTOMATIC, OS_CONST) Os_IocConfigSet[OS_IOC_TOTAL_NUM + 1U] = 
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
        &Os_IocConfig_[!"node:name(.)"!],
    [!ENDLOOP!][!//
    NULL_PTR
    [!ENDINDENT!][!//
};

#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
[!ENDINDENT!][!//
[!ENDSELECT!][!//
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#define OS_START_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
[!VAR "CurrentIocName" = "node:name(.)"!][!//
[!VAR "HasInitValue" = "'false'"!][!//
    [!IF "count(OsIocBufferLength/*) = 0"!][!//
        [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
            [!IF "not(node:empty(OsIocInitValue))"!][!//
                [!VAR "HasInitValue" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$HasInitValue = 'true'"!][!//
static FUNC(void, OS_CODE) OsIoc_[!"$CurrentIocName"!]_InitData
(
    [!INDENT "4"!][!//
    void
    [!ENDINDENT!][!//
)
{
    [!INDENT "4"!][!//
    [!IF "count(OsIocDataProperties/*) = 1"!][!//
        OsIoc_[!"$CurrentIocName"!]_Buffer = [!"./OsIocDataProperties/*/OsIocInitValue"!];
    [!ELSE!][!//
        [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
            [!IF "not(node:empty(OsIocInitValue))"!][!//
                OsIoc_[!"$CurrentIocName)"!]_Buffer_[!"@index"!] = [!"OsIocInitValue"!];
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDIF!][!//
    [!ENDINDENT!][!//
}

        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//
#define OS_STOP_SEC_CODE_QM_GLOBAL
#include "Os_memmap.h"
/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_ioc_Lcfg.h
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
#ifndef OS_IOC_LCFG_H_
#define OS_IOC_LCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_ioc_Cfg.h"
#include "Os_ioc_types.h"
#include "Os_kernel_Cfg.h"
#include "Os_GeneralTypes.h"
#include "Os_isr_types.h"
#include "Os_resource_types.h"
#include "Os_task_types.h"
#include "Os_spinlock_types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
    [!IF "count(OsIocBufferLength/*) = 0"!][!//
        [!IF "count(OsIocDataProperties/*) = 1"!][!//
extern [!"node:value(OsIocDataProperties/*/OsIocDataTypeRef)"!] OsIoc_[!"node:name(.)"!]_Buffer;
        [!ELSE!][!//
            [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
extern [!"node:value(OsIocDataTypeRef)"!] OsIoc_[!"node:name(../..)"!]_Buffer_[!"@index"!];
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ELSE!][!//
        [!IF "count(OsIocDataProperties/*) > 1"!][!//
            [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
extern [!"node:value(OsIocDataTypeRef)"!] OsIoc_[!"node:name(../..)"!]_Buffer_[!"@index"!][OS_IOC_[!"text:toupper(node:name(../..))"!]_BUFFER_SIZE];
            [!ENDLOOP!][!//
        [!ELSE!][!//
            [!IF "(OsIocReceiverProperties/*/OsIocReceiveCallbackEnable = 'false') and (count(OsIocSenderProperties/*) > 1)"!][!//
extern [!"node:value(OsIocDataProperties/*/OsIocDataTypeRef)"!] OsIoc_[!"node:name(.)"!]_Buffer[OS_IOC_[!"text:toupper(node:name(.))"!]_RECEIVE_CHANNEL_NUM][OS_IOC_[!"text:toupper(node:name(.))"!]_BUFFER_SIZE];
            [!ELSE!][!//
extern [!"node:value(OsIocDataProperties/*/OsIocDataTypeRef)"!] OsIoc_[!"node:name(.)"!]_Buffer[OS_IOC_[!"text:toupper(node:name(.))"!]_BUFFER_SIZE];
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//

[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
    [!IF "count(OsIocBufferLength/*) > 0"!][!//
        [!IF "node:value(./OsIocReceiverProperties/*/OsIocReceiveCallbackEnable) = 'true'"!][!//
extern Os_IocRunningDataType Os_Ioc_[!"node:name(.)"!]_RunningData;
        [!ELSE!][!//
extern Os_IocRunningDataType Os_Ioc_[!"node:name(.)"!]_RunningData[OS_IOC_[!"text:toupper(node:name(.))"!]_RECEIVE_CHANNEL_NUM];
        [!ENDIF!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//
/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
extern const Os_IocConfigType Os_IocConfig_[!"node:name(.)"!];
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//

extern CONSTP2CONST(Os_IocConfigType, AUTOMATIC, OS_CONST) Os_IocConfigSet[OS_IOC_TOTAL_NUM + 1U];
extern const Os_IocInterCoreServiceChannelCfgRefType Os_IocServiceChannelCfgRef[OS_KERNEL_MAX_CORE_NUM];
/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
    [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
        [!IF "OsIocReceiveCallbackEnable = 'true'"!][!//
extern FUNC(void, OS_CODE) [!"OsIocReceiverPullCB"!]
(
    [!INDENT "4"!][!//
    void
    [!ENDINDENT!][!//
);

        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//
#endif /* OS_IOC_LCFG_H_ */

/****************************************************************************************************
**     End of File: Os_ioc_Lcfg.h                                                                  **
****************************************************************************************************/


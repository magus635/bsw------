/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_ioc_Cfg.h
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
#ifndef OS_IOC_CFG_H_
#define OS_IOC_CFG_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!IF "count(./OsIoc/*/OsIocIncludeHeader/*) > 0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocIncludeHeader/*, '@index')"!][!//
    [!IF "string-length(.) > 0"!][!//
#include "[!"."!]"
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
#define OS_IOC_TOTAL_NUM                ([!"num:i(count(./OsIoc/*/*/*))"!]U)
#define OS_IOC_SERVICE_CALL_PARM_IN_MAX_NUM     (4UL)
#define OS_IOC_SERVICE_CALL_PARM_OUT_MAX_NUM    (1UL)
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
[!VAR "IocCallbackCount" = "0"!][!//
    [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
        [!IF "OsIocReceiveCallbackEnable = 'true'"!][!//
            [!VAR "IocCallbackCount" = "$IocCallbackCount + 1"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//

#define OS_IOC_[!"text:toupper(node:name(.))"!]_CALLBACK_NUM    ([!"num:i($IocCallbackCount)"!]U)
    [!IF "count(./OsIocBufferLength/*) > 0"!][!//
        [!IF "node:value(./OsIocReceiverProperties/*/OsIocReceiveCallbackEnable) = 'true'"!][!//
#define OS_IOC_[!"text:toupper(node:name(.))"!]_RECEIVE_CHANNEL_NUM (1U)
        [!ELSE!][!//
#define OS_IOC_[!"text:toupper(node:name(.))"!]_RECEIVE_CHANNEL_NUM ([!"num:i(count(./OsIocSenderProperties/*))"!]U)
        [!ENDIF!][!//
#define OS_IOC_[!"text:toupper(node:name(.))"!]_BUFFER_SIZE         ([!"num:i(node:value(./OsIocBufferLength/*) + 1)"!]U)
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!IF "count(./OsCoreIdMappingConfig/*) > 1"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'OsPhysicalCoreId')"!][!//
[!VAR "CurrentCoreId" = "./OsPhysicalCoreId"!][!//
    [!LOOP "node:order(./OsCoreServiceCall/*,'@index')"!][!//
#define OS_IOC_CORE[!"$CurrentCoreId"!]_TO_CORE[!"node:value(node:ref(./OsReceiverCore)/OsPhysicalCoreId)"!]_SERVICECALL_BUFFER_LENGTH      ([!"num:i(OsCoreServiceCallBufferLength + 1)"!]UL)
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//

#define OS_IOC_SERVICECALL_ASYNC            (0x0UL)
#define OS_IOC_SERVICECALL_SYNC_UNHANDLED   (0x10000UL)
#define OS_IOC_SERVICECALL_SYNC_HANDLED     (0x20000UL)
#define OS_IOC_SERVICECALL_ACK              (0x30000UL)
#define OS_IOC_SERVICECALL_TYPE_MASK        (0xFFFF0000UL)
#define OS_IOC_SERVICECALL_OBJECTID_MASK    (0xFFFFUL)
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




#endif /* OS_IOC_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_ioc_Cfg.h                                                                   **
****************************************************************************************************/


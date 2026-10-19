/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_ioc_Callout.h
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


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!IF "count(./OsIoc/*) != 0"!][!//
#include "Std_Types.h"
[!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDSELECT!][!//
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
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!INDENT "0"!][!//
[!LOOP "node:order(./OsIoc/*/OsIocCommunication/*,'@index')"!][!//
[!VAR "CurrentIocName" = "node:name(.)"!][!//
    [!IF "count(OsIocBufferLength/*) = 0"!][!//
        [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
/****************************************************************************************************
*   Function Name           : IocWrite[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [!IF "count(../../OsIocDataProperties/*) > 1"!][SWS_Os_91004]][!ELSE!][SWS_Os_91003][!ENDIF!]
****************************************************************************************************/
extern FUNC(Std_ReturnType, OS_CODE) IocWrite[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
(
    [!INDENT "4"!][!//
            [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                [!VAR "FindType" = "'false'"!][!//
                [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                    [!IF "OsIocDataTypeRef = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                        [!VAR "FindType" = "'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "$FindType = 'true'"!][!//
    [!"OsIocDataTypeRef"!] Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                [!ELSE!][!//
    P2CONST([!"OsIocDataTypeRef"!], AUTOMATIC, OS_CONST) Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                [!ENDIF!][!//
            [!ENDLOOP!][!//
    [!ENDINDENT!][!//
);

        [!ENDLOOP!][!//
        [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
/****************************************************************************************************
*   Function Name           : IocRead[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [!IF "count(../../OsIocDataProperties/*) > 1"!][SWS_Os_91006]][!ELSE!][SWS_Os_91005][!ENDIF!]
****************************************************************************************************/
extern FUNC(Std_ReturnType, OS_CODE) IocRead[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
(
    [!INDENT "4"!][!//
            [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
    P2VAR([!"OsIocDataTypeRef"!], AUTOMATIC, OS_VAR) Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
            [!ENDLOOP!][!//
    [!ENDINDENT!][!//
);

        [!ENDLOOP!][!//
    [!ELSE!][!//
        [!IF "(OsIocReceiverProperties/*/OsIocReceiveCallbackEnable = 'false') and (count(OsIocSenderProperties/*) > 1)"!][!//
            [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
/****************************************************************************************************
*   Function Name           : IocSend_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00718]
****************************************************************************************************/
extern FUNC(Std_ReturnType, OS_CODE) IocSend_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
(
    [!INDENT "4"!][!//
                [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                    [!VAR "FindType" = "'false'"!][!//
                    [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                        [!IF "OsIocDataTypeRef = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                            [!VAR "FindType" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!IF "$FindType = 'true'"!][!//
    [!"OsIocDataTypeRef"!] Data
                    [!ELSE!][!//
    P2CONST([!"OsIocDataTypeRef"!], AUTOMATIC, OS_CONST) Data
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
    [!ENDINDENT!][!//
);

            [!ENDLOOP!][!//
/****************************************************************************************************
*   Function Name           : IocReceive_[!"$CurrentIocName"!]
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00738]
****************************************************************************************************/
extern FUNC(Std_ReturnType, OS_CODE) IocReceive_[!"$CurrentIocName"!]
(
    [!INDENT "4"!][!//
                [!LOOP "node:order(./OsIocDataProperties/*,'@index')"!][!//
    P2VAR([!"OsIocDataTypeRef"!], AUTOMATIC, OS_VAR) Data
                [!ENDLOOP!][!//
    [!ENDINDENT!][!//
);

/****************************************************************************************************
*   Function Name           : IocEmptyQueue_[!"$CurrentIocName"!]
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00754]
****************************************************************************************************/
extern FUNC(Std_ReturnType, OS_CODE) IocEmptyQueue_[!"$CurrentIocName"!]
(
    [!INDENT "4"!][!//
    void
    [!ENDINDENT!][!//
);

        [!ELSE!][!//
            [!LOOP "node:order(./OsIocSenderProperties/*,'@index')"!][!//
/****************************************************************************************************
*   Function Name           : IocSend[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [!IF "count(../../OsIocDataProperties/*) > 1"!][SWS_Os_00728]][!ELSE!][SWS_Os_00718][!ENDIF!]
****************************************************************************************************/
extern FUNC(Std_ReturnType, OS_CODE) IocSend[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!][!IF "count(../*) > 1"!]_[!"node:name(.)"!][!ENDIF!]
(
    [!INDENT "4"!][!//
                [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
                    [!VAR "FindType" = "'false'"!][!//
                    [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                        [!IF "OsIocDataTypeRef = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                            [!VAR "FindType" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!IF "$FindType = 'true'"!][!//
    [!"OsIocDataTypeRef"!] Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                    [!ELSE!][!//
    P2CONST([!"OsIocDataTypeRef"!], AUTOMATIC, OS_CONST) Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
    [!ENDINDENT!][!//
);

            [!ENDLOOP!][!//
            [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
/****************************************************************************************************
*   Function Name           : IocReceive[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!]
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [!IF "count(../../OsIocDataProperties/*) > 1"!][SWS_Os_00746]][!ELSE!][SWS_Os_00738][!ENDIF!]
****************************************************************************************************/
extern FUNC(Std_ReturnType, OS_CODE) IocReceive[!IF "count(../../OsIocDataProperties/*) > 1"!]Group[!ENDIF!]_[!"$CurrentIocName"!]
(
    [!INDENT "4"!][!//
                [!LOOP "node:order(../../OsIocDataProperties/*,'@index')"!][!//
    P2VAR([!"OsIocDataTypeRef"!], AUTOMATIC, OS_VAR) Data_[!"@index"!][!IF "not(node:islast(.))"!],[!ENDIF!]
                [!ENDLOOP!][!//
    [!ENDINDENT!][!//
);

            [!ENDLOOP!][!//
/****************************************************************************************************
*   Function Name           : IocEmptyQueue_[!"$CurrentIocName"!]
*   Service ID              : None.
*   Description             : None.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : [SWS_Os_00754]
****************************************************************************************************/
extern FUNC(Std_ReturnType, OS_CODE) IocEmptyQueue_[!"$CurrentIocName"!]
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
/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_services_Lcfg.h
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
#ifndef OS_SERVICES_LCFG_H_
#define OS_SERVICES_LCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os_services_types.h"
#include "Os_services_Cfg.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
    [!LOOP "node:order(./OsApplicationTrustedFunction/*,'@index')"!][!//
        typedef struct
        {
            [!INDENT "4"!][!//
            [!LOOP "node:order(./OsTrustedFunctionParameter/*,'@index')"!][!//
                [!IF "OsTrustedFunctionParameterType = 'IN'"!][!//
                    [!VAR "FindType" = "'false'"!][!//
                    [!FOR "Count" = "num:i(1)" TO "num:i(ecu:get('Os.IocPrimitiveDataTypeNum'))"!][!//
                        [!IF "OsTrustedFunctionParameterDataType = ecu:list('Os.IocPrimitiveDataType')[$Count]"!][!//
                            [!VAR "FindType" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ENDFOR!][!//
                    [!IF "$FindType = 'true'"!][!//
                        [!"OsTrustedFunctionParameterDataType"!] [!"node:name(.)"!];
                    [!ELSE!][!//
                        P2VAR([!"OsTrustedFunctionParameterDataType"!], TYPEDEF, OS_VAR) [!"node:name(.)"!];
                    [!ENDIF!][!//
                [!ELSE!][!//
                    P2VAR([!"OsTrustedFunctionParameterDataType"!], TYPEDEF, OS_VAR) [!"node:name(.)"!];
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!ENDINDENT!][!//
        } TRUSTED_[!"OsTrustedFunctionName"!]ParamList;

    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
extern const OsServices_ConfigType OsServices_TrustedFunctionRefs[OS_SERVICE_FUNC_TOTAL_NUM + 1U];
/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
    [!LOOP "node:order(./OsApplicationTrustedFunction/*,'@index')"!][!//
        extern FUNC(void, OS_CODE) TRUSTED_[!"OsTrustedFunctionName"!]
        (
            [!INDENT "4"!][!//
            TrustedFunctionIndexType FunctionIndex,
            TrustedFunctionParameterRefType FuncParam
            [!ENDINDENT!][!//
        );

    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
#endif /* OS_SERVICES_LCFG_H_ */

/****************************************************************************************************
**     End of File: Os_services_Lcfg.h                                                                **
****************************************************************************************************/


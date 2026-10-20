/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_services_Lcfg.c
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
#include "datatypes.h"
#include "Compiler.h"
#include "Os_services_Lcfg.h"
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
**                          Private Variable Definitions                                           **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//

[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
    [!LOOP "node:order(./OsApplicationTrustedFunction/*,'@index')"!][!//
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(../../OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
        static TRUSTED_[!"OsTrustedFunctionName"!]ParamList TRUSTED_[!"OsTrustedFunctionName"!]Param;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(../../OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
    [!ENDLOOP!][!//
[!ENDLOOP!][!//


[!LOOP "node:order(./OsApplication/*,'@index')"!][!//
    [!IF "num:i(count(./OsApplicationTrustedFunction/*)) != '0'"!][!//
#define OS_START_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"

    [!ENDIF!][!//
    [!LOOP "node:order(./OsApplicationTrustedFunction/*,'@index')"!][!//
static const OsServices_TFConfigType OsServices_[!"OsTrustedFunctionName"!] =
{
    [!INDENT "4"!][!//
    /* The Application ID belong to . */
    [!"num:i(../../@index)"!],                    /* ApplicationID */
    TRUSTED_[!"OsTrustedFunctionName"!]                  /* Callback */
    [!ENDINDENT!][!//
};

    [!ENDLOOP!][!//
    [!IF "num:i(count(./OsApplicationTrustedFunction/*)) != '0'"!][!//
#define OS_STOP_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"

    [!ENDIF!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

const OsServices_ConfigType  OsServices_TrustedFunctionRefs[OS_SERVICE_FUNC_TOTAL_NUM + 1U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
        [!LOOP "node:order(./OsApplicationTrustedFunction/*,'@index')"!][!//
            {
                [!INDENT "8"!][!//
                (TrustedFunctionParameterRefType)&TRUSTED_[!"OsTrustedFunctionName"!]Param,
                &OsServices_[!"OsTrustedFunctionName"!]
                [!ENDINDENT!][!//
            },
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    {
        [!INDENT "8"!][!//
        NULL_PTR,
        NULL_PTR
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};

#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/






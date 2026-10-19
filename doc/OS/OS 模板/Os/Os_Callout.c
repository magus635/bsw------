/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_Callout.c
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
*  V0.0.1   1-June-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Os.h"
#include "Os_application_Lcfg.h"
#include "Os_isr_Lcfg.h"
#include "Os_ioc_Lcfg.h"
#include "Os_hook.h"
#include "Os_hook_Lcfg.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/


/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
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
FUNC(void, OS_CODE) Core0TrustedFunction
(
    Core0TrustedFunctionType FunctionParams
)
{
    FunctionParams.parameter1 = 0u;
}
FUNC(void, OS_CODE) Core1TrustedFunction
(
    Core1TrustedFunctionType FunctionParams
)
{
    FunctionParams.parameter1 = 1u;
}

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
            [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                
                    void ErrorHook_[!"node:name(.)"!](StatusType Error)
                    {
                        [!INDENT "4"!][!//
                        while(1);
                        [!ENDINDENT!][!//
                    }
                [!ENDIF!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//

                    void StartupHook_[!"node:name(.)"!](void)
                    {

                    }
                [!ENDIF!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//

                    void ShutdownHook_[!"node:name(.)"!](StatusType Error)
                    {

                    }
                [!ENDIF!][!//
            [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS"!][!//
    [!IF "node:value(./OsHooks/OsErrorHook) = 'true'"!][!//
        void ErrorHook(StatusType Error)
        {
            [!INDENT "4"!][!//
            boolean ErrorHookControl;
            Os_HookErrorDetail ErrorInfo;

            GetErrorInformation(&ErrorInfo);
            ErrorHookControl = TRUE;
            while(TRUE == ErrorHookControl)
            {
                    ;
            }
            [!ENDINDENT!][!//
        }
    [!ENDIF!][!//

    [!IF "node:value(./OsHooks/OsStartupHook) = 'true'"!][!//
        void StartupHook(void)
        {

        }
    [!ENDIF!][!//

    [!IF "node:value(./OsHooks/OsShutdownHook) = 'true'"!][!//
        void ShutdownHook(StatusType Error)
        {

        }
    [!ENDIF!][!//

    [!IF "node:value(./OsHooks/OsProtectionHook) = 'true'"!][!//
        ProtectionReturnType ProtectionHook(StatusType Error)
        {
            [!INDENT "4"!][!//
            boolean ProtectionHookControl;
            ProtectionReturnType Reaction;

            Reaction = PRO_IGNORE;
            ProtectionHookControl = TRUE;
            while (ProtectionHookControl)
            {
                    ;
            }
            return Reaction;
            [!ENDINDENT!][!//
        }
    [!ENDIF!][!//

    [!IF "./OsHooks/OsPreTaskHook = 'true'"!][!//
        void PreTaskHook(void)
        {
            
        }
    [!ENDIF!][!//
    
    [!IF "./OsHooks/OsPostTaskHook = 'true'"!][!//
        void PostTaskHook(void)
        {
            
        }
    [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          AUTOSAR Function Definitions                                           **
****************************************************************************************************/



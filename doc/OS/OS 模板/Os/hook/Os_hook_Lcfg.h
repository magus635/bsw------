/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_hook_Lcfg.h
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
#ifndef OS_HOOK_LCFG_H_
#define OS_HOOK_LCFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/
extern const Os_AppHooksConfigType Os_AppHooksConfigSet;
extern Os_HookDynamicType Os_HookDynPro;
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
extern const Os_CoreHooksType Os_Core[!"node:ref(./OsCoreId)/EcucCoreId"!]Hooks;
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
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
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
            [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                    extern void ErrorHook_[!"node:name(.)"!](StatusType Error);

                [!ENDIF!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                    extern void StartupHook_[!"node:name(.)"!](void);

                [!ENDIF!][!//
                [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                    extern void ShutdownHook_[!"node:name(.)"!](StatusType Error);
                    
                [!ENDIF!][!//
            [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS"!][!//
    [!IF "node:value(./OsHooks/OsErrorHook) = 'true'"!][!//
        extern void ErrorHook(StatusType Error);
    [!ENDIF!][!//

    [!IF "node:value(./OsHooks/OsStartupHook) = 'true'"!][!//
        extern void StartupHook(void);
    [!ENDIF!][!//

    [!IF "node:value(./OsHooks/OsShutdownHook) = 'true'"!][!//
        extern void ShutdownHook(StatusType Error);
    [!ENDIF!][!//

    [!IF "node:value(./OsHooks/OsProtectionHook) = 'true'"!][!//
        extern ProtectionReturnType ProtectionHook(StatusType Error);
    [!ENDIF!][!//

    [!IF "./OsHooks/OsPreTaskHook = 'true'"!][!//
        extern void PreTaskHook(void);
    [!ENDIF!][!//
    
    [!IF "./OsHooks/OsPostTaskHook = 'true'"!][!//
        extern void PostTaskHook(void);
    [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
#endif /* OS_HOOK_LCFG_H_ */

/****************************************************************************************************
**     End of File: Os_hook_Lcfg.h                                                                **
****************************************************************************************************/

 
/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_context_Cfg.h
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
*  V0.0.1   6-June-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_CONTEXT_CFG_H_
#define OS_CONTEXT_CFG_H_


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/


/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!VAR "TotalContextNum" = "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
        [!VAR "TotalContextNum" = "$TotalContextNum + count(./OsAppTaskRef/*)"!][!//
        [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
            [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                [!VAR "TotalContextNum" = "$TotalContextNum + 1"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) = node:name(.)"!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                [!VAR "TotalContextNum" = "$TotalContextNum + 1"!][!//
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                [!VAR "TotalContextNum" = "$TotalContextNum + 1"!][!//
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                [!VAR "TotalContextNum" = "$TotalContextNum + 1"!][!//
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                [!VAR "TotalContextNum" = "$TotalContextNum + 1"!][!//
            [!ENDIF!][!//
        [!ELSE!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                [!VAR "TotalContextNum" = "$TotalContextNum + 1"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//
                [!VAR "TotalContextNum" = "$TotalContextNum + 1"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//
                [!VAR "TotalContextNum" = "$TotalContextNum + 1"!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
        [!VAR "CurrentContextAppID"="./@index"!][!//
        [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIoc/*/OsIocCommunication/*,'@index')"!][!//
            [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
                [!IF "(node:value(./OsIocReceiveCallbackEnable) = 'true') and ($CurrentContextAppID = node:ref(./OsIocReceivingOsApplicationRef)/@index)"!][!//
                    [!VAR "TotalContextNum" = "$TotalContextNum + 1"!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!VAR "TotalContextNum" = "$TotalContextNum + count(./OsCoreIdMappingConfig/*)"!]
[!ENDSELECT!][!//
#define FPU_DREGS_NUM                                          (32u)
#define TOTALNUM_OF_CONTEXT                                    ([!"num:i($TotalContextNum)"!]u)

#define OS_CONTEXT_STACK_MONITORING                            (STD_ON)
#define OS_CONTEXT_STACK_MONITORING_FILL_PATTERN               (0xAA55AA55UL)

#define OS_CONTEXT_SYS_MODE                                    (0x1F)
#define OS_CONTEXT_USER_MODE                                   (0x10)
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




#endif /* OS_CONTEXT_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_context_Cfg.h                                                           **
****************************************************************************************************/


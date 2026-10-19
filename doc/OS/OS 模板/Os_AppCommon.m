[!NOCODE!][!//
/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Can_Cfg_Common.m
*
*   Platform             : AUTOSAR
*
*   Peripheral           : MCAN
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.2.2
*   Build Version        : Cortex-R52/THA6206
*
*	Copyright (c) 2021, Beijing Tongfang Microelectroics Co., Ltd.
*   All Rights Reserved.
*
***************************************************************************************************/
[!/**************************************************************************************************
*
*       Variables
*
**************************************************************************************************/!][!//
[!/* avoid multiple inclusion */!][!//
[!IF "not(var:defined('OS_CFG_APPCOMMON_M'))"!][!//
[!VAR "OS_CFG_APPCOMMON_M"="'true'"!][!//

[!VAR "ObjectID"="0"!][!//
[!VAR "AppID"="0"!][!//
[!VAR "IocCbkObjectIDCount"="0"!][!//


[!INDENT "0"!][!//
[!MACRO "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "", "IocCbkObjectIDCount" =""!][!//
    [!NOCODE!][!//
    [!VAR "IocCbkObjectIDCount"="0"!][!//
    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIoc/*/OsIocCommunication/*,'@index')"!][!//
        [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
            [!IF "(node:value(./OsIocReceiveCallbackEnable) = 'true') and (num:i($AppID)= num:i(node:ref(./OsIocReceivingOsApplicationRef)/@index))"!][!//
                [!VAR "IocCbkObjectIDCount" = "$IocCbkObjectIDCount + 1"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//


[!VAR "HookObjectIDCount"="0"!][!//
[!INDENT "0"!][!//
[!MACRO "Os_Calculate_Hook_ObjectCount", "AppID"= "", "HookObjectIDCount" =""!][!//
    [!NOCODE!][!//
    [!VAR "HookObjectIDCount"="0"!][!//
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*[num:i($AppID + 1)]"!][!//
        [!IF "node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) != node:name(.)"!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppErrorHook)) and (node:value(./OsApplicationHooks/OsAppErrorHook) = 'true')"!][!//
                [!VAR "HookObjectIDCount" = "$HookObjectIDCount + 1"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppStartupHook)) and (node:value(./OsApplicationHooks/OsAppStartupHook) = 'true')"!][!//                
                [!VAR "HookObjectIDCount" = "$HookObjectIDCount + 1"!][!//
            [!ENDIF!][!//
            [!IF "(node:exists(./OsApplicationHooks/OsAppShutdownHook)) and (node:value(./OsApplicationHooks/OsAppShutdownHook) = 'true')"!][!//                
                [!VAR "HookObjectIDCount" = "$HookObjectIDCount + 1"!][!//
            [!ENDIF!][!//
        [!ELSE!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsErrorHook) = 'true'"!][!//
                [!VAR "HookObjectIDCount" = "$HookObjectIDCount + 1"!][!//
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsStartupHook) = 'true'"!][!//
                [!VAR "HookObjectIDCount" = "$HookObjectIDCount + 1"!][!//
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsShutdownHook) = 'true'"!][!//
                [!VAR "HookObjectIDCount" = "$HookObjectIDCount + 1"!][!//
            [!ENDIF!][!//
            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsOS/OsHooks/OsProtectionHook) = 'true'"!][!//
                [!VAR "HookObjectIDCount" = "$HookObjectIDCount + 1"!][!//
            [!ENDIF!][!//
            [!VAR "HookObjectIDCount" = "$HookObjectIDCount + 1"!][!//
        [!ENDIF!][!//
    [!ENDSELECT!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!MACRO "Os_Calculate_IocCallBack_ObjectId", "CurrentIocName"= "", "ReceiverAppId" = "", "ObjectId" = ""!][!//
    [!NOCODE!][!//
    [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*,'@index')"!][!//
        [!VAR "CurrentAppId" = "@index"!][!//
        [!VAR "HookObjectIDCount"="0"!][!//
        [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$CurrentAppId","HookObjectIDCount" ="$HookObjectIDCount"!][!//
        [!IF "$CurrentAppId != $ReceiverAppId"!][!//
            [!VAR "IocCbkObjectIDCount"="0"!][!//
            [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$CurrentAppId","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
            [!VAR "ObjectId" = "num:i($ObjectId + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
        [!ELSE!][!//
            [!VAR "ObjectId" = "num:i($ObjectId + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount))"!][!//
            [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsIoc/*/OsIocCommunication/*,'@index')"!][!//
                [!VAR "LoopIocName" = "node:name(.)"!][!//
                [!VAR "FindIocCbk" = "'false'"!][!//
                [!LOOP "node:order(./OsIocReceiverProperties/*,'@index')"!][!//
                    [!IF "(OsIocReceiveCallbackEnable = 'true') and (node:ref(./OsIocReceivingOsApplicationRef)/@index = $ReceiverAppId)"!][!//
                        [!IF "$LoopIocName = $CurrentIocName"!][!//
                            [!VAR "FindIocCbk" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ELSE!][!//
                            [!VAR "ObjectId" = "$ObjectId + 1"!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!IF "$FindIocCbk = 'true'"!][!//
                    [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!MACRO "Os_Calculate_Resource_CeilingPriority", "ResourceName"= "", "CeilingPriority" = ""!][!//
[!NOCODE!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!VAR "FindAssignedIsr" = "'false'"!][!//
    [!LOOP "node:order(./OsIsr/*,'@index')"!][!//
        [!LOOP "node:order(./OsIsrResourceRef/*,'@index')"!][!//
            [!IF "node:name(node:ref(.)) = $ResourceName"!][!//
                [!VAR "FindAssignedIsr" = "'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$FindAssignedIsr = 'true'"!][!//
            [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$FindAssignedIsr = 'true'"!][!//
        [!VAR "CeilingPriority" = "'0xFFFFFFFF'"!][!//
    [!ELSE!][!//
        [!VAR "CeilingPriority" = "0"!][!//
        [!VAR "PriorityResourceCountList" = "''"!][!//
        [!VAR "ResourceCoreID" = "0"!][!//
        [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig/*, '@index')"!][!//
            [!VAR "ResourceCoreID" = "@index"!][!//
            [!VAR "PriorityResourceCountList" = "''"!][!//
            [!VAR "Separator" = "','"!][!//
            [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
            [!LOOP "node:order(./*,'@index')"!][!//
                [!IF "$ResourceCoreID = node:ref(./OsApplicationCoreRef)/@index"!][!//
                    [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                        [!VAR "PriorityIncludecomma" = "concat($Separator, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                        [!IF "not(contains($PriorityResourceCountList, $PriorityIncludecomma))"!][!//
                            [!VAR "PriorityResourceCountList" = "concat($PriorityResourceCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                        [!ENDIF!][!//
                    [!ENDLOOP!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!ENDSELECT!][!//
            [!VAR "Total_PriorityResource" = "num:i(count(text:split($PriorityResourceCountList, $Separator)))"!][!//
            [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsTask/*,'@index')"!][!//
                [!LOOP "node:order(./OsTaskResourceRef/*,'@index')"!][!//
                    [!IF "node:name(node:ref(.)) = $ResourceName"!][!//
                        [!FOR "n" = "0" TO "$Total_PriorityResource - 1"!][!//
                            [!IF "num:order(text:split($PriorityResourceCountList, $Separator))[position() = $n+1] = node:value(../../OsTaskPriority)"!][!//
                                [!IF "num:i($n) > num:i($CeilingPriority)"!][!//
                                    [!VAR "CeilingPriority" = "num:i($n)"!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ENDFOR!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
        [!ENDLOOP!][!//
    [!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDNOCODE!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!ENDIF!][!// avoid multiple inclusion ENDIF
[!ENDNOCODE!][!//

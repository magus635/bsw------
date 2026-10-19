/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_task_Cfg.h
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
#ifndef OS_TASK_CFG_H_
#define OS_TASK_CFG_H_

[!//
[!NOCODE!][!//
[!INCLUDE "Os_AppCommon.m"!][!//
[!ENDNOCODE!][!//
[!//
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/


/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsEvent"!][!//
[!LOOP "node:order(./*,"@index")"!][!//
    #define [!"text:toupper(node:name(.))"!]               ([!"./OsEventMask"!]U)
[!ENDLOOP!][!//
[!ENDSELECT!][!//

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsTask"!][!//
[!LOOP "node:order(./*,"@index")"!][!//
    #define [!"text:toupper(node:name(.))"!]        (TaskType)([!"@index"!]U)
[!ENDLOOP!][!//
[!ENDSELECT!][!//

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsTask"!][!//
#define TOTAL_TASK_NUM      (TaskType)([!"num:i(count(./*))"!])
[!ENDSELECT!][!//
#define INVALID_TASK        TOTAL_TASK_NUM

[!VAR "Separator" = "','"!][!//
[!VAR "CoreID" = "0"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig/*, '@index')"!][!//
    [!VAR "CoreID" = "@index"!][!//
    [!VAR "PriorityCountList" = "''"!][!//
    [!VAR "EveryPriorityCountList" = "''"!][!//
    [!VAR "EveryMaxAllowed" = "''"!][!//
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!IF "$CoreID = node:ref(./OsApplicationCoreRef)/@index"!][!//
            [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                [!VAR "EveryPriorityCountList" = "concat($EveryPriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!VAR "EveryMaxAllowed" =  "concat($EveryMaxAllowed, num:i(node:value(node:ref(.)/OsTaskActivation)), $Separator)"!][!//
                [!VAR "PriorityIncludecomma" = "concat($Separator, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!IF "contains($PriorityCountList, $PriorityIncludecomma)"!][!//
                [!ELSE!][!//
                    [!VAR "PriorityCountList" = "concat($PriorityCountList, node:value(node:ref(.)/OsTaskPriority), $Separator)"!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!VAR "Total_Priority" = "num:i(count(text:split($PriorityCountList, $Separator)))"!][!//
    [!FOR "i" = "0" TO "$Total_Priority - 1"!][!//
        [!VAR "CurrentPriorityTaskNum" = "0"!][!//
        [!FOR "j" = "1" TO "num:i(count(text:split($EveryPriorityCountList, $Separator)))"!][!//
            [!IF "num:order(text:split($PriorityCountList, $Separator))[position() = $i+1] = text:split($EveryPriorityCountList, $Separator)[position()= $j]"!][!//
                [!VAR "CurrentPriorityTaskNum" = "$CurrentPriorityTaskNum + text:split($EveryMaxAllowed, $Separator)[position()= $j]"!][!//
            [!ELSE!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
        [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsResource"!][!//
            [!LOOP "node:order(./*,'@index')"!][!//
                [!IF "(OsResourceProperty = 'LINKED') and (OsResourceLinkedToResScheduler = 'false')"!][!//
                    [!VAR "ResourceCoreRef" = "node:ref(node:ref(node:ref(OsResourceLinkedResourceRef)/OsResourceCoreRef)/OsCoreId)/EcucCoreId"!][!//
                [!ELSE!][!//
                    [!VAR "ResourceCoreRef" = "node:ref(node:ref(OsResourceCoreRef)/OsCoreId)/EcucCoreId"!][!//
                [!ENDIF!][!//
                [!IF "$ResourceCoreRef = $CoreID"!][!//
                    [!VAR "CeilingPriority" = "0"!][!//
                    [!IF "(OsResourceProperty = 'LINKED') and (OsResourceLinkedToResScheduler = 'false')"!][!//
                        [!VAR "ResName" = "node:name(node:ref(OsResourceLinkedResourceRef))"!][!//
                    [!ELSE!][!//
                        [!VAR "ResName" = "node:name(.)"!][!//
                    [!ENDIF!][!//
                    [!CALL "Os_Calculate_Resource_CeilingPriority", "ResourceName"= "$ResName", "CeilingPriority" = "$CeilingPriority"!][!//
                    [!IF "$CeilingPriority = $i"!][!//
                        [!VAR "CurrentPriorityTaskNum" = "$CurrentPriorityTaskNum + 1"!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDSELECT!][!//
    #define PRIORITY[!"$i"!]_CORE[!"$CoreID"!]_QUEUESIZE                           ([!"num:i($CurrentPriorityTaskNum + 1)"!]U)
    [!ENDFOR!][!//
#define TASK_CORE[!"$CoreID"!]_TOTAL_PRIORITY                           ([!"$Total_Priority"!]U)

[!ENDLOOP!][!//
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




#endif /* OS_TASK_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_task_Cfg.h                                                                 **
****************************************************************************************************/


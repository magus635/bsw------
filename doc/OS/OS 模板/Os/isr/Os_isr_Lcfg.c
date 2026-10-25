/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName          : Os_isr_Lcfg.c
*
*   Platform          : AUTOSAR
*
*   BSW Module        : Os
*
*   brief         : xxx
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
**              Revision Control History                           **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date       Author(ID)      SVN_Version     Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)            Initial Version
*
****************************************************************************************************/
[!//
[!NOCODE!][!//
[!INCLUDE "Os_AppCommon.m"!][!//
[!VAR "IsrObjectID"="0"!][!//
[!VAR "FindIsrIDFlag"="'false'"!][!//
[!ENDNOCODE!][!//
[!//
/****************************************************************************************************
**              Includes                                   **
****************************************************************************************************/
#include "Os_isr_Cfg.h"
#include "Os_isr_Lcfg.h"
#include "Os_isr_types.h"
#include "Os_isr.h"
#include "Os_counter_Cfg.h"
/****************************************************************************************************
**              Private Macro Definitions                          **
****************************************************************************************************/

/****************************************************************************************************
**              Private Type Definitions                        **
****************************************************************************************************/

/****************************************************************************************************
**              Private Structure Definitions                       **
****************************************************************************************************/

/****************************************************************************************************
**              Private Variable Definitions                       **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'OsPhysicalCoreId')"!][!//
    [!VAR "CurrentPhysicalCoreId" = "OsPhysicalCoreId"!][!//
    [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
        [!IF "count(./OsAppIsrRef/*) != 0"!][!//
            [!IF "node:ref(OsApplicationCoreRef)/OsPhysicalCoreId = $CurrentPhysicalCoreId"!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!][!//
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                [!ELSE!][!//
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                [!ENDIF!][!//
                    [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
                        [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                            static Os_IsrDynamicType [!"node:name(node:ref(.))"!]_RunningData;
                        [!ENDIF!][!//
                    [!ENDLOOP!][!//
                [!IF "node:value(./OsTrusted) = 'true'"!][!//
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                [!ELSE!][!//
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_32
#include "Os_memmap.h"
                [!ENDIF!][!//
                
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**              Global Variable Definitions                        **
****************************************************************************************************/

/****************************************************************************************************
**              Private Constant Definitions                        **
****************************************************************************************************/
[!VAR "AllISRInApp" = "','"!][!//
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!VAR "TPIsrPriority" = "31"!][!//
[!VAR "CurrentAppObjectCnt" = "0"!][!//
[!VAR "IsrObjectID" = "0"!][!//
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'@index')"!][!//
        [!IF "node:exists(./OsTpCounterRef)"!][!//
            [!IF "@index = 0"!][!//
                [!VAR "TPIsrPriority" = "node:ref(node:ref(OsTpCounterRef)/OsTimerTypeIsrRef)/OsIsrPriority"!][!//
            [!ELSE!][!//
                [!IF "node:ref(node:ref(OsTpCounterRef)/OsTimerTypeIsrRef)/OsIsrPriority != $TPIsrPriority"!][!//
                    [!ERROR!][!//
                        ERROR:The priority of tp Isrs must be same.
                    [!ENDERROR!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
        [!IF "num:i(count(./OsAppIsrRef/*)) != '0'"!][!//
#define OS_START_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"
        [!ENDIF!][!//

        [!VAR "IsrObjectID"="num:i($IsrObjectID + count(./OsAppTaskRef/*))"!][!//
        [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
            [!IF "contains($AllISRInApp, concat(',', node:name(node:ref(.)), ','))"!][!//
                [!ERROR!][!//
                    ERROR:The [!"node:name(node:ref(.))"!] ISR is multi referenced in [!"node:name(./../..)"!].
                [!ENDERROR!][!//
            [!ENDIF!][!//
            [!IF "(node:value(../../OsTrusted) = 'false') and (node:ref(.)/OsIsrCategory = 'CATEGORY_1')"!][!//
                [!ERROR!][!//
                    ERROR:The [!"node:name(node:ref(.))"!] must belong to a trusted app.
                [!ENDERROR!][!//
            [!ENDIF!][!//
            [!VAR "AllISRInApp" = "concat($AllISRInApp, node:name(node:ref(.)), ',')"!][!//
            [!VAR "CurrentIsrName" = "node:name(node:ref(.))"!][!//
            [!VAR "CurrentIsrSource" = "node:ref(.)/OsIsrInterruptSource"!][!//
            [!VAR "CurrentCore" = "num:i(node:ref(../../OsApplicationCoreRef)/OsPhysicalCoreId)"!][!//
            [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*,'@index')"!][!//
                [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
                    [!IF "($CurrentIsrName != node:name(node:ref(.))) and ($CurrentIsrSource = num:i(node:ref(.)/OsIsrInterruptSource))"!][!//
                        [!IF "$CurrentIsrSource < 32"!][!//
                            [!IF "$CurrentCore = num:i(node:ref(../../OsApplicationCoreRef)/OsPhysicalCoreId)"!][!//
                                [!ERROR!][!//
                                    ERROR:The [!"node:name(node:ref(.))"!] ISR and [!"$CurrentIsrName"!] ISR have the same source.
                                [!ENDERROR!][!//
                            [!ENDIF!][!//
                        [!ELSE!][!//
                            [!ERROR!][!//
                                ERROR:The [!"node:name(node:ref(.))"!] ISR and [!"$CurrentIsrName"!] ISR have the same source.
                            [!ENDERROR!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDLOOP!][!//
            [!IF "(node:value(../../../../OsOS/OsScalabilityClass) = 'SC2') or (node:value(../../../../OsOS/OsScalabilityClass) = 'SC4')"!][!//
                [!VAR "CurrentIsrName" = "node:name(node:ref(.))"!][!//
                [!VAR "IsTpIsr" = "'false'"!][!//
                [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig/*,'@index')"!][!//
                    [!IF "node:exists(./OsTpCounterRef)"!][!//
                        [!IF "$CurrentIsrName = node:name(node:ref(node:ref(OsTpCounterRef)/OsTimerTypeIsrRef))"!][!//
                            [!VAR "IsTpIsr" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!IF "$IsTpIsr = 'false'"!][!//
                    [!IF "node:ref(.)/OsIsrPriority <= $TPIsrPriority"!][!//
                        [!ERROR!][!//
                            ERROR:The priority of tp Isr must be the highest.
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            static const Os_IsrConfigType [!"node:name(node:ref(.))"!]_isr =
            {
                [!INDENT "4"!][!//
                /* isrHWConfig */
                {
                    [!INDENT "8"!][!//
                    [!"node:ref(.)/OsIsrPriority"!]U,                  /* Priority */
                    [!IF "node:value(../../../../OsResourceSubderivative) = 'Os_SC300'"!][!//
                    0,                               /* Group */
                    0,                               /* TriggerMethod */
                    [!ELSE!][!//
                    OS_ISR_INTERRUPTGROUP_[!"node:ref(.)/OsIsrSrcAssignedTo"!],    /* Group */
                    OS_ISR_TRIGGERMETHOD_[!"node:ref(.)/OsIsrTriggerMethod"!],    /* TriggerMethod */
                    [!ENDIF!][!//
                    [!"text:toupper(node:ref(.)/OsIsrInitialEnableInterruptSource)"!],               /* Enable */
                    [!"node:ref(.)/OsIsrInterruptSource"!]U,                 /* IntID */
                    [!"num:i(node:ref(../../OsApplicationCoreRef)/OsPhysicalCoreId)"!]U                  /* PhysicalCoreID */
                    [!ENDINDENT!][!//
                },
                [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!]OS_INTERRUPTTYPE_CAT2[!ELSE!]OS_INTERRUPTTYPE_CAT1[!ENDIF!],          /* IntType */
                [!"node:ref(.)/@index"!]U,                     /* ISRID */
                [!"num:i($IsrObjectID)"!]UL,                    /* ObjectID */
                [!"text:toupper(node:ref(.)/IsCrossCoreServiceCallIsr)"!],                   /* isCrossCore */
                [!IF "not(node:empty(node:ref(.)/OsIsrHandler))"!][!//
                    (uint32)&[!"node:ref(.)/OsIsrHandler"!],                             /* InterruptHandlerAddress */
                [!ELSE!][!//
                    0UL,                                         /* InterruptHandlerAddress */
                [!ENDIF!][!//
                [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                    &[!"node:name(node:ref(.))"!]_RunningData                 /* Isr running data */
                [!ELSE!][!//
                    NULL_PTR                             /* Isr running data */
                [!ENDIF!][!//
                [!VAR "IsrObjectID" = "$IsrObjectID + 1"!][!//
                [!ENDINDENT!][!//
            };
        [!ENDLOOP!][!//
        [!VAR "AppID"="num:i(./@index)"!][!//
        [!VAR "IocCbkObjectIDCount"="0"!][!//
        [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
        [!VAR "HookObjectIDCount"="0"!][!//
        [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
        [!VAR "CurrentAppObjectCnt" = "num:i($CurrentAppObjectCnt + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
        [!VAR "IsrObjectID" = "$CurrentAppObjectCnt"!][!//
        [!IF "num:i(count(./OsAppIsrRef/*)) != '0'"!][!//
#define OS_STOP_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"

        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**              Global Constant Definitions                        **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'OsPhysicalCoreId')"!][!//
[!VAR "CurrentCore" = "num:i(OsPhysicalCoreId)"!][!//
#define OS_START_SEC_CONFIG_DATA_QM_CORE[!"num:i($CurrentCore)"!]_UNSPECIFIED
#include "Os_memmap.h"

static const Os_IsrConfigRefType Os_Core[!"$CurrentCore"!]_InternalIntVecTable[OS_ISR_INTERNALINT_TOTAL_NUM] =
{
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!IF "node:value(./OsResourceSubderivative) = 'Os_SC300'"!][!//
        [!VAR "TotalIntTableNum" = "num:i(15)"!][!//
    [!ELSE!][!//
        [!VAR "TotalIntTableNum" = "num:i(31)"!][!//
    [!ENDIF!][!//
        [!FOR "IntVecTableCount" = "num:i(0)" TO "$TotalIntTableNum"!][!//
        [!VAR "FindIsrFlag"="'false'"!][!//
        [!INDENT "4"!][!//
        [!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication/*,'@index')"!][!//
            [!IF "$CurrentCore = node:ref(OsApplicationCoreRef)/OsPhysicalCoreId"!][!//
                [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
                    [!IF "node:ref(.)/OsIsrInterruptSource = $IntVecTableCount"!][!//
                        &[!"node:name(node:ref(.))"!]_isr[!IF "$IntVecTableCount < 31"!],[!ENDIF!]
                        [!VAR "FindIsrFlag"="'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDIF!][!//
            [!IF "FindIsrFlag = 'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "$FindIsrFlag = 'false'"!][!//
            NULL_PTR[!IF "$IntVecTableCount < 31"!],[!ENDIF!]
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    [!ENDFOR!][!//
    [!ENDSELECT!][!//
};

#define OS_STOP_SEC_CONFIG_DATA_QM_CORE[!"num:i($CurrentCore)"!]_UNSPECIFIED
#include "Os_memmap.h"

[!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

P2CONST(Os_IsrConfigRefType, AUTOMATIC, OS_CONST) Os_Cores_InternalIntVecTable[OS_KERNEL_MAX_CORE_NUM] =
{
[!INDENT "4"!][!//
[!VAR "PhysicalCoreUsed" = "''"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'num:i(@index)')"!][!//
    [!VAR "PhysicalCoreUsed" = "concat($PhysicalCoreUsed, OsPhysicalCoreId)"!][!//
[!ENDLOOP!][!//
[!FOR "CoreNumCount" = "num:i(0)" TO "num:i(ecu:get('OsResource.NumOfCores') - 1)"!][!//
    [!IF "contains($PhysicalCoreUsed, $CoreNumCount)"!][!//
        Os_Core[!"num:i($CoreNumCount)"!]_InternalIntVecTable[!IF "$CoreNumCount < ecu:get('OsResource.NumOfCores') - 1"!],[!ENDIF!]
    [!ELSE!][!//
        NULL_PTR[!IF "$CoreNumCount < ecu:get('OsResource.NumOfCores') - 1"!],[!ENDIF!]
    [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//
};
#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

#define OS_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

const Os_IsrConfigRefType Os_PeripheralIntVecTable[OS_ISR_SPI_TOTAL_NUM] = 
{
[!IF "node:value(./OsResourceSubderivative) = 'Os_SC300'"!][!//
    [!VAR "TotalPeripheralIntTableNum" = "num:i(255)"!][!//
[!ELSE!][!//
    [!VAR "TotalPeripheralIntTableNum" = "num:i(991)"!][!//
[!ENDIF!][!//
[!FOR "IntVecTableCount" = "$TotalIntTableNum + 1" TO "$TotalPeripheralIntTableNum"!][!//
    [!VAR "FindIsrFlag"="'false'"!][!//
    [!INDENT "4"!][!//
    [!LOOP "node:order(./OsIsr/*,'num:i(@index)')"!][!//
        [!VAR "ISRName" = "concat(',',node:name(.),',')"!][!//
        [!IF "contains($AllISRInApp, $ISRName)"!][!//
        [!ELSE!][!//
            [!ERROR!][!//
                ERROR:The [!"node:name(.)"!] ISR is not referenced in any application.
            [!ENDERROR!][!//
        [!ENDIF!][!//
        [!IF "OsIsrInterruptSource = $IntVecTableCount"!][!//
            &[!"node:name(.)"!]_isr[!//
            [!IF "$IntVecTableCount < 991"!][!//
                ,
            [!ENDIF!][!//
            [!VAR "FindIsrFlag"="'true'"!][!//
            [!BREAK!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!IF "$FindIsrFlag = 'false'"!][!//
        NULL_PTR[!IF "$IntVecTableCount < 991"!],[!ENDIF!]
    [!ENDIF!][!//
    [!ENDINDENT!][!//
[!ENDFOR!][!//
};
[!ENDSELECT!][!//
[!ENDINDENT!][!//

#define OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
[!IF "OsResourceSubderivative != 'Os_SC300'"!][!//
    const uint32 Os_IsrGICAddr[OS_KERNEL_MAX_CORE_NUM] =
    {
        [!INDENT "4"!][!//
        [!IF "OsResourceSubderivative = 'Os_THA6206'"!][!//
            0xF0000000U,
            0xF0000000U
        [!ELSEIF "OsResourceSubderivative = 'Os_THA610X'"!][!//
            0xF0000000U
        [!ELSE!][!//
            0xF0000000U,
            0xF0000000U,
            0xF0200000U,
            0xF0200000U
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    };
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

const Os_IsrConfigRefType Os_IsrConfigSet[OS_ISR_TOTAL_NUM] =
{
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!INDENT "4"!][!//
    [!LOOP "node:order(./OsIsr/*,'num:i(@index)')"!][!//
        &[!"node:name(.)"!]_isr[!IF "not(node:islast(.))"!],[!ENDIF!]
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
};

#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

/****************************************************************************************************
**              Private Function Declarations                      **
****************************************************************************************************/

/****************************************************************************************************
**              Private Function Definitions                       **
****************************************************************************************************/

/****************************************************************************************************
**              Global Function Definitions                        **
****************************************************************************************************/






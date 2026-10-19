/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_kernel_Cfg.h
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
#ifndef OS_KERNEL_CFG_H_
#define OS_KERNEL_CFG_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
[!//
[!NOCODE!][!//
[!INCLUDE "Os_AppCommon.m"!][!//
[!ENDNOCODE!][!//
[!//
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!INDENT "0"!][!//
[!VAR "CurrentCoreID"="0"!][!//
[!VAR "CurrentCoreAppNumCount"="0"!][!//
[!VAR "CurrentCoreAppStartNum"="0"!][!//
[!VAR "CurrentCoreContextNumCount"="0"!][!//
[!VAR "CurrentCoreContextStartNum"="0"!][!//
[!VAR "CurrentCoreTpObjectNumCount"="0"!][!//
[!VAR "CurrentCoreTpObjectStartNum"="0"!][!//
[!VAR "CurrentCoreMpRegionNumCount"="0"!][!//
[!VAR "CurrentCoreMpAppRegionNumCount"="0"!][!//
[!VAR "CurrentCoreMpObjRegionNumCount"="0"!][!//
[!VAR "CurrentCoreStartOsInitFunctionObjectIDNumCount"="0"!][!//
[!VAR "CurrentCoreKernelApplicationNum"="0"!][!//
[!VAR "CurrentCoreResourceNumCount"="0"!][!//
[!VAR "CurrentCoreResourceStartNum"="0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//


#define OS_CORE_ID_0                                ((CoreIdType)0)
#define OS_CORE_ID_1                                ((CoreIdType)1)
    [!LOOP "node:order(./OsCoreIdMappingConfig/*,'num:i(node:ref(./OsCoreId)/EcucCoreId)')"!][!//
        [!VAR "CurrentCoreID"="num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
        [!VAR "CurrentCoreAppNumCount"="0"!][!//
        [!VAR "CurrentCoreContextNumCount"="0"!][!//
        [!VAR "CurrentCoreTpObjectNumCount"="0"!][!//
        [!VAR "CurrentCoreMpRegionNumCount"="0"!][!//
        [!VAR "CurrentCoreMpAppRegionNumCount"="0"!][!//
        [!VAR "CurrentCoreMpObjRegionNumCount"="0"!][!//
        [!VAR "CurrentCoreKernelApplicationNum"="0"!][!//
        [!VAR "CurrentCoreResourceNumCount"="0"!][!//
        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
            [!IF "num:i($CurrentCoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId)"!][!//
                [!IF "num:i($CurrentCoreMpAppRegionNumCount) < num:i(count(./OsAppMemoryProtection/*))"!][!//
                    [!VAR "CurrentCoreMpAppRegionNumCount" = "count(./OsAppMemoryProtection/*)"!][!//
                [!ENDIF!][!//
                [!VAR "AppID"="num:i(./@index)"!][!//
                [!VAR "IocCbkObjectIDCount"="0"!][!//
                [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
                [!VAR "HookObjectIDCount"="0"!][!//
                [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
                [!VAR "CurrentCoreAppNumCount" = "$CurrentCoreAppNumCount + 1"!][!//
                [!VAR "CurrentAppIsr2Num" = "0"!][!//
                [!LOOP "node:order(./OsAppIsrRef/*,"@index")"!][!//
                    [!IF "node:value(node:ref(.)/OsIsrCategory) = 'CATEGORY_2'"!][!//
                        [!VAR "CurrentAppIsr2Num" = "$CurrentAppIsr2Num + 1"!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!VAR "CurrentCoreContextNumCount"="num:i($CurrentCoreContextNumCount + count(./OsAppTaskRef/*) + num:i($CurrentAppIsr2Num) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
                [!LOOP "node:order(./OsAppTaskRef/*,"@index")"!][!//
                    [!IF "node:exists(node:ref(.)/OsTaskTimingProtection/*[1])"!][!//
                        [!VAR "CurrentCoreTpObjectNumCount" = "$CurrentCoreTpObjectNumCount + 1"!][!//
                    [!ENDIF!][!//
                    [!IF "(count(node:ref(.)/OsTaskMemoryProtection/*) != 0) and (num:i($CurrentCoreMpObjRegionNumCount) < num:i(count(node:ref(.)/OsTaskMemoryProtection/*)))"!][!//
                    [!VAR "CurrentCoreMpObjRegionNumCount"="num:i(count(node:ref(.)/OsTaskMemoryProtection/*))"!][!//                    
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!LOOP "node:order(./OsAppIsrRef/*,"@index")"!][!//
                    [!IF "node:exists(node:ref(.)/OsIsrTimingProtection/*[1])"!][!//
                        [!VAR "CurrentCoreTpObjectNumCount" = "$CurrentCoreTpObjectNumCount + 1"!][!//
                    [!ENDIF!][!//
                    [!IF "(count(node:ref(.)/OsIsrMemoryProtection/*) != 0) and (num:i($CurrentCoreMpObjRegionNumCount) < num:i(count(node:ref(.)/OsIsrMemoryProtection/*)))"!][!//
                    [!VAR "CurrentCoreMpObjRegionNumCount"="num:i(count(node:ref(.)/OsIsrMemoryProtection/*))"!][!//                    
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!VAR "CurrentCoreStartOsInitFunctionObjectIDNumCount"="0"!][!//
        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
            [!VAR "AppID"="num:i(./@index)"!][!//
            [!VAR "IocCbkObjectIDCount"="0"!][!//
            [!CALL "Os_Calculate_IocCallBack_ObjectCount", "AppID"= "$AppID","IocCbkObjectIDCount" ="$IocCbkObjectIDCount"!][!//
            [!VAR "HookObjectIDCount"="0"!][!//
            [!CALL "Os_Calculate_Hook_ObjectCount", "AppID"= "$AppID","HookObjectIDCount" ="$HookObjectIDCount"!][!//
            [!IF "(node:name(node:ref(node:ref(./OsApplicationCoreRef)/OsKernelApplication)) = node:name(.)) and (num:i($CurrentCoreID) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId))"!][!//
                [!VAR "CurrentCoreKernelApplicationNum"="num:i($AppID)"!][!//
                [!VAR "CurrentCoreStartOsInitFunctionObjectIDNumCount"="num:i($CurrentCoreStartOsInitFunctionObjectIDNumCount + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) - 1)"!][!//
                [!BREAK!][!//
            [!ELSE!][!//
                [!VAR "CurrentCoreStartOsInitFunctionObjectIDNumCount"="num:i($CurrentCoreStartOsInitFunctionObjectIDNumCount + count(./OsAppTaskRef/*) + count(./OsAppIsrRef/*) + count(./OsAppCounterRef/*) + count(./OsAppAlarmRef/*) + count(./OsAppScheduleTableRef/*) + num:i($HookObjectIDCount) + num:i($IocCbkObjectIDCount))"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!LOOP "node:order(../../OsResource/*,'@index')"!][!//
            [!IF "(OsResourceProperty = 'LINKED') and (OsResourceLinkedToResScheduler = 'false')"!][!//
                [!VAR "ResourceCoreRef" = "node:ref(node:ref(node:ref(OsResourceLinkedResourceRef)/OsResourceCoreRef)/OsCoreId)/EcucCoreId"!][!//
            [!ELSE!][!//
                [!VAR "ResourceCoreRef" = "node:ref(node:ref(OsResourceCoreRef)/OsCoreId)/EcucCoreId"!][!//
            [!ENDIF!][!//
            [!IF "$ResourceCoreRef = $CurrentCoreID"!][!//
                [!VAR "CurrentCoreResourceNumCount"="$CurrentCoreResourceNumCount + 1"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!IF "../../OsOS/OsUseResScheduler = 'true'"!][!//
            [!VAR "CurrentCoreResourceNumCount"="$CurrentCoreResourceNumCount + 1"!][!//
        [!ENDIF!][!//
        [!VAR "CurrentCoreMpRegionNumCount"="num:i(count(./OsCoreMemoryProtection/*))"!][!//
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_APPLICATION_COUNT_NUMBER                ((uint32)[!"num:i($CurrentCoreAppNumCount)"!])
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_APPLICATION_START_NUMBER                ((uint32)[!"num:i($CurrentCoreAppStartNum)"!])
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_CONTEXT_COUNT_NUMBER                    ((uint32)[!"num:i($CurrentCoreContextNumCount)"!])   
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_CONTEXT_START_NUMBER                    ((uint32)[!"num:i($CurrentCoreContextStartNum)"!])
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_TPOBJECT_COUNT_NUMBER                   ((uint32)[!"num:i($CurrentCoreTpObjectNumCount)"!])
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_TPOBJECT_START_NUMBER                   ((uint32)[!"num:i($CurrentCoreTpObjectStartNum)"!])
[!IF "node:exists(./OsTpCounterRef)"!][!//
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_TPOBJECT_USED_COUNTERID                 ((uint32)[!"num:i(node:ref(./OsTpCounterRef)/@index)"!])
[!ENDIF!][!//
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_MPU_CORE_REGION_MAX_NUMBER              ((uint32)[!"num:i($CurrentCoreMpRegionNumCount)"!]) 
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_MPU_APP_REGION_MAX_NUMBER               ((uint32)[!"num:i($CurrentCoreMpAppRegionNumCount)"!])  
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_MPU_OBJECT_REGION_MAX_NUMBER            ((uint32)[!"num:i($CurrentCoreMpObjRegionNumCount)"!])
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_STARTOS_INITFUNCTION_OBJECT_NUMBER      ((uint32)[!"num:i($CurrentCoreStartOsInitFunctionObjectIDNumCount)"!])
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_KERNEL_APPLICATION_NUMBER               ((uint32)[!"num:i($CurrentCoreKernelApplicationNum)"!])
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_RESOURCE_COUNT_NUMBER                   ((uint32)[!"num:i($CurrentCoreResourceNumCount)"!])
#define OS_KERNEL_CORE[!"num:i($CurrentCoreID)"!]_RESOURCE_START_NUMBER                   ((uint32)[!"num:i($CurrentCoreResourceStartNum)"!])

        [!VAR "CurrentCoreAppStartNum"="num:i($CurrentCoreAppStartNum + $CurrentCoreAppNumCount)"!][!//
        [!VAR "CurrentCoreContextStartNum"="num:i($CurrentCoreContextStartNum + $CurrentCoreContextNumCount)"!][!//
        [!VAR "CurrentCoreTpObjectStartNum"="num:i($CurrentCoreTpObjectStartNum + $CurrentCoreTpObjectNumCount)"!][!//
        [!VAR "CurrentCoreResourceStartNum"="num:i($CurrentCoreResourceStartNum + $CurrentCoreResourceNumCount)"!][!//
    [!ENDLOOP!][!//

#define OS_CORE_ID_MASTER                     ([!"ecu:get('OsResource.MasterCore')"!])
#define OS_KERNEL_MAX_CORE_NUM                ([!"ecu:get('OsResource.NumOfCores')"!]U)
#define OS_KERNEL_TOTAL_USED_NUM              ([!"num:i(count(/AUTOSAR/TOP-LEVEL-PACKAGES/EcuC/ELEMENTS/EcuC/EcucHardware/EcucCoreDefinition/*))"!]UL)
#define OS_CORE_ID_INVAILD_NUM                ((CoreIdType)[!"num:i(count(/AUTOSAR/TOP-LEVEL-PACKAGES/EcuC/ELEMENTS/EcuC/EcucHardware/EcucCoreDefinition/*))"!])
[!VAR "CoreID_Mask"="0"!][!//
[!VAR "CoreID_CombineMask"="'0x0'"!][!//
[!LOOP "node:order(./OsCoreIdMappingConfig/*,'num:i(node:ref(./OsCoreId)/EcucCoreId)')"!][!//
[!VAR "CoreID_Mask"="num:inttohex(bit:shl(num:i(1),num:i(node:ref(./OsCoreId)/EcucCoreId)),8)"!][!//
[!VAR "CoreID_CombineMask"="num:inttohex(bit:or(num:hextoint($CoreID_CombineMask),num:hextoint($CoreID_Mask)),8)"!][!//
[!ENDLOOP!][!//
#define OS_KERNEL_COMBINE_COREID_MASK         ((uint32)[!"$CoreID_CombineMask"!])

[!IF "./OsOS/OsScalabilityClass = 'SC2'"!][!//
#define OS_KERNEL_SUPPORT_SC2
[!ENDIF!][!//
[!IF "./OsOS/OsScalabilityClass = 'SC3'"!][!//
#define OS_KERNEL_SUPPORT_SC3
[!ENDIF!][!//
[!IF "./OsOS/OsScalabilityClass = 'SC4'"!][!//
#define OS_KERNEL_SUPPORT_SC2
#define OS_KERNEL_SUPPORT_SC3
[!ENDIF!][!//

[!IF "./OsOS/OsStatus = 'EXTENDED'"!][!//
#define OS_STATUS_EXTENDED          (STD_ON)
[!ELSE!][!//
#define OS_STATUS_EXTENDED          (STD_OFF)
[!ENDIF!][!//

[!IF "node:value(./OsOS/OsUseArti) = 'true'"!][!//
#define OS_STATUS_USEARTI           (STD_ON)
[!ELSE!][!//
#define OS_STATUS_USEARTI           (STD_OFF)
[!ENDIF!][!//


[!IF "./OsOS/OsUseServiceProtection = 'true'"!][!//
#define OS_SERVICE_PROTECTION          (STD_ON)
[!ELSE!][!//
#define OS_SERVICE_PROTECTION          (STD_OFF)
[!ENDIF!][!//

[!ENDSELECT!][!//
[!ENDINDENT!][!//

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


#endif /* OS_KERNEL_CFG_H_ */

/****************************************************************************************************
**     End of File: Os_kernel_Cfg.h                                                                 **
****************************************************************************************************/



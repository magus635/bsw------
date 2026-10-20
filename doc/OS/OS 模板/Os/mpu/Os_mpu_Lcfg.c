/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_mpu_Lcfg.c
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
#include "Os_mpu_types.h"
#include "Os_mpu_Cfg.h"
#include "Os_mpu_Lcfg.h"

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

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

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        extern uint32 Image$$[!"node:name(.)"!]$$Base;
        extern uint32 Image$$[!"node:name(.)"!]$$ZI$$Limit;
        
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsCoreIdMappingConfig"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
#define OS_START_SEC_CONST_QM_CORE[!"num:i(./OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"
        [!IF "count(./OsCoreMemoryProtection/*) != 0"!][!//

        const Os_HalMpuRegionType OsMpu_ConfigSet_Core[!"node:value(node:ref(./OsCoreId)/EcucCoreId)"!]_Regions[[!"num:i(count(./OsCoreMemoryProtection/*))"!]] =
        {
          [!INDENT "4"!][!//
          [!VAR "RegionNum" = "0"!][!//
          [!LOOP "node:order(./OsCoreMemoryProtection/*,'@index')"!][!//
            {
                [!INDENT "8"!][!//
                [!"num:inttohex($RegionNum,8)"!],          /* RegionNumber */
                [!VAR "RegionNum" = "$RegionNum + 1"!][!//
                [!IF "node:name(./OsCoreMemoryProtectionChoice) = 'RegionSelect'"!][!//
                    (uint32)([!"concat( '&Image$$', node:name(node:ref(./OsCoreMemoryProtectionChoice/MemoryBlockRef)), '$$Base')"!]),            /* RegionBaseAddress */
                [!ELSE!][!//
                    (uint32)[!"num:inttohex(node:value(./OsCoreMemoryProtectionChoice/OsCoreMemoryProtectionStartAddress),8)"!]U,          /* RegionBaseAddress */
                [!ENDIF!][!//
                [!IF "node:name(./OsCoreMemoryProtectionChoice) = 'RegionSelect'"!][!//
                    (uint32)([!"concat( '&Image$$', node:name(node:ref(./OsCoreMemoryProtectionChoice/MemoryBlockRef)), '$$ZI$$Limit')"!]),                /* RegionEndAddress */
                [!ELSE!][!//
                    (uint32)([!"num:inttohex(node:value(./OsCoreMemoryProtectionChoice/OsCoreMemoryProtectionEndAddress),8)"!]U),                /* RegionEndAddress */
                [!ENDIF!][!//
                [!"./CoreRegionReadWriteAccess"!]|[!"CoreExecutionAccess"!],
                MPU_REGION_ENABLE
                [!ENDINDENT!][!//
            },
          [!ENDLOOP!][!//
          [!ENDINDENT!][!//
        };

        const Os_MpuConfigType OsMpu_ConfigSet_Core[!"node:value(node:ref(./OsCoreId)/EcucCoreId)"!] =
        {
            [!INDENT "4"!][!//
            (uint32)[!"num:i(count(./OsCoreMemoryProtection/*))"!],                  /* MpuRegionCount */
            OsMpu_ConfigSet_Core[!"node:value(node:ref(./OsCoreId)/EcucCoreId)"!]_Regions                /* MpuRegions */
            [!ENDINDENT!][!//
        };

        const Os_HalStackConfigAddressType OsMpu_ConfigSet_OsStackCore[!"node:value(node:ref(./OsCoreId)/EcucCoreId)"!] = 
        {
            [!INDENT "4"!][!//
            (uint32)(&Image$$OS_CORE[!"node:value(node:ref(./OsCoreId)/EcucCoreId)"!]_STACK$$Base),          /* StackBaseAddress */
            (uint32)(&Image$$OS_CORE[!"node:value(node:ref(./OsCoreId)/EcucCoreId)"!]_STACK$$ZI$$Limit)           /* StackEndAddress */
            [!ENDINDENT!][!//
        };

        const Os_HalCoreMpuConfigType OsMpu_ConfigSetCore[!"node:value(node:ref(./OsCoreId)/EcucCoreId)"!] = 
        {
            [!INDENT "4"!][!//
            &OsMpu_ConfigSet_Core[!"node:value(node:ref(./OsCoreId)/EcucCoreId)"!],
            &OsMpu_ConfigSet_OsStackCore[!"node:value(node:ref(./OsCoreId)/EcucCoreId)"!]
            [!ENDINDENT!][!//
        };
        [!ENDIF!][!//
#define OS_STOP_SEC_CONST_QM_CORE[!"num:i(./OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"  
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
#define OS_START_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"
        [!IF "count(./OsAppMemoryProtection/*) != 0"!][!//
        const Os_HalMpuRegionType OsMpu_ConfigSet_[!"node:name(.)"!]_Regions[[!"num:i(count(./OsAppMemoryProtection/*))"!]] =
        {
        [!INDENT "4"!][!//
        [!VAR "RegionNum" = "num:i(count(node:ref(./OsApplicationCoreRef)/OsCoreMemoryProtection/*))"!][!//
        [!LOOP "node:order(./OsAppMemoryProtection/*,'@index')"!][!//
            {
                [!INDENT "8"!][!//
                [!"num:inttohex($RegionNum,8)"!],          /* RegionNumber */
                [!VAR "RegionNum" = "$RegionNum + 1"!][!//
                [!IF "node:name(./OsAppMemoryProtectionChoice) = 'RegionSelect'"!][!//
                    (uint32)([!"concat( '&Image$$', node:name(node:ref(./OsAppMemoryProtectionChoice/MemoryBlockRef)), '$$Base')"!]),            /* RegionBaseAddress */
                [!ELSE!][!//
                    (uint32)[!"num:inttohex(node:value(./OsAppMemoryProtectionChoice/OsAppMemoryProtectionStartAddress),8)"!]U,          /* RegionBaseAddress */
                [!ENDIF!][!//
                [!IF "node:name(./OsAppMemoryProtectionChoice) = 'RegionSelect'"!][!//
                    (uint32)([!"concat( '&Image$$', node:name(node:ref(./OsAppMemoryProtectionChoice/MemoryBlockRef)), '$$ZI$$Limit')"!]),                /* RegionEndAddress */
                [!ELSE!][!//
                    (uint32)([!"num:inttohex(node:value(./OsAppMemoryProtectionChoice/OsAppMemoryProtectionEndAddress),8)"!]U),                /* RegionEndAddress */
                [!ENDIF!][!//
                [!"./AppRegionReadWriteAccess"!]|[!"AppExecutionAccess"!],
                MPU_REGION_ENABLE
                [!ENDINDENT!][!//
            },
        [!ENDLOOP!][!//
        [!ENDINDENT!][!//
        };

        const Os_MpuConfigType OsMpu_ConfigSet_[!"node:name(.)"!] =
        {
            [!INDENT "4"!][!//
            (uint32)[!"num:i(count(./OsAppMemoryProtection/*))"!],                /* MpuRegionCount */
            OsMpu_ConfigSet_[!"node:name(.)"!]_Regions                       /* MpuRegions */
            [!ENDINDENT!][!//
        };
        [!ENDIF!][!//
#define OS_STOP_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"    
    [!ENDLOOP!][!//

#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
CONSTP2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST) OsMpu_ConfigSet_ApplicationsRefs[OS_APPLICATION_TOTAL_NUM + 1U] =
{
    [!INDENT "4"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!IF "count(./OsAppMemoryProtection/*) = 0"!][!//
            NULL_PTR,
        [!ELSE!][!//
            &OsMpu_ConfigSet_[!"node:name(.)"!],
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    NULL_PTR
    [!ENDINDENT!][!//
};
#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsTask"!][!//
    [!LOOP "node:order(../OsCoreIdMappingConfig/*,'@index')"!][!//
        [!VAR "CoreRegion" = "num:i(count(./OsCoreMemoryProtection/*))"!][!//
        [!VAR "CurrentCoreIDCheckIndex" = "num:i(node:ref(./OsCoreId)/EcucCoreId)"!][!//
        [!VAR "AppRegion" = "0"!][!//
        [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsApplication"!][!//
            [!LOOP "node:order(./*,'@index')"!][!//
                [!IF "(num:i($AppRegion) < num:i(count(./OsAppMemoryProtection/*))) and (num:i($CurrentCoreIDCheckIndex) = num:i(node:ref(node:ref(./OsApplicationCoreRef)/OsCoreId)/EcucCoreId))"!][!//
                    [!VAR "AppRegion" = "count(./OsAppMemoryProtection/*)"!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDSELECT!][!//
        [!LOOP "node:order(../../OsApplication/*,'@index')"!][!//
#define OS_START_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"
            [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
                [!IF "(count(node:ref(.)/OsTaskMemoryProtection/*) != 0) and (num:i($CurrentCoreIDCheckIndex) = num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId))"!][!//

                const Os_HalMpuRegionType  OsMpu_ConfigSet_[!"node:name(node:ref(.))"!]_Regions[[!"num:i(count(node:ref(.)/OsTaskMemoryProtection/*))"!]] =
                {
                    [!VAR "RegionNum" = "$CoreRegion + $AppRegion"!][!//
                    [!INDENT "4"!][!//
                    [!LOOP "node:order(node:ref(.)/OsTaskMemoryProtection/*,'@index')"!][!//
                        {   
                            [!INDENT "8"!][!//
                            [!"num:inttohex($RegionNum,8)"!],          /* RegionNumber */
                            [!VAR "RegionNum" = "$RegionNum + 1"!][!//
                            [!IF "node:name(./OsTaskMemoryProtectionChoice) = 'RegionSelect'"!][!//
                                (uint32)([!"concat( '&Image$$', node:name(node:ref(./OsTaskMemoryProtectionChoice/MemoryBlockRef)), '$$Base')"!]),            /* RegionBaseAddress */
                            [!ELSE!][!//
                                (uint32)[!"num:inttohex(node:value(./OsTaskMemoryProtectionChoice/OsTaskMemoryProtectionStartAddress),8)"!]U,          /* RegionBaseAddress */
                            [!ENDIF!][!//
                            [!IF "node:name(./OsTaskMemoryProtectionChoice) = 'RegionSelect'"!][!//
                                (uint32)([!"concat( '&Image$$', node:name(node:ref(./OsTaskMemoryProtectionChoice/MemoryBlockRef)), '$$ZI$$Limit')"!]),                /* RegionEndAddress */
                            [!ELSE!][!//
                                (uint32)([!"num:inttohex(node:value(./OsTaskMemoryProtectionChoice/OsTaskMemoryProtectionEndAddress),8)"!]U),                /* RegionEndAddress */
                            [!ENDIF!][!//
                            [!"./TaskRegionReadWriteAccess"!]|[!"TaskExecutionAccess"!],
                            MPU_REGION_ENABLE
                            [!ENDINDENT!][!//
                        },
                    [!ENDLOOP!][!//
                    [!ENDINDENT!][!//
                };

                const Os_MpuConfigType OsMpu_ConfigSet_[!"node:name(node:ref(.))"!] =
                {
                    [!INDENT "4"!][!//
                    (uint32)[!"num:i(count(node:ref(.)/OsTaskMemoryProtection/*))"!],                                         /* MpuRegionCount */
                    OsMpu_ConfigSet_[!"node:name(node:ref(.))"!]_Regions                     /* MpuRegions */
                    [!ENDINDENT!][!//
                };

                [!ENDIF!][!//
                [!IF "(count(node:ref(.)/OsTaskAccessCheck/*) > 0)  and (num:i($CurrentCoreIDCheckIndex) = num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId))"!][!//
                    const Os_AccessRegionConfig OsMpu_AccessCheck_[!"node:name(node:ref(.))"!]_Regions[[!"num:i(count(node:ref(.)/OsTaskAccessCheck/*))"!]] =
                    {
                    [!INDENT "4"!][!//
                    [!LOOP "node:order(node:ref(.)/OsTaskAccessCheck/*,'@index')"!][!//
                        {
                            [!INDENT "8"!][!//
                            [!"num:inttohex(OsTaskAccessCheckStartAddress,8)"!]U,        /* AddressStart */
                            [!"num:inttohex(OsTaskAccessCheckEndAddress,8)"!]U,        /* AddressEnd */ 
                            [!"node:value(./TaskAccessRight)"!]        /* AddressRight */
                            [!ENDINDENT!][!//
                        },
                    [!ENDLOOP!][!//
                    [!ENDINDENT!][!//
                    };

                    const Os_AccessConfigType OsMpu_AccessCheck_[!"node:name(node:ref(.))"!] =
                    {
                        [!INDENT "4"!][!//
                        (uint32)[!"num:i(count(node:ref(.)/OsTaskAccessCheck/*))"!],                                         /* MpuRegionCount */ 
                        OsMpu_AccessCheck_[!"node:name(node:ref(.))"!]_Regions,                     /* MpuRegions */
                        [!ENDINDENT!][!//
                    };
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
                [!IF "(count(node:ref(.)/OsIsrMemoryProtection/*) != 0) and (num:i($CurrentCoreIDCheckIndex) = num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId))"!][!//
                    [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                        const Os_HalMpuRegionType  OsMpu_ConfigSet_[!"node:name(node:ref(.))"!]_Regions[[!"num:i(count(node:ref(.)/OsIsrMemoryProtection/*))"!]] =
                        {
                            [!VAR "RegionNum" = "$CoreRegion + $AppRegion"!][!//
                            [!INDENT "4"!][!//
                            [!LOOP "node:order(node:ref(.)/OsIsrMemoryProtection/*,'@index')"!][!//
                                {   
                                    [!INDENT "8"!][!//
                                    [!"num:inttohex($RegionNum,8)"!],          /* RegionNumber */
                                    [!VAR "RegionNum" = "$RegionNum + 1"!][!//
                                    [!IF "node:name(./OsIsrMemoryProtectionChoice) = 'RegionSelect'"!][!//
                                        (uint32)([!"concat( '&Image$$', node:name(node:ref(./OsIsrMemoryProtectionChoice/MemoryBlockRef)), '$$Base')"!]),            /* RegionBaseAddress */
                                    [!ELSE!][!//
                                        (uint32)[!"num:inttohex(node:value(./OsIsrMemoryProtectionChoice/OsIsrMemoryProtectionStartAddress),8)"!]U,          /* RegionBaseAddress */
                                    [!ENDIF!][!//
                                    [!IF "node:name(./OsIsrMemoryProtectionChoice) = 'RegionSelect'"!][!//
                                        (uint32)([!"concat( '&Image$$', node:name(node:ref(./OsIsrMemoryProtectionChoice/MemoryBlockRef)), '$$ZI$$Limit')"!]),                /* RegionEndAddress */
                                    [!ELSE!][!//
                                        (uint32)([!"num:inttohex(node:value(./OsIsrMemoryProtectionChoice/OsIsrMemoryProtectionEndAddress),8)"!]U),                /* RegionEndAddress */
                                    [!ENDIF!][!//
                                    [!"./IsrRegionReadWriteAccess"!]|[!"IsrExecutionAccess"!],
                                    MPU_REGION_ENABLE
                                    [!ENDINDENT!][!//
                                },
                            [!ENDLOOP!][!//
                            [!ENDINDENT!][!//
                        };

                        const Os_MpuConfigType OsMpu_ConfigSet_[!"node:name(node:ref(.))"!] =
                        {
                            [!INDENT "4"!][!//
                            (uint32)[!"num:i(count(node:ref(.)/OsIsrMemoryProtection/*))"!],                /* MpuRegionCount */
                            &OsMpu_ConfigSet_[!"node:name(node:ref(.))"!]_Regions                       /* MpuRegions */
                            [!ENDINDENT!][!//
                        };
                    [!ENDIF!][!//
                [!ENDIF!][!//
                [!IF "(count(node:ref(.)/OsIsrAccessCheck/*) > 0) and (num:i($CurrentCoreIDCheckIndex) = num:i(node:ref(node:ref(../../OsApplicationCoreRef)/OsCoreId)/EcucCoreId))"!][!//
                    const Os_AccessRegionConfig OsMpu_AccessCheck_[!"node:name(node:ref(.))"!]_Regions[[!"num:i(count(node:ref(.)/OsIsrAccessCheck/*))"!]] =
                    {
                    [!INDENT "4"!][!//
                    [!LOOP "node:order(node:ref(.)/OsIsrAccessCheck/*,'@index')"!][!//
                        {
                            [!INDENT "8"!][!//
                            [!"num:inttohex(OsIsrAccessCheckStartAddress,8)"!]U,        /* AddressStart */
                            [!"num:inttohex(OsIsrAccessCheckEndAddress,8)"!]U,        /* AddressEnd */ 
                            [!"node:value(./IsrAccessRight)"!]        /* AddressRight */
                            [!ENDINDENT!][!//
                        },
                    [!ENDLOOP!][!//
                    [!ENDINDENT!][!//
                    };

                    const Os_AccessConfigType OsMpu_AccessCheck_[!"node:name(node:ref(.))"!] =
                    {
                        [!INDENT "4"!][!//
                        (uint32)[!"num:i(count(node:ref(.)/OsIsrAccessCheck/*))"!],                  /* MpuRegionCount */ 
                        OsMpu_AccessCheck_[!"node:name(node:ref(.))"!]_Regions,        /* MpuRegions */
                        [!ENDINDENT!][!//
                    };

                [!ENDIF!][!//
            [!ENDLOOP!][!//
#define OS_STOP_SEC_CONST_QM_CORE[!"num:i(node:ref(./OsApplicationCoreRef)/OsPhysicalCoreId)"!]_UNSPECIFIED
#include "Os_memmap.h"  
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
CONSTP2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST) OsMpu_ConfigSet_ObjectRefs[OS_MPU_COUNT + 1U] =
{   
    [!INDENT "4"!][!//
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
        [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
            [!IF "count(node:ref(.)/OsTaskMemoryProtection/*) != 0"!][!//
                &OsMpu_ConfigSet_[!"node:name(node:ref(.))"!],
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
            [!IF "count(node:ref(.)/OsIsrMemoryProtection/*) != 0"!][!//
            [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                &OsMpu_ConfigSet_[!"node:name(node:ref(.))"!],
            [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    NULL_PTR
    [!ENDINDENT!][!//
};

CONSTP2CONST(Os_AccessConfigType, TYPEDEF, OS_CONST) OsMpu_AccessCheck_ObjectRefs[OS_MPU_ACCESSCOUNT + 1U] =
{
    [!INDENT "4"!][!//
    [!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os"!][!//
    [!LOOP "node:order(./OsApplication/*,'@index')"!][!//
        [!LOOP "node:order(./OsAppTaskRef/*,'@index')"!][!//
            [!IF "count(node:ref(.)/OsTaskAccessCheck/*) != 0"!][!//
                &OsMpu_AccessCheck_[!"node:name(node:ref(.))"!],
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!LOOP "node:order(./OsAppIsrRef/*,'@index')"!][!//
            [!IF "count(node:ref(.)/OsIsrAccessCheck/*) != 0"!][!//
            [!IF "node:ref(.)/OsIsrCategory = 'CATEGORY_2'"!][!//
                &OsMpu_AccessCheck_[!"node:name(node:ref(.))"!],
            [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    NULL_PTR
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//


[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsPeripheralArea"!][!//
/***************************************Peripheral Region Start*************************************/
    [!LOOP "node:order(./*,'@index')"!][!//
    const Os_PeripheralConfigType  OsMpu_OsPeripheralRegion[!"num:i(@index)"!] =
    {
        [!INDENT "4"!][!//
        [!"num:inttohex(./OsPeripheralAreaStartAddress,8)"!]UL,                   /* AddressStart */ 
        [!"num:inttohex(./OsPeripheralAreaEndAddress,8)"!]UL,                   /* AddressEnd */
        [!VAR "AccessApplicationMask"="0"!][!//
        [!LOOP "node:order(./OsPeripheralAreaAccessingApplication/*,'@index')"!][!//
            [!VAR "AccessApplicationMask" = "bit:or(num:i($AccessApplicationMask),num:i(bit:shl(1,num:i(node:ref(.)/@index))))"!][!//
        [!ENDLOOP!][!//
        (uint32)[!"num:inttohex($AccessApplicationMask,8)"!]UL                  /* AccessingApplications */ 
        [!ENDINDENT!][!//
    };
    [!ENDLOOP!][!//

    CONSTP2CONST(Os_PeripheralConfigType, TYPEDEF, OS_CONST)  OsMpu_PeripheralRefs[OS_PERIPHERALID_COUNT + 1U] =            
    {
        [!INDENT "4"!][!//
        [!LOOP "node:order(./*,'@index')"!][!//
            &OsMpu_OsPeripheralRegion[!"num:i(@index)"!],
        [!ENDLOOP!][!//
        NULL_PTR
        [!ENDINDENT!][!//
    };

/***************************************Peripheral Region End***************************************/
[!ENDSELECT!][!//
#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
[!ENDINDENT!][!//



/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/






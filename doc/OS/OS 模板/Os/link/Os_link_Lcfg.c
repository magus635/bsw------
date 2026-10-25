/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_link_Lcfg.c
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
[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsResourceSubderivative) = 'Os_THA6206' or node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsResourceSubderivative) = 'Os_THA610X'"!][!//
#include "Os_GeneralTypes.h"
#include "Compiler.h"
#include "Os_kernel_Cfg.h"
#include "Os_link_Cfg.h"
#include "startup_memtypes.h"
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
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        [!IF "node:name(node:ref(./MemoryRegionRef)) = 'PFLASH0' or node:name(node:ref(./MemoryRegionRef)) = 'PFLASH1'"!][!//
        [!ELSE!][!//
        [!IF "node:value(./MemoryRegionType) != 'BSS'"!][!//
        extern uint32 Image$$[!"node:name(.)"!]$$Base;
        extern uint32 Image$$[!"node:name(.)"!]_LIMIT$$Base;
        extern uint32 Load$$[!"node:name(.)"!]$$Base;
        extern uint32 Load$$[!"node:name(.)"!]$$Limit;

        [!ELSE!][!//
        extern uint32 Image$$[!"node:name(.)"!]$$Base;
        extern uint32 Image$$[!"node:name(.)"!]_LIMIT$$Base;
        
        [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
extern uint32 Image$$CORE0_USER_STACK$$Base;
extern uint32 Image$$CORE0_USER_STACK$$ZI$$Limit;

extern uint32 Image$$CORE0_HYP_STACK$$Base;
extern uint32 Image$$CORE0_HYP_STACK$$ZI$$Limit;

extern uint32 Image$$CORE0_KERNEL_STACK$$Base;
extern uint32 Image$$CORE0_KERNEL_STACK$$ZI$$Limit;

extern uint32 Image$$CORE0_ABORT_STACK$$Base;
extern uint32 Image$$CORE0_ABORT_STACK$$ZI$$Limit;

extern uint32 Image$$CORE0_UNDEFINED_STACK$$Base;
extern uint32 Image$$CORE0_UNDEFINED_STACK$$ZI$$Limit;

extern uint32 Image$$CORE0_IRQ_STACK$$Base;
extern uint32 Image$$CORE0_IRQ_STACK$$ZI$$Limit;

extern uint32 Image$$CORE0_FIQ_STACK$$Base;
extern uint32 Image$$CORE0_FIQ_STACK$$ZI$$Limit;

extern uint32 Image$$CORE1_USER_STACK$$Base;
extern uint32 Image$$CORE1_USER_STACK$$ZI$$Limit;

extern uint32 Image$$CORE1_HYP_STACK$$Base;
extern uint32 Image$$CORE1_HYP_STACK$$ZI$$Limit;

extern uint32 Image$$CORE1_KERNEL_STACK$$Base;
extern uint32 Image$$CORE1_KERNEL_STACK$$ZI$$Limit;

extern uint32 Image$$CORE1_ABORT_STACK$$Base;
extern uint32 Image$$CORE1_ABORT_STACK$$ZI$$Limit;

extern uint32 Image$$CORE1_UNDEFINED_STACK$$Base;
extern uint32 Image$$CORE1_UNDEFINED_STACK$$ZI$$Limit;

extern uint32 Image$$CORE1_IRQ_STACK$$Base;
extern uint32 Image$$CORE1_IRQ_STACK$$ZI$$Limit;

extern uint32 Image$$CORE1_FIQ_STACK$$Base;
extern uint32 Image$$CORE1_FIQ_STACK$$ZI$$Limit;

#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
const static Os_LinkBssMemCfg Os_MemZeroInit_StageOne_GroupSets[MEM_ZEROINIT_STAGEONE_NUM] =
{
[!INDENT "4"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        [!IF "(node:value(./MemoryRegionType) = 'BSS' or node:value(./MemoryRegionType) = 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGEONE'"!][!//
        {
            [!INDENT "8"!][!//
            &Image$$[!"node:name(.)"!]$$Base, /*StartAddr*/
            &Image$$[!"node:name(.)"!]_LIMIT$$Base,/*EndAddr*/
            [!IF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'ALL'"!][!//
            0xFF, /*For all core.*/
            [!ELSEIF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'CORE0'"!][!//
            OS_CORE_ID_0, /*For master core.*/
            [!ELSE!][!//
            OS_CORE_ID_1,
            [!ENDIF!][!//
            [!"num:inttohex(./MemoryBlockAlign)"!]     /*Alignment requirement.*/
            [!ENDINDENT!][!//
        },
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
};

const static Os_LinkBssMemCfg Os_MemZeroInit_StageTwo_GroupSets[MEM_ZEROINIT_STAGETWO_NUM] =
{
[!INDENT "4"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        [!IF "(node:value(./MemoryRegionType) = 'BSS' or node:value(./MemoryRegionType) = 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGETWO'"!][!//
        {
            [!INDENT "8"!][!//
            &Image$$[!"node:name(.)"!]$$Base, /*StartAddr*/
            &Image$$[!"node:name(.)"!]_LIMIT$$Base,/*EndAddr*/
            [!IF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'ALL'"!][!//
            0xFF, /*For all core.*/
            [!ELSEIF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'CORE0'"!][!//
            OS_CORE_ID_0, /*For master core.*/
            [!ELSE!][!//
            OS_CORE_ID_1,
            [!ENDIF!][!//
            [!"num:inttohex(./MemoryBlockAlign)"!]     /*Alignment requirement.*/
            [!ENDINDENT!][!//
        },
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
};

const static Os_LinkBssMemCfg Os_MemZeroInit_StageThree_GroupSets[MEM_ZEROINIT_STAGETHREE_NUM] =
{
[!INDENT "4"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        [!IF "(node:value(./MemoryRegionType) = 'BSS' or node:value(./MemoryRegionType) = 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGETHREE'"!][!//
        {
            [!INDENT "8"!][!//
            &Image$$[!"node:name(.)"!]$$Base, /*StartAddr*/
            &Image$$[!"node:name(.)"!]_LIMIT$$Base,/*EndAddr*/
            [!IF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'ALL'"!][!//
            0xFF, /*For all core.*/
            [!ELSEIF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'CORE0'"!][!//
            OS_CORE_ID_0, /*For master core.*/
            [!ELSE!][!//
            OS_CORE_ID_1,
            [!ENDIF!][!//
            [!"num:inttohex(./MemoryBlockAlign)"!]     /*Alignment requirement.*/
            [!ENDINDENT!][!//
        },
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
};

const static Os_LinkBssMemCfg Os_MemZeroInit_Unclear_GroupSets[MEM_ZEROINIT_STAGEUNCLEAR_NUM] =
{
[!INDENT "4"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        [!IF "(node:value(./MemoryRegionType) = 'BSS' or node:value(./MemoryRegionType) = 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGEUNCLEAR'"!][!//
        {
            [!INDENT "8"!][!//
            &Image$$[!"node:name(.)"!]$$Base, /*StartAddr*/
            &Image$$[!"node:name(.)"!]_LIMIT$$Base,/*EndAddr*/
            [!IF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'ALL'"!][!//
            0xFF, /*For all core.*/
            [!ELSEIF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'CORE0'"!][!//
            OS_CORE_ID_0, /*For master core.*/
            [!ELSE!][!//
            OS_CORE_ID_1,
            [!ENDIF!][!//
            [!"num:inttohex(./MemoryBlockAlign)"!]     /*Alignment requirement.*/
            [!ENDINDENT!][!//
        },
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
};

const static Os_LinkDataMemCfg Os_MemDataInit_StageOne_GroupSets[MEM_DATAINIT_STAGEONE_NUM] =
{
[!INDENT "4"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        [!IF "node:name(node:ref(./MemoryRegionRef)) = 'PFLASH0' or node:name(node:ref(./MemoryRegionRef)) = 'PFLASH1'"!][!//
        [!ELSE!][!//
            [!IF "(node:value(./MemoryRegionType) != 'BSS' and node:value(./MemoryRegionType) != 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGEONE'"!][!//
            {
                [!INDENT "8"!][!//
                &Load$$[!"node:name(.)"!]$$Base,/*startRomAddr*/
                &Load$$[!"node:name(.)"!]$$Limit,/*endRomAddr*/
                &Image$$[!"node:name(.)"!]$$Base, /*StartAddr*/
                &Image$$[!"node:name(.)"!]_LIMIT$$Base,/*EndAddr*/
                [!IF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'ALL'"!][!//
                0xFF, /*For all core.*/
                [!ELSEIF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'CORE0'"!][!//
                OS_CORE_ID_0, /*For master core.*/
                [!ELSE!][!//
                OS_CORE_ID_1,
                [!ENDIF!][!//
                [!"num:inttohex(./MemoryBlockAlign)"!]     /*Alignment requirement.*/
                [!ENDINDENT!][!//
            },
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
};

const static Os_LinkDataMemCfg Os_MemDataInit_StageTwo_GroupSets[MEM_DATAINIT_STAGETWO_NUM] =
{
[!INDENT "4"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        [!IF "node:name(node:ref(./MemoryRegionRef)) = 'PFLASH0' or node:name(node:ref(./MemoryRegionRef)) = 'PFLASH1'"!][!//
        [!ELSE!][!//
            [!IF "(node:value(./MemoryRegionType) != 'BSS' and node:value(./MemoryRegionType) != 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGETWO'"!][!//
            {
                [!INDENT "8"!][!//
                &Load$$[!"node:name(.)"!]$$Base,/*startRomAddr*/
                &Load$$[!"node:name(.)"!]$$Limit,/*endRomAddr*/
                &Image$$[!"node:name(.)"!]$$Base, /*StartAddr*/
                &Image$$[!"node:name(.)"!]_LIMIT$$Base,/*EndAddr*/
                [!IF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'ALL'"!][!//
                0xFF, /*For all core.*/
                [!ELSEIF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'CORE0'"!][!//
                OS_CORE_ID_0, /*For master core.*/
                [!ELSE!][!//
                OS_CORE_ID_1,
                [!ENDIF!][!//
                [!"num:inttohex(./MemoryBlockAlign)"!]     /*Alignment requirement.*/
                [!ENDINDENT!][!//
            },
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
};

const static Os_LinkDataMemCfg Os_MemDataInit_StageThree_GroupSets[MEM_DATAINIT_STAGETHREE_NUM] =
{
[!INDENT "4"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock"!][!//
    [!LOOP "node:order(./*, '@index')"!][!//
        [!IF "node:name(node:ref(./MemoryRegionRef)) = 'PFLASH0' or node:name(node:ref(./MemoryRegionRef)) = 'PFLASH1'"!][!//
        [!ELSE!][!//
            [!IF "(node:value(./MemoryRegionType) != 'BSS' and node:value(./MemoryRegionType) != 'NON_INIT') and node:value(./MemoryCopyStage) = 'STAGETHREE'"!][!//
            {
                [!INDENT "8"!][!//
                &Load$$[!"node:name(.)"!]$$Base,/*startRomAddr*/
                &Load$$[!"node:name(.)"!]$$Limit,/*endRomAddr*/
                &Image$$[!"node:name(.)"!]$$Base, /*StartAddr*/
                &Image$$[!"node:name(.)"!]_LIMIT$$Base,/*EndAddr*/
                [!IF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'ALL'"!][!//
                0xFF, /*For all core.*/
                [!ELSEIF "node:value(node:ref(./MemoryRegionRef)/MemoryRegionCopy) = 'CORE0'"!][!//
                OS_CORE_ID_0, /*For master core.*/
                [!ELSE!][!//
                OS_CORE_ID_1,
                [!ENDIF!][!//
                [!"num:inttohex(./MemoryBlockAlign)"!]     /*Alignment requirement.*/
                [!ENDINDENT!][!//
            },
            [!ENDIF!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
};
#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

#define OS_START_SEC_CONST_QM_CORE0_UNSPECIFIED
#include "Os_memmap.h"
const static Os_LinkSingleStackCfg Os_MemStackCore0_GroupSets[OS_STACK_MODE_NUM] =
{
    {
        &Image$$CORE0_USER_STACK$$Base,
        &Image$$CORE0_USER_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE0_HYP_STACK$$Base,
        &Image$$CORE0_HYP_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE0_KERNEL_STACK$$Base,
        &Image$$CORE0_KERNEL_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE0_ABORT_STACK$$Base,
        &Image$$CORE0_ABORT_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE0_UNDEFINED_STACK$$Base,
        &Image$$CORE0_UNDEFINED_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE0_IRQ_STACK$$Base,
        &Image$$CORE0_IRQ_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE0_FIQ_STACK$$Base,
        &Image$$CORE0_FIQ_STACK$$ZI$$Limit
    },
};
#define OS_STOP_SEC_CONST_QM_CORE0_UNSPECIFIED
#include "Os_memmap.h"    

[!IF "num:i(ecu:get('OsResource.NumOfCores')) > 1"!][!//
#define OS_START_SEC_CONST_QM_CORE1_UNSPECIFIED
#include "Os_memmap.h"
const static Os_LinkSingleStackCfg Os_MemStackCore1_GroupSets[OS_STACK_MODE_NUM] =
{
    {
        &Image$$CORE1_USER_STACK$$Base,
        &Image$$CORE1_USER_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE1_HYP_STACK$$Base,
        &Image$$CORE1_HYP_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE1_KERNEL_STACK$$Base,
        &Image$$CORE1_KERNEL_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE1_ABORT_STACK$$Base,
        &Image$$CORE1_ABORT_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE1_UNDEFINED_STACK$$Base,
        &Image$$CORE1_UNDEFINED_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE1_IRQ_STACK$$Base,
        &Image$$CORE1_IRQ_STACK$$ZI$$Limit
    },
    {
        &Image$$CORE1_FIQ_STACK$$Base,
        &Image$$CORE1_FIQ_STACK$$ZI$$Limit
    },
};
#define OS_STOP_SEC_CONST_QM_CORE1_UNSPECIFIED
#include "Os_memmap.h"
[!ENDIF!][!//


#define OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"
/*used for clone bss sections.*/
const Os_LinkBssMemGroupCfg Os_MemZeroInit_StageOne =
{
    MEM_ZEROINIT_STAGEONE_NUM,
    Os_MemZeroInit_StageOne_GroupSets,
};

/*used for common bss sections.*/
const Os_LinkBssMemGroupCfg Os_MemZeroInit_StageTwo =
{
    MEM_ZEROINIT_STAGETWO_NUM,
    Os_MemZeroInit_StageTwo_GroupSets,
};

/*used for private bss sections.*/
const Os_LinkBssMemGroupCfg Os_MemZeroInit_StageThree =
{
    MEM_ZEROINIT_STAGETHREE_NUM,
    Os_MemZeroInit_StageThree_GroupSets,
};

/*used for private bss sections.*/
const Os_LinkBssMemGroupCfg Os_MemZeroInit_Unclear =
{
    MEM_ZEROINIT_STAGEUNCLEAR_NUM,
    Os_MemZeroInit_Unclear_GroupSets,
};
/*used for system stack setting.*/
const Os_LinkStackCfg Os_MemStackInit[[!"num:i(ecu:get('OsResource.NumOfCores'))"!]] =
{
    {OS_STACK_MODE_NUM, Os_MemStackCore0_GroupSets},
[!IF "num:i(ecu:get('OsResource.NumOfCores')) > 1"!][!//
    {OS_STACK_MODE_NUM, Os_MemStackCore1_GroupSets},
[!ENDIF!][!//
};

/*used for clone data/code sections.*/
const Os_LinkDataMemGroupCfg Os_MemDataInit_StageOne =
{
    MEM_DATAINIT_STAGEONE_NUM,
    Os_MemDataInit_StageOne_GroupSets,
};

/*used for common data/code sections.*/
const Os_LinkDataMemGroupCfg Os_MemDataInit_StageTwo =
{
    MEM_DATAINIT_STAGETWO_NUM,
    Os_MemDataInit_StageTwo_GroupSets,
};

/*used for private data/code sections.*/
const Os_LinkDataMemGroupCfg Os_MemDataInit_StageThree =
{
    MEM_DATAINIT_STAGETHREE_NUM,
    Os_MemDataInit_StageThree_GroupSets,
};
#define OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
#include "Os_memmap.h"

[!ENDIF!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/


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

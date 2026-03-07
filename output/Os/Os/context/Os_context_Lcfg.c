/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_context_Lcfg.c
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
*   Genaration Time       : 2026-03-05 20:16:07
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
#include "Os_context_Cfg.h"
#include "Os_context_Lcfg.h"
#include "Os_mpu_Lcfg.h"
#include "Os_task.h"
#include "Os_isr.h"
#include "Os_ioc.h"
#include "Os_ioc_Lcfg.h"
#include "Os_counter.h"
#include "Os_isr_Lcfg.h"
#include "Os_hook.h"
#include "Os_kernel.h"
#include "Os_hook_Lcfg.h"
#include "Os_timingprotection_Lcfg.h"
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

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#define OS_START_SEC_STACKCFG_QM_CORE0_32
#include "Os_memmap.h" 
static uint32 Idle_Task_Core0_stack[256];
static uint32 Task1_stack[256];
static uint32 Task5_stack[256];
static uint32 Task6_stack[256];
static uint32 Default_Init_Task_stack[256];
static uint32 Task2_stack[256];
static uint32 Task3_stack[256];
static uint32 Task8_stack[256];
static uint32 Task16_stack[256];
static uint32 Task17_stack[256];
static uint32 Task18_stack[256];
static uint32 Task19_stack[256];
static uint32 Task20_stack[256];
static uint32 Os_IsrCfg_SystemTimer_stack[256];
static uint32 Os_IsrCfg_VirtualTimer_stack[256];
static uint32 OsIsr_BaseTimer1_stack[256];
static uint32 OsIsr_0_stack[256];
static uint32 Task4_stack[256];
static uint32 Task7_stack[256];
static uint32 Os_IsrCfg_BaseTimer0_stack[256];
static uint32 OsCore0_ErrorHook_stack[256];
static uint32 OsCore0_StartupHook_stack[256];
static uint32 OsCore0_ProtectionHook_stack[256];
static uint32 OsCore0_StartOsInitFunction_stack[256];
#define OS_STOP_SEC_STACKCFG_QM_CORE0_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_Hal_ContextFrame Idle_Task_Core0_ContextInfo;
static Os_Hal_ContextRunningDataType Idle_Task_Core0_ContextRunningData;
static Os_Hal_ContextFrame Task1_ContextInfo;
static Os_Hal_ContextRunningDataType Task1_ContextRunningData;
static Os_Hal_ContextFrame Task5_ContextInfo;
static Os_Hal_ContextRunningDataType Task5_ContextRunningData;
static Os_Hal_ContextFrame Task6_ContextInfo;
static Os_Hal_ContextRunningDataType Task6_ContextRunningData;
static Os_Hal_ContextFrame Default_Init_Task_ContextInfo;
static Os_Hal_ContextRunningDataType Default_Init_Task_ContextRunningData;
static Os_Hal_ContextFrame Task2_ContextInfo;
static Os_Hal_ContextRunningDataType Task2_ContextRunningData;
static Os_Hal_ContextFrame Task3_ContextInfo;
static Os_Hal_ContextRunningDataType Task3_ContextRunningData;
static Os_Hal_ContextFrame Task8_ContextInfo;
static Os_Hal_ContextRunningDataType Task8_ContextRunningData;
static Os_Hal_ContextFrame Task16_ContextInfo;
static Os_Hal_ContextRunningDataType Task16_ContextRunningData;
static Os_Hal_ContextFrame Task17_ContextInfo;
static Os_Hal_ContextRunningDataType Task17_ContextRunningData;
static Os_Hal_ContextFrame Task18_ContextInfo;
static Os_Hal_ContextRunningDataType Task18_ContextRunningData;
static Os_Hal_ContextFrame Task19_ContextInfo;
static Os_Hal_ContextRunningDataType Task19_ContextRunningData;
static Os_Hal_ContextFrame Task20_ContextInfo;
static Os_Hal_ContextRunningDataType Task20_ContextRunningData;
static Os_Hal_ContextFrame Os_IsrCfg_SystemTimer_ContextInfo;
static Os_Hal_ContextRunningDataType Os_IsrCfg_SystemTimer_ContextRunningData;
static Os_Hal_ContextFrame Os_IsrCfg_VirtualTimer_ContextInfo;
static Os_Hal_ContextRunningDataType Os_IsrCfg_VirtualTimer_ContextRunningData;
static Os_Hal_ContextFrame OsIsr_BaseTimer1_ContextInfo;
static Os_Hal_ContextRunningDataType OsIsr_BaseTimer1_ContextRunningData;
static Os_Hal_ContextFrame OsIsr_0_ContextInfo;
static Os_Hal_ContextRunningDataType OsIsr_0_ContextRunningData;
static Os_Hal_ContextFrame OsCore0_ErrorHook_ContextInfo;
static Os_Hal_ContextRunningDataType OsCore0_ErrorHook_ContextRunningData;
static Os_Hal_ContextFrame OsCore0_StartupHook_ContextInfo;
static Os_Hal_ContextRunningDataType OsCore0_StartupHook_ContextRunningData;
static Os_Hal_ContextFrame OsCore0_ProtectionHook_ContextInfo;
static Os_Hal_ContextRunningDataType OsCore0_ProtectionHook_ContextRunningData;
static Os_Hal_ContextFrame OsCore0_StartOsInitFunction_ContextInfo;
static Os_Hal_ContextRunningDataType OsCore0_StartOsInitFunction_ContextRunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h" 
static Os_Hal_ContextFrame Task4_ContextInfo;
static Os_Hal_ContextRunningDataType Task4_ContextRunningData;
#define OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h" 
#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
static Os_Hal_ContextFrame Task7_ContextInfo;
static Os_Hal_ContextRunningDataType Task7_ContextRunningData;
static Os_Hal_ContextFrame Os_IsrCfg_BaseTimer0_ContextInfo;
static Os_Hal_ContextRunningDataType Os_IsrCfg_BaseTimer0_ContextRunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
#include "Os_memmap.h"
#define OS_START_SEC_STACKCFG_QM_CORE1_32
#include "Os_memmap.h" 
static uint32 Default_Init_Task_Core1_stack[256];
static uint32 Idle_Task_Core1_stack[256];
static uint32 Task0_Core1_stack[256];
static uint32 Task9_Core1_stack[256];
static uint32 Task10_Core1_stack[256];
static uint32 Task12_Core1_stack[256];
static uint32 Task11_Core1_stack[256];
static uint32 Task13_Core1_stack[256];
static uint32 Task14_Core1_stack[256];
static uint32 Task15_Core1_stack[256];
static uint32 Os_IsrCfg_SystemTimer_Core1_stack[256];
static uint32 OsIsr_IsrCfg_VirtualTimer_Core1_stack[256];
static uint32 OsIsr_1_stack[256];
static uint32 OsCore1_ErrorHook_stack[256];
static uint32 OsCore1_StartupHook_stack[256];
static uint32 OsCore1_ProtectionHook_stack[256];
static uint32 OsCore1_StartOsInitFunction_stack[256];
#define OS_STOP_SEC_STACKCFG_QM_CORE1_32
#include "Os_memmap.h"

#define OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"
static Os_Hal_ContextFrame Default_Init_Task_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Default_Init_Task_Core1_ContextRunningData;
static Os_Hal_ContextFrame Idle_Task_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Idle_Task_Core1_ContextRunningData;
static Os_Hal_ContextFrame Task0_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Task0_Core1_ContextRunningData;
static Os_Hal_ContextFrame Task9_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Task9_Core1_ContextRunningData;
static Os_Hal_ContextFrame Task10_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Task10_Core1_ContextRunningData;
static Os_Hal_ContextFrame Task12_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Task12_Core1_ContextRunningData;
static Os_Hal_ContextFrame Task11_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Task11_Core1_ContextRunningData;
static Os_Hal_ContextFrame Task13_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Task13_Core1_ContextRunningData;
static Os_Hal_ContextFrame Task14_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Task14_Core1_ContextRunningData;
static Os_Hal_ContextFrame Task15_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Task15_Core1_ContextRunningData;
static Os_Hal_ContextFrame Os_IsrCfg_SystemTimer_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType Os_IsrCfg_SystemTimer_Core1_ContextRunningData;
static Os_Hal_ContextFrame OsIsr_IsrCfg_VirtualTimer_Core1_ContextInfo;
static Os_Hal_ContextRunningDataType OsIsr_IsrCfg_VirtualTimer_Core1_ContextRunningData;
static Os_Hal_ContextFrame OsIsr_1_ContextInfo;
static Os_Hal_ContextRunningDataType OsIsr_1_ContextRunningData;
static Os_Hal_ContextFrame OsCore1_ErrorHook_ContextInfo;
static Os_Hal_ContextRunningDataType OsCore1_ErrorHook_ContextRunningData;
static Os_Hal_ContextFrame OsCore1_StartupHook_ContextInfo;
static Os_Hal_ContextRunningDataType OsCore1_StartupHook_ContextRunningData;
static Os_Hal_ContextFrame OsCore1_ProtectionHook_ContextInfo;
static Os_Hal_ContextRunningDataType OsCore1_ProtectionHook_ContextRunningData;
static Os_Hal_ContextFrame OsCore1_StartOsInitFunction_ContextInfo;
static Os_Hal_ContextRunningDataType OsCore1_StartOsInitFunction_ContextRunningData;
#define OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
#include "Os_memmap.h"

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/
const Os_ContextType Idle_Task_Core0_Context_Config =
{
    (uint32)&Idle_Task_Core0_stack[0],               /* StackTopAddr */
    (uint32)&Idle_Task_Core0_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Idle_Task_Core0,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Idle_Task_Core0_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Idle_Task_Core0_ContextRunningData
};
const Os_ContextType Task1_Context_Config =
{
    (uint32)&Task1_stack[0],               /* StackTopAddr */
    (uint32)&Task1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    &Os_TimingProection_ObjSet[0],
    &Task1_ContextRunningData
};
const Os_ContextType Task5_Context_Config =
{
    (uint32)&Task5_stack[0],               /* StackTopAddr */
    (uint32)&Task5_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task5,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task5_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    &Os_TimingProection_ObjSet[1],
    &Task5_ContextRunningData
};
const Os_ContextType Task6_Context_Config =
{
    (uint32)&Task6_stack[0],               /* StackTopAddr */
    (uint32)&Task6_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task6,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task6_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task6_ContextRunningData
};
const Os_ContextType Default_Init_Task_Context_Config =
{
    (uint32)&Default_Init_Task_stack[0],               /* StackTopAddr */
    (uint32)&Default_Init_Task_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Default_Init_Task,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Default_Init_Task_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Default_Init_Task_ContextRunningData
};
const Os_ContextType Task2_Context_Config =
{
    (uint32)&Task2_stack[0],               /* StackTopAddr */
    (uint32)&Task2_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task2,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task2_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    &Os_TimingProection_ObjSet[2],
    &Task2_ContextRunningData
};
const Os_ContextType Task3_Context_Config =
{
    (uint32)&Task3_stack[0],               /* StackTopAddr */
    (uint32)&Task3_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task3,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task3_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    &Os_TimingProection_ObjSet[3],
    &Task3_ContextRunningData
};
const Os_ContextType Task8_Context_Config =
{
    (uint32)&Task8_stack[0],               /* StackTopAddr */
    (uint32)&Task8_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task8,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task8_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task8_ContextRunningData
};
const Os_ContextType Task16_Context_Config =
{
    (uint32)&Task16_stack[0],               /* StackTopAddr */
    (uint32)&Task16_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task16,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task16_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task16_ContextRunningData
};
const Os_ContextType Task17_Context_Config =
{
    (uint32)&Task17_stack[0],               /* StackTopAddr */
    (uint32)&Task17_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task17,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task17_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task17_ContextRunningData
};
const Os_ContextType Task18_Context_Config =
{
    (uint32)&Task18_stack[0],               /* StackTopAddr */
    (uint32)&Task18_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task18,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task18_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task18_ContextRunningData
};
const Os_ContextType Task19_Context_Config =
{
    (uint32)&Task19_stack[0],               /* StackTopAddr */
    (uint32)&Task19_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task19,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task19_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task19_ContextRunningData
};
const Os_ContextType Task20_Context_Config =
{
    (uint32)&Task20_stack[0],               /* StackTopAddr */
    (uint32)&Task20_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task20,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task20_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task20_ContextRunningData
};
const Os_ContextType Os_IsrCfg_SystemTimer_Context_Config =
{
    (uint32)&Os_IsrCfg_SystemTimer_stack[0],               /* StackTopAddr */
    (uint32)&Os_IsrCfg_SystemTimer_stack[256],            /* StackBottomAddr */
    (uint32)&Isr_OsCounter_PfrtService,            /* EntryFunction */
    (uint32)&OsIsr_PostISR,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    30U << 3,            /* InterruptSetting */
    &Os_IsrCfg_SystemTimer_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Os_IsrCfg_SystemTimer_ContextRunningData
};
const Os_ContextType Os_IsrCfg_VirtualTimer_Context_Config =
{
    (uint32)&Os_IsrCfg_VirtualTimer_stack[0],               /* StackTopAddr */
    (uint32)&Os_IsrCfg_VirtualTimer_stack[256],            /* StackBottomAddr */
    (uint32)&Isr_TimingProtectionService,            /* EntryFunction */
    (uint32)&OsIsr_PostISR,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    27U << 3,            /* InterruptSetting */
    &Os_IsrCfg_VirtualTimer_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Os_IsrCfg_VirtualTimer_ContextRunningData
};
const Os_ContextType OsIsr_BaseTimer1_Context_Config =
{
    (uint32)&OsIsr_BaseTimer1_stack[0],               /* StackTopAddr */
    (uint32)&OsIsr_BaseTimer1_stack[256],            /* StackBottomAddr */
    (uint32)&Isr_Isr2Test,            /* EntryFunction */
    (uint32)&OsIsr_PostISR,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    29U << 3,            /* InterruptSetting */
    &OsIsr_BaseTimer1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    &Os_TimingProection_ObjSet[4],
    &OsIsr_BaseTimer1_ContextRunningData
};
const Os_ContextType OsIsr_0_Context_Config =
{
    (uint32)&OsIsr_0_stack[0],               /* StackTopAddr */
    (uint32)&OsIsr_0_stack[256],            /* StackBottomAddr */
    (uint32)0,                    /* EntryFunction */
    (uint32)&OsIsr_PostServiceCallISR,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    28U << 3,            /* InterruptSetting */
    &OsIsr_0_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsIsr_0_ContextRunningData
};
const Os_ContextType Core0KernelApp0_ErrorHook_Context_Config =
{
    (uint32)&OsCore0_ErrorHook_stack[0],               /* StackTopAddr */
    (uint32)&OsCore0_ErrorHook_stack[256],            /* StackBottomAddr */
    (uint32)&ErrorHook,            /* EntryFunction */
    (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
    &OsCore0_ErrorHook_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsCore0_ErrorHook_ContextRunningData
};
const Os_ContextType Core0KernelApp0_StartupHook_Context_Config =
{
    (uint32)&OsCore0_StartupHook_stack[0],               /* StackTopAddr */
    (uint32)&OsCore0_StartupHook_stack[256],            /* StackBottomAddr */
    (uint32)&StartupHook,            /* EntryFunction */
    (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
    &OsCore0_StartupHook_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsCore0_StartupHook_ContextRunningData
};
const Os_ContextType Core0KernelApp0_ProtectionHook_Context_Config =
{
    (uint32)&OsCore0_ProtectionHook_stack[0],               /* StackTopAddr */
    (uint32)&OsCore0_ProtectionHook_stack[256],            /* StackBottomAddr */
    (uint32)&ProtectionHook,            /* EntryFunction */
    (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    0,            /* InterruptSetting */
    &OsCore0_ProtectionHook_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsCore0_ProtectionHook_ContextRunningData
};

const Os_ContextType Core0_StartOsInitFunction_Context_Config =
{
    (uint32)&OsCore0_StartOsInitFunction_stack[0],               /* StackTopAddr */
    (uint32)&OsCore0_StartOsInitFunction_stack[256],            /* StackBottomAddr */
    (uint32)&OsKernel_StartOs_InitFunction,            /* EntryFunction */
    (uint32)0,                                         /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
    &OsCore0_StartOsInitFunction_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsCore0_StartOsInitFunction_ContextRunningData
};

const Os_ContextType Task4_Context_Config =
{
    (uint32)&Task4_stack[0],               /* StackTopAddr */
    (uint32)&Task4_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task4,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_USER_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task4_ContextInfo,
    &OsMpu_ConfigSet_ObjectRefs[0],
    NULL_PTR,
    NULL_PTR,
    &Task4_ContextRunningData
};
const Os_ContextType Task7_Context_Config =
{
    (uint32)&Task7_stack[0],               /* StackTopAddr */
    (uint32)&Task7_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task7,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task7_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task7_ContextRunningData
};
const Os_ContextType Os_IsrCfg_BaseTimer0_Context_Config =
{
    (uint32)&Os_IsrCfg_BaseTimer0_stack[0],               /* StackTopAddr */
    (uint32)&Os_IsrCfg_BaseTimer0_stack[256],            /* StackBottomAddr */
    (uint32)&Isr_OsCounter_PitService,            /* EntryFunction */
    (uint32)&OsIsr_PostISR,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    28U << 3,            /* InterruptSetting */
    &Os_IsrCfg_BaseTimer0_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Os_IsrCfg_BaseTimer0_ContextRunningData
};
const Os_ContextType Default_Init_Task_Core1_Context_Config =
{
    (uint32)&Default_Init_Task_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Default_Init_Task_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Default_Init_Task_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Default_Init_Task_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Default_Init_Task_Core1_ContextRunningData
};
const Os_ContextType Idle_Task_Core1_Context_Config =
{
    (uint32)&Idle_Task_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Idle_Task_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Idle_Task_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Idle_Task_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Idle_Task_Core1_ContextRunningData
};
const Os_ContextType Task0_Core1_Context_Config =
{
    (uint32)&Task0_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Task0_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task0_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task0_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task0_Core1_ContextRunningData
};
const Os_ContextType Task9_Core1_Context_Config =
{
    (uint32)&Task9_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Task9_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task9_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task9_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task9_Core1_ContextRunningData
};
const Os_ContextType Task10_Core1_Context_Config =
{
    (uint32)&Task10_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Task10_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task10_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task10_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task10_Core1_ContextRunningData
};
const Os_ContextType Task12_Core1_Context_Config =
{
    (uint32)&Task12_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Task12_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task12_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task12_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    &Os_TimingProection_ObjSet[5],
    &Task12_Core1_ContextRunningData
};
const Os_ContextType Task11_Core1_Context_Config =
{
    (uint32)&Task11_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Task11_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task11_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task11_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    &Os_TimingProection_ObjSet[6],
    &Task11_Core1_ContextRunningData
};
const Os_ContextType Task13_Core1_Context_Config =
{
    (uint32)&Task13_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Task13_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task13_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task13_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task13_Core1_ContextRunningData
};
const Os_ContextType Task14_Core1_Context_Config =
{
    (uint32)&Task14_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Task14_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task14_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task14_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task14_Core1_ContextRunningData
};
const Os_ContextType Task15_Core1_Context_Config =
{
    (uint32)&Task15_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Task15_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Task_Task15_Core1,               /* EntryFunction */
    (uint32)&OsTask_ErrorReturn,            /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                           /* ProgramSetting */
    0xF8,                           /* InterruptSetting */
    &Task15_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Task15_Core1_ContextRunningData
};
const Os_ContextType Os_IsrCfg_SystemTimer_Core1_Context_Config =
{
    (uint32)&Os_IsrCfg_SystemTimer_Core1_stack[0],               /* StackTopAddr */
    (uint32)&Os_IsrCfg_SystemTimer_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Isr_OsCounter_PfrtService,            /* EntryFunction */
    (uint32)&OsIsr_PostISR,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    30U << 3,            /* InterruptSetting */
    &Os_IsrCfg_SystemTimer_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &Os_IsrCfg_SystemTimer_Core1_ContextRunningData
};
const Os_ContextType OsIsr_IsrCfg_VirtualTimer_Core1_Context_Config =
{
    (uint32)&OsIsr_IsrCfg_VirtualTimer_Core1_stack[0],               /* StackTopAddr */
    (uint32)&OsIsr_IsrCfg_VirtualTimer_Core1_stack[256],            /* StackBottomAddr */
    (uint32)&Isr_TimingProtectionService,            /* EntryFunction */
    (uint32)&OsIsr_PostISR,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    27U << 3,            /* InterruptSetting */
    &OsIsr_IsrCfg_VirtualTimer_Core1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsIsr_IsrCfg_VirtualTimer_Core1_ContextRunningData
};
const Os_ContextType OsIsr_1_Context_Config =
{
    (uint32)&OsIsr_1_stack[0],               /* StackTopAddr */
    (uint32)&OsIsr_1_stack[256],            /* StackBottomAddr */
    (uint32)0,                    /* EntryFunction */
    (uint32)&OsIsr_PostServiceCallISR,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    28U << 3,            /* InterruptSetting */
    &OsIsr_1_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsIsr_1_ContextRunningData
};
const Os_ContextType Core1KernelApp3_ErrorHook_Context_Config =
{
    (uint32)&OsCore1_ErrorHook_stack[0],               /* StackTopAddr */
    (uint32)&OsCore1_ErrorHook_stack[256],            /* StackBottomAddr */
    (uint32)&ErrorHook,            /* EntryFunction */
    (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
    &OsCore1_ErrorHook_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsCore1_ErrorHook_ContextRunningData
};
const Os_ContextType Core1KernelApp3_StartupHook_Context_Config =
{
    (uint32)&OsCore1_StartupHook_stack[0],               /* StackTopAddr */
    (uint32)&OsCore1_StartupHook_stack[256],            /* StackBottomAddr */
    (uint32)&StartupHook,            /* EntryFunction */
    (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
    &OsCore1_StartupHook_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsCore1_StartupHook_ContextRunningData
};
const Os_ContextType Core1KernelApp3_ProtectionHook_Context_Config =
{
    (uint32)&OsCore1_ProtectionHook_stack[0],               /* StackTopAddr */
    (uint32)&OsCore1_ProtectionHook_stack[256],            /* StackBottomAddr */
    (uint32)&ProtectionHook,            /* EntryFunction */
    (uint32)&OsHook_Hookreturn,               /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    0,            /* InterruptSetting */
    &OsCore1_ProtectionHook_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsCore1_ProtectionHook_ContextRunningData
};

const Os_ContextType Core1_StartOsInitFunction_Context_Config =
{
    (uint32)&OsCore1_StartOsInitFunction_stack[0],               /* StackTopAddr */
    (uint32)&OsCore1_StartOsInitFunction_stack[256],            /* StackBottomAddr */
    (uint32)&OsKernel_StartOs_InitFunction,            /* EntryFunction */
    (uint32)0,                                         /* ReturnFunction */
    OS_CONTEXT_SYS_MODE,                         /* ProgramSetting */
    OS_ISR_CAT2_DISABLE_LEVEL << 3,            /* InterruptSetting */
    &OsCore1_StartOsInitFunction_ContextInfo,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    &OsCore1_StartOsInitFunction_ContextRunningData
};


/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
const Os_ContextConfigType Os_ContextConfigSet =
{
    {
        &Idle_Task_Core0_Context_Config,
        &Task1_Context_Config,
        &Task5_Context_Config,
        &Task6_Context_Config,
        &Default_Init_Task_Context_Config,
        &Task2_Context_Config,
        &Task3_Context_Config,
        &Task8_Context_Config,
        &Task16_Context_Config,
        &Task17_Context_Config,
        &Task18_Context_Config,
        &Task19_Context_Config,
        &Task20_Context_Config,
        &Os_IsrCfg_SystemTimer_Context_Config,
        &Os_IsrCfg_VirtualTimer_Context_Config,
        &OsIsr_BaseTimer1_Context_Config,
        &OsIsr_0_Context_Config,
        &Core0KernelApp0_ErrorHook_Context_Config,
        &Core0KernelApp0_StartupHook_Context_Config,
        &Core0KernelApp0_ProtectionHook_Context_Config,
        &Core0_StartOsInitFunction_Context_Config,
        &Task4_Context_Config,
        &Task7_Context_Config,
        &Os_IsrCfg_BaseTimer0_Context_Config,
        &Default_Init_Task_Core1_Context_Config,
        &Idle_Task_Core1_Context_Config,
        &Task0_Core1_Context_Config,
        &Task9_Core1_Context_Config,
        &Task10_Core1_Context_Config,
        &Task12_Core1_Context_Config,
        &Task11_Core1_Context_Config,
        &Task13_Core1_Context_Config,
        &Task14_Core1_Context_Config,
        &Task15_Core1_Context_Config,
        &Os_IsrCfg_SystemTimer_Core1_Context_Config,
        &OsIsr_IsrCfg_VirtualTimer_Core1_Context_Config,
        &OsIsr_1_Context_Config,
        &Core1KernelApp3_ErrorHook_Context_Config,
        &Core1KernelApp3_StartupHook_Context_Config,
        &Core1KernelApp3_ProtectionHook_Context_Config,
        &Core1_StartOsInitFunction_Context_Config,
        NULL_PTR
    }
};
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/



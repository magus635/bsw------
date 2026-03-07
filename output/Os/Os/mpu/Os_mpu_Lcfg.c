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
*   Genaration Time       : 2026-03-05 20:16:15
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


/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

const Os_HalMpuRegionType OsMpu_ConfigSet_Core0_Regions[2] =
{
    {
        0x00000000,          /* RegionNumber */
        (uint32)0x00000000U,          /* RegionBaseAddress */
        (uint32)(0x00000000U),                /* RegionEndAddress */
        MPU_EL1_R_EL0_R|MPU_EXECUTE_ALLOWED,
        MPU_REGION_ENABLE
    },
    {
        0x00000001,          /* RegionNumber */
        (uint32)0x00000000U,          /* RegionBaseAddress */
        (uint32)(0x00000000U),                /* RegionEndAddress */
        MPU_EL1_R_EL0_R|MPU_EXECUTE_NEVER,
        MPU_REGION_ENABLE
    },
};

const Os_MpuConfigType OsMpu_ConfigSet_Core0 =
{
    (uint32)2,                  /* MpuRegionCount */
    OsMpu_ConfigSet_Core0_Regions                /* MpuRegions */
};

const Os_HalStackConfigAddressType OsMpu_ConfigSet_OsStackCore0 = 
{
    (uint32)(&Image$$OS_CORE0_STACK$$Base),          /* StackBaseAddress */
    (uint32)(&Image$$OS_CORE0_STACK$$ZI$$Limit)           /* StackEndAddress */
};

const Os_HalCoreMpuConfigType OsMpu_ConfigSetCore0 = 
{
    &OsMpu_ConfigSet_Core0,
    &OsMpu_ConfigSet_OsStackCore0
};

const Os_HalMpuRegionType OsMpu_ConfigSet_Core1_Regions[1] =
{
    {
        0x00000000,          /* RegionNumber */
        (uint32)0x00000000U,          /* RegionBaseAddress */
        (uint32)(0x00000000U),                /* RegionEndAddress */
        MPU_EL1_R_EL0_R|MPU_EXECUTE_NEVER,
        MPU_REGION_ENABLE
    },
};

const Os_MpuConfigType OsMpu_ConfigSet_Core1 =
{
    (uint32)1,                  /* MpuRegionCount */
    OsMpu_ConfigSet_Core1_Regions                /* MpuRegions */
};

const Os_HalStackConfigAddressType OsMpu_ConfigSet_OsStackCore1 = 
{
    (uint32)(&Image$$OS_CORE1_STACK$$Base),          /* StackBaseAddress */
    (uint32)(&Image$$OS_CORE1_STACK$$ZI$$Limit)           /* StackEndAddress */
};

const Os_HalCoreMpuConfigType OsMpu_ConfigSetCore1 = 
{
    &OsMpu_ConfigSet_Core1,
    &OsMpu_ConfigSet_OsStackCore1
};
const Os_HalMpuRegionType OsMpu_ConfigSet_OsApplication_1_Regions[2] =
{
    {
        0x00000002,          /* RegionNumber */
        (uint32)0x00000000U,          /* RegionBaseAddress */
        (uint32)(0x00000000U),                /* RegionEndAddress */
        MPU_EL1_RW_EL0_NONE|MPU_EXECUTE_NEVER,
        MPU_REGION_ENABLE
    },
    {
        0x00000003,          /* RegionNumber */
        (uint32)0x00000000U,          /* RegionBaseAddress */
        (uint32)(0x00000000U),                /* RegionEndAddress */
        MPU_EL1_RW_EL0_RW|MPU_EXECUTE_NEVER,
        MPU_REGION_ENABLE
    },
};

const Os_MpuConfigType OsMpu_ConfigSet_OsApplication_1 =
{
    (uint32)2,                /* MpuRegionCount */
    OsMpu_ConfigSet_OsApplication_1_Regions                       /* MpuRegions */
};

CONSTP2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST) OsMpu_ConfigSet_ApplicationsRefs[OS_APPLICATION_TOTAL_NUM + 1U] =
{
    NULL_PTR,
    &OsMpu_ConfigSet_OsApplication_1,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR
};

const Os_HalMpuRegionType  OsMpu_ConfigSet_Task4_Regions[1] =
{
    {   
        0x00000004,          /* RegionNumber */
        (uint32)0x00000000U,          /* RegionBaseAddress */
        (uint32)(0x00000000U),                /* RegionEndAddress */
        MPU_EL1_RW_EL0_RW|MPU_EXECUTE_NEVER,
        MPU_REGION_ENABLE
    },
};

const Os_MpuConfigType OsMpu_ConfigSet_Task4 =
{
    (uint32)1,                                         /* MpuRegionCount */
    OsMpu_ConfigSet_Task4_Regions                     /* MpuRegions */
};

CONSTP2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST) OsMpu_ConfigSet_ObjectRefs[OS_MPU_COUNT + 1U] =
{   
    &OsMpu_ConfigSet_Task4,
    NULL_PTR
};

CONSTP2CONST(Os_AccessConfigType, TYPEDEF, OS_CONST) OsMpu_AccessCheck_ObjectRefs[OS_MPU_ACCESSCOUNT + 1U] =
{
    NULL_PTR
};
/***************************************Peripheral Region Start*************************************/

CONSTP2CONST(Os_PeripheralConfigType, TYPEDEF, OS_CONST)  OsMpu_PeripheralRefs[OS_PERIPHERALID_COUNT + 1U] =            
{
    NULL_PTR
};

/***************************************Peripheral Region End***************************************/



/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/






/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_mpu_hal.c
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
#include "Std_Types.h"
#include "Os_compiler_types.h"
#include "Os_mpu_types.h"
#include "Os_mpu_Cfg.h"
#include "Os_mpu_hal.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define SCTLR_MPU_MASK (1U << 0U)
#define SCTLR_BR_MASK  (1U << 17U)
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

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : OsMpu_Internal_HalSetRegion
*   Service ID              : None.
*   Description             : Set the MPU region config to hardware.
*   Parameters in           : PtrRegion: The pointer to region information.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) OsMpu_Internal_HalSetRegion
(
    P2CONST(Os_HalMpuRegionType, TYPEDEF, OS_CONST) PtrRegion
);

/****************************************************************************************************
*   Function Name           : OsMpu_Internal_HalEnable
*   Service ID              : None.
*   Description             : Enable MPU module.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) OsMpu_Internal_HalEnable
(
    void
);

/****************************************************************************************************
*   Function Name           : OsMpu_Internal_HalDisable
*   Service ID              : None.
*   Description             : Disable MPU module.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) OsMpu_Internal_HalDisable
(
    void
);

/****************************************************************************************************
*   Function Name           : OsMpu_Internal_HalDisable
*   Service ID              : None.
*   Description             : Enable MPU background.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) OsMpu_Internal_EnBackground
(
    void
);

/****************************************************************************************************
*   Function Name           : Os_Internal_MpuSelectRegion
*   Service ID              : None.
*   Description             : Select the processed region .
*   Parameters in           : RegionIndex: the index of region.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) Os_Internal_MpuSelectRegion
(
    uint32 RegionIndex
);

/****************************************************************************************************
*   Function Name           : Os_Internal_MpuDisBackground
*   Service ID              : None.
*   Description             : Disable MPU background.
*   Parameters in           : None.
*   Parameters inout        : None.
*   Parameters out          : None.
*   Sync/Async              : Synchronous.
*   Reentrancy              : Non-Reentrant.
*   Return value            : None.
*   Preconditions           : None.
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, OS_CODE) Os_Internal_MpuDisBackground
(
    void
);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

FUNC(void, OS_CODE) OsMpu_Internal_HalEnable
(
    void
)
{
    volatile uint32 SysCtrlReg;

    Os_Inf_GetCP(15, 0, SysCtrlReg, 1, 0, 0);
    SysCtrlReg |= SCTLR_MPU_MASK;
    Os_Inf_SetCP(15, 0, SysCtrlReg, 1, 0, 0);
}
FUNC(void, OS_CODE) OsMpu_Internal_HalDisable
(
    void
)
{
    volatile uint32 SysCtrlReg;

    Os_Inf_GetCP(15, 0, SysCtrlReg, 1, 0, 0);
    SysCtrlReg &= ~SCTLR_MPU_MASK;
    Os_Inf_SetCP(15, 0, SysCtrlReg, 1, 0, 0);
}

FUNC(void, OS_CODE) OsMpu_Internal_EnBackground
(
    void
)
{
    volatile uint32 SysCtrlReg;
    Os_Inf_GetCP(15, 0, SysCtrlReg, 1, 0, 0);
    SysCtrlReg |= SCTLR_BR_MASK;
    Os_Inf_SetCP(15, 0, SysCtrlReg, 1, 0, 0);
}

FUNC(void, OS_CODE) Os_Internal_MpuDisBackground
(
    void
)
{
    volatile uint32 SysCtrlReg;

    Os_Inf_GetCP(15, 0, SysCtrlReg, 1, 0, 0);
    SysCtrlReg &= ~SCTLR_BR_MASK;
    Os_Inf_SetCP(15, 0, SysCtrlReg, 1, 0, 0);
}

FUNC(void, OS_CODE) Os_Internal_MpuSelectRegion
(
    uint32 RegionIndex
)
{
    Os_Inf_SetCP(15, 0, RegionIndex, 6, 2, 1);
}

FUNC(void, OS_CODE) Os_Internal_MpuSetRegionBaseAddress
(
    uint32 BaseAddress
)
{
    Os_Inf_SetCP(15, 0, BaseAddress, 6, 3, 0);
}

FUNC(void, OS_CODE) Os_Internal_MpuSetRegionLimitAddress
(
    uint32 LimitAddress
)
{
    Os_Inf_SetCP(15, 0, LimitAddress, 6, 3, 1);
}

FUNC(void, OS_CODE) Os_Internal_MpuEnableRegion
(
    void
)
{
    volatile uint32 LimitAddress;

    Os_Inf_GetCP(15, 0, LimitAddress, 6, 3, 1);
    LimitAddress |= MPU_REGION_ENABLE;
    Os_Inf_SetCP(15, 0, LimitAddress, 6, 3, 1);
}

FUNC(void, OS_CODE) Os_Internal_MpuDisableRegion
(
    void
)
{
    volatile uint32 LimitAddress;

    Os_Inf_GetCP(15, 0, LimitAddress, 6, 3, 1);
    LimitAddress &= (uint32)~MPU_REGION_ENABLE;
    Os_Inf_SetCP(15, 0, LimitAddress, 6, 3, 1);

}

FUNC(void, OS_CODE) Os_Internal_MpuClearRegion
(
    void
)
{
    uint32 Address = 0;

    Os_Inf_SetCP(15, 0, Address, 6, 3, 0);
    Os_Inf_SetCP(15, 0, Address, 6, 3, 1);
}

FUNC(void, OS_CODE) OsMpu_Internal_HalSetRegion
(
    P2CONST(Os_HalMpuRegionType, TYPEDEF, OS_CONST) Region
)
{
    Os_Internal_MpuSelectRegion(Region->RegionNum);
    Os_Internal_MpuClearRegion();
    Os_Internal_MpuSetRegionBaseAddress(Region->RegionBaseAddr|Region->AccessControl);
    Os_Internal_MpuSetRegionLimitAddress(((Region->RegionEndAddr - 1U)&(~MPU_REGION_ALIGNMENT_MASK))|Region->EnableFlags);
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

FUNC(void, OS_CODE) OsMpu_Hal_CoreInit(
    P2CONST(Os_MpuConfigType , TYPEDEF, OS_CONST) CoreConfig
)
{
    uint32 RegionIndex;

    OsMpu_Internal_HalDisable();

    /* init core regions */
    for(RegionIndex = 0; RegionIndex < CoreConfig->RegionCounts; RegionIndex++)
    {
        OsMpu_Internal_HalSetRegion(&(CoreConfig->MpuRegions[RegionIndex]));
    }
    OsMpu_Internal_EnBackground();
    OsMpu_Internal_HalEnable();
} 

FUNC(void, OS_CODE)OsMpu_Hal_MpuSwitch(
    P2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST) MpuConfig
)
{
    uint32 RegionIndex;
    for(RegionIndex = 0; RegionIndex < MpuConfig->RegionCounts; RegionIndex++)
    {
        OsMpu_Internal_HalSetRegion(&(MpuConfig->MpuRegions[RegionIndex]));
    }
}

FUNC(void, OS_CODE) OsMpu_Hal_SetStack(
    P2CONST(Os_MpuConfigType , TYPEDEF, OS_CONST) StackConfig
)
 {
    uint32 RegionIndex;

    OsMpu_Internal_HalDisable();
    for(RegionIndex = OS_MPU_STACK_REGION_PROTECT_ONE; RegionIndex < MAX_REGION_COUNT + 1U; RegionIndex++)
    {
        Os_Internal_MpuSelectRegion(RegionIndex);
        Os_Internal_MpuClearRegion();
    }

    /* set stack region to the last three regions */
    for(RegionIndex = 0; RegionIndex < StackConfig->RegionCounts; RegionIndex++)
    {
        OsMpu_Internal_HalSetRegion(&(StackConfig->MpuRegions[RegionIndex]));
    }

    /* if there only two regins in stack , clear the last region */
    OsMpu_Internal_EnBackground();
    /*Disable all the three stack region */
    for(RegionIndex = OS_MPU_STACK_REGION_PROTECT_ONE; RegionIndex < MAX_REGION_COUNT + 1U; RegionIndex++)
    {
        Os_Internal_MpuSelectRegion(RegionIndex);
        Os_Internal_MpuDisableRegion();
    }

    /*Enable MPU again */
    OsMpu_Internal_HalEnable();
 }

FUNC(void, OS_CODE) OsMpu_Hal_EnableRegion(uint32 RegionIndex)
{
    if(RegionIndex < MAX_REGION_COUNT)
    {
        Os_Internal_MpuSelectRegion(RegionIndex);
        Os_Internal_MpuEnableRegion();
    }
}

FUNC(void, OS_CODE) OsMpu_Hal_DisableRegions(uint32 RegionIndex)
{
    if(RegionIndex < MAX_REGION_COUNT)
    {
        Os_Internal_MpuSelectRegion(RegionIndex);
        Os_Internal_MpuDisableRegion();
    }
}

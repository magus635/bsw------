/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_isr_hal.c
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
#include "common.h"
#include "Os_isr_hal.h"
#include "Os_isr_GICv3Register.h"
#include "Os_isr_Lcfg.h"
#include "Os_compiler_types.h"
#include "intc_hal.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define OS_ISR_HAL_EOIMODE_MASK (0x2U)

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
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
FUNC(void, OS_CODE) OsIsr_Hal_GetLevel
(
    P2VAR(Os_IsrLevelType, AUTOMATIC, OS_VAR) Level
)
{
    uint32 Pmr;

    /* Read value of ICC_PMR */
    Os_Inf_GetCP(15, 0, Pmr, 4, 6, 0);
    /* Get the interrupt level from ICC_PMR */
    *Level = Pmr >> 3U;
}

FUNC(void, OS_CODE) OsIsr_Hal_SetLevel
(
    Os_IsrLevelType Level
)
{
    Level = Level << 3U;
    /* Write to ICC_PMR */
    Os_Inf_SetCP(15, 0, Level, 4, 6, 0);
}

FUNC(void, OS_CODE) OsIsr_Hal_DisableInterruptSource
(
    uint32 IntID,
    CoreIdType CoreID
)
{
    /* If is SPI */
    if(IntID >= OS_ISR_MIN_SPI_ID)
    {
        GICv3(CoreID)->DISTRIBUTOR.GICDICENABLER[(IntID >> 5U) - 1U] = 1U << (IntID % 32U);
    }
    /* SGI and PPI */
    else
    {
        GICv3(CoreID)->REDISTRIBUTOR[CoreID & 1U].GICRICENABLER = 1U << IntID;
    }
}

FUNC(void, OS_CODE) OsIsr_Hal_EnableInterruptSource
(
    uint32 IntID,
    CoreIdType CoreID
)
{
    /* If is SPI */
    if(IntID >= OS_ISR_MIN_SPI_ID)
    {
        GICv3(CoreID)->DISTRIBUTOR.GICDISENABLER[(IntID >> 5U) - 1U] = 1U << (IntID % 32U);
    }
    /* SGI and PPI */
    else
    {
        GICv3(CoreID)->REDISTRIBUTOR[CoreID & 1U].GICRISENABLER = 1U << IntID;
    }
}

FUNC(void, OS_CODE) OsIsr_Hal_ClearPendingInterrupt
(
    uint32 IntID,
    CoreIdType CoreID
)
{
    /* SPI */
    if(IntID >= OS_ISR_MIN_SPI_ID)
    {
        GICv3(CoreID)->DISTRIBUTOR.GICDICPENDR[(IntID >> 5U) -1U] = 1 << (IntID % 32U);
    }
    /* PPI or SGI */
    else
    {
        GICv3(CoreID)->REDISTRIBUTOR[CoreID & 1U].GICRICPENDR = 1 << IntID;
    }
}

FUNC(boolean, OS_CODE) OsIsr_Hal_IsEnable
(
    uint32 IntID,
    CoreIdType CoreID
)
{
    boolean Res;

    /* SPI */
    if(IntID >= OS_ISR_MIN_SPI_ID)
    {
        Res = (GICv3(CoreID)->DISTRIBUTOR.GICDICENABLER[(IntID >> 5U) -1U] >> (IntID % 32U)) & 1U;
    }
    /* PPI or SGI */
    else
    {
        Res = (GICv3(CoreID)->REDISTRIBUTOR[CoreID & 1U].GICRICENABLER >> IntID) & 1U;
    }
    return Res;
}

FUNC(void, OS_CODE) OsIsr_Hal_EndOfInterrupt
(
    uint32 IntID,
    CoreIdType CoreID
)
{
    uint32 EoiMode;

    /* Get value of ICC_CTRL */
    Os_Inf_GetCP(15, 0, EoiMode, 12, 12, 4);
    /* Get value of EOI_MODE from ICC_CTRL */
    EoiMode = EoiMode & OS_ISR_HAL_EOIMODE_MASK;
    /* End of Interrupt */
    Os_Inf_SetCP(15, 0, IntID, 12, 12, 1);
    /* If EoI will not deactivate interrupt */
    if(EoiMode != 0)
    {
        /* SPI */
        if(IntID >= OS_ISR_MIN_SPI_ID)
        {
            GICv3(CoreID)->DISTRIBUTOR.GICDICACTIVER[(IntID >> 5U) - 1U] = 1 << (IntID % 32U);
        }
        /* PPI/SGI */
        else
        {
            GICv3(CoreID)->REDISTRIBUTOR[CoreID & 1U].GICRICACTIVER = 1 << IntID;
        }
    }
}

FUNC(void, OS_CODE) OsIsr_Hal_InstallIsr
(
    P2CONST(Os_Isr_Hal_ConfigType, AUTOMATIC, OS_CONST) IsrHwConfig
)
{
    Intc_InterruptConfig IntConfig;

    IntConfig.intID = IsrHwConfig->intID;
    IntConfig.group = IsrHwConfig->group;
    IntConfig.priority = IsrHwConfig->priority;
    IntConfig.triggerMethod = IsrHwConfig->triggerMethod;
    IntConfig.enable = IsrHwConfig->enable;
#ifdef OS_THA6206
    IntConfig.coreID = IsrHwConfig->coreID;
#endif

    OsIntc_Hal_InstallInterrupt(&IntConfig, 1);
}

FUNC(void, OS_CODE) OsIsr_Hal_TriggerSoftwareInterrupt
(
    uint32 IntId,
    uint32 TargetCoreId
)
{
    uint64 IntInfo;

    TargetCoreId = 1UL << TargetCoreId;
    /* Set intID of SGI and write targetList */
    IntInfo = ((uint64)IntId << 24ULL) | ((uint64)TargetCoreId);
    /* Write intInfo into register. */
    SET_CP64(15, 0, IntInfo, 12);
}

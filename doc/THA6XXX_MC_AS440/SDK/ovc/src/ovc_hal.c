/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    ovc_hal.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of OVC module.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 * #ovc_hal_c_REF_1:MISRAC2012-Rule-19.2;
 * Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
 *
 *#ovc_hal_c_REF_2:MISRAC2012-Dir-11.4;
 * Justification: Converting integers to object pointers to reduce register access complexity.
 *
 * #ovc_hal_c_REF_3:MISRAC2012-Dir-4.9;
 * Justification: Function like macros are used to reduce code complexity.
 *
 * #ovc_hal_c_REF_4:MISRAC2012-Rule-10.5;
 * Justification: Cortex-R52+ lacks bool type, minimum unit is uint8.
 *
 *#ovc_hal_c_REF_5:MISRAC2012-Rule-1.2;
 * Justification: Inline assembly for CPU-specific operations.
 *
 * #ovc_hal_c_REF_6:MISRAC2012-Rule-2.1;
 * Justification: The interface is called by the application layer.
 *
 *#ovc_hal_c_REF_7:MISRAC2012-Dir-4.3;
 * Justification: Mixing inline assembly with C code reduces code complexity.
 * 
 * #ovc_hal_c_REF_8:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #ovc_hal_c_REF_9:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 * 
 * #ovc_hal_c_REF_10:MISRAC2012-Rule-8.7; 
 * Justification:The interface is called by the application layer.
 */

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "ovc_std.h"
#include "ovc_hal.h"
#include "ovc_register.h"
#include "cpuwdt_hal.h"
#include "tha6_cfg.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /*INPUT_ARG_DETECT*/
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
#define OVC_ENABLE_MASK (0x00000001U)
#define OVC_DSIABLE_MASK (0x00000001U)

/* #Violation: ovc_hal_c_REF_8 */
#define OVC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ovc_hal_c_REF_9 */
#include "Ovc_MemMap.h"

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: ovc_hal_c_REF_6 */
boolean Ovc_Hal_InitBlock(OVC_MODULE *const pOvc, const Ovc_BlockConfig *const pConfig)
{
    boolean ret;
    ret = TRUE;
    OVC_BLOCK *ovcBlockPtr;
    /* #Violation: ovc_hal_c_REF_1 */
    OVC_RBAR rbarVal;
    rbarVal.U = 0U;

#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ovc_hal_c_REF_2 */
    /* #Violation: ovc_hal_c_REF_3 */
    /* #Violation: ovc_hal_c_REF_4 */
    Assert((boolean)CHECK_OVC_BASE(pOvc));
    /* #Violation: ovc_hal_c_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: ovc_hal_c_REF_4 */
    /* #Violation: ovc_hal_c_REF_3 */
    Assert((boolean)(TRUE == (uint32)OVC_CHECK_TARGET_ADDRESS_REGION(pConfig->targetBaseAddress)));
    /* #Violation: ovc_hal_c_REF_4 */
    /* #Violation: ovc_hal_c_REF_3 */
    Assert((boolean)(TRUE == (uint32)OVC_CHECK_OVERLAY_ADDRESS_REGION(pConfig->redirectionBaseAddress)));
#endif /*INPUT_ARG_DETECT*/

    /* Address alignment check */
    ret &= Ovc_Std_AddrAligCheck(pConfig->targetBaseAddress, pConfig->redirectionBaseAddress, (uint32)(pConfig->blockSize));

    if(TRUE == ret)
    {
        /* Disable START and STOP control */
        /* #Violation: ovc_hal_c_REF_5 */
        ret &= Ovc_Std_DisableOVSTARTandOVSTOP(pOvc, (uint32)pConfig->coreId);

        /* Disable the overlay block */
        ret &= Ovc_Hal_DisableBlock(pOvc, pConfig->coreId, pConfig->blockId);

        /* Select the user-defined overlay block */
        ovcBlockPtr = (OVC_BLOCK *)&(pOvc->CORE[pConfig->coreId].BLOCK[pConfig->blockId]);

        /* Initialize the memory type */
        rbarVal.B.MEMSEL = (uint32)pConfig->redirectMemType;
        /* Initialize the redirection base address */
        rbarVal.B.BASE = (uint32)(pConfig->redirectionBaseAddress >> 5U);
        ovcBlockPtr->RBAR.U = rbarVal.U;

        /* Initialize the target base address */
        ovcBlockPtr->TAR.B.BASE = (uint32)(pConfig->targetBaseAddress >> 5U);

        /* Initialize the block size */
        ovcBlockPtr->MASK.B.MASK = (uint32)(pConfig->blockSize);

        /* Enable the overlay block function */
        ret &= Ovc_Hal_EnableBlock(pOvc, pConfig->coreId, pConfig->blockId);

        /* Set the overlay of core has been configured */
        ret &= Ovc_Std_FinishOverlayConfig(pOvc, (uint32)pConfig->coreId);
    }
    
    return ret;
}

/* #Violation: ovc_hal_c_REF_6 */
/* #Violation: ovc_hal_c_REF_7 */
boolean Ovc_Hal_EnableCore(OVC_MODULE *const pOvc, Ovc_CoreId coreId)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ovc_hal_c_REF_2 */
    /* #Violation: ovc_hal_c_REF_3 */
    /* #Violation: ovc_hal_c_REF_4 */
    Assert((boolean)CHECK_OVC_BASE(pOvc));
#endif /*INPUT_ARG_DETECT*/
    /* #Violation: ovc_hal_c_REF_5 */
    regVal = pOvc->EN.U;
    regVal |= ((uint32)OVC_ENABLE_MASK << (uint32)coreId);
    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    /* Value 1 indicates OVC is enable on core0 or core1*/
    pOvc->EN.U = regVal;
    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    /* #Violation: ovc_hal_c_REF_5 */
    ret = Ovc_Register_ReadBack_Check(ret, regVal, pOvc->EN.U);
    /* Close bypass */
    ret &= Ovc_Hal_BypassControl(pOvc, coreId, OVC_NON_BYPASS_FLAGS);
    return ret;
}

/* #Violation: ovc_hal_c_REF_6 */
/* #Violation: ovc_hal_c_REF_7 */
boolean Ovc_Hal_DisableCore(OVC_MODULE *const pOvc, Ovc_CoreId coreId)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ovc_hal_c_REF_2 */
    /* #Violation: ovc_hal_c_REF_3 */
    /* #Violation: ovc_hal_c_REF_4 */
    Assert((boolean)CHECK_OVC_BASE(pOvc));
#endif /*INPUT_ARG_DETECT*/

    /* #Violation: ovc_hal_c_REF_5 */
    regVal = pOvc->EN.U;
    regVal &= ~((uint32)OVC_DSIABLE_MASK << (uint32)coreId);
    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    /* Value 0 indicates OVC is enable on core0 or core1*/
    pOvc->EN.U = regVal;
    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    /* #Violation: ovc_hal_c_REF_5 */
    ret = Ovc_Register_ReadBack_Check(ret, regVal, pOvc->EN.U);

    return ret;
}

/* #Violation: ovc_hal_c_REF_10 */
/* #Violation: ovc_hal_c_REF_7 */
boolean Ovc_Hal_EnableBlock(OVC_MODULE *const pOvc, Ovc_CoreId coreId, Ovc_BlockId blockId)
{
    boolean ret;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ovc_hal_c_REF_2 */
    /* #Violation: ovc_hal_c_REF_3 */
    /* #Violation: ovc_hal_c_REF_4 */
    Assert((boolean)CHECK_OVC_BASE(pOvc));
#endif /*INPUT_ARG_DETECT*/

    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    /* Overlay block enabled */
    pOvc->CORE[coreId].BLOCK[blockId].RBAR.B.OVBLKEN = 1U;
    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    /* #Violation: ovc_hal_c_REF_5 */
    ret = Ovc_Register_ReadBack_Check(ret, (uint32)1U, pOvc->CORE[coreId].BLOCK[blockId].RBAR.B.OVBLKEN);

    return ret;
}

/* #Violation: ovc_hal_c_REF_10 */
/* #Violation: ovc_hal_c_REF_7 */
boolean Ovc_Hal_DisableBlock(OVC_MODULE *const pOvc, Ovc_CoreId coreId, Ovc_BlockId blockId)
{
    boolean ret;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ovc_hal_c_REF_2 */
    /* #Violation: ovc_hal_c_REF_3 */
    /* #Violation: ovc_hal_c_REF_4 */
    Assert((boolean)CHECK_OVC_BASE(pOvc));
#endif /*INPUT_ARG_DETECT*/

    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    /* Overlay block disabled */
    pOvc->CORE[coreId].BLOCK[blockId].RBAR.B.OVBLKEN = 0U;
    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    /* #Violation: ovc_hal_c_REF_5 */
    ret = Ovc_Register_ReadBack_Check(ret, (uint32)0U, pOvc->CORE[coreId].BLOCK[blockId].RBAR.B.OVBLKEN);

    return ret;
}

/* #Violation: ovc_hal_c_REF_6 */
uint32 Ovc_Hal_GetErrorFlagStatus(const OVC_MODULE *const pOvc, Ovc_CoreId coreId)
{
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ovc_hal_c_REF_2 */
    /* #Violation: ovc_hal_c_REF_3 */
    /* #Violation: ovc_hal_c_REF_4 */
    Assert((boolean)CHECK_OVC_BASE(pOvc));
#endif /*INPUT_ARG_DETECT*/

    return (pOvc->CORE[coreId].ERRCON.U >> 30U);
}

/* #Violation: ovc_hal_c_REF_6 */
void Ovc_Hal_ClearErrorFlagStatus(OVC_MODULE *const pOvc, Ovc_CoreId coreId)
{
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ovc_hal_c_REF_2 */
    /* #Violation: ovc_hal_c_REF_3 */
    /* #Violation: ovc_hal_c_REF_4 */
    Assert((boolean)CHECK_OVC_BASE(pOvc));
#endif /*INPUT_ARG_DETECT*/

    pOvc->CORE[coreId].ERRCON.B.INT_CLR = 1U;
    pOvc->CORE[coreId].ERRCON.B.INT_CLR = 0U;
}

/* #Violation: ovc_hal_c_REF_10 */
/* #Violation: ovc_hal_c_REF_7 */
boolean Ovc_Hal_BypassControl(OVC_MODULE *const pOvc, Ovc_CoreId coreId, Ovc_BypassFlags flags)
{
    boolean ret;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ovc_hal_c_REF_2 */
    /* #Violation: ovc_hal_c_REF_3 */
    /* #Violation: ovc_hal_c_REF_4 */
    Assert((boolean)CHECK_OVC_BASE(pOvc));
#endif /*INPUT_ARG_DETECT*/

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();

    
#if defined(THA6_THA6206) || defined(THA6_THA6104) || defined(THA6_THA6206D)
    (void)coreId;
    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    pOvc->BYPASS0.U = (uint32)flags;
    /* #Violation: ovc_hal_c_REF_5 */
    DSB();
    ret = Ovc_Register_ReadBack_Check(ret, (uint32)flags, pOvc->BYPASS0.U);
#endif

#if defined(THA6_THA6412)
    /*Clear ENDINIT protection,the register protected by E can be written */
    if (OVC_CORE_ID_0 == coreId)
    {
        /* #Violation: ovc_hal_c_REF_5 */
        DSB();
        pOvc->BYPASS0.U = (uint32)flags;
        /* #Violation: ovc_hal_c_REF_5 */
        DSB();
        ret = Ovc_Register_ReadBack_Check(ret, (uint32)flags, pOvc->BYPASS0.U);
    }
    else
    {
        /* #Violation: ovc_hal_c_REF_5 */
        DSB();
        pOvc->BYPASS1.U = (uint32)flags;
        /* #Violation: ovc_hal_c_REF_5 */
        DSB();
        ret = Ovc_Register_ReadBack_Check(ret, (uint32)flags, pOvc->BYPASS1.U);
    }
#endif /* defined(THA6_THA6412) */
    ret &= Cpuwdt_Hal_SetEndinit();
    
    ENABLE_ALL_INTERRUPTS();
    return ret;
}

/* #Violation: ovc_hal_c_REF_8 */
#define OVC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ovc_hal_c_REF_9 */
#include "Ovc_MemMap.h"

/**********************************************************************************************************************
**                                                    End of File                                                    **
**********************************************************************************************************************/

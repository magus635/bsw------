/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dma_hal.c
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of DMA module.
 *********************************************************************************************************************/

/*
*#Violation Summary
*
*#dma_hal_c_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#dma_hal_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Limitation of Coretex-R52+ Core; Boolean can only be representes as unit8.
*
*#dma_hal_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#dma_hal_c_REF_4:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to register.
*
*#dma_hal_c_REF_5:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#dma_hal_c_REF_6:MISRAC2012-Dir-4.1; 
* Justification: Number of loops is set by different configurations.
*
*#dma_hal_c_REF_7:MISRAC2012-Rule-15.7; 
* Justification: MISRAC2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#dma_hal_c_REF_8: MISRAC2012-Rule-16.4; 
* Justification: MISRAC2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#dma_hal_c_REF_9:CertC-DCL19-C;
* Justification: Reserved API for user access.
*
*#dma_hal_c_REF_10:CertC-DCL02-C;
* Justification: Company-specific naming conventions are applied. Developers will not be confused.
*
*#dma_hal_c_REF_11:CertC-DCL15-C;
* Justification: Reserved API for user access.
*
*#dma_hal_c_REF_12:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#dma_hal_c_REF_13:CWE-1071;
* Justification: MISRAC2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#dma_hal_c_REF_14:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#dma_hal_c_REF_15:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#dma_hal_c_REF_16:MISRAC2012-Rule-8.7;
* Justification: The function is used by other file.
*
*#dma_hal_c_REF_17:MISRAC2012-Rule-2.2;
* Justification: Value used in assembly code.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "dma_register.h"
#include "dma_hal.h"
#include "dma_std.h"
#include "safewdt_hal.h"
#include "rcc_hal.h"
#include "Platform_Types.h"
#include "multicore.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* DMA channel interrupt mask */
#define DMA_CHANNEL_INTERRUPT_MASK (0x0000003FU)
/* Local access CPUXXTCM address mask */
#define DMA_LOCALACCESS_CPUXXTCM_ADDRMASK (0xFFC00000U)
/* AXI access CPU0XTCM address mask */
#define DMA_AXIACCESS_CPU0XTCM_ADDRMASK (0x30000000U)
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* AXI access CPU1XTCM address mask */
#define DMA_AXIACCESS_CPU1XTCM_ADDRMASK (0x30400000U)
#if defined(THA6_THA6412)
/* AXI access CPU2XTCM address mask */
#define DMA_AXIACCESS_CPU2XTCM_ADDRMASK (0x31000000U)
/* AXI access CPU3XTCM address mask */
#define DMA_AXIACCESS_CPU3XTCM_ADDRMASK (0x31400000U)
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Dma_Hal_InternalAddrConvert
 * Description:  Check whether the input address is an internal access address within the CPUXXTCM or PFLASH, if it is,
 *v              this API will automatically be automatically converted to external access address
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        Address: Original address
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2026/02/05    01359      Create
 *********************************************************************************************************************/
static uint32 Dma_Hal_InternalAddrConvert(uint32 address);
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static uint32 Dma_Hal_InternalAddrConvert(uint32 address)
{
    MultiCoreID id;
    /* Check whether the address is an internal access address within the CPUXXTCM */
    if((address & DMA_LOCALACCESS_CPUXXTCM_ADDRMASK) == 0U)
    {
        id = Multicore_GetCoreID();
        switch(id)
        {
            case MULTICOREID_CPU0:
                /* If it is an internal access address, it will be automatically converted to an AXI access address */
                address += DMA_AXIACCESS_CPU0XTCM_ADDRMASK;
                break;
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
            case MULTICOREID_CPU1:
                /* If it is an internal access address, it will be automatically converted to an AXI access address */
                address += DMA_AXIACCESS_CPU1XTCM_ADDRMASK;
                break;
#if defined(THA6_THA6412)
            case MULTICOREID_CPU2:
                /* If it is an internal access address, it will be automatically converted to an AXI access address */
                address += DMA_AXIACCESS_CPU2XTCM_ADDRMASK;
                break;
            case MULTICOREID_CPU3:
                /* If it is an internal access address, it will be automatically converted to an AXI access address */
                address += DMA_AXIACCESS_CPU3XTCM_ADDRMASK;
                break;
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */
            default:
                /* Will not enter */
                (void)address;
                break;
        }
    }
    /* Check whether the address is an internal access address within the PFLASH */
    else if((address & FLASH_PFLASH_INTERNALADDR_MASKVALUE) == FLASH_PFLASH_INTERNALADDR_COMPVALUE)
    {
        /* If it is an internal access address, it will be automatically converted to external device address in PFLASH*/
        address += FLASH_PFLASH_INTERNALTODEVICE_ADDR_OFFSET;
    }
    else
    {
        (void)address;
    }
    
    return address;
}
/**********************************************************************************************************************
 *                                            Private Constant Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: dma_hal_c_REF_14 */
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dma_hal_c_REF_15 */
#include "Dma_MemMap.h"
/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_ResetDma(DMA_MODULE *const pDma)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_BASE(pDma));
#endif /* INPUT_ARG_DETECT */
    Rcc_ModuleRst moduleDmaSel;
    uint8 channelID;
    uint8 channelMaxID;
    uint8 reqMuxMax;
    uint8 reqMux;
    boolean ret;
    Rcc_ErrorFlag rccFlag;

    ret = TRUE;
    /* Select the maximum channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_12 */
    /* #Violation: dma_hal_c_REF_3 */
    channelMaxID = (uint8)GET_DMA_MAX_CH(pDma);
    /* Safety disable channel, will not lose data of DMA FIFO */
    for(channelID = 0; channelID < channelMaxID; channelID++)
    {
#if defined(THA6_THA6206)  || defined(THA6_THA6206D)
        Dma_Hal_DisableChannel(pDma, channelID);
#endif
#if defined(THA6_THA6412) || defined(THA6_THA6104)
        ret &= Dma_Hal_SafeDisableChannel(pDma, channelID);
#endif
    }
    /* Rest DMA REQMUX */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_12 */
    /* #Violation: dma_hal_c_REF_3 */
    reqMuxMax = GET_DMA_MAX_MUXREQ(pDma);
    for(reqMux = 0U; reqMux <= reqMuxMax; reqMux++)
    {
#if defined(THA6_THA6206)  || defined(THA6_THA6206D)
            pDma->REQMUX[reqMux].B.REQMUX = 0xFF;
            ret = Dma_Register_ReadBack_Check(ret, 0xFF, pDma->REQMUX[reqMux].B.REQMUX);
#endif
#if defined(THA6_THA6412) || defined(THA6_THA6104)
            pDma->REQMUX[reqMux].B.REQMUX = 0x1FF;
            ret = Dma_Register_ReadBack_Check(ret, 0x1FF, pDma->REQMUX[reqMux].B.REQMUX);
#endif

    }
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_12 */
    /* #Violation: dma_hal_c_REF_3 */
    moduleDmaSel = (Rcc_ModuleRst)GET_DMA_RCC_RST_NUM(pDma);
    rccFlag = Rcc_Hal_TrigModuleRst(moduleDmaSel);
    if(rccFlag == RCC_ERRORFLAG_SUCCESS)
    {
        ret &= TRUE;
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_EnableDma(DMA_MODULE *const pDma)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_BASE(pDma));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = Dma_Std_EnableDma(pDma);
    return ret;
}


/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_DisableDma(DMA_MODULE *const pDma)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_BASE(pDma));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = Dma_Std_DisableDma(pDma);
    return ret;
}


/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_DeInitChannel(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;
 
    /* Clear channel all status */
    pDma->CH[channelID].INTCLR.U = 0x3FU;
    pDma->CH[channelID].DBSTS.U = 0x3U;

    pDma->CH[channelID].CONFIG.U = 0U;
    pDma->CH[channelID].CONTROL.U = 0U;
    pDma->CH[channelID].SRCADDR.U = 0U;
    pDma->CH[channelID].DESTADDR.U = 0U;
    pDma->CH[channelID].LLIREG.U = 0U;
    pDma->CH[channelID].ADVCONFIG.U = 0U;
    pDma->CH[channelID].PATCONFIG.U = 0U;
    pDma->CH[channelID].SWADDR.U = 0U;
    pDma->CH[channelID].DBCONTROL.U = 0U;
    pDma->CH[channelID].PAT.U = 0U;
    pDma->CH[channelID].PATMSK.U = 0U;
    pDma->CH[channelID].THR.U = 0U;
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    pDma->CH[channelID].HALT.U = 0U;
#endif
    
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].CONFIG.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].CONTROLINIT.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].SRCADDR.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].DESTADDR.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].LLIREG.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].ADVCONFIG.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].PATCONFIG.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].SWADDR.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].DBCONTROL.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].PAT.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].PATMSK.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].THR.U);
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].HALT.U);
#endif
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_DeInitChannelWithCRC(DMA_MODULE *const pDma, uint8 channelID)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    /* Clear all interrupt status */
    /* Unlock safe endinit protect */
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    Dma_Std_ClearAllStatus(pDma, channelID);
    /* Lock safe endinit protect */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();

    pDma->CH[channelID].CONFIG.U = 0U;
    pDma->CH[channelID].CONTROL.U = 0U;
    pDma->CH[channelID].SRCADDR.U = 0U;
    pDma->CH[channelID].DESTADDR.U = 0U;
    pDma->CH[channelID].LLIREG.U = 0U;
    pDma->CH[channelID].ADVCONFIG.U = 0U;
    pDma->CH[channelID].PATCONFIG.U = 0U;
    pDma->CH[channelID].SWADDR.U = 0U;
    pDma->CH[channelID].DBCONTROL.U = 0U;
    pDma->CH[channelID].PAT.U = 0U;
    pDma->CH[channelID].PATMSK.U = 0U;
    /* Unlock safe endinit protect */
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    pDma->CH[channelID].CRCCONFIG.U = 3U;
    pDma->CH[channelID].EXPLLICRC.U = 0U;
    /* Lock safe endinit protect */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Dma_Register_ReadBack_Check(ret, 3U, pDma->CH[channelID].CRCCONFIG.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].EXPLLICRC.U);
    pDma->CH[channelID].THR.U = 0U;
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    pDma->CH[channelID].HALT.U = 0U;
#endif

    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].CONFIG.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].CONTROLINIT.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].SRCADDR.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].DESTADDR.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].LLIREG.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].ADVCONFIG.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].PATCONFIG.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].SWADDR.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].DBCONTROL.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].PAT.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].PATMSK.U);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].THR.U);
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].HALT.U);
#endif

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_EnableChannel(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = Dma_Std_EnableChannel(pDma, channelID);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
void Dma_Hal_DisableChannel(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    Dma_Std_DisableChannel(pDma, channelID);
}

/* #Violation: dma_hal_c_REF_16 */
/* #Violation: dma_hal_c_REF_11 */
/* #Violation: dma_hal_c_REF_9 */
boolean Dma_Hal_SafeDisableChannel(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
#if defined(THA6_THA6206)  || defined(THA6_THA6206D)
    /*THA6206 does not support the Halt function, so THA6206 cannot support Safety disable channel function*/
    (void)pDma;
    (void)channelID;
    ret = FALSE;
#endif
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    uint16 delayCount;
    boolean activeStatus;
    delayCount = 0xFFFF;
    activeStatus = TRUE;

    /* Halt the channel */
    ret = Dma_Std_SuspendChannel(pDma, channelID, TRUE);
    /* Waiting for channel inactivity */
    for(; (delayCount > 0U) && (0U != activeStatus); delayCount--)
    {
        activeStatus = Dma_Std_GetActiveStatus(pDma, channelID);
    }
    /* Disable channel */
    Dma_Std_DisableChannel(pDma, channelID);
    ret &= Dma_Std_SuspendChannel(pDma, channelID, FALSE);
#endif
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_SuspendChannel(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = Dma_Std_SuspendChannel(pDma, channelID, 1U);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_ResumeChannel(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = Dma_Std_SuspendChannel(pDma, channelID, 0U);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_InitChannelTransfer(DMA_MODULE *const pDma, uint8 channelID, const Dma_ChannelTransferConfig *const pConfig)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* Check transfer size */
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(pConfig->transferSize < 4096U));
    if(pConfig->flowControlAndTransferType > DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2P)
    {
        /* #Violation: dma_hal_c_REF_2 */
        Assert((boolean)(0U == (boolean)pConfig->transferSize));
    }
    /* Source and destination address should be align with transfer width */
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pConfig->transferWidth & 0x7U)) - 1U) & pConfig->source.address)) );
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pConfig->transferWidth & 0x7U)) - 1U) & pConfig->destination.address)));
#endif /* INPUT_ARG_DETECT */
    /* #Violation: dma_hal_c_REF_4 */
    DMA_CH_CONTROL controlDma;
    /* #Violation: dma_hal_c_REF_4 */
    DMA_CH_CONFIG configDma;
    boolean ret;
    ret = TRUE;

    /* Write source and destination address registers */
    pDma->CH[channelID].SRCADDR.U = Dma_Hal_InternalAddrConvert(pConfig->source.address);
    pDma->CH[channelID].DESTADDR.U = Dma_Hal_InternalAddrConvert(pConfig->destination.address);
    ret = Dma_Register_ReadBack_Check(ret, Dma_Hal_InternalAddrConvert(pConfig->source.address), pDma->CH[channelID].SRCADDR.U);
    ret = Dma_Register_ReadBack_Check(ret, Dma_Hal_InternalAddrConvert(pConfig->destination.address), pDma->CH[channelID].DESTADDR.U);
    /* Write control register */
    controlDma.U = pDma->CH[channelID].CONTROL.U;
    controlDma.B.SI = (uint32)pConfig->source.increment;
    controlDma.B.DI = (uint32)pConfig->destination.increment;
    controlDma.B.SBSIZE = (uint32)pConfig->source.burstSize;
    controlDma.B.DBSIZE = (uint32)pConfig->destination.burstSize;
    controlDma.B.SWIDTH = (uint32)pConfig->transferWidth;
    controlDma.B.DWIDTH = (uint32)pConfig->transferWidth;
    controlDma.B.TRANSIZE = (uint32)pConfig->transferSize;
    controlDma.B.I = 1U;
    /* The default setting for the destination is MASTER2 and source is MASTER1*/
    controlDma.B.D = 1U;
    controlDma.B.S = 0U;
    pDma->CH[channelID].CONTROL.U = controlDma.U;
    ret = Dma_Register_ReadBack_Check(ret, controlDma.U, pDma->CH[channelID].CONTROLINIT.U);
    /* Write configuration register and REQMUX register*/
    configDma.U = pDma->CH[channelID].CONFIG.U;
    configDma.B.FLOWCTR = (uint32)pConfig->flowControlAndTransferType;
    /* Configuration source request */
    ret &= Dma_Std_SetGlobalRequest(pDma, pConfig->sourceRequest.request, pConfig->sourceRequest.requestMUX);
    configDma.B.SRCPERH = pConfig->sourceRequest.request;

    /* Configuration destination request */
    ret &= Dma_Std_SetGlobalRequest(pDma, pConfig->destinationRequest.request, pConfig->destinationRequest.requestMUX);
    configDma.B.DESTPERH = pConfig->destinationRequest.request;

    pDma->CH[channelID].CONFIG.U = configDma.U;
    ret = Dma_Register_ReadBack_Check(ret, configDma.U, pDma->CH[channelID].CONFIG.U);

    /* By default, terminal count and bus error and transfer size threshold interrupts mask are enabled */
    ret &= Dma_Std_SetTerminalCountInterruptMask(pDma, channelID, 1U);
    ret &= Dma_Std_SetErrorInterruptMask(pDma, channelID, 1U);
    ret &= Dma_Std_SetTransferSizeThresholdInterruptMask(pDma, channelID, 1U);
    ret &= Dma_Std_SetTransferSizeThresholdInterrupt(pDma, channelID, 1U);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
void Dma_Hal_ReInitChannelTransfer(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    pDma->CH[channelID].SRCADDR.U = pDma->CH[channelID].SRCADDRINIT.U;
    pDma->CH[channelID].DESTADDR.U = pDma->CH[channelID].DESTADDRINIT.U;
    pDma->CH[channelID].LLIREG.U = pDma->CH[channelID].LLIREGINIT.U;
    pDma->CH[channelID].CONTROL.U = pDma->CH[channelID].CONTROLINIT.U;
}

/* #Violation: dma_hal_c_REF_5 */
uint16 Dma_Hal_GetRemainderTransferNum(const DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    return (uint16)pDma->CH[channelID].CONTROL.B.TRANSIZE;
}

/* #Violation: dma_hal_c_REF_5 */
/* #Violation: dma_hal_c_REF_10 */
boolean Dma_Hal_SetTransferSizeThreshold(DMA_MODULE *const pDma, uint8 channelID, uint16 thr)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* If the peripheral as flow controller, set thr = 0 */
    if(pDma->CH[channelID].CONFIG.B.FLOWCTR > (uint32)DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2P)
    {
        /* #Violation: dma_hal_c_REF_2 */
        Assert((boolean)((boolean)0U == (boolean)thr));
    }
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;
    pDma->CH[channelID].THR.B.THR = (uint16)thr;
    ret = Dma_Register_ReadBack_Check(ret, (uint16)thr, pDma->CH[channelID].THR.B.THR);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_InitShadowOperation(DMA_MODULE *const pDma, uint8 channelID, const Dma_ShadowOperationConfig *const pConfig)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* Source and destination address should be align with transfer width */
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pConfig->transferWidth & 0x7U)) - 1U) & pConfig->source.address)) );
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pConfig->transferWidth & 0x7U)) - 1U) & pConfig->destination.address)));
#endif /* INPUT_ARG_DETECT */
    /* #Violation: dma_hal_c_REF_4 */
    /* #Violation: dma_hal_c_REF_10 */
    DMA_CH_CONTROL control;
    boolean ret;
    ret = TRUE;

    /* Write source and destination address registers */
    pDma->CH[channelID].SRCADDRINIT.U = Dma_Hal_InternalAddrConvert(pConfig->source.address);
    pDma->CH[channelID].DESTADDRINIT.U = Dma_Hal_InternalAddrConvert(pConfig->destination.address);
    /* Write LLI address registers */
    pDma->CH[channelID].LLIREGINIT.B.LLI = (pConfig->linkedListItemAddress >> 2U);
    ret = Dma_Register_ReadBack_Check(ret, Dma_Hal_InternalAddrConvert(pConfig->source.address), pDma->CH[channelID].SRCADDRINIT.U);
    ret = Dma_Register_ReadBack_Check(ret, Dma_Hal_InternalAddrConvert(pConfig->destination.address), pDma->CH[channelID].DESTADDRINIT.U);
    ret = Dma_Register_ReadBack_Check(ret, (pConfig->linkedListItemAddress >> 2U), pDma->CH[channelID].LLIREGINIT.B.LLI);
    /* Write control register */
    control.U = pDma->CH[channelID].CONTROLINIT.U;
    control.B.SI = (uint32)pConfig->source.increment;
    control.B.DI = (uint32)pConfig->destination.increment;
    control.B.SBSIZE = (uint32)pConfig->source.burstSize;
    control.B.DBSIZE = (uint32)pConfig->destination.burstSize;
    control.B.SWIDTH = (uint32)pConfig->transferWidth;
    control.B.DWIDTH = (uint32)pConfig->transferWidth;
    control.B.TRANSIZE = pConfig->transferSize;
    control.B.I = 1U;
    pDma->CH[channelID].CONTROLINIT.U = control.U;
    ret = Dma_Register_ReadBack_Check(ret, control.U, pDma->CH[channelID].CONTROLINIT.U);
    /* Enable continue mode */
    pDma->CH[channelID].ADVCONFIG.B.CMODEN = 1U;
    ret = Dma_Register_ReadBack_Check(ret, 1U, pDma->CH[channelID].ADVCONFIG.B.CMODEN);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
void Dma_Hal_WriteLinkedListItem(const DMA_MODULE *const pDma, uint8 channelID, Dma_LinkedListItem *const pAddr,
                                 const Dma_LinkedListItemConfig *const pConfig)
{
    /* #Violation: dma_hal_c_REF_4 */
    DMA_CH_CONTROL lliControl;
    uint32         lliBufAddr;
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pAddr));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* Check address align */
    /* Source and destination address should be align with transfer width */
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pConfig->transferWidth & 0x7U)) - 1U) & pConfig->source.address)) );
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pConfig->transferWidth & 0x7U)) - 1U) & pConfig->destination.address)));
#endif /* INPUT_ARG_DETECT */
    /* Initial linked list item */
    /* #Violation: dma_hal_c_REF_6 */
    pAddr->linkedListItemSrcAddr.U = Dma_Hal_InternalAddrConvert(pConfig->source.address);
    pAddr->linkedListItemDestAddr.U = Dma_Hal_InternalAddrConvert(pConfig->destination.address);
    /* Read back the current channel configuration and write any configurations
     * that the user does not care about into the linked list item */
    /* #Violation: dma_hal_c_REF_17 */
    lliControl.U = pDma->CH[channelID].CONTROL.U;
    pAddr->linkedListItemCtrl.B.S = lliControl.B.S;
    pAddr->linkedListItemCtrl.B.D = lliControl.B.D;
    pAddr->linkedListItemCtrl.B.AM = lliControl.B.AM;
    pAddr->linkedListItemCtrl.B.BE = lliControl.B.BE;
    pAddr->linkedListItemCtrl.B.CE = lliControl.B.CE;
    pAddr->linkedListItemCtrl.B.DI = (uint32)pConfig->destination.increment;
    pAddr->linkedListItemCtrl.B.SI = (uint32)pConfig->source.increment;
    pAddr->linkedListItemCtrl.B.DWIDTH = (uint32)pConfig->transferWidth;
    pAddr->linkedListItemCtrl.B.SWIDTH = (uint32)pConfig->transferWidth;
    pAddr->linkedListItemCtrl.B.DBSIZE = (uint32)pConfig->destination.burstSize;
    pAddr->linkedListItemCtrl.B.SBSIZE = (uint32)pConfig->source.burstSize;
    pAddr->linkedListItemCtrl.B.TRANSIZE = pConfig->transferSize;
    pAddr->linkedListItemCtrl.B.I = pConfig->terminaCountInterEn;

    lliBufAddr = pConfig->linkedListItemAddress;

    /* Check whether the address of the linked list node is an internal access address within the CPUXXTCM
     * and check whether it is the last node */
    if(lliBufAddr != 0U)
    {
        lliBufAddr = Dma_Hal_InternalAddrConvert(lliBufAddr);
    }

    pAddr->linkedListItemLliReg.B.LLI = (lliBufAddr >> 2U);
}

/* #Violation: dma_hal_c_REF_5 */
/* #Violation: dma_hal_c_REF_10 */
boolean Dma_Hal_InitLinkedListItem(DMA_MODULE *const pDma, uint8 channelID, const Dma_LinkedListItem *const pLliAddr)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pLliAddr));
    /* Check address align */
    /* Source and destination address should be align with transfer width */
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pDma->CH[channelID].CONTROL.B.SWIDTH & 0x7U)) - 1U) & pLliAddr->linkedListItemSrcAddr.U)));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pDma->CH[channelID].CONTROL.B.DWIDTH & 0x7U)) - 1U) & pLliAddr->linkedListItemDestAddr.U)));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;

    pDma->CH[channelID].LLIREG.B.LLI = pLliAddr->linkedListItemLliReg.B.LLI;
    pDma->CH[channelID].CONTROL.U = pLliAddr->linkedListItemCtrl.U;
    pDma->CH[channelID].SRCADDR.U = pLliAddr->linkedListItemSrcAddr.U;
    pDma->CH[channelID].DESTADDR.U = pLliAddr->linkedListItemDestAddr.U;
    ret = Dma_Register_ReadBack_Check(ret, pLliAddr->linkedListItemLliReg.B.LLI, pDma->CH[channelID].LLIREG.B.LLI);
    ret = Dma_Register_ReadBack_Check(ret, pLliAddr->linkedListItemCtrl.U, pDma->CH[channelID].CONTROLINIT.U);
    ret = Dma_Register_ReadBack_Check(ret, pLliAddr->linkedListItemSrcAddr.U, pDma->CH[channelID].SRCADDR.U );
    ret = Dma_Register_ReadBack_Check(ret, pLliAddr->linkedListItemDestAddr.U, pDma->CH[channelID].DESTADDR.U);
    
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_InitLinkedListItemWithCRC(DMA_MODULE *const pDma, uint8 channelID, const Dma_LinkedListItem *const pLliAddr)
{
    /* #Violation: dma_hal_c_REF_4 */
    DMA_CH_CRCCONFIG tempValue;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pLliAddr));
    /* Check address align */
    /* Source and destination address should be align with transfer width */
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pDma->CH[channelID].CONTROL.B.SWIDTH & 0x7U)) - 1U) & pLliAddr->linkedListItemSrcAddr.U)));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (((1UL << ((uint32)pDma->CH[channelID].CONTROL.B.DWIDTH & 0x7U)) - 1U) & pLliAddr->linkedListItemDestAddr.U)));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    pDma->CH[channelID].LLIREG.B.LLI = pLliAddr->linkedListItemLliReg.B.LLI;
    pDma->CH[channelID].CONTROL.U = pLliAddr->linkedListItemCtrl.U;
    pDma->CH[channelID].SRCADDR.U = pLliAddr->linkedListItemSrcAddr.U;
    pDma->CH[channelID].DESTADDR.U = pLliAddr->linkedListItemDestAddr.U;

    tempValue.U = pDma->CH[channelID].CRCCONFIG.U;
    tempValue.B.LLICRCEN = 3U;
    tempValue.B.LLICRCMSK = 3U;
    /* Unlock safe endinit protect */
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    pDma->CH[channelID].CRCCONFIG.U = tempValue.U;
    /* Lock safe endinit protect */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Dma_Register_ReadBack_Check(ret, tempValue.U, pDma->CH[channelID].CRCCONFIG.U);

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_InitMatchPattern(DMA_MODULE *const pDma, uint8 channelID, const Dma_MatchPatternConfig *const pConfig)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;

    pDma->CH[channelID].PATCONFIG.B.SIZE = (uint32)pConfig->patternSize;
    pDma->CH[channelID].PATCONFIG.B.PATSTOP = pConfig->patternMatchedStop;
    pDma->CH[channelID].PAT.U = pConfig->patternData;
    pDma->CH[channelID].PATMSK.U = pConfig->patternDataMaskBit;
    ret = Dma_Register_ReadBack_Check(ret, (uint32)pConfig->patternSize, pDma->CH[channelID].PATCONFIG.B.SIZE);
    ret = Dma_Register_ReadBack_Check(ret, pConfig->patternMatchedStop, pDma->CH[channelID].PATCONFIG.B.PATSTOP);
    ret = Dma_Register_ReadBack_Check(ret, pConfig->patternData, pDma->CH[channelID].PAT.U);
    ret = Dma_Register_ReadBack_Check(ret, pConfig->patternDataMaskBit, pDma->CH[channelID].PATMSK.U);
    /* Enable match pattern interrupt */
    ret &= Dma_Std_SetMatchPatternInterrupt(pDma, channelID, 1U);
    /* Mask match pattern interrupt */
    ret &= Dma_Std_SetMatchPatternInterruptMask(pDma, channelID, 1U);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_EnableDaisyChain(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;

    pDma->CH[channelID].ADVCONFIG.B.DAISYEN = 1U;
    ret = Dma_Register_ReadBack_Check(ret, 1U, pDma->CH[channelID].ADVCONFIG.B.DAISYEN);
    ret &= Dma_Std_EnableChannel(pDma, channelID);

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_DisableDaisyChain(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;

    pDma->CH[channelID].ADVCONFIG.B.DAISYEN = 0U;
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->CH[channelID].ADVCONFIG.B.DAISYEN);
    Dma_Std_DisableChannel(pDma, channelID);

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_EnableContinuousMode(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;

    pDma->CH[channelID].ADVCONFIG.B.CMODEN = 1U;
    ret = Dma_Register_ReadBack_Check(ret, 1U, pDma->CH[channelID].ADVCONFIG.B.CMODEN);

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
void Dma_Hal_DisableContinuousMode(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    pDma->CH[channelID].ADVCONFIG.B.CMODEN = 0U;
}

/* #Violation: dma_hal_c_REF_5 */
void Dma_Hal_SoftwareSwitchDoubleBuffer(DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    Dma_Std_SwitchDoubleBuffer(pDma, channelID);
}

/* #Violation: dma_hal_c_REF_5 */
Dma_DoubleBufferFrozenStatus Dma_Hal_GetDoubleBufferFrozenStatus(const DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    Dma_DoubleBufferFrozenStatus status;
    Dma_DoubleBufferActiveStatus activeStatus;
    boolean buffer0Status;
    boolean buffer1Status;

    /* Get double buffer active and frozen status */
    activeStatus = Dma_Std_GetDoubleBufferActiveStatus(pDma, channelID);
    buffer0Status = Dma_Std_GetBuffer0FrozenStatus(pDma, channelID);
    buffer1Status = Dma_Std_GetBuffer1FrozenStatus(pDma, channelID);
    /* If buffer0 and buffer1 are frozen at the same time,
       determine which state is frozen first based on the active state */
    if((0U != buffer0Status) && (0U != buffer1Status))
    {
        /* If activeStatus is 1, Buffer1 is frozen first and should be processed first */
        if(0U != (uint32)activeStatus)
        {
            status = DMA_DOUBLEBUFFERFROZENSTATUS_BOTH_FROZEN_BUFFER1FIRST;
        }
        /* If activeStatus is 0, Buffer0 is frozen first and should be processed first */
        else
        {
            status = DMA_DOUBLEBUFFERFROZENSTATUS_BOTH_FROZEN_BUFFER0FIRST;
        }
    }
    /* No buffer frozen */
    else if((0U == buffer0Status) && (0U == buffer1Status))
    {
        status = DMA_DOUBLEBUFFERFROZENSTATUS_NO_FROZEN;
    }
    /* Only one buffer frozen */
    else
    {
        if(0U != buffer0Status)
        {
            status = DMA_DOUBLEBUFFERFROZENSTATUS_BUFFER0_FROZEN;
        }
        else
        {
            status = DMA_DOUBLEBUFFERFROZENSTATUS_BUFFER1_FROZEN;
        }
    }
    return status;
}

/* #Violation: dma_hal_c_REF_5 */
void Dma_Hal_ClearDoubleBufferFrozenStatus(DMA_MODULE *const pDma, uint8 channelID, Dma_DoubleBufferStatusSel sel)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    if(DMA_DOUBLEBUFFERSTATUSSELECT_BUFFER0 == sel)
    {
        Dma_Std_ClearBuffer0FrozenStatus(pDma, channelID);
    }
    else if(DMA_DOUBLEBUFFERSTATUSSELECT_BUFFER1 == sel)
    {
        Dma_Std_ClearBuffer1FrozenStatus(pDma, channelID);
    }
    else
    {
        Dma_Std_ClearBuffer0FrozenStatus(pDma, channelID);
        Dma_Std_ClearBuffer1FrozenStatus(pDma, channelID);
    }
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_InitDoubleBuffer(DMA_MODULE *const pDma, uint8 channelID, const Dma_DoubleBufferConfig *const pConfig)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* Check address align */
    /* Switch address should be align with transfer width */
    if(pConfig->sel == DMA_DBSOURCEORDESTINATION_SOURCE)
    {
        /* #Violation: dma_hal_c_REF_2 */
        Assert((boolean)(0U == (((1UL << ((uint32)pDma->CH[channelID].CONTROL.B.SWIDTH & 0x7U)) - 1U) & pConfig->switchAddr)));
    }
    else
    {
        /* #Violation: dma_hal_c_REF_2 */
        Assert((boolean)(0U == (((1UL << ((uint32)pDma->CH[channelID].CONTROL.B.DWIDTH & 0x7U)) - 1U) & pConfig->switchAddr)));
    }
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    /* #Violation: dma_hal_c_REF_4 */
    DMA_CH_ADVCONFIG tempValue;
   
    ret = TRUE;
    tempValue.U = pDma->CH[channelID].ADVCONFIG.U;
    tempValue.B.DBMODE = ((((uint32)pConfig->sel) << 1U) | ((uint32)pConfig->mode) | 4U);
    tempValue.B.CMODEN = 1U;
    
    pDma->CH[channelID].SWADDR.U = (uint32)pConfig->switchAddr;
    /* Enable continue mode */
    pDma->CH[channelID].ADVCONFIG.U = tempValue.U;

    ret = Dma_Register_ReadBack_Check(ret, (uint32)pConfig->switchAddr, pDma->CH[channelID].SWADDR.U);
    ret = Dma_Register_ReadBack_Check(ret, tempValue.U, pDma->CH[channelID].ADVCONFIG.U);

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_InitCircularBuffer(DMA_MODULE *const pDma, uint8 channelID, const Dma_CircularBufferConfig *const pConfig)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* Check circular buffer size */
    if((DMA_CBSOURCEORDESTINATION_DESTINATION == pConfig->sel) || (DMA_CBSOURCEORDESTINATION_BOTH == pConfig->sel))
    {
        /* The bit being looped in the address should be 0 */
        /* #Violation: dma_hal_c_REF_2 */
        Assert((boolean) (0U == (((1UL << ((uint32)pConfig->desSize & 0xFU)) - 1U) & pDma->CH[channelID].DESTADDR.U)));
    }
    if((DMA_CBSOURCEORDESTINATION_SOURCE == pConfig->sel) || (DMA_CBSOURCEORDESTINATION_BOTH == pConfig->sel))
    {
        /* The bit being looped in the address should be 0 */
        /* #Violation: dma_hal_c_REF_2 */
        Assert((boolean) (0U == (((1UL << ((uint32)pConfig->srcSize & 0xFU)) - 1U) & pDma->CH[channelID].SRCADDR.U )));
    }
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    /* #Violation: dma_hal_c_REF_4 */
    DMA_CH_ADVCONFIG tempValue;
 
    ret = TRUE;
    tempValue.U = pDma->CH[channelID].ADVCONFIG.U;
    tempValue.B.DCBEN = ((((uint32)pConfig->sel) & 0x02U) != 0U) ? 1U : 0U;
    tempValue.B.SCBEN = ((((uint32)pConfig->sel) & 0x01U) != 0U) ? 1U : 0U;
    tempValue.B.DCBSIZE = (uint32)pConfig->desSize;
    tempValue.B.SCBSIZE = (uint32)pConfig->srcSize;
    tempValue.B.DCBWIC = (uint32)pConfig->desRollbackHaltEn;
    pDma->CH[channelID].ADVCONFIG.U = tempValue.U;
 
    ret = Dma_Register_ReadBack_Check(ret, tempValue.U, pDma->CH[channelID].ADVCONFIG.U);
    /* Enable circular buffer interrupt */
    ret &= Dma_Std_SetSourceCircularBufferInterrupt(pDma, channelID, 1U);
    ret &= Dma_Std_SetDestinationCircularBufferBufferInterrupt(pDma, channelID, 1U);
    /* Mask circular buffer interrupt */
    ret &= Dma_Std_SetSourceCircularBufferInterruptMask(pDma, channelID, 1U);
    ret &= Dma_Std_SetDestinationCircularBufferInterruptMask(pDma, channelID, 1U);

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_EnableInterrupt(DMA_MODULE *const pDma, uint8 channelID, uint8 interrupt)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* Check the validity of the interruption */
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (interrupt & (~DMA_CHANNEL_INTERRUPT_MASK))));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_TC))
    {
        ret &= Dma_Std_SetTerminalCountInterruptMask(pDma, channelID, 0U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_BUSERROR))
    {
        ret &= Dma_Std_SetErrorInterruptMask(pDma, channelID, 0U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_SCB))
    {
        ret &= Dma_Std_SetSourceCircularBufferInterruptMask(pDma, channelID, 0U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_DCB))
    {
        ret &= Dma_Std_SetDestinationCircularBufferInterruptMask(pDma, channelID, 0U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_PAT))
    {
        ret &= Dma_Std_SetMatchPatternInterruptMask(pDma, channelID, 0U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_THR))
    {
        ret &= Dma_Std_SetTransferSizeThresholdInterruptMask(pDma, channelID, 0U);
    }

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_DisableInterrupt(DMA_MODULE *const pDma, uint8 channelID, uint8 interrupt)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
    /* Check the validity of the interruption */
    /* #Violation: dma_hal_c_REF_2 */
    Assert((boolean)(0U == (interrupt & (~DMA_CHANNEL_INTERRUPT_MASK))));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_TC))
    {
        ret &= Dma_Std_SetTerminalCountInterruptMask(pDma, channelID, 1U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_BUSERROR))
    {
        ret &= Dma_Std_SetErrorInterruptMask(pDma, channelID, 1U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_SCB))
    {
        ret &= Dma_Std_SetSourceCircularBufferInterruptMask(pDma, channelID, 1U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_DCB))
    {
        ret &= Dma_Std_SetDestinationCircularBufferInterruptMask(pDma, channelID, 1U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_PAT))
    {
        ret &= Dma_Std_SetMatchPatternInterruptMask(pDma, channelID, 1U);
    }

    if(0U != (interrupt & DMA_CHANNELINTERRUPT_THR))
    {
        ret &= Dma_Std_SetTransferSizeThresholdInterruptMask(pDma, channelID, 1U);
    }

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
uint8 Dma_Hal_GetInterruptStatus(const DMA_MODULE *const pDma, uint8 channelID, uint8 interrupt)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    return (uint8)(pDma->CH[channelID].INT.U & (uint32)interrupt);
}

/* #Violation: dma_hal_c_REF_5 */
uint8 Dma_Hal_GetStatus(const DMA_MODULE *const pDma, uint8 channelID, uint8 stat)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    return (uint8)(pDma->CH[channelID].RAWINT.U & (uint8)stat);
}

/* #Violation: dma_hal_c_REF_5 */
void Dma_Hal_ClearStatus(DMA_MODULE *const pDma, uint8 channelID, uint8 stat)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    pDma->CH[channelID].INTCLR.U = (uint32)stat;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_SetChannelAccessMode(DMA_MODULE *const pDma, uint8 channelID, Dma_AccessMode mode)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    /* #Violation: dma_hal_c_REF_4 */
    DMA_CH_CONTROL controlMode;
    boolean ret;
    ret = TRUE;

    controlMode.U = pDma->CH[channelID].CONTROLINIT.U;
    controlMode.B.AM = (uint32)mode;
    pDma->CH[channelID].CONTROL.U = controlMode.U;
    
    ret = Dma_Register_ReadBack_Check(ret, controlMode.U, pDma->CH[channelID].CONTROLINIT.U);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_InitTimeStamp(DMA_MODULE *const pDma, uint8 clkDiv)
{
    boolean ret;
    uint32 tempValue;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)(CHECK_DMA_BASE(pDma)));
#endif
    /* Unlock safe endinit protect */
    ret = TRUE;
    tempValue = ((uint32)clkDiv | (1UL << 8U));
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    pDma->ITIMERDIV.U = tempValue;
    pDma->SFCONFIG.B.TSTMPEN = 3U;
    /* Lock safe endinit protect */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Dma_Register_ReadBack_Check(ret, tempValue, pDma->ITIMERDIV.U);
    ret = Dma_Register_ReadBack_Check(ret, 3U, pDma->SFCONFIG.B.TSTMPEN);

    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_DisableTimeStamp(DMA_MODULE *const pDma)
{
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: dma_hal_c_REF_1 */   
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_BASE(pDma));
#endif
    ret = TRUE;
    /* Unlock safe endinit protect */
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    pDma->ITIMERDIV.B.CKG = 0U;
    pDma->SFCONFIG.B.TSTMPEN = 0U;
    /* Lock safe endinit protect */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->ITIMERDIV.B.CKG);
    ret = Dma_Register_ReadBack_Check(ret, 0U, pDma->SFCONFIG.B.TSTMPEN);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
uint32 Dma_Hal_GetCurrentTimeStamp(const DMA_MODULE *const pDma)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_BASE(pDma));
#endif
    return pDma->ITIMERVAL.U;
}

/* #Violation: dma_hal_c_REF_5 */
uint32 Dma_Hal_GetTransferTimeStamp(const DMA_MODULE *const pDma, uint8 channelID, Dma_TransferTimeStampSel sel)
{
    uint32 stampValue;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    if(DMA_TRANSFERTIMESTAMPSEL_START == sel)
    {
        stampValue = pDma->CH[channelID].STTSTMP.U;
    }
    else
    {
        stampValue = pDma->CH[channelID].EDTSTMP.U;
    }
    return stampValue;
}

/* #Violation: dma_hal_c_REF_5 */
Dma_TransferTimeStampStatus Dma_Hal_GetAndClearTransferTimeStampValidStatus(DMA_MODULE *const pDma, uint8 channelID,
                                                                            Dma_TransferTimeStampSel sel)
{
    Dma_TransferTimeStampStatus stat;
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;
    stat = (0U != (pDma->CH[channelID].TSTMPVLD.U & (uint32)sel)) ? DMA_TRANSFERTIMESTAMP_VALID : DMA_TRANSFERTIMESTAMP_INVALID;
    if(DMA_TRANSFERTIMESTAMP_VALID == stat)
    {
        /* Unlock safe endinit protect */
        DISABLE_ALL_INTERRUPTS();
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        pDma->CH[channelID].TSTMPCLR.U = (uint8)sel;
        /* Lock safe endinit protect */
        ret &= Safewdt_Hal_SetSafetyEndinit();
        ENABLE_ALL_INTERRUPTS();
    }
    if(FALSE == ret)
    {
        stat = DMA_TRANSFERTIMESTAMP_BOTH_VALID_SEPROTECT_ERROR;
    }
    return stat;
}

/* #Violation: dma_hal_c_REF_5 */
Dma_CrcErrorStatus Dma_Hal_GetAndClearCrcErrorStatus(DMA_MODULE *const pDma, uint8 channelID, Dma_CrcErrorSel sel)
{
    Dma_CrcErrorStatus stat;
    uint32 chID;
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    chID = channelID;
    ret = TRUE;

    if(DMA_CRCERRORSEL_DATA == sel)
    {
        if(32U > channelID)
        {
            stat = ((0U != (pDma->ERRSTS3.U & (1UL << chID))) ? DMA_CRCERRORSTATUS_CRC_ERROR : DMA_CRCERRORSTATUS_NOCRC_ERROR);
        }
        else
        {
            stat = ((0U != (pDma->ERRSTS4.U & (1UL << (chID - 32UL)))) ? DMA_CRCERRORSTATUS_CRC_ERROR : DMA_CRCERRORSTATUS_NOCRC_ERROR);
        }
        if(DMA_CRCERRORSTATUS_CRC_ERROR == stat)
        {
            /* Unlock safe endinit protect */
            DISABLE_ALL_INTERRUPTS();
            ret &= Safewdt_Hal_ClearSafetyEndinit();
            pDma->CH[channelID].ERRCLR.B.DCRC = 1U;
            /* Lock safe endinit protect */
            ret &= Safewdt_Hal_SetSafetyEndinit();
            ENABLE_ALL_INTERRUPTS();
        }
    }
    else
    {
        if(32U > channelID)
        {
            stat = ((0U != (pDma->ERRSTS5.U & (1UL << chID))) ? DMA_CRCERRORSTATUS_CRC_ERROR : DMA_CRCERRORSTATUS_NOCRC_ERROR);
        }
        else
        {
            stat = ((0U != (pDma->ERRSTS6.U & (1UL << (chID - 32UL)))) ? DMA_CRCERRORSTATUS_CRC_ERROR : DMA_CRCERRORSTATUS_NOCRC_ERROR);
        }
        if(DMA_CRCERRORSTATUS_CRC_ERROR == stat)
        {
            /* Unlock safe endinit protect */
            DISABLE_ALL_INTERRUPTS();
            ret &= Safewdt_Hal_ClearSafetyEndinit();
            pDma->CH[channelID].ERRCLR.B.LCRC = 1U;
            /* Lock safe endinit protect */
            ret &= Safewdt_Hal_SetSafetyEndinit();
            ENABLE_ALL_INTERRUPTS();
        }
    }

    if(FALSE == ret)
    {
        stat = DMA_CRCERRORSTATUS_BOTH_CRC_SEPROTECT_ERROR;
    }
    return stat;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_GetChannelEnableStatus(const DMA_MODULE *const pDma, uint8 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    boolean stat;
    uint32 chID;

    chID = channelID;
    /* Channel ID less than 32, get status from ENBLDCHNS0*/
    if(channelID < 32U)
    {
        stat = ((0U != (pDma->ENBLDCHNS0.U & (1UL << chID))) ? TRUE : FALSE);
    }
    /* Channel ID greater than or equal 32, get status from ENBLDCHNS1*/
    else
    {
        stat = ((0U != (pDma->ENBLDCHNS1.U & (1UL << (chID - 32UL)))) ? TRUE : FALSE);
    }

    return stat;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_SetBufferable(DMA_MODULE *const pDma, uint8 channelID, Dma_BufferableSel sel)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    /* #Violation: dma_hal_c_REF_4 */
    DMA_CH_CONTROL controlMode;
    boolean ret;
    ret = TRUE;

    controlMode.U = pDma->CH[channelID].CONTROLINIT.U;
    controlMode.B.BE = (uint32)sel;
    pDma->CH[channelID].CONTROL.U = controlMode.U;

    ret = Dma_Register_ReadBack_Check(ret, controlMode.U, pDma->CH[channelID].CONTROLINIT.U);
    return ret;
}

/* #Violation: dma_hal_c_REF_5 */
boolean Dma_Hal_SetCacheable(DMA_MODULE *const pDma, uint8 channelID, Dma_CacheableSel sel)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check DMA base address and channel number */
    /* #Violation: dma_hal_c_REF_1 */
    /* #Violation: dma_hal_c_REF_3 */
    Assert((boolean)CHECK_DMA_CH_ID(pDma, channelID));
#endif /* INPUT_ARG_DETECT */
    /* #Violation: dma_hal_c_REF_4 */
    DMA_CH_CONTROL controlMode;
    boolean ret;
    ret = TRUE;

    controlMode.U = pDma->CH[channelID].CONTROLINIT.U;
    controlMode.B.CE = (uint32)sel;
    pDma->CH[channelID].CONTROL.U = controlMode.U;

    ret = Dma_Register_ReadBack_Check(ret, controlMode.U, pDma->CH[channelID].CONTROLINIT.U);
    return ret;
}

/* #Violation: dma_hal_c_REF_14 */
#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dma_hal_c_REF_15 */
#include "Dma_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

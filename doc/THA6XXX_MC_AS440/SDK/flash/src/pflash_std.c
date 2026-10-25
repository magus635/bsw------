/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    pflash_std.c
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of Flash module.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#pflash_std_c_REF_1:INT36-C;
 *Justification: Cast a numeric value to a pointer type for accessing data at a specified memory address.
 *
 * #pflash_std_c_REF_2:MISRAC2012-Rule-1.2;
 * Justification: Inline assembly for CPU-specific operations.
 * 
 *#pflash_std_c_REF_3:MISRAC2012-Rule-11.4;
 * Justification: Converting integers to object pointers to reduce register access complexity.
 *
 * #pflash_std_c_REF_5:MISRAC2012-Rule-2.1;
 * Justification: The interface is called by the application layer.
 *
 *#pflash_std_c_REF_6:MISRAC2012-Dir-4.3;
 * Justification: Mixing inline assembly with C code reduces code complexity.
 *  
 * #pflash_std_c_REF_9:MISRAC2012-Rule-2.2;
 * Justification: Platform-based design with configurable macros.
 *
 *#pflash_std_c_REF_10:CWE-704;
 *Justification: Cast a numeric value to a pointer type for accessing data at a specified memory address.
 *
 * #pflash_std_c_REF_11:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #pflash_std_c_REF_12:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 * 
 * #pflash_std_c_REF_13:MISRAC2012-Rule-10.5;
 * Justification: Cortex-R52+ lacks bool type, minimum unit is uint8.
 * 
 * #pflash_std_c_REF_14:MISRAC2012-Dir-4.9;
 * Justification: Function like macros are used to reduce code complexity.
 * 
 * #pflash_std_c_REF_15:MISRAC2012-Dir-1.1;
 * Justification:Inline assembly for CPU-specific operations.
 * 
 * #pflash_std_c_REF_16:MISRAC2012-Dir-4.2;
 * Justification:Inline assembly for CPU-specific operations.
 * 
 */

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "tha6_cfg.h"
#include "pflash_std.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/*^PFLASH PROGRAM TIMEOUT^ Pflash program timeout value*/
/* #Violation: pflash_std_c_REF_11 */
#define DEFAULT_PROG_TIMEOUT 0x100U

/* #Violation: pflash_std_c_REF_14 */
#define PFLASH_IN_RANGE(addr, start, end) (((addr) >= (start)) && ((addr) <= (end)))
/**********************************************************************************************************************
 *                                            Private Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/* #Violation: pflash_std_c_REF_11 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pflash_std_c_REF_12 */
#include "Fls_MemMap.h"
/**********************************************************************************************************************
 * Function:             Flash_Std_GetPflash0InfoCtrl
 * Description:          Get the PFLASH0 INFO control object
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                swapVal: Swap control register value
 * Inout:                None
 * Output:               None
 * Return:               FLASH_CTR_MODULE*: PFlash controler pointer
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/11/10    01359     Create
 *********************************************************************************************************************/
static FLASH_CTR_MODULE *Flash_Std_GetPflash0InfoCtrl(uint32 swapVal);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetPflash1InfoCtrl
 * Description:          Get the PFLASH1 INFO control object
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                swapVal: Swap control register value
 * Inout:                None
 * Output:               None
 * Return:               FLASH_CTR_MODULE*: PFlash controler pointer
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/11/10    01359     Create
 *********************************************************************************************************************/
static FLASH_CTR_MODULE *Flash_Std_GetPflash1InfoCtrl( uint32 swapVal);

#if defined(THA6_THA6412)
/**********************************************************************************************************************
 * Function:             Flash_Std_GetPflash2InfoCtrl
 * Description:          Get the PFLASH2 INFO control object
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                swapVal: Swap control register value
 * Inout:                None
 * Output:               None
 * Return:               FLASH_CTR_MODULE*: PFlash controler pointer
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/11/10    01359     Create
 *********************************************************************************************************************/
static FLASH_CTR_MODULE *Flash_Std_GetPflash2InfoCtrl( uint32 swapVal);

/**********************************************************************************************************************
 * Function:             Flash_Std_GetPflash3InfoCtrl
 * Description:          Get the PFLASH3 INFO control object
 * Sync/Async:           Synchronous
 * Reentrancy:           Reentrant
 * Input:                swapVal: Swap control register value
 * Inout:                None
 * Output:               None
 * Return:               FLASH_CTR_MODULE*: PFlash controler pointer
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/11/10    01359     Create
 *********************************************************************************************************************/
static FLASH_CTR_MODULE *Flash_Std_GetPflash3InfoCtrl( uint32 swapVal);
#endif
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static FLASH_CTR_MODULE *Flash_Std_GetPflash0InfoCtrl(uint32 swapVal)
{
    FLASH_CTR_MODULE *ret = NULL_PTR;
#if defined(THA6_THA6104) || defined(THA6_THA6206) || defined(THA6_THA6206D)
    if ((swapVal == 0xAAU) || (swapVal == 0x0U))
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH0_CTR;
    }
    else if (swapVal == 0x55U)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH1_CTR;
    }
    else
    {
        /* do nothing*/
    }
#elif defined(THA6_THA6412)
    if ((swapVal == 0xAAU) || (swapVal == 0x0U))
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH0_CTR;
    }
    else if (swapVal == 0x55U)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH2_CTR;
    }
    else
    {
        /* do nothing*/
    }
#endif
    return ret;
}

static FLASH_CTR_MODULE *Flash_Std_GetPflash1InfoCtrl(uint32 swapVal)
{
    FLASH_CTR_MODULE *ret = NULL_PTR;
#if defined(THA6_THA6104) || defined(THA6_THA6206) || defined(THA6_THA6206D)
    if ((swapVal == 0xAAU) || (swapVal == 0x0U))
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH1_CTR;
    }
    else if (swapVal == 0x55U)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH0_CTR;
    }
    else
    {
        /* do nothing*/
    }
#elif defined(THA6_THA6412)
    if (swapVal == 0x0U)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH1_CTR;
    }
    if (swapVal == 0xAAU)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH2_CTR;
    }
    if (swapVal == 0x55U)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH0_CTR;
    }
#endif
    return ret;
}

#if defined(THA6_THA6412)
static FLASH_CTR_MODULE *Flash_Std_GetPflash2InfoCtrl(uint32 swapVal)
{
    FLASH_CTR_MODULE *ret = NULL_PTR;
    if (swapVal == 0x0U)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH2_CTR;
    }
    if (swapVal == 0xAAU)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH1_CTR;
    }
    if (swapVal == 0x55U)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH3_CTR;
    }
    return ret;
}

static FLASH_CTR_MODULE *Flash_Std_GetPflash3InfoCtrl(uint32 swapVal)
{
    FLASH_CTR_MODULE *ret = NULL_PTR;
    if ((swapVal == 0xAAU) || (swapVal == 0x0U))
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH3_CTR;
    }
    else if (swapVal == 0x55U)
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH1_CTR;
    }
    else
    {
        /* do nothing*/
    }
    return ret;
}
#endif
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/

Pflash_StdStatus Flash_Std_InitPflash(FLASH_COMMON_CTR_MODULE *const pCommonCtr, const Pflash_ClockCfg *const pCfg)
{
    boolean ret;
    ret = TRUE;
    Pflash_StdStatus bRetSts;
    uint32 regVal;

    if (NULL_PTR != pCfg)
    {

        /*Set FLASH_PFCON CLKDIV*/
        regVal = pCommonCtr->PFCON;
        regVal &= ~(uint32)(PFCON_CLKDIV_MASK);
        regVal |= ((uint32)pCfg->bCLKDIV << PFCON_CLKDIV_POS);

        /*Set PFCON RDT*/
        regVal &= ~(uint32)(PFCON_RDT_MASK);
        regVal |= pCfg->bRDT;

        /*Set PFCON STO0*/
        regVal &= ~(uint32)(PFCON_STO0_MASK);
        regVal |= ((uint32)pCfg->bSTO0 << (uint8)PFCON_STO0_POS);

        /*Set PFCON STO1*/
        regVal &= ~(uint32)(PFCON_STO1_MASK);
        regVal |= ((uint32)pCfg->bSTO1 << (uint8)PFCON_STO1_POS);

        pCommonCtr->PFCON = regVal;
        ret = PFlash_Register_ReadBack_Check(ret, regVal, pCommonCtr->PFCON);

        bRetSts = PFLASH_STDSTATUS_OK;
    }
    else
    {
        bRetSts = PFLASH_STDSTATUS_PARAM_ERR;
    }

    if(FALSE == ret)
    {
        bRetSts = PFLASH_STDSTATUS_PARAM_ERR;
    }
    return bRetSts;
}

boolean Flash_Std_CheckPFlashBusy(const FLASH_STS_MODULE *const pPFx_STS)
{
    boolean ret;
    uint32 stsVal;
    stsVal = pPFx_STS->STS;
    if ((PF_STS_ERASE_MASK == (stsVal & PF_STS_ERASE_MASK)) ||
        (PF_STS_PROG_MASK == (stsVal & PF_STS_PROG_MASK)) ||
        (PF_STS_BLANK_CHECK_MASK == (stsVal & PF_STS_BLANK_CHECK_MASK)))
    {
        ret = TRUE;
    }
    else
    {
        ret = FALSE;
    }
    return ret;
}

Pflash_OperationStatus Flash_Std_GetPFlashProgStatus(const FLASH_STS_MODULE *const pPFx_STS)
{
    Pflash_OperationStatus status;
    uint32 stsVal;
    stsVal = pPFx_STS->STS;

    if (PF_STS_PROGF_MASK == (stsVal & PF_STS_PROGF_MASK))
    {
        /*The result of program is completed*/
        status = PFLASH_OPERATIONSTATUS_COMPLETED;
    }
    else if (PF_STS_POVT_MASK == (stsVal & PF_STS_POVT_MASK))
    {
        status = PFLASH_OPERATIONSTATUS_TIMEOUT;
    }
    else if (PF_STS_PROG_MASK == (stsVal & PF_STS_PROG_MASK))
    {
        status = PFLASH_OPERATIONSTATUS_BUSY;
    }
    else
    {
        status = PFLASH_OPERATIONSTATUS_NOACTION;
    }
    return status;
}

Pflash_OperationStatus Flash_Std_GetPFlashEraseStatus(const FLASH_STS_MODULE *const pPFx_STS)
{
    Pflash_OperationStatus status;
    uint32 stsVal;
    stsVal = pPFx_STS->STS;
    if (PF_STS_ERSF_MASK == (stsVal & PF_STS_ERSF_MASK))
    {
        /*The result of erase is completed*/
        status = PFLASH_OPERATIONSTATUS_COMPLETED;
    }
    else if (PF_STS_ERASE_MASK == (stsVal & PF_STS_ERASE_MASK))
    {
        status = PFLASH_OPERATIONSTATUS_BUSY;
    }
    else
    {
        status = PFLASH_OPERATIONSTATUS_NOACTION;
    }
    return status;
}

Pflash_OperationStatus Flash_Std_GetPFlashBlankStatus(const FLASH_STS_MODULE *const pPFx_STS)
{
    Pflash_OperationStatus status;

    uint32 stsVal;
    stsVal = pPFx_STS->STS;

    if (PF_STS_BCF_MASK == (stsVal & PF_STS_BCF_MASK))
    {
        if (PF_STS_ECSTS_MASK == (stsVal & PF_STS_ECSTS_MASK))
        {
            /*The result of blank check is non-empty*/
            status = PFLASH_OPERATIONSTATUS_ERROR;
        }
        else
        {
            /*The result of blank check is empty*/
            status = PFLASH_OPERATIONSTATUS_COMPLETED;
        }
    }
    else if(PF_STS_BLANK_CHECK_MASK == (stsVal & PF_STS_BLANK_CHECK_MASK))
    {
        status = PFLASH_OPERATIONSTATUS_BUSY;
    }
    else
    {
        status = PFLASH_OPERATIONSTATUS_NOACTION;
    }
    return status;
}

void Flash_Std_ClearPFlashBlankStatus(FLASH_STS_MODULE *const pPFx_STS)
{
    pPFx_STS->STS = (uint32)(PF_STS_BCF_MASK | PF_STS_ECSTS_MASK);
}

void Flash_Std_ClearPFlashProgStatus(FLASH_STS_MODULE *const pPFx_STS)
{
    pPFx_STS->STS = (uint32)(PF_STS_PROGF_MASK);
}

void Flash_Std_ClearPFlashEraseStatus(FLASH_STS_MODULE *const pPFx_STS)
{
    pPFx_STS->STS = (uint32)(PF_STS_ERSF_MASK);
}

/* #Violation: pflash_std_c_REF_6 */
boolean Flash_Std_ErasePFlash(FLASH_CTR_MODULE *const pPFx_CTR, uint32 uAddress, uint8 bEraseType)
{
    boolean ret;
    ret = TRUE;
    /*need atomic operation*/
    pPFx_CTR->CTR3 = (uint32)(uAddress & PF_CTR3_EADDR_MASK);
    /* #Violation: pflash_std_c_REF_2 */
    /* #Violation: pflash_std_c_REF_15 */
    /* #Violation: pflash_std_c_REF_16 */
    DMB();
    pPFx_CTR->CTR4 = (uint32)(((uint32)bEraseType << 4U) | PF_CTR4_ESTART_MASK);
    ret = PFlash_Register_ReadBack_Check(ret, (uint32)(uAddress & PF_CTR3_EADDR_MASK), pPFx_CTR->CTR3);
    ret = PFlash_Register_ReadBack_Check(ret, (uint32)((uint32)bEraseType), (pPFx_CTR->CTR4 >> 4U));

    return ret;
}

/* #Violation: pflash_std_c_REF_6 */
boolean Flash_Std_ProgPFlash(FLASH_CTR_MODULE *const pPFx_CTR, uint32 uAddress, const uint32 *const pData, uint32 uDataLen)
{
    boolean ret;
    ret = TRUE;
    uint32 uMod;
    uint32 uLoop;
    uint32 uCount;
    uint32 progAddress;
    uint32 dataAdd;

    uCount = 0;
    if(FLASH_PFLASH_PWORD_SIZE <= uDataLen)
    {
        uMod = uDataLen / FLASH_PFLASH_PWORD_SIZE;
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
        uCount = uDataLen / 4U;
#endif
#if defined(THA6_THA6104)
        uCount = uDataLen / 8U;
#endif
        uMod--;
    }
    else
    {
        uMod = 0U;
    }

    progAddress = uAddress;
    /* #Violation: pflash_std_c_REF_3 */
    dataAdd = (uint32)pData;
    /*First write the data length and hardware execute prog_extra auto*/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
    pPFx_CTR->CTR7 = (uint32)(PF_CTR7_PEXTRA_MASK | uMod);
    ret = PFlash_Register_ReadBack_Check(ret, (uint32)(PF_CTR7_PEXTRA_MASK | uMod), pPFx_CTR->CTR7);
#endif
#if defined(THA6_THA6104)
    pPFx_CTR->CTR7 = (uint32)uMod;
    ret = PFlash_Register_ReadBack_Check(ret, (uint32)(uMod), pPFx_CTR->CTR7);
#endif

    /* #Violation: pflash_std_c_REF_2 */
    /* #Violation: pflash_std_c_REF_15 */
    /* #Violation: pflash_std_c_REF_16 */
    DMB();

    /*Secondly ,write the data*/
    if(FALSE != (dataAdd & 0x3U))
    {
        uCount = uDataLen;
        for(uLoop = 0; uLoop < uCount; uLoop++)
        {
            /* #Violation: pflash_std_c_REF_3 */
            /* #Violation: pflash_std_c_REF_3 */
            *(volatile uint8 *)(progAddress + uLoop) = *((volatile uint8 *)(dataAdd + uLoop));
        }
    }
    else
    {
        for (uLoop = 0; uLoop < uCount; uLoop++)
        {
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
            /* #Violation: pflash_std_c_REF_3 */
            /* #Violation: pflash_std_c_REF_3 */
            *(volatile uint32 *)(progAddress) = *((volatile uint32 *)(dataAdd + (uLoop * 4U)));
            progAddress += 4U;
#endif
#if defined(THA6_THA6104)
            /* #Violation: pflash_std_c_REF_3 */
            /* #Violation: pflash_std_c_REF_3 */
            *(volatile uint64 *)(progAddress) = *((volatile uint64 *)(dataAdd + (uLoop * 8U)));
            progAddress += 8U;
#endif
        }
    }

    return ret;
}

boolean Flash_Std_CheckPFlashBlank(FLASH_CTR_MODULE *const pPFx_CTR, uint32 uAddress, Pflash_BlankType eBlank)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    regVal = (uint32)(uAddress & PF_CTR5_ECADDR_MASK);
    /* #Violation: pflash_std_c_REF_9 */
    regVal &= ~(uint32)PF_CTR5_ECLEN_MASK;
    regVal |= ((uint32)eBlank) << PF_CTR5_ECLEN_POS;
    regVal |= PF_CTR5_ECEN_MASK;

    /* #Violation: pflash_std_c_REF_1 */
    pPFx_CTR->CTR5 = regVal;

    ret = PFlash_Register_ReadBack_Check(ret, (uint32)(regVal & ~(0x3U)), (pPFx_CTR->CTR5 & ~(0x3U)));

    return ret;
}
/* #Violation: pflash_std_c_REF_5 */
uint32 Flash_Std_GetAllPFlashStatus(const FLASH_STS_MODULE *const pPFx_STS)
{
    return pPFx_STS->STS;
}
/* #Violation: pflash_std_c_REF_5 */
void Flash_Std_ClearAllPFlashStatus(FLASH_STS_MODULE *const pPFx_STS)
{
    pPFx_STS->STS = PF_STS_ALL_MASK;
}

boolean Flash_Std_GetPFlashEccStatus(const FLASH_STS_MODULE *const pPFx_STS)
{
    /* #Violation: pflash_std_c_REF_13 */
    return (boolean)((pPFx_STS->SASTS0 & (uint32)(PF_SASTS0_UCRE_MASK)) == (uint32)(PF_SASTS0_UCRE_MASK));
}

void Flash_Std_ClearPFlashEccStatus(FLASH_STS_MODULE *const pPFx_STS)
{
    pPFx_STS->SASTS0 = (uint32)(PF_SASTS0_UCRE_MASK);
}

boolean Flash_Std_EnablePFlashInt(FLASH_MSK_MODULE *const pPFx_MSK , uint32 uFlashInt)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    regVal = pPFx_MSK->MSKINT;
    regVal &= ~(uint32)(uFlashInt);

    pPFx_MSK->MSKINT = regVal;
    ret = PFlash_Register_ReadBack_Check(ret, regVal, (uint32)pPFx_MSK->MSKINT);
    
    return ret;
}

boolean Flash_Std_DisablePFlashInt(FLASH_MSK_MODULE *const pPFx_MSK , uint32 uFlashInt)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    regVal = pPFx_MSK->MSKINT;
    regVal |= (uint32)(uFlashInt);

    pPFx_MSK->MSKINT = regVal;
    ret = PFlash_Register_ReadBack_Check(ret, regVal, (uint32)pPFx_MSK->MSKINT);
    
    return ret;
}

boolean Flash_Std_EnablePFlashEccBusErrorAlarm(FLASH_MSK_MODULE *const pPFx_MSK)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    regVal = pPFx_MSK->SAMSKBE0;
    regVal &= ~(uint32)(PF_SAMSKBE0_MUCRE_MASK);
    pPFx_MSK->SAMSKBE0 = regVal;

    ret = PFlash_Register_ReadBack_Check(ret, regVal, (uint32)pPFx_MSK->SAMSKBE0);
    
    return ret;
}

boolean Flash_Std_DisablePFlashEccBusErrorAlarm(FLASH_MSK_MODULE *const pPFx_MSK)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    regVal = pPFx_MSK->SAMSKBE0;
    regVal |= (uint32)(PF_SAMSKBE0_MUCRE_MASK);

    pPFx_MSK->SAMSKBE0 = regVal;
    ret = PFlash_Register_ReadBack_Check(ret, regVal, (uint32)pPFx_MSK->SAMSKBE0);
    
    return ret;
}
#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* #Violation: pflash_std_c_REF_5 */
boolean Flash_Std_ConfigPFlashBuf(FLASH_COMMON_BUFCFG_MODULE *const pBufcfg, uint32 regVal)
{
    boolean ret;
    ret = TRUE;

    pBufcfg->PF0BUFCFG = (uint32)(regVal);
    ret = PFlash_Register_ReadBack_Check(ret, regVal, pBufcfg->PF0BUFCFG);

    pBufcfg->PF1BUFCFG = (uint32)(regVal);
    ret = PFlash_Register_ReadBack_Check(ret, regVal, pBufcfg->PF1BUFCFG);

    return ret;
}
#endif

FLASH_CTR_MODULE *Flash_Std_GetPFlashCtr(uint32 uAddress)
{
    FLASH_CTR_MODULE *ret = NULL_PTR;

    /* Get SWAP configure */
    /* #Violation: pflash_std_c_REF_3 */
    const uint32 swapVal = (uint32)(FLASH_CLUSTER0_CTR->SWAPCON & 0xFFU);

    /* #Violation: pflash_std_c_REF_14 */
    if (PFLASH_IN_RANGE(uAddress, FLASH_DEVICE_PFLASH0_START_ADDR, FLASH_DEVICE_PFLASH0_END_ADDR))
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH0_CTR;
    }
    /* #Violation: pflash_std_c_REF_14 */
    if (PFLASH_IN_RANGE(uAddress, FLASH_DEVICE_PFLASH1_START_ADDR, FLASH_DEVICE_PFLASH1_END_ADDR))
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH1_CTR;
    }

#if defined(THA6_THA6412)
    /* #Violation: pflash_std_c_REF_14 */
    if (PFLASH_IN_RANGE(uAddress, FLASH_DEVICE_PFLASH2_START_ADDR, FLASH_DEVICE_PFLASH2_END_ADDR))
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH2_CTR;
    }
    /* #Violation: pflash_std_c_REF_14 */
    if (PFLASH_IN_RANGE(uAddress, FLASH_DEVICE_PFLASH3_START_ADDR, FLASH_DEVICE_PFLASH3_END_ADDR))
    {
        /* #Violation: pflash_std_c_REF_3 */
        ret = FLASH_PFLASH3_CTR;
    }
#endif

    if ((TRUE == CHECK_PFLASH_INFO_ADD) && (NULL_PTR == ret))
    {
        /* #Violation: pflash_std_c_REF_14 */
        if (PFLASH_IN_RANGE(uAddress, FLASH_DEVICE_PFLASH0_INFO_START_ADDR, FLASH_DEVICE_PFLASH0_INFO_END_ADDR))
        {
            ret = Flash_Std_GetPflash0InfoCtrl(swapVal);
        }
        /* #Violation: pflash_std_c_REF_14 */
        if (PFLASH_IN_RANGE(uAddress, FLASH_DEVICE_PFLASH1_INFO_START_ADDR, FLASH_DEVICE_PFLASH1_INFO_END_ADDR))
        {
            ret = Flash_Std_GetPflash1InfoCtrl(swapVal);
        }

#if defined(THA6_THA6412)
        /* #Violation: pflash_std_c_REF_14 */
        if (PFLASH_IN_RANGE(uAddress, FLASH_DEVICE_PFLASH2_INFO_START_ADDR, FLASH_DEVICE_PFLASH2_INFO_END_ADDR))
        {
            ret = Flash_Std_GetPflash2InfoCtrl(swapVal);
        }
        /* #Violation: pflash_std_c_REF_14 */
        if (PFLASH_IN_RANGE(uAddress, FLASH_DEVICE_PFLASH3_INFO_START_ADDR, FLASH_DEVICE_PFLASH3_INFO_END_ADDR))
        {
            ret = Flash_Std_GetPflash3InfoCtrl(swapVal);
        }
#endif
    }

    return ret;
}
/* #Violation: pflash_std_c_REF_11 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pflash_std_c_REF_12 */
#include "Fls_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

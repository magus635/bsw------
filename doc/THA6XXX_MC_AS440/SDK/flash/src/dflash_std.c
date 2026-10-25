/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dflash_std.c
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of Flash module.
 *********************************************************************************************************************/
/*
 *
 *#Violation Summary
 *
 *#dflash_std_c_REF_1:MISRAC2012-Rule-11.4;
 *Justification: Converting integers to object pointers to reduce register access complexity.
 *
 *#dflash_std_c_REF_2:MISRAC2012-Dir-4.3;
 * Justification: Mixing inline assembly with C code reduces code complexity.
 *
 * #dflash_std_c_REF_4:MISRAC2012-Rule-10.5;
 * Justification: Cortex-R52+ lacks bool type, minimum unit is uint8.
 *
 *#dflash_std_c_REF_5:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #dflash_std_c_REF_6:MISRAC2012-Rule-1.2;
 * Justification: Inline assembly for CPU-specific operations.
 *
 *#dflash_std_c_REF_8:MISRAC2012-Rule-11.4;
 * Justification: Casting a pointer to an integral type to obtain its address.
 * 
 * #dflash_std_c_REF_9:MISRAC2012-Rule-2.2;
 * Justification: Platform-based design with configurable macros.
 * 
 * #dflash_std_c_REF_10:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 *
 * #dflash_std_c_REF_11:MISRAC2012-Dir-1.1;
 * Justification:Inline assembly for CPU-specific operations.
 * 
 * #dflash_std_c_REF_12:MISRAC2012-Dir-4.2;
 * Justification:Inline assembly for CPU-specific operations.
 */
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "dflash_std.h"
#include "tha6_cfg.h"
#include "Platform_Types.h"
#include "flash_register.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/*^DFLASH MACRO^*/
/* #Violation: dflash_std_c_REF_5 */
#define FALSH_UNLOCK_MASTER_ID (0x3FU) /*Dflash unlock master id*/
/* #Violation: dflash_std_c_REF_5 */
#define DEFAULT_PROG_TIMEOUT (0x100U) /*Dflash program timeout*/
/* #Violation: dflash_std_c_REF_5 */
#define DFLASH_ERASE_SECTOR (0U) /*Dflash erase sector*/

/**********************************************************************************************************************
 *                                            Private Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/* #Violation: dflash_std_c_REF_5 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dflash_std_c_REF_10 */
#include "Fls_MemMap.h"
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
Dflash_StdStatus Flash_Std_InitDflash(const Dflash_ClockCfg *const pCfg)
{
    boolean ret;
    ret = TRUE;
    Dflash_StdStatus bRetSts;
    uint32 regVal;

    if (NULL_PTR != pCfg)
    {
        /*Set FLASH_DFCON CLKDIV*/
        /* #Violation: dflash_std_c_REF_1 */
        regVal = FLASH_CLUSTER0_CTR->DFCON;
        regVal &= ~(uint32)(DFCON_CLKDIV_MASK);
        regVal |= ((uint32)pCfg->bCLKDIV << DFCON_CLKDIV_POS);

        /*Set FLASH_DFCON RDT*/
        regVal &= ~(uint32)(DFCON_RDT_MASK);
        regVal |= pCfg->bRDT;

        /*Set FLASH_DFCON STO0*/
        regVal &= ~(uint32)(DFCON_STO0_MASK);
        regVal |= ((uint32)pCfg->bSTO0 << (uint8)DFCON_STO0_POS);

        /*Set FLASH_DFCON STO1*/
        regVal &= ~(uint32)(DFCON_STO1_MASK);
        regVal |= ((uint32)pCfg->bSTO1 << (uint8)DFCON_STO1_POS);

        /* #Violation: dflash_std_c_REF_1 */
        FLASH_CLUSTER0_CTR->DFCON = regVal;
        /* #Violation: dflash_std_c_REF_1 */
        ret = DFlash_Register_ReadBack_Check(ret, regVal, FLASH_CLUSTER0_CTR->DFCON);

        /* #Violation: dflash_std_c_REF_1 */
        regVal = FLASH_DFLASH_CTR->CTR1;
        regVal |= (uint32)DF_CTR1_BUFEN_MASK;
        /* #Violation: dflash_std_c_REF_1 */
        FLASH_DFLASH_CTR->CTR1 = regVal;
        /* #Violation: dflash_std_c_REF_1 */
        ret = DFlash_Register_ReadBack_Check(ret, regVal, FLASH_DFLASH_CTR->CTR1);
        /* #Violation: dflash_std_c_REF_1 */
        regVal = FLASH_DFLASH_CTR->CTR8;
        regVal &= ~(uint32)DF_CTR8_OVTE_MASK;
        /* #Violation: dflash_std_c_REF_1 */
        FLASH_DFLASH_CTR->CTR8 = regVal;
        /* #Violation: dflash_std_c_REF_1 */
        ret = DFlash_Register_ReadBack_Check(ret, regVal, FLASH_DFLASH_CTR->CTR8);

        bRetSts = DFLASH_STDSTATUS_OK;
    }
    else
    {
        ret = FALSE;
    }

    if(FALSE == ret)
    {
        bRetSts = DFLASH_STDSTATUS_PARAM_ERR;
    }
    return bRetSts;
}

boolean Flash_Std_CheckDFlashBusy(void)
{
    boolean ret;
    uint32 stsVal;
    /* #Violation: dflash_std_c_REF_1 */
    stsVal = FLASH_DFLASH_STS->STS;
    /* #Violation: dflash_std_c_REF_1 */
    if ((DF_STS_ERASE_MASK == (stsVal & DF_STS_ERASE_MASK)) ||
        /* #Violation: dflash_std_c_REF_1 */
        (DF_STS_PROG_MASK == (stsVal & DF_STS_PROG_MASK)) ||
        /* #Violation: dflash_std_c_REF_1 */
        (DF_STS_BLANK_CHECK_MASK == (stsVal & DF_STS_BLANK_CHECK_MASK)))
    {
        ret = TRUE;
    }
    else
    {
        ret = FALSE;
    }
    return ret;
}

Dflash_OperationStatus Flash_Std_GetDFlashProgStatus(void)
{
    Dflash_OperationStatus status;
    uint32 stsVal;
    /* #Violation: dflash_std_c_REF_1 */
    stsVal = FLASH_DFLASH_STS->STS;
    
    if (DF_STS_PROGF_MASK == (stsVal & DF_STS_PROGF_MASK))
    { 
        /*The result of program is completed*/
        status = DFLASH_OPERATIONSTATUS_COMPLETED;
    }   
    else if (DF_STS_POVT_MASK == (stsVal & DF_STS_POVT_MASK))
    {   
        status = DFLASH_OPERATIONSTATUS_TIMEOUT;
    }
    else if (DF_STS_PROG_MASK == (stsVal & DF_STS_PROG_MASK))
    {
        status = DFLASH_OPERATIONSTATUS_BUSY;
    }
    else
    {
        status = DFLASH_OPERATIONSTATUS_NOACTION;
    }
    return status;
}

Dflash_OperationStatus Flash_Std_GetDFlashEraseStatus(void)
{
    Dflash_OperationStatus status;
    uint32 stsVal;
    /* #Violation: dflash_std_c_REF_1 */
    stsVal = FLASH_DFLASH_STS->STS;
    if (DF_STS_ERSF_MASK == (stsVal & DF_STS_ERSF_MASK))
    { 
        /*The result of erase is completed*/
        status = DFLASH_OPERATIONSTATUS_COMPLETED;
    }
    else if(DF_STS_ERASE_MASK == (stsVal & DF_STS_ERASE_MASK))
    {
        status = DFLASH_OPERATIONSTATUS_BUSY;
    }
    else
    {
        status = DFLASH_OPERATIONSTATUS_NOACTION;
    }
    return status;
}

Dflash_OperationStatus Flash_Std_GetDFlashBlankStatus(void)
{
    Dflash_OperationStatus status;
    uint32 stsVal;
    /* #Violation: dflash_std_c_REF_1 */
    stsVal = FLASH_DFLASH_STS->STS;
    /* #Violation: dflash_std_c_REF_1 */
    if (DF_STS_BCF_MASK == (stsVal & DF_STS_BCF_MASK))
    { /* #Violation: dflash_std_c_REF_1 */
        if (DF_STS_ECSTS_MASK == (stsVal & DF_STS_ECSTS_MASK))
        {
            /*The result of blank check is non-empty*/
            status = DFLASH_OPERATIONSTATUS_ERROR;
        }
        else
        {
            /*The result of blank check is empty*/
            status = DFLASH_OPERATIONSTATUS_COMPLETED;
        }
    }
    else if(DF_STS_BLANK_CHECK_MASK == (stsVal & DF_STS_BLANK_CHECK_MASK))
    {
        status = DFLASH_OPERATIONSTATUS_BUSY;
    }
    else
    {
        status = DFLASH_OPERATIONSTATUS_NOACTION;
    }
    return status;
}

void Flash_Std_ClearDFlashProgStatus(void)
{
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_STS->STS = (uint32)(DF_STS_PROGF_MASK);
}

void Flash_Std_ClearDFlashEraseStatus(void)
{
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_STS->STS = (uint32)(DF_STS_ERSF_MASK);
}

void Flash_Std_ClearDFlashBlankStatus(void)
{
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_STS->STS = (uint32)(DF_STS_BCF_MASK | DF_STS_ECSTS_MASK);
}

/* #Violation: dflash_std_c_REF_2 */
boolean Flash_Std_EraseDFlash(uint32 uAddress)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_CTR->CTR3 = (uint32)(uAddress & DF_CTR3_EADDR_MASK);
    /* #Violation: dflash_std_c_REF_1 */
    ret = DFlash_Register_ReadBack_Check(ret, (uint32)(uAddress & DF_CTR3_EADDR_MASK), (uint32)FLASH_DFLASH_CTR->CTR3);
    /* #Violation: dflash_std_c_REF_6 */
    /* #Violation: dflash_std_c_REF_11 */
    /* #Violation: dflash_std_c_REF_12 */
    DMB();
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_CTR->CTR4 = (uint32)((DFLASH_ERASE_SECTOR << 4U) | DF_CTR4_ESTART_MASK);
    /* #Violation: dflash_std_c_REF_1 */
    ret = DFlash_Register_ReadBack_Check(ret, (uint32)(DFLASH_ERASE_SECTOR), (uint32)(FLASH_DFLASH_CTR->CTR4) >> 4U);
    return ret;
}

/* #Violation: dflash_std_c_REF_2 */
boolean Flash_Std_ProgDFlash(uint32 uAddress, const uint8 *const pData, uint32 uDataLen)
{
    boolean ret;
    ret = TRUE;
    uint32 uMod;
    uint32 uLoop;
    uint32 uCount;
    uint32 progAddress;
    uint32 dataAdd;

    if(FLASH_DFLASH_PWORD_SIZE <= uDataLen)
    {
        uMod = uDataLen / FLASH_DFLASH_PWORD_SIZE;
        uMod--;
    }
    else
    {
        uMod = 0U;
    }

    progAddress = uAddress;
    /* #Violation: dflash_std_c_REF_8 */
    dataAdd = (uint32)pData;
    /*First write the data length and hardware execute prog_extra auto*/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_CTR->CTR7 = (uint32)(DF_CTR7_PEXTRA_MASK | uMod);
    /* #Violation: dflash_std_c_REF_1 */
    ret = DFlash_Register_ReadBack_Check(ret, (uint32)(DF_CTR7_PEXTRA_MASK | uMod), (uint32)FLASH_DFLASH_CTR->CTR7);
#endif
#if defined(THA6_THA6104)
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_CTR->CTR7 = (uint32)uMod;
    /* #Violation: dflash_std_c_REF_1 */
    ret = DFlash_Register_ReadBack_Check(ret, (uint32)(uMod), (uint32)FLASH_DFLASH_CTR->CTR7);
#endif

    /* #Violation: dflash_std_c_REF_6 */
    /* #Violation: dflash_std_c_REF_11 */
    /* #Violation: dflash_std_c_REF_12 */
    DMB();

    if (FALSE != (dataAdd & 0x3U))
    {
        uCount = uDataLen;
        /*Secondly ,write the data*/
        for (uLoop = 0; uLoop < uCount; uLoop++)
        {
            /* #Violation: dflash_std_c_REF_1 */
            /* #Violation: dflash_std_c_REF_1 */
            *(volatile uint8 *)(progAddress) = *((volatile uint8 *)(dataAdd + uLoop));
            progAddress += (uint32)1U;
        }
    }
    else
    {
        uCount = uDataLen / 4U;
        /*Secondly ,write the data*/
        for (uLoop = 0; uLoop < uCount; uLoop++)
        {
            /* #Violation: dflash_std_c_REF_1 */
            /* #Violation: dflash_std_c_REF_1 */
            *(volatile uint32 *)(progAddress) = *((volatile uint32 *)(dataAdd + (uLoop * 4U)));
            progAddress += (uint32)4U;
        }
    }
    return ret;
}

boolean Flash_Std_CheckDFlashBlank(uint32 uAddress, Blank_Type eBlank)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    regVal = (uint32)(uAddress & DF_CTR5_ECADDR_MASK);
    /* #Violation: dflash_std_c_REF_9 */
    regVal &= ~(uint32)DF_CTR5_ECLEN_MASK;
    regVal |= ((uint32)eBlank << FLASH_DFLASH_CTR5_ECLEN_POS);
    regVal |= DF_CTR5_ECEN_MASK;

    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_CTR->CTR5 = regVal;
    /* #Violation: dflash_std_c_REF_1 */
    ret = DFlash_Register_ReadBack_Check(ret, (uint32)(regVal & ~(0x3U)), (uint32)(FLASH_DFLASH_CTR->CTR5& ~(0x3U)));

    return ret;
}

boolean Flash_Std_EnableDFlashInt(uint32 uFlashInt)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    /* #Violation: dflash_std_c_REF_1 */
    regVal = FLASH_DFLASH_MSK->MSKINT;
    regVal &= ~(uint32)(uFlashInt);
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_MSK->MSKINT = regVal;
    /* #Violation: dflash_std_c_REF_1 */
    ret = DFlash_Register_ReadBack_Check(ret, regVal, (uint32)FLASH_DFLASH_MSK->MSKINT);
    return ret;
}
boolean Flash_Std_DisableDFlashInt(uint32 uFlashInt)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    /* #Violation: dflash_std_c_REF_1 */
    regVal = FLASH_DFLASH_MSK->MSKINT;
    regVal |= (uint32)(uFlashInt); 
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_MSK->MSKINT = regVal;
    /* #Violation: dflash_std_c_REF_1 */
    ret = DFlash_Register_ReadBack_Check(ret, regVal, (uint32)FLASH_DFLASH_MSK->MSKINT);
    return ret;
}

boolean Flash_Std_EnableDFlashEccBusErrorAlarm(void)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    /* #Violation: dflash_std_c_REF_1 */
    regVal = FLASH_DFLASH_MSK->SAMSKBE0;
    regVal &= ~(uint32)(SAMSKBE0_MUCRE_MASK);
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_MSK->SAMSKBE0 = regVal;
    /* #Violation: dflash_std_c_REF_1 */
    ret = DFlash_Register_ReadBack_Check(ret, regVal, (uint32)FLASH_DFLASH_MSK->SAMSKBE0);
    return ret;
}
boolean Flash_Std_DisableDFlashEccBusErrorAlarm(void)
{
    boolean ret;
    ret = TRUE;
    uint32 regVal;

    /* #Violation: dflash_std_c_REF_1 */
    regVal = FLASH_DFLASH_MSK->SAMSKBE0;
    regVal |= (uint32)(SAMSKBE0_MUCRE_MASK);
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_MSK->SAMSKBE0 = regVal;
    /* #Violation: dflash_std_c_REF_6 */
    /* #Violation: dflash_std_c_REF_1 */
    ret = DFlash_Register_ReadBack_Check(ret, regVal, (uint32)FLASH_DFLASH_MSK->SAMSKBE0);
    return ret;
}

boolean Flash_Std_GetDFlashEccStatus(void)
{
    /* #Violation: dflash_std_c_REF_1 */
    /* #Violation: dflash_std_c_REF_4 */
    return (boolean)((FLASH_DFLASH_STS->SASTS0 & (uint32)(DF0_SASTS0_UCRE_MASK)) == (uint32)(DF0_SASTS0_UCRE_MASK));
}

void Flash_Std_ClearDFlashEccStatus(void)
{
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_STS->SASTS0 = (uint32)(DF0_SASTS0_UCRE_MASK);
}

uint32 Flash_Std_GetAllDFlashStatus(void)
{
    /* #Violation: dflash_std_c_REF_1 */
    return FLASH_DFLASH_STS->STS;
}
void Flash_Std_ClearAllDFlashStatus(void)
{
    /* #Violation: dflash_std_c_REF_1 */
    FLASH_DFLASH_STS->STS = DF_STS_ALL_MASK;
}
/* #Violation: dflash_std_c_REF_5 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dflash_std_c_REF_10 */
#include "Fls_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    flash_ssuhal.c
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
 *
 *#Violation Summary
 *
 * #flashssu_hal_c_REF_1:MISRAC2012-Rule-10.5;
 * Justification: Cortex-R52+ lacks bool type, minimum unit is uint8.
 *
 *#flashssu_hal_c_REF_2:MISRAC2012-Rule-11.4;
 * Justification: Converting integers to object pointers to reduce register access complexity.
 *
 * #flashssu_hal_c_REF_3:MISRAC2012-Dir-4.9;
 * Justification: Function like macros are used to reduce code complexity.
 *
 * #flashssu_hal_c_REF_4:MISRAC2012-Rule-2.1;
 * Justification: The interface is called by the application layer.
 * 
 * #flashssu_hal_c_REF_5:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #flashssu_hal_c_REF_6:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 */

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "tha6_cfg.h"
#include "safewdt_hal.h"
#include "flashssu_hal.h"

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/*^FLASH_SSU_STATUS^* Flash ssu unlock status*/
#define FLASH_SSU_DF_STATUS (0x1U) /*Dflash status*/
#define FLASH_SSU_PF_STATUS (0x4U) /*Pflash status*/
#define FLASH_SSU_NVRBS_STATUS (0x10U) /*Dflash status*/
#define FLASH_SSU_NVRNF_STATUS (0x40U) /*Dflash status*/
#define FLASH_SSU_PWD_WIDTH (8U)   /*PWD register width*/

/* #Violation: flashssu_hal_c_REF_5 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: flashssu_hal_c_REF_6 */
#include "Fls_MemMap.h"

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:             Flash_Hal_GetPrtSts
 * Description:          Check the unlock status register
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uAddress: The address of Dflash
 *                       bSts: The bit value to be check
 * Inout:                None
 * Output:               None
 * Return:               boolean: True or False
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
static boolean Flash_Hal_GetPrtSts(const FLASH_COMMON_STS_MODULE * const pSts, uint32 bSts);

/**********************************************************************************************************************
 * Function:             Flash_Hal_ClearPrtSts
 * Description:          Clear the unlock status register.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pSts: The pointer to the status register
 *                       bSts: The bit value to be clear
 * Inout:                None
 * Output:               None
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
static void Flash_Hal_ClearPrtSts(FLASH_COMMON_STS_MODULE * const pSts, uint32 bSts);

/**********************************************************************************************************************
 * Function:             Flash_Hal_StreamToUint32
 * Description:          uint8 to uint32.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                pPIN: The pointer to the data
 *                       Index: The offset of data
 * Inout:                None
 * Output:               None
 * Return:               uint32: data
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2025/03/04    01361     Create
 *********************************************************************************************************************/
static uint32 Flash_Hal_StreamToUint32(const uint8 * const pPIN, uint8 Index);

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static boolean Flash_Hal_GetPrtSts(const FLASH_COMMON_STS_MODULE *const pSts, uint32 bSts)
{
    /* #Violation: flashssu_hal_c_REF_1 */
    return (boolean)((uint32)0U == (uint32)(pSts->PRTSTS & bSts));
}

static void Flash_Hal_ClearPrtSts(FLASH_COMMON_STS_MODULE *const pSts, uint32 bSts)
{
    pSts->PRTSTS = bSts;
}

static uint32 Flash_Hal_StreamToUint32(const uint8 *const pPIN, uint8 Index)
{
    return ((uint32)pPIN[Index]) | ((uint32)pPIN[Index + 1U] << 8U) | ((uint32)pPIN[Index + 2U] << 16U) |
            ((uint32)pPIN[Index + 3U] << 24U);
}

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: flashssu_hal_c_REF_4 */
Flash_SSUStatus Flash_Hal_CheckDFlashSSUPwd(const uint8 *const pPIN)
{
    uint32 uPwd;
    uint8 iLoop;
    Flash_SSUStatus bRetStatus;
    boolean bCheckStatus;

    bRetStatus = FLASH_SSUSTATUS_FAILED;

    if (NULL_PTR != pPIN)
    {

        for (iLoop = 0U; iLoop < FLASH_SSU_PWD_WIDTH; iLoop++)
        {
            uPwd = Flash_Hal_StreamToUint32(pPIN, (uint8)(iLoop * 4U));
            /* #Violation: flashssu_hal_c_REF_2 */
            FLASH_CLUSTER0_PININPUT->DFPIN[iLoop] = uPwd;
        }
        /* #Violation: flashssu_hal_c_REF_2 */
        bCheckStatus = Flash_Hal_GetPrtSts(FLASH_CLUSTER0_STS, FLASH_SSU_DF_STATUS);
        /* #Violation: flashssu_hal_c_REF_2 */
        Flash_Hal_ClearPrtSts(FLASH_CLUSTER0_STS, FLASH_SSU_DF_STATUS);
        if (TRUE == bCheckStatus)
        {
            bRetStatus = FLASH_SSUSTATUS_OK;
        }
    }
    else
    {
        bRetStatus = FLASH_SSUSTATUS_PARAM_ERR;
    }

    return bRetStatus;
}

/* #Violation: flashssu_hal_c_REF_4 */
boolean Flash_Hal_ConfigDFlashSSU(uint8 bPermType, Flash_SSURdPerm RdVal, Flash_SSUWrPerm WrVal)
{
    boolean ret;
    uint8 typeTmp;
    ret = TRUE;
    typeTmp = (bPermType & (DF_SSU_WR_PERM | DF_SSU_RD_PERM));

    switch (typeTmp)
    {
    case 1U:
        DISABLE_ALL_INTERRUPTS();
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        /* #Violation: flashssu_hal_c_REF_2 */
        FLASH_DFLASH_SSU->Wr[0] = (uint32)WrVal;
        ret &= Safewdt_Hal_SetSafetyEndinit();
        ENABLE_ALL_INTERRUPTS();
        break;

    case 2U:
        DISABLE_ALL_INTERRUPTS();
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        /* #Violation: flashssu_hal_c_REF_2 */
        FLASH_DFLASH_SSU->Rd = (uint32)RdVal;
        ret &= Safewdt_Hal_SetSafetyEndinit();
        ENABLE_ALL_INTERRUPTS();
        break;

    case 3U:
        DISABLE_ALL_INTERRUPTS();
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        /* #Violation: flashssu_hal_c_REF_2 */
        FLASH_DFLASH_SSU->Wr[0] = (uint32)WrVal;
        /* #Violation: flashssu_hal_c_REF_2 */
        FLASH_DFLASH_SSU->Rd = (uint32)RdVal;
        ret &= Safewdt_Hal_SetSafetyEndinit();
        ENABLE_ALL_INTERRUPTS();
        break;

    default:
        ret = FALSE;
        break;
    }

    return ret;
}

/* #Violation: flashssu_hal_c_REF_4 */
Flash_SSUStatus Flash_Hal_CheckPFlashSSUPwd(FLASH_PININPUT_MODULE *const pPFx_PININPUT, const uint8 *const pPIN)
{
#if (INPUT_ARG_DETECT == STD_ON)
/* #Violation: flashssu_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPFx_PININPUT));
#endif /* INPUT_ARG_DETECT */
    
    uint32 uPwd;
    uint8 iLoop;
    Flash_SSUStatus bRetStatus;
    boolean bCheckStatus;
    FLASH_COMMON_STS_MODULE *pSts;
    const uint8 *const pPINAdd = pPIN;

    /* #Violation: flashssu_hal_c_REF_2 */
    /* #Violation: flashssu_hal_c_REF_3 */
    pSts = FLASH_GET_COMMON_STS_FROM_PININPUT(pPFx_PININPUT);

    bRetStatus = FLASH_SSUSTATUS_FAILED;

    if (NULL_PTR != pPINAdd)
    {
        for (iLoop = 0U; iLoop < FLASH_SSU_PWD_WIDTH; iLoop++)
        {
            uPwd = Flash_Hal_StreamToUint32(pPINAdd, (iLoop * 4U));
            /* #Violation: flashssu_hal_c_REF_2 */
            pPFx_PININPUT->PFPIN[iLoop] = uPwd;
        }
        bCheckStatus = Flash_Hal_GetPrtSts(pSts, FLASH_SSU_PF_STATUS);
        Flash_Hal_ClearPrtSts(pSts, FLASH_SSU_PF_STATUS);
        if (TRUE == bCheckStatus)
        {
            bRetStatus = FLASH_SSUSTATUS_OK;
        }
    }
    else
    {
        bRetStatus = FLASH_SSUSTATUS_PARAM_ERR;
    }
    return bRetStatus;
}

/* #Violation: flashssu_hal_c_REF_4 */
boolean Flash_Hal_ConfigPFlashSSU(FLASH_SSU_MODULE *const pPFx_SSU, Flash_SSURdPerm RdVal, uint32 WrVal1, uint32 WrVal2)
{
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: flashssu_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pPFx_SSU));
#endif /* INPUT_ARG_DETECT */
    
    boolean ret;
    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    pPFx_SSU->Rd = (uint32)RdVal;
    pPFx_SSU->Wr[0] = (uint32)WrVal1;
    pPFx_SSU->Wr[1] = (uint32)WrVal2;
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    return ret;
}

/* #Violation: flashssu_hal_c_REF_4 */
Flash_SSUStatus Flash_Hal_CheckNVRBS_SSUPwd(const uint8 *const pPIN)
{
    uint32 uPwd;
    uint8 iLoop;
    Flash_SSUStatus bRetStatus;
    boolean bCheckStatus;

    bRetStatus = FLASH_SSUSTATUS_FAILED;

    if (NULL_PTR != pPIN)
    {

        for (iLoop = 0U; iLoop < FLASH_SSU_PWD_WIDTH; iLoop++)
        {
            uPwd = Flash_Hal_StreamToUint32(pPIN, (uint8)(iLoop * 4U));
            /* #Violation: flashssu_hal_c_REF_2 */
            FLASH_CLUSTER0_PININPUT->NVRBSPIN[iLoop] = uPwd;
        }
        /* #Violation: flashssu_hal_c_REF_2 */
        bCheckStatus = Flash_Hal_GetPrtSts(FLASH_CLUSTER0_STS, FLASH_SSU_NVRBS_STATUS);
        /* #Violation: flashssu_hal_c_REF_2 */
        Flash_Hal_ClearPrtSts(FLASH_CLUSTER0_STS, FLASH_SSU_NVRBS_STATUS);
        if (TRUE == bCheckStatus)
        {
            bRetStatus = FLASH_SSUSTATUS_OK;
        }
    }
    else
    {
        bRetStatus = FLASH_SSUSTATUS_PARAM_ERR;
    }

    return bRetStatus;
}

/* #Violation: flashssu_hal_c_REF_4 */
Flash_SSUStatus Flash_Hal_CheckNVRNF_SSUPwd(const uint8 *const pPIN)
{
    uint32 uPwd;
    uint8 iLoop;
    Flash_SSUStatus bRetStatus;
    boolean bCheckStatus;

    bRetStatus = FLASH_SSUSTATUS_FAILED;

    if (NULL_PTR != pPIN)
    {

        for (iLoop = 0U; iLoop < FLASH_SSU_PWD_WIDTH; iLoop++)
        {
            uPwd = Flash_Hal_StreamToUint32(pPIN, (uint8)(iLoop * 4U));
            /* #Violation: flashssu_hal_c_REF_2 */
            FLASH_CLUSTER0_PININPUT->NVRCFGPIN[iLoop] = uPwd;
        }
        /* #Violation: flashssu_hal_c_REF_2 */
        bCheckStatus = Flash_Hal_GetPrtSts(FLASH_CLUSTER0_STS, FLASH_SSU_NVRNF_STATUS);
        /* #Violation: flashssu_hal_c_REF_2 */
        Flash_Hal_ClearPrtSts(FLASH_CLUSTER0_STS, FLASH_SSU_NVRNF_STATUS);
        if (TRUE == bCheckStatus)
        {
            bRetStatus = FLASH_SSUSTATUS_OK;
        }
    }
    else
    {
        bRetStatus = FLASH_SSUSTATUS_PARAM_ERR;
    }

    return bRetStatus;
}

/* #Violation: flashssu_hal_c_REF_4 */
boolean Flash_Hal_ConfigCluster0NVRSSU(uint32 writeMPU, uint32 readMPU)
{
    boolean ret;
    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    
    /* #Violation: flashssu_hal_c_REF_2 */
    FLASH_CLUSTER0_NVRMPU->NVREWMPU = writeMPU;
    /* #Violation: flashssu_hal_c_REF_2 */
    FLASH_CLUSTER0_NVRMPU->NVRRMPU = readMPU;
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();

    return ret;
}


/* #Violation: flashssu_hal_c_REF_5 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: flashssu_hal_c_REF_6 */
#include "Fls_MemMap.h"


/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

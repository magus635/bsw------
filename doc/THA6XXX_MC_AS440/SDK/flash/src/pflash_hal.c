/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    pflash_hal.c
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of Flash module.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#pflash_hal_c_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 *
 * #pflash_hal_c_REF_2:MISRAC2012-Rule-10.5;
 * Justification: Cortex-R52+ lacks bool type, minimum unit is uint8.
 *
 *#pflash_hal_c_REF_3:MISRAC2012-Rule-11.4;
 * Justification: Converting integers to object pointers to reduce register access complexity.
 *
 * #pflash_hal_c_REF_4:MISRAC2012-Dir-4.9;
 * Justification: Function like macros are used to reduce code complexity.
 *
 * #pflash_hal_c_REF_5:MISRAC2012-Rule-2.1;
 * Justification: The interface is called by the application layer.
 *
 * #pflash_hal_c_REF_6:MISRAC2012-Dir-4.1;
 * Justification: The Number of loops is set by different configuration.
 * 
 * #pflash_hal_c_REF_7:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 * 
 * #pflash_hal_c_REF_8:MISRAC2012-Rule-8.7; 
 * Justification:The interface is called by the application layer.
 *
 */

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "pflash_hal.h"
#include "safewdt_hal.h"
#include "stm_hal.h"
#include "rcc_hal.h"
#include "tha6_cfg.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/*^PFLASH MACRO^*/
#define PFLASH_BLANK_CHECK_TIMEOUT (0x100000U) /*pflash blank check timeout value*/
#define PFLASH_ERASE_TIMEOUT (0x7A6000U)       /*pflash erase timeout value*/
#define PFLASH_PROG_TIMEOUT (0x100000U)        /*pflash program timeout value*/

#define FLASH_CLOCK_FREQUENCY_MIN (10000000U) /*pflash clock min frequency 10mhz*/
/* #Violation: pflash_hal_c_REF_1 */
#define FLASH_CLOCK_FREQUENCY_MAX (100000000U)    /*pflash clock max frequency 100mhz*/
#if defined(THA6_THA6206) || defined(THA6_THA6412)  || defined(THA6_THA6206D)
#define FLASH_CLOCK_FREQUENCY_DESIRE (100000000U) /*pflash clock desired frequency 100mhz*/
#endif

#if defined(THA6_THA6104)
#define FLASH_CLOCK_FREQUENCY_DESIRE (75000000U) /*pflash clock desired frequency 75mhz*/
#endif

#define FLASH_CLOCK_FREQUENCY_CYCLE (100000U) /* ns / 10000 */

/* #Violation: pflash_hal_c_REF_1 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pflash_hal_c_REF_7 */
#include "Fls_MemMap.h"
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function:             Flash_Hal_CalPFlashTiming
 * Description:          Calculate the timing of Pflash operations
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:                uint32|uClockFreq:The CPU clock frequency
 * Inout:                None
 * Output:               Pflash_ClockCfg *|pCfg:The pointer to the structure for configuring Pflash timing
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
static void Flash_Hal_CalPFlashTiming(uint32 uClockFreq,Pflash_ClockCfg * const pCfg);

/**********************************************************************************************************************
 * Function:             Flash_Hal_PFlashStreamToUint32
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
static uint32 Flash_Hal_PFlashStreamToUint32(const uint8 *const pPIN, uint8 Index);

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/

static void Flash_Hal_CalPFlashTiming(uint32 uClockFreq, Pflash_ClockCfg *const pCfg)
{
    float32 uRDT;
    uint32 uTFreq;
    uint32 uDivPos;

    uDivPos = 0;
#if defined(THA6_THA6104)
    /* Modify Qac question: Using the value of an uninitialized variable */
    pCfg->bSTO1 = (uint8)0U;
#endif
    /*Calculate clock divider*/
    if (uClockFreq > FLASH_CLOCK_FREQUENCY_DESIRE)
    {
        uTFreq = uClockFreq;
        /*find the suitable clock division*/
        while ((uDivPos < (uint32)PFLASH_CLKDIV_MAX) && (uTFreq > FLASH_CLOCK_FREQUENCY_DESIRE))
        {
            uDivPos++;
            uTFreq = uClockFreq / ((uint32)1U << uDivPos);
        }
    }
    else
    {
        uTFreq = uClockFreq;
    }
    pCfg->bCLKDIV = (uint8)uDivPos;

    /*Calculate RDT*/
    /* #Violation: pflash_hal_c_REF_4 */
    uRDT = PFLASH_CALCULATE_RDT(uClockFreq);

    if (uRDT < (float32)0)
    {
        uRDT = (float32)0;
    }
    else
    {
        if (uRDT > (float32)((uint32)uRDT))
        {
            uRDT = uRDT + (float32)1;
        }
    }

    pCfg->bRDT = (uint8)uRDT;
    pCfg->bSTO0 = (uint8)(uTFreq / FLASH_STO0_FACTOR);
    if (0U < (uint32)(uTFreq % FLASH_STO0_FACTOR))
    {
        pCfg->bSTO0 += (uint8)1U;
    }

    if (0U != uTFreq)
    {
        /* Divide by 10,000 to simplify the calculation */
        uTFreq = uTFreq / 10000U;
        pCfg->bSTO1 = (uint8)((FLASH_STO1_DESIRE * uTFreq) / FLASH_CLOCK_FREQUENCY_CYCLE);
    }

    if(0U < ((FLASH_STO1_DESIRE * uTFreq) % FLASH_CLOCK_FREQUENCY_CYCLE))
    {
        pCfg->bSTO1 += (uint8)1U;
    }

#if defined(THA6_THA6104)
    pCfg->bSTO1 += (uint8)1U;
#endif
}

static uint32 Flash_Hal_PFlashStreamToUint32(const uint8 *const pPIN, uint8 Index)
{
    return ((uint32)pPIN[Index]) | ((uint32)pPIN[Index + 1U] << 8U) | ((uint32)pPIN[Index + 2U] << 16U) |
            ((uint32)pPIN[Index + 3U] << 24U);
}

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: pflash_hal_c_REF_5 */
boolean Flash_Hal_CheckPFlashBusy(uint32 uAddress)
{
    boolean bBusyStatus;
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    const volatile FLASH_STS_MODULE *pPFx_STS;
    bBusyStatus = TRUE;

    /* #Violation: pflash_hal_c_REF_3 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_3 */
        /* #Violation: pflash_hal_c_REF_4 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);

        bBusyStatus = Flash_Std_CheckPFlashBusy(pPFx_STS);
    }

    return bBusyStatus;
}


/* #Violation: pflash_hal_c_REF_5 */
Pflash_ResultStatus Flash_Hal_InitPFlash(void)
{
    Pflash_ResultStatus bRetSts;
    Pflash_StdStatus bStdSts;
    uint32 uClockFreq;
    Pflash_ClockCfg sClkCfg;
    uint8 clusterNum;
    FLASH_COMMON_CTR_MODULE *pCommonCtr;

    /* PFlash input clock source is the CPU clock */
    uClockFreq = (uint32)Rcc_Hal_GetSysClkFreq();
    if (uClockFreq < FLASH_CLOCK_FREQUENCY_MIN)
    {
        bRetSts = PFLASH_RESULTSTATUS_FAILED;
    }
    else
    {
        /*calculate RDT, STO0,STO1,Clk Div*/
        Flash_Hal_CalPFlashTiming(uClockFreq, &sClkCfg);
        /* #Violation: pflash_hal_c_REF_6 */
        for (clusterNum = 0; clusterNum < FLASH_CLUSTER_NUM; clusterNum++)
        {
            /* #Violation: pflash_hal_c_REF_3 */
            /* #Violation: pflash_hal_c_REF_4 */
            pCommonCtr = GET_CLUSTER_CTR(clusterNum);
            bStdSts = Flash_Std_InitPflash(pCommonCtr, &sClkCfg);

            if (PFLASH_STDSTATUS_OK == bStdSts)
            {
                bRetSts = PFLASH_RESULTSTATUS_OK;
            }
            else
            {
                bRetSts = PFLASH_RESULTSTATUS_FAILED;
                break;
            }
        }
    }
    return bRetSts;
}

/* #Violation: pflash_hal_c_REF_5 */
Pflash_ResultStatus Flash_Hal_PFlashSwitchFreq(uint32 uClockFreq)
{
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(uClockFreq <= FLASH_MAX_CLOCK));
#endif
    
    Pflash_ResultStatus bRetSts;
    Pflash_StdStatus bStdSts;
    Pflash_ClockCfg sClkCfg;
    uint8 clusterNum;
    FLASH_COMMON_CTR_MODULE *pCommonCtr;

    /*calculate RDT, STO0,STO1,Clk Div*/
    Flash_Hal_CalPFlashTiming(uClockFreq, &sClkCfg);
    /* #Violation: pflash_hal_c_REF_6 */
    for (clusterNum = 0; clusterNum < FLASH_CLUSTER_NUM; clusterNum++)
    {
        /* #Violation: pflash_hal_c_REF_3 */
        /* #Violation: pflash_hal_c_REF_4 */
        pCommonCtr = GET_CLUSTER_CTR(clusterNum);
        bStdSts = Flash_Std_InitPflash(pCommonCtr, &sClkCfg);

        if (PFLASH_STDSTATUS_OK == bStdSts)
        {
            bRetSts = PFLASH_RESULTSTATUS_OK;
        }
        else
        {
            bRetSts = PFLASH_RESULTSTATUS_FAILED;
            break;
        }
    }
    return bRetSts;
}


#if defined(THA6_THA6104) || defined(THA6_THA6412)
/* #Violation: pflash_hal_c_REF_5 */
Pflash_ResultStatus Flash_Hal_PFlashBufferConfig(const FLASH_PflashBufCfg *const pConfig)
{
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;
    Pflash_ResultStatus bRetSts;

    uint8 clusterNum;
    const FLASH_COMMON_CTR_MODULE *pCommonCtr;
    FLASH_COMMON_BUFCFG_MODULE *pBufcfg;
    uint32 regBufConfig;
    regBufConfig = 0;
    if (TRUE == pConfig->prefetchBufEn)
    {
        regBufConfig |= PF_BUFCFG_PBEN_MASK;
    }

#if defined(THA6_THA6412)
    if (TRUE == pConfig->commonDataBufEn)
    {
        regBufConfig |= PF_BUFCFG_CDBEN_MASK;
    }
    regBufConfig |= (((uint32)(pConfig->CommonDataBufMode)) << PF_BUFCFG_CDBMODE_OFFSET);
#endif

    for (clusterNum = 0; clusterNum < (uint8)FLASH_CLUSTER_NUM; clusterNum++)
    {
        /* #Violation: pflash_hal_c_REF_3 */
        /* #Violation: pflash_hal_c_REF_1 */
        pCommonCtr = GET_CLUSTER_CTR(clusterNum);
        /* #Violation: pflash_hal_c_REF_1 */
        /* #Violation: pflash_hal_c_REF_3 */
        pBufcfg = (FLASH_COMMON_BUFCFG_MODULE *)GET_BUFCFG_FROM_CLUSTER((pCommonCtr));

        ret &= Flash_Std_ConfigPFlashBuf(pBufcfg, regBufConfig);
        bRetSts = PFLASH_RESULTSTATUS_OK;
    }

    if(FALSE == ret)
    {
        bRetSts = PFLASH_RESULTSTATUS_FAILED;
    }

    return bRetSts;
}
#endif

/* #Violation: pflash_hal_c_REF_5 */
Pflash_ResultStatus Flash_Hal_ErasePFlashSync(uint32 uAddress, Pflash_EraseType eErType)
{
    boolean ret;
    ret = TRUE;
    uint64 uTimeout;
    boolean bBusyStatus;
    Pflash_OperationStatus uCurStatus;
    Pflash_ResultStatus bRetStatus;
    FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_STS_MODULE *pPFx_STS;
    uint32 checkBlabkLoop;
    uint8 i;
    checkBlabkLoop = 1;
    /* #Violation: pflash_hal_c_REF_3 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /*Set erase address and erase type. Under normal mode, PFlash support sector
        erase only*/
        /* #Violation: pflash_hal_c_REF_3 */
        /* #Violation: pflash_hal_c_REF_4 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        ret &= Flash_Std_ErasePFlash(pPFx_CTR, uAddress, (uint8)eErType);
        uTimeout = Stm_Hal_GetValue();
        do
        {
            bBusyStatus = Flash_Std_CheckPFlashBusy(pPFx_STS);
        } while (((Stm_Hal_GetValue() - uTimeout) < (uint64)PFLASH_ERASE_TIMEOUT) &&
                 (TRUE == bBusyStatus));
        if (FALSE == bBusyStatus)
        {
            uCurStatus = Flash_Std_GetPFlashEraseStatus(pPFx_STS);
            Flash_Std_ClearPFlashEraseStatus(pPFx_STS);
            if (PFLASH_OPERATIONSTATUS_COMPLETED == uCurStatus)
            {
                if(PFLASH_ERASETYPE_BLOCK == eErType)
                {
                    checkBlabkLoop = FLASH_PFLASH_SECTOR_NUM_INBLOCK;
                }
                /* Check PFlash Blank */
                for(i = 0; i < checkBlabkLoop; i++)
                {

                    bRetStatus = Flash_Hal_CheckPFlashBlankSync(uAddress + (uint32)(i * (uint32)FLASH_PFLASH_SECTOR_SIZE), PFLASH_BLANKTYPE_SECTOR);
                    if(PFLASH_RESULTSTATUS_OK != bRetStatus)
                    {
                        break;
                    }
                }
            }
            else
            {
                bRetStatus = PFLASH_RESULTSTATUS_FAILED;
            }
        }
        else
        {
            bRetStatus = PFLASH_RESULTSTATUS_TIMEOUT;
            Flash_Std_ClearAllPFlashStatus(pPFx_STS);
        }
    }
    else
    {
        bRetStatus = PFLASH_RESULTSTATUS_PARAM_ERR;
    }

    if(FALSE == ret)
    {
        bRetStatus = PFLASH_RESULTSTATUS_FAILED;
    }

    return bRetStatus;
}

/* #Violation: pflash_hal_c_REF_5 */
boolean Flash_Hal_ErasePFlashAsync(uint32 uAddress, Pflash_EraseType eErType)
{
    boolean ret;
    ret = TRUE;
    FLASH_CTR_MODULE *pPFx_CTR;
    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);

    if (pPFx_CTR != NULL_PTR)
    {
        ret &= Flash_Std_ErasePFlash(pPFx_CTR, uAddress, (uint8)eErType);
    }

    return ret;
}

/* #Violation: pflash_hal_c_REF_5 */
Pflash_ResultStatus Flash_Hal_GetPFlashEraseStatus(uint32 uAddress)
{
    Pflash_OperationStatus uCurStatus;
    Pflash_ResultStatus bRetStatus;
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_STS_MODULE *pPFx_STS;
    boolean bBusyStatus;

    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);

        bBusyStatus = Flash_Std_CheckPFlashBusy(pPFx_STS);
        if (FALSE == bBusyStatus)
        {
            uCurStatus = Flash_Std_GetPFlashEraseStatus(pPFx_STS);
            Flash_Std_ClearPFlashEraseStatus(pPFx_STS);
            if (PFLASH_OPERATIONSTATUS_COMPLETED == uCurStatus)
            {
                bRetStatus = PFLASH_RESULTSTATUS_OK;
            }
            else
            {
                bRetStatus = PFLASH_RESULTSTATUS_FAILED;
            }
        }
        else
        {
            bRetStatus = PFLASH_RESULTSTATUS_BUSY;
        }
       
    }
    else
    {
        bRetStatus = PFLASH_RESULTSTATUS_PARAM_ERR;
    }

    return bRetStatus;
}

/* #Violation: pflash_hal_c_REF_5 */
void Flash_Hal_ClearPFlashEraseStatus(uint32 uAddress)
{
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_STS_MODULE *pPFx_STS;

    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        Flash_Std_ClearPFlashEraseStatus(pPFx_STS);
    }
}


/* #Violation: pflash_hal_c_REF_5 */
Pflash_ResultStatus Flash_Hal_ProgPFlashSync(uint32 uAddress, const uint32 *const pData, uint32 uDataLen)
{
    boolean ret;
    ret = TRUE;
    uint64 uTimeout;
    boolean bBusyStatus;
    Pflash_OperationStatus uCurStatus;
    Pflash_ResultStatus bRetStatus;
    FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_STS_MODULE *pPFx_STS;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if the pData is null pointer */
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pData));
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(uDataLen <= FLASH_PFLASH_MAX_PWORD_SIZE));
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(FLASH_PFLASH_PWORD_SIZE <= uDataLen));
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(FALSE == (uDataLen % FLASH_PFLASH_PWORD_SIZE)));
#endif /* INPUT_ARG_DETECT */

    /* #Violation: pflash_hal_c_REF_3 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /*Set erase address and erase type. Under normal mode, PFlash support sector
        erase only*/
        /* #Violation: pflash_hal_c_REF_3 */
        /* #Violation: pflash_hal_c_REF_4 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        ret &= Flash_Std_ProgPFlash(pPFx_CTR, uAddress, pData, uDataLen);
        uTimeout = Stm_Hal_GetValue();
        do
        {
            bBusyStatus = Flash_Std_CheckPFlashBusy(pPFx_STS);
        } while (((Stm_Hal_GetValue() - uTimeout) < (uint64)PFLASH_PROG_TIMEOUT) &&
                 (TRUE == bBusyStatus));
        if (FALSE == bBusyStatus)
        {
            uCurStatus = Flash_Std_GetPFlashProgStatus(pPFx_STS);
            Flash_Std_ClearPFlashProgStatus(pPFx_STS);
            if (PFLASH_OPERATIONSTATUS_COMPLETED == uCurStatus)
            {
                bRetStatus = Flash_Hal_PFlashProgCheck(uAddress, pData, uDataLen);
            }
            else
            {
                bRetStatus = PFLASH_RESULTSTATUS_FAILED;
            }
        }
        else
        {
            bRetStatus = PFLASH_RESULTSTATUS_TIMEOUT;
            Flash_Std_ClearAllPFlashStatus(pPFx_STS);
        }
    }
    else
    {
        bRetStatus = PFLASH_RESULTSTATUS_PARAM_ERR;
    }

    if(FALSE == ret)
    {
        bRetStatus = PFLASH_RESULTSTATUS_FAILED;
    }
    return bRetStatus;
}

/* #Violation: pflash_hal_c_REF_8 */
Pflash_ResultStatus Flash_Hal_PFlashProgCheck(uint32 uAddress, const uint32 *const pData, uint32 uDataLen)
{
    Pflash_ResultStatus bRetStatus;
    uint32 progAddress;
    uint32 uLoop;

    FLASH_CTR_MODULE const *pPFx_CTR;
    uint32 dataVal;
    uint32 pDataAddr;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if the pData is null pointer */
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pData));
#endif /* INPUT_ARG_DETECT */

    progAddress = uAddress;
    bRetStatus = PFLASH_RESULTSTATUS_OK;
    /* #Violation: pflash_hal_c_REF_3 */
    pDataAddr = (uint32)pData;
    /* #Violation: pflash_hal_c_REF_3 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if ((pPFx_CTR != NULL_PTR) && (FALSE == (uDataLen % 4U)))
    {
        if(FALSE != (pDataAddr & 0x3U))
        {
            for (uLoop = 0; uLoop < (uDataLen / 4U); uLoop++)
            {
                dataVal = Flash_Hal_PFlashStreamToUint32((const uint8 *)pData, (uint8)(uLoop * 4U));
                /* #Violation: pflash_hal_c_REF_3 */
                if(*(volatile uint32 *)(progAddress + (uLoop * 4U)) != dataVal)
                {
                    bRetStatus = PFLASH_RESULTSTATUS_FAILED;
                    break;
                }
            }
        }
        else
        {
            for (uLoop = 0; uLoop < (uDataLen / 4U); uLoop++)
            {
                /* #Violation: pflash_hal_c_REF_1 */
                /* #Violation: pflash_hal_c_REF_3 */
                dataVal = *((volatile uint32 *)(pDataAddr + (uLoop * 4U)));
                /* #Violation: pflash_hal_c_REF_1 */
                /* #Violation: pflash_hal_c_REF_3 */
                if(*(volatile uint32 *)(progAddress + (uLoop * 4U)) != dataVal)
                {
                    bRetStatus = PFLASH_RESULTSTATUS_FAILED;
                    break;
                }
            }
            
        }
    }
    else
    {
        bRetStatus = PFLASH_RESULTSTATUS_PARAM_ERR;
    }
    
    return bRetStatus;
}


/* #Violation: pflash_hal_c_REF_5 */
boolean Flash_Hal_ProgPFlashAsync(uint32 uAddress, const uint32 *const pData, uint32 uDataLen)
{
    boolean ret;
    ret = TRUE;
    FLASH_CTR_MODULE *pPFx_CTR;

#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if the pData is null pointer */
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pData));
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(uDataLen <= FLASH_PFLASH_MAX_PWORD_SIZE));
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(FLASH_PFLASH_PWORD_SIZE <= uDataLen));
    /* #Violation: pflash_hal_c_REF_2 */
    Assert((boolean)(FALSE == (uDataLen % FLASH_PFLASH_PWORD_SIZE)));
#endif /* INPUT_ARG_DETECT */

    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        ret &= Flash_Std_ProgPFlash(pPFx_CTR, uAddress, pData, uDataLen);
    }

    return ret;

}

/* #Violation: pflash_hal_c_REF_5 */
Pflash_ResultStatus Flash_Hal_GetPFlashProgStatus(uint32 uAddress)
{
    boolean bBusyStatus;
    Pflash_OperationStatus uCurStatus;
    Pflash_ResultStatus bRetStatus;
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_STS_MODULE *pPFx_STS;
    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        bBusyStatus = Flash_Std_CheckPFlashBusy(pPFx_STS);
        if (FALSE == bBusyStatus)
        {
            uCurStatus = Flash_Std_GetPFlashProgStatus(pPFx_STS);
            Flash_Std_ClearPFlashProgStatus(pPFx_STS);
            if (PFLASH_OPERATIONSTATUS_COMPLETED == uCurStatus)
            {
                bRetStatus = PFLASH_RESULTSTATUS_OK;
            }
            else
            {
                bRetStatus = PFLASH_RESULTSTATUS_FAILED;
            }
        }
        else
        {
            bRetStatus = PFLASH_RESULTSTATUS_BUSY;
        }
       
    }
    else
    {
        bRetStatus = PFLASH_RESULTSTATUS_PARAM_ERR;
    }

    return bRetStatus;
}

/* #Violation: pflash_hal_c_REF_5 */
void Flash_Hal_ClearPFlashProgStatus(uint32 uAddress)
{
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_STS_MODULE *pPFx_STS;

    /* #Violation: pflash_hal_c_REF_4 */
    /* #Violation: pflash_hal_c_REF_3 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        Flash_Std_ClearPFlashProgStatus(pPFx_STS);
    }
}

/* #Violation: pflash_hal_c_REF_5 */
void Flash_Hal_ClearAllPFlashStatus(uint32 uAddress)
{
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_STS_MODULE *pPFx_STS;

    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        Flash_Std_ClearAllPFlashStatus(pPFx_STS);
    }
}

/* #Violation: pflash_hal_c_REF_5 */
uint32 Flash_Hal_GetAllPFlashStatus(uint32 uAddress)
{
    uint32 staRet;
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    const volatile FLASH_STS_MODULE *pPFx_STS;

    staRet = 0U;

    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        staRet = Flash_Std_GetAllPFlashStatus(pPFx_STS);
    }

    return staRet;
}


/* #Violation: pflash_hal_c_REF_5 */
boolean Flash_Hal_GetPFlashEccStatus(uint32 uAddress)
{
    boolean staRet;
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    const volatile FLASH_STS_MODULE *pPFx_STS;

    staRet = FALSE;

    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        staRet = Flash_Std_GetPFlashEccStatus(pPFx_STS);
    }

    return staRet;
}


/* #Violation: pflash_hal_c_REF_5 */
boolean Flash_Hal_ClearPFlashEccStatus(uint32 uAddress)
{
    boolean ret;
    ret = TRUE;
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_STS_MODULE *pPFx_STS;

    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        DISABLE_ALL_INTERRUPTS();
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        
        Flash_Std_ClearPFlashEccStatus(pPFx_STS);
        ret &= Safewdt_Hal_SetSafetyEndinit();
        
        ENABLE_ALL_INTERRUPTS();
    }

    return ret;

}

/* #Violation: pflash_hal_c_REF_5 */
boolean Flash_Hal_ConfigPFlashInt(uint32 uAddress, uint32 uFlashInt, Pflash_IntOp eOp)
{
    boolean ret;
    ret = TRUE;
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_MSK_MODULE *pPFx_MSK;

    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_MSK = GET_PFLASH_MSK_FROM_CTR(pPFx_CTR);
        if (PFLASH_INTOP_ENABLE == eOp)
        {
            ret &= Flash_Std_EnablePFlashInt(pPFx_MSK, uFlashInt);
        }
        else
        {
            ret &= Flash_Std_DisablePFlashInt(pPFx_MSK, uFlashInt);
        }
    }

    return ret;
}

/* #Violation: pflash_hal_c_REF_5 */
boolean Flash_Hal_ConfigAllPFlashInt(uint32 uFlashInt, Pflash_IntOp eOp)
{
    boolean ret;
    ret = TRUE;

    if (PFLASH_INTOP_ENABLE == eOp)
    {
        /* #Violation: pflash_hal_c_REF_3 */
        ret &= Flash_Std_EnablePFlashInt(FLASH_PFLASH0_MSK, uFlashInt);
        /* #Violation: pflash_hal_c_REF_3 */
        ret &= Flash_Std_EnablePFlashInt(FLASH_PFLASH1_MSK, uFlashInt);
#if defined(THA6_THA6412)
        /* #Violation: pflash_hal_c_REF_3 */
        ret &= Flash_Std_EnablePFlashInt(FLASH_PFLASH2_MSK, uFlashInt);
        /* #Violation: pflash_hal_c_REF_3 */
        ret &= Flash_Std_EnablePFlashInt(FLASH_PFLASH3_MSK, uFlashInt);
#endif
    }
    else
    {
        /* #Violation: pflash_hal_c_REF_3 */
        ret &= Flash_Std_DisablePFlashInt(FLASH_PFLASH0_MSK, uFlashInt);
        /* #Violation: pflash_hal_c_REF_3 */
        ret &= Flash_Std_DisablePFlashInt(FLASH_PFLASH1_MSK, uFlashInt);
#if defined(THA6_THA6412)
        /* #Violation: pflash_hal_c_REF_3 */
        ret &= Flash_Std_DisablePFlashInt(FLASH_PFLASH2_MSK, uFlashInt);
        /* #Violation: pflash_hal_c_REF_3 */
        ret &= Flash_Std_DisablePFlashInt(FLASH_PFLASH3_MSK, uFlashInt);
#endif
    }

    return ret;
}

/* #Violation: pflash_hal_c_REF_5 */
boolean Flash_Hal_ConfigPFlashEccBusErrorAlarm(uint32 uAddress, Pflash_IntOp eOp)
{
    boolean ret;
    ret = TRUE;
    const volatile FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_MSK_MODULE *pPFx_MSK;

    /* #Violation: pflash_hal_c_REF_4 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_4 */
        /* #Violation: pflash_hal_c_REF_3 */
        pPFx_MSK = GET_PFLASH_MSK_FROM_CTR(pPFx_CTR);
        DISABLE_ALL_INTERRUPTS();
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        
        if (PFLASH_INTOP_ENABLE == eOp)
        {
            ret &= Flash_Std_EnablePFlashEccBusErrorAlarm(pPFx_MSK);
        }
        else
        {
            ret &= Flash_Std_DisablePFlashEccBusErrorAlarm(pPFx_MSK);
        }
        ret &= Safewdt_Hal_SetSafetyEndinit();
        
        ENABLE_ALL_INTERRUPTS();
    }

    return ret;
}


/* #Violation: pflash_hal_c_REF_8 */
Pflash_ResultStatus Flash_Hal_CheckPFlashBlankSync(uint32 uAddress, Pflash_BlankType eBlank)
{
    boolean ret;
    ret = TRUE;
    Pflash_ResultStatus bRetStatus;
    uint64 uTimeout;
    boolean bBusyStatus;
    Pflash_OperationStatus uCurStatus;
    FLASH_CTR_MODULE *pPFx_CTR;
    FLASH_STS_MODULE *pPFx_STS;

    /* #Violation: pflash_hal_c_REF_3 */
    pPFx_CTR = Flash_Std_GetPFlashCtr(uAddress);
    if (pPFx_CTR != NULL_PTR)
    {
        /* #Violation: pflash_hal_c_REF_3 */
        /* #Violation: pflash_hal_c_REF_4 */
        pPFx_STS = GET_PFLASH_STS_FROM_CTR(pPFx_CTR);
        ret &= Flash_Std_CheckPFlashBlank(pPFx_CTR, uAddress, eBlank);
        uTimeout = Stm_Hal_GetValue();
        do
        {
            bBusyStatus = Flash_Std_CheckPFlashBusy(pPFx_STS);
        } while (((Stm_Hal_GetValue() - uTimeout) < (uint64)PFLASH_BLANK_CHECK_TIMEOUT) &&
                 (TRUE == bBusyStatus));
        if (FALSE == bBusyStatus)
        {
            uCurStatus = Flash_Std_GetPFlashBlankStatus(pPFx_STS);
            Flash_Std_ClearPFlashBlankStatus(pPFx_STS);
            if (PFLASH_OPERATIONSTATUS_COMPLETED == uCurStatus)
            {
                bRetStatus = PFLASH_RESULTSTATUS_OK;
            }
            else
            {
                bRetStatus = PFLASH_RESULTSTATUS_FAILED;
            }
        }
        else
        {
            bRetStatus = PFLASH_RESULTSTATUS_TIMEOUT;
            Flash_Std_ClearAllPFlashStatus(pPFx_STS);
        }
    }
    else
    {
        bRetStatus = PFLASH_RESULTSTATUS_PARAM_ERR;
    }

    if(FALSE == ret)
    {
        bRetStatus = PFLASH_RESULTSTATUS_FAILED;
    }
    
    return bRetStatus;
}

/* #Violation: pflash_hal_c_REF_1 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pflash_hal_c_REF_7 */
#include "Fls_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

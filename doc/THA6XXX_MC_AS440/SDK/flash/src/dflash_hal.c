/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dflash_hal.c
 * Author:      00393
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of Flash module.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#dflash_hal_c_REF_1:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 *
 * #dflash_hal_c_REF_2:MISRAC2012-Dir-4.9;
 * Justification: Function like macros are used to reduce code complexity.
 *
 * #dflash_hal_c_REF_3:MISRAC2012-Rule-10.5;
 * Justification: Cortex-R52+ lacks bool type, minimum unit is uint8.
 *
 * #dflash_hal_c_REF_4:MISRAC2012-Rule-2.1;
 * Justification: The interface is called by the application layer.
 * 
 * #dflash_hal_c_REF_5:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 *
 * #dflash_hal_c_REF_6:MISRAC2012-Rule-8.7; 
 * Justification:The function is used by other file.
 *
 * #dflash_hal_c_REF_7:MISRAC2012-Rule-11.4;
 * Justification:Converting integers to object pointers to reduce register access complexity.
 */

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "dflash_std.h"
#include "dflash_hal.h"
#include "stm_hal.h"
#include "rcc_hal.h"
#include "safewdt_hal.h"
#include "tha6_cfg.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/*^INTERNAL MACRO^*/
#define DFLASH_BLANK_CHECK_TIMEOUT (0x100000U) /*Blank check timeout*/
#define FLASH_CLOCK_FREQUENCY_MIN (10000000U)  /*10MHZ*/
/* #Violation: dflash_hal_c_REF_1 */
#define FLASH_CLOCK_FREQUENCY_MAX (100000000U)    /*100MHZ*/
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
#define FLASH_CLOCK_FREQUENCY_DESIRE (100000000U) /*100MHZ*/
#endif
#if defined(THA6_THA6104)
#define FLASH_CLOCK_FREQUENCY_DESIRE (75000000U) /*75MHZ*/
#endif
#define FLASH_CLOCK_FREQUENCY_CYCLE (100000U) /* ns / 10000 */

/* #Violation: dflash_hal_c_REF_1 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dflash_hal_c_REF_5 */
#include "Fls_MemMap.h"
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:             Flash_Hal_CheckDFlashAddr
 * Description:          Check the address of Dflash.
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uint32|uAddress:the address of Dflash
 * Inout:                None
 * Output:               None
 * Return:               Dflash_Type: The type of Dflash
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
static Dflash_Type Flash_Hal_CheckDFlashAddr(uint32 uAddress);
/**********************************************************************************************************************
 * Function:             Flash_Hal_CalDFlashTiming
 * Description:          Calculate the timing of Dflash operations
 * Sync/Async:           Synchronous
 * Reentrancy:           Non-Reentrant
 * Input:                uint32|uClockFreq:The CPU clock frequency
 * Inout:                None
 * Output:               Pflash_ClockCfg *|pCfg:The pointer to the structure for configuring Dflash timing
 * Return:               None
 * Others:               None
 * History:
 * Date          Author    Modified
 * 2023/10/27    00393     Create
 *********************************************************************************************************************/
static void Flash_Hal_CalDFlashTiming(uint32 uClockFreq, Dflash_ClockCfg *const pCfg);

/**********************************************************************************************************************
 * Function:             Flash_Hal_DFlashStreamToUint32
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
static uint32 Flash_Hal_DFlashStreamToUint32(const uint8 * const pPIN, uint8 Index);


/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static Dflash_Type Flash_Hal_CheckDFlashAddr(uint32 uAddress)
{
    Dflash_Type eType;
    /* #Violation: dflash_hal_c_REF_2 */
    if (TRUE == CHECK_DFLASH_ADDRESS(uAddress))
    {
        eType = DFLASH_TYPE_DFLASH;
    }
    else
    {
        eType = DFLASH_TYPE_OTHER;
    }
    return eType;
}

static void Flash_Hal_CalDFlashTiming(uint32 uClockFreq, Dflash_ClockCfg *const pCfg)
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
        while (((uDivPos < ((uint32)FLASH_CLKDIV_MAX)) && ((uTFreq > FLASH_CLOCK_FREQUENCY_DESIRE))))
        {
            uDivPos++;
            uTFreq = (uint32)(uClockFreq / ((uint32)1U << uDivPos));
        }
    }
    else
    {
        uTFreq = uClockFreq;
    }
    pCfg->bCLKDIV = (uint8)uDivPos;

    /*Calculate RDT*/
    /* #Violation: dflash_hal_c_REF_2 */
    uRDT = DFLASH_CALCULATE_RDT(uClockFreq);

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

static uint32 Flash_Hal_DFlashStreamToUint32(const uint8 *const pPIN, uint8 Index)
{
    return ((uint32)pPIN[Index]) | ((uint32)pPIN[Index + 1U] << 8U) | ((uint32)pPIN[Index + 2U] << 16U) |
            ((uint32)pPIN[Index + 3U] << 24U);
}

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: dflash_hal_c_REF_4 */
Dflash_ResultStatus Flash_Hal_InitDFlash(void)
{
    Dflash_ResultStatus bRetSts;
    Dflash_StdStatus bStdSts;
    uint32 uClockFreq;
    Dflash_ClockCfg sClkCfg;

    /* DFlash input clock source is the CPU clodk divided 2*/
    uClockFreq = (uint32)Rcc_Hal_GetSysClkFreq() / (uint32)2U;
    if (uClockFreq < FLASH_CLOCK_FREQUENCY_MIN)
    {
        bRetSts = DFLASH_RESULTSTATUS_FAILED;
    }
    else
    {
        /*calculate RDT, STO0,STO1,Clk Div*/
        Flash_Hal_CalDFlashTiming(uClockFreq, &sClkCfg);
        bStdSts = Flash_Std_InitDflash(&sClkCfg);
        if (DFLASH_STDSTATUS_OK == bStdSts)
        {
            bRetSts = DFLASH_RESULTSTATUS_OK;
        }
        else
        {
            bRetSts = DFLASH_RESULTSTATUS_FAILED;
        }
    }
    return bRetSts;
}

/* #Violation: dflash_hal_c_REF_4 */
Dflash_ResultStatus Flash_Hal_DFlashSwitchFreq(uint32 uClockFreq)
{
    Dflash_ResultStatus bRetSts;
    Dflash_StdStatus bStdSts;
    Dflash_ClockCfg sClkCfg;
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: dflash_hal_c_REF_3 */
    Assert((boolean)(uClockFreq <= FLASH_MAX_CLOCK));
#endif

    /*calculate RDT, STO0,STO1,Clk Div*/
    Flash_Hal_CalDFlashTiming(uClockFreq / (uint32)2, &sClkCfg);

    bStdSts = Flash_Std_InitDflash(&sClkCfg);
    if (DFLASH_STDSTATUS_OK == bStdSts)
    {
        bRetSts = DFLASH_RESULTSTATUS_OK;
    }
    else
    {
        bRetSts = DFLASH_RESULTSTATUS_FAILED;
    }
    return bRetSts;
}

/* #Violation: dflash_hal_c_REF_6 */
boolean Flash_Hal_CheckDFlashBusy(void)
{
    return Flash_Std_CheckDFlashBusy();
}

/* #Violation: dflash_hal_c_REF_4 */
Dflash_ResultStatus Flash_Hal_GetDFlashStatus(Dflash_StatusID eStatusID)
{
    Dflash_OperationStatus status;
    Dflash_ResultStatus bRetStatus;
    status = DFLASH_OPERATIONSTATUS_ERROR;
    bRetStatus = DFLASH_RESULTSTATUS_FAILED;

    if (DFLASH_STATUSID_PROG == eStatusID)
    {
        status = Flash_Std_GetDFlashProgStatus();
    }
    else if (DFLASH_STATUSID_ERASE == eStatusID)
    {
        status = Flash_Std_GetDFlashEraseStatus();
    }
    else if (DFLASH_STATUSID_BLANK == eStatusID)
    {
        status = Flash_Std_GetDFlashBlankStatus();
    }
    else
    {
        bRetStatus = DFLASH_RESULTSTATUS_PARAM_ERR;
    }
    if (DFLASH_OPERATIONSTATUS_COMPLETED == status)
    {
        bRetStatus = DFLASH_RESULTSTATUS_OK;
    }
    return bRetStatus;
}

/* #Violation: dflash_hal_c_REF_4 */
void Flash_Hal_ClearDFlashStatus(Dflash_StatusID eStatusID)
{
    if (DFLASH_STATUSID_PROG == eStatusID)
    {
        Flash_Std_ClearDFlashProgStatus();
    }
    else if (DFLASH_STATUSID_ERASE == eStatusID)
    {
        Flash_Std_ClearDFlashEraseStatus();
    }
    else if (DFLASH_STATUSID_BLANK == eStatusID)
    {
        Flash_Std_ClearDFlashBlankStatus();
    }
    else
    {
        /*else*/
    }
}

/* #Violation: dflash_hal_c_REF_4 */
uint32 Flash_Hal_GetAllDFlashStatus(void)
{
    return Flash_Std_GetAllDFlashStatus();
}

/* #Violation: dflash_hal_c_REF_4 */
void Flash_Hal_ClearAllDFlashStatus(void)
{
    Flash_Std_ClearAllDFlashStatus();
}

/* #Violation: dflash_hal_c_REF_4 */
Dflash_ResultStatus Flash_Hal_EraseDFlash(uint32 uAddress)
{
    boolean ret;
    ret = TRUE;
    Dflash_ResultStatus bRetStatus;
    if (DFLASH_TYPE_DFLASH == Flash_Hal_CheckDFlashAddr(uAddress))
    {
        /*Set erase address*/
        ret = Flash_Std_EraseDFlash(uAddress);
        bRetStatus = DFLASH_RESULTSTATUS_OK;
    }
    else
    {
        bRetStatus = DFLASH_RESULTSTATUS_PARAM_ERR;
    }

    if (FALSE == ret)
    {
        bRetStatus = DFLASH_RESULTSTATUS_FAILED;
    }

    return bRetStatus;
}

/* #Violation: dflash_hal_c_REF_4 */
Dflash_ResultStatus Flash_Hal_ProgDFlash(uint32 uAddress, const uint8 *const pData, uint32 uDataLen)
{
    boolean ret;
    ret = TRUE;
    Dflash_ResultStatus bRetStatus;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if the pData is null pointer */
    /* #Violation: dflash_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pData));
    /* #Violation: dflash_hal_c_REF_3 */
    Assert((boolean)(uDataLen <= FLASH_DFLASH_MAX_PWORD_SIZE));
    /* #Violation: dflash_hal_c_REF_3 */
    Assert((boolean)(FLASH_DFLASH_PWORD_SIZE <= uDataLen));
    /* #Violation: dflash_hal_c_REF_3 */
    Assert((boolean)(FALSE == (uDataLen % FLASH_DFLASH_PWORD_SIZE)));
#endif /* INPUT_ARG_DETECT */
    if (DFLASH_TYPE_DFLASH == Flash_Hal_CheckDFlashAddr(uAddress))
    {
        ret &= Flash_Std_ProgDFlash(uAddress, pData, uDataLen);
        bRetStatus = DFLASH_RESULTSTATUS_OK;
    }
    else
    {
        bRetStatus = DFLASH_RESULTSTATUS_PARAM_ERR;
    }

    if (FALSE == ret)
    {
        bRetStatus = DFLASH_RESULTSTATUS_FAILED;
    }

    return bRetStatus;
}

/* #Violation: dflash_hal_c_REF_4 */
Dflash_ResultStatus Flash_Hal_DFlashProgCheck(uint32 uAddress, const uint8 *const pData, uint32 uDataLen)
{
    Dflash_ResultStatus bRetStatus;
    uint32 progAddress;
    uint32 uLoop;
    uint32 dataVal;
    uint32 pDataAddr;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if the pData is null pointer */
    /* #Violation: dflash_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pData));
#endif /* INPUT_ARG_DETECT */

    progAddress = uAddress;
    /* #Violation: dflash_hal_c_REF_7 */
    pDataAddr = (uint32)pData;
    bRetStatus = DFLASH_RESULTSTATUS_OK;

    if ((DFLASH_TYPE_DFLASH == Flash_Hal_CheckDFlashAddr(uAddress)) && (FALSE == (uDataLen % 4U)))
    {
        if(FALSE != (pDataAddr & 0x3U))
        {
            for (uLoop = 0; uLoop < (uDataLen / 4U); uLoop++)
            {
                dataVal = Flash_Hal_DFlashStreamToUint32(pData, (uint8)(uLoop * 4U));
                /* #Violation: dflash_hal_c_REF_7 */
                if(*(volatile uint32 *)(progAddress + (uLoop * 4U)) != dataVal)
                {
                    bRetStatus = DFLASH_RESULTSTATUS_FAILED;
                    break;
                }
            }
        }
        else
        {
            for (uLoop = 0; uLoop < (uDataLen / 4U); uLoop++)
            {
                /* #Violation: dflash_hal_c_REF_7 */
                dataVal = *((volatile uint32 *)(pDataAddr + (uLoop * 4U)));
                /* #Violation: dflash_hal_c_REF_7 */
                if(*(volatile uint32 *)(progAddress + (uLoop * 4U)) != dataVal)
                {
                    bRetStatus = DFLASH_RESULTSTATUS_FAILED;
                    break;
                }
            }
            
        }
            
    }
    else
    {
        bRetStatus = DFLASH_RESULTSTATUS_PARAM_ERR;
    }

    return bRetStatus;

}



/* #Violation: dflash_hal_c_REF_4 */
Dflash_ResultStatus Flash_Hal_CheckDFlashBlankSync(uint32 uAddress, uint32 uLen)
{
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if the uLen equal zero */
    /* #Violation: dflash_hal_c_REF_3 */
    Assert((boolean)(uLen > 0UL));
#endif /* INPUT_ARG_DETECT */

    Dflash_ResultStatus bRetStatus;
    boolean ret;
    ret = TRUE;
    uint64 uTimeout;
    boolean bBusyStatus;
    Dflash_OperationStatus uCurStatus;
    uint32 loopCnt;
    uint32 cnt;
    boolean loopFlag;

    loopFlag = TRUE;
    loopCnt = uLen / FLASH_DFLASH_PWORD_SIZE;

    if (0UL < (uLen % FLASH_DFLASH_PWORD_SIZE))
    {
        ++loopCnt;
    }

    bRetStatus = DFLASH_RESULTSTATUS_FAILED;

    if (DFLASH_TYPE_DFLASH == Flash_Hal_CheckDFlashAddr(uAddress))
    {
        for (cnt = 0; (cnt < loopCnt) && (TRUE == loopFlag); cnt++)
        {
            ret &= Flash_Std_CheckDFlashBlank(uAddress + (cnt * FLASH_DFLASH_PWORD_SIZE), BLANK_TYPE_PWORD);
            uTimeout = Stm_Hal_GetValue();
            do
            {
                bBusyStatus = Flash_Hal_CheckDFlashBusy();
            } while (((Stm_Hal_GetValue() - uTimeout) < (uint64)DFLASH_BLANK_CHECK_TIMEOUT) && (TRUE == bBusyStatus));
            if (FALSE == bBusyStatus)
            {
                uCurStatus = Flash_Std_GetDFlashBlankStatus();
                Flash_Std_ClearDFlashBlankStatus();
                if (DFLASH_OPERATIONSTATUS_COMPLETED == uCurStatus)
                {
                    bRetStatus = DFLASH_RESULTSTATUS_OK;
                }
                else
                {
                    bRetStatus = DFLASH_RESULTSTATUS_FAILED;
                    loopFlag = FALSE;
                }
            }
            else
            {
                bRetStatus = DFLASH_RESULTSTATUS_TIMEOUT;
                loopFlag = FALSE;
                Flash_Std_ClearAllDFlashStatus();
            }
        }
    }
    else
    {
        bRetStatus = DFLASH_RESULTSTATUS_PARAM_ERR;
    }

    if (FALSE == ret)
    {
        bRetStatus = DFLASH_RESULTSTATUS_FAILED;
    }

    return bRetStatus;
}

/* #Violation: dflash_hal_c_REF_4 */
Dflash_ResultStatus Flash_Hal_CheckDFlashSectorBlankSync(uint32 uAddress)
{
    Dflash_ResultStatus bRetStatus;
    boolean ret;
    ret = TRUE;
    uint64 uTimeout;
    boolean bBusyStatus;
    Dflash_OperationStatus uCurStatus;

    if (DFLASH_TYPE_DFLASH == Flash_Hal_CheckDFlashAddr(uAddress))
    {
        ret &= Flash_Std_CheckDFlashBlank(uAddress, BLANK_TYPE_SECTOR);
        uTimeout = Stm_Hal_GetValue();
        do
        {
            bBusyStatus = Flash_Hal_CheckDFlashBusy();
        } while (((Stm_Hal_GetValue() - uTimeout) < (uint64)DFLASH_BLANK_CHECK_TIMEOUT) && (TRUE == bBusyStatus));
        
        if (FALSE == bBusyStatus)
        {
            uCurStatus = Flash_Std_GetDFlashBlankStatus();
            Flash_Std_ClearDFlashBlankStatus();
            if (DFLASH_OPERATIONSTATUS_COMPLETED == uCurStatus)
            {
                bRetStatus = DFLASH_RESULTSTATUS_OK;
            }
            else
            {
                bRetStatus = DFLASH_RESULTSTATUS_FAILED;
            }
        }
        else
        {
            bRetStatus = DFLASH_RESULTSTATUS_TIMEOUT;
            Flash_Std_ClearAllDFlashStatus();
        }

    }
    else
    {
        bRetStatus = DFLASH_RESULTSTATUS_PARAM_ERR;
    }

    if (FALSE == ret)
    {
        bRetStatus = DFLASH_RESULTSTATUS_FAILED;
    }

    return bRetStatus;
}


/* #Violation: dflash_hal_c_REF_4 */
boolean Flash_Hal_ConfigDFlashInt(uint32 uFlashInt, Dflash_IntOp eOp)
{
    boolean ret;
    ret = TRUE;
    if (DFLASH_INTOP_ENABLE == eOp)
    {
        ret &= Flash_Std_EnableDFlashInt(uFlashInt);
    }
    else
    {
        ret &= Flash_Std_DisableDFlashInt(uFlashInt);
    }
    return ret;
}

/* #Violation: dflash_hal_c_REF_4 */
boolean Flash_Hal_ConfigDFlashEccBusErrorAlarm(Dflash_IntOp eOp)
{
    boolean ret;
    ret = TRUE;
    if (DFLASH_INTOP_ENABLE == eOp)
    {
        DISABLE_ALL_INTERRUPTS();
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        
        ret &= Flash_Std_EnableDFlashEccBusErrorAlarm();
        ret &= Safewdt_Hal_SetSafetyEndinit();
        
        ENABLE_ALL_INTERRUPTS();
    }
    else
    {
        DISABLE_ALL_INTERRUPTS();
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        
        ret &= Flash_Std_DisableDFlashEccBusErrorAlarm();
        ret &= Safewdt_Hal_SetSafetyEndinit();
        
        ENABLE_ALL_INTERRUPTS();
    }
    return ret;
}

/* #Violation: dflash_hal_c_REF_4 */
boolean Flash_Hal_GetDFlashEccStatus(void)
{
    return Flash_Std_GetDFlashEccStatus();
}

/* #Violation: dflash_hal_c_REF_4 */
boolean Flash_Hal_ClearDFlashEccStatus(void)
{
    boolean ret;
    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();

    Flash_Std_ClearDFlashEccStatus();
    ret &= Safewdt_Hal_SetSafetyEndinit();
    
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

/* #Violation: dflash_hal_c_REF_1 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dflash_hal_c_REF_5 */
#include "Fls_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

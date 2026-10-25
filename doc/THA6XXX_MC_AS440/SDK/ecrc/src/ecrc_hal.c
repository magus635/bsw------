/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    ecrc_hal.c
 * Author:      01321
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of ECRC module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #ecrc_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access
*
* #ecrc_hal_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core. Boolean can only be representes as uint8.
*
* #ecrc_hal_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #ecrc_hal_c_REF_4:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured 
*                by code review.
*
* #ecrc_hal_c_REF_5:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #ecrc_hal_c_REF_6:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #ecrc_hal_c_REF_7:MISRAC2012-Rule-2.2; 
* Justification:Platform-based design with configurable macros.
* 
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "ecrc_hal.h"
#include "Platform_Types.h"
#include "ecrc_register.h"
#include "cpuwdt_hal.h"
#include "safewdt_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* The time out time waiting for result flag or reset flag */
#define ECRC_TIMEOUT_TIME (1024U)

/* Interrupt Mask */
#define ECRC_INTERRUPT_MASK (0x0FU)

/* Access pattern for Register */
#define ECRC_ACCESS_PATTERN (0xFACECAFEU)

/* Clear CRC status */
#define ECRC_STATUS_CLEAR (0x00U)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: ecrc_hal_c_REF_6 */
#define ECRC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ecrc_hal_c_REF_5 */
#include "Ecrc_MemMap.h"

/* #Violation: ecrc_hal_c_REF_1 */
boolean Ecrc_Hal_Init(const Ecrc_Cfg *const pEcrcConfig)
{
    /* #Violation: ecrc_hal_c_REF_4 */
    ECRC_CHCFG config;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pEcrcConfig));
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(pEcrcConfig->channelID < CHANNEL_MAX_NUM));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    /* #Violation: ecrc_hal_c_REF_3 */
    config.U = ECRC->CHR[pEcrcConfig->channelID].CHCFG.U;
    config.B.RELOAD = (uint32)pEcrcConfig->reload;
    config.B.BYTEREFIN = (uint32)pEcrcConfig->byteReflection;
    config.B.BITREFOUT = (uint32)pEcrcConfig->bitReflection;
    config.B.XOUT = (uint32)pEcrcConfig->xout;
    config.B.BYTESWAP = (uint32)pEcrcConfig->byteswap;

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* Set the configuration register */
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[pEcrcConfig->channelID].CHCFG.U = config.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, config.U, ECRC->CHR[pEcrcConfig->channelID].CHCFG.U);

    return ret;
}

/* #Violation: ecrc_hal_c_REF_1 */
boolean Ecrc_Hal_SetInterrupt(uint32 channelID, const uint32 interruptEnable)
{
    uint32  interruptSet;
    uint32  regValue;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(channelID < CHANNEL_MAX_NUM));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    interruptSet = (~(interruptEnable & ECRC_INTERRUPT_MASK)) & 0xFU; /* The corresponding enable bits are 0 */
    /* #Violation: ecrc_hal_c_REF_3 */
    regValue = ECRC->CHR[channelID].CHCFG.U & (~ECRC_INTERRUPT_MASK);

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* Enable or disable the corresponding interrupt: for this register 0-enable, 1-disable  */
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CHCFG.U = regValue|interruptSet;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, (regValue|interruptSet), ECRC->CHR[channelID].CHCFG.U);

    return ret;
}

/* #Violation: ecrc_hal_c_REF_1 */
uint32 Ecrc_Hal_GetInterrupt(uint32 channelID)
{
    uint32 interruptTypes;
    
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(channelID < CHANNEL_MAX_NUM));
#endif /* INPUT_ARG_DETECT */
    
    /* Get the channel number from which it send the interrupt */
    /* #Violation: ecrc_hal_c_REF_3 */
    interruptTypes = (ECRC->CHR[channelID].CSR.U & ECRC_INTERRUPT_MASK);
    return interruptTypes;
}

/* #Violation: ecrc_hal_c_REF_1 */
boolean Ecrc_Hal_ClearInterrupt(uint32 channelID, uint32 clearMask)
{
    uint32 mask;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(channelID < CHANNEL_MAX_NUM));
#endif /* INPUT_ARG_DETECT */

    mask = clearMask;
    ret = TRUE;
    mask = ~(mask & ECRC_INTERRUPT_MASK); /* The corresponding clear bits are 0 */

    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CSR.U  &= mask;  /* Clear the corresponding interrupt */

    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, 0U, (ECRC->CHR[channelID].CSR.U&(~mask)));

    return ret;
}

/* #Violation: ecrc_hal_c_REF_1 */
Ecrc_ErrorFlag Ecrc_Hal_Reset(void)
{
    Ecrc_ErrorFlag resetStatus;
    uint32 timeout;
    boolean ret;

    ret = TRUE;
    resetStatus = ECRC_NOT_OK;
    timeout = 0U;
    /* Reset ECRC module */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->MRSTR1.B.RST = 1U;
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->MRSTR0.B.RST = 1U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* Check if ECRC is already reset */
    /* #Violation: ecrc_hal_c_REF_3 */
    while((1U != ECRC->MRSTR0.B.RSTST) && (timeout < ECRC_TIMEOUT_TIME))
    {
        timeout++;
    }

    /* #Violation: ecrc_hal_c_REF_3 */
    if(1U == ECRC->MRSTR0.B.RSTST)
    {
        resetStatus = ECRC_OK;
    }
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->MRSTCLR.B.CLR = 1U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    if ((timeout >= ECRC_TIMEOUT_TIME) || (ret == FALSE))
    {
        resetStatus = ECRC_NOT_OK;
    }

    return resetStatus;
}

/* #Violation: ecrc_hal_c_REF_1 */
Ecrc_ErrorFlag Ecrc_Hal_CalculateCrcWithoutCheck(Ecrc_Cal *const pEcrcCal, uint32 channelID)
{
    uint32 loopCounter;
    Ecrc_ErrorFlag calculateStatus;
    boolean ret;

#if defined(THA6_THA6412) || defined(THA6_THA6104)
    uint32 timeout;
    timeout = 0U;
#endif

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pEcrcCal));
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(channelID < CHANNEL_MAX_NUM));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    /* #Violation: ecrc_hal_c_REF_7 */
    calculateStatus = ECRC_NOT_OK;
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CSR.U = ECRC_STATUS_CLEAR;    /* Clear CRC status flag */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CHCFG.B.KERNEL = (uint32)pEcrcCal->kernel;
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CHCFG.B.CHKEN = 0U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, 0U, ECRC->CHR[channelID].CSR.U);
    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, (uint32)pEcrcCal->kernel, ECRC->CHR[channelID].CHCFG.B.KERNEL);
    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, 0U, ECRC->CHR[channelID].CHCFG.B.CHKEN);


#if defined(THA6_THA6412) || defined(THA6_THA6104)
    /* Set Length of the data */
    /* If first call or reload length is disable, then set input data length */
    /* #Violation: ecrc_hal_c_REF_3 */
    if((TRUE == pEcrcCal->crcIsFirstCall) || (0U == ECRC->CHR[channelID].CHCFG.B.RELOAD))
    {
        /* Set the input data length */
        /* Write Access pattern first */
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].CHLEN.U = ECRC_ACCESS_PATTERN;
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].CHLEN.B.LEN = pEcrcCal->crcDataLength;
        /* #Violation: ecrc_hal_c_REF_3 */
        ret = Ecrc_Register_ReadBack_Check(ret, pEcrcCal->crcDataLength, ECRC->CHR[channelID].CHLEN.B.LEN);
    }
#endif

    /* Set Crc start value */
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CHCRC.B.CRC = pEcrcCal->crcStartValue;
    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, pEcrcCal->crcStartValue, ECRC->CHR[channelID].CHCRC.B.CRC);

    /* Push all data into input register */
    for(loopCounter=0; loopCounter < (pEcrcCal->crcDataLength); ++loopCounter)
    {
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].CHIN.B.INPUT = pEcrcCal->pData[loopCounter];
        /* #Violation: ecrc_hal_c_REF_3 */
        ret = Ecrc_Register_ReadBack_Check(ret, pEcrcCal->pData[loopCounter], ECRC->CHR[channelID].CHIN.B.INPUT);
    }

#if defined(THA6_THA6412) || defined(THA6_THA6104)
    /* #Violation: ecrc_hal_c_REF_3 */
    while((1U != ECRC->CHR[channelID].CSR.B.RESFLAG) && (timeout < ECRC_TIMEOUT_TIME))
    {
        timeout++;
    }

    if (timeout >= ECRC_TIMEOUT_TIME)
    {
        ret = FALSE;
    }

    /* #Violation: ecrc_hal_c_REF_3 */
    if(1U == ECRC->CHR[channelID].CSR.B.RESFLAG) /* ECRC result can be get */
    {
        /* #Violation: ecrc_hal_c_REF_3 */
        pEcrcCal->pResult = ECRC->CHR[channelID].CHRES.B.RESULT;
        calculateStatus = ECRC_OK;
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].CSR.U = 0x7FU;
        /* #Violation: ecrc_hal_c_REF_3 */
        ret = Ecrc_Register_ReadBack_Check(ret, 0U, ECRC->CHR[channelID].CSR.B.RESFLAG);
    }
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D)
    /* #Violation: ecrc_hal_c_REF_3 */
    pEcrcCal->pResult = ECRC->CHR[channelID].CHRES.B.RESULT;
    calculateStatus = ECRC_OK;
#endif

    if (FALSE == ret)
    {
        calculateStatus = ECRC_NOT_OK;
    }

    return calculateStatus;
}

/* #Violation: ecrc_hal_c_REF_1 */
Ecrc_ErrorFlag Ecrc_Hal_CalculateCrcWithCheck(Ecrc_Cal *const pEcrcCal, uint32 channelID, uint32 expectedCrc)
{
    uint32 timeout;
    uint32 loopCounter;
    Ecrc_ErrorFlag calculateStatus;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pEcrcCal));
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(channelID < CHANNEL_MAX_NUM));
#endif /* INPUT_ARG_DETECT */

    calculateStatus = ECRC_NOT_OK;
    timeout = 0U;
    ret = TRUE;

    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CSR.U = ECRC_STATUS_CLEAR;    /* Clear CRC status flag */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CHCFG.B.KERNEL = (uint32)pEcrcCal->kernel;
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CHCFG.B.CHKEN = 1U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, 0U, ECRC->CHR[channelID].CSR.U);
    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, (uint32)pEcrcCal->kernel, ECRC->CHR[channelID].CHCFG.B.KERNEL);
    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, 1U, ECRC->CHR[channelID].CHCFG.B.CHKEN);

    /* If first call or reload length is disable, then set input data length */
    /* #Violation: ecrc_hal_c_REF_3 */
    if((TRUE == pEcrcCal->crcIsFirstCall) || (0U == ECRC->CHR[channelID].CHCFG.B.RELOAD))
    {
        /* Set the input data length */
        /* Write Access pattern first */
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].CHLEN.U = ECRC_ACCESS_PATTERN;
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].CHLEN.B.LEN = pEcrcCal->crcDataLength;
        /* #Violation: ecrc_hal_c_REF_3 */
        ret = Ecrc_Register_ReadBack_Check(ret, pEcrcCal->crcDataLength, ECRC->CHR[channelID].CHLEN.B.LEN);
    }

    /* Set the expected CRC */
    /* Write Access pattern first */
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CHCHK.B.CHK = ECRC_ACCESS_PATTERN;
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CHCHK.B.CHK = expectedCrc;
    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, expectedCrc, ECRC->CHR[channelID].CHCHK.B.CHK);

    /* Set Crc start value */
    /* #Violation: ecrc_hal_c_REF_3 */
    ECRC->CHR[channelID].CHCRC.B.CRC = pEcrcCal->crcStartValue;
    /* #Violation: ecrc_hal_c_REF_3 */
    ret = Ecrc_Register_ReadBack_Check(ret, pEcrcCal->crcStartValue, ECRC->CHR[channelID].CHCRC.B.CRC);

    /* Push all data into input register */
    for(loopCounter=0; loopCounter < (pEcrcCal->crcDataLength); ++loopCounter)
    {
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].CHIN.B.INPUT = pEcrcCal->pData[loopCounter];
        /* #Violation: ecrc_hal_c_REF_3 */
        ret = Ecrc_Register_ReadBack_Check(ret, pEcrcCal->pData[loopCounter], ECRC->CHR[channelID].CHIN.B.INPUT);
    }

    /* #Violation: ecrc_hal_c_REF_3 */
    while((1U != ECRC->CHR[channelID].CSR.B.RESFLAG) && (timeout < ECRC_TIMEOUT_TIME))
    {
           timeout++;
    }

    if (timeout >= ECRC_TIMEOUT_TIME)
    {
        ret = FALSE;
    }

    /* #Violation: ecrc_hal_c_REF_3 */
    if(1U == ECRC->CHR[channelID].CSR.B.RESFLAG) /* ECRC result can be get */
    {
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].CSR.U = 0x7FU;
        /* #Violation: ecrc_hal_c_REF_3 */
        ret = Ecrc_Register_ReadBack_Check(ret, 0U, ECRC->CHR[channelID].CSR.B.RESFLAG);
        /* #Violation: ecrc_hal_c_REF_3 */
        calculateStatus = (1U == ECRC->CHR[channelID].CSR.B.CMST) ? (ECRC_NOT_OK) : (ECRC_OK);
        /* #Violation: ecrc_hal_c_REF_3 */
        pEcrcCal->pResult = ECRC->CHR[channelID].CHRES.B.RESULT;
    }

    if (FALSE == ret)
    {
        calculateStatus = ECRC_NOT_OK;
    }

    return calculateStatus;
}

/* #Violation: ecrc_hal_c_REF_1 */
Ecrc_AlarmStatus Ecrc_Hal_GetAlarmStatus(Ecrc_AlarmStatusFlag flagStatus, uint32 channelID)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(channelID < CHANNEL_MAX_NUM));
#endif /* INPUT_ARG_DETECT */
    Ecrc_AlarmStatus alarmStatus;
    /* Check the specific bit have a flag */
    /* #Violation: ecrc_hal_c_REF_3 */
    alarmStatus = (1U == ((ECRC->CHR[channelID].ALMSTR.U >> (uint32)flagStatus) & 1U)) ?
                  ECRC_ALARMSTATUS_SET : ECRC_ALARMSTATUS_RESET;
    return alarmStatus;
}

/* #Violation: ecrc_hal_c_REF_1 */
boolean Ecrc_Hal_ClearAlarmStatus(Ecrc_AlarmStatusFlag flagStatus, uint32 channelID)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: ecrc_hal_c_REF_2 */
    Assert((boolean)(channelID < CHANNEL_MAX_NUM));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit(); /* Unlock safe endinit protect */
    if((ECRC_ALARMSTATUSFLAG_SENCRE == flagStatus) || (ECRC_ALARMSTATUSFLAG_SENRE == flagStatus))
    {
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].ALMCLR.B.SENAC = 3U;
    }
    else if((ECRC_ALARMSTATUSFLAG_ECRE == flagStatus) || (ECRC_ALARMSTATUSFLAG_ESTRST == flagStatus)
            || (ECRC_ALARMSTATUSFLAG_ESTCFG == flagStatus))
    {
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].ALMCLR.B.EAC = 3U;
    }
    else if((ECRC_ALARMSTATUSFLAG_SECRE == flagStatus) || (ECRC_ALARMSTATUSFLAG_SEST == flagStatus))
    {
        /* #Violation: ecrc_hal_c_REF_3 */
        ECRC->CHR[channelID].ALMCLR.B.SEAC = 3U;
    }
    else
    {
        /* Do nothing*/
        ret = FALSE;
    }
    ret &= Safewdt_Hal_SetSafetyEndinit(); /* Lock safe endinit protect */
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

/* #Violation: ecrc_hal_c_REF_6 */
#define ECRC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: ecrc_hal_c_REF_5 */
#include "Ecrc_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

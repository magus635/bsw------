/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    safewdt_hal.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of SAFEWDT module.
 *********************************************************************************************************************/

/*
* #Violation Summary
*
* #safewdt_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #safewdt_hal_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #safewdt_hal_c_REF_3:MISRAC2012-Rule-8.7;
* Justification:This function may be used in other module.
*
* #safewdt_hal_c_REF_4:MISRAC2012-Rule-10.5;
* Justification:Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
* #safewdt_hal_c_REF_5:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #safewdt_hal_c_REF_6:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #safewdt_hal_c_REF_7:MISRAC2012-Rule-2.2; 
* Justification:Platform-based design with configurable macros.
*
* #safewdt_hal_c_REF_8:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
* #safewdt_hal_c_REF_9:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
* #safewdt_hal_c_REF_10:MISRAC2012-Rule-2.2;
* Justification:Value used in assembly code; Platform-based design with configurable macros.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "safewdt_hal.h"
#include "safewdt_std.h"
#include "safewdt_register.h"
#include "regtypes.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /*INPUT_ARG_DETECT*/
/**********************************************************************************************************************
 *                                             Private Macro Definitions
 *********************************************************************************************************************/
/* Logical operation mask,bit-fields[12:0] */
#define SAFEWDT_MASK_12_0             (0x1FFFU)
/* Logical operation mask,bit-fields[5:0] */
#define SAFEWDT_MASK_5_0              (0x3FU)
/* #Violation: safewdt_hal_c_REF_2 */
#define SAFEWDT_WDT_CNT_THV           (0x1FFFFU)
/* WDT fixed password */
/* #Violation: safewdt_hal_c_REF_2 */
#define SAFEWDT_PWWDT_FIXED_PASSWORD  (0xB40U)
/* SE fixed password */
#define SAFEWDT_PWSE_FIXED_PASSWORD   (0x2C00U)
/* WDT timeout value */
#define SAFEWDT_WDTCNTVAL_TIMEOUT_MAX (0x3200600UL)
/* SE timeout value */
#define SAFEWDT_SEOUTSTS_TIMEOUT_MAX  (0x1800600UL)
/* WDT delay factor */
#define SAFEWDT_WDT_DELAY             (6U)

/**********************************************************************************************************************
 *                                           Private Function Declarations
 *********************************************************************************************************************/
/* #Violation: safewdt_hal_c_REF_2 */
#define SAFEWDT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: safewdt_hal_c_REF_6 */
#include "Safewdt_MemMap.h"

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_CalculateDynamicPassword
 * Description:  Calculate current correct dynamic password
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        prePassword: Previous correct password
 *               password: Current correct password
 *               pwMode: Password dynamic generation mode selected during initialization
 * Inout:        None
 * Output:       None
 * Return:       uint16: Current correct dynamic password
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208      Create
 *********************************************************************************************************************/
static uint16 Safewdt_Hal_CalculateDynamicPassword(uint16 prePassword, Safewdt_PwMode pwMode);

/**********************************************************************************************************************
 *                                           Private Function Definitions
 *********************************************************************************************************************/
static uint16 Safewdt_Hal_CalculateDynamicPassword(uint16 prePassword, Safewdt_PwMode pwMode)
{
    uint16 password;

    /* If user-defined password generation mode is dynamic 1 */
    if(SAFEWDT_PWMODE_DYNAMIC_1 == pwMode)
    {
        /* Calculate the current correct password */
        password =
            ((prePassword & SAFEWDT_MASK_12_0) << 1U) | (((prePassword >> 13U) & 1U) ^ ((prePassword >> 12U) & 1U) ^ \
                                                         ((prePassword >> 11U) & 1U) ^ ((prePassword >> 2U) & 1U));
    }
    else /* The user-defined password generation mode is dynamic 2 */
    {
        /* Calculate the current correct password */
        password = prePassword ^ SAFEWDT_MASK_5_0;
    }

    return password;
}

/**********************************************************************************************************************
 *                                            Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: safewdt_hal_c_REF_1 */
boolean Safewdt_Hal_InitWdt(const Safewdt_WdtConfig *const pConfig)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: safewdt_hal_c_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: safewdt_hal_c_REF_4 */
    Assert((boolean)((pConfig->wdtHighThv0 <= SAFEWDT_WDT_CNT_THV)));
    /* #Violation: safewdt_hal_c_REF_4 */
    Assert((boolean)((pConfig->wdtHighThv1 <= SAFEWDT_WDT_CNT_THV)));
    /* #Violation: safewdt_hal_c_REF_4 */
    Assert((boolean)(pConfig->wdtHighThv0 > pConfig->wdtLowThv0));
    /* #Violation: safewdt_hal_c_REF_4 */
    Assert((boolean)(pConfig->wdtHighThv1 > pConfig->wdtLowThv1));
    /* #Violation: safewdt_hal_c_REF_4 */
    Assert((boolean)(SAFEWDT_SAFECPUID_NONE != pConfig->safeCpuId));
#endif

    ret = TRUE;
    /* Clear PW0 protection */
    ret &= Safewdt_Std_ClearPw0();

    if(SAFEWDT_PWMODE_FIXED == pConfig->pwWdtMode)
    {
        /* PWWDT permission password generation mode */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->PWMAI.B.WDTPWM = (uint32)pConfig->pwWdtMode;
    }
    else
    {
        /* PWWDT permission password initial value */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->PWMAI.B.WDTPWINIT = pConfig->pwWdtInit;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, pConfig->pwWdtInit, SAFEWDT_HAL->PWMAI.B.WDTPWINIT);

        /* PWWDT permission password generation mode */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->PWMAI.B.WDTPWM = (uint32)pConfig->pwWdtMode;
    }
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, (uint32)pConfig->pwWdtMode, SAFEWDT_HAL->PWMAI.B.WDTPWM);

    /* Safety core id */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SAFECPUID.U = (uint32)pConfig->safeCpuId;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, (uint32)pConfig->safeCpuId, SAFEWDT_HAL->SAFECPUID.U);

    /* WDT counter clock divisor coefficient */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->CLKMNG.B.WDTCLKDIV = (uint32)pConfig->wdtClkDiv;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, (uint32)pConfig->wdtClkDiv, SAFEWDT_HAL->CLKMNG.B.WDTCLKDIV);

    /* Error output mode of first dog feeding interval */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->OUTM.B.WDTOUTM1 = (uint32)pConfig->wdtFirOutMode;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, (uint32)pConfig->wdtFirOutMode, SAFEWDT_HAL->OUTM.B.WDTOUTM1);

    if(0U == pConfig->wdtLowThv0)
    {
        /* Normal mode */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLEN.B.WDTLEN0 = 0U;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, 0U, SAFEWDT_HAL->WDTLEN.B.WDTLEN0);

        /* Lower limit of first interval is 0 */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLTHV0.U = 0U;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, 0U, SAFEWDT_HAL->WDTLTHV0.U);
    }
    else
    {
        /* Windows mode */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLEN.B.WDTLEN0 = 1U;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, 1U, SAFEWDT_HAL->WDTLEN.B.WDTLEN0);

        /* Lower limit of first interval */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLTHV0.U = pConfig->wdtLowThv0;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, pConfig->wdtLowThv0, SAFEWDT_HAL->WDTLTHV0.U);
    }

    if(0U == pConfig->wdtLowThv1)
    {
        /* Normal mode */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLEN.B.WDTLEN1 = 0U;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, 0U, SAFEWDT_HAL->WDTLEN.B.WDTLEN1);

        /* Lower limit of second interval is 0 */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLTHV1.U = 0U;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, 0U, SAFEWDT_HAL->WDTLTHV1.U);
    }
    else
    {
        /* Windows mode */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLEN.B.WDTLEN1 = 1U;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, 1U, SAFEWDT_HAL->WDTLEN.B.WDTLEN1);

        /* Lower limit of second interval */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLTHV1.U = pConfig->wdtLowThv1;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, pConfig->wdtLowThv1, SAFEWDT_HAL->WDTLTHV1.U);
    }

    /* Upper limit of first interval */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->WDTHTHV0.U = pConfig->wdtHighThv0;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, pConfig->wdtHighThv0, SAFEWDT_HAL->WDTHTHV0.U);

    /* Upper limit of second interval */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->WDTHTHV1.U = pConfig->wdtHighThv1;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, pConfig->wdtHighThv1, SAFEWDT_HAL->WDTHTHV1.U);

    /* Set PW0 protection */
    ret &= Safewdt_Std_SetPw0();

    return ret;
}

/* #Violation: safewdt_hal_c_REF_1 */
boolean Safewdt_Hal_InitSafetyEndinit(const Safewdt_SafetyEndinitConfig *const pConfig)
{
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: safewdt_hal_c_REF_4 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: safewdt_hal_c_REF_4 */
    Assert((boolean)((pConfig->pwSeInit <= 0x3FFFU)));
#endif

    ret = TRUE;
    /* Clear PW0 protection */
    ret &= Safewdt_Std_ClearPw0();

    /* Safety core id */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SAFECPUID.U = (uint32)pConfig->safeCpuId;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, SAFEWDT_HAL->SAFECPUID.U, (uint32)pConfig->safeCpuId);

    if(SAFEWDT_PWMODE_FIXED == pConfig->pwSeMode)
    {
        /* PWSE permission password generation mode */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->PWMAI.B.SEPWM = (uint32)pConfig->pwSeMode;
    }
    else
    {
        /* PWSE permission password generation mode */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->PWMAI.B.SEPWM = (uint32)pConfig->pwSeMode;
        
        /* PWSE permission password initial value */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->PWMAI.B.SEPWINIT = pConfig->pwSeInit;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, SAFEWDT_HAL->PWMAI.B.SEPWINIT, pConfig->pwSeInit);
    }
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, SAFEWDT_HAL->PWMAI.B.SEPWM, (uint32)pConfig->pwSeMode);

    /* Clock divisor coefficient */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->CLKMNG.B.SECLKDIV = (uint32)pConfig->seClkDiv;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, SAFEWDT_HAL->CLKMNG.B.SECLKDIV, (uint32)pConfig->seClkDiv);

    /* Error output mode */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->OUTM.B.SEOUTM = (uint32)pConfig->seOutMode;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, SAFEWDT_HAL->OUTM.B.SEOUTM, (uint32)pConfig->seOutMode);
    /* SE counter threshold */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SETHV.U = pConfig->seThv;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, SAFEWDT_HAL->SETHV.U, pConfig->seThv);

    /* Set PW0 protection */
    ret &= Safewdt_Std_SetPw0();

    /* Enable the Safety ENDINIT function */
    ret &= Safewdt_Std_ClearPwse();
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SECNTEN.U = 3U;
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, SAFEWDT_HAL->SECNTEN.U, 3U);
    ret &= Safewdt_Std_SetPwse();

    return ret;
}

/* #Violation: safewdt_hal_c_REF_1 */
uint16 Safewdt_Hal_GetWdtPassword(void)
{
    Safewdt_PwMode wdtMode;
    uint16 prePassword;
    uint16 password;

    /* PWWDT permission password generation mode */
    /* #Violation: safewdt_hal_c_REF_4 */
    /* #Violation: safewdt_hal_c_REF_5 */
    wdtMode = (Safewdt_PwMode)SAFEWDT_HAL->PWMAI.B.WDTPWM;
    /* Acquire previous correct password */
    /* #Violation: safewdt_hal_c_REF_5 */
    prePassword = (uint16)SAFEWDT_HAL->WDTPW.U;

    if(SAFEWDT_PWMODE_FIXED == wdtMode)
    {
        /* Current correct password is fixed password  */
        password = SAFEWDT_PWWDT_FIXED_PASSWORD;
    }
    else /* The user-defined password generation mode is dynamic */
    {
        password = Safewdt_Hal_CalculateDynamicPassword(prePassword, wdtMode);
    }

    return password;
}

/* #Violation: safewdt_hal_c_REF_3 */
/* #Violation: safewdt_hal_c_REF_9 */
boolean Safewdt_Hal_EnableWdt(void)
{
    boolean ret;
    uint32  thv;
    uint32 clkDiv;
    uint32 index;
    volatile uint32 wdtFactors[4U] = {1U, 64U, 256U, 16384U};

    ret = TRUE;

    /* After enabling WDT, first execute the service WDT operation to ensure
     * that the counter is functioning properly. */
    /* #Violation: safewdt_hal_c_REF_5 */
    if (0U == SAFEWDT_HAL->WDTLEN.B.WDTLEN0)
    {
        ret &= Safewdt_Std_ClearPwwdt();
        /* Enable the NWDT function */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTCNTEN.U = 3U;

        /* Restart the NWDT counter */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTCNTC.U = 3U;
        ret &= Safewdt_Std_SetPwwdt();
    }
    else
    {
        /* #Violation: safewdt_hal_c_REF_5 */
        /* #Violation: safewdt_hal_c_REF_10 */
        index = SAFEWDT_HAL->CLKMNG.B.WDTCLKDIV;
        if (index < 4U)
        {
            /* #Violation: safewdt_hal_c_REF_10 */
            clkDiv = wdtFactors[index] * SAFEWDT_WDT_DELAY;
        }
        else
        {
            /* #Violation: safewdt_hal_c_REF_10 */
            clkDiv = 1U * SAFEWDT_WDT_DELAY;
        }

        /* #Violation: safewdt_hal_c_REF_5 */
        thv = SAFEWDT_HAL->WDTLTHV0.U;

        ret &= Safewdt_Std_ClearPw0();
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLTHV0.U = 0U;
        ret &= Safewdt_Std_SetPw0();

        ret &= Safewdt_Std_ClearPwwdt();
        /* Enable the WWDT function */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTCNTEN.U = 3U;

        /* Restart the WWDT counter */
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTCNTC.U = 3U;
        ret &= Safewdt_Std_SetPwwdt();

        /* Wait for counter restart */
        /* #Violation: safewdt_hal_c_REF_8 */
        ASM_VOLATILE(
            "1:               \n"
            " SUBS %0, %0, #1 \n"
            "NOP              \n"
        #ifdef __TASKING__
            " BNE 1p          \n"
        #else
            " BNE 1b          \n"
        #endif
            : "+r" (clkDiv)
            :
            : "cc"
                );

        ret &= Safewdt_Std_ClearPw0();
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->WDTLTHV0.U = thv;
        ret &= Safewdt_Std_SetPw0();
    }

    return ret;
}

/* #Violation: safewdt_hal_c_REF_1 */
boolean Safewdt_Hal_ServiceWdt(void)
{
    boolean ret;

    ret = TRUE;
    ret &= Safewdt_Std_ClearPwwdt();

    /* Restart the WDT counter */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->WDTCNTC.U = 3U;

    ret &= Safewdt_Std_SetPwwdt();

    return ret;
}

/* #Violation: safewdt_hal_c_REF_3 */
boolean Safewdt_Hal_DisableWdt(void)
{
    boolean ret;
    uint32 timeOutCnt;
    uint32 almMask1;
    uint32 almMask2;
    uint32 intMask;
    
    timeOutCnt = 0U;
    ret = TRUE;

    /* Mask alarm and interrupt */
    /* #Violation: safewdt_hal_c_REF_5 */
    almMask1 = SAFEWDT_HAL->SWMASK.B.WDTALM1MK;
    /* #Violation: safewdt_hal_c_REF_5 */
    almMask2 = SAFEWDT_HAL->SWMASK.B.WDTALM2MK;
    /* #Violation: safewdt_hal_c_REF_5 */
    intMask = SAFEWDT_HAL->SWINTMASK.B.WDTINT1MK;
    ret &= Safewdt_Std_ClearPw0();
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SWMASK.B.WDTALM1MK = 3U;
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SWMASK.B.WDTALM2MK = 3U;
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SWINTMASK.B.WDTINT1MK = 3U;
    ret &= Safewdt_Std_SetPw0();

    /* #Violation: safewdt_hal_c_REF_5 */
    ret &= Safewdt_Register_ReadBack_Check(ret, 3U, SAFEWDT_HAL->SWMASK.B.WDTALM1MK);
    /* #Violation: safewdt_hal_c_REF_5 */
    ret &= Safewdt_Register_ReadBack_Check(ret, 3U, SAFEWDT_HAL->SWMASK.B.WDTALM2MK);
    /* #Violation: safewdt_hal_c_REF_5 */
    ret &= Safewdt_Register_ReadBack_Check(ret, 3U, SAFEWDT_HAL->SWINTMASK.B.WDTINT1MK);    

    ret &= Safewdt_Std_ClearPwwdt();

    /* Stop the WDT counter */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->WDTCNTEN.U = 0U;

    ret &= Safewdt_Std_SetPwwdt();

    /* Wait the WDT count clear */
    /* #Violation: safewdt_hal_c_REF_5 */
    while((0U != SAFEWDT_HAL->WDTCNTVAL.U) && (timeOutCnt < SAFEWDT_WDTCNTVAL_TIMEOUT_MAX))
    {
        timeOutCnt++;
    }
    
    /* Unmask alarm and interrupt */
    ret &= Safewdt_Std_ClearPw0();
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SWMASK.B.WDTALM1MK = almMask1;
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SWMASK.B.WDTALM2MK = almMask2;
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SWINTMASK.B.WDTINT1MK = intMask;
    ret &= Safewdt_Std_SetPw0();

    /* #Violation: safewdt_hal_c_REF_5 */
    ret &= Safewdt_Register_ReadBack_Check(ret, almMask1, SAFEWDT_HAL->SWMASK.B.WDTALM1MK);
    /* #Violation: safewdt_hal_c_REF_5 */
    ret &= Safewdt_Register_ReadBack_Check(ret, almMask2, SAFEWDT_HAL->SWMASK.B.WDTALM2MK);
    /* #Violation: safewdt_hal_c_REF_5 */
    ret &= Safewdt_Register_ReadBack_Check(ret, intMask, SAFEWDT_HAL->SWINTMASK.B.WDTINT1MK); 

    if (timeOutCnt >= SAFEWDT_WDTCNTVAL_TIMEOUT_MAX)
    {
        ret = FALSE;
    }
    
    return ret;
}

/* #Violation: safewdt_hal_c_REF_1 */
boolean Safewdt_Hal_ChangeHighThv(uint32 newHighThv0, uint32 newHighThv1)
{
    boolean ret;
#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: safewdt_hal_c_REF_4 */
    /* #Violation: safewdt_hal_c_REF_5 */
    Assert((boolean)(newHighThv0 > SAFEWDT_HAL->WDTLTHV0.U));
    /* #Violation: safewdt_hal_c_REF_4 */
    /* #Violation: safewdt_hal_c_REF_5 */
    Assert((boolean)(newHighThv1 > SAFEWDT_HAL->WDTLTHV1.U));
    /* #Violation: safewdt_hal_c_REF_4 */
    /* #Violation: safewdt_hal_c_REF_5 */
    Assert((boolean)(newHighThv0 <= SAFEWDT_WDT_CNT_THV));
    /* #Violation: safewdt_hal_c_REF_4 */
    /* #Violation: safewdt_hal_c_REF_5 */
    Assert((boolean)(newHighThv1 <= SAFEWDT_WDT_CNT_THV));
#endif

    ret = TRUE;
    /* Disable the WDT function */
    /* #Violation: safewdt_hal_c_REF_7 */
    ret &= Safewdt_Hal_DisableWdt();

    ret &= Safewdt_Std_ClearPw0();

    /* Upper limit of first interval */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->WDTHTHV0.U = newHighThv0;

    /* Upper limit of second interval */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->WDTHTHV1.U = newHighThv1;

    ret &= Safewdt_Std_SetPw0();

    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, newHighThv0, SAFEWDT_HAL->WDTHTHV0.U);
    /* #Violation: safewdt_hal_c_REF_5 */
    ret = Safewdt_Register_ReadBack_Check(ret, newHighThv1, SAFEWDT_HAL->WDTHTHV1.U);

    /* Enable the WDT function */
    ret &= Safewdt_Hal_EnableWdt();

    return ret;
}

/* #Violation: safewdt_hal_c_REF_1 */
Safewdt_Status Safewdt_Hal_GetAlarmFlagStatus(Safewdt_AlarmStatusFlag flag)
{
    Safewdt_Status status;

    /* Acquire the corresponding flag status,check if the status is reset */
    /* #Violation: safewdt_hal_c_REF_5 */
    if(0U == (SAFEWDT_HAL->SWALMSTS.U & (uint32)flag))
    {
        status = SAFEWDT_STATUS_RESET;
    }
    else /* The status is set */
    {
        status = SAFEWDT_STATUS_SET;
    }

    return status;
}

/* #Violation: safewdt_hal_c_REF_1 */
Safewdt_Status Safewdt_Hal_GetInterruptFlagStatus(Safewdt_InterruptStatusFlag flag)
{
    Safewdt_Status status;

    /* Acquire the corresponding flag status,check if the status is reset */
    /* #Violation: safewdt_hal_c_REF_5 */
    if(0U == (SAFEWDT_HAL->SWINTSTS.U & (uint32)flag))
    {
        status = SAFEWDT_STATUS_RESET;
    }
    else /* The status is set */
    {
        status = SAFEWDT_STATUS_SET;
    }

    return status;
}

/* #Violation: safewdt_hal_c_REF_1 */
Safewdt_Status Safewdt_Hal_GetPwAndLpFlagStatus(Safewdt_PwAndLpStatusFlag flag)
{
    Safewdt_Status status;

    /* Acquire the corresponding flag status,check if the status is reset */
    /* #Violation: safewdt_hal_c_REF_5 */
    if(0U == (SAFEWDT_HAL->SWSTS.U & (uint32)flag))
    {
        status = SAFEWDT_STATUS_RESET;
    }
    else /* The status is set */
    {
        status = SAFEWDT_STATUS_SET;
    }

    return status;
}

/* #Violation: safewdt_hal_c_REF_1 */
boolean Safewdt_Hal_ClearFlagStatus(Safewdt_ClearStatusFlag flag)
{
    boolean ret;

    ret = TRUE;
    ret &= Safewdt_Std_ClearPw0();

    /* Clear the flag status */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SAFEWDTCL.U = (uint32)flag;

    ret &= Safewdt_Std_SetPw0();

    return ret;
}

/* #Violation: safewdt_hal_c_REF_1 */
uint16 Safewdt_Hal_GetSePassword(void)
{
    Safewdt_PwMode seMode;
    uint16 prePassword;
    uint16 password;

    /*PWWDT permission password generation mode */
    /* #Violation: safewdt_hal_c_REF_4 */
    /* #Violation: safewdt_hal_c_REF_5 */
    seMode = (Safewdt_PwMode)SAFEWDT_HAL->PWMAI.B.SEPWM;
    /* Acquire previous correct password */
    /* #Violation: safewdt_hal_c_REF_5 */
    prePassword = (uint16)SAFEWDT_HAL->SEPW.U;

    if(SAFEWDT_PWMODE_FIXED == seMode)
    {
        /* Current correct password is fixed password */
        password = SAFEWDT_PWSE_FIXED_PASSWORD;
    }
    else /* The user-defined password generation mode is dynamic */
    {
        password = Safewdt_Hal_CalculateDynamicPassword(prePassword, seMode);
    }

    return password;
}

boolean Safewdt_Hal_ClearSafetyEndinit(void)
{
    /******************************************************
     * Usage Restrictions
     * - Before using this API, it is necessary to enter 
     *   the critical section for protection.
     *******************************************************/
    uint32 timeOutCnt;
    boolean ret;
    
    ret = TRUE;
    timeOutCnt = 0U;
    ret &= Safewdt_Std_ClearPwse();

    /* Enable the Safety ENDINIT function */
    /* #Violation: safewdt_hal_c_REF_5 */
    if (3U != SAFEWDT_HAL->SECNTEN.U)
    {
        /* #Violation: safewdt_hal_c_REF_5 */
        SAFEWDT_HAL->SECNTEN.U = 3U;
        /* #Violation: safewdt_hal_c_REF_5 */
        ret = Safewdt_Register_ReadBack_Check(ret, SAFEWDT_HAL->SECNTEN.U, 3U);
    }

    /* Start the SE counter */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SECNTC.B.SESTART = 3U;

    ret &= Safewdt_Std_SetPwse();

    /* #Violation: safewdt_hal_c_REF_5 */
    while((1U == SAFEWDT_HAL->SESTS.B.SEOUTSTS) && (timeOutCnt < SAFEWDT_SEOUTSTS_TIMEOUT_MAX))
    {
        timeOutCnt++;
    }
    
    if (timeOutCnt >= SAFEWDT_SEOUTSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

boolean Safewdt_Hal_SetSafetyEndinit(void)
{
    /******************************************************
     * Usage Restrictions
     * - Before using this API, it is necessary to enter 
     *   the critical section for protection.
     *******************************************************/
    uint32  timeOutCnt;
    boolean ret;

    ret = TRUE;
    timeOutCnt = 0U;
    ret &= Safewdt_Std_ClearPwse();

    /* Disable the Safety ENDINIT function */
    /* #Violation: safewdt_hal_c_REF_5 */
    SAFEWDT_HAL->SECNTC.B.SESTOP = 3U;

    ret &= Safewdt_Std_SetPwse();

    /* #Violation: safewdt_hal_c_REF_5 */
    while((0U == SAFEWDT_HAL->SESTS.B.SEOUTSTS) && (timeOutCnt < SAFEWDT_SEOUTSTS_TIMEOUT_MAX))
    {
        timeOutCnt++;
    }
    
    if (timeOutCnt >= SAFEWDT_SEOUTSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

/* #Violation: safewdt_hal_c_REF_2 */
#define SAFEWDT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: safewdt_hal_c_REF_6 */
#include "Safewdt_MemMap.h"
/**********************************************************************************************************************
 *                                                    End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    cpuwdt_hal.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of CPUWDT module.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #cpuwdt_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:reason 1503 Reserved API for user access
*
* #cpuwdt_hal_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:reason 1534 The macros are reserved for upper layers
*
* #cpuwdt_hal_c_REF_3:MISRAC2012-Rule-8.7;
* Justification:reason 1505 This function may be used in other module.
*
* #cpuwdt_hal_c_REF_4:MISRAC2012-Rule-10.5;
* Justification:reason 4342 Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
* #cpuwdt_hal_c_REF_5:MISRAC2012-Rule-11.4;
* Justification:reason 0303 Converting integers to object pointers to reduce register access complexity.
*
* #cpuwdt_hal_c_REF_6:MISRAC2012-Rule-10.5;
* Justification:reason 4304 Limitation of Cortex-R52+ Core; Boolean can only be represents as uint8;
* 
* *#cpuwdt_hal_c_REF_7:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #cpuwdt_hal_c_REF_8:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #cpuwdt_hal_c_REF_9:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #cpuwdt_hal_c_REF_10:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #cpuwdt_hal_c_REF_11:MISRAC2012-Rule-2.2; 
* Justification:Platform-based design with configurable macros.
*
* #cpuwdt_hal_c_REF_12:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
* #cpuwdt_hal_c_REF_13:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
* #cpuwdt_hal_c_REF_14:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
* #cpuwdt_hal_c_REF_15:MISRAC2012-Rule-2.2;
* Justification:Value used in assembly code; Platform-based design with configurable macros.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "multicore.h"
#include "Platform_Types.h"
#include "cpuwdt_hal.h"
#include "cpuwdt_std.h"
#include "cpuwdt_register.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /*INPUT_ARG_DETECT*/
/**********************************************************************************************************************
 *                                             Private Macro Definitions
 *********************************************************************************************************************/
/* Logical operation mask,bit-fields[12:0] */
#define CPUWDT_MASK_12_0             (0x1FFFU)
/* Logical operation mask,bit-fields[5:0] */
#define CPUWDT_MASK_5_0              (0x3FU)
/* #Violation: cpuwdt_hal_c_REF_2 */
#define CPUWDT_WDT_CNT_THV           (0x1FFFFU)
/* WDT fixed password */
#define CPUWDT_PWWDT_FIXED_PASSWORD  (0xA30U)
/* CE fixed password */
#define CPUWDT_PWCE_FIXED_PASSWORD   (0x3A00U)
/* WDT timeout value */
#define CPUWDT_WDTCNTSTS_TIMEOUT_MAX (0x3200600UL)
/* CE timeout value */
#define CPUWDT_CEOUTSTS_TIMEOUT_MAX  (0x1800600UL)
/* WDT delay factor */
#define CPUWDT_WDT_DELAY             (6U)

/**********************************************************************************************************************
 *                                           Private Function Declarations
 *********************************************************************************************************************/
/* #Violation: cpuwdt_hal_c_REF_10 */
#define CPUWDT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpuwdt_hal_c_REF_9 */
#include "Cpuwdt_MemMap.h"

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_CalculateDynamicPassword
 * Description:  Calculate current correct dynamic password
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        prePassword: Previous correct password
 *                  pwMode: Password dynamic generation mode selected during initialization.
 * Inout:        None
 * Output:       None
 * Return:       uint16: Current correct dynamic password
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
static uint16 Cpuwdt_Hal_CalculateDynamicPassword(uint16 prePassword, Cpuwdt_PwMode pwMode);

/**********************************************************************************************************************
 *                                           Private Function Definitions
 *********************************************************************************************************************/
static uint16 Cpuwdt_Hal_CalculateDynamicPassword(uint16 prePassword, Cpuwdt_PwMode pwMode)
{
    uint16 password;

    /* If user-defined password generation mode is dynamic 1 */
    if(CPUWDT_PWMODE_DYNAMIC_1 == pwMode)
    {
        /* Calculate the current correct password */
        password =
            ((prePassword & CPUWDT_MASK_12_0) << 1U) | (((prePassword >> 13U) & 1U) ^ ((prePassword >> 12U) & 1U) ^
                                                        ((prePassword >> 11U) & 1U) ^ ((prePassword >> 2U) & 1U));
    }
    else /* The user-defined password generation mode is dynamic 2 */
    {
        /* Calculate the current correct password */
        password = prePassword ^ CPUWDT_MASK_5_0;
    }

    return password;
}

/**********************************************************************************************************************
 *                                            Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: cpuwdt_hal_c_REF_1 */
boolean Cpuwdt_Hal_InitWdt(const Cpuwdt_WdtConfig* const pConfig)
{
    boolean ret;
    MultiCoreID coreId;
    CPUWDT_MODULE *cpuwdt;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(pConfig->wdtHighThv0 <= CPUWDT_WDT_CNT_THV));
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(pConfig->wdtHighThv1 <= CPUWDT_WDT_CNT_THV));
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(pConfig->wdtHighThv0 > pConfig->wdtLowThv0));
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(pConfig->wdtHighThv1 > pConfig->wdtLowThv1));
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(pConfig->pwWdtInit <= 0x3FFFU));
#endif /* INPUT_ARG_DETECT */
    
    ret = TRUE;

    coreId = Multicore_GetCoreID();

    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    /* Clear PW0 protection */
    ret &= Cpuwdt_Std_ClearPw0(coreId);

    if(CPUWDT_PWMODE_FIXED == pConfig->pwWdtMode)
    {
        /* PWWDT permission password generation mode */
        cpuwdt->PWMAI.B.WDTPWM = (uint32)pConfig->pwWdtMode;
    }
    else
    {
        /* PWWDT permission password generation mode */
        cpuwdt->PWMAI.B.WDTPWM = (uint32)pConfig->pwWdtMode;
        /* PWWDT permission password initial value */
        cpuwdt->PWMAI.B.WDTPWINIT = pConfig->pwWdtInit;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, pConfig->pwWdtInit, cpuwdt->PWMAI.B.WDTPWINIT);
    }
    ret &= Cpuwdt_Register_ReadBack_Check(ret, (uint32)pConfig->pwWdtMode, cpuwdt->PWMAI.B.WDTPWM);

    /* WDT counter clock divisor coefficient */
    cpuwdt->CLKMNG.B.WDTCKDIV = (uint32)pConfig->wdtClkDiv;
    ret &= Cpuwdt_Register_ReadBack_Check(ret, (uint32)pConfig->wdtClkDiv, cpuwdt->CLKMNG.B.WDTCKDIV);
    /* Error output mode of first dog feeding interval */
    cpuwdt->OUTM.B.WDTOUTM1 = (uint32)pConfig->wdtFirOutMode;
    ret &= Cpuwdt_Register_ReadBack_Check(ret, (uint32)pConfig->wdtFirOutMode, cpuwdt->OUTM.B.WDTOUTM1);

    if(0U == pConfig->wdtLowThv0)
    {
        /* Normal mode */
        cpuwdt->WDTLEN.B.WDTLEN0 = 0U;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, 0U, cpuwdt->WDTLEN.B.WDTLEN0);
        /* Lower limit of first interval is 0 */
        cpuwdt->WDTLTHV0.U = 0U;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, 0U, cpuwdt->WDTLTHV0.U);
    }
    else
    {
        /* Windows mode */
        cpuwdt->WDTLEN.B.WDTLEN0 = 1U;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, 1U, cpuwdt->WDTLEN.B.WDTLEN0);
        /* Llower limit of first interval */
        cpuwdt->WDTLTHV0.U = pConfig->wdtLowThv0;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, pConfig->wdtLowThv0, cpuwdt->WDTLTHV0.U);
    }

    if(0U == pConfig->wdtLowThv1)
    {
        /* Normal mode */
        cpuwdt->WDTLEN.B.WDTLEN1 = 0U;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, 0U, cpuwdt->WDTLEN.B.WDTLEN1);
        /* Lower limit of second interval is 0 */
        cpuwdt->WDTLTHV1.U = 0U;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, 0U, cpuwdt->WDTLTHV1.U);
    }
    else
    {
        /* Windows mode */
        cpuwdt->WDTLEN.B.WDTLEN1 = 1U;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, 1U, cpuwdt->WDTLEN.B.WDTLEN1);
        /* Lower limit of second interval */
        cpuwdt->WDTLTHV1.U = pConfig->wdtLowThv1;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, pConfig->wdtLowThv1, cpuwdt->WDTLTHV1.U);
    }

    /* Upper limit of first interval */
    cpuwdt->WDTHTHV0.U = pConfig->wdtHighThv0;
    ret &= Cpuwdt_Register_ReadBack_Check(ret, pConfig->wdtHighThv0, cpuwdt->WDTHTHV0.U);
    /* Upper limit of second interval */
    cpuwdt->WDTHTHV1.U = pConfig->wdtHighThv1;
    ret &= Cpuwdt_Register_ReadBack_Check(ret, pConfig->wdtHighThv1, cpuwdt->WDTHTHV1.U);

    /* Set PW0 protection */
    ret &= Cpuwdt_Std_SetPw0(coreId);
    return ret;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
boolean Cpuwdt_Hal_InitEndinit(const Cpuwdt_EndinitConfig *const pConfig)
{
    boolean ret;
    MultiCoreID coreId;
    CPUWDT_MODULE *cpuwdt;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(pConfig->pwCeInit <= 0x3FFFU));
#endif /*INPUT_ARG_DETECT*/

    ret = TRUE;
    coreId = Multicore_GetCoreID();

    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    /*Clear PW0 protection*/
    ret &= Cpuwdt_Std_ClearPw0(coreId);

    if(CPUWDT_PWMODE_FIXED == pConfig->pwCeMode)
    {
        /* PWCE permission password generation mode */
        cpuwdt->PWMAI.B.CEPWM = (uint32)pConfig->pwCeMode;
    }
    else
    {
        /* PWCE permission password generation mode */
        cpuwdt->PWMAI.B.CEPWM = (uint32)pConfig->pwCeMode;
        /* PWCE permission password initial value */
        cpuwdt->PWMAI.B.CEPWINIT = pConfig->pwCeInit;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, pConfig->pwCeInit, cpuwdt->PWMAI.B.CEPWINIT);
    }
    ret &= Cpuwdt_Register_ReadBack_Check(ret, (uint32)pConfig->pwCeMode, cpuwdt->PWMAI.B.CEPWM);

    /* CE counter clock divisor coefficient */
    cpuwdt->CLKMNG.B.CECKDIV = (uint32)pConfig->ceClkDiv;
    ret &= Cpuwdt_Register_ReadBack_Check(ret, (uint32)pConfig->ceClkDiv, cpuwdt->CLKMNG.B.CECKDIV);
    /* Error output mode */
    cpuwdt->OUTM.B.CEOUTM = (uint32)pConfig->ceOutMode;
    ret &= Cpuwdt_Register_ReadBack_Check(ret, (uint32)pConfig->ceOutMode, cpuwdt->OUTM.B.CEOUTM);
    /* CE counter threshold */
    cpuwdt->CETHV.U = pConfig->ceThv;
    ret &= Cpuwdt_Register_ReadBack_Check(ret, pConfig->ceThv, cpuwdt->CETHV.U);

    /*Set PW0 protection*/
    ret &= Cpuwdt_Std_SetPw0(coreId);

    /* Enable the ENDINIT function */
    ret &= Cpuwdt_Std_ClearPwce(coreId);
    cpuwdt->CECNTEN.U = 3U;
    ret &= Cpuwdt_Register_ReadBack_Check(ret, 3U, cpuwdt->CECNTEN.U);
    ret &= Cpuwdt_Std_SetPwce(coreId);

    return ret;
}
/* #Violation: cpuwdt_hal_c_REF_1 */
uint16 Cpuwdt_Hal_GetWdtPassword(void)
{
    MultiCoreID coreId;
    CPUWDT_MODULE const volatile *cpuwdt;
    Cpuwdt_PwMode wdtMode;
    uint16 prePassword;
    uint16 password;

    coreId = Multicore_GetCoreID();
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    /* PWWDT permission password generation mode */
    /* #Violation: cpuwdt_hal_c_REF_4 */
    wdtMode = (Cpuwdt_PwMode)cpuwdt->PWMAI.B.WDTPWM;

    /* Previous correct password */
    prePassword = (uint16)cpuwdt->WDTPW.U;

    if(CPUWDT_PWMODE_FIXED == wdtMode)
    {
        /* Fixed password */
        password = CPUWDT_PWWDT_FIXED_PASSWORD;
    }
    else
    {
        /* Dynamic password */
        password = Cpuwdt_Hal_CalculateDynamicPassword(prePassword, wdtMode);
    }

    return password;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
/* #Violation: cpuwdt_hal_c_REF_3 */
/* #Violation: cpuwdt_hal_c_REF_14 */
boolean Cpuwdt_Hal_EnableWdt(void)
{
    boolean ret;
    MultiCoreID coreId;
    CPUWDT_MODULE *cpuwdt;
    uint32 thv;
    uint32 clkDiv;
    uint32 index;
    volatile uint32 wdtFactors[4U] = {1U, 64U, 256U, 16384U};

    ret = TRUE;
    coreId = Multicore_GetCoreID();

    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);


    /* After enabling WDT, first execute the service WDT operation to ensure
     * that the counter is functioning properly. */
    if (0U == cpuwdt->WDTLEN.B.WDTLEN0)
    {
        ret &= Cpuwdt_Std_ClearPwwdt(coreId);
        /* Enable the NWDT function */
        cpuwdt->WDTCNTEN.U = 3U;

        /* Restart the NWDT counter */
        cpuwdt->WDTCNTC.U = 3U;
        ret &= Cpuwdt_Std_SetPwwdt(coreId);
    }
    else
    {
        /* #Violation: cpuwdt_hal_c_REF_15 */
        index = cpuwdt->CLKMNG.B.WDTCKDIV;
        if (index < 4U)
        {
            /* #Violation: cpuwdt_hal_c_REF_15 */
            clkDiv = wdtFactors[index] * CPUWDT_WDT_DELAY;
        }
        else
        {
            /* #Violation: cpuwdt_hal_c_REF_15 */
            clkDiv = 1U * CPUWDT_WDT_DELAY;
        }

        thv = cpuwdt->WDTLTHV0.U;

        ret &= Cpuwdt_Std_ClearPw0(coreId);
        cpuwdt->WDTLTHV0.U = 0U;
        ret &= Cpuwdt_Std_SetPw0(coreId);

        ret &= Cpuwdt_Std_ClearPwwdt(coreId);
        /* Enable the WWDT function */
        cpuwdt->WDTCNTEN.U = 3U;

        /* Restart the WWDT counter */
        cpuwdt->WDTCNTC.U = 3U;
        ret &= Cpuwdt_Std_SetPwwdt(coreId);

        /* Wait for counter restart */
        /* #Violation: cpuwdt_hal_c_REF_13 */
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

        ret &= Cpuwdt_Std_ClearPw0(coreId);
        cpuwdt->WDTLTHV0.U = thv;
        ret &= Cpuwdt_Std_SetPw0(coreId);
    }

    return ret;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
boolean Cpuwdt_Hal_ServiceWdt(void)
{
    boolean ret;
    MultiCoreID coreId;
    CPUWDT_MODULE *cpuwdt;

    ret = TRUE;

    coreId = Multicore_GetCoreID();
    
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    ret &= Cpuwdt_Std_ClearPwwdt(coreId);

    /* Restart the WDT counter */
    cpuwdt->WDTCNTC.U = 3U;

    ret &= Cpuwdt_Std_SetPwwdt(coreId);

    return ret;
}

/* THA6206 does not support the use of this API. Calling this API will return 0xFFFFFFFF. */
/* #Violation: cpuwdt_hal_c_REF_1 */
uint32 Cpuwdt_Hal_GetWdgCounter(void)
{
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    MultiCoreID coreId;
    CPUWDT_MODULE const *cpuwdt;
#endif
    uint32 cnt;

#if defined(THA6_THA6206) || defined(THA6_THA6206D)
    cnt = 0xFFFFFFFFU;
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6104)
    coreId = Multicore_GetCoreID();
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    cnt = cpuwdt->WDTCNTSTS.U;
#endif

    return cnt;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
/* #Violation: cpuwdt_hal_c_REF_3 */
boolean Cpuwdt_Hal_DisableWdt(void)
{
    boolean ret;
    MultiCoreID coreId;
    CPUWDT_MODULE *cpuwdt;
    uint32 timeOutCnt;
    uint32 almMask1;
    uint32 almMask2;
    uint32 intMask;
    
    timeOutCnt = 0U;
    ret = TRUE;
    coreId = Multicore_GetCoreID();
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    /* Mask alarm and interrupt */
    almMask1 = cpuwdt->CWMASK.B.WDTALM1MK;
    almMask2 = cpuwdt->CWMASK.B.WDTALM2MK;
    intMask = cpuwdt->CWINTMASK.B.WDTINT1MK;
    ret &= Cpuwdt_Std_ClearPw0(coreId);
    cpuwdt->CWMASK.B.WDTALM1MK = 3U;
    cpuwdt->CWMASK.B.WDTALM2MK = 3U;
    cpuwdt->CWINTMASK.B.WDTINT1MK = 3U;
    ret &= Cpuwdt_Std_SetPw0(coreId);

    ret &= Cpuwdt_Register_ReadBack_Check(ret, 3U, cpuwdt->CWMASK.B.WDTALM1MK);
    ret &= Cpuwdt_Register_ReadBack_Check(ret, 3U, cpuwdt->CWMASK.B.WDTALM2MK);
    ret &= Cpuwdt_Register_ReadBack_Check(ret, 3U, cpuwdt->CWINTMASK.B.WDTINT1MK);

    ret &= Cpuwdt_Std_ClearPwwdt(coreId);

    /* Disable the WDT function */
    cpuwdt->WDTCNTEN.U = 0U;

    ret &= Cpuwdt_Std_SetPwwdt(coreId);

    /* Wait the WDT count clear */
    while((0U != cpuwdt->WDTCNTSTS.U) && (timeOutCnt < CPUWDT_WDTCNTSTS_TIMEOUT_MAX))
    {
        timeOutCnt++;
    }

    /* Unmask alarm and interrupt */
    ret &= Cpuwdt_Std_ClearPw0(coreId);
    cpuwdt->CWMASK.B.WDTALM1MK = almMask1;
    cpuwdt->CWMASK.B.WDTALM2MK = almMask2;
    cpuwdt->CWINTMASK.B.WDTINT1MK = intMask;
    ret &= Cpuwdt_Std_SetPw0(coreId);

    ret &= Cpuwdt_Register_ReadBack_Check(ret, almMask1, cpuwdt->CWMASK.B.WDTALM1MK);
    ret &= Cpuwdt_Register_ReadBack_Check(ret, almMask2, cpuwdt->CWMASK.B.WDTALM2MK);
    ret &= Cpuwdt_Register_ReadBack_Check(ret, intMask, cpuwdt->CWINTMASK.B.WDTINT1MK);

    if (timeOutCnt >= CPUWDT_WDTCNTSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
boolean Cpuwdt_Hal_ChangeHighThv(uint32 newHighThv0, uint32 newHighThv1)
{
    boolean ret;
    MultiCoreID coreId;
    CPUWDT_MODULE *cpuwdt;

    ret = TRUE;

    coreId = Multicore_GetCoreID();

    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(newHighThv0 > cpuwdt->WDTLTHV0.U));
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(newHighThv1 > cpuwdt->WDTLTHV1.U));
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(newHighThv0 <= CPUWDT_WDT_CNT_THV));
    /* #Violation: cpuwdt_hal_c_REF_6 */
    Assert((boolean)(newHighThv1 <= CPUWDT_WDT_CNT_THV));
#endif /* INPUT_ARG_DETECT */

    /* Disable the WDT function */
    /* #Violation: cpuwdt_hal_c_REF_11 */
    ret &= Cpuwdt_Hal_DisableWdt();

    ret &= Cpuwdt_Std_ClearPw0(coreId);

    /* Upper limit of first interval */
    cpuwdt->WDTHTHV0.U = newHighThv0;

    /* Upper limit of second interval */
    cpuwdt->WDTHTHV1.U = newHighThv1;

    ret &= Cpuwdt_Std_SetPw0(coreId);

    ret &= Cpuwdt_Register_ReadBack_Check(ret, newHighThv0, cpuwdt->WDTHTHV0.U);
    ret &= Cpuwdt_Register_ReadBack_Check(ret, newHighThv1, cpuwdt->WDTHTHV1.U);

    /* Enable the WDT function */
    ret &= Cpuwdt_Hal_EnableWdt();

    return ret;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
Cpuwdt_Status Cpuwdt_Hal_GetAlarmFlagStatus(Cpuwdt_AlarmStatusFlag flag)
{
    MultiCoreID coreId;
    const CPUWDT_MODULE* cpuwdt;
    Cpuwdt_Status status;

    coreId = Multicore_GetCoreID();
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    /* Acquire the corresponding flag status,check if the status is reset */
    if(0U == (cpuwdt->CWALMSTS.U & (uint32)flag))
    {
        status = CPUWDT_STATUS_RESET;
    }
    else /* The status is set */
    {
        status = CPUWDT_STATUS_SET;
    }

    return status;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
Cpuwdt_Status Cpuwdt_Hal_GetInterruptFlagStatus(Cpuwdt_InterruptStatusFlag flag)
{
    MultiCoreID coreId;
    const CPUWDT_MODULE* cpuwdt;
    Cpuwdt_Status status;

    coreId = Multicore_GetCoreID();
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    /* Acquire the corresponding flag status,check if the status is reset */
    if(0U == (cpuwdt->CWINTSTS.U & (uint32)flag))
    {
        status = CPUWDT_STATUS_RESET;
    }
    else /* The status is set */
    {
        status = CPUWDT_STATUS_SET;
    }

    return status;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
Cpuwdt_Status Cpuwdt_Hal_GetPwAndLpFlagStatus(Cpuwdt_PwAndLpStatusFlag flag)
{
    MultiCoreID coreId;
    const CPUWDT_MODULE* cpuwdt;
    Cpuwdt_Status status;

    coreId = Multicore_GetCoreID();
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    /* Acquire the corresponding flag status,check if the status is reset */
    if(0U == (cpuwdt->CWSTS.U & (uint32)flag))
    {
        status = CPUWDT_STATUS_RESET;
    }
    else /* The status is set */
    {
        status = CPUWDT_STATUS_SET;
    }

    return status;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
boolean Cpuwdt_Hal_ClearFlagStatus(Cpuwdt_ClearStatusFlag flag)
{
    boolean ret;
    MultiCoreID coreId;
    CPUWDT_MODULE *cpuwdt;

    ret = TRUE;

    coreId = Multicore_GetCoreID();

    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    ret &= Cpuwdt_Std_ClearPw0(coreId);

    /* Clear the flag status */
    cpuwdt->CPUWDTCL.U = (uint32)flag;

    ret &= Cpuwdt_Std_SetPw0(coreId);

    return ret;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
uint16 Cpuwdt_Hal_GetCePassword(void)
{
    MultiCoreID coreId;
    const CPUWDT_MODULE* cpuwdt;
    Cpuwdt_PwMode ceMode;
    uint16 prePassword;
    uint16 password;

    coreId = Multicore_GetCoreID();
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    /* PWWDT permission password generation mode */
    /* #Violation: cpuwdt_hal_c_REF_4 */
    ceMode = (Cpuwdt_PwMode)cpuwdt->PWMAI.B.CEPWM;

    /* Acquire previous correct password */
    prePassword = (uint16)cpuwdt->CEPW.U;

    /* If the user-defined password generation mode is fixed */
    if(CPUWDT_PWMODE_FIXED == ceMode)
    {
        password = CPUWDT_PWCE_FIXED_PASSWORD;
    }
    else /* The user-defined password generation mode is dynamic */
    {
        password = Cpuwdt_Hal_CalculateDynamicPassword(prePassword, ceMode);
    }

    return password;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
boolean Cpuwdt_Hal_ClearEndinit(void)
{
    /******************************************************
     * Usage Restrictions
     * - Before using this API, it is necessary to enter 
     *   the critical section for protection.
     *******************************************************/
    boolean ret;
    MultiCoreID coreId;
    CPUWDT_MODULE *cpuwdt;
    uint32 timeOutCnt;
    
    timeOutCnt = 0U;
    ret = TRUE;

    coreId = Multicore_GetCoreID();
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    ret &= Cpuwdt_Std_ClearPwce(coreId);

    /* Enable the ENDINIT function */
    if (3U != cpuwdt->CECNTEN.U)
    {
        cpuwdt->CECNTEN.U = 3U;
        ret &= Cpuwdt_Register_ReadBack_Check(ret, 3U, cpuwdt->CECNTEN.U);
    }
    /* Start the CE counter */
    cpuwdt->CECNTC.B.CESTART = 0x3U;

    ret &= Cpuwdt_Std_SetPwce(coreId);

    while ((1U == cpuwdt->CESTS.B.CEOUTSTS) && (timeOutCnt < CPUWDT_CEOUTSTS_TIMEOUT_MAX))
    {
        timeOutCnt++;
    }
    
    if (timeOutCnt >= CPUWDT_CEOUTSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }
    
    return ret;
}

/* #Violation: cpuwdt_hal_c_REF_1 */
boolean Cpuwdt_Hal_SetEndinit(void)
{
    /******************************************************
     * Usage Restrictions
     * - Before using this API, it is necessary to enter 
     *   the critical section for protection.
     *******************************************************/
    boolean ret;
    MultiCoreID coreId;
    CPUWDT_MODULE *cpuwdt;
    uint32 timeOutCnt;
    
    ret = TRUE;
    timeOutCnt = 0U;

    coreId = Multicore_GetCoreID();
    /* #Violation: cpuwdt_hal_c_REF_5 */
    /* #Violation: cpuwdt_hal_c_REF_12 */
    cpuwdt = CPUWDT(coreId);

    ret &= Cpuwdt_Std_ClearPwce(coreId);

    /* Disable the ENDINIT function */
    cpuwdt->CECNTC.B.CESTOP = 3U;

    ret &= Cpuwdt_Std_SetPwce(coreId);

    while ((0U == cpuwdt->CESTS.B.CEOUTSTS) && (timeOutCnt < CPUWDT_CEOUTSTS_TIMEOUT_MAX))
    {
        timeOutCnt++;
    }
    
    if (timeOutCnt >= CPUWDT_CEOUTSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

/* #Violation: cpuwdt_hal_c_REF_10 */
#define CPUWDT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpuwdt_hal_c_REF_9 */
#include "Cpuwdt_MemMap.h"
/**********************************************************************************************************************
 *                                                    End of File
 *********************************************************************************************************************/

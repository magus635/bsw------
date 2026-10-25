/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    cpuwdt_std.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all internal functions of CPUWDT module.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #cpuwdt_std_c_REF_1:MISRAC2012-MISRAC2012-Rule-10.5;
* Justification:reason 4304 Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8;
*
* #cpuwdt_std_c_REF_2:MISRAC2012-Rule-11.4;
* Justification:reason 0303 Converting integers to object pointers to reduce register access complexity.
* 
* #cpuwdt_std_c_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #cpuwdt_std_c_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
 * #cpuwdt_std_c_REF_5:MISRAC2012-Rule-1.2;
 * Justification: Inline assembly for CPU-specific operations.
 * 
 * #cpuwdt_std_c_REF_6:MISRAC2012-Dir-4.3;
 * Justification: Mixing inline assembly with C code reduces code complexity.
 * 
 * #cpuwdt_std_c_REF_7:MISRAC2012-Dir-4.9;
 * Justification:Function like macros are used to reduce code complexity.
 *
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "cpuwdt_std.h"
#include "cpuwdt_register.h"
#include "multicore.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* PW0 password */
#define CPUWDT_PASSWORD0         (0x3AU)
/* WDTPW password */
#define CPUWDT_PASSWORDWDT       (0xA30U)
/* CEPW password */
#define CPUWDT_PASSWORDCE        (0x3A00U)
/* CPUWDT timeout value */
#define CPUWDT_CWSTS_TIMEOUT_MAX (0xE00UL)
 /**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/* #Violation: cpuwdt_std_c_REF_4 */
#define CPUWDT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpuwdt_std_c_REF_3 */
#include "Cpuwdt_MemMap.h"

/**********************************************************************************************************************
 * Function:     Cpuwdt_Std_GetPassword
 * Description:  Get CE or WDT password
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        sel: Select WDT or CE
 *                       0: WDT    1: CE
 *                       Other: invalid
 *               coreId: Current core id
 * Inout:        None
 * Output:       None
 * Return:       uint16: Current correct dynamic password
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208      Create
 *********************************************************************************************************************/
static uint16 Cpuwdt_Std_GetPassword(uint8 sel, MultiCoreID coreId);
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static uint16 Cpuwdt_Std_GetPassword(uint8 sel, MultiCoreID coreId)
{
    const CPUWDT_MODULE *cpuwdt;
    uint16 password;
    uint8 mode;

    /* #Violation: cpuwdt_std_c_REF_2 */
    /* #Violation: cpuwdt_std_c_REF_7 */
    cpuwdt = CPUWDT(coreId);

    if (0U == sel)
    {
        mode = cpuwdt->PWMAI.B.WDTPWM;
        password = (uint16)cpuwdt->WDTPW.U;
    }
    else
    {
        mode = cpuwdt->PWMAI.B.CEPWM;
        password = (uint16)cpuwdt->CEPW.U;
    }

    /* Password generation mode is dynamic 1 */
    if(1U == mode)
    {
        /* Calculate the current correct password */
        password = ((password & 0x1FFFU) << 1U) | (((password >> 13U) & 1U) ^ ((password >> 12U) & 1U) ^ \
                                                    ((password >> 11U) & 1U) ^ ((password >> 2U) & 1U));
    }
    /* Password generation mode is dynamic 2 */
    else if (2U == mode)
    {
        /* Calculate the current correct password */
        password = password ^ 0x3FU;
    }
    /* Static password */
    else
    {
        if (0U == sel)
        {
            password = CPUWDT_PASSWORDWDT;
        }
        else
        {
            password = CPUWDT_PASSWORDCE;
        }
    }

    return password;
}
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: cpuwdt_std_c_REF_6 */
boolean Cpuwdt_Std_ClearPw0(MultiCoreID coreId)
{
    CPUWDT_MODULE *cpuwdt;
    uint32 timeOutCnt;
    boolean ret;

    timeOutCnt = 0U;
    ret = TRUE;
    /* #Violation: cpuwdt_std_c_REF_2 */
    /* #Violation: cpuwdt_std_c_REF_7 */
    cpuwdt = CPUWDT(coreId);

    /* Unlock PW0 permission */
    cpuwdt->PW0.U = CPUWDT_PASSWORD0;
    /* #Violation: cpuwdt_std_c_REF_5 */
    DSB();
    cpuwdt->PW0.U = CPUWDT_PASSWORD0;

    while((0U == cpuwdt->CWSTS.B.PW0V) && (timeOutCnt < CPUWDT_CWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }

    if (timeOutCnt >= CPUWDT_CWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

boolean Cpuwdt_Std_SetPw0(MultiCoreID coreId)
{
    CPUWDT_MODULE *cpuwdt;
    uint32 timeOutCnt;
    boolean ret;

    timeOutCnt = 0U;
    ret = TRUE;
    /* #Violation: cpuwdt_std_c_REF_2 */
    /* #Violation: cpuwdt_std_c_REF_7 */
    cpuwdt = CPUWDT(coreId);

    /* Lock PW0 permission */
    cpuwdt->PWLOCK.B.PW0LCK = 1U;

    while((1U == cpuwdt->CWSTS.B.PW0V) && (timeOutCnt < CPUWDT_CWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }

    if (timeOutCnt >= CPUWDT_CWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

/* #Violation: cpuwdt_std_c_REF_6 */
boolean Cpuwdt_Std_ClearPwwdt(MultiCoreID coreId)
{
    CPUWDT_MODULE *cpuwdt;
    uint32 timeOutCnt;
    uint16 password;
    boolean ret;

    timeOutCnt = 0U;
    ret = TRUE;
    /* #Violation: cpuwdt_std_c_REF_2 */
    /* #Violation: cpuwdt_std_c_REF_7 */
    cpuwdt = CPUWDT(coreId);

    /* Unlock PWWDT permission */
    password = Cpuwdt_Std_GetPassword(0U, coreId);
    cpuwdt->WDTPW.B.WDTPW = password;
    cpuwdt->PWLOCK.B.WDTPWLCK = 1U;
    /* #Violation: cpuwdt_std_c_REF_5 */
    DSB();
    password = Cpuwdt_Std_GetPassword(0U, coreId);
    cpuwdt->WDTPW.B.WDTPW = password;

    while((0U == cpuwdt->CWSTS.B.WDTPWV) && (timeOutCnt < CPUWDT_CWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }

    if (timeOutCnt >= CPUWDT_CWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

boolean Cpuwdt_Std_SetPwwdt(MultiCoreID coreId)
{
    CPUWDT_MODULE *cpuwdt;
    uint32 timeOutCnt;
    boolean ret;

    timeOutCnt = 0U;
    ret = TRUE;
    /* #Violation: cpuwdt_std_c_REF_2 */
    /* #Violation: cpuwdt_std_c_REF_7 */
    cpuwdt = CPUWDT(coreId);

    cpuwdt->PWLOCK.B.WDTPWLCK = 1U;

    while((1U == cpuwdt->CWSTS.B.WDTPWV) && (timeOutCnt < CPUWDT_CWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }

    if (timeOutCnt >= CPUWDT_CWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

/* #Violation: cpuwdt_std_c_REF_6 */
boolean Cpuwdt_Std_ClearPwce(MultiCoreID coreId)
{
    CPUWDT_MODULE *cpuwdt;
    uint32 timeOutCnt;
    uint16 password;
    boolean ret;
    
    timeOutCnt = 0U;
    ret = TRUE;
    /* #Violation: cpuwdt_std_c_REF_2 */
    /* #Violation: cpuwdt_std_c_REF_7 */
    cpuwdt = CPUWDT(coreId);

    /* Unlock PWCE permission */
    password = Cpuwdt_Std_GetPassword(1U, coreId);
    cpuwdt->CEPW.B.CEPW = password;
    cpuwdt->PWLOCK.B.CEPWLCK = 1U;
    /* #Violation: cpuwdt_std_c_REF_5 */
    DSB();
    password = Cpuwdt_Std_GetPassword(1U, coreId);
    cpuwdt->CEPW.B.CEPW = password;

    while((0U == cpuwdt->CWSTS.B.CEPWV) && (timeOutCnt < CPUWDT_CWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }
    
    if (timeOutCnt >= CPUWDT_CWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }
    
    return ret;
}

boolean Cpuwdt_Std_SetPwce(MultiCoreID coreId)
{
    CPUWDT_MODULE *cpuwdt;
    uint32 timeOutCnt;
    boolean ret;

    timeOutCnt = 0U;
    ret = TRUE;
    /* #Violation: cpuwdt_std_c_REF_2 */
    /* #Violation: cpuwdt_std_c_REF_7 */
    cpuwdt = CPUWDT(coreId);

    /* Lock PWCE permission */
    cpuwdt->PWLOCK.B.CEPWLCK = 1U;

    while((1U == cpuwdt->CWSTS.B.CEPWV) && (timeOutCnt < CPUWDT_CWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }

    if (timeOutCnt >= CPUWDT_CWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

/* #Violation: cpuwdt_std_c_REF_4 */
#define CPUWDT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpuwdt_std_c_REF_3 */
#include "Cpuwdt_MemMap.h"
/**********************************************************************************************************************
**                                                    End of File                                                    **
**********************************************************************************************************************/

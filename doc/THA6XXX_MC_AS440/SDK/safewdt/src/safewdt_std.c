/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    safewdt_std.c
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all internal functions of SAFEWDT_HAL module.
 *********************************************************************************************************************/

/*
* #Violation Summary
*
* #safewdt_std_c_REF_1:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #safewdt_std_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #safewdt_std_c_REF_3:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #safewdt_std_c_REF_4:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
* #safewdt_std_c_REF_5:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "safewdt_std.h"
#include "safewdt_register.h"
#include "Platform_Types.h"
#include "regtypes.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* PW0 password */
#define SAFEWDT_PASSWORD0         (0x4BU)
/* WDTPW password */
#define SAFEWDT_PASSWORDWDT       (0xB40U)
/* SEPW password */
#define SAFEWDT_PASSWORDSE        (0x2C00U)
/* SAFEWDT_HAL timeout value */
#define SAFEWDT_SWSTS_TIMEOUT_MAX (0xE00UL)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/* #Violation: safewdt_std_c_REF_3 */ 
#define SAFEWDT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: safewdt_std_c_REF_2 */ 
#include "Safewdt_MemMap.h"
/**********************************************************************************************************************
 * Function:     Safewdt_Std_GetPassword
 * Description:  Get SE or WDT password
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        sel: Select WDT or SE
 *                       0: WDT    1: SE
 *                       Other: invalid
 * Inout:        None
 * Output:       None
 * Return:       uint16: Current correct dynamic password
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208      Create
 *********************************************************************************************************************/
static uint16 Safewdt_Std_GetPassword(uint8 sel);
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static uint16 Safewdt_Std_GetPassword(uint8 sel)
{
    uint16 password;
    uint8 mode;

    if (0U == sel)
    {
        /* #Violation: safewdt_std_c_REF_1 */ 
        mode = SAFEWDT_HAL->PWMAI.B.WDTPWM;
        /* #Violation: safewdt_std_c_REF_1 */ 
        password = (uint16)SAFEWDT_HAL->WDTPW.U;
    }
    else
    {
        /* #Violation: safewdt_std_c_REF_1 */ 
        mode = SAFEWDT_HAL->PWMAI.B.SEPWM;
        /* #Violation: safewdt_std_c_REF_1 */ 
        password = (uint16)SAFEWDT_HAL->SEPW.U;
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
            password = SAFEWDT_PASSWORDWDT;
        }
        else
        {
            password = SAFEWDT_PASSWORDSE;
        }
    }

    return password;
}
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: safewdt_std_c_REF_5 */ 
boolean Safewdt_Std_ClearPw0(void)
{
    boolean ret;
    uint32 timeOutCnt;
    
    timeOutCnt = 0U;
    ret = TRUE;

    /* Unlock PW0 permission */
    /* #Violation: safewdt_std_c_REF_1 */ 
    SAFEWDT_HAL->PW0.U = SAFEWDT_PASSWORD0;
    /* #Violation: safewdt_std_c_REF_4 */ 
    DSB();
    /* #Violation: safewdt_std_c_REF_1 */ 
    SAFEWDT_HAL->PW0.U = SAFEWDT_PASSWORD0;

    /* #Violation: safewdt_std_c_REF_1 */ 
    while((0U == SAFEWDT_HAL->SWSTS.B.PW0STS) && (timeOutCnt < SAFEWDT_SWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }
    
    if (timeOutCnt >= SAFEWDT_SWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }

    return ret;
}

boolean Safewdt_Std_SetPw0(void)
{
    uint32 timeOutCnt;
    boolean ret;

    timeOutCnt = 0U;
    ret = TRUE;
    /* Lock PW0 permission*/
    /* #Violation: safewdt_std_c_REF_1 */ 
    SAFEWDT_HAL->PWLOCK.B.PW0LCK = 1U;

    /* #Violation: safewdt_std_c_REF_1 */ 
    while((1U == SAFEWDT_HAL->SWSTS.B.PW0STS) && (timeOutCnt < SAFEWDT_SWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }
    
    if (timeOutCnt >= SAFEWDT_SWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }
        
    return ret;
}

/* #Violation: safewdt_std_c_REF_5 */ 
boolean Safewdt_Std_ClearPwwdt(void)
{
    uint32 timeOutCnt;
    uint16 password;
    boolean ret;
    
    timeOutCnt = 0U;
    ret = TRUE;

    /*Unlock PWWDT permission*/
    password = Safewdt_Std_GetPassword(0U);
    /* #Violation: safewdt_std_c_REF_1 */
    SAFEWDT_HAL->WDTPW.B.WDTPW = password;
    /* #Violation: safewdt_std_c_REF_1 */
    SAFEWDT_HAL->PWLOCK.B.WDTPWLCK = 1U;
    /* #Violation: safewdt_std_c_REF_4 */ 
    DSB();
    password = Safewdt_Std_GetPassword(0U);
    /* #Violation: safewdt_std_c_REF_1 */
    SAFEWDT_HAL->WDTPW.B.WDTPW = password;

    /* #Violation: safewdt_std_c_REF_1 */ 
    while((0U == SAFEWDT_HAL->SWSTS.B.WDTPWSTS) && (timeOutCnt < SAFEWDT_SWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }
    
    if (timeOutCnt >= SAFEWDT_SWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }
        
    return ret;
}

boolean Safewdt_Std_SetPwwdt(void)
{
    uint32 timeOutCnt;
    boolean ret;

    timeOutCnt = 0U;
    ret = TRUE;
    /*Lock PWWDT permission*/
    /* #Violation: safewdt_std_c_REF_1 */ 
    SAFEWDT_HAL->PWLOCK.B.WDTPWLCK = 1U;

    /* #Violation: safewdt_std_c_REF_1 */ 
    while((1U == SAFEWDT_HAL->SWSTS.B.WDTPWSTS) && (timeOutCnt < SAFEWDT_SWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }
    
    if (timeOutCnt >= SAFEWDT_SWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }
        
    return ret;
}

/* #Violation: safewdt_std_c_REF_5 */ 
boolean Safewdt_Std_ClearPwse(void)
{
    uint32 timeOutCnt;
    uint16 password;
    boolean ret;

    timeOutCnt = 0U;
    ret = TRUE;

    /*Unlock PWSE permission*/
    password = Safewdt_Std_GetPassword(1U);
    /* #Violation: safewdt_std_c_REF_1 */
    SAFEWDT_HAL->SEPW.B.SEPW = password;
    /* #Violation: safewdt_std_c_REF_1 */
    SAFEWDT_HAL->PWLOCK.B.SEPWLCK = 1U;
    /* #Violation: safewdt_std_c_REF_4 */ 
    DSB();
    password = Safewdt_Std_GetPassword(1U);
    /* #Violation: safewdt_std_c_REF_1 */
    SAFEWDT_HAL->SEPW.B.SEPW = password;

    /* #Violation: safewdt_std_c_REF_1 */ 
    while((0U == SAFEWDT_HAL->SWSTS.B.SEPWSTS) && (timeOutCnt < SAFEWDT_SWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }
    
    if (timeOutCnt >= SAFEWDT_SWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }
        
    return ret;
}

boolean Safewdt_Std_SetPwse(void)
{
    uint32 timeOutCnt;
    boolean ret;

    timeOutCnt = 0U;
    ret = TRUE;
    /*Lock PWSE permission*/
    /* #Violation: safewdt_std_c_REF_1 */
    SAFEWDT_HAL->PWLOCK.B.SEPWLCK = 1U;

    /* #Violation: safewdt_std_c_REF_1 */ 
    while((1U == SAFEWDT_HAL->SWSTS.B.SEPWSTS) && (timeOutCnt < SAFEWDT_SWSTS_TIMEOUT_MAX))
    {
       timeOutCnt++;
    }
    
    if (timeOutCnt >= SAFEWDT_SWSTS_TIMEOUT_MAX)
    {
        ret = FALSE;
    }
        
    return ret;
}

/* #Violation: safewdt_std_c_REF_3 */ 
#define SAFEWDT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: safewdt_std_c_REF_2 */ 
#include "Safewdt_MemMap.h"
/**********************************************************************************************************************
 *                                                    End of File
 *********************************************************************************************************************/

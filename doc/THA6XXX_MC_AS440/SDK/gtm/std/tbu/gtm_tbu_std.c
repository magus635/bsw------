/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_tbu_std.c
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations for all the internal
 *                 functions of the TBU module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#gtm_tbu_std_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#gtm_tbu_std_c_REF_2:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #gtm_tbu_std_c_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_tbu_std_c_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm_tbu_std.h"
#include "tha6_cfg.h"
#include "gtm.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: gtm_tbu_std_c_REF_4 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tbu_std_c_REF_3 */
#include "Gtm_MemMap.h"

uint32 Gtm_Tbu_Std_GetCounterValue(Gtm_Tbu_Ch channel)
{
    uint32 value;
    const GTM_TBU *tbu;

    /* #Violation: gtm_tbu_std_c_REF_2 */
    tbu = &GTM_HAL->GTM_CLUSTER[0].TBU;
    if (channel == GTM_TBU_CH_TS0)
    {
        if (1U == tbu->CH0_CTRL.B.LOW_RES)
        {
            value = tbu->CH0_BASE.B.BASE >> 3U;
        }
        else
        {
            value = tbu->CH0_BASE.B.BASE & 0xFFFFFFU;
        }
    }
    else if (channel == GTM_TBU_CH_TS1)
    {
        value = tbu->CH1_BASE.B.BASE;
    }
    else
    {
        value = tbu->CH2_BASE.B.BASE;
    }
    value &= 0xFFFFFFU;
    return value;
}

boolean Gtm_Tbu_Std_SetChannels(uint32 chEn)
{
    GTM_TBU *pTbu;
    uint32 expect;
    uint32 ch;
    boolean ret;

    expect = 0U;
    for (ch = 0U; ch <= (uint32)GTM_TBU_CH_TS3; ch++)
    {
        uint32 shift;
        shift = ch * 2U;
        if (((uint32)2U << shift) == (chEn & ((uint32)3U << shift)))
        {
            expect |= ((uint32)3U << shift);
        }
    }
    ret = TRUE;
    /* #Violation: gtm_tbu_std_c_REF_2 */
    pTbu = (GTM_TBU *)&GTM_HAL->GTM_CLUSTER[0].TBU;
    pTbu->CHEN.U = chEn;
    ret = Gtm_Register_ReadBack_Check(ret, expect, pTbu->CHEN.U);
    return ret;
}

boolean Gtm_Tbu_Std_SetClockSource(Gtm_Tbu_Ch channel, uint8 clk)
{
    GTM_TBU *pTbu;
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tbu_std_c_REF_2 */
    pTbu = (GTM_TBU *)&GTM_HAL->GTM_CLUSTER[0].TBU;

    if (channel == GTM_TBU_CH_TS0)
    {
        pTbu->CH0_CTRL.B.CH_CLK_SRC = clk;
        ret = Gtm_Register_ReadBack_Check(ret, (uint32)clk, pTbu->CH0_CTRL.B.CH_CLK_SRC);
    }
    else if (channel == GTM_TBU_CH_TS1)
    {
        pTbu->CH1_CTRL.B.CH_CLK_SRC = clk;
        ret = Gtm_Register_ReadBack_Check(ret, (uint32)clk, pTbu->CH1_CTRL.B.CH_CLK_SRC);
    }
    else
    {
        pTbu->CH2_CTRL.B.CH_CLK_SRC = clk;
        ret = Gtm_Register_ReadBack_Check(ret, (uint32)clk, pTbu->CH2_CTRL.B.CH_CLK_SRC);
    }
    return ret;
}

boolean Gtm_Tbu_Std_SetMode(Gtm_Tbu_Ch channel, uint8 mode)
{
    GTM_TBU *pTbu;
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tbu_std_c_REF_2 */
    pTbu = (GTM_TBU *)&GTM_HAL->GTM_CLUSTER[0].TBU;

    switch ((Gtm_Tbu_Ch)channel)
    {
        case GTM_TBU_CH_TS1:
        {
            pTbu->CH1_CTRL.B.CH_MODE = mode;
            ret = Gtm_Register_ReadBack_Check(ret, (uint32)mode, pTbu->CH1_CTRL.B.CH_MODE);
            break;
        }
        case GTM_TBU_CH_TS2:
        {
            pTbu->CH2_CTRL.B.CH_MODE = mode;
            ret = Gtm_Register_ReadBack_Check(ret, (uint32)mode, pTbu->CH2_CTRL.B.CH_MODE);
            break;
        }
        default:
        {
            /* Do nothing */
            ret = FALSE;
            break;
        }
    }
    return ret;
}

void Gtm_Tbu_Std_SetBase(Gtm_Tbu_Ch channel, uint32 base)
{
    GTM_TBU *pTbu;

    /* #Violation: gtm_tbu_std_c_REF_2 */
    pTbu = (GTM_TBU *)&GTM_HAL->GTM_CLUSTER[0].TBU;

    if (channel == GTM_TBU_CH_TS0)
    {
        pTbu->CH0_BASE.U = base;
    }
    else if (channel == GTM_TBU_CH_TS1)
    {
        pTbu->CH1_BASE.U = base;
    }
    else
    {
        pTbu->CH2_BASE.U = base;
    }
}

boolean Gtm_Tbu_Std_SetTs0Res(uint8 res)
{
    GTM_TBU *pTbu;
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tbu_std_c_REF_2 */
    pTbu = (GTM_TBU *)&GTM_HAL->GTM_CLUSTER[0].TBU;

    pTbu->CH0_CTRL.B.LOW_RES = res;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)res, pTbu->CH0_CTRL.B.LOW_RES);
    return ret;
}

/* #Violation: gtm_tbu_std_c_REF_4 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tbu_std_c_REF_3 */
#include "Gtm_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

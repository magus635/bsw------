/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_timebase_hal.c
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of TIMEBASE module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
* #gtm_timebase_hal_c_REF_1:MISRAC2012-Rule-2.1; 
* Justification:Reserved API for user access.
*
* #gtm_timebase_hal_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core. Boolean can only be representes as uint8.
*
* #gtm_timebase_hal_c_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_timebase_hal_c_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm_timebase_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
#define GTM_CMU_CLK_NUM    (8U)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: gtm_timebase_hal_c_REF_4 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timebase_hal_c_REF_3 */
#include "Gtm_MemMap.h"

/* #Violation: gtm_timebase_hal_c_REF_1 */
boolean Gtm_TimeBase_Hal_InitClock(const Gtm_ClockConfig *const pConfig)
{
    uint32   clkConfig;
    uint32   clkEnable;
    uint32   expect;
    uint8    clk;
    GTM_CMU *pCmu;
    Gtm_Cmu_ConfigurableClk pClkCfg[GTM_CMU_CLK_NUM];
    boolean  ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timebase_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: gtm_timebase_hal_c_REF_2 */
    Assert((boolean)((0xFFFFFFU >= pConfig->globalClk.den) && (0xFFFFFFU >= pConfig->globalClk.num)));
    /* #Violation: gtm_timebase_hal_c_REF_2 */
    Assert((boolean)((0xFFFFFFU >= pConfig->externalClk.eclk0.den) && (0xFFFFFFU >= pConfig->externalClk.eclk0.num)));
    /* #Violation: gtm_timebase_hal_c_REF_2 */
    Assert((boolean)((0xFFFFFFU >= pConfig->externalClk.eclk1.den) && (0xFFFFFFU >= pConfig->externalClk.eclk1.num)));
    /* #Violation: gtm_timebase_hal_c_REF_2 */
    Assert((boolean)((0xFFFFFFU >= pConfig->externalClk.eclk2.den) && (0xFFFFFFU >= pConfig->externalClk.eclk2.num)));
    /* #Violation: gtm_timebase_hal_c_REF_2 */
    Assert((boolean)((0xFFFFFFU >= pConfig->configClk.clk0.divider) && (0xFFFFFFU >= pConfig->configClk.clk1.divider) &&
                    (0xFFFFFFU >= pConfig->configClk.clk2.divider) && (0xFFFFFFU >= pConfig->configClk.clk3.divider) &&
                    (0xFFFFFFU >= pConfig->configClk.clk4.divider) && (0xFFFFFFU >= pConfig->configClk.clk5.divider) &&
                    (0xFFFFFFU >= pConfig->configClk.clk6.divider) && (0xFFFFFFU >= pConfig->configClk.clk7.divider)));
#endif

    ret = TRUE;
    pCmu = Gtm_Cmu_Std_GetCmuPointer();

    /****************************** Enable aei_sys_clk ********************************/
    ret &= Gtm_Cmu_Std_SetClusterClocks((const Gtm_Cluster_ClkConfig *)&pConfig->clusterClk);

    /* Disable all the CMU clocks before configuring  GlobalClockDivider/CMUClk/FXCLK */
    ret &= Gtm_Cmu_Std_DisableAllClocks(pCmu);
    clkEnable = 0U;
    expect = 0U;

    /************************* Configure global clock divider *************************/
    ret &= Gtm_Cmu_Std_SetGlobalNUM(pCmu, pConfig->globalClk.num);
    ret &= Gtm_Cmu_Std_SetGlobalDEN(pCmu, pConfig->globalClk.den);

    /**************************** Configure external clock ****************************/
    if (TRUE == pConfig->externalClk.eclk0.isEnabled)
    {
        ret &= Gtm_Cmu_Std_SetECLKDivider(pCmu, 0, pConfig->externalClk.eclk0.num, pConfig->externalClk.eclk0.den);
        clkEnable |= ((uint32)GTM_CMU_CLK_ENABLE << GTM_CMU_EN_ECLK0_POS); /* Enable clock */
        expect |= ((uint32)3U << GTM_CMU_EN_ECLK0_POS);
    }

    if (TRUE == pConfig->externalClk.eclk1.isEnabled)
    {
        ret &= Gtm_Cmu_Std_SetECLKDivider(pCmu, 1, pConfig->externalClk.eclk1.num, pConfig->externalClk.eclk1.den);
        clkEnable |= ((uint32)GTM_CMU_CLK_ENABLE << GTM_CMU_EN_ECLK1_POS); /* Enable clock */
        expect |= ((uint32)3U << GTM_CMU_EN_ECLK1_POS);
    }

    if (TRUE == pConfig->externalClk.eclk2.isEnabled)
    {
        ret &= Gtm_Cmu_Std_SetECLKDivider(pCmu, 2, pConfig->externalClk.eclk2.num, pConfig->externalClk.eclk2.den);
        clkEnable |= ((uint32)GTM_CMU_CLK_ENABLE << GTM_CMU_EN_ECLK2_POS); /* Enable clock */
        expect |= ((uint32)3U << GTM_CMU_EN_ECLK2_POS);
    }

    /************************** Configure configurable clock **************************/
    clkConfig = 0;
    pClkCfg[0] = pConfig->configClk.clk0;
    pClkCfg[1] = pConfig->configClk.clk1;
    pClkCfg[2] = pConfig->configClk.clk2;
    pClkCfg[3] = pConfig->configClk.clk3;
    pClkCfg[4] = pConfig->configClk.clk4;
    pClkCfg[5] = pConfig->configClk.clk5;
    pClkCfg[6] = pConfig->configClk.clk6;
    pClkCfg[7] = pConfig->configClk.clk7;

    for (clk = 0U; clk < GTM_CMU_CLK_NUM; clk++)
    {
        if (TRUE == pClkCfg[clk].isEnabled)
        {
            clkConfig |= ((uint32)pClkCfg[clk].src << (2U*clk));
            ret &= Gtm_Cmu_Std_SetCLKDivider(pCmu, clk, pClkCfg[clk].divider);
            clkEnable |= ((uint32)GTM_CMU_CLK_ENABLE << (2U*clk)); /* Enable clock */
            expect |= ((uint32)3U << (2U*clk));
        }
    }

    ret &= Gtm_Cmu_Std_SetClockCtrl(pCmu, clkConfig);

    /**************************** Fixed configurable clock ****************************/
    if (TRUE == pConfig->fixedClk.isEnabled)
    {
        ret &= Gtm_Cmu_Std_SetFXCLKSelection(pCmu, (uint8)pConfig->fixedClk.src);
        clkEnable |= ((uint32)GTM_CMU_CLK_ENABLE << GTM_CMU_EN_FXCLK_POS); /* Enable clock */
        expect |= ((uint32)3U << GTM_CMU_EN_FXCLK_POS);
    }

    /* Enable CMU clock */
    pCmu->CLK_EN.U = clkEnable;

    ret = Gtm_Register_ReadBack_Check(ret, expect, pCmu->CLK_EN.U);

    return ret;
}

/* #Violation: gtm_timebase_hal_c_REF_1 */
boolean Gtm_TimeBase_Hal_InitFreeTimer(const Gtm_FreeTimerConfig *const pConfig)
{
    uint32 chEn;
    boolean ret;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timebase_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));

    if (NULL_PTR != pConfig->pCh0)
    {
        /* #Violation: gtm_timebase_hal_c_REF_2 */
        Assert((boolean)(0xFFFFFFU >= pConfig->pCh0->initVal));
    }

    if (NULL_PTR != pConfig->pCh1)
    {
        /* #Violation: gtm_timebase_hal_c_REF_2 */
        Assert((boolean)(0xFFFFFFU >= pConfig->pCh1->initVal));
    }

    if (NULL_PTR != pConfig->pCh2)
    {
        /* #Violation: gtm_timebase_hal_c_REF_2 */
        Assert((boolean)(0xFFFFFFU >= pConfig->pCh2->initVal));
    }
#endif

    ret = TRUE;
    /* Disable all channel */
    chEn = (GTM_TBU_CH_DISABLE << GTM_TBU_ENDIS_POS0) | (GTM_TBU_CH_DISABLE << GTM_TBU_ENDIS_POS1) |
           (GTM_TBU_CH_DISABLE << GTM_TBU_ENDIS_POS2) | (GTM_TBU_CH_DISABLE << GTM_TBU_ENDIS_POS3);
    ret &= Gtm_Tbu_Std_SetChannels(chEn);

    chEn = 0;

    if (NULL_PTR != pConfig->pCh0)
    {
        ret &= Gtm_Tbu_Std_SetClockSource(GTM_TBU_CH_TS0, (uint8)pConfig->pCh0->clk);
        Gtm_Tbu_Std_SetBase(GTM_TBU_CH_TS0, pConfig->pCh0->initVal);
        ret &= Gtm_Tbu_Std_SetTs0Res((uint8)pConfig->pCh0->bitUse);

        if (TRUE == pConfig->pCh0->isEnabled)
        {
            chEn |= (GTM_TBU_CH_ENABLE << GTM_TBU_ENDIS_POS0);
        }
    }

    if (NULL_PTR != pConfig->pCh1)
    {
        ret &= Gtm_Tbu_Std_SetClockSource(GTM_TBU_CH_TS1, (uint8)pConfig->pCh1->clk);
        Gtm_Tbu_Std_SetBase(GTM_TBU_CH_TS1, pConfig->pCh1->initVal);
        ret &= Gtm_Tbu_Std_SetMode(GTM_TBU_CH_TS1, (uint8)pConfig->pCh1->mode);

        if (TRUE == pConfig->pCh1->isEnabled)
        {
            chEn |= (GTM_TBU_CH_ENABLE << GTM_TBU_ENDIS_POS1);
        }
    }

    if (NULL_PTR != pConfig->pCh2)
    {
        ret &= Gtm_Tbu_Std_SetClockSource(GTM_TBU_CH_TS2, (uint8)pConfig->pCh2->clk);
        Gtm_Tbu_Std_SetBase(GTM_TBU_CH_TS2, pConfig->pCh2->initVal);
        ret &= Gtm_Tbu_Std_SetMode(GTM_TBU_CH_TS2, (uint8)pConfig->pCh2->mode);

        if (TRUE == pConfig->pCh2->isEnabled)
        {
            chEn |= (GTM_TBU_CH_ENABLE << GTM_TBU_ENDIS_POS2);
        }
    }

    /* TBU channels enable */
    ret &= Gtm_Tbu_Std_SetChannels(chEn);
    return ret;
}

/* #Violation: gtm_timebase_hal_c_REF_1 */
uint32 Gtm_TimeBase_Hal_GetFreeTimerCounter(Gtm_Tbu_Ch channel)
{
    /* TBU counter value */
    return Gtm_Tbu_Std_GetCounterValue(channel);
}

/* #Violation: gtm_timebase_hal_c_REF_4 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timebase_hal_c_REF_3 */
#include "Gtm_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

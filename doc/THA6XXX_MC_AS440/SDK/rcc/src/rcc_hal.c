/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    rcc_hal.c
 * Author:      00976
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of RCC module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#rcc_hal_c_REF_1:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured
*               by code review.
*#rcc_hal_c_REF_2:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #rcc_hal_c_REF_3:MISRAC2012-Rule-10.5;
* Justification: Cortex-R52+ lacks bool type, minimum unit is uint8.
*
*#rcc_hal_c_REF_5:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #rcc_hal_c_REF_6:MISRAC2012-Rule-2.1;
* Justification: The interface is called by the application layer.
*
* #rcc_hal_c_REF_10:MISRAC2012-Rule-2.2;
* Justification: Platform-based design with configurable macros.
*
* #rcc_hal_c_REF_12:CEW-704;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #rcc_hal_c_REF_13:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
* 
* #rcc_hal_c_REF_14:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #rcc_hal_c_REF_15:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
* #rcc_hal_c_REF_16:MISRAC2012-Rule-8.7;
* Justification:The function is used by other function.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "rcc_hal.h"
#include "Platform_Types.h"
#include "rcc_register.h"
#include "safewdt_hal.h"
#include "cpuwdt_hal.h"
#include "compilertypes.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* FOUTVCO range */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_FOUTVCO_MIN (400000000U)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_FOUTVCO_MAX (1600000000U)
/* SSMOD DIVVAL range */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_SSMOD_DIVVAL_MIN (0U)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_SSMOD_DIVVAL_MAX (63U)
/* SSMOD SPREAD range */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_SSMOD_SPREAD_MIN (1U)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_SSMOD_SPREAD_MAX (31U)
/* PLL fbDiv parameter range in integer mode */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_SYSPLL_INTEGER_MODE_FBDIV_MAX (1600U)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_PERPLL_INTEGER_MODE_FBDIV_MAX (1600U)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_PLL_INTEGER_MODE_FBDIV_MIN (16U)
/* PLL fbDiv parameter range in decimal mode */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_PLL_DECIMAL_MODE_FBDIV_MAX (400U)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_PLL_DECIMAL_MODE_FBDIV_MIN (20U)
/* PLL refDiv parameter range  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_PLL_REFDIV_MAX (63U)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_PLL_REFDIV_MIN (1U)
/* EXT Pre DIV */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_EXT_PREDIV_MAX (1023U)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_EXT_PREDIV_MIN (0U)
/* PLL postDiv1&2 parameter range  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_PLL_POSTDIV_MAX (7U)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_PLL_POSTDIV_MIN (1U)
/* PLL FRAC factor:2^24 */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_PLL_FRAC_FACTOR (16777216.0F)
/* Cpu clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_CPUCLKDIV_MAX (255U)
/* System clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_SYSCLKDIV_MAX (7U)
/* AXI clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_AXICLKDIV_MAX (63U)
/* AHB clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_AHBCLKDIV_MAX (511U)
/* GTM clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_GTMCLKDIV_MAX (31U)
/* QSPI and ESPI clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_SPICLKDIV_MAX (31U)
/* CAN clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_CANCLKDIV_MAX (63U)
/* FC clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_FCCLKDIV_MAX (31U)
/* RDC and DSADC clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_RDC_DSADCCLKDIV_MAX (63U)
/* WDT clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_WDTCLKDIV_MAX (31U)
/* IPCNT clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_IPCNTCLKDIV_MAX (63U)
/* ASI BAUD BUS clock division factor max value */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_ASIBAUDBUSCLKDIV_MAX (511U)

/* BASETIMER clock division factor min value */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_BASETIMERCLKDIV_MIN (3U)

/* STM clock division factor max value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_STMCLKDIV_MAX (31U)
/* TIMOUTCNT max value */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_TIMOUTCNT_MAX (1000U)
/* Debug reset flag clear value  */
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_DBG_RESET (0xE60U)

/* WDT protect value  */
#define RCC_WDTPROT_VALUE (0xACCE5566U)

/* Module Reset count value */
#define RCC_MODREST_COUNT (1000U)

#define RCC_BIT_DISABLE (0U)
#define RCC_BIT_ENABLE (1U)
#define RCC_REG_WIDTH (32U)

/* Enable all DSADC clock  */
#define RCC_ENABLE_ALLDSADC_CLK (0x3FFU)
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_ENABLE_DSADC_CFG (0x00800000UL)

/* HSE stability count value */
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
#define RCC_HSE_STBCOUNT (0x64190U)
#endif

#if defined(THA6_THA6104)
#define RCC_HSE_STBCOUNT (0x63D678C00ULL)
#endif

#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* EXTCLKDIVCFG register mask value */
#define  RCC_EXTCLKDIVCFG_MASK_VAL (0x30003U)
#endif
/* Chip basic configuration initialization */
/* Flash configuration */
#define CHIP_BASIC_CFG_DFCON_REGADDR (0xC0100000U + 0x004U)
#define CHIP_BASIC_CFG_PFCON_REGADDR (0xC0100000U + 0x008U)
#if defined(THA6_THA6412)
#define CHIP_BASIC_CFG_PFCON2_REGADDR (0xC0140C00U + 0x008U)
#endif
/* DSADC configuration */
/* #Violation: rcc_hal_c_REF_13 */
#define CHIP_BASIC_CFG_DSADC0_MFCFG_REGADDR (0xB0002000U + 0x20U)
/* #Violation: rcc_hal_c_REF_13 */
#define CHIP_BASIC_CFG_DSADC1_MFCFG_REGADDR (0xB0002400U + 0x20U)
/* #Violation: rcc_hal_c_REF_13 */
#define CHIP_BASIC_CFG_DSADC2_MFCFG_REGADDR (0xB0012000U + 0x20U)
/* #Violation: rcc_hal_c_REF_13 */
#define CHIP_BASIC_CFG_DSADC3_MFCFG_REGADDR (0xB0012400U + 0x20U)

#if defined(THA6_THA6412)
#define CHIP_BASIC_CFG_DSADC4_MFCFG_REGADDR (0xB0002800U + 0x20U)
#define CHIP_BASIC_CFG_DSADC5_MFCFG_REGADDR (0xB0002C00U + 0x20U)
#define CHIP_BASIC_CFG_DSADC6_MFCFG_REGADDR (0xB0012800U + 0x20U)
#define CHIP_BASIC_CFG_DSADC7_MFCFG_REGADDR (0xB0012C00U + 0x20U)
#define CHIP_BASIC_CFG_DSADC8_MFCFG_REGADDR (0xB0301000U + 0x20U)
#define CHIP_BASIC_CFG_DSADC9_MFCFG_REGADDR (0xB0301400U + 0x20U)

#endif
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rcc_hal_c_REF_14 */
#include "Rcc_MemMap.h"

#define RCC_REG_CHECK
#if defined(RCC_REG_CHECK)
LOCAL_FORCEINLINE boolean Rcc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Rcc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Rcc_Hal_GetModuleClkSrcFreq
 * Description:  Get module clock source frequency, such as PLL, HSE, HSI, etc.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Clock source selection
 *                  perPllOutClkSel: PerPll output clock source selection
 * Inout:        None
 * Output:       None
 * Return:       float32: Selected clock source
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 *********************************************************************************************************************/
static float32 Rcc_Hal_GetModuleClkSrcFreq(Rcc_ModuleClockSource clkSrc, Rcc_PerPllClkType perPllOutClkSel);

/**********************************************************************************************************************
 * Function:     Rcc_Hal_EnableWdtClk
 * Description:  Enable/disable WDT module clock.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSet: Enable/disable WDT module clock
 *                  setBit: set bit
 * Inout:        None
 * Output:       None
 * Return:       boolean: Operation success or not
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/30    00930       Create
 *********************************************************************************************************************/
static boolean Rcc_Hal_EnableWdtClk(Rcc_ModuleClkSet clkSet, uint32 setBit);

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
static boolean Rcc_Hal_EnableWdtClk(Rcc_ModuleClkSet clkSet, uint32 setBit)
{
    boolean ret;
    uint32 regVal;
    ret = TRUE;
    /* Enable WDT clock protect */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKENWDTPROT.U = RCC_WDTPROT_VALUE;
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)RCC_WDTPROT_VALUE, (uint32)RCC_CLOCK->CLKENWDTPROT.U);
    if (clkSet == RCC_MODULECLK_ENABLE)
    {
        /* #Violation: rcc_hal_c_REF_2 */
        regVal = (uint32)RCC_CLOCK->CLKENWDT.U;
        regVal |= setBit;
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKENWDT.U = regVal;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, regVal, (uint32)RCC_CLOCK->CLKENWDT.U);
    }
    else
    {
        /* #Violation: rcc_hal_c_REF_2 */
        regVal = (uint32)RCC_CLOCK->CLKENWDT.U;
        regVal &= ~setBit;
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKENWDT.U = regVal;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, regVal, (uint32)RCC_CLOCK->CLKENWDT.U);
    }
    /* Disable WDT clock protect */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKENWDTPROT.U = 0x0U;
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, 0x0U, (uint32)RCC_CLOCK->CLKENWDTPROT.U);
    return ret;
}

static float32 Rcc_Hal_GetModuleClkSrcFreq(Rcc_ModuleClockSource clkSrc, Rcc_PerPllClkType perPllOutClkSel)
{
    float32 freq;

    freq = (float32)RCC_CLK_SOURCE_HSI;

    /* Get clock source frequency according to inpur arg clkSrc */
    switch (clkSrc)
    {
    case RCC_MODULECLOCKSOURCE_HSI:
        freq = (float32)RCC_CLK_SOURCE_HSI;
        break;
    case RCC_MODULECLOCKSOURCE_PERPLL:
        freq = Rcc_Hal_GetPerPllFreq(perPllOutClkSel);
        break;
    case RCC_MODULECLOCKSOURCE_HSE:
        freq = (float32)RCC_CLK_SOURCE_HSE;
        break;
    default:
    {
        /* Do nothing */
    }
    break;
    }
    return freq;
}

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: rcc_hal_c_REF_6 */
Rcc_ErrorFlag Rcc_Hal_EnableHse(uint32 timeoutTime)
{
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(0U < timeoutTime));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    Rcc_ErrorFlag flag;
    uint64 curTime;
    ret = TRUE;
    curTime = 0UL;
    flag = RCC_ERRORFLAG_TIMEOUT;

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->HSECON1.B.HSE_EN = RCC_BIT_ENABLE;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)RCC_BIT_ENABLE, (uint32)RCC_CLOCK->HSECON1.B.HSE_EN);

    /* Wait until HSE output stable clock */
    while (((curTime < ((uint64)(RCC_HSE_STBCOUNT + (uint64)timeoutTime))) && (RCC_ERRORFLAG_TIMEOUT == flag)))
    {
        /* Check if HSE is stable */
        /* #Violation: rcc_hal_c_REF_2 */
        if (RCC_BIT_ENABLE == RCC_CLOCK->HSECON1.B.HSE_READY)
        {
            flag = RCC_ERRORFLAG_SUCCESS;
        }
        /* Get current time */
        curTime++;
    }

    /* chip basic configuration initialization */
    /* 1. Flash RDT adjust for CPU work at 400MHz, ref. chip user manual table: P/DFLASH Read/Erase/Program Time Reference Values */
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_PFCON_REGADDR) |= 9UL;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, 9UL, (*(uint32 *)CHIP_BASIC_CFG_PFCON_REGADDR) & 9UL);
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DFCON_REGADDR) |= 3UL;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, 3UL, (*(uint32 *)CHIP_BASIC_CFG_DFCON_REGADDR) & 3UL);
#if defined(THA6_THA6412)
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_PFCON2_REGADDR) |= 9UL;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, 9UL, (*(uint32 *)CHIP_BASIC_CFG_PFCON2_REGADDR) & 9UL);
#endif

/*************************************************************************************************
 * 2. DSADC DSPB port configuration
 * [DIFF] MFCFG.COMVOSPBBYPASS(the register bit control DSADC DSPB port internal common mode voltage 
 *        output) reset value change from 0(DSPB common mode voltage output enable) in THA6206 
 *        version C to 1(DSPB common mode voltage output disable) in THA6206 version D.
 * 
 * User should configure DSADCx.MFCFG.COMVOSPBBYPASS as 1 in chip initialization phase scene while user 
 * defined THA6_THA6206 and THA6_THA6412. Please refer to THA6206 version C DSADC errata.
 * 
 * User can do not configure DSADCx.MFCFG.COMVOSPBBYPASS in chip initialization phase scene while 
 * user defined THA6_THA6206D, if user configure DSADCx.MFCFG.COMVOSPBBYPASS as 1 while defined 
 * THA6_THA6206D in chip initialization phase scene, it has no impact.
 *************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206)
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC0_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC0_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC1_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC1_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC2_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC2_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC3_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC3_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
#endif

#if defined(THA6_THA6412)
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC4_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC4_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC5_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC5_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC6_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC6_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC7_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC7_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC8_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC8_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
    /* #Violation: rcc_hal_c_REF_5 */
    (*(uint32 *)CHIP_BASIC_CFG_DSADC9_MFCFG_REGADDR) |= RCC_ENABLE_DSADC_CFG;
    /* #Violation: rcc_hal_c_REF_5 */
    ret = Rcc_Register_ReadBack_Check(ret, RCC_ENABLE_DSADC_CFG, (*(uint32 *)CHIP_BASIC_CFG_DSADC9_MFCFG_REGADDR) & RCC_ENABLE_DSADC_CFG);
#endif

    if (FALSE == ret)
    {
        flag = RCC_ERRORFLAG_FAIL;
    }

    return flag;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigSysPll(const Rcc_PllConfig *const pSysPllCfg)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SYSPLLCON1 sysPllCon1Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SYSPLLCON2 sysPllCon2Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SYSPLLCON3 sysPllCon3Val;

#if (INPUT_ARG_DETECT == STD_ON)
    float32 refClk;
    float32 foutVco;

    /* Get pll source clock*/
    if (RCC_PLLCLOCKSOURCE_HSI == pSysPllCfg->pllSource)
    {
        refClk = (float32)RCC_CLK_SOURCE_HSI;
    }
    else
    {
        refClk = (float32)RCC_CLK_SOURCE_HSE;
    }

    /* Check if pSysPllCfg is NULL_PTR */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pSysPllCfg));

    /* Check if PLL element is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllCfg->refDiv >= RCC_PLL_REFDIV_MIN) && (pSysPllCfg->refDiv <= RCC_PLL_REFDIV_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllCfg->postDiv1 >= RCC_PLL_POSTDIV_MIN) && (pSysPllCfg->postDiv1 <= RCC_PLL_POSTDIV_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllCfg->postDiv2 >= RCC_PLL_POSTDIV_MIN) && (pSysPllCfg->postDiv2 <= RCC_PLL_POSTDIV_MAX)));
#if defined(THA6_THA6104)
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllCfg->postDiv3 >= RCC_PLL_POSTDIV_MIN) && (pSysPllCfg->postDiv3 <= RCC_PLL_POSTDIV_MAX)));
#endif
    /* sysPllCon2 mode check */
    if (RCC_PLLMODE_INTEGER == pSysPllCfg->pllMode)
    {
        /* Check fbdiv in integer mode */
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)((pSysPllCfg->fbDiv >= RCC_PLL_INTEGER_MODE_FBDIV_MIN) &&
                         (pSysPllCfg->fbDiv <= RCC_SYSPLL_INTEGER_MODE_FBDIV_MAX)));
        /* calculate FOUTVCO */
        foutVco = (refClk * (float32)pSysPllCfg->fbDiv) / (float32)pSysPllCfg->refDiv;
        /* Check if FOUTVCO is in the specific range */
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)(foutVco >= (float32)RCC_FOUTVCO_MIN));
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)(foutVco <= (float32)RCC_FOUTVCO_MAX));
    }
    else
    {
        /* Check fbdiv in decimal mode */
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)((pSysPllCfg->fbDiv >= RCC_PLL_DECIMAL_MODE_FBDIV_MIN) &&
                         (pSysPllCfg->fbDiv <= RCC_PLL_DECIMAL_MODE_FBDIV_MAX)));
        /* calculate FOUTVCO */
        foutVco = (refClk * ((float32)pSysPllCfg->fbDiv + ((float32)pSysPllCfg->frac / RCC_PLL_FRAC_FACTOR))) /
                  (float32)pSysPllCfg->refDiv;
        /* Check if FOUTVCO is in the specific range */
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)(foutVco >= (float32)RCC_FOUTVCO_MIN));
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)(foutVco <= (float32)RCC_FOUTVCO_MAX));
    }
#endif /* INPUT_ARG_DETECT */

    /* Get system PLL control registers' vaule */
    /* #Violation: rcc_hal_c_REF_2 */
    sysPllCon1Val.U = RCC_CLOCK->SYSPLLCON1.U;
    /* #Violation: rcc_hal_c_REF_2 */
    sysPllCon2Val.U = RCC_CLOCK->SYSPLLCON2.U;
    /* #Violation: rcc_hal_c_REF_2 */
    sysPllCon3Val.U = RCC_CLOCK->SYSPLLCON3.U;

    /* Assign sysPllCon1 structure parameters */
    sysPllCon1Val.B.FOUTVCOPD = (uint32)RCC_PLLVCO_DISABLE;
    if (RCC_PLLMODE_INTEGER == pSysPllCfg->pllMode)
    {
        sysPllCon1Val.B.DACPD = RCC_BIT_ENABLE;
    }
    else
    {
        sysPllCon1Val.B.DACPD = RCC_BIT_DISABLE;
    }
    sysPllCon1Val.B.PLLMOD = (uint32)(pSysPllCfg->pllMode);
    /* must set bit as 0 */
    sysPllCon1Val.B.FOUT4PHASEPD = RCC_BIT_DISABLE;
    sysPllCon1Val.B.FOUTPOSTDIVPD = (uint32)RCC_PLLPOSTDIVIDER_ENABLE;
    sysPllCon1Val.B.PLLPD = RCC_BIT_ENABLE; /* Before modify PLL configuration, PLL should power down */

    /* Assign sysPllCon2 structure parameters */
    sysPllCon2Val.B.REFDIV = pSysPllCfg->refDiv;
    sysPllCon2Val.B.POSTDIV1 = pSysPllCfg->postDiv1;
    sysPllCon2Val.B.POSTDIV2 = pSysPllCfg->postDiv2;
#if defined(THA6_THA6104)
    sysPllCon2Val.B.POSTDIV3 = pSysPllCfg->postDiv3;
#endif
    sysPllCon2Val.B.FBDIV = pSysPllCfg->fbDiv;

    /* Assign sysPllCon3 structure parameters */
    sysPllCon3Val.B.FRAC = pSysPllCfg->frac;

    DISABLE_ALL_INTERRUPTS();
    /* Assign to relative registers  */
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON1.B.PLLPD = RCC_BIT_ENABLE; /* PLL power down */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PLLREFSEL.B.SYSPLL_REFSEL = (uint32)(pSysPllCfg->pllSource);
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON4.U = 0x0U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON2.U = sysPllCon2Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON3.U = sysPllCon3Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON1.U = sysPllCon1Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON1.B.PLLPD = RCC_BIT_DISABLE; /* PLL power on */
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(pSysPllCfg->pllSource), (uint32)RCC_CLOCK->PLLREFSEL.B.SYSPLL_REFSEL);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(sysPllCon2Val.U), (uint32)RCC_CLOCK->SYSPLLCON2.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(sysPllCon3Val.U), (uint32)RCC_CLOCK->SYSPLLCON3.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(0U), (uint32)RCC_CLOCK->SYSPLLCON4.U);
    /* Not wait READY */
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(sysPllCon1Val.U & 0xFFFEFFFEU), (uint32)(RCC_CLOCK->SYSPLLCON1.U & 0xFFFEFFFEU));

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigSysPllSsmod(const Rcc_PllSsmodConfig *const pSysPllSsmodCfg)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SYSPLLCON1 sysPllCon1Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SYSPLLCON2 sysPllCon2Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SYSPLLCON3 sysPllCon3Val;

    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SSMODCON1 ssModCon1Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SSMODCON2 ssModCon2Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SSMODCON3 ssModCon3Val;

#if (INPUT_ARG_DETECT == STD_ON)
    float32 refClk;
    float32 foutVco;

    /* Get pll source clock*/
    if (RCC_PLLCLOCKSOURCE_HSI == pSysPllSsmodCfg->pllSource)
    {
        refClk = (float32)RCC_CLK_SOURCE_HSI;
    }
    else
    {
        refClk = (float32)RCC_CLK_SOURCE_HSE;
    }

    /* Check if pSysPllCfg is NULL_PTR */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pSysPllSsmodCfg));

    /* Check if PLL element is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllSsmodCfg->refDiv >= RCC_PLL_REFDIV_MIN) && (pSysPllSsmodCfg->refDiv <= RCC_PLL_REFDIV_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllSsmodCfg->postDiv1 >= RCC_PLL_POSTDIV_MIN) && (pSysPllSsmodCfg->postDiv1 <= RCC_PLL_POSTDIV_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllSsmodCfg->postDiv2 >= RCC_PLL_POSTDIV_MIN) && (pSysPllSsmodCfg->postDiv2 <= RCC_PLL_POSTDIV_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(pSysPllSsmodCfg->divval <= RCC_SSMOD_DIVVAL_MAX));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllSsmodCfg->sperad >= RCC_SSMOD_SPREAD_MIN) && (pSysPllSsmodCfg->sperad <= RCC_SSMOD_SPREAD_MAX)));
#if defined(THA6_THA6104)
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllSsmodCfg->postDiv3 >= RCC_PLL_POSTDIV_MIN) && (pSysPllSsmodCfg->postDiv3 <= RCC_PLL_POSTDIV_MAX)));
#endif
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(RCC_PLLMODE_DECIMAL == pSysPllSsmodCfg->pllMode));

    /* Check fbdiv in decimal mode */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pSysPllSsmodCfg->intin >= RCC_PLL_DECIMAL_MODE_FBDIV_MIN) &&
                     (pSysPllSsmodCfg->intin <= RCC_PLL_DECIMAL_MODE_FBDIV_MAX)));
    /* calculate FOUTVCO */
    foutVco = (refClk * ((float32)pSysPllSsmodCfg->intin + ((float32)pSysPllSsmodCfg->fracin / RCC_PLL_FRAC_FACTOR))) /
              (float32)pSysPllSsmodCfg->refDiv;
    /* Check if FOUTVCO is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(foutVco >= (float32)RCC_FOUTVCO_MIN));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(foutVco <= (float32)RCC_FOUTVCO_MAX));

#endif /* INPUT_ARG_DETECT */

    /* Get system PLL SSMOD control registers' vaule */
    /* #Violation: rcc_hal_c_REF_2 */
    ssModCon1Val.U = RCC_CLOCK->SSMODCON1.U;
    /* #Violation: rcc_hal_c_REF_2 */
    ssModCon2Val.U = RCC_CLOCK->SSMODCON2.U;
    /* #Violation: rcc_hal_c_REF_2 */
    ssModCon3Val.U = RCC_CLOCK->SSMODCON3.U;

    /* Get system PLL control registers' vaule */
    /* #Violation: rcc_hal_c_REF_2 */
    sysPllCon1Val.U = RCC_CLOCK->SYSPLLCON1.U;
    /* #Violation: rcc_hal_c_REF_2 */
    sysPllCon2Val.U = RCC_CLOCK->SYSPLLCON2.U;
    /* #Violation: rcc_hal_c_REF_2 */
    sysPllCon3Val.U = RCC_CLOCK->SYSPLLCON3.U;

    /* Assign ssModCon1 structure parameters */
    ssModCon1Val.B.INTIN = pSysPllSsmodCfg->intin;
    ssModCon1Val.B.DIVVAL = pSysPllSsmodCfg->divval;
    ssModCon1Val.B.SPREAD = pSysPllSsmodCfg->sperad;
    ssModCon1Val.B.DISABLE_SSCG = 0U;
    ssModCon1Val.B.DOWNSPREAD = (uint32)pSysPllSsmodCfg->ssMode;
    ssModCon1Val.B.RESET = 0U;

    ssModCon2Val.B.RESETPTR = 0U;

    ssModCon3Val.B.FRACIN = pSysPllSsmodCfg->fracin;

    /* Assign sysPllCon1 structure parameters */
    sysPllCon1Val.B.FOUTVCOPD = (uint32)RCC_PLLVCO_DISABLE;
    sysPllCon1Val.B.DACPD = RCC_BIT_DISABLE;
    sysPllCon1Val.B.PLLMOD = (uint32)(pSysPllSsmodCfg->pllMode);
    /* must set bit as 0 */
    sysPllCon1Val.B.FOUT4PHASEPD = RCC_BIT_DISABLE;
    sysPllCon1Val.B.FOUTPOSTDIVPD = (uint32)RCC_PLLPOSTDIVIDER_ENABLE;
    sysPllCon1Val.B.PLLPD = RCC_BIT_ENABLE; /* Before modify PLL configuration, PLL should power down */

    /* Assign sysPllCon2 structure parameters */
    sysPllCon2Val.B.REFDIV = pSysPllSsmodCfg->refDiv;
    sysPllCon2Val.B.POSTDIV1 = pSysPllSsmodCfg->postDiv1;
    sysPllCon2Val.B.POSTDIV2 = pSysPllSsmodCfg->postDiv2;
#if defined(THA6_THA6104)
    sysPllCon2Val.B.POSTDIV3 = pSysPllSsmodCfg->postDiv3;
#endif
    sysPllCon2Val.B.FBDIV = pSysPllSsmodCfg->intin;

    /* Assign sysPllCon3 structure parameters */
    sysPllCon3Val.B.FRAC = pSysPllSsmodCfg->fracin;

    DISABLE_ALL_INTERRUPTS();
    /* Assign to relative registers  */
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON1.B.PLLPD = RCC_BIT_ENABLE; /* PLL power down */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PLLREFSEL.B.SYSPLL_REFSEL = (uint32)(pSysPllSsmodCfg->pllSource);
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SSMODCON3.U = ssModCon3Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SSMODCON2.U = ssModCon2Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SSMODCON1.U = ssModCon1Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON4.U = 0x1U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SSMODCON2.U = ssModCon2Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON2.U = sysPllCon2Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON3.U = sysPllCon3Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON1.U = sysPllCon1Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSPLLCON1.B.PLLPD = RCC_BIT_DISABLE; /* PLL power on */
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(pSysPllSsmodCfg->pllSource), (uint32)RCC_CLOCK->PLLREFSEL.B.SYSPLL_REFSEL);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(ssModCon3Val.U), (uint32)RCC_CLOCK->SSMODCON3.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(ssModCon2Val.U), (uint32)RCC_CLOCK->SSMODCON2.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(ssModCon1Val.U), (uint32)RCC_CLOCK->SSMODCON1.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, 0x1U, RCC_CLOCK->SYSPLLCON4.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(sysPllCon2Val.U), (uint32)RCC_CLOCK->SYSPLLCON2.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(sysPllCon3Val.U), (uint32)RCC_CLOCK->SYSPLLCON3.U);
    /* Not wait READY */
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(sysPllCon1Val.U & 0xFFFEFFFEU), (uint32)(RCC_CLOCK->SYSPLLCON1.U & 0xFFFEFFFEU));

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigPerPll(const Rcc_PllConfig *const pPerPllCfg)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_PERPLLCON1 perPllCon1Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_PERPLLCON2 perPllCon2Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_PERPLLCON3 perPllCon3Val;

#if (INPUT_ARG_DETECT == STD_ON)
    float32 refClk;
    float32 foutVco;
    /* Get pll source clock*/
    if (RCC_PLLCLOCKSOURCE_HSI == pPerPllCfg->pllSource)
    {
        refClk = (float32)RCC_CLK_SOURCE_HSI;
    }
    else
    {
        refClk = (float32)RCC_CLK_SOURCE_HSE;
    }

    /* Check if pPerPllCfg is NULL_PTR */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pPerPllCfg));
    /* Check if PLL element is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllCfg->refDiv >= RCC_PLL_REFDIV_MIN) && (pPerPllCfg->refDiv <= RCC_PLL_REFDIV_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllCfg->postDiv1 >= RCC_PLL_POSTDIV_MIN) && (pPerPllCfg->postDiv1 <= RCC_PLL_POSTDIV_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllCfg->postDiv2 >= RCC_PLL_POSTDIV_MIN) && (pPerPllCfg->postDiv2 <= RCC_PLL_POSTDIV_MAX)));
#if defined(THA6_THA6104)
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllCfg->postDiv3 >= RCC_PLL_POSTDIV_MIN) && (pPerPllCfg->postDiv3 <= RCC_PLL_POSTDIV_MAX)));
#endif
    /* perPllCon2 check */
    if (RCC_PLLMODE_INTEGER == pPerPllCfg->pllMode)
    {
        /* Check fbdiv in integer mode */
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)((pPerPllCfg->fbDiv >= RCC_PLL_INTEGER_MODE_FBDIV_MIN) &&
                         (pPerPllCfg->fbDiv <= RCC_PERPLL_INTEGER_MODE_FBDIV_MAX)));
        /* calculate FOUTVCO */
        foutVco = (refClk * (float32)pPerPllCfg->fbDiv) / (float32)pPerPllCfg->refDiv;
        /* Check if FOUTVCO is in the specific range */
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)((foutVco >= (float32)RCC_FOUTVCO_MIN) && (foutVco <= (float32)RCC_FOUTVCO_MAX)));
    }
    else
    {
        /* Check fbdiv in decimal mode */
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)((pPerPllCfg->fbDiv >= RCC_PLL_DECIMAL_MODE_FBDIV_MIN) &&
                         (pPerPllCfg->fbDiv <= RCC_PLL_DECIMAL_MODE_FBDIV_MAX)));
        /* calculate FOUTVCO */
        foutVco = ((refClk * ((float32)pPerPllCfg->fbDiv + ((float32)pPerPllCfg->frac / RCC_PLL_FRAC_FACTOR)))) /
                  (float32)pPerPllCfg->refDiv;
        /* Check if FOUTVCO is in the specific range */
        /* #Violation: rcc_hal_c_REF_3 */
        Assert((boolean)((foutVco >= (float32)RCC_FOUTVCO_MIN) && (foutVco <= (float32)RCC_FOUTVCO_MAX)));
    }
#endif /* INPUT_ARG_DETECT */

    /* Get peripheral PLL control registers' vaule */
    /* #Violation: rcc_hal_c_REF_2 */
    perPllCon1Val.U = RCC_CLOCK->PERPLLCON1.U;
    /* #Violation: rcc_hal_c_REF_2 */
    perPllCon2Val.U = RCC_CLOCK->PERPLLCON2.U;
    /* #Violation: rcc_hal_c_REF_2 */
    perPllCon3Val.U = RCC_CLOCK->PERPLLCON3.U;

    /* Assign perPllCon1 structure parameters */
    perPllCon1Val.B.FOUTVCOPD = (uint32)RCC_PLLVCO_DISABLE;
    if (RCC_PLLMODE_INTEGER == pPerPllCfg->pllMode)
    {
        perPllCon1Val.B.DACPD = RCC_BIT_ENABLE;
    }
    else
    {
        perPllCon1Val.B.DACPD = RCC_BIT_DISABLE;
    }
    perPllCon1Val.B.PLLMOD = (uint32)(pPerPllCfg->pllMode);
    perPllCon1Val.B.FOUT4PHASEPD = RCC_BIT_DISABLE;
    perPllCon1Val.B.FOUTPOSTDIVPD = RCC_BIT_DISABLE;
    perPllCon1Val.B.PLLPD = RCC_BIT_ENABLE; /* Before modify PLL configuration, PLL should power down */

    /* Assign perPllCon2 structure parameters */
    perPllCon2Val.B.REFDIV = pPerPllCfg->refDiv;
    perPllCon2Val.B.POSTDIV1 = pPerPllCfg->postDiv1;
    perPllCon2Val.B.POSTDIV2 = pPerPllCfg->postDiv2;
#if defined(THA6_THA6104)
    perPllCon2Val.B.POSTDIV3 = pPerPllCfg->postDiv3;
#endif
    perPllCon2Val.B.FBDIV = pPerPllCfg->fbDiv;

    /* Assign perPllCon3 structure parameters */
    perPllCon3Val.B.FRAC = pPerPllCfg->frac;

    DISABLE_ALL_INTERRUPTS();
    /* Assign to relative registers  */
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON1.B.PLLPD = RCC_BIT_ENABLE; /* PLL power down */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PLLREFSEL.B.PERPLL_REFSEL = (uint32)pPerPllCfg->pllSource;
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON4.U = 0x0U;
#endif
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON2.U = perPllCon2Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON3.U = perPllCon3Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON1.U = perPllCon1Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON1.B.PLLPD = RCC_BIT_DISABLE; /* PLL power on */
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(pPerPllCfg->pllSource), (uint32)RCC_CLOCK->PLLREFSEL.B.PERPLL_REFSEL);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(perPllCon2Val.U), (uint32)RCC_CLOCK->PERPLLCON2.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(perPllCon3Val.U), (uint32)RCC_CLOCK->PERPLLCON3.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(0U), (uint32)RCC_CLOCK->PERPLLCON4.U);
#endif
    /* Not wait READY */
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(perPllCon1Val.U & 0xFFFEFFFEU), (uint32)(RCC_CLOCK->PERPLLCON1.U & 0xFFFEFFFEU));

    return ret;
}

#if defined(THA6_THA6412) || defined(THA6_THA6104)
/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigPerPllSsmod(const Rcc_PllSsmodConfig *const pPerPllSsmodCfg)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_PERPLLCON1 perPllCon1Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_PERPLLCON2 perPllCon2Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_PERPLLCON3 perPllCon3Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SSMODCON1 ssModCon1Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SSMODCON2 ssModCon2Val;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SSMODCON3 ssModCon3Val;

#if (INPUT_ARG_DETECT == STD_ON)
    float32 refClk;
    float32 foutVco;

    /* Get pll source clock*/
    if (RCC_PLLCLOCKSOURCE_HSI == pPerPllSsmodCfg->pllSource)
    {
        refClk = (float32)RCC_CLK_SOURCE_HSI;
    }
    else
    {
        refClk = (float32)RCC_CLK_SOURCE_HSE;
    }

    /* Check if pSysPllCfg is NULL_PTR */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pPerPllSsmodCfg));

    /* Check if PLL element is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllSsmodCfg->refDiv >= RCC_PLL_REFDIV_MIN) && (pPerPllSsmodCfg->refDiv <= RCC_PLL_REFDIV_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllSsmodCfg->postDiv1 >= RCC_PLL_POSTDIV_MIN) && (pPerPllSsmodCfg->postDiv1 <= RCC_PLL_POSTDIV_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllSsmodCfg->postDiv2 >= RCC_PLL_POSTDIV_MIN) && (pPerPllSsmodCfg->postDiv2 <= RCC_PLL_POSTDIV_MAX)));
#if defined(THA6_THA6104)
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllSsmodCfg->postDiv3 >= RCC_PLL_POSTDIV_MIN) && (pPerPllSsmodCfg->postDiv3 <= RCC_PLL_POSTDIV_MAX)));
#endif
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(pPerPllSsmodCfg->divval <= RCC_SSMOD_DIVVAL_MAX));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllSsmodCfg->sperad >= RCC_SSMOD_SPREAD_MIN) && (pPerPllSsmodCfg->sperad <= RCC_SSMOD_SPREAD_MAX)));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(RCC_PLLMODE_DECIMAL == pPerPllSsmodCfg->pllMode));
    /* Check fbdiv in decimal mode */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((pPerPllSsmodCfg->intin >= RCC_PLL_DECIMAL_MODE_FBDIV_MIN) &&
                     (pPerPllSsmodCfg->intin <= RCC_PLL_DECIMAL_MODE_FBDIV_MAX)));
    /* calculate FOUTVCO */
    foutVco = (refClk * ((float32)pPerPllSsmodCfg->intin + ((float32)pPerPllSsmodCfg->fracin / RCC_PLL_FRAC_FACTOR))) /
              (float32)pPerPllSsmodCfg->refDiv;
    /* Check if FOUTVCO is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(foutVco >= (float32)RCC_FOUTVCO_MIN));
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(foutVco <= (float32)RCC_FOUTVCO_MAX));

#endif /* INPUT_ARG_DETECT */

    /* Get system PLL SSMOD control registers' vaule */
    /* #Violation: rcc_hal_c_REF_2 */
    ssModCon1Val.U = RCC_CLOCK->PERPLLSSMODCON1.U;
    /* #Violation: rcc_hal_c_REF_2 */
    ssModCon2Val.U = RCC_CLOCK->PERPLLSSMODCON2.U;
    /* #Violation: rcc_hal_c_REF_2 */
    ssModCon3Val.U = RCC_CLOCK->PERPLLSSMODCON3.U;

    /* Get system PLL control registers' vaule */
    /* #Violation: rcc_hal_c_REF_2 */
    perPllCon1Val.U = RCC_CLOCK->PERPLLCON1.U;
    /* #Violation: rcc_hal_c_REF_2 */
    perPllCon2Val.U = RCC_CLOCK->PERPLLCON2.U;
    /* #Violation: rcc_hal_c_REF_2 */
    perPllCon3Val.U = RCC_CLOCK->PERPLLCON3.U;

    /* Assign ssModCon1 structure parameters */
    ssModCon1Val.B.INTIN = pPerPllSsmodCfg->intin;
    ssModCon1Val.B.DIVVAL = pPerPllSsmodCfg->divval;
    ssModCon1Val.B.SPREAD = pPerPllSsmodCfg->sperad;
    ssModCon1Val.B.DISABLE_SSCG = 0U;
    ssModCon1Val.B.DOWNSPREAD = (uint32)pPerPllSsmodCfg->ssMode;
    ssModCon1Val.B.RESET = 0U;

    ssModCon2Val.B.RESETPTR = 0U;

    ssModCon3Val.B.FRACIN = pPerPllSsmodCfg->fracin;

    /* Assign sysPllCon1 structure parameters */
    perPllCon1Val.B.FOUTVCOPD = (uint32)RCC_PLLVCO_DISABLE;
    perPllCon1Val.B.DACPD = RCC_BIT_DISABLE;
    perPllCon1Val.B.PLLMOD = (uint32)(pPerPllSsmodCfg->pllMode);
    /* must set bit as 0 */
    perPllCon1Val.B.FOUT4PHASEPD = RCC_BIT_DISABLE;
    perPllCon1Val.B.FOUTPOSTDIVPD = (uint32)RCC_PLLPOSTDIVIDER_ENABLE;
    perPllCon1Val.B.PLLPD = RCC_BIT_ENABLE; /* Before modify PLL configuration, PLL should power down */

    /* Assign sysPllCon2 structure parameters */
    perPllCon2Val.B.REFDIV = pPerPllSsmodCfg->refDiv;
    perPllCon2Val.B.POSTDIV1 = pPerPllSsmodCfg->postDiv1;
    perPllCon2Val.B.POSTDIV2 = pPerPllSsmodCfg->postDiv2;
#if defined(THA6_THA6104)
    perPllCon2Val.B.POSTDIV3 = pPerPllSsmodCfg->postDiv3;
#endif
    perPllCon2Val.B.FBDIV = pPerPllSsmodCfg->intin;

    /* Assign sysPllCon3 structure parameters */
    perPllCon3Val.B.FRAC = pPerPllSsmodCfg->fracin;

    DISABLE_ALL_INTERRUPTS();
    /* Assign to relative registers  */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON1.B.PLLPD = RCC_BIT_ENABLE; /* PLL power down */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PLLREFSEL.B.PERPLL_REFSEL = (uint32)(pPerPllSsmodCfg->pllSource);
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLSSMODCON3.U = ssModCon3Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLSSMODCON2.U = ssModCon2Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLSSMODCON1.U = ssModCon1Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON4.U = 0x1U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLSSMODCON2.U = ssModCon2Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON2.U = perPllCon2Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON3.U = perPllCon3Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON1.U = perPllCon1Val.U;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->PERPLLCON1.B.PLLPD = RCC_BIT_DISABLE; /* PLL power on */
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(pPerPllSsmodCfg->pllSource), (uint32)RCC_CLOCK->PLLREFSEL.B.PERPLL_REFSEL);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(ssModCon3Val.U), (uint32)RCC_CLOCK->PERPLLSSMODCON3.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(ssModCon2Val.U), (uint32)RCC_CLOCK->PERPLLSSMODCON2.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(ssModCon1Val.U), (uint32)RCC_CLOCK->PERPLLSSMODCON1.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, 0x1U, RCC_CLOCK->PERPLLCON4.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(perPllCon2Val.U), (uint32)RCC_CLOCK->PERPLLCON2.U);
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(perPllCon3Val.U), (uint32)RCC_CLOCK->PERPLLCON3.U);
    /* Not wait READY */
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(perPllCon1Val.U & 0xFFFEFFFEU), (uint32)(RCC_CLOCK->PERPLLCON1.U & 0xFFFEFFFEU));

    return ret;
}
#endif

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigCpuClk(Rcc_CpuClockSource cpuClkSrc, uint8 clkDiv)
{
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SYSCLKCON1 cpuClkCon;
    ret = TRUE;
    cpuClkCon.U = 0U;

    /* Assign cpuClkCon structure parameters from input args */
    cpuClkCon.B.SYSCLKSEL = (uint32)cpuClkSrc;
    cpuClkCon.B.CPU_DIV = clkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSCLKCON1.U = cpuClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(cpuClkCon.U), (uint32)(RCC_CLOCK->SYSCLKCON1.U & 0xFFFFFEFFU));

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigBusClk(uint8 sysClkDiv, uint8 axiClkDiv, uint16 ahbApbClkDiv)
{
    /* The source of system clock, AXI clock, AHB clcok, and APB clock is CPU clock*/
    /* AHB clock division factor is same as APB clcok's */
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_SYSCLKCON2 busClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((sysClkDiv <= RCC_SYSCLKDIV_MAX) && (axiClkDiv <= RCC_AXICLKDIV_MAX) &&
                     (ahbApbClkDiv <= RCC_AHBCLKDIV_MAX)));
#endif /* INPUT_ARG_DETECT */

    busClkCon.U = 0U;

    /* Assign busClkCon structure parameters from input args */
    busClkCon.B.AHB_DIV = ahbApbClkDiv;
    busClkCon.B.AXI_DIV = axiClkDiv;
    busClkCon.B.SYS_DIV = sysClkDiv;

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();

    /* Assign value to register */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSCLKCON2.U = busClkCon.U;
    /* Enable div config above, and wait for clock output stablely */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSCLKCON4.B.BUSDIV_UPDATE = RCC_BIT_ENABLE;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(busClkCon.U), (uint32)(RCC_CLOCK->SYSCLKCON2.U));
    /* #Violation: rcc_hal_c_REF_5 */
    /* #Violation: rcc_hal_c_REF_12 */
    /* #Violation: rcc_hal_c_REF_10 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(RCC_BIT_DISABLE), (uint32)(RCC_CLOCK->SYSCLKCON4.B.BUSDIV_UPDATE));
    

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigGtmClk(Rcc_ModuleClockSource clkSrc, uint8 gtmClkDiv)
{
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_CLKCON1 gtmClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(gtmClkDiv <= RCC_GTMCLKDIV_MAX));
#endif /* INPUT_ARG_DETECT */

    gtmClkCon.U = 0U;

    /* Assign gtmClkCon structure parameters from input args */
    gtmClkCon.B.GTM_CLKSEL = (uint32)clkSrc;
    gtmClkCon.B.GTM_DIV = gtmClkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();

    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON1.U = gtmClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(gtmClkCon.U), (uint32)(RCC_CLOCK->CLKCON1.U));
    

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigQspiClk(Rcc_ModuleClockSource clkSrc, uint8 qspiClkDiv)
{
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_CLKCON2 qspiClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(qspiClkDiv <= RCC_SPICLKDIV_MAX));
#endif /* INPUT_ARG_DETECT */

    qspiClkCon.U = 0U;

    /* Assign qspiClkCon structure parameters from input args */
    qspiClkCon.B.QSPI_CLKSEL = (uint32)clkSrc;
    qspiClkCon.B.QSPI_DIV = qspiClkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();

    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON2.U = qspiClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(qspiClkCon.U), (uint32)(RCC_CLOCK->CLKCON2.U));
    

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigEspiClk(Rcc_ModuleClockSource clkSrc, uint8 espiClkDiv)
{
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_CLKCON3 espiClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(espiClkDiv <= RCC_SPICLKDIV_MAX));
#endif /* INPUT_ARG_DETECT */

    espiClkCon.U = 0U;

    /* Assign espiClkCon structure parameters from input args */
    espiClkCon.B.ESPI_CLKSEL = (uint32)clkSrc;
    espiClkCon.B.ESPI_DIV = espiClkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON3.U = espiClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(espiClkCon.U), (uint32)(RCC_CLOCK->CLKCON3.U));
    

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigCanClk(Rcc_ModuleClockSource clkSrc, uint8 canClkDiv)
{
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_CLKCON4 canClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(canClkDiv <= RCC_CANCLKDIV_MAX));
#endif /* INPUT_ARG_DETECT */

    canClkCon.U = 0U;

    /* Assign canClkCon structure parameters from input args */
    canClkCon.B.CAN_CCLKSEL = (uint32)clkSrc;
    canClkCon.B.CAN_DIV = canClkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON4.U = canClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(canClkCon.U), (uint32)(RCC_CLOCK->CLKCON4.U));

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigFcClk(Rcc_ModuleClockSource clkSrc, uint8 fcClkDiv)
{
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_CLKCON11 fcClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(fcClkDiv <= RCC_FCCLKDIV_MAX));
#endif /* INPUT_ARG_DETECT */

    fcClkCon.U = 0U;

    /* Assign fcClkCon structure parameters from input args */
    fcClkCon.B.FC_CLKSEL = (uint32)clkSrc;
    fcClkCon.B.FC_DIV = fcClkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON11.U = fcClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(fcClkCon.U), (uint32)(RCC_CLOCK->CLKCON11.U));

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigSaradcClk(Rcc_ModuleClockSource clkSrc)
{
    boolean ret;
    ret = TRUE;
    /* Assign value to register */
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON5.B.SARADC_CLKSEL = (uint32)clkSrc;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(clkSrc), (uint32)(RCC_CLOCK->CLKCON5.B.SARADC_CLKSEL));
    
    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigRdcDsadcClk(Rcc_ModuleClockSource clkSrc, uint8 rdcClkDiv, uint8 dsadcClkDiv)
{
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_CLKCON6 rdcDsadcClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)((rdcClkDiv <= RCC_RDC_DSADCCLKDIV_MAX) && (dsadcClkDiv <= RCC_RDC_DSADCCLKDIV_MAX)));
#endif /* INPUT_ARG_DETECT */

    rdcDsadcClkCon.U = 0U;

    /* Assign saradcClkCon structure parameters from input args */
    rdcDsadcClkCon.B.RDCDSADC_CLKSEL = (uint32)clkSrc;
    /* DSADC and RDC use same clock source */
    rdcDsadcClkCon.B.DSADC_DIV = dsadcClkDiv;
    rdcDsadcClkCon.B.RDC_DIV = rdcClkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON6.U = rdcDsadcClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(rdcDsadcClkCon.U), (uint32)(RCC_CLOCK->CLKCON6.U));
    
    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigMscClk(Rcc_ModuleClockSource clkSrc)
{
    boolean ret;
    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    /* Select MSC clock source. Note: There is no divider for MSC in RCC */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON7.B.MSC_CLKSEL = (uint32)clkSrc;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(clkSrc), (uint32)(RCC_CLOCK->CLKCON7.B.MSC_CLKSEL));
    

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigWdtClk(Rcc_ModuleClockSource clkSrc, uint8 wdtClkDiv)
{
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_CLKCON8 wdtClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(wdtClkDiv <= RCC_WDTCLKDIV_MAX));
#endif /* INPUT_ARG_DETECT */

    wdtClkCon.U = 0U;

    /* Assign cpuwdtClkCon structure parameters from input args */
    wdtClkCon.B.CPUWDT_CLKSEL = (uint32)clkSrc;
    wdtClkCon.B.CPUWDT_DIV = wdtClkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON8.U = wdtClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(wdtClkCon.U), (uint32)(RCC_CLOCK->CLKCON8.U));
    

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigIpcntClk(Rcc_IpcntClockSource clkSrc, uint8 ipcntClkDiv)
{
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_CLKCON9 ipcntClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(ipcntClkDiv <= RCC_IPCNTCLKDIV_MAX));
#endif /* INPUT_ARG_DETECT */

    ipcntClkCon.U = 0U;

    /* Assign ipcntClkCon structure parameters from input args */
    ipcntClkCon.B.IPCNT_CLKSEL = (uint32)clkSrc;
    ipcntClkCon.B.IPCNT_DIV = ipcntClkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON9.U = ipcntClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(ipcntClkCon.U), (uint32)(RCC_CLOCK->CLKCON9.U));
    
    return ret;
}

#if defined(THA6_THA6104)
/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigAsiBaudBusClk(Rcc_ModuleClockSource clkSrc, uint16 asiBaudBusClkDiv)
{
    /* #Violation: rcc_hal_c_REF_3, for CHIP THA6206 and THA6412 */
    boolean ret;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_CLKCON10 asiBaudBusClkCon;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(asiBaudBusClkDiv <= RCC_ASIBAUDBUSCLKDIV_MAX));
#endif /* INPUT_ARG_DETECT */

    asiBaudBusClkCon.U = 0;

    /* Assign asiBaudBusClkCon structure parameters from input args */
    asiBaudBusClkCon.B.ASIBAUD_CLKSEL = (uint32)clkSrc;
    asiBaudBusClkCon.B.ASIBAUDBUS_DIV = asiBaudBusClkDiv;

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->CLKCON10.U = asiBaudBusClkCon.U;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(asiBaudBusClkCon.U), (uint32)(RCC_CLOCK->CLKCON10.U) & ~(0xFFU));
    

    return ret;
}
#endif

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigBaseTimerClk(Rcc_BasetimerIdx baseTimIdx, Rcc_ModuleClockSource clkSrc, uint16 clkDiv)
{
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(RCC_BASETIMERCLKDIV_MIN <= clkDiv));
#endif /* INPUT_ARG_DETECT */
    boolean ret;
    ret = TRUE;
    /* BaseTimer clock source is system clock */
    /* Set corresponding basetimer div according to args */
    switch (baseTimIdx)
    {
    case RCC_BASETIMERIDX_1:
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM1CON.B.TIM1_CLKSEL = (uint32)clkSrc;
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM1CON.B.DIV = clkDiv;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, (uint32)(((uint32)clkSrc << 16U) | (uint32)clkDiv), (uint32)(RCC_CLOCK->CLKTIM1CON.U));
        break;
    case RCC_BASETIMERIDX_2:
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM2CON.B.TIM2_CLKSEL = (uint32)clkSrc;
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM2CON.B.DIV = clkDiv;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, (uint32)(((uint32)clkSrc << 16U) | (uint32)clkDiv), (uint32)(RCC_CLOCK->CLKTIM2CON.U));
        break;
    case RCC_BASETIMERIDX_3:
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM3CON.B.TIM3_CLKSEL = (uint32)clkSrc;
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM3CON.B.DIV = clkDiv;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, (uint32)(((uint32)clkSrc << 16U) | (uint32)clkDiv), (uint32)(RCC_CLOCK->CLKTIM3CON.U));
        break;
    case RCC_BASETIMERIDX_4:
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM4CON.B.TIM4_CLKSEL = (uint32)clkSrc;
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM4CON.B.DIV = clkDiv;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, (uint32)(((uint32)clkSrc << 16U) | (uint32)clkDiv), (uint32)(RCC_CLOCK->CLKTIM4CON.U));
        break;
    case RCC_BASETIMERIDX_5:
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM5CON.B.TIM5_CLKSEL = (uint32)clkSrc;
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM5CON.B.DIV = clkDiv;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, (uint32)(((uint32)clkSrc << 16U) | (uint32)clkDiv), (uint32)(RCC_CLOCK->CLKTIM5CON.U));
        break;
    case RCC_BASETIMERIDX_6:
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM6CON.B.TIM6_CLKSEL = (uint32)clkSrc;
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKTIM6CON.B.DIV = clkDiv;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, (uint32)(((uint32)clkSrc << 16U) | (uint32)clkDiv), (uint32)(RCC_CLOCK->CLKTIM6CON.U));
        break;
    default:
    {
        /* Do nothing */
    }
    break;
    }
    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ConfigStmClk(uint8 stmClkDiv)
{
    boolean ret;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if div factor is in the specific range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(stmClkDiv <= RCC_STMCLKDIV_MAX));
#endif /* INPUT_ARG_DETECT */

    DISABLE_ALL_INTERRUPTS();
    /* Assign value to register */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_CLOCK->SYSCLKCON5.B.CPU_CNTCLKDIV = stmClkDiv;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)(stmClkDiv), (uint32)(RCC_CLOCK->SYSCLKCON5.B.CPU_CNTCLKDIV));
    

    return ret;
}

boolean Rcc_Hal_SetModuleClk(Rcc_ModuleClkType moduleType, Rcc_ModuleClkSet clkSet)
{
    boolean ret;
    uint32 regVal;
    uint32 regGroupIdx;
    uint32 setBit;
    uint32 clearBit;
    uint32 clkEnRegAddr;
    ret = TRUE;
    /* Divide moduleType into corresponding group related with RCC registers */
    regGroupIdx = (uint32)moduleType / RCC_REG_WIDTH;

    /* Control bit value in one register */
    setBit = (uint32)1U << ((uint32)moduleType % RCC_REG_WIDTH);
    clearBit = ~setBit;
    if ((moduleType >= RCC_MODULECLKTYPE_DSADC0CLK) && (moduleType <= RCC_MODULECLKTYPE_DSADC9CLK))
    {
        setBit = RCC_ENABLE_ALLDSADC_CLK; /* All DSADC clock should be enable together */
    }

    /* Get clock enable register address */
    if (regGroupIdx < (uint32)RCC_MODULECLKWDT)
    {
        /* #Violation: rcc_hal_c_REF_2 */
        /* #Violation: rcc_hal_c_REF_2 */
        clkEnRegAddr = (uint32)&RCC_CLOCK->CLKEN1.U + (regGroupIdx * 4U);
        DISABLE_ALL_INTERRUPTS();
        ret &= Cpuwdt_Hal_ClearEndinit();
        
        if (clkSet == RCC_MODULECLK_ENABLE)
        {
            /* Enbale selected module clock */
            /* #Violation: rcc_hal_c_REF_2 */
            regVal = (*(volatile uint32 *)clkEnRegAddr);
            regVal |= setBit;
            /* #Violation: rcc_hal_c_REF_2 */
            (*(volatile uint32 *)clkEnRegAddr) = regVal;
        }
        else
        {
            /* Disable selected module clock */
            /* #Violation: rcc_hal_c_REF_2 */
            regVal = (*(volatile uint32 *)clkEnRegAddr);
            regVal &= clearBit;
            /* #Violation: rcc_hal_c_REF_2 */
            (*(volatile uint32 *)clkEnRegAddr) = regVal;
        }
        ret &= Cpuwdt_Hal_SetEndinit();
        ENABLE_ALL_INTERRUPTS();
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, regVal, (*(volatile uint32 *)clkEnRegAddr));
        

    }
    /* Set WDT clock enable */
    else if ((uint32)RCC_MODULECLKWDT == regGroupIdx)
    {
        ret = Rcc_Hal_EnableWdtClk(clkSet, setBit);
    }
    else
    {
        /* Do nothing */
    }
    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
Rcc_PllStatus Rcc_Hal_GetPllStatus(Rcc_PllType pllType)
{
    Rcc_PllStatus pllSta;
    if (RCC_PLLTYPE_SYS == pllType)
    {
        /* #Violation: rcc_hal_c_REF_3 */
        /* #Violation: rcc_hal_c_REF_5 */
        pllSta = (Rcc_PllStatus)RCC_CLOCK->SYSPLLCON1.B.PLLRDY;
    }
    else
    {
        /* #Violation: rcc_hal_c_REF_3 */
        /* #Violation: rcc_hal_c_REF_5 */
        pllSta = (Rcc_PllStatus)RCC_CLOCK->PERPLLCON1.B.PLLRDY;
    }
    return pllSta;
}

/* #Violation: rcc_hal_c_REF_16 */
float32 Rcc_Hal_GetSysPllFreq(void)
{
    float32 pllClk;
    float32 refClk;
    uint32 refClkSel;
    uint32 refDivVal;
    uint32 postDiv1Val;
    uint32 postDiv2Val;
    uint32 pllMode;
    uint32 fbDivVal;
    uint32 fracVal;
    uint32 ssmodEn;
    /* #Violation: rcc_hal_c_REF_2 */
    pllMode = RCC_CLOCK->SYSPLLCON1.B.PLLMOD;
    /* #Violation: rcc_hal_c_REF_2 */
    refClkSel = RCC_CLOCK->PLLREFSEL.B.SYSPLL_REFSEL;
    /* #Violation: rcc_hal_c_REF_2 */
    refDivVal = RCC_CLOCK->SYSPLLCON2.B.REFDIV;
    /* #Violation: rcc_hal_c_REF_2 */
    postDiv2Val = RCC_CLOCK->SYSPLLCON2.B.POSTDIV2;
    /* #Violation: rcc_hal_c_REF_2 */
    postDiv1Val = RCC_CLOCK->SYSPLLCON2.B.POSTDIV1;
    /* #Violation: rcc_hal_c_REF_2 */
    fbDivVal = RCC_CLOCK->SYSPLLCON2.B.FBDIV;
    /* #Violation: rcc_hal_c_REF_2 */
    fracVal = RCC_CLOCK->SYSPLLCON3.B.FRAC;
    /* #Violation: rcc_hal_c_REF_2 */
    ssmodEn = RCC_CLOCK->SYSPLLCON4.B.SYSPLL_MODE;

    /* Check if used SSMOD, if true, then modify the division factor */
    if (1U == ssmodEn)
    {
        /* #Violation: rcc_hal_c_REF_2 */
        fbDivVal = RCC_CLOCK->SSMODCON1.B.INTIN;
        /* #Violation: rcc_hal_c_REF_2 */
        fracVal = RCC_CLOCK->SSMODCON3.B.FRACIN;
    }

    /* Get pll source clock*/
    if ((uint32)RCC_PLLCLOCKSOURCE_HSI == refClkSel)
    {
        refClk = (float32)RCC_CLK_SOURCE_HSI;
    }
    else
    {
        refClk = (float32)RCC_CLK_SOURCE_HSE;
    }

    /* Calculate PLL output clock frequncy according to PLL mode */
    if ((uint32)RCC_PLLMODE_INTEGER == pllMode)
    {
        if ((refDivVal != 0U) && (postDiv2Val != 0U) && (postDiv1Val != 0U) && (fbDivVal >= RCC_PLL_INTEGER_MODE_FBDIV_MIN) &&
            (fbDivVal <= RCC_SYSPLL_INTEGER_MODE_FBDIV_MAX))
        {
            /* calculate PLL output clock in integer mode: PLL_CLK = REF_CLK*FBDIV / (REFDIV*POSTDIV1*POSTDIV2) */
            /* calculate PLL FOUTPOSTDIV clock frequency */
            pllClk = (refClk * (float32)fbDivVal) / ((float32)refDivVal * (float32)postDiv2Val * (float32)postDiv1Val);
            /* calculate PLL FOUT1PH0 clock frequency */
            pllClk /= 2.0F;
        }
        else
        {
            pllClk = refClk;
        }
    }
    else
    {
        if ((refDivVal != 0U) && (postDiv2Val != 0U) && (postDiv1Val != 0U) && (fbDivVal >= RCC_PLL_DECIMAL_MODE_FBDIV_MIN) &&
            (fbDivVal <= RCC_PLL_DECIMAL_MODE_FBDIV_MAX))
        {
            /* calculate PLL output clock in decimal mode: PLL_CLK = REF_CLK*(FBDIV+FRAC/(2^24)) /
             * (REFDIV*POSTDIV1*POSTDIV2) */
            /* calculate PLL FOUTPOSTDIV clock frequency */
            pllClk = (refClk * ((float32)fbDivVal + ((float32)fracVal / RCC_PLL_FRAC_FACTOR))) /
                     ((float32)refDivVal * (float32)postDiv2Val * (float32)postDiv1Val);
            /* calculate PLL FOUT1PH0 clock frequency */
            pllClk /= 2.0F;
        }
        else
        {
            pllClk = refClk;
        }
    }

    return pllClk;
}

/* #Violation: rcc_hal_c_REF_16 */
float32 Rcc_Hal_GetPerPllFreq(Rcc_PerPllClkType OutClkSel)
{
    float32 pllClk;
    float32 refClk;
    uint32 refClkSel;
    uint32 refDivVal;
    uint32 postDiv1Val;
    uint32 postDiv2Val;
#if defined(THA6_THA6104)
    uint32 postDiv3Val;
#endif
    uint32 pllMode;
    uint32 fbDivVal;
    uint32 fracVal;

#if defined(THA6_THA6104) || defined(THA6_THA6412)
    uint32 ssmodEn;
#endif

    /* #Violation: rcc_hal_c_REF_2 */
    refClkSel = RCC_CLOCK->PLLREFSEL.B.PERPLL_REFSEL;
    /* #Violation: rcc_hal_c_REF_2 */
    pllMode = RCC_CLOCK->PERPLLCON1.B.PLLMOD;
    /* #Violation: rcc_hal_c_REF_2 */
    refDivVal = RCC_CLOCK->PERPLLCON2.B.REFDIV;
#if defined(THA6_THA6104)
    /* #Violation: rcc_hal_c_REF_2 */
    postDiv3Val = RCC_CLOCK->PERPLLCON2.B.POSTDIV3;
#endif
    /* #Violation: rcc_hal_c_REF_2 */
    postDiv2Val = RCC_CLOCK->PERPLLCON2.B.POSTDIV2;
    /* #Violation: rcc_hal_c_REF_2 */
    postDiv1Val = RCC_CLOCK->PERPLLCON2.B.POSTDIV1;
    /* #Violation: rcc_hal_c_REF_2 */
    fbDivVal = RCC_CLOCK->PERPLLCON2.B.FBDIV;
    /* #Violation: rcc_hal_c_REF_2 */
    fracVal = RCC_CLOCK->PERPLLCON3.B.FRAC;

#if defined(THA6_THA6104) || defined(THA6_THA6412)
    /* #Violation: rcc_hal_c_REF_2 */
    ssmodEn = RCC_CLOCK->PERPLLCON4.B.PERPLL_MODE;

    /* Check if used SSMOD, if true, then modify the division factor */
    if (1U == ssmodEn)
    {
        /* #Violation: rcc_hal_c_REF_2 */
        fbDivVal = RCC_CLOCK->PERPLLSSMODCON1.B.INTIN;
        /* #Violation: rcc_hal_c_REF_2 */
        fracVal = RCC_CLOCK->PERPLLSSMODCON3.B.FRACIN;
    }
#endif
    /* Get PLL clock source */
    if ((uint32)RCC_PLLCLOCKSOURCE_HSI == refClkSel)
    {
        refClk = (float32)RCC_CLK_SOURCE_HSI;
    }
    else
    {
        refClk = (float32)RCC_CLK_SOURCE_HSE;
    }

    /* Calculate PLL output clock frequncy according to PLL mode */
    if ((uint32)RCC_PLLMODE_INTEGER == pllMode)
    {
        if ((refDivVal != 0U) && (postDiv2Val != 0U) && (postDiv1Val != 0U) && (fbDivVal >= RCC_PLL_INTEGER_MODE_FBDIV_MIN) &&
            (fbDivVal <= RCC_PERPLL_INTEGER_MODE_FBDIV_MAX))
        {
            /* calculate PLL output clock in integer mode: PLL_CLK = REF_CLK*FBDIV / (REFDIV*POSTDIV1*POSTDIV2) */
            /* calculate PLL FOUTPOSTDIV clock frequency */
            pllClk = (refClk * (float32)fbDivVal) / ((float32)refDivVal * (float32)postDiv2Val * (float32)postDiv1Val);

            if (RCC_PERPLLCLKTYPE_HIGH == OutClkSel)
            {
                /* calculate PLL FOUT1PH0 clock frequency */
                pllClk /= 2.0F;
            }
            else
            {
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
                /* calculate PLL FOUT2 clock frequency */
                pllClk /= 4.0F;
#endif
#if defined(THA6_THA6104)
                /* calculate PLL FOUT5 clock frequency */
                if (0U != postDiv3Val)
                {
                    pllClk /= ((float32)postDiv3Val);
                }
#endif
            }
        }
        else
        {
            pllClk = refClk;
        }
    }
    else
    {
        if ((refDivVal != 0U) && (postDiv2Val != 0U) && (postDiv1Val != 0U) && (fbDivVal >= RCC_PLL_DECIMAL_MODE_FBDIV_MIN) &&
            (fbDivVal <= RCC_PLL_DECIMAL_MODE_FBDIV_MAX))
        {
            /* calculate PLL output clock in decimal mode: PLL_CLK = REF_CLK*(FBDIV+FRAC/(2^24)) /
             * (REFDIV*POSTDIV1*POSTDIV2) */
            pllClk = (refClk * ((float32)fbDivVal + ((float32)fracVal / RCC_PLL_FRAC_FACTOR))) /
                     ((float32)refDivVal * (float32)postDiv2Val * (float32)postDiv1Val);

            if (RCC_PERPLLCLKTYPE_HIGH == OutClkSel)
            {
                /* calculate PLL FOUT1PH0 clock frequency */
                pllClk /= 2.0F;
            }
            else
            {
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
                /* calculate PLL FOUT2 clock frequency */
                pllClk /= 4.0F;
#endif
#if defined(THA6_THA6104)
                /* calculate PLL FOUT5 clock frequency */
                if (0U != postDiv3Val)
                {
                    pllClk /= ((float32)postDiv3Val);
                }
#endif
            }
        }
        else
        {
            pllClk = refClk;
        }
    }

    return pllClk;
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetSysClkSrcFreq(void)
{

    float32 clkFreq;
    uint32 clkSelVal;

    clkFreq = (float32)RCC_CLK_SOURCE_HSI;
    /* #Violation: rcc_hal_c_REF_2 */
    clkSelVal = RCC_CLOCK->SYSCLKCON1.B.SYSCLKSEL;

    /* Get clock source frequency according to SYSCLKSEL register */
    switch (clkSelVal)
    {
    case (uint32)RCC_CPUCLOCKSOURCE_HSI:
        clkFreq = (float32)RCC_CLK_SOURCE_HSI;
        break;
    case (uint32)RCC_CPUCLOCKSOURCE_SYSPLL:
        clkFreq = Rcc_Hal_GetSysPllFreq();
        break;
    case (uint32)RCC_CPUCLOCKSOURCE_HSE:
        clkFreq = (float32)RCC_CLK_SOURCE_HSE;
        break;
    default:
    {
        /* Do nothing */
    }
    break;
    }

    return clkFreq;

}

/* #Violation: rcc_hal_c_REF_16 */
float32 Rcc_Hal_GetCpuClkFreq(void)
{
    float32 freq;
    float32 clkFreq;
    uint32 clkDiv;
    uint32 clkSelVal;

    clkFreq = (float32)RCC_CLK_SOURCE_HSI;

    /* Get CPU clock source and division factor */
    /* #Violation: rcc_hal_c_REF_2 */
    clkSelVal = RCC_CLOCK->SYSCLKCON1.B.SYSCLKSEL;
    /* #Violation: rcc_hal_c_REF_2 */
    clkDiv = (uint32)RCC_CLOCK->SYSCLKCON1.B.CPU_DIV + 1U;

    /* Get clock source frequency according to SYSCLKSEL register */
    switch (clkSelVal)
    {
    case (uint32)RCC_CPUCLOCKSOURCE_HSI:
        clkFreq = (float32)RCC_CLK_SOURCE_HSI;
        break;
    case (uint32)RCC_CPUCLOCKSOURCE_SYSPLL:
        clkFreq = Rcc_Hal_GetSysPllFreq();
        break;
    case (uint32)RCC_CPUCLOCKSOURCE_HSE:
        clkFreq = (float32)RCC_CLK_SOURCE_HSE;
        break;
    default:
    {
        /* Do nothing */
    }
    break;
    }

    /* Calcalate CPU clock frequency */
    freq = clkFreq / (float32)clkDiv;
    return freq;
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetSysClkFreq(void)
{
    float32 freq;
    float32 clkFreq;
    uint32 clkDiv;

    /* System bus clock source is CPU clock */
    clkFreq = Rcc_Hal_GetCpuClkFreq();
    /* #Violation: rcc_hal_c_REF_2 */
    clkDiv = (uint32)RCC_CLOCK->SYSCLKCON2.B.SYS_DIV + 1U;

    /* Calcalate System bus clock frequency */
    freq = clkFreq / (float32)clkDiv;
    return freq;
}


/* #Violation: rcc_hal_c_REF_16 */
/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetAxiClkFreq(void)
{
    float32 freq;
    float32 clkFreq;
    uint32 clkDiv;

    /* AXI bus clock source is CPU clock */
    clkFreq = Rcc_Hal_GetCpuClkFreq();
    /* #Violation: rcc_hal_c_REF_2 */
    clkDiv = (uint32)RCC_CLOCK->SYSCLKCON2.B.AXI_DIV + 1U;

    /* Calcalate AXI bus clock frequency */
    freq = clkFreq / (float32)clkDiv;
    return freq;
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetAhbApbClkFreq(void)
{
    float32 freq;
    float32 clkFreq;
    uint32 clkDiv;

    /* AHB and APB bus clock source is CPU clock */
    clkFreq = Rcc_Hal_GetCpuClkFreq();
    /* #Violation: rcc_hal_c_REF_2 */
    clkDiv = (uint32)RCC_CLOCK->SYSCLKCON2.B.AHB_DIV + 1U;

    /* Calcalate AXI bus clock frequency */
    freq = clkFreq / (float32)clkDiv;
    return freq;
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetEspiClkFreq(void)
{
    float32 freq;
    uint32 clkSelVal;
    uint32 clkDiv;

    /* Get ESPI clock source and division factor */
    /* #Violation: rcc_hal_c_REF_2 */
    clkSelVal = RCC_CLOCK->CLKCON3.B.ESPI_CLKSEL;
    /* #Violation: rcc_hal_c_REF_2 */
    clkDiv = (uint32)RCC_CLOCK->CLKCON3.B.ESPI_DIV + 1U;
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    /* Calcalate ESPI clock frequency */
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSelVal, RCC_PERPLLCLKTYPE_LOW) / (float32)clkDiv;
#endif
#if defined(THA6_THA6104)
    /* Calcalate ESPI clock frequency */
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSelVal, RCC_PERPLLCLKTYPE_HIGH) / (float32)clkDiv;
#endif
    return freq;
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetBasetimerClkFreq(Rcc_BasetimerIdx baseTimIdx)
{
    float32 freq;
    uint32 clkDivVal;
    Rcc_ModuleClockSource clkSel;

    clkSel = RCC_MODULECLOCKSOURCE_PERPLL;
    clkDivVal = 1U;

    /* Select clock frequency division factor according to input args */
    switch (baseTimIdx)
    {
    case RCC_BASETIMERIDX_1:
        /* #Violation: rcc_hal_c_REF_5 */
        /* #Violation: rcc_hal_c_REF_3 */
        clkSel = (Rcc_ModuleClockSource)RCC_CLOCK->CLKTIM1CON.B.TIM1_CLKSEL;
        /* #Violation: rcc_hal_c_REF_2 */
        clkDivVal = (uint32)RCC_CLOCK->CLKTIM1CON.B.DIV + 1U;
        break;
    case RCC_BASETIMERIDX_2:
        /* #Violation: rcc_hal_c_REF_3 */
        /* #Violation: rcc_hal_c_REF_5 */
        clkSel = (Rcc_ModuleClockSource)RCC_CLOCK->CLKTIM2CON.B.TIM2_CLKSEL;
        /* #Violation: rcc_hal_c_REF_2 */
        clkDivVal = (uint32)RCC_CLOCK->CLKTIM2CON.B.DIV + 1U;
        break;
    case RCC_BASETIMERIDX_3:
        /* #Violation: rcc_hal_c_REF_3 */
        /* #Violation: rcc_hal_c_REF_5 */
        clkSel = (Rcc_ModuleClockSource)RCC_CLOCK->CLKTIM3CON.B.TIM3_CLKSEL;
        /* #Violation: rcc_hal_c_REF_2 */
        clkDivVal = (uint32)RCC_CLOCK->CLKTIM3CON.B.DIV + 1U;
        break;
    case RCC_BASETIMERIDX_4:
        /* #Violation: rcc_hal_c_REF_3 */
        /* #Violation: rcc_hal_c_REF_5 */
        clkSel = (Rcc_ModuleClockSource)RCC_CLOCK->CLKTIM4CON.B.TIM4_CLKSEL;
        /* #Violation: rcc_hal_c_REF_2 */
        clkDivVal = (uint32)RCC_CLOCK->CLKTIM4CON.B.DIV + 1U;
        break;
    case RCC_BASETIMERIDX_5:
        /* #Violation: rcc_hal_c_REF_3 */
        /* #Violation: rcc_hal_c_REF_5 */
        clkSel = (Rcc_ModuleClockSource)RCC_CLOCK->CLKTIM5CON.B.TIM5_CLKSEL;
        /* #Violation: rcc_hal_c_REF_2 */
        clkDivVal = (uint32)RCC_CLOCK->CLKTIM5CON.B.DIV + 1U;
        break;
    case RCC_BASETIMERIDX_6:
        /* #Violation: rcc_hal_c_REF_3 */
        /* #Violation: rcc_hal_c_REF_5 */
        clkSel = (Rcc_ModuleClockSource)RCC_CLOCK->CLKTIM6CON.B.TIM6_CLKSEL;
        /* #Violation: rcc_hal_c_REF_2 */
        clkDivVal = (uint32)RCC_CLOCK->CLKTIM6CON.B.DIV + 1U;
        break;
    default:
    {
        /* Do nothing */
    }
    break;
    }
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    /* Calcalate BaseTimer clock frequency */
    freq = Rcc_Hal_GetModuleClkSrcFreq(clkSel, RCC_PERPLLCLKTYPE_LOW) / (float32)clkDivVal;
#endif
#if defined(THA6_THA6104)
    /* Calcalate BaseTimer clock frequency */
    freq = Rcc_Hal_GetModuleClkSrcFreq(clkSel, RCC_PERPLLCLKTYPE_HIGH) / (float32)clkDivVal;
#endif
    return freq;
}

#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetAsiBaudClkFreq(void)
{
    float32 freq;
    uint32 clkDivVal;

    /* Get ASI Baud division factor from register. Note: ASI Baud clock source is CPU clock */
    /* #Violation: rcc_hal_c_REF_2 */
    clkDivVal = (uint32)RCC_CLOCK->CLKCON10.B.ASIBAUD_DIV + 1U;

    /* Calcalate ASI Baud clock frequency */
    freq = Rcc_Hal_GetCpuClkFreq() / (float32)clkDivVal;

    return freq;
}
#endif

#if defined(THA6_THA6104)
/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetAsiBaudClkFreq(void)
{
    float32 freq;
    uint32 clkDivVal;
    uint32 clkSel;
    /* Get ASI clock source and division factor */
    /* #Violation: rcc_hal_c_REF_2 */
    clkSel = (uint32)RCC_CLOCK->CLKCON10.B.ASIBAUD_CLKSEL;
    /* #Violation: rcc_hal_c_REF_2 */
    clkDivVal = (uint32)RCC_CLOCK->CLKCON10.B.ASIBAUD_DIV + 1U;

    /* Calcalate ASI clock frequency */
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSel, RCC_PERPLLCLKTYPE_HIGH) / (float32)clkDivVal;

    return freq;
}
#endif

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetMscClkFreq(void)
{
    float32 freq;
    uint32 clkSelVal;

    /* Get MSC clock source config from register. Note: MSC has no divider in RCC */
    /* #Violation: rcc_hal_c_REF_2 */
    clkSelVal = RCC_CLOCK->CLKCON7.B.MSC_CLKSEL;
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSelVal, RCC_PERPLLCLKTYPE_LOW);
    return freq;
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetGethClkFreq(void)
{
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    /* GETH clock is same as AXI bus clock */
    return Rcc_Hal_GetAxiClkFreq();
#endif
#if defined(THA6_THA6104)
    /* GETH clock is same as AHB bus clock */
    return Rcc_Hal_GetAhbApbClkFreq();
#endif
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetGtmClkFreq(void)
{
    float32 freq;
    uint32 clkSelVal;
    uint32 clkDiv;

    /* Get GTM clock source and division factor */
    /* #Violation: rcc_hal_c_REF_2 */
    clkSelVal = RCC_CLOCK->CLKCON1.B.GTM_CLKSEL;
    /* #Violation: rcc_hal_c_REF_2 */
    clkDiv = (uint32)RCC_CLOCK->CLKCON1.B.GTM_DIV + 1U;
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    /* Calcalate GTM clock frequency */
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSelVal, RCC_PERPLLCLKTYPE_LOW) / (float32)clkDiv;
#endif
#if defined(THA6_THA6104)
    /* Calcalate GTM clock frequency */
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSelVal, RCC_PERPLLCLKTYPE_HIGH) / (float32)clkDiv;
#endif
    return freq;
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetStmClkFreq(void)
{
    float32 freq;
    uint32 clkDiv;
    float32 clkFreq;
    uint32 clkSelVal;

    clkFreq = (float32)RCC_CLK_SOURCE_HSI;

    /* Get STM clock source and division factor */
    /* #Violation: rcc_hal_c_REF_2 */
    clkSelVal = RCC_CLOCK->SYSCLKCON1.B.SYSCLKSEL;

    /* #Violation: rcc_hal_c_REF_3 */
    switch ((Rcc_CpuClockSource)clkSelVal)
    {
    case RCC_CPUCLOCKSOURCE_HSI:
        clkFreq = (float32)RCC_CLK_SOURCE_HSI;
        break;
    case RCC_CPUCLOCKSOURCE_SYSPLL:
        clkFreq = Rcc_Hal_GetSysPllFreq();
        break;
    case RCC_CPUCLOCKSOURCE_HSE:
        clkFreq = (float32)RCC_CLK_SOURCE_HSE;
        break;
    default:
    {
        /* Do nothing */
    }
    break;
    }

    /* #Violation: rcc_hal_c_REF_2 */
    clkDiv = (uint32)RCC_CLOCK->SYSCLKCON5.B.CPU_CNTCLKDIV + 1U;

    /* Calcalate STM clock frequency */
    freq = clkFreq / (float32)clkDiv;
    return freq;
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetCanClkFreq(void)
{
    float32 freq;
    uint32 clkSelVal;
    uint32 clkDiv;

    /* Get CAN clock source and division factor */
    /* #Violation: rcc_hal_c_REF_2 */
    clkSelVal = RCC_CLOCK->CLKCON4.B.CAN_CCLKSEL;
    /* #Violation: rcc_hal_c_REF_2 */
    clkDiv = (uint32)RCC_CLOCK->CLKCON4.B.CAN_DIV + 1U;
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    /* Calcalate CAN clock frequency */
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSelVal, RCC_PERPLLCLKTYPE_HIGH) / (float32)clkDiv;
#endif
#if defined(THA6_THA6104)
    /* Calcalate CAN clock frequency */
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSelVal, RCC_PERPLLCLKTYPE_LOW) / (float32)clkDiv;
#endif
    return freq;
}

/* #Violation: rcc_hal_c_REF_6 */
float32 Rcc_Hal_GetWdtClkFreq(void)
{
    float32 freq;
    uint32 clkSelVal;
    uint32 clkDiv;

    /* Get WDT clock source and division factor */
    /* #Violation: rcc_hal_c_REF_2 */
    clkSelVal = RCC_CLOCK->CLKCON8.B.CPUWDT_CLKSEL;
    /* #Violation: rcc_hal_c_REF_2 */
    clkDiv = (uint32)RCC_CLOCK->CLKCON8.B.CPUWDT_DIV + 1U;
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    /* Calcalate WDT clock frequency */
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSelVal, RCC_PERPLLCLKTYPE_LOW) / (float32)clkDiv;
#endif
#if defined(THA6_THA6104)
    /* Calcalate WDT clock frequency */
    /* #Violation: rcc_hal_c_REF_3 */
    freq = Rcc_Hal_GetModuleClkSrcFreq((Rcc_ModuleClockSource)clkSelVal, RCC_PERPLLCLKTYPE_HIGH) / (float32)clkDiv;
#endif
    return freq;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ClockOutputEnable(const Rcc_ClockExtConfig *const clockExtConfig)
{
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if the clockExtConfig is null pointer */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != clockExtConfig));
#endif /* INPUT_ARG_DETECT */

    boolean ret;
    ret = TRUE;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_EXTCLKCON extClkConVal;
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_EXTCLKDIV extClkDivVal;
#if defined(THA6_THA6104) || defined(THA6_THA6412)
    /* #Violation: rcc_hal_c_REF_1 */
    RCC_EXTCLKDIVCFG extDivModVal;
#endif
#if (INPUT_ARG_DETECT == STD_ON)
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(clockExtConfig->preDiv <= RCC_EXT_PREDIV_MAX));
#endif /*INPUT_ARG_DETECT*/

    /* Get registers' value */
    /* #Violation: rcc_hal_c_REF_2 */
    extClkConVal.U = RCC_CLOCK->EXTCLKCON.U;
    /* #Violation: rcc_hal_c_REF_2 */
    extClkDivVal.U = RCC_CLOCK->EXTCLKDIV.U;
#if defined(THA6_THA6104) || defined(THA6_THA6412)
    /* #Violation: rcc_hal_c_REF_2 */
    extDivModVal.U = RCC_CLOCK->EXTCLKDIVCFG.U;
#endif
    /* Assign structure parameters */
    if (RCC_CLOCK_EXT0 == clockExtConfig->clockExt)
    {
#if defined(THA6_THA6104) || defined(THA6_THA6412)
        extDivModVal.B.EXTCLK0_DIVM = (uint32)(clockExtConfig->divMode);
#endif
        extClkDivVal.B.EXTCLK0PRE_DIV = (clockExtConfig->preDiv);
        extClkConVal.B.EXTCLK0_SEL = (uint32)clockExtConfig->ext0ClkSel;
        extClkConVal.B.EXTCLK0_EN = 1U;
    }
    else
    {
#if defined(THA6_THA6104) || defined(THA6_THA6412)
        extDivModVal.B.EXTCLK1_DIVM = (uint32)clockExtConfig->divMode;
#endif
        extClkDivVal.B.EXTCLK1PRE_DIV = clockExtConfig->preDiv;
        extClkConVal.B.EXTCLK1_SEL = (uint32)clockExtConfig->ext1ClkSel;
        extClkConVal.B.EXTCLK1_EN = 1U;
    }

    DISABLE_ALL_INTERRUPTS();
    /* Assign to relative registers  */
    ret &= Cpuwdt_Hal_ClearEndinit();

#if defined(THA6_THA6104) || defined(THA6_THA6412)
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->EXTCLKDIVCFG.U = extDivModVal.U;
#endif
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->EXTCLKDIV.U = extClkDivVal.U;
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->EXTCLKCON.U = extClkConVal.U;
        ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
#if defined(THA6_THA6104) || defined(THA6_THA6412)
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, (extDivModVal.U & RCC_EXTCLKDIVCFG_MASK_VAL), (RCC_CLOCK->EXTCLKDIVCFG.U & RCC_EXTCLKDIVCFG_MASK_VAL));
#endif
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, extClkDivVal.U, RCC_CLOCK->EXTCLKDIV.U);
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, extClkConVal.U, RCC_CLOCK->EXTCLKCON.U);


    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ClockOutputDisable(Rcc_ClockExtType clockExt)
{
    boolean ret;
    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    
        if (RCC_CLOCK_EXT0 == clockExt)
        {
            /* #Violation: rcc_hal_c_REF_2 */
            RCC_CLOCK->EXTCLKCON.B.EXTCLK0_EN = 0U;
            /* #Violation: rcc_hal_c_REF_2 */
            ret = Rcc_Register_ReadBack_Check(ret, 0U, RCC_CLOCK->EXTCLKCON.B.EXTCLK0_EN);
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
            /* #Violation: rcc_hal_c_REF_2 */
            RCC_CLOCK->EXTCLKCON.B.EXTCLK0_SEL = (uint32)RCC_EXT0_RESERVED;
            /* #Violation: rcc_hal_c_REF_2 */
            ret = Rcc_Register_ReadBack_Check(ret, (uint32)RCC_EXT0_RESERVED, RCC_CLOCK->EXTCLKCON.B.EXTCLK0_SEL);
#endif
        }
        else
        {
            /* #Violation: rcc_hal_c_REF_2 */
            RCC_CLOCK->EXTCLKCON.B.EXTCLK1_EN = 0U;
            /* #Violation: rcc_hal_c_REF_2 */
            ret = Rcc_Register_ReadBack_Check(ret, 0U, RCC_CLOCK->EXTCLKCON.B.EXTCLK1_EN);
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
            /* #Violation: rcc_hal_c_REF_2 */
            RCC_CLOCK->EXTCLKCON.B.EXTCLK1_SEL = (uint32)RCC_EXT1_RESERVED;
            /* #Violation: rcc_hal_c_REF_2 */
            ret = Rcc_Register_ReadBack_Check(ret, (uint32)RCC_EXT1_RESERVED, RCC_CLOCK->EXTCLKCON.B.EXTCLK1_SEL);
#endif
        }
        ret &= Cpuwdt_Hal_SetEndinit();
    
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_PLLSwitchEnable(Rcc_PllType pllType)
{
    boolean ret;
    ret = TRUE;
    if (RCC_PLLTYPE_SYS == pllType)
    {
        DISABLE_ALL_INTERRUPTS();
        /* Enable SYSPLL switch and loss alarm */
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->PLLLOCKCON.U |= 0x5U;
        ret &= Safewdt_Hal_SetSafetyEndinit();
        ENABLE_ALL_INTERRUPTS();
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, 0x5U, RCC_CLOCK->PLLLOCKCON.U & 0x5U);
    }
    else
    {
        DISABLE_ALL_INTERRUPTS();
        /* Enable PERPLL switch and loss alarm */
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->PLLLOCKCON.U |= 0xAU;
        ret &= Safewdt_Hal_SetSafetyEndinit();
        ENABLE_ALL_INTERRUPTS();
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, 0xAU, RCC_CLOCK->PLLLOCKCON.U & 0xAU);
    }

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_PLLSwitchDisable(Rcc_PllType pllType)
{
    boolean ret;
    ret = TRUE;
    if (RCC_PLLTYPE_SYS == pllType)
    {
        DISABLE_ALL_INTERRUPTS();
        /* Disbale SYSPLL switch and loss alarm */
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->PLLLOCKCON.U &= (~(0x5U));
        ret &= Safewdt_Hal_SetSafetyEndinit();
        ENABLE_ALL_INTERRUPTS();
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, 0x0U, RCC_CLOCK->PLLLOCKCON.U & 0x5U);
    }
    else
    {
        DISABLE_ALL_INTERRUPTS();
        /* Disbale PERPLL switch and loss alarm */
        ret &= Safewdt_Hal_ClearSafetyEndinit();
        
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->PLLLOCKCON.U &= (~(0xAU));
        ret &= Safewdt_Hal_SetSafetyEndinit();
        ENABLE_ALL_INTERRUPTS();
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, 0x0U, RCC_CLOCK->PLLLOCKCON.U & 0xAU);
    }

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
Rcc_PLLLossLockStatus Rcc_Hal_GetPLLLossLockStatus(Rcc_PllType pllType)
{
    Rcc_PLLLossLockStatus flag;
    uint32 regVal;

    /* Get register bit value */
    if (RCC_PLLTYPE_SYS == pllType)
    {
        /* #Violation: rcc_hal_c_REF_2 */
        regVal = (RCC_CLOCK->CLKALIVESTAT.U >> 22U) & 0x1U;
    }
    else
    {
        /* #Violation: rcc_hal_c_REF_2 */
        regVal = (RCC_CLOCK->CLKALIVESTAT.U >> 23U) & 0x1U;
    }

    if (0x1U == regVal)
    {
        flag = RCC_CLOCK_PLLLOSSLOCK_ERROR;
    }
    else
    {
        flag = RCC_CLOCK_PLLLOSSLOCK_NORMAL;
    }

    return flag;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ClearPLLLossLockStatus(Rcc_PllType pllType)
{
    boolean ret;
    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();

    if (RCC_PLLTYPE_SYS == pllType)
    {
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKALIVESTATCLR.U |= (uint32)((uint32)0x1U << 22U);
    }
    else
    {
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_CLOCK->CLKALIVESTATCLR.U |= (uint32)((uint32)0x1U << 23U);
    }

    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_InitRstType(Rcc_RstSrc rstSrc, Rcc_RstType rstType)
{
    boolean ret;
    ret = TRUE;
    uint32 maskVal;
    uint32 regVal;

    /* Get register value */
    /* #Violation: rcc_hal_c_REF_2 */
    regVal = RCC_RESET->RSTCON1.U;
    /* Calculate the mask */
    maskVal = (uint32)((uint32)0x3U << (uint32)rstSrc);
    regVal = (regVal & (~maskVal)) | ((uint32)rstType << (uint32)rstSrc);

    DISABLE_ALL_INTERRUPTS();
    /* Set selected reset source with selected reset type */
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* Upadte register value */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_RESET->RSTCON1.U = regVal;
    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, regVal, (uint32)RCC_RESET->RSTCON1.U);
    


    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ReqSwTrigRst(void)
{
    boolean ret;
    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();

    /* #Violation: rcc_hal_c_REF_2 */
    RCC_RESET->SWRSTCON.B.SWRSTREQ = RCC_BIT_ENABLE;
    ret &= Cpuwdt_Hal_SetEndinit();
    
    ENABLE_ALL_INTERRUPTS();
    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
Rcc_RstReason Rcc_Hal_ReadRstStatus(void)
{
    Rcc_RstReason rstReason;
    uint8 setBitCnt;
    uint32 rstStatReg;
    uint8 bitPos;
    setBitCnt = 0U;
    rstReason = RCC_RSTREASON_NONE;

    /* Remove DBGRST type by mask */
    /* #Violation: rcc_hal_c_REF_2 */
    rstStatReg = RCC_RESET->RSTSTAT.U;

    /* Record reason if bit set */
    for (bitPos = 0U; bitPos < RCC_REG_WIDTH; bitPos++)
    {
        if (RCC_BIT_ENABLE == ((rstStatReg >> bitPos) & RCC_BIT_ENABLE))
        {
            setBitCnt++;
            /* #Violation: rcc_hal_c_REF_3 */
            rstReason = (Rcc_RstReason)(bitPos);
        }
    }
    /* If more than 2 reset source happened, then break */
    if (setBitCnt >= 2U)
    {
        rstReason = RCC_RSTREASON_MUTITYPE;
    }
    return rstReason;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_ClearRstStatus(Rcc_RstReason rstReason)
{
    boolean ret;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if rstReason in the valid range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(rstReason <= RCC_RSTREASON_NONE));
#endif /* INPUT_ARG_DETECT */

    uint32 setBit;

    if ((RCC_RSTREASON_MUTITYPE == rstReason) || (RCC_RSTREASON_NONE == rstReason))
    {
        /* #Violation: rcc_hal_c_REF_2 */
        setBit = RCC_RESET->RSTSTAT.U;
    }
    else
    {
        setBit = ((uint32)1U << (uint32)rstReason) | RCC_DBG_RESET; /* Clear DBG reset together */
    }

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    /* Clear reset status */
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_RESET->RSTSTATCLR.U |= setBit;
    ret &= Cpuwdt_Hal_SetEndinit();
    
    ENABLE_ALL_INTERRUPTS();
    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_SetRstTimeoutCnt(uint16 cnt)
{
    boolean ret;
    ret = TRUE;
#if (INPUT_ARG_DETECT == STD_ON)
    /* Check if cnt in the valid range */
    /* #Violation: rcc_hal_c_REF_3 */
    Assert((boolean)(cnt <= RCC_TIMOUTCNT_MAX));
#endif /* INPUT_ARG_DETECT */

    DISABLE_ALL_INTERRUPTS();
    /* Config timeout counter, and enbale the counter count function */
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_RESET->TIMOUTCNT.B.COUNTER = cnt;
    /* #Violation: rcc_hal_c_REF_2 */
    RCC_RESET->TIMOUTCNTEN.B.TIMOUTCNTEN = RCC_BIT_ENABLE;
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)cnt, (uint32)RCC_RESET->TIMOUTCNT.B.COUNTER);
    /* #Violation: rcc_hal_c_REF_2 */
    ret = Rcc_Register_ReadBack_Check(ret, (uint32)RCC_BIT_ENABLE, (uint32)RCC_RESET->TIMOUTCNTEN.B.TIMOUTCNTEN);

    return ret;
}

/* #Violation: rcc_hal_c_REF_6 */
Rcc_ErrorFlag Rcc_Hal_TrigModuleRst(Rcc_ModuleRst moduleSel)
{
    /******************************************************
     * Usage Restrictions
     * - This interface cannot be invoked concurrently by 
     * multiple cores; it is recommended to add a mutex lock.
     *******************************************************/
    boolean ret;
    Rcc_ErrorFlag flag;
    uint32 regVal;
    uint32 regGroupIdx;
    uint32 bitOffset;
    uint32 setBit;
    uint32 clearBit;
    uint32 curTime;
    /* Record module reset register address */
    uint32 rstRegAdr;
    ret = TRUE;
    rstRegAdr = 0U;
    curTime = 0U;
    flag = RCC_ERRORFLAG_TIMEOUT;
    /* Divide moduleSel into corresponding group related with RCC registers */
    regGroupIdx = (uint32)moduleSel / RCC_REG_WIDTH;

    /* Control bit value in one register */
    bitOffset = (uint32)moduleSel % RCC_REG_WIDTH;
    setBit = (uint32)1U << bitOffset;
    clearBit = ~setBit;
    /* Get reset register address */
    /* #Violation: rcc_hal_c_REF_5 */
    if(((uint32)RCC_MODULERSTWDT) > regGroupIdx)
    {
        /* #Violation: rcc_hal_c_REF_2 */
        /* #Violation: rcc_hal_c_REF_2 */
        rstRegAdr = ((uint32) & (RCC_RESET->MODRSTCON1.U)) + (0x4U * regGroupIdx);
    }
    else if(((uint32)RCC_MODULERSTWDT) == regGroupIdx)
    {
        /* #Violation: rcc_hal_c_REF_2 */
        /* #Violation: rcc_hal_c_REF_2 */
        rstRegAdr = ((uint32) & (RCC_RESET->MODRSTCONWDT.U));
    }
    else
    {
        flag = RCC_ERRORFLAG_NULLPTR;
    }

    if (0U != rstRegAdr)
    {
        if ((uint32)RCC_MODULERSTWDT != regGroupIdx)
        {
            /* #Violation: rcc_hal_c_REF_2 */
            regVal = (*(volatile uint32 *)rstRegAdr);
            DISABLE_ALL_INTERRUPTS();
            ret &= Cpuwdt_Hal_ClearEndinit();
            
            /* Trigger module reset */
            /* #Violation: rcc_hal_c_REF_2 */
            (*(volatile uint32 *)rstRegAdr) |= setBit;
            /* #Violation: rcc_hal_c_REF_2 */
            ret = Rcc_Register_ReadBack_Check(ret, (uint32)(regVal | setBit), (*(volatile uint32 *)rstRegAdr));
            /* #Violation: rcc_hal_c_REF_2 */
            (*(volatile uint32 *)rstRegAdr) &= clearBit;
            while((curTime < RCC_MODREST_COUNT) && (RCC_ERRORFLAG_TIMEOUT == flag))
            {   
                /* #Violation: rcc_hal_c_REF_2 */
                if(FALSE == ((*(volatile uint32 *)rstRegAdr) & setBit))
                {
                    flag = RCC_ERRORFLAG_SUCCESS;
                }
                curTime++;
            }
            ret &= Cpuwdt_Hal_SetEndinit();
            
            ENABLE_ALL_INTERRUPTS();
        }
        else
        {
            /* #Violation: rcc_hal_c_REF_2 */
            RCC_RESET->WDTRSTPROT.U = RCC_WDTPROT_VALUE;
            /* #Violation: rcc_hal_c_REF_2 */
            ret = Rcc_Register_ReadBack_Check(ret, (uint32)(RCC_WDTPROT_VALUE), (uint32)RCC_RESET->WDTRSTPROT.U);
            /* #Violation: rcc_hal_c_REF_2 */
            regVal = (*(volatile uint32 *)rstRegAdr);
            /* Trigger WDG module reset */
            /* #Violation: rcc_hal_c_REF_2 */
            (*(volatile uint32 *)rstRegAdr) |= setBit;
            /* #Violation: rcc_hal_c_REF_2 */
            ret = Rcc_Register_ReadBack_Check(ret, (uint32)(regVal | setBit), (*(volatile uint32 *)rstRegAdr));
            /* #Violation: rcc_hal_c_REF_2 */
            (*(volatile uint32 *)rstRegAdr) &= clearBit;
            while((curTime < RCC_MODREST_COUNT) && (RCC_ERRORFLAG_TIMEOUT == flag))
            {
                /* #Violation: rcc_hal_c_REF_2 */
                if(FALSE == ((*(volatile uint32 *)rstRegAdr) & setBit))
                {
                    flag = RCC_ERRORFLAG_SUCCESS;
                }
                curTime++;
            }
            /* #Violation: rcc_hal_c_REF_2 */
            RCC_RESET->WDTRSTPROT.U = 0x0U;
            /* #Violation: rcc_hal_c_REF_2 */
            ret = Rcc_Register_ReadBack_Check(ret, (uint32)(0x0U), (uint32)RCC_RESET->WDTRSTPROT.U);
        }
    }

    if (FALSE == ret)
    {
        flag = RCC_ERRORFLAG_FAIL;
    }
    return flag;
}

/* #Violation: rcc_hal_c_REF_6 */
boolean Rcc_Hal_SetShutdownFlag(boolean bitFlag)
{
    boolean ret;
    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();
    
    if (TRUE == bitFlag)
    {
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_RESET->CPUSHUTDOWNFLAG.B.CPUSHUTDOWNFLAG = RCC_BIT_ENABLE;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, (uint32)(RCC_BIT_ENABLE), (uint32)RCC_RESET->CPUSHUTDOWNFLAG.B.CPUSHUTDOWNFLAG);
    }
    else
    {
        /* #Violation: rcc_hal_c_REF_2 */
        RCC_RESET->CPUSHUTDOWNFLAG.B.CPUSHUTDOWNFLAG = RCC_BIT_DISABLE;
        /* #Violation: rcc_hal_c_REF_2 */
        ret = Rcc_Register_ReadBack_Check(ret, (uint32)(RCC_BIT_DISABLE), (uint32)RCC_RESET->CPUSHUTDOWNFLAG.B.CPUSHUTDOWNFLAG);
    }
    ret &= Cpuwdt_Hal_SetEndinit();
    
    ENABLE_ALL_INTERRUPTS();
    return ret;
}
/* #Violation: rcc_hal_c_REF_13 */
#define RCC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rcc_hal_c_REF_14 */
#include "Rcc_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

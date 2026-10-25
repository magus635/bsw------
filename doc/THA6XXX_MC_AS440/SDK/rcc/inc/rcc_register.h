/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    rcc_register.h
 * Author:      0976
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of RCC module registers.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#rcc_register_h_REF_1:MISRAC2012-Rule-19.2;
 * Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured
 *                by code review.
 *
 *#rcc_register_h_REF_2:MISRAC2012-Rule-2.3;
 * Justification: The members of the type are used in configuration-generated code.
 *
 */
#ifndef RCC_REGISTER_H_
#define RCC_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        RCC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Hse control register 1 */
typedef struct
{
    ureg32 HSE_EN : 1;      /* [0:0] Hse enabled - RW */
    ureg32 HSE_BYPEN : 1;   /* [1:1] Bypass enable signal, valid only if hse_en = 0 - RW */
    ureg32 HSE_APREN : 1;   /* [2:2] Automatic amplitude control function enable signal, when it is "1", the gain is the
                           maximum value by default - RW */
    ureg32 HSE_GAINSEL : 2; /* [4:3] Gain selection signal, valid when apren = 0 - RW */
    ureg32 reserved_5 : 4;  /* [8:5] Internal reserved */
    ureg32 HSE_READY : 1;
    /* [9:9] The hse xtal clock stabilization indicator indicates the steady state of the clock in xtal
      mode, and in bypass mode, it is not necessary to pay attention to the indicator bits. - RO */
    ureg32 reserved_10 : 22; /* [31:10] Internal reserved */
} RCC_HSECON1_Bits;

/* Hse control register 2 */
typedef struct
{
#if defined(THA6_THA6206) || defined(THA6_THA6412) || defined(THA6_THA6206D)
    ureg32 STBCNT : 16;      /* [15:0] Hse xtal clock stabilization time configuration - RW */
    ureg32 reserved_16 : 16; /* [31:16] Internal reserved */
#endif
#if defined(THA6_THA6104)
    ureg32 STBCNT : 32; /* [31:0] Hse xtal clock stabilization time configuration - RW */
#endif
} RCC_HSECON2_Bits;

/* Pll reference clock selection register */
typedef struct
{
    ureg32 SYSPLL_REFSEL : 2; /* [1:0] System pll reference clock selection - RW */
    ureg32 PERPLL_REFSEL : 2; /* [3:2] Peripheral pll reference clock selection - RW */
    ureg32 reserved_4 : 28;   /* [31:4] Internal reserved */
} RCC_PLLREFSEL_Bits;

/* System pll control register 1 */
typedef struct
{
    ureg32 PLLPD : 1;         /* [0:0] Pll clock power down enabled - RW */
    ureg32 reserved_1 : 3;    /* [1:3] Internal reserved */
    ureg32 FOUTPOSTDIVPD : 1; /* [4:4] Post divider close (must keep 0) - RW */
    ureg32 FOUT4PHASEPD : 1;  /* [5:5] 4 phase clock generates shutdown enable (must keep 0) - RW */
    ureg32 reserved_6 : 2;    /* [6:7] Internal reserved */
    ureg32 PLLMOD : 1;        /* [8:8] Pll clock mode - RW */
    ureg32 DACPD : 1;         /* [9:9] Power down noise canceling dac in frac mode - RW */
    ureg32 reserved_10 : 2;   /* [11:10] Internal reserved */
    ureg32 FOUTVCOPD : 1;     /* [12:12] Vco output clock off (must keep 1) - RW */
    ureg32 reserved_14 : 3;   /* [15:13] Internal reserved */
    ureg32 PLLRDY : 1;        /* [16:16] Pll clock setup complete, lock complete - RO */
    ureg32 reserved_17 : 15;  /* [23:17] Internal reserved */
} RCC_SYSPLLCON1_Bits;

/* System pll control register 2 */
typedef struct
{
    ureg32 FBDIV : 12;      /* [11:0] Pll feedback factor settings - RW */
    ureg32 POSTDIV1 : 3;    /* [14:12] Pll post divider1 settings (1 to 7) - RW */
    ureg32 reserved_15 : 1; /* [15:15] Internal reserved */
    ureg32 POSTDIV2 : 3;    /* [18:16] Pll post divider2 settings (1 to 7) - RW */
    ureg32 reserved_19 : 1; /* [19:19] Internal reserved */
    ureg32 REFDIV : 6;      /* [25:20] Reference clock divider settings (1 to 63) - RW */
    ureg32 POSTDIV3 : 3;    /* [28:26] Pll post divider3 settings (1 to 7) - RW, for CHIP THA6104 */
    ureg32 reserved_26 : 3; /* [31:29] Internal reserved */
} RCC_SYSPLLCON2_Bits;

/* System pll control register 3 */
typedef struct
{
    ureg32 FRAC : 24;       /* [23:0] Decimal multiplier settings - RW */
    ureg32 reserved_24 : 8; /* [31:24] Internal reserved */
} RCC_SYSPLLCON3_Bits;

/* System pll control register 4 */
typedef struct
{
    ureg32 SYSPLL_MODE : 1; /* [0:0] System pll spread mode enable - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_SYSPLLCON4_Bits;

/* Spread-spectrum bridge control register 1 */
typedef struct
{
    ureg32 RESET : 1;        /* [0:0] Modulator reset control - RW */
    ureg32 DOWNSPREAD : 1;   /* [1:1] Frequency adjustment control - RW */
    ureg32 DISABLE_SSCG : 1; /* [2:2] Bypass mode control - RW */
    ureg32 reserved_3 : 1;   /* [3:3] Internal reserved */
    ureg32 SPREAD : 5;       /* [8:4] Frequency change amplitude control (in 0.1% steps) - RW */
    ureg32 DIVVAL : 6;       /* [14:9] Enter the crossover coefficient to set the modulation frequency - RW */
    ureg32 reserved_15 : 1;  /* [15:15] Internal reserved */
    ureg32 INTIN : 12;       /* [27:16] Input integer crossover value - RW */
    ureg32 reserved_27 : 4;  /* [31:28] Internal reserved */
} RCC_SSMODCON1_Bits;

/* Spread-spectrum bridge control register 2 */
typedef struct
{
    ureg32 reserved_0 : 1;  /* [0:0] Internal reserved */
    ureg32 RESETPTR : 1;    /* [1:1] Wave table pointer reset control - RW */
    ureg32 reserved_2 : 30; /* [31:2] Internal reserved */
} RCC_SSMODCON2_Bits;

/* Spread-spectrum bridge control register 3 */
typedef struct
{
    ureg32 FRACIN : 24;     /* [23:0] Decimal frequency division value entered - RW */
    ureg32 reserved_24 : 8; /* [31:24] Internal reserved */
} RCC_SSMODCON3_Bits;

/* Peripheral pll control register 1 */
typedef struct
{
    ureg32 PLLPD : 1;         /* [0:0] Pll clock power down enabled - RW */
    ureg32 reserved_1 : 3;    /* [1:3] Internal reserved */
    ureg32 FOUTPOSTDIVPD : 1; /* [4:4] Post divider close (must keep 0) - RW */
    ureg32 FOUT4PHASEPD : 1;  /* [5:5] 4 phase clock generates shutdown enable (must keep 0) - RW */
    ureg32 reserved_6 : 2;    /* [6:7] Internal reserved */
    ureg32 PLLMOD : 1;        /* [8:8] Pll clock mode - RW */
    ureg32 DACPD : 1;         /* [9:9] Power down noise canceling dac in frac mode - RW */
    ureg32 reserved_10 : 2;   /* [11:10] Internal reserved */
    ureg32 FOUTVCOPD : 1;     /* [12:12] Vco output clock off (must keep 1) - RW */
    ureg32 reserved_14 : 3;   /* [15:13] Internal reserved */
    ureg32 PLLRDY : 1;        /* [16:16] Pll clock setup complete, lock complete - RO */
    ureg32 reserved_17 : 15;  /* [31:17] Internal reserved */
} RCC_PERPLLCON1_Bits;

/* Peripheral pll control register 2 */
typedef struct
{
    ureg32 FBDIV : 12;      /* [11:0] Pll feedback factor settings - RW */
    ureg32 POSTDIV1 : 3;    /* [14:12] Pll post divider1 settings (1 to 7) - RW */
    ureg32 reserved_15 : 1; /* [15:15] Internal reserved */
    ureg32 POSTDIV2 : 3;    /* [18:16] Pll post divider2 settings (1 to 7) - RW */
    ureg32 reserved_19 : 1; /* [19:19] Internal reserved */
    ureg32 REFDIV : 6;      /* [25:20] Reference clock divider settings (1 to 63) - RW */
    ureg32 POSTDIV3 : 3;    /* [28:26] Pll post divider3 settings (1 to 7) - RW, for CHIP THA6104 */
    ureg32 reserved_26 : 3; /* [31:29] Internal reserved */
} RCC_PERPLLCON2_Bits;

/* Peripheral pll control register 3 */
typedef struct
{
    ureg32 FRAC : 24;       /* [23:0] Decimal multiplier settings - RW */
    ureg32 reserved_24 : 8; /* [31:24] Internal reserved */
} RCC_PERPLLCON3_Bits;

/* Peripheral pll control register 4, for CHIP THA6104 and THA6412 */
typedef struct
{
    ureg32 PERPLL_MODE : 1; /* [0:0] Peripheral pll spread mode enable - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_PERPLLCON4_Bits;

/* System clock control register 1 */
typedef struct
{
    ureg32 CPU_DIV : 8;         /* [7:0] Cpu clock division coefficient, maximum 256 division frequency - RW */
    ureg32 CPUDIVCLK_READY : 1; /* [8:8] Cpu clock division coefficient ready status - RW, for CHIP THA6412 and THA6104 */
    ureg32 reserved_9 : 11;     /* [19:9] Internal reserved */
    ureg32 SYSCLKSEL : 2;       /* [21:20] System clock (sys_clk_src) source selection - RW */
    ureg32 reserved_22 : 10;    /* [31:22] Internal reserved */
} RCC_SYSCLKCON1_Bits;

/* System clock control register 2 */
typedef struct
{
    ureg32 AHB_DIV : 9;     /* [8:0] Ahb clock frequency division coefficient - RW */
    ureg32 reserved_9 : 3;  /* [11:9] Internal reserved */
    ureg32 AXI_DIV : 6;     /* [17:12] Axi clock crossover coefficient, max 64 crossover - RW */
    ureg32 reserved_18 : 2; /* [19:18] Internal reserved */
    ureg32 SYS_DIV : 3;     /* [22:20] System clock division coefficient, maximum 8 divisions - RW */
    ureg32 reserved_23 : 9; /* [31:23] Internal reserved */
} RCC_SYSCLKCON2_Bits;

/* System clock control register 3 */
typedef struct
{
    ureg32 RST_BUSCLKCNTCLR : 1; /* [0:0] bus clock frequency divide counter clear while system reset - RW */
    ureg32 reserved_1 : 31;      /* [31:1] Internal reserved */
} RCC_SYSCLKCON3_Bits;

/* System clock control register 4 */
typedef struct
{
    ureg32 BUSDIV_UPDATE : 1; /* [0:0] Trigger bus and cpu frequency division effective - W1c */
    ureg32 reserved_1 : 31;   /* [31:1] Internal reserved */
} RCC_SYSCLKCON4_Bits;

/* System clock control register 5 */
typedef struct
{
    ureg32 CPU_CNTCLKDIV : 5; /* [4:0] STM clock division coefficient - RW */
    ureg32 reserved_5 : 27;   /* [31:5] Internal reserved */
} RCC_SYSCLKCON5_Bits;

/* System clock control register 6 */
typedef struct
{
    ureg32 ATDCLKDIV : 3;    /* [2:0] Cpu data trace clock frequency division coefficient - RW */
    ureg32 reserved_3 : 1;   /* [3:3] Internal reserved */
    ureg32 ATICLKDIV : 3;    /* [6:4] Cpu instruction trace clock frequency division coefficient - RW */
    ureg32 reserved_7 : 1;   /* [7:7] Internal reserved */
    ureg32 DBGDIV : 3;       /* [10:8] Cpu debug apb interface clock frequency division - RW */
    ureg32 reserved_11 : 21; /* [31:11] Internal reserved */
} RCC_SYSCLKCON6_Bits;

/* System clock control register 7 */
typedef struct
{
    ureg32 ATB_DIV : 4;     /* [3:0] Atb clock division coefficient - RW */
    ureg32 reserved_4 : 20; /* [23:4] Internal reserved */
    ureg32 ATBCLKSEL : 2;   /* [25:24] Atbclk clock source selection - RW */
    ureg32 reserved_26 : 6; /* [31:26] Internal reserved */
} RCC_SYSCLKCON7_Bits;

/* System clock control register 8 */
typedef struct
{
    ureg32 TRACE_DIV : 4;    /* [3:0] Trace clock frequency division coefficient - RW */
    ureg32 reserved_4 : 12;  /* [15:4] Internal reserved */
    ureg32 TRACE_CLKSEL : 2; /* [17:16] Trace clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_SYSCLKCON8_Bits;

/* Clock control register 1 */
typedef struct
{
    ureg32 GTM_DIV : 5;      /* [4:0] Gtm clock frequency division coefficient - RW */
    ureg32 reserved_5 : 11;  /* [15:5] Internal reserved */
    ureg32 GTM_CLKSEL : 2;   /* [17:16] Gtm cluster clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKCON1_Bits;

/* Clock control register 2, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 QSPI_DIV : 5;     /* [4:0] Qspi clock crossover coefficient - RW */
    ureg32 reserved_5 : 11;  /* [15:5] Internal reserved */
    ureg32 QSPI_CLKSEL : 2;  /* [17:16] Qspi clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKCON2_Bits;

/* Clock control register 3 */
typedef struct
{
    ureg32 ESPI_DIV : 5;     /* [4:0] Espi clock crossover coefficient - RW */
    ureg32 reserved_5 : 11;  /* [15:5] Internal reserved */
    ureg32 ESPI_CLKSEL : 2;  /* [17:16] Espi clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKCON3_Bits;

/* Clock control register 4 */
typedef struct
{
    ureg32 CAN_DIV : 6;      /* [5:0] Can cclk clock division coefficient - RW */
    ureg32 reserved_6 : 10;  /* [15:6] Internal reserved */
    ureg32 CAN_CCLKSEL : 2;  /* [17:16] Can_cclk clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKCON4_Bits;

/* Clock control register 5 */
typedef struct
{
    ureg32 reserved_0 : 16;   /* [5:0] Saradc clock crossover coefficient - RW */
    ureg32 SARADC_CLKSEL : 2; /* [17:16] Saradc clock source selection - RW */
    ureg32 reserved_18 : 14;  /* [31:18] Internal reserved */
} RCC_CLKCON5_Bits;

/* Clock control register 6, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 DSADC_DIV : 6;       /* [5:0] Dsadc clock crossover coefficient - RW */
    ureg32 reserved_6 : 2;      /* [7:6] Internal reserved */
    ureg32 RDC_DIV : 6;         /* [13:8] Rdc clock crossover coefficient - RW */
    ureg32 reserved_14 : 2;     /* [15:14] Internal reserved */
    ureg32 RDCDSADC_CLKSEL : 2; /* [17:16] Rdc/dsadc clock source selection - RW */
    ureg32 reserved_18 : 14;    /* [31:18] Internal reserved */
} RCC_CLKCON6_Bits;

/* Clock control register 7, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 MSC_CLKSEL : 2;  /* [1:0] Msc clock source selection - RW */
    ureg32 reserved_2 : 30; /* [31:2] Internal reserved */
} RCC_CLKCON7_Bits;

/* Clock control register 8 */
typedef struct
{
    ureg32 CPUWDT_DIV : 5;    /* [4:0] Cpu_wdt_clock crossover coefficient - RW */
    ureg32 reserved_5 : 11;   /* [15:5] Internal reserved */
    ureg32 CPUWDT_CLKSEL : 2; /* [17:16] Cpu0/1 wdt and safety wdt clock source selection - RW */
    ureg32 reserved_18 : 14;  /* [31:18] Internal reserved */
} RCC_CLKCON8_Bits;

/* Clock control register 9 */
typedef struct
{
    ureg32 IPCNT_DIV : 6;    /* [5:0] Ipcnt clock crossover coefficient - RW */
    ureg32 reserved_6 : 10;  /* [15:6] Internal reserved */
    ureg32 IPCNT_CLKSEL : 2; /* [17:16] Ipcnt clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKCON9_Bits;

/* Clock control register 10 */
typedef struct
{
    ureg32 ASIBAUD_DIV : 8;    /* [7:0] Asi baud clock crossover coefficient - RO */
    ureg32 ASIBAUDBUS_DIV : 9; /* [16: 8] Asi Baud Bus clock crossover coefficient - RW, for CHIP THA6104 */
    ureg32 ASIBAUD_CLKSEL : 2; /* [18:17] Asi Baud clock source selection -RW, for CHIP THA6104*/
    ureg32 reserved_8 : 13;    /* [31:8] Internal reserved */
} RCC_CLKCON10_Bits;

/* Clock control register 11, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 FC_DIV : 5;       /* [4:0] Fc clock frequency division coefficient - RW */
    ureg32 reserved_5 : 11;  /* [15:5] Internal reserved */
    ureg32 FC_CLKSEL : 2;    /* [17:16] Fc clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKCON11_Bits;

/* Timer1 clock control register */
typedef struct
{
    ureg32 DIV : 16;         /* [15:0] Clock division - RW */
    ureg32 TIM1_CLKSEL : 2;  /* [17:16] Tim1 clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKTIM1CON_Bits;

/* Timer2 clock control register */
typedef struct
{
    ureg32 DIV : 16;         /* [15:0] Clock division - RW */
    ureg32 TIM2_CLKSEL : 2;  /* [17:16] Tim2 clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKTIM2CON_Bits;

/* Timer3 clock control register */
typedef struct
{
    ureg32 DIV : 16;         /* [15:0] Clock division - RW */
    ureg32 TIM3_CLKSEL : 2;  /* [17:16] Tim3 clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKTIM3CON_Bits;

/* Timer4 clock control register */
typedef struct
{
    ureg32 DIV : 16;         /* [15:0] Clock division - RW */
    ureg32 TIM4_CLKSEL : 2;  /* [17:16] Tim4 clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKTIM4CON_Bits;

/* Timer5 clock control register, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 DIV : 16;         /* [15:0] Clock division - RW */
    ureg32 TIM5_CLKSEL : 2;  /* [17:16] Tim5 clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKTIM5CON_Bits;

/* Timer6 clock control register, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 DIV : 16;         /* [15:0] Clock division - RW */
    ureg32 TIM6_CLKSEL : 2;  /* [17:16] Tim6 clock source selection - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_CLKTIM6CON_Bits;

/* Module clock enable register 1 */
typedef struct
{
    ureg32 DMA0_EN : 1;      /* [0:0] Axi_dma0 enable - RW */
    ureg32 reserved_1 : 3;   /* [3:1] Internal reserved */
    ureg32 DMA1_EN : 1;      /* [4:4] Ahb_dma1 enabled - RW, for CHIP THA6206 and THA6412 */
    ureg32 DMA2_EN : 1;      /* [5:5] Ahb_dma2 enabled - RW */
    ureg32 DMA3_EN : 1;      /* [6:6] Ahb_dma3 enabled - RW, for CHIP THA6206 and THA6412 */
    ureg32 reserved_7 : 13;  /* [19:7] Internal reserved */
    ureg32 TSENSOR0_EN : 1;  /* [20:20] Tsensor0 enable - RW */
    ureg32 TSENSOR1_EN : 1;  /* [21:21] Tsensor1 enable - RW */
    ureg32 reserved_22 : 10; /* [31:22] Internal reserved */
} RCC_CLKEN1_Bits;

/* Module clock enable register 2 */
typedef struct
{
    ureg32 GTM_EN : 1;          /* [0:0] Gtm enabled - RW */
    ureg32 GETH_EN : 1;         /* [1:1] Geth enabled - RW */
    ureg32 HRPWM_EN : 1;        /* [2:2] HRPWM enabled - RW, for CHIP THA6412 and THA6104 */
    ureg32 reserved_3 : 1;      /* [3:3] Internal reserved */
    ureg32 BASETIMG0CLK_EN : 1; /* [4:4] Basetim0 & 1 pclk enabled - RW */
    ureg32 BASETIMG1CLK_EN : 1; /* [5:5] Basetim2 & 3 pclk enabled - RW */
    ureg32 BASETIMG2CLK_EN : 1; /* [6:6] Basetim4 & 5 pclk enabled - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_7 : 9;      /* [15:7] Internal reserved */
    ureg32 QSPI_EN : 1;         /* [16:16] Qspi enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_17 : 3;     /* [19:17] Internal reserved */
    ureg32 I2C0_EN : 1;         /* [20:20] I2c0 enable - RW */
    ureg32 I2C1_EN : 1;         /* [21:21] I2c1 enable - RW, for CHIP THA6412 and THA6104 */
    ureg32 reserved_22 : 2;     /* [23:22] Internal reserved */
    ureg32 MSC0_EN : 1;         /* [24:24] Msc0 enabled - RW */
    ureg32 MSC1_EN : 1;         /* [25:25] Msc1 enabled - RW, for CHIP THA6412 */
    ureg32 MSC2_EN : 1;         /* [26:26] Msc2 enabled - RW, for CHIP THA6412 */
    ureg32 reserved_27 : 1;     /* [27:27] Internal reserved */
    ureg32 ECRC_EN : 1;         /* [28:28] Ecrc enabled - RW */
    ureg32 reserved_29 : 3;     /* [31:29] Internal reserved */

} RCC_CLKEN2_Bits;

/* Module clock enable register 3 */
typedef struct
{
    ureg32 SENT0_EN : 1;    /* [0:0] Sent0 enable - RW */
    ureg32 SENT1_EN : 1;    /* [1:1] Sent1 enable - RW */
    ureg32 SENT2_EN : 1;    /* [2:2] Sent2 enable - RW */
    ureg32 SENT3_EN : 1;    /* [3:3] Sent3 enable - RW */
    ureg32 SENT4_EN : 1;    /* [4:4] Sent4 enable - RW */
    ureg32 SENT5_EN : 1;    /* [5:5] Sent5 enable - RW */
    ureg32 SENT6_EN : 1;    /* [6:6] Sent6 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 SENT7_EN : 1;    /* [7:7] Sent7 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 SENT8_EN : 1;    /* [8:8] Sent8 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 SENT9_EN : 1;    /* [9:9] Sent9 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_10 : 2; /* [11:10] Internal reserved */
    ureg32 PSI5_EN : 1;     /* [12:12] Psi5 enable - RW, for CHIP THA6412 */
    ureg32 reserved_13 : 3; /* [15:13] Internal reserved */
    ureg32 ESPI0_EN : 1;    /* [16:16] Espi0 enable - RW */
    ureg32 ESPI1_EN : 1;    /* [17:17] Espi1 enabled - RW */
    ureg32 ESPI2_EN : 1;    /* [18:18] Espi2 enabled - RW */
    ureg32 ESPI3_EN : 1;    /* [19:19] Espi3 enabled - RW */
    ureg32 ESPI4_EN : 1;    /* [20:20] Espi4 enabled - RW */
    ureg32 ESPI5_EN : 1;    /* [21:21] Espi5 enabled - RW */
    ureg32 ESPI6_EN : 1;    /* [22:22] Espi6 enabled - RW, for CHIP THA6412 and THA6206 */
    ureg32 ESPI7_EN : 1;    /* [23:23] Espi7 enabled - RW, for CHIP THA6412 and THA6206 */
    ureg32 ESPI8_EN : 1;    /* [24:24] Espi8 enabled - RW , for CHIP THA6412 and THA6206*/
    ureg32 reserved_25 : 7; /* [31:25] Internal reserved */
} RCC_CLKEN3_Bits;

/* Module clock enable register 4 */
typedef struct
{
    ureg32 ASI0_EN : 1;     /* [0:0] Asi0 enabled - RW */
    ureg32 ASI1_EN : 1;     /* [1:1] Asi1 enabled - RW */
    ureg32 ASI2_EN : 1;     /* [2:2] Asi2 enabled - RW */
    ureg32 ASI3_EN : 1;     /* [3:3] Asi3 enabled - RW */
    ureg32 ASI4_EN : 1;     /* [4:4] Asi4 enabled - RW */
    ureg32 ASI5_EN : 1;     /* [5:5] Asi5 enabled - RW */
    ureg32 ASI6_EN : 1;     /* [6:6] Asi6 enabled - RW */
    ureg32 ASI7_EN : 1;     /* [7:7] Asi7 enabled - RW */
    ureg32 reserved_8 : 8;  /* [15:8] Internal reserved */
    ureg32 CAN0_EN : 1;     /* [16:16] Can0 enable - RW */
    ureg32 CAN1_EN : 1;     /* [17:17] Can1 enabled - RW */
    ureg32 CAN2_EN : 1;     /* [18:18] Can2 enabled - RW */
    ureg32 CAN3_EN : 1;     /* [19:19] Can3 enabled - RW */
    ureg32 CAN4_EN : 1;     /* [20:20] Can4 enabled - RW */
    ureg32 CAN5_EN : 1;     /* [21:21] Can5 enabled - RW */
    ureg32 CAN6_EN : 1;     /* [22:22] Can6 enable - RW, for CHIP THA6412 */
    ureg32 CAN7_EN : 1;     /* [23:23] Can7 enabled - RW, for CHIP THA6412 */
    ureg32 CAN8_EN : 1;     /* [24:24] Can8 enabled - RW, for CHIP THA6412 */
    ureg32 CAN9_EN : 1;     /* [25:25] Can9 enabled - RW, for CHIP THA6412 */
    ureg32 CAN10_EN : 1;    /* [26:26] Can10 enabled - RW, for CHIP THA6412 */
    ureg32 CAN11_EN : 1;    /* [27:27] Can11 enabled - RW, for CHIP THA6412 */
    ureg32 reserved_28 : 4; /* [31:28] Internal reserved */

} RCC_CLKEN4_Bits;

/* Module clock enable register 5 */
typedef struct
{
    ureg32 DSADC0_EN : 1;   /* [0:0] Dsadc0 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 DSADC1_EN : 1;   /* [1:1] Dsadc1 enabled - RW, for CHIP THA6412 and THA6206 */
    ureg32 DSADC2_EN : 1;   /* [2:2] Dsadc2 enabled - RW, for CHIP THA6412 and THA6206 */
    ureg32 DSADC3_EN : 1;   /* [3:3] Dsadc3 enabled - RW, for CHIP THA6412 and THA6206 */
    ureg32 DSADC4_EN : 1;   /* [4:4] Dsadc4 enabled - RW, for CHIP THA6412 */
    ureg32 DSADC5_EN : 1;   /* [5:5] Dsadc5 enabled - RW, for CHIP THA6412 */
    ureg32 DSADC6_EN : 1;   /* [6:6] Dsadc6 enabled - RW, for CHIP THA6412 */
    ureg32 DSADC7_EN : 1;   /* [7:7] Dsadc7 enabled - RW, for CHIP THA6412 */
    ureg32 DSADC8_EN : 1;   /* [8:8] Dsadc8 enabled - RW, for CHIP THA6412 */
    ureg32 DSADC9_EN : 1;   /* [9:9] Dsadc9 enabled - RW, for CHIP THA6412 */
    ureg32 reserved_10 : 2; /* [11:10] Internal reserved */
    ureg32 SARADC0_EN : 1;  /* [12:12] Saradc0 enable - RW */
    ureg32 SARADC1_EN : 1;  /* [13:13] Saradc1 enable - RW */
    ureg32 SARADC2_EN : 1;  /* [14:14] Saradc2 enable - RW */
    ureg32 SARADC3_EN : 1;  /* [15:15] Saradc3 enable - RW */
    ureg32 SARADC8_EN : 1;  /* [16:16] Saradc8 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 SARADC9_EN : 1;  /* [17:17] Saradc9 enable - RW , for CHIP THA6412 and THA6206*/
    ureg32 SARADC4_EN : 1;  /* [18:18] Saradc4 enable - RW, for CHIP THA6412 */
    ureg32 SARADC5_EN : 1;  /* [19:19] Saradc5 enable - RW, for CHIP THA6412 */
    ureg32 SARADC6_EN : 1;  /* [20:20] Saradc6 enable - RW, for CHIP THA6412 */
    ureg32 SARADC7_EN : 1;  /* [21:21] Saradc7 enable - RW, for CHIP THA6412 */
    ureg32 SARADC10_EN : 1; /* [22:22] Saradc10 enable - RW, for CHIP THA6412 */
    ureg32 SARADC11_EN : 1; /* [23:23] Saradc11 enable - RW, for CHIP THA6412 */
    ureg32 FC0_EN : 1;      /* [24:24] Fc0 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 FC1_EN : 1;      /* [25:25] Fc1 enabled - RW, for CHIP THA6412 and THA6206 */
    ureg32 FC2_EN : 1;      /* [26:26] Fc2 enable - RW, for CHIP THA6412 */
    ureg32 FC3_EN : 1;      /* [27:27] Fc3 enabled - RW, for CHIP THA6412 */
    ureg32 RDC0_EN : 1;     /* [28:28] Rdc0 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 RDC1_EN : 1;     /* [29:29] Rdc1 enable - RW, for CHIP THA6412 */
    ureg32 reserved_30 : 2; /* [31:30] Internal reserved */

} RCC_CLKEN5_Bits;

/* Module clock enable register 6 */
typedef struct
{
    ureg32 BASETIM0_EN : 1; /* [0:0] Basetim0 timclk1 enable - RW */
    ureg32 BASETIM1_EN : 1; /* [1:1] Basetim0 timclk2 enable - RW */
    ureg32 BASETIM2_EN : 1; /* [2:2] Basetim1 timclk1 enabled - RW */
    ureg32 BASETIM3_EN : 1; /* [3:3] Basetim1 timclk2 enabled - RW */
    ureg32 BASETIM4_EN : 1; /* [4:4] Basetim2 timclk1 enabled - RW, for CHIP THA6412 and THA6206 */
    ureg32 BASETIM5_EN : 1; /* [5:5] Basetim2 timclk2 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_6 : 6;  /* [11:6] Internal reserved */
    ureg32 GMU0_EN : 1;     /* [12:12] Gmu0 enable - RW */
    ureg32 GMU1_EN : 1;     /* [13:13] Gmu1 enable - RW, for CHIP THA6412 */
    ureg32 reserved_14 : 2; /* [15:14] Internal reserved */
    ureg32 LMU1_EN : 1;     /* [16:16] Lmu1 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 LMU2_EN : 1;     /* [17:17] Lmu2 enabled - RW */
    ureg32 LMU3_EN : 1;     /* [18:18] Lmu3 enable - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_19 : 9; /* [27:19] Internal reserved */
    ureg32 DBGCLK_EN : 1;   /* [28:28] Dbgclk enable - RW */
    ureg32 ATBCLK_EN : 1;   /* [29:29] Atbclk enabled - RW */
    ureg32 TRACECLK_EN : 1; /* [30:30] Traceclk enable - RW */
    ureg32 reserved_31 : 1; /* [31:31] Internal reserved */
} RCC_CLKEN6_Bits;

/* Module clock enable register 7 */
typedef struct
{
    ureg32 NVMHCLK0_EN : 1; /* [0:0] Cluster0 Nvm hclk enable - RW */
    ureg32 NVMPFC0_EN : 1;  /* [1:1] Nvm pfc0 enable - RW */
    ureg32 NVMPFC1_EN : 1;  /* [2:2] Nvm pfc1 enable - RW */
    ureg32 NVMDFC0_EN : 1;  /* [3:3] Nvm dfc0 enable - RW */
    ureg32 NVMPFC2_EN : 1;  /* [4:4] Nvm pfc2 enable - RW, for CHIP THA6412 */
    ureg32 NVMPFC3_EN : 1;  /* [5:5] Nvm pfc3 enable - RW, for CHIP THA6412 */
    ureg32 NVMHCLK1_EN : 1; /* [6:6] Cluster1 Nvm hclk enable - RW, for CHIP THA6412 */
    ureg32 reserved_7 : 25; /* [31:7] Internal reserved */
} RCC_CLKEN7_Bits;

/* Module clock enable register 8, for THA6412 */
typedef struct
{
    ureg32 SENT10_EN : 1;    /* [0:0] Sent10 enable - RW */
    ureg32 SENT11_EN : 1;    /* [1:1] Sent11 enable - RW */
    ureg32 SENT12_EN : 1;    /* [2:2] Sent12 enable - RW */
    ureg32 SENT13_EN : 1;    /* [3:3] Sent13 enable - RW */
    ureg32 SENT14_EN : 1;    /* [4:4] Sent14 enable - RW */
    ureg32 SENT15_EN : 1;    /* [5:5] Sent15 enable - RW */
    ureg32 SENT16_EN : 1;    /* [6:6] Sent16 enable - RW */
    ureg32 SENT17_EN : 1;    /* [7:7] Sent17 enable - RW */
    ureg32 SENT18_EN : 1;    /* [8:8] Sent18 enable - RW */
    ureg32 SENT19_EN : 1;    /* [9:9] Sent19 enable - RW */
    ureg32 SENT20_EN : 1;    /* [10:10] Sent20 enable - RW */
    ureg32 SENT21_EN : 1;    /* [11:11] Sent21 enable - RW */
    ureg32 SENT22_EN : 1;    /* [12:12] Sent22 enable - RW */
    ureg32 SENT23_EN : 1;    /* [13:13] Sent23 enable - RW */
    ureg32 SENT24_EN : 1;    /* [14:14] Sent14 enable - RW */
    ureg32 reserved_15 : 17; /* [31:15] Internal reserved */
} RCC_CLKEN8_Bits;

/* Module clock enable register 9 */
typedef struct
{
#if defined(THA6_THA6412)
    ureg32 ASI8_EN : 1;      /* [0:0] Asi8 enabled - RW */
    ureg32 ASI9_EN : 1;      /* [1:1] Asi9 enabled - RW */
    ureg32 ASI10_EN : 1;     /* [2:2] Asi10 enabled - RW */
    ureg32 ASI11_EN : 1;     /* [3:3] Asi11 enabled - RW */
    ureg32 ASI12_EN : 1;     /* [4:4] Asi12 enabled - RW */
    ureg32 ASI13_EN : 1;     /* [5:5] Asi13 enabled - RW */
    ureg32 ASI14_EN : 1;     /* [6:6] Asi14 enabled - RW */
    ureg32 ASI15_EN : 1;     /* [7:7] Asi15 enabled - RW */
    ureg32 ASI16_EN : 1;     /* [8:8] Asi16 enabled - RW */
    ureg32 ASI17_EN : 1;     /* [9:9] Asi17 enabled - RW */
    ureg32 ASI18_EN : 1;     /* [10:10] Asi18 enabled - RW */
    ureg32 ASI19_EN : 1;     /* [11:11] Asi19 enabled - RW */
    ureg32 ASI20_EN : 1;     /* [12:12] Asi20 enabled - RW */
    ureg32 ASI21_EN : 1;     /* [13:13] Asi21 enabled - RW */
    ureg32 ASI22_EN : 1;     /* [14:14] Asi22 enabled - RW */
    ureg32 ASI23_EN : 1;     /* [15:15] Asi23 enabled - RW */
    ureg32 reserved_16 : 16; /* [31:16] Internal reserved */
#endif
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
    ureg32 reserved_0 : 32; /* [31:0] Internal reserved */
#endif
#if defined(THA6_THA6104)
    ureg32 ASI8_EN : 1;     /* [0:0] Asi8 enabled - RW */
    ureg32 ASI9_EN : 1;     /* [1:1] Asi9 enabled - RW */
    ureg32 ASI10_EN : 1;    /* [2:2] Asi10 enabled - RW */
    ureg32 ASI11_EN : 1;    /* [3:3] Asi11 enabled - RW */
    ureg32 reserved_4 : 28; /* [31:4] Internal reserved */
#endif
} RCC_CLKEN9_Bits;

/* CPU Cluster1 clock enable register, for CHIP THA6104 and TAH6412 */
typedef struct
{
    ureg32 CLUSTER1_CLKEN : 1; /* [0:0] CPU Cluster1 clock enable - RW */
    ureg32 reserved_1 : 31;    /* [31:1] Internal reserved */
} RCC_CPUCLUSTER1CLKEN_Bits;

/* Process clock enable register, for CHIP TAH6412 and THA6104 */
typedef struct
{
    ureg32 PROCESS_CLK_EN : 1; /* [0:0] PROCESS_CLK enable - RW */
    ureg32 reserved_1 : 31;    /* [31:1] Internal reserved */
} RCC_CLKENPROC_Bits;

/* WDT module clock enable register */
typedef struct
{
    ureg32 SAFEWDT_EN : 1;  /* [0:0] SafeWDT enable - RW */
    ureg32 reserved_1 : 3;  /* [3:1] Internal reserved */
    ureg32 CPU0WDT_EN : 1;  /* [4:4] CPU0WDT enable - RW */
    ureg32 CPU1WDT_EN : 1;  /* [5:5] CPU1WDT enable - RW */
    ureg32 CPU2WDT_EN : 1;  /* [6:6] CPU2WDT enable - RW, for CHIP THA6412 */
    ureg32 CPU3WDT_EN : 1;  /* [7:7] CPU3WDT enable - RW, for CHIP  THA6412 */
    ureg32 reserved_8 : 24; /* [31:8] Internal reserved */
} RCC_CLKENWDT_Bits;

/* WDT module enable protection register */
typedef struct
{
    ureg32 CLKENWDTPROT : 32; /* [31:0] SafeWDT protection - RW */
} RCC_CLKENWDTPROT_Bits;

/* Module crossover enable register */
typedef struct
{
    ureg32 reserved_0 : 1;         /* [0:0] Internal reserved */
    ureg32 IPCNTCLKDIVEN : 1;      /* [1:1] Clock divider working enable - RW */
    ureg32 GTMCLKDIVEN : 1;        /* [2:2] Clock divider working enable - RW */
    ureg32 QSPICLKDIVEN : 1;       /* [3:3] Clock divider working enable - RW, for CHIP THA6206 and THA6412 */
    ureg32 ESPICLKDIVEN : 1;       /* [4:4] Clock divider working enable - RW */
    ureg32 CANCCLKDIVEN : 1;       /* [5:5] Clock divider working enable - RW */
    ureg32 reserved_6 : 1;         /* [6:6] Internal reserved */
    ureg32 RDCDSADCCLKDIVEN : 1;   /* [7:7] Clock divider working enable- RW, for CHIP THA6206 and THA6412  */
    ureg32 ASIBAUDCLKDIVEN : 1;    /* [8:8] Clock divider working enable - RW */
    ureg32 FCCLKDIVEN : 1;         /* [9:9] Clock divider working enable - RW, for CHIP THA6206 and THA6412 */
    ureg32 BASETIM0TCLK1DIVEN : 1; /* [10:10] Clock divider working enable - RW */
    ureg32 BASETIM0TCLK2DIVEN : 1; /* [11:11] Clock divider working enable - RW */
    ureg32 BASETIM1TCLK1DIVEN : 1; /* [12:12] Clock divider working enable - RW */
    ureg32 BASETIM1TCLK2DIVEN : 1; /* [13:13] Clock divider working enable - RW */
    ureg32 BASETIM2TCLK1DIVEN : 1; /* [14:14] Clock divider working enable - RW, for THA6206 and THA6412 */
    ureg32 BASETIM2TCLK2DIVEN : 1; /* [15:15] Clock divider working enable - RW, for THA6206 and THA6412 */
    ureg32 ATBCLKDIVEN : 1;        /* [16:16] Clock divider working enable - RW */
    ureg32 TRACECLKDIVEN : 1;      /* [17:17] Clock divider working enable - RW */
    ureg32 ISTCONCLKDIVEN : 1;     /* [18:18] Clock divider working enable - RW */
    ureg32 LBISTDCCLKDIVEN : 1;    /* [19:19] Clock divider working enable - RW */
    ureg32 CNTCLKDIVEN : 1;        /* [20:20] Clock divider working enable - RW */
    ureg32 CPUPCLKDBGDIVEN : 1;    /* [21:21] Clock divider working enable - RW */
    ureg32 CPUATCLKIDIVEN : 1;     /* [22:22] Clock divider working enable - RW */
    ureg32 CPUATCLKDDIVEN : 1;     /* [23:23] Clock divider working enable - RW */
    ureg32 MEMREPCONCLKDIVEN : 1;  /* [24:24] Clock divider working enable - RW, for CHIP THA6412 */
    ureg32 reserved_25 : 7;        /* [31:25] Internal reserved */
} RCC_CLKENDIV_Bits;

/* External clock output control register */
typedef struct
{
    ureg32 EXTCLK0_EN : 1;   /* [0:0] Ext0 pin clk output enable - RW */
    ureg32 EXTCLK1_EN : 1;   /* [1:1] Ext1 pin clk output enable - RW */
    ureg32 reserved_2 : 2;   /* [3:2] Internal reserved */
    ureg32 EXTCLK0_SEL : 5;  /* [8:4] Ext clk0 output clock selection - RW */
    ureg32 reserved_9 : 3;   /* [11:9] Internal reserved */
    ureg32 EXTCLK1_SEL : 5;  /* [16:12] Ext clk1 output clock selection - RW */
    ureg32 reserved_17 : 15; /* [31:17] Internal reserved */
} RCC_EXTCLKCON_Bits;

/* External clock output crossover register*/
typedef struct
{
    ureg32 EXTCLK0PRE_DIV : 10; /* [9:0] Configure icg integer division coefficient for extclk0pre - RW */
    ureg32 reserved_10 : 2;     /* [11:10] Internal reserved */
    ureg32 EXTCLK0_DIV : 1;     /* [12:12] Configure dff crossover coefficient for extclk0pre - RW */
    ureg32 reserved_13 : 3;     /* [15:13] Internal reserved */
    ureg32 EXTCLK1PRE_DIV : 10; /* [25:16] Icg integer frequency division coefficient configured for extclk1pre - RW */
    ureg32 reserved_26 : 2;     /* [27:26] Internal reserved */
    ureg32 EXTCLK1_DIV : 1;     /* [28:28] Configure dff crossover coefficient for extclk1pre - RW */
    ureg32 reserved_29 : 3;     /* [31:29] Internal reserved */
} RCC_EXTCLKDIV_Bits;

/* External clock divider register, for CHIP THA6104 and THA6412 */
typedef struct
{
    ureg32 EXTCLK0_DIVM : 2; /* [1:0] Divider Mode - RW */
    ureg32 reserved_2 : 14;  /* [15:2] Internal reserved */
    ureg32 EXTCLK1_DIVM : 2; /* [17:16] Divider Mode - RW */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
} RCC_EXTCLKDIVCFG_Bits;

/* System Clock Switch state register, for CHIP THA6104 and THA6412 */
typedef struct
{
    ureg32 SWFLAG : 1;      /* [0:0] Switch flag */
    ureg32 reserved_1 : 31; /* [31:18] Internal reserved */
} RCC_SYSCLKSWSTAT_Bits;

/* Peripheral clock Switch state register, for CHIP THA6104 and THA6412 */
typedef struct
{
#if defined(THA6_THA6412)
    ureg32 GTM_SWFLAG : 1;      /* [0:0] GTM Switch flag */
    ureg32 QSPI_SWFLAG : 1;     /* [1:1] QSPI Switch flag */
    ureg32 ESPI_SWFLAG : 1;     /* [2:2] ESPI Switch flag */
    ureg32 CAN_SWFLAG : 1;      /* [3:3] CAN Switch flag */
    ureg32 SARADC_SWFLAG : 1;   /* [4:4] SARADC Switch flag */
    ureg32 RDCDSADC_SWFLAG : 1; /* [5:5] RDC DSADC Switch flag */
    ureg32 MSC_SWFLAG : 1;      /* [6:6] MSC Switch flag */
    ureg32 CPUWDT_SWFLAG : 1;   /* [7:7] CPUWDT Switch flag */
    ureg32 FC_SWFLAG : 1;       /* [8:8] FC Switch flag */
    ureg32 TIM1_SWFLAG : 1;     /* [9:9] TIM1 Switch flag */
    ureg32 TIM2_SWFLAG : 1;     /* [10:10] TIM2 Switch flag */
    ureg32 TIM3_SWFLAG : 1;     /* [11:11] TIM3 Switch flag */
    ureg32 TIM4_SWFLAG : 1;     /* [12:12] TIM4 Switch flag */
    ureg32 TIM5_SWFLAG : 1;     /* [13:13] TIM5 Switch flag */
    ureg32 TIM6_SWFLAG : 1;     /* [14:14] TIM6 Switch flag */
    ureg32 reserved_15 : 17;    /* [31:15] Internal reserved */
#endif
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
    ureg32 reserved_0 : 32; /* [31:0] Internal reserved */
#endif
#if defined(THA6_THA6104)
    ureg32 GTM_SWFLAG : 1;     /* [0:0] GTM Switch flag */
    ureg32 reserved_1 : 1;     /* [1:1] QSPI Switch flag */
    ureg32 ESPI_SWFLAG : 1;    /* [2:2] ESPI Switch flag */
    ureg32 CAN_SWFLAG : 1;     /* [3:3] CAN Switch flag */
    ureg32 SARADC_SWFLAG : 1;  /* [4:4] SARADC Switch flag */
    ureg32 reserved_5 : 2;     /* [6:5] RDC DSADC Switch flag */
    ureg32 CPUWDT_SWFLAG : 1;  /* [7:7] CPUWDT Switch flag */
    ureg32 reserved_8 : 1;     /* [8:8] FC Switch flag */
    ureg32 TIM1_SWFLAG : 1;    /* [9:9] TIM1 Switch flag */
    ureg32 TIM2_SWFLAG : 1;    /* [10:10] TIM2 Switch flag */
    ureg32 TIM3_SWFLAG : 1;    /* [11:11] TIM3 Switch flag */
    ureg32 TIM4_SWFLAG : 1;    /* [12:12] TIM4 Switch flag */
    ureg32 reserved_13 : 2;    /* [14:13] TIM5 Switch flag */
    ureg32 ASIBUAD_SWFLAG : 1; /* [15:15] ASI BAUD Switch flag */
    ureg32 reserved_16 : 16;   /* [31:16] Internal reserved */
#endif

} RCC_PERCLKSWSTAT_Bits;

/* Pll lock control register */
typedef struct
{
    ureg32 SYSPLL_SWITCHEN : 1; /* [0:0] After the syspll lock or alive alarm, the syspll clock switches to the control of
                                   the hsi clock. - RW */
    ureg32 PERPLL_SWITCHEN : 1; /* [1:1] After the perpll lock is locked, the perpll clock switches to the control of the
                                   hsi clock. - RW */
    ureg32 SYSPLL_LLALMEN : 1;  /* [2:2] Syspll lock alarm enable - RW */
    ureg32 PERPLL_LLALMEN : 1;  /* [3:3] Perpll lock alarm enable - RW */
    ureg32 reserved_4 : 28;     /* [31:4] Internal reserved */
} RCC_PLLLOCKCON_Bits;

/* Syspll clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Syspll clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_SYSPLLCLKMON_Bits;

/* Perpll clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Perpll clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVE_MON_EN : 1; /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_PERPLLMON_Bits;

/* Hse clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Hse clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_HSECLKCON_Bits;

/* Hsi clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Hsi clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Alive monitor enable - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Alive monitor self-test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_HSICLKMON_Bits;

/* Lsi clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Lsi clk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 reserved_27 : 5;  /* [31:27] Internal reserved */
} RCC_LSICLKMON_Bits;

/* Cpu clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Cpu clk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_CPUCLKMON_Bits;

/* Sysclk clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Sys_clk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_SYSCLKMON_Bits;

/* Axi bus clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Axi clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_AXICLKMON_Bits;

/* Ahb bus clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Apb clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_AHBCLKMON_Bits;

/* Standby domain apb bus clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Apb_stb_clk clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_APBSTBCLKMON_Bits;

/* Wdt clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Cpu_wdt_clk clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_WDTCLKMON_Bits;

/* Ipcnt clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Ipcnt_clk clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_IPCNTCLKMON_Bits;

/* Iwdg clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Wdg_clk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 reserved_27 : 5;  /* [31:27] Internal reserved */
} RCC_IWDGCLKMON_Bits;

/* Gtm clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Gtm clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_GTMCLKMON_Bits;

/* Qspi clock monitoring register, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Qspi_clk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_QSPICLKMON_Bits;

/* Espi clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Espi_clk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_ESPICLKMON_Bits;

/* Cancclk clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Can_cclk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIV_MON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_CANCCLKMON_Bits;

/* Saradc clock monitoring register */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Saradc_clk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_SARADCCLKMON_Bits;

/* Rdc clock monitoring register, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Rdc_clk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_RDCCLKMON_Bits;

/* Dsadc clock monitoring register, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Dsadc_clk clock frequency monitoring enable - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_DSADCCLKMON_Bits;

/* Msc clock monitoring register, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Msc_clk clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_MSCCLKMON_Bits;

/* FC clock monitoring register, for CHIP THA6206 and THA6412 */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Msc_clk clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_FCCLKMON_Bits;

/* Cpu clock cluster1 monitoring register, for CHIP THA6412 */
typedef struct
{
    ureg32 CLUSTER1_FREQMON_EN : 1;   /* [0:0] Cpu cluster1 clock frequency monitoring enabled - RW */
    ureg32 CLUSTER1_UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 CLUSTER1_LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 CLUSTER1_ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 CLUSTER1_ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 CLUSTER1_MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;           /* [31:30] Internal reserved */
} RCC_CPUCLKCLUSTER1MON_Bits;

/* AXI NVM CFG clock monitoring register for THA6104 */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Process clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_AXINVMCFGCLKMON_Bits;

/* Process clock monitoring register, for CHIP THA6104 and THA6412 */
typedef struct
{
    ureg32 FREQMON_EN : 1;   /* [0:0] Process clock frequency monitoring enabled - RW */
    ureg32 UPPER_VAL : 12;   /* [12:1] Frequency monitoring preset high threshold - RW */
    ureg32 LOWER_VAL : 12;   /* [24:13] Frequency monitoring preset low threshold - RW */
    ureg32 ALIVEMON_EN : 1;  /* [25:25] Frequency alive monitoring enabled - RW */
    ureg32 ALIVETEST_EN : 1; /* [26:26] Frequency alive monitoring self test enable - RW */
    ureg32 MONALIVE_DIV : 3; /* [29:27] Alive monitor clock divide */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_PROCCLKMON_Bits;

/* Process clock Frequency register, for CHIP THA6104 and THA6412 */
typedef struct
{
    ureg32 FREQUENCY : 16;       /* [15:0] Process clock valid - RO */
    ureg32 FREQ_VALID_FLAG : 16; /* [31:16] Process clock frequency - RO */
} RCC_PROCCLKFREQ_Bits;

/* Clock frequency monitoring status register 1 */
typedef struct
{
    ureg32 SYSPLL_UPFLAG : 1;          /* [0:0] This clock frequency monitors status bit 1 - RO */
    ureg32 SYSPLL_LOWFLAG : 1;         /* [1:1] This clock frequency monitors status bit 2 - RO */
    ureg32 PERPLL_UPFLAG : 1;          /* [2:2] This clock frequency monitors status bit 1 - RO */
    ureg32 PERPLL_LOWFLAG : 1;         /* [3:3] This clock frequency monitors status bit 2 - RO */
    ureg32 HSE_UPFLAG : 1;             /* [4:4] This clock frequency monitors status bit 1 - RO */
    ureg32 HSE_LOWFLAG : 1;            /* [5:5] This clock frequency monitors status bit 2 - RO */
    ureg32 HSI_UPFLAG : 1;             /* [6:6] This clock frequency monitors status bit 1 - RO */
    ureg32 HSI_LOWFLAG : 1;            /* [7:7] This clock frequency monitors status bit 2 - RO */
    ureg32 LSI_UPFLAG : 1;             /* [8:8] This clock frequency monitors status bit 1 - RO */
    ureg32 LSI_LOWFLAG : 1;            /* [9:9] This clock frequency monitors status bit 2 - RO */
    ureg32 CPUCLKCLUSTER0_UPFLAG : 1;  /* [10:10] This clock frequency monitors status bit 1 - RO */
    ureg32 CPUCLKCLUSTER0_LOWFLAG : 1; /* [11:11] This clock frequency monitors status bit 2 - RO */
    ureg32 SYSCLK_UPFLAG : 1;          /* [12:12] This clock frequency monitors status bit 1 - RO */
    ureg32 SYSCLK_LOWFLAG : 1;         /* [13:13] This clock frequency monitors status bit 2 - RO */
    ureg32 AXI_UPFLAG : 1;             /* [14:14] This clock frequency monitors status bit 1 - RO */
    ureg32 AXI_LOWFLAG : 1;            /* [15:15] This clock frequency monitors status bit 2 - RO */
    ureg32 AHB_UPFLAG : 1;             /* [16:16] This clock frequency monitors status bit 1 - RO */
    ureg32 AHB_LOWFLAG : 1;            /* [17:17] This clock frequency monitors status bit 2 - RO */
    ureg32 APBSTB_UPFLAG : 1;          /* [18:18] This clock frequency monitors status bit 1 - RO */
    ureg32 APBSTB_LOWFLAG : 1;         /* [19:19] This clock frequency monitors status bit 2 - RO */
    ureg32 WDT_UPFLAG : 1;             /* [20:20] This clock frequency monitors status bit 1 - RO */
    ureg32 WDT_LOWFLAG : 1;            /* [21:21] This clock frequency monitors status bit 2 - RO */
    ureg32 IPCNT_UPFLAG : 1;           /* [22:22] This clock frequency monitors status bit 1 - RO */
    ureg32 IPCNT_LOWFLAG : 1;          /* [23:23] This clock frequency monitors status bit 2 - RO */
    ureg32 IWDG_UPFLAG : 1;            /* [24:24] This clock frequency monitors status bit 1 - RO */
    ureg32 IWDG_LOWFLAG : 1;           /* [25:25] This clock frequency monitors status bit 2 - RO */
    ureg32 GTM_UPFLAG : 1;             /* [26:26] This clock frequency monitors status bit 1 - RO */
    ureg32 GTM_LOWFLAG : 1;            /* [27:27] This clock frequency monitors status bit 2 - RO */
    ureg32 QSPI_UPFLAG : 1;            /* [28:28] This clock frequency monitors status bit 1 - RO, for CHIP THA6206 and THA6412 */
    ureg32 QSPI_LOWFLAG : 1;           /* [29:29] This clock frequency monitors status bit 2 - RO, for CHIP THA6206 and THA6412 */
    ureg32 ESPI_UPFLAG : 1;            /* [30:30] This clock frequency monitors status bit 1 - RO */
    ureg32 ESPI_LOWFLAG : 1;           /* [31:31] This clock frequency monitors status bit 2 - RO */
} RCC_CLKFREQMONSTAT1_Bits;

/* Clock frequency monitoring status clear register 1 */
typedef struct
{
    ureg32 SYSPLL_FLAGCLR : 1;         /* [0:0] The clock monitors status clearance - RW */
    ureg32 reserved_1 : 1;             /* [1:1] Internal reserved */
    ureg32 PERPLL_FLAGCLR : 1;         /* [2:2] The clock monitors status clearance - RW */
    ureg32 reserved_3 : 1;             /* [3:3] Internal reserved */
    ureg32 HSE_FLAGCLR : 1;            /* [4:4] The clock monitors status clearance - RW */
    ureg32 reserved_5 : 1;             /* [5:5] Internal reserved */
    ureg32 HSI_FLAGCLR : 1;            /* [6:6] Hsi monitoring status clear - RW */
    ureg32 reserved_7 : 1;             /* [7:7] Internal reserved */
    ureg32 LSICLK_FLAGCLR : 1;         /* [8:8] The clock monitors status clearance - RW */
    ureg32 reserved_9 : 1;             /* [9:9] Internal reserved */
    ureg32 CPUCLKCLUSTER0_FLAGCLR : 1; /* [10:10] The clock monitors status clearance - RW */
    ureg32 reserved_11 : 1;            /* [11:11] Internal reserved */
    ureg32 SYSCLK_FLAGCLR : 1;         /* [12:12] The clock monitors status clearance - RW */
    ureg32 reserved_13 : 1;            /* [13:13] Internal reserved */
    ureg32 AXI_FLAGCLR : 1;            /* [14:14] The clock monitors status clearance - RW */
    ureg32 reserved_15 : 1;            /* [15:15] Internal reserved */
    ureg32 AHB_FLAGCLR : 1;            /* [16:16] The clock monitors status clearance - RW */
    ureg32 reserved_17 : 1;            /* [17:17] Internal reserved */
    ureg32 APBSTB_FLAGCLR : 1;         /* [18:18] The clock monitors status clearance - RW */
    ureg32 reserved_19 : 1;            /* [19:19] Internal reserved */
    ureg32 WDT_FLAGCLR : 1;            /* [20:20] The clock monitors status clearance - RW */
    ureg32 reserved_21 : 1;            /* [21:21] Internal reserved */
    ureg32 IPCNT_FLAGCLR : 1;          /* [22:22] The clock monitors status clearance - RW */
    ureg32 reserved_23 : 1;            /* [23:23] Internal reserved */
    ureg32 IWDG_FLAGCLR : 1;           /* [24:24] The clock monitors status clearance - RW */
    ureg32 reserved_25 : 1;            /* [25:25] Internal reserved */
    ureg32 GTM_FLAGCLR : 1;            /* [26:26] The clock monitors status clearance - RW */
    ureg32 reserved_27 : 1;            /* [27:27] Internal reserved */
    ureg32 QSPI_FLAGCLR : 1;           /* [28:28] The clock monitors status clearance - RW, for CHIP THA6206 and THA6412 */
    ureg32 reserved_29 : 1;            /* [29:29] Internal reserved */
    ureg32 ESPI_FLAGCLR : 1;           /* [30:30] The clock monitors status clearance - RW */
    ureg32 reserved_31 : 1;            /* [31:31] Internal reserved */
} RCC_CLKFREQMONSTAT1CLR_Bits;

/* Clock frequency monitoring status register 2 */
typedef struct
{
    ureg32 CAN_UPPERFLAG : 1;            /* [0:0] This clock frequency monitors status bit 1 - RO */
    ureg32 CAN_LOWERFLAG : 1;            /* [1:1] This clock frequency monitors status bit 2 - RO */
    ureg32 SARADC_UPPERFLAG : 1;         /* [2:2] This clock frequency monitors status bit 1 - RO */
    ureg32 SARADC_LOWERFLAG : 1;         /* [3:3] This clock frequency monitors status bit 2 - RO, for CHIP THA6412 and THA6206 */
    ureg32 RDC_UPPERFLAG : 1;            /* [4:4] This clock frequency monitors status bit 1 - RO , for CHIP THA6412 and THA6206*/
    ureg32 RDC_LOWERFLAG : 1;            /* [5:5] This clock frequency monitors status bit 2 - RO, for CHIP THA6412 and THA6206 */
    ureg32 DSADC_UPPERFLAG : 1;          /* [6:6] This clock frequency monitors status bit 1 - RO, for CHIP THA6412 and THA6206 */
    ureg32 DSADC_LOWERFLAG : 1;          /* [7:7] This clock frequency monitors status bit 2 - RO , for CHIP THA6412 and THA6206*/
    ureg32 MSC_UPPERFLAG : 1;            /* [8:8] This clock frequency monitors status bit 1 - RO, for CHIP THA6412 and THA6206 */
    ureg32 MSC_LOWERFLAG : 1;            /* [9:9] This clock frequency monitors status bit 2 - RO, for CHIP THA6412 and THA6206 */
    ureg32 FC_UPPERFLAG : 1;             /* [10:10] This clock frequency monitors status bit 1 - RO, for CHIP THA6412 and THA6206 */
    ureg32 FC_LOWERFLAG : 1;             /* [11:11] This clock frequency monitors status bit 2 - RO, for CHIP THA6412 and THA6206 */
    ureg32 PROC_UPPERFLAG : 1;           /* [12:12] This clock frequency monitors status bit 0 - RO, for CHIP THA6412 */
    ureg32 PROC_LOWERFLAG : 1;           /* [13:13] This clock frequency monitors status bit 1 - RO, for CHIP THA6412 */
    ureg32 CPUCLKCLUSTER1_UPPERFLAG : 1; /* [14:14] This clock frequency monitors status bit 0 - RO, for CHIP THA6412 */
    ureg32 CPUCLKCLUSTER1_LOWERFLAG : 1; /* [15:15] This clock frequency monitors status bit 1 - RO, for CHIP THA6412 */
    ureg32 reserved_16 : 16;             /* [31:16] Internal reserved */

} RCC_CLKFREQMONSTAT2_Bits;

/* Clock frequency monitoring status clear register 2 */
typedef struct
{
    ureg32 CAN_FLAGCLR : 1;            /* [0:0] The clock monitors status clearance - RW */
    ureg32 reserved_1 : 1;             /* [1:1] Internal reserved */
    ureg32 SARADC_FLAGCLR : 1;         /* [2:2] The clock monitors status clearance - RW */
    ureg32 reserved_3 : 1;             /* [3:3] Internal reserved */
    ureg32 RDC_FLAGCLR : 1;            /* [4:4] The clock monitors status clearance - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_5 : 1;             /* [5:5] Internal reserved */
    ureg32 DSADC_FLAGCLR : 1;          /* [6:6] The clock monitors status clearance - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_7 : 1;             /* [7:7] Internal reserved */
    ureg32 MSC_FLAGCLR : 1;            /* [8:8] The clock monitors status clearance - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_9 : 1;             /* [9:9] Internal reserved */
    ureg32 FC_FLAGCLR : 1;             /* [10:10] The clock monitors status clearance - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_11 : 1;            /* [11:11] Internal reserved */
    ureg32 PROC_FLAGCLR : 1;           /* [12:12] The clock monitors status clearance - RW, for CHIP THA6412 */
    ureg32 reserved_13 : 1;            /* [13:13] Internal reserved */
    ureg32 CPUCLKCLUSTER1_FLAGCLR : 1; /* [14:14] The clock monitors status clearance - RW, for CHIP THA6412 */
    ureg32 reserved_15 : 17;           /* [31:15] Internal reserved */

} RCC_CLKFREQMONSTAT2CLR_Bits;

/* Clock alive monitoring status register */
typedef struct
{
    ureg32 SYSPLL_ERRFLAG : 1;          /* [0:0] The clock is alive to monitor status bits - RO */
    ureg32 PERPLL_ERRFLAG : 1;          /* [1:1] The clock is alive to monitor status bits - RO */
    ureg32 HSE_ERRFLAG : 1;             /* [2:2] The clock is alive to monitor status bits - RO */
    ureg32 HSI_ERRFLAG : 1;             /* [3:3] The clock is alive to monitor status bits - RO */
    ureg32 LSI_ERRFLAG : 1;             /* [4:4] The clock is alive to monitor status bits - RO */
    ureg32 CPUCLKCLUSTER0_ERRFLAG : 1;  /* [5:5] The clock is alive to monitor status bits - RO */
    ureg32 SYSCLK_ERRFLAG : 1;          /* [6:6] The clock is alive to monitor status bits - RO */
    ureg32 AXI_ERRFLAG : 1;             /* [7:7] The clock is alive to monitor status bits - RO */
    ureg32 AHB_ERRFLAG : 1;             /* [8:8] The clock is alive to monitor status bits - RO */
    ureg32 APBSTB_ERRFLAG : 1;          /* [9:9] The clock is alive to monitor status bits - RO */
    ureg32 WDT_ERRFLAG : 1;             /* [10:10] The clock is alive to monitor status bits - RO */
    ureg32 IPCNT_ERRFLAG : 1;           /* [11:11] The clock is alive to monitor status bits - RO */
    ureg32 IWDG_ERRFLAG : 1;            /* [12:12] The clock is alive to monitor status bits - RO */
    ureg32 GTM_ERRFLAG : 1;             /* [13:13] The clock is alive to monitor status bits - RO */
    ureg32 QSPI_ERRFLAG : 1;            /* [14:14] The clock is alive to monitor status bits - RO, for CHIP THA6206 and THA6412 */
    ureg32 ESPI_ERRFLAG : 1;            /* [15:15] The clock is alive to monitor status bits - RO */
    ureg32 CAN_ERRFLAG : 1;             /* [16:16] The clock is alive to monitor status bits - RO */
    ureg32 SARADC_ERRFLAG : 1;          /* [17:17] The clock is alive to monitor status bits - RO */
    ureg32 RDC_ERRFLAG : 1;             /* [18:18] The clock is alive to monitor status bits - RO, for CHIP THA6206 and THA6412*/
    ureg32 DSADC_ERRFLAG : 1;           /* [19:19] The clock is alive to monitor status bits - RO, for CHIP THA6206 and THA6412 */
    ureg32 MSC_ERRFLAG : 1;             /* [20:20] The clock is alive to monitor status bits - RO, for CHIP THA6206 and THA6412 */
    ureg32 FC_ERRFLAG : 1;              /* [21:21] The clock is alive to monitor status bits - RO, for CHIP THA6206 and THA6412 */
    ureg32 SYSPLL_LOCKLOSS_ERRFLAG : 1; /* [22:22] The clock is alive to monitor status bits - RO */
    ureg32 PERPLL_LOCKLOSS_ERRFLAG : 1; /* [23:23] The clock is alive to monitor status bits - RO */
    ureg32 PROC_ERRFLAG : 1;            /* [24:24] The clock is alive to monitor status bits - RO, for CHIP THA6412 */
    ureg32 CPUCLKCLUSTER1_ERRFLAG : 1;  /* [25:25] The clock is alive to monitor status bits - RO, for CHIP THA6412 */
    ureg32 AXINVMCFG_ERRFLAG : 1;       /* [26:26] The clock is alive to monitor status bits - RO, for CHIP THA6104 */
    ureg32 reserved_27 : 5;             /* [31:27] Internal reserved */
} RCC_CLKALIVESTAT_Bits;

/* Clock alive monitoring status clear register */
typedef struct
{
    ureg32 SYSPLL_ERRCLR : 1;          /* [0:0] The clock is in a state to clear - RW */
    ureg32 PERPLL_ERRCLR : 1;          /* [1:1] The clock is in a state to clear - RW */
    ureg32 HSE_ERRCLR : 1;             /* [2:2] The clock is in a state to clear - RW */
    ureg32 HSI_ERRCLR : 1;             /* [3:3] The clock is in a state to clear - RW */
    ureg32 LSI_ERRCLR : 1;             /* [4:4] The clock is in a state to clear - RW */
    ureg32 CPUCLKCLUSTER0_ERRCLR : 1;  /* [5:5] The clock is in a state to clear - RW */
    ureg32 SYSCLK_ERRCLR : 1;          /* [6:6] The clock is in a state to clear - RW */
    ureg32 AXI_ERRCLR : 1;             /* [7:7] The clock is in a state to clear - RW */
    ureg32 AHB_ERRCLR : 1;             /* [8:8] The clock is in a state to clear - RW */
    ureg32 APBSTB_ERRCLR : 1;          /* [9:9] The clock is in a state to clear - RW */
    ureg32 WDT_ERRCLR : 1;             /* [10:10] The clock is in a state to clear - RW */
    ureg32 IPCNT_ERRCLR : 1;           /* [11:11] The clock is in a state to clear - RW */
    ureg32 IWDG_ERRCLR : 1;            /* [12:12] The clock is in a state to clear - RW */
    ureg32 GTM_ERRCLR : 1;             /* [13:13] The clock is in a state to clear - RW */
    ureg32 QSPI_ERRCLR : 1;            /* [14:14] The clock is in a state to clear - RW, for CHIP THA6206 and THA6412 */
    ureg32 ESPI_ERRCLR : 1;            /* [15:15] The clock is in a state to clear - RW */
    ureg32 CAN_ERR_CLR : 1;            /* [16:16] The clock is in a state to clear - RW */
    ureg32 SARADC_ERRCLR : 1;          /* [17:17] The clock is in a state to clear - RW */
    ureg32 RDC_ERRCLR : 1;             /* [18:18] The clock is in a state to clear - RW, for CHIP THA6206 and THA6412 */
    ureg32 DSADC_ERRCLR : 1;           /* [19:19] The clock is in a state to clear - RW, for CHIP THA6206 and THA6412 */
    ureg32 MSC_ERRCLR : 1;             /* [20:20] The clock is in a state to clear - RW, for CHIP THA6206 and THA6412 */
    ureg32 FC_ERRCLR : 1;              /* [21:21] The clock is in a state to clear - RW, for CHIP THA6206 and THA6412 */
    ureg32 SYSPLL_LOCKLOSS_ERRCLR : 1; /* [22:22] The clock is in a state to clear - RW */
    ureg32 PERPLL_LOCKLOSS_ERRCLR : 1; /* [23:23] The clock is in a state to clear - RW */
    ureg32 PROC_ERRCLR : 1;            /* [24:24] The clock is in a state to clear - RW, for CHIP THA6412 */
    ureg32 CPUCLKCLUSTER1_ERRCLR : 1;  /* [25:25] The clock is in a state to clear - RW, for CHIP THA6412 */
    ureg32 AXINVMCFG_ERRCLR : 1;       /*[26:26] The clock is in a state to clear - RW, for CHIP THA6104 */
    ureg32 reserved_27 : 5;            /* [31:27] Internal reserved */
} RCC_CLKALIVESTATCLR_Bits;

/* Clock security alarm enable register */
typedef struct
{
    ureg32 CLKSFFALMSMEN : 1; /* [0:0] Clock security alarm enable */
    ureg32 reserved_1 : 31;   /* [31:1] Internal reserved */
} RCC_CLKSFFALMSMEN_Bits;

/* Clock security register alarm status register */
typedef struct
{
    ureg32 G0CLKSFF_ALMFLAG : 1;     /* [0:0] This security register alarm status bit - RO */
    ureg32 G1CLKSFF_ALMFLAG : 1;     /* [1:1] This security register alarm status bit - RO */
    ureg32 G2CLKSFF_ALMFLAG : 1;     /* [2:2] This security register alarm status bit - RO */
    ureg32 G3CLKSFF_ALMFLAG : 1;     /* [3:3] This security register alarm status bit - RO */
    ureg32 G4CLKSFF_ALMFLAG : 1;     /* [4:4] This security register alarm status bit - RO */
    ureg32 G5CLKSFF_ALMFLAG : 1;     /* [5:5] This security register alarm status bit - RO */
    ureg32 G6CLKSFF_ALMFLAG : 1;     /* [6:6] This security register alarm status bit - RO */
    ureg32 G7CLKSFF_ALMFLAG : 1;     /* [7:7] This security register alarm status bit - RO */
    ureg32 ALM_OSCTRIMCON : 1;       /* [8:8] This security register alarm status bit - RO, for CHIP THA6412 and THA6104 */
    ureg32 ALM_XTALTRIMCON : 1;      /* [9:9] This security register alarm status bit - RO, for CHIP THA6412 and THA6104 */
    ureg32 ALM_CLKENCPUCLUSTER0 : 1; /* [10:10] This security register alarm status bit - RO, for CHIP THA6412 */
    ureg32 ALM_CLKENCPUCLUSTER1 : 1; /* [11:11] This security register alarm status bit - RO, for CHIP THA6412 */
    ureg32 reserved_12 : 20;         /* [31:12] Internal reserved */
} RCC_CLKSFFALMSTAT_Bits;

/* Clock security register alarm status clear register */
typedef struct
{
    ureg32 CLKSFFALMSTSCLR : 1; /* [0:0] Security register alarm status bit  - RW */
    ureg32 reserved_1 : 31;     /* [31:1] Internal reserved */
} RCC_CLKSFFALMSTATCLR_Bits;

/* Clock safety register alarm status injection register */
typedef struct
{
    ureg32 CLKSFFALM1FAULTIN : 1; /* [0:0] Safety register fault injection, - RW */
    ureg32 reserved_1 : 31;       /* [31:1] Internal reserved */
} RCC_CLKSFFALMFAULTIN_Bits;

/* Clock domain bus error mask register */
typedef struct
{
    ureg32 CLKBEMASK : 1;   /* [0:0] Clock domain bus error mask register - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_CLKBEMASK_Bits;

/* Access E/SE trigger alarm register */
typedef struct
{
    ureg32 CLKEALMSTAT : 1;  /* [0:0] Access E trigger alarm register - RW */
    ureg32 CLKSEALMSTAT : 1; /* [1:1] Access SE trigger alarm register - RW */
    ureg32 reserved_2 : 30;  /* [31:2] Internal reserved */
} RCC_CLKESEALMSTAT_Bits;

/* Access E/SE trigger alarm clear register */
typedef struct
{
    ureg32 CLKEALMSTATCLR : 1;  /* [0:0] Access E trigger alarm clear register - RW */
    ureg32 CLKSEALMSTATCLR : 1; /* [1:1] Access SE trigger alarm clear register - RW */
    ureg32 reserved_2 : 30;     /* [31:2] Internal reserved */
} RCC_CLKESEALMSTATCLR_Bits;

/**********************************************************************************************************************
 *                                        RCC RST Register Bit-Fields Definitions
 *********************************************************************************************************************/

/* Reset status register */
typedef struct
{
    ureg32 ESR0RSTSTA : 1;      /* [0:0] Esr0 request triggered reset status - RO */
    ureg32 ESR1RSTSTA : 1;      /* [1:1] Esr1 request triggered reset status - RO */
    ureg32 SACRSTSTA : 1;       /* [2:2] Sac request triggered reset status - RO */
    ureg32 SWRSTSTA : 1;        /* [3:3] Sw request triggered reset status - RO */
    ureg32 IWDGRSTSTA : 1;      /* [4:4] Iwdg request triggered reset status - RO */
    ureg32 CPU0DBGRSTSTA : 1;   /* [5:5] Cpu0 dbgrst - RO */
    ureg32 CPU1DBGRSTSTA : 1;   /* [6:6] Cpu1 dbgrst - RO */
    ureg32 CPU0WARMRSTSTA : 1;  /* [7:7] Cpu0 warmreset - RO */
    ureg32 CPU1WARMRSTSTA : 1;  /* [8:8] Cpu1 warmreset - RO */
    ureg32 HSMDBGSYSRSTSTA : 1; /* [9:9] Hsm_dbgsysresetreq request triggered reset status - RO */
    ureg32 CPU2DBGRSTSTA : 1;   /* [10:10] Cpu2 dbgrst - RO, for CHIP THA6412 */
    ureg32 CPU3DBGRSTSTA : 1;   /* [11:11] Cpu3 dbgrst - RO, for CHIP THA6412 */
    ureg32 CPU2WARMRSTSTA : 1;  /* [12:12] Cpu2 warmreset - RO, for CHIP THA6412 */
    ureg32 CPU3WARMRSTSTA : 1;  /* [13:13] Cpu3 warmreset - RO, for CHIP THA6412 */
    ureg32 reserved_14 : 2;     /* [15:14] Internal reserved */
    ureg32 PORSTPINRSTSTA : 1;  /* [16:16] Porst pin request triggered reset status - RO */
    ureg32 ISTRSTSTA : 1;       /* [17:17] Internal reserved */
    ureg32 HSMAPPRSTSTA : 1;    /* [18:18] Hsm application reset request triggers reset status - RO */
    ureg32 HSMSYSRSTSTA : 1;    /* [19:19] Hsm system reset request triggers reset status - RO */
    ureg32 reserved_20 : 3;     /* [22:20] Internal reserved */
    ureg32 PORRSTSTA : 1;       /* [23:23] Power-on reset flag (default is 1 b1) - RO */
    ureg32 reserved_24 : 8;     /* [31:24] Internal reserved */
} RCC_RSTSTAT_Bits;

/* Reset status clear register */
typedef struct
{
    ureg32 ESR0_RSTCLR : 1;        /* [0:0] Rststat status clear - WO */
    ureg32 ESR1_RSTCLR : 1;        /* [1:1] Rststat status clear - WO */
    ureg32 SAC_RSTCLR : 1;         /* [2:2] Rststat status clear - WO */
    ureg32 SW_RSTCLR : 1;          /* [3:3] Rststat status clear - WO */
    ureg32 IWDG_RSTCLR : 1;        /* [4:4] Rststat status clear - WO */
    ureg32 CPU0_DBGRSTREQ : 1;     /* [5:5] Rststat status clear - WO */
    ureg32 CPU1_DBGRSTREQ : 1;     /* [6:6] Rststat status clear - WO */
    ureg32 CPU0_WARMRESETREQ : 1;  /* [7:7] Rststat status clear - WO */
    ureg32 CPU1_WARMRESETREQ : 1;  /* [8:8] Rststat status clear - WO */
    ureg32 HSM_DBGSYSRESETREQ : 1; /* [9:9] Rststat status clear - WO */
    ureg32 CPU2_DBGRSTREQ : 1;     /* [10:10] Rststat status clear - WO, for CHIP THA6412 */
    ureg32 CPU3_DBGRSTREQ : 1;     /* [11:11] Rststat status clear - WO, for CHIP THA6412 */
    ureg32 CPU2_WARMRESETREQ : 1;  /* [12:12] Rststat status clear - WO, for CHIP THA6412 */
    ureg32 CPU3_WARMRESETREQ : 1;  /* [13:13] Rststat status clear - WO, for CHIP THA6412 */
    ureg32 reserved_14 : 2;        /* [15:14] Internal reserved */
    ureg32 PORST_PIN : 1;          /* [16:16] Rststat status clear - WO */
    ureg32 IST_REQSTAT : 1;        /* [17:17] Rststat status clear - WO */
    ureg32 HSM_APP : 1;            /* [18:18] Rststat status clear - WO */
    ureg32 HSM_SYS : 1;            /* [19:19] Rststat status clear - WO */
    ureg32 reserved_20 : 3;        /* [22:20] Internal reserved */
    ureg32 POR_STAT : 1;           /* [23:23] Rststat status clear - WO */
    ureg32 reserved_24 : 8;        /* [31:24] Internal reserved */
} RCC_RSTSTATCLR_Bits;

/* Sac reset request flag register */
typedef struct
{
    ureg32 RSTFLAG : 1;     /* [0:0] Sac reset request flag bit - RO */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_SACRSTFLAG_Bits;

/* Sac reset request flag clear register */
typedef struct
{
    ureg32 SACRSTCLR : 1;   /* [0:0] Sac reset request flag clear - WO */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_SACRSTCLR_Bits;

/* Software reset register (sw triggered rst) */
typedef struct
{
    ureg32 SWRSTREQ : 1;    /* [0:0] Software reset request - w */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_SWRSTCON_Bits;

/* Reset control register 1 */
typedef struct
{
    ureg32 ESR0RST_SEL : 2;      /* [1:0] Esr0 reset request triggered reset configuration - RW */
    ureg32 ESR1RST_SEL : 2;      /* [3:2] Esr1 reset request triggered reset configuration - RW */
    ureg32 SACRST_SEL : 2;       /* [5:4] Sac reset request triggered reset configuration - RW */
    ureg32 SWRST_SEL : 2;        /* [7:6] Sw reset request triggered reset configuration - RW */
    ureg32 IWDGRST_SEL : 2;      /* [9:8] Iwdg reset request triggered reset configuration - RW */
    ureg32 CPU2_WARMREQRST : 2;  /* [11:10] Cpu2_warmrst_req reset request trigger reset configuration - RW, for CHIP THA6412 */
    ureg32 CPU3_WARMREQRST : 2;  /* [13:12] Cpu3_warmrst_req reset request triggered reset configuration - RW, for CHIP THA6412 */
    ureg32 CPU0_WARMREQRST : 2;  /* [15:14] Cpu0_warmrst_req reset request trigger reset configuration - RW */
    ureg32 CPU1_WARMREQRST : 2;  /* [17:16] Cpu1_warmrst_req reset request triggered reset configuration - RW */
    ureg32 HSM_DBGSYSRSTREQ : 2; /* [19:18] Hsm dbg - RW */
    ureg32 reserved_20 : 12;     /* [31:20] Internal reserved */
} RCC_RSTCON1_Bits;

/* Reset control register 2 */
typedef struct
{
    ureg32 HSM_APP : 2;     /* [1:0] Hsm application reset request triggered reset configuration - RO */
    ureg32 HSM_SYS : 2;     /* [3:2] Hsm system reset request triggers reset configuration, - RO */
    ureg32 reserved_4 : 28; /* [31:4] Internal reserved */
} RCC_RSTCON2_Bits;

/* Reset control register 3 */
typedef struct
{
    ureg32 CPU0_DBG_RST_REQ : 2; /* [1:0] CPU0_DBG_RST reset request triggered reset configuration - RW */
    ureg32 CPU1_DBG_RST_REQ : 2; /* [3:2] CPU1_DBG_RST reset request triggered reset configuration - RW */
    ureg32 CPU2_DBG_RST_REQ : 2; /* [5:4] CPU2_DBG_RST reset request triggered reset configuration - RW, for CHIP THA6412 */
    ureg32 CPU3_DBG_RST_REQ : 2; /* [7:6] CPU3_DBG_RST reset request triggered reset configuration - RW, for CHIP THA6412 */
    ureg32 reserved_8 : 24;      /* [31:8] Internal reserved */
} RCC_RSTCON3_Bits;

/* Debug reset control register */
typedef struct
{
    ureg32 DBGRST : 1;      /* [0:0] Write rcc register trigger debug reset - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_DBGRSTCON_Bits;

/* Wdt reset type control register */
typedef struct
{
    ureg32 CPU0WDT_RSTTYPE : 1; /* [0:0] Cpu0 wdt reset type register - RW */
    ureg32 CPU1WDT_RSTTYPE : 1; /* [1:1] Cpu1 wdt reset type register - RW */
    ureg32 SAFEWDT_RSTTYPE : 1; /* [2:2] Safe wdt reset type register - RW */
    ureg32 CPU2WDT_RSTTYPE : 1; /* [3:3] Cpu2 wdt reset type register - RW, for CHIP THA6412 */
    ureg32 CPU3WDT_RSTTYPE : 1; /* [4:4] Cpu3 wdt reset type register - RW, for CHIP THA6412 */
    ureg32 reserved_5 : 27;     /* [31:5] Internal reserved */
} RCC_WDTRSTCON_Bits;

/* Wdt reset type control register */
typedef struct
{
    ureg32 STM_RSTTYPE : 1; /* [0:0] System timer reset type register - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_STMRSTCON_Bits;

/* Cpu cluster reset flag clear control register */
typedef struct
{
    ureg32 RSTCLR : 1;      /* [0:0] Cpu cluster reset flag clear - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_CPUCLUSTRSTCLR_Bits;

/* Cpu cluster reset control register */
typedef struct
{
    ureg32 NTOPRST : 1;      /* [0] Cpucluster reset control - RW */
    ureg32 NTOPRSTFLAG : 1;  /* [1] Cpucluster reset flag - RH */
    ureg32 reserved_2 : 2;   /* [3:2] Internal reserved */
    ureg32 NCORERESET0 : 1;  /* [4] core0 follow cluster reset select */
    ureg32 NCPUPORESET0 : 1; /* [5] CPU0 follow cluster reset select */
    ureg32 NCORERESET1 : 1;  /* [6] core1 follow cluster reset select */
    ureg32 NCPUPORESET1 : 1; /* [7] CPU1 follow cluster reset select */
    ureg32 reserved_8 : 24;  /* [8:31] Internal reserved */
} RCC_CPUCLUSTERRSTCON_Bits;

/* Cpu cluster reset control register */
typedef struct
{
    ureg32 NTOPRST : 1;      /* [0:0] Cpucluster reset control - RW */
    ureg32 NTOPRSTFLAG : 1;  /* [1:1] Cpucluster reset flag - RH */
    ureg32 reserved_2 : 2;   /* [3:2] Internal reserved */
    ureg32 NCORERESET2 : 1;  /* [4:4] core2 follow cluster reset select */
    ureg32 NCPUPORESET2 : 1; /* [5:5] CPU2 follow cluster reset select */
    ureg32 NCORERESET3 : 1;  /* [6:6] core3 follow cluster reset select */
    ureg32 NCPUPORESET3 : 1; /* [7:6] CPU3 follow cluster reset select */
    ureg32 reserved_8 : 24;  /* [8:31] Internal reserved */
} RCC_CPUCLUSTER1RSTCON_Bits;

/* Cpu0 reset control register */
typedef struct
{
    ureg32 CPURSTCLR : 1;   /* [0:0] Cpu reset state clear - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_CPURSTCLR_Bits;

/* Cpu0 core reset control register */
typedef struct
{
    ureg32 CORERST : 1;         /* [0:0] Core reset reset control - RW */
    ureg32 CORERSTFLAG : 1;     /* [1:1] Core reset flag - RH */
    ureg32 reserved_2 : 2;      /* [3:2] Internal reserved */
    ureg32 NCPUPRESET : 1;      /* [4:4] NCPUPORESET0 reset control - RW */
    ureg32 NCPUPORESETFLAG : 1; /* [5:5] NCPUPORESET0 reset flag - RH */
    ureg32 reserved_6 : 26;     /* [31:6] Internal reserved */
} RCC_CPURSTCON_Bits;

/* Cluster reset configuration register */
typedef struct
{
    ureg32 WFI_EN : 1;      /* [0:0] Core reset reset control - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_CPUCLUSTERRSTCFG_Bits;

/* PMC reset clear register */
typedef struct
{
    ureg32 PMCRSTCLR : 1;   /* [0:0] PWRC reset clear control - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_PMCRSTCLR_Bits;

/* PWRC reset control register */
typedef struct
{
    ureg32 NRESET : 1;      /* [0:0] PWRC reset control - RW */
    ureg32 NRESET_FLAG : 1; /* [1:1] PWRC reset flag - RW */
    ureg32 reserved_2 : 30; /* [31:2] Internal reserved */
} RCC_PMCRSTCON_Bits;

/* Module reset control register 1 */
typedef struct
{
    ureg32 DMA0_RST : 1;     /* [0:0] Axi_dma0 soft reset - RW */
    ureg32 reserved_1 : 3;   /* [3:1] Internal reserved */
    ureg32 DMA1_RST : 1;     /* [4:4] Ahb_dma1 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 DMA2_RST : 1;     /* [5:5] Ahb_dma2 soft reset - RW */
    ureg32 DMA3_RST : 1;     /* [6:6] Ahb_dma3 soft reset - RW, for CHIP THA6412 and THA6206 */
    ureg32 reserved_7 : 5;   /* [11:7] Internal reserved */
    ureg32 STM_RST : 1;      /* [12:12] STM soft reset - RW, for CHIP THA6412 */
    ureg32 reserved_13 : 7;  /* [19:13] Internal reserved */
    ureg32 TSENSOR0_RST : 1; /* [20:20] Tsensor0_rst soft reset - RW */
    ureg32 TSENSOR1_RST : 1; /* [21:21] Tsensor1_rst soft reset - RW */
    ureg32 reserved_22 : 10; /* [31:22] Internal reserved */
} RCC_MODRSTCON1_Bits;

/* Module reset control register 2 */
typedef struct
{
    ureg32 GTM_RST : 1;       /* [0:0] Gtm soft reset - RW */
    ureg32 GETH_RST : 1;      /* [1:1] Geth soft reset - RW */
    ureg32 reserved_2 : 2;    /* [3:2] Internal reserved */
    ureg32 BASETIMG0_RST : 1; /* [4:4] Basetim0 & 1 soft reset - RW */
    ureg32 BASETIMG1_RST : 1; /* [5:5] Basetim2 & 3 soft reset - RW */
    ureg32 BASETIMG2_RST : 1; /* [6:6] Basetim4 & 5 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 reserved_7 : 9;    /* [15:7] Internal reserved */
    ureg32 QSPI_RST : 1;      /* [16:16] Qspi soft reset - RW */
    ureg32 reserved_17 : 3;   /* [19:17] Internal reserved */
    ureg32 I2C0_RST : 1;      /* [20:20] I2c0 soft reset - RW */
    ureg32 I2C1_RST : 1;      /* [21:21] I2c1 soft reset - RW, for CHIP THA6412 */
    ureg32 reserved_22 : 2;   /* [23:22] Internal reserved */
    ureg32 MSC0_RST : 1;      /* [24:24] Msc0 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 MSC1_RST : 1;      /* [25:25] Msc1 soft reset - RW, for CHIP THA6412 */
    ureg32 MSC2_RST : 1;      /* [26:26] Msc2 soft reset - RW, for CHIP THA6412 */
    ureg32 reserved_27 : 1;   /* [27:27] Internal reserved */
    ureg32 ECRC_RST : 1;      /* [28:28] Ecrc soft reset - RW */
    ureg32 reserved_29 : 3;   /* [31:29] Internal reserved */
} RCC_MODRSTCON2_Bits;

/* Module reset control register 3 */
typedef struct
{
    ureg32 SENT0_RST : 1;   /* [0:0] Sent0 soft reset - RW */
    ureg32 SENT1_RST : 1;   /* [1:1] Sent1 soft reset - RW */
    ureg32 SENT2_RST : 1;   /* [2:2] Sent2 soft reset - RW */
    ureg32 SENT3_RST : 1;   /* [3:3] Sent3 soft reset - RW */
    ureg32 SENT4_RST : 1;   /* [4:4] Sent4 soft reset - RW */
    ureg32 SENT5_RST : 1;   /* [5:5] Sent5 soft reset - RW */
    ureg32 SENT6_RST : 1;   /* [6:6] Sent6 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 SENT7_RST : 1;   /* [7:7] Sent7 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 SENT8_RST : 1;   /* [8:8] Sent8 soft reset - RW, for CHIP THA6206 and THA6412*/
    ureg32 SENT9_RST : 1;   /* [9:9] Sent9 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 reserved_10 : 2; /* [11:10] Internal reserved */
    ureg32 PSI5_RST : 1;    /* [12:12] PSI5 soft reset - RW, for CHIP THA6412 */
    ureg32 reserved_13 : 3; /* [15:13] Internal reserved */
    ureg32 ESPI0_RST : 1;   /* [16:16] Espi0 soft reset - RW */
    ureg32 ESPI1_RST : 1;   /* [17:17] Espi1 soft reset - RW */
    ureg32 ESPI2_RST : 1;   /* [18:18] Espi2 soft reset - RW */
    ureg32 ESPI3_RST : 1;   /* [19:19] Espi3 soft reset - RW */
    ureg32 ESPI4_RST : 1;   /* [20:20] Espi4 soft reset - RW */
    ureg32 ESPI5_RST : 1;   /* [21:21] Espi5 soft reset - RW */
    ureg32 ESPI6_RST : 1;   /* [22:22] Espi6 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 ESPI7_RST : 1;   /* [23:23] Espi7 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 ESPI8_RST : 1;   /* [24:24] Espi8 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 reserved_25 : 7; /* [31:25] Internal reserved */
} RCC_MODRSTCON3_Bits;

/* Module reset control register 4 */
typedef struct
{
    ureg32 ASI0_RST : 1;    /* [0:0] Asi0 soft reset - RW */
    ureg32 ASI1_RST : 1;    /* [1:1] Asi1 soft reset - RW */
    ureg32 ASI2_RST : 1;    /* [2:2] Asi2 soft reset - RW */
    ureg32 ASI3_RST : 1;    /* [3:3] Asi3 soft reset - RW */
    ureg32 ASI4_RST : 1;    /* [4:4] Asi4 soft reset - RW */
    ureg32 ASI5_RST : 1;    /* [5:5] Asi5 soft reset - RW */
    ureg32 ASI6_RST : 1;    /* [6:6] Asi6 soft reset - RW */
    ureg32 ASI7_RST : 1;    /* [7:7] Asi7 soft reset - RW */
    ureg32 reserved_8 : 8;  /* [15:8] Internal reserved */
    ureg32 MCAN0_RST : 1;   /* [16:16] Multican_top0 soft reset - RW */
    ureg32 reserved_17 : 2; /* [18:17] Internal reserved */
    ureg32 MCAN1_RST : 1;   /* [19:19] Multican_top1 soft reset - RW */
    ureg32 reserved_20 : 2; /* [21:20] Internal reserved */
    ureg32 MCAN2_RST : 1;   /* [22:22] Multican_top2 soft reset - RW, for CHIP THA6412 */
    ureg32 reserved_23 : 2; /* [24:23] Internal reserved */
    ureg32 MCAN3_RST : 1;   /* [25:25] Multican_top3 soft reset - RW, for CHIP THA6412 */
    ureg32 reserved_26 : 6; /* [31:26] Internal reserved */
} RCC_MODRSTCON4_Bits;

/* Module reset control register 5 */
typedef struct
{
    ureg32 DSADC0_RST : 1;  /* [0:0] Dsadc0 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 DSADC1_RST : 1;  /* [1:1] Dsadc1 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 DSADC2_RST : 1;  /* [2:2] Dsadc2 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 DSADC3_RST : 1;  /* [3:3] Dsadc3 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 DSADC4_RST : 1;  /* [4:4] Dsadc4 soft reset - RW, for CHIP THA6412 */
    ureg32 DSADC5_RST : 1;  /* [5:5] Dsadc5 soft reset - RW, for CHIP THA6412 */
    ureg32 DSADC6_RST : 1;  /* [6:6] Dsadc6 soft reset - RW, for CHIP THA6412 */
    ureg32 DSADC7_RST : 1;  /* [7:7] Dsadc7 soft reset - RW, for CHIP THA6412 */
    ureg32 DSADC8_RST : 1;  /* [8:8] Dsadc8 soft reset - RW, for CHIP THA6412 */
    ureg32 DSADC9_RST : 1;  /* [9:9] Dsadc9 soft reset - RW, for CHIP THA6412 */
    ureg32 reserved_10 : 2; /* [11:10] Internal reserved */
    ureg32 SARADC0_RST : 1; /* [12:12] Saradc0 soft reset - RW */
    ureg32 SARADC1_RST : 1; /* [13:13] Saradc1 soft reset - RW */
    ureg32 SARADC2_RST : 1; /* [14:14] Saradc2 soft reset - RW */
    ureg32 SARADC3_RST : 1; /* [15:15] Saradc3 soft reset - RW */
    ureg32 SARADC8_RST : 1; /* [16:16] Saradc8 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 SARADC9_RST : 1; /* [17:17] Saradc9 soft reset - RW, for CHIP THA6206 and THA6412 */

    ureg32 SARADC4_RST : 1;  /* [18:18] Saradc4 soft reset - RW , for CHIP THA6412*/
    ureg32 SARADC5_RST : 1;  /* [19:19] Saradc5 soft reset - RW , for CHIP THA6412*/
    ureg32 SARADC6_RST : 1;  /* [20:20] Saradc6 soft reset - RW , for CHIP THA6412*/
    ureg32 SARADC7_RST : 1;  /* [21:21] Saradc7 soft reset - RW , for CHIP THA6412*/
    ureg32 SARADC10_RST : 1; /* [22:22] Saradc10 soft reset - RW , for CHIP THA6412*/
    ureg32 SARADC11_RST : 1; /* [23:23] Saradc11 soft reset - RW , for CHIP THA6412*/
    ureg32 FC0_RST : 1;      /* [24:24] Fc0 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 FC1_RST : 1;      /* [25:25] Fc1 soft reset - RW, for CHIP THA6206 and THA6412 */
    ureg32 FC2_RST : 1;      /* [26:26] Fc2 soft reset - RW, for CHIP THA6412 */
    ureg32 FC3_RST : 1;      /* [27:27] Fc3 soft reset - RW, for CHIP THA6412 */
    ureg32 RDC0_RST : 1;     /* [28:28] Rdc0 soft reset - RW , for CHIP THA6206 and THA6412*/
    ureg32 RDC1_RST : 1;     /* [29:29] Rdc1 soft reset - RW, for CHIP THA6412 */
    ureg32 reserved_30 : 2;  /* [31:30] Internal reserved */
} RCC_MODRSTCON5_Bits;

/* Module reset control register 5 */
typedef struct
{
    ureg32 BUSPROT_RST : 1; /* [0:0] Busprot_rst soft reset - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_MODRSTCON6_Bits;

/* Module reset control register 7, for CHIP THA6412 */
typedef struct
{
    ureg32 SENT10_RST : 1;   /* [0:0] Sent10 soft reset - RW */
    ureg32 SENT11_RST : 1;   /* [1:1] Sent11 soft reset - RW */
    ureg32 SENT12_RST : 1;   /* [2:2] Sent12 soft reset - RW */
    ureg32 SENT13_RST : 1;   /* [3:3] Sent13 soft reset - RW */
    ureg32 SENT14_RST : 1;   /* [4:4] Sent14 soft reset - RW */
    ureg32 SENT15_RST : 1;   /* [5:5] Sent15 soft reset - RW */
    ureg32 SENT16_RST : 1;   /* [6:6] Sent16 soft reset - RW */
    ureg32 SENT17_RST : 1;   /* [7:7] Sent17 soft reset - RW */
    ureg32 SENT18_RST : 1;   /* [8:8] Sent18 soft reset - RW */
    ureg32 SENT19_RST : 1;   /* [9:9] Sent19 soft reset - RW */
    ureg32 SENT20_RST : 1;   /* [10:10] Sent20 soft reset - RW */
    ureg32 SENT21_RST : 1;   /* [11:11] Sent21 soft reset - RW */
    ureg32 SENT22_RST : 1;   /* [12:12] Sent22 soft reset - RW */
    ureg32 SENT23_RST : 1;   /* [13:13] Sent23 soft reset - RW */
    ureg32 SENT24_RST : 1;   /* [14:14] Sent24 soft reset - RW */
    ureg32 reserved_15 : 17; /* [31:15] Internal reserved */
} RCC_MODRSTCON7_Bits;

/* Module reset control register 8 , for CHIP THA6412 */
typedef struct
{
    ureg32 ASI8_RST : 1;     /* [0:0] ASI8 soft reset - RW */
    ureg32 ASI9_RST : 1;     /* [1:1] ASI9 soft reset - RW */
    ureg32 ASI10_RST : 1;    /* [2:2] ASI10 soft reset - RW */
    ureg32 ASI11_RST : 1;    /* [3:3] ASI11 soft reset - RW */
    ureg32 ASI12_RST : 1;    /* [4:4] ASI12 soft reset - RW */
    ureg32 ASI13_RST : 1;    /* [5:5] ASI13 soft reset - RW */
    ureg32 ASI14_RST : 1;    /* [6:6] ASI14 soft reset - RW */
    ureg32 ASI15_RST : 1;    /* [7:7] ASI15 soft reset - RW */
    ureg32 ASI16_RST : 1;    /* [8:8] ASI16 soft reset - RW */
    ureg32 ASI17_RST : 1;    /* [9:9] ASI17 soft reset - RW */
    ureg32 ASI18_RST : 1;    /* [10:10] ASI18 soft reset - RW */
    ureg32 ASI19_RST : 1;    /* [11:11] ASI19 soft reset - RW */
    ureg32 ASI20_RST : 1;    /* [12:12] ASI20 soft reset - RW */
    ureg32 ASI21_RST : 1;    /* [13:13] ASI21 soft reset - RW */
    ureg32 ASI22_RST : 1;    /* [14:14] ASI22 soft reset - RW */
    ureg32 ASI23_RST : 1;    /* [15:15] ASI23 soft reset - RW */
    ureg32 reserved_16 : 16; /* [31:16] Internal reserved */
} RCC_MODRSTCON8_Bits;

/* Wdt reset control register */
typedef struct
{
    ureg32 SAFEWDT_RST : 1; /* [0:0] Safe wdt soft reset - RW */
    ureg32 reserved_1 : 3;  /* [3:1] Internal reserved */
    ureg32 CPU0WDT_RST : 1; /* [4:4] Cpu0 wdt soft reset - RW */
    ureg32 CPU1WDT_RST : 1; /* [5:5] Cpu1 wdt soft reset - RW */
    ureg32 CPU2WDT_RST : 1; /* [6:6] Cpu2 wdt soft reset - RW, for CHIP THA6412 */
    ureg32 CPU3WDT_RST : 1; /* [7:7] Cpu3 wdt soft reset - RW, for CHIP THA6412 */
    ureg32 reserved_8 : 24; /* [31:8] Internal reserved */
} RCC_MODRSTCONWDT_Bits;

/* Wdt reset control register */
typedef struct
{
    ureg32 RSTPROT : 32; /* [31:0] Safe wdt soft reset - RW */
} RCC_WDTRSTPROT_Bits;

/* Esr_porst io filtering enables
energy register */
typedef struct
{
    ureg32 ESR0_EN : 1;     /* [0:0] Esr0 digital filter enable control - RW */
    ureg32 ESR1_EN : 1;     /* [1:1] Esr1 digital filter enable control - RW */
    ureg32 PORST_EN : 1;    /* [2:2] Porst digital filter enable control - RW */
    ureg32 JTAGRST_EN : 1;  /* [3:3] JTAGnTRST cell filter enable control - RW */
    ureg32 reserved_4 : 28; /* [31:4] Internal reserved */
} RCC_ESRPORSTIODFEN_Bits;

/* Timeout count value enable settings */
typedef struct
{
    ureg32 TIMOUTCNTEN : 1; /* [0:0] Enable/disable timeout counter count after heat reset request: - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_TIMOUTCNTEN_Bits;

/* Timeout count value settings */
typedef struct
{
    ureg32 COUNTER : 16;     /* [15:0] Timeout counter value setting - RW */
    ureg32 reserved_16 : 16; /* [31:16] Internal reserved */
} RCC_TIMOUTCNT_Bits;

/* Cpu shutdown flag register */
typedef struct
{
    ureg32 CPUSHUTDOWNFLAG : 1; /* [0:0] Cpu shutdown program completion flag - rw */
    ureg32 reserved_1 : 15;     /* [15:1] Internal reserved */
    ureg32 USRINFO : 16;        /* [31:16] User info save - rw */
} RCC_CPUSHUTDOWNFLAG_Bits;

/* Rcc interrupt mask register */
typedef struct
{
    ureg32 RCCINTMSK : 1;   /* [0:0] Warm reset intterupt control - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_RCCINTMASK_Bits;

/* Rcc interrupt enable register */
typedef struct
{
    ureg32 RCCINTEN : 1;    /* [0:0] Thermal reset interrupt generation control bit - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_RCCINTEN_Bits;

/* Rcc interrupt status register */
typedef struct
{
    ureg32 RCCINTSTAT : 1;  /* [0:0] Hot reset interrupted state bit - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_RCCINTSTAT_Bits;

/* Rcc interrupt set & reset registers */
typedef struct
{
    ureg32 CLRRCCINT : 1;    /* [0:0] Software clear hot reset interrupt - WO */
    ureg32 reserved_1 : 15;  /* [15:1] Internal reserved */
    ureg32 SETRCCINT : 1;    /* [16:16] Software set thermal reset interrupt stat, read as 0 - WO */
    ureg32 reserved_17 : 15; /* [31:17] Internal reserved */
} RCC_RCCINTSETCLR_Bits;

/* Rcc interrupt set write protection register */
typedef struct
{
    ureg32 RCCINTSETPROT_CTR : 1; /* [0:0] Register rccintsetprot software setup interrupt stat write protection - RW */
    ureg32 reserved_1 : 31;       /* [31:1] Internal reserved */
} RCC_RCCINTSETPROT_Bits;

/* Ram low power exit flag clear */
typedef struct
{
    ureg32 RAMLPEXITFLAGCLR : 1; /* [0:0] RAM low power exit flag clear - RWH */
    ureg32 reserved_1 : 31;      /* [31:1] Internal reserved */
} RCC_RAMLPEXITFLAGCLR_Bits;

/* Ram low power exit flag */
typedef struct
{
    ureg32 RAM0LPEXITFLAG : 1; /* [0:0] 0: did not exit normally before reset - RH */
    ureg32 RAM1LPEXITFLAG : 1; /* [1:1] 0: did not exit normally before reset - RH */
    ureg32 RAM2LPEXITFLAG : 1; /* [2:2] 0: did not exit normally before reset - RH */
    ureg32 RAM3LPEXITFLAG : 1; /* [3:3] 0: did not exit normally before reset - RH */
    ureg32 RAM4LPEXITFLAG : 1; /* [4:4] 0: did not exit normally before reset - RH, for CHIP THA6412 */
    ureg32 RAM5LPEXITFLAG : 1; /* [5:5] 0: did not exit normally before reset - RH, for CHIP THA6412 */
    ureg32 RAM6LPEXITFLAG : 1; /* [6:6] 0: did not exit normally before reset - RH, for CHIP THA6412 */
    ureg32 reserved_7 : 25;    /* [31:7] Internal reserved */
} RCC_RAMLPEXITFLAG_Bits;

/* Ram low power exit enable */
typedef struct
{
    ureg32 RAM0LPEXITEN : 1; /* [0:0] RAM0LPEXIT - CPU0 RAM - RW */
    ureg32 RAM1LPEXITEN : 1; /* [1:1] RAM1LPEXIT - CPU1 RAM - RW */
    ureg32 RAM2LPEXITEN : 1; /* [2:2] RAM2LPEXIT - GMU RAM - RW */
    ureg32 RAM3LPEXITEN : 1; /* [3:3] RAM3LPEXIT - GTM RAM - RW */
    ureg32 RAM4LPEXITEN : 1; /* [4:4] RAM4LPEXIT - CPU2 RAM - RW, for CHIP THA6412 */
    ureg32 RAM5LPEXITEN : 1; /* [5:5] RAM5LPEXIT - CPU3 RAM - RW, for CHIP THA6412 */
    ureg32 RAM6LPEXITEN : 1; /* [6:6] RAM6LPEXIT - GMU1 RAM - RW, for CHIP THA6412 */
    ureg32 reserved_7 : 25;  /* [31:7] Internal reserved */
} RCC_RAMLPEXITEN_Bits;

/* Reset security register warning enable register */
typedef struct
{
    ureg32 RSTSFFALMSMEN : 1; /* [0:0] Safety register alarm enable - RW */
    ureg32 reserved_1 : 31;   /* [31:1] Internal reserved */
} RCC_RSTSFFALMSMEN_Bits;

/* Reset security register alarm status register */
typedef struct
{
    ureg32 G0RSTSFF_ALMFLAG : 1; /* [0:0] Security register alarm status bit - RO */
    ureg32 G1RSTSFF_ALMFLAG : 1; /* [1:1] Security register alarm status bit - RO */
    ureg32 G2RSTSFF_ALMFLAG : 1; /* [2:2] Security register alarm status bit - RO */
    ureg32 G3RSTSFF_ALMFLAG : 1; /* [3:3] Security register alarm status bit - RO */
    ureg32 G4RSTSFF_ALMFLAG : 1; /* [4:4] Security register alarm status bit - RO */
    ureg32 G5RSTSFF_ALMFLAG : 1; /* [5:5] Security register alarm status bit - RO */
    ureg32 G6RSTSFF_ALMFLAG : 1; /* [6:6] Security register alarm status bit - RO */
    ureg32 reserved_8 : 25;      /* [31:7] Internal reserved */
} RCC_RSTSFFALMSTAT_Bits;

/* Reset security register alarm status clear register */
typedef struct
{
    ureg32 ALMSTACLR : 1;   /* [0:0] Security register alarm status bit for this class - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_RSTSFFALMSTATCLR_Bits;

/* Reset security register alarm status injection register */
typedef struct
{
    ureg32 RSTSFFALMFAULTIN : 1; /* [0:0] Safety register fail injection - RW */
    ureg32 reserved_1 : 31;      /* [31:1] Internal reserved */
} RCC_RSTSFFALMFAULTIN_Bits;

/* Reset domain trig bus error mask register */
typedef struct
{
    ureg32 BEM : 1;         /* [0:0]  Reset domain trig bus error mask - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_RSTBEMASK_Bits;

/* Reset trigger E/SE alarm state register */
typedef struct
{
    ureg32 RSTEALMSTAT : 1;  /* [0:0]  E alarm stat - RW */
    ureg32 RSTSEALMSTAT : 1; /* [1:1]  SE alarm stat - RW */
    ureg32 reserved_2 : 30;  /* [31:2] Internal reserved */
} RCC_RSTESEALMSTAT_Bits;

/* Reset trigger E/SE alarm state register */
typedef struct
{
    ureg32 RSTEALMCLR : 1;  /* [0:0]  E alarm stat clear - RW */
    ureg32 RSTSEALMCLR : 1; /* [1:1]  SE alarm stat clear - RW */
    ureg32 reserved_2 : 30; /* [31:2] Internal reserved */
} RCC_RSTESEALMCLR_Bits;

/**********************************************************************************************************************
 *                                        RCC Clock STB Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Lsi 70k internal oscillator control register 1 */
typedef struct
{
    ureg32 LSI_READY : 1;   /* [0:0] Lsi clock stability indicator - RH */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_LSICON1_Bits;

/* Lsi 70k internal oscillator control register 2 */
typedef struct
{
    ureg32 STBCNT : 16;      /* [15:0] Lsi osc70k clock stabilization time configuration - RW */
    ureg32 reserved_16 : 16; /* [31:16] Internal reserved */
} RCC_LSICON2_Bits;

/* System clock selection for backup domain */
typedef struct
{
    ureg32 CLK_SEL : 1;     /* [0:0] Standby power domain system clock selection - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_CLKSTBSEL_Bits;

/* Backup domain module clock enable */
typedef struct
{
    ureg32 IWDG_EN : 1;     /* [0:0] Iwdg clock enable control - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_CLKSTBEN_Bits;

/* Safety register alarm enable */
typedef struct
{
    ureg32 CLKSTBSFFALMSMEN : 1; /* [0:0] Safety register alarm enable - RW */
    ureg32 reserved_1 : 31;      /* [31:1] Internal reserved */
} RCC_CLKSTBSFFALMSMEN_Bits;

/* Clock security register alarm statistics register */
typedef struct
{
    ureg32 CLKSTBSFF0ALMSTAT : 1; /* [0:0] This security register alarm statistics bit - RO */
    ureg32 CLKSTBSFF1ALMSTAT : 1; /* [1:1] This security register alarm statistics bit - RO */
    ureg32 CLKSTBSFF2ALMSTAT : 1; /* [2:2] This security register alarm statistics bit - RO */
    ureg32 CLKSTBSFF3ALMSTAT : 1; /* [3:3] This security register alarm statistics bit - RO */
    ureg32 CLKSTBSFF4ALMSTAT : 1; /* [4:4] This security register alarm statistics bit - RO */
    ureg32 CLKSTBSFF5ALMSTAT : 1; /* [5:5] This security register alarm statistics bit - RO */
    ureg32 CLKSTBSFF6ALMSTAT : 1; /* [6:6] This security register alarm statistics bit - RO */
    ureg32 CLKSTBSFF7ALMSTAT : 1; /* [7:7] This security register alarm statistics bit - RO */
    ureg32 CLKSTBSFF8ALMSTAT : 1; /* [8:8] This security register alarm statistics bit - RO */
    ureg32 CLKSTBSFF9ALMSTAT : 1; /* [9:9] This security register alarm statistics bit - RO, for CHIP THA6412 and THA6104 */
    ureg32 reserved_10 : 22;      /* [31:10] Internal reserved */
} RCC_CLKSTBSFFALMSTAT_Bits;

/* Clock security register alarm status clear register */
typedef struct
{
    ureg32 CLKSTBSFFALMSTSCLR : 1; /* [0:0] Security register alarm status bit  - RW */
    ureg32 reserved_1 : 31;        /* [31:1] Internal reserved */
} RCC_CLKSTBSFFALMSTATCLR_Bits;

/* Clock safety register alarm status injection register */
typedef struct
{
    ureg32 CLKSTBSFFALM1FAULTIN : 1; /* [0:0] Safety register fault injection, - RW */
    ureg32 reserved_1 : 31;          /* [31:1] Internal reserved */
} RCC_CLKSTBSFFALMFAULTIN_Bits;

/* CLKSTBBEMASK register */
typedef struct
{
    ureg32 CLKSTBBEMASK : 1; /* [0:0] Clock bus error mask - RW */
    ureg32 reserved_1 : 31;  /* [31:1] Internal reserved */
} RCC_CLKSTBBEMASK_Bits;

/* Access E/SE register alarm register */
typedef struct
{
    ureg32 CLKSTBEALMSTAT : 1;  /* [0:0] Access E register alarm - RO */
    ureg32 CLKSTBSEALMSTAT : 1; /* [1:1] Access SE register alarm - RO */
    ureg32 reserved_2 : 30;     /* [31:2] Internal reserved */
} RCC_CLKSTBESEALMSTAT_Bits;

/* Access E/SE register alarm clear register */
typedef struct
{
    ureg32 CLKSTBEALMSTATCLR : 1;  /* [0:0] Access E register alarm clear - RO */
    ureg32 CLKSTBSEALMSTATCLR : 1; /* [1:1] Access SE register alarm clear - RO */
    ureg32 reserved_2 : 30;        /* [31:2] Internal reserved */
} RCC_CLKSTBESEALMSTATCLR_Bits;

/**********************************************************************************************************************
 *                                        RCC Reset STB Register Bit-Fields Definitions
 *********************************************************************************************************************/

/* Reset control register 1 for backup domain (module reset) */
typedef struct
{
    ureg32 IWDG_RST : 1;    /* [0:0] Iwdg module soft reset - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_STBMODRST_Bits;

/* Reset control register 2 for backup domain (system reset) */
typedef struct
{
    ureg32 SW_RST : 1;      /* [0:0] Software system reset request for backup domain - W */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_STBSWRST_Bits;

/* Rstb_stb_io reset enable register */
typedef struct
{
    ureg32 RST_EN : 1;      /* [0:0] Rstb_stb io reset enable control - RW */
    ureg32 reserved_1 : 31; /* [31:1] Internal reserved */
} RCC_IORSTEN_Bits;

/* Reset security register warning enable register */
typedef struct
{
    ureg32 RSTSTBSFFALMSMEN : 1; /* [0:0] Safety register alarm enable - RW */
    ureg32 reserved_1 : 31;      /* [31:1] Internal reserved */
} RCC_RSTSTBSFFALMSMEN_Bits;

typedef struct
{
    ureg32 RSTSTBG0RSTSFF_ALMFLAG : 1; /* [0:0] Security register alarm status bit - RO */
    ureg32 RSTSTBG1RSTSFF_ALMFLAG : 1; /* [1:1] Security register alarm status bit - RO */
    ureg32 RSTSTBG2RSTSFF_ALMFLAG : 1; /* [2:2] Security register alarm status bit - RO */
    ureg32 RSTSTBG3RSTSFF_ALMFLAG : 1; /* [3:3] Security register alarm status bit - RO */
    ureg32 RSTSTBG4RSTSFF_ALMFLAG : 1; /* [4:4] Security register alarm status bit - RO */
    ureg32 RSTSTBG5RSTSFF_ALMFLAG : 1; /* [5:5] Security register alarm status bit - RO */
    ureg32 RSTSTBG6RSTSFF_ALMFLAG : 1; /* [6:6] Security register alarm status bit - RO */
    ureg32 reserved_8 : 25;            /* [31:8] Internal reserved */
} RCC_RSTSTBSFFALMSTAT_Bits;

/* Reset security register alarm status clear register */
typedef struct
{
    ureg32 RSTSTBALMSTACLR : 1; /* [0:0] Security register alarm status bit for this class - RW */
    ureg32 reserved_1 : 31;     /* [31:1] Internal reserved */
} RCC_RSTSTBSFFALMSTATCLR_Bits;

/* Reset security register alarm status injection register */
typedef struct
{
    ureg32 RSTSTBSFFALMFAULTIN : 1; /* [0:0] Safety register fail injection - RW */
    ureg32 reserved_1 : 31;         /* [31:1] Internal reserved */
} RCC_RSTSTBSFFALMFAULTIN_Bits;

typedef struct
{
    ureg32 RSTSTBBEMASK : 1; /* [0] CLK register bus error mask control */
    ureg32 reserved_1 : 31;  /* [31:1] Internal reserved */
} RCC_RSTSTBBEMASK_Bits;

typedef struct
{
    ureg32 RSTSTBEALMSTAT : 1;  /* E ALM status */
    ureg32 RSTSTBSEAIMSTAT : 1; /* SE ALM status */
    ureg32 reserved_1 : 30;     /* [31:2] Internal reserved */
} RCC_RSTSTBESEALMSTAT_Bits;

typedef struct
{
    ureg32 RSTSTBEALMSTATCLR : 1;  /* clear E ALM status */
    ureg32 RSTSTBSEALMSTATCLR : 1; /*  clear SE ALM status */
    ureg32 reserved_1 : 30;        /* [31:2] Internal reserved */
} RCC_RSTSTBESEALMSTATCLR_Bits;

/**********************************************************************************************************************
 *                                           RCC Register Definitions
 *********************************************************************************************************************/

/* HSECON1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_HSECON1_Bits B; /* Bit-Field access */
} RCC_HSECON1;

/* HSECON2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_HSECON2_Bits B; /* Bit-Field access */
} RCC_HSECON2;

/* PLLREFSEL register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_PLLREFSEL_Bits B; /* Bit-Field access */
} RCC_PLLREFSEL;

/* SYSPLLCON1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSPLLCON1_Bits B; /* Bit-Field access */
} RCC_SYSPLLCON1;

/* SYSPLLCON2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSPLLCON2_Bits B; /* Bit-Field access */
} RCC_SYSPLLCON2;

/* SYSPLLCON3 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSPLLCON3_Bits B; /* Bit-Field access */
} RCC_SYSPLLCON3;

/* SYSPLLCON4 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSPLLCON4_Bits B; /* Bit-Field access */
} RCC_SYSPLLCON4;

/* SSMODCON1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_SSMODCON1_Bits B; /* Bit-Field access */
} RCC_SSMODCON1;

/* SSMODCON2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_SSMODCON2_Bits B; /* Bit-Field access */
} RCC_SSMODCON2;

/* SSMODCON3 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_SSMODCON3_Bits B; /* Bit-Field access */
} RCC_SSMODCON3;

/* PERPLLCON1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_PERPLLCON1_Bits B; /* Bit-Field access */
} RCC_PERPLLCON1;

/* PERPLLCON2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_PERPLLCON2_Bits B; /* Bit-Field access */
} RCC_PERPLLCON2;

/* PERPLLCON3 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_PERPLLCON3_Bits B; /* Bit-Field access */
} RCC_PERPLLCON3;

/* PERPLLCON4 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_PERPLLCON4_Bits B; /* Bit-Field access */
} RCC_PERPLLCON4;

/* SYSCLKCON1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSCLKCON1_Bits B; /* Bit-Field access */
} RCC_SYSCLKCON1;

/* SYSCLKCON2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSCLKCON2_Bits B; /* Bit-Field access */
} RCC_SYSCLKCON2;

/* RCC_SYSCLKCON3 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSCLKCON3_Bits B; /* Bit-Field access */
} RCC_SYSCLKCON3;

/* SYSCLKCON4 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSCLKCON4_Bits B; /* Bit-Field access */
} RCC_SYSCLKCON4;

/* SYSCLKCON5 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSCLKCON5_Bits B; /* Bit-Field access */
} RCC_SYSCLKCON5;

/* SYSCLKCON6 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSCLKCON6_Bits B; /* Bit-Field access */
} RCC_SYSCLKCON6;

/* SYSCLKCON7 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSCLKCON7_Bits B; /* Bit-Field access */
} RCC_SYSCLKCON7;

/* SYSCLKCON8 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SYSCLKCON8_Bits B; /* Bit-Field access */
} RCC_SYSCLKCON8;

/* CLKCON1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_CLKCON1_Bits B; /* Bit-Field access */
} RCC_CLKCON1;

/* CLKCON2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_CLKCON2_Bits B; /* Bit-Field access */
} RCC_CLKCON2;

/* CLKCON3 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_CLKCON3_Bits B; /* Bit-Field access */
} RCC_CLKCON3;

/* CLKCON4 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_CLKCON4_Bits B; /* Bit-Field access */
} RCC_CLKCON4;

/* CLKCON5 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_CLKCON5_Bits B; /* Bit-Field access */
} RCC_CLKCON5;

/* CLKCON6 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_CLKCON6_Bits B; /* Bit-Field access */
} RCC_CLKCON6;

/* CLKCON7 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_CLKCON7_Bits B; /* Bit-Field access */
} RCC_CLKCON7;

/* CLKCON8 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_CLKCON8_Bits B; /* Bit-Field access */
} RCC_CLKCON8;

/* CLKCON9 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_CLKCON9_Bits B; /* Bit-Field access */
} RCC_CLKCON9;

/* CLKCON10 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    RCC_CLKCON10_Bits B; /* Bit-Field access */
} RCC_CLKCON10;

/* CLKCON11 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    RCC_CLKCON11_Bits B; /* Bit-Field access */
} RCC_CLKCON11;

/* CLKTIM1CON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_CLKTIM1CON_Bits B; /* Bit-Field access */
} RCC_CLKTIM1CON;

/* CLKTIM2CON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_CLKTIM2CON_Bits B; /* Bit-Field access */
} RCC_CLKTIM2CON;

/* CLKTIM3CON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_CLKTIM3CON_Bits B; /* Bit-Field access */
} RCC_CLKTIM3CON;

/* CLKTIM4CON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_CLKTIM4CON_Bits B; /* Bit-Field access */
} RCC_CLKTIM4CON;

/* CLKTIM5CON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_CLKTIM5CON_Bits B; /* Bit-Field access */
} RCC_CLKTIM5CON;

/* CLKTIM6CON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_CLKTIM6CON_Bits B; /* Bit-Field access */
} RCC_CLKTIM6CON;

/* CLKEN1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    RCC_CLKEN1_Bits B; /* Bit-Field access */
} RCC_CLKEN1;

/* CLKEN2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    RCC_CLKEN2_Bits B; /* Bit-Field access */
} RCC_CLKEN2;

/* CLKEN3 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    RCC_CLKEN3_Bits B; /* Bit-Field access */
} RCC_CLKEN3;

/* CLKEN4 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    RCC_CLKEN4_Bits B; /* Bit-Field access */
} RCC_CLKEN4;

/* CLKEN5 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    RCC_CLKEN5_Bits B; /* Bit-Field access */
} RCC_CLKEN5;

/* CLKEN6 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    RCC_CLKEN6_Bits B; /* Bit-Field access */
} RCC_CLKEN6;

/* CLKEN7 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    RCC_CLKEN7_Bits B; /* Bit-Field access */
} RCC_CLKEN7;

/* CLKEN8 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    RCC_CLKEN8_Bits B; /* Bit-Field access */
} RCC_CLKEN8;

/* CLKEN9 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    RCC_CLKEN9_Bits B; /* Bit-Field access */
} RCC_CLKEN9;

/* CPUCLUSTER1CLKEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_CPUCLUSTER1CLKEN_Bits B; /* Bit-Field access */
} RCC_CPUCLUSTER1CLKEN;

/* Process clock enable register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_CLKENPROC_Bits B; /* Bit-Field access */
} RCC_CLKENPROC;

/* RCC_CLKENWDT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    RCC_CLKENWDT_Bits B; /* Bit-Field access */
} RCC_CLKENWDT;

/* RCC_CLKENWDTPROT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_CLKENWDTPROT_Bits B; /* Bit-Field access */
} RCC_CLKENWDTPROT;

/* CLKENDIV register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    RCC_CLKENDIV_Bits B; /* Bit-Field access */
} RCC_CLKENDIV;

/* EXTCLKCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_EXTCLKCON_Bits B; /* Bit-Field access */
} RCC_EXTCLKCON;

/* EXTCLKDIV register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_EXTCLKDIV_Bits B; /* Bit-Field access */
} RCC_EXTCLKDIV;

/* EXTCLKDIVCFG register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_EXTCLKDIVCFG_Bits B; /* Bit-Field access */
} RCC_EXTCLKDIVCFG;

/* SYSCLKSWSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;
    RCC_SYSCLKSWSTAT_Bits B;
} RCC_SYSCLKSWSTAT;

/* PERCLKSWSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_PERCLKSWSTAT_Bits B; /* Bit-Field access */
} RCC_PERCLKSWSTAT;

/* PLLLOCKCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_PLLLOCKCON_Bits B; /* Bit-Field access */
} RCC_PLLLOCKCON;

/* SYSPLLCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_SYSPLLCLKMON_Bits B; /* Bit-Field access */
} RCC_SYSPLLCLKMON;

/* PERPLLMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_PERPLLMON_Bits B; /* Bit-Field access */
} RCC_PERPLLMON;

/* HSECLKCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_HSECLKCON_Bits B; /* Bit-Field access */
} RCC_HSECLKCON;

/* HSICLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_HSICLKMON_Bits B; /* Bit-Field access */
} RCC_HSICLKMON;

/* LSICLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_LSICLKMON_Bits B; /* Bit-Field access */
} RCC_LSICLKMON;

/* CPUCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_CPUCLKMON_Bits B; /* Bit-Field access */
} RCC_CPUCLKMON;

/* SYSCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_SYSCLKMON_Bits B; /* Bit-Field access */
} RCC_SYSCLKMON;

/* AXICLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_AXICLKMON_Bits B; /* Bit-Field access */
} RCC_AXICLKMON;

/* AHBCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_AHBCLKMON_Bits B; /* Bit-Field access */
} RCC_AHBCLKMON;

/* APBSTBCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_APBSTBCLKMON_Bits B; /* Bit-Field access */
} RCC_APBSTBCLKMON;

/* WDTCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_WDTCLKMON_Bits B; /* Bit-Field access */
} RCC_WDTCLKMON;

/* IPCNTCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    RCC_IPCNTCLKMON_Bits B; /* Bit-Field access */
} RCC_IPCNTCLKMON;

/* IWDGCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_IWDGCLKMON_Bits B; /* Bit-Field access */
} RCC_IWDGCLKMON;

/* GTMCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_GTMCLKMON_Bits B; /* Bit-Field access */
} RCC_GTMCLKMON;

/* QSPICLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_QSPICLKMON_Bits B; /* Bit-Field access */
} RCC_QSPICLKMON;

/* ESPICLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_ESPICLKMON_Bits B; /* Bit-Field access */
} RCC_ESPICLKMON;

/* CANCCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_CANCCLKMON_Bits B; /* Bit-Field access */
} RCC_CANCCLKMON;

/* SARADCCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_SARADCCLKMON_Bits B; /* Bit-Field access */
} RCC_SARADCCLKMON;

/* RDCCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_RDCCLKMON_Bits B; /* Bit-Field access */
} RCC_RDCCLKMON;

/* DSADCCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    RCC_DSADCCLKMON_Bits B; /* Bit-Field access */
} RCC_DSADCCLKMON;

/* MSCCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_MSCCLKMON_Bits B; /* Bit-Field access */
} RCC_MSCCLKMON;

/* FCCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    RCC_FCCLKMON_Bits B; /* Bit-Field access */
} RCC_FCCLKMON;

/* CPUCLKCLUSTER1MON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                     /* Unsigned access */
    RCC_CPUCLKCLUSTER1MON_Bits B; /* Bit-Field access */
} RCC_CPUCLKCLUSTER1MON;

/* RCC_AXINVMCFGCLKMON regiter */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                   /* Unsigned access */
    RCC_AXINVMCFGCLKMON_Bits B; /* Bit-Field access */
} RCC_AXINVMCFGCLKMON;

/* PROCCLKMON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_PROCCLKMON_Bits B; /* Bit-Field access */
} RCC_PROCCLKMON;

/* PROCCLKFREQ register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    RCC_PROCCLKFREQ_Bits B; /* Bit-Field access */
} RCC_PROCCLKFREQ;

/* CLKMONSTAT1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                   /* Unsigned access */
    RCC_CLKFREQMONSTAT1_Bits B; /* Bit-Field access */
} RCC_CLKFREQMONSTAT1;

/* CLKSTAT1CLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                      /* Unsigned access */
    RCC_CLKFREQMONSTAT1CLR_Bits B; /* Bit-Field access */
} RCC_CLKFREQMONSTAT1CLR;

/* CLKMONSTAT2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                   /* Unsigned access */
    RCC_CLKFREQMONSTAT2_Bits B; /* Bit-Field access */
} RCC_CLKFREQMONSTAT2;

/* CLKSTAT2CLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                      /* Unsigned access */
    RCC_CLKFREQMONSTAT2CLR_Bits B; /* Bit-Field access */
} RCC_CLKFREQMONSTAT2CLR;

/* CLKALIVESTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_CLKALIVESTAT_Bits B; /* Bit-Field access */
} RCC_CLKALIVEMONSTAT;

/* CLKALIVESTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                   /* Unsigned access */
    RCC_CLKALIVESTATCLR_Bits B; /* Bit-Field access */
} RCC_CLKALIVEMONSTATCLR;

/* CLKSTBSFFALMSMEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    RCC_CLKSFFALMSMEN_Bits B; /* Bit-Field access */
} RCC_CLKSFFALMSMEN;

/* CLKSFFALMSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    RCC_CLKSFFALMSTAT_Bits B; /* Bit-Field access */
} RCC_CLKSFFALMSTAT;

/* CLKSFFALMSTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_CLKSFFALMSTATCLR_Bits B; /* Bit-Field access */
} RCC_CLKSFFALMSTATCLR;

/* CLKSFFALMFAULTIN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_CLKSFFALMFAULTIN_Bits B; /* Bit-Field access */
} RCC_CLKSFFALMFAULTIN;

/* CLKSTBBEMASK register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_CLKSTBBEMASK_Bits B; /* Bit-Field access */
} RCC_CLKSTBBEMASK;

/* CLKSTBESEALMSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_CLKSTBESEALMSTAT_Bits B; /* Bit-Field access */
} RCC_CLKSTBESEALMSTAT;

/* CLKSTBESEALMSTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                       /* Unsigned access */
    RCC_CLKSTBESEALMSTATCLR_Bits B; /* Bit-Field access */
} RCC_CLKSTBESEALMSTATCLR;

/* CLKBEMASK register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_CLKBEMASK_Bits B; /* Bit-Field access */
} RCC_CLKBEMASK;

/* CLKESEALMSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    RCC_CLKESEALMSTAT_Bits B; /* Bit-Field access */
} RCC_CLKESEALMSTAT;

/* CLKESEALMSTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_CLKESEALMSTATCLR_Bits B; /* Bit-Field access */
} RCC_CLKESEALMSTATCLR;

/**********************************************************************************************************************
 *                                        RCC RST Register Definitions
 *********************************************************************************************************************/

/* RSTSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_RSTSTAT_Bits B; /* Bit-Field access */
} RCC_RSTSTAT;

/* RSTSTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_RSTSTATCLR_Bits B; /* Bit-Field access */
} RCC_RSTSTATCLR;

/* SACRSTFLAG register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_SACRSTFLAG_Bits B; /* Bit-Field access */
} RCC_SACRSTFLAG;

/* SACRSTCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_SACRSTCLR_Bits B; /* Bit-Field access */
} RCC_SACRSTCLR;

/* SWRSTCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    RCC_SWRSTCON_Bits B; /* Bit-Field access */
} RCC_SWRSTCON;

/* RSTCON1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_RSTCON1_Bits B; /* Bit-Field access */
} RCC_RSTCON1;

/* RSTCON2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_RSTCON2_Bits B; /* Bit-Field access */
} RCC_RSTCON2;

/* RSTCON3 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_RSTCON3_Bits B; /* Bit-Field access */
} RCC_RSTCON3;

/* DBGRSTCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_DBGRSTCON_Bits B; /* Bit-Field access */
} RCC_DBGRSTCON;

/* WDTRSTCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_WDTRSTCON_Bits B; /* Bit-Field access */
} RCC_WDTRSTCON;

/* STMRSTCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_STMRSTCON_Bits B; /* Bit-Field access */
} RCC_STMRSTCON;

/* CPUCLUSTRSTCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                  /* Unsigned access */
    RCC_CPUCLUSTRSTCLR_Bits B; /* Bit-Field access */
} RCC_CPUCLUSTRSTCLR;

/* CPUCLUSTERRSTCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_CPUCLUSTERRSTCON_Bits B; /* Bit-Field access */
} RCC_CPUCLUSTERRSTCON;

/* CPUCLUSTERRSTCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                     /* Unsigned access */
    RCC_CPUCLUSTER1RSTCON_Bits B; /* Bit-Field access */
} RCC_CPUCLUSTER1RSTCON;

/* CPU0RSTCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_CPURSTCLR_Bits B; /* Bit-Field access */
} RCC_CPURSTCLR;

/* CPU0RSTCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_CPURSTCON_Bits B; /* Bit-Field access */
} RCC_CPURSTCON;

/* CPUCLUSTERRSTCFG register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_CPUCLUSTERRSTCFG_Bits B; /* Bit-Field access */
} RCC_CPUCLUSTERRSTCFG;

/* PMCRSTCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_PMCRSTCLR_Bits B; /* Bit-Field access */
} RCC_PMCRSTCLR;

/* PMCRSTCON register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_PMCRSTCON_Bits B; /* Bit-Field access */
} RCC_PMCRSTCON;

/* MODRSTCON1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_MODRSTCON1_Bits B; /* Bit-Field access */
} RCC_MODRSTCON1;

/* MODRSTCON2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_MODRSTCON2_Bits B; /* Bit-Field access */
} RCC_MODRSTCON2;

/* MODRSTCON3 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_MODRSTCON3_Bits B; /* Bit-Field access */
} RCC_MODRSTCON3;

/* MODRSTCON4 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_MODRSTCON4_Bits B; /* Bit-Field access */
} RCC_MODRSTCON4;

/* MODRSTCON5 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_MODRSTCON5_Bits B; /* Bit-Field access */
} RCC_MODRSTCON5;

/* MODRSTCON6 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_MODRSTCON6_Bits B; /* Bit-Field access */
} RCC_MODRSTCON6;

/* MODRSTCON5 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_MODRSTCON7_Bits B; /* Bit-Field access */
} RCC_MODRSTCON7;

/* MODRSTCON5 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_MODRSTCON8_Bits B; /* Bit-Field access */
} RCC_MODRSTCON8;

/* MODRSTCONWDT_Bits register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_MODRSTCONWDT_Bits B; /* Bit-Field access */
} RCC_MODRSTCONWDT;

/* WDTRSTPROT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_WDTRSTPROT_Bits B; /* Bit-Field access */
} RCC_WDTRSTPROT;

/* ESRPORSTIODFEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                  /* Unsigned access */
    RCC_ESRPORSTIODFEN_Bits B; /* Bit-Field access */
} RCC_ESRPORSTIODFEN;

/* TIMOUTCNTEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    RCC_TIMOUTCNTEN_Bits B; /* Bit-Field access */
} RCC_TIMOUTCNTEN;

/* TIMOUTCNT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_TIMOUTCNT_Bits B; /* Bit-Field access */
} RCC_TIMOUTCNT;

/* CPUSHUTDOWNFLAG register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                   /* Unsigned access */
    RCC_CPUSHUTDOWNFLAG_Bits B; /* Bit-Field access */
} RCC_CPUSHUTDOWNFLAG;

/* RCCINTMASK register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_RCCINTMASK_Bits B; /* Bit-Field access */
} RCC_RCCINTMASK;

/* RCCINTEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    RCC_RCCINTEN_Bits B; /* Bit-Field access */
} RCC_RCCINTEN;

/* RCCINTSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    RCC_RCCINTSTAT_Bits B; /* Bit-Field access */
} RCC_RCCINTSTAT;

/* RCCINTSETCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    RCC_RCCINTSETCLR_Bits B; /* Bit-Field access */
} RCC_RCCINTSETCLR;

/* RCCINTSETPROT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    RCC_RCCINTSETPROT_Bits B; /* Bit-Field access */
} RCC_RCCINTSETPROT;

/* RAMLPEXITFLAGCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_RAMLPEXITFLAGCLR_Bits B; /* Bit-Field access */
} RCC_RAMLPEXITFLAGCLR;

/* RAMLPEXITFLAG register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    RCC_RAMLPEXITFLAG_Bits B; /* Bit-Field access */
} RCC_RAMLPEXITFLAG;

/* RAMLPEXITEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    RCC_RAMLPEXITEN_Bits B; /* Bit-Field access */
} RCC_RAMLPEXITEN;

/* RSTSFFALMSMEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    RCC_RSTSFFALMSMEN_Bits B; /* Bit-Field access */
} RCC_RSTSFFALMSMEN;

/* RSTSFFALMSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    RCC_RSTSFFALMSTAT_Bits B; /* Bit-Field access */
} RCC_RSTSFFALMSTAT;

/* RSTSFFALMSTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_RSTSFFALMSTATCLR_Bits B; /* Bit-Field access */
} RCC_RSTSFFALMSTATCLR;

/* RSTSFFALMFAULTIN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_RSTSFFALMFAULTIN_Bits B; /* Bit-Field access */
} RCC_RSTSFFALMFAULTIN;

/* RSTSTBBEMASK register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_RSTBEMASK_Bits B; /* Bit-Field access */
} RCC_RSTBEMASK;

/* RSTSTBESEALMSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    RCC_RSTESEALMSTAT_Bits B; /* Bit-Field access */
} RCC_RSTESEALMSTAT;

/* RSTSTBESEALMSTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U; /* Unsigned access */
    RCC_RSTESEALMCLR_Bits B;
} RCC_RSTESEALMSTATCLR;

/**********************************************************************************************************************
 *                                           RCC Clock STB Register Definitions
 *********************************************************************************************************************/
/* LSICON1 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_LSICON1_Bits B; /* Bit-Field access */
} RCC_LSICON1;

/* LSICON2 register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_LSICON2_Bits B; /* Bit-Field access */
} RCC_LSICON2;

/* CLKSTBSEL register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_CLKSTBSEL_Bits B; /* Bit-Field access */
} RCC_CLKSTBSEL;

/* CLKSTBEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    RCC_CLKSTBEN_Bits B; /* Bit-Field access */
} RCC_CLKSTBEN;

/* CLKSTBSFFALMSMEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_CLKSTBSFFALMSMEN_Bits B; /* Bit-Field access */
} RCC_CLKSTBSFFALMSMEN;

/* CLKSTBSFFALMSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                    /* Unsigned access */
    RCC_CLKSTBSFFALMSTAT_Bits B; /* Bit-Field access */
} RCC_CLKSTBSFFALMSTAT;

/* CLKSTBSFFALMSTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                       /* Unsigned access */
    RCC_CLKSTBSFFALMSTATCLR_Bits B; /* Bit-Field access */
} RCC_CLKSTBSFFALMSTATCLR;

/* CLKSTBSFFALMFAULTIN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;                       /* Unsigned access */
    RCC_CLKSTBSFFALMFAULTIN_Bits B; /* Bit-Field access */
} RCC_CLKSTBSFFALMFAULTIN;

/**********************************************************************************************************************
 *                                           RCC Reset STB Register Definitions
 *********************************************************************************************************************/

/* STBMODRST register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    RCC_STBMODRST_Bits B; /* Bit-Field access */
} RCC_STBMODRST;

/* STBSWRST register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    RCC_STBSWRST_Bits B; /* Bit-Field access */
} RCC_STBSWRST;

/* IORSTEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    RCC_IORSTEN_Bits B; /* Bit-Field access */
} RCC_IORSTEN;

/* STB RSTSFFALMSMEN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;
    RCC_RSTSTBSFFALMSMEN_Bits B;
} RCC_RSTSTBSFFALMSMEN;

/* STB RSTSFFALMSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;
    RCC_RSTSTBSFFALMSTAT_Bits B;
} RCC_RSTSTBSFFALMSTAT;

/* STB RSTSFFALMSTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;
    RCC_RSTSTBSFFALMSTATCLR_Bits B;
} RCC_RSTSTBSFFALMSTATCLR;

/* STB RSTSFFALMFAULTIN register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;
    RCC_RSTSTBSFFALMFAULTIN_Bits B;
} RCC_RSTSTBSFFALMFAULTIN;

/* STB RSTSTBBEMASK register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;
    RCC_RSTSTBBEMASK_Bits B;
} RCC_RSTSTBBEMASK;

/* STB RSTSTBESEALMSTAT register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;
    RCC_RSTSTBESEALMSTAT_Bits B;
} RCC_RSTSTBESEALMSTAT;

/* STB RSTSTBESEALMSTATCLR register */
typedef union
/* #Violation: rcc_register_h_REF_1 */
{
    ureg32 U;
    RCC_RSTSTBESEALMSTATCLR_Bits B;
} RCC_RSTSTBESEALMSTATCLR;

/**********************************************************************************************************************
 *                                         RCC Register Configuration Structure
 *********************************************************************************************************************/
typedef volatile struct
{
    /* General SFR */
    RCC_HSECON1 HSECON1;                     /* 0x0010 - Hse control register 1 */
    RCC_HSECON2 HSECON2;                     /* 0x0014 - Hse control register 2 */
    ureg32 RESERVED_0018[18];                /* 0x0018 - Internal reserved */
    RCC_PLLREFSEL PLLREFSEL;                 /* 0x0060 - Pll reference clock selection register */
    RCC_SYSPLLCON1 SYSPLLCON1;               /* 0x0064 - System pll control register 1 */
    RCC_SYSPLLCON2 SYSPLLCON2;               /* 0x0068 - System pll control register 2 */
    RCC_SYSPLLCON3 SYSPLLCON3;               /* 0x006C - System pll control register 3 */
    RCC_SYSPLLCON4 SYSPLLCON4;               /* 0x0070 - System pll control register 4 */
    RCC_SSMODCON1 SSMODCON1;                 /* 0x0074 - Spread-spectrum bridge control register 1 */
    RCC_SSMODCON2 SSMODCON2;                 /* 0x0078 - Spread-spectrum bridge control register 2 */
    RCC_SSMODCON3 SSMODCON3;                 /* 0x007C - Spread-spectrum bridge control register 3 */
    RCC_PERPLLCON1 PERPLLCON1;               /* 0x0080 - Peripheral pll control register 1 */
    RCC_PERPLLCON2 PERPLLCON2;               /* 0x0084 - Peripheral pll control register 2 */
    RCC_PERPLLCON3 PERPLLCON3;               /* 0x0088 - Peripheral pll control register 3 */
    RCC_PERPLLCON4 PERPLLCON4;               /* 0x008C - Peripheral pll control register 4, for CHIP THA6412 and THA6104 */
    RCC_SSMODCON1 PERPLLSSMODCON1;           /* 0x0090 - Spread-spectrum bridge control register 1, for CHIP THA6412 and THA6104 */
    RCC_SSMODCON2 PERPLLSSMODCON2;           /* 0x0094 - Spread-spectrum bridge control register 2, for CHIP THA6412 and THA6104 */
    RCC_SSMODCON3 PERPLLSSMODCON3;           /* 0x0098 - Spread-spectrum bridge control register 3, for CHIP THA6412 and THA6104 */
    ureg32 RESERVED_009C[25];                /* 0x009C - Internal reserved */
    RCC_SYSCLKCON1 SYSCLKCON1;               /* 0x0100 - System clock control register 1 */
    RCC_SYSCLKCON2 SYSCLKCON2;               /* 0x0104 - System clock control register 2 */
    RCC_SYSCLKCON3 SYSCLKCON3;               /* 0x0108 - System clock control register 3 */
    RCC_SYSCLKCON4 SYSCLKCON4;               /* 0x010C - System clock control register 4 */
    RCC_SYSCLKCON5 SYSCLKCON5;               /* 0x0110 - System clock control register 5 */
    RCC_SYSCLKCON6 SYSCLKCON6;               /* 0x0114 - System clock control register 6 */
    RCC_SYSCLKCON7 SYSCLKCON7;               /* 0x0118 - System clock control register 7 */
    RCC_SYSCLKCON8 SYSCLKCON8;               /* 0x011C - System clock control register 8 */
    ureg32 RESERVED_0120[32];                /* 0x0120 - Internal reserved */
    RCC_CLKCON1 CLKCON1;                     /* 0x01A0 - Clock control register 1 */
    RCC_CLKCON2 CLKCON2;                     /* 0x01A4 - Clock control register 2, for CHIP THA6206 and THA6412 */
    RCC_CLKCON3 CLKCON3;                     /* 0x01A8 - Clock control register 3 */
    RCC_CLKCON4 CLKCON4;                     /* 0x01AC - Clock control register 4 */
    RCC_CLKCON5 CLKCON5;                     /* 0x01B0 - Clock control register 5 */
    RCC_CLKCON6 CLKCON6;                     /* 0x01B4 - Clock control register 6, for CHIP THA6206 and THA6412 */
    RCC_CLKCON7 CLKCON7;                     /* 0x01B8 - Clock control register 7, for CHIP THA6206 and THA6412 */
    RCC_CLKCON8 CLKCON8;                     /* 0x01BC - Clock control register 8 */
    RCC_CLKCON9 CLKCON9;                     /* 0x01C0 - Clock control register 9 */
    RCC_CLKCON10 CLKCON10;                   /* 0x01C4 - Clock control register 10 */
    RCC_CLKCON11 CLKCON11;                   /* 0x01C8 - Clock control register 11, for CHIP THA6206 and THA6412 */
    ureg32 RESERVED_01CC[37];                /* 0x01CC - Internal reserved */
    RCC_CLKTIM1CON CLKTIM1CON;               /* 0x0260 - Timer1 clock control register */
    RCC_CLKTIM2CON CLKTIM2CON;               /* 0x0264 - Timer2 clock control register */
    RCC_CLKTIM3CON CLKTIM3CON;               /* 0x0268 - Timer3 clock control register */
    RCC_CLKTIM4CON CLKTIM4CON;               /* 0x026C - Timer4 clock control register */
    RCC_CLKTIM5CON CLKTIM5CON;               /* 0x0270 - Timer5 clock control register, for CHIP THA6206 and THA6412 */
    RCC_CLKTIM6CON CLKTIM6CON;               /* 0x0274 - Timer6 clock control register, for CHIP THA6206 and THA6412 */
    ureg32 RESERVED_0278[34];                /* 0x0278 - Internal reserved */
    RCC_CLKEN1 CLKEN1;                       /* 0x0300 - Module clock enable register 1 */
    RCC_CLKEN2 CLKEN2;                       /* 0x0304 - Module clock enable register 2 */
    RCC_CLKEN3 CLKEN3;                       /* 0x0308 - Module clock enable register 3 */
    RCC_CLKEN4 CLKEN4;                       /* 0x030C - Module clock enable register 4 */
    RCC_CLKEN5 CLKEN5;                       /* 0x0310 - Module clock enable register 5 */
    RCC_CLKEN6 CLKEN6;                       /* 0x0314 - Module clock enable register 6 */
    RCC_CLKEN7 CLKEN7;                       /* 0x0318 - Module clock enable register 7 */
    RCC_CLKEN8 CLKEN8;                       /* 0x031C - Module clock enable register 8, for CHIP THA6412 */
    RCC_CLKEN9 CLKEN9;                       /* 0x0320 - Module clock enable register 9, for CHIP THA6412 */
    uint32 RESERVED_0324[15];                /* 0x0324 - Internal reserved */
    RCC_CPUCLUSTER1CLKEN CPUCLUSTER1CLKEN;   /* 0x0360 - Cpu cluster1 clock enable register, for CHIP THA6412 */
    uint32 CPUCLUSTER1CLKENPROT;             /* 0x0364 - Cpu cluster1 clock enable protect register, for CHIP THA6412 */
    uint32 RESERVED_0368[2];                 /* 0x0368 - Internal reserved */
    RCC_CLKENPROC CLKENPROC;                 /* 0x0370 - Process clock enable register, for CHIP THA6412 and THA6104 */
    RCC_CLKENWDT CLKENWDT;                   /* 0x0374 - WDT module clock enable register */
    RCC_CLKENWDTPROT CLKENWDTPROT;           /* 0x0378 - WDT module clock enable protection register */
    RCC_CLKENDIV CLKENDIV;                   /* 0x037C - Module crossover enable register */
    RCC_EXTCLKCON EXTCLKCON;                 /* 0x0380 - External clock output control register */
    RCC_EXTCLKDIV EXTCLKDIV;                 /* 0x0384 - External clock output crossover register */
    RCC_EXTCLKDIVCFG EXTCLKDIVCFG;           /* 0x0388 - External clock output configure register, for CHIP THA6412 and THA6104 */
    ureg32 RESERVED_038C[27];                /* 0x038C - Internal reserved */
    RCC_SYSCLKSWSTAT SYSCLKSWSTAT;           /* 0x03F8 - System clock  switch register */
    RCC_PERCLKSWSTAT PERCLKSWSTAT;           /* 0x03FC - Peripheral clock  switch register, for CHIP THA6412 and THA6104 */
    RCC_PLLLOCKCON PLLLOCKCON;               /* 0x0400 - Pll lock control register */
    RCC_SYSPLLCLKMON SYSPLLCLKMON;           /* 0x0404 - Syspll clock monitoring register */
    RCC_PERPLLMON PERPLLMON;                 /* 0x0408 - Perpll clock monitoring register */
    RCC_HSECLKCON HSECLKCON;                 /* 0x040C - Hse clock monitoring register */
    RCC_HSICLKMON HSICLKMON;                 /* 0x0410 - Hsi clock monitoring register */
    RCC_LSICLKMON LSICLKMON;                 /* 0x0414 - Lsi clock monitoring register */
    RCC_CPUCLKMON CPUCLKMON;                 /* 0x0418 - Cpu clock monitoring register */
    RCC_SYSCLKMON SYSCLKMON;                 /* 0x041C - Sysclk clock monitoring register */
    RCC_AXICLKMON AXICLKMON;                 /* 0x0420 - Axi bus clock monitoring register */
    RCC_AHBCLKMON AHBCLKMON;                 /* 0x0424 - Ahb bus clock monitoring register */
    RCC_APBSTBCLKMON APBSTBCLKMON;           /* 0x0428 - Standby domain apb bus clock monitoring register */
    RCC_WDTCLKMON WDTCLKMON;                 /* 0x042C - Wdt clock monitoring register */
    RCC_IPCNTCLKMON IPCNTCLKMON;             /* 0x0430 - Ipcnt clock monitoring register */
    RCC_IWDGCLKMON IWDGCLKMON;               /* 0x0434 - Iwdg clock monitoring register */
    RCC_GTMCLKMON GTMCLKMON;                 /* 0x0438 - Gtm clock monitoring register */
    RCC_QSPICLKMON QSPICLKMON;               /* 0x043C - Qspi clock monitoring register, for CHIP THA6206 and THA6412 */
    RCC_ESPICLKMON ESPICLKMON;               /* 0x0440 - Espi clock monitoring register */
    RCC_CANCCLKMON CANCCLKMON;               /* 0x0444 - Cancclk clock monitoring register */
    RCC_SARADCCLKMON SARADCCLKMON;           /* 0x0448 - Saradc clock monitoring register */
    RCC_RDCCLKMON RDCCLKMON;                 /* 0x044C - Rdc clock monitoring register, for CHIP THA6206 and THA6412 */
    RCC_DSADCCLKMON DSADCCLKMON;             /* 0x0450 - Dsadc clock monitoring register, for CHIP THA6206 and THA6412 */
    RCC_MSCCLKMON MSCCLKMON;                 /* 0x0454 - Msc clock monitoring register, for CHIP THA6206 and THA6412 */
    RCC_FCCLKMON FCCLKMON;                   /* 0x0458 - Fc clock monitoring register, for CHIP THA6206 and THA6412 */
    RCC_CPUCLKCLUSTER1MON CPUCLKCLUSTER1MON; /* 0x045C - CPU cluster1 clock monitor register, for CHIP THA6412 */
    RCC_AXINVMCFGCLKMON AXINVMCFGCLKMON;     /* 0x460 - AXI NVM Configure register, for CHIP THA6104 */
    uint32 RESERVED_0464[37];                /* 0x0464 - Internal reserved */
    RCC_PROCCLKMON PROCCLKMON;               /* 0x04F8 - Process clock monitor register, for CHIP THA6412 and THA6104 */
    RCC_PROCCLKFREQ PROCCLKFREQ;             /* 0x04FC - Process clock frequency register, for CHIP THA6412 and THA6104 */
    RCC_CLKFREQMONSTAT1 CLKMONSTAT1;         /* 0x0500 - Clock frequency monitoring status register 1 */
    RCC_CLKFREQMONSTAT1CLR CLKSTAT1CLR;      /* 0x0504 - Clock frequency monitoring status clear register 1 */
    RCC_CLKFREQMONSTAT2 CLKMONSTAT2;         /* 0x0508 - Clock frequency monitoring status register 2, for CHIP THA6412 */
    RCC_CLKFREQMONSTAT2CLR CLKSTAT2CLR;      /* 0x050C - Clock frequency monitoring status clear register 2, for CHIP THA6412 */
    RCC_CLKALIVEMONSTAT CLKALIVESTAT;        /* 0x0510 - Clock alive monitoring status register */
    RCC_CLKALIVEMONSTATCLR CLKALIVESTATCLR;  /* 0x0514 - Clock alive monitoring status clear register */
    ureg32 RESERVED_0518[18];                /* 0x0518 - Internal reserved */
    RCC_CLKSFFALMSMEN CLKSFFALMSMEN;         /* 0x0560 - Clock safety register alarm enable register */
    RCC_CLKSFFALMSTAT CLKSFFALMSTAT;         /* 0x0564 - Clock security register alarm status register */
    RCC_CLKSFFALMSTATCLR CLKSFFALMSTATCLR;   /* 0x0568 - Clock security register alarm status clear register */
    RCC_CLKSFFALMFAULTIN CLKSFFALMFAULTIN;   /* 0x056C - Clock safety register alarm status injection register */
    ureg32 RESERVED_0570[4];                 /* 0x0570 - Internal reserved */
    RCC_CLKBEMASK CLKBEMASK;                 /* 0x0580 - Clock domain register bus error mask register */
    RCC_CLKESEALMSTAT CLKESEALMSTAT;         /* 0x0584 - Access E/SE trigger alarm register */
    RCC_CLKESEALMSTATCLR CLKESEALMSTATCLR;   /* 0x0588 - Access E/SE trigger alarm clear register */

} RCC_CLOCK_MODULE;

typedef volatile struct
{
    /* General SFR */
    RCC_RSTSTAT RSTSTAT;                     /* 0x0800 - Reset status register */
    RCC_RSTSTATCLR RSTSTATCLR;               /* 0x0804 - Reset status clear register */
    RCC_SACRSTFLAG SACRSTFLAG;               /* 0x0808 - Sac reset request flag register */
    RCC_SACRSTCLR SACRSTCLR;                 /* 0x080C - Sac reset request flag clear register */
    ureg32 RESERVED_0814[20];                /* 0x0810 - Internal reserved */
    RCC_SWRSTCON SWRSTCON;                   /* 0x0860 - Software reset register (sw triggered rst) */
    RCC_RSTCON1 RSTCON1;                     /* 0x0864 - Reset control register 1 */
    RCC_RSTCON2 RSTCON2;                     /* 0x0868 - Reset control register 2 */
    RCC_RSTCON3 RSTCON3;                     /* 0x086C - Reset control register 3 */
    ureg32 RESERVED_0870[12];                /* 0x0870 - Internal reserved */
    RCC_DBGRSTCON DBGRSTCON;                 /* 0x08A0 - Debug reset control register */
    RCC_WDTRSTCON WDTRSTCON;                 /* 0x08A4 - Wdt reset type control register */
    RCC_STMRSTCON STMRSTCON;                 /* 0x08A8 - STM reset type control register, for CHIP THA6412 and THA6104 */
    uint32 RESERVED_08AC;                    /* 0x08AC - Internal reserved */
    uint32 CPUCLUSTER1RSTPROT;               /* 0x08B0 - CPU cluster 1 reset protection register, for CHIP THA6412 */
    RCC_CPUCLUSTRSTCLR CPUCLUSTER1RSTCLR;    /* 0x08B4 - CPU cluster reset clear register, for CHIP THA6412 */
    RCC_CPUCLUSTER1RSTCON CPUCLUSTER1RSTCON; /* 0x08B8 - CPU cluster reset control register, for CHIP THA6412 */
    RCC_CPURSTCLR CPU2RSTCLR;                /* 0x08BC - Cpu2 reset clear control register, for CHIP THA6412 */
    RCC_CPURSTCON CPU2RSTCON;                /* 0x08C0 - Cpu2 core reset control register, for CHIP THA6412 */
    RCC_CPURSTCLR CPU3RSTCLR;                /* 0x08C4 - Cpu3 reset clear control register, for CHIP THA6412 */
    RCC_CPURSTCON CPU3RSTCON;                /* 0x08C8 - Cpu3 core reset control register, for CHIP THA6412 */
    RCC_CPUCLUSTERRSTCFG CPUCLUSTER1RSTCFG;  /* 0x08CC - cluster1 CPU reset configuration register, for CHIP THA6412 */
    uint32 CPUCLUSTER0RSTPROT;               /* 0x08D0 - CPU cluster 0 reset protection register  */
    RCC_CPUCLUSTRSTCLR CPUCLUSTERRSTCLR;     /* 0x08D4 - CPU cluster reset clear register */
    RCC_CPUCLUSTERRSTCON CPUCLUSTER0RSTCON;  /* 0x08D8 - CPU cluster reset control register */
    RCC_CPURSTCLR CPU0RSTCLR;                /* 0x08DC - Cpu0 reset clear control register */
    RCC_CPURSTCON CPU0RSTCON;                /* 0x08E0 - Cpu0 core reset control register */
    RCC_CPURSTCLR CPU1RSTCLR;                /* 0x08E4 - Cpu1 reset clear control register */
    RCC_CPURSTCON CPU1RSTCON;                /* 0x08E8 - Cpu1 core reset control register */
    RCC_CPUCLUSTERRSTCFG CPUCLUSTER0RSTCFG;  /* 0x08EC - cluster 0 CPU reset configuration register, for CHIP THA6412 and THA6104 */
    RCC_PMCRSTCLR PMCRSTCLR;                 /* 0x08F0 - PMC reset clear register, for CHIP THA6412 and THA6104 */
    RCC_PMCRSTCON PMCRSTCON;                 /* 0x08F4 - PMC reset control register, for CHIP THA6412 and THA6104 */
    ureg32 RESERVED_08F8[2];                 /* 0x08F8 - Internal reserved */
    RCC_MODRSTCON1 MODRSTCON1;               /* 0x0900 - Module reset control register 1 */
    RCC_MODRSTCON2 MODRSTCON2;               /* 0x0904 - Module reset control register 2 */
    RCC_MODRSTCON3 MODRSTCON3;               /* 0x0908 - Module reset control register 3 */
    RCC_MODRSTCON4 MODRSTCON4;               /* 0x090C - Module reset control register 4 */
    RCC_MODRSTCON5 MODRSTCON5;               /* 0x0910 - Module reset control register 5 */
    RCC_MODRSTCON6 MODRSTCON6;               /* 0x0914 - Module reset control register 6 */
    RCC_MODRSTCON7 MODRSTCON7;               /* 0x0918 - Module reset control register 7, for CHIP THA6412 */
    RCC_MODRSTCON8 MODRSTCON8;               /* 0x091C - Module reset control register 8, for CHIP THA6412 and THA6104 */
    ureg32 RESERVED_0920[13];                /* 0x0920 - Internal reserved */
    RCC_MODRSTCONWDT MODRSTCONWDT;           /* 0x0954 - WDT reset control register */
    RCC_WDTRSTPROT WDTRSTPROT;               /* 0x0958 - WDT reset control protection register */
    ureg32 RESERVED_095C[1];                 /* 0x095C - Internal reserved */
    RCC_ESRPORSTIODFEN ESRPORSTIODFEN;       /* 0x0960 - Esr_porst io filtering enables energy register */
    ureg32 RESERVED_0964[39];                /* 0x0964 - Internal reserved */
    RCC_TIMOUTCNTEN TIMOUTCNTEN;             /* 0x0A00 - Timeout count value enable settings */
    RCC_TIMOUTCNT TIMOUTCNT;                 /* 0x0A04 - Timeout count value settings */
    RCC_CPUSHUTDOWNFLAG CPUSHUTDOWNFLAG;     /* 0x0A08 - Cpu shutdown flag register */
    RCC_RCCINTMASK RCCINTMASK;               /* 0x0A0C - Rcc interrupt mask register */
    RCC_RCCINTEN RCCINTEN;                   /* 0x0A10 - Rcc interrupt enable register */
    RCC_RCCINTSTAT RCCINTSTAT;               /* 0x0A14 - Rcc interrupt status register */
    RCC_RCCINTSETCLR RCCINTSETCLR;           /* 0x0A18 - Rcc interrupt set and clear register */
    RCC_RCCINTSETPROT RCCINTSETPROT;         /* 0x0A1C - Rcc interrupt set write-protection register */
    ureg32 RESERVED_0A20[16];                /* 0x0A20 - Internal reserved */
    RCC_RAMLPEXITFLAGCLR RAMLPEXITFLAGCLR;   /* 0x0A60 - Ram exit low power exit complete clear register */
    RCC_RAMLPEXITFLAG RAMLPEXITFLAG;         /* 0x0A64 - Ram exit low power exit complete flag register */
    RCC_RAMLPEXITEN RAMLPEXITEN;             /* 0x0A68 - Ram exit low power exit enable register */
    ureg32 RESERVED_0A6C[37];                /* 0x0A6C - Internal reserved */
    RCC_RSTSFFALMSMEN RSTSFFALMSMEN;         /* 0x0B00 - Reset security register warning enable register */
    RCC_RSTSFFALMSTAT RSTSFFALMSTAT;         /* 0x0B04 - Reset security register alarm status register */
    RCC_RSTSFFALMSTATCLR RSTSFFALMSTATCLR;   /* 0x0B08 - Reset security register alarm status clear register */
    RCC_RSTSFFALMFAULTIN RSTSFFALMFAULTIN;   /* 0x0B0C - Reset security register alarm status injection register */
    ureg32 RESERVED_0B10[28];                /* 0x0B10 - Internal reserved */
    RCC_RSTBEMASK RSTBEMASK;                 /* 0x0B80 - Reset domain trig bus error mask register */
    RCC_RSTESEALMSTAT RSTESEALMSTAT;         /* 0x0B84 - Reset trigger E/SE alarm state register */
    RCC_RSTESEALMSTATCLR RSTESEALMSTATCLR;   /* 0x0B88 - Reset trigger E/SE alarm state clear register */

} RCC_RESET_MODULE;

/**********************************************************************************************************************
 *                                         RCC STB Register Configuration Structure
 *********************************************************************************************************************/

typedef volatile struct
{
    RCC_LSICON1 LSICON1;     /* 0x0000 - Lsi 70k internal oscillator control register 1 */
    RCC_LSICON2 LSICON2;     /* 0x0004 - Lsi 70k internal oscillator control register 2 */
    ureg32 RESERVED_0008[2]; /* 0x0008 - Internal reserved */

    RCC_CLKSTBSEL CLKSTBSEL;                     /* 0x0010 - System clock selection for backup domain */
    RCC_CLKSTBEN CLKSTBEN;                       /* 0x0014 - Backup domain module clock enable */
    ureg32 RESERVED_0018[26];                    /* 0x0018 - Internal reserved */
    RCC_CLKSTBSFFALMSMEN CLKSTBSFFALMSMEN;       /* 0x0080 - reset safety register alarm status enable register */
    RCC_CLKSTBSFFALMSTAT CLKSTBSFFALMSTAT;       /* 0x0084 - reset safety register alarm status register */
    RCC_CLKSTBSFFALMSTATCLR CLKSTBSFFALMSTATCLR; /* 0x0088 - reset safety register alarm status clear register */
    RCC_CLKSTBSFFALMFAULTIN CLKSTBSFFALMFAULTIN; /* 0x008C - reset safety register alarm status injection register */
    ureg32 RESERVED_0090[28];                    /* 0x0090 - Internal reserved */
    RCC_CLKSTBBEMASK CLKSTBBEMASK;               /* 0x0100 - BUS error mask register */
    RCC_CLKSTBESEALMSTAT CLKSTBESEALMSTAT;       /* 0x0104 - Access E/SE register alarm register */
    RCC_CLKSTBESEALMSTATCLR CLKSTBESEALMSTATCLR; /* 0x0108 - Access E/SE register alarm clear register */
/* #Violation: rcc_register_h_REF_2 */
} RCC_STBCLOCK_MODULE;


typedef volatile struct
{
    RCC_STBMODRST STBMODRST;                     /* 0x0200 - Reset control register 1 for backup domain (module reset) */
    RCC_STBSWRST STBSWRST;                       /* 0x0204 - Reset control register 2 for backup domain (system reset) */
    RCC_IORSTEN IORSTEN;                         /* 0x0208 - Rstb_stb_io reset enable register */
    ureg32 RESERVED_020C[29];                    /* 0x020C - Internal reserved */
    RCC_RSTSTBSFFALMSMEN RSTSTBSFFALMSMEN;       /* 0x0280 - Reset security register warning enable register */
    RCC_RSTSTBSFFALMSTAT RSTSTBSFFALMSTAT;       /* 0x0284 - Reset security register alarm status register */
    RCC_RSTSTBSFFALMSTATCLR RSTSTBSFFALMSTATCLR; /* 0x0288 - Reset security register alarm status clear register */
    RCC_RSTSTBSFFALMFAULTIN RSTSTBSFFALMFAULTIN; /* 0x028C - Reset security register alarm status injection register */
    ureg32 RESERVED_0290[28];                    /* 0x0290 - Internal reserved */
    RCC_RSTSTBBEMASK RSTSTBBEMASK;               /* 0x0300 - CLK area register bus error mask register */
    RCC_RSTSTBESEALMSTAT RSTSTBESEALMSTAT;       /* 0x0304 - CLK area register  E/SE  alarm status  register */
    RCC_RSTSTBESEALMSTATCLR RSTSTBESEALMSTATCLR; /* 0x0308 - CLK area register  E/SE  alarm status  clear register */
/* #Violation: rcc_register_h_REF_2 */
} RCC_STBRESET_MODULE;

#endif /* RCC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

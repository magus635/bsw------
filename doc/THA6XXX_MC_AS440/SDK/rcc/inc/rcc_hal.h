/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    rcc_hal.h
 * Author:      00976
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
 *#Violation Summary
 *
 * #rcc_hal_h_REF_1:MISRAC2012-Rule-11.4;
 * Justification: Converting integers to object pointers to reduce register access complexity.
 *
 *#rcc_hal_h_REF_2:MISRAC2012-Rule-2.3;
 * Justification: The members of the type are used in configuration-generated code.
 *
 *#rcc_hal_h_REF_3:MISRAC2012-Dir-4.8;
 * Justification: The implementation of this structs type are used in upper layers.
 *
 * #rcc_hal_h_REF_4:DCL12-C;
 * Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity;
 * 
 * #rcc_hal_h_REF_5:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 * 
 * #rcc_hal_h_REF_6:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 */

#ifndef RCC_HAL_H_
#define RCC_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "rcc_register.h"
#include "tha6_cfg.h"
#include "compilertypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* The enumeration of PLL clock source definition. */
typedef enum
{
    RCC_PLLCLOCKSOURCE_HSI = 0U, /* HSI */
    RCC_PLLCLOCKSOURCE_HSE       /* HSE */
} Rcc_PllClockSource;

/* The enumeration of IPCNT clock source definition. */
typedef enum
{
    RCC_IPCNTCLOCKSOURCE_HSI = 0U, /* HSI */
    RCC_IPCNTCLOCKSOURCE_HSE       /* HSE */
} Rcc_IpcntClockSource;

/* The enumeration of perpll output clock frequency definition. */
typedef enum
{
    RCC_PERPLLCLKTYPE_LOW = 0U, /* Peripheral PLL LOW */
    RCC_PERPLLCLKTYPE_HIGH      /* Peripheral PLL HIGH */
} Rcc_PerPllClkType;

/* The enumeration of PLL post driver control definition. */
typedef enum
{
    RCC_PLLPOSTDIVIDER_ENABLE = 0U, /* Enable post divider output */
    RCC_PLLPOSTDIVIDER_DISABLE      /* Disable post divider output */
/* #Violation: rcc_hal_h_REF_2 */
} Rcc_PllPostDivider;

/* The enumeration of PLL VCO control definition. */
typedef enum
{
    RCC_PLLVCO_ENABLE = 0U, /* Enable VCO output */
    RCC_PLLVCO_DISABLE      /* Disable VCO output */
/* #Violation: rcc_hal_h_REF_2 */
} Rcc_PllVco;

/* The enumeration of PLL mode definition. */
typedef enum
{
    RCC_PLLMODE_DECIMAL = 0U, /* PLL decimal mode */
    RCC_PLLMODE_INTEGER       /* PLL integer mode */
} Rcc_PllMode;

/* The enumeration of CPU clock source definition. */
typedef enum
{
    RCC_CPUCLOCKSOURCE_HSI = 0U, /* HSI as CPU clock source */
    RCC_CPUCLOCKSOURCE_SYSPLL,   /* System PLL as CPU clock source */
    RCC_CPUCLOCKSOURCE_HSE       /* HSE as CPU clock source */
} Rcc_CpuClockSource;

/* The enumeration of peripheral modules' clock source definition. */
typedef enum
{
    RCC_MODULECLOCKSOURCE_HSI = 0U, /* HSI as module clock source */
    RCC_MODULECLOCKSOURCE_PERPLL,   /* System PLL as module clock source */
    RCC_MODULECLOCKSOURCE_HSE       /* HSE as module clock source */
} Rcc_ModuleClockSource;

/* The enumeration of base timer index definition. */
typedef enum
{
    RCC_BASETIMERIDX_1 = 0U, /* Select base timer 0 */
    RCC_BASETIMERIDX_2,      /* Select base timer 1 */
    RCC_BASETIMERIDX_3,      /* Select base timer 2 */
    RCC_BASETIMERIDX_4,      /* Select base timer 3 */
    RCC_BASETIMERIDX_5,      /* Select base timer 4, for CHIP THA6206 and THA6412 */
    RCC_BASETIMERIDX_6       /* Select base timer 5, for CHIP THA6206 and THA6412 */
} Rcc_BasetimerIdx;

/* The enumeration of module clock type definition. */
typedef enum
{
    /* CLKEN1 */
    RCC_MODULECLKTYPE_DMA0CLK = 0U,      /*Select DMA0 clock*/
    RCC_MODULECLKTYPE_DMA1CLK = 4U,      /*Select DMA1 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_DMA2CLK = 5U,      /*Select DMA2 clock*/
    RCC_MODULECLKTYPE_DMA3CLK = 6U,      /*Select DMA3 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_TSENSOR0CLK = 20U, /*Select GMU0 clock*/
    RCC_MODULECLKTYPE_TSENSOR1CLK = 21U, /*Select LMU0 clock*/
    /* CLKEN2 */
    RCC_MODULECLKTYPE_GTMCLK = 32U,       /*Select GTM clock*/
    RCC_MODULECLKTYPE_GETHCLK = 33U,      /*Select GETH clock*/
    RCC_MODULECLKTYPE_HRPWM = 34U,        /*Select HRPWM clock, for CHIP THA6412 and THA6104 */
    RCC_MODULECLKTYPE_BASETIM0PCLK = 36U, /*Select BASETIMER0 PClock*/
    RCC_MODULECLKTYPE_BASETIM1PCLK = 37U, /*Select BASETIMER1 PClock*/
    RCC_MODULECLKTYPE_BASETIM2PCLK = 38U, /*Select BASETIMER2 PClock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_QSPICLK = 48U,      /*Select QSPI clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_I2C0CLK = 52U,      /*Select I2C0 clock*/
    RCC_MODULECLKTYPE_I2C1CLK = 53U,      /*Select I2C1 clock, for CHIP THA6412 and THA6104 */
    RCC_MODULECLKTYPE_MSC0CLK = 56U,      /*Select MSC0 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_MSC1CLK = 57U,      /*Select MSC1 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_MSC2CLK = 58U,      /*Select MSC2 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_ECRCCLK = 60U,      /*Select ECRC clock*/
    /* CLKEN3 */
    RCC_MODULECLKTYPE_SENT0CLK = 64U, /*Select SENT0 clock*/
    RCC_MODULECLKTYPE_SENT1CLK = 65U, /*Select SENT1 clock*/
    RCC_MODULECLKTYPE_SENT2CLK = 66U, /*Select SENT2 clock*/
    RCC_MODULECLKTYPE_SENT3CLK = 67U, /*Select SENT3 clock*/
    RCC_MODULECLKTYPE_SENT4CLK = 68U, /*Select SENT4 clock*/
    RCC_MODULECLKTYPE_SENT5CLK = 69U, /*Select SENT5 clock*/
    RCC_MODULECLKTYPE_SENT6CLK = 70U, /*Select SENT6 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_SENT7CLK = 71U, /*Select SENT7 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_SENT8CLK = 72U, /*Select SENT8 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_SENT9CLK = 73U, /*Select SENT9 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_PSI5CLK = 76U,  /*Select PSI5 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_ESPI0CLK = 80U, /*Select ESPI0 clock*/
    RCC_MODULECLKTYPE_ESPI1CLK = 81U, /*Select ESPI1 clock*/
    RCC_MODULECLKTYPE_ESPI2CLK = 82U, /*Select ESPI2 clock*/
    RCC_MODULECLKTYPE_ESPI3CLK = 83U, /*Select ESPI3 clock*/
    RCC_MODULECLKTYPE_ESPI4CLK = 84U, /*Select ESPI4 clock*/
    RCC_MODULECLKTYPE_ESPI5CLK = 85U, /*Select ESPI5 clock*/
    RCC_MODULECLKTYPE_ESPI6CLK = 86U, /*Select ESPI6 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_ESPI7CLK = 87U, /*Select ESPI7 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_ESPI8CLK = 88U, /*Select ESPI8 clock, for CHIP THA6412 and THA6206*/
    /* CLKEN4 */
    RCC_MODULECLKTYPE_ASI0CLK = 96U,   /*Select ASI0 clock*/
    RCC_MODULECLKTYPE_ASI1CLK = 97U,   /*Select ASI1 clock*/
    RCC_MODULECLKTYPE_ASI2CLK = 98U,   /*Select ASI2 clock*/
    RCC_MODULECLKTYPE_ASI3CLK = 99U,   /*Select ASI3 clock*/
    RCC_MODULECLKTYPE_ASI4CLK = 100U,  /*Select ASI4 clock*/
    RCC_MODULECLKTYPE_ASI5CLK = 101U,  /*Select ASI5 clock*/
    RCC_MODULECLKTYPE_ASI6CLK = 102U,  /*Select ASI6 clock*/
    RCC_MODULECLKTYPE_ASI7CLK = 103U,  /*Select ASI7 clock*/
    RCC_MODULECLKTYPE_CAN0CLK = 112U,  /*Select CAN0 clock*/
    RCC_MODULECLKTYPE_CAN1CLK = 113U,  /*Select CAN1 clock*/
    RCC_MODULECLKTYPE_CAN2CLK = 114U,  /*Select CAN2 clock*/
    RCC_MODULECLKTYPE_CAN3CLK = 115U,  /*Select CAN3 clock*/
    RCC_MODULECLKTYPE_CAN4CLK = 116U,  /*Select CAN4 clock*/
    RCC_MODULECLKTYPE_CAN5CLK = 117U,  /*Select CAN5 clock*/
    RCC_MODULECLKTYPE_CAN6CLK = 118U,  /*Select CAN6 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_CAN7CLK = 119U,  /*Select CAN7 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_CAN8CLK = 120U,  /*Select CAN8 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_CAN9CLK = 121U,  /*Select CAN9 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_CAN10CLK = 122U, /*Select CAN10 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_CAN11CLK = 123U, /*Select CAN11 clock, for CHIP THA6412*/
    /* CLKEN5 */
    RCC_MODULECLKTYPE_DSADC0CLK = 128U,   /*Select DSADC0 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_DSADC1CLK = 129U,   /*Select DSADC1 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_DSADC2CLK = 130U,   /*Select DSADC2 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_DSADC3CLK = 131U,   /*Select DSADC3 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_DSADC4CLK = 132U,   /*Select DSADC4 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_DSADC5CLK = 133U,   /*Select DSADC5 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_DSADC6CLK = 134U,   /*Select DSADC6 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_DSADC7CLK = 135U,   /*Select DSADC7 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_DSADC8CLK = 136U,   /*Select DSADC8 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_DSADC9CLK = 137U,   /*Select DSADC9 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_SARADC0CLK = 140U,  /*Select SARADC0 clock*/
    RCC_MODULECLKTYPE_SARADC1CLK = 141U,  /*Select SARADC1 clock*/
    RCC_MODULECLKTYPE_SARADC2CLK = 142U,  /*Select SARADC2 clock*/
    RCC_MODULECLKTYPE_SARADC3CLK = 143U,  /*Select SARADC3 clock*/
    RCC_MODULECLKTYPE_SARADC8CLK = 144U,  /*Select SARADC8 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_SARADC9CLK = 145U,  /*Select SARADC9 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_SARADC4CLK = 146U,  /*Select SARADC4 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_SARADC5CLK = 147U,  /*Select SARADC5 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_SARADC6CLK = 148U,  /*Select SARADC6 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_SARADC7CLK = 149U,  /*Select SARADC7 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_SARADC10CLK = 150U, /*Select SARADC10 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_SARADC11CLK = 151U, /*Select SARADC11 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_FC0CLK = 152U,      /*Select FC0 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_FC1CLK = 153U,      /*Select FC1 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_FC2CLK = 154U,      /*Select FC2 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_FC3CLK = 155U,      /*Select FC3 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_RDC0CLK = 156U,     /*Select RDC0 clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_RDC1CLK = 157U,     /*Select RDC1 clock, for CHIP THA6412*/
    /* CLKEN6 */
    RCC_MODULECLKTYPE_BASETIM1TIMPCLK = 160U, /*BASETIMER1 InputClock*/
    RCC_MODULECLKTYPE_BASETIM2TIMPCLK = 161U, /*BASETIMER2 InputClock*/
    RCC_MODULECLKTYPE_BASETIM3TIMPCLK = 162U, /*BASETIMER3 InputClock*/
    RCC_MODULECLKTYPE_BASETIM4TIMPCLK = 163U, /*BASETIMER4 InputClock*/
    RCC_MODULECLKTYPE_BASETIM5TIMPCLK = 164U, /*BASETIMER5 InputClock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_BASETIM6TIMPCLK = 165U, /*BASETIMER6 InputClock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_GMU0CLK = 172U,         /*Select GMU0 clock*/
    RCC_MODULECLKTYPE_GMU1CLK = 173U,         /*Select GMU1 clock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_LMU1CLK = 176U,         /*Select LMU1CLK clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_LMU2CLK = 177U,         /*Select LMU2CLK clock*/
    RCC_MODULECLKTYPE_LMU3CLK = 178U,         /*Select LMU3CLK clock, for CHIP THA6412 and THA6206*/
    RCC_MODULECLKTYPE_DBGCLK = 188U,          /*Select DBGCLK clock*/
    RCC_MODULECLKTYPE_ATBCLK = 189U,          /*Select ATBCLK clock*/
    RCC_MODULECLKTYPE_TRACECLK = 190U,        /*Select TRACECLK clock*/
    /* CLKEN7 */
    RCC_MODULECLKTYPE_FLASHHCLK0 = 192U,   /*Cluster0 FLASH HCLK InputClock*/
    RCC_MODULECLKTYPE_FLASHPFC0CLK = 193U, /*FLASHPFC0CLK InputClock*/
    RCC_MODULECLKTYPE_FLASHPFC1CLK = 194U, /*FLASHPFC1CLK InputClock*/
    RCC_MODULECLKTYPE_FLASHDFC0CLK = 195U, /*FLASHPFC0CLK InputClock*/
    RCC_MODULECLKTYPE_FLASHPFC2CLK = 196U, /*FLASHPFC2CLK InputClock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_FLASHPFC3CLK = 197U, /*FLASHPFC3CLK InputClock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_FLASHHCLK1 = 198U,   /*Cluster1 FLASH HCLK InputClock, for CHIP THA6412*/

    /* CLKEN8 , for CHIP THA6412*/
    RCC_MODULECLKTYPE_SENT10CLK = 224U, /*Select SENT10 clock*/
    RCC_MODULECLKTYPE_SENT11CLK = 225U, /*Select SENT11 clock*/
    RCC_MODULECLKTYPE_SENT12CLK = 226U, /*Select SENT12 clock*/
    RCC_MODULECLKTYPE_SENT13CLK = 227U, /*Select SENT13 clock*/
    RCC_MODULECLKTYPE_SENT14CLK = 228U, /*Select SENT14 clock*/
    RCC_MODULECLKTYPE_SENT15CLK = 229U, /*Select SENT15 clock*/
    RCC_MODULECLKTYPE_SENT16CLK = 230U, /*Select SENT16 clock*/
    RCC_MODULECLKTYPE_SENT17CLK = 231U, /*Select SENT17 clock*/
    RCC_MODULECLKTYPE_SENT18CLK = 232U, /*Select SENT18 clock*/
    RCC_MODULECLKTYPE_SENT19CLK = 233U, /*Select SENT19 clock*/
    RCC_MODULECLKTYPE_SENT20CLK = 234U, /*Select SENT20 clock*/
    RCC_MODULECLKTYPE_SENT21CLK = 235U, /*Select SENT21 clock*/
    RCC_MODULECLKTYPE_SENT22CLK = 236U, /*Select SENT22 clock*/
    RCC_MODULECLKTYPE_SENT23CLK = 237U, /*Select SENT23 clock*/
    RCC_MODULECLKTYPE_SENT24CLK = 238U, /*Select SENT24 clock*/

    /* CLKEN9 , for CHIP THA6412*/
    RCC_MODULECLKTYPE_ASI8CLK = 256U,  /*Select ASI8 clock*/
    RCC_MODULECLKTYPE_ASI9CLK = 257U,  /*Select ASI9 clock*/
    RCC_MODULECLKTYPE_ASI10CLK = 258U, /*Select ASI10 clock*/
    RCC_MODULECLKTYPE_ASI11CLK = 259U, /*Select ASI11 clock*/
    RCC_MODULECLKTYPE_ASI12CLK = 260U, /*Select ASI12 clock*/
    RCC_MODULECLKTYPE_ASI13CLK = 261U, /*Select ASI13 clock*/
    RCC_MODULECLKTYPE_ASI14CLK = 262U, /*Select ASI14 clock*/
    RCC_MODULECLKTYPE_ASI15CLK = 263U, /*Select ASI15 clock*/
    RCC_MODULECLKTYPE_ASI16CLK = 264U, /*Select ASI16 clock*/
    RCC_MODULECLKTYPE_ASI17CLK = 265U, /*Select ASI17 clock*/
    RCC_MODULECLKTYPE_ASI18CLK = 266U, /*Select ASI18 clock*/
    RCC_MODULECLKTYPE_ASI19CLK = 267U, /*Select ASI19 clock*/
    RCC_MODULECLKTYPE_ASI20CLK = 268U, /*Select ASI20 clock*/
    RCC_MODULECLKTYPE_ASI21CLK = 269U, /*Select ASI21 clock*/
    RCC_MODULECLKTYPE_ASI22CLK = 270U, /*Select ASI22 clock*/
    RCC_MODULECLKTYPE_ASI23CLK = 271U, /*Select ASI23 clock*/

    /* CLKENWDT */
    RCC_MODULECLKTYPE_SAFEWDTCLK = 288U, /*SAFEWDTCLK InputClock*/
    RCC_MODULECLKTYPE_CPU0WDTCLK = 292U, /*CPU0WDTCLK InputClock*/
    RCC_MODULECLKTYPE_CPU1WDTCLK = 293U, /*CPU1WDTCLK InputClock*/
    RCC_MODULECLKTYPE_CPU2WDTCLK = 294U, /*CPU2WDTCLK InputClock, for CHIP THA6412*/
    RCC_MODULECLKTYPE_CPU3WDTCLK = 295U  /*CPU3WDTCLK InputClock, for CHIP THA6412*/

} Rcc_ModuleClkType;

/* The enumeration of PLL type definition. */
typedef enum
{
    RCC_PLLTYPE_SYS = 0U, /* Select system PLL */
    RCC_PLLTYPE_PER       /* Select peripheral PLL */
} Rcc_PllType;

/* The enumeration of clock set definition. */
typedef enum
{
    RCC_MODULECLK_DISABLE = 0U, /* Disable RCC output module clock */
    RCC_MODULECLK_ENABLE        /* Enable RCC output module clock */
} Rcc_ModuleClkSet;

/* The enumeration of reset source select definition. */
typedef enum
{
    RCC_RSTSRC_ESR0 = 0U,     /* Select ESR0 as reset source */
    RCC_RSTSRC_ESR1 = 2U,     /* Select ESR1 as reset source */
    RCC_RSTSRC_SAC = 4U,      /* Select SAC as reset source */
    RCC_RSTSRC_SW = 6U,       /* Select SW as reset source */
    RCC_RSTSRC_IWDG = 8U,     /* Select IWDG as reset source */
    RCC_RSTSRC_CPU2REQ = 10U, /* Select CPU2 as reset source */
    RCC_RSTSRC_CPU3REQ = 12U, /* Select CPU3 as reset source */
    RCC_RSTSRC_CPU0REQ = 14U, /* Select CPU0 as reset source */
    RCC_RSTSRC_CPU1REQ = 16U  /* Select CPU1 as reset source */
} Rcc_RstSrc;

/* The enumeration of reset type selection definition. */
typedef enum
{
    RCC_RSTTYPE_NONE = 0U, /* None reset */
    RCC_RSTTYPE_SYS = 1U,  /* System reset */
    RCC_RSTTYPE_APP        /* Application reset */
} Rcc_RstType;

/* The enumeration of reset reason definition. */
typedef enum
{
    RCC_RSTREASON_ESR0 = 0U,         /* The last reset was triggered by ESR0 */
    RCC_RSTREASON_ESR1 = 1U,         /* The last reset was triggered by ESR1 */
    RCC_RSTREASON_SAC = 2U,          /* The last reset was triggered by SAC */
    RCC_RSTREASON_SW = 3U,           /* The last reset was triggered by SW */
    RCC_RSTREASON_IWDG = 4U,         /* The last reset was triggered by IWDG */
    RCC_RSTREASON_CPU0DBGRST = 5U,   /* The last reset was triggered by CPU0 DBG reset */
    RCC_RSTREASON_CPU1DBGRST = 6U,   /* The last reset was triggered by CPU1 DBG reset */
    RCC_RSTREASON_CPU0WARMRST = 7U,  /* The last reset was triggered by CPU0 warm reset */
    RCC_RSTREASON_CPU1WARMRST = 8U,  /* The last reset was triggered by CPU1 warm reset */
    RCC_RSTREASON_HSMDBGRST = 9U,    /* The last reset was triggered by HSM DBG system reset */
    RCC_RSTREASON_CPU2DBGRST = 10U,  /* The last reset was triggered by CPU2 DBG reset */
    RCC_RSTREASON_CPU3DBGRST = 11U,  /* The last reset was triggered by CPU3 DBG reset */
    RCC_RSTREASON_CPU2WARMRST = 12U, /* The last reset was triggered by CPU2 warm reset */
    RCC_RSTREASON_CPU3WARMRST = 13U, /* The last reset was triggered by CPU3 warm reset */
    RCC_RSTREASON_PORSTPIN = 16U,    /* The last reset was triggered by PORSTPIN */
    RCC_RSTREASON_IST = 17U,         /* The last reset was triggered by IST */
    RCC_RSTREASON_HSMAPP = 18U,      /* The last reset was triggered by HSM application reset request */
    RCC_RSTREASON_HSMSYS = 19U,      /* The last reset was triggered by HSM system reset request */
    RCC_RSTREASON_PORON = 23U,       /* The last reset was triggered by power-on */
    RCC_RSTREASON_MUTITYPE,          /* The last reset was triggered by multi-reason */
    RCC_RSTREASON_NONE               /* No reset action happened */
} Rcc_RstReason;

/* The enumeration of PLL status definition. */
typedef enum
{
    RCC_PLLSTATUS_NOTREADY = 0U, /* PLL clock establish not ready */
    RCC_PLLSTATUS_READY          /* PLL clock establish ready */
} Rcc_PllStatus;

/* The enumeration of module reset type definition. */
typedef enum
{
    /* MODRSTCON1 */
    RCC_MODULERST_DMA0 = 0U,      /* Trigger DMA0 reset */
    RCC_MODULERST_DMA1 = 4U,      /* Trigger DMA1 reset */
    RCC_MODULERST_DMA2 = 5U,      /* Trigger DMA2 reset */
    RCC_MODULERST_DMA3 = 6U,      /* Trigger DMA3 reset */
    RCC_MODULERST_STM = 12U,      /* Trigger STM reset */
    RCC_MODULERST_TSENSOR0 = 20U, /* Trigger T-sentor0 reset */
    RCC_MODULERST_TSENSOR1 = 21U, /* Trigger T-sentor1 reset */
    /* MODRSTCON2 */
    RCC_MODULERST_GTM = 32U,      /* Trigger GTM reset */
    RCC_MODULERST_GETH = 33U,     /* Trigger GETH reset */
    RCC_MODULERST_BASETIM0 = 36U, /* Trigger bastimer1&2 reset */
    RCC_MODULERST_BASETIM1 = 37U, /* Trigger bastimer3&4 reset */
    RCC_MODULERST_BASETIM2 = 38U, /* Trigger bastimer5&6 reset */
    RCC_MODULERST_QSPI = 48U,     /* Trigger QSPI reset */
    RCC_MODULERST_I2C0 = 52U,     /* Trigger I2C0 reset */
    RCC_MODULERST_I2C1 = 53U,     /* Trigger I2C1 reset */
    RCC_MODULERST_MSC0 = 56U,     /* Trigger MSC0 reset */
    RCC_MODULERST_MSC1 = 57U,     /* Trigger MSC1 reset */
    RCC_MODULERST_MSC2 = 58U,     /* Trigger MSC2 reset */
    RCC_MODULERST_ECRC = 60U,     /* Trigger ECRC reset */
    /* MODRSTCON3 */
    RCC_MODULERST_SENT0 = 64U, /* Trigger SENT0 reset */
    RCC_MODULERST_SENT1 = 65U, /* Trigger SENT1 reset */
    RCC_MODULERST_SENT2 = 66U, /* Trigger SENT2 reset */
    RCC_MODULERST_SENT3 = 67U, /* Trigger SENT3 reset */
    RCC_MODULERST_SENT4 = 68U, /* Trigger SENT4 reset */
    RCC_MODULERST_SENT5 = 69U, /* Trigger SENT5 reset */
    RCC_MODULERST_SENT6 = 70U, /* Trigger SENT6 reset */
    RCC_MODULERST_SENT7 = 71U, /* Trigger SENT7 reset */
    RCC_MODULERST_SENT8 = 72U, /* Trigger SENT8 reset */
    RCC_MODULERST_SENT9 = 73U, /* Trigger SENT9 reset */
    RCC_MODULERST_PSI5 = 76U,  /* Trigger PSI5 reset */
    RCC_MODULERST_ESPI0 = 80U, /* Trigger ESPI0 reset */
    RCC_MODULERST_ESPI1 = 81U, /* Trigger ESPI1 reset */
    RCC_MODULERST_ESPI2 = 82U, /* Trigger ESPI2 reset */
    RCC_MODULERST_ESPI3 = 83U, /* Trigger ESPI3 reset */
    RCC_MODULERST_ESPI4 = 84U, /* Trigger ESPI4 reset */
    RCC_MODULERST_ESPI5 = 85U, /* Trigger ESPI5 reset */
    RCC_MODULERST_ESPI6 = 86U, /* Trigger ESPI6 reset */
    RCC_MODULERST_ESPI7 = 87U, /* Trigger ESPI7 reset */
    RCC_MODULERST_ESPI8 = 88U, /* Trigger ESPI8 reset */
    /* MODRSTCON4 */
    RCC_MODULERST_ASI0 = 96U,   /* Trigger ASI0 reset */
    RCC_MODULERST_ASI1 = 97U,   /* Trigger ASI1 reset */
    RCC_MODULERST_ASI2 = 98U,   /* Trigger ASI2 reset */
    RCC_MODULERST_ASI3 = 99U,   /* Trigger ASI3 reset */
    RCC_MODULERST_ASI4 = 100U,  /* Trigger ASI4 reset */
    RCC_MODULERST_ASI5 = 101U,  /* Trigger ASI5 reset */
    RCC_MODULERST_ASI6 = 102U,  /* Trigger ASI6 reset */
    RCC_MODULERST_ASI7 = 103U,  /* Trigger ASI7 reset */
    RCC_MODULERST_MCAN0 = 112U, /* Trigger MCAN0 reset */
    RCC_MODULERST_MCAN1 = 115U, /* Trigger MCAN1 reset */
    RCC_MODULERST_MCAN2 = 118U, /* Trigger MCAN2 reset */
    RCC_MODULERST_MCAN3 = 121U, /* Trigger MCAN3 reset */
    /* MODRSTCON5 */
    RCC_MODULERST_DSADC0 = 128U,   /* Trigger DSADC0 reset */
    RCC_MODULERST_DSADC1 = 129U,   /* Trigger DSADC1 reset */
    RCC_MODULERST_DSADC2 = 130U,   /* Trigger DSADC2 reset */
    RCC_MODULERST_DSADC3 = 131U,   /* Trigger DSADC3 reset */
    RCC_MODULERST_DSADC4 = 132U,   /* Trigger DSADC4 reset */
    RCC_MODULERST_DSADC5 = 133U,   /* Trigger DSADC5 reset */
    RCC_MODULERST_DSADC6 = 134U,   /* Trigger DSADC6 reset */
    RCC_MODULERST_DSADC7 = 135U,   /* Trigger DSADC7 reset */
    RCC_MODULERST_DSADC8 = 136U,   /* Trigger DSADC8 reset */
    RCC_MODULERST_DSADC9 = 137U,   /* Trigger DSADC9 reset */
    RCC_MODULERST_SARADC0 = 140U,  /* Trigger SARADC0 reset */
    RCC_MODULERST_SARADC1 = 141U,  /* Trigger SARADC1 reset */
    RCC_MODULERST_SARADC2 = 142U,  /* Trigger SARADC2 reset */
    RCC_MODULERST_SARADC3 = 143U,  /* Trigger SARADC3 reset */
    RCC_MODULERST_SARADC8 = 144U,  /* Trigger SARADC8 reset */
    RCC_MODULERST_SARADC9 = 145U,  /* Trigger SARADC9 reset */
    RCC_MODULERST_SARADC4 = 146U,  /* Trigger SARADC4 reset */
    RCC_MODULERST_SARADC5 = 147U,  /* Trigger SARADC5 reset */
    RCC_MODULERST_SARADC6 = 148U,  /* Trigger SARADC6 reset */
    RCC_MODULERST_SARADC7 = 149U,  /* Trigger SARADC7 reset */
    RCC_MODULERST_SARADC10 = 150U, /* Trigger SARADC10 reset */
    RCC_MODULERST_SARADC11 = 151U, /* Trigger SARADC11 reset */
    RCC_MODULERST_FC0 = 152U,      /* Trigger FC0 reset */
    RCC_MODULERST_FC1 = 153U,      /* Trigger FC1 reset */
    RCC_MODULERST_FC2 = 154U,      /* Trigger FC2 reset */
    RCC_MODULERST_FC3 = 155U,      /* Trigger FC3 reset */
    RCC_MODULERST_RDC0 = 156U,     /* Trigger RDC0 reset */
    RCC_MODULERST_RDC1 = 157U,     /* Trigger RDC1 reset */
    /* MODRSTCON6 */
    RCC_MODULERST_BUSPROT = 160U, /* Trigger BUSPROT reset */
    /* MODRSTCON7 */
    RCC_MODULERST_SENT10 = 192U, /* Trigger SENT10 reset */
    RCC_MODULERST_SENT11 = 193U, /* Trigger SENT11 reset */
    RCC_MODULERST_SENT12 = 194U, /* Trigger SENT12 reset */
    RCC_MODULERST_SENT13 = 195U, /* Trigger SENT13 reset */
    RCC_MODULERST_SENT14 = 196U, /* Trigger SENT14 reset */
    RCC_MODULERST_SENT15 = 197U, /* Trigger SENT15 reset */
    RCC_MODULERST_SENT16 = 198U, /* Trigger SENT16 reset */
    RCC_MODULERST_SENT17 = 199U, /* Trigger SENT17 reset */
    RCC_MODULERST_SENT18 = 200U, /* Trigger SENT18 reset */
    RCC_MODULERST_SENT19 = 201U, /* Trigger SENT19 reset */
    RCC_MODULERST_SENT20 = 202U, /* Trigger SENT20 reset */
    RCC_MODULERST_SENT21 = 203U, /* Trigger SENT21 reset */
    RCC_MODULERST_SENT22 = 204U, /* Trigger SENT22 reset */
    RCC_MODULERST_SENT23 = 205U, /* Trigger SENT23 reset */
    RCC_MODULERST_SENT24 = 206U, /* Trigger SENT24 reset */

    /* MODRSTCON8 */
    RCC_MODULERST_ASI8 = 224U,  /* Trigger ASI8 reset */
    RCC_MODULERST_ASI9 = 225U,  /* Trigger ASI9 reset */
    RCC_MODULERST_ASI10 = 226U, /* Trigger ASI10 reset */
    RCC_MODULERST_ASI11 = 227U, /* Trigger ASI11 reset */
    RCC_MODULERST_ASI12 = 228U, /* Trigger ASI12 reset */
    RCC_MODULERST_ASI13 = 229U, /* Trigger ASI13 reset */
    RCC_MODULERST_ASI14 = 230U, /* Trigger ASI14 reset */
    RCC_MODULERST_ASI15 = 231U, /* Trigger ASI15 reset */
    RCC_MODULERST_ASI16 = 232U, /* Trigger ASI16 reset */
    RCC_MODULERST_ASI17 = 233U, /* Trigger ASI17 reset */
    RCC_MODULERST_ASI18 = 234U, /* Trigger ASI18 reset */
    RCC_MODULERST_ASI19 = 235U, /* Trigger ASI19 reset */
    RCC_MODULERST_ASI20 = 236U, /* Trigger ASI20 reset */
    RCC_MODULERST_ASI21 = 237U, /* Trigger ASI21 reset */
    RCC_MODULERST_ASI22 = 238U, /* Trigger ASI22 reset */
    RCC_MODULERST_ASI23 = 239U, /* Trigger ASI23 reset */

    /* MODRSTCONWDT */
    RCC_MODULERST_SAFEWDT = 256U, /* Trigger safe WDT reset */
    RCC_MODULERST_CPU0WDT = 260U, /* Trigger CPU0 WDT reset */
    RCC_MODULERST_CPU1WDT = 261U, /* Trigger CPU1 WDT reset */
    RCC_MODULERST_CPU2WDT = 262U, /* Trigger CPU2 WDT reset */
    RCC_MODULERST_CPU3WDT = 263U, /* Trigger CPU3 WDT reset */

    RCC_MODULERST_MAX = 288U
} Rcc_ModuleRst;

/* Error indicating flag */
typedef enum
{
    RCC_ERRORFLAG_SUCCESS = 0U, /* Execute successful */
    RCC_ERRORFLAG_TIMEOUT,      /* Code execute timeout */
    RCC_ERRORFLAG_NULLPTR,      /* Null pointer */
    RCC_ERRORFLAG_FAIL,         /* Execute fail */
} Rcc_ErrorFlag;

/* Module reset group index */
typedef enum
{
    RCC_MODULERSTGROUP1 = 0U, /* Module reset group 1 */
    RCC_MODULERSTGROUP2,      /* Module reset group 2 */
    RCC_MODULERSTGROUP3,      /* Module reset group 3 */
    RCC_MODULERSTGROUP4,      /* Module reset group 4 */
    RCC_MODULERSTGROUP5,      /* Module reset group 5 */
    RCC_MODULERSTGROUP6,      /* Module reset group 6 */
    RCC_MODULERSTGROUP7,      /* Module reset group 7 */
    RCC_MODULERSTGROUP8,      /* Module reset group 8 */
    RCC_MODULERSTWDT          /* Module reset for WDT */
/* #Violation: rcc_hal_h_REF_2 */
} Rcc_ModuleRstGroup;

/* Module clock gate group index */
typedef enum
{
    RCC_MODULECLKGROUP1 = 0U, /* Module clock group 1 */
    RCC_MODULECLKGROUP2,      /* Module clock group 2 */
    RCC_MODULECLKGROUP3,      /* Module clock group 3 */
    RCC_MODULECLKGROUP4,      /* Module clock group 4 */
    RCC_MODULECLKGROUP5,      /* Module clock group 5 */
    RCC_MODULECLKGROUP6,      /* Module clock group 6 */
    RCC_MODULECLKGROUP7,      /* Module clock group 7 */
    RCC_MODULECLKGROUP8,      /* Module clock group 8 */
    RCC_MODULECLKGROUP9,      /* Module clock group 9 */
    RCC_MODULECLKWDT          /* Module clock WDT*/
/* #Violation: rcc_hal_h_REF_2 */
} Rcc_ModuleClkGroup;

/* The enumeration of SSMOD Frequency modulation mode */
typedef enum
{
    RCC_SSMODMIDMODE = 0U, /* middle sperad */
    RCC_SSMODDOWNMODE      /* down sperad */
} Rcc_SSMODMode;

/* The enumeration of EXT type definition. */
typedef enum
{
    RCC_CLOCK_EXT0 = 0U, /* Clock export 0 */
    RCC_CLOCK_EXT1       /* Clock export 1 */
} Rcc_ClockExtType;

/* The enumeration of EXT0 output clock selection definition. */
typedef enum
{
    RCC_EXT0_CPUCLK = 0U,   /* CPU Clock */
    RCC_EXT0_SYSPLLCLK,     /* SYSPLL Clock */
    RCC_EXT0_PERPLLCLK,     /* PERPLL (FOUT1PH0) Clock */
    RCC_EXT0_HSECLK,        /* HSE Clock */
    RCC_EXT0_HSICLK,        /* HSI Clock */
    RCC_EXT0_WDTCLK,        /* CPUWDT Clock */
    RCC_EXT0_LSICLK,        /* LSI Clock */
    RCC_EXT0_IWDGCLK,       /* IWDG Clock */
    RCC_EXT0_SYSCLK,        /* System Clock */
    RCC_EXT0_AXICLK,        /* AXI BUS Clock */
    RCC_EXT0_AHBCLK,        /* AHB BUS Clock */
    RCC_EXT0_APBSTBCLK,     /* APB STB Clock */
    RCC_EXT0_STMCLK,        /* STM Clock */
    RCC_EXT0_CPUPCLKDBGCLK, /* CPU PCLK DBG Clock */
    RCC_EXT0_CPUATCLKDCLK,  /* CPU ATCLKD Clock */
    RCC_EXT0_CPUATCLKICLK,  /* CPU ATCLKI Clock */
    RCC_EXT0_GTMCLK,        /* GTM Clock */
    RCC_EXT0_IPCNTCLK,      /* IPCNT Clock */
    RCC_EXT0_DBGCLK,        /* DBG Clock */
    RCC_EXT0_ATBCLK,        /* ATB Clock */
    RCC_EXT0_TRACECLK,      /* TRACE Clock */
    RCC_EXT0_PROCCLK,       /* PROC Clock, for CHIP THA6412 */
    RCC_EXT0_RESERVED
} Rcc_Ext0ClockSel;

/* The enumeration of EXT1 output clock selection definition. */
typedef enum
{
    RCC_EXT1_CPUCLK = 0U,          /* CPU Clock */
    RCC_EXT1_SYSPLLCLK,            /* SYSPLL Clock */
    RCC_EXT1_PERPLLCLK,            /* PERPLL(FOUT1PH0) Clock */
    RCC_EXT1_QSPICLK,              /* QSPI Clock, for CHIP THA6206 and THA6412 */
    RCC_EXT1_HSICLK,               /* HSI Clock */
    RCC_EXT1_ESPICLK,              /* ESPI Clock */
    RCC_EXT1_CANCLK,               /* CAN Clock */
    RCC_EXT1_SARADCCLK,            /* SARADC Clock */
    RCC_EXT1_SYSCLK,               /* System Clock */
    RCC_EXT1_AXICLK,               /* AXI BUS Clock */
    RCC_EXT1_AHBCLK,               /* AHB BUS Clock */
    RCC_EXT1_RDCCLK,               /* RDC Clock, for CHIP THA6206 and THA6412 */
    RCC_EXT1_DSADCCLK,             /* DSADC Clock, for CHIP THA6206 and THA6412 */
    RCC_EXT1_MSCCLK,               /* MSC Clock, for CHIP THA6206 and THA6412 */
    RCC_EXT1_ASIBUADCLK,           /* ASI BAUD Clock */
    RCC_EXT1_SYSPLLREFCLK,         /* SYSPLL Reference Clock */
    RCC_EXT1_PERPLLREFCLK,         /* PERPLL Reference Clock */
    RCC_EXT1_DCDCCLK,              /* DCDC Clock */
    RCC_EXT1_SYSPLLFOUTVCOCLK,     /* SYSPLL FOUTVCO Clock */
    RCC_EXT1_SYSPLLFOUTPOSTDIVCLK, /* SYSPLL FOUTPOSTDIV Clock */
    RCC_EXT1_SYSPLLFOUT1PH180CLK,  /* SYSPLL FOUT1PH180 Clock */
    RCC_EXT1_SYSPLLCLKSSCGCLK,     /* SYSPLL CLKSSCG Clock */
    RCC_EXT1_PERPLLFOUTVCOCLK,     /* PERPLL FOUTVCO Clock */
    RCC_EXT1_PERPLLFOUTPOSTDIVCLK, /* PERPLL FOUTPOSTDIV Clock */
    RCC_EXT1_PERPLLFOUT1PH180CLK,  /* PERPLL FOUT1PH180 Clock */
    RCC_EXT1_PERPLLCLKSSCGCLK,     /* PERPLL CLKSSCG Clock, for CHIP THA6412 */
    RCC_EXT1_RESERVED
} Rcc_Ext1ClockSel;

/* The enumeration of EXT divider Mode definition. */
typedef enum
{
    RCC_CLOCK_EXTDIV_CLOSE = 0U, /* divider close */
    RCC_CLOCK_EXTDIV_INTEGER,    /* divider integer mode */
    RCC_CLOCK_EXTDIV_DECIMAL     /* divider decimal mode */
} Rcc_ClockExtDivMode;

/* The enumeration of Clock monitor divider definition. */
typedef enum
{
    RCC_CLOCK_ALIVE_2DIV = 0U,  /* 2 divider */
    RCC_CLOCK_ALIVE_4DIV,       /* 4 divider */
    RCC_CLOCK_ALIVE_8DIV,       /* 8 divider */
    RCC_CLOCK_ALIVE_16DIV,      /* 16 divider */
    RCC_CLOCK_ALIVE_32DIV,      /* 32 divider */
    RCC_CLOCK_ALIVE_64DIV,      /* 64 divider */
    RCC_CLOCK_ALIVE_128DIV,     /* 128 divider */
    RCC_CLOCK_ALIVE_256DIV,     /* 256 divider */
} Rcc_ClockAliveMonDiv;

/* The enumeration of module monitor type definition. */
typedef enum
{
    RCC_CLOCK_FREQMON_SYSPLL = 0U,          /* SYSPLL frequency monitor */
    RCC_CLOCK_FREQMON_PERPLL = 2U,          /* PERPLL frequency monitor */
    RCC_CLOCK_FREQMON_HSE  = 4U,            /* HSE frequency monitor */
    RCC_CLOCK_FREQMON_HSI  = 6U,            /* HSI frequency monitor */
    RCC_CLOCK_FREQMON_LSI  = 8U,            /* LSI frequency monitor */
    RCC_CLOCK_FREQMON_CLUSTER0CPU  = 10U,   /* Cluster0 CPU frequency monitor */
    RCC_CLOCK_FREQMON_SYSTEM  = 12U,        /* System frequency monitor */
    RCC_CLOCK_FREQMON_AXI  = 14U,           /* AXI frequency monitor */
    RCC_CLOCK_FREQMON_AHB  = 16U,           /* AHB frequency monitor */
    RCC_CLOCK_FREQMON_APBSTB  = 18U,        /* APBSTB frequency monitor */
    RCC_CLOCK_FREQMON_WDT  = 20U,           /* WDT frequency monitor */
    RCC_CLOCK_FREQMON_IPCNT  = 22U,         /* IPCNT frequency monitor */
    RCC_CLOCK_FREQMON_IWDG  = 24U,          /* IWDG frequency monitor */
    RCC_CLOCK_FREQMON_GTM  = 26U,           /* GTM frequency monitor */
    RCC_CLOCK_FREQMON_QSPI  = 28U,          /* QSPI frequency monitor */
    RCC_CLOCK_FREQMON_ESPI  = 30U,          /* ESPI frequency monitor */

    RCC_CLOCK_FREQMON_CAN  = 32U,           /* CAN frequency monitor */
    RCC_CLOCK_FREQMON_SARADC  = 34U,        /* SARADC frequency monitor */
    RCC_CLOCK_FREQMON_RDC  = 36U,           /* RDC frequency monitor */
    RCC_CLOCK_FREQMON_DSADC  = 38U,         /* DSADC frequency monitor */
    RCC_CLOCK_FREQMON_MSC  = 40U,           /* MSC frequency monitor */
    RCC_CLOCK_FREQMON_FC  = 42U,            /* FC frequency monitor */
    RCC_CLOCK_FREQMON_PROC  = 44U,          /* PROC frequency monitor */
    RCC_CLOCK_FREQMON_CLUSTER1CPU  = 46U,   /* Cluster1 CPU frequency monitor */
    RCC_CLOCK_FREQMON_AXINVM  = 48U,        /* AXI NVM frequency monitor */

} Rcc_ModuleClkFreqMon;

/* The enumeration of module monitor frequency Status definition. */
typedef enum
{
    RCC_CLOCK_FREQMON_NORMAL = 0U,  /* clock frequency normal */
    RCC_CLOCK_FREQMON_UPPER,        /* clock frequency upper */
    RCC_CLOCK_FREQMON_LOWER,        /* clock frequency lower */
    RCC_CLOCK_FREQMON_MULTI,        /* clock frequency multiple status */
/* #Violation: rcc_hal_h_REF_2 */
} Rcc_MonFreqStatus;

/* The enumeration of module monitor alive Status definition. */
typedef enum
{
    RCC_CLOCK_ALIVEQMON_NORMAL = 0U,  /* clock alive normal */
    RCC_CLOCK_ALIVEQMON_ERROR,        /* clock not alive */
/* #Violation: rcc_hal_h_REF_2 */
} Rcc_MonAliveStatus;

/* The enumeration of PLL loss lock Status definition. */
typedef enum
{
    RCC_CLOCK_PLLLOSSLOCK_NORMAL = 0U,  /* clock alive normal */
    RCC_CLOCK_PLLLOSSLOCK_ERROR,        /* clock not alive */
} Rcc_PLLLossLockStatus;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* This structure can be used to initialize and configure system PLL or peripheral PLL */
/* #Violation: rcc_hal_h_REF_3 */
typedef struct
{
    Rcc_PllClockSource pllSource; /* pllSource */
    Rcc_PllMode pllMode;          /* pllMode */
    uint8 refDiv;                 /* refDiv range from 1 to 63 */
    uint8 postDiv1;               /* postDiv1 range from 1 to 7  */
    uint8 postDiv2;               /* postDiv2 range from  1 to 7  */
    uint8 postDiv3; /* postDiv3 range from  1 to 7 , for CHIP THA6104 */
    uint16 fbDiv; /* fbDiv range from 16 to 2400 in integer mode, from 20 to 240 in decimal mode */
    uint32 frac;  /* frac range from 0 to 2^24  */
} Rcc_PllConfig;

/* This structure can be used to initialize and configure system PLL or peripheral PLL with SSMOD */
/* #Violation: rcc_hal_h_REF_3 */
typedef struct
{
    Rcc_PllClockSource pllSource; /* pllSource */
    Rcc_PllMode pllMode;          /* pllMode */
    uint8 refDiv;                 /* refDiv range from 1 to 63 */
    uint8 postDiv1;               /* postDiv1 range from 1 to 7  */
    uint8 postDiv2;               /* postDiv2 range from  1 to 7  */
    uint8 postDiv3;         /* postDiv3 range from  1 to 7, for CHIP THA6104  */
    uint16 intin;         /* fbDiv=intin range from 16 to 2400 in integer mode, from 20 to 240 in decimal mode */
    uint32 fracin;        /* fracin range from 0 to 2^24  */
    uint8 divval;         /* Configure frequency change speed */
    uint8 sperad;         /* Configure the frequency offset percentage 0.1%~3.1% */
    Rcc_SSMODMode ssMode; /* SSMOD Frequency modulation mode */
} Rcc_PllSsmodConfig;

/* This structure can be used to initialize and configure Clock output */
/* #Violation: rcc_hal_h_REF_3 */
typedef struct
{
    Rcc_ClockExtType clockExt;   /* configure EXT0 or EXT1 */
    Rcc_Ext0ClockSel ext0ClkSel; /* EXT0 output clock selection */
    Rcc_Ext1ClockSel ext1ClkSel; /* EXT1 output clock selection */
    uint16 preDiv;               /* Predivision coefficient */
    Rcc_ClockExtDivMode divMode; /* divider mode */
} Rcc_ClockExtConfig;

/* This structure can be used to initialize and configure Clock monitor */
/* #Violation: rcc_hal_h_REF_3 */
typedef struct
{
    Rcc_ModuleClkFreqMon moduleSelct;   /* configure module montior */
    Rcc_ClockAliveMonDiv aliveDiv;      /* configure alive montior divider */
    uint16 LowThreshold;                /* configure frequency montior low threshold */
    uint16 HighThreshold;               /* configure frequency montior high threshold */
/* #Violation: rcc_hal_h_REF_2 */
}Rcc_ClockMonConfig;

/* #Violation: rcc_hal_h_REF_5 */
#define RCC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rcc_hal_h_REF_6 */
#include "Rcc_MemMap.h"

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/****************************************************************************************************
 * Function:     Rcc_Hal_ReadRstStatusReg
 * Description:  Read reset status register value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint32: reset status register value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
LOCAL_FORCEINLINE uint32 Rcc_Hal_ReadRstStatusReg(void);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Rcc_Hal_ReadRstStatusReg(void)
{
    /* #Violation: rcc_hal_h_REF_1 */
    return RCC_RESET->RSTSTAT.U;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/****************************************************************************************************
 * Function:     Rcc_Hal_EnableHse
 * Description:  Enable HSE clock and stabilize output
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        timeoutTime: The time to wait for HSE workinhg stablely
 * Inout:        None
 * Output:       None
 * Return:       Rcc_ErrorFlag: HSE enbale process state
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976      Create
 ****************************************************************************************************/
extern Rcc_ErrorFlag Rcc_Hal_EnableHse(uint32 timeoutTime);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigSysPll
 * Description:  Configure system PLL and start PLL without waiting for PLL Lock to complete
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pSysPllCfg: Pointer to the system PLL configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2023/06/08    00976      Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigSysPll(const Rcc_PllConfig *const pSysPllCfg);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigSysPllSsmod
 * Description:  Configure system PLL SSMOD and start PLL without waiting for PLL Lock to complete
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        Rcc_PllSsmodConfig: Pointer to the system PLL SSMOD configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2025/02/26    01361      Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigSysPllSsmod(const Rcc_PllSsmodConfig *const pSysPllSsmodCfg);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigPerPll
 * Description:  Configure peripheral PLL and start PLL without waiting for PLL Lock to complete
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPerPllCfg: Pointer to the peripheral PLL configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       Do not configure SSMOD
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976      Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigPerPll(const Rcc_PllConfig *const pPerPllCfg);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigPerPllSsmod
 * Description:  Configure peripheral PLL SSMOD and start PLL without waiting for PLL Lock to complete
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        Rcc_PllSsmodConfig: Pointer to the peripheral PLL SSMOD configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2025/02/26    01361      Create
 ****************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6104)
extern boolean Rcc_Hal_ConfigPerPllSsmod(const Rcc_PllSsmodConfig *const pPerPllSsmodCfg);
#endif
/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigCpuClk
 * Description:  Configure CPU clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        cpuClkSrc: CPU clock source selection
 *               clkDiv: CPU clock divide register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigCpuClk(Rcc_CpuClockSource cpuClkSrc, uint8 clkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigBusClk
 * Description:  Configure system clock divide register value(max value:7)
 *               AXI BUS clock divide register value(max value:8)
 *               APB(same as AHB) BUS clock divide register value(max value:511)
 *               and AHB BUS clock frequency AXI BUS clock frequency system clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        sysClkDiv: System clock divide register value
 *               axiClkDiv: AXI BUS clock divide register value
 *               ahbApbClkDiv: AHB and APB BUS clock divide register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigBusClk(uint8 sysClkDiv, uint8 axiClkDiv, uint16 ahbApbClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigGtmClk
 * Description:  Set GTM clock frequency (the maximum frequency division register value is 31)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: select GTM clock source
 *               gtmClkDiv: Set GTM clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigGtmClk(Rcc_ModuleClockSource clkSrc, uint8 gtmClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigQspiClk
 * Description:  Set QSPI clock frequency (the maximum frequency division register value is 31)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select QSPI clock source
 *               qspiClkDiv: Set QSPI clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigQspiClk(Rcc_ModuleClockSource clkSrc, uint8 qspiClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigEspiClk
 * Description:  Set ESPI clock frequency (the maximum frequency division register value is 31)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select ESPI clock source
 *               espiClkDiv: Set ESPI clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigEspiClk(Rcc_ModuleClockSource clkSrc, uint8 espiClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigCanClk
 * Description:  Set CAN clock frequency (the maximum frequency division register value is 15)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select CAN clock source
 *               canClkDiv: Set CAN clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigCanClk(Rcc_ModuleClockSource clkSrc, uint8 canClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigFcClk
 * Description:  Set FC clock frequency (the maximum frequency division register value is 31)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select FC clock source
 *               fcClkDiv: Set FC clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/04/07    00930       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigFcClk(Rcc_ModuleClockSource clkSrc, uint8 fcClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigSaradcClk
 * Description:  Set SARADC clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select SARADC clock source
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigSaradcClk(Rcc_ModuleClockSource clkSrc);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigRdcDsadcClk
 * Description:  Set RDC and DSADC clock frequency(the both of maximum frequency division register value is 31)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select RDC and DSADC clock source
 *               rdcClkDiv: Set RDC clock division register value
 *               dsadcClkDiv: Set DSADC clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigRdcDsadcClk(Rcc_ModuleClockSource clkSrc, uint8 rdcClkDiv, uint8 dsadcClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigMscClk
 * Description:  Set MSC clock frequency(no frequency division register value)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select MSC clock source
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigMscClk(Rcc_ModuleClockSource clkSrc);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigCpuwdtClk
 * Description:  Set CPU WDT and safety WDT clock frequency (the maximum frequency division register value is 31)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select WDT clock source
 *               wdtClkDiv: Set WDT clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigWdtClk(Rcc_ModuleClockSource clkSrc, uint8 wdtClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigIpcntClk
 * Description:  Set IPCNT clock frequency(the maximum frequency division register value is 63)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select IPCNT clock source
 *               ipcntClkDiv: Set IPCNT clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigIpcntClk(Rcc_IpcntClockSource clkSrc, uint8 ipcntClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigAsiBaudBusClk (for THA6104)
 * Description:  Set ASI BAUD BUS clock frequency (the maximum frequency division register value is 255)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clkSrc: Select ASI BAUD BUS clock source
 *               fcClkDiv: Set ASI BAUD BUS clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/02/19    01361       Create
 ****************************************************************************************************/
#if defined(THA6_THA6104)
extern boolean Rcc_Hal_ConfigAsiBaudBusClk(Rcc_ModuleClockSource clkSrc, uint16 asiBaudBusClkDiv);
#endif
/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigBaseTimerClk
 * Description:  Set selected BASETIMER clock frequency(the maximum frequency division register value is 65535),
 *               and BaseTimer clock frequency is less than or equal to APB BUS clock frequency/2
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (This function is non-reentrant when operating on the same BASETIMER, 
 *                   but reentrant when operating on different BASETIMER.)
 * Input:        baseTimIdx: Select BASETIMER index
 *               clkSrc: set clock source
 *               clkDiv: Set BASETIMER clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigBaseTimerClk(Rcc_BasetimerIdx baseTimIdx, Rcc_ModuleClockSource clkSrc, uint16 clkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_ConfigStmClk
 * Description:  Set STM clock frequency(the maximum frequency division register value is 15)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        stmClkDiv: Set STM clock division register value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/06/03    00930       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ConfigStmClk(uint8 stmClkDiv);

/****************************************************************************************************
 * Function:     Rcc_Hal_EnableModuleClk
 * Description:  Enable or disable selected module clock
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        moduleType: Select module type
 *               clkSet: Enable or disable module clock
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_SetModuleClk(Rcc_ModuleClkType moduleType, Rcc_ModuleClkSet clkSet);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetPllStatus
 * Description:  Get selected (system or peripheral) PLL status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pllType: Select PLL type
 * Inout:        None
 * Output:       None
 * Return:       Rcc_PllStatus: PLL status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern Rcc_PllStatus Rcc_Hal_GetPllStatus(Rcc_PllType pllType);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetSysPllFreq
 * Description:  Get system PLL clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: System PLL clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetSysPllFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetPerPllFreq
 * Description:  Get Peripheral PLL clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        OutClkSel: select high or low output clock frequency
 * Inout:        None
 * Output:       None
 * Return:       float32: Peripheral PLL clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetPerPllFreq(Rcc_PerPllClkType OutClkSel);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetSysClkSrcFreq
 * Description:  Get system clock source frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: system clock source frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/09    01361       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetSysClkSrcFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetCpuClkFreq
 * Description:  Get CPU clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: CPU clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetCpuClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetSysClkFreq
 * Description:  Get system bus clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: system bus clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/09    01361       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetSysClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetAxiClkFreq
 * Description:  Get AXI bus clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: AXI bus clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetAxiClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetAhbApbClkFreq
 * Description:  Get AHB and APB bus clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: AHB and APB bus clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetAhbApbClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetEspiClkFreq
 * Description:  Get ESPI clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: ESPI clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetEspiClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetBasetimerClkFreq
 * Description:  Get BASETIMER clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        baseTimIdx: Basetimer index
 * Inout:        None
 * Output:       None
 * Return:       float32: BASETIMER clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetBasetimerClkFreq(Rcc_BasetimerIdx baseTimIdx);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetAsiBaudClkFreq
 * Description:  Get ASI baud clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: ASI baud clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetAsiBaudClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetMscClkFreq
 * Description:  Get MSC clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: MSC clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetMscClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetGethClkFreq
 * Description:  Get GETH clock frequency, which is same as AXI clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: GETH clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetGethClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetGtmClkFreq
 * Description:  Get GTM clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: GTM clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetGtmClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetStmClkFreq
 * Description:  Get STM clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: STM clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetStmClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetCanClkFreq
 * Description:  Get CAN clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: CAN clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetCanClkFreq(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetWdtClkFreq
 * Description:  Get CPU WDT and safety WDT clock frequency
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       float32: CPU WDT and safety WDT clock frequency
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern float32 Rcc_Hal_GetWdtClkFreq(void);


/****************************************************************************************************
 * Function:     Rcc_Hal_ClockOutputEnable
 * Description:  Configure clock EXT0/1
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clockExtConfig: Pointer to the ext configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2025/02/26    01361      Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ClockOutputEnable(const Rcc_ClockExtConfig * const clockExtConfig);

/****************************************************************************************************
 * Function:     Rcc_Hal_ClockOutputDisable
 * Description:  Configure clock EXT0/1
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        clockExt: Pointer to the ext type
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2025/02/26    01361      Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ClockOutputDisable(Rcc_ClockExtType clockExt);

/****************************************************************************************************
 * Function:     Rcc_Hal_PLLSwitchEnable
 * Description:  Enable PLL Loss Lock switch
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pllType: PLL type
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2025/04/01    01361      Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_PLLSwitchEnable(Rcc_PllType pllType);

/****************************************************************************************************
 * Function:     Rcc_Hal_PLLSwitchDisable
 * Description:  Disable PLL Loss Lock switch
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pllType: PLL type
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2025/04/01    01361      Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_PLLSwitchDisable(Rcc_PllType pllType);

/****************************************************************************************************
 * Function:     Rcc_Hal_GetPLLLossLockStatus
 * Description:  Get PLL Loss Lock flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pllType: PLL type
 * Inout:        None
 * Output:       None
 * Return:       Rcc_PLLLossLockStatus: RCC_CLOCK_PLLLOSSLOCK_NORMAL or RCC_CLOCK_PLLLOSSLOCK_ERROR
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2025/04/01    01361      Create
 ****************************************************************************************************/
extern Rcc_PLLLossLockStatus Rcc_Hal_GetPLLLossLockStatus(Rcc_PllType pllType);

/****************************************************************************************************
 * Function:     Rcc_Hal_ClearPLLLossLockStatus
 * Description:  Clear PLL Loss Lock flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pllType: PLL type
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:      None
 *  Date          Author    Modified
 *  2025/04/01    01361      Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ClearPLLLossLockStatus(Rcc_PllType pllType);

/****************************************************************************************************
 * Function:     Rcc_Hal_InitRstType
 * Description:  Set reset types for different reset sources
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        rstSrc: Reset source selection
 *               rstType: Reset type selection
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_InitRstType(Rcc_RstSrc rstSrc, Rcc_RstType rstType);

/****************************************************************************************************
 * Function:     Rcc_Hal_ReqSwTrigRst
 * Description:  Software trigger reset request
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ReqSwTrigRst(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_ReadRstStatus
 * Description:  Get reset status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       Rcc_RstReason: Reset reason
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern Rcc_RstReason Rcc_Hal_ReadRstStatus(void);

/****************************************************************************************************
 * Function:     Rcc_Hal_ClearRstStatus
 * Description:  Clear reset status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        Rcc_RstReason: Reset reason
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/29    00930       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_ClearRstStatus(Rcc_RstReason rstReason);

/****************************************************************************************************
 * Function:     Rcc_Hal_SetRstTimeoutCnt
 * Description:  Set timeout counter value and enable timeout function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        cnt: Timeout counter value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:       The counter value can be modified at anytime before warm reset signal trigger
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_SetRstTimeoutCnt(uint16 cnt);

/****************************************************************************************************
 * Function:     Rcc_Hal_TrigModuleRst
 * Description:  Trigger selected module reset
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        moduleSel: Selsect module
 * Inout:        None
 * Output:       None
 * Return:       Rcc_ErrorFlag: the status of module reset
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/06/08    00976       Create
 ****************************************************************************************************/
extern Rcc_ErrorFlag Rcc_Hal_TrigModuleRst(Rcc_ModuleRst moduleSel);

/****************************************************************************************************
 * Function:     Rcc_Hal_SetShutdownFlag
 * Description:  Set CPU SHUTDOWN FLAG
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        bitFlag: TURE:set CPU SHUTDOWN FLAG, FALSE: Clear CPU SHUTDOWN FLAG
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                   TRUE:  Register read back check correct
 *                   FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/10/29    00930       Create
 ****************************************************************************************************/
extern boolean Rcc_Hal_SetShutdownFlag(boolean bitFlag);

/* #Violation: rcc_hal_h_REF_5 */
#define RCC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: rcc_hal_h_REF_6 */
#include "Rcc_MemMap.h"

#endif /* RCC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

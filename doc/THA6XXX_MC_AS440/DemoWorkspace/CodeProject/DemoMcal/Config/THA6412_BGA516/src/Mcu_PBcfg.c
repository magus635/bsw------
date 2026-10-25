/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Mcu_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : RCC PWRC
*
*   brief                 : This file contains all configurations of Mcu Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Mcu_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#Mcu_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*#Mcu_PBcfg_c_REF_4:MISRAC2012-Rule-11.4; 
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#Mcu_PBcfg_c_REF_5:MISRAC2012-Rule-10.5; 
* Justification: Necessary type casting to reduce code complexity; Code review ensure the safety of the casting.
*
*#Mcu_PBcfg_c_REF_6:CWE-547; 
* Justification: The Tresos-generated code does not use symbolic constants for buffer size 
* substitution.
*
*
*/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcu_Cfg.h"
#include "Mcu.h"

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
#include "gtm.h"
#include "gtm_pwm_hal.h"
/* #Violation: Mcu_PBcfg_c_REF_2 */
#define MCU_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Mcu_PBcfg_c_REF_1*/
#include "Mcu_MemMap.h"
/***************************************************************************************************
*                        Mcu_RamConfiguration Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_RamSettingType Mcu_RamConfiguration[3U] = 
{
    {
        /* pRamSectionBaseAddress*/
        /* #Violation: Mcu_PBcfg_c_REF_4*/
        (uint32*)0x1000U, 
        /* ulRamSectionSize*/
        (uint32)0x40U,  
        /* ucRamDefaultValue*/
        (uint8)0xaaU,
        /* RamWriteSize*/
        (uint8)0x8U
    },
    {
        /* pRamSectionBaseAddress*/
        /* #Violation: Mcu_PBcfg_c_REF_4*/
        (uint32*)0x200300U, 
        /* ulRamSectionSize*/
        (uint32)0x200U,  
        /* ucRamDefaultValue*/
        (uint8)0x55U,
        /* RamWriteSize*/
        (uint8)0x8U
    },
    {
        /* pRamSectionBaseAddress*/
        /* #Violation: Mcu_PBcfg_c_REF_4*/
        (uint32*)0x82002000U, 
        /* ulRamSectionSize*/
        (uint32)0x2000U,  
        /* ucRamDefaultValue*/
        (uint8)0x7cU,
        /* RamWriteSize*/
        (uint8)0x8U
    },
};

/***************************************************************************************************
*                        Mcu_PBClockSysPllConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PllCfgType Mcu_PBClockSysPllConfigData[1U] =
{
    {
        /*Rcc_PllClockSource*/
        RCC_PLLCLOCKSOURCE_HSE,
        /*Rcc_PllMode*/
        RCC_PLLMODE_INTEGER,
        /*RefDiv*/
        2U,
        /* uint8 PostDiv1 */
        1U,
        /* uint8 PostDiv2 */
        1U, 
        /*postDiv3 reserve for tha6104*/
        0U,     
        /* uint32 FBDiv */
        80U,
        /* uint32 FRAC */                 
        0U           
    },
};

/***************************************************************************************************
*                        Mcu_PBClockPerPllConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PllCfgType Mcu_PBClockPerPllConfigData[1U] =
{
    {
        /*Rcc_PllClockSource*/
        RCC_PLLCLOCKSOURCE_HSE,
        /*Rcc_PllMode*/
        RCC_PLLMODE_INTEGER,
        /*RefDiv*/
        2U,
        /* uint8 PostDiv1 */
        1U,
        /* uint8 PostDiv2 */
        1U, 
        /*postDiv3 reserve for tha6104*/
        0U, 
        /* uint32 FBDiv */
        80U,
        /* uint32 FRAC */                 
        0U
    },
};

/***************************************************************************************************
*                        Mcu_PBClockSysConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_SysClkType Mcu_PBClockSysConfigData[1U] =
{
    {
        /* Mcu_SYSClockSrcType */
        RCC_CPUCLOCKSOURCE_SYSPLL,
        /* CpuClkDiv */
        0U,
        /* SysClkDiv */
        0U,
        /* AxiDiv */
        1U,     
        /* AHBDiv */
        3U,
    },
};

/***************************************************************************************************
*                        Mcu_PBClockGtmConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockGtmConfigData[1U] =
{
    {
        RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
        0U       /* ClkDiv */
    },
};

/***************************************************************************************************
*                        Mcu_PBClockSarAdcConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockSarAdcConfigData[1U] =
{
    {
        RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
        0U       /* NOT USE */
    },
};

/***************************************************************************************************
*                        Mcu_PBClockDsadcRdcConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockDsadcRdcConfigData[1U] =
{
    {
        RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
        /*Rdcdiv:19U   , dsadcDiv: 39U */
        4903U       /* rdcDiv<<8 + dsadcDiv */
    },
};

/***************************************************************************************************
*                        Mcu_PBClockMscConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockMscConfigData[1U] =
{
    {
        RCC_MODULECLOCKSOURCE_HSI,    /* Msc ClkSrc */
        0U                                                           /* ClkDiv */
    },
};
/***************************************************************************************************
*                        Mcu_PBClockEspiConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockEspiConfigData[1U] =
{
    {
        RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
        4U       /* ClkDiv */
    },
};

/***************************************************************************************************
*                        Mcu_PBClockWdtConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockWdtConfigData[1U] =
{
    {
        RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
        3U       /* ClkDiv */
    },
};

/***************************************************************************************************
*                        Mcu_PBClockBaseTimerConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_BaseTimerClkType Mcu_PBClockBaseTimerConfigData[1U] =
{
    {
        {
            /*BaseTimer0*/
            {
                RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
                199U       /* ClkDiv */
            },
            /*BaseTimer1*/
            {
                RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
                199U       /* ClkDiv */
            },
            /*BaseTimer2*/
            {
                RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
                199U       /* ClkDiv */
            },
            /*BaseTimer3*/
            {
                RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
                199U       /* ClkDiv */
            },
            /*BaseTimer4*/
            {
                RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
                199U       /* ClkDiv */
            },
            /*BaseTimer5*/
            {
                RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
                19999U       /* ClkDiv */
            },
        },        
    },
};

/***************************************************************************************************
*                        Mcu_PBClockCanConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_PerClkType Mcu_PBClockCanConfigData[1U] =
{
    {
        RCC_MODULECLOCKSOURCE_PERPLL,    /* PLL_Clk_Src ClkSrc */
        9U       /* ClkDiv */
    },
};

/***************************************************************************************************
*                        Mcu_PBClockDmaConfigData Structure Description
****************************************************************************************************/
/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_DMAClkType Mcu_PBClockDmaConfigData[1U] =
{
    {
        TRUE,    /* DMA0CkEn */
        TRUE,    /* DMA1CkEn */
        TRUE,    /* DMA2CkEn */
        TRUE    /* DMA3CkEn */
    },
};

/***************************************************************************************************
*                        Mcu_ClockMonitorConfig Structure Description
****************************************************************************************************/
static const Mcu_MonitorClkType Mcu_MonitorClkCfg[]=
{
    {
        /*syspll clock monitor*/
        {
            RCC_CLOCK_FREQMON_SYSPLL,
            /* #Violation: Mcu_PBcfg_c_REF_5 */
            (Rcc_ClockAliveMonDiv)7U,
            114U,
            132U,
        },
        /*Perpll clock monitor*/
        {
            RCC_CLOCK_FREQMON_PERPLL,
            /* #Violation: Mcu_PBcfg_c_REF_5 */
            (Rcc_ClockAliveMonDiv)7U,
            114U,
            132U,
        },
        /*syspll clock monitor*/
        {
            RCC_CLOCK_FREQMON_CLUSTER0CPU,
            /* #Violation: Mcu_PBcfg_c_REF_5 */
            (Rcc_ClockAliveMonDiv)7U,
            114U,
            132U,
        },        
    },
};

/***************************************************************************************************
*                        Mcu_ClockConfig Structure Description
****************************************************************************************************/
static const Mcu_ClockConfigType Mcu_ClockConfig[MCU_NUM_CLOCK_SETTING] =
{        
    {
        &Mcu_PBClockSysPllConfigData[0],
        &Mcu_PBClockPerPllConfigData[0],
        &Mcu_PBClockSysConfigData[0],
        &Mcu_PBClockGtmConfigData[0],
        &Mcu_PBClockMscConfigData[0],
        &Mcu_PBClockEspiConfigData[0],
        NULL_PTR,
        &Mcu_PBClockWdtConfigData[0],
        &Mcu_PBClockCanConfigData[0],
        &Mcu_PBClockSarAdcConfigData[0],
        &Mcu_PBClockDsadcRdcConfigData[0],
        &Mcu_PBClockDmaConfigData[0],
        &Mcu_PBClockBaseTimerConfigData[0],
        400000000U,
        &Mcu_MonitorClkCfg[0],/* do not use*/
    },
};

/***************************************************************************************************
*                        Mcu_CMUConfig Structure Description
****************************************************************************************************/
static const Gtm_ClockConfig Gtm_CMUConfig[] =
{
    {
        /* GTM cluster clock configuration */
        {
            /* #Violation: Mcu_PBcfg_c_REF_5*/
            (Gtm_Cluster_Clk)1U,/* Enable / disable GTM cluster 0 clock */
            /* #Violation: Mcu_PBcfg_c_REF_5*/
            (Gtm_Cluster_Clk)1U,/* Enable / disable GTM cluster 1 clock */
            /* #Violation: Mcu_PBcfg_c_REF_5*/
            (Gtm_Cluster_Clk)1U,/* Enable / disable GTM cluster 2 clock */
            /* #Violation: Mcu_PBcfg_c_REF_5*/
            (Gtm_Cluster_Clk)1U,/* Enable / disable GTM cluster 3 clock */
            /* #Violation: Mcu_PBcfg_c_REF_5*/
            (Gtm_Cluster_Clk)1U,/* Enable / disable GTM cluster 4 clock */
            /* #Violation: Mcu_PBcfg_c_REF_5*/
            (Gtm_Cluster_Clk)1U,/* Enable / disable GTM cluster 5 clock */
            /* #Violation: Mcu_PBcfg_c_REF_5*/
            (Gtm_Cluster_Clk)1U,/* Enable / disable GTM cluster 6 clock */
            /* #Violation: Mcu_PBcfg_c_REF_5*/
            (Gtm_Cluster_Clk)1U,/* Enable / disable GTM cluster 7 clock */
        },
        /* CMU global clock configuration */
        {
            10U, /* The numerator for CMU global clock resolution generator */
            1U, /* The denominator for CMU global clock resolution generator */
        },
        /* CMU external clock configuration */
        {
            /* The configuration of the external clock 0 */
            {
                1U, /* The numerator for the external clock resolution generator */
                1U, /* The denominator for the external clock resolution generator */
                FALSE /* Clock enable control */
            },
            /* The configuration of the external clock 1 */
            {
                10000, /* The numerator for the external clock resolution generator */
                1, /* The denominator for the external clock resolution generator */
                TRUE /* Clock enable control */
            },
            /* The configuration of the external clock 2 */
            {
                1U, /* The numerator for the external clock resolution generator */
                1U, /* The denominator for the external clock resolution generator */
                FALSE /* Clock enable control */
            }
        },
        /* CMU configurable clock configuration */
        {
        {
            1U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            TRUE /*CmuClock 0 enable control */
        },
        {
            19U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            TRUE /*CmuClock 1 enable control */
        },
        {
            0U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            FALSE /*CmuClock 2 enable control */
        },
        {
            0U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            FALSE /*CmuClock 3 enable control */
        },
        {
            0U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            FALSE /*CmuClock 4 enable control */
        },
        {
            19U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            TRUE /*CmuClock 5 enable control */
        },
        {
            0U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            FALSE /*CmuClock 6 enable control */
        },
        {
            0U, /* Count value for the clock divider */
            GTM_CMU_CLK_SRC_GCLK, /* Input selection for Clock Resolution Generator */
            FALSE /*CmuClock 7 enable control */
        },
        },
        /* CMU fixed clock configuration */
        {
            GTM_CMU_CLK5, /* Input selection for CMU fixed clock */
            TRUE /*fixed enable control */
        }
    }
};

/***************************************************************************************************
*                        Mcu_TBUConfig Structure Description
****************************************************************************************************/
/* The configuration of the TBU channel 0 */
static const Gtm_Tbu_Channel0 Tbu_Channel0=
{
    /* Free timer offset value */
    0U,
    /* Free timer clock source */
    GTM_CMU_CLK_1,
    /* Count value alignment */
    GTM_TBU_TS0_BIT_LOWER,
    /* Enable / disable free timer */
    TRUE
};
static const Gtm_Tbu_Channel12 Tbu_Channel1=
{
    /* Free timer offset value */
    0U,
    /* Free timer clock source */
    GTM_CMU_CLK_1,
    /* Counting mode */
    GTM_TBU_MODE_FREERUNNING,
    /* Enable / disable free timer */
    TRUE
};


/* #Violation: Mcu_PBcfg_c_REF_6 */
static const Mcu_TBUConfigType Mcu_TBUConfig[1U] =
{
    {    
        /* The configuration of the TBU channel 0 */
        &Tbu_Channel0,
        /* The configuration of the TBU channel 1 */
        &Tbu_Channel1,
        /* The configuration of the TBU channel 2 */
        NULL_PTR,
    }
};

/***************************************************************************************************
*                        Mcu_GTMWrapperConfig Structure Description
****************************************************************************************************/

static const Mcu_TimConfigType Mcu_TimConfig[10] =
{
    /*TIM Id, Tim Channel Id, SelNum */
    {GTM_TIM_INDEX_0,GTM_TIM_CH_INDEX_0,GTM_CHXSEL_1 },
    {GTM_TIM_INDEX_0,GTM_TIM_CH_INDEX_1,GTM_CHXSEL_3 },
    {GTM_TIM_INDEX_0,GTM_TIM_CH_INDEX_2,GTM_CHXSEL_3 },
    {GTM_TIM_INDEX_0,GTM_TIM_CH_INDEX_3,GTM_CHXSEL_3 },
    {GTM_TIM_INDEX_0,GTM_TIM_CH_INDEX_4,GTM_CHXSEL_2 },
    {GTM_TIM_INDEX_0,GTM_TIM_CH_INDEX_5,GTM_CHXSEL_2 },
    {GTM_TIM_INDEX_0,GTM_TIM_CH_INDEX_6,GTM_CHXSEL_14 },
    {GTM_TIM_INDEX_0,GTM_TIM_CH_INDEX_7,GTM_CHXSEL_14 },
    {GTM_TIM_INDEX_2,GTM_TIM_CH_INDEX_0,GTM_CHXSEL_1 },
    {GTM_TIM_INDEX_2,GTM_TIM_CH_INDEX_1,GTM_CHXSEL_2 },
};

static const Mcu_DsadcConfigType Mcu_DsadcConfig[2] =
{
    /*DSADC Id, Dsadc Channel Id, SelNum */
    {0U, 6U, GTM_CHXSEL_2 },
    {0U, 7U, GTM_CHXSEL_2 },
};

static const Mcu_GtmToDsadcConfigType Mcu_GtmToDsadcConfig[1] =
{
    /*GtmToDsadcTrigGroup Id, Dsadc Channel Id, SelNum */
    {0U, 0U, GTM_CHXSEL_10 },
};

static const Mcu_ToutConfigType Mcu_ToutConfig[22] =
{
    /*SelNum , ToutNum*/
    {GTM_TOUTSEL_0,0x11U},
    {GTM_TOUTSEL_0,0x1dU},
    {GTM_TOUTSEL_0,0x9U},
    {GTM_TOUTSEL_1,0xaU},
    {GTM_TOUTSEL_1,0x16U},
    {GTM_TOUTSEL_1,0x18U},
    {GTM_TOUTSEL_1,0x19U},
    {GTM_TOUTSEL_4,0x7fU},
    {GTM_TOUTSEL_1,0x24U},
    {GTM_TOUTSEL_1,0x60U},
    {GTM_TOUTSEL_2,0x0U},
    {GTM_TOUTSEL_2,0x1U},
    {GTM_TOUTSEL_2,0x2U},
    {GTM_TOUTSEL_2,0x3U},
    {GTM_TOUTSEL_2,0xeU},
    {GTM_TOUTSEL_2,0xfU},
    {GTM_TOUTSEL_2,0x6U},
    {GTM_TOUTSEL_2,0x7U},
    {GTM_TOUTSEL_2,0x6dU},
    {GTM_TOUTSEL_2,0x50U},
    {GTM_TOUTSEL_3,0x26U},
    {GTM_TOUTSEL_3,0x27U},

};

/***************************************************************************************************
*                        Mcu_AdcConfigType Structure Description
****************************************************************************************************/
static const Mcu_AdcConfigType Mcu_AdcConfig[3] =
{
    /*ADC id,    Trigger Group Id, SelValue */
    
    
    {GTM_TRIG_ADCGROUP_0,GTM_TRIG_ADCTRIG_0,GTM_CHXSEL_12},
    {GTM_TRIG_ADCGROUP_3,GTM_TRIG_ADCTRIG_0,GTM_CHXSEL_14},
    {GTM_TRIG_ADCGROUP_8,GTM_TRIG_ADCTRIG_1,GTM_CHXSEL_8},
};

/* GTM trigger source configuration parameters */
static const Mcu_GtmTriggerConfigType GtmTriggerConfig[3] = 
{
    {
        /* GtmOutputSignal0 */
        {
            /* Hardware Channel Type */
            (uint8)GTM_OUTPUT_MODULE_ATOM,
            /* Hardware Timer Module Index */
            1U,
            /* Group index, only used for TIO module */
            0U,
            /* Hardware Channel Index */
            1U
        },
        {
            /* Clock Source */
            GTM_PWM_CLOCK_CMUCLK1,
            /* Period */
            20000U,
            /* Duty Cycle */
            10000U,
            /* Initial Counter Shift */
            0U,
            /* reserve*/
            {
            0U,
            0U,
            0U,
            },
            /* Channel Counter Reset Source */
            GTM_PWM_RESETEVENT_ONCM0,
            /* Signal Level */
            GTM_SIGNALSTATE_LOW,
            {
                /* CCU0 Trigger Interrupt */
                FALSE,
                /* CCU1 Trigger Interrupt */
                FALSE,
                /* Interrupt Mode */
                GTM_IRQMODE_LEVEL
            },
            /* Trigger Output Signal Select */
            GTM_PWM_TRIGOUT_FORWARD,
            /*PWM channel count mode*/
            GTM_PWM_COUNTMODE_UP,
            /* Update Mechanism */
            TRUE,
            /* Channel Control */
            TRUE,
            /* Channel Output Control */
            TRUE,
            /* Update Immediate Control */
            TRUE
        }
    },
    {
        /* GtmOutputSignal1 */
        {
            /* Hardware Channel Type */
            (uint8)GTM_OUTPUT_MODULE_ATOM,
            /* Hardware Timer Module Index */
            3U,
            /* Group index, only used for TIO module */
            0U,
            /* Hardware Channel Index */
            5U
        },
        {
            /* Clock Source */
            GTM_PWM_CLOCK_CMUCLK1,
            /* Period */
            20000U,
            /* Duty Cycle */
            10000U,
            /* Initial Counter Shift */
            0U,
            /* reserve*/
            {
            0U,
            0U,
            0U,
            },
            /* Channel Counter Reset Source */
            GTM_PWM_RESETEVENT_ONCM0,
            /* Signal Level */
            GTM_SIGNALSTATE_LOW,
            {
                /* CCU0 Trigger Interrupt */
                FALSE,
                /* CCU1 Trigger Interrupt */
                FALSE,
                /* Interrupt Mode */
                GTM_IRQMODE_LEVEL
            },
            /* Trigger Output Signal Select */
            GTM_PWM_TRIGOUT_FORWARD,
            /*PWM channel count mode*/
            GTM_PWM_COUNTMODE_UP,
            /* Update Mechanism */
            TRUE,
            /* Channel Control */
            TRUE,
            /* Channel Output Control */
            TRUE,
            /* Update Immediate Control */
            TRUE
        }
    },
    {
        /* GtmOutputSignal2 */
        {
            /* Hardware Channel Type */
            (uint8)GTM_OUTPUT_MODULE_ATOM,
            /* Hardware Timer Module Index */
            1U,
            /* Group index, only used for TIO module */
            0U,
            /* Hardware Channel Index */
            7U
        },
        {
            /* Clock Source */
            GTM_PWM_CLOCK_CMUCLK1,
            /* Period */
            20000U,
            /* Duty Cycle */
            10000U,
            /* Initial Counter Shift */
            0U,
            /* reserve*/
            {
            0U,
            0U,
            0U,
            },
            /* Channel Counter Reset Source */
            GTM_PWM_RESETEVENT_ONCM0,
            /* Signal Level */
            GTM_SIGNALSTATE_LOW,
            {
                /* CCU0 Trigger Interrupt */
                FALSE,
                /* CCU1 Trigger Interrupt */
                FALSE,
                /* Interrupt Mode */
                GTM_IRQMODE_LEVEL
            },
            /* Trigger Output Signal Select */
            GTM_PWM_TRIGOUT_FORWARD,
            /*PWM channel count mode*/
            GTM_PWM_COUNTMODE_UP,
            /* Update Mechanism */
            TRUE,
            /* Channel Control */
            TRUE,
            /* Channel Output Control */
            TRUE,
            /* Update Immediate Control */
            TRUE
        }
    },
};

/***************************************************************************************************
*                        Mcu_GTM_MscTypeConfig Structure Description
****************************************************************************************************/
/***************************************************************************************************
*                        Mcu_GTM_DmaTypeConfig Structure Description
****************************************************************************************************/
static const Mcu_DmaConfigType Mcu_DmaConfig[5] =
{
    /*RegsterOffset, SelValue */
    { GTM_TRIG_DMAL1_MUX_00,3U},
    { GTM_TRIG_DMAL1_MUX_01,6U},
    { GTM_TRIG_DMAL1_MUX_10,15U},
    { GTM_TRIG_DMAL1_MUX_20,10U},
    { GTM_TRIG_DMAL1_MUX_30,18U},
    
};

static const Mcu_DmaL2ConfigType Mcu_DmaL2Config[5] =
{
    /*RegsterOffset,Channel */
    { GTM_TRIG_DMAL1_MUX_00,GTM_TRIG_DMACHANNEL_0},
    { GTM_TRIG_DMAL1_MUX_01,GTM_TRIG_DMACHANNEL_1},
    { GTM_TRIG_DMAL1_MUX_10,GTM_TRIG_DMACHANNEL_2},
    { GTM_TRIG_DMAL1_MUX_20,GTM_TRIG_DMACHANNEL_3},
    { GTM_TRIG_DMAL1_MUX_30,GTM_TRIG_DMACHANNEL_4},
    
};

static const Mcu_GtmWrapperConfigType Mcu_GtmWrapperConfig[1U]=
{
    {
        /* Tim Setting */
        &Mcu_TimConfig[0],
        /* Dsadc Setting */
        &Mcu_DsadcConfig[0],
        /* Tout Setting */
        &Mcu_ToutConfig[0],
        /* Adc Setting */
        &Mcu_AdcConfig[0],
        /* GtmToDsadc Setting */
        &Mcu_GtmToDsadcConfig[0],
        /* Msc Setting */
        NULL_PTR,
        NULL_PTR,
        /* Dma Setting */
        &Mcu_DmaConfig[0],
        &Mcu_DmaL2Config[0],
        10U, /* Num of Tim cfg*/
        2U, /* Num of Dsadc CFG*/
        22U, /* Num of TOUT cfg*/
        3U, /* Num of Adc Cfg*/
        1U, /* Num of Gtm to Dsadc Cfg */
        0U, /* Num of Msc Cfg */
        0U, /* Num of Msc L2 cfg*/
        5U, /* Num of Dma L1 Cfg */
        5U, /* Num of Dma L2 Cfg */
    }
};

/* Reset setting */
static const Mcu_ResetConfigType Mcu_ResetConfig[MCU_RESET_CONFIG_NUM] =
{
    {RCC_RSTSRC_SW,RCC_RSTTYPE_APP},
    {RCC_RSTSRC_ESR0,RCC_RSTTYPE_NONE},
    {RCC_RSTSRC_ESR1,RCC_RSTTYPE_NONE},
    {RCC_RSTSRC_SAC,RCC_RSTTYPE_SYS},
    {RCC_RSTSRC_IWDG,RCC_RSTTYPE_NONE},
    {RCC_RSTSRC_CPU0REQ,RCC_RSTTYPE_NONE},
    {RCC_RSTSRC_CPU1REQ,RCC_RSTTYPE_NONE},
};

/* be used by setmode() */
static const Mcu_ModeConfigType Mcu_ModeConfig[] =
{
    {
        /* Valid mode  */
        1U,
        /* parameter for standby mode */
        NULL_PTR,
        0U
    }
};

/***************************************************************************************************
*                        Mcu_ConfigSet Structure Description
****************************************************************************************************/
const Mcu_ConfigType Mcu_ConfigSet[MCU_CONFIG_COUNT] =
{
    {
        /* ClockSettingPtr */
        &Mcu_ClockConfig[0],
        /* RamSettingPtr; */
        MCU_NUM_RAM_SECTORS,
        &Mcu_RamConfiguration[0],
        /* GTMConfigPtr */
        &Mcu_GtmWrapperConfig[0],
        /* CMUConfigPtr */
        &Gtm_CMUConfig[0],
        /* TBUConfigPtr */
        &Mcu_TBUConfig[0],
        /* GTMtriggerConfigPtr */
        &GtmTriggerConfig[0],
        &Mcu_ResetConfig[0],
        /* ModeConfigPtr */
        &Mcu_ModeConfig[0],
        3U,
    }
};

/* #Violation: Mcu_PBcfg_c_REF_2 */
#define MCU_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Mcu_PBcfg_c_REF_1*/
#include "Mcu_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


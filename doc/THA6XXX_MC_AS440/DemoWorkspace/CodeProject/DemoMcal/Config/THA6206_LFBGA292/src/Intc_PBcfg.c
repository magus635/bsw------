/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Intc_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Intc
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*  Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Intc_PBcfg_c_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Intc_PBcfg_c_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Intc_PBcfg_c_REF_3:MISRAC2012-Dir-1.1;
* Justification:Compiler can handle more than 4095 macro identifiers.
*
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
/* #Violation: Intc_PBcfg_c_REF_3 */
#include "Intc_Irq.h"
#include "Intc.h"
#include "Mcall.h"

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

/* Configuration informations which mapped to Core0 */
/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"

/* Iterrupt(SGI ,PPI and SPI) sources configuration list of Core0 */
static const Intc_IntSrcConfigType
                    Intc_IntSrcConfigSetCore0[INTC_CFG_INTSRC_NUM_CORE0] = 
{
    /* Interrupt source: IntcIntSrcContainer_0 - CPU0_SGI0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_EDGE,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        0U,
        /* Interrupt service handler */
        Intc_Irq_Core0IntSrc0Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - CPU0WDT_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        32U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc32Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - INTC_CPU0SOFTINT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        56U,
        /* Interrupt service handler */
        Intc_Irq_Core0IntSrc56Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SBD_PERCH_TX_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        73U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc73Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_5 - SBD_PERCH_RX_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        77U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc77Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - DMA0_CH_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        95U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc95Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - DMA0_CH_INT2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        97U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc97Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_3 - DMA0_CH_INT3 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        98U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc98Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_4 - DMA0_CH_INT4 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        99U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc99Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - DMA1_CH_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        149U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc149Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - DMA2_CH_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        115U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc115Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_3 - DMA2_CH_INT3 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        118U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc118Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - DMA3_CH_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        129U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc129Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - DMA3_CH_INT1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        130U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc130Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_4 - DFLASH0_FINISH */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        227U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc227Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - BASETIM0_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        246U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc246Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - BASETIM2_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        248U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc248Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - BASETIM4_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        250U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc250Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - BASETIM5_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        251U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc251Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_13 - CAN0_ROUTE4 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        265U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc265Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_16 - CAN0_ROUTE7 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        268U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc268Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SARADC0_G0SR0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        377U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc377Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SARADC0_G0SR1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        378U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc378Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - SARADC0_G0SR2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        379U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc379Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SARADC1_G1SR0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        383U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc383Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SARADC1_G1SR1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        384U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc384Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - SARADC1_G1SR2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        385U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc385Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SARADC3_G3SR0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        395U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc395Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SARADC3_G3SR1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        396U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc396Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - SARADC3_G3SR2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        397U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc397Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SARADC8_G8SR0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        401U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc401Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SARADC8_G8SR1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        402U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc402Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - SARADC8_G8SR2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        403U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc403Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SARADC9_G9SR0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        407U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc407Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SARADC9_G9SR1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        408U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc408Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - SARADC9_G9SR2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        409U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc409Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - DSADC0_SRA */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        439U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc439Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - DSADC0_SRM */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        440U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc440Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - DSADC1_SRA */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        441U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc441Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - DSADC1_SRM */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        442U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc442Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - DSADC2_SRA */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        443U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc443Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - DSADC2_SRM */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        444U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc444Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - ESPI0_RX_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        465U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc465Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - ESPI0_ERR_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        466U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc466Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - ESPI4_RX_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        501U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc501Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - ESPI4_ERR_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        502U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc502Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SENT2_RX_ERROR */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        580U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc580Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SENT2_RX_VALID */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        581U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc581Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SENT3_RX_ERROR */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        584U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc584Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SENT3_RX_VALID */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        585U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc585Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SENT6_RX_ERROR */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        596U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc596Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SENT6_RX_VALID */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        597U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc597Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - ASI2_RX */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        641U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc641Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - ASI2_ERROR */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        643U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc643Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - ASI5_RX */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        656U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc656Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - ASI5_TX */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        657U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc657Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - ASI5_ERROR */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        658U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc658Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_61 - GTM_TIM0_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        748U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc748Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_66 - GTM_TIM0_INT5 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        753U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc753Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_77 - GTM_TIM2_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        764U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc764Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_78 - GTM_TIM2_INT1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        765U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc765Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_85 - GTM_TOM0_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        772U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc772Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_90 - GTM_TOM0_INT5 */
    {
        /* Interrupt priority */
        0U,
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        777U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc777Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_97 - GTM_TOM1_INT4 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        784U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc784Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_109 - GTM_ATOM0_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        796U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc796Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_113 - GTM_ATOM1_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        800U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc800Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_115 - GTM_ATOM1_INT2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        802U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc802Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_132 - GTM_TIO1_INT7 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        819U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc819Entry,
    }
};

/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"

/* Configuration informations which mapped to Core1 */
/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"

/* Iterrupt(SGI ,PPI and SPI) sources configuration list of Core1 */
static const Intc_IntSrcConfigType
                    Intc_IntSrcConfigSetCore1[INTC_CFG_INTSRC_NUM_CORE1] = 
{
    /* Interrupt source: IntcIntSrcContainer_0 - CPU1_SGI0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_EDGE,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        0U,
        /* Interrupt service handler */
        Intc_Irq_Core1IntSrc0Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - CPU1WDT_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        34U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc34Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - INTC_CPU1SOFTINT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        89U,
        /* Interrupt service handler */
        Intc_Irq_Core1IntSrc89Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - DMA0_CH_INT1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        96U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc96Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - BASETIM1_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        247U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc247Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - BASETIM3_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        249U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc249Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SARADC2_G2SR0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        389U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc389Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SARADC2_G2SR1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        390U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc390Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - SARADC2_G2SR2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        391U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc391Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - ESPI2_RX_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        483U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc483Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - ESPI2_ERR_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        484U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc484Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - ESPI8_ERR_INT */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        538U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc538Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - ASI3_RX */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        646U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc646Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_2 - ASI3_ERROR */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Not enable when installing, manually enable using API Intc_EnableInterrupt() */
        FALSE,
        /* Unique interrupt ID */
        648U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc648Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_62 - GTM_TIM0_INT1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        749U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc749Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_63 - GTM_TIM0_INT2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        750U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc750Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_64 - GTM_TIM0_INT3 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        751U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc751Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_65 - GTM_TIM0_INT4 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        752U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc752Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_86 - GTM_TOM0_INT1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        773U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc773Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_111 - GTM_ATOM0_INT2 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        798U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc798Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_114 - GTM_ATOM1_INT1 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        801U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc801Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_133 - GTM_TIO2_INT0 */
    {
        /* Interrupt priority */
        0U,  /* Default to 0 */
        /* Allocated to IRQ(Group1) */
        INTC_INTERRUPTGROUP_IRQ,
        /* Interrupt trigger method */
        INTC_TRIGGERMETHOD_LEVEL,
        /* Enable when installing */
        TRUE,
        /* Unique interrupt ID */
        820U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc820Entry,
    }
};

/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"

/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"

/* Intc configuration set parameters */
const Intc_ConfigType Intc_ConfigSet[INTC_CONFIGSET_CNT] =
{
    {
        {
            {
                /* Total interrupt in core0 */
                INTC_CFG_INTSRC_NUM_CORE0,
                /* Interrupt Configuration set */
                &Intc_IntSrcConfigSetCore0[0]
            },
            {
                /* Total interrupt in core1 */
                INTC_CFG_INTSRC_NUM_CORE1,
                /* Interrupt Configuration set */
                &Intc_IntSrcConfigSetCore1[0]
            }
        }
    }
};

/* #Violation: Intc_PBcfg_c_REF_1 */
#define INTC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Intc_PBcfg_c_REF_2 */
#include "Intc_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

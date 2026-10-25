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
    /* Interrupt source: IntcIntSrcContainer_3 - SBD_PERCH_RX_INT0 */
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
    /* Interrupt source: IntcIntSrcContainer_2 - DMA2_CH_INT2 */
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
        117U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc117Entry,
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
    /* Interrupt source: IntcIntSrcContainer_4 - DMA2_CH_INT4 */
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
        119U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc119Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_5 - DMA2_CH_INT5 */
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
        120U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc120Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_6 - DMA2_CH_INT6 */
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
        121U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc121Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_7 - DMA2_CH_INT7 */
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
        122U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc122Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_8 - DMA2_CH_INT8 */
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
        123U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc123Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_9 - DMA2_CH_INT9 */
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
        124U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc124Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_12 - DMA2_CH_INT12 */
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
        127U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc127Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_13 - DMA2_CH_INT13 */
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
        128U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc128Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_14 - DMA2_CH_INT14 */
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
        217U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc217Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_15 - DMA2_CH_INT15 */
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
        218U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc218Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_16 - DMA2_CH_INT16 */
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
        219U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc219Entry,
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
    /* Interrupt source: IntcIntSrcContainer_0 - SENT4_RX_ERROR */
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
        588U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc588Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SENT4_RX_VALID */
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
        589U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc589Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_0 - SENT5_RX_ERROR */
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
        592U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc592Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_1 - SENT5_RX_VALID */
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
        593U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc593Entry,
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
    /* Interrupt source: IntcIntSrcContainer_17 - GTM_TIM0_INT0 */
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
    /* Interrupt source: IntcIntSrcContainer_22 - GTM_TIM0_INT5 */
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
    /* Interrupt source: IntcIntSrcContainer_24 - GTM_TIM0_INT7 */
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
        755U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc755Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_25 - GTM_TIM1_INT0 */
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
        756U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc756Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_33 - GTM_TOM0_INT0 */
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
    /* Interrupt source: IntcIntSrcContainer_38 - GTM_TOM0_INT5 */
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
        777U,
        /* Interrupt service handler */
        Intc_Irq_IntSrc777Entry,
    },
    /* Interrupt source: IntcIntSrcContainer_45 - GTM_TOM1_INT4 */
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
    /* Interrupt source: IntcIntSrcContainer_49 - GTM_ATOM0_INT0 */
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
    /* Interrupt source: IntcIntSrcContainer_60 - GTM_TIO1_INT7 */
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
                /* No interrupt configured in core1 */
                NULL_PTR
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

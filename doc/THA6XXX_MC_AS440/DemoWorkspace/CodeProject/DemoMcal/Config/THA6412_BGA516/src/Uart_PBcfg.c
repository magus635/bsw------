/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Uart_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Uart
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Uart_PBcfg_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Uart_PBcfg_c_REF_2:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#Uart_PBcfg_c_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#include "Uart.h"
#include "Uart_Cfg.h"
#include "tha6_cfg.h"
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
**                          External Function Declarations                                         **
****************************************************************************************************/
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/* #Violation: Uart_PBcfg_c_REF_3 */
#define UART_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Uart_PBcfg_c_REF_1 */
#include "Uart_MemMap.h"

static const Uart_HwUnitConfigType Uart_HWUnitConfigSetCore0[UART_MAX_CHANNEL_TO_CORE0] =
{
    /* ASI0 used by DebugChannel*/
    {
        /* Baud-rate ratio: Clock[2.0E8]/baud-rate[115200]/RegisterValue[108.50694444444444] */
        /* Integer Baud rate */
        108U,
        /* Fractional Baud rate */
        8U,
        /* Enable/disable RX/TX/Error interrupt */
        ASI_UART_NO_INT,
        /* The number of over sample */
        ASI_UART_SAMPLENUM_16,
        /* The number of data bit */
        ASI_UART_DATATBITS_8,
        /* The number of stop bit */
        ASI_UART_STOPBITS_1,
        /* Parity control: no parity, even, odd, logic 0, logic 1 */
        ASI_UART_PARITY_NONE,
        /* Buffer works in  Buffer mode and disable DMA  */
        FALSE,
        /* Enable/disable RX buffer lock mode */
        FALSE
    }
};

/* Uart channel configuration parameters of Core0 */
static const Uart_ChannelConfigType Uart_ChannelConfigSetCore0[UART_MAX_CHANNEL_TO_CORE0] =
{
    {
        /* Uart Channel ID (Name: DebugChannel) */
        0U,
        /* ASI HwUnit(ASI0) of assigned to Uart channel (Name: DebugChannel) */
        0U,
        /* Uart channel transmission data width (byte) */
        1U,
        /* Receive interrupt handling function */
        NULL_PTR,
        /* Transmit interrupt handling function */
        NULL_PTR,
        /* Error interrupt handling function */
        NULL_PTR,
        /* The configuration information structure of the hardware unit(ASI0) (Name: DebugChannel) */
        &Uart_HWUnitConfigSetCore0[0]
    }
};

/* Uart channel number and configuration information in Core0 */
static const Uart_CoreConfigType Uart_ConfigSetCore0 =
{
    /* Maximum number of the channels allocated to the core0 */
    UART_MAX_CHANNEL_TO_CORE0,
    /* Uart configuration information of core0 */
    &Uart_ChannelConfigSetCore0[0]
};
/* #Violation: Uart_PBcfg_c_REF_3 */
#define UART_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Uart_PBcfg_c_REF_1 */
#include "Uart_MemMap.h"

/* #Violation: Uart_PBcfg_c_REF_3 */
#define UART_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Uart_PBcfg_c_REF_1 */
#include "Uart_MemMap.h"

/*
This array is used for mapping Uart Channel to the Core.
Array index is Uart channel -> array member is index of Corex[x=0~4]
*/
static const uint8 Uart_ChannelToCoreMap[UART_TOTAL_CFG_CHANNEL_NUM] =
{
    /* DebugChannel configuration information is assigned to index0 of Core0 */
    0U
};

/*
This array is used for mapping UART hardware unit to the Uart channel.
Array index is hardware unit -> array member is Uart channel
*/
static const uint8 Uart_HwToChannel[UART_MAX_HWUNIT_COUNT] =
{
    /* ASI0 assigned to DebugChannel in Core0 */
    0U,
    /* ASI1 not assigned */
    0xFFU,
    /* ASI2 not assigned */
    0xFFU,
    /* ASI3 not assigned */
    0xFFU,
    /* ASI4 not assigned */
    0xFFU,
    /* ASI5 not assigned */
    0xFFU,
    /* ASI6 not assigned */
    0xFFU,
    /* ASI7 not assigned */
    0xFFU,
    /* ASI8 not assigned */
    0xFFU,
    /* ASI9 not assigned */
    0xFFU,
    /* ASI10 not assigned */
    0xFFU,
    /* ASI11 not assigned */
    0xFFU,
    /* ASI12 not assigned */
    0xFFU,
    /* ASI13 not assigned */
    0xFFU,
    /* ASI14 not assigned */
    0xFFU,
    /* ASI15 not assigned */
    0xFFU,
    /* ASI16 not assigned */
    0xFFU,
    /* ASI17 not assigned */
    0xFFU,
    /* ASI18 not assigned */
    0xFFU,
    /* ASI19 not assigned */
    0xFFU,
    /* ASI20 not assigned */
    0xFFU,
    /* ASI21 not assigned */
    0xFFU,
    /* ASI22 not assigned */
    0xFFU,
    /* ASI23 not assigned */
    0xFFU
};

/* Uart available ASI hardware unit mapping table.*/
static ASI_MODULE *const Uart_HwUnitMap[UART_MAX_HWUNIT_COUNT] =
{
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI0,        /* ASI0 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI1,        /* ASI1 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI2,        /* ASI2 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI3,        /* ASI3 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI4,        /* ASI4 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI5,        /* ASI5 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI6,        /* ASI6 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI7,        /* ASI7 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI8,        /* ASI8 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI9,        /* ASI9 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI10,        /* ASI10 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI11,        /* ASI11 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI12,        /* ASI12 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI13,        /* ASI13 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI14,        /* ASI14 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI15,        /* ASI15 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI16,        /* ASI16 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI17,        /* ASI17 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI18,        /* ASI18 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI19,        /* ASI19 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI20,        /* ASI20 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI21,        /* ASI21 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI22,        /* ASI22 is available*/
    /* #Violation: Uart_PBcfg_c_REF_2 */
    ASI23         /* ASI23 is available*/
};

/* Configuration parameters */
const Uart_ConfigType Uart_ConfigSet[UART_CONFIG_COUNT] =
{
    {
        {
            /* Uart Channels configuration of Core0 */
            &Uart_ConfigSetCore0,
            /* Uart Channels configuration of Core1 */
            NULL_PTR,
            /* Uart Channels configuration of Core2 */
            NULL_PTR,
            /* Uart Channels configuration of Core3 */
            NULL_PTR
        },
        /* Table for relationship between channel ID in specified core and UART channel ID */
        &Uart_ChannelToCoreMap[0],
        /* Table for relationship between hardware unit and logical UART channel ID */
        &Uart_HwToChannel[0],
        /* Uart available ASI hardware unit mapping table.*/
        &Uart_HwUnitMap[0]
    }
};
/* #Violation: Uart_PBcfg_c_REF_3 */
#define UART_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Uart_PBcfg_c_REF_1 */
#include "Uart_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

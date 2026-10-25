/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Lin_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : ASI
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
* 
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Lin_PBcfg_c_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the 
* driver must be placed.
*
*#Lin_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#include "Lin_Cfg.h"
#include "Lin_GeneralTypes.h"
#include "Lin.h"

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/* Lin Channel(s) configuration informations which mapped to Core0 */
/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"

/* Lin HwUnit configuration parameters of Core0 */
static const Lin_HwUnitConfigType Lin_HWUnitConfigSetCore0[LIN_MAX_CHANNEL_TO_CORE0] =
{
    {
        /* Master or Slave mode */
        ASI_LIN_MODE_MASTER,
        /* Frame break length */
        ASI_LIN_BREAKLEN_13BIT,
        /* Baud-rate ratio: Clock[2.0E8]/baud-rate[19200]/RegisterValue[0x28b0] */
        /* Integer Baud rate = RegisterValue / 16 */
        651U,
        /* Fractional Baud rate = RegisterValue % 16 */
        0U,
        /* Enable/disable Error/RX/AutoWakeup interrupt */
        (ASI_LIN_DATA_RX_COMPLETED_INT | ASI_LIN_WAKEUP_INT | ASI_LIN_ALL_ERROR_INTS),
        /* Frame header(Max:0x2F) or response Timeout Value(Max:0x0F) */
        0xE,
        /* ID filter configuration, only for slave node */
        NULL_PTR,
        /* Enable auto wake-up */
        TRUE,
        /* Enable or disable master RX with DMA */
        FALSE,
        /* Enable/disable RX buffer lock mode */
        FALSE
    },
    {
        /* Master or Slave mode */
        ASI_LIN_MODE_SLAVE,
        /* Frame break length */
        ASI_LIN_BREAKLEN_13BIT,
        /* Baud-rate ratio: Clock[2.0E8]/baud-rate[19200]/RegisterValue[0x28b0] */
        /* Integer Baud rate = RegisterValue / 16 */
        651U,
        /* Fractional Baud rate = RegisterValue % 16 */
        0U,
        /* Enable/disable Error/RX/AutoWakeup interrupt */
        (ASI_LIN_DATA_RX_COMPLETED_INT | ASI_LIN_WAKEUP_INT | ASI_LIN_ALL_ERROR_INTS | ASI_LIN_DATA_TX_COMPLETED_INT | ASI_LIN_HEADER_RX_INT),
        /* Frame header(Max:0x2F) or response Timeout Value(Max:0x0F) */
        0x2F,
        /* ID filter configuration, only for slave node */
        NULL_PTR,
        /* Enable auto wake-up */
        TRUE,
        /* Enable or disable master RX with DMA */
        FALSE,
        /* Enable/disable RX buffer lock mode */
        FALSE
    }
};

/* Lin channel configuration parameters of Core0 */
static const Lin_ChannelConfigType Lin_ChannelConfigSetCore0[LIN_MAX_CHANNEL_TO_CORE0] =
{
    {
        /* Lin Channel ID */
        0U,
        /* ASI HwUnit(ASI2) of assigned to Lin channel */
        2U,
        /* Is wake-up supported by the LIN channel */
        FALSE,
        /* This parameter contains a reference to the Wake-up Source for this controller
        * as defined in the ECU State Manager.*/
        0U,
        /* The configuration information structure of the hardware unit(ASI2) corresponding to the Channel0 */
        &Lin_HWUnitConfigSetCore0[0]
    },
    {
        /* Lin Channel ID */
        2U,
        /* ASI HwUnit(ASI5) of assigned to Lin channel */
        5U,
        /* Is wake-up supported by the LIN channel */
        FALSE,
        /* This parameter contains a reference to the Wake-up Source for this controller
        * as defined in the ECU State Manager.*/
        0U,
        /* The configuration information structure of the hardware unit(ASI5) corresponding to the Channel2 */
        &Lin_HWUnitConfigSetCore0[1]
    }
};

/* Lin channel number and configuration information in Core0 */
static const Lin_CoreConfigType Lin_ConfigSetCore0 =
{
    /* Maximum number of the channels allocated to the core0 */
    LIN_MAX_CHANNEL_TO_CORE0,
    /* Lin configuration information of core0 */
    &Lin_ChannelConfigSetCore0[0]
};
/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"
/* Lin Channel(s) configuration informations which mapped to Core1 */
/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"

/* Lin HwUnit configuration parameters of Core1 */
static const Lin_HwUnitConfigType Lin_HWUnitConfigSetCore1[LIN_MAX_CHANNEL_TO_CORE1] =
{
    {
        /* Master or Slave mode */
        ASI_LIN_MODE_MASTER,
        /* Frame break length */
        ASI_LIN_BREAKLEN_13BIT,
        /* Baud-rate ratio: Clock[2.0E8]/baud-rate[19200]/RegisterValue[0x28b0] */
        /* Integer Baud rate = RegisterValue / 16 */
        651U,
        /* Fractional Baud rate = RegisterValue % 16 */
        0U,
        /* Enable/disable Error/RX/AutoWakeup interrupt */
        (ASI_LIN_DATA_RX_COMPLETED_INT | ASI_LIN_WAKEUP_INT | ASI_LIN_ALL_ERROR_INTS),
        /* Frame header(Max:0x2F) or response Timeout Value(Max:0x0F) */
        0xE,
        /* ID filter configuration, only for slave node */
        NULL_PTR,
        /* Enable auto wake-up */
        TRUE,
        /* Enable or disable master RX with DMA */
        FALSE,
        /* Enable/disable RX buffer lock mode */
        FALSE
    }
};

/* Lin channel configuration parameters of Core1 */
static const Lin_ChannelConfigType Lin_ChannelConfigSetCore1[LIN_MAX_CHANNEL_TO_CORE1] =
{
    {
        /* Lin Channel ID */
        1U,
        /* ASI HwUnit(ASI3) of assigned to Lin channel */
        3U,
        /* Is wake-up supported by the LIN channel */
        FALSE,
        /* This parameter contains a reference to the Wake-up Source for this controller
        * as defined in the ECU State Manager.*/
        0U,
        /* The configuration information structure of the hardware unit(ASI3) corresponding to the Channel1 */
        &Lin_HWUnitConfigSetCore1[0]
    }
};

/* Lin channel number and configuration information in Core1 */
static const Lin_CoreConfigType Lin_ConfigSetCore1 =
{
    /* Maximum number of the channels allocated to the core1 */
    LIN_MAX_CHANNEL_TO_CORE1,
    /* Lin configuration information of core1 */
    &Lin_ChannelConfigSetCore1[0]
};
/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"
/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"
/* Shared configuration const data for all cores. */

/* 
This array is used for mapping Lin Channel to the Core. 
Array index is Lin channel -> array member is index of Lin_ChannelConfigSetCorex[x=0~4]
*/
static const uint8 Lin_ChannelToCoreMap[LIN_TOTAL_CFG_CHANNEL_NUM] =
{
    /* Lin_TestChannel_0 configuration information is assigned to index0 of Core0 */
    0U,
    /* Lin_TestChannel_1 configuration information is assigned to index0 of Core1 */
    0U,
    /* Lin_TestSlaveChannel_0 configuration information is assigned to index1 of Core0 */
    1U
};

/* Relationship between ASI hardware unit and LIN channel */
/* 
This array is used for mapping LIN hardware unit to the Lin channel. 
Array index is hardware unit -> array member is Lin channel
*/
static const uint8 Lin_HwToChannel[LIN_MAX_HWUNIT_COUNT] =
{
    /* ASI0 not assigned */
    0xFFU,
    /* ASI1 not assigned */
    0xFFU,
    /* ASI2 assigned to LinChannel_0 in Core0 */
    0U,
    /* ASI3 assigned to LinChannel_1 in Core1 */
    1U,
    /* ASI4 not assigned */
    0xFFU,
    /* ASI5 assigned to LinChannel_2 in Core0 */
    2U,
    /* ASI6 not assigned */
    0xFFU,
    /* ASI7 not assigned */
    0xFFU
};

/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"

/* Configuration parameters */
const Lin_ConfigType Lin_ConfigSet[LIN_CONFIG_COUNT] =  
{
    {
        {
            /* LIN channels configuration of core0 */
            &Lin_ConfigSetCore0,
            /* LIN channels configuration of core1 */
            &Lin_ConfigSetCore1
        },
        /* Table for relationship between channel ID in specified core and LIN channel ID */
        &Lin_ChannelToCoreMap[0],
        /* Table for relationship between hardware unit and logical LIN channel ID */
        &Lin_HwToChannel[0]
    }
};

/* #Violation: Lin_PBcfg_c_REF_2 */
#define LIN_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Lin_PBcfg_c_REF_1 */ 
#include "Lin_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

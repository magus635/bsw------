/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : I2c_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : I2C
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
* 
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright /(c) 2021,Beijing Tongxin Microelectroics co.Ltd
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#I2c_PBcfg_c_REF_1:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#I2c_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#include "I2c_Cfg.h"
#include "I2c_GeneralTypes.h"
#include "I2c.h"
#include "i2c_hal.h"

/****************************************************************************************************
**                          Configurations                                                         **
****************************************************************************************************/
/* Notification Function Declarations */
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */ 
#include "I2c_MemMap.h"

/* I2c HwUnit configuration parameters of Core0 */
static const I2c_InitConfigType I2c_HWUnitConfigSetCore0[I2C_MAX_CHANNEL_TO_CORE0] =
{
    {
        /* FIFO mode */
        TRUE,
        /* RX-FIFO water mark */
        4U,
        /* TX-FIFO water mark */
        4U,
        /* FIFO AlignMode */
        I2C_FIFO_ALIGNBYTE_1,
        /* Bus Speed */
        I2C_STANDARD_MODE,
        /* I2C fast mode Tlow/Thigh = 16/9 */
        0x00000001U,
        /* Single transmition */
        0U
    }
};

/* I2c channel configuration parameters of Core0 */
static const I2c_ChannelConfigType I2c_ChannelConfigSetCore0[I2C_MAX_CHANNEL_TO_CORE0] =
{
    {
        /* The configuration information structure of the hardware unit(I2C0) corresponding to the Channel0 */
        &I2c_HWUnitConfigSetCore0[0],
        /* Pointer to the notification function */
        NULL_PTR,
        /* I2C HwUnit(I2C0) of assigned to I2c channel */
        0U,
        /* I2C Channel ID */
        0U
    }
};

/* I2c channel number and configuration information in Core0 */
static const I2c_InitCoreConfigType I2c_ConfigSetCore0 =
{
    /* I2c configuration information of core0 */
    &I2c_ChannelConfigSetCore0[0],
    /* Maximum number of the channels allocated to the core0 */
    I2C_MAX_CHANNEL_TO_CORE0
};

/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */ 
#include "I2c_MemMap.h"

/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */ 
#include "I2c_MemMap.h"

/* 
This array is used for mapping I2c Channel to the Core. 
Array index is I2c channel -> array member is index of I2c_ChannelConfigSetCorex[x=0~1]
*/
static const uint8 I2c_ChannelToCoreMap[I2C_TOTAL_CFG_CHANNEL_NUM] =
{
    /* I2cChannel_0 configuration information is assigned to index0 of Core0 */
    0U
};

/* 
This array is used for mapping I2c hardware unit to the I2c channel. 
Array index is hardware unit -> array member is I2c channel
*/
static const uint8 I2c_HwToChannel[I2C_MAX_HWUNIT_COUNT] =
{
    /* I2C0 assigned to I2cChannel_0 in Core0 */
    0U,
    /* I2C1 not assigned */
    0xFFU
};

/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */ 
#include "I2c_MemMap.h"
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */ 
#include "I2c_MemMap.h"

/* Configuration parameters */
const I2c_ConfigType I2c_ConfigSet[I2C_CONFIG_COUNT] =
{
    {
        {
            /* I2C channels configuration of Core0 */
            &I2c_ConfigSetCore0,
            /* I2C channels configuration of Core1 */
            NULL_PTR
        },
        /* Table for relationship between channel ID in specified core and I2c channel ID */
        &I2c_ChannelToCoreMap[0],
        /* Table for relationship between hardware unit and logical I2c channel ID */
        &I2c_HwToChannel[0]
    }
};


/* #Violation: I2c_PBcfg_c_REF_2 */
#define I2C_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: I2c_PBcfg_c_REF_1 */
#include "I2c_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dio_PBCfg.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all configurations of Dio Driver
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
*#Dio_PBcfg_c_REF_1:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Dio_PBcfg_c_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dio.h"
#include "Dio_Cfg.h"

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
/* #Violation: Dio_PBcfg_c_REF_2 */
#define DIO_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
#include "Dio_MemMap.h"
static const Dio_PortChannelIdType Dio_PortChannelCfgData[DIO_AVAILABEL_PORT_TOTAL_NUMBER]=
{
    {/* Port0 */ DIO_PORT_CONFIGURED,     (0x0404U)},
    {/* Port1 */ DIO_PORT_CONFIGURED,     (0x0000U)},
    {/* Port2 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port10 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port11 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port12 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port13 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port14 */ DIO_PORT_CONFIGURED,     (0x03f8U)},
    {/* Port15 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port20 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port21 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port22 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port23 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port24 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port25 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port26 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port30 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port31 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port32 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port33 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port34 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port40 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)},
    {/* Port41 */ DIO_PORT_NOT_CONFIGURED, (0x0000U)}
};

static const Dio_ChannelGroupType Dio_GroupConfigData[DIO_CHANNELGROUPCOUNT]=
{
    {
        /* DioPort_14, DIO_GROUP_TEST_OUT */
        (Dio_PortType)14U,          /* Port Id */
        (uint8)4U,                  /* Offset  */
        (Dio_PortLevelType)0x30U    /* Mask    */
    },
    {
        /* DioPort_14, DIO_GROUP_TEST_IN */
        (Dio_PortType)14U,          /* Port Id */
        (uint8)3U,                  /* Offset  */
        (Dio_PortLevelType)0x38U    /* Mask    */
    } 
};

static const uint8 Dio_AvailablePortIndexMap[DIO_MAX_PORT_NUMBER] =
{
    0x00U,   /* Port0 */
    0x01U,   /* Port1 */
    0x02U,   /* Port2 */
    0xFFU,   /* Port3 */
    0xFFU,   /* Port4 */
    0xFFU,   /* Port5 */
    0xFFU,   /* Port6 */
    0xFFU,   /* Port7 */
    0xFFU,   /* Port8 */
    0xFFU,   /* Port9 */
    0x03U,   /* Port10 */
    0x04U,   /* Port11 */
    0x05U,   /* Port12 */
    0x06U,   /* Port13 */
    0x07U,   /* Port14 */
    0x08U,   /* Port15 */
    0xFFU,   /* Port16 */
    0xFFU,   /* Port17 */
    0xFFU,   /* Port18 */
    0xFFU,   /* Port19 */
    0x09U,   /* Port20 */
    0x0AU,   /* Port21 */
    0x0BU,   /* Port22 */
    0x0CU,   /* Port23 */
    0x0DU,   /* Port24 */
    0x0EU,   /* Port25 */
    0x0FU,   /* Port26 */
    0xFFU,   /* Port27 */
    0xFFU,   /* Port28 */
    0xFFU,   /* Port29 */
    0x10U,   /* Port30 */
    0x11U,   /* Port31 */
    0x12U,   /* Port32 */
    0x13U,   /* Port33 */
    0x14U,   /* Port34 */
    0xFFU,   /* Port35 */
    0xFFU,   /* Port36 */
    0xFFU,   /* Port37 */
    0xFFU,   /* Port38 */
    0xFFU,   /* Port39 */
    0x15U,   /* Port40 */
    0x16U    /* Port41 */
};

static const uint16 Dio_AvailablePortPins[DIO_AVAILABEL_PORT_TOTAL_NUMBER] =
{
    0xffffU,    /* Port0 */
    0xffffU,    /* Port1 */
    0xffffU,    /* Port2 */
    0xefffU,    /* Port10 */
    0xffffU,    /* Port11 */
    0x0003U,    /* Port12 */
    0xfeffU,    /* Port13 */
    0xffffU,    /* Port14 */
    0xfdffU,    /* Port15 */
    0x7fcbU,    /* Port20 */
    0x00ffU,    /* Port21 */
    0x0fffU,    /* Port22 */
    0x00ffU,    /* Port23 */
    0xffffU,    /* Port24 */
    0xffffU,    /* Port25 */
    0x0001U,    /* Port26 */
    0xffffU,    /* Port30 */
    0xffffU,    /* Port31 */
    0x00ffU,    /* Port32 */
    0xffffU,    /* Port33 */
    0x003eU,    /* Port34 */
    0xffffU,    /* Port40 */
    0x01ffU     /* Port41 */
};

const Dio_ConfigType Dio_ConfigSet =
{
    /* DIO single channel configuration parameters */
    &Dio_PortChannelCfgData[0],
    /* DIO channel group configuration parameters set */
    &Dio_GroupConfigData[0],
    /* The Port index from available Port */
    &Dio_AvailablePortIndexMap[0],
    /* The PIN available for each port */
    &Dio_AvailablePortPins[0]
};
/* #Violation: Dio_PBcfg_c_REF_2 */
#define DIO_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dio_PBcfg_c_REF_1 */
#include "Dio_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Port_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all configuration declarations of Port Driver
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
*
*#Port_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/
#ifndef PORT_CFG_H_
#define PORT_CFG_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/*  SWS_Port_00130:
    Port.h shall include Port_Cfg.h for the API pre-compiler switches and Std_Types.h
*/
#include "Std_Types.h"
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION           (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION           (4U)
#define PORT_CFG_AR_RELEASE_REVISION_VERSION        (0U)

#define PORT_CFG_SW_MAJOR_VERSION                   (1U)
#define PORT_CFG_SW_MINOR_VERSION                   (2U)
#define PORT_CFG_SW_PATCH_VERSION                   (0U)

#define PORT_CFG_VENDOR_ID                          (175U) /* 0xAF */
#define PORT_CFG_MODULE_ID                          (124U) /* 0x7C */

/*
  Configuration: PORT_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define PORT_DEV_ERROR_DETECT                       (STD_ON)
/*
  Configuration: PORT_SAFETY_ENABLE
- if Selected, Safety check is Enabled
- if Deselected, Safety check is Disabled
*/
#define PORT_SAFETY_ENABLE                          (STD_ON)
/*
  Configuration: PORT_VERSION_INFO_API
- if Selected,  Function Port_GetVersionInfo is available
- if Deselected, Function Port_GetVersionInfo is not available
*/
#define PORT_VERSION_INFO_API                       (STD_ON)
/*
  Configuration: PORT_SET_PIN_MODE_API
- if Selected,  Function Port_SetPinMode is available
- if Deselected, Function Port_SetPinMode is not available
*/
#define PORT_SET_PIN_MODE_API                       (STD_ON)

/*  SWS_Port_00086:
    The function Port_SetPinDirection shall only be available to the user if the pre-compile
    parameter PortSetPinDirectionApi is set to TRUE. If set to FALSE, the function
    Port_SetPinDirection is not available.
  Configuration: PORT_SET_PIN_DIRECTION_API
- if Selected,  Function Port_SetPinDirection is available
- if Deselected, Function Port_SetPinDirection is not available
*/
#define PORT_SET_PIN_DIRECTION_API                  (STD_ON)
/*
  Configuration: PORT_LVDS_FUNCTION_ENABLE
- if Selected,  LVDS function is enabled.
- if Deselected, LVDS function is disabled
*/
#define PORT_LVDS_FUNCTION_ENABLE                   (STD_ON)

/* Definition to specify the available Port total number */
#define PORT_AVAILABEL_TOTAL_NUMBER                 (16U)

/* Definition to specify the available Alternate function register total number */
#define PORT_RXMUX_REG_TOTAL_NUMBER                 (36U)

/* Maximum Port Number */
#define PORT_MAX_NUMBER                             (42U)

/* Maximum Pin Number */
#define PIN_MAX_NUMBER                              (16U)

/* Total number of CTRx registers */
#define PORT_CTRX_NUMBER                            (4U)

/* Total number of DSRx registers */
#define PORT_DSRX_NUMBER                            (2U)

/* Total number of port configuration files */
#define PORT_CONFIG_COUNT                           (1U)

/*  SWS_Port_00006:
    The user of the PORT Driver module shall configure the symbolic names of the port pins of the MCU.
    SWS_Port_00207:
    These symbolic names for the individual port pins (e.g. PORT_A_PIN_0)
    shall be defined in the configuration tool.
    SWS_Port_00076:
    The PORT Driver module's implementer shall define symbolic names in the file Port_Cfg.h
*/
/* Symbolic Name: Port0 */
#ifndef PortConf_PortContainer_0
#define PortConf_PortContainer_0                    (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_0                             (0U)
#endif
/* Symbolic Name: P0.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_CAN10_TXD
#define PortConf_PortContainer_0_CAN10_TXD          ((Port_PinType) 0x000U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_0       ((Port_PinType) 0x000U)
#endif
/* Symbolic Name: P0.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_I2C0_SDA
#define PortConf_PortContainer_0_I2C0_SDA          ((Port_PinType) 0x001U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_1       ((Port_PinType) 0x001U)
#endif
/* Symbolic Name: P0.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_I2C0_SCL
#define PortConf_PortContainer_0_I2C0_SCL          ((Port_PinType) 0x002U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_2       ((Port_PinType) 0x002U)
#endif
/* Symbolic Name: P0.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_SENT_SPC2
#define PortConf_PortContainer_0_SENT_SPC2          ((Port_PinType) 0x003U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_3       ((Port_PinType) 0x003U)
#endif
/* Symbolic Name: P0.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_4
#define PortConf_PortContainer_0_PortPin_4          ((Port_PinType) 0x004U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_4       ((Port_PinType) 0x004U)
#endif
/* Symbolic Name: P0.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_5
#define PortConf_PortContainer_0_PortPin_5          ((Port_PinType) 0x005U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_5       ((Port_PinType) 0x005U)
#endif
/* Symbolic Name: P0.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_SENT_SPC5
#define PortConf_PortContainer_0_SENT_SPC5          ((Port_PinType) 0x006U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_6       ((Port_PinType) 0x006U)
#endif
/* Symbolic Name: P0.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_7
#define PortConf_PortContainer_0_PortPin_7          ((Port_PinType) 0x007U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_7       ((Port_PinType) 0x007U)
#endif
/* Symbolic Name: P0.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_8
#define PortConf_PortContainer_0_PortPin_8          ((Port_PinType) 0x008U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_8       ((Port_PinType) 0x008U)
#endif
/* Symbolic Name: P0.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_9
#define PortConf_PortContainer_0_PortPin_9          ((Port_PinType) 0x009U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_9       ((Port_PinType) 0x009U)
#endif
/* Symbolic Name: P0.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_10
#define PortConf_PortContainer_0_PortPin_10          ((Port_PinType) 0x00aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_10       ((Port_PinType) 0x00aU)
#endif
/* Symbolic Name: P0.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_11
#define PortConf_PortContainer_0_PortPin_11          ((Port_PinType) 0x00bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_11       ((Port_PinType) 0x00bU)
#endif
/* Symbolic Name: P0.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_12
#define PortConf_PortContainer_0_PortPin_12          ((Port_PinType) 0x00cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_12       ((Port_PinType) 0x00cU)
#endif
/* Symbolic Name: Port2 */
#ifndef PortConf_PortContainer_1
#define PortConf_PortContainer_1                    (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_2                             (2U)
#endif
/* Symbolic Name: P2.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_0
#define PortConf_PortContainer_1_PortPin_0          ((Port_PinType) 0x020U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_2_PIN_0       ((Port_PinType) 0x020U)
#endif
/* Symbolic Name: P2.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_1
#define PortConf_PortContainer_1_PortPin_1          ((Port_PinType) 0x021U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_2_PIN_1       ((Port_PinType) 0x021U)
#endif
/* Symbolic Name: P2.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_2
#define PortConf_PortContainer_1_PortPin_2          ((Port_PinType) 0x022U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_2_PIN_2       ((Port_PinType) 0x022U)
#endif
/* Symbolic Name: P2.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_3
#define PortConf_PortContainer_1_PortPin_3          ((Port_PinType) 0x023U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_2_PIN_3       ((Port_PinType) 0x023U)
#endif
/* Symbolic Name: P2.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_CAN11_RXDA
#define PortConf_PortContainer_1_CAN11_RXDA          ((Port_PinType) 0x024U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_2_PIN_4       ((Port_PinType) 0x024U)
#endif
/* Symbolic Name: P2.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_CAN11_TXD
#define PortConf_PortContainer_1_CAN11_TXD          ((Port_PinType) 0x025U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_2_PIN_5       ((Port_PinType) 0x025U)
#endif
/* Symbolic Name: P2.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_6
#define PortConf_PortContainer_1_PortPin_6          ((Port_PinType) 0x026U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_2_PIN_6       ((Port_PinType) 0x026U)
#endif
/* Symbolic Name: P2.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_7
#define PortConf_PortContainer_1_PortPin_7          ((Port_PinType) 0x027U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_2_PIN_7       ((Port_PinType) 0x027U)
#endif
/* Symbolic Name: P2.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_8
#define PortConf_PortContainer_1_PortPin_8          ((Port_PinType) 0x028U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_2_PIN_8       ((Port_PinType) 0x028U)
#endif
/* Symbolic Name: Port10 */
#ifndef PortConf_PortContainer_2
#define PortConf_PortContainer_2                    (10U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_10                             (10U)
#endif
/* Symbolic Name: P10.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_0
#define PortConf_PortContainer_2_PortPin_0          ((Port_PinType) 0x0a1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_10_PIN_1       ((Port_PinType) 0x0a1U)
#endif
/* Symbolic Name: P10.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_1
#define PortConf_PortContainer_2_PortPin_1          ((Port_PinType) 0x0a2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_10_PIN_2       ((Port_PinType) 0x0a2U)
#endif
/* Symbolic Name: P10.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_2
#define PortConf_PortContainer_2_PortPin_2          ((Port_PinType) 0x0a3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_10_PIN_3       ((Port_PinType) 0x0a3U)
#endif
/* Symbolic Name: P10.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_3
#define PortConf_PortContainer_2_PortPin_3          ((Port_PinType) 0x0a4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_10_PIN_4       ((Port_PinType) 0x0a4U)
#endif
/* Symbolic Name: P10.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_4
#define PortConf_PortContainer_2_PortPin_4          ((Port_PinType) 0x0a5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_10_PIN_5       ((Port_PinType) 0x0a5U)
#endif
/* Symbolic Name: P10.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_5
#define PortConf_PortContainer_2_PortPin_5          ((Port_PinType) 0x0a6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_10_PIN_6       ((Port_PinType) 0x0a6U)
#endif
/* Symbolic Name: P10.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_6
#define PortConf_PortContainer_2_PortPin_6          ((Port_PinType) 0x0a7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_10_PIN_7       ((Port_PinType) 0x0a7U)
#endif
/* Symbolic Name: P10.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_7
#define PortConf_PortContainer_2_PortPin_7          ((Port_PinType) 0x0a8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_10_PIN_8       ((Port_PinType) 0x0a8U)
#endif
/* Symbolic Name: Port11 */
#ifndef PortConf_PortContainer_3
#define PortConf_PortContainer_3                    (11U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_11                             (11U)
#endif
/* Symbolic Name: P11.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_0
#define PortConf_PortContainer_3_PortPin_0          ((Port_PinType) 0x0b2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_11_PIN_2       ((Port_PinType) 0x0b2U)
#endif
/* Symbolic Name: P11.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_1
#define PortConf_PortContainer_3_PortPin_1          ((Port_PinType) 0x0b3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_11_PIN_3       ((Port_PinType) 0x0b3U)
#endif
/* Symbolic Name: P11.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_2
#define PortConf_PortContainer_3_PortPin_2          ((Port_PinType) 0x0b6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_11_PIN_6       ((Port_PinType) 0x0b6U)
#endif
/* Symbolic Name: P11.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_3
#define PortConf_PortContainer_3_PortPin_3          ((Port_PinType) 0x0b8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_11_PIN_8       ((Port_PinType) 0x0b8U)
#endif
/* Symbolic Name: P11.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_4
#define PortConf_PortContainer_3_PortPin_4          ((Port_PinType) 0x0b9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_11_PIN_9       ((Port_PinType) 0x0b9U)
#endif
/* Symbolic Name: P11.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_5
#define PortConf_PortContainer_3_PortPin_5          ((Port_PinType) 0x0baU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_11_PIN_10       ((Port_PinType) 0x0baU)
#endif
/* Symbolic Name: P11.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_6
#define PortConf_PortContainer_3_PortPin_6          ((Port_PinType) 0x0bbU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_11_PIN_11       ((Port_PinType) 0x0bbU)
#endif
/* Symbolic Name: P11.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_7
#define PortConf_PortContainer_3_PortPin_7          ((Port_PinType) 0x0bcU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_11_PIN_12       ((Port_PinType) 0x0bcU)
#endif
/* Symbolic Name: Port13 */
#ifndef PortConf_PortContainer_4
#define PortConf_PortContainer_4                    (13U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_13                             (13U)
#endif
/* Symbolic Name: P13.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_0
#define PortConf_PortContainer_4_PortPin_0          ((Port_PinType) 0x0d0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_13_PIN_0       ((Port_PinType) 0x0d0U)
#endif
/* Symbolic Name: P13.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_1
#define PortConf_PortContainer_4_PortPin_1          ((Port_PinType) 0x0d1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_13_PIN_1       ((Port_PinType) 0x0d1U)
#endif
/* Symbolic Name: P13.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_2
#define PortConf_PortContainer_4_PortPin_2          ((Port_PinType) 0x0d2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_13_PIN_2       ((Port_PinType) 0x0d2U)
#endif
/* Symbolic Name: P13.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_3
#define PortConf_PortContainer_4_PortPin_3          ((Port_PinType) 0x0d3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_13_PIN_3       ((Port_PinType) 0x0d3U)
#endif
/* Symbolic Name: Port14 */
#ifndef PortConf_PortContainer_5
#define PortConf_PortContainer_5                    (14U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_14                             (14U)
#endif
/* Symbolic Name: P14.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_0
#define PortConf_PortContainer_5_PortPin_0          ((Port_PinType) 0x0e0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_0       ((Port_PinType) 0x0e0U)
#endif
/* Symbolic Name: P14.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortDemoPin1
#define PortConf_PortContainer_5_PortDemoPin1          ((Port_PinType) 0x0e1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_1       ((Port_PinType) 0x0e1U)
#endif
/* Symbolic Name: P14.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortDemoPin2
#define PortConf_PortContainer_5_PortDemoPin2          ((Port_PinType) 0x0e2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_2       ((Port_PinType) 0x0e2U)
#endif
/* Symbolic Name: P14.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_3
#define PortConf_PortContainer_5_PortPin_3          ((Port_PinType) 0x0e3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_3       ((Port_PinType) 0x0e3U)
#endif
/* Symbolic Name: P14.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_4
#define PortConf_PortContainer_5_PortPin_4          ((Port_PinType) 0x0e4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_4       ((Port_PinType) 0x0e4U)
#endif
/* Symbolic Name: P14.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_5
#define PortConf_PortContainer_5_PortPin_5          ((Port_PinType) 0x0e5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_5       ((Port_PinType) 0x0e5U)
#endif
/* Symbolic Name: P14.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_6
#define PortConf_PortContainer_5_PortPin_6          ((Port_PinType) 0x0e6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_6       ((Port_PinType) 0x0e6U)
#endif
/* Symbolic Name: P14.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_7
#define PortConf_PortContainer_5_PortPin_7          ((Port_PinType) 0x0e7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_7       ((Port_PinType) 0x0e7U)
#endif
/* Symbolic Name: P14.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_8
#define PortConf_PortContainer_5_PortPin_8          ((Port_PinType) 0x0e8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_8       ((Port_PinType) 0x0e8U)
#endif
/* Symbolic Name: P14.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_9
#define PortConf_PortContainer_5_PortPin_9          ((Port_PinType) 0x0e9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_9       ((Port_PinType) 0x0e9U)
#endif
/* Symbolic Name: P14.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_10
#define PortConf_PortContainer_5_PortPin_10          ((Port_PinType) 0x0eaU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_14_PIN_10       ((Port_PinType) 0x0eaU)
#endif
/* Symbolic Name: Port15 */
#ifndef PortConf_PortContainer_6
#define PortConf_PortContainer_6                    (15U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_15                             (15U)
#endif
/* Symbolic Name: P15.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_CAN02_TXD
#define PortConf_PortContainer_6_CAN02_TXD          ((Port_PinType) 0x0f0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_15_PIN_0       ((Port_PinType) 0x0f0U)
#endif
/* Symbolic Name: P15.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_CAN02_RXDA
#define PortConf_PortContainer_6_CAN02_RXDA          ((Port_PinType) 0x0f1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_15_PIN_1       ((Port_PinType) 0x0f1U)
#endif
/* Symbolic Name: P15.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_Uart_Tx
#define PortConf_PortContainer_6_Uart_Tx          ((Port_PinType) 0x0f2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_15_PIN_2       ((Port_PinType) 0x0f2U)
#endif
/* Symbolic Name: P15.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_Uart_Rx
#define PortConf_PortContainer_6_Uart_Rx          ((Port_PinType) 0x0f3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_15_PIN_3       ((Port_PinType) 0x0f3U)
#endif
/* Symbolic Name: P15.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_4
#define PortConf_PortContainer_6_PortPin_4          ((Port_PinType) 0x0f4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_15_PIN_4       ((Port_PinType) 0x0f4U)
#endif
/* Symbolic Name: P15.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_5
#define PortConf_PortContainer_6_PortPin_5          ((Port_PinType) 0x0f5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_15_PIN_5       ((Port_PinType) 0x0f5U)
#endif
/* Symbolic Name: P15.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_6
#define PortConf_PortContainer_6_PortPin_6          ((Port_PinType) 0x0f6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_15_PIN_6       ((Port_PinType) 0x0f6U)
#endif
/* Symbolic Name: P15.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_7
#define PortConf_PortContainer_6_PortPin_7          ((Port_PinType) 0x0f7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_15_PIN_7       ((Port_PinType) 0x0f7U)
#endif
/* Symbolic Name: P15.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_8
#define PortConf_PortContainer_6_PortPin_8          ((Port_PinType) 0x0f8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_15_PIN_8       ((Port_PinType) 0x0f8U)
#endif
/* Symbolic Name: Port20 */
#ifndef PortConf_PortContainer_7
#define PortConf_PortContainer_7                    (20U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_20                             (20U)
#endif
/* Symbolic Name: P20.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_LIN3_TX
#define PortConf_PortContainer_7_LIN3_TX          ((Port_PinType) 0x140U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_0       ((Port_PinType) 0x140U)
#endif
/* Symbolic Name: P20.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_1
#define PortConf_PortContainer_7_PortPin_1          ((Port_PinType) 0x141U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_1       ((Port_PinType) 0x141U)
#endif
/* Symbolic Name: P20.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_2
#define PortConf_PortContainer_7_PortPin_2          ((Port_PinType) 0x142U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_2       ((Port_PinType) 0x142U)
#endif
/* Symbolic Name: P20.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_LIN3_RX
#define PortConf_PortContainer_7_LIN3_RX          ((Port_PinType) 0x143U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_3       ((Port_PinType) 0x143U)
#endif
/* Symbolic Name: P20.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_4
#define PortConf_PortContainer_7_PortPin_4          ((Port_PinType) 0x146U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_6       ((Port_PinType) 0x146U)
#endif
/* Symbolic Name: P20.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_CAN00_RXDB
#define PortConf_PortContainer_7_CAN00_RXDB          ((Port_PinType) 0x147U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_7       ((Port_PinType) 0x147U)
#endif
/* Symbolic Name: P20.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_CAN00_TXD
#define PortConf_PortContainer_7_CAN00_TXD          ((Port_PinType) 0x148U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_8       ((Port_PinType) 0x148U)
#endif
/* Symbolic Name: P20.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_ESPI0_SLSO1
#define PortConf_PortContainer_7_ESPI0_SLSO1          ((Port_PinType) 0x149U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_9       ((Port_PinType) 0x149U)
#endif
/* Symbolic Name: P20.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_8
#define PortConf_PortContainer_7_PortPin_8          ((Port_PinType) 0x14aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_10       ((Port_PinType) 0x14aU)
#endif
/* Symbolic Name: P20.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_ESPI0_SCLK
#define PortConf_PortContainer_7_ESPI0_SCLK          ((Port_PinType) 0x14bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_11       ((Port_PinType) 0x14bU)
#endif
/* Symbolic Name: P20.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_ESPI0_MRSTA
#define PortConf_PortContainer_7_ESPI0_MRSTA          ((Port_PinType) 0x14cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_12       ((Port_PinType) 0x14cU)
#endif
/* Symbolic Name: P20.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_11
#define PortConf_PortContainer_7_PortPin_11          ((Port_PinType) 0x14dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_13       ((Port_PinType) 0x14dU)
#endif
/* Symbolic Name: P20.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_ESPI0_MTSR
#define PortConf_PortContainer_7_ESPI0_MTSR          ((Port_PinType) 0x14eU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_20_PIN_14       ((Port_PinType) 0x14eU)
#endif
/* Symbolic Name: Port21 */
#ifndef PortConf_PortContainer_8
#define PortConf_PortContainer_8                    (21U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_21                             (21U)
#endif
/* Symbolic Name: P21.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_0
#define PortConf_PortContainer_8_PortPin_0          ((Port_PinType) 0x151U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_21_PIN_1       ((Port_PinType) 0x151U)
#endif
/* Symbolic Name: P21.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_1
#define PortConf_PortContainer_8_PortPin_1          ((Port_PinType) 0x152U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_21_PIN_2       ((Port_PinType) 0x152U)
#endif
/* Symbolic Name: P21.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_2
#define PortConf_PortContainer_8_PortPin_2          ((Port_PinType) 0x153U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_21_PIN_3       ((Port_PinType) 0x153U)
#endif
/* Symbolic Name: P21.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_3
#define PortConf_PortContainer_8_PortPin_3          ((Port_PinType) 0x154U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_21_PIN_4       ((Port_PinType) 0x154U)
#endif
/* Symbolic Name: P21.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_4
#define PortConf_PortContainer_8_PortPin_4          ((Port_PinType) 0x155U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_21_PIN_5       ((Port_PinType) 0x155U)
#endif
/* Symbolic Name: P21.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_5
#define PortConf_PortContainer_8_PortPin_5          ((Port_PinType) 0x156U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_21_PIN_6       ((Port_PinType) 0x156U)
#endif
/* Symbolic Name: P21.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_6
#define PortConf_PortContainer_8_PortPin_6          ((Port_PinType) 0x157U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_21_PIN_7       ((Port_PinType) 0x157U)
#endif
/* Symbolic Name: Port22 */
#ifndef PortConf_PortContainer_9
#define PortConf_PortContainer_9                    (22U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_22                             (22U)
#endif
/* Symbolic Name: P22.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_0
#define PortConf_PortContainer_9_PortPin_0          ((Port_PinType) 0x160U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_22_PIN_0       ((Port_PinType) 0x160U)
#endif
/* Symbolic Name: P22.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_1
#define PortConf_PortContainer_9_PortPin_1          ((Port_PinType) 0x161U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_22_PIN_1       ((Port_PinType) 0x161U)
#endif
/* Symbolic Name: P22.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_2
#define PortConf_PortContainer_9_PortPin_2          ((Port_PinType) 0x162U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_22_PIN_2       ((Port_PinType) 0x162U)
#endif
/* Symbolic Name: P22.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_3
#define PortConf_PortContainer_9_PortPin_3          ((Port_PinType) 0x163U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_22_PIN_3       ((Port_PinType) 0x163U)
#endif
/* Symbolic Name: Port23 */
#ifndef PortConf_PortContainer_10
#define PortConf_PortContainer_10                    (23U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_23                             (23U)
#endif
/* Symbolic Name: P23.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_0
#define PortConf_PortContainer_10_PortPin_0          ((Port_PinType) 0x170U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_23_PIN_0       ((Port_PinType) 0x170U)
#endif
/* Symbolic Name: P23.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_1
#define PortConf_PortContainer_10_PortPin_1          ((Port_PinType) 0x171U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_23_PIN_1       ((Port_PinType) 0x171U)
#endif
/* Symbolic Name: P23.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_2
#define PortConf_PortContainer_10_PortPin_2          ((Port_PinType) 0x172U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_23_PIN_2       ((Port_PinType) 0x172U)
#endif
/* Symbolic Name: P23.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_3
#define PortConf_PortContainer_10_PortPin_3          ((Port_PinType) 0x173U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_23_PIN_3       ((Port_PinType) 0x173U)
#endif
/* Symbolic Name: Port32 */
#ifndef PortConf_PortContainer_11
#define PortConf_PortContainer_11                    (32U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_32                             (32U)
#endif
/* Symbolic Name: P32.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_0
#define PortConf_PortContainer_11_PortPin_0          ((Port_PinType) 0x201U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_32_PIN_1       ((Port_PinType) 0x201U)
#endif
/* Symbolic Name: P32.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_1
#define PortConf_PortContainer_11_PortPin_1          ((Port_PinType) 0x204U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_32_PIN_4       ((Port_PinType) 0x204U)
#endif
/* Symbolic Name: Port33 */
#ifndef PortConf_PortContainer_12
#define PortConf_PortContainer_12                    (33U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_33                             (33U)
#endif
/* Symbolic Name: P33.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_LIN5_TX
#define PortConf_PortContainer_12_LIN5_TX          ((Port_PinType) 0x210U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_0       ((Port_PinType) 0x210U)
#endif
/* Symbolic Name: P33.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_1
#define PortConf_PortContainer_12_PortPin_1          ((Port_PinType) 0x211U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_1       ((Port_PinType) 0x211U)
#endif
/* Symbolic Name: P33.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_2
#define PortConf_PortContainer_12_PortPin_2          ((Port_PinType) 0x212U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_2       ((Port_PinType) 0x212U)
#endif
/* Symbolic Name: P33.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_3
#define PortConf_PortContainer_12_PortPin_3          ((Port_PinType) 0x213U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_3       ((Port_PinType) 0x213U)
#endif
/* Symbolic Name: P33.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_LIN5_RX
#define PortConf_PortContainer_12_LIN5_RX          ((Port_PinType) 0x214U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_4       ((Port_PinType) 0x214U)
#endif
/* Symbolic Name: P33.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_5
#define PortConf_PortContainer_12_PortPin_5          ((Port_PinType) 0x215U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_5       ((Port_PinType) 0x215U)
#endif
/* Symbolic Name: P33.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_SENT4C
#define PortConf_PortContainer_12_SENT4C          ((Port_PinType) 0x216U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_6       ((Port_PinType) 0x216U)
#endif
/* Symbolic Name: P33.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_7
#define PortConf_PortContainer_12_PortPin_7          ((Port_PinType) 0x217U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_7       ((Port_PinType) 0x217U)
#endif
/* Symbolic Name: P33.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_8
#define PortConf_PortContainer_12_PortPin_8          ((Port_PinType) 0x218U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_8       ((Port_PinType) 0x218U)
#endif
/* Symbolic Name: P33.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_CAN01_TXD
#define PortConf_PortContainer_12_CAN01_TXD          ((Port_PinType) 0x219U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_9       ((Port_PinType) 0x219U)
#endif
/* Symbolic Name: P33.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_CAN01_RXDD
#define PortConf_PortContainer_12_CAN01_RXDD          ((Port_PinType) 0x21aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_10       ((Port_PinType) 0x21aU)
#endif
/* Symbolic Name: P33.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_11
#define PortConf_PortContainer_12_PortPin_11          ((Port_PinType) 0x21bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_11       ((Port_PinType) 0x21bU)
#endif
/* Symbolic Name: P33.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_12
#define PortConf_PortContainer_12_PortPin_12          ((Port_PinType) 0x21cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_33_PIN_12       ((Port_PinType) 0x21cU)
#endif
/* Symbolic Name: Port34 */
#ifndef PortConf_PortContainer_13
#define PortConf_PortContainer_13                    (34U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_34                             (34U)
#endif
/* Symbolic Name: P34.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_0
#define PortConf_PortContainer_13_PortPin_0          ((Port_PinType) 0x221U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_34_PIN_1       ((Port_PinType) 0x221U)
#endif
/* Symbolic Name: P34.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_1
#define PortConf_PortContainer_13_PortPin_1          ((Port_PinType) 0x222U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_34_PIN_2       ((Port_PinType) 0x222U)
#endif
/* Symbolic Name: Port40 */
#ifndef PortConf_PortContainer_14
#define PortConf_PortContainer_14                    (40U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_40                             (40U)
#endif
/* Symbolic Name: P40.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_0
#define PortConf_PortContainer_14_PortPin_0          ((Port_PinType) 0x284U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_40_PIN_4       ((Port_PinType) 0x284U)
#endif
/* Symbolic Name: P40.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_1
#define PortConf_PortContainer_14_PortPin_1          ((Port_PinType) 0x285U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_40_PIN_5       ((Port_PinType) 0x285U)
#endif
/* Symbolic Name: P40.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_2
#define PortConf_PortContainer_14_PortPin_2          ((Port_PinType) 0x286U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_40_PIN_6       ((Port_PinType) 0x286U)
#endif
/* Symbolic Name: P40.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_3
#define PortConf_PortContainer_14_PortPin_3          ((Port_PinType) 0x287U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_40_PIN_7       ((Port_PinType) 0x287U)
#endif
/* Symbolic Name: P40.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_4
#define PortConf_PortContainer_14_PortPin_4          ((Port_PinType) 0x288U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_40_PIN_8       ((Port_PinType) 0x288U)
#endif
/* Symbolic Name: P40.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_5
#define PortConf_PortContainer_14_PortPin_5          ((Port_PinType) 0x289U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_40_PIN_9       ((Port_PinType) 0x289U)
#endif
/* Symbolic Name: Port41 */
#ifndef PortConf_PortContainer_15
#define PortConf_PortContainer_15                    (41U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_41                             (41U)
#endif
/* Symbolic Name: P41.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_0
#define PortConf_PortContainer_15_PortPin_0          ((Port_PinType) 0x290U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_0       ((Port_PinType) 0x290U)
#endif
/* Symbolic Name: P41.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_1
#define PortConf_PortContainer_15_PortPin_1          ((Port_PinType) 0x291U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_1       ((Port_PinType) 0x291U)
#endif
/* Symbolic Name: P41.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_2
#define PortConf_PortContainer_15_PortPin_2          ((Port_PinType) 0x292U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_2       ((Port_PinType) 0x292U)
#endif
/* Symbolic Name: P41.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_3
#define PortConf_PortContainer_15_PortPin_3          ((Port_PinType) 0x293U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_3       ((Port_PinType) 0x293U)
#endif
/* Symbolic Name: P41.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_4
#define PortConf_PortContainer_15_PortPin_4          ((Port_PinType) 0x294U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_4       ((Port_PinType) 0x294U)
#endif
/* Symbolic Name: P41.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_5
#define PortConf_PortContainer_15_PortPin_5          ((Port_PinType) 0x295U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_5       ((Port_PinType) 0x295U)
#endif
/* Symbolic Name: P41.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_6
#define PortConf_PortContainer_15_PortPin_6          ((Port_PinType) 0x296U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_6       ((Port_PinType) 0x296U)
#endif
/* Symbolic Name: P41.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_7
#define PortConf_PortContainer_15_PortPin_7          ((Port_PinType) 0x297U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_7       ((Port_PinType) 0x297U)
#endif
/* Symbolic Name: P41.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_8
#define PortConf_PortContainer_15_PortPin_8          ((Port_PinType) 0x298U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_8       ((Port_PinType) 0x298U)
#endif
/* Symbolic Name: P41.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_9
#define PortConf_PortContainer_15_PortPin_9          ((Port_PinType) 0x299U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_41_PIN_9       ((Port_PinType) 0x299U)
#endif

/* Generate IOM input multiplexing register configuration values */
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_14_7         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_14_8         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_14_9         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_20_12        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_20_13        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_20_14        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_0         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_1         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_2         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_3         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_4         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_5         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_6         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_7         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_8         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_9         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_10        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_11        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON0_33_12        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_0          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_1          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_2          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_3          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_4          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_5          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_6          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_7          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_8          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_9          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_12         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_0          (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_1          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_2          (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_3          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_4          (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_5          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_6          (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_7          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_8          (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_2         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_6         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_9         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_10        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_11        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_12        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_13_3         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_14_0         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_14_1         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_14_7         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_14_8         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_4         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_5         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_6         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_7         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_8         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_1         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_7         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_8         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_9         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_10        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_11        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_12        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_13        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_8         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_9         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_10        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_11        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_12        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_34_1         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_34_2         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_0_0          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_0_1          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_2_0          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_2_2          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_2_5          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_1         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_2         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_3         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_4         (9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_5         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_6         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_7         (5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_8         (6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_11_3         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_11_12        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_0         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_1         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_2         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_3         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_7         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_10        (8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_0         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_1         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_2         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_3         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_4         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_5         (5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_6         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_7         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_0         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_3         (5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_8         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_10        (6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_12        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_21_7         (6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_22_1         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_8         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_9         (5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_12        (7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_34_1         (3U)
/* Generate GTM input multiplexing register configuration values */
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO0_0_0          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO1_0_1          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO2_0_3          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO3_0_5          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO4_0_7          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO5_0_8          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO6_0_9          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO0_2_0          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO1_2_2          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO2_2_4          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO3_2_6          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO4_2_7          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO5_2_8          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO6_33_5         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO7_33_6         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_GTMTIO7_33_7         (1U)
/* Generate EXTI input multiplexing register configuration values */
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_EXTIREQ72_10_4       (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_EXTIREQ72_15_1       (0U)
/* Generate IOMPIN input multiplexing register configuration values */
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMPIN13_14_7        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMPIN13_20_12       (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMPIN14_14_8        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMPIN14_20_13       (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMPIN15_14_9        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMPIN15_20_14       (0U)
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

#endif /* PORT_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


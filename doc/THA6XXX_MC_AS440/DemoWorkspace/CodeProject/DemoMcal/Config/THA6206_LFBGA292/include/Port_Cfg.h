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
#define PORT_AVAILABEL_TOTAL_NUMBER                 (17U)

/* Definition to specify the available Alternate function register total number */
#define PORT_RXMUX_REG_TOTAL_NUMBER                 (23U)

/* Maximum Port Number */
#define PORT_MAX_NUMBER                             (41U)

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
#ifndef PortConf_PortContainer_0_PortPin_0
#define PortConf_PortContainer_0_PortPin_0          ((Port_PinType) 0x000U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_0       ((Port_PinType) 0x000U)
#endif
/* Symbolic Name: P0.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_1
#define PortConf_PortContainer_0_PortPin_1          ((Port_PinType) 0x001U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_1       ((Port_PinType) 0x001U)
#endif
/* Symbolic Name: P0.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_2
#define PortConf_PortContainer_0_PortPin_2          ((Port_PinType) 0x002U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_2       ((Port_PinType) 0x002U)
#endif
/* Symbolic Name: P0.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_SENT2
#define PortConf_PortContainer_0_SENT2          ((Port_PinType) 0x003U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_3       ((Port_PinType) 0x003U)
#endif
/* Symbolic Name: P0.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_SENT3SPC
#define PortConf_PortContainer_0_SENT3SPC          ((Port_PinType) 0x004U)
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
#ifndef PortConf_PortContainer_0_PortPin_6
#define PortConf_PortContainer_0_PortPin_6          ((Port_PinType) 0x006U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_6       ((Port_PinType) 0x006U)
#endif
/* Symbolic Name: P0.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_SENT6SPC
#define PortConf_PortContainer_0_SENT6SPC          ((Port_PinType) 0x007U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_7       ((Port_PinType) 0x007U)
#endif
/* Symbolic Name: P0.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_SENT7SPC
#define PortConf_PortContainer_0_SENT7SPC          ((Port_PinType) 0x008U)
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
/* Symbolic Name: Port1 */
#ifndef PortConf_PortContainer_1
#define PortConf_PortContainer_1                    (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_1                             (1U)
#endif
/* Symbolic Name: P1.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_0
#define PortConf_PortContainer_1_PortPin_0          ((Port_PinType) 0x014U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_4       ((Port_PinType) 0x014U)
#endif
/* Symbolic Name: P1.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_1
#define PortConf_PortContainer_1_PortPin_1          ((Port_PinType) 0x015U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_5       ((Port_PinType) 0x015U)
#endif
/* Symbolic Name: P1.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_2
#define PortConf_PortContainer_1_PortPin_2          ((Port_PinType) 0x016U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_6       ((Port_PinType) 0x016U)
#endif
/* Symbolic Name: P1.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_3
#define PortConf_PortContainer_1_PortPin_3          ((Port_PinType) 0x017U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_7       ((Port_PinType) 0x017U)
#endif
/* Symbolic Name: Port2 */
#ifndef PortConf_PortContainer_2
#define PortConf_PortContainer_2                    (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_2                             (2U)
#endif
/* Symbolic Name: P2.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_0
#define PortConf_PortContainer_2_PortPin_0          ((Port_PinType) 0x020U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_0       ((Port_PinType) 0x020U)
#endif
/* Symbolic Name: P2.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_1
#define PortConf_PortContainer_2_PortPin_1          ((Port_PinType) 0x021U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_1       ((Port_PinType) 0x021U)
#endif
/* Symbolic Name: P2.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_2
#define PortConf_PortContainer_2_PortPin_2          ((Port_PinType) 0x022U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_2       ((Port_PinType) 0x022U)
#endif
/* Symbolic Name: P2.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_3
#define PortConf_PortContainer_2_PortPin_3          ((Port_PinType) 0x023U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_3       ((Port_PinType) 0x023U)
#endif
/* Symbolic Name: P2.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_CAN11_RXD
#define PortConf_PortContainer_2_CAN11_RXD          ((Port_PinType) 0x024U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_4       ((Port_PinType) 0x024U)
#endif
/* Symbolic Name: P2.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_CAN11_TXD
#define PortConf_PortContainer_2_CAN11_TXD          ((Port_PinType) 0x025U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_5       ((Port_PinType) 0x025U)
#endif
/* Symbolic Name: P2.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_6
#define PortConf_PortContainer_2_PortPin_6          ((Port_PinType) 0x026U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_6       ((Port_PinType) 0x026U)
#endif
/* Symbolic Name: P2.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_7
#define PortConf_PortContainer_2_PortPin_7          ((Port_PinType) 0x027U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_7       ((Port_PinType) 0x027U)
#endif
/* Symbolic Name: P2.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_8
#define PortConf_PortContainer_2_PortPin_8          ((Port_PinType) 0x028U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_8       ((Port_PinType) 0x028U)
#endif
/* Symbolic Name: Port10 */
#ifndef PortConf_PortContainer_3
#define PortConf_PortContainer_3                    (10U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_10                             (10U)
#endif
/* Symbolic Name: P10.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_0
#define PortConf_PortContainer_3_PortPin_0          ((Port_PinType) 0x0a0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_0       ((Port_PinType) 0x0a0U)
#endif
/* Symbolic Name: P10.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_1
#define PortConf_PortContainer_3_PortPin_1          ((Port_PinType) 0x0a1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_1       ((Port_PinType) 0x0a1U)
#endif
/* Symbolic Name: P10.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_2
#define PortConf_PortContainer_3_PortPin_2          ((Port_PinType) 0x0a2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_2       ((Port_PinType) 0x0a2U)
#endif
/* Symbolic Name: P10.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_3
#define PortConf_PortContainer_3_PortPin_3          ((Port_PinType) 0x0a3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_3       ((Port_PinType) 0x0a3U)
#endif
/* Symbolic Name: P10.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_MSC0_EN0
#define PortConf_PortContainer_3_MSC0_EN0          ((Port_PinType) 0x0a4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_4       ((Port_PinType) 0x0a4U)
#endif
/* Symbolic Name: P10.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_ASI2_ATX
#define PortConf_PortContainer_3_ASI2_ATX          ((Port_PinType) 0x0a5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_5       ((Port_PinType) 0x0a5U)
#endif
/* Symbolic Name: P10.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_ASI2_ARXD
#define PortConf_PortContainer_3_ASI2_ARXD          ((Port_PinType) 0x0a6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_6       ((Port_PinType) 0x0a6U)
#endif
/* Symbolic Name: P10.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_7
#define PortConf_PortContainer_3_PortPin_7          ((Port_PinType) 0x0a7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_7       ((Port_PinType) 0x0a7U)
#endif
/* Symbolic Name: P10.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_8
#define PortConf_PortContainer_3_PortPin_8          ((Port_PinType) 0x0a8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_8       ((Port_PinType) 0x0a8U)
#endif
/* Symbolic Name: Port11 */
#ifndef PortConf_PortContainer_4
#define PortConf_PortContainer_4                    (11U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_11                             (11U)
#endif
/* Symbolic Name: P11.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_0
#define PortConf_PortContainer_4_PortPin_0          ((Port_PinType) 0x0b0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_0       ((Port_PinType) 0x0b0U)
#endif
/* Symbolic Name: P11.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_1
#define PortConf_PortContainer_4_PortPin_1          ((Port_PinType) 0x0b1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_1       ((Port_PinType) 0x0b1U)
#endif
/* Symbolic Name: P11.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_2
#define PortConf_PortContainer_4_PortPin_2          ((Port_PinType) 0x0b2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_2       ((Port_PinType) 0x0b2U)
#endif
/* Symbolic Name: P11.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_3
#define PortConf_PortContainer_4_PortPin_3          ((Port_PinType) 0x0b3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_3       ((Port_PinType) 0x0b3U)
#endif
/* Symbolic Name: P11.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_4
#define PortConf_PortContainer_4_PortPin_4          ((Port_PinType) 0x0b4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_4       ((Port_PinType) 0x0b4U)
#endif
/* Symbolic Name: P11.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_5
#define PortConf_PortContainer_4_PortPin_5          ((Port_PinType) 0x0b5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_5       ((Port_PinType) 0x0b5U)
#endif
/* Symbolic Name: P11.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_6
#define PortConf_PortContainer_4_PortPin_6          ((Port_PinType) 0x0b6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_6       ((Port_PinType) 0x0b6U)
#endif
/* Symbolic Name: P11.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_7
#define PortConf_PortContainer_4_PortPin_7          ((Port_PinType) 0x0b7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_7       ((Port_PinType) 0x0b7U)
#endif
/* Symbolic Name: P11.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_8
#define PortConf_PortContainer_4_PortPin_8          ((Port_PinType) 0x0b8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_8       ((Port_PinType) 0x0b8U)
#endif
/* Symbolic Name: P11.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_9
#define PortConf_PortContainer_4_PortPin_9          ((Port_PinType) 0x0b9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_9       ((Port_PinType) 0x0b9U)
#endif
/* Symbolic Name: P11.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_10
#define PortConf_PortContainer_4_PortPin_10          ((Port_PinType) 0x0baU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_10       ((Port_PinType) 0x0baU)
#endif
/* Symbolic Name: P11.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_11
#define PortConf_PortContainer_4_PortPin_11          ((Port_PinType) 0x0bbU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_11       ((Port_PinType) 0x0bbU)
#endif
/* Symbolic Name: P11.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_12
#define PortConf_PortContainer_4_PortPin_12          ((Port_PinType) 0x0bcU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_12       ((Port_PinType) 0x0bcU)
#endif
/* Symbolic Name: P11.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_13
#define PortConf_PortContainer_4_PortPin_13          ((Port_PinType) 0x0bdU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_13       ((Port_PinType) 0x0bdU)
#endif
/* Symbolic Name: P11.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_14
#define PortConf_PortContainer_4_PortPin_14          ((Port_PinType) 0x0beU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_14       ((Port_PinType) 0x0beU)
#endif
/* Symbolic Name: P11.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_4_PortPin_15
#define PortConf_PortContainer_4_PortPin_15          ((Port_PinType) 0x0bfU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_4_PORT_11_PIN_15       ((Port_PinType) 0x0bfU)
#endif
/* Symbolic Name: Port12 */
#ifndef PortConf_PortContainer_5
#define PortConf_PortContainer_5                    (12U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_12                             (12U)
#endif
/* Symbolic Name: P12.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_0
#define PortConf_PortContainer_5_PortPin_0          ((Port_PinType) 0x0c0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_12_PIN_0       ((Port_PinType) 0x0c0U)
#endif
/* Symbolic Name: P12.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_5_PortPin_1
#define PortConf_PortContainer_5_PortPin_1          ((Port_PinType) 0x0c1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_5_PORT_12_PIN_1       ((Port_PinType) 0x0c1U)
#endif
/* Symbolic Name: Port13 */
#ifndef PortConf_PortContainer_6
#define PortConf_PortContainer_6                    (13U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_13                             (13U)
#endif
/* Symbolic Name: P13.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_MSC0_FCLN
#define PortConf_PortContainer_6_MSC0_FCLN          ((Port_PinType) 0x0d0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_0       ((Port_PinType) 0x0d0U)
#endif
/* Symbolic Name: P13.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_MSC0_FCLP
#define PortConf_PortContainer_6_MSC0_FCLP          ((Port_PinType) 0x0d1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_1       ((Port_PinType) 0x0d1U)
#endif
/* Symbolic Name: P13.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_MSC0_SON
#define PortConf_PortContainer_6_MSC0_SON          ((Port_PinType) 0x0d2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_2       ((Port_PinType) 0x0d2U)
#endif
/* Symbolic Name: P13.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_MSC0_SOP
#define PortConf_PortContainer_6_MSC0_SOP          ((Port_PinType) 0x0d3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_3       ((Port_PinType) 0x0d3U)
#endif
/* Symbolic Name: Port14 */
#ifndef PortConf_PortContainer_7
#define PortConf_PortContainer_7                    (14U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_14                             (14U)
#endif
/* Symbolic Name: P14.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_0
#define PortConf_PortContainer_7_PortPin_0          ((Port_PinType) 0x0e0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_0       ((Port_PinType) 0x0e0U)
#endif
/* Symbolic Name: P14.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortDemoPin1
#define PortConf_PortContainer_7_PortDemoPin1          ((Port_PinType) 0x0e1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_1       ((Port_PinType) 0x0e1U)
#endif
/* Symbolic Name: P14.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortDemoPin2
#define PortConf_PortContainer_7_PortDemoPin2          ((Port_PinType) 0x0e2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_2       ((Port_PinType) 0x0e2U)
#endif
/* Symbolic Name: P14.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_MSC0_SDI2
#define PortConf_PortContainer_7_MSC0_SDI2          ((Port_PinType) 0x0e3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_3       ((Port_PinType) 0x0e3U)
#endif
/* Symbolic Name: P14.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_4
#define PortConf_PortContainer_7_PortPin_4          ((Port_PinType) 0x0e4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_4       ((Port_PinType) 0x0e4U)
#endif
/* Symbolic Name: P14.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_5
#define PortConf_PortContainer_7_PortPin_5          ((Port_PinType) 0x0e5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_5       ((Port_PinType) 0x0e5U)
#endif
/* Symbolic Name: P14.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_6
#define PortConf_PortContainer_7_PortPin_6          ((Port_PinType) 0x0e6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_6       ((Port_PinType) 0x0e6U)
#endif
/* Symbolic Name: P14.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_7
#define PortConf_PortContainer_7_PortPin_7          ((Port_PinType) 0x0e7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_7       ((Port_PinType) 0x0e7U)
#endif
/* Symbolic Name: P14.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_8
#define PortConf_PortContainer_7_PortPin_8          ((Port_PinType) 0x0e8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_8       ((Port_PinType) 0x0e8U)
#endif
/* Symbolic Name: P14.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_ESPI2_SLSO
#define PortConf_PortContainer_7_ESPI2_SLSO          ((Port_PinType) 0x0e9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_9       ((Port_PinType) 0x0e9U)
#endif
/* Symbolic Name: P14.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_10
#define PortConf_PortContainer_7_PortPin_10          ((Port_PinType) 0x0eaU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_10       ((Port_PinType) 0x0eaU)
#endif
/* Symbolic Name: Port15 */
#ifndef PortConf_PortContainer_8
#define PortConf_PortContainer_8                    (15U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_15                             (15U)
#endif
/* Symbolic Name: P15.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_CAN02_TX
#define PortConf_PortContainer_8_CAN02_TX          ((Port_PinType) 0x0f0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_0       ((Port_PinType) 0x0f0U)
#endif
/* Symbolic Name: P15.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_CAN02_RX
#define PortConf_PortContainer_8_CAN02_RX          ((Port_PinType) 0x0f1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_1       ((Port_PinType) 0x0f1U)
#endif
/* Symbolic Name: P15.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_UART_TX
#define PortConf_PortContainer_8_UART_TX          ((Port_PinType) 0x0f2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_2       ((Port_PinType) 0x0f2U)
#endif
/* Symbolic Name: P15.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_UART_RX
#define PortConf_PortContainer_8_UART_RX          ((Port_PinType) 0x0f3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_3       ((Port_PinType) 0x0f3U)
#endif
/* Symbolic Name: P15.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_I2C_CLK
#define PortConf_PortContainer_8_I2C_CLK          ((Port_PinType) 0x0f4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_4       ((Port_PinType) 0x0f4U)
#endif
/* Symbolic Name: P15.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_I2C_DATA
#define PortConf_PortContainer_8_I2C_DATA          ((Port_PinType) 0x0f5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_5       ((Port_PinType) 0x0f5U)
#endif
/* Symbolic Name: P15.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_ESPI2_MTSR
#define PortConf_PortContainer_8_ESPI2_MTSR          ((Port_PinType) 0x0f6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_6       ((Port_PinType) 0x0f6U)
#endif
/* Symbolic Name: P15.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_ESPI2_MRSTB
#define PortConf_PortContainer_8_ESPI2_MRSTB          ((Port_PinType) 0x0f7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_7       ((Port_PinType) 0x0f7U)
#endif
/* Symbolic Name: P15.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_ESPI2_SCLK
#define PortConf_PortContainer_8_ESPI2_SCLK          ((Port_PinType) 0x0f8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_8       ((Port_PinType) 0x0f8U)
#endif
/* Symbolic Name: Port20 */
#ifndef PortConf_PortContainer_9
#define PortConf_PortContainer_9                    (20U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_20                             (20U)
#endif
/* Symbolic Name: P20.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_0
#define PortConf_PortContainer_9_PortPin_0          ((Port_PinType) 0x140U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_0       ((Port_PinType) 0x140U)
#endif
/* Symbolic Name: P20.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_1
#define PortConf_PortContainer_9_PortPin_1          ((Port_PinType) 0x141U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_1       ((Port_PinType) 0x141U)
#endif
/* Symbolic Name: P20.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_2
#define PortConf_PortContainer_9_PortPin_2          ((Port_PinType) 0x143U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_3       ((Port_PinType) 0x143U)
#endif
/* Symbolic Name: P20.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_4
#define PortConf_PortContainer_9_PortPin_4          ((Port_PinType) 0x146U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_6       ((Port_PinType) 0x146U)
#endif
/* Symbolic Name: P20.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_CAN00_RXD
#define PortConf_PortContainer_9_CAN00_RXD          ((Port_PinType) 0x147U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_7       ((Port_PinType) 0x147U)
#endif
/* Symbolic Name: P20.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_CAN00_TXD
#define PortConf_PortContainer_9_CAN00_TXD          ((Port_PinType) 0x148U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_8       ((Port_PinType) 0x148U)
#endif
/* Symbolic Name: P20.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_ESPI0_SLSO1
#define PortConf_PortContainer_9_ESPI0_SLSO1          ((Port_PinType) 0x149U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_9       ((Port_PinType) 0x149U)
#endif
/* Symbolic Name: P20.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_5
#define PortConf_PortContainer_9_PortPin_5          ((Port_PinType) 0x14aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_10       ((Port_PinType) 0x14aU)
#endif
/* Symbolic Name: P20.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_ESPI0_SCLK
#define PortConf_PortContainer_9_ESPI0_SCLK          ((Port_PinType) 0x14bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_11       ((Port_PinType) 0x14bU)
#endif
/* Symbolic Name: P20.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_ESPI0_MRST
#define PortConf_PortContainer_9_ESPI0_MRST          ((Port_PinType) 0x14cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_12       ((Port_PinType) 0x14cU)
#endif
/* Symbolic Name: P20.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_13
#define PortConf_PortContainer_9_PortPin_13          ((Port_PinType) 0x14dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_13       ((Port_PinType) 0x14dU)
#endif
/* Symbolic Name: P20.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_ESPI0_MTSR
#define PortConf_PortContainer_9_ESPI0_MTSR          ((Port_PinType) 0x14eU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_14       ((Port_PinType) 0x14eU)
#endif
/* Symbolic Name: Port21 */
#ifndef PortConf_PortContainer_10
#define PortConf_PortContainer_10                    (21U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_21                             (21U)
#endif
/* Symbolic Name: P21.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_0
#define PortConf_PortContainer_10_PortPin_0          ((Port_PinType) 0x150U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_21_PIN_0       ((Port_PinType) 0x150U)
#endif
/* Symbolic Name: P21.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_1
#define PortConf_PortContainer_10_PortPin_1          ((Port_PinType) 0x151U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_21_PIN_1       ((Port_PinType) 0x151U)
#endif
/* Symbolic Name: P21.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_2
#define PortConf_PortContainer_10_PortPin_2          ((Port_PinType) 0x152U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_21_PIN_2       ((Port_PinType) 0x152U)
#endif
/* Symbolic Name: P21.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_3
#define PortConf_PortContainer_10_PortPin_3          ((Port_PinType) 0x153U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_21_PIN_3       ((Port_PinType) 0x153U)
#endif
/* Symbolic Name: P21.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_4
#define PortConf_PortContainer_10_PortPin_4          ((Port_PinType) 0x154U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_21_PIN_4       ((Port_PinType) 0x154U)
#endif
/* Symbolic Name: P21.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_5
#define PortConf_PortContainer_10_PortPin_5          ((Port_PinType) 0x155U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_21_PIN_5       ((Port_PinType) 0x155U)
#endif
/* Symbolic Name: P21.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_6
#define PortConf_PortContainer_10_PortPin_6          ((Port_PinType) 0x156U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_21_PIN_6       ((Port_PinType) 0x156U)
#endif
/* Symbolic Name: P21.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_10_PortPin_7
#define PortConf_PortContainer_10_PortPin_7          ((Port_PinType) 0x157U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_10_PORT_21_PIN_7       ((Port_PinType) 0x157U)
#endif
/* Symbolic Name: Port22 */
#ifndef PortConf_PortContainer_11
#define PortConf_PortContainer_11                    (22U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_22                             (22U)
#endif
/* Symbolic Name: P22.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_ESPI3_MTSR
#define PortConf_PortContainer_11_ESPI3_MTSR          ((Port_PinType) 0x160U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_0       ((Port_PinType) 0x160U)
#endif
/* Symbolic Name: P22.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_ESPI3_MRST
#define PortConf_PortContainer_11_ESPI3_MRST          ((Port_PinType) 0x161U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_1       ((Port_PinType) 0x161U)
#endif
/* Symbolic Name: P22.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_ESPI4_SLSO3
#define PortConf_PortContainer_11_ESPI4_SLSO3          ((Port_PinType) 0x162U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_2       ((Port_PinType) 0x162U)
#endif
/* Symbolic Name: P22.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_ESPI3_SCLK
#define PortConf_PortContainer_11_ESPI3_SCLK          ((Port_PinType) 0x163U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_3       ((Port_PinType) 0x163U)
#endif
/* Symbolic Name: P22.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_ESPI6_SLSO1
#define PortConf_PortContainer_11_ESPI6_SLSO1          ((Port_PinType) 0x164U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_4       ((Port_PinType) 0x164U)
#endif
/* Symbolic Name: P22.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_ESPI6_MTSR
#define PortConf_PortContainer_11_ESPI6_MTSR          ((Port_PinType) 0x165U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_5       ((Port_PinType) 0x165U)
#endif
/* Symbolic Name: P22.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_6
#define PortConf_PortContainer_11_PortPin_6          ((Port_PinType) 0x166U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_6       ((Port_PinType) 0x166U)
#endif
/* Symbolic Name: P22.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_ESPI6_SCLK
#define PortConf_PortContainer_11_ESPI6_SCLK          ((Port_PinType) 0x167U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_7       ((Port_PinType) 0x167U)
#endif
/* Symbolic Name: P22.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_8
#define PortConf_PortContainer_11_PortPin_8          ((Port_PinType) 0x169U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_9       ((Port_PinType) 0x169U)
#endif
/* Symbolic Name: P22.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_9
#define PortConf_PortContainer_11_PortPin_9          ((Port_PinType) 0x16aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_10       ((Port_PinType) 0x16aU)
#endif
/* Symbolic Name: P22.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_ESPI6_SLSO2
#define PortConf_PortContainer_11_ESPI6_SLSO2          ((Port_PinType) 0x16bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_11       ((Port_PinType) 0x16bU)
#endif
/* Symbolic Name: Port23 */
#ifndef PortConf_PortContainer_12
#define PortConf_PortContainer_12                    (23U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_23                             (23U)
#endif
/* Symbolic Name: P23.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_CAN10_RXD
#define PortConf_PortContainer_12_CAN10_RXD          ((Port_PinType) 0x170U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_0       ((Port_PinType) 0x170U)
#endif
/* Symbolic Name: P23.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_CAN10_TXD
#define PortConf_PortContainer_12_CAN10_TXD          ((Port_PinType) 0x171U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_1       ((Port_PinType) 0x171U)
#endif
/* Symbolic Name: P23.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_CAN12_TXD
#define PortConf_PortContainer_12_CAN12_TXD          ((Port_PinType) 0x172U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_2       ((Port_PinType) 0x172U)
#endif
/* Symbolic Name: P23.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_CAN12_RXD
#define PortConf_PortContainer_12_CAN12_RXD          ((Port_PinType) 0x173U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_3       ((Port_PinType) 0x173U)
#endif
/* Symbolic Name: P23.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_4
#define PortConf_PortContainer_12_PortPin_4          ((Port_PinType) 0x174U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_4       ((Port_PinType) 0x174U)
#endif
/* Symbolic Name: P23.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_5
#define PortConf_PortContainer_12_PortPin_5          ((Port_PinType) 0x175U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_5       ((Port_PinType) 0x175U)
#endif
/* Symbolic Name: Port32 */
#ifndef PortConf_PortContainer_13
#define PortConf_PortContainer_13                    (32U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_32                             (32U)
#endif
/* Symbolic Name: P32.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_0
#define PortConf_PortContainer_13_PortPin_0          ((Port_PinType) 0x200U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_32_PIN_0       ((Port_PinType) 0x200U)
#endif
/* Symbolic Name: P32.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_1
#define PortConf_PortContainer_13_PortPin_1          ((Port_PinType) 0x201U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_32_PIN_1       ((Port_PinType) 0x201U)
#endif
/* Symbolic Name: P32.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_2
#define PortConf_PortContainer_13_PortPin_2          ((Port_PinType) 0x202U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_32_PIN_2       ((Port_PinType) 0x202U)
#endif
/* Symbolic Name: P32.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_3
#define PortConf_PortContainer_13_PortPin_3          ((Port_PinType) 0x203U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_32_PIN_3       ((Port_PinType) 0x203U)
#endif
/* Symbolic Name: P32.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_4
#define PortConf_PortContainer_13_PortPin_4          ((Port_PinType) 0x204U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_32_PIN_4       ((Port_PinType) 0x204U)
#endif
/* Symbolic Name: Port33 */
#ifndef PortConf_PortContainer_14
#define PortConf_PortContainer_14                    (33U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_33                             (33U)
#endif
/* Symbolic Name: P33.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_ASI5_TX
#define PortConf_PortContainer_14_ASI5_TX          ((Port_PinType) 0x210U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_0       ((Port_PinType) 0x210U)
#endif
/* Symbolic Name: P33.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_SENT9
#define PortConf_PortContainer_14_SENT9          ((Port_PinType) 0x211U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_1       ((Port_PinType) 0x211U)
#endif
/* Symbolic Name: P33.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_2
#define PortConf_PortContainer_14_PortPin_2          ((Port_PinType) 0x212U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_2       ((Port_PinType) 0x212U)
#endif
/* Symbolic Name: P33.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_3
#define PortConf_PortContainer_14_PortPin_3          ((Port_PinType) 0x213U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_3       ((Port_PinType) 0x213U)
#endif
/* Symbolic Name: P33.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_ASI5_RX
#define PortConf_PortContainer_14_ASI5_RX          ((Port_PinType) 0x214U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_4       ((Port_PinType) 0x214U)
#endif
/* Symbolic Name: P33.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_SENT5
#define PortConf_PortContainer_14_SENT5          ((Port_PinType) 0x215U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_5       ((Port_PinType) 0x215U)
#endif
/* Symbolic Name: P33.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_6
#define PortConf_PortContainer_14_PortPin_6          ((Port_PinType) 0x216U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_6       ((Port_PinType) 0x216U)
#endif
/* Symbolic Name: P33.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_7
#define PortConf_PortContainer_14_PortPin_7          ((Port_PinType) 0x217U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_7       ((Port_PinType) 0x217U)
#endif
/* Symbolic Name: P33.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_8
#define PortConf_PortContainer_14_PortPin_8          ((Port_PinType) 0x218U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_8       ((Port_PinType) 0x218U)
#endif
/* Symbolic Name: P33.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_CAN01_TXD
#define PortConf_PortContainer_14_CAN01_TXD          ((Port_PinType) 0x219U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_9       ((Port_PinType) 0x219U)
#endif
/* Symbolic Name: P33.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_CAN01_RXD
#define PortConf_PortContainer_14_CAN01_RXD          ((Port_PinType) 0x21aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_10       ((Port_PinType) 0x21aU)
#endif
/* Symbolic Name: P33.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_11
#define PortConf_PortContainer_14_PortPin_11          ((Port_PinType) 0x21bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_11       ((Port_PinType) 0x21bU)
#endif
/* Symbolic Name: P33.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_12
#define PortConf_PortContainer_14_PortPin_12          ((Port_PinType) 0x21cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_12       ((Port_PinType) 0x21cU)
#endif
/* Symbolic Name: P33.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_13
#define PortConf_PortContainer_14_PortPin_13          ((Port_PinType) 0x21dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_33_PIN_13       ((Port_PinType) 0x21dU)
#endif
/* Symbolic Name: Port34 */
#ifndef PortConf_PortContainer_15
#define PortConf_PortContainer_15                    (34U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_34                             (34U)
#endif
/* Symbolic Name: P34.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_ESPI6_MRSTA
#define PortConf_PortContainer_15_ESPI6_MRSTA          ((Port_PinType) 0x222U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_34_PIN_2       ((Port_PinType) 0x222U)
#endif
/* Symbolic Name: P34.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_1
#define PortConf_PortContainer_15_PortPin_1          ((Port_PinType) 0x223U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_34_PIN_3       ((Port_PinType) 0x223U)
#endif
/* Symbolic Name: P34.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_2
#define PortConf_PortContainer_15_PortPin_2          ((Port_PinType) 0x224U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_34_PIN_4       ((Port_PinType) 0x224U)
#endif
/* Symbolic Name: Port40 */
#ifndef PortConf_PortContainer_16
#define PortConf_PortContainer_16                    (40U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_40                             (40U)
#endif
/* Symbolic Name: P40.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_0
#define PortConf_PortContainer_16_PortPin_0          ((Port_PinType) 0x280U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_0       ((Port_PinType) 0x280U)
#endif
/* Symbolic Name: P40.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_1
#define PortConf_PortContainer_16_PortPin_1          ((Port_PinType) 0x281U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_1       ((Port_PinType) 0x281U)
#endif
/* Symbolic Name: P40.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_2
#define PortConf_PortContainer_16_PortPin_2          ((Port_PinType) 0x282U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_2       ((Port_PinType) 0x282U)
#endif
/* Symbolic Name: P40.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_3
#define PortConf_PortContainer_16_PortPin_3          ((Port_PinType) 0x283U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_3       ((Port_PinType) 0x283U)
#endif
/* Symbolic Name: P40.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_4
#define PortConf_PortContainer_16_PortPin_4          ((Port_PinType) 0x284U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_4       ((Port_PinType) 0x284U)
#endif
/* Symbolic Name: P40.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_5
#define PortConf_PortContainer_16_PortPin_5          ((Port_PinType) 0x285U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_5       ((Port_PinType) 0x285U)
#endif
/* Symbolic Name: P40.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_6
#define PortConf_PortContainer_16_PortPin_6          ((Port_PinType) 0x286U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_6       ((Port_PinType) 0x286U)
#endif
/* Symbolic Name: P40.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_7
#define PortConf_PortContainer_16_PortPin_7          ((Port_PinType) 0x287U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_7       ((Port_PinType) 0x287U)
#endif
/* Symbolic Name: P40.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_8
#define PortConf_PortContainer_16_PortPin_8          ((Port_PinType) 0x288U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_8       ((Port_PinType) 0x288U)
#endif
/* Symbolic Name: P40.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_9
#define PortConf_PortContainer_16_PortPin_9          ((Port_PinType) 0x289U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_40_PIN_9       ((Port_PinType) 0x289U)
#endif

/* Generate IOM input multiplexing register configuration values */
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
#define PORT_RXMUX_IOMMON2_10_4         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_5         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_6         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_10_7         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_11_0         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_11_1         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_11_3         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_11_12        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_12_1         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_0         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_1         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_2         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_3         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_14_10        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_0         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_1         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_2         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_3         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_4         (5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_5         (6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_6         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_15_7         (5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_0         (6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_3         (7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_8         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_10        (7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_20_12        (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_21_7         (8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_22_0         (9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_22_1         (10U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_32_2         (11U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_8         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_9         (5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_12        (8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_13        (9U)
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


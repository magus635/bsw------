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
#define PORT_AVAILABEL_TOTAL_NUMBER                 (23U)

/* Definition to specify the available Alternate function register total number */
#define PORT_RXMUX_REG_TOTAL_NUMBER                 (34U)

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
#ifndef PortConf_PortContainer_0_PortPin_3
#define PortConf_PortContainer_0_PortPin_3          ((Port_PinType) 0x003U)
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
#ifndef PortConf_PortContainer_0_PortPin_6
#define PortConf_PortContainer_0_PortPin_6          ((Port_PinType) 0x006U)
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
/* Symbolic Name: P0.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_13
#define PortConf_PortContainer_0_PortPin_13          ((Port_PinType) 0x00dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_13       ((Port_PinType) 0x00dU)
#endif
/* Symbolic Name: P0.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_14
#define PortConf_PortContainer_0_PortPin_14          ((Port_PinType) 0x00eU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_14       ((Port_PinType) 0x00eU)
#endif
/* Symbolic Name: P0.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_0_PortPin_15
#define PortConf_PortContainer_0_PortPin_15          ((Port_PinType) 0x00fU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_0_PORT_0_PIN_15       ((Port_PinType) 0x00fU)
#endif
/* Symbolic Name: Port1 */
#ifndef PortConf_PortContainer_1
#define PortConf_PortContainer_1                    (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_1                             (1U)
#endif
/* Symbolic Name: P1.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_0
#define PortConf_PortContainer_1_PortPin_0          ((Port_PinType) 0x010U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_0       ((Port_PinType) 0x010U)
#endif
/* Symbolic Name: P1.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_1
#define PortConf_PortContainer_1_PortPin_1          ((Port_PinType) 0x011U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_1       ((Port_PinType) 0x011U)
#endif
/* Symbolic Name: P1.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_2
#define PortConf_PortContainer_1_PortPin_2          ((Port_PinType) 0x012U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_2       ((Port_PinType) 0x012U)
#endif
/* Symbolic Name: P1.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_3
#define PortConf_PortContainer_1_PortPin_3          ((Port_PinType) 0x013U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_3       ((Port_PinType) 0x013U)
#endif
/* Symbolic Name: P1.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_4
#define PortConf_PortContainer_1_PortPin_4          ((Port_PinType) 0x014U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_4       ((Port_PinType) 0x014U)
#endif
/* Symbolic Name: P1.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_5
#define PortConf_PortContainer_1_PortPin_5          ((Port_PinType) 0x015U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_5       ((Port_PinType) 0x015U)
#endif
/* Symbolic Name: P1.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_6
#define PortConf_PortContainer_1_PortPin_6          ((Port_PinType) 0x016U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_6       ((Port_PinType) 0x016U)
#endif
/* Symbolic Name: P1.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_7
#define PortConf_PortContainer_1_PortPin_7          ((Port_PinType) 0x017U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_7       ((Port_PinType) 0x017U)
#endif
/* Symbolic Name: P1.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_8
#define PortConf_PortContainer_1_PortPin_8          ((Port_PinType) 0x018U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_8       ((Port_PinType) 0x018U)
#endif
/* Symbolic Name: P1.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_9
#define PortConf_PortContainer_1_PortPin_9          ((Port_PinType) 0x019U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_9       ((Port_PinType) 0x019U)
#endif
/* Symbolic Name: P1.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_10
#define PortConf_PortContainer_1_PortPin_10          ((Port_PinType) 0x01aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_10       ((Port_PinType) 0x01aU)
#endif
/* Symbolic Name: P1.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_11
#define PortConf_PortContainer_1_PortPin_11          ((Port_PinType) 0x01bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_11       ((Port_PinType) 0x01bU)
#endif
/* Symbolic Name: P1.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_12
#define PortConf_PortContainer_1_PortPin_12          ((Port_PinType) 0x01cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_12       ((Port_PinType) 0x01cU)
#endif
/* Symbolic Name: P1.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_13
#define PortConf_PortContainer_1_PortPin_13          ((Port_PinType) 0x01dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_13       ((Port_PinType) 0x01dU)
#endif
/* Symbolic Name: P1.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_14
#define PortConf_PortContainer_1_PortPin_14          ((Port_PinType) 0x01eU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_14       ((Port_PinType) 0x01eU)
#endif
/* Symbolic Name: P1.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_1_PortPin_15
#define PortConf_PortContainer_1_PortPin_15          ((Port_PinType) 0x01fU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_1_PORT_1_PIN_15       ((Port_PinType) 0x01fU)
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
#ifndef PortConf_PortContainer_2_PortPin_4
#define PortConf_PortContainer_2_PortPin_4          ((Port_PinType) 0x024U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_4       ((Port_PinType) 0x024U)
#endif
/* Symbolic Name: P2.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_5
#define PortConf_PortContainer_2_PortPin_5          ((Port_PinType) 0x025U)
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
/* Symbolic Name: P2.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_9
#define PortConf_PortContainer_2_PortPin_9          ((Port_PinType) 0x029U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_9       ((Port_PinType) 0x029U)
#endif
/* Symbolic Name: P2.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_10
#define PortConf_PortContainer_2_PortPin_10          ((Port_PinType) 0x02aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_10       ((Port_PinType) 0x02aU)
#endif
/* Symbolic Name: P2.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_11
#define PortConf_PortContainer_2_PortPin_11          ((Port_PinType) 0x02bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_11       ((Port_PinType) 0x02bU)
#endif
/* Symbolic Name: P2.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_12
#define PortConf_PortContainer_2_PortPin_12          ((Port_PinType) 0x02cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_12       ((Port_PinType) 0x02cU)
#endif
/* Symbolic Name: P2.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_13
#define PortConf_PortContainer_2_PortPin_13          ((Port_PinType) 0x02dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_13       ((Port_PinType) 0x02dU)
#endif
/* Symbolic Name: P2.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_14
#define PortConf_PortContainer_2_PortPin_14          ((Port_PinType) 0x02eU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_14       ((Port_PinType) 0x02eU)
#endif
/* Symbolic Name: P2.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_2_PortPin_15
#define PortConf_PortContainer_2_PortPin_15          ((Port_PinType) 0x02fU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_2_PORT_2_PIN_15       ((Port_PinType) 0x02fU)
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
#ifndef PortConf_PortContainer_3_PortPin_4
#define PortConf_PortContainer_3_PortPin_4          ((Port_PinType) 0x0a4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_4       ((Port_PinType) 0x0a4U)
#endif
/* Symbolic Name: P10.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_ASI2_TX
#define PortConf_PortContainer_3_ASI2_TX          ((Port_PinType) 0x0a5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_5       ((Port_PinType) 0x0a5U)
#endif
/* Symbolic Name: P10.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_ASI2_RX
#define PortConf_PortContainer_3_ASI2_RX          ((Port_PinType) 0x0a6U)
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
/* Symbolic Name: P10.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_9
#define PortConf_PortContainer_3_PortPin_9          ((Port_PinType) 0x0a9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_9       ((Port_PinType) 0x0a9U)
#endif
/* Symbolic Name: P10.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_10
#define PortConf_PortContainer_3_PortPin_10          ((Port_PinType) 0x0aaU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_10       ((Port_PinType) 0x0aaU)
#endif
/* Symbolic Name: P10.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_11
#define PortConf_PortContainer_3_PortPin_11          ((Port_PinType) 0x0abU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_11       ((Port_PinType) 0x0abU)
#endif
/* Symbolic Name: P10.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_12
#define PortConf_PortContainer_3_PortPin_12          ((Port_PinType) 0x0adU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_13       ((Port_PinType) 0x0adU)
#endif
/* Symbolic Name: P10.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_13
#define PortConf_PortContainer_3_PortPin_13          ((Port_PinType) 0x0aeU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_14       ((Port_PinType) 0x0aeU)
#endif
/* Symbolic Name: P10.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_3_PortPin_14
#define PortConf_PortContainer_3_PortPin_14          ((Port_PinType) 0x0afU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_3_PORT_10_PIN_15       ((Port_PinType) 0x0afU)
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
#ifndef PortConf_PortContainer_6_PortPin_0
#define PortConf_PortContainer_6_PortPin_0          ((Port_PinType) 0x0d0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_0       ((Port_PinType) 0x0d0U)
#endif
/* Symbolic Name: P13.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_1
#define PortConf_PortContainer_6_PortPin_1          ((Port_PinType) 0x0d1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_1       ((Port_PinType) 0x0d1U)
#endif
/* Symbolic Name: P13.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_2
#define PortConf_PortContainer_6_PortPin_2          ((Port_PinType) 0x0d2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_2       ((Port_PinType) 0x0d2U)
#endif
/* Symbolic Name: P13.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_3
#define PortConf_PortContainer_6_PortPin_3          ((Port_PinType) 0x0d3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_3       ((Port_PinType) 0x0d3U)
#endif
/* Symbolic Name: P13.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_4
#define PortConf_PortContainer_6_PortPin_4          ((Port_PinType) 0x0d4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_4       ((Port_PinType) 0x0d4U)
#endif
/* Symbolic Name: P13.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_5
#define PortConf_PortContainer_6_PortPin_5          ((Port_PinType) 0x0d5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_5       ((Port_PinType) 0x0d5U)
#endif
/* Symbolic Name: P13.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_6
#define PortConf_PortContainer_6_PortPin_6          ((Port_PinType) 0x0d6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_6       ((Port_PinType) 0x0d6U)
#endif
/* Symbolic Name: P13.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_7
#define PortConf_PortContainer_6_PortPin_7          ((Port_PinType) 0x0d7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_7       ((Port_PinType) 0x0d7U)
#endif
/* Symbolic Name: P13.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_8
#define PortConf_PortContainer_6_PortPin_8          ((Port_PinType) 0x0d9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_9       ((Port_PinType) 0x0d9U)
#endif
/* Symbolic Name: P13.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_9
#define PortConf_PortContainer_6_PortPin_9          ((Port_PinType) 0x0daU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_10       ((Port_PinType) 0x0daU)
#endif
/* Symbolic Name: P13.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_10
#define PortConf_PortContainer_6_PortPin_10          ((Port_PinType) 0x0dbU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_11       ((Port_PinType) 0x0dbU)
#endif
/* Symbolic Name: P13.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_11
#define PortConf_PortContainer_6_PortPin_11          ((Port_PinType) 0x0dcU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_12       ((Port_PinType) 0x0dcU)
#endif
/* Symbolic Name: P13.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_12
#define PortConf_PortContainer_6_PortPin_12          ((Port_PinType) 0x0ddU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_13       ((Port_PinType) 0x0ddU)
#endif
/* Symbolic Name: P13.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_13
#define PortConf_PortContainer_6_PortPin_13          ((Port_PinType) 0x0deU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_14       ((Port_PinType) 0x0deU)
#endif
/* Symbolic Name: P13.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_6_PortPin_14
#define PortConf_PortContainer_6_PortPin_14          ((Port_PinType) 0x0dfU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_6_PORT_13_PIN_15       ((Port_PinType) 0x0dfU)
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
#ifndef PortConf_PortContainer_7_PortPin_3
#define PortConf_PortContainer_7_PortPin_3          ((Port_PinType) 0x0e3U)
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
/* Symbolic Name: P14.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_11
#define PortConf_PortContainer_7_PortPin_11          ((Port_PinType) 0x0ebU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_11       ((Port_PinType) 0x0ebU)
#endif
/* Symbolic Name: P14.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_12
#define PortConf_PortContainer_7_PortPin_12          ((Port_PinType) 0x0ecU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_12       ((Port_PinType) 0x0ecU)
#endif
/* Symbolic Name: P14.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_13
#define PortConf_PortContainer_7_PortPin_13          ((Port_PinType) 0x0edU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_13       ((Port_PinType) 0x0edU)
#endif
/* Symbolic Name: P14.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_14
#define PortConf_PortContainer_7_PortPin_14          ((Port_PinType) 0x0eeU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_14       ((Port_PinType) 0x0eeU)
#endif
/* Symbolic Name: P14.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_7_PortPin_15
#define PortConf_PortContainer_7_PortPin_15          ((Port_PinType) 0x0efU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_7_PORT_14_PIN_15       ((Port_PinType) 0x0efU)
#endif
/* Symbolic Name: Port15 */
#ifndef PortConf_PortContainer_8
#define PortConf_PortContainer_8                    (15U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_15                             (15U)
#endif
/* Symbolic Name: P15.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_0
#define PortConf_PortContainer_8_PortPin_0          ((Port_PinType) 0x0f0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_0       ((Port_PinType) 0x0f0U)
#endif
/* Symbolic Name: P15.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_1
#define PortConf_PortContainer_8_PortPin_1          ((Port_PinType) 0x0f1U)
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
#ifndef PortConf_PortContainer_8_I2C0_CLK
#define PortConf_PortContainer_8_I2C0_CLK          ((Port_PinType) 0x0f4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_4       ((Port_PinType) 0x0f4U)
#endif
/* Symbolic Name: P15.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_I2C0_SDA
#define PortConf_PortContainer_8_I2C0_SDA          ((Port_PinType) 0x0f5U)
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
/* Symbolic Name: P15.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_9
#define PortConf_PortContainer_8_PortPin_9          ((Port_PinType) 0x0faU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_10       ((Port_PinType) 0x0faU)
#endif
/* Symbolic Name: P15.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_10
#define PortConf_PortContainer_8_PortPin_10          ((Port_PinType) 0x0fbU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_11       ((Port_PinType) 0x0fbU)
#endif
/* Symbolic Name: P15.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_11
#define PortConf_PortContainer_8_PortPin_11          ((Port_PinType) 0x0fcU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_12       ((Port_PinType) 0x0fcU)
#endif
/* Symbolic Name: P15.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_12
#define PortConf_PortContainer_8_PortPin_12          ((Port_PinType) 0x0fdU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_13       ((Port_PinType) 0x0fdU)
#endif
/* Symbolic Name: P15.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_13
#define PortConf_PortContainer_8_PortPin_13          ((Port_PinType) 0x0feU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_14       ((Port_PinType) 0x0feU)
#endif
/* Symbolic Name: P15.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_8_PortPin_14
#define PortConf_PortContainer_8_PortPin_14          ((Port_PinType) 0x0ffU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_8_PORT_15_PIN_15       ((Port_PinType) 0x0ffU)
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
#ifndef PortConf_PortContainer_9_PortPin_3
#define PortConf_PortContainer_9_PortPin_3          ((Port_PinType) 0x146U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_6       ((Port_PinType) 0x146U)
#endif
/* Symbolic Name: P20.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_4
#define PortConf_PortContainer_9_PortPin_4          ((Port_PinType) 0x147U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_7       ((Port_PinType) 0x147U)
#endif
/* Symbolic Name: P20.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_5
#define PortConf_PortContainer_9_PortPin_5          ((Port_PinType) 0x148U)
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
#ifndef PortConf_PortContainer_9_PortPin_7
#define PortConf_PortContainer_9_PortPin_7          ((Port_PinType) 0x14aU)
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
#ifndef PortConf_PortContainer_9_ESPI0_MRSTA
#define PortConf_PortContainer_9_ESPI0_MRSTA          ((Port_PinType) 0x14cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_9_PORT_20_PIN_12       ((Port_PinType) 0x14cU)
#endif
/* Symbolic Name: P20.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_9_PortPin_10
#define PortConf_PortContainer_9_PortPin_10          ((Port_PinType) 0x14dU)
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
#ifndef PortConf_PortContainer_11_PortPin_0
#define PortConf_PortContainer_11_PortPin_0          ((Port_PinType) 0x160U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_0       ((Port_PinType) 0x160U)
#endif
/* Symbolic Name: P22.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_1
#define PortConf_PortContainer_11_PortPin_1          ((Port_PinType) 0x161U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_1       ((Port_PinType) 0x161U)
#endif
/* Symbolic Name: P22.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_2
#define PortConf_PortContainer_11_PortPin_2          ((Port_PinType) 0x162U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_2       ((Port_PinType) 0x162U)
#endif
/* Symbolic Name: P22.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_3
#define PortConf_PortContainer_11_PortPin_3          ((Port_PinType) 0x163U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_3       ((Port_PinType) 0x163U)
#endif
/* Symbolic Name: P22.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_4
#define PortConf_PortContainer_11_PortPin_4          ((Port_PinType) 0x164U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_4       ((Port_PinType) 0x164U)
#endif
/* Symbolic Name: P22.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_5
#define PortConf_PortContainer_11_PortPin_5          ((Port_PinType) 0x165U)
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
#ifndef PortConf_PortContainer_11_PortPin_7
#define PortConf_PortContainer_11_PortPin_7          ((Port_PinType) 0x167U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_7       ((Port_PinType) 0x167U)
#endif
/* Symbolic Name: P22.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_8
#define PortConf_PortContainer_11_PortPin_8          ((Port_PinType) 0x168U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_8       ((Port_PinType) 0x168U)
#endif
/* Symbolic Name: P22.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_9
#define PortConf_PortContainer_11_PortPin_9          ((Port_PinType) 0x169U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_9       ((Port_PinType) 0x169U)
#endif
/* Symbolic Name: P22.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_10
#define PortConf_PortContainer_11_PortPin_10          ((Port_PinType) 0x16aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_11_PORT_22_PIN_10       ((Port_PinType) 0x16aU)
#endif
/* Symbolic Name: P22.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_11_PortPin_11
#define PortConf_PortContainer_11_PortPin_11          ((Port_PinType) 0x16bU)
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
#ifndef PortConf_PortContainer_12_PortPin_0
#define PortConf_PortContainer_12_PortPin_0          ((Port_PinType) 0x170U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_0       ((Port_PinType) 0x170U)
#endif
/* Symbolic Name: P23.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_1
#define PortConf_PortContainer_12_PortPin_1          ((Port_PinType) 0x171U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_1       ((Port_PinType) 0x171U)
#endif
/* Symbolic Name: P23.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_2
#define PortConf_PortContainer_12_PortPin_2          ((Port_PinType) 0x172U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_2       ((Port_PinType) 0x172U)
#endif
/* Symbolic Name: P23.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_3
#define PortConf_PortContainer_12_PortPin_3          ((Port_PinType) 0x173U)
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
/* Symbolic Name: P23.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_6
#define PortConf_PortContainer_12_PortPin_6          ((Port_PinType) 0x176U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_6       ((Port_PinType) 0x176U)
#endif
/* Symbolic Name: P23.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_12_PortPin_7
#define PortConf_PortContainer_12_PortPin_7          ((Port_PinType) 0x177U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_12_PORT_23_PIN_7       ((Port_PinType) 0x177U)
#endif
/* Symbolic Name: Port24 */
#ifndef PortConf_PortContainer_13
#define PortConf_PortContainer_13                    (24U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_24                             (24U)
#endif
/* Symbolic Name: P24.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_0
#define PortConf_PortContainer_13_PortPin_0          ((Port_PinType) 0x180U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_0       ((Port_PinType) 0x180U)
#endif
/* Symbolic Name: P24.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_1
#define PortConf_PortContainer_13_PortPin_1          ((Port_PinType) 0x181U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_1       ((Port_PinType) 0x181U)
#endif
/* Symbolic Name: P24.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_2
#define PortConf_PortContainer_13_PortPin_2          ((Port_PinType) 0x182U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_2       ((Port_PinType) 0x182U)
#endif
/* Symbolic Name: P24.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_3
#define PortConf_PortContainer_13_PortPin_3          ((Port_PinType) 0x183U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_3       ((Port_PinType) 0x183U)
#endif
/* Symbolic Name: P24.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_4
#define PortConf_PortContainer_13_PortPin_4          ((Port_PinType) 0x184U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_4       ((Port_PinType) 0x184U)
#endif
/* Symbolic Name: P24.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_5
#define PortConf_PortContainer_13_PortPin_5          ((Port_PinType) 0x185U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_5       ((Port_PinType) 0x185U)
#endif
/* Symbolic Name: P24.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_6
#define PortConf_PortContainer_13_PortPin_6          ((Port_PinType) 0x186U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_6       ((Port_PinType) 0x186U)
#endif
/* Symbolic Name: P24.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_7
#define PortConf_PortContainer_13_PortPin_7          ((Port_PinType) 0x187U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_7       ((Port_PinType) 0x187U)
#endif
/* Symbolic Name: P24.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_8
#define PortConf_PortContainer_13_PortPin_8          ((Port_PinType) 0x188U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_8       ((Port_PinType) 0x188U)
#endif
/* Symbolic Name: P24.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_9
#define PortConf_PortContainer_13_PortPin_9          ((Port_PinType) 0x189U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_9       ((Port_PinType) 0x189U)
#endif
/* Symbolic Name: P24.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_10
#define PortConf_PortContainer_13_PortPin_10          ((Port_PinType) 0x18aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_10       ((Port_PinType) 0x18aU)
#endif
/* Symbolic Name: P24.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_11
#define PortConf_PortContainer_13_PortPin_11          ((Port_PinType) 0x18bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_11       ((Port_PinType) 0x18bU)
#endif
/* Symbolic Name: P24.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_12
#define PortConf_PortContainer_13_PortPin_12          ((Port_PinType) 0x18cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_12       ((Port_PinType) 0x18cU)
#endif
/* Symbolic Name: P24.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_13
#define PortConf_PortContainer_13_PortPin_13          ((Port_PinType) 0x18dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_13       ((Port_PinType) 0x18dU)
#endif
/* Symbolic Name: P24.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_14
#define PortConf_PortContainer_13_PortPin_14          ((Port_PinType) 0x18eU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_14       ((Port_PinType) 0x18eU)
#endif
/* Symbolic Name: P24.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_13_PortPin_15
#define PortConf_PortContainer_13_PortPin_15          ((Port_PinType) 0x18fU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_13_PORT_24_PIN_15       ((Port_PinType) 0x18fU)
#endif
/* Symbolic Name: Port25 */
#ifndef PortConf_PortContainer_14
#define PortConf_PortContainer_14                    (25U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_25                             (25U)
#endif
/* Symbolic Name: P25.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_0
#define PortConf_PortContainer_14_PortPin_0          ((Port_PinType) 0x190U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_0       ((Port_PinType) 0x190U)
#endif
/* Symbolic Name: P25.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_1
#define PortConf_PortContainer_14_PortPin_1          ((Port_PinType) 0x191U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_1       ((Port_PinType) 0x191U)
#endif
/* Symbolic Name: P25.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_2
#define PortConf_PortContainer_14_PortPin_2          ((Port_PinType) 0x192U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_2       ((Port_PinType) 0x192U)
#endif
/* Symbolic Name: P25.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_3
#define PortConf_PortContainer_14_PortPin_3          ((Port_PinType) 0x193U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_3       ((Port_PinType) 0x193U)
#endif
/* Symbolic Name: P25.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_4
#define PortConf_PortContainer_14_PortPin_4          ((Port_PinType) 0x194U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_4       ((Port_PinType) 0x194U)
#endif
/* Symbolic Name: P25.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_5
#define PortConf_PortContainer_14_PortPin_5          ((Port_PinType) 0x195U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_5       ((Port_PinType) 0x195U)
#endif
/* Symbolic Name: P25.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_6
#define PortConf_PortContainer_14_PortPin_6          ((Port_PinType) 0x196U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_6       ((Port_PinType) 0x196U)
#endif
/* Symbolic Name: P25.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_7
#define PortConf_PortContainer_14_PortPin_7          ((Port_PinType) 0x197U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_7       ((Port_PinType) 0x197U)
#endif
/* Symbolic Name: P25.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_8
#define PortConf_PortContainer_14_PortPin_8          ((Port_PinType) 0x198U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_8       ((Port_PinType) 0x198U)
#endif
/* Symbolic Name: P25.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_9
#define PortConf_PortContainer_14_PortPin_9          ((Port_PinType) 0x199U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_9       ((Port_PinType) 0x199U)
#endif
/* Symbolic Name: P25.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_10
#define PortConf_PortContainer_14_PortPin_10          ((Port_PinType) 0x19aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_10       ((Port_PinType) 0x19aU)
#endif
/* Symbolic Name: P25.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_11
#define PortConf_PortContainer_14_PortPin_11          ((Port_PinType) 0x19bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_11       ((Port_PinType) 0x19bU)
#endif
/* Symbolic Name: P25.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_12
#define PortConf_PortContainer_14_PortPin_12          ((Port_PinType) 0x19cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_12       ((Port_PinType) 0x19cU)
#endif
/* Symbolic Name: P25.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_13
#define PortConf_PortContainer_14_PortPin_13          ((Port_PinType) 0x19dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_13       ((Port_PinType) 0x19dU)
#endif
/* Symbolic Name: P25.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_14
#define PortConf_PortContainer_14_PortPin_14          ((Port_PinType) 0x19eU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_14       ((Port_PinType) 0x19eU)
#endif
/* Symbolic Name: P25.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_14_PortPin_15
#define PortConf_PortContainer_14_PortPin_15          ((Port_PinType) 0x19fU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_14_PORT_25_PIN_15       ((Port_PinType) 0x19fU)
#endif
/* Symbolic Name: Port26 */
#ifndef PortConf_PortContainer_15
#define PortConf_PortContainer_15                    (26U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_26                             (26U)
#endif
/* Symbolic Name: P26.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_15_PortPin_0
#define PortConf_PortContainer_15_PortPin_0          ((Port_PinType) 0x1a0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_15_PORT_26_PIN_0       ((Port_PinType) 0x1a0U)
#endif
/* Symbolic Name: Port30 */
#ifndef PortConf_PortContainer_16
#define PortConf_PortContainer_16                    (30U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_30                             (30U)
#endif
/* Symbolic Name: P30.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_0
#define PortConf_PortContainer_16_PortPin_0          ((Port_PinType) 0x1e0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_0       ((Port_PinType) 0x1e0U)
#endif
/* Symbolic Name: P30.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_1
#define PortConf_PortContainer_16_PortPin_1          ((Port_PinType) 0x1e1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_1       ((Port_PinType) 0x1e1U)
#endif
/* Symbolic Name: P30.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_2
#define PortConf_PortContainer_16_PortPin_2          ((Port_PinType) 0x1e2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_2       ((Port_PinType) 0x1e2U)
#endif
/* Symbolic Name: P30.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_3
#define PortConf_PortContainer_16_PortPin_3          ((Port_PinType) 0x1e3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_3       ((Port_PinType) 0x1e3U)
#endif
/* Symbolic Name: P30.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_4
#define PortConf_PortContainer_16_PortPin_4          ((Port_PinType) 0x1e4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_4       ((Port_PinType) 0x1e4U)
#endif
/* Symbolic Name: P30.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_5
#define PortConf_PortContainer_16_PortPin_5          ((Port_PinType) 0x1e5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_5       ((Port_PinType) 0x1e5U)
#endif
/* Symbolic Name: P30.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_6
#define PortConf_PortContainer_16_PortPin_6          ((Port_PinType) 0x1e6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_6       ((Port_PinType) 0x1e6U)
#endif
/* Symbolic Name: P30.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_7
#define PortConf_PortContainer_16_PortPin_7          ((Port_PinType) 0x1e7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_7       ((Port_PinType) 0x1e7U)
#endif
/* Symbolic Name: P30.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_8
#define PortConf_PortContainer_16_PortPin_8          ((Port_PinType) 0x1e8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_8       ((Port_PinType) 0x1e8U)
#endif
/* Symbolic Name: P30.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_9
#define PortConf_PortContainer_16_PortPin_9          ((Port_PinType) 0x1e9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_9       ((Port_PinType) 0x1e9U)
#endif
/* Symbolic Name: P30.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_10
#define PortConf_PortContainer_16_PortPin_10          ((Port_PinType) 0x1eaU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_10       ((Port_PinType) 0x1eaU)
#endif
/* Symbolic Name: P30.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_11
#define PortConf_PortContainer_16_PortPin_11          ((Port_PinType) 0x1ebU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_11       ((Port_PinType) 0x1ebU)
#endif
/* Symbolic Name: P30.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_12
#define PortConf_PortContainer_16_PortPin_12          ((Port_PinType) 0x1ecU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_12       ((Port_PinType) 0x1ecU)
#endif
/* Symbolic Name: P30.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_13
#define PortConf_PortContainer_16_PortPin_13          ((Port_PinType) 0x1edU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_13       ((Port_PinType) 0x1edU)
#endif
/* Symbolic Name: P30.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_14
#define PortConf_PortContainer_16_PortPin_14          ((Port_PinType) 0x1eeU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_14       ((Port_PinType) 0x1eeU)
#endif
/* Symbolic Name: P30.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_16_PortPin_15
#define PortConf_PortContainer_16_PortPin_15          ((Port_PinType) 0x1efU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_16_PORT_30_PIN_15       ((Port_PinType) 0x1efU)
#endif
/* Symbolic Name: Port31 */
#ifndef PortConf_PortContainer_17
#define PortConf_PortContainer_17                    (31U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_31                             (31U)
#endif
/* Symbolic Name: P31.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_0
#define PortConf_PortContainer_17_PortPin_0          ((Port_PinType) 0x1f0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_0       ((Port_PinType) 0x1f0U)
#endif
/* Symbolic Name: P31.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_1
#define PortConf_PortContainer_17_PortPin_1          ((Port_PinType) 0x1f1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_1       ((Port_PinType) 0x1f1U)
#endif
/* Symbolic Name: P31.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_2
#define PortConf_PortContainer_17_PortPin_2          ((Port_PinType) 0x1f2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_2       ((Port_PinType) 0x1f2U)
#endif
/* Symbolic Name: P31.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_3
#define PortConf_PortContainer_17_PortPin_3          ((Port_PinType) 0x1f3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_3       ((Port_PinType) 0x1f3U)
#endif
/* Symbolic Name: P31.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_4
#define PortConf_PortContainer_17_PortPin_4          ((Port_PinType) 0x1f4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_4       ((Port_PinType) 0x1f4U)
#endif
/* Symbolic Name: P31.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_5
#define PortConf_PortContainer_17_PortPin_5          ((Port_PinType) 0x1f5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_5       ((Port_PinType) 0x1f5U)
#endif
/* Symbolic Name: P31.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_6
#define PortConf_PortContainer_17_PortPin_6          ((Port_PinType) 0x1f6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_6       ((Port_PinType) 0x1f6U)
#endif
/* Symbolic Name: P31.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_7
#define PortConf_PortContainer_17_PortPin_7          ((Port_PinType) 0x1f7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_7       ((Port_PinType) 0x1f7U)
#endif
/* Symbolic Name: P31.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_8
#define PortConf_PortContainer_17_PortPin_8          ((Port_PinType) 0x1f8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_8       ((Port_PinType) 0x1f8U)
#endif
/* Symbolic Name: P31.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_9
#define PortConf_PortContainer_17_PortPin_9          ((Port_PinType) 0x1f9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_9       ((Port_PinType) 0x1f9U)
#endif
/* Symbolic Name: P31.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_10
#define PortConf_PortContainer_17_PortPin_10          ((Port_PinType) 0x1faU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_10       ((Port_PinType) 0x1faU)
#endif
/* Symbolic Name: P31.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_11
#define PortConf_PortContainer_17_PortPin_11          ((Port_PinType) 0x1fbU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_11       ((Port_PinType) 0x1fbU)
#endif
/* Symbolic Name: P31.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_12
#define PortConf_PortContainer_17_PortPin_12          ((Port_PinType) 0x1fcU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_12       ((Port_PinType) 0x1fcU)
#endif
/* Symbolic Name: P31.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_13
#define PortConf_PortContainer_17_PortPin_13          ((Port_PinType) 0x1fdU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_13       ((Port_PinType) 0x1fdU)
#endif
/* Symbolic Name: P31.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_14
#define PortConf_PortContainer_17_PortPin_14          ((Port_PinType) 0x1feU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_14       ((Port_PinType) 0x1feU)
#endif
/* Symbolic Name: P31.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_17_PortPin_15
#define PortConf_PortContainer_17_PortPin_15          ((Port_PinType) 0x1ffU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_17_PORT_31_PIN_15       ((Port_PinType) 0x1ffU)
#endif
/* Symbolic Name: Port32 */
#ifndef PortConf_PortContainer_18
#define PortConf_PortContainer_18                    (32U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_32                             (32U)
#endif
/* Symbolic Name: P32.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_18_PortPin_0
#define PortConf_PortContainer_18_PortPin_0          ((Port_PinType) 0x200U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_18_PORT_32_PIN_0       ((Port_PinType) 0x200U)
#endif
/* Symbolic Name: P32.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_18_PortPin_1
#define PortConf_PortContainer_18_PortPin_1          ((Port_PinType) 0x201U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_18_PORT_32_PIN_1       ((Port_PinType) 0x201U)
#endif
/* Symbolic Name: P32.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_18_PortPin_2
#define PortConf_PortContainer_18_PortPin_2          ((Port_PinType) 0x202U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_18_PORT_32_PIN_2       ((Port_PinType) 0x202U)
#endif
/* Symbolic Name: P32.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_18_PortPin_3
#define PortConf_PortContainer_18_PortPin_3          ((Port_PinType) 0x203U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_18_PORT_32_PIN_3       ((Port_PinType) 0x203U)
#endif
/* Symbolic Name: P32.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_18_PortPin_4
#define PortConf_PortContainer_18_PortPin_4          ((Port_PinType) 0x204U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_18_PORT_32_PIN_4       ((Port_PinType) 0x204U)
#endif
/* Symbolic Name: P32.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_18_PortPin_5
#define PortConf_PortContainer_18_PortPin_5          ((Port_PinType) 0x205U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_18_PORT_32_PIN_5       ((Port_PinType) 0x205U)
#endif
/* Symbolic Name: P32.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_18_PortPin_6
#define PortConf_PortContainer_18_PortPin_6          ((Port_PinType) 0x206U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_18_PORT_32_PIN_6       ((Port_PinType) 0x206U)
#endif
/* Symbolic Name: P32.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_18_PortPin_7
#define PortConf_PortContainer_18_PortPin_7          ((Port_PinType) 0x207U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_18_PORT_32_PIN_7       ((Port_PinType) 0x207U)
#endif
/* Symbolic Name: Port33 */
#ifndef PortConf_PortContainer_19
#define PortConf_PortContainer_19                    (33U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_33                             (33U)
#endif
/* Symbolic Name: P33.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_0
#define PortConf_PortContainer_19_PortPin_0          ((Port_PinType) 0x210U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_0       ((Port_PinType) 0x210U)
#endif
/* Symbolic Name: P33.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_1
#define PortConf_PortContainer_19_PortPin_1          ((Port_PinType) 0x211U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_1       ((Port_PinType) 0x211U)
#endif
/* Symbolic Name: P33.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_2
#define PortConf_PortContainer_19_PortPin_2          ((Port_PinType) 0x212U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_2       ((Port_PinType) 0x212U)
#endif
/* Symbolic Name: P33.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_3
#define PortConf_PortContainer_19_PortPin_3          ((Port_PinType) 0x213U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_3       ((Port_PinType) 0x213U)
#endif
/* Symbolic Name: P33.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_4
#define PortConf_PortContainer_19_PortPin_4          ((Port_PinType) 0x214U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_4       ((Port_PinType) 0x214U)
#endif
/* Symbolic Name: P33.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_5
#define PortConf_PortContainer_19_PortPin_5          ((Port_PinType) 0x215U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_5       ((Port_PinType) 0x215U)
#endif
/* Symbolic Name: P33.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_6
#define PortConf_PortContainer_19_PortPin_6          ((Port_PinType) 0x216U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_6       ((Port_PinType) 0x216U)
#endif
/* Symbolic Name: P33.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_7
#define PortConf_PortContainer_19_PortPin_7          ((Port_PinType) 0x217U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_7       ((Port_PinType) 0x217U)
#endif
/* Symbolic Name: P33.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_8
#define PortConf_PortContainer_19_PortPin_8          ((Port_PinType) 0x218U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_8       ((Port_PinType) 0x218U)
#endif
/* Symbolic Name: P33.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_9
#define PortConf_PortContainer_19_PortPin_9          ((Port_PinType) 0x219U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_9       ((Port_PinType) 0x219U)
#endif
/* Symbolic Name: P33.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_10
#define PortConf_PortContainer_19_PortPin_10          ((Port_PinType) 0x21aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_10       ((Port_PinType) 0x21aU)
#endif
/* Symbolic Name: P33.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_11
#define PortConf_PortContainer_19_PortPin_11          ((Port_PinType) 0x21bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_11       ((Port_PinType) 0x21bU)
#endif
/* Symbolic Name: P33.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_12
#define PortConf_PortContainer_19_PortPin_12          ((Port_PinType) 0x21cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_12       ((Port_PinType) 0x21cU)
#endif
/* Symbolic Name: P33.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_13
#define PortConf_PortContainer_19_PortPin_13          ((Port_PinType) 0x21dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_13       ((Port_PinType) 0x21dU)
#endif
/* Symbolic Name: P33.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_14
#define PortConf_PortContainer_19_PortPin_14          ((Port_PinType) 0x21eU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_14       ((Port_PinType) 0x21eU)
#endif
/* Symbolic Name: P33.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_19_PortPin_15
#define PortConf_PortContainer_19_PortPin_15          ((Port_PinType) 0x21fU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_19_PORT_33_PIN_15       ((Port_PinType) 0x21fU)
#endif
/* Symbolic Name: Port34 */
#ifndef PortConf_PortContainer_20
#define PortConf_PortContainer_20                    (34U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_34                             (34U)
#endif
/* Symbolic Name: P34.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_20_PortPin_0
#define PortConf_PortContainer_20_PortPin_0          ((Port_PinType) 0x221U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_20_PORT_34_PIN_1       ((Port_PinType) 0x221U)
#endif
/* Symbolic Name: P34.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_20_PortPin_1
#define PortConf_PortContainer_20_PortPin_1          ((Port_PinType) 0x222U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_20_PORT_34_PIN_2       ((Port_PinType) 0x222U)
#endif
/* Symbolic Name: P34.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_20_PortPin_2
#define PortConf_PortContainer_20_PortPin_2          ((Port_PinType) 0x223U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_20_PORT_34_PIN_3       ((Port_PinType) 0x223U)
#endif
/* Symbolic Name: P34.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_20_PortPin_3
#define PortConf_PortContainer_20_PortPin_3          ((Port_PinType) 0x224U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_20_PORT_34_PIN_4       ((Port_PinType) 0x224U)
#endif
/* Symbolic Name: P34.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_20_PortPin_4
#define PortConf_PortContainer_20_PortPin_4          ((Port_PinType) 0x225U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_20_PORT_34_PIN_5       ((Port_PinType) 0x225U)
#endif
/* Symbolic Name: Port40 */
#ifndef PortConf_PortContainer_21
#define PortConf_PortContainer_21                    (40U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_40                             (40U)
#endif
/* Symbolic Name: P40.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_0
#define PortConf_PortContainer_21_PortPin_0          ((Port_PinType) 0x280U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_0       ((Port_PinType) 0x280U)
#endif
/* Symbolic Name: P40.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_1
#define PortConf_PortContainer_21_PortPin_1          ((Port_PinType) 0x281U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_1       ((Port_PinType) 0x281U)
#endif
/* Symbolic Name: P40.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_2
#define PortConf_PortContainer_21_PortPin_2          ((Port_PinType) 0x282U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_2       ((Port_PinType) 0x282U)
#endif
/* Symbolic Name: P40.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_3
#define PortConf_PortContainer_21_PortPin_3          ((Port_PinType) 0x283U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_3       ((Port_PinType) 0x283U)
#endif
/* Symbolic Name: P40.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_4
#define PortConf_PortContainer_21_PortPin_4          ((Port_PinType) 0x284U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_4       ((Port_PinType) 0x284U)
#endif
/* Symbolic Name: P40.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_5
#define PortConf_PortContainer_21_PortPin_5          ((Port_PinType) 0x285U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_5       ((Port_PinType) 0x285U)
#endif
/* Symbolic Name: P40.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_6
#define PortConf_PortContainer_21_PortPin_6          ((Port_PinType) 0x286U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_6       ((Port_PinType) 0x286U)
#endif
/* Symbolic Name: P40.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_7
#define PortConf_PortContainer_21_PortPin_7          ((Port_PinType) 0x287U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_7       ((Port_PinType) 0x287U)
#endif
/* Symbolic Name: P40.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_8
#define PortConf_PortContainer_21_PortPin_8          ((Port_PinType) 0x288U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_8       ((Port_PinType) 0x288U)
#endif
/* Symbolic Name: P40.9
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_9
#define PortConf_PortContainer_21_PortPin_9          ((Port_PinType) 0x289U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_9       ((Port_PinType) 0x289U)
#endif
/* Symbolic Name: P40.10
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_10
#define PortConf_PortContainer_21_PortPin_10          ((Port_PinType) 0x28aU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_10       ((Port_PinType) 0x28aU)
#endif
/* Symbolic Name: P40.11
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_11
#define PortConf_PortContainer_21_PortPin_11          ((Port_PinType) 0x28bU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_11       ((Port_PinType) 0x28bU)
#endif
/* Symbolic Name: P40.12
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_12
#define PortConf_PortContainer_21_PortPin_12          ((Port_PinType) 0x28cU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_12       ((Port_PinType) 0x28cU)
#endif
/* Symbolic Name: P40.13
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_13
#define PortConf_PortContainer_21_PortPin_13          ((Port_PinType) 0x28dU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_13       ((Port_PinType) 0x28dU)
#endif
/* Symbolic Name: P40.14
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_14
#define PortConf_PortContainer_21_PortPin_14          ((Port_PinType) 0x28eU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_14       ((Port_PinType) 0x28eU)
#endif
/* Symbolic Name: P40.15
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_21_PortPin_15
#define PortConf_PortContainer_21_PortPin_15          ((Port_PinType) 0x28fU)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_21_PORT_40_PIN_15       ((Port_PinType) 0x28fU)
#endif
/* Symbolic Name: Port41 */
#ifndef PortConf_PortContainer_22
#define PortConf_PortContainer_22                    (41U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PORT_41                             (41U)
#endif
/* Symbolic Name: P41.0
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_22_PortPin_0
#define PortConf_PortContainer_22_PortPin_0          ((Port_PinType) 0x290U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_22_PORT_41_PIN_0       ((Port_PinType) 0x290U)
#endif
/* Symbolic Name: P41.1
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_22_PortPin_1
#define PortConf_PortContainer_22_PortPin_1          ((Port_PinType) 0x291U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_22_PORT_41_PIN_1       ((Port_PinType) 0x291U)
#endif
/* Symbolic Name: P41.2
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_22_PortPin_2
#define PortConf_PortContainer_22_PortPin_2          ((Port_PinType) 0x292U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_22_PORT_41_PIN_2       ((Port_PinType) 0x292U)
#endif
/* Symbolic Name: P41.3
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_22_PortPin_3
#define PortConf_PortContainer_22_PortPin_3          ((Port_PinType) 0x293U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_22_PORT_41_PIN_3       ((Port_PinType) 0x293U)
#endif
/* Symbolic Name: P41.4
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_22_PortPin_4
#define PortConf_PortContainer_22_PortPin_4          ((Port_PinType) 0x294U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_22_PORT_41_PIN_4       ((Port_PinType) 0x294U)
#endif
/* Symbolic Name: P41.5
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_22_PortPin_5
#define PortConf_PortContainer_22_PortPin_5          ((Port_PinType) 0x295U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_22_PORT_41_PIN_5       ((Port_PinType) 0x295U)
#endif
/* Symbolic Name: P41.6
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_22_PortPin_6
#define PortConf_PortContainer_22_PortPin_6          ((Port_PinType) 0x296U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_22_PORT_41_PIN_6       ((Port_PinType) 0x296U)
#endif
/* Symbolic Name: P41.7
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_22_PortPin_7
#define PortConf_PortContainer_22_PortPin_7          ((Port_PinType) 0x297U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_22_PORT_41_PIN_7       ((Port_PinType) 0x297U)
#endif
/* Symbolic Name: P41.8
The upper 8 bits are Port number(Hex), and the lower 4 bits are Pin number(Hex) */
#ifndef PortConf_PortContainer_22_PortPin_8
#define PortConf_PortContainer_22_PortPin_8          ((Port_PinType) 0x298U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PortConf_PortContainer_22_PORT_41_PIN_8       ((Port_PinType) 0x298U)
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
#define PORT_RXMUX_IOMMON1_0_0          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_1          (0U)
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
#define PORT_RXMUX_IOMMON1_0_7          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_8          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_9          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_10         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_0_12         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_0          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_1          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_2          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_3          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_4          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_5          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_6          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_7          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_2_8          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_3         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_6         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_9         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_10        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_11        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_11_12        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_14_0         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_14_1         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_4         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_5         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_6         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_7         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_15_8         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_7         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_8         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_9         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_10        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_11        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_12        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_20_13        (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_32_4         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_2         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_4         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_8         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_9         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_10        (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_11        (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_13        (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_14        (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_33_15        (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_34_1         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_34_2         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_34_3         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_34_4         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON1_34_5         (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_0_0          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_0_1          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_0_2          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_1_2          (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_1_3          (3U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_1_5          (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_1_13         (5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_2_0          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_2_2          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_2_5          (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_2_9          (6U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_2_13         (6U)
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
#define PORT_RXMUX_IOMMON2_13_9         (11U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_13_10        (6U)
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
#define PORT_RXMUX_IOMMON2_14_15        (10U)
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
#define PORT_RXMUX_IOMMON2_22_1         (0U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_22_6         (1U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_22_9         (2U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_32_2         (9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_32_3         (10U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_32_5         (7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_8         (4U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_9         (5U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_12        (8U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_33_13        (9U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_34_1         (7U)
/* #Violation: Port_Cfg_h_REF_1 */
#define PORT_RXMUX_IOMMON2_34_4         (2U)
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


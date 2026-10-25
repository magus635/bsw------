/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dio_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all configuration declarations of Dio Driver
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
*#Dio_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*/

#ifndef DIO_CFG_H_
#define DIO_CFG_H_


#include "Dio_GeneralTypes.h"



/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define DIO_CFG_AR_RELEASE_MAJOR_VERSION         (4U)
#define DIO_CFG_AR_RELEASE_MINOR_VERSION         (4U)
#define DIO_CFG_AR_RELEASE_REVISION_VERSION      (0U)

#define DIO_CFG_SW_MAJOR_VERSION                 (1U)
#define DIO_CFG_SW_MINOR_VERSION                 (2U)
#define DIO_CFG_SW_PATCH_VERSION                 (0U)

#define DIO_CFG_VENDOR_ID                        (175U) /*(0XAF)*/
#define DIO_CFG_MODULE_ID                        (120U) /*(0X78)*/

/*
Configuration: DIO_DEV_ERROR_DETECT
- if Selected, DET is Enabled 
- if Deselected, DET is Disabled 
*/
#define DIO_DEV_ERROR_DETECT                     (STD_ON)

/*
Configuration: DIO_VERSION_INFO_API 
- if Selected,  Function Dio_GetVersionInfo is available  
- if Deselected, Function Dio_GetVersionInfo is not available 
*/
#define DIO_VERSION_INFO_API                     (STD_ON)

/*
Configuration: DIO_FLIP_CHANNEL_API 
- if Selected,  Function DioFlipChannelApi is available  
- if Deselected, Function DioFlipChannelApi is not available 
*/     
#define DIO_FLIP_CHANNEL_API                     (STD_ON)

#define DIO_MASKED_WRITE_PORT_API                (STD_OFF)


/* Definition to specify the available Port total number */
#define DIO_AVAILABEL_PORT_TOTAL_NUMBER          (23U)

/* Maximum Port Number(Hex) */
#define DIO_MAX_PORT_NUMBER                      (42U)

#define DIO_PIN_MAX_NUMBER                       (16U)

/* Macro to define the maximum portPinId available */
#define DIO_MAX_AVAILABEL_PORT_PIN_ID            (0X298U)

/* Macro to define the Num of channel groups configured */
#define DIO_CHANNELGROUPCOUNT                   (2U)

/* Definition to specify the ports that are read only ports on the
   microcontroller
   Bit value = 0 implies the port readable/writable
   Bit value = 1 implies the port is read only port
   Bit 0 is for Port 0, Bit 1 is for Port 1, ... , Bit 31 is for Port 31 
*/
#define DIO_PORTS_READONLY_00_31                 (0x00000000U)
/* Definition to specify the ports that are read only ports on the
   microcontroller
   Bit value = 0 implies the port readable/writable
   Bit value = 1 implies the port is read only port
   Bit 0 is for Port 32, Bit 1 is for Port 33, ... , Bit 9 is for Port 41 
*/
#define DIO_PORTS_READONLY_32_63                 (0x00000300U)

/*
                       Symbolic names for Channels
*/
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_0                          ((Dio_ChannelType)0x000)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_1                          ((Dio_ChannelType)0x001)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_2                          ((Dio_ChannelType)0x002)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_3                          ((Dio_ChannelType)0x003)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_4                          ((Dio_ChannelType)0x004)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_5                          ((Dio_ChannelType)0x005)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_6                          ((Dio_ChannelType)0x006)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_7                          ((Dio_ChannelType)0x007)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_8                          ((Dio_ChannelType)0x008)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_9                          ((Dio_ChannelType)0x009)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_10                         ((Dio_ChannelType)0x00a)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_11                         ((Dio_ChannelType)0x00b)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_12                         ((Dio_ChannelType)0x00c)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_13                         ((Dio_ChannelType)0x00d)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_14                         ((Dio_ChannelType)0x00e)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_0_15                         ((Dio_ChannelType)0x00f)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_0                          ((Dio_ChannelType)0x010)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_1                          ((Dio_ChannelType)0x011)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_2                          ((Dio_ChannelType)0x012)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_3                          ((Dio_ChannelType)0x013)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_4                          ((Dio_ChannelType)0x014)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_5                          ((Dio_ChannelType)0x015)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_6                          ((Dio_ChannelType)0x016)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_7                          ((Dio_ChannelType)0x017)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_8                          ((Dio_ChannelType)0x018)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_9                          ((Dio_ChannelType)0x019)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_10                         ((Dio_ChannelType)0x01a)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_11                         ((Dio_ChannelType)0x01b)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_12                         ((Dio_ChannelType)0x01c)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_13                         ((Dio_ChannelType)0x01d)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_14                         ((Dio_ChannelType)0x01e)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_1_15                         ((Dio_ChannelType)0x01f)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_0                          ((Dio_ChannelType)0x020)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_1                          ((Dio_ChannelType)0x021)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_2                          ((Dio_ChannelType)0x022)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_3                          ((Dio_ChannelType)0x023)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_4                          ((Dio_ChannelType)0x024)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_5                          ((Dio_ChannelType)0x025)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_6                          ((Dio_ChannelType)0x026)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_7                          ((Dio_ChannelType)0x027)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_8                          ((Dio_ChannelType)0x028)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_9                          ((Dio_ChannelType)0x029)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_10                         ((Dio_ChannelType)0x02a)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_11                         ((Dio_ChannelType)0x02b)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_12                         ((Dio_ChannelType)0x02c)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_13                         ((Dio_ChannelType)0x02d)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_14                         ((Dio_ChannelType)0x02e)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_2_15                         ((Dio_ChannelType)0x02f)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_0                          ((Dio_ChannelType)0x0a0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_1                          ((Dio_ChannelType)0x0a1)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_2                          ((Dio_ChannelType)0x0a2)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_3                          ((Dio_ChannelType)0x0a3)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_4                          ((Dio_ChannelType)0x0a4)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_5                          ((Dio_ChannelType)0x0a5)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_6                          ((Dio_ChannelType)0x0a6)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_7                          ((Dio_ChannelType)0x0a7)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_8                          ((Dio_ChannelType)0x0a8)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_9                          ((Dio_ChannelType)0x0a9)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_10                         ((Dio_ChannelType)0x0aa)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_11                         ((Dio_ChannelType)0x0ab)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_13                         ((Dio_ChannelType)0x0ad)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_14                         ((Dio_ChannelType)0x0ae)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_10_15                         ((Dio_ChannelType)0x0af)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_0                          ((Dio_ChannelType)0x0b0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_1                          ((Dio_ChannelType)0x0b1)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_2                          ((Dio_ChannelType)0x0b2)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_3                          ((Dio_ChannelType)0x0b3)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_4                          ((Dio_ChannelType)0x0b4)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_5                          ((Dio_ChannelType)0x0b5)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_6                          ((Dio_ChannelType)0x0b6)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_7                          ((Dio_ChannelType)0x0b7)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_8                          ((Dio_ChannelType)0x0b8)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_9                          ((Dio_ChannelType)0x0b9)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_10                         ((Dio_ChannelType)0x0ba)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_11                         ((Dio_ChannelType)0x0bb)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_12                         ((Dio_ChannelType)0x0bc)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_13                         ((Dio_ChannelType)0x0bd)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_14                         ((Dio_ChannelType)0x0be)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_11_15                         ((Dio_ChannelType)0x0bf)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_12_0                          ((Dio_ChannelType)0x0c0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_12_1                          ((Dio_ChannelType)0x0c1)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_0                          ((Dio_ChannelType)0x0d0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_1                          ((Dio_ChannelType)0x0d1)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_2                          ((Dio_ChannelType)0x0d2)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_3                          ((Dio_ChannelType)0x0d3)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_4                          ((Dio_ChannelType)0x0d4)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_5                          ((Dio_ChannelType)0x0d5)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_6                          ((Dio_ChannelType)0x0d6)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_7                          ((Dio_ChannelType)0x0d7)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_9                          ((Dio_ChannelType)0x0d9)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_10                         ((Dio_ChannelType)0x0da)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_11                         ((Dio_ChannelType)0x0db)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_12                         ((Dio_ChannelType)0x0dc)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_13                         ((Dio_ChannelType)0x0dd)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_14                         ((Dio_ChannelType)0x0de)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_13_15                         ((Dio_ChannelType)0x0df)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_0                          ((Dio_ChannelType)0x0e0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_1                          ((Dio_ChannelType)0x0e1)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_2                          ((Dio_ChannelType)0x0e2)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_3                          ((Dio_ChannelType)0x0e3)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_4                          ((Dio_ChannelType)0x0e4)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_5                          ((Dio_ChannelType)0x0e5)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_6                          ((Dio_ChannelType)0x0e6)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_7                          ((Dio_ChannelType)0x0e7)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_8                          ((Dio_ChannelType)0x0e8)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_9                          ((Dio_ChannelType)0x0e9)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_10                         ((Dio_ChannelType)0x0ea)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_11                         ((Dio_ChannelType)0x0eb)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_12                         ((Dio_ChannelType)0x0ec)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_13                         ((Dio_ChannelType)0x0ed)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_14                         ((Dio_ChannelType)0x0ee)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_14_15                         ((Dio_ChannelType)0x0ef)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_0                          ((Dio_ChannelType)0x0f0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_1                          ((Dio_ChannelType)0x0f1)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_2                          ((Dio_ChannelType)0x0f2)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_3                          ((Dio_ChannelType)0x0f3)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_4                          ((Dio_ChannelType)0x0f4)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_5                          ((Dio_ChannelType)0x0f5)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_6                          ((Dio_ChannelType)0x0f6)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_7                          ((Dio_ChannelType)0x0f7)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_8                          ((Dio_ChannelType)0x0f8)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_10                         ((Dio_ChannelType)0x0fa)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_11                         ((Dio_ChannelType)0x0fb)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_12                         ((Dio_ChannelType)0x0fc)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_13                         ((Dio_ChannelType)0x0fd)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_14                         ((Dio_ChannelType)0x0fe)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_15_15                         ((Dio_ChannelType)0x0ff)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_0                          ((Dio_ChannelType)0x140)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_1                          ((Dio_ChannelType)0x141)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_3                          ((Dio_ChannelType)0x143)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_6                          ((Dio_ChannelType)0x146)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_7                          ((Dio_ChannelType)0x147)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_8                          ((Dio_ChannelType)0x148)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_9                          ((Dio_ChannelType)0x149)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_10                         ((Dio_ChannelType)0x14a)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_11                         ((Dio_ChannelType)0x14b)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_12                         ((Dio_ChannelType)0x14c)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_13                         ((Dio_ChannelType)0x14d)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_20_14                         ((Dio_ChannelType)0x14e)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_21_0                          ((Dio_ChannelType)0x150)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_21_1                          ((Dio_ChannelType)0x151)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_21_2                          ((Dio_ChannelType)0x152)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_21_3                          ((Dio_ChannelType)0x153)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_21_4                          ((Dio_ChannelType)0x154)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_21_5                          ((Dio_ChannelType)0x155)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_21_6                          ((Dio_ChannelType)0x156)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_21_7                          ((Dio_ChannelType)0x157)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_0                          ((Dio_ChannelType)0x160)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_1                          ((Dio_ChannelType)0x161)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_2                          ((Dio_ChannelType)0x162)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_3                          ((Dio_ChannelType)0x163)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_4                          ((Dio_ChannelType)0x164)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_5                          ((Dio_ChannelType)0x165)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_6                          ((Dio_ChannelType)0x166)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_7                          ((Dio_ChannelType)0x167)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_8                          ((Dio_ChannelType)0x168)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_9                          ((Dio_ChannelType)0x169)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_10                         ((Dio_ChannelType)0x16a)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_22_11                         ((Dio_ChannelType)0x16b)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_23_0                          ((Dio_ChannelType)0x170)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_23_1                          ((Dio_ChannelType)0x171)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_23_2                          ((Dio_ChannelType)0x172)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_23_3                          ((Dio_ChannelType)0x173)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_23_4                          ((Dio_ChannelType)0x174)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_23_5                          ((Dio_ChannelType)0x175)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_23_6                          ((Dio_ChannelType)0x176)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_23_7                          ((Dio_ChannelType)0x177)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_0                          ((Dio_ChannelType)0x180)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_1                          ((Dio_ChannelType)0x181)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_2                          ((Dio_ChannelType)0x182)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_3                          ((Dio_ChannelType)0x183)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_4                          ((Dio_ChannelType)0x184)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_5                          ((Dio_ChannelType)0x185)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_6                          ((Dio_ChannelType)0x186)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_7                          ((Dio_ChannelType)0x187)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_8                          ((Dio_ChannelType)0x188)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_9                          ((Dio_ChannelType)0x189)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_10                         ((Dio_ChannelType)0x18a)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_11                         ((Dio_ChannelType)0x18b)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_12                         ((Dio_ChannelType)0x18c)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_13                         ((Dio_ChannelType)0x18d)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_14                         ((Dio_ChannelType)0x18e)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_24_15                         ((Dio_ChannelType)0x18f)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_0                          ((Dio_ChannelType)0x190)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_1                          ((Dio_ChannelType)0x191)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_2                          ((Dio_ChannelType)0x192)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_3                          ((Dio_ChannelType)0x193)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_4                          ((Dio_ChannelType)0x194)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_5                          ((Dio_ChannelType)0x195)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_6                          ((Dio_ChannelType)0x196)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_7                          ((Dio_ChannelType)0x197)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_8                          ((Dio_ChannelType)0x198)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_9                          ((Dio_ChannelType)0x199)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_10                         ((Dio_ChannelType)0x19a)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_11                         ((Dio_ChannelType)0x19b)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_12                         ((Dio_ChannelType)0x19c)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_13                         ((Dio_ChannelType)0x19d)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_14                         ((Dio_ChannelType)0x19e)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_25_15                         ((Dio_ChannelType)0x19f)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_26_0                          ((Dio_ChannelType)0x1a0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_0                          ((Dio_ChannelType)0x1e0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_1                          ((Dio_ChannelType)0x1e1)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_2                          ((Dio_ChannelType)0x1e2)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_3                          ((Dio_ChannelType)0x1e3)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_4                          ((Dio_ChannelType)0x1e4)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_5                          ((Dio_ChannelType)0x1e5)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_6                          ((Dio_ChannelType)0x1e6)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_7                          ((Dio_ChannelType)0x1e7)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_8                          ((Dio_ChannelType)0x1e8)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_9                          ((Dio_ChannelType)0x1e9)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_10                         ((Dio_ChannelType)0x1ea)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_11                         ((Dio_ChannelType)0x1eb)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_12                         ((Dio_ChannelType)0x1ec)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_13                         ((Dio_ChannelType)0x1ed)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_14                         ((Dio_ChannelType)0x1ee)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_30_15                         ((Dio_ChannelType)0x1ef)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_0                          ((Dio_ChannelType)0x1f0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_1                          ((Dio_ChannelType)0x1f1)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_2                          ((Dio_ChannelType)0x1f2)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_3                          ((Dio_ChannelType)0x1f3)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_4                          ((Dio_ChannelType)0x1f4)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_5                          ((Dio_ChannelType)0x1f5)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_6                          ((Dio_ChannelType)0x1f6)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_7                          ((Dio_ChannelType)0x1f7)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_8                          ((Dio_ChannelType)0x1f8)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_9                          ((Dio_ChannelType)0x1f9)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_10                         ((Dio_ChannelType)0x1fa)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_11                         ((Dio_ChannelType)0x1fb)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_12                         ((Dio_ChannelType)0x1fc)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_13                         ((Dio_ChannelType)0x1fd)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_14                         ((Dio_ChannelType)0x1fe)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_31_15                         ((Dio_ChannelType)0x1ff)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_32_0                          ((Dio_ChannelType)0x200)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_32_1                          ((Dio_ChannelType)0x201)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_32_2                          ((Dio_ChannelType)0x202)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_32_3                          ((Dio_ChannelType)0x203)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_32_4                          ((Dio_ChannelType)0x204)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_32_5                          ((Dio_ChannelType)0x205)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_32_6                          ((Dio_ChannelType)0x206)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_32_7                          ((Dio_ChannelType)0x207)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_0                          ((Dio_ChannelType)0x210)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_1                          ((Dio_ChannelType)0x211)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_2                          ((Dio_ChannelType)0x212)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_3                          ((Dio_ChannelType)0x213)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_4                          ((Dio_ChannelType)0x214)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_5                          ((Dio_ChannelType)0x215)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_6                          ((Dio_ChannelType)0x216)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_7                          ((Dio_ChannelType)0x217)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_8                          ((Dio_ChannelType)0x218)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_9                          ((Dio_ChannelType)0x219)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_10                         ((Dio_ChannelType)0x21a)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_11                         ((Dio_ChannelType)0x21b)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_12                         ((Dio_ChannelType)0x21c)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_13                         ((Dio_ChannelType)0x21d)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_14                         ((Dio_ChannelType)0x21e)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_33_15                         ((Dio_ChannelType)0x21f)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_34_1                          ((Dio_ChannelType)0x221)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_34_2                          ((Dio_ChannelType)0x222)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_34_3                          ((Dio_ChannelType)0x223)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_34_4                          ((Dio_ChannelType)0x224)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_34_5                          ((Dio_ChannelType)0x225)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_0                          ((Dio_ChannelType)0x280)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_1                          ((Dio_ChannelType)0x281)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_2                          ((Dio_ChannelType)0x282)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_3                          ((Dio_ChannelType)0x283)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_4                          ((Dio_ChannelType)0x284)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_5                          ((Dio_ChannelType)0x285)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_6                          ((Dio_ChannelType)0x286)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_7                          ((Dio_ChannelType)0x287)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_8                          ((Dio_ChannelType)0x288)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_9                          ((Dio_ChannelType)0x289)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_10                         ((Dio_ChannelType)0x28a)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_11                         ((Dio_ChannelType)0x28b)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_12                         ((Dio_ChannelType)0x28c)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_13                         ((Dio_ChannelType)0x28d)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_14                         ((Dio_ChannelType)0x28e)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_40_15                         ((Dio_ChannelType)0x28f)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_41_0                          ((Dio_ChannelType)0x290)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_41_1                          ((Dio_ChannelType)0x291)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_41_2                          ((Dio_ChannelType)0x292)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_41_3                          ((Dio_ChannelType)0x293)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_41_4                          ((Dio_ChannelType)0x294)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_41_5                          ((Dio_ChannelType)0x295)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_41_6                          ((Dio_ChannelType)0x296)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_41_7                          ((Dio_ChannelType)0x297)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_CHANNEL_41_8                          ((Dio_ChannelType)0x298)
/*
                      Symbolic names for DIO ports
*/
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_0                                ((Dio_PortType)0)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_1                                ((Dio_PortType)1)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_2                                ((Dio_PortType)2)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_10                               ((Dio_PortType)10)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_11                               ((Dio_PortType)11)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_12                               ((Dio_PortType)12)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_13                               ((Dio_PortType)13)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_14                               ((Dio_PortType)14)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_15                               ((Dio_PortType)15)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_20                               ((Dio_PortType)20)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_21                               ((Dio_PortType)21)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_22                               ((Dio_PortType)22)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_23                               ((Dio_PortType)23)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_24                               ((Dio_PortType)24)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_25                               ((Dio_PortType)25)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_26                               ((Dio_PortType)26)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_30                               ((Dio_PortType)30)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_31                               ((Dio_PortType)31)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_32                               ((Dio_PortType)32)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_33                               ((Dio_PortType)33)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_34                               ((Dio_PortType)34)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_40                               ((Dio_PortType)40)
/* #Violation: Dio_Cfg_h_REF_1 */
#define DIO_PORT_41                               ((Dio_PortType)41)

/*
      User Defined Symbolic Names for the DIO Ports, Channels & Channel Groups
*/

/*
DIO PORT : (DioPort_14)
*/

/* To prevent double declaration */
#ifndef DioConf_DioPort_DioPort_14
#define DioConf_DioPort_DioPort_14                                 (DIO_PORT_14)
#endif
/* DIO Channel : (DIO_TEST_OUT1) */
/* To prevent double declaration */
#ifndef DioConf_DioChannel_DIO_TEST_OUT1
#define DioConf_DioChannel_DIO_TEST_OUT1                             (DIO_CHANNEL_14_3)
#endif
/* DIO Channel : (DIO_TEST_OUT2) */
/* To prevent double declaration */
#ifndef DioConf_DioChannel_DIO_TEST_OUT2
#define DioConf_DioChannel_DIO_TEST_OUT2                             (DIO_CHANNEL_14_4)
#endif
/* DIO Channel : (DIO_TEST_OUT3) */
/* To prevent double declaration */
#ifndef DioConf_DioChannel_DIO_TEST_OUT3
#define DioConf_DioChannel_DIO_TEST_OUT3                             (DIO_CHANNEL_14_5)
#endif
/* DIO Channel : (DIO_TEST_IN1) */
/* To prevent double declaration */
#ifndef DioConf_DioChannel_DIO_TEST_IN1
#define DioConf_DioChannel_DIO_TEST_IN1                             (DIO_CHANNEL_14_6)
#endif
/* DIO Channel : (DIO_TEST_IN2) */
/* To prevent double declaration */
#ifndef DioConf_DioChannel_DIO_TEST_IN2
#define DioConf_DioChannel_DIO_TEST_IN2                             (DIO_CHANNEL_14_7)
#endif
/* DIO Channel : (DIO_TEST_IN3) */
/* To prevent double declaration */
#ifndef DioConf_DioChannel_DIO_TEST_IN3
#define DioConf_DioChannel_DIO_TEST_IN3                             (DIO_CHANNEL_14_8)
#endif
/* DIO Channel : (ESPI2_SLSO) */
/* To prevent double declaration */
#ifndef DioConf_DioChannel_ESPI2_SLSO
#define DioConf_DioChannel_ESPI2_SLSO                             (DIO_CHANNEL_14_9)
#endif
/*DIO Channel Group : DIO_GROUP_TEST_OUT*/
/* To prevent double declaration */
#ifndef DioConf_DioChannelGroup_DIO_GROUP_TEST_OUT
#define DioConf_DioChannelGroup_DIO_GROUP_TEST_OUT                        (&Dio_ConfigSet.Dio_ChGroupDataPtr[0])
#endif
/*DIO Channel Group : DIO_GROUP_TEST_IN*/
/* To prevent double declaration */
#ifndef DioConf_DioChannelGroup_DIO_GROUP_TEST_IN
#define DioConf_DioChannelGroup_DIO_GROUP_TEST_IN                        (&Dio_ConfigSet.Dio_ChGroupDataPtr[1])
#endif

/*
DIO PORT : (DioPort_0)
*/

/* To prevent double declaration */
#ifndef DioConf_DioPort_DioPort_0
#define DioConf_DioPort_DioPort_0                                 (DIO_PORT_0)
#endif
/* DIO Channel : (OCU_TEST) */
/* To prevent double declaration */
#ifndef DioConf_DioChannel_OCU_TEST
#define DioConf_DioChannel_OCU_TEST                             (DIO_CHANNEL_0_2)
#endif
/* DIO Channel : (GPT_TEST) */
/* To prevent double declaration */
#ifndef DioConf_DioChannel_GPT_TEST
#define DioConf_DioChannel_GPT_TEST                             (DIO_CHANNEL_0_10)
#endif

/*
DIO PORT : (DioPort_1)
*/

/* To prevent double declaration */
#ifndef DioConf_DioPort_DioPort_1
#define DioConf_DioPort_DioPort_1                                 (DIO_PORT_1)
#endif
/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
extern const Dio_ConfigType Dio_ConfigSet;
/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

#endif /* DIO_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

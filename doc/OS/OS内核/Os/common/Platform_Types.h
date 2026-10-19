/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Platform_Types.h
*
*   Platform              : AUTOSAR
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_

/* Including the hal type header file */
#include "datatypes.h"

/***************************************************************************************************
*                               General
***************************************************************************************************/
#define CPU_TYPE_8          (8U)
#define CPU_TYPE_16         (16U)
#define CPU_TYPE_32         (32U)
#define MSB_FIRST           (0U)
#define LSB_FIRST           (1U)
#define HIGH_BYTE_FIRST     (0U)
#define LOW_BYTE_FIRST      (1U)
/***************************************************************************************************
*                               Symbols
***************************************************************************************************/
#define CPU_TYPE            CPU_TYPE_32
#define CPU_BIT_ORDER       LSB_FIRST
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST
#ifndef TRUE
#define TRUE                (1U)
#endif
#ifndef FALSE
#define FALSE               (0U)
#endif
/***************************************************************************************************
*                               Types
***************************************************************************************************/
#ifndef DATATYPES_H_

/* These types have already been defined in datatypes.h */
typedef unsigned char       boolean;
typedef signed char         sint8;
typedef unsigned char       uint8;

typedef signed short        sint16;
typedef unsigned short      uint16;

typedef signed long         sint32;
typedef unsigned long       uint32;
typedef float               float32;

typedef signed long long    sint64;
typedef double              float64;
typedef unsigned long long  uint64;

#endif /* DATATYPES_H_ */

typedef unsigned long       uint8_least;
typedef signed long         sint8_least;

typedef unsigned long       uint16_least;
typedef signed long         sint16_least;

typedef unsigned long       uint32_least;
typedef signed long         sint32_least;

/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define PLATFORM_VENDOR_ID                     175

#define PLATFORM_SW_MAJOR_VERSION              1
#define PLATFORM_SW_MINOR_VERSION              0
#define PLATFORM_SW_PATCH_VERSION              0

#endif /* PLATFORM_TYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

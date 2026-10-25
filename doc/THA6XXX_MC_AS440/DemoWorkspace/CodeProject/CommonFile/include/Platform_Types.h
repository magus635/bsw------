/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : Platform_Types.h
*
*   Platform             : AUTOSAR
*
*   brief                : This file specifies the AUTOSAR platform types header file. It contains 
*                          all platform dependent types and symbols. Those types must be abstracted in 
*                          order to become platform and compiler independent.
*
*   Autosar Version      : 4.4.0
*
*   SW Version           : 1.0.0
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
#ifndef PLATFORM_TYPES_H_
#define PLATFORM_TYPES_H_


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
   #define TRUE   1u
#endif

#ifndef FALSE
   #define FALSE  0u
#endif

/**********************************************************************************************************************
 *                                             Typdef Definitions
 *********************************************************************************************************************/
typedef unsigned char       boolean;        /* for use with TRUE/FALSE        */

/* #Violation: Platform_Types_h_REF_1 */
typedef signed char         sint8;          /*        -128 .. +127            */
/* #Violation: Platform_Types_h_REF_1 */
typedef unsigned char       uint8;          /*           0 .. 255             */
/* #Violation: Platform_Types_h_REF_1 */
typedef signed short        sint16;         /*      -32768 .. +32767          */
/* #Violation: Platform_Types_h_REF_1 */
typedef unsigned short      uint16;         /*           0 .. 65535           */
/* #Violation: Platform_Types_h_REF_1 */
typedef signed long         sint32;         /* -2147483648 .. +2147483647     */
/* #Violation: Platform_Types_h_REF_1 */
typedef unsigned long       uint32;         /*           0 .. 4294967295      */
/* #Violation: Platform_Types_h_REF_1 */
typedef signed long long    sint64;
/* #Violation: Platform_Types_h_REF_1 */
typedef unsigned long long  uint64;

/* #Violation: Platform_Types_h_REF_1 */
typedef unsigned long       uint8_least;    /* At least 8 bit                 */
/* #Violation: Platform_Types_h_REF_1 */
typedef unsigned long       uint16_least;   /* At least 16 bit                */
/* #Violation: Platform_Types_h_REF_1 */
typedef unsigned long       uint32_least;   /* At least 32 bit                */
/* #Violation: Platform_Types_h_REF_1 */
typedef signed long         sint8_least;    /* At least 7 bit + 1 bit sign    */
/* #Violation: Platform_Types_h_REF_1 */
typedef signed long         sint16_least;   /* At least 15 bit + 1 bit sign   */
/* #Violation: Platform_Types_h_REF_1 */
typedef signed long         sint32_least;   /* At least 31 bit + 1 bit sign   */

typedef float               float32;
typedef double              float64;


#endif /* PLATFORM_TYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

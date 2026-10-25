/********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: basetimer_registers.h
 * Author:   01030
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: This file contains register definitions for the base timer.
 **********************************************************************************************************************/
 /*
* #Violation Summary
*
* #basetimer_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:Using unions for bit-field access to registers.
*
* #basetimer_register_h_REF_2:MISRAC2012-Rule-4.8;
* Justification:The implementation of this structs type are used in upper layers.
*
* #basetimer_register_h_REF_3:CertC-DCL12-C;
* Justification:Apply such struct/union definitions to simplify the code structure and reduce the code complexity.
*
*/
#ifndef BASETIMER_REGISTER_H_
#define BASETIMER_REGISTER_H_
/**********************************************************************************************************************
**                                                     Includes                                                      **
**********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
**                                             Global Macro Definitions                                              **
**********************************************************************************************************************/
/*********************************************************************************************************************
**                                       BASETIMER Register Bit-Fields Definitions                                   **
*********************************************************************************************************************/
/* Basetimer Ctrl Register*/
typedef struct
{
    ureg32 ONESHOT:1;     /* [0:0]  Counter Mode: b'1 one-shot; b'0: wrap mode  (RW) */
    ureg32 SIZE:1;        /* [1:1]  Timer Size:  b'1 32-bit; b'0 16bit (RW) */
    ureg32 reserved_4:3;  /* [4:2]  Internal Reserved */
    ureg32 INTEN:1;       /* [5:5]  Interrupt Enable  (RW) */
    ureg32 MODE:1;        /* [6:6]  Timer Mode: free-running or periodic (RW) */
    ureg32 EN:1;          /* [7:7]  Timer Enable (RW) */
    ureg32 PULSEN:2;      /* [9:8]  CAN/PMC pulse enable signal, 0x11: Positive edge, other: Negative edge (RW) */
    ureg32 reserved_8:22; /* [31:10] Internal Reserved */
} BASETIMER_CTRL_Bits;

/* BaseTimer Status Clear Register */
typedef struct
{
    ureg32 CLR:1;         /* [0:0]  Clear Timer-out and interrupt status (WO) */
    ureg32 reserved_1:31; /* [31:1] Internal Reserved */
} BASETIMER_CLR_Bits;

/* BaseTimer Timer-out Interrupt Status Register */
typedef struct
{
    ureg32 INTSTS:1;      /* [0:0]  Timer-out Interrupt Status (WO) */
    ureg32 reserved_1:31; /* [31:1] Internal Reserved */
} BASETIMER_ISR_Bits;

/* BaseTimer Raw Interrupt Status Register */
typedef struct
{
    ureg32 RIS:1;         /* [0:0]  Raw Interrupt Status (WO) */
    ureg32 reserved_1:31; /* [31:1] Internal Reserved */
} BASETIMER_RIS_Bits;

/* BaseTimer Halt Register */
typedef struct
{
    ureg32 HALTEN:2;      /* [1:0]  HALT enable or disable,0x11: Positive edge, other: Negative edge (RW) */
    ureg32 reserved_1:30; /* [31:2] Reserved for future use (RO) */
} BASETIMER_HALTTIMER_Bits;

/**********************************************************************************************************************
**                                        BASETIMER Register Definitions                                             **
**********************************************************************************************************************/
typedef union
/* #Violation: basetimer_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    BASETIMER_CLR_Bits B; /* Bitfield access */
} BASETIMER_CLR;

/* BaseTimer Control Register */
typedef union
/* #Violation: basetimer_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    BASETIMER_CTRL_Bits B; /* Bitfield access */
} BASETIMER_CTRL;

/* BaseTimer Timer-out Status Register */
typedef union
/* #Violation: basetimer_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    BASETIMER_RIS_Bits B; /* Bitfield access */
} BASETIMER_RIS;

/*BaseTimer Timer-out Status Register */
typedef union
/* #Violation: basetimer_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    BASETIMER_ISR_Bits B; /* Bitfield access */
} BASETIMER_ISR;

/* BaseTimer HALT Register */
typedef union
/* #Violation: basetimer_register_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    BASETIMER_HALTTIMER_Bits B; /* Bitfield access */
} BASETIMER_HALTTIMER;

/**********************************************************************************************************************
*                                         BASETIMER Register Configuration Structure                                 **
**********************************************************************************************************************/
/* BASETIMER module struct */
/* #Violation: basetimer_register_h_REF_2 */
/* #Violation: basetimer_register_h_REF_3 */
typedef volatile struct
{
    uint32 LOAD;                   /* 0x0 BaseTimer Loading Register */
    uint32 VALUE;                  /* 0x4 BaseTimer Value Register */
    BASETIMER_CTRL CTRL;           /* 0x8 BaseTimer Control Register */
    BASETIMER_CLR CLR;             /* 0xC BaseTimer Status Clear Register */
    BASETIMER_RIS RIS;             /* 0x10 BaseTimer Raw Status Register */
    BASETIMER_ISR BTISR;           /* 0x14 BaseTimer Interrupt Status Register */
    uint32 BGLOAD;                 /* 0x18 BaseTimer Beginning Loading Register */
    BASETIMER_HALTTIMER HALTTIMER; /* 0x1C BaseTimer Halt Timer Register */
} BASETIMER_MODULE;

/**********************************************************************************************************************
 *                                                  BASETIMER Module Object
 *********************************************************************************************************************/
#endif /* BASETIMER_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

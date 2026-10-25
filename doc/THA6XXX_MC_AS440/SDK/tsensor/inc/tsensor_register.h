/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    tsensor_register.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of TSENSOR module registers.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#tsensor_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:reason 0750 Using unions for bit-field access to registers
*/
#ifndef TSENSOR_REGISTER_H_
#define TSENSOR_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        TSENSOR Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* TSENSOR RESULT Register struct */
typedef struct
{
    ureg32 RES:12;         /* [11:0] Sample result (RO) */
#if defined (THA6_THA6412) || defined (THA6_THA6104)
    ureg32 VLD:1;          /* [12:12] Valid flag of sampling result */
    ureg32 reserved_13:19; /* [31:13] Internal reserved */
#endif
#if defined (THA6_THA6206) || defined (THA6_THA6206D)
    ureg32 reserved_12:20; /* [31:12] Internal reserved */
#endif
} TSENSOR_RESULT_Bits;

/* TSENSOR STAT Register struct */
typedef struct
{
    ureg32 reserved_0:1;   /* [0:0] Internal reserved */
    ureg32 UOF:1;          /* [1:1] Temperature upper limit overflow status (RO) */
    ureg32 INT:1;          /* [2:2] Interrupt status (RO) */
    ureg32 LLU:1;          /* [3:3] Temperature lower limit overflow status (RO) */
    ureg32 ALMRES:1;       /* [4:4] Abnormal results alarm status (RO) */
    ureg32 ALMUS:1;        /* [5:5] Abnormal 1us count value alarm status (RO) */
    ureg32 ALMTHR:1;       /* [6:6] Abnormal temperature threshold alarm status (RO) */
    ureg32 ALMSFRCLR:1;    /* [7:7] Special function register of CLEAR alarm status (RO) */
    ureg32 ALMSFRSAMP:1;   /* [8:8] Special function register of SAMPLE alarm status (RO) */
    ureg32 ALMSE:1;        /* [9:9] Safe watch dog enable alarm status (RO)*/
    ureg32 ALMSFRTEST:1;   /* [10:10] Special function register of SAFE.TESTEN alarm status (RO) */
    ureg32 ALMSFRMASK:1;   /* [11:11] Special function register of MASK alarm status (RO) */
    ureg32 reserved_12:20; /* [31:12] Internal reserved */
} TSENSOR_STAT_Bits;

/* TSENSOR LIM Register struct */
typedef struct
{
    ureg32 UPPER:12;      /* [11:0] High temperature threshold (RW) */
    ureg32 reserved_12:4; /* [15:12] Internal reserved */
    ureg32 LOWER:12;      /* [27:16] Low temperature threshold (RW) */
    ureg32 reserved_28:4; /* [31:28] Internal reserved */
} TSENSOR_LIM_Bits;

/* TSENSOR SAMP Register struct */
typedef struct
{
    ureg32 USDIV:8;       /* [7:0] AHB clock counts in 1us (RW) */
    ureg32 reserved_8:8;  /* [15:8]  Internal reserved */
    ureg32 AVRTIMES:3;    /* [18:16] Average times of sample results (RW) */
    ureg32 reserved_19:1; /* [19:19] Internal reserved */
    ureg32 EN:1;             /* [20:20] TSENSOR enable (RW) */
    ureg32 INTEN:1;       /* [21:21] TSENSOR interrupt enable (RW) */
    ureg32 SLCK:1;        /* [22:22] HSM lock enable(RW) */
    ureg32 TRIG:1;        /* [23:23] TSENSOR trigger source select (RW) */
    ureg32 BYEN:1;        /* [24:24] TSENSOR bypass Enable (RW) */
    ureg32 reserved_25:7; /* [31:25] Internal reserved */
} TSENSOR_SAMP_Bits;

/* TSENSOR INTERVAL Register struct */
typedef struct
{
    ureg32 INTERVAL:32; /* [31:0] TSENSOR sample interval (RW) */
} TSENSOR_INTERVAL_Bits;

/*TSENSOR SAFE Register struct */
typedef struct
{
    ureg32 TDATA:12;       /* [11:0] Test data (RW) */
    ureg32 reserved_12:18; /* [29:12] Internal reserved */
    ureg32 TESTEN:2;       /* [31:30] Test enable (RW) */
} TSENSOR_SAFE_Bits;

/* TSENSOR ALARMMASK Register struct */
typedef struct
{
    ureg32 ALMMSK:2;       /* [1:0] Enable over/under temperature threshold alarm or not (RW) */
    ureg32 BUSERRMASK:2;   /* [3:2] Bus error mask (RW) */
    ureg32 SFRALMASK:2;   /* [5:4] Special function register alarm mask (RW) */
    ureg32 THRALMSK:2;     /* [7:6] Threshold alarm mask (RW) */
    ureg32 REALMSK:2;      /* [9:8] Result alarm mask (RW) */
    ureg32 SPALMSK:2;      /* [11:10] Spill alarm mask (RW) */
    ureg32 USALMSK:2;      /* [13:12] 1us alarm mask (RW) */
    ureg32 reserved_14:18; /* [31:14] Internal reserved */
} TSENSOR_MASK_Bits;

/* TSENSOR CLEAR Register struct */
typedef struct
{
    ureg32 reserved_0:1;    /* [0:0] Internal reserved */
    ureg32 CLRUOF:1;        /* [1:1] Clear Abnormal 1us count value alarm status (W1C) */
    ureg32 CLRINT:1;        /* [2:2] Clear Abnormal results alarm status (W1C) */
    ureg32 CLRLLU:1;        /* [3:3] Clear Temperature under low threshold status (W1C) */
    ureg32 CLRALMRES:1;     /* [4:4] Clear Interrupt status (W1C) */
    ureg32 CLRALMUS:1;      /* [5:5] Clear Temperature over high threshold status (W1C) */
    ureg32 CLRALMTHR:1;     /* [6:6] Clear TSENSOR ready status (W1C) */
    ureg32 CLRALMSFR:1;     /* [7:7] Clear alarm special function register (WO) */
    ureg32 ALMSFRSAMP:1;    /* [8:8] Clear alarm special function register sample (WO) */
    ureg32 CLRALMSE:1;      /* [9:9] Clear alarm special function register of Safe Watch Dog Enable (WO) */
    ureg32 CLRLMSFRTEST:1;  /* [10:10] Clear alarm special function register of SAFE (WO) */
    ureg32 CLRALMSFRMASK:1; /* [11:11] Clear alarm special function register of MASK (WO) */
    ureg32 reserved_12:20;  /* [31:12] Internal reserved */
} TSENSOR_CLEAR_Bits;

/* TSENSOR OFFSET Register struct */
typedef struct
{
    ureg32 OFFSET:32; /* [31:0] Offset of calibrating register (RO) */
} TSENSOR_OFFSET_Bits;

/*TSENSOR SLOPE Register struct */
typedef struct
{
    ureg32 SLOPE:32; /* [31:0] Slope register (RO) */
} TSENSOR_SLOPE_Bits;

/*TSENSOR ANGCFG Register struct */
typedef struct
{
    ureg32 QUWIN:16;       /* [15:0] Quantization Window */
    ureg32 SEL:2;          /* [17:16] Signal output mode selection */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
}TSENSOR_ANGCFG_Bits;


/**********************************************************************************************************************
 *                                           TSENSOR Register Union Definitions
 *********************************************************************************************************************/
/* TSENSOR RESULT register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    TSENSOR_RESULT_Bits B; /* Bitfield access */
} TSENSOR_RESULT;

/* TSENSOR STAT register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    TSENSOR_STAT_Bits B; /* Bitfield access */
} TSENSOR_STAT;

/* TSENSOR LIM register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    TSENSOR_LIM_Bits B; /* Bitfield access */
} TSENSOR_LIM;

/* TSENSOR SAMP register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    TSENSOR_SAMP_Bits B; /* Bitfield access */
} TSENSOR_SAMP;

/* TSENSOR INTERVAL register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    TSENSOR_INTERVAL_Bits B; /* Bitfield access */
} TSENSOR_INTERVAL;

/* TSENSOR SAFE register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    TSENSOR_SAFE_Bits B; /* Bitfield access */
} TSENSOR_SAFE;

/* TSENSOR MASK register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    TSENSOR_MASK_Bits B; /* Bitfield access */
} TSENSOR_MASK;

/* TSENSOR CLEAR register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    TSENSOR_CLEAR_Bits B; /* Bitfield access */
} TSENSOR_CLEAR;

/* TSENSOR OFFSET register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    float32 F;              /* FLoat access */
    TSENSOR_OFFSET_Bits B; /* Bitfield access */
} TSENSOR_OFFSET;

/* TSENSOR SLOPE register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    float32 F;             /* FLoat access */
    TSENSOR_SLOPE_Bits B; /* Bitfield access */
} TSENSOR_SLOPE;

/* TSENSOR SLOPE register union */
typedef union
/* #Violation: tsensor_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    float32 F;            /* FLoat access */
    TSENSOR_ANGCFG_Bits B;  /* Bitfield access */
}TSENSOR_ANGCFG;

/**********************************************************************************************************************
 *                                                TSENSOR Register Structure
 *********************************************************************************************************************/
/* TSENSOR object */
typedef volatile struct
{
    TSENSOR_RESULT RESULT;     /* 0x0 TSENSOR result register */
    TSENSOR_STAT STAT;         /* 0x4 TSENSOR state register */
    TSENSOR_LIM LIM;           /* 0x8 TSENSOR limit register */
    TSENSOR_SAMP SAMP;         /* 0xC TSENSOR sample register */
    TSENSOR_INTERVAL INTERVAL; /* 0x10 TSENSOR interval register */
    TSENSOR_SAFE SAFE;         /* 0x14 TSENSOR safe register */
    TSENSOR_MASK MASK;         /* 0x18 TSENSOR mask register */
    TSENSOR_CLEAR CLEAR;       /* 0x1C TSENSOR clear register */
    TSENSOR_OFFSET OFFSET;     /* 0x20 TSENSOR offset register */
    TSENSOR_SLOPE SLOPE;       /* 0x24 TSENSOR slope register */
    TSENSOR_ANGCFG ANGCFG;     /* 0X28 TSENSOR Analog config register */
} TSENSOR_MODULE;

#endif /* TSENSOR_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

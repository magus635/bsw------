/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    iom_register.h
 * Author:      00915
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of IOM module Registers.
 *********************************************************************************************************************/

/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
*#Violation Summary
*
*#iom_register_h_REF_1:MISRAC2012-Rule-19.2; 
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by
*               code review.
*
*/

#ifndef IOM_REGISTER_H_
#define IOM_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        IOM Register Bit-Fields Definitions
 *********************************************************************************************************************/

/* IOM Clock Control Register */
typedef struct 
{
    ureg32  reserved_0:8;        /* [7:0] Internal Reserved */
    ureg32  CKDIV:8;             /* [15:8] Clock Divider Value in RUN Mode  - RW */
    ureg32  reserved_16:16;      /* [31:16] Internal Reserved */
} IOM_CKCON_Bits;

/* IOM EMU Counter Configuration Register */
typedef struct 
{
    ureg32  CXEC0:4;             /* [3:0] Channel Mux for Event Counter 0  - RW */
    ureg32  TEC0:4;              /* [7:4] Threshold for Event Counter 0  - RW */
    ureg32  CXEC1:4;             /* [11:8] Channel Mux for Event Counter 1  - RW */
    ureg32  TEC1:4;              /* [15:12] Threshold for Event Counter 1  - RW */
    ureg32  CXEC2:4;             /* [19:16] Channel Mux for Event Counter 2  - RW */
    ureg32  TEC2:4;              /* [23:20] Threshold for Event Counter 2  - RW */
    ureg32  CXEC3:4;             /* [27:24] Channel Mux for Event Counter 3 (rw) */
    ureg32  TEC3:4;              /* [31:28] Threshold for Event Counter 3  - RW */
} IOM_EMUCCFG_Bits;

/* IOM EMU Global Event Selection Register */
typedef struct 
{
    ureg32  RCES0:1;             /* [0:0] Channel Event Select for Alarm  - RW */
    ureg32  RCES1:1;             /* [1:1] Channel Event Select for Alarm  - RW */
    ureg32  RCES2:1;             /* [2:2] Channel Event Select for Alarm  - RW */
    ureg32  RCES3:1;             /* [3:3] Channel Event Select for Alarm  - RW */
    ureg32  RCES4:1;             /* [4:4] Channel Event Select for Alarm  - RW */
    ureg32  RCES5:1;             /* [5:5] Channel Event Select for Alarm  - RW */
    ureg32  RCES6:1;             /* [6:6] Channel Event Select for Alarm  - RW */
    ureg32  RCES7:1;             /* [7:7] Channel Event Select for Alarm  - RW */
    ureg32  RCES8:1;             /* [8:8] Channel Event Select for Alarm  - RW */
    ureg32  RCES9:1;             /* [9:9] Channel Event Select for Alarm  - RW */
    ureg32  RCES10:1;            /* [10:10] Channel Event Select for Alarm  - RW */
    ureg32  RCES11:1;            /* [11:11] Channel Event Select for Alarm  - RW */
    ureg32  RCES12:1;            /* [12:12] Channel Event Select for Alarm  - RW */
    ureg32  RCES13:1;            /* [13:13] Channel Event Select for Alarm  - RW */
    ureg32  RCES14:1;            /* [14:14] Channel Event Select for Alarm  - RW */
    ureg32  RCES15:1;            /* [15:15] Channel Event Select for Alarm  - RW */
    ureg32  CCES0:1;             /* [16:16] Counted Channel Event Select for Alarm  - RW */
    ureg32  CCES1:1;             /* [17:17] Counted Channel Event Select for Alarm  - RW */
    ureg32  CCES2:1;             /* [18:18] Counted Channel Event Select for Alarm  - RW */
    ureg32  CCES3:1;             /* [19:19] Counted Channel Event Select for Alarm  - RW */
    ureg32  reserved_20:12;      /* [31:20] Internal Reserved */
} IOM_EMUESEL_Bits;

/* IOM EMU Event History Register 0 */
typedef struct 
{
    ureg32  AEH0C0:1;                /* [0:0] Alarm Triggered Event History 0 for Channel 0 - RW */
    ureg32  AEH0C1:1;                /* [1:1] Alarm Triggered Event History 0 for Channel 1 - RW */
    ureg32  AEH0C2:1;                /* [2:2] Alarm Triggered Event History 0 for Channel 2 - RW */
    ureg32  AEH0C3:1;                /* [3:3] Alarm Triggered Event History 0 for Channel 3 - RW */
    ureg32  AEH0C4:1;                /* [4:4] Alarm Triggered Event History 0 for Channel 4 - RW */
    ureg32  AEH0C5:1;                /* [5:5] Alarm Triggered Event History 0 for Channel 5 - RW */
    ureg32  AEH0C6:1;                /* [6:6] Alarm Triggered Event History 0 for Channel 6 - RW */
    ureg32  AEH0C7:1;                /* [7:7]  Alarm Triggered Event History 0 for Channel 7 - RW */
    ureg32  AEH0C8:1;                /* [8:8] Alarm Triggered Event History 0 for Channel 8 - RW */
    ureg32  AEH0C9:1;                /* [9:9]  Alarm Triggered Event History 0 for Channel 9 - RW */
    ureg32  AEH0C10:1;               /* [10:10] Alarm Triggered Event History 0 for Channel 10 - RW */
    ureg32  AEH0C11:1;               /* [11:11] Alarm Triggered Event History 0 for Channel 11 - RW */
    ureg32  AEH0C12:1;               /* [12:12] Alarm Triggered Event History 0 for Channel 12 - RW */
    ureg32  AEH0C13:1;               /* [13:13] Alarm Triggered Event History 0 for Channel 13 - RW */
    ureg32  AEH0C14:1;               /* [14:14] Alarm Triggered Event History 0 for Channel 14 - RW */
    ureg32  AEH0C15:1;               /* [15:15] Alarm Triggered Event History 0 for Channel 15 - RW */
    ureg32  AEH1C0:1;                /* [16:16] Alarm Triggered Event History 1 for Channel 0 - RW */
    ureg32  AEH1C1:1;                /* [17:17] Alarm Triggered Event History 1 for Channel 1 - RW */
    ureg32  AEH1C2:1;                /* [18:18] Alarm Triggered Event History 1 for Channel 2 - RW */
    ureg32  AEH1C3:1;                /* [19:19] Alarm Triggered Event History 1 for Channel 3 - RW */
    ureg32  AEH1C4:1;                /* [20:20] Alarm Triggered Event History 1 for Channel 4 - RW */
    ureg32  AEH1C5:1;                /* [21:21] Alarm Triggered Event History 1 for Channel 5 - RW */
    ureg32  AEH1C6:1;                /* [22:22] Alarm Triggered Event History 1 for Channel 6 - RW */
    ureg32  AEH1C7:1;                /* [23:23] Alarm Triggered Event History 1 for Channel 7 - RW */
    ureg32  AEH1C8:1;                /* [24:24] Alarm Triggered Event History 1 for Channel 8 - RW */
    ureg32  AEH1C9:1;                /* [25:25] Alarm Triggered Event History 1 for Channel 9 - RW */
    ureg32  AEH1C10:1;               /* [26:26] Alarm Triggered Event History 1 for Channel 10 - RW */
    ureg32  AEH1C11:1;               /* [27:27] Alarm Triggered Event History 1 for Channel 11 - RW */
    ureg32  AEH1C12:1;               /* [28:28] Alarm Triggered Event History 1 for Channel 12 - RW */
    ureg32  AEH1C13:1;               /* [29:29] Alarm Triggered Event History 1 for Channel 13 - RW */
    ureg32  AEH1C14:1;               /* [30:30] Alarm Triggered Event History 1 for Channel 14 - RW */
    ureg32  AEH1C15:1;               /* [31:31] Alarm Triggered Event History 1 for Channel 15 - RW */
} IOM_EMUEHR0_Bits;

/** \briefIOM EMU Event History Register 1 */
typedef struct 
{
    ureg32  AEH2C0:1;                /* [0:0] Alarm Triggered Event History 2 for Channel 0 - RW */
    ureg32  AEH2C1:1;                /* [1:1] Alarm Triggered Event History 2 for Channel 1 - RW */
    ureg32  AEH2C2:1;                /* [2:2] Alarm Triggered Event History 2 for Channel 2 - RW */
    ureg32  AEH2C3:1;                /* [3:3] Alarm Triggered Event History 2 for Channel 3 - RW */
    ureg32  AEH2C4:1;                /* [4:4] Alarm Triggered Event History 2 for Channel 4 - RW */
    ureg32  AEH2C5:1;                /* [5:5] Alarm Triggered Event History 2 for Channel 5 - RW */
    ureg32  AEH2C6:1;                /* [6:6] Alarm Triggered Event History 2 for Channel 6 - RW */
    ureg32  AEH2C7:1;                /* [7:7] Alarm Triggered Event History 2 for Channel 7 - RW */
    ureg32  AEH2C8:1;                /* [8:8] Alarm Triggered Event History 2 for Channel 8 - RW */
    ureg32  AEH2C9:1;                /* [9:9] Alarm Triggered Event History 2 for Channel 9 - RW */
    ureg32  AEH2C10:1;               /* [10:10] Alarm Triggered Event History 2 for Channel 10 - RW */
    ureg32  AEH2C11:1;               /* [11:11] Alarm Triggered Event History 2 for Channel 11 - RW */
    ureg32  AEH2C12:1;               /* [12:12] Alarm Triggered Event History 2 for Channel 12 - RW */
    ureg32  AEH2C13:1;               /* [13:13] Alarm Triggered Event History 2 for Channel 13 - RW */
    ureg32  AEH2C14:1;               /* [14:14] Alarm Triggered Event History 2 for Channel 14 - RW */
    ureg32  AEH2C15:1;               /* [15:15] Alarm Triggered Event History 2 for Channel 15 - RW */
    ureg32  AEH3C0:1;                /* [16:16] Alarm Triggered Event History 3 for Channel 0 - RW */
    ureg32  AEH3C1:1;                /* [17:17] Alarm Triggered Event History 3 for Channel 1 - RW */
    ureg32  AEH3C2:1;                /* [18:18] Alarm Triggered Event History 3 for Channel 2 - RW */
    ureg32  AEH3C3:1;                /* [19:19] Alarm Triggered Event History 3 for Channel 3 - RW */
    ureg32  AEH3C4:1;                /* [20:20] Alarm Triggered Event History 3 for Channel 4 - RW */
    ureg32  AEH3C5:1;                /* [21:21] Alarm Triggered Event History 3 for Channel 5 - RW */
    ureg32  AEH3C6:1;                /* [22:22] Alarm Triggered Event History 3 for Channel 6 - RW */
    ureg32  AEH3C7:1;                /* [23:23] Alarm Triggered Event History 3 for Channel 7 - RW */
    ureg32  AEH3C8:1;                /* [24:24] Alarm Triggered Event History 3 for Channel 8 - RW */
    ureg32  AEH3C9:1;                /* [25:25] Alarm Triggered Event History 3 for Channel 9 - RW */
    ureg32  AEH3C10:1;               /* [26:26] Alarm Triggered Event History 3 for Channel 10 - RW */
    ureg32  AEH3C11:1;               /* [27:27] Alarm Triggered Event History 3 for Channel 11 - RW */
    ureg32  AEH3C12:1;               /* [28:28] Alarm Triggered Event History 3 for Channel 12 - RW */
    ureg32  AEH3C13:1;               /* [29:29] Alarm Triggered Event History 3 for Channel 13 - RW */
    ureg32  AEH3C14:1;               /* [30:30] Alarm Triggered Event History 3 for Channel 14 - RW */
    ureg32  AEH3C15:1;               /* [31:31] Alarm Triggered Event History 3 for Channel 15 - RW */
} IOM_EMUEHR1_Bits;

/* IOM GTM Input EXOR Combiner Selection Register */
typedef struct
{
    ureg32  EN0:1;               /* [0:0] GTM input 0 selection for EXOR combiner  - RW */
    ureg32  EN1:1;               /* [1:1] GTM input 1 selection for EXOR combiner  - RW */
    ureg32  EN2:1;               /* [2:2] GTM input 2 selection for EXOR combiner  - RW */
    ureg32  EN3:1;               /* [3:3] GTM input 3 selection for EXOR combiner  - RW */
    ureg32  EN4:1;               /* [4:4] GTM input 4 selection for EXOR combiner  - RW */
    ureg32  EN5:1;               /* [5:5] GTM input 5 selection for EXOR combiner  - RW */
    ureg32  EN6:1;               /* [6:6] GTM input 6 selection for EXOR combiner  - RW */
    ureg32  EN7:1;               /* [7:7] GTM input 7 selection for EXOR combiner  - RW */
    ureg32  reserved_8:24;       /* [31:8] Internal Reserved */
} IOM_GSCCFG_Bits;

/* IOM Filter and Prescaler Channels Rising & Falling Edge Status Register */
typedef struct 
{
    ureg32  FEDC0:1;             /* [0:0] Falling Edge Glitch Flag for FPC0 - RW */
    ureg32  FEDC1:1;             /* [1:1] Falling Edge Glitch Flag for FPC1 - RW */
    ureg32  FEDC2:1;             /* [2:2] Falling Edge Glitch Flag for FPC2 - RW */
    ureg32  FEDC3:1;             /* [3:3] Falling Edge Glitch Flag for FPC3 - RW */
    ureg32  FEDC4:1;             /* [4:4] Falling Edge Glitch Flag for FPC4 - RW */
    ureg32  FEDC5:1;             /* [5:5] Falling Edge Glitch Flag for FPC5 - RW */
    ureg32  FEDC6:1;             /* [6:6] Falling Edge Glitch Flag for FPC6 - RW */
    ureg32  FEDC7:1;             /* [7:7] Falling Edge Glitch Flag for FPC7 - RW */
    ureg32  FEDC8:1;             /* [8:8] Falling Edge Glitch Flag for FPC8 - RW */
    ureg32  FEDC9:1;             /* [9:9] Falling Edge Glitch Flag for FPC9 - RW */
    ureg32  FEDC10:1;            /* [10:10] Falling Edge Glitch Flag for FPC10 - RW */
    ureg32  FEDC11:1;            /* [11:11] Falling Edge Glitch Flag for FPC11 - RW */
    ureg32  FEDC12:1;            /* [12:12] Falling Edge Glitch Flag for FPC12 - RW */
    ureg32  FEDC13:1;            /* [13:13] Falling Edge Glitch Flag for FPC13 - RW */
    ureg32  FEDC14:1;            /* [14:14] Falling Edge Glitch Flag for FPC14 - RW */
    ureg32  FEDC15:1;            /* [15:15] Falling Edge Glitch Flag for FPC15 - RW */
    ureg32  REDC0:1;             /* [16:16] Rising Edge Glitch Flag for FPC0 - RW */
    ureg32  REDC1:1;             /* [17:17] Rising Edge Glitch Flag for FPC1 - RW */
    ureg32  REDC2:1;             /* [18:18] Rising Edge Glitch Flag for FPC2 - RW */
    ureg32  REDC3:1;             /* [19:19] Rising Edge Glitch Flag for FPC3 - RW */
    ureg32  REDC4:1;             /* [20:20] Rising Edge Glitch Flag for FPC4 - RW */
    ureg32  REDC5:1;             /* [21:21] Rising Edge Glitch Flag for FPC5 - RW */
    ureg32  REDC6:1;             /* [22:22] Rising Edge Glitch Flag for FPC6 - RW */
    ureg32  REDC7:1;             /* [23:23] Rising Edge Glitch Flag for FPC7 - RW */
    ureg32  REDC8:1;             /* [24:24] Rising Edge Glitch Flag for FPC8 - RW */
    ureg32  REDC9:1;             /* [25:25] Rising Edge Glitch Flag for FPC9 - RW */
    ureg32  REDC10:1;            /* [26:26] Rising Edge Glitch Flag for FPC10 - RW */
    ureg32  REDC11:1;            /* [27:27] Rising Edge Glitch Flag for FPC11 - RW */
    ureg32  REDC12:1;            /* [28:28] Rising Edge Glitch Flag for FPC12 - RW */
    ureg32  REDC13:1;            /* [29:29] Rising Edge Glitch Flag for FPC13 - RW */
    ureg32  REDC14:1;            /* [30:30] Rising Edge Glitch Flag for FPC14 - RW */
    ureg32  REDC15:1;            /* [31:31] Rising Edge Glitch Flag for FPC15 - RW */
} IOM_PPUESTS_Bits;

/* IOM Filter and Prescaler Channel Control Register */
typedef struct 
{
    ureg32  FTHR:16;             /* [15:0] Threshold Value of Filter & Prescaler Channel  - RW */
    ureg32  OMSEL:3;             /* [18:16] Operation Mode Selection for Filter & Prescaler Channel  - RW */
    ureg32  MSEL:2;              /* [20:19] Monitor Input Signal Selection for Filter & Prescaler Channel  - RW */
    ureg32  reserved_21:1;       /* [21:21] Internal Reserved */
    ureg32  TBMOD:1;             /* [22:22] Reset Timer behavior for Filter & Prescaler Channel k on Glitch  - RW */
    ureg32  reserved_23:1;       /* [23:23] Internal Reserved */
    ureg32  RSEL:3;              /* [26:24] Reference Input Signal Selection for Filter & Prescaler Channel  - RW */
    ureg32  reserved_27:5;       /* [31:27] Internal Reserved */
} IOM_PPUCON_Bits;

/* IOM Filter and Prescaler Channel Timer Register */
typedef struct 
{
    ureg32  TVAL:16;             /* [15:0] Timer Value of Filter and Prescaler Channel  - RW */
    ureg32  reserved_16:16;      /* [31:16] Internal Reserved */
} IOM_PPUTVAL_Bits;

/* IOM Logic Analyzer Module Event Window Count Status Register */
typedef struct 
{
    ureg32  CVAL:24;             /* [23:0] Event Window Count Value MPU block  - RW */
    ureg32  reserved_24:7;       /* [30:24] Internal Reserved */
    ureg32  COVF:1;              /* [31:31] Count Overflow Flag MPU block  - RW */
} IOM_LPUEWSTS_Bits;


/* IOM Logic Analyzer Module Configuration Register*/
typedef struct 
{
    ureg32  IVR:1;               /* [0:0] Invert Reference MPU block  - RW */
    ureg32  IVM:1;               /* [1:1] Invert Monitor MPU block  - RW */
    ureg32  MSSEL:1;             /* [2:2] Monitor Source Select MPU block  - RW */
    ureg32  EMSEL:1;             /* [3:3] Runmode Select MPU block  - RW */
    ureg32  EWSEL:1;             /* [4:4] Event Window Select MPU block  - RW */
    ureg32  EDIS:1;              /* [5:5] Disable Events MPU block  - RW */
    ureg32  reserved_6:2;        /* [7:6] Internal Reserved */
    ureg32  EDS:4;               /* [11:8] Event Window Active Edge Selection MPU block  - RW */
    ureg32  IVW:1;               /* [12:12] Invert Event Window MPU block  - RW */
    ureg32  reserved_13:3;       /* [15:13] Internal Reserved */
    ureg32  MSEL:4;              /* [19:16] Monitor Input Signal Selection MPU block  - RW */
    ureg32  RSEL:4;              /* [23:20] Reference Input Signal Selection MPU block  - RW */
    ureg32  reserved_24:8;       /* [31:24] Internal Reserved */
} IOM_LPUCFG_Bits;

/* IOM Logic Analyzer Module Event Window Count Status Register */
typedef struct 
{
    ureg32  EWTHR:24;            /* [23:0] Event Window Count Value MPU block -RW */
    ureg32  reserved_24:8;       /* [31:24] Internal Reserved */
} IOM_LPUEWC_Bits;

/* IOM Functional Safety Module Status Register */
typedef struct 
{
    ureg32  DIVEP:1;             /* [0:0] CKCON.CKDIVE E Protection Flag  - RW */
    ureg32  SAFESE:1;            /* [1:1] CKCON.CKDIVE SE Protection Flag  - RW */
    ureg32  DIVALM:1;            /* [2:2] CKCON Register Monitoring Flag Bit  - RW */
    ureg32  CFGALM:1;            /* [3:3] EMUCCFG Register Monitoring Flag Bit  - RW */
    ureg32  SAFENALM:1;          /* [4:4] IOM SAFEN Register Detection Flag - RW */
    ureg32  reserved_5:27;       /* [31:5] Internal Reserved */
} IOM_SAFETYSTS_Bits;

/* IOM Safety Enable Register */
typedef struct
{
    ureg32  SAFEN:2;             /* [1:0] Redundancy Safety Mechanism Enable - RW */
    ureg32  FAULTEN:2;           /* [3:2] Redundancy Safety Mechanism Fault Injection Enable  - RW */
    ureg32  reserved_4:28;       /* [31:4] Internal Reserved */
} IOM_IOMSAFEN_Bits;

/* IOM Mask Register */
typedef struct
{
    ureg32  BEMASK:1;             /* [0:0] Bus Error Mask - RW */
    ureg32  reserved_1:31;        /* [31:1] Internal Reserved */
} IOM_IOMMASKR_Bits;
/**********************************************************************************************************************
 *                                              IOM Register Definitions
 *********************************************************************************************************************/
/* CKCON Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_CKCON_Bits B;  /* Bitfield access */
} IOM_CKCON;

/* EMUCCFG Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_EMUCCFG_Bits B;  /* Bitfield access */
} IOM_EMUCCFG;

/* EMUESEL Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_EMUESEL_Bits B;  /* Bitfield access */
} IOM_EMUESEL;

/* EMUEHR0 Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_EMUEHR0_Bits B;  /* Bitfield access */
} IOM_EMUEHR0;

/* EMUEHR1 Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_EMUEHR1_Bits B;  /* Bitfield access */
} IOM_EMUEHR1;

/* GICCFG Register (THA6412 and THA6104) */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_GSCCFG_Bits B;  /* Bitfield access */
} IOM_GSCCFG;

/* PPUESTS Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_PPUESTS_Bits B;  /* Bitfield access */
} IOM_PPUESTS;

/* FPCCTR Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_PPUCON_Bits B;  /* Bitfield access */
} IOM_PPUCON;

/* PPUTVAL Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_PPUTVAL_Bits B;  /* Bitfield access */
} IOM_PPUTVAL;

/* MPUEWSTS Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_LPUEWSTS_Bits B;  /* Bitfield access */
} IOM_LPUEWSTS;

/* MPUCFG Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_LPUCFG_Bits B;  /* Bitfield access */
} IOM_LPUCFG;

/* MPUEWC Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_LPUEWC_Bits B;  /* Bitfield access */
} IOM_LPUEWC;


/* SAFETYSTS Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned acRCESs */
    sint32 I;         /* Signed acRCESs */
    IOM_SAFETYSTS_Bits B;  /* Bitfield acRCESs */
} IOM_SAFETYSTS;

/* IOMSAFEN Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned acRCESs */
    sint32 I;         /* Signed acRCESs */
    IOM_IOMSAFEN_Bits B;  /* Bitfield acRCESs */
} IOM_IOMSAFEN;

/* IOMMASKR Register */
typedef union
/* #Violation: iom_register_h_REF_1*/
{
    uint32 U;         /* Unsigned access */
    sint32 I;         /* Signed access */
    IOM_IOMMASKR_Bits B;  /* Bitfield access */
} IOM_IOMMASKR;

/**********************************************************************************************************************
 *                                        IOM Register Configuration Structure
 *********************************************************************************************************************/
/* IOM object */
typedef volatile struct
{
    IOM_CKCON CKCON;            /* 0x0 - IOM Clock Control Register */
    ureg32 RESERVED_4[11];      /* 0x04 - Internal Reserved */
    IOM_EMUCCFG EMUCCFG;        /* 0x30 - IOM EMU Counter Configuration Register */
    IOM_EMUESEL EMUESEL;        /* 0x34 - IOM EMU Global Event Selection Register */
    IOM_EMUEHR0 EMUEHR0;        /* 0x38 - IOM EMU Event History Register 0 */
    IOM_EMUEHR1 EMUEHR1;        /* 0x3C - IOM EMU Event History Register 1 */
    IOM_GSCCFG GSCCFG;          /* 0x40 - IOM GTM Input EXOR Combiner Selection Register (THA6412 and THA6104) */
    ureg32 RESERVED_44[13];     /* 0x44 - Internal Reserved */
    IOM_PPUESTS PPUESTS;        /* 0x78 - IOM Filter and Prescaler Channels Rising & Falling Edge Status Register */
    ureg32 RESERVED_7C;         /* 0x7C - Internal Reserved */
    IOM_PPUCON  PPUCON[16];     /* 0x80 - IOM Filter and Prescaler Channel Control Register */
    IOM_PPUTVAL PPUTVAL[16];    /* 0xC0 - IOM Filter and Prescaler Channel Timer Register */
    IOM_LPUEWSTS LPUEWSTS[16];  /* 0x100 - IOM Logic Analyzer Module Event Window Count Status Register */
    ureg32 RESERVED_140[16];    /* 0x140 - Internal Reserved */
    IOM_LPUCFG LPUCFG[16];      /* 0x180 - IOM Logic Analyzer Module Configuration Register */
    IOM_LPUEWC LPUEWC[16];      /* 0x1C0 - IOM Logic Analyzer Module Event Window Count Status Register */
    IOM_SAFETYSTS SAFETYSTS;    /* 0x200 - IOM Functional Safety Module Status Register */
    IOM_IOMSAFEN IOMSAFEN;      /* 0x204 - IOM Safety Enable Register */
    IOM_IOMMASKR IOMMASKR;      /* 0x208 - IOM Mask Register */
} IOM_MODULE;

/**********************************************************************************************************************
 *                                                  IOM Module Object
 *********************************************************************************************************************/

#endif /* IOM_Register_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

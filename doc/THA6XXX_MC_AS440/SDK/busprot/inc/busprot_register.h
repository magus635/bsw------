/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: busprot_register.h
 * Author:  00930
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: BUSPROT module register definition header file.
 *             This file defines the register offsets and bit definitions for the BUSPROT module.
 ***************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#busprot_register_h_REF_1:MISRAC2012-Rule-19.2;
 * Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured
 *                by code review.
 *
 */

#ifndef BUSPROT_REGISTER_H_
#define BUSPROT_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
#include "Platform_Types.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        BUSPROT Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Identification Register */
typedef struct
{
    ureg32 MOD_DIR : 4;     /* [3:0]  Module Direction -(R) */
    ureg32 MOD_INTER : 4;   /* [7:4]  Module Interface -(R) */
    ureg32 reserved_8 : 24; /* [31:8] Internal reserved */
} BUSPROT_ID_Bits;

/* Access Enable Register */
typedef struct
{
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
    ureg32 ACCEN : 18;       /* [17:0]  Master ID access control (RW) for CHIP THA6412, [13:0] for THA6206 */
    ureg32 reserved_18 : 14; /* [31:18] Internal reserved */
#endif
#if defined(THA6_THA6104)
    ureg32 ACCEN05 : 6;      /* [5:0] Master ID (0~5) access control (RW) */
    ureg32 reserved_6 : 1;   /* [6:6] Internal reserved */
    ureg32 ACCEN7 : 1;       /* [7:7] Master ID (7) access control (RW) */
    ureg32 reserved_7 : 2;   /* [9:8] Internal reserved */
    ureg32 ACCEN1011 : 2;    /* [11:10] Master ID (10~11) access control (RW) */
    ureg32 reserved_12 : 6;  /* [17:12] Internal reserved */
    ureg32 ACCEN18 : 1;      /* [18:18] Master ID (18) access control (RW) */
    ureg32 reserved_19 : 13; /* [31:19] Internal reserved */
#endif
} BUSPROT_ACCEN_Bits;

/* Access Control Register */
typedef struct
{
    ureg32 SW_ACCEN : 2;    /* [1:0]  Software Access Enable - (RW) */
    ureg32 MIDPROT_MOD : 2; /* [3:2]  Master Id Protect Model -(RW) */
    ureg32 MIDPROT_EN : 2;  /* [5:4]  Master Id Protect Enable -(RW) */
    ureg32 reserved_6 : 26; /* [31:6] Internal reserved */
} BUSPROT_ACTRL_Bits;

/* AHB EDC PARITY Register */
typedef struct
{
    ureg32 MASTER_ERR : 2;   /* [1:0]   Master Error - (R), for CHIP THA6412 and THA6104 */
    ureg32 reserved_2 : 2;   /* [3:2]   Internal reserved */
    ureg32 SLAVE_ERR : 10;   /* [13:4]  Slave Error -(R) */
    ureg32 reserved_14 : 18; /* [31:14] Internal reserved  */
} BUSPROT_HEDCPTY_Bits;

/* AHB Error Clear Register */
typedef struct
{
    ureg32 ERR_CLR : 2;     /* [1:0]  Error Clear - (RW) */
    ureg32 reserved_2 : 30; /* [31:2]  Internal reserved  */
} BUSPROT_HERRCLR_Bits;

/* AHB Error Information Register */
typedef struct
{
    ureg32 CTRL_INFO : 14;   /* [13:0]  Control information - (R) */
    ureg32 reserved_14 : 18; /* [31:14]  Internal reserved  */
} BUSPROT_HERRINFO_Bits;

/* AHB Error Address Register */
typedef struct
{
    ureg32 ADDR : 32; /* [31:0]  AHB Error Address - (R) */
} BUSPROT_HERRADDR_Bits;

/* AHB Error Data Register */
typedef struct
{
    ureg32 DATA : 32; /* [31:0]  AHB Error Data - (R) */
} BUSPROT_HERRDATA_Bits;

/* APB and AHB EDC Parity Register */
typedef struct
{
    ureg32 EDC_ERR : 4;      /* [3:0]  EDC Error - (R) */
    ureg32 PTY_ERR : 6;      /* [9:4]  Parity Error -(R) */
    ureg32 ADR_ERR : 2;      /* [11:10]  Address EDC Error -(R) */
    ureg32 reserved_12 : 20; /* [31:12]  Internal reserved  */
} BUSPROT_PEDCPTY_Bits;

/* APB Error Clear Register */
typedef struct
{
    ureg32 ERR_CLR : 2;     /* [1:0]  Error Clear - (W) */
    ureg32 reserved_2 : 30; /* [31:2]  Internal reserved  */
} BUSPROT_PERRCLR_Bits;

/* APB Error Address Register */
typedef struct
{
    ureg32 ADDR : 32; /* [31:0]  APB Error Address - (R) */
} BUSPROT_PERRADDR_Bits;

/* APB Error Data Register */
typedef struct
{
    ureg32 DATA : 32; /* [31:0]  APB Error Data - (R) */
} BUSPROT_PERRDATA_Bits;

/* AXI Error Register */
typedef struct
{
    ureg32 MASTER_ERR : 3;  /* [2:0] Master Error - (R) */
    ureg32 reserved_3 : 1;  /* [3:3] Internal reserved */
    ureg32 SLAVE_ERR : 4;   /* [7:4] Slave Error - (R) */
    ureg32 MID_ERR : 1;     /* [8:8] Master ID Error - (R) */
    ureg32 reserved_9 : 23; /* [31:9] Internal reserved */
} BUSPROT_AERR_Bits;

/* AXI Error Clear Register */
typedef struct
{
    ureg32 ERR_CLR : 2;     /* [1:0] Error Clear - (W) */
    ureg32 reserved_2 : 30; /* [31:2] Internal reserved */
} BUSPROT_AERRCLR_Bits;

/* Fault Injection Register */
typedef struct
{
    ureg32 EDCINJEC_EN : 2; /* [1:0] EDC Fault injection enable - (RW) */
    ureg32 PTYINJEC_EN : 2; /* [3:2] Parity Fault injection enable - (RW) */
    ureg32 POSTION : 5;     /* [8:4] Postion - (RW) */
    ureg32 reserved_9 : 23; /* [31:9] Internal reserved */
} BUSPROT_FATINJCTRL_Bits;

/* Timeout Threshold Register */
typedef struct
{
    ureg32 THOLD_VAL : 32; /* [31:0] Threshold Value - (RW) */
} BUSPROT_TMOUTHOLD_Bits;

/* Timeout Control Register */
typedef struct
{
    ureg32 TMOUT_EN : 2;    /* [1:0] Timeout enable - (RW) */
    ureg32 reserved_2 : 30; /* [31:2] Internal reserved */
} BUSPROT_TMOUTCTRL_Bits;

/* Mask Register */
typedef struct
{
    ureg32 EDCPTYALM_MASK : 2; /* [1:0] EDC or Parity Alarm Mask - (RW) */
    ureg32 BERR_MASK : 2;      /* [3:2] Bus Error Mask - (RW) */
    ureg32 REDUALM_MASK : 2;   /* [5:4] Redundancy Alarm Mask - (RW) */
    ureg32 TMALM_MASK : 2;     /* [7:6] Timeout Alarm Mask - (RW) */
    ureg32 MIDALM_MASK : 2;    /* [9:8] Master Id Alarm Mask - (RW) */
    ureg32 reserved_10 : 22;   /* [31:10] Internal reserved */
} BUSPROT_MSK_Bits;

/* Alarm Clear Register */
typedef struct
{
    ureg32 SEALM_CLR : 2;    /* [1:0]  Safewdg Endinit Alarm Clear - (W) */
    ureg32 TMOUTALM_CLR : 2; /* [3:2]  Timeout Alarm Clear - (W) */
    ureg32 MIDALM_CLR : 2;   /* [5:4]  Master Id Clear - (W) */
    ureg32 REDUNALM_CLR : 2; /* [7:6]  Redundancy Alarm Clear - (W) */
    ureg32 reserved_8 : 24;  /* [31:8] Internal reserved */
} BUSPROT_ALMCLR_Bits;

/* Alarm Status Register */
typedef struct
{
    ureg32 SEALM_STS : 1;        /* [0:0] Safewdg Endinit Alarm Status - (R) */
    ureg32 TMOUTALM_STS : 1;     /* [1:1] Timeout Alarm Status - (R) */
    ureg32 MIDALM_STS : 1;       /* [2:2] Master Id Status - (R) */
    ureg32 MSKALM_STS : 1;       /* [3:3] Mask Alarm Status - (R) */
    ureg32 TMOUTCTRLALM_STS : 1; /* [4:4] TMOUTCTRL Alarm Status - (R) */
    ureg32 PERRCLRALM_STS : 1;   /* [5:5] PERRCLR Alarm Status - (R) */
    ureg32 HERRCLRALM_STS : 1;   /* [6:6] HERRCLR Alarm Status - (R) */
    ureg32 AERRCLRALM_STS : 1;   /* [7:7] AERRCLR Alarm Status - (R) */
    ureg32 ACTRLALM_STS : 1;     /* [8:8] ACTRL Alarm Status - (R) */
    ureg32 BYPASSALM_STS : 1;    /* [9:9] Bypass Alarm Status - (R) */
    ureg32 PFIJALM_STS : 1;      /* [10:10] Parity fault injection Alarm Status - (R) */
    ureg32 CLRALM_STS : 1;       /* [11:11] Clear Alarm Status - (R) */
    ureg32 reserved_12 : 20;     /* [31:12] Internal reserved */
} BUSPROT_ALMSTS_Bits;

/**********************************************************************************************************************
 *                                          BUSPROT Register Union Definitions
 *********************************************************************************************************************/
/* Identification Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    BUSPROT_ID_Bits B; /* Bitfield access */
} BUSPROT_ID;

/* Access Enable Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    BUSPROT_ACCEN_Bits B; /* Bitfield access */
} BUSPROT_ACCEN;

/* Access Control Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    BUSPROT_ACTRL_Bits B; /* Bitfield access */
} BUSPROT_ACTRL;

/* AHB EDC PARITY Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    BUSPROT_HEDCPTY_Bits B; /* Bitfield access */
} BUSPROT_HEDCPTY;

/* AHB Error Clear Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    BUSPROT_HERRCLR_Bits B; /* Bitfield access */
} BUSPROT_HERRCLR;

/* AHB Error Information Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    BUSPROT_HERRINFO_Bits B; /* Bitfield access */
} BUSPROT_HERRINFO;

/* AHB Error Address Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    BUSPROT_HERRADDR_Bits B; /* Bitfield access */
} BUSPROT_HERRADDR;

/* AHB Error Data Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    BUSPROT_HERRDATA_Bits B; /* Bitfield access */
} BUSPROT_HERRDATA;

/* APB and AHB EDC Parity Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    BUSPROT_PEDCPTY_Bits B; /* Bitfield access */
} BUSPROT_PEDCPTY;

/* APB Error Clear Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    BUSPROT_PERRCLR_Bits B; /* Bitfield access */
} BUSPROT_PERRCLR;

/* APB Error Address Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    BUSPROT_PERRADDR_Bits B; /* Bitfield access */
} BUSPROT_PERRADDR;

/* APB Error Data Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    BUSPROT_PERRDATA_Bits B; /* Bitfield access */
} BUSPROT_PERRDATA;

/* AXI Error Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    BUSPROT_AERR_Bits B; /* Bitfield access */
} BUSPROT_AERR;

/* AXI Error Clear Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    BUSPROT_AERRCLR_Bits B; /* Bitfield access */
} BUSPROT_AERRCLR;

/* Fault Injection Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    BUSPROT_FATINJCTRL_Bits B; /* Bitfield access */
} BUSPROT_FATINJCTRL;

/* Timeout Threshold Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    BUSPROT_TMOUTHOLD_Bits B; /* Bitfield access */
} BUSPROT_TMOUTHOLD;

/* Timeout Control Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    BUSPROT_TMOUTCTRL_Bits B; /* Bitfield access */
} BUSPROT_TMOUTCTRL;

/* Mask Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    BUSPROT_MSK_Bits B; /* Bitfield access */
} BUSPROT_MSK;

/* Alarm Clear Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    BUSPROT_ALMCLR_Bits B; /* Bitfield access */
} BUSPROT_ALMCLR;

/* Alarm Status Register */
typedef union
/* #Violation: busprot_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    BUSPROT_ALMSTS_Bits B; /* Bitfield access */
} BUSPROT_ALMSTS;

/**********************************************************************************************************************
 *                                               BUSPROT Register Structure
 *********************************************************************************************************************/
typedef volatile struct
{
    BUSPROT_ID ID;                 /* 0, Identification Register  */
    BUSPROT_ACCEN ACCEN;           /* 4,  Access Enable Register */
    uint8 reserved_C[4];           /* 8, internal Reserved */
    BUSPROT_ACTRL ACTRL;           /* C, Access Control Register */
    BUSPROT_HEDCPTY HEDCPTY;       /* 10, AHB EDC PARITY Register */
    BUSPROT_HERRCLR HERRCLR;       /* 14, AHB Error Clear Register */
    BUSPROT_HERRINFO HERRINFO;     /* 18, AHB Error Information Register */
    BUSPROT_HERRADDR HERRADDR;     /* 1C, AHB Error Address Register  */
    BUSPROT_HERRDATA HERRDATA;     /* 20, AHB Error Data Register */
    BUSPROT_PEDCPTY PEDCPTY;       /* 24, APB and AHB EDC Parity Register */
    BUSPROT_PERRCLR PERRCLR;       /* 28, APB Error Clear Register */
    BUSPROT_PERRADDR PERRADDR;     /* 2C, APB Error Address Register */
    BUSPROT_PERRDATA PERRDATA;     /* 30, APB Error Data Register */
    BUSPROT_AERR AERR;             /* 34, AXI Error Register */
    BUSPROT_AERRCLR AERRCLR;       /* 38, AXI Error Clear Register */
    BUSPROT_FATINJCTRL FATINJCTRL; /* 3C, Fault Injection Register */
    BUSPROT_TMOUTHOLD TMOUTHOLD;   /* 40, Timeout Threshold Register */
    BUSPROT_TMOUTCTRL TMOUTCTRL;   /* 44, Timeout Control Register */
    BUSPROT_MSK MSK;               /* 48, Mask Register */
    BUSPROT_ALMCLR ALMCLR;         /* 4C, Alarm Clear Register */
    BUSPROT_ALMSTS ALMSTS;         /* 50, Alarm Status Register */
} BUSPROT_MODULE;

#endif /* BUSPROT_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

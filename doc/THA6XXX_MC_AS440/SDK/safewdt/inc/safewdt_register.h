/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    safewdt_register.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of SAFEWDT module registers.
 *********************************************************************************************************************/

/*
* #Violation Summary
*
*#safewdt_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by
*               code review.
*
*/

#ifndef SAFEWDT_REGISTER_H_
#define SAFEWDT_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                      SAFEWDT Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Password0 register */
typedef struct
{
    ureg32 PW0:14;         /* [13:0] PW0 permission password - RW */
    ureg32 reserved_14:18; /* [31:14] Internal reserved */
} SAFEWDT_PW0_Bits;

/* Password lock register */
typedef struct
{
    ureg32 PW0LCK:1;      /* [0:0] PW0 locking signal - RW */
    ureg32 SEPWLCK:1;     /* [1:1] PWSE locking signal - RW */
    ureg32 WDTPWLCK:1;    /* [2:2] PWWDT locking signal - RW */
    ureg32 reserved_3:29; /* [31:3] Internal Reserved */
} SAFEWDT_PWLOCK_Bits;

/* PWSE/PWWDT password mode selection and initial password register */
typedef struct
{
    ureg32 WDTPWINIT:14; /* [13:0] WDTPW Initialization password - RW */
    ureg32 WDTPWM:2;     /* [15:14] WDTPWM Mode Selection - RW */
    ureg32 SEPWINIT:14;  /* [29:16] SEPW Initialization Password - RW */
    ureg32 SEPWM:2;      /* [31:30] SEPW Mode Selection - RW */
} SAFEWDT_PWMAI_Bits;

/* PW0 password unlocking validity period register */
typedef struct
{
    ureg32 PW0CNT:16;      /* [15:0] PW0 Unlocked Counter Threshold - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} SAFEWDT_PW0CNT_Bits;

/* Clock management register */
typedef struct
{
    ureg32 WDTCLKDIV:3;   /* [2:0] WDT clock frequency division coefficient - RW */
    ureg32 SECLKDIV:3;    /* [5:3] SE clock frequency division - RW */
    ureg32 LPSEN:1;       /* [6:6] Low Power Signal Enable - RW */
    ureg32 reserved_7:25; /* [31:7] Internal reserved */
} SAFEWDT_CLKMNG_Bits;

/* Output mode register */
typedef struct
{
    ureg32 SEOUTM:1;      /* [0:0] SE permission error output mode selection
                             (0:alarm, 1:interrupt) - RW */
    ureg32 WDTOUTM1:1;    /* [1:1] WDT feeding dog error output mode selection for first
                             period(0:alarm,1:interrupt) - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} SAFEWDT_OUTM_Bits;

/* SAFECPU id register */
typedef struct
{
    ureg32 SAFECOREID:2;  /* [1:0] Safety core id(00:CPU0,01:CPU1,other:none) - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} SAFEWDT_SAFECPUID_Bits;

/* SAFEWDT status register */
typedef struct
{
    ureg32 WDTLPI:1;       /* [0:0] WDT Low Power Indication - RO */
    ureg32 SWMLPI:1;       /* [1:1] SAFEWDT Module Low Power Indication - RO */
    ureg32 PW0STS:1;       /* [2:2] Indicate PW0 successfully unlocked - RO */
    ureg32 SEPWSTS:1;      /* [3:3] Indicate PWSE successfully unlocked - RO */
    ureg32 WDTPWSTS:1;     /* [4:4] Indicate PWWDT successfully unlocked - RO */
    ureg32 reserved_5:27;  /* [31:5] Internal reserved */
} SAFEWDT_SWSTS_Bits;

/* SAFEWDT alarm status register */
typedef struct
{
    ureg32 SEALM:1;       /* [0:0] SE permission error alarm - RO */
    ureg32 WDTALM1:1;     /* [1:1] WDT feeding dog error alarm for first period - RO */
    ureg32 WDTALM2:1;     /* [2:2] WDT feeding dog error alarm for second period - RO */
    ureg32 SWALM:1;       /* [3:3] Security function mechanism error alarm, PW0/PWSE/PWWDT
                             error alarm - RO */
    ureg32 SWREGALM:1;    /* [4:4] Register error alarm (dual bit redundancy) - RO */
    ureg32 reserved_5:27; /* [31:5] Internal reserved */
} SAFEWDT_SWALMSTS_Bits;

/* SAFEWDT interrupt status register */
typedef struct
{
    ureg32 SEINT:1;       /* [0:0] Indicate that SE interrupt will generate - RO */
    ureg32 WDTINT1:1;     /* [1:1] WDT feeding dog error interrupt for first period - RO */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} SAFEWDT_SWINTSTS_Bits;

/* SAFEWDT alarm/interrupt enable register */
typedef struct
{
    ureg32 SEALME:2;       /* [1:0] SE alarm enable - RW */
    ureg32 SEINTE:2;       /* [3:2] SE interrupt enable - RW */
    ureg32 WDTALME1:2;     /* [5:4] WDT feeding dog error alarm enable for first period
                              - RW */
    ureg32 WDTINTE1:2;     /* [7:6] WDT feeding dog error interrupt enable for first period
                              - RO */
    ureg32 WDTALME2:2;     /* [9:8] WDT feeding dog error alarm enable for second period
                              - RW */
    ureg32 WDTLPIE:2;      /* [11:10] WDT low power status report enable - RW */
    ureg32 SWMLPIE:2;      /* [13:12] SAFEWDT module low Power status report enable - RW */
    ureg32 SWALMEN:2;      /* [15:14] SAFEWDT alarm report enable - RW */
    ureg32 REGALMEN:2;     /* [17:16] This bit field is used to enable reporting SAFEWDT
                              register bit redundancy mechanism alarm - RW */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} SAFEWDT_SAFEWDTEN_Bits;

/* SAFEWDT clear register */
typedef struct
{
    ureg32 SEALMC:2;       /* [1:0] Clear the status of SWALMSTS.SEALM - W1C */
    ureg32 SEINTC:2;       /* [3:2] Clear the status of SWINTSTS.SEINT - W1C */
    ureg32 WDTALMC1:2;     /* [5:4] Clear the status of SWALMSTS.WDTALM1 - W1C */
    ureg32 WDTINTC1:2;     /* [7:6] Clear the status of SWINTSTS.WDTINT1 period - W1C */
    ureg32 WDTALMC2:2;     /* [9:8] Clear the status of SWALMSTS.WDTALM2 - W1C */
    ureg32 SWLPIC:2;       /* [11:10] Clear the status of SWSTS.SWMLPI - W1C */
    ureg32 WDTLPIC:2;      /* [13:12] Clear the status of SWSTS.WDTLPI - W1C */
    ureg32 SWALMC:2;       /* [15:14] Clear the status of SWALMSTS.SWALM - W1C */
    ureg32 SWREGALMC:2;    /* [17:16] Clear the status of SWALMSTS.SWREGALM - W1C */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} SAFEWDT_SAFEWDTCL_Bits;

/* SAFEWDT alarm and bus error mask register */
typedef struct
{
    ureg32 SEALMMK:2;      /* [0:1] SE permission error alarm mask - RW */
    ureg32 WDTALM1MK:2;    /* [3:2] WDT counter first interval overflow error alarm mask - RW*/
    ureg32 WDTALM2MK:2;    /* [5:4] WDT counter second interval overflow error alarm mask - RW*/
    ureg32 SWALMMK:2;      /* [7:6] Mask SAFEWDT alarm - RW */
    ureg32 REGALMMK:2;     /* [9:8] Register dual bit redundancy error alarm mask - RW */
    ureg32 BEMASK:2;       /* [11:10] Register illegal operation bus error mask - RW */
    ureg32 reserved_12:20; /* [31:12] Internal reserved */
} SAFEWDT_SWMASK_Bits;

/* SAFEWDT interrupt mask register */
typedef struct
{
    ureg32 SEINTMK:2;     /* [1:0] SE permission error interrupt mask - RW */
    ureg32 WDTINT1MK:2;   /* [3:2] WDT counter first interval overflow error interrupt mask - RW */
    ureg32 reserved_4:28; /* [31:4] Internal reserved */
} SAFEWDT_SWINTMASK_Bits;

/* Debug trace hardware clock enable register */
typedef struct
{
    ureg32 DBGHWEN:1;     /* [0:0] Debug hardware clock enable - RW */
    ureg32 reserved_1:31; /* [31:1] Internal reserved */
} SAFEWDT_DBGHWCKEN_Bits;
/**********************************************************************************************************************
 *                                          SE Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* SE permission password register */
typedef struct
{
    ureg32 SEPW:14;        /* [13:0] SE permission password - RW */
    ureg32 reserved_14:18; /* [31:14] Internal reserved */
} SAFEWDT_SEPW_Bits;

/* SE permission password unlocking validity period register */
typedef struct
{
    ureg32 SEPWCNT:16;     /* [15:0] SE permission password unlocking validity period - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} SAFEWDT_SEPWCNT_Bits;

/* SE counter enable register */
typedef struct
{
    ureg32 SECNTEN:2;     /* [1:0] SE counter enable signal - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} SAFEWDT_SECNTEN_Bits;

/* SE counter control register */
typedef struct
{
    ureg32 SESTART:2;     /* [1:0] SE counter start signal - RW */
    ureg32 SESTOP:2;      /* [3:2] SE counter stop signal - RW */
    ureg32 reserved_4:28; /* [31:4] Internal Reserved */
} SAFEWDT_SECNTC_Bits;

/* SE counter threshold register */
typedef struct
{
    ureg32 SETHV:16;       /* [15:0] SE counter threshold value - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} SAFEWDT_SETHV_Bits;

/* SE counter status register */
typedef struct
{
    ureg32 SECNT:16;       /* [15:0] SE counter value - R0 */
    ureg32 SEOUTSTS:1;     /* [16:16] SE output signal - RO */
    ureg32 reserved_17:15; /* [31:17] Internal Reserved */
} SAFEWDT_SESTS_Bits;

/**********************************************************************************************************************
 *                                          WDT Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* WDT permission password register */
typedef struct
{
    ureg32 WDTPW:14;       /* [13:0] WDT permission password - RW */
    ureg32 reserved_14:18; /* [31:14] Internal reserved */
} SAFEWDT_WDTPW_Bits;

/* WDT permission unlocking validity period register */
typedef struct
{
    ureg32 WDTPWCNT:16;    /* [15:0] WDT permission password unlocking validity period - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} SAFEWDT_WDTPWCNT_Bits;

/* WDT counter enable register */
typedef struct
{
    ureg32 WDTCNTEN:2;    /* [1:0] WDT counter enable signal - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} SAFEWDT_WDTCNTEN_Bits;

/* WDT counter control register */
typedef struct
{
    ureg32 WDTSERVICE:2;  /* [1:0] WDT Service - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} SAFEWDT_WDTCNTC_Bits;

/* WDT counter lower limit enable register for WDT/WWDT selection */
typedef struct
{
    ureg32 WDTLEN0:1;     /* [0:0] Enable lower limit of first period of WDT counter - RW */
    ureg32 WDTLEN1:1;     /* [1:1] Enable lower limit of second period of WDT counter - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} SAFEWDT_WDTLEN_Bits;

/* WDT counter status register */
typedef struct
{
    ureg32 CNTVAL:18;      /* [17:0] WDT counter value - RW */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} SAFEWDT_WDTCNTVAL_Bits;

/* WDT counter lower limit of first period register */
typedef struct
{
    ureg32 WDTLTHV0:17;    /* [16:0] WDT counter lower limit of first period - RW */
    ureg32 reserved_17:15; /* [31:17] Internal reserved */
} SAFEWDT_WDTLTHV0_Bits;

/* WDT counter higher limit of first period register */
typedef struct
{
    ureg32 WDTHTHV0:17;    /* [16:0] WDT counter upper limit of first period - RW */
    ureg32 reserved_17:15; /* [31:17] Internal reserved */
} SAFEWDT_WDTHTHV0_Bits;

/* WDT counter lower limit of second period register */
typedef struct
{
    ureg32 WDTLTHV1:17;    /* [16:0] WDT counter lower limit of second period - RW */
    ureg32 reserved_17:15; /* [31:17] Internal reserved */
} SAFEWDT_WDTLTHV1_Bits;

/* WDT counter higher limit of second period register */
typedef struct
{
    ureg32 WDTHTHV1:17;    /* [16:0] WDT counter higher limit of second period - RW */
    ureg32 reserved_17:15; /* [31:17] Internal reserved */
} SAFEWDT_WDTHTHV1_Bits;

/**********************************************************************************************************************
 *                                           SAFEWDT Register Definitions
 *********************************************************************************************************************/
/* PWLOCK register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAFEWDT_PWLOCK_Bits B; /* Bit-Field access */
} SAFEWDT_PWLOCK;

/* PW0 register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    SAFEWDT_PW0_Bits B; /* Bit-Field access */
} SAFEWDT_PW0;

/* PW0CNT register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAFEWDT_PW0CNT_Bits B; /* Bit-Field access */
} SAFEWDT_PW0CNT;

/* PWMAI register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SAFEWDT_PWMAI_Bits B; /* Bit-Field access */
} SAFEWDT_PWMAI;

/* CLKMNG register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAFEWDT_CLKMNG_Bits B; /* Bit-Field access */
} SAFEWDT_CLKMNG;

/* OUTM register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    SAFEWDT_OUTM_Bits B; /* Bit-Field access */
} SAFEWDT_OUTM;

/* SAFECPU id register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SAFEWDT_SAFECPUID_Bits B; /* Bit-Field access */
} SAFEWDT_SAFECPUID;

/* SWSTS register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SAFEWDT_SWSTS_Bits B; /* Bit-Field access */
} SAFEWDT_SWSTS;

/* SWALMSTS register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SAFEWDT_SWALMSTS_Bits B; /* Bit-Field access */
} SAFEWDT_SWALMSTS;

/* SWINTRSTS register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SAFEWDT_SWINTSTS_Bits B; /* Bit-Field access */
} SAFEWDT_SWINTSTS;

/* SAFEWDTEN register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SAFEWDT_SAFEWDTEN_Bits B; /* Bit-Field access */
} SAFEWDT_SAFEWDTEN;

/* SAFEWDTCL register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SAFEWDT_SAFEWDTCL_Bits B; /* Bit-Field access */
} SAFEWDT_SAFEWDTCL;

/* SWMASK register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAFEWDT_SWMASK_Bits B; /* Bit-Field access */
} SAFEWDT_SWMASK;

/* SWINTMASK register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SAFEWDT_SWINTMASK_Bits B; /* Bit-Field access */
} SAFEWDT_SWINTMASK;

/* DBGHWCKEN register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SAFEWDT_DBGHWCKEN_Bits B; /* Bit-Field access */
} SAFEWDT_DBGHWCKEN;
/**********************************************************************************************************************
 *                                             SE Register Definitions
 *********************************************************************************************************************/
/* SEPW register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    SAFEWDT_SEPW_Bits B; /* Bit-Field access */
} SAFEWDT_SEPW;

/* SEPWCNT register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SAFEWDT_SEPWCNT_Bits B; /* Bit-Field access */
} SAFEWDT_SEPWCNT;

/* SECNTEN register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SAFEWDT_SECNTEN_Bits B; /* Bit-Field access */
} SAFEWDT_SECNTEN;

/* SECNTC register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAFEWDT_SECNTC_Bits B; /* Bit-Field access */
} SAFEWDT_SECNTC;

/* SETHV register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SAFEWDT_SETHV_Bits B; /* Bit-Field access */
} SAFEWDT_SETHV;

/* SESTS register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SAFEWDT_SESTS_Bits B; /* Bit-Field access */
} SAFEWDT_SESTS;

/**********************************************************************************************************************
 *                                             WDT Register Definitions
 *********************************************************************************************************************/
/* WDTPW register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SAFEWDT_WDTPW_Bits B; /* Bit-Field access */
} SAFEWDT_WDTPW;

/* WDTPWCNT register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SAFEWDT_WDTPWCNT_Bits B; /* Bit-Field access */
} SAFEWDT_WDTPWCNT;

/* WDTCNTEN register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SAFEWDT_WDTCNTEN_Bits B; /* Bit-Field access */
} SAFEWDT_WDTCNTEN;

/* WDTCNTC register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SAFEWDT_WDTCNTC_Bits B; /* Bit-Field access */
} SAFEWDT_WDTCNTC;

/* WDTLEN register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAFEWDT_WDTLEN_Bits B; /* Bit-Field access */
} SAFEWDT_WDTLEN;

/* WDTCNTSTS register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SAFEWDT_WDTCNTVAL_Bits B; /* Bit-Field access */
} SAFEWDT_WDTCNTVAL;

/* WDTLTHV0 register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SAFEWDT_WDTLTHV0_Bits B; /* Bit-Field access */
} SAFEWDT_WDTLTHV0;

/* WDTHTHV0 register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SAFEWDT_WDTHTHV0_Bits B; /* Bit-Field access */
} SAFEWDT_WDTHTHV0;

/* WDTLTHV1 register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SAFEWDT_WDTLTHV1_Bits B; /* Bit-Field access */
} SAFEWDT_WDTLTHV1;

/* WDTHTHV1 register */
typedef union
/* #Violation: safewdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SAFEWDT_WDTHTHV1_Bits B; /* Bit-Field access */
} SAFEWDT_WDTHTHV1;

/**********************************************************************************************************************
 *                                     SAFEWDT Register Configuration Structure
 *********************************************************************************************************************/
/* SAFEWDT object */
typedef volatile struct
{
    SAFEWDT_PW0 PW0;             /* 0x0 - Password0 register */
    SAFEWDT_PWLOCK PWLOCK;       /* 0x4 - Password lock register */
    SAFEWDT_PWMAI PWMAI;         /* 0x8 - Password mode and initialization register */
    SAFEWDT_PW0CNT PW0CNT;       /* 0xC - Password0 count register */
    SAFEWDT_SEPWCNT SEPWCNT;     /* 0x10 - SE password count register */
    SAFEWDT_SETHV SETHV;         /* 0x14 - SE threshold value register */
    SAFEWDT_SEPW SEPW;           /* 0x18 - SE password register */
    SAFEWDT_SECNTEN SECNTEN;     /* 0x1C - SE count enable register */
    SAFEWDT_SECNTC SECNTC;       /* 0x20 - SE count control register */
    SAFEWDT_WDTPWCNT WDTPWCNT;   /* 0x24 - WDT password count register */
    SAFEWDT_WDTLEN WDTLEN;       /* 0x28 - WDT low threshold enable register */
    SAFEWDT_WDTLTHV0 WDTLTHV0;   /* 0x2C - WDT first interval low threshold value register */
    SAFEWDT_WDTHTHV0 WDTHTHV0;   /* 0x30 - WDT first interval high threshold value register */
    SAFEWDT_WDTLTHV1 WDTLTHV1;   /* 0x34 - WDT second interval low threshold value register */
    SAFEWDT_WDTHTHV1 WDTHTHV1;   /* 0x38 - WDT second interval high threshold value register */
    SAFEWDT_WDTPW WDTPW;         /* 0x3C - WDT password register */
    SAFEWDT_WDTCNTEN WDTCNTEN;   /* 0x40 - WDT count enable register */
    SAFEWDT_WDTCNTC WDTCNTC;     /* 0x44 - WDT count control register */
    SAFEWDT_CLKMNG CLKMNG;       /* 0x48 - Clock management register */
    SAFEWDT_OUTM OUTM;           /* 0x4C - Output mode register */
    SAFEWDT_SAFECPUID SAFECPUID; /* 0x50 - SAFECPU ID register */
    SAFEWDT_SESTS SESTS;         /* 0x54 - SE status register */
    SAFEWDT_WDTCNTVAL WDTCNTVAL; /* 0x58 - WDT Counter Value Register */
    SAFEWDT_SWSTS SWSTS;         /* 0x5C - SAFEWDT states register */
    SAFEWDT_SWALMSTS SWALMSTS;   /* 0x60 - SAFEWDT alarm states register */
    SAFEWDT_SWINTSTS SWINTSTS;   /* 0x64 - SAFEWDT interrupt states register */
    SAFEWDT_SAFEWDTEN SAFEWDTEN; /* 0x68 - SAFEWDT alarm/interrupt enable register */
    SAFEWDT_SAFEWDTCL SAFEWDTCL; /* 0x6C - SAFEWDT clean register */
    SAFEWDT_SWMASK SWMASK;       /* 0x70 - SAFEWDT alarm error and bus error mask register */
    SAFEWDT_SWINTMASK SWINTMASK; /* 0x74 - SAFEWDT interrupt mask register */
    SAFEWDT_DBGHWCKEN DBGHWCKEN; /* 0x78 - Debug trace hardware clock enable register */
} SAFEWDT_MODULE;

#endif /* SAFEWDT_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

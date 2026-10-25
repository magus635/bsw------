/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    cpuwdt_register.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of CPUWDT module registers.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
*#cpuwdt_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:reason 0750 Using unions for bit-field access to registers
*
*/
#ifndef CPUWDT_REGISTER_H_
#define CPUWDT_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                      CPUWDT Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Password0 register */
typedef struct
{
    ureg32 PW0:14;         /* [13:0] PW0 permission password - RW */
    ureg32 reserved_14:18; /* [31:14] Internal reserved */
} CPUWDT_PW0_Bits;

/* Password lock register */
typedef struct
{
    ureg32 PW0LCK:1;      /* [0:0] PW0 locking signal (0:unlock, 1:lock) - RW */
    ureg32 CEPWLCK:1;     /* [1:1] CE locking signal (0:unlock, 1:lock) - RW */
    ureg32 WDTPWLCK:1;    /* [2:2] WDT locking signal (0:unlock, 1:lock) - RW */
    ureg32 reserved_3:29; /* [31:3] Internal reserved */
} CPUWDT_PWLOCK_Bits;

/* PWCE/PWWDT password mode selection and initial password register */
typedef struct
{
    ureg32 WDTPWINIT:14; /* [13:0] PWWDT initial password - RW */
    ureg32 WDTPWM:2;     /* [15:14] PWWDT password mode selection - RW */
    ureg32 CEPWINIT:14;  /* [29:16] PWCE initial password - RW */
    ureg32 CEPWM:2;      /* [31:30] PWCE password mode selection - RW */
} CPUWDT_PWMAI_Bits;

/* PW0 password unlocking validity period register */
typedef struct
{
    ureg32 PW0CNT:16;      /* [15:0] PW0 password unlocking validity period - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} CPUWDT_PW0CNT_Bits;

/* CE permission password unlocking validity period register */
typedef struct
{
    ureg32 CEPWCNT:16;     /* [15:0] CE permission password unlocking validity period - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} CPUWDT_CEPWCNT_Bits;

/* CE counter threshold register */
typedef struct
{
    ureg32 CETHV:16;       /* [15:0] CE counter threshold value - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} CPUWDT_CETHV_Bits;

/* CE permission password register */
typedef struct
{
    ureg32 CEPW:14;        /* [13:0] CE permission password - RW */
    ureg32 reserved_14:18; /* [31:14] Internal reserved */
} CPUWDT_CEPW_Bits;

/* CE counter enable register */
typedef struct
{
    ureg32 CECNTEN:2;     /* [1:0] CE counter enable signal - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} CPUWDT_CECNTEN_Bits;

/* CE counter control register */
typedef struct
{
    ureg32 CESTART:2;     /* [1:0] CE counter start signal - W1C */
    ureg32 CESTOP:2;      /* [3:2] CE counter stop signal - W1C */
    ureg32 reserved_4:28; /* [31:4] Internal reserved */
} CPUWDT_CECNTC_Bits;

/* WDT permission unlocking validity period register */
typedef struct
{
    ureg32 WDTPWCNT:16;    /* [15:0] WDT permission password unlocking validity period - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} CPUWDT_WDTPWCNT_Bits;

/* WDT counter lower limit enable register for WDT/WWDT selection */
typedef struct
{
    ureg32 WDTLEN0:1;     /* [0:0] Enable lower limit of first period of WDT counter - RW */
    ureg32 WDTLEN1:1;     /* [1:1] Enable lower limit of second period of WDT counter
                             - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} CPUWDT_WDTLEN_Bits;

/* WDT counter lower limit of first period register */
typedef struct
{
    ureg32 WDTLTHV0:17;    /* [16:0] WDT counter lower limit of first period - RW */
    ureg32 reserved_17:15; /* [31:17] Internal reserved */
} CPUWDT_WDTLTHV0_Bits;

/* WDT Counter higher limit of first period register */
typedef struct
{
    ureg32 WDTHTHV0:17;    /* [16:0] WDT counter upper limit of first period - RW */
    ureg32 reserved_17:15; /* [31:17] Internal reserved */
} CPUWDT_WDTHTHV0_Bits;

/* WDT counter lower limit of second period register */
typedef struct
{
    ureg32 WDTLTHV1:17;    /* [16:0] WDT counter lower limit of second period - RW */
    ureg32 reserved_17:15; /* [31:17] Internal reserved */
} CPUWDT_WDTLTHV1_Bits;

/* WDT counter higher limit of second period register */
typedef struct
{
    ureg32 WDTHTHV1:17;    /* [16:0] WDT counter higher limit of second period - RW*/
    ureg32 reserved_17:15; /* [31:17] Internal reserved */
} CPUWDT_WDTHTHV1_Bits;

/* WDT permission password register */
typedef struct
{
    ureg32 WDTPW:14;       /* [13:0] WDT permission password - RW */
    ureg32 reserved_14:18; /* [31:14] Internal reserved */
} CPUWDT_WDTPW_Bits;

/* WDT counter enable register */
typedef struct
{
    ureg32 WDTCNTEN:2;    /* [1:0] WDT counter enable signal - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} CPUWDT_WDTCNTEN_Bits;

/* WDT counter control register */
typedef struct
{
    ureg32 WDTSERVICE:2;    /* [1:0] WDT counter start signal - W1C */
    ureg32 reserved_2:30;   /* [31:2] Internal reserved */
} CPUWDT_WDTCNTC_Bits;

/* Clock management register */
typedef struct
{
    ureg32 WDTCKDIV:3;      /* [2:0] WDT clock frequency division coefficient - RW */
    ureg32 CECKDIV:3;       /* [5:3] CE clock frequency division - RW */
    ureg32 LPSEN:1;         /* [6:6] Low Power Signal Enable - RW */
    ureg32 reserved_7:25;   /* [31:7] Internal reserved */
} CPUWDT_CLKMNG_Bits;

/* Output mode register */
typedef struct
{
    ureg32 CEOUTM:1;      /* [0:0] CE permission error output mode selection (0:alarm,
                             1:interrupt) - RW */
    ureg32 WDTOUTM1:1;    /* [1:1] WDT feeding dog error output mode selection for first
                             period (0:alarm, 1:interrupt) - RW */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} CPUWDT_OUTM_Bits;

/* CE counter status register */
typedef struct
{
    ureg32 CECNT:16;       /* [15:0] CE counter value - RO */
    ureg32 CEOUTSTS:1;     /* [16:16] CE output signal - RO */
    ureg32 CEGLBSTS:1;     /* [17:17] Global E status indication - RO */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} CPUWDT_CESTS_Bits;

/* WDT counter status register */
typedef struct
{
    ureg32 CNTSTS:18;      /* [17:0] WDT counter value - RW */
    ureg32 reserved_17:14; /* [31:17] Internal reserved */
} CPUWDT_WDTCNTSTS_Bits;

/* CPUWDT status register */
typedef struct
{
    ureg32 CWLPI:1;       /* [0:0] WDT low power status recording - RO */
    ureg32 CWAPBLPI:1;    /* [1:1] CPUWDT APB low power status recording - RO */
    ureg32 PW0V:1;        /* [2:2] Indicate PW0 successfully unlocked - RO */
    ureg32 CEPWV:1;       /* [3:3] Indicate PWCE successfully unlocked - RO */
    ureg32 WDTPWV:1;      /* [4:4] Indicate PWWDT successfully unlocked - RO */
    ureg32 reserved_5:27; /* [31:5] Internal reserved */
} CPUWDT_CWSTS_Bits;

/* CPUWDT alarm status register */
typedef struct
{
    ureg32 CEALM:1;       /* [0:0] CE permission error alarm - RO */
    ureg32 WDTALM1:1;     /* [1:1] WDT feeding dog error alarm for first period - RO */
    ureg32 WDTALM2:1;     /* [2:2] WDT feeding dog error alarm for second period - RO */
    ureg32 CWALM:1;       /* [3:3] Security function mechanism error alarm, PW0/PWCE/PWWDT
                             error alarm - RO */
    ureg32 CWREGALM:1;    /* [4:4] Register error alarm (dual bit redundancy) - RO */
    ureg32 reserved_5:27; /* [31:5] Internal reserved */
} CPUWDT_CWALMSTS_Bits;

/* CPUWDT interrupt status register */
typedef struct
{
    ureg32 CEINTR:1;      /* [0:0] CE permission error interrupt - RO */
    ureg32 WDTINTR1:1;    /* [1:1] WDT feeding dog error interrupt for first period - RO */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} CPUWDT_CWINTSTS_Bits;

/* CPUWDT alarm/interrupt enable register */
typedef struct
{
    ureg32 CEALME:2;       /* [1:0] CE permission error alarm enable - RW */
    ureg32 CEINTRE:2;      /* [3:2] CE permission error interrupt enable - RW */
    ureg32 WDTALME1:2;     /* [5:4] WDT feeding dog error alarm enable for first period
                              - RW */
    ureg32 WDTINTE1:2;     /* [7:6] WDT feeding dog error interrupt enable for first period
                               - RO */
    ureg32 WDTALME2:2;     /* [9:8] WDT feeding dog error alarm enable for second period
                              - RW */
    ureg32 CLKLPIE:2;      /* [11:10] WDT and APB clk low power recording enable - RW */
    ureg32 WDTCLKLPIE:2;   /* [13:12] WDT clk low power recording enable - RW */
    ureg32 PWALMEN:2;      /* [15:14] Security function mechanism, PW0/PWCE/PWWDT error
                             alarm enable - RW */
    ureg32 REGALMEN:2;     /* [17:16] Register error alarm enable (dual bit redundancy)
                               - RW */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} CPUWDT_CPUWDTEN_Bits;

/* CPUWDT clear register */
typedef struct
{
    ureg32 CEALMC:2;       /* [1:0] Clear CE permission error alarm status - WO */
    ureg32 CEINTRC:2;      /* [3:2] Clear CE permission error interrupt status - WO */
    ureg32 WDTALMC1:2;     /* [5:4] Clear WDT feeding dog error alarm status for first period
                              - WO */
    ureg32 WDTINTC1:2;     /* [7:6] Clear WDT feeding dog error interrupt status for first
                               period - WO */
    ureg32 WDTALMC2:2;     /* [9:8] Clear WDT feeding dog error alarm status for second
                              period - WO */
    ureg32 CWLPIC:2;       /* [11:10] Clear WDT and APB clk low power recording status
                               - WO */
    ureg32 WDTLPIC:2;      /* [13:12] Clear WDT clk low power recording status - WO */
    ureg32 PWALMC:2;       /* [15:14] Clear security function mechanism, PW0/PWCE/PWWDT error
                              alarm status - WO */
    ureg32 REGALMC:2;      /* [17:16] Clear register error alarm status (dual bit redundancy)
                                - WO */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} CPUWDT_CPUWDTCL_Bits;

/* CPUWDT alarm and bus error mask register */
typedef struct
{
    ureg32 CEALMMK:2;      /* [0:1] CE permission error alarm mask - RW */
    ureg32 WDTALM1MK:2;    /* [3:2] WDT counter first interval overflow error alarm mask - RW*/
    ureg32 WDTALM2MK:2;    /* [5:4] WDT counter second interval overflow error alarm mask - RW*/
    ureg32 PWALMMK:2;      /* [7:6] Security function mechanism, PW0/PWCE/PWWDT error alarm mask - RW */
    ureg32 REGALMMK:2;     /* [9:8] Register dual bit redundancy error alarm mask - RW */
    ureg32 MIDEMASK:2;     /* [11:10] ID master match bus error mask - RW */
    ureg32 BEMASK:2;       /* [13:12] Register illegal operation bus error mask - RW */
    ureg32 reserved_14:18; /* [31:14] Internal reserved */
} CPUWDT_CWMASK_Bits;

/* CPUWDT interrupt mask register */
typedef struct
{
    ureg32 CEINTMK:2;     /* [1:0] CE permission error interrupt mask - RW */
    ureg32 WDTINT1MK:2;   /* [3:2] WDT counter first interval overflow error interrupt mask - RW */
    ureg32 reserved_4:28; /* [31:4] Internal reserved */
} CPUWDT_CWINTMASK_Bits;

/* Debug trace hardware clock enable register */
typedef struct
{
    ureg32 DBGHWEN:1;     /* [0:0] Debug hardware clock enable - RW */
    ureg32 reserved_1:31; /* [31:1] Internal reserved */
} CPUWDT_DBGHWCKEN_Bits;
/**********************************************************************************************************************
 *                                            CPUWDT Register Definitions
 *********************************************************************************************************************/
/* PW0 register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CPUWDT_PW0_Bits B; /* Bit-Field access */
} CPUWDT_PW0;

/* PWLOCK register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    CPUWDT_PWLOCK_Bits B; /* Bit-Field access */
} CPUWDT_PWLOCK;

/* PWMAI register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    CPUWDT_PWMAI_Bits B; /* Bit-Field access */
} CPUWDT_PWMAI;

/* PW0CNT register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    CPUWDT_PW0CNT_Bits B; /* Bit-Field access */
} CPUWDT_PW0CNT;

/* CEPWCNT register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    CPUWDT_CEPWCNT_Bits B; /* Bit-Field access */
} CPUWDT_CEPWCNT;

/* CETHV register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    CPUWDT_CETHV_Bits B; /* Bit-Field access */
} CPUWDT_CETHV;

/* CEPW register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    CPUWDT_CEPW_Bits B; /* Bit-Field access */
} CPUWDT_CEPW;

/* CECNTEN register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    CPUWDT_CECNTEN_Bits B; /* Bit-Field access */
} CPUWDT_CECNTEN;

/* CECNTC register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    CPUWDT_CECNTC_Bits B; /* Bit-Field access */
} CPUWDT_CECNTC;

/* WDTPWCNT register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_WDTPWCNT_Bits B; /* Bit-Field access */
} CPUWDT_WDTPWCNT;

/* WDTLEN register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    CPUWDT_WDTLEN_Bits B; /* Bit-Field access */
} CPUWDT_WDTLEN;

/* WDTLTHV0 register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_WDTLTHV0_Bits B; /* Bit-Field access */
} CPUWDT_WDTLTHV0;

/* WDTHTHV0 register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_WDTHTHV0_Bits B; /* Bit-Field access */
} CPUWDT_WDTHTHV0;

/* WDTLTHV1 register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_WDTLTHV1_Bits B; /* Bit-Field access */
} CPUWDT_WDTLTHV1;

/* WDTHTHV1 register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_WDTHTHV1_Bits B; /* Bit-Field access */
} CPUWDT_WDTHTHV1;

/* WDTPW register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    CPUWDT_WDTPW_Bits B; /* Bit-Field access */
} CPUWDT_WDTPW;

/* WDTCNTEN register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_WDTCNTEN_Bits B; /* Bit-Field access */
} CPUWDT_WDTCNTEN;

/* WDTCNTC register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    CPUWDT_WDTCNTC_Bits B; /* Bit-Field access */
} CPUWDT_WDTCNTC;

/* CLKMNG register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    CPUWDT_CLKMNG_Bits B; /* Bit-Field access */
} CPUWDT_CLKMNG;

/* OUTM register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    CPUWDT_OUTM_Bits B; /* Bit-Field access */
} CPUWDT_OUTM;

/* CESTS register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    CPUWDT_CESTS_Bits B; /* Bit-Field access */
} CPUWDT_CESTS;

/* WDTCNTSTS register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    CPUWDT_WDTCNTSTS_Bits B; /* Bit-Field access */
} CPUWDT_WDTCNTSTS;

/* CWSTS register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    CPUWDT_CWSTS_Bits B; /* Bit-Field access */
} CPUWDT_CWSTS;

/* CWALMSTS register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_CWALMSTS_Bits B; /* Bit-Field access */
} CPUWDT_CWALMSTS;

/* CWINTSTS register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_CWINTSTS_Bits B; /* Bit-Field access */
} CPUWDT_CWINTSTS;

/* CPUWDTEN register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_CPUWDTEN_Bits B; /* Bit-Field access */
} CPUWDT_CPUWDTEN;

/* CPUWDTCL register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    CPUWDT_CPUWDTCL_Bits B; /* Bit-Field access */
} CPUWDT_CPUWDTCL;

/* CWMASK register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    CPUWDT_CWMASK_Bits B; /* Bit-Field access */
} CPUWDT_CWMASK;

/* CWINTMASK register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    CPUWDT_CWINTMASK_Bits B; /* Bit-Field access */
} CPUWDT_CWINTMASK;

/* DBGHWCKEN register */
typedef union
/* #Violation: cpuwdt_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    CPUWDT_DBGHWCKEN_Bits B; /* Bit-Field access */
} CPUWDT_DBGHWCKEN;
/**********************************************************************************************************************
 *                                        CPUWDT Register Configuration Structure
 *********************************************************************************************************************/
/* CPUWDT object */
typedef volatile struct
{
    CPUWDT_PW0 PW0;             /* 0x0 - Password0 register */
    CPUWDT_PWLOCK PWLOCK;       /* 0x4 - Password lock register */
    CPUWDT_PWMAI PWMAI;         /* 0x8 - Password mode and initialization register */
    CPUWDT_PW0CNT PW0CNT;       /* 0xC - Password0 count register */
    CPUWDT_CEPWCNT CEPWCNT;     /* 0x10 - CE password count register */
    CPUWDT_CETHV CETHV;         /* 0x14 - CE threshold value register */
    CPUWDT_CEPW CEPW;           /* 0x18 - CE password register */
    CPUWDT_CECNTEN CECNTEN;     /* 0x1C - CE count enable register */
    CPUWDT_CECNTC CECNTC;       /* 0x20 - CE count control register */
    CPUWDT_WDTPWCNT WDTPWCNT;   /* 0x24 - WDT password count register */
    CPUWDT_WDTLEN WDTLEN;       /* 0x28 - WDT low threshold enable register */
    CPUWDT_WDTLTHV0 WDTLTHV0;   /* 0x2C - WDT first interval low threshold value register */
    CPUWDT_WDTHTHV0 WDTHTHV0;   /* 0x30 - WDT first interval high threshold value register */
    CPUWDT_WDTLTHV1 WDTLTHV1;   /* 0x34 - WDT second interval low threshold value register */
    CPUWDT_WDTHTHV1 WDTHTHV1;   /* 0x38 - WDT second interval high threshold value register */
    CPUWDT_WDTPW WDTPW;         /* 0x3C - WDT password register */
    CPUWDT_WDTCNTEN WDTCNTEN;   /* 0x40 - WDT count enable register */
    CPUWDT_WDTCNTC WDTCNTC;     /* 0x44 - WDT count control register */
    CPUWDT_CLKMNG CLKMNG;       /* 0x48 - Clock management register */
    CPUWDT_OUTM OUTM;           /* 0x4C - Output mode register */
    CPUWDT_CESTS CESTS;         /* 0x50 - CE status register */
    CPUWDT_WDTCNTSTS WDTCNTSTS; /* 0x54 - WDT count states register */
    CPUWDT_CWSTS CWSTS;         /* 0x58 - CPUWDT states register */
    CPUWDT_CWALMSTS CWALMSTS;   /* 0x5C - CPUWDT alarm states register */
    CPUWDT_CWINTSTS CWINTSTS;   /* 0x60 - CPUWDT interrupt states register */
    CPUWDT_CPUWDTEN CPUWDTEN;   /* 0x64 - CPUWDT alarm/interrupt enable register */
    CPUWDT_CPUWDTCL CPUWDTCL;   /* 0x68 - CPUWDT clean register */
    CPUWDT_CWMASK CWMASK;       /* 0x6C - CPUWDT alarm error and bus error mask register */
    CPUWDT_CWINTMASK CWINTMASK; /* 0x70 - CPUWDT interrupt mask register */
    CPUWDT_DBGHWCKEN DBGHWCKEN; /* 0x74 - Debug trace hardware clock enable register */
} CPUWDT_MODULE;

#endif /* CPUWDT_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

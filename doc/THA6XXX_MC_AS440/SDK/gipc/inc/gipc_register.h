/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gipc_register.h
 * Author:      01200
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of GIPC module registers.
 *********************************************************************************************************************/

/*
*#Violation Summary
*
* #gipc_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to register.
*
* #gipc_register_h_REF_2:MISRAC2012-Dir-4.8
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*/


#ifndef GIPC_REGISTER_H_
#define GIPC_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        GIPC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Exclusives reservation granule register */
typedef struct
{
    ureg32 ERG:4;         /* [3:0] GIPC exclusives reservation granule - RW */
    ureg32 reserved_4:28; /* [31:4] Internal reserved */
} GIPC_ERG_Bits;

/* FSM status register */
typedef struct
{
    ureg32 STATE:2;        /* [1:0] FSM state - RO */
    ureg32 MADDR:18;       /* [19:2] Marked address - RO */
    ureg32 reserved_20:12; /* [31:20] Internal reserved */
} GIPC_FSMSTS_Bits;

/* FSM write clear register */
typedef struct
{
    ureg32 STATECLR:2;    /* [1:0] Write to clear the state of FSM, from exclusive access to open access - WO */
    ureg32 reserved_2:30; /* [31:2] Internal reserved */
} GIPC_FSMSTSCLR_Bits;

/* PPI status register */
typedef struct
{
    ureg32 PPISTSL:1;     /* [0:0] Write 1 to clear the status of PPI - WO */
    ureg32 PPISTSM:1;     /* [1:1] Write 1 to clear the status of PPI - WO (THA6412 only) */
    ureg32 PPISTSH:1;     /* [2:2] Write 1 to clear the status of PPI - WO (THA6412 only) */
    ureg32 reserved_3:29; /* [31:3] Internal reserved */
} GIPC_PPISTS_Bits;

/* PPI control register */
typedef struct
{
    ureg32 PPICTRLL:2;    /* [1:0] Generate PPI - WO */
    ureg32 PPICTRLM:2;    /* [3:2] Generate PPI - WO (THA6412 only) */
    ureg32 PPICTRLH:2;    /* [5:4] Generate PPI - WO (THA6412 only) */
    ureg32 reserved_6:24; /* [29:6] Internal reserved */
    ureg32 PPIMASK:2;     /* [31:30] GIPC interrupt masking */
} GIPC_PPICTRL_Bits;

/* AXI addr channel protection code alarm address */
typedef struct
{
    ureg32 ALMADDR:18;    /* [17:0] AXI addr channel protection code alarm address - RO */
    ureg32 reserved_18:6; /* [23:18] Internal reserved */
    ureg32 ALMMSID:6;     /* [29:24] AXI addr channel protection code alarm MasterID - RO (THA6412 only) */
    ureg32 reserved_30:2; /* [31:30] Internal reserved */
} GIPC_ALMADDR_Bits;

/* GIPC safety fault input register */
typedef struct
{
    ureg32 reserved_0:2;   /* [1:0] Internal reserved */
    ureg32 FMFI:2;         /* [3:2] FSM monitor fault input - RW */
    ureg32 FPCFI:2;        /* [5:4] FSM plausibility check fault input - RW */
    ureg32 AARFI:2;        /* [7:6] AXI addr logic redundancy fault input - RW */
    ureg32 AACPCFI:2;      /* [9:8] AXI addr channel protection code fault input - RW */
    ureg32 reserved_10:22; /* [31:10] Internal reserved */
} GIPC_SAFEFAULT_Bits;

/* GIPC safety enable register */
typedef struct
{
    ureg32 DRSE:2;         /* [1:0] DFF redundancy safety enable - RW */
    ureg32 FMSE:2;         /* [3:2] FSM monitor safety enable - RW */
    ureg32 FPCSE:2;        /* [5:4] FSM plausibility check safety enable - RW */
    ureg32 AARSE:2;        /* [7:6] AXI addr logic redundancy safety enable - RW */
    ureg32 AACPCSE:2;      /* [9:8] AXI addr channel protection code safety enable - RW */
    ureg32 reserved_10:20; /* [29:10] Internal reserved */
    ureg32 BEMASK:2;       /* [31:30] Bus error mask control - RW */
} GIPC_SAFEEN_Bits;

/* GIPC safety alarm register */
typedef struct
{
    ureg32 FMALM0:1;        /* [0:0] Core0 FSM monitor alarm - RO */
    ureg32 FMALM1:1;        /* [1:1] Core1 FSM monitor alarm - RO */
    ureg32 FMALM2:1;        /* [2:2] Core2 FSM monitor alarm - RO (THA6412 only) */
    ureg32 FMALM3:1;        /* [3:3] Core3 FSM monitor alarm - RO (THA6412 only) */
    ureg32 FPCALM0:1;       /* [4:4] Core0 FSM plausibility check alarm - RO */
    ureg32 FPCALM1:1;       /* [5:5] Core1 FSM plausibility check alarm - RO */
    ureg32 FPCALM2:1;       /* [6:6] Core2 FSM plausibility check alarm - RO (THA6412 only) */
    ureg32 FPCALM3:1;       /* [7:7] Core3 FSM plausibility check alarm - RO (THA6412 only) */
    ureg32 AARALM:1;        /* [8:8] AXI addr logic redundancy alarm - RO */
    ureg32 AACPCALM:1;      /* [9:9] AXI addr channel protection code alarm - RO */
    ureg32 EALM:1;          /* [10:10] E alarm - RO */
    ureg32 SEALM:1;         /* [11:11] SE alarm - RO */
    ureg32 ERGALM:1;        /* [12:12] ERG alarm - RO */
    ureg32 FSMSTSCLRALM0:1; /* [13:13] FSMSTSCLR0 alarm - RO */
    ureg32 FSMSTSCLRALM1:1; /* [14:14] FSMSTSCLR1 alarm - RO */
    ureg32 FSMSTSCLRALM2:1; /* [15:15] FSMSTSCLR2 alarm - RO (THA6412 only) */
    ureg32 FSMSTSCLRALM3:1; /* [16:16] FSMSTSCLR3 alarm - RO (THA6412 only) */
    ureg32 PPICTRLALM0:1;   /* [17:17] PPICTRL0 alarm - RO */
    ureg32 PPICTRLALM1:1;   /* [18:18] PPICTRL1 alarm - RO */
    ureg32 PPICTRLALM2:1;   /* [19:19] PPICTRL2 alarm - RO (THA6412 only) */
    ureg32 PPICTRLALM3:1;   /* [20:20] PPICTRL3 alarm - RO (THA6412 only) */
    ureg32 SAFEFAULTALM:1;  /* [21:21] SAFEFAULT alarm - RO */
    ureg32 SAFEENALM:1;     /* [22:22] SAFEENALM alarm - RO */
    ureg32 ALARMCLRALM:1;   /* [23:23] ALARMCLR alarm - RO */
    ureg32 reserved_24:8;   /* [31:24] Internal reserved */
} GIPC_ALARM_Bits;

/* GIPC safety alarm clear register */
typedef struct
{
    ureg32 FMALMC:2;       /* [1:0] FSM monitor alarm clear - WO */
    ureg32 FPCALMC:2;      /* [3:2] FSM plausibility check alarm clear - WO */
    ureg32 AARALMC:2;      /* [5:4] AXI addr logic redundancy alarm clear - WO */
    ureg32 AACPCALMC:2;    /* [7:6] AXI addr channel protection code alarm clear - WO */
    ureg32 ESEALMC:2;      /* [9:8] E/SE alarm clear - WO */
    ureg32 DRALMC:2;       /* [11:10] DFF redundancy alarm clear - WO */
    ureg32 reserved_12:20; /* [31:12] Internal reserved */
} GIPC_ALARMCLR_Bits;
/**********************************************************************************************************************
 *                                              INTC Register Definitions
 *********************************************************************************************************************/
/* ERG register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    GIPC_ERG_Bits B; /* Bit-Field access */
} GIPC_ERG;

/* FSMSTS register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    GIPC_FSMSTS_Bits B; /* Bit-Field access */
} GIPC_FSMSTS;

/* FSMSTSCLR register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    GIPC_FSMSTSCLR_Bits B; /* Bit-Field access */
} GIPC_FSMSTSCLR;

/* PPISTS register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    GIPC_PPISTS_Bits B; /* Bit-Field access */
} GIPC_PPISTS;

/* PPICTRL register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    GIPC_PPICTRL_Bits B; /* Bit-Field access */
} GIPC_PPICTRL;

/* ALMADDR register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    GIPC_ALMADDR_Bits B; /* Bit-Field access */
} GIPC_ALMADDR;

/* SAFEFAULT register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    GIPC_SAFEFAULT_Bits B; /* Bit-Field access */
} GIPC_SAFEFAULT;

/* SAFEEN register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    GIPC_SAFEEN_Bits B; /* Bit-Field access */
} GIPC_SAFEEN;

/* ALARM register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    GIPC_ALARM_Bits B; /* Bit-Field access */
} GIPC_ALARM;

/* ALARMCLR register */
typedef union
/* #Violation: gipc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    GIPC_ALARMCLR_Bits B; /* Bit-Field access */
} GIPC_ALARMCLR;

/**********************************************************************************************************************
 *                                        GIPC Register Configuration Structure
 *********************************************************************************************************************/
/* #Violation: gipc_register_h_REF_2 */
typedef volatile struct
{
    GIPC_ERG ERG;                /* 0x0 - Exclusives reservation granule register */
    GIPC_FSMSTS FSMSTS[4];       /* 0x4 - FSM status register */
    GIPC_FSMSTSCLR FSMSTSCLR[4]; /* 0x14 - FSM write clear register */
    GIPC_PPISTS PPISTS[4];       /* 0x24 - PPI status register */
    GIPC_PPICTRL PPICTRL[4];     /* 0x34 - PPI control register */
    GIPC_ALMADDR ALMADDR;        /* 0x44 - AXI addr channel protection code alarm address */
    GIPC_SAFEFAULT SAFEFAULT;    /* 0x48 - GIPC safety fault input register */
    GIPC_SAFEEN SAFEEN;          /* 0x4C - GIPC safety enable register */
    GIPC_ALARM ALARM;            /* 0x50 - GIPC safety alarm register */
    GIPC_ALARMCLR ALARMCLR;      /* 0x54 - GIPC safety alarm clear register */
} GIPC_MODULE;

#endif /* GIPC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

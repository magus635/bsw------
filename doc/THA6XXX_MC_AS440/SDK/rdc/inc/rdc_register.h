/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    rdc_register.h
 * Author:      00915
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of RDC module registers.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #rdc_register_h_REF_1:MISRAC2012-Rule-19.2
* Justification:Using unions for bit-field access to registers.
*
*/
#ifndef RDC_REGISTER_H_
#define RDC_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        RDC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Excitation carrier duty cycle configuration register */
typedef struct
{
    ureg32 CW_NEG:16; /* [15:0] The starting point of the excitation carrier duty cycle - RW */
    ureg32 CW_POS:16; /* [31:16] The ending point of the excitation carrier duty cycle - RW */
} RDC_CWDR_Bits;

/* Number of carrier points and number of sine points configuration register */
typedef struct
{
    ureg32 TOTAL_POINTS:16; /* [15:0] Number of sine wave points - RW */
    ureg32 CW_POINTS:16;    /* [31:16] Number Of Sawtooth Carrier Points - RW */
} RDC_CWPOINTS_Bits;

/* Excitation carrier configuration register */
typedef struct
{
    ureg32 WAVEMODE:1;      /* [0:0] Waveform configuration - RW */
    ureg32 STEPCFG:3;       /* [3:1] The counter step value is configured with the corresponding
                                     excitation output frequency - RW */
    ureg32 SOFTCFGEN:1;     /* [4:4] In SPWM mode, the software generates an spwm-enable switch - RW */
    ureg32 REQENFLAG:1;     /* [5:5] Data Interrupt Request - RW */
    ureg32 reserved_6:2;    /* [7:6] Internal reserved */
#if defined(THA6_THA6206D)
    ureg32 PULSEDURCLK:1;   /* [8:8] Pulse extension */
    ureg32 DPLLDATASEL:1;   /* [9:9] DPLL data selection */
    ureg32 EDGEMODE:2;      /* [11:10] Trigger single edge mode selection */
#else
    ureg32 PULSEDURCLK:4;   /* [11:8] Pulse extension */
#endif
    ureg32 reserved_12:20;  /* [31:12] Internal reserved */
} RDC_CWCFG_Bits;

/* Excitation carrier control register */
typedef struct
{
    ureg32 EXCRUN:1;         /* [0:0] Excitation enable switch - RW */
    ureg32 reserved_1:31; /* [31:1] Internal reserved */
} RDC_CWCTRL_Bits;

/* Solve the loop carrier recovery loop kp configuration register */
typedef struct
{
    ureg32 KP:18;          /* [17:0] DPLL loop kp register configuration - RW */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} RDC_DPLLKP_Bits;

/* Solve the loop carrier recovery loop ki configuration register */
typedef struct
{
    ureg32 KI:18;          /* [17:0] DPLL loop ki register configuration - RW */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} RDC_DPLLKI_Bits;

/* Solve the loop carrier main loop kp configuration register */
typedef struct
{
    ureg32 KP:18;          /* [17:0] Main loop kp register configuration - RW */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} RDC_MAINKP_Bits;

/* Solve the loop carrier main loop ki configuration register */
typedef struct
{
    ureg32 KI:18;          /* [17:0] Main loop ki register configuration - RW */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} RDC_MAINKI_Bits;

/* RDC solves the loop dc bias compensation register */
typedef struct
{
    sreg32 DOCQ:16; /* [15:0] Q-way dc bias - RW */
    sreg32 DOCI:16; /* [31:16] I-way dc bias - RW */
} RDC_DCOFFSET_Bits;

/* RDC solves the loop gain bias compensation register */
typedef struct
{
    ureg32 GCOFFSETI:16;   /* [15:0] I-way gain compensation - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} RDC_GAINOFFSET_Bits;

/* RDC solves the loop configuration register */
typedef struct
{
    ureg32 HPFBYPASS:1;         /* [0:0] High-pass filter enabled - RW */
    ureg32 HPFCFG:3;            /* [3:1] High-pass filter cutoff frequency configuration - RW */
    ureg32 DCBYPASS:1;          /* [4:4] DC bias compensation enabled - RW */
    ureg32 GCBYPASS:1;          /* [5:5] Gain compensation enabled - RW */
    ureg32 TRISEL:1;            /* [6:6] Trigger source selection configuration - RW */
    ureg32 SARADCU2SBYPASS:1;   /* [7:7] SARADC symbol bit control register - RW */
    ureg32 VLDSEL:1;            /* [8:8] Processing circuit data selection - RW */
    ureg32 SAMPCFG:2;           /* [9:10] Sampling rate configuration - RW */
    ureg32 SIGSEL:1;            /* [11:11] RDC parsing signal configuration - RW */
#if defined(THA6_THA6206D)
    ureg32 CDCDNUM:3;           /* [14:12] HDI cross clock domain delay control - RW */
    ureg32 RESET:1;             /* [15:15] Reset control of RDC settlement function - RW */
#else
    ureg32 CDCDNUM:4;           /* [15:12] HDI cross clock domain delay control - RW */
#endif
    ureg32 IDATASEL:4;          /* [19:16]  I-channel data source selection - RW */
    ureg32 QDATASEL:4;          /* [23:20]  Q-channel data source selection - RW */
    ureg32 reserved_24:8;       /* [31:24] Internal reserved */
} RDC_RECFG_Bits;

/* RDC cpu trigger register */
typedef struct
{
    ureg32 CPUTRI:1;      /* [0:0] RDC cpu trigger - RW */
    ureg32 reserved_1:31; /* [31:1] Internal reserved */
} RDC_CPUTRI_Bits;

/* RDC solves the loop phase estimation reporting register */
typedef struct
{
    ureg32 PE:18;          /* [17:0] Phase estimation reports registers - RW */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
} RDC_CPE_Bits;

/* The speed value of the real-time solution of the rdc solution loop */
typedef struct
{
    sreg32 VELOCITY:24;   /* [23:0] Real-time speed reporting registers - RW */
    ureg32 reserved_24:8; /* [31:24] Internal reserved */
} RDC_VEL_Bits;

/* The angle value of the real-time solution of the rdc solution loop */
typedef struct
{
    sreg32 ANGEL:24;      /* [23:0] Real-time angle reporting registers - RW */
    ureg32 reserved_24:8; /* [31:24] Internal reserved */
} RDC_ANG_Bits;

/* The speed value triggered by the interrupt is reported */
typedef struct
{
    sreg32 TRIVEL:24;     /* [23:0] Speed value triggered by the interrupt is reported - RW */
    ureg32 reserved_24:8; /* [31:24] Internal reserved */
} RDC_TRIVEL_Bits;

/* The angle value triggered by the interrupt is reported */
typedef struct
{
    sreg32 TRIANG:24;     /* [23:0] Angle value triggered by the interrupt is reported - RW */
    ureg32 reserved_24:8; /* [31:24] Internal reserved */
} RDC_TRIANG_Bits;

/* The time value triggered by the interrupt is reported */
typedef struct
{
    ureg32 TSCOUNT:16;     /* [15:0] Time value triggered by the interrupt is reported - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} RDC_TRIGTSMP_Bits;

/* IQ Extreme Value Clear Register */
typedef struct
{
    ureg32 CLR:1;           /* [0:0] lQ Extreme Value Clear Register - W1C */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} RDC_IQEXTREVALCLR_Bits;

/* I Extreme Value Reporting Register */
typedef struct
{
    sreg32 MIN:16;      /* [0:15] I Channel Maximum Value Report - RO */
    sreg32 MAX:16;      /* [31:15] I Channel Minimum Value Report - RO */
} RDC_IEXTREVALRPT_Bits;

/* Q Extreme Value Reporting Register */
typedef struct
{
    sreg32 MIN:16;      /* [0:15] Q Channel Maximum Value Report - RO */
    sreg32 MAX:16;      /* [31:15] Q Channel Minimum Value Report - RO */
} RDC_QEXTREVALRPT_Bits;

/* Monitor Signal Reporting Register */
typedef struct
{
    ureg32 MON:16;          /* [15:0] Monitoring Signal Reporting Value - RO */
    ureg32 reserved_16:16;  /* [31:15] Internal reserved */
} RDC_MONRPT_Bits;

/* Bus Error Mask Register */
typedef struct
{
    ureg32 MSK:1;           /* [0:0] Bus Error Mask - RW */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} RDC_BUSERRMSK_Bits;

/* Enable the reference phase Register */
typedef struct
{
    ureg32 EN:1;            /* [0:0] Enable the reference phase - RW */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} RDC_REFPHASEEN_Bits;

/* Reference phase Register */
typedef struct
{
    sreg32 PHASE:18;        /* [17:0] Reference phase Value - RW */
    sreg32 reserved_18:14;  /* [31:18] Internal reserved */
} RDC_REFPHASE_Bits;

/* Security Mechanism Enable Register */
typedef struct
{
    ureg32 EN:2;            /* [1:0] Security mechanism enable register - RW */
    ureg32 reserved_2:30;   /* [31:2] Internal reserved */
} RDC_REGSAFETYEN_Bits;

/* Clear Register For The Register Alarm */
typedef struct
{
    ureg32 CLR:2;           /* [1:0] Clear Register For The Register Alarm - W1C */
    ureg32 reserved_2:30;   /* [31:2] Internal reserved */
} RDC_REGALARMCLR_Bits;

/* Reporting Register for Register Alarm Status */
typedef struct
{
    ureg32 LOSCLRRALM:1;      /* [0:0] LOS clr Alarm - RO (THA6412 support only) */
    ureg32 OOSCLRRALM:1;      /* [1:1] OOS clr Alarm - RO (THA6412 support only)*/
    ureg32 RSCLRRALM:1;       /* [2:2] RS clr Alarm - RO (THA6412 support only) */
    ureg32 LSTOCLRRALM:1;     /* [3:3] LST clr Alarm - RO (THA6412 support only) */
    ureg32 DOSCLRRALM:1;      /* [4:4] DOS clr Alarm - RO (THA6412 support only) */
    ureg32 REGSAFEENRALM:1;   /* [5:5] Reg Safety En Alarm - RO (THA6412 support only) */
    ureg32 REGACRALM:1;       /* [6:6] Reg Alarm clr - RO (THA6412 support only) */
    ureg32 EXTFREQMERALM:1;   /* [7:7] Fre mon En - RO (THA6412 support only) */
    ureg32 EXTFREQACRALM:1;   /* [8:8] Fre Alarm clr - RO (THA6412 support only) */
    ureg32 LOSENRALM:1;       /* [9:9] LOS Alarm - RO (THA6412 support only) */
    ureg32 DOSENRALM:1;       /* [10:10] DOS Alarm - RO (THA6412 support only) */
    ureg32 OOSENRALM:1;       /* [11:11] ORA Alarm - RO (THA6412 support only) */
    ureg32 EXTENRALM:1;       /* [12:12] Ext Alarm - RO (THA6412 support only) */
    ureg32 LSTOENRALM:1;      /* [13:13] Lvs Alarm - RO (THA6412 support only) */
    ureg32 RSENRALM:1;        /* [14:14] RS Alarm - RO (THA6412 support only) */
    ureg32 PERALM:1;          /* [15:15] RDCPE Register Redundancy Alarm State - RO (THA6412 support only) */
    ureg32 VELRALM:1;         /* [16:16] RDCVEL Register Redundancy Alarm State - RO (THA6412 support only) */
    ureg32 ANGRALM:1;         /* [17:17] RDCANG Register Redundancy Alarm State - RO (THA6412 support only) */
    ureg32 TRIGVELRALM:1;     /* [18:18] RDCTRIGVEL Register Redundancy Alarm State - RO (THA6412 support only) */
    ureg32 TRIGANGRALM:1;     /* [19:19] RDCTRIGANG Register Redundancy Alarm State - RO (THA6412 support only) */
    ureg32 TRIGTSMPRALM:1;    /* [20:20] RDCTRIGTSMP Register Redundancy Alarm State - RO (THA6412 support only) */
    ureg32 IAACALM:1;         /* [21:21] Illegal Access Alarm Clear Alarm Status - RO */
    ureg32 reserved_22:10;    /* [31:22] Internal reserved */
} RDC_REGALARMSTS_Bits;

/* SE Locked Illegal Access Alarm Clearing Register */
typedef struct
{
    ureg32 CLR:2;           /* [1:0] Illegal Access Alarm Alarm Clear - W1C */
    ureg32 reserved_2:30;   /* [31:2] Internal reserved */
} RDC_REGIACLR_Bits;

/* Interrupt Source Trigger Time Timestamp Reporting Register */
typedef struct
{
    ureg32 LOSCRASCLR:2;    /* [1:0] LOS Clear - W1C */
    ureg32 OOSCRASCLR:2;    /* [3:2] OOS Clear - W1C */
    ureg32 RSCRASCLR:2;     /* [5:4] RS Clear - W1C */
    ureg32 LSTOCRASCLR:2;   /* [7:6] LST Clear - W1C */
    ureg32 DOSCRASCLR:2;    /* [9:8] DOS Clear - W1C (THA6206 Ver.C not supported) */
    ureg32 reserved_10:22;  /* [31:10] Internal reserved */
} RDC_FUNALARMCLR_Bits;

/* LOST Of Signal Threshold Configuration Register */
typedef struct
{
    ureg32 TCFG:16;         /* [15:0] Threshold Configuration Register - RW */
    ureg32 reserved_16:16;  /* [31:15] Internal reserved */
} RDC_LOSTCFG_Bits;

/* Over Range Of Signal Threshold Configuration Register */
typedef struct
{
    ureg32 TCFG:16;         /* [15:0] Threshold Configuration Register - RW */
    ureg32 reserved_16:16;  /* [31:15] Internal reserved */
} RDC_OOSTCFG_Bits;

/* Loss of Tracking Threshold Configuration Register */
typedef struct
{
    sreg32 LTCFG:16;        /* [15:0] Loop stability lower limit configuration - RW */
    sreg32 HTCFG:16;        /* [31:15] Loop stability upper limit configuration - RW */
} RDC_LOTTCFG_Bits;

/* Reference Signal Error High Threshold Configuration Register */
typedef struct
{
    ureg32 TCFG:18;         /* [17:0] Threshold Configuration Register - RW */
    ureg32 reserved_16:14;  /* [31:18] Internal reserved */
} RDC_RSHTCFG_Bits;

/* Reference Signal Error Low Threshold Configuration Register */
typedef struct
{
    ureg32 TCFG:18;         /* [17:0] Threshold Configuration Register - RW */
    ureg32 reserved_16:14;  /* [31:18] Internal reserved */
} RDC_RSLTCFG_Bits;

/* Loop Stability Timeout Threshold Configuration Register */
typedef struct
{
    ureg32 CNT;             /* [31:0] Count Numbers - RW */
} RDC_LSTOTCFG_Bits;

/* Function Alarm Status Register */
typedef struct
{
    ureg32 LOSALM:1;       /* [0:0] LOS Alarm Status - RW */
    ureg32 DOSALM:1;       /* [1:1] DOS Alarm Status - RW (THA6206 Ver.C not supported) */
    ureg32 OOSALM:1;       /* [2:2] OOS Alarm Status - RW */
    ureg32 EXTALM:1;       /* [3:3] EXT Alarm Status - RW */
    ureg32 LSTOALM:1;      /* [4:4] LSTO Alarm Status - RW */
    ureg32 RSALM:1;        /* [5:5] RS Alarm Status - RW */
    ureg32 reserved_6:26;  /* [31:6] Internal reserved - RW */
} RDC_FUNALARMSTS_Bits;

/* Degradation Of Signal Mismatch Threshold Configuration Register */
typedef struct
{
    ureg32 TCFG:16;         /* [15:0] Threshold Configuration Register - RW */
    ureg32 reserved_16:16;  /* [31:15] Internal reserved */
} RDC_DOSMMTTCFG_Bits;

/* Frequency Monitor Enable */
typedef struct
{
    ureg32 EN:2;            /* [1:0] Enable Control Register - RW */
    ureg32 reserved_2:30;   /* [31:2] Internal reserved */
} RDC_FREMONEN_Bits;

/* Frequency Monitor Threshold Configration Register */
typedef struct
{
    ureg32 TLCFG:16;        /* [15:0] Frequency lower limit configuration - RW */
    ureg32 THCFG:16;        /* [31:15] Frequency upper limit configuration - RW */
} RDC_FREMONCFG_Bits;

/* Frequency Monitor Alarm Clear Register */
typedef struct
{
    ureg32 CLR:2;           /* [1:0] Frequency Monitor Alarm Clear Register - W1C */
    ureg32 reserved_2:30;   /* [31:2] Internal reserved */
} RDC_FREALARMCLR_Bits;

/* Degradation Of Signal window Register */
typedef struct
{
    ureg32 EN:1;            /* [0:0] Enable Control Register - RW */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} RDC_DOSWIN_Bits;

/* Loop Stable Reporting Register */
typedef struct
{
    ureg32 STS:1;           /* [0:0] Loop Stability Flag Reporting Register - RW */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} RDC_LSRPT_Bits;

/* Function Safety EEnable Register */
typedef struct
{
    ureg32 LOSEN:2;         /* [1:0] LOS Security Mechanism Enables Control of Registers - RW */
    ureg32 DOSEN:2;         /* [3:2] DOS Security Mechanism Enables Control of Registers - RW
                                     (THA6206 Ver.C not supported)*/
    ureg32 ORAEN:2;         /* [5:4] ORA Security Mechanism Enables Control of Registers - RW */
    ureg32 EXTEN:2;         /* [7:7] EXT Security Mechanism Enables Control of Registers - RW */
    ureg32 LSVEN:2;         /* [9:8] LSV Security Mechanism Enables Control of Registers - RW */
    ureg32 RSEN:2;          /* [11:10] RS Security Mechanism Enables Control of Registers - RW */
    ureg32 reserved_12:20;  /* [31:12] Internal reserved */
} RDC_FUNSAFETYEN_Bits;

/* Illegal Access Signal protected by SE Register */
typedef struct
{
    ureg32 STS:1;           /* [0:0] Illegal access to SE protected signal status - RW */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} RDC_REGIAALARMSTS_Bits;

/**********************************************************************************************************************
 *                                              RDC Register Definitions
 *********************************************************************************************************************/
/* CWDR register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;        /* Unsigned access */
    sreg32 I;        /* Signed access */
    RDC_CWDR_Bits B; /* Bitfield access */
} RDC_CWDR;

/* CWPOINTS register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    sreg32 I;            /* Signed access */
    RDC_CWPOINTS_Bits B; /* Bitfield access */
} RDC_CWPOINTS;

/* CWCFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;         /* Unsigned access */
    sreg32 I;         /* Signed access */
    RDC_CWCFG_Bits B; /* Bitfield access */
} RDC_CWCFG;

/* CWCTRL register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    sreg32 I;          /* Signed access */
    RDC_CWCTRL_Bits B; /* Bitfield access */
} RDC_CWCTRL;

/* DPLLKP register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    sreg32 I;          /* Signed access */
    RDC_DPLLKP_Bits B; /* Bitfield access */
} RDC_DPLLKP;

/* DPLLKI register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    sreg32 I;          /* Signed access */
    RDC_DPLLKI_Bits B; /* Bitfield access */
} RDC_DPLLKI;

/* MAINKP register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    sreg32 I;          /* Signed access */
    RDC_MAINKP_Bits B; /* Bitfield access */
} RDC_MAINKP;

/* MAINKI register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    sreg32 I;          /* Signed access */
    RDC_MAINKI_Bits B; /* Bitfield access */
} RDC_MAINKI;

/* DCOFFSET register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    sreg32 I;            /* Signed access */
    RDC_DCOFFSET_Bits B; /* Bitfield access */
} RDC_DCOFFSET;

/* GAINOFFSET register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    sreg32 I;              /* Signed access */
    RDC_GAINOFFSET_Bits B; /* Bitfield access */
} RDC_GAINOFFSET;

/* RECFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;         /* Unsigned access */
    sreg32 I;         /* Signed access */
    RDC_RECFG_Bits B; /* Bitfield access */
} RDC_RECFG;

/* CPUTRI register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    sreg32 I;          /* Signed access */
    RDC_CPUTRI_Bits B; /* Bitfield access */
} RDC_CPUTRI;

/* CPE register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;       /* Unsigned access */
    sreg32 I;       /* Signed access */
    RDC_CPE_Bits B; /* Bitfield access */
} RDC_CPE;

/* VEL register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;       /* Unsigned access */
    sreg32 I;       /* Signed access */
    RDC_VEL_Bits B; /* Bitfield access */
} RDC_VEL;

/* ANG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;       /* Unsigned access */
    sreg32 I;       /* Signed access */
    RDC_ANG_Bits B; /* Bitfield access */
} RDC_ANG;

/* TRIVEL register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    sreg32 I;          /* Signed access */
    RDC_TRIVEL_Bits B; /* Bitfield access */
} RDC_TRIVEL;

/* TRIANG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    sreg32 I;          /* Signed access */
    RDC_TRIANG_Bits B; /* Bitfield access */
} RDC_TRIANG;

/* TRITSMP register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    sreg32 I;             /* Signed access */
    RDC_TRIGTSMP_Bits B;  /* Bitfield access */
} RDC_TRIGTSMP;

/* IQEXTREVALCLR register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    sreg32 I;                 /* Signed access */
    RDC_IQEXTREVALCLR_Bits B; /* Bitfield access */
} RDC_IQEXTREVALCLR;

/* IEXTREVALRPT register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    sreg32 I;                /* Signed access */
    RDC_IEXTREVALRPT_Bits B; /* Bitfield access */
} RDC_IEXTREVALRPT;

/* QEXTREVALRPT register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;                /* Unsigned access */
    sreg32 I;                /* Signed access */
    RDC_QEXTREVALRPT_Bits B; /* Bitfield access */
} RDC_QEXTREVALRPT;

/* MONRPT register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    sreg32 I;           /* Signed access */
    RDC_MONRPT_Bits B;  /* Bitfield access */
} RDC_MONRPT;

/* BUSERRMSK register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    sreg32 I;             /* Signed access */
    RDC_BUSERRMSK_Bits B; /* Bitfield access */
} RDC_BUSERRMSK;

/* REFPHASEEN register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    sreg32 I;              /* Signed access */
    RDC_REFPHASEEN_Bits B; /* Bitfield access */
} RDC_REFPHASEEN;

/* REFPHASE register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    sreg32 I;            /* Signed access */
    RDC_REFPHASE_Bits B; /* Bitfield access */
} RDC_REFPHASE;

/* REGSAFETYEN register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    sreg32 I;               /* Signed access */
    RDC_REGSAFETYEN_Bits B; /* Bitfield access */
} RDC_REGSAFETYEN;

/* REGALARMCLR register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    sreg32 I;               /* Signed access */
    RDC_REGALARMCLR_Bits B; /* Bitfield access */
} RDC_REGALARMCLR;

/* REGALARMSTS register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    sreg32 I;               /* Signed access */
    RDC_REGALARMSTS_Bits B; /* Bitfield access */
} RDC_REGALARMSTS;

/* REGIACLR register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    sreg32 I;            /* Signed access */
    RDC_REGIACLR_Bits B; /* Bitfield access */
} RDC_REGIACLR;

/* FUNALARMCLR register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    sreg32 I;               /* Signed access */
    RDC_FUNALARMCLR_Bits B; /* Bitfield access */
} RDC_FUNALARMCLR;

/* LOSTCFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    sreg32 I;           /* Signed access */
    RDC_LOSTCFG_Bits B; /* Bitfield access */
} RDC_LOSTCFG;

/* OOSTCFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    sreg32 I;           /* Signed access */
    RDC_OOSTCFG_Bits B; /* Bitfield access */
} RDC_OOSTCFG;

/* LOTTCFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    sreg32 I;           /* Signed access */
    RDC_LOTTCFG_Bits B; /* Bitfield access */
} RDC_LOTTCFG;

/* RSHTCFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    sreg32 I;           /* Signed access */
    RDC_RSHTCFG_Bits B; /* Bitfield access */
} RDC_RSHTCFG;

/* RSLTCFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    sreg32 I;           /* Signed access */
    RDC_RSLTCFG_Bits B; /* Bitfield access */
} RDC_RSLTCFG;

/* LSTOTCFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    sreg32 I;            /* Signed access */
    RDC_LSTOTCFG_Bits B; /* Bitfield access */
} RDC_LSTOTCFG;

/* FUNALARMSTS */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    sreg32 I;            /* Signed access */
    RDC_FUNALARMSTS_Bits B; /* Bitfield access */
} RDC_FUNALARMSTS;


/* DOSMMTTCFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    sreg32 I;              /* Signed access */
    RDC_DOSMMTTCFG_Bits B; /* Bitfield access */
} RDC_DOSMMTTCFG;

/* FREMONEN register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    sreg32 I;            /* Signed access */
    RDC_FREMONEN_Bits B; /* Bitfield access */
} RDC_FREMONEN;

/* FREMONCFG register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    sreg32 I;             /* Signed access */
    RDC_FREMONCFG_Bits B; /* Bitfield access */
} RDC_FREMONCFG;

/* FREALARMCLR register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    sreg32 I;               /* Signed access */
    RDC_FREALARMCLR_Bits B; /* Bitfield access */
} RDC_FREALARMCLR;

/* DOSWIN register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    sreg32 I;           /* Signed access */
    RDC_DOSWIN_Bits B;  /* Bitfield access */
} RDC_DOSWIN;

/* LSRPT register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    sreg32 I;           /* Signed access */
    RDC_LSRPT_Bits B;   /* Bitfield access */
} RDC_LSRPT;

/* FUNSAFETYEN register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    sreg32 I;               /* Signed access */
    RDC_FUNSAFETYEN_Bits B; /* Bitfield access */
} RDC_FUNSAFETYEN;

/* REGIAALARMSTS register */
typedef union
/* #Violation: rdc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    sreg32 I;                 /* Signed access */
    RDC_REGIAALARMSTS_Bits B; /* Bitfield access */
} RDC_REGIAALARMSTS;

/**********************************************************************************************************************
 *                                        RDC Register Configuration Structure
 *********************************************************************************************************************/
/* RDC Object */
typedef volatile struct
{
    RDC_CWDR CWDRx[20];              /* 0x0 - Excitation carrier duty cycle configuration register */
    RDC_CWPOINTS CWPOINTS;           /* 0x54 - Number of carrier points and number of sine points configuration
                                               register */
    RDC_CWCFG CWCFG;                 /* 0x58 - Excitation carrier configuration register */
    RDC_CWCTRL CWCTRL;               /* 0x5C - Excitation carrier control register */
    RDC_DPLLKP DPLLKP;               /* 0x60 - Solve the loop carrier recovery loop kp configuration register */
    RDC_DPLLKI DPLLKI;               /* 0x64 - Solve the loop carrier recovery loop ki configuration register */
    RDC_MAINKP MAINKP;               /* 0x68 - Solve the loop carrier main loop kp configuration register */
    RDC_MAINKI MAINKI;               /* 0x6C - Solve the loop carrier main loop ki configuration register */
    RDC_DCOFFSET DCOFFSET;           /* 0x70 - RDC solves the loop dc bias compensation register */
    RDC_GAINOFFSET GAINOFFSET;       /* 0x74 - RDC solves the loop gain bias compensation register */
    RDC_RECFG RECFG;                 /* 0x78 - RDC solves the loop configuration register */
    RDC_CPUTRI CPUTRI;               /* 0x7C - RDC cpu trigger register */
    RDC_CPE CPE;                     /* 0x80 - RDC solves the loop phase estimation reporting register */
    RDC_VEL VEL;                     /* 0x84 - The speed value of the real-time solution of the rdc solution loop
                                               register */
    RDC_ANG ANG;                     /* 0x88 - The angle value of the real-time solution of the rdc solution loop
                                               register */
    RDC_TRIVEL TRIVEL;               /* 0x8C - The speed value triggered by the interrupt is reported register */
    RDC_TRIANG TRIANG;               /* 0x90 - The angle value triggered by the interrupt is reported register */
    RDC_TRIGTSMP TRIGTSMP;           /* 0x94 - The time value triggered by the interrupt is reported register */
    RDC_IQEXTREVALCLR IQEXTREVALCLR; /* 0x98 - IQ Extreme Value Clear Register */
    RDC_IEXTREVALRPT IEXTREVALRPT;   /* 0x9C - I Extreme Value Reporting Register */
    RDC_QEXTREVALRPT QEXTREVALRPT;   /* 0xA0 - Q Extreme Value Reporting Register */
    RDC_MONRPT MONRPT;               /* 0xA4 - Monitor Signal Report Register */
    RDC_BUSERRMSK BUSERRMSK;         /* 0xA8 - Bus Error Mask Register */
    RDC_REFPHASEEN  REFPHASEEN;      /* 0xAC - Phase Reference Enable Register (THA6412 support only) */
    RDC_REFPHASE    REFPHASE;        /* 0XB0 - Phase Reference Value Register (THA6412 support only) */
    uint8  reserved_B4[156];         /* 0xB4 - Internal Reserved */
    RDC_REGSAFETYEN REGSAFETYEN;     /* 0x150 - Security Mechanism Enable Register (THA6412 support only) */
    RDC_REGALARMCLR REGALARMCLR;     /* 0x154 - Clear Register For The Register Alarm (THA6412 support only) */
    RDC_REGALARMSTS REGALARMSTS;     /* 0x158 - Reporting Register for Register Alarm Status */
    RDC_REGIACLR REGIACLR;           /* 0x15C - Register Illegal Access Alarm Clearing Register */
    RDC_FUNALARMCLR FUNALARMCLR;     /* 0x160 - Interrupt Source Trigger Time Timestamp Reporting Register */
    RDC_LOSTCFG LOSTCFG;             /* 0x164 - LOST Of Signal Threshold Configuration Register */
    RDC_OOSTCFG OOSTCFG;             /* 0x168 - Over Range Of Signal Threshold Configuration Register */
    RDC_LOTTCFG LOTTCFG;             /* 0x16C - Loss of Tracking Threshold Configuration Register */
    RDC_RSHTCFG RSHTCFG;             /* 0x170 - Reference Signal Error High Threshold Configuration Register */
    RDC_RSLTCFG RSLTCFG;             /* 0x174 - Reference Signal Error Low Threshold Configuration Register */
    RDC_LSTOTCFG LSTOTCFG;           /* 0x178 - Loop Stability Timeout Threshold Configuration Register */
    RDC_FUNALARMSTS FUNALARMSTS;     /* 0x17C - Function Alarm Status Register */
    RDC_DOSMMTTCFG DOSMMTTCFG;       /* 0x180 - Degradation Of Signal Mismatch Threshold Configuration Register
                                                (THA6206 Ver.C not supported) */
    RDC_FREMONEN FREMONEN;           /* 0x184 - Frequency Monitor Enable */
    RDC_FREMONCFG FREMONCFG;         /* 0x188 - Frequency Monitor Threshold Configuration Register */
    RDC_FREALARMCLR FREALARMCLR;     /* 0x18C - Frequency Monitor Alarm Clear Register */
    RDC_DOSWIN DOSWIN;               /* 0x190 - Degradation Of Signal window Register (THA6206 Ver.C not supported) */
    RDC_LSRPT LSRPT;                 /* 0x194 - Loop Stable Reporting Register */
    RDC_FUNSAFETYEN FUNSAFETYEN;     /* 0x198 - Function Safety EEnable Register */
    RDC_REGIAALARMSTS REGIAALARMSTS; /* 0x19C - Illegal Access Signal protected by SE Register */
} RDC_MODULE;


#endif /* RDC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

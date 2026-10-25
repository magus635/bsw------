/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dsadc_register.h
 * Author:      30037
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of DSADC module registers.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #dsadc_register_h_REF_1:MISRAC2012-Rule-19.2
* Justification:Using unions for bit-field access to registers.
*
* #dsadc_register_h_REF_2:CERTC-DCL12-C;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*/
#ifndef DSADC_REGISTER_H_
#define DSADC_REGISTER_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        DASDC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Modulator configuration register */
typedef struct
{
    ureg32 PINSET : 1;       /* [ 0: 0] Setting of positive input line (RW) */
    ureg32 NINSET : 1;       /* [ 1: 1] Setting of negative input line (RW) */
    ureg32 PINEN : 1;        /* [ 2: 2] Positive input enable (RW) */
    ureg32 NINEN : 1;        /* [ 3: 3] Negative input enable (RW) */
    ureg32 PGAGSEL : 3;      /* [ 6: 4] Gain select of analog input path (RW) */
    ureg32 reserved_7 : 1;   /* [ 7: 7] Internal reserved */
    ureg32 INPSEL : 1;       /* [ 8: 8] Input pin selection (RW) */
    ureg32 reserved_9 : 1;   /* [ 9: 9] Internal reserved */
    ureg32 INMUXS : 1;       /* [10:10] Input multiplexer setting (RW) */
    ureg32 COMVOSPAEN : 1;   /* [11:11] Common Voltage SPA Enable (RW) */
    ureg32 INMCP : 2;        /* [13:12] Input multiplexer control pattern (RW) */
    ureg32 INMCC : 1;        /* [14:14] Input multiplexer changing control (RW) */
    ureg32 INPWP : 1;        /* [15:15] Write Protection for Input Parameters (WO) */
    ureg32 FDIVC : 4;        /* [19:16] Frequency divider cofficient (RW) */
    ureg32 APC : 1;          /* [20:20] Automatic power control (RW) */
    ureg32 MPSWP : 1;        /* [21:21] Configuring register FDIVC and APC write protection (WO)*/
    ureg32 reserved_22 : 6;  /* [27:22] Internal reserved */
    ureg32 INPACSEL : 1;     /* [28:28] Input port DS1PA and DS1PC select (RW) */
    ureg32 INNACSEL : 1;     /* [29:29] Input port DS1NA and DS1NC select (RW) */
    ureg32 INPBDSEL : 1;     /* [30:30] Input port DS1PB and DS1PD select (RW) */
    ureg32 INNBDSEL : 1;     /* [31:31] Input port DS1NB and DS1ND select (RW) */
} DSADC_MODCFG_Bits;

/* Demodulator input configuration Register */
typedef struct
{
    ureg32 TRGSEL : 4;       /* [ 3: 0] Trigger select (RW) */
    ureg32 TSTRP : 2;        /* [ 5: 4] Timestamp trigger pattern (RW) */
    ureg32 TSP : 1;          /* [ 6: 6] Timestamp pattern (RW) */
    ureg32 RDP : 1;          /* [ 7: 7] Conversion result display pattern (RW) */
    ureg32 MSWP : 1;         /* [ 8: 8] Write protection for mode settings (RW) */
    ureg32 reserved_9 : 2;   /* [10: 9] Internal reserved */
    ureg32 RSTADC : 1;       /* [11:11] ADC loop reset signal (RW) */
    ureg32 reserved_12 : 1;  /* [12:12] Internal reserved */
    ureg32 FIFOBYPASS : 1;   /* [13:13] Fifo Bypass (RW) */
    ureg32 reserved_14 : 18; /* [31:14] Internal reserved */
} DSADC_DEMICFG_Bits;

/* Common pattern voltage configuration register */
typedef struct
{
    ureg32 reserved_0 : 4;   /* [ 3: 0] Internal reserved */
    ureg32 VXEN : 1;         /* [ 4: 4] Common mode voltage enable (RW) */
    ureg32 reserved_5 : 15;  /* [19: 5] Internal reserved */
    ureg32 COMVOSNAEN : 1;   /* [20:20] Common Voltage SNA Enable (RW) */
    ureg32 COMVOSNBEN : 1;   /* [21:21] Common Voltage SNB Enable (RW) */
    ureg32 reserved_22 : 10; /* [31:22] Internal reserved */
} DSADC_CPVCFG_Bits;

/* Result FIFO control register */
typedef struct
{
    ureg32 SRLVAL : 2;       /* [ 1: 0] Service request FIFO value (RW) */
    ureg32 reserved_2 : 2;   /* [ 3: 2] Internal reserved */
    ureg32 RDECLR : 1;       /* [ 4: 4] Read error flag clear (WO) */
    ureg32 WRECLR : 1;       /* [ 5: 5] Write error flag clear (WO) */
    ureg32 FICLR : 1;        /* [ 6: 6] FIFO clear (WO) */
    ureg32 reserved_7 : 9;   /* [15: 7] Internal reserved */
    ureg32 FILLVAL : 3;      /* [18:16] FIFO fill Value (RO) */
    ureg32 RDEF : 1;         /* [19:19] Read error flag (RO) */
    ureg32 WREF : 1;         /* [20:20] Write error flag (RO) */
    ureg32 reserved_21 : 11; /* [31:21] Internal reserved */
} DSADC_RFCON_Bits;

/* Main conversion result register */
typedef struct
{
    ureg32 MCRES : 16;       /* [15: 0] Main conversion result value (RO) */
    ureg32 reserved_16 : 16; /* [31:16] Internal reserved */
} DSADC_MCRES_Bits;

/* Time-Stamp register */
typedef struct
{
    ureg32 TSTMPVAL : 16;    /* [15: 0] The most recent captured timestamp value (RO) */
    ureg32 AMSET : 1;        /* [16:16] Analog multiplexer setting (RO) */
    ureg32 reserved_17 : 1;  /* [17:17] Internal reserved */
    ureg32 TSVF : 1;         /* [18:18] Timestamp valid flag (RO) */
    ureg32 reserved_19 : 13; /* [31:19] Internal reserved */
} DSADC_TSTMP_Bits;

/* Time-Stamp counter */
typedef struct
{
    ureg32 TSCVAL : 16;      /* [15: 0] Timestamp counter value (RO) */
    ureg32 TSCCS : 2;        /* [17:16] Timestamp counter clock selection (RW) */
    ureg32 TSCSC : 1;        /* [18:18] Timestamp counter start control (RW) */
    ureg32 AMSCEN : 1;       /* [19:19] Analog multiple sector copy enable (RW) */
    ureg32 reserved_20 : 12; /* [31:20] Internal reserved */
} DSADC_TSCNT_Bits;

/* Main filter configuration register */
typedef struct
{
    ureg32 MCFEN : 1;       /* [ 0: 0] Main CIC filter enable (RW) */
    ureg32 MCFSF : 7;       /* [ 7: 1] Main CIC filter sampling factor (RW) */
    ureg32 MCPS : 2;        /* [ 9: 8] Main CIC parallel series selection (RW) */
    ureg32 MCGSL : 5;       /* [14:10] Main CIC gain shift length (RW) */
    ureg32 INTERBYPASS : 1; /* [15:15] Intergrator Bypass (RW) */
    ureg32 MGSRC : 2;       /* [17:16] Main generation service request configuration (RW) */
    ureg32 MAGCS : 2;       /* [19:18] Main alarm generation condition selection (RW) */
    ureg32 FIR0DEC : 1;     /* [20:20] FIR0 filter decimation rate (RW) */
    ureg32 FIR1DEC : 1;     /* [21:21] FIR1 filter decimation rate (RW) */
    ureg32 reserved_22 : 1; /* [22:22] Internal reserved */
    ureg32 COMVOSPBBYPASS : 1; /* [23:23] Common Voltage SPB Bypass (RW) */
    ureg32 FIR0FEN : 1;     /* [24:24] FIR0 output enable (RW) */
    ureg32 FIR1FEN : 1;     /* [25:25] FIR1 output enable (RW) */
    ureg32 FIR0OSF : 1;     /* [26:26] FIR0 output shift (RW) */
    ureg32 FIR1OSF : 2;     /* [28:27] FIR1 output shift (RW) */
    ureg32 OCENCFG : 3;     /* [31:29] Offset compensation filter configuration (RW) */
} DSADC_MFCFG_Bits;

/* Auxiliary filter configuration register */
typedef struct
{
    ureg32 ACFEN : 1;        /* [ 0: 0] Auxiliary CIC filter enable (RW) */
    ureg32 ACFDF : 5;        /* [ 5: 1] Auxiliary CIC filter decimation factor (RW) */
    ureg32 reserved_6 : 2;   /* [ 7: 6] Internal reserved */
    ureg32 ACPS : 2;         /* [ 9: 8] Auxiliary CIC parallel series selection (RW) */
    ureg32 ACGSL : 5;        /* [14:10] Auxiliary CIC gain shift length (RW) */
    ureg32 reserved_15 : 1;  /* [15:15] Internal reserved */
    ureg32 AGSRC : 2;        /* [17:16] Auxiliary generation service request configuration (RW) */
    ureg32 AAGCS : 2;        /* [19:18] Auxiliary alarm generation condition selection (RW) */
    ureg32 reserved_20 : 12; /* [31:20] Internal reserved */
} DSADC_AFCFG_Bits;

/* Gain offset ctrl register */
typedef struct
{
    ureg32 GAINOFFEN : 1;    /* [ 0: 0] Fine gain offset enable (RW) */
    ureg32 GAINOFF : 8;      /* [ 8: 1] Gain offset value (RW) */
    ureg32 reserved_9 : 7;   /* [15: 9] Internal reserved */
    ureg32 OFFSETVAL : 3;    /* [18:16] Offset Value (RW) */
    ureg32 reserved_19 : 13; /* [31:19] Internal reserved */
} DSADC_GAINCTR_Bits;

/* Threshold check limit register */
typedef struct
{
    ureg32 TCUL : 16; /* [15: 0] Threshold check upper limit (RW) */
    ureg32 TCLL : 16; /* [31:16] Threshold check lower limit (RW) */
} DSADC_THRESLM_Bits;

/* Auxiliary conversion result register */
typedef struct
{
    ureg32 ACRES : 16;       /* [15: 0] Most recent conversion result of auxiliary filter (RO) */
    ureg32 reserved_16 : 16; /* [31:16] Internal reserved */
} DSADC_ACRES_Bits;

/* Interrupt enable register */
typedef struct
{
    ureg32 TRIGIE : 1;       /* [ 0: 0] External trigger interrupt enable (RW) */
    ureg32 FIFOFILLIE : 1;   /* [ 1: 1] FIFO full interrupt enable (RW) */
    ureg32 SAMIE : 1;        /* [ 2: 2] Main channel result more than high limmit interrupt enable (RW) */
    ureg32 SBMIE : 1;        /* [ 3: 3] Main channel result less than low limmit interrupt enable (RW) */
    ureg32 TSTMPIE : 1;      /* [ 4: 4] Timestamp interrupt enable (RW) */
    ureg32 SAAIE : 1;        /* [ 5: 5] Auxiliary channel result more than high limmit interrupt enable (RW) */
    ureg32 SBAIE : 1;        /* [ 6: 6] Auxiliary channel result less than low limmit interrupt enable (RW) */
    ureg32 REAIE : 1;        /* [ 7: 7] Auxiliary transition completes interrupt enable (RW) */
    ureg32 DMAFIFOIE : 1;    /* [ 8: 8] DMA FIFO request interrupt enable (RW) */
    ureg32 DMATRIGIE : 1;    /* [ 9: 9] DMA external triggrt interrupt enable (RW) */
    ureg32 DMATSTMPIE : 1;   /* [10:10] DMA timestamp interrupt enable (RW) */
    ureg32 DMAREAIE : 1;     /* [11:11] Auxiliary DMA transition completes interrupt enable (RW) */
    ureg32 reserved_12 : 20; /* [31:12] Internal reserved */
} DSADC_INTEN_Bits;

/* Interrupt clear register */
typedef struct
{
    ureg32 TRIGCLR : 1;     /* [ 0: 0] External trigger interrupt clear (RWH) */
    ureg32 FIFOFILLCLR : 1; /* [ 1: 1] FIFO full interrupt clear (RWH) */
    ureg32 SAMCLR : 1;      /* [ 2: 2] Main channel result more than high limmit interrupt clear (RWH) */
    ureg32 SBMCLR : 1;      /* [ 3: 3] Main channel result less than low limmit interrupt clear (RWH) */
    ureg32 TSTMPCLR : 1;    /* [ 4: 4] Timestamp interrupt clear (RWH) */
    ureg32 SAACLR : 1;      /* [ 5: 5] Auxiliary channel result more than high limmit interrupt clear (RWH) */
    ureg32 SBACLR : 1;      /* [ 6: 6] Auxiliary channel result less than low limmit interrupt clear (RWH) */
    ureg32 REACLR : 1;      /* [ 7: 7] Auxiliary transition completes interrupt clear (RWH) */
    ureg32 DMARCLR : 1;     /* [ 8: 8] DMA request loss alarm clear (RWH)*/
    ureg32 reserved_9 : 23; /* [31: 9] Internal reserved */
} DSADC_INTCLR_Bits;

/* Interrupt status register */
typedef struct
{
    ureg32 TRIGST : 1;      /* [ 0: 0] External trigger interrupt status (RO) */
    ureg32 FIFOFILLST : 1;  /* [ 1: 1] FIFO full interrupt status (RO) */
    ureg32 SAMST : 1;       /* [ 2: 2] Main channel result more than high limmit interrupt status (RO) */
    ureg32 SBMST : 1;       /* [ 3: 3] Main channel result less than low limmit interrupt status (RO) */
    ureg32 TSTMPST : 1;     /* [ 4: 4] Timestamp interrupt status (RO) */
    ureg32 SAAST : 1;       /* [ 5: 5] Auxiliary channel result more than high limmit interrupt status (RO) */
    ureg32 SBAST : 1;       /* [ 6: 6] Auxiliary channel result less than low limmit interrupt status (RO) */
    ureg32 REAST : 1;       /* [ 7: 7] Auxiliary transition completes interrupt status (RO) */
    ureg32 reserved_8 : 24; /* [31: 8] Internal reserved */
} DSADC_INTSTS_Bits;

/* Test configuration register */
typedef struct
{
    ureg32 TESTSEL : 3;     /* [ 2: 0] Common mode test voltage output control (RW) */
    ureg32 reserved_3 : 29; /* [31: 3] Internal reserved */
} DSADC_TESTCFG_Bits;

/* Compensating register */
typedef struct
{
    ureg32 GCOFFSET : 16; /* [15: 0] Gain compensation offset (RW) */
    ureg32 DCOFFSET : 16; /* [31:16] DC compensation offset (RW) */
} DSADC_COMP_Bits;

/* Safety mechanism enable */
typedef struct
{
    ureg32 REGSMEN : 2;      /* [ 1: 0] Register redundancy safety mechanism enable (RW) */
    ureg32 FISMEN : 2;       /* [ 3: 2] FIFO write full or read empty safety mechanism enable (RW) */
    ureg32 DASMEN : 2;       /* [ 5: 4] Data exceed threshold safety mechanism enable (RW) */
    ureg32 DMASMEN : 2;      /* [ 7: 6] DMA timeout safety mechanism enable (RW) */
    ureg32 TRIGSMEN : 2;     /* [ 9: 8] Trigger timeout safety mechanism enable (RW) */
    ureg32 reserved_10 : 22; /* [31:10] Internal reserved */
} DSADC_SMEN_Bits;

/* Alarm clear register */
typedef struct
{
    ureg32 REGACLR : 2;      /* [ 1: 0] Register redundancy alarm clear (W1C) */
    ureg32 FIACLR : 2;       /* [ 3: 2] FIFO write full or read empty alarm clear (W1C) */
    ureg32 DAACLR : 2;       /* [ 5: 4] Data exceed threshold alarm clear (W1C) */
    ureg32 DMAACLR : 2;      /* [ 7: 6] DMA timeout alarm clear (W1C) */
    ureg32 TRIGACLR : 2;     /* [ 9: 8] Trigger timeout alarm clear (W1C) */
    ureg32 SEACLR : 2;       /* [11:10] Illegal acess signal protected by SE alarm clear (W1C) */
    ureg32 reserved_12 : 20; /* [31:12] Internal reserved */
} DSADC_ALACLR_Bits;

/* Alarm state register */
typedef struct
{
    ureg32 SMREAST : 1;     /* [ 0: 0] SMEN register redundancy alarm state (RO) */
    ureg32 ACLRERST : 1;    /* [ 1: 1] ALACLR register redundancy alarm state (RO) */
    ureg32 FIREGAST : 1;    /* [ 2: 2] FAIN register redundancy alarm state (RO) */
    ureg32 MRESAST : 1;     /* [ 3: 3] Main result redundancy alarm state (RO) */
    ureg32 FIAST : 1;       /* [ 4: 4] FIFO write full or read empty alarm state (RO) */
    ureg32 DAAST : 1;       /* [ 5: 5] Data exceed threshold alarm clear (RO) */
    ureg32 DMAAST : 1;      /* [ 6: 6] DMA timeout alarm state (RO) */
    ureg32 TRIGAST : 1;     /* [ 7: 7] Trigger timeout alarm state (RO) */
    ureg32 SEAST : 1;       /* [ 8: 8] Illegal acess signal protected by SE alarm state (RO) */
    ureg32 DMALOST : 1;     /* [ 9: 9] DMA Request Lost State (RO) */
    ureg32 reserved_10 : 22;/* [31: 10] Internal reserved */
} DSADC_ALASTS_Bits;

/* Fault injection register */
typedef struct
{
    ureg32 DMAFAIN : 2;     /* [ 1: 0] DMA timeout fault inject (RW) */
    ureg32 TRIGFAIN : 2;    /* [ 3: 2] Trigger timeout fault inject (RW) */
    ureg32 reserved_4 : 28; /* [31: 4] Internal reserved */
} DSADC_FAIN_Bits;

/* DMA timeout threshold */
typedef struct
{
    ureg32 DMATHRES : 32; /* [31: 0] DMA timeout threshold (RW) */
} DSADC_DMATHRES_Bits;

/* Trigger timeout threshold */
typedef struct
{
    ureg32 TRIGTHRES : 32; /* [31: 0] Trigger timeout threshold (RW) */
} DSADC_TRIGTHRES_Bits;

/* Calibration control register */
typedef struct
{
    ureg32 GCOBEN : 1;      /* [ 0: 0] Fine gain offset bypass enable (RW) */
    ureg32 DCOBEN : 1;      /* [ 1: 1] Automatic DC offset bypass enable (RW) */
    ureg32 VSELLV : 2;      /* [ 3: 2] Calibration voltage selection (RW) */
    ureg32 CALSELLV : 2;    /* [ 5: 4] Calibration input selection (RW) */
    ureg32 CALEN : 1;       /* [ 6: 6] Calibrating enable (RW) */
    ureg32 reserved_7 : 25; /* [31: 7] Internal reserved */
} DSADC_COMPCON_Bits;

/* Test mode */
typedef struct
{
    ureg32 TESTMODE : 1;    /* [ 0: 0] Test mode (RW) */
    ureg32 reserved_1 : 31; /* [31: 1] Internal reserved */
} DSADC_TESTMODE_Bits;

/* Ditehering enable register */
typedef struct
{
    ureg32 DITHEREN : 1;    /* [ 0: 0] Dithering mode enable (RW) */
    ureg32 reserved_1 : 31; /* [31: 1] Internal reserved */
} DSADC_DITHEREN_Bits;

/* Carrier wave configration register */
typedef struct
{
    ureg32 EN : 1;           /* [ 0: 0] Excitation enable (RW) */
    ureg32 MODE : 2;         /* [ 2: 1] Wave mode configuration (RW) */
    ureg32 PCMEN : 1;        /* [ 3: 3] PCM enable (RW) */
    ureg32 CWPHICRL : 1;     /* [ 4: 4] Carrier waveform (RW) */
    ureg32 reserved_5 : 3;   /* [ 7: 5] Internal reserved */
    ureg32 PERCYCLE : 5;     /* [12: 8] Excitation Micro-step Cycle Index (RH) */
    ureg32 PERINDEX : 5;     /* [17: 13] Excitation Micro-step Index (RH) */
    ureg32 SIGNBIT : 1;      /* [18:18] Excitation results (RH) */
    ureg32 SYNSIGNBIT : 1;   /* [19:19] Excitation results after synchronization completion (RH) */
    ureg32 reserved_20 : 12; /* [31:20] Internal reserved */
} DSADC_CWCFG_Bits;

/* Carrier wave sync control register */
typedef struct
{
    ureg32 SYNCEND : 8;   /* [ 7: 0] Synchronised signal end (RW) */
    ureg32 SYNCSTART : 8; /* [15: 8] Synchronised signal start (RW) */
    ureg32 DELAY : 8;     /* [23:16] Delay value (RO) */
    ureg32 CNT : 8;       /* [31:24] Delay counter (RO) */
} DSADC_CWSYNC_Bits;

/* Intergrator Control Register  */
typedef struct
{
    ureg32 SFL : 3;          /* [ 2: 0] Shift length control (RW) */
    ureg32 MODE : 1;         /* [ 3: 3] Mean mode (RW) */
    ureg32 LEN : 6;          /* [ 9: 4] Mean Points (RW) */
    ureg32 reserved_10 : 22; /* [31:10] Internal reserved */
} DSADC_INTERCON_Bits;

/* Bus error mask register */
typedef struct
{
    ureg32 BUSERRMSK : 1;     /* [ 0: 0] Bus error mask (RW) */
    ureg32 DMALOSSMASK : 1;   /* [ 1: 1] DMA request loss mask (RW) */
    ureg32 reserved_2 : 30;   /* [31: 2] Internal reserved */
} DSADC_BUSERRMSK_Bits;

/* Suspend Public Register Configure In Debug Mode */
typedef struct
{
    ureg32 SUSCTRL : 4;     /* [ 3: 0] Debug suspend contrl (RW) */
    ureg32 SUSWP : 1;       /* [ 4: 4] Suspend Write Protection (WO) */
    ureg32 SUSFLAG : 1;     /* [ 5: 5] Suspend flag (RW) */
    ureg32 DBGP : 1;        /* [ 6: 6] Debug pattern (RW) */
    ureg32 reserved_7 : 25; /* [31: 7] Internal reserved */
} DSADC_DEBUG_Bits;

/* Global channel run control register */
typedef struct
{
    ureg32 CH0RUNCTL : 1;    /* [ 0: 0] Channel 0 run control (RW) */
    ureg32 CH1RUNCTL : 1;    /* [ 1: 1] Channel 1 run control (RW) */
    ureg32 CH2RUNCTL : 1;    /* [ 2: 2] Channel 2 run control (RW) */
    ureg32 CH3RUNCTL : 1;    /* [ 3: 3] Channel 3 run control (RW) */
    ureg32 CH4RUNCTL : 1;    /* [ 4: 4] Channel 4 run control (RW) */
    ureg32 CH5RUNCTL : 1;    /* [ 5: 5] Channel 5 run control (RW) */
    ureg32 CH6RUNCTL : 1;    /* [ 6: 6] Channel 6 run control (RW) */
    ureg32 CH7RUNCTL : 1;    /* [ 7: 7] Channel 7 run control (RW) */
    ureg32 CH8RUNCTL : 1;    /* [ 8: 8] Channel 8 run control (RW) */
    ureg32 CH9RUNCTL : 1;    /* [ 9: 9] Channel 9 run control (RW) */
    ureg32 reserved_10 : 6;  /* [15:10] Internal reserved */
    ureg32 M0RUNCTL : 1;     /* [16:16] Modulator 0 run control (RW) */
    ureg32 M1RUNCTL : 1;     /* [17:17] Modulator 1 run control (RW) */
    ureg32 M2RUNCTL : 1;     /* [18:18] Modulator 2 run control (RW) */
    ureg32 M3RUNCTL : 1;     /* [19:19] Modulator 3 run control (RW) */
    ureg32 M4RUNCTL : 1;     /* [20:20] Modulator 4 run control (RW) */
    ureg32 M5RUNCTL : 1;     /* [21:21] Modulator 5 run control (RW) */
    ureg32 M6RUNCTL : 1;     /* [22:22] Modulator 6 run control (RW) */
    ureg32 M7RUNCTL : 1;     /* [23:23] Modulator 7 run control (RW) */
    ureg32 M8RUNCTL : 1;     /* [24:24] Modulator 8 run control (RW) */
    ureg32 M9RUNCTL : 1;     /* [25:25] Modulator 9 run control (RW) */
    ureg32 reserved_26 : 6;  /* [31:26] Internal reserved */
} DSADC_GLOBCRC_Bits;

/* Event state flag register */
typedef struct
{
    ureg32 RESEVF0 : 1;      /* [ 0: 0] Channel 0 result event flag (RW) */
    ureg32 RESEVF1 : 1;      /* [ 1: 1] Channel 1 result event flag (RW) */
    ureg32 RESEVF2 : 1;      /* [ 2: 2] Channel 2 result event flag (RW) */
    ureg32 RESEVF3 : 1;      /* [ 3: 3] Channel 3 result event flag (RW) */
    ureg32 RESEVF4 : 1;      /* [ 4: 4] Channel 4 result event flag (RW) */
    ureg32 RESEVF5 : 1;      /* [ 5: 5] Channel 5 result event flag (RW) */
    ureg32 RESEVF6 : 1;      /* [ 6: 6] Channel 6 result event flag (RW) */
    ureg32 RESEVF7 : 1;      /* [ 7: 7] Channel 7 result event flag (RW) */
    ureg32 RESEVF8 : 1;      /* [ 8: 8] Channel 8 result event flag (RW) */
    ureg32 RESEVF9 : 1;      /* [ 9: 9] Channel 9 result event flag (RW) */
    ureg32 reserved_10 : 6;  /* [15:10] Internal reserved */
    ureg32 ALEVF0 : 1;       /* [16:16] Channel 0 alarm event flag (RW) */
    ureg32 ALEVF1 : 1;       /* [17:17] Channel 1 alarm event flag (RW) */
    ureg32 ALEVF2 : 1;       /* [18:18] Channel 2 alarm event flag (RW) */
    ureg32 ALEVF3 : 1;       /* [19:19] Channel 3 alarm event flag (RW) */
    ureg32 ALEVF4 : 1;       /* [20:20] Channel 4 alarm event flag (RW) */
    ureg32 ALEVF5 : 1;       /* [21:21] Channel 5 alarm event flag (RW) */
    ureg32 ALEVF6 : 1;       /* [22:22] Channel 6 alarm event flag (RW) */
    ureg32 ALEVF7 : 1;       /* [23:23] Channel 7 alarm event flag (RW) */
    ureg32 ALEVF8 : 1;       /* [24:24] Channel 8 alarm event flag (RW) */
    ureg32 ALEVF9 : 1;       /* [25:25] Channel 9 alarm event flag (RW) */
    ureg32 reserved_26 : 6;  /* [31:26] Internal reserved */
} DSADC_GLOBEVSF_Bits;

/* Event state flag clear register */
typedef struct
{
    ureg32 RESECLR0 : 1;     /* [ 0: 0] Channel 0 result event flag clear (RW) */
    ureg32 RESECLR1 : 1;     /* [ 1: 1] Channel 1 result event flag clear (RW) */
    ureg32 RESECLR2 : 1;     /* [ 2: 2] Channel 2 result event flag clear (RW) */
    ureg32 RESECLR3 : 1;     /* [ 3: 3] Channel 3 result event flag clear (RW) */
    ureg32 RESECLR4 : 1;     /* [ 4: 4] Channel 4 result event flag clear (RW) */
    ureg32 RESECLR5 : 1;     /* [ 5: 5] Channel 5 result event flag clear (RW) */
    ureg32 RESECLR6 : 1;     /* [ 6: 6] Channel 6 result event flag clear (RW) */
    ureg32 RESECLR7 : 1;     /* [ 7: 7] Channel 7 result event flag clear (RW) */
    ureg32 RESECLR8 : 1;     /* [ 8: 8] Channel 8 result event flag clear (RW) */
    ureg32 RESECLR9 : 1;     /* [ 9: 9] Channel 9 result event flag clear (RW) */
    ureg32 reserved_10 : 6;  /* [15:10] Internal reserved */
    ureg32 ALECLR0 : 1;      /* [16:16] Channel 0 alarm event flag clear (RW) */
    ureg32 ALECLR1 : 1;      /* [17:17] Channel 1 alarm event flag clear (RW) */
    ureg32 ALECLR2 : 1;      /* [18:18] Channel 2 alarm event flag clear (RW) */
    ureg32 ALECLR3 : 1;      /* [19:19] Channel 3 alarm event flag clear (RW) */
    ureg32 ALECLR4 : 1;      /* [20:20] Channel 4 alarm event flag clear (RW) */
    ureg32 ALECLR5 : 1;      /* [21:21] Channel 5 alarm event flag clear (RW) */
    ureg32 ALECLR6 : 1;      /* [22:22] Channel 6 alarm event flag clear (RW) */
    ureg32 ALECLR7 : 1;      /* [23:23] Channel 7 alarm event flag clear (RW) */
    ureg32 ALECLR8 : 1;      /* [24:24] Channel 8 alarm event flag clear (RW) */
    ureg32 ALECLR9 : 1;      /* [25:25] Channel 9 alarm event flag clear (RW) */
    ureg32 reserved_26 : 6;  /* [31:26] Internal reserved */
} DSADC_GLOBEVSFCLR_Bits;

/* Global synchronization register */
typedef struct
{
    ureg32 MCH0EN : 1;       /* [ 0: 0] Main channel 0 adc enable signal (RW) */
    ureg32 MCH1EN : 1;       /* [ 1: 1] Main channel 1 adc enable signal (RW) */
    ureg32 MCH2EN : 1;       /* [ 2: 2] Main channel 2 adc enable signal (RW) */
    ureg32 MCH3EN : 1;       /* [ 3: 3] Main channel 3 adc enable signal (RW) */
    ureg32 MCH4EN : 1;       /* [ 4: 4] Main channel 4 adc enable signal (RW) */
    ureg32 MCH5EN : 1;       /* [ 5: 5] Main channel 5 adc enable signal (RW) */
    ureg32 MCH6EN : 1;       /* [ 6: 6] Main channel 6 adc enable signal (RW) */
    ureg32 MCH7EN : 1;       /* [ 7: 7] Main channel 7 adc enable signal (RW) */
    ureg32 ACH0EN : 1;       /* [ 8: 8] Auxiliary channel 0 adc enable signal (RW) */
    ureg32 ACH1EN : 1;       /* [ 9: 9] Auxiliary channel 1 adc enable signal (RW) */
    ureg32 ACH2EN : 1;       /* [10:10] Auxiliary channel 2 adc enable signal (RW) */
    ureg32 ACH3EN : 1;       /* [11:11] Auxiliary channel 3 adc enable signal (RW) */
    ureg32 ACH4EN : 1;       /* [12:12] Auxiliary channel 4 adc enable signal (RW) */
    ureg32 ACH5EN : 1;       /* [13:13] Auxiliary channel 5 adc enable signal (RW) */
    ureg32 ACH6EN : 1;       /* [14:14] Auxiliary channel 6 adc enable signal (RW) */
    ureg32 ACH7EN : 1;       /* [15:15] Auxiliary channel 7 adc enable signal (RW) */
    ureg32 MCH8EN : 1;       /* [16:16] Main channel 8 adc enable signal (RW) */
    ureg32 MCH9EN : 1;       /* [17:17] Main channel 9 adc enable signal (RW) */
    ureg32 ACH8EN : 1;       /* [18:18] Auxiliary channel 8 adc enable signal (RW) */
    ureg32 ACH9EN : 1;       /* [19:19] Auxiliary channel 9 adc enable signal (RW) */
    ureg32 SYNCSWITCH : 1;   /* [20:20] Channel synchronization switch (RW) */
    ureg32 INTEREN : 1;      /* [21:21] Integrator enable (RW) */
    ureg32 reserved_22 : 10; /* [31:22] Internal reserved */
} DSADC_GLOBSYNC_Bits;

/**********************************************************************************************************************
 *                                           DSADC Register Union Definitions
 *********************************************************************************************************************/
/* Modulator configuration register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    DSADC_MODCFG_Bits B; /* Bitfield access */
} DSADC_MODCFG;

/* Demodulator input configuration register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    DSADC_DEMICFG_Bits B; /* Bitfield access */
} DSADC_DEMICFG;

/* Common pattern voltage configuration register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    DSADC_CPVCFG_Bits B; /* Bitfield access */
} DSADC_CPVCFG;

/* Result FIFO control register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_RFCON_Bits B; /* Bitfield access */
} DSADC_RFCON;

/* Main conversion result register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_MCRES_Bits B; /* Bitfield access */
} DSADC_MCRES;

/* Time-Stamp register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_TSTMP_Bits B; /* Bitfield access */
} DSADC_TSTMP;

/* Time-Stamp counter */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_TSCNT_Bits B; /* Bitfield access */
} DSADC_TSCNT;

/* Main filter configuration register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_MFCFG_Bits B; /* Bitfield access */
} DSADC_MFCFG;

/* Auxiliary filter configuration register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_AFCFG_Bits B; /* Bitfield access */
} DSADC_AFCFG;

/* Gain offset ctrl register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    DSADC_GAINCTR_Bits B; /* Bitfield access */
} DSADC_GAINCTR;

/* Threshold check limit register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    DSADC_THRESLM_Bits B; /* Bitfield access */
} DSADC_THRESLM;

/* Auxiliary conversion result register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_ACRES_Bits B; /* Bitfield access */
} DSADC_ACRES;

/* Interrupt enable register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_INTEN_Bits B; /* Bitfield access */
} DSADC_INTEN;

/* Interrupt clear register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    DSADC_INTCLR_Bits B; /* Bitfield access */
} DSADC_INTCLR;

/* Interrupt status register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    DSADC_INTSTS_Bits B; /* Bitfield access */
} DSADC_INTSTS;

/* Test configuration register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    DSADC_TESTCFG_Bits B; /* Bitfield access */
} DSADC_TESTCFG;

/* Compensating register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    DSADC_COMP_Bits B; /* Bitfield access */
} DSADC_COMP;

/* Safety mechanism enable */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    DSADC_SMEN_Bits B; /* Bitfield access */
} DSADC_SMEN;

/* Alarm status clear register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    DSADC_ALACLR_Bits B; /* Bitfield access */
} DSADC_ALACLR;

/* Alarm status register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    DSADC_ALASTS_Bits B; /* Bitfield access */
} DSADC_ALASTS;

/* Fault injection register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    DSADC_FAIN_Bits B; /* Bitfield access */
} DSADC_FAIN;

/* DMA timeout threshold */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    DSADC_DMATHRES_Bits B; /* Bitfield access */
} DSADC_DMATHRES;

/* Trigger timeout threshold */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    DSADC_TRIGTHRES_Bits B; /* Bitfield access */
} DSADC_TRIGTHRES;

/* Calibration control register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    DSADC_COMPCON_Bits B; /* Bitfield access */
} DSADC_COMPCON;

/* Test mode */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    DSADC_TESTMODE_Bits B; /* Bitfield access */
} DSADC_TESTMODE;

/* Ditehering enable register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    DSADC_DITHEREN_Bits B; /* Bitfield access */
} DSADC_DITHEREN;

/* Carrier wave configration register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_CWCFG_Bits B; /* Bitfield access */
} DSADC_CWCFG;

/* Carrier wave sync control register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;            /* Unsigned access */
    DSADC_CWSYNC_Bits B; /* Bitfield access */
} DSADC_CWSYNC;

/* Mean control register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    DSADC_INTERCON_Bits B; /* Bitfield access */
} DSADC_INTERCON;

/* Bus error mask register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;               /* Unsigned access */
    DSADC_BUSERRMSK_Bits B; /* Bitfield access */
} DSADC_BUSERRMSK;

/* Suspend public register configure in debug mode */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    DSADC_DEBUG_Bits B; /* Bitfield access */
} DSADC_DEBUG;

/* Global channel run control register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    DSADC_GLOBCRC_Bits B; /* Bitfield access */
} DSADC_GLOBCRC;

/* Event state flag register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    DSADC_GLOBEVSF_Bits B; /* Bitfield access */
} DSADC_GLOBEVSF;

/* Event state flag clear register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;                 /* Unsigned access */
    DSADC_GLOBEVSFCLR_Bits B; /* Bitfield access */
} DSADC_GLOBEVSFCLR;

/* Global synchronization register */
typedef union
/* #Violation: dsadc_register_h_REF_1 */
{
    ureg32 U;              /* Unsigned access */
    DSADC_GLOBSYNC_Bits B; /* Bitfield access */
} DSADC_GLOBSYNC;

/**********************************************************************************************************************
 *                                                DSADC Register Configuration Structure
 *********************************************************************************************************************/
/* DSADC module register structure */
/* #Violation: dsadc_register_h_REF_2 */
typedef volatile struct
{
    DSADC_MODCFG MODCFG;       /*  0, Modulator configuration register */
    DSADC_DEMICFG DEMICFG;     /*  4, Demodulator input configuration register */
    DSADC_CPVCFG CPVCFG;       /*  8, Common pattern voltage configuration register */
    ureg32 reserved_0C;        /*  C, Internal reserved */
    DSADC_RFCON RFCON;         /* 10, Result FIFO control register */
    DSADC_MCRES MCRES;         /* 14, Main conversion result register */
    DSADC_TSTMP TSTMP;         /* 18, Time-Stamp register */
    DSADC_TSCNT TSCNT;         /* 1C, Time-Stamp counter */
    DSADC_MFCFG MFCFG;         /* 20, Main filter configuration register */
    DSADC_AFCFG AFCFG;         /* 24, Auxiliary filter configuration register */
    DSADC_GAINCTR GAINCTR;     /* 28, Gain offset ctrl register */
    DSADC_THRESLM THRESLM;     /* 2C, Threshold check limit register */
    DSADC_ACRES ACRES;         /* 30, Auxiliary conversion result register */
    DSADC_INTEN INTEN;         /* 34, Interrupt enable register */
    DSADC_INTCLR INTCLR;       /* 38, Interrupt clear register */
    DSADC_INTSTS INTSTS;       /* 3C, Interrupt status register */
    DSADC_TESTCFG TESTCFG;     /* 40, Test configuration register */
    DSADC_COMP COMP;           /* 44, Compensating register */
    DSADC_SMEN SMEN;           /* 48, Safety mechanism enable */
    DSADC_ALACLR ALACLR;       /* 4C, Alarm status clear register */
    DSADC_ALASTS ALASTS;       /* 50, Alarm status register */
    DSADC_FAIN FAIN;           /* 54, Fault injection register */
    DSADC_DMATHRES DMATHRES;   /* 58, DMA timeout threshold */
    DSADC_TRIGTHRES TRIGTHRES; /* 5C, Trigger timeout threshold */
    DSADC_COMPCON COMPCON;     /* 60, Calibration control register */
    DSADC_TESTMODE TESTMODE;   /* 64, Test mode */
    DSADC_DITHEREN DITHEREN;   /* 68, Ditehering enable register */
    DSADC_CWCFG CWCFG;         /* 6C, Carrier wave configration register */
    DSADC_CWSYNC CWSYNC;       /* 70, Carrier wave sync control register */
    DSADC_INTERCON INTERCON;     /* 74, Mean control register */
    DSADC_BUSERRMSK BUSERRMSK; /* 78, Bus error mask register */
} DSADC_MODULE;

/* DSADC common register structure */
/* #Violation: dsadc_register_h_REF_2 */
typedef volatile struct
{
    DSADC_DEBUG     DEBUG;         /*  0, Suspend public register configure in debug mode */
    DSADC_GLOBCRC GLOBCRC;         /*  4, Global channel run control register */
    DSADC_GLOBEVSF GLOBEVSF;       /*  8, Event state flag register */
    DSADC_GLOBEVSFCLR GLOBEVSFCLR; /*  C, Event state flag clear register */
    DSADC_GLOBSYNC GLOBSYNC;       /*  10, Global synchronization register */
} DSADC_COMMON;

/**********************************************************************************************************************
 *                                                  DSADC Module Object
 *********************************************************************************************************************/

#endif /* DSADC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

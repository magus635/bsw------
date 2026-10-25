/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    espi_register.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: ESPI module register definition header file.This file defines the register offsets and bit definitions
 *              for the ESPI module.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#espi_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:Using unions for bit-field access to registers
*/
#ifndef ESPI_REGISTER_H_
#define ESPI_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        ESPI Register Bit-Fields Definitions
 *********************************************************************************************************************/
/*Port Input Select Switch Register */
typedef struct
{
    ureg32 SMISS:3;       /* [2:0]  Slave Mode Input Selection Switch SMISS-(RW) */
    ureg32 reserved_3:29; /* [31:3] Internal reserved */
} ESPI_SISW_Bits;

/* Module Identification Register */
typedef struct
{
    ureg32 MDRV:8;  /* [7:0]   Module Revision Number - MDRV (RW) */
    ureg32 MDTP:8;  /* [15:8]  Module Type - MDTP (R) */
    ureg32 MDNB:16; /* [31:16] Module Number Value - MDNB (R) */
} ESPI_MDID_Bits;

/* Global Configuration Register */
typedef struct
{
    ureg32 GTQ:8;           /* [7:0] Global Time Quantum Length - GTQ (RW) */
    ureg32 SFRBEM:1;        /* [8:8] SFR Bus Error Mask - SFRBEM (RW) */
    ureg32 STSI:1;          /* [9:9] STS Injection - STSI (RW) */
    ureg32 TOV:4;           /* [13:10] Time-Out Value for the Expect Phase - TOV (RW) */
    ureg32 OLBC:1;          /* [14:14] Loop-Back Control - OLBC (RW) */
    ureg32 DLMS:1;          /* [15:15] Delayed Mode for SLSO0 - DLMS (RW) */
    ureg32 STBDL:5;         /* [20:16] Strobe Delay for SLSO0 in Delayed Mode - STBDL (RW) */
    ureg32 TPRF:1;          /* [21:21] Stop on RxFIFO Full - TPRF (RW) */
    ureg32 SODP:1;          /* [22:22] Slave Transmit Idle State Polarity - SODP (RW) */
    ureg32 HDTRM:1;         /* [23:23] Half-Duplex Transmit Receive Mode HDTRM(RW) */
    ureg32 EN:1;            /* [24:24] Enable Bit - EN (RW) */
    ureg32 MS:2;            /* [26:25] Master Slave Mode - MS (RW) */
    ureg32 SATREN:1;        /* [27:27] Automatic Reset Enable - SATREN (RW) */
    ureg32 HDMEN:1;         /* [28:28] Half-Duplex Mode Enable - HDMEN(RW) */
    ureg32 CLKMUX:1;        /* [29:29] Clock Select - CLKMUX (RW) */
    ureg32 SRSTB:2;         /* [31:30] Bits for resetting sub-modules per software - SRSTB (RW) */
} ESPI_GNRCON_Bits;

/* Global Configuration Register 1 */
typedef struct
{
    ureg32 ERRIENS:9;     /* [8:0] Error Enable Bits - ERRORENS (RW) */
    ureg32 TXFIEN:1;      /* [9:9] Tx Interrupt Event Enable - TXEN (RW) */
    ureg32 RXFIEN:1;      /* [10:10] RX Interrupt Event Enable - RXEN (RW) */
    ureg32 TSE1EN:1;      /* [11:11] Interrupt on PT1 Event Enable - PT1EN (RW) */
    ureg32 TSE2EN:1;      /* [12:12] Interrupt on PT2 Event Enable - PT2EN (RW) */
    ureg32 DAIGEN:1;      /* [13:13] Data ignore enable - DAIGEN (RW) */
    ureg32 SEFEN:1;       /* [14:14] Slave end flag enable - SEFEN (RW) */
    ureg32 UEIEN:1;       /* [15:15] Interrupt on USR Event Enable - UEIEN (RW) */
    ureg32 LTEIEN:1;      /* [16:16] Interrupt on Large Transmission End Event Enable (RW) */
    ureg32 reserved_17:3; /* [19:17] Internal reserved */
    ureg32 TSE1:3;        /* [22:20] Phase Transition Event 1 - PT1 (RW) */
    ureg32 TSE2:3;        /* [25:23] Phase Transition Event 2 - PT2 (RW) */
    ureg32 TXFM:2;        /* [27:26] TXFIFO Mode - TXFM (RW) */
    ureg32 RXFM:2;        /* [29:28] RXFIFO Mode - RXFM (RW) */
    ureg32 TXDREN:1;      /* [30:30] TxDMA Enable -TXDREN(RW)*/
    ureg32 RXDREN:1;      /* [31:31] RxDMA Enable -RXDREN(RW) */
} ESPI_GNRCON1_Bits;

/* Elementary Configuration Register */
typedef struct
{
    ureg32 LDB:1;    /* [0:0] Last data block in a frame - LDB (RW) */
    ureg32 IPSC:3;   /* [3:1] Prescaler for the Idle delay - IPSC (RW) */
    ureg32 IDL:3;    /* [6:4] Idle delay length - IDL (RW) */
    ureg32 LPSC:3;   /* [9:7] Prescaler for the leading delay - LPSC (RW) */
    ureg32 LDL:3;    /* [12:10] Leading delay length - LDL (RW) */
    ureg32 TPSC:3;   /* [15:13] Prescaler for the trailing delay - TPRE (RW) */
    ureg32 TDL:3;    /* [18:16] Trailing delay length - TDL (RW) */
    ureg32 PARTYP:1; /* [19:19] Parity type - PARTYP (RW) */
    ureg32 UIOT1:1;  /* [20:20] User interrupt at the PT1 event in the subsequent frames - UIOT1 (RW) */
    ureg32 MSB:1;    /* [21:21] Shift MSB or LSB first - MSB (RW) */
    ureg32 DLU:1;    /* [22:22] Data length unit - DLU(RW) */
    ureg32 DL:5;     /* [27:23] Data length - DL (RW) */
    ureg32 SCM:4;    /* [31:28] Slave selection channel mux - SCM (RW) */
} ESPI_EMCON_Bits;

/* Development Configuration Register */
typedef struct
{
    ureg32 TQ:6;           /* [5:0] Time quantum for Tk -  TQ (RW) */
    ureg32 CSA:2;          /* [7:6] Clock cycle segment 1 - CSA (RW) */
    ureg32 CSB:2;          /* [9:8] Clock cycle segment 2 - CSB (RW) */
    ureg32 CSC:2;          /* [11:10] Clock cycle segment 3 - CSC (RW) */
    ureg32 CPH:1;          /* [12:12] Clock phase - CPH (RW) */
    ureg32 CPOL:1;         /* [13:13] Clock polarity - CPOL (RW) */
    ureg32 PRTEN:1;        /* [14:14] Enable parity check - PRTEN (RW) */
    ureg32 reserved_15:15; /* [29:15] Internal reserved */
    ureg32 DFBEN:2;        /* [31:30] Data format change to / from big-endian - DFBEN (RW) */
} ESPI_DCON_Bits;

/* Status Register */
typedef struct
{
    ureg32 ERRIFS:9;      /* [8:0] Interrupt on errors event flags - ERRIFS (RW) */
    ureg32 TXF:1;         /* [9:9] Transmit interrupt request flag - TXF (RW) */
    ureg32 RXF:1;         /* [10:10] Receive interrupt request flag - RXF (RW) */
    ureg32 TSE1F:1;       /* [11:11] Transition stage event1 flag - TSE1F (RW) */
    ureg32 TSE2F:1;       /* [12:12] Transition stage event2 flag - TSE2F (RW) */
    ureg32 DAIG:1;        /* [13:13] Data ignore error Flag  - DAIG(RW) */
    ureg32 SEF:1;         /* [14:14] Slave end flag -SEF */
    ureg32 USRF:1;        /* [15:15] User interrupt request flag - USRF (RW) */
    ureg32 SFRAF:1;       /* [16:16] Special function register alarm flag - SFRAF(RW) */
    ureg32 STOAF:1;       /* [17:17] Slave timeout alarm flag - STOAF(RW) */
    ureg32 SEAF:1;        /* [18:18] SE protection alarm flag - SEAF (RW) */
    ureg32 LTEF:1;        /* [19:19] Large Transmission End Flag - LTEF (RO) */
    ureg32 reserved_20:2; /* [21:20] Internal reserved */
    ureg32 CSF:4;         /* [25:22] Currently communication slave select flag -CSF(RW) */
    ureg32 RPV:1;         /* [26:26] Received parity value - RPV (RW) */
    ureg32 TPV:1;         /* [27:27] Transmitted parity value - TPV (RW) */
    ureg32 FS:4;          /* [31:28] Flags the ongoing phase - FS (RW) */
} ESPI_STS_Bits;

/* Extend Status Register */
typedef struct
{
    ureg32 TBCNT:8;       /* [7:0] Bits counter of a transmission  - TBCNT (R) */
    ureg32 reserved_8:20; /* [27:8] Internal reserved */
    ureg32 CBDEN:1;       /* [28:28] Clock baud rate deviation detection enable - CBDEN (RW) */
    ureg32 CBDF:1;        /* [29:29] Clock baud rate deviation error flag - CBDF (RW) */
    ureg32 CSDEN:1;       /* [30:30] Clock spike detection enable - CSDEN (RW) */
    ureg32 CSEF:1;        /* [31:31] Clock spike error flag - CSF (RW) */
} ESPI_ESTS_Bits;

/* Slave Select Output Control Register */
typedef struct
{
    ureg32 OAP:16; /* [15:0]  Active polarity for the SLSO outputs - OAP (RW) */
    ureg32 OEB:16; /* [31:16] Enable bits for the SLSO outputs - OEB (RW) */
} ESPI_SSCON_Bits;

/* Flags Clear Register */
typedef struct
{
    ureg32 ERRFSC:9;       /*[8:0] Errors event flags clearing with only bits writing - ERRFSC (WO) */
    ureg32 TXC:1;          /*[9:9] Transmit event flag clear - TXC (WO) */
    ureg32 RXC:1;          /*[10:10] Receive event flag clear - RXC (WO) */
    ureg32 TSE1FC:1;       /*[11:11] Transition stage event 1 flag clear - TSE1FC (WO) */
    ureg32 TSE2FC:1;       /*[12:12] Transition stage event 2 flag clear - TSE2FC (WO) */
    ureg32 DAIGC:1;        /*[13:13] Data ignore flag clear - DAIGC (WO) */
    ureg32 SEFC:1;         /*[14:14] Slave end flag clear - SEFC (WO) */
    ureg32 USRC:1;         /*[15:15] User event flag clear - USRC (WO)  */
    ureg32 SFRAC:1;        /*[16:16] Special function register alarm flag clear - SFRAC (WO) */
    ureg32 STOAC:1;        /*[17:17] Slave timeout alarm flag clear - STOAC (WO) */
    ureg32 SEAC:1;         /*[18:18] SE protection alarm flag clear - SEAC (WO) */
    ureg32 LTEFC:1;        /*[19:19] Large Transmission End Flag Clear - LTEFC (WO) */
    ureg32 reserved_20:12; /*[31:20] Internal reserved */
} ESPI_STSC_Bits;

/* Large Transmission Configuration Register */
typedef struct
{
    ureg32 DLT:16;  /* [15:0] Data length of large transmission - DLT (RW) */
    ureg32 DCNT:16; /* [31:16] Data counter for large transmission - DCNT(RO) */
} ESPI_LTCON_Bits;

/* HYBRID ENTRY Register */
typedef struct
{
    ureg32 HBE:32; /* [31:0] Hybric entry for writing EMCON or DATA to the TxFIFO - HBE (WO) */
} ESPI_HBRENTRY_Bits;

/* EMCON ENTRY Register */
typedef struct
{
    ureg32 ESE:32; /* [31:0] Specialized entry for writing EMCON to the TxFIFO - ESE (WO) */
} ESPI_EMCONENTRY_Bits;

/* DATA ENTRY Register */
typedef struct
{
    ureg32 DSE:32; /*[31:0] Specialized entry for writing DATA to the TxFIFO - DSE (WO) */
} ESPI_DATAENTRY_Bits;

/* RX Read Data Register */
typedef struct
{
    ureg32 RSE:32; /*[31:0] Specialized entry for reading rx data from the RxFIFO - RSE (RO) */
} ESPI_RDR_Bits;

/* Move Counter Register */
typedef struct
{
    ureg32 TOMS:13;       /* [12:0] Target of move step - TOMS (RW) */
    ureg32 reserved_13:3; /* [15:13] Internal reserved */
    ureg32 RMN:13;        /* [28:16] Remaining move number - RMN (RO) */
    ureg32 reserved_29:3; /* [31:29] Internal reserved */
} ESPI_MC_Bits;

/*Move Counter control Register */
typedef struct
{
    ureg32 ETPSC:3;       /* [2:0] Prescaler for the extended trailing delay - ETPSC (RW) */
    ureg32 ETDL:3;        /* [5:3] Extended trailing delay length - ETDL (RW) */
    ureg32 reserved_6:10; /* [15:6] Internal reserved */
    ureg32 BFIEN:1;       /* [16:16] Enable BFIF interrupt - BFIEN (RW) */
    ureg32 BFIF:1;        /* [17:17] BFIF interrupt flag - BFIF(RW) */
    ureg32 BFIC:1;        /* [18:18] Clear bit for BFIF - BFIC (W1C) */
    ureg32 BFIS:1;        /* [19:19] Set bit for BFIF - BFIS(RW)   */
    ureg32 AFIEN:1;       /* [20:20] Enable AFIF interrupt - AFIEN (RW) */
    ureg32 AFIF:1;        /* [21:21] AFIF interrupt flag - AFIF(RW) */
    ureg32 AFIC:1;        /* [22:22] Clear bit for AFIF - AFIC(RW) */
    ureg32 AFIS:1;        /* [23:23] Set bit for AFIF(RW) */
    ureg32 reserved_24:6; /* [29:24] Internal reserved */
    ureg32 ETEN:1;        /* [30:30] Extended trailing delay enable - ETEN (RW) */
    ureg32 MCEN:1;        /* [31:31] Move counter enable - MCEN (RW) */
} ESPI_MCCON_Bits;

/* Delay configuration register*/
typedef struct
{
    ureg32 DELAYTIME:6;    /* [5:0] Delay time configuration -DELAYTIME (RW)*/
    ureg32 reserved_19:26; /* [31:6] Internal reserved */
} ESPI_DELAY_Bits;

/* Data mode selection register*/
typedef struct
{
    ureg32 SLAVEDATACNT:17; /* [16:0]  Slave data output delay count - RW */
    ureg32 DATASEL:2;      /* [18:17] Data output select - RW */
    ureg32 reserved_19:13; /* [31:19] Internal reserved */
} ESPI_DATAMODE_Bits;

/* Rx data read Debug Register */
typedef struct
{
    ureg32 RSE:32; /* [31:0] Specialized entry for reading rx data from the RxFIFO in debug mode - RSE (RO) */
} ESPI_RDRD_Bits;

/* FIFO threshold configuration register*/
typedef struct
{
    ureg32 TXTHRESHOLD:4; /* [3:0] Transmit FIFO interrupt threshold - TXTHRESHOLD (RW) */
    ureg32 RXTHRESHOLD:4; /* [7:4] Receive FIFO interrupt threshold - RXTHRESHOLD (RW) */
    ureg32 STORT:18;      /* [25:8] Slave timeout recovery time - STORT (RW) */
    ureg32 STOEN:1;       /* [26:26] Slave timeout enable - STOEN (RW) */
    ureg32 reserved_27:5; /* [31:27] Internal reserved */
} ESPI_FIFOTHRESHOLD_Bits;

/* FIFO level register*/
typedef struct
{
    ureg32 TXLEVEL:5;      /* [4:0] TXFIFO filling level - TXLEVEL(RW)*/
    ureg32 reserved_5:3;   /* [7:5] Internal reserved */
    ureg32 RXLEVEL:5;      /* [12:8] RXFIFO filling level - RXLEVEL(RW)*/
    ureg32 reserved_13:19; /* [31:13] Internal reserved */
} ESPI_FIFOLEVEL_Bits;

/* Development configuration extended group register */
typedef struct
{
    ureg32 TQ:6;            /* [5:0] Time quantum */
    ureg32 CSA:2;           /* [7:6] Clock cycle segment A */
    ureg32 CSB:2;           /* [9:8] Clock cycle segment B */
    ureg32 CSC:2;           /* [11:10] Clock cycle segment C */
    ureg32 CPH:1;           /* [12:12] Clock phase */
    ureg32 CPOL:1;          /* [13:13] Clock polarity */
    ureg32 PRTEN:1;         /* [14:14] Enable parity check */
    ureg32 reserved_15:15;  /* [29:15] Reserved */
    ureg32 DFBEN:2;         /* [31:30] Data format for big endian */
} ESPI_DCONEG_Bits;
/**********************************************************************************************************************
 *                                          ESPI Register Union Definitions
 *********************************************************************************************************************/
/* Basic Configuration Register */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    ESPI_EMCON_Bits B; /* Bit-field access */
} ESPI_EMCON;

/* EMCON_ENTRY Register */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    ESPI_EMCONENTRY_Bits B; /* Bit-field access */
} ESPI_EMCONENTRY;

/* DATA_ENTRY Register*/
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    ESPI_DATAENTRY_Bits B; /* Bit-field access */
} ESPI_DATAENTRY;

/* Configuration Extension */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    ESPI_DCON_Bits B; /* Bit-field access */
} ESPI_DCON;

/* Flags Clear Register */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    ESPI_STSC_Bits B; /* Bit-field access */
} ESPI_STSC;

/*Global Configuration Register */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ESPI_GNRCON_Bits B; /* Bit-field access */
} ESPI_GNRCON;

/* Global Configuration Register 1*/
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    ESPI_GNRCON1_Bits B; /* Bit-field access */
} ESPI_GNRCON1;

/* Module Identification Register*/
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    ESPI_MDID_Bits B; /* Bit-field access */
} ESPI_MDID;

/* Move Counter Register */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    ESPI_MC_Bits B; /* Bit-field access */
} ESPI_MC;

/* Move Counter control Register */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    ESPI_MCCON_Bits B; /* Bit-field access */
} ESPI_MCCON;

/* ESPI_HBRENTRY Register */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    ESPI_HBRENTRY_Bits B; /* Bit-field access */
} ESPI_HBRENTRY;

/* Port Input Select Register*/
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    ESPI_SISW_Bits B; /* Bit-field access */
} ESPI_SISW;

/* RX_EXIT Register   */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    ESPI_RDR_Bits B; /*Bit-field access */
} ESPI_RDR;

/* RX_EXIT Debug Register  */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    ESPI_RDRD_Bits B; /* Bit-field access */
} ESPI_RDRD;

/* Slave Select Output Control Register   */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    ESPI_SSCON_Bits B; /* Bit-field access */
} ESPI_SSCON;

/* STS Register */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    ESPI_STS_Bits B; /* Bit-field access */
} ESPI_STS;

/*STS Register 1  */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    ESPI_ESTS_Bits B; /* Bit-field access */
} ESPI_ESTS;

/*Extra Large Data Configuration Register   */
typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    ESPI_LTCON_Bits B; /* Bit-field access */
} ESPI_LTCON;

typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    ESPI_DELAY_Bits B; /* Bit-field access */
} ESPI_DELAY;

typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    ESPI_DATAMODE_Bits B; /* Bit-field access */
} ESPI_DATAMODE;

typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    ESPI_FIFOTHRESHOLD_Bits B; /* Bit-field access */
} ESPI_FIFOTHRESHOLD;

typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    ESPI_FIFOLEVEL_Bits B; /* Bit-field access */
} ESPI_FIFOLEVEL;

typedef union
/* #Violation: espi_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    ESPI_DCONEG_Bits B;  /* Bit-field access */
} ESPI_DCONEG;
/**********************************************************************************************************************
 *                                               ESPI Register Structure
 *********************************************************************************************************************/
typedef volatile struct
{
    uint8 RESERVED_0[4];              /* 0x0 internal Reserved */
    ESPI_SISW SISW;                   /* 0x4  Port Input Select Switch Register*/
    ESPI_MDID MDID;                   /* 0x8 Module Identification Register*/
    uint8 RESERVED_C[4];              /* 0xC internal Reserved */
    ESPI_GNRCON GNRCON;               /* 0x10 Global Configuration Register*/
    ESPI_GNRCON1 GNRCON1;             /* 0x14 Global Configuration Register 1*/
    ESPI_EMCON EMCON;                 /* 0x18 Basic Configuration Register*/
    uint8 RESERVED_1C[4];             /* 0x1C internal Reserved */
    ESPI_DCON DCON[8];                /* 0x20 Configuration Extension*/
    ESPI_STS STS;                     /* 0x40 STS Register*/
    ESPI_ESTS ESTS;                   /* 0x44 STS Register 1*/
    ESPI_SSCON SSCON;                 /* 0x48 Slave Select Output Control Register*/
    uint8 RESERVED_4C[8];             /* 0x4C internal Reserved */
    ESPI_STSC STSC;                   /* 0x54 Flags Clear Register*/
    ESPI_LTCON LTCON;                 /* 0x58 Extra Large Data Configuration Register*/
    ESPI_HBRENTRY HBRENTRY;           /* 0x5C MIX_ENTRY Register*/
    ESPI_EMCONENTRY EMCONENTRY;       /* 0x60 EMCON_ENTRY Register*/
    ESPI_DATAENTRY DATAENTRY[8];      /* 0x64 DATA_ENTRY Register */
    uint8 RESERVED_84[12];            /* 0x84 internal Reserved */
    ESPI_RDR RDR;                     /* 0x90 RX_EXIT Register*/
    ESPI_RDR RDR1;                    /* 0x94 RX_EXIT1 Register*/
    ESPI_RDR RDR2;                    /* 0x98 RX_EXIT2 Register*/
    ESPI_RDR RDR3;                    /* 0x9C RX_EXIT3 Register*/
    uint8 RESERVED_A0[4];             /* 0xA0 internal Reserved */
    ESPI_MC MC;                       /* 0xA4 Move Counter Register*/
    ESPI_MCCON MCCON;                 /* 0xA8 Move Counter control Register*/
    ESPI_DELAY DELAY;                 /* 0xAC Delay Register*/
    ESPI_DATAMODE DATAMODE;           /* 0xB0 DATAMODE Register*/
    ESPI_RDRD RDRD;                   /* 0xB4 RX_EXIT Debug Register */
    ESPI_FIFOTHRESHOLD FIFOTHRESHOLD; /* 0xB8 FIFO Threshold Register */
    ESPI_FIFOLEVEL FIFOLEVEL;         /* 0xBC FIFO Level Resister */
    ESPI_DCONEG DCONEG[8];            /* 0xC0 Configuration Extension- Extended Group*/
} ESPI_MODULE;

#endif /* ESPI_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

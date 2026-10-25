/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    can_register.h
 * Author:      00101
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of CAN module registers.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #can_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by
*               code review.
*
* #can_register_h_REF_2:MISRAC2012-Rule-2.3;
* Justification: Reserved types are defined in AUTOSAR specifications.
*
* #can_register_h_REF_3:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
* #can_register_h_REF_4:CERTC-DCL12-C;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*/

#ifndef CAN_REGISTER_H_
#define CAN_REGISTER_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        CAN Register Bit-Fields Definitions
 *********************************************************************************************************************/
/*  Core release register  */
typedef struct
{
    ureg32 DAY:8;     /* [7:0] Time stamp Day - RO */
    ureg32 MON:8;     /* [15:8] Time stamp month - RO*/
    ureg32 YEAR:4;    /* [19:16] Time stamp year - RO */
    ureg32 SUBSTEP:4; /* [23:20] Sub-step of core release - RO */
    ureg32 STEP:4;    /* [27:24] Step of core release - RO */
    ureg32 REL:4;     /* [31:28] Core release - RO */
} CAN_CREL_Bits;

/*  Endianness test value register  */
typedef struct
{
    ureg32 ETV:32; /* [31:0] Endianness test value - RO */
} CAN_ENDN_Bits;

/*  Data bit timing & prescaler register */
typedef struct
{
    ureg32 DSJW:4;        /* [3:0] Data (Re) Synchronization jump width - RW */
    ureg32 DTSEG2:4;      /* [7:4] Data time segment after sample point - RW */
    ureg32 DTSEG1:5;      /* [12:8] Data time segment before sample point - RW */
    ureg32 reserved_13:3; /* [15:13] Internal reserved */
    ureg32 DBRP:5;        /* [20:16] Data baud rate prescaler - RW */
    ureg32 reserved_21:2; /* [22:21] Internal reserved */
    ureg32 TDC:1;         /* [23:23] Transmitter delay compensation - RW */
    ureg32 reserved_24:8; /* [31:24] Internal reserved */
} CAN_DBTP_Bits;

/*  Test register */
typedef struct
{
    ureg32 reserved_3:4;  /* [3:0] Internal reserved */
    ureg32 LBCK:1;        /* [4:4] Loop back mode - RW */
    ureg32 TX:2;          /* [6:5] Control of transmit pin - RW */
    ureg32 RX:1;          /* [7:7] Receive pin - RO */
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
} CAN_TEST_Bits;

/*  RAM watchdog  */
typedef struct
{
    ureg32 WDC:8;          /* [7:0] Watchdog configuration - RW */
    ureg32 WDV:8;          /* [15:8] Watchdog value - RO */
    ureg32 reserved_16:16; /* [31:16]  Internal reserved */
} CAN_RWD_Bits;

/*  CC Control register */
typedef struct
{
    ureg32 INIT:1;         /* [0:0] Initialization - RW */
    ureg32 CCE:1;          /* [1:1] Configuration change enable - RW */
    ureg32 ROM:1;          /* [3:3] Restricted Operation Mode - RO */
    ureg32 CSA:1;          /* [3:3] Clock stop acknowledge - RO */
    ureg32 CSR:1;          /* [4:4] Clock stop request - RW*/
    ureg32 MON:1;          /* [5:5] Bus monitoring mode - RW */
    ureg32 DAR:1;          /* [6:6] Disable automatic retransmission - RW */
    ureg32 TEST:1;         /* [7:7] Test mode enable - RW */
    ureg32 FDOE:1;         /* [8:8] FD operation enable - RW */
    ureg32 BRSE:1;         /* [9:9] Bit rate switch enable - RW */
    ureg32 reserved_10:1;  /* [10:10] Internal reserved */
    ureg32 WMM:1;          /* [11:11] Wide Message Marker */
    ureg32 PXHD:1;         /* [12:12] Protocol exception handling disable - RW */
    ureg32 EFBI:1;         /* [13:13] Edge filtering during bus integration - RW */
    ureg32 TXP:1;          /* [14:14] Transmit pause - RW */
    ureg32 NISO:1;         /* [15:15] Non ISO operation - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} CAN_CCCR_Bits;

/*  Nominal bit timing & prescaler register */
typedef struct
{
    ureg32 NTSEG2:7;     /* [6:0] Nominal time segment after sample point - RW */
    ureg32 reserved_7:1; /* [7:7] Internal reserved */
    ureg32 NTSEG1:8;     /* [15:8] Nominal time segment before sample point - RW */
    ureg32 NBRP:9;       /* [24:16] Baud rate prescaler - RW */
    ureg32 NSJW:7;       /* [31:25] (Re)Synchronization jump width - RW */
} CAN_NBTP_Bits;

/*  Timeout counter configuration */
typedef struct
{
    ureg32 ETOC:1;        /* [0:0] Enable timeout counter - RW */
    ureg32 TOS:2;         /* [2:1] Timeout select - RW */
    ureg32 reserved_3:13; /* [15:3] Internal reserved */
    ureg32 TOP:16;        /* [31:16] Timeout period - RW */
} CAN_TOCC_Bits;

/*  Timeout counter value */
typedef struct
{
    ureg32 TOC:16;         /* [15:0] Timeout counter - RW */
    ureg32 reserved_16:16; /* [31:16]  Internal reserved */
} CAN_TOCV_Bits;

/*  Timestamp counter configuration  */
typedef struct
{
    ureg32 TSS:2;          /* [1:0] Time segment before sample point -RW */
    ureg32 reserved_2:14;  /* [15:2] Internal reserved */
    ureg32 TCP:4;          /* [19:16] Time stamp counter prescaler - RW */
    ureg32 reserved_20:12; /* [31:20] Internal reserved */
} CAN_TSCC_Bits;

/*  Timestamp counter value */
typedef struct
{
    ureg32 TSC:16;         /* [15:0] Time stamp counter - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} CAN_TSCV_Bits;

/*  Error counter register  */
typedef struct
{
    ureg32 TEC:8;         /* [7:0] Transmit error counter - RO */
    ureg32 REC:7;         /* [14:8] Receive error counter - RO */
    ureg32 RP:1;          /* [15:15] Receive error passive - RO */
    ureg32 CEL:8;         /* [23:16] CAN error logging - RO */
    ureg32 reserved_24:8; /* [31:24] Internal reserved */
} CAN_ECR_Bits;

/*  Protocol status register  */
typedef struct
{
    ureg32 LEC:3;         /* [2:0] Last error code - RO */
    ureg32 ACT:2;         /* [4:3] Activity - RO*/
    ureg32 EP:1;          /* [5:5] Error passive - RO */
    ureg32 EW:1;          /* [6:6] Warning status - RO */
    ureg32 BO:1;          /* [7:7] Bus off status - RO */
    ureg32 DLEC:3;        /* [10:8] Data phase last error code - RO */
    ureg32 RESI:1;        /* [11:11] ESI flag of last received CAN FD message - RO */
    ureg32 RBRS:1;        /* [12:12] BRS flag of last received CAN FD message - RO */
    ureg32 RFDF:1;        /* [13:13] Received a CAN FD message - RO */
    ureg32 PXE:1;         /* [14:14] Protocol exception event - RO */
    ureg32 reserved_15:1; /* [15:15] Internal reserved */
    ureg32 TDCV:7;        /* [22:16] Transmitter delay compensation value - RO */
    ureg32 reserved_23:9; /* [31:23] Internal reserved */
} CAN_PSR_Bits;

/*  Transmitter delay compensation register */
typedef struct
{
    ureg32 TDCF:7;         /* [6:0] Transmitter delay compensation filter window length - RW */
    ureg32 reserved_7:1;   /* [7:7]  Internal reserved */
    ureg32 TDCO:7;         /* [14:8] Transmitter delay compensation offset - RW */
    ureg32 reserved_15:17; /* [31:15]  Internal reserved */
} CAN_TDCR_Bits;

/*  Interrupt register */
typedef struct
{
    ureg32 RF0N:1;        /* [0:0] Rx FIFO 0 new message - RW */
    ureg32 RF0W:1;        /* [1:1] Rx FIFO 0 watermark reached - RW */
    ureg32 RF0F:1;        /* [2:2] Rx FIFO 0 full - RW */
    ureg32 RF0L:1;        /* [3:3] Rx FIFO 0 message lost - RW */
    ureg32 RF1N:1;        /* [4:4] Rx FIFO 1 new message - RW */
    ureg32 RF1W:1;        /* [5:5] Rx FIFO 1 watermark reached - RW */
    ureg32 RF1F:1;        /* [6:6] Rx FIFO 1 full - RW */
    ureg32 RF1L:1;        /* [7:7] Rx FIFO 1 message lost - RW */
    ureg32 HPM:1;         /* [8:8] High priority message - RW */
    ureg32 TC:1;          /* [9:9] Transmission completed - RW */
    ureg32 TCF:1;         /* [10:10] Transmission cancellation finished - RW */
    ureg32 TFE:1;         /* [11:11] Tx FIFO empty - RW */
    ureg32 TEFN:1;        /* [12:12] Tx event FIFO new entry - RW */
    ureg32 TEFW:1;        /* [13:13] Tx event FIFO watermark reached - RW */
    ureg32 TEFF:1;        /* [14:14] Tx event FIFO full - RW */
    ureg32 TEFL:1;        /* [15:15] Tx event FIFO element lost - RW */
    ureg32 TSW:1;         /* [16:16] Timestamp wraparound - RW */
    ureg32 MRAF:1;        /* [17:17] Message RAM access failure - RW */
    ureg32 TOO:1;         /* [18:18] Timeout occurred - RW */
    ureg32 DRX:1;         /* [19:19] Message stored to dedicated Rx buffer - RW */
    ureg32 BEC:1;         /* [20:20]  Bit error uncorrected - RW */
    ureg32 BEU:1;         /* [21:21]  Bit error corrected - RW)  */
    ureg32 ELO:1;         /* [22:22] Error logging overflow - RW */
    ureg32 EP:1;          /* [23:23] Error passive - RW */
    ureg32 EW:1;          /* [24:24] Warning status - RW */
    ureg32 BO:1;          /* [25:25] Buso ff status - RW */
    ureg32 WDI:1;         /* [26:26] Watchdog interrupt - RW */
    ureg32 PEA:1;         /* [27:27] Protocol error in arbitration phase - RW */
    ureg32 PED:1;         /* [28:28] Protocol error in data phase - RW */
    ureg32 ARA:1;         /* [29:29] Access to reserved address - RW) */
    ureg32 reserved_30:2; /* [31:30]  Internal reserved */
} CAN_IR_Bits;

/*  Interrupt enable  */
typedef struct
{
    ureg32 RF0NE:1;       /* [0:0] Rx FIFO 0 new message interrupt enable - RW */
    ureg32 RF0WE:1;       /* [1:1] Rx FIFO 0 watermark reached interrupt enable - RW*/
    ureg32 RF0FE:1;       /* [2:2] Rx FIFO 0 full interrupt enable - RO */
    ureg32 RF0LE:1;       /* [3:3] Rx FIFO 0 message lost interrupt enable - RW */
    ureg32 RF1NE:1;       /* [4:4] Rx FIFO 1 new message interrupt enable -RW */
    ureg32 RF1WE:1;       /* [5:5] Rx FIFO 1 watermark reached interrupt enable - RW*/
    ureg32 RF1FE:1;       /* [6:6] Rx FIFO 1 full interrupt enable - RW */
    ureg32 RF1LE:1;       /* [7:7] Rx FIFO 1 message lost interrupt enable - RW*/
    ureg32 HPME:1;        /* [8:8] High priority message interrupt enable - RW */
    ureg32 TCE:1;         /* [9:9] Transmission completed interrupt enable - RW */
    ureg32 TCFE:1;        /* [10:10] Transmission cancellation finished interrupt enable - RW */
    ureg32 TFEE:1;        /* [11:11] Tx FIFO empty interrupt enable - RW */
    ureg32 TEFNE:1;       /* [12:12] Tx event FIFO new entry interrupt enable - RW */
    ureg32 TEFWE:1;       /* [13:13] Tx event FIFO watermark reached interrupt enable - RW */
    ureg32 TEFFE:1;       /* [14:14] Tx event FIFO full interrupt enable - RW */
    ureg32 TEFLE:1;       /* [15:15] Tx event FIFO element lost interrupt enable - RW */
    ureg32 TSWE:1;        /* [16:16] Timestamp wraparound interrupt enable - RW */
    ureg32 MRAFE:1;       /* [17:17] Message RAM access failure interrupt enable - RW */
    ureg32 TOOE:1;        /* [18:18] Timeout occurred interrupt enable - RW */
    ureg32 DRXE:1;        /* [19:19] Message stored to dedicated Rx buffer interrupt enable - RW */
    ureg32 BECE:1;        /* [20:20]  Bit error uncorrected - RW */
    ureg32 BEUE:1;        /* [21:21]  Bit error corrected- RW  */
    ureg32 ELOE:1;        /* [22:22] Error logging overflow interrupt enable - RW */
    ureg32 EPE:1;         /* [23:23] Error passive interrupt enable - RW */
    ureg32 EWE:1;         /* [24:24] Warning status interrupt enable - RW*/
    ureg32 BOE:1;         /* [25:25] Bus off status interrupt enable - RW */
    ureg32 WDIE:1;        /* [26:26] Watchdog interrupt enable - RW */
    ureg32 PEAE:1;        /* [27:27] Protocol error in arbitration phase enable - RW */
    ureg32 PEDE:1;        /* [28:28] Protocol error in data phase enable - RW */
    ureg32 ARAE:1;        /* [29:29] Access to reserved rddress - RW */
    ureg32 reserved_30:2; /* [31:30]  Internal reserved */
} CAN_IE_Bits;

/*  Interrupt line select  */

typedef struct
{
    ureg32 RF0NL:1;       /* [0:0] Rx FIFO 0 new message - RW*/
    ureg32 RF0WL:1;       /* [1:1] Rx FIFO 0 watermark reached - RW*/
    ureg32 RF0FL:1;       /* [2:2] Rx FIFO 0 full level - RW */
    ureg32 RF0LL:1;       /* [3:3] Rx FIFO 0 message lost - RW */
    ureg32 RF1NL:1;       /* [4:4] Rx FIFO 1 new message - RW */
    ureg32 RF1WL:1;       /* [5:5] Rx FIFO 1 Watermark reached - RW */
    ureg32 RF1FL:1;       /* [6:6] Rx FIFO 1 full level- RW*/
    ureg32 RF1LL:1;       /* [7:7] Rx FIFO 1 message lost - RW */
    ureg32 HPML:1;        /* [8:8] High priority message - RW */
    ureg32 TCL:1;         /* [9:9] Transmission completed - RW */
    ureg32 TCFL:1;        /* [10:10] Transmission cancellation finished - RW */
    ureg32 TFEL:1;        /* [11:11] Tx FIFO empty - RW */
    ureg32 TEFNL:1;       /* [12:12] Tx event FIFO new entry - RW */
    ureg32 TEFWL:1;       /* [13:13] Tx event FIFO watermark reached - RW */
    ureg32 TEFFL:1;       /* [14:14] Tx event FIFO full - RW */
    ureg32 TEFLL:1;       /* [15:15] Tx event FIFO element lost - RW */
    ureg32 TSWL:1;        /* [16:16] Timestamp wraparound - RW */
    ureg32 MRAFL:1;       /* [17:17] Message RAM access failure - RW*/
    ureg32 TOOL:1;        /* [18:18] Timeout occurred - RW */
    ureg32 DRXL:1;        /* [19:19] Message stored to dedicated Rx buffer - RW */
    ureg32 BECL:1;        /* [20:20]  Bit error uncorrected- RW*/
    ureg32 BEUL:1;        /* [21:21]  Bit error corrected- RW  */
    ureg32 ELOL:1;        /* [22:22] Error logging overflow - RW */
    ureg32 EPL:1;         /* [23:23] Error passive - RW */
    ureg32 EWL:1;         /* [24:24] Warning status - RW */
    ureg32 BOL:1;         /* [25:25] Bus off status -RW */
    ureg32 WDIL:1;        /* [26:26] Watchdog interrupt - RW */
    ureg32 PEAL:1;        /* [27:27] Protocol error in arbitration phase - RW */
    ureg32 PEDL:1;        /* [28:28] Protocol error in data phase - RW */
    ureg32 ARAL:1;        /* [29:29] Access to reserved dddress- RW */
    ureg32 reserved_30:2; /* [31:30] Internal reserved */
} CAN_ILS_Bits;

/*  Interrupt line enable register*/

typedef struct
{
    ureg32 EINT0:1;       /* [0:0] Enable interrupt line 0 - RW */
    ureg32 EINT1:1;       /* [1:1] Enable interrupt line 1 - RW*/
    ureg32 reserved_2:30; /* [31:2]  Internal reserved */
} CAN_ILE_Bits;

/*  Global filter configuration*/
typedef struct
{
    ureg32 RRFE:1;        /* [0:0] Reject remote frames extended - RW */
    ureg32 RRFS:1;        /* [1:1] Reject remote frames standard - RW */
    ureg32 ANFE:2;        /* [3:2] Accept non-matching frames extended - RW */
    ureg32 ANFS:2;        /* [5:4] Accept non-matching frames standard - RW*/
    ureg32 reserved_6:26; /* [31:6]  Internal reserved */
} CAN_GFC_Bits;

/*  Standard ID filter configuration */
typedef struct
{
    ureg32 reserved_0:2;  /* [1:0]  Internal reserved */
    ureg32 FLSSA:14;      /* [15:2] Filter list standard start address - RW */
    ureg32 LSS:8;         /* [23:16] List size standard - RW */
    ureg32 reserved_24:8; /* [31:24]  Internal reserved */
} CAN_SIDFC_Bits;

/*  Extended ID filter configuration  */
typedef struct
{
    ureg32 reserved_0:2;  /* [1:0]  Internal reserved */
    ureg32 FLESA:14;      /* [15:2] Filter list extended start address - RW */
    ureg32 LSE:7;         /* [22:16] List size extended - RW */
    ureg32 reserved_23:9; /* [31:23]  Internal reserved */
} CAN_XIDFC_Bits;

/*  Extended ID and mask  */
typedef struct
{
    ureg32 EIDM:29;       /* [28:0] Extended ID mask - RW */
    ureg32 reserved_29:3; /* [31:29]  Internal reserved */
} CAN_XIDAM_Bits;

/*  High priority message status  */
typedef struct
{
    ureg32 BIDX:6;         /* [5:0] Buffer index - RO */
    ureg32 MSI:2;          /* [7:6] Message storage indicator - RO */
    ureg32 FIDX:7;         /* [14:8] Filter index - RO */
    ureg32 FLST:1;         /* [15:15] Filter list - RO */
    ureg32 reserved_16:16; /* [31:16]  Internal reserved */
} CAN_HPMS_Bits;

/*  New data 1  */
typedef struct
{
    ureg32 ND0:1;  /* [0:0] New data in Rx buffer 0 - RW */
    ureg32 ND1:1;  /* [1:1] New data in Rx buffer 1 - RW */
    ureg32 ND2:1;  /* [2:2] New data in Rx bufferr 2 - RW */
    ureg32 ND3:1;  /* [3:3] New data in Rx buffer 3 - RW */
    ureg32 ND4:1;  /* [4:4] New data in Rx buffer 4 - RW */
    ureg32 ND5:1;  /* [5:5] New data in Rx buffer 5 - RW */
    ureg32 ND6:1;  /* [6:6] New data in Rx buffer 6 - RW */
    ureg32 ND7:1;  /* [7:7] New data in Rx buffer 7 - RW */
    ureg32 ND8:1;  /* [8:8] New data in Rx buffer 8 - RW */
    ureg32 ND9:1;  /* [9:9] New data in Rx buffer 9 - RW */
    ureg32 ND10:1; /* [10:10] New data in Rx buffer 10 - RW */
    ureg32 ND11:1; /* [11:11] New data in Rx buffer 11 - RW */
    ureg32 ND12:1; /* [12:12] New data in Rx buffer 12 - RW */
    ureg32 ND13:1; /* [13:13] New data in Rx buffer 13 - RW */
    ureg32 ND14:1; /* [14:14] New data in Rx buffer 14 - RW */
    ureg32 ND15:1; /* [15:15] New data in Rx buffer 15 - RW */
    ureg32 ND16:1; /* [16:16] New data in Rx buffer 16 - RW */
    ureg32 ND17:1; /* [17:17] New data in Rx buffer 17 - RW */
    ureg32 ND18:1; /* [18:18] New data in Rx buffer 18 - RW */
    ureg32 ND19:1; /* [19:19] New data in Rx buffer 19 - RW */
    ureg32 ND20:1; /* [20:20] New data in Rx buffer 20 - RW */
    ureg32 ND21:1; /* [21:21] New data in Rx buffer 21 - RW */
    ureg32 ND22:1; /* [22:22] New data in Rx buffer 22 - RW */
    ureg32 ND23:1; /* [23:23] New data in Rx buffer 23 - RW */
    ureg32 ND24:1; /* [24:24] New data in Rx buffer 24 - RW */
    ureg32 ND25:1; /* [25:25] New data in Rx buffer 25 - RW */
    ureg32 ND26:1; /* [26:26] New data in Rx buffer 26 - RW*/
    ureg32 ND27:1; /* [27:27] New data in Rx buffer 27 - RW */
    ureg32 ND28:1; /* [28:28] New data in Rx buffer 28 - RW */
    ureg32 ND29:1; /* [29:29] New data in Rx buffer 29 - RW */
    ureg32 ND30:1; /* [30:30] New data in Rx buffer 30 - RW */
    ureg32 ND31:1; /* [31:31] New data in Rx buffer 31 - RW */
} CAN_NDAT1_Bits;

/*  New data 2  */
typedef struct
{
    ureg32 ND32:1; /* [0:0] New data in Rx buffer 32 - RW */
    ureg32 ND33:1; /* [1:1] New data in Rx buffer 33 - RW */
    ureg32 ND34:1; /* [2:2] New data in Rx buffer 34 - RW */
    ureg32 ND35:1; /* [3:3] New data in Rx buffer 35 - RW */
    ureg32 ND36:1; /* [4:4] New data in Rx buffer 36 - RW */
    ureg32 ND37:1; /* [5:5] New data in Rx buffer 37 - RW */
    ureg32 ND38:1; /* [6:6] New data in Rx buffer 38 - RW */
    ureg32 ND39:1; /* [7:7] New data in Rx buffer 39 - RW */
    ureg32 ND40:1; /* [8:8] New data in Rx buffer 40 - RW */
    ureg32 ND41:1; /* [9:9] New data in Rx buffer 41 - RW */
    ureg32 ND42:1; /* [10:10] New data in Rx buffer 42 - RW */
    ureg32 ND43:1; /* [11:11] New data in Rx buffer 43 - RW */
    ureg32 ND44:1; /* [12:12] New data in Rx buffer 44 - RW */
    ureg32 ND45:1; /* [13:13] New data in Rx buffer 45 - RW */
    ureg32 ND46:1; /* [14:14] New data in Rx buffer 46 - RW */
    ureg32 ND47:1; /* [15:15] New data in Rx buffer 47 - RW */
    ureg32 ND48:1; /* [16:16] New data in Rx buffer 48 - RW */
    ureg32 ND49:1; /* [17:17] New data in Rx buffer 49 - RW */
    ureg32 ND50:1; /* [18:18] New data in Rx buffer 50 - RW */
    ureg32 ND51:1; /* [19:19] New data in Rx buffer 51 - RW */
    ureg32 ND52:1; /* [20:20] New data in Rx buffer 52 - RW */
    ureg32 ND53:1; /* [21:21] New data in Rx buffer 53 - RW */
    ureg32 ND54:1; /* [22:22] New data in Rx buffer 54 - RW */
    ureg32 ND55:1; /* [23:23] New data in Rx buffer 55 - RW */
    ureg32 ND56:1; /* [24:24] New data in Rx buffer 56 - RW */
    ureg32 ND57:1; /* [25:25] New data in Rx buffer 57 - RW */
    ureg32 ND58:1; /* [26:26] New data in Rx buffer 58 - RW */
    ureg32 ND59:1; /* [27:27] New data in Rx buffer 59 - RW */
    ureg32 ND60:1; /* [28:28] New data in Rx buffer 60 - RW */
    ureg32 ND61:1; /* [29:29] New data in Rx buffer 61 - RW */
    ureg32 ND62:1; /* [30:30] New data in Rx buffer 62 - RW */
    ureg32 ND63:1; /* [31:31] New data in Rx buffer 63 - RW */
} CAN_NDAT2_Bits;

/*  Rx FIFO 0 configuration */
typedef struct
{
    ureg32 reserved_0:2;  /* [1:0]  Internal reserved */
    ureg32 F0SA:14;       /* [15:2] Rx FIFO 0 start address - RW */
    ureg32 F0S:7;         /* [22:16] Rx FIFO 0 size - RW */
    ureg32 reserved_23:1; /* [23:23]  Internal reserved */
    ureg32 F0WM:7;        /* [30:24] Rx FIFO 0 watermark - RW */
    ureg32 F0OM:1;        /* [31:31] FIFO 0 operation mode - RW */
} CAN_RX_F0C_Bits;

/*  Rx FIFO 0 status */
typedef struct
{
    ureg32 F0FL:7;        /* [6:0] Rx FIFO 0 fill level - RO */
    ureg32 reserved_7:1;  /* [7:7] Internal reserved */
    ureg32 F0GI:6;        /* [13:8] Rx FIFO 0 get index - RO */
    ureg32 reserved_14:2; /* [15:14] Internal reserved */
    ureg32 F0PI:6;        /* [21:16] Rx FIFO 0 put index - RO */
    ureg32 reserved_22:2; /* [23:22] Internal reserved */
    ureg32 F0F:1;         /* [24:24] Rx FIFO 0 full - RO */
    ureg32 RF0L:1;        /* [25:25] Rx FIFO 0 message lost - RO */
    ureg32 reserved_26:6; /* [31:26] Internal reserved */
} CAN_RX_F0S_Bits;

/*  Rx FIFO 0 acknowledge  */
typedef struct
{
    ureg32 F0AI:6;        /* [5:0] Rx FIFO 0 acknowledge index - RW */
    ureg32 reserved_6:26; /* [31:6] Internal reserved */
} CAN_RX_F0A_Bits;

/*  Rx buffer configuration  */
typedef struct
{
    ureg32 reserved_0:2;   /* [1:0] Internal reserved */
    ureg32 RBSA:14;        /* [15:2] Rx buffer start address - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} CAN_RX_BC_Bits;

/*  Rx FIFO 1 configuration*/
typedef struct
{
    ureg32 reserved_0:2;  /* [1:0] Internal reserved */
    ureg32 F1SA:14;       /* [15:2] Rx FIFO 1 start address - RW */
    ureg32 F1S:7;         /* [22:16] Rx FIFO 1 size - RW */
    ureg32 reserved_23:1; /* [23:23] Internal reserved */
    ureg32 F1WM:7;        /* [30:24] Rx FIFO 1 watermark - RW */
    ureg32 F1OM:1;        /* [31:31] FIFO 1 operation mode - RW */
} CAN_RX_F1C_Bits;

/*  Rx FIFO 1 status  */
typedef struct
{
    ureg32 F1FL:7;        /* [6:0] Rx FIFO 1 fill level - RO */
    ureg32 reserved_7:1;  /* [7:7] Internal reserved */
    ureg32 F1GI:6;        /* [13:8] Rx FIFO 1 get index - RO */
    ureg32 reserved_14:2; /* [15:14] Internal reserved */
    ureg32 F1PI:6;        /* [21:16] Rx FIFO 1 put index - RO */
    ureg32 reserved_22:2; /* [23:22] Internal reserved */
    ureg32 F1F:1;         /* [24:24] Rx FIFO 1 full - RO */
    ureg32 RF1L:1;        /* [25:25] Rx FIFO 1 message lost - RO */
    ureg32 reserved_26:6; /* [31:26] Internal reserved */
} CAN_RX_F1S_Bits;

/*  Rx FIFO 1 acknowledge  */
typedef struct
{
    ureg32 F1AI:6;        /* [5:0] Rx FIFO 1 acknowledge index - RW */
    ureg32 reserved_6:26; /* [31:6] Internal reserved */
} CAN_RX_F1A_Bits;

/*  Rx buffer/FIFO element size configuration  */
typedef struct
{
    ureg32 F0DS:3;         /* [2:0] Rx FIFO 0 data field size - RW */
    ureg32 reserved_3:1;   /* [3:3] Internal reserved */
    ureg32 F1DS:3;         /* [6:4] Rx FIFO 1 data field size - RW */
    ureg32 reserved_7:1;   /* [7:7] Internal reserved */
    ureg32 RBDS:3;         /* [10:8] Rx buffer data field size - RW */
    ureg32 reserved_11:21; /* [31:11] Internal reserved */
} CAN_RX_ESC_Bits;

/*  Tx buffer configuration  */
typedef struct
{
    ureg32 reserved_0:2;  /* [1:0]  Internal reserved */
    ureg32 TBSA:14;       /* [15:2] Tx buffers start address - RW */
    ureg32 NDTB:6;        /* [21:16] Number of dedicated transmit buffers - RW */
    ureg32 reserved_22:2; /* [23:22] Internal reserved */
    ureg32 TFQS:6;        /* [29:24] Transmit FIFO/queue size - RW */
    ureg32 TFQM:1;        /* [30:30] Tx FIFO/queue mode - RW */
    ureg32 reserved_31:1; /* [31:31] Internal reserved */
} CAN_TX_BC_Bits;

/*  Tx FIFO/queue status  */
typedef struct
{
    ureg32 TFFL:6;         /* [5:0] Tx FIFO free level - RO */
    ureg32 reserved_6:2;   /* [7:6] Internal reserved */
    ureg32 TFGI:5;         /* [12:8] Tx FIFO get index - RO */
    ureg32 reserved_13:3;  /* [15:13] Internal reserved */
    ureg32 TFQPI:5;        /* [20:16] Tx FIFO/queue put index - RO */
    ureg32 TFQF:1;         /* [21:21] Tx FIFO/queue full - RO */
    ureg32 reserved_22:10; /* [31:22] Internal reserved */
} CAN_TX_FQS_Bits;

/*  Tx buffer element size configuration */
typedef struct
{
    ureg32 TBDS:3;        /* [2:0] Tx buffer data field size - RW */
    ureg32 reserved_3:29; /* [31:3] Internal reserved */
} CAN_TX_ESC_Bits;

/*  Tx buffer request pending */
typedef struct
{
    ureg32 TRP0:1;  /* [0:0] Transmission request pending Tx  buffer 0 - RO */
    ureg32 TRP1:1;  /* [1:1] Transmission request pending Tx  buffer 1 - RO */
    ureg32 TRP2:1;  /* [2:2] Transmission request pending Tx  buffer 2 - RO */
    ureg32 TRP3:1;  /* [3:3] Transmission request pending Tx  buffer 3 - RO */
    ureg32 TRP4:1;  /* [4:4] Transmission request pending Tx  buffer 4 - RO */
    ureg32 TRP5:1;  /* [5:5] Transmission request pending Tx  buffer 5 - RO */
    ureg32 TRP6:1;  /* [6:6] Transmission request pending Tx  buffer 6 - RO */
    ureg32 TRP7:1;  /* [7:7] Transmission request pending Tx  buffer 7 - RO */
    ureg32 TRP8:1;  /* [8:8] Transmission request pending Tx  buffer 8 - RO */
    ureg32 TRP9:1;  /* [9:9] Transmission request pending Tx  buffer 9 - RO */
    ureg32 TRP10:1; /* [10:10] Transmission request pending Tx  buffer 10 - RO */
    ureg32 TRP11:1; /* [11:11] Transmission request pending Tx  buffer 11 - RO */
    ureg32 TRP12:1; /* [12:12] Transmission request pending Tx  buffer 12 - RO */
    ureg32 TRP13:1; /* [13:13] Transmission request pending Tx  buffer 13 - RO */
    ureg32 TRP14:1; /* [14:14] Transmission request pending Tx  buffer 14 - RO */
    ureg32 TRP15:1; /* [15:15] Transmission request pending Tx  buffer 15 - RO */
    ureg32 TRP16:1; /* [16:16] Transmission request pending Tx  buffer 16 - RO */
    ureg32 TRP17:1; /* [17:17] Transmission request pending Tx  buffer 17 - RO */
    ureg32 TRP18:1; /* [18:18] Transmission request pending Tx  buffer 18 - RO */
    ureg32 TRP19:1; /* [19:19] Transmission request pending Tx  buffer 19 - RO */
    ureg32 TRP20:1; /* [20:20] Transmission request pending Tx  buffer 20 - RO */
    ureg32 TRP21:1; /* [21:21] Transmission request pending Tx  buffer 21 - RO */
    ureg32 TRP22:1; /* [22:22] Transmission request pending Tx  buffer 22 - RO */
    ureg32 TRP23:1; /* [23:23] Transmission request pending Tx  buffer 23 - RO */
    ureg32 TRP24:1; /* [24:24] Transmission request pending Tx  buffer 24 - RO */
    ureg32 TRP25:1; /* [25:25] Transmission request pending Tx  buffer 25 - RO */
    ureg32 TRP26:1; /* [26:26] Transmission request pending Tx  buffer 26 - RO */
    ureg32 TRP27:1; /* [27:27] Transmission request pending Tx  buffer 27 - RO */
    ureg32 TRP28:1; /* [28:28] Transmission request pending Tx  buffer 28 - RO */
    ureg32 TRP29:1; /* [29:29] Transmission request pending Tx  buffer 29 - RO */
    ureg32 TRP30:1; /* [30:30] Transmission request pending Tx  buffer 30 - RO */
    ureg32 TRP31:1; /* [31:31] Transmission request pending Tx  buffer 31 - RO */
} CAN_TX_BRP_Bits;

/*  Tx buffer add request  */
typedef struct
{
    ureg32 AR0:1;  /* [0:0] Add request Tx buffer 0 - RW */
    ureg32 AR1:1;  /* [1:1] Add request Tx buffer 1 - RW */
    ureg32 AR2:1;  /* [2:2] Add request Tx buffer 2 - RW */
    ureg32 AR3:1;  /* [3:3] Add request Tx buffer 3 - RW */
    ureg32 AR4:1;  /* [4:4] Add request Tx buffer 4 - RW */
    ureg32 AR5:1;  /* [5:5] Add request Tx buffer 5 - RW */
    ureg32 AR6:1;  /* [6:6] Add request Tx buffer 6 - RW */
    ureg32 AR7:1;  /* [7:7] Add request Tx buffer 7 - RW */
    ureg32 AR8:1;  /* [8:8] Add request Tx buffer 8 - RW */
    ureg32 AR9:1;  /* [9:9] Add request Tx buffer 9 - RW */
    ureg32 AR10:1; /* [10:10] Add request Tx buffer 10 - RW */
    ureg32 AR11:1; /* [11:11] Add request Tx buffer 11 - RW */
    ureg32 AR12:1; /* [12:12] Add request Tx buffer 12 - RW */
    ureg32 AR13:1; /* [13:13] Add request Tx buffer 13 - RW */
    ureg32 AR14:1; /* [14:14] Add request Tx buffer 14 - RW */
    ureg32 AR15:1; /* [15:15] Add request Tx buffer 15 - RW */
    ureg32 AR16:1; /* [16:16] Add request Tx buffer 16 - RW */
    ureg32 AR17:1; /* [17:17] Add request Tx buffer 17 - RW */
    ureg32 AR18:1; /* [18:18] Add request Tx buffer 18 - RW */
    ureg32 AR19:1; /* [19:19] Add request Tx buffer 19 - RW */
    ureg32 AR20:1; /* [20:20] Add request Tx buffer 20 - RW */
    ureg32 AR21:1; /* [21:21] Add request Tx buffer 21 - RW */
    ureg32 AR22:1; /* [22:22] Add request Tx buffer 22 - RW */
    ureg32 AR23:1; /* [23:23] Add request Tx buffer 23 - RW */
    ureg32 AR24:1; /* [24:24] Add request Tx buffer 24 - RW */
    ureg32 AR25:1; /* [25:25] Add request Tx buffer 25 - RW */
    ureg32 AR26:1; /* [26:26] Add request Tx buffer 26 - RW */
    ureg32 AR27:1; /* [27:27] Add request Tx buffer 27 - RW */
    ureg32 AR28:1; /* [28:28] Add request Tx buffer 28 - RW */
    ureg32 AR29:1; /* [29:29] Add request Tx buffer 29 - RW */
    ureg32 AR30:1; /* [30:30] Add request Tx buffer 30 - RW */
    ureg32 AR31:1; /* [31:31] Add request Tx buffer 31 - RW */
} CAN_TX_BAR_Bits;

/*  Tx buffer cancellation request */
typedef struct
{
    ureg32 CR0:1;  /* [0:0] Cancellation request Tx buffer 0 - RW */
    ureg32 CR1:1;  /* [1:1] Cancellation request Tx buffer 1 - RW */
    ureg32 CR2:1;  /* [2:2] Cancellation request Tx buffer 2 - RW */
    ureg32 CR3:1;  /* [3:3] Cancellation request Tx buffer 3 - RW */
    ureg32 CR4:1;  /* [4:4] Cancellation request Tx buffer 4 - RW */
    ureg32 CR5:1;  /* [5:5] Cancellation request Tx buffer 5 - RW */
    ureg32 CR6:1;  /* [6:6] Cancellation request Tx buffer 6 - RW */
    ureg32 CR7:1;  /* [7:7] Cancellation request Tx buffer 7 - RW */
    ureg32 CR8:1;  /* [8:8] Cancellation request Tx buffer 8 - RW */
    ureg32 CR9:1;  /* [9:9] Cancellation request Tx buffer 9 - RW */
    ureg32 CR10:1; /* [10:10] Cancellation request Tx buffer 10 - RW */
    ureg32 CR11:1; /* [11:11] Cancellation request Tx buffer 11 - RW */
    ureg32 CR12:1; /* [12:12] Cancellation request Tx buffer 12 - RW */
    ureg32 CR13:1; /* [13:13] Cancellation request Tx buffer 13 - RW */
    ureg32 CR14:1; /* [14:14] Cancellation request Tx buffer 14 - RW */
    ureg32 CR15:1; /* [15:15] Cancellation request Tx buffer 15 - RW */
    ureg32 CR16:1; /* [16:16] Cancellation request Tx buffer 16 - RW */
    ureg32 CR17:1; /* [17:17] Cancellation request Tx buffer 17 - RW */
    ureg32 CR18:1; /* [18:18] Cancellation request Tx buffer 18 - RW */
    ureg32 CR19:1; /* [19:19] Cancellation request Tx buffer 19 - RW */
    ureg32 CR20:1; /* [20:20] Cancellation request Tx buffer 20 - RW */
    ureg32 CR21:1; /* [21:21] Cancellation request Tx buffer 21 - RW */
    ureg32 CR22:1; /* [22:22] Cancellation request Tx buffer 22 - RW */
    ureg32 CR23:1; /* [23:23] Cancellation request Tx buffer 23 - RW */
    ureg32 CR24:1; /* [24:24] Cancellation request Tx buffer 24 - RW */
    ureg32 CR25:1; /* [25:25] Cancellation request Tx buffer 25 - RW */
    ureg32 CR26:1; /* [26:26] Cancellation request Tx buffer 26 - RW */
    ureg32 CR27:1; /* [27:27] Cancellation request Tx buffer 27 - RW */
    ureg32 CR28:1; /* [28:28] Cancellation request Tx buffer 28 - RW */
    ureg32 CR29:1; /* [29:29] Cancellation request Tx buffer 29 - RW */
    ureg32 CR30:1; /* [30:30] Cancellation request Tx buffer 30 - RW */
    ureg32 CR31:1; /* [31:31] Cancellation request Tx buffer 31 - RW */
} CAN_TX_BCR_Bits;

/*  Tx Buffer Transmission Occurred  */
typedef struct
{
    ureg32 TO0:1;  /* [0:0] Transmission occurred Tx buffer 0 - RO */
    ureg32 TO1:1;  /* [1:1] Transmission occurred Tx buffer 1 - RO */
    ureg32 TO2:1;  /* [2:2] Transmission occurred Tx buffer 2 - RO */
    ureg32 TO3:1;  /* [3:3] Transmission occurred Tx buffer 3 - RO */
    ureg32 TO4:1;  /* [4:4] Transmission occurred Tx buffer 4 - RO */
    ureg32 TO5:1;  /* [5:5] Transmission occurred Tx buffer 5 - RO */
    ureg32 TO6:1;  /* [6:6] Transmission occurred Tx buffer 6 - RO */
    ureg32 TO7:1;  /* [7:7] Transmission occurred Tx buffer 7 - RO */
    ureg32 TO8:1;  /* [8:8] Transmission occurred Tx buffer 8 - RO */
    ureg32 TO9:1;  /* [9:9] Transmission occurred Tx buffer 9 - RO */
    ureg32 TO10:1; /* [10:10] Transmission occurred Tx buffer 10 - RO */
    ureg32 TO11:1; /* [11:11] Transmission occurred Tx buffer 11 - RO */
    ureg32 TO12:1; /* [12:12] Transmission occurred Tx buffer 12 - RO */
    ureg32 TO13:1; /* [13:13] Transmission occurred Tx buffer 13 - RO */
    ureg32 TO14:1; /* [14:14] Transmission occurred Tx buffer 14 - RO */
    ureg32 TO15:1; /* [15:15] Transmission occurred Tx buffer 15 - RO */
    ureg32 TO16:1; /* [16:16] Transmission occurred Tx buffer 16 - RO */
    ureg32 TO17:1; /* [17:17] Transmission occurred Tx buffer 17 - RO */
    ureg32 TO18:1; /* [18:18] Transmission occurred Tx buffer 18 - RO */
    ureg32 TO19:1; /* [19:19] Transmission occurred Tx buffer 19 - RO */
    ureg32 TO20:1; /* [20:20] Transmission occurred Tx buffer 20 - RO */
    ureg32 TO21:1; /* [21:21] Transmission occurred Tx buffer 21 - RO */
    ureg32 TO22:1; /* [22:22] Transmission occurred Tx buffer 22 - RO */
    ureg32 TO23:1; /* [23:23] Transmission occurred Tx buffer 23 - RO */
    ureg32 TO24:1; /* [24:24] Transmission occurred Tx buffer 24 - RO */
    ureg32 TO25:1; /* [25:25] Transmission occurred Tx buffer 25 - RO */
    ureg32 TO26:1; /* [26:26] Transmission occurred Tx buffer 26 - RO */
    ureg32 TO27:1; /* [27:27] Transmission occurred Tx buffer 27 - RO */
    ureg32 TO28:1; /* [28:28] Transmission occurred Tx buffer 28 - RO */
    ureg32 TO29:1; /* [29:29] Transmission occurred Tx buffer 29 - RO */
    ureg32 TO30:1; /* [30:30] Transmission occurred Tx buffer 30 - RO */
    ureg32 TO31:1; /* [31:31] Transmission occurred Tx buffer 31 - RO */
} CAN_TX_BTO_Bits;

/*  Tx buffer cancellation finished  */
typedef struct
{
    ureg32 CF0:1;  /* [0:0] Cancellation finished Tx buffer 0 - RO */
    ureg32 CF1:1;  /* [1:1] Cancellation finished Tx buffer 1 - RO */
    ureg32 CF2:1;  /* [2:2] Cancellation finished Tx buffer 2 - RO */
    ureg32 CF3:1;  /* [3:3] Cancellation finished Tx buffer 3 - RO */
    ureg32 CF4:1;  /* [4:4] Cancellation finished Tx buffer 4 - RO */
    ureg32 CF5:1;  /* [5:5] Cancellation finished Tx buffer 5 - RO */
    ureg32 CF6:1;  /* [6:6] Cancellation finished Tx buffer 6 - RO */
    ureg32 CF7:1;  /* [7:7] Cancellation finished Tx buffer 7 - RO */
    ureg32 CF8:1;  /* [8:8] Cancellation finished Tx buffer 8 - RO */
    ureg32 CF9:1;  /* [9:9] Cancellation finished Tx buffer 9 - RO */
    ureg32 CF10:1; /* [10:10] Cancellation finished Tx buffer 10 - RO */
    ureg32 CF11:1; /* [11:11] Cancellation finished Tx buffer 11 - RO */
    ureg32 CF12:1; /* [12:12] Cancellation finished Tx buffer 12 - RO */
    ureg32 CF13:1; /* [13:13] Cancellation finished Tx buffer 13 - RO */
    ureg32 CF14:1; /* [14:14] Cancellation finished Tx buffer 14 - RO */
    ureg32 CF15:1; /* [15:15] Cancellation finished Tx buffer 15 - RO */
    ureg32 CF16:1; /* [16:16] Cancellation finished Tx buffer 16 - RO */
    ureg32 CF17:1; /* [17:17] Cancellation finished Tx buffer 17 - RO */
    ureg32 CF18:1; /* [18:18] Cancellation finished Tx buffer 18 - RO */
    ureg32 CF19:1; /* [19:19] Cancellation finished Tx buffer 19 - RO */
    ureg32 CF20:1; /* [20:20] Cancellation finished Tx buffer 20 - RO */
    ureg32 CF21:1; /* [21:21] Cancellation finished Tx buffer 21 - RO */
    ureg32 CF22:1; /* [22:22] Cancellation finished Tx buffer 22 - RO */
    ureg32 CF23:1; /* [23:23] Cancellation finished Tx buffer 23 - RO */
    ureg32 CF24:1; /* [24:24] Cancellation finished Tx buffer 24 - RO */
    ureg32 CF25:1; /* [25:25] Cancellation finished Tx buffer 25 - RO */
    ureg32 CF26:1; /* [26:26] Cancellation finished Tx buffer 26 - RO */
    ureg32 CF27:1; /* [27:27] Cancellation finished Tx buffer 27 - RO */
    ureg32 CF28:1; /* [28:28] Cancellation finished Tx buffer 28 - RO */
    ureg32 CF29:1; /* [29:29] Cancellation finished Tx buffer 29 - RO */
    ureg32 CF30:1; /* [30:30] Cancellation finished Tx buffer 30 - RO */
    ureg32 CF31:1; /* [31:31] Cancellation finished Tx buffer 31 - RO */
} CAN_TX_BCF_Bits;

/*  Tx buffer transmission interrupt enable  */
typedef struct
{
    ureg32 TIE0:1;  /* [0:0] Transmission interrupt enable Tx buffer 0 - RW */
    ureg32 TIE1:1;  /* [1:1] Transmission interrupt enable Tx buffer 1 - RW  */
    ureg32 TIE2:1;  /* [2:2] Transmission interrupt enable Tx buffer 2 - RW  */
    ureg32 TIE3:1;  /* [3:3] Transmission interrupt enable Tx buffer 3 - RW  */
    ureg32 TIE4:1;  /* [4:4] Transmission interrupt enable Tx buffer 4 - RW  */
    ureg32 TIE5:1;  /* [5:5] Transmission interrupt enable Tx buffer 5 - RW  */
    ureg32 TIE6:1;  /* [6:6] Transmission interrupt enable Tx buffer 6 - RW  */
    ureg32 TIE7:1;  /* [7:7] Transmission interrupt enable Tx buffer 7 - RW  */
    ureg32 TIE8:1;  /* [8:8] Transmission interrupt enable Tx buffer 8 - RW  */
    ureg32 TIE9:1;  /* [9:9] Transmission interrupt enable Tx buffer 9 - RW */
    ureg32 TIE10:1; /* [10:10] Transmission interrupt enable Tx buffer 10 - RW  */
    ureg32 TIE11:1; /* [11:11] Transmission interrupt enable Tx buffer 11 - RW  */
    ureg32 TIE12:1; /* [12:12] Transmission interrupt enable Tx buffer 12 - RW  */
    ureg32 TIE13:1; /* [13:13] Transmission interrupt enable Tx buffer 13 - RW  */
    ureg32 TIE14:1; /* [14:14] Transmission interrupt enable Tx buffer 14 - RW  */
    ureg32 TIE15:1; /* [15:15] Transmission interrupt enable Tx buffer 15 - RW  */
    ureg32 TIE16:1; /* [16:16] Transmission interrupt enable Tx buffer 16 - RW  */
    ureg32 TIE17:1; /* [17:17] Transmission interrupt enable Tx buffer 17 - RW  */
    ureg32 TIE18:1; /* [18:18] Transmission interrupt enable Tx buffer 18 - RW  */
    ureg32 TIE19:1; /* [19:19] Transmission interrupt enable Tx buffer 19 - RW  */
    ureg32 TIE20:1; /* [20:20] Transmission interrupt enable Tx buffer 20 - RW  */
    ureg32 TIE21:1; /* [21:21] Transmission interrupt enable Tx buffer 21 - RW */
    ureg32 TIE22:1; /* [22:22] Transmission interrupt enable Tx buffer 22 - RW  */
    ureg32 TIE23:1; /* [23:23] Transmission interrupt enable Tx buffer 23 - RW  */
    ureg32 TIE24:1; /* [24:24] Transmission interrupt enable Tx buffer 24 - RW  */
    ureg32 TIE25:1; /* [25:25] Transmission interrupt enable Tx buffer 25 - RW  */
    ureg32 TIE26:1; /* [26:26] Transmission interrupt enable Tx buffer 26 - RW  */
    ureg32 TIE27:1; /* [27:27] Transmission interrupt enable Tx buffer 27 - RW  */
    ureg32 TIE28:1; /* [28:28] Transmission interrupt enable Tx buffer 28 - RW  */
    ureg32 TIE29:1; /* [29:29] Transmission interrupt enable Tx buffer 29 - RW  */
    ureg32 TIE30:1; /* [30:30] Transmission interrupt enable Tx buffer 30 - RW  */
    ureg32 TIE31:1; /* [31:31] Transmission interrupt enable Tx buffer 31 - RW */
} CAN_TX_BTIE_Bits;

/*  Tx Buffer Cancellation Finished Interrupt Enable  */
typedef struct
{
    ureg32 CFIE0:1;  /* [0:0] Cancellation finished interrupt enable Tx buffer 0 - RW  */
    ureg32 CFIE1:1;  /* [1:1] Cancellation finished interrupt enable Tx buffer 1 - RW  */
    ureg32 CFIE2:1;  /* [2:2] Cancellation finished interrupt enable Tx buffer 2 - RW  */
    ureg32 CFIE3:1;  /* [3:3] Cancellation finished interrupt enable Tx buffer 3 - RW  */
    ureg32 CFIE4:1;  /* [4:4] Cancellation finished interrupt enable Tx buffer 4 - RW */
    ureg32 CFIE5:1;  /* [5:5] Cancellation finished interrupt enable Tx buffer 5 - RW */
    ureg32 CFIE6:1;  /* [6:6] Cancellation finished interrupt enable Tx buffer 6 - RW */
    ureg32 CFIE7:1;  /* [7:7] Cancellation finished interrupt enable Tx buffer 7 - RW */
    ureg32 CFIE8:1;  /* [8:8] Cancellation finished interrupt enable Tx buffer 8 - RW */
    ureg32 CFIE9:1;  /* [9:9] Cancellation finished interrupt enable Tx buffer 9 - RW */
    ureg32 CFIE10:1; /* [10:10] Cancellation finished interrupt enable Tx buffer 10 - RW */
    ureg32 CFIE11:1; /* [11:11] Cancellation finished interrupt enable Tx buffer 11 - RW */
    ureg32 CFIE12:1; /* [12:12] Cancellation finished interrupt enable Tx buffer 12 - RW */
    ureg32 CFIE13:1; /* [13:13] Cancellation finished interrupt enable Tx buffer 13 - RW */
    ureg32 CFIE14:1; /* [14:14] Cancellation finished interrupt enable Tx buffer 14 - RW */
    ureg32 CFIE15:1; /* [15:15] Cancellation finished interrupt enable Tx buffer 15 - RW */
    ureg32 CFIE16:1; /* [16:16] Cancellation finished interrupt enable Tx buffer 16 - RW */
    ureg32 CFIE17:1; /* [17:17] Cancellation finished interrupt enable Tx buffer 17 - RW */
    ureg32 CFIE18:1; /* [18:18] Cancellation finished interrupt enable Tx buffer 18 - RW */
    ureg32 CFIE19:1; /* [19:19] Cancellation finished interrupt enable Tx buffer 19 - RW */
    ureg32 CFIE20:1; /* [20:20] Cancellation finished interrupt enable Tx buffer 20 - RW */
    ureg32 CFIE21:1; /* [21:21] Cancellation finished interrupt enable Tx buffer 21 - RW */
    ureg32 CFIE22:1; /* [22:22] Cancellation finished interrupt enable Tx buffer 22 - RW */
    ureg32 CFIE23:1; /* [23:23] Cancellation finished interrupt enable Tx buffer 23 - RW */
    ureg32 CFIE24:1; /* [24:24] Cancellation finished interrupt enable Tx buffer 24 - RW */
    ureg32 CFIE25:1; /* [25:25] Cancellation finished interrupt enable Tx buffer 25 - RW */
    ureg32 CFIE26:1; /* [26:26] Cancellation finished interrupt enable Tx buffer 26 - RW */
    ureg32 CFIE27:1; /* [27:27] Cancellation finished interrupt enable Tx buffer 27 - RW */
    ureg32 CFIE28:1; /* [28:28] Cancellation finished interrupt enable Tx buffer 28 - RW */
    ureg32 CFIE29:1; /* [29:29] Cancellation finished interrupt enable Tx buffer 29 - RW */
    ureg32 CFIE30:1; /* [30:30] Cancellation finished interrupt enable Tx buffer 30 - RW */
    ureg32 CFIE31:1; /* [31:31] Cancellation finished interrupt enable Tx buffer 31 - RW */
} CAN_TX_BCIE_Bits;

/*  Tx event FIFO configuration  */
typedef struct
{
    ureg32 reserved_0:2;  /* [1:0] Internal reserved */
    ureg32 EFSA:14;       /* [15:2] Event FIFO start address - RW */
    ureg32 EFS:6;         /* [21:16] Event FIFO size - RW */
    ureg32 reserved_22:2; /* [23:22] Internal reserved */
    ureg32 EFWM:6;        /* [29:24] Event FIFO water mark - RW */
    ureg32 reserved_30:2; /* [31:30] Internal reserved */
} CAN_TX_EFC_Bits;

/*  Tx event FIFO status  */
typedef struct
{
    ureg32 EFFL:6;        /* [5:0] Event FIFO fill level - RO */
    ureg32 reserved_6:2;  /* [7:6] Internal reserved */
    ureg32 EFGI:5;        /* [12:8] Event FIFO get index - RO */
    ureg32 reserved_13:3; /* [15:13] Internal reserved */
    ureg32 EFPI:5;        /* [20:16] Event FIFO put index - RO */
    ureg32 reserved_21:3; /* [23:21] Internal reserved */
    ureg32 EFF:1;         /* [24:24] Event FIFO full - RO */
    ureg32 TEFL:1;        /* [25:25] Tx event FIFO element lost - RO */
    ureg32 reserved_26:6; /* [31:26] Internal reserved */
} CAN_TX_EFS_Bits;

/*  Tx event FIFO acknowledge */
typedef struct
{
    ureg32 EFAI:5;        /* [4:0] Event FIFO acknowledge index - RW */
    ureg32 reserved_5:27; /* [31:5]  Internal reserved */
} CAN_TX_EFA_Bits;

/*  Register 0 */
typedef struct
{
    ureg32 ID:29; /* [28:0] Identifier - RW  */
    ureg32 RTR:1; /* [29:29] Remote transmission request - RW  */
    ureg32 XTD:1; /* [30:30] Extended identifier - RW  */
    ureg32 ESI:1; /* [31:31] Error state indicator - RW  */
} CAN_R0_Bits;

/*  Register 1 */
typedef struct
{
    ureg32 RXTS:16;       /* [15:0] Rx time stamp - RW  */
    ureg32 DLC:4;         /* [19:16] Data length code - RW  */
    ureg32 BRS:1;         /* [20:20] Bit rate switch - RW  */
    ureg32 FDF:1;         /* [21:21] Frame data format - RW  */
    ureg32 reserved_22:2; /* [23:22]  Internal reserved */
    ureg32 FIDX:7;        /* [30:24] Filter index - RW  */
    ureg32 ANMF:1;        /* [31:31] Accepted non-matching frame - RW  */
} CAN_R1_Bits;

/*  Transmit buffer 0 */
typedef struct
{
    ureg32 ID:29; /* [28:0] Identifier - RW  */
    ureg32 RTR:1; /* [29:29] Remote transmission request - RW  */
    ureg32 XTD:1; /* [30:30] Extended identifier - RW  */
    ureg32 ESI:1; /* [31:31] Error state indicator - RW  */
} CAN_TXMSG_T0_Bits;

/*  Transmit buffer 1 */
typedef struct
{
    ureg32 reserved_0:8;  /* [7:0]  Internal reserved */
    ureg32 MM_H:8;        /* [15:8]  MM high 8 bit */
    ureg32 DLC:4;         /* [19:16] Data length code - RW  */
    ureg32 BRS:1;         /* [20:20] Bit rate switching - RW  */
    ureg32 FDF:1;         /* [21:21] FD format - RW  */
    ureg32 reserved_22:1; /* [22:22]  Internal reserved */
    ureg32 EFC:1;         /* [23:23] Event FIFO control - RW  */
    ureg32 MM:8;          /* [31:24] Message marker - RW  */
} CAN_TXMSG_T1_Bits;

/*  Event 0 */
typedef struct
{
    ureg32 ID:29; /* [28:0] Identifier - RW  */
    ureg32 RTR:1; /* [29:29] Remote transmission request - RW  */
    ureg32 XTD:1; /* [30:30] Extended identifier - RW  */
    ureg32 ESI:1; /* [31:31] Error state indicator - RW  */
} CAN_TXEVENT_E0_Bits;

/*  Event 1 */
typedef struct
{
    ureg32 TXTS:16; /* [15:0] Tx timestamp - RW  */
    ureg32 DLC:4;   /* [19:16] Data length code - RW  */
    ureg32 BRS:1;   /* [20:20] Bit rate switch - RW  */
    ureg32 FDF:1;   /* [21:21] FD format - RW */
    ureg32 ET:2;    /* [23:22] Event type - RW  */
    ureg32 MM:8;    /* [31:24] Message marker - RW  */
} CAN_TXEVENT_E1_Bits;

/*  Standard message 0 */
typedef struct
{
    ureg32 SFID2:11;      /* [10:0] Standard filter ID 2 - RW  */
    ureg32 reserved_11:5; /* [15:11] Internal reserved */
    ureg32 SFID1:11;      /* [26:16] Standard filter ID 1 - RW  */
    ureg32 SFEC:3;        /* [29:27] Standard filter element configuration - RW */
    ureg32 SFT:2;         /* [31:30] Standard filter type - RW  */
} CAN_STDMSG_S0_Bits;

/*  Extended message 0 */
typedef struct
{
    ureg32 EFID1:29; /* [28:0] Extended filter ID 1 - RW  */
    ureg32 EFEC:3;   /* [31:29] Extended filter element configuration - RW  */
} CAN_EXTMSG_F0_Bits;

/*  Filter element 1  note */
typedef struct
{
    ureg32 EFID2:29;      /* [28:0 ] Extended filter ID 2 - RW  */
    ureg32 reserved_29:1; /* [29:29] Internal reserved */
    ureg32 EFT:2;         /* [31:30] Extended filter type - RW */
} CAN_EXTMSG_F1_Bits;

/*  DMU Core release  */
typedef struct
{
    ureg32 DAY:8;     /* [7:0] Time stamp day - RO */
    ureg32 MON:8;     /* [15:8] Time stamp month - RO */
    ureg32 YEAR:4;    /* [19:16] Time stamp year - RO*/
    ureg32 SUBSTEP:4; /* [23:20] Sub-step of core release - - RO */
    ureg32 STEP:4;    /* [27:24] Step of core release - - RO */
    ureg32 REL:4;     /* [31:28] Core release -- RO */
} CAN_DMUCR_Bits;

/*  DMU  internals register  */
typedef struct
{
    ureg32 TXR:1;         /* [0:0] TX service request line of DMU - RO */
    ureg32 RX0R:1;        /* [1:1] RX0 service request line of DMU -RO */
    ureg32 RX1R:1;        /* [2:2] RX1 service request line of DMU -RO */
    ureg32 TXER:1;        /* [3:3] TX event service request line of DMU -RO */
    ureg32 reserved_4:4;  /* [7:4] Internal reserved */
    ureg32 TFQPIP:5;      /* [12:8]  TX FIFO/queue put index previous -RO */
    ureg32 reserved_13:2; /* [14:13] Internal reserved */
    ureg32 ENA:1;         /* [15:15] DMU is enabled -RO */
    ureg32 DEHS:3;        /* [18:16] Detect element handler state -RO */
    ureg32 reserved_19:1; /* [19:19] Internal reserved */
    ureg32 DTXE:1;        /* [20:20] DTXE detect DMU element service -RO */
    ureg32 DRX1:1;        /* [21:21] DRX1 detect DMU element service -RO */
    ureg32 DRX0:1;        /* [22:22] DRX0 detect DMU element service -RO */
    ureg32 DTX:1;         /* [23:23] DTX detect DMU element service -RO */
    ureg32 EHS:3;         /* [26:24] Element handler State -RO */
    ureg32 reserved_27:1; /* [27:27] Internal reserved */
    ureg32 TXE:1;         /* [28:28] TXE actual DMU element service -RO */
    ureg32 RX1:1;         /* [29:29] RX1 actual DMU element service -RO */
    ureg32 RX0:1;         /* [30:30] RX0 actual DMU element service -RO */
    ureg32 TX:1;          /* [31:31] TX actual DMU element service -RO */
} CAN_DMUI_Bits;

/*  DMU queueing counter  register  */
typedef struct
{
    ureg32 TXEEC:8;  /* [7:0] TX element enqueueing counter -RO */
    ureg32 RX0EDC:8; /* [15:8] RX0 element dequeueing counter -RO */
    ureg32 RX1EDC:8; /* [23:16] RX1 element dequeueing counter -RO */
    ureg32 TXEEDC:8; /* [31:24] TX event element dequeueing counter - RO */
} CAN_DMUQC_Bits;

/*  DMU interrupt register  */
typedef struct
{
    ureg32 TXENSA:1;      /* [0:0] TX element not start address - RC */
    ureg32 TXEIE:1;       /* [1:1] TX element illegal enqueueing - RC */
    ureg32 TXEIAS:1;      /* [2:2] TX element illegal access sequence - RC */
    ureg32 TXEIDLC:1;     /* [3:3] TX element illegal DLC - RC */
    ureg32 TXEWATA:1;     /* [4:4] TX element write after trigger address - RC */
    ureg32 TXEIR:1;       /* [5:5] TX element illegal Read - RC */
    ureg32 TXEE:1;        /* [6:6] TX element enqueued- RC */
    ureg32 reserved_7:1;  /* [7:7] Internal reserved -R */
    ureg32 RX0ENSA:1;     /* [8:8] RX0 element not start address - RC */
    ureg32 RX0EID:1;      /* [9:9] RX0 element illegal dequeueing - RC */
    ureg32 RX0EIAS:1;     /* [10:10] RX0 element illegal access sequence - RC */
    ureg32 RX0EIW:1;      /* [11:11] RX0 element illegal write - RC) */
    ureg32 RX0ED:1;       /* [12:12] RX0 element dequeued- RC */
    ureg32 RX0EIO:1;      /* [13:13] RX0 element illegal oveRCrite by timestamp- RC */
    ureg32 BEC:1;         /* [14:14] Bit error corrected - RC */
    ureg32 BEU:1;         /* [15:15] Bit error uncorrected - RC */
    ureg32 RX1ENSA:1;     /* [16:16] RX1 element not start address - RC */
    ureg32 RX1EID:1;      /* [17:17] RX1 element illegal dequeueing - RC */
    ureg32 RX1EIAS:1;     /* [18:18] RX1 element illegal access sequence - RC */
    ureg32 RX1EIW:1;      /* [19:19] RX1 element illegal write - RC) */
    ureg32 RX1ED:1;       /* [20:20] RX1 element dequeued- RC */
    ureg32 RX1EIO:1;      /* [21:21] RX1 element illegal oveRCrite by timestamp- RC */
    ureg32 reserved_22:2; /* [23:22] Internal reserved -R */
    ureg32 TXEENSA:1;     /* [24:24] TX event element not start address - RC */
    ureg32 TXEEID:1;      /* [25:25] TX event element Illegal dequeueing - RC */
    ureg32 TXEEIAS:1;     /* [26:26] TX event element Illegal access sequence - RC */
    ureg32 TXEEIW:1;      /* [27:27] TX event element Illegal write - RC */
    ureg32 TXEED:1;       /* [28:28] TX event element dequeued - RC */
    ureg32 DT:1;          /* [29:29] Debug trigger- RC */
    ureg32 IAC:1;         /* [30:30] Illegal access while in configuration mode- RC */
    ureg32 reserved_31:1; /* [31:31]  Internal reserved -R */
} CAN_DMUIR_Bits;

/*  DMU interrupt enable register */
typedef struct
{
    ureg32 TXENSAE:1;     /* [0:0] TX element not start address enable - RW */
    ureg32 TXEIEE:1;      /* [1:1] TX element illegal enqueueing enable- RW */
    ureg32 TXEIASE:1;     /* [2:2] TX element illegal access sequence enable- RW */
    ureg32 TXEIDLCE:1;    /* [3:3] TX element illegal DLC enable - RW */
    ureg32 TXEWATAE:1;    /* [4:4] TX element write after trigger address enable - RW */
    ureg32 TXEIRE:1;      /* [5:5] TX element illegal Read enable - RW */
    ureg32 TXEEE:1;       /* [6:6] TX element enqueued enable- RW */
    ureg32 reserved_7:1;  /* [7:7] Internal reserved -R */
    ureg32 RX0ENSAE:1;    /* [8:8] RX0 element not start address enable - RW */
    ureg32 RX0EIDE:1;     /* [9:9] RX0 element illegal dequeueing enable - RW */
    ureg32 RX0EIASE:1;    /* [10:10] RX0 element illegal access sequence enable - RW */
    ureg32 RX0EIWE:1;     /* [11:11] RX0 element illegal write enable - RW */
    ureg32 RX0EDE:1;      /* [12:12] RX0 element dequeued enable - RW */
    ureg32 RX0EIOE:1;     /* [13:13] RX0 element illegal overwrite by timestamp enable - RW  */
    ureg32 BECE:1;        /* [14:14] Bit error corrected  enable - RW */
    ureg32 BEUE:1;        /* [15:15] Bit error uncorrected enable - RW */
    ureg32 RX1ENSAE:1;    /* [16:16] RX1 element not start address enable - RW */
    ureg32 RX1EIDE:1;     /* [17:17] RX1 element illegal dequeueing enable - RW */
    ureg32 RX1EIASE:1;    /* [18:18] RX1 element illegal access sequence enable - RW */
    ureg32 RX1EIWE:1;     /* [19:19] RX1 element illegal write enable - RW */
    ureg32 RX1EDE:1;      /* [20:20] RX1 element dequeued enable - RW */
    ureg32 RX1EIOE:1;     /* [21:21] RX1 element illegal overwrite by timestamp enable - RW  */
    ureg32 reserved_22:2; /* [23:22] Internal reserved -R */
    ureg32 TXEENSAE:1;    /* [24:24] TX event element not start address enable - RW */
    ureg32 TXEEIDE:1;     /* [25:25] TX event element illegal dequeueing enable - RW */
    ureg32 TXEEIASE:1;    /* [26:26] TX event element illegal access sequence enable - RW */
    ureg32 TXEEIWE:1;     /* [27:27] TX event element illegal write enable - RW */
    ureg32 TXEEDE:1;      /* [28:28] TX event element dequeued enable - RW */
    ureg32 DTE:1;         /* [29:29] Debug trigger enable -RW */
    ureg32 IACE:1;        /* [30:30] Illegal access while in configuration mode enable - RW */
    ureg32 reserved_31:1; /* [31:31]  Internal reserved -R */
} CAN_DMUIE_Bits;

/*  Module version */
typedef struct
{
    ureg32 MOD_REV:8; /* [7:0]   Module version number - RO */
    ureg32 DAY:8;     /* [15:8]  Module version: day  - RO */
    ureg32 MON:8;     /* [23:16] Module version: month  - RO */
    ureg32 YEAR:8;    /* [31:24] Module version: Year  - RO */
} CAN_ID_Bits;

/*  Enable interrupt sources after classification merging 0x804+n*0x1800 */
typedef struct
{
    ureg32 RF0NRE:1;      /* [0:0] Rx FIFO 0 new message - RW */
    ureg32 RF0WRE:1;      /* [1:1] Rx FIFO 0 watermark reached - RW */
    ureg32 RF0FRE:1;      /* [2:2] Rx FIFO 0 full - RW */
    ureg32 RF0LRE:1;      /* [3:3] Rx FIFO 0 message lost - RW */
    ureg32 RF1NRE:1;      /* [4:4] Rx FIFO 1 new message - RW */
    ureg32 RF1WRE:1;      /* [5:5] Rx FIFO 1 watermark reached - RW */
    ureg32 RF1FRE:1;      /* [6:6] Rx FIFO 1 full - RW */
    ureg32 RF1LRE:1;      /* [7:7] Rx FIFO 1 message lost - RW */
    ureg32 HPMRE:1;       /* [8:8] High priority message - RW */
    ureg32 TCRE:1;        /* [9:9] Transmission completed - RW */
    ureg32 TCFRE:1;       /* [10:10] Transmission cancellation finished - RW */
    ureg32 TFERE:1;       /* [11:11] Tx FIFO empty - RW */
    ureg32 TEFNRE:1;      /* [12:12] Tx event FIFO new Entry - RW */
    ureg32 TEFWRE:1;      /* [13:13] Tx event FIFO watermark reached - RW */
    ureg32 TEFFRE:1;      /* [14:14] Tx event FIFO full - RW */
    ureg32 TEFLRE:1;      /* [15:15] Tx event FIFO element lost - RW */
    ureg32 TSWRE:1;       /* [16:16] Timestamp wraparound - RW */
    ureg32 MRAFRE:1;      /* [17:17] Message RAM access failure - RW */
    ureg32 TOORE:1;       /* [18:18] Timeout occurred - RW */
    ureg32 DRXRE:1;       /* [19:19] Message stored to dedicated Rx buffer - RW */
    ureg32 BECRE:1;       /* [20:20] Bit error uncorrected- RW */
    ureg32 BEURE:1;       /* [21:21] Bit error corrected- RW  */
    ureg32 ELORE:1;       /* [22:22] Error logging overflow - RW */
    ureg32 EPRE:1;        /* [23:23] Error passive - RW */
    ureg32 EWRE:1;        /* [24:24] Warning status - RW */
    ureg32 BORE:1;        /* [25:25] Bus off status - RW */
    ureg32 WDIRE:1;       /* [26:26] Watchdog interrupt - RW */
    ureg32 PEARE:1;       /* [27:27] Protocol error in arbitration phase - RW */
    ureg32 PEDRE:1;       /* [28:28] Protocol error in data phase - RW */
    ureg32 ARARE:1;       /* [29:29] Access to reserved address- RW*/
    ureg32 reserved_30:2; /* [31:30] Internal reserved */
} CAN_RIE_Bits;

/* Interrupt class status register 0x810+n*0x1800  */
typedef struct
{
    ureg32 REINT:1;        /* [0:0] Message stored in a receive buffer interrupt - RO */
    ureg32 RxF1F:1;        /* [1:1] Receive FIFO 1 is ful interrupt - RO */
    ureg32 RxF0F:1;        /* [2:2] Receive FIFO 0 is ful interrupt - RO */
    ureg32 RxF1N:1;        /* [3:3] Receive FIFO1 got a new message interrupt  - RO */
    ureg32 RxF0N:1;        /* [4:4] Receive FIFO0 got a new message interrupt  - RO */
    ureg32 RETI:1;         /* [5:5] A receive timeout event interrupt - RO */
    ureg32 TRAQ:1;         /* [6:6] A transmission queue event interrupt - RO */
    ureg32 TRACO:1;        /* [7:7] A transmission control event interrupt - RO */
    ureg32 TEFIFO:1;       /* [8:8] A transmit event FIFO incident interrupt-  RO */
    ureg32 HPE:1;          /* [9:9] A high priority event interrupt - RO */
    ureg32 WATI:1;         /* [10:10] A water mark interrupt has been reached - RO */
    ureg32 ALRT:1;         /* [11:11] An alert interrupt- RO */
    ureg32 MOER:1;         /* [12:12] Module error interrupt - RO */
    ureg32 SAFE:1;         /* [13:13] The safety counter interrupt  RO */
    ureg32 BOFF:1;         /* [14:14] Bus Off Interrupt -  RO */
    ureg32 LOI:1;          /* [15:15] last error interrupt- RO */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} CAN_ISREG_Bits;

/* Interrupt class enable register  */
typedef struct
{
    ureg32 REINTEE:1;      /* [0:0] A message stored in a receive buffer interrupt - RW */
    ureg32 RxF1FE:1;       /* [1:1] Receive FIFO 1 is ful interrupt - RW */
    ureg32 RxF0FE:1;       /* [2:2] Receive FIFO 0 is ful interrupt - RW */
    ureg32 RxF1NE:1;       /* [3:3] Receive FIFO1 got a new message interrupt  -  RW */
    ureg32 RxF0NE:1;       /* [4:4] Receive FIFO0 got a new message interrupt  - RW */
    ureg32 RETIE:1;        /* [5:5] A receive timeout event interrupt-  RW */
    ureg32 TRAQE:1;        /* [6:6] A transmission queue event interrupt- RW */
    ureg32 TRACOE:1;       /* [7:7] A transmission control event interrupt -  RW */
    ureg32 TEFIFOE:1;      /* [8:8] A transmit event FIFO incident interrupt-  RW*/
    ureg32 HPEE:1;         /* [9:9] A high priority event interrupt - RW */
    ureg32 WATIE:1;        /* [10:10] A water mark interrupt has been reached - RW */
    ureg32 ALRTE:1;        /* [11:11] An alert interrupt-  RW */
    ureg32 MOERE:1;        /* [12:12] Module error interrupt - RW */
    ureg32 SAFEE:1;        /* [13:13] The safety counter interrupt - RW */
    ureg32 BOFFE:1;        /* [14:14] Bus Off Interrupt -  RW */
    ureg32 LOIE:1;         /* [15:15] last error interrupt- RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} CAN_ISREG_EN_Bits;

/* Interrupt routing groups1 0x818+n*0x1800 */
typedef struct
{
    ureg32 TEFIFO:4; /* [3:0] A transmit event FIFO incident interrupt - RW */
    ureg32 HPE:4;    /* [7:4] A high priority event interrupt - RW */
    ureg32 WATI:4;   /* [11:8] A water mark interrupt has been reached - RW */
    ureg32 ALRT:4;   /* [15:12] An alert interrupt - RW */
    ureg32 MOER:4;   /* [19:16] Module error interrupt - RW*/
    ureg32 SAFE:4;   /* [23:20] The safety counter interrupt - RW */
    ureg32 BOFF:4;   /* [27:24] Bus Off Interrupt - RW */
    ureg32 LOI:4;    /* [31:28] last error interrupt- RW */
} CAN_GRINT1_Bits;

/* Interrupt routing Groups2 0x81c+n*0x1800 */
typedef struct
{
    ureg32 REINT:4; /* [3:0] A message stored in a receive buffer interrupt -RW */
    ureg32 RXF1F:4; /* [7:4] Receive FIFO 1 is ful interrupt - RW */
    ureg32 RXF0F:4; /* [11:8] Receive FIFO 0 is ful interrupt - RW */
    ureg32 RXF1N:4; /* [15:12] Receive FIFO1 got a new message interrupt  - RW */
    ureg32 RXF0N:4; /* [19:16] Receive FIFO0 got a new message interrupt  - RW */
    ureg32 RETI:4;  /* [23:20] A receive timeout event interrupt - RW */
    ureg32 TRAQ:4;  /* [27:24] A transmission queue event interrupt- RW*/
    ureg32 TRACO:4; /* [31:18] A transmission control event interrupt - RW */
} CAN_GRINT2_Bits;

/* DMU request DMA enable register  0x844+n*0x1800 */
typedef struct
{
    ureg32 DMU_TXRE:1;    /* [0:0] DMU TX FIFO/Queue request to DMA- RW */
    ureg32 DMU_RX0RE:1;   /* [1:1] DMU RX FIFO0 request to DMA- RW */
    ureg32 DMU_RX1RE:1;   /* [2:2] DMU RX FIFO1 request to DMA- RW */
    ureg32 DMU_TXERE:1;   /* [3:3] DMU TX Event FIFO request to DMA- RW*/
    ureg32 reserved_4:28; /* [31:4] Internal reserved */
} CAN_DREN_Bits;

/* DMU gate control 1 register 0x848+n*0x1800 */
typedef struct
{
    ureg32 TXR_CNT:16;  /* [15:0] DMU TXR requirement time waiting count- RW */
    ureg32 RX0R_CNT:16; /* [31:16] DMU  RX0 requirement time waiting count - RW */
} CAN_DGC1_Bits;

/*   DMU gate control 2 register 0x84c+n*0x1800  */
typedef struct
{
    ureg32 RX1R_CNT:16; /* [15:0] DMU RX1R requirement time waiting count- RW */
    ureg32 TXER_CNT:16; /* [31:16] DMU TXER requirement time waiting count - RW */
} CAN_DGC2_Bits;

/*  External time stamp configuration  0x860+n*1800 */
typedef struct
{
    ureg32 TMSTPCNT:16;  /* [15:0] Time stamp count- RO */
    ureg32 TMSTPUNIT:15; /* [30:16] Time stamp unit- RW */
    ureg32 TMSTART:1;    /* [31] Time stamp count start- RW */
} CAN_EXTMSTPCFG_Bits;

/*  DMA request timeout  0xb1c+n*0x1800 */
typedef struct
{
    ureg32 DQTMOT:32; /* [31:0] DMA request timeout time configuration- RW */
} CAN_DQTMOT_Bits;

/*  DMA  timeout  clear  0xb20+n*0x1800 */
typedef struct
{
    ureg32 DTMOC:2;       /* [1:0] DMA timeout clear configuration- RW */
    ureg32 reserved_1:30; /* [31:2]  Internal reserved */
} CAN_DTMOC_Bits;

/*  DMA  Request timeout enable  0xb24+n*0x1800 */
typedef struct
{
    ureg32 DTMEN:2;        /* [0:1] DMA timeout enable configuration- RW */
    ureg32 reserved_2:14;  /* [15:2] Internal reserved */
    ureg32 ERRIJEN:2;      /* [17:16] timeout fault injection */
    ureg32 reserved_18:14; /* [31:18] Internal reserved */
/* Violation: can_register_h_REF_2 */
} CAN_DTMOE_Bits;

/**********************************************************************************************************************
 *                                              CAN Register Definitions
 *********************************************************************************************************************/
/* [7:0]  Module version 0x4800 */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;      /* Unsigned access */
    CAN_ID_Bits B; /* Bitfield access */
} CAN_ID;

/*  Routing Interrupt Enable n Register*/
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    CAN_RIE_Bits B; /* Bitfield access */
} CAN_RIE;

/*   Interrupt signal   Register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_ISREG_Bits B; /* Bitfield access */
} CAN_ISREG;

/*   Interrupt signal enable   Register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    CAN_ISREG_EN_Bits B; /* Bitfield access */
} CAN_ISREG_EN;

/*  Interrupt routing groups1  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_GRINT1_Bits B; /* Bitfield access */
} CAN_GRINT1;

/*  Interrupt routing groups2 */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_GRINT2_Bits B; /* Bitfield access */
} CAN_GRINT2;

/* DMU request enable i register */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_DREN_Bits B; /* Bitfield access */
} CAN_DREN;

/*   DMU gate control 1 register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_DGC1_Bits B; /* Bitfield access */
} CAN_DGC1;

/*   DMU gate control 2 register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_DGC2_Bits B; /* Bitfield access */
} CAN_DGC2;

/*  External time stamp configuration  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    CAN_EXTMSTPCFG_Bits B; /* Bitfield access */
} CAN_EXTMSTPCFG;

/*  DMA request timeout  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_DQTMOT_Bits B; /* Bitfield access */
/* Violation: can_register_h_REF_2 */
} CAN_DQTMOT;

/* #Violation: can_register_h_REF_2 */
/*  DMA  timeout clear */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_DTMOC_Bits B; /* Bitfield access */
/* Violation: can_register_h_REF_2 */
} CAN_DTMOC;

/*  DMU core release */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_DMUCR_Bits B; /* Bitfield access */
} CAN_DMUCR;

/*  DMU  internals Register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_DMUI_Bits B; /* Bitfield access */
} CAN_DMUI;

/*  DMU queueing counter  Register */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_DMUQC_Bits B; /* Bitfield access */
} CAN_DMUQC;

/*  DMU interrupt register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_DMUIR_Bits B; /* Bitfield access */
} CAN_DMUIR;

/*  DMU interrupt enable register */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_DMUIE_Bits B; /* Bitfield access */
} CAN_DMUIE;

/*  Filter element 0   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    CAN_EXTMSG_F0_Bits B; /* Bitfield access */
} CAN_EXTMSG_F0;

/*  Filter element 1   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    sint32 I;             /* Signed access */
    CAN_EXTMSG_F1_Bits B; /* Bitfield access */
} CAN_EXTMSG_F1;

/*  CC control register */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_CCCR_Bits B; /* Bitfield access */
} CAN_CCCR;

/*  Core release register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_CREL_Bits B; /* Bitfield access */
} CAN_CREL;

/*  Data bit timing & prescaler register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_DBTP_Bits B; /* Bitfield access */
} CAN_DBTP;

/*  Error counter register */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    CAN_ECR_Bits B; /* Bitfield access */
} CAN_ECR;

/*  Endian register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_ENDN_Bits B; /* Bitfield access */
} CAN_ENDN;

/*  Global filter configuration */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    CAN_GFC_Bits B; /* Bitfield access */
} CAN_GFC;

/*  High priority message status */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_HPMS_Bits B; /* Bitfield access */
} CAN_HPMS;

/*  Interrupt enable */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;      /* Unsigned access */
    CAN_IE_Bits B; /* Bitfield access */
} CAN_IE;

/*  Interrupt register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;      /* Unsigned access */
    CAN_IR_Bits B; /* Bitfield access */
} CAN_IR;

/*  Interrupt line select register */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    CAN_ILS_Bits B; /* Bitfield access */
} CAN_ILS;

/*  Interrupt line enable register */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    CAN_ILE_Bits B; /* Bitfield access */
} CAN_ILE;

/*  Nominal bit timing & prescaler register */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_NBTP_Bits B; /* Bitfield access */
} CAN_NBTP;

/*  New data 1 */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_NDAT1_Bits B; /* Bitfield access */
} CAN_NDAT1;

/*  New data 2 */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_NDAT2_Bits B; /* Bitfield access */
} CAN_NDAT2;

/*  Protocol status register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    CAN_PSR_Bits B; /* Bitfield access */
} CAN_PSR;

/*  RAM watchdog   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    CAN_RWD_Bits B; /* Bitfield access */
} CAN_RWD;

/*  Rx buffer configuration */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_RX_BC_Bits B; /* Bitfield access */
} CAN_RX_BC;

/*  Rx buffer/FIFO element size configuration   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_RX_ESC_Bits B; /* Bitfield access */
} CAN_RX_ESC;

/*  Rx FIFO 0 acknowledge */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_RX_F0A_Bits B; /* Bitfield access */
} CAN_RX_F0A;

/*  Rx FIFO 0 configuration */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_RX_F0C_Bits B; /* Bitfield access */
} CAN_RX_F0C;

/*  Rx FIFO 0 status  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_RX_F0S_Bits B; /* Bitfield access */
} CAN_RX_F0S;

/*  Rx FIFO 1 acknowledge */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_RX_F1A_Bits B; /* Bitfield access */
} CAN_RX_F1A;

/*  Rx FIFO 1 configuration */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_RX_F1C_Bits B; /* Bitfield access */
} CAN_RX_F1C;

/*  Rx FIFO 1 status */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_RX_F1S_Bits B; /* Bitfield access */
} CAN_RX_F1S;

/*  Standard ID filter configuration  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_SIDFC_Bits B; /* Bitfield access */
} CAN_SIDFC;

/*  Transmitter delay compensation register  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_TDCR_Bits B; /* Bitfield access */
} CAN_TDCR;

/*  Test register */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_TEST_Bits B; /* Bitfield access */
} CAN_TEST;

/*  Timeout counter configuration  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_TOCC_Bits B; /* Bitfield access */
} CAN_TOCC;

/*  Timeout counter value */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_TOCV_Bits B; /* Bitfield access */
} CAN_TOCV;

/*  Timestamp counter configuration  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_TSCC_Bits B; /* Bitfield access */
} CAN_TSCC;

/*  Timestamp counter value  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    CAN_TSCV_Bits B; /* Bitfield access */
} CAN_TSCV;

/*  Tx buffer add request  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_BAR_Bits B; /* Bitfield access */
} CAN_TX_BAR;

/*  Tx buffer configuration  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_TX_BC_Bits B; /* Bitfield access */
} CAN_TX_BC;

/*  Tx buffer cancellation finished*/
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_BCF_Bits B; /* Bitfield access */
} CAN_TX_BCF;

/*  Tx buffer cancellation finished interrupt enable */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    CAN_TX_BCIE_Bits B; /* Bitfield access */
} CAN_TX_BCIE;

/*  Tx buffer cancellation request  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_BCR_Bits B; /* Bitfield access */
} CAN_TX_BCR;

/*  Tx buffer request pending */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_BRP_Bits B; /* Bitfield access */
} CAN_TX_BRP;

/*  Tx buffer transmission interrupt enable  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    CAN_TX_BTIE_Bits B; /* Bitfield access */
} CAN_TX_BTIE;

/*  Tx buffer transmission occurred */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_BTO_Bits B; /* Bitfield access */
} CAN_TX_BTO;

/*  Tx event FIFO acknowledge  */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_EFA_Bits B; /* Bitfield access */
} CAN_TX_EFA;

/*  Tx event FIFO configuration */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_EFC_Bits B; /* Bitfield access */
} CAN_TX_EFC;

/*  Tx event FIFO status */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_EFS_Bits B; /* Bitfield access */
} CAN_TX_EFS;

/*  Tx buffer element size configuration */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_ESC_Bits B; /* Bitfield access */
} CAN_TX_ESC;

/*  Tx FIFO/queue status */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    CAN_TX_FQS_Bits B; /* Bitfield access */
} CAN_TX_FQS;

/*  Extended ID and mask */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_XIDAM_Bits B; /* Bitfield access */
} CAN_XIDAM;

/*  Extended ID filter configuration   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    CAN_XIDFC_Bits B; /* Bitfield access */
} CAN_XIDFC;

/*  Register 0 */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;      /* Unsigned access */
    CAN_R0_Bits B; /* Bitfield access */
} CAN_R0;

/*  Register 1   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;      /* Unsigned access */
    CAN_R1_Bits B; /* Bitfield access */
} CAN_R1;

/* Standard message 0 */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    CAN_STDMSG_S0_Bits B; /* Bitfield access */
} CAN_STDMSG_S0;

/*  Event 0   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    CAN_TXEVENT_E0_Bits B; /* Bitfield access */
} CAN_TXEVENT_E0;

/*  Event 1   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    CAN_TXEVENT_E1_Bits B; /* Bitfield access */
} CAN_TXEVENT_E1;

/*  Transmit buffer 0   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    CAN_TXMSG_T0_Bits B; /* Bitfield access */
} CAN_TXMSG_T0;

/*  Transmit buffer 1   */
typedef union
/* #Violation: can_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    CAN_TXMSG_T1_Bits B; /* Bitfield access */
} CAN_TXMSG_T1;

/**********************************************************************************************************************
 *                                       CAN Register Configuration Structure
 *********************************************************************************************************************/
/*  Standard filter object */
/* #Violation: can_register_h_REF_4 */
typedef volatile struct
{
    CAN_STDMSG_S0 S0; /* 0, Standard filter Message 0*/
} CAN_STDMSG;

/*  Extened filter object */
/* #Violation: can_register_h_REF_4 */
typedef volatile struct
{
    CAN_EXTMSG_F0 F0; /* 0, Extended filter Element 0*/
    CAN_EXTMSG_F1 F1; /* 4, Extended filter 1*/
} CAN_EXTMSG;

/*  Tx event object */
typedef volatile struct
{
    CAN_TXEVENT_E0 E0; /* 0, Tx event 0*/
    CAN_TXEVENT_E1 E1; /* 4, Tx event 1*/
} CAN_TXEVENT;

/*  Transmit buffer object */
typedef volatile struct
{
    CAN_TXMSG_T0 T0; /* 0, Transmit buffer 0*/
    CAN_TXMSG_T1 T1; /* 4, Transmit buffer 1*/
    /* #Violation: can_register_h_REF_3 */
    uint32 DB[16];   /* 8, Data word*/
} CAN_TXMSG;

/*  Receive buffer object */
typedef volatile struct
{
    CAN_R0 R0;     /* 0, Receive buffer 0*/
    CAN_R1 R1;     /* 4, Receive buffer 1*/
    /* #Violation: can_register_h_REF_3 */
    uint32 DB[16]; /* 8, Data word*/
} CAN_RXMSG;

/*  RX object register group*/
typedef volatile struct
{
    CAN_RX_F0C F0C; /* 0A0, Rx FIFO 0 Configuration  */
    CAN_RX_F0S F0S; /* 0A4, Rx FIFO 0 Status  */
    CAN_RX_F0A F0A; /* 0A8, Rx FIFO 0 acknowledge  */
    CAN_RX_BC BC;   /* 0AC, Rx buffer configuration  */
    CAN_RX_F1C F1C; /* 0B0, Rx FIFO 1 configuration  */
    CAN_RX_F1S F1S; /* 0B4, Rx FIFO 1 status  */
    CAN_RX_F1A F1A; /* 0B8, Rx FIFO 1 acknowledge  */
    CAN_RX_ESC ESC; /* 0Bc, Rx buffer/FIFO element size configuration  */
} CAN_RX;
/*  TX object register group */
typedef volatile struct
{
    CAN_TX_BC BC;          /* 0C0, Tx buffer configuration  */
    CAN_TX_FQS FQS;        /* 0C4, Tx FIFO/queue status  */
    CAN_TX_ESC ESC;        /* 0C8, Tx buffer element size configuration  */
    CAN_TX_BRP BRP;        /* 0CC, Tx buffer request pending  */
    CAN_TX_BAR BAR;        /* 0D0, Tx buffer add request  */
    CAN_TX_BCR BCR;        /* 0D4, Tx buffer cancellation request  */
    CAN_TX_BTO BTO;        /* 0D8, Tx buffer Transmission occurred  */
    CAN_TX_BCF BCF;        /* 0DC, Tx buffer cancellation finished  */
    CAN_TX_BTIE BTIE;      /* 0E0, Tx buffer transmission interrupt enable  */
    CAN_TX_BCIE BCIE;      /* 0E4, Tx buffer cancellation finished interrupt enable  */
    uint8 reserved_0E8[8]; /* 0E8, Internal reserved */
    CAN_TX_EFC EFC;        /* 0F0, Tx event FIFO configuration  */
    CAN_TX_EFS EFS;        /* 0F4, Tx event FIFO status  */
    CAN_TX_EFA EFA;        /* 0F8, Tx event FIFO acknowledge  */
} CAN_TX;

typedef volatile struct
{
    CAN_TXMSG DMU_TXElement;             /* 0x200-244, DMU TX element*/
    uint8 reserved_488[56];              /* 0x248-27C,  Internal reserved */
    CAN_RXMSG DMU_RX0Element;            /* 0x280-2c4, DMU RX0 element*/
    uint8 reserved_4c8[56];              /* 0x2c8-2fC,  Internal reserved */
    CAN_RXMSG DMU_RX1Element;            /* 0x300-344, DMU RX1 element*/
    uint8 reserved_548[56];              /* 0x348-37c,  Internal reserved */
    CAN_TXEVENT DMU_TXEventElement;      /* 0x380-384, DMU RX1 element*/
    uint8 reserved_588[56];              /* 0x388-3Bc,  Internal reserved */
    CAN_DMUCR DMUCR;                     /* 0x3C0, DMU core release  */
    CAN_DMUI DMUI;                       /* 0x3C4, DMU  internals */
    CAN_DMUQC DMUQC;                     /* 0x3C8, DMU queueing counter */
    CAN_DMUIR DMUIR;                     /* 0x3CC, DMU interrupt register */
    CAN_DMUIE DMUIE;                     /* 0x3D0, DMU interrupt enable*/
    uint8 reserved_5D4[4];               /* 0x3D4, internal reserved */
    uint8 reserved_5D8[40];              /* 0x3D8-3FC, internal reserved */
    CAN_TXMSG DMU_TXElementDebug;        /* 0x400-444, DMU TX element debug*/
    uint8 reserved_648[56];              /* 0x448-47C, Internal reserved */
    CAN_RXMSG DMU_RX0ElementDebug;       /* 0x480-4CC, DMU RX0 element debug*/
    uint8 reserved_6C8[56];              /* 0x4C8-4FC, Internal reserved */
    CAN_RXMSG DMU_RX1ElementDebug;       /* 0x500-544, DMU RX1 element debug*/
    uint8 reserved_748[56];              /* 0x548-57C, Internal reserved */
    CAN_TXEVENT DMU_TXEventElementDebug; /* 0x580-584, DMU RX1 element debug*/
    uint8 reserved_788[632];             /* 0x588-7FC,  Internal reserved */
} CAN_DMU;

/*  Node object register group*/
/* #Violation: can_register_h_REF_4 */
typedef volatile struct
{
    CAN_CREL CREL;             /* 0x000, Core release register  */
    CAN_ENDN ENDN;             /* 0x004, Endian register  */
    uint8 reserved_08[4];      /* 0x008, Internal reserved */
    CAN_DBTP DBTP;             /* 0x00C, Data bit timing & prescaler register  */
    CAN_TEST TEST;             /* 0x010, Test register  */
    CAN_RWD RWD;               /* 0x014, RAM watchdog  */
    CAN_CCCR CCCR;             /* 0x018, CC control register  */
    CAN_NBTP NBTP;             /* 0x01C, Nominal bit timing & prescaler register  */
    CAN_TSCC TSCC;             /* 0x020, Timestamp counter configuration  */
    CAN_TSCV TSCV;             /* 0x024, Timestamp counter value  */
    CAN_TOCC TOCC;             /* 0x028, Timeout counter configuration  */
    CAN_TOCV TOCV;             /* 0x02C, Timeout counter value  */
    uint8 reserved_030[16];    /* 0x030, Internal reserved */
    CAN_ECR ECR;               /* 0x040, Error counter register  */
    CAN_PSR PSR;               /* 0x044, Protocol status register  */
    CAN_TDCR TDCR;             /* 0x048, Transmitter delay compensation register  */
    uint8 reserved_04c[4];     /* 0x04C, Internal reserved */
    CAN_IR IR;                 /* 0x050, Interrupt register  */
    CAN_IE IE;                 /* 0x054, Interrupt enable  */
    CAN_ILS ILS;               /* 0x058, Interrupt line select register  */
    CAN_ILE ILE;               /* 0x05c, Interrupt line enable register  */
    uint8 reserved_060[32];    /* 0x060-07c, Internal reserved */
    CAN_GFC GFC;               /* 0x080, Global filter configuration  */
    CAN_SIDFC SIDFC;           /* 0x084, Standard ID filter configuration  */
    CAN_XIDFC XIDFC;           /* 0x088, Extended ID filter configuration  */
    uint8 reserved_08c[4];     /* 0x08C, Internal reserved */
    CAN_XIDAM XIDAM;           /* 0x090, Extended ID AND Mask  */
    CAN_HPMS HPMS;             /* 0x094, High priority message status  */
    CAN_NDAT1 NDAT1;           /* 0x098, New data 1  */
    CAN_NDAT2 NDAT2;           /* 0x09C, New data 2  */
    CAN_RX RX;                 /* 0x0A0-0x0BC, Rx register set   */
    CAN_TX TX;                 /* 0x0C0-0x0F8, Tx register set */
    uint8 reserved_0fc[260];   /* 0x0FC-0x1fc, Internal reserved */
    CAN_DMU DMU;               /* 0x0200-0x07fc, DMU object register group register*/
    uint8 reserved_0800[4];    /* 0x0800,  Internal reserved */
    CAN_RIE RIE;               /* 0x804+n*0x1800 Enable interrupt sources after classification merging  */
    uint8 reserved_810[8];     /* 0x808-80c Internal reserved  */
    CAN_ISREG ISREG;           /* 0x810+n*0x1800 Interrupt class status register */
    CAN_ISREG_EN ISREG_EN;     /* 0x814+n*0x1800 Interrupt class enable register */
    CAN_GRINT1 GRINT1;         /* 0x818+n*0x1800 Interrupt routing groups1  */
    CAN_GRINT2 GRINT2;         /* 0x81c+n*0x1800 Interrupt routing groups2  */
    uint8 reserved_820[36];    /* 0x820-0x840   Internal reserved */
    CAN_DREN DREN;             /* 0x844+n*0x1800 \DMU request DMA enable register  */
    CAN_DGC1 DGC1;             /* 0x848+n*0x1800 \DMU gate control 1 register  */
    CAN_DGC2 DGC2;             /* 0x84c+n*0x1800 \DMU gate control 2 register  */
    uint8 reserved_850[16];    /* 0x850-0x85c Internal reserved  */
    CAN_EXTMSTPCFG EXTMSTPCFG; /* 0x860+n*1800 \external time stamp configuration  */
    uint8 reserved_864[3996];  /* 0x864-0x17fc  Internal reserved   */
} CAN_NODE;

/*  CAN module object group register */
/* #Violation: can_register_h_REF_2 */
typedef volatile struct
{
    CAN_NODE N[3];              /* 0x0000-0x17fc,0x1800-0x2ffc,0x3000-0x47fc, IP independent register */
    CAN_ID ID;                  /* Module version 0x4800  */
    uint8 reserved_4804[14332]; /* Internal reserved  0x4804-0x7ffc */
    uint32 RAM[8192];           /* Embedded SRAM for messages, 0x8000-0xfffc,*/
} CAN_MODULE;

#endif /* CAN_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

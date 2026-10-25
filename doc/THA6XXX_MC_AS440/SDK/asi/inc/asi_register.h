/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    asi_register.h
 * Author:      00101
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of ASI module registers.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Coding Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #asi_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by
*               code review.
*
*/

#ifndef ASI_REGISTER_H_
#define ASI_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        ASI Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* LIN Control Register 1 */
typedef volatile struct 
{
    ureg32 INITREQ:1;        /* [0:0] Initialization Mode Request - RW */
    ureg32 SLEEP:1;          /* [1:1] Sleep Mode Request - RW */
    ureg32 RBLM:1;           /* [2:2] Receiver Buffer Locked Mode - RW */
    ureg32 SSBL:1;           /* [3:3] Slave Mode Sync Break Length - RW */
    ureg32 MME:1;            /* [4:4] Master Mode Enable - RW */
    ureg32 LBKM:1;           /* [5:5] Loop Back Mode - RW */
    ureg32 reserved_6:1;     /* [6:6] Internal reversed */
    ureg32 BF:1;             /* [7:7] Bypass Filter - RW */
    ureg32 MBL:4;            /* [8:11] Master Break Length - RW */
    ureg32 AUTOWU:1;         /* [12:12] Automatic Wake-Up - RW */
    ureg32 LASE:1;           /* [13:13] LIN Autosynchronization Enable - RW */
    ureg32 CFD:1;            /* [14:14] Checksum Field Disable - RW  */
    ureg32 CCD:1;            /* [15:15] Checksum Calculation Disable - RW */
    ureg32 NLSE:1;           /* [16:16] LIN State Capture Enable on Bit Error - RW */
    ureg32 reserved_17 :15;  /* [31:17] internal reversed */
} ASI_LINCR1_Bits;

/* LIN Interrupt enable register */
typedef volatile struct
{
    ureg32 HRIE:1;           /* [0:0] Header Received Interrupt Enable - RW */
    ureg32 DTIE:1;           /* [1:1] Data Transmitted Interrupt Enable - RW */
    ureg32 DRIE:1;           /* [2:2] Data Reception Complete Interrupt Enable - RW */
    ureg32 TOIE:1;           /* [3:3] Timeout Interrupt Enable - RW */
    ureg32 reserved_4:1;     /* [4:4] internal reversed */
    ureg32 WUIE:1;           /* [5:5] Wakeup Interrupt Enable - RW */
    ureg32 LSIE:1;           /* [6:6] LIN State Interrupt Enable - RW */
    ureg32 BOIE:1;           /* [7:7] Buffer Overrun Interrupt Enable - RW */
    ureg32 FEIE:1;           /* [8:8] Frame Error Interrupt Enable - RW */
    ureg32 reserved_9:2;     /* [10:9] Internal reserved */
    ureg32 HEIE:1;           /* [11:11] Header Error Interrupt Enable - RW */
    ureg32 CEIE:1;           /* [12:12] Checksum Error Interrupt Enable - RW */
    ureg32 BEIE:1;           /* [13:13] Bit Error Interrupt Enable - RW */
    ureg32 OCIE:1;           /* [14:14] Output Compare Interrupt Enable - RW */
    ureg32 SZIE:1;           /* [15:15] Stuck at Zero Interrupt Enable - RW */
    ureg32 reserved_16:16;   /* [31:16] Internal reserved */
} ASI_LINIER_Bits;

/* LIN Status Register */
typedef volatile struct
{
    ureg32 HRF:1;            /* [0:0] Header Received Flag - W1C */
    ureg32 DTF:1;            /* [1:1] Data Transmission Completed Flag - W1C */
    ureg32 DRF:1;            /* [2:2] Data Reception Completed Flag - W1C */
    ureg32 reserved_3:2;     /* [4:3] Internal reserved */
    ureg32 WUF:1;            /* [5:5] Wakeup Flag - W1C */
    ureg32 RDI:1;            /* [6:6] Receiver Data Input - RO */
    ureg32 RXBUSY:1;         /* [7:7] Receiver Busy Flag - RO */
    ureg32 DRBNE:1;          /* [8:8] Data Reception Buffer Not Empty Flag - W1C */
    ureg32 RMB:1;            /* [9:9] Release Message Buffer - W1C */
    ureg32 reserved_10:2;    /* [11:10] Internal reserved */
    ureg32 LINS:4;           /* [15:12] LIN State - RO */
    ureg32 RDC:3;            /* [18:16] Receive Data Byte Count - RO */
    ureg32 AUTOSYNC_COMP:1;  /* [19:19] Auto Synchronization Complete - W1C */
    ureg32 reserved_20:12;   /* [31:20] Internal reserved */
} ASI_LINSR_Bits;

/* LIN Error Status Register */
typedef volatile struct
{
    ureg32 NF:1;             /* [0:0] Noise Flag - W1C */
    ureg32 reserved_1:6;     /* [6:1] Internal reserved */
    ureg32 BOF:1;            /* [7:7] Buffer Overrun Flag - W1C */
    ureg32 FEF:1;            /* [8:8] Framing Error Flag - W1C */
    ureg32 IPDEF:1;          /* [9:9] ID Parity Error Flag - W1C */
    ureg32 SDEF:1;           /* [10:10] Break Delimiter Error Flag - W1C */
    ureg32 SFEF:1;           /* [11:11] Sync Field Error Flag - W1C */
    ureg32 CEF:1;            /* [12:12] Checksum Error Flag - W1C */
    ureg32 BEF:1;            /* [13:13] Bit Error Flag - W1C */
    ureg32 OCF:1;            /* [14:14] Output Compare Flag - W1C */
    ureg32 SZF:1;            /* [15:15] Stuck at Zero Flag - W1C */
    ureg32 reserved_16:16;   /* [31:16] Internal reserved */
} ASI_LINESR_Bits;                    

/* UART Mode Control Register */
typedef volatile struct
{
    ureg32 UART:1;           /* [0:0] UART Mode Enable - RW */
    ureg32 WL0:1;            /* [1:1] Word Length in UART Mode - RW */
    ureg32 PCE:1;            /* [2:2] Parity Control Enable - RW */
    ureg32 PC0:1;            /* [3:3] Parity Control - RW */
    ureg32 TxEn:1;           /* [4:4] Transmitter Enable - RW */
    ureg32 RxEn:1;           /* [5:5] Receiver Enable - RW */
    ureg32 PC1:1;            /* [6:6] Parity Control - RW */
    ureg32 WL1:1;            /* [7:7] Word Length in UART Mode - RW */
    ureg32 TFBM:1;           /* [8:8] Tx FIFO / Buffer Mode - RW */
    ureg32 RFBM:1;           /* [9:9] Rx FIFO / Buffer Mode - RW */
    ureg32 RDFL_RFC:3;       /* [12:10] Receiver Data Field Length / Rx FIFO Counter - RW */
    ureg32 TDFL_TFC:3;       /* [15:13] Transmitter Data Field Length / Tx FIFO Counter - RW */
    ureg32 WLS:1;            /* [16:16] Special Word Length in UART Mode - RW */
    ureg32 SBUR:2;           /* [18:17] Number of Stop Bits in UART Reception Mode - RW */
    ureg32 DTU:1;            /* [19:19] Disable Timeout in UART mode - RW  */
    ureg32 NEF:3;            /* [22:20] Number of Expected Frames - RW */
    ureg32 ROSE:1;           /* [23:23] Reduced Oversampling Enable - RW */
    ureg32 OSR:4;            /* [27:24] Oversampling Rate - RW */
    ureg32 CSP:3;            /* [30:28] Configurable Sample Point - RW */
    ureg32 MIS:1;            /* [31:31] Monitor Idle State - RW */
} ASI_UARTCR_Bits;

/* UART Mode Status Register */
typedef volatile struct
{
    ureg32 NF:1;             /* [0:0] Noise Flag - W1C */
    ureg32 DTF_TFF:1;        /* [1:1] Data Transmission Completed Flag / Tx FIFO Full Flag - W1C */
    ureg32 DRF_RFE:1;        /* [2:2] Data Reception Completed Flag / Rx FIFO Empty Flag - W1C */
    ureg32 TO:1;             /* [3:3] Timeout - W1C */
    ureg32 RFNE:1;           /* [4:4] Receive FIFO Not Empty - RO */
    ureg32 WUF:1;            /* [5:5] Wake Up Flag - W1C */
    ureg32 RDI:1;            /* [6:6] Receiver Data Input - RO */
    ureg32 BOF:1;            /* [7:7] FIFO/Buffer Overrun Flag - W1C */
    ureg32 FEF:1;            /* [8:8] Framing Error Flag - W1C */
    ureg32 RMB:1;            /* [9:9] Release Message Buffer - W1C */
    ureg32 PE:4;             /* [13:10] Parity Error Flag - W1C */
    ureg32 OCF:1;            /* [14:14] Output Compare Flag - W1C */
    ureg32 SZF:1;            /* [15:15] Stuck at Zero Flag - W1C */
    ureg32 reserved_16:16;   /* [31:16] Internal reserved - W1C */
} ASI_UARTSR_Bits;

/* LIN Time-Out Control Status Register */
typedef volatile struct
{
    ureg32 CNT:8;            /* [7:0] Counter Value - RW */
    ureg32 TOCE:1;           /* [8:8] Timeout Counter Enable - RW */
    ureg32 IOT:1;            /* [9:9] Idle on Timeout - RW */
    ureg32 MODE:1;           /* [10:10] Timeout Counter Mode - RW */
    ureg32 reserved_11:21;   /* [31:11] Internal reserved */
} ASI_LINTCSR_Bits;

/* LIN Output Compare Register */
typedef volatile struct
{
    ureg32 OC1:8;            /* [7:0] Output compare value 1 - RW */
    ureg32 OC2:8;            /* [15:8] Output compare value 2 - RW */
    ureg32 reserved_16:16;   /* [31:16] Internal reserved */
} ASI_LINOCR_Bits;

/* LIN Time-Out Control Register */
typedef volatile struct
{
    ureg32 HTO:7;            /* [6:0] Header Timeout Value - RW */
    ureg32 reserved_7:1;     /* [7:7] Internal reserved */
    ureg32 RTO:4;            /* [11:8] Response Timeout Value - RW */
    ureg32 reserved_12:20;   /* [31:12] Internal reserved */
} ASI_LINTOCR_Bits;

/* LIN Fractional Baud Rate Register */
typedef volatile struct
{
    ureg32 FBR:4;            /* [3:0] Fractional Baud Rate - RW */
    ureg32 reserved_4:28;    /* [31:4] Internal reserved */
} ASI_LINFBRR_Bits;

/* LIN Integer Baud Rate Register */
typedef volatile struct
{
    ureg32 IBR:20;           /* [19:0] Integer Baud Rate - RW */
    ureg32 reserved_20:12;   /* [31:20] Internal reserved */
} ASI_LINIBRR_Bits;

/* LIN Checksum Field Register */
typedef volatile struct
{
    ureg32 CF:8;             /* [7:0] Checksum Bits - RW */
    ureg32 reserved_8:24;    /* [31:8] Internal reserved */
} ASI_LINCFR_Bits;

/* LIN Control Register 2 */
typedef volatile struct
{
    ureg32 reserved_0:8;     /* [7:0] Internal reserved */
    ureg32 HTRQ:1;           /* [8:8] Header Transmission Request - RW */
    ureg32 ABRQ:1;           /* [9:9] Abort Request - RW */
    ureg32 DTRQ:1;           /* [10:10] Data Transmission Request - RW */
    ureg32 DDRQ:1;           /* [11:11] Data Discard Request - RW */
    ureg32 WURQ:1;           /* [12:12] Wakeup Generate Request - RW */
    ureg32 IOPE:1;           /* [13:13] Idle on Identifier Parity Error: - RW */
    ureg32 IOBE:1;           /* [14:14] Idle on Bit Error - RW */
    ureg32 TBDE:1;           /* [15:15] Two-Bit Delimiter Enable - RW */
    ureg32 reserved_16:16;   /* [31:16] Internal reserved */
} ASI_LINCR2_Bits;

/* Buffer Identifier Register */
typedef volatile struct
{
    ureg32 ID:6;             /* [5:0] Identifier - RW */
    ureg32 reserved_6:2;     /* [7:6] Internal reserved */
    ureg32 CCS:1;            /* [8:8] Classic Checksum - RW */
    ureg32 DIR:1;            /* [9:9] The direction of the data field - RW */
    ureg32 DFL:3;            /* [12:10] Data Field Length - RW */
    ureg32 reserved_13:19;   /* [31:13] Internal reserved */
} ASI_BIDR_Bits;

/* Identifier Filter Enable Register */
typedef volatile struct
{
    ureg32 FACT:16;          /* [15:0] Filter Active - RW */
    ureg32 reserved_16:16;   /* [31:16] Internal reserved */
} ASI_IFER_Bits;

/* Identifier Filter Match Index */
typedef volatile struct
{
    ureg32 IFMI:5;           /* [4:0] Filter Match Index - RO */
    ureg32 reserved_5:27;    /* [31:5] Internal reserved */
} ASI_IFMI_Bits;

/* Identifier Filter Mode Register */
typedef volatile struct
{
    ureg32 IFM:8;            /* [7:0] Filter Mode - RW */
    ureg32 reserved_8:24;    /* [31:8] Internal reserved */
} ASI_IFMR_Bits;

/* Identifier Filter Control Register */
typedef volatile struct
{
    ureg32 ID:6;             /* [5:0] Identifier - RW */
    ureg32 reserved_2:2;     /* [7:6] Internal reserved */
    ureg32 CCS:1;            /* [8:8] Classic Checksum - RW */
    ureg32 DIR:1;            /* [9:9] the direction of the data field - RW */
    ureg32 DFL:3;            /* [12:10] Data Field Length - RW */
    ureg32 reserved_13:19;   /* [31:13] Internal reserved */
} ASI_IFCR_Bits;

/* Global Control Register */
typedef volatile struct
{
    ureg32 SR:1;             /* [0:0] Soft Reset - RW */
    ureg32 STOP:1;           /* [1:1] One or Two Stop Bit Configuration - RW */
    ureg32 RDLIS:1;          /* [2:2] Received Data Level Inversion Selection - RW */
    ureg32 TDLIS:1;          /* [3:3] Transmit Data Level Inversion Selection - RW */
    ureg32 RDFBM:1;          /* [4:4] Receive Data First Bit MSB - RW */
    ureg32 TDFBM:1;          /* [5:5] Transmit Data First Bit MSB - RW */
    ureg32 reserved_6:26;    /* [31:6] Internal reserved */
} ASI_GCR_Bits;

/* UART Preset Timeout Register */
typedef volatile struct
{
    ureg32 PTO:12;           /* [11:0] Preset Timeout - RW */
    ureg32 reserved_12:20;   /* [31:12] Internal reserved */
} ASI_UARTPTO_Bits;

/* UART Current Timeout Register */
typedef volatile struct
{
    ureg32 CTO:12;           /* [11:0] Preset Timeout - RO */
    ureg32 reserved_12:20;   /* [31:12] Internal reserved */
} ASI_UARTCTO_Bits;

/* DMA Tx Enable Register */
typedef volatile struct
{
    ureg32 DTE0:1;           /* [0:0] DMA Tx Channel n Enable - RW */
    ureg32 reserved_1:31;    /* [31:1] Internal reserved */
} ASI_DMATXE_Bits;

/* DMA Rx Enable Register */
typedef volatile struct
{
    ureg32 DRE0:1;           /* [0:0] DMA Rx Channel n Enable - RW */
    ureg32 reserved_1:31;    /* [31:1] Internal reserved */
} ASI_DMARXE_Bits;

/* Stop mode request Register */
typedef volatile struct
{
    ureg32 STOPREQ:1;         /* [0:0] Stop Request - RW */
    ureg32 reserved_1:31;     /* [31:1] Internal reserved */
} ASI_SRR_Bits;

/* DMA request Register */
typedef volatile struct
{
    ureg32 DMARXREQ:1;        /* [0:0] DMA TX Channel 0 Request - RW */
    ureg32 reserved_1:15;     /* [15:1] Internal reserved */
    ureg32 DMATXREQ:1;        /* [16:16] DMA RX Channel 0 Request - RW */
    ureg32 reserved_17:15;    /* [31:17] Internal reserved */
} ASI_DRR_Bits;

/* Trigger request Register */
typedef volatile struct
{
    ureg32 TRIG:1;           /* [0:0] Header Transmission Trigger - RW */
    ureg32 reserved_1:31;    /* [31:1] Internal reserved */
} ASI_TRIGGER_Bits;

/* Collision 0 request Register */
typedef volatile struct
{
    ureg32 DCENT:1;           /* [0:0] Detection  Collision Enable - RW */
    ureg32 DCS:8;             /* [8:1] Detection  Collision Sample - RW */
    ureg32 DCTH:23;           /* [31:9] Detection  Collision Threshold - RW */
} ASI_CR0_Bits;

/* Collision 1 request Register */
typedef volatile struct
{
    ureg32 DFISJ:24;          /* [23:0] Data Frame Idle Sampling Judgment Interval - RW */
    ureg32 CODCOTH:8;         /* [31:24] Collision Detection Comparison Threshold Value - RW */
} ASI_CR1_Bits;

/* ASI Status Register */
typedef volatile struct
{
    ureg32 AAINT:1;          /* [0:0] ASI all interrupts - W1C */
    ureg32 CDINT:1;          /* [1:1] Collision detection interrupt - W1C */
    ureg32 CDINT0:1;         /* [2:2] Collision detection interrupt 0 - W1C */
    ureg32 CDINT1:1;         /* [3:3] Collision detection interrupt 1 - W1C */
    ureg32 STOPACK:1;        /* [4:4] Ipg_stop_ack - W1C */
    ureg32 CDINT0CI:1;       /* [5:5] CDINT0 Clear indication - RO */
    ureg32 CDINT1CI:1;       /* [6:6] CDINT1 Clear indication - RO */
    ureg32 reserved_7:25;    /* [31:7] Internal reserved */
} ASI_ASTR_Bits;

/* ASI Interrupt Enabled Register */
typedef volatile struct
{
    ureg32 AAINTEN:1;        /* [0:0] ASI all interrupts Enabled - RW */
    ureg32 reserved_1:31;    /* [31:1] Internal reserved */
} ASI_AINTENR_Bits;

/* APB Bus Error Mask Register */
typedef volatile struct
{
    ureg32 APBEMP:1;         /* [0:0] ASI DMA Reception Bytes - RW */
    ureg32 reserved_1:31;    /* [31:1] Internal reserved */
} ASI_APBEMR_Bits;
/**********************************************************************************************************************
 *                                             ASI Register Definitions
 *********************************************************************************************************************/
/* LIN Control Register 1 */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINCR1_Bits B;        /* Bit field access */
} ASI_LINCR1;

/* LIN Interrupt enable register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINIER_Bits B;        /* Bit field access */
} ASI_LINIER;

/* LIN Status Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINSR_Bits B;         /* Bit field access */
} ASI_LINSR;

/* LIN Error Status Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINESR_Bits B;        /* Bit field access */
} ASI_LINESR;

/* UART Mode Control Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_UARTCR_Bits B;        /* Bit field access */
} ASI_UARTCR;

/* UART Mode Status Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_UARTSR_Bits B;        /* Bit field access */
} ASI_UARTSR;

/* LIN Time-Out Control Status Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINTCSR_Bits B;       /* Bit field access */
} ASI_LINTCSR;

/* LIN Output Compare Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINOCR_Bits B;        /* Bit field access */
} ASI_LINOCR;

/* LIN Time-Out Control Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINTOCR_Bits B;       /* Bit field access */
} ASI_LINTOCR;

/* LIN LIN Fractional Baud Rate Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINFBRR_Bits B;       /* Bit field access */
} ASI_LINFBRR;

/* LIN Time-Out Control Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINIBRR_Bits B;       /* Bit field access */
} ASI_LINIBRR;

/* LIN Checksum Field Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINCFR_Bits B;        /* Bit field access */
} ASI_LINCFR;

/* LIN Control Register 2 */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_LINCR2_Bits B;        /* Bit field access */
} ASI_LINCR2;

/* Buffer Identifier Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_BIDR_Bits B;          /* Bit field access */
} ASI_BIDR;

/* Buffer Data Register Least Significant */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    uint8 B[4];               /* Unsigned Byte access */
    uint16 S[2];              /* Unsigned Short access */
} ASI_BDRL;

/* Buffer Data Register Most Significant */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    uint8 B[4];               /* Unsigned Byte access */
    uint16 S[2];              /* Unsigned Short access */
} ASI_BDRM;

/* Identifier Filter Enable Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_IFER_Bits B;          /* Bit field access */
} ASI_IFER;

/* Identifier Filter Match Index */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_IFMI_Bits B;          /* Bit field access */
} ASI_IFMI;

/* Identifier Filter Mode Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_IFMR_Bits B;          /* Bit field access */
} ASI_IFMR;

/* Identifier Filter Control Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_IFCR_Bits B;          /* Bit field access */
} ASI_IFCR;

/* Global Control Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_GCR_Bits B;           /* Bit field access */
} ASI_GCR;

/* UART Preset Timeout Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_UARTPTO_Bits B;       /* Bit field access */
} ASI_UARTPTO;

/* UART Current Timeout Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_UARTCTO_Bits B;       /* Bit field access */
} ASI_UARTCTO;

/* DMA Tx Enable Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_DMATXE_Bits B;        /* Bit field access */
} ASI_DMATXE;

/* DMA Rx Enable Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_DMARXE_Bits B;        /* Bit field access */
} ASI_DMARXE;

/* Stop mode Request Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_SRR_Bits B;           /* Bit field access */
} ASI_SRR;

/* DMA request Register Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_DRR_Bits B;           /* Bit field access */
} ASI_DRR;

/* Trigger Register */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_TRIGGER_Bits B;       /* Bit field access */
} ASI_TRIGGER;

/* Collision 0 Register Register (THA6412 only) */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_CR0_Bits B;           /* Bit field access */
} ASI_CR0;

/* Collision 1 Register Register (THA6412 only) */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_CR1_Bits B;           /* Bit field access */
} ASI_CR1;

/* ASI Status Register (THA6412 only) */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_ASTR_Bits B;          /* Bit field access */
} ASI_ASTR;

/* ASI Interrupt Enabled Register (THA6412 only) */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_AINTENR_Bits B;       /* Bit field access */
} ASI_AINTENR;

/* APB Bus Error Mask Register (THA6412 only) */
typedef union
/* #Violation: asi_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ASI_APBEMR_Bits B;        /* Bit field access */
} ASI_APBEMR;

/**********************************************************************************************************************
 *                                        ASI Register Configuration Structure
 *********************************************************************************************************************/
/* ASI_MODULE modes definition. */
typedef volatile struct
{
    ASI_LINCR1          LINCR1;          /* 0x0 LIN Control Register 1 */
    ASI_LINIER          LINIER;          /* 0x4 LIN Interrupt enable register */
    ASI_LINSR           LINSR;           /* 0x8 LIN Status Register */
    ASI_LINESR          LINESR;          /* 0xC LIN Error Status Register */
    ASI_UARTCR          UARTCR;          /* 0x10 UART Mode Control Register */
    ASI_UARTSR          UARTSR;          /* 0x14 UART Mode Status Register */
    ASI_LINTCSR         LINTCSR;         /* 0x18 LIN Time-Out Control Status Register */
    ASI_LINOCR          LINOCR;          /* 0x1C LIN Output Compare Register */
    ASI_LINTOCR         LINTOCR;         /* 0x20 LIN Time-Out Control Register */
    ASI_LINFBRR         LINFBRR;         /* 0x24 LIN Fractional Baud Rate Register */
    ASI_LINIBRR         LINIBRR;         /* 0x28 LIN Integer Baud Rate Register */
    ASI_LINCFR          LINCFR;          /* 0x2C LIN Checksum Field Register */
    ASI_LINCR2          LINCR2;          /* 0x30 LIN Control Register 2 */
    ASI_BIDR            BIDR;            /* 0x34 Buffer Identifier Register */
    ASI_BDRL            BDRL;            /* 0x38 Buffer Data Register Least Significant */
    ASI_BDRM            BDRM;            /* 0x3C Buffer Data Register Most Significant */
    ASI_IFER            IFER;            /* 0x40 Identifier Filter Enable Register */
    ASI_IFMI            IFMI;            /* 0x44 Identifier Filter Match Index */
    ASI_IFMR            IFMR;            /* 0x48 Identifier Filter Mode Register */
    ASI_IFCR            IFCR[16];        /* 0x4C Identifier Filter Control Register */
    ASI_GCR             GCR;             /* 0x8C Global Control Register */
    ASI_UARTPTO         UARTPTO;         /* 0x90 UART Preset Timeout Register */
    ASI_UARTCTO         UARTCTO;         /* 0x94 UART Current Timeout Register */
    ASI_DMATXE          DMATXE;          /* 0x98 DMA Tx Enable Register */
    ASI_DMARXE          DMARXE;          /* 0x9C DMA Rx Enable Register */
    ASI_SRR             SRR;             /* 0xA0 Stop mode request Register */
    ASI_DRR             DRR;             /* 0xA4 DMA request Register */
    ASI_TRIGGER         TR;              /* 0xA8 Trigger Register */
    ASI_CR0             CR0;             /* 0xAC Collision 0 Register (THA6206 not supported) */
    ASI_CR1             CR1;             /* 0xB0 Collision 1 Register (THA6206 not supported) */
    ASI_ASTR            ASTR;            /* 0xB4 ASI Status Register (THA6206 not supported) */
    ASI_AINTENR         AINTENR;         /* 0xB8 ASI Interrupt Enabled Register */
    ASI_APBEMR          APBEMR;          /* 0xBC APB Bus Error Mask Register */
} ASI_MODULE;

#endif /* ASI_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/


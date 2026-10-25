/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    msc_register.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of MSC module registers.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#msc_register_h_REF_1:MISRAC2012-Rule-19.2; 
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
*#msc_register_h_REF_2:MISRAC2012-Dir-4.8;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#msc_register_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity;
*
*#msc_register_h_REF_4:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#msc_register_h_REF_5:CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*/

#ifndef MSC_REGISTER_H_
#define MSC_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        MSC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Module Identification Register */
typedef struct
{
    ureg32 MREV:8;  /* [7:0] Module Revision Number - RW */
    ureg32 MTYPE:8; /* [15:8] Module Type - RW */
    ureg32 MNUM:16; /* [31:16] Module Number Value - RW */
} MSC_MID_Bits;

/* Fractional Divider Register */
typedef struct
{
    ureg32 STEP:10;       /* [9:0] Step Value - RW */
    ureg32 ECEN:1;        /* [10:10] Enable valid signal - RW */
    ureg32 reserved_11:3; /* [13:11] Internal reserved */
    ureg32 DIVM:2;        /* [15:14] Divider Mode - RW */
    ureg32 RESULT:10;     /* [25:16] Result Value - RW */
    ureg32 reserved_26:4; /* [29:26] Internal reserved */
    ureg32 ENHCC:1;       /* [30:30] Enable Hardware Clock Control - RW */
    ureg32 CLKDIS:1;      /* [31:31] Disable Clock - RW */
} MSC_FDIV_Bits;

/*Upstream Status Register */
typedef struct
{
    ureg32 UCFT:1;         /* [0:0] Upstream Channel Frame Type - RW */
    ureg32 UCRR:3;         /* [3:1] Upstream Channel Receiving Rate - RW */
    ureg32 PCON:1;         /* [4:4] Parity Control - RW */
    ureg32 SRDCON:1;       /* [5:5] Service Request Delay Control - RW */
    ureg32 reserved_6:10;  /* [15:6] Internal reserved */
    ureg32 UCNT:5;         /* [20:16] Upstream Counter - RH */
    ureg32 reserved_21:11; /* [31:21] Internal reserved */
} MSC_UPSTS_Bits;

/* Downstream Control Register */
typedef struct
{
    ureg32 TRM:1;         /* [0:0] Transmission Mode - RW */
    ureg32 COMP:1;        /* [1:1] Command Pending - RW */
    ureg32 DATP:1;        /* [2:2] Data Pending - RW */
    ureg32 NBDFL:5;       /* [7:3] Number of SRL Bits Shifted at Data Frames - RW */
    ureg32 NBDFH:5;       /* [12:8] Number of SRH Bits Shifted at Data Frames - RW */
    ureg32 SELSRL:1;      /* [13:13] Enable SRL Active Phase Selection Bit - RW */
    ureg32 SELSRH:1;      /* [14:14] Enable SRH Active Phase Selection Bit - RW */
    ureg32 DDIS:1;        /* [15:15] Downstream Disable - RH */
    ureg32 NBCF:6;        /* [21:16] Number of Bits Shifted at Command Frames - RW */
    ureg32 reserved_22:2; /* [23:22] Internal reserved */
    ureg32 PPLD:5;        /* [28:24] Passive Phase Length at Data Frames - RW */
    ureg32 reserved_29:3; /* [31:29] Internal reserved */
} MSC_DCON_Bits;

/* Downstream Status Register */
typedef struct
{
    ureg32 PTCNT:4;       /* [3:0] Passive Time Frame Counter - RW */
    ureg32 reserved_4:4;  /* [7:4] Internal reserved */
    ureg32 NUMPT:4;       /* [11:8] Number Of Passive Time Frames - RW */
    ureg32 reserved_12:4; /* [15:12] Internal reserved */
    ureg32 DCNT:8;        /* [23:16] Downstream Counter - RW */
    ureg32 DATFA:1;       /* [24:24] Data Frame Active - RW */
    ureg32 COMFA:1;       /* [25:25] Command Frame Active - RW */
    ureg32 reserved_26:6; /* [31:26] Internal reserved */
} MSC_DSTS_Bits;

/* Downstream Data Register */
typedef struct
{
    ureg32 DDL:16; /* [15:0] Downstream Data for SRL Shift Register - RW */
    ureg32 DDH:16; /* [31:16] Downstream Data for SRH Shift Register - RW */
} MSC_DD_Bits;

/* Downstream Command Register */
typedef struct
{
    ureg32 DCL:16; /* [15:0] Downstream Command for SRL Shift Register - RW */
    ureg32 DCH:16; /* [31:16] Downstream Command for SRH Shift Register - RW */
} MSC_DC_Bits;

/* Downstream Select Data Source Low Register */
typedef struct
{
    ureg32 SSL0:2;  /* [1:0] Select Source for SRL - RW */
    ureg32 SSL1:2;  /* [3:2] Select Source for SRL - RW */
    ureg32 SSL2:2;  /* [5:4] Select Source for SRL - RW */
    ureg32 SSL3:2;  /* [7:6] Select Source for SRL - RW */
    ureg32 SSL4:2;  /* [9:8] Select Source for SRL - RW */
    ureg32 SSL5:2;  /* [11:10] Select Source for SRL - RW */
    ureg32 SSL6:2;  /* [13:12] Select Source for SRL - RW */
    ureg32 SSL7:2;  /* [15:14] Select Source for SRL - RW */
    ureg32 SSL8:2;  /* [17:16] Select Source for SRL - RW */
    ureg32 SSL9:2;  /* [19:18] Select Source for SRL - RW */
    ureg32 SSL10:2; /* [21:20] Select Source for SRL - RW */
    ureg32 SSL11:2; /* [23:22] Select Source for SRL - RW */
    ureg32 SSL12:2; /* [25:24] Select Source for SRL - RW */
    ureg32 SSL13:2; /* [27:26] Select Source for SRL - RW */
    ureg32 SSL14:2; /* [29:28] Select Source for SRL - RW */
    ureg32 SSL15:2; /* [31:30] Select Source for SRL - RW */
} MSC_DDSL_Bits;

/* Downstream Select Data Source High Register */
typedef struct
{
    ureg32 SSH0:2;  /* [1:0] Select Source for SRH - RW */
    ureg32 SSH1:2;  /* [3:2] Select Source for SRH - RW */
    ureg32 SSH2:2;  /* [5:4] Select Source for SRH - RW */
    ureg32 SSH3:2;  /* [7:6] Select Source for SRH - RW */
    ureg32 SSH4:2;  /* [9:8] Select Source for SRH - RW */
    ureg32 SSH5:2;  /* [11:10] Select Source for SRH - RW */
    ureg32 SSH6:2;  /* [13:12] Select Source for SRH - RW */
    ureg32 SSH7:2;  /* [15:14] Select Source for SRH - RW */
    ureg32 SSH8:2;  /* [17:16] Select Source for SRH - RW */
    ureg32 SSH9:2;  /* [19:18] Select Source for SRH - RW */
    ureg32 SSH10:2; /* [21:20] Select Source for SRH - RW */
    ureg32 SSH11:2; /* [23:22] Select Source for SRH - RW */
    ureg32 SSH12:2; /* [25:24] Select Source for SRH - RW */
    ureg32 SSH13:2; /* [27:26] Select Source for SRH - RW */
    ureg32 SSH14:2; /* [29:28] Select Source for SRH - RW */
    ureg32 SSH15:2; /* [31:30] Select Source for SRH - RW */
} MSC_DDSH_Bits;

/* Emergency Stop Register */
typedef struct
{
    ureg32 ENL0:1;  /* [0:0] Emergency Stop Enable for Bit 0 in SRL - RW */
    ureg32 ENL1:1;  /* [1:1] Emergency Stop Enable for Bit 1 in SRL - RW */
    ureg32 ENL2:1;  /* [2:2] Emergency Stop Enable for Bit 2 in SRL - RW */
    ureg32 ENL3:1;  /* [3:3] Emergency Stop Enable for Bit 3 in SRL - RW */
    ureg32 ENL4:1;  /* [4:4] Emergency Stop Enable for Bit 4 in SRL - RW */
    ureg32 ENL5:1;  /* [5:5] Emergency Stop Enable for Bit 5 in SRL - RW */
    ureg32 ENL6:1;  /* [6:6] Emergency Stop Enable for Bit 6 in SRL - RW */
    ureg32 ENL7:1;  /* [7:7] Emergency Stop Enable for Bit 7 in SRL - RW */
    ureg32 ENL8:1;  /* [8:8] Emergency Stop Enable for Bit 8 in SRL - RW */
    ureg32 ENL9:1;  /* [9:9] Emergency Stop Enable for Bit 9 in SRL - RW */
    ureg32 ENL10:1; /* [10:10] Emergency Stop Enable for Bit 10 in SRL - RW */
    ureg32 ENL11:1; /* [11:11] Emergency Stop Enable for Bit 11 in SRL - RW */
    ureg32 ENL12:1; /* [12:12] Emergency Stop Enable for Bit 12 in SRL - RW */
    ureg32 ENL13:1; /* [13:13] Emergency Stop Enable for Bit 13 in SRL - RW */
    ureg32 ENL14:1; /* [14:14] Emergency Stop Enable for Bit 14 in SRL - RW */
    ureg32 ENL15:1; /* [15:15] Emergency Stop Enable for Bit 15 in SRL - RW */
    ureg32 ENH0:1;  /* [16:16] Emergency Stop Enable for Bit 0 in SRH - RW */
    ureg32 ENH1:1;  /* [17:17] Emergency Stop Enable for Bit 1 in SRH - RW */
    ureg32 ENH2:1;  /* [18:18] Emergency Stop Enable for Bit 2 in SRH - RW */
    ureg32 ENH3:1;  /* [19:19] Emergency Stop Enable for Bit 3 in SRH - RW */
    ureg32 ENH4:1;  /* [20:20] Emergency Stop Enable for Bit 4 in SRH - RW */
    ureg32 ENH5:1;  /* [21:21] Emergency Stop Enable for Bit 5 in SRH - RW */
    ureg32 ENH6:1;  /* [22:22] Emergency Stop Enable for Bit 6 in SRH - RW */
    ureg32 ENH7:1;  /* [23:23] Emergency Stop Enable for Bit 7 in SRH - RW */
    ureg32 ENH8:1;  /* [24:24] Emergency Stop Enable for Bit 8 in SRH - RW */
    ureg32 ENH9:1;  /* [25:25] Emergency Stop Enable for Bit 9 in SRH - RW */
    ureg32 ENH10:1; /* [26:26] Emergency Stop Enable for Bit 10 in SRH - RW */
    ureg32 ENH11:1; /* [27:27] Emergency Stop Enable for Bit 11 in SRH - RW */
    ureg32 ENH12:1; /* [28:28] Emergency Stop Enable for Bit 12 in SRH - RW */
    ureg32 ENH13:1; /* [29:29] Emergency Stop Enable for Bit 13 in SRH - RW */
    ureg32 ENH14:1; /* [30:30] Emergency Stop Enable for Bit 14 in SRH - RW */
    ureg32 ENH15:1; /* [31:31] Emergency Stop Enable for Bit 15 in SRH - RW */
} MSC_EMSR_Bits;

/* Upstream Data Register */
typedef struct
{
    ureg32 RDAT:8;        /* [7:0] Received Data - RH */
    ureg32 OVF:1;         /* [8:8] Overflow Flag - RH */
    ureg32 OVEN:1;        /* [9:9] Overflow Feature Enable - RH */
    ureg32 reserved_10:6; /* [15:10] Internal reserved */
    ureg32 VB:1;          /* [16:16] Valid Bit - RH  */
    ureg32 PB:1;          /* [17:17] Parity Bit - RH  */
    ureg32 CB:1;          /* [18:18] Clear Bit - RH  */
    ureg32 LBF:2;         /* [20:19] Lower Address Bit Field - RH */
    ureg32 IPF:1;         /* [21:21] Internal Parity Flag - RH */
    ureg32 PE:1;          /* [22:22] Parity Error - RH */
    ureg32 reserved_23:9; /* [31:23] Internal reserved */
} MSC_UDR_Bits;

/* Interrupt Control Register */
typedef struct
{
    ureg32 DFIP:2;         /* [1:0] Data Frame Interrupt Node Pointer - RW */
    ureg32 EDII:1;         /* [2:2] Data Frame Interrupt Select - RW */
    ureg32 DFIE:1;         /* [3:3] Data Frame Interrupt Enable - RW */
    ureg32 CFIP:2;         /* [5:4] Command Frame Interrupt Node Pointer - RW */
    ureg32 reserved_6:1;   /* [6:6] Internal reserved */
    ureg32 CFIE:1;         /* [7:7] Command Frame Interrupt Enable - RW */
    ureg32 TFINTP:2;       /* [9:8] Time Frame Interrupt Pointer - RW */
    ureg32 reserved_10:1;  /* [10:10] Internal reserved */
    ureg32 TFINTE:1;       /* [11:11] Time Frame Interrupt Enable - RW */
    ureg32 RDIP:2;         /* [13:12] Receive Data Interrupt Configuration - RW */
    ureg32 RDII:2;         /* [15:14] Receive Data Interrupt Enable - RW */
    ureg32 SELDMA:1;       /* [16:16] Select DMA handling - RW */
    ureg32 SELMIR:1;       /* [17:17] Select mirror register enable - RW */
    ureg32 RDIE:1;         /* [18:18] Receive Data Interrupt Enable - RW */
    ureg32 DFILOSTE:1;     /* [19:19] Data Frame DMA Interrupt LOST Enable - RW */
    ureg32 CFILOSTE:1;     /* [20:20] Command Frame Interrupt LOST Enable - RW */
    ureg32 TFILOSTE:1;     /* [21:21] Time Frame DMA Interrupt LOST Enable- RW */
    ureg32 RDILOSTE:1;     /* [22:22] Receive Data DMA Interrupt LOST Enable - RW */
    ureg32 reserved_23:9;  /* [31:23] Internal reserved */
} MSC_INTCON_Bits;

/* Interrupt Set Clear Register */
typedef struct
{
    ureg32 CDFIF:1;       /* [0:0] Clear DFIF Flag - WO */
    ureg32 CCFIF:1;       /* [1:1] Clear CFIF Flag - WO */
    ureg32 CTFIF:1;       /* [2:2] Clear TFIF Flag - WO */
    ureg32 CRDIF:1;       /* [3:3] Clear RDIF Flag - WO */
    ureg32 CDATP:1;       /* [4:4] Clear DATP Flag - WO */
    ureg32 CCOMP:1;       /* [5:5] Clear CCOMP Flag - WO */
    ureg32 CDDIS:1;       /* [6:6] Clear DSDIS Flag - WO */
    ureg32 CDFILOST:1;    /* [7:7] Clear DFILOST Flag - WO */
    ureg32 CCFILOST:1;    /* [8:8] Clear CFILOST Flag - WO */
    ureg32 CTFILOST:1;    /* [9:9] Clear TFILOST Flag - WO */
    ureg32 CRDILOST:1;    /* [10:10] Clear RDILOST Flag - WO */
    ureg32 reserved_11:5; /* [15:11] Internal reserved */
    ureg32 SDFIF:1;       /* [16:16] Set DFIF Flag - WO */
    ureg32 SCFIF:1;       /* [17:17] Set CFIF Flag - WO */
    ureg32 STFIF:1;       /* [18:18] Set TFIF Flag - WO */
    ureg32 SRDIF:1;       /* [19:19] Set RDIF Flag - WO */
    ureg32 SDATP:1;       /* [20:20] Set DATP Bit - WO */
    ureg32 SCOMP:1;       /* [21:21] Set COMP Flag - WO */
    ureg32 SDDIS:1;       /* [22:22] Set DSDIS Flag - WO */
    ureg32 reserved_23:9; /* [31:23] Internal reserved */
} MSC_INTSC_Bits;

/* Interrupt Status Register */
typedef struct
{
    ureg32 DFIF:1;        /* [0:0] Data Frame Interrupt Flag - RH */
    ureg32 CFIF:1;        /* [1:1] Command Frame Interrupt Flag - RH */
    ureg32 TFIF:1;        /* [2:2] Time Frame Interrupt Flag - RH */
    ureg32 RDIF:1;        /* [3:3] Receive Data Interrupt Flag - RH */
    ureg32 DFILOST:1;     /* [4:4] Data Frame Interrupt Lost Flag - RH */
    ureg32 CFILOST:1;     /* [5:5] Command Frame Interrupt Lost Flag - RH */
    ureg32 TFILOST:1;     /* [6:6] Time Frame Interrupt Lost Flag - RH */
    ureg32 RDILOST:1;     /* [7:7] Receive Data Interrupt Lost Flag - RH */
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
} MSC_INTSTS_Bits;

/* Output Control Register */
typedef struct
{
    ureg32 reserved_0:2;   /* [1:0] Internal reserved */
    ureg32 CSP:1;          /* [2:2] Chip Selection Lines Polarity - RW */
    ureg32 SDILP:1;        /* [3:3] SDI Line Polarity - RW */
    ureg32 reserved_4:4;   /* [7:4] Internal reserved */
    ureg32 CLKCON:1;       /* [8:8] Clock Control - RW */
    ureg32 CSENL:2;        /* [10:9] Chip Enable Selection for ENL - RW */
    ureg32 CSENH:2;        /* [12:11] Chip Enable Selection for ENH - RW */
    ureg32 CSENC:2;        /* [14:13] Chip Enable Selection for ENC - RW */
    ureg32 reserved_15:1;  /* [15:15] Internal reserved */
    ureg32 SDIS:3;         /* [18:16] Serial Data Input Selection - RW */
    ureg32 reserved_19:12; /* [30:19] Internal reserved */
    ureg32 HRESPMASK:1;    /* [31:31] HRESP signal mask - RW */
} MSC_OCON_Bits;

/* Downstream Control Enhanced Register */
typedef struct
{
    ureg32 NBDFHE:1;      /* [0:0] Number of SRH Bits Shifted at Data Frames Extension - RW */
    ureg32 NBDFLE:1;      /* [1:1] Number of SRL Bits Shifted at Data Frames Extension - RW */
    ureg32 reserved_2:12; /* [13:2] Internal reserved */
    ureg32 EXEN:1;        /* [14:14] Extension Enable - RW */
    ureg32 CCF:1;         /* [15:15] Command-Command Flag - RW */
    ureg32 IEP0:1;        /* [16:16] Injection Enable of the Pin 0 Signal - RW */
    ureg32 IPP0:6;        /* [22:17] Injection Position of the Pin 0 Signal - RW */
    ureg32 reserved_23:1; /* [23:23] Internal reserved */
    ureg32 IEP1:1;        /* [24:24] Injection Enable of the Pin 1 Signal - RW */
    ureg32 IPP1:6;        /* [30:25] Injection Position of the Pin 1 Signal - RW */
    ureg32 CDCM:1;        /* [31:31] Command-Data-Command in Data Repetition Mode - RW */
} MSC_DCONE_Bits;

/* Upstream Control Enhanced Register */
typedef struct
{
    ureg32 UTP:4;          /* [3:0] Upstream Time-out Prescaler - RW */
    ureg32 UTV:4;          /* [7:4] Upstream Time-out Value - RW */
    ureg32 UTIE:1;         /* [8:8] Upstream Time-out Interrupt Enable - RW */
    ureg32 UTF:1;          /* [9:9] Upstream Time-out Flag - RH */
    ureg32 UTC:1;          /* [10:10] Upstream Time-out Clear - RW */
    ureg32 UTS:1;          /* [11:11] Upstream Time-out Set - WO */
    ureg32 reserved_12:1;  /* [12:12] Internal reserved */
    ureg32 UTASR:1;        /* [13:13] Upstream Time-out Alternate Service Request - RW */
    ureg32 UTIP:2;         /* [15:14] Upstream Time-out Interrupt Node Pointer - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} MSC_UCONE_Bits;

/* Downstream Select Data Source Low Extension Register */
typedef struct
{
    ureg32 SSL16:2; /* [1:0] Select Source for SRL - RW */
    ureg32 SSL17:2; /* [3:2] Select Source for SRL - RW */
    ureg32 SSL18:2; /* [5:4] Select Source for SRL - RW */
    ureg32 SSL19:2; /* [7:6] Select Source for SRL - RW */
    ureg32 SSL20:2; /* [9:8] Select Source for SRL - RW */
    ureg32 SSL21:2; /* [11:10] Select Source for SRL - RW */
    ureg32 SSL22:2; /* [13:12] Select Source for SRL - RW */
    ureg32 SSL23:2; /* [15:14] Select Source for SRL - RW */
    ureg32 SSL24:2; /* [17:16] Select Source for SRL - RW */
    ureg32 SSL25:2; /* [19:18] Select Source for SRL - RW */
    ureg32 SSL26:2; /* [21:20] Select Source for SRL - RW */
    ureg32 SSL27:2; /* [23:22] Select Source for SRL - RW */
    ureg32 SSL28:2; /* [25:24] Select Source for SRL - RW */
    ureg32 SSL29:2; /* [27:26] Select Source for SRL - RW */
    ureg32 SSL30:2; /* [29:28] Select Source for SRL - RW */
    ureg32 SSL31:2; /* [31:30] Select Source for SRL - RW */
} MSC_DDSLE_Bits;

/* Downstream Select Data Source High Extension Register */
typedef struct
{
    ureg32 SSH16:2; /* [1:0] Select Source for SRH - RW */
    ureg32 SSH17:2; /* [3:2] Select Source for SRH - RW */
    ureg32 SSH18:2; /* [5:4] Select Source for SRH - RW */
    ureg32 SSH19:2; /* [7:6] Select Source for SRH - RW */
    ureg32 SSH20:2; /* [9:8] Select Source for SRH - RW */
    ureg32 SSH21:2; /* [11:10] Select Source for SRH - RW */
    ureg32 SSH22:2; /* [13:12] Select Source for SRH - RW */
    ureg32 SSH23:2; /* [15:14] Select Source for SRH - RW */
    ureg32 SSH24:2; /* [17:16] Select Source for SRH - RW */
    ureg32 SSH25:2; /* [19:18] Select Source for SRH - RW */
    ureg32 SSH26:2; /* [21:20] Select Source for SRH - RW */
    ureg32 SSH27:2; /* [23:22] Select Source for SRH - RW */
    ureg32 SSH28:2; /* [25:24] Select Source for SRH - RW */
    ureg32 SSH29:2; /* [27:26] Select Source for SRH - RW */
    ureg32 SSH30:2; /* [29:28] Select Source for SRH - RW */
    ureg32 SSH31:2; /* [31:30] Select Source for SRH - RW */
} MSC_DDSHE_Bits;

/* Emergency Stop Extension Register */
typedef struct
{
    ureg32 ENL16:1; /* [0:0] Emergency Stop Enable for Bit 16 in SRL - RW */
    ureg32 ENL17:1; /* [1:1] Emergency Stop Enable for Bit 17 in SRL - RW */
    ureg32 ENL18:1; /* [2:2] Emergency Stop Enable for Bit 18 in SRL - RW */
    ureg32 ENL19:1; /* [3:3] Emergency Stop Enable for Bit 19 in SRL - RW */
    ureg32 ENL20:1; /* [4:4] Emergency Stop Enable for Bit 20 in SRL - RW */
    ureg32 ENL21:1; /* [5:5] Emergency Stop Enable for Bit 21 in SRL - RW */
    ureg32 ENL22:1; /* [6:6] Emergency Stop Enable for Bit 22 in SRL - RW */
    ureg32 ENL23:1; /* [7:7] Emergency Stop Enable for Bit 23 in SRL - RW */
    ureg32 ENL24:1; /* [8:8] Emergency Stop Enable for Bit 24 in SRL - RW */
    ureg32 ENL25:1; /* [9:9] Emergency Stop Enable for Bit 25 in SRL - RW */
    ureg32 ENL26:1; /* [10:10] Emergency Stop Enable for Bit 26 in SRL - RW */
    ureg32 ENL27:1; /* [11:11] Emergency Stop Enable for Bit 27 in SRL - RW */
    ureg32 ENL28:1; /* [12:12] Emergency Stop Enable for Bit 28 in SRL - RW */
    ureg32 ENL29:1; /* [13:13] Emergency Stop Enable for Bit 29 in SRL - RW */
    ureg32 ENL30:1; /* [14:14] Emergency Stop Enable for Bit 30 in SRL - RW */
    ureg32 ENL31:1; /* [15:15] Emergency Stop Enable for Bit 31 in SRL - RW */
    ureg32 ENH16:1; /* [16:16] Emergency Stop Enable for Bit 16 in SRH - RW */
    ureg32 ENH17:1; /* [17:17] Emergency Stop Enable for Bit 17 in SRH - RW */
    ureg32 ENH18:1; /* [18:18] Emergency Stop Enable for Bit 18 in SRH - RW */
    ureg32 ENH19:1; /* [19:19] Emergency Stop Enable for Bit 19 in SRH - RW */
    ureg32 ENH20:1; /* [20:20] Emergency Stop Enable for Bit 20 in SRH - RW */
    ureg32 ENH21:1; /* [21:21] Emergency Stop Enable for Bit 21 in SRH - RW */
    ureg32 ENH22:1; /* [22:22] Emergency Stop Enable for Bit 22 in SRH - RW */
    ureg32 ENH23:1; /* [23:23] Emergency Stop Enable for Bit 23 in SRH - RW */
    ureg32 ENH24:1; /* [24:24] Emergency Stop Enable for Bit 24 in SRH - RW */
    ureg32 ENH25:1; /* [25:25] Emergency Stop Enable for Bit 25 in SRH - RW */
    ureg32 ENH26:1; /* [26:26] Emergency Stop Enable for Bit 26 in SRH - RW */
    ureg32 ENH27:1; /* [27:27] Emergency Stop Enable for Bit 27 in SRH - RW */
    ureg32 ENH28:1; /* [28:28] Emergency Stop Enable for Bit 28 in SRH - RW */
    ureg32 ENH29:1; /* [29:29] Emergency Stop Enable for Bit 29 in SRH - RW */
    ureg32 ENH30:1; /* [30:30] Emergency Stop Enable for Bit 30 in SRH - RW */
    ureg32 ENH31:1; /* [31:31] Emergency Stop Enable for Bit 31 in SRH - RW */
} MSC_EMSRE_Bits;

/* Downstream Timing Extension Register */
typedef struct
{
    ureg32 PPLDE:2;        /* [1:0] Passive Phase Length at Data Frames Extension - RW */
    ureg32 PPLCE:6;        /* [7:2] Passive Phase Length at Control Frames Extension - RW */
    ureg32 NDIVD:4;        /* [11:8] N Divider Downstream - RW */
    ureg32 PPLCEM:1;       /* [12:12] PPCE Extension Bit on the MSB Side - RW */
    ureg32 reserved_13:3;  /* [15:13] Internal reserved */
    ureg32 FM:1;           /* [16:16] Fast Mode - RW */
    ureg32 reserved_17:11; /* [27:17] Internal reserved */
    ureg32 CX:1;           /* [28:28] Command Extension Mode - RW */
    ureg32 reserved_29:2;  /* [30:29] Internal reserved */
    ureg32 UL1:1;          /* [31:31] Unlock CX and FM for one write access - RW */
} MSC_DTE_Bits;

/* Downstream Data Mirror Register */
typedef struct
{
    ureg32 DDLM:16; /* [15:0] Downstream Data Mirror for SRL Shift Register - WO */
    ureg32 DDHM:16; /* [31:16] Downstream Data Mirror for SRH Shift Register - WO */
} MSC_DDRM_Bits;

/* Downstream Data Extension Register */
typedef struct
{
    ureg32 DDLE:16; /* [15:0] Downstream Data Extension for SRL Shift Register - RW */
    ureg32 DDHE:16; /* [31:16] Downstream Data Extension for SRH Shift Register - RW */
} MSC_DDRE_Bits;

/* Downstream Command Mirror Register */
typedef struct
{
    ureg32 DCLM:16; /* [15:0] Downstream Command Mirror of the DC.DCL Bit Field - WO */
    ureg32 DCHM:16; /* [31:16] Downstream Command Mirror of the DC.DCH Bit Field - WO */
} MSC_DCRM_Bits;

/* Downstream Command Extension Register */
typedef struct
{
    ureg32 DCEH:32; /*[31:0] Downstream Command Extension for SRH Shift Register - RW */
} MSC_DCRE_Bits;

/* Asynchronous block configuration register */
typedef struct
{
    ureg32 DLC:4;         /* [3:0] Duration of the Low Phase of the Shift Clock - RW */
    ureg32 DHC:4;         /* [7:4] Duration of the High Phase of the Shift Clock - RW */
    ureg32 OINTP:2;       /* [9:8] Overflow Interrupt Node Pointer - RW */
    ureg32 OASREQ:1;      /* [10:10] Overflow Alternate Service Request - RW */
    ureg32 reserved_11:1; /* [11:11] Internal reserved */
    ureg32 OVF:1;         /* [12:12] Overflow Flag - RO */
    ureg32 OVFM:2;        /* [14:13] Overflow Flag Modify - WO */
    ureg32 OINTE:1;       /* [15:15] Overflow Interrupt Enable - RW */
    ureg32 NDIVA:3;       /* [18:16] N Divider ABRA - RW */
    ureg32 UINTP:2;       /* [20:19] Underflow Interrupt Node Pointer - RW */
    ureg32 UASREQ:1;      /* [21:21] Underflow Alternate Service Request - RW */
    ureg32 reserved_22:1; /* [22:22] Internal reserved */
    ureg32 UNF:1;         /* [23:23] Underflow Flag - RO */
    ureg32 UNFM:2;        /* [25:24] Underflow Flag Modify - WO */
    ureg32 UINTE:1;       /* [26:26] Underflow Interrupt Enable - RW */
    ureg32 CLKSEL:3;      /* [29:27] Clock Select - RW */
    ureg32 reserved_30:1; /* [30:30] Internal reserved */
    ureg32 ABB:1;         /* [31:31] Asynchronous Block Bypass - RW */
} MSC_ABCR_Bits;

/* Asynchronous Block Configuration Extension Register */
typedef struct
{
    ureg32 PPA:5;         /* [4:0] Passive Phase Length Output by ABRA - RW */
    ureg32 reserved_5:27; /* [31:5] Internal Reserved */
} MSC_ABCRE_Bits;

/**********************************************************************************************************************
 *                                             MSC Register Definitions
 *********************************************************************************************************************/
/* Module Identification Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    MSC_MID_Bits B; /* Bit-Field access */
} MSC_MID;

/* Fractional Divider Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_FDIV_Bits B; /* Bit-Field access */
} MSC_FDIV;

/* Upstream Status Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    MSC_UPSTS_Bits B; /* Bit-Field access */
} MSC_UPSTS;

/* Downstream Control Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_DCON_Bits B; /* Bit-Field access */
} MSC_DCON;

/* Downstream Status Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_DSTS_Bits B; /* Bit-Field access */
} MSC_DSTS;

/* Downstream Data Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;      /* Unsigned access */
    MSC_DD_Bits B; /* Bit-Field access */
} MSC_DD;

/*Downstream Command Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;      /* Unsigned access */
    MSC_DC_Bits B; /* Bit-Field access */
} MSC_DC;

/* Downstream Select Data Source Low Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_DDSL_Bits B; /* Bit-Field access */
} MSC_DDSL;

/* Downstream Select Data Source High Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_DDSH_Bits B; /* Bit-Field access */
} MSC_DDSH;

/* Emergency Stop Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_EMSR_Bits B; /* Bit-Field access */
} MSC_EMSR;

/* Upstream Data Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    MSC_UDR_Bits B; /* Bit-Field access */
} MSC_UDR;

/* Interrupt Control Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    MSC_INTCON_Bits B; /* Bit-Field access */
} MSC_INTCON;

/* Interrupt Status Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    MSC_INTSTS_Bits B; /* Bit-Field access */
} MSC_INTSTS;

/* Interrupt Set Clear Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    MSC_INTSC_Bits B; /* Bit-Field access */
} MSC_INTSC;

/* Output Control Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_OCON_Bits B; /* Bit-Field access */
} MSC_OCON;

/* Downstream Control Enhanced Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    MSC_DCONE_Bits B; /* Bit-Field access */
} MSC_DCONE;

/* Upstream Control Enhanced Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    MSC_UCONE_Bits B; /* Bit-Field access */
} MSC_UCONE;

/* Downstream Select Data Source Low Extension Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    MSC_DDSLE_Bits B; /* Bit-Field access */
} MSC_DDSLE;

/* Downstream Select Data Source High Extension Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    MSC_DDSHE_Bits B; /* Bit-Field access */
} MSC_DDSHE;

/* Emergency Stop Extension Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    MSC_EMSRE_Bits B; /* Bit-Field access */
} MSC_EMSRE;

/* Downstream Timing Extension Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    MSC_DTE_Bits B; /* Bit-Field access */
} MSC_DTE;

/* Downstream Data Mirror Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_DDRM_Bits B; /* Bit-Field access */
} MSC_DDRM;

/* Downstream Data Extension Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_DDRE_Bits B; /* Bit-Field access */
} MSC_DDRE;

/*Downstream Command Mirror Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_DCRM_Bits B; /* Bit-Field access */
} MSC_DCRM;

/*Downstream Command Extension Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_DCRE_Bits B; /* Bit-Field access */
} MSC_DCRE;

/* Asynchronous Block Configuration Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    MSC_ABCR_Bits B; /* Bit-Field access */
} MSC_ABCR;

/* Asynchronous Block Configuration Extension Register */
typedef union
/* #Violation: msc_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    MSC_ABCRE_Bits B; /* Bit-Field access */
} MSC_ABCRE;

/**********************************************************************************************************************
 *                                        MSC Register Configuration Structure
 *********************************************************************************************************************/
/* #Violation: msc_register_h_REF_2 */
/* #Violation: msc_register_h_REF_3 */
typedef volatile struct
{
    ureg32 RESERVED_0[2];  /* 0x0 - Internal reserved */
    MSC_MID MID;           /* 0x8 - Module Identification Register */
    MSC_FDIV FDIV;         /* 0xC - Fractional Divider Register */
    MSC_UPSTS UPSTS;       /* 0x10 - Upstream Status Register */
    MSC_DCON DCON;         /* 0X14 - Downstream Control Register */
    MSC_DSTS DSTS;         /* 0X18 - Downstream Status Register */
    MSC_DD DD;             /* 0x1C - Downstream Data Register */
    MSC_DC DC;             /* 0x20 - Downstream Command Register */
    MSC_DDSL DDSL;         /* 0x24 - Downstream Select Data Source Low Register */
    MSC_DDSH DDSH;         /* 0x28 - Downstream Select Data Source High Register */
    MSC_EMSR EMSR;         /* 0x2C - Emergency Stop Register */
    /* #Violation: msc_register_h_REF_4 */
    /* #Violation: msc_register_h_REF_5 */
    MSC_UDR UDR[4];        /* 0x30 - Upstream Data Register */
    MSC_INTCON INTCON;     /* 0x40 - Interrupt Control Register */
    MSC_INTSTS INTSTS;     /* 0x44 - Interrupt Status Register */
    MSC_INTSC INTSC;       /* 0x48 - Interrupt Set Clear Register */
    MSC_OCON OCON;         /* 0x4C - Output Control Register */
    ureg32 RESERVED_50[2]; /* 0x50 - Internal reserved */
    MSC_DCONE DCONE;       /* 0x58 - Downstream Control Enhanced Register */
    MSC_UCONE UCONE;       /* 0x5C - Upstream Control Enhanced Register */
    MSC_DDSLE DDSLE;       /* 0x60 - Downstream Select Data Source Low Extension Register */
    MSC_DDSHE DDSHE;       /* 0x64 - Downstream Select Data Source High Extension Register */
    MSC_EMSRE EMSRE;       /* 0x68 - Emergency Stop Extension Register */
    MSC_DTE DTE;           /* 0x6C - Downstream Timing Extension Register */
    MSC_DDRM DDRM;         /* 0x70 - Downstream Data Mirror Register */
    MSC_DDRE DDRE;         /* 0x74 - Downstream Data Extension Register */
    MSC_DCRM DCRM;         /* 0x78 - Downstream Command Mirror Register */
    MSC_DCRE DCRE;         /* 0x7C - Downstream Command Extension Register */
    MSC_ABCR ABCR;         /* 0x80 - Asynchronous Block Configuration Register */
    MSC_ABCRE ABCRE;       /* 0x84 - Asynchronous Block Configuration Extension Register */
} MSC_MODULE;

#endif /* MSC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

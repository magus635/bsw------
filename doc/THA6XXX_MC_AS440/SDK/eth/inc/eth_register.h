/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    eth_register.h
 * Author:      00930
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of ETH module registers.
 *********************************************************************************************************************/
#ifndef ETH_REGISTER_H_
#define ETH_REGISTER_H_

/*
*#Violation Summary
*#eth_regiter_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to registers.
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        ETH Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* MAC Block */
/* MAC Configuration Register */
typedef struct
{
    ureg32 RE:1;          /* [0:0] Receiver Enable - RE (rw) */
    ureg32 TE:1;          /* [1:1] Transmitter Enable - TE (rw) */
    ureg32 PRELEN:2;      /* [3:2] Preamble Length for Transmit packets - PRELEN (rw) */
    ureg32 DC:1;          /* [4:4] Deferral Check - DC (rw) */
    ureg32 BL:2;          /* [6:5] Back-Off Limit - BL (rw) */
    ureg32 reserved_7:1;  /* [7:7] internal Reserved */
    ureg32 DR:1;          /* [8:8] Disable Retry - DR (rw) */
    ureg32 DCRS:1;        /* [9:9] Disable Carrier Sense During Transmission - DCRS (rw) */
    ureg32 DO:1;          /* [10:10] Disable Receive Own - DO (rw) */
    ureg32 ECRSFD:1;      /* [11:11] Enable Carrier Sense Before Transmission in Full-Duplex Mode - ECRSFD (rw) */
    ureg32 LM:1;          /* [12:12] Loopback Mode - LM (rw) */
    ureg32 DM:1;          /* [13:13] Duplex Mode - DM (rw),0x0 (HDUPLX): Half-duplex mode */
    ureg32 FES:1;         /* [14:14] Speed - FES (rw) */
    ureg32 PS:1;          /* [15:15] Port Select - PS (rw) */
    ureg32 JE:1;          /* [16:16] Jumbo Packet Enable - JE (rw) */
    ureg32 JD:1;          /* [17:17] Jabber Disable - JD (rw) */
    ureg32 BE:1;          /* [18:18] Packet Burst Enable - BE (rw) */
    ureg32 WD:1;          /* [19:19] Watchdog Disable - WD (rw) */
    ureg32 ACS:1;         /* [20:20] Automatic Pad or CRC Stripping - ACS (rw) */
    ureg32 CST:1;         /* [21:21] CRC stripping for Type packets - CST (rw) */
    ureg32 S2KP:1;        /* [22:22] IEEE 802.3as Support for 2K Packets - S2KP (rw) */
    ureg32 GPSLCE:1;      /* [23:23] Giant Packet Size Limit Control Enable - GPSLCE (rw) */
    ureg32 IPG:3;         /* [26:24] Inter-Packet Gap - IPG (rw) */
    ureg32 IPC:1;         /* [27:27] Checksum Offload - IPC (rw) */
    ureg32 SARC:3;        /* [30:28] Source Address Insertion or Replacement Control - SARC (rw) A6 Reserved  */
    ureg32 reserved_31:1; /* [31:31] internal Reserved,ARP Offload Enable */
} ETH_MAC_CONFIGURATION_Bits;

/* MAC Extended Configuration Register */
typedef struct
{
    ureg32 GPSL:14;       /* [13:0] Giant Packet Size Limit - GPSL (rw) */
    ureg32 reserved_14:2; /* [15:14] internal Reserved */
    ureg32 DCRCC:1;       /* [16:16] Disable CRC Checking for Received Packets - DCRCC (rw) */
    ureg32 SPEN:1;        /* [17:17] Slow Protocol Detection Enable - SPEN (rw) */
    ureg32 USP:1;         /* [18:18] Unicast Slow Protocol Packet Detect - USP (rw) */
    ureg32 reserved_19:1; /* [19:19] internal Reserved,packet Duplication Control(Multicast/broadcast) */
    ureg32 HDSMS:3;       /* [22:20] Maximum Size for Splitting the Header Data - HDSMS (rw) */
    ureg32 reserved_23:1; /* [23:23] internal Reserved */
    ureg32 EIPGEN:1;      /* [24:24] Extended Inter-Packet Gap Enable - EIPGEN (rw) */
    ureg32 EIPG:5;        /* [29:25] Extended Inter-Packet Gap - EIPG (rw) */
    ureg32 reserved_30:1; /* [30:30] internal Reserved */
    ureg32 reserved_31:1; /* [31:31] internal Reserved,Flexible Header Enable (rw) */
} ETH_MAC_EXT_CONFIGURATION_Bits;

/* MAC Packet Filter Register */
typedef struct
{
    ureg32 PR:1;          /* [0:0] Promiscuous Mode - PR (rw) */
    ureg32 HUC:1;         /* [1:1] Hash Unicast, THA6206 and THA6412 are supported, but THA6104 is not supported */
    ureg32 HMC:1;         /* [2:2] Hash Multicast, THA6206 and THA6412 are supported, but THA6104 is not supported */
    ureg32 DAIF:1;        /* [3:3] DA Inverse Filtering - DAIF (rw) */
    ureg32 PM:1;          /* [4:4] Pass All Multicast - PM (rw) */
    ureg32 DBF:1;         /* [5:5] Disable Broadcast Packets - DBF (rw) */
    ureg32 PCF:2;         /* [7:6] Pass Control Packets - PCF (rw) */
    ureg32 SAIF:1;        /* [8:8] SA Inverse Filtering - SAIF (rw) */
    ureg32 SAF:1;         /* [9:9] Source Address Filter Enable - SAF (rw) */
    ureg32 HPF:1;         /* [10:10] Hash or perfect Filter, THA6206 and THA6412 are supported, but THA6104 is not supported */
    ureg32 reserved_11:5; /* [15:11] internal Reserved */
    ureg32 VTFE:1;        /* [16:16] VLAN Tag Filter Enable - VTFE (rw) */
    ureg32 reserved_17:3; /* [19:17] internal Reserved */
    ureg32 reserved_20:2; /* [21:20] internal Reserved */
    ureg32 reserved_22:9; /* [30:22] internal Reserved */
    ureg32 RA:1;          /* [31:31] Receive All - RA (rw) */
} ETH_MAC_PACKET_FILTER_Bits;

/* MAC Watchdog Timeout Register */
typedef struct
{
    ureg32 WTO:4;         /* [3:0] Watchdog Timeout - WTO (rw) */
    ureg32 reserved_4:4;  /* [7:4] internal Reserved */
    ureg32 PWE:1;         /* [8:8] Programmable Watchdog Enable - PWE (rw) */
    ureg32 reserved_9:7;  /* [15:9] internal Reserved */
    ureg32 JTO:4;         /* [19:16] Jabber Timeout */
    ureg32 reserved_20:4; /* [23:20] internal Reserved */
    ureg32 PJE:1;         /* [24:24] internal Reserved */
    ureg32 reserved_25:7; /* [31:25] internal Reserved */
} ETH_MAC_WATCHDOG_TIMEOUT_Bits;

/* The Hash Table Register 0 contains the first 32 bits of the
 hash table,, when the width of the hash table is 128 or 256 bits. offset = 0x10 */
typedef struct
{
    ureg32 HT31T0:32; /* [31:0]the first 32 Bits [31:0] of the Hash table (rw) */
} ETH_MAC_HASH_Table_Reg0_Bits;

/* The Hash Table Register 1 */
typedef struct
{
    ureg32 HT63T32:32; /* [31:0]the 32 Bits  [63:32] of the Hash table (rw) */
} ETH_MAC_HASH_Table_Reg1_Bits;

/* The Hash Table Register 2 */
typedef struct
{
    ureg32 HT95T64:32; /* [31:0]the 32 Bits  [95:64] of the Hash table (rw) */
} ETH_MAC_HASH_Table_Reg2_Bits;

/* The Hash Table Register 3 */
typedef struct
{
    ureg32 HT127T96:32; /* [31:0]the 32 Bits  [127:96] of the Hash table (rw) */
} ETH_MAC_HASH_Table_Reg3_Bits;

/* The Hash Table Register 4 */
typedef struct
{
    ureg32 HT159T128:32; /* [31:0]the 32 Bits  [159:128] of the Hash table (rw) */
} ETH_MAC_HASH_Table_Reg4_Bits;

/* The Hash Table Register 5 */
typedef struct
{
    ureg32 HT191T160:32; /* [31:0]the 32 Bits  [191:160] of the Hash table (rw) */
} ETH_MAC_HASH_Table_Reg5_Bits;

/* The Hash Table Register 6 */
typedef struct
{
    ureg32 HT223T192:32; /* [31:0]the 32 Bits  [223:192] of the Hash table (rw) */
} ETH_MAC_HASH_Table_Reg6_Bits;

/* The Hash Table Register 7 */
typedef struct
{
    ureg32 HT255T224:32; /* [31:0]the 32 Bits  [255:224] of the Hash table (rw) */
} ETH_MAC_HASH_Table_Reg7_Bits;

/* MAC VLAN Tag Control Register,redefined format of the MAC VLAN Tag Register */
typedef struct
{
    ureg32 OB:1;          /* [0:0] Operation Busy - OB (rw) */
    ureg32 CT:1;          /* [1:1] Command Type - CT (rw) */
    ureg32 OFS:3;         /* [4:2] Offset - OFS (rw) */
    ureg32 reserved_5:11; /* [15:5] internal Reserved */
    ureg32 ETV:1;         /* [16:16] Enable 12-Bit VLAN Tag Comparison for VLAN Hash Filtering */
    ureg32 VTIM:1;        /* [17:17] VLAN Tag Inverse Match Enable - VTIM (rw) */
    ureg32 ESVL:1;        /* [18:18] Enable S-VLAN - ESVL (rw) */
    ureg32 ERSVLM:1;      /* [19:19] Enable Receive S-VLAN Match for VLAN Hash Filtering */
    ureg32 DOVLTC:1;      /* [20:20] Disable VLAN Type Check for VLAN Hash Filtering */
    ureg32 EVLS:2;        /* [22:21] Enable VLAN Tag Stripping on Receive - EVLS (rw) */
    ureg32 reserved_23:1; /* [23:23] internal Reserved */
    ureg32 EVLRXS:1;      /* [24:24] Enable VLAN Tag in Rx status - EVLRXS (rw) */
    ureg32 VTHM:1;        /* [25:25] VLAN Tag Hash Table Match Enable - VTHM (rw) */
    ureg32 EDVLP:1;       /* [26:26] Enable Double VLAN Processing - EDVLP (rw) */
    ureg32 ERIVLT:1;      /* [27:27]  (rw) */
    ureg32 EIVLS:2;       /* [29:28] Enable Inner VLAN Tag Stripping on Receive - EIVLS (rw) */
    ureg32 reserved_30:1; /* [30:30] internal Reserved */
    ureg32 EIVLRXS:1;     /* [31:31] Enable Inner VLAN Tag in Rx Status - EIVLRXS (rw) */
} ETH_MAC_VLAN_TAG_CTRL_Bits;

/* The VLAN Tag register identifies the IEEE 802.1Q VLAN type packets. */
typedef struct
{
    ureg32 VL:16;         /* [15:0] VLAN Tag Identifier for Receive Packets(rw) */
    ureg32 EVT:1;         /* [16:16] Enable 12-Bit VLAN Tag Comparison(rw) */
    ureg32 VTIM:1;        /* [17:17] VLAN Tag Inverse Match Enable(rw) */
    ureg32 ESVL:1;        /* [18:18] Enable S-VLAN packets (Type = 0x88A8) as valid VLAN tagged(rw) */
    ureg32 ERSVLM:1;      /* [19:19] Enable Receive S-VLAN Match (rw) */
    ureg32 DOVLTC:1;      /* [20:20] Disable VLAN Type Check (rw) */
    ureg32 EVLS:2;        /* [22:21] Enable VLAN Tag Stripping on Receive (rw) */
    ureg32 reserved_23:1; /* [23:23] internal Reserved */
    ureg32 EVLRXS:1;      /* [24:24] Enable VLAN Tag in Rx status (rw) */
    ureg32 VTHM:1;        /* [25:25] VLAN Tag Hash Table Match Enable (rw) */
    ureg32 EDVLP:1;       /* [26:26] Enable Double VLAN Processing (rw) */
    ureg32 ERIVLT:1;      /* [27:27] Enable Inner VLAN Tag (rw) */
    ureg32 EIVLS:2;       /* [29:28] Enable Inner VLAN Tag Stripping on Receive (rw) */
    ureg32 reserved_30:1; /* [30:30] internal Reserved */
    ureg32 EIVLRXS:1;     /* [31:31] Enable Inner VLAN Tag in Rx Status */
} ETH_MAC_VLAN_TAG_Bits;

/* MAC VLAN Tag Data Register */
typedef struct
{
    ureg32 VID:16;        /* [15:0] VLAN Tag ID - VID (rw) */
    ureg32 VEN:1;         /* [16:16] VLAN Tag Enable - VEN (rw) */
    ureg32 ETV:1;         /* [17:17] 12bits or 16bits VLAN comparison - ETV (rw) */
    ureg32 DOVLTC:1;      /* [18:18] Disable VLAN Type Comparison - DOVLTC (rw) */
    ureg32 ERSVLM:1;      /* [19:19] Enable S-VLAN Match for received Frames - ERSVLM (rw) */
    ureg32 ERIVLT:1;      /* [20:20] Enable Inner VLAN Tag Comparison - ERIVLT (rw) */
    ureg32 reserved_21:3; /* [23:21] internal Reserved */
    ureg32 DMACHEN:1;     /* [24:24] DMA Channel Number Enable - DMACHEN (rw) */
    ureg32 DMACHN:2;      /* [26:25] DMA Channel Number - DMACHN (rw) */
    ureg32 reserved_27:5; /* [31:27] internal Reserved */
} ETH_MAC_VLAN_TAG_DATA_Bits;

/* MAC VLAN Tag Filter Register */
typedef struct
{
    ureg32 VID:16;        /* [15:0] VLAN Tag ID - VID (rw) */
    ureg32 VEN:1;         /* [16:16] VLAN Tag Enable - VEN (rw) */
    ureg32 ETV:1;         /* [17:17] 12bits or 16bits VLAN comparison - ETV (rw) */
    ureg32 DOVLTC:1;      /* [18:18] Disable VLAN Type Comparison - DOVLTC (rw) */
    ureg32 ERSVLM:1;      /* [19:19] Enable S-VLAN Match for received Frames - ERSVLM (rw) */
    ureg32 ERIVLT:1;      /* [20:20] Enable Inner VLAN Tag Comparison - ERIVLT (rw) */
    ureg32 reserved_21:3; /* [23:21] internal Reserved */
    ureg32 DMACHEN:1;     /* [24:24] DMA Channel Number Enable - DMACHEN (rw) */
    ureg32 DMACHN:2;      /* [26:25] DMA Channel Number - DMACHN (rw) */
    ureg32 reserved_27:5; /* [31:27] internal Reserved */
} ETH_MAC_VLAN_TAG_FILTER_Bits;

/* MAC VLAN Hash Table Register */
typedef struct
{
    ureg32 VLHT:16;        /* [15:0] VLAN Hash Table - VLHT (rw) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MAC_VLAN_HASH_TABLE_Bits;

/* MAC VLAN Tag Inclusion or Replacement Register */
typedef struct ETH_MAC_VLAN_INCL_Bits
{
    ureg32 VLT:16;        /* [15:0] VLAN Tag for Transmit Packets - VLT (rw) */
    ureg32 VLC:2;         /* [17:16] VLAN Tag Control in Transmit Packets - VLC (rw) */
    ureg32 VLP:1;         /* [18:18] VLAN Priority Control - VLP (rw) */
    ureg32 CSVL:1;        /* [19:19] C-VLAN or S-VLAN - CSVL (rw) */
    ureg32 VLTI:1;        /* [20:20] VLAN Tag Input - VLTI (rw) */
    ureg32 reserved_21:1; /* [21:21] Channel based tag insertion - CBTI (rw) */
    ureg32 reserved_22:2; /* [23:22] internal Reserved */
    ureg32 reserved_24:2; /* [25:24] Address - ADDR (rw) */
    ureg32 reserved_26:4; /* [29:26] internal Reserved */
    ureg32 reserved_30:1; /* [30:30] Read write control - RDWR (rw) */
    ureg32 reserved_31:1; /* [31:31] Busy - BUSY (r) */
} ETH_MAC_VLAN_INCL_Bits;

/* MAC VLAN Tag Inclusion or Replacement Register per Queue */
typedef struct
{
    ureg32 VLT:16;         /* [15:0] VLAN Tag for Transmit Packets - VLT (rw) */
    ureg32 reserved_16:3;  /* [18:16] internal Reserved */
    ureg32 CSVL:1;         /* [19:19] C-VLAN or S-VLAN - CSVL (rw) */
    ureg32 reserved_20:12; /* [31:20] internal Reserved */
} ETH_MAC_VLAN_INCL_Q_Bits;

/* MAC Inner VLAN Tag Inclusion or Replacement Register */
typedef struct
{
    ureg32 VLT:16;         /* [15:0] VLAN Tag for Transmit Packets - VLT (rw) */
    ureg32 VLC:2;          /* [17:16] VLAN Tag Control in Transmit Packets - VLC (rw) */
    ureg32 VLP:1;          /* [18:18] VLAN Priority Control - VLP (rw) */
    ureg32 CSVL:1;         /* [19:19] C-VLAN or S-VLAN - CSVL (rw) */
    ureg32 VLTI:1;         /* [20:20] VLAN Tag Input - VLTI (rw) */
    ureg32 reserved_21:11; /* [31:21] internal Reserved */
} ETH_MAC_INNER_VLAN_INCL_Bits;

/* MAC Queue 0/1/2/3 TX Flow Control Register */
typedef struct
{
    ureg32 FCB_BPA:1;    /* [0:0] Flow Control Busy or Backpressure Activate - FCB_BPA (rw) */
    ureg32 TFE:1;        /* [1:1] Transmit Flow Control Enable - TFE (rw) */
    ureg32 reserved_2:2; /* [3:2] internal Reserved */
    ureg32 PLT:3;        /* [6:4] Pause Low Threshold - PLT (rw) */
    ureg32 DZPQ:1;       /* [7:7] Disable Zero-Quanta Pause - DZPQ (rw) */
    ureg32 reserved_8:8; /* [15:8] internal Reserved */
    ureg32 PT:16;        /* [31:16] Pause Time - PT (rw) */
} ETH_MAC_Q0_TX_FLOW_CTRL_Bits;

/* MAC Receive Flow Control Register */
typedef struct
{
    ureg32 RFE:1;         /* [0:0] Receive Flow Control Enable - RFE (rw) */
    ureg32 UP:1;          /* [1:1] Unicast Pause Packet Detect - UP (rw) */
    ureg32 reserved_2:6;  /* [7:2] internal Reserved */
    ureg32 PFCE:1;        /* [8:8] Priority Based Flow Control Enable */
    ureg32 reserved_9:23; /* [31:9] internal Reserved */
} ETH_MAC_RX_FLOW_CTRL_Bits;

/* MAC Receive Queue Control 4 register */
typedef struct
{
    ureg32 UFFQE:1;        /* [0:0] Unicast Address Filter Fail Packets Queuing Enable  - UFFQE (rw) */
    ureg32 UFFQ:2;         /* [2:1] Unicast Address Filter Fail Packets Queue - UFFQ (rw) */
    ureg32 reserved_3:5;   /* [7:3] internal Reserved */
    ureg32 MFFQE:1;        /* [8:8] Multicast Address Filter Fail Packets Queuing Enable  - MFFQE (rw) */
    ureg32 MFFQ:2;         /* [10:9] Multicast Address Filter Fail Packets Queue - MFFQ (rw) */
    ureg32 reserved_11:5;  /* [15:11] internal Reserved */
    ureg32 VFFQE:1;        /* [16:16] VLAN Tag Filter Fail Packets Queuing Enable  - VFFQE (rw) */
    ureg32 VFFQ:2;         /* [18:17] VLAN Tag Filter Fail Packets Queue - VFFQ (rw) */
    ureg32 reserved_19:13; /* [31:19] internal Reserved */
} ETH_MAC_RXQ_CTRL4_Bits;

/* The Transmit Queue Priority Mapping 0 register contains the priority values assigned to Tx Queue 0 through Tx Queue 3
 */
typedef struct
{
    ureg32 PSTQ0:8; /* [7:0] Priorities Selected in Transmit Queue 0 */
    ureg32 PSTQ1:8; /* [15:8] Priorities Selected in Transmit Queue 1 */
    ureg32 PSTQ2:8; /* [23:16] Priorities Selected in Transmit Queue 2 */
    ureg32 PSTQ3:8; /* [31:24] Priorities Selected in Transmit Queue 3 */
} ETH_MAC_TXQ_PRTY_MAP0_Bits;

/* MAC Receive Queue Control 0 Register */
typedef struct
{
    ureg32 RXQ0EN:2;       /* [1:0] Receive Queue 0 Enable - RXQ0EN (rw) */
    ureg32 RXQ1EN:2;       /* [3:2] Receive Queue 1 Enable - RXQ1EN (rw) */
    ureg32 RXQ2EN:2;       /* [5:4] Receive Queue 2 Enable - RXQ2EN (rw) */
    ureg32 RXQ3EN:2;       /* [7:6] Receive Queue 3 Enable - RXQ3EN (rw) */
    ureg32 reserved_8:8;   /* [15:8] internal Reserved */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MAC_RXQ_CTRL0_Bits;

/* MAC Receive Queue Control 1 Register */
typedef struct
{
    ureg32 AVCPQ:3;       /* [2:0] AV Untagged Control Packets Queue - AVCPQ (rw) */
    ureg32 reserved_3:1;  /* [3:3] internal Reserved */
    ureg32 PTPQ:3;        /* [6:4] PTP Packets Queue - PTPQ (rw) */
    ureg32 reserved_7:1;  /* [7:7] internal Reserved */
    ureg32 DCBCPQ:3;      /* [10:8] DCB Control Packet Queue */
    ureg32 reserved_11:1; /* [11:11] internal Reserved */
    ureg32 UPQ:3;         /* [14:12] Untagged Packet Queue - UPQ (rw) */
    ureg32 reserved_15:1; /* [15:15] internal Reserved */
    ureg32 MCBCQ:3;       /* [18:16] Multicast and Broadcast Queue - MCBCQ (rw) */
    ureg32 reserved_19:1; /* [19:19] internal Reserved */
    ureg32 MCBCQEN:1;     /* [20:20] Multicast and Broadcast Queue Enable - MCBCQEN (rw) */
    ureg32 TACPQE:1;      /* [21:21] Tagged AV Control Packets Queuing Enable. - TACPQE (rw) */
    ureg32 TPQC:2;        /* [23:22] Tagged PTP over Ethernet Packets Queuing Control - MFFQE (rw) */
    ureg32 FPRQ:3;        /* [26:24] Frame Preemption Residue Queue - FPRQ (rw) */
    ureg32 reserved_27:1; /* [27:27] internal Reserved */
    ureg32 OMCBCQ:1;      /* [28:28] Over-riding MC-BC Queue priority select - OMCBCQ (rw) */
    ureg32 TBRQE:1;       /* [29:29] Type Field Based Rx Queuing Enable - TBRQE (rw) */
    ureg32 reserved_30:2; /* [31:30] internal Reserved */
} ETH_MAC_RXQ_CTRL1_Bits;

/* MAC Receive Queue Control 2 Register */
typedef struct
{
    ureg32 PSRQ0:8; /* [7:0] Priorities Selected in the Receive Queue 0 - PSRQ0 (rw) */
    ureg32 PSRQ1:8; /* [15:8] Priorities Selected in the Receive Queue 1 - PSRQ1 (rw) */
    ureg32 PSRQ2:8; /* [23:16] Priorities Selected in the Receive Queue 2 - PSRQ2 (rw) */
    ureg32 PSRQ3:8; /* [31:24] Priorities Selected in the Receive Queue 3 - PSRQ3 (rw) */
} ETH_MAC_RXQ_CTRL2_Bits;

/* MAC Interrupt Status Register */
typedef struct
{
    ureg32 RGSMIIIS:1;    /* [0:0] RGMII or SMII Interrupt Status - RGSMIIIS (r) */
    ureg32 reserved_1:2;  /* [2:1] internal Reserved */
    ureg32 PHYIS:1;       /* [3:3] PHY Interrupt - PHYIS (r) */
    ureg32 PMTIS:1;       /* [4:4] PMT Interrupt Status - PMTIS (r) */
    ureg32 LPIIS:1;       /* [5:5] LPI Interrupt Status - LPIIS (r) */
    ureg32 reserved_6:2;  /* [7:6] internal Reserved */
    ureg32 MMCIS:1;       /* [8:8] MMC Interrupt Status - MMCIS (r) */
    ureg32 MMCRXIS:1;     /* [9:9] MMC Receive Interrupt Status - MMCRXIS (r) */
    ureg32 MMCTXIS:1;     /* [10:10] MMC Transmit Interrupt Status - MMCTXIS (r) */
    ureg32 MMCRXIPIS:1;   /* [11:11] MMC Receive Checksum Offload Interrupt Status - MMCRXIPIS (r) */
    ureg32 TSIS:1;        /* [12:12] Timestamp Interrupt Status - TSIS (r) */
    ureg32 TXSTSIS:1;     /* [13:13] Transmit Status Interrupt - TXSTSIS (r) */
    ureg32 RXSTSIS:1;     /* [14:14] Receive Status Interrupt - RXSTSIS (r) */
    ureg32 reserved_15:2; /* [16:15] internal Reserved */
    ureg32 FPEIS:1;       /* [17:17] Frame Preemption Interrupt Status (r) */
    ureg32 MDIOIS:1;      /* [18:18] MDIO Interrupt Status - MDIOIS (r) */
    ureg32 MFTIS:1;       /* [19:19] MMC FPE Transmit Interrupt Status (r) */
    ureg32 MFRIS:1;       /* [20:20] MMC FPE Receive Interrupt Status (r) */
    ureg32 reserved_21:2; /* [22:21] internal Reserved */
    ureg32 PCIS:1;        /* [23:23] Policing Counter Interrupt Status (r) */
    ureg32 reserved_24:8; /* [31:24] internal Reserved */
} ETH_MAC_INTERRUPT_STATUS_Bits;

/* MAC Interrupt Enable Register */
typedef struct
{
    ureg32 RGSMIIIE:1;     /* [0:0] RGMII or SMII Interrupt Enable - RGSMIIIE (rw) */
    ureg32 reserved_1:2;   /* [2:1] internal Reserved */
    ureg32 PHYIE:1;        /* [3:3] PHY Interrupt Enable - PHYIE (rw) */
    ureg32 PMTIE:1;        /* [4:4] PMT Interrupt Enable - PMTIE (rw) */
    ureg32 LPIIE:1;        /* [5:5] LPI Interrupt Enable - LPIIE (rw) */
    ureg32 reserved_6:6;   /* [11:6] internal Reserved */
    ureg32 TSIE:1;         /* [12:12] Timestamp Interrupt Enable - TSIE (rw) */
    ureg32 TXSTSIE:1;      /* [13:13] Transmit Status Interrupt Enable - TXSTSIE (rw) */
    ureg32 RXSTSIE:1;      /* [14:14] Receive Status Interrupt Enable - RXSTSIE (rw) */
    ureg32 reserved_15:2;  /* [16:15] internal Reserved */
    ureg32 FPEIE:1;        /* [17:17] Frame Preemption Interrupt Enable (rw) */
    ureg32 MDIOIE:1;       /* [18:18] MDIO Interrupt Enable - MDIOIE (rw) */
    ureg32 reserved_19:13; /* [31:19] internal Reserved */
} ETH_MAC_INTERRUPT_ENABLE_Bits;

/* MAC Receive Transmit Status Register */
typedef struct
{
    ureg32 TJT:1;         /* [0:0] Transmit Jabber Timeout - TJT (r) */
    ureg32 NCARR:1;       /* [1:1] No Carrier - NCARR (r) */
    ureg32 LCARR:1;       /* [2:2] Loss of Carrier - LCARR (r) */
    ureg32 EXDEF:1;       /* [3:3] Excessive Deferral - EXDEF (r) */
    ureg32 LCOL:1;        /* [4:4] Late Collision - LCOL (r) */
    ureg32 EXCOL:1;       /* [5:5] Excessive Collisions - EXCOL (r) */
    ureg32 reserved_6:2;  /* [7:6] internal Reserved */
    ureg32 RWT:1;         /* [8:8] Receive Watchdog Timeout - RWT (r) */
    ureg32 reserved_9:23; /* [31:9] internal Reserved */
} ETH_MAC_RX_TX_STATUS_Bits;

/* MAC PMT Control and Status Register */
typedef struct
{
    ureg32 PWRDWN:1;       /* [0:0] Power Down - PWRDWN (rw) */
    ureg32 MGKPKTEN:1;     /* [1:1] Magic Packet Enable - MGKPKTEN (rw) */
    ureg32 RWKPKTEN:1;     /* [2:2] Remote Wake-Up Packet Enable - RWKPKTEN (rw) */
    ureg32 reserved_3:2;   /* [4:3] internal Reserved */
    ureg32 MGKPRCVD:1;     /* [5:5] Magic Packet Received - MGKPRCVD (r) */
    ureg32 RWKPRCVD:1;     /* [6:6] Remote Wake-Up Packet Received - RWKPRCVD (r) */
    ureg32 reserved_7:2;   /* [8:7] internal Reserved */
    ureg32 GLBLUCAST:1;    /* [9:9] Global Unicast - GLBLUCAST (rw) */
    ureg32 RWKPFE:1;       /* [10:10] Remote Wake-up Packet Forwarding Enable - RWKPFE (rw) */
    ureg32 reserved_11:13; /* [23:11] internal Reserved */
    ureg32 RWKPTR:5;       /* [28:24] Remote Wake-up FIFO Pointer - RWKPTR (r) */
    ureg32 reserved_29:2;  /* [30:29] internal Reserved */
    ureg32 RWKFILTRST:1;   /* [31:31] Remote Wake-Up Packet Filter Register Pointer Reset - RWKFILTRST (rw) */
} ETH_MAC_PMT_CONTROL_STATUS_Bits;

/* MAC Wake-up Filter Command 0 Register */
typedef struct
{
    ureg32 FILTER0_COMMAND:4; /* [3:0] Filter0_Command (rw) */
    ureg32 reserved_4:4;      /* [7:4] internal Reserved */
    ureg32 FILTER1_COMMAND:4; /* [11:8] Filter1_Command (rw) */
    ureg32 reserved_12:4;     /* [15:12] internal Reserved */
    ureg32 FILTER2_COMMAND:4; /* [19:16] Filter2_Command (rw) */
    ureg32 reserved_20:4;     /* [23:20] internal Reserved */
    ureg32 FILTER3_COMMAND:4; /* [27:24] Filter3_Command (rw) */
    ureg32 reserved_28:4;     /* [31:28] internal Reserved */
} ETH_RWK_FILTER_COMMAND_0_Bits;

/* MAC Wake-up Filter Byte Mask register */
typedef struct
{
    ureg32 FILTERI_BYTE_MASK:32; /* [31:0] Filter{i}32-bit Mask - Filteri_Byte_Mask (rw) */
} ETH_RWK_FILTER_BYTE_MASK_Bits;

/* MAC Wake-up Filter CRC Register */
typedef struct
{
    ureg32 FILTER0_CRC:16; /* [15:0] Filter0_CRC (rw) */
    ureg32 FILTER1_CRC:16; /* [31:16] Filter1_CRC (rw) */
} ETH_RWK_FILTER_CRC_Bits;

/* MAC Wake-up Filter Offset 0 Register */
typedef struct
{
    ureg32 FILTER0_OFFSET:8; /* [7:0] Filter0_Offset (rw) */
    ureg32 FILTER1_OFFSET:8; /* [15:8] Filter1_Offset (rw) */
    ureg32 FILTER2_OFFSET:8; /* [23:16] Filter2_Offset (rw) */
    ureg32 FILTER3_OFFSET:8; /* [31:24] Filter3_Offset (rw) */
} ETH_RWK_FILTER_OFFSET_0_Bits;

/* MAC Wake-up Packet Filter Register */
typedef struct
{
    ureg32 WKUPFRMFTR:32; /* [31:0] RWK Packet Filter - WKUPFRMFTR (rw) */
} ETH_MAC_RWK_PACKET_FILTER_Bits;

/* MAC LPI Control and Status Register */
typedef struct
{
    ureg32 TLPIEN:1;       /* [0:0] Transmit LPI Entry - TLPIEN (r) */
    ureg32 TLPIEX:1;       /* [1:1] Transmit LPI Exit - TLPIEX (r) */
    ureg32 RLPIEN:1;       /* [2:2] Receive LPI Entry - RLPIEN (r) */
    ureg32 RLPIEX:1;       /* [3:3] Receive LPI Exit - RLPIEX (r) */
    ureg32 reserved_4:4;   /* [7:4] internal Reserved */
    ureg32 TLPIST:1;       /* [8:8] Transmit LPI State - TLPIST (r) */
    ureg32 RLPIST:1;       /* [9:9] Receive LPI State - RLPIST (r) */
    ureg32 reserved_10:6;  /* [15:10] internal Reserved */
    ureg32 LPIEN:1;        /* [16:16] LPI Enable - LPIEN (rw) */
    ureg32 PLS:1;          /* [17:17] PHY Link Status - PLS (rw) */
    ureg32 PLSEN:1;        /* [18:18] PHY Link Status Enable - PLSEN (rw) */
    ureg32 LPITXA:1;       /* [19:19] LPI Tx Automate - LPITXA (rw) */
    ureg32 LPIATE:1;       /* [20:20] LPI Timer Enable - LPIATE (rw) */
    ureg32 LPITCSE:1;      /* [21:21] LPI Tx Clock Stop Enable - LPITCSE (rw) */
    ureg32 reserved_22:10; /* [31:22] internal Reserved */
} ETH_MAC_LPI_CONTROL_STATUS_Bits;

/* MAC LPI Timers Control Register */
typedef struct
{
    ureg32 TWT:16;        /* [15:0] LPI TW Timer - TWT (rw) */
    ureg32 LST:10;        /* [25:16] LPI LS Timer - LST (rw) */
    ureg32 reserved_26:6; /* [31:26] internal Reserved */
} ETH_MAC_LPI_TIMERS_CONTROL_Bits;

/* MAC LPI Entry Timer Register */
typedef struct
{
    ureg32 reserved_0:3;   /* [2:0] internal Reserved */
    ureg32 LPIET:17;       /* [19:3] LPI Entry Timer - LPIET (rw) */
    ureg32 reserved_20:12; /* [31:20] internal Reserved */
} ETH_MAC_LPI_ENTRY_TIMER_Bits;

/* MAC One Microsecond Tic Counter Register */
typedef struct
{
    ureg32 TIC_1US_CNTR:12; /* [11:0] 1US TIC Counter - TIC_1US_CNTR (rw) */
    ureg32 reserved_12:20;  /* [31:12] internal Reserved */
} ETH_MAC_1US_TIC_COUNTER_Bits;

/* MAC PHY Interface Control and Status Register */
typedef struct
{
    ureg32 TC:1;           /* [0:0] Transmit Configuration in RGMII, SGMII, or SMII - TC (rw) */
    ureg32 LUD:1;          /* [1:1] Link Up or Down - LUD (rw) */
    ureg32 reserved_2:1;   /* [2:2] internal Reserved */
    ureg32 reserved_3:1;   /* [3:3] internal Reserved */
    ureg32 reserved_4:1;   /* [4:4] internal Reserved */
    ureg32 reserved_5:11;  /* [15:5] internal Reserved */
    ureg32 LNKMOD:1;       /* [16:16] Link Mode - LNKMOD (r) */
    ureg32 LNKSPEED:2;     /* [18:17] Link Speed - LNKSPEED (r) */
    ureg32 LNKSTS:1;       /* [19:19] Link Status - LNKSTS (r) */
    ureg32 reserved_20:10; /* [29:20] internal Reserved */
    ureg32 reserved_30:2;  /* [31:30] internal Reserved */
} ETH_MAC_PHYIF_CONTROL_STATUS_Bits;

/* MAC Version Register */
typedef struct
{
    ureg32 SNPSVER:8;      /* [7:0] Synopsys-defined Version - SNPSVER (r) */
    ureg32 USERVER:8;      /* [15:8] User-defined Version (configured with coreConsultant) - USERVER (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MAC_VERSION_Bits;

/* MAC Debug Register */
typedef struct
{
    ureg32 RPESTS:1;       /* [0:0] MAC GMII or MII Receive Protocol Engine Status - RPESTS (r) */
    ureg32 RFCFCSTS:2;     /* [2:1] MAC Receive Packet Controller FIFO Status - RFCFCSTS (r) */
    ureg32 reserved_3:13;  /* [15:3] internal Reserved */
    ureg32 TPESTS:1;       /* [16:16] MAC GMII or MII Transmit Protocol Engine Status - TPESTS (r) */
    ureg32 TFCSTS:2;       /* [18:17] MAC Transmit Packet Controller Status - TFCSTS (r) */
    ureg32 reserved_19:13; /* [31:19] internal Reserved */
} ETH_MAC_DEBUG_Bits;

/* MAC Hardware Feature Register 0 */
typedef struct
{
    ureg32 MIISEL:1;       /* [0:0] 10 or 100 Mbps Support - MIISEL (r) */
    ureg32 GMIISEL:1;      /* [1:1] 1000 Mbps Support - GMIISEL (r) */
    ureg32 HDSEL:1;        /* [2:2] Half-duplex Support - HDSEL (r) */
    ureg32 PCSSEL:1;       /* [3:3] PCS Registers (TBI, SGMII, or RTBI PHY interface) - PCSSEL (r) */
    ureg32 VLHASH:1;       /* [4:4] VLAN Hash Filter Selected - VLHASH (r) */
    ureg32 SMASEL:1;       /* [5:5] SMA (MDIO) Interface - SMASEL (r) */
    ureg32 RWKSEL:1;       /* [6:6] PMT Remote Wake-up Packet Enable - RWKSEL (r) */
    ureg32 MGKSEL:1;       /* [7:7] PMT Magic Packet Enable - MGKSEL (r) */
    ureg32 MMCSEL:1;       /* [8:8] RMON Module Enable - MMCSEL (r) */
    ureg32 ARPOFFSEL:1;    /* [9:9] ARP Offload Enabled - ARPOFFSEL (r) */
    ureg32 reserved_10:2;  /* [11:10] internal Reserved */
    ureg32 TSSEL:1;        /* [12:12] IEEE 1588-2008 Timestamp Enabled - TSSEL (r) */
    ureg32 EEESEL:1;       /* [13:13] Energy Efficient Ethernet Enabled - EEESEL (r) */
    ureg32 TXCOESEL:1;     /* [14:14] Transmit Checksum Offload Enabled - TXCOESEL (r) */
    ureg32 reserved_15:1;  /* [15:15] internal Reserved */
    ureg32 RXCOESEL:1;     /* [16:16] Receive Checksum Offload Enabled - RXCOESEL (r) */
    ureg32 reserved_17:1;  /* [17:17] internal Reserved */
    ureg32 ADDMACADRSEL:5; /* [22:18] MAC Addresses 1-31 Selected - ADDMACADRSEL (r) */
    ureg32 MACADR32SEL:1;  /* [23:23] MAC Addresses 32-63 Selected - MACADR32SEL (r) */
    ureg32 MACADR64SEL:1;  /* [24:24] MAC Addresses 64-127 Selected - MACADR64SEL (r) */
    ureg32 TSSTSSEL:2;     /* [26:25] Timestamp System Time Source - TSSTSSEL (r) */
    ureg32 SAVLANINS:1;    /* [27:27] Source Address or VLAN Insertion Enable - SAVLANINS (r) */
    ureg32 ACTPHYSEL:4;    /* [31:28] Active PHY Selected - ACTPHYSEL (r) */
} ETH_MAC_HW_FEATURE0_Bits;

/* MAC Hardware Feature Register 1 */
typedef struct
{
    ureg32 RXFIFOSIZE:5;  /* [4:0] MTL Receive FIFO Size - RXFIFOSIZE (r) */
    ureg32 SPRAM:1;       /* [5:5] Single Port RAM Enable - SPRAM (r) */
    ureg32 TXFIFOSIZE:5;  /* [10:6] MTL Transmit FIFO Size - TXFIFOSIZE (r) */
    ureg32 OSTEN:1;       /* [11:11] One-Step Timestamping Enable - OSTEN (r) */
    ureg32 PTOEN:1;       /* [12:12] PTP Offload Enable - PTOEN (r) */
    ureg32 ADVTHWORD:1;   /* [13:13] IEEE 1588 High Word Register Enable - ADVTHWORD (r) */
    ureg32 ADDR64:2;      /* [15:14] Address Width. - ADDR64 (r) */
    ureg32 DCBEN:1;       /* [16:16] DCB Feature Enable - DCBEN (r) */
    ureg32 SPHEN:1;       /* [17:17] Split Header Feature Enable - SPHEN (r) */
    ureg32 TSOEN:1;       /* [18:18] TCP Segmentation Offload Enable - TSOEN (r) */
    ureg32 DBGMEMA:1;     /* [19:19] DMA Debug Registers Enable - DBGMEMA (r) */
    ureg32 AVSEL:1;       /* [20:20] AV Feature Enable - AVSEL (r) */
    ureg32 RAVSEL:1;      /* [21:21] Rx Side Only AV Feature Enable - RAVSEL (r) */
    ureg32 reserved_22:1; /* [22:22] internal Reserved */
    ureg32 POUOST:1;      /* [23:23] One Step for PTP over UDP/IP Feature Enable - POUOST (r) */
    ureg32 HASHTBLSZ:2;   /* [25:24] Hash Table Size - HASHTBLSZ (r) */
    ureg32 reserved_26:1; /* [26:26] internal Reserved */
    ureg32 L3L4FNUM:4;    /* [30:27] Total number of L3 or L4 Filters - L3L4FNUM (r) */
    ureg32 reserved_31:1; /* [31:31] internal Reserved */
} ETH_MAC_HW_FEATURE1_Bits;

/* MAC Hardware Feature Register 2 */
typedef struct
{
    ureg32 RXQCNT:4;      /* [3:0] Number of MTL Receive Queues - RXQCNT (r) */
    ureg32 reserved_4:2;  /* [5:4] internal Reserved */
    ureg32 TXQCNT:4;      /* [9:6] Number of MTL Transmit Queues - TXQCNT (r) */
    ureg32 reserved_10:2; /* [11:10] internal Reserved */
    ureg32 RXCHCNT:4;     /* [15:12] Number of DMA Receive Channels - RXCHCNT (r) */
    ureg32 RDCSZ:2;       /* [17:16] Rx DMA Descriptor cache size */
    ureg32 TXCHCNT:4;     /* [21:18] Number of DMA Transmit Channels - TXCHCNT (r) */
    ureg32 TDCSZ:2;       /* [23:22] Tx DMA Descriptor cache size */
    ureg32 PPSOUTNUM:3;   /* [26:24] Number of PPS Outputs - PPSOUTNUM (r) */
    ureg32 reserved_27:1; /* [27:27] internal Reserved */
    ureg32 AUXSNAPNUM:3;  /* [30:28] Number of Auxiliary Snapshot Inputs - AUXSNAPNUM (r) */
    ureg32 reserved_31:1; /* [31:31] internal Reserved */
} ETH_MAC_HW_FEATURE2_Bits;

/* MAC Hardware Feature Register 3 */
typedef struct
{
    ureg32 NRVF:3;        /* [2:0] Number of Extended VLAN Tag Filters Enabled - NRVF (r) */
    ureg32 reserved_3:1;  /* [3:3] internal Reserved */
    ureg32 CBTISEL:1;     /* [4:4] Queue/Channel based VLAN tag insertion on Tx Enable - CBTISEL (r) */
    ureg32 DVLAN:1;       /* [5:5] DVLAN (r) */
    ureg32 reserved_6:3;  /* [8:6] internal Reserved */
    ureg32 PDUPSEL:1;     /* [9:9] PDUPSEL (r) */
    ureg32 FRPSEL:1;      /* [10:10] PDUPSEL (r) */
    ureg32 FRPBS:2;       /* [12:11] FRPBS (r) */
    ureg32 FRPES:2;       /* [14:13] FRPES (r) */
    ureg32 reserved_15:1; /* [15:15] internal Reserved */
    ureg32 ESTSEL:1;      /* [16:16] ESTSEL (r) */
    ureg32 ESTDEP:3;      /* [19:17] ESTDEP (r) */
    ureg32 ESTWID:2;      /* [21:20] ESTWID (r) */
    ureg32 reserved_22:4; /* [25:22] internal Reserved */
    ureg32 FPESEL:1;      /* [26:26] FPESEL (r) */
    ureg32 TBSSEL:1;      /* [27:27] TBSSEL (r) */
    ureg32 ASP:2;         /* [29:28] ASP (r) */
    ureg32 reserved_30:2; /* [31:30] internal Reserved */
} ETH_MAC_HW_FEATURE3_Bits;

/* MAC Hardware Feature Register 4 */
typedef struct
{
    ureg32 PCSEL:2;       /*[1:0] Number of Extended VLAN Tag Filters Enabled - NRVF (r) */
    ureg32 reserved_2:30; /*[31:2] internal Reserved */
} ETH_MAC_HW_FEATURE4_Bits;

/* MAC DPP FSM Interrupt Status Register */
typedef struct
{
    ureg32 reserved_0:1;  /* [0:0] Application Transmit Interface Parity checker Error Status(r/w) */
    ureg32 reserved_1:1;  /* [1:1] TSO data path Parity checker Error Status(r/w) */
    ureg32 RDPES:1;       /* [2:2] Read Descriptor Parity checker Error Status(r/w) */
    ureg32 MPES:1;        /* [3:3] MTL data path Parity checker Error Status(r/w) */
    ureg32 MTSPES:1;      /* [4:4] MTL TX Status data path Parity checker Error Status(r/w) */
    ureg32 ARPES:1;       /* [5:5] Application Receive interface data path Parity Error Status(r/w) */
    ureg32 reserved_6:1;  /* [6:6] CSR Write data path Parity checker Error Status(r/w) */
    ureg32 reserved_7:1;  /* [7:7] AXI Slave Read data path Parity checker Error Status (r/w) */
    ureg32 TTES:1;        /* [8:8] Tx FSM  Timeout Error Status (r/w) */
    ureg32 RTES:1;        /* [9:9] Rx FSM  Timeout Error Status (r/w) */
    ureg32 CTES:1;        /* [10:10] CSR FSM  Timeout Error Status (r/w) */
    ureg32 ATES:1;        /* [11:11] APP FSM  Timeout Error Status (r/w) */
    ureg32 PTES:1;        /* [12:12] PTP FSM  Timeout Error Status (r/w) */
    ureg32 reserved_13:1; /* [13:13] Tx125 FSM Timeout Error Status (r/w) */
    ureg32 reserved_14:1; /* [14:14] Rx125 FSM Timeout Error Status (r/w) */
    ureg32 reserved_15:1; /* [15:15] REV MDC FSM Timeout Error Status (r/w) */
    ureg32 MSTTES:1;      /* [16:16] Master Read/Write Timeout Error Status (r/w) */
    ureg32 SLVTES:1;      /* [17:17] Slave Read/Write Timeout Error Status (r/w) */
    ureg32 reserved_18:6; /* [23:18] internal Reserved */
    ureg32 FSMPES:1;      /* [24:24] FSM State Parity Error Status(r/w) */
    ureg32 MTBUPES:1;     /* [25:25] MAC TBU data path Parity checker Error Status */
    ureg32 MTFCPES:1;     /* [26:26] MAC TFC data path Parity checker Error Status */
    ureg32 MRWCPES:1;     /* [27:27] MTL RWC data path Parity checker Error Status */
    ureg32 reserved_28:4; /* [31:28] internal Reserved */
} ETH_MAC_DPP_FSM_INTERRUPT_STATUS_Bits;

/* FSM Control Register */
typedef struct
{
    ureg32 TMOUTEN:1;     /* [0:0]  FSM timeout feature(r/w) */
    ureg32 PRTYEN:1;      /* [1:1] FSM parity feature is enabled.(r/w) */
    ureg32 reserved_2:6;  /* [7:2] Read Descriptor Parity checker Error Status(r/w) */
    ureg32 TTEIN:1;       /* [8:8] Tx FSM  Timeout Error Injection (r/w) */
    ureg32 RTEIN:1;       /* [9:9] Rx FSM  Timeout Error Injection (r/w) */
    ureg32 CTEIN:1;       /* [10:10] CSR FSM  Timeout Error Injection (r/w) */
    ureg32 ATEIN:1;       /* [11:11] APP FSM  Timeout Error Injection (r/w) */
    ureg32 PTEIN:1;       /* [12:12] PTP FSM  Timeout Error Injection (r/w) */
    ureg32 reserved_13:3; /* [15:13] internal Reserved */
    ureg32 TPEIN:1;       /* [16:16] Tx FSM Parity Error Injection (r/w) */
    ureg32 RPEIN:1;       /* [17:17] Rx FSM Parity Error Injection (r/w) */
    ureg32 CPEIN:1;       /* [18:18] CSR FSM Parity Error Injection */
    ureg32 APEIN:1;       /* [19:19] APP FSM Parity Error Injection */
    ureg32 PPEIN:1;       /* [20:20] PTP FSM Parity Error Injection */
    ureg32 reserved_21:3; /* [23:21] internal Reserved */
    ureg32 TLGRNML:1;     /* [24:24] Tx Large/Normal Mode Select(r/w) */
    ureg32 RLGRNML:1;     /* [25:25] Rx Large/Normal Mode Select */
    ureg32 CLGRNML:1;     /* [26:26] CSR Large/Normal Mode Select */
    ureg32 ALGRNML:1;     /* [27:27] APP Large/Normal Mode Select */
    ureg32 PLGRNML:1;     /* [28:28] PTP Large/Normal Mode Select */
    ureg32 reserved_29:3; /* [31:29] internal Reserved */
} ETH_MAC_FSM_CONTROL_Bits;

/* FSM and Interface Timeout values Register */
typedef struct
{
    ureg32 TMR:10;        /* [9:0] number of CSR clocks required  (rw) */
    ureg32 reserved_10:6; /* [15:10] internal Reserved */
    ureg32 NTMRMD:4;      /* [19:16] The timeout duration based on the mode value is given (rw) */
    ureg32 LTMRMD:4;      /* [23:20] The timeout duration based on the mode value is given (rw) */
    ureg32 reserved_24:8; /* [31:24] internal Reserved */
} ETH_MAC_FSM_ACT_TIMER_Bits;

/* MAC MDIO Address Register */
typedef struct
{
    ureg32 GB:1;          /* [0:0] GMII Busy - GB (rw) */
    ureg32 C45E:1;        /* [1:1] Clause 45 PHY Enable - C45E (rw) */
    ureg32 GOC_0:1;       /* [2:2] GMII Operation Command 0 - GOC_0 (rw) */
    ureg32 GOC_1:1;       /* [3:3] GMII Operation Command 1 - GOC_1 (rw) */
    ureg32 SKAP:1;        /* [4:4] Skip Address Packet - SKAP (rw) */
    ureg32 reserved_5:3;  /* [7:5] internal Reserved */
    ureg32 CR:4;          /* [11:8] CSR Clock Range - CR (rw) */
    ureg32 NTC:3;         /* [14:12] Number of Trailing Clocks - NTC (rw) */
    ureg32 reserved_15:1; /* [15:15] internal Reserved */
    ureg32 RDA:5;         /* [20:16] Register/Device Address - RDA (rw) */
    ureg32 PA:5;          /* [25:21] Physical Layer Address - PA (rw) */
    ureg32 BTB:1;         /* [26:26] Back to Back transactions - BTB (rw) */
    ureg32 PSE:1;         /* [27:27] Preamble Suppression Enable - PSE (rw) */
    ureg32 reserved_28:4; /* [31:28] internal Reserved */
} ETH_MAC_MDIO_ADDRESS_Bits;

/* MAC MDIO Data Register */
typedef struct
{
    ureg32 GD:16; /* [15:0] GMII Data - GD (rw) */
    ureg32 RA:16; /* [31:16] Register Address - RA (rw) */
} ETH_MAC_MDIO_DATA_Bits;

/* The GPIO Control register */
typedef struct
{
    ureg32 GPIE:4;        /* [3:0] GPI Interrupt Enable (rw) */
    ureg32 reserved_4:12; /* [15:4] internal Reserved */
    ureg32 GPIT:16;       /* [31:16] GPI Type */
} ETH_MAC_GPIO_CONTROL_Bits;

/* The General Purpose IO Status register */
typedef struct
{
    ureg32 GPIS:16; /* [x:0] General Purpose Input Status (rw) */
                    /* [15:4] internal Reserved */
    ureg32 GPO:16;  /* [x:16] General Purpose Output(rw) */
                    /* [31:y] internal Reserved */
} ETH_MAC_GPIO_STATUS_Bits;

/* The ARP Address register */
typedef struct
{
    ureg32 ARPPA:32; /* [31:0] used for perfect match with the Protocol
                                 Address of Target field in the received ARP packet. (rw) */
} ETH_MAC_ARP_ADDRESS_Bits;

/* MAC CSR Software Controls Register */
typedef struct
{
    ureg32 RCWE:1;        /* [0:0] Register Clear on Write 1 Enable - RCWE (rw) */
    ureg32 reserved_1:7;  /* [7:1] internal Reserved */
    ureg32 SEEN:1;        /* [8:8] Slave Error Response Enable - SEEN (rw) */
    ureg32 reserved_9:23; /* [31:9] internal Reserved */
} ETH_MAC_CSR_SW_CTRL_Bits;

/* MAC_FPE_CTRL_STS Register*/
typedef struct
{
    ureg32 EFPE:1;         /* [0:0] Enable Tx Frame Preemption (rw) */
    ureg32 SVER:1;         /* [1:1] Send Verify mPacket (rw) */
    ureg32 SRSP:1;         /* [2:2] Send Respond mPacket(rw) */
    ureg32 ARV:1;          /* [3:3] Autogenerate respond mPacket on receiving mPacket */
    ureg32 S1_SET_0:1;     /* [4:4] Synopsys Reserved, Must be set to "0". (rw) */
    ureg32 reserved_4:11;  /* [15:5] internal Reserved */
    ureg32 RVER:1;         /* [16:16] Received Verify Frame (rw) */
    ureg32 RRSP:1;         /* [17:17] Received Respond Frame (rw) */
    ureg32 TVER:1;         /* [18:18] Transmitted Verify Frame (rw) */
    ureg32 TRSP:1;         /* [19:19] Transmitted Respond Frame (rw) */
    ureg32 reserved_20:12; /* [31:20] internal Reserved */
} ETH_MAC_FPE_CTRL_STS_Bits;

/* MAC Extended Configuration Register 1 */
typedef struct
{
    ureg32 SPLOFST:7;     /* [6:0] Split Offset - SPLOFST (rw) */
    ureg32 reserved_7:1;  /* [7:7] internal Reserved */
    ureg32 SPLM:2;        /* [9:8] Split Mode - SPLM (rw) */
    ureg32 reserved_10:6; /* [15:10] internal Reserved */
    ureg32 SAVO:7;        /* [22:16] Split AV Offset - SAVO (rw) */
    ureg32 reserved_23:1; /* [23:23] internal Reserved */
    ureg32 SAVE:1;        /* [24:24] Split AV Enable - SAVE (rw) */
    ureg32 reserved_25:7; /* [31:25] internal Reserved */
} ETH_MAC_EXT_CFG1_Bits;

/*MAC_Presn_Time_ns Register*/
typedef struct
{
    ureg32 MPTN:32; /* [31:0] MAC 1722 Presentation Time in ns (r) */
} ETH_MAC_PRESN_TIME_NS_Bits;

/*MAC_Presn_Time_ns Register*/
typedef struct
{
    ureg32 MPTU:32; /* [31:0] MAC 1722 Presentation Time Update in ns (r) */
} ETH_MAC_PRESN_TIME_UPDT_Bits;

/* MAC Address 0 High Register */
typedef struct
{
    ureg32 ADDRHI:16;      /* [15:0] MAC Address0[47:32] - ADDRHI (rw) */
    ureg32 DCS:2;          /* [17:16] DMA Channel Select - DCS (rw) */
    ureg32 reserved_18:13; /* [30:18] internal Reserved */
    ureg32 AE:1;           /* [31:31] Address Enable - AE (r) , always 1*/
} ETH_MAC_ADDRESS_HIGH0_Bits;

/* MAC Address 0 Low Register */
typedef struct
{
    ureg32 ADDRLO:32; /* [31:0] MAC Address0[31:0] - ADDRLO (rw) */
} ETH_MAC_ADDRESS_LOW0_Bits;

/* MAC Address High Register */
typedef struct
{
    ureg32 ADDRHI:16;     /* [15:0] MAC Address1 [47:32] - ADDRHI (rw) */
    ureg32 DCS:2;         /* [17:16] DMA Channel Select - DCS (rw) */
    ureg32 reserved_18:6; /* [23:18] internal Reserved */
    ureg32 MBC:6;         /* [29:24] Mask Byte Control - MBC (rw) */
    ureg32 SA:1;          /* [30:30] Source Address - SA (rw) */
    ureg32 AE:1;          /* [31:31] Address Enable - AE (rw) */
} ETH_MAC_ADDRESS_HIGH_Bits;

/* MAC Address Low Register */
typedef struct
{
    ureg32 ADDRLO:32; /* [31:0] MAC Address1 [31:0] - ADDRLO (rw) */
} ETH_MAC_ADDRESS_LOW_Bits;

/* MMC Control Register */
typedef struct
{
    ureg32 CNTRST:1;      /* [0:0] Counters Reset - CNTRST (rw) */
    ureg32 CNTSTOPRO:1;   /* [1:1] Counter Stop Rollover - CNTSTOPRO (rw) */
    ureg32 RSTONRD:1;     /* [2:2] Reset on Read - RSTONRD (rw) */
    ureg32 CNTFREEZ:1;    /* [3:3] MMC Counter Freeze - CNTFREEZ (rw) */
    ureg32 CNTPRST:1;     /* [4:4] Counters Preset - CNTPRST (rw) */
    ureg32 CNTPRSTLVL:1;  /* [5:5] Full-Half Preset - CNTPRSTLVL (rw) */
    ureg32 reserved_6:2;  /* [7:6] internal Reserved */
    ureg32 UCDBC:1;       /* [8:8] Update MMC Counters for Dropped Broadcast Packets - UCDBC (rw) */
    ureg32 reserved_9:23; /* [31:9] internal Reserved */
} ETH_MMC_CONTROL_Bits;

/* MMC Receive Interrupts Register */
typedef struct
{
    ureg32 RXGBPKTIS:1;    /* [0:0] MMC Receive Good Bad Packet Counter Interrupt Status - RXGBPKTIS (r) */
    ureg32 RXGBOCTIS:1;    /* [1:1] MMC Receive Good Bad Octet Counter Interrupt Status - RXGBOCTIS (r) */
    ureg32 RXGOCTIS:1;     /* [2:2] MMC Receive Good Octet Counter Interrupt Status - RXGOCTIS (r) */
    ureg32 RXBCGPIS:1;     /* [3:3] MMC Receive Broadcast Good Packet Counter Interrupt Status - RXBCGPIS (r) */
    ureg32 RXMCGPIS:1;     /* [4:4] MMC Receive Multicast Good Packet Counter Interrupt Status - RXMCGPIS (r) */
    ureg32 RXCRCERPIS:1;   /* [5:5] MMC Receive CRC Error Packet Counter Interrupt Status - RXCRCERPIS (r) */
    ureg32 RXALGNERPIS:1;  /* [6:6] MMC Receive Alignment Error Packet Counter Interrupt Status - RXALGNERPIS (r) */
    ureg32 RXRUNTPIS:1;    /* [7:7] MMC Receive Runt Packet Counter Interrupt Status - RXRUNTPIS (r) */
    ureg32 RXJABERPIS:1;   /* [8:8] MMC Receive Jabber Error Packet Counter Interrupt Status - RXJABERPIS (r) */
    ureg32 RXUSIZEGPIS:1;  /* [9:9] MMC Receive Undersize Good Packet Counter Interrupt Status - RXUSIZEGPIS (r) */
    ureg32 RXOSIZEGPIS:1;  /* [10:10] MMC Receive Oversize Good Packet Counter Interrupt Status - RXOSIZEGPIS (r) */
    ureg32 RX64OCTGBPIS:1; /* [11:11] MMC Receive 64 Octet Good Bad Packet Counter Interrupt Status - RX64OCTGBPIS) */
    ureg32 RX65T127OCTGBPIS:1;   /* [12:12] MMC Receive 65 to 127 Octet Good Bad Packet Counter Interrupt Status -
                                    RX65T127OCTGBPIS (r) */
    ureg32 RX128T255OCTGBPIS:1;  /* [13:13] MMC Receive 128 to 255 Octet Good Bad Packet Counter Interrupt Status -
                                    RX128T255OCTGBPIS (r) */
    ureg32 RX256T511OCTGBPIS:1;  /* [14:14] MMC Receive 256 to 511 Octet Good Bad Packet Counter Interrupt Status -
                                    RX256T511OCTGBPIS (r) */
    ureg32 RX512T1023OCTGBPIS:1; /* [15:15] MMC Receive 512 to 1023 Octet Good Bad Packet Counter Interrupt Status -
                                    RX512T1023OCTGBPIS (r) */
    ureg32 RX1024TMAXOCTGBPIS:1; /* [16:16] MMC Receive 1024 to Maximum Octet Good Bad Packet Counter Interrupt Status
                                    RX1024TMAXOCTGBPIS (r) */
    ureg32 RXUCGPIS:1;           /* [17:17] MMC Receive Unicast Good Packet Counter Interrupt Status - RXUCGPIS (r) */
    ureg32 RXLENERPIS:1;         /* [18:18] MMC Receive Length Error Packet Counter Interrupt Status - RXLENERPIS(r) */
    ureg32 RXORANGEPIS:1; /* [19:19] MMC Receive Out Of Range Error Packet Counter Interrupt Status. - RXORANGEPIS */
    ureg32 RXPAUSPIS:1;   /* [20:20] MMC Receive Pause Packet Counter Interrupt Status - RXPAUSPIS (r) */
    ureg32 RXFOVPIS:1;    /* [21:21] MMC Receive FIFO Overflow Packet Counter Interrupt Status - RXFOVPIS (r) */
    ureg32 RXVLANGBPIS:1; /* [22:22] MMC Receive VLAN Good Bad Packet Counter Interrupt Status - RXVLANGBPIS (r) */
    ureg32 RXWDOGPIS:1;   /* [23:23] MMC Receive Watchdog Error Packet Counter Interrupt Status - RXWDOGPIS (r) */
    ureg32 RXRCVERRPIS:1; /* [24:24] MMC Receive Error Packet Counter Interrupt Status - RXRCVERRPIS (r) */
    ureg32 RXCTRLPIS:1;   /* [25:25] MMC Receive Control Packet Counter Interrupt Status - RXCTRLPIS (r) */
    ureg32 RXLPIUSCIS:1;  /* [26:26] MMC Receive LPI microsecond counter interrupt status - RXLPIUSCIS (r) */
    ureg32 RXLPITRCIS:1;  /* [27:27] MMC Receive LPI transition counter interrupt status - RXLPITRCIS (r) */
    ureg32 reserved_28:4; /* [31:28] internal Reserved */
} ETH_MMC_RX_INTERRUPT_Bits;

/* MMC Transmit Interrupts Register */
typedef struct
{
    ureg32 TXGBOCTIS:1;    /* [0:0] MMC Transmit Good Bad Octet Counter Interrupt Status - TXGBOCTIS (r) */
    ureg32 TXGBPKTIS:1;    /* [1:1] MMC Transmit Good Bad Packet Counter Interrupt Status - TXGBPKTIS (r) */
    ureg32 TXBCGPIS:1;     /* [2:2] MMC Transmit Broadcast Good Packet Counter Interrupt Status - TXBCGPIS (r) */
    ureg32 TXMCGPIS:1;     /* [3:3] MMC Transmit Multicast Good Packet Counter Interrupt Status - TXMCGPIS (r) */
    ureg32 TX64OCTGBPIS:1; /* [4:4] MMC Transmit 64 Octet Good Bad Packet Counter Interrupt Status - TX64OCTGBPIS(r) */
    ureg32 TX65T127OCTGBPIS:1;   /* [5:5] MMC Transmit 65 to 127 Octet Good Bad Packet Counter Interrupt Status -
                                    TX65T127OCTGBPIS (r) */
    ureg32 TX128T255OCTGBPIS:1;  /* [6:6] MMC Transmit 128 to 255 Octet Good Bad Packet Counter Interrupt Status -
                                    TX128T255OCTGBPIS (r) */
    ureg32 TX256T511OCTGBPIS:1;  /* [7:7] MMC Transmit 256 to 511 Octet Good Bad Packet Counter Interrupt Status -
                                    TX256T511OCTGBPIS (r) */
    ureg32 TX512T1023OCTGBPIS:1; /* [8:8] MMC Transmit 512 to 1023 Octet Good Bad Packet Counter Interrupt Status -
                                    TX512T1023OCTGBPIS (r) */
    ureg32 TX1024TMAXOCTGBPIS:1; /* [9:9] MMC Transmit 1024 to Maximum Octet Good Bad Packet Counter Interrupt Status -
                                    TX1024TMAXOCTGBPIS (r) */
    ureg32 TXUCGBPIS:1;    /* [10:10] MMC Transmit Unicast Good Bad Packet Counter Interrupt Status - TXUCGBPIS (r) */
    ureg32 TXMCGBPIS:1;    /* [11:11] MMC Transmit Multicast Good Bad Packet Counter Interrupt Status - TXMCGBPIS(r) */
    ureg32 TXBCGBPIS:1;    /* [12:12] MMC Transmit Broadcast Good Bad Packet Counter Interrupt Status - TXBCGBPIS(r) */
    ureg32 TXUFLOWERPIS:1; /* [13:13] MMC Transmit Underflow Error Packet Counter Interrupt Status - TXUFLOWERPIS(r) */
    ureg32 TXSCOLGPIS:1;   /* [14:14] MMC Transmit Single Collision Good Packet Counter Interrupt Status - TXSCOLGPIS */
    ureg32 TXMCOLGPIS:1;   /* [15:15] MMC Transmit Multiple Collision Good Packet Counter Interrupt Status - TXMCOLGPIS
                              (r) */
    ureg32 TXDEFPIS:1;     /* [16:16] MMC Transmit Deferred Packet Counter Interrupt Status - TXDEFPIS (r) */
    ureg32 TXLATCOLPIS:1;  /* [17:17] MMC Transmit Late Collision Packet Counter Interrupt Status - TXLATCOLPIS (r) */
    ureg32 TXEXCOLPIS:1;  /* [18:18] MMC Transmit Excessive Collision Packet Counter Interrupt Status - TXEXCOLPIS(r) */
    ureg32 TXCARERPIS:1;  /* [19:19] MMC Transmit Carrier Error Packet Counter Interrupt Status - TXCARERPIS (r) */
    ureg32 TXGOCTIS:1;    /* [20:20] MMC Transmit Good Octet Counter Interrupt Status - TXGOCTIS (r) */
    ureg32 TXGPKTIS:1;    /* [21:21] MMC Transmit Good Packet Counter Interrupt Status - TXGPKTIS (r) */
    ureg32 TXEXDEFPIS:1;  /* [22:22] MMC Transmit Excessive Deferral Packet Counter Interrupt Status - TXEXDEFPIS (r) */
    ureg32 TXPAUSPIS:1;   /* [23:23] MMC Transmit Pause Packet Counter Interrupt Status - TXPAUSPIS (r) */
    ureg32 TXVLANGPIS:1;  /* [24:24] MMC Transmit VLAN Good Packet Counter Interrupt Status - TXVLANGPIS (r) */
    ureg32 TXOSIZEGPIS:1; /* [25:25] MMC Transmit Oversize Good Packet Counter Interrupt Status - TXOSIZEGPIS (r) */
    ureg32 TXLPIUSCIS:1;  /* [26:26] MMC Transmit LPI microsecond counter interrupt status - TXLPIUSCIS (r) */
    ureg32 TXLPITRCIS:1;  /* [27:27] MMC Transmit LPI transition counter interrupt status - TXLPITRCIS (r) */
    ureg32 reserved_28:4; /* [31:28] internal Reserved */
} ETH_MMC_TX_INTERRUPT_Bits;

/* MMC Receive Interrupts Mask Register */
typedef struct
{
    ureg32 RXGBPKTIM:1;    /* [0:0] MMC Receive Good Bad Packet Counter Interrupt Mask - RXGBPKTIM (rw) */
    ureg32 RXGBOCTIM:1;    /* [1:1] MMC Receive Good Bad Octet Counter Interrupt Mask - RXGBOCTIM (rw) */
    ureg32 RXGOCTIM:1;     /* [2:2] MMC Receive Good Octet Counter Interrupt Mask - RXGOCTIM (rw) */
    ureg32 RXBCGPIM:1;     /* [3:3] MMC Receive Broadcast Good Packet Counter Interrupt Mask - RXBCGPIM (rw) */
    ureg32 RXMCGPIM:1;     /* [4:4] MMC Receive Multicast Good Packet Counter Interrupt Mask - RXMCGPIM (rw) */
    ureg32 RXCRCERPIM:1;   /* [5:5] MMC Receive CRC Error Packet Counter Interrupt Mask - RXCRCERPIM (rw) */
    ureg32 RXALGNERPIM:1;  /* [6:6] MMC Receive Alignment Error Packet Counter Interrupt Mask - RXALGNERPIM (rw) */
    ureg32 RXRUNTPIM:1;    /* [7:7] MMC Receive Runt Packet Counter Interrupt Mask - RXRUNTPIM (rw) */
    ureg32 RXJABERPIM:1;   /* [8:8] MMC Receive Jabber Error Packet Counter Interrupt Mask - RXJABERPIM (rw) */
    ureg32 RXUSIZEGPIM:1;  /* [9:9] MMC Receive Undersize Good Packet Counter Interrupt Mask - RXUSIZEGPIM (rw) */
    ureg32 RXOSIZEGPIM:1;  /* [10:10] MMC Receive Oversize Good Packet Counter Interrupt Mask - RXOSIZEGPIM (rw) */
    ureg32 RX64OCTGBPIM:1; /* [11:11] MMC Receive 64 Octet Good Bad Packet Counter Interrupt Mask - RX64OCTGBPIM(rw) */
    ureg32 RX65T127OCTGBPIM:1;   /* [12:12] MMC Receive 65 to 127 Octet Good Bad Packet Counter Interrupt Mask -
                                    RX65T127OCTGBPIM (rw) */
    ureg32 RX128T255OCTGBPIM:1;  /* [13:13] MMC Receive 128 to 255 Octet Good Bad Packet Counter Interrupt Mask -
                                    RX128T255OCTGBPIM (rw) */
    ureg32 RX256T511OCTGBPIM:1;  /* [14:14] MMC Receive 256 to 511 Octet Good Bad Packet Counter Interrupt Mask -
                                    RX256T511OCTGBPIM (rw) */
    ureg32 RX512T1023OCTGBPIM:1; /* [15:15] MMC Receive 512 to 1023 Octet Good Bad Packet Counter Interrupt Mask -
                                    RX512T1023OCTGBPIM (rw) */
    ureg32 RX1024TMAXOCTGBPIM:1; /* [16:16] MMC Receive 1024 to Maximum Octet Good Bad Packet Counter Interrupt Mask -
                                    RX1024TMAXOCTGBPIM (rw) */
    ureg32 RXUCGPIM:1;           /* [17:17] MMC Receive Unicast Good Packet Counter Interrupt Mask - RXUCGPIM (rw) */
    ureg32 RXLENERPIM:1;         /* [18:18] MMC Receive Length Error Packet Counter Interrupt Mask - RXLENERPIM(rw) */
    ureg32 RXORANGEPIM:1; /* [19:19] MMC Receive Out Of Range Error Packet Counter Interrupt Mask - RXORANGEPIM(rw) */
    ureg32 RXPAUSPIM:1;   /* [20:20] MMC Receive Pause Packet Counter Interrupt Mask - RXPAUSPIM (rw) */
    ureg32 RXFOVPIM:1;    /* [21:21] MMC Receive FIFO Overflow Packet Counter Interrupt Mask - RXFOVPIM (rw) */
    ureg32 RXVLANGBPIM:1; /* [22:22] MMC Receive VLAN Good Bad Packet Counter Interrupt Mask - RXVLANGBPIM (rw) */
    ureg32 RXWDOGPIM:1;   /* [23:23] MMC Receive Watchdog Error Packet Counter Interrupt Mask - RXWDOGPIM (rw) */
    ureg32 RXRCVERRPIM:1; /* [24:24] MMC Receive Error Packet Counter Interrupt Mask - RXRCVERRPIM (rw) */
    ureg32 RXCTRLPIM:1;   /* [25:25] MMC Receive Control Packet Counter Interrupt Mask - RXCTRLPIM (rw) */
    ureg32 RXLPIUSCIM:1;  /* [26:26] MMC Receive LPI microsecond counter interrupt Mask - RXLPIUSCIM (rw) */
    ureg32 RXLPITRCIM:1;  /* [27:27] MMC Receive LPI transition counter interrupt Mask - RXLPITRCIM (rw) */
    ureg32 reserved_28:4; /* [31:28] internal Reserved */
} ETH_MMC_RX_INTERRUPT_MASK_Bits;

/* MMC Transmit Interrupts Mask Register */
typedef struct
{
    ureg32 TXGBOCTIM:1;    /* [0:0] MMC Transmit Good Bad Octet Counter Interrupt Mask - TXGBOCTIM (rw) */
    ureg32 TXGBPKTIM:1;    /* [1:1] MMC Transmit Good Bad Packet Counter Interrupt Mask - TXGBPKTIM (rw) */
    ureg32 TXBCGPIM:1;     /* [2:2] MMC Transmit Broadcast Good Packet Counter Interrupt Mask - TXBCGPIM (rw) */
    ureg32 TXMCGPIM:1;     /* [3:3] MMC Transmit Multicast Good Packet Counter Interrupt Mask - TXMCGPIM (rw) */
    ureg32 TX64OCTGBPIM:1; /* [4:4] MMC Transmit 64 Octet Good Bad Packet Counter Interrupt Mask - TX64OCTGBPIM (rw) */
    ureg32 TX65T127OCTGBPIM:1;   /* [5:5] MMC Transmit 65 to 127 Octet Good Bad Packet Counter Interrupt Mask -
                                    TX65T127OCTGBPIM (rw) */
    ureg32 TX128T255OCTGBPIM:1;  /* [6:6] MMC Transmit 128 to 255 Octet Good Bad Packet Counter Interrupt Mask -
                                    TX128T255OCTGBPIM (rw) */
    ureg32 TX256T511OCTGBPIM:1;  /* [7:7] MMC Transmit 256 to 511 Octet Good Bad Packet Counter Interrupt Mask -
                                    TX256T511OCTGBPIM (rw) */
    ureg32 TX512T1023OCTGBPIM:1; /* [8:8] MMC Transmit 512 to 1023 Octet Good Bad Packet Counter Interrupt Mask -
                                    TX512T1023OCTGBPIM (rw) */
    ureg32 TX1024TMAXOCTGBPIM:1; /* [9:9] MMC Transmit 1024 to Maximum Octet Good Bad Packet Counter Interrupt Mask -
                                    TX1024TMAXOCTGBPIM (rw) */
    ureg32 TXUCGBPIM:1;    /* [10:10] MMC Transmit Unicast Good Bad Packet Counter Interrupt Mask - TXUCGBPIM (rw) */
    ureg32 TXMCGBPIM:1;    /* [11:11] MMC Transmit Multicast Good Bad Packet Counter Interrupt Mask - TXMCGBPIM (rw) */
    ureg32 TXBCGBPIM:1;    /* [12:12] MMC Transmit Broadcast Good Bad Packet Counter Interrupt Mask - TXBCGBPIM (rw) */
    ureg32 TXUFLOWERPIM:1; /* [13:13] MMC Transmit Underflow Error Packet Counter Interrupt Mask - TXUFLOWERPIM (rw) */
    ureg32 TXSCOLGPIM:1;   /* [14:14] MMC Transmit Single Collision Good Packet Counter Interrupt Mask - TXSCOLGPIM */
    ureg32 TXMCOLGPIM:1;   /* [15:15] MMC Transmit Multiple Collision Good Packet Counter Interrupt Mask - TXMCOLGPIM */
    ureg32 TXDEFPIM:1;     /* [16:16] MMC Transmit Deferred Packet Counter Interrupt Mask - TXDEFPIM (rw) */
    ureg32 TXLATCOLPIM:1;  /* [17:17] MMC Transmit Late Collision Packet Counter Interrupt Mask - TXLATCOLPIM (rw) */
    ureg32 TXEXCOLPIM:1;   /* [18:18] MMC Transmit Excessive Collision Packet Counter Interrupt Mask - TXEXCOLPIM(rw) */
    ureg32 TXCARERPIM:1;   /* [19:19] MMC Transmit Carrier Error Packet Counter Interrupt Mask - TXCARERPIM (rw) */
    ureg32 TXGOCTIM:1;     /* [20:20] MMC Transmit Good Octet Counter Interrupt Mask - TXGOCTIM (rw) */
    ureg32 TXGPKTIM:1;     /* [21:21] MMC Transmit Good Packet Counter Interrupt Mask - TXGPKTIM (rw) */
    ureg32 TXEXDEFPIM:1;   /* [22:22] MMC Transmit Excessive Deferral Packet Counter Interrupt Mask - TXEXDEFPIM (rw) */
    ureg32 TXPAUSPIM:1;    /* [23:23] MMC Transmit Pause Packet Counter Interrupt Mask - TXPAUSPIM (rw) */
    ureg32 TXVLANGPIM:1;   /* [24:24] MMC Transmit VLAN Good Packet Counter Interrupt Mask - TXVLANGPIM (rw) */
    ureg32 TXOSIZEGPIM:1;  /* [25:25] MMC Transmit Oversize Good Packet Counter Interrupt Mask - TXOSIZEGPIM (rw) */
    ureg32 TXLPIUSCIM:1;   /* [26:26] MMC Transmit LPI microsecond counter interrupt Mask - TXLPIUSCIM (rw) */
    ureg32 TXLPITRCIM:1;   /* [27:27] MMC Transmit LPI transition counter interrupt Mask - TXLPITRCIM (rw) */
    ureg32 reserved_28:4;  /* [31:28] internal Reserved */
} ETH_MMC_TX_INTERRUPT_MASK_Bits;

/* Good And Bad Transmitted Octet Count Register */
typedef struct
{
    ureg32 TXOCTGB:32; /* [31:0] Tx Octet Count Good Bad - TXOCTGB (r) */
} ETH_TX_OCTET_COUNT_GOOD_BAD_Bits;

/* Good And Bad Transmitted Packets Count Register */
typedef struct
{
    ureg32 TXPKTGB:16;     /* [15:0] Tx Packet Count Good Bad - TXPKTGB (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_PACKET_COUNT_GOOD_BAD_Bits;

/* Good Transmitted Broadcast Packets Count Register */
typedef struct
{
    ureg32 TXBCASTG:16;    /* [15:0] Tx Broadcast Packets Good - TXBCASTG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_BROADCAST_PACKETS_GOOD_Bits;

/* Good Transmitted Multicast Packets Count Register */
typedef struct
{
    ureg32 TXMCASTG:16;    /* [15:0] Tx Multicast Packets Good - TXMCASTG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_MULTICAST_PACKETS_GOOD_Bits;

/* Good And Bad 64 Octets Packets Transmitted Count Register */
typedef struct
{
    ureg32 TX64OCTGB:16;   /* [15:0] Tx 64Octets Packets Good_Bad - TX64OCTGB (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_64OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 65to127 Octets Packets Transmitted Count Register */
typedef struct
{
    ureg32 TX65_127OCTGB:16; /* [15:0] Tx 65To127Octets Packets Good Bad - TX65_127OCTGB (r) */
    ureg32 reserved_16:16;   /* [31:16] internal Reserved */
} ETH_TX_65TO127OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 128to255 Octets Packets Transmitted Count Register */
typedef struct
{
    ureg32 TX128_255OCTGB:16; /* [15:0] Tx 128To255Octets Packets Good Bad - TX128_255OCTGB (r) */
    ureg32 reserved_16:16;    /* [31:16] internal Reserved */
} ETH_TX_128TO255OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 256to511 Octets Packets Transmitted Count Register */
typedef struct
{
    ureg32 TX256_511OCTGB:16; /* [15:0] Tx 256To511Octets Packets Good Bad - TX256_511OCTGB (r) */
    ureg32 reserved_16:16;    /* [31:16] internal Reserved */
} ETH_TX_256TO511OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 512to1023 Octets Packets Transmitted Count Register */
typedef struct
{
    ureg32 TX512_1023OCTGB:16; /* [15:0] Tx 512To1023Octets Packets Good Bad - TX512_1023OCTGB (r) */
    ureg32 reserved_16:16;     /* [31:16] internal Reserved */
} ETH_TX_512TO1023OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 1024toMax Octets Packets Transmitted Count Register */
typedef struct
{
    ureg32 TX1024_MAXOCTGB:16; /* [15:0] Tx 1024ToMaxOctets Packets Good Bad - TX1024_MAXOCTGB (r) */
    ureg32 reserved_16:16;     /* [31:16] internal Reserved */
} ETH_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_Bits;

/* Good Transmitted Unicat Packets Count Register */
typedef struct
{
    ureg32 TXUCASTGB:16;   /* [15:0] Tx Unicast Packets Good Bad - TXUCASTGB (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_UNICAST_PACKETS_GOOD_BAD_Bits;

/* Good And Bad Transmitted Multicast Packets Count Register */
typedef struct
{
    ureg32 TXMCASTGB:16;   /* [15:0] Tx Multicast Packets Good Bad - TXMCASTGB (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_MULTICAST_PACKETS_GOOD_BAD_Bits;

/* Good And Bad Transmitted Broadcast Packets Count Register */
typedef struct
{
    ureg32 TXBCASTGB:16;   /* [15:0] Tx Broadcast Packets Good Bad - TXBCASTGB (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_BROADCAST_PACKETS_GOOD_BAD_Bits;

/* Transmitted Underflow Error Packets Count Register */
typedef struct
{
    ureg32 TXUNDRFLW:16;   /* [15:0] Tx Underflow Error Packets - TXUNDRFLW (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_UNDERFLOW_ERROR_PACKETS_Bits;

/* Good Transmitted Single Collision Count Register */
typedef struct
{
    ureg32 TXSNGLCOLG:16;  /* [15:0] Tx Single Collision Good Packets - TXSNGLCOLG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_SINGLE_COLLISION_GOOD_PACKETS_Bits;

/* Transmitted Multiple Collision Count Register */
typedef struct
{
    ureg32 TXMULTCOLG:16;  /* [15:0] Tx Multiple Collision Good Packets - TXMULTCOLG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_MULTIPLE_COLLISION_GOOD_PACKETS_Bits;

/* Transmitted Deferred Packets Count Register */
typedef struct
{
    ureg32 TXDEFRD:16;     /* [15:0] Tx Deferred Packets - TXDEFRD (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_DEFERRED_PACKETS_Bits;

/* Transmitted Late Collision Packets Count Register */
typedef struct
{
    ureg32 TXLATECOL:16;   /* [15:0] Tx Late Collision Packets - TXLATECOL (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_LATE_COLLISION_PACKETS_Bits;

/* Transmitted Excessive Collision Packets Count Register */
typedef struct
{
    ureg32 TXEXSCOL:16;    /* [15:0] Tx Excessive Collision Packets - TXEXSCOL (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_EXCESSIVE_COLLISION_PACKETS_Bits;

/* Transmitted Carrier Error Packets Count Register */
typedef struct
{
    ureg32 TXCARR:16;      /* [15:0] Tx Carrier Error Packets - TXCARR (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_CARRIER_ERROR_PACKETS_Bits;

/* Good Transmitted Octet Count Register */
typedef struct
{
    ureg32 TXOCTG:32; /* [31:0] Tx Octet Count Good - TXOCTG (r) */
} ETH_TX_OCTET_COUNT_GOOD_Bits;

/* Good Transmitted Packet Count Register */
typedef struct
{
    ureg32 TXPKTG:16;      /* [15:0] Tx Packet Count Good - TXPKTG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_PACKET_COUNT_GOOD_Bits;

/* Transmitted Excessive Deferral Error Count Register */
typedef struct
{
    ureg32 TXEXSDEF:16;    /* [15:0] Tx Excessive Deferral Error - TXEXSDEF (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_EXCESSIVE_DEFERRAL_ERROR_Bits;

/* Transmitted Pause Packets Count Register */
typedef struct
{
    ureg32 TXPAUSE:16;     /* [15:0] Tx Pause Packets - TXPAUSE (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_PAUSE_PACKETS_Bits;

/* Good Transmitted VLAN Packets Count Register */
typedef struct
{
    ureg32 TXVLANG:16;     /* [15:0] Tx VLAN Packets Good - TXVLANG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_VLAN_PACKETS_GOOD_Bits;

/* Good Transmitted Osize Packets Count Register */
typedef struct
{
    ureg32 TXOSIZG:16;     /* [15:0] Tx OSize Packets Good - TXOSIZG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_OSIZE_PACKETS_GOOD_Bits;

/* Good And Bad Received Packets Count Register */
typedef struct
{
    ureg32 RXPKTGB:16;     /* [15:0] Rx Packets Count Good Bad - RXPKTGB (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_PACKETS_COUNT_GOOD_BAD_Bits;

/* Good And Bad Received Octet Count Register */
typedef struct
{
    ureg32 RXOCTGB:32; /* [31:0] Rx Octet Count Good Bad - RXOCTGB (r) */
} ETH_RX_OCTET_COUNT_GOOD_BAD_Bits;

/* Good Received Octet Count Register */
typedef struct
{
    ureg32 RXOCTG:32; /* [31:0] Rx Octet Count Good - RXOCTG (r) */
} ETH_RX_OCTET_COUNT_GOOD_Bits;

/* Good Received Broadcast Packets Count Register */
typedef struct
{
    ureg32 RXBCASTG:16;    /* [15:0] Rx Broadcast Packets Good - RXBCASTG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_BROADCAST_PACKETS_GOOD_Bits;

/* Good Received Multicast Packets Count Register */
typedef struct
{
    ureg32 RXMCASTG:16;    /* [15:0] Rx Multicast Packets Good - RXMCASTG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_MULTICAST_PACKETS_GOOD_Bits;

/* Received CRC Error Packets Count Register */
typedef struct
{
    ureg32 RXCRCERR:16;    /* [15:0] Rx CRC Error Packets - RXCRCERR (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_CRC_ERROR_PACKETS_Bits;

/* Received Alignment Error Count Register */
typedef struct
{
    ureg32 RXALGNERR:16;   /* [15:0] Rx Alignment Error Packets - RXALGNERR (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_ALIGNMENT_ERROR_PACKETS_Bits;

/* Received Runtime Error Count Register */
typedef struct
{
    ureg32 RXRUNTERR:16;   /* [15:0] Rx Runt Error Packets - RXRUNTERR (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_RUNT_ERROR_PACKETS_Bits;

/* Received Jabber Error Count Register */
typedef struct
{
    ureg32 RXJABERR:16;    /* [15:0] Rx Jabber Error Packets - RXJABERR (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_JABBER_ERROR_PACKETS_Bits;

/* Good Received Undersized Packets Count Register */
typedef struct
{
    ureg32 RXUNDERSZG:16;  /* [15:0] Rx Undersize Packets Good - RXUNDERSZG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_UNDERSIZE_PACKETS_GOOD_Bits;

/* Good Received Oversized Packets Count Register */
typedef struct
{
    ureg32 RXOVERSZG:16;   /* [15:0] Rx Oversize Packets Good - RXOVERSZG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_OVERSIZE_PACKETS_GOOD_Bits;

/* Good And Bad 64 Octets Packets Received Count Register */
typedef struct
{
    ureg32 RX64OCTGB:16;   /* [15:0] Rx 64 Octets Packets Good Bad - RX64OCTGB (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_64OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 65to127 Octets Packets Received Count Register */
typedef struct
{
    ureg32 RX65_127OCTGB:16; /* [15:0] Rx 65-127 Octets Packets Good Bad - RX65_127OCTGB (r) */
    ureg32 reserved_16:16;   /* [31:16] internal Reserved */
} ETH_RX_65TO127OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 128to255 Octets Packets Received Count Register */
typedef struct
{
    ureg32 RX128_255OCTGB:16; /* [15:0] Rx 128-255 Octets Packets Good Bad - RX128_255OCTGB (r) */
    ureg32 reserved_16:16;    /* [31:16] internal Reserved */
} ETH_RX_128TO255OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 256to511 Octets Packets Received Count Register */
typedef struct
{
    ureg32 RX256_511OCTGB:16; /* [15:0] Rx 256-511 Octets Packets Good Bad - RX256_511OCTGB (r) */
    ureg32 reserved_16:16;    /* [31:16] internal Reserved */
} ETH_RX_256TO511OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 512to1023 Octets Packets Received Count Register */
typedef struct
{
    ureg32 RX512_1023OCTGB:16; /* [15:0] RX 512-1023 Octets Packets Good Bad - RX512_1023OCTGB (r) */
    ureg32 reserved_16:16;     /* [31:16] internal Reserved */
} ETH_RX_512TO1023OCTETS_PACKETS_GOOD_BAD_Bits;

/* Good And Bad 1024toMax Octets Packets Received Count Register */
typedef struct
{
    ureg32 RX1024_MAXOCTGB:16; /* [15:0] Rx 1024-Max Octets Good Bad - RX1024_MAXOCTGB (r) */
    ureg32 reserved_16:16;     /* [31:16] internal Reserved */
} ETH_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_Bits;

/* Good Received Unicat Packets Count Register */
typedef struct
{
    ureg32 RXUCASTG:16;    /* [15:0] Rx Unicast Packets Good - RXUCASTG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_UNICAST_PACKETS_GOOD_Bits;

/* Received Length Error Packets Count Register */
typedef struct
{
    ureg32 RXLENERR:16;    /* [15:0] Rx Length Error Packets - RXLENERR (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_LENGTH_ERROR_PACKETS_Bits;

/* Received Out Of Range Type Count Register */
typedef struct
{
    ureg32 RXOUTOFRNG:16;  /* [15:0] Rx Out of Range Type Packet - RXOUTOFRNG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_OUT_OF_RANGE_TYPE_PACKETS_Bits;

/* Received Pause Packets Count Register */
typedef struct
{
    ureg32 RXPAUSEPKT:16;  /* [15:0] Rx Pause Packets - RXPAUSEPKT (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_PAUSE_PACKETS_Bits;

/* Received FIFO Overflow Count Register */
typedef struct
{
    ureg32 RXFIFOOVFL:16;  /* [15:0] Rx FIFO Overflow Packets - RXFIFOOVFL (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_FIFO_OVERFLOW_PACKETS_Bits;

/* Good And Bad Received VLAN Packets Count Registerv */
typedef struct
{
    ureg32 RXVLANPKTGB:16; /* [15:0] Rx VLAN Packets Good Bad - RXVLANPKTGB (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_VLAN_PACKETS_GOOD_BAD_Bits;

/* Received Watchdog Error Count Register */
typedef struct
{
    ureg32 RXWDGERR:16;    /* [15:0] Rx Watchdog Error Packets - RXWDGERR (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_WATCHDOG_ERROR_PACKETS_Bits;

/* Received Receive Error Count Register */
typedef struct
{
    ureg32 RXRCVERR:16;    /* [15:0] Rx Receive Error Packets - RXRCVERR (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_RECEIVE_ERROR_PACKETS_Bits;

/* Good Received Control Packets Count Register */
typedef struct
{
    ureg32 RXCTRLG:16;     /* [15:0] Rx Control Packets Good - RXCTRLG (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_CONTROL_PACKETS_GOOD_Bits;

/* Transmitted LPI Microseconds Count Register */
typedef struct
{
    ureg32 TXLPIUSC:16;    /* [15:0] Tx LPI Microseconds Counter - TXLPIUSC (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_LPI_USEC_CNTR_Bits;

/* Transmitted LPI Transition Count Register */
typedef struct
{
    ureg32 TXLPITRC:16;    /* [15:0] Tx LPI Transition counter - TXLPITRC (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_TX_LPI_TRAN_CNTR_Bits;

/* Received Microseconds LPI Count Register */
typedef struct
{
    ureg32 RXLPIUSC:16;    /* [15:0] Rx LPI Microseconds Counter - RXLPIUSC (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_LPI_USEC_CNTR_Bits;

/* Received LPI Transition Count Register */
typedef struct
{
    ureg32 RXLPITRC:16;    /* [15:0] Rx LPI Transition counter - RXLPITRC (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RX_LPI_TRAN_CNTR_Bits;

/* MMC IPC Receive Interrupts Mask Register */
typedef struct
{
    ureg32 RXIPV4GPIM:1;     /* [0:0] MMC Receive IPV4 Good Packet Counter Interrupt Mask - RXIPV4GPIM (rw) */
    ureg32 RXIPV4HERPIM:1;   /* [1:1] MMC Receive IPV4 Header Error Packet Counter Interrupt Mask - RXIPV4HERPIM(rw) */
    ureg32 RXIPV4NOPAYPIM:1; /* [2:2] MMC Receive IPV4 No Payload Packet Counter Interrupt Mask - RXIPV4NOPAYPIM(rw) */
    ureg32 RXIPV4FRAGPIM:1;  /* [3:3] MMC Receive IPV4 Fragmented Packet Counter Interrupt Mask - RXIPV4FRAGPIM(rw) */
    ureg32 RXIPV4UDSBLPIM:1; /* [4:4] MMC Receive IPV4 UDP Checksum Disabled Packet Counter Interrupt Mask -
                                RXIPV4UDSBLPIM (rw) */
    ureg32 RXIPV6GPIM:1;     /* [5:5] MMC Receive IPV6 Good Packet Counter Interrupt Mask - RXIPV6GPIM (rw) */
    ureg32 RXIPV6HERPIM:1;   /* [6:6] MMC Receive IPV6 Header Error Packet Counter Interrupt Mask - RXIPV6HERPIM(rw) */
    ureg32 RXIPV6NOPAYPIM:1; /* [7:7] MMC Receive IPV6 No Payload Packet Counter Interrupt Mask - RXIPV6NOPAYPIM(rw) */
    ureg32 RXUDPGPIM:1;      /* [8:8] MMC Receive UDP Good Packet Counter Interrupt Mask - RXUDPGPIM (rw) */
    ureg32 RXUDPERPIM:1;     /* [9:9] MMC Receive UDP Error Packet Counter Interrupt Mask - RXUDPERPIM (rw) */
    ureg32 RXTCPGPIM:1;      /* [10:10] MMC Receive TCP Good Packet Counter Interrupt Mask - RXTCPGPIM (rw) */
    ureg32 RXTCPERPIM:1;     /* [11:11] MMC Receive TCP Error Packet Counter Interrupt Mask - RXTCPERPIM (rw) */
    ureg32 RXICMPGPIM:1;     /* [12:12] MMC Receive ICMP Good Packet Counter Interrupt Mask - RXICMPGPIM (rw) */
    ureg32 RXICMPERPIM:1;    /* [13:13] MMC Receive ICMP Error Packet Counter Interrupt Mask - RXICMPERPIM (rw) */
    ureg32 reserved_14:2;    /* [15:14] internal Reserved */
    ureg32 RXIPV4GOIM:1;     /* [16:16] MMC Receive IPV4 Good Octet Counter Interrupt Mask - RXIPV4GOIM (rw) */
    ureg32 RXIPV4HEROIM:1;   /* [17:17] MMC Receive IPV4 Header Error Octet Counter Interrupt Mask - RXIPV4HEROIM */
    ureg32 RXIPV4NOPAYOIM:1; /* [18:18] MMC Receive IPV4 No Payload Octet Counter Interrupt Mask - RXIPV4NOPAYOIM */
    ureg32 RXIPV4FRAGOIM:1;  /* [19:19] MMC Receive IPV4 Fragmented Octet Counter Interrupt Mask - RXIPV4FRAGOIM(rw) */
    ureg32 RXIPV4UDSBLOIM:1; /* [20:20] MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Mask -
                                RXIPV4UDSBLOIM (rw) */
    ureg32 RXIPV6GOIM:1;     /* [21:21] MMC Receive IPV6 Good Octet Counter Interrupt Mask - RXIPV6GOIM (rw) */
    ureg32 RXIPV6HEROIM:1;   /* [22:22] MMC Receive IPV6 Good Octet Counter Interrupt Mask - RXIPV6HEROIM (rw) */
    ureg32 RXIPV6NOPAYOIM:1; /* [23:23] MMC Receive IPV6 Header Error Octet Counter Interrupt Mask - RXIPV6NOPAYOIM */
    ureg32 RXUDPGOIM:1;      /* [24:24] MMC Receive IPV6 No Payload Octet Counter Interrupt Mask - RXUDPGOIM (rw) */
    ureg32 RXUDPEROIM:1;     /* [25:25] MMC Receive UDP Good Octet Counter Interrupt Mask - RXUDPEROIM (rw) */
    ureg32 RXTCPGOIM:1;      /* [26:26] MMC Receive TCP Good Octet Counter Interrupt Mask - RXTCPGOIM (rw) */
    ureg32 RXTCPEROIM:1;     /* [27:27] MMC Receive TCP Error Octet Counter Interrupt Mask - RXTCPEROIM (rw) */
    ureg32 RXICMPGOIM:1;     /* [28:28] MMC Receive ICMP Good Octet Counter Interrupt Mask - RXICMPGOIM (rw) */
    ureg32 RXICMPEROIM:1;    /* [29:29] MMC Receive ICMP Error Octet Counter Interrupt Mask - RXICMPEROIM (rw) */
    ureg32 reserved_30:2;    /* [31:30] internal Reserved */
} ETH_MMC_IPC_RX_INTERRUPT_MASK_Bits;

/* MMC IPC Receive Interrupts Register */
typedef struct
{
    ureg32 RXIPV4GPIS:1;     /* [0:0] MMC Receive IPV4 Good Packet Counter Interrupt Status - RXIPV4GPIS (r) */
    ureg32 RXIPV4HERPIS:1;   /* [1:1] MMC Receive IPV4 Header Error Packet Counter Interrupt Status - RXIPV4HERPIS(r) */
    ureg32 RXIPV4NOPAYPIS:1; /* [2:2] MMC Receive IPV4 No Payload Packet Counter Interrupt Status - RXIPV4NOPAYPIS(r) */
    ureg32 RXIPV4FRAGPIS:1;  /* [3:3] MMC Receive IPV4 Fragmented Packet Counter Interrupt Status - RXIPV4FRAGPIS(r) */
    ureg32 RXIPV4UDSBLPIS:1; /* [4:4] MMC Receive IPV4 UDP Checksum Disabled Packet Counter Interrupt Status -
                                RXIPV4UDSBLPIS (r) */
    ureg32 RXIPV6GPIS:1;     /* [5:5] MMC Receive IPV6 Good Packet Counter Interrupt Status - RXIPV6GPIS (r) */
    ureg32 RXIPV6HERPIS:1;   /* [6:6] MMC Receive IPV6 Header Error Packet Counter Interrupt Status - RXIPV6HERPIS(r) */
    ureg32 RXIPV6NOPAYPIS:1; /* [7:7] MMC Receive IPV6 No Payload Packet Counter Interrupt Status - RXIPV6NOPAYPIS(r) */
    ureg32 RXUDPGPIS:1;      /* [8:8] MC Receive UDP Good Packet Counter Interrupt Status - RXUDPGPIS (r) */
    ureg32 RXUDPERPIS:1;     /* [9:9] MMC Receive UDP Error Packet Counter Interrupt Status - RXUDPERPIS (r) */
    ureg32 RXTCPGPIS:1;      /* [10:10] MMC Receive TCP Good Packet Counter Interrupt Status - RXTCPGPIS (r) */
    ureg32 RXTCPERPIS:1;     /* [11:11] MMC Receive TCP Error Packet Counter Interrupt Status - RXTCPERPIS (r) */
    ureg32 RXICMPGPIS:1;     /* [12:12] MMC Receive ICMP Good Packet Counter Interrupt Status - RXICMPGPIS (r) */
    ureg32 RXICMPERPIS:1;    /* [13:13] MMC Receive ICMP Error Packet Counter Interrupt Status - RXICMPERPIS (r) */
    ureg32 reserved_14:2;    /* [15:14] internal Reserved */
    ureg32 RXIPV4GOIS:1;     /* [16:16] MMC Receive IPV4 Good Octet Counter Interrupt Status - RXIPV4GOIS (r) */
    ureg32 RXIPV4HEROIS:1; /* [17:17] MMC Receive IPV4 Header Error Octet Counter Interrupt Status - RXIPV4HEROIS(r) */
    ureg32
        RXIPV4NOPAYOIS:1;   /* [18:18] MMC Receive IPV4 No Payload Octet Counter Interrupt Status - RXIPV4NOPAYOIS(r) */
    ureg32 RXIPV4FRAGOIS:1; /* [19:19] MMC Receive IPV4 Fragmented Octet Counter Interrupt Status - RXIPV4FRAGOIS(r) */
    ureg32 RXIPV4UDSBLOIS:1; /* [20:20] MMC Receive IPV4 UDP Checksum Disabled Octet Counter Interrupt Status -
                                RXIPV4UDSBLOIS (r) */
    ureg32 RXIPV6GOIS:1;     /* [21:21] MMC Receive IPV6 Good Octet Counter Interrupt Status - RXIPV6GOIS (r) */
    ureg32 RXIPV6HEROIS:1; /* [22:22] MMC Receive IPV6 Header Error Octet Counter Interrupt Status - RXIPV6HEROIS(r) */
    ureg32
        RXIPV6NOPAYOIS:1; /* [23:23] MMC Receive IPV6 No Payload Octet Counter Interrupt Status - RXIPV6NOPAYOIS(r) */
    ureg32 RXUDPGOIS:1;   /* [24:24] MMC Receive UDP Good Octet Counter Interrupt Status - RXUDPGOIS (r) */
    ureg32 RXUDPEROIS:1;  /* [25:25] MMC Receive UDP Error Octet Counter Interrupt Status - RXUDPEROIS (r) */
    ureg32 RXTCPGOIS:1;   /* [26:26] MMC Receive TCP Good Octet Counter Interrupt Status - RXTCPGOIS (r) */
    ureg32 RXTCPEROIS:1;  /* [27:27] MMC Receive TCP Error Octet Counter Interrupt Status - RXTCPEROIS (r) */
    ureg32 RXICMPGOIS:1;  /* [28:28] MMC Receive ICMP Good Octet Counter Interrupt Status - RXICMPGOIS (r) */
    ureg32 RXICMPEROIS:1; /* [29:29] MMC Receive ICMP Error Octet Counter Interrupt Status - RXICMPEROIS (r) */
    ureg32 reserved_30:2; /* [31:30] internal Reserved */
} ETH_MMC_IPC_RX_INTERRUPT_Bits;

/* Good Received RxIPv4 Packets Count Register */
typedef struct
{
    ureg32 RXIPV4GDPKT:16; /* [15:0] RxIPv4 Good Packets - RXIPV4GDPKT (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RXIPV4_GOOD_PACKETS_Bits;

/* Received IPv4 Header Error Packets Count Register */
typedef struct
{
    ureg32 RXIPV4HDRERRPKT:16; /* [15:0] RxIPv4 Header Error Packets - RXIPV4HDRERRPKT (r) */
    ureg32 reserved_16:16;     /* [31:16] internal Reserved */
} ETH_RXIPV4_HEADER_ERROR_PACKETS_Bits;

/* Received IPv4 No Payload Packets Count Register */
typedef struct
{
    ureg32 RXIPV4NOPAYPKT:16; /* [15:0] RxIPv4 Payload Packets - RXIPV4NOPAYPKT (r) */
    ureg32 reserved_16:16;    /* [31:16] internal Reserved */
} ETH_RXIPV4_NO_PAYLOAD_PACKETS_Bits;

/* Received IPv4 Fragmented Packets Count Register */
typedef struct
{
    ureg32 RXIPV4FRAGPKT:16; /* [15:0] RxIPv4 Fragmented Packets - RXIPV4FRAGPKT (r) */
    ureg32 reserved_16:16;   /* [31:16] internal Reserved */
} ETH_RXIPV4_FRAGMENTED_PACKETS_Bits;

/* Received IPv4 UPD Checksum Disabled Packets Count Register */
typedef struct
{
    ureg32 RXIPV4UDSBLPKT:16; /* [15:0] RxIPv4 UDP Checksum Disabled Packets - RXIPV4UDSBLPKT (r) */
    ureg32 reserved_16:16;    /* [31:16] internal Reserved */
} ETH_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_Bits;

/* Good Received RxIPv6 Packets Count Register */
typedef struct
{
    ureg32 RXIPV6GDPKT:16; /* [15:0] RxIPv6 Good Packets - RXIPV6GDPKT (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RXIPV6_GOOD_PACKETS_Bits;

/* Received IPv6 Header Error Packets Count Register */
typedef struct
{
    ureg32 RXIPV6HDRERRPKT:16; /* [15:0] RxIPv6 Header Error Packets - RXIPV6HDRERRPKT (r) */
    ureg32 reserved_16:16;     /* [31:16] internal Reserved */
} ETH_RXIPV6_HEADER_ERROR_PACKETS_Bits;

/* Received IPv6 No Payload Packets Count Register */
typedef struct
{
    ureg32 RXIPV6NOPAYPKT:16; /* [15:0] RxIPv6 Payload Packets - RXIPV6NOPAYPKT (r) */
    ureg32 reserved_16:16;    /* [31:16] internal Reserved */
} ETH_RXIPV6_NO_PAYLOAD_PACKETS_Bits;

/* Good Received UDP Packets Count Register */
typedef struct
{
    ureg32 RXUDPGDPKT:16;  /* [15:0] RxUDP Good Packets - RXUDPGDPKT (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RXUDP_GOOD_PACKETS_Bits;

/* Received UDP Error Packets Count Register */
typedef struct
{
    ureg32 RXUDPERRPKT:16; /* [15:0] RxUDP Error Packets - RXUDPERRPKT (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RXUDP_ERROR_PACKETS_Bits;

/* Good Received TCP Packets Count Register */
typedef struct
{
    ureg32 RXTCPGDPKT:16;  /* [15:0] RxTCP Good Packets - RXTCPGDPKT (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RXTCP_GOOD_PACKETS_Bits;

/* Received TCP Error Packets Count Register */
typedef struct
{
    ureg32 RXTCPERRPKT:16; /* [15:0] RxTCP Error Packets - RXTCPERRPKT (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RXTCP_ERROR_PACKETS_Bits;

/* Good Received ICMP Packets Count Register */
typedef struct
{
    ureg32 RXICMPGDPKT:16; /* [15:0] RxICMP Good Packets - RXICMPGDPKT (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_RXICMP_GOOD_PACKETS_Bits;

/* Received ICMP Error Packets Count Register */
typedef struct
{
    ureg32 RXICMPERRPKT:16; /* [15:0] RxICMP Error Packets - RXICMPERRPKT (r) */
    ureg32 reserved_16:16;  /* [31:16] internal Reserved */
} ETH_RXICMP_ERROR_PACKETS_Bits;

/* Good Received IPV4 Octets Count Register */
typedef struct
{
    ureg32 RXIPV4GDOCT:32; /* [31:0] RxIPv4 Good Octets - RXIPV4GDOCT (r) */
} ETH_RXIPV4_GOOD_OCTETS_Bits;

/* Received IPV4 Header Error Octets Count Register */
typedef struct
{
    ureg32 RXIPV4HDRERROCT:32; /* [31:0] RxIPv4 Header Error Octets - RXIPV4HDRERROCT (r) */
} ETH_RXIPV4_HEADER_ERROR_OCTETS_Bits;

/* Received IPV4 No Payload Octets Count Register */
typedef struct
{
    ureg32 RXIPV4NOPAYOCT:32; /* [31:0] RxIPv4 Payload Octets - RXIPV4NOPAYOCT (r) */
} ETH_RXIPV4_NO_PAYLOAD_OCTETS_Bits;

/* Received IPV4 Fragmented Octets Count Register */
typedef struct
{
    ureg32 RXIPV4FRAGOCT:32; /* [31:0] RxIPv4 Fragmented Octets - RXIPV4FRAGOCT (r) */
} ETH_RXIPV4_FRAGMENTED_OCTETS_Bits;

/* Received IPV4 UPD Checksum Disabled Octets Count Register */
typedef struct
{
    ureg32 RXIPV4UDSBLOCT:32; /* [31:0] RxIPv4 UDP Checksum Disable Octets - RXIPV4UDSBLOCT (r) */
} ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_Bits;

/* Good Received IPV6 Octets Count Register */
typedef struct
{
    ureg32 RXIPV6GDOCT:32; /* [31:0] RxIPv6 Good Octets - RXIPV6GDOCT (r) */
} ETH_RXIPV6_GOOD_OCTETS_Bits;

/* Received IPV6 Header Error Octets Count Register */
typedef struct
{
    ureg32 RXIPV6HDRERROCT:32; /* [31:0] RxIPv6 Header Error Octets - RXIPV6HDRERROCT (r) */
} ETH_RXIPV6_HEADER_ERROR_OCTETS_Bits;

/* Received IPV6 No Payload Octets Count Register */
typedef struct
{
    ureg32 RXIPV6NOPAYOCT:32; /* [31:0] RxIPv6 Payload Octets - RXIPV6NOPAYOCT (r) */
} ETH_RXIPV6_NO_PAYLOAD_OCTETS_Bits;

/* Good Received UDP Octets Count Register */
typedef struct
{
    ureg32 RXUDPGDOCT:32; /* [31:0] RxUDP Good Octets - RXUDPGDOCT (r) */
} ETH_RXUDP_GOOD_OCTETS_Bits;

/* Received UDP Error Octets Count Register */
typedef struct
{
    ureg32 RXUDPERROCT:32; /* [31:0] RxUDP Error Octets - RXUDPERROCT (r) */
} ETH_RXUDP_ERROR_OCTETS_Bits;

/* Good Received TCP Octets Count Register */
typedef struct
{
    ureg32 RXTCPGDOCT:32; /* [31:0] RxTCP Good Octets - RXTCPGDOCT (r) */
} ETH_RXTCP_GOOD_OCTETS_Bits;

/* Received TCP Error Octets Count Register */
typedef struct
{
    ureg32 RXTCPERROCT:32; /* [31:0] RxTCP Error Octets - RXTCPERROCT (r) */
} ETH_RXTCP_ERROR_OCTETS_Bits;

/* Good Received ICMP Octets Count Register */
typedef struct
{
    ureg32 RXICMPGDOCT:32; /* [31:0] RxICMP Good Octets - RXICMPGDOCT (r) */
} ETH_RXICMP_GOOD_OCTETS_Bits;

/* Received ICMP Error Octets Count Register */
typedef struct
{
    ureg32 RXICMPERROCT:32; /* [31:0] RxICMP Error Octets - RXICMPERROCT (r) */
} ETH_RXICMP_ERROR_OCTETS_Bits;

/* MMC_FPE_Tx_Interrupt Register */
typedef struct
{
    ureg32 FCIS:1;        /* [0:0] MMC Tx FPE Fragment Counter Interrupt status (r) */
    ureg32 HRCIS:1;       /* [1:1] MMC Tx Hold Request Counter Interrupt Status (r) */
    ureg32 reserved_2:30; /* [31:2] internal Reserved */
} ETH_MMC_FPE_TX_INTERRUPT_Bits;

/* MMC_FPE_Tx_Interrupt mask Register */
typedef struct
{
    ureg32 FCIM:1;        /* [0:0] MMC Tx FPE Fragment Counter Interrupt Mask (r) */
    ureg32 HRCIM:1;       /* [1:1] MMC Tx Hold Request Counter Interrupt MASK (r) */
    ureg32 reserved_2:30; /* [31:2] internal Reserved */
} ETH_MMC_FPE_TX_INTERRUPT_MASK_Bits;

/* number of additional mPackets transmitted Register */
typedef struct
{
    ureg32 TXFFC:32; /* [31:0] Tx FPE Fragment counter (r) */
} ETH_MMC_TX_FPE_FRAGMENT_CNTR_Bits;

/* count of number of times a hold request Register*/
typedef struct
{
    ureg32 TXHRC:32; /* [31:0] Tx Hold Request Counter (r) */
} ETH_MMC_TX_HOLD_REQ_CNTR_Bits;

/* MMC_FPE_Rx_Interrupt Register */
typedef struct
{
    ureg32 PAECIS:1;      /* [0:0] MMC Rx Packet Assembly Error Counter Interrupt Status(r) */
    ureg32 PSECIS:1;      /* [1:1] MMC Rx Packet SMD Error Counter Interrupt Status (r) */
    ureg32 PAOCIS:1;      /* [2:2] MMC Rx Packet Assembly OK Counter Interrupt Status (r) */
    ureg32 FCIS:1;        /* [3:3] MMC Rx FPE Fragment Counter Interrupt status (r) */
    ureg32 reserved_2:28; /* [31:4] internal Reserved */
} ETH_MMC_FPE_RX_INTERRUPT_Bits;

/* MMC FPE Rx Interrupt Mask Register*/
typedef struct
{
    ureg32 PAECIM:1;      /* [0:0] MMC Rx Packet Assembly Error Counter Interrupt mask(r) */
    ureg32 PSECIM:1;      /* [1:1] MMC Rx Packet SMD Error Counter Interrupt mask (r) */
    ureg32 PAOCIM:1;      /* [2:2] MMC Rx Packet Assembly OK Counter Interrupt mask (r) */
    ureg32 FCIM:1;        /* [3:3] MMC Rx FPE Fragment Counter Interrupt mask (r) */
    ureg32 reserved_2:28; /* [31:4] internal Reserved */
} ETH_MMC_FPE_RX_INTERRUPT_MASK_Bits;

/* the number of MAC frames with reassembly errors */
typedef struct
{
    ureg32 PAEC:32; /* [31:0] Rx Packet Assembly Error Counter (r) */
} ETH_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR_Bits;

/* rejected due to unknown SMD value */
typedef struct
{
    ureg32 PSEC:32; /* [31:0] Rx Packet SMD Error Counter(r) */
} ETH_MMC_RX_PACKET_SMD_ERR_CNTR_Bits;

/* The number of MAC frames with reassembly  */
typedef struct
{
    ureg32 PAOC:32; /* [31:0] Rx Packet Assembly OK Counter (r) */
} ETH_MMC_RX_PACKET_ASSEMBLY_OK_CNTR_Bits;

/* The number of additional mPackets received due to preemption */
typedef struct
{
    ureg32 FFC:32; /* [31:0] Rx FPE Fragment Counter (r) */
} ETH_MMC_RX_FPE_FRAGMENT_CNTR_Bits;

/* The indirect access control and status */
typedef struct
{
    ureg32 OB:1;           /* [0:0] Operation Busy - OB(rw) */
    ureg32 COM:1;          /* [1:1] Command type - COM(rw) */
    ureg32 reserved_2:3;   /* [4:2] internal Reserved */
    ureg32 AUTO:1;         /* [5:5] Auto increment - AUTO(rw) */
    ureg32 reserved_6:2;   /* [7:6] internal Reserved */
    ureg32 AOFF:8;         /* [15:8] Address Offset - AOFF(rw) */
    ureg32 MSEL:4;         /* [19:16] Mode Select - MSEL (rw) */
    ureg32 reserved_20:11; /* [30:20] internal Reserved */
    ureg32 SNPS_R:1;       /* [31:31] SNPS_R */
} ETH_MAC_INDIR_ACCESS_CTRL_Bits;

/* The indirect access data */
typedef struct
{
    ureg32 DATA:32; /* [31:0] The indirect access data - DATA(rw) */
} ETH_MAC_INDIR_ACCESS_DATA_Bits;

/* Contains threshold based interrupt enable for corresponding policing counters */
typedef struct
{
    ureg32 PCTIE:16;       /* [15:0] Policing counter threshold interrupt enable - PCTIE(rw) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MAC_PCTH_INTR_ENABLE_Bits;

/* Contains threshold based interrupt for corresponding policing counters */
typedef struct
{
    ureg32 PCTIS:16;       /* [15:0] Policing counter threshold interrupt - PCTIS(rw) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MAC_PCTH_INTR_STATUS_Bits;

/* Contains enable bits for Time based interrupt */
typedef struct
{
    ureg32 TWIE:4;        /* [3:0] Time window interrupt enable - TWIE(rw) */
    ureg32 reserved_4:28; /* [31:4] internal Reserved */
} ETH_MAC_PCTW_INTR_ENABLE_Bits;

/* Contains Time based interrupt status */
typedef struct
{
    ureg32 TWIS:4;        /* [3:0] Time window interrupt status - TWIS(rw) */
    ureg32 reserved_4:28; /* [31:4] internal Reserved */
} ETH_MAC_PCTW_INTR_STATUS_Bits;

/* MAC Timestamp Control Register */
typedef struct
{
    ureg32 TSENA:1;       /* [0:0] Enable Timestamp - TSENA (rw) */
    ureg32 TSCFUPDT:1;    /* [1:1] Fine or Coarse Timestamp Update - TSCFUPDT (rw) */
    ureg32 TSINIT:1;      /* [2:2] Initialize Timestamp - TSINIT (rw) */
    ureg32 TSUPDT:1;      /* [3:3] Update Timestamp - TSUPDT (rw) */
    ureg32 reserved_4:1;  /* [4:4] internal Reserved */
    ureg32 TSADDREG:1;    /* [5:5] Update Addend Register - TSADDREG (rw) */
    ureg32 PTGE:1;        /* [6:6] Presentation Time Generation Enable - PTGE(rw) */
    ureg32 reserved_7:1;  /* [7:7] internal Reserved */
    ureg32 TSENALL:1;     /* [8:8] Enable Timestamp for All Packets - TSENALL (rw) */
    ureg32 TSCTRLSSR:1;   /* [9:9] Timestamp Digital or Binary Rollover Control - TSCTRLSSR (rw) */
    ureg32 TSVER2ENA:1;   /* [10:10] Enable PTP Packet Processing for Version 2 Format - TSVER2ENA (rw) */
    ureg32 TSIPENA:1;     /* [11:11] Enable Processing of PTP over Ethernet Packets - TSIPENA (rw) */
    ureg32 TSIPV6ENA:1;   /* [12:12] Enable Processing of PTP Packets Sent over IPv6-UDP - TSIPV6ENA (rw) */
    ureg32 TSIPV4ENA:1;   /* [13:13] Enable Processing of PTP Packets Sent over IPv4-UDP - TSIPV4ENA (rw) */
    ureg32 TSEVNTENA:1;   /* [14:14] Enable Timestamp Snapshot for Event Messages - TSEVNTENA (rw) */
    ureg32 TSMSTRENA:1;   /* [15:15] Enable Snapshot for Messages Relevant to Master - TSMSTRENA (rw) */
    ureg32 SNAPTYPSEL:2;  /* [17:16] Select PTP packets for Taking Snapshots - SNAPTYPSEL (rw) */
    ureg32 TSENMACADDR:1; /* [18:18] Enable MAC Address for PTP Packet Filtering - TSENMACADDR (rw) */
    ureg32 CSC:1;         /* [19:19] Enable checksum correction during OST for PTP over UDP/IPv4 packets - CSC (rw) */
    ureg32 ESTI:1;        /* [20:20] External System Time input */
    ureg32 reserved_21:3; /* [23:21] internal Reserved */
    ureg32 TXTSSTSM:1;    /* [24:24] Transmit Timestamp Status Mode - TXTSSTSM (rw) */
    ureg32 reserved_25:3; /* [27:25] internal Reserved */
    ureg32 AV8021ASMEN:1; /* [28:28] AV 802.1AS Mode Enable - AV8021ASMEN (rw) */
    ureg32 reserved_29:3; /* [31:29] internal Reserved */
} ETH_MAC_TIMESTAMP_CONTROL_Bits;

/* MAC Sub-Second Increment Register */
typedef struct
{
    ureg32 reserved_0:8;  /* [7:0] internal Reserved */
    ureg32 SNSINC:8;      /* [15:8] Sub-nanosecond Increment Value - SNSINC (rw) */
    ureg32 SSINC:8;       /* [23:16] Sub-second Increment Value - SSINC (rw) */
    ureg32 reserved_24:8; /* [31:24] internal Reserved */
} ETH_MAC_SUB_SECOND_INCREMENT_Bits;

/* MAC System Time Seconds Register */
typedef struct
{
    ureg32 TSS:32; /* [31:0] Timestamp Second - TSS (r) */
} ETH_MAC_SYSTEM_TIME_SECONDS_Bits;

/* MAC System Time Nanoseconds Register */
typedef struct
{
    ureg32 TSSS:31;       /* [30:0] Timestamp Sub Seconds - TSSS (r) */
    ureg32 reserved_31:1; /* [31:31] internal Reserved */
} ETH_MAC_SYSTEM_TIME_NANOSECONDS_Bits;

/* MAC System Time Seconds Update Register */
typedef struct
{
    ureg32 TSS:32; /* [31:0] Timestamp Seconds - TSS (rw) */
} ETH_MAC_SYSTEM_TIME_SECONDS_UPDATE_Bits;

/* MAC System Time Nanoseconds Update Register */
typedef struct
{
    ureg32 TSSS:31;  /* [30:0] Timestamp Sub Seconds - TSSS (rw) */
    ureg32 ADDSUB:1; /* [31:31] Add or Subtract Time - ADDSUB (rw) */
} ETH_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_Bits;

/* MAC Timestamp Addend Register */
typedef struct
{
    ureg32 TSAR:32; /* [31:0] Timestamp Addend Register - TSAR (rw) */
} ETH_MAC_TIMESTAMP_ADDEND_Bits;

/* MAC System Time Higher Word Seconds Register */
typedef struct
{
    ureg32 TSHWR:16;       /* [15:0] Timestamp Higher Word Register - TSHWR (rw) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_Bits;

/* MAC Timestamp Status Register */
typedef struct
{
    ureg32 TSSOVF:1;      /* [0:0] Timestamp Seconds Overflow - TSSOVF (r) */
    ureg32 TSTARGT0:1;    /* [1:1] Timestamp Target Time Reached - TSTARGT0 (r) */
    ureg32 reserved_2:1;  /* [2:2] internal Reserved */
    ureg32 TSTRGTERR0:1;  /* [3:3] Timestamp Target Time Error - TSTRGTERR0 (r) */
    ureg32 TSTARGT1:1;    /* [4:4] Timestamp Target Time Reached for Target Time PPS1 - TSTARGT1 (r) */
    ureg32 TSTRGTERR1:1;  /* [5:5] Timestamp Target Time Error - TSTRGTERR1 (r) */
    ureg32 TSTARGT2:1;    /* [6:6] Timestamp Target Time Reached for Target Time PPS2 - TSTARGT2 (r) */
    ureg32 TSTRGTERR2:1;  /* [7:7] Timestamp Target Time Error - TSTRGTERR2 (r) */
    ureg32 TSTARGT3:1;    /* [8:8] Timestamp Target Time Reached for Target Time PPS3 - TSTARGT3 (r) */
    ureg32 TSTRGTERR3:1;  /* [9:9] Timestamp Target Time Error - TSTRGTERR3 (r) */
    ureg32 reserved_10:5; /* [14:10] internal Reserved */
    ureg32 TXTSSIS:1;     /* [15:15] Tx Timestamp Status Interrupt Status - TXTSSIS (r) */
    ureg32 reserved_16:4; /* [19:16] internal Reserved */
    ureg32 reserved_20:4; /* [23:20] internal Reserved */
    ureg32 reserved_24:6; /* [29:24] internal Reserved */
    ureg32 reserved_30:2; /* [31:30] internal Reserved */
} ETH_MAC_TIMESTAMP_STATUS_Bits;

/* MAC_RX_DOMAIN_TIME_INCR_Bits Register */
typedef struct
{
    ureg32 reserved_0:8; /* [7:0] internal Reserved */
    ureg32 RXSNS:8;      /* [15:8] Receive Domain Time Increment in Sub-Nanoseconds - RXSNS (rw) */
    ureg32 RXNS:16;      /* [31:16] Receive Domain Time Increment in Nanoseconds - RXNS (rw) */
} ETH_MAC_RX_DOMAIN_TIME_INCR_Bits;

/* MAC_TX_DOMAIN_TIME_INCR_Bits Register */
typedef struct
{
    ureg32 reserved_0:8; /* [7:0] internal Reserved */
    ureg32 TXSNS:8;      /* [15:8] Transmit Domain Time Increment in Sub-Nanoseconds - TXSNS (rw) */
    ureg32 TXNS:16;      /* [31:16] Transmit Domain Time Increment in Nanoseconds - TXNS (rw) */
} ETH_MAC_TX_DOMAIN_TIME_INCR_Bits;

/* MAC Transmit Timestamp Nanoseconds Status Register */
typedef struct
{
    ureg32 TXTSSLO:31; /* [30:0] Transmit Timestamp Status Low - TXTSSLO (r) */
    ureg32 TXTSSMIS:1; /* [31:31] Transmit Timestamp Status Missed - TXTSSMIS (r) */
} ETH_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_Bits;

/* MAC Transmit Timestamp Seconds Status Register */
typedef struct
{
    ureg32 TXTSSHI:32; /* [31:0] Transmit Timestamp Status High - TXTSSHI (r) */
} ETH_MAC_TX_TIMESTAMP_STATUS_SECONDS_Bits;

/* MAC Timestamp Ingress Asymmetry Correction Register */
typedef struct
{
    ureg32 OSTIAC:32; /* [31:0] One-Step Timestamp Ingress Asymmetry Correction - OSTIAC (rw) */
} ETH_MAC_TIMESTAMP_INGRESS_ASYM_CORR_Bits;

/* MAC Timestamp Egress Asymmetry Correction Register */
typedef struct
{
    ureg32 OSTEAC:32; /* [31:0] One-Step Timestamp Egress Asymmetry Correction - OSTEAC (rw) */
} ETH_MAC_TIMESTAMP_EGRESS_ASYM_CORR_Bits;

/* MAC Timestamp Ingress Correction Nanoseconds Register */
typedef struct
{
    ureg32 TSIC:32; /* [31:0] Timestamp Ingress Correction - TSIC (rw) */
} ETH_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_Bits;

/* MAC Timestamp Egress Correction Nanoseconds Register */
typedef struct
{
    ureg32 TSEC:32; /* [31:0] Timestamp Egress Correction - TSEC (rw) */
} ETH_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_Bits;

/* MAC Timestamp Ingress Correction Subnanoseconds Register */
typedef struct
{
    ureg32 reserved_0:8;   /* [7:0] internal Reserved */
    ureg32 TSICSNS:8;      /* [15:8] Timestamp Ingress Correction, sub-nanoseconds - TSICSNS (rw) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_Bits;

/* MAC Timestamp Egress Correction Subnanoseconds Register */
typedef struct
{
    ureg32 reserved_0:8;   /* [7:0] internal Reserved */
    ureg32 TSECSNS:8;      /* [15:8] Timestamp Egress Correction, sub-nanoseconds - TSECSNS (rw) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_Bits;

/* MAC Timestamp Ingress Latency Register */
typedef struct
{
    ureg32 reserved_0:8;  /* [7:0] internal Reserved */
    ureg32 ITLSNS:8;      /* [15:8] Ingress Timestamp Latency, in nanoseconds (r) */
    ureg32 ITLNS:12;      /* [27:16] Ingress Timestamp Latency, in sub-nanoseconds (r) */
    ureg32 reserved_28:4; /* [31:28] internal Reserved */
} ETH_MAC_TIMESTAMP_INGRESS_LATENCY_Bits;

/* MAC Timestamp Egress  Latency Register */
typedef struct
{
    ureg32 reserved_0:8;  /* [7:0] internal Reserved */
    ureg32 ETLSNS:8;      /* [15:8] Egress Timestamp Latency, in nanoseconds (r) */
    ureg32 ETLNS:12;      /* [27:16] Egress Timestamp Latency, in sub-nanoseconds (r) */
    ureg32 reserved_28:4; /* [31:28] internal Reserved */
} ETH_MAC_TIMESTAMP_EGRESS_LATENCY_Bits;

/* MAC PPS Control Register */
typedef struct
{
    ureg32 PPSCTRL_PPSCMD:4; /* [3:0] Flexible PPS Output (ptp_pps_o[0]) Control - PPSCTRL_PPSCMD (rw) */
    ureg32 PPSEN0:1;         /* [4:4] Flexible PPS Output Mode Enable - PPSEN0 (rw) */
    ureg32 TRGTMODSEL0:2;    /* [6:5] Target Time Register Mode for PPS0 Output - TRGTMODSEL0 (rw) */
    ureg32 MCGREN0:1;        /* [7:7] MCGR mode enable for PPS0 output */
    ureg32 PPSCMD1:4;        /* [11:8] Flexible PPS1 output control */
    ureg32 reserved_12:1;    /* [12:12] internal Reserved */
    ureg32 TRGTMODSEL1:2;    /* [14:13] Target time register mode for PPS1 output */
    ureg32 MCGREN1:1;        /* [15:15] MCGR mode enable for PPS1 output */
    ureg32 PPSCMD2:4;        /* [19:16] Flexible PPS2 output control */
    ureg32 reserved_20:1;    /* [20:20] internal Reserved */
    ureg32 TRGTMODSEL2:2;    /* [22:21] Target time register mode for PPS2 output */
    ureg32 MCGREN2:1;        /* [23:23] MCGR mode enable for PPS2 output */
    ureg32 PPSCMD3:4;        /* [27:24] Flexible PPS3 output control  */
    ureg32 TIMESEL:1;        /* [28:28] Time select */
    ureg32 TRGTMODSEL3:2;    /* [30:29] Target time register mode for PPS3 output */
    ureg32 MCGREN3:1;        /* [31:31] MCGR mode enable for PPS3 output */
} ETH_MAC_PPS_CONTROL_Bits;

/* MAC PPS 0 Target Time Seconds Register */
typedef struct
{
    ureg32 TSTRH0:32; /* [31:0] PPS Target Time Seconds Register - TSTRH0 (rw) */
} ETH_MAC_PPS0_TARGET_TIME_SECONDS_Bits;

/* MAC PPS 0 Target Time Nanoeconds Register */
typedef struct
{
    ureg32 TTSL0:31;    /* [30:0] Target Time Low for PPS Register - TTSL0 (rw) */
    ureg32 TRGTBUSY0:1; /* [31:31] PPS Target Time Register Busy - TRGTBUSY0 (rw) */
} ETH_MAC_PPS0_TARGET_TIME_NANOSECONDS_Bits;

/* MAC PPS 0 Interval Register */
typedef struct
{
    ureg32 PPSINT0:32; /* [31:0] PPS Output Signal Interval - PPSINT0 (rw) */
} ETH_MAC_PPS0_INTERVAL_Bits;

/* MAC PPS 0 Width Register */
typedef struct
{
    ureg32 PPSWIDTH0:32; /* [31:0] PPS Output Signal Width - PPSWIDTH0 (rw) */
} ETH_MAC_PPS0_WIDTH_Bits;

/* MAC_PTO_CONTROL Register */
typedef struct
{
    ureg32 PTOEN:1;        /* [0:0] PTP offload enable - PTOEN (rw) */
    ureg32 ASYNCEN:1;      /* [1:1] Automatic PTP SYNC message enable - ASYNCEN (rw)  */
    ureg32 APDREQEN:1;     /* [2:2] Automatic PTP Pdelay_Req message enable - ASYNCEN (rw) */
    ureg32 reserved_3:1;   /* [3:3] internal Reserved */
    ureg32 ASYNCTRIG:1;    /* [4:4] Automatic PTP SYNC message trigger */
    ureg32 APDREQTRIG:1;   /* [5:5] Automatic PTP Pdelay_Req message trigger */
    ureg32 DRRDIS:1;       /* [6:6] Disable PTO delay Request/response generation */
    ureg32 PDRDIS:1;       /* [7:7] Disable Peer delay response generation */
    ureg32 DN:8;           /* [15:8] Domain Number */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MAC_PTO_CONTROL_Bits;

/* MAC_SOURCE_PORT_IDENTITY0 Register */
typedef struct
{
    ureg32 SPI0:32; /* [31:0] Source Port identity */
} ETH_MAC_SOURCE_PORT_IDENTITY0_Bits;

/* MAC_SOURCE_PORT_IDENTITY0 Register */
typedef struct
{
    ureg32 SPI1:32; /* [31:0] Source Port identity */
} ETH_MAC_SOURCE_PORT_IDENTITY1_Bits;

/* MAC_SOURCE_PORT_IDENTITY0 Register */
typedef struct
{
    ureg32 SPI2:32; /* [31:0] Source Port identity */
} ETH_MAC_SOURCE_PORT_IDENTITY2_Bits;

/* MAC_SOURCE_PORT_IDENTITY0 Register */
typedef struct
{
    ureg32 LSI:8;          /* [7:0] Log sync interval */
    ureg32 DRSYNCR:3;      /* [10:8] Delay_Req to SYNC Ratio */
    ureg32 reserved_11:13; /* [23:11] internal Reserved */
    ureg32 LMPDRI:8;       /* [31:24] Log min Pdelay_Req interval */
} ETH_MAC_LOG_MESSAGE_INTERVAL_Bits;

/* DMA Block */
/* DMA Bus Mode Register */
typedef struct
{
    ureg32 SWR:1;          /* [0:0] Software Reset - SWR (rw) */
    ureg32 reserved_1:1;   /* [1:1] internal Reserved, DMA Tx or Rx Arbitration Scheme - DA*/
    ureg32 TAA:3;          /* [4:2] Transmit Arbitration Algorithm - TAA (rw) */
    ureg32 reserved_5:3;   /* [7:5] internal Reserved */
    ureg32 DSPW:1;         /* [8:8] Descriptor Posted Write (rw) */
    ureg32 reserved_9:2;   /* [10:9] internal Reserved */
    ureg32 TXPR:1;         /* [11:11] Transmit Priority - TXPR (rw) */
    ureg32 reserved_12:3;  /* [14:12] internal Reserved,Priority Ratio - PR*/
    ureg32 reserved_15:1;  /* [15:15] internal Reserved */
    ureg32 INTM:2;         /* [17:16] Interrupt Mode - INTM (rw) */
    ureg32 reserved_18:14; /* [31:18] internal Reserved */
} ETH_DMA_MODE_Bits;

/* DMA System Bus Mode Register */
typedef struct
{
    ureg32 FB:1;         /* [0:0] Fixed Burst Length - FB (rw) , max 16 */
    ureg32 BLEN4:1;      /* [1:1] AXI Burst length 4 */
    ureg32 BLEN8:1;      /* [2:2] AXI Burst length 8 */
    ureg32 BLEN16:1;     /* [3:3] AXI Burst length 16 */
    ureg32 BLEN32:1;     /* [4:4] AXI Burst length 32 */
    ureg32 BLEN64:1;     /* [5:5] AXI Burst length 64 */
    ureg32 BLEN128:1;    /* [6:6] AXI Burst length 128 */
    ureg32 BLEN256:1;    /* [7:7] AXI Burst length 256 */
    ureg32 reserved_8:2; /* [9:8] internal Reserved */
    ureg32 AALE:1; /* [10:10] enable AXI master to LPI state when no activity for LPIEI of AXI_LPI_Entry_Interval */
    ureg32 reserved_11:1; /* [11:11] internal Reserved */
    ureg32 AAL:1;         /* [12:12] Address-Aligned Beats - AAL (rw) */
    ureg32 ONEKBBE:1;     /* [13:13] enable 1KB boundary crossing for AXI master beats */
    ureg32 reserved_14:2; /* [15:14] internal Reserved, Mixed Burst - MB,Rebuild INCRx Burst - RB */
    ureg32 RD_OSR_LMT:3;  /* [18:16] read outstanding request limit, max 8 */
    ureg32 reserved_19:5; /* [23:19] internal Reserved */
    ureg32 WR_OSR_LMT:3;  /* [26:24] write outstanding request limit */
    ureg32 reserved_27:3; /* [29:27] internal Reserved */
    ureg32 LPI_XIT_PKT:1; /* [30:30] enable magic packet or remote wake-up packet */
    ureg32 EN_LPI:1;      /* [31:31] enable LPI request from AXI system clock */
} ETH_DMA_SYSBUS_MODE_Bits;

/* DMA Interrupt Status Register */
typedef struct
{
    ureg32 DC0IS:1;        /* [0:0] DMA Channel 0 Interrupt Status - DC0IS (r) */
    ureg32 DC1IS:1;        /* [1:1] DMA Channel 1 Interrupt Status - DC1IS (r) */
    ureg32 DC2IS:1;        /* [2:2] DMA Channel 2 Interrupt Status - DC2IS (r) */
    ureg32 DC3IS:1;        /* [3:3] DMA Channel 3 Interrupt Status - DC3IS (r) */
    ureg32 reserved_4:4;   /* [7:4] internal Reserved */
    ureg32 reserved_8:8;   /* [15:8] internal Reserved */
    ureg32 MTLIS:1;        /* [16:16] MTL Interrupt Status - MTLIS (r) */
    ureg32 MACIS:1;        /* [17:17] MAC Interrupt Status - MACIS (r) */
    ureg32 reserved_18:14; /* [31:18] internal Reserved */
} ETH_DMA_INTERRUPT_STATUS_Bits;

/* DMA Debug Status 0 Register */
typedef struct
{
    ureg32 AXWHSTS:1;    /* [0:0] AHB Master Status - AXWHSTS (r) */
    ureg32 AXRHSTS:1;    /* [1:1] AXI Master read channel status */
    ureg32 reserved_2:6; /* [7:2] internal Reserved */
    ureg32 RPS0:4;       /* [11:8] DMA Channel 0 Receive Process State - RPS0 (r) */
    ureg32 TPS0:4;       /* [15:12] DMA Channel 0 Transmit Process State - TPS0 (r) */
    ureg32 RPS1:4;       /* [19:16] DMA Channel 1 Receive Process State - RPS1 (r) */
    ureg32 TPS1:4;       /* [23:20] DMA Channel 1 Transmit Process State - TPS1 (r) */
    ureg32 RPS2:4;       /* [27:24] DMA Channel 2 Receive Process State - RPS2 (r) */
    ureg32 TPS2:4;       /* [31:28] DMA Channel 2 Transmit Process State - TPS2 (r) */
} ETH_DMA_DEBUG_STATUS0_Bits;

/* DMA Debug Status 1 Register */
typedef struct
{
    ureg32 RPS3:4;        /* [3:0] DMA Channel 3 Receive Process State - RPS3 (r) */
    ureg32 TPS3:4;        /* [7:4] DMA Channel 3 Transmit Process State - TPS3 (r) */
    ureg32 reserved_8:24; /* [31:8] internal Reserved */
} ETH_DMA_DEBUG_STATUS1_Bits;

typedef struct
{
    ureg32 TDRC:4;         /* [3:0] TDRC */
    ureg32 TDRD:2;         /* [5:4] TDRD */
    ureg32 reserved_6:2;   /* [7:6] internal Reserved */
    ureg32 TEC:4;          /* [11:8] TEC */
    ureg32 TED:2;          /* [13:12] TED */
    ureg32 reserved_14:2;  /* [15:14] internal Reserved */
    ureg32 THC:4;          /* [19:16] THC*/
    ureg32 THD:2;          /* [21:20] THD */
    ureg32 reserved_22:10; /* [31:22] internal Reserved */
} ETH_AXI4_TX_AR_ACE_CONTROL_Bits;

typedef struct
{
    ureg32 RDWC:4;        /* [3:0] TDRC */
    ureg32 RDWD:2;        /* [5:4] TDRD */
    ureg32 reserved_6:2;  /* [7:6] internal Reserved */
    ureg32 RPC:4;         /* [11:8] RPC */
    ureg32 RPD:2;         /* [13:12] RPD */
    ureg32 reserved_14:2; /* [15:14] internal Reserved */
    ureg32 RHC:4;         /* [19:16] RHC */
    ureg32 RHD:2;         /* [21:20] RHD */
    ureg32 reserved_22:2; /* [23:22] internal Reserved */
    ureg32 RDC:4;         /* [27:24] RDC */
    ureg32 RDD:2;         /* [29:28] RDD */
    ureg32 reserved_30:2; /* [31:30] internal Reserved */
} ETH_AXI4_RX_AW_ACE_CONTROL_Bits;

typedef struct
{
    ureg32 TDWC:4;        /* [3:0] TDRC */
    ureg32 TDWD:2;        /* [5:4] TDRD */
    ureg32 reserved_6:2;  /* [7:6] internal Reserved */
    ureg32 RDRC:4;        /* [11:8] RDRC */
    ureg32 RDRD:2;        /* [13:12] RDRD */
    ureg32 reserved_14:2; /* [15:14] internal Reserved */
    ureg32 RDP:3;         /* [18:16] RDP */
    ureg32 reserved_19:1; /* [19:19] internal Reserved */
    ureg32 WRP:3;         /* [22:20] WRP */
    ureg32 reserved_23:9; /* [31:23] internal Reserved */
} ETH_AXI4_TXRX_AWAR_ACE_CONTROL_Bits;

/* AXI LPI entry interval Register */
typedef struct
{
    ureg32 LPIEI:4;       /* [3:0] LPI Entry Interval */
    ureg32 reserved_4:28; /* [31:4] internal Reserved */
} ETH_AXI_LPI_ENTRY_INTERVAL_Bits;

/* DMA_TBS_CRTL Register */
typedef struct
{
    ureg32 FTOV:1;       /* [0:0] Fetch time offset valid */
    ureg32 reserved_1:3; /* [3:1] internal Reserved */
    ureg32 FGOS:3;       /* [6:4] Fetch GSN offset */
    ureg32 reserved_7:1; /* [7:7] internal Reserved */
    ureg32 FTOS:24;      /* [31:8] Fetch time offset */
} ETH_DMA_TBS_CRTL_Bits;

/* DMA Safety interrupt Status */
typedef struct
{
    ureg32 DECIS:1;       /* [0:0] DMA ECC Correctable error Interrupt Status */
    ureg32 DEUIS:1;       /* [1:1] DMAECC Ucorrectable error Interrupt Status */
    ureg32 reserved_2:26; /* [27:2] internal Reserved */
    ureg32 MSCIS:1;       /* [28:28] MTL Safety Correctable error Interrupt Status */
    ureg32 MSUIS:1;       /* [29:29] MTL Safety Uncorrectable error Interrupt Status */
    ureg32 reserved_30:1; /* [30:30] internal Reserved */
    ureg32 MCSIS:1;       /* [31:31] MAC Safety Uncorrectable Interrupt Status */
} ETH_DMA_SAFETY_INTERRUPT_STATUS_Bits;

/* DMA Channel Control Register */
typedef struct
{
    ureg32 reserved_0:14; /* [13:0] maximum segment size(TSE) */
    ureg32 reserved_14:2; /* [15:14] internal Reserved */
    ureg32 PBLX8:1;       /* [16:16] 8xPBL mode - PBLx8 (rw) */
    ureg32 reserved_17:1; /* [17:17] internal Reserved */
    ureg32 DSL:3;         /* [20:18] Descriptor Skip Length - DSL (rw) */
    ureg32 reserved_21:3; /* [23:21] internal Reserved */
    ureg32 SPH:1;         /* [24:24] Split Headers - SPH (rw) */
    ureg32 reserved_25:7; /* [31:25] internal Reserved */
} ETH_DMA_CH_CONTROL_Bits;

/* DMA Channel Transmit Control Register */
typedef struct
{
    ureg32 ST:1;          /* [0:0] Start or Stop Transmission Command - ST (rw) */
    ureg32 TCW:3;         /* [3:1] Transmit Channel Weight - TCW (rw) */
    ureg32 OSF:1;         /* [4:4] Operate on Second Packet - OSF (rw) */
    ureg32 reserved_5:7;  /* [11:5] internal Reserved */
    ureg32 reserved_12:3; /* [14:12] internal Reserved,TSE,TSE_MODE*/
    ureg32 IPBL:1;        /* [15:15] does not check for PBL number in MTL before transfer*/
    ureg32 TXPBL:6;       /* [21:16] Transmit Programmable Burst Length - TxPBL (rw) */
    ureg32 reserved_22:1; /* [22:22] internal Reserved,early transmit interrupt control */
    ureg32 reserved_23:1; /* [23:23] internal Reserved */
    ureg32 TQOS:4;        /* [27:24] transmit QOS */
    ureg32 EDSE:1;        /* [28:28] enhanced descriptor enable */
    ureg32 TFSEL:2;       /* [30:29] Select one of the four DMA_TBS_CTRL register */
    ureg32 reserved_31:1; /* [31:31] internal Reserved */
} ETH_DMA_CH_TX_CONTROL_Bits;

/* DMA Channel Receive Control Register */
typedef struct
{
    ureg32 SR:1;          /* [0:0] Start or Stop Receive - SR (rw) */
    ureg32 RBSZ_X_0:3;    /* [3:1] Receive Buffer size Low - RBSZ_x_0 (r), 3 for 64bit data bus, 2 for 32bits */
    ureg32 RBSZ_13_Y:11;  /* [14:4] Receive Buffer size High - RBSZ_13_y (rw) */
    ureg32 reserved_15:1; /* [15:15] internal Reserved */
    ureg32 RXPBL:6;       /* [21:16] Receive Programmable Burst Length - RxPBL (rw) */
    ureg32 reserved_22:1; /* [22:22] internal Reserved,early receive interrupt control-ERIC */
    ureg32 reserved_23:1; /* [23:23] internal Reserved */
    ureg32 RQOS:4;        /* [27:24] Rx AXI4 QOS */
    ureg32 reserved_28:3; /* [30:28] internal Reserved */
    ureg32 RPF:1;         /* [31:31] DMA Rx Channel0 Packet Flush - RPF (rw) */
} ETH_DMA_CH_RX_CONTROL_Bits;

/* DMA Channel Transmit Descriptor List Address Register */
typedef struct
{
    ureg32 reserved_0:3; /* [2:0] internal Reserved for 32bit , 64bit 2:0*/
    ureg32 TDESLA:29;    /* [31:3] Start of Transmit List - TDESLA (rw) */
} ETH_DMA_CH_TXDESC_LIST_ADDRESS_Bits;

/* DMA Channel Receive Descriptor List Address Register */
typedef struct
{
    ureg32 reserved_0:3; /* [2:0] internal Reserved for 64bit data bus width*/
    ureg32 RDESLA:29;    /* [31:3] Start of Receive List - RDESLA (rw) */
} ETH_DMA_CH_RXDESC_LIST_ADDRESS_Bits;

/* DMA Channel Transmit Descriptor Tail Pointer Register */
typedef struct
{
    ureg32 reserved_0:3; /* [2:0] internal Reserved */
    ureg32 TDTP:29;      /* [31:3] Transmit Descriptor Tail Pointer - TDTP (rw) */
} ETH_DMA_CH_TXDESC_TAIL_POINTER_Bits;

/* DMA Channel Recieve Descriptor Tail Pointer Register */
typedef struct
{
    ureg32 reserved_0:3; /* [2:0] internal Reserved */
    ureg32 RDTP:29;      /* [31:3] Receive Descriptor Tail Pointer - RDTP (rw) */
} ETH_DMA_CH_RXDESC_TAIL_POINTER_Bits;

/* DMA Channel Transmit Descriptor Ring Length Register */
typedef struct
{
    ureg32 TDRL:10;        /* [9:0] Transmit Descriptor Ring Length - TDRL (rw) */
    ureg32 reserved_10:22; /* [31:10] internal Reserved */
} ETH_DMA_CH_TXDESC_RING_LENGTH_Bits;

/* DMA Channel Recieve Descriptor Ring Length Register */
typedef struct
{
    ureg32 RDRL:10;       /* [9:0] Receive Descriptor Ring Length - RDRL (rw) */
    ureg32 reserved_10:7; /* [16:10] internal Reserved */
    ureg32 ARBS:7;        /* [23:17] Alternate Receive Buffer Size - ARBS (rw) */
    ureg32 reserved_24:8; /* [31:24] internal Reserved */
} ETH_DMA_CH_RXDESC_RING_LENGTH_Bits;

/* DMA Channel Interrupt Enable Register */
typedef struct
{
    ureg32 TIE:1;          /* [0:0] Transmit Interrupt Enable - TIE (rw) */
    ureg32 TXSE:1;         /* [1:1] Transmit Stopped Enable - TXSE (rw) */
    ureg32 TBUE:1;         /* [2:2] Transmit Buffer Unavailable Enable - TBUE (rw) */
    ureg32 reserved_3:3;   /* [5:3] internal Reserved */
    ureg32 RIE:1;          /* [6:6] Receive Interrupt Enable - RIE (rw) */
    ureg32 RBUE:1;         /* [7:7] Receive Buffer Unavailable Enable - RBUE (rw) */
    ureg32 RSE:1;          /* [8:8] Receive Stopped Enable - RSE (rw) */
    ureg32 RWTE:1;         /* [9:9] Receive Watchdog Timeout Enable - RWTE (rw) */
    ureg32 ETIE:1;         /* [10:10] Early Transmit Interrupt Enable - ETIE (rw) */
    ureg32 ERIE:1;         /* [11:11] Early Receive Interrupt Enable - ERIE (rw) */
    ureg32 FBEE:1;         /* [12:12] Fatal Bus Error Enable - FBEE (rw) */
    ureg32 CDEE:1;         /* [13:13] Context Descriptor Error Enable - CDEE (rw) */
    ureg32 AIE:1;          /* [14:14] Abnormal Interrupt Summary Enable - AIE (rw) */
    ureg32 NIE:1;          /* [15:15] Normal Interrupt Summary Enable - NIE (rw) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_DMA_CH_INTERRUPT_ENABLE_Bits;

/* DMA Channel Recieve Interrupt Watchdog Timer Register */
typedef struct
{
    ureg32 RWT:8;          /* [7:0] Receive Interrupt Watchdog Timer Count - RWT (rw) */
    ureg32 reserved_8:8;   /* [15:8] internal Reserved */
    ureg32 RWTU:2;         /* [17:16] Receive Interrupt Watchdog Timer Count Units - RWTU (rw) */
    ureg32 reserved_18:14; /* [31:18] internal Reserved */
} ETH_DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_Bits;

/* DMA Channel Slot Function Control and Status Register */
typedef struct
{
    ureg32 ESC:1;          /* [0:0] Enable Slot Comparison - ESC (rw) */
    ureg32 ASC:1;          /* [1:1] Advance Slot Check - ASC (rw) */
    ureg32 reserved_2:2;   /* [3:2] internal Reserved */
    ureg32 SIV:12;         /* [15:4] Slot Interval Value - SIV (rw) */
    ureg32 RSN:4;          /* [19:16] Reference Slot Number - RSN (r) */
    ureg32 reserved_20:12; /* [31:20] internal Reserved */
} ETH_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_Bits;

/* DMA Channel Current Application Receive Descriptor Register */
typedef struct
{
    ureg32 CURRDESAPTR:32; /* [31:0] Application Receive Descriptor Address Pointer - CURRDESAPTR (r) */
} ETH_DMA_CH_CURRENT_APP_RXDESC_Bits;

/* DMA Channel Current Application Transmit Buffer Address Register */
typedef struct
{
    ureg32 CURTBUFAPTR:32; /* [31:0] Application Transmit Buffer Address Pointer - CURTBUFAPTR (r) */
} ETH_DMA_CH_CURRENT_APP_TXBUFFER_Bits;

/* DMA Channel Current Application Receive Buffer Address Register */
typedef struct
{
    ureg32 CURRBUFAPTR:32; /* [31:0] Application Receive Buffer Address Pointer - CURRBUFAPTR (r) */
} ETH_DMA_CH_CURRENT_APP_RXBUFFER_Bits;

/* DMA Channel Current Application Transmit Descriptor Register */
typedef struct
{
    ureg32 CURTDESAPTR:32; /* [31:0] Application Transmit Descriptor Address Pointer - CURTDESAPTR (r) */
} ETH_DMA_CH_CURRENT_APP_TXDESC_Bits;

/* DMA Channel Status Register */
typedef struct
{
    unsigned int TI:1;           /* [0:0] Transmit Interrupt - TI (rw) */
    unsigned int TPS:1;          /* [1:1] Transmit Process Stopped - TPS (rw) */
    unsigned int TBU:1;          /* [2:2] Transmit Buffer Unavailable - TBU (rw) */
    unsigned int reserved_3:3;   /* [5:3] internal Reserved */
    unsigned int RI:1;           /* [6:6] Receive Interrupt - RI (rw) */
    unsigned int RBU:1;          /* [7:7] Receive Buffer Unavailable - RBU (rw) */
    unsigned int RPS:1;          /* [8:8] Receive Process Stopped - RPS (rw) */
    unsigned int RWT:1;          /* [9:9] Receive Watchdog Timeout - RWT (rw) */
    unsigned int ETI:1;          /* [10:10] Early Transmit Interrupt - ETI (rw) */
    unsigned int ERI:1;          /* [11:11] Early Receive Interrupt - ERI (rw) */
    unsigned int FBE:1;          /* [12:12] Fatal Bus Error - FBE (rw) */
    unsigned int CDE:1;          /* [13:13] Context Descriptor Error - CDE (rw) */
    unsigned int AIS:1;          /* [14:14] Abnormal Interrupt Summary - AIS (rw) */
    unsigned int NIS:1;          /* [15:15] Normal Interrupt Summary - NIS (rw) */
    unsigned int TEB:3;          /* [18:16] Tx DMA Error Bits - TEB (r) */
    unsigned int REB:3;          /* [21:19] Rx DMA Error Bits - REB (r) */
    unsigned int reserved_22:10; /* [31:22] internal Reserved */
} ETH_DMA_CH_STATUS_Bits;

/* DMA Channel Missed Frames Count Register */
typedef struct
{
    ureg32 MFC:11;         /* [10:0] Dropped Packet Counters - MFC (r) */
    ureg32 reserved_11:4;  /* [14:11] internal Reserved */
    ureg32 MFCO:1;         /* [15:15] Overflow status of the MFC Counter - MFCO (r) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_DMA_CH_MISS_FRAME_CNT_Bits;

/* DMA Channel RXP_ACCEPT_CNT Register */
typedef struct
{
    ureg32 RXPAC:31;  /* [30:0] Rx Parser Accept Counters - RXPAC (r) */
    ureg32 RXPACOF:1; /* [31:31] Rx Parser Accept Counter Overflow Bit - RXPACOF (r) */
} ETH_DMA_CH_RXP_ACCEPT_CNT_Bits;

/* MTL Block */
/* MTL Operation Mode Register */
typedef struct
{
    ureg32 reserved_0:1;   /* [0:0] internal Reserved */
    ureg32 DTXSTS:1;       /* [1:1] Drop Transmit Status - DTXSTS (rw) */
    ureg32 RAA:1;          /* [2:2] Receive Arbitration Algorithm - RAA (rw), SP or WSP */
    ureg32 reserved_3:2;   /* [4:3] internal Reserved */
    ureg32 SCHALG:2;       /* [6:5] Tx Scheduling Algorithm - SCHALG (rw) , WRR/SP/ WFQ(DCB)/DWRR(DCB) */
    ureg32 reserved_7:1;   /* [7:7] internal Reserved */
    ureg32 CNTPRST:1;      /* [8:8] Counters Preset - CNTPRST (rw) */
    ureg32 CNTCLR:1;       /* [9:9] Counters Reset - CNTCLR (rw) */
    ureg32 reserved_10:4;  /* [13:10] internal Reserved */
    ureg32 RXPED:1;        /* [14:14] RxParser Error/Incomplete Parsing Packet Drop Enable*/
    ureg32 FRPE:1;         /* [15:15] Flexible Rx Parser Enable */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MTL_OPERATION_MODE_Bits;

/* FIFO debug Register */
typedef struct
{
    ureg32 FDBGEN:1;       /* [0:0] FIFO Debug Access Enable */
    ureg32 DBGMOD:1;       /* [1:1] Debug Mode Access to FIFO */
    ureg32 BYTEEN:2;       /* [3:2] Byte Enables */
    ureg32 reserved_4:1;   /* [4:4] internal Reserved */
    ureg32 PKTSTATE:2;     /* [6:5] Encoded Packet State */
    ureg32 reserved_7:1;   /* [7:7] internal Reserved */
    ureg32 RSTALL:1;       /* [8:8] Reset All Pointers (rw) */
    ureg32 RSTSEL:1;       /* [9:9] Reset Pointers of Selected FIFO */
    ureg32 FIFORDEN:1;     /* [10:10] FIFO Read Enable */
    ureg32 FIFOWREN:1;     /* [11:11] FIFO Write Enable */
    ureg32 FIFOSEL:2;      /* [13:12] FIFO Selected for Access */
    ureg32 PKTIE:1;        /* [14:14] Receive Packet Available Interrupt Status Enable(rw) */
    ureg32 STSIE:1;        /* [15:15] Transmit Status Available Interrupt Status Enable (rw) */
    ureg32 EIEE:1;         /* [16:16] ECC Inject Error Enable for Tx, Rx and TSO memories */
    ureg32 EIAEE:1;        /* [17:17] ECC Inject Address Error for Tx, Rx and TSO memories */
    ureg32 EIEC:1;         /* [18:18] ECC Inject Error Control for Tx, Rx and TSO memories */
    ureg32 reserved_19:13; /* [31:19] internal Reserved */
} ETH_MTL_DBG_CTL_Bits;

/* FIFO debug status Register*/
typedef struct
{
    ureg32 FIFOBUSY:1;    /* [0:0] FIFO busy */
    ureg32 PKTSTATE:2;    /* [2:1] Encoded Packet State */
    ureg32 BYTEEN:2;      /* [4:3] Byte Enables */
    ureg32 reserved_5:3;  /* [7:5] internal Reserved */
    ureg32 PKTI:1;        /* [8:8] Receive Packet Available Interrupt Status */
    ureg32 STSI:1;        /* [9:9] Transmit Status Available Interrupt Status*/
    ureg32 reserved_10:5; /* [14:10] internal Reserved */
    ureg32 LOCR:17;       /* [31:15] Remaining Locations in the FIFO */
} ETH_MTL_DBG_STS_Bits;

/* FIFO debug data Register*/
typedef struct
{
    ureg32 FDBGDATA:32; /* [31:0] FIFO debug data */
} ETH_MTL_FIFO_DEBUG_DATA_Bits;

/* MTL Interrupt Status Register */
typedef struct
{
    ureg32 Q0IS:1;        /* [0:0] Queue 0 Interrupt status - Q0IS (r) */
    ureg32 Q1IS:1;        /* [1:1] Queue 1 Interrupt status - Q1IS (r) */
    ureg32 Q2IS:1;        /* [2:2] Queue 2 Interrupt status - Q2IS (r) */
    ureg32 Q3IS:1;        /* [3:3] Queue 3 Interrupt status - Q3IS (r) */
    ureg32 reserved_4:4;  /* [7:4] internal Reserved */
    ureg32 reserved_8:8;  /* [15:8] internal Reserved */
    ureg32 reserved_16:1; /* [16:16] internal Reserved */
    ureg32 DBGIS:1;       /* [17:17] Debug Interrupt status */
    ureg32 ESTIS:1;       /* [18:18] EST Interrupt status */
    ureg32 reserved_19:4; /* [22:19] internal Reserved */
    ureg32 MTLPIS:1;      /* [23:23] MTL Rx Parser Interrupt status */
    ureg32 reserved_31:8; /* [31:24] internal Reserved */
} ETH_MTL_INTERRUPT_STATUS_Bits;

/* MTL Receive Queue and DMA Channel Mapping 0 Register */
typedef struct
{
    ureg32 Q0MDMACH:2;    /* [1:0] Queue 0 Mapped to DMA Channel - Q0MDMACH (rw) */
    ureg32 reserved_2:2;  /* [3:2] internal Reserved */
    ureg32 Q0DDMACH:1;    /* [4:4] Queue 0 Enabled for DA-based DMA Channel Selection - Q0DDMACH (rw) */
    ureg32 reserved_5:3;  /* [7:5] internal Reserved */
    ureg32 Q1MDMACH:2;    /* [9:8] Queue 1 Mapped to DMA Channel - Q1MDMACH (rw) */
    ureg32 reserved_10:2; /* [11:10] internal Reserved */
    ureg32 Q1DDMACH:1;    /* [12:12] Queue 1 Enabled for DA-based DMA Channel Selection - Q1DDMACH (rw) */
    ureg32 reserved_13:3; /* [15:13] internal Reserved */
    ureg32 Q2MDMACH:2;    /* [17:16] Queue 2 Mapped to DMA Channel - Q2MDMACH (rw) */
    ureg32 reserved_18:2; /* [19:18] internal Reserved */
    ureg32 Q2DDMACH:1;    /* [20:20] Queue 2 Enabled for DA-based DMA Channel Selection - Q2DDMACH (rw) */
    ureg32 reserved_21:3; /* [23:21] internal Reserved */
    ureg32 Q3MDMACH:2;    /* [25:24] Queue 3 Mapped to DMA Channel - Q3MDMACH (rw) */
    ureg32 reserved_26:2; /* [27:26] internal Reserved */
    ureg32 Q3DDMACH:1;    /* [28:28] Queue 3 Enabled for Dynamic (per packet) DMA Channel Selection - Q3DDMACH(rw) */
    ureg32 reserved_29:3; /* [31:29] internal Reserved */
} ETH_MTL_RXQ_DMA_MAP0_Bits;

/* MTL control the operation of time based scheduling Register */
typedef struct
{
    ureg32 ESTM:1;       /* [0:0] EST offset mode */
    ureg32 LEOV:1;       /* [1:1] Launch expiry offset valid */
    ureg32 reserved_2:2; /* [3:2] internal Reserved */
    ureg32 LEGOS:3;      /* [6:4] Launch expiry GSN offset */
    ureg32 reserved_7:1; /* [7:5] internal Reserved */
    ureg32 LEOS:24;      /* [31:8] Launch expiry offset */
} ETH_MTL_TBS_CTRL_Bits;

/* MTL EST control Register */
typedef struct
{
    ureg32 EEST:1;        /* [0:0] Enable EST */
    ureg32 SSWL:1;        /* [1:1] Switch to S/W owned list */
    ureg32 reserved_2:1;  /* [2:2] internal Reserved */
    ureg32 QHLBF:1;       /* [3:3] Quick assertion of HLBF error */
    ureg32 DDBF:1;        /* [4:4] Do not drop frames during frame size error */
    ureg32 DFBS:1;        /* [5:5] Drop frames causing scheduling error */
    ureg32 LCSE:2;        /* [7:6] Loop count to report scheduling error */
    ureg32 TILS:3;        /* [10:8] Time interval left shift amount */
    ureg32 reserved_11:1; /* [11:11] internal Reserved */
    ureg32 CTOV:12;       /* [23:12] Current time offset value */
    ureg32 PTOV:8;        /* [31:24] PTP time offset value */
} ETH_MTL_EST_CONTROL_Bits;

/* ETH_MTL_EST_EXT_CONTROL Register */
typedef struct
{
    ureg32 OVHD:6;        /* [5:0] Overhead byte value */
    ureg32 reserved_6:26; /* [31:6] internal Reserved */
} ETH_MTL_EST_EXT_CONTROL_Bits;

/* ETH_MTL_EST_STATUS Register */
typedef struct
{
    ureg32 SWLC:1;         /* [0:0] Switch to S/W owned list complete */
    ureg32 BTRE:1;         /* [1:1] BTR error */
    ureg32 HLBF:1;         /* [2:2] Head-Of_Line blocking due to frame size */
    ureg32 HLBS:1;         /* [3:3] Head-Of_Line blocking due to scheduling */
    ureg32 CGCE:1;         /* [4:4] Constant gate control error */
    ureg32 reserved_5:2;   /* [6:5] internal Reserved */
    ureg32 SWOL:1;         /* [7:7] S/W owned list */
    ureg32 BTRL:8;         /* [15:8] BTR error loop count */
    ureg32 CGSN:4;         /* [19:16] Current GCL slot number */
    ureg32 reserved_20:12; /* [31:20] internal Reserved */
} ETH_MTL_EST_STATUS_Bits;

/* ETH_MTL_EST_SCH_ERROR Register */
typedef struct
{
    ureg32 SEQN:4;        /* [3:0] Schedule error queue number */
    ureg32 reserved_4:28; /* [31:4] internal Reserved */
} ETH_MTL_EST_SCH_ERROR_Bits;

/* ETH_MTL_EST_FRM_SIZE_ERROR Register */
typedef struct
{
    ureg32 FEQN:4;        /* [3:0] Frame size error queue number */
    ureg32 reserved_4:28; /* [31:4] internal Reserved */
} ETH_MTL_EST_FRM_SIZE_ERROR_Bits;

/* ETH_MTL_EST_FRM_SIZE_CAPTURE Register */
typedef struct
{
    ureg32 HBFS:15;        /* [14:0] Frame size of HLBF */
    ureg32 reserved_15:1;  /* [15:15] internal Reserved */
    ureg32 HBFQ:2;         /* [17:16] Queue number of HLBF */
    ureg32 reserved_18:14; /* [31:18] internal Reserved */
} ETH_MTL_EST_FRM_SIZE_CAPTURE_Bits;

/* ETH_MTL_EST_INTR_ENABLE Register */
typedef struct
{
    ureg32 IECC:1;        /* [0:0] Interrupt enable for switch list */
    ureg32 IEBE:1;        /* [1:1] Interrupt enable for BTR error */
    ureg32 IEHF:1;        /* [2:2] Interrupt enable for HLBF */
    ureg32 IEHS:1;        /* [3:3] Interrupt enable for HLBS */
    ureg32 CGCE:1;        /* [4:4] Interrupt enable for CGCE */
    ureg32 reserved_5:27; /* [31:5] internal Reserved */
} ETH_MTL_EST_INTR_ENABLE_Bits;

/* ETH_MTL_EST_GCL_CONTROL Register */
typedef struct
{
    ureg32 SRWO:1;        /* [0:0] Start read or write operation */
    ureg32 R1W0:1;        /* [1:1] Read 1, write 0 */
    ureg32 GCRR:1;        /* [2:2] Gate control related register */
    ureg32 reserved_3:1;  /* [3:3] internal Reserved */
    ureg32 DBGM:1;        /* [4:4] Debug Mode */
    ureg32 DBGB:1;        /* [5:5] Debug mode bank select */
    ureg32 reserved_6:2;  /* [7:6] internal Reserved */
    ureg32 ADDR:7;        /* [14:8] Gate control list address */
    ureg32 reserved_15:6; /* [20:15] internal Reserved */
    ureg32 ESTEIEE:1;     /* [21:21] EST ECC inject error enable */
    ureg32 ESTEIAEE:1;    /* [22:22] EST ECC inject address error enable */
    ureg32 ESTEIEC:1;     /* [23:23] ECC inject error control for EST memory */
    ureg32 reserved_24:8; /* [31:24] internal Reserved */
} ETH_MTL_EST_GCL_CONTROL_Bits;

/* ETH_MTL_EST_GCL_DATA Register */
typedef struct
{
    ureg32 GCD:32; /* [31:0] Gate control data */
} ETH_MTL_EST_GCL_DATA_Bits;

/* ETH_MTL_FPE_CTRL_STS Register */
typedef struct
{
    ureg32 AFSZ:2;         /* [1:0] Additional fragment size */
    ureg32 reserved_2:5;   /* [6:2] internal Reserved */
    ureg32 LBHT:1;         /* [7:7] Level based hold transition */
    ureg32 PEC:4;          /* [11:8] Preemption classification */
    ureg32 reserved_12:16; /* [27:12] internal Reserved */
    ureg32 HRS:1;          /* [28:28] Hold/Release status */
    ureg32 reserved_29:3;  /* [31:29] internal Reserved */
} ETH_MTL_FPE_CTRL_STS_Bits;

/* ETH_MTL_FPE_ADVANCE Register */
typedef struct
{
    ureg32 HADV:16; /* [15:0] Hold Advance */
    ureg32 RADV:16; /* [31:16] Release Advance */
} ETH_MTL_FPE_ADVANCE_Bits;

/* ETH_MTL_RXP_CONTROL_STATUS Register */
typedef struct
{
    ureg32 NVE:7;         /* [6:0] Number of valid entry address/index in instruction table */
    ureg32 reserved_7:4;  /* [10:7] internal Reserved */
    ureg32 OKI_DME:1;     /* [11:11] Instruction's OK index dual meaning enable */
    ureg32 reserved_12:4; /* [15:12] internal Reserved */
    ureg32 NPE:7;         /* [22:16] Number of parsable entries in instruction table */
    ureg32 reserved_23:7; /* [29:23] internal Reserved */
    ureg32 ELIRS:1;       /* [30:30] Enable last instruction in Rx status */
    ureg32 RXPI:1;        /* [31:31] Rx parser in idle state */
} ETH_MTL_RXP_CONTROL_STATUS_Bits;

/* ETH_MTL_RXP_INTERRUPT_CONTROL_STATUS Register */
typedef struct
{
    ureg32 NVEOVIS:1;      /* [0:0] Number of valid entry address/index overflow status */
    ureg32 NPEOVIS:1;      /* [1:1] Number of parsable entry overflow status */
    ureg32 FOOVIS:1;       /* [2:2] Frame offset overflow interrupt status */
    ureg32 PDRFIS:1;       /* [3:3] Packet dropped due to RF interrupt status */
    ureg32 reserved_4:12;  /* [15:4] internal Reserved */
    ureg32 NVEOVIE:1;      /* [16:16] Number of valid entries overflow interrupt enable */
    ureg32 NPEOVIE:1;      /* [17:17] Number of parsable entries overflow interrupt enable */
    ureg32 FOOVIE:1;       /* [18:18] Frame offset overflow interrupt enable */
    ureg32 PDRFIE:1;       /* [19:19] Packet drop due to RF interrupt enable */
    ureg32 reserved_20:12; /* [31:20] internal Reserved */
} ETH_MTL_RXP_INTERRUPT_CONTROL_STATUS_Bits;

/* ETH_MTL_RXP_DROP_CNT Register */
typedef struct
{
    ureg32 RXPDC:31;   /* [30:0] Rx Parser drop count */
    ureg32 RXPDCOVF:1; /* [31:31] Rx Parser drop counter overflow bit */
} ETH_MTL_RXP_DROP_CNT_Bits;

/* ETH_MTL_RXP_ERROR_CNT Register */
typedef struct
{
    ureg32 RXPEC:31;   /* [30:0] Rx Parser error count */
    ureg32 RXPECOVF:1; /* [31:31] Rx Parser error counter overflow bit */
} ETH_MTL_RXP_ERROR_CNT_Bits;

/* MTL_RXP_INDIRECT_ACC_CONTROL_STATUS Register */
typedef struct
{
    ureg32 ADDR:9;        /* [8:0] FRP instruction table offset address */
    ureg32 reserved_9:7;  /* [15:9] internal Reserved */
    ureg32 WRRDN:1;       /* [16:16] Read write control */
    ureg32 reserved_17:3; /* [19:17] internal Reserved */
    ureg32 RXPEIEE:1;     /* [20:20] ECC inject error enable for Rx parser memory */
    ureg32 RXPEIAEE:1;    /* [21:21] ECC inject address error enable for rx parser memory */
    ureg32 RXPEIEC:1;     /* [22:22] ECC inject error control for rx parser memory */
    ureg32 reserved_23:8; /* [30:23] internal Reserved */
    ureg32 STARTBUSY:1;   /* [31:31] FRP instruction table access busy */
} ETH_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_Bits;

/* MTL the data associated to indirect access to Rx Parser memory Register */
typedef struct
{
    ureg32 DATA:32; /* [31:0] FRP instruction table write/read data */
} ETH_MTL_RXP_INDIRECT_ACC_DATA_Bits;

/* MTL bypass count of Rx Parser Register */
typedef struct
{
    ureg32 RXPBC:31;  /* [30:0] Rx parser bypass count */
    ureg32 RXPBCOF:1; /* [31:31] Rx parser bypass counter overflow bit */
} ETH_MTL_RXP_BYPASS_CNT_Bits;

/* MTL ECC Control Register */
typedef struct
{
    ureg32 MTXEE:1;       /* [0:0] MTL Tx FIFO ECC Enable (rw) */
    ureg32 MRXEE:1;       /* [1:1] MTL Rx FIFO ECC Enable (rw)*/
    ureg32 MESTEE:1;      /* [2:2] MTL EST ECC Enable (rw) */
    ureg32 MRXPEE:1;      /* [3:3] MTL Rx Parser ECC Enable */
    ureg32 reserved_4:1;  /* [4:4] internal Reserved,TSOEE-TSO memory ECC Enable(rw) */
    ureg32 reserved_5:3;  /* [7:5] internal Reserved */
    ureg32 MEEAO:1;       /* [8:8] MTL ECC Error Address Status Over-ride (rw) */
    ureg32 reserved_9:23; /* [31:9] internal Reserved */
} ETH_MTL_ECC_CTL_Bits;

/* MTL Safety Interrupt Status Register */
typedef struct
{
    ureg32 MECIS:1;       /* [0:0] MTL ECC Correctable error interrupt status */
    ureg32 MEUIS:1;       /* [1:1] MTL ECC Uncorrectable error interrupt status */
    ureg32 reserved_2:29; /* [30:2] internal Reserved */
    ureg32 reserved_31:1; /* [31:31] MTL ECC Uncorrectable error interrupt status - MCSIS */
} ETH_MTL_SAFETY_INTERRUPT_STATUS_Bits;

/* MTL Safety Interrupt Enable Register */
typedef struct
{
    ureg32 TXCEIE:1;       /* [0:0] MTL ECC Tx memory Correctable Error Interrupt Enable */
    ureg32 reserved_1:3;   /* [3:1] internal Reserved */
    ureg32 RXCEIE:1;       /* [4:4] MTL ECC Rx memory Correctable Error Interrupt Enable */
    ureg32 reserved_5:3;   /* [7:5] internal Reserved*/
    ureg32 ECEIE:1;        /* [8:8] EST memory Correctable Error Interrupt Enable */
    ureg32 reserved_9:3;   /* [11:9] internal Reserved */
    ureg32 RPCEIE:1;       /* [12:12] Rx Parser memory Correctable Error Interrupt Enable */
    ureg32 reserved_13:19; /* [31:13] internal Reserved */
} ETH_MTL_ECC_INTERRUPT_ENABLE_Bits;

/* MTL ECC Interrupt Status Register */
typedef struct
{
    ureg32 TXCES:1;        /* [0:0] MTL Tx memory Correctable Error Status */
    ureg32 TXAMS:1;        /* [1:1] MTL TX memory Address Mismatch Status */
    ureg32 TXUES:1;        /* [2:2] MTL Tx memory Uncorrectable Error Status */
    ureg32 reserved_3:1;   /* [3:3] internal Reserved*/
    ureg32 RXCES:1;        /* [4:4] MTL Rx memory Correctable Error Status */
    ureg32 RXAMS:1;        /* [5:5] MTL RX memory Address Mismatch Status */
    ureg32 RXUES:1;        /* [6:6] MTL Rx memory Uncorrectable Error Status */
    ureg32 reserved_7:1;   /* [7:7] internal Reserved */
    ureg32 ECES:1;         /* [8:8] MTL EST memory correctable Error Status */
    ureg32 EAMS:1;         /* [9:9] MTL EST memory address mismatch Status */
    ureg32 EUES:1;         /* [10:10] MTL EST memory Uncorrectable Error Status */
    ureg32 reserved_11:1;  /* [11:11] internal Reserved */
    ureg32 RPCES:1;        /* [12:12] MTL Rx parser memory correctable Error Status */
    ureg32 RPAMS:1;        /* [13:13] MTL Rx parser memory address mismatch Status */
    ureg32 RPUES:1;        /* [14:14] MTL Rx parser memory Uncorrectable Error Status */
    ureg32 reserved_15:17; /* [31:15] internal Reserved */
} ETH_MTL_ECC_INTERRUPT_STATUS_Bits;

/* MTL ECC Error Status Register */
typedef struct
{
    ureg32 EESRE:1;       /* [0:0] MTL ECC Error Status Read Enable */
    ureg32 EMS:3;         /* [3:1] MTL ECC Memory Selection */
    ureg32 CCES:1;        /* [4:4] MTL ECC Clear Correctable Error Status */
    ureg32 CUES:1;        /* [5:5] MTL ECC Clear Uncorrectable error status */
    ureg32 reserved_6:26; /* [31:6] internal Reserved */
} ETH_MTL_ECC_ERR_STS_RCTL_Bits;

/* MTL ECC Error Address Register */
typedef struct
{
    ureg32 ECEAS:16; /* [15:0] MTL ECC Correctable Error Address Status */
    ureg32 EUEAS:16; /* [31:16] MTL ECC Uncorrectable Error Address Status */
} ETH_MTL_ECC_ERR_ADDR_STATUS_Bits;

/* MTL ECC Error Count Status Register */
typedef struct
{
    ureg32 ECECS:8;        /* [7:0] MTL ECC Ucorrectable Error Counter Status */
    ureg32 reserved_8:8;   /* [15:8] internal Reserved */
    ureg32 EUECS:4;        /* [19:16] MTL ECC Correctable Error Counter Status */
    ureg32 reserved_20:12; /* [31:20] internal Reserved */
} ETH_MTL_ECC_ERR_CNTR_STATUS_Bits;

/* MTL_DPP_CONTROL Register */
typedef struct
{
    ureg32 EDPP:1;         /* [0:0] Enable data path parity protection */
    ureg32 OPE:1;          /* [1:0] Odd parity enable */
    ureg32 reserved_2:4;   /* [5:2] internal Reserved */
    ureg32 IPETRD:1;       /* [6:6] Insert parity error in DMA Tx/Rx descriptor parity checker */
    ureg32 IPEMTF:1;       /* [7:7] Insert parity error in MTL Tx FIFO write data parity checker */
    ureg32 IPEMTS:1;       /* [8:8] Insert parity error in MTL Tx status FIFO parity checker */
    ureg32 IPERID:1;       /* [9:9] Insert parity error in Rx interface data parity checker */
    ureg32 reserved_10:3;  /* [12:10] internal Reserved */
    ureg32 IPEMTBU:1;      /* [13:13] Insert parity error in MAC TBU data parity checker */
    ureg32 IPEMTFC:1;      /* [14:14] Insert parity error in MAC TFC data parity checker */
    ureg32 IPEMRWC:1;      /* [15:15] Insert parity error in MTL RWC data parity checker */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} ETH_MTL_DPP_CONTROL_Bits;

/* MTL_DPP_ECC_EIC Register */
typedef struct
{
    ureg32 BLEI:8;         /* [7:0] Bit location of error injection */
    ureg32 reserved_8:8;   /* [15:8] internal Reserved */
    ureg32 EIM:1;          /* [16:16] Error injection mode */
    ureg32 reserved_17:15; /* [31:17] internal Reserved */
} ETH_MTL_DPP_ECC_EIC_Bits;

/* MTL Queue 0 Transmit Operation Mode Register */
typedef struct
{
    ureg32 FTQ:1;        /* [0:0] Flush Transmit Queue - FTQ (rw) */
    ureg32 TSF:1;        /* [1:1] Transmit Store and Forward - TSF (rw) */
    ureg32 TXQEN:2;      /* [3:2] Transmit Queue Enable - TXQEN (rw) */
    ureg32 TTC:3;        /* [6:4] Transmit Threshold Control - TTC (rw) */
    ureg32 reserved_7:9; /* [15:7] internal Reserved */
    ureg32 TQS:4; /* [19:16] Transmit Queue Size - TQS (rw), depends on the memory size, 4bit=> (15+1)*256=4096 */
    ureg32 reserved_20:12; /* [31:20] internal Reserved */
} ETH_MTL_TXQ0_OPERATION_MODE_Bits;

/* MTL Queue 0 Transmit Underflow Counter Register */
typedef struct
{
    ureg32 UFFRMCNT:11;    /* [10:0] Underflow Packet Counter - UFFRMCNT (r) */
    ureg32 UFCNTOVF:1;     /* [11:11] Overflow Bit for Underflow Packet Counter - UFCNTOVF (r) */
    ureg32 reserved_12:20; /* [31:12] internal Reserved */
} ETH_MTL_TXQ0_UNDERFLOW_Bits;

/* MTL Queue 0 Transmit Debug Register */
typedef struct
{
    ureg32 TXQPAUSED:1;   /* [0:0] Transmit Queue in Pause - TXQPAUSED (r) */
    ureg32 TRCSTS:2;      /* [2:1] MTL Tx Queue Read Controller Status - TRCSTS (r) */
    ureg32 TWCSTS:1;      /* [3:3] MTL Tx Queue Write Controller Status - TWCSTS (r) */
    ureg32 TXQSTS:1;      /* [4:4] MTL Tx Queue Not Empty Status - TXQSTS (r) */
    ureg32 TXSTSFSTS:1;   /* [5:5] MTL Tx Status FIFO Full Status - TXSTSFSTS (r) */
    ureg32 reserved_6:10; /* [15:6] internal Reserved */
    ureg32 PTXQ:3;        /* [18:16] Number of Packets in the Transmit Queue - PTXQ (r) */
    ureg32 reserved_19:1; /* [19:19] internal Reserved */
    ureg32 STXSTSF:3;     /* [22:20] Number of Status Words in Tx Status FIFO of Queue - STXSTSF (r) */
    ureg32 reserved_23:9; /* [31:23] internal Reserved */
} ETH_MTL_TXQ0_DEBUG_Bits;

/* MTL Queue 0 Transmit Status Register */
typedef struct
{
    ureg32 ABS:24; /* [23:0] Average Bits per Slot This field contains the average transmitted bits per slot - ABS(r) */
    ureg32 reserved_24:8; /* [31:24] internal Reserved */
} ETH_MTL_TXQ0_ETS_STATUS_Bits;

/* MTL Queue 0 Transmit Quantum or Weights Register */
typedef struct
{
    ureg32 ISCQW:21;       /* [20:0] Quantum or Weights - ISCQW (rw) */
    ureg32 reserved_21:11; /* [31:21] internal Reserved */
} ETH_MTL_TXQ0_QUANTUM_WEIGHT_Bits;

/* MTL Queue0 Interrupt Status Register */
typedef struct
{
    ureg32 TXUNFIS:1;     /* [0:0] Transmit Queue Underflow Interrupt Status - TXUNFIS (rw) */
    ureg32 ABPSIS:1;      /* [1:1] Average Bits Per Slot Interrupt Status - ABPSIS (rw) */
    ureg32 reserved_2:6;  /* [7:2] internal Reserved */
    ureg32 TXUIE:1;       /* [8:8] Transmit Queue Underflow Interrupt Enable - TXUIE (rw) */
    ureg32 ABPSIE:1;      /* [9:9] Average Bits Per Slot Interrupt Enable - ABPSIE (rw) */
    ureg32 reserved_10:6; /* [15:10] internal Reserved */
    ureg32 RXOVFIS:1;     /* [16:16] Receive Queue Overflow Interrupt Status - RXOVFIS (rw) */
    ureg32 reserved_17:7; /* [23:17] internal Reserved */
    ureg32 RXOIE:1;       /* [24:24] Receive Queue Overflow Interrupt Enable - RXOIE (rw) */
    ureg32 reserved_25:7; /* [31:25] internal Reserved */
} ETH_MTL_Q0_INTERRUPT_CONTROL_STATUS_Bits;

/* MTL Queue 0 Receive Operation Mode Register */
typedef struct
{
    ureg32 RTC:2;         /* [1:0] Receive Queue Threshold Control - RTC (rw) */
    ureg32 reserved_2:1;  /* [2:2] internal Reserved */
    ureg32 FUP:1;         /* [3:3] Forward Undersized Good Packets - FUP (rw) */
    ureg32 FEP:1;         /* [4:4] Forward Error Packets - FEP (rw) */
    ureg32 RSF:1;         /* [5:5] Receive Queue Store and Forward - RSF (rw) */
    ureg32 DIS_TCP_EF:1;  /* [6:6] Disable Dropping of TCP/IP Checksum Error Packets - DIS_TCP_EF (rw) */
    ureg32 EHFC:1;        /* [7:7] Enable Hardware Flow Control - EHFC (rw) */
    ureg32 RFA:4;         /* [11:8] Threshold for Activating Flow Control (in half-duplex and full-duplex - RFA(rw) */
    ureg32 reserved_12:2; /* [13:12] internal Reserved */
    ureg32 RFD:4; /* [17:14] Threshold for Deactivating Flow Control (in half-duplex and full-duplex modes) - RFD(rw) */
    ureg32 reserved_18:2; /* [19:18] internal Reserved */
    ureg32 RQS:5;         /* [24:20] Receive Queue Size - RQS (rw),32*256 = 8192, 16384*2*4/256==512 */
    ureg32 reserved_25:7; /* [31:25] internal Reserved */
} ETH_MTL_RXQ0_OPERATION_MODE_Bits;

/* MTL Queue 0 Receive Missed Packet and Overflow Counter Register */
typedef struct
{
    ureg32 OVFPKTCNT:11;  /* [10:0] Overflow Packet Counter - OVFPKTCNT (r) */
    ureg32 OVFCNTOVF:1;   /* [11:11] Overflow Counter Overflow Bit - OVFCNTOVF (r) */
    ureg32 reserved_12:4; /* [15:12] internal Reserved */
    ureg32 MISPKTCNT:11;  /* [26:16] Missed Packet Counter - MISPKTCNT (r) */
    ureg32 MISCNTOVF:1;   /* [27:27] Missed Packet Counter Overflow Bit - MISCNTOVF (r) */
    ureg32 reserved_28:4; /* [31:28] internal Reserved */
} ETH_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_Bits;

/* MTL Queue 0 Receive Debug Register */
typedef struct
{
    ureg32 RWCSTS:1;      /* [0:0] MTL Rx Queue Write Controller Active Status - RWCSTS (r) */
    ureg32 RRCSTS:2;      /* [2:1] MTL Rx Queue Read Controller State - RRCSTS (r) */
    ureg32 reserved_3:1;  /* [3:3] internal Reserved */
    ureg32 RXQSTS:2;      /* [5:4] MTL Rx Queue Fill-Level Status - RXQSTS (r) */
    ureg32 reserved_6:10; /* [15:6] internal Reserved */
    ureg32 PRXQ:14;       /* [29:16] Number of Packets in Receive Queue - PRXQ (r) */
    ureg32 reserved_30:2; /* [31:30] internal Reserved */
} ETH_MTL_RXQ0_DEBUG_Bits;

/* MTL Queue 0 Receive Control Register */
typedef struct
{
    ureg32 RXQ_WEGT:3;      /* [2:0] Receive Queue Weight - RXQ_WEGT (rw) */
    ureg32 RXQ_FRM_ARBIT:1; /* [3:3] Receive Queue Packet Arbitration - RXQ_FRM_ARBIT (rw) */
    ureg32 reserved_4:28;   /* [31:4] internal Reserved */
} ETH_MTL_RXQ0_CONTROL_Bits;

/* MTL Queue Transmit Operation Mode Register */
typedef struct
{
    ureg32 FTQ:1;          /* [0:0] Flush Transmit Queue - FTQ (rw) */
    ureg32 TSF:1;          /* [1:1] Transmit Store and Forward - TSF (rw) */
    ureg32 TXQEN:2;        /* [3:2] Transmit Queue Enable - TXQEN (rw) */
    ureg32 TTC:3;          /* [6:4] Transmit Threshold Control - TTC (rw) */
    ureg32 reserved_7:9;   /* [15:7] internal Reserved */
    ureg32 TQS:4;          /* [19:16] Transmit Queue Size - TQS (rw) */
    ureg32 reserved_20:12; /* [31:20] internal Reserved */
} ETH_MTL_TXQ_OPERATION_MODE_Bits;

/* MTL Queue Transmit Underflow Counter Register */
typedef struct
{
    ureg32 UFFRMCNT:11;    /* [10:0] Underflow Packet Counter - UFFRMCNT (r) */
    ureg32 UFCNTOVF:1;     /* [11:11] Overflow Bit for Underflow Packet Counter - UFCNTOVF (r) */
    ureg32 reserved_12:20; /* [31:12] internal Reserved */
} ETH_MTL_TXQ_UNDERFLOW_Bits;

/* MTL Queue Transmit Debug Register */
typedef struct
{
    ureg32 TXQPAUSED:1;   /* [0:0] Transmit Queue in Pause - TXQPAUSED (r) */
    ureg32 TRCSTS:2;      /* [2:1] MTL Tx Queue Read Controller Status - TRCSTS (r) */
    ureg32 TWCSTS:1;      /* [3:3] MTL Tx Queue Write Controller Status - TWCSTS (r) */
    ureg32 TXQSTS:1;      /* [4:4] MTL Tx Queue Not Empty Status - TXQSTS (r) */
    ureg32 TXSTSFSTS:1;   /* [5:5] MTL Tx Status FIFO Full Status - TXSTSFSTS (r) */
    ureg32 reserved_6:10; /* [15:6] internal Reserved */
    ureg32 PTXQ:3;        /* [18:16] Number of Packets in the Transmit Queue - PTXQ (r) */
    ureg32 reserved_19:1; /* [19:19] internal Reserved */
    ureg32 STXSTSF:3;     /* [22:20] Number of Status Words in Tx Status FIFO of Queue - STXSTSF (r) */
    ureg32 reserved_23:9; /* [31:23] internal Reserved */
} ETH_MTL_TXQ_DEBUG_Bits;

/* MTL Queue Transmit ETS Control Register */
typedef struct
{
    ureg32 reserved_0:2;  /* [1:0] internal Reserved */
    ureg32 AVALG:1;       /* [2:2] AV Algorithm - AVALG (rw) */
    ureg32 CC:1;          /* [3:3] Credit Control - CC (rw) */
    ureg32 SLC:3;         /* [6:4] Slot Count - SLC (rw) */
    ureg32 reserved_7:25; /* [31:7] internal Reserved */
} ETH_MTL_TXQ_ETS_CONTROL_Bits;

/* MTL Queue Transmit ETS Status Register */
typedef struct
{
    ureg32 ABS:24;        /* [23:0] Average Bits per Slot - ABS (r) */
    ureg32 reserved_24:8; /* [31:24] internal Reserved */
} ETH_MTL_TXQ_ETS_STATUS_Bits;

/* MTL Queue Transmit Quantum or Weights Register */
typedef struct
{
    ureg32 ISCQW:21;       /* [20:0] idleSlopeCredit, Quantum or Weights - ISCQW (rw) */
    ureg32 reserved_21:11; /* [31:21] internal Reserved */
} ETH_MTL_TXQ_QUANTUM_WEIGHT_Bits;

/* MTL Queue Transmit SendSlopeCredit Register */
typedef struct
{
    ureg32 SSC:14;         /* [13:0] sendSlopeCredit Value - SSC (rw) */
    ureg32 reserved_14:18; /* [31:14] internal Reserved */
} ETH_MTL_TXQ_SENDSLOPECREDIT_Bits;

/* MTL Queue Transmit HiCredit Register */
typedef struct
{
    ureg32 HC:29;         /* [28:0] hiCredit Value - HC (rw) */
    ureg32 reserved_29:3; /* [31:29] internal Reserved */
} ETH_MTL_TXQ_HICREDIT_Bits;

/* MTL Queue Transmit LoCredit Register */
typedef struct
{
    ureg32 LC:29;         /* [28:0] loCredit Value - LC (rw) */
    ureg32 reserved_29:3; /* [31:29] internal Reserved */
} ETH_MTL_TXQ_LOCREDIT_Bits;

/* MTL Queue Interrupt Status Register */
typedef struct
{
    ureg32 TXUNFIS:1;     /* [0:0] Transmit Queue Underflow Interrupt Status - TXUNFIS (rw) */
    ureg32 ABPSIS:1;      /* [1:1] Average Bits Per Slot Interrupt Status - ABPSIS (rw) */
    ureg32 reserved_2:6;  /* [7:2] internal Reserved */
    ureg32 TXUIE:1;       /* [8:8] Transmit Queue Underflow Interrupt Enable - TXUIE (rw) */
    ureg32 ABPSIE:1;      /* [9:9] Average Bits Per Slot Interrupt Enable - ABPSIE (rw) */
    ureg32 reserved_10:6; /* [15:10] internal Reserved */
    ureg32 RXOVFIS:1;     /* [16:16] Receive Queue Overflow Interrupt Status - RXOVFIS (rw) */
    ureg32 reserved_17:7; /* [23:17] internal Reserved */
    ureg32 RXOIE:1;       /* [24:24] Receive Queue Overflow Interrupt Enable - RXOIE (rw) */
    ureg32 reserved_25:7; /* [31:25] internal Reserved */
} ETH_MTL_Q_INTERRUPT_CONTROL_STATUS_Bits;

/* MTL Queue Receive Operation Mode Register */
typedef struct
{
    ureg32 RTC:2;         /* [1:0] Receive Queue Threshold Control - RTC (rw) */
    ureg32 reserved_2:1;  /* [2:2] internal Reserved */
    ureg32 FUP:1;         /* [3:3] Forward Undersized Good Packets - FUP (rw) */
    ureg32 FEP:1;         /* [4:4] Forward Error Packets - FEP (rw) */
    ureg32 RSF:1;         /* [5:5] Receive Queue Store and Forward - RSF (rw) */
    ureg32 DIS_TCP_EF:1;  /* [6:6] Disable Dropping of TCP/IP Checksum Error Packets - DIS_TCP_EF (rw) */
    ureg32 EHFC:1;        /* [7:7] Enable Hardware Flow Control - EHFC (rw) */
    ureg32 RFA:4;         /* [11:8] Threshold for Activating Flow Control (in half-duplex and full-duplex - RFA(rw) */
    ureg32 reserved_12:2; /* [13:12] internal Reserved */
    /* [17:14] Threshold for Deactivating Flow Control (in half-duplex and full-duplex modes) - RFD(rw) */
    ureg32 RFD:4;
    ureg32 reserved_18:2; /* [19:18] internal Reserved */
    ureg32 RQS:5;         /* [24:20] Receive Queue Size - RQS (rw) */
    ureg32 reserved_25:7; /* [31:25] internal Reserved */
} ETH_MTL_RXQ_OPERATION_MODE_Bits;

/* MTL Queue Receive Missed Packet and Overflow Counter Register */
typedef struct
{
    ureg32 OVFPKTCNT:11;  /* [10:0] Overflow Packet Counter - OVFPKTCNT (r) */
    ureg32 OVFCNTOVF:1;   /* [11:11] Overflow Counter Overflow Bit - OVFCNTOVF (r) */
    ureg32 reserved_12:4; /* [15:12] internal Reserved */
    ureg32 MISPKTCNT:11;  /* [26:16] Missed Packet Counter - MISPKTCNT (r) */
    ureg32 MISCNTOVF:1;   /* [27:27] Missed Packet Counter Overflow Bit - MISCNTOVF (r) */
    ureg32 reserved_28:4; /* [31:28] internal Reserved */
} ETH_MTL_RXQ_MISSED_PACKET_OVERFLOW_CNT_Bits;

/* MTL Queue Receive Debug Register */
typedef struct
{
    ureg32 RWCSTS:1;      /* [0:0] MTL Rx Queue Write Controller Active Status - RWCSTS (r) */
    ureg32 RRCSTS:2;      /* [2:1] MTL Rx Queue Read Controller State - RRCSTS (r) */
    ureg32 reserved_3:1;  /* [3:3] internal Reserved */
    ureg32 RXQSTS:2;      /* [5:4] MTL Rx Queue Fill-Level Status - RXQSTS (r) */
    ureg32 reserved_6:10; /* [15:6] internal Reserved */
    ureg32 PRXQ:14;       /* [29:16] Number of Packets in Receive Queue - PRXQ (r) */
    ureg32 reserved_30:2; /* [31:30] internal Reserved */
} ETH_MTL_RXQ_DEBUG_Bits;

/* MTL Queue Receive Control Register */
typedef struct
{
    ureg32 RXQ_WEGT:3;      /* [2:0] Receive Queue Weight - RXQ_WEGT (rw) */
    ureg32 RXQ_FRM_ARBIT:1; /* [3:3] Receive Queue Packet Arbitration - RXQ_FRM_ARBIT (rw) */
    ureg32 reserved_4:28;   /* [31:4] internal Reserved */
} ETH_MTL_RXQ_CONTROL_Bits;

/* Module Identification Register */
typedef struct
{
    ureg32 MODREV:32; /* [31:0] MODREV */
} ETH_MIR_Bits;

/* General Purpose Control Register */
typedef struct
{
    ureg32 reserved_0:22; /* [21:0] rsv */
    ureg32 PHYSEL:3;      /* [24:22] External Phy Interface PHYSEL MII(3b'000) or GMII(3b'000) or RGMII(3b'001) or
                             RMII(3b'100)*/
    ureg32 reserved_25:7; /* [31:25] internal Reserved */
} ETH_GPCTL_Bits;

/* Skew Control Register,used when RGMII mode */
typedef struct
{
    ureg32 SKEW_TX_CTRL:11; /* [10:0] TX Clock delay control - SKEW_TX_CTRL (rw) */
    ureg32 SKEW_RX_CTRL:11; /* [21:11] RX Clock delay control - SKEW_RX_CTRL (rw) */
    ureg32 reserved_22:10; /* [22:31] internal Reserved */
} ETH_SKEWCTL_Bits;

/* PHY_TXCTL Register */
typedef struct
{
    ureg32 PHY_TXCTL_O:1; /* [0:0] RGMII phy_txctl_o(rw) */
    ureg32 reserved_1:31; /* [31:1] internal Reserved */
} ETH_PHY_TXCTL_Bits;

/* ETH_PPS Register */
typedef struct
{
    ureg32 ETH_PPS_O:2;   /* [1:0] geth_pps(rw) */
    ureg32 reserved_1:30; /* [31:2] internal Reserved */
} ETH_PPS_REGISTER_Bits;

/* Low Power Moder Register */
typedef struct
{
    ureg32 GETH_LPI_MODE:2; /* [1:0] Low power mode */
    ureg32 reserved_1:30;   /* [31:2] internal Reserved */
} ETH_LPMR_Bits;

/* ALAM Register */
typedef struct
{
    ureg32 SAII:1;         /* [0:0] STA_ALAM_IP_INT */
    ureg32 SAWI:1;         /* [1:1] STA_ALAM_WAPPER_INT */
    ureg32 SARI:1;         /* [2:2] STA_ALAM_REG_INT */
    ureg32 SAGLI:1;        /* [3:3] STA_ALAM_GAP_LOGIC_INT */
    ureg32 SAEDI:1;        /* [4:4] STA_ALAM_ETH_DETECT_INT */
    ureg32 SAERWI:1;       /* [5:5] STA_ALAM_ETH_WRAPPER_INT */
    ureg32 SAERCE:1;       /* [6:6] STA_ALAM_ETH_REG_CL_E */
    ureg32 SAEREE:1;       /* [7:7] STA_ALAM_ETH_REG_EN_E */
    ureg32 SAER:1;         /* [8:8] STA_ALAM_ETH_REG */
    ureg32 SAERSE:1;       /* [9:9] STA_ALAM_ETH_REG_SE */
    ureg32 SAERE:1;        /* [10:10] STA_ALAM_ETH_REG */
    ureg32 reserved_11:21; /* [31:11] internal Reserved */
} ETH_EAR_Bits;

/* ALAM_EN Register */
typedef struct
{
    ureg32 SAIIE:2;        /* [1:0] STA_ALAM_IP_INT_EN */
    ureg32 SAWIE:2;        /* [3:2] STA_ALAM_WAPPER_INT_EN */
    ureg32 SARIE:2;        /* [5:4] STA_ALAM_REG_INT_EN */
    ureg32 SAGLIE:2;       /* [7:6] STA_ALAM_GAP_LOGIC_INT_EN */
    ureg32 SAEDIE:2;       /* [9:8] STA_ALAM_ETH_DETECT_INT_EN */
    ureg32 SAERWIE:2;      /* [11:10] STA_ALAM_ETH_WRAPPER_INT_EN */
    ureg32 SAERCEE:2;      /* [13:12] STA_ALAM_ETH_REG_CL_E_EN */
    ureg32 SAEREEE:2;      /* [15:14] STA_ALAM_ETH_REG_EN_E_EN */
    ureg32 SAERE:2;        /* [17:16] STA_ALAM_ETH_REG_EN */
    ureg32 SAERSEE:2;      /* [19:18] STA_ALAM_ETH_REG_SE_EN */
    ureg32 SAEREE:2;       /* [21:20] STA_ALAM_ETH_REG_EN */
    ureg32 reserved_22:10; /* [31:22] internal Reserved */
} ETH_EAER_Bits;

/* ALAM_CLEAN Register */
typedef struct
{
    ureg32 SAIIC:2;        /* [1:0] STA_ALAM_IP_INT_CLEAN */
    ureg32 SAWIC:2;        /* [3:2] STA_ALAM_WAPPER_INT_CLEAN */
    ureg32 SARIC:2;        /* [5:4] STA_ALAM_REG_INT_CLEAN */
    ureg32 SAGLIC:2;       /* [7:6] STA_ALAM_GAP_LOGIC_INT_CLEAN */
    ureg32 SAEDIC:2;       /* [9:8] STA_ALAM_ETH_DETECT_INT_CLEAN */
    ureg32 SAERWIC:2;      /* [11:10] STA_ALAM_ETH_WRAPPER_INT_CLEAN */
    ureg32 SAERCEC:2;      /* [13:12] STA_ALAM_ETH_REG_CL_E_CLEAN */
    ureg32 SAEREEC:2;      /* [15:14] STA_ALAM_ETH_REG_EN_E_CLEAN */
    ureg32 SAERC:2;        /* [17:16] STA_ALAM_ETH_REG_CLEAN */
    ureg32 SAERSEC:2;      /* [19:18] STA_ALAM_ETH_REG_SE_CLEAN */
    ureg32 SAEREC:2;       /* [21:20] STA_ALAM_ETH_REG_CLEAN */
    ureg32 reserved_22:10; /* [31:22] internal Reserved */
} ETH_EACR_Bits;

/* EFSIMDR Register */
typedef struct
{
    ureg32 SAWII:1;       /* [0:0] STA_ALAM_WAPPER_INT_injection */
    ureg32 SAGLII:1;      /* [1:1] STA_ALAM_GAP_LOGIC_INT_injection */
    ureg32 SAEDII:1;      /* [2:2] STA_ALAM_ETH_DETECT_INT_injection */
    ureg32 SAERWII:1;     /* [3:3] STA_ALAM_ETH_WRAPPER_INT_injection */
    ureg32 reserved_4:28; /* [31:4] internal Reserved */
} ETH_EFSIMDR_Bits;

/* EIR Register */
typedef struct
{
    ureg32 SALPAI:1;      /* [0:0] STA_LPM_INT */
    ureg32 SALPI:1;       /* [1:1] STA_LPM_AWAKEN_INT */
    ureg32 reserved_2:30; /* [31:2] internal Reserved */
} ETH_EIR_Bits;

/* EIER Register */
typedef struct
{
    ureg32 SALPIE:2;      /* [1:0] STA_LPM_INT_EN */
    ureg32 reserved_2:30; /* [31:2] internal Reserved */
} ETH_EIER_Bits;

/* EICR Register */
typedef struct
{
    ureg32 SALPIC:2;      /* [1:0] STA_LPM_INT_CLEAN */
    ureg32 reserved_2:30; /* [31:2] internal Reserved */
} ETH_EICR_Bits;

/* AHBEMR Register */
typedef struct
{
    ureg32 AHBEMR:1;      /* [0:0] AHBEMR */
    ureg32 reserved_1:31; /* [31:1] internal Reserved */
} ETH_AHBEMR_Bits;

/* XCVRENR Register */
typedef struct
{
    ureg32 XCVRENR:1;     /* [0:0] XCVRENR */
    ureg32 reserved_1:31; /* [31:1] internal Reserved */
} ETH_XCVRENR_Bits;
/**********************************************************************************************************************
 *                                              ETH Register Definitions
 *********************************************************************************************************************/
/* DMA Channel Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    ETH_DMA_CH_CONTROL_Bits B; /* Bitfield access */
} ETH_DMA_CH_CONTROL;

/* DMA Channel Current Application Receive Buffer Address Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                               /* Unsigned access */
    ETH_DMA_CH_CURRENT_APP_RXBUFFER_Bits B; /* Bitfield access */
} ETH_DMA_CH_CURRENT_APP_RXBUFFER;

/* DMA Channel Current Application Receive Descriptor Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_DMA_CH_CURRENT_APP_RXDESC_Bits B; /* Bitfield access */
} ETH_DMA_CH_CURRENT_APP_RXDESC;

/* DMA Channel Current Application Transmit Buffer Address Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                               /* Unsigned access */
    ETH_DMA_CH_CURRENT_APP_TXBUFFER_Bits B; /* Bitfield access */
} ETH_DMA_CH_CURRENT_APP_TXBUFFER;

/* DMA Channel Current Application Transmit Descriptor Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_DMA_CH_CURRENT_APP_TXDESC_Bits B; /* Bitfield access */
} ETH_DMA_CH_CURRENT_APP_TXDESC;

/* DMA Channel Interrupt Enable Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_DMA_CH_INTERRUPT_ENABLE_Bits B; /* Bitfield access */
} ETH_DMA_CH_INTERRUPT_ENABLE;

/* DMA Channel Missed Frames Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_DMA_CH_MISS_FRAME_CNT_Bits B; /* Bitfield access */
} ETH_DMA_CH_MISS_FRAME_CNT;

/* DMA Channel RXP_ACCEPT_CNT Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_DMA_CH_RXP_ACCEPT_CNT_Bits B; /* Bitfield access */
} ETH_DMA_CH_RXP_ACCEPT_CNT;

/* DMA Channel Receive Descriptor List Address Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_DMA_CH_RXDESC_LIST_ADDRESS_Bits B; /* Bitfield access */
} ETH_DMA_CH_RXDESC_LIST_ADDRESS;

/* DMA Channel Recieve Descriptor Ring Length Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_DMA_CH_RXDESC_RING_LENGTH_Bits B; /* Bitfield access */
} ETH_DMA_CH_RXDESC_RING_LENGTH;

/* DMA Channel Recieve Descriptor Tail Pointer Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_DMA_CH_RXDESC_TAIL_POINTER_Bits B; /* Bitfield access */
} ETH_DMA_CH_RXDESC_TAIL_POINTER;

/* DMA Channel Receive Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_DMA_CH_RX_CONTROL_Bits B; /* Bitfield access */
} ETH_DMA_CH_RX_CONTROL;

/* DMA Channel Recieve Interrupt Watchdog Timer Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                      /* Unsigned access */
    ETH_DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER_Bits B; /* Bitfield access */
} ETH_DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER;

/* DMA Channel Slot Function Control and Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                       /* Unsigned access */
    ETH_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS_Bits B; /* Bitfield access */
} ETH_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS;

/* DMA Channel Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ETH_DMA_CH_STATUS_Bits B; /* Bitfield access */
} ETH_DMA_CH_STATUS;

/* DMA Channel Transmit Descriptor List Address Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_DMA_CH_TXDESC_LIST_ADDRESS_Bits B; /* Bitfield access */
} ETH_DMA_CH_TXDESC_LIST_ADDRESS;

/* DMA Channel Transmit Descriptor Ring Length Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_DMA_CH_TXDESC_RING_LENGTH_Bits B; /* Bitfield access */
} ETH_DMA_CH_TXDESC_RING_LENGTH;

/* DMA Channel Transmit Descriptor Tail Pointer Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_DMA_CH_TXDESC_TAIL_POINTER_Bits B; /* Bitfield access */
} ETH_DMA_CH_TXDESC_TAIL_POINTER;

/* DMA Channel Transmit Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_DMA_CH_TX_CONTROL_Bits B; /* Bitfield access */
} ETH_DMA_CH_TX_CONTROL;

/* DMA_SAFETY_INTERRUPT */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                               /* Unsigned access */
    ETH_DMA_SAFETY_INTERRUPT_STATUS_Bits B; /* Bitfield access */
} ETH_DMA_SAFETY_INTERRUPT_STATUS;

/* AXI LPI Entry interval */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_AXI_LPI_ENTRY_INTERVAL_Bits B; /* Bitfield access */
} ETH_AXI_LPI_ENTRY_INTERVAL;

/* DMA_TBS_CTRL */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    ETH_DMA_TBS_CRTL_Bits B; /* Bitfield access */
} ETH_DMA_TBS_CRTL;

/* DMA Debug Status 0 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_DMA_DEBUG_STATUS0_Bits B; /* Bitfield access */
} ETH_DMA_DEBUG_STATUS0;

/* DMA Debug Status 1 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_DMA_DEBUG_STATUS1_Bits B; /* Bitfield access */
} ETH_DMA_DEBUG_STATUS1;

/* AXI4_TX_AR_ACE_CONTROL Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_AXI4_TX_AR_ACE_CONTROL_Bits B; /* Bitfield access */
} ETH_AXI4_TX_AR_ACE_CONTROL;

/* AXI4_RX_AW_ACE_CONTROL Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_AXI4_RX_AW_ACE_CONTROL_Bits B; /* Bitfield access */
} ETH_AXI4_RX_AW_ACE_CONTROL;

/* AXI4_TXRX_AWAR_ACE_CONTROL Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_AXI4_TXRX_AWAR_ACE_CONTROL_Bits B; /* Bitfield access */
} ETH_AXI4_TXRX_AWAR_ACE_CONTROL;

/* DMA Interrupt Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_DMA_INTERRUPT_STATUS_Bits B; /* Bitfield access */
} ETH_DMA_INTERRUPT_STATUS;

/* DMA Bus Mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    ETH_DMA_MODE_Bits B; /* Bitfield access */
} ETH_DMA_MODE;

/* DMA System Bus Mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_DMA_SYSBUS_MODE_Bits B; /* Bitfield access */
} ETH_DMA_SYSBUS_MODE;

/* Module Identification Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    ETH_MIR_Bits B; /* Bitfield access */
} ETH_MIR;

/* General Purpose Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    ETH_GPCTL_Bits B; /* Bitfield access */
} ETH_GPCTL;

/* MAC One Microsecond Tic Counter Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_1US_TIC_COUNTER_Bits B; /* Bitfield access */
} ETH_MAC_1US_TIC_COUNTER;

/* MAC Address High Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MAC_ADDRESS_HIGH_Bits B; /* Bitfield access */
} ETH_MAC_ADDRESS_HIGH;

/* MAC Address 0 High Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MAC_ADDRESS_HIGH0_Bits B; /* Bitfield access */
} ETH_MAC_ADDRESS_HIGH0;

/* MAC Address Low Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_ADDRESS_LOW_Bits B; /* Bitfield access */
} ETH_MAC_ADDRESS_LOW;

/* MAC Address 0 Low Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MAC_ADDRESS_LOW0_Bits B; /* Bitfield access */
} ETH_MAC_ADDRESS_LOW0;

/* MAC Configuration Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MAC_CONFIGURATION_Bits B; /* Bitfield access */
} ETH_MAC_CONFIGURATION;

/* MAC CSR Software Controls Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_CSR_SW_CTRL_Bits B; /* Bitfield access */
} ETH_MAC_CSR_SW_CTRL;

/* This register controls the operation of Frame Preemption */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MAC_FPE_CTRL_STS_Bits B; /* Bitfield access */
} ETH_MAC_FPE_CTRL_STS;

/* MAC Debug Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    ETH_MAC_DEBUG_Bits B; /* Bitfield access */
} ETH_MAC_DEBUG;

/* MAC Extended Configuration Register 1 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    ETH_MAC_EXT_CFG1_Bits B; /* Bitfield access */
} ETH_MAC_EXT_CFG1;

/* MAC_PRESN_TIME_NS Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MAC_PRESN_TIME_NS_Bits B; /* Bitfield access */
} ETH_MAC_PRESN_TIME_NS;

/* MAC_Presn_Time_Updt Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_PRESN_TIME_UPDT_Bits B; /* Bitfield access */
} ETH_MAC_PRESN_TIME_UPDT;

/* MAC Extended Configuration Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_MAC_EXT_CONFIGURATION_Bits B; /* Bitfield access */
} ETH_MAC_EXT_CONFIGURATION;

/* MAC Hardware Feature Register 0 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_HW_FEATURE0_Bits B; /* Bitfield access */
} ETH_MAC_HW_FEATURE0;

/* MAC Hardware Feature Register 1 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_HW_FEATURE1_Bits B; /* Bitfield access */
} ETH_MAC_HW_FEATURE1;

/* MAC Hardware Feature Register 2 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_HW_FEATURE2_Bits B; /* Bitfield access */
} ETH_MAC_HW_FEATURE2;

/* MAC Hardware Feature Register 3 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_HW_FEATURE3_Bits B; /* Bitfield access */
} ETH_MAC_HW_FEATURE3;

/* MAC Hardware Feature Register 4 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_HW_FEATURE4_Bits B; /* Bitfield access */
} ETH_MAC_HW_FEATURE4;

/* FSM Data Path Parity Interrupt Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                /* Unsigned access */
    ETH_MAC_DPP_FSM_INTERRUPT_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_DPP_FSM_INTERRUPT_STATUS;

/* MAC_FSM_CONTROL Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_FSM_CONTROL_Bits B; /* Bitfield access */
} ETH_MAC_FSM_CONTROL;

/* MAC_FSM_ACT_TIMER Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MAC_FSM_ACT_TIMER_Bits B; /* Bitfield access */
} ETH_MAC_FSM_ACT_TIMER;

/* MAC Inner VLAN Tag Inclusion or Replacement Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_INNER_VLAN_INCL_Bits B; /* Bitfield access */
} ETH_MAC_INNER_VLAN_INCL;

/* MAC Interrupt Enable Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MAC_INTERRUPT_ENABLE_Bits B; /* Bitfield access */
} ETH_MAC_INTERRUPT_ENABLE;

/* MAC Interrupt Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MAC_INTERRUPT_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_INTERRUPT_STATUS;

/* MAC LPI Control and Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_MAC_LPI_CONTROL_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_LPI_CONTROL_STATUS;

/* MAC LPI Entry Timer Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_LPI_ENTRY_TIMER_Bits B; /* Bitfield access */
} ETH_MAC_LPI_ENTRY_TIMER;

/* MAC LPI Timers Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_MAC_LPI_TIMERS_CONTROL_Bits B; /* Bitfield access */
} ETH_MAC_LPI_TIMERS_CONTROL;

/* MAC MDIO Address Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MAC_MDIO_ADDRESS_Bits B; /* Bitfield access */
} ETH_MAC_MDIO_ADDRESS;

/* MAC MDIO Data Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ETH_MAC_MDIO_DATA_Bits B; /* Bitfield access */
} ETH_MAC_MDIO_DATA;

/* GPIO Control register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MAC_GPIO_CONTROL_Bits B; /* Bitfield access */
} ETH_MAC_GPIO_CONTROL;

/* MAC_GPIO_STATUS register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_GPIO_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_GPIO_STATUS;

/* MAC_ARP_ADDRESS register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_ARP_ADDRESS_Bits B; /* Bitfield access */
} ETH_MAC_ARP_ADDRESS;

/* MAC Packet Filter Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MAC_PACKET_FILTER_Bits B; /* Bitfield access */
} ETH_MAC_PACKET_FILTER;

/* MAC PHY Interface Control and Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_MAC_PHYIF_CONTROL_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_PHYIF_CONTROL_STATUS;

/* MAC PMT Control and Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_MAC_PMT_CONTROL_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_PMT_CONTROL_STATUS;

/* MAC PPS 0 Interval Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MAC_PPS0_INTERVAL_Bits B; /* Bitfield access */
} ETH_MAC_PPS0_INTERVAL;

/* MAC PPS 0 Target Time Nanoeconds Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                    /* Unsigned access */
    ETH_MAC_PPS0_TARGET_TIME_NANOSECONDS_Bits B; /* Bitfield access */
} ETH_MAC_PPS0_TARGET_TIME_NANOSECONDS;

/* MAC PPS 0 Target Time Seconds Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                /* Unsigned access */
    ETH_MAC_PPS0_TARGET_TIME_SECONDS_Bits B; /* Bitfield access */
} ETH_MAC_PPS0_TARGET_TIME_SECONDS;

/* MAC PPS 0 Width Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    ETH_MAC_PPS0_WIDTH_Bits B; /* Bitfield access */
} ETH_MAC_PPS0_WIDTH;

/* MAC_PTO_CONTROL Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_PTO_CONTROL_Bits B; /* Bitfield access */
} ETH_MAC_PTO_CONTROL;

/* MAC_SOURCE_PORT_IDENTITY0 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_MAC_SOURCE_PORT_IDENTITY0_Bits B; /* Bitfield access */
} ETH_MAC_SOURCE_PORT_IDENTITY0;

/* MAC_SOURCE_PORT_IDENTITY1 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_MAC_SOURCE_PORT_IDENTITY1_Bits B; /* Bitfield access */
} ETH_MAC_SOURCE_PORT_IDENTITY1;

/* MAC_SOURCE_PORT_IDENTITY2 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_MAC_SOURCE_PORT_IDENTITY2_Bits B; /* Bitfield access */
} ETH_MAC_SOURCE_PORT_IDENTITY2;

/* ETH_MAC_LOG_MESSAGE_INTERVAL Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_MAC_LOG_MESSAGE_INTERVAL_Bits B; /* Bitfield access */
} ETH_MAC_LOG_MESSAGE_INTERVAL;

/* MAC PPS Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_PPS_CONTROL_Bits B; /* Bitfield access */
} ETH_MAC_PPS_CONTROL;

/* MAC Queue 0 TX Flow Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_Q0_TX_FLOW_CTRL_Bits B; /* Bitfield access */
} ETH_MAC_Q0_TX_FLOW_CTRL;

/* MAC Queue 1/2/3 TX Flow Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_Q0_TX_FLOW_CTRL_Bits B; /* Bitfield access */
} ETH_MAC_Q1_TX_FLOW_CTRL;

/* MAC Wake-up Packet Filter Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_MAC_RWK_PACKET_FILTER_Bits B; /* Bitfield access */
} ETH_MAC_RWK_PACKET_FILTER;

/* MAC Receive Queue Control 0 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ETH_MAC_RXQ_CTRL0_Bits B; /* Bitfield access */
} ETH_MAC_RXQ_CTRL0;

/* MAC Receive Queue Control 1 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ETH_MAC_RXQ_CTRL1_Bits B; /* Bitfield access */
} ETH_MAC_RXQ_CTRL1;

/* MAC Receive Queue Control 2 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ETH_MAC_RXQ_CTRL2_Bits B; /* Bitfield access */
} ETH_MAC_RXQ_CTRL2;

/* MAC Receive Queue Control 4 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ETH_MAC_RXQ_CTRL4_Bits B; /* Bitfield access */
} ETH_MAC_RXQ_CTRL4;

/* the priority values assigned to Tx Queue 0 through Tx Queue 3 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MAC_TXQ_PRTY_MAP0_Bits B; /* Bitfield access */
} ETH_MAC_TXQ_PRTY_MAP0;

/* MAC Receive Flow Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MAC_RX_FLOW_CTRL_Bits B; /* Bitfield access */
} ETH_MAC_RX_FLOW_CTRL;

/* MAC Receive Transmit Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MAC_RX_TX_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_RX_TX_STATUS;

/* interrupts generated from all FPE related Transmit statistics counters  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MMC_FPE_TX_INTERRUPT_Bits B; /* Bitfield access */
} ETH_MMC_FPE_TX_INTERRUPT;

/* MMC_FPE_TX_INTERRUPT_MASK Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_MMC_FPE_TX_INTERRUPT_MASK_Bits B; /* Bitfield access */
} ETH_MMC_FPE_TX_INTERRUPT_MASK;

/* MMC_TX_FPE_FRAGMENT_CNTR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_MMC_TX_FPE_FRAGMENT_CNTR_Bits B; /* Bitfield access */
} ETH_MMC_TX_FPE_FRAGMENT_CNTR;

/* MMC_TX_HOLD_REQ_CNTR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MMC_TX_HOLD_REQ_CNTR_Bits B; /* Bitfield access */
} ETH_MMC_TX_HOLD_REQ_CNTR;

/* MMC_FPE_RX_INTERRUPT Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MMC_FPE_RX_INTERRUPT_Bits B; /* Bitfield access */
} ETH_MMC_FPE_RX_INTERRUPT;

/* MMC_FPE_RX_INTERRUPT_MASK Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_MMC_FPE_RX_INTERRUPT_MASK_Bits B; /* Bitfield access */
} ETH_MMC_FPE_RX_INTERRUPT_MASK;

/* MMC_RX_PACKET_ASSEMBLY_ERR_CNTR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                   /* Unsigned access */
    ETH_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR_Bits B; /* Bitfield access */
} ETH_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR;

/* MMC_RX_PACKET_SMD_ERR_CNTR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_MMC_RX_PACKET_SMD_ERR_CNTR_Bits B; /* Bitfield access */
} ETH_MMC_RX_PACKET_SMD_ERR_CNTR;

/* MMC_RX_PACKET_ASSEMBLY_OK_CNTR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                  /* Unsigned access */
    ETH_MMC_RX_PACKET_ASSEMBLY_OK_CNTR_Bits B; /* Bitfield access */
} ETH_MMC_RX_PACKET_ASSEMBLY_OK_CNTR;

/* MMC_RX_FPE_FRAGMENT_CNTR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_MMC_RX_FPE_FRAGMENT_CNTR_Bits B; /* Bitfield access */
} ETH_MMC_RX_FPE_FRAGMENT_CNTR;

/* MAC_Indir_Access_Ctrl Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_MAC_INDIR_ACCESS_CTRL_Bits B; /* Bitfield access */
} ETH_MAC_INDIR_ACCESS_CTRL;

/* MAC_Indir_Access_DATA Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_MAC_INDIR_ACCESS_DATA_Bits B; /* Bitfield access */
} ETH_MAC_INDIR_ACCESS_DATA;

/* MAC_PCTH_INTR_ENABLE Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MAC_PCTH_INTR_ENABLE_Bits B; /* Bitfield access */
} ETH_MAC_PCTH_INTR_ENABLE;

/* MAC_PCTH_INTR_STATUS Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MAC_PCTH_INTR_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_PCTH_INTR_STATUS;

/* MAC_PCTW_INTR_ENABLE Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MAC_PCTW_INTR_ENABLE_Bits B; /* Bitfield access */
} ETH_MAC_PCTW_INTR_ENABLE;

/* MAC_PCTH_INTR_STATUS Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MAC_PCTW_INTR_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_PCTW_INTR_STATUS;

/* MAC Sub-Second Increment Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_MAC_SUB_SECOND_INCREMENT_Bits B; /* Bitfield access */
} ETH_MAC_SUB_SECOND_INCREMENT;

/* MAC System Time Higher Word Seconds Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                       /* Unsigned access */
    ETH_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS_Bits B; /* Bitfield access */
} ETH_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS;

/* MAC System Time Nanoseconds Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                               /* Unsigned access */
    ETH_MAC_SYSTEM_TIME_NANOSECONDS_Bits B; /* Bitfield access */
} ETH_MAC_SYSTEM_TIME_NANOSECONDS;

/* MAC System Time Nanoseconds Update Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                      /* Unsigned access */
    ETH_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE_Bits B; /* Bitfield access */
} ETH_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE;

/* MAC System Time Seconds Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_MAC_SYSTEM_TIME_SECONDS_Bits B; /* Bitfield access */
} ETH_MAC_SYSTEM_TIME_SECONDS;

/* MAC System Time Seconds Update Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                  /* Unsigned access */
    ETH_MAC_SYSTEM_TIME_SECONDS_UPDATE_Bits B; /* Bitfield access */
} ETH_MAC_SYSTEM_TIME_SECONDS_UPDATE;

/* MAC Timestamp Addend Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MAC_TIMESTAMP_ADDEND_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_ADDEND;

/* MAC Timestamp Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_MAC_TIMESTAMP_CONTROL_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_CONTROL;

/* MAC Timestamp Egress Asymmetry Correction Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                  /* Unsigned access */
    ETH_MAC_TIMESTAMP_EGRESS_ASYM_CORR_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_EGRESS_ASYM_CORR;

/* MAC Timestamp Egress Correction Nanoseconds Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                        /* Unsigned access */
    ETH_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND;

/* MAC Timestamp Egress Correction Subnanoseconds Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                        /* Unsigned access */
    ETH_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC;

/* MAC Timestamp Ingress Asymmetry Correction Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                   /* Unsigned access */
    ETH_MAC_TIMESTAMP_INGRESS_ASYM_CORR_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_INGRESS_ASYM_CORR;

/* MAC Timestamp Ingress Correction Nanoseconds Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                         /* Unsigned access */
    ETH_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND;

/* MAC Timestamp Ingress Correction Subnanoseconds Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                         /* Unsigned access */
    ETH_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC;

/* MAC Timestamp Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MAC_TIMESTAMP_STATUS_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_STATUS;

/* MAC_RX_DOMAIN_TIME_INCR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_MAC_RX_DOMAIN_TIME_INCR_Bits B; /* Bitfield access */
} ETH_MAC_RX_DOMAIN_TIME_INCR;

/* MAC_TX_DOMAIN_TIME_INCR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_MAC_TX_DOMAIN_TIME_INCR_Bits B; /* Bitfield access */
} ETH_MAC_TX_DOMAIN_TIME_INCR;

/* MAC Transmit Timestamp Nanoseconds Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                       /* Unsigned access */
    ETH_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS_Bits B; /* Bitfield access */
} ETH_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS;

/* MAC Transmit Timestamp Seconds Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                   /* Unsigned access */
    ETH_MAC_TX_TIMESTAMP_STATUS_SECONDS_Bits B; /* Bitfield access */
} ETH_MAC_TX_TIMESTAMP_STATUS_SECONDS;

/* Ingress MAC latency */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                 /* Unsigned access */
    ETH_MAC_TIMESTAMP_INGRESS_LATENCY_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_INGRESS_LATENCY;

/* Egress MAC latency  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                /* Unsigned access */
    ETH_MAC_TIMESTAMP_EGRESS_LATENCY_Bits B; /* Bitfield access */
} ETH_MAC_TIMESTAMP_EGRESS_LATENCY;

/* MAC Version Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    ETH_MAC_VERSION_Bits B; /* Bitfield access */
} ETH_MAC_VERSION;

/* MAC VLAN Hash Table Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_VLAN_HASH_TABLE_Bits B; /* Bitfield access */
} ETH_MAC_VLAN_HASH_TABLE;

/* MAC VLAN Tag Inclusion or Replacement Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ETH_MAC_VLAN_INCL_Bits B; /* Bitfield access */
} ETH_MAC_VLAN_INCL;

/* MAC VLAN Tag Inclusion or Replacement Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MAC_VLAN_INCL_Q_Bits B; /* Bitfield access */
} ETH_MAC_VLAN_INCL_Q;

/* The VLAN Tag register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    ETH_MAC_VLAN_TAG_Bits B; /* Bitfield access */
} ETH_MAC_VLAN_TAG;

/* MAC VLAN Tag Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MAC_VLAN_TAG_CTRL_Bits B; /* Bitfield access */
} ETH_MAC_VLAN_TAG_CTRL;

/* MAC VLAN Tag Data Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MAC_VLAN_TAG_DATA_Bits B; /* Bitfield access */
} ETH_MAC_VLAN_TAG_DATA;

/* MAC VLAN Tag Filter Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_VLAN_TAG_FILTER_Bits B; /* Bitfield access */
} ETH_MAC_VLAN_TAG_FILTER;

/* MAC Watchdog Timeout Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MAC_WATCHDOG_TIMEOUT_Bits B; /* Bitfield access */
} ETH_MAC_WATCHDOG_TIMEOUT;

/* The Hash Table Register 0 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_HASH_Table_Reg0_Bits B; /* Bitfield access */
} ETH_MAC_HASH_Table_Reg0;

/* The Hash Table Register 1 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_HASH_Table_Reg1_Bits B; /* Bitfield access */
} ETH_MAC_HASH_Table_Reg1;

/* The Hash Table Register 2 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_HASH_Table_Reg2_Bits B; /* Bitfield access */
} ETH_MAC_HASH_Table_Reg2;

/* The Hash Table Register 3 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_HASH_Table_Reg3_Bits B; /* Bitfield access */
} ETH_MAC_HASH_Table_Reg3;

/* The Hash Table Register 4 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_HASH_Table_Reg4_Bits B; /* Bitfield access */
} ETH_MAC_HASH_Table_Reg4;

/* The Hash Table Register 5 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_HASH_Table_Reg5_Bits B; /* Bitfield access */
} ETH_MAC_HASH_Table_Reg5;

/* The Hash Table Register 6*/
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_HASH_Table_Reg6_Bits B; /* Bitfield access */
} ETH_MAC_HASH_Table_Reg6;

/* The Hash Table Register 7 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MAC_HASH_Table_Reg7_Bits B; /* Bitfield access */
} ETH_MAC_HASH_Table_Reg7;

/* MMC Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    ETH_MMC_CONTROL_Bits B; /* Bitfield access */
} ETH_MMC_CONTROL;

/* MMC IPC Receive Interrupts Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MMC_IPC_RX_INTERRUPT_Bits B; /* Bitfield access */
} ETH_MMC_IPC_RX_INTERRUPT;

/* MMC IPC Receive Interrupts Mask Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_MMC_IPC_RX_INTERRUPT_MASK_Bits B; /* Bitfield access */
} ETH_MMC_IPC_RX_INTERRUPT_MASK;

/* MMC Receive Interrupts Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MMC_RX_INTERRUPT_Bits B; /* Bitfield access */
} ETH_MMC_RX_INTERRUPT;

/* MMC Receive Interrupts Mask Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_MMC_RX_INTERRUPT_MASK_Bits B; /* Bitfield access */
} ETH_MMC_RX_INTERRUPT_MASK;

/* MMC Transmit Interrupts Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MMC_TX_INTERRUPT_Bits B; /* Bitfield access */
} ETH_MMC_TX_INTERRUPT;

/* MMC Transmit Interrupts Mask Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_MMC_TX_INTERRUPT_MASK_Bits B; /* Bitfield access */
} ETH_MMC_TX_INTERRUPT_MASK;

/* MTL Interrupt Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MTL_INTERRUPT_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_INTERRUPT_STATUS;

/* MTL Operation Mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_MTL_OPERATION_MODE_Bits B; /* Bitfield access */
} ETH_MTL_OPERATION_MODE;

/* FIFO debug Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    ETH_MTL_DBG_CTL_Bits B; /* Bitfield access */
} ETH_MTL_DBG_CTL;

/* MTL Operation Mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    ETH_MTL_DBG_STS_Bits B; /* Bitfield access */
} ETH_MTL_DBG_STS;

/* MTL Operation Mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MTL_FIFO_DEBUG_DATA_Bits B; /* Bitfield access */
} ETH_MTL_FIFO_DEBUG_DATA;

/* MTL Queue 0 Interrupt Control Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                   /* Unsigned access */
    ETH_MTL_Q0_INTERRUPT_CONTROL_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_Q0_INTERRUPT_CONTROL_STATUS;

/* MTL Queue Interrupt Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                  /* Unsigned access */
    ETH_MTL_Q_INTERRUPT_CONTROL_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_Q_INTERRUPT_CONTROL_STATUS;

/* MTL Queue 0 Receive Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MTL_RXQ0_CONTROL_Bits B; /* Bitfield access */
} ETH_MTL_RXQ0_CONTROL;

/* MTL Queue 0 Receive Debug Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    ETH_MTL_RXQ0_DEBUG_Bits B; /* Bitfield access */
} ETH_MTL_RXQ0_DEBUG;

/* MTL Queue 0 Receive Missed Packet and Overflow Counter Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                       /* Unsigned access */
    ETH_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT_Bits B; /* Bitfield access */
} ETH_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT;

/* MTL Queue 0 Receive Operation Mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_MTL_RXQ0_OPERATION_MODE_Bits B; /* Bitfield access */
} ETH_MTL_RXQ0_OPERATION_MODE;

/* MTL Queue Receive Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MTL_RXQ_CONTROL_Bits B; /* Bitfield access */
} ETH_MTL_RXQ_CONTROL;

/* MTL Queue Receive Debug Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ETH_MTL_RXQ_DEBUG_Bits B; /* Bitfield access */
} ETH_MTL_RXQ_DEBUG;

/* MTL Receive Queue and DMA Channel Mapping 0 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MTL_RXQ_DMA_MAP0_Bits B; /* Bitfield access */
} ETH_MTL_RXQ_DMA_MAP0;

/* MTL control the operation of time based scheduling Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    ETH_MTL_TBS_CTRL_Bits B; /* Bitfield access */
} ETH_MTL_TBS_CTRL;

/* MTL EST control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MTL_EST_CONTROL_Bits B; /* Bitfield access */
} ETH_MTL_EST_CONTROL;

/* MTL_EST_EXT_CONTROL Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MTL_EST_EXT_CONTROL_Bits B; /* Bitfield access */
} ETH_MTL_EST_EXT_CONTROL;

/* ETH_MTL_EST_STATUS Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    ETH_MTL_EST_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_EST_STATUS;

/* ETH_MTL_EST_SCH_ERROR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MTL_EST_SCH_ERROR_Bits B; /* Bitfield access */
} ETH_MTL_EST_SCH_ERROR;

/* ETH_MTL_EST_FRM_SIZE_ERROR Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_MTL_EST_FRM_SIZE_ERROR_Bits B; /* Bitfield access */
} ETH_MTL_EST_FRM_SIZE_ERROR;

/* ETH_MTL_EST_FRM_SIZE_CAPTURE Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_MTL_EST_FRM_SIZE_CAPTURE_Bits B; /* Bitfield access */
} ETH_MTL_EST_FRM_SIZE_CAPTURE;

/* ETH_MTL_EST_INTR_ENABLE Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MTL_EST_INTR_ENABLE_Bits B; /* Bitfield access */
} ETH_MTL_EST_INTR_ENABLE;

/* ETH_MTL_EST_GCL_CONTROL Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MTL_EST_GCL_CONTROL_Bits B; /* Bitfield access */
} ETH_MTL_EST_GCL_CONTROL;

/* ETH_MTL_EST_GCL_DATA Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MTL_EST_GCL_DATA_Bits B; /* Bitfield access */
} ETH_MTL_EST_GCL_DATA;

/* ETH_MTL_FPE_CTRL_STS Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MTL_FPE_CTRL_STS_Bits B; /* Bitfield access */
} ETH_MTL_FPE_CTRL_STS;

/* ETH_MTL_FPE_ADVANCE Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MTL_FPE_ADVANCE_Bits B; /* Bitfield access */
} ETH_MTL_FPE_ADVANCE;

/* ETH_MTL_RXP_CONTROL_STATUS Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_MTL_RXP_CONTROL_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_RXP_CONTROL_STATUS;

/* ETH_MTL_RXP_INTERRUPT_CONTROL_STATUS Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                    /* Unsigned access */
    ETH_MTL_RXP_INTERRUPT_CONTROL_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_RXP_INTERRUPT_CONTROL_STATUS;

/* ETH_MTL_RXP_DROP_CNT Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MTL_RXP_DROP_CNT_Bits B; /* Bitfield access */
} ETH_MTL_RXP_DROP_CNT;

/* ETH_MTL_RXP_ERROR_CNT Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MTL_RXP_ERROR_CNT_Bits B; /* Bitfield access */
} ETH_MTL_RXP_ERROR_CNT;

/* ETH_MTL_INDIRECT_ACC_CONTROL_STATUS Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                       /* Unsigned access */
    ETH_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS;

/* ETH_MTL_INDIRECT_ACC_DATA Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_MTL_RXP_INDIRECT_ACC_DATA_Bits B; /* Bitfield access */
} ETH_MTL_RXP_INDIRECT_ACC_DATA;

/* ETH_MTL_BYPASS_CNT Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_MTL_RXP_BYPASS_CNT_Bits B; /* Bitfield access */
} ETH_MTL_RXP_BYPASS_CNT;

/* MTL ECC operating mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    ETH_MTL_ECC_CTL_Bits B; /* Bitfield access */
} ETH_MTL_ECC_CTL;

/* MTL ECC Safety interrupt status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                               /* Unsigned access */
    ETH_MTL_SAFETY_INTERRUPT_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_SAFTEY_INTERRUPR_STATUS;

/* MTL ECC interrupts enable Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_MTL_ECC_INTERRUPT_ENABLE_Bits B; /* Bitfield access */
} ETH_MTL_ECC_INTERRUPT_ENABLE;

/* MTL ECC interrupts Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_MTL_ECC_INTERRUPT_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_ECC_INTERRUPT_STATUS;

/* MTL ECC error status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_MTL_ECC_ERR_STS_RCTL_Bits B; /* Bitfield access */
} ETH_MTL_ECC_ERR_STS_RCTL;

/* MTL ECC memory addresses for the correctable and uncorrectable Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_MTL_ECC_ERR_ADDR_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_ECC_ERR_ADDR_STATUS;

/* MTL ECC Error count for Correctable and uncorrectable Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_MTL_ECC_ERR_CNTR_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_ECC_ERR_CNTR_STATUS;

/* MTL DPP control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MTL_DPP_CONTROL_Bits B; /* Bitfield access */
} ETH_MTL_DPP_CONTROL;

/* ETH_MTL_DPP_ECC_EIC Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    ETH_MTL_DPP_ECC_EIC_Bits B; /* Bitfield access */
} ETH_MTL_DPP_ECC_EIC;

/* MTL Queue Receive Missed Packet and Overflow Counter Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                      /* Unsigned access */
    ETH_MTL_RXQ_MISSED_PACKET_OVERFLOW_CNT_Bits B; /* Bitfield access */
} ETH_MTL_RXQ_MISSED_PACKET_OVERFLOW_CNT;

/* MTL Queue Receive Operation Mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_MTL_RXQ_OPERATION_MODE_Bits B; /* Bitfield access */
} ETH_MTL_RXQ_OPERATION_MODE;

/* MTL Queue 0 Transmit Debug Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    ETH_MTL_TXQ0_DEBUG_Bits B; /* Bitfield access */
} ETH_MTL_TXQ0_DEBUG;

/* MTL Queue 0 Transmit Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MTL_TXQ0_ETS_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_TXQ0_ETS_STATUS;

/* MTL Queue 0 Transmit Operation Mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_MTL_TXQ0_OPERATION_MODE_Bits B; /* Bitfield access */
} ETH_MTL_TXQ0_OPERATION_MODE;

/* MTL Queue 0 Transmit Quantum or Weights Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_MTL_TXQ0_QUANTUM_WEIGHT_Bits B; /* Bitfield access */
} ETH_MTL_TXQ0_QUANTUM_WEIGHT;

/* MTL Queue 0 Transmit Underflow Counter Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_MTL_TXQ0_UNDERFLOW_Bits B; /* Bitfield access */
} ETH_MTL_TXQ0_UNDERFLOW;

/* MTL Queue Transmit Debug Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    ETH_MTL_TXQ_DEBUG_Bits B; /* Bitfield access */
} ETH_MTL_TXQ_DEBUG;

/* MTL Queue Transmit ETS Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_MTL_TXQ_ETS_CONTROL_Bits B; /* Bitfield access */
} ETH_MTL_TXQ_ETS_CONTROL;

/* MTL Queue Transmit ETS Status Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_MTL_TXQ_ETS_STATUS_Bits B; /* Bitfield access */
} ETH_MTL_TXQ_ETS_STATUS;

/* MTL Queue Transmit HiCredit Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MTL_TXQ_HICREDIT_Bits B; /* Bitfield access */
} ETH_MTL_TXQ_HICREDIT;

/* MTL Queue Transmit LoCredit Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_MTL_TXQ_LOCREDIT_Bits B; /* Bitfield access */
} ETH_MTL_TXQ_LOCREDIT;

/* MTL Queue Transmit Operation Mode Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_MTL_TXQ_OPERATION_MODE_Bits B; /* Bitfield access */
} ETH_MTL_TXQ_OPERATION_MODE;

/* MTL Queue Transmit Quantum or Weights Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    ETH_MTL_TXQ_QUANTUM_WEIGHT_Bits B; /* Bitfield access */
} ETH_MTL_TXQ_QUANTUM_WEIGHT;

/* MTL Queue Transmit SendSlopeCredit Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_MTL_TXQ_SENDSLOPECREDIT_Bits B; /* Bitfield access */
} ETH_MTL_TXQ_SENDSLOPECREDIT;

/* MTL Queue Transmit Underflow Counter Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_MTL_TXQ_UNDERFLOW_Bits B; /* Bitfield access */
} ETH_MTL_TXQ_UNDERFLOW;

/* MAC Wake-up Filter Byte Mask register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_RWK_FILTER_BYTE_MASK_Bits B; /* Bitfield access */
} ETH_RWK_FILTER_BYTE_MASK;

/* MAC Wake-up Filter Command 0 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_RWK_FILTER_COMMAND_0_Bits B; /* Bitfield access */
} ETH_RWK_FILTER_COMMAND_0;

/* MAC Wake-up Filter CRC Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    ETH_RWK_FILTER_CRC_Bits B; /* Bitfield access */
} ETH_RWK_FILTER_CRC;

/* MAC Wake-up Filter Offset 0 Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_RWK_FILTER_OFFSET_0_Bits B; /* Bitfield access */
} ETH_RWK_FILTER_OFFSET_0;

/* Received ICMP Error Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_RXICMP_ERROR_OCTETS_Bits B; /* Bitfield access */
} ETH_RXICMP_ERROR_OCTETS;

/* Received ICMP Error Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_RXICMP_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RXICMP_ERROR_PACKETS;

/* Good Received ICMP Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_RXICMP_GOOD_OCTETS_Bits B; /* Bitfield access */
} ETH_RXICMP_GOOD_OCTETS;

/* Good Received ICMP Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_RXICMP_GOOD_PACKETS_Bits B; /* Bitfield access */
} ETH_RXICMP_GOOD_PACKETS;

/* Received IPV4 Fragmented Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_RXIPV4_FRAGMENTED_OCTETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_FRAGMENTED_OCTETS;

/* Received IPv4 Fragmented Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_RXIPV4_FRAGMENTED_PACKETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_FRAGMENTED_PACKETS;

/* Good Received IPV4 Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_RXIPV4_GOOD_OCTETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_GOOD_OCTETS;

/* Good Received RxIPv4 Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_RXIPV4_GOOD_PACKETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_GOOD_PACKETS;

/* Received IPV4 Header Error Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_RXIPV4_HEADER_ERROR_OCTETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_HEADER_ERROR_OCTETS;

/* Received IPv4 Header Error Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                               /* Unsigned access */
    ETH_RXIPV4_HEADER_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_HEADER_ERROR_PACKETS;

/* Received IPV4 No Payload Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_RXIPV4_NO_PAYLOAD_OCTETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_NO_PAYLOAD_OCTETS;

/* Received IPv4 No Payload Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_RXIPV4_NO_PAYLOAD_PACKETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_NO_PAYLOAD_PACKETS;

/* Received IPv4 UPD Checksum Disabled Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                        /* Unsigned access */
    ETH_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS;

/* Received IPV4 UPD Checksum Disabled Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                      /* Unsigned access */
    ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS_Bits B; /* Bitfield access */
} ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS;

/* Good Received IPV6 Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_RXIPV6_GOOD_OCTETS_Bits B; /* Bitfield access */
} ETH_RXIPV6_GOOD_OCTETS;

/* Good Received RxIPv6 Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_RXIPV6_GOOD_PACKETS_Bits B; /* Bitfield access */
} ETH_RXIPV6_GOOD_PACKETS;

/* Received IPV6 Header Error Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_RXIPV6_HEADER_ERROR_OCTETS_Bits B; /* Bitfield access */
} ETH_RXIPV6_HEADER_ERROR_OCTETS;

/* Received IPv6 Header Error Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                               /* Unsigned access */
    ETH_RXIPV6_HEADER_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RXIPV6_HEADER_ERROR_PACKETS;

/* Received IPV6 No Payload Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_RXIPV6_NO_PAYLOAD_OCTETS_Bits B; /* Bitfield access */
} ETH_RXIPV6_NO_PAYLOAD_OCTETS;

/* Received IPv6 No Payload Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_RXIPV6_NO_PAYLOAD_PACKETS_Bits B; /* Bitfield access */
} ETH_RXIPV6_NO_PAYLOAD_PACKETS;

/* Received TCP Error Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_RXTCP_ERROR_OCTETS_Bits B; /* Bitfield access */
} ETH_RXTCP_ERROR_OCTETS;

/* Received TCP Error Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_RXTCP_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RXTCP_ERROR_PACKETS;

/* Good Received TCP Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_RXTCP_GOOD_OCTETS_Bits B; /* Bitfield access */
} ETH_RXTCP_GOOD_OCTETS;

/* Good Received TCP Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_RXTCP_GOOD_PACKETS_Bits B; /* Bitfield access */
} ETH_RXTCP_GOOD_PACKETS;

/* Received UDP Error Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_RXUDP_ERROR_OCTETS_Bits B; /* Bitfield access */
} ETH_RXUDP_ERROR_OCTETS;

/* Received UDP Error Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_RXUDP_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RXUDP_ERROR_PACKETS;

/* Good Received UDP Octets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    ETH_RXUDP_GOOD_OCTETS_Bits B; /* Bitfield access */
} ETH_RXUDP_GOOD_OCTETS;

/* Good Received UDP Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    ETH_RXUDP_GOOD_PACKETS_Bits B; /* Bitfield access */
} ETH_RXUDP_GOOD_PACKETS;

/* Good And Bad 1024toMax Octets Packets Received Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                       /* Unsigned access */
    ETH_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 128to255 Octets Packets Received Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                      /* Unsigned access */
    ETH_RX_128TO255OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_RX_128TO255OCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 256to511 Octets Packets Received Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                      /* Unsigned access */
    ETH_RX_256TO511OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_RX_256TO511OCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 512to1023 Octets Packets Received Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                       /* Unsigned access */
    ETH_RX_512TO1023OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_RX_512TO1023OCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 64 Octets Packets Received Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                /* Unsigned access */
    ETH_RX_64OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_RX_64OCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 65to127 Octets Packets Received Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                     /* Unsigned access */
    ETH_RX_65TO127OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_RX_65TO127OCTETS_PACKETS_GOOD_BAD;

/* Received Alignment Error Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_RX_ALIGNMENT_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_ALIGNMENT_ERROR_PACKETS;

/* Good Received Broadcast Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_RX_BROADCAST_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_RX_BROADCAST_PACKETS_GOOD;

/* Good Received Control Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_RX_CONTROL_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_RX_CONTROL_PACKETS_GOOD;

/* Received CRC Error Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_RX_CRC_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_CRC_ERROR_PACKETS;

/* Received FIFO Overflow Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_RX_FIFO_OVERFLOW_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_FIFO_OVERFLOW_PACKETS;

/* Received Jabber Error Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_RX_JABBER_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_JABBER_ERROR_PACKETS;

/* Received Length Error Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_RX_LENGTH_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_LENGTH_ERROR_PACKETS;

/* Received LPI Transition Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_RX_LPI_TRAN_CNTR_Bits B; /* Bitfield access */
} ETH_RX_LPI_TRAN_CNTR;

/* Received Microseconds LPI Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_RX_LPI_USEC_CNTR_Bits B; /* Bitfield access */
} ETH_RX_LPI_USEC_CNTR;

/* Good Received Multicast Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_RX_MULTICAST_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_RX_MULTICAST_PACKETS_GOOD;

/* Good Received Octet Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_RX_OCTET_COUNT_GOOD_Bits B; /* Bitfield access */
} ETH_RX_OCTET_COUNT_GOOD;

/* Good And Bad Received Octet Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_RX_OCTET_COUNT_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_RX_OCTET_COUNT_GOOD_BAD;

/* Received Out Of Range Type Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                /* Unsigned access */
    ETH_RX_OUT_OF_RANGE_TYPE_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_OUT_OF_RANGE_TYPE_PACKETS;

/* Good Received Oversized Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_RX_OVERSIZE_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_RX_OVERSIZE_PACKETS_GOOD;

/* Good And Bad Received Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_RX_PACKETS_COUNT_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_RX_PACKETS_COUNT_GOOD_BAD;

/* Received Pause Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_RX_PAUSE_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_PAUSE_PACKETS;

/* Received Receive Error Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_RX_RECEIVE_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_RECEIVE_ERROR_PACKETS;

/* Received Runtime Error Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_RX_RUNT_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_RUNT_ERROR_PACKETS;

/* Good Received Undersized Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_RX_UNDERSIZE_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_RX_UNDERSIZE_PACKETS_GOOD;

/* Good Received Unicat Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_RX_UNICAST_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_RX_UNICAST_PACKETS_GOOD;

/* Good And Bad Received VLAN Packets Count Registerv */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_RX_VLAN_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_RX_VLAN_PACKETS_GOOD_BAD;

/* Received Watchdog Error Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_RX_WATCHDOG_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_RX_WATCHDOG_ERROR_PACKETS;

/* Skew Control Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ETH_SKEWCTL_Bits B; /* Bitfield access */
} ETH_SKEWCTL;

/* PHY_TXCTL Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    ETH_PHY_TXCTL_Bits B; /* Bitfield access */
} ETH_PHY_TXCTL;

/* ETH_PPS Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    ETH_PPS_REGISTER_Bits B; /* Bitfield access */
} ETH_PPS_REGISTER;

/* ETH_LPMR Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    ETH_LPMR_Bits B; /* Bitfield access */
} ETH_LPMR;

/* ETH_EAR Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    ETH_EAR_Bits B; /* Bitfield access */
} ETH_EAR;

/* ETH_EAER Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    ETH_EAER_Bits B; /* Bitfield access */
} ETH_EAER;

/* ETH_EACR Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    ETH_EACR_Bits B; /* Bitfield access */
} ETH_EACR;

/* ETH_EFSIMDR Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ETH_EFSIMDR_Bits B; /* Bitfield access */
} ETH_EFSIMDR;

/* ETH_EIR Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    ETH_EIR_Bits B; /* Bitfield access */
} ETH_EIR;

/* ETH_EIER Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    ETH_EIER_Bits B; /* Bitfield access */
} ETH_EIER;

/* ETH_EICR Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    ETH_EICR_Bits B; /* Bitfield access */
} ETH_EICR;

/* ETH_AHBEMR Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    ETH_AHBEMR_Bits B; /* Bitfield access */
} ETH_AHBEMR;

/* ETH_XCVRENR Register  */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    ETH_XCVRENR_Bits B; /* Bitfield access */
} ETH_XCVRENR;

/* Good And Bad 1024toMax Octets Packets Transmitted Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                       /* Unsigned access */
    ETH_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 128to255 Octets Packets Transmitted Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                      /* Unsigned access */
    ETH_TX_128TO255OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_128TO255OCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 256to511 Octets Packets Transmitted Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                      /* Unsigned access */
    ETH_TX_256TO511OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_256TO511OCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 512to1023 Octets Packets Transmitted Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                       /* Unsigned access */
    ETH_TX_512TO1023OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_512TO1023OCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 64 Octets Packets Transmitted Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                /* Unsigned access */
    ETH_TX_64OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_64OCTETS_PACKETS_GOOD_BAD;

/* Good And Bad 65to127 Octets Packets Transmitted Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                     /* Unsigned access */
    ETH_TX_65TO127OCTETS_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_65TO127OCTETS_PACKETS_GOOD_BAD;

/* Good Transmitted Broadcast Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_TX_BROADCAST_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_TX_BROADCAST_PACKETS_GOOD;

/* Good And Bad Transmitted Broadcast Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                 /* Unsigned access */
    ETH_TX_BROADCAST_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_BROADCAST_PACKETS_GOOD_BAD;

/* Transmitted Carrier Error Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_TX_CARRIER_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_TX_CARRIER_ERROR_PACKETS;

/* Transmitted Deferred Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_TX_DEFERRED_PACKETS_Bits B; /* Bitfield access */
} ETH_TX_DEFERRED_PACKETS;

/* Transmitted Excessive Collision Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                  /* Unsigned access */
    ETH_TX_EXCESSIVE_COLLISION_PACKETS_Bits B; /* Bitfield access */
} ETH_TX_EXCESSIVE_COLLISION_PACKETS;

/* Transmitted Excessive Deferral Error Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                               /* Unsigned access */
    ETH_TX_EXCESSIVE_DEFERRAL_ERROR_Bits B; /* Bitfield access */
} ETH_TX_EXCESSIVE_DEFERRAL_ERROR;

/* Transmitted Late Collision Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_TX_LATE_COLLISION_PACKETS_Bits B; /* Bitfield access */
} ETH_TX_LATE_COLLISION_PACKETS;

/* Transmitted LPI Transition Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_TX_LPI_TRAN_CNTR_Bits B; /* Bitfield access */
} ETH_TX_LPI_TRAN_CNTR;

/* Transmitted LPI Microseconds Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_TX_LPI_USEC_CNTR_Bits B; /* Bitfield access */
} ETH_TX_LPI_USEC_CNTR;

/* Good Transmitted Multicast Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                             /* Unsigned access */
    ETH_TX_MULTICAST_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_TX_MULTICAST_PACKETS_GOOD;

/* Good And Bad Transmitted Multicast Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                 /* Unsigned access */
    ETH_TX_MULTICAST_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_MULTICAST_PACKETS_GOOD_BAD;

/* Transmitted Multiple Collision Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                      /* Unsigned access */
    ETH_TX_MULTIPLE_COLLISION_GOOD_PACKETS_Bits B; /* Bitfield access */
} ETH_TX_MULTIPLE_COLLISION_GOOD_PACKETS;

/* Good Transmitted Octet Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    ETH_TX_OCTET_COUNT_GOOD_Bits B; /* Bitfield access */
} ETH_TX_OCTET_COUNT_GOOD;

/* Good And Bad Transmitted Octet Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    ETH_TX_OCTET_COUNT_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_OCTET_COUNT_GOOD_BAD;

/* Good Transmitted Osize Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    ETH_TX_OSIZE_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_TX_OSIZE_PACKETS_GOOD;

/* Good Transmitted Packet Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_TX_PACKET_COUNT_GOOD_Bits B; /* Bitfield access */
} ETH_TX_PACKET_COUNT_GOOD;

/* Good And Bad Transmitted Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                            /* Unsigned access */
    ETH_TX_PACKET_COUNT_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_PACKET_COUNT_GOOD_BAD;

/* Transmitted Pause Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                    /* Unsigned access */
    ETH_TX_PAUSE_PACKETS_Bits B; /* Bitfield access */
} ETH_TX_PAUSE_PACKETS;

/* Good Transmitted Single Collision Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                                    /* Unsigned access */
    ETH_TX_SINGLE_COLLISION_GOOD_PACKETS_Bits B; /* Bitfield access */
} ETH_TX_SINGLE_COLLISION_GOOD_PACKETS;

/* Transmitted Underflow Error Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                              /* Unsigned access */
    ETH_TX_UNDERFLOW_ERROR_PACKETS_Bits B; /* Bitfield access */
} ETH_TX_UNDERFLOW_ERROR_PACKETS;

/* Good Transmitted Unicat Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                               /* Unsigned access */
    ETH_TX_UNICAST_PACKETS_GOOD_BAD_Bits B; /* Bitfield access */
} ETH_TX_UNICAST_PACKETS_GOOD_BAD;

/* Good Transmitted VLAN Packets Count Register */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    ETH_TX_VLAN_PACKETS_GOOD_Bits B; /* Bitfield access */
} ETH_TX_VLAN_PACKETS_GOOD;

/**********************************************************************************************************************
 *                                        ETH Descriptors Definition
 *********************************************************************************************************************/
/* Bit Fields of RDES0 Context Descriptor */
typedef struct
{
    ureg32 RTSL:32; /* [31:0]Receive Packet Timestamp Low */
} Eth_RxContextDescr0_Bits;

/* Bit Fields of RDES1 Context Descriptor */
typedef struct
{
    ureg32 RTSH:32; /* [31:0]Receive Packet Timestamp High */
} Eth_RxContextDescr1_Bits;

/* Bit Fields of RDES2 Context Descriptor */
typedef struct
{
    ureg32 reserved_0:32; /* [31:0]Reserved */
} Eth_RxContextDescr2_Bits;

/* Bit Fields of RDES3 Context Descriptor */
typedef struct
{
    ureg32 reserved_0:29; /* [28:0]Reserved */
    ureg32 DE:1;          /* [29:29]Descriptor Error */
    ureg32 CTXT:1;        /* [30:30]Receive Context Descriptor */
    ureg32 OWN:1;         /* [31:31]Own Bit */
} Eth_RxContextDescr3_Bits;

/* Bit Fields of RDES0 in Read Format */
typedef struct
{
    ureg32 BUF1AP:32; /* [31:0]Header or Buffer 1 Address Pointer */
} Eth_RxDescr0_RF_Bits;

/* Bit Fields of RDES0 in Write back Format */
typedef struct
{
    ureg32 OVT:16; /* [15:0]Outer VLAN Tag */
    ureg32 IVT:16; /* [31:16]Inner VLAN Tag */
} Eth_RxDescr0_WF_Bits;

/* Bit Fields of RDES1 in Read Format */
typedef struct
{
    ureg32 reserved_0:32; /* [31:0]Reserved */
} Eth_RxDescr1_RF_Bits;

/* Bit Fields of RDES1 in Write back Format */
typedef struct
{
    ureg32 PT:3;   /* [2:0]Payload Type */
    ureg32 IPHE:1; /* [3:3]IP Header Error */
    ureg32 IP4:1;  /* [4:4]IPV4 Header Present */
    ureg32 IP6:1;  /* [5:5]IPv6 header Present */
    ureg32 IPCB:1; /* [6:6]IP Checksum Bypassed */
    ureg32 IPCE:1; /* [7:7]IP Payload Error */
    ureg32 PMT:4;  /* [11:8]PTP Message Type */
    ureg32 PFT:1;  /* [12:12]PTP Packet Type */
    ureg32 PV:1;   /* [13:13]PTP Version */
    ureg32 TSA:1;  /* [14:14]Timestamp Available */
    ureg32 TD:1;   /* [15:15]Timestamp Dropped */
    ureg32 OPC:16; /* [31:16]OAM Sub-Type Code, or MAC Control Packet opcode */
} Eth_RxDescr1_WF_Bits;

/* Bit Fields of RDES2 in Read Format */
typedef struct
{
    ureg32 BUF2AP:32; /* [31:0]Buffer 2 Address Pointer */
} Eth_RxDescr2_RF_Bits;

/* Bit Fields of RDES2 in Write back Format */
typedef struct
{
    ureg32 HL:10;         /* [9:0]L3/L4 Header Length */
    ureg32 ARPNR:1;       /* [10:10]ARP Reply Not Generated */
    ureg32 reserved_11:3; /* [13:11]Reserved */
    ureg32 ITS:1;         /* [14:14]Inner VLAN Tag Filter Status (ITS) */
    ureg32 OTS:1;         /* [15:15]VLAN Filter Status */
    ureg32 SAF:1;         /* [16:16]SA Address Filter Fail */
    ureg32 DAF:1;         /* [17:17]Destination Address Filter Fail */
    ureg32 HF:1;          /* [18:18]Hash Filter Status */
    ureg32 MADRM:8;       /* [26:19]MAC Address Match or Hash Value */
    ureg32 L3FM:1;        /* [27:27]Layer 3 Filter Match */
    ureg32 L4FM:1;        /* [28:28]Layer 4 Filter Match */
    ureg32 L3L4FM:3;      /* [31:29]Layer 3 and Layer 4 Filter Number Matched */
} Eth_RxDescr2_WF_Bits;

/* Bit Fields of RDES3 in Read Format */
typedef struct
{
    ureg32 reserved_0:24; /* [23:0]Reserved */
    ureg32 BUF1V:1;       /* [24:24]Buffer 1 Address Valid */
    ureg32 BUF2V:1;       /* [25:25]Buffer 2 Address Valid */
    ureg32 reserved_27:4; /* [29:26]Reserved */
    ureg32 IOC:1;         /* [30:30]Interrupt on Completion */
    ureg32 OWN:1;         /* [31:31]Own bit */
} Eth_RxDescr3_RF_Bits;

/* Bit Fields of RDES3 in Write back Format */
typedef struct
{
    ureg32 PL:15;  /* [14:0]Packet Length */
    ureg32 ERRSUM:1;   /* [15:15]Error Summary */
    ureg32 LT:3;   /* [18:16]Length/Type Field */
    ureg32 DE:1;   /* [19:19]Dribble Bit Error */
    ureg32 RE:1;   /* [20:20]Receive Error */
    ureg32 OE:1;   /* [21:21]Overflow Error */
    ureg32 RWT:1;  /* [22:22]Receive Watchdog Timeout */
    ureg32 GP:1;   /* [23:23]Giant Packet */
    ureg32 CE:1;   /* [24:24]CRC Error */
    ureg32 RS0V:1; /* [25:25]Receive Status RDES0 Valid */
    ureg32 RS1V:1; /* [26:26]Receive Status RDES1 Valid */
    ureg32 RS2V:1; /* [27:27]Receive Status RDES2 Valid */
    ureg32 LD:1;   /* [28:28]Last Descriptor */
    ureg32 FD:1;   /* [29:29]First Descriptor */
    ureg32 CTXT:1; /* [30:30]Receive Context Descriptor */
    ureg32 OWN:1;  /* [31:31]Own Bit */
} Eth_RxDescr3_WF_Bits;

/* Bit Fields of TDES0 Context Descriptor */
typedef struct
{
    ureg32 TTSL:32; /* [31:0]Transmit Packet Timestamp Low */
} Eth_TxContextDescr0_Bits;

/* Bit Fields of TDES1 Context Descriptor */
typedef struct
{
    ureg32 TTSH:32; /* [31:0]Transmit Packet Timestamp High */
} Eth_TxContextDescr1_Bits;

/* Bit Fields of TDES2 Context Descriptor */
typedef struct
{
    ureg32 MSS:14;        /* [13:0]Maximum Segment Size */
    ureg32 reserved_14:2; /* [15:14]Reserved */
    ureg32 IVT:16;        /* [31:16]Inner VLAN Tag */
} Eth_TxContextDescr2_Bits;

/* Bit Fields of TDES3 Context Descriptor */
typedef struct
{
    ureg32 VT:16;         /* [15:0]VLAN Tag */
    ureg32 VLTV:1;        /* [16:16]VLAN Tag Valid */
    ureg32 IVLTV:1;       /* [17:17]Inner VLAN Tag Valid */
    ureg32 IVTIR:2;       /* [19:18]Inner VLAN Tag Insert or Replace */
    ureg32 reserved_20:3; /* [22:20]Reserved */
    ureg32 CDE:1;         /* [23:23]Context Descriptor Error */
    ureg32 reserved_24:2; /* [25:24]Reserved */
    ureg32 TCMSSV:1;      /* [26:26]One-Step Timestamp Correction Input or MSS Valid */
    ureg32 OSTC:1;        /* [27:27]One-Step Timestamp Correction Enable */
    ureg32 reserved_28:2; /* [29:28]Reserved */
    ureg32 CTXT:1;        /* [30:30]Context Type */
    ureg32 OWN:1;         /* [31:31]Own Bit */
} Eth_TxContextDescr3_Bits;

/* Bit Fields of TDES0 in Read Format */
typedef struct
{
    ureg32 BUF1AP:32; /* [31:0]Buffer 1 Address Pointer */
} Eth_TxDescr0_RF_Bits;

/* Bit Fields of TDES0 in Write-back Format */
typedef struct
{
    ureg32 TTSL:32; /* [31:0]Transmit Packet Timestamp Low */
} Eth_TxDescr0_WF_Bits;

/* Bit Fields of TDES1 in Read Format */
typedef struct
{
    ureg32 BUF2AP:32; /* [31:0]Buffer 2 or Buffer 1 Address Pointer */
} Eth_TxDescr1_RF_Bits;

/* Bit Fields of TDES1 in Write-back Format */
typedef struct
{
    ureg32 TTSH:32; /* [31:0]Transmit Packet Timestamp High */
} Eth_TxDescr1_WF_Bits;

/* Bit Fields of TDES2 in Read Format */
typedef struct
{
    ureg32 B1L:14;      /* [13:0]Header Length or Buffer 1 Length */
    ureg32 VTIR:2;      /* [15:14]VLAN Tag Insertion or Replacement */
    ureg32 B2L:14;      /* [29:16]Buffer 2 Length */
    ureg32 TTSE_TMWD:1; /* [30:30]Transmit Timestamp Enable or External TSO Memory Write Enable */
    ureg32 IOC:1;       /* [31:31]Interrupt on Completion */
} Eth_TxDescr2_RF_Bits;

/* Bit Fields of TDES2 in Write-back Format */
typedef struct
{
    ureg32 reserved_0:32; /* [31:0]Reserved */
} Eth_TxDescr2_WF_Bits;

/* Bit Fields of TDES3 in Read Format
 */
typedef struct
{
    ureg32 FL_TPL:15; /* [14:0]Packet Length or TCP Payload Length */
    ureg32 TPL:1;     /* [15:15]Reserved or TCP Payload Length */
    ureg32 CIC_TPL:2; /* [17:16]Checksum Insertion Control or TCP Payload LengthThese bits control the checksum, 11=ip
                         header checksum & payload checksum insert */
    ureg32 TSE:1;     /* [18:18]TCP Segmentation Enable */
    ureg32 SLOTNUM_THL:4; /* [22:19]SLOTNUM: Slot Number Control Bits in AV Mode */
    ureg32 SAIC:3;        /* [25:23]SA Insertion Control, 00 do not insert*/
    ureg32 CPC:2;         /* [27:26]CRC Pad Control ,00 crc&pad insertion, at least 60bytes*/
    ureg32 LD:1;          /* [28:28]Last Descriptor */
    ureg32 FD:1;          /* [29:29]First Descriptor */
    ureg32 CTXT:1;        /* [30:30]Context Type This bit should be set to 1'b0 for normal descriptor */
    ureg32 OWN:1;         /* [31:31] Own Bit , 0 = application*/
} Eth_TxDescr3_RF_Bits;

/* Bit Fields of TDES3 in Write-back Format
 */
typedef struct
{
    ureg32 IHE:1;          /* [0:0]bit0,IP Header Error */
    ureg32 DB:1;           /* [1:1]bit1,Deferred Bit */
    ureg32 UF:1;           /* [2:2]bit2,Underflow Error */
    ureg32 ED:1;           /* [3:3]bit3,Excessive Deferral */
    ureg32 CC:4;           /* [7:4]bit4-bit7,Collision Count */
    ureg32 EC:1;           /* [8:8]bit8,Excessive Collision */
    ureg32 LC:1;           /* [9:9]bit9,Late Collision */
    ureg32 NC:1;           /* [10:10]bit10,No Carrier */
    ureg32 LOC:1;          /* [11:11]bit11,Loss of Carrier */
    ureg32 PCE:1;          /* [12:12]bit12,Payload Checksum */
    ureg32 FF:1;           /* [13:13]bit13,Packet Flushed */
    ureg32 JT:1;           /* [14:14]bit14,Jabber Timeout */
    ureg32 ERRSUM:1;       /* [15:15]bit15,Error Summary */
    ureg32 EUE:1;          /* [16:16]bit16, ECC uncorrectable error in the TSO memory */
    ureg32 TTSS:1;         /* [17:17]bit17,Tx Timestamp Status */
    ureg32 reserved_18:10; /* [27:18]bit18-27,Reserved */
    ureg32 LD:1;           /* [28:28]bit28,Last Descriptor */
    ureg32 FD:1;           /* [29:29]bit29,First Descriptor */
    ureg32 CTXT:1;         /* [30:30]bit30,Context Type */
    ureg32 OWN:1;          /* [31:31]bit31,Own bit */
} Eth_TxDescr3_WF_Bits;

/* RDES0 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    Eth_RxDescr0_RF_Bits R;     /* Read Format Bitfiled Access */
    Eth_RxDescr0_WF_Bits W;     /* Write back Format Bitfiled Access */
    Eth_RxContextDescr0_Bits C; /* Context Descriptor Format Bitfiled Access */
    uint32 U;                   /* Unsigned access */
} Eth_RxDescr0;

/* RDES1 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    Eth_RxDescr1_RF_Bits R;     /* Read Format Bitfiled Access */
    Eth_RxDescr1_WF_Bits W;     /* Write back Format Bitfiled Access */
    Eth_RxContextDescr1_Bits C; /* Context Descriptor Format Bitfiled Access */
    uint32 U;                   /* Unsigned access */
} Eth_RxDescr1;

/* RDES2 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    Eth_RxDescr2_RF_Bits R;     /* Read Format Bitfiled Access */
    Eth_RxDescr2_WF_Bits W;     /* Write back Format Bitfiled Access */
    Eth_RxContextDescr2_Bits C; /* Context Descriptor Format Bitfiled Access */
    uint32 U;                   /* Unsigned access */
} Eth_RxDescr2;

/* RDES3 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    Eth_RxDescr3_RF_Bits R;     /* Read Format Bitfiled Access */
    Eth_RxDescr3_WF_Bits W;     /* Write back Format Bitfiled Access */
    Eth_RxContextDescr3_Bits C; /* Context Descriptor Format Bitfiled Access */
    uint32 U;                   /* Unsigned access */
} Eth_RxDescr3;

/* TDES0 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    Eth_TxDescr0_RF_Bits R;     /* Read Format Bitfiled Access */
    Eth_TxDescr0_WF_Bits W;     /* Write-back Format Bitfiled Access */
    Eth_TxContextDescr0_Bits C; /* Context Descriptor Format Bitfiled Access */
    uint32 U;                   /* Unsigned access */
} Eth_TxDescr0;

/* TDES1 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    Eth_TxDescr1_RF_Bits R;     /* Read Format Bitfiled Access */
    Eth_TxDescr1_WF_Bits W;     /* Write-back Format Bitfiled Access */
    Eth_TxContextDescr1_Bits C; /* Context Descriptor Format Bitfiled Access */
    uint32 U;                   /* Unsigned access */
} Eth_TxDescr1;

/* TDES2 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    Eth_TxDescr2_RF_Bits R;     /* Read Format Bitfiled Access */
    Eth_TxDescr2_WF_Bits W;     /* Write-back Format Bitfiled Access */
    Eth_TxContextDescr2_Bits C; /* COntext Descriptor Format Bitfiled Access */
    uint32 U;                   /* Unsigned access */
} Eth_TxDescr2;

/* TDES3 */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    Eth_TxDescr3_RF_Bits R;     /* Read Format Bitfiled Access */
    Eth_TxDescr3_WF_Bits W;     /* Write-back Format Bitfiled Access */
    Eth_TxContextDescr3_Bits C; /* Context Descriptor Format Bitfiled Access */
    uint32 U;                   /* Unsigned access */
} Eth_TxDescr3;

/* MAC VLAN Tag type\control registers*/
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    ETH_MAC_VLAN_TAG MAC_VLAN_TAG; /* 50, MAC VLAN Tag IEEE 802.1Q VLAN type packets*/
    ETH_MAC_VLAN_TAG_CTRL
    MAC_VLAN_TAG_CTRL; /* 50, MAC VLAN Tag Control Register, redefine format for MAC VLAN Tag.*/
}ETH_MAC_VLAN_TAG_T_C;

/* MAC VLAN Tag data\filter registers */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    ETH_MAC_VLAN_TAG_DATA MAC_VLAN_TAG_DATA;     /* 54, MAC VLAN Tag Data Register.*/
    ETH_MAC_VLAN_TAG_FILTER MAC_VLAN_TAG_FILTER; /* 54, MAC VLAN Tag Filter Register.*/
}ETH_MAC_VLAN_TAG_D_F;

/* MAC VLAN Inclusion or Replacement Registers */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    ETH_MAC_VLAN_INCL_Q MAC_VLAN_INCL_Q; /* 60, MAC VLAN Tag Inclusion or Replacement Register per Queue */
    ETH_MAC_VLAN_INCL MAC_VLAN_INCL;     /* 60, MAC VLAN Tag Inclusion or Replacement Register.*/
}ETH_MAC_VLAN_INCL_Q_A;

/* MAC Wake-up Packet Filter Registers */
typedef union
/* #Violation: eth_regiter_h_REF_1 */
{
    ETH_MAC_RWK_PACKET_FILTER MAC_RWK_PACKET_FILTER; /* C4, MAC Wake-up Packet Filter Register,RESERVED.*/
    ETH_RWK_FILTER_COMMAND_0 RWK_FILTER_COMMAND_0;   /* C4, MAC Wake-up Filter Command 0 Register,RESERVED.*/
    ETH_RWK_FILTER_OFFSET_0 RWK_FILTER_OFFSET_0;     /* C4, MAC Wake-up Filter Offset 0 Register,RESERVED.*/
    ETH_RWK_FILTER_CRC RWK_FILTER_CRC;               /* C4, MAC Wake-up Filter CRC Register,RESERVED.*/
    ETH_RWK_FILTER_BYTE_MASK RWK_FILTER_BYTE_MASK;   /* C4, MAC Wake-up Filter Byte Mask register */
}ETH_MAC_RWK_FILTER;

/**********************************************************************************************************************
 *                                        ETH Register Configuration Structure
 *********************************************************************************************************************/
/* MTL_TXQ0 Register */
typedef volatile struct
{
    ETH_MTL_TXQ0_OPERATION_MODE OPERATION_MODE; /* 0, MTL Queue 0 Transmit Operation Mode Register*/
    ETH_MTL_TXQ0_UNDERFLOW UNDERFLOW;           /* 4, MTL Queue 0 Transmit Underflow Counter Register*/
    ETH_MTL_TXQ0_DEBUG MTL_TXQ_DEBUG;           /* 8, MTL Queue 0 Transmit Debug Register*/
    ureg32 reserved_C[2];                       /* C, internal Reserved */
    ETH_MTL_TXQ0_ETS_STATUS ETS_STATUS;         /* 14, MTL Queue 0 Transmit Status Register*/
    ETH_MTL_TXQ0_QUANTUM_WEIGHT QUANTUM_WEIGHT; /* 18, MTL Queue 0 Transmit Quantum or Weights Register*/
} ETH_MTL_TXQ0;

/* MTL_Q0 Register */
typedef volatile struct
{
    ETH_MTL_Q0_INTERRUPT_CONTROL_STATUS INTERRUPT_CONTROL_STATUS; /*0,MTL Queue 0 Interrupt Control Status Register*/
} ETH_MTL_Q0;

/* MTL_RXQ0 Register */
typedef volatile struct
{
    ETH_MTL_RXQ0_OPERATION_MODE OPERATION_MODE; /* 0, MTL Queue 0 Receive Operation Mode Register*/
    ETH_MTL_RXQ0_MISSED_PACKET_OVERFLOW_CNT MISSED_PACKET_OVERFLOW_CNT; /* 4, MTL Queue 0 Missed Packet and Overflow Counter register*/
    /* 4, MTL Queue 0 Receive Missed Packet and Overflow Counter Register*/
    ETH_MTL_RXQ0_DEBUG MTL_RXQ_DEBUG; /* 8, MTL Queue 0 Receive Debug Register*/
    ETH_MTL_RXQ0_CONTROL CONTROL;     /* C, MTL Queue 0 Receive Control Register*/
} ETH_MTL_RXQ0;

/* MTL_TXQ Register */
typedef volatile struct
{
    ETH_MTL_TXQ_OPERATION_MODE OPERATION_MODE;   /* 0, MTL Queue Transmit Operation Mode Register*/
    ETH_MTL_TXQ_UNDERFLOW UNDERFLOW;             /* 4, MTL Queue Transmit Underflow Counter Register*/
    ETH_MTL_TXQ_DEBUG MTL_TXQ_DEBUG;             /* 8, MTL Queue Transmit Debug Register*/
    ureg32 reserved_C;                           /* C, internal Reserved */
    ETH_MTL_TXQ_ETS_CONTROL ETS_CONTROL;         /* 10, MTL Queue Transmit ETS Control Register*/
    ETH_MTL_TXQ_ETS_STATUS ETS_STATUS;           /* 14, MTL Queue Transmit ETS Status Register*/
    ETH_MTL_TXQ_QUANTUM_WEIGHT QUANTUM_WEIGHT;   /* 18, MTL Queue Transmit Quantum or Weights Register*/
    ETH_MTL_TXQ_SENDSLOPECREDIT SENDSLOPECREDIT; /* 1C, MTL Queue Transmit SendSlopeCredit Register*/
    ETH_MTL_TXQ_HICREDIT HICREDIT;               /* 20, MTL Queue Transmit HiCredit Register*/
    ETH_MTL_TXQ_LOCREDIT LOCREDIT;               /* 24, MTL Queue Transmit LoCredit Register*/
} ETH_MTL_TXQ;

/* MTL_Q Register */
typedef volatile struct
{
    ETH_MTL_Q_INTERRUPT_CONTROL_STATUS INTERRUPT_CONTROL_STATUS; /* 0, MTL Queue Interrupt Status Register*/
} ETH_MTL_Q;

/* MTL_RXQ Register */
typedef volatile struct
{
    ETH_MTL_RXQ_OPERATION_MODE OPERATION_MODE; /* 0, MTL Queue Receive Operation Mode Register*/
    ETH_MTL_RXQ_MISSED_PACKET_OVERFLOW_CNT MISSED_PACKET_OVERFLOW_CNT; /* 4, MTL Queue Missed Packet and Overflow Counter register*/
    /* 4, MTL Queue Receive Missed Packet and Overflow Counter Register*/
    ETH_MTL_RXQ_DEBUG MTL_RXQ_DEBUG; /* 8, MTL Queue Receive Debug Register*/
    ETH_MTL_RXQ_CONTROL CONTROL;     /* C, MTL Queue Receive Control Register*/
} ETH_MTL_RXQ;

/* DMA_CH Register  */
typedef volatile struct
{
    ETH_DMA_CH_CONTROL CONTROL;       /* 0, DMA Channel Control Register*/
    ETH_DMA_CH_TX_CONTROL TX_CONTROL; /* 4, DMA Channel Transmit Control Register*/
    ETH_DMA_CH_RX_CONTROL RX_CONTROL; /* 8, DMA Channel Receive Control Register*/
    ureg32 RESERVED_C[2];              /* C, internal Reserved , TXDESC_LIST_HADDRESS 0x1110*/
    ETH_DMA_CH_TXDESC_LIST_ADDRESS
    TXDESC_LIST_ADDRESS;  /* 14, DMA Channel Transmit Descriptor List Address Register*/
    ureg32 RESERVED_18; /* 18, internal Reserved RXDESC_LIST_HADDRESS*/
    ETH_DMA_CH_RXDESC_LIST_ADDRESS
    RXDESC_LIST_ADDRESS; /* 1C, DMA Channel Receive Descriptor List Address Register*/
    ETH_DMA_CH_TXDESC_TAIL_POINTER
    TXDESC_TAIL_POINTER;  /* 20, DMA Channel Transmit Descriptor Tail Pointer Register*/
    ureg32 RESERVED_24; /* 24, internal Reserved */
    ETH_DMA_CH_RXDESC_TAIL_POINTER
    RXDESC_TAIL_POINTER;                              /* 28, DMA Channel Recieve Descriptor Tail Pointer Register*/
    ETH_DMA_CH_TXDESC_RING_LENGTH TXDESC_RING_LENGTH; /* 2C, DMA Channel Transmit Descriptor Ring Length Register*/
    ETH_DMA_CH_RXDESC_RING_LENGTH RXDESC_RING_LENGTH; /* 30, DMA Channel Recieve Descriptor Ring Length Register*/
    ETH_DMA_CH_INTERRUPT_ENABLE INTERRUPT_ENABLE;     /* 34, DMA Channel Interrupt Enable Register*/
    ETH_DMA_CH_RX_INTERRUPT_WATCHDOG_TIMER RX_INTERRUPT_WATCHDOG_TIMER; /* 38, DMA Channel Recieve Interrupt Watchdog Timer Register*/
    ETH_DMA_CH_SLOT_FUNCTION_CONTROL_STATUS SLOT_FUNCTION_CONTROL_STATUS; /* 3C, DMA Channel Slot Function Control and Status Register*/
    ureg32 RESERVED_40; /* 40, internal Reserved */
    ETH_DMA_CH_CURRENT_APP_TXDESC
    CURRENT_APP_TXDESC;   /* 44, DMA Channel Current Application Transmit Descriptor Register*/
    ureg32 RESERVED_48; /* 48, internal Reserved */
    ETH_DMA_CH_CURRENT_APP_RXDESC
    CURRENT_APP_RXDESC;   /* 4C, DMA Channel Current Application Receive Descriptor Register*/
    ureg32 RESERVED_50; /* 50, internal Reserved ,Current_App_TxBuffer_H*/
    ETH_DMA_CH_CURRENT_APP_TXBUFFER
    CURRENT_APP_TXBUFFER; /* 54, DMA Channel Current Application Transmit Buffer Address Register*/
    ureg32 RESERVED_58; /* 58, internal Reserved , Current_App_RxBuffer_H*/
    ETH_DMA_CH_CURRENT_APP_RXBUFFER
    CURRENT_APP_RXBUFFER;     /* 5C, DMA Channel Current Application Receive Buffer Address Register*/
    ETH_DMA_CH_STATUS STATUS; /* 60, DMA Channel Status Register*/
    ETH_DMA_CH_MISS_FRAME_CNT MISS_FRAME_CNT; /* 64, DMA Channel Missed Frames Count Register*/
    ETH_DMA_CH_RXP_ACCEPT_CNT RXP_ACCEPT_CNT; /* 68, DMA Channel Rx Parser accept Frames Count Register, THA6206 and
                                               THA6412 are supported, but THA6104 is not supported(RESERVED)*/
    ureg32 RESERVED_6C[5];                    /* 6C, internal Reserved 0x80-0x6C==>20*/
} ETH_DMA_CH;

/* ETH Module Register */
typedef volatile struct
{
    /* MAC Registers  */
    ETH_MAC_CONFIGURATION MAC_CONFIGURATION;         /* 0, MAC Configuration Register*/
    ETH_MAC_EXT_CONFIGURATION MAC_EXT_CONFIGURATION; /* 4, MAC Extended Configuration Register*/
    ETH_MAC_PACKET_FILTER MAC_PACKET_FILTER;         /* 8, MAC Packet Filter Register*/
    ETH_MAC_WATCHDOG_TIMEOUT MAC_WATCHDOG_TIMEOUT;   /* C, MAC Watchdog Timeout Register*/
    ETH_MAC_HASH_Table_Reg0 MAC_HASH_Table_Reg0;     /* 10, Hash table register 0*/
    ETH_MAC_HASH_Table_Reg1 MAC_HASH_Table_Reg1;     /* 14, Hash table register 1,RESERVED.*/
    ETH_MAC_HASH_Table_Reg2 MAC_HASH_Table_Reg2;     /* 18, Hash table register 2,RESERVED.*/
    ETH_MAC_HASH_Table_Reg3 MAC_HASH_Table_Reg3;     /* 1c, Hash table register 3,RESERVED.*/
    ETH_MAC_HASH_Table_Reg4 MAC_HASH_Table_Reg4;     /* 20, Hash table register 4,RESERVED.*/
    ETH_MAC_HASH_Table_Reg5 MAC_HASH_Table_Reg5;     /* 24, Hash table register 5,RESERVED.*/
    ETH_MAC_HASH_Table_Reg6 MAC_HASH_Table_Reg6;     /* 28, Hash table register 6,RESERVED.*/
    ETH_MAC_HASH_Table_Reg7 MAC_HASH_Table_Reg7;     /* 2c, Hash table register 7,RESERVED.*/
    ureg32 RESERVED_30[8];                           /* 30, internal Reserved */
    ETH_MAC_VLAN_TAG_T_C MVT;                         /* 50, MAC VLAN Tag type\control Registers*/
    ETH_MAC_VLAN_TAG_D_F MVTD;                        /* 54, MAC VLAN Tag data\filter registers */
    ETH_MAC_VLAN_HASH_TABLE MAC_VLAN_HASH_TABLE;     /* 58, MAC VLAN Hash Table Register*/
    ureg32 RESERVED_5C;                              /* 5C, internal Reserved */
    ETH_MAC_VLAN_INCL_Q_A MVI;                       /* 60, MAC VLAN Inclusion or Replacement Registers */
    ETH_MAC_INNER_VLAN_INCL MAC_INNER_VLAN_INCL; /* 64,inner VLAN Tag,RESERVED. */
    ureg32 RESERVED_68[2];                        /* 68, internal Reserved */

    ETH_MAC_Q0_TX_FLOW_CTRL MAC_Q0_TX_FLOW_CTRL; /* 70, MAC Queue 0 TX Flow Control Register*/
    ETH_MAC_Q1_TX_FLOW_CTRL MAC_Q1_TX_FLOW_CTRL; /* 74, MAC Queue 1 TX Flow Control Register*/
    ETH_MAC_Q1_TX_FLOW_CTRL MAC_Q2_TX_FLOW_CTRL; /* 78, MAC Queue 2 TX Flow Control Register, THA6206 and THA6412
                                                   are supported, but THA6104 is not supported*/
    ETH_MAC_Q1_TX_FLOW_CTRL MAC_Q3_TX_FLOW_CTRL; /* 7c, MAC Queue 3 TX Flow Control Register, THA6206 and THA6412
                                                   are supported, but THA6104 is not supported*/
    ureg32 RESERVED_80[4];                   /* 80, internal Reserved */
    ETH_MAC_RX_FLOW_CTRL MAC_RX_FLOW_CTRL;   /* 90, MAC Receive Flow Control Register*/
    ETH_MAC_RXQ_CTRL4 MAC_RXQ_CTRL4;         /* 94, MAC Receive Queue Control 4 register*/
    ETH_MAC_TXQ_PRTY_MAP0 MAC_TXQ_Prty_Map0; /* 98, priority value*/
    ureg32 RESERVED_9C;                     /* 9c, ETH_MAC_TXQ_PRTY_MAP1, THA6104, THA6206 and THA6412 RESERVED. */

    ETH_MAC_RXQ_CTRL0 MAC_RXQ_CTRL0;               /* A0, MAC Receive Queue Control 0 Register*/
    ETH_MAC_RXQ_CTRL1 MAC_RXQ_CTRL1;               /* A4, MAC Receive Queue Control 1 Register*/
    ETH_MAC_RXQ_CTRL2 MAC_RXQ_CTRL2;               /* A8, MAC Receive Queue Control 2 Register*/
    ureg32 RESERVED_AC;                          /* AC, internal Reserved ,ETH_MAC_RXQ_CTRL3 for queue 4-7,RESERVED.*/
    ETH_MAC_INTERRUPT_STATUS MAC_INTERRUPT_STATUS; /* B0, MAC Interrupt Status Register*/
    ETH_MAC_INTERRUPT_ENABLE MAC_INTERRUPT_ENABLE; /* B4, MAC Interrupt Enable Register*/
    ETH_MAC_RX_TX_STATUS MAC_RX_TX_STATUS;         /* B8, MAC Receive Transmit Status Register*/
    ureg32 RESERVED_BC;                          /* BC, internal Reserved */
    ETH_MAC_PMT_CONTROL_STATUS MAC_PMT_CONTROL_STATUS; /* C0, MAC PMT Control and Status Register,RESERVED.*/
    ETH_MAC_RWK_FILTER RF;                       /* C4, MAC Wake-up Packet Filter Registers.*/
    ureg32 RESERVED_C8[2]; /* C8, internal Reserved */

    ETH_MAC_LPI_CONTROL_STATUS MAC_LPI_CONTROL_STATUS; /* D0, MAC LPI Control and Status Register,RESERVED.*/
    ETH_MAC_LPI_TIMERS_CONTROL MAC_LPI_TIMERS_CONTROL; /* D4, MAC LPI Timers Control Register,RESERVED.*/
    ETH_MAC_LPI_ENTRY_TIMER MAC_LPI_ENTRY_TIMER;       /* D8, MAC LPI Entry Timer Register,RESERVED.*/
    ETH_MAC_1US_TIC_COUNTER MAC_1US_TIC_COUNTER;       /* DC, MAC One Microsecond Tic Counter Register,RESERVED.*/
    ureg32 RESERVED_E0[6];                             /* e0, internal Reserved */

    ETH_MAC_PHYIF_CONTROL_STATUS MAC_PHYIF_CONTROL_STATUS; /* F8, MAC PHY Interface Control and Status Register, THA6206
                                                            and THA6412 are supported, but THA6104 is not supported*/
    ureg32 RESERVED_FC[5];                                 /* FC, internal Reserved */

    ETH_MAC_VERSION MAC_VERSION; /* 110, MAC Version Register*/
    ETH_MAC_DEBUG MAC_DEBUG;     /* 114, MAC Debug Register*/
    ureg32 RESERVED_118;       /* 118, internal Reserved */

    ETH_MAC_HW_FEATURE0 MAC_HW_FEATURE0; /* 11C, MAC Hardware Feature Register 0*/
    ETH_MAC_HW_FEATURE1 MAC_HW_FEATURE1; /* 120, MAC Hardware Feature Register 1*/
    ETH_MAC_HW_FEATURE2 MAC_HW_FEATURE2; /* 124, MAC Hardware Feature Register 2*/
    ETH_MAC_HW_FEATURE3 MAC_HW_FEATURE3; /* 128, MAC Hardware Feature Register 3*/
    ETH_MAC_HW_FEATURE4 MAC_HW_FEATURE4; /* 12C, MAC Hardware Feature Register 4*/
    ureg32 RESERVED_130[4];              /* 130, internal Reserved */

    /* Automotive Safety,Data Path Parity Errors */
    ETH_MAC_DPP_FSM_INTERRUPT_STATUS
    MAC_DPP_FSM_INTERRUPT_STATUS;              /* 140, AN control register */
    ureg32 RESERVED_144;                       /* 144, internal Reserved */
    ETH_MAC_FSM_CONTROL MAC_FSM_CONTROL;       /* 148, AN control register */
    ETH_MAC_FSM_ACT_TIMER MAC_FSM_ACT_TIMER;   /* 14c, AN control register */
    ureg32 RESERVED_150;                       /* 150, ETH_MAC_SNPS_SCS_REG1 */

    ureg32 RESERVED_154[43];                   /* 154, internal Reserved */
    ETH_MAC_MDIO_ADDRESS MAC_MDIO_ADDRESS;     /* 200, MAC MDIO Address Register*/
    ETH_MAC_MDIO_DATA MAC_MDIO_DATA;       /* 204, MAC MDIO Data Register*/

    /* GPIO  disabled */
    ETH_MAC_GPIO_CONTROL MAC_GPIO_CONTROL; /* 208, GPIO, THA6104, THA6206 and THA6412 RESERVED.*/
    ETH_MAC_GPIO_STATUS MAC_GPIO_STATUS;   /* 20c, GPIO, THA6104, THA6206 and THA6412 RESERVED.*/
    /* ARP OFFLOAD disabled */
    ETH_MAC_ARP_ADDRESS MAC_ARP_ADDRESS;   /* 210, arp address, THA6206 and THA6412 RESERVED*/
    ureg32 RESERVED_214[7];                /* 214, internal Reserved */
    ETH_MAC_CSR_SW_CTRL MAC_CSR_SW_CTRL;   /* 230, MAC CSR Software Controls Register*/

    /* Frame Preemption */
    ETH_MAC_FPE_CTRL_STS MAC_FPE_CTRL_STS; /* 234, Frame Preemption, THA6206 and THA6412 are supported,
                                            but THA6104 is not supported(RESERVED) */
    ETH_MAC_EXT_CFG1 MAC_EXT_CFG1;         /* 238, MAC Extended Configuration Register 1, Split mode control field and 
                                            offset field for Split Header feature, THA6206 and THA6412 are supported, 
                                            but THA6104 is not supported(RESERVED)*/
    ureg32 RESERVED_23C;                   /* 23C, internal Reserved */

    /* FLEXI_PPS_OUT */
    ETH_MAC_PRESN_TIME_NS
    MAC_PRESN_TIME_NS; /* 240, 32-bit binary rollover equivalent time of the PTP System Time in ns */
    ETH_MAC_PRESN_TIME_UPDT MAC_PRESN_TIME_UPDT; /* 244,32-bit value of MAC 1722 Presentation Time in ns */
    ureg32 RESERVED_248[46];                     /* 248, internal Reserved */

    ETH_MAC_ADDRESS_HIGH0 MAC_ADDRESS_HIGH0; /* 300,MACAddress0HighRegister*/
    ETH_MAC_ADDRESS_LOW0 MAC_ADDRESS_LOW0;   /* 304,MACAddress0LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH1;  /* 308,MACAddress1HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW1;    /* 30C,MACAddress1LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH2;  /* 310,MACAddress2HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW2;    /* 314,MACAddress2LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH3;  /* 318,MACAddress3HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW3;    /* 31C,MACAddress3LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH4;  /* 320,MACAddress4HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW4;    /* 324,MACAddress4LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH5;  /* 328,MACAddress5HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW5;    /* 32C,MACAddress5LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH6;  /* 330,MACAddress6HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW6;    /* 334,MACAddress6LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH7;  /* 338,MACAddress7HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW7;    /* 33C,MACAddress7LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH8;  /* 340,MACAddress8HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW8;    /* 344,MACAddress8LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH9;  /* 348,MACAddress9HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW9;    /* 34C,MACAddress9LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH10; /* 350,MACAddress10HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW10;   /* 354,MACAddress10LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH11; /* 358,MACAddress11HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW11;   /* 35C,MACAddress11LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH12; /* 360,MACAddress12HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW12;   /* 364,MACAddress12LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH13; /* 368,MACAddress13HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW13;   /* 36C,MACAddress13LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH14; /* 370,MACAddress14HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW14;   /* 374,MACAddress14LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH15; /* 378,MACAddress15HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW15;   /* 37C,MACAddress15LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH16; /* 380,MACAddress16HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW16;   /* 384,MACAddress16LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH17; /* 388,MACAddress17HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW17;   /* 38C,MACAddress17LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH18; /* 390,MACAddress18HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW18;   /* 394,MACAddress18LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH19; /* 398,MACAddress19HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW19;   /* 39C,MACAddress19LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH20; /* 3A0,MACAddress20HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW20;   /* 3A4,MACAddress20LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH21; /* 3A8,MACAddress21HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW21;   /* 3AC,MACAddress21LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH22; /* 3B0,MACAddress22HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW22;   /* 3B4,MACAddress22LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH23; /* 3B8,MACAddress23HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW23;   /* 3BC,MACAddress23LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH24; /* 3C0,MACAddress24HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW24;   /* 3C4,MACAddress24LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH25; /* 3C8,MACAddress25HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW25;   /* 3CC,MACAddress25LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH26; /* 3D0,MACAddress26HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW26;   /* 3D4,MACAddress26LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH27; /* 3D8,MACAddress27HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW27;   /* 3DC,MACAddress27LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH28; /* 3E0,MACAddress28HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW28;   /* 3E4,MACAddress28LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH29; /* 3E8,MACAddress29HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW29;   /* 3EC,MACAddress29LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH30; /* 3F0,MACAddress30HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW30;   /* 3F4,MACAddress30LowRegister*/
    ETH_MAC_ADDRESS_HIGH MAC_ADDRESS_HIGH31; /* 3F8,MACAddress31HighRegister*/
    ETH_MAC_ADDRESS_LOW MAC_ADDRESS_LOW31;   /* 3FC,MACAddress31LowRegister*/
    ureg32 RESERVED_400[192];                 /* 400, internal Reserved */

    /* MMC register */
    ETH_MMC_CONTROL MMC_CONTROL;                             /* 700, MMC Control Register*/
    ETH_MMC_RX_INTERRUPT MMC_RX_INTERRUPT;                   /* 704, MMC Receive Interrupts Register*/
    ETH_MMC_TX_INTERRUPT MMC_TX_INTERRUPT;                   /* 708, MMC Transmit Interrupts Register*/
    ETH_MMC_RX_INTERRUPT_MASK MMC_RX_INTERRUPT_MASK;         /* 70C, MMC Receive Interrupts Mask Register*/
    ETH_MMC_TX_INTERRUPT_MASK MMC_TX_INTERRUPT_MASK;         /* 710, MMC Transmit Interrupts Mask Register*/
    ETH_TX_OCTET_COUNT_GOOD_BAD TX_OCTET_COUNT_GOOD_BAD;     /* 714, Good And Bad Transmitted Octet Count Register*/
    ETH_TX_PACKET_COUNT_GOOD_BAD TX_PACKET_COUNT_GOOD_BAD;   /* 718, Good And Bad Transmitted Packets Count Register*/
    ETH_TX_BROADCAST_PACKETS_GOOD TX_BROADCAST_PACKETS_GOOD; /* 71C, Good Transmitted Broadcast Packets Count Register*/
    ETH_TX_MULTICAST_PACKETS_GOOD TX_MULTICAST_PACKETS_GOOD; /* 720, Good Transmitted Multicast Packets Count Register*/
    ETH_TX_64OCTETS_PACKETS_GOOD_BAD
    TX_64OCTETS_PACKETS_GOOD_BAD; /* 724, Good And Bad 64 Octets Packets Transmitted Count Register*/
    ETH_TX_65TO127OCTETS_PACKETS_GOOD_BAD
    TX_65TO127OCTETS_PACKETS_GOOD_BAD; /* 728, Good And Bad 65to127 Octets Packets Transmitted Count Register*/
    ETH_TX_128TO255OCTETS_PACKETS_GOOD_BAD
    TX_128TO255OCTETS_PACKETS_GOOD_BAD; /* 72C, Good And Bad 128to255 Octets Packets Transmitted Count Register*/
    ETH_TX_256TO511OCTETS_PACKETS_GOOD_BAD
    TX_256TO511OCTETS_PACKETS_GOOD_BAD; /* 730, Good And Bad 256to511 Octets Packets Transmitted Count Register*/
    ETH_TX_512TO1023OCTETS_PACKETS_GOOD_BAD
    TX_512TO1023OCTETS_PACKETS_GOOD_BAD; /* 734, Good And Bad 512to1023 Octets Packets Transmitted Count Register*/
    ETH_TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD
    TX_1024TOMAXOCTETS_PACKETS_GOOD_BAD; /* 738, Good And Bad 1024toMax Octets Packets Transmitted Count Register*/
    ETH_TX_UNICAST_PACKETS_GOOD_BAD
    TX_UNICAST_PACKETS_GOOD_BAD; /* 73C, Good Transmitted Unicat Packets Count Register*/
    ETH_TX_MULTICAST_PACKETS_GOOD_BAD
    TX_MULTICAST_PACKETS_GOOD_BAD; /* 740, Good And Bad Transmitted Multicast Packets Count Register*/
    ETH_TX_BROADCAST_PACKETS_GOOD_BAD
    TX_BROADCAST_PACKETS_GOOD_BAD; /* 744, Good And Bad Transmitted Broadcast Packets Count Register*/
    ETH_TX_UNDERFLOW_ERROR_PACKETS
    TX_UNDERFLOW_ERROR_PACKETS; /* 748, Transmitted Underflow Error Packets Count Register*/
    ETH_TX_SINGLE_COLLISION_GOOD_PACKETS
    TX_SINGLE_COLLISION_GOOD_PACKETS; /* 74C, Good Transmitted Single Collision Count Register*/
    ETH_TX_MULTIPLE_COLLISION_GOOD_PACKETS
    TX_MULTIPLE_COLLISION_GOOD_PACKETS;                      /* 750, Transmitted Multiple Collision Count Register*/
    ETH_TX_DEFERRED_PACKETS TX_DEFERRED_PACKETS;             /* 754, Transmitted Deferred Packets Count Register*/
    ETH_TX_LATE_COLLISION_PACKETS TX_LATE_COLLISION_PACKETS; /* 758, Transmitted Late Collision Packets Count Register*/
    ETH_TX_EXCESSIVE_COLLISION_PACKETS
    TX_EXCESSIVE_COLLISION_PACKETS; /* 75C, Transmitted Excessive Collision Packets Count Register*/
    ETH_TX_CARRIER_ERROR_PACKETS TX_CARRIER_ERROR_PACKETS; /* 760, Transmitted Carrier Error Packets Count Register*/
    ETH_TX_OCTET_COUNT_GOOD TX_OCTET_COUNT_GOOD;           /* 764, Good Transmitted Octet Count Register*/
    ETH_TX_PACKET_COUNT_GOOD TX_PACKET_COUNT_GOOD;         /* 768, Good Transmitted Packet Count Register*/
    ETH_TX_EXCESSIVE_DEFERRAL_ERROR
    TX_EXCESSIVE_DEFERRAL_ERROR;                     /* 76C, Transmitted Excessive Deferral Error Count Register*/
    ETH_TX_PAUSE_PACKETS TX_PAUSE_PACKETS;           /* 770, Transmitted Pause Packets Count Register*/
    ETH_TX_VLAN_PACKETS_GOOD TX_VLAN_PACKETS_GOOD;   /* 774, Good Transmitted VLAN Packets Count Register*/
    ETH_TX_OSIZE_PACKETS_GOOD TX_OSIZE_PACKETS_GOOD; /* 778, Good Transmitted Osize Packets Count Register*/
    ureg32 RESERVED_77C;                           /* 77C, internal Reserved */
    ETH_RX_PACKETS_COUNT_GOOD_BAD RX_PACKETS_COUNT_GOOD_BAD;   /* 780, Good And Bad Received Packets Count Register*/
    ETH_RX_OCTET_COUNT_GOOD_BAD RX_OCTET_COUNT_GOOD_BAD;       /* 784, Good And Bad Received Octet Count Register*/
    ETH_RX_OCTET_COUNT_GOOD RX_OCTET_COUNT_GOOD;               /* 788, Good Received Octet Count Register*/
    ETH_RX_BROADCAST_PACKETS_GOOD RX_BROADCAST_PACKETS_GOOD;   /* 78C, Good Received Broadcast Packets Count Register*/
    ETH_RX_MULTICAST_PACKETS_GOOD RX_MULTICAST_PACKETS_GOOD;   /* 790, Good Received Multicast Packets Count Register*/
    ETH_RX_CRC_ERROR_PACKETS RX_CRC_ERROR_PACKETS;             /* 794, Received CRC Error Packets Count Register*/
    ETH_RX_ALIGNMENT_ERROR_PACKETS RX_ALIGNMENT_ERROR_PACKETS; /* 798, Received Alignment Error Count Register*/
    ETH_RX_RUNT_ERROR_PACKETS RX_RUNT_ERROR_PACKETS;           /* 79C, Received Runtime Error Count Register*/
    ETH_RX_JABBER_ERROR_PACKETS RX_JABBER_ERROR_PACKETS;       /* 7A0, Received Jabber Error Count Register*/
    ETH_RX_UNDERSIZE_PACKETS_GOOD RX_UNDERSIZE_PACKETS_GOOD;   /* 7A4, Good Received Undersized Packets Count Register*/
    ETH_RX_OVERSIZE_PACKETS_GOOD RX_OVERSIZE_PACKETS_GOOD;     /* 7A8, Good Received Oversized Packets Count Register*/
    ETH_RX_64OCTETS_PACKETS_GOOD_BAD
    RX_64OCTETS_PACKETS_GOOD_BAD; /* 7AC, Good And Bad 64 Octets Packets Received Count Register*/
    ETH_RX_65TO127OCTETS_PACKETS_GOOD_BAD
    RX_65TO127OCTETS_PACKETS_GOOD_BAD; /* 7B0, Good And Bad 65to127 Octets Packets Received Count Register*/
    ETH_RX_128TO255OCTETS_PACKETS_GOOD_BAD
    RX_128TO255OCTETS_PACKETS_GOOD_BAD; /* 7B4, Good And Bad 128to255 Octets Packets Received Count Register*/
    ETH_RX_256TO511OCTETS_PACKETS_GOOD_BAD
    RX_256TO511OCTETS_PACKETS_GOOD_BAD; /* 7B8, Good And Bad 256to511 Octets Packets Received Count Register*/
    ETH_RX_512TO1023OCTETS_PACKETS_GOOD_BAD
    RX_512TO1023OCTETS_PACKETS_GOOD_BAD; /* 7BC, Good And Bad 512to1023 Octets Packets Received Count Register*/
    ETH_RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD
    RX_1024TOMAXOCTETS_PACKETS_GOOD_BAD; /* 7C0, Good And Bad 1024toMax Octets Packets Received Count Register*/
    ETH_RX_UNICAST_PACKETS_GOOD RX_UNICAST_PACKETS_GOOD; /* 7C4, Good Received Unicast Packets Count Register*/
    ETH_RX_LENGTH_ERROR_PACKETS RX_LENGTH_ERROR_PACKETS; /* 7C8, Received Length Error Packets Count Register*/
    ETH_RX_OUT_OF_RANGE_TYPE_PACKETS RX_OUT_OF_RANGE_TYPE_PACKETS; /* 7CC, Received Out Of Range Type Count Register*/
    ETH_RX_PAUSE_PACKETS RX_PAUSE_PACKETS;                         /* 7D0, Received Pause Packets Count Register*/
    ETH_RX_FIFO_OVERFLOW_PACKETS RX_FIFO_OVERFLOW_PACKETS;         /* 7D4, Received FIFO Overflow Count Register*/
    ETH_RX_VLAN_PACKETS_GOOD_BAD RX_VLAN_PACKETS_GOOD_BAD; /* 7D8, Good And Bad Received VLAN Packets Count Registerv*/
    ETH_RX_WATCHDOG_ERROR_PACKETS RX_WATCHDOG_ERROR_PACKETS; /* 7DC, Received Watchdog Error Count Register*/
    ETH_RX_RECEIVE_ERROR_PACKETS RX_RECEIVE_ERROR_PACKETS;   /* 7E0, Received Receive Error Count Register*/
    ETH_RX_CONTROL_PACKETS_GOOD RX_CONTROL_PACKETS_GOOD;     /* 7E4, Good Received Control Packets Count Register*/
    ureg32 RESERVED_7E8;                                   /* 7E8, internal Reserved */
    ETH_TX_LPI_USEC_CNTR TX_LPI_USEC_CNTR;                   /* 7EC, Transmitted LPI Microseconds Count Register*/
    ETH_TX_LPI_TRAN_CNTR TX_LPI_TRAN_CNTR;                   /* 7F0, Transmitted LPI Transition Count Register*/
    ETH_RX_LPI_USEC_CNTR RX_LPI_USEC_CNTR;                   /* 7F4, Received Microseconds LPI Count Register*/
    ETH_RX_LPI_TRAN_CNTR RX_LPI_TRAN_CNTR;                   /* 7F8, Received LPI Transition Count Register*/
    ureg32 RESERVED_7FC;                                   /* 7FC, internal Reserved */
    ETH_MMC_IPC_RX_INTERRUPT_MASK MMC_IPC_RX_INTERRUPT_MASK; /* 800, MMC IPC Receive Interrupts Mask Register*/
    ureg32 RESERVED_804;                                   /* 804, internal Reserved */
    ETH_MMC_IPC_RX_INTERRUPT MMC_IPC_RX_INTERRUPT;           /* 808, MMC IPC Receive Interrupts Register*/
    ureg32 RESERVED_80C;                                   /* 80C, internal Reserved */
    ETH_RXIPV4_GOOD_PACKETS RXIPV4_GOOD_PACKETS;             /* 810, Good Received RxIPv4 Packets Count Register*/
    ETH_RXIPV4_HEADER_ERROR_PACKETS
    RXIPV4_HEADER_ERROR_PACKETS;                             /* 814, Received IPv4 Header Error Packets Count Register*/
    ETH_RXIPV4_NO_PAYLOAD_PACKETS RXIPV4_NO_PAYLOAD_PACKETS; /* 818, Received IPv4 No Payload Packets Count Register*/
    ETH_RXIPV4_FRAGMENTED_PACKETS RXIPV4_FRAGMENTED_PACKETS; /* 81C, Received IPv4 Fragmented Packets Count Register*/
    ETH_RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS
    RXIPV4_UDP_CHECKSUM_DISABLED_PACKETS;        /* 820, Received IPv4 UPD Checksum Disabled Packets Count Register*/
    ETH_RXIPV6_GOOD_PACKETS RXIPV6_GOOD_PACKETS; /* 824, Good Received RxIPv6 Packets Count Register*/
    ETH_RXIPV6_HEADER_ERROR_PACKETS
    RXIPV6_HEADER_ERROR_PACKETS;                             /* 828, Received IPv6 Header Error Packets Count Register*/
    ETH_RXIPV6_NO_PAYLOAD_PACKETS RXIPV6_NO_PAYLOAD_PACKETS; /* 82C, Received IPv6 No Payload Packets Count Register*/
    ETH_RXUDP_GOOD_PACKETS RXUDP_GOOD_PACKETS;               /* 830, Good Received UDP Packets Count Register*/
    ETH_RXUDP_ERROR_PACKETS RXUDP_ERROR_PACKETS;             /* 834, Received UDP Error Packets Count Register*/
    ETH_RXTCP_GOOD_PACKETS RXTCP_GOOD_PACKETS;               /* 838, Good Received TCP Packets Count Register*/
    ETH_RXTCP_ERROR_PACKETS RXTCP_ERROR_PACKETS;             /* 83C, Received TCP Error Packets Count Register*/
    ETH_RXICMP_GOOD_PACKETS RXICMP_GOOD_PACKETS;             /* 840, Good Received ICMP Packets Count Register*/
    ETH_RXICMP_ERROR_PACKETS RXICMP_ERROR_PACKETS;           /* 844, Received ICMP Error Packets Count Register*/
    ureg32 RESERVED_848[2];                                   /* 848, internal Reserved */
    ETH_RXIPV4_GOOD_OCTETS RXIPV4_GOOD_OCTETS;               /* 850, Good Received IPV4 Octets Count Register*/
    ETH_RXIPV4_HEADER_ERROR_OCTETS
    RXIPV4_HEADER_ERROR_OCTETS;                            /* 854, Received IPV4 Header Error Octets Count Register*/
    ETH_RXIPV4_NO_PAYLOAD_OCTETS RXIPV4_NO_PAYLOAD_OCTETS; /* 858, Received IPV4 No Payload Octets Count Register*/
    ETH_RXIPV4_FRAGMENTED_OCTETS RXIPV4_FRAGMENTED_OCTETS; /* 85C, Received IPV4 Fragmented Octets Count Register*/
    ETH_RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS
    RXIPV4_UDP_CHECKSUM_DISABLE_OCTETS;        /* 860, Received IPV4 UPD Checksum Disabled Octets Count Register*/
    ETH_RXIPV6_GOOD_OCTETS RXIPV6_GOOD_OCTETS; /* 864, Good Received IPV6 Octets Count Register*/
    ETH_RXIPV6_HEADER_ERROR_OCTETS
    RXIPV6_HEADER_ERROR_OCTETS;                            /* 868, Received IPV6 Header Error Octets Count Register*/
    ETH_RXIPV6_NO_PAYLOAD_OCTETS RXIPV6_NO_PAYLOAD_OCTETS; /* 86C, Received IPV6 No Payload Octets Count Register*/
    ETH_RXUDP_GOOD_OCTETS RXUDP_GOOD_OCTETS;               /* 870, Good Received UDP Octets Count Register*/
    ETH_RXUDP_ERROR_OCTETS RXUDP_ERROR_OCTETS;             /* 874, Received UDP Error Octets Count Register*/
    ETH_RXTCP_GOOD_OCTETS RXTCP_GOOD_OCTETS;               /* 878, Good Received TCP Octets Count Register*/
    ETH_RXTCP_ERROR_OCTETS RXTCP_ERROR_OCTETS;             /* 87C, Received TCP Error Octets Count Register*/
    ETH_RXICMP_GOOD_OCTETS RXICMP_GOOD_OCTETS;             /* 880, Good Received ICMP Octets Count Register*/
    ETH_RXICMP_ERROR_OCTETS RXICMP_ERROR_OCTETS;           /* 884, Received ICMP Error Octets Count Register*/
    ureg32 RESERVED_888[6];                                /* 888, internal Reserved */
    /* FPE */
    ETH_MMC_FPE_TX_INTERRUPT MMC_FPE_TX_INTERRUPT;                       /* 8a0, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ETH_MMC_FPE_TX_INTERRUPT_MASK MMC_FPE_TX_INTERRUPT_MASK;             /* 8a4, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ETH_MMC_TX_FPE_FRAGMENT_CNTR MMC_TX_FPE_FRAGMENT_CNTR;               /* 8a8, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ETH_MMC_TX_HOLD_REQ_CNTR MMC_TX_HOLD_REQ_CNTR;                       /* 8ac, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_8B0[4];                                              /* 8b0, internal Reserved*/
    ETH_MMC_FPE_RX_INTERRUPT MMC_FPE_RX_INTERRUPT;                       /* 8c0, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ETH_MMC_FPE_RX_INTERRUPT_MASK MMC_FPE_RX_INTERRUPT_MASK;             /* 8c4, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ETH_MMC_RX_PACKET_ASSEMBLY_ERR_CNTR MMC_RX_PACKET_ASSEMBLY_ERR_CNTR; /* 8c8, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ETH_MMC_RX_PACKET_SMD_ERR_CNTR MMC_RX_PACKET_SMD_ERR_CNTR;           /* 8cc, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ETH_MMC_RX_PACKET_ASSEMBLY_OK_CNTR MMC_RX_PACKET_ASSEMBLY_OK_CNTR;   /* 8d0, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ETH_MMC_RX_FPE_FRAGMENT_CNTR MMC_RX_FPE_FRAGMENT_CNTR;               /* 8d4, THA6206 and THA6412 are supported,
                                                                           but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_8D8[102];                                             /* 8d8, internal Reserved */
    ETH_MAC_INDIR_ACCESS_CTRL MAC_INDIR_ACCESS_CTRL;             /* A70, Indirect access control and status register */
    ETH_MAC_INDIR_ACCESS_DATA MAC_INDIR_ACCESS_DATA;             /* A74, Indirect access data register */
    ETH_MAC_PCTH_INTR_ENABLE MAC_PCTH_INTR_ENABLE;               /* A78, Threshold for policing counters, THA6206 and THA6412
                                                                  are supported, but THA6104 is not supported(RESERVED) */
    ETH_MAC_PCTH_INTR_STATUS MAC_PCTH_INTR_STATUS;               /* A7C, Threshold for policing counters, THA6206 and THA6412
                                                                  are supported, but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_A80[8];                                      /* a80, internal Reserved */
    ETH_MAC_PCTW_INTR_ENABLE MAC_PCTW_INTR_ENABLE;               /* AA0, Enable bits for time based interrupt, THA6206 and THA6412
                                                                  are supported, but THA6104 is not supported(RESERVED) */
    ETH_MAC_PCTW_INTR_STATUS MAC_PCTW_INTR_STATUS;               /* AA4, Time window based interrupt status, THA6206 and THA6412
                                                                  are supported, but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_AA8[22];                                     /* AA8, internal Reserved */
    ETH_MAC_TIMESTAMP_CONTROL MAC_TIMESTAMP_CONTROL;             /* B00, MAC Timestamp Control Register*/
    ETH_MAC_SUB_SECOND_INCREMENT MAC_SUB_SECOND_INCREMENT;       /* B04, MAC Sub-Second Increment Register*/
    ETH_MAC_SYSTEM_TIME_SECONDS MAC_SYSTEM_TIME_SECONDS;         /* B08, MAC System Time Seconds Register*/
    ETH_MAC_SYSTEM_TIME_NANOSECONDS MAC_SYSTEM_TIME_NANOSECONDS; /* B0C, MAC System Time Nanoseconds Register*/
    ETH_MAC_SYSTEM_TIME_SECONDS_UPDATE MAC_SYSTEM_TIME_SECONDS_UPDATE; /* B10, MAC System Time Seconds Update Register*/
    ETH_MAC_SYSTEM_TIME_NANOSECONDS_UPDATE MAC_SYSTEM_TIME_NANOSECONDS_UPDATE; /* B14, MAC System Time Nanoseconds Update Register*/
    ETH_MAC_TIMESTAMP_ADDEND MAC_TIMESTAMP_ADDEND; /* B18, MAC Timestamp Addend Register*/
    ETH_MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS
    MAC_SYSTEM_TIME_HIGHER_WORD_SECONDS;                 /* B1C, MAC System Time Higher Word Seconds Register*/
    ETH_MAC_TIMESTAMP_STATUS MAC_TIMESTAMP_STATUS;       /* B20, MAC Timestamp Status Register*/
    ETH_MAC_RX_DOMAIN_TIME_INCR MAC_RX_DOMAIN_TIME_INCR; /* B24, THE Increment value of PTP time in RX clock */
    ETH_MAC_TX_DOMAIN_TIME_INCR MAC_TX_DOMAIN_TIME_INCR; /* B28, THE Increment value of PTP time in TX clock */
    ureg32 RESERVED_B2C;                               /* B2C, internal Reserved */
    ETH_MAC_TX_TIMESTAMP_STATUS_NANOSECONDS
    MAC_TX_TIMESTAMP_STATUS_NANOSECONDS; /* B30, MAC Transmit Timestamp Nanoseconds Status Register*/
    ETH_MAC_TX_TIMESTAMP_STATUS_SECONDS
    MAC_TX_TIMESTAMP_STATUS_SECONDS; /* B34, MAC Transmit Timestamp Seconds Status Register*/
    ureg32 RESERVED_B38[6];          /* B38, internal Reserved */

    ETH_MAC_TIMESTAMP_INGRESS_ASYM_CORR
    MAC_TIMESTAMP_INGRESS_ASYM_CORR; /* B50, MAC Timestamp Ingress Asymmetry Correction Register.*/
    ETH_MAC_TIMESTAMP_EGRESS_ASYM_CORR
    MAC_TIMESTAMP_EGRESS_ASYM_CORR; /* B54, MAC Timestamp Egress Asymmetry Correction Register.*/
    ETH_MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND
    MAC_TIMESTAMP_INGRESS_CORR_NANOSECOND; /* B58, MAC Timestamp Ingress Correction Nanoseconds Register.*/
    ETH_MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND
    MAC_TIMESTAMP_EGRESS_CORR_NANOSECOND; /* B5C, MAC Timestamp Egress Correction Nanoseconds Register.*/
    ETH_MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC
    MAC_TIMESTAMP_INGRESS_CORR_SUBNANOSEC; /* B60, MAC Timestamp Ingress Correction Subnanoseconds Register,A6
                                              RESERVED.*/
    ETH_MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC
    MAC_TIMESTAMP_EGRESS_CORR_SUBNANOSEC; /* B64, MAC Timestamp Egress Correction Subnanoseconds Register,A6
                                             RESERVED.*/
    ETH_MAC_TIMESTAMP_INGRESS_LATENCY MAC_TIMESTAMP_INGRESS_LATENCY; /* B68, MAC Timestamp Ingress latency Register*/
    ETH_MAC_TIMESTAMP_EGRESS_LATENCY MAC_TIMESTAMP_EGRESS_LATENCY;   /* B6c, MAC Timestamp Egress latency Register*/

    ETH_MAC_PPS_CONTROL MAC_PPS_CONTROL; /* B70, MAC PPS Control Register*/
    ureg32 RESERVED_B74[3];              /* B74, internal Reserved */

    ETH_MAC_PPS0_TARGET_TIME_SECONDS MAC_PPS0_TARGET_TIME_SECONDS; /* B80, MAC PPS 0 Target Time Seconds Register*/
    ETH_MAC_PPS0_TARGET_TIME_NANOSECONDS
    MAC_PPS0_TARGET_TIME_NANOSECONDS;                              /* B84, MAC PPS 0 Target Time Nanoeconds Register*/
    ETH_MAC_PPS0_INTERVAL MAC_PPS0_INTERVAL;                       /* B88, MAC PPS 0 Interval Register*/
    ETH_MAC_PPS0_WIDTH MAC_PPS0_WIDTH;                             /* B8C, MAC PPS 0 Width Register*/
    ETH_MAC_PPS0_TARGET_TIME_SECONDS MAC_PPS1_TARGET_TIME_SECONDS; /* B90, MAC PPS 1 Target Time Seconds Register*/
    ETH_MAC_PPS0_TARGET_TIME_NANOSECONDS
    MAC_PPS1_TARGET_TIME_NANOSECONDS;                              /* B94, MAC PPS 1 Target Time Nanoeconds Register*/
    ETH_MAC_PPS0_INTERVAL MAC_PPS1_INTERVAL;                       /* B98, MAC PPS 1 Interval Register*/
    ETH_MAC_PPS0_WIDTH MAC_PPS1_WIDTH;                             /* B9C, MAC PPS 1 Width Register*/
    ETH_MAC_PPS0_TARGET_TIME_SECONDS MAC_PPS2_TARGET_TIME_SECONDS; /* Ba0, MAC PPS 2 Target Time Seconds Register, THA6206 and
                                                                    THA6412 are supported, but THA6104 is not supported(RESERVED)*/
    ETH_MAC_PPS0_TARGET_TIME_NANOSECONDS
    MAC_PPS2_TARGET_TIME_NANOSECONDS;                              /* Ba4, MAC PPS 2 Target Time Nanoeconds Register,THA6206 and
                                                                    THA6412 are supported, but THA6104 is not supported(RESERVED)*/
    ETH_MAC_PPS0_INTERVAL MAC_PPS2_INTERVAL;                       /* Ba8, MAC PPS 2 Interval Register, THA6206 and
                                                                    THA6412 are supported, but THA6104 is not supported(RESERVED)*/
    ETH_MAC_PPS0_WIDTH MAC_PPS2_WIDTH;                             /* BaC, MAC PPS 2 Width Register, THA6206 and
                                                                    THA6412 are supported, but THA6104 is not supported(RESERVED)*/
    ETH_MAC_PPS0_TARGET_TIME_SECONDS MAC_PPS3_TARGET_TIME_SECONDS; /* Bb0, MAC PPS 3 Target Time Seconds Register, THA6206 and
                                                                    THA6412 are supported, but THA6104 is not supported(RESERVED)*/
    ETH_MAC_PPS0_TARGET_TIME_NANOSECONDS
    MAC_PPS3_TARGET_TIME_NANOSECONDS;                        /* Bb4, MAC PPS 3 Target Time Nanoeconds Register, THA6206 and
                                                              THA6412 are supported, but THA6104 is not supported(RESERVED)*/
    ETH_MAC_PPS0_INTERVAL MAC_PPS3_INTERVAL;                 /* Bb8, MAC PPS 3 Interval Register, THA6206 and
                                                              THA6412 are supported, but THA6104 is not supported(RESERVED)*/
    ETH_MAC_PPS0_WIDTH MAC_PPS3_WIDTH;                       /* BbC, MAC PPS 3 Width Register, THA6206 and
                                                              THA6412 are supported, but THA6104 is not supported(RESERVED)*/
    ETH_MAC_PTO_CONTROL MAC_PTO_CONTROL;                     /* Bc0, PTP offload engine operation */
    ETH_MAC_SOURCE_PORT_IDENTITY0 MAC_SOURCE_PORT_IDENTITY0; /* Bc4, Bits[31:0]of the 80-bit source port identity */
    ETH_MAC_SOURCE_PORT_IDENTITY1 MAC_SOURCE_PORT_IDENTITY1; /* Bc8, Bits[63:32]of the 80-bit source port identity */
    ETH_MAC_SOURCE_PORT_IDENTITY2 MAC_SOURCE_PORT_IDENTITY2; /* Bcc, Bits[79:64]of the 80-bit source port identity */
    ETH_MAC_LOG_MESSAGE_INTERVAL MAC_LOG_MESSAGE_INTERVAL;   /* BD0, Periodic intervals for PTP packet generation */
    ureg32 RESERVED_BD4[11];                                  /* BD4, internal Reserved */

    /* MTL Registers  */
    ETH_MTL_OPERATION_MODE MTL_OPERATION_MODE; /* C00, MTL Operation Mode Register*/
    ureg32 RESERVED_C04;                     /* C04, internal Reserved,RESERVED.*/
    /* FIFO Debug */
    ETH_MTL_DBG_CTL MTL_DBG_CTL;                   /* C08, MTL  Register*/
    ETH_MTL_DBG_STS MTL_DBG_STS;                   /* C0c, MTL  Register*/
    ETH_MTL_FIFO_DEBUG_DATA MTL_FIFO_DEBUG_DATA;   /* C10, MTL  Register*/
    ureg32 RESERVED_C14[3];                        /* C14, internal Reserved */
    ETH_MTL_INTERRUPT_STATUS MTL_INTERRUPT_STATUS; /* C20, MTL Interrupt Status Register*/
    ureg32 RESERVED_C24[3];                        /* C24, internal Reserved */
    ETH_MTL_RXQ_DMA_MAP0 MTL_RXQ_DMA_MAP0;         /* C30, MTL Receive Queue and DMA Channel Mapping 0 Register*/
    ureg32 RESERVED_C34[3];              /* C34, MTL Receive Queue and DMA Channel Mapping 1 Register,RESERVED.*/
    ETH_MTL_TBS_CTRL MTL_TBS_CTRL;       /* C40, Control Time Based Scheduling, THA6206 and
                                           THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_C44[3];              /* C44, AT2202 RESERVED.*/
    ETH_MTL_EST_CONTROL MTL_EST_CONTROL; /* C50, Control the operation of EST, THA6206 and
                                           THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_EST_EXT_CONTROL MTL_EST_EXT_CONTROL;           /* C54, Control the operation of EST, THA6206 and
                                                             THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_EST_STATUS MTL_EST_STATUS;                     /* C58, Status related to EST, THA6206 and
                                                             THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_C5C;                                 /* C5C, AT2202 RESERVED.*/
    ETH_MTL_EST_SCH_ERROR MTL_EST_SCH_ERROR;               /* C60, One hot encoded queue numbers, THA6206 and
                                                            THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_EST_FRM_SIZE_ERROR MTL_EST_FRM_SIZE_ERROR;     /* C64, One hot encoded queue numbers, THA6206 and
                                                            THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_EST_FRM_SIZE_CAPTURE MTL_EST_FRM_SIZE_CAPTURE; /* C68, Capture the frame size and queue number, THA6206 and
                                                            THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_C6C;                                 /* C6C, AT2202 RESERVED.*/
    ETH_MTL_EST_INTR_ENABLE MTL_EST_INTR_ENABLE;           /* C70, Interrupt enable for EST, THA6206 and
                                                            THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_C74[3];                                /* C74, AT2202 RESERVED.*/
    ETH_MTL_EST_GCL_CONTROL MTL_EST_GCL_CONTROL;           /* C80, Control to read or write the GCL, THA6206 and
                                                            THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_EST_GCL_DATA MTL_EST_GCL_DATA;                 /* C84, The data of read or write the GCL */
    ureg32 RESERVED_C88[2];                                 /* C88, AT2202 RESERVED.*/
    ETH_MTL_FPE_CTRL_STS MTL_FPE_CTRL_STS;                 /* C90, Control and status of Frame preemption, THA6206 and
                                                            THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_FPE_ADVANCE MTL_FPE_ADVANCE;                   /* C94, Hold the hold and release advance time, THA6206 and
                                                            THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_C98[2];                                 /* C98, AT2202 RESERVED.*/
    ETH_MTL_RXP_CONTROL_STATUS MTL_RXP_CONTROL_STATUS;     /* CA0, Rx parser, THA6206 and THA6412 are supported,
                                                            but THA6104 is not supported(RESERVED) */
    ETH_MTL_RXP_INTERRUPT_CONTROL_STATUS
    MTL_RXP_INTERRUPT_CONTROL_STATUS;        /* CA4, Provide enable control for interrupt, THA6206 and
                                              THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_RXP_DROP_CNT MTL_RXP_DROP_CNT;   /* CA8, Provide the drop count of Rx Parser initiated drops, THA6206 and
                                              THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_RXP_ERROR_CNT MTL_RXP_ERROR_CNT; /* CAC, Provide the related error count of Rx Parser, THA6206 and
                                              THA6412 are supported, but THA6104 is not supported(RESERVED) */

    ETH_MTL_RXP_INDIRECT_ACC_CONTROL_STATUS
    MTL_RXP_INDIRECT_ACC_CONTROL_STATUS;                     /* CB0, Indirect access control and status, THA6206 and THA6412
                                                              are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_RXP_INDIRECT_ACC_DATA MTL_RXP_INDIRECT_ACC_DATA; /* CB4, Data associated to indirect access to Rx Parser, THA6206
                                                              and THA6412 are supported, but THA6104 is not supported(RESERVED) */
    ETH_MTL_RXP_BYPASS_CNT MTL_RXP_BYPASS_CNT;               /* CB8, Bypass count of Rx Parser, THA6206 and THA6412 are supported,
                                                              but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_CBC;                                   /* CBC, AT2202 RESERVED.*/
    ETH_MTL_ECC_CTL MTL_ECC_CTL;                             /* CC0, ECC control*/
    ETH_MTL_SAFTEY_INTERRUPR_STATUS MTL_SAFTEY_INTERRUPR_STATUS; /* CC4, Safety interrupt status*/
    ETH_MTL_ECC_INTERRUPT_ENABLE MTL_ECC_INTERRUPT_ENABLE;       /* CC8, ECC interrupts enable*/
    ETH_MTL_ECC_INTERRUPT_STATUS MTL_ECC_INTERRUPT_STATUS;       /* CCC, ECC interrupts status*/
    ETH_MTL_ECC_ERR_STS_RCTL MTL_ECC_ERR_STS_RCTL; /* Cd0, ECC Establishes the control for ecc error status capture*/
    ETH_MTL_ECC_ERR_ADDR_STATUS
    MTL_ECC_ERR_ADDR_STATUS; /* Cd4, ECC memory addresses for the correctable and uncorrectable*/
    ETH_MTL_ECC_ERR_CNTR_STATUS MTL_ECC_ERR_CNTR_STATUS; /* Cd8, ECC Error count for Correctable and uncorrectable*/
    ureg32 RESERVED_CDC;                               /* Cdc, internal Reserved , MTL_RXQ_DMA_MAP1 when queue>4*/

    ETH_MTL_DPP_CONTROL MTL_DPP_CONTROL; /* Ce0, Data parity protection and error */
    ETH_MTL_DPP_ECC_EIC MTL_DPP_ECC_EIC; /* Ce4, ECC/DPP error injection */
    ureg32 RESERVED_CE8[6];              /* Ce8, internal Reserved */

    /* MTL_Q0 Registers */
    ETH_MTL_TXQ0 MTL_TXQ0;  /* D00-D18, MTL Queue 0 Transmit Quantum or Weights Register, multi-registers */
    ureg32 RESERVED_D1C[4]; /* D1C, internal Reserved */
    ETH_MTL_Q0 MTL_Q0;      /* D2C, MTL Queue 0 Interrupt Control Status Register*/
    ETH_MTL_RXQ0 MTL_RXQ0;  /* D30, MTL Queue 0 Receive Control Register*/

    /* MTL_Q1 Registers */
    ETH_MTL_TXQ MTL_TXQ1;    /* D40, <==(0x40 * 1) + 0xD00*/
    ureg32 RESERVED_D68;   /* D68, internal Reserved */
    ETH_MTL_Q MTL_Q1;        /* D6C, <== (0x40*1) + D2c*/
    ETH_MTL_RXQ MTL_RXQ1;    /* D70, <== (0x40*1) + D30*/
    ETH_MTL_TXQ MTL_TXQ2;    /* D80, <==(0x40 * 2) + 0xD00, THA6206 and THA6412 are supported, but THA6104 is
                              not supported(RESERVED) */
    ureg32 RESERVED_DA8;   /* DA8, internal Reserved */
    ETH_MTL_Q MTL_Q2;        /* DAC,<== (0x40*2) + D2c, THA6206 and THA6412 are supported, but THA6104 is
                              not supported(RESERVED) */
    ETH_MTL_RXQ MTL_RXQ2;    /* DB0,  <== (0x40*2) + D30, THA6206 and THA6412 are supported, but THA6104 is
                              not supported(RESERVED)*/
    ETH_MTL_TXQ MTL_TXQ3;    /* DC0, <==(0x40 * 3) + 0xD00, THA6206 and THA6412 are supported, but THA6104 is
                              not supported(RESERVED)*/
    ureg32 RESERVED_DE8;   /* DE8, internal Reserved */
    ETH_MTL_Q MTL_Q3;        /* DEC, <== (0x40*3) + D2c, THA6206 and THA6412 are supported, but THA6104 is
                              not supported(RESERVED)*/
    ETH_MTL_RXQ MTL_RXQ3;    /* DF0,  <== (0x40*3) + D30, THA6206 and THA6412 are supported, but THA6104 is
                              not supported(RESERVED)*/
    ureg32 RESERVED_E00[128]; /* E00, internal Reserved */

    /* DMA Registers  */
    ETH_DMA_MODE DMA_MODE;                         /* 1000, DMA Bus Mode Register*/
    ETH_DMA_SYSBUS_MODE DMA_SYSBUS_MODE;           /* 1004, DMA System Bus Mode Register*/
    ETH_DMA_INTERRUPT_STATUS DMA_INTERRUPT_STATUS; /* 1008, DMA Interrupt Status Register*/
    ETH_DMA_DEBUG_STATUS0 DMA_DEBUG_STATUS0;       /* 100C, DMA Debug Status 0 Register*/
    ETH_DMA_DEBUG_STATUS1 DMA_DEBUG_STATUS1;       /* 1010, DMA Debug Status 1 Register, THA6206 and THA6412 are supported,
                                                    but THA6104 is not supported(RESERVED)*/
    ureg32 RESERVED_1014[3];                       /* 1014, internal Reserved , DMA_DEBUG_STATUS2 when DMA channel>4*/
    ETH_AXI4_TX_AR_ACE_CONTROL AXI4_TX_AR_ACE_CONTROL;         /*1020, AXI4_TX_AR_ACE_CONTROL*/
    ETH_AXI4_RX_AW_ACE_CONTROL AXI4_RX_AW_ACE_CONTROL;         /*1024, AXI4_RX_AW_ACE_CONTROL*/
    ETH_AXI4_TXRX_AWAR_ACE_CONTROL AXI4_TXRX_AWAR_ACE_CONTROL; /*1028, AXI4_RX_AW_ACE_CONTROL*/
    ureg32 RESERVED_102C[5]; /* 102C, internal Reserved , DMA_DEBUG_STATUS2 when DMA channel>4*/
    ETH_AXI_LPI_ENTRY_INTERVAL AXI_LPI_ENTRY_INTERVAL;           /* 1040, Control the AXI LPI entry interval*/
    ureg32 RESERVED_1044[3];                                     /* 1044, internal Reserved*/
    ETH_DMA_TBS_CRTL DMA_TBS_CRTL0;                              /* 1050, Control TBS attributes, THA6206 and THA6412 are supported,
                                                                  but THA6104 is not supported(RESERVED) */
    ETH_DMA_TBS_CRTL DMA_TBS_CRTL1;                              /* 1054, Control TBS attributes, THA6206 and THA6412 are supported,
                                                                  but THA6104 is not supported(RESERVED) */
    ETH_DMA_TBS_CRTL DMA_TBS_CRTL2;                              /* 1058, Control TBS attributes, THA6206 and THA6412 are supported,
                                                                  but THA6104 is not supported(RESERVED) */
    ETH_DMA_TBS_CRTL DMA_TBS_CRTL3;                              /* 105C, Control TBS attributes, THA6206 and THA6412 are supported,
                                                                  but THA6104 is not supported(RESERVED) */
    ureg32 RESERVED_1060[8];                                     /* 1060, internal Reserved*/
    ETH_DMA_SAFETY_INTERRUPT_STATUS DMA_SAFETY_INTERRUPT_STATUS; /* 1080, Control the AXI LPI entry interval*/
    ureg32 RESERVED_1084[31];                                    /* 1084, internal Reserved*/
    ETH_DMA_CH DMA_CH[4];                                        /* 1100, DMA Channel, THA6206 and THA6412 support 4 Tx channels,
                                                                  while THA6104 supports 2 Tx channels*/
    ureg32 RESERVED_1300[833];                                   /* 1300, internal Reserved */

    /* External Registers */
    ETH_MIR MIR;               /* 2004, Module Identification Register */
    ETH_GPCTL GPCTL;           /* 2008, General Purpose Control Register*/
    ureg32 RESERVED_200C[13];  /* 200C, internal Reserved */
    ETH_SKEWCTL SKEWCTL;       /* 2040, Skew Control Register, THA6206 and THA6412 are supported,
                               but THA6104 is not supported*/
    ETH_PHY_TXCTL PTR;         /* 2044, RGMII phy_txctl_o, THA6206 is supported,
                               but THA6104 and THA6412 are not supported*/
    ETH_PPS_REGISTER EPR;      /* 2048, geth_pps work mode, */
    ETH_LPMR LPMR;             /* 204C, Low power mode register */
    ETH_EAR EAR;               /* 2050, ALAM register */
    ETH_EAER EAER;             /* 2054, ALAM EN register */
    ETH_EACR EACR;             /* 2058, ALAM CLEAN register */
    ETH_EFSIMDR EFSIMDR;       /* 205C, Functional safety injection detects */
    ETH_EIR EIR;               /* 2060, INTR register */
    ETH_EIER EIER;             /* 2064, INTR EN register */
    ETH_EICR EICR;             /* 2068, INTR CLEAN register */
    ETH_AHBEMR AHBEMR;         /* 206C, AHBEMR register */
    ETH_XCVRENR XCVRENR;       /* 2070, XCVRENR register, THA6104 is supported,
                               but THA6206 and THA6412 are not supported */
} ETH_MODULE;

#endif /* ETH_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    sent_register.h
 * Author:      01321
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of SENT module registers.
 *********************************************************************************************************************/
#ifndef SENT_REGISTER_H_
#define SENT_REGISTER_H_

/*
*#Violation Summary
*#sent_regiter_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
*#sent_regiter_h_REF_2:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#sent_regiter_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
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
 *                                        SENT Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* CSENT Receive Configuration Register */
typedef volatile struct
{
    ureg32 RX_ENB:1;                   /* [0:0] enable receive (rw) */
    ureg32 RX_CRCENB:1;                /* [1:1] enable crc calculation (rw) */
    ureg32 RX_IDLEPOL:1;               /* [2:2] The idle polarity of received data (rw) */
    ureg32 RX_PPENB:1;                 /* [3:3] Indicates that Pause Pulse will be expected after the crc if this is enabled (rw) */
    ureg32 RX_SPCENB:1;                /* [4:4] the receiver will generate a pulse with the width programmed in SPCMTP (rw) */
    ureg32 RX_DNIB:3;                  /* [7:5] Indicates the number of data nibbles should be expected (rw) */
    ureg32 RX_SPCMTP:8;                /* [15:8] Specifies the SPC Master Trigger Pulse width in TT unit. (rw) */
    ureg32 SPC_MODE:1;                 /* [16:16] It indicate the CSENT receiver is in Short PWM Protocal mode. */
    ureg32 RX_CRC_WITH_STATUS:1;       /* [17:17] The receiver will not check the CRC of the slow channel if this SLOW_CRCD is set to 1(rw) */
    ureg32 RX_CRCTYPE:1;               /* [18:18] Specifies the crc type (rw) */
    ureg32 RX_SYNC_RST:1;              /* [19:19] the SYNCTT count will be reset when SYNC_RST is set to '1'  (rw) */
    ureg32 TTCLK_SPC:12;               /* [31:20] Specifies the tick time for the SPC Master Trigger Pulse */
} SENT_RCFG_Bits;

/* Receiver FAST Channel Data Register */
typedef volatile struct
{
    ureg32 CRC:4;                      /* [3:0] Specifies CRC of fast channel data (r) */
    ureg32 DATA6:4;                    /* [7:4] Specifies DATA6 of fast channel data (r) */
    ureg32 DATA5:4;                    /* [11:8] Specifies DATA5 of fast channel data (r) */
    ureg32 DATA4:4;                    /* [15:12] Specifies DATA4 of fast channel data (r) */
    ureg32 DATA3:4;                    /* [19:16] Specifies DATA3 of fast channel data (r) */
    ureg32 DATA2:4;                    /* [23:20] Specifies DATA2 of fast channel data (r) */
    ureg32 DATA1:4;                    /* [27:24] Specifies DATA1 of fast channel data (r) */
    ureg32 STAT:4;                     /* [31:28] Specifies Status of fast channel data  */
} SENT_RFDATA_Bits;

/* Receiver SLOW Channel Data Register - short serial message data */
typedef volatile struct 
{
    ureg32 CRC:4;                      /* [3:0] CRC (r) */
    ureg32 reserved_4:3;               /* [6:4] internal Reserved */
    ureg32 C:1;                        /* [7:7] Configuration bit (r) */
    ureg32 DATA:8;                     /* [15:8] DATA (r) */
    ureg32 reserved_16:8;              /* [23:16] internal Reserved */
    ureg32 MSGID:4;                    /* [27:24] Message ID (r) */
    ureg32 reserved_28:4;              /* [31:28] internal Reserved */
} SENT_RSDATA_SHORT_Bits;

/* Receiver SLOW Channel Data Register - enhanced 12-bit serial message data */
typedef volatile struct
{
    ureg32 CRC:6;                      /* [5:0] CRC (r) */
    ureg32 reserved_4:1;               /* [6:6] Reserved */
    ureg32 C:1;                        /* [7:7] C (r) */
    ureg32 DATA:12;                    /* [19:8] DATA (r) */
    ureg32 reserved_20:4;              /* [23:20] Reserved */
    ureg32 MSGID:8;                    /* [31:24] Message ID (r) */    
} SENT_RSDATA_ENHANCE12_Bits;

/* Receiver SLOW Channel Data Register - enhanced 16-bit serial message data */
typedef volatile struct 
{
    ureg32 CRC:6;                      /* [5:0] CRC (r) */
    ureg32 reserved_4:1;               /* [6:6] Reserved */
    ureg32 C:1;                        /* [7:7] C (r) */
    ureg32 DATA:16;                    /* [23:8] DATA (r) */
    ureg32 MSGID:4;                    /* [27:24] Message ID (r) */
    ureg32 reserved_28:4;              /* [31:28] Reserved */
} SENT_RSDATA_ENHANCE16_Bits;

/* Receiver Status Register */
typedef volatile struct
{
    ureg32 RXNIB:3;                    /* [2:0] Specifies the length of the received nibbles (r) */
    ureg32 PP:1;                       /* [3:3] Specifies whether pause pulse is received */
    ureg32 RX_CRCERR:1;                /* [4:4] Specifies the status of CRC error (r) */
    ureg32 RX_FRMERR:1;                /* [5:5] Specifies the status of frame error (r) */
    ureg32 RXSLOW_CRCERR:1;            /* [6:6] Specifies the status of CRC error in the received slow channel data (r) */
    ureg32 RXSLOW_FORMATERR:1;         /* [7:7] Specifies the status of frame error in the received slow channel data (r) */
    ureg32 RXSLOW_ST:5;                /* [12:8] Specifies the receiving status of the slow channel data during through Status and Communication nibble (r) */
    ureg32 RXSLOW_DN:1;                /* [13:13] When it is set, it indicates that the receiving of the slow channel serial message is done (r) */
    ureg32 RXFAST_DN:1;                /* [14:14] When it is set, it indicates that the receiving of the fast channel serial message is done (r) */
    ureg32 RX_SYNC:1;                  /* [15:15] When it is set, it indicates that SENT receive a valid synchronization period (r) */
    ureg32 RX_TTCLK:16;                /* [31:16] Specifies the most recent synchronization tick time calculation in clocks (r) */
} SENT_RSTAT_Bits;

/* Receiver Synchronous Register */
typedef volatile struct
{
    ureg32 RSYNC_MIN:16;               /* [15:0] Specifies the Minimum number of clocks in a tick as resulting from the sync pulse (rw) */
    ureg32 RSYNC_MAX:16;               /* [31:16] Specifies the Maximum number of clocks in a tick as resulting from the sync pulse (rw) */
} SENT_RSYNC_Bits;

/* Mode Select Register */
typedef volatile struct
{
    ureg32 MODE:1;                     /* [0:0] Specifies the trigger method (rw) */
    ureg32 reserved_1:15;              /* [15:1] Reserved */
    ureg32 EXTREGBYPS:1;               /* [16:16] Enable/Disable the External register access (rw) */
    ureg32 reserved_17:15;             /* [31:17] Reserved */
}SENT_MSEL_Bits;

/* Trigger timeout */
typedef volatile struct
{
    ureg32 TB:26;                      /* [25:0] Timeout Boundary (rw) */
    ureg32 reserved_26:6;              /* [31:26] Reserved */
}SENT_TTMOUT_Bits;

/* External State */
typedef volatile struct
{
    ureg32 DATAMIS:1;                  /* [0:0] Data Missing (r) */
    ureg32 DATAREC:1;                  /* [1:1] Data Received (r) */
    ureg32 reserved_2:30;              /* [31:2] Reserved */
}SENT_EXTSTAT_Bits;

/* External Trigger Configuration Register */
typedef volatile struct
{
    ureg32 EXTTR:15;                   /* [14:0] Enable/Disable gtm_trigger_i[14:0] (rw) */
    ureg32 reserved_15:17;             /* [31:15] Reserved */
}SENT_ETCFG_Bits;

/* Receiver Status Register 2 */
typedef volatile struct
{
    ureg32 SP25E:1;                    /* [0:0] Sync pulse width error (r) */
    ureg32 SP15625E:1;                 /* [1:1] Width error between two consecutive sync pulses (r) */
    ureg32 reserved_2:30;              /* [31:2] Reserved */
} SENT_RSTAT2_Bits;

/* Interrupt Mask Register */
typedef volatile struct
{
    ureg32 VLDMASK:1;                  /* [0:0] Data reception valid interrupt mask (r) */
    ureg32 ERRMASK:1;                  /* [1:1] Data reception error interrupt mask (r) */
    ureg32 reserved_2:30;              /* [31:2] Reserved */
} SENT_INTMASK_Bits;
/**********************************************************************************************************************
 *                                              SENT Register Definitions
 *********************************************************************************************************************/
/* Receiver Configuration Register */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                          /* Unsigned access */
    SENT_RCFG_Bits B;                  /* Bit-Field access */
} SENT_RCFG;

/* Receiver FAST Channel Data Register */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_RFDATA_Bits B;                 /* Bit-Field access */
} SENT_RFDATA;

/* Receiver SLOW Channel Data Register */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_RSDATA_SHORT_Bits B;           /* Bit-Field access */
    SENT_RSDATA_ENHANCE12_Bits E12;     /* Bit-Field access */
    SENT_RSDATA_ENHANCE16_Bits E16;     /* Bit-Field access */
} SENT_RSDATA;

/* Receiver Status Register */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_RSTAT_Bits B;                  /* Bit-Field access */
} SENT_RSTAT;

/* Receiver SYNC Register */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_RSYNC_Bits B;                  /* Bit-Field access */
} SENT_RSYNC;

/* Mode Select Register */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_MSEL_Bits B;                   /* Bit-Field access */
}SENT_MSEL;

/* Trigger timeout */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_TTMOUT_Bits B;                 /* Bit-Field access */
}SENT_TTMOUT;

/* External State */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_EXTSTAT_Bits B;                /* Bit-Field access */
}SENT_EXTSTAT;

/* External Trigger Configuration Register */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_ETCFG_Bits B;                  /* Bit-Field access */
}SENT_ETCFG;

/* Receiver Status Register 2 */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_RSTAT2_Bits B;                 /* Bit-Field access */
} SENT_RSTAT2;

/* Interrupt Mask Register */
typedef union
/* #Violation: sent_regiter_h_REF_1 */
{
    uint32 U;                           /* Unsigned access */
    SENT_INTMASK_Bits B;                /* Bit-Field access */
} SENT_INTMASK;
/**********************************************************************************************************************
 *                                        SENT Register Configuration Structure
 *********************************************************************************************************************/
/* SENT channel Register */
/* #Violation: sent_regiter_h_REF_2 */
/* #Violation: sent_regiter_h_REF_3 */
typedef volatile struct
{
    ureg32 RESERVED_0[5];               /* 0x0 Reserved */
    SENT_RSTAT2 RSTAT2;                 /* 0x14 Receiver Status Register 2, only support THA6104 */
    SENT_INTMASK INTMASK;               /* 0x18 Interrupt Mask Register, only support THA6104 */
    SENT_EXTSTAT EXTSTAT;               /* 0x1C External State */
    SENT_RCFG RCFG;                     /* 0x20 Receiver Configuration Register */
    SENT_RFDATA RFDATA;                 /* 0x24 Receiver Fast Channel Data Register/FIFO */
    SENT_RSDATA RSDATA;                 /* 0x28 Receive Slow Channel DAta Register */
    SENT_RSTAT RSTAT;                   /* 0x2C Receiver Status Register(for fast and slow channel) */
    SENT_RSYNC RSYNC;                   /* 0x30 Receiver Sync Min and Max */
    SENT_MSEL MSEL;                     /* 0x34 Mode Select */
    SENT_ETCFG ETCFG;                   /* 0x38 External Trigger Configuration */
    SENT_TTMOUT TTMOUT;                 /* 0x3C Trigger timeout */
} SENT_MODULE;

#endif /* SENT_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

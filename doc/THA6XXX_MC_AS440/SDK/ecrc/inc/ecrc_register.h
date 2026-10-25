/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    ecrc_register.h
 * Author:      01321
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of ECRC module registers.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#ecrc_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Union is used to define the registers type.
*
*/
 #ifndef ECRC_REGISTER_H_
#define ECRC_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        ECRC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Channel Status Register */
typedef volatile struct
{
    ureg32 CH0:1;  /* [0:0] Status of Channel 0 */
    ureg32 CH1:1;  /* [1:1] Status of Channel 1 */
    ureg32 CH2:1;  /* [2:2] Status of Channel 2 */
    ureg32 CH3:1;  /* [3:3] Status of Channel 3 */
    ureg32 CH4:1;  /* [4:4] Status of Channel 4 */
    ureg32 CH5:1;  /* [5:5] Status of Channel 5 */
    ureg32 CH6:1;  /* [6:6] Status of Channel 6 */
    ureg32 CH7:1;  /* [7:7] Status of Channel 7 */
    ureg32 reserved_8:24;   /* [31:8] Reserved */
} ECRC_CHSTR_Bits;

/* Module Reset Clear Register */
typedef volatile struct
{
    ureg32 CLR:1;    /* [0:0] Clear reset status */
    ureg32 reserved_1:31;   /* [31:1] Reserved */
} ECRC_MRSTCLR_Bits;

/* Module Reset Register 1 */
typedef volatile struct
{
    ureg32 RST:1;   /* [0:0] Reset request 1 */
    ureg32 reserved_1:31;   /* [31:1] Reserved */
} ECRC_MRSTR1_Bits;

/* Module Reset Register 0 */
typedef volatile struct
{
    ureg32 RST:1;           /* [0:0] Reset request 0 */
    ureg32 RSTST:1;            /* [1:1] Reset Status */
    ureg32 reserved_2:30;   /* [31:2] Reserved */
} ECRC_MRSTR0_Bits;

/* Channel Input Register i */
typedef volatile struct
{
    ureg32 INPUT:32;   /* [31:0] input data register */
} ECRC_CHIN_Bits;

/* Channel Result Register i */
typedef volatile struct
{
    ureg32 RESULT:32;  /* [31:0] result CRC register */
} ECRC_CHRES_Bits;

/* Channel Configuration Register i */
typedef volatile struct
{
    ureg32 CMI:1;  /* [0:0] CRC Mismatch Interrupt enable */
    ureg32 CFI:1;  /* [1:1] Configuration Fault Interrupt enable */
    ureg32 LFI:1;  /* [2:2] Length Fault Interrupt enable */
    ureg32 BFI:1;  /* [3:3] Bus Fault Interrupt enable */
    ureg32 CHKEN:1;    /* [4:4] CRC Check Comparison enable */
    ureg32 RELOAD:1;   /* [5:5] Automatic Length Reload enable */
    ureg32 reserved_6:2;   /* [7:6] Reserved */
    ureg32 BYTEREFIN:1;    /* [8:8] IR Byte wise Reflection IR */
    ureg32 BITREFOUT:1;    /* [9:9] CRC Bit Wise Reflect */
    ureg32 XOUT:1; /* [10:10] XOR out with final CRC 0xFFFFFFFF or 0x00000000 */
    ureg32 BYTESWAP:1; /* [11:11] Byte swap, change big ending or small ending */
    ureg32 reserved_12:4;  /* [15:12] Reserved */
    ureg32 KERNEL:4;   /* [19:16] Kernel CRC algorithm choose */
    ureg32 reserved_20:12; /* [31:20] Reserved */
} ECRC_CHCFG_Bits;

/* CRC Status Register i */
typedef volatile struct
{
    ureg32 CMST:1; /* [0:0] CRC Mismatch Status */
    ureg32 CFST:1; /* [1:1] Configuration Redundant Fault Status */
    ureg32 LFST:1; /* [2:2] Length Fault Status */
    ureg32 BFST:1; /* [3:3] Bus Fault Status */
    ureg32 FMICRC:1;   /* [4:4] Force Mismatch Interrupt CRC bit redundant error */
    ureg32 FMICFG:1;   /* [5:5] Force Mismatch Interrupt CFG bit redundant error */
    ureg32 FMICHK:1;   /* [6:6] Force Mismatch Interrupt CHK bit redundant error */
    ureg32 RESFLAG:1;    /* [7:7] Result flag */
    ureg32 reserved_8:24;  /* [31:8] Reserved */
} ECRC_CSR_Bits;

/* Channel Length Register i */
typedef volatile struct
{
    ureg32 LEN:16; /* [15:0] Message Length Register */
    ureg32 reserved_16:16; /* [31:16] Reserved */
} ECRC_CHLEN_Bits;

/* Channel Check Register i */
typedef volatile struct
{
    ureg32 CHK:32; /* [31:0] Check Register */
} ECRC_CHCHK_Bits;

/* Channel Crc Register i */
typedef volatile struct
{
    ureg32 CRC:32; /* [31:0] CRC Register */
} ECRC_CHCRC_Bits;

/* Channel Test Register i */
typedef volatile struct
{
    ureg32 FCRC:2; /* [1:0] Force CRC Register Mismatch */
    ureg32 FCFG:2; /* [3:2] Force CFG Register Mismatch */
    ureg32 FCHK:2; /* [5:4] Force Check Register Mismatch */
    ureg32 reserved_6:26;  /* [31:6] Reserved */
} ECRC_CHTST_Bits;

/* Alarm Status Register i */
typedef volatile struct
{
    ureg32 ESTCFG:1;    /* [0:0] Endinit status CFG */
    ureg32 ESTRST:1;    /* [1:1] Endinit status RST */
    ureg32 SEST:1;        /* [2:2] Safety Endinit status */
    ureg32 ECRE:1;        /* [3:3] Endinit clear redundancy error */
    ureg32 SECRE:1;        /* [4:4] Safety Endinit clear redundancy error */
    ureg32 SENRE:1;        /* [5:5] Safety enable redundancy error */
    ureg32 SENCRE:1;    /* [6:6] Safety enable clear redundancy error */
    ureg32 reserved_7:25;    /* [31:7] Reserved */
} ECRC_ALMSTR_Bits;

/* Alarm Clear Register i */
typedef volatile struct
{
    ureg32 EAC:2;    /* [1:0] Endinit alarm clear */
    ureg32 SEAC:2;    /* [3:2] Safety Endinit alarm clear */
    ureg32 SENAC:2;    /* [5:4] Safety enable alarm clear */
    ureg32 reserved_6:26;/* [31:6] Reserved */
} ECRC_ALMCLR_Bits;

/* Safety Enable Register */
typedef volatile struct
{
    ureg32 RSEN:2;    /* [1:0] Redundancy safety eanble */
    ureg32 reserved_2:30;    /* [31:2] Reserved */
} ECRC_SAFEEN_Bits;

/* ENBRn Register */
typedef volatile struct
{
    ureg32 REQEN:1;           /* [0:0] DMA Request enable  */
    ureg32 reserved_1:31;  /* [31:1] Reserved */
} ECRC_ENBR_Bits;

/* Mask Register */
typedef volatile struct
{
    ureg32 BEMASK:1;    /* [0:0] Bus error mask  */
    ureg32 reserved_1:31;    /* [31:1] Reserved */
} ECRC_MASKR_Bits;

/* Burst Register i */
typedef volatile struct
{
    ureg32 BURST:32; /* [31:0] Burst input data */
} ECRC_BURST_Bits;

/**********************************************************************************************************************
 *                                              ECRC Register Definitions
 *********************************************************************************************************************/
/* CHSTR Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_CHSTR_Bits B;  /* Bit-Field access */
} ECRC_CHSTR;

/* MRSTCLR Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{  
    uint32 U;              /* Unsigned access */
    ECRC_MRSTCLR_Bits B;   /* Bit-Field access */
} ECRC_MRSTCLR;

/* MRSTR1 Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    ECRC_MRSTR1_Bits B;   /* Bit-Field access */
} ECRC_MRSTR1;

/* MRSTR0 Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    ECRC_MRSTR0_Bits B;   /* Bit-Field access */
} ECRC_MRSTR0;

/* CHINi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_CHIN_Bits B;   /* Bit-Field access */
} ECRC_CHIN;

/* CHRESi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_CHRES_Bits B;  /* Bit-Field access */
} ECRC_CHRES;

/* CHCFGi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_CHCFG_Bits B;  /* Bit-Field access */
} ECRC_CHCFG;

/* CSRi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */   
{
    uint32 U;           /* Unsigned access */
    ECRC_CSR_Bits B;    /* Bit-Field access */
} ECRC_CSR;

/* CHLENi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_CHLEN_Bits B;  /* Bit-Field access */
} ECRC_CHLEN;

/* CHCHKi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_CHCHK_Bits B;  /* Bit-Field access */
} ECRC_CHCHK;

/* CHCRCi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_CHCRC_Bits B;  /* Bit-Field access */
} ECRC_CHCRC;

/* CHTSTi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_CHTST_Bits B;  /* Bit-Field access */
} ECRC_CHTST;

/* ALMSTRi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_ALMSTR_Bits B; /* Bit-Field access */
} ECRC_ALMSTR;

/* ALMCLRi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_ALMCLR_Bits B; /* Bit-Field access */
} ECRC_ALMCLR;

/* SAFEEN Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_SAFEEN_Bits B; /* Bit-Field access */
} ECRC_SAFEEN;

/* MASKR Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_MASKR_Bits B;  /* Bit-Field access */
} ECRC_MASKR;

/* ENBRn Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_ENBR_Bits B;  /* Bit-Field access */
} ECRC_ENBR;

/* BURSTi Register */
typedef union
/* #Violation: ecrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    ECRC_BURST_Bits B;  /* Bit-Field access */
} ECRC_BURST;

/**********************************************************************************************************************
 *                                        ECRC Register Configuration Structure
 *********************************************************************************************************************/
/* ECRC channel register i */
typedef volatile struct
{
    ECRC_CHIN CHIN;     /* 0x0 Channel Input Register i */
    ECRC_CHRES CHRES;   /* 0x4 Channel Result Register i */
    ECRC_CHCFG CHCFG;   /* 0x8 Channel Configuration Register i */
    ECRC_CSR CSR;       /* 0xC Channel CRC Status Register i */
    ECRC_CHLEN CHLEN;   /* 0x10 Channel Length Register i */
    ECRC_CHCHK CHCHK;   /* 0x14 Channel Check Register i */
    ECRC_CHCRC CHCRC;   /* 0x18 Channel CRC Register i */
    ECRC_CHTST CHTST;   /* 0x1C Channel Test Register i */
    ECRC_ALMSTR ALMSTR; /* 0x20 Channel Alarm Status Register i */
    ECRC_ALMCLR ALMCLR; /* 0x24 Channel Alarm Clear Register i */
} ECRC_CHR;

/* ECRC object */
typedef volatile struct
{
    ECRC_CHR CHR[8];            /* 0x0 Channel Register */
    ECRC_MRSTCLR MRSTCLR;       /* 0x140 Module Reset Clear Register */
    ECRC_MRSTR1 MRSTR1;         /* 0x144 Module Reset Register 1 */
    ECRC_MRSTR0 MRSTR0;         /* 0x148 Module Reset Register 0 */
    ECRC_CHSTR CHSTR;           /* 0x14C Channel Status Register */
    ECRC_SAFEEN SAFEEN;         /* 0x150 Safety Enable Register */
    ECRC_MASKR MASKR;           /* 0x154 MASK Register */
    ECRC_ENBR ENBR[8];            /* 0x158 ENBRn Register (THA6412 only) */
    uint32 RESERVED_178[34];    /* 0x178 reserved */
    ECRC_BURST BURST[128];      /* 0x200 Burst Register */
} ECRC_MODULE;

#endif /* ECRC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

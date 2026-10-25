/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    es_register.h
 * Author:      01321
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of ES module registers.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#es_register_h_REF_1:MISRAC2012-Rule-19.2; 
* Justification:Using unions for bit-field access to registers
*/
#ifndef ES_REGISTER_H_
#define ES_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        ES Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* ES Configuration register */
typedef volatile struct
{
    ureg32 POL:1;         /* [0:0] Input Polarity */
    ureg32 MODE:1;        /* [1:1] Mode Selection */
    ureg32 ENON:1;        /* [2:2] Enable on */
    ureg32 PSEL:1;        /* [3:3] PSEL Port Selection */
    ureg32 PBGFEN:1;      /* [4:4] Port B Glitch Filter Enable */
    ureg32 reserved_5:11; /* [15:5] Reserved */
    ureg32 EMSF:1;        /* [16:16] Emergency Stop Flag */
    ureg32 SEMSF:1;       /* [17:17] SAC Emergency Stop Flag */
    ureg32 PBGFCNT:10;    /* [27:18] Port B Glitch Filter Counter */
    ureg32 reserved_28:4; /* [31:28] Reserved */
} ES_ESCTRL_Bits;

/* ES Control register */
typedef volatile struct
{
    ureg32 reserved_0:18; /* [17:0] Reserved */
    ureg32 BUSMASK:2;     /* [19:18] Bus error mask */
    ureg32 SFFALMEN:2;    /* [21:20] SFF alarm enable */
    ureg32 ALMCLR:2;      /* [23:22] Clear ALMSTS register flag */
    ureg32 EMSFM:2;       /* [25:24] EMSF Modification */
    ureg32 SEMSFM:2;      /* [27:26] SEMSF Modification */
    ureg32 reserved_28:4; /* [31:28] Reserved */
} ES_ESCMD_Bits;

typedef volatile struct
{
    ureg32 reserved_0:23; /* [22:0] Reserved */
    ureg32 BITALM:1;      /* [23:23] Bit redundant alarm of ALMCLR */
    ureg32 SEALM:1;       /* [24:24] SE alarm of ESCTRL */
    ureg32 SFFALMSTS:1;   /* [25:25] ALMSTS register redundant alarm */
    ureg32 SFFCMD:1;      /* [26:26] ESCMD register redundant alarm */
    ureg32 SFFCTRL:1;     /* [27:27] ESCTRL register redundant alarm */
    ureg32 reserved_28:4; /* [31:28] Reserved */
} ES_ALMSTS_Bits;
/**********************************************************************************************************************
 *                                              ES Register Definitions
 *********************************************************************************************************************/
/* ES_ESCTRL register */
typedef union
/* #Violation: es_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    ES_ESCTRL_Bits B; /* Bit-Field access */
} ES_ESCTRL;

/* ES_ESCMD register */
typedef union
/* #Violation: es_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    ES_ESCMD_Bits B; /* Bit-Field access */
} ES_ESCMD;

/* ES_ALMSTS regsiter */
typedef union
/* #Violation: es_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    ES_ALMSTS_Bits B; /* Bit-Field access */
} ES_ALMSTS;

/**********************************************************************************************************************
 *                                        ES Register Configuration Structure
 *********************************************************************************************************************/
typedef volatile struct
{
    ureg32 RESERVED_0[1]; /* 0x0 - Internal reserved */
    ES_ESCTRL ESCTRL;     /* 0x4 - ESCTRL register */
    ES_ESCMD ESCMD;       /* 0x8 - ESCMD register */
    ES_ALMSTS ALMSTS;     /* 0xC - ALMSTS register */
} ES_MODULE;

#endif /* ES_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

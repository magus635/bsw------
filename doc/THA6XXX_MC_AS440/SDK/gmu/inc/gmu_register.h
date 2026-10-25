/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  gmu_register.h
 * Author:    01368
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all definitions of GMU module registers
 ************************************************************************************************/
/*
 *#Violation Summary
 *
 *#gmu_register_h_REF_1:MISRAC2012-Rule-2.3;
 * Justification: The members of the type are used in configuration-generated code.
 * 
 */

#ifndef GMU_REGISTER_H_
#define GMU_REGISTER_H_

/************************************************************************************************
 *                                                Includes
 ************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* The GMU region count */
#define NORMAL_PROTECT_REGION_MAX 32U

/**********************************************************************************************************************
 *                                        GMU Register Configuration Structure
 *********************************************************************************************************************/
 typedef struct
{
    ureg32 RGNLA;     /* 0x50 +x*0x10 - Region Lower Address*/
    ureg32 RGNHA;     /* 0x54 +x*0x10 - Region Higher Address */
    ureg32 RGNACCENW; /* 0x58 +x*0x10 - Region Write Access Enable Register */
    ureg32 RGNACCENR; /* 0x5C +x*0x10 - Region Read Access Enable Register */
} GMU_NormReg;

typedef struct
{
    ureg32 SPRGNLA;      /* 0x250 +x*0x10 - Special Region Lower Address*/
    ureg32 SPRGNHA;      /* 0x254 +x*0x10 - Special Region Higher Address */
    ureg32 SPRRGNACCENW; /* 0x258 +x*0x10 - Special Region Write Access Enable Register */
    ureg32 SPRRGNACCENR; /* 0x25C +x*0x10 - Special Region Read Access Enable Register */
/* Violation: gmu_register_h_REF_1 */
} GMU_SpecReg;


typedef volatile struct
{
    ureg32 MEMCFG0;                 /* 0x00 - Memory0 Config; The register not support in THA6206 and THA6104 */
    ureg32 RESERVED_0004[3];        /* 0x04 - Reserve */
    ureg32 MEMCFG1;                 /* 0x10 - Memory1 Config */
    ureg32 SPMCTRL0;                /* 0x14 - Sleep Mode Control0*/
    ureg32 SPMCTRL1;                /* 0x18 - Sleep Mode Control1*/
    ureg32 Res1;                    /* 0x1C - Reserve*/
    ureg32 MEMSTS;                  /* 0x20 - Memory State*/
    ureg32 SPSTS;                   /* 0x24 - Sleep State*/
    ureg32 ALMMSK;                  /* 0x28 - Alarm Mask*/
    ureg32 MEMSCTRL0;               /* 0x2C - Memory Safety Control0*/
    ureg32 MEMSCTRL1;               /* 0x30 - Memory Safety Control1*/
    ureg32 RESERVED_0034[7];        /* 0x34 - Reserve */
    GMU_NormReg NRGN[32];           /* 0x50 - Normal Region  */
#if defined (THA6_THA6412) || defined (THA6_THA6104)
    GMU_SpecReg SRGN[4];            /* 0x250 -Special Region  */
#endif    
#if defined (THA6_THA6206)  || defined (THA6_THA6206D)
    ureg32 RESERVED_0250[16];       /* 0x250 - Reserve */
#endif
    ureg32 NMSPRGNACC;              /* 0x290 -Special Region Access*/
    ureg32 RESERVED_0294[3];        /* 0x294 -Reserve */
    ureg32 SBRECORD[5];             /* 0x2A0+x*0x4 - Single Bit Record Register */
    ureg32 DBRECORD;                /* 0x2B4 - Double Bit Record Register */
} GMU_MODULE;

#endif /* GMU_REGISTER_H_ */

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

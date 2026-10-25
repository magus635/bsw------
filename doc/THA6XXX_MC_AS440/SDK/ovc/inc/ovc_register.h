/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    ovc_register.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of OVC module registers.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
 *#Violation Summary
 *
 *#ovc_register_h_REF_1:MISRAC2012-Rule-19.2;
 * Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be 
 *                ensured by code review.
 *
 */

#ifndef OVC_REGISTER_H_
#define OVC_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
#define OVC_CORE_NUMBERS 2
#define OVC_BLOCK_NUMBERS 32
 /**********************************************************************************************************************
 *                                        OVC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* OVC enable register*/
typedef struct
{
    ureg32 OVEN0 : 1;       /* [0:0] OVC is enabled on core0 - RW */
    ureg32 OVEN1 : 1;       /* [1:1] OVC is enabled on core1 - RW, for CHIP THA6206 and THA6412 */
    ureg32 reserved_2 : 30; /* [31:2] Internal reserved */
} OVC_EN_Bits;

/* OVC control register*/
typedef struct
{
    ureg32 SEL : 2;         /* [0:0] Action selected by OVSTRT, OVSTP bits, set by the same
                               register write access, is applied to core0 - RW */
                            /* [1:1] Action selected by OVSTRT, OVSTP bits, set by the same
                               register write access, is applied to core1 - RW, for CHIP THA6206 and THA6412 */
    ureg32 reserved_2 : 14; /* [15:2] Internal reserved */
    ureg32 OVSTART : 1;     /* [16:16] For each CPU selected with CSEL, all the blocks selected
                               with OVCx_OSEL will be activated - RW */
    ureg32 OVSTOP : 1;      /* [17:17] For CPUs selected with CSEL, all the overlay blocks are
                               deactivated - RW */
    ureg32 reserved_18 : 6; /* [23:18] Internal reserved */
    ureg32 OVCONF : 2;      /* [24:24] Overlay Configured 0 - RW */
                            /* [25:25] Overlay Configured 1 - RW, for CHIP THA6206 and THA6412 */
    ureg32 reserved_26 : 3; /* [28:26] Internal reserved */
    ureg32 POVCONF : 1;     /* [29:29] Write Protection for OVCONF - RW */
    ureg32 reserved_30 : 2; /* [31:30] Internal reserved */
} OVC_CTR_Bits;

/* OVC bypass0 register */
typedef struct
{
    ureg32 OVCBYPS0 : 2;  /* [1:0] OVC Bypass control - RW */
    ureg32 reserved : 30; /* [31:2] Internal reserved */
} OVC_BYPASS0_Bits;

/* OVC bypass1 register, for Chip THA6412 */
typedef struct
{
    ureg32 OVCBYPS1 : 2;  /* [1:0] OVC Bypass control - RW */
    ureg32 reserved : 30; /* [31:2] Internal reserved */
} OVC_BYPASS1_Bits;

/* OVC alarm clear register */
typedef struct
{
    ureg32 CORECLR : 2;   /* [0:0] CORECLR[0] : address selection redundancy error error alarm
                             and clear register status - WO */
                          /* [1:1] CORECLR[1] : target address ECC check error alarm and clear
                             register status - WO */
    ureg32 REGCLR : 1;    /* [2:2] The Bypass register multi-bit redundancy error alarm and
                             clear register status - WO */
    ureg32 PROTCLR : 1;   /* [3:3] E/SE protected register illegal access alarm and clear
                             register status - WO */
    ureg32 reserved : 28; /* [31:4] Internal reserved */
} OVC_ALMCLR_Bits;

/* OVC select register (ovc_core0/ovc_core1) */
typedef struct
{
    ureg32 SOVEN : 32; /* [31:0] Enable OVC block of core - RW */
} OVC_SEL_Bits;

/* OVC map register (ovc_core0/ovc_core1) */
typedef struct
{
    ureg32 MAPS : 32; /* [31:0] core's OVC block redirection indication - RO */
} OVC_MAP_Bits;

/* OVC error control register (OVC core0/OVC core1) */
typedef struct
{
    ureg32 INT_CLR : 1;      /* [0:0] Clear OVC error status - RW */
    ureg32 reserved_1 : 3;   /* [3:1] Internal reserved */
    ureg32 AW_ECC_ALM : 1;   /* [4:4] AW channel address ECC verification error status - RO */
    ureg32 AR_ECC_ALM : 1;   /* [5:5] AR channel address ECC verification error status - RO */
    ureg32 AW_SEL_ALM : 1;   /* [6:6] block write selection redundancy error alarm
                                status - RO */
    ureg32 AR_SEL_ALM : 1;   /* [7:7] block read selection redundancy error alarm
                                status - RO */
    ureg32 BYPASS_ALM : 1;   /* [8:8] bypass redundancy error alarm status - RO */
    ureg32 SE_ALM : 1;       /* [9:9] SE permission access register, illegal access alarm
                                status - RO */
    ureg32 E_ALM : 1;        /* [10:10] E permission access register, illegal access alarm
                                status - RO */
    ureg32 reserved_11 : 19; /* [29:11] Internal reserved */
    ureg32 INVALID_ADR : 1;  /* [30:30] Target address invalid indication - RO */
    ureg32 ERR_STATUS : 1;   /* [31:31] OVC error indication - RO */
} OVC_ERRCON_Bits;

/* OVC redirection base address register (OVC core0/core1) */
typedef struct
{
    ureg32 reserved_0 : 5;  /* [4:0] Internal reserved */
    ureg32 BASE : 17;       /* [21:5] the base address the overlay memory block in the
                            overlay memory - RW */
    ureg32 reserved_22 : 2; /* [23:22] Internal reserved */
    ureg32 MEMSEL : 4;      /* [27:24] Selects overlay memory used for redirection - RW */
    ureg32 reserved_28 : 3; /* [30:28] Internal reserved*/
    ureg32 OVBLKEN : 1;     /* [31:31] Overlay enabled - RW */
} OVC_RBAR_Bits;

/* OVC overlay address mask (OVC core0/core1) */
typedef struct
{
    ureg32 reserved_0 : 5;  /* [4:0] Internal reserved */
    ureg32 MASK : 12;       /* [16:5] OVC block size definition - RW */
    ureg32 ONE : 11;        /* [27:17] fixed "1" values - RO */
    ureg32 reserved_28 : 4; /* [31:28] Internal reserved */
} OVC_MASK_Bits;

/* OVC target address (OVC core0/core1) */
typedef struct
{
    ureg32 reserved : 5; /* [4:0] Internal reserved */
    ureg32 BASE : 27;    /* [31:5] Target base address - RW */
} OVC_TAR_Bits;

/* OVC alarm enable register */
typedef struct
{
    ureg32 ALMEN0 : 1;    /* [0:0] Enable OVC core0 address selection redundancy error error alarm - RW */
    ureg32 ALMEN1 : 1;    /* [1:1] Enable OVC core0 target address ECC check error alarm - RW */
    ureg32 ALMEN2 : 1;    /* [2:2] Enable OVC core1 address selection redundancy error error alarm - RW, for CHIP THA6206 and THA6412 */
    ureg32 ALMEN3 : 1;    /* [3:3] Enable OVC core1 target address ECC check error alarm - RW, for CHIP THA6206 and THA6412 */
    ureg32 ALMEN4 : 1;    /* [4:4] Enable bypass redundancy error alarm - RW */
    ureg32 reserved : 27; /* [5:31] Internal reserved */
} OVC_ALMEN_Bits;

/* OVC INTC Mask register */
typedef struct
{
    ureg32 INTMSK0 : 1;   /* [0:0] Mask OVC core0 INTC - RW */
    ureg32 INTMSK1 : 1;   /* [1:1] Mask OVC core1 INTC - RW, for CHIP THA6206 and THA6412 */
    ureg32 reserved : 30; /* [2:31] Internal reserved */

} OVC_INTMSK_Bits;

/* OVC Bus Error Mask register */
typedef struct
{
    ureg32 BUSERRMSK : 1; /* [0:0] Mask Bus Error - RW */
    ureg32 reserved : 31; /* [1:31] Internal reserved */

} OVC_BUSERRMSK_Bits;
/**********************************************************************************************************************
 *                                              OVC Register Definitions
 *********************************************************************************************************************/
/*OVCEN register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;      /* Unsigned access */
    OVC_EN_Bits B; /* Bit-Field access */
} OVC_EN;

/*OVCCTR register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;       /* Unsigned access */
    OVC_CTR_Bits B; /* Bit-Field access */
} OVC_CTR;

/*BYPASS0 register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    OVC_BYPASS0_Bits B; /* Bit-Field access */
} OVC_BYPASS0;

/*BYPASS1 register for Chip THA6412*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;           /* Unsigned access */
    OVC_BYPASS1_Bits B; /* Bit-Field access */
} OVC_BYPASS1;

/*ALMCLR register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    OVC_ALMCLR_Bits B; /* Bit-Field access */
} OVC_ALMCLR;

/*SEL register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;       /* Unsigned access */
    OVC_SEL_Bits B; /* Bit-Field access */
} OVC_SEL;

/*Map register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;       /* Unsigned access */
    OVC_MAP_Bits B; /* Bit-Field access */
} OVC_MAP;

/*ERRCON register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    OVC_ERRCON_Bits B; /* Bit-Field access */
} OVC_ERRCON;

/*MASK register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;        /* Unsigned access */
    OVC_MASK_Bits B; /* Bit-Field access */
} OVC_MASK;

/*TAR register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;       /* Unsigned access */
    OVC_TAR_Bits B; /* Bit-Field access */
} OVC_TAR;

/*RBAR register*/
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;        /* Unsigned access */
    OVC_RBAR_Bits B; /* Bit-Field access */
} OVC_RBAR;

/* ALMEN register */
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;         /* Unsigned access */
    OVC_ALMEN_Bits B; /* Bit-Field access */
} OVC_ALMEN;

/* INTMSK register */
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;          /* Unsigned access */
    OVC_INTMSK_Bits B; /* Bit-Field access */
} OVC_INTMSK;

/* BUSERRMSK register */
typedef union
/* #Violation: ovc_register_h_REF_1 */
{
    ureg32 U;             /* Unsigned access */
    OVC_BUSERRMSK_Bits B; /* Bit-Field access */
} OVC_BUSERRMSK;
/**********************************************************************************************************************
 *                                        OVC Register Configuration Structure
 *********************************************************************************************************************/
/* OVC core block object */
typedef volatile struct
{
    OVC_RBAR RBAR; /* 0x14+n1*0x200+n2*0xC(n1:core id,n2:block id) - Redirected
                      address base register */
    OVC_TAR TAR;   /* 0x18+n1*0x200+n2*0xC(n1:core id,n2:block id) - Overlay target
                      address base register */
    OVC_MASK MASK; /* 0x1C+n1*0x200+n2*0xC(n1:core id,n2:block id) - Overlay mask
                      register */
} OVC_BLOCK;

/* CORE object */
typedef volatile struct
{
    OVC_SEL SEL;         /* 0x8+n*0x200(n:core id) - COREx OVC select register */
    OVC_MAP MAP;         /* 0xC+n*0x200(n:core id) - COREx OVC map register */
    OVC_ERRCON ERRCON;   /* 0x10+n*0x200(n:core id) - COREx OVC error control register */
    OVC_BLOCK BLOCK[OVC_BLOCK_NUMBERS]; /* 0x14+n*0x200(n:core id) - COREx block register */
    ureg32 RESERVED[29]; /* 0x194+n*0x200(n:core id) - Internal reserved */
} OVC_CORE;

/* OVC module */
typedef volatile struct
{
    OVC_EN EN;               /* 0x0 - Enable register */
    OVC_CTR CTR;             /* 0x4 - Control register */
    OVC_CORE CORE[OVC_CORE_NUMBERS];        /* 0x8 - Core register, CORE[1] for CHIP THA6206 and THA6412 */
    OVC_BYPASS0 BYPASS0;     /* 0x408 - BYPASS0 register */
    OVC_ALMCLR ALMCLR[OVC_CORE_NUMBERS];    /* 0x40c - ALMCLR0 register */
                             /* 0x410 - ALMCLR1 register, for CHIP THA6206 and THA6412 */
    OVC_ALMEN ALMEN;         /* 0x414 - Alarm Enable register */
    OVC_INTMSK INTMSK;       /* 0x418 - INTC mask register */
    OVC_BUSERRMSK BUSERRMSK; /* 0x41c - Bus Error mask register */
    OVC_BYPASS1 BYPASS1;     /* 0x420 - BYPASS1 register for Chip THA6412*/
} OVC_MODULE;

#endif /* OVC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

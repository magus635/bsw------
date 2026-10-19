/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_isr_GICv3Register.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_ISR_GICV3REGISTER_H_
#define OS_ISR_GICV3REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "datatypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                   GIC Distributor Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* GIC Distributor control register */
typedef struct
{
    uint32 ENABLEGRP0:1;  /* [0:0] Enable Group 0 interrupts from the GIC Distributor to the GIC CPU Interface - RW */
    uint32 ENABLEGRP1:1;  /* [1:1] Enable Group 1 interrupts from the GIC Distributor to the GIC CPU Interface - RW */
    uint32 reserved_2:2;  /* [3:2] Internal reserved */
    uint32 ARE:1;         /* [4:4] Affinity Routing Enable - RO */
    uint32 reserved_5:1;  /* [5:5] Internal reserved */
    uint32 DS:1;          /* [6:6] Disable Security - RO */
    uint32 EINWF:1;       /* [7:7] Enable 1 of N Wakeup functionality - RO */
    uint32 reserved_8:23; /* [30:8] Internal reserved */
    uint32 RWP:1;         /* [31:31] Register Write Pending - RO */
} GICD_CTRL_Bits;

/* GIC Distributor interrupt controller typer register */
typedef struct
{
    uint32 ITLINESNUMBER:5; /* [4:0] Indicates the number of SPI INTIDs that GIC Distributor supports - RO */
    uint32 CPUNUMBER:3;     /* [7:5] Indicates the number of cores that can be used as interrupt targets when
                               GICD_CTLR.ARE is 0 - RO */
    uint32 reserved_8:2;    /* [9:8] Internal reserved */
    uint32 SECURITYEXTN:1;  /* [10:10] Indicates whether the GIC Distributor supports two Security states - RO */
    uint32 reserved_11:5;   /* [15:11] Internal reserved */
    uint32 MBIS:1;          /* [16:16] Indicates whether the GIC Distributor supports Message-Based Interrupts
                               Supported - RO */
    uint32 LPIS:1;          /* [17:17] Indicates whether the GIC Distributor supports Locality-specific Peripheral
                               Interrupts (LPIs) - RO */
    uint32 DVIS:1;          /* [18:18] Indicates whether the GIC Distributor supports Direct Virtual LPI injection
                               - RO */
    uint32 IDBITS:5;        /* [23:19] Indicates the number of INTID bits that the GIC Distributor supports,
                               minus one - RO */
    uint32 A3V:1;           /* [24:24] Indicates whether the GIC Distributor supports nonzero values of Affinity
                               level 3 - RO */
    uint32 NO1N:1;          /* [25:25] Indicates whether the GIC Distributor supports 1 of N SPIs - RO */
    uint32 reserved_26:6;   /* [31:26] Internal reserved */
} GICD_TYPER_Bits;

/* GIC Distributor interrupt routing register */
typedef struct
{
    uint32 AFF0:8;                 /* [7:0] Affinity level 0 - RW */
    uint32 AFF1:8;                 /* [15:8] Affinity level 1 - RO */
    uint32 AFF2:8;                 /* [23:16] Affinity level 2 - RO */
    uint32 reserved_24:7;          /* [30:24] Internal reserved */
    uint32 INTERRUPTROUTINGMODE:1; /* [31:31] Interrupt Routing Mode - RW */
    uint32 AFF3:8;                 /* [39:32] Affinity level 3 - RO */
    uint32 reserved_40:24;         /* [63:40] Internal reserved */
} GICD_IROUTER_Bits;

/* GIC Distributor identification register */
typedef struct
{
    uint32 COMPONENTID:8; /* [7:0] Component ID - RO */
    uint32 reserved_8:24; /* [31:8] Internal reserved */
} GICD_PIDR_Bits;

/* GIC Distributor component identification register */
typedef struct
{
    uint32 COMPONENTID:8; /* [7:0] Component ID - RO */
    uint32 reserved_8:24; /* [31:8] Internal reserved */
} GICD_CIDR_Bits;
/**********************************************************************************************************************
 *                                  GIC Redistributor Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* GIC Redistributor control register */
typedef struct
{
    uint32 ENABLELPIS:1;  /* [0:0] This bit controls whether physical LPIs are enabled - RO */
    uint32 reserved_1:2;  /* [2:1] Internal reserved */
    uint32 RWP:1;         /* [3:3] Register Write Pending - RO */
    uint32 reserved_4:20; /* [23:4] Internal reserved */
    uint32 DPG0:1;        /* [24:24] Relates to 1 of N distribution which is not supported - RAZ/WI */
    uint32 DPG1NS:1;      /* [25:25] Relates to 1 of N distribution which is not supported - RAZ/WI */
    uint32 DPG1S:1;       /* [26:26] Relates to 1 of N distribution which is not supported - RAZ/WI */
    uint32 reserved_27:4; /* [30:27] Internal reserved */
    uint32 UWP:1;         /* [31:31] Indicates whether upstream writes are pending - RO */
} GICR_CTRL_Bits;

/* GIC Redistributor interrupt controller typer register */
typedef struct
{
    uint32 PLPIS:1;            /* [0:0] Indicates whether the GIC implementation supports physical LPIs - RO */
    uint32 VLPIS:1;            /* [1:1] Indicates whether the GIC implementation supports virtual
                                  LPIs - RO */
    uint32 reserved_2:1;       /* [2:2] Internal reserved */
    uint32 DIRECTLPI:1;        /* [3:3] Indicates whether this Redistributor supports direct injection of LPIs - RO */
    uint32 LAST:1;             /* [4:4] Indicates whether this Redistributor is the last numbered Redistributor in a
                                 series of contiguous Redistributor pages - RO */
    uint32 DPGS:1;             /* [5:5] Sets support for GICR_CTLR.DPG* bits - RO */
    uint32 reserved_6:2;       /* [7:6] Internal reserved */
    uint32 PROCESSORNUMBER:16; /* [23:8] A unique identifier for the core - RO */
    uint32 COMMONLPIAFF:2;     /* [25:24] Relates to LPIs which are not supported - RO */
    uint32 reserved_26:6;      /* [31:26] Internal reserved */
    uint32 AFF0:8;             /* [39:32] Affinity level 0 - RO */
    uint32 AFF1:8;             /* [47:40] Affinity level 1 - RO */
    uint32 AFF2:8;             /* [55:48] Affinity level 2 - RO */
    uint32 AFF3:8;             /* [63:56] Affinity level 3 - RO */
} GICR_TYPER_Bits;

/* GIC Redistributor wake register */
typedef struct
{
    uint32 reserved_0:1;     /* [0:0] Internal reserved */
    uint32 PROCESSORSLEEP:1; /* [1:1] Instructs the Redistributor that the target is entering the processor sleep state
                                - RW */
    uint32 CHILDRENASLEEP:1; /* [2:2] Indicates if the connected target is quiescent - RW */
    uint32 reserved_3:29;    /* [31:3] Internal reserved */
} GICR_WAKER_Bits;

/* GIC Redistributor identification register */
typedef struct
{
    uint32 COMPONENTID:8; /* [7:0] Component ID - RO */
    uint32 reserved_8:24; /* [31:8] Internal reserved */
} GICR_PIDR_Bits;

/* GIC Redistributor component identification register */
typedef struct
{
    uint32 COMPONENTID:8; /* [7:0] Component ID - RO */
    uint32 reserved_8:24; /* [31:8] Internal reserved */
} GICR_CIDR_Bits;
/**********************************************************************************************************************
 *                                        GIC Distributor Register Definitions
 *********************************************************************************************************************/
/* GICD_CTRL register */
typedef union
{
    uint32 U;              /* Unsigned access */
    GICD_CTRL_Bits B; /* Bit-Field access */
} GICD_CTRL;

/* GICD_TYPER register */
typedef union
{
    uint32 U;               /* Unsigned access */
    GICD_TYPER_Bits B; /* Bit-Field access */
} GICD_TYPER;

/* GICD_IROUTER register */
typedef union
{
    uint64 U;                 /* Unsigned access */
    GICD_IROUTER_Bits B; /* Bit-Field access */
} GICD_IROUTER;

/* GICD_PIDR register */
typedef union
{
    uint32 U;              /* Unsigned access */
    GICD_PIDR_Bits B; /* Bit-Field access */
} GICD_PIDR;

/* GICD_CIDR register */
typedef union
{
    uint32 U;              /* Unsigned access */
    GICD_CIDR_Bits B; /* Bit-Field access */
} GICD_CIDR;
/**********************************************************************************************************************
 *                                       GIC Redistributor Register Definitions
 *********************************************************************************************************************/
/* GICR_CTRL register */
typedef union
{
    uint32 U;              /* Unsigned access */
    GICR_CTRL_Bits B; /* Bit-Field access */
} GICR_CTRL;

/* GICR_TYPER register */
typedef union
{
    uint64 U;               /* Unsigned access */
    GICR_TYPER_Bits B; /* Bit-Field access */
} GICR_TYPER;

/* GICR_WAKER register */
typedef union
{
    uint32 U;               /* Unsigned access */
    GICR_WAKER_Bits B; /* Bit-Field access */
} GICR_WAKER;

/* GICR_PIDR register */
typedef union
{
    uint32 U;              /* Unsigned access */
    GICR_PIDR_Bits B; /* Bit-Field access */
} GICR_PIDR;

/* GICR_CIDR register */
typedef union
{
    uint32 U;              /* Unsigned access */
    GICR_CIDR_Bits B; /* Bit-Field access */
} GICR_CIDR;
/**********************************************************************************************************************
 *                                        INTC Register Configuration Structure
 *********************************************************************************************************************/
typedef volatile struct
{
    GICD_CTRL GICDCTRL;            /* 0x0 - Distributor control register */
    GICD_TYPER GICDTYPER;          /* 0x4 - Interrupt controller typer register */
    uint32 GICDIIDR;                    /* 0x8 - Distributor Implementer Identification Register */
    uint32 reserved_8[30];              /* 0xC - Internal reserved */
    uint32 GICDIGROUP[30];              /* 0x84 - Interrupt Group Registers */
    uint32 reserved_FC[2];              /* 0xFC - Internal reserved */
    uint32 GICDISENABLER[30];           /* 0x104 - Interrupt Set-Enable Registers */
    uint32 reserved_17C[2];             /* 0x17C - Internal reserved */
    uint32 GICDICENABLER[30];           /* 0x184 - Interrupt Clear-Enable Registers */
    uint32 reserved_1FC[2];             /* 0x1FC - Internal reserved */
    uint32 GICDISPENDR[30];             /* 0x204 - Interrupt Set-Pending Registers */
    uint32 reserved_27C[2];             /* 0x27C - Internal reserved */
    uint32 GICDICPENDR[30];             /* 0x284 - Interrupt Clear-Pending Registers */
    uint32 reserved_2FC[2];             /* 0x2FC - Internal reserved */
    uint32 GICDISACTIVER[30];           /* 0x304 - Interrupt Set-Active Registers */
    uint32 reserved_37C[2];             /* 0x37C - Internal reserved */
    uint32 GICDICACTIVER[30];           /* 0x384 - Interrupt Clear-Active Registers */
    uint32 reserved_3FC[9];             /* 0x3FC - Internal reserved */
    uint32 GICDIPRIORITYR[240];         /* 0x420 - Interrupt Priority Registers */
    uint32 reserved_7E0[266];           /* 0x7E0 - Internal reserved */
    uint32 GICDICFGR[60];               /* 0xC08 - Interrupt Configuration Registers */
    uint32 reserved_CF8[5378];          /* 0xCF8 - Internal reserved */
    GICD_IROUTER GICDIROUTER[960]; /* 0x6100 - Interrupt Routing Registers */
    uint32 reserved_7EFC[8244];         /* 0x7EFC - Internal reserved */
    GICD_PIDR GICDPIDR[8];         /* 0xFFD0 - Identification Registers */
    GICD_CIDR GICDCIDR[4];         /* 0xFFF0 - Component Identification Registers */
} DISTRIBUTOR_MODULE;

typedef volatile struct
{
    /* offset from address of GICR for control target n : 0x100000 + 2n*0x10000 */
    GICR_CTRL GICRCTRL;    /* 0x0 - Redistributor Control Register */
    uint32 GICRIIDR;            /* 0x4 - Redistributor Implementer Identification */
    GICR_TYPER GICRTYPER;  /* 0x8 - Redistributor Type Register */
    uint32 reserved_10;         /* 0x10 - Internal reserved */
    GICR_WAKER GICRWAKER;  /* 0x14 - Redistributor Wake Register */
    uint32 reserved_18[16366];  /* 0x18 - Internal reserved */
    GICR_PIDR GICRPIDR[8]; /* 0xFFE0 - Redistributor Identification Registers */
    GICR_CIDR GICRCIDR[4]; /* 0xFFF0 - Redistributor Component Identification */
    /* offset from address of GICR for SGIs and PPIs target n : 0x110000 + 2n*0x10000 */
    uint32 reserved_0[32];      /* 0x0 - Internal reserved */
    uint32 GICRIGROUPR;         /* 0x80 - Interrupt Group Register */
    uint32 RESERCED_84[31];     /* 0x84 - Internal reserved */
    uint32 GICRISENABLER;       /* 0x100 - Interrupt Set-Enable Register */
    uint32 reserved_104[31];    /* 0x104 - Internal reserved */
    uint32 GICRICENABLER;       /* 0x180 - Interrupt Clear-Enable Register */
    uint32 reserved_184[31];    /* 0x184 - Internal reserved */
    uint32 GICRISPENDR;         /* 0x200 - Interrupt Set-Pending Register */
    uint32 reserved_204[31];    /* 0x204 - Internal reserved */
    uint32 GICRICPENDR;         /* 0x280 - Interrupt Clear-Pending Register */
    uint32 reserved_284[31];    /* 0x284 - Internal reserved */
    uint32 GICRISACTIVER;       /* 0x300 - Interrupt Set-Active Register */
    uint32 reserved_304[31];    /* 0x304 - Internal reserved */
    uint32 GICRICACTIVER;       /* 0x380 - Interrupt Clear-Active Register */
    uint32 reserved_384[31];    /* 0x384 - Internal reserved */
    uint32 GICRIPRIORITY[8];    /* 0x400 - Interrupt Priority Registers */
    uint32 reserved_420[504];   /* 0x420 - Internal reserved */
    uint32 GICRICFGR0;          /* 0xC00 - Interrupt Configuration Register */
    uint32 GICRICFGR1;          /* 0xC04 - Interrupt Configuration Register */
    uint32 reserved_C08[15614]; /* 0xC08 - Internal reserved */
} REDISTRIBUTOR_MODULE;

typedef volatile struct
{
    DISTRIBUTOR_MODULE DISTRIBUTOR;        /* 0x0 - GIC Distributor module */
    uint32 reserved_10000[245760];              /* 0x10000 - Internal reserved */
    REDISTRIBUTOR_MODULE REDISTRIBUTOR[2]; /* 0x100000 - GIC Redistributor module */
} GIC_MODULE;

#endif /* OS_ISR_GICV3REGISTER_H_ */
/**********************************************************************************************************************
 *                 End of File: Os_isr_GICv3Register.h
 *********************************************************************************************************************/

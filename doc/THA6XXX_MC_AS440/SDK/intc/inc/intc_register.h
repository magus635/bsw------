/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    intc_register.h
 * Author:      01369
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of INTC module registers.
 *********************************************************************************************************************/

/*
*#Violation Summary
*
*#intc_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to register.
*
*#intc_register_h_REF_2:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#intc_register_h_REF_3:CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*/

#ifndef INTC_REGISTER_H_
#define INTC_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        INTC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Semaphore enable register */
typedef struct
{
    ureg32 SEMFEN0:2;      /* [1:0] Semaphore0 read-clear function enable - RW */
    ureg32 SEMFEN1:2;      /* [3:2] Semaphore1 read-clear function enable - RW */
    ureg32 SEMFEN2:2;      /* [5:4] Semaphore2 read-clear function enable - RW */
    ureg32 SEMFEN3:2;      /* [7:6] Semaphore3 read-clear function enable - RW */
    ureg32 SEMFEN4:2;      /* [9:8] Semaphore4 read-clear function enable - RW */
    ureg32 SEMFEN5:2;      /* [11:10] Semaphore5 read-clear function enable - RW */
    ureg32 SEMFEN6:2;      /* [13:12] Semaphore6 read-clear function enable - RW */
    ureg32 SEMFEN7:2;      /* [15:14] Semaphore7 read-clear function enable - RW */
    ureg32 SEMFEN8:2;      /* [17:16] Semaphore8 read-clear function enable - RW */
    ureg32 SEMFEN9:2;      /* [19:18] Semaphore9 read-clear function enable - RW */
    ureg32 SEMFEN10:2;      /* [21:20] Semaphore10 read-clear function enable - RW */
    ureg32 SEMFEN11:2;      /* [23:22] Semaphore11 read-clear function enable - RW */
    ureg32 SEMFEN12:2;      /* [25:24] Semaphore12 read-clear function enable - RW */
    ureg32 SEMFEN13:2;      /* [27:26] Semaphore13 read-clear function enable - RW */
    ureg32 SEMFEN14:2;      /* [29:28] Semaphore14 read-clear function enable - RW */
    ureg32 SEMFEN15:2;      /* [31:30] Semaphore15 read-clear function enable - RW */
} INTC_SEMAPEN_Bits;

/* Semaphore register */
typedef struct
{
    ureg32 SEMF:2;        /* [1:0] Semaphore occupancy status - RW */
    ureg32 reserved_2:14; /* [15:2] Internal reserved */
    ureg32 SEMFPSW:16;    /* [31:16] Semaphore password - RW */
} INTC_SEMAP_Bits;

/* Soft interrupt control register */
typedef struct
{
    ureg32 SOFTINT:2;     /* [1:0] Software interrupt valid/invalid - RW */
    ureg32 reserved_2:14; /* [15:2] Internal reserved */
    ureg32 SFINTPSW:16;   /* [31:16] Software interrupt password - RW */
} INTC_SFINTCR_Bits;

/* Interrupt count enable register */
typedef struct
{
    ureg32 INTCNT_EN:1;   /* [0:0] Interrupt count enable - RW */
    ureg32 reserved_1:31; /* [31:1] Internal reserved */
} INTC_INTCNTEN_Bits;

/* Set interrupt password register */
typedef struct
{
    ureg32 SETINTEN:2;    /* [1:0] Software set interrupt enable - RW */
    ureg32 reserved_2:14; /* [15:2] Internal reserved */
    ureg32 SETPSW:16;     /* [31:16] Software set interrupt password - RW */
} INTC_SETPSW_Bits;

/* Alarm status register */
typedef struct
{
    ureg32 SEMALM:8;      /* [7:0] Alarm state of SEMFEN7-SEMFEN0 Multi-bit redundant - RO */
    ureg32 SFINTALM:8;    /* [15:8] Alarm state of SOFTINT7-SOFTINT0 Multi-bit redundant - RO */
    ureg32 SETINTALM:1;   /* [16:16] Alarm state of SETINTEN Multi-bit redundant - RO */
    ureg32 PROTALM:1;     /* [17:17] Alarm state of se protection register illegal access - RO */
    ureg32 SEMFALM:8;     /* [25:18] Alarm state of SEMAP.SEMF Multi-bit redundant - RO */
    ureg32 reserved_26:6; /* [31:26] Internal reserved */
} INTC_ALMSTS_Bits;

/* Alarm status register */
typedef struct
{
    ureg32 SEMALM:8;      /* [7:0] Alarm state of SEMFEN7-SEMFEN0 Multi-bit redundant - RO */
    ureg32 SFINTALM:8;    /* [15:8] Alarm state of SOFTINT7-SOFTINT0 Multi-bit redundant - RO */
    ureg32 reserved_16:2; /* [17:16] Internal reserved */
    ureg32 SEMFALM:8;     /* [25:18] Alarm state of SEMAP.SEMF Multi-bit redundant - RO */
    ureg32 reserved_26:6; /* [31:26] Internal reserved */
} INTC_ALMSTS1_Bits;

/* Alarm clear register */
typedef struct
{
    ureg32 SEMALMCLR:1;    /* [0:0] Clear the alarm state of SEMFEN7-SEMFEN0 Multi-bit redundant and SEMAP.SEMF
                              Multi-bit redundant - WO */
    ureg32 SFTINTALMCLR:1; /* [1:1] Clear the alarm state of SOFTINT7-SOFTINT0 Multi-bit redundant - WO */
    ureg32 SETINTALMCLR:1; /* [2:2] Clear the alarm state of SETINTEN Multi-bit redundant - WO */
    ureg32 PROTALMCLR:1;   /* [3:3] Clear the alarm state of SE illegal access - WO */
    ureg32 reserved_4:28;  /* [31:4] Internal reserved */
} INTC_ALMCLR_Bits;

/* Alarm enable register */
typedef struct
{
    ureg32 ALMEN0:1;        /* [0:0] Enable the alarm of SEMFEN/SEMAP.SEMF Multi-bit redundant - RW */
    ureg32 ALMEN1:1;        /* [1:1] Enable the alarm of SFINTCR.SOFTINT Multi-bit redundant - RW */
    ureg32 ALMEN2:1;        /* [2:2] Enable the alarm of SETPSW.SETINTEN Multi-bit redundant - RW */
    ureg32 reserved_3:29;   /* [31:3] Internal reserved */
} INTC_ALMEN_Bits;

/* Soft interrupt mask register */
typedef struct
{
    ureg32 STINTMSK0:1;     /* [0:0] soft_int_core0_o[0] interrupt masking control - RW */
    ureg32 STINTMSK1:1;     /* [1:1] soft_int_core0_o[1] interrupt masking control - RW */
    ureg32 STINTMSK2:1;     /* [2:2] soft_int_core0_o[2] interrupt masking control - RW */
    ureg32 STINTMSK3:1;     /* [3:3] soft_int_core0_o[3] interrupt masking control - RW */
    ureg32 STINTMSK4:1;     /* [4:4] soft_int_core1_o[0] interrupt masking control - RW */
    ureg32 STINTMSK5:1;     /* [5:5] soft_int_core1_o[1] interrupt masking control - RW */
    ureg32 STINTMSK6:1;     /* [6:6] soft_int_core1_o[2] interrupt masking control - RW */
    ureg32 STINTMSK7:1;     /* [7:7] soft_int_core1_o[3] interrupt masking control - RW */
    ureg32 STINTMSK8:1;     /* [8:8] soft_int_core10_o[0] interrupt masking control - RW */
    ureg32 STINTMSK9:1;     /* [9:9] soft_int_core10_o[1] interrupt masking control - RW */
    ureg32 STINTMSK10:1;     /* [10:10] soft_int_core10_o[2] interrupt masking control - RW */
    ureg32 STINTMSK11:1;     /* [11:11] soft_int_core10_o[3] interrupt masking control - RW */
    ureg32 STINTMSK12:1;     /* [12:12] soft_int_core11_o[0] interrupt masking control - RW */
    ureg32 STINTMSK13:1;     /* [13:13] soft_int_core11_o[1] interrupt masking control - RW */
    ureg32 STINTMSK14:1;     /* [14:14] soft_int_core11_o[2] interrupt masking control - RW */
    ureg32 STINTMSK15:1;     /* [15:15] soft_int_core11_o[3] interrupt masking control - RW */
    ureg32 reserved_16:16;   /* [31:16] Internal reserved */
} INTC_STINTMSK_Bits;

/* Bus error mask */
typedef struct
{
    ureg32 BUSERRMSK:1;     /* [0:0] Bus error masking control - RW */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} INTC_BUSERRMSK_Bits;

/* DCC interrupt mask */
typedef struct
{
    ureg32 COMMRX0MSK:1;    /* [0:0] COMMRX0 interrupt mask control - RW */
    ureg32 COMMTX0MSK:1;    /* [1:1] COMMTX0 interrupt mask control - RW */
    ureg32 COMMRX1MSK:1;    /* [2:2] COMMRX1 interrupt mask control - RW */
    ureg32 COMMTX1MSK:1;    /* [3:3] COMMTX1 interrupt mask control - RW */
    ureg32 reserved_4:12;   /* [15:4] Internal reserved */
    ureg32 DCCPSW:16;       /* [31:16] Password of DCCINTMSK register - RW */
} INTC_DCCINTMSK_Bits;


/**********************************************************************************************************************
 *                                   GIC Distributor Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* GIC Distributor control register */
typedef struct
{
    ureg32 ENABLEGRP0:1;  /* [0:0] Enable Group 0 interrupts from the GIC Distributor to the GIC CPU Interface - RW */
    ureg32 ENABLEGRP1:1;  /* [1:1] Enable Group 1 interrupts from the GIC Distributor to the GIC CPU Interface - RW */
    ureg32 reserved_2:2;  /* [3:2] Internal reserved */
    ureg32 ARE:1;         /* [4:4] Affinity Routing Enable - RO */
    ureg32 reserved_5:1;  /* [5:5] Internal reserved */
    ureg32 DS:1;          /* [6:6] Disable Security - RO */
    ureg32 EINWF:1;       /* [7:7] Enable 1 of N Wakeup functionality - RO */
    ureg32 reserved_8:23; /* [30:8] Internal reserved */
    ureg32 RWP:1;         /* [31:31] Register Write Pending - RO */
} INTC_GICD_CTRL_Bits;

/* GIC Distributor interrupt controller typer register */
typedef struct
{
    ureg32 ITLINESNUMBER:5; /* [4:0] Indicates the number of SPI INTIDs that GIC Distributor supports - RO */
    ureg32 CPUNUMBER:3;     /* [7:5] Indicates the number of cores that can be used as interrupt targets when
                               GICD_CTLR.ARE is 0 - RO */
    ureg32 reserved_8:2;    /* [9:8] Internal reserved */
    ureg32 SECURITYEXTN:1;  /* [10:10] Indicates whether the GIC Distributor supports two Security states - RO */
    ureg32 reserved_11:5;   /* [15:11] Internal reserved */
    ureg32 MBIS:1;          /* [16:16] Indicates whether the GIC Distributor supports Message-Based Interrupts
                               Supported - RO */
    ureg32 LPIS:1;          /* [17:17] Indicates whether the GIC Distributor supports Locality-specific Peripheral
                               Interrupts (LPIs) - RO */
    ureg32 DVIS:1;          /* [18:18] Indicates whether the GIC Distributor supports Direct Virtual LPI injection
                               - RO */
    ureg32 IDBITS:5;        /* [23:19] Indicates the number of INTID bits that the GIC Distributor supports,
                               minus one - RO */
    ureg32 A3V:1;           /* [24:24] Indicates whether the GIC Distributor supports nonzero values of Affinity
                               level 3 - RO */
    ureg32 NO1N:1;          /* [25:25] Indicates whether the GIC Distributor supports 1 of N SPIs - RO */
    ureg32 reserved_26:6;   /* [31:26] Internal reserved */
} INTC_GICD_TYPER_Bits;

/* GIC Distributor interrupt routing register */
typedef struct
{
    ureg32 AFF0:8;                 /* [7:0] Affinity level 0 - RW */
    ureg32 AFF1:8;                 /* [15:8] Affinity level 1 - RO */
    ureg32 AFF2:8;                 /* [23:16] Affinity level 2 - RO */
    ureg32 reserved_24:7;          /* [30:24] Internal reserved */
    ureg32 INTERRUPTROUTINGMODE:1; /* [31:31] Interrupt Routing Mode - RW */
    ureg32 AFF3:8;                 /* [39:32] Affinity level 3 - RO */
    ureg32 reserved_40:24;         /* [63:40] Internal reserved */
} INTC_GICD_IROUTER_Bits;

/* GIC Distributor identification register */
typedef struct
{
    ureg32 COMPONENTID:8; /* [7:0] Component ID - RO */
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
} INTC_GICD_PIDR_Bits;

/* GIC Distributor component identification register */
typedef struct
{
    ureg32 COMPONENTID:8; /* [7:0] Component ID - RO */
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
} INTC_GICD_CIDR_Bits;
/**********************************************************************************************************************
 *                                  GIC Redistributor Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* GIC Redistributor control register */
typedef struct
{
    ureg32 ENABLELPIS:1;  /* [0:0] This bit controls whether physical LPIs are enabled - RO */
    ureg32 reserved_1:2;  /* [2:1] Internal reserved */
    ureg32 RWP:1;         /* [3:3] Register Write Pending - RO */
    ureg32 reserved_4:20; /* [23:4] Internal reserved */
    ureg32 DPG0:1;        /* [24:24] Relates to 1 of N distribution which is not supported - RAZ/WI */
    ureg32 DPG1NS:1;      /* [25:25] Relates to 1 of N distribution which is not supported - RAZ/WI */
    ureg32 DPG1S:1;       /* [26:26] Relates to 1 of N distribution which is not supported - RAZ/WI */
    ureg32 reserved_27:4; /* [30:27] Internal reserved */
    ureg32 UWP:1;         /* [31:31] Indicates whether upstream writes are pending - RO */
} INTC_GICR_CTRL_Bits;

/* GIC Redistributor interrupt controller typer register */
typedef struct
{
    ureg32 PLPIS:1;            /* [0:0] Indicates whether the GIC implementation supports physical LPIs - RO */
    ureg32 VLPIS:1;            /* [1:1] Indicates whether the GIC implementation supports virtual
                                  LPIs - RO */
    ureg32 reserved_2:1;       /* [2:2] Internal reserved */
    ureg32 DIRECTLPI:1;        /* [3:3] Indicates whether this Redistributor supports direct injection of LPIs - RO */
    ureg32 LAST:1;             /* [4:4] Indicates whether this Redistributor is the last numbered Redistributor in a
                                 series of contiguous Redistributor pages - RO */
    ureg32 DPGS:1;             /* [5:5] Sets support for GICR_CTLR.DPG* bits - RO */
    ureg32 reserved_6:2;       /* [7:6] Internal reserved */
    ureg32 PROCESSORNUMBER:16; /* [23:8] A unique identifier for the core - RO */
    ureg32 COMMONLPIAFF:2;     /* [25:24] Relates to LPIs which are not supported - RO */
    ureg32 reserved_26:6;      /* [31:26] Internal reserved */
    ureg32 AFF0:8;             /* [39:32] Affinity level 0 - RO */
    ureg32 AFF1:8;             /* [47:40] Affinity level 1 - RO */
    ureg32 AFF2:8;             /* [55:48] Affinity level 2 - RO */
    ureg32 AFF3:8;             /* [63:56] Affinity level 3 - RO */
} INTC_GICR_TYPER_Bits;

/* GIC Redistributor wake register */
typedef struct
{
    ureg32 reserved_0:1;     /* [0:0] Internal reserved */
    ureg32 PROCESSORSLEEP:1; /* [1:1] Instructs the Redistributor that the target is entering the processor sleep state
                                - RW */
    ureg32 CHILDRENASLEEP:1; /* [2:2] Indicates if the connected target is quiescent - RW */
    ureg32 reserved_3:29;    /* [31:3] Internal reserved */
} INTC_GICR_WAKER_Bits;

/* GIC Redistributor identification register */
typedef struct
{
    ureg32 COMPONENTID:8; /* [7:0] Component ID - RO */
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
} INTC_GICR_PIDR_Bits;

/* GIC Redistributor component identification register */
typedef struct
{
    ureg32 COMPONENTID:8; /* [7:0] Component ID - RO */
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
} INTC_GICR_CIDR_Bits;
/**********************************************************************************************************************
 *                                              INTC Register Definitions
 *********************************************************************************************************************/
/* SEMAPEN register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    INTC_SEMAPEN_Bits B; /* Bit-Field access */
} INTC_SEMAPEN;

/* SEMAP register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    INTC_SEMAP_Bits B; /* Bit-Field access */
} INTC_SEMAP;

/* SFINTCR register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    INTC_SFINTCR_Bits B; /* Bit-Field access */
} INTC_SFINTCR;

/* INTCNTEN register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    INTC_INTCNTEN_Bits B; /* Bit-Field access */
} INTC_INTCNTEN;

/* SETPSW register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    INTC_SETPSW_Bits B; /* Bit-Field access */
} INTC_SETPSW;

/* ALMSTS register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    INTC_ALMSTS_Bits B; /* Bit-Field access */
} INTC_ALMSTS;

/* ALMSTS register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    INTC_ALMSTS1_Bits B; /* Bit-Field access */
} INTC_ALMSTS1;

/* ALMCLR register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    INTC_ALMCLR_Bits B; /* Bit-Field access */
} INTC_ALMCLR;

/* ALMEN register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    INTC_ALMEN_Bits B;  /* Bit-Field access */
} INTC_ALMEN;

/* STINTMSK register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    INTC_STINTMSK_Bits B; /* Bit-Field access */
} INTC_STINTMSK;

/* BUSERRMSK register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    INTC_BUSERRMSK_Bits B; /* Bit-Field access */
} INTC_BUSERRMSK;

/* DCCINTMSK register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    INTC_DCCINTMSK_Bits B; /* Bit-Field access */
} INTC_DCCINTMSK;

/**********************************************************************************************************************
 *                                        GIC Distributor Register Definitions
 *********************************************************************************************************************/
/* GICD_CTRL register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    INTC_GICD_CTRL_Bits B; /* Bit-Field access */
} INTC_GICD_CTRL;

/* GICD_TYPER register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    INTC_GICD_TYPER_Bits B; /* Bit-Field access */
} INTC_GICD_TYPER;

/* GICD_IROUTER register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint64 U;                 /* Unsigned access */
    INTC_GICD_IROUTER_Bits B; /* Bit-Field access */
} INTC_GICD_IROUTER;

/* GICD_PIDR register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    INTC_GICD_PIDR_Bits B; /* Bit-Field access */
} INTC_GICD_PIDR;

/* GICD_CIDR register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    INTC_GICD_CIDR_Bits B; /* Bit-Field access */
} INTC_GICD_CIDR;
/**********************************************************************************************************************
 *                                       GIC Redistributor Register Definitions
 *********************************************************************************************************************/
/* GICR_CTRL register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    INTC_GICR_CTRL_Bits B; /* Bit-Field access */
} INTC_GICR_CTRL;

/* GICR_TYPER register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint64 U;               /* Unsigned access */
    INTC_GICR_TYPER_Bits B; /* Bit-Field access */
} INTC_GICR_TYPER;

/* GICR_WAKER register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    INTC_GICR_WAKER_Bits B; /* Bit-Field access */
} INTC_GICR_WAKER;

/* GICR_PIDR register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    INTC_GICR_PIDR_Bits B; /* Bit-Field access */
} INTC_GICR_PIDR;

/* GICR_CIDR register */
/* #Violation: intc_register_h_REF_3 */
typedef union
/* #Violation: intc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    INTC_GICR_CIDR_Bits B; /* Bit-Field access */
} INTC_GICR_CIDR;
/**********************************************************************************************************************
 *                                        INTC Register Configuration Structure
 *********************************************************************************************************************/
typedef volatile struct
{
    INTC_SEMAPEN SEMAPEN;     /* 0x0 - Semaphore enable register */
    /* #Violation: intc_register_h_REF_2 */
    INTC_SEMAP SEMAP[16];      /* 0x4 - Semaphore register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_44[16];   /* 0x44 - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    INTC_SFINTCR SFINTCR[16];  /* 0x84 - Soft interrupt control register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_C4[16];   /* 0xC4 - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 CPUCLCNT[13];       /* 0x104 - CPU clear count control register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_138[18];  /* 0x138 - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 INTCNT[26];        /* 0x180 - Interrupt count register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_1E8[35];  /* 0x1E8 - Internal reserved */
    INTC_INTCNTEN INTCNTEN;   /* 0x274 - Interrupt count enable register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 LEVEDGSEL0[7];      /* 0x278 - Level and edge interrupt set register */
    ureg32 RESERVED_294;      /* 0x294 - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 SETINT[31];        /* 0x298 - Set interrupt register */
    INTC_SETPSW SETPSW;       /* 0x314 - Set interrupt password register */
    INTC_ALMSTS ALMSTS0;       /* 0x318 - Alarm status register */
    INTC_ALMCLR ALMCLR;       /* 0x31C - Alarm clear register */
    INTC_ALMEN ALMEN;         /* 0x320 - Alarm enable register */
    INTC_STINTMSK STINTMSK;   /* 0x324 - Soft interrupt mask */
    INTC_BUSERRMSK BUSERRMSK; /* 0x328 - Bus error mask */
    INTC_DCCINTMSK DCCINTMSK0; /* 0x32C - DCC interrupt mask */
    INTC_DCCINTMSK DCCINTMSK1; /* 0x330 - DCC interrupt mask */
    INTC_ALMSTS1 ALMSTS1;       /* 0x334 - Alarm status register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 LEVEDGSEL1[4];      /* 0x338 - Level and edge interrupt set register */
} INTC_MODULE;

typedef volatile struct
{
    INTC_GICD_CTRL GICDCTRL;            /* 0x0 - Distributor control register */
    INTC_GICD_TYPER GICDTYPER;          /* 0x4 - Interrupt controller typer register */
    ureg32 GICDIIDR;                    /* 0x8 - Distributor Implementer Identification Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_8[30];              /* 0xC - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICDIGROUP[30];              /* 0x84 - Interrupt Group Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_FC[2];              /* 0xFC - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICDISENABLER[30];           /* 0x104 - Interrupt Set-Enable Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_17C[2];             /* 0x17C - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICDICENABLER[30];           /* 0x184 - Interrupt Clear-Enable Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_1FC[2];             /* 0x1FC - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICDISPENDR[30];             /* 0x204 - Interrupt Set-Pending Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_27C[2];             /* 0x27C - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICDICPENDR[30];             /* 0x284 - Interrupt Clear-Pending Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_2FC[2];             /* 0x2FC - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICDISACTIVER[30];           /* 0x304 - Interrupt Set-Active Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_37C[2];             /* 0x37C - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICDICACTIVER[30];           /* 0x384 - Interrupt Clear-Active Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_3FC[9];             /* 0x3FC - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICDIPRIORITYR[240];         /* 0x420 - Interrupt Priority Registers */
    /* #Violation: intc_register_h_REF_2 */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_7E0[266];           /* 0x7E0 - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICDICFGR[60];               /* 0xC08 - Interrupt Configuration Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_CF8[5378];          /* 0xCF8 - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    INTC_GICD_IROUTER GICDIROUTER[960]; /* 0x6100 - Interrupt Routing Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_7EFC[8244];         /* 0x7EFC - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    INTC_GICD_PIDR GICDPIDR[8];         /* 0xFFD0 - Identification Registers */
    /* #Violation: intc_register_h_REF_2 */
    INTC_GICD_CIDR GICDCIDR[4];         /* 0xFFF0 - Component Identification Registers */
} INTC_DISTRIBUTOR_MODULE;

typedef volatile struct
{
    /* offset from address of GICR for control target n : 0x100000 + 2n*0x10000 */
    INTC_GICR_CTRL GICRCTRL;    /* 0x0 - Redistributor Control Register */
    ureg32 GICRIIDR;            /* 0x4 - Redistributor Implementer Identification */
    INTC_GICR_TYPER GICRTYPER;  /* 0x8 - Redistributor Type Register */
    ureg32 RESERVED_10;         /* 0x10 - Internal reserved */
    INTC_GICR_WAKER GICRWAKER;  /* 0x14 - Redistributor Wake Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_18[16366];  /* 0x18 - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    INTC_GICR_PIDR GICRPIDR[8]; /* 0xFFE0 - Redistributor Identification Registers */
    /* #Violation: intc_register_h_REF_2 */
    INTC_GICR_CIDR GICRCIDR[4]; /* 0xFFF0 - Redistributor Component Identification */
    /* offset from address of GICR for SGIs and PPIs target n : 0x110000 + 2n*0x10000 */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_0[32];      /* 0x0 - Internal reserved */
    ureg32 GICRIGROUPR;         /* 0x80 - Interrupt Group Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_84[31];     /* 0x84 - Internal reserved */
    ureg32 GICRISENABLER;       /* 0x100 - Interrupt Set-Enable Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_104[31];    /* 0x104 - Internal reserved */
    ureg32 GICRICENABLER;       /* 0x180 - Interrupt Clear-Enable Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_184[31];    /* 0x184 - Internal reserved */
    ureg32 GICRISPENDR;         /* 0x200 - Interrupt Set-Pending Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_204[31];    /* 0x204 - Internal reserved */
    ureg32 GICRICPENDR;         /* 0x280 - Interrupt Clear-Pending Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_284[31];    /* 0x284 - Internal reserved */
    ureg32 GICRISACTIVER;       /* 0x300 - Interrupt Set-Active Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_304[31];    /* 0x304 - Internal reserved */
    ureg32 GICRICACTIVER;       /* 0x380 - Interrupt Clear-Active Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_384[31];    /* 0x384 - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 GICRIPRIORITY[8];    /* 0x400 - Interrupt Priority Registers */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_420[504];   /* 0x420 - Internal reserved */
    ureg32 GICRICFGR0;          /* 0xC00 - Interrupt Configuration Register */
    ureg32 GICRICFGR1;          /* 0xC04 - Interrupt Configuration Register */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_C08[15614]; /* 0xC08 - Internal reserved */
} INTC_REDISTRIBUTOR_MODULE;

typedef volatile struct
{
    INTC_DISTRIBUTOR_MODULE DISTRIBUTOR;        /* 0x0 - GIC Distributor module */
    /* #Violation: intc_register_h_REF_2 */
    ureg32 RESERVED_10000[245760];              /* 0x10000 - Internal reserved */
    /* #Violation: intc_register_h_REF_2 */
    INTC_REDISTRIBUTOR_MODULE REDISTRIBUTOR[2]; /* 0x100000 - GIC Redistributor module */
} INTC_GIC_MODULE;

#endif /* INTC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

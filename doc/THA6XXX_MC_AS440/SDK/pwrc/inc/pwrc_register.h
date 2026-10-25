/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: pwrc_register.h
 * Author:  00930
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: PWRC module register definition header file.
 *             This file defines the register offsets and bit definitions for the PWRC module.
 ***************************************************************************************************/
/*
*#Violation Summary
*
*#pwrc_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will 
*                be ensured by code review.
*
*/
#ifndef PWRC_REGISTER_H_
#define PWRC_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
#include "Platform_Types.h"

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        PWRC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* PWRC Low Power Control Register */
typedef struct
{
    ureg32 LPMSEL:1;       /* [0:0]  Low Power Mode Select -(RW) */
    ureg32 reserved_1:7;   /* [7:1]  Internal reserved */
    ureg32 UP_EN:1;        /* [8:8]  Bit Update Enable -(WO) */
    ureg32 reserved_9:7;   /* [15:9] Internal reserved */
    ureg32 STBYBLINK:8;    /* [23:16] Standby mode BLNK waiting time -(RW) */
    ureg32 reserved_24:8;  /* [31:24] Internal reserved */
} PWRC_LPCON_Bits;

/* PWRC voltage alarm control Register */
typedef struct
{
    ureg32 VEXTUV:1;       /* [0:0]  VEXT under voltage detect -(RW) */
    ureg32 VDDP3UV:1;      /* [1:1]  VDDP3 under voltage detect -(RW) */
    ureg32 VDDUV:1;        /* [2:2]  VDD under voltage detect -(RW) */
    ureg32 VEVRSBUV:1;     /* [3:3]  VEVRSB under voltage detect -(RW) */
    ureg32 VDDSBUV:1;      /* [4:4]  VDDSB under voltage detect -(RW) */
    ureg32 VDDMUV:1;       /* [5:5]  VDDM under voltage detect -(RW) */
    ureg32 reserved_6:2;   /* [7:6]  Internal reserved */
    ureg32 VEXTOV:1;       /* [8:8]  VEXT over voltage detect -(RW) */
    ureg32 VDDP3OV:1;      /* [9:9]  VDDP3 over voltage detect -(RW) */
    ureg32 VDDOV:1;        /* [10:10]  VDD over voltage detect -(RW) */
    ureg32 VEVRSBOV:1;     /* [11:11]  VEVRSB over voltage detect -(RW) */
    ureg32 VDDSBOV:1;      /* [12:12]  VDDSB over voltage detect -(RW) */
    ureg32 VDDMOV:1;       /* [13:13]  VDDM over voltage detect -(RW) */
    ureg32 reserved_14:2;  /* [15:14]  Internal reserved */
    ureg32 UP_EN:1;        /* [16:16]  Bit Update Enable -(WO) */
    ureg32 reserved_17:15; /* [31:17] Internal reserved */
} PWRC_VLTALMCON_Bits;

/* PWRC ESR1 signal Control Register */
typedef struct
{
    ureg32 ESR1DETSEL:2;   /* [1:0]  ESR1 edge select -(RW) */
    ureg32 ESR1DFEN:1;     /* [2:2]  ESR1 digtal filter enable -(RW) */
    ureg32 reserved_3:29;  /* [31:3] Internal reserved */
} PWRC_ESR1SCON_Bits;

/* PWRC low power mode real time status Register */
typedef struct
{
    ureg32 CPU0WFI:1;       /* [0:0]  CPU0 WFI low power real time indicate -(RO) */
    ureg32 CPU0WFE:1;       /* [1:1]  CPU0 WFE low power real time indicate -(RO) */
    ureg32 CPU1WFI:1;       /* [2:2]  CPU1 WFI low power real time indicate -(RO) */
    ureg32 CPU1WFE:1;       /* [3:3]  CPU1 WFE low power real time indicate -(RO) (THA6412 only) */
    ureg32 CPU2WFI:1;       /* [4:4]  CPU2 WFI low power real time indicate -(RO) (THA6412 only) */
    ureg32 CPU2WFE:1;       /* [5:5]  CPU2 WFE low power real time indicate -(RO) (THA6412 only) */
    ureg32 CPU3WFI:1;       /* [6:6]  CPU3 WFI low power real time indicate -(RO) (THA6412 only) */
    ureg32 CPU3WFE:1;       /* [7:7]  CPU3 WFE low power real time indicate -(RO) (THA6412 only) */
    ureg32 reserved_8:24;   /* [31:8] Internal reserved */
} PWRC_CPULPRTSTS_Bits;

/* PWRC current and voltage alarm real time status Register */
typedef struct
{
    ureg32 VEXTUV:1;              /* [0:0] Under-voltage VEXT alarm -(RO) */
    ureg32 VDDP3UV:1;             /* [1:1]  Under-voltage VDDP3 alarm -(RO) */
    ureg32 VDDUV:1;               /* [2:2]  Under-voltage VDD alarm -(RO) */
    ureg32 VEVRSBUV:1;            /* [3:3]  Under-voltage VEVRSB alarm -(RO) */
    ureg32 VDDSBUV:1;             /* [4:4]  Under-voltage VDDSB alarm -(RO) */
    ureg32 VDDMUV:1;              /* [5:5]  Under-voltage VDDM alarm -(RO) */
    ureg32 reserved_6:2;          /* [7:6] Internal reserved */
    ureg32 VEXTOV:1;              /* [8:8] Over-voltage VEXT alarm -(RO) */
    ureg32 VDDP3OV:1;             /* [9:9]  Over-voltage VDDP3 alarm -(RO) */
    ureg32 VDDOV:1;               /* [10:10]  Over-voltage VDD alarm -(RO) */
    ureg32 VEVRSBOV:1;            /* [11:11]  Over-voltage VEVRSB alarm -(RO) */
    ureg32 VDDSBOV:1;             /* [12:12]  Over-voltage VDDSB alarm -(RO) */
    ureg32 VDDMOV:1;              /* [13:13]  Over-voltage VDDM alarm -(RO) */
    ureg32 reserved_14:3;         /* [16:14] Internal reserved */
    ureg32 VDDOCP:1;              /* [17:17]  VDD overcurrent protect alarm -(RO) */
    ureg32 VDDSCP:1;              /* [18:18]  VDD short circuit protect alarm -(RO) */
    ureg32 VDDP3OCP:1;            /* [19:19]  VDDP3 overcurrent protect alarm -(RO) */
    ureg32 VDDP3SCP:1;            /* [20:20]  VDDP3 short circuit protect alarm -(RO) */
    ureg32 reserved_21:11;        /* [31:21] Internal reserved */
} PWRC_CURVLTALMRTSTS_Bits;

/* PWRC PBIST2 voltage self detect alarm real time status Register */
typedef struct
{
    ureg32 ALLOV:1;             /* [0:0] PBIST2 over-voltage state  -(RO) */
    ureg32 VEXTOV:1;            /* [1:1] VEXT PBIST2 over-voltage state  -(RO) */
    ureg32 VDDP3OV:1;           /* [2:2] VDDP3 PBIST2 over-voltage state  -(RO) */
    ureg32 VDDOV:1;             /* [3:3] VDD PBIST2 over-voltage state  -(RO) */
    ureg32 VEVRSBOV:1;          /* [4:4] VEVRSB PBIST2 over-voltage state  -(RO) */
    ureg32 VDDSBOV:1;           /* [5:5] VDDSB PBIST2 over-voltage state  -(RO) */
    ureg32 reserved_6:26;       /* [31:6] Internal reserved */
} PWRC_PBIST2ALMRTSTS_Bits;

/* PWRC CPU active real time status Register */
typedef struct
{
    ureg32 CPU0PACTIVESTS:1;    /* [0:0]  CPU0 Pactive state -(RO) */
    ureg32 CPU1PACTIVESTS:1;    /* [1:1]  CPU1 Pactive state -(RO) */
    ureg32 CPU2PACTIVESTS:1;    /* [2:2]  CPU2 Pactive state -(RO) (THA6412 only) */
    ureg32 CPU3PACTIVESTS:1;    /* [3:3]  CPU3 Pactive state -(RO) (THA6412 only) */
    ureg32 reserved_4:28;       /* [31:4] Internal reserved */
} PWRC_CPUACTRTSTS_Bits;

/* PWRC ESR1 status Register */
typedef struct
{
    ureg32 ESR1STS:1;       /* [0:0]  ESR1 edge detect status -(RO) */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} PWRC_ESR1STS_Bits;

/* PWRC ESR1 interrupt mask Register */
typedef struct
{
    ureg32 SEICPU0MSK:1;            /* [0:0] ESR1 SEI interrupt to CPU0 mask  -(RW) */
    ureg32 SEICPU1MSK:1;            /* [1:1] ESR1 SEI interrupt to CPU1 mask  -(RW) */
    ureg32 INTMSK:1;                /* [2:2] ESR1 interrupt mask  -(RW) */
    ureg32 SEICPU2MSK:1;            /* [3:3] ESR1 SEI interrupt to CPU2 mask  -(RW) (THA6412 only) */
    ureg32 SEICPU3MSK:1;            /* [4:4] ESR1 SEI interrupt to CPU3 mask  -(RW) (THA6412 only) */
    ureg32 reserved_5:27;           /* [31:5] Internal reserved */
} PWRC_ESR1INTMSK_Bits;

/* PWRC ESR1 interrupt clear Register */
typedef struct
{
    ureg32 CLR:1;           /* [0:0]  ESR1 interrupt clear -(WO) */
    ureg32 reserved_1:31;   /* [31:1] Internal reserved */
} PWRC_ESR1INTCLR_Bits;

/* PWRC low power mode interrupt status Register */
typedef struct
{
    ureg32 CPU0WFI:1;       /* [0:0]  CPU0 enter to WFI -(RO) */
    ureg32 CPU0WFE:1;       /* [1:1]  CPU0 enter to WFE -(RO) */
    ureg32 CPU1WFI:1;       /* [2:2]  CPU1 enter to WFI -(RO) */
    ureg32 CPU1WFE:1;       /* [3:3]  CPU1 enter to WFE -(RO) */
    ureg32 CPU2WFI:1;       /* [4:4]  CPU2 enter to WFI -(RO) (THA6412 only) */
    ureg32 CPU2WFE:1;       /* [5:5]  CPU2 enter to WFE -(RO) (THA6412 only) */
    ureg32 CPU3WFI:1;       /* [6:6]  CPU3 enter to WFI -(RO) (THA6412 only) */
    ureg32 CPU3WFE:1;       /* [7:7]  CPU3 enter to WFE -(RO) (THA6412 only) */
    ureg32 reserved_8:24;   /* [31:8] Internal reserved */
}PWRC_CPULPINTSTS_Bits;

/* CPU low power mode interrupt mask register */
typedef struct
{
    ureg32 MSK:8;         /* [7:0]  CPU low power mode interrupt mask - (RW) (THA6106: bit3 ~ bit0) */
    ureg32 reserved_8:24; /* [31:8]  Internal reserved  */
} PWRC_CPULPINTMSK_Bits;

/* CPU low power mode interrupt clear register */
typedef struct
{
    ureg32 CLR:8;         /* [7:0]  CPU low power mode interrupt clear - (WO) (THA6106: bit3 ~ bit0) */
    ureg32 reserved_8:24; /* [31:8]  Internal reserved  */
} PWRC_CPULPINTCLR_Bits;

/* PWRC current and voltage status Register */
typedef struct
{
    ureg32 VEXTUV:1;              /* [0:0] Under-voltage VEXT alarm -(RO) */
    ureg32 VDDP3UV:1;             /* [1:1]  Under-voltage VDDP3 alarm -(RO) */
    ureg32 VDDUV:1;               /* [2:2]  Under-voltage VDD alarm -(RO) */
    ureg32 VEVRSBUV:1;            /* [3:3]  Under-voltage VEVRSB alarm -(RO) */
    ureg32 VDDSBUV:1;             /* [4:4]  Under-voltage VDDSB alarm -(RO) */
    ureg32 VDDMUV:1;              /* [5:5]  Under-voltage VDDM alarm -(RO) */
    ureg32 reserved_6:2;          /* [7:6] Internal reserved */
    ureg32 VEXTOV:1;              /* [8:8] Over-voltage VEXT alarm -(RO) */
    ureg32 VDDP3OV:1;             /* [9:9]  Over-voltage VDDP3 alarm -(RO) */
    ureg32 VDDOV:1;               /* [10:10]  Over-voltage VDD alarm -(RO) */
    ureg32 VEVRSBOV:1;            /* [11:11]  Over-voltage VEVRSB alarm -(RO) */
    ureg32 VDDSBOV:1;             /* [12:12]  Over-voltage VDDSB alarm -(RO) */
    ureg32 VDDMOV:1;              /* [13:13]  Over-voltage VDDM alarm -(RO) */
    ureg32 reserved_14:2;         /* [15:14] Internal reserved */
    ureg32 VDDOCP:1;              /* [16:16]  VDD overcurrent protect alarm -(RO) */
    ureg32 VDDSCP:1;              /* [17:17]  VDD short circuit protect alarm -(RO) */
    ureg32 VDDP3OCP:1;            /* [18:18]  VDDP3 overcurrent protect alarm -(RO) */
    ureg32 VDDP3SCP:1;            /* [19:19]  VDDP3 short circuit protect alarm -(RO) */
    ureg32 reserved_20:12;        /* [31:20] Internal reserved */
} PWRC_CURVLTSTS_Bits;

/* PWRC current and voltage interrupt mask Register */
typedef struct
{
    ureg32 UVMSK:6;               /* [5:0]  Current and voltage interrupt mask - (RW) */
    ureg32 reserved_6:2;          /* [7:6]  Internal reserved  */
    ureg32 OVMSK:6;               /* [13:8]  Current and voltage interrupt mask - (RW) */
    ureg32 reserved_14:2;         /* [15:14]  Internal reserved  */
    ureg32 CMSK:4;                /* [19:16]  Current and voltage interrupt mask - (RW) */
    ureg32 reserved_20:12;        /* [31:20]  Internal reserved  */
} PWRC_CURVLTINTMSK_Bits;

/* PWRC current and voltage alarm mask Register */
typedef struct
{
    ureg32 UVMSK:6;        /* [5:0]  Current and voltage alarm mask - (RW) */
    ureg32 reserved_6:2;   /* [7:6]  Internal reserved  */
    ureg32 OVMSK:6;        /* [13:8]  Current and voltage alarm mask - (RW) */
    ureg32 reserved_14:2;  /* [15:14]  Internal reserved  */
    ureg32 CMSK:4;         /* [19:16]  Current alarm mask - (RW) */
    ureg32 reserved_20:12; /* [31:20]  Internal reserved  */
} PWRC_CURVLTALMMSK_Bits;

/* PWRC current and voltage clear Register */
typedef struct
{
    ureg32 UVCLR:6;         /* [5:0]  Current and voltage alarm clear - (WO) */
    ureg32 reserved_6:2;    /* [7:6]  Internal reserved  */
    ureg32 OVCLR:6;         /* [13:8]  Current and voltage alarm clear - (WO) */
    ureg32 reserved_14:2;   /* [15:14]  Internal reserved  */
    ureg32 CCLR:4;          /* [19:16]  Current alarm clear - (WO) */
    ureg32 reserved_20:12;  /* [31:20]  Internal reserved  */
} PWRC_CURVLTCLR_Bits;

/* PWRC Voltage detect threshold coarse adjustment Register */
typedef struct
{
    ureg32 VEXT_ADJ:3;            /* [2:0] VEXT threshold adjustment -(RW) */
    ureg32 reserved_3:1;          /* [3:3] Internal reserved */
    ureg32 VDDP3_ADJ:2;           /* [5:4] VDDP3 threshold adjustment -(RW) */
    ureg32 reserved_6:2;          /* [7:6] Internal reserved */
    ureg32 VDD_ADJ:3;             /* [10:8] VDD threshold adjustment -(RW) */
    ureg32 reserved_11:1;         /* [11:11] Internal reserved */
    ureg32 VEVRSB_ADJ:3;          /* [14:12] VEVRSB threshold adjustment -(RW) */
    ureg32 reserved_15:1;         /* [15:15] Internal reserved */
    ureg32 VDDSB_ADJ:3;           /* [18:16] VDDSB threshold adjustment -(RW) */
    ureg32 reserved_19:1;         /* [19:19] Internal reserved */
    ureg32 VDDM_ADJ:3;            /* [22:20] VDDM threshold adjustment -(RW) */
    ureg32 reserved_23:1;         /* [23:23] Internal reserved */
    ureg32 UP_EN:1;               /* [24:24] Bit update enable -(W) */
    ureg32 reserved_25:7;         /* [31:25] Internal reserved */
} PWRC_DETADJ_Bits;

/* PWRC Voltage detect threshold fine adjustment Register */
typedef struct
{
    ureg32 VEXT_SHIFT:3;          /* [2:0] VEXT threshold adjustment -(RW) */
    ureg32 reserved_3:1;          /* [3:3] Internal reserved */
    ureg32 VDDP3_SHIFT:3;         /* [6:4] VDDP3 threshold adjustment -(RW) */
    ureg32 reserved_7:1;          /* [7:7] Internal reserved */
    ureg32 VDD_SHIFT:3;           /* [10:8] VDD threshold adjustment -(RW) */
    ureg32 reserved_11:1;         /* [11:11] Internal reserved */
    ureg32 VEVRSB_SHIFT:3;        /* [14:12] VEVRSB threshold adjustment -(RW) */
    ureg32 reserved_15:1;         /* [15:15] Internal reserved */
    ureg32 VDDSB_SHIFT:3;         /* [18:16] VDDSB threshold adjustment -(RW) */
    ureg32 reserved_19:1;         /* [19:19] Internal reserved */
    ureg32 VDDM_SHIFT:3;          /* [22:20] VDDM threshold adjustment -(RW) */
    ureg32 reserved_23:1;         /* [23:23] Internal reserved */
    ureg32 UP_EN:1;               /* [24:24] Bit update enable -(W) */
    ureg32 reserved_25:7;         /* [31:25] Internal reserved */
} PWRC_DETEADJ_Bits;

/* PWRC ADC reference current control Register */
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
typedef struct
{
    ureg32 IREF_EN:1;      /* [0:0]  DSADC reference current enable - (RW) */
    ureg32 reserved_1:1;   /* [1:1]  Internal reserved  */
    ureg32 FC_TEST_EN:1;   /* [2:2]  High precision BGR12 FC test enable -(RW) */
    ureg32 reserved_3:29;  /* [31:3]  Internal reserved  */
} PWRC_ADCREFC_Bits;
#endif
#if defined(THA6_THA6104)
typedef struct
{
    ureg32 reserved_0:2;      /* [1:0]  Internal reserved */
    ureg32 FLASH_VERF_EN:1;   /* [2:2]  Enable control of Flash 1V reference voltage VREF -(RW) */
    ureg32 reserved_3:29;     /* [31:3]  Internal reserved  */
} PWRC_ADCREFC_Bits;
#endif
/* PWRC debug mode low power configure */
typedef struct
{
    ureg32 DBGEN:4;       /* [3:0]  Debug mode low power enable - (RW) */
    ureg32 reserved_4:28; /* [31:4]  Internal reserved  */
} PWRC_DBGC_Bits;

/* PWRCSTB Standby Mode Main Domain Protection Register */
typedef struct
{
    ureg32 STDP:8;            /* [7:0] Standby Protect Enable (RW) */
    ureg32 reserved_8:24;     /* [31:8] Internal Reserved */
} PWRCSTB_STDP_Bits;

/* PWRCSTB HWCFG Status Register */
typedef struct
{
    ureg32 HWCFG1:1;          /* [0:0] HWCFG1 Level Status (R) */
    ureg32 HWCFG2:1;          /* [1:1] HWCFG2 Level Status (R) */
    ureg32 HWCFG6:1;          /* [2:2] HWCFG6 Level Status (R) */
    ureg32 HWCFG0:1;          /* [3:3] HWCFG0 Level Status (R) */
    ureg32 reserved_3:28;     /* [31:4] Internal Reserved */
} PWRCSTB_HWCFGSTS_Bits;

/* PWRCSTB hardware default configuration 6 status control Register*/
typedef struct
{
    ureg32 TRISTREQ:1;      /* [0:0]  Port tri-status require - (RW) */
    ureg32 reserved_1:7;    /* [7:1]  Internal reserved  */
    ureg32 TRIST:1;         /* [8:8]  Port tri-status - (RH) */
    ureg32 reserved_9:23;   /* [31:9]  Internal reserved  */
} PWRCSTB_DPCR_Bits;

/* PWRCSTB Standby Wake-Up Control Register */
typedef struct
{
    ureg32 ESR0WKEN:1;          /* [0:0] ESR0 Wake-up enable from Standby (RW) */
    ureg32 ESR1WKEN:1;          /* [1:1] ESR1 Wake-up enable from Standby (RW) */
    ureg32 PINAWKEN:1;          /* [2:2] PINA Wake-up enable from Standby (RW) */
    ureg32 PINBWKEN:1;          /* [3:3] PINB Wake-up enable from Standby (RW) */
    ureg32 reserved_4:1;        /* [4:4]  Internal reserved  */
    ureg32 PORSTWKEN:1;         /* [5:5] PORST Wake-up enable from Standby (RW) */
    ureg32 IWDGWKEN:1;          /* [6:6] IWDG Wake-up enable from Standby (RW) */
    ureg32 PWRWKEN:1;           /* [7:7] VEXT Wake-up enable from Standby (RW) */
    ureg32 ESR0DFEN:1;          /* [8:8] ESR0 Digital Filter Enable  (RW) */
    ureg32 ESR1DFEN:1;          /* [9:9] ESR1 Digital Filter Enable  (RW) */
    ureg32 PINADFEN:1;          /* [10:10] PINA Digital Filter Enable  (RW) */
    ureg32 PINBDFEN:1;          /* [11:11] PINB Digital Filter Enable  (RW) */
    ureg32 reserved_12:1;       /* [12:12]  Internal reserved  */
    ureg32 PORSTDFEN:1;         /* [13:13] PORST Digital Filter Enable  (RW) */
    ureg32 STIODFEN:1;          /* [14:14] Standby IO digital filter enable (RW) (THA6412 only) */
    ureg32 reserved_15:1;       /* [15:15]internal Reserved */
    ureg32 ESR0EDCON:2;         /* [17:16] ESR0 Edge Detection Control  (RW) */
    ureg32 ESR1EDCON:2;         /* [19:18] ESR1 Edge Detection Control  (RW) */
    ureg32 PINAEDCON:2;         /* [21:20] PINA Edge Detection Control  (RW) */
    ureg32 PINBEDCON:2;         /* [23:22] PINB Edge Detection Control  (RW) */
    ureg32 reserved_24:2;       /* [25:24]internal Reserved */
    ureg32 PORSTEDCON:2;        /* [27:26] PORST Edge Detection Control (RW) */
    ureg32 reserved_28:4;       /* [31:28] Internal Reserved */
} PWRCSTB_WKUPC_Bits;

/* PWRCSTB Standby Wake Up Time Control Register */
typedef struct
{
    ureg32 BLNKFIL:4;            /* [3:0] Blanking Filter delay for Wake-up (RW) */
    ureg32 BLNKFIL_ALL:1;        /* [4:4] Blanking Filter delay enable (RW) */
    ureg32 reserved_5:3;         /* [7:5] Internal Reserved */
    ureg32 RSTTIME:8;            /* [15:8] Reset time from Standby (RW) */
    ureg32 reserved_16:16;       /* [31:16] Internal Reserved */
} PWRCSTB_WKUPTIM_Bits;

/* PWRCSTB Standby Wake-Up Status Register */
typedef struct
{
    ureg32 ESR0_TRG:1;          /* [0:0] ESR0 Wake-up Flag (RW) */
    ureg32 ESR1_TRG:1;          /* [1:1] ESR1 Wake-up Flag (RW) */
    ureg32 PINA_TRG:1;          /* [2:2] PINA Wake-up Flag (RW) */
    ureg32 PINB_TRG:1;          /* [3:3] PINB Wake-up Flag (RW) */
    ureg32 reserved_4:1;        /* [4:4]  Internal reserved  */
    ureg32 PORST_TRG:1;         /* [5:5] PORST Wake-up Flag (RW) */
    ureg32 IWDG_TRG:1;          /* [6:6] IWDG Wake-up Flag (RW) */
    ureg32 VEXTUP_TRG:1;        /* [7:7] VEXT Wake-up Flag (RW) */
    ureg32 STBY_RDY:1;          /* [8:8] Standby Domain's Clock and reset is Ready (RW) */
    ureg32 STBY_FLAG:1;         /* [9:9] Standby Event Flag (RW) */
    ureg32 reserved_10:22;      /* [31:10] internal Reserved */
} PWRCSTB_WKUPSTS_Bits;

/* PWRCSTB IP low power status Control Register*/
typedef struct
{
    ureg32 reserved_0:12;  /* [11:0]  Internal reserved  */
    ureg32 LS_H2L_PD:1;    /* [12:12] Level shifter high to low enable - (RWH) */
    ureg32 reserved_13:19; /* [31:13]  Internal reserved  */
} PWRCSTB_IPPC_Bits;

/* PWRCSTB standby IO low power state wakeup control Register 0 (THA6412 only) */
typedef struct
{
    ureg32 P33_00_PAD_TRG:2;             /* [1:0] Standby IO edge wakeup control (RW) */
    ureg32 P33_01_PAD_TRG:2;             /* [3:2] Standby IO edge wakeup control (RW) */
    ureg32 P33_02_PAD_TRG:2;             /* [5:4] Standby IO edge wakeup control (RW) */
    ureg32 P33_03_PAD_TRG:2;             /* [7:6] Standby IO edge wakeup control (RW) */
    ureg32 P33_04_PAD_TRG:2;             /* [9:8] Standby IO edge wakeup control (RW) */
    ureg32 P33_05_PAD_TRG:2;             /* [11:10] Standby IO edge wakeup control (RW) */
    ureg32 P33_06_PAD_TRG:2;             /* [13:12] Standby IO edge wakeup control (RW) */
    ureg32 P33_07_PAD_TRG:2;             /* [15:14] Standby IO edge wakeup control (RW) */
    ureg32 P33_08_PAD_TRG:2;             /* [17:16] Standby IO edge wakeup control (RW) */
    ureg32 P33_09_PAD_TRG:2;             /* [19:18] Standby IO edge wakeup control (RW) */
    ureg32 P33_10_PAD_TRG:2;             /* [21:20] Standby IO edge wakeup control (RW) */
    ureg32 P33_11_PAD_TRG:2;             /* [23:22] Standby IO edge wakeup control (RW) */
    ureg32 reserved_24:2;                /* [25:24]internal Reserved */
    ureg32 P33_13_PAD_TRG:2;             /* [27:26] Standby IO edge wakeup control (RW) */
    ureg32 P33_14_PAD_TRG:2;             /* [29:28] Standby IO edge wakeup control (RW) */
    ureg32 P33_15_PAD_TRG:2;             /* [31:30] Standby IO edge wakeup control (RW) */
} PWRCSTB_STIOWKUPC0_Bits;

/* PWRCSTB standby IO low power state wakeup control Register 1 (THA6412 only) */
typedef struct
{
    ureg32 P34_01_PAD_TRG:2;             /* [1:0] Standby IO edge wakeup control (RW) */
    ureg32 P34_02_PAD_TRG:2;             /* [3:2] Standby IO edge wakeup control (RW) */
    ureg32 P34_03_PAD_TRG:2;             /* [5:4] Standby IO edge wakeup control (RW) */
    ureg32 P34_04_PAD_TRG:2;             /* [7:6] Standby IO edge wakeup control (RW) */
    ureg32 P34_05_PAD_TRG:2;             /* [9:8] Standby IO edge wakeup control (RW) */
    ureg32 reserved_10:22;               /* [31:10]internal Reserved */
 } PWRCSTB_STIOWKUPC1_Bits;

 /* PWRCSTB standby IO low power state wakeup status Register (THA6412 only) */
 typedef struct
 {
     ureg32 P34_01_PAD_TRG:1;             /* [0:0] Wakeup status query (RW1C) */
     ureg32 P34_02_PAD_TRG:1;             /* [1:1] Wakeup status query (RW1C) */
     ureg32 P34_03_PAD_TRG:1;             /* [2:2] Wakeup status query (RW1C) */
     ureg32 P34_04_PAD_TRG:1;             /* [3:3] Wakeup status query (RW1C) */
     ureg32 P34_05_PAD_TRG:1;             /* [4:4] Wakeup status query (RW1C) */
     ureg32 P33_00_PAD_TRG:1;             /* [5:5] Wakeup status query (RW1C) */
     ureg32 P33_01_PAD_TRG:1;             /* [6:6] Wakeup status query (RW1C) */
     ureg32 P33_02_PAD_TRG:1;             /* [7:7] Wakeup status query (RW1C) */
     ureg32 P33_03_PAD_TRG:1;             /* [8:8] Wakeup status query (RW1C) */
     ureg32 P33_04_PAD_TRG:1;             /* [9:9] Wakeup status query (RW1C) */
     ureg32 P33_05_PAD_TRG:1;             /* [10:10] Wakeup status query (RW1C) */
     ureg32 P33_06_PAD_TRG:1;             /* [11:11] Wakeup status query (RW1C) */
     ureg32 P33_07_PAD_TRG:1;             /* [12:12] Wakeup status query (RW1C) */
     ureg32 P33_08_PAD_TRG:1;             /* [13:13] Wakeup status query (RW1C) */
     ureg32 P33_09_PAD_TRG:1;             /* [14:14] Wakeup status query (RW1C) */
     ureg32 P33_10_PAD_TRG:1;             /* [15:15] Wakeup status query (RW1C) */
     ureg32 P33_11_PAD_TRG:1;             /* [16:16] Wakeup status query (RW1C) */
     ureg32 reserved_17:1;                /* [17:17]internal Reserved */
     ureg32 P33_13_PAD_TRG:1;             /* [18:18] Wakeup status query (RW1C) */
     ureg32 P33_14_PAD_TRG:1;             /* [19:19] Wakeup status query (RW1C) */
     ureg32 P33_15_PAD_TRG:1;             /* [20:20] Wakeup status query (RW1C) */
     ureg32 reserved_21:11;               /* [31:21]internal Reserved */
} PWRCSTB_STIOWKUSTS_Bits;

/* PWRCSTB Voltage Select Register (THA6412 & THA6206 only) */
typedef struct
{
    ureg32 VDD_SEL:3;             /* [2:0] Select VDD Level (RW) */
    ureg32 reserved_3:5;          /* [7:3] Internal Reserved */
    ureg32 VDDP3_SEL:3;           /* [10:8] Select VDDP3 Level (RW) */
    ureg32 reserved_11:5;         /* [15:11]internal Reserved */
    ureg32 VDDSB_SEL:3;           /* [18:16] Select VDDSB Voltage Value (RW) */
    ureg32 reserved_19:1;         /* [19:19] Internal Reserved */
    ureg32 UP_EN:1;               /* [20:20] Update Register Enable (RW) */
    ureg32 reserved_21:11;        /* [31:21] internal Reserved */
} PWRCSTB_VOSEL_Bits;

/* PWRCSTB Primary Detection Control Register */
typedef struct
{
    ureg32 VEXT_DIS:1;             /* [0:0] VEXT Primary Supply Detection Control (RW) */
    ureg32 VDDP3_DIS:1;            /* [1:1] VDDP Primary Supply Detection Control (RW) */
    ureg32 VDD_DIS:1;              /* [2:2] VDD Primary Supply Detection Control  (RW) */
    ureg32 reserved_3:5;           /* [7:3] Internal Reserved */
    ureg32 UP_EN:1;                /* [8:8] Update Register Enable (RW) */
    ureg32 reserved_9:23;          /* [31:9] Internal Reserved */
} PWRCSTB_PRIMRYDC_Bits;

/* PWRCSTB Voltage Detection Control Register */
typedef struct
{
    ureg32 VEXT_UV_DIS:1;              /* [0:0] VEXT Supply Under-voltage Self-Detection Disable (RW) */
    ureg32 VDDP3_UV_DIS:1;             /* [1:1] VDDP3 Supply Under-voltage Self-Detection Disable (RW) */
    ureg32 VDD_UV_DIS:1;               /* [2:2] VDD Supply Under-voltage Self-Detection Disable (RW) */
    ureg32 VEVRSB_UV_DIS:1;            /* [3:3] VEVRSB Supply Under-voltage Self-Detection Disable (RW) */
    ureg32 VDDSB_UV_DIS:1;             /* [4:4] VDDSB Supply Under-voltage Self-Detection Disable (RW) */
    ureg32 reserved_5:3;               /* [7:5] Internal Reserved */
    ureg32 VEXT_OV_DIS:1;              /* [8:8] VEXT Supply Over-voltage Self-Detection Disable (RW) */
    ureg32 VDDP3_OV_DIS:1;             /* [9:9] VDDP3 Supply Over-voltage Self-Detection Disable (RW) */
    ureg32 VDD_OV_DIS:1;               /* [10:10]  VDD Supply Over-voltage Self-Detection Disable (RW) */
    ureg32 VEVRSB_OV_DIS:1;            /* [11:11]  VEVRSB Supply Over-voltage Self-Detection Disable (RW) */
    ureg32 VDDSB_OV_DIS:1;             /* [12:12]  VDDSB Supply Over-voltage Self-Detection Disable (RW) */
    ureg32 reserved_13:3;              /* [15:13] Internal Reserved */
    ureg32 UPEN:1;                     /* [16:16] Update Register Enable (RW) */
    ureg32 reserved_17:15;             /* [31:17] Internal Reserved */
} PWRCSTB_PBIST2DC_Bits;

/* PWRCSTB EVR DCDC Control Register */
typedef struct
{
    ureg32 DCDC_EN:2;            /* [1:0] DC-DC Supply Software Enable (RW) */
    ureg32 OCP_EN:1;             /* [2:2] DC-DC Over Current Protection Detection Enable (RW) */
    ureg32 SCP_EN:1;             /* [3:3] DC-DC Short Circuit Protection Detection Enable  (RW) */
    ureg32 DRV_SEL:1;            /* [4:4] DC-DC Pull-Down Node Enable  (RW) */
    ureg32 DDCDC_RITRIMLV:2;     /* [6:5] DC-DC Ri-VS Resistor  (RW) */
    ureg32 DCDC_PERI_SELLV:2;    /* [8:7] DC-DC Ri-PE voltage dividing Resistor select (RW) */
    ureg32 SLEEP:1;              /* [9:9] DC-DC Low Driver Enable */
    ureg32 UP_EN:1;              /* [10:10] Update Register Enable (RW) */
    ureg32 reserved_11:21;       /* [31:11] Internal Reserved */
} PWRCSTB_EVRC_Bits;

/* PWRCSTB EVR33 Control Register */
typedef struct
{
    ureg32 EVR33_EN:2;           /* [1:0] EVR33 Supply Software Enable (RW) */
    ureg32 OCP_EN:1;             /* [2:2] EVR33 Over Current Protection Detection Enable (RW) */
    ureg32 SCP_EN:1;             /* [3:3] EVR33 Short Circuit Protection Detection Enable  (RW) */
    ureg32 DISCHG1_EN:1;         /* [4:4] EVR33 Discharge1 Enable  (RW) */
    ureg32 DISCHG2_EN:1;         /* [5:5] EVR33 Discharge2 Enable  (RW) */
    ureg32 reserved_6:1;         /* [6:6]Internal Reserved */
    ureg32 UP_EN:1;              /* [7:7] Update Register Enable (RW) */
    ureg32 reserved_8:24;        /* [31:8] Internal Reserved */
} PWRCSTB_EVR33C_Bits;

/* PWRCSTB EVRSB Control Register */
typedef struct
{
    ureg32 VDDSB_THRD_SEL:1;     /* [0:0] VDDSB PBIST Detection Threshold Value (RW) */
    ureg32 reserved_1:6;         /* [6:1] Internal Reserved */
    ureg32 UP_EN:1;              /* [7:7] Update Register Enable (RW) */
    ureg32 reserved_8:24;        /* [31:8] Internal Reserved */
} PWRCSTB_EVRSBVC_Bits;

/* PWRCSTB Reference Voltage Control Register */
typedef struct
{
    ureg32 HPBGR_DIS:1;          /* [0:0] High Precision BGR Disable (RW) */
    ureg32 BGRCMP_DIS:1;         /* [1:1] High & Low Precision Compare Disable (RW) */
    ureg32 reserved_2:5;         /* [6:2] Internal Reserved */
    ureg32 UP_EN:1;              /* [7:7] Update Register Enable (RW) */
    ureg32 reserved_8:24;        /* [31:8] Internal Reserved */
} PWRCSTB_REFC_Bits;

#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
/* PWRCSTB EVRC SREFpread spectrum clock Control Register */
typedef struct
{
    ureg32 SPSP:4;        /* [3:0]  Spread spectrum clock - (RW) */
    ureg32 SPSP_EN:1;     /* [4:4]  Spread spectrum cycle enable - (RW) */
    ureg32 SPSP_STEP:3;   /* [7:5]  Spread spectrum cycle - (RW) */
    ureg32 reserved_8:24; /* [31:8]  Internal reserved  */
} PWRCSTB_EVRCCK_Bits;

/* PWRCSTB Safety Alarm Status Register */
typedef struct
{
    ureg32 reserved_0:14;   /* [13:0] Internal reserved (R) */
    ureg32 FSM:1;           /* [14:14] FSM Illegial Jump (RH) */
    ureg32 E:1;             /* [15:15] E Illegal Access (RH) */
    ureg32 SE:1;            /* [16:16] SE Illegal Access (RH) */
    ureg32 reserved_17:15;  /* [31:17]  Internal reserved (R) */
} PWRCSTB_ALMS_Bits;

/* PWRCSTB Safety Alarm Enable Register */
typedef struct
{
    ureg32 reserved_0:1;    /* [0:0]  Internal reserved (RW) */
    ureg32 FSMEN:1;         /* [1:1]  FSM Illegal Jump Enable (RW) */
    ureg32 reserved_2:30;   /* [31:2]  Internal reserved (R) */
} PWRCSTB_ALME_Bits;

/* PWRCSTB Safety Alarm Clear Register */
typedef struct
{
    ureg32 reserved_0:2;    /* [1:0]  Internal reserved (R) */
    ureg32 FSMCLR:1;        /* [2:2]  FSM ILLEGAL Jump Clear (W) */
    ureg32 reserved_3:1;    /* [3:3]  Internal reserved (R) */
    ureg32 ECLR:1;          /* [4:4]  E ILLEGAL Access Clear (W) */
    ureg32 reserved_5:1;    /* [5:5]  Internal reserved (R) */
    ureg32 SECLR:1;         /* [6:6]  SE ILLEGAL Access Clear (W) */
    ureg32 reserved_2:25;   /* [31:7]  Internal reserved (R) */
} PWRCSTB_ALMC_Bits;

/* PWRCSTB Safety Alarm Injection Register */
typedef struct
{
    ureg32 reserved_0:2;      /* [1:0]  Internal reserved (RW) */
    ureg32 FSMERRIN:2;        /* [3:2]  Redundancy injection- (RW) */
    ureg32 reserved_4:28;     /* [31:4]  Internal reserved (R) */
} PWRCSTB_ERRINS_Bits;

/* PWRCSTB Bus Error Mask Register */
typedef struct
{
    ureg32 BEMSKS:1;        /* [0:0]  Bus error mask (RW) */
    ureg32 reserved_1:30;   /* [31:1]  Internal reserved (R) */
} PWRCSTB_BEMSKS_Bits;
#endif

#if defined(THA6_THA6104)
/* PWRCSTB EVRC SREFpread spectrum clock Control Register */
typedef struct
{
    ureg32 reserved_0:3;  /* [2:0]  Internal reserved  */
    ureg32 SPSP:1;        /* [3:3]  Spread spectrum clock - (RW) */
    ureg32 reserved_8:28; /* [31:4]  Internal reserved  */
} PWRCSTB_EVRCCK_Bits;

/* PWRCSTB Safety Alarm Status Register */
typedef struct
{
    ureg32 ERRINS:1;        /* [0:0] ERRINS Redundancy Alarm Status (RH) */
    ureg32 ALMC:1;          /* [1:1] ALMC Redundancy Alarm Status (RH) */
    ureg32 ALME:1;          /* [2:2] ALME Redundancy Alarm Status(RH) */
    ureg32 REFC:1;          /* [3:3] REFC Redundancy Alarm Status (RH) */
    ureg32 VEVRSBVC:1;      /* [4:4] VEVRSBVC Redundancy Alarm Status (RH) */
    ureg32 EVR33C:1;        /* [5:5] EVR33C Redundancy Alarm Status (RH) */
    ureg32 EVRCC:1;         /* [6:6] EVRCC Redundancy Alarm Status(RH) */
    ureg32 PBIST2DC:1;      /* [7:7] PBIST2DC Redundancy Alarm Status (RH) */
    ureg32 PRIMRYDC:1;      /* [8:8] PRIMRYDC Redundancy Alarm Status (RH) */
    ureg32 reserved_9:1;    /* [9:9] Internal reserved (R) */
    ureg32 SWP:1;           /* [10:10] SWP Redundancy Alarm Status (RH) */
    ureg32 STDP:1;          /* [11:11] STDP Redundancy Alarm Status (RH) */
    ureg32 IPPC:1;          /* [12:12] IPPC Redundancy Alarm Status (RH) */
    ureg32 PWRTRIM:1;       /* [13:13] Power Trim Redundancy (RH) */
    ureg32 FSM:1;           /* [14:14] FSM Illegial Jump (RH) */
    ureg32 E:1;             /* [15:15] E Illegal Access (RH) */
    ureg32 SE:1;            /* [16:16] SE Illegal Access (RH) */
    ureg32 reserved_17:15;  /* [31:17]  Internal reserved (R) */
} PWRCSTB_ALMS_Bits;

/* PWRCSTB Safety Alarm Enable Register */
typedef struct
{
    ureg32 SFFEN:1;         /* [0:0] Register Redundancy Enable (RW) */
    ureg32 FSMEN:1;         /* [1:1]  FSM Illegal Jump Enable (RW) */
    ureg32 reserved_2:30;   /* [31:2]  Internal reserved (R) */
} PWRCSTB_ALME_Bits;

/* PWRCSTB Safety Alarm Clear Register */
typedef struct
{
    ureg32 SFFCLR:1;        /* [0:0]  Bus error mask (RW) */
    ureg32 reserved_1:1;    /* [1:1]  Internal reserved (R) */
    ureg32 FSMCLR:1;        /* [2:2]  FSM Illegal Jump Clear (W) */
    ureg32 reserved_3:1;    /* [3:3]  Internal reserved (R) */
    ureg32 ECLR:1;          /* [4:4]  E Illegal Access Clear (W) */
    ureg32 reserved_5:1;    /* [5:5]  Internal reserved (R) */
    ureg32 SECLR:1;         /* [6:6]  SE Illegal Access Clear (W) */
    ureg32 reserved_2:25;   /* [31:7]  Internal reserved (R) */
} PWRCSTB_ALMC_Bits;

/* PWRCSTB Safety Alarm Injection Register */
typedef struct
{
    ureg32 SFFERRIN:2;        /* [1:0]  Redundancy injection (RW) */
    ureg32 FSMERRIN:2;        /* [3:2]  Illegal Jump Injection (RW) */
    ureg32 reserved_4:28;     /* [31:4]  Internal reserved (R) */
} PWRCSTB_ERRINS_Bits;

/* PWRCSTB Bus Error Mask Register */
typedef struct
{
    ureg32 BEMSKS:1;        /* [0:0]  Bus error mask (RW) */
    ureg32 STBYFLAG_IOEN:1; /* [1:1]  Standby status flag indicate on P33.3; this bit is only valid in THA6104 - (RW) */
    ureg32 reserved_2:30;   /* [31:2]  Internal reserved (R) */
} PWRCSTB_BEMSKS_Bits;
#endif

/**********************************************************************************************************************
 *                                          PWRC Register Union Definitions
 *********************************************************************************************************************/
/* System low power control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    PWRC_LPCON_Bits B; /* Bitfield access */
} PWRC_LPCON;

/* Voltage alarm control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    PWRC_VLTALMCON_Bits B; /* Bitfield access */
} PWRC_VLTALMCON;

/* ESR1 signal Control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    PWRC_ESR1SCON_Bits B; /* Bitfield access */
} PWRC_ESR1SCON;

/* CPU Low Power Mode Real Time Status Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    PWRC_CPULPRTSTS_Bits B; /* Bitfield access */
} PWRC_CPULPRTSTS;

/* PWRC current and voltage alarm real time status Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    PWRC_CURVLTALMRTSTS_Bits B; /* Bitfield access */
} PWRC_CURVLTALMRTSTS;

/* PWRC PBIST2 voltage selt detect alarm real time status Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                   /* Unsigned access */
    PWRC_PBIST2ALMRTSTS_Bits B; /* Bitfield access */
} PWRC_PBIST2ALMRTSTS;

/* PWRC CPU active real time status Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    PWRC_CPUACTRTSTS_Bits B; /* Bitfield access */
} PWRC_CPUACTRTSTS;

/* ESR1 status Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    PWRC_ESR1STS_Bits B; /* Bitfield access */
} PWRC_ESR1STS;

/* PWRC ESR1 interrupt mask Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    PWRC_ESR1INTMSK_Bits B; /* Bitfield access */
} PWRC_ESR1INTMSK;

/* PWRC ESR1 interrupt clear Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    PWRC_ESR1INTCLR_Bits B; /* Bitfield access */
} PWRC_ESR1INTCLR;

/* PWRC low power mode interrupt status Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    PWRC_CPULPINTSTS_Bits B; /* Bitfield access */
}PWRC_CPULPINTSTS;

/* PWRC low power mode interrupt mask Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    PWRC_CPULPINTMSK_Bits B; /* Bitfield access */
}PWRC_CPULPINTMSK;

/* CPU low power mode interrupt clear register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    PWRC_CPULPINTCLR_Bits B; /* Bitfield access */
} PWRC_CPULPINTCLR;

/* PWRC current and voltage status Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    PWRC_CURVLTSTS_Bits B; /* Bitfield access */
} PWRC_CURVLTSTS;

/* PWRC current and voltage interrupt mask Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    PWRC_CURVLTINTMSK_Bits B; /* Bitfield access */
} PWRC_CURVLTINTMSK;

/* PWRC current and voltage alarm mask Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    PWRC_CURVLTALMMSK_Bits B; /* Bitfield access */
} PWRC_CURVLTALMMSK;

/* PWRC current and voltage clear Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    PWRC_CURVLTCLR_Bits B; /* Bitfield access */
} PWRC_CURVLTCLR;

/* PWRC Voltage detect threshold coarse adjustment Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    PWRC_DETADJ_Bits B; /* Bitfield access */
} PWRC_DETADJ;

/* PWRC Voltage detect threshold fine adjustment Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    PWRC_DETEADJ_Bits B; /* Bitfield access */
} PWRC_DETEADJ;

/* PWRC ADC reference current control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    PWRC_ADCREFC_Bits B; /* Bitfield access */
} PWRC_ADCREFC;

/* PWRC debug mode low power config */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    PWRC_DBGC_Bits B; /* Bitfield access */
} PWRC_DBGC;

/* PWRCSTB Standby Mode Protection Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_STDP_Bits B;       /* Bitfield access */
} PWRCSTB_STDP;

/* PWRCSTB HWCFG Status Register*/
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_HWCFGSTS_Bits B;   /* Bitfield access */
} PWRCSTB_HWCFGSTS;

/* PWRCSTB hardware default configuration 6 status control Register*/
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_DPCR_Bits B;       /* Bitfield access */
} PWRCSTB_DPCR;

/* PWRCSTB Standby Wake Up Control Register*/
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_WKUPC_Bits B;      /* Bitfield access */
} PWRCSTB_WKUPC;

/* PWRCSTB Standby Wake Up Time Control Register*/
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_WKUPTIM_Bits B;    /* Bitfield access */
} PWRCSTB_WKUPTIM;

/* PWRCSTB Standby Wake Up Status Register*/
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_WKUPSTS_Bits B;    /* Bitfield access */
} PWRCSTB_WKUPSTS;

/* PWRCSTB IP low power status Control Register*/
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_IPPC_Bits B;       /* Bitfield access */
} PWRCSTB_IPPC;

/* PWRCSTB IP low power status Control Register 0 (THA6412 only) */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    PWRCSTB_STIOWKUPC0_Bits B;      /* Bitfield access */
} PWRCSTB_STIOWKUPC0;

/* PWRCSTB IP low power status Control Register 1 (THA6412 only) */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                       /* Unsigned access */
    PWRCSTB_STIOWKUPC1_Bits B;      /* Bitfield access */
} PWRCSTB_STIOWKUPC1;

/* PWRCSTB standby IO low power state wakeup status Register (THA6412 only) */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_STIOWKUSTS_Bits B; /* Bitfield access */
} PWRCSTB_STIOWKUSTS;

/* PWRCSTB Voltage Select Register*/
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_VOSEL_Bits B;      /* Bitfield access */
} PWRCSTB_VOSEL;

/* PWRCSTB Primary Detection Control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_PRIMRYDC_Bits B;   /* Bitfield access */
} PWRCSTB_PRIMRYDC;

/* PWRCSTB Voltage Programmable Built In Selt2 Control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_PBIST2DC_Bits B;   /* Bitfield access */
} PWRCSTB_PBIST2DC;

/* PWRCSTB EVR DCDC Control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_EVRC_Bits B;       /* Bitfield access */
} PWRCSTB_EVRC;

/* PWRCSTB EVR33 Control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_EVR33C_Bits B;     /* Bitfield access */
} PWRCSTB_EVR33C;

/* PWRCSTB EVRSB Control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_EVRSBVC_Bits B;    /* Bitfield access */
} PWRCSTB_EVRSBVC;

/* PWRCSTB Reference Voltage  Control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_REFC_Bits B;       /* Bitfield access */
} PWRCSTB_REFC;

/* PWRCSTB EVRC SREFpread spectrum clock Control Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_EVRCCK_Bits B;     /* Bitfield access */
} PWRCSTB_EVRCCK;

/* PWRCSTB Safety Alarm Status Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_ALMS_Bits B;       /* Bitfield access */
} PWRCSTB_ALMS;

/* PWRCSTB Safety Alarm Enable Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_ALME_Bits B;       /* Bitfield access */
} PWRCSTB_ALME;

/* PWRCSTB Safety Alarm Clear Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_ALMC_Bits B;       /* Bitfield access */
} PWRCSTB_ALMC;

/* PWRCSTB Safety Alarm Injection Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_ERRINS_Bits B;     /* Bitfield access */
} PWRCSTB_ERRINS;

/* PWRCSTB Bus Error Mask Register */
typedef union
/* #Violation: pwrc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    PWRCSTB_BEMSKS_Bits B;     /* Bitfield access */
} PWRCSTB_BEMSKS;

/**********************************************************************************************************************
 *                                               PWRC Register Structure
 *********************************************************************************************************************/
typedef volatile struct
{
    PWRC_LPCON LPCON;                   /* 0x0, System low power control Register  */
    PWRC_VLTALMCON VLTALMCON;           /* 0x4, Voltage alarm control Register */
    PWRC_ESR1SCON ESR1SCON;             /* 0x8, ESR1 signal Control Register */
    ureg32 RESERVED_C[13];              /* 0xc, Internal Reserved */
    PWRC_CPULPRTSTS CPULPRTSTS;         /* 0x40, PWRC low power mode real time status Register */
    PWRC_CURVLTALMRTSTS CURVLTALMRTSTS; /* 0x44, PWRC current and voltage alarm real time status Register */
    PWRC_PBIST2ALMRTSTS PBIST2ALMRTSTS; /* 0x48, PWRC PBIST2 voltage self detect alarm real time status Register */
    PWRC_CPUACTRTSTS  CPUACTRTSTS;      /* 0x4C, PWRC CPU active real time status Register  */
    ureg32 RESERVED_50[16];             /* 0x50, internal Reserved */
    PWRC_ESR1STS ESR1STS;               /* 0x90, ESR1 status Register */
    PWRC_ESR1INTMSK ESR1INTMSK;         /* 0x94, PWRC ESR1 interrupt mask Register */
    PWRC_ESR1INTCLR ESR1INTCLR;         /* 0x98, ESR1 interrupt clear Register */
    ureg32 RESERVED_9C[25];             /* 0x9C, Internal Reserved */
    PWRC_CPULPINTSTS CPULPINTSTS;       /* 0x100, PWRC low power mode interrupt status Register */
    PWRC_CPULPINTMSK CPULPINTMSK;       /* 0x104, PWRC low power mode interrupt mask Register */
    PWRC_CPULPINTCLR CPULPINTCLR;       /* 0x108, PWRC low power mode interrupt clear Register */
    ureg32 RESERVED_10C;                /* 0x10C, Internal Reserved */
    PWRC_CURVLTSTS CURVLTSTS;           /* 0x110, PWRC current and voltage status Register */
    PWRC_CURVLTINTMSK CURVLTINTMSK;     /* 0x114, PWRC current and voltage interrupt mask Register */
    ureg32 RESERVED_118[14];            /* 0x118, Internal Reserved */
    PWRC_CURVLTALMMSK CURVLTALMMSK;     /* 0x150, PWRC current and voltage alarm mask Register */
    ureg32 RESERVED_154;                /* 0x154, Internal Reserved */
    PWRC_CURVLTCLR CURVLTCLR;           /* 0x158, PWRC current and voltage clear Register */
    ureg32 RESERVED_15C;                /* 0x15C, Internal Reserved */
    ureg32 SAFEALMSTS;                  /* 0x160, Safety alarm status Register */
    ureg32 SAFEALMEN;                   /* 0x164, Safety alarm mask Register */
    ureg32 SAFEALMCLR;                  /* 0x168, Safety alarm clear Register */
    ureg32 ERRIN;                       /* 0x16C, Safety error injection Register */
    ureg32 BEMSK;                       /* 0x170, Bus error mask Register */
    ureg32 RESERVED_174[35];            /* 0x174, Internal Reserved */
    PWRC_DETADJ DETADJ;                 /* 0x200, PWRC Voltage detect threshold fine adjustment Register */
    PWRC_DETEADJ DETEADJ;               /* 0x204, PWRC Voltage detect threshold fine adjustment Register */
    PWRC_ADCREFC ADCREFC;               /* 0x208, PWRC ADC reference current control Register */
    PWRC_DBGC DBGC;                     /* 0x20C, PWRC debug mode low power configure */
} PWRC_MODULE;

typedef volatile struct
{
    ureg32  SWP;                    /* 0x00, Write Protection Register */
    PWRCSTB_STDP  STDP;             /* 0x04, Standby Mode Protection Register */
    PWRCSTB_HWCFGSTS  HWCFGSTS;     /* 0x08, HWCFG Status Register */
    PWRCSTB_DPCR  DPCR;             /* 0x0C, Internal Reserved  */
    PWRCSTB_WKUPC  WKUPC;           /* 0x10, Standby Wake-Up Control Register  */
    PWRCSTB_WKUPTIM  WKUPTIM;       /* 0x14, Standby Wake Up Time Control Register */
    PWRCSTB_WKUPSTS  WKUPSTS;       /* 0x18, Standby Wake-Up Status Register */
    ureg32 RESERVED_1C;             /* 0x1C, Internal Reserved  */
    PWRCSTB_IPPC  IPPC;             /* 0x20, PWRCSTB IP low power status Control Register */
    PWRCSTB_STIOWKUPC0 STIOWKUPC0;  /* 0x24, Standby IO low power wake up control Register 0 (THA6412 only) */
    PWRCSTB_STIOWKUPC1 STIOWKUPC1;  /* 0x28, Standby IO low power wake up control Register 1 (THA6412 only) */
    PWRCSTB_STIOWKUSTS STIOWKUSTS;  /* 0x2C, Standby IO low power wake up control Register 1 (THA6412 only) */
    PWRCSTB_VOSEL  VOSEL;           /* 0x30, Voltage Select Register (THA6412, THA6206, THA6206D only)  */
    PWRCSTB_PRIMRYDC  PRIMRYDC;     /* 0x34, Primary Detection Control Register */
    PWRCSTB_PBIST2DC  PBIST2DC;     /* 0x38, Voltage Detection Control Register */
    ureg32 RESERVED_3C;             /* 0x3C, Internal Reserved */
    PWRCSTB_EVRC  EVRCC;            /* 0x40, EVR DCDC Control Register */
    PWRCSTB_EVR33C  EVR33C;         /* 0x44, EVR33 Control Register */
    PWRCSTB_EVRSBVC  EVRSBVC;       /* 0x48, EVR VDDSB Control Register */
    PWRCSTB_REFC  REFC;             /* 0x4C, Reference Voltage Control Register */
    PWRCSTB_EVRCCK EVRCCK;          /* 0x50, EVRC SREFpread spectrum clock Control Register */
    ureg32 RESERVED_54[3];          /* 0x54, Internal Reserved */
    PWRCSTB_ALMS ALMS;              /* 0x60, Safety Alarm Status Register */
    PWRCSTB_ALME ALME;              /* 0x64, Safety Alarm Enable Register */
    PWRCSTB_ALMC ALMC;              /* 0x68, Safety Alarm Clear Register */
    PWRCSTB_ERRINS ERRINS;          /* 0x6C, Safety Alarm Injection Register */
    PWRCSTB_BEMSKS BEMSKS;          /* 0x70, Bus Error Mask Register */
} PWRCSTB_MODULE;
/**********************************************************************************************************************
 *                                                  BUSPROT Module Object
 *********************************************************************************************************************/

#endif /* PWRC_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

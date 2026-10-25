/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    sac_register.h
 * Author:      00977
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all definitions of SAC module registers.
 *********************************************************************************************************************/
/*
*#Violation Summary
*#sac_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Union is used to define the registers type.
*/
#ifndef SAC_REGISTER_H
#define SAC_REGISTER_H

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "regtypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* SAC alarm group total number */
#define SAC_ALAM_GUPMUM (13U)
/* SAC standby alarm group total number */
#define SAC_STDB_ALAM_GUPMUM (2U)
/**********************************************************************************************************************
 *                                         SAC Register Bit-Fields Definitions
 *********************************************************************************************************************/

/* Alarm global configuration register */
typedef struct
{
    ureg32 IGCS0:4;       /* [3:0] Interrupt generation configuration set 0 - RW */
    ureg32 reserved_4:1;  /* [4:4] Internal reserved */
    ureg32 IGCS1:4;       /* [8:5] Interrupt generation configuration set 1 - RW */
    ureg32 reserved_9:1;  /* [9:9] Internal reserved */
    ureg32 IGCS2:4;       /* [13:10] Interrupt generation configuration set 2 - RW */
    ureg32 reserved_14:1; /* [14:14] Internal reserved */
    ureg32 IGCS3:4;       /* [18:15] Interrupt generation configuration set 3 - RW */
    ureg32 NMISEL:4;      /* [22:19] NMI selection - RW; This bit [22:21] Reserved in THA6206 and THA6104, Active in THA6412 */
    ureg32 PES:6;         /* [28:23] Port emergency stop - RW */
    ureg32 EFRST:1;       /* [29:29] Enable FAULT to RUN state transition - RW */
    ureg32 EMU:1;         /* [30:30] Enable emulation  - RW */
    ureg32 reserved_31:1; /* [31:31] Internal reserved */
} SAC_AGC_Bits;

/* Alarm executed status register */
typedef struct
{
    ureg32 IRQ0STS:1;     /* [0:0] IRQ0 request status - RH */
    ureg32 IRQ1STS:1;     /* [1:1] IRQ1 request status - RH */
    ureg32 IRQ2STS:1;     /* [2:2] IRQ2 request status - RH */
    ureg32 IRQ3STS:1;     /* [3:3] IRQ3 request status - RH */
    ureg32 RSTSTS:1;      /* [4:4] RST  request status - RH */
    ureg32 reserved_5:4;  /* [8:5] Internal reserved */
    ureg32 NMISTS:1;      /* [9:9] NMI request status - RH */
    ureg32 reserved_10:1; /* [10:10] Internal reserved */
    ureg32 PESSTS:1;      /* [11:11] PES request status - RH */
    ureg32 reserved_12:4; /* [15:12] Internal reserved */
    ureg32 IRQ0AEM:1;     /* [16:16] IRQ0 AEM - RH */
    ureg32 IRQ1AEM:1;     /* [17:17] IRQ1 AEM - RH */
    ureg32 IRQ2AEM:1;     /* [18:18] IRQ2 AEM - RH */
    ureg32 IRQ3AEM:1;     /* [19:19] IRQ3 AEM - RH */
    ureg32 RSTAEM:1;      /* [20:20] RST AEM - RH */
    ureg32 reserved_21:4; /* [24:21] Internal reserved */
    ureg32 NMIAEM:1;      /* [25:25] NMI AEM - RH */
    ureg32 reserved_26:1; /* [26:26] Internal reserved */
    ureg32 PESAEM:1;      /* [27:27] PES AEM - RH */
    ureg32 reserved_28:4; /* [31:28] Internal reserved */
} SAC_AEX_Bits;

/* Alarm executed status clear register */
typedef struct
{
    ureg32 IRQ0STSCLR:1;  /* [0:0] IRQ0 request status clear - WO */
    ureg32 IRQ1STSCLR:1;  /* [1:1] IRQ1 request status clear - WO */
    ureg32 IRQ2STSCLR:1;  /* [2:2] IRQ2 request status clear - WO */
    ureg32 IRQ3STSCLR:1;  /* [3:3] IRQ3 request status clear - WO */
    ureg32 RSTSTSCLR:1;   /* [4:4] RST  request status clear - WO */
    ureg32 reserved_5:4;  /* [8:5] Internal reserved */
    ureg32 NMISTSCLR:1;   /* [9:9] NMI request status clear - WO */
    ureg32 reserved_10:1; /* [10:10] Internal reserved */
    ureg32 PESSTSCLR:1;   /* [11:11] PES request status clear - WO */
    ureg32 reserved_12:4; /* [15:12] Internal reserved */
    ureg32 IRQ0AEMCLR:1;  /* [16:16] IRQ0 AEM status clear - WO */
    ureg32 IRQ1AEMCLR:1;  /* [17:17] IRQ1 AEM status clear - WO */
    ureg32 IRQ2AEMCLR:1;  /* [18:18] IRQ2 AEM status clear - WO */
    ureg32 IRQ3AEMCLR:1;  /* [19:19] IRQ3 AEM status clear - WO */
    ureg32 RSTAEMCLR:1;   /* [20:20] RST AEM status clear - WO */
    ureg32 reserved_21:4; /* [24:21] Internal reserved */
    ureg32 NMIAEMCLR:1;   /* [25:25] NMI AEM status clear - WO */
    ureg32 reserved_26:1; /* [26:26] Internal reserved */
    ureg32 PESAEMCLR:1;   /* [27:27] PES AEM status clear - WO */
    ureg32 reserved_28:4; /* [31:28] Internal reserved */
} SAC_AEXCLR_Bits;

/* Alarm and fault counter register */
typedef struct
{
    ureg32 FCNT:4;         /* [3:0] Fault counter - RH */
    ureg32 ACNT:12;        /* [15:4] Alarm counter - RH */
    ureg32 reserved_16:14; /* [29:16] Internal reserved */
    ureg32 FCO:1;          /* [30:30] Fault counter overflow - RH */
    ureg32 ACO:1;          /* [31:31] Alarm counter overflow - RH */
} SAC_AFCNT_Bits;

/* Alarm status register */
typedef struct
{
    ureg32 SF0:1;  /* [0:0] Status flag0 in alarm status register i - RWH */
    ureg32 SF1:1;  /* [1:1] Status flag1 in alarm status register i - RWH */
    ureg32 SF2:1;  /* [2:2] Status flag2 in alarm status register i - RWH */
    ureg32 SF3:1;  /* [3:3] Status flag3 in alarm status register i - RWH */
    ureg32 SF4:1;  /* [4:4] Status flag4 in alarm status register i - RWH */
    ureg32 SF5:1;  /* [5:5] Status flag5 in alarm status register i - RWH */
    ureg32 SF6:1;  /* [6:6] Status flag6 in alarm status register i - RWH */
    ureg32 SF7:1;  /* [7:7] Status flag7 in alarm status register i - RWH */
    ureg32 SF8:1;  /* [8:8] Status flag8 in alarm status register i - RWH */
    ureg32 SF9:1;  /* [9:9] Status flag9 in alarm status register i - RWH */
    ureg32 SF10:1; /* [10:10] Status flag10 in alarm status register i - RWH */
    ureg32 SF11:1; /* [11:11] Status flag11 in alarm status register i - RWH */
    ureg32 SF12:1; /* [12:12] Status flag12 in alarm status register i - RWH */
    ureg32 SF13:1; /* [13:13] Status flag13 in alarm status register i - RWH */
    ureg32 SF14:1; /* [14:14] Status flag14 in alarm status register i - RWH */
    ureg32 SF15:1; /* [15:15] Status flag15 in alarm status register i - RWH */
    ureg32 SF16:1; /* [16:16] Status flag16 in alarm status register i - RWH */
    ureg32 SF17:1; /* [17:17] Status flag17 in alarm status register i - RWH */
    ureg32 SF18:1; /* [18:18] Status flag18 in alarm status register i - RWH */
    ureg32 SF19:1; /* [19:19] Status flag19 in alarm status register i - RWH */
    ureg32 SF20:1; /* [20:20] Status flag20 in alarm status register i - RWH */
    ureg32 SF21:1; /* [21:21] Status flag21 in alarm status register i - RWH */
    ureg32 SF22:1; /* [22:22] Status flag22 in alarm status register i - RWH */
    ureg32 SF23:1; /* [23:23] Status flag23 in alarm status register i - RWH */
    ureg32 SF24:1; /* [24:24] Status flag24 in alarm status register i - RWH */
    ureg32 SF25:1; /* [25:25] Status flag25 in alarm status register i - RWH */
    ureg32 SF26:1; /* [26:26] Status flag26 in alarm status register i - RWH */
    ureg32 SF27:1; /* [27:27] Status flag27 in alarm status register i - RWH */
    ureg32 SF28:1; /* [28:28] Status flag28 in alarm status register i - RWH */
    ureg32 SF29:1; /* [29:29] Status flag29 in alarm status register i - RWH */
    ureg32 SF30:1; /* [30:30] Status flag30 in alarm status register i - RWH */
    ureg32 SF31:1; /* [31:31] Status flag31 in alarm status register i - RWH */
} SAC_ASR_Bits;

/* Alarm backup register */
typedef struct
{
    ureg32 AD0:1;  /* [0:0] Alarm diagnosis flag 0 belonging to alarm backup register i - RH */
    ureg32 AD1:1;  /* [1:1] Alarm diagnosis flag 1 belonging to alarm backup register i - RH */
    ureg32 AD2:1;  /* [2:2] Alarm diagnosis flag 2 belonging to alarm backup register i - RH */
    ureg32 AD3:1;  /* [3:3] Alarm diagnosis flag 3 belonging to alarm backup register i - RH */
    ureg32 AD4:1;  /* [4:4] Alarm diagnosis flag 4 belonging to alarm backup register i - RH */
    ureg32 AD5:1;  /* [5:5] Alarm diagnosis flag 5 belonging to alarm backup register i - RH */
    ureg32 AD6:1;  /* [6:6] Alarm diagnosis flag 6 belonging to alarm backup register i - RH */
    ureg32 AD7:1;  /* [7:7] Alarm diagnosis flag 7 belonging to alarm backup register i - RH */
    ureg32 AD8:1;  /* [8:8] Alarm diagnosis flag 8 belonging to alarm backup register i - RH */
    ureg32 AD9:1;  /* [9:9] Alarm diagnosis flag 9 belonging to alarm backup register i - RH */
    ureg32 AD10:1; /* [10:10] Alarm diagnosis flag 10 belonging to alarm backup register i - RH */
    ureg32 AD11:1; /* [11:11] Alarm diagnosis flag 11 belonging to alarm backup register i - RH */
    ureg32 AD12:1; /* [12:12] Alarm diagnosis flag 12 belonging to alarm backup register i - RH */
    ureg32 AD13:1; /* [13:13] Alarm diagnosis flag 13 belonging to alarm backup register i - RH */
    ureg32 AD14:1; /* [14:14] Alarm diagnosis flag 14 belonging to alarm backup register i - RH */
    ureg32 AD15:1; /* [15:15] Alarm diagnosis flag 15 belonging to alarm backup register i - RH */
    ureg32 AD16:1; /* [16:16] Alarm diagnosis flag 16 belonging to alarm backup register i - RH */
    ureg32 AD17:1; /* [17:17] Alarm diagnosis flag 17 belonging to alarm backup register i - RH */
    ureg32 AD18:1; /* [18:18] Alarm diagnosis flag 18 belonging to alarm backup register i - RH */
    ureg32 AD19:1; /* [19:19] Alarm diagnosis flag 19 belonging to alarm backup register i - RH */
    ureg32 AD20:1; /* [20:20] Alarm diagnosis flag 20 belonging to alarm backup register i - RH */
    ureg32 AD21:1; /* [21:21] Alarm diagnosis flag 21 belonging to alarm backup register i - RH */
    ureg32 AD22:1; /* [22:22] Alarm diagnosis flag 22 belonging to alarm backup register i - RH */
    ureg32 AD23:1; /* [23:23] Alarm diagnosis flag 23 belonging to alarm backup register i - RH */
    ureg32 AD24:1; /* [24:24] Alarm diagnosis flag 24 belonging to alarm backup register i - RH */
    ureg32 AD25:1; /* [25:25] Alarm diagnosis flag 25 belonging to alarm backup register i - RH */
    ureg32 AD26:1; /* [26:26] Alarm diagnosis flag 26 belonging to alarm backup register i - RH */
    ureg32 AD27:1; /* [27:27] Alarm diagnosis flag 27 belonging to alarm backup register i - RH */
    ureg32 AD28:1; /* [28:28] Alarm diagnosis flag 28 belonging to alarm backup register i - RH */
    ureg32 AD29:1; /* [29:29] Alarm diagnosis flag 29 belonging to alarm backup register i - RH */
    ureg32 AD30:1; /* [30:30] Alarm diagnosis flag 30 belonging to alarm backup register i - RH */
    ureg32 AD31:1; /* [31:31] Alarm diagnosis flag 31 belonging to alarm backup register i - RH */
} SAC_AB_Bits;

/* Module identification register */
typedef struct
{
    ureg32 MOD_REV:8;     /* [7:0] Module revision number - RO */
    ureg32 MOD_TYPE:8;    /* [15:8] Module type - RO */
    ureg32 MOD_NUMBER:16; /* [31:16] Module number value - RO */
} SAC_ID_Bits;

/* Command register */
typedef struct
{
    ureg32 CMD:4;         /* [3:0] Implements the SAC command interface - RW */
    ureg32 ARG:4;         /* [7:4] Argument to be used with the command - RW */
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
} SAC_CMD_Bits;

/* Key register */
typedef struct
{
    ureg32 CFGLCK:8;       /* [7:0] Configuration lock - RW */
    ureg32 PERLCK:8;       /* [15:8] Permanent lock - RW */
    ureg32 reserved_16:16; /* [31:16] Internal reserved */
} SAC_KEYS_Bits;

/* Fault indication protocol */
typedef struct
{
    ureg32 PRE1:3;       /* [2:0] Prescaler1 - RW */
    ureg32 PRE2:2;       /* [4:3] Prescaler2 - RW */
    ureg32 MODE:2;       /* [6:5] Fault indication protocol configuration - RW */
    ureg32 PES:1;        /* [7:7] Port emergency stop (PES) - RW */
    ureg32 TFIP_LOW:14;  /* [21:8] Specifies the FIP fault state duration - RO */
    ureg32 TFIP_HIGH:10; /* [31:22] Specifies the FIP fault state duration - RW */
} SAC_FIP_Bits;

/* Status register */
typedef struct
{
    ureg32 CMD:4;          /* [3:0] Last command received - RH */
    ureg32 ARG:4;          /* [7:4] Last command argument received - RH */
    ureg32 RES:1;          /* [8:8] Result of last received command - RH */
    ureg32 ASCE:1;         /* [9:9] Alarm status clear enable - RH */
    ureg32 FIP:2;          /* [11:10] Fault indication protocol status - RH */
    ureg32 reserved_12:4;  /* [15:12] Internal reserved */
    ureg32 IETS0:1;        /* [16:16] Interrupt execution timer 0 status - RH */
    ureg32 reserved_17:1;  /* [17:17] Internal reserved */
    ureg32 IETS1:1;        /* [18:18] Interrupt execution timer 1 status - RH */
    ureg32 reserved_19:1;  /* [19:19] Internal reserved */
    ureg32 reserved_20:12; /* [31:20] Internal reserved */
} SAC_STS_Bits;

/* ES glitch filter configuration */
typedef struct
{
    ureg32 ESGFCNT:10;     /* [9:0] ES glitch filter counter - RW */
    ureg32 reserved_10:22; /* [31:10] Internal reserved */
} SAC_ESGLF_Bits;

/* Interrupt execution timer configuration */
typedef struct
{
    ureg32 IET0E:1;      /* [0:0] IET0 enable bit - RW */
    ureg32 IET1E:1;      /* [1:1] IET1 enable bit - RW */
    ureg32 reserved_2:6; /* [7:2] Internal reserved */
    ureg32 IETD:24;      /* [31:8] Interrupt execution timer duration - RW */
} SAC_IETC_Bits;

/* Interrupt execution timer 0 alarm configuration 0 */
typedef struct
{
    ureg32 GID0:4;        /* [3:0] Group index 0 - RW */
    ureg32 ALID0:5;       /* [8:4] Alarm identifier 0 - RW */
    ureg32 reserved_9:7;  /* [15:9] Internal reserved */
    ureg32 GID1:4;        /* [19:16] Group index 1 - RW */
    ureg32 ALID1:5;       /* [24:20] Alarm identifier 1 - RW */
    ureg32 reserved_25:7; /* [31:25] Internal reserved */
} SAC_IETAC00_Bits;

/* Interrupt execution timer 0 alarm configuration 1 */
typedef struct
{
    ureg32 GID2:4;        /* [3:0] Group index 2 - RW */
    ureg32 ALID2:5;       /* [8:4] Alarm identifier 2. - RW */
    ureg32 reserved_9:7;  /* [15:9] Internal reserved */
    ureg32 GID3:4;        /* [19:16] Group index 3 - RW */
    ureg32 ALID3:5;       /* [24:20] Alarm identifier 3 - RW */
    ureg32 reserved_25:7; /* [31:25] Internal reserved */
} SAC_IETAC01_Bits;

/* Interrupt execution timer 1 alarm configuration 0 */
typedef struct
{
    ureg32 GID0:4;        /* [3:0] Group index 0 - RW */
    ureg32 ALID0:5;       /* [8:4] Alarm identifier 0 - RW */
    ureg32 reserved_9:7;  /* [15:9] Internal reserved */
    ureg32 GID1:4;        /* [19:16] Group index 1 - RW */
    ureg32 ALID1:5;       /* [24:20] Alarm identifier 1 - RW */
    ureg32 reserved_25:7; /* [31:25] Internal reserved */
} SAC_IETAC10_Bits;

/* Interrupt execution timer 1 alarm configuration 1 */
typedef struct
{
    ureg32 GID2:4;        /* [3:0] Group index 2 - RW */
    ureg32 ALID2:5;       /* [8:4] Alarm identifier 2 - RW */
    ureg32 reserved_9:7;  /* [15:9] Internal reserved */
    ureg32 GID3:4;        /* [19:16] Group index 3 - RW */
    ureg32 ALID3:5;       /* [24:20] Alarm identifier 3 - RW */
    ureg32 reserved_25:7; /* [31:25] Internal reserved */
} SAC_IETAC11_Bits;

/* FIP configuration register */
typedef struct
{
    ureg32 FIPAG_FC0:1;  /* [0:0] Fault indication configuration flag for alarm 0 belonging to alarm group i - RW */
    ureg32 FIPAG_FC1:1;  /* [1:1] Fault indication configuration flag for alarm 1 belonging to alarm group i - RW */
    ureg32 FIPAG_FC2:1;  /* [2:2] Fault indication configuration flag for alarm 2 belonging to alarm group i - RW */
    ureg32 FIPAG_FC3:1;  /* [3:3] Fault indication configuration flag for alarm 3 belonging to alarm group i - RW */
    ureg32 FIPAG_FC4:1;  /* [4:4] Fault indication configuration flag for alarm 4 belonging to alarm group i - RW */
    ureg32 FIPAG_FC5:1;  /* [5:5] Fault indication configuration flag for alarm 5 belonging to alarm group i - RW */
    ureg32 FIPAG_FC6:1;  /* [6:6] Fault indication configuration flag for alarm 6 belonging to alarm group i - RW */
    ureg32 FIPAG_FC7:1;  /* [7:7] Fault indication configuration flag for alarm 7 belonging to alarm group i - RW */
    ureg32 FIPAG_FC8:1;  /* [8:8] Fault indication configuration flag for alarm 8 belonging to alarm group i - RW */
    ureg32 FIPAG_FC9:1;  /* [9:9] Fault indication configuration flag for alarm 9 belonging to alarm group i - RW */
    ureg32 FIPAG_FC10:1; /* [10:10] Fault indication configuration flag for alarm 10 belonging to alarm group i - RW */
    ureg32 FIPAG_FC11:1; /* [11:11] Fault indication configuration flag for alarm 11 belonging to alarm group i - RW */
    ureg32 FIPAG_FC12:1; /* [12:12] Fault indication configuration flag for alarm 12 belonging to alarm group i - RW */
    ureg32 FIPAG_FC13:1; /* [13:13] Fault indication configuration flag for alarm 13 belonging to alarm group i - RW */
    ureg32 FIPAG_FC14:1; /* [14:14] Fault indication configuration flag for alarm 14 belonging to alarm group i - RW */
    ureg32 FIPAG_FC15:1; /* [15:15] Fault indication configuration flag for alarm 15 belonging to alarm group i - RW */
    ureg32 FIPAG_FC16:1; /* [16:16] Fault indication configuration flag for alarm 16 belonging to alarm group i - RW */
    ureg32 FIPAG_FC17:1; /* [17:17] Fault indication configuration flag for alarm 17 belonging to alarm group i - RW */
    ureg32 FIPAG_FC18:1; /* [18:18] Fault indication configuration flag for alarm 18 belonging to alarm group i - RW */
    ureg32 FIPAG_FC19:1; /* [19:19] Fault indication configuration flag for alarm 19 belonging to alarm group i - RW */
    ureg32 FIPAG_FC20:1; /* [20:20] Fault indication configuration flag for alarm 20 belonging to alarm group i - RW */
    ureg32 FIPAG_FC21:1; /* [21:21] Fault indication configuration flag for alarm 21 belonging to alarm group i - RW */
    ureg32 FIPAG_FC22:1; /* [22:22] Fault indication configuration flag for alarm 22 belonging to alarm group i - RW */
    ureg32 FIPAG_FC23:1; /* [23:23] Fault indication configuration flag for alarm 23 belonging to alarm group i - RW */
    ureg32 FIPAG_FC24:1; /* [24:24] Fault indication configuration flag for alarm 24 belonging to alarm group i - RW */
    ureg32 FIPAG_FC25:1; /* [25:25] Fault indication configuration flag for alarm 25 belonging to alarm group i - RW */
    ureg32 FIPAG_FC26:1; /* [26:26] Fault indication configuration flag for alarm 26 belonging to alarm group i - RW */
    ureg32 FIPAG_FC27:1; /* [27:27] Fault indication configuration flag for alarm 27 belonging to alarm group i - RW */
    ureg32 FIPAG_FC28:1; /* [28:28] Fault indication configuration flag for alarm 28 belonging to alarm group i - RW */
    ureg32 FIPAG_FC29:1; /* [29:29] Fault indication configuration flag for alarm 29 belonging to alarm group i - RW */
    ureg32 FIPAG_FC30:1; /* [30:30] Fault indication configuration flag for alarm 30 belonging to alarm group i - RW */
    ureg32 FIPAG_FC31:1; /* [31:31] Fault indication configuration flag for alarm 31 belonging to alarm group i - RW */
} SAC_FIPAG_Bits;

/* Port control */
typedef struct
{
    ureg32 HWDIR:2;       /* [1:0] Port direction - RW */
    ureg32 reserved_2:2;  /* [3:2] Internal reserved */
    ureg32 GFPES_EN:1;    /* [4:4] Glitch filter for errorpin FIP0 to PES enable - RW */
    ureg32 GFSTS_EN:1;    /* [5:5] Glitch filter for errorpin FIP0 to register STS enable - RW */
    ureg32 reserved_6:26; /* [31:6] Internal reserved */
} SAC_PCTL_Bits;

/* Alarm configuration register */
typedef struct
{
    ureg32 CF0:1;  /* [0:0] Configuration flag x (x=0-2) for alarm 0 belonging to alarm group i - RW */
    ureg32 CF1:1;  /* [1:1] Configuration flag x (x=0-2) for alarm 1 belonging to alarm group i - RW */
    ureg32 CF2:1;  /* [2:2] Configuration flag x (x=0-2) for alarm 2 belonging to alarm group i - RW */
    ureg32 CF3:1;  /* [3:3] Configuration flag x (x=0-2) for alarm 3 belonging to alarm group i - RW */
    ureg32 CF4:1;  /* [4:4] Configuration flag x (x=0-2) for alarm 4 belonging to alarm group i - RW */
    ureg32 CF5:1;  /* [5:5] Configuration flag x (x=0-2) for alarm 5 belonging to alarm group i - RW */
    ureg32 CF6:1;  /* [6:6] Configuration flag x (x=0-2) for alarm 6 belonging to alarm group i - RW */
    ureg32 CF7:1;  /* [7:7] Configuration flag x (x=0-2) for alarm 7 belonging to alarm group i - RW */
    ureg32 CF8:1;  /* [8:8] Configuration flag x (x=0-2) for alarm 8 belonging to alarm group i - RW */
    ureg32 CF9:1;  /* [9:9] Configuration flag x (x=0-2) for alarm 9 belonging to alarm group i - RW */
    ureg32 CF10:1; /* [10:10] Configuration flag x (x=0-2) for alarm 10 belonging to alarm group i - RW */
    ureg32 CF11:1; /* [11:11] Configuration flag x (x=0-2) for alarm 11 belonging to alarm group i - RW */
    ureg32 CF12:1; /* [12:12] Configuration flag x (x=0-2) for alarm 12 belonging to alarm group i - RW */
    ureg32 CF13:1; /* [13:13] Configuration flag x (x=0-2) for alarm 13 belonging to alarm group i - RW */
    ureg32 CF14:1; /* [14:14] Configuration flag x (x=0-2) for alarm 14 belonging to alarm group i - RW */
    ureg32 CF15:1; /* [15:15] Configuration flag x (x=0-2) for alarm 15 belonging to alarm group i - RW */
    ureg32 CF16:1; /* [16:16] Configuration flag x (x=0-2) for alarm 16 belonging to alarm group i - RW */
    ureg32 CF17:1; /* [17:17] Configuration flag x (x=0-2) for alarm 17 belonging to alarm group i - RW */
    ureg32 CF18:1; /* [18:18] Configuration flag x (x=0-2) for alarm 18 belonging to alarm group i - RW */
    ureg32 CF19:1; /* [19:19] Configuration flag x (x=0-2) for alarm 19 belonging to alarm group i - RW */
    ureg32 CF20:1; /* [20:20] Configuration flag x (x=0-2) for alarm 20 belonging to alarm group i - RW */
    ureg32 CF21:1; /* [21:21] Configuration flag x (x=0-2) for alarm 21 belonging to alarm group i - RW */
    ureg32 CF22:1; /* [22:22] Configuration flag x (x=0-2) for alarm 22 belonging to alarm group i - RW */
    ureg32 CF23:1; /* [23:23] Configuration flag x (x=0-2) for alarm 23 belonging to alarm group i - RW */
    ureg32 CF24:1; /* [24:24] Configuration flag x (x=0-2) for alarm 24 belonging to alarm group i - RW */
    ureg32 CF25:1; /* [25:25] Configuration flag x (x=0-2) for alarm 25 belonging to alarm group i - RW */
    ureg32 CF26:1; /* [26:26] Configuration flag x (x=0-2) for alarm 26 belonging to alarm group i - RW */
    ureg32 CF27:1; /* [27:27] Configuration flag x (x=0-2) for alarm 27 belonging to alarm group i - RW */
    ureg32 CF28:1; /* [28:28] Configuration flag x (x=0-2) for alarm 28 belonging to alarm group i - RW */
    ureg32 CF29:1; /* [29:29] Configuration flag x (x=0-2) for alarm 29 belonging to alarm group i - RW */
    ureg32 CF30:1; /* [30:30] Configuration flag x (x=0-2) for alarm 30 belonging to alarm group i - RW */
    ureg32 CF31:1; /* [31:31] Configuration flag x (x=0-2) for alarm 31 belonging to alarm group i - RW */
} SAC_ACAG_Bits;

/* Debug register */
typedef struct
{
    ureg32 reserved_0:27; /* [26:0] Internal reserved */
    ureg32 FSTS:1;        /* [27:27] Fault state timing status - RH */
    ureg32 FSMSTS:4;      /* [31:28] State machine status - RH */
} SAC_DBG_Bits;

/* SAC core alarm status register */
typedef struct
{
    ureg32 reserved_0:14; /* [13:0] Internal reserved */
    ureg32 BITALM:1;      /* [14:14] ALMCLR bit redundancy alarm - RH */
    ureg32 reserved_15:1; /* [15:15] Internal reserved */
    ureg32 COREFSMALM:1;  /* [16:16] SAC core fsm redundancy alarm - RH */
    ureg32 ALIVEALM:1;    /* [17:17] Core alive alarm - RH */
    ureg32 SESAC:1;       /* [18:18] SE alarm of SAC core - RH */
    ureg32 SFFPCTL:1;     /* [19:19] SFF alarm of PCTL register - RH */
    ureg32 SFFIETAC:1;    /* [20:20] SFF alarm of IETAC register - RH */
    ureg32 SFFIETC:1;     /* [21:21] SFF alarm of IETC register - RH */
    ureg32 SFFDBG:1;      /* [22:22] SFF alarm of DBG register - RH */
    ureg32 SFFSTS:1;      /* [23:23] SFF alarm of STS register - RH */
    ureg32 SFFFIP:1;      /* [24:24] SFF alarm of FIP register - RH */
    ureg32 SFFCMD:1;      /* [25:25] SFF alarm of CMD register - RH */
    ureg32 SFFAC2AGn:1;   /* [26:26] SFF alarm of AC2AGn register - RH */
    ureg32 SFFAC1AGn:1;   /* [27:27] SFF alarm of AC1AGn register - RH */
    ureg32 SFFAC0AGn:1;   /* [28:28] SFF alarm of AC0AGn register - RH */
    ureg32 SFFFIPAGn:1;   /* [29:29] SFF alarm of FIPAGn register - RH */
    ureg32 SFFAEX:1;      /* [30:30] SFF alarm of AEX register - RH */
    ureg32 SFFAGC:1;      /* [31:31] SFF alarm of AGC register - RH */
} SAC_ALMSTSCORE_Bits;

/* SAC core alarm control register */
typedef struct
{
    ureg32 reserved_0:16; /* [15:0] Internal reserved */
    ureg32 BUSERRMASK:2;  /* [17:16] Bus error mask - RW */
    ureg32 ALIVEALMEN:2;  /* [19:18] Core alive mechanism enable control - RW */
    ureg32 SFFALMEN:2;    /* [21:20] Redundancy mechanism enable control - RW */
    ureg32 FSMALMEN:2;    /* [23:22] FSM redundancy mechanism enable control - RW */
    ureg32 ALIVECLR:2;    /* [25:24] Core alive alarm clear control - RW */
    ureg32 FSMCLR:2;      /* [27:26] SAC core fsm redundancy alarm clear control - RW */
    ureg32 SFFCLR:2;      /* [29:28] SFF alarm clear control - RW */
    ureg32 SECLR:2;       /* [31:30] SE alarm clear control - RW */
} SAC_ALMCTRLCORE_Bits;

/* STDBY alarm 20 and 21 status register */
typedef struct
{
    ureg32 reserved_0:7; /* [6:0] Internal reserved */
    ureg32 SF7:1;  /* [7:7] Status flag7 in alarm status register i - RW */
    ureg32 reserved_8:1; /* [8:8] Internal reserved */
    ureg32 SF9:1;  /* [9:9] Status flag9 in alarm status register i - RW */
    ureg32 SF10:1; /* [10:10] Status flag10 in alarm status register i - RW */
    ureg32 SF11:1; /* [11:11] Status flag11 in alarm status register i - RW */
    ureg32 SF12:1; /* [12:12] Status flag12 in alarm status register i - RW */
    ureg32 SF13:1; /* [13:13] Status flag13 in alarm status register i - RW */
    ureg32 SF14:1; /* [14:14] Status flag14 in alarm status register i - RW */
    ureg32 SF15:1; /* [15:15] Status flag15 in alarm status register i - RW */
    ureg32 SF16:1; /* [16:16] Status flag16 in alarm status register i - RW */
    ureg32 SF17:1; /* [17:17] Status flag17 in alarm status register i - RW */
    ureg32 SF18:1; /* [18:18] Status flag18 in alarm status register i - RW */
    ureg32 SF19:1; /* [19:19] Status flag19 in alarm status register i - RW */
    ureg32 SF20:1; /* [20:20] Status flag20 in alarm status register i - RW */
    ureg32 SF21:1; /* [21:21] Status flag21 in alarm status register i - RW */
    ureg32 SF22:1; /* [22:22] Status flag22 in alarm status register i - RW */
    ureg32 SF23:1; /* [23:23] Status flag23 in alarm status register i - RW */
    ureg32 SF24:1; /* [24:24] Status flag24 in alarm status register i - RW */
    ureg32 SF25:1; /* [25:25] Status flag25 in alarm status register i - RW */
    ureg32 SF26:1; /* [26:26] Status flag26 in alarm status register i - RW */
    ureg32 SF27:1; /* [27:27] Status flag27 in alarm status register i - RW */
    ureg32 SF28:1; /* [28:28] Status flag28 in alarm status register i - RW */
    ureg32 SF29:1; /* [29:29] Status flag29 in alarm status register i - RW */
    ureg32 SF30:1; /* [30:30] Status flag30 in alarm status register i - RW */
    ureg32 SF31:1; /* [31:31] Status flag31 in alarm status register i - RW */
} SAC_ASRSTDBY_Bits;

/* STDBY alarm 20 and 21 FIP configuration register */
typedef struct
{
    ureg32 BITPROT:1; /* [0:0] Register bits protection */
    ureg32 reserved_1:6; /* [6:1] Internal reserved */
    ureg32 FC7:1;  /* [7:7] Fault indication configuration flag for alarm 7 belonging to alarm group i - RW */
    ureg32 reserved_8:1; /* [8:8] Internal reserved */
    ureg32 FC9:1;  /* [9:9] Fault indication configuration flag for alarm 9 belonging to alarm group i - RW */
    ureg32 FC10:1; /* [10:10] Fault indication configuration flag for alarm 10 belonging to alarm group i - RW */
    ureg32 FC11:1; /* [11:11] Fault indication configuration flag for alarm 11 belonging to alarm group i - RW */
    ureg32 FC12:1; /* [12:12] Fault indication configuration flag for alarm 12 belonging to alarm group i - RW */
    ureg32 FC13:1; /* [13:13] Fault indication configuration flag for alarm 13 belonging to alarm group i - RW */
    ureg32 FC14:1; /* [14:14] Fault indication configuration flag for alarm 14 belonging to alarm group i - RW */
    ureg32 FC15:1; /* [15:15] Fault indication configuration flag for alarm 15 belonging to alarm group i - RW */
    ureg32 FC16:1; /* [16:16] Fault indication configuration flag for alarm 16 belonging to alarm group i - RW */
    ureg32 FC17:1; /* [17:17] Fault indication configuration flag for alarm 17 belonging to alarm group i - RW */
    ureg32 FC18:1; /* [18:18] Fault indication configuration flag for alarm 18 belonging to alarm group i - RW */
    ureg32 FC19:1; /* [19:19] Fault indication configuration flag for alarm 19 belonging to alarm group i - RW */
    ureg32 FC20:1; /* [20:20] Fault indication configuration flag for alarm 20 belonging to alarm group i - RW */
    ureg32 FC21:1; /* [21:21] Fault indication configuration flag for alarm 21 belonging to alarm group i - RW */
    ureg32 FC22:1; /* [22:22] Fault indication configuration flag for alarm 22 belonging to alarm group i - RW */
    ureg32 FC23:1; /* [23:23] Fault indication configuration flag for alarm 23 belonging to alarm group i - RW */
    ureg32 FC24:1; /* [24:24] Fault indication configuration flag for alarm 24 belonging to alarm group i - RW */
    ureg32 FC25:1; /* [25:25] Fault indication configuration flag for alarm 25 belonging to alarm group i - RW */
    ureg32 FC26:1; /* [26:26] Fault indication configuration flag for alarm 26 belonging to alarm group i - RW */
    ureg32 FC27:1; /* [27:27] Fault indication configuration flag for alarm 27 belonging to alarm group i - RW */
    ureg32 FC28:1; /* [28:28] Fault indication configuration flag for alarm 28 belonging to alarm group i - RW */
    ureg32 FC29:1; /* [29:29] Fault indication configuration flag for alarm 29 belonging to alarm group i - RW */
    ureg32 FC30:1; /* [30:30] Fault indication configuration flag for alarm 30 belonging to alarm group i - RW */
    ureg32 FC31:1; /* [31:31] Fault indication configuration flag for alarm 31 belonging to alarm group i - RW */
} SAC_AGFIPSTDBY_Bits;

/* STDBY command register */
typedef struct
{
    ureg32 STBEN:2;        /* [1:0] STDBY enable */
    ureg32 FIPEN:2;        /* [3:2] STDBY FIP error pin enable */
    ureg32 ACEN:1;         /* [4:4] STDBY alarm status clear enable */
    ureg32 EMU:2;          /* [6:5] STDBY emulation */
    ureg32 FIPCTRL:2;      /* [8:7] STDBY FIP software control */
    ureg32 ALMCLR0:1;      /* [9:9] SFF fault inject. This bit Reserved in THA6412 and THA6104, Active in THA6206 */
    ureg32 BUSERRMASK:2;   /* [11:10] bus error mask */
    ureg32 SFFALMEN:2;     /* [13:12] SFF alarm enable */
    ureg32 FAULTEN:2;      /* [15:14] SFF fault inject */
    ureg32 ALMCLR:2;       /* [17:16] SFF fault inject. This bit Reserved in THA6206, Active in THA6412 */
    ureg32 reserved_18:12; /* [29:18] Internal reserved */
    ureg32 BITPROT:1;      /* [30:30] STDBY register bits protection */
    ureg32 reserved_31:1;  /* [31:31] Internal reserved */
} SAC_CMDSTDBY_Bits;

/* STDBY alarm status register */
typedef struct
{
#if defined (THA6_THA6412) || defined (THA6_THA6104)
    ureg32 SFFCMD:1;       /* [0:0] Sff_alm of CMDSTDBY register */
    ureg32 SFFASR21FIP:1;  /* [1:1] Sff_alm of ASR21FIP register */
    ureg32 SFFASR20FIP:1;  /* [2:2] Sff_alm of ASR20FIP register */
#endif    
#if defined (THA6_THA6206) || defined (THA6_THA6206D)
    ureg32 reserved_0:3;   /* [2:0] Internal reserved */
#endif
    ureg32 SECMD:1;        /* [3:3] Se_alm of CMDSTDBY register */
    ureg32 SEAG21FIP:1;    /* [4:4] Se_alm of ASR21FIP register */
    ureg32 SEAG20FIP:1;    /* [5:5] Se_alm of ASR20FIP register */
    ureg32 SEASR21:1;      /* [6:6] Se_alm of ASR21STDBY register */
    ureg32 SEASR20:1;      /* [7:7] Se_alm of ASR20STDBY register */
#if defined (THA6_THA6412) || defined (THA6_THA6104) 
    ureg32 EMUBIT:1;       /* [8:8] Bit_alm of EMU */
    ureg32 STBENBIT:1;     /* [9:9] Bit_alm of STBEN */
    ureg32 MASKBIT:1;      /* [10:10] Bit_alm of buserrmask */
    ureg32 SFFENBIT:1;     /* [11:11] Bit_alm of SFFALMEN  */
    ureg32 FIPENBIT:1;     /* [12:12] Bit_alm of FIPEN  */
    ureg32 FAULTBIT:1;     /* [13:13] Bit_alm of FAULTEN  */
    ureg32 ALMCLRBIT:1;    /* [14:14] Bit_alm of ALMCLR  */
    ureg32 reserved_31:17; /* [31:15] Internal reserved */
#endif    
#if defined (THA6_THA6206) || defined (THA6_THA6206D)
    ureg32 reserved_8:24; /* [31:8] Internal reserved */
#endif
} SAC_ALMSTSSTDBY_Bits;

/**********************************************************************************************************************
 *                                          SAC Register Bit-Fields Definitions
 *********************************************************************************************************************/

/* Alarm global configuration register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    SAC_AGC_Bits B; /* Bitfield access */
} SAC_AGC;

/* Alarm executed status register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    SAC_AEX_Bits B; /* Bitfield access */
} SAC_AEX;

/* Alarm executed status clear register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;          /* Unsigned access */
    SAC_AEXCLR_Bits B; /* Bitfield access */
} SAC_AEXCLR;

/* Alarm and fault counter register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    SAC_AFCNT_Bits B; /* Bitfield access */
} SAC_AFCNT;

/* Alarm status register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    SAC_ASR_Bits B; /* Bitfield access */
} SAC_ASR;

/* Alarm backup register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;      /* Unsigned access */
    SAC_AB_Bits B; /* Bitfield access */
} SAC_AB;

/* Module identification register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;      /* Unsigned access */
    SAC_ID_Bits B; /* Bitfield access */
} SAC_ID;

/* Command register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    SAC_CMD_Bits B; /* Bitfield access */
} SAC_CMD;

/* Key register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    SAC_KEYS_Bits B; /* Bitfield access */
} SAC_KEYS;

/* Fault indication protocol */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    SAC_FIP_Bits B; /* Bitfield access */
} SAC_FIP;

/* Status register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    SAC_STS_Bits B; /* Bitfield access */
} SAC_STS;

/* ES glitch filter configuration */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    SAC_ESGLF_Bits B; /* Bitfield access */
} SAC_ESGLF;

/* Interrupt execution timer configuration */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    SAC_IETC_Bits B; /* Bitfield access */
} SAC_IETC;

/* Interrupt execution timer 0 alarm configuration 0 */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    SAC_IETAC00_Bits B; /* Bitfield access */
} SAC_IETAC00;

/* Interrupt execution timer 0 alarm configuration 1 */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    SAC_IETAC01_Bits B; /* Bitfield access */
} SAC_IETAC01;

/* Interrupt execution timer 1 alarm configuration 0 */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    SAC_IETAC10_Bits B; /* Bitfield access */
} SAC_IETAC10;

/* Interrupt execution timer 1 alarm configuration 1 */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;           /* Unsigned access */
    SAC_IETAC11_Bits B; /* Bitfield access */
} SAC_IETAC11;

/* FIP configuration register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;         /* Unsigned access */
    SAC_FIPAG_Bits B; /* Bitfield access */
} SAC_FIPAG;

/* Port control */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    SAC_PCTL_Bits B; /* Bitfield access */
} SAC_PCTL;

/* Alarm configuration register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;        /* Unsigned access */
    SAC_ACAG_Bits B; /* Bitfield access */
} SAC_ACAG;

/* Debug register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;       /* Unsigned access */
    SAC_DBG_Bits B; /* Bitfield access */
} SAC_DBG;

/* SAC core alarm status register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAC_ALMSTSCORE_Bits B; /* Bitfield access */
} SAC_ALMSTSCORE;

/* SAC core alarm control register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SAC_ALMCTRLCORE_Bits B; /* Bitfield access */
} SAC_ALMCTRLCORE;

/* STDBY alarm 20 and 21 status register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAC_ASRSTDBY_Bits B; /* Bitfield access */
} SAC_ASRSTDBY;


/* STDBY alarm 20 and 21 FIP configuration register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAC_AGFIPSTDBY_Bits B; /* Bitfield access */
} SAC_AGFIPSTDBY;


/* STDBY command register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAC_CMDSTDBY_Bits B; /* Bitfield access */
} SAC_CMDSTDBY;

/* STDBY alarm status register */
typedef union
/* #Violation: sac_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SAC_ALMSTSSTDBY_Bits B; /* Bitfield access */
} SAC_ALMSTSSTDBY;

/**********************************************************************************************************************
 *                                        SAC Register Configuration Structure
 *********************************************************************************************************************/

typedef volatile struct
{
    SAC_AGC AGC;                                  /* 0x00 - Alarm global configuration register */
    SAC_AEX AEX;                                  /* 0x04 - Alarm executed status register */
    SAC_AEXCLR AEXCLR;                            /* 0x08 - Alarm executed status clear register */
    SAC_AFCNT AFCNT;                              /* 0x0C - Alarm and fault counter register */
    SAC_ASR ASR[SAC_ALAM_GUPMUM];             /* 0x10 - Alarm status register */
    ureg32 RESERVED_0044[11];                     /* 0x44 - Internal reserved  */
    SAC_AB AB[SAC_ALAM_GUPMUM];               /* 0x70 - Alarm backup register */
    ureg32 RESERVED_00A4[24];                     /* 0xA4 - Internal reserved  */
    SAC_ID ID;                                    /* 0x104 - Module identification register */
    SAC_CMD CMD;                                  /* 0x108 - Command register */
    SAC_KEYS KEYS;                                /* 0x10C - Key register */
    SAC_FIP FIP;                                  /* 0x110 - Fault indication protocol */
    SAC_STS STS;                                  /* 0x114 - Status register */
    SAC_ESGLF ESGLF;                              /* 0x118 - ES glitch filter configuration */
    ureg32 RESERVED_011C[9];                      /* 0x11C - Internal reserved  */
    SAC_IETC IETC;                                /* 0x140 - Interrupt execution timer configuration */
    SAC_IETAC00 IETAC00;                          /* 0x144 - Interrupt execution timer 0 alarm configuration 0 */
    SAC_IETAC01 IETAC01;                          /* 0x148 - Interrupt execution timer 0 alarm configuration 1 */
    SAC_IETAC10 IETAC10;                          /* 0x14C - Interrupt execution timer 1 alarm configuration 0 */
    SAC_IETAC11 IETAC11;                          /* 0x150 - Interrupt execution timer 1 alarm configuration 1 */
    ureg32 RESERVED_0154[3];                      /* 0x154 - Internal reserved  */
    SAC_FIPAG FIPAG[SAC_ALAM_GUPMUM];         /* 0x160 - FIP configuration register */
    ureg32 RESERVED_0194[27];                     /* 0x194 - Internal reserved  */
    SAC_PCTL PCTL;                                /* 0x200 - Port control */
    ureg32 RESERVED_0204[3];                      /* 0x204 - Internal reserved  */
    SAC_ACAG AC0AG[SAC_ALAM_GUPMUM];          /* 0x210 - Alarm configuration register */
    ureg32 RESERVED_0244[3];                      /* 0x244 - Internal reserved  */
    SAC_ACAG AC1AG[SAC_ALAM_GUPMUM];          /* 0x250 - Alarm configuration register */
    ureg32 RESERVED_0284[3];                      /* 0x284 - Internal reserved  */
    SAC_ACAG AC2AG[SAC_ALAM_GUPMUM];          /* 0x290 - Alarm configuration register */
    ureg32 RESERVED_0324[15];                     /* 0x2C4 - Internal reserved  */
    SAC_DBG DBG;                                  /* 0x300 - Debug register */
    SAC_ALMSTSCORE ALMSTSCORE;                    /* 0x304 - SAC core alarm status register */
    SAC_ALMCTRLCORE ALMCTRLCORE;                  /* 0x308 - SAC core alarm control register */
} SAC_MODULE;

typedef volatile struct
{
    SAC_ASRSTDBY ASRSTDBY[SAC_STDB_ALAM_GUPMUM]; /* 0x00 - STDBY alarm 20 and 21 status register */
    ureg32 RESERVED_0008[2];     /* 0x08 - Internal reserved  */
    SAC_AGFIPSTDBY AGFIPSTDBY[SAC_STDB_ALAM_GUPMUM]; /* 0x10 - STDBY alarm 20 and 21 FIP configuration register */
    ureg32 RESERVED_0018[2];     /* 0x18 - Internal reserved */
    SAC_CMDSTDBY CMDSTDBY;     /* 0x20 - STDBY command register */
    SAC_ALMSTSSTDBY ALMSTSSTDBY; /* 0x24 - STDBY alarm status register */
} SAC_STDBY_MODULE;

/**********************************************************************************************************************
 *                                                  SAC Module Object
 *********************************************************************************************************************/

#define PWRCSTBY_SWP *(ureg32 volatile *)(0xD0060000U) /* SWP register address of PWRCSTBY module */

#endif /* SAC_REGISTER_H */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  saradc_register.h
 * Author:    30037
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all definitions of SARADC module registers
 *********************************************************************************************************************/
/*
*#Violation Summary
*#saradc_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification: Using unions for bit-field access to registers.
*/

#ifndef SARADC_REGISTER_H_
#define SARADC_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                        SARADC Register Bit-Fields Definitions
 *********************************************************************************************************************/
/** \brief Queue 2 trigger control register */
typedef struct
{
    ureg32 TRICNT:6;       /*[5:0] trigger counter */
    ureg32 reserved_6:2;   /*[7:6] Reserved.*/
    ureg32 TRICNTSET:6;    /*[13:8] trigger counter set*/
    ureg32 reserved_14:2;  /*[15:14] Reserved.*/
    ureg32 INTRISEL:1;     /*[16:16] Internal trigger select*/
    ureg32 reserved_17:15; /*[31:17] Reserved.*/
} SARADC_Q2TRICTRL_Bits;

/** \brief Analog configration register */
typedef struct
{
    ureg32 ANAEN:1;       /*[0:0] SARADC analog enable*/
#if defined (THA6_THA6206D)
    ureg32 CH2PDDEN:1;    /*[1:1] Channel2 global strong pull-down enable */
#endif
#if defined (THA6_THA6206) || defined (THA6_THA6104) || defined (THA6_THA6412)
    ureg32 reserved_1:1;  /*[1:1] Reserved */
#endif
    ureg32 ANARESO:2;     /*[3:2] SARADC converter resolution.*/
    ureg32 CALIC:1;       /*[4:4] Calibration control*/
    ureg32 DISHEN:1;      /*[5:5] Calibration offset enable*/
    ureg32 reserved_6:2;  /*[7:6] Reserved*/
    ureg32 ANADIVF:8;     /*[15:8] SARADC divider factor for the analog internal clock*/
    ureg32 OFFSET:6;      /*[21:16] SARADC offset*/
    ureg32 reserved_22:9; /*[30:22] Reserved*/
    ureg32 ANAFLG:1;      /*[31:31] SARADC analog flag*/
} SARADC_ANACFG_Bits;

/** \brief Arbiter control register */
typedef volatile struct
{
    ureg32 PRIOL0:2;      /* [1:0] Priority level of queue 0  */
    ureg32 reserved_2:1;  /* [2:2] Reserved */
    ureg32 CONSMODE0:1;   /* [3:3] Conversion start mode of queue 0 */
    ureg32 PRIOL1:2;      /* [5:4] Priority level of queue 1 */
    ureg32 reserved_6:1;  /* [6:6] Reserved */
    ureg32 CONSMODE1:1;   /* [7:7]  Conversion start mode of queue 1 */
    ureg32 PRIOL2:2;      /* [9:8]  Priority level of queue 2 */
    ureg32 reserved_10:1; /* [10:10] Reserved */
    ureg32 CONSMODE2:1;   /* [11:11]  Conversion start mode of queue 2 */
    ureg32 reserved_:1;   /* [12:12] Reserved */
    ureg32 INJECT0CLR:1;  /* [13:13]  Queue0 inject clear */
    ureg32 INJECT1CLR:1;  /* [14:14]  Queue1 inject clear */
    ureg32 INJECT2CLR:1;  /* [15:15]  Queue2 inject clear */
    ureg32 Q0WAIT:1;      /* [16:16]  Queue0 wait status */
    ureg32 Q1WAIT:1;      /* [17:17]  Queue1 wait status */
    ureg32 Q2WAIT:1;      /* [18:18]  Queue2 wait status */
    ureg32 reserved_19:1; /* [19:19] Reserved */
    ureg32 Q0BUSY:1;      /* [20:20]  Queue0 busy flag */
    ureg32 Q1BUSY:1;      /* [21:21]  Queue1 busy flag */
    ureg32 Q2BUSY:1;      /* [22:22]  Queue2 busy flag */
    ureg32 SYNCBUSY:1;    /* [23:23]  Synchronous queue busy flag */
    ureg32 ARBEN0:1;      /* [24:24]  Arbitration queue0 enable */
    ureg32 ARBEN1:1;      /* [25:25]  Arbitration queue1 enable */
    ureg32 ARBEN2:1;      /* [26:26]  Arbitration queue2 enable */
    ureg32 INJECT0STA:1;  /* [27:27]  Queue0 inject status */
    ureg32 INJECT1STA:1;  /* [28:28]  Queue1 inject status */
    ureg32 INJECT2STA:1;  /* [29:29]  Queue2 inject status */
    ureg32 reserved_30:2; /* [31:30] Reserved */
} SARADC_ARBCTRL_Bits;

/** \brief Sample time control register */
typedef volatile struct
{
    ureg32 STCTRL:8;      /* [7:0] Sample time control */
    ureg32 reserved_8:24; /* [31:8] Reserved */
} SARADC_SAMCTRL_Bits;

/** \brief Functional bound control register */
typedef volatile struct
{
    ureg32 BOUNDL:12;   /* [11:0]Software set lower boundary*/
    ureg32 BOUNDLSEL:4; /* [15:12]lower boundary selection*/
    ureg32 BOUNDU:12;   /* [27:16]Software set upper boundary*/
    ureg32 BOUNDUSEL:4; /* [31:28]Upper boundary selection */
} SARADC_FUNBOUND_Bits;

/** \brief Synchronous converter control register */
typedef volatile struct
{
    ureg32 SYNCSEL:2;     /* [1:0]Synchronous converter source selection*/
    ureg32 reserved_2:2;  /* [3:2] Reserved */
    ureg32 SYNCEN1:1;   /* [4:4]Synchronous converter phase follow CI1*/
    ureg32 SYNCEN2:1;   /* [5:5]Synchronous converter phase follow CI2 */
    ureg32 SYNCEN3:1;   /* [6:6]Synchronous converter phase follow CI3  */
    ureg32 reserved_7:25; /* [31:7] Reserved */
} SARADC_SYNCCTRL_Bits;

/** \brief Queue trigger configuration register */
typedef volatile struct
{
    ureg32 reserved_0:6;  /* [5:0] Reserved */
    ureg32 TRISEL:2;      /* [7:6]Trigger selection */
    ureg32 EXTTRISEL:4;   /* [11:8]External trigger selection */
    ureg32 EXTTRILVL:1;   /* [12:12]External trigger level */
    ureg32 TRIMODE:2;     /* [14:13]Trigger mode */
    ureg32 TRWE:1;        /* [15:15]Trigger register write enable*/
    ureg32 GATESEL:4;     /* [19:16]Gate selection */
    ureg32 GATELVL:1;     /* [20:20]Gate level  */
    ureg32 reserved_21:2; /* [22:21] Reserved */
    ureg32 GSWE:1;        /* [23:23]GATESEL register write enable */
    ureg32 reserved_23:8; /* [31:24] Reserved */
} SARADC_QTRICTRL_Bits;

/** \brief Queue mode control register */
typedef volatile struct
{
    ureg32 GATEEN:2;       /* [1:0]Gate enable*/
    ureg32 reserved_2:2;   /* [3:2] Reserved */
    ureg32 EXTTRIEN:1;     /* [4:4]External trigger enable */
    ureg32 reserved_5:3;   /* [7:5] Reserved */
    ureg32 STRIGEN:1;      /* [8:8]Software trigger generation */
    ureg32 reserved_9:3;   /* [11:9] Reserved */
    ureg32 FLUQU:1;        /* [12:12]Flush queue */
    ureg32 reserved_13:19; /* [31:13] Reserved */
} SARADC_QMODE_Bits;

/** \brief Queue input configration register */
typedef volatile struct
{
    ureg32 REQCHN:5;       /* [4:0]Conversion request channel number */
    ureg32 RFEN:1;         /* [5:5]Refill enable  */
    ureg32 reserved_6:1;   /* [6:6] Reserved */
    ureg32 EXTEREN:1;      /* [7:7]External trigger enable */
    ureg32 QIEN:1;         /* [8:8]Source interrupt enable  */
    ureg32 MDLPD:1;        /* [9:9]Multiplexer diagnostics pull down with low resistance enable */
    ureg32 MDPD:1;         /* [10:10]Multiplexer diagnostics pull down enable  */
    ureg32 MDPU:1;         /* [11:11]Multiplexer diagnostics pull up enable  */
    ureg32 CDEN:1;         /* [12:12]Converter diagnostics enable  */
    ureg32 CONDSEL:2;      /* [14:13]Converter diagnostics selection  */
    ureg32 SUCCEEN:1;      /* [15:15]Successive converter enable  */
    ureg32 reserved_16:16; /* [31:16] Reserved */
} SARADC_QINCFG_Bits;

/** \brief Queue  request timer mode register */
typedef volatile struct
{
    ureg32 SEQTMOD:2;      /* [1:0]Sequence timer mode*/
    ureg32 reserved_2:6;   /* [7:2] Reserved */
    ureg32 SEQTVALUE:8;    /* [15:8]Sequence timer value */
    ureg32 STRITEN:1;      /* [16:16]Software trigger timer enable */
    ureg32 EXTTRITEN:1;    /* [17:17]External trigger timer enable */
    ureg32 reserved_18:14; /* [31:18] Reserved */
} SARADC_QREQTM_Bits;

/** \brief Channel control register */
typedef volatile struct
{
    ureg32 CHINTMODE:2;   /* [1:0]Channel interrupt mode  */
    ureg32 SYNCREQ:1;     /* [2:2]Synchronization request */
    ureg32 BOUNDSEL:2;    /* [4:3]Boundary selection  */
    ureg32 BOUNDDR:1;     /* [5:5]Discard result out of boundary  */
    ureg32 BOUNDRS:1;     /* [6:6]Boundary range selection  */
    ureg32 reserved_7:1;  /* [7:7] Reserved */
    ureg32 RESSTTAR:1;    /* [8:8]Result store target */
    ureg32 reserved_9:3;  /* [11:9] Reserved */
    ureg32 RESSTREG:4;    /* [15:12]Result store register  */
    ureg32 DREDCTRL:4;    /* [19:16]Data reduction control  */
    ureg32 HDIFCEN:1;     /* [20:20]HDI interface to FC enable   */
    ureg32 HDIGTMEN:1;    /* [21:21]HDI interface to GTM enable   */
    ureg32 HDIRDCEN:1;    /* [22:22]HDI interface to RDC enable */
    ureg32 reserved_23:1; /* [23:23] Reserved */
    ureg32 BWDETEN:1;     /* [24:24]Broken wire detection enable */
    ureg32 BWDREFSEL:1;   /* [25:25]Broken wire reference voltage selection  */
    ureg32 reserved_26:6; /* [31:26] Reserved */
} SARADC_CHCTRL_Bits;

/** \brief Result control register */
typedef volatile struct
{
    ureg32 WFRMODE:1;     /* [0:0] Wait-for-read mode */
    ureg32 reserved_1:3;  /* [3:1] Reserved */
    ureg32 RESALI:1;      /* [4:4] Result alignment */
    ureg32 reserved_5:3;  /* [7:5] Reserved */
    ureg32 NRINTEN:1;     /* [8:8] New result interrupt enable */
    ureg32 reserved_9:23; /* [31:9] Reserved */
} SARADC_RESCTRL_Bits;

/** \brief Result register */
typedef volatile struct
{
    ureg32 CONRESULT:16;  /* [15:0]Result of most recent conversion*/
    ureg32 CHNUM:5;       /* [20:16]Channel number */
    ureg32 CONREQS:2;     /* [22:21]Converted request source  */
    ureg32 reserved_23:1; /* [23:23] Reserved */
    ureg32 VFLAG:1;       /* [24:24]Valid flag  */
    ureg32 reserved_25:7; /* [31:25] Reserved */
} SARADC_RESULT_Bits;

/** \brief Result debug register */
typedef volatile struct
{
    ureg32 CONRESULT:16;  /* [15:0]Result of most recent conversion */
    ureg32 CHNUM:5;       /* [20:16]Channel number */
    ureg32 CONREQS:2;     /* [22:21]Converted request source */
    ureg32 reserved_23:1; /* [23:23] Reserved */
    ureg32 VFLAG:1;       /* [24:24]Valid flag  */
    ureg32 reserved_25:7; /* [31:25] Reserved */
} SARADC_RESULTD_Bits;

/** \brief Channel interrupt flag register */
typedef volatile struct
{
    ureg32 CINT0:1;        /* [0:0]Channel interrupt for channel 0 */
    ureg32 CINT1:1;        /* [1:1]Channel interrupt for channel 1 */
    ureg32 CINT2:1;        /* [2:2]Channel interrupt for channel 2 */
    ureg32 CINT3:1;        /* [3:3]Channel interrupt for channel 3 */
    ureg32 CINT4:1;        /* [4:4]Channel interrupt for channel 4 */
    ureg32 CINT5:1;        /* [5:5]Channel interrupt for channel 5 */
    ureg32 CINT6:1;        /* [6:6]Channel interrupt for channel 6 */
    ureg32 CINT7:1;        /* [7:7]Channel interrupt for channel 7 */
    ureg32 CINT8:1;        /* [8:8]Channel interrupt for channel 8 */
    ureg32 CINT9:1;        /* [9:9]Channel interrupt for channel 9 */
    ureg32 CINT10:1;       /* [10:10]Channel interrupt for channel 10  */
    ureg32 CINT11:1;       /* [11:11]Channel interrupt for channel 11 */
    ureg32 CINT12:1;       /* [12:12]Channel interrupt for channel 12, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 CINT13:1;       /* [13:13]Channel interrupt for channel 13, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 CINT14:1;       /* [14:14]Channel interrupt for channel 14, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 CINT15:1;       /* [15:15]Channel interrupt for channel 15, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 reserved_16:14; /* [29:16] Reserved */
    ureg32 CMASK:2;        /* [31:30] Mask channel interrupt */
} SARADC_CINTCTRL_Bits;

/** \brief Result interrupt flag register */
typedef volatile struct
{
    ureg32 RINT0:1;        /* [0:0]Result interrupt for RESULT 0  */
    ureg32 RINT1:1;        /* [1:1]Result interrupt for RESULT 1  */
    ureg32 RINT2:1;        /* [2:2]Result interrupt for RESULT 2  */
    ureg32 RINT3:1;        /* [3:3]Result interrupt for RESULT 3  */
    ureg32 RINT4:1;        /* [4:4]Result interrupt for RESULT 4  */
    ureg32 RINT5:1;        /* [5:5]Result interrupt for RESULT 5  */
    ureg32 RINT6:1;        /* [6:6]Result interrupt for RESULT 6  */
    ureg32 RINT7:1;        /* [7:7]Result interrupt for RESULT 7  */
    ureg32 RINT8:1;        /* [8:8]Result interrupt for RESULT 8  */
    ureg32 RINT9:1;        /* [9:9]Result interrupt for RESULT 9  */
    ureg32 RINT10:1;       /* [10:10]Result interrupt for RESULT 10  */
    ureg32 RINT11:1;       /* [11:11]Result interrupt for RESULT 11  */
    ureg32 RINT12:1;       /* [12:12]Result interrupt for RESULT 12  */
    ureg32 RINT13:1;       /* [13:13]Result interrupt for RESULT 13  */
    ureg32 RINT14:1;       /* [14:14]Result interrupt for RESULT 14 */
    ureg32 RINT15:1;       /* [15:15]Result interrupt for RESULT 15  */
    ureg32 reserved_16:14; /* [29:16] Reserved */
    ureg32 RMASK:2;        /* [31:30] Mask result interrupt */
} SARADC_RINTCTRL_Bits;

/** \brief Source interrupt flag register */
typedef volatile struct
{
    ureg32 SINT0:1;       /* [0:0]Source interrupt for queue 0  */
    ureg32 SINT1:1;       /* [1:1]Source interrupt for queue 1  */
    ureg32 SINT2:1;       /* [2:2]Source interrupt for queue 2  */
    ureg32 reserved_3:27; /* [29:3] Reserved */
    ureg32 SMASK:2;       /* [31:30] Mask source interrupt */
} SARADC_SINTCTRL_Bits;

/** \brief Channel interrupt clear register */
typedef volatile struct
{
    ureg32 CCLR0:1;        /* [0:0]Channel 0 interrupt clear */
    ureg32 CCLR1:1;        /* [1:1]Channel 1 interrupt clear */
    ureg32 CCLR2:1;        /* [2:2]Channel 2 interrupt clear */
    ureg32 CCLR3:1;        /* [3:3]Channel 3 interrupt clear */
    ureg32 CCLR4:1;        /* [4:4]Channel 4 interrupt clear */
    ureg32 CCLR5:1;        /* [5:5]Channel 5 interrupt clear */
    ureg32 CCLR6:1;        /* [6:6]Channel 6 interrupt clear */
    ureg32 CCLR7:1;        /* [7:7]Channel 7 interrupt clear */
    ureg32 CCLR8:1;        /* [8:8]Channel 8 interrupt clear */
    ureg32 CCLR9:1;        /* [9:9]Channel 9 interrupt clear */
    ureg32 CCLR10:1;       /* [10:10]Channel 10 interrupt clear  */
    ureg32 CCLR11:1;       /* [11:11]Channel 11 interrupt clear */
    ureg32 CCLR12:1;       /* [12:12]Channel 12 interrupt clear, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 CCLR13:1;       /* [13:13]Channel 13 interrupt clear, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 CCLR14:1;       /* [14:14]Channel 14 interrupt clear, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 CCLR15:1;       /* [15:15]Channel 15 interrupt clear, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 reserved_16:16; /* [31:16] Reserved */  
} SARADC_CINTCLR_Bits;

/** \brief Result interrupt clear register */
typedef volatile struct
{
    ureg32 RCLR0:1;        /* [0:0]Result 0 interrupt clear  */
    ureg32 RCLR1:1;        /* [1:1]Result 1 interrupt clear  */
    ureg32 RCLR2:1;        /* [2:2]Result 2 interrupt clear  */
    ureg32 RCLR3:1;        /* [3:3]Result 3 interrupt clear  */
    ureg32 RCLR4:1;        /* [4:4]Result 4 interrupt clear  */
    ureg32 RCLR5:1;        /* [5:5]Result 5 interrupt clear  */
    ureg32 RCLR6:1;        /* [6:6]Result 6 interrupt clear  */
    ureg32 RCLR7:1;        /* [7:7]Result 7 interrupt clear  */
    ureg32 RCLR8:1;        /* [8:8]Result 8 interrupt clear  */
    ureg32 RCLR9:1;        /* [9:9]Result 9 interrupt clear  */
    ureg32 RCLR10:1;       /* [10:10]Result 10 interrupt clear  */
    ureg32 RCLR11:1;       /* [11:11]Result 11 interrupt clear  */
    ureg32 RCLR12:1;       /* [12:12]Result 12 interrupt clear  */
    ureg32 RCLR13:1;       /* [13:13]Result 13 interrupt clear  */
    ureg32 RCLR14:1;       /* [14:14]Result 14 interrupt clear  */
    ureg32 RCLR15:1;       /* [15:15]Result 15 interrupt clear  */
    ureg32 reserved_16:16; /* [31:16] Reserved */
} SARADC_RINTCLR_Bits;

/** \brief Queue interrupt clear register */
typedef volatile struct
{
    ureg32 SCLR0:1;       /* [0:0]Queue 0 interrupt clear */
    ureg32 SCLR1:1;       /* [1:1]Queue 1 interrupt clear */
    ureg32 SCLR2:1;       /* [2:2]Queue 2 interrupt clear */
    ureg32 reserved_3:29; /* [31:3] Reserved */
} SARADC_SINTCLR_Bits;

/** \brief Channel interrupt node pointer 0 register */
typedef volatile struct
{
    ureg32 CINT0NP:4; /* [3:0]Channel 0 interrupt node pointer */
    ureg32 CINT1NP:4; /* [7:4]Channel 1 interrupt node pointer */
    ureg32 CINT2NP:4; /* [11:8]Channel 2 interrupt node pointer */
    ureg32 CINT3NP:4; /* [15:12]Channel 3 interrupt node pointer */
    ureg32 CINT4NP:4; /* [19:16]Channel 4 interrupt node pointer */
    ureg32 CINT5NP:4; /* [23:20]Channel 5 interrupt node pointer */
    ureg32 CINT6NP:4; /* [27:24]Channel 6 interrupt node pointer */
    ureg32 CINT7NP:4; /* [31:28]Channel 7 interrupt node pointer */
} SARADC_CINTNP0_Bits;

/** \brief Channel interrupt node pointer 1 register */
typedef volatile struct
{
    ureg32 CINT8NP:4;  /* [3:0]Channel 8 interrupt node pointer */
    ureg32 CINT9NP:4;  /* [7:4]Channel 9 interrupt node pointer */
    ureg32 CINT10NP:4; /* [11:8]Channel 10 interrupt node pointer */
    ureg32 CINT11NP:4; /* [15:12]Channel 11 interrupt node pointer */
    ureg32 CINT12NP:4; /* [19:16]Channel 12 interrupt node pointer, This bit reserved in THA6206 and THA6412, Active in and THA610 */
    ureg32 CINT13NP:4; /* [23:20]Channel 13 interrupt node pointer, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 CINT14NP:4; /* [27:24]Channel 14 interrupt node pointer, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 CINT15NP:4; /* [31:28]Channel 15 interrupt node pointer, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
} SARADC_CINTNP1_Bits;

/** \brief Result interrupt node pointer 0 register */
typedef volatile struct
{
    ureg32 RINT0NP:4; /* [3:0]Result 0 interrupt node pointer  */
    ureg32 RINT1NP:4; /* [7:4]Result 1 interrupt node pointer  */
    ureg32 RINT2NP:4; /* [11:8]Result 2 interrupt node pointer  */
    ureg32 RINT3NP:4; /* [15:12]Result 3 interrupt node pointer  */
    ureg32 RINT4NP:4; /* [19:16]Result 4 interrupt node pointer  */
    ureg32 RINT5NP:4; /* [23:20]Result 5 interrupt node pointer */
    ureg32 RINT6NP:4; /* [27:24]Result 6 interrupt node pointer  */
    ureg32 RINT7NP:4; /* [31:28]Result 7 interrupt node pointer  */
} SARADC_RINTNP0_Bits;

/** \brief Result interrupt node pointer 1 register */
typedef volatile struct
{
    ureg32 RINT8NP:4;  /* [3:0]Result 8 interrupt node pointer */
    ureg32 RINT9NP:4;  /* [7:4]Result 9 interrupt node pointer  */
    ureg32 RINT10NP:4; /* [11:8]Result 10 interrupt node pointer */
    ureg32 RINT11NP:4; /* [15:12]Result 11 interrupt node pointer  */
    ureg32 RINT12NP:4; /* [19:16]Result 12 interrupt node pointer  */
    ureg32 RINT13NP:4; /* [23:20]Result 13 interrupt node pointer  */
    ureg32 RINT14NP:4; /* [27:24]Result 14 interrupt node pointer  */
    ureg32 RINT15NP:4; /* [31:28]Result 15 interrupt node pointer  */
} SARADC_RINTNP1_Bits;

/** \brief Source interrupt node pointer register */
typedef volatile struct
{
    ureg32 SINT0NP:4;      /* [3:0]Source 0 interrupt node pointer*/
    ureg32 SINT1NP:4;      /* [7:4]Source 1 interrupt node pointer  */
    ureg32 SINT2NP:4;      /* [11:8]Source 2 interrupt node pointer  */
    ureg32 reserved_12:20; /* [31:12] Reserved */
} SARADC_SINTNP_Bits;

/** \brief Software trigger interrupt register */
typedef volatile struct
{
    ureg32 SAGINT0:1;      /* [0:0]Software activate group interrupt 0 */
    ureg32 SAGINT1:1;      /* [1:1]Software activate group interrupt 1  */
    ureg32 SAGINT2:1;      /* [2:2]Software activate group interrupt 2  */
    ureg32 SAGINT3:1;      /* [3:3]Software activate group interrupt 3  */
    ureg32 reserved_4:4;   /* [7:4] Reserved */
    ureg32 SASINT0:1;      /* [8:8]Software activate shared interrupt 0  */
    ureg32 SASINT1:1;      /* [9:9]Software activate shared interrupt 1  */
    ureg32 SASINT2:1;      /* [10:10]Software activate shared interrupt 2  */
    ureg32 SASINT3:1;      /* [11:11]Software activate shared interrupt 3  */
    ureg32 reserved_12:20; /* [31:12] Reserved */
} SARADC_STRIINT_Bits;

/** \brief Alias channel register  */
typedef volatile struct
{
    ureg32 ALIASCH:5;     /* [4:0] Alias channel for CH0 conversion */
    ureg32 reserved_5:27; /* [31:5] Reserved */
} SARADC_ALIASCH_Bits;

/** \brief DMA enable control register */
typedef volatile struct
{
    ureg32 DMAEN0:1;       /* [0:0]DMA enable 0 */
    ureg32 DMAEN1:1;       /* [1:1]DMA enable 1 */
    ureg32 DMAEN2:1;       /* [2:2]DMA enable 2 */
    ureg32 DMAEN3:1;       /* [3:3]DMA enable 3 */
    ureg32 DMAEN4:1;       /* [4:4]DMA enable 4 */
    ureg32 DMAEN5:1;       /* [5:5]DMA enable 5 */
    ureg32 DMAEN6:1;       /* [6:6]DMA enable 6 */
    ureg32 DMAEN7:1;       /* [7:7]DMA enable 7 */
    ureg32 DMAEN8:1;       /* [8:8]DMA enable 8 */
    ureg32 DMAEN9:1;       /* [9:9]DMA enable 9 */
    ureg32 DMAEN10:1;      /* [10:10]DMA enable 10 */
    ureg32 DMAEN11:1;      /* [11:11]DMA enable 11 */
    ureg32 DMAEN12:1;      /* [12:12]DMA enable 12, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 DMAEN13:1;      /* [13:13]DMA enable 13, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 DMAEN14:1;      /* [14:14]DMA enable 14, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 DMAEN15:1;      /* [15:15]DMA enable 15, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 reserved_16:16; /* [31:16] Reserved */
} SARADC_DMAEN_Bits;

/** \brief Analog configuration register */
typedef volatile struct
{
    ureg32 COMPCRT:1;     /* [0:0]Trim factor of comparator*/
    ureg32 reserved_1:31; /* [31:1] Reserved */
} SARADC_ANCONFIG_Bits;

/** \brief Queue fifo status register */
typedef volatile struct
{
    ureg32 COUNT:5;       /* [4:0]FIFO counter */
    ureg32 EMPTY:1;       /* [5:5]FIFO empty flag  */
    ureg32 FULL:1;        /* [6:6]FIFO full flag  */
    ureg32 reserved_7:25; /* [31:7] Reserved */
} SARADC_QFIFO_Bits;

/** \brief SARADC safety fault input register */
typedef volatile struct
{
    ureg32 DRFI:2;         /* [1:0]DFF redundancy fault input  */
    ureg32 TRIDFI:2;       /* [3:2]Trigger signal monitor detection fault input  */
    ureg32 FTFI:2;         /* [5:4]Feedback timeout fault input  */
    ureg32 GATEDFI:2;      /* [7:6]Gate signal monitor detection fault input  */
    ureg32 SYNCDFI:2;      /* [9:8]SYNC signal monitor detection fault input  */
    ureg32 DAISYDFI:2;     /* [11:10]DAISY signal monitor detection fault input  */
    ureg32 reserved_12:20; /* [31:12] Reserved */
} SARADC_FAULTIN_Bits;

/** \brief SARADC safety enable register */
typedef volatile struct
{
    ureg32 DRSE:2;         /* [1:0]DFF redundancy safety enable  */
    ureg32 TRIDSE:2;       /* [3:2]Trigger signal monitor detection safety enable */
    ureg32 DTSE:2;         /* [5:4]DMA timeout safety enable */
    ureg32 BDSE:2;         /* [7:6]Boundary detection safety enable  */
    ureg32 GATEDSE:2;      /* [9:8]Gate signal monitor detection safety enable */
    ureg32 SYNCDSE:2;      /* [11:10]SYNC signal monitor detection safety enable  */
    ureg32 DAISYDSE:2;     /* [13:12]DAISY signal monitor detection safety enable  */
    ureg32 DMALSE:2;       /* [15:14]DMA request lose enable; This bit reserved in THA6206, Active in THA6412 and THA6104 */
    ureg32 reserved_16:14; /* [29:16] Reserved */
#if defined (THA6_THA6412) || defined (THA6_THA6104)
    ureg32 BEMASK:2;       /* [31:30] Bus error mask control; This bit reserved in THA6206, Active in THA6412 and THA6104*/
#endif    
#if defined (THA6_THA6206) || defined(THA6_THA6206D)
    ureg32 reserved_30:2;  /* [31:30] Internal reserved */
#endif
} SARADC_SAFEEN_Bits;

/** \brief SARADC safety alarm register */
typedef volatile struct
{
    ureg32 BOUNDALM:1;      /* [0:0]Boundary detection alarm  */
    ureg32 DMATOALM:1;      /* [1:1]DMA timeout alarm  */
    ureg32 EALM:1;          /* [2:2]E alarm  */
    ureg32 SEALM:1;         /* [3:3]SE alarm  */
    ureg32 TRITOALM:1;      /* [4:4]Trigger timeout alarm  */
    ureg32 GATOALM:1;       /* [5:5]Gate timeout alarm  */
    ureg32 SYNTOALM:1;      /* [6:6]Synchronization signal timeout alarm */
    ureg32 DAITOALM:1;      /* [7:7]Daisy chain signal timeout alarm  */
    ureg32 ANACFGALM:1;     /* [8:8]ANACFG redundancy alarm  */
    ureg32 ARBCTRLALM:1;    /* [9:9]ARBCTRL redundancy alarm  */
    ureg32 QINCFGALM:1;     /* [10:10]QINCFGn(n=0-2) redundancy alarm  */
    ureg32 CHCTRLALM:1;     /* [11:11]CHCTRLn(n=0-11) redundancy alarm */
    ureg32 RESCTRLALM:1;    /* [12:12]RESCTRLn(n=0-15) redundancy alarm  */
    ureg32 RESULTALM:1;     /* [13:13]RESULTn(n=0-15) redundancy alarm  */
    ureg32 ANCONFIGALM:1;   /* [14:14]ANCONFIG redundancy alarm  */
    ureg32 FAULTINALM:1;    /* [15:15]FAULTIN redundancy alarm  */
    ureg32 SAFEENALM:1;     /* [16:16]SAFEEN redundancy alarm  */
    ureg32 ALARMCLRALM:1;   /* [17:17]ALARMCLR redundancy alarm */
    ureg32 GLORESULTALM:1;  /* [18:18]GLORESULT redundancy alarm  */
    ureg32 GLORESCTRLALM:1; /* [19:19]GLORESCTRL redundancy alarm  */
    ureg32 DMAALOSEALM:1;   /* [20:20]DMA request lose alarm; This bit reserved in THA6206, Active in THA6412 and THA6104 */
    ureg32 CINTMSKALM:1;    /* [21:21]Channel interrupt mask redundancy alarm, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 RINTMSKALM:1;    /* [22:22]Result interrupt mask redundancy alarm, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 SINTMSKALM:1;    /* [23:23]Source interrupt mask redundancy alarm, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 GINTMSKALM:1;    /* [24:24]Globle interrupt mask redundancy alarm, This bit reserved in THA6206 and THA6412, Active in and THA6104 */
    ureg32 reserved_25:7;   /* [31:25] Reserved */
} SARADC_SAFEALM_Bits;

/** \brief SARADC safety alarm clear register */
typedef volatile struct
{
    ureg32 DRALMC:2;       /* [1:0]DFF redundancy alarm clear  */
    ureg32 SMDALMC:2;      /* [3:2]Signal monitor detection alarm clear  */
    ureg32 BOUNDALMC:2;    /* [5:4]Boundary detection alarm clear */
    ureg32 DMATOALMC:2;    /* [7:6]DMA timeout alarm clear  */
    ureg32 ESEALMC:2;      /* [9:8]E/SE alarm clear  */
    ureg32 reserved_10:22; /* [31:10] Reserved */ 
} SARADC_SAFEALMCLR_Bits;

/** \brief Safety boundary control register */
typedef volatile struct
{
    ureg32 SAFEBOUNDL:12; /* [11:0]Software set lower boundary*/
    ureg32 reserved_12:4; /* [15:12] Reserved */
    ureg32 SAFEBOUNDU:12; /* [27:16]Software set upper boundary*/
    ureg32 reserved_28:2; /* [29:28] Reserved */
    ureg32 SAFEBOUNDDR:1; /* [30:30]Discard result out of boundary */
    ureg32 reserved_31:1; /* [31:31] Reserved */
} SARADC_SAFEBOUND_Bits;

/** \brief Trigger/gate monitor threshold register */
typedef volatile struct
{
    ureg32 TRIGATTHRES:32; /* [31:0] Trigger/gate monitor threshold  */
} SARADC_TRIGATTHRES_Bits;

/** \brief Synchronization signal monitor threshold register */
typedef volatile struct
{
    ureg32 SYNCTHRES:32; /* [31:0] Synchronization signal monitor threshold  */
} SARADC_SYNCTHRES_Bits;

/** \brief Daisy chain signal monitor threshold register */
typedef volatile struct
{
    ureg32 DAISYTHRES:32; /* [31:0] Daisy chain signal monitor threshold */
} SARADC_DAISYTHRES_Bits;

/** \brief DMA handshake threshold register */
typedef volatile struct
{
    ureg32 DMATHRES:32; /* [31:0] DMA handshake threshold  */
} SARADC_DMATHRES_Bits;

/** \brief Global result interrupt register */
typedef volatile struct
{
    ureg32 GINT:1;         /* [0:0]Global result interrupt flag  */
    ureg32 reserved_1:7;   /* [7:1] Reserved */
    ureg32 GCLR:1;         /* [8:8]Global result interrupt clear  */
    ureg32 reserved_9:7;   /* [15:9] Reserved */
    ureg32 GRINTNP:4;      /* [19:16]Global result interrupt node pointer  */
    ureg32 reserved_20:10; /* [29:20] Reserved */
    ureg32 GMASK:2;        /* [31:30]Global result interrupt mask  */
} SARADC_GLOINTCTRL_Bits;

/** \brief Global result register */
typedef volatile struct
{
    ureg32 GCONRESULT:16; /* [15:0]Result of most recent conversion  */
    ureg32 GNUM:4;        /* [19:16]Group number */
    ureg32 GCHNUM:5;      /* [24:20]Channel number */
    ureg32 reserved_25:3; /* [27:25] Reserved */
    ureg32 GCONREQS:2;    /* [29:28]Converted request source */
    ureg32 reserved_30:1; /* [30:30] Reserved */
    ureg32 GVFLAG:1;      /* [31:31]Valid flag  */
} SARADC_GLORESULT_Bits;

/** \brief Global result debug register */
typedef volatile struct
{
    ureg32 GCONRESULT:16; /* [15:0]Result of most recent conversion  */
    ureg32 GNUM:4;        /* [19:16]Group number */
    ureg32 GCHNUM:5;      /* [24:20]Channel number */
    ureg32 reserved_25:3; /* [27:25] Reserved */
    ureg32 GCONREQS:2;    /* [29:28]Converted request source */
    ureg32 reserved_30:1; /* [30:30] Reserved */
    ureg32 GVFLAG:1;      /* [31:31]Valid flag  */
} SARADC_GLORESULTD_Bits;

/** \brief Global result control register */
typedef volatile struct
{
    ureg32 GRESALI:1;     /* [0:0] Result alignment */
    ureg32 reserved_1:3;  /* [3:1] Reserved */
    ureg32 GWFRMODE:1;    /* [4:4] Wait-for-read mode  */
    ureg32 reserved_5:3;  /* [7:5] Reserved */
    ureg32 GNRINTEN:1;    /* [8:8] New result interrupt enable */
    ureg32 reserved_9:23; /* [31:9] Reserved */
} SARADC_GLORESCTRL_Bits;

/** \brief Global DMA enable control register */
typedef volatile struct
{
    ureg32 GDMAEN:1;      /* [0:0] Global DMA enable control */
    ureg32 reserved_1:31; /* [31:1] Reserved */
} SARADC_GLODMA_Bits;

/** \brief Global functional bound control register */
typedef volatile struct
{
    ureg32 GBOUNDL:12;    /* [11:0]Software set lower boundary */
    ureg32 reserved_12:4; /* [15:12] Reserved */
    ureg32 GBOUNDU:12;    /* [27:16]Software set upper boundary */
    ureg32 reserved_28:4; /* [31:28] Reserved */
} SARADC_GLOFUNBOUND_Bits;



/**********************************************************************************************************************
 *                                              SARADC Register Definitions
 *********************************************************************************************************************/

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SARADC_Q2TRICTRL_Bits B; /* Bit-Field access */
} SARADC_Q2TRICTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SARADC_ANACFG_Bits B; /* Bit-Field access */
} SARADC_ANACFG;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_ARBCTRL_Bits B; /* Bit-Field access */
} SARADC_ARBCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_SAMCTRL_Bits B; /* Bit-Field access */
} SARADC_SAMCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SARADC_FUNBOUND_Bits B; /* Bit-Field access */
} SARADC_FUNBOUND;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SARADC_SYNCCTRL_Bits B; /* Bit-Field access */
} SARADC_SYNCCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SARADC_QTRICTRL_Bits B; /* Bit-Field access */
} SARADC_QTRICTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    SARADC_QMODE_Bits B; /* Bit-Field access */
} SARADC_QMODE;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SARADC_QINCFG_Bits B; /* Bit-Field access */
} SARADC_QINCFG;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SARADC_QREQTM_Bits B; /* Bit-Field access */
} SARADC_QREQTM;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SARADC_CHCTRL_Bits B; /* Bit-Field access */
} SARADC_CHCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_RESCTRL_Bits B; /* Bit-Field access */
} SARADC_RESCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SARADC_RESULT_Bits B; /* Bit-Field access */
} SARADC_RESULT;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_RESULTD_Bits B; /* Bit-Field access */
} SARADC_RESULTD;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SARADC_CINTCTRL_Bits B; /* Bit-Field access */
} SARADC_CINTCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SARADC_RINTCTRL_Bits B; /* Bit-Field access */
} SARADC_RINTCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SARADC_SINTCTRL_Bits B; /* Bit-Field access */
} SARADC_SINTCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_CINTCLR_Bits B; /* Bit-Field access */
} SARADC_CINTCLR;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_RINTCLR_Bits B; /* Bit-Field access */
} SARADC_RINTCLR;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_SINTCLR_Bits B; /* Bit-Field access */
} SARADC_SINTCLR;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_CINTNP0_Bits B; /* Bit-Field access */
} SARADC_CINTNP0;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_CINTNP1_Bits B; /* Bit-Field access */
} SARADC_CINTNP1;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_RINTNP0_Bits B; /* Bit-Field access */
} SARADC_RINTNP0;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_RINTNP1_Bits B; /* Bit-Field access */
} SARADC_RINTNP1;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SARADC_SINTNP_Bits B; /* Bit-Field access */
} SARADC_SINTNP;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_STRIINT_Bits B; /* Bit-Field access */
} SARADC_STRIINT;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_ALIASCH_Bits B; /* Bit-Field access */
} SARADC_ALIASCH;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    SARADC_DMAEN_Bits B; /* Bit-Field access */
} SARADC_DMAEN;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SARADC_ANCONFIG_Bits B; /* Bit-Field access */
} SARADC_ANCONFIG;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    SARADC_QFIFO_Bits B; /* Bit-Field access */
} SARADC_QFIFO;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;              /* Unsigned access */
    SARADC_FAULTIN_Bits B; /* Bit-Field access */
} SARADC_FAULTIN;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SARADC_SAFEEN_Bits B; /* Bit-Field access */
} SARADC_SAFEEN;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;            /* Unsigned access */
    SARADC_SAFEALM_Bits B; /* Bit-Field access */
} SARADC_SAFEALM;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SARADC_SAFEALMCLR_Bits B; /* Bit-Field access */
} SARADC_SAFEALMCLR;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SARADC_SAFEBOUND_Bits B; /* Bit-Field access */
} SARADC_SAFEBOUND;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    SARADC_TRIGATTHRES_Bits B; /* Bit-Field access */
} SARADC_TRIGATTHRES;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SARADC_SYNCTHRES_Bits B; /* Bit-Field access */
} SARADC_SYNCTHRES;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SARADC_DAISYTHRES_Bits B; /* Bit-Field access */
} SARADC_DAISYTHRES;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;               /* Unsigned access */
    SARADC_DMATHRES_Bits B; /* Bit-Field access */
} SARADC_DMATHRES;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SARADC_GLOINTCTRL_Bits B; /* Bit-Field access */
} SARADC_GLOINTCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                /* Unsigned access */
    SARADC_GLORESULT_Bits B; /* Bit-Field access */
} SARADC_GLORESULT;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SARADC_GLORESULTD_Bits B; /* Bit-Field access */
} SARADC_GLORESULTD;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                 /* Unsigned access */
    SARADC_GLORESCTRL_Bits B; /* Bit-Field access */
} SARADC_GLORESCTRL;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;             /* Unsigned access */
    SARADC_GLODMA_Bits B; /* Bit-Field access */
} SARADC_GLODMA;

typedef union
/* #Violation: saradc_register_h_REF_1 */
{
    uint32 U;                  /* Unsigned access */
    SARADC_GLOFUNBOUND_Bits B; /* Bit-Field access */
} SARADC_GLOFUNBOUND;

/*ALMCLR Register*/

/**********************************************************************************************************************
 *                                        SARADC Register Configuration Structure
 *********************************************************************************************************************/
typedef volatile struct
{
    SARADC_Q2TRICTRL Q2TRICTRL;       /* Queue 2 trigger control register */
    SARADC_ANACFG ANACFG;             /* Analog configration register */
    SARADC_ARBCTRL ARBCTRL;           /* Arbiter control register */
    SARADC_SAMCTRL SAMCTRL;           /* Sample time control register */
    SARADC_FUNBOUND FUNBOUND;         /* Functional bound control register */
    SARADC_SYNCCTRL SYNCCTRL;         /* Synchronous converter control register */
    SARADC_QTRICTRL QTRICTRL[3];      /* Queue trigger configuration register */
    SARADC_QMODE QMODE[3];            /* Queue mode control register */
    SARADC_QINCFG QINCFG[3];          /* Queue input configration register */
    SARADC_QREQTM QREQTM[3];          /* Queue  request timer mode register */
    SARADC_CHCTRL CHCTRL[16];         /* Channel control register,CHCTRL[12] ~ [16] reserved in THA6206 and THA6412, actived in THA6104 */
    SARADC_RESCTRL RESCTRL[16];       /* Result control register */
    SARADC_RESULT RESULT[16];         /* Result register */
    SARADC_RESULTD RESULTD[16];       /* Result debug register */
    SARADC_CINTCTRL CINTCTRL;         /* Channel interrupt flag register */
    SARADC_RINTCTRL RINTCTRL;         /* Result interrupt flag register */
    SARADC_SINTCTRL SINTCTRL;         /* Queue interrupt flag register */
    SARADC_CINTCLR CINTCLR;           /* Channel interrupt clear register */
    SARADC_RINTCLR RINTCLR;           /* Result interrupt clear register */
    SARADC_SINTCLR SINTCLR;           /* Queue interrupt clear register */
    SARADC_CINTNP0 CINTNP0;           /* Channel interrupt node pointer 0 register */
    SARADC_CINTNP1 CINTNP1;           /* Channel interrupt node pointer 1 register */
    SARADC_RINTNP0 RINTNP0;           /* Result interrupt node pointer 0 register */
    SARADC_RINTNP1 RINTNP1;           /* Result interrupt node pointer 1 register */
    SARADC_SINTNP SINTNP;             /* Source interrupt node pointer register */
    SARADC_STRIINT STRIINT;           /* Software trigger interrupt register  */
    SARADC_ALIASCH ALIASCH;           /* Alias channel register */
    SARADC_DMAEN DMAEN;               /* DMA enable control register */
    SARADC_ANCONFIG ANCONFIG;         /* Analog configuration register */
    SARADC_QFIFO QFIFO[3];            /* Queue fifo status register */
    ureg32 RESERVED_0190;             /* 0x0190 - Internal reserved  */        
    SARADC_FAULTIN FAULTIN;           /* SARADC safety fault input register */
    SARADC_SAFEEN SAFEEN;             /* SARADC safety enable register */
    SARADC_SAFEALM SAFEALM;           /* SARADC safety alarm register */
    SARADC_SAFEALMCLR SAFEALMCLR;     /* SARADC safety alarm clear register */
    SARADC_SAFEBOUND SAFEBOUND;       /* Safety boundary control register */
    SARADC_TRIGATTHRES TRIGATTHRES;   /* Trigger/gate monitor threshold register */
    SARADC_SYNCTHRES SYNCTHRES;       /* Synchronization signal monitor threshold register */
    SARADC_DAISYTHRES DAISYTHRES;     /* Daisy chain signal monitor threshold register */
    SARADC_DMATHRES DMATHRES;         /* DMA handshake threshold register */
    ureg32 RESERVED_01B8[18];         /* 0x01B8 - Internal reserved  */ 
    SARADC_GLOINTCTRL GLOINTCTRL;     /* Global result interruption control register */
    SARADC_GLORESULT GLORESULT;       /* Global result register */
    SARADC_GLORESULTD GLORESULTD;     /* Global result debug register */
    SARADC_GLORESCTRL GLORESCTRL;     /* Global result control register */
    SARADC_GLODMA GLODMA;             /* Global DMA enable control register */
    SARADC_GLOFUNBOUND GLOFUNBOUND;   /* Global functional bound control register */
} SARADC_MODULE;

#endif /* SARADC_REGISTER_H_*/
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

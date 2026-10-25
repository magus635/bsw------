/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    msc_std.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of internal functions.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#msc_std_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity 
*
*#msc_std_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity
*/
#ifndef MSC_STD_H_
#define MSC_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "msc_register.h"
#include "Platform_Types.h"
#include "compilertypes.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* MSC upstream register type */
typedef enum
{
    MSC_UD0 = 0U, /* Upstream ID is 0 */
    MSC_UD1,      /* Upstream ID is 1 */
    MSC_UD2,      /* Upstream ID is 2 */
    MSC_UD3       /* Upstream ID is 3 */
} Msc_UpstreamRegType;

/* Enable SRL/SRH active phase selection bit */
typedef enum
{
    MSC_SELBIT_NONE = 0U, /* No selection bit inserted */
    MSC_SELBIT_LOWLEVEL   /* Low level selection bit inserted */
} Msc_SelBit;

/* Output control -  EN/FCL/SDI/SO Signal line polarity */
typedef enum
{
    MSC_SIGNALPOLARITY_NONINVERTED = 0U, /* MSC signal and signal line polarity is identical */
    MSC_SIGNALPOLARITY_INVERTED          /* MSC signal and signal line polarity is inverted */
} Msc_SignalPolarity;

/* Downstream control enhanced - Command-Data-Command in data repetition mode */
typedef enum
{
    MSC_CDCMODE_DISABLED = 0U, /* Disables the automatic insertion of data */
    MSC_CDCMODE_ENABLED        /* Enables the automatic insertion of data */
} Msc_CdcMode;

/* Divider mode */
typedef enum
{
    MSC_DIVMODE_NORMAL = 1U, /* Specifies the divider mode is normal */
    MSC_DIVMODE_FRACTIONAL   /* Specifies the divider mode is fractional */
} Msc_DivMode;

/* Upstream channel frame type */
typedef enum
{
    MSC_FRAMETYPE_12BIT = 0U, /* Specifies the 12-bit upstream frame selected */
    MSC_FRAMETYPE_16BIT       /* Specifies the 16-bit upstream frame selected */
} Msc_FrameType;

/* Upstream parity check mode */
typedef enum
{
    MSC_PARITY_EVEN = 0U, /* Specifies the even parity */
    MSC_PARITY_ODD        /* Specifies the odd parity */
} Msc_Parity;

/* Service request delay control */
typedef enum
{
    MSC_REQDELAY_NODELAY = 0U, /* Specifies the no delay */
    MSC_REQDELAY_1BIT          /* Specifies the delay of 1 bit time */
} Msc_ReqDelay;

/* Interrupt control - Enable DMA handling interrupt  */
typedef enum
{
    MSC_DMA_DISABLED = 0U, /* DMA handing interrupt disabled */
    MSC_DMA_ENABLED        /* DMA handling interrupt enabled */
} Msc_Dma;

/* Dma handling - Enable register mirror  */
typedef enum
{
    MSC_MIRROR_DISABLED = 0U, /* Register mirror disabled */
    MSC_MIRROR_ENABLED        /* Register mirror enabled */
} Msc_Mirror;

/* Output control - Clock control */
typedef enum
{
    MSC_FCLVALID_ACTIVE_PHASE_ONLY = 0U, /* FCL is active during active phases of data or command frames */
    MSC_FCLVALID_ALWAYS                  /* FCL is always active */
} Msc_FclValid;

/* Downstream channel transmission mode */
typedef enum
{
    MSC_TRANSMODE_TRIGGERED = 0U, /* Triggered mode */
    MSC_TRANSMODE_DATAREPETITION  /* Data repetition mode */
} Msc_TransMode;

/* MSC interrupt enable control */
typedef enum
{
    MSC_INTREN_DISABLED = 0U, /* Disables the interrupt generation */
    MSC_INTREN_ENABLED        /* Enables the interrupt generation */
} Msc_IntrEn;

/* Downstream control enhanced - Injection enable of the pin 0 and 1 Signal */
typedef enum
{
    MSC_INJEN_DISABLED = 0U, /* Disables the external signal injection in a data frame */
    MSC_INJEN_ENABLED        /* Enables the external signal injection in a data frame */
} Msc_InjEn;

/* Enable/disable downstream channel */
typedef enum
{
    MSC_DOWNSTREAMEN_DISABLED = 0U, /* To disable downstream channel */
    MSC_DOWNSTREAMEN_ENABLED        /* To enable downstream channel */
} Msc_DownstreamEn;

/* Interrupt control - Data frame interrupt enable */
typedef enum
{
    MSC_DFINTERRUPT_LASTBIT = 0U, /* An interrupt is generated when the last data bit has been shifted out */
    MSC_DFINTERRUPT_FIRSTBIT      /* An interrupt is generated when the First data bit has been shifted out */
} Msc_DfiType;

/* Interrupt control - Receive data interrupt enable */
typedef enum
{
    MSC_RDITYPE_RECEIVE = 1U, /* An interrupt is generated when data is received and written into the upstream data registers */
    MSC_RDITYPE_RDIESET,      /* An interrupt is generated as with RDIE = 01B but only if the received data is not equal to 00H */
    MSC_RDITYPE_RECEIVEINUD3  /* An interrupt is generated when data is received and written into the UDR3 registers */
} Msc_RdiType;

/* MSC reception error status */
typedef enum
{
    MSC_RXSTATUS_PE = 0U,   /* Parity check error */
    MSC_RXSTATUS_RECEIVED,  /* Specifies right data received */
    MSC_RXSTATUS_NORESPONSE /* Specifies no data received */
} Msc_RxStatus;

/* Interrupt Control - CF/DF/RD/TF Interrupt node pointer */
typedef enum
{
    MSC_INTRNODE_SR0 = 0U, /* Service request output SR0 selected */
    MSC_INTRNODE_SR1,      /* Service request output SR1 selected */
    MSC_INTRNODE_SR2,      /* Service request output SR2 selected */
    MSC_INTRNODE_SR3       /* Service request output SR3 selected */
} Msc_IntrNode;

/* MSC targets used as chip enable selection for ENH, ENL and ENC */
typedef enum
{
    MSC_TARGET_EN0 = 0U, /* Target EN0 */
    MSC_TARGET_EN1,      /* Target EN1 */
    MSC_TARGET_EN2,      /* Target EN2 */
    MSC_TARGET_EN3       /* Target EN3 */
} Msc_Target;

/* Interrupt control - OVF/UNF/UT With alternative interrupt node pointer */
typedef enum
{
    MSC_ALINTRNODE_SR0 = 0U, /* Service request output SR0 selected */
    MSC_ALINTRNODE_SR1,      /* Service request output SR1 selected */
    MSC_ALINTRNODE_SR2,      /* Service request output SR2 selected */
    MSC_ALINTRNODE_SR3,      /* Service request output SR3 selected */
    MSC_ALINTRNODE_SR4       /* Service request output SR4 selected */
} Msc_AlIntrNode;

/* Serial data input selection */
typedef enum
{
    MSC_SDI_0 = 0U, /* SDI0 is selected for the SDI of the upstream channel */
    MSC_SDI_1,      /* SDI1 is selected for the SDI of the upstream channel */
    MSC_SDI_2,      /* SDI2 is selected for the SDI of the upstream channel */
    MSC_SDI_3       /* SDI3 is selected for the SDI of the upstream channel */
} Msc_Sdi;

/* Upstream channel receiving rate */
typedef enum
{
    MSC_UPDIV_DISABLED = 0U, /* Specifies the disabled */
    MSC_UPDIV_4,             /* Specifies the baud rate = fMSC / 4 */
    MSC_UPDIV_8,             /* Specifies the baud rate = fMSC / 8 */
    MSC_UPDIV_16,            /* Specifies the baud rate = fMSC / 16 */
    MSC_UPDIV_32,            /* Specifies the baud rate = fMSC / 32 */
    MSC_UPDIV_64,            /* Specifies the baud rate = fMSC / 64 */
    MSC_UPDIV_128,           /* Specifies the baud rate = fMSC / 128 */
    MSC_UPDIV_256            /* Specifies the baud rate = fMSC / 256 */
} Msc_UpDiv;

/* Upstream control enhanced - Upstream timeout prescaler. */
typedef enum
{
    MSC_TIMEOUTPRESCALER_1 = 0U, /* Prescale value 1 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_2,      /* Prescale value 2 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_4,      /* Prescale value 4 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_8,      /* Prescale value 8 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_16,     /* Prescale value 16 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_32,     /* Prescale value 32 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_64,     /* Prescale value 64 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_128,    /* Prescale value 128 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_256,    /* Prescale value 256 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_512,    /* Prescale value 512 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_1024,   /* Prescale value 1024 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_2048,   /* Prescale value 2048 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_4096,   /* Prescale value 4096 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_8192,   /* Prescale value 8192 for the upstream time-out limit */
    MSC_TIMEOUTPRESCALER_16384   /* Prescale value 16384 for the upstream time-out limit */
} Msc_TimeoutPrescaler;

/* Upstream control enhanced - Upstream timeout value. */
typedef enum
{
    MSC_TIMEOUTVALUE_1 = 0U, /* Upstream timeout value 1 */
    MSC_TIMEOUTVALUE_2,      /* Upstream timeout value 2 */
    MSC_TIMEOUTVALUE_3,      /* Upstream timeout value 3 */
    MSC_TIMEOUTVALUE_4,      /* Upstream timeout value 4 */
    MSC_TIMEOUTVALUE_5,      /* Upstream timeout value 5 */
    MSC_TIMEOUTVALUE_6,      /* Upstream timeout value 6 */
    MSC_TIMEOUTVALUE_7,      /* Upstream timeout value 7 */
    MSC_TIMEOUTVALUE_8,      /* Upstream timeout value 8 */
    MSC_TIMEOUTVALUE_9,      /* Upstream timeout value 9 */
    MSC_TIMEOUTVALUE_10,     /* Upstream timeout value 10 */
    MSC_TIMEOUTVALUE_11,     /* Upstream timeout value 11 */
    MSC_TIMEOUTVALUE_12,     /* Upstream timeout value 12 */
    MSC_TIMEOUTVALUE_13,     /* Upstream timeout value 13 */
    MSC_TIMEOUTVALUE_14,     /* Upstream timeout value 14 */
    MSC_TIMEOUTVALUE_15,     /* Upstream timeout value 15 */
    MSC_TIMEOUTVALUE_16      /* Upstream timeout value 16 */
} Msc_TimeoutValue;

/* Number of SRx[] (x->SRL/SRH) bits shifted at data frames */
typedef enum
{
    MSC_DFLENGTH_0 = 0U, /* No SRx bit shifted */
    MSC_DFLENGTH_1,      /* SRx[0] shifted */
    MSC_DFLENGTH_2,      /* SRx[1:0] shifted */
    MSC_DFLENGTH_3,      /* SRx[2:0] shifted */
    MSC_DFLENGTH_4,      /* SRx[3:0] shifted */
    MSC_DFLENGTH_5,      /* SRx[4:0] shifted */
    MSC_DFLENGTH_6,      /* SRx[5:0] shifted */
    MSC_DFLENGTH_7,      /* SRx[6:0] shifted */
    MSC_DFLENGTH_8,      /* SRx[7:0] shifted */
    MSC_DFLENGTH_9,      /* SRx[8:0] shifted */
    MSC_DFLENGTH_10,     /* SRx[9:0] shifted */
    MSC_DFLENGTH_11,     /* SRx[10:0] shifted */
    MSC_DFLENGTH_12,     /* SRx[11:0] shifted */
    MSC_DFLENGTH_13,     /* SRx[12:0] shifted */
    MSC_DFLENGTH_14,     /* SRx[13:0] shifted */
    MSC_DFLENGTH_15,     /* SRx[14:0] shifted */
    MSC_DFLENGTH_16      /* SRx[15:0] shifted */
} Msc_DfLength;

/* Number of bits shifted at command frames */
typedef enum
{
    MSC_CFLENGTH_0 = 0U, /* No bit shifted */
    MSC_CFLENGTH_1,      /* SRL[0] shifted */
    MSC_CFLENGTH_2,      /* SRL[1:0] shifted */
    MSC_CFLENGTH_3,      /* SRL[2:0] shifted */
    MSC_CFLENGTH_4,      /* SRL[3:0] shifted */
    MSC_CFLENGTH_5,      /* SRL[4:0] shifted */
    MSC_CFLENGTH_6,      /* SRL[5:0] shifted */
    MSC_CFLENGTH_7,      /* SRL[6:0] shifted */
    MSC_CFLENGTH_8,      /* SRL[7:0] shifted */
    MSC_CFLENGTH_9,      /* SRL[8:0] shifted */
    MSC_CFLENGTH_10,     /* SRL[9:0] shifted */
    MSC_CFLENGTH_11,     /* SRL[10:0] shifted */
    MSC_CFLENGTH_12,     /* SRL[11:0] shifted */
    MSC_CFLENGTH_13,     /* SRL[12:0] shifted */
    MSC_CFLENGTH_14,     /* SRL[13:0] shifted */
    MSC_CFLENGTH_15,     /* SRL[14:0] shifted */
    MSC_CFLENGTH_16,     /* SRL[15:0] shifted */
    MSC_CFLENGTH_17,     /* SRL[15:0] and SRH[0] shifted */
    MSC_CFLENGTH_18,     /* SRL[15:0] and SRH[1:0] shifted */
    MSC_CFLENGTH_19,     /* SRL[15:0] and SRH[2:0] shifted */
    MSC_CFLENGTH_20,     /* SRL[15:0] and SRH[3:0] shifted */
    MSC_CFLENGTH_21,     /* SRL[15:0] and SRH[4:0] shifted */
    MSC_CFLENGTH_22,     /* SRL[15:0] and SRH[5:0] shifted */
    MSC_CFLENGTH_23,     /* SRL[15:0] and SRH[6:0] shifted */
    MSC_CFLENGTH_24,     /* SRL[15:0] and SRH[7:0] shifted */
    MSC_CFLENGTH_25,     /* SRL[15:0] and SRH[8:0] shifted */
    MSC_CFLENGTH_26,     /* SRL[15:0] and SRH[9:0] shifted */
    MSC_CFLENGTH_27,     /* SRL[15:0] and SRH[10:0] shifted */
    MSC_CFLENGTH_28,     /* SRL[15:0] and SRH[11:0] shifted */
    MSC_CFLENGTH_29,     /* SRL[15:0] and SRH[12:0] shifted */
    MSC_CFLENGTH_30,     /* SRL[15:0] and SRH[13:0] shifted */
    MSC_CFLENGTH_31,     /* SRL[15:0] and SRH[14:0] shifted */
    MSC_CFLENGTH_32      /* SRL[15:0] and SRH[15:0] shifted */
} Msc_CfLength;

/* Passive phase length at data frames */
typedef enum
{
#if defined(THA6_THA6206D)
    MSC_DFPPL_2 = 0U, /* Passive phase length is 2 tFCL */
    MSC_DFPPL_3,      /* Passive phase length is 3 tFCL */
#endif
    MSC_DFPPL_4 = 2U, /* Passive phase length is 4 tFCL */
    MSC_DFPPL_5,      /* Passive phase length is 5 tFCL */
    MSC_DFPPL_6,      /* Passive phase length is 6 tFCL */
    MSC_DFPPL_7,      /* Passive phase length is 7 tFCL */
    MSC_DFPPL_8,      /* Passive phase length is 8 tFCL */
    MSC_DFPPL_9,      /* Passive phase length is 9 tFCL */
    MSC_DFPPL_10,     /* Passive phase length is 10 tFCL */
    MSC_DFPPL_11,     /* Passive phase length is 11 tFCL */
    MSC_DFPPL_12,     /* Passive phase length is 12 tFCL */
    MSC_DFPPL_13,     /* Passive phase length is 13 tFCL */
    MSC_DFPPL_14,     /* Passive phase length is 14 tFCL */
    MSC_DFPPL_15,     /* Passive phase length is 15 tFCL */
    MSC_DFPPL_16,     /* Passive phase length is 16 tFCL */
    MSC_DFPPL_17,     /* Passive phase length is 17 tFCL */
    MSC_DFPPL_18,     /* Passive phase length is 18 tFCL */
    MSC_DFPPL_19,     /* Passive phase length is 19 tFCL */
    MSC_DFPPL_20,     /* Passive phase length is 20 tFCL */
    MSC_DFPPL_21,     /* Passive phase length is 21 tFCL */
    MSC_DFPPL_22,     /* Passive phase length is 22 tFCL */
    MSC_DFPPL_23,     /* Passive phase length is 23 tFCL */
    MSC_DFPPL_24,     /* Passive phase length is 24 tFCL */
    MSC_DFPPL_25,     /* Passive phase length is 25 tFCL */
    MSC_DFPPL_26,     /* Passive phase length is 26 tFCL */
    MSC_DFPPL_27,     /* Passive phase length is 27 tFCL */
    MSC_DFPPL_28,     /* Passive phase length is 28 tFCL */
    MSC_DFPPL_29,     /* Passive phase length is 29 tFCL */
    MSC_DFPPL_30,     /* Passive phase length is 30 tFCL */
    MSC_DFPPL_31,     /* Passive phase length is 31 tFCL */
    MSC_DFPPL_32,     /* Passive phase length is 32 tFCL */
    MSC_DFPPL_33      /* Passive phase length is 33 tFCL */
} Msc_DfPpl;

/* Downstream status - Number of passive time frames */
typedef enum
{
    MSC_PTFCOUNT_0 = 0U, /* No passive time frames inserted */
    MSC_PTFCOUNT_1,      /* 1 passive time frames inserted */
    MSC_PTFCOUNT_2,      /* 2 passive time frames inserted */
    MSC_PTFCOUNT_3,      /* 3 passive time frames inserted */
    MSC_PTFCOUNT_4,      /* 4 passive time frames inserted */
    MSC_PTFCOUNT_5,      /* 5 passive time frames inserted */
    MSC_PTFCOUNT_6,      /* 6 passive time frames inserted */
    MSC_PTFCOUNT_7,      /* 7 passive time frames inserted */
    MSC_PTFCOUNT_8,      /* 8 passive time frames inserted */
    MSC_PTFCOUNT_9,      /* 9 passive time frames inserted */
    MSC_PTFCOUNT_10,     /* 10 passive time frames inserted */
    MSC_PTFCOUNT_11,     /* 11 passive time frames inserted */
    MSC_PTFCOUNT_12,     /* 12 passive time frames inserted */
    MSC_PTFCOUNT_13,     /* 13 passive time frames inserted */
    MSC_PTFCOUNT_14,     /* 14 passive time frames inserted */
    MSC_PTFCOUNT_15      /* 15 passive time frames inserted */
} Msc_PtfCount;

/* Downstream control enhanced - Injection position of the pin 0 and 1 signal */
typedef enum
{
    MSC_INJPOS_0 = 0U, /* Injected external bit is at position 0 of the data frame */
    MSC_INJPOS_1,      /* Injected external bit is at position 1 of the data frame */
    MSC_INJPOS_2,      /* Injected external bit is at position 2 of the data frame */
    MSC_INJPOS_3,      /* Injected external bit is at position 3 of the data frame */
    MSC_INJPOS_4,      /* Injected external bit is at position 4 of the data frame */
    MSC_INJPOS_5,      /* Injected external bit is at position 5 of the data frame */
    MSC_INJPOS_6,      /* Injected external bit is at position 6 of the data frame */
    MSC_INJPOS_7,      /* Injected external bit is at position 7 of the data frame */
    MSC_INJPOS_8,      /* Injected external bit is at position 8 of the data frame */
    MSC_INJPOS_9,      /* Injected external bit is at position 9 of the data frame */
    MSC_INJPOS_10,     /* Injected external bit is at position 10 of the data frame */
    MSC_INJPOS_11,     /* Injected external bit is at position 11 of the data frame */
    MSC_INJPOS_12,     /* Injected external bit is at position 12 of the data frame */
    MSC_INJPOS_13,     /* Injected external bit is at position 13 of the data frame */
    MSC_INJPOS_14,     /* Injected external bit is at position 14 of the data frame */
    MSC_INJPOS_15,     /* Injected external bit is at position 15 of the data frame */
    MSC_INJPOS_16,     /* Injected external bit is at position 16 of the data frame */
    MSC_INJPOS_17,     /* Injected external bit is at position 17 of the data frame */
    MSC_INJPOS_18,     /* Injected external bit is at position 18 of the data frame */
    MSC_INJPOS_19,     /* Injected external bit is at position 19 of the data frame */
    MSC_INJPOS_20,     /* Injected external bit is at position 20 of the data frame */
    MSC_INJPOS_21,     /* Injected external bit is at position 21 of the data frame */
    MSC_INJPOS_22,     /* Injected external bit is at position 22 of the data frame */
    MSC_INJPOS_23,     /* Injected external bit is at position 23 of the data frame */
    MSC_INJPOS_24,     /* Injected external bit is at position 24 of the data frame */
    MSC_INJPOS_25,     /* Injected external bit is at position 25 of the data frame */
    MSC_INJPOS_26,     /* Injected external bit is at position 26 of the data frame */
    MSC_INJPOS_27,     /* Injected external bit is at position 27 of the data frame */
    MSC_INJPOS_28,     /* Injected external bit is at position 28 of the data frame */
    MSC_INJPOS_29,     /* Injected external bit is at position 29 of the data frame */
    MSC_INJPOS_30,     /* Injected external bit is at position 30 of the data frame */
    MSC_INJPOS_31      /* Injected external bit is at position 31 of the data frame */
} Msc_InjPos;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Clock configuration structure */
/* #Violation: msc_std_h_REF_2 */
typedef struct
{
    uint32 baud;         /* Specifies the baud rate */
    Msc_DivMode divMode; /* Specifies the divided clock mode */
} Msc_ClockConfig;

/* Interrupt configuration structure */
/* #Violation: msc_std_h_REF_1 */
/* #Violation: msc_std_h_REF_2 */
typedef struct
{
    Msc_RdiType rdiType;  /* Specifies the receive data interrupt type */
    Msc_IntrNode rdiNode; /* Specifies the receive data interrupt node */
    Msc_IntrNode tfiNode; /* Specifies the time frame interrupt node */
    Msc_IntrNode cfiNode; /* Specifies the command frame interrupt node */
    Msc_IntrNode dfiNode; /* Specifies the data frame interrupt node */
    Msc_DfiType dfiType;  /* Specifies the data frame interrupt type */
} Msc_InterruptConfig;

/* Upstream channel configuration structure */
/* #Violation: msc_std_h_REF_2 */
typedef struct
{
    Msc_UpDiv upDiv;           /* Specifies the upstream channel division coefficient */
    Msc_FrameType frameType;   /* Specifies the upstream channel frame type */
    Msc_Parity parity;         /* Specifies the parity mode */
    Msc_ReqDelay reqDelay;     /* Specifies the service request delay */
    Msc_SignalPolarity sdiPol; /* Specifies the SDI polarity */
} Msc_UpstreamConfig;

/* Downstream data source configuration structure */
typedef struct
{
    uint32 lowSrc;         /* Specifies the downstream low data source selection */
    uint32 highSrc;        /* Specifies the downstream high data source selection */
    uint32 emsBits;        /* Specifies the emergency stop enable bits */
    Msc_InjEn pin0InjEn;   /* Specifies the injection enable pin 0 */
    Msc_InjPos pin0InjPos; /* Specifies the injection position pin 0 */
    Msc_InjEn pin1InjEn;   /* Specifies the injection enable pin 1 */
    Msc_InjPos pin1InjPos; /* Specifies the injection position pin 1 */
} Msc_DataSourceConfig;

/* Downstream control configuration structure */
/* #Violation: msc_std_h_REF_2 */
typedef struct
{
    Msc_TransMode transMode;        /* Specifies the transmission mode */
    Msc_CfLength cfLength;          /* Specifies the number of bits shifted at command frames */
    Msc_DfLength srlDfLength;       /* Specifies the number of SRL bits shifted at data frames */
    Msc_DfLength srhDfLength;       /* Specifies the number of SRH bits shifted at data frames */
    Msc_DfPpl dfPpl;                /* Specifies the passive phase length at data frames */
    Msc_SelBit srlSelBit;           /* To enable or disable SRL active phase selection bit */
    Msc_SelBit srhSelBit;           /* To enable or disable SRH active phase selection bit */
    Msc_FclValid fclValid;          /* Specifies the clock active phase */
    Msc_SignalPolarity cslPol;      /* Specifies the CSLP polarity */
    Msc_PtfCount ptfCount;          /* Specifies the number of passive time frames in data repetition mode */
    Msc_CdcMode cdcMode;            /* Specifies the command-data-command in data repetition mode */
    Msc_DataSourceConfig srcConfig; /* Specifies the data source configuration */
    Msc_DownstreamEn downstreamEn;  /* To disable or enable downstream channel */
} Msc_DownstreamConfig;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
#define MSC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Msc_MemMap.h"

/**********************************************************************************************************************
 * Function:     Msc_Std_InitBaudRate
 * Description:  Initialize the MSC baud-rate.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               pConfig: the downstream baud-rate
 *               the frequency of AHB (unit: Hz)
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *  2025/05/13    01358     Add input parameter: ahbClkFreq
 *********************************************************************************************************************/
extern void Msc_Std_InitBaudRate(MSC_MODULE *const pMsc, const Msc_ClockConfig *const pConfig, float32 ahbClkFreq);

/**********************************************************************************************************************
 * Function:     Msc_Std_InitUpstream
 * Description:  Initialize the upstream channel data format
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               pConfig: Specifies the upstream channel frame layout configuration pointer
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Std_InitUpstream(MSC_MODULE *const pMsc, const Msc_UpstreamConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Msc_Std_InitDownstream
 * Description:  Initialize the downstream channel data format
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               pConfig: Specifies the downstream channel configuration pointer
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Std_InitDownstream(MSC_MODULE *const pMsc, const Msc_DownstreamConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Msc_Std_InitInterrupt
 * Description:  Initialize interrupt mode and node selection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               pConfig: Specifies the interrupt configuration pointer
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Std_InitInterrupt(MSC_MODULE *const pMsc, const Msc_InterruptConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Msc_Std_GetRxStatus
 * Description:  Get the status of the upstream reception status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               upstreamIdx: Specifies the index of the upstream data register
 * Inout:        None
 * Output:       None
 * Return:       Msc_RxStatus: Upstream reception status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern Msc_RxStatus Msc_Std_GetRxStatus(const MSC_MODULE *const pMsc, Msc_UpstreamRegType upstreamIdx);

/**********************************************************************************************************************
 * Function:     Msc_Std_ClearUpstreamValidFlag
 * Description:  Clear the valid flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               upstreamIdx: Specifies the index of the upstream data register
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern void Msc_Std_ClearUpstreamValidFlag(MSC_MODULE *const pMsc, Msc_UpstreamRegType upstreamIdx);

/**********************************************************************************************************************
 * Function:     Msc_Std_GetData
 * Description:  Get the upstream data from upstream data register
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pMsc: Pointer to the MSC module
 *               upstreamIdx: Specifies index of the upstream data register
 * Inout:        None
 * Output:       None
 * Return:       uint8: Received data
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01208     Create
 *  2024/08/15    01208     Add input parameter
 *********************************************************************************************************************/
extern uint8 Msc_Std_GetData(const MSC_MODULE *const pMsc, Msc_UpstreamRegType upstreamIdx);

#define MSC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Msc_MemMap.h"

#endif /* MSC_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    eth_hal.h
 * Author:      00930
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
#ifndef ETH_HAL_H_
#define ETH_HAL_H_

/*
*#Violation Summary
*#eth_hal_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for different configurations
*
*#eth_hal_h_REF_2:MISRAC2012-Rule-2.3;
* Justification: The members of the type are used in configuration-generated code.
*
*#eth_hal_h_REF_3:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by code review.
*
*#eth_hal_h_REF_4:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#eth_hal_h_REF_5:CertC-DCL15-C;
* Justification: Reserved API for user access
*
*#eth_hal_h_REF_6:CertC-DCL19-C;
* Justification: Reserved API for user access
*
*#eth_hal_h_REF_7:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity
*
*#eth_hal_h_REF_8:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#eth_hal_h_REF_9:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Eth_GeneralTypes.h"
#include "Platform_Types.h"
#include "eth_register.h"
#include "compilertypes.h"
#include "port_hal.h"
#include "Eth_Cfg.h"
#include "tha6_cfg.h"
#include "eth_std.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* The max packet size is 1518 bytes */
/* #Violation: eth_hal_h_REF_1 */
#define ETH_MAX_PACKETSIZE_1518 (1518U)
/* The max packet size is 1522 bytes */
/* #Violation: eth_hal_h_REF_1 */
#define ETH_MAX_PACKETSIZE_1522 (1522U)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Define the ETH return status */
typedef enum
{
    ETH_STATUS_OK = 0x00U,          /* Generic operation success status */
    ETH_STATUS_ERROR = 0x01U,       /* Generic operation failure status */
    ETH_STATUS_BUSY = 0x02U,        /* Generic operation busy status */
    ETH_STATUS_OVFL = 0x03U         /* Ethernet no buffer of the required length */
} Eth_Status;

/* Overview of mode and line speed support:
 *
                    MII         |        RMII         |        RGMII
   -----------------------------------------------------------------------
    10M    |    THA6206 (Y)     |     THA6206 (Y)     |     THA6206 (N)
           |    THA6206D(Y)     |     THA6206D(Y)     |     THA6206D(Y)
           |    THA6412 (Y)     |     THA6412 (Y)     |     THA6412 (N)
           |    THA6104 (Y)     |     THA6104 (N)     |     THA6104 (N)
   -----------------------------------------------------------------------
    100M   |    THA6206 (Y)     |     THA6206 (Y)     |     THA6206 (N)
           |    THA6206D(Y)     |     THA6206D(Y)     |     THA6206D(Y)
           |    THA6412 (Y)     |     THA6412 (Y)     |     THA6412 (N)
           |    THA6104 (N)     |     THA6104 (N)     |     THA6104 (N)
   -----------------------------------------------------------------------
    1000M  |                    |                     |     THA6206 (Y)
           |          -         |          -          |     THA6206D(Y)
           |                    |                     |     THA6412 (Y)
           |                    |                     |     THA6104 (N)
   -----------------------------------------------------------------------
   Note:   Y: Support N: Not support
*/
/* Define the ETH PHY interface mode */
typedef enum
{
    ETH_PHY_INTERFACE_MII = 0U,   /* MII mode */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    ETH_PHY_INTERFACE_RGMII = 1U, /* RGMII mode, THA6206, THA6206D and THA6412 are supported,
                                     but THA6104 is not supported */
    ETH_PHY_INTERFACE_RMII = 4U   /* RMII mode */
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
} Eth_PhyInterfaceMode;

/* Define the ethernet line speed */
typedef enum
{
    ETH_LINESPEED_10M = 0U, /* 10 Mbps */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    ETH_LINESPEED_100M,     /* 100 Mbps */
    ETH_LINESPEED_1000M     /* 1000 Mbps, THA6206, THA6206D and THA6412 are supported,
                               but THA6104 is not supported */
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
} Eth_LineSpeed;

/* Define the Rx/Tx DMA channel */
typedef enum
{
    ETH_DMA_CHANNEL0 = 0U, /* Rx/Tx Dma Channel 0 */
    ETH_DMA_CHANNEL1,      /* Rx/Tx Dma Channel 1 */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    ETH_DMA_CHANNEL2,      /* Rx/Tx Dma Channel 2, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_DMA_CHANNEL3       /* Rx/Tx Dma Channel 3, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
} Eth_DmaChannel;

/* Define the duplex mode */
typedef enum
{
    ETH_HALFDUPLEX_MODE = 0U, /* Half Duplex Mode */
    ETH_FULLDUPLEX_MODE       /* Full Duplex Mode */
} Eth_DuplexMode;

/* Define the loopback mode */
typedef enum
{
    ETH_LOOPBACK_DISABLE = 0U, /* Disable loopback */
    ETH_LOOPBACK_ENABLE        /* Enable loopback */
} Eth_LoopbackMode;

/* Define transmit scheduling algorithm for Tx Queues */
typedef enum
{
    ETH_TX_SCHEDULING_ALG_WRR = 0U, /* WRR Algorithm */
    ETH_TX_SCHEDULING_ALG_SP = 3U   /* Strict Priority Algorithm */
/* #Violation: eth_hal_h_REF_2 */
} Eth_TxSchedulingAlgorithm;

/* Define receive arbitration algorithm for Rx Queues */
typedef enum
{
    ETH_RX_ARBITRATION_ALG_SP = 0U, /* Strict Priority */
    ETH_RX_ARBITRATION_ALG_WSP      /* Weighted Strict Priority */
/* #Violation: eth_hal_h_REF_2 */
} Eth_RxArbitrationAlgorithm;

/* Define MTL Tx Queue size */
typedef enum
{
    ETH_TXQUEUE_SIZE_256B = 0U, /* Queue size is 256Bytes */
    ETH_TXQUEUE_SIZE_512B,      /* Queue size is 512Bytes */
    ETH_TXQUEUE_SIZE_768B,      /* Queue size is 768Bytes */
    ETH_TXQUEUE_SIZE_1024B,     /* Queue size is 1024Bytes */
    ETH_TXQUEUE_SIZE_1280B,     /* Queue size is 1280Bytes */
    ETH_TXQUEUE_SIZE_1536B,     /* Queue size is 1536Bytes */
    ETH_TXQUEUE_SIZE_1792B,     /* Queue size is 1792Bytes */
    ETH_TXQUEUE_SIZE_2048B,     /* Queue size is 2048Bytes */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    ETH_TXQUEUE_SIZE_2304B,     /* Queue size is 2304Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_TXQUEUE_SIZE_2560B,     /* Queue size is 2560Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_TXQUEUE_SIZE_2816B,     /* Queue size is 2816Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_TXQUEUE_SIZE_3072B,     /* Queue size is 3072Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_TXQUEUE_SIZE_3328B,     /* Queue size is 3328Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_TXQUEUE_SIZE_3584B,     /* Queue size is 3584Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_TXQUEUE_SIZE_3840B,     /* Queue size is 3840Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_TXQUEUE_SIZE_4096B      /* Queue size is 4096Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
} Eth_TxQueueSize;

/* Define MTL Rx Queue size */
typedef enum
{
    ETH_RXQUEUE_SIZE_256B = 0U, /* Queue size is 256Bytes */
    ETH_RXQUEUE_SIZE_512B,      /* Queue size is 512Bytes */
    ETH_RXQUEUE_SIZE_768B,      /* Queue size is 768Bytes */
    ETH_RXQUEUE_SIZE_1024B,     /* Queue size is 1024Bytes */
    ETH_RXQUEUE_SIZE_1280B,     /* Queue size is 1280Bytes */
    ETH_RXQUEUE_SIZE_1536B,     /* Queue size is 1536Bytes */
    ETH_RXQUEUE_SIZE_1792B,     /* Queue size is 1792Bytes */
    ETH_RXQUEUE_SIZE_2048B,     /* Queue size is 2048Bytes */
    ETH_RXQUEUE_SIZE_2304B,     /* Queue size is 2304Bytes */
    ETH_RXQUEUE_SIZE_2560B,     /* Queue size is 2560Bytes */
    ETH_RXQUEUE_SIZE_2816B,     /* Queue size is 2816Bytes */
    ETH_RXQUEUE_SIZE_3072B,     /* Queue size is 3072Bytes */
    ETH_RXQUEUE_SIZE_3328B,     /* Queue size is 3328Bytes */
    ETH_RXQUEUE_SIZE_3584B,     /* Queue size is 3584Bytes */
    ETH_RXQUEUE_SIZE_3840B,     /* Queue size is 3840Bytes */
    ETH_RXQUEUE_SIZE_4096B,     /* Queue size is 4096Bytes */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    ETH_RXQUEUE_SIZE_4352B,     /* Queue size is 4352Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_4608B,     /* Queue size is 4608Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_4864B,     /* Queue size is 4864Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_5120B,     /* Queue size is 5120Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_5376B,     /* Queue size is 5376Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_5632B,     /* Queue size is 5632Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_5888B,     /* Queue size is 5888Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_6144B,     /* Queue size is 6144Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_6400B,     /* Queue size is 6400Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_6656B,     /* Queue size is 6656Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_6912B,     /* Queue size is 6912Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_7168B,     /* Queue size is 7168Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_7424B,     /* Queue size is 7424Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_7680B,     /* Queue size is 7680Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_7936B,     /* Queue size is 7936Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_RXQUEUE_SIZE_8192B      /* Queue size is 8192Bytes, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
} Eth_RxQueueSize;

/* Flow Control thresholds for MTL Receive FIFO\n
 * Definition in GETH_MTL_RXQx_OPERATION_MODE.B.RFD
 * Definition in GETH_MTL_RXQx_OPERATION_MODE.B.RFA
 */
typedef enum
{
    ETH_RXFLOWCONTROL_THRESHOLD_1KB = 0U, /* Full minius  1KB */
    ETH_RXFLOWCONTROL_THRESHOLD_1_5KB,    /* Full minius 1.5KB */
    ETH_RXFLOWCONTROL_THRESHOLD_2KB,      /* Full minius  2KB */
    ETH_RXFLOWCONTROL_THRESHOLD_2_5KB,    /* Full minius 2.5KB */
    ETH_RXFLOWCONTROL_THRESHOLD_3KB,      /* Full minius  3KB */
    ETH_RXFLOWCONTROL_THRESHOLD_3_5KB,    /* Full minius 3.5KB */
    ETH_RXFLOWCONTROL_THRESHOLD_4KB,      /* Full minius  4KB */
    ETH_RXFLOWCONTROL_THRESHOLD_4_5KB,    /* Full minius 4.5KB */
    ETH_RXFLOWCONTROL_THRESHOLD_5KB,      /* Full minius  5KB */
    ETH_RXFLOWCONTROL_THRESHOLD_5_5KB,    /* Full minius 5.5KB */
    ETH_RXFLOWCONTROL_THRESHOLD_6KB,      /* Full minius  6KB */
    ETH_RXFLOWCONTROL_THRESHOLD_6_5KB,    /* Full minius 6.5KB */
    ETH_RXFLOWCONTROL_THRESHOLD_7KB,      /* Full minius  7KB */
    ETH_RXFLOWCONTROL_THRESHOLD_7_5KB,    /* Full minius 7.5KB */
    ETH_RXFLOWCONTROL_THRESHOLD_8KB,      /* Full minius  8KB */
    ETH_RXFLOWCONTROL_THRESHOLD_8_5KB     /* Full minius 8.5KB */
} Eth_RxFlowControlThresholds;

/* Define MTL Tx Queue Threshold */
typedef enum
{
    ETH_TXQUEUE_THRESHOLD_32B = 0U, /* Transmit Queue Threshold 32Bytes */
    ETH_TXQUEUE_THRESHOLD_64B,      /* Transmit Queue Threshold 64Bytes */
    ETH_TXQUEUE_THRESHOLD_96B,      /* Transmit Queue Threshold 96Bytes */
    ETH_TXQUEUE_THRESHOLD_128B,     /* Transmit Queue Threshold 128Bytes */
    ETH_TXQUEUE_THRESHOLD_192B,     /* Transmit Queue Threshold 192Bytes */
    ETH_TXQUEUE_THRESHOLD_256B,     /* Transmit Queue Threshold 256Bytes */
    ETH_TXQUEUE_THRESHOLD_384B,     /* Transmit Queue Threshold 384Bytes */
    ETH_TXQUEUE_THRESHOLD_512B      /* Transmit Queue Threshold 512Bytes */
} Eth_TxQueueThreshold;

/* Define MTL Rx Queue Threshold */
typedef enum
{
    ETH_RXQUEUE_THRESHOLD_64B = 0U, /* Receive Queue Threshold 64Bytes */
    ETH_RXQUEUE_THRESHOLD_32B,      /* Receive Queue Threshold 32Bytes */
    ETH_RXQUEUE_THRESHOLD_96B,      /* Receive Queue Threshold 96Bytes */
    ETH_RXQUEUE_THRESHOLD_128B      /* Receive Queue Threshold 128Bytes */
} Eth_RxQueueThreshold;

/* Define the Rx/Tx MTL queue */
typedef enum
{
    ETH_MTL_QUEUE0 = 0U, /* MTL Queue ID 0 */
    ETH_MTL_QUEUE1,      /* MTL Queue ID 1 */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    ETH_MTL_QUEUE2,      /* MTL Queue ID 2, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    ETH_MTL_QUEUE3       /* MTL Queue ID 3, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
#endif /* THA6_THA6206\THA6_THA6206D\THA_THA6412 */
} Eth_MtlQueue;

/* Define DMA Interrupt Mode */
typedef enum
{
    ETH_DMA_INTERRUPT_MODE0 = 0U, /* sbd_perch_* are pulse signals for packet transfer completion*/
    ETH_DMA_INTERRUPT_MODE1,      /* sbd_perch_* are level signals for packet transfer completion */
    ETH_DMA_INTERRUPT_MODE2       /* sbd_perch_* are level signals for packet transfer completion,
                                  signal is asserted again if same event occurred before it was cleared */
} Eth_DmaInterruptMode;

/* Define programmable burst length of DMA channel */
typedef enum
{
    ETH_DMA_BURSTLENGTH0 = 0U,   /* maximum burst length 0 */
    ETH_DMA_BURSTLENGTH1 = 1U,   /* maximum burst length 1 */
    ETH_DMA_BURSTLENGTH2 = 2U,   /* maximum burst length 2 */
    ETH_DMA_BURSTLENGTH4 = 4U,   /* maximum burst length 4 */
    ETH_DMA_BURSTLENGTH8 = 8U,   /* maximum burst length 8 */
    ETH_DMA_BURSTLENGTH16 = 16U, /* maximum burst length 16 */
    ETH_DMA_BURSTLENGTH32 = 32U  /* maximum burst length 32 */
} Eth_DmaBurstLength;

/* Define DMA interrupt enable flags */
typedef enum
{
    ETH_DMA_TRANSMIT = 0x0001U,                  /* Transmit Interrupt */
    ETH_DMA_TRANSMITSTOPED = 0x0002U,            /* Transmit Stopped */
    ETH_DMA_TRANSMITBUFFERUNAVAILABLE = 0x0004U, /* Transmit Buffer Unavailable*/
    ETH_DMA_RECEIVE = 0x0040U,                   /* Receive Interrupt */
    ETH_DMA_RECEIVEBUFFERUNAVAILABLE = 0x0080U,  /* Receive Buffer Unavailable */
    ETH_DMA_RECEIVESTOPPED = 0x0100U,            /* Receive Stopped */
    ETH_DMA_RECEIVEWATCHDOGTIMEOUT = 0x0200U,    /* Receive Watch-dog Timeout */
    ETH_DMA_EARLYTRANSMIT = 0x0400U,             /* Early Transmit Interrupt */
    ETH_DMA_EARLYRECEIVE = 0x0800U,              /* Early Receive Interrupt */
    ETH_DMA_FATALBUSERROR = 0x1000U,             /* Fatal Bus Error */
    ETH_DMA_CONTEXTDESCRIPTORERROR = 0x2000U,    /* Context Descriptor Error */
    ETH_DMA_ABNORMALINTERRUPTSUMMARY = 0x4000U,  /* Abnormal Interrupt Summary:TXSE|RBUE|RSE|RWTE|ETIE|FBEE|CDEE */
    ETH_DMA_NORMALINTERRUPTSUMMARY = 0x8000U     /* Normal Interrupt Summary:TIE|TBUE|RIE|ERIE */
/* #Violation: eth_hal_h_REF_2 */
} Eth_DmaInterruptFlag;

/* Define type of payload */
typedef enum
{
    ETH_PAYLOAD_TYPE_UNKNOWN = 0U, /* Unknown type or IP payload not processed */
    ETH_PAYLOAD_TYPE_UDP,          /* UDP packet */
    ETH_PAYLOAD_TYPE_TCP,          /* TCP packet */
    ETH_PAYLOAD_TYPE_ICMP          /* ICMP packet */
} Eth_PayloadType;

/* Define CSR clock range, for THA6206\THA6206D\THA6412\THA6104, CSR clock is 100MHz */
typedef enum
{
    ETH_CSR_CLK_42 = 0U, /* CSR Clock = 60-100MHz,MDC Clock is CSR Clock/42 */
    ETH_CSR_CLK_62,      /* CSR Clock = 100-150MHz,MDC Clock is CSR Clock/62 */
    ETH_CSR_CLK_16,      /* CSR Clock = 20-35MHz,MDC Clock is CSR Clock/16 */
    ETH_CSR_CLK_26,      /* CSR Clock = 35-60MHz,MDC Clock is CSR Clock/26 */
    ETH_CSR_CLK_102,     /* CSR Clock = 150-250MHz,MDC Clock is CSR Clock/102 */
    ETH_CSR_CLK_124,     /* CSR Clock = 250-300MHz,MDC Clock is CSR Clock/124 */
    ETH_CSR_CLK_204,     /* CSR Clock = 300-500MHz,MDC Clock is CSR Clock/204 */
    ETH_CSR_CLK_324,     /* CSR Clock = 500-800MHz,MDC Clock is CSR Clock/324 */
    ETH_FASK_CSR_CLK_4,  /* MDC Clock is CSR Clock/4 */
    ETH_FASK_CSR_CLK_6,  /* MDC Clock is CSR Clock/6 */
    ETH_FASK_CSR_CLK_8,  /* MDC Clock is CSR Clock/8 */
    ETH_FASK_CSR_CLK_10, /* MDC Clock is CSR Clock/10 */
    ETH_FASK_CSR_CLK_12, /* MDC Clock is CSR Clock/12 */
    ETH_FASK_CSR_CLK_14, /* MDC Clock is CSR Clock/14 */
    ETH_FASK_CSR_CLK_16, /* MDC Clock is CSR Clock/16 */
    ETH_FASK_CSR_CLK_18  /* MDC Clock is CSR Clock/18 */
/* #Violation: eth_hal_h_REF_2 */
} Eth_CsrClockRange;

/* Define RGMII CLK Skew Control */
typedef enum
{
    ETH_CLKDELAY_CELL_0 = 0x0U, /* 0 delay cell */
    ETH_CLKDELAY_CELL_1 = 0x01U, /* 1 delay cell */
    ETH_CLKDELAY_CELL_2 = 0x03U, /* 2 delay cell */
    ETH_CLKDELAY_CELL_3 = 0x07U, /* 3 delay cell */
    ETH_CLKDELAY_CELL_4 = 0x0FU, /* 4 delay cell */
    ETH_CLKDELAY_CELL_5 = 0x10U, /* 5 delay cell */
    ETH_CLKDELAY_CELL_6 = 0x11U, /* 6 delay cell */
    ETH_CLKDELAY_CELL_7 = 0x13U, /* 7 delay cell */
    ETH_CLKDELAY_CELL_8 = 0x17U, /* 8 delay cell */
    ETH_CLKDELAY_CELL_9 = 0x1FU, /* 9 delay cell */
    ETH_CLKDELAY_CELL_10 = 0x30U, /* 10 delay cell */
    ETH_CLKDELAY_CELL_11 = 0x31U, /* 11 delay cell */
    ETH_CLKDELAY_CELL_12 = 0x33U, /* 12 delay cell */
    ETH_CLKDELAY_CELL_13 = 0x37U, /* 13 delay cell */
    ETH_CLKDELAY_CELL_14 = 0x3FU, /* 14 delay cell */
    ETH_CLKDELAY_CELL_15 = 0x70U, /* 15 delay cell */
    ETH_CLKDELAY_CELL_16 = 0x71U, /* 16 delay cell */
    ETH_CLKDELAY_CELL_17 = 0x73U, /* 17 delay cell */
    ETH_CLKDELAY_CELL_18 = 0x77U, /* 18 delay cell */
    ETH_CLKDELAY_CELL_19 = 0x7FU, /* 19 delay cell */
    ETH_CLKDELAY_CELL_20 = 0xF0U, /* 20 delay cell */
    ETH_CLKDELAY_CELL_21 = 0xF1U, /* 21 delay cell */
    ETH_CLKDELAY_CELL_22 = 0xF3U, /* 22 delay cell */
    ETH_CLKDELAY_CELL_23 = 0xF7U, /* 23 delay cell */
    ETH_CLKDELAY_CELL_24 = 0xFFU, /* 24 delay cell */
    ETH_CLKDELAY_CELL_25 = 0x1F0U, /* 25 delay cell */
    ETH_CLKDELAY_CELL_26 = 0x1F1U, /* 26 delay cell */
    ETH_CLKDELAY_CELL_27 = 0x1F3U, /* 27 delay cell */
    ETH_CLKDELAY_CELL_28 = 0x1F7U, /* 28 delay cell */
    ETH_CLKDELAY_CELL_29 = 0x1FFU, /* 29 delay cell */
    ETH_CLKDELAY_CELL_30 = 0x3F0U, /* 30 delay cell */
    ETH_CLKDELAY_CELL_31 = 0x3F1U, /* 31 delay cell */
    ETH_CLKDELAY_CELL_32 = 0x3F3U, /* 32 delay cell */
    ETH_CLKDELAY_CELL_33 = 0x3F7U, /* 33 delay cell */
    ETH_CLKDELAY_CELL_34 = 0x3FFU, /* 34 delay cell */
    ETH_CLKDELAY_CELL_35 = 0x400U, /* 35 delay cell */
    ETH_CLKDELAY_CELL_36 = 0x401U, /* 36 delay cell */
    ETH_CLKDELAY_CELL_37 = 0x403U, /* 37 delay cell */
    ETH_CLKDELAY_CELL_38 = 0x407U, /* 38 delay cell */
    ETH_CLKDELAY_CELL_39 = 0x40FU, /* 39 delay cell */
    ETH_CLKDELAY_CELL_40 = 0x410U, /* 40 delay cell */
    ETH_CLKDELAY_CELL_41 = 0x411U, /* 41 delay cell */
    ETH_CLKDELAY_CELL_42 = 0x413U, /* 42 delay cell */
    ETH_CLKDELAY_CELL_43 = 0x417U, /* 43 delay cell */
    ETH_CLKDELAY_CELL_44 = 0x41FU, /* 44 delay cell */
    ETH_CLKDELAY_CELL_45 = 0x430U, /* 45 delay cell */
    ETH_CLKDELAY_CELL_46 = 0x431U, /* 46 delay cell */
    ETH_CLKDELAY_CELL_47 = 0x433U, /* 47 delay cell */
    ETH_CLKDELAY_CELL_48 = 0x437U, /* 48 delay cell */
    ETH_CLKDELAY_CELL_49 = 0x43FU, /* 49 delay cell */
    ETH_CLKDELAY_CELL_50 = 0x470U, /* 50 delay cell */
    ETH_CLKDELAY_CELL_51 = 0x471U, /* 51 delay cell */
    ETH_CLKDELAY_CELL_52 = 0x473U, /* 52 delay cell */
    ETH_CLKDELAY_CELL_53 = 0x477U, /* 53 delay cell */
    ETH_CLKDELAY_CELL_54 = 0x47FU, /* 54 delay cell */
    ETH_CLKDELAY_CELL_55 = 0x4F0U, /* 55 delay cell */
    ETH_CLKDELAY_CELL_56 = 0x4F1U, /* 56 delay cell */
    ETH_CLKDELAY_CELL_57 = 0x4F3U, /* 57 delay cell */
    ETH_CLKDELAY_CELL_58 = 0x4F7U, /* 58 delay cell */
    ETH_CLKDELAY_CELL_59 = 0x4FFU, /* 59 delay cell */
    ETH_CLKDELAY_CELL_60 = 0x5F0U, /* 60 delay cell */
    ETH_CLKDELAY_CELL_61 = 0x5F1U, /* 61 delay cell */
    ETH_CLKDELAY_CELL_62 = 0x5F3U, /* 62 delay cell */
    ETH_CLKDELAY_CELL_63 = 0x5F7U, /* 63 delay cell */
    ETH_CLKDELAY_CELL_64 = 0x5FFU, /* 64 delay cell */
    ETH_CLKDELAY_CELL_65 = 0x7F0U, /* 65 delay cell */
    ETH_CLKDELAY_CELL_66 = 0x7F1U, /* 66 delay cell */
    ETH_CLKDELAY_CELL_67 = 0x7F3U, /* 67 delay cell */
    ETH_CLKDELAY_CELL_68 = 0x7F7U, /* 68 delay cell */
    ETH_CLKDELAY_CELL_69 = 0x7FFU /* 69 delay cell */
} Eth_ClkDelay;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Structure for ETH pins Configuration */
typedef struct
{
    Port_EthRmiiPinsConfig *pRmiiPins;   /* Pointer to structure for RMII pins */
    Port_EthRgmiiPinsConfig *pRgmiiPins; /* Pointer to structure for RGMII pins, THA6206, THA6206D and THA6412 are supported,
                                            but THA6104 is not supported */
    Port_EthMiiPinsConfig *pMiiPins;     /* Pointer to structure for MII pins */
} Eth_PinConfig;

/* Structure for ETH DMA Rx Descriptor */
typedef struct
{
/* #Violation: eth_hal_h_REF_4 */
    Eth_RxDescr0 RDES0; /* Rx Descriptor DWORD 0 */
    Eth_RxDescr1 RDES1; /* Rx Descriptor DWORD 1 */
    Eth_RxDescr2 RDES2; /* Rx Descriptor DWORD 2 */
    Eth_RxDescr3 RDES3; /* Rx Descriptor DWORD 3 */
} Eth_RxDescr;

/* Structure for ETH DMA Tx Descriptor */
typedef struct
{
    Eth_TxDescr0 TDES0; /* Tx Descriptor DWORD 0 */
    Eth_TxDescr1 TDES1; /* Tx Descriptor DWORD 1 */
    Eth_TxDescr2 TDES2; /* Tx Descriptor DWORD 2 */
    Eth_TxDescr3 TDES3; /* Tx Descriptor DWORD 3 */
} Eth_TxDescr;

/* Structure for ETH MAC initialization configuration */
typedef struct
{
    Eth_DuplexMode duplexMode;          /* Duplex Mode */
    Eth_LineSpeed lineSpeed;            /* Ethernet line speed */
    Eth_LoopbackMode loopbackMode;      /* Loopback mode enable/disable */
    uint16 maxPacketSize;               /* Maximum size of the ethernet packet */
    uint8 macAddress[6];                /* MAC address for the ethernet */
    boolean enableTimestamp;            /* Enable/disable timestamp */
    boolean allPacketPassing;           /* Set receive all packet */
    boolean daAddrInversePassing;       /* Set destination address inverse Filter */
    boolean vlanTagPassing;             /* Set VLAN Tag Filter */
    boolean enablePromiscuous;          /* Set promiscuousMode */
    boolean enableMulticast;            /* Set multicasteMode */
    boolean enableBroadcast;            /* Set broadcastMode */
    boolean checksumOffload;            /* Set checksum offload */
    boolean crcStrippingForEther;       /* Set CRC stripping for Type packets */
    boolean automaticPadOrCRCStripping; /* Set pad stripping for Type or ethernet packets */
    boolean disableCrcChecking;         /* Set CRC Checking for Received Packets */
} Eth_MacConfig;

/* Structure for ETH MTL Tx Queue Configuration */
typedef struct
/* #Violation: eth_hal_h_REF_4 */
{
    boolean storeAndForward;                  /* Transmit store and forward enable/disable */
    Eth_TxQueueSize txQueueSize;              /* Tx Queue size */
    Eth_TxQueueThreshold txQueueThreshold;    /* Transmit Queue Threshold */
    boolean txQueueUnderflowInterruptEnabled; /* Enable/Disable Tx Queue Underflow Interrupt */
    boolean txQueueEnabled;                   /* Enable/Disable Tx Queue */
    Eth_MtlTxqen txQueueMode;                 /* MTL_TxQ_Operation_Mode*/
    uint16 idleSlopeCredit;                   /* The Idle slope credit for Queue*/
    uint32 hiCredit;                          /* The high credit for qav Queue*/
    uint32 loCredit;                          /* The low credit for qav Queue*/
    uint16 sendSlopeCredit;                   /* The send slope credit for qav Queue*/
    uint16 txChId;                            /* The queue id*/
} Eth_TxQueueConfig;

/* Structure for ETH MTL Rx Queue Configuration */
typedef struct
/* #Violation: eth_hal_h_REF_4 */
{
    boolean storeAndForward;                 /* Receive Store and Forward Enable/Disable */
    Eth_RxQueueSize rxQueueSize;             /* Rx Queue size */
    Eth_RxFlowControlThresholds  rxFlowControlThresholdsActive; /* RFA: Threshold for activating flow control */
    Eth_RxFlowControlThresholds  rxFlowControlThresholdsDeactive; /* RFD: Threshold for deactivating flow control */
    Eth_RxQueueThreshold rxQueueThreshold;   /* Receive Queue Threshold */
    Eth_DmaChannel rxDmaChannelMap;          /* Mapped DMA Channel of Rx Queue */
    uint8 taggedUserpriority;                /* tagged packets user priority, set 0 if single channel */
    boolean forwardErrorPacket;              /* Error Packet Forwarding Enable/Disable */
    boolean forwardUndersizedGoodPacket;     /* Undersized Good Packet Forwarding Enable/Disable */
    boolean rxQueueOverflowInterruptEnabled; /* Enable/Disable Rx Queue Overflow Interrupt */
    boolean rxQueueEnabled;                  /* Enable/Disable Rx Queue */
    boolean rxFlowCtlEnabled;                /* Enable/Disable flow control signal operation */
} Eth_RxQueueConfig;

/* Structure for ETH MTL bdAndMultiQueue configuration */
typedef struct
{
    Eth_MtlQueue bdAndMultiQueue;  /* Broad And Multicast queue, MCBCQ */
    boolean bdAndMultiQueueEnable; /* Broad And Multicast queue enable, MCBCQEN */
} Eth_MtlRxBdAndMultiQueueConfig;

/* Structure for ETH MTL bdAndMultiQueue configuration */
typedef struct
{
    Eth_MtlQueue unicastAVTPQueue; /* Unicast AVTP queue, AVCPQ */
    boolean taggedAVQueueEnable;   /* Tagged AV control packets queue enable,TACPQE */
} Eth_MtlRxUnicastAVTPQueueConfig;

/* Structure for ETH MTL RxQueue configuration */
typedef struct
{
    boolean overridingMcbcqPriEnable;                       /* Overriding MC-BC queue priority select,OMCBCQ */
    Eth_MtlRxBdAndMultiQueueConfig bdAndMultiQueueConfig;   /* Broad And Multicast queue config */
    Eth_MtlRxUnicastAVTPQueueConfig unicastAVTPQueueConfig; /* Unicast AVTP queue, AVCPQ */
    Eth_MtlQueue unicastPTPQueue;                           /* Unicast PTP queue, PTPQ */
    Eth_MtlQueue remainingUnicastQueue;                     /* Remaining Unicast queue, UPQ */
    Eth_MtlQueue preemptableQueue;                          /* All preemptable packet queue */
} Eth_MtlRxQueueConfig;

/* Structure for ETH MTL initialization configuration */
typedef struct
{
    boolean txFifoEccEnable; /* Set ECC feature for MTL Tx FIFO memory */
    boolean rxFifoEccEnable; /* Set ECC feature for MTL Rx FIFO memory */
    Eth_MtlRxQueueConfig rxQueueConfig; /* Configure ETH MTL rxQueue */
    const Eth_TxQueueConfig *txQueue; /* Tx queue configurations of selected queues */
    const Eth_RxQueueConfig *rxQueue; /* Rx queue configurations of selected queues */
} Eth_MtlConfig;

/* DMA Channel Interrupt Enable Register */
typedef struct
{
    ureg32 TIE:1;          /* [0:0] Transmit Interrupt Enable - TIE (rw) */
    ureg32 TXSE:1;         /* [1:1] Transmit Stopped Enable - TXSE (rw) */
    ureg32 TBUE:1;         /* [2:2] Transmit Buffer Unavailable Enable - TBUE (rw) */
    ureg32 reserved_3:3;   /* [5:3] internal Reserved */
    ureg32 RIE:1;          /* [6:6] Receive Interrupt Enable - RIE (rw) */
    ureg32 RBUE:1;         /* [7:7] Receive Buffer Unavailable Enable - RBUE (rw) */
    ureg32 RSE:1;          /* [8:8] Receive Stopped Enable - RSE (rw) */
    ureg32 RWTE:1;         /* [9:9] Receive Watchdog Timeout Enable - RWTE (rw) */
    ureg32 ETIE:1;         /* [10:10] Early Transmit Interrupt Enable - ETIE (rw) */
    ureg32 ERIE:1;         /* [11:11] Early Receive Interrupt Enable - ERIE (rw) */
    ureg32 FBEE:1;         /* [12:12] Fatal Bus Error Enable - FBEE (rw) */
    ureg32 CDEE:1;         /* [13:13] Context Descriptor Error Enable - CDEE (rw) */
    ureg32 AIE:1;          /* [14:14] Abnormal Interrupt Summary Enable - AIE (rw) */
    ureg32 NIE:1;          /* [15:15] Normal Interrupt Summary Enable - NIE (rw) */
    ureg32 reserved_16:16; /* [31:16] internal Reserved */
} Eth_DmaChInterruptEnableBit;

/* DMA Channel Interrupt Enable Register */
typedef union
/* #Violation: eth_hal_h_REF_3 */
{
    uint32 U;                      /* Unsigned access */
    Eth_DmaChInterruptEnableBit B; /* Bitfield access */
} Eth_DmaChInterruptEnable;

/* Structure for ETH DMA Tx channel configuration */
typedef struct
{
    Eth_DmaBurstLength maxBurstLength;               /* Maximum burst length of the channel */
    Eth_TxDescr *pTxDescrList;                       /* Pointer to TX descriptors RAM */
    uint8 *pDescTxBuffer;                            /* Ponter to Tx Buffer  */
    Eth_DmaChInterruptEnable txDmaChInterruptEnable; /* DMA channel Tx interrupt enable */
    boolean txChannelEnabled;                        /* Enable/Disable Tx Channel */
    uint16 numOfTxBuffers;                           /* Number of tx buffers.*/
    uint16 txBufferAlignSize;                        /* Configured tx buffer size after align*/
    uint8 txChIdx;                                   /* DMA channel id*/
    uint8 txDmaChnlWght;                             /* DMA channel Arbitration weight*/
} Eth_TxChannelConfig;

/* Structure for ETH DMA Rx channel configuration */
typedef struct
{
    Eth_DmaBurstLength maxBurstLength;               /* Maximum burst length of the channel */
    Eth_RxDescr *pRxDescrList;                       /* pointer to Rx descriptors RAM */
    uint8 *pDescRxBuffer;                            /* Ponter to Rx Buffer */
    Eth_DmaChInterruptEnable rxDmaChInterruptEnable; /* DMA channel Rx interrupt enable */
    boolean rxChannelEnabled;                        /* Enable/Disable Rx Channel */
    /*Rx Ingress cfg */
    uint16 numOfRxBuffers;                           /* Number of Recive buffers*/
    uint16 rxBufferAlignSize;                        /* Size of of Recive buffer after align*/
} Eth_RxChannelConfig;

/* Structure for ETH DMA initialization configuration */
typedef struct
{
    boolean addrAlignedBeatsEnabled;                 /* Enable/Disable Address Aligned Beats */
    Eth_DmaInterruptMode interruptMode;              /* Interrupt mode */
    const Eth_TxChannelConfig *txChannel;            /* Tx Channels configurations of selected Channels */
    const Eth_RxChannelConfig *rxChannel;            /* Rx Channels configurations of selected Channels */
} Eth_DmaConfig;

/* Structure for ETH Module initialization configuration */
typedef struct
{
    ETH_MODULE *const pEthModule;          /* Pointer to ETH register base address */
    Eth_PhyInterfaceMode phyInterfaceMode; /* External Phy Interface RMII Mode */
    Eth_ClkDelay txClkDelay;               /* Set the Tx clock delay in RGMII mode, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    Eth_ClkDelay rxClkDelay;               /* Set the Rx clock delay in RGMII mode, THA6206, THA6206D and THA6412 are supported, but THA6104 is not supported */
    Eth_PinConfig pins;                    /* Configuration structure for Pins */
    Eth_MacConfig mac;                     /* Configuration structure for MAC initialization */
    Eth_MtlConfig mtl;                     /* Configuration structure for MTL initialization */
    Eth_DmaConfig dma;                     /* Configuration structure for DMA initialization */
    uint8 ethNumTxChnls;                   /* Number of Tx channels used in the controller, THA6206, THA6206D and THA6412 support
                                            up to 4 Tx channels, while THA6104 supports up to 2 Tx channels */
    uint8 ethDmaTxArbAlg;                  /* DMA transmit arbitration algorithm */
    uint8 ethMtlTxSchAlg;                  /* MTL transmit scheduling algorithm */
    uint8 ethNumRxChnls;                   /* Number of Rx Channels used in the controller, THA6206, THA6206D and THA6412 support
                                            up to 4 Tx channels, while THA6104 supports up to 2 Tx channels */
    uint8 ethUntagRxQueue;                 /* Queue where the untagged Rx frames are routed, Without using this parameter, the corresponding
                                              configuration of this parameter is controlled by Eth_MtlRxQueueConfig.remainingUnicastQueue. */
    boolean txIrqIsEnabled;                /* Transmit interrupt is enabled */
    boolean rxIrqIsEnabled;                /* Receive interrupt is enabled */
    uint32 ethFre;                         /* ETH frequency, in Hz */
    Eth_CsrClockRange ethMiiCrValue;       /* CR value for MII, CSR clock */
} Eth_Config;

/* Structure for ETH detailed status of a receive buffer descriptor */
typedef struct
{
    Eth_PayloadType payloadType;       /* The type of payload encapsulated in the IP datagram */
    Eth_TimeStampType timeStamp;       /* The timestamp of the received packet */
    uint32 errStatus;                  /* Representing the errors that occurred */
    uint16 outerVlanTag;               /* The outer VLAN tag of the received packet */
    uint16 innerVlanTag;               /* The inner VLAN tag of the received packet */
    boolean ipv6;                      /* Indicates that the frame is an IPv6 frame */
    boolean ipv4;                      /* Indicates that the frame is an IPv4 frame */
    boolean ipPayloadErr;              /* Indicates that an IP payload error has occurred */
    boolean ipHeaderErr;               /* Indicates that an IP header error has occurred */
    boolean ingressTimeStampAvailable; /* IngressTimeStamp is available */
    Eth_RxDescr *pCurDescr;            /* Pointer to Rx Descriptor (current descriptor) */
} Eth_RxInfo;

/* Structure for ETH detailed status of a transmit buffer descriptor */
typedef struct
{
    Eth_TimeStampType timeStamp;      /* The timestamp of the received packet */
    uint32 errStatus;                 /* Representing the errors that occurred */
    boolean egressTimeStampAvailable; /* EgressTimeStamp is available */
} Eth_TxInfo;

/* Structure for ETH Tx channels of descriptor information */
/* #Violation: eth_hal_h_REF_4 */

typedef struct
/* #Violation: eth_hal_h_REF_4 */
{
    uint32 descrBufAddr;      /* Descriptor buffer1 address */
    uint32 txdescTxConfirm; /* Transmit descriptor buffer pointer */
#if (ETH_SWT_MANAGEMENT_SUPPORT == TRUE)
    uint8 *swtTxDataPtr;    /* Pointer to the Tx Data address used during invocation of EthSwt APIs */
    uint16 swtTxLength;     /* To store the Tx Length used during invocation of EthSwt APIs */
#endif
} Eth_TxDescrInfo;

/* Structure for ETH Tx channels information*/
/* #Violation: eth_hal_h_REF_4 */

typedef struct
/* #Violation: eth_hal_h_REF_4 */
{
    Eth_DmaChannel channelId;       /* Tx DMA channel Index */
    uint32 numOfDescriptor;         /* Number of descriptor */
    uint16 txBuffer1Size;           /* Configured Tx buffer1 size */
    Eth_TxInfo txInfo;              /* ETH detailed status of a transmit buffer descriptor */
#if (ETH_SWT_MANAGEMENT_SUPPORT == TRUE)
    uint16 currQFront;              /* Current queue front index used to get the element from the queue */
    uint16 currQRear;               /* Current queue rear index used to store the element into the queue */
#endif
    volatile Eth_TxDescr *pTxDescriptor;     /* Pointer to Tx Descriptor (current descriptor) */
    boolean txChannelEnabled;       /* Enable/Disable Tx Queue */
    uint32 descIndex;               /* Tx descriptor index */
    Eth_TxDescr *pTxBaseDescriptor; /* Pointer to Tx base Descriptor (TX descriptors RAM) */
} Eth_TxChannelInfo;

/* Structure for ETH Rx channels of descriptor information */
typedef struct
/* #Violation: eth_hal_h_REF_4 */
{
    uint32 descrBufAddr;      /* Descriptor buffer1 address */
#if (ETH_SWT_MANAGEMENT_SUPPORT == TRUE)
    uint8 *swtRxDataPtr;      /* Pointer to the Rx Data address used during invocation of EthSwt APIs */
    uint16 swtRxLength;       /* To store the Rx Length used during invocation of EthSwt APIs */
    boolean swtMgmtFrameOnly; /* Flag to indicate type of frame used during invocation of EthSwt APIs */
#endif
} Eth_RxDescrInfo;

/* Structure for ETH Rx channels information */
typedef struct
/* #Violation: eth_hal_h_REF_4 */
{
    Eth_DmaChannel channelId;       /* Rx DMA channel Index */
    uint32 numOfDescriptor;         /* Number of descriptor */
    uint16 rxBuffer1Size;           /* Configured Rx buffer1 size */
    Eth_RxInfo rxInfo;              /* ETH detailed status of a receive buffer descriptor */
    volatile Eth_RxDescr *pRxDescriptor; /* Pointer to Rx Descriptor (current descriptor) */
    boolean rxChannelEnabled;       /* Enable/Disable Rx Queue */
    uint32 descIndex;               /* Rx descriptor index */
    uint16 rxCount;                 /* Number of frames received */
    Eth_RxDescr *pRxBaseDescriptor; /* Pointer to Rx base Descriptor */
} Eth_RxChannelInfo;

/* Structure for ETH driver handle */
typedef struct
{
    ETH_MODULE *pEthModule;              /* Pointer to the ETH module registers */
    Eth_TxDescrInfo **txDescrInfoPtr;    /* Tx channels handle of descriptor information */
    Eth_RxDescrInfo **rxDescrInfoPtr;    /* Rx channels handle of descriptor information */
    Eth_RxChannelInfo *rxChannelInfoPtr; /* Rx channels information handle */
    Eth_TxChannelInfo *txChannelInfoPtr; /* Tx channels information handle */
    float64 prevFreqCompensationValue;   /* Previous frequency compensation value */
    Eth_CsrClockRange ethMiiCrValue;     /* CR value for MII */
    uint8 numOfUsedTxCh;                 /* Number of transmit channel scheduled used, THA6206, THA6206D and THA6412 support
                                          up to 4 Tx channels, while THA6104 supports up to 2 Tx channels*/
} Eth_NodeHandle;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: eth_hal_h_REF_8 */
#define ETH_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: eth_hal_h_REF_9 */
#include "Eth_MemMap.h"

/**********************************************************************************************************************
 * Function:     Eth_Hal_Init
 * Description:  Initialize ETH module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthConfig: Pointer to the structure for ETH module initialization configuration
 * Inout:        pEthNode:  Pointer to the Structure for ETH driver handle
 * Output:       None
 * Return:       Eth_Status:
 *                 ETH_STATUS_OK: Successfully initialized the ETH module and register read back check correct
 *                 ETH_STATUS_ERROR: Failed to initialize ETH module or register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_Status Eth_Hal_Init(Eth_NodeHandle *pEthNode, const Eth_Config *const pEthConfig);

/**********************************************************************************************************************
 * Function:     Eth_Hal_GetControllerMode
 * Description:  Get the controller mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthNode:  Pointer to the Structure for ETH driver handle
 * Inout:        None
 * Output:       None
 * Return:       Eth_ModeType:
 *                 ETH_MODE_DOWN: Controller disabled
 *                 ETH_MODE_ACTIVE: Controller enabled
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_ModeType Eth_Hal_GetControllerMode(const Eth_NodeHandle *const pEthNode);

/**********************************************************************************************************************
 * Function:     Eth_Hal_SetControllerMode
 * Description:  Set the controller mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode:  Pointer to the Structure for ETH driver handle
 *               ctrlMode: The controller mode
 * Inout:        None
 * Output:       None
 * Return:       Eth_Status:
 *                 ETH_STATUS_OK: Successfully set the controller mode and register read back check correct
 *                 ETH_STATUS_ERROR: Failed to set the controller mode or register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_Status Eth_Hal_SetControllerMode(const Eth_NodeHandle *const pEthNode, Eth_ModeType ctrlMode);

/**********************************************************************************************************************
 * Function:     Eth_Hal_GetMacAddress
 * Description:  Obtain MAC address(physical source address)
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthNode:  Pointer to the Structure for ETH driver handle
 * Inout:        None
 * Output:       pMacAddr: Pointer to physical source address (MAC address) in network byte order
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern void Eth_Hal_GetMacAddress(const Eth_NodeHandle *const pEthNode, uint8 *const pMacAddr);

/**********************************************************************************************************************
 * Function:     Eth_Hal_SetMacAddress
 * Description:  Set MAC address(physical source address)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode:  Pointer to the Structure for ETH driver handle
 *               pMacAddr: Pointer to physical source address (MAC address)
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern boolean Eth_Hal_SetMacAddress(const Eth_NodeHandle *const pEthNode, const uint8 *const pMacAddr);

/**********************************************************************************************************************
 * Function:     Eth_Hal_UpdatePhysAddrFilter
 * Description:  Update the physical DA address filter
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode:  Pointer to the Structure for ETH driver handle
 *               pMacAddr: Pointer to the physical destination address (MAC address) in network byte order
 *               action: Add or remove the address from the Ethernet controllers filter
 * Inout:        None
 * Output:       None
 * Return:       Eth_Status:
 *                 ETH_STATUS_OK: Successfully updated the physical DA address filter and register read back check correct
 *                 ETH_STATUS_ERROR: Failed to update the physical DA address filter or register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_Status Eth_Hal_UpdatePhysAddrFilter(const Eth_NodeHandle *const pEthNode, const uint8 *const pMacAddr,
                                               Eth_FilterActionType action);

/**********************************************************************************************************************
 * Function:     Eth_Hal_GetDropCounter
 * Description:  Reads a list with drop counter values of the corresponding controller
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthNode:  Pointer to the structure for ETH driver handle
 * Inout:        None
 * Output:       pDropCounter: Pointer to the Structure for statistic counter for diagnostics
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *  2024/12/19    01359      Modify: Delete the Inout parameter CouterValue and Change the attribute
 *                                   of the output parameter pDropCounter from uint32 to Eth_CounterType
 *********************************************************************************************************************/
extern void Eth_Hal_GetDropCounter(const Eth_NodeHandle *const pEthNode, Eth_CounterType *const pDropCounter);

/**********************************************************************************************************************
 * Function:     Eth_Hal_GetEtherStats
 * Description:  Obtain the Rx statistical results
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 * Inout:        None
 * Output:       pEtherStats: Pointer to the Structure for ETH Rx statistic
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern void Eth_Hal_GetEtherStats(const Eth_NodeHandle *const pEthNode, Eth_RxStatsType *const pEtherStats);

/**********************************************************************************************************************
 * Function:     Eth_Hal_GetTxStats
 * Description:  Obtain the Tx statistical results
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 * Inout:        None
 * Output:       pTxStats: Pointer to the Structure for ETH Tx statistic
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/12/27    01359      Create
 *********************************************************************************************************************/
extern void Eth_Hal_GetTxStats(const Eth_NodeHandle *const pEthNode, Eth_TxStatsType *const pTxStats);

/**********************************************************************************************************************
 * Function:     Eth_Hal_GetTxErrorCounterValues
 * Description:  Obtain the transmission error counter values
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 * Inout:        None
 * Output:       pTxErrorCounterValues: Pointer to the Structure for ETH transmission Error Counters
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/12/27    01359      Create
 *********************************************************************************************************************/
extern void Eth_Hal_GetTxErrorCounterValues(const Eth_NodeHandle *const pEthNode, Eth_TxErrorCounterValuesType *const pTxErrorCounterValues);

/**********************************************************************************************************************
 * Function:     Eth_Hal_Receive
 * Description:  The function shall receive ETH data.
 *               The function shall read the next frame from the receive buffers.
 *               Check the receive errors, timestamp and reply to the application.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               channelId: The Rx DMA channel
 * Inout:        pRxInfo: Pointer to the receive information
 * Output:       pRxBuf: Pointer to the RxBuf
 *               pReceiveLength: Pointer to the length of received
 * Return:       Eth_RxStatusType:
 *                 ETH_RECEIVED: A frame has been received and there are no more frames in the queue
 *                 ETH_NOT_RECEIVED: No frames received
 *                 ETH_RECEIVED_MORE_DATA_AVAILABLE: A frame received and at least another one in the queue detected
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_RxStatusType Eth_Hal_Receive(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint8 **const pRxBuf, uint16 *const pReceiveLength,
                             Eth_RxInfo *const pRxInfo);

/**********************************************************************************************************************
 * Function:    Eth_Hal_GetTxBuffer
 * Description: Get transmit buffer,transmit buffer should be aligned(64) format
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthNode: Pointer to the Structure for ETH driver handle
 *              channelId: The Tx DMA channel
 * Inout:       pLenByte: In: desired length in bytes, out: granted length in bytes
 * Output:      pBufIdx: Index to the granted buffer resource
 *              pTxBuf: Pointer to Tx buffer
 * Return:      Eth_Status:
 *                ETH_STATUS_OK: Success status
 *                ETH_STATUS_BUSY: Hardware busy status
 *                ETH_STATUS_OVFL: No buffer of the required length
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_Status Eth_Hal_GetTxBuffer(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint32 *const pBufIdx,
                                      uint8 **const pTxBuf, uint16 *const pLenByte);

/**********************************************************************************************************************
 * Function:    Eth_Hal_Transmit
 * Description: Transmit ETH data, the max length of transmit data is 1522 bytes
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthNode: Pointer to the Structure for ETH driver handle
 *              channelId: The Tx DMA channel
 *              beginBufIdx: The first buffer index for this packet transmission
 *              endBufIdx: The last buffer index for this packet transmission
 *              packetLength: The packet length to transmit
 * Inout:       None
 * Output:      None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    00930      Create
 *********************************************************************************************************************/
extern boolean Eth_Hal_Transmit(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint32 beginBufIdx, uint32 endBufIdx,
                             uint32 packetLength);

/**********************************************************************************************************************
 * Function:    Eth_Hal_GetTxStatus
 * Description: Checks if the transmission of a Buffer is complete
 *              when transmission succeed, ETH get the timestamp
 *              when transmission fail, ETH get the error status.
 *              when transmission has finished, release the transmit buffer and other resource .
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:       pEthNode: Pointer to the Structure for ETH driver handle
 *              channelId: The Tx DMA channel
 *              beginBufIdx: The first buffer index for this packet transmission
 *              endBufIdx: The last buffer index for this packet transmission
 * Inout:       pTxInfo: Pointer to the transmit confirm information
 * Output:      None
 * Return:      Eth_Status:
 *                ETH_STATUS_OK: Success status
 *                ETH_STATUS_ERROR: Failure status
 *                ETH_STATUS_BUSY: Busy status
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/06/17    00930      Create
 *********************************************************************************************************************/
extern Eth_Status Eth_Hal_GetTxStatus(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint32 beginBufIdx,
                                      uint32 endBufIdx, Eth_TxInfo *const pTxInfo);

/**********************************************************************************************************************
 * Function:    Eth_Hal_SetCurrentTime
 * Description: Set the global ETH Reference time
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthNode:  Pointer to the Structure for ETH driver handle
 *              pTimeStamp: Pointer to the timestamp structure
 * Inout:       None
 * Output:      None
 * Return:      Eth_Status:
 *                ETH_STATUS_OK: Success status
 *                ETH_STATUS_ERROR: Failure status
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    00930      Create
 *********************************************************************************************************************/
extern Eth_Status Eth_Hal_SetCurrentTime(const Eth_NodeHandle *const pEthNode, const Eth_TimeStampType *const pTimeStamp);

/**********************************************************************************************************************
 * Function:    Eth_Hal_SetCurrentTime
 * Description: Get the current global ETH reference time
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:       pEthNode:  Pointer to the Structure for ETH driver handle
 * Inout:        None
 * Output:      pTimeStamp: Pointer to the timestamp structure
 * Return:      None
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    00930      Create
 *********************************************************************************************************************/
extern void Eth_Hal_GetCurrentTime(const Eth_NodeHandle *const pEthNode, Eth_TimeStampType *const pTimeStamp);

/**********************************************************************************************************************
 * Function:    Eth_Hal_SetCorrectionTime
 * Description: Correct the current time
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pTimeOffset: Pointer to the offset between time stamp grandmaster and time stamp by local clock
 *              pRateRatio: Ponter to the time elements to calculate and to modify the ratio of the frequency of
 *                                                           the grandmaster in relation to the frequency of the Local Clock
 * Inout:       pEthNode:  Pointer to the Structure for ETH driver handle
 * Output:      None
 * Return:      Eth_Status:
 *                ETH_STATUS_OK: Success status
 *                ETH_STATUS_ERROR: Failure status
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    00930      Create
 *********************************************************************************************************************/
extern Eth_Status Eth_Hal_SetCorrectionTime(Eth_NodeHandle *const pEthNode, const Eth_TimeIntDiffType *const pTimeOffset,
                                            const Eth_RateRatioType *const pRateRatio);

/**********************************************************************************************************************
 * Function:    Eth_Hal_EnableEgressTimeStamp
 * Description: Enable egress timestamp
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthNode: Pointer to the Structure for ETH driver handle
 *              channelId: The Tx DMA channel
 *              bufIdx: Index of the message buffer, where expects egress time
 * Inout:        None
 * Output:      None
 * Return:      None
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    00930      Create
 *********************************************************************************************************************/
extern void Eth_Hal_EnableEgressTimeStamp(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId, uint32 bufIdx);

/**********************************************************************************************************************
 * Function:    Eth_Hal_WriteMii
 * Description: Write PHY register through MII interface
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthNode: Pointer to the Structure for ETH driver handle
 *              phyAddr: PHY address
 *              regAddr: The register address of PHY
 *              regVal: Value to be written into the register
 * Inout:        None
 * Output:      None
 * Return:      Eth_Status:
 *                 ETH_STATUS_OK: Successfully wrote PHY register through MII interface and register read back check correct
 *                 ETH_STATUS_ERROR: Failed to write PHY register through MII interface or register read back check incorrect
 *                 ETH_STATUS_BUSY: Busy status
 * Others:    None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    00930      Create
 *********************************************************************************************************************/
extern Eth_Status Eth_Hal_WriteMii(const Eth_NodeHandle *const pEthNode, uint32 phyAddr, uint32 regAddr, uint16 regVal);

/**********************************************************************************************************************
 * Function:    Eth_Hal_ReadMii through MII interface
 * Description: Read PHY register to the ETH module registers
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:       pEthNode: Pointer to the Structure for ETH driver handle
 *              phyAddr: PHY address
 *              regAddr: The register address of PHY
 * Inout:        None
 * Output:      pRegVal: The register value to read
 * Return:      Eth_Status:
 *                 ETH_STATUS_OK: Successfully read PHY registerter to the ETH module registers and register read back check correct
 *                 ETH_STATUS_ERROR: Failed to read PHY registerter to the ETH module registers or register read back check incorrect
 *                 ETH_STATUS_BUSY: Busy status
 * Others:      None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    00930      Create
 *********************************************************************************************************************/
extern Eth_Status Eth_Hal_ReadMii(const Eth_NodeHandle *const pEthNode, uint32 phyAddr, uint32 regAddr, uint16 *const pRegVal);

/**********************************************************************************************************************
 * Function:     Eth_Hal_SetDmaInterrupt
 * Description:  Configure DMA interrupts enable
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               channelId: The DMA channel
 *               interruptEnable: Interrupt enable selection
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/24    00930      Create
 *********************************************************************************************************************/
extern boolean Eth_Hal_SetDmaInterrupt(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId,
                                    const uint32 interruptEn);

/**********************************************************************************************************************
 * Function:     Eth_Hal_GetDmaInterruptStatus
 * Description:  Get DMA interrupt Status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               channelId: The DMA channel
 * Inout:        None
 * Output:       None
 * Return:       uint32:DMA interrupt status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/24    00930      Create
 *********************************************************************************************************************/
extern uint32 Eth_Hal_GetDmaInterruptStatus(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId);

/**********************************************************************************************************************
 * Function:     Eth_Hal_ClearDmaInterruptStatus
 * Description:  Clear DMA interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEthNode: Pointer to the Structure for ETH driver handle
 *               channelId: The DMA channel
 *               clearMask: Interrupt clear mask, if the corresponding bit == 1, clear the interrupt
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/10/24    00930      Create
 *********************************************************************************************************************/
extern void Eth_Hal_ClearDmaInterruptStatus(const Eth_NodeHandle *const pEthNode, Eth_DmaChannel channelId,
                                            uint32 clearMask);

/**********************************************************************************************************************
 * Function:     Eth_Hal_FreeRxDescriptor
 * Description:  Free the received descriptors
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       pCurDescr: Pointer to the current descriptor
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/30    00930      Create
 *  2024/12/19    01359      Modify: Removes the release receive descriptor operation and
 *                                   changes the function property from static to extern
 *********************************************************************************************************************/
extern void Eth_Hal_FreeRxDescriptor(volatile Eth_RxDescr *const pCurDescr);

/* #Violation: eth_hal_h_REF_8 */
#define ETH_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: eth_hal_h_REF_9 */
#include "Eth_MemMap.h"
#endif /* ETH_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

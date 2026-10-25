/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    psi5_register.h
 * Author:      01849
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: PSI5 module register definition header file.This file defines the register offsets and bit definitions
 *              for the PSI5 module.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #psi5_register_h_REF_1:MISRAC2012-Rule-19.2;
* Justification:Using unions for bit-field access to registers.
*
* #psi5_register_h_REF_2:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*/
#ifndef PSI5_REGISTER_H_
#define PSI5_REGISTER_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "regtypes.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        PSI5 Register Bit-Fields Definitions
 *********************************************************************************************************************/
/* Control register */
typedef struct
{
    ureg32 CH0_ENABLE:1;       /* [0:0] Enable the core for channel 0- RW */
    ureg32 CH1_ENABLE:1;       /* [1:1] Enable the core for channel 1- RW */
    ureg32 CH2_ENABLE:1;       /* [2:2] Enable the core for channel 2- RW */
    ureg32 CH3_ENABLE:1;       /* [3:3] Enable the core for channel 3- RW */
    ureg32 EXT_DMA_ENABLE:1;   /* [4:4] External DMA enable- RW*/
    ureg32 DEC_FREE:8;         /* [12:5] Number of bit periods to detect bus free once Manchester error- RW */
    ureg32 CH0_RSP_PROT:1;     /* [13:13] For Sensor to ECU response in bidirectional communication for channel 0- RW */
    ureg32 CH1_RSP_PROT:1;     /* [14:14] For Sensor to ECU response in bidirectional communication for channel 1- RW */
    ureg32 CH2_RSP_PROT:1;     /* [15:15] For Sensor to ECU response in bidirectional communication for channel 2- RW */
    ureg32 CH3_RSP_PROT:1;     /* [16:16] For Sensor to ECU response in bidirectional communication for channel 3- RW */
    ureg32 reserved_17:15;     /* [31:17] Internal reserved */
} PSI5_CONTROL_Bits;

/* Controls the prescaler for timestamp counter register */
typedef struct
{
    ureg32 TS_PRESCALER:16;    /* [15:0] Controls the prescaler for timestamp counter, this divides output clock
                                         of prescaler, this is enabled when at least one channel is enabled- RW */
    ureg32 reserved_16:16;     /* [31:16] Internal reserved */
} PSI5_TS_PRESCALER_Bits;

/* Current timestamp register */
typedef struct
{
    ureg32 TS_CURRENT:24;  /* [23:0] This register holds current timestamp- R */
    ureg32 reserved_24:8;  /* [31:24] Internal reserved */
} PSI5_TS_CURRENT_Bits;

/* Glitch filter width register */
typedef struct
{
    ureg32 GLITCH_FILTER:8;  /* [7:0] Controls the glitch filter width, the value ranges from 0 to 255, recommended
                                      setting is 4. If set to 0, the glitch filter is turned off- RW */
    ureg32 reserved_8:24;    /* [31:8] Internal reserved */
} PSI5_GLITCH_FILTER_Bits;

/* Global interrupt enable register */
typedef struct
{
    ureg32 IRQ_CHN0:1;      /* [0:0] IRQ enable for Channel 0, Read IRQ_STATUS_CH0 to know cause of IRQ- RW */
    ureg32 IRQ_CHN1:1;      /* [1:1] IRQ enable for Channel 1, Read IRQ_STATUS_CH1 to know cause of IRQ- RW */
    ureg32 IRQ_CHN2:1;      /* [2:2] IRQ enable for Channel 2, Read IRQ_STATUS_CH2 to know cause of IRQ- RW */
    ureg32 IRQ_CHN3:1;      /* [3:3] IRQ enable for Channel 3, Read IRQ_STATUS_CH3 to know cause of IRQ- RW */
    ureg32 reserved_4:28;   /* [31:4] Internal reserved */
/* #Violation: psi5_register_h_REF_2 */
} PSI5_IRQ_ENABLE_Bits;

/* Global interrupt status register */
typedef struct
{
    ureg32 IRQ_CHN0:1;       /* [0:0] IRQ status for Channel 0, Read IRQ_STATUS_CH0 to know cause of IRQ- RW */
    ureg32 IRQ_CHN1:1;       /* [1:1] IRQ status for Channel 1, Read IRQ_STATUS_CH0 to know cause of IRQ- RW */
    ureg32 IRQ_CHN2:1;       /* [2:2] IRQ status for Channel 2, Read IRQ_STATUS_CH2 to know cause of IRQ- RW */
    ureg32 IRQ_CHN3:1;       /* [3:3] IRQ status for Channel 3, Read IRQ_STATUS_CH3 to know cause of IRQ- RW */
    ureg32 reserved_4:28;    /* [31:4] Internal reserved */
} PSI5_IRQ_STATUS_Bits;

/* Controls the transmit and receive control register for channel */
typedef struct
{
    ureg32 CTRL_COM_MODE:1;       /* [0:0] Controls communication sync mode or async mode- RW */
    ureg32 CTRL_AVBS:1;           /* [1:1] Controls  verbose for async mode- RW */
    ureg32 reserved_2:30;         /* [31:2] Internal reserved */
} PSI5_CH_TXRX_CONTROL_Bits;

/* Controls the prescaler for transmit and receive slower clock register */
typedef struct
{
    ureg32 CH_PRESCALER:16;       /* [15:0] Controls the prescaler for transmit and receive slower clock- RW */
    ureg32 reserved_16:16;        /* [31:16] Internal reserved */
} PSI5_CH_PRESCALER_Bits;

/* Controls the transmit side for channel register */
typedef struct
{
    ureg32 TX_CRC_MODE:1;     /* [0:0] Enables insert CRC by hardware or software- RW */
    ureg32 TX_BIT_STUFF:1;    /* [1:1] Enables sending bit stuffing- RW */
    ureg32 TX_START_CTRL:1;   /* [2:2] Start sequence generation control- RW */
    ureg32 TX_ENH_PROT:2;     /* [4:3] Enhanced Protocol Selection- RW */
    ureg32 TX_START_PAT:1;    /* [5:5] Start pattern when doing ECU to Sensor when TX0_TOOTH_GAP is selected- RW */
    ureg32 TX_TSYNC_MODE:1;   /* [6:6] Control sync mode -RW */
    ureg32 TX_TSYNC_EN:1;     /* [7:7] Enables sending sync generation- RW */
    ureg32 TX_TSYNC_PERIOD:8; /* [15:8] The T-sync width in internal clock (prescaler output), the value ranges from
                                        0 to 255- RW */
    ureg32 TX_ENC_GAP:8;      /* [23:16] Gap between two Sync pulse for ECU to Sensor when using ToothGap mode, the
                                         value ranges from 0 to 255- RW */
    ureg32 TX_PWM_ADD:8;      /* [31:24] Controls PWM width, the value ranges from 0 to 255- RW */
} PSI5_CH_TX_CONTROL_Bits;

/* Controls the transmit side slot register */
typedef struct
{
    ureg32 TX_SLOT_GAP:8;       /* [7:0] Controls the gap between two slots in prescaler output clock, the value
                                         ranges from 0 to 255- RW */
    ureg32 TX_SLOT_POST:8;      /* [15:8] Controls the gap between last slot and sync pulse, the value ranges
                                          from 0 to 255- RW */
    ureg32 TX_SYNC_SLOT_GAP:8;  /* [23:16] Controls the gap between sync pulse and first slot, the value ranges
                                           from 0 to 255- RW */
    ureg32 reserved_24:8;       /* [31:24] Internal reserved */
} PSI5_CH_TX_SLOT_CTRL_Bits;

/* Controls the width of each slot for channel 0 for Slot0,1,2,3 register */
typedef struct
{
    ureg32 RX_SLOT0_WIDTH:8;      /* [7:0] Width of slot0 from Start bits to Parity/CRC bits- RW */
    ureg32 RX_SLOT1_WIDTH:8;      /* [15:8] Width of slot1 from Start bits to Parity/CRC bits- RW */
    ureg32 RX_SLOT2_WIDTH:8;      /* [23:16] Width of slot2 from Start bits to Parity/CRC bits- RW */
    ureg32 RX_SLOT3_WIDTH:8;      /* [31:24] Width of slot3 from Start bits to Parity/CRC bits- RW */
} PSI5_CH_RX_SLOT_CTRL0_Bits;

/* Controls the width of each slot for channel 0 for Slot4,5 register */
typedef struct
{
    ureg32 RX_SLOT4_WIDTH:8;      /* [7:0] Width of slot4 from Start bits to Parity/CRC bits- RW */
    ureg32 RX_SLOT5_WIDTH:8;      /* [15:8] Width of slot5 from Start bits to Parity/CRC bits- RW */
    ureg32 reserved_16:16;        /* [31:16] Internal reserved */
} PSI5_CH_RX_SLOT_CTRL1_Bits;

/* Controls the receive side normal sensor data register */
typedef struct
{
    ureg32 RX_MSG0:1;   /* [0:0] Messaging bits, If set, the 2 Messaging bits are configured in slot 0- RW */
    ureg32 RX_FEC0:1;   /* [1:1] Frame Expectation Control, If set, a frame is expected for the PSI5 in slot 0- RW */
    ureg32 RX_VBS0:1;   /* [2:2] Verbose mode, message is expected in slot0 an empty frame is stored in buffer- RW */
    ureg32 RX_PROT0:1;  /* [3:3] Using CRC or parity protection for frames from Sensor to ECU for slot 0- RW */
    ureg32 RX_MSG1:1;   /* [4:4] Messaging bits, If set, the 2 Messaging bits are configured in slot 1- RW */
    ureg32 RX_FEC1:1;   /* [5:5] Frame Expectation Control, If set, a frame is expected for the PSI5 in slot 1- RW */
    ureg32 RX_VBS1:1;   /* [6:6] Verbose mode, message is expected in slot1 an empty frame is stored in buffer- RW */
    ureg32 RX_PROT1:1;  /* [7:7] Using CRC or parity protection for frames from Sensor to ECU for slot 1- RW */
    ureg32 RX_MSG2:1;   /* [8:8] Messaging bits, If set, the 2 Messaging bits are configured in slot 2- RW */
    ureg32 RX_FEC2:1;   /* [9:9] Frame Expectation Control, If set, a frame is expected for the PSI5 in slot 2- RW */
    ureg32 RX_VBS2:1;   /* [10:10] Verbose mode, message is expected in slot2 an empty frame is stored in buffer- RW */
    ureg32 RX_PROT2:1;  /* [11:11] Using CRC or parity protection for frames from Sensor to ECU for slot 2- RW */
    ureg32 RX_MSG3:1;   /* [12:12] Messaging bits, If set, the 2 Messaging bits are configured in slot 3- RW */
    ureg32 RX_FEC3:1;   /* [13:13] Frame Expectation Control, If set, a frame is expected for the PSI5 in slot 3- RW */
    ureg32 RX_VBS3:1;   /* [14:14] Verbose mode, message is expected in slot3 an empty frame is stored in buffer- RW */
    ureg32 RX_PROT3:1;  /* [15:15] Using CRC or parity protection for frames from Sensor to ECU for slot 3- RW */
    ureg32 RX_MSG4:1;   /* [16:16] Messaging bits, If set, the 2 Messaging bits are configured in slot 4- RW */
    ureg32 RX_FEC4:1;   /* [17:17] Frame Expectation Control, If set, a frame is expected for the PSI5 in slot 4- RW */
    ureg32 RX_VBS4:1;   /* [18:18] Verbose mode, message is expected in slot4 an empty frame is stored in buffer- RW */
    ureg32 RX_PROT4:1;  /* [19:19] Using CRC or parity protection for frames from Sensor to ECU for slot 4- RW */
    ureg32 RX_MSG5:1;   /* [20:20] Messaging bits, If set, the 2 Messaging bits are configured in slot 5- RW */
    ureg32 RX_FEC5:1;   /* [21:21] Frame Expectation Control, If set, a frame is expected for the PSI5 in slot 5- RW */
    ureg32 RX_VBS5:1;   /* [22:22] Verbose mode, message is expected in slot5 an empty frame is stored in buffer- RW */
    ureg32 RX_PROT5:1;  /* [23:23] Using CRC or parity protection for frames from Sensor to ECU for slot 5- RW */
    ureg32 reserved_24:8;/* [31:24] Internal reserved */
} PSI5_CH_RX_CONTROL_Bits;

/* Control threshold for interrupt register */
typedef struct
{
    ureg32 TX_FIFO_THRESHOLD:8;   /* [7:0] Transmit Data FIFO threshold for read, the value Maximum is 4- RW */
    ureg32 RX_FIFO_THRESHOLD:8;   /* [15:8] Receive Data FIFO threshold for read, the value Maximum is 96- RW */
    ureg32 reserved_16:16;        /* [31:16] Internal reserved */
} PSI5_CH_FIFO_THRESHOLD_Bits;

/* Flush the FIFO register */
typedef struct
{
    ureg32 TX_FIFO_FLUSH:1;       /* [0:0] FLUSH Transmit Data FIFO- RW */
    ureg32 RX_FIFO_FLUSH:1;       /* [1:1] FLUSH Receive Data FIFO- RW */
    ureg32 reserved_2:30;         /* [31:2] Internal reserved */
} PSI5_CH_FIFO_FLUSH_Bits;

/* Transmit data FIFO(write) register, control data */
typedef struct
{
    ureg32 TX_TYPE:1;             /* [0:0] This field holds type of data- W */
    ureg32 TX_SADDR:3;            /* [3:1] This field holds the sensor address- W */
    ureg32 TX_CFG:1;              /* [4:4] This field holds the configuration bit- W */
    ureg32 TX_FC:3;               /* [7:5] This field holds the function code- W */
    ureg32 TX_BLEN:6;             /* [13:8] This field holds the number of bits to transmit- W */
    ureg32 reserved_14:18;        /* [31:14] Internal reserved */
} PSI5_CH_TX_FIFO_CONTROL_Bits;

/* Transmit data FIFO(write) register, payload data */
typedef struct
{
    ureg32 TX_TYPE:1;             /* [0:0] This field hold type of data- W */
    ureg32 TX_PAYLOAD:30;         /* [30:1] This field holds to transmit data- W */
    ureg32 reserved_31:1;         /* [31:31] Internal reserved */
} PSI5_CH_TX_FIFO_PAYLOAD_Bits;

/* Receive control data FIFO(read) register, control data */
typedef struct
{
    ureg32 RX_TYPE:2;     /* [1:0] Hold type of data- R */
    ureg32 RX_LEN:6;      /* [7:2] Holds the number of bits- R */
    ureg32 RX_SLOT:3;     /* [10:8] Holds the slot counter value- R */
    ureg32 RX_MSG:2;      /* [12:11] Holds the message bits- R */
    ureg32 RX_TIE:1;      /* [13:13] The SOF and the EOF of a frame are received in different time slots- R */
    ureg32 RX_NBI:1;      /* [14:14] Last frame received less bits than expected but no manchester error- R */
    ureg32 RX_MEI:1;      /* [15:15] Set if a manchester error occurred- R */
    ureg32 RX_NFI:1;      /* [16:16] No Frame Received Flag- R */
    ureg32 reserved_17:15;/* [31:17] Internal reserved */
} PSI5_CH_RX_FIFO_CONTROL_Bits;

/* Receive timestamp data FIFO(read) register, timestamp data */
typedef struct
{
    ureg32 RX_TYPE:2;        /* [1:0] Hold type of data- R */
    ureg32 RX_TIMESTAMP:24;  /* [25:2] This field holds the number of bits timestamp data- R */
    ureg32 reserved_26:6;    /* [31:26] Internal reserved */
} PSI5_CH_RX_FIFO_TIMESTAMP_Bits;

/* Receive payload data FIFO(read) register, payload data */
typedef struct
{
    ureg32 RX_TYPE:2;     /* [1:0] Hold type of data- R */
    ureg32 RX_PAYLOAD:30; /* [31:2] This field holds the number of bits payload data- R */
} PSI5_CH_RX_FIFO_PAYLOAD_Bits;

/* Channel interrupt enable register */
typedef struct
{
    ureg32 IRQ_CH_TX_DONE:1;            /* [0:0] Interrupt for done transmission of command/packet- RW */
    ureg32 IRQ_CH_RX_READY:1;           /* [1:1] Interrupt for ready reception of command/packet- RW */
    ureg32 IRQ_CH_TX_CMD_ERR:1;         /* [2:2] Interrupt when bit 0 of TX_FIFO is set inverse- RW */
    ureg32 IRQ_CH_MEI_ERR:1;            /* [3:3] Interrupt for Messaging Bits with Manchester coding Error- RW */
    ureg32 IRQ_CH_CRC_ERR:1;            /* [4:4] Interrupt for Checksum error- RW */
    ureg32 IRQ_CH_TEI_ERR:1;            /* [5:5] Interrupt for Frame not sent in expected time slot- RW */
    ureg32 IRQ_CH_START_ERR:1;          /* [6:6] Interrupt for start bit errors- RW */
    ureg32 IRQ_CH_SEI_ERR:1;            /* [7:7] Interrupt for sync timing error- RW */
    ureg32 IRQ_CH_TX_FIFO_TT:1;         /* [8:8] Interrupt for Transmit Data FIFO threshold reached on read- RW */
    ureg32 IRQ_CH_TX_FIFO_UR:1;         /* [9:9] Interrupt for Transmit Data FIFO underrun- RW */
    ureg32 IRQ_CH_TX_FIFO_OR:1;         /* [10:10] Interrupt for Transmit Data FIFO overrun- RW */
    ureg32 IRQ_CH_TX_FIFO_FULL:1;       /* [11:11] Interrupt for Transmit Data FIFO full- RW */
    ureg32 IRQ_CH_TX_FIFO_EMPTY:1;      /* [12:12] Interrupt for Transmit Data FIFO empty- RW */
    ureg32 IRQ_CH_RX_FIFO_TT:1;         /* [13:13] Interrupt for Receive Data FIFO threshold reached on read- RW */
    ureg32 IRQ_CH_RX_FIFO_UR:1;         /* [14:14] Interrupt for Receive Data FIFO underrun- RW */
    ureg32 IRQ_CH_RX_FIFO_OR:1;         /* [15:15] Interrupt for Receive Data FIFO overrun- RW */
    ureg32 IRQ_CH_RX_FIFO_FULL:1;       /* [16:16] Interrupt for Receive Data FIFO full- RW */
    ureg32 IRQ_CH_RX_FIFO_EMPTY:1;      /* [17:17] Interrupt for Receive Data FIFO empty- RW */
    ureg32 reserved_18:14;              /* [31:18] Internal reserved */
} PSI5_CH_IRQ_ENABLE_Bits;

/* Channel interrupt status register */
typedef struct
{
    ureg32 IRQ_CH_TX_DONE:1;            /* [0:0] Interrupt for done transmission of command/packet- RW */
    ureg32 IRQ_CH_RX_READY:1;           /* [1:1] Interrupt for ready reception of command/packet- RW */
    ureg32 IRQ_CH_TX_CMD_ERR:1;         /* [2:2] Interrupt when bit 0 of TX_FIFO is set inverse- RW */
    ureg32 IRQ_CH_MEI_ERR:1;            /* [3:3] Interrupt for Messaging Bits with Manchester coding Error- RW */
    ureg32 IRQ_CH_CRC_ERR:1;            /* [4:4] Interrupt for Checksum error- RW */
    ureg32 IRQ_CH_TEI_ERR:1;            /* [5:5] Interrupt for Frame not sent in expected time slot- RW */
    ureg32 IRQ_CH_START_ERR:1;          /* [6:6] Interrupt for start bit errors- RW */
    ureg32 IRQ_CH_SEI_ERR:1;            /* [7:7] Interrupt for sync timing error- RW */
    ureg32 IRQ_CH_TX_FIFO_TT:1;         /* [8:8] Interrupt for Transmit Data FIFO threshold reached on read- RW */
    ureg32 IRQ_CH_TX_FIFO_UR:1;         /* [9:9] Interrupt for Transmit Data FIFO underrun- RW */
    ureg32 IRQ_CH_TX_FIFO_OR:1;         /* [10:10] Interrupt for Transmit Data FIFO overrun- RW */
    ureg32 IRQ_CH_TX_FIFO_FULL:1;       /* [11:11] Interrupt for Transmit Data FIFO full- RW */
    ureg32 IRQ_CH_TX_FIFO_EMPTY:1;      /* [12:12] Interrupt for Transmit Data FIFO empty- RW */
    ureg32 IRQ_CH_RX_FIFO_TT:1;         /* [13:13] Interrupt for Receive Data FIFO threshold reached on read- RW */
    ureg32 IRQ_CH_RX_FIFO_UR:1;         /* [14:14] Interrupt for Receive Data FIFO underrun- RW */
    ureg32 IRQ_CH_RX_FIFO_OR:1;         /* [15:15] Interrupt for Receive Data FIFO overrun- RW */
    ureg32 IRQ_CH_RX_FIFO_FULL:1;       /* [16:16] Interrupt for Receive Data FIFO full- RW */
    ureg32 IRQ_CH_RX_FIFO_EMPTY:1;      /* [17:17] Interrupt for Receive Data FIFO empty- RW */
    ureg32 reserved_18:14;              /* [31:18] Internal reserved */
} PSI5_CH_IRQ_STATUS_Bits;

/**********************************************************************************************************************
 *                                              PSI5 Register Union Definitions
 *********************************************************************************************************************/
/* Control register */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CONTROL_Bits B;          /* Bit-field access */
} PSI5_CONTROL;

/* Prescaler register for timestamp */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_TS_PRESCALER_Bits B;     /* Bit-field access */
} PSI5_TS_PRESCALER;

/* Current timestamp register */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_TS_CURRENT_Bits B;       /* Bit-field access */
} PSI5_TS_CURRENT;

/* Glitch filter register */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_GLITCH_FILTER_Bits B;    /* Bitf-ield access */
} PSI5_GLITCH_FILTER;

/* Interrupt status register */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_IRQ_STATUS_Bits B;       /* Bit-field access */
} PSI5_IRQ_STATUS;

/* Transmit and receive control register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_TXRX_CONTROL_Bits B;  /* Bit-field access */
} PSI5_CH_TXRX_CONTROL;

/* Prescaler register for Channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_PRESCALER_Bits B;     /* Bit-field access */
} PSI5_CH_PRESCALER;

/* Transmit control register for Channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_TX_CONTROL_Bits B;    /* Bit-field access */
} PSI5_CH_TX_CONTROL;

/* Transmit slot control register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_TX_SLOT_CTRL_Bits B;  /* Bit-field access */
} PSI5_CH_TX_SLOT_CTRL;

/* Receive slot control 0 register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_RX_SLOT_CTRL0_Bits B; /* Bit-field access */
} PSI5_CH_RX_SLOT_CTRL0;

/* Receive slot control 1 register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_RX_SLOT_CTRL1_Bits B; /* Bit-field access */
} PSI5_CH_RX_SLOT_CTRL1;

/* Receive control register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_RX_CONTROL_Bits B;    /* Bit-field access */
} PSI5_CH_RX_CONTROL;

/* FIFO threshold register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                      /* Unsigned access */
    PSI5_CH_FIFO_THRESHOLD_Bits B; /* Bit-field access */
} PSI5_CH_FIFO_THRESHOLD;

/* FIFO flush register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_FIFO_FLUSH_Bits B;    /* Bit-field access */
} PSI5_CH_FIFO_FLUSH;

/* Transmit FIFO register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                        /* Unsigned access */
    PSI5_CH_TX_FIFO_CONTROL_Bits B1; /* Bit-field1 access */
    PSI5_CH_TX_FIFO_PAYLOAD_Bits B2; /* Bit-field2 access */
} PSI5_CH_TX_FIFO;

/* Receive FIFO register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                         /* Unsigned access */
    PSI5_CH_RX_FIFO_CONTROL_Bits B1;  /* Bit-field1 access */
    PSI5_CH_RX_FIFO_TIMESTAMP_Bits B2;/* Bit-field2 access */
    PSI5_CH_RX_FIFO_PAYLOAD_Bits B3;  /* Bit-field3 access */
} PSI5_CH_RX_FIFO;

/* Interrupt enable register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_IRQ_ENABLE_Bits B;    /* Bit-field access */
} PSI5_CH_IRQ_ENABLE;

/* Interrupt status Register for channel */
typedef union
/* #Violation: psi5_register_h_REF_1 */
{
    uint32 U;                     /* Unsigned access */
    PSI5_CH_IRQ_STATUS_Bits B;    /* Bit-field access */
} PSI5_CH_IRQ_STATUS;

/**********************************************************************************************************************
 *                                       PSI5 Register Structure
 *********************************************************************************************************************/
/* Channel object register group */
typedef volatile struct
{
    PSI5_CH_TXRX_CONTROL      CH_TXRX_CONTROL;    /* 0x18-6,  */
    PSI5_CH_PRESCALER         CH_PRESCALER;       /* 0x1C-7,  */
    PSI5_CH_TX_CONTROL        CH_TX_CONTROL;      /* 0x20-8,  */
    PSI5_CH_TX_SLOT_CTRL      CH_TX_SLOT_CTRL;    /* 0x24-9,  */
    PSI5_CH_RX_SLOT_CTRL0     CH_RX_SLOT_CTRL0;   /* 0x28-10, */
    PSI5_CH_RX_SLOT_CTRL1     CH_RX_SLOT_CTRL1;   /* 0x2C-11, */
    PSI5_CH_RX_CONTROL        CH_RX_CONTROL;      /* 0x30-12, */
    PSI5_CH_FIFO_THRESHOLD    CH_FIFO_THRESHOLD;  /* 0x34-13, */
    PSI5_CH_FIFO_FLUSH        CH_FIFO_FLUSH;      /* 0x38-14, */
    PSI5_CH_TX_FIFO           CH_TX_FIFO;         /* 0x3C-15, */
    PSI5_CH_RX_FIFO           CH_RX_FIFO;         /* 0x40-16  */
    PSI5_CH_IRQ_ENABLE        CH_IRQ_ENABLE;      /* 0x44-17, */
    PSI5_CH_IRQ_STATUS        CH_IRQ_STATUS;      /* 0x48-18, */
} PSI5_CH;

/* PSI5 module object register group */
typedef volatile struct
{
    PSI5_CONTROL              CONTROL;            /* 0x00-0 */
    PSI5_TS_PRESCALER         TS_PRESCALER;       /* 0x04-1 */
    PSI5_TS_CURRENT           TS_CURRENT;         /* 0x08-2 */
    PSI5_GLITCH_FILTER        GLITCH_FILTER;      /* 0x0C-3 */
    uint8                     RESERVED_10[4];     /* 0x10-4 */
    PSI5_IRQ_STATUS           IRQ_STATUS;         /* 0x14-5 */
    PSI5_CH                   CH[4];              /* Channel object register group*/
} PSI5_MODULE;



#endif /* PSI5_REGISTER_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

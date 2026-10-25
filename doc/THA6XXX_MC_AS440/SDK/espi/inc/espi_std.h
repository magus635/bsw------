/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    espi_std.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: ESPI standard driver header file.This file contains function prototypes for ESPI standard driver.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#espi_std_h_REF_1:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*
*/
#ifndef ESPI_STD_H_
#define ESPI_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "espi_register.h"
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
/* ESPI master data mode enum defines */
typedef enum
{
    ESPI_MASTER_MODE_SINGLESHORT = 0U, /* Short Mode  */
    ESPI_MASTER_MODE_SINGLELONG,       /* Long Mode */
    ESPI_MASTER_MODE_CONTINUOUSSHORT,  /* Short Continuous Mode */
    ESPI_MASTER_MODE_CONTINUOUSLONG,   /* Long Continuous Mode */
    ESPI_MASTER_MODE_XXL,              /* Extra Large Data(XXL) Mode */
    ESPI_MASTER_MODE_MOVECOUNTER       /* Move counter Mode */
} Espi_Master_DataMode;

/* ESPI work mode enum defines */
typedef enum
{
    ESPI_MODE_MASTER = 0U, /* Master mode */
    ESPI_MODE_SLAVE = 2U   /* Slave mode */
/* #Violation: espi_std_h_REF_1 */
} Espi_WorkMode;

/* ESPI transmit/receive data buffer width enum */
typedef enum
{
    ESPI_DATABUFFER_8BITS = 1U,  /* Transmit/receive data buffer width is 8 bits (1 byte)   */
    ESPI_DATABUFFER_16BITS = 2U, /* Transmit/receive data buffer width is 16 bits (2 bytes) */
    ESPI_DATABUFFER_32BITS = 4U  /* Transmit/receive data buffer width is 32 bits (4 bytes) */
} Espi_DataBufferWidth;

/* ESPI transmit FIFO interrupt threshold enum */
typedef enum
{
    ESPI_TXFIFO_THRESHOLD_ONE = 0U, /* TxFifo Threshold is 1 */
    ESPI_TXFIFO_THRESHOLD_TWO,      /* TxFifo Threshold is 2 */
    ESPI_TXFIFO_THRESHOLD_THREE,    /* TxFifo Threshold is 3 */
    ESPI_TXFIFO_THRESHOLD_FOUR,     /* TxFifo Threshold is 4 */
    ESPI_TXFIFO_THRESHOLD_FIVE,     /* TxFifo Threshold is 5 */
    ESPI_TXFIFO_THRESHOLD_SIX,      /* TxFifo Threshold is 6 */
    ESPI_TXFIFO_THRESHOLD_SEVEN,    /* TxFifo Threshold is 7 */
    ESPI_TXFIFO_THRESHOLD_EIGHT,    /* TxFifo Threshold is 8 */
    ESPI_TXFIFO_THRESHOLD_NINE,     /* TxFifo Threshold is 9 */
    ESPI_TXFIFO_THRESHOLD_TEN,      /* TxFifo Threshold is 10 */
    ESPI_TXFIFO_THRESHOLD_ELEVEN,   /* TxFifo Threshold is 11 */
    ESPI_TXFIFO_THRESHOLD_TWELVE,   /* TxFifo Threshold is 12 */
    ESPI_TXFIFO_THRESHOLD_THIRTEEN, /* TxFifo Threshold is 13 */
    ESPI_TXFIFO_THRESHOLD_FOURTEEN, /* TxFifo Threshold is 14 */
    ESPI_TXFIFO_THRESHOLD_FIFTEEN,  /* TxFifo Threshold is 15 */
    ESPI_TXFIFO_THRESHOLD_SIXTEEN   /* TxFifo Threshold is 16 */
} Espi_TxFifo_Threshold;

/* ESPI receive FIFO interrupt threshold enum */
typedef enum
{
    ESPI_RXFIFO_THRESHOLD_ZERO = 0U, /* RxFifo Threshold is 0 */
    ESPI_RXFIFO_THRESHOLD_ONE,       /* RxFifo Threshold is 1 */
    ESPI_RXFIFO_THRESHOLD_TWO,       /* RxFifo Threshold is 2 */
    ESPI_RXFIFO_THRESHOLD_THREE,     /* RxFifo Threshold is 3 */
    ESPI_RXFIFO_THRESHOLD_FOUR,      /* RxFifo Threshold is 4 */
    ESPI_RXFIFO_THRESHOLD_FIVE,      /* RxFifo Threshold is 5 */
    ESPI_RXFIFO_THRESHOLD_SIX,       /* RxFifo Threshold is 6 */
    ESPI_RXFIFO_THRESHOLD_SEVEN,     /* RxFifo Threshold is 7 */
    ESPI_RXFIFO_THRESHOLD_EIGHT,     /* RxFifo Threshold is 8 */
    ESPI_RXFIFO_THRESHOLD_NINE,      /* RxFifo Threshold is 9 */
    ESPI_RXFIFO_THRESHOLD_TEN,       /* RxFifo Threshold is 10 */
    ESPI_RXFIFO_THRESHOLD_ELEVEN,    /* RxFifo Threshold is 11 */
    ESPI_RXFIFO_THRESHOLD_TWELVE,    /* RxFifo Threshold is 12 */
    ESPI_RXFIFO_THRESHOLD_THIRTEEN,  /* RxFifo Threshold is 13 */
    ESPI_RXFIFO_THRESHOLD_FOURTEEN,  /* RxFifo Threshold is 14 */
    ESPI_RXFIFO_THRESHOLD_FIFTEEN    /* RxFifo Threshold is 15 */
} Espi_RxFifo_Threshold;

/*ESPI FIFO move mode enum */
typedef enum
{
    ESPI_FIFOMODE_COMBINED = 0U, /* Combined move Mode */
    ESPI_FIFOMODE_SINGLE,        /* Single move Mode */
    ESPI_FIFOMODE_BATCH          /* Batch move Mode */
} Espi_FifoMode;

/* ESPI parity mode enum */
typedef enum
{
    ESPI_PARITYMODE_EVEN = 0U, /* Even Parity Mode */
    ESPI_PARITYMODE_ODD,       /* Odd Parity Mode */
    ESPI_PARITYMODE_NONE       /* None Parity Mode */
} Espi_ParityMode;

/*ESPI data length enum */
typedef enum
{
    ESPI_DATAWIDTH_2 = 1U, /* Data length is 2 bits or 2 bytes */
    ESPI_DATAWIDTH_3,      /* Data length is 3 bits or 3 bytes */
    ESPI_DATAWIDTH_4,      /* Data length is 4 bits or 4 bytes */
    ESPI_DATAWIDTH_5,      /* Data length is 5 bits or 5 bytes */
    ESPI_DATAWIDTH_6,      /* Data length is 6 bits or 6 bytes */
    ESPI_DATAWIDTH_7,      /* Data length is 7 bits or 7 bytes */
    ESPI_DATAWIDTH_8,      /* Data length is 8 bits or 8 bytes */
    ESPI_DATAWIDTH_9,      /* Data length is 9 bits or 9 bytes */
    ESPI_DATAWIDTH_10,     /* Data length is 10 bits or 10 bytes */
    ESPI_DATAWIDTH_11,     /* Data length is 11 bits or 11 bytes */
    ESPI_DATAWIDTH_12,     /* Data length is 12 bits or 12 bytes */
    ESPI_DATAWIDTH_13,     /* Data length is 13 bits or 13 bytes */
    ESPI_DATAWIDTH_14,     /* Data length is 14 bits or 14 bytes */
    ESPI_DATAWIDTH_15,     /* Data length is 15 bits or 15 bytes */
    ESPI_DATAWIDTH_16,     /* Data length is 16 bits or 16 bytes */
    ESPI_DATAWIDTH_17,     /* Data length is 17 bits or 17 bytes */
    ESPI_DATAWIDTH_18,     /* Data length is 18 bits or 18 bytes */
    ESPI_DATAWIDTH_19,     /* Data length is 19 bits or 19 bytes */
    ESPI_DATAWIDTH_20,     /* Data length is 20 bits or 20 bytes */
    ESPI_DATAWIDTH_21,     /* Data length is 21 bits or 21 bytes */
    ESPI_DATAWIDTH_22,     /* Data length is 22 bits or 22 bytes */
    ESPI_DATAWIDTH_23,     /* Data length is 23 bits or 23 bytes */
    ESPI_DATAWIDTH_24,     /* Data length is 24 bits or 24 bytes */
    ESPI_DATAWIDTH_25,     /* Data length is 25 bits or 25 bytes */
    ESPI_DATAWIDTH_26,     /* Data length is 26 bits or 26 bytes */
    ESPI_DATAWIDTH_27,     /* Data length is 27 bits or 27 bytes */
    ESPI_DATAWIDTH_28,     /* Data length is 28 bits or 28 bytes */
    ESPI_DATAWIDTH_29,     /* Data length is 29 bits or 29 bytes */
    ESPI_DATAWIDTH_30,     /* Data length is 30 bits or 30 bytes */
    ESPI_DATAWIDTH_31,     /* Data length is 31 bits or 31 bytes */
    ESPI_DATAWIDTH_32      /* Data length is 32 bits or 32 bytes */
} Espi_DataWidth;

/* ESPI data length unit enum */
typedef enum
{
    ESPI_DATAWIDTH_UNIT_BIT = 0U, /* Data length unit is Bit */
    ESPI_DATAWIDTH_UNIT_BYTE      /* Data length unit is Byte */
/* #Violation: espi_std_h_REF_1 */
} Espi_DataWidth_Unit;

/* ESPI bit order enum */
typedef enum
{
    ESPI_BITORDER_LSB = 0U, /* Least Significant Bit (LSB) first */
    ESPI_BITORDER_MSB       /* Most Significant Bit (MSB) first */
} Espi_BitOrder;

/* ESPI last word enum */
typedef enum
{
    ESPI_NOTLASTWORD = 0U, /* Not last word */
    ESPI_LASTWORD          /* last word */
/* #Violation: espi_std_h_REF_1 */
} Espi_LastWord;

/* ESPI phase enum */
typedef enum
{
    ESPI_PHASE_WAIT = 0U,  /* wait phase */
    ESPI_PHASE_IDLEA,      /* idleA phase */
    ESPI_PHASE_IDLEB,      /* idleB phase */
    ESPI_PHASE_LEAD,       /* lead phase */
    ESPI_PHASE_DATA,       /* data phase */
    ESPI_PHASE_TRAIL,      /* trail phase */
    ESPI_PHASE_EXPECT,     /* expect phase */
    ESPI_PHASE_LEADSTROBE, /* lead strobe phase */
    ESPI_PHASE_TRAILSTROBE /* trail strobe phase */
/* #Violation: espi_std_h_REF_1 */
} Espi_Phase;

/*  Expect Timeout Value */
typedef enum
{
    ESPI_EXPECTTIMEOUT_64 = 0,  /* EXPECT phase timeout value is 64 */
    ESPI_EXPECTTIMEOUT_128,     /* EXPECT phase timeout value is 128 */
    ESPI_EXPECTTIMEOUT_256,     /* EXPECT phase timeout value is 256 */
    ESPI_EXPECTTIMEOUT_512,     /* EXPECT phase timeout value is 512 */
    ESPI_EXPECTTIMEOUT_1024,    /* EXPECT phase timeout value is 1024 */
    ESPI_EXPECTTIMEOUT_2048,    /* EXPECT phase timeout value is 2048 */
    ESPI_EXPECTTIMEOUT_4096,    /* EXPECT phase timeout value is 4096 */
    ESPI_EXPECTTIMEOUT_8192,    /* EXPECT phase timeout value is 8192 */
    ESPI_EXPECTTIMEOUT_16384,   /* EXPECT phase timeout value is 16384 */
    ESPI_EXPECTTIMEOUT_32768,   /* EXPECT phase timeout value is 32768 */
    ESPI_EXPECTTIMEOUT_65536,   /* EXPECT phase timeout value is 65536 */
    ESPI_EXPECTTIMEOUT_131072,  /* EXPECT phase timeout value is 131072 */
    ESPI_EXPECTTIMEOUT_262144,  /* EXPECT phase timeout value is 262144 */
    ESPI_EXPECTTIMEOUT_524288,  /* EXPECT phase timeout value is 524288 */
    ESPI_EXPECTTIMEOUT_1048576, /* EXPECT phase timeout value is 1048576 */
    ESPI_EXPECTTIMEOUT_2097152  /* EXPECT phase timeout value is 2097152 */
} Espi_ExpectTimeoutValue;

/* ESPI clock polarity enum */
typedef enum
{
    ESPI_CLOCKPOLARITY_IDLE_LOW = 0U, /* Idle clock line is low */
    ESPI_CLOCKPOLARITY_IDLE_HIGH      /* Idle clock line is high */
} Espi_ClockPolarity;

/* ESPI clock phase enum */
typedef enum
{
    ESPI_CLOCKPHASE_FIRSTSAMPLE = 0U, /* The first clock edge is sampled */
    ESPI_CLOCKPHASE_SECONDSAMPLE      /* The second clock edge is sampled */
} Espi_ClockPhase;

/* ESPI active output level enum */
typedef enum
{
    ESPI_SLSOOUTPUT_LEVEL_LOW = 0U, /* Active Output Level for the SLSO is low */
    ESPI_SLSOOUTPUT_LEVEL_HIGH      /* Active Output Level for the SLSO is high */
} Espi_ActiveOutputLevel;

/* Delay prescaler coefficient value enum */
typedef enum
{
    ESPI_DELAY_PRESCALER_1 = 0,     /* espi delay prescaler 1 */
    ESPI_DELAY_PRESCALER_4,         /* espi delay prescaler 4 */
    ESPI_DELAY_PRESCALER_16,        /* espi delay prescaler 16 */
    ESPI_DELAY_PRESCALER_64,        /* espi delay prescaler 64 */
    ESPI_DELAY_PRESCALER_256,       /* espi delay prescaler 256 */
    ESPI_DELAY_PRESCALER_1024,      /* espi delay prescaler 1024 */
    ESPI_DELAY_PRESCALER_4096,      /* espi delay prescaler 4096 */
    ESPI_DELAY_PRESCALER_16384      /* espi delay prescaler 16384 */
} Espi_DelayPrescaler;

/* Delay unit value enum */
typedef enum
{
    ESPI_DELAY_UNIT_1 = 0, /* espi delay unit value 1 */
    ESPI_DELAY_UNIT_2,     /* espi delay unit value 2 */
    ESPI_DELAY_UNIT_3,     /* espi delay unit value 3 */
    ESPI_DELAY_UNIT_4,     /* espi delay unit value 4 */
    ESPI_DELAY_UNIT_5,     /* espi delay unit value 5 */
    ESPI_DELAY_UNIT_6,     /* espi delay unit value 6 */
    ESPI_DELAY_UNIT_7,     /* espi delay unit value 7 */
    ESPI_DELAY_UNIT_8      /* espi delay unit value 8 */
} Espi_DelayUnit;

/* ESPI baud rate parameter A enum */
typedef enum
{
    ESPI_PARAMETER_A_ONE_UNIT = 1U, /* Baud-rate parameter A one units */
    ESPI_PARAMETER_A_TWO_UNITS,     /* Baud-rate parameter A two units */
    ESPI_PARAMETER_A_THREE_UNITS,   /* Baud-rate parameter A three units */
    ESPI_PARAMETER_A_FOUR_UNITS     /* Baud-rate parameter A four units */
} Espi_Parameter_A;

/* ESPI baud rate parameter B enum */
typedef enum
{
    ESPI_PARAMETER_B_NONE = 0U,  /* No baud rate parameter B */
    ESPI_PARAMETER_B_ONE_UNIT,   /* Baud-rate parameter B one units */
    ESPI_PARAMETER_B_TWO_UNITS,  /* Baud-rate parameter B two units */
    ESPI_PARAMETER_B_THREE_UNITS /* Baud-rate parameter B three units */
} Espi_Parameter_B;

/* ESPI baud rate parameter C enum */
typedef enum
{
    ESPI_PARAMETER_C_NONE = 0U,  /* No baud rate parameter C */
    ESPI_PARAMETER_C_ONE_UNIT,   /* Baud-rate parameter C one units */
    ESPI_PARAMETER_C_TWO_UNITS,  /* Baud-rate parameter C two units */
    ESPI_PARAMETER_C_THREE_UNITS /* Baud-rate parameter C three units */
} Espi_Parameter_C;

/* ESPI channel ID enum */
typedef enum
{
    ESPI_CS_CHANNEL_ID_0 = 0U, /* CS Channel 0 */
    ESPI_CS_CHANNEL_ID_1,      /* CS Channel 1 */
    ESPI_CS_CHANNEL_ID_2,      /* CS Channel 2 */
    ESPI_CS_CHANNEL_ID_3,      /* CS Channel 3 */
    ESPI_CS_CHANNEL_ID_4,      /* CS Channel 4 */
    ESPI_CS_CHANNEL_ID_5,      /* CS Channel 5 */
    ESPI_CS_CHANNEL_ID_6,      /* CS Channel 6 */
    ESPI_CS_CHANNEL_ID_7,      /* CS Channel 7 */
    ESPI_CS_CHANNEL_ID_8,      /* CS Channel 8 */
    ESPI_CS_CHANNEL_ID_9,      /* CS Channel 9 */
    ESPI_CS_CHANNEL_ID_10,     /* CS Channel 10 */
    ESPI_CS_CHANNEL_ID_11,     /* CS Channel 11 */
    ESPI_CS_CHANNEL_ID_12,     /* CS Channel 12 */
    ESPI_CS_CHANNEL_ID_13,     /* CS Channel 13 */
    ESPI_CS_CHANNEL_ID_14,     /* CS Channel 14 */
    ESPI_CS_CHANNEL_ID_15      /* CS Channel 15 */
} Espi_Cs_ChannelId;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* The structure of Initialization for baudRate */
typedef struct
{
    Espi_Parameter_A baudrateParameterA; /* baud rate parameter A */
    Espi_Parameter_B baudrateParameterB; /* baud rate parameter B */
    Espi_Parameter_C baudrateParameterC; /* baud rate parameter C */
    uint8 baudrateParameterQ;            /* baud rate parameter Q, the value should >= 1 */
} Espi_BaudRate;

/* The structure of specifies the phase delay time configuration for an ESPI device.*/
typedef struct
{
    Espi_DelayPrescaler delayTimePrescalercoEfficient; /* Prescaler fot the Delay */
    Espi_DelayUnit delayTimePrescalerUnit;             /* Delay Length */
} Espi_PhaseDelayTime;

/* The structure of specifies the phase delay */
typedef struct
{
    Espi_PhaseDelayTime trailDelayTime;   /* Trail delay */
    Espi_PhaseDelayTime leadingDelayTime; /* Leading delay */
    Espi_PhaseDelayTime idleDelayTime;    /* Ldle delay */
} Espi_PhaseDelay;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function: Espi_Register_ReadBack_Check
 * Description: espi register write check
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:     state: Original state.
 *            expect: The value expected to be written.
 *            value: The value actually written.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2025/05/14   01358     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Espi_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect);

/**********************************************************************************************************************
 * Function:     Espi_Std_ReadReceiveFifo
 * Description:  This function read data from the receive FIFO of the ESPI module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: Pointer to the ESPI module
 * Inout:        None
 * Output:       None
 * Return:       uint32: type data read from the receive FIFO
 * Others:       The function checks whether the receive FIFO is empty. If not, it reads the data and returns it.
 * History:
 *  Date          Author    Modified
 *  2023/06/02    01030     Created
 *  2023/10/17    01208     Modify
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Espi_Std_ReadReceiveFifo(const ESPI_MODULE *const pEspi);

/**********************************************************************************************************************
 * Function:     Espi_Std_WriteTransferFifo
 * Description:  This function write data to the transfer FIFO of the ESPI module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: Pointer to the ESPI module
 *               data: Data to be written to the transfer FIFO
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       This is an inline function, which writes data to the transfer FIFO of the ESPI module.
 * History:
 *  Date          Author    Modified
 *  2023/06/02    01030     Created
 *  2023/10/17    01208     Modify
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Espi_Std_WriteTransferFifo(ESPI_MODULE *const pEspi, uint32 data);

/**********************************************************************************************************************
 * Function:     Espi_Std_InitTxFifo
 * Description:  Initialize TXFIFO
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: pointer to the ESPI master module
 *               txFifoMode: TXFIFO mode
 *               txFifoThreshold: TXFIFO threshold
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * History:
 * Others:
 *  Date         Author   Modified
 *  2023/10/10   01208    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Espi_Std_InitTxFifo(ESPI_MODULE *const pEspi, Espi_FifoMode txFifoMode, Espi_TxFifo_Threshold txFifoThreshold);

/**********************************************************************************************************************
 * Function:     Espi_Std_InitRxFifo
 * Description:  Initialize RXFIFO
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: pointer to the ESPI master module
 *               rxFifoMode: RXFIFO mode
 *               rxFifoThreshold: RXFIFO threshold
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * History:
 * Others:
 *  Date         Author   Modified
 *  2023/10/10   01208    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Espi_Std_InitRxFifo(ESPI_MODULE *const pEspi, Espi_FifoMode rxFifoMode, Espi_RxFifo_Threshold rxFifoThreshold);

/**********************************************************************************************************************
 * Function:     Espi_Std_InitExpectTimeoutThreshold
 * Description:  Initialize the ESPI module expect phase timeout threshold
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: pointer to the ESPI master module
 *               expectTimeoutThreshold: expect phase timeout threshold
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author   Modified
 *  2023/10/10   01208    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Espi_Std_InitExpectTimeoutThreshold(ESPI_MODULE *const pEspi, Espi_ExpectTimeoutValue expectTimeoutThreshold);

/**********************************************************************************************************************
 * Function:     Espi_Std_EnableMoveCounterMode
 * Description:  Initialize the ESPI module Move Counter Mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: pointer to the ESPI master module
 *               enable: enable or disable MV Counter Mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * History:
 * Others:
 *  Date         Author   Modified
 *  2024/04/19   01208    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Espi_Std_EnableMoveCounterMode(ESPI_MODULE *const pEspi, boolean enable);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define SPI_START_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"

#define ESPI_REG_CHECK
#if defined(ESPI_REG_CHECK)
LOCAL_FORCEINLINE boolean Espi_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Espi_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

LOCAL_FORCEINLINE uint32 Espi_Std_ReadReceiveFifo(const ESPI_MODULE *const pEspi)
{
    uint32 data;
    data = pEspi->RDR.U;
    return data;
}

LOCAL_FORCEINLINE void Espi_Std_WriteTransferFifo(ESPI_MODULE *const pEspi, uint32 data)
{
    pEspi->DATAENTRY[0].U = data;
}

LOCAL_FORCEINLINE boolean Espi_Std_InitTxFifo(ESPI_MODULE *const pEspi, Espi_FifoMode txFifoMode, Espi_TxFifo_Threshold txFifoThreshold)
{
    boolean ret;
    ret = TRUE;
    /* Set TX FIFO mode */
    pEspi->GNRCON1.B.TXFM = (uint32)txFifoMode;
    ret &= Espi_Register_ReadBack_Check(ret, pEspi->GNRCON1.B.TXFM, (uint32)txFifoMode);
    /* Set TX FIFO threshold */
    pEspi->FIFOTHRESHOLD.B.TXTHRESHOLD = (uint32)txFifoThreshold;
    ret &= Espi_Register_ReadBack_Check(ret, pEspi->FIFOTHRESHOLD.B.TXTHRESHOLD, (uint32)txFifoThreshold);

    return ret;
}

LOCAL_FORCEINLINE boolean Espi_Std_InitRxFifo(ESPI_MODULE *const pEspi, Espi_FifoMode rxFifoMode, Espi_RxFifo_Threshold rxFifoThreshold)
{
    boolean ret;
    ret = TRUE;
    /* Set RX FIFO mode */
    pEspi->GNRCON1.B.RXFM = (uint32)rxFifoMode;
    ret &= Espi_Register_ReadBack_Check(ret, pEspi->GNRCON1.B.RXFM, (uint32)rxFifoMode);
    /* Set RX FIFO threshold */
    pEspi->FIFOTHRESHOLD.B.RXTHRESHOLD = (uint32)rxFifoThreshold;
    ret &= Espi_Register_ReadBack_Check(ret, pEspi->FIFOTHRESHOLD.B.RXTHRESHOLD, (uint32)rxFifoThreshold);

    return ret;
}

LOCAL_FORCEINLINE boolean Espi_Std_InitExpectTimeoutThreshold(ESPI_MODULE *const pEspi, Espi_ExpectTimeoutValue expectTimeoutThreshold)
{
    boolean ret;
    ret = TRUE;
    /* Set timeout duration threshold */
    pEspi->GNRCON.B.TOV = (uint32)expectTimeoutThreshold;
    ret &= Espi_Register_ReadBack_Check(ret, pEspi->GNRCON.B.TOV, (uint32)expectTimeoutThreshold);

    return ret;
}

LOCAL_FORCEINLINE boolean Espi_Std_EnableMoveCounterMode(ESPI_MODULE *const pEspi, boolean enable)
{
    boolean ret;
    ret = TRUE;
    /* Enable Move counter Mode */
    pEspi->MCCON.B.MCEN = (uint32)enable;
    ret &= Espi_Register_ReadBack_Check(ret, pEspi->MCCON.B.MCEN, (uint32)enable);

    return ret;
}
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Function:     Espi_Std_SetDma
 * Description:  Enable or disable DMA handling
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: pointer to the ESPI master module
 *               dmaEn: Enable or disable DMA handling
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * History:
 * Others:
 *  Date         Author   Modified
 *  2023/10/10   01208    create
 *********************************************************************************************************************/
extern boolean Espi_Std_SetDma(ESPI_MODULE *const pEspi, boolean dmaEn);

/**********************************************************************************************************************
 * Function:     Espi_Master_Std_InitClock
 * Description:  Initialize the ESPI master module clock properties
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: pointer to the ESPI master module
 *               clockDivision: clock division
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * History:
 * Others:
 *  Date         Author   Modified
 *  2023/10/10   01208    create
 *********************************************************************************************************************/
extern boolean Espi_Master_Std_InitClock(ESPI_MODULE *const pEspi, uint16 clockDivision);

/**********************************************************************************************************************
 * Function:     Espi_Master_Std_CalculateChannelConfiguration
 * Description:  Initialize the ESPI master channel configuration
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        baudrate:baud rate
 *               clockpolarity: clock polarity
 *               clockphase: clock phase
 *               paritycheckEnable: parity check enable
 * Inout:        None
 * Output:       None
 * Return:       uint32: channel configuration value
 * Others:
 * History:
 *  Date         Author   Modified
 *  2023/10/10   01208     create
 *********************************************************************************************************************/
extern uint32 Espi_Master_Std_CalculateChannelConfiguration(const Espi_BaudRate baudRate, Espi_ClockPolarity clockPolarity, Espi_ClockPhase clockPhase, boolean parityCheckEnable);

/**********************************************************************************************************************
 * Function:     Espi_Std_InitSlaveSlectConfiguration
 * Description:  Initialize the slave select configuration
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: pointer to the ESPI master module
 *               csChannel: channel slave select
 *               slsoActiveLevel: SLSO output active level
 *               slsoEn: enable or disable SLSO output
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author   Modified
 *  2023/10/10   01208     create
 *********************************************************************************************************************/
extern boolean Espi_Master_Std_InitSlaveSlectConfiguration(ESPI_MODULE *const pEspi, Espi_Cs_ChannelId csChannel,
                                                        Espi_ActiveOutputLevel slsoActiveLevel, boolean slsoEn);

/**********************************************************************************************************************
 * Function:     Espi_Slave_Std_InitClock
 * Description:  Initialize the ESPI slave module clock properties
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: pointer to the ESPI master module
 *               clockDivision: clock division
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author   Modified
 *  2023/10/10   01208     create
 *********************************************************************************************************************/
extern boolean Espi_Slave_Std_InitClock(ESPI_MODULE *const pEspi, uint16 clockDivision);

/**********************************************************************************************************************
 * Function:     Espi_Slave_Std_CalculateChannelConfiguration
 * Description:  Initialize the ESPI slave channel configuration
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        parityEn: enable or disable parity check
 *               baudRate: baud rate
 * Inout:        None
 * Output:       None
 * Return:       uint32: channel configuration value
 * Others:
 * History:
 *  Date         Author   Modified
 *  2023/10/10   01208    create
 *********************************************************************************************************************/
extern uint32 Espi_Slave_Std_CalculateChannelConfiguration(boolean parityEn, const Espi_BaudRate baudRate);

#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"

#endif /* ESPI_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/


/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    espi_hal.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: ESPI hardware abstraction layer header file.This file contains function prototypes for ESPI module
 *              hardware abstraction layer.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#espi_hal_h_REF_1:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*
*#espi_hal_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers
*
*#espi_hal_h_REF_3:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity
*
*#espi_hal_h_REF_4:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity
*/
#ifndef ESPI_HAL_H_
#define ESPI_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "espi_std.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "rcc_hal.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^ESPI_CS^ chip select channel max */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_CS_CHANNEL_MAX (16U)

/* ^ESPI_DATA_STEP^ data step byte */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_DATA_STEP_BYTE (8U)

/* ^ESPI_INTC_FLAG^ Interrupt flag */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_NO_ERROR (0x0U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_PARITY_ERROR (0x1U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_UNEXPECT_CFG_ERROR (0x2U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_BAUDRATE_ERROR (0x4U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_TX_OVF_ERROR (0x8U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_TX_UNF_ERROR (0x10U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_RX_OVF_ERROR (0x20U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_RX_UNF_ERRROR (0x40U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_EXPECT_TIMEOUT_ERROR (0x80U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_SLS_IINACT_ERROR (0x100U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_TX (0x200U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_RX (0x400U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_PT1EVENT (0x800U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_PT2EVENT (0X1000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_DATA_IGNORE (0x2000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_SALVE_END (0x4000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_USER_EVENET (0x8000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_FLAG_LARGE_TRANSMIT_END (0x80000U)
/* ^ESPI_INTC_FLAG^ SRSTB flag */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_SRSTB_SET (0x10000000U)

/* ^ESPI_INTC_ALL^ All interrupt flags */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_ALL_ERROR_FLAGS (0x13FU)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_INTC_ALL_FLAGS (0x8FFFFU)
/* ^ESPI_ALARM_FLAG^ Alarm flag */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_ALARM_FLAG_SPECIAL_REG (0x10000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_ALARM_FLAG_SLAVE_TIMEOUT (0x20000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_ALARM_FLAG_SE_PROTECT (0x40000U)

/* ^ESPI_ALARM_ALL^ All alarm flags */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_ALARM_ALL_FLAGS (0x70000U)

/* ^ESPI_PHASE_FLAG^ Phase flag */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_FLAG_WAIT (0x0U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_FLAG_IDLEA (0x10000000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_FLAG_IDLEB (0x20000000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_FLAG_LEAD (0x30000000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_FLAG_DATA (0x40000000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_FLAG_TRAIL (0x50000000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_FLAG_EXPECT (0x60000000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_FLAG_LEAD_STROBE (0x70000000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_FLAG_TRAIL_STROBE (0x80000000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_PHASE_ALL_FLAGS (0xF0000000U)

/* ^ESPI_ALL_FLAGS^ All flags */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_ALL_FLAGS_RO_STATES (0xF0040000U)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_ALL_FLAGS_RW_STATES (0x7FFFFU)
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_ALL_FLAGS_STATES (0xFFCFFFFFU)

/* ^ESPI_MOVE_STEP^ move step mask */
/* #Violation: espi_hal_h_REF_2 */
#define ESPI_MOVE_STEP_MASK (0x1FFFU)

/* ^ESPI_TXF_FLAG_SET^ TXF flag set mask */
#define ESPI_TXF_FLAG_SET (0x1U)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* ESPI Master Module initialization configuration structure */
typedef struct
{
    Espi_ExpectTimeoutValue expectTimeoutThreshold; /* Timeout duration threshold */
    Espi_TxFifo_Threshold txFifoThreshold;          /* Threshold for transmitting FIFO */
    Espi_RxFifo_Threshold rxFifoThreshold;          /* Threshold for receiving FIFO */
    Espi_FifoMode txFifoMode;                       /* Transmitting FIFO mode */
    Espi_FifoMode rxFifoMode;                       /* Receiving FIFO mode */
    uint32 interruptEn;                             /* Interrupt enable */
    uint16 clockDivision;                            /* Clock division, the value should >= 1 */
    boolean dmaEn;                                  /* Enable/disable DMA TX RX */
    boolean moveCounterEn;                          /* Enable/disable Move Counter Mode */
} Espi_Master_ModuleInitConfig;
/* ESPI Master channel initialization configuration structure */
typedef struct
{
    Espi_BaudRate baudRate;                 /* Baud rate configuration*/
    Espi_ClockPolarity clockPolarity;       /* Clock polarity configuration*/
    Espi_ClockPhase clockPhase;             /* Clock phase configuration*/
    boolean parityCheckEnable;              /* Enable or disable parity check*/
    Espi_Cs_ChannelId csChannel;            /* Select Slave Select Channel*/
    Espi_ActiveOutputLevel slsoActiveLevel; /* Slso work level is high or low*/
    boolean slsoEn;                         /* Enable/disable Slso output*/
} Espi_Master_ChannelInitConfig;
/*The structure can be used to initialize and configure an ESPI slave module */
typedef struct
{
    Espi_ExpectTimeoutValue expectTimeoutThreshold; /* Timeout duration threshold */
    Espi_TxFifo_Threshold txFifoThreshold;          /* Threshold for transmitting FIFO */
    Espi_RxFifo_Threshold rxFifoThreshold;          /* Threshold for receiving FIFO */
    Espi_FifoMode txFifoMode;                       /* Transmitting FIFO mode */
    Espi_FifoMode rxFifoMode;                       /* Receiving FIFO mode */
    uint32 interruptEn;                             /* Interrupt enable/disable */
    uint16 clockDivision;                            /* Clock division, the value should >= 1 */
    boolean dmaEn;                                  /* Enable DMA TX RX */
    boolean moveCounterEn;                          /* Enable/disable Move Counter Mode */
} Espi_Slave_ModuleInitConfig;
/*The structure of configures an ESPI slave channel's parameters */
typedef struct
{
    Espi_BaudRate baudRate;      /* Baud rate configuration*/
    Espi_Cs_ChannelId csChannel; /* Select slave select channel*/
    boolean parityCheckEnable;   /* Enable or disable parity check*/
} Espi_Slave_ChannelInitConfig;
/* ESPI Channel Dynamic Configuration */
typedef struct
{
    Espi_PhaseDelay delayTime;     /* Phase delay time */
    Espi_DataWidth dataWidth;      /* Data length */
    Espi_Master_DataMode dataMode; /* Data frame mode */
    Espi_BitOrder bitOrder;        /* Bit order */
    Espi_ParityMode parityMode;    /* Parity mode */
} Espi_ChannelDynamicConfig;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
#define SPI_START_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"

/**********************************************************************************************************************
 * Function:     Espi_Hal_TriggerDmaRequest
 * Description:  Trigger DMA request with handling both configuration and data
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: ID of the ESPI module to reset
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author    Modified
 *  2024/05/23   01208     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Espi_Hal_TriggerDmaRequest(ESPI_MODULE *const pEspi);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/* #Violation: espi_hal_c_REF_4 */
LOCAL_FORCEINLINE boolean Espi_Hal_TriggerDmaRequest(ESPI_MODULE *const pEspi)
{
    boolean ret;
    ret = TRUE;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: espi_hal_h_REF_3 */
    /* #Violation: espi_hal_h_REF_4 */
    Assert((boolean)(CHECK_ESPI_BASE(pEspi)));
#endif

#if defined(THA6_THA6412)
    uint32 regValue = 0U;
    regValue = pEspi->GNRCON1.U;
    pEspi->GNRCON1.U = (regValue & 0xC3FFFFFFU) | (5UL << 26U);
    pEspi->GNRCON1.U = regValue;
#endif

    pEspi->STS.U = (uint32)(ESPI_TXF_FLAG_SET << 9U); /* write 1 to bit STS.TXF */
    ret &= Espi_Register_ReadBack_Check(ret, pEspi->STS.B.TXF, ESPI_TXF_FLAG_SET);
    return ret;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Espi_Master_Hal_InitModule
 * Description:  Initialize the ESPI master module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When initializing different ESPI modules, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pEspi: pointer to the ESPI master module
 *               pConfig: pointer to the ESPI master module configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
extern boolean Espi_Master_Hal_InitModule(ESPI_MODULE *const pEspi, const Espi_Master_ModuleInitConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Espi_Master_Hal_ChannelInit
 * Description:  Initialize the specified ESPI master channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When initializing different ESPI channels of the same ESPI or different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: pointer to the ESPI master module
 *               pConfig: pointer to the ESPI master channel configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *  2023/07/19    01030     Modify
 *********************************************************************************************************************/
extern boolean Espi_Master_Hal_InitChannel(ESPI_MODULE *const pEspi, const Espi_Master_ChannelInitConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Espi_Slave_Hal_EnableCsChannel
 * Description:  Enable or disable slave channel cs input
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When enabling different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: pointer to the ESPI slave module
 *               enable: enable or disable SLSI
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
extern boolean Espi_Slave_Hal_EnableCsChannel(ESPI_MODULE *const pEspi, boolean enable);

/**********************************************************************************************************************
 * Function:     Espi_Slave_Hal_lnitModule
 * Description:  Initialize the ESPI slave module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When initializing different ESPI modules, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pEspi: pointer to the ESPI slave module
 *               pConfig: pointer to the ESPI slave module configuration structure
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
extern boolean Espi_Slave_Hal_InitModule(ESPI_MODULE *const pEspi, const Espi_Slave_ModuleInitConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Espi_Slave_Hal_InitChannel
 * Description:  Initialize the specified ESPI slave channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When initializing different ESPI channels of the same ESPI or different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: pointer to the ESPI slave module
 *               pConfig: pointer to the ESPI slave channel configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
extern boolean Espi_Slave_Hal_InitChannel(ESPI_MODULE *const pEspi, const Espi_Slave_ChannelInitConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Espi_Hal_CalculateDynamicConfiguration
 * Description:  Initialize the ESPI master/slave channel dynamic configuration
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant 
 * Input:        channelId: channel ID
 *               pConfig: pointer to the ESPI master/slave channel dynamic configuration
 * Inout:        None
 * Output:       None
 * Return:       uint32: dynamic configuration value
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
extern uint32 Espi_Hal_CalculateChannelDynamicConfiguration(Espi_Cs_ChannelId channelId, const Espi_ChannelDynamicConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Espi_Hal_WriteConfiguration
 * Description:  Write configuration data to the ESPI module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: Pointer to the ESPI master module
 *               baconVal: Configuration value in uint32 format
 *               lastWord: A boolean flag indicating whether this is the last word of data being written
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
extern void Espi_Hal_WriteConfiguration(ESPI_MODULE *const pEspi, uint32 baconVal, boolean lastWord);

/**********************************************************************************************************************
 * Function:     Espi_Hal_ReceiveData
 * Description:  Receives data from ESPI module and stores to the buffer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When reading data from different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: Pointer to the ESPI
 *               rxbuffer: Pointer to the buffer to store the received data
 *               bufferWidth: The width step of receive data buffer
 * Inout:        None
 * Output:       None
 * Return:       uint8: The step of received bytes
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
extern uint8 Espi_Hal_ReceiveData(const ESPI_MODULE *const pEspi, uint8 *const rxBuffer, Espi_DataBufferWidth bufferWidth);

/**********************************************************************************************************************
 * Function:     Espi_Hal_SendData
 * Description:  Sends data from buffer to ESPI module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When writing data to different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: Pointer to the ESPI
 *               txBuffer: Pointer to the buffer storing the transmit data
 *               bufferWidth: The width of transmit data buffer
 * Inout:        None
 * Output:       None
 * Return:       uint8: The number of transmitted data steps
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/09    01030     Create
 *********************************************************************************************************************/
extern uint8 Espi_Hal_SendData(ESPI_MODULE *const pEspi, const uint8 *const txBuffer, const Espi_DataBufferWidth bufferWidth);

/**********************************************************************************************************************
 * Function:     Espi_Hal_SetExtraLargeDataLength
 * Description:  Set extra large data length
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: pointer to the ESPI module
 *               byteCount: the number of bytes
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       The minimum data length is 2 bytes, the maximum data length is 65536 bytes
 * History:
 *  Date          Author    Modified
 *  2023/11/23    01208     Create
 *********************************************************************************************************************/
extern boolean Espi_Hal_SetExtraLargeDataLength(ESPI_MODULE *const pEspi, uint16 byteCount);

/**********************************************************************************************************************
 * Function:     Espi_Hal_SetFifoLevel
 * Description:  Set FIFO level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: pointer to the ESPI module
 *               txLvl: TX FIFO level, the valid range is 0 ~ 15
 *               rxLvl: RX FIFO level, the valid range is 0 ~ 15
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/18    01208     Create
 *********************************************************************************************************************/
extern boolean Espi_Hal_SetFifoLevel(ESPI_MODULE *const pEspi, uint8 txLvl, uint8 rxLvl);

/**********************************************************************************************************************
 * Function:     Espi_Hal_GetRxFifoLevel
 * Description:  Get RXFIFO level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEspi: pointer to the ESPI module
 * Inout:        None
 * Output:       None
 * Return:       uint32: current rxfifo level
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/10/11    01208     Create
 *********************************************************************************************************************/
extern uint32 Espi_Hal_GetRxFifoLevel(const ESPI_MODULE *const pEspi);

/**********************************************************************************************************************
 * Function:     Espi_Hal_GetTxFifoLevel
 * Description:  Get TXFIFO level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEspi: pointer to the ESPI module
 * Inout:        None
 * Output:       None
 * Return:       uint32: current txfifo level
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/10/11    01208     Create
 *********************************************************************************************************************/
extern uint32 Espi_Hal_GetTxFifoLevel(const ESPI_MODULE *const pEspi);

/**********************************************************************************************************************
 * Function:     Espi_Hal_SetInterrupt
 * Description:  Enable or disable ESPI module interrupts.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: pointer to the ESPI module
 *               interrupt: interrupt flag
 *               enable: enable or disable interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/10/10    01208     Create
 *********************************************************************************************************************/
extern boolean Espi_Hal_SetInterrupt(ESPI_MODULE *const pEspi, uint32 interrupt, boolean enable);

/**********************************************************************************************************************
 * Function:     Espi_Hal_GetFlagStatus
 * Description:  Get ESPI flag status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEspi: pointer to the ESPI module
 *               flag: status mask
 * Inout:        None
 * Output:       None
 * Return:       uint32: ESPI flag status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/08    01030     Create
 *  2023/09/18    01208     Modify
 *********************************************************************************************************************/
extern uint32 Espi_Hal_GetFlagStatus(const ESPI_MODULE *const pEspi, uint32 flag);

/**********************************************************************************************************************
 * Function:     Espi_Hal_ClearFlagStatus
 * Description:  Clear ESPI flag status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pEspi: pointer to the ESPI module
 *               flag: clear flags
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/08    01030     Create
 *  2023/07/20    01030     modify
 *********************************************************************************************************************/
extern void Espi_Hal_ClearFlagStatus(ESPI_MODULE *const pEspi, uint32 flag);

/**********************************************************************************************************************
 * Function:     Espi_Hal_ResetModule
 * Description:  Resets the specified ESPI module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEspi: ID of the ESPI module to reset
 * Inout:        None
 * Output:       None
 * Return:       Rcc_ErrorFlag: Error indicating flag
 * History:
 *  Date         Author    Modified
 *  2023/08/18   01030     Create
 *********************************************************************************************************************/
extern Rcc_ErrorFlag Espi_Hal_ResetModule(ESPI_MODULE *const pEspi);

/**********************************************************************************************************************
 * Function:     Espi_Hal_EnableLoopBack
 * Description:  Enable or disable output loop-back control
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: Pointer to espi module
 *               enable: To enable or disable output loop-back control
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * History:
 *  Date         Author    Modified
 *  2023/01/23   01208     Create
 *********************************************************************************************************************/
extern boolean Espi_Hal_EnableLoopBack(ESPI_MODULE *const pEspi, boolean enable);

/**********************************************************************************************************************
 * Function:     Espi_Hal_SetMoveCounterDataLength
 * Description:  Set data length for Move Counter Mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: Pointer to espi module
 *               uint16: moveStep: move step
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * History:
 *  Date         Author    Modified
 *  2024/04/19   01208     Create
 *********************************************************************************************************************/
extern boolean Espi_Hal_SetMoveCounterDataLength(ESPI_MODULE *const pEspi, uint16 moveStep);

/**********************************************************************************************************************
 * Function:     Espi_Hal_SetDma
 * Description:  Enable or disable DMA
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different ESPI modules, 
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: ID of the ESPI module to reset
 *               dmaEn: enable or disable DMA
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * History:
 *  Date         Author    Modified
 *  2025/04/02   01809     Create
 *********************************************************************************************************************/
extern boolean Espi_Hal_SetDma(ESPI_MODULE *const pEspi, boolean dmaEn);

/**********************************************************************************************************************
 * Function:     Espi_Hal_FlushRxFifo
 * Description:  Flush the RXFIFO of the ESPI module: reset the FIFO pointers, the FSM and the counters
 *               and re-arm the RXFIFO move logic
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different ESPI modules,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pEspi: pointer to the ESPI module
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       Before this function is called, the transfer shall be stopped, the interrupts and the DMA
 *               requests of the module shall be disabled and the DMA channels shall be cancelled. The
 *               function contains no polling loop, it may be called inside a critical section.
 *               GNRCON.SRSTB is self clearing and is not read back.
 * History:
 *  Date         Author    Modified
 *  2026/09/16   -         Create
 *********************************************************************************************************************/
extern boolean Espi_Hal_FlushRxFifo(ESPI_MODULE *const pEspi);

#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"

#endif /* ESPI_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

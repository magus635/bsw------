/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    asi_hal.h
 * Author:      00101
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #asi_hal_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
* #asi_hal_h_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
#ifndef ASI_HAL_H_
#define ASI_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "asi_register.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* LIN flag */
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_NO_FLAG_SET (0x0U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_HEADER_RX_FLAG (0x01U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_DATA_TX_COMPLETED_FLAG (0x02U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_DATA_RX_COMPLETED_FLAG (0x04U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_WAKEUP_FLAG (0x20U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_RECEIVER_BUSY_FLAG (0x80U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_DATA_RX_BUFFER_NOT_EMPTY_FLAG (0x100U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_MESSAGE_BUFFER_READY_FLAG (0x200U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_AUTOSYNC_COMPLETE_FLAG (0x80000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_STATE_FLAG      (0xF000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_SLEEP_STATE_FLAG (0x0000U)
#define ASI_LIN_INIT_STATE_FLAG (0x1000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_IDLE_STATE_FLAG (0x2000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_BREAK_STATE_FLAG (0x3000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_BREAK_DELIMITER_STATE_FLAG (0x4000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_SYNC_FIELD_STATE_FLAG (0x5000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_ID_FIELD_STATE_FLAG (0x6000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_HEADER_DONE_STATE_FLAG (0x7000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_DATA_DONE_STATE_FLAG (0x8000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_CHECKSUM_STATE_FLAG (0x9000U)
#define ASI_LIN_MASK_RO_FLAGS  (0x80327U)
#define ASI_LIN_ALL_FLAGS (0xFF3E7U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_NOISE_FLAG (0x80000001U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_BUFFER_OVERRUN_FLAG (0x80000080U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_FRAMING_ERROR_FLAG  (0x80000100U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_ID_PARITY_ERROR_FLAG  (0x80000200U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_BREAK_DELIMITER_ERROR_FLAG (0x80000400U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_SYNC_FIELD_ERROR_FLAG  (0x80000800U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_CHECKSUM_ERROR_FLAG  (0x80001000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_BITERROR_FLAG  (0x80002000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_OUTPUT_COMPARE_FLAG (0x80004000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_STUCK_AT_ZERO_FLAG  (0x80008000U)
#define ASI_LIN_ALL_ERROR_FLAGS (0x8000FF81U)

/* LIN Interrupt */
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_NO_INT  (0x00U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_HEADER_RX_INT  (0x01U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_DATA_TX_COMPLETED_INT  (0x02U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_DATA_RX_COMPLETED_INT  (0x04U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_WAKEUP_INT  (0x20U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_LINSTATE_INT  (0x40U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_BUFFER_OVERRUN_INT  (0x80U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_FRAME_ERROR_INT  (0x100U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_HEADER_ERROR_INT  (0x800U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_CHECKSUM_ERROR_INT  (0x1000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_BIT_ERROR_INT  (0x2000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_OUTPUT_COMPARE_INT  (0x4000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_STUCK_AT_ZERO_INT  (0x8000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_ALL_INTS  (0xF9E7U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_LIN_ALL_ERROR_INTS  (0xF980U)

/* UART flag */
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_NOISE_FLAG (0x01U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_TX_COMPLETED_FLAG (0x02U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_TX_FIFO_FULL_FLAG (0x02U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_RX_COMPLETED_FLAG (0x04U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_RX_FIFO_EMPPTY_FLAG (0x04U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_TIMEOUT_FLAG (0x08U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_RX_FIFO_NOT_EMPTY_FLAG (0x10U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_WAKEUP_FLAG (0x20U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_FIFO_BUFFER_OVERRUN_FLAG (0x80U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_FRAMING_ERROR_FLAG (0x100U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_BUFFER_DATA_READY_FLAG (0x200U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_PARITY_ERROR_FLAG (0x3C00U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_OUTPUT_COMPARE_FLAG (0x4000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_STACK_AT_ZERO_FLAG (0x8000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_SLEEP_MODE_FLAG    (0x80000000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_INIT_MODE_FLAG     (0x80000001U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_IDLE_MODE_FLAG     (0x80000002U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_ALL_FLAGS (0xFFFFU)
#define ASI_UART_CLEAR_ALL_FLAGS (0xFFAFU)

/* UART Interrupt */
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_NO_INT  (0x00U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_DATA_TRANSMITTED_INT (0x02U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_DATA_RX_COMPLETE_INT (0x04U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_TIMEOUT_INT (0x08U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_WAKEUP_INT (0x20U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_BUFFER_OVERRUN_INT (0x80U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_FRAME_ERROR_INT (0x100U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_OUTPUT_COMPARE_INT (0x4000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_STUCK_AT_ZERO_INT (0x8000U)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_ALL_INTS (0xD0AEU)
/* #Violation: asi_hal_h_REF_1 */
#define ASI_UART_ALL_ERROR_INTS (0xC180U)
#define ASI_OUTPUT_COMPARE_MAX_COUNTER (0xFFFFU)

/* ASI Run State */
#define ASI_RUNSTATE_OK (0U)
#define ASI_RUNSTATE_NOT_OK (1U)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* LIN node mode */
typedef enum
{
    ASI_LIN_MODE_SLAVE = 0U, /* LIN slave mode. */
    ASI_LIN_MODE_MASTER      /* LIN master mode. */
} Asi_Lin_Mode;

/* LIN frame beak length */
typedef enum
{
    ASI_LIN_BREAKLEN_10BIT = 0U, /* 10-bit break length */
    ASI_LIN_BREAKLEN_11BIT,      /* 11-bit break length */
    ASI_LIN_BREAKLEN_12BIT,      /* 12-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_13BIT,      /* 13-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_14BIT,      /* 14-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_15BIT,      /* 15-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_16BIT,      /* 16-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_17BIT,      /* 17-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_18BIT,      /* 18-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_19BIT,      /* 19-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_20BIT,      /* 20-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_21BIT,      /* 21-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_22BIT,      /* 22-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_23BIT,      /* 23-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_36BIT,      /* 36-bit break length, only master node supported. */
    ASI_LIN_BREAKLEN_50BIT       /* 50-bit break length, only master node supported. */
} Asi_Lin_BreakLen;

/* LIN Frame data direction */
typedef enum
{
    ASI_LIN_DATADIR_RX = 0U, /* Node receives the data */
    ASI_LIN_DATADIR_TX,      /* Node transmits the data */
    ASI_LIN_DATADIR_NODATA   /* Frame data is irrelevant for the node */
} Asi_Lin_DataDIR;

/* LIN frame checksum type */
typedef enum
{
    ASI_LIN_CHECKSUMTYPE_ENCHANCED = 0U, /* Enhanced checksum */
    ASI_LIN_CHECKSUMTYPE_CLASSIC         /* Classic checksum */
} Asi_Lin_ChecksumType;

/* LIN ID filter mode */
typedef enum
{
    ASI_LIN_IDFILTERMODE_LIST = 0U, /* ID list filter mode */
    ASI_LIN_IDFILTERMODE_MASK       /* ID mask filter mode */
} Asi_Lin_IdFilterMode;

/* The number of UART sample */
typedef enum
{
    ASI_UART_SAMPLENUM_16 = 0x0U, /* The number of sample is 16 */
    ASI_UART_SAMPLENUM_4 = 0x04U, /* The number of sample is 4 */
    ASI_UART_SAMPLENUM_5 = 0x05U, /* The number of sample is 5 */
    ASI_UART_SAMPLENUM_6 = 0x06U, /* The number of sample is 6 */
    ASI_UART_SAMPLENUM_8 = 0x08U, /* The number of sample is 8 */
} Asi_Uart_SampleNum;

/* The count of UART data bits */
typedef enum
{
    ASI_UART_DATATBITS_7 = 0x0U,  /* 7-bit data */
    ASI_UART_DATATBITS_8 = 0x02U, /* 8-bit data */
    ASI_UART_DATATBITS_15= 0x80U, /* 15-bit data */
    ASI_UART_DATATBITS_16= 0x82U  /* 16-bit data */
} Asi_Uart_DataBits;

/* The count of UART stop bits */
typedef enum
{
    ASI_UART_STOPBITS_1 = 0U, /* 1 stop bit */
    ASI_UART_STOPBITS_2,      /* 2 stop bits */
    ASI_UART_STOPBITS_3       /* 3 stop bits */
} Asi_Uart_StopBits;

/* UART parity control */
typedef enum
{
    ASI_UART_PARITY_EVEN = 0x04U,   /* Even */
    ASI_UART_PARITY_ODD = 0x0CU,    /* Odd */
    ASI_UART_PARITY_LOGIC0 = 0x24U, /* Parity is always logic 0 */
    ASI_UART_PARITY_LOGIC1 = 0x2CU, /* Parity is always logic 1 */
    ASI_UART_PARITY_NONE = 0x00     /* No parity */
} Asi_Uart_Parity;

/* UART DMA Control */
typedef enum
{
    ASI_UART_DMACTRL_TX = 0U, /* TX with DMA */
    ASI_UART_DMACTRL_RX,      /* RX with DMA */
    ASI_UART_DMACTRL_TXRX     /* Both TX and RX with DMA */
} Asi_Uart_DmaCtrl;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* LIN Frame Control structure */
typedef struct
{
    Asi_Lin_DataDIR dir;            /* Frame data direction */
    Asi_Lin_ChecksumType checksum;  /* Frame checksum type */
    uint8 dataLength;               /* data filed length: 1 ~ 8 bytes*/
    uint8 frameID;                  /* Frame ID */
} Asi_Lin_FrameControl;

/* LIN Frame ID filter structure */
typedef struct
{
    Asi_Lin_IdFilterMode filterMode;     /* Filter mode: mast or list */
    Asi_Lin_FrameControl FilterControl;  /* filter control structure */
} Asi_Lin_IdFilter;

/* LIN Frame ID filter configuration structure */
typedef struct
{
    Asi_Lin_IdFilter* pIdFilter; /* Pointer to Id filter structure */
    uint8 idFilterCount;         /* The count of Id filter */
} Asi_Lin_IdFilterConfig;

/* LIN configuration initial structure */
typedef struct
{
    Asi_Lin_Mode mode;                       /* Master or Slave mode */
    Asi_Lin_BreakLen breakLength;            /* Frame break length */
    uint32 IntegerBaudRate;                  /* Integer Baud rate(Max:0xFFFFF) */
    uint32 FractionalBaudRate;               /* Fractional Baud rate(Max:0xF) */
    uint32 enableInterrupt;                  /* Enable or disable interrupt based on bit field.the defined macros
                                                ASI_LIN_XXX_INT can be used */
    uint32 frameTimeout;                     /* Frame header(Max:0x2F) or response Timeout Value(Max:0x0F) */
    Asi_Lin_IdFilterConfig* pIdFilterConfig; /* ID filter configuration, only for slave node */
    boolean isAutoWakeUp;                    /* Enable or disable auto wake-up */
    boolean isMasterRxDmaEnabled;            /* Enable or disable master RX with DMA */
    boolean isRxBufferLockEnabled;           /* Enable or disable RX buffer lock mode */
} Asi_Lin_Config;

/* UART configuration structure */
typedef struct
{
    uint32 IntegerBaudRate;          /* Integer Baud rate */
    uint32 FractionalBaudRate;       /* Fractional Baud rate */
    uint32 enableInterrupt;          /* Enable or disable interrupt,the defined macros ASI_UART_XXX_INT can be used*/
    Asi_Uart_SampleNum sampleNumber; /* The number of sample */
    Asi_Uart_DataBits dataBits;      /* The number of data bit */
    Asi_Uart_StopBits stopBits;      /* The number of stop bit */
    Asi_Uart_Parity parity;          /* Parity control: no parity, even, odd, logic 0, logic 1 */
    boolean isEnableFIFO;            /* Select FIFO or buffer mode for TX and RX */
    boolean isRxBufferLockEnabled;   /* Enable/disable RX buffer lock mode */
} Asi_Uart_Config;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: asi_hal_h_REF_1 */
#define ASI_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: asi_hal_h_REF_2 */
#include "Asi_MemMap.h"
/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_InitModule
 * Description:  Initialize the specified LIN module(node).
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pLin: pointer to ASI(LIN) module.
 *               pConfig: pointer to LIN configuration structure.
 *               timeout: timeout value(system timer counter). The value range from 0x0 to 0xFFFF_FFFF.
 * Inout:        None
 * Output:       None
 * Return:       uint8: 0-successful; 1-failed;
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern uint8 Asi_Lin_Hal_InitModule(ASI_MODULE *const pLin, const Asi_Lin_Config *const pConfig, uint32 timeout);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_SendHeader
 * Description:  Send LIN frame header by master node. It's failed to execute by slave node.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pLin: pointer to ASI(LIN) module.
 *               pFrameHeader: pointer to LIN frame control structure.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Lin_Hal_SendHeader(ASI_MODULE *const pLin, const Asi_Lin_FrameControl *const pFrameHeader);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_SendData
 * Description:  Send the response data with the specified length.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pLin: pointer to ASI(LIN) module.
 *               pData: pointer to the response data.
 *               length: the response data length. The value range is 1 ~ 8 bytes.
 * Inout:        None
 * Output:       None
 * Return:       uint8: 0-successful; 1-failed;
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern uint8 Asi_Lin_Hal_SendData(ASI_MODULE *const pLin, const uint8 *const pData, uint32 length);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_ReceiveHeader
 * Description:  Store the frame ID into the user's buffer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pLin: pointer to ASI(LIN) module.
 *               pFrameID: pointer to the frame ID.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Lin_Hal_ReceiveHeader(const ASI_MODULE *const pLin,  uint8* const pFrameID);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_ReceiveData
 * Description:  Store the response data with the specified length into the user's buffer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pLin: pointer to ASI(LIN) module.
 *               pData: pointer to the response data.
 *               length: the response data length, the range is 1 ~ 8 bytes.
 * Inout:        None
 * Output:       None
 * Return:       uint32: The actual length of received data.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern uint32 Asi_Lin_Hal_ReceiveData (const ASI_MODULE *const pLin, uint8* const pData, uint8 length);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_SetInterrupt 
 * Description:  Enable or disable the specified interrupt or all interrupts.
 *               User can use LIN interrupt macro "ASI_LIN_XXX_INT" to specify interrupt(s).
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pLin: pointer to ASI(LIN) module.
 *               interrupt: the specified interrupt. The value range from 0x0 to 0x0000_FFFF.
 *               isEnabled: TRUE - enable the interrupt(s);FALSE - disable the interrupt(s).
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Lin_Hal_SetInterrupt(ASI_MODULE *const pLin, uint32 interrupt, boolean isEnabled);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_GetFlagStatus
 * Description:  Get the status of the specified flag.
 *               User can use LIN flag macro to specify flag(s).
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pLin: pointer to ASI(LIN) module.
 *               flag: LIN flag, user can use the defined macro ASI_LIN_XXX_FLAG or ASI_LIN_XXX_ERROR_FLAG.
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0-no flag is set; other-the specified flag is set(one bit indicates one flag status).
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern uint32 Asi_Lin_Hal_GetFlagStatus(const ASI_MODULE *const pLin, uint32 flag);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_ClearFlagStatus
 * Description:  Clear the status of specified hardware flag.
 *               User can use the defined macro ASI_LIN_XXX_FLAG to specify flag(s).
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pLin: pointer to ASI(LIN) module.
 *               flag: LIN flag, user can use the defined macro ASI_LIN_XXX_FLAG or ASI_LIN_XXX_ERROR_FLAG.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Lin_Hal_ClearFlagStatus(ASI_MODULE *const pLin, uint32 flag);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_SendWakeupRequest
 * Description:  Send wakeup signal by master node.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pLin: pointer to ASI(LIN) module.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       Before sending wake-up request, the module must not be in Sleep Mode.
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Lin_Hal_SendWakeupRequest(ASI_MODULE *const pLin);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_DataDiscardRequest
 * Description:  Send data discard request.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pLin: pointer to ASI(LIN) module.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       For a LIN slave, This function can be call only when the identifier is software-filtered.
 * History:
 *  Date          Author    Modified
 *  2024/11/28    01744     Create, add function adaptation 0001286
 *********************************************************************************************************************/
extern void Asi_Lin_Hal_DataDiscardRequest(ASI_MODULE *const pLin);

/**********************************************************************************************************************
 * Function:     Asi_Lin_Hal_SetBufferIdentifier
 * Description:  Set the buffer direction.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pLin: pointer to ASI(LIN) module.
 *               pFrameHeader: pointer to the configuration set of Lin frames.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/28    01744     Create, add function adaptation 0001286
 *********************************************************************************************************************/
extern void Asi_Lin_Hal_SetBufferIdentifier(ASI_MODULE *const pLin, const Asi_Lin_FrameControl *const pFrameHeader);

/**********************************************************************************************************************
 * Function:     Asi_Uart_Hal_InitModule 
 * Description:  Initialize the specified UART module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pUart: pointer to ASI(UART) module.
 *               pConfig: pointer to UART configuration structure.
 *               timeout: timeout value(system timer counter). The value range from 0x0 to 0xFFFF_FFFF.
 * Inout:        None
 * Output:       None
 * Return:       uint8: 0 - successful; 1 - failed;
 * Others:       After initialization, both TX and RX is enabled.
 *               After initialization, both TX and RX with DMA is disabled.
 *               Asi_Uart_Hal_SetTxRxWithDMA() can be used to enable or disable DMA for TX/RX.
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern uint8 Asi_Uart_Hal_InitModule(ASI_MODULE *const pUart, const Asi_Uart_Config *const pConfig, uint32 timeout);

/**********************************************************************************************************************
 * Function:     Asi_Uart_Hal_SendData
 * Description:  Send one data.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pUart: pointer to ASI(UART) module.
 *               pData: pointer to data buffer.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       when UART data bit-width is 15 or 16 bits, the function will read two byes, user must make sure that the
 *               buffer stores two bytes.
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Uart_Hal_SendData(ASI_MODULE *const pUart, const uint8 *const pData);

/**********************************************************************************************************************
 * Function:     Asi_Uart_Hal_ReceiveData
 * Description:  Receive one data.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pUart: pointer to ASI(UART) module.
 *               pData: pointer to data buffer.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       When UART data bit-width is 15 or 16 bits, the function will write two byes into the buffer,
 *               user must make sure that the buffer length is equal or greater than two.
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Uart_Hal_ReceiveData(const ASI_MODULE *const pUart, uint8 *const pData);

/**********************************************************************************************************************
 * Function:     Asi_Uart_Hal_SetInterrupt 
 * Description:  Enable or disable the specified interrupt or all interrupts.
 *               User can use UART Interrupt macro to specify one or more interrupt.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pUart: pointer to ASI(UART) module.
 *               interrupt: he specified interrupt, user can use the defined macro ASI_UART_XXX_INT.
 *               isEnabled: TRUE-enable the interrupt(s); FALSE-disable the interrupt(s).
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Uart_Hal_SetInterrupt(ASI_MODULE *const pUart, uint32 interrupt, boolean isEnabled);

/**********************************************************************************************************************
 * Function:     Asi_Uart_Hal_GetFlagStatus 
 * Description:  Get the status of specified hardware flag, user can use UART Flag macro to specify one or more flag.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pUart: pointer to ASI(Uart) module.
 *               flag: hardware flag, the defined macro "ASI_UART_XXX_FLAG" can be used.
 * Inout:        None
 * Output:       None
 * Return:       uint32: 0-no flag is set; other-the specified flag is set;
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern uint32 Asi_Uart_Hal_GetFlagStatus(const ASI_MODULE *const pUart, uint32 flag);

/**********************************************************************************************************************
 * Function:     Asi_Uart_Hal_ClearFlagStatus 
 * Description:  Clear the status of specified hardware flag, user can use UART Flag macro to specify one or more flag.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pUart: pointer to ASI(UART) module.
 *               flag: hardware flag, the defined macro "ASI_UART_XXX_FLAG" can be used.ASI_UART_SLEEP_MODE_FLAG,
 *               ASI_UART_IDLE_MODE_FLAG,ASI_UART_INIT_MODE_FLAG can not be cleared by software.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Uart_Hal_ClearFlagStatus(ASI_MODULE *const pUart, uint32 flag);

/**********************************************************************************************************************
 * Function:     Asi_Uart_Hal_SetTxRxWithDMA 
 * Description:  Enable or disable TX/RX with DMA.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pUart: pointer to ASI(UART) module.
 *               txRx: specified tx, rx or both.
 *               isEnabled: TRUE-enable DMA; FALSE-disable DMA.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Uart_Hal_SetTxRxWithDMA(ASI_MODULE *const pUart, Asi_Uart_DmaCtrl txRx, boolean isEnabled);

/**********************************************************************************************************************
 * Function:     Asi_Hal_EnterSleepMode 
 * Description:  The hardware module will enter sleep mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pAsi: pointer to ASI module.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern void Asi_Hal_EnterSleepMode(ASI_MODULE *const pAsi);

/**********************************************************************************************************************
 * Function:     Asi_Hal_ExitSleepMode 
 * Description:  The hardware module will exit sleep mode.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pAsi: pointer to ASI module.
 * Inout:        None
 * Output:       None
 * Return:       uint8: 0-successful; 1-failed;
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern uint8 Asi_Hal_ExitSleepMode(ASI_MODULE *const pAsi);

/**********************************************************************************************************************
 * Function:     Asi_Hal_ResetModule
 * Description:  Reset the specified ASI Module.
 *               This function will reset the specified hardware module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pLin: pointer to ASI module.
 * Inout:        None
 * Output:       None
 * Return:       uint8: 0-successful; 1-failed;
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern uint8 Asi_Hal_ResetModule(ASI_MODULE *const pAsi);

/**********************************************************************************************************************
 * Function:     Asi_Hal_SoftReset
 * Description:  Soft reset the specified ASI Module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different ASI modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pAsi: pointer to ASI module.
 *               timeout: timeout value(system timer counter). The value range from 0x0 to 0xFFFF_FFFF.
 * Inout:        None
 * Output:       None
 * Return:       uint8: 0-successful; 1-failed
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/27    00101     Create
 *********************************************************************************************************************/
extern uint8 Asi_Hal_SoftReset(ASI_MODULE *const pAsi, uint32 timeout);


/* #Violation: asi_hal_h_REF_1 */
#define ASI_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: asi_hal_h_REF_2 */
#include "Asi_MemMap.h"

#endif /* ASI_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/    

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    dma_hal.h
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/

/*
*#Violation Summary
*
*#dma_hal_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#dma_hal_h_REF_2:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#dma_hal_h_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*  
*#dma_hal_h_REF_4:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
* 
*#dma_hal_h_REF_5:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#dma_hal_h_REF_6:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#dma_hal_h_REF_7:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/

#ifndef DMA_HAL_H_
#define DMA_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "dma_register.h"
#include "Platform_Types.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* ^DMA_CHANNELSTATUS^ Dma channel status */
/* #Violation: dma_hal_h_REF_2 */
#define DMA_CHANNELSTATUS_TC (1U)       /* Define channel terminal count status */
/* #Violation: dma_hal_h_REF_2 */
#define DMA_CHANNELSTATUS_BUSERROR (2U) /* Define channel bus error status */
/* #Violation: dma_hal_h_REF_2 */
#define DMA_CHANNELSTATUS_SCB (4U)      /* Define channel source circular buffer status */
/* #Violation: dma_hal_h_REF_2 */
#define DMA_CHANNELSTATUS_DCB (8U)      /* Define channel destination circular buffer status */
/* #Violation: dma_hal_h_REF_2 */
#define DMA_CHANNELSTATUS_PAT (16U)     /* Define channel match pattern status */
/* #Violation: dma_hal_h_REF_2 */
#define DMA_CHANNELSTATUS_THR (32U)     /* Define channel transfer size threshold status */

/* ^DMA_CHANNELINTERRUPT^ Dma channel interrupt */
#define DMA_CHANNELINTERRUPT_TC (1U)       /* Define channel terminal count interrupt */
#define DMA_CHANNELINTERRUPT_BUSERROR (2U) /* Define channel bus error interrupt */
#define DMA_CHANNELINTERRUPT_SCB (4U)      /* Define channel source circular buffer interrupt */
#define DMA_CHANNELINTERRUPT_DCB (8U)      /* Define channel destination circular buffer interrupt */
#define DMA_CHANNELINTERRUPT_PAT (16U)     /* Define channel match pattern interrupt */
#define DMA_CHANNELINTERRUPT_THR (32U)     /* Define channel transfer size threshold interrupt */
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enum for source or destination address increment mode */
typedef enum
{
    DMA_CHANNELADDRESSINCREMENT_NO_INCREASE = 0U, /* No increment */
    DMA_CHANNELADDRESSINCREMENT_INCREASE          /* Increment */
} Dma_ChannelAddressIncrement;

/* Enum for source or destination transfer width select */
typedef enum
{
    DMA_CHANNELTRANSFERWIDTH_8BIT = 0U, /* 8 bits */
    DMA_CHANNELTRANSFERWIDTH_16BIT,     /* 16 bits */
    DMA_CHANNELTRANSFERWIDTH_32BIT,     /* 32 bits */
    DMA_CHANNELTRANSFERWIDTH_64BIT,     /* 64 bits */
    DMA_CHANNELTRANSFERWIDTH_128BIT     /* 128 bits */
} Dma_ChannelTransferWidth;

/* Enum for source or destination burst size */
typedef enum
{
    DMA_CHANNELBURSTSIZE_1 = 0U, /* 1 transfer */
    DMA_CHANNELBURSTSIZE_4,      /* 4 transfer */
    DMA_CHANNELBURSTSIZE_8,      /* 8 transfer */
    DMA_CHANNELBURSTSIZE_16,     /* 16 transfer */
    DMA_CHANNELBURSTSIZE_32,     /* 32 transfer */
    DMA_CHANNELBURSTSIZE_64,     /* 64 transfer */
    DMA_CHANNELBURSTSIZE_128,    /* 128 transfer */
    DMA_CHANNELBURSTSIZE_256     /* 256 transfer */
} Dma_ChannelBurstSize;

/* Enum for DMA flow control mode and transfer type */
typedef enum
{
    DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M = 0U, /* DMA flow control, memory to memory */
    DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2P,      /* DMA flow control, memory to peripheral */
    DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2M,      /* DMA flow control, peripheral to memory */
    DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2P,      /* DMA flow control, peripheral to peripheral */
    DMA_FLOWCONTROLANDTRANSFERTYPE_DPER_P2P,     /* Destination peripheral flow control, peripheral to peripheral */
    DMA_FLOWCONTROLANDTRANSFERTYPE_PER_M2P,      /* Peripheral flow control, memory to peripheral */
    DMA_FLOWCONTROLANDTRANSFERTYPE_PER_P2M,      /* Peripheral flow control, peripheral to memory */
    DMA_FLOWCONTROLANDTRANSFERTYPE_SPER_P2P      /* Source peripheral flow control, peripheral to peripheral */
} Dma_FlowControlAndTransferType;

/* Enum for select double buffer source or destination */
typedef enum
{
    DMA_DBSOURCEORDESTINATION_SOURCE = 0U, /* Source double buffer */
    DMA_DBSOURCEORDESTINATION_DESTINATION  /* Destination double buffer */
} Dma_DBSourceOrDestination;

/* Enum for select switch mode */
typedef enum
{
    DMA_DBSWITCHMODE_SW = 0U, /* Double buffer software switch */
    DMA_DBSWITCHMODE_HW_SW    /* Double buffer hardware or software switch */
} Dma_DBSwitchMode;

/* Enum for select circular buffer source or destination   */
typedef enum
{
    DMA_CBSOURCEORDESTINATION_SOURCE = 1U, /* Source circular buffer */
    DMA_CBSOURCEORDESTINATION_DESTINATION, /* Destination circular buffer */
    DMA_CBSOURCEORDESTINATION_BOTH         /* Both of source and destination */
} Dma_CBSourceOrDestination;

/* Enum for circular buffer size */
typedef enum
{
    DMA_CBSIZE_NONE = 0U, /* no circle*/
    DMA_CBSIZE_2BYTE,     /* 2 byte */
    DMA_CBSIZE_4BYTE,     /* 4 byte */
    DMA_CBSIZE_8BYTE,     /* 8 byte */
    DMA_CBSIZE_16BYTE,    /* 16 byte */
    DMA_CBSIZE_32BYTE,    /* 32 byte */
    DMA_CBSIZE_64BYTE,    /* 64 byte */
    DMA_CBSIZE_128BYTE,   /* 128 byte */
    DMA_CBSIZE_256BYTE,   /* 256 byte */
    DMA_CBSIZE_512BYTE,   /* 512 byte */
    DMA_CBSIZE_1024BYTE,  /* 1024 byte */
    DMA_CBSIZE_2048BYTE,  /* 2048 byte */
    DMA_CBSIZE_4096BYTE,  /* 4096 byte */
    DMA_CBSIZE_8192BYTE,  /* 8192 byte */
    DMA_CBSIZE_16384BYTE, /* 16384 byte */
    DMA_CBSIZE_32768BYTE  /* 32768 byte */
} Dma_CBSize;

/* Enum for pattern data size */
typedef enum
{
    DMA_PATTERNSIZE_DISABLE = 0U, /* No match pattern operation*/
    DMA_PATTERNSIZE_8BIT,         /* 8 bit */
    DMA_PATTERNSIZE_16BIT,        /* 16 bit */
    DMA_PATTERNSIZE_32BIT         /* 32 bit */
} Dma_PatternSize;

/* Enum for double buffer mode */
typedef enum
{
    DMA_DOUBLEBUFFERFROZENSTATUS_NO_FROZEN = 0U,           /* No buffer frozen */
    DMA_DOUBLEBUFFERFROZENSTATUS_BUFFER0_FROZEN,           /* Buffer0 frozen */
    DMA_DOUBLEBUFFERFROZENSTATUS_BUFFER1_FROZEN,           /* Buffer1 frozen */
    DMA_DOUBLEBUFFERFROZENSTATUS_BOTH_FROZEN_BUFFER0FIRST, /* Both buffers have frozen,buffer0 first frozen */
    DMA_DOUBLEBUFFERFROZENSTATUS_BOTH_FROZEN_BUFFER1FIRST  /* Both buffers have frozen,buffer1 first frozen */
} Dma_DoubleBufferFrozenStatus;

/* Enum for select double buffer status*/
typedef enum
{
    DMA_DOUBLEBUFFERSTATUSSELECT_BUFFER0 = 0U, /* Select buffer0 */
    DMA_DOUBLEBUFFERSTATUSSELECT_BUFFER1,      /* Select buffer1 */
    DMA_DOUBLEBUFFERSTATUSSELECT_BOTHBUFFER   /* Select buffer0 and buffer1 */
} Dma_DoubleBufferStatusSel;

/* Enum for dma access mode */
typedef enum
{
    DMA_ACCESSMODE_USER = 0U, /* User mode */
    DMA_ACCESSMODE_PRIVILEGED /* Privileged mode */
} Dma_AccessMode;

/* Enum for transfer start or end time stamp */
typedef enum
{
    DMA_TRANSFERTIMESTAMPSEL_START = 1U, /* Transfer start time stamp */
    DMA_TRANSFERTIMESTAMPSEL_END = 2U    /* Transfer end time stamp */
} Dma_TransferTimeStampSel;

/* Enum for data CRC error or LLI CRC error select */
typedef enum
{
    DMA_CRCERRORSEL_DATA = 0U, /* data CRC error */
    DMA_CRCERRORSEL_LLI        /* LLI CRC error */
} Dma_CrcErrorSel;

/* Enum for bufferable select */
typedef enum
{
    DMA_BUFFERABLE_DISABLE = 0U, /* Non-bufferable */
    DMA_BUFFERABLE_ENABLE        /* Bufferable */
} Dma_BufferableSel;

/* Enum for cacheable select */
typedef enum
{
    DMA_CACHEABLE_DISABLE = 0U, /* Non-cacheable */
    DMA_CACHEABLE_ENABLE        /* Cacheable */
} Dma_CacheableSel;

/* Enum for CRC error status */
typedef enum
{
    DMA_CRCERRORSTATUS_NOCRC_ERROR = 0U,           /* No CRC error */
    DMA_CRCERRORSTATUS_CRC_ERROR,                  /* CRC error */
    DMA_CRCERRORSTATUS_BOTH_CRC_SEPROTECT_ERROR    /* Both CRC error and SE protection error, SE protection error refers to the
                                                      failure to unlock/lock the SE protection when clearing the CRC error status */
} Dma_CrcErrorStatus;

/* Enum for transfer time stamp valid status */
typedef enum
{
    DMA_TRANSFERTIMESTAMP_INVALID = 0U,                 /* Transfer time stamp invalid */
    DMA_TRANSFERTIMESTAMP_VALID,                        /* Transfer time stamp valid */
    DMA_TRANSFERTIMESTAMP_BOTH_VALID_SEPROTECT_ERROR    /* Both transfer time stamp valid and SE protection error, SE protection error refers to the
                                                           failure to unlock/lock the SE protection when clearing the transfer time stamp valid status */
} Dma_TransferTimeStampStatus;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Struct for channel address configuration */
typedef struct
/* #Violation: dma_hal_h_REF_5 */
{
    uint32 address;                        /* Source or destination address */
    Dma_ChannelAddressIncrement increment; /* Source or destination address increment mode*/
    Dma_ChannelBurstSize burstSize;        /* Source or destination burst size */
} Dma_ChannelAddressConfig;

/* Struct for channel request */
typedef struct
{
    uint32 request;    /* Channel request. If the chip is THA6206, this number is less than or equal to 255*/
    uint32 requestMUX; /* Global request. When the channel request is set to a global request,
                            this value needs to be set, otherwise 0 can be written.
                            If the chip is THA6206, this number is less than or equal to 255 */
} Dma_ChannelRequst;

/* Struct for configuration of the transfer */
typedef struct
/* #Violation: dma_hal_h_REF_5 */
{
    Dma_ChannelAddressConfig source;                           /* Source address configuration */
    Dma_ChannelAddressConfig destination;                      /* Source address configuration */
    Dma_ChannelTransferWidth transferWidth;                    /* Source or destination transfer width*/
    Dma_FlowControlAndTransferType flowControlAndTransferType; /* Select flow control and transfer type */
    Dma_ChannelRequst sourceRequest;                           /* Source request.
                                                                  When the source is to memory,
                                                                  write 0 to this value */
    Dma_ChannelRequst destinationRequest;                      /* Destination request.
                                                                  When the destination is to memory,
                                                                  write 0 to this value */
    uint16 transferSize;                                       /* Transfer size */
} Dma_ChannelTransferConfig;

/* Struct for configuration of the LLI */
typedef struct
/* #Violation: dma_hal_h_REF_1 */
/* #Violation: dma_hal_h_REF_5 */
{
    Dma_ChannelAddressConfig source;        /* Source address configuration */
    Dma_ChannelAddressConfig destination;   /* Destination address configuration */
    Dma_ChannelTransferWidth transferWidth; /* Source or destination transfer width*/
    uint32 linkedListItemAddress;           /* Linked list item address, setting to 0 indicates the end of the linked list */
    uint16 transferSize;                    /* Transfer size */
    boolean terminaCountInterEn;            /* Linked list item address terminal
                                               count interrupt enable*/
} Dma_LinkedListItemConfig;

/* Struct for configuration of the shadow operation */
typedef struct
/* #Violation: dma_hal_h_REF_1 */
/* #Violation: dma_hal_h_REF_5 */
{
    Dma_ChannelAddressConfig source;        /* Source address configuration */
    Dma_ChannelAddressConfig destination;   /* Source address configuration */
    Dma_ChannelTransferWidth transferWidth; /* Source or destination transfer width*/
    uint32 linkedListItemAddress;           /* Linked list item address */
    uint16 transferSize;                    /* Transfer size */
} Dma_ShadowOperationConfig;

/* Struct for channel pattern match configuration */
typedef struct
/* #Violation: dma_hal_h_REF_1 */
/* #Violation: dma_hal_h_REF_5 */
{
    Dma_PatternSize patternSize; /* Pattern size */
    uint32 patternData;          /* Pattern data */
    uint32 patternDataMaskBit;   /* Pattern data mask bit */
    boolean patternMatchedStop;  /* Stop when pattern matched */
} Dma_MatchPatternConfig;

/* Struct for channel double buffer configuration */
typedef struct
/* #Violation: dma_hal_h_REF_5 */
{
    Dma_DBSourceOrDestination sel; /* Select source or destination address */
    Dma_DBSwitchMode mode;         /* Switch mode */
    uint32 switchAddr;             /* Switch address */
} Dma_DoubleBufferConfig;

/* Struct for channel circular buffer configuration */
typedef struct
/* #Violation: dma_hal_h_REF_1 */
/* #Violation: dma_hal_h_REF_5 */
{
    Dma_CBSourceOrDestination sel; /* Select circular buffer */
    Dma_CBSize srcSize;            /* Source circular buffer size. Source does not circular, set to 0*/
    Dma_CBSize desSize;            /* Destination circular buffer size. Destination does not circular, set to 0*/
    boolean desRollbackHaltEn;     /* Destination address rollback halt enable */
} Dma_CircularBufferConfig;

/* Struct for channel linked list item */
typedef struct
/* #Violation: dma_hal_h_REF_1 */
/* #Violation: dma_hal_h_REF_5 */
{
    DMA_CH_SRCADDR linkedListItemSrcAddr; /* Linked list item source address */
    DMA_CH_DESTADDR linkedListItemDestAddr; /* Linked list item destination address */
    DMA_CH_LLIREG linkedListItemLliReg;   /* Linked list item register */
    DMA_CH_CONTROL linkedListItemCtrl;    /* Linked list item control */
    DMA_CH_EXPLLICRC linkedListItemCRC;   /* Linked list item CRC */
} Dma_LinkedListItem;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: dma_hal_h_REF_6 */
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dma_hal_h_REF_7 */
#include "Dma_MemMap.h"
/**********************************************************************************************************************
 * Function:     Dma_Hal_ResetDma
 * Description:  Reset one specific DMA module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: Module reset successfully, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_ResetDma(DMA_MODULE *const pDma);
/**********************************************************************************************************************
 * Function:     Dma_Hal_DisableDma
 * Description:  Disable one specific DMA module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If dma is disabled, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_DisableDma(DMA_MODULE *const pDma);
/**********************************************************************************************************************
 * Function:     Dma_Hal_EnableDma
 * Description:  Enable one specific DMA module
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If dma is enabled, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_EnableDma(DMA_MODULE *const pDma);
/**********************************************************************************************************************
 * Function:     Dma_Hal_DeInitChannel
 * Description:  Restore channel register values to default values
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If channel register values is Restored, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *  2024/07/17    01254     To be compatible with THA6412, add resume halt register
 *********************************************************************************************************************/
extern boolean Dma_Hal_DeInitChannel(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_DeInitChannelWithCRC
 * Description:  Restore channel register values to default values, and restore CRCCONFIG and EXPLLICRC register
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       Only the security core can be used
 * History:
 *  Date          Author    Modified
 *  2025/03/25    01369    Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_DeInitChannelWithCRC(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_EnableChannel
 * Description:  Enable channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the dma channel is enabled, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_EnableChannel(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_DisableChannel
 * Description:  Disable channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern void Dma_Hal_DisableChannel(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_SafeDisableChannel
 * Description:  Safety disable channel, will not lose data of DMA FIFO
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the dma channel is disabled, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_SafeDisableChannel(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_SuspendChannel
 * Description:  Suspend channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the dma channel is suspended, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_SuspendChannel(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_ResumeChannel
 * Description:  Resume suspend channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If the dma channel is resumed, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_ResumeChannel(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_InitChannelTransfer
 * Description:  Initial channel transfer configuration, these are the most basic configurations,
 *               Initialization will enable terminal count interrupts and mask terminal count and error interrupts.
 *               Used before channel transmission
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               pConfig: Channel transfer configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If channel transfer configuration is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_InitChannelTransfer(DMA_MODULE *const pDma, uint8 channelID,
                                        const Dma_ChannelTransferConfig *const pConfig);
/**********************************************************************************************************************
 * Function:     Dma_Hal_ReInitChannelTransfer
 * Description:  Quickly reinitialize the current channel.
 *               Configure as the configuration for the last transmission on this channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/11/15    01254     Create
 *********************************************************************************************************************/
extern void Dma_Hal_ReInitChannelTransfer(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_GetRemainderTransferNum
 * Description:  return remaining transfer numbers
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       uint16: number: current remaining transfer numbers
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern uint16 Dma_Hal_GetRemainderTransferNum(const DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_SetTransferSizeThreshold
 * Description:  set transfer size threshold
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               thr: transfer size threshold value
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If configuration is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_SetTransferSizeThreshold(DMA_MODULE *const pDma, uint8 channelID, uint16 thr);
/**********************************************************************************************************************
 * Function:     Dma_Hal_InitShadowOperation
 * Description:  Initial channel initial register, these registers are also used as shadow operation registers,
 *               use before shadow operation
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               pConfig: Initial register configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If shadow operate configuration is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_InitShadowOperation(DMA_MODULE *const pDma, uint8 channelID,
                                        const Dma_ShadowOperationConfig *const pConfig);
/**********************************************************************************************************************
 * Function:     Dma_Hal_WriteLinkedListItem
 * Description:  Write linked list item to memory, can be used to build linked lists
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               pConfig: linked list item configuration
 * Inout:        pAddr: linked list item address
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern void Dma_Hal_WriteLinkedListItem(const DMA_MODULE *const pDma, uint8 channelID, Dma_LinkedListItem *const pAddr,
                                        const Dma_LinkedListItemConfig *const pConfig);
/**********************************************************************************************************************
 * Function:     Dma_Hal_InitLinkedListItem
 * Description:  Initial linked list item, use before linked list transmission
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               pLliAddr: linked list item address
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_InitLinkedListItem(DMA_MODULE *const pDma, uint8 channelID, const Dma_LinkedListItem *const pLliAddr);
/**********************************************************************************************************************
 * Function:     Dma_Hal_InitLinkedListItemWithCRC
 * Description:  Initial linked list item and enable CRC, use before linked list transmission
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               pLliAddr: Pointer to linked list item address
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       Only the security core can be used
 * History:
 *  Date          Author    Modified
 *  2025/03/25    01369     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_InitLinkedListItemWithCRC(DMA_MODULE *const pDma, uint8 channelID, const Dma_LinkedListItem *const pLliAddr);
/**********************************************************************************************************************
 * Function:     Dma_Hal_InitMatchPattern
 * Description:  Initial match pattern register, Initialization will enable match pattern interrupts
 *               and mask match pattern interrupts.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               pConfig: Match pattern configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If match pattern init is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_InitMatchPattern(DMA_MODULE *const pDma, uint8 channelID, const Dma_MatchPatternConfig *const pConfig);
/**********************************************************************************************************************
 * Function:     Dma_Hal_InitDoubleBuffer
 * Description:  Initial double buffer
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               pConfig: Double buffer configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If double buffer init is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_InitDoubleBuffer(DMA_MODULE *const pDma, uint8 channelID, const Dma_DoubleBufferConfig *const pConfig);
/**********************************************************************************************************************
 * Function:     Dma_Hal_InitCircularBuffer
 * Description:  Initial circular buffer, Initialization will enable circular buffer interrupts
 *               and mask circular buffer interrupts.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               pConfig: Circular buffer configuration
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If circular buffer init is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_InitCircularBuffer(DMA_MODULE *const pDma, uint8 channelID,
                                       const Dma_CircularBufferConfig *const pConfig);
/**********************************************************************************************************************
 * Function:     Dma_Hal_EnableDaisyChain
 * Description:  Enable daisy chain channel, used before daisy chain transmission
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If enable daisy chain channel is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_EnableDaisyChain(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_DisableDaisyChain
 * Description:  Disable daisy chain channel, used before daisy chain transmission
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If enable daisy chain channel is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_DisableDaisyChain(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_EnableContinuousMode
 * Description:  Enable continuous mode, used before overload mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If enable continuous mode is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_EnableContinuousMode(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_DisableContinuousMode
 * Description:  Disable continuous mode, used before overload mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern void Dma_Hal_DisableContinuousMode(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_SoftwareSwitchDoubleBuffer
 * Description:  Software switch double buffer
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern void Dma_Hal_SoftwareSwitchDoubleBuffer(DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_GetDoubleBufferFrozenStatus
 * Description:  Get channel double buffer frozen status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       Dma_DoubleBufferFrozenStatus: status: Buffer0 and buffer1 frozen status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern Dma_DoubleBufferFrozenStatus Dma_Hal_GetDoubleBufferFrozenStatus(const DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_ClearDoubleBufferFrozenStatus
 * Description:  Clear channel double buffer frozen status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               sel: Select the buffer to clear
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/11/15    01254     Create
 *********************************************************************************************************************/
extern void Dma_Hal_ClearDoubleBufferFrozenStatus(DMA_MODULE *const pDma, uint8 channelID,
                                                  Dma_DoubleBufferStatusSel sel);
/**********************************************************************************************************************
 * Function:     Dma_Hal_EnableInterrupt
 * Description:  Enable channel interrupt. Include terminal count interrupt, source circular buffer,
 *               destination circular buffer interrupt, match pattern interrupt, bus error interrupt,
 *               transfer size threshold interrupt.
 *               Can enable multiple interrupt states at the same time
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               interrupt: select interrupt,
 *               multiple interrupt bits can be used after or operation.
 *               The interrupt value can be set to:
 *               DMA_CHANNELINTERRUPT_TC
 *               DMA_CHANNELINTERRUPT_ERROR
 *               DMA_CHANNELINTERRUPT_SCB
 *               DMA_CHANNELINTERRUPT_DCB
 *               DMA_CHANNELINTERRUPT_PAT
 *               DMA_CHANNELINTERRUPT_THR
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If enable interrupt is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_EnableInterrupt(DMA_MODULE *const pDma, uint8 channelID, uint8 interrupt);
/**********************************************************************************************************************
 * Function:     Dma_Hal_DisableInterrupt
 * Description:  Disable channel interrupt. Include terminal count interrupt, source circular buffer,
 *               destination circular buffer interrupt, match pattern interrupt, bus error interrupt,
 *               transfer size threshold interrupt.
 *               Can disable multiple interrupt states at the same time
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               interrupt: select interrupt,
 *               multiple interrupt bits can be used after or operation.
 *               The interrupt value can be set to:
 *               DMA_CHANNELINTERRUPT_TC
 *               DMA_CHANNELINTERRUPT_ERROR
 *               DMA_CHANNELINTERRUPT_SCB
 *               DMA_CHANNELINTERRUPT_DCB
 *               DMA_CHANNELINTERRUPT_PAT
 *               DMA_CHANNELINTERRUPT_THR
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If disable interrupt is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_DisableInterrupt(DMA_MODULE *const pDma, uint8 channelID, uint8 interrupt);
/**********************************************************************************************************************
 * Function:     Dma_Hal_GetInterruptStatus
 * Description:  Get channel interrupt status. Include terminal count interrupt, source circular buffer,
 *               destination circular buffer interrupt, match pattern interrupt, bus error interrupt,
 *               transfer size threshold interrupt.
 *               Can get multiple interrupt states at the same time
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               interrupt: select interrupt, multiple status bits can be used after or operation.
 *               The interrupt value can be set to:
 *               DMA_CHANNELINTERRUPT_TC
 *               DMA_CHANNELINTERRUPT_ERROR
 *               DMA_CHANNELINTERRUPT_SCB
 *               DMA_CHANNELINTERRUPT_DCB
 *               DMA_CHANNELINTERRUPT_PAT
 *               DMA_CHANNELINTERRUPT_THR
 * Inout:        None
 * Output:       None
 * Return:       uint8: interrupt: If the interrupt state is set, the corresponding interrupt status bit is 1
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern uint8 Dma_Hal_GetInterruptStatus(const DMA_MODULE *const pDma, uint8 channelID, uint8 interrupt);
/**********************************************************************************************************************
 * Function:     Dma_Hal_GetStatus
 * Description:  Get channel status. Include terminal count status, source circular status,
 *               destination circular buffer status, match pattern status, bus error status,
 *               transfer size threshold status.
 *               Can get multiple states at the same time
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               stat: select interrupt,
 *               multiple status bits can be used after or operation.
 *               The stat value can be set to:
 *               DMA_CHANNELSTATUS_TC
 *               DMA_CHANNELSTATUS_ERROR
 *               DMA_CHANNELSTATUS_SCB
 *               DMA_CHANNELSTATUS_DCB
 *               DMA_CHANNELSTATUS_PAT
 *               DMA_CHANNELSTATUS_THR
 * Inout:        None
 * Output:       None
 * Return:       uint8: stat: If the selected state is set, the corresponding status bit is 1
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern uint8 Dma_Hal_GetStatus(const DMA_MODULE *const pDma, uint8 channelID, uint8 stat);
/**********************************************************************************************************************
 * Function:     Dma_Hal_ClearStatus
 * Description:  Clear channel status. Include terminal count status, source circular status,
 *               destination circular buffer status, match pattern status, bus error status,
 *               transfer size threshold status.
 *               Can clear multiple states at the same time
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               stat: select status, multiple status bits can be used after or operation.
 *               The stat value can be set to:
 *               DMA_CHANNELSTATUS_TC\DMA_CHANNELINTERRUPT_TC
 *               DMA_CHANNELSTATUS_ERROR\DMA_CHANNELINTERRUPT_ERROR
 *               DMA_CHANNELSTATUS_SCB\DMA_CHANNELINTERRUPT_SCB
 *               DMA_CHANNELSTATUS_DCB\DMA_CHANNELINTERRUPT_DCB
 *               DMA_CHANNELSTATUS_PAT\DMA_CHANNELINTERRUPT_PAT
 *               DMA_CHANNELSTATUS_THR\DMA_CHANNELINTERRUPT_THR
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern void Dma_Hal_ClearStatus(DMA_MODULE *const pDma, uint8 channelID, uint8 stat);
/**********************************************************************************************************************
 * Function:     Dma_Hal_SetChannelAccessMode
 * Description:  Set DMA channel access mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               mode: user mode or privileged mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: status: If set DMA channel access mode is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_SetChannelAccessMode(DMA_MODULE *const pDma, uint8 channelID, Dma_AccessMode mode);
/**********************************************************************************************************************
 * Function:     Dma_Hal_InitTimeStamp
 * Description:  Initial DMA time stamp function.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               clkDiv: clock division
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       Only the security core can be used
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *  2025/03/25    01369     Add usage restrictions
 *********************************************************************************************************************/
extern boolean Dma_Hal_InitTimeStamp(DMA_MODULE *const pDma, uint8 clkDiv);
/**********************************************************************************************************************
 * Function:     Dma_Hal_DisableTimeStamp
 * Description:  Disable DMA time stamp function.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       Only the security core can be used
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *  2025/03/25    01369     Add usage restrictions
 *********************************************************************************************************************/
extern boolean Dma_Hal_DisableTimeStamp(DMA_MODULE *const pDma);
/**********************************************************************************************************************
 * Function:     Dma_Hal_GetCurrentTimeStamp
 * Description:  Get current time stamp.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 * Inout:        None
 * Output:       None
 * Return:       uint32: value: current time stamp value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern uint32 Dma_Hal_GetCurrentTimeStamp(const DMA_MODULE *const pDma);
/**********************************************************************************************************************
 * Function:     Dma_Hal_GetTransferTimeStamp
 * Description:  Get transmission start or end timestamp value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               sel: select transfer start or end time stamp
 * Inout:        None
 * Output:       None
 * Return:       uint32: value: transfer start or end time stamp value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern uint32 Dma_Hal_GetTransferTimeStamp(const DMA_MODULE *const pDma, uint8 channelID, Dma_TransferTimeStampSel sel);
/**********************************************************************************************************************
 * Function:     Dma_Hal_GetAndClearTransferTimeStampValidStatus
 * Description:  Get and clear transmission start or end timestamp valid status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               sel: select transfer start or end time stamp
 * Inout:        None
 * Output:       None
 * Return:       Dma_TransferTimeStampStatus:
 *                       DMA_TRANSFERTIMESTAMP_INVALID: Transfer time stamp invalid
 *                       DMA_TRANSFERTIMESTAMP_VALID: Transfer time stamp valid
 *                       DMA_TRANSFERTIMESTAMP_BOTH_VALID_SEPROTECT_ERROR: Both transfer time stamp valid and SE protection error,
 *                                                                         SE protection error refers to the failure to unlock/lock
 *                                                                         the SE protection when clearing the transfer time stamp valid status
 * Others:       Only the security core can be used
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *  2025/03/25    01369     Add usage restrictions
 *  2025/09/12    01359     Modify the return value type
 *********************************************************************************************************************/
extern Dma_TransferTimeStampStatus Dma_Hal_GetAndClearTransferTimeStampValidStatus(DMA_MODULE *const pDma, uint8 channelID,
                                                               Dma_TransferTimeStampSel sel);
/**********************************************************************************************************************
 * Function:     Dma_Hal_GetAndClearCrcErrorStatus
 * Description:  Get and clear CRC error status, the status include data error and LLI error.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               sel: select data error or LLI error
 * Inout:        None
 * Output:       None
 * Return:       Dma_CrcErrorStatus:
 *                       DMA_CRCERRORSTATUS_NOCRC_ERROR: No CRC error
 *                       DMA_CRCERRORSTATUS_CRC_ERROR: CRC error
 *                       DMA_CRCERRORSTATUS_BOTH_CRC_SEPROTECT_ERROR: Both CRC error and SE protection error, SE protection
 *                                                                    error refers to the failure to unlock/lock the SE protection
 *                                                                    when clearing the CRC error status
 * Others:       Only the security core can be used
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *  2025/03/25    01369     Add usage restrictions
 *  2025/09/12    01359     Modify the return value type
 *********************************************************************************************************************/
extern Dma_CrcErrorStatus Dma_Hal_GetAndClearCrcErrorStatus(DMA_MODULE *const pDma, uint8 channelID, Dma_CrcErrorSel sel);
/**********************************************************************************************************************
 * Function:     Dma_Hal_GetChannelEnableStatus
 * Description:  Get channel enable status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 * Inout:        None
 * Output:       None
 * Return:       boolean: stat: if channel is enable, the stat is TRUE
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/12    01254     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_GetChannelEnableStatus(const DMA_MODULE *const pDma, uint8 channelID);
/**********************************************************************************************************************
 * Function:     Dma_Hal_SetBufferable
 * Description:  Set DMA channel bufferable selection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               sel: Non-bufferable or bufferable
 * Inout:        None
 * Output:       None
 * Return:       boolean: ret: If set DMA channel bufferable is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/07/10    01359     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_SetBufferable(DMA_MODULE *const pDma, uint8 channelID, Dma_BufferableSel sel);
/**********************************************************************************************************************
 * Function:     Dma_Hal_SetCacheable
 * Description:  Set DMA channel cacheable selection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (When configuring different DMA modules or different channels of the same DMA module,
 *               this function is a reentrant function; in other cases, it is a non-reentrant function)
 * Input:        pDma: Pointer to DMA module
 *               channelID: Channel ID
 *               sel: Non-cacheable or cacheable
 * Inout:        None
 * Output:       None
 * Return:       boolean: ret: If set DMA channel cacheable is succeeded, the status is true
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/07/10    01359     Create
 *********************************************************************************************************************/
extern boolean Dma_Hal_SetCacheable(DMA_MODULE *const pDma, uint8 channelID, Dma_CacheableSel sel);

/* #Violation: dma_hal_h_REF_6 */
#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: dma_hal_h_REF_7 */
#include "Dma_MemMap.h"
#endif /* DMA_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

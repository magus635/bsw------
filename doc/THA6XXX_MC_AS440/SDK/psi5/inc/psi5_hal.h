/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    psi5_hal.h
 * Author:      01849
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: PSI5 hardware abstraction layer source file.
 *              This file contains implementations for PSI5 hardware abstraction layer.
 *********************************************************************************************************************/
#ifndef PSI5_HAL_H_
#define PSI5_HAL_H_

/*
* #Violation Summary
*
* #psi5_hal_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #psi5_hal_h_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #psi5_hal_h_REF_3:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
* #psi5_hal_h_REF_4:MISRAC2012-Dir-4.8
* Justification:Apply such struct/union definitions to simplify the code structure and reduce the code complexity.
*
* #psi5_hal_h_REF_5:CERTC-DCL12-C;
* Justification:Apply such struct/union definitions to simplify the code structure and reduce the code complexity.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "psi5_std.h"
#include "Platform_Types.h"
#include "rcc_hal.h"
#include "tha6_cfg.h"

#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Enable */
#define SYNCENABLE (1U)
/* Disable */
#define SYNCDISABLE (0U)
/* Assert send range judge */
/* #Violation: psi5_hal_h_REF_1 */
#define PSI5_ASSERTSEND_RANGEJUDGE (4U)
/* Interrupt parameter */
/* #Violation: psi5_hal_h_REF_1 */
#define PSI5_INTERRUPTCHANNEL_MAX (0x0003FFFFU)
/* #Violation: psi5_hal_h_REF_1 */
#define PSI5_INTERRUPT_MAX (0x0000000FU)
/* Frame offset */
/* Frame 4 */
#define PSI5_XXLONG_LONG1_PAYLOADOFFSET (9U)
#define PSI5_XXLONG_LONG1_RADDROFFSET (3U)
#define PSI5_XXLONG_LONG2_PAYLOADOFFSET (5U)
#define PSI5_XXLONG_LONG2_RADDROFFSET (3U)
#define PSI5_XXLONG_XLONG_PAYLOADOFFSET (11U)
#define PSI5_XXLONG_XLONG_RADDROFFSET (3U)
#define PSI5_XXLONG_BLEN (20U)
/* Frame 1-3 */
#define PSI5_LONG1_PAYLOADOFFSET (6U)
#define PSI5_LONG2_PAYLOADOFFSET (2U)
#define PSI5_XLONG_PAYLOADOFFSET (8U)
#define PSI5_SHORT_BLEN (0U)
#define PSI5_XLONG_BLEN (16U)
#define PSI5_LONG_BLEN (10U)
/* Protection bit offset */
#define PSI5_RSP_PROT_OFFSET (13U)
/* Detect free bit offset */
#define PSI5_DEC_FREE_OFFSET (5U)
/* Data protection bit offset */
#define PSI5_PROT_OFFSET (3U)
/* TXFIFO depth value */
/* #Violation: psi5_hal_h_REF_1 */
#define PSI5_TXFIFO_DEPTH (4U)
/* RXFIFO depth value */
/* #Violation: psi5_hal_h_REF_1 */
#define PSI5_RXFIFO_DEPTH (96U)
/* ENH_PROT limit value */
/* #Violation: psi5_hal_h_REF_1 */
#define PSI5_ENH_PROT_LIMIT (3U)
/* TS_PRESCALER limit value */
/* #Violation: psi5_hal_h_REF_1 */
#define PSI5_TS_PRESCALER_LIMIT (1U)
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
/* Brief Tx command configuration structure */
/* #Violation: psi5_hal_h_REF_4 */
/* #Violation: psi5_hal_h_REF_5 */
typedef struct
{
    uint8 txCommandChTsycnPeriod;    /* Controls the sync width in internal clock, the value ranges from 0 to 255 */
    uint8 txCommandChPwmAdd;         /* Controls PWM add width, this time is added to pulse width, the value
                                        ranges from 0 to 255 */
    uint8 txCommandChSyncGap;        /* Controls gap between two sync pulse for ECU to sensor, the value ranges
                                        from 0 to 255 */
    uint8 txCommandChSync_SlotGap;   /* Controls the gap between sync pulse and first slot in prescaler output clock,
                                        the value ranges from 0 to 255 */
    uint8 txCommandChSlot_Post;      /* Controls the gap between last slot and sync pulse in prescaler output clock, the
                                        value ranges from 0 to 255 */
    uint8 txCommandChSlot_Gap;       /* Controls the gap between two slots in prescaler output clock, the value ranges
                                        from 0 to 255 */
    Psi5_ChSlot_Width chSlot_Width;  /* Controls the width of slot in number of bits from Start bits to end bits */
} Psi5_TxCommand_Config;


/* Brief Tx sync configuration structure */
/* #Violation: psi5_hal_h_REF_4 */
/* #Violation: psi5_hal_h_REF_5 */
typedef struct
{
    uint8 txSyncChTsycnPeriod;     /* Controls the sync width in internal clock, the value ranges from 0 to 255 */
    uint8 txSyncChSync_SlotGap;    /* Controls the gap between sync pulse and first slot in prescaler output clock,
                                      the value ranges from 0 to 255 */
    uint8 txSyncChSlot_Post;       /* Controls the gap between last slot and sync pulse in prescaler output clock, the
                                      value ranges from 0 to 255 */
    uint8 txSyncChSlot_Gap;        /* Controls the gap between two slots in prescaler output clock, the value ranges
                                      from 0 to 255 */
    Psi5_ChSlot_Width chSlot_Width;/* Controls the width of slot in number of bits from Start bits to end bits */
} Psi5_TxSync_Config;

/* Brief transmit control configuration structure */
/* #Violation: psi5_hal_h_REF_4 */
/* #Violation: psi5_hal_h_REF_5 */
typedef struct
{
    Psi5_TsyncEn tsyncEnabled;              /* Whether the sync is turned on or not */
    Psi5_TsyncMode tsyncMode;               /* Whether the sync mode */
    Psi5_Startpat startpatSelected;         /* Start pattern select */
    Psi5_EnhProt enhancedProtocolSelected;  /* Whether the enhanced protocol is selected or not */
    Psi5_AutoStartSeque startSequenceGenerationEnabled;/* Whether the start sequence generation is turned on or not */
    Psi5_AutoStuff bitStuffingEnabled;      /* Whether the bit stuffing is turned on or not */
    Psi5_CrcMode crcGenerationEnabled;      /* Whether the crc generation is turned on or not */
    uint8 fifoThresholdLevel;               /* The fifo warning level, the maximum value is 4 */
    Psi5_Prot responseProt;                 /* The crc or parity selection for sensor response to ECU to sensor */
} Psi5_TransmitControl;

/* Brief module configuration structure */
/* #Violation: psi5_hal_h_REF_4 */
/* #Violation: psi5_hal_h_REF_5 */
typedef struct
{
    uint16 timestampPrescaler;  /* Brief specifies timestamp prescaler based i_clk, the value ranges from 1 to 65536 */
    uint8 glitchFilter;         /* Brief specifies glitch filter, the value ranges from 0 to 255 */
    boolean dmaEn;              /* Enable/disable DMA Tx and Rx */
} Psi5_ModuleConfig;

/* Brief channel configuration structure */
/* #Violation: psi5_hal_h_REF_4 */
/* #Violation: psi5_hal_h_REF_5 */
typedef struct
{
    PSI5_MODULE *module;                 /* Brief specifies pointer to the Psi5 module handle */
    uint8 decFree;                       /* Brief specifies detected free, the value ranges from 0 to 255 */
    Psi5_ChannelId channelId;            /* Brief specifies the channel index */
    uint16 channelPrescaler;             /* Brief specifies channel prescaler based i_clk, the value ranges
                                            from 1 to 65536 */
    Psi5_ReceiveControl receiveControl;  /* Brief specifies the configuration for reception */
    Psi5_TransmitControl sendControl;    /* Brief specifies the configuration for transmission */
} Psi5_ChannelInitConfig;

/* Brief data frame structure for sensor data */
/* #Violation: psi5_hal_h_REF_4 */
/* #Violation: psi5_hal_h_REF_5 */
typedef struct
{
    Psi5_RxType dataType; /* Brief specifies data frame structure of sensor data type */
    uint8 frameLength;    /* Brief specifies data frame structure of sensor data length */
    Psi5_Slot slotId;     /* Brief specifies data frame structure of sensor slot ID */
    uint8 msgBit;         /* Brief specifies data frame structure of serial message bit */
    uint8 rxTIE;          /* Brief specifies data frame structure of serial TIE bit */
    uint8 rxNBI;          /* Brief specifies data frame structure of serial NBI bit */
    uint8 rxMEI;          /* Brief specifies data frame structure of serial MEI bit */
    uint8 rxNFI;          /* Brief specifies data frame structure of serial NFI bit */
    uint32  payload;      /* Brief specifies data frame structure of sensor data pay load */
    uint32 timestamp;     /* Brief specifies data frame structure of time stamp */
} Psi5_ReceiveFrame;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: psi5_hal_h_REF_1 */
#define PSI5_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: psi5_hal_h_REF_2 */
#include "Psi5_MemMap.h"
/**********************************************************************************************************************
 * Function:     Psi5_Hal_InitModule
 * Description:  Initialize the psi5 module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module.
 *               pConfig: pointer to the psi5 module configuration.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern void Psi5_Hal_InitModule(PSI5_MODULE *const pPsi5, const Psi5_ModuleConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_InitChannel
 * Description:  Initialize the psi5 channel.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different PSI5 channel, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pConfig: pointer to the psi5 channel initial configuration.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern void Psi5_Hal_InitChannel(const Psi5_ChannelInitConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_ResetModule
 * Description:  Resets the specified PSI5 module.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       Rcc_ErrorFlag: Error indicating flag.
 * Others:       None
 * History:
 *  Date         Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern Rcc_ErrorFlag Psi5_Hal_ResetModule(void);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_ReadChannelData
 * Description:  Read the channel data.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different PSI5 channel, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               pFrame: pointer to the psi5 module receive frame.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern void Psi5_Hal_ReadChannelData(const PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                     Psi5_ReceiveFrame *const pFrame);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_SendChannelData
 * Description:  Send the channel data.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different PSI5 channel, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               pFrame: pointer to the psi5 module transmit frame.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern void Psi5_Hal_SendChannelData(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                     const Psi5_TransmitFrame *const pFrame);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_Txcommand_Config
 * Description:  Set the tx command config.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different PSI5 channel, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               config: pointer to the psi5 module Tx commamnd config.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern void Psi5_Hal_TxCommand_Config(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                      const Psi5_TxCommand_Config *const config);
/**********************************************************************************************************************
 * Function:     Psi5_Hal_TxSync_Config
 * Description:  Set the tx sync config.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different PSI5 channel, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               config: pointer to the psi5 module Tx sync config.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern void Psi5_Hal_TxSync_Config(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                   const Psi5_TxSync_Config *const config);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_RxAsync_Config
 * Description:  Set the rx async config.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different PSI5 channel, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               config: pointer to the receive control slot width configuration.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/11/07    01849     Create
 *********************************************************************************************************************/
extern void Psi5_Hal_RxAsync_Config(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                    const Psi5_ChSlot_Width *const config);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_EnableTsyncPulse
 * Description:  Synchronous pulse signal on.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different PSI5 channel, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               receiveControl: pointer to the psi5 receive control parameter.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
extern void Psi5_Hal_EnableTsyncPulse(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                      const Psi5_ReceiveControl *const receiveControl);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_DisableTsyncPulse
 * Description:  Synchronous pulse signal off.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different PSI5 channel, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
extern void Psi5_Hal_DisableTsyncPulse(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_GetInterruptStatus
 * Description:  Get the interrupt status information.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pPsi5: pointer to the psi5 module.
 * Inout:        None
 * Output:       None
 * Return:       uint32: Return the interrupt status information.
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
extern uint32 Psi5_Hal_GetInterruptStatus(const PSI5_MODULE *const pPsi5);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_ClearInterrupt
 * Description:  Clear interrupt signal.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pPsi5: pointer to the psi5 module.
 *               interrupt: interrupt source number, set valid from typedef enum Psi5_IrqSource.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
extern void Psi5_Hal_ClearInterrupt(PSI5_MODULE *const pPsi5, uint32 interrupt);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_SetChannelInterrupt
 * Description:  Set whether channel interrupt is enabled.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(When operation different PSI5 channel, this function is a reentrant function;
 *               in other cases, it is a non-reentrant function)
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               enable: the Interrupt request is enable or disable.
 *               interrupt: interrupt source number, set valid from typedef enum Psi5_ChIrqSource.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
extern void Psi5_Hal_SetChannelInterrupt(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                         Psi5_IrqRequest enable, uint32 interrupt);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_GetChannelInterruptFlag
 * Description:  Get the specified channel interrupt status information.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               interrupt: interrupt source number.
 * Inout:        None
 * Output:       None
 * Return:       Psi5_InterruptFlag: Return the specified interrupt status information.
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
extern Psi5_InterruptFlag Psi5_Hal_GetChannelInterruptFlag(const PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId,
                                                           Psi5_ChIrqSource interrupt);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_GetChannelInterruptStatus
 * Description:  Get the interrupt status information.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 * Inout:        None
 * Output:       None
 * Return:       uint32: Return the interrupt status information.
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
extern uint32 Psi5_Hal_GetChannelInterruptStatus(const PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_ClearChannelInterrupt
 * Description:  Clear channel interrupt signal.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               interrupt: interrupt source number, set valid from typedef enum Psi5_ChIrqSource.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
extern void Psi5_Hal_ClearChannelInterrupt(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId, uint32 interrupt);

/**********************************************************************************************************************
 * Function:     Psi5_Hal_FlushFifo
 * Description:  Set fifo flush register.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pPsi5: pointer to the psi5 module.
 *               channelId: channel number of operation.
 *               fifoFlush: fifo flush source number, set valid from typedef enum Psi5_FifoFlushType.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
extern void Psi5_Hal_FlushFifo(PSI5_MODULE *const pPsi5, Psi5_ChannelId channelId, uint32 fifoFlush);

/* #Violation: psi5_hal_h_REF_1 */
#define PSI5_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: psi5_hal_h_REF_2 */
#include "Psi5_MemMap.h"

#endif /* PSI5_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

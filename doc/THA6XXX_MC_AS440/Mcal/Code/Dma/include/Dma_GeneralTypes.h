/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dma_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DMA
*
*   brief                 : This file contains all type definitions of Dma Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Dma_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
*   code complexity.
*
*#Dma_GeneralTypes_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
*   code complexity.
*
*/

#ifndef DMA_GENERALTYPES_H_
#define DMA_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dma_Cfg.h"
#include "Mcall.h"
#include "dma_hal.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* Type definition for HW unit */
typedef uint8                                Dma_HwUnitType;
/* Type definition for channel ID(Logical channel ID) */
typedef uint8                                Dma_ChannelType;
/* Type definition for transfer */
typedef uint8                                Dma_TransferType;
#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
/* Type definition for index of the linked list ID in each channel */
typedef Dma_TransferType                     Dma_LinkedListType;
#endif /* \(DMA_CFG_LINKEDLIST_EN == STD_ON) */
#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
/* Type definition for the shadowing operation ID in each channel */
typedef Dma_TransferType                     Dma_ShadowingType;
#endif /* \(DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) */
#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
/* Type definition for the double buffer ID in each channel */
typedef Dma_TransferType                     Dma_DoubleBufferType;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
/* Type definition for the circular buffer ID in each channel */
typedef Dma_TransferType                     Dma_CircularBufferType;
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */
#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
/* Type definition for the pattern match ID in each channel */
typedef Dma_TransferType                     Dma_PatternType;
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */

/* Type redefinition for linked list buffer */
typedef Dma_LinkedListItem                   Dma_LliBufType;
/* Type redefinition for linked list configuration */
typedef Dma_LinkedListItemConfig             Dma_LliCfgType;


/****************************************************************************************************
**                          Global Enumeration Definitions                                         **
****************************************************************************************************/
#if (DMA_DEV_ERROR_DETECT == STD_ON)
/* DMA driver initialization status */
typedef enum
{
    DMA_UNINITIALIZE = 0U,
    DMA_INITIALIZED
} Dma_InitType;
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

/* Type definition of the channel transfer cancel method */
typedef enum
{
    /* Directly cancel an on-going channel transfer */
    DMA_CH_CANCEL_DIRECT = 0U,
    /* Safely cancel an on-going channel transfer */
    DMA_CH_CANCEL_SAFE
} Dma_ChCancelType;

/* Type definition of the channel interrupt */
typedef enum
{
    /* Terminal count interrupt */
    DMA_CH_INT_TC = DMA_CHANNELINTERRUPT_TC
    /* Error interrupt */
    ,DMA_CH_INT_ERROR = DMA_CHANNELINTERRUPT_BUSERROR
#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
    /* Source circular buffer rollback interrupt */
    ,DMA_CH_INT_SCB = DMA_CHANNELINTERRUPT_SCB
    /* Destination circular buffer rollback interrupt */
    ,DMA_CH_INT_DCB = DMA_CHANNELINTERRUPT_DCB
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON) */
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */
#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
    /* Data pattern matched interrupt */
    ,DMA_CH_INT_PATTERN = DMA_CHANNELINTERRUPT_PAT
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON) */
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */
#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
    /* Remaining transfer count threshold interrupt */
    ,DMA_CH_INT_REMAINING_COUNT = DMA_CHANNELINTERRUPT_THR
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN == STD_ON) */
} Dma_ChEventType;

/* Type definition for the event status of channel transfer */
typedef enum
{
    /* Not any event occurred */
    DMA_CH_NONE                   = 0x0000U,
    /* bit1 - 0x01 - channel transfer completed(Terminal count = 0) */
    DMA_CH_TRANSFER_COMPLETE      = 0x0001U,
    /* bit2 - 0x02 - Some error occurred during the channel transfer */
    DMA_CH_ERROR                  = 0x0002U,
#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
    /* bit3 - 0x04 - Source circular buffer rollback event occurred */
    DMA_CH_SCB                    = 0x0004U,
    /* bit4 - 0x08 - Destination circular buffer rollback event occurred */
    DMA_CH_DCB                    = 0x0008U,
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */
#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
    /* bit5 - 0x10 - Data pattern matched */
    DMA_CH_PATTERN_MATCHED        = 0x0010U,
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */
    /* bit6 - 0x20 - Channel is transferring */
    DMA_CH_TRANSFERRING           = 0x0040U,
    /* bit7 - 0x40 - Channel is in suspend status, API Dma_ChannelPause() called */
    DMA_CH_SUSPENDED              = 0x0080U
} Dma_ChStatusType;

/* Type definition for the double buffer frozen status */
typedef enum
{
    /* Only buffer0 frozen */
    DMA_CH_DB_FROZEN_BUF0 = DMA_DOUBLEBUFFERFROZENSTATUS_BUFFER0_FROZEN,
    /* Only buffer1 frozen */
    DMA_CH_DB_FROZEN_BUF1 = DMA_DOUBLEBUFFERFROZENSTATUS_BUFFER1_FROZEN,
    /* Both buffer0 and buffer1 are frozen, but buffer0 was frozen first */
    DMA_CH_DB_BOTH_FROZEN_BUF0 = DMA_DOUBLEBUFFERFROZENSTATUS_BOTH_FROZEN_BUFFER0FIRST,
    /* Both buffer0 and buffer1 are frozen, but buffer1 was frozen first */
    DMA_CH_DB_BOTH_FORZEN_BUF1 = DMA_DOUBLEBUFFERFROZENSTATUS_BOTH_FROZEN_BUFFER1FIRST,
} Dma_DblFrznStatusType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
/* Type definition for channel transfer configuration */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Source address configuration */
    Dma_ChannelAddressConfig             Source;
    /* Destination address configuration */
    Dma_ChannelAddressConfig             Destination;
    /* Transfer width configuration */
    Dma_ChannelTransferWidth             TransferWidth;
    /* Transfer size configuration: 0 ~ 4095 */
    uint16                               TransferSize;
} Dma_ChannelTransferType;
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

/* Type definition for global run-time variables set */
typedef struct
{
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
    /* Pointer to the array that index of the configuration set in multiple configuration sets,
     * transfer or linked list item configuration */
    Dma_TransferType                     *ChCurrTransferPtr;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
#if ((DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) && (DMA_CFG_MULTI_SHADOWING_NUM != 0U))
    /* Pointer to the array that index of the configuration set in multiple configuration sets,
     * shadowing operation configuration */
    Dma_ShadowingType                    *ChCurrShadowingPtr;
#endif /* \((DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) && (DMA_CFG_MULTI_SHADOWING_NUM != 0U)) */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    /* Pointer to the status of daisy chain */
    uint8                                *DcStatusPtr;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
    /* Pointer to the manually configured transfer data (array of pointers per channel) */
    Dma_ChannelTransferType              **ChTransManualPtr;
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */
    /* Pointer to the channel status */
    Dma_ChStatusType                     *ChStatusPtr;
} Dma_GlobalDataSetType;

/* Type definition for the mapping relationship between logical channel ID, HW unit,
 * physical channel and core */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Physical channel which the logical channel ID is mapped to */
    uint8                              PhyChannelId;
    /* HW unit which the logical channel ID is mapped to */
    Dma_HwUnitType                     HwUnitId;
    /* The index position of the logical channel in the Core "ChMapCoreId" */
    uint8                              CoreChIdx;
#if (DMA_CFG_MULTI_TRANSFER_NUM != 0U)
    /* Transfer index of channel, used to index the position of the array that
     * records multiple sets of configurations in current core */
    Dma_TransferType                   ChTransferIdx;
#endif /* \(DMA_CFG_MULTI_TRANSFER_NUM != 0U) */
#if ((DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) && (DMA_CFG_MULTI_SHADOWING_NUM != 0U))
    /* Pattern index of channel, used to index the position of the array that
     * records multiple sets of configurations in current core */
    Dma_ShadowingType                  ChShadowingIdx;
#endif /* \((DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) && (DMA_CFG_MULTI_SHADOWING_NUM != 0U)) */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    /* Daisy chain index, used to index the position of the daisy chain array */
    uint8                              CoreDcIdx;
    /* When this channel is end channel in daisy chain, used for flag the first channel
     * in the daisy chain. */
    Dma_ChannelType                    CoreDcFirstCh;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
    /* Core Id which the logical channel ID is mapped to */
    Mcal_CoreType                      ChMapCoreId;
} Dma_ChannelMapType;

#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
/* Type definition for linked list mapping relationship */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Total number of linked list items in this list */
    uint8                              LliMaxNum;
    /* Pointer to the list of linked list, this list containing transfer configuration parameter
     * IDs of the linked list that assigned */
    const Dma_TransferType             *LliToTransferIdPtr;
} Dma_LinkedListMapType;

/* Type definition for linked list configuration parameters of a channel */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Pointer to the Mapping list of shadowing to transfer and linked list */
    const Dma_LinkedListMapType        *LliMapInfoPtr;
    /* Pointer to the linked list buffer */
    Dma_LliBufType                     *LliBufPtr;
} Dma_ChLinkedListConfigType;
#endif /* \(DMA_CFG_LINKEDLIST_EN == STD_ON) */

#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
/* Type definition for shadow mapping relationship */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Transfer configuration parameter ID of the shadowing operation that assigned */
    Dma_TransferType                   ShadowToTransferId;
#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
    /* Linked list configuration parameter ID of the shadow operation that assigned,
     * If linked list is not used for this shadowing operation, this value shall be 0xFF */
    Dma_LinkedListType                 ShadowToLliId;
#endif /* \(DMA_CFG_LINKEDLIST_EN == STD_ON) */
} Dma_ShadowingMapType;
#endif /* \(DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) */

#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
/* Type definition for double buffer */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Pointer to the double buffer configuration parameters */
    const Dma_DoubleBufferConfig           DblBufConfig;
    /* Pointer to double buffer frozen notification function */
    void (*DmaDblFrznNotificationPtr)(Dma_ChannelType Channel,
                                      Dma_DblFrznStatusType DblFrznBufStatus);
} Dma_DoubleBufferConfigType;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */

#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
/* Type definition for daisy chain mapping relationship */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Total number of daisy chain in this list */
    uint8                             DcMaxNum;
    /* Pointer to the list of daisy chain, this list containing channel
     * IDs of the daisy chain that assigned */
    const Dma_ChannelType             *DcToChannelPtr;
} Dma_DaisyChainMapType;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */

/* Type definition for transfer configuration */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
    /* Point to double buffer configuration */
    Dma_DoubleBufferType                   ChDoubleBufferId;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
    /* Point to the circular buffer configuration */
    Dma_CircularBufferType                 ChCircularBufferId;
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */
#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
    /* Point to the pattern configuration */
    Dma_PatternType                        ChPatternId;
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */
#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
    /* If enable the linked list for this transfer, flag the linked list ID */
    Dma_LinkedListType                     ChLinkedListId;
#endif /* \(DMA_CFG_LINKEDLIST_EN == STD_ON) */
#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
    /* Remaining count of transfer */
    uint16                                 ChRemainCount;
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN == STD_ON) */
    /* Pointer to the transfer configuration parameters */
    const Dma_ChannelTransferConfig        ChTransferConfig;
} Dma_TransferConfigType;

/* Type definition for channel configuration */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Logical channel ID */
    uint8                                  ChannelId;
#if (DMA_CFG_CHANNEL_NO_TRANSFER_EN == STD_ON)
    /* Flag whether the transfer configuration exists status */
    boolean                                IsTransCfgExists;
#endif /* \(DMA_CFG_CHANNEL_NO_TRANSFER_EN == STD_ON) */
#if (DMA_DEV_ERROR_DETECT == STD_ON)
    /* Total number of transfer configuration set */
    Dma_TransferType                       ChTransferTotalNum;
#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
    /* Total number of shadowing configuration set */
    Dma_ShadowingType                      ChShadowTotalNum;
#endif /* \(DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) */
#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
    /* Total number of linked list configuration set */
    Dma_LinkedListType                     ChLliTotalNum;
#endif /* \(DMA_CFG_LINKEDLIST_EN == STD_ON) */
#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */
#if (DMA_CFG_INTERRUPT_EN == STD_ON)
    /* Bits for interrupt enable: 1 - enabled, 0 - disabled */
    uint8                                  ChInterruptEnBits;
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */
#if (DMA_CFG_CONTINUOUS_MODE_EN == STD_ON)
    /* Channel continuous mode(refill function) enable status */
    boolean                                ChContinuousMode;
#endif /* \(DMA_CFG_CONTINUOUS_MODE_EN == STD_ON) */
#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
    /* Pointer to the Mapping list of shadowing to transfer and linked list */
    const Dma_ShadowingMapType             *ChShadowMapInfoPtr;
#endif /* \(DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) */
#if (DMA_CFG_LINKEDLIST_EN == STD_ON)
    /* Pointer to channel Linked list configuration */
    const Dma_ChLinkedListConfigType       *ChLliConfigPtr;
#endif /* \(DMA_CFG_LINKEDLIST_EN == STD_ON) */
    /* Pointer to channel notification function */
    void (*DmaChannelNotificationPtr)(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
    /* Pointer to the transfer configuration parameters */
    const Dma_TransferConfigType           *ChTransferConfigPtr;
} Dma_ChConfigType;

/* Type definition for HW unit configuration structure */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Maximum number of the ADC HwUnit allocated to the core */
    Dma_HwUnitType                     MaxHwUnitNum;
    /* List to save the used HW units */
    const Dma_HwUnitType               *HwUnitListPtr;
    /* Pointer to the configuration of hardware units and physical channels mapped to
     * logical channels */
    const Dma_ChannelType              *HwToChannelPtr[DMA_MAX_HWUNIT_COUNT];
} Dma_HwUnitConfigType;

/* Type for core configuration */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Total number of channels */
    uint8                                  MaxChannel;
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
    /* Total number of daisy chain */
    uint8                                  MaxDaisyChain;
    /* Pointer to the daisy chain configuration parameter list */
    const Dma_DaisyChainMapType            *DaisyChainListPtr;
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
    /* Pointer to the configuration parameters of channels */
    const Dma_ChConfigType                 *ChannelConfigPtr;
} Dma_CoreConfigType;

#if ((DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) || (DMA_CFG_PATTERN_MATCH_EN == STD_ON) || \
        (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON))
/* Type for general configuration */
/* #Violation: Dma_GeneralTypes_h_REF_1 */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
    /* Pointer to the double buffer configuration parameters */
    const Dma_DoubleBufferConfigType       *DblBufConfigPtr;
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
    /* Pointer to the circular buffer configuration parameters */
    const Dma_CircularBufferConfig         *CircBufConfigPtr;
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */
#if (DMA_CFG_PATTERN_MATCH_EN == STD_ON)
    /* Pointer to channel pattern match configuration parameters */
    const Dma_MatchPatternConfig           *PatternConfigPtr;
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */
} Dma_CommonConfigType;
#endif /* \((DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) || (DMA_CFG_PATTERN_MATCH_EN == STD_ON) || \
        (DMA_CFG_CIRCULAR_BUFFER_EN== STD_ON)) */

/* Type for configuration set of Dma module */
/* #Violation: Dma_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Pointer to core configuration set */
    const Dma_CoreConfigType           *CoreConfigPtr[MCAL_NUMBER_OF_CORES];
#if ((DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) || (DMA_CFG_PATTERN_MATCH_EN == STD_ON) || \
        (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON))
    /* Pointer to Dma common configuration set */
    const Dma_CommonConfigType         *CommConfigPtr;
#endif /* \((DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) || (DMA_CFG_PATTERN_MATCH_EN == STD_ON) || \
        (DMA_CFG_CIRCULAR_BUFFER_EN== STD_ON)) */
    /* Pointer to the mapping relationship of logical channel */
    const Dma_ChannelMapType           *ChannelMapInfoPtr;
    /* Pointer to Dma HW unit Configuration */
    const Dma_HwUnitConfigType         *HwUnitConfigPtr;
} Dma_ConfigType;

#endif /* \DMA_GENERALTYPES_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

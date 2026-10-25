/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dma.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DMA
*
*   brief                 : This file contains all function declarations of Dma Driver
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
*#Dma_h_REF_1:MISRAC2012-Rule-20.7;
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard 
*   rule.
*
*/

#ifndef DMA_H_
#define DMA_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dma_GeneralTypes.h"
#include "Dma_Cfg.h"
#include "Dma_PBcfg.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Development error values */
#if (DMA_DEV_ERROR_DETECT == STD_ON)
/* service is called without Dma Driver initialization */
#define DMA_E_UNINIT                               ((uint8)0x0A)
/* Initialization service called twice without deinit */
#define DMA_E_ALREADY_INITIALIZED                  ((uint8)0x0D)
/* Initialization service is called with configPtr as NULL*/
#define DMA_E_PARAM_CONFIG                         ((uint8)0x0E)
/* Service is called with NULL_PTR  */
#define DMA_E_PARAM_POINTER                        ((uint8)0x0F)
/* Service is called with invalid channel ID */
#define DMA_E_PARAM_CHANNEL                        ((uint8)0x11)
#if (DMA_CFG_DOUBLE_BUFFER_SWITCH_API == STD_ON)
/* Service is called with double buffer function of specified channel is not enabled */
#define DMA_E_DOUBLE_BUFFER                        ((uint8)0x12)
#endif /* \(DMA_CFG_DOUBLE_BUFFER_SWITCH_API == STD_ON) */
#if (DMA_CFG_SHADOWING_UPDATE_API == STD_ON)
/* Service is called with invalid shadowing operation ID */
#define DMA_E_SHADOWING                            ((uint8)0x16)
#endif /* \(DMA_CFG_SHADOWING_UPDATE_API == STD_ON) */
#if ((DMA_CFG_TRANSFER_UPDATE_API == STD_ON) || (DMA_CFG_SHADOWING_UPDATE_API == STD_ON))
/* Service is called with invalid shadowing operation or transfer ID */
#define DMA_E_PARAM_WRONG_ID                       ((uint8)0x17)
#endif /* \((DMA_CFG_TRANSFER_UPDATE_API == STD_ON) || (DMA_CFG_SHADOWING_UPDATE_API == STD_ON)) */
#if (DMA_CFG_CHANNEL_CANCEL_API == STD_ON)
/* Service is called with invalid channel cancel method */
#define DMA_E_CANCEL_METHOD                        ((uint8)0x18)
#endif /* \(DMA_CFG_CHANNEL_CANCEL_API == STD_ON) */
#if ((DMA_CFG_TRANSFER_UPDATE_API == STD_ON) || (DMA_CFG_SHADOWING_UPDATE_API == STD_ON))
/* Switch ID is same with current ID when API Dma_ChannelUpdate() and
 * Dma_ChannelShadowingUpdate() calling  */
#define DMA_E_UPDATE_SAME_ID                       ((uint8)0x19)
/* Multiple configurations is unsupported for the channel  when API Dma_ChannelUpdate() and
 * Dma_ChannelShadowingUpdate() calling  */
#define DMA_E_CHANNEL_MULTI_CONFIG                 ((uint8)0x1A)
#endif /* \((DMA_CFG_TRANSFER_UPDATE_API == STD_ON) || (DMA_CFG_SHADOWING_UPDATE_API == STD_ON)) */
#if (DMA_CFG_DAISYCHAIN_EN == STD_ON)
#if ((DMA_CFG_CHANNEL_CANCEL_API == STD_ON) || (DMA_CFG_CHANNEL_PAUSE_API == STD_ON))
/* Service is called during transferring of daisy chain, if the channel is not the first member in
 * the daisy chain shall not allowed to be operated */
#define DMA_E_CHANNEL_DAISYCHAIN                   ((uint8)0x1B)
#endif /* \((DMA_CFG_CHANNEL_CANCEL_API == STD_ON) || (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)) */
/* Service is channel start, which is the first in the daisy chain, and one or more channels
 * within the daisy chain are in the transferring status */
#define DMA_E_DAISYCHAIN_START_FAILED              ((uint8)0x1C)
#endif /* \(DMA_CFG_DAISYCHAIN_EN == STD_ON) */
#if (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)
/* Specified channel is not in paused status */
#define DMA_E_CHANNEL_NOT_SUSPEND                  ((uint8)0x20)
#endif /* \(DMA_CFG_CHANNEL_PAUSE_API == STD_ON) */
#if ((DMA_CFG_CHANNEL_CANCEL_API == STD_ON) || (DMA_CFG_CHANNEL_PAUSE_API == STD_ON) || \
     (DMA_CFG_SHADOWING_UPDATE_API == STD_ON))
/* Specified channel is in IDLE status */
#define DMA_E_CHANNEL_IDLE                         ((uint8)0x21)
#endif /* \((DMA_CFG_CHANNEL_CANCEL_API == STD_ON) || (DMA_CFG_CHANNEL_PAUSE_API == STD_ON) || \
     (DMA_CFG_SHADOWING_UPDATE_API == STD_ON)) */
/* Specified channel is in transferring status */
#define DMA_E_CHANNEL_TRANSFERING                  ((uint8)0x22)
/* Service is called with no transfer configuration for the parameter channel */
#if (DMA_CFG_DOUBLE_BUFFER_SWITCH_API == STD_ON)
#define DMA_E_CHANNEL_NO_TRANS_CONFIG              ((uint8)0x23)
#endif /* \(DMA_CFG_DOUBLE_BUFFER_SWITCH_API == STD_ON) */
/* Error while data transferring or linked list item loading */
#define DMA_E_BUSERROR                             ((uint8)0x31)
/* Master core is not initialized when slave call Dma_Init */
#define DMA_E_MASTER_CORE_UNINITIALIZE             ((uint8)0x32U)
#if (DMA_CFG_DEINIT_API == STD_ON)
/* There are slave cores that have not been de-initialized when call Dma_DeInit */
#define DMA_E_SLAVE_CORE_INITIALIZED               ((uint8)0x33U)
#endif /* \(DMA_CFG_DEINIT_API == STD_ON) */

#if (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292)
/* The feature is not supported on the current chip when the service is called */
#define DMA_E_FEATURE_NOT_SUPPORTED                ((uint8)0x34)
#endif /* \(MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6206_LFBGA292) */
#endif /* \(DMA_CFG_CHANNEL_PAUSE_API == STD_ON) */

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
#define DMA_E_TRANSFER_SIZE_OUT_OF_RANGE           ((uint8)0x35)
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */


/* No hardware unit is configured for specified core */
#define DMA_E_CORE_NOT_CONFIGURED                  ((uint8)0xE0U)
/* DMA logical channel is not allocated to current core */
#define DMA_E_CORE_CHANNEL_MISMATCH                ((uint8)0xE1U)

#endif /* \(DMA_DEV_ERROR_DETECT == STD_ON) */

#if (DMA_SAFETY_ENABLE == STD_ON)
/* Safety error is occurred */
#define DMA_E_SAFETY_CHECK_FAILED                  ((uint8)0xE2U)
#endif /* \(DMA_SAFETY_ENABLE == STD_ON) */

/* API Service ID for Dma_Init() */
#define DMA_SID_INIT                               ((uint8)0x00)
/* API Service ID for Dma_DeInit() */
#define DMA_SID_DEINIT                             ((uint8)0x01)
/* Service ID for API Dma_ChannelStart() */
#define DMA_SID_CHANNELSTART                       ((uint8)0x02)
#if (DMA_CFG_CHANNEL_CANCEL_API == STD_ON)
/* Service ID for API Dma_ChannelCancel() */
#define DMA_SID_CHANNELCANCEL                      ((uint8)0x03)
#endif /* \(DMA_CFG_CHANNEL_CANCEL_API == STD_ON) */
#if (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)
/* Service ID for API Dma_ChannelSuspend() */
#define DMA_SID_CHANNELSUSPEND                     ((uint8)0x04)
/* Service ID for API Dma_ChannelResume() */
#define DMA_SID_CHANNELRESUME                      ((uint8)0x05)
#endif /* \(DMA_CFG_CHANNEL_PAUSE_API == STD_ON) */
#if (DMA_CFG_TRANSFER_UPDATE_API == STD_ON)
/* Service ID for API Dma_ChannelUpdate() */
#define DMA_SID_CHANNELUPDATE                      ((uint8)0x06)
#endif /* \(DMA_CFG_TRANSFER_UPDATE_API == STD_ON) */
#if (DMA_CFG_SHADOWING_OPERATION_EN == STD_ON)
#if (DMA_CFG_SHADOWING_UPDATE_API == STD_ON)
/* Service ID for API Dma_ChannelShadowingUpdate() */
#define DMA_SID_CHANNELSHADOWUPDATE                ((uint8)0x07)
#endif /* \(DMA_CFG_SHADOWING_UPDATE_API == STD_ON) */
#endif /* \(DMA_CFG_SHADOWING_OPERATION_EN == STD_ON) */
#if (DMA_CFG_DOUBLE_BUFFER_EN == STD_ON)
#if (DMA_CFG_DOUBLE_BUFFER_SWITCH_API == STD_ON)
/* Service ID for API Dma_ChannelDoubleBufferSwitch() */
#define DMA_SID_CHANNELDOUBLEBUFFERSWITCH          ((uint8)0x08)
#endif /* \(DMA_CFG_DOUBLE_BUFFER_SWITCH_API == STD_ON) */
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */
#if (DMA_CFG_CHANNEL_REMAINING_TRANSFER_API == STD_ON)
/* Service ID for API Dma_GetChannelRemainTransfer() */
#define DMA_SID_GETCHANNELREMAINTRANSFER           ((uint8)0x09)
#endif /* \(DMA_CFG_CHANNEL_REMAINING_TRANSFER_API == STD_ON) */
/* Service ID for API Dma_GetChannelStatus() */
#define DMA_SID_GETCHANNELSTATUS                   ((uint8)0x10)
#if (DMA_CFG_VERSION_INFO_API == STD_ON)
/* Service ID for API Dma_GetVersionInfo() */
#define DMA_SID_GETVERSIONINFO                     ((uint8)0x11)
#endif /* \(DMA_CFG_VERSION_INFO_API == STD_ON) */
/* Service ID for API Dma_LliMemberInsertManual() */
#define DMA_SID_LLIMEMBERINSERTMANUAL              ((uint8)0x12)
/* Service ID for API Dma_LliInsertCompleteManual() */
#define DMA_SID_LLIINSERTCOMPLETEMANUAL            ((uint8)0x13)
#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
/* Service ID for API Dma_ChannelUpdateManual() */
#define DMA_SID_CHANNELUPDATEMANUAL                ((uint8)0x14)
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */
#if ((DMA_CFG_ERR_INTERRUPT_EN == STD_ON) || (DMA_DEV_ERROR_DETECT == STD_ON))
/* Service ID for interrupt handler Dma_Error_ISRHandler() */
#define DMA_SID_ERROR_ISR                          ((uint8)0xE2)
#endif /* \((DMA_CFG_ERR_INTERRUPT_EN == STD_ON) || (DMA_DEV_ERROR_DETECT== STD_ON)) */
#if (DMA_CFG_INTERRUPT_EN == STD_ON)
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
/* Service ID for interrupt handler Dma_TerminalCount_ISRHandler() */
#define DMA_SID_TERMINALCOUNT_ISR                  ((uint8)0xE0)
#endif /* \(DMA_CFG_TC_INTERRUPT_EN == STD_ON) */
#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
/* Service ID for interrupt handler Dma_RemainingCount_ISRHandler() */
#define DMA_SID_REMAININGCOUNT_ISR                 ((uint8)0xE1)
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN == STD_ON) */
#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
/* Service ID for interrupt handler Dma_SrcCircBufRb_ISRHandler() */
#define DMA_SID_SRCCIRCBUF_ISR                     ((uint8)0xE3)
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON) */
#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
/* Service ID for interrupt handler Dma_DestCircBufRb_ISRHandler() */
#define DMA_SID_DESTCIRCBUF_ISR                    ((uint8)0xE4)
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON) */
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */
#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
/* Service ID for interrupt handler Dma_PatternMatch_ISRHandler() */
#define DMA_SID_PATTERNMATCH_ISR                   ((uint8)0xE5)
#endif /* \(DMA_CFG_PATTERN_MATCH_EN == STD_ON) */
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */


/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dma_MemMap.h"

extern FUNC(void, DMA_PUBLIC_CODE) Dma_Init
(
    CONSTP2CONST(Dma_ConfigType, AUTOMATIC, DMA_APPL_CONST) ConfigPtr
);

#if (DMA_CFG_DEINIT_API == STD_ON)
extern FUNC(void, DMA_PUBLIC_CODE) Dma_DeInit
(
    void
);
#endif /* \(DMA_CFG_DEINIT_API == STD_ON) */

extern FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelStart
(
    Dma_ChannelType Channel
);

#if (DMA_CFG_CHANNEL_CANCEL_API == STD_ON)
extern FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelCancel
(
    Dma_ChannelType Channel,
    Dma_ChCancelType CancelMethod
);
#endif /* \(DMA_CFG_CHANNEL_CANCEL_API == STD_ON) */

#if (DMA_CFG_CHANNEL_PAUSE_API == STD_ON)
extern FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelSuspend
(
    Dma_ChannelType Channel
);

FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelResume
(
    Dma_ChannelType Channel
);
#endif /* \(DMA_CFG_CHANNEL_PAUSE_API == STD_ON) */

#if (DMA_CFG_TRANSFER_UPDATE_API == STD_ON)
extern FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelUpdate
(
    Dma_ChannelType Channel,
    Dma_TransferType TransferId
);
#endif /* \(DMA_CFG_TRANSFER_UPDATE_API == STD_ON) */

#if (DMA_CFG_SHADOWING_UPDATE_API == STD_ON)
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelShadowingUpdate
(
    Dma_ChannelType Channel,
    Dma_ShadowingType ShadowingId
);
#endif /* \(DMA_CFG_SHADOWING_UPDATE_API == STD_ON) */

#if (DMA_CFG_DOUBLE_BUFFER_SWITCH_API == STD_ON)
extern FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelDoubleBufferSwitch
(
    Dma_ChannelType Channel
);
#endif /* \(DMA_CFG_DOUBLE_BUFFER_EN == STD_ON) */

#if (DMA_CFG_CHANNEL_REMAINING_TRANSFER_API == STD_ON)
extern FUNC(uint16, DMA_PUBLIC_CODE) Dma_GetChannelRemainTransfer
(
    Dma_ChannelType Channel
);
#endif /* \(DMA_CFG_CHANNEL_REMAINING_TRANSFER_API == STD_ON) */

extern FUNC(uint32, DMA_PUBLIC_CODE) Dma_GetChannelStatus
(
    Dma_ChannelType Channel
);

#if (DMA_CFG_VERSION_INFO_API == STD_ON)
extern FUNC(void, INTC_PUBLIC_CODE) Dma_GetVersionInfo
(
    /* #Violation: Dma_h_REF_1 */
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, ADC_APPL_DATA) VersionInfoPtr
);
#endif /* \(DMA_CFG_VERSION_INFO_API == STD_ON) */

extern FUNC(Std_ReturnType, INTC_PUBLIC_CODE) Dma_LliMemberInsertManual
(
    Dma_ChannelType Channel,
    /* #Violation: Dma_h_REF_1 */
    CONSTP2VAR(Dma_LliBufType, AUTOMATIC, ADC_APPL_DATA) LliBufPtr,
    CONSTP2CONST(Dma_LliCfgType, AUTOMATIC, ADC_APPL_DATA) LliCfgPtr
);

extern FUNC(Std_ReturnType, INTC_PUBLIC_CODE) Dma_LliInsertCompleteManual
(
    Dma_ChannelType Channel,
    CONSTP2CONST(Dma_LliBufType, AUTOMATIC, ADC_APPL_DATA) LliBufHeadAddrPtr
);

#if (DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON)
FUNC(void, DMA_PUBLIC_CODE) Dma_ChannelUpdateManual
(
    Dma_ChannelType Channel,
    CONSTP2VAR(Dma_ChannelTransferType, AUTOMATIC, DMA_APPL_DATA) ChannelTransferPtr
);
#endif /* \(DMA_CFG_TRANSFER_UPDATE_MANUAL_API == STD_ON) */

#if (DMA_CFG_INTERRUPT_EN == STD_ON)
#if (DMA_CFG_TC_INTERRUPT_EN == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Dma_TerminalCount_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
);
#endif /* \(DMA_CFG_TC_INTERRUPT_EN == STD_ON) */

#if (DMA_CFG_RTC_INTERRUPT_EN == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Dma_RemainingCount_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
);
#endif /* \(DMA_CFG_RTC_INTERRUPT_EN == STD_ON) */

#if (DMA_CFG_ERR_INTERRUPT_EN == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Dma_Error_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
);
#endif /* \(DMA_CFG_ERR_INTERRUPT_EN == STD_ON) */

#if (DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON)
#if (DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Dma_SrcCircBufRb_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
);
#endif /* \(DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN == STD_ON) */

#if (DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Dma_DestCircBufRb_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
);
#endif /* \(DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN == STD_ON) */
#endif /* \(DMA_CFG_CIRCULAR_BUFFER_EN == STD_ON) */

#if (DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON)
extern FUNC(void, ADC_PUBLIC_CODE) Dma_PatternMatch_ISRHandler
(
    Dma_HwUnitType HwUnitId,
    uint8          PhyChannelId
);
#endif /* \(DMA_CFG_PATTERN_INTERRUPT_EN == STD_ON) */
#endif /* \(DMA_CFG_INTERRUPT_EN == STD_ON) */

#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dma_MemMap.h"

#endif /* \DMA_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

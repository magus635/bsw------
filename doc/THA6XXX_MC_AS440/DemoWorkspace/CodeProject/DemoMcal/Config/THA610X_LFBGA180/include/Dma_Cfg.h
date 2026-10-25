/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Dma_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : DMA
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Dma_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*/

#ifndef DMA_CFG_H_
#define DMA_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

#define DMA_CFG_AR_RELEASE_MAJOR_VERSION                   (4U)
#define DMA_CFG_AR_RELEASE_MINOR_VERSION                   (4U)
#define DMA_CFG_AR_RELEASE_REVISION_VERSION                (0U)

#define DMA_CFG_SW_MAJOR_VERSION                           (1U)
#define DMA_CFG_SW_MINOR_VERSION                           (2U)
#define DMA_CFG_SW_PATCH_VERSION                           (0U)

#define DMA_CFG_VENDOR_ID                                  (175U)
#define DMA_CFG_MODULE_ID                                  (255U)

/* Total configuration sets */
#define DMA_CONFIGSET_CNT                                  (1U)

/*
Configuration: DmaSafetyErrorDetect
- if Selected, Safety Error Check is Enabled 
- if Deselected, Safety Error Check is Disabled 
*/
#define DMA_SAFETY_ENABLE                                  (STD_ON)

/*
Configuration: DmaDevErrorDetect
- if Selected, DET is Enabled 
- if Deselected, DET is Disabled 
*/
#define DMA_DEV_ERROR_DETECT                               (STD_ON)

/*
Configuration: DmaDeInitApi
- if Selected, DeInit() API is Enabled 
- if Deselected, DeInit() API is Disabled 
*/
#define DMA_CFG_DEINIT_API                                 (STD_ON)

/*
Configuration: DmaSuspendResumeApi
- if Selected, Dma_ChannelPause() API is Enabled 
- if Deselected, Dma_ChannelPause() API is Disabled 
*/
#define DMA_CFG_CHANNEL_PAUSE_API                          (STD_ON)

/*
Configuration: DmaCancelApi
- if Selected, Dma_ChannelCancel() API is Enabled 
- if Deselected, Dma_ChannelCancel() API is Disabled 
*/
#define DMA_CFG_CHANNEL_CANCEL_API                         (STD_ON)

/*
Configuration: DmaRemainingTransferApi
- if Selected, Dma_ChannelCancel() API is Enabled 
- if Deselected, Dma_ChannelCancel() API is Disabled 
*/
#define DMA_CFG_CHANNEL_REMAINING_TRANSFER_API             (STD_OFF)

/*
Configuration: DmaVersionInfoApi
- if Selected, Dma_GetVersionInfo() API is Enabled 
- if Deselected, Dma_GetVersionInfo API is Disabled 
*/
#define DMA_CFG_VERSION_INFO_API                           (STD_ON)

/*
Configuration: DmaDoubleBufferSoftwareSwitchApi
- if Selected, Dma_ChannelDoubleBufferSwitch() API is Enabled 
- if Deselected, Dma_ChannelDoubleBufferSwitch API is Disabled 
*/
#define DMA_CFG_DOUBLE_BUFFER_SWITCH_API                   (STD_OFF)

/*
Configuration: DmaTransferUpdateApi
- if Selected, DMA channel transfer configuration switch API is Enabled 
- if Deselected, DMA channel transfer configuration switch API is Disabled 
*/
#define DMA_CFG_TRANSFER_UPDATE_API                        (STD_ON)

/*
Configuration: DmaShadowingUpdateApi
- if Selected, DMA channel shadowing operation configuration switch API is Enabled 
- if Deselected, DMA channel shadowing operation configuration switch API is Disabled 
*/
#define DMA_CFG_SHADOWING_UPDATE_API                       (STD_ON)

/*
Configuration: DmaTransferUpdateManualApi
- if Selected, DMA channel transfer configuration update manual API is Enabled 
- if Deselected, DMA channel transfer configuration update manual API is Disabled 
*/
#define DMA_CFG_TRANSFER_UPDATE_MANUAL_API                 (STD_ON)

/*
Configuration: DmaLinkedListEnable
- if Selected, DMA linked list functionality is Enabled 
- if Deselected, DMA linked list functionality is Disabled 
*/
#define DMA_CFG_LINKEDLIST_EN                              (STD_ON)

/*
Configuration: DmaDaisyChainEnable
- if Selected, DMA daisy chain functionality is Enabled 
- if Deselected, DMA daisy chain functionality is Disabled 
*/
#define DMA_CFG_DAISYCHAIN_EN                              (STD_ON)

/*
Configuration: DmaContinuousModeEnable
- if Selected, DMA continuous functionality is Enabled 
- if Deselected, DMA continuous functionality is Disabled 
*/
#define DMA_CFG_CONTINUOUS_MODE_EN                         (STD_ON)


/*
Configuration: DmaDoubleBufferEnable
- if Selected, DMA channel linked list functionality is Enabled 
- if Deselected, DET is Disabled 
*/
#define DMA_CFG_DOUBLE_BUFFER_EN                           (STD_ON)


/*
Configuration: DmaShadowingOperationEnable
- if Selected, DMA shadowing operation functionality is Enabled 
- if Deselected, DMA shadowing operation functionality is Disabled 
*/
#define DMA_CFG_SHADOWING_OPERATION_EN                     (STD_ON)


/*
Configuration: DmaCircularBufferEnable
- if Selected, DMA circular buffer is Enabled 
- if Deselected, DMA circular buffer is Disabled 
*/
#define DMA_CFG_CIRCULAR_BUFFER_EN                         (STD_ON)


/*
Configuration: DmaPatternEnable
- if Selected, DMA pattern match functionality is Enabled 
- if Deselected, DMA pattern match functionality is Disabled 
*/
#define DMA_CFG_PATTERN_MATCH_EN                           (STD_ON)

/*
Configuration: DmaChannelInterruptEnable
- if Selected, DMA interrupt functionality is Enabled 
- if Deselected, DMA interrupt functionality is Disabled 
*/
#define DMA_CFG_INTERRUPT_EN                               (STD_ON)

/* Configuration: DmaChannelTerminalCountInterruptEnable
    Terminal count(TC) interrupt
*/
#define DMA_CFG_TC_INTERRUPT_EN                            (STD_ON)
/* Configuration: DmaChannelRemainCountInterruptEnable
    Remaining transfer count(RTC) interrupt
*/
#define DMA_CFG_RTC_INTERRUPT_EN                           (STD_OFF)
/* Configuration: DmaChannelErrorInterruptEnable
    Error interrupt
*/
#define DMA_CFG_ERR_INTERRUPT_EN                           (STD_ON)
/* Configuration: DmaChScbRollbackInterruptEnable
    Source circular buffer rollback interrupt
*/
#define DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN                  (STD_OFF)
/* Configuration: DmaChDcbRollbackInterruptEnable
    Destination circular buffer rollback interrupt
*/
#define DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN                 (STD_OFF)
/* Configuration: DmaChPatternMatchedInterruptEnable
    Data pattern matched interrupt
*/
#define DMA_CFG_PATTERN_INTERRUPT_EN                       (STD_ON)

/* Macro for No transfer configuration in certain channel(s) */
#define DMA_CFG_CHANNEL_NO_TRANSFER_EN                     (STD_ON)

/* Number of transfer or LLI multiple configuration sets
Configuration: DmaChTransferConfig and DmaChLinkedListItemConfig */
#define DMA_CFG_MULTI_TRANSFER_NUM                         (3U)
/* Number of transfer or LLI multiple configuration sets allocated to Core0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_TRANSFER_NUM_CORE0                         (3U)
/* Number of transfer or LLI multiple configuration sets allocated to Core1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_TRANSFER_NUM_CORE1                         (0U)

/* Number of shadowing multiple configuration sets
Configuration: DmaChShadowConfig */
#define DMA_CFG_MULTI_SHADOWING_NUM                        (1U)
/* Number of shadowing multiple configuration sets allocated to Core0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_SHADOWING_NUM_CORE0                         (1U)
/* Number of shadowing multiple configuration sets allocated to Core1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_SHADOWING_NUM_CORE1                         (0U)

                    /* Number of daisy chain of core0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DAISY_CHAIN_NUM_CORE0                         (2U)
                    /* Number of daisy chain of core1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DAISY_CHAIN_NUM_CORE1                         (0U)

/* Number of channels allocated to Core0 */
#define DMA_CFG_MAX_CHANNELS_CORE0                         (18U)
/* Number of channels allocated to Core1 */
#define DMA_CFG_MAX_CHANNELS_CORE1                         (0U)
/* Total number of channels */
#define DMA_CFG_MAX_CHANNELS                               (18U)

/* The number of all HW units */
#define DMA_MAX_HWUNIT_COUNT                               (4U)

/* ID of DMA HwUnit1 */
#define DMA_HWUNIT_DMA0                                    (0U)
/* ID of DMA HwUnit2 */
#define DMA_HWUNIT_DMA2                                    (2U)

/* IDs of physical channel in DMA0 */
/* ID of physical channel0 */
#define DMA_DMA0_PHYCHANNEL0                               (0U)
/* ID of physical channel1 */
#define DMA_DMA0_PHYCHANNEL1                               (1U)
/* ID of physical channel2 */
#define DMA_DMA0_PHYCHANNEL2                               (2U)
/* ID of physical channel3 */
#define DMA_DMA0_PHYCHANNEL3                               (3U)

/* IDs of physical channel in DMA2 */
/* ID of physical channel0 */
#define DMA_DMA2_PHYCHANNEL0                               (0U)
/* ID of physical channel1 */
#define DMA_DMA2_PHYCHANNEL1                               (1U)
/* ID of physical channel2 */
#define DMA_DMA2_PHYCHANNEL2                               (2U)
/* ID of physical channel3 */
#define DMA_DMA2_PHYCHANNEL3                               (3U)
/* ID of physical channel4 */
#define DMA_DMA2_PHYCHANNEL4                               (4U)
/* ID of physical channel5 */
#define DMA_DMA2_PHYCHANNEL5                               (5U)
/* ID of physical channel6 */
#define DMA_DMA2_PHYCHANNEL6                               (6U)
/* ID of physical channel7 */
#define DMA_DMA2_PHYCHANNEL7                               (7U)
/* ID of physical channel8 */
#define DMA_DMA2_PHYCHANNEL8                               (8U)
/* ID of physical channel9 */
#define DMA_DMA2_PHYCHANNEL9                               (9U)
/* ID of physical channel10 */
#define DMA_DMA2_PHYCHANNEL10                               (10U)
/* ID of physical channel11 */
#define DMA_DMA2_PHYCHANNEL11                               (11U)
/* ID of physical channel12 */
#define DMA_DMA2_PHYCHANNEL12                               (12U)
/* ID of physical channel13 */
#define DMA_DMA2_PHYCHANNEL13                               (13U)
/* ID of physical channel14 */
#define DMA_DMA2_PHYCHANNEL14                               (14U)
/* ID of physical channel15 */
#define DMA_DMA2_PHYCHANNEL15                               (15U)
/* ID of physical channel16 */
#define DMA_DMA2_PHYCHANNEL16                               (16U)
/* ID of physical channel17 */
#define DMA_DMA2_PHYCHANNEL17                               (17U)
/* ID of physical channel18 */
#define DMA_DMA2_PHYCHANNEL18                               (18U)
/* ID of physical channel19 */
#define DMA_DMA2_PHYCHANNEL19                               (19U)
/* ID of physical channel20 */
#define DMA_DMA2_PHYCHANNEL20                               (20U)
/* ID of physical channel21 */
#define DMA_DMA2_PHYCHANNEL21                               (21U)
/* ID of physical channel22 */
#define DMA_DMA2_PHYCHANNEL22                               (22U)
/* ID of physical channel23 */
#define DMA_DMA2_PHYCHANNEL23                               (23U)
/* ID of physical channel24 */
#define DMA_DMA2_PHYCHANNEL24                               (24U)
/* ID of physical channel25 */
#define DMA_DMA2_PHYCHANNEL25                               (25U)
/* ID of physical channel26 */
#define DMA_DMA2_PHYCHANNEL26                               (26U)
/* ID of physical channel27 */
#define DMA_DMA2_PHYCHANNEL27                               (27U)
/* ID of physical channel28 */
#define DMA_DMA2_PHYCHANNEL28                               (28U)
/* ID of physical channel29 */
#define DMA_DMA2_PHYCHANNEL29                               (29U)
/* ID of physical channel30 */
#define DMA_DMA2_PHYCHANNEL30                               (30U)
/* ID of physical channel31 */
#define DMA_DMA2_PHYCHANNEL31                               (31U)
/* ID of physical channel32 */
#define DMA_DMA2_PHYCHANNEL32                               (32U)
/* ID of physical channel33 */
#define DMA_DMA2_PHYCHANNEL33                               (33U)
/* ID of physical channel34 */
#define DMA_DMA2_PHYCHANNEL34                               (34U)
/* ID of physical channel35 */
#define DMA_DMA2_PHYCHANNEL35                               (35U)
/* ID of physical channel36 */
#define DMA_DMA2_PHYCHANNEL36                               (36U)
/* ID of physical channel37 */
#define DMA_DMA2_PHYCHANNEL37                               (37U)
/* ID of physical channel38 */
#define DMA_DMA2_PHYCHANNEL38                               (38U)
/* ID of physical channel39 */
#define DMA_DMA2_PHYCHANNEL39                               (39U)
/* ID of physical channel40 */
#define DMA_DMA2_PHYCHANNEL40                               (40U)
/* ID of physical channel41 */
#define DMA_DMA2_PHYCHANNEL41                               (41U)
/* ID of physical channel42 */
#define DMA_DMA2_PHYCHANNEL42                               (42U)
/* ID of physical channel43 */
#define DMA_DMA2_PHYCHANNEL43                               (43U)


/****************************************************************************************************
**                          Macro definition of channel interrupt enable                           **
****************************************************************************************************/
/* Channel ID0(M2M): Physical channel0 in DMA0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL0_INT_EN                       (STD_OFF)
/* Channel ID1(M2M_Continuous): Physical channel1 in DMA0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL1_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL1_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL1_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL1_ERROR_INT_EN                 (STD_ON)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL1_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL1_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL1_PATTERN_INT_EN               (STD_OFF)

/* Channel ID2(M2M_DoubleBuf): Physical channel2 in DMA0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL2_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL2_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL2_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL2_ERROR_INT_EN                 (STD_OFF)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL2_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL2_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL2_PATTERN_INT_EN               (STD_OFF)

/* Channel ID3(M2M_CircBuf): Physical channel3 in DMA0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL3_INT_EN                       (STD_OFF)
/* Channel ID4(M2M_LinkedList): Physical channel12 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL12_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL12_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL12_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL12_ERROR_INT_EN                 (STD_OFF)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL12_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL12_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL12_PATTERN_INT_EN               (STD_OFF)

/* Channel ID5(M2M_Shadow): Physical channel13 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL13_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL13_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL13_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL13_ERROR_INT_EN                 (STD_OFF)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL13_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL13_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL13_PATTERN_INT_EN               (STD_OFF)

/* Channel ID6(M2M_Pattern): Physical channel14 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL14_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL14_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL14_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL14_ERROR_INT_EN                 (STD_ON)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL14_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL14_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL14_PATTERN_INT_EN               (STD_ON)

/* Channel ID7(M2M_Daisy0): Physical channel15 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL15_INT_EN                       (STD_OFF)
/* Channel ID8(M2M_Daisy1): Physical channel16 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL16_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL16_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL16_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL16_ERROR_INT_EN                 (STD_OFF)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL16_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL16_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL16_PATTERN_INT_EN               (STD_OFF)

/* Channel ID9(ADC1_Channel0): Physical channel2 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL2_INT_EN                       (STD_OFF)
/* Channel ID10(ADC1_Channel1): Physical channel3 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL3_INT_EN                       (STD_OFF)
/* Channel ID11(ADC1_Channel2): Physical channel4 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL4_INT_EN                       (STD_OFF)
/* Channel ID12(ADC1_Channel3): Physical channel5 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL5_INT_EN                       (STD_OFF)
/* Channel ID13(ADC1_Channel7): Physical channel6 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL6_INT_EN                       (STD_OFF)
/* Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL7_INT_EN                       (STD_OFF)
/* Channel ID15(SPITx): Physical channel8 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL8_INT_EN                       (STD_OFF)
/* Channel ID16(SPIRx): Physical channel9 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL9_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL9_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL9_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL9_ERROR_INT_EN                 (STD_OFF)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL9_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL9_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL9_PATTERN_INT_EN               (STD_OFF)

/* Channel ID17(ADC1_AllChToOneResReg): Physical channel17 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL17_INT_EN                       (STD_OFF)

/****************************************************************************************************
**                          Macro definition of request ID                                         **
****************************************************************************************************/
/* DMA0 local request: "REQUEST0_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST0_GTM                  (0U)
/* DMA0 local request: "REQUEST1_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST1_GTM                  (1U)
/* DMA0 local request: "REQUEST2_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST2_GTM                  (2U)
/* DMA0 local request: "REQUEST3_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST3_GTM                  (3U)
/* DMA0 local request: "REQUEST4_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST4_GTM                  (4U)
/* DMA0 local request: "REQUEST5_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST5_GTM                  (5U)
/* DMA0 local request: "REQUEST6_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST6_GTM                  (6U)
/* DMA0 local request: "REQUEST7_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST7_GTM                  (7U)
/* DMA0 local request: "REQUEST9_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST9_GLOBAL_REQUEST                  (9U)
/* DMA0 local request: "REQUEST10_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST10_GLOBAL_REQUEST                  (10U)
/* DMA0 local request: "REQUEST11_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST11_GLOBAL_REQUEST                  (11U)
/* DMA0 local request: "REQUEST12_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST12_GLOBAL_REQUEST                  (12U)
/* DMA0 local request: "REQUEST13_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST13_GLOBAL_REQUEST                  (13U)
/* DMA0 local request: "REQUEST14_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST14_GLOBAL_REQUEST                  (14U)
/* DMA0 local request: "REQUEST15_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST15_GLOBAL_REQUEST                  (15U)
/* DMA0 local request: "REQUEST16_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST16_GLOBAL_REQUEST                  (16U)
/* DMA0 local request: "REQUEST17_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST17_GLOBAL_REQUEST                  (17U)
/* DMA0 local request: "REQUEST18_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST18_GLOBAL_REQUEST                  (18U)
/* DMA0 local request: "REQUEST19_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST19_GLOBAL_REQUEST                  (19U)
/* DMA0 local request: "REQUEST20_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST20_GLOBAL_REQUEST                  (20U)
/* DMA0 local request: "REQUEST21_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST21_GLOBAL_REQUEST                  (21U)
/* DMA0 local request: "REQUEST22_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST22_GLOBAL_REQUEST                  (22U)
/* DMA0 local request: "REQUEST23_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST23_GLOBAL_REQUEST                  (23U)
/* DMA0 local request: "REQUEST24_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST24_GLOBAL_REQUEST                  (24U)

/* DMA2 local request: "REQUEST0_ESPI0_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST0_ESPI0_TX                  (0U)
/* DMA2 local request: "REQUEST1_ESPI0_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST1_ESPI0_RX                  (1U)
/* DMA2 local request: "REQUEST2_ESPI1_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST2_ESPI1_TX                  (2U)
/* DMA2 local request: "REQUEST3_ESPI1_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST3_ESPI1_RX                  (3U)
/* DMA2 local request: "REQUEST4_ESPI2_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST4_ESPI2_TX                  (4U)
/* DMA2 local request: "REQUEST5_ESPI2_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST5_ESPI2_RX                  (5U)
/* DMA2 local request: "REQUEST6_ESPI5_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST6_ESPI5_TX                  (6U)
/* DMA2 local request: "REQUEST7_ESPI5_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST7_ESPI5_RX                  (7U)
/* DMA2 local request: "REQUEST14_CAN00_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST14_CAN00_TX_FIFO                  (14U)
/* DMA2 local request: "REQUEST15_CAN00_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST15_CAN00_RX_FIFO0                  (15U)
/* DMA2 local request: "REQUEST16_CAN00_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST16_CAN00_RX_FIFO1                  (16U)
/* DMA2 local request: "REQUEST17_CAN00_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST17_CAN00_TX_EVENT                  (17U)
/* DMA2 local request: "REQUEST18_CAN01_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST18_CAN01_TX_FIFO                  (18U)
/* DMA2 local request: "REQUEST19_CAN01_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST19_CAN01_RX_FIFO0                  (19U)
/* DMA2 local request: "REQUEST20_CAN01_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST20_CAN01_RX_FIFO1                  (20U)
/* DMA2 local request: "REQUEST21_CAN01_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST21_CAN01_TX_EVENT                  (21U)
/* DMA2 local request: "REQUEST22_CAN02_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST22_CAN02_TX_FIFO                  (22U)
/* DMA2 local request: "REQUEST23_CAN02_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST23_CAN02_RX_FIFO0                  (23U)
/* DMA2 local request: "REQUEST24_CAN02_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST24_CAN02_RX_FIFO1                  (24U)
/* DMA2 local request: "REQUEST25_CAN02_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST25_CAN02_TX_EVENT                  (25U)
/* DMA2 local request: "REQUEST26_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST26_GLOBAL_REQUEST                  (26U)
/* DMA2 local request: "REQUEST27_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST27_GLOBAL_REQUEST                  (27U)
/* DMA2 local request: "REQUEST28_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST28_GLOBAL_REQUEST                  (28U)
/* DMA2 local request: "REQUEST29_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST29_GLOBAL_REQUEST                  (29U)
/* DMA2 local request: "REQUEST46_ECRC_CH0_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST46_ECRC_CH0_RESULT                  (46U)
/* DMA2 local request: "REQUEST47_ECRC_CH1_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST47_ECRC_CH1_RESULT                  (47U)
/* DMA2 local request: "REQUEST48_ECRC_CH2_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST48_ECRC_CH2_RESULT                  (48U)
/* DMA2 local request: "REQUEST49_ECRC_CH3_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST49_ECRC_CH3_RESULT                  (49U)
/* DMA2 local request: "REQUEST50_ECRC_CH4_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST50_ECRC_CH4_RESULT                  (50U)
/* DMA2 local request: "REQUEST51_ECRC_CH5_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST51_ECRC_CH5_RESULT                  (51U)
/* DMA2 local request: "REQUEST52_ECRC_CH6_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST52_ECRC_CH6_RESULT                  (52U)
/* DMA2 local request: "REQUEST53_ECRC_CH7_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST53_ECRC_CH7_RESULT                  (53U)
/* DMA2 local request: "REQUEST62_SARADC0_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST62_SARADC0_RESULT0                  (62U)
/* DMA2 local request: "REQUEST63_SARADC0_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST63_SARADC0_RESULT1                  (63U)
/* DMA2 local request: "REQUEST64_SARADC0_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST64_SARADC0_RESULT2                  (64U)
/* DMA2 local request: "REQUEST65_SARADC0_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST65_SARADC0_RESULT3                  (65U)
/* DMA2 local request: "REQUEST66_SARADC0_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST66_SARADC0_RESULT4                  (66U)
/* DMA2 local request: "REQUEST67_SARADC0_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST67_SARADC0_RESULT5                  (67U)
/* DMA2 local request: "REQUEST68_SARADC0_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST68_SARADC0_RESULT6                  (68U)
/* DMA2 local request: "REQUEST69_SARADC0_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST69_SARADC0_RESULT7                  (69U)
/* DMA2 local request: "REQUEST70_SARADC0_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST70_SARADC0_RESULT8                  (70U)
/* DMA2 local request: "REQUEST71_SARADC0_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST71_SARADC0_RESULT9                  (71U)
/* DMA2 local request: "REQUEST72_SARADC0_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST72_SARADC0_RESULT10                  (72U)
/* DMA2 local request: "REQUEST73_SARADC0_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST73_SARADC0_RESULT11                  (73U)
/* DMA2 local request: "REQUEST74_SARADC0_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST74_SARADC0_RESULT12                  (74U)
/* DMA2 local request: "REQUEST75_SARADC0_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST75_SARADC0_RESULT13                  (75U)
/* DMA2 local request: "REQUEST76_SARADC0_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST76_SARADC0_RESULT14                  (76U)
/* DMA2 local request: "REQUEST77_SARADC0_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST77_SARADC0_RESULT15                  (77U)
/* DMA2 local request: "REQUEST78_SARADC_GLOBAL_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST78_SARADC_GLOBAL_RESULT                  (78U)
/* DMA2 local request: "REQUEST79_SARADC1_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST79_SARADC1_RESULT0                  (79U)
/* DMA2 local request: "REQUEST80_SARADC1_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST80_SARADC1_RESULT1                  (80U)
/* DMA2 local request: "REQUEST81_SARADC1_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST81_SARADC1_RESULT2                  (81U)
/* DMA2 local request: "REQUEST82_SARADC1_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST82_SARADC1_RESULT3                  (82U)
/* DMA2 local request: "REQUEST83_SARADC1_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST83_SARADC1_RESULT4                  (83U)
/* DMA2 local request: "REQUEST84_SARADC1_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST84_SARADC1_RESULT5                  (84U)
/* DMA2 local request: "REQUEST85_SARADC1_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST85_SARADC1_RESULT6                  (85U)
/* DMA2 local request: "REQUEST86_SARADC1_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST86_SARADC1_RESULT7                  (86U)
/* DMA2 local request: "REQUEST87_SARADC1_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST87_SARADC1_RESULT8                  (87U)
/* DMA2 local request: "REQUEST88_SARADC1_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST88_SARADC1_RESULT9                  (88U)
/* DMA2 local request: "REQUEST89_SARADC1_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST89_SARADC1_RESULT10                  (89U)
/* DMA2 local request: "REQUEST90_SARADC1_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST90_SARADC1_RESULT11                  (90U)
/* DMA2 local request: "REQUEST91_SARADC1_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST91_SARADC1_RESULT12                  (91U)
/* DMA2 local request: "REQUEST92_SARADC1_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST92_SARADC1_RESULT13                  (92U)
/* DMA2 local request: "REQUEST93_SARADC1_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST93_SARADC1_RESULT14                  (93U)
/* DMA2 local request: "REQUEST94_SARADC1_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST94_SARADC1_RESULT15                  (94U)
/* DMA2 local request: "REQUEST95_SARADC2_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST95_SARADC2_RESULT0                  (95U)
/* DMA2 local request: "REQUEST96_SARADC2_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST96_SARADC2_RESULT1                  (96U)
/* DMA2 local request: "REQUEST97_SARADC2_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST97_SARADC2_RESULT2                  (97U)
/* DMA2 local request: "REQUEST98_SARADC2_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST98_SARADC2_RESULT3                  (98U)
/* DMA2 local request: "REQUEST99_SARADC2_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST99_SARADC2_RESULT4                  (99U)
/* DMA2 local request: "REQUEST100_SARADC2_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST100_SARADC2_RESULT5                  (100U)
/* DMA2 local request: "REQUEST101_SARADC2_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST101_SARADC2_RESULT6                  (101U)
/* DMA2 local request: "REQUEST102_SARADC2_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST102_SARADC2_RESULT7                  (102U)
/* DMA2 local request: "REQUEST103_SARADC2_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST103_SARADC2_RESULT8                  (103U)
/* DMA2 local request: "REQUEST104_SARADC2_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST104_SARADC2_RESULT9                  (104U)
/* DMA2 local request: "REQUEST105_SARADC2_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST105_SARADC2_RESULT10                  (105U)
/* DMA2 local request: "REQUEST106_SARADC2_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST106_SARADC2_RESULT11                  (106U)
/* DMA2 local request: "REQUEST107_SARADC2_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST107_SARADC2_RESULT12                  (107U)
/* DMA2 local request: "REQUEST108_SARADC2_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST108_SARADC2_RESULT13                  (108U)
/* DMA2 local request: "REQUEST109_SARADC2_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST109_SARADC2_RESULT14                  (109U)
/* DMA2 local request: "REQUEST110_SARADC2_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST110_SARADC2_RESULT15                  (110U)
/* DMA2 local request: "REQUEST111_SARADC3_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST111_SARADC3_RESULT0                  (111U)
/* DMA2 local request: "REQUEST112_SARADC3_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST112_SARADC3_RESULT1                  (112U)
/* DMA2 local request: "REQUEST113_SARADC3_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST113_SARADC3_RESULT2                  (113U)
/* DMA2 local request: "REQUEST114_SARADC3_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST114_SARADC3_RESULT3                  (114U)
/* DMA2 local request: "REQUEST115_SARADC3_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST115_SARADC3_RESULT4                  (115U)
/* DMA2 local request: "REQUEST116_SARADC3_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST116_SARADC3_RESULT5                  (116U)
/* DMA2 local request: "REQUEST117_SARADC3_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST117_SARADC3_RESULT6                  (117U)
/* DMA2 local request: "REQUEST118_SARADC3_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST118_SARADC3_RESULT7                  (118U)
/* DMA2 local request: "REQUEST119_SARADC3_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST119_SARADC3_RESULT8                  (119U)
/* DMA2 local request: "REQUEST120_SARADC3_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST120_SARADC3_RESULT9                  (120U)
/* DMA2 local request: "REQUEST121_SARADC3_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST121_SARADC3_RESULT10                  (121U)
/* DMA2 local request: "REQUEST122_SARADC3_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST122_SARADC3_RESULT11                  (122U)
/* DMA2 local request: "REQUEST123_SARADC3_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST123_SARADC3_RESULT12                  (123U)
/* DMA2 local request: "REQUEST124_SARADC3_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST124_SARADC3_RESULT13                  (124U)
/* DMA2 local request: "REQUEST125_SARADC3_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST125_SARADC3_RESULT14                  (125U)
/* DMA2 local request: "REQUEST126_SARADC3_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST126_SARADC3_RESULT15                  (126U)
/* DMA2 local request: "REQUEST127_CAN10_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST127_CAN10_TX_FIFO                  (127U)
/* DMA2 local request: "REQUEST128_CAN10_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST128_CAN10_RX_FIFO0                  (128U)
/* DMA2 local request: "REQUEST129_CAN10_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST129_CAN10_RX_FIFO1                  (129U)
/* DMA2 local request: "REQUEST130_CAN10_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST130_CAN10_TX_EVENT                  (130U)
/* DMA2 local request: "REQUEST131_CAN11_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST131_CAN11_TX_FIFO                  (131U)
/* DMA2 local request: "REQUEST132_CAN11_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST132_CAN11_RX_FIFO0                  (132U)
/* DMA2 local request: "REQUEST133_CAN11_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST133_CAN11_RX_FIFO1                  (133U)
/* DMA2 local request: "REQUEST134_CAN11_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST134_CAN11_TX_EVENT                  (134U)
/* DMA2 local request: "REQUEST135_CAN12_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST135_CAN12_TX_FIFO                  (135U)
/* DMA2 local request: "REQUEST136_CAN12_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST136_CAN12_RX_FIFO0                  (136U)
/* DMA2 local request: "REQUEST137_CAN12_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST137_CAN12_RX_FIFO1                  (137U)
/* DMA2 local request: "REQUEST138_CAN12_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST138_CAN12_TX_EVENT                  (138U)
/* DMA2 local request: "REQUEST139_ASI0_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST139_ASI0_LIN_UART_TX                  (139U)
/* DMA2 local request: "REQUEST1_ASI140_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST1_ASI140_LIN_UART_RX                  (1U)
/* DMA2 local request: "REQUEST140_ASI1_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST140_ASI1_LIN_UART_TX                  (140U)
/* DMA2 local request: "REQUEST142_ASI1_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST142_ASI1_LIN_UART_RX                  (142U)
/* DMA2 local request: "REQUEST143_ASI2_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST143_ASI2_LIN_UART_TX                  (143U)
/* DMA2 local request: "REQUEST144_ASI2_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST144_ASI2_LIN_UART_RX                  (144U)
/* DMA2 local request: "REQUEST145_ASI3_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST145_ASI3_LIN_UART_TX                  (145U)
/* DMA2 local request: "REQUEST146_ASI3_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST146_ASI3_LIN_UART_RX                  (146U)
/* DMA2 local request: "REQUEST147_ASI4_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST147_ASI4_LIN_UART_TX                  (147U)
/* DMA2 local request: "REQUEST148_ASI4_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST148_ASI4_LIN_UART_RX                  (148U)
/* DMA2 local request: "REQUEST149_ASI5_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST149_ASI5_LIN_UART_TX                  (149U)
/* DMA2 local request: "REQUEST150_ASI5_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST150_ASI5_LIN_UART_RX                  (150U)
/* DMA2 local request: "REQUEST151_ASI6_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST151_ASI6_LIN_UART_TX                  (151U)
/* DMA2 local request: "REQUEST152_ASI6_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST152_ASI6_LIN_UART_RX                  (152U)
/* DMA2 local request: "REQUEST153_ASI7_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST153_ASI7_LIN_UART_TX                  (153U)
/* DMA2 local request: "REQUEST154_ASI7_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST154_ASI7_LIN_UART_RX                  (154U)
/* DMA2 local request: "REQUEST155_ASI8_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST155_ASI8_LIN_UART_TX                  (155U)
/* DMA2 local request: "REQUEST156_ASI8_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST156_ASI8_LIN_UART_RX                  (156U)
/* DMA2 local request: "REQUEST157_ASI9_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST157_ASI9_LIN_UART_TX                  (157U)
/* DMA2 local request: "REQUEST158_ASI9_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST158_ASI9_LIN_UART_RX                  (158U)
/* DMA2 local request: "REQUEST159_ASI10_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST159_ASI10_LIN_UART_TX                  (159U)
/* DMA2 local request: "REQUEST160_ASI10_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST160_ASI10_LIN_UART_RX                  (160U)
/* DMA2 local request: "REQUEST161_ASI11_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST161_ASI11_LIN_UART_TX                  (161U)
/* DMA2 local request: "REQUEST162_ASI11_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST162_ASI11_LIN_UART_RX                  (162U)
/* DMA2 local request: "REQUEST163_ESPI3_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST163_ESPI3_TX                  (163U)
/* DMA2 local request: "REQUEST164_ESPI3_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST164_ESPI3_RX                  (164U)
/* DMA2 local request: "REQUEST165_ESPI4_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST165_ESPI4_TX                  (165U)
/* DMA2 local request: "REQUEST166_ESPI4_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST166_ESPI4_RX                  (166U)
/* DMA2 local request: "REQUEST167_I2C0_TX_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST167_I2C0_TX_RX                  (167U)


/* DMA global request of multiplexer: "REQUEST0_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST0_GTM                  (0U)
/* DMA global request of multiplexer: "REQUEST1_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST1_GTM                  (1U)
/* DMA global request of multiplexer: "REQUEST2_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST2_GTM                  (2U)
/* DMA global request of multiplexer: "REQUEST3_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST3_GTM                  (3U)
/* DMA global request of multiplexer: "REQUEST4_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST4_GTM                  (4U)
/* DMA global request of multiplexer: "REQUEST5_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST5_GTM                  (5U)
/* DMA global request of multiplexer: "REQUEST6_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST6_GTM                  (6U)
/* DMA global request of multiplexer: "REQUEST7_GTM" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST7_GTM                  (7U)
/* DMA global request of multiplexer: "REQUEST15_SARADC0_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST15_SARADC0_RESULT0                  (15U)
/* DMA global request of multiplexer: "REQUEST16_SARADC0_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST16_SARADC0_RESULT1                  (16U)
/* DMA global request of multiplexer: "REQUEST17_SARADC0_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST17_SARADC0_RESULT2                  (17U)
/* DMA global request of multiplexer: "REQUEST18_SARADC0_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST18_SARADC0_RESULT3                  (18U)
/* DMA global request of multiplexer: "REQUEST19_SARADC0_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST19_SARADC0_RESULT4                  (19U)
/* DMA global request of multiplexer: "REQUEST20_SARADC0_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST20_SARADC0_RESULT5                  (20U)
/* DMA global request of multiplexer: "REQUEST21_SARADC0_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST21_SARADC0_RESULT6                  (21U)
/* DMA global request of multiplexer: "REQUEST22_SARADC0_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST22_SARADC0_RESULT7                  (22U)
/* DMA global request of multiplexer: "REQUEST23_SARADC0_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST23_SARADC0_RESULT8                  (23U)
/* DMA global request of multiplexer: "REQUEST24_SARADC0_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST24_SARADC0_RESULT9                  (24U)
/* DMA global request of multiplexer: "REQUEST25_SARADC0_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST25_SARADC0_RESULT10                  (25U)
/* DMA global request of multiplexer: "REQUEST26_SARADC0_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST26_SARADC0_RESULT11                  (26U)
/* DMA global request of multiplexer: "REQUEST27_SARADC0_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST27_SARADC0_RESULT12                  (27U)
/* DMA global request of multiplexer: "REQUEST28_SARADC0_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST28_SARADC0_RESULT13                  (28U)
/* DMA global request of multiplexer: "REQUEST29_SARADC0_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST29_SARADC0_RESULT14                  (29U)
/* DMA global request of multiplexer: "REQUEST30_SARADC0_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST30_SARADC0_RESULT15                  (30U)
/* DMA global request of multiplexer: "REQUEST31_SARADC_GLOBAL_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST31_SARADC_GLOBAL_RESULT                  (31U)
/* DMA global request of multiplexer: "REQUEST32_SARADC1_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST32_SARADC1_RESULT0                  (32U)
/* DMA global request of multiplexer: "REQUEST33_SARADC1_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST33_SARADC1_RESULT1                  (33U)
/* DMA global request of multiplexer: "REQUEST34_SARADC1_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST34_SARADC1_RESULT2                  (34U)
/* DMA global request of multiplexer: "REQUEST35_SARADC1_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST35_SARADC1_RESULT3                  (35U)
/* DMA global request of multiplexer: "REQUEST36_SARADC1_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST36_SARADC1_RESULT4                  (36U)
/* DMA global request of multiplexer: "REQUEST37_SARADC1_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST37_SARADC1_RESULT5                  (37U)
/* DMA global request of multiplexer: "REQUEST38_SARADC1_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST38_SARADC1_RESULT6                  (38U)
/* DMA global request of multiplexer: "REQUEST39_SARADC1_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST39_SARADC1_RESULT7                  (39U)
/* DMA global request of multiplexer: "REQUEST40_SARADC1_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST40_SARADC1_RESULT8                  (40U)
/* DMA global request of multiplexer: "REQUEST41_SARADC1_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST41_SARADC1_RESULT9                  (41U)
/* DMA global request of multiplexer: "REQUEST42_SARADC1_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST42_SARADC1_RESULT10                  (42U)
/* DMA global request of multiplexer: "REQUEST43_SARADC1_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST43_SARADC1_RESULT11                  (43U)
/* DMA global request of multiplexer: "REQUEST44_SARADC1_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST44_SARADC1_RESULT12                  (44U)
/* DMA global request of multiplexer: "REQUEST45_SARADC1_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST45_SARADC1_RESULT13                  (45U)
/* DMA global request of multiplexer: "REQUEST46_SARADC1_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST46_SARADC1_RESULT14                  (46U)
/* DMA global request of multiplexer: "REQUEST47_SARADC1_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST47_SARADC1_RESULT15                  (47U)
/* DMA global request of multiplexer: "REQUEST48_SARADC2_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST48_SARADC2_RESULT0                  (48U)
/* DMA global request of multiplexer: "REQUEST49_SARADC2_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST49_SARADC2_RESULT1                  (49U)
/* DMA global request of multiplexer: "REQUEST50_SARADC2_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST50_SARADC2_RESULT2                  (50U)
/* DMA global request of multiplexer: "REQUEST51_SARADC2_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST51_SARADC2_RESULT3                  (51U)
/* DMA global request of multiplexer: "REQUEST52_SARADC2_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST52_SARADC2_RESULT4                  (52U)
/* DMA global request of multiplexer: "REQUEST53_SARADC2_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST53_SARADC2_RESULT5                  (53U)
/* DMA global request of multiplexer: "REQUEST54_SARADC2_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST54_SARADC2_RESULT6                  (54U)
/* DMA global request of multiplexer: "REQUEST55_SARADC2_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST55_SARADC2_RESULT7                  (55U)
/* DMA global request of multiplexer: "REQUEST56_SARADC2_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST56_SARADC2_RESULT8                  (56U)
/* DMA global request of multiplexer: "REQUEST57_SARADC2_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST57_SARADC2_RESULT9                  (57U)
/* DMA global request of multiplexer: "REQUEST58_SARADC2_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST58_SARADC2_RESULT10                  (58U)
/* DMA global request of multiplexer: "REQUEST59_SARADC2_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST59_SARADC2_RESULT11                  (59U)
/* DMA global request of multiplexer: "REQUEST60_SARADC2_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST60_SARADC2_RESULT12                  (60U)
/* DMA global request of multiplexer: "REQUEST61_SARADC2_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST61_SARADC2_RESULT13                  (61U)
/* DMA global request of multiplexer: "REQUEST62_SARADC2_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST62_SARADC2_RESULT14                  (62U)
/* DMA global request of multiplexer: "REQUEST63_SARADC2_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST63_SARADC2_RESULT15                  (63U)
/* DMA global request of multiplexer: "REQUEST64_SARADC3_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST64_SARADC3_RESULT0                  (64U)
/* DMA global request of multiplexer: "REQUEST65_SARADC3_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST65_SARADC3_RESULT1                  (65U)
/* DMA global request of multiplexer: "REQUEST66_SARADC3_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST66_SARADC3_RESULT2                  (66U)
/* DMA global request of multiplexer: "REQUEST67_SARADC3_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST67_SARADC3_RESULT3                  (67U)
/* DMA global request of multiplexer: "REQUEST68_SARADC3_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST68_SARADC3_RESULT4                  (68U)
/* DMA global request of multiplexer: "REQUEST69_SARADC3_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST69_SARADC3_RESULT5                  (69U)
/* DMA global request of multiplexer: "REQUEST70_SARADC3_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST70_SARADC3_RESULT6                  (70U)
/* DMA global request of multiplexer: "REQUEST71_SARADC3_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST71_SARADC3_RESULT7                  (71U)
/* DMA global request of multiplexer: "REQUEST72_SARADC3_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST72_SARADC3_RESULT8                  (72U)
/* DMA global request of multiplexer: "REQUEST73_SARADC3_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST73_SARADC3_RESULT9                  (73U)
/* DMA global request of multiplexer: "REQUEST74_SARADC3_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST74_SARADC3_RESULT10                  (74U)
/* DMA global request of multiplexer: "REQUEST75_SARADC3_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST75_SARADC3_RESULT11                  (75U)
/* DMA global request of multiplexer: "REQUEST76_SARADC3_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST76_SARADC3_RESULT12                  (76U)
/* DMA global request of multiplexer: "REQUEST77_SARADC3_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST77_SARADC3_RESULT13                  (77U)
/* DMA global request of multiplexer: "REQUEST78_SARADC3_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST78_SARADC3_RESULT14                  (78U)
/* DMA global request of multiplexer: "REQUEST79_SARADC3_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST79_SARADC3_RESULT15                  (79U)
/* DMA global request of multiplexer: "REQUEST112_ESPI0_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST112_ESPI0_TX                  (112U)
/* DMA global request of multiplexer: "REQUEST113_ESPI0_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST113_ESPI0_RX                  (113U)
/* DMA global request of multiplexer: "REQUEST114_ESPI1_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST114_ESPI1_TX                  (114U)
/* DMA global request of multiplexer: "REQUEST115_ESPI1_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST115_ESPI1_RX                  (115U)
/* DMA global request of multiplexer: "REQUEST116_ESPI2_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST116_ESPI2_TX                  (116U)
/* DMA global request of multiplexer: "REQUEST117_ESPI2_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST117_ESPI2_RX                  (117U)
/* DMA global request of multiplexer: "REQUEST118_ESPI5_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST118_ESPI5_TX                  (118U)
/* DMA global request of multiplexer: "REQUEST119_ESPI5_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST119_ESPI5_RX                  (119U)
/* DMA global request of multiplexer: "REQUEST120_ESPI6_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST120_ESPI6_TX                  (120U)
/* DMA global request of multiplexer: "REQUEST126_CAN00_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST126_CAN00_TX_FIFO                  (126U)
/* DMA global request of multiplexer: "REQUEST127_CAN00_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST127_CAN00_RX_FIFO0                  (127U)
/* DMA global request of multiplexer: "REQUEST128_CAN00_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST128_CAN00_RX_FIFO1                  (128U)
/* DMA global request of multiplexer: "REQUEST129_CAN00_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST129_CAN00_TX_EVENT                  (129U)
/* DMA global request of multiplexer: "REQUEST130_CAN01_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST130_CAN01_TX_FIFO                  (130U)
/* DMA global request of multiplexer: "REQUEST131_CAN01_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST131_CAN01_RX_FIFO0                  (131U)
/* DMA global request of multiplexer: "REQUEST132_CAN01_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST132_CAN01_RX_FIFO1                  (132U)
/* DMA global request of multiplexer: "REQUEST133_CAN01_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST133_CAN01_TX_EVENT                  (133U)
/* DMA global request of multiplexer: "REQUEST134_CAN02_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST134_CAN02_TX_FIFO                  (134U)
/* DMA global request of multiplexer: "REQUEST135_CAN02_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST135_CAN02_RX_FIFO0                  (135U)
/* DMA global request of multiplexer: "REQUEST136_CAN02_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST136_CAN02_RX_FIFO1                  (136U)
/* DMA global request of multiplexer: "REQUEST137_CAN02_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST137_CAN02_TX_EVENT                  (137U)
/* DMA global request of multiplexer: "REQUEST138_ASI0_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST138_ASI0_LIN_UART_TX                  (138U)
/* DMA global request of multiplexer: "REQUEST139_ASI0_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST139_ASI0_LIN_UART_RX                  (139U)
/* DMA global request of multiplexer: "REQUEST140_ASI1_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST140_ASI1_LIN_UART_TX                  (140U)
/* DMA global request of multiplexer: "REQUEST141_ASI1_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST141_ASI1_LIN_UART_RX                  (141U)
/* DMA global request of multiplexer: "REQUEST142_ASI2_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST142_ASI2_LIN_UART_TX                  (142U)
/* DMA global request of multiplexer: "REQUEST143_ASI2_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST143_ASI2_LIN_UART_RX                  (143U)
/* DMA global request of multiplexer: "REQUEST144_ASI3_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST144_ASI3_LIN_UART_TX                  (144U)
/* DMA global request of multiplexer: "REQUEST145_ASI3_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST145_ASI3_LIN_UART_RX                  (145U)
/* DMA global request of multiplexer: "REQUEST146_ASI4_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST146_ASI4_LIN_UART_TX                  (146U)
/* DMA global request of multiplexer: "REQUEST147_ASI4_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST147_ASI4_LIN_UART_RX                  (147U)
/* DMA global request of multiplexer: "REQUEST148_ASI5_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST148_ASI5_LIN_UART_TX                  (148U)
/* DMA global request of multiplexer: "REQUEST149_ASI5_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST149_ASI5_LIN_UART_RX                  (149U)
/* DMA global request of multiplexer: "REQUEST150_ASI6_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST150_ASI6_LIN_UART_TX                  (150U)
/* DMA global request of multiplexer: "REQUEST151_ASI6_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST151_ASI6_LIN_UART_RX                  (151U)
/* DMA global request of multiplexer: "REQUEST152_ASI7_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST152_ASI7_LIN_UART_TX                  (152U)
/* DMA global request of multiplexer: "REQUEST153_ASI7_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST153_ASI7_LIN_UART_RX                  (153U)
/* DMA global request of multiplexer: "REQUEST154_ESPI3_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST154_ESPI3_TX                  (154U)
/* DMA global request of multiplexer: "REQUEST155_ESPI3_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST155_ESPI3_RX                  (155U)
/* DMA global request of multiplexer: "REQUEST156_ESPI4_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST156_ESPI4_TX                  (156U)
/* DMA global request of multiplexer: "REQUEST157_ESPI4_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST157_ESPI4_RX                  (157U)
/* DMA global request of multiplexer: "REQUEST158_I2C0_TX_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST158_I2C0_TX_RX                  (158U)
/* DMA global request of multiplexer: "REQUEST163_CAN10_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST163_CAN10_TX_FIFO                  (163U)
/* DMA global request of multiplexer: "REQUEST164_CAN10_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST164_CAN10_RX_FIFO0                  (164U)
/* DMA global request of multiplexer: "REQUEST165_CAN10_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST165_CAN10_RX_FIFO1                  (165U)
/* DMA global request of multiplexer: "REQUEST166_CAN10_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST166_CAN10_TX_EVENT                  (166U)
/* DMA global request of multiplexer: "REQUEST167_CAN11_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST167_CAN11_TX_FIFO                  (167U)
/* DMA global request of multiplexer: "REQUEST168_CAN11_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST168_CAN11_RX_FIFO0                  (168U)
/* DMA global request of multiplexer: "REQUEST169_CAN11_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST169_CAN11_RX_FIFO1                  (169U)
/* DMA global request of multiplexer: "REQUEST170_CAN11_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST170_CAN11_TX_EVENT                  (170U)
/* DMA global request of multiplexer: "REQUEST171_CAN12_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST171_CAN12_TX_FIFO                  (171U)
/* DMA global request of multiplexer: "REQUEST172_CAN12_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST172_CAN12_RX_FIFO0                  (172U)
/* DMA global request of multiplexer: "REQUEST173_CAN12_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST173_CAN12_RX_FIFO1                  (173U)
/* DMA global request of multiplexer: "REQUEST174_CAN12_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST174_CAN12_TX_EVENT                  (174U)
/* DMA global request of multiplexer: "REQUEST315_ECRC_CH0_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST315_ECRC_CH0_RESULT                  (315U)
/* DMA global request of multiplexer: "REQUEST316_ECRC_CH1_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST316_ECRC_CH1_RESULT                  (316U)
/* DMA global request of multiplexer: "REQUEST317_ECRC_CH2_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST317_ECRC_CH2_RESULT                  (317U)
/* DMA global request of multiplexer: "REQUEST318_ECRC_CH3_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST318_ECRC_CH3_RESULT                  (318U)
/* DMA global request of multiplexer: "REQUEST319_ECRC_CH4_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST319_ECRC_CH4_RESULT                  (319U)
/* DMA global request of multiplexer: "REQUEST320_ECRC_CH5_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST320_ECRC_CH5_RESULT                  (320U)
/* DMA global request of multiplexer: "REQUEST321_ECRC_CH6_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST321_ECRC_CH6_RESULT                  (321U)
/* DMA global request of multiplexer: "REQUEST322_ECRC_CH7_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST322_ECRC_CH7_RESULT                  (322U)
/* DMA global request of multiplexer: "REQUEST323_ASI8_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST323_ASI8_LIN_UART_TX                  (323U)
/* DMA global request of multiplexer: "REQUEST324_ASI8_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST324_ASI8_LIN_UART_RX                  (324U)
/* DMA global request of multiplexer: "REQUEST325_ASI9_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST325_ASI9_LIN_UART_TX                  (325U)
/* DMA global request of multiplexer: "REQUEST326_ASI9_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST326_ASI9_LIN_UART_RX                  (326U)
/* DMA global request of multiplexer: "REQUEST327_ASI10_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST327_ASI10_LIN_UART_TX                  (327U)
/* DMA global request of multiplexer: "REQUEST328_ASI10_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST328_ASI10_LIN_UART_RX                  (328U)
/* DMA global request of multiplexer: "REQUEST329_ASI11_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST329_ASI11_LIN_UART_TX                  (329U)
/* DMA global request of multiplexer: "REQUEST330_ASI11_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST330_ASI11_LIN_UART_RX                  (330U)

/****************************************************************************************************
**                          Macro definition of transfer ID                                        **
****************************************************************************************************/
/* Transfer ID(M2M) in Channel ID0(M2M): Physical channel0 in DMA0 */
#ifndef DmaConf_DmaChTransferConfig_M2M_Transfer
#define DmaConf_DmaChTransferConfig_M2M_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_Transfer */
/* Transfer ID(M2M_Continuous) in Channel ID1(M2M_Continuous): Physical channel1 in DMA0 */
#ifndef DmaConf_DmaChTransferConfig_M2M_Continuous_Transfer
#define DmaConf_DmaChTransferConfig_M2M_Continuous_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_Continuous_Transfer */
/* Transfer ID(M2M_DoubleBuf) in Channel ID2(M2M_DoubleBuf): Physical channel2 in DMA0 */
#ifndef DmaConf_DmaChTransferConfig_M2M_DoubleBuf_Transfer
#define DmaConf_DmaChTransferConfig_M2M_DoubleBuf_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_DoubleBuf_Transfer */
/* Transfer ID(M2M_CircBuf) in Channel ID3(M2M_CircBuf): Physical channel3 in DMA0 */
#ifndef DmaConf_DmaChTransferConfig_M2M_CircBuf_Transfer
#define DmaConf_DmaChTransferConfig_M2M_CircBuf_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_CircBuf_Transfer */
/* Transfer ID(M2M_LinkedList) in Channel ID4(M2M_LinkedList): Physical channel12 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_LinkedListTransfer0
#define DmaConf_DmaChTransferConfig_LinkedListTransfer0             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_LinkedListTransfer0 */
/* Transfer ID(M2M_LinkedList) in Channel ID4(M2M_LinkedList): Physical channel12 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_LinkedListTransfer1
#define DmaConf_DmaChTransferConfig_LinkedListTransfer1             ((Dma_TransferType)1U)
#endif /* DmaConf_DmaChTransferConfig_LinkedListTransfer1 */
/* Transfer ID(M2M_LinkedList) in Channel ID4(M2M_LinkedList): Physical channel12 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_LinkedListTransfer2
#define DmaConf_DmaChTransferConfig_LinkedListTransfer2             ((Dma_TransferType)2U)
#endif /* DmaConf_DmaChTransferConfig_LinkedListTransfer2 */
/* Transfer ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel13 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_BasicTransfer
#define DmaConf_DmaChTransferConfig_BasicTransfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_BasicTransfer */
/* Transfer ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel13 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_ShadowTransfer0
#define DmaConf_DmaChTransferConfig_ShadowTransfer0             ((Dma_TransferType)1U)
#endif /* DmaConf_DmaChTransferConfig_ShadowTransfer0 */
/* Transfer ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel13 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_ShadowTransfer1
#define DmaConf_DmaChTransferConfig_ShadowTransfer1             ((Dma_TransferType)2U)
#endif /* DmaConf_DmaChTransferConfig_ShadowTransfer1 */
/* Transfer ID(M2M_Pattern) in Channel ID6(M2M_Pattern): Physical channel14 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_M2M_Pattern_Transfer
#define DmaConf_DmaChTransferConfig_M2M_Pattern_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_Pattern_Transfer */
/* Transfer ID(M2M_Daisy0) in Channel ID7(M2M_Daisy0): Physical channel15 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_M2M_Daisy0_Transfer
#define DmaConf_DmaChTransferConfig_M2M_Daisy0_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_Daisy0_Transfer */
/* Transfer ID(M2M_Daisy1) in Channel ID8(M2M_Daisy1): Physical channel16 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_M2M_Daisy1_Transfer
#define DmaConf_DmaChTransferConfig_M2M_Daisy1_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_Daisy1_Transfer */
/* Transfer ID(ADC1_Channel0) in Channel ID9(ADC1_Channel0): Physical channel2 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_DmaChTransferConfig_0
#define DmaConf_DmaChTransferConfig_DmaChTransferConfig_0             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_DmaChTransferConfig_0 */
/* Transfer ID(ADC1_Channel1) in Channel ID10(ADC1_Channel1): Physical channel3 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_Channel1_Transfer
#define DmaConf_DmaChTransferConfig_ADC1_Channel1_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_Channel1_Transfer */
/* Transfer ID(ADC1_Channel2) in Channel ID11(ADC1_Channel2): Physical channel4 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_Channel2_Transfer
#define DmaConf_DmaChTransferConfig_ADC1_Channel2_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_Channel2_Transfer */
/* Transfer ID(ADC1_Channel3) in Channel ID12(ADC1_Channel3): Physical channel5 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_Channel3_Transfer
#define DmaConf_DmaChTransferConfig_ADC1_Channel3_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_Channel3_Transfer */
/* Transfer ID(ADC1_Channel7) in Channel ID13(ADC1_Channel7): Physical channel6 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_Channel7_Transfer
#define DmaConf_DmaChTransferConfig_ADC1_Channel7_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_Channel7_Transfer */
/* Transfer ID(ADC1_GroupSwTrig2) in Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel4
#define DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel4             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel4 */
/* Transfer ID(ADC1_GroupSwTrig2) in Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel5
#define DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel5             ((Dma_TransferType)1U)
#endif /* DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel5 */
/* Transfer ID(ADC1_GroupSwTrig2) in Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel6
#define DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel6             ((Dma_TransferType)2U)
#endif /* DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel6 */
/* Transfer ID(ADC1_AllChToOneResReg) in Channel ID17(ADC1_AllChToOneResReg): Physical channel17 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_AllChToOneResRegTransfer
#define DmaConf_DmaChTransferConfig_ADC1_AllChToOneResRegTransfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_AllChToOneResRegTransfer */

/****************************************************************************************************
**                          Macro definition of shadow operation                                   **
****************************************************************************************************/
/* Shadowing operation ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel13 in DMA2 */
#ifndef DmaConf_DmaChShadowConfig_DmaChShadowConfig_0
#define DmaConf_DmaChShadowConfig_DmaChShadowConfig_0              ((Dma_ShadowingType)0U)
#endif /* DmaConf_DmaChShadowConfig_DmaChShadowConfig_0 */
/* Shadowing operation ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel13 in DMA2 */
#ifndef DmaConf_DmaChShadowConfig_DmaChShadowConfig_1
#define DmaConf_DmaChShadowConfig_DmaChShadowConfig_1              ((Dma_ShadowingType)1U)
#endif /* DmaConf_DmaChShadowConfig_DmaChShadowConfig_1 */

/****************************************************************************************************
**                          Macro definition of logical channel ID                                 **
****************************************************************************************************/
/* Channel ID0(M2M): Physical channel0 in DMA0 */
#ifndef DmaConf_DmaChannel_M2M
#define DmaConf_DmaChannel_M2M                      ((Dma_ChannelType)0)
#endif /* DmaConf_DmaChannel_M2M */

/* Channel ID1(M2M_Continuous): Physical channel1 in DMA0 */
#ifndef DmaConf_DmaChannel_M2M_Continuous
#define DmaConf_DmaChannel_M2M_Continuous                      ((Dma_ChannelType)1)
#endif /* DmaConf_DmaChannel_M2M_Continuous */

/* Channel ID2(M2M_DoubleBuf): Physical channel2 in DMA0 */
#ifndef DmaConf_DmaChannel_M2M_DoubleBuf
#define DmaConf_DmaChannel_M2M_DoubleBuf                      ((Dma_ChannelType)2)
#endif /* DmaConf_DmaChannel_M2M_DoubleBuf */

/* Channel ID3(M2M_CircBuf): Physical channel3 in DMA0 */
#ifndef DmaConf_DmaChannel_M2M_CircBuf
#define DmaConf_DmaChannel_M2M_CircBuf                      ((Dma_ChannelType)3)
#endif /* DmaConf_DmaChannel_M2M_CircBuf */

/* Channel ID4(M2M_LinkedList): Physical channel12 in DMA2 */
#ifndef DmaConf_DmaChannel_M2M_LinkedList
#define DmaConf_DmaChannel_M2M_LinkedList                      ((Dma_ChannelType)4)
#endif /* DmaConf_DmaChannel_M2M_LinkedList */

/* Channel ID5(M2M_Shadow): Physical channel13 in DMA2 */
#ifndef DmaConf_DmaChannel_M2M_Shadow
#define DmaConf_DmaChannel_M2M_Shadow                      ((Dma_ChannelType)5)
#endif /* DmaConf_DmaChannel_M2M_Shadow */

/* Channel ID6(M2M_Pattern): Physical channel14 in DMA2 */
#ifndef DmaConf_DmaChannel_M2M_Pattern
#define DmaConf_DmaChannel_M2M_Pattern                      ((Dma_ChannelType)6)
#endif /* DmaConf_DmaChannel_M2M_Pattern */

/* Channel ID7(M2M_Daisy0): Physical channel15 in DMA2 */
#ifndef DmaConf_DmaChannel_M2M_Daisy0
#define DmaConf_DmaChannel_M2M_Daisy0                      ((Dma_ChannelType)7)
#endif /* DmaConf_DmaChannel_M2M_Daisy0 */

/* Channel ID8(M2M_Daisy1): Physical channel16 in DMA2 */
#ifndef DmaConf_DmaChannel_M2M_Daisy1
#define DmaConf_DmaChannel_M2M_Daisy1                      ((Dma_ChannelType)8)
#endif /* DmaConf_DmaChannel_M2M_Daisy1 */

/* Channel ID9(ADC1_Channel0): Physical channel2 in DMA2 */
#ifndef DmaConf_DmaChannel_ADC1_Channel0
#define DmaConf_DmaChannel_ADC1_Channel0                      ((Dma_ChannelType)9)
#endif /* DmaConf_DmaChannel_ADC1_Channel0 */

/* Channel ID10(ADC1_Channel1): Physical channel3 in DMA2 */
#ifndef DmaConf_DmaChannel_ADC1_Channel1
#define DmaConf_DmaChannel_ADC1_Channel1                      ((Dma_ChannelType)10)
#endif /* DmaConf_DmaChannel_ADC1_Channel1 */

/* Channel ID11(ADC1_Channel2): Physical channel4 in DMA2 */
#ifndef DmaConf_DmaChannel_ADC1_Channel2
#define DmaConf_DmaChannel_ADC1_Channel2                      ((Dma_ChannelType)11)
#endif /* DmaConf_DmaChannel_ADC1_Channel2 */

/* Channel ID12(ADC1_Channel3): Physical channel5 in DMA2 */
#ifndef DmaConf_DmaChannel_ADC1_Channel3
#define DmaConf_DmaChannel_ADC1_Channel3                      ((Dma_ChannelType)12)
#endif /* DmaConf_DmaChannel_ADC1_Channel3 */

/* Channel ID13(ADC1_Channel7): Physical channel6 in DMA2 */
#ifndef DmaConf_DmaChannel_ADC1_Channel7
#define DmaConf_DmaChannel_ADC1_Channel7                      ((Dma_ChannelType)13)
#endif /* DmaConf_DmaChannel_ADC1_Channel7 */

/* Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA2 */
#ifndef DmaConf_DmaChannel_ADC1_GroupSwTrig2
#define DmaConf_DmaChannel_ADC1_GroupSwTrig2                      ((Dma_ChannelType)14)
#endif /* DmaConf_DmaChannel_ADC1_GroupSwTrig2 */

/* Channel ID15(SPITx): Physical channel8 in DMA2 */
#ifndef DmaConf_DmaChannel_SPITx
#define DmaConf_DmaChannel_SPITx                      ((Dma_ChannelType)15)
#endif /* DmaConf_DmaChannel_SPITx */

/* Channel ID16(SPIRx): Physical channel9 in DMA2 */
#ifndef DmaConf_DmaChannel_SPIRx
#define DmaConf_DmaChannel_SPIRx                      ((Dma_ChannelType)16)
#endif /* DmaConf_DmaChannel_SPIRx */

/* Channel ID17(ADC1_AllChToOneResReg): Physical channel17 in DMA2 */
#ifndef DmaConf_DmaChannel_ADC1_AllChToOneResReg
#define DmaConf_DmaChannel_ADC1_AllChToOneResReg                      ((Dma_ChannelType)17)
#endif /* DmaConf_DmaChannel_ADC1_AllChToOneResReg */


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
#endif  /* DMA_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


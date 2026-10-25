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
/* Number of transfer or LLI multiple configuration sets allocated to Core2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_TRANSFER_NUM_CORE2                         (0U)
/* Number of transfer or LLI multiple configuration sets allocated to Core3 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_TRANSFER_NUM_CORE3                         (0U)

/* Number of shadowing multiple configuration sets
Configuration: DmaChShadowConfig */
#define DMA_CFG_MULTI_SHADOWING_NUM                        (1U)
/* Number of shadowing multiple configuration sets allocated to Core0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_SHADOWING_NUM_CORE0                         (1U)
/* Number of shadowing multiple configuration sets allocated to Core1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_SHADOWING_NUM_CORE1                         (0U)
/* Number of shadowing multiple configuration sets allocated to Core2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_SHADOWING_NUM_CORE2                         (0U)
/* Number of shadowing multiple configuration sets allocated to Core3 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_SHADOWING_NUM_CORE3                         (0U)

                    /* Number of daisy chain of core0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DAISY_CHAIN_NUM_CORE0                         (2U)
                    /* Number of daisy chain of core1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DAISY_CHAIN_NUM_CORE1                         (0U)
                    /* Number of daisy chain of core2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DAISY_CHAIN_NUM_CORE2                         (0U)
                    /* Number of daisy chain of core3 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DAISY_CHAIN_NUM_CORE3                         (0U)

/* Number of channels allocated to Core0 */
#define DMA_CFG_MAX_CHANNELS_CORE0                         (18U)
/* Number of channels allocated to Core1 */
#define DMA_CFG_MAX_CHANNELS_CORE1                         (1U)
/* Number of channels allocated to Core2 */
#define DMA_CFG_MAX_CHANNELS_CORE2                         (0U)
/* Number of channels allocated to Core3 */
#define DMA_CFG_MAX_CHANNELS_CORE3                         (0U)
/* Total number of channels */
#define DMA_CFG_MAX_CHANNELS                               (19U)

/* The number of all HW units */
#define DMA_MAX_HWUNIT_COUNT                               (4U)

/* ID of DMA HwUnit1 */
#define DMA_HWUNIT_DMA0                                    (0U)
/* ID of DMA HwUnit2 */
#define DMA_HWUNIT_DMA1                                    (1U)
/* ID of DMA HwUnit3 */
#define DMA_HWUNIT_DMA2                                    (2U)
/* ID of DMA HwUnit4 */
#define DMA_HWUNIT_DMA3                                    (3U)

/* IDs of physical channel in DMA0 */
/* ID of physical channel0 */
#define DMA_DMA0_PHYCHANNEL0                               (0U)
/* ID of physical channel1 */
#define DMA_DMA0_PHYCHANNEL1                               (1U)
/* ID of physical channel2 */
#define DMA_DMA0_PHYCHANNEL2                               (2U)
/* ID of physical channel3 */
#define DMA_DMA0_PHYCHANNEL3                               (3U)
/* ID of physical channel4 */
#define DMA_DMA0_PHYCHANNEL4                               (4U)
/* ID of physical channel5 */
#define DMA_DMA0_PHYCHANNEL5                               (5U)
/* ID of physical channel6 */
#define DMA_DMA0_PHYCHANNEL6                               (6U)
/* ID of physical channel7 */
#define DMA_DMA0_PHYCHANNEL7                               (7U)
/* ID of physical channel8 */
#define DMA_DMA0_PHYCHANNEL8                               (8U)
/* ID of physical channel9 */
#define DMA_DMA0_PHYCHANNEL9                               (9U)
/* ID of physical channel10 */
#define DMA_DMA0_PHYCHANNEL10                               (10U)
/* ID of physical channel11 */
#define DMA_DMA0_PHYCHANNEL11                               (11U)
/* ID of physical channel12 */
#define DMA_DMA0_PHYCHANNEL12                               (12U)
/* ID of physical channel13 */
#define DMA_DMA0_PHYCHANNEL13                               (13U)
/* ID of physical channel14 */
#define DMA_DMA0_PHYCHANNEL14                               (14U)
/* ID of physical channel15 */
#define DMA_DMA0_PHYCHANNEL15                               (15U)

/* IDs of physical channel in DMA1 */
/* ID of physical channel0 */
#define DMA_DMA1_PHYCHANNEL0                               (0U)
/* ID of physical channel1 */
#define DMA_DMA1_PHYCHANNEL1                               (1U)
/* ID of physical channel2 */
#define DMA_DMA1_PHYCHANNEL2                               (2U)
/* ID of physical channel3 */
#define DMA_DMA1_PHYCHANNEL3                               (3U)
/* ID of physical channel4 */
#define DMA_DMA1_PHYCHANNEL4                               (4U)
/* ID of physical channel5 */
#define DMA_DMA1_PHYCHANNEL5                               (5U)
/* ID of physical channel6 */
#define DMA_DMA1_PHYCHANNEL6                               (6U)
/* ID of physical channel7 */
#define DMA_DMA1_PHYCHANNEL7                               (7U)
/* ID of physical channel8 */
#define DMA_DMA1_PHYCHANNEL8                               (8U)
/* ID of physical channel9 */
#define DMA_DMA1_PHYCHANNEL9                               (9U)
/* ID of physical channel10 */
#define DMA_DMA1_PHYCHANNEL10                               (10U)
/* ID of physical channel11 */
#define DMA_DMA1_PHYCHANNEL11                               (11U)
/* ID of physical channel12 */
#define DMA_DMA1_PHYCHANNEL12                               (12U)
/* ID of physical channel13 */
#define DMA_DMA1_PHYCHANNEL13                               (13U)
/* ID of physical channel14 */
#define DMA_DMA1_PHYCHANNEL14                               (14U)
/* ID of physical channel15 */
#define DMA_DMA1_PHYCHANNEL15                               (15U)
/* ID of physical channel16 */
#define DMA_DMA1_PHYCHANNEL16                               (16U)
/* ID of physical channel17 */
#define DMA_DMA1_PHYCHANNEL17                               (17U)
/* ID of physical channel18 */
#define DMA_DMA1_PHYCHANNEL18                               (18U)
/* ID of physical channel19 */
#define DMA_DMA1_PHYCHANNEL19                               (19U)
/* ID of physical channel20 */
#define DMA_DMA1_PHYCHANNEL20                               (20U)
/* ID of physical channel21 */
#define DMA_DMA1_PHYCHANNEL21                               (21U)
/* ID of physical channel22 */
#define DMA_DMA1_PHYCHANNEL22                               (22U)
/* ID of physical channel23 */
#define DMA_DMA1_PHYCHANNEL23                               (23U)
/* ID of physical channel24 */
#define DMA_DMA1_PHYCHANNEL24                               (24U)
/* ID of physical channel25 */
#define DMA_DMA1_PHYCHANNEL25                               (25U)
/* ID of physical channel26 */
#define DMA_DMA1_PHYCHANNEL26                               (26U)
/* ID of physical channel27 */
#define DMA_DMA1_PHYCHANNEL27                               (27U)
/* ID of physical channel28 */
#define DMA_DMA1_PHYCHANNEL28                               (28U)
/* ID of physical channel29 */
#define DMA_DMA1_PHYCHANNEL29                               (29U)
/* ID of physical channel30 */
#define DMA_DMA1_PHYCHANNEL30                               (30U)
/* ID of physical channel31 */
#define DMA_DMA1_PHYCHANNEL31                               (31U)
/* ID of physical channel32 */
#define DMA_DMA1_PHYCHANNEL32                               (32U)
/* ID of physical channel33 */
#define DMA_DMA1_PHYCHANNEL33                               (33U)
/* ID of physical channel34 */
#define DMA_DMA1_PHYCHANNEL34                               (34U)
/* ID of physical channel35 */
#define DMA_DMA1_PHYCHANNEL35                               (35U)
/* ID of physical channel36 */
#define DMA_DMA1_PHYCHANNEL36                               (36U)
/* ID of physical channel37 */
#define DMA_DMA1_PHYCHANNEL37                               (37U)
/* ID of physical channel38 */
#define DMA_DMA1_PHYCHANNEL38                               (38U)
/* ID of physical channel39 */
#define DMA_DMA1_PHYCHANNEL39                               (39U)
/* ID of physical channel40 */
#define DMA_DMA1_PHYCHANNEL40                               (40U)
/* ID of physical channel41 */
#define DMA_DMA1_PHYCHANNEL41                               (41U)
/* ID of physical channel42 */
#define DMA_DMA1_PHYCHANNEL42                               (42U)
/* ID of physical channel43 */
#define DMA_DMA1_PHYCHANNEL43                               (43U)
/* ID of physical channel44 */
#define DMA_DMA1_PHYCHANNEL44                               (44U)
/* ID of physical channel45 */
#define DMA_DMA1_PHYCHANNEL45                               (45U)
/* ID of physical channel46 */
#define DMA_DMA1_PHYCHANNEL46                               (46U)
/* ID of physical channel47 */
#define DMA_DMA1_PHYCHANNEL47                               (47U)
/* ID of physical channel48 */
#define DMA_DMA1_PHYCHANNEL48                               (48U)
/* ID of physical channel49 */
#define DMA_DMA1_PHYCHANNEL49                               (49U)
/* ID of physical channel50 */
#define DMA_DMA1_PHYCHANNEL50                               (50U)
/* ID of physical channel51 */
#define DMA_DMA1_PHYCHANNEL51                               (51U)
/* ID of physical channel52 */
#define DMA_DMA1_PHYCHANNEL52                               (52U)
/* ID of physical channel53 */
#define DMA_DMA1_PHYCHANNEL53                               (53U)
/* ID of physical channel54 */
#define DMA_DMA1_PHYCHANNEL54                               (54U)
/* ID of physical channel55 */
#define DMA_DMA1_PHYCHANNEL55                               (55U)
/* ID of physical channel56 */
#define DMA_DMA1_PHYCHANNEL56                               (56U)
/* ID of physical channel57 */
#define DMA_DMA1_PHYCHANNEL57                               (57U)
/* ID of physical channel58 */
#define DMA_DMA1_PHYCHANNEL58                               (58U)
/* ID of physical channel59 */
#define DMA_DMA1_PHYCHANNEL59                               (59U)
/* ID of physical channel60 */
#define DMA_DMA1_PHYCHANNEL60                               (60U)
/* ID of physical channel61 */
#define DMA_DMA1_PHYCHANNEL61                               (61U)
/* ID of physical channel62 */
#define DMA_DMA1_PHYCHANNEL62                               (62U)
/* ID of physical channel63 */
#define DMA_DMA1_PHYCHANNEL63                               (63U)

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

/* IDs of physical channel in DMA3 */
/* ID of physical channel0 */
#define DMA_DMA3_PHYCHANNEL0                               (0U)
/* ID of physical channel1 */
#define DMA_DMA3_PHYCHANNEL1                               (1U)
/* ID of physical channel2 */
#define DMA_DMA3_PHYCHANNEL2                               (2U)
/* ID of physical channel3 */
#define DMA_DMA3_PHYCHANNEL3                               (3U)
/* ID of physical channel4 */
#define DMA_DMA3_PHYCHANNEL4                               (4U)
/* ID of physical channel5 */
#define DMA_DMA3_PHYCHANNEL5                               (5U)
/* ID of physical channel6 */
#define DMA_DMA3_PHYCHANNEL6                               (6U)
/* ID of physical channel7 */
#define DMA_DMA3_PHYCHANNEL7                               (7U)
/* ID of physical channel8 */
#define DMA_DMA3_PHYCHANNEL8                               (8U)
/* ID of physical channel9 */
#define DMA_DMA3_PHYCHANNEL9                               (9U)
/* ID of physical channel10 */
#define DMA_DMA3_PHYCHANNEL10                               (10U)
/* ID of physical channel11 */
#define DMA_DMA3_PHYCHANNEL11                               (11U)
/* ID of physical channel12 */
#define DMA_DMA3_PHYCHANNEL12                               (12U)
/* ID of physical channel13 */
#define DMA_DMA3_PHYCHANNEL13                               (13U)
/* ID of physical channel14 */
#define DMA_DMA3_PHYCHANNEL14                               (14U)
/* ID of physical channel15 */
#define DMA_DMA3_PHYCHANNEL15                               (15U)
/* ID of physical channel16 */
#define DMA_DMA3_PHYCHANNEL16                               (16U)
/* ID of physical channel17 */
#define DMA_DMA3_PHYCHANNEL17                               (17U)
/* ID of physical channel18 */
#define DMA_DMA3_PHYCHANNEL18                               (18U)
/* ID of physical channel19 */
#define DMA_DMA3_PHYCHANNEL19                               (19U)
/* ID of physical channel20 */
#define DMA_DMA3_PHYCHANNEL20                               (20U)
/* ID of physical channel21 */
#define DMA_DMA3_PHYCHANNEL21                               (21U)
/* ID of physical channel22 */
#define DMA_DMA3_PHYCHANNEL22                               (22U)
/* ID of physical channel23 */
#define DMA_DMA3_PHYCHANNEL23                               (23U)


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
/* Channel ID4(M2M_LinkedList): Physical channel4 in DMA0 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL4_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL4_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL4_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL4_ERROR_INT_EN                 (STD_OFF)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL4_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL4_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA0_CHANNEL4_PATTERN_INT_EN               (STD_OFF)

/* Channel ID5(M2M_Shadow): Physical channel0 in DMA1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL0_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL0_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL0_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL0_ERROR_INT_EN                 (STD_OFF)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL0_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL0_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL0_PATTERN_INT_EN               (STD_OFF)

/* Channel ID6(M2M_Pattern): Physical channel0 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL0_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL0_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL0_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL0_ERROR_INT_EN                 (STD_ON)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL0_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL0_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL0_PATTERN_INT_EN               (STD_ON)

/* Channel ID7(M2M_Daisy0): Physical channel0 in DMA3 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA3_CHANNEL0_INT_EN                       (STD_OFF)
/* Channel ID8(M2M_Daisy1): Physical channel1 in DMA3 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA3_CHANNEL1_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA3_CHANNEL1_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA3_CHANNEL1_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA3_CHANNEL1_ERROR_INT_EN                 (STD_OFF)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA3_CHANNEL1_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA3_CHANNEL1_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA3_CHANNEL1_PATTERN_INT_EN               (STD_OFF)

/* Channel ID9(ADC1_Channel0): Physical channel2 in DMA1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL2_INT_EN                       (STD_OFF)
/* Channel ID10(ADC1_Channel1): Physical channel3 in DMA1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL3_INT_EN                       (STD_OFF)
/* Channel ID11(ADC1_Channel2): Physical channel4 in DMA1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL4_INT_EN                       (STD_OFF)
/* Channel ID12(ADC1_Channel3): Physical channel5 in DMA1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL5_INT_EN                       (STD_OFF)
/* Channel ID13(ADC1_Channel7): Physical channel6 in DMA1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL6_INT_EN                       (STD_OFF)
/* Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL7_INT_EN                       (STD_OFF)
/* Channel ID15(SPITx): Physical channel2 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL2_INT_EN                       (STD_OFF)
/* Channel ID16(SPIRx): Physical channel3 in DMA2 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL3_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL3_TC_INT_EN                    (STD_ON)
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL3_RTC_INT_EN                   (STD_OFF)
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL3_ERROR_INT_EN                 (STD_OFF)
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL3_SRC_CB_INT_EN                (STD_OFF)
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL3_DEST_CB_INT_EN               (STD_OFF)
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA2_CHANNEL3_PATTERN_INT_EN               (STD_OFF)

/* Channel ID17(Dsadc3): Physical channel8 in DMA1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL8_INT_EN                       (STD_OFF)
/* Channel ID18(ADC1_AllChToOneResReg): Physical channel9 in DMA1 */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DMA1_CHANNEL9_INT_EN                       (STD_OFF)

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
/* DMA0 local request: "REQUEST8_QSPI" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST8_QSPI                  (8U)
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
/* DMA0 local request: "REQUEST25_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST25_GLOBAL_REQUEST                  (25U)
/* DMA0 local request: "REQUEST26_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST26_GLOBAL_REQUEST                  (26U)
/* DMA0 local request: "REQUEST27_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST27_GLOBAL_REQUEST                  (27U)
/* DMA0 local request: "REQUEST28_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST28_GLOBAL_REQUEST                  (28U)
/* DMA0 local request: "REQUEST29_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST29_GLOBAL_REQUEST                  (29U)
/* DMA0 local request: "REQUEST30_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST30_GLOBAL_REQUEST                  (30U)
/* DMA0 local request: "REQUEST31_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST31_GLOBAL_REQUEST                  (31U)
/* DMA0 local request: "REQUEST32_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST32_GLOBAL_REQUEST                  (32U)
/* DMA0 local request: "REQUEST33_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST33_GLOBAL_REQUEST                  (33U)
/* DMA0 local request: "REQUEST34_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST34_GLOBAL_REQUEST                  (34U)
/* DMA0 local request: "REQUEST35_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST35_GLOBAL_REQUEST                  (35U)
/* DMA0 local request: "REQUEST36_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST36_GLOBAL_REQUEST                  (36U)
/* DMA0 local request: "REQUEST37_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST37_GLOBAL_REQUEST                  (37U)
/* DMA0 local request: "REQUEST38_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST38_GLOBAL_REQUEST                  (38U)
/* DMA0 local request: "REQUEST39_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST39_GLOBAL_REQUEST                  (39U)
/* DMA0 local request: "REQUEST40_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA0_REQUEST40_GLOBAL_REQUEST                  (40U)

/* DMA1 local request: "REQUEST0_DSADC0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST0_DSADC0                  (0U)
/* DMA1 local request: "REQUEST1_DSADC1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST1_DSADC1                  (1U)
/* DMA1 local request: "REQUEST2_DSADC2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST2_DSADC2                  (2U)
/* DMA1 local request: "REQUEST3_DSADC3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST3_DSADC3                  (3U)
/* DMA1 local request: "REQUEST4_FC0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST4_FC0                  (4U)
/* DMA1 local request: "REQUEST5_FC1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST5_FC1                  (5U)
/* DMA1 local request: "REQUEST6_SARADC0_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST6_SARADC0_RESULT0                  (6U)
/* DMA1 local request: "REQUEST7_SARADC0_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST7_SARADC0_RESULT1                  (7U)
/* DMA1 local request: "REQUEST8_SARADC0_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST8_SARADC0_RESULT2                  (8U)
/* DMA1 local request: "REQUEST9_SARADC0_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST9_SARADC0_RESULT3                  (9U)
/* DMA1 local request: "REQUEST10_SARADC0_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST10_SARADC0_RESULT4                  (10U)
/* DMA1 local request: "REQUEST11_SARADC0_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST11_SARADC0_RESULT5                  (11U)
/* DMA1 local request: "REQUEST12_SARADC0_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST12_SARADC0_RESULT6                  (12U)
/* DMA1 local request: "REQUEST13_SARADC0_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST13_SARADC0_RESULT7                  (13U)
/* DMA1 local request: "REQUEST14_SARADC0_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST14_SARADC0_RESULT8                  (14U)
/* DMA1 local request: "REQUEST15_SARADC0_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST15_SARADC0_RESULT9                  (15U)
/* DMA1 local request: "REQUEST16_SARADC0_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST16_SARADC0_RESULT10                  (16U)
/* DMA1 local request: "REQUEST17_SARADC0_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST17_SARADC0_RESULT11                  (17U)
/* DMA1 local request: "REQUEST18_SARADC0_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST18_SARADC0_RESULT12                  (18U)
/* DMA1 local request: "REQUEST19_SARADC0_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST19_SARADC0_RESULT13                  (19U)
/* DMA1 local request: "REQUEST20_SARADC0_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST20_SARADC0_RESULT14                  (20U)
/* DMA1 local request: "REQUEST21_SARADC0_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST21_SARADC0_RESULT15                  (21U)
/* DMA1 local request: "REQUEST22_SARADC_GLOBAL_RESULT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST22_SARADC_GLOBAL_RESULT                  (22U)
/* DMA1 local request: "REQUEST23_SARADC1_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST23_SARADC1_RESULT0                  (23U)
/* DMA1 local request: "REQUEST24_SARADC1_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST24_SARADC1_RESULT1                  (24U)
/* DMA1 local request: "REQUEST25_SARADC1_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST25_SARADC1_RESULT2                  (25U)
/* DMA1 local request: "REQUEST26_SARADC1_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST26_SARADC1_RESULT3                  (26U)
/* DMA1 local request: "REQUEST27_SARADC1_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST27_SARADC1_RESULT4                  (27U)
/* DMA1 local request: "REQUEST28_SARADC1_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST28_SARADC1_RESULT5                  (28U)
/* DMA1 local request: "REQUEST29_SARADC1_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST29_SARADC1_RESULT6                  (29U)
/* DMA1 local request: "REQUEST30_SARADC1_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST30_SARADC1_RESULT7                  (30U)
/* DMA1 local request: "REQUEST31_SARADC1_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST31_SARADC1_RESULT8                  (31U)
/* DMA1 local request: "REQUEST32_SARADC1_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST32_SARADC1_RESULT9                  (32U)
/* DMA1 local request: "REQUEST33_SARADC1_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST33_SARADC1_RESULT10                  (33U)
/* DMA1 local request: "REQUEST34_SARADC1_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST34_SARADC1_RESULT11                  (34U)
/* DMA1 local request: "REQUEST35_SARADC1_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST35_SARADC1_RESULT12                  (35U)
/* DMA1 local request: "REQUEST36_SARADC1_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST36_SARADC1_RESULT13                  (36U)
/* DMA1 local request: "REQUEST37_SARADC1_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST37_SARADC1_RESULT14                  (37U)
/* DMA1 local request: "REQUEST38_SARADC1_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST38_SARADC1_RESULT15                  (38U)
/* DMA1 local request: "REQUEST39_SARADC2_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST39_SARADC2_RESULT0                  (39U)
/* DMA1 local request: "REQUEST40_SARADC2_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST40_SARADC2_RESULT1                  (40U)
/* DMA1 local request: "REQUEST41_SARADC2_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST41_SARADC2_RESULT2                  (41U)
/* DMA1 local request: "REQUEST42_SARADC2_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST42_SARADC2_RESULT3                  (42U)
/* DMA1 local request: "REQUEST43_SARADC2_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST43_SARADC2_RESULT4                  (43U)
/* DMA1 local request: "REQUEST44_SARADC2_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST44_SARADC2_RESULT5                  (44U)
/* DMA1 local request: "REQUEST45_SARADC2_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST45_SARADC2_RESULT6                  (45U)
/* DMA1 local request: "REQUEST46_SARADC2_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST46_SARADC2_RESULT7                  (46U)
/* DMA1 local request: "REQUEST47_SARADC2_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST47_SARADC2_RESULT8                  (47U)
/* DMA1 local request: "REQUEST48_SARADC2_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST48_SARADC2_RESULT9                  (48U)
/* DMA1 local request: "REQUEST49_SARADC2_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST49_SARADC2_RESULT10                  (49U)
/* DMA1 local request: "REQUEST50_SARADC2_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST50_SARADC2_RESULT11                  (50U)
/* DMA1 local request: "REQUEST51_SARADC2_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST51_SARADC2_RESULT12                  (51U)
/* DMA1 local request: "REQUEST52_SARADC2_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST52_SARADC2_RESULT13                  (52U)
/* DMA1 local request: "REQUEST53_SARADC2_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST53_SARADC2_RESULT14                  (53U)
/* DMA1 local request: "REQUEST54_SARADC2_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST54_SARADC2_RESULT15                  (54U)
/* DMA1 local request: "REQUEST55_SARADC3_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST55_SARADC3_RESULT0                  (55U)
/* DMA1 local request: "REQUEST56_SARADC3_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST56_SARADC3_RESULT1                  (56U)
/* DMA1 local request: "REQUEST57_SARADC3_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST57_SARADC3_RESULT2                  (57U)
/* DMA1 local request: "REQUEST58_SARADC3_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST58_SARADC3_RESULT3                  (58U)
/* DMA1 local request: "REQUEST59_SARADC3_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST59_SARADC3_RESULT4                  (59U)
/* DMA1 local request: "REQUEST60_SARADC3_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST60_SARADC3_RESULT5                  (60U)
/* DMA1 local request: "REQUEST61_SARADC3_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST61_SARADC3_RESULT6                  (61U)
/* DMA1 local request: "REQUEST62_SARADC3_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST62_SARADC3_RESULT7                  (62U)
/* DMA1 local request: "REQUEST63_SARADC3_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST63_SARADC3_RESULT8                  (63U)
/* DMA1 local request: "REQUEST64_SARADC3_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST64_SARADC3_RESULT9                  (64U)
/* DMA1 local request: "REQUEST65_SARADC3_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST65_SARADC3_RESULT10                  (65U)
/* DMA1 local request: "REQUEST66_SARADC3_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST66_SARADC3_RESULT11                  (66U)
/* DMA1 local request: "REQUEST67_SARADC3_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST67_SARADC3_RESULT12                  (67U)
/* DMA1 local request: "REQUEST68_SARADC3_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST68_SARADC3_RESULT13                  (68U)
/* DMA1 local request: "REQUEST69_SARADC3_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST69_SARADC3_RESULT14                  (69U)
/* DMA1 local request: "REQUEST70_SARADC3_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST70_SARADC3_RESULT15                  (70U)
/* DMA1 local request: "REQUEST71_SARADC8_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST71_SARADC8_RESULT0                  (71U)
/* DMA1 local request: "REQUEST72_SARADC8_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST72_SARADC8_RESULT1                  (72U)
/* DMA1 local request: "REQUEST73_SARADC8_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST73_SARADC8_RESULT2                  (73U)
/* DMA1 local request: "REQUEST74_SARADC8_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST74_SARADC8_RESULT3                  (74U)
/* DMA1 local request: "REQUEST75_SARADC8_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST75_SARADC8_RESULT4                  (75U)
/* DMA1 local request: "REQUEST76_SARADC8_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST76_SARADC8_RESULT5                  (76U)
/* DMA1 local request: "REQUEST77_SARADC8_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST77_SARADC8_RESULT6                  (77U)
/* DMA1 local request: "REQUEST78_SARADC8_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST78_SARADC8_RESULT7                  (78U)
/* DMA1 local request: "REQUEST79_SARADC8_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST79_SARADC8_RESULT8                  (79U)
/* DMA1 local request: "REQUEST80_SARADC8_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST80_SARADC8_RESULT9                  (80U)
/* DMA1 local request: "REQUEST81_SARADC8_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST81_SARADC8_RESULT10                  (81U)
/* DMA1 local request: "REQUEST82_SARADC8_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST82_SARADC8_RESULT11                  (82U)
/* DMA1 local request: "REQUEST83_SARADC8_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST83_SARADC8_RESULT12                  (83U)
/* DMA1 local request: "REQUEST84_SARADC8_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST84_SARADC8_RESULT13                  (84U)
/* DMA1 local request: "REQUEST85_SARADC8_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST85_SARADC8_RESULT14                  (85U)
/* DMA1 local request: "REQUEST86_SARADC8_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST86_SARADC8_RESULT15                  (86U)
/* DMA1 local request: "REQUEST87_SARADC9_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST87_SARADC9_RESULT0                  (87U)
/* DMA1 local request: "REQUEST88_SARADC9_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST88_SARADC9_RESULT1                  (88U)
/* DMA1 local request: "REQUEST89_SARADC9_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST89_SARADC9_RESULT2                  (89U)
/* DMA1 local request: "REQUEST90_SARADC9_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST90_SARADC9_RESULT3                  (90U)
/* DMA1 local request: "REQUEST91_SARADC9_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST91_SARADC9_RESULT4                  (91U)
/* DMA1 local request: "REQUEST92_SARADC9_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST92_SARADC9_RESULT5                  (92U)
/* DMA1 local request: "REQUEST93_SARADC9_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST93_SARADC9_RESULT6                  (93U)
/* DMA1 local request: "REQUEST94_SARADC9_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST94_SARADC9_RESULT7                  (94U)
/* DMA1 local request: "REQUEST95_SARADC9_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST95_SARADC9_RESULT8                  (95U)
/* DMA1 local request: "REQUEST96_SARADC9_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST96_SARADC9_RESULT9                  (96U)
/* DMA1 local request: "REQUEST97_SARADC9_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST97_SARADC9_RESULT10                  (97U)
/* DMA1 local request: "REQUEST98_SARADC9_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST98_SARADC9_RESULT11                  (98U)
/* DMA1 local request: "REQUEST99_SARADC9_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST99_SARADC9_RESULT12                  (99U)
/* DMA1 local request: "REQUEST100_SARADC9_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST100_SARADC9_RESULT13                  (100U)
/* DMA1 local request: "REQUEST101_SARADC9_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST101_SARADC9_RESULT14                  (101U)
/* DMA1 local request: "REQUEST102_SARADC9_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST102_SARADC9_RESULT15                  (102U)
/* DMA1 local request: "REQUEST103_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST103_GLOBAL_REQUEST                  (103U)
/* DMA1 local request: "REQUEST104_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST104_GLOBAL_REQUEST                  (104U)
/* DMA1 local request: "REQUEST105_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST105_GLOBAL_REQUEST                  (105U)
/* DMA1 local request: "REQUEST106_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST106_GLOBAL_REQUEST                  (106U)
/* DMA1 local request: "REQUEST107_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST107_GLOBAL_REQUEST                  (107U)
/* DMA1 local request: "REQUEST108_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST108_GLOBAL_REQUEST                  (108U)
/* DMA1 local request: "REQUEST109_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST109_GLOBAL_REQUEST                  (109U)
/* DMA1 local request: "REQUEST110_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST110_GLOBAL_REQUEST                  (110U)
/* DMA1 local request: "REQUEST111_SARADC4_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST111_SARADC4_RESULT0                  (111U)
/* DMA1 local request: "REQUEST112_SARADC4_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST112_SARADC4_RESULT1                  (112U)
/* DMA1 local request: "REQUEST113_SARADC4_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST113_SARADC4_RESULT2                  (113U)
/* DMA1 local request: "REQUEST114_SARADC4_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST114_SARADC4_RESULT3                  (114U)
/* DMA1 local request: "REQUEST115_SARADC4_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST115_SARADC4_RESULT4                  (115U)
/* DMA1 local request: "REQUEST116_SARADC4_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST116_SARADC4_RESULT5                  (116U)
/* DMA1 local request: "REQUEST117_SARADC4_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST117_SARADC4_RESULT6                  (117U)
/* DMA1 local request: "REQUEST118_SARADC4_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST118_SARADC4_RESULT7                  (118U)
/* DMA1 local request: "REQUEST119_SARADC4_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST119_SARADC4_RESULT8                  (119U)
/* DMA1 local request: "REQUEST120_SARADC4_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST120_SARADC4_RESULT9                  (120U)
/* DMA1 local request: "REQUEST121_SARADC4_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST121_SARADC4_RESULT10                  (121U)
/* DMA1 local request: "REQUEST122_SARADC4_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST122_SARADC4_RESULT11                  (122U)
/* DMA1 local request: "REQUEST123_SARADC4_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST123_SARADC4_RESULT12                  (123U)
/* DMA1 local request: "REQUEST124_SARADC4_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST124_SARADC4_RESULT13                  (124U)
/* DMA1 local request: "REQUEST125_SARADC4_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST125_SARADC4_RESULT14                  (125U)
/* DMA1 local request: "REQUEST126_SARADC4_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST126_SARADC4_RESULT15                  (126U)
/* DMA1 local request: "REQUEST127_SARADC5_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST127_SARADC5_RESULT0                  (127U)
/* DMA1 local request: "REQUEST128_SARADC5_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST128_SARADC5_RESULT1                  (128U)
/* DMA1 local request: "REQUEST129_SARADC5_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST129_SARADC5_RESULT2                  (129U)
/* DMA1 local request: "REQUEST130_SARADC5_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST130_SARADC5_RESULT3                  (130U)
/* DMA1 local request: "REQUEST131_SARADC5_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST131_SARADC5_RESULT4                  (131U)
/* DMA1 local request: "REQUEST132_SARADC5_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST132_SARADC5_RESULT5                  (132U)
/* DMA1 local request: "REQUEST133_SARADC5_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST133_SARADC5_RESULT6                  (133U)
/* DMA1 local request: "REQUEST134_SARADC5_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST134_SARADC5_RESULT7                  (134U)
/* DMA1 local request: "REQUEST135_SARADC5_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST135_SARADC5_RESULT8                  (135U)
/* DMA1 local request: "REQUEST136_SARADC5_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST136_SARADC5_RESULT9                  (136U)
/* DMA1 local request: "REQUEST137_SARADC5_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST137_SARADC5_RESULT10                  (137U)
/* DMA1 local request: "REQUEST138_SARADC5_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST138_SARADC5_RESULT11                  (138U)
/* DMA1 local request: "REQUEST139_SARADC5_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST139_SARADC5_RESULT12                  (139U)
/* DMA1 local request: "REQUEST140_SARADC5_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST140_SARADC5_RESULT13                  (140U)
/* DMA1 local request: "REQUEST141_SARADC5_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST141_SARADC5_RESULT14                  (141U)
/* DMA1 local request: "REQUEST142_SARADC5_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST142_SARADC5_RESULT15                  (142U)
/* DMA1 local request: "REQUEST143_SARADC6_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST143_SARADC6_RESULT0                  (143U)
/* DMA1 local request: "REQUEST144_SARADC6_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST144_SARADC6_RESULT1                  (144U)
/* DMA1 local request: "REQUEST145_SARADC6_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST145_SARADC6_RESULT2                  (145U)
/* DMA1 local request: "REQUEST146_SARADC6_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST146_SARADC6_RESULT3                  (146U)
/* DMA1 local request: "REQUEST147_SARADC6_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST147_SARADC6_RESULT4                  (147U)
/* DMA1 local request: "REQUEST148_SARADC6_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST148_SARADC6_RESULT5                  (148U)
/* DMA1 local request: "REQUEST149_SARADC6_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST149_SARADC6_RESULT6                  (149U)
/* DMA1 local request: "REQUEST150_SARADC6_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST150_SARADC6_RESULT7                  (150U)
/* DMA1 local request: "REQUEST151_SARADC6_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST151_SARADC6_RESULT8                  (151U)
/* DMA1 local request: "REQUEST152_SARADC6_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST152_SARADC6_RESULT9                  (152U)
/* DMA1 local request: "REQUEST153_SARADC6_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST153_SARADC6_RESULT10                  (153U)
/* DMA1 local request: "REQUEST154_SARADC6_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST154_SARADC6_RESULT11                  (154U)
/* DMA1 local request: "REQUEST155_SARADC6_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST155_SARADC6_RESULT12                  (155U)
/* DMA1 local request: "REQUEST156_SARADC6_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST156_SARADC6_RESULT13                  (156U)
/* DMA1 local request: "REQUEST157_SARADC6_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST157_SARADC6_RESULT14                  (157U)
/* DMA1 local request: "REQUEST158_SARADC6_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST158_SARADC6_RESULT15                  (158U)
/* DMA1 local request: "REQUEST159_SARADC7_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST159_SARADC7_RESULT0                  (159U)
/* DMA1 local request: "REQUEST160_SARADC7_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST160_SARADC7_RESULT1                  (160U)
/* DMA1 local request: "REQUEST161_SARADC7_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST161_SARADC7_RESULT2                  (161U)
/* DMA1 local request: "REQUEST162_SARADC7_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST162_SARADC7_RESULT3                  (162U)
/* DMA1 local request: "REQUEST163_SARADC7_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST163_SARADC7_RESULT4                  (163U)
/* DMA1 local request: "REQUEST164_SARADC7_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST164_SARADC7_RESULT5                  (164U)
/* DMA1 local request: "REQUEST165_SARADC7_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST165_SARADC7_RESULT6                  (165U)
/* DMA1 local request: "REQUEST166_SARADC7_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST166_SARADC7_RESULT7                  (166U)
/* DMA1 local request: "REQUEST167_SARADC7_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST167_SARADC7_RESULT8                  (167U)
/* DMA1 local request: "REQUEST168_SARADC7_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST168_SARADC7_RESULT9                  (168U)
/* DMA1 local request: "REQUEST169_SARADC7_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST169_SARADC7_RESULT10                  (169U)
/* DMA1 local request: "REQUEST170_SARADC7_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST170_SARADC7_RESULT11                  (170U)
/* DMA1 local request: "REQUEST171_SARADC7_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST171_SARADC7_RESULT12                  (171U)
/* DMA1 local request: "REQUEST172_SARADC7_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST172_SARADC7_RESULT13                  (172U)
/* DMA1 local request: "REQUEST173_SARADC7_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST173_SARADC7_RESULT14                  (173U)
/* DMA1 local request: "REQUEST174_SARADC7_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST174_SARADC7_RESULT15                  (174U)
/* DMA1 local request: "REQUEST175_SARADC10_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST175_SARADC10_RESULT0                  (175U)
/* DMA1 local request: "REQUEST176_SARADC10_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST176_SARADC10_RESULT1                  (176U)
/* DMA1 local request: "REQUEST177_SARADC10_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST177_SARADC10_RESULT2                  (177U)
/* DMA1 local request: "REQUEST178_SARADC10_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST178_SARADC10_RESULT3                  (178U)
/* DMA1 local request: "REQUEST179_SARADC10_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST179_SARADC10_RESULT4                  (179U)
/* DMA1 local request: "REQUEST180_SARADC10_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST180_SARADC10_RESULT5                  (180U)
/* DMA1 local request: "REQUEST181_SARADC10_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST181_SARADC10_RESULT6                  (181U)
/* DMA1 local request: "REQUEST182_SARADC10_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST182_SARADC10_RESULT7                  (182U)
/* DMA1 local request: "REQUEST183_SARADC10_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST183_SARADC10_RESULT8                  (183U)
/* DMA1 local request: "REQUEST184_SARADC10_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST184_SARADC10_RESULT9                  (184U)
/* DMA1 local request: "REQUEST185_SARADC10_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST185_SARADC10_RESULT10                  (185U)
/* DMA1 local request: "REQUEST186_SARADC10_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST186_SARADC10_RESULT11                  (186U)
/* DMA1 local request: "REQUEST187_SARADC10_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST187_SARADC10_RESULT12                  (187U)
/* DMA1 local request: "REQUEST188_SARADC10_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST188_SARADC10_RESULT13                  (188U)
/* DMA1 local request: "REQUEST189_SARADC10_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST189_SARADC10_RESULT14                  (189U)
/* DMA1 local request: "REQUEST190_SARADC10_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST190_SARADC10_RESULT15                  (190U)
/* DMA1 local request: "REQUEST191_SARADC11_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST191_SARADC11_RESULT0                  (191U)
/* DMA1 local request: "REQUEST192_SARADC11_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST192_SARADC11_RESULT1                  (192U)
/* DMA1 local request: "REQUEST193_SARADC11_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST193_SARADC11_RESULT2                  (193U)
/* DMA1 local request: "REQUEST194_SARADC11_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST194_SARADC11_RESULT3                  (194U)
/* DMA1 local request: "REQUEST195_SARADC11_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST195_SARADC11_RESULT4                  (195U)
/* DMA1 local request: "REQUEST196_SARADC11_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST196_SARADC11_RESULT5                  (196U)
/* DMA1 local request: "REQUEST197_SARADC11_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST197_SARADC11_RESULT6                  (197U)
/* DMA1 local request: "REQUEST198_SARADC11_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST198_SARADC11_RESULT7                  (198U)
/* DMA1 local request: "REQUEST199_SARADC11_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST199_SARADC11_RESULT8                  (199U)
/* DMA1 local request: "REQUEST200_SARADC11_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST200_SARADC11_RESULT9                  (200U)
/* DMA1 local request: "REQUEST201_SARADC11_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST201_SARADC11_RESULT10                  (201U)
/* DMA1 local request: "REQUEST202_SARADC11_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST202_SARADC11_RESULT11                  (202U)
/* DMA1 local request: "REQUEST203_SARADC11_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST203_SARADC11_RESULT12                  (203U)
/* DMA1 local request: "REQUEST204_SARADC11_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST204_SARADC11_RESULT13                  (204U)
/* DMA1 local request: "REQUEST205_SARADC11_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST205_SARADC11_RESULT14                  (205U)
/* DMA1 local request: "REQUEST206_SARADC11_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST206_SARADC11_RESULT15                  (206U)
/* DMA1 local request: "REQUEST207_PSI5_CH0_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST207_PSI5_CH0_DATA_TX                  (207U)
/* DMA1 local request: "REQUEST208_PSI5_CH0_CTRL_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST208_PSI5_CH0_CTRL_TX                  (208U)
/* DMA1 local request: "REQUEST209_PSI5_CH0_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST209_PSI5_CH0_DATA_RX                  (209U)
/* DMA1 local request: "REQUEST210_PSI5_CH0_CTRL_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST210_PSI5_CH0_CTRL_RX                  (210U)
/* DMA1 local request: "REQUEST211_PSI5_CH1_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST211_PSI5_CH1_DATA_TX                  (211U)
/* DMA1 local request: "REQUEST212_PSI5_CH1_CTRL_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST212_PSI5_CH1_CTRL_TX                  (212U)
/* DMA1 local request: "REQUEST213_PSI5_CH1_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST213_PSI5_CH1_DATA_RX                  (213U)
/* DMA1 local request: "REQUEST214_PSI5_CH1_CTRL_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST214_PSI5_CH1_CTRL_RX                  (214U)
/* DMA1 local request: "REQUEST215_PSI5_CH2_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST215_PSI5_CH2_DATA_TX                  (215U)
/* DMA1 local request: "REQUEST216_PSI5_CH2_CTRL_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST216_PSI5_CH2_CTRL_TX                  (216U)
/* DMA1 local request: "REQUEST217_PSI5_CH2_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST217_PSI5_CH2_DATA_RX                  (217U)
/* DMA1 local request: "REQUEST218_PSI5_CH2_CTRL_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST218_PSI5_CH2_CTRL_RX                  (218U)
/* DMA1 local request: "REQUEST219_PSI5_CH3_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST219_PSI5_CH3_DATA_TX                  (219U)
/* DMA1 local request: "REQUEST220_PSI5_CH3_CTRL_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST220_PSI5_CH3_CTRL_TX                  (220U)
/* DMA1 local request: "REQUEST221_PSI5_CH3_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST221_PSI5_CH3_DATA_RX                  (221U)
/* DMA1 local request: "REQUEST222_PSI5_CH3_CTRL_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST222_PSI5_CH3_CTRL_RX                  (222U)
/* DMA1 local request: "REQUEST223_DSADC4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST223_DSADC4                  (223U)
/* DMA1 local request: "REQUEST224_DSADC5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST224_DSADC5                  (224U)
/* DMA1 local request: "REQUEST225_DSADC6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST225_DSADC6                  (225U)
/* DMA1 local request: "REQUEST226_DSADC7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST226_DSADC7                  (226U)
/* DMA1 local request: "REQUEST227_DSADC8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST227_DSADC8                  (227U)
/* DMA1 local request: "REQUEST228_DSADC9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST228_DSADC9                  (228U)
/* DMA1 local request: "REQUEST229_FC2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST229_FC2                  (229U)
/* DMA1 local request: "REQUEST230_FC3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA1_REQUEST230_FC3                  (230U)

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
/* DMA2 local request: "REQUEST8_ESPI6_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST8_ESPI6_TX                  (8U)
/* DMA2 local request: "REQUEST9_ESPI6_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST9_ESPI6_RX                  (9U)
/* DMA2 local request: "REQUEST10_ESPI7_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST10_ESPI7_TX                  (10U)
/* DMA2 local request: "REQUEST11_ESPI7_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST11_ESPI7_RX                  (11U)
/* DMA2 local request: "REQUEST12_ESPI8_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST12_ESPI8_TX                  (12U)
/* DMA2 local request: "REQUEST13_ESPI8_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST13_ESPI8_RX                  (13U)
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
/* DMA2 local request: "REQUEST30_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST30_GLOBAL_REQUEST                  (30U)
/* DMA2 local request: "REQUEST31_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST31_GLOBAL_REQUEST                  (31U)
/* DMA2 local request: "REQUEST32_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST32_GLOBAL_REQUEST                  (32U)
/* DMA2 local request: "REQUEST33_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST33_GLOBAL_REQUEST                  (33U)
/* DMA2 local request: "REQUEST34_CAN22_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST34_CAN22_TX_FIFO                  (34U)
/* DMA2 local request: "REQUEST35_CAN22_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST35_CAN22_RX_FIFO0                  (35U)
/* DMA2 local request: "REQUEST36_CAN22_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST36_CAN22_RX_FIFO1                  (36U)
/* DMA2 local request: "REQUEST37_CAN22_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST37_CAN22_TX_EVENT                  (37U)
/* DMA2 local request: "REQUEST38_MSC1_DOWNSTREAM_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST38_MSC1_DOWNSTREAM_DATA_TX                  (38U)
/* DMA2 local request: "REQUEST39_MSC1_DOWNSTREAM_CMD_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST39_MSC1_DOWNSTREAM_CMD_TX                  (39U)
/* DMA2 local request: "REQUEST40_MSC1_DOWNSTREAM_PT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST40_MSC1_DOWNSTREAM_PT                  (40U)
/* DMA2 local request: "REQUEST41_MSC1_UPSTREAM_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST41_MSC1_UPSTREAM_DATA_RX                  (41U)
/* DMA2 local request: "REQUEST42_MSC2_DOWNSTREAM_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST42_MSC2_DOWNSTREAM_DATA_TX                  (42U)
/* DMA2 local request: "REQUEST43_MSC2_DOWNSTREAM_CMD_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST43_MSC2_DOWNSTREAM_CMD_TX                  (43U)
/* DMA2 local request: "REQUEST44_MSC2_DOWNSTREAM_PT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST44_MSC2_DOWNSTREAM_PT                  (44U)
/* DMA2 local request: "REQUEST45_MSC2_UPSTREAM_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST45_MSC2_UPSTREAM_DATA_RX                  (45U)
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
/* DMA2 local request: "REQUEST54_CAN20_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST54_CAN20_TX_FIFO                  (54U)
/* DMA2 local request: "REQUEST55_CAN20_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST55_CAN20_RX_FIFO0                  (55U)
/* DMA2 local request: "REQUEST56_CAN20_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST56_CAN20_RX_FIFO1                  (56U)
/* DMA2 local request: "REQUEST57_CAN20_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST57_CAN20_TX_EVENT                  (57U)
/* DMA2 local request: "REQUEST58_CAN21_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST58_CAN21_TX_FIFO                  (58U)
/* DMA2 local request: "REQUEST59_CAN21_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST59_CAN21_RX_FIFO0                  (59U)
/* DMA2 local request: "REQUEST60_CAN21_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST60_CAN21_RX_FIFO1                  (60U)
/* DMA2 local request: "REQUEST61_CAN21_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA2_REQUEST61_CAN21_TX_EVENT                  (61U)

/* DMA3 local request: "REQUEST0_ASI0_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST0_ASI0_LIN_UART_TX                  (0U)
/* DMA3 local request: "REQUEST1_ASI0_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST1_ASI0_LIN_UART_RX                  (1U)
/* DMA3 local request: "REQUEST2_ASI1_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST2_ASI1_LIN_UART_TX                  (2U)
/* DMA3 local request: "REQUEST3_ASI1_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST3_ASI1_LIN_UART_RX                  (3U)
/* DMA3 local request: "REQUEST4_ASI2_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST4_ASI2_LIN_UART_TX                  (4U)
/* DMA3 local request: "REQUEST5_ASI2_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST5_ASI2_LIN_UART_RX                  (5U)
/* DMA3 local request: "REQUEST6_ASI3_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST6_ASI3_LIN_UART_TX                  (6U)
/* DMA3 local request: "REQUEST7_ASI3_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST7_ASI3_LIN_UART_RX                  (7U)
/* DMA3 local request: "REQUEST8_ASI4_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST8_ASI4_LIN_UART_TX                  (8U)
/* DMA3 local request: "REQUEST9_ASI4_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST9_ASI4_LIN_UART_RX                  (9U)
/* DMA3 local request: "REQUEST10_ASI5_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST10_ASI5_LIN_UART_TX                  (10U)
/* DMA3 local request: "REQUEST11_ASI5_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST11_ASI5_LIN_UART_RX                  (11U)
/* DMA3 local request: "REQUEST12_ASI6_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST12_ASI6_LIN_UART_TX                  (12U)
/* DMA3 local request: "REQUEST13_ASI6_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST13_ASI6_LIN_UART_RX                  (13U)
/* DMA3 local request: "REQUEST14_ASI7_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST14_ASI7_LIN_UART_TX                  (14U)
/* DMA3 local request: "REQUEST15_ASI7_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST15_ASI7_LIN_UART_RX                  (15U)
/* DMA3 local request: "REQUEST16_ESPI3_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST16_ESPI3_TX                  (16U)
/* DMA3 local request: "REQUEST17_ESPI3_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST17_ESPI3_RX                  (17U)
/* DMA3 local request: "REQUEST18_ESPI4_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST18_ESPI4_TX                  (18U)
/* DMA3 local request: "REQUEST19_ESPI4_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST19_ESPI4_RX                  (19U)
/* DMA3 local request: "REQUEST20_I2C0_TX_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST20_I2C0_TX_RX                  (20U)
/* DMA3 local request: "REQUEST21_MSC0_DOWNSTREAM_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST21_MSC0_DOWNSTREAM_DATA_TX                  (21U)
/* DMA3 local request: "REQUEST22_MSC0_DOWNSTREAM_CMD_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST22_MSC0_DOWNSTREAM_CMD_TX                  (22U)
/* DMA3 local request: "REQUEST23_MSC0_DOWNSTREAM_PT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST23_MSC0_DOWNSTREAM_PT                  (23U)
/* DMA3 local request: "REQUEST24_MSC0_UPSTREAM_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST24_MSC0_UPSTREAM_DATA_RX                  (24U)
/* DMA3 local request: "REQUEST25_CAN10_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST25_CAN10_TX_FIFO                  (25U)
/* DMA3 local request: "REQUEST26_CAN10_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST26_CAN10_RX_FIFO0                  (26U)
/* DMA3 local request: "REQUEST27_CAN10_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST27_CAN10_RX_FIFO1                  (27U)
/* DMA3 local request: "REQUEST28_CAN10_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST28_CAN10_TX_EVENT                  (28U)
/* DMA3 local request: "REQUEST29_CAN11_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST29_CAN11_TX_FIFO                  (29U)
/* DMA3 local request: "REQUEST30_CAN11_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST30_CAN11_RX_FIFO0                  (30U)
/* DMA3 local request: "REQUEST31_CAN11_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST31_CAN11_RX_FIFO1                  (31U)
/* DMA3 local request: "REQUEST32_CAN11_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST32_CAN11_TX_EVENT                  (32U)
/* DMA3 local request: "REQUEST33_CAN12_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST33_CAN12_TX_FIFO                  (33U)
/* DMA3 local request: "REQUEST34_CAN12_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST34_CAN12_RX_FIFO0                  (34U)
/* DMA3 local request: "REQUEST35_CAN12_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST35_CAN12_RX_FIFO1                  (35U)
/* DMA3 local request: "REQUEST36_CAN12_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST36_CAN12_TX_EVENT                  (36U)
/* DMA3 local request: "REQUEST37_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST37_GLOBAL_REQUEST                  (37U)
/* DMA3 local request: "REQUEST38_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST38_GLOBAL_REQUEST                  (38U)
/* DMA3 local request: "REQUEST39_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST39_GLOBAL_REQUEST                  (39U)
/* DMA3 local request: "REQUEST40_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST40_GLOBAL_REQUEST                  (40U)
/* DMA3 local request: "REQUEST41_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST41_GLOBAL_REQUEST                  (41U)
/* DMA3 local request: "REQUEST42_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST42_GLOBAL_REQUEST                  (42U)
/* DMA3 local request: "REQUEST43_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST43_GLOBAL_REQUEST                  (43U)
/* DMA3 local request: "REQUEST44_GLOBAL_REQUEST" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST44_GLOBAL_REQUEST                  (44U)
/* DMA3 local request: "REQUEST45_ASI12_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST45_ASI12_LIN_UART_TX                  (45U)
/* DMA3 local request: "REQUEST46_ASI12_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST46_ASI12_LIN_UART_RX                  (46U)
/* DMA3 local request: "REQUEST47_ASI13_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST47_ASI13_LIN_UART_TX                  (47U)
/* DMA3 local request: "REQUEST48_ASI13_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST48_ASI13_LIN_UART_RX                  (48U)
/* DMA3 local request: "REQUEST49_ASI14_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST49_ASI14_LIN_UART_TX                  (49U)
/* DMA3 local request: "REQUEST50_ASI14_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST50_ASI14_LIN_UART_RX                  (50U)
/* DMA3 local request: "REQUEST51_ASI15_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST51_ASI15_LIN_UART_TX                  (51U)
/* DMA3 local request: "REQUEST52_ASI15_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST52_ASI15_LIN_UART_RX                  (52U)
/* DMA3 local request: "REQUEST53_ASI16_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST53_ASI16_LIN_UART_TX                  (53U)
/* DMA3 local request: "REQUEST54_ASI16_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST54_ASI16_LIN_UART_RX                  (54U)
/* DMA3 local request: "REQUEST55_ASI17_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST55_ASI17_LIN_UART_TX                  (55U)
/* DMA3 local request: "REQUEST56_ASI17_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST56_ASI17_LIN_UART_RX                  (56U)
/* DMA3 local request: "REQUEST57_ASI18_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST57_ASI18_LIN_UART_TX                  (57U)
/* DMA3 local request: "REQUEST58_ASI18_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST58_ASI18_LIN_UART_RX                  (58U)
/* DMA3 local request: "REQUEST59_ASI19_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST59_ASI19_LIN_UART_TX                  (59U)
/* DMA3 local request: "REQUEST60_ASI19_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST60_ASI19_LIN_UART_RX                  (60U)
/* DMA3 local request: "REQUEST61_ASI20_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST61_ASI20_LIN_UART_TX                  (61U)
/* DMA3 local request: "REQUEST62_ASI20_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST62_ASI20_LIN_UART_RX                  (62U)
/* DMA3 local request: "REQUEST63_ASI21_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST63_ASI21_LIN_UART_TX                  (63U)
/* DMA3 local request: "REQUEST64_ASI21_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST64_ASI21_LIN_UART_RX                  (64U)
/* DMA3 local request: "REQUEST65_ASI22_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST65_ASI22_LIN_UART_TX                  (65U)
/* DMA3 local request: "REQUEST66_ASI22_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST66_ASI22_LIN_UART_RX                  (66U)
/* DMA3 local request: "REQUEST67_ASI23_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST67_ASI23_LIN_UART_TX                  (67U)
/* DMA3 local request: "REQUEST68_ASI23_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST68_ASI23_LIN_UART_RX                  (68U)
/* DMA3 local request: "REQUEST69_I2C1_TX_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST69_I2C1_TX_RX                  (69U)
/* DMA3 local request: "REQUEST70_CAN30_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST70_CAN30_TX_FIFO                  (70U)
/* DMA3 local request: "REQUEST71_CAN30_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST71_CAN30_RX_FIFO0                  (71U)
/* DMA3 local request: "REQUEST72_CAN30_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST72_CAN30_RX_FIFO1                  (72U)
/* DMA3 local request: "REQUEST73_CAN30_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST73_CAN30_TX_EVENT                  (73U)
/* DMA3 local request: "REQUEST74_CAN31_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST74_CAN31_TX_FIFO                  (74U)
/* DMA3 local request: "REQUEST75_CAN31_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST75_CAN31_RX_FIFO0                  (75U)
/* DMA3 local request: "REQUEST76_CAN31_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST76_CAN31_RX_FIFO1                  (76U)
/* DMA3 local request: "REQUEST77_CAN31_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST77_CAN31_TX_EVENT                  (77U)
/* DMA3 local request: "REQUEST78_CAN32_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST78_CAN32_TX_FIFO                  (78U)
/* DMA3 local request: "REQUEST79_CAN32_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST79_CAN32_RX_FIFO0                  (79U)
/* DMA3 local request: "REQUEST80_CAN32_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST80_CAN32_RX_FIFO1                  (80U)
/* DMA3 local request: "REQUEST81_CAN32_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST81_CAN32_TX_EVENT                  (81U)
/* DMA3 local request: "REQUEST82_ASI8_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST82_ASI8_LIN_UART_TX                  (82U)
/* DMA3 local request: "REQUEST83_ASI8_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST83_ASI8_LIN_UART_RX                  (83U)
/* DMA3 local request: "REQUEST84_ASI9_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST84_ASI9_LIN_UART_TX                  (84U)
/* DMA3 local request: "REQUEST85_ASI9_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST85_ASI9_LIN_UART_RX                  (85U)
/* DMA3 local request: "REQUEST86_ASI10_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST86_ASI10_LIN_UART_TX                  (86U)
/* DMA3 local request: "REQUEST87_ASI10_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST87_ASI10_LIN_UART_RX                  (87U)
/* DMA3 local request: "REQUEST88_ASI11_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST88_ASI11_LIN_UART_TX                  (88U)
/* DMA3 local request: "REQUEST89_ASI11_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA3_REQUEST89_ASI11_LIN_UART_RX                  (89U)


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
/* DMA global request of multiplexer: "REQUEST8_QSPI" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST8_QSPI                  (8U)
/* DMA global request of multiplexer: "REQUEST9_DSADC0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST9_DSADC0                  (9U)
/* DMA global request of multiplexer: "REQUEST10_DSADC1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST10_DSADC1                  (10U)
/* DMA global request of multiplexer: "REQUEST11_DSADC2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST11_DSADC2                  (11U)
/* DMA global request of multiplexer: "REQUEST12_DSADC3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST12_DSADC3                  (12U)
/* DMA global request of multiplexer: "REQUEST13_FC0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST13_FC0                  (13U)
/* DMA global request of multiplexer: "REQUEST14_FC1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST14_FC1                  (14U)
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
/* DMA global request of multiplexer: "REQUEST80_SARADC8_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST80_SARADC8_RESULT0                  (80U)
/* DMA global request of multiplexer: "REQUEST81_SARADC8_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST81_SARADC8_RESULT1                  (81U)
/* DMA global request of multiplexer: "REQUEST82_SARADC8_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST82_SARADC8_RESULT2                  (82U)
/* DMA global request of multiplexer: "REQUEST83_SARADC8_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST83_SARADC8_RESULT3                  (83U)
/* DMA global request of multiplexer: "REQUEST84_SARADC8_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST84_SARADC8_RESULT4                  (84U)
/* DMA global request of multiplexer: "REQUEST85_SARADC8_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST85_SARADC8_RESULT5                  (85U)
/* DMA global request of multiplexer: "REQUEST86_SARADC8_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST86_SARADC8_RESULT6                  (86U)
/* DMA global request of multiplexer: "REQUEST87_SARADC8_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST87_SARADC8_RESULT7                  (87U)
/* DMA global request of multiplexer: "REQUEST88_SARADC8_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST88_SARADC8_RESULT8                  (88U)
/* DMA global request of multiplexer: "REQUEST89_SARADC8_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST89_SARADC8_RESULT9                  (89U)
/* DMA global request of multiplexer: "REQUEST90_SARADC8_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST90_SARADC8_RESULT10                  (90U)
/* DMA global request of multiplexer: "REQUEST91_SARADC8_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST91_SARADC8_RESULT11                  (91U)
/* DMA global request of multiplexer: "REQUEST92_SARADC8_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST92_SARADC8_RESULT12                  (92U)
/* DMA global request of multiplexer: "REQUEST93_SARADC8_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST93_SARADC8_RESULT13                  (93U)
/* DMA global request of multiplexer: "REQUEST94_SARADC8_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST94_SARADC8_RESULT14                  (94U)
/* DMA global request of multiplexer: "REQUEST95_SARADC8_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST95_SARADC8_RESULT15                  (95U)
/* DMA global request of multiplexer: "REQUEST96_SARADC9_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST96_SARADC9_RESULT0                  (96U)
/* DMA global request of multiplexer: "REQUEST97_SARADC9_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST97_SARADC9_RESULT1                  (97U)
/* DMA global request of multiplexer: "REQUEST98_SARADC9_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST98_SARADC9_RESULT2                  (98U)
/* DMA global request of multiplexer: "REQUEST99_SARADC9_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST99_SARADC9_RESULT3                  (99U)
/* DMA global request of multiplexer: "REQUEST100_SARADC9_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST100_SARADC9_RESULT4                  (100U)
/* DMA global request of multiplexer: "REQUEST101_SARADC9_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST101_SARADC9_RESULT5                  (101U)
/* DMA global request of multiplexer: "REQUEST102_SARADC9_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST102_SARADC9_RESULT6                  (102U)
/* DMA global request of multiplexer: "REQUEST103_SARADC9_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST103_SARADC9_RESULT7                  (103U)
/* DMA global request of multiplexer: "REQUEST104_SARADC9_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST104_SARADC9_RESULT8                  (104U)
/* DMA global request of multiplexer: "REQUEST105_SARADC9_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST105_SARADC9_RESULT9                  (105U)
/* DMA global request of multiplexer: "REQUEST106_SARADC9_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST106_SARADC9_RESULT10                  (106U)
/* DMA global request of multiplexer: "REQUEST107_SARADC9_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST107_SARADC9_RESULT11                  (107U)
/* DMA global request of multiplexer: "REQUEST108_SARADC9_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST108_SARADC9_RESULT12                  (108U)
/* DMA global request of multiplexer: "REQUEST109_SARADC9_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST109_SARADC9_RESULT13                  (109U)
/* DMA global request of multiplexer: "REQUEST110_SARADC9_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST110_SARADC9_RESULT14                  (110U)
/* DMA global request of multiplexer: "REQUEST111_SARADC9_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST111_SARADC9_RESULT15                  (111U)
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
/* DMA global request of multiplexer: "REQUEST121_ESPI6_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST121_ESPI6_RX                  (121U)
/* DMA global request of multiplexer: "REQUEST122_ESPI7_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST122_ESPI7_TX                  (122U)
/* DMA global request of multiplexer: "REQUEST123_ESPI7_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST123_ESPI7_RX                  (123U)
/* DMA global request of multiplexer: "REQUEST124_ESPI8_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST124_ESPI8_TX                  (124U)
/* DMA global request of multiplexer: "REQUEST125_ESPI8_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST125_ESPI8_RX                  (125U)
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
/* DMA global request of multiplexer: "REQUEST159_MSC0_DOWNSTREAM_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST159_MSC0_DOWNSTREAM_DATA_TX                  (159U)
/* DMA global request of multiplexer: "REQUEST160_MSC0_DOWNSTREAM_CMD_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST160_MSC0_DOWNSTREAM_CMD_TX                  (160U)
/* DMA global request of multiplexer: "REQUEST161_MSC0_DOWNSTREAM_PT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST161_MSC0_DOWNSTREAM_PT                  (161U)
/* DMA global request of multiplexer: "REQUEST162_MSC0_UPSTREAM_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST162_MSC0_UPSTREAM_DATA_RX                  (162U)
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
/* DMA global request of multiplexer: "REQUEST175_DSADC4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST175_DSADC4                  (175U)
/* DMA global request of multiplexer: "REQUEST176_DSADC5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST176_DSADC5                  (176U)
/* DMA global request of multiplexer: "REQUEST177_DSADC6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST177_DSADC6                  (177U)
/* DMA global request of multiplexer: "REQUEST178_DSADC7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST178_DSADC7                  (178U)
/* DMA global request of multiplexer: "REQUEST179_DSADC8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST179_DSADC8                  (179U)
/* DMA global request of multiplexer: "REQUEST180_DSADC9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST180_DSADC9                  (180U)
/* DMA global request of multiplexer: "REQUEST181_FC2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST181_FC2                  (181U)
/* DMA global request of multiplexer: "REQUEST182_FC3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST182_FC3                  (182U)
/* DMA global request of multiplexer: "REQUEST183_SARADC4_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST183_SARADC4_RESULT0                  (183U)
/* DMA global request of multiplexer: "REQUEST184_SARADC4_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST184_SARADC4_RESULT1                  (184U)
/* DMA global request of multiplexer: "REQUEST185_SARADC4_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST185_SARADC4_RESULT2                  (185U)
/* DMA global request of multiplexer: "REQUEST186_SARADC4_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST186_SARADC4_RESULT3                  (186U)
/* DMA global request of multiplexer: "REQUEST187_SARADC4_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST187_SARADC4_RESULT4                  (187U)
/* DMA global request of multiplexer: "REQUEST188_SARADC4_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST188_SARADC4_RESULT5                  (188U)
/* DMA global request of multiplexer: "REQUEST189_SARADC4_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST189_SARADC4_RESULT6                  (189U)
/* DMA global request of multiplexer: "REQUEST190_SARADC4_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST190_SARADC4_RESULT7                  (190U)
/* DMA global request of multiplexer: "REQUEST191_SARADC4_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST191_SARADC4_RESULT8                  (191U)
/* DMA global request of multiplexer: "REQUEST192_SARADC4_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST192_SARADC4_RESULT9                  (192U)
/* DMA global request of multiplexer: "REQUEST193_SARADC4_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST193_SARADC4_RESULT10                  (193U)
/* DMA global request of multiplexer: "REQUEST194_SARADC4_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST194_SARADC4_RESULT11                  (194U)
/* DMA global request of multiplexer: "REQUEST195_SARADC4_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST195_SARADC4_RESULT12                  (195U)
/* DMA global request of multiplexer: "REQUEST196_SARADC4_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST196_SARADC4_RESULT13                  (196U)
/* DMA global request of multiplexer: "REQUEST197_SARADC4_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST197_SARADC4_RESULT14                  (197U)
/* DMA global request of multiplexer: "REQUEST198_SARADC4_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST198_SARADC4_RESULT15                  (198U)
/* DMA global request of multiplexer: "REQUEST199_SARADC5_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST199_SARADC5_RESULT0                  (199U)
/* DMA global request of multiplexer: "REQUEST200_SARADC5_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST200_SARADC5_RESULT1                  (200U)
/* DMA global request of multiplexer: "REQUEST201_SARADC5_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST201_SARADC5_RESULT2                  (201U)
/* DMA global request of multiplexer: "REQUEST202_SARADC5_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST202_SARADC5_RESULT3                  (202U)
/* DMA global request of multiplexer: "REQUEST203_SARADC5_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST203_SARADC5_RESULT4                  (203U)
/* DMA global request of multiplexer: "REQUEST204_SARADC5_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST204_SARADC5_RESULT5                  (204U)
/* DMA global request of multiplexer: "REQUEST205_SARADC5_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST205_SARADC5_RESULT6                  (205U)
/* DMA global request of multiplexer: "REQUEST206_SARADC5_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST206_SARADC5_RESULT7                  (206U)
/* DMA global request of multiplexer: "REQUEST207_SARADC5_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST207_SARADC5_RESULT8                  (207U)
/* DMA global request of multiplexer: "REQUEST208_SARADC5_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST208_SARADC5_RESULT9                  (208U)
/* DMA global request of multiplexer: "REQUEST209_SARADC5_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST209_SARADC5_RESULT10                  (209U)
/* DMA global request of multiplexer: "REQUEST210_SARADC5_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST210_SARADC5_RESULT11                  (210U)
/* DMA global request of multiplexer: "REQUEST211_SARADC5_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST211_SARADC5_RESULT12                  (211U)
/* DMA global request of multiplexer: "REQUEST212_SARADC5_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST212_SARADC5_RESULT13                  (212U)
/* DMA global request of multiplexer: "REQUEST213_SARADC5_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST213_SARADC5_RESULT14                  (213U)
/* DMA global request of multiplexer: "REQUEST214_SARADC5_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST214_SARADC5_RESULT15                  (214U)
/* DMA global request of multiplexer: "REQUEST215_SARADC6_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST215_SARADC6_RESULT0                  (215U)
/* DMA global request of multiplexer: "REQUEST216_SARADC6_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST216_SARADC6_RESULT1                  (216U)
/* DMA global request of multiplexer: "REQUEST217_SARADC6_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST217_SARADC6_RESULT2                  (217U)
/* DMA global request of multiplexer: "REQUEST218_SARADC6_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST218_SARADC6_RESULT3                  (218U)
/* DMA global request of multiplexer: "REQUEST219_SARADC6_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST219_SARADC6_RESULT4                  (219U)
/* DMA global request of multiplexer: "REQUEST220_SARADC6_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST220_SARADC6_RESULT5                  (220U)
/* DMA global request of multiplexer: "REQUEST221_SARADC6_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST221_SARADC6_RESULT6                  (221U)
/* DMA global request of multiplexer: "REQUEST222_SARADC6_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST222_SARADC6_RESULT7                  (222U)
/* DMA global request of multiplexer: "REQUEST223_SARADC6_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST223_SARADC6_RESULT8                  (223U)
/* DMA global request of multiplexer: "REQUEST224_SARADC6_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST224_SARADC6_RESULT9                  (224U)
/* DMA global request of multiplexer: "REQUEST225_SARADC6_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST225_SARADC6_RESULT10                  (225U)
/* DMA global request of multiplexer: "REQUEST226_SARADC6_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST226_SARADC6_RESULT11                  (226U)
/* DMA global request of multiplexer: "REQUEST227_SARADC6_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST227_SARADC6_RESULT12                  (227U)
/* DMA global request of multiplexer: "REQUEST228_SARADC6_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST228_SARADC6_RESULT13                  (228U)
/* DMA global request of multiplexer: "REQUEST229_SARADC6_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST229_SARADC6_RESULT14                  (229U)
/* DMA global request of multiplexer: "REQUEST230_SARADC6_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST230_SARADC6_RESULT15                  (230U)
/* DMA global request of multiplexer: "REQUEST231_SARADC7_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST231_SARADC7_RESULT0                  (231U)
/* DMA global request of multiplexer: "REQUEST232_SARADC7_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST232_SARADC7_RESULT1                  (232U)
/* DMA global request of multiplexer: "REQUEST233_SARADC7_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST233_SARADC7_RESULT2                  (233U)
/* DMA global request of multiplexer: "REQUEST234_SARADC7_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST234_SARADC7_RESULT3                  (234U)
/* DMA global request of multiplexer: "REQUEST235_SARADC7_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST235_SARADC7_RESULT4                  (235U)
/* DMA global request of multiplexer: "REQUEST236_SARADC7_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST236_SARADC7_RESULT5                  (236U)
/* DMA global request of multiplexer: "REQUEST237_SARADC7_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST237_SARADC7_RESULT6                  (237U)
/* DMA global request of multiplexer: "REQUEST238_SARADC7_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST238_SARADC7_RESULT7                  (238U)
/* DMA global request of multiplexer: "REQUEST239_SARADC7_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST239_SARADC7_RESULT8                  (239U)
/* DMA global request of multiplexer: "REQUEST240_SARADC7_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST240_SARADC7_RESULT9                  (240U)
/* DMA global request of multiplexer: "REQUEST241_SARADC7_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST241_SARADC7_RESULT10                  (241U)
/* DMA global request of multiplexer: "REQUEST242_SARADC7_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST242_SARADC7_RESULT11                  (242U)
/* DMA global request of multiplexer: "REQUEST243_SARADC7_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST243_SARADC7_RESULT12                  (243U)
/* DMA global request of multiplexer: "REQUEST244_SARADC7_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST244_SARADC7_RESULT13                  (244U)
/* DMA global request of multiplexer: "REQUEST245_SARADC7_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST245_SARADC7_RESULT14                  (245U)
/* DMA global request of multiplexer: "REQUEST246_SARADC7_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST246_SARADC7_RESULT15                  (246U)
/* DMA global request of multiplexer: "REQUEST247_SARADC10_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST247_SARADC10_RESULT0                  (247U)
/* DMA global request of multiplexer: "REQUEST248_SARADC10_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST248_SARADC10_RESULT1                  (248U)
/* DMA global request of multiplexer: "REQUEST249_SARADC10_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST249_SARADC10_RESULT2                  (249U)
/* DMA global request of multiplexer: "REQUEST250_SARADC10_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST250_SARADC10_RESULT3                  (250U)
/* DMA global request of multiplexer: "REQUEST251_SARADC10_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST251_SARADC10_RESULT4                  (251U)
/* DMA global request of multiplexer: "REQUEST252_SARADC10_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST252_SARADC10_RESULT5                  (252U)
/* DMA global request of multiplexer: "REQUEST253_SARADC10_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST253_SARADC10_RESULT6                  (253U)
/* DMA global request of multiplexer: "REQUEST254_SARADC10_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST254_SARADC10_RESULT7                  (254U)
/* DMA global request of multiplexer: "REQUEST255_SARADC10_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST255_SARADC10_RESULT8                  (255U)
/* DMA global request of multiplexer: "REQUEST256_SARADC10_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST256_SARADC10_RESULT9                  (256U)
/* DMA global request of multiplexer: "REQUEST257_SARADC10_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST257_SARADC10_RESULT10                  (257U)
/* DMA global request of multiplexer: "REQUEST258_SARADC10_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST258_SARADC10_RESULT11                  (258U)
/* DMA global request of multiplexer: "REQUEST259_SARADC10_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST259_SARADC10_RESULT12                  (259U)
/* DMA global request of multiplexer: "REQUEST260_SARADC10_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST260_SARADC10_RESULT13                  (260U)
/* DMA global request of multiplexer: "REQUEST261_SARADC10_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST261_SARADC10_RESULT14                  (261U)
/* DMA global request of multiplexer: "REQUEST262_SARADC10_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST262_SARADC10_RESULT15                  (262U)
/* DMA global request of multiplexer: "REQUEST263_SARADC11_RESULT0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST263_SARADC11_RESULT0                  (263U)
/* DMA global request of multiplexer: "REQUEST264_SARADC11_RESULT1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST264_SARADC11_RESULT1                  (264U)
/* DMA global request of multiplexer: "REQUEST265_SARADC11_RESULT2" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST265_SARADC11_RESULT2                  (265U)
/* DMA global request of multiplexer: "REQUEST266_SARADC11_RESULT3" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST266_SARADC11_RESULT3                  (266U)
/* DMA global request of multiplexer: "REQUEST267_SARADC11_RESULT4" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST267_SARADC11_RESULT4                  (267U)
/* DMA global request of multiplexer: "REQUEST268_SARADC11_RESULT5" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST268_SARADC11_RESULT5                  (268U)
/* DMA global request of multiplexer: "REQUEST269_SARADC11_RESULT6" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST269_SARADC11_RESULT6                  (269U)
/* DMA global request of multiplexer: "REQUEST270_SARADC11_RESULT7" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST270_SARADC11_RESULT7                  (270U)
/* DMA global request of multiplexer: "REQUEST271_SARADC11_RESULT8" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST271_SARADC11_RESULT8                  (271U)
/* DMA global request of multiplexer: "REQUEST272_SARADC11_RESULT9" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST272_SARADC11_RESULT9                  (272U)
/* DMA global request of multiplexer: "REQUEST273_SARADC11_RESULT10" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST273_SARADC11_RESULT10                  (273U)
/* DMA global request of multiplexer: "REQUEST274_SARADC11_RESULT11" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST274_SARADC11_RESULT11                  (274U)
/* DMA global request of multiplexer: "REQUEST275_SARADC11_RESULT12" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST275_SARADC11_RESULT12                  (275U)
/* DMA global request of multiplexer: "REQUEST276_SARADC11_RESULT13" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST276_SARADC11_RESULT13                  (276U)
/* DMA global request of multiplexer: "REQUEST277_SARADC11_RESULT14" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST277_SARADC11_RESULT14                  (277U)
/* DMA global request of multiplexer: "REQUEST278_SARADC11_RESULT15" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST278_SARADC11_RESULT15                  (278U)
/* DMA global request of multiplexer: "REQUEST279_PSI5_CH0_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST279_PSI5_CH0_DATA_TX                  (279U)
/* DMA global request of multiplexer: "REQUEST280_PSI5_CH0_CTRL_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST280_PSI5_CH0_CTRL_TX                  (280U)
/* DMA global request of multiplexer: "REQUEST281_PSI5_CH0_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST281_PSI5_CH0_DATA_RX                  (281U)
/* DMA global request of multiplexer: "REQUEST282_PSI5_CH0_CTRL_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST282_PSI5_CH0_CTRL_RX                  (282U)
/* DMA global request of multiplexer: "REQUEST283_PSI5_CH1_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST283_PSI5_CH1_DATA_TX                  (283U)
/* DMA global request of multiplexer: "REQUEST284_PSI5_CH1_CTRL_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST284_PSI5_CH1_CTRL_TX                  (284U)
/* DMA global request of multiplexer: "REQUEST285_PSI5_CH1_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST285_PSI5_CH1_DATA_RX                  (285U)
/* DMA global request of multiplexer: "REQUEST286_PSI5_CH1_CTRL_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST286_PSI5_CH1_CTRL_RX                  (286U)
/* DMA global request of multiplexer: "REQUEST287_PSI5_CH2_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST287_PSI5_CH2_DATA_TX                  (287U)
/* DMA global request of multiplexer: "REQUEST288_PSI5_CH2_CTRL_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST288_PSI5_CH2_CTRL_TX                  (288U)
/* DMA global request of multiplexer: "REQUEST289_PSI5_CH2_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST289_PSI5_CH2_DATA_RX                  (289U)
/* DMA global request of multiplexer: "REQUEST290_PSI5_CH2_CTRL_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST290_PSI5_CH2_CTRL_RX                  (290U)
/* DMA global request of multiplexer: "REQUEST291_PSI5_CH3_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST291_PSI5_CH3_DATA_TX                  (291U)
/* DMA global request of multiplexer: "REQUEST292_PSI5_CH3_CTRL_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST292_PSI5_CH3_CTRL_TX                  (292U)
/* DMA global request of multiplexer: "REQUEST293_PSI5_CH3_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST293_PSI5_CH3_DATA_RX                  (293U)
/* DMA global request of multiplexer: "REQUEST294_PSI5_CH3_CTRL_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST294_PSI5_CH3_CTRL_RX                  (294U)
/* DMA global request of multiplexer: "REQUEST295_CAN20_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST295_CAN20_TX_FIFO                  (295U)
/* DMA global request of multiplexer: "REQUEST296_CAN20_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST296_CAN20_RX_FIFO0                  (296U)
/* DMA global request of multiplexer: "REQUEST297_CAN20_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST297_CAN20_RX_FIFO1                  (297U)
/* DMA global request of multiplexer: "REQUEST298_CAN20_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST298_CAN20_TX_EVENT                  (298U)
/* DMA global request of multiplexer: "REQUEST299_CAN21_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST299_CAN21_TX_FIFO                  (299U)
/* DMA global request of multiplexer: "REQUEST300_CAN21_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST300_CAN21_RX_FIFO0                  (300U)
/* DMA global request of multiplexer: "REQUEST301_CAN21_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST301_CAN21_RX_FIFO1                  (301U)
/* DMA global request of multiplexer: "REQUEST302_CAN21_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST302_CAN21_TX_EVENT                  (302U)
/* DMA global request of multiplexer: "REQUEST303_CAN22_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST303_CAN22_TX_FIFO                  (303U)
/* DMA global request of multiplexer: "REQUEST304_CAN22_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST304_CAN22_RX_FIFO0                  (304U)
/* DMA global request of multiplexer: "REQUEST305_CAN22_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST305_CAN22_RX_FIFO1                  (305U)
/* DMA global request of multiplexer: "REQUEST306_CAN22_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST306_CAN22_TX_EVENT                  (306U)
/* DMA global request of multiplexer: "REQUEST307_MSC1_DOWNSTREAM_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST307_MSC1_DOWNSTREAM_DATA_TX                  (307U)
/* DMA global request of multiplexer: "REQUEST308_MSC1_DOWNSTREAM_CMD_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST308_MSC1_DOWNSTREAM_CMD_TX                  (308U)
/* DMA global request of multiplexer: "REQUEST309_MSC1_DOWNSTREAM_PT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST309_MSC1_DOWNSTREAM_PT                  (309U)
/* DMA global request of multiplexer: "REQUEST310_MSC1_UPSTREAM_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST310_MSC1_UPSTREAM_DATA_RX                  (310U)
/* DMA global request of multiplexer: "REQUEST311_MSC2_DOWNSTREAM_DATA_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST311_MSC2_DOWNSTREAM_DATA_TX                  (311U)
/* DMA global request of multiplexer: "REQUEST312_MSC2_DOWNSTREAM_CMD_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST312_MSC2_DOWNSTREAM_CMD_TX                  (312U)
/* DMA global request of multiplexer: "REQUEST313_MSC2_DOWNSTREAM_PT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST313_MSC2_DOWNSTREAM_PT                  (313U)
/* DMA global request of multiplexer: "REQUEST314_MSC2_UPSTREAM_DATA_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST314_MSC2_UPSTREAM_DATA_RX                  (314U)
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
/* DMA global request of multiplexer: "REQUEST331_ASI12_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST331_ASI12_LIN_UART_TX                  (331U)
/* DMA global request of multiplexer: "REQUEST332_ASI12_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST332_ASI12_LIN_UART_RX                  (332U)
/* DMA global request of multiplexer: "REQUEST333_ASI13_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST333_ASI13_LIN_UART_TX                  (333U)
/* DMA global request of multiplexer: "REQUEST334_ASI13_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST334_ASI13_LIN_UART_RX                  (334U)
/* DMA global request of multiplexer: "REQUEST335_ASI14_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST335_ASI14_LIN_UART_TX                  (335U)
/* DMA global request of multiplexer: "REQUEST336_ASI14_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST336_ASI14_LIN_UART_RX                  (336U)
/* DMA global request of multiplexer: "REQUEST337_ASI15_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST337_ASI15_LIN_UART_TX                  (337U)
/* DMA global request of multiplexer: "REQUEST338_ASI15_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST338_ASI15_LIN_UART_RX                  (338U)
/* DMA global request of multiplexer: "REQUEST339_ASI16_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST339_ASI16_LIN_UART_TX                  (339U)
/* DMA global request of multiplexer: "REQUEST340_ASI16_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST340_ASI16_LIN_UART_RX                  (340U)
/* DMA global request of multiplexer: "REQUEST341_ASI17_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST341_ASI17_LIN_UART_TX                  (341U)
/* DMA global request of multiplexer: "REQUEST342_ASI17_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST342_ASI17_LIN_UART_RX                  (342U)
/* DMA global request of multiplexer: "REQUEST343_ASI18_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST343_ASI18_LIN_UART_TX                  (343U)
/* DMA global request of multiplexer: "REQUEST344_ASI18_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST344_ASI18_LIN_UART_RX                  (344U)
/* DMA global request of multiplexer: "REQUEST345_ASI19_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST345_ASI19_LIN_UART_TX                  (345U)
/* DMA global request of multiplexer: "REQUEST346_ASI19_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST346_ASI19_LIN_UART_RX                  (346U)
/* DMA global request of multiplexer: "REQUEST347_ASI20_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST347_ASI20_LIN_UART_TX                  (347U)
/* DMA global request of multiplexer: "REQUEST348_ASI20_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST348_ASI20_LIN_UART_RX                  (348U)
/* DMA global request of multiplexer: "REQUEST349_ASI21_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST349_ASI21_LIN_UART_TX                  (349U)
/* DMA global request of multiplexer: "REQUEST350_ASI21_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST350_ASI21_LIN_UART_RX                  (350U)
/* DMA global request of multiplexer: "REQUEST351_ASI22_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST351_ASI22_LIN_UART_TX                  (351U)
/* DMA global request of multiplexer: "REQUEST352_ASI22_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST352_ASI22_LIN_UART_RX                  (352U)
/* DMA global request of multiplexer: "REQUEST353_ASI23_LIN_UART_TX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST353_ASI23_LIN_UART_TX                  (353U)
/* DMA global request of multiplexer: "REQUEST354_ASI23_LIN_UART_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST354_ASI23_LIN_UART_RX                  (354U)
/* DMA global request of multiplexer: "REQUEST355_I2C1_TX_RX" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST355_I2C1_TX_RX                  (355U)
/* DMA global request of multiplexer: "REQUEST356_CAN30_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST356_CAN30_TX_FIFO                  (356U)
/* DMA global request of multiplexer: "REQUEST357_CAN30_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST357_CAN30_RX_FIFO0                  (357U)
/* DMA global request of multiplexer: "REQUEST358_CAN30_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST358_CAN30_RX_FIFO1                  (358U)
/* DMA global request of multiplexer: "REQUEST359_CAN30_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST359_CAN30_TX_EVENT                  (359U)
/* DMA global request of multiplexer: "REQUEST360_CAN31_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST360_CAN31_TX_FIFO                  (360U)
/* DMA global request of multiplexer: "REQUEST361_CAN31_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST361_CAN31_RX_FIFO0                  (361U)
/* DMA global request of multiplexer: "REQUEST362_CAN31_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST362_CAN31_RX_FIFO1                  (362U)
/* DMA global request of multiplexer: "REQUEST363_CAN31_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST363_CAN31_TX_EVENT                  (363U)
/* DMA global request of multiplexer: "REQUEST364_CAN32_TX_FIFO" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST364_CAN32_TX_FIFO                  (364U)
/* DMA global request of multiplexer: "REQUEST365_CAN32_RX_FIFO0" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST365_CAN32_RX_FIFO0                  (365U)
/* DMA global request of multiplexer: "REQUEST366_CAN32_RX_FIFO1" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST366_CAN32_RX_FIFO1                  (366U)
/* DMA global request of multiplexer: "REQUEST367_CAN32_TX_EVENT" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_REQUEST367_CAN32_TX_EVENT                  (367U)

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
/* Transfer ID(M2M_LinkedList) in Channel ID4(M2M_LinkedList): Physical channel4 in DMA0 */
#ifndef DmaConf_DmaChTransferConfig_LinkedListTransfer0
#define DmaConf_DmaChTransferConfig_LinkedListTransfer0             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_LinkedListTransfer0 */
/* Transfer ID(M2M_LinkedList) in Channel ID4(M2M_LinkedList): Physical channel4 in DMA0 */
#ifndef DmaConf_DmaChTransferConfig_LinkedListTransfer1
#define DmaConf_DmaChTransferConfig_LinkedListTransfer1             ((Dma_TransferType)1U)
#endif /* DmaConf_DmaChTransferConfig_LinkedListTransfer1 */
/* Transfer ID(M2M_LinkedList) in Channel ID4(M2M_LinkedList): Physical channel4 in DMA0 */
#ifndef DmaConf_DmaChTransferConfig_LinkedListTransfer2
#define DmaConf_DmaChTransferConfig_LinkedListTransfer2             ((Dma_TransferType)2U)
#endif /* DmaConf_DmaChTransferConfig_LinkedListTransfer2 */
/* Transfer ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel0 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_BasicTransfer
#define DmaConf_DmaChTransferConfig_BasicTransfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_BasicTransfer */
/* Transfer ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel0 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_ShadowTransfer0
#define DmaConf_DmaChTransferConfig_ShadowTransfer0             ((Dma_TransferType)1U)
#endif /* DmaConf_DmaChTransferConfig_ShadowTransfer0 */
/* Transfer ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel0 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_ShadowTransfer1
#define DmaConf_DmaChTransferConfig_ShadowTransfer1             ((Dma_TransferType)2U)
#endif /* DmaConf_DmaChTransferConfig_ShadowTransfer1 */
/* Transfer ID(M2M_Pattern) in Channel ID6(M2M_Pattern): Physical channel0 in DMA2 */
#ifndef DmaConf_DmaChTransferConfig_M2M_Pattern_Transfer
#define DmaConf_DmaChTransferConfig_M2M_Pattern_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_Pattern_Transfer */
/* Transfer ID(M2M_Daisy0) in Channel ID7(M2M_Daisy0): Physical channel0 in DMA3 */
#ifndef DmaConf_DmaChTransferConfig_M2M_Daisy0_Transfer
#define DmaConf_DmaChTransferConfig_M2M_Daisy0_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_Daisy0_Transfer */
/* Transfer ID(M2M_Daisy1) in Channel ID8(M2M_Daisy1): Physical channel1 in DMA3 */
#ifndef DmaConf_DmaChTransferConfig_M2M_Daisy1_Transfer
#define DmaConf_DmaChTransferConfig_M2M_Daisy1_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_M2M_Daisy1_Transfer */
/* Transfer ID(ADC1_Channel0) in Channel ID9(ADC1_Channel0): Physical channel2 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_DmaChTransferConfig_0
#define DmaConf_DmaChTransferConfig_DmaChTransferConfig_0             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_DmaChTransferConfig_0 */
/* Transfer ID(ADC1_Channel1) in Channel ID10(ADC1_Channel1): Physical channel3 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_Channel1_Transfer
#define DmaConf_DmaChTransferConfig_ADC1_Channel1_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_Channel1_Transfer */
/* Transfer ID(ADC1_Channel2) in Channel ID11(ADC1_Channel2): Physical channel4 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_Channel2_Transfer
#define DmaConf_DmaChTransferConfig_ADC1_Channel2_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_Channel2_Transfer */
/* Transfer ID(ADC1_Channel3) in Channel ID12(ADC1_Channel3): Physical channel5 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_Channel3_Transfer
#define DmaConf_DmaChTransferConfig_ADC1_Channel3_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_Channel3_Transfer */
/* Transfer ID(ADC1_Channel7) in Channel ID13(ADC1_Channel7): Physical channel6 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_Channel7_Transfer
#define DmaConf_DmaChTransferConfig_ADC1_Channel7_Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_Channel7_Transfer */
/* Transfer ID(ADC1_GroupSwTrig2) in Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel4
#define DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel4             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel4 */
/* Transfer ID(ADC1_GroupSwTrig2) in Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel5
#define DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel5             ((Dma_TransferType)1U)
#endif /* DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel5 */
/* Transfer ID(ADC1_GroupSwTrig2) in Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel6
#define DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel6             ((Dma_TransferType)2U)
#endif /* DmaConf_DmaChTransferConfig_DmaChTransfer_ADC1_Channel6 */
/* Transfer ID(Dsadc3) in Channel ID17(Dsadc3): Physical channel8 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_Dsadc3Transfer
#define DmaConf_DmaChTransferConfig_Dsadc3Transfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_Dsadc3Transfer */
/* Transfer ID(ADC1_AllChToOneResReg) in Channel ID18(ADC1_AllChToOneResReg): Physical channel9 in DMA1 */
#ifndef DmaConf_DmaChTransferConfig_ADC1_AllChToOneResRegTransfer
#define DmaConf_DmaChTransferConfig_ADC1_AllChToOneResRegTransfer             ((Dma_TransferType)0U)
#endif /* DmaConf_DmaChTransferConfig_ADC1_AllChToOneResRegTransfer */

/****************************************************************************************************
**                          Macro definition of shadow operation                                   **
****************************************************************************************************/
/* Shadowing operation ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel0 in DMA1 */
#ifndef DmaConf_DmaChShadowConfig_DmaChShadowConfig_0
#define DmaConf_DmaChShadowConfig_DmaChShadowConfig_0              ((Dma_ShadowingType)0U)
#endif /* DmaConf_DmaChShadowConfig_DmaChShadowConfig_0 */
/* Shadowing operation ID(M2M_Shadow) in Channel ID5(M2M_Shadow): Physical channel0 in DMA1 */
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

/* Channel ID4(M2M_LinkedList): Physical channel4 in DMA0 */
#ifndef DmaConf_DmaChannel_M2M_LinkedList
#define DmaConf_DmaChannel_M2M_LinkedList                      ((Dma_ChannelType)4)
#endif /* DmaConf_DmaChannel_M2M_LinkedList */

/* Channel ID5(M2M_Shadow): Physical channel0 in DMA1 */
#ifndef DmaConf_DmaChannel_M2M_Shadow
#define DmaConf_DmaChannel_M2M_Shadow                      ((Dma_ChannelType)5)
#endif /* DmaConf_DmaChannel_M2M_Shadow */

/* Channel ID6(M2M_Pattern): Physical channel0 in DMA2 */
#ifndef DmaConf_DmaChannel_M2M_Pattern
#define DmaConf_DmaChannel_M2M_Pattern                      ((Dma_ChannelType)6)
#endif /* DmaConf_DmaChannel_M2M_Pattern */

/* Channel ID7(M2M_Daisy0): Physical channel0 in DMA3 */
#ifndef DmaConf_DmaChannel_M2M_Daisy0
#define DmaConf_DmaChannel_M2M_Daisy0                      ((Dma_ChannelType)7)
#endif /* DmaConf_DmaChannel_M2M_Daisy0 */

/* Channel ID8(M2M_Daisy1): Physical channel1 in DMA3 */
#ifndef DmaConf_DmaChannel_M2M_Daisy1
#define DmaConf_DmaChannel_M2M_Daisy1                      ((Dma_ChannelType)8)
#endif /* DmaConf_DmaChannel_M2M_Daisy1 */

/* Channel ID9(ADC1_Channel0): Physical channel2 in DMA1 */
#ifndef DmaConf_DmaChannel_ADC1_Channel0
#define DmaConf_DmaChannel_ADC1_Channel0                      ((Dma_ChannelType)9)
#endif /* DmaConf_DmaChannel_ADC1_Channel0 */

/* Channel ID10(ADC1_Channel1): Physical channel3 in DMA1 */
#ifndef DmaConf_DmaChannel_ADC1_Channel1
#define DmaConf_DmaChannel_ADC1_Channel1                      ((Dma_ChannelType)10)
#endif /* DmaConf_DmaChannel_ADC1_Channel1 */

/* Channel ID11(ADC1_Channel2): Physical channel4 in DMA1 */
#ifndef DmaConf_DmaChannel_ADC1_Channel2
#define DmaConf_DmaChannel_ADC1_Channel2                      ((Dma_ChannelType)11)
#endif /* DmaConf_DmaChannel_ADC1_Channel2 */

/* Channel ID12(ADC1_Channel3): Physical channel5 in DMA1 */
#ifndef DmaConf_DmaChannel_ADC1_Channel3
#define DmaConf_DmaChannel_ADC1_Channel3                      ((Dma_ChannelType)12)
#endif /* DmaConf_DmaChannel_ADC1_Channel3 */

/* Channel ID13(ADC1_Channel7): Physical channel6 in DMA1 */
#ifndef DmaConf_DmaChannel_ADC1_Channel7
#define DmaConf_DmaChannel_ADC1_Channel7                      ((Dma_ChannelType)13)
#endif /* DmaConf_DmaChannel_ADC1_Channel7 */

/* Channel ID14(ADC1_GroupSwTrig2): Physical channel7 in DMA1 */
#ifndef DmaConf_DmaChannel_ADC1_GroupSwTrig2
#define DmaConf_DmaChannel_ADC1_GroupSwTrig2                      ((Dma_ChannelType)14)
#endif /* DmaConf_DmaChannel_ADC1_GroupSwTrig2 */

/* Channel ID15(SPITx): Physical channel2 in DMA2 */
#ifndef DmaConf_DmaChannel_SPITx
#define DmaConf_DmaChannel_SPITx                      ((Dma_ChannelType)15)
#endif /* DmaConf_DmaChannel_SPITx */

/* Channel ID16(SPIRx): Physical channel3 in DMA2 */
#ifndef DmaConf_DmaChannel_SPIRx
#define DmaConf_DmaChannel_SPIRx                      ((Dma_ChannelType)16)
#endif /* DmaConf_DmaChannel_SPIRx */

/* Channel ID17(Dsadc3): Physical channel8 in DMA1 */
#ifndef DmaConf_DmaChannel_Dsadc3
#define DmaConf_DmaChannel_Dsadc3                      ((Dma_ChannelType)17)
#endif /* DmaConf_DmaChannel_Dsadc3 */

/* Channel ID18(ADC1_AllChToOneResReg): Physical channel9 in DMA1 */
#ifndef DmaConf_DmaChannel_ADC1_AllChToOneResReg
#define DmaConf_DmaChannel_ADC1_AllChToOneResReg                      ((Dma_ChannelType)18)
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


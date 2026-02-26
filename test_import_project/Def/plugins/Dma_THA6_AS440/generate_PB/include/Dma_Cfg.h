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

[!NOCODE!][!//
[!INCLUDE "Dma_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
#ifndef DMA_CFG_H_
#define DMA_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
[!SELECT "as:modconf('Dma')[1]"!][!//

#define DMA_CFG_AR_RELEASE_MAJOR_VERSION                   ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define DMA_CFG_AR_RELEASE_MINOR_VERSION                   ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define DMA_CFG_AR_RELEASE_REVISION_VERSION                ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define DMA_CFG_SW_MAJOR_VERSION                           ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define DMA_CFG_SW_MINOR_VERSION                           ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define DMA_CFG_SW_PATCH_VERSION                           ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define DMA_CFG_VENDOR_ID                                  ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define DMA_CFG_MODULE_ID                                  ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/* Total configuration sets */
#define DMA_CONFIGSET_CNT                                  (1U)

/*
Configuration: DmaSafetyErrorDetect
- if Selected, Safety Error Check is Enabled 
- if Deselected, Safety Error Check is Disabled 
*/
#define DMA_SAFETY_ENABLE                                  [!IF "DmaGeneral/DmaSafetyErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaDevErrorDetect
- if Selected, DET is Enabled 
- if Deselected, DET is Disabled 
*/
#define DMA_DEV_ERROR_DETECT                               [!IF "DmaGeneral/DmaDevErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaDeInitApi
- if Selected, DeInit() API is Enabled 
- if Deselected, DeInit() API is Disabled 
*/
#define DMA_CFG_DEINIT_API                                 [!IF "DmaGeneral/DmaDeInitApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaSuspendResumeApi
- if Selected, Dma_ChannelPause() API is Enabled 
- if Deselected, Dma_ChannelPause() API is Disabled 
*/
#define DMA_CFG_CHANNEL_PAUSE_API                          [!IF "DmaGeneral/DmaSuspendResumeApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaCancelApi
- if Selected, Dma_ChannelCancel() API is Enabled 
- if Deselected, Dma_ChannelCancel() API is Disabled 
*/
#define DMA_CFG_CHANNEL_CANCEL_API                         [!IF "DmaGeneral/DmaCancelApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaRemainingTransferApi
- if Selected, Dma_ChannelCancel() API is Enabled 
- if Deselected, Dma_ChannelCancel() API is Disabled 
*/
#define DMA_CFG_CHANNEL_REMAINING_TRANSFER_API             [!IF "DmaGeneral/DmaRemainingTransferApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaVersionInfoApi
- if Selected, Dma_GetVersionInfo() API is Enabled 
- if Deselected, Dma_GetVersionInfo API is Disabled 
*/
#define DMA_CFG_VERSION_INFO_API                           [!IF "DmaGeneral/DmaVersionInfoApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaDoubleBufferSoftwareSwitchApi
- if Selected, Dma_ChannelDoubleBufferSwitch() API is Enabled 
- if Deselected, Dma_ChannelDoubleBufferSwitch API is Disabled 
*/
#define DMA_CFG_DOUBLE_BUFFER_SWITCH_API                   [!IF "DmaGeneral/DmaDoubleBufferSoftwareSwitchApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaTransferUpdateApi
- if Selected, DMA channel transfer configuration switch API is Enabled 
- if Deselected, DMA channel transfer configuration switch API is Disabled 
*/
#define DMA_CFG_TRANSFER_UPDATE_API                        [!IF "DmaGeneral/DmaTransferUpdateApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaShadowingUpdateApi
- if Selected, DMA channel shadowing operation configuration switch API is Enabled 
- if Deselected, DMA channel shadowing operation configuration switch API is Disabled 
*/
#define DMA_CFG_SHADOWING_UPDATE_API                       [!IF "DmaGeneral/DmaShadowingUpdateApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaTransferUpdateManualApi
- if Selected, DMA channel transfer configuration update manual API is Enabled 
- if Deselected, DMA channel transfer configuration update manual API is Disabled 
*/
#define DMA_CFG_TRANSFER_UPDATE_MANUAL_API                 [!IF "DmaGeneral/DmaTransferUpdateManualApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaLinkedListEnable
- if Selected, DMA linked list functionality is Enabled 
- if Deselected, DMA linked list functionality is Disabled 
*/
#define DMA_CFG_LINKEDLIST_EN                              [!IF "DmaGeneral/DmaLinkedListEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaDaisyChainEnable
- if Selected, DMA daisy chain functionality is Enabled 
- if Deselected, DMA daisy chain functionality is Disabled 
*/
#define DMA_CFG_DAISYCHAIN_EN                              [!IF "DmaGeneral/DmaDaisyChainEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaContinuousModeEnable
- if Selected, DMA continuous functionality is Enabled 
- if Deselected, DMA continuous functionality is Disabled 
*/
#define DMA_CFG_CONTINUOUS_MODE_EN                         [!IF "DmaGeneral/DmaContinuousModeEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]


/*
Configuration: DmaDoubleBufferEnable
- if Selected, DMA channel linked list functionality is Enabled 
- if Deselected, DET is Disabled 
*/
#define DMA_CFG_DOUBLE_BUFFER_EN                           [!IF "DmaGeneral/DmaDoubleBufferEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]


/*
Configuration: DmaShadowingOperationEnable
- if Selected, DMA shadowing operation functionality is Enabled 
- if Deselected, DMA shadowing operation functionality is Disabled 
*/
#define DMA_CFG_SHADOWING_OPERATION_EN                     [!IF "DmaGeneral/DmaShadowingOperationEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]


/*
Configuration: DmaCircularBufferEnable
- if Selected, DMA circular buffer is Enabled 
- if Deselected, DMA circular buffer is Disabled 
*/
#define DMA_CFG_CIRCULAR_BUFFER_EN                         [!IF "DmaGeneral/DmaCircularBufferEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]


/*
Configuration: DmaPatternEnable
- if Selected, DMA pattern match functionality is Enabled 
- if Deselected, DMA pattern match functionality is Disabled 
*/
#define DMA_CFG_PATTERN_MATCH_EN                           [!IF "DmaGeneral/DmaPatternEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: DmaChannelInterruptEnable
- if Selected, DMA interrupt functionality is Enabled 
- if Deselected, DMA interrupt functionality is Disabled 
*/
[!CALL "CG_FindDmaChannelMacroStatus", "NodeName" = "'DmaChannelInterruptEnable'"!][!//
#define DMA_CFG_INTERRUPT_EN                               [!IF "$Var_NodeCfgEnableStatus = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

[!CALL "CG_FindDmaChannelInterruptStatusMacro"!][!//
/* Configuration: DmaChannelTerminalCountInterruptEnable
    Terminal count(TC) interrupt
*/
#define DMA_CFG_TC_INTERRUPT_EN                            [!IF "$Var_TcIntEnableStatus = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/* Configuration: DmaChannelRemainCountInterruptEnable
    Remaining transfer count(RTC) interrupt
*/
#define DMA_CFG_RTC_INTERRUPT_EN                           [!IF "$Var_RtcIntEnableStatus = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/* Configuration: DmaChannelErrorInterruptEnable
    Error interrupt
*/
#define DMA_CFG_ERR_INTERRUPT_EN                           [!IF "$Var_ErrorIntEnableStatus = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/* Configuration: DmaChScbRollbackInterruptEnable
    Source circular buffer rollback interrupt
*/
#define DMA_CFG_SRC_CIRC_BUF_INTERRUPT_EN                  [!IF "$Var_SrcCircBufIntEnableStatus = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/* Configuration: DmaChDcbRollbackInterruptEnable
    Destination circular buffer rollback interrupt
*/
#define DMA_CFG_DEST_CIRC_BUF_INTERRUPT_EN                 [!IF "$Var_DestCircBufIntEnableStatus = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/* Configuration: DmaChPatternMatchedInterruptEnable
    Data pattern matched interrupt
*/
#define DMA_CFG_PATTERN_INTERRUPT_EN                       [!IF "$Var_PatternIntEnableStatus = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* Macro for No transfer configuration in certain channel(s) */
[!CALL "CG_GenNoTransferCfgFlag"!][!//
#define DMA_CFG_CHANNEL_NO_TRANSFER_EN                     [!IF "$Var_NoTransferCfgFlg = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

[!CALL "CG_MultiConfigTypeAndMultiConfigEnableStatus"!][!//
/* Number of transfer or LLI multiple configuration sets
Configuration: DmaChTransferConfig and DmaChLinkedListItemConfig */
#define DMA_CFG_MULTI_TRANSFER_NUM                         ([!"num:i($Var_TransferMultiConfigTotal)"!]U)
[!INDENT "0"!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "CoreUsedForDmaChannelFlg" = "num:i(0)"!][!//
    [!IF "$Var_CoreIdx = num:i(0)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_TransferMultiConfigCore0)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_TransferMultiConfigCore1)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_TransferMultiConfigCore2)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_TransferMultiConfigCore3)"!][!//
    [!ENDIF!][!//
/* Number of transfer or LLI multiple configuration sets allocated to Core[!"num:i($Var_CoreIdx)"!] */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_TRANSFER_NUM_CORE[!"num:i($Var_CoreIdx)"!]                         ([!"num:i($CoreUsedForDmaChannelFlg)"!]U)
[!ENDFOR!][!//
[!ENDINDENT!][!//

/* Number of shadowing multiple configuration sets
Configuration: DmaChShadowConfig */
#define DMA_CFG_MULTI_SHADOWING_NUM                        ([!"num:i($Var_ShadowingMultiConfigTotal)"!]U)
[!INDENT "0"!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "CoreUsedForDmaChannelFlg" = "num:i(0)"!][!//
    [!IF "$Var_CoreIdx = num:i(0)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_ShadowingMultiConfigCore0)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_ShadowingMultiConfigCore1)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_ShadowingMultiConfigCore2)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_ShadowingMultiConfigCore3)"!][!//
    [!ENDIF!][!//
/* Number of shadowing multiple configuration sets allocated to Core[!"num:i($Var_CoreIdx)"!] */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_MULTI_SHADOWING_NUM_CORE[!"num:i($Var_CoreIdx)"!]                         ([!"num:i($CoreUsedForDmaChannelFlg)"!]U)
[!ENDFOR!][!//
[!ENDINDENT!][!//

[!CALL "CG_DaisyChainCoreMapInfo"!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "CoreUsedForDmaChannelFlg" = "num:i(0)"!][!//
    [!IF "$Var_CoreIdx = num:i(0)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_DaisyChainNumCore0)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_DaisyChainNumCore1)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_DaisyChainNumCore2)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($Var_DaisyChainNumCore3)"!][!//
    [!ENDIF!][!//
/* Number of daisy chain of core[!"num:i($Var_CoreIdx)"!] */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_DAISY_CHAIN_NUM_CORE[!"num:i($Var_CoreIdx)"!]                         ([!"num:i($CoreUsedForDmaChannelFlg)"!]U)
[!ENDFOR!][!//

[!INDENT "0"!][!//
[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "CoreUsedForDmaChannelFlg" = "num:i(0)"!][!//
    [!IF "$Var_CoreIdx = num:i(0)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($DmaChannelMappedCore0)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(1)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($DmaChannelMappedCore1)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(2)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($DmaChannelMappedCore2)"!][!//
    [!ELSEIF "$Var_CoreIdx = num:i(3)"!][!//
        [!VAR "CoreUsedForDmaChannelFlg" = "num:i($DmaChannelMappedCore3)"!][!//
    [!ENDIF!][!//
/* Number of channels allocated to Core[!"num:i($Var_CoreIdx)"!] */
#define DMA_CFG_MAX_CHANNELS_CORE[!"num:i($Var_CoreIdx)"!]                         ([!"num:i($CoreUsedForDmaChannelFlg)"!]U)
[!ENDFOR!][!//
/* Total number of channels */
#define DMA_CFG_MAX_CHANNELS                               ([!"num:i(count(DmaConfigSet/DmaChannel/*))"!]U)
[!ENDINDENT!][!//

/* The number of all HW units */
#define DMA_MAX_HWUNIT_COUNT                               ([!"num:i(ecu:get('Dma.TotalHwUnit'))"!]U)

[!INDENT "0"!][!//
    [!FOR "Var_HwUnitCnt" = "num:i(1)" TO "num:i(count(ecu:list('Dma.HwUnitList')))"!][!//
        [!VAR "Var_HwUnitName" = "ecu:list('Dma.HwUnitList')[num:i($Var_HwUnitCnt)]"!][!//
        [!VAR "Var_HwUnitId" = "text:split($Var_HwUnitName, 'DMA')[1]"!][!//
/* ID of DMA HwUnit[!"num:i($Var_HwUnitCnt)"!] */
#define DMA_HWUNIT_[!"$Var_HwUnitName"!]                                    ([!"num:i($Var_HwUnitId)"!]U)
    [!ENDFOR!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
    [!FOR "Var_HwUnitCnt" = "num:i(1)" TO "num:i(count(ecu:list('Dma.HwUnitList')))"!][!//
        [!VAR "Var_HwUnitName" = "ecu:list('Dma.HwUnitList')[num:i($Var_HwUnitCnt)]"!][!//
/* IDs of physical channel in [!"$Var_HwUnitName"!] */
        [!VAR "Var_HwUnitId" = "text:split($Var_HwUnitName, 'DMA')[1]"!][!//
        [!FOR "Var_ChannelID" = "num:i(0)" TO "num:i(ecu:get(concat('Dma.ChannelNumDma', num:i($Var_HwUnitId))) - 1)"!][!//
/* ID of physical channel[!"num:i($Var_ChannelID)"!] */
#define DMA_[!"$Var_HwUnitName"!]_PHYCHANNEL[!"num:i($Var_ChannelID)"!]                               ([!"num:i($Var_ChannelID)"!]U)
        [!ENDFOR!][!//

    [!ENDFOR!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Macro definition of channel interrupt enable                           **
****************************************************************************************************/
[!CALL "CG_GeneDmaChannelInterruptEnableMacro"!][!//

/****************************************************************************************************
**                          Macro definition of request ID                                         **
****************************************************************************************************/
[!CALL "CG_GeneDmaChannelRequestMacro"!][!//

/****************************************************************************************************
**                          Macro definition of transfer ID                                        **
****************************************************************************************************/
[!CALL "CG_GeneDmaLogicalTransferID"!][!//

/****************************************************************************************************
**                          Macro definition of shadow operation                                   **
****************************************************************************************************/
[!CALL "CG_GeneDmaLogicalShadowID"!][!//

/****************************************************************************************************
**                          Macro definition of logical channel ID                                 **
****************************************************************************************************/
[!CALL "CG_GeneDmaLogicalChannelID"!][!//

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
[!ENDSELECT!][!//
#endif  /* DMA_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


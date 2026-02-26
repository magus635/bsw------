[!NOCODE!][!//
/****************************************************************************************************
* 
****************************************************************************************************/
/****************************************************************************************************
*   FileName             : Dma_Cfg_Common.m
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

[!IF "not(var:defined('DMA_CFG_COMMON_M'))"!][!//
[!VAR "DMA_CFG_COMMON_M" = "'true'"!][!//

[!/* Macro to find the core to which the DMA channel is mapped */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = ""!][!//
    [!VAR "ModuleName" = "'DMA'"!][!//
    [!VAR "DmaChannelMappedCoreId" = "num:i(0)"!][!//
    [!VAR "DmaChannelMappedFlag" = "'false'"!][!//
    [!SELECT "as:modconf('Resource')[1]"!][!//
    [!LOOP "ResourceCoreConfigSet/ResourceCoreConfig/*"!][!//
        [!VAR "Resource_CoreId" = "./ResourceCoreId"!][!//
        [!VAR "Resource_CoreEnable" = "./ResourceCoreEnable"!][!//
        [!IF "$Resource_CoreEnable = 'true'"!][!//
            [!LOOP "ResourceAllocation/*"!][!//
                [!IF "./ResourceModule = $ModuleName"!][!//
                    [!IF "node:refvalid(./ResourceModuleRef) = 'true'"!][!//
                        [!VAR "ModuleIndex" = "num:i(count(text:split(./ResourceModuleRef, '/')))"!][!//
                        [!VAR "Resource_ModuleName" = "text:split(./ResourceModuleRef, '/')[num:i($ModuleIndex)]"!][!//
                        [!IF "$DmaChannelName = $Resource_ModuleName"!][!//
                            [!VAR "DmaChannelMappedCoreId" = "num:i(text:split($Resource_CoreId, 'CORE')[1])"!][!//
                            [!VAR "DmaChannelMappedFlag" = "'true'"!][!//
                            [!BREAK!][!//
                        [!ENDIF!][!//
                    [!ELSE!][!//
                        [!ERROR!][!//
                            ERROR: Invalid resource allocation done in [!"$Resource_CoreId"!] for [!"$ModuleName"!] module:[!"node:path(.)"!][!//
                        [!ENDERROR!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
    [!ENDSELECT!][!//
    [!IF "$DmaChannelMappedFlag = 'false'"!][!//
        [!/* If not allocated the Adc HwUnit to any core then will default allocate it to core0 */!][!//
        [!VAR "DmaChannelMappedCoreId" = "num:i(0)"!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to find which core used for Dma channel */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindTotalNumDmaChannelMappedToCorex"!][!//
    [!VAR "DmaChannelMappedCore0" = "num:i(0)"!][!//
    [!VAR "DmaChannelMappedCore1" = "num:i(0)"!][!//
    [!VAR "DmaChannelMappedCore2" = "num:i(0)"!][!//
    [!VAR "DmaChannelMappedCore3" = "num:i(0)"!][!//
    [!LOOP "DmaConfigSet/DmaChannel/*"!][!//
        [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName"="node:name(.)"!][!//
        [!IF "num:i($DmaChannelMappedCoreId) = num:i(0)"!][!//
            [!VAR "DmaChannelMappedCore0" = "num:i($DmaChannelMappedCore0 + 1)"!][!//
        [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(1)"!][!//
            [!VAR "DmaChannelMappedCore1" = "num:i($DmaChannelMappedCore1 + 1)"!][!//
        [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(2)"!][!//
            [!VAR "DmaChannelMappedCore2" = "num:i($DmaChannelMappedCore2 + 1)"!][!//
        [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(3)"!][!//
            [!VAR "DmaChannelMappedCore3" = "num:i($DmaChannelMappedCore3 + 1)"!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!CALL "CG_FindTotalNumDmaChannelMappedToCorex"!][!//

[!/* Macro to geneate the C-macro */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindDmaChannelMacroStatus",  "NodeName" = ""!][!//
    [!SELECT "as:modconf('Dma')[1]/DmaConfigSet"!][!//
        [!VAR "Var_NodeCfgEnableStatus" = "'false'"!][!//
        [!LOOP "DmaChannel/*"!][!//
            [!/* For loop all node in current channel */!][!//
            [!FOR "VAR_NodeNum" = "num:i(1)" TO "num:i(count(*))"!][!//
                [!IF "node:name(./*[position() = $VAR_NodeNum]) = $NodeName"!][!//
                    [!IF "node:value(./*[position() = $VAR_NodeNum]) = 'true'"!][!//
                        [!VAR "Var_NodeCfgEnableStatus" = "'true'"!][!//
                    [!ENDIF!][!//
                    [!/* Exit FOR loop when node is found */!][!//
                    [!BREAK!][!//
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!IF "$Var_NodeCfgEnableStatus = 'true'"!][!//
                [!BREAK!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* If no transfer configuraiont in certain DMA channel */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GenNoTransferCfgFlag"!][!//
    [!SELECT "as:modconf('Dma')[1]/DmaConfigSet"!][!//
        [!VAR "Var_NoTransferCfgFlg" = "'false'"!][!//
        [!LOOP "node:order(./DmaChannel/*, './DmaChannelId')"!][!//
            [!IF "num:i(count(./DmaChTransferConfig/*)) = num:i(0)"!][!//
                [!VAR "Var_NoTransferCfgFlg" = "'true'"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the interrupt enable status c-style macro */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_MultiConfigTypeAndMultiConfigEnableStatus"!][!//
    [!SELECT "as:modconf('Dma')[1]/DmaConfigSet"!][!//
        [!VAR "Var_TransferMultiConfigTotal" = "num:i(0)"!][!//
        [!VAR "Var_ShadowingMultiConfigTotal" = "num:i(0)"!][!//
        [!VAR "Var_TransferMultiConfigCore0" = "num:i(0)"!][!//
        [!VAR "Var_TransferMultiConfigCore1" = "num:i(0)"!][!//
        [!VAR "Var_TransferMultiConfigCore2" = "num:i(0)"!][!//
        [!VAR "Var_TransferMultiConfigCore3" = "num:i(0)"!][!//
        [!VAR "Var_ShadowingMultiConfigCore0" = "num:i(0)"!][!//
        [!VAR "Var_ShadowingMultiConfigCore1" = "num:i(0)"!][!//
        [!VAR "Var_ShadowingMultiConfigCore2" = "num:i(0)"!][!//
        [!VAR "Var_ShadowingMultiConfigCore3" = "num:i(0)"!][!//
        [!LOOP "./DmaChannel/*"!][!//
            [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(.)"!][!//
            [!IF "num:i(count(./DmaChTransferConfig/*)) > num:i(1)"!][!//
                [!IF "num:i($DmaChannelMappedCoreId) = num:i(0)"!][!//
                    [!VAR "Var_TransferMultiConfigCore0" = "num:i($Var_TransferMultiConfigCore0 + 1)"!][!//
                [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(1)"!][!//
                    [!VAR "Var_TransferMultiConfigCore1" = "num:i($Var_TransferMultiConfigCore1 + 1)"!][!//
                [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(2)"!][!//
                    [!VAR "Var_TransferMultiConfigCore2" = "num:i($Var_TransferMultiConfigCore2 + 1)"!][!//
                [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(3)"!][!//
                    [!VAR "Var_TransferMultiConfigCore3" = "num:i($Var_TransferMultiConfigCore3 + 1)"!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!//
            [!IF "as:modconf('Dma')[1]/DmaGeneral/DmaShadowingOperationEnable = 'true'"!][!//
                [!IF "node:exists(./DmaChShadowConfig) and (num:i(count(./DmaChShadowConfig/*)) > num:i(1))"!][!//
                    [!IF "num:i($DmaChannelMappedCoreId) = num:i(0)"!][!//
                        [!VAR "Var_ShadowingMultiConfigCore0" = "num:i($Var_ShadowingMultiConfigCore0 + 1)"!][!//
                    [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(1)"!][!//
                        [!VAR "Var_ShadowingMultiConfigCore1" = "num:i($Var_ShadowingMultiConfigCore1 + 1)"!][!//
                    [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(2)"!][!//
                        [!VAR "Var_ShadowingMultiConfigCore2" = "num:i($Var_ShadowingMultiConfigCore2 + 1)"!][!//
                    [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(3)"!][!//
                        [!VAR "Var_ShadowingMultiConfigCore3" = "num:i($Var_ShadowingMultiConfigCore3 + 1)"!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!//
        [!VAR "Var_TransferMultiConfigTotal" = "num:i($Var_TransferMultiConfigCore0 + $Var_TransferMultiConfigCore1 + $Var_TransferMultiConfigCore2 + $Var_TransferMultiConfigCore3)"!][!//
        [!//
        [!IF "as:modconf('Dma')[1]/DmaGeneral/DmaShadowingOperationEnable = 'true'"!][!//
            [!VAR "Var_ShadowingMultiConfigTotal" = "num:i($Var_ShadowingMultiConfigCore0 + $Var_ShadowingMultiConfigCore1 + $Var_ShadowingMultiConfigCore2 + $Var_ShadowingMultiConfigCore3)"!][!//
        [!ENDIF!][!//
    [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the interrupt enable status c-style macro */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_DaisyChainCoreMapInfo"!][!//
    [!VAR "Var_DaisyChainNumCore0" = "num:i(0)"!][!//
    [!VAR "Var_DaisyChainNumCore1" = "num:i(0)"!][!//
    [!VAR "Var_DaisyChainNumCore2" = "num:i(0)"!][!//
    [!VAR "Var_DaisyChainNumCore3" = "num:i(0)"!][!//
    [!IF "as:modconf('Dma')[1]/DmaGeneral/DmaDaisyChainEnable = 'true'"!][!//
        [!LOOP "as:modconf('Dma')[1]/DmaConfigSet/DmaDaisyChain/*"!][!//
            [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(node:ref(./DmaDaisyChainAssignment/*[1]))"!][!//
            [!VAR "Var_FirstChannelCoreId" = "num:i($DmaChannelMappedCoreId)"!][!//
            [!LOOP "./DmaDaisyChainAssignment/*"!][!//
                [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(node:ref(.))"!][!//
                [!VAR "Var_CurrChannelCoreId" = "num:i($DmaChannelMappedCoreId)"!][!//
                [!IF "num:i($Var_FirstChannelCoreId) != num:i($Var_CurrChannelCoreId)"!][!//
                    [!ERROR!][!//
                        255-1000-ERROR: All members of daisy chain shall be in same core of [!"node:name(../../.)"!].
                    [!ENDERROR!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!//
            [!IF "num:i($Var_FirstChannelCoreId) = num:i(0)"!][!//
                [!VAR "Var_DaisyChainNumCore0" = "num:i($Var_DaisyChainNumCore0 + 1)"!][!//
            [!ELSEIF "num:i($Var_FirstChannelCoreId) = num:i(1)"!][!//
                [!VAR "Var_DaisyChainNumCore1" = "num:i($Var_DaisyChainNumCore1 + 1)"!][!//
            [!ELSEIF "num:i($Var_FirstChannelCoreId) = num:i(2)"!][!//
                [!VAR "Var_DaisyChainNumCore2" = "num:i($Var_DaisyChainNumCore2 + 1)"!][!//
            [!ELSEIF "num:i($Var_FirstChannelCoreId) = num:i(3)"!][!//
                [!VAR "Var_DaisyChainNumCore3" = "num:i($Var_DaisyChainNumCore3 + 1)"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the interrupt enable status c-style macro */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_FindDmaChannelInterruptStatusMacro"!][!//
    [!SELECT "as:modconf('Dma')[1]/DmaConfigSet"!][!//
        [!VAR "Var_TcIntEnableStatus" = "'false'"!][!//
        [!/* Rtc: Remaining transfer count */!][!//
        [!VAR "Var_RtcIntEnableStatus" = "'false'"!][!//
        [!VAR "Var_ErrorIntEnableStatus" = "'false'"!][!//
        [!VAR "Var_SrcCircBufIntEnableStatus" = "'false'"!][!//
        [!VAR "Var_DestCircBufIntEnableStatus" = "'false'"!][!//
        [!VAR "Var_PatternIntEnableStatus" = "'false'"!][!//
        [!LOOP "DmaChannel/*"!][!//
            [!IF "./DmaChannelInterruptEnable = 'true'"!][!//
                [!IF "$Var_ErrorIntEnableStatus = 'false'"!][!//
                    [!VAR "Var_ErrorIntEnableStatus" = "./DmaChannelInterruptConfig/DmaChannelErrorInterruptEnable"!][!//
                [!ENDIF!][!//
                [!IF "$Var_TcIntEnableStatus = 'false'"!][!//
                    [!VAR "Var_TcIntEnableStatus" = "./DmaChannelInterruptConfig/DmaChannelTerminalCountInterruptEnable"!][!//
                [!ENDIF!][!//
                [!IF "$Var_RtcIntEnableStatus = 'false'"!][!//
                    [!VAR "Var_RtcIntEnableStatus" = "./DmaChannelInterruptConfig/DmaChannelRemainCountInterruptEnable"!][!//
                [!ENDIF!][!//
                [!IF "(as:modconf('Dma')[1]/DmaGeneral/DmaCircularBufferEnable = 'true') and (./DmaChannelCircularBufferEnable = 'true')"!][!//
                    [!IF "$Var_SrcCircBufIntEnableStatus = 'false'"!][!//
                        [!IF "node:exists(./DmaChannelInterruptConfig/DmaChScbRollbackInterruptEnable)"!][!//
                            [!VAR "Var_SrcCircBufIntEnableStatus" = "./DmaChannelInterruptConfig/DmaChScbRollbackInterruptEnable"!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!IF "$Var_DestCircBufIntEnableStatus = 'false'"!][!//
                        [!IF "node:exists(./DmaChannelInterruptConfig/DmaChDcbRollbackInterruptEnable)"!][!//
                            [!VAR "Var_DestCircBufIntEnableStatus" = "./DmaChannelInterruptConfig/DmaChDcbRollbackInterruptEnable"!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
                [!IF "(as:modconf('Dma')[1]/DmaGeneral/DmaPatternEnable = 'true') and (./DmaChannelPatternEnable = 'true')"!][!//
                    [!IF "$Var_PatternIntEnableStatus = 'false'"!][!//
                        [!IF "node:exists(./DmaChannelInterruptConfig/DmaChPatternMatchedInterruptEnable)"!][!//
                            [!VAR "Var_PatternIntEnableStatus" = "./DmaChannelInterruptConfig/DmaChPatternMatchedInterruptEnable"!][!//
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!//
            [!IF "($Var_TcIntEnableStatus = 'true')"!][!//
                [!IF "($Var_RtcIntEnableStatus = 'true')"!][!//
                    [!IF "($Var_ErrorIntEnableStatus = 'true')"!][!//
                            [!IF "($Var_SrcCircBufIntEnableStatus = 'true') and ($Var_DestCircBufIntEnableStatus = 'true')"!][!//
                                [!IF "($Var_PatternIntEnableStatus = 'true')"!][!//
                                    [!BREAK!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDSELECT!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the interrupt enable status c-style macro */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_DoubleBufferNotificationExists"!][!//
    [!VAR "Var_DoubleBufferNotificationFlag" = "'false'"!][!//
    [!IF "as:modconf('Dma')[1]/DmaGeneral/DmaDoubleBufferEnable = 'true'"!][!//
        [!LOOP "as:modconf('Dma')[1]/DmaConfigSet/DmaDoubleBuffer/*"!][!//
            [!IF "node:exists(./DmaDoubleBufferFrozenNotification) and (./DmaDoubleBufferFrozenNotification != 'NULL_PTR')"!][!//
                [!VAR "Var_DoubleBufferNotificationFlag" = "'true'"!][!//
                [!BREAK!]
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDIF!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!MACRO "CG_GetBitsUsedDmaHwUnitNum"!][!//
    [!VAR "Var_UsedHwUnitCntBits" = "num:i(0)"!][!//
    [!LOOP "DmaConfigSet/DmaChannel/*"!][!//
        [!VAR "Var_UsedHwUnitCntBits" = "bit:or($Var_UsedHwUnitCntBits, bit:shl(1, text:split(./DmaChannelHwUnitAllocation, 'DMA')[1]))"!][!//
    [!ENDLOOP!][!//
    [!//
    [!VAR "Var_CfgUsedDmaHwUnitNum" = "num:i(0)"!][!//
    [!FOR "Var_HwUnitCnt" = "num:i(1)" TO "num:i(count(ecu:list('Dma.HwUnitList')))"!][!//
        [!VAR "Var_HwUnitName" = "ecu:list('Dma.HwUnitList')[num:i($Var_HwUnitCnt)]"!][!//
        [!VAR "Var_HwUnitId" = "text:split($Var_HwUnitName, 'DMA')[1]"!][!//
        [!IF "num:i(bit:and($Var_UsedHwUnitCntBits, bit:shl(1, $Var_HwUnitId))) != num:i(0)"!][!//
            [!VAR "Var_CfgUsedDmaHwUnitNum" = "num:i($Var_CfgUsedDmaHwUnitNum + 1)"!][!//
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the logical channel ID */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDmaLogicalChannelID"!][!//
    [!LOOP "node:order(as:modconf('Dma')[1]/DmaConfigSet/DmaChannel/*, './DmaChannelId')"!][!//
/* Channel ID[!"./DmaChannelId"!]([!"node:name(.)"!]): Physical channel[!"num:i(./DmaPhyChannel)"!] in [!"./DmaChannelHwUnitAllocation"!] */
#ifndef DmaConf_DmaChannel_[!"node:name(.)"!]
#define DmaConf_DmaChannel_[!"node:name(.)"!]                      ((Dma_ChannelType)[!"./DmaChannelId"!])
#endif /* DmaConf_DmaChannel_[!"node:name(.)"!] */

    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the logical channel transfer ID */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDmaLogicalTransferID"!][!//
    [!LOOP "node:order(as:modconf('Dma')[1]/DmaConfigSet/DmaChannel/*, './DmaChannelId')"!][!//
        [!IF "node:exists(./DmaChTransferConfig)"!][!//
            [!LOOP "node:order(./DmaChTransferConfig/*, './DmaTransferId ')"!][!//
/* Transfer ID[!"../../DmaTransferId "!]([!"node:name(../../.)"!]) in Channel ID[!"../../DmaChannelId"!]([!"node:name(../../.)"!]): Physical channel[!"num:i(../../DmaPhyChannel)"!] in [!"../../DmaChannelHwUnitAllocation"!] */
#ifndef DmaConf_DmaChTransferConfig_[!"node:name(.)"!]
#define DmaConf_DmaChTransferConfig_[!"node:name(.)"!]             ((Dma_TransferType)[!"./DmaTransferId "!]U)
#endif /* DmaConf_DmaChTransferConfig_[!"node:name(.)"!] */
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the logical channel shadow operation ID */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDmaLogicalShadowID"!][!//
    [!LOOP "node:order(as:modconf('Dma')[1]/DmaConfigSet/DmaChannel/*, './DmaChannelId')"!][!//
        [!IF "node:exists(./DmaChShadowConfig)"!][!//
            [!LOOP "node:order(./DmaChShadowConfig/*, './DmaChShadowId')"!][!//
/* Shadowing operation ID[!"../../DmaChShadowId"!]([!"node:name(../../.)"!]) in Channel ID[!"../../DmaChannelId"!]([!"node:name(../../.)"!]): Physical channel[!"num:i(../../DmaPhyChannel)"!] in [!"../../DmaChannelHwUnitAllocation"!] */
#ifndef DmaConf_DmaChShadowConfig_[!"node:name(.)"!]
#define DmaConf_DmaChShadowConfig_[!"node:name(.)"!]              ((Dma_ShadowingType)[!"./DmaChShadowId"!]U)
#endif /* DmaConf_DmaChShadowConfig_[!"node:name(.)"!] */
            [!ENDLOOP!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the channel interrupt enable C-style macro */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDmaChannelInterruptEnableMacro"!][!//
    [!LOOP "node:order(as:modconf('Dma')[1]/DmaConfigSet/DmaChannel/*, './DmaChannelId')"!][!//
        [!IF "node:value(./DmaChannelInterruptEnable) = 'true'"!][!//
/* Channel ID[!"./DmaChannelId"!]([!"node:name(.)"!]): Physical channel[!"num:i(./DmaPhyChannel)"!] in [!"./DmaChannelHwUnitAllocation"!] */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_[!"./DmaChannelHwUnitAllocation"!]_CHANNEL[!"./DmaPhyChannel"!]_INT_EN                       (STD_ON)
/* Termainal count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_[!"./DmaChannelHwUnitAllocation"!]_CHANNEL[!"./DmaPhyChannel"!]_TC_INT_EN                    [!//
            [!IF "./DmaChannelInterruptConfig/DmaChannelTerminalCountInterruptEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
            [!//
/* Remaining transfer count interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_[!"./DmaChannelHwUnitAllocation"!]_CHANNEL[!"./DmaPhyChannel"!]_RTC_INT_EN                   [!//
            [!IF "./DmaChannelInterruptConfig/DmaChannelRemainCountInterruptEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
            [!//
/* Error interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_[!"./DmaChannelHwUnitAllocation"!]_CHANNEL[!"./DmaPhyChannel"!]_ERROR_INT_EN                 [!//
            [!IF "./DmaChannelInterruptConfig/DmaChannelErrorInterruptEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
            [!//
/* Source circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_[!"./DmaChannelHwUnitAllocation"!]_CHANNEL[!"./DmaPhyChannel"!]_SRC_CB_INT_EN                [!//
            [!IF "./DmaChannelInterruptConfig/DmaChScbRollbackInterruptEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
            [!//
/* Destination circular buffer rollback interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_[!"./DmaChannelHwUnitAllocation"!]_CHANNEL[!"./DmaPhyChannel"!]_DEST_CB_INT_EN               [!//
            [!IF "./DmaChannelInterruptConfig/DmaChDcbRollbackInterruptEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
            [!//
/* Data pattern matched interrupt enabled */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_[!"./DmaChannelHwUnitAllocation"!]_CHANNEL[!"./DmaPhyChannel"!]_PATTERN_INT_EN               [!//
            [!IF "./DmaChannelInterruptConfig/DmaChPatternMatchedInterruptEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
            [!/* Line feed */!]
        [!ELSE!][!//
        /* Channel ID[!"./DmaChannelId"!]([!"node:name(.)"!]): Physical channel[!"num:i(./DmaPhyChannel)"!] in [!"./DmaChannelHwUnitAllocation"!] */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_CFG_[!"./DmaChannelHwUnitAllocation"!]_CHANNEL[!"./DmaPhyChannel"!]_INT_EN                       (STD_OFF)
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!/* Macro to geneate the C-Style macro of DMA request */!][!//
[!INDENT "0"!][!//
[!MACRO "CG_GeneDmaChannelRequestMacro"!][!//
    [!FOR "Var_HwUnitCnt" = "num:i(1)" TO "num:i(count(ecu:list('Dma.HwUnitList')))"!][!//
        [!VAR "Var_HwUnitId" = "text:split(ecu:list('Dma.HwUnitList')[num:i($Var_HwUnitCnt)], 'DMA')[1]"!][!//
        [!FOR "Var_DmaChannelReqId" = "num:i(1)" TO "num:i(count(ecu:list(concat('Dma.Request.Peripheral.Dma', num:i($Var_HwUnitId)))))"!][!//
            [!VAR "Var_DmaChannelRequestItem" = "ecu:list(concat('Dma.Request.Peripheral.Dma', num:i($Var_HwUnitId)))[num:i($Var_DmaChannelReqId)]"!][!//
            [!VAR "Var_DmaChannelRequestItem" = "text:split($Var_DmaChannelRequestItem, 'DMA_')[1]"!][!//
            [!VAR "Var_RequestId" = "text:split(text:split($Var_DmaChannelRequestItem, '_')[1], 'REQUEST')[1]"!][!//
/* DMA[!"num:i($Var_HwUnitId)"!] local request: "[!"$Var_DmaChannelRequestItem"!]" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_DMA[!"num:i($Var_HwUnitId)"!]_[!"$Var_DmaChannelRequestItem"!]                  [!//
             ([!"$Var_RequestId"!]U)
        [!ENDFOR!][!//
        [!/* Line feed */!]
    [!ENDFOR!][!//
    [!/* Line feed */!]
    [!FOR "Var_DmaGlobalReqMuxId" = "num:i(1)" TO "num:i(count(ecu:list('Dma.Request.Peripheral.MUX')))"!][!//
        [!VAR "Var_DmaGlobalRequestItem" = "ecu:list('Dma.Request.Peripheral.MUX')[num:i($Var_DmaGlobalReqMuxId)]"!][!//
        [!VAR "Var_DmaGlobalRequestItem" = "text:split($Var_DmaGlobalRequestItem, 'DMA_')[1]"!][!//
        [!VAR "Var_RequestId" = "text:split(text:split($Var_DmaGlobalRequestItem, '_')[1], 'REQUEST')[1]"!][!//
/* DMA global request of multiplexer: "[!"$Var_DmaGlobalRequestItem"!]" */
/* #Violation: Dma_Cfg_h_REF_1*/
#define DMA_MUX_GLOBAL_[!"$Var_DmaGlobalRequestItem"!]                  ([!"$Var_RequestId"!]U)
    [!ENDFOR!][!//
[!ENDMACRO!][!//
[!ENDINDENT!][!//

[!ENDIF!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Dma_PBCfg.c
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
*#Dma_PBcfg_c_REF_1:MISRAC2012-Rule-11.4;
* Justification: The register must load the buffer's address.
*
*#Dma_PBcfg_c_REF_2:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain
*   parts of the driver must be placed.
*
*#Dma_PBcfg_c_REF_3:CertC-DCL06-C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*#Dma_PBcfg_c_REF_4:CWE-547;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
*/

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Dma_Cfg_Common.m"!][!//
[!ENDNOCODE!][!//
[!//
#include "Dma.h"
#include "Mcall.h"
/* Include external header files to call notification functions */
[!INDENT "0"!][!//
    [!LOOP "DmaConfigSet/DmaUserHeaderFile/*"!][!//
        [!IF "(node:value(.) != '')"!][!//
            #include "[!"node:value(.)"!]"
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDINDENT!][!//

[!NOCODE!][!//
    [!VAR "Var_DmaDetEnableFlag" = "DmaGeneral/DmaDevErrorDetect"!][!//
    [!VAR "Var_DmaDaisyChainEnFlag" = "DmaGeneral/DmaDaisyChainEnable"!][!//
    [!VAR "Var_DmaContinuousModeEnFlag" = "DmaGeneral/DmaContinuousModeEnable"!][!//
    [!VAR "Var_DmaLinkedListEnFlag" = "DmaGeneral/DmaLinkedListEnable"!][!//
    [!VAR "Var_DmaShadowTransferEnFlag" = "DmaGeneral/DmaShadowingOperationEnable"!][!//
    [!VAR "Var_DmaDoubleBufferEnFlag" = "DmaGeneral/DmaDoubleBufferEnable"!][!//
    [!VAR "Var_DmaCircularBufferEnFlag" = "DmaGeneral/DmaCircularBufferEnable"!][!//
    [!VAR "Var_DmaPatternMatchEnFlag" = "DmaGeneral/DmaPatternEnable"!][!//
    [!CALL "CG_FindDmaChannelMacroStatus", "NodeName" = "'DmaChannelInterruptEnable'"!][!//
    [!VAR "Var_DmaGlobalIntEnFlag" = "$Var_NodeCfgEnableStatus"!][!//
    [!CALL "CG_MultiConfigTypeAndMultiConfigEnableStatus"!][!//
    [!CALL "CG_DaisyChainCoreMapInfo"!][!//
    [!CALL "CG_FindDmaChannelInterruptStatusMacro"!][!//
    [!CALL "CG_GetBitsUsedDmaHwUnitNum"!][!//
    [!CALL "CG_GenNoTransferCfgFlag"!][!//
    [!IF "num:i(variant:size()) != num:i(0)"!][!//
        [!VAR "Var_DmaConfigShortName"="concat('_', variant:name())"!][!//
    [!ELSE!][!//
        [!VAR "Var_DmaConfigShortName"="''"!][!//
    [!ENDIF!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          External Function Declarations                                         **
****************************************************************************************************/
[!INDENT "0"!][!//
    [!LOOP "node:order(DmaConfigSet/DmaChannel/*, './DmaChannelId')"!][!//
        [!IF "node:exists(DmaChannelNotification) and (./DmaChannelNotification != 'NULL_PTR')"!][!//
extern void [!"./DmaChannelNotification"!](Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!IF "DmaGeneral/DmaDoubleBufferEnable = 'true'"!][!//
    [!LOOP "node:order(DmaConfigSet/DmaDoubleBuffer/*, './DmaDoubleBufferId')"!][!//
        [!IF "node:exists(DmaDoubleBufferFrozenNotification) and (./DmaDoubleBufferFrozenNotification != 'NULL_PTR')"!][!//
extern void [!"./DmaDoubleBufferFrozenNotification"!](Dma_ChannelType Channel, Dma_DblFrznStatusType FrozenStatus);
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
[!INDENT "0"!][!//
[!IF "$Var_DmaLinkedListEnFlag = 'true'"!][!//
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
        [!IF "num:i($CoreUsedForDmaChannelFlg) != num:i(0)"!][!//

/* Core[!"num:i($Var_CoreIdx)"!] */
#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE[!"num:i($Var_CoreIdx)"!]_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"
            [!/*Line feed*/!]
            [!LOOP "node:order(as:modconf('Dma')[1]/DmaConfigSet/DmaChannel/*, './DmaChannelId')"!][!//
                [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(.)"!][!//
                [!IF "num:i($DmaChannelMappedCoreId) = num:i($Var_CoreIdx)"!][!//
                    [!IF "node:exists(DmaChannelLinkedListEnable) and (./DmaChannelLinkedListEnable = 'true')"!][!//
                        [!/* Maximum length of linked list configuration parameters */!][!//
                        [!VAR "Var_MaxLengthLli" = "num:i(0)"!][!//
                        [!LOOP "./DmaChLinkedListItemConfig/*"!][!//
                            [!IF "num:i($Var_MaxLengthLli) < num:i(count(./DmaChLinkedListTransferAssignment/*))"!][!//
                                [!VAR "Var_MaxLengthLli" = "num:i(count(./DmaChLinkedListTransferAssignment/*))"!][!//
                            [!ENDIF!][!//
                        [!ENDLOOP!][!//
/* Linked list item buffer of channel [!"./DmaChannelId"!] */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static Dma_LliBufType Dma_Channel[!"./DmaChannelId"!]LliCore[!"num:i($Var_CoreIdx)"!][[!"num:i($Var_MaxLengthLli)"!]];
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!/*Line feed*/!]
#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE[!"num:i($Var_CoreIdx)"!]_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"
        [!ENDIF!][!//
    [!ENDFOR!][!//
[!ENDIF!][!//
[!ENDINDENT!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

[!FOR "Var_CoreIdx" = "num:i(0)" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!INDENT "0"!][!//
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
    [!IF "num:i($CoreUsedForDmaChannelFlg) != num:i(0)"!][!//

        /* Configuration informations which mapped to Core[!"$Var_CoreIdx"!] */
        #define DMA_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"num:i($Var_CoreIdx)"!]_UNSPECIFIED
        /* #Violation: Dma_PBcfg_c_REF_2 */
        #include "Dma_MemMap.h"

        [!LOOP "node:order(DmaConfigSet/DmaChannel/*, './DmaChannelId')"!][!//
            [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(.)"!][!//
            [!IF "num:i($DmaChannelMappedCoreId) = num:i($Var_CoreIdx)"!][!//
                [!VAR "Var_TotalTransferConfigNum" = "num:i(count(./DmaChTransferConfig/*))"!][!//
                [!IF "num:i($Var_TotalTransferConfigNum) > num:i(0)"!][!//
                    /* Basic transfer configuration parameter of channel[!"./DmaChannelId"!]: [!"node:name(.)"!]
                    Configuration: DmaChTransferConfig */
                    static const Dma_TransferConfigType Dma_TransferConfigListChannel[!"./DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!][[!"num:i($Var_TotalTransferConfigNum)"!]] = 
                    {
                        [!VAR "Var_TransferConfigCnt" = "num:i(0)"!][!//
                        [!LOOP "node:order(./DmaChTransferConfig/*, './DmaTransferId')"!][!//
                            [!INDENT "4"!][!//
                            {
                                [!INDENT "8"!][!//
                                [!IF "$Var_DmaDoubleBufferEnFlag = 'true'"!][!//
                                    /* The ID of the double buffer assigned to this transfer */
                                    [!IF "(node:exists(./../../DmaChannelDoubleBufferEnable) and (./../../DmaChannelDoubleBufferEnable = 'true')) and 
                                           (./DmaTransferDoubleBufferEnable = 'true')"!][!//
                                        [!"node:ref(./DmaTransferDoubleBufferAssignment)/DmaDoubleBufferId"!]U,
                                    [!ELSE!][!//
                                        255U,   /* Invalid ID */
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                                [!IF "$Var_DmaCircularBufferEnFlag = 'true'"!][!//
                                    /* The ID of the circular buffer assigned to this transfer */
                                    [!IF "(node:exists(./../../DmaChannelCircularBufferEnable) and (./../../DmaChannelCircularBufferEnable = 'true')) and 
                                           (./DmaTransferCircularBufferEnable = 'true')"!][!//
                                        [!"node:ref(./DmaTransferCircularBufferAssignment)/DmaCircularBufferId"!]U,
                                    [!ELSE!][!//
                                        255U,    /* Invalid ID */
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                                [!IF "$Var_DmaPatternMatchEnFlag = 'true'"!][!//
                                    /* The ID of the pattern assigned to this transfer */
                                    [!IF "(node:exists(./../../DmaChannelPatternEnable) and (./../../DmaChannelPatternEnable = 'true')) and 
                                           (./DmaTransferPatternEnable = 'true')"!][!//
                                        [!"node:ref(./DmaTransferPatternAssignment)/DmaPatternId"!]U,
                                    [!ELSE!][!//
                                        255U,    /* Invalid ID */
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                                [!IF "$Var_DmaLinkedListEnFlag = 'true'"!][!//
                                    /* The ID of the linked list assigned to this transfer */
                                    [!IF "(node:exists(./../../DmaChannelLinkedListEnable) and (./../../DmaChannelLinkedListEnable = 'true')) and 
                                          (./DmaTransferLinkedListEnable = 'true')"!][!//
                                        [!"node:ref(./DmaTransferLinkedListAssignment)/DmaChLinkedListId"!]U,
                                    [!ELSE!][!//
                                        255U,    /* Invalid ID */
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                                [!IF "$Var_RtcIntEnableStatus = 'true'"!][!//
                                    /* Remaining count threshold for trigger the interrupt */
                                    [!IF "node:exists(./DmaTransferRemainingCountThr)"!][!//
                                        [!"./DmaTransferRemainingCountThr"!]U,
                                    [!ELSE!][!//
                                        0U,
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                                {
                                    [!INDENT "12"!][!//
                                    /* Source address configuration */
                                    {
                                        [!INDENT "16"!][!//
                                        /* Source address */
                                        [!IF "./DmaTransferSourceAddress != 'NULL_PTR'"!][!//
                                            /* #Violation: Dma_PBcfg_c_REF_1 */
                                            (uint32)[!"./DmaTransferSourceAddress"!],
                                        [!ELSE!][!//
                                            (uint32)0U,
                                        [!ENDIF!][!//
                                        /* Auto increase or no increase */
                                        DMA_CHANNELADDRESSINCREMENT_[!"text:split(./DmaTransferSourceAddressMovement, 'DMA_ADDRESS_')[1]"!],
                                        /* Burst size */
                                        DMA_CHANNELBURSTSIZE_[!"text:split(./DmaTransferSourceBurstNum, 'DMA_BURST_SIZE_')[1]"!]
                                        [!ENDINDENT!][!//
                                    },
                                    /* Destination address configuration */
                                    {
                                        [!INDENT "16"!][!//
                                        /* Destination address */
                                        [!IF "./DmaTransferDestinationAddress != 'NULL_PTR'"!][!//
                                            /* #Violation: Dma_PBcfg_c_REF_1 */
                                            (uint32)[!"./DmaTransferDestinationAddress"!],
                                        [!ELSE!][!//
                                            (uint32)0U,
                                        [!ENDIF!][!//
                                        /* Auto increase or no increase */
                                        DMA_CHANNELADDRESSINCREMENT_[!"text:split(./DmaTransferDestinationAddressMovement, 'DMA_ADDRESS_')[1]"!],
                                        /* Burst size */
                                        DMA_CHANNELBURSTSIZE_[!"text:split(./DmaTransferDestinationBurstNum, 'DMA_BURST_SIZE_')[1]"!]
                                        [!ENDINDENT!][!//
                                    },
                                    /* Transfer width(unit: bit(s)) */
                                    DMA_CHANNELTRANSFERWIDTH_[!"text:split(./DmaTransferDataWidth, 'DMA_TRANSFER_DATA_')[1]"!],
                                    /* Flow control */
                                    DMA_FLOWCONTROLANDTRANSFERTYPE_[!"./../../DmaChTransferConfigFlowControl"!],
                                    /* Source request configuration */
                                    {
                                        [!INDENT "16"!][!//
                                        [!IF "node:exists(./../../DmaChannelSourceRequestSelect)"!][!//
                                            /* Local request: [!"./../../DmaChannelSourceRequestSelect"!] */
                                            DMA_DMA[!"num:i(text:split(./../../DmaChannelHwUnitAllocation, 'DMA')[1])"!]_[!"text:split(./../../DmaChannelSourceRequestSelect, 'DMA_')[1]"!],
                                            [!IF "node:exists(./../../DmaChannelSourceGlobalRequestMUX)"!][!//
                                                /* Global multiplexer request: [!"./../../DmaChannelSourceGlobalRequestMUX"!] */
                                                DMA_MUX_GLOBAL_[!"text:split(./../../DmaChannelSourceGlobalRequestMUX, 'DMA_')[1]"!]
                                            [!ELSE!][!//
                                                /* Global multiplexer request - None */
                                                0U
                                            [!ENDIF!][!//
                                        [!ELSE!][!//
                                            /* Local request - None */
                                            0U,
                                            /* Global multiplexer request - None */
                                            0U
                                        [!ENDIF!][!//
                                        [!ENDINDENT!][!//
                                    },
                                    /* Destination request configuration */
                                    {
                                        [!INDENT "16"!][!//
                                        [!IF "node:exists(./../../DmaChannelDestinationRequestSelect)"!][!//
                                            /* Local request: [!"./../../DmaChannelDestinationRequestSelect"!] */
                                            DMA_DMA[!"num:i(text:split(./../../DmaChannelHwUnitAllocation, 'DMA')[1])"!]_[!"text:split(./../../DmaChannelDestinationRequestSelect, 'DMA_')[1]"!],
                                            [!IF "node:exists(./../../DmaChannelDestinationGlobalRequestMUX)"!][!//
                                                /* Global multiplexer request: [!"./../../DmaChannelDestinationGlobalRequestMUX"!] */
                                                DMA_MUX_GLOBAL_[!"text:split(./../../DmaChannelDestinationGlobalRequestMUX, 'DMA_')[1]"!]
                                            [!ELSE!][!//
                                                /* Global multiplexer request - None */
                                                0U
                                            [!ENDIF!][!//
                                        [!ELSE!][!//
                                            /* Local request - None */
                                            0U,
                                            /* Global multiplexer request - None */
                                            0U
                                        [!ENDIF!][!//
                                        [!ENDINDENT!][!//
                                    },
                                    /* Number of transfer */
                                    [!"./DmaTransferSize"!]U
                                    [!ENDINDENT!][!//
                                }
                                [!ENDINDENT!][!//
                            }[!//
                            [!IF "num:i($Var_TransferConfigCnt) < num:i($Var_TotalTransferConfigNum - 1)"!][!//
                                ,
                            [!ENDIF!][!//
                            [!VAR "Var_TransferConfigCnt" = "num:i($Var_TransferConfigCnt + 1)"!][!//
                            [!ENDINDENT!][!//
                        [!ENDLOOP!][!//
                        [!/* Line feed */!]
                    };
                    [!/* Line feed */!]
                    [!IF "$Var_DmaLinkedListEnFlag = 'true'"!][!//
                        [!IF "node:exists(./DmaChannelLinkedListEnable) and (./DmaChannelLinkedListEnable = 'true')"!][!//
                            /* Transfer ID assigned to the linked list
                            Configuration: DmaChLinkedListTransferAssignment */
                            [!LOOP "node:order(./DmaChLinkedListItemConfig/*, './DmaChLinkedListId')"!][!//
                                [!VAR "Var_TotalLinkedlistItemNum" = "num:i(count(./DmaChLinkedListTransferAssignment/*))"!][!//
                                /* Linked list ID[!"./DmaChLinkedListId"!] of channel [!"./../../DmaChannelId"!]: "[!"node:name(./../../.)"!]" */
                                /* First element is the total number of linked list items, others point to the transfer ID */
                                /* #Violation: Dma_PBcfg_c_REF_3 */
                                /* #Violation: Dma_PBcfg_c_REF_4 */
                                static const Dma_TransferType Dma_TransfersMapLli[!"@index"!]Channel[!"./../../DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!][[!"num:i($Var_TotalLinkedlistItemNum)"!]] = 
                                {
                                    [!INDENT "4"!][!//
                                    [!VAR "Var_LinkedlistItemCnt" = "num:i(0)"!][!//
                                    /* Transfer IDs */
                                    [!LOOP "./DmaChLinkedListTransferAssignment/*"!][!//
                                        [!"node:ref(.)/DmaTransferId"!]U[!//
                                        [!IF "num:i($Var_LinkedlistItemCnt) < num:i($Var_TotalLinkedlistItemNum - 1)"!][!//
                                            , 
                                        [!ENDIF!][!//
                                        [!VAR "Var_LinkedlistItemCnt" = "num:i($Var_LinkedlistItemCnt + 1)"!][!//
                                    [!ENDLOOP!][!//
                                    [!/* Line feed */!]
                                    [!ENDINDENT!][!//
                                };
                            [!ENDLOOP!][!//

                            [!VAR "Var_TotalLinkedlistNum" = "num:i(count(./DmaChLinkedListItemConfig/*))"!][!//
                            /* Pointer to the linked list mapping information list
                            Configuration: DmaChLinkedListItemConfig */
                            static const Dma_LinkedListMapType Dma_TransfersLli[!"@index"!]Channel[!"./DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!][[!"num:i($Var_TotalLinkedlistNum)"!]] = 
                            {
                                [!INDENT "4"!][!//
                                [!VAR "Var_LinkedlistCnt" = "num:i(0)"!][!//
                                [!LOOP "node:order(./DmaChLinkedListItemConfig/*, './DmaChLinkedListId')"!][!//
                                {
                                    [!INDENT "8"!][!//
                                    /* Total number of this linked list members */
                                    [!"num:i(count(./DmaChLinkedListTransferAssignment/*))"!]U,
                                    /* Pointer to the transfer that linked list is assigned */
                                    &Dma_TransfersMapLli[!"@index"!]Channel[!"./../../DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!][0]
                                    [!ENDINDENT!][!//
                                }[!//
                                    [!IF "num:i($Var_LinkedlistCnt) < num:i($Var_TotalLinkedlistNum - 1)"!][!//
                                        ,
                                    [!ENDIF!][!//
                                    [!VAR "Var_LinkedlistCnt" = "num:i($Var_LinkedlistCnt + 1)"!][!//
                                [!ENDLOOP!][!//
                                [!/* Line feed */!]
                                [!ENDINDENT!][!//
                            };

                            /* Linked list configuration entry of channel[!"./DmaChannelId"!] */
                            static const Dma_ChLinkedListConfigType Dma_LinkedListConfigChannel[!"./DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!] = 
                            {
                                [!INDENT "4"!][!//
                                [!VAR "Var_LinkedlistConfigCnt" = "num:i(0)"!][!//
                                /* Pointer to the linked list item of transfer configuration mapping list */
                                &Dma_TransfersLli[!"@index"!]Channel[!"./DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!][0],
                                /* Pointer to the linked list buffer */
                                &Dma_Channel[!"./DmaChannelId"!]LliCore[!"num:i($Var_CoreIdx)"!][0]
                                [!ENDINDENT!][!//
                            };
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!//
                    [!IF "$Var_DmaShadowTransferEnFlag = 'true'"!][!//
                        [!IF "node:exists(./DmaChannelShadowOperationEnable) and (./DmaChannelShadowOperationEnable = 'true')"!][!//
                        [!/* Line feed */!]
                            [!VAR "Var_TotalShadowConfigNum" = "num:i(count(./DmaChShadowConfig/*))"!][!//
                        /* Shadowing detail configuration parameters of channel[!"./DmaChannelId"!]
                        Configuration: DmaChShadowConfig */
                        /* #Violation: Dma_PBcfg_c_REF_3 */
                        /* #Violation: Dma_PBcfg_c_REF_4 */
                        static const Dma_ShadowingMapType Dma_ShadowingMapChannel[!"./DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!][[!"num:i($Var_TotalShadowConfigNum)"!]] = 
                        {
                            [!INDENT "4"!][!//
                            [!VAR "Var_ShadowConfigCnt" = "num:i(0)"!][!//
                            [!LOOP "node:order(./DmaChShadowConfig/*, './DmaChShadowId')"!][!//
                            /* Shadow operation ID[!"./DmaChShadowId"!] of channel [!"./../../DmaChannelId"!]: "[!"node:name(./../../.)"!]" */
                            {
                                [!INDENT "12"!][!//
                                    /* [!"node:name(node:ref(./DmaChShadowTransferAssignment))"!]: Transfer ID[!"node:ref(./DmaChShadowTransferAssignment)/DmaTransferId"!] */
                                    [!"node:ref(./DmaChShadowTransferAssignment)/DmaTransferId"!]U
                                    [!IF "$Var_DmaLinkedListEnFlag = 'true'"!][!//
                                        [!IF "node:exists(./DmaChShadowLinkedListEnable) and node:exists(./DmaChShadowLinkedListAssignment)"!][!//
                                            /* [!"node:name(node:ref(./DmaChShadowLinkedListAssignment))"!]: Transfer ID[!"node:ref(./DmaChShadowLinkedListAssignment)/DmaChLinkedListId"!] */
                                            ,[!"node:ref(./DmaChShadowLinkedListAssignment)/DmaChLinkedListId"!]U
                                        [!ELSE!][!//
                                            [!IF "num:i($Var_TransferMultiConfigTotal) != 0"!][!//
                                                /*Linked list is not enabled*/
                                                ,0xFFU
                                            [!ENDIF!][!//
                                        [!ENDIF!][!//
                                    [!ENDIF!][!//
                                [!ENDINDENT!][!//
                            }[!//
                            [!IF "num:i($Var_ShadowConfigCnt) < num:i($Var_TotalShadowConfigNum - 1)"!][!//
                                ,
                            [!ENDIF!][!//
                            [!VAR "Var_ShadowConfigCnt" = "num:i($Var_ShadowConfigCnt + 1)"!][!//
                            [!ENDLOOP!][!//
                            [!/*Line feed*/!]
                            [!ENDINDENT!][!//
                        };
                        [!ENDIF!][!//
                    [!ENDIF!][!//
                    [!/* Line feed */!]
                [!ELSE!][!//
                    [!IF "$Var_NoTransferCfgFlg = 'true'"!][!//
                        /* Basic transfer configuration parameter of channel[!"./DmaChannelId"!]: [!"node:name(.)"!]
                        This channel no transfer configuration and this is generated default. */
                        /* #Violation: Dma_PBcfg_c_REF_3 */
                        /* #Violation: Dma_PBcfg_c_REF_4 */
                        static const Dma_TransferConfigType Dma_TransferConfigListChannel[!"./DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!][1U] = 
                        {
                            [!VAR "Var_TransferConfigCnt" = "num:i(0)"!][!//
                            [!INDENT "4"!][!//
                            {
                                [!INDENT "8"!][!//
                                [!IF "$Var_DmaDoubleBufferEnFlag = 'true'"!][!//
                                    255U,   /* Invalid ID */
                                [!ENDIF!][!//
                                [!IF "$Var_DmaCircularBufferEnFlag = 'true'"!][!//
                                    255U,    /* Invalid ID */
                                [!ENDIF!][!//
                                [!IF "$Var_DmaPatternMatchEnFlag = 'true'"!][!//
                                    255U,    /* Invalid ID */
                                [!ENDIF!][!//
                                [!IF "$Var_DmaLinkedListEnFlag = 'true'"!][!//
                                    255U,    /* Invalid ID */
                                [!ENDIF!][!//
                                [!IF "$Var_RtcIntEnableStatus = 'true'"!][!//
                                    0U,     /* No remaining terminal count */
                                [!ENDIF!][!//
                                {
                                    [!INDENT "12"!][!//
                                    /* Source address configuration */
                                    {
                                        [!INDENT "16"!][!//
                                        /* Source address default point to NULL_PTR */
                                        (uint32)0U,
                                        /* No increase */
                                        DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                                        /* Burst size */
                                        DMA_CHANNELBURSTSIZE_1
                                        [!ENDINDENT!][!//
                                    },
                                    /* Destination address configuration */
                                    {
                                        [!INDENT "16"!][!//
                                        /* Destination address default point to NULL_PTR */
                                        (uint32)0U,
                                        /* Auto increase or no increase */
                                        DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                                        /* Burst size */
                                        DMA_CHANNELBURSTSIZE_1
                                        [!ENDINDENT!][!//
                                    },
                                    /* Transfer width(unit: bit(s)) */
                                    DMA_CHANNELTRANSFERWIDTH_8BIT,
                                    /* Flow control */
                                    DMA_FLOWCONTROLANDTRANSFERTYPE_[!"./DmaChTransferConfigFlowControl"!],
                                    /* Source request configuration */
                                    {
                                        [!INDENT "16"!][!//
                                        [!IF "node:exists(./DmaChannelSourceRequestSelect)"!][!//
                                            /* Local request: [!"./DmaChannelSourceRequestSelect"!] */
                                            DMA_DMA[!"num:i(text:split(./DmaChannelHwUnitAllocation, 'DMA')[1])"!]_[!"text:split(./DmaChannelSourceRequestSelect, 'DMA_')[1]"!],
                                            [!IF "node:exists(./DmaChannelSourceGlobalRequestMUX)"!][!//
                                                /* Global multiplexer request: [!"./DmaChannelSourceGlobalRequestMUX"!] */
                                                DMA_MUX_GLOBAL_[!"text:split(./DmaChannelSourceGlobalRequestMUX, 'DMA_')[1]"!]
                                            [!ELSE!][!//
                                                /* Global multiplexer request - None */
                                                0U
                                            [!ENDIF!][!//
                                        [!ELSE!][!//
                                            /* Local request - None */
                                            0U,
                                            /* Global multiplexer request - None */
                                            0U
                                        [!ENDIF!][!//
                                        [!ENDINDENT!][!//
                                    },
                                    /* Destination request configuration */
                                    {
                                        [!INDENT "16"!][!//
                                        [!IF "node:exists(./DmaChannelDestinationRequestSelect)"!][!//
                                            /* Local request: [!"./DmaChannelDestinationRequestSelect"!] */
                                            DMA_DMA[!"num:i(text:split(./DmaChannelHwUnitAllocation, 'DMA')[1])"!]_[!"text:split(./DmaChannelDestinationRequestSelect, 'DMA_')[1]"!],
                                            [!IF "node:exists(./DmaChannelDestinationGlobalRequestMUX)"!][!//
                                                /* Global multiplexer request: [!"./DmaChannelDestinationGlobalRequestMUX"!] */
                                                DMA_MUX_GLOBAL_[!"text:split(./DmaChannelDestinationGlobalRequestMUX, 'DMA_')[1]"!]
                                            [!ELSE!][!//
                                                /* Global multiplexer request - None */
                                                0U
                                            [!ENDIF!][!//
                                        [!ELSE!][!//
                                            /* Local request - None */
                                            0U,
                                            /* Global multiplexer request - None */
                                            0U
                                        [!ENDIF!][!//
                                        [!ENDINDENT!][!//
                                    },
                                    /* Number of transfer */
                                    1U
                                    [!ENDINDENT!][!//
                                }
                                [!ENDINDENT!][!//
                            }[!//
                            [!IF "num:i($Var_TransferConfigCnt) < num:i($Var_TotalTransferConfigNum - 1)"!][!//
                                ,
                            [!ENDIF!][!//
                            [!VAR "Var_TransferConfigCnt" = "num:i($Var_TransferConfigCnt + 1)"!][!//
                            [!ENDINDENT!][!//
                            [!/* Line feed */!]
                        };
                        [!/* Line feed */!]
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//

        /* Detail configuration parameters of all channels in core[!"num:i($Var_CoreIdx)"!] */
        static const Dma_ChConfigType Dma_ChannelConfigCore[!"num:i($Var_CoreIdx)"!][DMA_CFG_MAX_CHANNELS_CORE[!"num:i($Var_CoreIdx)"!]] = 
        {
            [!INDENT "4"!][!//
            [!VAR "Var_CoreChannelIdx" = "num:i(0)"!][!//
            [!LOOP "node:order(DmaConfigSet/DmaChannel/*, './DmaChannelId')"!][!//
                [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(.)"!][!//
                [!IF "num:i($DmaChannelMappedCoreId) = num:i($Var_CoreIdx)"!][!//
                    [!VAR "Var_TotalTransferConfigNum" = "num:i(count(./DmaChTransferConfig/*))"!][!//
                    /* Configuration parameter of [!"./DmaChannelHwUnitAllocation"!] channel[!"./DmaPhyChannel"!] */
                    /* Channel name: [!"node:name(.)"!],  channel ID: [!"./DmaChannelId"!] */
                    {
                    [!INDENT "8"!][!//
                        /* Channel ID */
                        [!"./DmaChannelId"!]U,
                        [!IF "$Var_NoTransferCfgFlg = 'true'"!][!//
                            [!IF "num:i($Var_TotalTransferConfigNum) = num:i(0)"!][!//
                                /* No transfer configurations */
                                FALSE,
                            [!ELSE!][!//
                                /* Transfer configurations exists */
                                TRUE,
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!IF "$Var_DmaDetEnableFlag = 'true'"!][!//
                            [!IF "as:modconf('Dma')[1]/DmaGeneral/DmaDevErrorDetect = 'true'"!][!//
                                /* Total number of transfer configurations */
                                [!"num:i($Var_TotalTransferConfigNum)"!]U,
                                [!IF "$Var_DmaShadowTransferEnFlag = 'true'"!][!//
                                    /* Total number of shadowing operation configurations */
                                    [!IF "num:i($Var_TotalTransferConfigNum) > num:i(0)"!][!//
                                        [!"num:i(count(./DmaChShadowConfig/*))"!]U,
                                    [!ELSE!][!//
                                        0U,
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                                [!IF "$Var_DmaLinkedListEnFlag = 'true'"!][!//
                                    /* Total number of linked list item configurations */
                                    [!IF "num:i($Var_TotalTransferConfigNum) > num:i(0)"!][!//
                                        [!"num:i(count(./DmaChLinkedListItemConfig/*))"!]U,
                                    [!ELSE!][!//
                                        0U,
                                    [!ENDIF!][!//
                                [!ENDIF!][!//
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!IF "$Var_DmaGlobalIntEnFlag = 'true'"!][!//
                            /* Interrupt enable bits */
                            [!IF "./DmaChannelInterruptEnable = 'true'"!][!//
                                [!VAR "Var_NotFirstIntFlag" = "'false'"!][!//
                                [!IF "./DmaChannelInterruptConfig/DmaChannelErrorInterruptEnable = 'true'"!][!//
                                    (uint8)DMA_CH_INT_ERROR[!//
                                    [!VAR "Var_NotFirstIntFlag" = "'true'"!][!//
                                [!ENDIF!][!//
                                [!IF "./DmaChannelInterruptConfig/DmaChannelTerminalCountInterruptEnable = 'true'"!][!//
                                    [!IF "$Var_NotFirstIntFlag = 'true'"!][!//
                                        | \
                                    [!ENDIF!][!//
                                    (uint8)DMA_CH_INT_TC[!//
                                    [!VAR "Var_NotFirstIntFlag" = "'true'"!][!//
                                [!ENDIF!][!//
                                [!IF "./DmaChannelInterruptConfig/DmaChannelRemainCountInterruptEnable = 'true'"!][!//
                                    [!IF "$Var_NotFirstIntFlag = 'true'"!][!//
                                        | \
                                    [!ENDIF!][!//
                                    (uint8)DMA_CH_INT_REMAINING_COUNT[!//
                                    [!VAR "Var_NotFirstIntFlag" = "'true'"!][!//
                                [!ENDIF!][!//
                                [!IF "($Var_DmaCircularBufferEnFlag = 'true') and 
                                      (node:exists(./DmaChannelInterruptConfig/DmaChScbRollbackInterruptEnable) and (./DmaChannelInterruptConfig/DmaChScbRollbackInterruptEnable = 'true'))"!][!//
                                    [!IF "$Var_NotFirstIntFlag = 'true'"!][!//
                                        | \
                                    [!ENDIF!][!//
                                    (uint8)DMA_CH_INT_SCB[!//
                                    [!VAR "Var_NotFirstIntFlag" = "'true'"!][!//
                                [!ENDIF!][!//
                                [!IF "($Var_DmaCircularBufferEnFlag = 'true') and 
                                      ((node:exists(./DmaChannelInterruptConfig/DmaChDcbRollbackInterruptEnable)) and (./DmaChannelInterruptConfig/DmaChDcbRollbackInterruptEnable = 'true'))"!][!//
                                    [!IF "$Var_NotFirstIntFlag = 'true'"!][!//
                                        | \
                                    [!ENDIF!][!//
                                    (uint8)DMA_CH_INT_DCB[!//
                                    [!VAR "Var_NotFirstIntFlag" = "'true'"!][!//
                                [!ENDIF!][!//
                                [!IF "($Var_DmaPatternMatchEnFlag = 'true') and 
                                      (node:exists(./DmaChannelInterruptConfig/DmaChPatternMatchedInterruptEnable) and (./DmaChannelInterruptConfig/DmaChPatternMatchedInterruptEnable = 'true'))"!][!//
                                    [!IF "$Var_NotFirstIntFlag = 'true'"!][!//
                                        | \
                                    [!ENDIF!][!//
                                    (uint8)DMA_CH_INT_PATTERN[!//
                                    [!VAR "Var_NotFirstIntFlag" = "'true'"!][!//
                                [!ENDIF!][!//
                                [!IF "$Var_NotFirstIntFlag = 'true'"!][!//
                                    ,
                                [!ENDIF!][!//
                            [!ELSE!][!//
                                0U,
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!/* Continuous Mode */!][!//
                        [!IF "$Var_DmaContinuousModeEnFlag = 'true'"!][!//
                            [!IF "node:exists(./DmaChannelContinuousEnable) and (./DmaChannelContinuousEnable = 'true')"!][!//
                                /* Continuous mode is enabled */
                                TRUE,
                            [!ELSE!][!//
                                /* Continuous mode is disabled */
                                FALSE,
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!/* Shadow Operation */!][!//
                        [!IF "$Var_DmaShadowTransferEnFlag = 'true'"!][!//
                            [!IF "(node:exists(./DmaChannelShadowOperationEnable) and (./DmaChannelShadowOperationEnable = 'true')) and 
                                  (num:i($Var_TotalTransferConfigNum) > num:i(0))"!][!//
                                /* Pointer to the shadow transfer configuration */
                                &Dma_ShadowingMapChannel[!"./DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!][0],
                            [!ELSE!][!//
                                /* Shadow operation is disabled */
                                NULL_PTR,
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!IF "$Var_DmaLinkedListEnFlag = 'true'"!][!//
                            [!IF "(node:exists(./DmaChannelLinkedListEnable) and (./DmaChannelLinkedListEnable = 'true')) and 
                                  (num:i($Var_TotalTransferConfigNum) > num:i(0))"!][!//
                                /* Pointer to the linked list configuration */
                                &Dma_LinkedListConfigChannel[!"./DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!],
                            [!ELSE!][!//
                                /* Linked list is disabled */
                                NULL_PTR,
                            [!ENDIF!][!//
                        [!ENDIF!][!//
                        [!IF "(node:exists(./DmaChannelNotification)) and (node:value(./DmaChannelNotification) != 'NULL_PTR')"!][!//
                            /* Pointer to the notification function */
                            [!"./DmaChannelNotification"!],
                        [!ELSE!][!//
                            /* Notification function is disabled */
                            NULL_PTR,
                        [!ENDIF!][!//
                        /* Pointer to the transfer configuration of channel[!"./DmaChannelId"!] */
                        &Dma_TransferConfigListChannel[!"./DmaChannelId"!]Core[!"num:i($Var_CoreIdx)"!][0]
                    [!ENDINDENT!][!//
                    }[!//
                    [!IF "num:i($Var_CoreChannelIdx) < num:i($CoreUsedForDmaChannelFlg - 1) "!][!//
                    ,
                    [!ENDIF!][!//
                    [!VAR "Var_CoreChannelIdx" = "num:i($Var_CoreChannelIdx + 1)"!][!//
                [!ENDIF!][!//
            [!ENDLOOP!][!//
            [!ENDINDENT!][!//
            [!/* Line feed */!]
        };

        [!/* Daisy chain */!][!//
        [!IF "$Var_DmaDaisyChainEnFlag = 'true'"!][!//
            [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i(0)"!][!//
            [!IF "$Var_CoreIdx = '0'"!][!//
                [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i($Var_DaisyChainNumCore0)"!][!//
            [!ELSEIF "$Var_CoreIdx = '1'"!][!//
                [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i($Var_DaisyChainNumCore1)"!][!//
            [!ELSEIF "$Var_CoreIdx = '2'"!][!//
                [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i($Var_DaisyChainNumCore2)"!][!//
            [!ELSEIF "$Var_CoreIdx = '3'"!][!//
                [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i($Var_DaisyChainNumCore3)"!][!//
            [!ENDIF!][!//
            [!IF "num:i($CoreUsedForDmaDaisyChainFlg) != num:i(0)"!][!//
                [!LOOP "node:order(DmaConfigSet/DmaDaisyChain/*, './DmaDaisyChainId')"!][!//
                    [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(node:ref(./DmaDaisyChainAssignment/*[1]))"!][!//
                    [!IF "num:i($DmaChannelMappedCoreId) = num:i($Var_CoreIdx)"!][!//
                        /* Daisy chain '[!"node:name(.)"!]' */
                        [!VAR "Var_TotalThisDaisyChainNum" = "num:i(count(./DmaDaisyChainAssignment/*))"!][!//
                        /* #Violation: Dma_PBcfg_c_REF_3 */
                        /* #Violation: Dma_PBcfg_c_REF_4 */
                        static const Dma_ChannelType Dma_DaisyChain[!"node:name(.)"!]Core[!"num:i($Var_CoreIdx)"!][[!"num:i($Var_TotalThisDaisyChainNum)"!]] = 
                        {
                            [!INDENT "4"!][!//
                            [!VAR "Var_DaisyThisChainCnt" = "num:i(0)"!][!//
                            /* Channel IDs */
                            [!LOOP "./DmaDaisyChainAssignment/*"!][!//
                                [!"node:ref(.)/DmaChannelId"!]U[!//
                                [!IF "num:i($Var_DaisyThisChainCnt) < num:i($Var_TotalThisDaisyChainNum - 1)"!][!//
                                    ,
                                [!ENDIF!][!//
                                [!VAR "Var_DaisyThisChainCnt" = "num:i($Var_DaisyThisChainCnt + 1)"!][!//
                            [!ENDLOOP!][!//
                            [!ENDINDENT!][!//
                            [!/* Line feed */!]
                        };
                    [!ENDIF!][!//
                [!ENDLOOP!][!//

                [!/* Calculate the total number of daisy chain in current core */!][!//
                [!VAR "Var_TotalDaisyChainConfigNum" = "num:i(0)"!][!//
                [!LOOP "node:order(DmaConfigSet/DmaDaisyChain/*, './DmaDaisyChainId')"!][!//
                    [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(node:ref(./DmaDaisyChainAssignment/*[1]))"!][!//
                    [!IF "num:i($DmaChannelMappedCoreId) = num:i($Var_CoreIdx)"!][!//
                        [!VAR "Var_TotalDaisyChainConfigNum" = "num:i($Var_TotalDaisyChainConfigNum + 1)"!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                /* Daisy chain set in Core[!"num:i($Var_CoreIdx)"!] */
                /* #Violation: Dma_PBcfg_c_REF_3 */
                /* #Violation: Dma_PBcfg_c_REF_4 */
                static const Dma_DaisyChainMapType Dma_DaisyChainConfigSetCore[!"num:i($Var_CoreIdx)"!][[!"num:i($Var_TotalDaisyChainConfigNum)"!]] = 
                {
                    [!INDENT "4"!][!//
                    [!VAR "Var_DaisyChainConfigCnt" = "num:i(0)"!][!//
                    [!LOOP "node:order(DmaConfigSet/DmaDaisyChain/*, './DmaDaisyChainId')"!][!//
                        [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(node:ref(./DmaDaisyChainAssignment/*[1]))"!][!//
                        [!IF "num:i($DmaChannelMappedCoreId) = num:i($Var_CoreIdx)"!][!//
                            {
                                [!INDENT "8"!][!//
                                    /* Total number of daisy chain members */
                                    [!"num:i(count(./DmaDaisyChainAssignment/*))"!]U,
                                    /* Pointer to the channels that linked list is assigned */
                                    &Dma_DaisyChain[!"node:name(.)"!]Core[!"num:i($Var_CoreIdx)"!][0]
                                [!ENDINDENT!][!//
                            }[!//
                                [!IF "num:i($Var_DaisyChainConfigCnt) < num:i($Var_TotalDaisyChainConfigNum - 1)"!][!//
                                    ,
                                [!ENDIF!][!//
                                [!VAR "Var_DaisyChainConfigCnt" = "num:i($Var_DaisyChainConfigCnt + 1)"!][!//
                        [!ENDIF!][!//
                    [!ENDLOOP!][!//
                    [!ENDINDENT!][!//
                    [!/* Line feed */!]
                };
            [!ENDIF!][!//
        [!ENDIF!][!//

        /* Configuration parameter of core[!"num:i($Var_CoreIdx)"!] */
        static const Dma_CoreConfigType Dma_ConfigSetCore[!"num:i($Var_CoreIdx)"!] = 
        {
            [!INDENT "4"!][!//
            /* The number of channels allocated to Core[!"num:i($Var_CoreIdx)"!] */
            DMA_CFG_MAX_CHANNELS_CORE[!"num:i($Var_CoreIdx)"!],
            [!IF "$Var_DmaDaisyChainEnFlag = 'true'"!][!//
                [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i(0)"!][!//
                [!IF "$Var_CoreIdx = '0'"!][!//
                    [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i($Var_DaisyChainNumCore0)"!][!//
                [!ELSEIF "$Var_CoreIdx = '1'"!][!//
                    [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i($Var_DaisyChainNumCore1)"!][!//
                [!ELSEIF "$Var_CoreIdx = '2'"!][!//
                    [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i($Var_DaisyChainNumCore2)"!][!//
                [!ELSEIF "$Var_CoreIdx = '3'"!][!//
                    [!VAR "CoreUsedForDmaDaisyChainFlg" = "num:i($Var_DaisyChainNumCore3)"!][!//
                [!ENDIF!][!//
                [!IF "num:i($CoreUsedForDmaDaisyChainFlg) != num:i(0)"!][!//
                    /* Total number of daisy chain */
                    [!"num:i($CoreUsedForDmaDaisyChainFlg)"!]U,
                    /* Pointer to the daisy chain list */
                    &Dma_DaisyChainConfigSetCore[!"num:i($Var_CoreIdx)"!][0],
                [!ELSE!][!//
                    /* Total number of daisy chain */
                    0U,
                    /* Pointer to the daisy chain list */
                    NULL_PTR,  
                [!ENDIF!][!//
            [!ENDIF!][!//
            /* Pointer to the configuration of channels */
            &Dma_ChannelConfigCore[!"num:i($Var_CoreIdx)"!][0]
            [!ENDINDENT!][!//
        };
        

        #define DMA_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"num:i($Var_CoreIdx)"!]_UNSPECIFIED
        /* #Violation: Dma_PBcfg_c_REF_2 */
        #include "Dma_MemMap.h"

    [!ENDIF!][!//
[!ENDINDENT!][!//
[!ENDFOR!][!//

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
#define DMA_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"

[!INDENT "0"!][!//
[!IF "$Var_DmaDoubleBufferEnFlag = 'true'"!][!//
[!/* Line feed */!]
[!VAR "Var_TotalDoubleBufferConfigNum" = "num:i(count(DmaConfigSet/DmaDoubleBuffer/*))"!][!//
/* Double buffer detail configuration parameter set
Configuration: DmaDoubleBuffer */
static const Dma_DoubleBufferConfigType Dma_DoubleBufferConfigList[[!"num:i($Var_TotalDoubleBufferConfigNum)"!]] = 
{
    [!INDENT "4"!][!//
    [!VAR "Var_DoubleBufferConfigCnt" = "num:i(0)"!][!//
    [!LOOP "node:order(DmaConfigSet/DmaDoubleBuffer/*, './DmaDoubleBufferId')"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            /* Double buffer target: source or destination */
            DMA_DBSOURCEORDESTINATION_[!"./DmaDoubleBufferSelect"!],
            /* Double buffer switch mode: HW or HW_SW */
            [!"./DmaDoubleBufferSwitchMethod"!],
            /* Double buffer address */
            /* #Violation: Dma_PBcfg_c_REF_1 */
            (uint32)[!"./DmaDoubleBufferAddress"!]
            [!ENDINDENT!][!//
        }[!//
        [!CALL "CG_DoubleBufferNotificationExists"!][!//
        ,
        [!IF "node:exists(./DmaDoubleBufferFrozenNotification) and (./DmaDoubleBufferFrozenNotification != 'NULL_PTR')"!][!//
            /* Pointer to the notification when double buffer frozen */
            [!"./DmaDoubleBufferFrozenNotification"!][!//
        [!ELSE!][!//
            /* No noftification */
            NULL_PTR[!//
        [!ENDIF!][!//
        [!/* Line feed */!]
        [!ENDINDENT!][!//
    }[!//
    [!IF "num:i($Var_DoubleBufferConfigCnt) < num:i($Var_TotalDoubleBufferConfigNum - 1)"!][!//
        ,
    [!ENDIF!][!//
    [!VAR "Var_DoubleBufferConfigCnt" = "num:i($Var_DoubleBufferConfigCnt + 1)"!][!//
    [!ENDLOOP!][!//
    [!/* Line feed */!]
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!IF "$Var_DmaCircularBufferEnFlag = 'true'"!][!//
    [!/* Line feed */!]
    [!VAR "Var_TotalCircularBufferConfigNum" = "num:i(count(DmaConfigSet/DmaCircularBuffer/*))"!][!//
/* Circular buffer configuration parameter set
Configuration: DmaCircularBuffer */
static const Dma_CircularBufferConfig Dma_CircularBufferConfigList[[!"num:i($Var_TotalCircularBufferConfigNum)"!]] = 
{
    [!INDENT "4"!][!//
    [!VAR "Var_CircularBufferConfigCnt" = "num:i(0)"!][!//
    [!LOOP "node:order(DmaConfigSet/DmaCircularBuffer/*, './DmaCircularBufferId')"!][!//
    {
        [!INDENT "8"!][!//
        /* Circular buffer object: source/destination/both */
        [!IF "(./DmaSourceCircularBufferSize != 'DMA_CBSIZE_NONE') and (./DmaDestinationCircularBufferSize != 'DMA_CBSIZE_NONE')"!][!//
            [!"ecu:list('Dma.ChannelCircularBufferCategory')[1]"!],
        [!ELSEIF "(./DmaSourceCircularBufferSize != 'DMA_CBSIZE_NONE')"!][!//
            [!"ecu:list('Dma.ChannelCircularBufferCategory')[2]"!],
        [!ELSEIF "(./DmaDestinationCircularBufferSize != 'DMA_CBSIZE_NONE')"!][!//
            [!"ecu:list('Dma.ChannelCircularBufferCategory')[3]"!],
        [!ENDIF!][!//
        [!//
        /* Size of source circular buffer */
        [!"./DmaSourceCircularBufferSize"!],
        [!//
        /* Size of destination circular buffer */
        [!"./DmaDestinationCircularBufferSize"!],
        [!//
        [!IF "node:exists(./DmaDcbRollbackHaltEnable) and (./DmaDcbRollbackHaltEnable = 'true')"!][!//
            /* Halt when Destination circular buffer rollback event occurred */
            TRUE
        [!ELSE!][!//
            /* Continuous when Destination circular buffer rollback event occurred */
            FALSE
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    }[!//
    [!IF "num:i($Var_CircularBufferConfigCnt) < num:i($Var_TotalCircularBufferConfigNum - 1)"!][!//
        ,
    [!ENDIF!][!//
    [!VAR "Var_CircularBufferConfigCnt" = "num:i($Var_CircularBufferConfigCnt + 1)"!][!//
    [!ENDLOOP!][!//
    [!/* Line feed */!]
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!IF "$Var_DmaPatternMatchEnFlag = 'true'"!][!//
    [!/* Line feed */!]
    [!VAR "Var_TotalPatternMatchConfigNum" = "num:i(count(DmaConfigSet/DmaPattern/*))"!][!//
/* Pattern match configuration parameter set
Configuration: DmaPattern */
static const Dma_MatchPatternConfig Dma_PatternMatchConfigList[[!"num:i($Var_TotalPatternMatchConfigNum)"!]] = 
{
    [!INDENT "4"!][!//
    [!VAR "Var_PatternMatchConfigCnt" = "num:i(0)"!][!//
    [!LOOP "node:order(DmaConfigSet/DmaPattern/*, './DmaPatternId')"!][!//
    {
        [!INDENT "8"!][!//
        /* Pattern match size(unit: bit(s)) */
        [!"./DmaPatternSize"!],
        /* Data used for pattern matching */
        [!"./DmaPatternData"!]U,
        /* Data mask bits for pattern matching */
        [!IF "node:exists(DmaPatternDataMaskBits)"!][!//
            [!"./DmaPatternDataMaskBits"!]U,
        [!ELSE!][!//
            0x00U,
        [!ENDIF!][!//
        /* Stop when pattern matched */
        [!IF "node:exists(./DmaTransferStopPatternMatched) and ./DmaTransferStopPatternMatched = 'true'"!]TRUE[!ELSE!]FALSE[!ENDIF!]
        [!ENDINDENT!][!//
    }[!//
    [!IF "num:i($Var_PatternMatchConfigCnt) < num:i($Var_TotalPatternMatchConfigNum - 1)"!][!//
        ,
    [!ENDIF!][!//
    [!VAR "Var_PatternMatchConfigCnt" = "num:i($Var_PatternMatchConfigCnt + 1)"!][!//
    [!ENDLOOP!][!//
    [!/* Line feed */!]
    [!ENDINDENT!][!//
};
[!ENDIF!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!IF "($Var_DmaDoubleBufferEnFlag = 'true') or ($Var_DmaPatternMatchEnFlag = 'true') or ($Var_DmaCircularBufferEnFlag = 'true')"!][!//
    /* Common configuration for all channels and cores, contains double buffer configuration, 
       circualr buffer configuration and pattern configuration */
    static const Dma_CommonConfigType Dma_CommonConfigSet = 
    {
        [!INDENT "4"!][!//
        [!VAR "Var_Comma_Flag" = "'false'"!][!//
        [!IF "($Var_DmaDoubleBufferEnFlag = 'true')"!][!//
            /* Pointer to the double buffer configuration address */
            &Dma_DoubleBufferConfigList[0]
            [!VAR "Var_Comma_Flag" = "'true'"!][!//
        [!ENDIF!][!//
        [!IF "($Var_DmaCircularBufferEnFlag = 'true')"!][!//
            /* Pointer to the circular buffer configuration address */
            [!IF "$Var_Comma_Flag = 'true'"!],[!ENDIF!][!//
            &Dma_CircularBufferConfigList[0]
            [!VAR "Var_Comma_Flag" = "'true'"!][!//
        [!ENDIF!][!//
        [!IF "($Var_DmaPatternMatchEnFlag = 'true')"!][!//
            /* Pointer to the pattern configuration address */
            [!IF "$Var_Comma_Flag = 'true'"!],[!ENDIF!][!//
            &Dma_PatternMatchConfigList[0]
        [!ENDIF!][!//
        [!ENDINDENT!][!//
    };
[!ENDIF!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!SELECT "DmaConfigSet"!][!//
/* Configuration for the core ID that DMA logical channel ID is mapped to */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
[!VAR "Var_TotalChannelNum" = "num:i(count(./DmaChannel/*))"!][!//
static const Dma_ChannelMapType Dma_ChannelMapConfig[[!"$Var_TotalChannelNum"!]] =
{
    [!INDENT "4"!][!//
    [!VAR "Var_ChannelIdCnt" = "num:i(0)"!][!//
    [!VAR "Var_ChannelIdxInCore0" = "num:i(0)"!][!//
    [!VAR "Var_ChannelIdxInCore1" = "num:i(0)"!][!//
    [!VAR "Var_ChannelIdxInCore2" = "num:i(0)"!][!//
    [!VAR "Var_ChannelIdxInCore3" = "num:i(0)"!][!//
    [!VAR "Var_TransferLliIdxInCore0" = "num:i(0)"!][!//
    [!VAR "Var_TransferLliIdxInCore1" = "num:i(0)"!][!//
    [!VAR "Var_TransferLliIdxInCore2" = "num:i(0)"!][!//
    [!VAR "Var_TransferLliIdxInCore3" = "num:i(0)"!][!//
    [!VAR "Var_ShadowingIdxInCore0" = "num:i(0)"!][!//
    [!VAR "Var_ShadowingIdxInCore1" = "num:i(0)"!][!//
    [!VAR "Var_ShadowingIdxInCore2" = "num:i(0)"!][!//
    [!VAR "Var_ShadowingIdxInCore3" = "num:i(0)"!][!//
    [!VAR "Var_DaisyChainIdxInCore0" = "num:i(0)"!][!//
    [!VAR "Var_DaisyChainIdxInCore1" = "num:i(0)"!][!//
    [!VAR "Var_DaisyChainIdxInCore2" = "num:i(0)"!][!//
    [!VAR "Var_DaisyChainIdxInCore3" = "num:i(0)"!][!//
    [!LOOP "node:order(DmaChannel/*, './DmaChannelId')"!][!//
        [!CALL "CG_FindDmaChannelMappedCoreId", "DmaChannelName" = "node:name(.)"!][!//
        [!VAR "DmaChannelMappedCoreId_Temp" = "$DmaChannelMappedCoreId"!][!//
        /* Logical channel ID [!"num:i(./DmaChannelId)"!], name is "[!"node:name(.)"!]":
          Physical channel , HW unit , channel index [!//
            [!IF "num:i($Var_TransferMultiConfigTotal) != 0"!][!//
            , 
            Transfer Index [!//
            [!ENDIF!][!//
            [!IF "num:i($Var_ShadowingMultiConfigTotal) != 0"!][!//
            , shadowing operation index [!//
            [!ENDIF!][!//
            [!IF "$Var_DmaDaisyChainEnFlag = 'true'"!][!//
            , daisy chain [!//
            , daisy chain head channel [!//
            [!ENDIF!][!//
          in core[!"num:i($DmaChannelMappedCoreId)"!] */
        {[!//
            [!"./DmaPhyChannel"!]U, [!//
            [!"text:split(./DmaChannelHwUnitAllocation, 'DMA')[1]"!]U, [!//
            [!IF "num:i($DmaChannelMappedCoreId) = num:i(0)"!][!//
                [!"$Var_ChannelIdxInCore0"!]U, [!//
                [!VAR "Var_ChannelIdxInCore0" = "num:i($Var_ChannelIdxInCore0 + 1)"!][!//
            [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(1)"!][!//
                [!"$Var_ChannelIdxInCore1"!]U, [!//
                [!VAR "Var_ChannelIdxInCore1" = "num:i($Var_ChannelIdxInCore1 + 1)"!][!//
            [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(2)"!][!//
                [!"$Var_ChannelIdxInCore2"!]U, [!//
                [!VAR "Var_ChannelIdxInCore2" = "num:i($Var_ChannelIdxInCore2 + 1)"!][!//
            [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(3)"!][!//
                [!"$Var_ChannelIdxInCore3"!]U, [!//
                [!VAR "Var_ChannelIdxInCore3" = "num:i($Var_ChannelIdxInCore3 + 1)"!][!//
            [!ENDIF!][!//
            [!IF "num:i($Var_TransferMultiConfigTotal) != 0"!][!//
                [!IF "num:i($DmaChannelMappedCoreId) = num:i(0)"!][!//
                    [!IF "num:i(count(./DmaChTransferConfig/*)) > num:i(1)"!][!//
                        [!"num:i($Var_TransferLliIdxInCore0)"!]U, [!//
                        [!VAR "Var_TransferLliIdxInCore0" = "num:i($Var_TransferLliIdxInCore0 + 1)"!][!//
                    [!ELSE!][!//
                        255U, [!//
                    [!ENDIF!][!//
                [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(1)"!][!//
                    [!IF "num:i(count(./DmaChTransferConfig/*)) > num:i(1)"!][!//
                        [!"num:i($Var_TransferLliIdxInCore1)"!]U, [!//
                        [!VAR "Var_TransferLliIdxInCore1" = "num:i($Var_TransferLliIdxInCore1 + 1)"!][!//
                    [!ELSE!][!//
                        255U, [!//
                    [!ENDIF!][!//
                [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(2)"!][!//
                    [!IF "num:i(count(./DmaChTransferConfig/*)) > num:i(1)"!][!//
                        [!"num:i($Var_TransferLliIdxInCore2)"!]U, [!//
                        [!VAR "Var_TransferLliIdxInCore2" = "num:i($Var_TransferLliIdxInCore2 + 1)"!][!//
                    [!ELSE!][!//
                        255U, [!//
                    [!ENDIF!][!//
                [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(3)"!][!//
                    [!IF "num:i(count(./DmaChTransferConfig/*)) > num:i(1)"!][!//
                        [!"num:i($Var_TransferLliIdxInCore3)"!]U, [!//
                        [!VAR "Var_TransferLliIdxInCore3" = "num:i($Var_TransferLliIdxInCore3 + 1)"!][!//
                    [!ELSE!][!//
                        255U, [!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!//
            [!IF "num:i($Var_ShadowingMultiConfigTotal) != 0"!][!//
                [!IF "num:i($DmaChannelMappedCoreId) = num:i(0)"!][!//
                    [!IF "num:i(count(./DmaChShadowConfig/*)) > num:i(1)"!][!//
                        [!"num:i($Var_ShadowingIdxInCore0)"!]U, [!//
                        [!VAR "Var_ShadowingIdxInCore0" = "num:i($Var_ShadowingIdxInCore0 + 1)"!][!//
                    [!ELSE!][!//
                        255U, [!//
                    [!ENDIF!][!//
                [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(1)"!][!//
                    [!IF "num:i(count(./DmaChShadowConfig/*)) > num:i(1)"!][!//
                        [!"num:i($Var_ShadowingIdxInCore1)"!]U, [!//
                        [!VAR "Var_ShadowingIdxInCore1" = "num:i($Var_ShadowingIdxInCore1 + 1)"!][!//
                    [!ELSE!][!//
                        255U, [!//
                    [!ENDIF!][!//
                [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(2)"!][!//
                    [!IF "num:i(count(./DmaChShadowConfig/*)) > num:i(1)"!][!//
                        [!"num:i($Var_ShadowingIdxInCore2)"!]U, [!//
                        [!VAR "Var_ShadowingIdxInCore2" = "num:i($Var_ShadowingIdxInCore2 + 1)"!][!//
                    [!ELSE!][!//
                        255U, [!//
                    [!ENDIF!][!//
                [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(3)"!][!//
                    [!IF "num:i(count(./DmaChShadowConfig/*)) > num:i(1)"!][!//
                        [!"num:i($Var_ShadowingIdxInCore3)"!]U, [!//
                        [!VAR "Var_ShadowingIdxInCore3" = "num:i($Var_ShadowingIdxInCore3 + 1)"!][!//
                    [!ELSE!][!//
                        255U, [!//
                    [!ENDIF!][!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            [!//
            [!IF "$Var_DmaDaisyChainEnFlag = 'true'"!][!//
                [!VAR "Var_CurrChannelId" = "./DmaChannelId"!][!//
                [!VAR "Var_DaisyChainChannelEn" = "'false'"!][!//
                [!VAR "Var_DaisyChainLastChannelEn" = "'false'"!][!//
                [!LOOP "node:order(as:modconf('Dma')[1]/DmaConfigSet/DmaDaisyChain/*, './DmaDaisyChainId')"!][!//
                    [!IF "node:ref(./DmaDaisyChainAssignment/*[1])/DmaChannelId = $Var_CurrChannelId"!][!//
                        [!IF "num:i($DmaChannelMappedCoreId) = num:i(0)"!][!//
                            [!"$Var_DaisyChainIdxInCore0"!]U, [!//
                            [!VAR "Var_DaisyChainIdxInCore0" = "num:i($Var_DaisyChainIdxInCore0 + 1)"!][!//
                        [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(1)"!][!//
                            [!"$Var_DaisyChainIdxInCore1"!]U, [!//
                            [!VAR "Var_DaisyChainIdxInCore1" = "num:i($Var_DaisyChainIdxInCore1 + 1)"!][!//
                        [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(2)"!][!//
                            [!"$Var_DaisyChainIdxInCore2"!]U, [!//
                            [!VAR "Var_DaisyChainIdxInCore2" = "num:i($Var_DaisyChainIdxInCore2 + 1)"!][!//
                        [!ELSEIF "num:i($DmaChannelMappedCoreId) = num:i(3)"!][!//
                            [!"$Var_DaisyChainIdxInCore3"!]U, [!//
                            [!VAR "Var_DaisyChainIdxInCore3" = "num:i($Var_DaisyChainIdxInCore3 + 1)"!][!//
                        [!ENDIF!][!//
                        [!VAR "Var_DaisyChainChannelEn" = "'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!IF "$Var_DaisyChainChannelEn = 'false'"!][!//
                    255U, [!//
                [!ENDIF!][!//
                [!LOOP "node:order(as:modconf('Dma')[1]/DmaConfigSet/DmaDaisyChain/*, './DmaDaisyChainId')"!][!//
                    [!IF "node:ref(./DmaDaisyChainAssignment/*[last()])/DmaChannelId = $Var_CurrChannelId"!][!//
                        [!"node:ref(./DmaDaisyChainAssignment/*[1])/DmaChannelId"!]U, [!//
                        [!VAR "Var_DaisyChainLastChannelEn" = "'true'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!IF "$Var_DaisyChainLastChannelEn = 'false'"!][!//
                    255U, [!//
                [!ENDIF!][!//
            [!ENDIF!][!//
            MCAL_CORE[!"num:i($DmaChannelMappedCoreId_Temp)"!][!//
        }[!//
        [!IF "num:i($Var_ChannelIdCnt) < num:i($Var_TotalChannelNum - 1)"!],[!ENDIF!]
        [!VAR "Var_ChannelIdCnt" = "num:i($Var_ChannelIdCnt + 1)"!][!//
    [!ENDLOOP!][!//
    [!ENDINDENT!][!//
};
[!ENDSELECT!][!//
[!ENDINDENT!][!//

[!INDENT "0"!][!//
[!VAR "Var_CfgHwUnitCnt" = "num:i(0)"!][!//
[!FOR "Var_HwUnitCnt" = "num:i(0)" TO "num:i(count(ecu:list('Dma.HwUnitList')) - 1)"!][!//
    [!VAR "Var_HwUnitName" = "ecu:list('Dma.HwUnitList')[num:i($Var_HwUnitCnt + 1)]"!][!//
    [!VAR "Var_HwUnitId" = "text:split($Var_HwUnitName, 'DMA')[1]"!][!//
    [!IF "num:i(bit:and($Var_UsedHwUnitCntBits, bit:shl(1, $Var_HwUnitId))) != num:i(0)"!][!//
        [!VAR "Var_AllPhyChannelNum" = "num:i(ecu:get(concat('Dma.ChannelNumDma', num:i($Var_HwUnitId))))"!][!//
        /* [!"$Var_HwUnitName"!]: array index is physical channel, array member is logical channel */
        /* #Violation: Dma_PBcfg_c_REF_3 */
        /* #Violation: Dma_PBcfg_c_REF_4 */
        static const Dma_ChannelType Dma_HwToChannelConfig_[!"$Var_HwUnitName"!][[!"num:i($Var_AllPhyChannelNum)"!]] = 
        {
            [!INDENT "4"!][!//
            [!VAR "Var_ChannelLoopCnt" = "num:i(0)"!][!//
            [!FOR "Var_PhyChannelId" = "num:i(0)" TO "num:i($Var_AllPhyChannelNum - 1)"!][!//
                [!VAR "Var_ChannelExistsFlg" = "'255'"!][!//
                [!LOOP "node:order(DmaConfigSet/DmaChannel/*, './DmaChannelId')"!][!//
                    [!IF "(./DmaChannelHwUnitAllocation = $Var_HwUnitName) and (num:i(./DmaPhyChannel) = num:i($Var_PhyChannelId))"!][!//
                        [!VAR "Var_ChannelExistsFlg" = "./DmaChannelId"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDLOOP!][!//
                [!"$Var_ChannelExistsFlg"!]U[!//
            [!IF "$Var_ChannelLoopCnt != num:i($Var_AllPhyChannelNum - 1)"!][!//
                ,
            [!ENDIF!][!//
            [!VAR "Var_ChannelLoopCnt" = "num:i($Var_ChannelLoopCnt + 1)"!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
            [!/* Line feed */!]
        };
    [!ENDIF!][!//
[!ENDFOR!][!//
[!ENDINDENT!][!//


[!INDENT "0"!][!//
/* Configuration for used HW unit list */
static const Dma_HwUnitType Dma_HwUnitUsedList[[!"num:i($Var_CfgUsedDmaHwUnitNum)"!]] = 
{
    [!INDENT "4"!][!//
        [!VAR "Var_CfgHwUnitCnt" = "num:i(0)"!][!//
        [!FOR "Var_HwUnitCnt" = "num:i(0)" TO "num:i(count(ecu:list('Dma.HwUnitList')) - 1)"!][!//
            [!VAR "Var_HwUnitName" = "ecu:list('Dma.HwUnitList')[num:i($Var_HwUnitCnt + 1)]"!][!//
            [!VAR "Var_HwUnitId" = "text:split($Var_HwUnitName, 'DMA')[1]"!][!//
            [!IF "num:i(bit:and($Var_UsedHwUnitCntBits, bit:shl(1, $Var_HwUnitId))) != num:i(0)"!][!//
                [!"num:i($Var_HwUnitId)"!]U[!//
                [!IF "num:i($Var_CfgHwUnitCnt) < num:i($Var_CfgUsedDmaHwUnitNum - 1)"!][!//
                ,
                [!ENDIF!][!//
                [!VAR "Var_CfgHwUnitCnt" = "num:i($Var_CfgHwUnitCnt + 1)"!][!//
            [!ENDIF!][!//
        [!ENDFOR!][!//
    [!ENDINDENT!][!//
    [!/* Line feed */!]
};

/* Configuration for the HW units */
static const Dma_HwUnitConfigType Dma_HwUnitConfig = 
{
    [!INDENT "4"!][!//
    /* The number of HW units used in the Tresos configured */
    [!"num:i($Var_CfgUsedDmaHwUnitNum)"!]U,
    /* Pointer to the list of all used HW units */
    &Dma_HwUnitUsedList[0],
    /* List of HW unit and physical channel to logical channel */
    {
        [!INDENT "8"!][!//
            [!VAR "Var_CfgHwUnitCnt" = "num:i(0)"!][!//
            [!FOR "Var_AllHwUnitCnt" = "num:i(0)" TO "num:i(ecu:get('Dma.TotalHwUnit') - 1)"!][!//
                [!VAR "Var_HwUnitExistsFlag" = "'FALSE'"!][!//
                [!FOR "Var_HwUnitCnt" = "num:i(0)" TO "num:i(count(ecu:list('Dma.HwUnitList')) - 1)"!][!//
                    [!VAR "Var_HwUnitName" = "ecu:list('Dma.HwUnitList')[num:i($Var_HwUnitCnt + 1)]"!][!//
                    [!VAR "Var_HwUnitId" = "text:split($Var_HwUnitName, 'DMA')[1]"!][!//
                    [!IF "num:i($Var_AllHwUnitCnt) = num:i($Var_HwUnitId)"!][!//
                        [!IF "num:i(bit:and($Var_UsedHwUnitCntBits, bit:shl(1, $Var_HwUnitId))) != num:i(0)"!][!//
                            /* Pointer to the mapping relationship from physical channel ID to logical channel ID 
                            for DMA[!"$Var_HwUnitId"!] */
                            &Dma_HwToChannelConfig_[!"$Var_HwUnitName"!][0][!//
                        [!ELSE!][!//
                            /* DMA[!"$Var_HwUnitId"!] not used */
                            NULL_PTR[!//
                        [!ENDIF!][!//
                        [!VAR "Var_HwUnitExistsFlag" = "'TRUE'"!][!//
                        [!BREAK!][!//
                    [!ENDIF!][!//
                [!ENDFOR!][!//
                [!IF "$Var_HwUnitExistsFlag = 'FALSE'"!][!//
                    /* DMA[!"$Var_AllHwUnitCnt"!] not exists */
                    NULL_PTR[!//
                [!ENDIF!][!//
                [!IF "num:i($Var_CfgHwUnitCnt) < num:i(ecu:get('Dma.TotalHwUnit') - 1)"!][!//
                    ,
                [!ENDIF!][!//
                [!VAR "Var_CfgHwUnitCnt" = "num:i($Var_CfgHwUnitCnt + 1)"!][!//
            [!ENDFOR!][!//
        [!ENDINDENT!][!//
        [!/* Line feed */!]
    }
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

[!INDENT "0"!][!//
/* Dma configuration set parameters */
const Dma_ConfigType Dma_ConfigSet[!"$Var_DmaConfigShortName"!][DMA_CONFIGSET_CNT] =
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        /* Configuration for each core */
        {
            [!INDENT "12"!][!//
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
                [!IF "num:i($CoreUsedForDmaChannelFlg) != num:i(0)"!][!//
                    /* Dma configuration of core[!"num:i($Var_CoreIdx)"!] */
                    &Dma_ConfigSetCore[!"num:i($Var_CoreIdx)"!][!//
                [!ELSE!][!//
                    /* No configuration for Core[!"num:i($Var_CoreIdx)"!] */
                    NULL_PTR[!//
                [!ENDIF!][!//
                [!IF "num:i($Var_CoreIdx) < num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                    ,
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
            [!/* Line feed */!]
        },
        [!IF "($Var_DmaDoubleBufferEnFlag = 'true') or ($Var_DmaPatternMatchEnFlag = 'true') or ($Var_DmaCircularBufferEnFlag = 'true')"!][!//
            /* Pointer to Dma common configuration set address */
            &Dma_CommonConfigSet,
        [!ENDIF!][!//
        /* Pointer to the configuration that maps Dma channel to core */
        &Dma_ChannelMapConfig[0],
        /* Pointer to the configuration for the HW unit */
        &Dma_HwUnitConfig
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};
[!ENDINDENT!][!//

#define DMA_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

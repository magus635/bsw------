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
#include "Dma.h"
#include "Mcall.h"
/* Include external header files to call notification functions */
#include "Dma_Demo.h"
#include "Adc_Demo.h"
#include "Dsadc_Demo.h"


/****************************************************************************************************
**                          External Function Declarations                                         **
****************************************************************************************************/
extern void DmaDemo_M2mContinuousNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
extern void DmaDemo_M2mLinkedListNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
extern void DmaDemo_M2mShadowNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
extern void DmaDemo_M2mPatternNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
extern void DmaDemo_M2mDaisyChain0Notif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
extern void DmaDemo_M2mDaisyChain1Notif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
extern void Spi_DmaNotification(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
extern void DmaDemo_DoubleBuffer0_Notif(Dma_ChannelType Channel, Dma_DblFrznStatusType FrozenStatus);

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/* Core0 */
#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"

/* Linked list item buffer of channel 4 */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static Dma_LliBufType Dma_Channel4LliCore0[3];
/* Linked list item buffer of channel 14 */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static Dma_LliBufType Dma_Channel14LliCore0[3];

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"

/* Core1 */
#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"


#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/


/* Configuration informations which mapped to Core0 */
#define DMA_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"

/* Basic transfer configuration parameter of channel0: M2M
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel0Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Dma_SrcBuf0_8bits[0],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Dma_DestBuf0_8bits[0],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_8BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request: DMA_REQUEST0_GTM */
                DMA_DMA0_REQUEST0_GTM,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    }
};


/* Basic transfer configuration parameter of channel2: M2M_DoubleBuf
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel2Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        0U,
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_32bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_32bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_32BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    }
};


/* Basic transfer configuration parameter of channel3: M2M_CircBuf
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel3Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        0U,
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_8BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    }
};


/* Basic transfer configuration parameter of channel4: M2M_LinkedList
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel4Core0[3] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_8BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    },
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_16bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_16bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    },
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        0U,
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_32bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_32bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_32BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    }
};

/* Transfer ID assigned to the linked list
Configuration: DmaChLinkedListTransferAssignment */
/* Linked list ID0 of channel 4: "M2M_LinkedList" */
/* First element is the total number of linked list items, others point to the transfer ID */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_TransferType Dma_TransfersMapLli0Channel4Core0[3] = 
{
    /* Transfer IDs */
    2U, 
    0U, 
    1U
};

/* Pointer to the linked list mapping information list
Configuration: DmaChLinkedListItemConfig */
static const Dma_LinkedListMapType Dma_TransfersLli4Channel4Core0[1] = 
{
    {
        /* Total number of this linked list members */
        3U,
        /* Pointer to the transfer that linked list is assigned */
        &Dma_TransfersMapLli0Channel4Core0[0]
    }
};

/* Linked list configuration entry of channel4 */
static const Dma_ChLinkedListConfigType Dma_LinkedListConfigChannel4Core0 = 
{
    /* Pointer to the linked list item of transfer configuration mapping list */
    &Dma_TransfersLli4Channel4Core0[0],
    /* Pointer to the linked list buffer */
    &Dma_Channel4LliCore0[0]
};

/* Basic transfer configuration parameter of channel5: M2M_Shadow
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel5Core0[3] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_8BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    },
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_16bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_16bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    },
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_32bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_32bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_32BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    }
};


/* Shadowing detail configuration parameters of channel5
Configuration: DmaChShadowConfig */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_ShadowingMapType Dma_ShadowingMapChannel5Core0[2] = 
{
    /* Shadow operation ID0 of channel 5: "M2M_Shadow" */
    {
        /* ShadowTransfer0: Transfer ID1 */
        1U
        /*Linked list is not enabled*/
        ,0xFFU
    },
    /* Shadow operation ID1 of channel 5: "M2M_Shadow" */
    {
        /* ShadowTransfer1: Transfer ID2 */
        2U
        /*Linked list is not enabled*/
        ,0xFFU
    }
};

/* Basic transfer configuration parameter of channel6: M2M_Pattern
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel6Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        0U,
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_8BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    }
};


/* Basic transfer configuration parameter of channel7: M2M_Daisy0
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel7Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_8bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_8BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    }
};


/* Basic transfer configuration parameter of channel8: M2M_Daisy1
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel8Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_16bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_16bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    }
};


/* Basic transfer configuration parameter of channel9: ADC1_Channel0
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel9Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB00004C8U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Adc_DmaTransferSwTrigResult[0],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2M,
            /* Source request configuration */
            {
                /* Local request: DMA_REQUEST23_SARADC1_RESULT0 */
                DMA_DMA1_REQUEST23_SARADC1_RESULT0,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            5U
        }
    }
};


/* Basic transfer configuration parameter of channel10: ADC1_Channel1
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel10Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB00004CCU,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Adc_DmaTransferSwTrigResult[5],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2M,
            /* Source request configuration */
            {
                /* Local request: DMA_REQUEST24_SARADC1_RESULT1 */
                DMA_DMA1_REQUEST24_SARADC1_RESULT1,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            5U
        }
    }
};


/* Basic transfer configuration parameter of channel11: ADC1_Channel2
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel11Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB00004D0U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Adc_DmaTransferSwTrigResult[10],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2M,
            /* Source request configuration */
            {
                /* Local request: DMA_REQUEST25_SARADC1_RESULT2 */
                DMA_DMA1_REQUEST25_SARADC1_RESULT2,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            5U
        }
    }
};


/* Basic transfer configuration parameter of channel12: ADC1_Channel3
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel12Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB00004D4U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Adc_DmaTransferSwTrigResult[15],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2M,
            /* Source request configuration */
            {
                /* Local request: DMA_REQUEST26_SARADC1_RESULT3 */
                DMA_DMA1_REQUEST26_SARADC1_RESULT3,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            5U
        }
    }
};


/* Basic transfer configuration parameter of channel13: ADC1_Channel7
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel13Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB00004E4U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Adc_DmaTransferSwTrigResult[3],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2M,
            /* Source request configuration */
            {
                /* Local request: DMA_REQUEST30_SARADC1_RESULT7 */
                DMA_DMA1_REQUEST30_SARADC1_RESULT7,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            1U
        }
    }
};


/* Basic transfer configuration parameter of channel14: ADC1_GroupSwTrig2
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel14Core0[3] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        0U,
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB00004D8U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Adc_DmaTransferSwTrigResult[0],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            1U
        }
    },
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB00004DCU,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Adc_DmaTransferSwTrigResult[1],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            1U
        }
    },
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB00004E0U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Adc_DmaTransferSwTrigResult[2],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            1U
        }
    }
};

/* Transfer ID assigned to the linked list
Configuration: DmaChLinkedListTransferAssignment */
/* Linked list ID0 of channel 14: "ADC1_GroupSwTrig2" */
/* First element is the total number of linked list items, others point to the transfer ID */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_TransferType Dma_TransfersMapLli0Channel14Core0[3] = 
{
    /* Transfer IDs */
    0U, 
    1U, 
    2U
};

/* Pointer to the linked list mapping information list
Configuration: DmaChLinkedListItemConfig */
static const Dma_LinkedListMapType Dma_TransfersLli14Channel14Core0[1] = 
{
    {
        /* Total number of this linked list members */
        3U,
        /* Pointer to the transfer that linked list is assigned */
        &Dma_TransfersMapLli0Channel14Core0[0]
    }
};

/* Linked list configuration entry of channel14 */
static const Dma_ChLinkedListConfigType Dma_LinkedListConfigChannel14Core0 = 
{
    /* Pointer to the linked list item of transfer configuration mapping list */
    &Dma_TransfersLli14Channel14Core0[0],
    /* Pointer to the linked list buffer */
    &Dma_Channel14LliCore0[0]
};

/* Basic transfer configuration parameter of channel15: SPITx
This channel no transfer configuration and this is generated default. */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_TransferConfigType Dma_TransferConfigListChannel15Core0[1U] = 
{
    {
        255U,   /* Invalid ID */
        255U,    /* Invalid ID */
        255U,    /* Invalid ID */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address default point to NULL_PTR */
                (uint32)0U,
                /* No increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address default point to NULL_PTR */
                (uint32)0U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_8BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2P,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request: DMA_REQUEST0_ESPI0_TX */
                DMA_DMA2_REQUEST0_ESPI0_TX,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            1U
        }
    }
};

/* Basic transfer configuration parameter of channel16: SPIRx
This channel no transfer configuration and this is generated default. */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_TransferConfigType Dma_TransferConfigListChannel16Core0[1U] = 
{
    {
        255U,   /* Invalid ID */
        255U,    /* Invalid ID */
        255U,    /* Invalid ID */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address default point to NULL_PTR */
                (uint32)0U,
                /* No increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address default point to NULL_PTR */
                (uint32)0U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_8BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2M,
            /* Source request configuration */
            {
                /* Local request: DMA_REQUEST1_ESPI0_RX */
                DMA_DMA2_REQUEST1_ESPI0_RX,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            1U
        }
    }
};

/* Basic transfer configuration parameter of channel17: Dsadc3
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel17Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB0012414U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&DsadcDemo_MainConvResult[0],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2M,
            /* Source request configuration */
            {
                /* Local request: DMA_REQUEST3_DSADC3 */
                DMA_DMA1_REQUEST3_DSADC3,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            10U
        }
    }
};


/* Basic transfer configuration parameter of channel18: ADC1_AllChToOneResReg
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel18Core0[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)0xB0000504U,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_NO_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)&Adc_DmaTransferSwTrigResult[0],
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_P2M,
            /* Source request configuration */
            {
                /* Local request: DMA_REQUEST38_SARADC1_RESULT15 */
                DMA_DMA1_REQUEST38_SARADC1_RESULT15,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            6U
        }
    }
};



/* Detail configuration parameters of all channels in core0 */
static const Dma_ChConfigType Dma_ChannelConfigCore0[DMA_CFG_MAX_CHANNELS_CORE0] = 
{
    /* Configuration parameter of DMA0 channel0 */
    /* Channel name: M2M,  channel ID: 0 */
    {
        /* Channel ID */
        0U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel0 */
        &Dma_TransferConfigListChannel0Core0[0]
    },
    /* Configuration parameter of DMA0 channel2 */
    /* Channel name: M2M_DoubleBuf,  channel ID: 2 */
    {
        /* Channel ID */
        2U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        (uint8)DMA_CH_INT_TC,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel2 */
        &Dma_TransferConfigListChannel2Core0[0]
    },
    /* Configuration parameter of DMA0 channel3 */
    /* Channel name: M2M_CircBuf,  channel ID: 3 */
    {
        /* Channel ID */
        3U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel3 */
        &Dma_TransferConfigListChannel3Core0[0]
    },
    /* Configuration parameter of DMA0 channel4 */
    /* Channel name: M2M_LinkedList,  channel ID: 4 */
    {
        /* Channel ID */
        4U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        3U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        1U,
        /* Interrupt enable bits */
        (uint8)DMA_CH_INT_TC,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Pointer to the linked list configuration */
        &Dma_LinkedListConfigChannel4Core0,
        /* Pointer to the notification function */
        DmaDemo_M2mLinkedListNotif,
        /* Pointer to the transfer configuration of channel4 */
        &Dma_TransferConfigListChannel4Core0[0]
    },
    /* Configuration parameter of DMA1 channel0 */
    /* Channel name: M2M_Shadow,  channel ID: 5 */
    {
        /* Channel ID */
        5U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        3U,
        /* Total number of shadowing operation configurations */
        2U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        (uint8)DMA_CH_INT_TC,
        /* Continuous mode is disabled */
        FALSE,
        /* Pointer to the shadow transfer configuration */
        &Dma_ShadowingMapChannel5Core0[0],
        /* Linked list is disabled */
        NULL_PTR,
        /* Pointer to the notification function */
        DmaDemo_M2mShadowNotif,
        /* Pointer to the transfer configuration of channel5 */
        &Dma_TransferConfigListChannel5Core0[0]
    },
    /* Configuration parameter of DMA2 channel0 */
    /* Channel name: M2M_Pattern,  channel ID: 6 */
    {
        /* Channel ID */
        6U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        (uint8)DMA_CH_INT_ERROR| \
        (uint8)DMA_CH_INT_TC| \
        (uint8)DMA_CH_INT_PATTERN,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Pointer to the notification function */
        DmaDemo_M2mPatternNotif,
        /* Pointer to the transfer configuration of channel6 */
        &Dma_TransferConfigListChannel6Core0[0]
    },
    /* Configuration parameter of DMA3 channel0 */
    /* Channel name: M2M_Daisy0,  channel ID: 7 */
    {
        /* Channel ID */
        7U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Pointer to the notification function */
        DmaDemo_M2mDaisyChain0Notif,
        /* Pointer to the transfer configuration of channel7 */
        &Dma_TransferConfigListChannel7Core0[0]
    },
    /* Configuration parameter of DMA3 channel1 */
    /* Channel name: M2M_Daisy1,  channel ID: 8 */
    {
        /* Channel ID */
        8U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        (uint8)DMA_CH_INT_TC,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Pointer to the notification function */
        DmaDemo_M2mDaisyChain1Notif,
        /* Pointer to the transfer configuration of channel8 */
        &Dma_TransferConfigListChannel8Core0[0]
    },
    /* Configuration parameter of DMA1 channel2 */
    /* Channel name: ADC1_Channel0,  channel ID: 9 */
    {
        /* Channel ID */
        9U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel9 */
        &Dma_TransferConfigListChannel9Core0[0]
    },
    /* Configuration parameter of DMA1 channel3 */
    /* Channel name: ADC1_Channel1,  channel ID: 10 */
    {
        /* Channel ID */
        10U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel10 */
        &Dma_TransferConfigListChannel10Core0[0]
    },
    /* Configuration parameter of DMA1 channel4 */
    /* Channel name: ADC1_Channel2,  channel ID: 11 */
    {
        /* Channel ID */
        11U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel11 */
        &Dma_TransferConfigListChannel11Core0[0]
    },
    /* Configuration parameter of DMA1 channel5 */
    /* Channel name: ADC1_Channel3,  channel ID: 12 */
    {
        /* Channel ID */
        12U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel12 */
        &Dma_TransferConfigListChannel12Core0[0]
    },
    /* Configuration parameter of DMA1 channel6 */
    /* Channel name: ADC1_Channel7,  channel ID: 13 */
    {
        /* Channel ID */
        13U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is enabled */
        TRUE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel13 */
        &Dma_TransferConfigListChannel13Core0[0]
    },
    /* Configuration parameter of DMA1 channel7 */
    /* Channel name: ADC1_GroupSwTrig2,  channel ID: 14 */
    {
        /* Channel ID */
        14U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        3U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        1U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is enabled */
        TRUE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Pointer to the linked list configuration */
        &Dma_LinkedListConfigChannel14Core0,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel14 */
        &Dma_TransferConfigListChannel14Core0[0]
    },
    /* Configuration parameter of DMA2 channel2 */
    /* Channel name: SPITx,  channel ID: 15 */
    {
        /* Channel ID */
        15U,
        /* No transfer configurations */
        FALSE,
        /* Total number of transfer configurations */
        0U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel15 */
        &Dma_TransferConfigListChannel15Core0[0]
    },
    /* Configuration parameter of DMA2 channel3 */
    /* Channel name: SPIRx,  channel ID: 16 */
    {
        /* Channel ID */
        16U,
        /* No transfer configurations */
        FALSE,
        /* Total number of transfer configurations */
        0U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        (uint8)DMA_CH_INT_TC,
        /* Continuous mode is disabled */
        FALSE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Pointer to the notification function */
        Spi_DmaNotification,
        /* Pointer to the transfer configuration of channel16 */
        &Dma_TransferConfigListChannel16Core0[0]
    },
    /* Configuration parameter of DMA1 channel8 */
    /* Channel name: Dsadc3,  channel ID: 17 */
    {
        /* Channel ID */
        17U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is enabled */
        TRUE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel17 */
        &Dma_TransferConfigListChannel17Core0[0]
    },
    /* Configuration parameter of DMA1 channel9 */
    /* Channel name: ADC1_AllChToOneResReg,  channel ID: 18 */
    {
        /* Channel ID */
        18U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        0U,
        /* Continuous mode is enabled */
        TRUE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Notification function is disabled */
        NULL_PTR,
        /* Pointer to the transfer configuration of channel18 */
        &Dma_TransferConfigListChannel18Core0[0]
    }
};

/* Daisy chain 'DmaDaisyChain_0' */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_ChannelType Dma_DaisyChainDmaDaisyChain_0Core0[2] = 
{
    /* Channel IDs */
    7U,
    8U
};
/* Daisy chain 'DmaDaisyChain_ADC1_GroupSwTrig2' */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_ChannelType Dma_DaisyChainDmaDaisyChain_ADC1_GroupSwTrig2Core0[2] = 
{
    /* Channel IDs */
    13U,
    14U
};

/* Daisy chain set in Core0 */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_DaisyChainMapType Dma_DaisyChainConfigSetCore0[2] = 
{
    {
        /* Total number of daisy chain members */
        2U,
        /* Pointer to the channels that linked list is assigned */
        &Dma_DaisyChainDmaDaisyChain_0Core0[0]
    },
    {
        /* Total number of daisy chain members */
        2U,
        /* Pointer to the channels that linked list is assigned */
        &Dma_DaisyChainDmaDaisyChain_ADC1_GroupSwTrig2Core0[0]
    }
};

/* Configuration parameter of core0 */
static const Dma_CoreConfigType Dma_ConfigSetCore0 = 
{
    /* The number of channels allocated to Core0 */
    DMA_CFG_MAX_CHANNELS_CORE0,
    /* Total number of daisy chain */
    2U,
    /* Pointer to the daisy chain list */
    &Dma_DaisyChainConfigSetCore0[0],
    /* Pointer to the configuration of channels */
    &Dma_ChannelConfigCore0[0]
};


#define DMA_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"


/* Configuration informations which mapped to Core1 */
#define DMA_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"

/* Basic transfer configuration parameter of channel1: M2M_Continuous
Configuration: DmaChTransferConfig */
static const Dma_TransferConfigType Dma_TransferConfigListChannel1Core1[1] = 
{
    {
        /* The ID of the double buffer assigned to this transfer */
        255U,   /* Invalid ID */
        /* The ID of the circular buffer assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the pattern assigned to this transfer */
        255U,    /* Invalid ID */
        /* The ID of the linked list assigned to this transfer */
        255U,    /* Invalid ID */
        {
            /* Source address configuration */
            {
                /* Source address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_SrcBuf0_16bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Destination address configuration */
            {
                /* Destination address */
                /* #Violation: Dma_PBcfg_c_REF_1 */
                (uint32)Dma_DestBuf0_16bits,
                /* Auto increase or no increase */
                DMA_CHANNELADDRESSINCREMENT_INCREASE,
                /* Burst size */
                DMA_CHANNELBURSTSIZE_1
            },
            /* Transfer width(unit: bit(s)) */
            DMA_CHANNELTRANSFERWIDTH_16BIT,
            /* Flow control */
            DMA_FLOWCONTROLANDTRANSFERTYPE_DMA_M2M,
            /* Source request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Destination request configuration */
            {
                /* Local request - None */
                0U,
                /* Global multiplexer request - None */
                0U
            },
            /* Number of transfer */
            32U
        }
    }
};



/* Detail configuration parameters of all channels in core1 */
static const Dma_ChConfigType Dma_ChannelConfigCore1[DMA_CFG_MAX_CHANNELS_CORE1] = 
{
    /* Configuration parameter of DMA0 channel1 */
    /* Channel name: M2M_Continuous,  channel ID: 1 */
    {
        /* Channel ID */
        1U,
        /* Transfer configurations exists */
        TRUE,
        /* Total number of transfer configurations */
        1U,
        /* Total number of shadowing operation configurations */
        0U,
        /* Total number of linked list item configurations */
        0U,
        /* Interrupt enable bits */
        (uint8)DMA_CH_INT_ERROR| \
        (uint8)DMA_CH_INT_TC,
        /* Continuous mode is enabled */
        TRUE,
        /* Shadow operation is disabled */
        NULL_PTR,
        /* Linked list is disabled */
        NULL_PTR,
        /* Pointer to the notification function */
        DmaDemo_M2mContinuousNotif,
        /* Pointer to the transfer configuration of channel1 */
        &Dma_TransferConfigListChannel1Core1[0]
    }
};


/* Configuration parameter of core1 */
static const Dma_CoreConfigType Dma_ConfigSetCore1 = 
{
    /* The number of channels allocated to Core1 */
    DMA_CFG_MAX_CHANNELS_CORE1,
    /* Total number of daisy chain */
    0U,
    /* Pointer to the daisy chain list */
    NULL_PTR,  
    /* Pointer to the configuration of channels */
    &Dma_ChannelConfigCore1[0]
};


#define DMA_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"


/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
#define DMA_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"


/* Double buffer detail configuration parameter set
Configuration: DmaDoubleBuffer */
static const Dma_DoubleBufferConfigType Dma_DoubleBufferConfigList[1] = 
{
    {
        {
            /* Double buffer target: source or destination */
            DMA_DBSOURCEORDESTINATION_SOURCE,
            /* Double buffer switch mode: HW or HW_SW */
            DMA_DBSWITCHMODE_HW_SW,
            /* Double buffer address */
            /* #Violation: Dma_PBcfg_c_REF_1 */
            (uint32)Dma_SrcBuf1_32bits
        },
        /* Pointer to the notification when double buffer frozen */
        DmaDemo_DoubleBuffer0_Notif
    }
};


/* Circular buffer configuration parameter set
Configuration: DmaCircularBuffer */
static const Dma_CircularBufferConfig Dma_CircularBufferConfigList[1] = 
{
    {
        /* Circular buffer object: source/destination/both */
        DMA_CBSOURCEORDESTINATION_SOURCE,
        /* Size of source circular buffer */
        DMA_CBSIZE_4BYTE,
        /* Size of destination circular buffer */
        DMA_CBSIZE_NONE,
        /* Continuous when Destination circular buffer rollback event occurred */
        FALSE
    }
};


/* Pattern match configuration parameter set
Configuration: DmaPattern */
static const Dma_MatchPatternConfig Dma_PatternMatchConfigList[1] = 
{
    {
        /* Pattern match size(unit: bit(s)) */
        DMA_PATTERNSIZE_8BIT,
        /* Data used for pattern matching */
        170U,
        /* Data mask bits for pattern matching */
        0U,
        /* Stop when pattern matched */
        TRUE
    }
};

/* Common configuration for all channels and cores, contains double buffer configuration, 
circualr buffer configuration and pattern configuration */
static const Dma_CommonConfigType Dma_CommonConfigSet = 
{
    /* Pointer to the double buffer configuration address */
    &Dma_DoubleBufferConfigList[0]
    /* Pointer to the circular buffer configuration address */
    ,&Dma_CircularBufferConfigList[0]
    /* Pointer to the pattern configuration address */
    ,&Dma_PatternMatchConfigList[0]
};

/* Configuration for the core ID that DMA logical channel ID is mapped to */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_ChannelMapType Dma_ChannelMapConfig[19] =
{
    /* Logical channel ID 0, name is "M2M":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {0U, 0U, 0U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 1, name is "M2M_Continuous":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core1 */
    {1U, 0U, 0U, 255U, 255U, 255U, 255U, MCAL_CORE1},
    /* Logical channel ID 2, name is "M2M_DoubleBuf":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {2U, 0U, 1U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 3, name is "M2M_CircBuf":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {3U, 0U, 2U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 4, name is "M2M_LinkedList":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {4U, 0U, 3U, 0U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 5, name is "M2M_Shadow":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {0U, 1U, 4U, 1U, 0U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 6, name is "M2M_Pattern":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {0U, 2U, 5U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 7, name is "M2M_Daisy0":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {0U, 3U, 6U, 255U, 255U, 0U, 255U, MCAL_CORE0},
    /* Logical channel ID 8, name is "M2M_Daisy1":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {1U, 3U, 7U, 255U, 255U, 255U, 7U, MCAL_CORE0},
    /* Logical channel ID 9, name is "ADC1_Channel0":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {2U, 1U, 8U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 10, name is "ADC1_Channel1":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {3U, 1U, 9U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 11, name is "ADC1_Channel2":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {4U, 1U, 10U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 12, name is "ADC1_Channel3":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {5U, 1U, 11U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 13, name is "ADC1_Channel7":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {6U, 1U, 12U, 255U, 255U, 1U, 255U, MCAL_CORE0},
    /* Logical channel ID 14, name is "ADC1_GroupSwTrig2":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {7U, 1U, 13U, 2U, 255U, 255U, 13U, MCAL_CORE0},
    /* Logical channel ID 15, name is "SPITx":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {2U, 2U, 14U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 16, name is "SPIRx":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {3U, 2U, 15U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 17, name is "Dsadc3":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {8U, 1U, 16U, 255U, 255U, 255U, 255U, MCAL_CORE0},
    /* Logical channel ID 18, name is "ADC1_AllChToOneResReg":
    Physical channel , HW unit , channel index , 
    Transfer Index , shadowing operation index , daisy chain , daisy chain head channel in core0 */
    {9U, 1U, 17U, 255U, 255U, 255U, 255U, MCAL_CORE0}
};

/* DMA0: array index is physical channel, array member is logical channel */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_ChannelType Dma_HwToChannelConfig_DMA0[8] = 
{
    0U,
    1U,
    2U,
    3U,
    4U,
    255U,
    255U,
    255U
};
/* DMA1: array index is physical channel, array member is logical channel */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_ChannelType Dma_HwToChannelConfig_DMA1[40] = 
{
    5U,
    255U,
    9U,
    10U,
    11U,
    12U,
    13U,
    14U,
    17U,
    18U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U
};
/* DMA2: array index is physical channel, array member is logical channel */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_ChannelType Dma_HwToChannelConfig_DMA2[8] = 
{
    6U,
    255U,
    15U,
    16U,
    255U,
    255U,
    255U,
    255U
};
/* DMA3: array index is physical channel, array member is logical channel */
/* #Violation: Dma_PBcfg_c_REF_3 */
/* #Violation: Dma_PBcfg_c_REF_4 */
static const Dma_ChannelType Dma_HwToChannelConfig_DMA3[8] = 
{
    7U,
    8U,
    255U,
    255U,
    255U,
    255U,
    255U,
    255U
};


/* Configuration for used HW unit list */
static const Dma_HwUnitType Dma_HwUnitUsedList[4] = 
{
    0U,
    1U,
    2U,
    3U
};

/* Configuration for the HW units */
static const Dma_HwUnitConfigType Dma_HwUnitConfig = 
{
    /* The number of HW units used in the Tresos configured */
    4U,
    /* Pointer to the list of all used HW units */
    &Dma_HwUnitUsedList[0],
    /* List of HW unit and physical channel to logical channel */
    {
        /* Pointer to the mapping relationship from physical channel ID to logical channel ID 
        for DMA0 */
        &Dma_HwToChannelConfig_DMA0[0],
        /* Pointer to the mapping relationship from physical channel ID to logical channel ID 
        for DMA1 */
        &Dma_HwToChannelConfig_DMA1[0],
        /* Pointer to the mapping relationship from physical channel ID to logical channel ID 
        for DMA2 */
        &Dma_HwToChannelConfig_DMA2[0],
        /* Pointer to the mapping relationship from physical channel ID to logical channel ID 
        for DMA3 */
        &Dma_HwToChannelConfig_DMA3[0]
    }
};

/* Dma configuration set parameters */
const Dma_ConfigType Dma_ConfigSet[DMA_CONFIGSET_CNT] =
{
    {
        /* Configuration for each core */
        {
            /* Dma configuration of core0 */
            &Dma_ConfigSetCore0,
            /* Dma configuration of core1 */
            &Dma_ConfigSetCore1
        },
        /* Pointer to Dma common configuration set address */
        &Dma_CommonConfigSet,
        /* Pointer to the configuration that maps Dma channel to core */
        &Dma_ChannelMapConfig[0],
        /* Pointer to the configuration for the HW unit */
        &Dma_HwUnitConfig
    }
};

#define DMA_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Dma_PBcfg_c_REF_2 */
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

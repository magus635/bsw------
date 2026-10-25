/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dma_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DMA
*
*   brief                 : This file contains Demo application for Dma Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dma_Demo.h"
#include "Demo_Common.h"
#include "Dma.h"
#include "Intc.h"

/****************************************************************************************************
**                          Private Type Definitions                                               **
****************************************************************************************************/


/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define DMA_DEMO_MAX_TIMEOUT                         (1000U)

/* Macro for continuous demo */
/* Number of channel transfer pause */
#define DMA_DEMO_PAUSE_CONTINUOUS_TRANS_NUM          (5U)
/* Number of channel transfer stop */
#define DMA_DEMO_CALCEL_CONTINUOUS_TRANS_NUM         (10U)

/* Macro for linked list demo */
#define DMA_DEMO_LINKEDLIST_LEN                      (1U)

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/* Core0 */
#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Dma_MemMap.h"

static uint8 Dma_DemoInitStatusCore0;

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Dma_MemMap.h"

/* Core1 */
#define DMA_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Dma_MemMap.h"

static uint8 Dma_DemoInitStatusCore1;

#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Dma_MemMap.h"


/* Core Global variables */
#define DMA_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dma_MemMap.h"

static Demo_CoreExeType Dma_DemoCoreExeFlag = {MCAL_CORE0, 0xFFU, DEMO_IDLE};

#define DMA_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dma_MemMap.h"


#define DMA_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dma_MemMap.h"

ALIGNED(4) uint8 Dma_SrcBuf0_8bits[DMA_DEMO_MAX_DATA_SIZE];
ALIGNED(4) uint8 Dma_DestBuf0_8bits[DMA_DEMO_MAX_DATA_SIZE];

uint16 Dma_SrcBuf0_16bits[DMA_DEMO_MAX_DATA_SIZE];
uint16 Dma_DestBuf0_16bits[DMA_DEMO_MAX_DATA_SIZE];

uint32 Dma_SrcBuf0_32bits[DMA_DEMO_MAX_DATA_SIZE];
uint32 Dma_SrcBuf1_32bits[DMA_DEMO_MAX_DATA_SIZE];
uint32 Dma_DestBuf0_32bits[DMA_DEMO_MAX_DATA_SIZE];


static uint8 DmaDemo_Continuous_Cnt;
static uint8 DmaDemo_DoubleBuffer_Cnt;
static uint8 DmaDemo_LinkedList_Cnt;
static uint8 DmaDemo_ShadowOprt_Cnt;

static boolean DmaDemo_PatternMatchFlag;
static boolean DmaDemo_DaisyChainTriggFlag;

static boolean DmaDemo_MasterCoreInitFlag;
#define DMA_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dma_MemMap.h"

#define DMA_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Dma_MemMap.h"

/* Initialize status of demo */
static uint8 * const Dma_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES] =
{
    &Dma_DemoInitStatusCore0,
    &Dma_DemoInitStatusCore1
};

#define DMA_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Dma_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#define DMA_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dma_MemMap.h"

static void Dma_MemoryToMemoryDemo(void);
static void Dma_MemoryToMemoryContinuousDemo(void);
static void Dma_MemoryToMemoryDoubleBufferDemo(void);
static void Dma_MemoryToMemoryCircularBufferDemo(void);
static void Dma_MemoryToMemoryLinkedListDemo(void);
static void Dma_MemoryToMemoryShadowDemo(void);
static void Dma_MemoryToMemoryPatternDemo(void);
static void Dma_MemoryToMemoryDaisyChainDemo(void);
static void Dma_MemoryToMemoryManualUpdateDemo(void);

/****************************************************************************************************
**                          Global Function Declarations                                          **
****************************************************************************************************/
void DmaDemo_M2mContinuousNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
void DmaDemo_M2mLinkedListNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
void DmaDemo_M2mShadowNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
void DmaDemo_M2mPatternNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
void DmaDemo_M2mDaisyChain0Notif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
void DmaDemo_M2mDaisyChain1Notif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt);
void DmaDemo_DoubleBuffer0_Notif(Dma_ChannelType Channel, Dma_DblFrznStatusType FrozenStatus);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Dma_MemoryToMemoryDemo
*
*   Service ID              : None.
*
*   Description             : One-shot mode memory to memory transfer, data length - 32,
*                             data width - 8bits.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Dma_MemoryToMemoryDemo(void)
{
    uint32 DataCnt;
    uint32 LoopCnt = 0U;
    uint32 ChStatus;
    uint8  TestResult;

    /* Initialize the source buffer */
    for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
    {
        Dma_SrcBuf0_8bits[DataCnt] = (uint8)DataCnt;
        /* Reset destination buffer */
        Dma_DestBuf0_8bits[DataCnt] = 0U;
    }

    /* Start channel to memory to memory transfer */
    Dma_ChannelStart(DmaConf_DmaChannel_M2M);

    /* Check Dma memory to memory transfer status */
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);
        ChStatus = Dma_GetChannelStatus(DmaConf_DmaChannel_M2M);
    } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) && (ChStatus != (uint32)DMA_CH_TRANSFER_COMPLETE));

    if ((uint32)DMA_CH_TRANSFER_COMPLETE == ChStatus)
    {
        TestResult = 0U;

        /* Check if the data after transfer is correct */
        for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
        {
            if (Dma_SrcBuf0_8bits[DataCnt] != Dma_DestBuf0_8bits[DataCnt])
            {
                /* data incorrect */
                TestResult = 2U;
                break;
            }
        }
    }
    else
    {
        TestResult = 1U;
    }

    if (0U == TestResult)
    {
        /* Data transfer is successfully */
        DEBUG_PRINTF("\nPASS");
    }
    else
    {
        /* Stop channel */
        Dma_ChannelCancel(DmaConf_DmaChannel_M2M, DMA_CH_CANCEL_DIRECT);
        switch (TestResult)
        {
            case 1U: DEBUG_PRINTF("\nTimeout"); break;
            case 2U: DEBUG_PRINTF("\nTransferred data mismatch"); break;
            default: /* Do Nothing */break;
        }
        DEBUG_PRINTF("\nFAILED");
    }
}

/****************************************************************************************************
*   Function Name           : Dma_MemoryToMemoryContinuousDemo
*
*   Service ID              : None.
*
*   Description             : Continuous mode for memory to memory transfer, data length - 32,
*                             data width - 16bits.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Dma_MemoryToMemoryContinuousDemo(void)
{
    uint32 DataCnt;
    uint32 LoopCnt;
    uint8 TestResult;

    /* Initialize the source buffer */
    for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
    {
        Dma_SrcBuf0_16bits[DataCnt] = (uint16)(DataCnt << 8U);
        /* Reset destination buffer */
        Dma_DestBuf0_16bits[DataCnt] = 0U;
    }
    DmaDemo_Continuous_Cnt = 0U;

    /* Start channel to memory to memory transfer */
    Dma_ChannelStart(DmaConf_DmaChannel_M2M_Continuous);

    /* Check Dma memory to memory transfer status */
    LoopCnt = 0U;
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);
    } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) &&
             (DmaDemo_Continuous_Cnt < DMA_DEMO_PAUSE_CONTINUOUS_TRANS_NUM));

    /* The data was transferred 5 times */
    if (DMA_DEMO_PAUSE_CONTINUOUS_TRANS_NUM <= DmaDemo_Continuous_Cnt)
    {
        /* Waiting for 10ms */
        Timer_DelayMs(10);

        /* Ensure the Dma transfer is paused */
        if (DMA_DEMO_PAUSE_CONTINUOUS_TRANS_NUM <= DmaDemo_Continuous_Cnt)
        {
#if !(defined(THA6_THA6206) || defined(THA6_THA6206D))
            /* THA6206 and THA6206D do not support suspend and resume operation */
            /* Resume the transfer */
            Dma_ChannelResume(DmaConf_DmaChannel_M2M_Continuous);
#endif /* !(defined(THA6_THA6206) || defined(THA6_THA6206D)) */

            /* Check Dma memory to memory transfer status */
            LoopCnt = 0U;
            do
            {
                LoopCnt++;
                Timer_DelayMs(1);
            } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) &&
                     (DmaDemo_Continuous_Cnt < DMA_DEMO_CALCEL_CONTINUOUS_TRANS_NUM));

            /* The data was transferred 10 times */
            if (DMA_DEMO_CALCEL_CONTINUOUS_TRANS_NUM <= DmaDemo_Continuous_Cnt)
            {
                TestResult = 0U;
                /* Check if the data after transfer is correct */
                for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
                {
                    if (Dma_SrcBuf0_16bits[DataCnt] != Dma_DestBuf0_16bits[DataCnt])
                    {
                        /* data incorrect */
                        TestResult = 2U;
                        break;
                    }
                }
            }
            else
            {
                TestResult = 1U;
            }
        }
        else
        {
            TestResult = 3U;
        }
    }
    else
    {
        TestResult = 1U;
    }

    if (0U == TestResult)
    {
        /* Data transfer is successfully */
        DEBUG_PRINTF("\nPASS");
    }
    else
    {
        /* Stop channel */
        Dma_ChannelCancel(DmaConf_DmaChannel_M2M_Continuous, DMA_CH_CANCEL_DIRECT);

        switch (TestResult)
        {
            case 1U: DEBUG_PRINTF("\nTimeout"); break;
            case 2U: DEBUG_PRINTF("\nTransferred data mismatch"); break;
            case 3U: DEBUG_PRINTF("\nUnexpect Interrupt Trigger"); break;
            default: /* Do Nothing */break;
        }
        DEBUG_PRINTF("\nFAILED");
    }
}

/****************************************************************************************************
*   Function Name           : Dma_MemoryToMemoryDoubleBufferDemo
*
*   Service ID              : None.
*
*   Description             : Double buffer mode for memory to memory transfer,
*                             data length - 32, data width - 32bits.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Dma_MemoryToMemoryDoubleBufferDemo(void)
{
    uint32 DataCnt;
    uint32 LoopCnt;
    uint8  TestResult = 0U;

    /* Initialize the source buffer */
    for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
    {
        Dma_SrcBuf0_32bits[DataCnt] = (uint32)(DataCnt << 16U);
        Dma_SrcBuf1_32bits[DataCnt] = (uint32)(DataCnt << 16U) + 1U;
        /* Reset destination buffer */
        Dma_DestBuf0_32bits[DataCnt] = 0U;
    }
    DmaDemo_DoubleBuffer_Cnt = 0U;

    /* Start channel to memory to memory transfer */
    Dma_ChannelStart(DmaConf_DmaChannel_M2M_DoubleBuf);

    /* Check Dma memory to memory transfer status */
    LoopCnt = 0U;
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);
    } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) && (1U > DmaDemo_DoubleBuffer_Cnt));

    if (1U == DmaDemo_DoubleBuffer_Cnt)
    {
        for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
        {
            if (Dma_DestBuf0_32bits[DataCnt] != Dma_SrcBuf1_32bits[DataCnt])
            {
                TestResult = 2U;
                break;
            }
        }
    }
    else
    {
        /* Timeout */
        TestResult = 1U;
    }


    if (0U == TestResult)
    {
        /* Data transfer is successfully */
        DEBUG_PRINTF("\nPASS");
    }
    else
    {
        if (2U != TestResult)
        {
            /* Stop channel */
            Dma_ChannelCancel(DmaConf_DmaChannel_M2M_DoubleBuf, DMA_CH_CANCEL_DIRECT);
        }
        switch (TestResult)
        {
            case 1U: DEBUG_PRINTF("\nTimeout"); break;
            case 2U: DEBUG_PRINTF("\nTransferred data mismatch"); break;
            default: /* Do Nothing */break;
        }

        DEBUG_PRINTF("\nFAILED");
    }
}

/****************************************************************************************************
*   Function Name           : Dma_MemoryToMemoryCircularBufferDemo
*
*   Service ID              : None.
*
*   Description             : Circular buffer mode for memory to memory transfer,
*                             data length - 32, data width - 8bits.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Dma_MemoryToMemoryCircularBufferDemo(void)
{
    uint32 DataCnt;
    uint32 DataLoop;
    uint32 LoopCnt = 0U;
    uint32 ChStatus;
    uint8  TestResult;

    /* Initialize the source buffer */
    for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
    {
        Dma_SrcBuf0_8bits[DataCnt] = (uint8)DataCnt;
        /* Reset destination buffer */
        Dma_DestBuf0_8bits[DataCnt] = 0U;
    }

    /* Start channel to memory to memory transfer */
    Dma_ChannelStart(DmaConf_DmaChannel_M2M_CircBuf);

    /* Check Dma memory to memory transfer status */
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);
        ChStatus = Dma_GetChannelStatus(DmaConf_DmaChannel_M2M_CircBuf);
    } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) && (ChStatus != (uint32)DMA_CH_TRANSFER_COMPLETE));

    if ((uint32)DMA_CH_TRANSFER_COMPLETE == ChStatus)
    {
        TestResult = E_OK;
        /* Initialize the source buffer */
        for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
        {
            DataLoop = (uint32)(DataCnt % 4U);
            if (Dma_SrcBuf0_8bits[DataLoop] != Dma_DestBuf0_8bits[DataCnt])
            {
                TestResult = 2U;
                break;
            }
        }
    }
    else
    {
        TestResult = 1U;
    }

    /* Stop channel */
    Dma_ChannelCancel(DmaConf_DmaChannel_M2M_CircBuf, DMA_CH_CANCEL_DIRECT);

    if (0U == TestResult)
    {
        /* Data transfer is successfully */
        DEBUG_PRINTF("\nPASS");
    }
    else
    {
        switch (TestResult)
        {
            case 1U: DEBUG_PRINTF("\nTimeout"); break;
            case 2U: DEBUG_PRINTF("\nTransferred data mismatch"); break;
            default: /* Do Nothing */break;
        }
        DEBUG_PRINTF("\nFAILED");
    }
}

/****************************************************************************************************
*   Function Name           : Dma_MemoryToMemoryLinkedListDemo
*
*   Service ID              : None.
*
*   Description             : Linked list mode for memory to memory transfer,
*                             linked list length - 3.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Dma_MemoryToMemoryLinkedListDemo(void)
{
    uint32 DataCnt;
    uint32 LoopCnt = 0U;
    Std_ReturnType TestResult = 0U;

    /* Initialize the source buffer */
    for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
    {
        Dma_SrcBuf0_8bits[DataCnt] = (uint8)DataCnt;
        /* Reset destination buffer */
        Dma_DestBuf0_8bits[DataCnt] = 0U;

        Dma_SrcBuf0_16bits[DataCnt] = (uint16)(DataCnt << 8U);
        /* Reset destination buffer */
        Dma_DestBuf0_16bits[DataCnt] = 0U;

        Dma_SrcBuf0_32bits[DataCnt] = (uint32)(DataCnt << 16U);
        /* Reset destination buffer */
        Dma_DestBuf0_32bits[DataCnt] = 0U;
    }
    DmaDemo_LinkedList_Cnt = 0U;

    /* Only transfer2 support the linked list function, so first switch the
     * configuration to transfer2 */
    Dma_ChannelUpdate(DmaConf_DmaChannel_M2M_LinkedList,
                      DmaConf_DmaChTransferConfig_LinkedListTransfer2);

    /* Start channel to memory to memory transfer */
    Dma_ChannelStart(DmaConf_DmaChannel_M2M_LinkedList);

    /* Check Dma memory to memory transfer status */
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);
    } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) && (DMA_DEMO_LINKEDLIST_LEN > DmaDemo_LinkedList_Cnt));

    if (DMA_DEMO_LINKEDLIST_LEN == DmaDemo_LinkedList_Cnt)
    {
        for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
        {
            if (Dma_SrcBuf0_8bits[DataCnt] != Dma_DestBuf0_8bits[DataCnt])
            {
                TestResult = 2U;
                break;
            }
            if (Dma_SrcBuf0_16bits[DataCnt] != Dma_DestBuf0_16bits[DataCnt])
            {
                TestResult = 3U;
                break;
            }
            if (Dma_SrcBuf0_32bits[DataCnt] != Dma_DestBuf0_32bits[DataCnt])
            {
                TestResult = 4U;
                break;
            }
        }
    }
    else
    {
        TestResult = 1U;
    }

    /* Stop channel */
    Dma_ChannelCancel(DmaConf_DmaChannel_M2M_LinkedList, DMA_CH_CANCEL_DIRECT);
    /* Resume transfer 0(Default) */
    Dma_ChannelUpdate(DmaConf_DmaChannel_M2M_LinkedList,
                      DmaConf_DmaChTransferConfig_LinkedListTransfer0);

    if (0U == TestResult)
    {
        /* Data transfer is successfully */
        DEBUG_PRINTF("\nPASS");
    }
    else
    {
        switch (TestResult)
        {
            case 1U: DEBUG_PRINTF("\nTimeout"); break;
            case 2U: DEBUG_PRINTF("\nTransferred data of Linked list element1 mismatch"); break;
            case 3U: DEBUG_PRINTF("\nTransferred data of Linked list element2 mismatch"); break;
            case 4U: DEBUG_PRINTF("\nTransferred data of Linked list element3 mismatch"); break;
            default: /* Do Nothing */break;
        }
        DEBUG_PRINTF("\nFAILED");
    }
}

/****************************************************************************************************
*   Function Name           : Dma_MemoryToMemoryShadowDemo
*
*   Service ID              : None.
*
*   Description             : Shadowing mode for memory to memory transfer.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Dma_MemoryToMemoryShadowDemo(void)
{
    
    uint32 DataCnt;
    uint32 LoopCnt = 0U;
    uint8  TestResult = 0U;

    /* Initialize the source buffer */
    for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
    {
        Dma_SrcBuf0_8bits[DataCnt] = (uint8)DataCnt;
        /* Reset destination buffer */
        Dma_DestBuf0_8bits[DataCnt] = 0U;

        Dma_SrcBuf0_16bits[DataCnt] = (uint16)(DataCnt << 8U);
        /* Reset destination buffer */
        Dma_DestBuf0_16bits[DataCnt] = 0U;

        Dma_SrcBuf0_32bits[DataCnt] = (uint32)(DataCnt << 16U);
        /* Reset destination buffer */
        Dma_DestBuf0_32bits[DataCnt] = 0U;
    }
    DmaDemo_ShadowOprt_Cnt = 0U;

    /* Start channel to memory to memory transfer */
    Dma_ChannelStart(DmaConf_DmaChannel_M2M_Shadow);

    /* Check Dma memory to memory transfer status */
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);
    } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) && (2U > DmaDemo_ShadowOprt_Cnt));

    if (2U == DmaDemo_ShadowOprt_Cnt)
    {
        for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
        {
            if (Dma_SrcBuf0_8bits[DataCnt] != Dma_DestBuf0_8bits[DataCnt])
            {
                TestResult = 2U;
                break;
            }
            if (Dma_SrcBuf0_16bits[DataCnt] != Dma_DestBuf0_16bits[DataCnt])
            {
                TestResult = 2U;
                break;
            }
        }
        if (0U == TestResult)
        {
            /* Switch to another shadow configuration */
            Dma_ChannelShadowingUpdate(DmaConf_DmaChannel_M2M_Shadow,
                                    DmaConf_DmaChShadowConfig_DmaChShadowConfig_1);
            /* Delay 1ms to ensure that the shadowing operation is completed */
            Timer_DelayMs(1U);
#if !(defined(THA6_THA6206) || defined(THA6_THA6206D))
            /* THA6206 and THA6206D do not support suspend and resume operation */
            /* Resume the transfer */
            Dma_ChannelResume(DmaConf_DmaChannel_M2M_Shadow);

            /* Check Dma memory to memory transfer status */
            do
            {
                LoopCnt++;
                Timer_DelayMs(1);
            } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) && (4U > DmaDemo_ShadowOprt_Cnt));
#else
            DmaDemo_ShadowOprt_Cnt = 4U;
#endif /* !(defined(THA6_THA6206) || defined(THA6_THA6206D)) */

            if (4U == DmaDemo_ShadowOprt_Cnt)
            {
                for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
                {
                    if (Dma_SrcBuf0_32bits[DataCnt] != Dma_DestBuf0_32bits[DataCnt])
                    {
                        TestResult = 3U;
                        break;
                    }
                }
            }
            else
            {
                TestResult = 4U;
            }
        }
    }
    else
    {
        TestResult = 1U;
    }

    /* Switch the shadowing configuration to ID0, that is default */
    Dma_ChannelShadowingUpdate(DmaConf_DmaChannel_M2M_Shadow,
                            DmaConf_DmaChShadowConfig_DmaChShadowConfig_0);

    if (E_OK == TestResult)
    {
        /* Data transfer is successfully */
        DEBUG_PRINTF("\nPASS");
    }
    else
    {
        if ((4U == TestResult))
        {
            Dma_ChannelCancel(DmaConf_DmaChannel_M2M_Shadow, DMA_CH_CANCEL_DIRECT);
        }
        /* Stop channel */
        switch (TestResult)
        {
            case 3U:
            case 1U: DEBUG_PRINTF("\nTimeout"); break;
            case 4U:
            case 2U: DEBUG_PRINTF("\nTransferred data mismatch"); break;
            default: /* Do Nothing */break;
        }

        DEBUG_PRINTF("\nFAILED");
    }
}

/****************************************************************************************************
*   Function Name           : Dma_MemoryToMemoryPatternDemo
*
*   Service ID              : None.
*
*   Description             : Pattern mode for memory to memory transfer. match data is 0xAA and
*                             data matched stop enabled.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Dma_MemoryToMemoryPatternDemo(void)
{
    uint32 DataCnt;
    uint32 LoopCnt = 0U;
    uint8  TestResult = 0U;

    /* Initialize the source buffer */
    for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
    {
        Dma_SrcBuf0_8bits[DataCnt] = (uint8)((uint8)DataCnt + 0xA0U);
        /* Reset destination buffer */
        Dma_DestBuf0_8bits[DataCnt] = 0U;
    }
    DmaDemo_PatternMatchFlag = FALSE;

    /* Start channel to memory to memory transfer */
    Dma_ChannelStart(DmaConf_DmaChannel_M2M_Pattern);

    /* Check Dma memory to memory transfer status */
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);
    } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) && (TRUE != DmaDemo_PatternMatchFlag));

    if (TRUE == DmaDemo_PatternMatchFlag)
    {
        /* Do Nothing */
        for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
        {
            if (Dma_SrcBuf0_8bits[DataCnt] != Dma_DestBuf0_8bits[DataCnt])
            {
                TestResult = 2U;
                break;
            }
            if (0xAAU == Dma_DestBuf0_8bits[DataCnt])
            {
                /* 0xAA is match data, data matched then return */
                break;
            }
        }
    }
    else
    {
        TestResult = 1U;
    }

    if (0U == TestResult)
    {
        /* Data transfer is successfully */
        DEBUG_PRINTF("\nPASS");
    }
    else
    {
        /* Stop channel */
        Dma_ChannelCancel(DmaConf_DmaChannel_M2M_Pattern, DMA_CH_CANCEL_DIRECT);

        switch (TestResult)
        {
            case 1U: DEBUG_PRINTF("\nTimeout"); break;
            case 2U: DEBUG_PRINTF("\nTransferred data mismatch"); break;
            default: /* Do Nothing */break;
        }
        DEBUG_PRINTF("\nFAILED");
    }
}

/****************************************************************************************************
*   Function Name           : Dma_MemoryToMemoryDaisyChainDemo
*
*   Service ID              : None.
*
*   Description             : Daisy chain mode for memory to memory transfer.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Dma_MemoryToMemoryDaisyChainDemo(void)
{
    uint32 DataCnt;
    uint32 LoopCnt = 0U;
    uint8  TestResult = 0U;

    /* Initialize the source buffer */
    for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
    {
        Dma_SrcBuf0_8bits[DataCnt] = (uint8)DataCnt;
        /* Reset destination buffer */
        Dma_DestBuf0_8bits[DataCnt] = 0U;

        Dma_SrcBuf0_16bits[DataCnt] = (uint8)DataCnt;
        /* Reset destination buffer */
        Dma_DestBuf0_16bits[DataCnt] = 0U;
    }
    DmaDemo_DaisyChainTriggFlag = FALSE;

    /* Start channel to memory to memory transfer */
    Dma_ChannelStart(DmaConf_DmaChannel_M2M_Daisy0);

    /* Check Dma memory to memory transfer status */
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);
    } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) && (TRUE != DmaDemo_DaisyChainTriggFlag));

    if (TRUE == DmaDemo_DaisyChainTriggFlag)
    {
        for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
        {
            if (Dma_SrcBuf0_8bits[DataCnt] != Dma_DestBuf0_8bits[DataCnt])
            {
                TestResult = 2U;
                break;
            }

            if (Dma_SrcBuf0_16bits[DataCnt] != Dma_DestBuf0_16bits[DataCnt])
            {
                TestResult = 2U;
                break;
            }
        }
    }
    else
    {
        TestResult = 1U;
    }

    if (0U == TestResult)
    {
        /* Data transfer is successfully */
        DEBUG_PRINTF("\nPASS");
    }
    else
    {
        /* Stop channel */
        Dma_ChannelCancel(DmaConf_DmaChannel_M2M_Daisy0, DMA_CH_CANCEL_DIRECT);
        Dma_ChannelCancel(DmaConf_DmaChannel_M2M_Daisy1, DMA_CH_CANCEL_DIRECT);
        switch (TestResult)
        {
            case 1U: DEBUG_PRINTF("\nTimeout"); break;
            case 2U: DEBUG_PRINTF("\nTransferred data mismatch"); break;
            default: /* Do Nothing */break;
        }
        DEBUG_PRINTF("\nFAILED");
    }
}

/****************************************************************************************************
*   Function Name           : Dma_MemoryToMemoryManualUpdateDemo
*
*   Service ID              : None.
*
*   Description             : Manual update mode memory to memory transfer.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Dma_MemoryToMemoryManualUpdateDemo(void)
{
    uint32 DataCnt;
    uint32 LoopCnt = 0U;
    uint32 ChStatus;
    uint8  TestResult;
    Dma_ChannelTransferType ChannelTransferConfig;

    /* Initialize the source buffer */
    for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
    {
        Dma_SrcBuf0_16bits[DataCnt] = (uint16)DataCnt;
        /* Reset destination buffer */
        Dma_DestBuf0_16bits[DataCnt] = 0U;
    }

    /* Change the transfer data */
    ChannelTransferConfig.Source.address = (uint32)&Dma_SrcBuf0_16bits[0U];
    ChannelTransferConfig.Source.increment = DMA_CHANNELADDRESSINCREMENT_INCREASE;
    ChannelTransferConfig.Source.burstSize = DMA_CHANNELBURSTSIZE_1;
    ChannelTransferConfig.Destination.address = (uint32)&Dma_DestBuf0_16bits[0U];
    ChannelTransferConfig.Destination.increment = DMA_CHANNELADDRESSINCREMENT_INCREASE;
    ChannelTransferConfig.Destination.burstSize = DMA_CHANNELBURSTSIZE_1;
    ChannelTransferConfig.TransferWidth = DMA_CHANNELTRANSFERWIDTH_16BIT;
    ChannelTransferConfig.TransferSize = DMA_DEMO_MAX_DATA_SIZE;

    /* The channel transfer configuration is updated using user-defined parameters */
    Dma_ChannelUpdateManual(DmaConf_DmaChannel_M2M, &ChannelTransferConfig);

    /* Start channel to memory to memory transfer */
    Dma_ChannelStart(DmaConf_DmaChannel_M2M);

    /* Check Dma memory to memory transfer status */
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);
        ChStatus = Dma_GetChannelStatus(DmaConf_DmaChannel_M2M);
    } while ((LoopCnt < DMA_DEMO_MAX_TIMEOUT) && (ChStatus != (uint32)DMA_CH_TRANSFER_COMPLETE));

    if ((uint32)DMA_CH_TRANSFER_COMPLETE == ChStatus)
    {
        TestResult = 0U;

        /* Check if the data after transfer is correct */
        for (DataCnt = 0U; DataCnt < DMA_DEMO_MAX_DATA_SIZE; DataCnt++)
        {
            if (Dma_SrcBuf0_16bits[DataCnt] != Dma_DestBuf0_16bits[DataCnt])
            {
                /* data incorrect */
                TestResult = 2U;
                break;
            }
        }
    }
    else
    {
        TestResult = 1U;
    }

    if (0U == TestResult)
    {
        /* Data transfer is successfully */
        DEBUG_PRINTF("\nPASS");
    }
    else
    {
        /* Stop channel */
        Dma_ChannelCancel(DmaConf_DmaChannel_M2M, DMA_CH_CANCEL_DIRECT);
        switch (TestResult)
        {
            case 1U: DEBUG_PRINTF("\nTimeout"); break;
            case 2U: DEBUG_PRINTF("\nTransferred data mismatch"); break;
            default: /* Do Nothing */break;
        }
        DEBUG_PRINTF("\nFAILED");
    }
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : Dma_DemoEntry
*
*   Service ID              : None.
*
*   Description             : DMA demo entry.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Dma_DemoEntry(void)
{
    char Cmd;
    uint8 ExitFlag;
    Std_VersionInfoType Dma_Ver;

    Dma_Init(&Dma_ConfigSet[0]);
    DmaDemo_MasterCoreInitFlag = TRUE;
    Dma_DemoCoreExeFlag.DemoStartupFlg = DEMO_STARTED;

    ExitFlag = 0U;
    while (0U == ExitFlag)
    {
       Dma_GetVersionInfo(&Dma_Ver);
       DEBUG_PRINTF("\n\n\n");
       DEBUG_PRINTF("\n/*********************************************************/");
       DEBUG_PRINTF("\n           DMA DRIVER DEMO MENU V%02d.%02d.%02d            ",
               Dma_Ver.sw_major_version, Dma_Ver.sw_minor_version, Dma_Ver.sw_patch_version);
       DEBUG_PRINTF("\n                                                         ");
       DEBUG_PRINTF("\n  <1> : Start to Memory to memory transfer in Core0. ");

#if defined(THA6_THA6104)
       DEBUG_PRINTF("\n  <2> : Start to Memory to memory transfer with continuous mode in Core0. ");
#else /* not defined(THA6_THA6104) */
       DEBUG_PRINTF("\n  <2> : Start to Memory to memory transfer with continuous mode in Core1. ");
#endif /* defined(THA6_THA6104) */
       DEBUG_PRINTF("\n  <3> : Start to Memory to memory transfer with double buffer in Core0. ");
       DEBUG_PRINTF("\n  <4> : Start to Memory to memory transfer with circular buffer in Core0. ");
       DEBUG_PRINTF("\n  <5> : Start to Memory to memory transfer with linked list in Core0. ");
       DEBUG_PRINTF("\n  <6> : Start to Memory to memory transfer with shadow operation in Core0. ");
       DEBUG_PRINTF("\n  <7> : Start to Memory to memory transfer with data match pattern in Core0. ");
       DEBUG_PRINTF("\n  <8> : Start to Memory to memory transfer with daisy chain in Core0. ");
       DEBUG_PRINTF("\n  <9> : Start to Memory to memory transfer with manual update in Core0. ");
       DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
       DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

       Cmd = DEBUG_GETC();
       switch (Cmd)
       {
           case '1':
           case '3':
           case '4':
           case '5':
           case '6':
           case '7':
           case '8':
           case '9':
           {
               /* Core 0 demo */
               Dma_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
               Dma_DemoCoreExeFlag.ExeCmdId = (uint8)Cmd - (uint8)'0';
               break;
           }
           case '2':
           {
#if defined(THA6_THA6104)
               /* Core 0 demo */
               Dma_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
#else /* not defined(THA6_THA6104) */
               /* Core 1 demo */
               Dma_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE1;
#endif /* defined(THA6_THA6104) */
               Dma_DemoCoreExeFlag.ExeCmdId = (uint8)Cmd - (uint8)'0';
               break;
           }
           case 'X':
           case 'x':
           {
               ExitFlag = 1U;
               Dma_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
               Dma_DemoCoreExeFlag.ExeCmdId = 255U;
               Dma_DemoCoreExeFlag.DemoStartupFlg = DEMO_IDLE;

               Timer_DelayMs(200);

               Dma_DeInit();
               DmaDemo_MasterCoreInitFlag = FALSE;
               break;
           }
           default:
           {
               DEBUG_PRINTF("\n\n  INVALID OPTION\n");
               break;
           }
       }

        if (0xFFU != Dma_DemoCoreExeFlag.ExeCmdId)
        {
            if (MCAL_CORE0 == Dma_DemoCoreExeFlag.ExeCmdCore)
            {
                /* Call Dma_Demo direct in Core 0 */
                Dma_Demo();
            }

            while(0xFFU != Dma_DemoCoreExeFlag.ExeCmdId)
            {
                /* Waiting till Dma demo test finished */
            }
        }
    }
}

/****************************************************************************************************
*   Function Name           : Dma_Demo
*
*   Service ID              : None.
*
*   Description             : This API shall be called by core which need to driver Dma.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void Dma_Demo(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    if (DEMO_STARTED == Dma_DemoCoreExeFlag.DemoStartupFlg)
    {
        if (0U == *Dma_DemoCoreInitStatus[CoreId])
        {
            if ((TRUE == DmaDemo_MasterCoreInitFlag) && (MCAL_MASTER_CORE != CoreId))
            {
                /* Initialize the Dma in each core */
                Dma_Init(&Dma_ConfigSet[0]);
                *Dma_DemoCoreInitStatus[CoreId] = 1U;
            }
        }
    }
    else
    {
        if (1U == *Dma_DemoCoreInitStatus[CoreId])
        {
            /* De-Initialize the Dma in each core */
            Dma_DeInit();
            *Dma_DemoCoreInitStatus[CoreId] = 0U;
        }
    }

    if ((Dma_DemoCoreExeFlag.ExeCmdCore == CoreId) && (0xFFU != Dma_DemoCoreExeFlag.ExeCmdId))
    {
        switch (Dma_DemoCoreExeFlag.ExeCmdId)
        {
            case 1U:
            {
                Dma_MemoryToMemoryDemo();
                break;
            }
            case 2U:
            {
                Dma_MemoryToMemoryContinuousDemo();
                break;
            }
            case 3U:
            {
                Dma_MemoryToMemoryDoubleBufferDemo();
                break;
            }
            case 4U:
            {
                Dma_MemoryToMemoryCircularBufferDemo();
                break;
            }
            case 5U:
            {
                Dma_MemoryToMemoryLinkedListDemo();
                break;
            }
            case 6U:
            {
                Dma_MemoryToMemoryShadowDemo();
                break;
            }
            case 7U:
            {
                Dma_MemoryToMemoryPatternDemo();
                break;
            }
            case 8U:
            {
                Dma_MemoryToMemoryDaisyChainDemo();
                break;
            }
            case 9U:
            {
                Dma_MemoryToMemoryManualUpdateDemo();
                break;
            }
            default:
            {
                /* Do Nothing */
                break;
            }
        }

        if (0xFEU > Dma_DemoCoreExeFlag.ExeCmdId)
        {
            Dma_DemoCoreExeFlag.ExeCmdId = 0xFFU;
            Dma_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
        }
    }
}

/****************************************************************************************************
*   Function Name           : Demo_xxxNotif
*
*   Service ID              : None.
*
*   Description             : Notification function
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
void DmaDemo_M2mContinuousNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt)
{
    (void)Channel;
    if (DMA_CH_INT_TC == ChIntEvt)
    {
        DmaDemo_Continuous_Cnt++;

        if (DmaDemo_Continuous_Cnt == DMA_DEMO_PAUSE_CONTINUOUS_TRANS_NUM)
        {
#if !(defined(THA6_THA6206) || defined(THA6_THA6206D))
            /* THA6206 and THA6206D do not support suspend and resume operation */
            /* Paused channel transfer */
            Dma_ChannelSuspend(DmaConf_DmaChannel_M2M_Continuous);
#endif /* !(defined(THA6_THA6206) || defined(THA6_THA6206D)) */
        }
        else if (DmaDemo_Continuous_Cnt == (DMA_DEMO_CALCEL_CONTINUOUS_TRANS_NUM))
        {
#if !(defined(THA6_THA6206) || defined(THA6_THA6206D))
            /* THA6206 and THA6206D do not support safe cancel the channel */
            /* Cancel channel transfer */
            Dma_ChannelCancel(DmaConf_DmaChannel_M2M_Continuous, DMA_CH_CANCEL_SAFE);
#else
            Dma_ChannelCancel(DmaConf_DmaChannel_M2M_Continuous, DMA_CH_CANCEL_DIRECT);
#endif /* !(defined(THA6_THA6206) || defined(THA6_THA6206D)) */
        }
        else
        {
            /* Do Nothing */
        }
    }
}

void DmaDemo_M2mLinkedListNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt)
{
    (void)Channel;
    if (DMA_CH_INT_TC == ChIntEvt)
    {
        DmaDemo_LinkedList_Cnt++;
    }
}

void DmaDemo_M2mShadowNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt)
{
    (void)Channel;
    if (DMA_CH_INT_TC == ChIntEvt)
    {
#if !(defined(THA6_THA6206) || defined(THA6_THA6206D))
        DmaDemo_ShadowOprt_Cnt++;
#endif /* !(defined(THA6_THA6206) || defined(THA6_THA6206D)) */

        if (1U == DmaDemo_ShadowOprt_Cnt)
        {
            /* Dma default switch to shadow configuration 0 */
#if (defined(THA6_THA6206) || defined(THA6_THA6206D))
            DmaDemo_ShadowOprt_Cnt++;
#endif /* (defined(THA6_THA6206) || defined(THA6_THA6206D)) */
        }
        else if (2U == DmaDemo_ShadowOprt_Cnt)
        {
#if !(defined(THA6_THA6206) || defined(THA6_THA6206D))
            /* THA6206 and THA6206D do not support suspend and resume operation */
            /* Paused channel transfer */
            Dma_ChannelSuspend(DmaConf_DmaChannel_M2M_Shadow);
#endif /* !(defined(THA6_THA6206) || defined(THA6_THA6206D)) */
        }
        else if (4U == DmaDemo_ShadowOprt_Cnt)
        {
            /* (4U == DmaDemo_ShadowOprt_Cnt) is used to ensure that the shadowing operation
             * is successfully completed at least once after it is updated. */
            /* Cancel channel transfer */
            Dma_ChannelCancel(DmaConf_DmaChannel_M2M_Shadow, DMA_CH_CANCEL_DIRECT);
        }
#if (defined(THA6_THA6206) || defined(THA6_THA6206D))
        else if (0U == DmaDemo_ShadowOprt_Cnt)
        {
            DmaDemo_ShadowOprt_Cnt++;
        }
#endif /* (defined(THA6_THA6206) || defined(THA6_THA6206D)) */
        else
        {
            /* Do Nothing */
        }
    }
}

void DmaDemo_M2mPatternNotif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt)
{
    (void)Channel;
    if (DMA_CH_INT_PATTERN == ChIntEvt)
    {
        DmaDemo_PatternMatchFlag = TRUE;
    }
}

void DmaDemo_M2mDaisyChain0Notif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt)
{
    /* Do nothing */
    (void)Channel;
    (void)ChIntEvt;
}

void DmaDemo_M2mDaisyChain1Notif(Dma_ChannelType Channel, Dma_ChEventType ChIntEvt)
{
    (void)Channel;
    /* Daisy chain channel interrupt triggered */
    if (DMA_CH_INT_TC == ChIntEvt)
    {
        DmaDemo_DaisyChainTriggFlag = TRUE;
    }
}

void DmaDemo_DoubleBuffer0_Notif(Dma_ChannelType Channel, Dma_DblFrznStatusType FrozenStatus)
{
    if (DmaConf_DmaChannel_M2M_DoubleBuf == Channel)
    {
        if (DMA_CH_DB_BOTH_FROZEN_BUF0 == FrozenStatus)
        {
            /* Stop channel */
            Dma_ChannelCancel(DmaConf_DmaChannel_M2M_DoubleBuf, DMA_CH_CANCEL_DIRECT);
            DmaDemo_DoubleBuffer_Cnt = 1U;
        }
    }
}


#define DMA_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dma_MemMap.h"

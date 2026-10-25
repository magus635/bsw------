/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Adc_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SARADC
*
*   brief                 : This file contains Demo application for Adc Driver
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
#include "Adc_Demo.h"
#include "Std_Types.h"
#include "Adc_Cfg.h"
#include "Adc.h"
#include "Intc.h"
#include "Demo_TestTime.h"
#include "Demo_Common.h"
#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
#include "Dma.h"
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define ADC_HW_TRIG_SINGLE_CHS           (7U)
#define ADC_HW_TRIG_STREAMING_CHS        (3U)
#define ADC_HW_TRIG_STREAMING_NUM        (5U)

#define ADC_SW_ONE_SHOT_SINGLE_CHS       (7U)
#define ADC_SW_CONTINUOUS_CHS            (7U)

#define ADC_SW_TRIG_STREAMING_CHS        (4U)
#define ADC_SW_TRIG_STREAMING_NUM        (5U)

#define ADC_POLLING_SW_SINGLE_CHS        (7U)
#define ADC_POLLING_HW_SINGLE_CHS        (8U)

#define ADC_POLLING_SW_STREAMING_CHS     (3U)
#define ADC_POLLING_SW_STREAMING_NUM     (5U)
#define ADC_POLLING_HW_STREAMING_CHS     (5U)
#define ADC_POLLING_HW_STREAMING_NUM     (5U)

#define ADC_SYNC_GROUP_HWUNIT_NUM        (2U)    /* SARADC0(master), SARADC2 */
#define ADC_SYNC_GROUP_CHS               (1U)
#define ADC_SYNC_GROUP_STREAMING_NUM     (5U)
#define ADC_SYNC_GROUP_BUFFER_SIZE       \
                    (ADC_SYNC_GROUP_CHS * ADC_SYNC_GROUP_STREAMING_NUM * ADC_SYNC_GROUP_HWUNIT_NUM)

#define ADC_CONVERSION_WAIT_TIMEOUT      (1000U)
#define ADC_CONVERSION_WAIT_LONG_TIMEOUT (5000U)

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/* Core0 */
#define ADC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Adc_MemMap.h"

static uint8 Adc_DemoInitStatusCore0;

#define ADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Adc_MemMap.h"

/* Core1 */
#define ADC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Adc_MemMap.h"

static uint8 Adc_DemoInitStatusCore1;

#define ADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Adc_MemMap.h"


/* Core Global variables */
#define ADC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Adc_MemMap.h"

static Demo_CoreExeType Adc_DemoCoreExeFlag = {(Mcal_CoreType)0U, 0xFFU, DEMO_IDLE};

#define ADC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Adc_MemMap.h"

#define ADC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Adc_MemMap.h"

static uint8 Adc_GtmTriggerCnt_0;

static uint32 Adc_SwContinuousConversionCnt;

static Adc_ValueGroupType Adc_HwTrigSingleResult[ADC_HW_TRIG_SINGLE_CHS];
static Adc_ValueGroupType
             Adc_HwTrigStreamingResult[ADC_HW_TRIG_STREAMING_CHS * ADC_HW_TRIG_STREAMING_NUM];
static Adc_ValueGroupType Adc_SyncGrpResult[ADC_SYNC_GROUP_BUFFER_SIZE];

static Adc_ValueGroupType Adc_SwContinusBuffer[ADC_SW_CONTINUOUS_CHS];
static Adc_ValueGroupType Adc_SwOneShotLimitChecking;

static Adc_ValueGroupType Adc_SwOneShotBuffer[ADC_SW_ONE_SHOT_SINGLE_CHS];

static Adc_ValueGroupType Adc_SwStreamingBuffer[ADC_SW_TRIG_STREAMING_CHS *
                                                ADC_SW_TRIG_STREAMING_NUM];

static Adc_ValueGroupType Adc_SwPollingSingleResult[ADC_POLLING_SW_SINGLE_CHS];
static Adc_ValueGroupType Adc_HwPollingSingleResult[ADC_POLLING_HW_SINGLE_CHS];

static Adc_ValueGroupType Adc_SwPollingStreamingResult[ADC_POLLING_SW_STREAMING_CHS *
                                                       ADC_POLLING_SW_STREAMING_NUM];
static Adc_ValueGroupType Adc_HwPollingStreamingResult[ADC_POLLING_HW_STREAMING_CHS *
                                                       ADC_POLLING_HW_STREAMING_NUM];

#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
Adc_ValueGroupType Adc_DmaTransferSwTrigResult[ADC_DMA_TRANSFER_SW_TRIG_CHS *
                                               ADC_DMA_TRSNAFER_SW_TRIG_COUNT];
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */

#define ADC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Adc_MemMap.h"

#define ADC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Adc_MemMap.h"

static uint8 * const Adc_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES] =
{
    &Adc_DemoInitStatusCore0,
    &Adc_DemoInitStatusCore1
};

#define ADC_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Adc_MemMap.h"

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
#define ADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"

static void Adc_HwTrigSingleWithGtmDemo(void);
static void Adc_HwTrigStreamingWithGtmDemo(void);
static void Adc_HwTrigSingleWithResultAccumuDemo(void);
static void Adc_SyncGroupHwTrigDemo(void);
static void Adc_SwTrigContinuousConversionDemo(void);
static void Adc_SwTrigWithLimitCheckingDemo(void);
static void Adc_SwTrigOneShotConversionDemo(void);
static void Adc_SwTrigContinuousStreamingDemo(void);
static void Adc_SwTrigOneShotConversionResultAccumuDemo(void);
static void Adc_SwTrigPollingSingleDemo(void);
static void Adc_HwTrigPollingSingleDemo(void);
static void Adc_SwTrigPollingStreamingDemo(void);
static void Adc_HwTrigPollingStreamingDemo(void);
#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
static void Adc_SwTrigDmaTransferDemo(void);
static void Adc_SwTrigDmaTransferWithDaisyChainDemo(void);
static void Adc_SwTrigDmaTransferAllChToOneResRegDemo(void);
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Adc_HwTrigSingleWithGtmDemo
*
*   Service ID              : None.
*
*   Description             : Single access, one-shot conversion, circular buffer for GTM ATOM
*                             timer trigger.
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
static void Adc_HwTrigSingleWithGtmDemo(void)
{
    Std_ReturnType ret;
    volatile uint32 LoopCnt;

    /* Enable the interrupt source:SARADC0 SR0 */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_377);

    Adc_GtmTriggerCnt_0 = 0U;

    /* Enable the notification function */
    Adc_EnableGroupNotification(AdcConf_AdcGroup_GroupHwTrig);
    /* Setup Result buffer */
    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupHwTrig, &Adc_HwTrigSingleResult[0]);
    if (E_OK == ret)
    {
        Adc_GtmTriggerCnt_0 = 0U;
        /* Enable HW trigger with GTM */
        Adc_EnableHardwareTrigger(AdcConf_AdcGroup_GroupHwTrig);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer FAILED!!!");
    }

    /* Maximum Waiting time is 1s */
    LoopCnt = 0U;
    do
    {
        LoopCnt ++;
        Timer_DelayMs(1);    /* Waiting 1ms */
    } while ((LoopCnt < ADC_CONVERSION_WAIT_TIMEOUT) && (Adc_GtmTriggerCnt_0 < 5U));

    if (Adc_GtmTriggerCnt_0 == 5U)
    {
        DEBUG_PRINTF("\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    Intc_DisableInterrupt(INTC_INTSRC_NUM_377);

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_HwTrigStreamingWithGtmDemo
*
*   Service ID              : None.
*
*   Description             : Streaming access, one-shot conversion, Stream buffer linear buffer for
*                             GTM ATOM timer trigger.
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
static void Adc_HwTrigStreamingWithGtmDemo(void)
{
    uint8 ChannelLoop;
    uint8 StreamingLoop;
    Std_ReturnType ret;
    volatile uint32 LoopCnt;
    /* ResultPtr is used to point to the first position of the latest conversion result */
    Adc_ValueGroupType *ResultPtr;
    Adc_StreamNumSampleType ValidNum;

    /* Enable the interrupt source:SARADC0 SR1 */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_378);

    /* Setup Result buffer */
    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupHwTrigStreaming,
                                &Adc_HwTrigStreamingResult[0]);
    if (E_OK == ret)
    {
        /* Enable HW trigger with GTM */
        Adc_EnableHardwareTrigger(AdcConf_AdcGroup_GroupHwTrigStreaming);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer FAILED!!!");
    }

    /* Maximum Waiting time is 1s */
    LoopCnt = 0U;
    do
    {
        Timer_DelayMs(1);    /* Waiting 1ms */
        ValidNum = Adc_GetStreamLastPointer(AdcConf_AdcGroup_GroupHwTrigStreaming, &ResultPtr);
        (void)ResultPtr;
        LoopCnt ++;
    } while ((LoopCnt < ADC_CONVERSION_WAIT_TIMEOUT) &&
                ((Adc_StreamNumSampleType)ADC_HW_TRIG_STREAMING_NUM != ValidNum));

    if (ADC_IDLE == Adc_GetGroupStatus(AdcConf_AdcGroup_GroupHwTrigStreaming))
    {
        DEBUG_PRINTF("\nSARADC0 HW trigger Linear Streaming Result: \r\n");
        for (StreamingLoop = 0U; StreamingLoop < ADC_HW_TRIG_STREAMING_NUM; StreamingLoop++)
        {
            DEBUG_PRINTF("No. %d: ", StreamingLoop);
            for(ChannelLoop = 0U; ChannelLoop < ADC_HW_TRIG_STREAMING_CHS; ChannelLoop++)
            {
                DEBUG_PRINTF("%4u ", Adc_HwTrigStreamingResult[StreamingLoop +
                                                    ADC_HW_TRIG_STREAMING_NUM * ChannelLoop]);
            }
            DEBUG_PRINTF("\r\n");
        }

        DEBUG_PRINTF("\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    Intc_DisableInterrupt(INTC_INTSRC_NUM_378);

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_HwTrigSingleWithResultAccumuDemo
*
*   Service ID              : None.
*
*   Description             : Single access, one-shot conversion, circular buffer for GTM ATOM
*                             timer trigger, result accumulation.
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
static void Adc_HwTrigSingleWithResultAccumuDemo(void)
{
    Std_ReturnType ret;
    volatile uint32 LoopCnt;

    /* Enable the interrupt source:SARADC0 SR0 */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_377);

    Adc_GtmTriggerCnt_0 = 0U;

    /* Enable the notification function */
    Adc_EnableGroupNotification(AdcConf_AdcGroup_GroupHwResultAccumulation);
    /* Setup Result buffer */
    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupHwResultAccumulation, &Adc_HwTrigSingleResult[0]);
    if (E_OK == ret)
    {
        Adc_GtmTriggerCnt_0 = 0U;
        /* Enable HW trigger with GTM */
        Adc_EnableHardwareTrigger(AdcConf_AdcGroup_GroupHwResultAccumulation);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer FAILED!!!");
    }

    /* Maximum Waiting time is 1s */
    LoopCnt = 0U;
    do
    {
        LoopCnt ++;
        Timer_DelayMs(1);    /* Waiting 1ms */
    } while ((LoopCnt < ADC_CONVERSION_WAIT_LONG_TIMEOUT) && (Adc_GtmTriggerCnt_0 < 5U));

    if (Adc_GtmTriggerCnt_0 == 5U)
    {
        DEBUG_PRINTF("\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    Intc_DisableInterrupt(INTC_INTSRC_NUM_377);

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_SyncGroupHwTrigDemo
*
*   Service ID              : None.
*
*   Description             : Sync conversion, master is SARADC0, slave are SARADC2, SARADC3
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
static void Adc_SyncGroupHwTrigDemo(void)
{
    uint8 ChannelLoop;
    uint8 HwunitLoop;
    uint8 StreamingLoop;
    const uint8 SyncGrpHwId[ADC_SYNC_GROUP_HWUNIT_NUM] = {0U, 2U};
    Std_ReturnType ret;
    volatile uint32 LoopCnt;
    Adc_ValueGroupType *Result;
    Adc_StreamNumSampleType ValidNum;

    /* Enable the interrupt source:SARADC0 SR0 */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_377);

    /* Setup Result buffer */
    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupSyncConv,
                                &Adc_SyncGrpResult[0]);
    if (E_OK == ret)
    {
        /* Enable HW trigger with GTM */
        Adc_EnableHardwareTrigger(AdcConf_AdcGroup_GroupSyncConv);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer FAILED!!!");
    }

    /* Maximum Waiting time is 1s */
    LoopCnt = 0U;
    do
    {
        Timer_DelayMs(1);    /* Waiting 1ms */
        ValidNum = Adc_GetStreamLastPointer(AdcConf_AdcGroup_GroupSyncConv, &Result);
        LoopCnt ++;
    } while ((LoopCnt < ADC_CONVERSION_WAIT_TIMEOUT) &&
                ((Adc_StreamNumSampleType)ADC_SYNC_GROUP_STREAMING_NUM != ValidNum));

    if (ADC_IDLE == Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSyncConv))
    {
        DEBUG_PRINTF("\nSync group HW trigger with Linear Streaming conversion Result: \r\n");
        for (HwunitLoop = 0U; HwunitLoop < ADC_SYNC_GROUP_HWUNIT_NUM; HwunitLoop++)
        {
            DEBUG_PRINTF("  - Sync group SARADC%d conversion results: \n", SyncGrpHwId[HwunitLoop]);
            for (StreamingLoop = 1U; StreamingLoop <= ADC_SYNC_GROUP_STREAMING_NUM; StreamingLoop++)
            {
                DEBUG_PRINTF("\t - No. %d: ", StreamingLoop);
                for(ChannelLoop = 0U; ChannelLoop < ADC_SYNC_GROUP_CHS; ChannelLoop++)
                {
                    DEBUG_PRINTF("%4u ",
                            Result[StreamingLoop + ADC_SYNC_GROUP_STREAMING_NUM * ChannelLoop]);
                }
                DEBUG_PRINTF("\r\n");
            }

        }
        DEBUG_PRINTF("\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    Intc_DisableInterrupt(INTC_INTSRC_NUM_377);

    DEBUG_PRINTF("\n");
}


/****************************************************************************************************
*   Function Name           : Adc_SwTrigContinuousConversionDemo
*
*   Service ID              : None.
*
*   Description             : Single access, continuous conversion, circular buffer, Software trigger
*
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
static void Adc_SwTrigContinuousConversionDemo(void)
{
    Std_ReturnType ret;
    volatile uint32 LoopCnt;
    Adc_StatusType ResultStatus;

    Intc_EnableInterrupt(INTC_INTSRC_NUM_389);

    Adc_SwContinuousConversionCnt = 0U;

    /* Setup Result buffer */
    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupContinuous, Adc_SwContinusBuffer);
    if (E_OK == ret)
    {
        /* Enable the notification */
        Adc_EnableGroupNotification(AdcConf_AdcGroup_GroupContinuous);
        /* Start Adc group conversion, then save the results into result buffer */
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupContinuous);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer FAILED!!!");
    }

    LoopCnt = 0U;
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);    /* Waiting 1ms */
    } while ((LoopCnt < ADC_CONVERSION_WAIT_TIMEOUT) && (Adc_SwContinuousConversionCnt < 5U));

    if (Adc_SwContinuousConversionCnt == 5U)
    {
        DEBUG_PRINTF("\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAILED");
    }

    /* Stop conversion when not in IDLE status */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupContinuous);
    if (ADC_IDLE != ResultStatus)
    {
        /* Stop Conversion */
        Adc_StopGroupConversion(AdcConf_AdcGroup_GroupContinuous);
    }

    Intc_DisableInterrupt(INTC_INTSRC_NUM_389);

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_SwTrigWithLimitCheckingDemo
*
*   Service ID              : None.
*
*   Description             : Single access, one-shot conversion, stream buffer linear, software
*                             trigger with limit checking.
*
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
static void Adc_SwTrigWithLimitCheckingDemo(void)
{
    Std_ReturnType ret;
    Adc_ValueGroupType ConvResult;
    volatile uint32 LoopCnt;
    Adc_StatusType ResultStatus;

    Intc_EnableInterrupt(INTC_INTSRC_NUM_389);

    /* Setup Result buffer */
    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupLimitCheck,
                                                             &Adc_SwOneShotLimitChecking);
    if (E_OK == ret)
    {
        /* Start Adc group conversion, then save the results into result buffer */
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupLimitCheck);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer FAILED!!!");
    }

    /* Waiting for conversion finished */
    /* Maximum waiting time is 1s */
    LoopCnt = 0;
    Timer_DelayMs(1);
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupLimitCheck);
    while ((LoopCnt < ADC_CONVERSION_WAIT_TIMEOUT) && (ADC_BUSY == ResultStatus))
    {
        /* If the result is not in range then stop Group conversion when one-shot mode */
        /* SWS_Adc_00449 */
        Adc_StopGroupConversion(AdcConf_AdcGroup_GroupLimitCheck);
        /* Re-start next conversion */
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupLimitCheck);
        LoopCnt++;
        Timer_DelayMs(1);
        ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupLimitCheck);
    }

    /* Check whether conversion completed */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupLimitCheck);
    if (ADC_STREAM_COMPLETED == ResultStatus)
    {
        ret = Adc_ReadGroup(AdcConf_AdcGroup_GroupLimitCheck, &ConvResult);
        if (E_OK == ret)
        {
            DEBUG_PRINTF("\nSARADC2 LimitCheckGroup_0 conversion Results: ");
            DEBUG_PRINTF("%4u ", ConvResult);
        }
        DEBUG_PRINTF("\n\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nNo conversion result in the range from 1500 to 3000.");
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    /* Stop conversion when not in IDLE status */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupLimitCheck);
    if (ADC_IDLE != ResultStatus)
    {
        /* Stop Conversion */
        Adc_StopGroupConversion(AdcConf_AdcGroup_GroupLimitCheck);
    }

    Intc_DisableInterrupt(INTC_INTSRC_NUM_389);

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_SwTrigOneShotConversionDemo
*
*   Service ID              : None.
*
*   Description             : Single access, one-shot conversion, circular buffer, software trigger
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
static void Adc_SwTrigOneShotConversionDemo(void)
{
    Std_ReturnType ret;
    volatile uint8 ChannelLoop;
    volatile uint32 LoopCnt;
    Adc_ValueGroupType Result[ADC_SW_ONE_SHOT_SINGLE_CHS];
    Adc_StatusType ResultStatus;

    Intc_EnableInterrupt(INTC_INTSRC_NUM_390);

    /* Setup Result buffer */
    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupOneShot, &Adc_SwOneShotBuffer[0]);
    if (E_OK == ret)
    {
        /* Start Adc group conversion, then save the results into result buffer */
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupOneShot);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer FAILED!!!");
    }

    LoopCnt = 0U;
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);    /* Waiting 1ms */
        ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupOneShot);
    } while ((LoopCnt <= ADC_CONVERSION_WAIT_TIMEOUT) && (ADC_BUSY == ResultStatus));

    /* Check whether conversion completed */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupOneShot);
    if (ADC_STREAM_COMPLETED == ResultStatus)
    {
        ret = Adc_ReadGroup(AdcConf_AdcGroup_GroupOneShot, &Result[0]);
        if (E_OK == ret)
        {
            DEBUG_PRINTF("\nSARADC3 AdcGroupOneShot conversion Results: ");
            for(ChannelLoop = 0; ChannelLoop < ADC_SW_ONE_SHOT_SINGLE_CHS; ChannelLoop++)
            {
                DEBUG_PRINTF("%4u ", Result[ChannelLoop]);
            }
        }
        DEBUG_PRINTF("\n\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    /* Stop conversion when not in IDLE status */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupOneShot);
    if (ADC_IDLE != ResultStatus)
    {
        /* Stop Conversion */
        Adc_StopGroupConversion(AdcConf_AdcGroup_GroupOneShot);
    }

    Intc_DisableInterrupt(INTC_INTSRC_NUM_390);

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_SwTrigOneShotConversionDemo
*
*   Service ID              : None.
*
*   Description             : Streaming access, continuous conversion, stream buffer linear, software
*                             trigger.
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
static void Adc_SwTrigContinuousStreamingDemo(void)
{
    Std_ReturnType ret;
    uint8 ChannelLoop;
    uint8 StreamingLoop;
    /* ResultPtr is used to point to the first position of the latest conversion result */
    Adc_ValueGroupType *ResultPtr;
    volatile uint32 LoopCnt;
    Adc_StatusType ResultStatus;
    Adc_StreamNumSampleType ValidNum;

    Intc_EnableInterrupt(INTC_INTSRC_NUM_391);

    /* Setup Result buffer */
    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupStreaming, &Adc_SwStreamingBuffer[0]);
    if (E_OK == ret)
    {
        /* Start Adc group conversion, then save the results into result buffer */
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupStreaming);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer FAILED!!!");
    }

    LoopCnt = 0U;
    do
    {
        Timer_DelayMs(1);    /* Waiting 1ms */
        ValidNum = Adc_GetStreamLastPointer(AdcConf_AdcGroup_GroupStreaming, &ResultPtr);
        (void)ResultPtr;
        LoopCnt++;
    } while ((LoopCnt < ADC_CONVERSION_WAIT_TIMEOUT) &&
                ((Adc_StreamNumSampleType)ADC_SW_TRIG_STREAMING_NUM != ValidNum));

    /* Streaming buffer filled completely; SW trigger disabled automatically; */
    if (ADC_IDLE == Adc_GetGroupStatus(AdcConf_AdcGroup_GroupStreaming))
    {
        DEBUG_PRINTF("\nSARADC2 SW trigger Linear Streaming Result: \r\n");
        for (StreamingLoop = 0U; StreamingLoop < ADC_SW_TRIG_STREAMING_NUM; StreamingLoop++)
        {
            DEBUG_PRINTF("No. %d: ", StreamingLoop);
            for(ChannelLoop = 0; ChannelLoop < ADC_SW_TRIG_STREAMING_CHS; ChannelLoop++)
            {
                DEBUG_PRINTF("%4u ", Adc_SwStreamingBuffer[StreamingLoop +
                                                    ADC_SW_TRIG_STREAMING_NUM * ChannelLoop]);
            }
            DEBUG_PRINTF("\r\n");
        }
        DEBUG_PRINTF("\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    /* Stop conversion when not in IDLE status */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupStreaming);
    if (ADC_IDLE != ResultStatus)
    {
        /* Stop Conversion */
        Adc_StopGroupConversion(AdcConf_AdcGroup_GroupStreaming);
    }

    Intc_DisableInterrupt(INTC_INTSRC_NUM_391);

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_SwTrigOneShotConversionResultAccumuDemo
*
*   Service ID              : None.
*
*   Description             : Single access, one-shot conversion, circular buffer, software trigger
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
static void Adc_SwTrigOneShotConversionResultAccumuDemo(void)
{
    Std_ReturnType ret;
    volatile uint8 ChannelLoop;
    volatile uint32 LoopCnt;
    Adc_ValueGroupType Result[ADC_SW_ONE_SHOT_SINGLE_CHS];
    Adc_StatusType ResultStatus;

    Intc_EnableInterrupt(INTC_INTSRC_NUM_389);

    /* Setup Result buffer */
    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupSwResultAccumulation,
                                Adc_SwOneShotBuffer);
    if (E_OK == ret)
    {
        /* Start Adc group conversion, then save the results into result buffer */
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupSwResultAccumulation);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer FAILED!!!");
    }

    LoopCnt = 0U;
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);    /* Waiting 1ms */
        ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwResultAccumulation);
    } while (LoopCnt <= ADC_CONVERSION_WAIT_LONG_TIMEOUT && (ADC_BUSY == ResultStatus));

    /* Check whether conversion completed */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwResultAccumulation);
    if (ADC_STREAM_COMPLETED == ResultStatus)
    {
        ret = Adc_ReadGroup(AdcConf_AdcGroup_GroupSwResultAccumulation, &Result[0]);
        if (E_OK == ret)
        {
            DEBUG_PRINTF("\nSARADC3 AdcGroupOneShot conversion Results: ");
            for(ChannelLoop = 0; ChannelLoop < ADC_SW_ONE_SHOT_SINGLE_CHS; ChannelLoop++)
            {
                DEBUG_PRINTF("%4u ", Result[ChannelLoop]);
            }
        }
        DEBUG_PRINTF("\n\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    /* Stop conversion when not in IDLE status */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwResultAccumulation);
    if (ADC_IDLE != ResultStatus)
    {
        /* Stop Conversion */
        Adc_StopGroupConversion(AdcConf_AdcGroup_GroupSwResultAccumulation);
    }

    Intc_DisableInterrupt(INTC_INTSRC_NUM_389);

    DEBUG_PRINTF("\n");
}

#if (ADC_POLLING_MODE_ENABLE == STD_ON)
/****************************************************************************************************
*   Function Name           : Adc_SwTrigPollingSingleDemo
*
*   Service ID              : None.
*
*   Description             : In polling mode, single access, one-shot conversion, circular buffer,
*                             Software trigger.
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
static void Adc_SwTrigPollingSingleDemo(void)
{
    Std_ReturnType ret;
    volatile uint8 ChannelLoop;
    Adc_ValueGroupType Result[ADC_POLLING_SW_SINGLE_CHS];
    volatile uint32 LoopCnt;
    Adc_StatusType ResultStatus;

    for(ChannelLoop = 0; ChannelLoop < ADC_POLLING_SW_SINGLE_CHS; ChannelLoop++)
    {
        Result[ChannelLoop] = 0xFFFFU;
    }

    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupSwPolling,
                                                               &Adc_SwPollingSingleResult[0]);
    if (E_OK == ret)
    {
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupSwPolling);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer fail");
    }

    LoopCnt = 0U;
    do
    {
        LoopCnt++;
        ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwPolling);
    } while ((LoopCnt <= ADC_CONVERSION_WAIT_TIMEOUT) && (ADC_BUSY == ResultStatus));

    /* Check whether conversion completed */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwPolling);
    if (ADC_STREAM_COMPLETED == ResultStatus)
    {
        ret = Adc_ReadGroup(AdcConf_AdcGroup_GroupSwPolling, &Result[0]);
        if (E_OK == ret)
        {
            DEBUG_PRINTF("\nSARADC8 polling mode; SW trigger conversion Results: ");
            for(ChannelLoop = 0; ChannelLoop < ADC_POLLING_SW_SINGLE_CHS; ChannelLoop++)
            {
                DEBUG_PRINTF("%4u ", Result[ChannelLoop]);
            }
        }
        DEBUG_PRINTF("\n\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_HwTrigPollingSingleDemo
*
*   Service ID              : None.
*
*   Description             : In polling mode, single access, one-shot conversion, circular buffer,
*                             GTM ATOM timer trigger.
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
static void Adc_HwTrigPollingSingleDemo(void)
{
    Std_ReturnType ret;
    volatile uint8 ChannelLoop;
    Adc_ValueGroupType Result[ADC_POLLING_HW_SINGLE_CHS];
    volatile uint32 LoopCnt;
    Adc_StatusType ResultStatus;

    for(ChannelLoop = 0; ChannelLoop < ADC_POLLING_SW_SINGLE_CHS; ChannelLoop++)
    {
        Result[ChannelLoop] = 0xFFFFU;
    }

    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupHwPolling,
                                                               &Adc_HwPollingSingleResult[0]);
    if (E_OK == ret)
    {
        Adc_EnableHardwareTrigger(AdcConf_AdcGroup_GroupHwPolling);
    }
    else
    {
        DEBUG_PRINTF("\nSARADC8 Setup result buffer fail");
    }

    LoopCnt = 0U;
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);    /* Waiting 1ms */
        ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupHwPolling);
    } while ((LoopCnt <= ADC_CONVERSION_WAIT_TIMEOUT) && (ADC_BUSY == ResultStatus));

    /* Check whether conversion completed */
    ResultStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupHwPolling);
    if (ADC_STREAM_COMPLETED == ResultStatus)
    {
        ret = Adc_ReadGroup(AdcConf_AdcGroup_GroupHwPolling, &Result[0]);
        if (E_OK == ret)
        {
            DEBUG_PRINTF("\nSARADC8 polling mode; HW trigger conversion Results: ");
            for(ChannelLoop = 0; ChannelLoop < ADC_POLLING_HW_SINGLE_CHS; ChannelLoop++)
            {
                DEBUG_PRINTF("%4u ", Result[ChannelLoop]);
            }
        }
        DEBUG_PRINTF("\n\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }
    Adc_DisableHardwareTrigger(AdcConf_AdcGroup_GroupHwPolling);

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_SwTrigPollingStreamingDemo
*
*   Service ID              : None.
*
*   Description             : In polling mode, streaming access, continuous conversion,
*                             stream buffer linear, software trigger.
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
static void Adc_SwTrigPollingStreamingDemo(void)
{
    Std_ReturnType ret;
    /* ResultPtr is used to point to the first position of the latest conversion result */
    Adc_ValueGroupType *ResultPtr;
    uint8 ChannelLoop;
    uint8 StreamingLoop;
    volatile uint32 LoopCnt = 0U;
    Adc_StreamNumSampleType ValidNum;
    Adc_StatusType ReturnStatus;

    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupSwStreaming,
                                                               &Adc_SwPollingStreamingResult[0]);
    if (E_OK == ret)
    {
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupSwStreaming);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer fail");
    }

    LoopCnt = 0U;
    /* In polling mode, the API Adc_GetGroupStatus() must be called periodically, used for
     * Update the status machine */
    do
    {
        LoopCnt++;
        ReturnStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwStreaming);
    } while ((LoopCnt <= ADC_CONVERSION_WAIT_TIMEOUT) && (ADC_STREAM_COMPLETED != ReturnStatus));

    ReturnStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwStreaming);
    if (ADC_STREAM_COMPLETED == ReturnStatus)
    {
        /* Streaming buffer filled completely; SW trigger disabled automatically; */
        ValidNum = Adc_GetStreamLastPointer(AdcConf_AdcGroup_GroupSwStreaming, &ResultPtr);
        if ((Adc_StreamNumSampleType)ADC_POLLING_SW_STREAMING_NUM == ValidNum)
        {
            (void)ResultPtr;
            DEBUG_PRINTF("\nSARADC8 polling mode; SW trigger Linear Streaming Result: \r\n");
            for (StreamingLoop = 0U; StreamingLoop < ADC_POLLING_SW_STREAMING_NUM; StreamingLoop++)
            {
                DEBUG_PRINTF("No. %d: ", StreamingLoop);
                for(ChannelLoop = 0; ChannelLoop < ADC_POLLING_SW_STREAMING_CHS; ChannelLoop++)
                {
                    DEBUG_PRINTF("%4u ", Adc_SwPollingStreamingResult[StreamingLoop +
                                                    ADC_POLLING_SW_STREAMING_NUM * ChannelLoop]);
                }
                DEBUG_PRINTF("\r\n");
            }
            DEBUG_PRINTF("\nTest Result = PASS");
        }
        else
        {
            DEBUG_PRINTF("\nTest Result = FAIL");
        }
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    DEBUG_PRINTF("\n");
}

/****************************************************************************************************
*   Function Name           : Adc_HwTrigPollingStreamingDemo
*
*   Service ID              : None.
*
*   Description             : In polling mode, streaming access, continuous conversion,
*                             stream buffer linear, GTM ATOM timer trigger.
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
static void Adc_HwTrigPollingStreamingDemo(void)
{
    Std_ReturnType ret;
    /* ResultPtr is used to point to the first position of the latest conversion result */
    Adc_ValueGroupType *ResultPtr;
    volatile uint32 LoopCnt;
    uint8 ChannelLoop;
    uint8 StreamingLoop;
    Adc_StatusType ReturnStatus;
    Adc_StreamNumSampleType ValidNum;

    ret = Adc_SetupResultBuffer(AdcConf_AdcGroup_GroupHwStreaming,
                                                               &Adc_HwPollingStreamingResult[0]);
    if (E_OK == ret)
    {
        Adc_EnableHardwareTrigger(AdcConf_AdcGroup_GroupHwStreaming);
    }
    else
    {
        DEBUG_PRINTF("\nSetup result buffer fail");
    }

    LoopCnt = 0U;

    do
    {
        LoopCnt++;
        Timer_DelayMs(1);    /* Waiting 1ms */
        ReturnStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupHwStreaming);
    } while ((LoopCnt <= ADC_CONVERSION_WAIT_TIMEOUT) && (ADC_STREAM_COMPLETED != ReturnStatus));

    ReturnStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupHwStreaming);
    if (ADC_STREAM_COMPLETED == ReturnStatus)
    {
        /* Streaming buffer filled completely; SW trigger disabled automatically; */
        ValidNum = Adc_GetStreamLastPointer(AdcConf_AdcGroup_GroupHwStreaming, &ResultPtr);
        if ((Adc_StreamNumSampleType)ADC_POLLING_HW_STREAMING_NUM == ValidNum)
        {
            (void)ResultPtr;
            DEBUG_PRINTF("\nSARADC8 polling mode; HW trigger Linear Streaming Result: \r\n");
            for (StreamingLoop = 0U; StreamingLoop < ADC_POLLING_HW_STREAMING_NUM; StreamingLoop++)
            {
                DEBUG_PRINTF("No. %d: ", StreamingLoop);
                for(ChannelLoop = 0; ChannelLoop < ADC_POLLING_HW_STREAMING_CHS; ChannelLoop++)
                {
                    DEBUG_PRINTF("%4u ", Adc_HwPollingStreamingResult[StreamingLoop +
                                                ADC_POLLING_HW_STREAMING_NUM * ChannelLoop]);
                }
                DEBUG_PRINTF("\r\n");
            }
            DEBUG_PRINTF("\nTest Result = PASS");
        }
        else
        {
            DEBUG_PRINTF("\nTest Result = FAIL");
        }
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    DEBUG_PRINTF("\n");
}

#endif /* (ADC_POLLING_MODE_ENABLE  \== STD_ON) */

#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
/****************************************************************************************************
*   Function Name           : Adc_SwTrigDmaTransferDemo
*
*   Service ID              : None.
*
*   Description             : In DMA mode, single access, one-shot conversion,
*                             stream buffer linear, Software trigger.
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
static void Adc_SwTrigDmaTransferDemo(void)
{
    volatile uint32 LoopCnt;
    uint8 ChannelLoop;
    uint8 Count;
    Adc_StatusType ReturnStatus;

    /* Initialize the DMA initialization */
    Dma_Init(&Dma_ConfigSet[0]);

    /* Start DMA channels(Enable the channels) */
    Dma_ChannelStart(DmaConf_DmaChannel_ADC1_Channel0);
    Dma_ChannelStart(DmaConf_DmaChannel_ADC1_Channel1);
    Dma_ChannelStart(DmaConf_DmaChannel_ADC1_Channel2);
    Dma_ChannelStart(DmaConf_DmaChannel_ADC1_Channel3);

    for (Count = 0U; Count < ADC_DMA_TRSNAFER_SW_TRIG_COUNT; Count++)
    {
        /* Start the conversion */
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupSwTrig);

        LoopCnt = 0U;
        do
        {
            LoopCnt++;
            Timer_DelayMs(1);    /* Waiting 1ms */
            ReturnStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwTrig);
        } while ((LoopCnt <= ADC_CONVERSION_WAIT_TIMEOUT) && (ADC_STREAM_COMPLETED != ReturnStatus));

        ReturnStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwTrig);
        if (ADC_STREAM_COMPLETED == ReturnStatus)
        {
            /* Do Nothing */
        }
        else
        {
            DEBUG_PRINTF("\nTest Result = FAIL");
            break;
        }
    }

    if (ADC_DMA_TRSNAFER_SW_TRIG_COUNT == Count)
    {
        DEBUG_PRINTF("\nSARADC1 DMA mode; SW trigger one-shot Result: \r\n");
        for (ChannelLoop = 0U; ChannelLoop < ADC_DMA_TRANSFER_SW_TRIG_CHS; ChannelLoop++)
        {
            DEBUG_PRINTF("ADC1 Channel%d:", ChannelLoop);
            for(Count = 0U; Count < ADC_DMA_TRSNAFER_SW_TRIG_COUNT; Count++)
            {
                DEBUG_PRINTF("%4u ", Adc_DmaTransferSwTrigResult[ChannelLoop * 5U + Count]);
            }
            DEBUG_PRINTF("\n");
        }
        DEBUG_PRINTF("\nTest Result = PASS");
    }

    DEBUG_PRINTF("\n");

    /* Cancel the channels(Disable the channels) */
    Dma_ChannelCancel(DmaConf_DmaChannel_ADC1_Channel0, DMA_CH_CANCEL_DIRECT);
    Dma_ChannelCancel(DmaConf_DmaChannel_ADC1_Channel1, DMA_CH_CANCEL_DIRECT);
    Dma_ChannelCancel(DmaConf_DmaChannel_ADC1_Channel2, DMA_CH_CANCEL_DIRECT);
    Dma_ChannelCancel(DmaConf_DmaChannel_ADC1_Channel3, DMA_CH_CANCEL_DIRECT);
    Dma_DeInit();
}

/****************************************************************************************************
*   Function Name           : Adc_SwTrigDmaTransferDemo
*
*   Service ID              : None.
*
*   Description             : In DMA mode, single access, one-shot conversion,
*                             stream buffer linear, Software trigger.
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
static void Adc_SwTrigDmaTransferWithDaisyChainDemo(void)
{
    volatile uint32 LoopCnt;
    uint8 ChannelLoop;
    uint8 Count;
    Adc_StatusType ReturnStatus;

    /* Initialize the DMA initialization */
    Dma_Init(&Dma_ConfigSet[0]);

    /* Start DMA channels(Enable the channels) */
    Dma_ChannelStart(DmaConf_DmaChannel_ADC1_Channel7);

    DEBUG_PRINTF("\nSARADC1 DMA mode with daisy chain and linked list; "
                 "SW trigger one-shot Result: \r\n");
    for (Count = 0U; Count < ADC_DMA_TRSNAFER_SW_TRIG_COUNT; Count++)
    {
        /* Start the conversion */
        Adc_StartGroupConversion(AdcConf_AdcGroup_GroupSwTrig_DmaLinkedList);

        LoopCnt = 0U;
        do
        {
            LoopCnt++;
            Timer_DelayMs(1);    /* Waiting 1ms */
            ReturnStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwTrig_DmaLinkedList);
        } while ((LoopCnt <= ADC_CONVERSION_WAIT_TIMEOUT) && (ADC_STREAM_COMPLETED != ReturnStatus));

        ReturnStatus = Adc_GetGroupStatus(AdcConf_AdcGroup_GroupSwTrig_DmaLinkedList);
        if (ADC_STREAM_COMPLETED == ReturnStatus)
        {
            DEBUG_PRINTF("%d Sampled:", Count);
            for(ChannelLoop = 0; ChannelLoop < ADC_DMA_TRANSFER_SW_TRIG_CHS; ChannelLoop++)
            {
                DEBUG_PRINTF("%4u ", Adc_DmaTransferSwTrigResult[ChannelLoop]);
            }
            DEBUG_PRINTF("\n");
        }
        else
        {
            DEBUG_PRINTF("\nTest Result = FAIL");
            break;
        }
    }

    if (ADC_DMA_TRSNAFER_SW_TRIG_COUNT == Count)
    {
        DEBUG_PRINTF("\nTest Result = PASS");
    }

    DEBUG_PRINTF("\n");

    /* Cancel the channels(Disable the channels) */
    Dma_ChannelCancel(DmaConf_DmaChannel_ADC1_Channel7, DMA_CH_CANCEL_DIRECT);
    Dma_DeInit();
}

/****************************************************************************************************
*   Function Name           : Adc_SwTrigDmaTransferAllChToOneResRegDemo
*
*   Service ID              : None.
*
*   Description             : In DMA mode, single access, one-shot conversion,
*                             stream buffer linear, Software trigger.
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
static void Adc_SwTrigDmaTransferAllChToOneResRegDemo(void)
{
    volatile uint32 LoopCnt;
    uint8 Count;
    uint32 DmaChStatus;

    /* Initialize the DMA initialization */
    Dma_Init(&Dma_ConfigSet[0]);

    /* Start DMA channels(Enable the channels) */
    Dma_ChannelStart(DmaConf_DmaChannel_ADC1_AllChToOneResReg);

    /* Start the conversion */
    Adc_StartGroupConversion(AdcConf_AdcGroup_GroupSwTrig_ResRegConf);

    LoopCnt = 0U;
    do
    {
        LoopCnt++;
        Timer_DelayMs(1);    /* Waiting 1ms */
        DmaChStatus = Dma_GetChannelStatus(DmaConf_DmaChannel_ADC1_AllChToOneResReg);
    } while ((LoopCnt < ADC_CONVERSION_WAIT_TIMEOUT) && 
            (DMA_CH_TRANSFER_COMPLETE != (DmaChStatus & DMA_CH_TRANSFER_COMPLETE)));

    if (LoopCnt != ADC_CONVERSION_WAIT_TIMEOUT)
    {
        DEBUG_PRINTF("\nSARADC1 DMA mode; SW trigger one-shot(All conversion results stored in one resigter) Result: \r\n");
        for(Count = 0U; Count < ADC_DMA_TRSNAFER_SW_TRIG_ONE_RES_REG_COUNT; Count++)
        {
            DEBUG_PRINTF("%4u ", Adc_DmaTransferSwTrigResult[Count]);
        }
        DEBUG_PRINTF("\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    DEBUG_PRINTF("\n");

    /* Stop conversion due to DMA result handling mode */
    Adc_StopGroupConversion(AdcConf_AdcGroup_GroupSwTrig_ResRegConf);

    /* Cancel the channels(Disable the channels) */
    Dma_ChannelCancel(DmaConf_DmaChannel_ADC1_AllChToOneResReg, DMA_CH_CANCEL_DIRECT);
    Dma_DeInit();
}
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : Adc_DemoEntry
*
*   Service ID              : None.
*
*   Description             : ADC demo entry.
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
void Adc_DemoEntry(void)
{
    char Cmd;
    uint8 ExitFlag;
    Std_VersionInfoType Adc_ver;

    ExitFlag = 0U;
    while (0U == ExitFlag)
    {
        Adc_GetVersionInfo(&Adc_ver);
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*********************************************************/");
        DEBUG_PRINTF("\n           ADC DRIVER DEMO MENU V%02d.%02d.%02d            ",
               Adc_ver.sw_major_version, Adc_ver.sw_minor_version, Adc_ver.sw_patch_version);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : (SARADC0)Start to Hardware trigger with GTM Timer(Single mode) in Core0. ");
        DEBUG_PRINTF("\n  <2> : (SARADC0)Start to Hardware trigger with GTM Timer(Streaming mode) in Core0. ");
#if defined(THA6_THA6104)
        DEBUG_PRINTF("\n  <3> : (SARADC2)Start to Software trigger with continuous conversion(single mode) in Core0. ");
        DEBUG_PRINTF("\n  <4> : (SARADC2)Start to Software trigger with one shot conversion and limit checking in Core0. ");
        DEBUG_PRINTF("\n  <5> : (SARADC2)Start to Software trigger with shot conversion in Core0. ");
        DEBUG_PRINTF("\n  <6> : (SARADC2)Start to Software trigger with continuous conversion(streaming mode) in Core0. ");
        DEBUG_PRINTF("\n  <7> : (SARADC3)Start to Software trigger with polling mode(single mode) in Core0. ");
        DEBUG_PRINTF("\n  <8> : (SARADC3)Start to Hardware trigger with polling mode(single mode) in Core0. ");
        DEBUG_PRINTF("\n  <9> : (SARADC3)Start to Software trigger with polling mode(streaming mode) in Core0. ");
        DEBUG_PRINTF("\n  <a> : (SARADC3)Start to Hardware trigger with polling mode(streaming mode) in Core0. ");
#else /* not defined(THA6_THA6104) */
        DEBUG_PRINTF("\n  <3> : (SARADC2)Start to Software trigger with continuous conversion(single mode) in Core1. ");
        DEBUG_PRINTF("\n  <4> : (SARADC2)Start to Software trigger with one shot conversion and limit checking in Core1. ");
        DEBUG_PRINTF("\n  <5> : (SARADC2)Start to Software trigger with shot conversion in Core1. ");
        DEBUG_PRINTF("\n  <6> : (SARADC2)Start to Software trigger with continuous conversion(streaming mode) in Core1. ");
        DEBUG_PRINTF("\n  <7> : (SARADC8)Start to Software trigger with polling mode(single mode) in Core0. ");
        DEBUG_PRINTF("\n  <8> : (SARADC8)Start to Hardware trigger with polling mode(single mode) in Core0. ");
        DEBUG_PRINTF("\n  <9> : (SARADC8)Start to Software trigger with polling mode(streaming mode) in Core0. ");
        DEBUG_PRINTF("\n  <a> : (SARADC8)Start to Hardware trigger with polling mode(streaming mode) in Core0. ");
#endif /* defined(THA6_THA6104) */

#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
        DEBUG_PRINTF("\n  <b> : (SARADC1)Start to Software trigger with DMA channel transfer in Core0. ");
        DEBUG_PRINTF("\n  <c> : (SARADC1)Start to Software trigger with DMA channel transfer(Linked list and daisy chain) in Core0. ");
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */
        DEBUG_PRINTF("\n  <d> : (SARADC0)Start to Hardware trigger with conversion result accumulation(Single mode) in Core0. ");
#if defined(THA6_THA6104)
        DEBUG_PRINTF("\n  <e> : (SARADC2)Start to Software trigger with conversion result accumulation(one-shot) in Core0. ");
#else /* not defined(THA6_THA6104) */
        DEBUG_PRINTF("\n  <e> : (SARADC2)Start to Software trigger with conversion result accumulation(one-shot) in Core1. ");
#endif /* defined(THA6_THA6104) */
        DEBUG_PRINTF("\n  <f> : Sync conversion Demo in Core0, master is SARADC0, Slave is SARADC2. ");
#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
        DEBUG_PRINTF("\n  <g> : (SARADC1)Start to Software trigger with DMA channel transfer(All conversion results stored in one register) in Core0. ");
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON)) */
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Adc_DemoCoreExeFlag.DemoStartupFlg = DEMO_STARTED;

        Cmd = DEBUG_GETC();
        if ((Cmd >= '0') && (Cmd <= '9'))
        {
#if defined(THA6_THA6104)
            /* Demo in Core0 */
            Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
#else /* not defined(THA6_THA6104) */
            if ((Cmd >= '3') && (Cmd <= '6'))
            {
                /* Demo in Core1 */
                Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE1;
            }
            else
            {
                /* Demo in Core0 */
                Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
            }
#endif /* defined(THA6_THA6104) */
            Adc_DemoCoreExeFlag.ExeCmdId = (uint8)((uint8)Cmd - (uint8)'0');
        }
        else if ((Cmd >= 'a') && (Cmd < 'x'))
        {
#if defined(THA6_THA6104)
            Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
#else /* not defined(THA6_THA6104) */
            if (Cmd == 'e')
            {
                Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE1;
            }
            else
            {
                Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
            }
#endif /* defined(THA6_THA6104) */
            Adc_DemoCoreExeFlag.ExeCmdId = (uint8)((uint8)Cmd - (uint8)'a') + 10U;
        }
        else if ((Cmd >= 'A') && (Cmd < 'X'))
        {
#if defined(THA6_THA6104)
            Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
#else /* not defined(THA6_THA6104) */
            if (Cmd == 'E')
            {
                Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE1;
            }
            else
            {
                Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
            }
#endif /* defined(THA6_THA6104) */
            Adc_DemoCoreExeFlag.ExeCmdId = (uint8)((uint8)Cmd - (uint8)'A') + 10U;
        }
        else
        {
            if (('x' == Cmd) || ('X' == Cmd))
            {
                ExitFlag = 1U;
                Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
                Adc_DemoCoreExeFlag.ExeCmdId = 254U;
                Adc_DemoCoreExeFlag.DemoStartupFlg = DEMO_IDLE;
            }
            else
            {
                DEBUG_PRINTF("\n\n  INVALID OPTION\n");
            }
        }

        if (0xFFU != Adc_DemoCoreExeFlag.ExeCmdId)
        {
            if (MCAL_CORE0 == Adc_DemoCoreExeFlag.ExeCmdCore)
            {
                /* Call Adc_Demo direct in Core 0 */
                Adc_Demo();
            }

            while (0xFFU != Adc_DemoCoreExeFlag.ExeCmdId)
            {
                /* Waiting till Adc demo test finished */
            }
        }
    }
}

/****************************************************************************************************
*   Function Name           : Adc_Demo
*
*   Service ID              : None.
*
*   Description             : This API shall be called by core which need to ADC driver.
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
void Adc_Demo(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    if (DEMO_STARTED == Adc_DemoCoreExeFlag.DemoStartupFlg)
    {
        if (0U == *Adc_DemoCoreInitStatus[CoreId])
        {
            /* Initialize the Adc */
            Adc_Init(&Adc_ConfigSet[0]);
            *Adc_DemoCoreInitStatus[CoreId] = 1U;
        }
    }
    else
    {
        if (1U == *Adc_DemoCoreInitStatus[CoreId])
        {
            /* De-Initialize the Adc */
            Adc_DeInit();
            *Adc_DemoCoreInitStatus[CoreId] = 0U;
        }
    }

    if ((Adc_DemoCoreExeFlag.ExeCmdCore == CoreId) && (0xFFU != Adc_DemoCoreExeFlag.ExeCmdId))
    {
        switch (Adc_DemoCoreExeFlag.ExeCmdId)
        {
            case 1U:
            {
                Adc_HwTrigSingleWithGtmDemo();
                break;
            }
            case 2U:
            {
                Adc_HwTrigStreamingWithGtmDemo();
                break;
            }
            case 3U:
            {
                Adc_SwTrigContinuousConversionDemo();
                break;
            }
            case 4U:
            {
                Adc_SwTrigWithLimitCheckingDemo();
                break;
            }
            case 5U:
            {
                Adc_SwTrigOneShotConversionDemo();
                break;
            }
            case 6U:
            {
                Adc_SwTrigContinuousStreamingDemo();
                break;
            }
            case 7U:
            {
                Adc_SwTrigPollingSingleDemo();
                break;
            }
            case 8U:
            {
                Adc_HwTrigPollingSingleDemo();
                break;
            }
            case 9U:
            {
                Adc_SwTrigPollingStreamingDemo();
                break;
            }
            case 10U:
            {
                Adc_HwTrigPollingStreamingDemo();
                break;
            }
#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
            case 11U:
            {
                Adc_SwTrigDmaTransferDemo();
                break;
            }
            case 12U:
            {
                Adc_SwTrigDmaTransferWithDaisyChainDemo();
                break;
            }
            case 16U:
            {
                Adc_SwTrigDmaTransferAllChToOneResRegDemo();
                break;
            }
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */
            case 13U:
            {
                Adc_HwTrigSingleWithResultAccumuDemo();
                break;
            }
            case 14U:
            {
                Adc_SwTrigOneShotConversionResultAccumuDemo();
                break;
            }
            case 15U:
            {
                Adc_SyncGroupHwTrigDemo();
                break;
            }
            case 254U:
            {
                if (1U == *Adc_DemoCoreInitStatus[CoreId])
                {
                    *Adc_DemoCoreInitStatus[CoreId] = 0U;
                    Adc_DeInit();
                }
                Adc_DemoCoreExeFlag.ExeCmdId = 255U;
                break;
            }
            default:
            {
                /* Do Nothing */
                break;
            }
        }

        if (0xFEU > Adc_DemoCoreExeFlag.ExeCmdId)
        {
            Adc_DemoCoreExeFlag.ExeCmdId = 0xFFU;
            /* Set to default core */
            Adc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
        }
    }
}

/****************************************************************************************************
*   Function Name           : AdcNotificationGroupx
*
*   Service ID              : None.
*
*   Description             : notification function
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
void AdcDemo_Adc0HwTrigNotif(void)
{
    uint16 ChannelLoop;
    Adc_ValueGroupType ResultBuffer[ADC_HW_TRIG_SINGLE_CHS];

    Adc_GtmTriggerCnt_0++;

    if (E_OK == Adc_ReadGroup(AdcConf_AdcGroup_GroupHwTrig, ResultBuffer))
    {
        /* print Adc result of each group */
        DEBUG_PRINTF("\nNo. :%d: ", Adc_GtmTriggerCnt_0);
        for(ChannelLoop = 0; ChannelLoop < ADC_HW_TRIG_SINGLE_CHS; ChannelLoop++)
        {
            DEBUG_PRINTF("%4u ", ResultBuffer[ChannelLoop]);
        }

        if (Adc_GtmTriggerCnt_0 >= 5U)
        {
            /* Disable Hardware trigger in AdcNotificationGroup1 as they use same gtm channel */
            /*Adc_DisableHardwareTrigger(Adc_Group_Ids[0]);*/
            /* Disable notification */
            Adc_DisableGroupNotification(AdcConf_AdcGroup_GroupHwTrig);
            Adc_DisableHardwareTrigger(AdcConf_AdcGroup_GroupHwTrig);
            DEBUG_PRINTF("\n5 times SARADC0 conversions finished.");
        }
    }
    else
    {
        DEBUG_PRINTF("\nRead SARADC0 conversion result FAILED.");
    }
}

void AdcDemo_Adc0HwTrigRsltAccumNotif(void)
{
    uint16 ChannelLoop;
    Adc_ValueGroupType ResultBuffer[ADC_HW_TRIG_SINGLE_CHS];

    Adc_GtmTriggerCnt_0++;

    if (E_OK == Adc_ReadGroup(AdcConf_AdcGroup_GroupHwResultAccumulation, ResultBuffer))
    {
        /* print Adc result of each group */
        DEBUG_PRINTF("\nNo. %d: ", Adc_GtmTriggerCnt_0);
        for(ChannelLoop = 0; ChannelLoop < ADC_HW_TRIG_SINGLE_CHS; ChannelLoop++)
        {
            DEBUG_PRINTF("%4u ", ResultBuffer[ChannelLoop]);
        }

        if (Adc_GtmTriggerCnt_0 >= 5U)
        {
            /* Disable Hardware trigger in AdcNotificationGroup1 as they use same gtm channel */
            /*Adc_DisableHardwareTrigger(Adc_Group_Ids[0]);*/
            /* Disable notification */
            Adc_DisableGroupNotification(AdcConf_AdcGroup_GroupHwResultAccumulation);
            Adc_DisableHardwareTrigger(AdcConf_AdcGroup_GroupHwResultAccumulation);
            DEBUG_PRINTF("\n5 times SARADC0 conversions finished.");
        }
    }
    else
    {
        DEBUG_PRINTF("\nRead SARADC0 conversion result FAILED.");
    }
}


void AdcDemo_Adc2ContinuousNotif(void)
{
    uint8 ChannelLoop;
    Adc_ValueGroupType ResultBuffer[ADC_SW_CONTINUOUS_CHS];
    Std_ReturnType ret;

    Adc_SwContinuousConversionCnt++;

    /* Read conversion result */
    ret = Adc_ReadGroup(AdcConf_AdcGroup_GroupContinuous, ResultBuffer);
    if (E_OK == ret)
    {
        DEBUG_PRINTF("\nNo. %d: ",
                                 Adc_SwContinuousConversionCnt);
        for(ChannelLoop = 0; ChannelLoop < ADC_SW_CONTINUOUS_CHS; ChannelLoop++)
        {
            DEBUG_PRINTF("%4u ", ResultBuffer[ChannelLoop]);
        }
    }

    /* Continuous conversion 5 times */
    if (Adc_SwContinuousConversionCnt >= 5U)
    {
        /* Disable the notification */
        Adc_DisableGroupNotification(AdcConf_AdcGroup_GroupContinuous);
        /* Stop Conversion */
        Adc_StopGroupConversion(AdcConf_AdcGroup_GroupContinuous);
    }
}

#define ADC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Adc_MemMap.h"

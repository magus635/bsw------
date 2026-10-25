/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dsadc_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DSADC
*
*   brief                 : This file contains Demo application for Dsadc Driver
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
#ifndef THA6_THA6104
/* No DSADC HW unit for THA610X */

#include "Dsadc_Demo.h"
#include "Std_Types.h"
#include "Dsadc_Cfg.h"
#include "Dsadc.h"
#include "Intc.h"
#include "Demo_TestTime.h"
#include "Demo_Common.h"
#include "Pwm.h"
#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
#include "Dma.h"
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

#define DSADC_CONVERSION_WAIT_TIMEOUT      (1000U)
#define DSADC_CONVERSION_WAIT_LONG_TIMEOUT (5000U)

#define DSADC_STREAMING_LINEAR_BUFFER_SAMPLE_NUM                     (5U)
#define DSADC_STREAMING_CIRCULAR_BUFFER_SAMPLE_NUM                   (10U)

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/* Core0 */
#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Dsadc_MemMap.h"

static uint8 Dsadc_DemoInitStatusCore0;

static boolean Dsadc_DemoCircularBufferFullFlag;

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Dsadc_MemMap.h"

/* Core1 */
#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Dsadc_MemMap.h"

static uint8 Dsadc_DemoInitStatusCore1;

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Dsadc_MemMap.h"


/* Core Global variables */
#define DSADC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dsadc_MemMap.h"

static Demo_CoreExeType Dsadc_DemoCoreExeFlag = {(Mcal_CoreType)0U, 0xFFU, DEMO_IDLE};

#define DSADC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dsadc_MemMap.h"

#define DSADC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dsadc_MemMap.h"

Dsadc_ResultType DsadcDemo_MainConvResult[DSADC_DEMO_CONVERSION_NUM];

static boolean DsadcDemo_MasterCoreInitFlag;

#define DSADC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dsadc_MemMap.h"

#define DSADC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Dsadc_MemMap.h"

static uint8 * const Dsadc_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES] =
{
    &Dsadc_DemoInitStatusCore0,
    &Dsadc_DemoInitStatusCore1
};

#define DSADC_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Dsadc_MemMap.h"

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
#define DSADC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dsadc_MemMap.h"

static void Dsadc_SingleAccessConversionDemo(void);
static void Dsadc_StreamingWithLinearBufferDemo(void);
static void Dsadc_StreamingWithCircularBufferDemo(void);

#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
static void Dsadc_SingleAccessConversionWithDmaDemo(void);
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Dsadc_Result2VoltageDiff
*
*   Service ID              : None.
*
*   Description             : Calculate the voltage value through the sampling results
*                             (differential mode).
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous
*
*   Reentrancy              : Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static float32 Dsadc_Result2VoltageDiff(sint16 ResultVal)
{
    float32 Volt;

    Volt = ((float32)ResultVal + 0.5f) / 3276.7f;

    return Volt;
}

/****************************************************************************************************
*   Function Name           : Dsadc_Result2VoltageSigle
*
*   Service ID              : None.
*
*   Description             : Calculate the voltage value through the sampling results
*                             (Single mode).
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
static float32 Dsadc_Result2VoltageSingle(sint16 ResultVal)
{
    float32 Volt;

    Volt = ((float32)ResultVal + 16384.0f) / 6553.4f;

    return Volt;
}

/****************************************************************************************************
*   Function Name           : Dsadc_SingleAccessConversionDemo
*
*   Service ID              : None.
*
*   Description             : PWM trigger DSADC sampling with a period of 1ms.
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
static void Dsadc_SingleAccessConversionDemo(void)
{
    Dsadc_StatusType MainChStatus;
    Dsadc_StatusType AuxChStatus;
    Std_ReturnType Err;
    Dsadc_ResultType Temp_ResultBuf[2];
    Dsadc_TimestampType TimestampValue;
    uint32 WaitLoop;

    Pwm_Init(&Pwm_ConfigSet[0]);
    Timer_DelayMs(20);    /* Waiting some time */

    /* Enable the interrupt source: DSADC0 */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_439);    /* Auxiliary conversion channel */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_440);    /* Main conversion channel */

    /* Setup the user buffer */
    Err = Dsadc_SetupResultBuffer(DsadcConf_DsadcChannel_SingleInt, &DsadcDemo_MainConvResult[0]);
    if (E_OK == Err)
    {
        Err = E_NOT_OK;
        /* Start modular: Digital-to-digital conversion will start */
        (void)Dsadc_StartConversion(DsadcConf_DsadcChannel_SingleInt);
        /* Clear buffer */
        DsadcDemo_MainConvResult[0] = 0;
        DsadcDemo_MainConvResult[1] = 0;

        /* Delay 100ms */
        Timer_DelayMs(100);
        DEBUG_PRINTF("\nDelay100ms\n");

        for (WaitLoop = 0U; WaitLoop < DSADC_CONVERSION_WAIT_TIMEOUT; WaitLoop++)
        {
            /* Get main conversion channel status */
            MainChStatus = Dsadc_GetChannelStatus(DsadcConf_DsadcChannel_SingleInt,
                                                  DSADC_CONV_CHANNEL_MAIN);
            /* Get auxiliary channel status */
            AuxChStatus = Dsadc_GetChannelStatus(DsadcConf_DsadcChannel_SingleInt,
                                                 DSADC_CONV_CHANNEL_AUX);
            if ((DSADC_STREAM_COMPLETED == MainChStatus) && (DSADC_STREAM_COMPLETED == AuxChStatus))
            {
                /* Main conversion channel is completed */
                /* Read the conversion result directly from the result buffer */
                /* Read main conversion channel result */
                Temp_ResultBuf[0] = DsadcDemo_MainConvResult[0];
                /* Read auxiliary conversion channel result */
                Temp_ResultBuf[1] = DsadcDemo_MainConvResult[1];
                /* Read timestamp value */
                TimestampValue = Dsadc_GetTimestamp(DsadcConf_DsadcChannel_SingleInt);
                if (0U != TimestampValue)
                {
                    Err = E_OK;
                    break;
                }
            }
        }
    }

    if (E_OK == Err)
    {
        DEBUG_PRINTF("\nMain conversion channel result: %d", Temp_ResultBuf[0]);
        DEBUG_PRINTF("\nConvert to voltage is %fV", Dsadc_Result2VoltageDiff(Temp_ResultBuf[0]));
        DEBUG_PRINTF("\nTimestamp value is: %d", TimestampValue);
        DEBUG_PRINTF("\nAuxiliary conversion channel result: %d", Temp_ResultBuf[1]);
        DEBUG_PRINTF("\n\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    /* Get current status */
    MainChStatus = Dsadc_GetChannelStatus(DsadcConf_DsadcChannel_SingleInt, DSADC_CONV_CHANNEL_MAIN);
    AuxChStatus = Dsadc_GetChannelStatus(DsadcConf_DsadcChannel_SingleInt, DSADC_CONV_CHANNEL_AUX);
    if ((DSADC_IDLE != MainChStatus) || (DSADC_IDLE != AuxChStatus))
    {
        /* Stop modular: Analog-to-digital conversion will stop */
        (void)Dsadc_StopConversion(DsadcConf_DsadcChannel_SingleInt);
    }

    /* Disable the interrupt source: DSADC0 */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_439);    /* Auxiliary conversion channel */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_440);    /* Main conversion channel */

    Pwm_DeInit();
}

/****************************************************************************************************
*   Function Name           : Dsadc_StreamingWithLinearBufferDemo
*
*   Service ID              : None.
*
*   Description             :
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
static void Dsadc_StreamingWithLinearBufferDemo(void)
{
    Dsadc_NumSampleType ResultLoop;
    Dsadc_NumSampleType ResultNum;
    Std_ReturnType Err;
    Dsadc_ResultType *ResultPtr;
    Dsadc_StatusType ChStatus;
    uint32 WaitLoop;

    /* Enable the interrupt */
    /* Enable the interrupt source: DSADC1 */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_441);    /* Auxiliary conversion channel */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_442);    /* Main conversion channel */

    /* Clear result buffer */
    for (ResultLoop = 0U; ResultLoop < DSADC_STREAMING_LINEAR_BUFFER_SAMPLE_NUM; ResultLoop++)
    {
        DsadcDemo_MainConvResult[ResultLoop] = 0;
    }

    /* Setup the user buffer */
    Err = Dsadc_SetupResultBuffer(DsadcConf_DsadcChannel_StreamingLinear, &DsadcDemo_MainConvResult[0]);
    if (E_OK == Err)
    {
        Err = E_NOT_OK;

        /* Delay 100ms and waiting for modulator and demodulator stability */
        Timer_DelayMs(100);
        DEBUG_PRINTF("\nDelay100ms\n");

        /* Start modular: Digital-to-digital conversion will start */
        (void)Dsadc_StartConversion(DsadcConf_DsadcChannel_StreamingLinear);

        for (WaitLoop = 0U; WaitLoop < DSADC_CONVERSION_WAIT_TIMEOUT; WaitLoop++)
        {
            Timer_DelayMs(1);    /* Waiting 1ms */
            /* Get main conversion result pointer and valid result number */
            ResultNum = Dsadc_GetStreamLastPointer(DsadcConf_DsadcChannel_StreamingLinear, &ResultPtr);
            if (DSADC_STREAMING_LINEAR_BUFFER_SAMPLE_NUM == ResultNum)
            {
                /* Linear buffer is full */
                DEBUG_PRINTF("\nLatest conversion result is: %d", ResultPtr[0]);
                DEBUG_PRINTF("\nConvert to voltage is %.2fV", Dsadc_Result2VoltageSingle(ResultPtr[0]));
                Err = E_OK;
                break;
            }
        }
    }

    if (E_OK == Err)
    {
        DEBUG_PRINTF("\nAll conversion results of main conversion channel: \n");
        /* Conversion success */
        for (ResultLoop = 0U; ResultLoop < DSADC_STREAMING_LINEAR_BUFFER_SAMPLE_NUM; ResultLoop++)
        {
            DEBUG_PRINTF("%d->%.2fV  ", DsadcDemo_MainConvResult[ResultLoop],
                                        Dsadc_Result2VoltageSingle(DsadcDemo_MainConvResult[ResultLoop]));
        }

        DEBUG_PRINTF("\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    ChStatus = Dsadc_GetChannelStatus(DsadcConf_DsadcChannel_StreamingLinear, DSADC_CONV_CHANNEL_MAIN);
    if (DSADC_IDLE != ChStatus)
    {
        /* Stop modular: Analog-to-digital conversion will stop */
        (void)Dsadc_StopConversion(DsadcConf_DsadcChannel_StreamingLinear);
    }

    /* Disable the interrupt source: DSADC0 */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_441);    /* Auxiliary conversion channel */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_442);    /* Main conversion channel */
}

/****************************************************************************************************
*   Function Name           : Dsadc_StreamingWithCircularBufferDemo
*
*   Service ID              : None.
*
*   Description             :
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
static void Dsadc_StreamingWithCircularBufferDemo(void)
{
    Dsadc_NumSampleType ResultLoop;
    Std_ReturnType Err;
    uint32 WaitLoop;

    /* Enable the interrupt */
    /* Enable the interrupt source: DSADC2 */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_443);    /* Auxiliary conversion channel */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_444);    /* Main conversion channel */

    for (ResultLoop = 0U; ResultLoop < DsadcConf_DsadcChannel_StreamingCircular; ResultLoop++)
    {
        DsadcDemo_MainConvResult[ResultLoop] = 0;
    }

    Dsadc_DemoCircularBufferFullFlag = FALSE;

    /* Setup the user buffer */
    Err = Dsadc_SetupResultBuffer(DsadcConf_DsadcChannel_StreamingCircular, &DsadcDemo_MainConvResult[0]);
    if (E_OK == Err)
    {
        Err = E_NOT_OK;

        /* Enable the notification */
        Dsadc_EnableNotification(DsadcConf_DsadcChannel_StreamingCircular);

        /* Delay 100ms and waiting for modulator and demodulator stability */
        Timer_DelayMs(100);
        DEBUG_PRINTF("\nDelay100ms\n");

        /* Start modular: Digital-to-digital conversion will start */
        (void)Dsadc_StartConversion(DsadcConf_DsadcChannel_StreamingCircular);

        for (WaitLoop = 0U; WaitLoop < DSADC_CONVERSION_WAIT_TIMEOUT; WaitLoop++)
        {
            Timer_DelayMs(1);    /* Waiting 1ms */
            if (TRUE == Dsadc_DemoCircularBufferFullFlag)
            {
                /* Buffer full */
                Err = E_OK;
                break;
            }
        }
    }

    if (E_OK == Err)
    {
        DEBUG_PRINTF("\nAll conversion results of main conversion channel: \n");
        for (ResultLoop = 0U;
                ResultLoop < DSADC_STREAMING_CIRCULAR_BUFFER_SAMPLE_NUM; ResultLoop++)
        {
            DEBUG_PRINTF("%d  ", DsadcDemo_MainConvResult[ResultLoop]);
        }

        DEBUG_PRINTF("\n\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    /* Disable the notification */
    Dsadc_DisableNotification(DsadcConf_DsadcChannel_StreamingCircular);
    /* Disable the interrupt source: DSADC0 */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_443);    /* Auxiliary conversion channel */
    Intc_DisableInterrupt(INTC_INTSRC_NUM_444);    /* Main conversion channel */
}


#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
/****************************************************************************************************
*   Function Name           : Dsadc_SingleAccessConversionWithDmaDemo
*
*   Service ID              : None.
*
*   Description             : In DMA mode, single access, one-shot conversion,
*                             streaming access mode with linear buffer, Software trigger.
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
static void Dsadc_SingleAccessConversionWithDmaDemo(void)
{
    Dsadc_StatusType MainChStatus;
    Std_ReturnType Err = E_NOT_OK;
    uint32 WaitLoop;
    uint8 ResultLoop;

    /* Initialize the Dma driver */
    Dma_Init(&Dma_ConfigSet[0]);

    /* Start Dma channel */
    Dma_ChannelStart(DmaConf_DmaChannel_Dsadc3);

    /* Start modular: Digital-to-digital conversion will start */
    (void)Dsadc_StartConversion(DsadcConf_DsadcChannel_SingleDma);

    /* Clear buffer */
    for (ResultLoop = 0U; ResultLoop < DSADC_DEMO_CONVERSION_NUM; ResultLoop++)
    {
        DsadcDemo_MainConvResult[ResultLoop] = (Dsadc_ResultType)0xFFFF;
    }

    for (WaitLoop = 0U; WaitLoop < DSADC_CONVERSION_WAIT_TIMEOUT; WaitLoop++)
    {
        Timer_DelayMs(1);    /* Waiting 1ms */
        if ((Dsadc_ResultType)0xFFFF != DsadcDemo_MainConvResult[DSADC_DEMO_CONVERSION_NUM - 1U])
        {
            /* Dma channel auto transfer success */
            Err = E_OK;
            break;
        }
    }

    if (E_OK == Err)
    {
        DEBUG_PRINTF("\nMain conversion channel result: \n");
        for (ResultLoop = 0U; ResultLoop < DSADC_DEMO_CONVERSION_NUM; ResultLoop++)
        {
            DEBUG_PRINTF("%d  ", DsadcDemo_MainConvResult[ResultLoop]);
        }
        DEBUG_PRINTF("\n\nTest Result = PASS");
    }
    else
    {
        DEBUG_PRINTF("\nTest Result = FAIL");
    }

    /* Get current status */
    MainChStatus = Dsadc_GetChannelStatus(DsadcConf_DsadcChannel_SingleDma, DSADC_CONV_CHANNEL_MAIN);
    if (DSADC_IDLE != MainChStatus)
    {
        /* Stop modular: Analog-to-digital conversion will stop */
        (void)Dsadc_StopConversion(DsadcConf_DsadcChannel_SingleDma);
    }

    /* Stop Dma channel */
    Dma_ChannelCancel(DmaConf_DmaChannel_Dsadc3, DMA_CH_CANCEL_DIRECT);
    /* De-initialize the Dma */
    Dma_DeInit();
}

#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : Dsadc_DemoEntry
*
*   Service ID              : None.
*
*   Description             : DSADC demo entry.
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
void Dsadc_DemoEntry(void)
{
    char Cmd;
    uint8 ExitFlag;
    Std_VersionInfoType Dsadc_ver;

    Dsadc_Init(&Dsadc_ConfigSet[0]);
    DsadcDemo_MasterCoreInitFlag = TRUE;
    Dsadc_DemoCoreExeFlag.DemoStartupFlg = DEMO_STARTED;

    ExitFlag = 0U;
    while (0U == ExitFlag)
    {
        Dsadc_GetVersionInfo(&Dsadc_ver);
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*********************************************************/");
        DEBUG_PRINTF("\n           DSADC DRIVER DEMO MENU V%02d.%02d.%02d            ",
               Dsadc_ver.sw_major_version, Dsadc_ver.sw_minor_version, Dsadc_ver.sw_patch_version);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : (DSADC0)Start to conversion: single access mode, GTM trigger0(PWM) trigger.");
        DEBUG_PRINTF("\n  <2> : (DSADC1)Start to conversion: streaming access mode, linear buffer, Software trigger.");
        DEBUG_PRINTF("\n  <3> : (DSADC2)Start to conversion: streaming access mode, circular buffer, Software trigger. ");
#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
        DEBUG_PRINTF("\n  <4> : (DSADC3)Start to conversion: streaming access mode, linear buffer, DMA result handling, Hardware trigger.");
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Cmd = DEBUG_GETC();
        if ((Cmd >= '0') && (Cmd <= '9'))
        {
            if ((Cmd >= '3') && (Cmd <= '6'))
            {
                Dsadc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
            }
            else
            {
                Dsadc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
            }
            Dsadc_DemoCoreExeFlag.ExeCmdId = (uint8)((uint8)Cmd - (uint8)'0');
        }
        else if ((Cmd >= 'a') && (Cmd < 'x'))
        {
            Dsadc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
            Dsadc_DemoCoreExeFlag.ExeCmdId = (uint8)((uint8)Cmd - (uint8)'a') + 10U;
        }
        else if ((Cmd >= 'A') && (Cmd < 'X'))
        {
            Dsadc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
            Dsadc_DemoCoreExeFlag.ExeCmdId = (uint8)((uint8)Cmd - (uint8)'A') + 10U;
        }
        else
        {
            if (('x' == Cmd) || ('X' == Cmd))
            {
                ExitFlag = 1U;
                Dsadc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
                Dsadc_DemoCoreExeFlag.ExeCmdId = 255U;
                Dsadc_DemoCoreExeFlag.DemoStartupFlg = DEMO_IDLE;

                /* waiting for slave de-init */
                Timer_DelayMs(200);

                Dsadc_DeInit();
                DsadcDemo_MasterCoreInitFlag = FALSE;
            }
            else
            {
                DEBUG_PRINTF("\n\n  INVALID OPTION\n");
            }
        }

        if (0xFFU != Dsadc_DemoCoreExeFlag.ExeCmdId)
        {
            if (MCAL_CORE0 == Dsadc_DemoCoreExeFlag.ExeCmdCore)
            {
                /* Call Dsadc_Demo direct in Core 0 */
                Dsadc_Demo();
            }

            while(0xFFU != Dsadc_DemoCoreExeFlag.ExeCmdId)
            {
                /* Waiting till Dsadc demo test finished */
            }
        }
    }
}

/****************************************************************************************************
*   Function Name           : Dsadc_Demo
*
*   Service ID              : None.
*
*   Description             : This API shall be called by core which need to DSADC driver.
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
void Dsadc_Demo(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    if (DEMO_STARTED == Dsadc_DemoCoreExeFlag.DemoStartupFlg)
    {
        if (0U == *Dsadc_DemoCoreInitStatus[CoreId])
        {
            if ((TRUE == DsadcDemo_MasterCoreInitFlag) && (MCAL_MASTER_CORE != CoreId))
            {
                /* Initialize the Dsadc */
                Dsadc_Init(&Dsadc_ConfigSet[0]);
                *Dsadc_DemoCoreInitStatus[CoreId] = 1U;
            }
        }
    }
    else
    {
        if (1U == *Dsadc_DemoCoreInitStatus[CoreId])
        {
            /* De-Initialize the Dsadc */
            Dsadc_DeInit();
            *Dsadc_DemoCoreInitStatus[CoreId] = 0U;
        }
    }

    if ((Dsadc_DemoCoreExeFlag.ExeCmdCore == CoreId) && (0xFFU != Dsadc_DemoCoreExeFlag.ExeCmdId))
    {
        switch (Dsadc_DemoCoreExeFlag.ExeCmdId)
        {
            case 1U:
            {
                Dsadc_SingleAccessConversionDemo();
                break;
            }
            case 2U:
            {
                Dsadc_StreamingWithLinearBufferDemo();
                break;
            }
            case 3U:
            {
                Dsadc_StreamingWithCircularBufferDemo();
                break;
            }
#if (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED == STD_ON))
            case 4U:
            {
                Dsadc_SingleAccessConversionWithDmaDemo();
                break;
            }
#endif /* (defined(MCAL_MODULE_CFG_DMA_USED) && (MCAL_MODULE_CFG_DMA_USED \== STD_ON)) */
            default:
            {
                /* Do Nothing */
                break;
            }
        }

        if (0xFEU > Dsadc_DemoCoreExeFlag.ExeCmdId)
        {
            Dsadc_DemoCoreExeFlag.ExeCmdId = 0xFFU;
            Dsadc_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
        }
    }
}

/****************************************************************************************************
*   Function Name           : DsadcBufferFillNotification
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
void DsadcDemo_CircularBufferFull(void)
{
    Dsadc_DemoCircularBufferFullFlag = TRUE;

    if (DSADC_STREAM_COMPLETED ==
          Dsadc_GetChannelStatus(DsadcConf_DsadcChannel_StreamingCircular, DSADC_CONV_CHANNEL_MAIN))
    {
        /* Stop modular: Digital-to-digital conversion will stop */
        (void)Dsadc_StopConversion(DsadcConf_DsadcChannel_StreamingCircular);
    }
}

#define DSADC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dsadc_MemMap.h"

#endif /* #ifndef THA6_THA6104 */

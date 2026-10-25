/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Spi_Demo.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : ESPI
 *
 *   brief                 : This file contains Demo application for Spi Driver.
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
#include "Spi_Demo.h"
#include "Spi.h"
#if (SPI_ENABLE_DMA == STD_ON)
#include "Dma.h"
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
typedef volatile struct
{
    /* The core which shall execute the command */
    /* This variable can only be changed by Core0(master) */
    Mcal_CoreType       ExeCmdCore;
    /* The command code */
    uint8               ExeCmd;
    /* Demo Entry flag */
    Demo_StartupType    DemoStartupFlg;
} Spi_CoreExeType;

#define SPI_SYNC_CHANNEL_NUM    (6U)
#define SPI_ASYNC_CHANNEL_NUM   (6U)

#define SPI_DATA_LENGTH_0       (5U)
#define SPI_DATA_LENGTH_1       (5U)
#define SPI_DATA_LENGTH_2       (5U)

#define SPI_DATA_LENGTH_3       (5U)
#define SPI_DATA_LENGTH_4       (5U)
#define SPI_DATA_LENGTH_5       (3U)
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define SPI_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Spi_MemMap.h"

static uint8 Sync_Channel_Data_Num[SPI_SYNC_CHANNEL_NUM] =
{
    SPI_DATA_LENGTH_0,
    SPI_DATA_LENGTH_1,
    SPI_DATA_LENGTH_2,
    SPI_DATA_LENGTH_3,
    SPI_DATA_LENGTH_4,
    SPI_DATA_LENGTH_5
};

static uint8 SampleApp_ucSource_0[SPI_DATA_LENGTH_0] = {0x12U, 0x34U, 0xabU, 0xcdU, 0xf0U};
static uint16 SampleApp_ucSource_1[SPI_DATA_LENGTH_1] = {0x2345U, 0x9876U, 0x89abU, 0xfedcU, 0xef01U};
static uint32 SampleApp_ucSource_2[SPI_DATA_LENGTH_2] = {0x11223344U, 0xaabbccddU, 0x00ff4488U, 0xffeeccddU, 0x99775533U};

static uint8 SampleApp_ucSource_3[SPI_DATA_LENGTH_3] = {0x13U, 0x34U, 0x56U, 0x78U, 0x9aU};
static uint16 SampleApp_ucSource_4[SPI_DATA_LENGTH_4] = {0x1234U, 0x4567U, 0x789aU, 0xbcdeU, 0xf012U};
static uint32 SampleApp_ucSource_5[SPI_DATA_LENGTH_5] = {0x12345678U, 0x9abcdef0U, 0x13579bdfU};

static Spi_AsyncModeType Async_transmit_mode = SPI_POLLING_MODE;

static Spi_CoreExeType Spi_DemoCoreExeFlag = {MCAL_CORE0, 0xFFU, DEMO_IDLE};

#define SPI_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Spi_MemMap.h"

#define SPI_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Spi_MemMap.h"

static uint8 SampleApp_ucDest_0[SPI_DATA_LENGTH_0];
static uint16 SampleApp_ucDest_1[SPI_DATA_LENGTH_1];
static uint32 SampleApp_ucDest_2[SPI_DATA_LENGTH_2];
static uint8 SampleApp_ucDest_3[SPI_DATA_LENGTH_3];
static uint16 SampleApp_ucDest_4[SPI_DATA_LENGTH_4];
static uint32 SampleApp_ucDest_5[SPI_DATA_LENGTH_5];

static uint8 Job_transmit_flg;
static uint8 Seq_transmit_flg;

static uint8 Spi_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES];

#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Spi_MemMap.h"
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
**                          Global Function Definitions                                            **
****************************************************************************************************/
void Spi_JobNotificationTest0(void);
void Spi_JobNotificationTest1(void);
void Spi_SeqNotificationTest0(void);
void Spi_SeqNotificationTest1(void);
/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#define SPI_START_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"

static void Spi_TransmitDemo(boolean SyncFlag);
static Std_ReturnType Spi_BufferComp8(uint8 *srcBufferPtr, uint8 *desBufferPtr, uint8 dataLength);
static Std_ReturnType Spi_BufferComp16(uint16 *srcBufferPtr, uint16 *desBufferPtr, uint8 dataLength);
static Std_ReturnType Spi_BufferComp32(uint32 *srcBufferPtr, uint32 *desBufferPtr, uint8 dataLength);
#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
#define SPI_START_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"
/****************************************************************************************************
*   Function Name           : Spi_TransmitDemo
*
*   Service ID              : None.
*
*   Description             : Demo for Spi synchronize transmission
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
/* Spi Sequence0:
 *     Spi Job0:  [Spi External Device0 - SPI0]
 *         Spi Channel0
 *         Spi Channel1
 *         Spi Channel2
 * Spi Sequence1:
 *     Spi Job1:  [Spi External Device1 - SPI2]
 *         Spi Channel3
 *         Spi Channel4
 *         Spi Channel5
 *
 * SyncCore0--SPI0--Core0:
 *     SCLK:                        P20.11
 *     SLSO1(Spi External Device0): P20.9
 *     MTSR:                        P20.14
 *     MRST:                        P20.12
 * SyncCore1--SPI2--Core1:
 *     SCLK:                        P15.8
 *     SLSO(Spi External Device1):  P14.9
 *     MTSR:                        P15.6
 *     MRST:                        P15.7
 *  */
static void Spi_TransmitDemo(boolean SyncFlag)
{
    uint8               ChannelNumLoop;
    uint8               Result;
    volatile uint32     LoopCnt;

    if(MCAL_CORE0 == Spi_DemoCoreExeFlag.ExeCmdCore)
    {
        /* Setup external buffers */
        (void)Spi_SetupEB(SpiConf_SpiChannel_SpiChannel_0,
                    (Spi_DataBufferType*)&SampleApp_ucSource_0,
                    (Spi_DataBufferType*)&SampleApp_ucDest_0,
                    SPI_DATA_LENGTH_0);
        (void)Spi_SetupEB(SpiConf_SpiChannel_SpiChannel_1,
                    (Spi_DataBufferType*)&SampleApp_ucSource_1,
                    (Spi_DataBufferType*)&SampleApp_ucDest_1,
                    SPI_DATA_LENGTH_1);
        (void)Spi_SetupEB(SpiConf_SpiChannel_SpiChannel_2,
                    (Spi_DataBufferType*)&SampleApp_ucSource_2,
                    (Spi_DataBufferType*)&SampleApp_ucDest_2,
                    SPI_DATA_LENGTH_2);
        if (TRUE == SyncFlag)
        {
            /* Sync transmit data */
            (void)Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_0);
        }
        else
        {
            /* Async transmit data */
            (void)Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence_0);
            /* Timeout is 1s */
            LoopCnt = 0U;
            while ((SPI_IDLE != Spi_GetHWUnitStatus(SpiConf_SpiHwUnitConfig_SPI0)) && (LoopCnt < 1000U))
            {
                if ((SPI_POLLING_MODE == Async_transmit_mode))
                {
                    /* Spi_MainFunction_Handling() can only be called in the core that
                        the HW unit is allocated */
                    Spi_MainFunction_Handling();
                }
                /* As for interrupt mode: For avoid occupy the interrupt handler in core3 long time,
                    and make other code can not be running normal */
                Timer_DelayMs(1);
                LoopCnt++;
            }
        }
        Result = 0U;
        Result += (uint8)Spi_BufferComp8((uint8 *)SampleApp_ucSource_0, SampleApp_ucDest_0, SPI_DATA_LENGTH_0);
        Result += (uint8)Spi_BufferComp16((uint16 *)SampleApp_ucSource_1, SampleApp_ucDest_1, SPI_DATA_LENGTH_1);
        Result += (uint8)Spi_BufferComp32((uint32 *)SampleApp_ucSource_2, SampleApp_ucDest_2, SPI_DATA_LENGTH_2);

        DEBUG_PRINTF("\r\nRecevied Data List0:");
        for(ChannelNumLoop = 0; ChannelNumLoop < Sync_Channel_Data_Num[0]; ChannelNumLoop++)
        {
            DEBUG_PRINTF("      0x%02x ", SampleApp_ucDest_0[ChannelNumLoop]);
            /* Clear data buffer */
            SampleApp_ucDest_0[ChannelNumLoop] = 0U;
        }

        DEBUG_PRINTF("\nRecevied Data List1:");
        for(ChannelNumLoop = 0; ChannelNumLoop < Sync_Channel_Data_Num[1]; ChannelNumLoop++)
        {
            DEBUG_PRINTF("    0x%04x ", SampleApp_ucDest_1[ChannelNumLoop]);
            /* Clear data buffer */
            SampleApp_ucDest_1[ChannelNumLoop] = 0U;
        }

        DEBUG_PRINTF("\nRecevied Data List2:");
        for(ChannelNumLoop = 0; ChannelNumLoop < Sync_Channel_Data_Num[2]; ChannelNumLoop++)
        {
            DEBUG_PRINTF("0x%08x ", SampleApp_ucDest_2[ChannelNumLoop]);
            /* Clear data buffer */
            SampleApp_ucDest_2[ChannelNumLoop] = 0U;
        }
    }
    else
    {
        /* Write the internal buffers */
        (void)Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_3, (Spi_DataBufferType*)SampleApp_ucSource_3);
        (void)Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_4, (Spi_DataBufferType*)SampleApp_ucSource_4);
        (void)Spi_WriteIB(SpiConf_SpiChannel_SpiChannel_5, (Spi_DataBufferType*)SampleApp_ucSource_5);
        if (TRUE == SyncFlag)
        {
            /* Sync transmit data */
            (void)Spi_SyncTransmit(SpiConf_SpiSequence_SpiSequence_1);
        }
        else
        {
            /* Async transmit data */
            (void)Spi_AsyncTransmit(SpiConf_SpiSequence_SpiSequence_1);
            /* Timeout is 1s */
            LoopCnt = 0U;
            while ((SPI_IDLE != Spi_GetHWUnitStatus(SpiConf_SpiHwUnitConfig_SPI2)) && (LoopCnt < 1000U))
            {
                if ((SPI_POLLING_MODE == Async_transmit_mode))
                {
                    /* Spi_MainFunction_Handling() can only be called in the core that
                        the HW unit is allocated */
                    Spi_MainFunction_Handling();
                }
                /* As for interrupt mode: For avoid occupy the interrupt handler in core3 long time,
                    and make other code can not be running normal */
                Timer_DelayMs(1);
                LoopCnt++;
            }
        }
        /* Read data from internal buffer */
        (void)Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_3, (Spi_DataBufferType*)SampleApp_ucDest_3);
        (void)Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_4, (Spi_DataBufferType*)SampleApp_ucDest_4);
        (void)Spi_ReadIB(SpiConf_SpiChannel_SpiChannel_5, (Spi_DataBufferType*)SampleApp_ucDest_5);
        Result = 0U;
        Result += (uint8)Spi_BufferComp8((uint8*)SampleApp_ucSource_3, SampleApp_ucDest_3, SPI_DATA_LENGTH_3);
        Result += (uint8)Spi_BufferComp16((uint16*)SampleApp_ucSource_4, SampleApp_ucDest_4, SPI_DATA_LENGTH_4);
        Result += (uint8)Spi_BufferComp32((uint32*)SampleApp_ucSource_5, SampleApp_ucDest_5, SPI_DATA_LENGTH_5);
        DEBUG_PRINTF("\nRecevied Data List3:");
        for(ChannelNumLoop = 0; ChannelNumLoop < Sync_Channel_Data_Num[3]; ChannelNumLoop++)
        {
            DEBUG_PRINTF("      0x%02x ", SampleApp_ucDest_3[ChannelNumLoop]);
            /* Clear data buffer */
            SampleApp_ucDest_3[ChannelNumLoop] = 0U;
        }

        DEBUG_PRINTF("\nRecevied Data List4:");
        for(ChannelNumLoop = 0; ChannelNumLoop < Sync_Channel_Data_Num[4]; ChannelNumLoop++)
        {
            DEBUG_PRINTF("    0x%04x ", SampleApp_ucDest_4[ChannelNumLoop]);
            /* Clear data buffer */
            SampleApp_ucDest_4[ChannelNumLoop] = 0U;
        }

        DEBUG_PRINTF("\nRecevied Data List5:");
        for(ChannelNumLoop = 0; ChannelNumLoop < Sync_Channel_Data_Num[5]; ChannelNumLoop++)
        {
            DEBUG_PRINTF("0x%08x ", SampleApp_ucDest_5[ChannelNumLoop]);
            /* Clear data buffer */
            SampleApp_ucDest_5[ChannelNumLoop] = 0U;
        }
    }
    if(0U == Result && TRUE == SyncFlag)
    {
        DEBUG_PRINTF("\r\nSynchronous Test SUCCESS!!!");
    }
    else if(0U == LoopCnt && TRUE == SyncFlag)
    {
        DEBUG_PRINTF("\r\nSynchronous Test FAILED: Transmission timeout!!!");
    }
    else if(0U == Result && FALSE == SyncFlag)
    {
        DEBUG_PRINTF("\r\nAsynchronous Test SUCCESS!!!");
    }
    else if(0U == LoopCnt && FALSE == SyncFlag)
    {
        DEBUG_PRINTF("\r\nAsynchronous Test FAILED: Transmission timeout!!!");
    }
    else if(TRUE == SyncFlag)
    {
        DEBUG_PRINTF("\r\nSynchronous Test FAILED: sending and receiving data are inconsistent!!!");
    }
    else
    {
        DEBUG_PRINTF("\r\nAsynchronous Test FAILED: sending and receiving data are inconsistent!!!");
    }
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Spi_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Spi demo entry function.
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
void Spi_DemoEntry(void)
{
    char                cmd;
    uint8               Exit;
    Std_VersionInfoType Spi_ver;

    /* Initialize the Dma in core0 */
    Dma_Init(&Dma_ConfigSet[0]);
    Exit = 0U;
    while (0U == Exit)
    {
        Spi_GetVersionInfo(&Spi_ver);
        DEBUG_PRINTF("\n\n");
        DEBUG_PRINTF("\n/*********************************************************/");
        DEBUG_PRINTF("\n           SPI DRIVER DEMO MENU V%02d.%02d.%02d            ",
                Spi_ver.sw_major_version, Spi_ver.sw_minor_version, Spi_ver.sw_patch_version);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF((const uint8*)"\n  <1> : Spi Demo is executed on Core0. ");
#if ((MCAL_USED_CORE_MASK&MCAL_CORE1_MASK) == MCAL_CORE1_MASK)
        DEBUG_PRINTF((const uint8*)"\n  <2> : Spi Demo is executed on Core1. ");
#endif /* ((MCAL_USED_CORE_MASK&MCAL_CORE1_MASK) == MCAL_CORE1_MASK) */
        DEBUG_PRINTF((const uint8 *)"\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF((const uint8 *)"\n  ENTER YOUR OPTION   : ");

        Spi_DemoCoreExeFlag.DemoStartupFlg = DEMO_STARTED;

        cmd = DEBUG_GETC();

        switch ((char)cmd)
        {
            case '1':
            {
                /* Demo for Core0 */
                Spi_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
                DEBUG_PRINTF((const uint8 *)"\n  Choose the Core0\n");
                Spi_DemoSelect();
                break;
            }
#if ((MCAL_USED_CORE_MASK & MCAL_CORE1_MASK) == MCAL_CORE1_MASK)
            case '2':
            {
#if (STD_ON == DEMO_PRINTQUEUEMODE)
                /* Demo for Core1 */
                Spi_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE1;
                DEBUG_PRINTF((const uint8 *)"\n  Choose the Core1\n");
                Spi_DemoSelect();
#else
                DEBUG_PRINTF((const uint8 *)"\n  The macro of DEMO_PRINTQUEUEMODE is STD_OFF, Does Not support Core1 printing.\n");
#endif
                break;
            }
#endif /* ((MCAL_USED_CORE_MASK&MCAL_CORE1_MASK) == MCAL_CORE1_MASK) */
            case 'x':
            case 'X':
            {
                Exit = 1U;
                Spi_DemoCoreExeFlag.DemoStartupFlg = DEMO_IDLE;
                break;
            }
            default:
            {
                /* Do Nothing */
                break;
            }
        }
    }
    Dma_DeInit();
}

/****************************************************************************************************
*   Function Name           : Spi_DemoSelect
*
*   Service ID              : None.
*
*   Description             : Spi demo executes Core selection function.
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
void Spi_DemoSelect(void)
{
    char                cmd;
    uint8               Exit;
    Std_VersionInfoType Spi_ver;

    Exit = 0U;
    while (0U == Exit)
    {
        Spi_GetVersionInfo(&Spi_ver);
        DEBUG_PRINTF("\n\n");
        DEBUG_PRINTF("\n/*********************************************************/");
        DEBUG_PRINTF("\n           SPI DRIVER DEMO MENU V%02d.%02d.%02d            ",
                Spi_ver.sw_major_version, Spi_ver.sw_minor_version, Spi_ver.sw_patch_version);
        DEBUG_PRINTF("\n                                                         ");
        if(MCAL_CORE0 == Spi_DemoCoreExeFlag.ExeCmdCore)
        {
            DEBUG_PRINTF("\n  <1> : Start to SPI0 Sync transmit in Core0.");
            DEBUG_PRINTF("\n  <2> : Start to SPI0 Async transmit(%s) in Core0.",
                (Async_transmit_mode == SPI_INTERRUPT_MODE) ? ("Interrupt Mode") : ("Polling Mode"));
        }
        else
        {
            DEBUG_PRINTF("\n  <1> : Start to SPI2 Sync transmit in Core1.");
            DEBUG_PRINTF("\n  <2> : Start to SPI2 Async transmit(%s) in Core1.",
                (Async_transmit_mode == SPI_INTERRUPT_MODE) ? ("Interrupt Mode") : ("Polling Mode"));
        }
        DEBUG_PRINTF("\n  <3> : Switch Async transmit mode to %s. ",
            (Async_transmit_mode == SPI_INTERRUPT_MODE) ? ("Polling Mode") : ("Interrupt Mode"));
        DEBUG_PRINTF("\n  <4> : Cancel the currently transmitted Sequence.");
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        cmd = DEBUG_GETC();

        switch (cmd)
        {
            case '1':
            {
                Spi_DemoCoreExeFlag.ExeCmd = 1U;
                break;
            }
            case '2':
            {
                Spi_DemoCoreExeFlag.ExeCmd = 2U;
                break;
            }
            case '3':
            {
                Spi_DemoCoreExeFlag.ExeCmd = 3U;
                break;
            }
            case '4':
            {
                Spi_DemoCoreExeFlag.ExeCmd = 4U;
                break;
            }
            case 'x':
            case 'X':
            {
                Exit = 1;
                Spi_DemoCoreExeFlag.ExeCmdCore = MCAL_CORE0;
                Spi_DemoCoreExeFlag.ExeCmd = 0xFFU;
                Async_transmit_mode = SPI_POLLING_MODE;
                break;
            }
            default:
            {
                DEBUG_PRINTF("\n\n  INVALID OPTION");
                break;
            }
        }
        if (0xFFU != Spi_DemoCoreExeFlag.ExeCmd)
        {
            if (MCAL_CORE0 == Spi_DemoCoreExeFlag.ExeCmdCore)
            {
                /* Call Spi_Demo direct in Core 0 */
                Spi_Demo();
            }
            else
            {
                /* Waiting till Dio demo test finished */
                while(0xFFU != Spi_DemoCoreExeFlag.ExeCmd)
                {
                    /* Do Nothing */
                }
            }
        }
    }
}

/****************************************************************************************************
*   Function Name           : Spi_Demo()
*
*   Service ID              : None.
*
*   Description             : Spi demo execution function.
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
 void Spi_Demo(void)
{
    Std_ReturnType          RetStatus;
    Mcal_CoreType           CoreId;
    Spi_SeqResultType       SeqStatus;

    CoreId = Mcal_GetCoreId();


    if ((DEMO_STARTED == Spi_DemoCoreExeFlag.DemoStartupFlg) &&
        (0x00U == Spi_DemoCoreInitStatus[CoreId]))
    {
        /* Initialize the Spi */ 
        Spi_Init(&Spi_ConfigSet[0]);
        Spi_DemoCoreInitStatus[CoreId] = 1U;
    }

    if ((DEMO_STARTED == Spi_DemoCoreExeFlag.DemoStartupFlg) &&
        (0x01U == Spi_DemoCoreInitStatus[CoreId]) &&
        (0xFFU != Spi_DemoCoreExeFlag.ExeCmd))
    {
#if (SPI_ENABLE_DMA == STD_ON)
        if ((MCAL_CORE0 != CoreId) && (MCAL_CORE0 != Spi_DemoCoreExeFlag.ExeCmdCore))
        {
            /* Initialize the Dma in core0 */
            Dma_Init(&Dma_ConfigSet[0]);
        }
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
    }
    if ((Spi_DemoCoreExeFlag.ExeCmdCore == CoreId) && (0xFFU != Spi_DemoCoreExeFlag.ExeCmd))
    {
        DEBUG_PRINTF("\nCurrent operation core : Core%d", CoreId);
        switch (Spi_DemoCoreExeFlag.ExeCmd)
        {
            case 1U:
            {
                Spi_TransmitDemo(TRUE);
                break;
            }
            case 2U:
            {
                Spi_TransmitDemo(FALSE);
                break;
            }
            case 3U:
            {
                if (SPI_INTERRUPT_MODE == Async_transmit_mode)
                {
                    Async_transmit_mode = SPI_POLLING_MODE;
                    RetStatus = Spi_SetAsyncMode(SPI_POLLING_MODE);
                }
                else
                {
                    Async_transmit_mode = SPI_INTERRUPT_MODE;
                    RetStatus = Spi_SetAsyncMode(SPI_INTERRUPT_MODE);
                }

                if (E_OK == RetStatus)
                {
                    DEBUG_PRINTF("\nSet Mode Success");
                    DEBUG_PRINTF("\nSwitch mode to %s",
                            (SPI_INTERRUPT_MODE == Async_transmit_mode) ? ("Interrupt Mode") : ("Polling Mode"));
                }
                else
                {
                    DEBUG_PRINTF("\nError: Set Mode Failed!!");
                }
                break;
            }
            case 4U:
            {
                if (MCAL_CORE0 == Spi_DemoCoreExeFlag.ExeCmdCore)
                {
                    Spi_Cancel(SpiConf_SpiSequence_SpiSequence_0);
                    SeqStatus = Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_0);
                }
                else
                {
                    Spi_Cancel(SpiConf_SpiSequence_SpiSequence_1);
                    SeqStatus = Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_1);
                }
                if(SPI_SEQ_CANCELLED == SeqStatus)
                {
                    DEBUG_PRINTF("\nCancel transmit Sequence Success");
                }
                else
                {
                    DEBUG_PRINTF("\nCancel transmit Sequence Failed");
                }
                break;
            }
            default:
            {
                /* Do Nothing */
                break;
            }
        }

        if ((DEMO_STARTED == Spi_DemoCoreExeFlag.DemoStartupFlg) &&
            (0x01U == Spi_DemoCoreInitStatus[CoreId]) &&
            (0xFFU != Spi_DemoCoreExeFlag.ExeCmd))
        {
            Spi_DemoCoreExeFlag.ExeCmd = 0xFFU;
    #if (SPI_ENABLE_DMA == STD_ON)
            if ((MCAL_CORE0 != CoreId) && (MCAL_CORE0 != Spi_DemoCoreExeFlag.ExeCmdCore))
            {
                Dma_DeInit();
            }
    #endif /* (SPI_ENABLE_DMA  \== STD_ON) */
        }

        if ((DEMO_IDLE == Spi_DemoCoreExeFlag.DemoStartupFlg) &&
            (0x01U == Spi_DemoCoreInitStatus[CoreId]))
        {
            /* De-Initialize the Spi */
            (void)Spi_DeInit();
            Spi_DemoCoreInitStatus[CoreId] = 0x00U;
        }
    }
}

/****************************************************************************************************
*   Function Name           : Spi_JobNotificationTestx
*
*   Service ID              : None.
*
*   Description             : Job Notification function
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
void Spi_JobNotificationTest0(void)
{
    Job_transmit_flg |= 0x01U;
    if (SPI_JOB_OK == Spi_GetJobResult(SpiConf_SpiJob_SpiJob_0))
    {
        DEBUG_PRINTF("\nJob0 transmit success.");
    }
    else
    {
        DEBUG_PRINTF("\nJob0 transmit failed.");
    }
}

void Spi_JobNotificationTest1(void)
{
    Job_transmit_flg |= 0x02U;
    if (SPI_JOB_OK == Spi_GetJobResult(SpiConf_SpiJob_SpiJob_1))
    {
        DEBUG_PRINTF("\nJob1 transmit success.");
    }
    else
    {
        DEBUG_PRINTF("\nJob1 transmit failed.");
    }
}
/****************************************************************************************************
*   Function Name           : Spi_SeqNotificationTestx
*
*   Service ID              : None.
*
*   Description             : Sequence Notification function
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
void Spi_SeqNotificationTest0(void)
{
    Seq_transmit_flg |= 0x01U;
    if (SPI_SEQ_OK == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_0))
    {
        DEBUG_PRINTF("\nSequence0 transmit success.");
    }
    else
    {
        DEBUG_PRINTF("\nSequence0 transmit failed.");
    }
}

void Spi_SeqNotificationTest1(void)
{
    Seq_transmit_flg |= 0x02U;
    if (SPI_SEQ_OK == Spi_GetSequenceResult(SpiConf_SpiSequence_SpiSequence_1))
    {
        DEBUG_PRINTF("\nSequence1 transmit success.");
    }
    else
    {
        DEBUG_PRINTF("\nSequence1 transmit failed.");
    }
}
/****************************************************************************************************
*   Function Name           : Spi_BufferCompx
*
*   Service ID              : None.
*
*   Description             : Spi data buffer comparison function
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
static Std_ReturnType Spi_BufferComp8(uint8* srcBufferPtr, uint8* desBufferPtr, uint8 dataLength)
{
    Std_ReturnType RetValue;
    uint8 Count;
    RetValue = E_OK;
    if(0U == dataLength)
    {
        DEBUG_PRINTF("the dataLength is 0!\n");
        RetValue = E_NOT_OK;
    }else if(NULL_PTR == srcBufferPtr){
        DEBUG_PRINTF("the SrcBuffer is null!\n");
        RetValue = E_NOT_OK;
    }else if(NULL_PTR == desBufferPtr){
        DEBUG_PRINTF("the DesBuffer is null!\n");
        RetValue = E_NOT_OK;
    }else{
        for(Count=0; Count<dataLength; Count++)
        {
            if(srcBufferPtr[Count] != desBufferPtr[Count])
            {
                RetValue = E_NOT_OK;
                break;
            }
        }

    }
    return RetValue;
}

static Std_ReturnType Spi_BufferComp16(uint16* srcBufferPtr, uint16* desBufferPtr, uint8 dataLength)
{
    Std_ReturnType RetValue;
    uint8 Count;
    RetValue = E_OK;
    if(0U == dataLength)
    {
        DEBUG_PRINTF("the dataLength is 0!\n");
        RetValue = E_NOT_OK;
    }else if(NULL_PTR == srcBufferPtr){
        DEBUG_PRINTF("the SrcBuffer is null!\n");
        RetValue = E_NOT_OK;
    }else if(NULL_PTR == desBufferPtr){
        DEBUG_PRINTF("the DesBuffer is null!\n");
        RetValue = E_NOT_OK;
    }else{
        for(Count=0; Count<dataLength; Count++)
        {
            if(srcBufferPtr[Count] != desBufferPtr[Count])
            {
                RetValue = E_NOT_OK;
                break;
            }
        }

    }
    return RetValue;
}
static Std_ReturnType Spi_BufferComp32(uint32* srcBufferPtr, uint32* desBufferPtr, uint8 dataLength)
{
    Std_ReturnType RetValue;
    uint8 Count;
    RetValue = E_OK;
    if(0U == dataLength)
    {
        DEBUG_PRINTF("the dataLength is 0!\n");
        RetValue = E_NOT_OK;
    }else if(NULL_PTR == srcBufferPtr){
        DEBUG_PRINTF("the SrcBuffer is null!\n");
        RetValue = E_NOT_OK;
    }else if(NULL_PTR == desBufferPtr){
        DEBUG_PRINTF("the DesBuffer is null!\n");
        RetValue = E_NOT_OK;
    }else{
        for(Count=0; Count<dataLength; Count++)
        {
            if(srcBufferPtr[Count] != desBufferPtr[Count])
            {
                RetValue = E_NOT_OK;
                break;
            }
        }

    }
    return RetValue;
}

#define SPI_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Spi_MemMap.h"

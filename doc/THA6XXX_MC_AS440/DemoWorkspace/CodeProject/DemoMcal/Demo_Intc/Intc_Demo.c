/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Intc_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : INTC
*
*   brief                 : This file contains Demo application for Intc Driver
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
#include "Intc_Demo.h"
#include "Intc.h"
#include "Mcall.h"
#ifdef  __DEBUG_CHIP__
#include "Uart_Demo.h"
#endif
#include "Demo_Common.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define INTC_NO_TRIGGERED                   (0x00U)
#define INTC_SWI_TRIGGERED                  (0x01U)

#define INTC_DEMO_IDLE                      (0U)
#define INTC_DEMO_ENTER                     (1U)
#define INTC_DEMO_RUNNING                   (2U)
#define INTC_DEMO_EXIT                      (3U)

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define INTC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Intc_MemMap.h"

static uint8 Demo_IntSgiTriggCore[MCAL_NUMBER_OF_CORES] =
{
    0U
    ,0U
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
    ,0U
    ,0U
#endif /* #if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
};

static uint8 Demo_IntSpiTriggCore[MCAL_NUMBER_OF_CORES] =
{
    0U
    ,0U
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
    ,0U
    ,0U
#endif /* #if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
};

static Demo_CoreExeType Demo_IntcCoreExeFlag = {MCAL_CORE0, 0xFFU, DEMO_IDLE};

static uint8 Demo_IntcCmdTemp = 0U;

static uint8 Demo_Sgi_EnableFlag[MCAL_NUMBER_OF_CORES] =
{
    INTC_DEMO_IDLE,
    INTC_DEMO_IDLE,
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
    INTC_DEMO_IDLE,
    INTC_DEMO_IDLE
#endif /* #if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
};

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
static uint8 Demo_Cluster1SpiEnableFlag = INTC_DEMO_IDLE;
#endif /* #if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */

#define INTC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Intc_MemMap.h"



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
#define INTC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Intc_MemMap.h"

static void Demo_IntcWaitingFeedback(void);
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : Demo_IntcWaitingFeedback
*
*   Service ID              : None.
*
*   Description             : Judge whether test successfully.
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
static void Demo_IntcWaitingFeedback(void)
{
    boolean TestResultFlag = TRUE;
    /* Waiting for 10ms to ensure all cores triggered */
    Timer_DelayMs(10);

    if (Demo_IntcCmdTemp <= 5)
    {
        if ((INTC_NO_TRIGGERED == Demo_IntSgiTriggCore[MCAL_CORE0]) &&
            (INTC_NO_TRIGGERED == Demo_IntSgiTriggCore[MCAL_CORE1]))
        {
            TestResultFlag = FALSE;
            DEBUG_PRINTF("\nNeither Core0 nor Core1 triggered SGI0.");
        }
        else
        {
            if (INTC_SWI_TRIGGERED == Demo_IntSgiTriggCore[MCAL_CORE0])
            {
                DEBUG_PRINTF("\nInterrupt source SGI0 Triggered in core0");
            }

            if (INTC_SWI_TRIGGERED == Demo_IntSgiTriggCore[MCAL_CORE1])
            {
                DEBUG_PRINTF("\nInterrupt source SGI0 Triggered in core1");
            }
        }

        Demo_IntSgiTriggCore[MCAL_CORE0] = INTC_NO_TRIGGERED;
        Demo_IntSgiTriggCore[MCAL_CORE1] = INTC_NO_TRIGGERED;
    }
    else if (Demo_IntcCmdTemp <= 7)
    {
        if (INTC_SWI_TRIGGERED == Demo_IntSpiTriggCore[MCAL_CORE0])
        {
            DEBUG_PRINTF("\nInterrupt source SPI56 Triggered in core0");
            Demo_IntSpiTriggCore[MCAL_CORE0] = INTC_NO_TRIGGERED;
        }
        else if (INTC_SWI_TRIGGERED == Demo_IntSpiTriggCore[MCAL_CORE1])
        {
            DEBUG_PRINTF("\nInterrupt source SPI56 Triggered in core1");
            Demo_IntSpiTriggCore[MCAL_CORE1] = INTC_NO_TRIGGERED;
        }
        else
        {
            TestResultFlag = FALSE;
        }
    }
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
    else if ((Demo_IntcCmdTemp <= 9) || ((Demo_IntcCmdTemp >= 'a') && (Demo_IntcCmdTemp <= 'c')))
    {
        if ((INTC_NO_TRIGGERED == Demo_IntSgiTriggCore[MCAL_CORE2]) &&
            (INTC_NO_TRIGGERED == Demo_IntSgiTriggCore[MCAL_CORE3]))
        {
            TestResultFlag = FALSE;
            DEBUG_PRINTF("\nNeither Core0 nor Core3 triggered SGI2.");
        }
        else
        {
            if (INTC_SWI_TRIGGERED == Demo_IntSgiTriggCore[0])
            {
                DEBUG_PRINTF("\nInterrupt source SGI0 Triggered in core2");
            }
            if (INTC_SWI_TRIGGERED == Demo_IntSgiTriggCore[1])
            {
                DEBUG_PRINTF("\nInterrupt source SGI0 Triggered in core3");
            }
        }

        Demo_IntSgiTriggCore[MCAL_CORE2] = INTC_NO_TRIGGERED;
        Demo_IntSgiTriggCore[MCAL_CORE3] = INTC_NO_TRIGGERED;
    }
    else if ((Demo_IntcCmdTemp >= 'd') && (Demo_IntcCmdTemp <= 'g'))
    {
        if (INTC_SWI_TRIGGERED == Demo_IntSpiTriggCore[MCAL_CORE2])
        {
            DEBUG_PRINTF("\nInterrupt source SPI56 Triggered in core2");
            Demo_IntSpiTriggCore[MCAL_CORE2] = INTC_NO_TRIGGERED;
        }
        else if (INTC_SWI_TRIGGERED == Demo_IntSpiTriggCore[MCAL_CORE3])
        {
            DEBUG_PRINTF("\nInterrupt source SPI56 Triggered in core3");
            Demo_IntSpiTriggCore[MCAL_CORE3] = INTC_NO_TRIGGERED;
        }
        else
        {
            TestResultFlag = FALSE;
        }
    }
#endif /* (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
    else
    {
        TestResultFlag = FALSE;
    }

    if (FALSE == TestResultFlag)
    {
        DEBUG_PRINTF("\nTestResult = Fail\n");
    }
    else
    {
        DEBUG_PRINTF("\nTestResult = Pass\n");
    }
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Intc_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Demo test entry for Intc, can only be called by master core.
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
void Intc_DemoEntry(void)
{
    char  Cmd;
    uint8 ExitFlag;
    Std_VersionInfoType Intc_ver;

    /* Enable the interrupt first */
    Demo_Sgi_EnableFlag[1] = INTC_DEMO_ENTER; /* Set for enable interrupt in core1 */
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
    Demo_Sgi_EnableFlag[2] = INTC_DEMO_ENTER; /* Set for enable interrupt in core2 */
    Demo_Sgi_EnableFlag[3] = INTC_DEMO_ENTER; /* Set for enable interrupt in core3 */
    Demo_Cluster1SpiEnableFlag = INTC_DEMO_ENTER; /* Set for enable SPI interrupt in core2 */
#endif /* (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */

    Intc_EnableInterrupt(INTC_INTSRC_NUM_56);
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA610X_LFBGA180)
    Intc_EnableInterrupt(INTC_INTSRC_NUM_89);
#endif /* (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA610X_LFBGA180) */
    Intc_EnableInterrupt(INTC_INTSRC_NUM_0);

    ExitFlag = 0U;
    while (0U == ExitFlag)
    {
        Intc_GetVersionInfo(&Intc_ver);
        DEBUG_PRINTF("\n\n");
        DEBUG_PRINTF("\n/*********************************************************/");
        DEBUG_PRINTF("\n           INTC DRIVER DEMO MENU V%02d.%02d.%02d            ",
                Intc_ver.sw_major_version, Intc_ver.sw_minor_version, Intc_ver.sw_patch_version);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Core0 Generate SGI0 interrupt for core0. ");
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA610X_LFBGA180)
        /* For THA6206 and THA6412 */
        DEBUG_PRINTF("\n  <2> : Core0 Generate SGI0 interrupt for Core0 and Core1.");
        DEBUG_PRINTF("\n  <3> : Core0 Generate SGI0 interrupt for core1.");
        DEBUG_PRINTF("\n  <4> : Core1 Generate SGI0 interrupt for core0.");
        DEBUG_PRINTF("\n  <5> : Core1 Generate SGI0 interrupt for core1.");
        DEBUG_PRINTF("\n  <6> : Core0 Generate SPI interrupt INTID89 for core1.");
        DEBUG_PRINTF("\n  <7> : Core1 Generate SPI interrupt INTID56 for core0.");
#endif /* (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA610X_LFBGA180) */
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
        /* For THA6412 only */
        /* DEBUG_PRINTF("\n  <8> : Core2 Generate SGI0 interrupt for Core2 and Core3."); */
        /* DEBUG_PRINTF("\n  <9> : Core2 Generate SGI0 interrupt for core2. "); */
        /* DEBUG_PRINTF("\n  <a> : Core2 Generate SGI0 interrupt for core3."); */
        /* DEBUG_PRINTF("\n  <b> : Core3 Generate SGI0 interrupt for core2."); */
        /* DEBUG_PRINTF("\n  <c> : Core3 Generate SGI0 interrupt for core3."); */
        /* DEBUG_PRINTF("\n  <d> : Core2 Generate SPI interrupt INTID89 for core3."); */
        /* DEBUG_PRINTF("\n  <e> : Core3 Generate SPI interrupt INTID56 for core2."); */
        /* DEBUG_PRINTF("\n  <f> : Core0 Generate SPI interrupt INTID56 for core2."); */
        /* DEBUG_PRINTF("\n  <g> : Core3 Generate SPI interrupt INTID89 for core1."); */
#endif /* (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Cmd = DEBUG_GETC();
        switch (Cmd)
        {
            case '1':
            case '2':
            case '3':
            case '6':
            {
                Demo_IntcCoreExeFlag.ExeCmdCore = MCAL_CORE0;
                Demo_IntcCoreExeFlag.ExeCmdId = Cmd - '0';
                break;
            }
            case '4':
            case '5':
            case '7':
            {
                Demo_IntcCoreExeFlag.ExeCmdCore = MCAL_CORE1;
                Demo_IntcCoreExeFlag.ExeCmdId = Cmd - '0';
                break;
            }
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
            /* Demo for THA6412, four core */
            case '8':
            case '9':
            {
                Demo_IntcCoreExeFlag.ExeCmdCore = MCAL_CORE2;
                Demo_IntcCoreExeFlag.ExeCmdId = Cmd - '0';
                break;
            }
            case 'a':
            case 'd':
            {
                Demo_IntcCoreExeFlag.ExeCmdCore = MCAL_CORE2;
                Demo_IntcCoreExeFlag.ExeCmdId = (uint8)(DEMO_UPPER_TO_LOWER(Cmd) - 'a') + 10U;
                break;
            }
            case 'b':
            case 'c':
            case 'e':
            {
                Demo_IntcCoreExeFlag.ExeCmdCore = MCAL_CORE3;
                Demo_IntcCoreExeFlag.ExeCmdId = (uint8)(DEMO_UPPER_TO_LOWER(Cmd) - 'a') + 10U;
                break;
            }
            case 'f':
            {
                Demo_IntcCoreExeFlag.ExeCmdCore = MCAL_CORE0;
                Demo_IntcCoreExeFlag.ExeCmdId = (uint8)(DEMO_UPPER_TO_LOWER(Cmd) - 'a') + 10U;
                break;
            }
            case 'g':
            {
                Demo_IntcCoreExeFlag.ExeCmdCore = MCAL_CORE3;
                Demo_IntcCoreExeFlag.ExeCmdId = (uint8)(DEMO_UPPER_TO_LOWER(Cmd) - 'a') + 10U;
                break;
            }
#endif /* (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
            case 'x':
            case 'X':
            {
                Intc_DisableInterrupt(INTC_INTSRC_NUM_56);
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA610X_LFBGA180)
                Intc_DisableInterrupt(INTC_INTSRC_NUM_89);
#endif /* (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA610X_LFBGA180) */
                Intc_DisableInterrupt(INTC_INTSRC_CPU0_SGI0_CORE0);
                Demo_Sgi_EnableFlag[1] = INTC_DEMO_EXIT;
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
                Demo_Sgi_EnableFlag[2] = INTC_DEMO_EXIT;
                Demo_Sgi_EnableFlag[3] = INTC_DEMO_EXIT;
                Demo_Cluster1SpiEnableFlag = INTC_DEMO_EXIT;
#endif /* (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
                ExitFlag = 1U;
                break;
            }
            default:
            {
                DEBUG_PRINTF("\n\n  INVALID OPTION");
                break;
            }
        }

        Demo_IntcCmdTemp = Demo_IntcCoreExeFlag.ExeCmdId;

        if (0xFFU != Demo_IntcCoreExeFlag.ExeCmdId)
        {
            if (MCAL_CORE0 == Demo_IntcCoreExeFlag.ExeCmdCore)
            {
                Intc_Demo();
            }

            while(0xFFU != Demo_IntcCoreExeFlag.ExeCmdId)
            {
                /* Waiting till Intc demo test finished */
            }

            /* Waiting notification called */
            Demo_IntcWaitingFeedback();
        }
    }
}

/****************************************************************************************************
*   Function Name           : Intc_Demo
*
*   Service ID              : None.
*
*   Description             : Demo test for Intc
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
void Intc_Demo(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    if (MCAL_CORE0 != CoreId)
    {
        if (INTC_DEMO_ENTER == Demo_Sgi_EnableFlag[CoreId])
        {
            Demo_Sgi_EnableFlag[CoreId] = INTC_DEMO_RUNNING;
            /* Prioritize enabling interrupts that need to be tested */
            Intc_EnableInterrupt(INTC_INTSRC_NUM_0);
        }
        else if (INTC_DEMO_EXIT == Demo_Sgi_EnableFlag[CoreId])
        {
            Intc_DisableInterrupt(INTC_INTSRC_NUM_0);
            Demo_Sgi_EnableFlag[CoreId] = INTC_DEMO_IDLE;
        }
        else
        {
            /* Do Nothing */
        }

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
        if (MCAL_CORE2 == CoreId)
        {
            if (INTC_DEMO_ENTER == Demo_Cluster1SpiEnableFlag)
            {
                Demo_Cluster1SpiEnableFlag = INTC_DEMO_RUNNING;
                /* Enable the interrupt in GIC1 */
                Intc_EnableInterrupt(INTC_INTSRC_NUM_56);
                Intc_EnableInterrupt(INTC_INTSRC_NUM_89);
            }
            else if (INTC_DEMO_EXIT == Demo_Cluster1SpiEnableFlag)
            {
                /* Disable the interrupt in GIC1 */
                Intc_DisableInterrupt(INTC_INTSRC_NUM_56);
                Intc_DisableInterrupt(INTC_INTSRC_NUM_89);
                Demo_Cluster1SpiEnableFlag = INTC_DEMO_IDLE;
            }
            else
            {
                /* Do Nothing */
            }
        }
#endif /* (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
    }


    if ((Demo_IntcCoreExeFlag.ExeCmdCore == CoreId) && (0xFFU != Demo_IntcCoreExeFlag.ExeCmdId))
    {
        switch (Demo_IntcCoreExeFlag.ExeCmdId)
        {
            case 1U:
            {
                DEBUG_PRINTF("\nCore0 Generate software interrupt SGI0 to core0\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE0);
                break;
            }
            case 2U:
            {
                DEBUG_PRINTF("\nCore0 Generate software interrupt SGI0 to core0 and core1\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE0_CORE1);
                break;
            }
            case 3U:
            {
                DEBUG_PRINTF("\nCore0 Generate software interrupt SGI0 to core1\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE1);
                break;
            }
            case 4U:
            {
                DEBUG_PRINTF("\nCore1 Generate software interrupt SGI0 to core0\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE0);
                break;
            }
            case 5U:
            {
                DEBUG_PRINTF("\nCore1 Generate software interrupt SGI0 to core1\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE1);
                break;
            }
#if (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA610X_LFBGA180)
            case 6U:
            {
                DEBUG_PRINTF("\nCore0 Generate software interrupt SPI89 to core1\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_89, INTC_TARGET_CORE1);
                break;
            }
#endif /* (MCAL_PROCESSOR_CAT != MCAL_PROCESSOR_THA610X_LFBGA180) */
            case 7U:
            {
                DEBUG_PRINTF("\nCore1 Generate software interrupt SPI56 to core0\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_56, INTC_TARGET_CORE0);
                break;
            }
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
            /* Demo for THA6412, four core */
            case 8U:
            {
                DEBUG_PRINTF("\nCore2 Generate software interrupt SGI0 to core2 and core3\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE2_CORE3);
                break;
            }
            case 9U:
            {
                DEBUG_PRINTF("\nCore2 Generate software interrupt SGI0 to core2\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE2);
                break;
            }
            case 10U:
            {
                DEBUG_PRINTF("\nCore2 Generate software interrupt SGI0 to core3\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE3);
                break;
            }
            case 11U:
            {
                DEBUG_PRINTF("\nCore3 Generate software interrupt SGI0 to core2\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE2);
                break;
            }
            case 12U:
            {
                DEBUG_PRINTF("\nCore3 Generate software interrupt SGI0 to core3\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_0, INTC_TARGET_CORE3);
                break;
            }
            case 13U:
            {
                DEBUG_PRINTF("\nCore2 Generate software interrupt SPI89 to core3\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_89, INTC_TARGET_CORE3);
                break;
            }
            case 14U:
            {
                DEBUG_PRINTF("\nCore3 Generate software interrupt SPI56 to core2\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_56, INTC_TARGET_CORE2);
                break;
            }
            case 15U:
            {
                DEBUG_PRINTF("\nCore0 Generate software interrupt SPI56 to core2\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_56, INTC_TARGET_CORE2);
                break;
            }
            case 16U:
            {
                DEBUG_PRINTF("\nCore3 Generate software interrupt SPI89 to core1\n");
                Intc_GenSwInterrupt(INTC_INTSRC_NUM_89, INTC_TARGET_CORE1);
                break;
            }
#endif /* (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */
            default:
            {
                /* Do Nothing */
                break;
            }
        }

        if (0xFFU > Demo_IntcCoreExeFlag.ExeCmdId)
        {
            Demo_IntcCoreExeFlag.ExeCmdId = 0xFFU;
            /* Set operated core to 0xFF for avoid core conflict */
            Demo_IntcCoreExeFlag.ExeCmdCore = MCAL_CORE0;
        }
    }
}

/****************************************************************************************************
*   Function Name           : Demo_Core<X>Sgi0Notification(<X>: core ID)
*
*   Service ID              : None.
*
*   Description             : Notification function for SGI interrupt
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
/* Write a service Intc_SW01_ISR_Handler to Intc_SW01_ISR_Callback() in Intc_Callout.c */
/* This is only demo to show how to use the software interrupt sources */
void Demo_Core0Sgi0Notification(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    Demo_IntSgiTriggCore[CoreId] = INTC_SWI_TRIGGERED;
}

void Demo_Core1Sgi0Notification(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    Demo_IntSgiTriggCore[CoreId] = INTC_SWI_TRIGGERED;
}

void Demo_Core0Spi56Notification(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    Demo_IntSpiTriggCore[CoreId] = INTC_SWI_TRIGGERED;
}

void Demo_Core1Spi89Notification(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    Demo_IntSpiTriggCore[CoreId] = INTC_SWI_TRIGGERED;
}

#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)

void Demo_Core2Sgi0Notification(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    Demo_IntSgiTriggCore[CoreId] = INTC_SWI_TRIGGERED;
}

void Demo_Core3Sgi0Notification(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    Demo_IntSgiTriggCore[CoreId] = INTC_SWI_TRIGGERED;
}

void Demo_Core2Spi56Notification(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    Demo_IntSpiTriggCore[CoreId] = INTC_SWI_TRIGGERED;
}

void Demo_Core3Spi89Notification(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    Demo_IntSpiTriggCore[CoreId] = INTC_SWI_TRIGGERED;
}
#endif /* (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516) */

#define INTC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Intc_MemMap.h"

/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Gpt_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM TOM
*
*   brief                 : This file contains Demo application for Gpt Driver
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
#include "Gpt_Demo.h"
#include "ComStack_Types.h"
#include "Gpt_GeneralTypes.h"
#include "Gpt.h"
#include "Gpt_Irq.h"
#include "Intc.h"
#include "Dio.h"
#include "Demo_Common.h"
#include "Gpt_Version.h"


/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define GPT_DEMO_TARGET_TIME                        (65000U)

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define GPT_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Gpt_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
static volatile uint32 GptChannel00_NotificationNumber;
static volatile uint32 GptChannel01_NotificationNumber;
static volatile uint32 GptChannel02_NotificationNumber;
static volatile uint32 GptChannel03_NotificationNumber;
static volatile uint32 GptChannel05_NotificationNumber;
static volatile uint32 GptChannel06_NotificationNumber;
static volatile uint32 GptChannel07_NotificationNumber;
static volatile uint32 GptChannel08_NotificationNumber;
static uint8 Gpt_DemoCoreSelFlg;
static CoreExeType GptCoreExeFlag;
static uint8 Gpt_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES];

#define GPT_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Gpt_MemMap.h"


/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/
#define GPT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Gpt_MemMap.h"

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
void Gpt_Notification_0(void)
{
  /* Notification for channel */
  GptChannel00_NotificationNumber++;

  /* 0.10 */
  if(0 == GptChannel00_NotificationNumber%2)
  {
      Dio_WriteChannel(DioConf_DioChannel_GPT_TEST,STD_LOW);
  }
  else
  {
      Dio_WriteChannel(DioConf_DioChannel_GPT_TEST,STD_HIGH);
  }
}

void Gpt_Notification_1(void)
{
  /* Notification for channel */
  GptChannel01_NotificationNumber++;
}

void Gpt_Notification_2(void)
{
  /* Notification for channel */
  GptChannel02_NotificationNumber++;
}

void Gpt_Notification_3(void)
{
  /* Notification for channel */
  GptChannel03_NotificationNumber++;
}

void Gpt_Notification_5(void)
{
  /* Notification for channel */
  GptChannel05_NotificationNumber++;
}

void Gpt_Notification_6(void)
{
  /* Notification for channel */
  GptChannel06_NotificationNumber++;
}

void Gpt_Notification_7(void)
{
  /* Notification for channel */
  GptChannel07_NotificationNumber++;
}

void Gpt_Notification_8(void)
{
  /* Notification for channel */
  GptChannel08_NotificationNumber++;
}
void Gpt_Notification_9(void)
{
    DEBUG_PRINTF("Gpt_Notification_invoked\n");

}

/****************************************************************************************************
 *   Function Name           : Gpt_ContinuousCountDemo0
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo for continuous timer based on GTM-TOM
 *                             of Gpt driver.
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
 *   Preconditions           : Gpt_Driver must be initialized.
 *
 ****************************************************************************************************/
static void Gpt_ContinuousCountDemo0(void)
{
  Mcal_CoreType CoreId;
  uint32 Channel;
  uint32 Status;
  uint32 TimeElapsed;
  uint32 TimeRemaining;
  uint32 Times;
  
  Status = 0U;
  CoreId = Mcal_GetCoreId ();

  if(MCAL_CORE0 == CoreId)
  {
    Channel = 0U;
    GptChannel00_NotificationNumber = 0U;
  }
  else
  {
    Channel = 2U;
    GptChannel02_NotificationNumber = 0U;
  }

  DEBUG_PRINTF("\r\n-----------------------------------\r\n");
  DEBUG_PRINTF("Demo1: Start continuous time(Case0)\n");

  /* Enable notification of channel */
  Gpt_EnableNotification(Channel);

  Gpt_StartTimer(Channel, GPT_DEMO_TARGET_TIME);
  DEBUG_PRINTF("\r\n Get 5 times counter value of channel:\r\n");
  /* Check whether timer works correctly */
  for(Times = 0U; Times < 5U; Times++)
  {
    TimeElapsed = 0U;
    TimeRemaining = 0U;
    /* Get channel elapsed counter */
    TimeElapsed = Gpt_GetTimeElapsed(Channel);
    /* Get channel elapsed counter */
    TimeRemaining = Gpt_GetTimeRemaining(Channel);

    if(!((TimeElapsed != 0U) && (TimeElapsed < GPT_DEMO_TARGET_TIME)))
    {
      Status++;
    }

    if(!((TimeRemaining != 0U) && (TimeRemaining < GPT_DEMO_TARGET_TIME)))
    {
      Status++;
    }
    DEBUG_PRINTF("No.%d elapsed value   is: %d\r\n", Times, TimeElapsed);
    DEBUG_PRINTF("No.%d remaining value is: %d\r\n", Times, TimeRemaining);
    DEBUG_PRINTF("No.%d the sum value   is: %d\r\n\r\n", Times, (TimeElapsed+TimeRemaining));
  }
  /* Channel period is 65ms, the notification must
    * be called more than 5 times after this delay */
  Timer_DelayMs(70U);

  if((MCAL_CORE0 == CoreId) && (GptChannel00_NotificationNumber == 0U))
  {
    Status++;
  }
  else if((MCAL_CORE1 == CoreId) && (GptChannel02_NotificationNumber == 0U))
  {
    Status++;
  }
  else
  {
    /* Do nothing */
  }
  
  if(0U == Status)
  {
    DEBUG_PRINTF("Result = Demo1(Case0) Passed;\r\n");
  }
  else
  {
    DEBUG_PRINTF("Result = Demo1(Case0) Failed;\r\n");
  }
  /* Disable channel notification */
  Gpt_DisableNotification(Channel);
  /* Stop channel */
  Gpt_StopTimer(Channel);
}

/****************************************************************************************************
 *   Function Name           : Gpt_ContinuousCountDemo1
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo for continuous timer based on base timer
 *                             of Gpt driver.
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
 *   Preconditions           : Gpt_Driver must be initialized.
 *
 ****************************************************************************************************/
#ifndef THA6_THA6104
 static void Gpt_ContinuousCountDemo1(void)
{
  Mcal_CoreType CoreId;
  uint32 Channel;
  uint32 Status;
  uint32 TimeElapsed;
  uint32 TimeRemaining;
  uint32 Times;
  
  Status = 0U;
  CoreId = Mcal_GetCoreId ();

  if(MCAL_CORE0 == CoreId)
  {
    Channel = GptConf_GptChannelConfiguration_GptChannelConfiguration_7;
    GptChannel05_NotificationNumber = 0U;
  }
  else
  {
    Channel = GptConf_GptChannelConfiguration_GptChannelConfiguration_8;
    GptChannel06_NotificationNumber = 0U;
  }
  DEBUG_PRINTF("\r\n-----------------------------------\r\n");
  DEBUG_PRINTF("Demo1: Start continuous time(Case1)\n");

  /* Enable notification of channel */
  Gpt_EnableNotification(Channel);

  Gpt_StartTimer(Channel, GPT_DEMO_TARGET_TIME);
  DEBUG_PRINTF("\r\n Get 5 times counter value of channel:\r\n");
  /* Check whether timer works correctly */
  for(Times = 0U; Times < 5U; Times++)
  {
    TimeElapsed = 0U;
    TimeRemaining = 0U;
    /* Get channel elapsed counter */
    TimeElapsed = Gpt_GetTimeElapsed(Channel);
    /* Get channel elapsed counter */
    TimeRemaining = Gpt_GetTimeRemaining(Channel);

    if(!((TimeElapsed != 0U) && (TimeElapsed < GPT_DEMO_TARGET_TIME)))
    {
      Status++;
    }

    if(!((TimeRemaining != 0U) && (TimeRemaining < GPT_DEMO_TARGET_TIME)))
    {
      Status++;
    }
    DEBUG_PRINTF("No.%d elapsed value   is: %d\r\n", Times, TimeElapsed);
    DEBUG_PRINTF("No.%d remaining value is: %d\r\n", Times, TimeRemaining);
    DEBUG_PRINTF("No.%d the sum value   is: %d\r\n\r\n", Times, (TimeElapsed+TimeRemaining));
  }
  /* Channel period is 65ms, the notification must
    * be called more than 5 times after this delay */
  Timer_DelayMs(70U);

  if((MCAL_CORE0 == CoreId) && (GptChannel05_NotificationNumber == 0U))
  {
    Status++;
  }
  else if((MCAL_CORE1 == CoreId) && (GptChannel06_NotificationNumber == 0U))
  {
    Status++;
  }
  else
  {
    /* Do nothing */
  }

  if(0U == Status)
  {
    DEBUG_PRINTF("Result = Demo1(Case1) Passed;\r\n");
  }
  else
  {
    DEBUG_PRINTF("Result = Demo1(Case1) Failed;\r\n");
  }
  /* Disable channel notification */
  Gpt_DisableNotification(Channel);
  /* Stop channel */
  Gpt_StopTimer(Channel);
}
#endif
/****************************************************************************************************
 *   Function Name           : Gpt_OneshotCountDemo0
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo for oneshot timer based on GTM-TOM
 *                             of Gpt driver.
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
 *   Preconditions           : Gpt_Driver must be initialized.
 *
 ****************************************************************************************************/
static void Gpt_OneshotCountDemo0(void)
{
  Mcal_CoreType CoreId;
  uint32 Channel;
  uint32 Status;
  uint32 TimeRemaining;
  uint32 TimeElapsed;

  Status = 0U;
  CoreId = Mcal_GetCoreId ();

  if(MCAL_CORE0 == CoreId)
  {
    Channel = 1U;
  }
  else
  {
    Channel = 3U;
  }
  DEBUG_PRINTF("\r\n-----------------------------------\r\n");
  DEBUG_PRINTF("Demo2: Start one-shot timer(Case0)\n");

  GptChannel01_NotificationNumber = 0U;
  GptChannel03_NotificationNumber = 0U;

  /* Enable notification of channel */
  Gpt_EnableNotification(Channel);

  Gpt_StartTimer(Channel, GPT_DEMO_TARGET_TIME);
  /* Check whether timer works correctly */
  TimeElapsed = 0U;
  TimeRemaining = 0U;
  /* Get channel elapsed counter */
  TimeElapsed = Gpt_GetTimeElapsed(Channel);
  /* Get channel elapsed counter */
  TimeRemaining = Gpt_GetTimeRemaining(Channel);

  if(!((TimeElapsed != 0U) && (TimeElapsed < GPT_DEMO_TARGET_TIME)))
  {
    Status++;
  }

  if(!((TimeRemaining != 0U) && (TimeRemaining < GPT_DEMO_TARGET_TIME)))
  {
    Status++;
  }
  DEBUG_PRINTF("Elapsed value   is: %d\r\n", TimeElapsed);
  DEBUG_PRINTF("Remaining value is: %d\r\n", TimeRemaining);
  DEBUG_PRINTF("The sum value   is: %d\r\n\r\n", (TimeElapsed+TimeRemaining));

  /* Channel period is 65ms, the target time must be reached after this delay */
  Timer_DelayMs(70U);

  if((MCAL_CORE0 == CoreId) && (GptChannel01_NotificationNumber == 0U))
  {
    Status++;
  }
  else if((MCAL_CORE1 == CoreId) && (GptChannel03_NotificationNumber == 0U))
  {
    Status++;
  }
  else
  {
    /* Do nothing */
  }

  /* The timer should remain unchanged */
  /* Get channel elapsed counter */
  TimeElapsed = Gpt_GetTimeElapsed(Channel);
  /* Get channel elapsed counter */
  TimeRemaining = Gpt_GetTimeRemaining(Channel);

  if(TimeElapsed != GPT_DEMO_TARGET_TIME)
  {
    Status++;
  }

  if(TimeRemaining != 0U)
  {
    Status++;
  }

  if(0U == Status)
  {
    DEBUG_PRINTF("Result = Demo2(Case0) Passed;\r\n");
  }
  else
  {
    DEBUG_PRINTF("Result = Demo2(Case0) Failed;\r\n");
  }

  DEBUG_PRINTF("\r\n\r\n");
  /* Disable channel notification */
  Gpt_DisableNotification(Channel);
  /* Stop channel */
  Gpt_StopTimer(Channel);

}

/****************************************************************************************************
 *   Function Name           : Gpt_OneshotCountDemo1
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo for oneshot timer based on base timer
 *                             of Gpt driver.
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
 *   Preconditions           : Gpt_Driver must be initialized.
 *
 ****************************************************************************************************/
static void Gpt_OneshotCountDemo1(void)
{
  Mcal_CoreType CoreId;
  uint32 Channel;
  uint32 Status;
  uint32 TimeRemaining;
  uint32 TimeElapsed;

  Status = 0U;
  CoreId = Mcal_GetCoreId ();
  
  if(MCAL_CORE0 == CoreId)
  {
    Channel = GptConf_GptChannelConfiguration_GptChannelConfiguration_9;
    GptChannel07_NotificationNumber = 0U;
  }
  else
  {
    Channel = GptConf_GptChannelConfiguration_GptChannelConfiguration_10;
    GptChannel08_NotificationNumber = 0U;
  }
  DEBUG_PRINTF("\r\n-----------------------------------\r\n");
  DEBUG_PRINTF("Demo2: Start one-shot timer(Case1)\n");

  /* Enable notification of channel */
  Gpt_EnableNotification(Channel);

  Gpt_StartTimer(Channel, GPT_DEMO_TARGET_TIME);
  /* Check whether timer works correctly */
  TimeElapsed = 0U;
  TimeRemaining = 0U;
  /* Get channel elapsed counter */
  TimeElapsed = Gpt_GetTimeElapsed(Channel);
  /* Get channel elapsed counter */
  TimeRemaining = Gpt_GetTimeRemaining(Channel);

  if(!((TimeElapsed != 0U) && (TimeElapsed < GPT_DEMO_TARGET_TIME)))
  {
    Status++;
  }

  if(!((TimeRemaining != 0U) && (TimeRemaining < GPT_DEMO_TARGET_TIME)))
  {
    Status++;
  }
  DEBUG_PRINTF("Elapsed value   is: %d\r\n", TimeElapsed);
  DEBUG_PRINTF("Remaining value is: %d\r\n", TimeRemaining);
  DEBUG_PRINTF("The sum value   is: %d\r\n\r\n", (TimeElapsed+TimeRemaining));

  /* Channel period is 65ms, the target time must be reached after this delay */
  Timer_DelayMs(70U);

  if((MCAL_CORE0 == CoreId) && (GptChannel07_NotificationNumber == 0U))
  {
    Status++;
  }
  else if((MCAL_CORE1 == CoreId) && (GptChannel08_NotificationNumber == 0U))
  {
    Status++;
  }
  else
  {
    /* Do nothing */
  }

  /* The timer should remain unchanged */
  /* Get channel elapsed counter */
  TimeElapsed = Gpt_GetTimeElapsed(Channel);
  /* Get channel elapsed counter */
  TimeRemaining = Gpt_GetTimeRemaining(Channel);

  if(TimeElapsed != GPT_DEMO_TARGET_TIME)
  {
    Status++;
  }

  if(TimeRemaining != 0U)
  {
    Status++;
  }

  if(0U == Status)
  {
    DEBUG_PRINTF("Result = Demo2(Case1) Passed;\r\n");
  }
  else
  {
    DEBUG_PRINTF("Result = Demo2(Case1) Failed;\r\n");
  }
  DEBUG_PRINTF("\r\n\r\n");
  /* Disable channel notification */
  Gpt_DisableNotification(Channel);
  /* Stop channel */
  Gpt_StopTimer(Channel);

}

/****************************************************************************************************
 *   Function Name           : Gpt_DemoPredefTimer
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo for predef timer of Gpt driver.
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
 *   Preconditions           : Gpt_Driver must be initialized.
 *
 ****************************************************************************************************/
void Gpt_DemoPredefTimer(void)
{
  uint32 Status;

  DEBUG_PRINTF("\r\n-----------------------------------\r\n");
  DEBUG_PRINTF("Demo3: Get predefine timer value\r\n");

  uint32 PredefTimeValue[3];
  uint32 Times;

  PredefTimeValue[0] = 0U;
  PredefTimeValue[1] = 0U;
  PredefTimeValue[2] = 0U;
  Status = 0U;

  DEBUG_PRINTF("\r\n");
  for(Times = 0U; Times < 3U; Times++)
  {
    /* Get predefine timer value of 100Us class */
    Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_100US_32BIT,
                  &PredefTimeValue[Times]);
    Timer_DelayMs(1);
    DEBUG_PRINTF("No.%d 100us predefine timer value is: %d\r\n", Times, PredefTimeValue[Times]);
  }

  if(PredefTimeValue[0] == PredefTimeValue[1])
  {
      Status++;
  }
  else if(PredefTimeValue[0] == PredefTimeValue[2])
  {
      Status++;
  }
  else if(PredefTimeValue[1] == PredefTimeValue[2])
  {
      Status++;
  }
  else
  {
    /* Do nothing */
  }

  PredefTimeValue[0] = 0U;
  PredefTimeValue[1] = 0U;
  PredefTimeValue[2] = 0U;

  DEBUG_PRINTF("\r\n");
  for(Times = 0U; Times < 3U; Times++)
  {
    /* Get predefine timer value of 1Us class */
    Gpt_GetPredefTimerValue(GPT_PREDEF_TIMER_1US_32BIT,
                  &PredefTimeValue[Times]);
    Timer_DelayMs(1);
    DEBUG_PRINTF("No.%d 1us predefine timer value is: %d\r\n", Times, PredefTimeValue[Times]);
  }

  if(PredefTimeValue[0] == PredefTimeValue[1])
  {
      Status++;
  }
  else if(PredefTimeValue[0] == PredefTimeValue[2])
  {
      Status++;
  }
  else if(PredefTimeValue[1] == PredefTimeValue[2])
  {
      Status++;
  }
  else
  {
    /* Do nothing */
  }

  if(0U == Status)
  {
    DEBUG_PRINTF("Result = Demo3 Passed;\r\n");
  }
  else
  {
    DEBUG_PRINTF("Result = Demo3 Failed;\r\n");
  }
  DEBUG_PRINTF("\r\n\r\n");
}

/****************************************************************************************************
 *   Function Name           : Gpt_Demo
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo API for Gpt driver.
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
 *   Preconditions           : Gpt_Driver must be initialized.
 *
 ****************************************************************************************************/
void Gpt_Demo
(
    void
)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId ();

    if ((Gpt_DemoCoreSelFlg== CoreId) &&(GptCoreExeFlag.CoreCmdExist == 1U))
    {
        Timer_DelayMs (10);
        switch (GptCoreExeFlag.CoreExeCmd)
        {
            /* Demo1: Start continuous timer */
            case '1':
            {
                Gpt_ContinuousCountDemo0();
#ifndef THA6_THA6104
                Gpt_ContinuousCountDemo1();
#endif
                break;
            }
            /* Demo2: Start one-shot timer */
            case '2':
            {
                Gpt_OneshotCountDemo0();
                Gpt_OneshotCountDemo1();
                break;
            }
            /* Demo3: Get predefine timer value */
            case '3':
            {
                Gpt_DemoPredefTimer();
                break;
            }
            default:
            {
                DEBUG_PRINTF("\r\n Please input correctly options! \r\n");
                break;
            }
        }

        /* 0xFF means there is no valid demo selection */
        if (0xFFU != GptCoreExeFlag.CoreExeCmd)
        {
            GptCoreExeFlag.CoreExeCmd = 0xFFU;
        }

        GptCoreExeFlag.CoreCmdExist = 0U;
    }
    /* Master core set the flag */
    if (1U == Gpt_DemoCoreInitStatus[CoreId])
    {
        /* Initialize and each core needs to be initialized once */
        Gpt_DemoCoreInitStatus[CoreId] = 2U;
        if (CoreId != 0U)
        {
            Gpt_Init (&Gpt_ConfigSet[0]);
        }
    }
    /* Only core1 is able to run to here, to de-init the Gpt module of current core */
    else if (3U == Gpt_DemoCoreInitStatus[CoreId])
    {
        Gpt_DemoCoreInitStatus[CoreId] = 0U;
    }

}/* Gpt_Demo() */


/****************************************************************************************************
*   Function Name           : Gpt_DemoSelect
*
*   Service ID              : None.
*
*   Description             : Select which demo to run.
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
static void Gpt_DemoSelect(void)
{
    uint8 Cmd;
    uint8 Gpt_Exit;
    Std_VersionInfoType Gpt_ver;

    Gpt_Exit = 0U;

    while (0U == Gpt_Exit)
    {
        Gpt_GetVersionInfo (&Gpt_ver);
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*********************************************************/");
        DEBUG_PRINTF("\n           GPT DRIVER DEMO MENU V%02d.%02d.%02d            ",
                Gpt_ver.sw_major_version, Gpt_ver.sw_minor_version, Gpt_ver.sw_patch_version);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n <1>:  Start continuous timer");
        DEBUG_PRINTF("\n <2>:  Start one-shot timer");
        DEBUG_PRINTF("\n <3>:  Predeftime");

        DEBUG_PRINTF("\n <x>: Go back to main menu\n");
        DEBUG_PRINTF("\nEnter option Number: ");

        Cmd = DEBUG_GETC();

        if(('1' == Cmd) || ('2' == Cmd) || ('3' == Cmd))
        {
            /* Convert the command character to number */
            GptCoreExeFlag.CoreExeCmd = Cmd;
            /* Set it to inform the Core to running the demo
             * It must be here */
            GptCoreExeFlag.CoreCmdExist = 1U;
            /* Delay for initialization of other core  */
            Timer_DelayMs (100);

            /* Call Gpt_Demo direct in Core 0 */
            Gpt_Demo ();
            while (0xFFU != GptCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Gpt demo test finished */
            }
            /* Clear it to wait next command */
            GptCoreExeFlag.CoreCmdExist = 0U;
        }
        else if (((char) Cmd == 'x') || ((char) Cmd == 'X'))
        {
            Gpt_Exit = 1U;
            GptCoreExeFlag.CoreExeCmd = 0xFFU;
            GptCoreExeFlag.CoreCmdExist = 0U;
        }
        else
        {
            DEBUG_PRINTF("\r\n Entered wrong option Number\r\n");
        }
    }
}

/****************************************************************************************************
*   Function Name           : Gpt_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Gpt demo application entry.
*                             Select which core to use to run Gpt Channel.
*                             This APi shall be called by main core(Core 0).
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
void Gpt_DemoEntry(void)
{
    uint8 Cmd;
    uint8 Gpt_Exit;
    Mcal_CoreType CoreId;

    Gpt_Exit = 0U;
    
    CoreId = Mcal_GetCoreId ();

    if (0U == Gpt_DemoCoreInitStatus[CoreId])
    {
        /* Set the flag to allow core 1 initialization */
        Gpt_DemoCoreInitStatus[1] = 1U;
        /* Wait core1 to initialize */
        Timer_DelayMs (100);
    }

    /* An infinite loop is used to let the user select a core to execute the demo */
    while (0U == Gpt_Exit)
    {
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("\n              GPT DRIVER DEMO MENU V%d.%d.%d                    ",
                GPT_SW_MAJOR_VERSION,GPT_SW_MINOR_VERSION,GPT_SW_PATCH_VERSION);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Gpt Demo in Core0. ");
#ifndef THA6_THA6104
        DEBUG_PRINTF("\n  <2> : Gpt Demo in Core1. ");
#endif
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        /* Wait for the user to enter options of the core */
        Cmd = DEBUG_GETC();

        /* User option:
         * 1: Demo core is core0
         * 2: Demo core is core1
         * X/x: Back to module demo menu */
        switch ((char) Cmd)
            {
                case '1':
                    {
                        /* Demo for Core0 */
                        Gpt_DemoCoreSelFlg = MCAL_CORE0;
                        DEBUG_PRINTF("\n  Choose the Core0 to execute demo \n");
                        Gpt_DemoSelect ();
                        break;
                    }
#ifndef THA6_THA6104
                case '2':
                    {
                        /* Demo for Core1 */
                        Gpt_DemoCoreSelFlg = MCAL_CORE1;
                        DEBUG_PRINTF("\n  Choose the Core1 to execute demo \n");
                        Gpt_DemoSelect ();
                        break;
                    }
#endif
                case 'x':
                case 'X':
                    {
                        /* Exit GPT Demo */
                        Gpt_Exit = 1U;
                        /* Set other core's flag , other core statrs to de-initialize */
                        Gpt_DemoCoreInitStatus[1] = 3U;

                        Gpt_DemoCoreInitStatus[0] = 0U;
                        break;
                    }
                default:
                {
                    DEBUG_PRINTF("\n Please input correctly options! \n");
                    break;
                }
            }
    }
}

#define GPT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Gpt_MemMap.h"


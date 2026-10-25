/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Pwm_Demo.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GTM-TOM, GTM-ATOM
 *
 *   brief                 : This file contains Demo application for Pwm Driver
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
#include "Demo_Common.h"
#include "Pwm_Demo.h"
#include "ComStack_Types.h"
#include "Pwm_GeneralTypes.h"
#include "Pwm.h"
#include "Pwm_Irq.h"
#include "Intc.h"
#include "Pwm_Version.h"
#include "Pwm.h"

/****************************************************************************************************
 **                          Private Macro Definitions                                              **
 ****************************************************************************************************/
typedef volatile struct
{
    uint8 CoreCmdExist; /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} CoreExeType;
/****************************************************************************************************
 **                          Private Variable Definitions                                           **
 ****************************************************************************************************/
#define PWM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Pwm_MemMap.h"

static volatile uint32 PwmChannel00_NotificationNumber;
static volatile uint32 PwmChannel01_NotificationNumber;
static volatile uint32 PwmChannel04_NotificationNumber;
static volatile uint32 PwmChannel05_NotificationNumber;

static uint8 Pwm_DemoCoreSelFlg;
static CoreExeType PwmCoreExeFlag;
static uint8 Pwm_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES];

#define PWM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Pwm_MemMap.h"

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
#define PWM_START_SEC_CODE_ASIL_D_GLOBAL
#include "Pwm_MemMap.h"

/****************************************************************************************************
 **                          Private Function Definitions                                           **
 ****************************************************************************************************/

/****************************************************************************************************
 **                          Global Function Definitions                                            **
 ****************************************************************************************************/
void Pwm_Notification_0 (void)
{
  PwmChannel00_NotificationNumber++;
}

void Pwm_Notification_1 (void)
{
  PwmChannel01_NotificationNumber++;
}

void Pwm_Notification_4 (void)
{
  PwmChannel04_NotificationNumber++;
}

void Pwm_Notification_5(void)
{
  PwmChannel05_NotificationNumber++;
}


/****************************************************************************************************
 *   Function Name           : Pwm_Demo
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo API for Pwm driver.
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
 *   Preconditions           : Pwm_Driver must be uninitialized.
 *
 ****************************************************************************************************/
void Pwm_Demo
(
    void

)
{
  Mcal_CoreType CoreId;
  uint32 FirstChannelId;
  Pwm_OutputStateType Level;
  uint32 Status;

  Status = 0U;

  CoreId = Mcal_GetCoreId();

  /* Channel0~channel3 are belong to core0 */
  if (MCAL_CORE0 == CoreId)
  {
    FirstChannelId = 0U;
  }
  /* Channel4~channel7 are belong to core1 */
  else
  {
    FirstChannelId = 4U;
  }


  /* If the execute core is current core and the command is valid, execute the related demo */
  if ((Pwm_DemoCoreSelFlg == CoreId) && (PwmCoreExeFlag.CoreCmdExist == 1U))
  {
    switch (PwmCoreExeFlag.CoreExeCmd)
    {
      /* Demo1: Set period and duty cycle */
      case '1':
      {
        /* Core0:P2.1, Core1:P0.6 */
        DEBUG_PRINTF("\r\nDemo1: Set channel%d 2ms-50%% to 1ms-50%%\r\n", (FirstChannelId + 1U));
        DEBUG_PRINTF("Observe pin: Core0-P2.1,  Core1-P0.6\r\n");
        PwmChannel01_NotificationNumber = 0U;
        PwmChannel05_NotificationNumber = 0U;

        Pwm_EnableNotification((FirstChannelId + 1), PWM_FALLING_EDGE);
        /* Set period of 2ms and duty cycle of 1ms to 1ms and 0.5ms */
        Pwm_SetPeriodAndDuty((FirstChannelId + 1), 1000, 500);

        Timer_DelayMs(5);
        Pwm_DisableNotification((FirstChannelId + 1));

        if (MCAL_CORE0 == CoreId)
        {
          if (0U != PwmChannel01_NotificationNumber)
          {
            DEBUG_PRINTF("Result = Pass;\r\n");
          }
          else
          {
            DEBUG_PRINTF("Result = Fail;\r\n");
          }
        }
        /* Channel4~channel7 are belong to core1 */
        else
        {
          if (0U != PwmChannel05_NotificationNumber)
          {
            DEBUG_PRINTF("Result = Pass;\r\n");
          }
          else
          {
            DEBUG_PRINTF("Result = Fail;\r\n");
          }
        }

        break;
      }
        /* Demo2: Set duty cycle */
      case '2':
      {
        DEBUG_PRINTF("\r\nDemo2: Set channel%d 2ms-50%% to 2ms-25%%\r\n", FirstChannelId);
        DEBUG_PRINTF("Demo2: Set channel%d 2ms-50%% to 2ms-25%%\r\n", (FirstChannelId + 2U));
        DEBUG_PRINTF("Demo2: Set channel%d 2ms-50%% to 2ms-25%%\r\n", (FirstChannelId + 3U));
        DEBUG_PRINTF("Observe pin: Core0-P2.1-P2.2-P2.3,  Core1-P0.5-P2.6-P2.7\r\n");
        
        PwmChannel00_NotificationNumber = 0U;
        PwmChannel04_NotificationNumber = 0U;

        Pwm_SetDutyCycle(FirstChannelId, 500U);
        Pwm_SetDutyCycle((FirstChannelId + 2U), 500U);
        Pwm_SetDutyCycle((FirstChannelId + 3U), 500U);
        Pwm_EnableNotification(FirstChannelId, PWM_FALLING_EDGE);

        Timer_DelayMs(5);
        Pwm_DisableNotification(FirstChannelId);

        if (MCAL_CORE0 == CoreId)
        {
          if (0U != PwmChannel00_NotificationNumber)
          {
            DEBUG_PRINTF("Result = Pass;\r\n");
          }
          else
          {
            DEBUG_PRINTF("Result = Fail;\r\n");
          }
        }
        else
        {
          if (0U !=PwmChannel04_NotificationNumber)
          {
            DEBUG_PRINTF("Result = Pass;\r\n");
          }
          else
          {
            DEBUG_PRINTF("Result = Fail;\r\n");
          }
        }

        break;
      }
        /* Demo2: Set output to idle level */
      case '3':
      {
        DEBUG_PRINTF("\r\nDemo3: Set channel%d to idle level(HIGH)\r\n", FirstChannelId);
        DEBUG_PRINTF("Demo3: Set channel%d to idle level(HIGH)\r\n", (FirstChannelId + 1U));
        DEBUG_PRINTF("Demo3: Set channel%d to idle level(HIGH)\r\n", (FirstChannelId + 2U));
        DEBUG_PRINTF("Demo3: Set channel%d to idle level(HIGH)\r\n", (FirstChannelId + 3U));
        DEBUG_PRINTF("Observe pin: Core0-P2.1-P2.2-P2.3,  Core1-P0.5-P2.6-P2.7\r\n");

        Pwm_SetOutputToIdle(FirstChannelId + 1U);
        Pwm_SetOutputToIdle(FirstChannelId + 2U);
        Pwm_SetOutputToIdle(FirstChannelId + 3U);
        Pwm_SetOutputToIdle(FirstChannelId);

        Level = Pwm_GetOutputState(FirstChannelId + 1U);
        if(Level != PWM_HIGH)
        {
            Status++;
        }

        Level = Pwm_GetOutputState(FirstChannelId + 2U);
        if(Level != PWM_HIGH)
        {
            Status++;
        }

        Level = Pwm_GetOutputState(FirstChannelId + 3U);
        if(Level != PWM_HIGH)
        {
            Status++;
        }

        Level = Pwm_GetOutputState(FirstChannelId);
        if(Level != PWM_HIGH)
        {
            Status++;
        }

        if (0U == Status)
        {
          DEBUG_PRINTF("Result = Pass;\r\n");
        }
        else
        {
          DEBUG_PRINTF("Result = Fail;\r\n");
        }

        break;
      }
        /* Demo4: Get output level */
      case '4':
      {

        DEBUG_PRINTF("Demo4: Get output level\r\n");

        Level = Pwm_GetOutputState(FirstChannelId);

        if (PWM_LOW == Level)
        {
          DEBUG_PRINTF("Channel%d output state is PWM_LOW\r\n", FirstChannelId);
        }
        else
        {
          DEBUG_PRINTF("Channel%d output state is PWM_HIGH\r\n", FirstChannelId);
        }

        Level = Pwm_GetOutputState(FirstChannelId + 1U);
        if (PWM_LOW == Level)
        {
          DEBUG_PRINTF("Channel%d output state is PWM_LOW\r\n", (FirstChannelId + 1U));
        }
        else
        {
          DEBUG_PRINTF("Channel%d output state is PWM_HIGH\r\n", (FirstChannelId + 1U));
        }

        Level = Pwm_GetOutputState(FirstChannelId + 2U);
        if (PWM_LOW == Level)
        {
          DEBUG_PRINTF("Channel%d output state is PWM_LOW\r\n", (FirstChannelId + 2U));
        }
        else
        {
          DEBUG_PRINTF("Channel%d output state is PWM_HIGH\r\n", (FirstChannelId + 2U));
        }

        Level = Pwm_GetOutputState(FirstChannelId + 3U);
        if (PWM_LOW == Level)
        {
          DEBUG_PRINTF("Channel%d output state is PWM_LOW\r\n", (FirstChannelId + 3U));
        }
        else
        {
          DEBUG_PRINTF("Channel%d output state is PWM_HIGH\r\n", (FirstChannelId + 3U));
        }

        break;
      }
      default:
      {
        break;
      }
    }

    /* 0xFF means there is no valid demo selection */
    if (0xFFU != PwmCoreExeFlag.CoreExeCmd)
    {
      PwmCoreExeFlag.CoreExeCmd = 0xFFU;
    }
  }

  /* This branch is executed once to initialize the pwm driver in current core */
  if (1U == Pwm_DemoCoreInitStatus[CoreId])
  {
    /* Initialize and each core needs to be initialized once */
    Pwm_DemoCoreInitStatus[CoreId] = 2U;
    if (CoreId != 0U)
    {
      Pwm_Init(&Pwm_ConfigSet[0]);
      DEBUG_PRINTF("\r\n----------------------------------------\r\n");
      DEBUG_PRINTF("\r\n PWM starts to generate in Core1\r\n");
      DEBUG_PRINTF("     P0.5: Fixed period channel\r\n");
      DEBUG_PRINTF("           - Period    : 2ms \r\n");
      DEBUG_PRINTF("           - Duty Cycle: 1ms \r\n");

      DEBUG_PRINTF("     P0.6: Variable period channel\r\n");
      DEBUG_PRINTF("           - Period    : 2ms \r\n");
      DEBUG_PRINTF("           - Duty Cycle: 1ms \r\n");

      DEBUG_PRINTF("     P2.6: Fixed period shift channel\r\n");
      DEBUG_PRINTF("           - Duty Cycle : 1ms \r\n");
      DEBUG_PRINTF("           - Shift Value: 200Tick(200us) \r\n");
      DEBUG_PRINTF("           - Reference channel : Channel4(P0.5) \r\n");

      DEBUG_PRINTF("     P2.7: Central aligned channel\r\n");
      DEBUG_PRINTF("           - Duty Cycle: 1ms \r\n");
      DEBUG_PRINTF("           - Reference channel : Channel4(P0.5) \r\n");
      DEBUG_PRINTF("\r\n----------------------------------------\r\n");
    }
  }
  /* Only core1 is able to run to here, to de-init the Gpt module of current core */
  else if (3U == Pwm_DemoCoreInitStatus[CoreId])
  {
    Pwm_DemoCoreInitStatus[CoreId] = 0U;
    Pwm_DeInit();
  }
} /* Pwm_Demo() */

/****************************************************************************************************
 *   Function Name           : Pwm_DemoSelect
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
static void Pwm_DemoSelect
(
    void

)
{
    uint8 Cmd;
    uint8 Pwm_Exit;
    Std_VersionInfoType Pwm_ver;

    Pwm_Exit = 0U;
    while (0U == Pwm_Exit)
    {
        Pwm_GetVersionInfo (&Pwm_ver);
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*********************************************************/");
        DEBUG_PRINTF("\n           PWM DRIVER DEMO MENU V%02d.%02d.%02d            ",
                Pwm_ver.sw_major_version, Pwm_ver.sw_minor_version, Pwm_ver.sw_patch_version);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n <1>:  Set period and duty cycle");
        DEBUG_PRINTF("\n <2>:  Set duty cycle");
        DEBUG_PRINTF("\n <3>:  Set output to idle level");
        DEBUG_PRINTF("\n <4>:  Get output level");
        DEBUG_PRINTF("\n <x>: Go back to main menu\n");
        DEBUG_PRINTF("\nEnter option Number: ");

        Cmd = DEBUG_GETC();

        if(('1' == Cmd) || ('2' == Cmd) || ('3' == Cmd) || ('4' == Cmd))
        {
            /* Convert the command character to number */
            PwmCoreExeFlag.CoreExeCmd = Cmd;
            /* Set it to inform the Core to running the demo
             * It must be here */
            PwmCoreExeFlag.CoreCmdExist = 1U;
            /* Delay for initialization of other core  */
            Timer_DelayMs (100);

            /* Call Pwm_Demo direct in Core 0 */
            Pwm_Demo();
            while (0xFFU != PwmCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Pwm demo test finished */
            }
            /* Clear it to wait next command */
            PwmCoreExeFlag.CoreCmdExist = 0U;
        }
        else if (((char) Cmd == 'x') || ((char) Cmd == 'X'))
        {
            Pwm_Exit = 1U;
            PwmCoreExeFlag.CoreExeCmd = 0xFFU;
        }
        else
        {
            DEBUG_PRINTF("\r\n Entered wrong option Number\r\n");
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Pwm_DemoEntry
 *
 *   Service ID              : None.
 *
 *   Description             : Pwm demo application entry.
 *                             Select which core to use to run Pwm Channel.
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
void Pwm_DemoEntry
(
    void
)
{
    uint8 Cmd;
    uint8 Pwm_Exit;

    Pwm_Exit = 0U;

    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId ();

    /* Initialize the Pwm in current core */
    Pwm_Init (&Pwm_ConfigSet[0]);
    DEBUG_PRINTF("\r\n----------------------------------------\r\n");
    DEBUG_PRINTF("\r\n PWM starts to generate in Core0\r\n");
    DEBUG_PRINTF("     P2.0: Fixed period channel\r\n");
    DEBUG_PRINTF("           - Period    : 2ms \r\n");
    DEBUG_PRINTF("           - Duty Cycle: 1ms \r\n");

    DEBUG_PRINTF("     P2.1: Variable period channel\r\n");
    DEBUG_PRINTF("           - Period    : 2ms \r\n");
    DEBUG_PRINTF("           - Duty Cycle: 1ms \r\n");

    DEBUG_PRINTF("     P2.2: Fixed period shift channel\r\n");
    DEBUG_PRINTF("           - Duty Cycle : 1ms \r\n");
    DEBUG_PRINTF("           - Shift Value: 200Tick(200us) \r\n");
    DEBUG_PRINTF("           - Reference channel : Channel0(P2.0) \r\n");

    DEBUG_PRINTF("     P2.3: Central aligned channel\r\n");
    DEBUG_PRINTF("           - Duty Cycle: 1ms \r\n");
    DEBUG_PRINTF("           - Reference channel : Channel0(P2.0) \r\n");
    DEBUG_PRINTF("\r\n----------------------------------------\r\n");

    if (0U == Pwm_DemoCoreInitStatus[CoreId])
    {
        /* Set the flag to allow core 1 initialization */
        Pwm_DemoCoreInitStatus[1] = 1U;
        /* Wait core1 to initialize */
        Timer_DelayMs (100);
    }

    while (0U == Pwm_Exit)
    {
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("\n              PWM DRIVER DEMO MENU V%d.%d.%d                    ",
                     PWM_SW_MAJOR_VERSION,PWM_SW_MINOR_VERSION,PWM_SW_PATCH_VERSION);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Pwm Demo in Core0. ");
#ifndef THA6_THA6104
        DEBUG_PRINTF("\n  <2> : Pwm Demo in Core1. ");
#endif
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Cmd = DEBUG_GETC();

        switch ((char) Cmd)
            {
            case '1':
                {
                    /* Demo for Core0 */
                    Pwm_DemoCoreSelFlg = MCAL_CORE0;
                    DEBUG_PRINTF("\n  Choose the Core0 to execute demo \n");
                    Pwm_DemoSelect ();
                    break;
                }
#ifndef THA6_THA6104
            case '2':
                {
                    /* Demo for Core1 */
                    Pwm_DemoCoreSelFlg = MCAL_CORE1;
                    DEBUG_PRINTF("\n  Choose the Core1 to execute demo \n");
                    Pwm_DemoSelect ();
                    break;
                }
#endif
            case 'x':
            case 'X':
                {
                      /* Exit PWM Demo */
                    Pwm_Exit = 1U;
                    /* Set other core's flag , other core starts to de-initialize */
                    Pwm_DemoCoreInitStatus[1] = 3U;
                    /* DeInit the Pwm module of current core */
                    Pwm_DeInit ();

                    Pwm_DemoCoreInitStatus[0] = 0U;
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

#define PWM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Pwm_MemMap.h"


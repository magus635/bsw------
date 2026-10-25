/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Iom_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : This file contains Demo application for Iom Driver
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
#include "Uart_Demo.h"
#include "Iom_Demo.h"
#include "Demo_Common.h"
#include "Iom_GeneralTypes.h"
#include "Iom.h"
#include "Dio.h"
#include "Pwm.h"
#include "Iom_Version.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
typedef volatile struct
{
    uint8 CoreCmdExist;    /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} Iom_ChannelCoreExeType;
/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"

static uint8 Iom_DemoCoreSelFlg = MCAL_CORE0;

#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"

#define LIN_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"

static Iom_ChannelCoreExeType IomCoreExeFlag = {0, 0xFFU};

#define LIN_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#define IOM_START_SEC_CODE_ASIL_D_GLOBAL
#include "Iom_MemMap.h"
/****************************************************************************************************
*   Function Name           : Iom_Demo
*
*   Service ID              : None.
*
*   Description             : Iom Demo function.
*                             Received UART data:
*                             1 - duty cycle too short
*                             2 - duty cycle normal
*                             3 - duty cycle too long
*                             4 - Signal delay too long
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
void Iom_Demo(void)
{
    Mcal_CoreType CoreId;
    Std_ReturnType EveHisRlt;

    CoreId = Mcal_GetCoreId();
    if ((Iom_DemoCoreSelFlg == CoreId) && (1U == IomCoreExeFlag.CoreCmdExist))
    {
        switch (IomCoreExeFlag.CoreExeCmd)
        {
            case 1:
            {
                DEBUG_PRINTF("\nCommand:1");
                /* duty cycle too short */
                /* Threshold 30us; test signal Period:200us, duty12.5% */
                Pwm_Init(&Pwm_ConfigSet[CoreId]);
                Pwm_SetPeriodAndDuty(PwmConf_PwmChannel_PwmChannel_8, 200U, 25U);
                Iom_SetLpuEventWindowTimeThreshold(IOM_LPUID_0, 3000U);/* 150U */
                Iom_ClrEmuEventTriggerHistory();
                Iom_EnableEmuCounter();
                Timer_DelayMs(100);
                EveHisRlt = Iom_GetLpuChannelTrigHistory(IOM_LPUID_0);
                if (E_OK == EveHisRlt)
                {
                    DEBUG_PRINTF("\nResult = OK, IOM detects that the duty cycle is too small;");
                }
                else
                {
                    DEBUG_PRINTF("\nResult = NG, IOM does not detect that the duty cycle is too small;");
                }
                Pwm_DeInit();
                break;
            }
            case 2:
            {
                DEBUG_PRINTF("\nCommand:2");
                /* duty cycle normal */
                /* Threshold 100us; test signal Period:200us,duty 62.5% */
                Pwm_Init(&Pwm_ConfigSet[CoreId]);
                Pwm_SetPeriodAndDuty(PwmConf_PwmChannel_PwmChannel_8, 200U, 125U);
                Iom_SetLpuEventWindowTimeThreshold(IOM_LPUID_0, 10000U);/* 500U */
                Iom_ClrEmuEventTriggerHistory();
                Iom_EnableEmuCounter();
                Timer_DelayMs(100);
                EveHisRlt = Iom_GetLpuChannelTrigHistory(IOM_LPUID_0);
                if (E_OK == EveHisRlt)
                {
                    DEBUG_PRINTF("Result = NG, IOM detects that the duty cycle is normal;");
                }
                else
                {
                    DEBUG_PRINTF("Result = OK, IOM does not detect that the duty cycle is normal;");
                }
                Pwm_DeInit();
                break;
            }
            case 3:
            {
                DEBUG_PRINTF("\nCommand:3");
                /* The duty cycle remains the 12.5%, but the event window threshold setting is small enough not to alert */
                /* Threshold 10us; test signal Period:200us,duty 12.5% */
                Pwm_Init(&Pwm_ConfigSet[CoreId]);
                Pwm_SetPeriodAndDuty(PwmConf_PwmChannel_PwmChannel_8, 200U, 25U);
                Iom_SetLpuEventWindowTimeThreshold(IOM_LPUID_0, 1000U);/* 50U */
                Iom_ClrEmuEventTriggerHistory();
                Iom_EnableEmuCounter();
                Timer_DelayMs(100);
                EveHisRlt = Iom_GetLpuChannelTrigHistory(IOM_LPUID_0);
                if (E_OK == EveHisRlt)
                {
                    DEBUG_PRINTF("Result = NG, IOM detects that the duty cycle is normal;");
                }
                else
                {
                    DEBUG_PRINTF("Result = OK, IOM does not detect that the duty cycle is normal;");
                }
                Pwm_DeInit();
                break;
            }
            case 4:
            {
                DEBUG_PRINTF("\nCommand:4");
                /* duty cycle too short */
                /* Threshold 150us; test signal Period:200us,duty 50% */
                Pwm_Init(&Pwm_ConfigSet[CoreId]);
                Pwm_SetPeriodAndDuty(PwmConf_PwmChannel_PwmChannel_8, 200U, 100U);
                Iom_SetLpuEventWindowTimeThreshold(IOM_LPUID_0, 15000U);/* 750U */
                Iom_ClrEmuEventTriggerHistory();
                Iom_EnableEmuCounter();
                Timer_DelayMs(100);
                EveHisRlt = Iom_GetLpuChannelTrigHistory(IOM_LPUID_0);
                if (E_NOT_OK == EveHisRlt)
                {
                    DEBUG_PRINTF("Result = NG, IOM detects that the duty cycle is normal;");
                }
                else
                {
                    DEBUG_PRINTF("Result = OK, IOM detect that the duty cycle is too small;");
                }
                Pwm_DeInit();
                break;
            }
            default:
            {
                DEBUG_PRINTF("\n\n  INVALID OPTION");
                break;
            }
        }
        if (0xFFU != IomCoreExeFlag.CoreExeCmd)
        {
            IomCoreExeFlag.CoreExeCmd = 0xFFU;
            /* Clear it to wait next command */
            IomCoreExeFlag.CoreCmdExist = 0U;
        }
    }
}


/****************************************************************************************************
*   Function Name           : Iom_DemoEntry
*
*   Service ID              : None.
*
*   Description             : This function is the demo API for IOM driver.
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
*   Preconditions           : IOM_Driver must be uninitialized.
*
****************************************************************************************************/
void Iom_DemoSelect(void)
{
    char cmd;
    volatile uint8 loopvar = 0;
    Std_VersionInfoType VersionInfo;

    Iom_Init(&Iom_ConfigSet[0]);
    Iom_GetVersionInfo(&VersionInfo);
    while (loopvar == 0U)
    {
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF("\n              IOM DRIVER DEMO MENU V%d.%d.%d                    ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n <1>:  duty cycle too short ");
        DEBUG_PRINTF("\n <2>:  set pwm duty cycle normal ");
        DEBUG_PRINTF("\n <3>:  set iom to make pwm duty cycle normal ");
        DEBUG_PRINTF("\n <4>:  set iom to make pwm duty cycle too short ");
        DEBUG_PRINTF("\n <x>: Go back to main menu\n");
        DEBUG_PRINTF("\nEnter option Number: ");

        cmd = DEBUG_GETC();

        if ((cmd >= 0x31U) && (cmd <= 0x34U))    /* ASCII '1'-'8' */
        {
            /* Convert the command character to number */
            IomCoreExeFlag.CoreExeCmd = (cmd - 0x30U);
            /* Set it to inform the Core to running the demo
            * It must be here */
            IomCoreExeFlag.CoreCmdExist = 1U;
            /* Call Iom_Demo direct in Core 0 */
            Iom_Demo();
            while(0xFFU != IomCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Iom demo test finished */
            }
        }
        else if (((char)cmd == 'x') || ((char)cmd == 'X'))
        {
            loopvar = 1U;
            IomCoreExeFlag.CoreExeCmd = 0xFFU;
        }
        else
        {
            DEBUG_PRINTF("\n\n  INVALID OPTION");
        }
    }/* End of While loop */

}/* Iom_Demo() */

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Iom_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Lin demo application entry.
*                             Select which core to use to run Lin Channel.
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
void Iom_DemoEntry(void)
{
    uint8               Cmd  = 0U;
    uint8               Exit = 0U;
    Std_VersionInfoType VersionInfo;

    Exit = 0U;
    while (0U == Exit)
    {
        Iom_GetVersionInfo(&VersionInfo);
        DEBUG_PRINTF((const uint8*)"\n\n\n");
        DEBUG_PRINTF((const uint8*)"\n/*********************************************************/");
        DEBUG_PRINTF((const uint8*)"\n           IOM DRIVER DEMO MENU V%02d.%02d.%02d            ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF((const uint8*)"\n                                                         ");
        DEBUG_PRINTF((const uint8*)"\n  <1> : Iom Demo in Core0. ");
#if 0
        DEBUG_PRINTF((const uint8*)"\n  <2> : Iom Demo in Core1. ");
#endif /* (MCAL_CFG_ENABLE_CORE1  \== STD_ON) */
        DEBUG_PRINTF((const uint8*)"\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF((const uint8*)"\n  ENTER YOUR OPTION   : ");

        /* Waiting till received a uart command character */
        Cmd = DEBUG_GETC();

        switch ((char)Cmd)
        {
            case '1':
            {
                /* Demo for Core0 */
                Iom_DemoCoreSelFlg = MCAL_CORE0;
                DEBUG_PRINTF((const uint8*)"\n  Choose the Core0 to running demo. \n");
                Iom_DemoSelect();
                break;
            }
#if 0
            case '2':
            {
                /* Demo for Core1 */
                Iom_DemoCoreSelFlg = MCAL_CORE1;
                DEBUG_PRINTF((const uint8*)"\n  Choose the Core1 to running demo. \n");
                Iom_DemoSelect();
                break;
            }
#endif /* ((MCAL_USED_CORE_MASK&MCAL_CORE1) == MCAL_CORE1) */
            case 'x':
            case 'X':
            {
                Exit = 1U;
                break;
            }
            default:
            {
                DEBUG_PRINTF("\n\n  INVALID OPTION");
                break;
            }
        }
    }
}

#define IOM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Iom_MemMap.h"



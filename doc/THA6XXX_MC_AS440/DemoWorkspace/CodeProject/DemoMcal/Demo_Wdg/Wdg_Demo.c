/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Wdg_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : This file contains Demo application for Wdg Driver
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
#include "Wdg_Cfg.h"
#include "Wdg.h"
#include "Intc.h"
#include "Wdg_Demo.h"
#include "Mcall.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
typedef struct
{
    uint8 CoreCmdExist;    /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} Wdg_ChannelCoreExeType;

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define WDG_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "Wdg_MemMap.h"

static volatile Wdg_ChannelCoreExeType WdgCoreExeFlag = {0, 0xFFU};

#define WDG_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "Wdg_MemMap.h"

#define WDG_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Wdg_MemMap.h"

static uint8 Wdg_DemoCoreSelFlg = MCAL_CORE0;
static volatile  uint8 Wdg_NotificationlFlag = 0U;

#define WDG_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Wdg_MemMap.h"

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
#define WDG_START_SEC_CODE_ASIL_D_GLOBAL
#include "Wdg_MemMap.h"

static void Wdg_DemoSelect(void);
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : Wdg_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Wdg demo application entry.
*                             Select which core to use to run Wdg demo.
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
void Wdg_DemoEntry(void)
{
    uint8 cmd;
    volatile uint8 loopvar = 0;
    Std_VersionInfoType VersionInfo;

    Wdg_GetVersionInfo(&VersionInfo);

    while (loopvar == 0U)
    {

        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                     WDG DRIVER DEMO MENU                          ");
        DEBUG_PRINTF("\n                      WDG Version V%d.%d.%d                        ",
          VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Run Wdg Demo in Core0. ");
#if (MCAL_CFG_ENABLE_CORE1 == STD_ON)
        DEBUG_PRINTF("\n  <2> : Run Wdg Demo in Core1. ");
#endif /* (MCAL_CFG_ENABLE_CORE1  \== STD_ON) */
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        loopvar = 0U;
        cmd = DEBUG_GETC();
        DEBUG_PRINTF("%c", cmd);
        switch ((char)cmd)
        {
            case '1':
            {
                /* Demo for Core0 */
                Wdg_DemoCoreSelFlg = MCAL_CORE0;
                DEBUG_PRINTF("\n  Choose the Core0 to running demo. \n");
                Wdg_DemoSelect();
                break;
            }
#if (MCAL_CFG_ENABLE_CORE1 == STD_ON)
            case '2':
            {
                /* Demo for Core1 */
                Wdg_DemoCoreSelFlg = MCAL_CORE1;
                DEBUG_PRINTF("\n  Choose the Core1 to running demo. \n");
                Wdg_DemoSelect();
                break;
            }
#endif /* (MCAL_CFG_ENABLE_CORE1  \== STD_ON) */
            case 'x':
            case 'X':
            {
                loopvar = 1;
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

/****************************************************************************************************
*   Function Name           : Wdg_DemoSelect
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
static void Wdg_DemoSelect(void)
{
    uint8 cmd;
    uint8 Wdg_exit;
    Std_VersionInfoType VersionInfo;

    Wdg_GetVersionInfo(&VersionInfo);
    Wdg_exit = 0U;
    while (0U == Wdg_exit)
    {
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                     WDG DRIVER DEMO MENU                          ");
        DEBUG_PRINTF("\n                      WDG Version V%d.%d.%d                        ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Initiate wdg driver. ");
        DEBUG_PRINTF("\n  <2> : Set wdg in slow mode. ");
        DEBUG_PRINTF("\n  <3> : Set wdg in fast mode. ");
        DEBUG_PRINTF("\n  <4> : Set wdg trigger condition 3 seconds in current mode.");
        DEBUG_PRINTF("\n  <5> : Stop wdg timer. ");
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Wdg_exit = 0U;
        cmd = DEBUG_GETC();
        if ((cmd >= 0x31U) && (cmd <= 0x35U))    /* ASCII '0'-'5' */
        {
            /* Convert the command character to number */
            WdgCoreExeFlag.CoreExeCmd = (cmd - 0x30U);
            /* Set it to inform the Core to running the demo
             * It must be here */
            WdgCoreExeFlag.CoreCmdExist = 1U;
            /* Call Wdg_Demo direct in Core 0 */
            Wdg_Demo();
            while(0xFFU != WdgCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Wdg demo test finished */
            }
            /* Clear it to wait next command */
            WdgCoreExeFlag.CoreCmdExist = 0U;
        }
        else if (((char)cmd == 'x') || ((char)cmd == 'X'))
        {
            WdgCoreExeFlag.CoreExeCmd = 88U;    /* ASCII 'X' */
            WdgCoreExeFlag.CoreCmdExist = 1U;
            Wdg_Demo();
            while(0xFFU != WdgCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Wdg demo test finished */
            }
            Wdg_exit = 1U;
            WdgCoreExeFlag.CoreCmdExist = 0U;
        }
        else
        {
            DEBUG_PRINTF("\n\n  INVALID OPTION");
        }
    }
}

/****************************************************************************************************
*   Function Name           : Wdg_Demo
*
*   Service ID              : None.
*
*   Description             : Wdg Demo function.
*                             Received UART data:
*                             <1> : Initiate wdg driver.
*                             <2> : Set wdg in slow mode.
*                             <3> : Set wdg in fast mode.
*                             <4> : Set wdg trigger condition 3 seconds in current mode.
*                             <5> : Stop wdg timer.
*                             <x> : Go back to Main Menu.
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
void Wdg_Demo(void)
{
    Mcal_CoreType CoreId;
    Std_ReturnType ReturnValue;

    CoreId = Mcal_GetCoreId();
    if ((Wdg_DemoCoreSelFlg == CoreId) && (WdgCoreExeFlag.CoreCmdExist == 1U))
    {
        switch (WdgCoreExeFlag.CoreExeCmd)
        {
            case 1:
            {
                DEBUG_PRINTF("\n\n Wdg has been STARTED.");
                DEBUG_PRINTF("\n The default trigger condition is %d seconds. ",
                                (Wdg_ConfigSet[0].CoreConfigPtr[CoreId]->InitialTimeout /
                                Wdg_ConfigSet[0].CoreConfigPtr[CoreId]->ClockFrequencyKHz / 1000U));
                Wdg_Init(&Wdg_ConfigSet[0]);
                break;
            }
            case 2:
            {
                DEBUG_PRINTF("\n\n Wdg start set mode to SLOW. ");
                DEBUG_PRINTF("\n Watchdog trigger routine is %d ms. ",
                                (Wdg_ConfigSet[0].CoreConfigPtr[CoreId]->SlowModeRefreshTime /
                                Wdg_ConfigSet[0].CoreConfigPtr[CoreId]->ClockFrequencyKHz));
                ReturnValue = Wdg_SetMode(WDGIF_SLOW_MODE);
                if (E_OK == ReturnValue)
                {
                    DEBUG_PRINTF("\n\n Wdg has been set to SLOW mode. ");
                }
                else
                {
                    DEBUG_PRINTF("\n\n Wdg set mode fail. ");
                }
                break;
            }
            case 3:
            {
                DEBUG_PRINTF("\n\n Wdg start set mode to FAST. ");
                DEBUG_PRINTF("\n Watchdog trigger routine is %d ms. ",
                                (Wdg_ConfigSet[0].CoreConfigPtr[CoreId]->FastModeRefreshTime /
                                Wdg_ConfigSet[0].CoreConfigPtr[CoreId]->ClockFrequencyKHz));
                ReturnValue = Wdg_SetMode(WDGIF_FAST_MODE);
                if (E_OK == ReturnValue)
                {
                    DEBUG_PRINTF("\n\n Wdg has been set to FAST mode. ");
                }
                else
                {
                    DEBUG_PRINTF("\n\n Wdg set mode fail. ");
                }
                break;
            }
            case 4:
            {
                Wdg_NotificationlFlag = 0U;
                DEBUG_PRINTF("\n\n Wdg has triggered for 3s. ");
                Wdg_SetTriggerCondition(3000U);
                break;
            }
            case 5:
            {
                DEBUG_PRINTF("\n\n Try stop the Wdg. ");
                (void)Wdg_SetMode(WDGIF_OFF_MODE);
                break;
            }
            case 88:
            {
                if (FALSE != Wdg_ConfigSet[0].CoreConfigPtr[CoreId]->DisableAllowed)
                {
                    DEBUG_PRINTF("\n\n Wdg has been stoped. ");
                    (void)Wdg_SetMode(WDGIF_OFF_MODE);
                }
                else
                {
                    DEBUG_PRINTF("\n\n Wdg can't stop in this Core, Check the Config. ");
                }
                break;
            }
            default:
            {
                break;
            }
        }
        if (0xFFU != WdgCoreExeFlag.CoreExeCmd)
        {
            WdgCoreExeFlag.CoreExeCmd = 0xFFU;
        }
    }
}

/****************************************************************************************************
*   Function Name           : Wdg_Notification
*
*   Service ID              : None.
*
*   Description             : Wdg notification function.
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
void Wdg_Notification(void)
{

    Wdg_NotificationlFlag = 1U;
}

#define WDG_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Wdg_MemMap.h"



/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Port_Demo.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : GPIO
 *
 *   brief                 : This file contains Demo application for Port Driver
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
#include "Mcall.h"
#include "Port.h"
#include "Port_Demo.h"
#include "Demo_Common.h"
#include "Port_TLLD.h"
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* Macro definition to get the base address of the Port group */
#define PORT(Group) \
                ((PORT_MODULE*)((uint32)PORT_P00_BASE_ADDRESS + ((uint32)(Group) * 0x100UL)))
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define PORT_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Port_MemMap.h"

typedef volatile struct
{
    /* The core which shall execute the command */
    /* This variable can only be changed by Core0(master) */
    Mcal_CoreType           CoreExeCmdCore;
    /* The command code */
    uint8                   CoreExeCmd;
    /* Init Status */
    Port_DriverStateType           PortInitStatus;
}Port_CoreExeType;

static Port_CoreExeType PortCoreExeFlag = {MCAL_CORE0, 0xFFU, PORT_UNINITIALIZED};

#define PORT_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Port_MemMap.h"
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
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

static void Port_DemoSelect(void);

#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"
/****************************************************************************************************
*   Function Name           : Port_Demo
*
*   Service ID              : None.
*
*   Description             : Port demo execution function.
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
void Port_Demo(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();
    if ((PortCoreExeFlag.CoreExeCmdCore == CoreId) && (0xFFU != PortCoreExeFlag.CoreExeCmd))
    {
        DEBUG_PRINTF("\n               Current operation core : Core%d", CoreId);
        switch (PortCoreExeFlag.CoreExeCmd)
        {
            case 1:
            {
                DEBUG_PRINTF("\nCommand:1");
                if(1U == PORT(PortConf_PORT_14)->CTR0.B.ENO1)
                {
                    /* Formal parameters Port_PinType is port number multiply 16 plus pin number */
                    Port_SetPinDirection(0x0e1U, PORT_PIN_IN);
                    if(0U == PORT(PortConf_PORT_14)->CTR0.B.ENO1)
                    {
                        DEBUG_PRINTF("\n\n  SUCCESS: Set P14.1 direction from input to output.");
                        Port_SetPinDirection(0x0e1U, PORT_PIN_OUT);
                    }
                    else
                    {
                        DEBUG_PRINTF("\n\n  FAIL: Set P14.1 direction from input to output.");
                    }
                }
                else
                {
                    DEBUG_PRINTF("\n\n  FAIL: P14.1 direction isn't output.");
                }
                break;
            }
            case 2:
            {
                DEBUG_PRINTF("\nCommand:2");
                if(PORT_OUTPUTALT_O1 == (Port_OutputAltModeType)PORT(PortConf_PORT_14)->CTR0.B.SEL1)
                {
                    /* Change P14.1 ALT mode from ALT1 to ALT2 */
                    Port_SetPinMode(0x0e1U, (Port_PinModeType)PORT_OUTPUTALT_O2);
                    if(PORT_OUTPUTALT_O2 == (Port_OutputAltModeType)PORT(PortConf_PORT_14)->CTR0.B.SEL1)
                    {
                        DEBUG_PRINTF("\n\n SUCCESS: Change P14.1 ALT mode from ALT1 to ALT2.");
                        Port_SetPinMode(0x0e1U, (Port_PinModeType)PORT_OUTPUTALT_O1);
                    }
                    else
                    {
                        DEBUG_PRINTF("\n\n FAIL: Change P14.1 ALT mode from ALT1 to ALT2.");
                    }
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: P14.1 ALT mode isn't ALT1.");
                }
                break;
            }
            case 3:
            {
                DEBUG_PRINTF("\nCommand:3");
                /* Check P14.2 Whether the Pin is refreshed to the initial state */
                PORT(PortConf_PORT_14)->CTR0.B.ENO2 = 1U;
                PORT(PortConf_PORT_14)->CTR0.B.SEL2 = (ureg32)PORT_OUTPUTALT_O1;
                Port_RefreshPortDirection();
                if(PORT_PIN_IN == (Port_PinDirectionType)(PORT(PortConf_PORT_14)->CTR0.B.ENO2) &&
                    (PORT_OUTPUTALT_O0 == (Port_OutputAltModeType)PORT(PortConf_PORT_14)->CTR0.B.SEL2))
                {
                    DEBUG_PRINTF("\n\n SUCCESS: Refresh all Port-Pins to initialized state.");
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: Refresh all Port-Pins to initialized state.");
                }
                break;
            }
            default:
            {
                DEBUG_PRINTF("\n\n  INVALID OPTION");
                break;
            }
        }
        if (0xFFU != PortCoreExeFlag.CoreExeCmd)
        {
            PortCoreExeFlag.CoreExeCmd = 0xFFU;
        }
    }
}

/****************************************************************************************************
*   Function Name           : Port_DemoSelect
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
static void Port_DemoSelect(void)
{
    char                    Cmd;
    uint8                   Exit;
    Std_VersionInfoType     VersionInfo;

    Exit = 0U;
    while (0U == Exit)
    {
        Port_GetVersionInfo(&VersionInfo);
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                      PORT DRIVER DEMO MENU                         ");
        DEBUG_PRINTF("\n                       PORT Version V%d.%d.%d                       ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  Port demo.");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Set P14.1 direction from input to output. ");
        DEBUG_PRINTF("\n  <2> : Change P14.1 ALT mode from PORT_OUTPUTALT_O1(GTM) to PORT_OUTPUTALT_O2(ASI). ");
        DEBUG_PRINTF("\n  <3> : Refresh all Port-Pins to initialized state. ");
        DEBUG_PRINTF("\n  <X> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Cmd = DEBUG_GETC();
        switch (Cmd)
        {
            case '1':
            {
                PortCoreExeFlag.CoreExeCmd = 1U;
                break;
            }
            case '2':
            {
                PortCoreExeFlag.CoreExeCmd = 2U;
                break;
            }
            case '3':
            {
                PortCoreExeFlag.CoreExeCmd = 3U;
                break;
            }
            case 'x':
            case 'X':
            {
                Exit = 1;
                /* Set operated core to 0xFF for avoid core conflict */
                PortCoreExeFlag.CoreExeCmdCore = MCAL_CORE0;
                break;
            }
            default:
            {
                DEBUG_PRINTF("\n\n  INVALID OPTION");
                break;
            }
        }
        if (0xFFU != PortCoreExeFlag.CoreExeCmd)
        {
            if (MCAL_CORE0 == PortCoreExeFlag.CoreExeCmdCore)
            {
                /* Call Dio_Demo direct in Core 0 */
                Port_Demo();
            }

            /* Waiting till Dio demo test finished */
            while(0xFFU != PortCoreExeFlag.CoreExeCmd)
            {
                /* Do Nothing */
            }
        }
    }
}

/****************************************************************************************************
*   Function Name           : Port_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Port demo entry function.
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
void Port_DemoEntry(void)
{
    char                Cmd;
    uint8               Exit;
    Std_VersionInfoType VersionInfo;

    Exit = 0U;
    while (0U == Exit)
    {
        Port_GetVersionInfo(&VersionInfo);
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                     Port DRIVER DEMO MENU                          ");
        DEBUG_PRINTF("\n                      Port Version V%d.%d.%d                        ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Run Port Demo in Core0. ");
#if ((MCAL_USED_CORE_MASK & MCAL_CORE1_MASK) == MCAL_CORE1_MASK)
        DEBUG_PRINTF("\n  <2> : Run Port Demo in Core1. ");
#endif /* ((MCAL_USED_CORE_MASK & MCAL_CORE1_MASK) == MCAL_CORE1_MASK) */
        DEBUG_PRINTF("\n  <X> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Cmd = DEBUG_GETC();

        switch (Cmd)
        {
            case '1':
            {
                /* Demo for Core0 */
                PortCoreExeFlag.CoreExeCmdCore = MCAL_CORE0;
                DEBUG_PRINTF("\n  Choose the Core0 to running demo. \n");
                Port_DemoSelect();
                break;
            }
#if ((MCAL_USED_CORE_MASK & MCAL_CORE1_MASK) == MCAL_CORE1_MASK)
            case '2':
            {
                /* Demo for Core1 */
                PortCoreExeFlag.CoreExeCmdCore = MCAL_CORE1;
                DEBUG_PRINTF("\n  Choose the Core1 to running demo. \n");
                Port_DemoSelect();
                break;
            }
#endif /* ((MCAL_USED_CORE_MASK & MCAL_CORE1_MASK) == MCAL_CORE1_MASK) */
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
#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Port_MemMap.h"

/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dio_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains Demo application for Dio Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright /(c) 2021,Beijing Tongxin Microelectroics co.Ltd
*
****************************************************************************************************/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dio_Cfg.h"
#include "Dio.h"
#include "Dio_Demo.h"
#include "Mcall.h"
#include "Demo_Common.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
typedef struct
{
    uint8 CoreCmdExist;    /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} Dio_CoreExeType;

#if (defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412))
#define DIO_CHANNEL_1_REAL_PIN_NAME "P14.4"
#define DIO_CHANNEL_2_REAL_PIN_NAME "P14.5"
#define DIO_GROUP_1_REAL_PIN_NAME   "P14.4-P14.5"
#else
#define DIO_CHANNEL_1_REAL_PIN_NAME "P21.4"
#define DIO_CHANNEL_2_REAL_PIN_NAME "P21.5"
#define DIO_GROUP_1_REAL_PIN_NAME   "P21.4-P21.5"
#endif /* #if ((THA6_THA6206) || (THA6_THA6412)) */
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define DIO_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dio_MemMap.h"

static uint8 Dio_DemoCoreSelFlg = MCAL_CORE0;

#define DIO_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dio_MemMap.h"

#define DIO_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dio_MemMap.h"

static Dio_CoreExeType DioCoreExeFlag = {0, 0xFFU};

#define DIO_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Dio_MemMap.h"

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
#define DIO_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dio_MemMap.h"

static void Dio_DemoSelect(void);

#define DIO_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dio_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#define DIO_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dio_MemMap.h"
/****************************************************************************************************
*   Function Name           : Dio_Demo
*
*   Service ID              : None.
*
*   Description             : Dio Demo function.
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
void Dio_Demo(void)
{
    Mcal_CoreType CoreId;
    uint16 buffer = 0xFFFF;

    CoreId = Mcal_GetCoreId();
    if ((Dio_DemoCoreSelFlg == CoreId) && (DioCoreExeFlag.CoreCmdExist == 1U))
    {
        switch (DioCoreExeFlag.CoreExeCmd)
        {
            case 1:
            {
                DEBUG_PRINTF("\nCommand:1");
                buffer = Dio_ReadChannel(DioConf_DioChannel_DIO_TEST_OUT2);
                if(0xFFFF != buffer)
                {
                    if(0U == buffer)
                    {
                        DEBUG_PRINTF("\n\n  SUCCESS: Read Level of %s is LOW", DIO_CHANNEL_1_REAL_PIN_NAME);
                    }
                    else if(1U == buffer)
                    {
                        DEBUG_PRINTF("\n\n  SUCCESS: Read Level of %s is HIGH", DIO_CHANNEL_1_REAL_PIN_NAME);
                    }
                    else
                    {
                        /* */
                    }
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: Not get %s level.", DIO_CHANNEL_1_REAL_PIN_NAME);
                }
                break;
            }
            case 2:
            {
                DEBUG_PRINTF("\nCommand:2");
                /* Set the start level is low */
                Dio_WriteChannel(DioConf_DioChannel_DIO_TEST_OUT2, STD_LOW);
                /* Call the interface to pull the high level signal */
                Dio_WriteChannel(DioConf_DioChannel_DIO_TEST_OUT2, STD_HIGH);
                if(0U != Dio_ReadChannel(DioConf_DioChannel_DIO_TEST_OUT2))
                {
                    DEBUG_PRINTF("\n\n SUCCESS: %s level is HIGH.", DIO_CHANNEL_1_REAL_PIN_NAME);
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: %s level is LOW.", DIO_CHANNEL_1_REAL_PIN_NAME);
                }
                break;
            }
            case 3:
            {
                DEBUG_PRINTF("\nCommand:3");
                /* Set the start level is high */
                Dio_WriteChannel(DioConf_DioChannel_DIO_TEST_OUT2, STD_HIGH);
                /* Call the interface to pull the low level signal */
                Dio_WriteChannel(DioConf_DioChannel_DIO_TEST_OUT2, STD_LOW);
                if(0U == Dio_ReadChannel(DioConf_DioChannel_DIO_TEST_OUT2))
                {
                    DEBUG_PRINTF("\n\n SUCCESS: %s level is LOW.", DIO_CHANNEL_1_REAL_PIN_NAME);
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: %s level is HIGH.", DIO_CHANNEL_1_REAL_PIN_NAME);
                }
                break;
            }
            case 4:
            {
                DEBUG_PRINTF("\nCommand:4");
                buffer = Dio_ReadChannel(DioConf_DioChannel_DIO_TEST_OUT2);
                (void)Dio_FlipChannel(DioConf_DioChannel_DIO_TEST_OUT2);
                if (buffer != Dio_ReadChannel(DioConf_DioChannel_DIO_TEST_OUT2))
                {
                    DEBUG_PRINTF("\n\n SUCCESS: Flip the level of %s.", DIO_CHANNEL_1_REAL_PIN_NAME);

                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: Flip the level of %s.", DIO_CHANNEL_1_REAL_PIN_NAME);
                }
                break;
            }
            case 5:
            {
                DEBUG_PRINTF("\nCommand:5");
                buffer = Dio_ReadChannelGroup(DioConf_DioChannelGroup_DIO_GROUP_TEST_OUT);
                if(0xFFFF != buffer)
                {
                    DEBUG_PRINTF("\n\n SUCCESS: Level of %s are 0x%x.",DIO_GROUP_1_REAL_PIN_NAME, buffer);
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: Not get %s Group level.", DIO_GROUP_1_REAL_PIN_NAME);
                }
                break;
            }
            case 6:
            {
                DEBUG_PRINTF("\nCommand:6");
                (void)Dio_WriteChannelGroup(DioConf_DioChannelGroup_DIO_GROUP_TEST_OUT, 0x0003);
                buffer = Dio_ReadChannelGroup(DioConf_DioChannelGroup_DIO_GROUP_TEST_OUT);
                if (0x0003 == buffer)
                {
                    DEBUG_PRINTF("\n\n SUCCESS: sets the level of %s to 0x0003(11b).", DIO_GROUP_1_REAL_PIN_NAME);
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: sets the level of %s to 0x0003(Real Level is 0x%x).", DIO_GROUP_1_REAL_PIN_NAME, buffer);
                }
                break;
            }
            case 7:
            {
                DEBUG_PRINTF("\nCommand:7");
                buffer = Dio_ReadPort(DioConf_DioPort_DioPort_1);
                if(0xFFFF != buffer)
                {
                    DEBUG_PRINTF("\n\n SUCCESS: Level of Port1 is 0x%x.", buffer);
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: Not get Port1 level.");
                }
                break;
            }
            case 8:
            {
                DEBUG_PRINTF("\nCommand:8");
                (void)Dio_WritePort(DioConf_DioPort_DioPort_1, (Dio_PortLevelType)0x90);
                buffer = Dio_ReadPort(DioConf_DioPort_DioPort_1);
                if(0xFFFF != buffer)
                {
                    DEBUG_PRINTF("\n\n SUCCESS: sets the level of Port1 to 0x90(10010000b)");
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: sets the level of Port1 to 0x90(Real Level is 0x%x).", buffer);
                }
                break;
            }
            case 9:
            {
                DEBUG_PRINTF("\nCommand:9");
                buffer = Dio_ReadChannel(DioConf_DioChannel_DIO_TEST_IN1);
                if(0xFFFF != buffer)
                {
                    if(0U == buffer)
                    {
                        DEBUG_PRINTF("\n\n  SUCCESS: Read Level of P14.6 is LOW");
                    }
                    else if(1U == buffer)
                    {
                        DEBUG_PRINTF("\n\n  SUCCESS: Read Level of P14.6 is HIGH");
                    }
                    else
                    {
                        /* */
                    }
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: Not get P14.6 level.");
                }
                break;
            }
            case 10:
            {
                DEBUG_PRINTF("\nCommand:a");
                buffer = Dio_ReadChannelGroup(DioConf_DioChannelGroup_DIO_GROUP_TEST_IN);
                if(0xFFFF != buffer)
                {
                    DEBUG_PRINTF("\n\n SUCCESS: Level of P14.6-P14.8 are 0x%x.", buffer);
                }
                else
                {
                    DEBUG_PRINTF("\n\n FAIL: Not get P14.6-P14.8 Group level.");
                }
                break;
            }
            default:
            {
                break;
            }
        }
        if (0xFFU != DioCoreExeFlag.CoreExeCmd)
        {
            DioCoreExeFlag.CoreExeCmd = 0xFFU;
            /* Clear it to wait next command */
            DioCoreExeFlag.CoreCmdExist = 0U;
        }
    }
}

/****************************************************************************************************
*   Function Name           : Dio_DemoSelect
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
static void Dio_DemoSelect(void)
{
    uint8 cmd = 0;
    uint8 Exit = 0;
    Std_VersionInfoType VersionInfo;

    while (0U == Exit)
    {
        Dio_GetVersionInfo(&VersionInfo);
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                      DIO DRIVER DEMO MENU                         ");
        DEBUG_PRINTF("\n                       DIO Version V%d.%d.%d                       ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  Dio demo present with %s, P1.0-p1.15, set to output. ", DIO_GROUP_1_REAL_PIN_NAME);
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Output: Read level from %s. ", DIO_GROUP_1_REAL_PIN_NAME);
        DEBUG_PRINTF("\n  <2> : Output: Write HIGH level to %s. ", DIO_GROUP_1_REAL_PIN_NAME);
        DEBUG_PRINTF("\n  <3> : Output: Write Low level to %s. ", DIO_GROUP_1_REAL_PIN_NAME);
        DEBUG_PRINTF("\n  <4> : Output: Flip level for %s. ", DIO_GROUP_1_REAL_PIN_NAME);
        DEBUG_PRINTF("\n  <5> : Output: Read level from ChannelGroup(%s). ", DIO_GROUP_1_REAL_PIN_NAME);
        DEBUG_PRINTF("\n  <6> : Output: Write 0x0003(11b) to ChannelGroup(%s). ", DIO_GROUP_1_REAL_PIN_NAME);
        DEBUG_PRINTF("\n  <7> : Output: Read level from Port1. ");
        DEBUG_PRINTF("\n  <8> : Output: Write 0x90(10010000b) to Port1. ");
        DEBUG_PRINTF("\n  <9> : Input:  Read level from P14.6. ");
        DEBUG_PRINTF("\n  <a> : Input:  Read level from ChannelGroup(P14.6-P14.8). ");
        DEBUG_PRINTF("\n  <X> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        cmd = DEBUG_GETC();

        if (((cmd >= 0x31U) && (cmd <= 0x39U)) || (cmd == 0x61U))    /* ASCII '1'-'9','a' */
        {
            if (cmd == 0x61U)
            {
                DioCoreExeFlag.CoreExeCmd = 10U;
            }
            else
            {
                /* Convert the command character to number */
                DioCoreExeFlag.CoreExeCmd = (cmd - 0x30U);
            }
            /* Set it to inform the Core to running the demo
             * It must be here */
            DioCoreExeFlag.CoreCmdExist = 1U;
            /* Call Dio_Demo direct in Core 0 */
            Dio_Demo();
            while(0xFFU != DioCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Dio demo test finished */
            }
        }
        else if (((char)cmd == 'x') || ((char)cmd == 'X'))
        {
            Exit = 1U;
            DioCoreExeFlag.CoreExeCmd = 0xFFU;
        }
        else
        {
            DEBUG_PRINTF("\n\n  INVALID OPTION");
        }
    }
}

/****************************************************************************************************
*   Function Name           : Dio_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Dio demo application entry.
*                             Select which core to use to run Dio demo.
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
void Dio_DemoEntry(void)
{
    uint8               cmd  = 0;
    volatile uint8      exit = 0;
    Std_VersionInfoType VersionInfo;

    while (exit == 0U)
    {
        Dio_GetVersionInfo(&VersionInfo);
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                     Dio DRIVER DEMO MENU                          ");
        DEBUG_PRINTF("\n                      Dio Version V%d.%d.%d                        ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Run Dio Demo in Core0. ");
#if (MCAL_CFG_ENABLE_CORE1 == STD_ON)
        DEBUG_PRINTF("\n  <2> : Run Dio Demo in Core1. ");
#endif /* ((MCAL_USED_CORE_MASK&MCAL_CORE1) == MCAL_CORE1) */
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        cmd = DEBUG_GETC();

        switch ((char)cmd)
        {
            case '1':
            {
                /* Demo for Core0 */
                Dio_DemoCoreSelFlg = MCAL_CORE0;
                DEBUG_PRINTF("\n  Choose the Core0 to running demo. \n");
                Dio_DemoSelect();
                break;
            }
            case '2':
            {
                /* Demo for Core1 */
                Dio_DemoCoreSelFlg = MCAL_CORE1;
                DEBUG_PRINTF("\n  Choose the Core1 to running demo. \n");
                Dio_DemoSelect();
                break;
            }
            case 'x':
            {
                exit = 1U;
                break;
            }
            case 'X':
            {
                exit = 1U;
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
#define DIO_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dio_MemMap.h"

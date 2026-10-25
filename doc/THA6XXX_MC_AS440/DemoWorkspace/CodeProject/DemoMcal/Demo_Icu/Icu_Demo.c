/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Icu_Demo.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : TIM
 *
 *   brief                 : This file contains Demo application for Icu Driver
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

#include "Icu_Demo.h"
#include "Demo_Common.h"
#include "Demo_TestTime.h"
#include "Icu.h"
#include "Icu_GeneralTypes.h"
#include "Icu_Version.h"


#ifdef __DEBUG_CHIP__
#include "Uart_Demo.h"
#endif
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
#define ICU_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Icu_MemMap.h"

static Icu_EdgeNumberType Nums[3];
static volatile uint32    Icu_NotificationNumber0;
static volatile uint32    Icu_NotificationNumber1;
static volatile uint32    Icu_NotificationNumber2;
static Icu_DutyCycleType  GddDutyCycleValues[2];
static Icu_ValueType      GusTimestamp[10];
static Icu_InputStateType States;
static uint8              Icu_DemoCoreSelFlg;
static CoreExeType        IcuCoreExeFlag;
static uint8              Icu_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES];
#define ICU_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Icu_MemMap.h"
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
#define ICU_START_SEC_CODE_ASIL_D_GLOBAL
#include "Icu_MemMap.h"

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
 *   Function Name           : Icu_FlexICU_Demo
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo API for ICU driver.
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
 *   Preconditions           : ICU_Driver must be uninitialized.
 *
 ****************************************************************************************************/

void Icu_SingalMeasurement(void)
{
    Mcal_CoreType CoreId;
    uint32        OffSet;
    CoreId = Mcal_GetCoreId();
    OffSet = CoreId << 2U;

    GddDutyCycleValues[0].ActiveTime = 0;
    GddDutyCycleValues[1].PeriodTime = 0;
    /*PWM measurement*/
    Timer_DelayMs(10);

    Icu_StartSignalMeasurement(OffSet + IcuConf_IcuChannel_IcuChannel_0);
    Timer_DelayMs(100);

    States = Icu_GetInputState(OffSet + IcuConf_IcuChannel_IcuChannel_0);

    Icu_GetDutyCycleValues(OffSet + IcuConf_IcuChannel_IcuChannel_0, &GddDutyCycleValues[0]);
    Timer_DelayMs(10);

    Timer_DelayMs(100);
    Icu_GetDutyCycleValues(OffSet + IcuConf_IcuChannel_IcuChannel_0, &GddDutyCycleValues[1]);
    Timer_DelayMs(10);
    Icu_StopSignalMeasurement(OffSet + IcuConf_IcuChannel_IcuChannel_0);
    Timer_DelayMs(10);
    DEBUG_PRINTF("\n\n");

    if (GddDutyCycleValues[0].ActiveTime != 0 && GddDutyCycleValues[1].PeriodTime != 0)
    {
        DEBUG_PRINTF("Result = Pass;");
    }
    else
    {
        DEBUG_PRINTF("Result = fail;");
    }
    DEBUG_PRINTF("\n\n");
}

void Icu_TimeStamp(void)    
{
    Mcal_CoreType CoreId;
    uint32        OffSet;
    CoreId = Mcal_GetCoreId();
    OffSet = CoreId << 2U;
    /*TimeStamping*/
    Timer_DelayMs(10);

    Icu_SetActivationCondition(
        OffSet + IcuConf_IcuChannel_IcuChannel_3,
        ICU_BOTH_EDGES);  
    Icu_EnableNotification(OffSet + IcuConf_IcuChannel_IcuChannel_3);
    Icu_StartTimestamp(OffSet + IcuConf_IcuChannel_IcuChannel_3, &GusTimestamp[0], 10, 5);
    Timer_DelayMs(20);
    DEBUG_PRINTF(
        "GusTimestamp[0] = %lu,GusTimestamp[1] = %lu,GusTimestamp[2]=%lu\n",
        GusTimestamp[0],
        GusTimestamp[1],
        GusTimestamp[2]);

    Icu_SetActivationCondition(
        OffSet + IcuConf_IcuChannel_IcuChannel_3,
        ICU_FALLING_EDGE);  
    Icu_StartTimestamp(OffSet + IcuConf_IcuChannel_IcuChannel_3, &GusTimestamp[0], 10, 5);
    Timer_DelayMs(20);

    Icu_SetActivationCondition(
        OffSet + IcuConf_IcuChannel_IcuChannel_3,
        ICU_RISING_EDGE);    
    Icu_StartTimestamp(OffSet + IcuConf_IcuChannel_IcuChannel_3, &GusTimestamp[0], 10, 5);
    Timer_DelayMs(20);
    Icu_StopTimestamp(OffSet + IcuConf_IcuChannel_IcuChannel_3);
    Icu_DisableNotification(OffSet + IcuConf_IcuChannel_IcuChannel_3);

    DEBUG_PRINTF("\n\n");
    if (GusTimestamp[0] != 0)
    {
        if (Icu_NotificationNumber0 != 0)
        {
            DEBUG_PRINTF("Result = Pass;");
            Icu_NotificationNumber0 = 0;
        }
        else
        {
            DEBUG_PRINTF("Result = Fail;");
        }
    }
    else
    {
        DEBUG_PRINTF("Result = Fail;");
    }
    DEBUG_PRINTF("\n\n");
}

void Icu_SignalDetect(void)  
{
    Mcal_CoreType CoreId;
    uint32        OffSet;
    uint32 EdgeNum1,EdgeNumForMultiEdge;
    CoreId = Mcal_GetCoreId();
    OffSet = CoreId << 2U;
    Timer_DelayMs(10);
    Icu_NotificationNumber1 = 0;

    States = Icu_GetInputState(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    Icu_SetActivationCondition(OffSet + IcuConf_IcuChannel_IcuChannel_1, ICU_RISING_EDGE);
    Icu_EnableNotification(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    Icu_EnableEdgeDetection(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    Timer_DelayMs(10);
    States = Icu_GetInputState(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    (void)States;
    Timer_DelayMs(1);
    Icu_DisableEdgeDetection(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    Icu_DisableNotification(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    EdgeNum1 = Icu_NotificationNumber1;
    Icu_NotificationNumber1 = 0;



    States = Icu_GetInputState(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    Icu_SetActivationCondition(OffSet + IcuConf_IcuChannel_IcuChannel_1, ICU_RISING_EDGE);
    Icu_EnableNotification(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    Icu_EnableMultiEdgeDetection(OffSet + IcuConf_IcuChannel_IcuChannel_1,10);
    Timer_DelayMs(10);
    States = Icu_GetInputState(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    (void)States;
    Timer_DelayMs(1);
    Icu_DisableEdgeDetection(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    Icu_DisableNotification(OffSet + IcuConf_IcuChannel_IcuChannel_1);
    EdgeNumForMultiEdge = Icu_NotificationNumber1;

    if (((EdgeNumForMultiEdge * 10U) <= EdgeNum1)
            && (((EdgeNumForMultiEdge + 1U) * 10U) > EdgeNum1)
            && (EdgeNum1 > 0U))
    {
        DEBUG_PRINTF("\n\n");
        DEBUG_PRINTF("Result = Pass;");
        DEBUG_PRINTF("\n\n");
        Icu_NotificationNumber1 = 0;
    }
    else
    {
        DEBUG_PRINTF("\n\n");
        DEBUG_PRINTF("Result = Fail;");
        DEBUG_PRINTF("\n\n");
    }
}

void Icu_EdgeCounter(void)
{
    Mcal_CoreType CoreId;
    uint32        OffSet;
    CoreId = Mcal_GetCoreId();
    OffSet = CoreId << 2U;
    Timer_DelayMs(10);
#if defined(THA6_THA6104)
    OffSet = 2;/*use channel 4 to test counter*/
#endif
    /* short time */
    Icu_SetActivationCondition(OffSet + IcuConf_IcuChannel_IcuChannel_2, ICU_RISING_EDGE);
    Icu_EnableEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);
    Timer_DelayMs(1);
    Timer_DelayMs(5);
    Nums[0] = Icu_GetEdgeNumbers(OffSet + IcuConf_IcuChannel_IcuChannel_2);
    Icu_DisableEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);

    /* long time */
    Timer_DelayMs(5);

    Icu_SetActivationCondition(OffSet + IcuConf_IcuChannel_IcuChannel_2, ICU_RISING_EDGE);
    Icu_EnableEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);
    Icu_ResetEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);

    Timer_DelayMs(15);
    Timer_DelayMs(5);

    Nums[1] = Icu_GetEdgeNumbers(OffSet + IcuConf_IcuChannel_IcuChannel_2);
    Icu_DisableEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);

    /* falling */
    Icu_SetActivationCondition(OffSet + IcuConf_IcuChannel_IcuChannel_2, ICU_FALLING_EDGE);
    Icu_EnableEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);
    Icu_ResetEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);

    Timer_DelayMs(5);
    Timer_DelayMs(5);

    Nums[2] = Icu_GetEdgeNumbers(OffSet + IcuConf_IcuChannel_IcuChannel_2);
    Icu_DisableEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);

    /* long time */
    Icu_ResetEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);
    Icu_SetActivationCondition(OffSet + IcuConf_IcuChannel_IcuChannel_2, ICU_FALLING_EDGE);
    Icu_EnableEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);

    Timer_DelayMs(15);
    Timer_DelayMs(5);

    Nums[0] = Icu_GetEdgeNumbers(OffSet + IcuConf_IcuChannel_IcuChannel_2);
    Icu_ResetEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);
    Icu_DisableEdgeCount(OffSet + IcuConf_IcuChannel_IcuChannel_2);

    if ((Nums[0] != 0) && (Nums[1] != 0) && (Nums[2] != 0))
    {
        DEBUG_PRINTF("\n\n");
        DEBUG_PRINTF("Result = Pass;");
        DEBUG_PRINTF("\n\n");
        Nums[0] = 0;
        Nums[1] = 0;
        Nums[2] = 0;
    }
    else
    {
        DEBUG_PRINTF("\n\n");
        DEBUG_PRINTF("Result = Fail;");
        DEBUG_PRINTF("\n\n");
    }
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/

void Icu_SignalNotification_1(void)
{
    Icu_NotificationNumber1++;
}

void Icu_SignalNotification_5(void)
{
    Icu_NotificationNumber1++;
}

void Icu_TimerOverflowNotification_2(void)
{
    Icu_NotificationNumber2++;
}

void Icu_TimestampNotification_3(void)
{
    Icu_NotificationNumber0++;
}

void Icu_TimestampNotification_7(void)
{
    Icu_NotificationNumber0++;
}

/****************************************************************************************************
 *   Function Name           : Icu_Demo
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo API for Icu driver.
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
 *   Preconditions           : Icu_Driver must be uninitialized.
 *
 ****************************************************************************************************/

void Icu_Demo(void)
{
    Mcal_CoreType CoreId;
    CoreId = Mcal_GetCoreId();
    if ((Icu_DemoCoreSelFlg == CoreId) && (IcuCoreExeFlag.CoreCmdExist == 1U))
    {
        switch (IcuCoreExeFlag.CoreExeCmd)
        {
        case '1':
        {
            DEBUG_PRINTF("1\n");
            Icu_SingalMeasurement();
            break;
        }
        case '2':
        {
            DEBUG_PRINTF("2\n");

            Icu_TimeStamp();
            break;
        }
        case '3':
        {
            DEBUG_PRINTF("3\n");

            Icu_SignalDetect();
            break;
        }
        case '4':
        {
            DEBUG_PRINTF("4\n");

            Icu_EdgeCounter();
            break;
        }

        default:
        {
            break;
        }
        }
        if (0xFFU != IcuCoreExeFlag.CoreExeCmd)
        {
            IcuCoreExeFlag.CoreExeCmd = 0xFFU;
        }
    }
    if (1U == Icu_DemoCoreInitStatus[CoreId])
    {
        /* Initialize and each core needs to be initialized once */
        Icu_DemoCoreInitStatus[CoreId] = 2U;
        if (CoreId != 0U)
        {
            Icu_Init(&Icu_ConfigSet[0]);
        }
    }
    else if (3U == Icu_DemoCoreInitStatus[CoreId])
    {
        Icu_DemoCoreInitStatus[CoreId] = 0U;
        Icu_DeInit();
    }

} /* Icu_Demo() */

/****************************************************************************************************
 *   Function Name           : Icu_DemoSelect
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
static void Icu_DemoSelect(void)
{
    uint8               cmd;
    uint8               Icu_exit;
    Std_VersionInfoType Icu_ver;

    Icu_exit = 0U;
    while (0U == Icu_exit)
    {
        Icu_GetVersionInfo(&Icu_ver);
        DEBUG_PRINTF((const uint8 *)"\n\n\n");
        DEBUG_PRINTF((const uint8 *)"\n/*********************************************************/");
        DEBUG_PRINTF(
            (const uint8 *)"\n           ICU DRIVER DEMO MENU V%02d.%02d.%02d            ",
            Icu_ver.sw_major_version,
            Icu_ver.sw_minor_version,
            Icu_ver.sw_patch_version);
        DEBUG_PRINTF((const uint8 *)"\n                                                         ");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF((const char *)"\n\n\n");
        DEBUG_PRINTF("\n                                                         ");

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
        DEBUG_PRINTF("\n < >: ..................PWM OUT:P32_4 .............");
        DEBUG_PRINTF("\n <1>:  ICU_MODE_SIGNAL_MEASUREMENT P00_9(Core0) P10_1(Core1) ");
        DEBUG_PRINTF("\n <2>:  ICU_MODE_TIMESTAMP P00_0(Core0) P10_0(Core1)");
        DEBUG_PRINTF("\n <3>: ICU_MODE_SIGNAL_EDGE_DETECT P0.2(Core0) P10_2(Core1)");
        DEBUG_PRINTF("\n <4>: ICU_MODE_EDGE_COUNTER  P10_8(Core0) P10_3(Core1)");
#endif


#if defined(THA6_THA6104)
        DEBUG_PRINTF("\n < >: ..................PWM OUT:P23_1 .............");
        DEBUG_PRINTF("\n <1>:  ICU_MODE_SIGNAL_MEASUREMENT P00_9(Core0)  ");
        DEBUG_PRINTF("\n <2>:  ICU_MODE_TIMESTAMP P14_4(Core0) ");
        DEBUG_PRINTF("\n <3>: ICU_MODE_SIGNAL_EDGE_DETECT P22.1(Core0)");
        DEBUG_PRINTF("\n <4>: ICU_MODE_EDGE_COUNTER  P00_9(Core0) ");
#endif


        DEBUG_PRINTF("\n <x>: exit");
        DEBUG_PRINTF("\nEnter option Number: ");

        cmd = DEBUG_GETC();

        {
            /* Convert the command character to number */
            IcuCoreExeFlag.CoreExeCmd = (cmd);  
            /* Set it to inform the Core to running the demo
             * It must be here */
            IcuCoreExeFlag.CoreCmdExist = 1U;
            /* Delay for init of other core  */
            Timer_DelayMs(100);

            /* Call Icu_Demo direct in Core 0 */
            Icu_Demo();

            while (0xFFU != IcuCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Icu demo test finished */
            }
            /* Clear it to wait next command */
            IcuCoreExeFlag.CoreCmdExist = 0U;
        }
        if (((char)cmd == 'x') || ((char)cmd == 'X'))
        {
            Icu_exit = 1U;
            IcuCoreExeFlag.CoreExeCmd = 0xFFU;
        }
        else
        {
            /* Do Nothing */
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Icu_DemoEntry
 *
 *   Service ID              : None.
 *
 *   Description             : Icu demo application entry.
 *                             Select which core to use to run Icu Channel.
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
void Icu_DemoEntry(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();
    if (0U == Icu_DemoCoreInitStatus[CoreId])
    {
        /* Initialize and each core needs to be initialized once */
        Icu_DemoCoreInitStatus[1] = 1U;

        Icu_Init(&Icu_ConfigSet[0]);
    }
#if (MCAL_USED_CORE_MASK != MCAL_CORE0_MASK)
    uint8         cmd;
    uint8         Icu_exit;
    Icu_exit = 0U;

    while (0U == Icu_exit)
    {
        DEBUG_PRINTF("\n/*********************************************************/\n");
        DEBUG_PRINTF(
            "\n              ICU DRIVER DEMO MENU V%d.%d.%d                    ",
            ICU_SW_MAJOR_VERSION,
            ICU_SW_MINOR_VERSION,
            ICU_SW_PATCH_VERSION);
        DEBUG_PRINTF((const uint8 *)"\n                                                         ");
        DEBUG_PRINTF((const uint8 *)"\n  <1> : Icu Demo in Core0. ");
#if ((MCAL_USED_CORE_MASK & MCAL_CORE1_MASK) == MCAL_CORE1_MASK)
        DEBUG_PRINTF((const uint8 *)"\n  <2> : Icu Demo in Core1. ");
#endif /* ((MCAL_USED_CORE_MASK&MCAL_CORE1_MASK) == MCAL_CORE1_MASK) */

        DEBUG_PRINTF((const uint8 *)"\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF((const uint8 *)"\n  ENTER YOUR OPTION   : ");

        cmd = DEBUG_GETC();

        switch ((char)cmd)
        {
            case '1':
            {
                /* Demo for Core0 */
                Icu_DemoCoreSelFlg = MCAL_CORE0;
                DEBUG_PRINTF((const uint8 *)"\n  Choose the Core0\n");
                Icu_DemoSelect();
                break;
            }
#if ((MCAL_USED_CORE_MASK & MCAL_CORE1_MASK) == MCAL_CORE1_MASK)
            case '2':
            {
                /* Demo for Core1 */
                Icu_DemoCoreSelFlg = MCAL_CORE1;
                DEBUG_PRINTF((const uint8 *)"\n  Choose the Core1\n");
                Icu_DemoSelect();
                break;
            }
#endif /* ((MCAL_USED_CORE_MASK&MCAL_CORE1_MASK) == MCAL_CORE1_MASK) */
            case 'x':
            case 'X':
            {
                Icu_exit = 1U;
                Icu_DeInit();
                Icu_DemoCoreInitStatus[0] = 0U;
                Icu_DemoCoreInitStatus[1] = 3U;
                break;
            }
            default:
            {
                DEBUG_PRINTF("\n\n  INVALID OPTION");
                break;
            }
        }
    }
#else
    Icu_DemoCoreSelFlg = MCAL_CORE0;
    Icu_DemoSelect();
#endif
}

#define ICU_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Icu_MemMap.h"

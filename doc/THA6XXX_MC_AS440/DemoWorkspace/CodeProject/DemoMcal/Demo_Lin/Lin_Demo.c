/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Lin_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
*
*   brief                 : This file contains Demo application for Lin Driver
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

#include "Lin_Demo.h"
#include "Mcall.h"
#include "Intc.h"
#include "Intc_Cfg.h"
#include "Demo_Common.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* Get LIN channel status timeout threshold.
 * When Buadrate is 20K, send a frame need 34*TBit + 10*(NData + 1)*TBit
 *                                      = 34*50us + 10*9*50us = 6200us
 * So set threshold as 20ms for hold status.
 * */
#define LIN_DEMO_WAIT_MS_THD                (20U)    /* unit: ms */

typedef volatile struct
{
    uint8 CoreCmdExist;    /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} Lin_ChannelCoreExeType;


/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Lin_MemMap.h"
static uint8 Lin_DemoInitStatusCore0 = 0U;
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "Lin_MemMap.h"

#define LIN_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Lin_MemMap.h"
static uint8 Lin_DemoInitStatusCore1 = 0U;
#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "Lin_MemMap.h"

#define LIN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"

static uint8 Lin_DemoCoreSelFlg = MCAL_CORE0;

#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"

#define LIN_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"

static Lin_ChannelCoreExeType LinCoreExeFlag = {0, 0xFFU};

static uint8 Lin_UserData[8] = {0x55, 0xAA, 0x11, 0x88, 0xA5, 0xA8, 0xFF, 0x00};

static Lin_PduType Lin_UserPduMasterResponse =
{
    .Pid = 0xF5,    /* ID:0x35 */
    .Cs = LIN_ENHANCED_CS,
    .Dl = 8,
    .Drc = LIN_FRAMERESPONSE_TX,
    .SduPtr = Lin_UserData
};

static Lin_PduType Lin_UserPduMasterRequest =
{
    .Pid = 0x20,    /* ID: 0x20 */
    .Cs = LIN_ENHANCED_CS,
    .Dl = 8,
    .Drc = LIN_FRAMERESPONSE_RX,
    .SduPtr = Lin_UserData
};

static Lin_PduType Lin_UserPduSalveToSalve =
{
    .Pid = 0x2E,    /* 0x2E */
    .Cs = LIN_ENHANCED_CS,
    .Dl = 8,
    .Drc = LIN_FRAMERESPONSE_IGNORE,
    .SduPtr = Lin_UserData
};

#define LIN_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"

#define LIN_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"

uint8 *Lin_SlaveSduPtr;

uint8 Lin_ResponseStatus;

#define LIN_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Lin_MemMap.h"

#define LIN_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Lin_MemMap.h"

/* Used LIN channel in Demo */
static const uint8 Lin_CorexChanneMap[MCAL_NUMBER_OF_CORES] =
{
    /* Core0 */
    LinConf_LinChannel_Lin_TestChannel_0,
    /* Core1 */
    LinConf_LinChannel_Lin_TestChannel_1
};

static uint8 * const Lin_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES] =
{
    &Lin_DemoInitStatusCore0,
    &Lin_DemoInitStatusCore1
};

#define LIN_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Lin_MemMap.h"
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
#define LIN_START_SEC_CODE_ASIL_D_GLOBAL
#include "Lin_MemMap.h"

static void Lin_SendFrameMasterResponse(void);
static void Lin_SendFrameSlaveResponse(void);
static void Lin_SendFrameSlaveToSlaveResponse(void);
static void Lin_GoToSleepDemo(void);
static void Lin_GoToSleepInternalDemo(void);
static void Lin_WakeupDemo(void);
static void Lin_WakeupInternalDemo(void);
static void Lin_SlaveReceiveDemo(void);
static void Lin_SlaveTransmitDemo(void);
static void Lin_SlaveIgnoreDemo(void);
static void Lin_DemoSelect(void);


/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Lin_SendFrameMasterResponse
*
*   Service ID              : None.
*
*   Description             : Control LIN channel Send a frame with response to slave.
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
static void Lin_SendFrameMasterResponse(void)
{
    uint32 waitLoop;
    Lin_StatusType RetStatus;
    Mcal_CoreType  CoreId;

    CoreId = Mcal_GetCoreId();
    (void)Lin_SendFrame(Lin_CorexChanneMap[CoreId], &Lin_UserPduMasterResponse);

    /* Waiting until send data */
    for (waitLoop = 0; waitLoop < LIN_DEMO_WAIT_MS_THD; waitLoop++)
    {
        RetStatus = Lin_GetStatus(Lin_CorexChanneMap[CoreId], (uint8**)&Lin_SlaveSduPtr);
        Timer_DelayMs(1U);    /* Waiting 1ms */
        if (LIN_TX_OK == RetStatus)
        {
            break;
        }
    }

    if (LIN_TX_OK == RetStatus)
    {
        DEBUG_PRINTF("\nLin channel frame header and response send SUCCESS!");
    }
    else
    {
        DEBUG_PRINTF("\nLin channel frame header and response send FAILED!");
    }
}

/****************************************************************************************************
*   Function Name           : Lin_SendFrameSlaveResponse
*
*   Service ID              : None.
*
*   Description             : Control LIN channel Send a frame and need slave response back.
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
static void Lin_SendFrameSlaveResponse(void)
{
    uint32 waitLoop;
    Lin_StatusType RetStatus;
    uint8 i;
    Mcal_CoreType  CoreId;

    CoreId = Mcal_GetCoreId();
    (void)Lin_SendFrame(Lin_CorexChanneMap[CoreId], &Lin_UserPduMasterRequest);

    /* Waiting until received data */
    for (waitLoop = 0; waitLoop < LIN_DEMO_WAIT_MS_THD; waitLoop++)
    {
        RetStatus = Lin_GetStatus(Lin_CorexChanneMap[CoreId], (uint8**)&Lin_SlaveSduPtr);
        Timer_DelayMs(1U);    /* Waiting 1ms */
        if (LIN_RX_OK == RetStatus)
        {
            break;
        }
    }

    if (LIN_RX_OK == RetStatus)
    {
        DEBUG_PRINTF("\nLin channel frame header send SUCCESS!");
        DEBUG_PRINTF("\nReceived Data from Slave ID 0x20:");
        for (i = 0U; i < 8U; i++)
        {
            DEBUG_PRINTF("0x%02x ", Lin_SlaveSduPtr[i]);
        }

    }
    else
    {
        DEBUG_PRINTF("\nLin channel frame header and response send FAILED!");
    }
}

/****************************************************************************************************
*   Function Name           : Lin_SendFrameSlaveResponse
*
*   Service ID              : None.
*
*   Description             : Control LIN channel Send a frame and does not need slave response.
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
static void Lin_SendFrameSlaveToSlaveResponse(void)
{
    uint32 waitLoop;
    Lin_StatusType RetStatus;
    Mcal_CoreType  CoreId;

    CoreId = Mcal_GetCoreId();
    (void)Lin_SendFrame(Lin_CorexChanneMap[CoreId], &Lin_UserPduSalveToSalve);

    /* Waiting until received data */
    for (waitLoop = 0; waitLoop < LIN_DEMO_WAIT_MS_THD; waitLoop++)
    {
        RetStatus = Lin_GetStatus(Lin_CorexChanneMap[CoreId], (uint8**)&Lin_SlaveSduPtr);
        Timer_DelayMs(1U);    /* Waiting 1ms */
        if (LIN_TX_OK == RetStatus)
        {
            break;
        }
    }

    if (LIN_TX_OK == RetStatus)
    {
        DEBUG_PRINTF("\nLin channel frame header SUCCESS!");
    }
    else
    {
        DEBUG_PRINTF("\nLin channel frame header and response send FAILED!");
    }
}

/****************************************************************************************************
*   Function Name           : Lin_GoToSleepDemo
*
*   Service ID              : None.
*
*   Description             : Go to sleep demo.
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
static void Lin_GoToSleepDemo(void)
{
    uint32 waitLoop;
    Lin_StatusType RetStatus;
    Mcal_CoreType  CoreId;

    CoreId = Mcal_GetCoreId();
    (void)Lin_GoToSleep(Lin_CorexChanneMap[CoreId]);

    /* Waiting until received data */
    for (waitLoop = 0; waitLoop < LIN_DEMO_WAIT_MS_THD; waitLoop++)
    {
        RetStatus = Lin_GetStatus(Lin_CorexChanneMap[CoreId], (uint8**)&Lin_SlaveSduPtr);
        Timer_DelayMs(1U);    /* Waiting 1ms */
        if (LIN_CH_SLEEP == RetStatus)
        {
            break;
        }
    }

    if (LIN_CH_SLEEP == RetStatus)
    {
        DEBUG_PRINTF("\nLin channel go to sleep status SUCCESS!");
    }
    else
    {
        DEBUG_PRINTF("\nLin channel go to sleep status FAILED!");
    }
}

/****************************************************************************************************
*   Function Name           : Lin_GoToSleepInternalDemo
*
*   Service ID              : None.
*
*   Description             : Go to sleep internal demo.
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
static void Lin_GoToSleepInternalDemo(void)
{
    uint32 waitLoop;
    Lin_StatusType RetStatus;
    Mcal_CoreType  CoreId;

    CoreId = Mcal_GetCoreId();

    (void)Lin_GoToSleepInternal(Lin_CorexChanneMap[CoreId]);

    /* Waiting until received data */
    for (waitLoop = 0; waitLoop < LIN_DEMO_WAIT_MS_THD; waitLoop++)
    {
        RetStatus = Lin_GetStatus(Lin_CorexChanneMap[CoreId], (uint8**)&Lin_SlaveSduPtr);
        Timer_DelayMs(1U);    /* Waiting 1ms */
        if (LIN_CH_SLEEP == RetStatus)
        {
            break;
        }
    }

    if (LIN_CH_SLEEP == RetStatus)
    {
        DEBUG_PRINTF("\nLin channel go to sleep status SUCCESS!");
    }
    else
    {
        DEBUG_PRINTF("\nLin channel go to sleep status FAILED!");
    }
}

/****************************************************************************************************
*   Function Name           : Lin_WakeupDemo
*
*   Service ID              : None.
*
*   Description             : Wakeup demo.
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
static void Lin_WakeupDemo(void)
{
    uint32 waitLoop;
    Lin_StatusType RetStatus;
    Mcal_CoreType  CoreId;

    CoreId = Mcal_GetCoreId();

    (void)Lin_Wakeup(Lin_CorexChanneMap[CoreId]);

    /* Waiting until received data */
    for (waitLoop = 0; waitLoop < LIN_DEMO_WAIT_MS_THD; waitLoop++)
    {
        RetStatus = Lin_GetStatus(Lin_CorexChanneMap[CoreId], (uint8**)&Lin_SlaveSduPtr);
        Timer_DelayMs(1U);    /* Waiting 1ms */
        if (LIN_OPERATIONAL == RetStatus)
        {
            break;
        }
    }

    if (LIN_OPERATIONAL == RetStatus)
    {
        DEBUG_PRINTF("\nLin channel wakeup SUCCESS!");
    }
    else
    {
        DEBUG_PRINTF("\nLin channel wakeup FAILED!");
    }
}

/****************************************************************************************************
*   Function Name           : Lin_WakeupInternalDemo
*
*   Service ID              : None.
*
*   Description             : Wakeup internal demo.
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
static void Lin_WakeupInternalDemo(void)
{
    uint32 waitLoop;
    Lin_StatusType RetStatus;
    Mcal_CoreType  CoreId;

    CoreId = Mcal_GetCoreId();

    (void)Lin_WakeupInternal(Lin_CorexChanneMap[CoreId]);

    /* Waiting until received data */
    for (waitLoop = 0; waitLoop < LIN_DEMO_WAIT_MS_THD; waitLoop++)
    {
        RetStatus = Lin_GetStatus(Lin_CorexChanneMap[CoreId], (uint8**)&Lin_SlaveSduPtr);
        Timer_DelayMs(1U);    /* Waiting 1ms */
        if (LIN_OPERATIONAL == RetStatus)
        {
            break;
        }
    }

    if (LIN_OPERATIONAL == RetStatus)
    {
        DEBUG_PRINTF("\nLin channel wakeup SUCCESS!");
    }
    else
    {
        DEBUG_PRINTF("\nLin channel wakeup FAILED!");
    }
}

/****************************************************************************************************
*   Function Name           : Lin_SlaveReceiveDemo
*
*   Service ID              : None.
*
*   Description             : Slave receive response data.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Lin_SlaveReceiveDemo(void)
{
    uint8           i;
    uint32           Counter;

    /* Reset global variable */
    Lin_ResponseStatus = 0U;
    Counter = 1000U;

    while(((0U == Lin_ResponseStatus) || (LIN_HEADER_RECV == Lin_ResponseStatus)) && (Counter > 0U))
    {
        Counter--;
        Timer_DelayMs(10U);    /* Waiting 1ms */
    }

    if (LIN_RX_INDC == Lin_ResponseStatus)
    {
        DEBUG_PRINTF("\nSlave receive SUCCESS!");
        DEBUG_PRINTF("\nReceived Data from ID 0x20:");
        for (i = 0U; i < 8U; i++)
        {
            DEBUG_PRINTF("0x%02x ", Lin_SlaveSduPtr[i]);
        }

    }
    else
    {
        DEBUG_PRINTF("\nSlave response FAILED!");
    }
}

/****************************************************************************************************
*   Function Name           : Lin_SlaveTransmitDemo
*
*   Service ID              : None.
*
*   Description             : Slave transmit response data.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous
*
*   Reentrancy              : Non-Reentrant
*
*   Return value            : None
*
*   Preconditions           : None
*
****************************************************************************************************/
static void Lin_SlaveTransmitDemo(void)
{
    uint32           Counter;

    /* Reset global variable */
    Lin_ResponseStatus = 0U;
    Counter = 1000U;

    while(((0U == Lin_ResponseStatus) || (LIN_HEADER_RECV == Lin_ResponseStatus)) && (Counter > 0U))
    {
        Counter--;
        Timer_DelayMs(10U);    /* Waiting 1ms */
    }

    if (LIN_TX_INDC == Lin_ResponseStatus)
    {
        DEBUG_PRINTF("\nSlave transmit response SUCCESS!");
    }
    else
    {
        DEBUG_PRINTF("\nSlave transmit response FAILED!");
    }
}

/****************************************************************************************************
*   Function Name           : Lin_SlaveIgnoreDemo
*
*   Service ID              : None.
*
*   Description             : Wakeup internal demo.
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
static void Lin_SlaveIgnoreDemo(void)
{
    uint32           Counter;

    /* Reset global variable */
    Lin_ResponseStatus = 0U;
    Counter = 1000U;

    while((0U == Lin_ResponseStatus) && (Counter > 0U))
    {
        Counter--;
        Timer_DelayMs(10U);    /* Waiting 1ms */
    }

    if (LIN_HEADER_RECV == Lin_ResponseStatus)
    {
        DEBUG_PRINTF("\nSlave Ignore response SUCCESS!");
    }
    else
    {
        DEBUG_PRINTF("\nSlave Ignore response FAILED!");
    }
}
/****************************************************************************************************
*   Function Name           : Lin_DemoSelect
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
static void Lin_DemoSelect(void)
{
    uint8 Cmd;
    uint8 Exit;
    Std_VersionInfoType VersionInfo;

    Exit = 0U;
    while (0U == Exit)
    {
        Lin_GetVersionInfo(&VersionInfo);
        DEBUG_PRINTF((const uint8*)"\n\n\n");
        DEBUG_PRINTF((const uint8*)"\n/*********************************************************/");
        DEBUG_PRINTF((const uint8*)"\n           LIN DRIVER DEMO MENU V%02d.%02d.%02d            ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF((const uint8*)"\n                                                         ");
        if(MCAL_CORE0 == Lin_DemoCoreSelFlg)
        {
            DEBUG_PRINTF((const uint8*)"\n  <1> : Master response demo: Send frame header and response data(Slave ID: 0x35) in Core0. ");
            DEBUG_PRINTF((const uint8*)"\n  <2> : Slave response demo: Send frame header only and waiting back data from slave(Slave ID: 0x20) in Core0. ");
            DEBUG_PRINTF((const uint8*)"\n  <3> : Slave to Slave response demo: Send header only and not receive response data(Slave ID: 0x2E) in Core0. ");
            DEBUG_PRINTF((const uint8*)"\n  <4> : GoToSleep: Send a sleep signal to sleep the slave device in Core0. ");
            DEBUG_PRINTF((const uint8*)"\n  <5> : WakeUp:    Send a wakeup signal to wake up the slave device in Core0. ");
            DEBUG_PRINTF((const uint8*)"\n  <6> : GoToSleepInternal: enter low-power mode in Core0. ");
            DEBUG_PRINTF((const uint8*)"\n  <7> : WakeupInternal:    exit  low-power mode in Core0. ");
            DEBUG_PRINTF((const uint8*)"\n  <8> : Slave receive response demo: Slave receive frame header and response data in core0");
            DEBUG_PRINTF((const uint8*)"\n  <9> : Slave transmit response demo: Slave receive frame header and send response data in core0");
            DEBUG_PRINTF((const uint8*)"\n  <a> : Slave ignore frame demo: Slave ignore this frame in core0");
        }
        else
        {  
            DEBUG_PRINTF((const uint8*)"\n  <1> : Master response demo: Send frame header and response data(Slave ID: 0x35) in Core1. ");
            DEBUG_PRINTF((const uint8*)"\n  <2> : Slave response demo: Send frame header only and waiting back data from slave(Slave ID: 0x20) in Core1. ");
            DEBUG_PRINTF((const uint8*)"\n  <3> : Slave to Slave response demo: Send header only and not receive response data(Slave ID: 0x2E) in Core1. ");
            DEBUG_PRINTF((const uint8*)"\n  <4> : GoToSleep: Send a sleep signal to sleep the slave device in Core1. ");
            DEBUG_PRINTF((const uint8*)"\n  <5> : WakeUp:    Send a wakeup signal to wake up the slave device in Core1. ");
            DEBUG_PRINTF((const uint8*)"\n  <6> : GoToSleepInternal: enter low-power mode in Core1. ");
            DEBUG_PRINTF((const uint8*)"\n  <7> : WakeupInternal:    exit  low-power mode in Core1 ");
        }
        DEBUG_PRINTF((const uint8*)"\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF((const uint8*)"\n  ENTER YOUR OPTION   : ");
        /* Waiting till received a uart command character */
        Cmd = DEBUG_GETC();

        /* As for Lin Demo, valid command character range from 1 to a */
        if (((Cmd >= 0x31U) && (Cmd <= 0x39U)) || (Cmd == 0x61U))
        {
            if(Cmd == 0x61U)
            {
                LinCoreExeFlag.CoreExeCmd = 10U;
            }
            else
            {
                /* Convert the command character to number */
                LinCoreExeFlag.CoreExeCmd = (Cmd - 0x30U);
            }
            /* Set it to inform the Core to running the demo
             * It must be here */
            LinCoreExeFlag.CoreCmdExist = 1U;
            /* Call Lin_Demo direct in Core 0 */
            Lin_Demo();
            while(0xFFU != LinCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Lin demo test finished */
            }
        }
        else if (((char)Cmd == 'x') || ((char)Cmd == 'X'))
        {
            Exit = 1U;
            LinCoreExeFlag.CoreExeCmd = 0xFFU;
        }
        else
        {
            DEBUG_PRINTF("\n\n  INVALID OPTION");
        }
    }
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Lin_DemoEntry
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
void Lin_DemoEntry(void)
{
    uint8               Cmd  = 0U;
    uint8               Exit = 0U;
    Std_VersionInfoType VersionInfo;

    Exit = 0U;
    while (0U == Exit)
    {
        Lin_GetVersionInfo(&VersionInfo);
        DEBUG_PRINTF((const uint8*)"\n\n\n");
        DEBUG_PRINTF((const uint8*)"\n/*********************************************************/");
        DEBUG_PRINTF((const uint8*)"\n           LIN DRIVER DEMO MENU V%02d.%02d.%02d            ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF((const uint8*)"\n                                                         ");
        DEBUG_PRINTF((const uint8*)"\n  <1> : Lin Channel0 Demo in Core0. ");
#if (MCAL_CFG_ENABLE_CORE1 == STD_ON)
        DEBUG_PRINTF((const uint8*)"\n  <2> : Lin Channel1 Demo in Core1. ");
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
                Lin_DemoCoreSelFlg = MCAL_CORE0;
                DEBUG_PRINTF((const uint8*)"\n  Choose the Core0 to running demo, Master Lin channel0 - ASI2(10.5/10.6). \n");
                DEBUG_PRINTF((const uint8*)"\n  Choose the Core0 to running demo, Slave  Lin channel0 - ASI5(33.0/33.4). \n");
                Lin_DemoSelect();
                break;
            }
#if ((MCAL_USED_CORE_MASK&MCAL_CORE1_MASK) == MCAL_CORE1_MASK)
            case '2':
            {
                /* Demo for Core1 */
                Lin_DemoCoreSelFlg = MCAL_CORE1;
                DEBUG_PRINTF((const uint8*)"\n  Choose the Core1 to running demo, Lin channel1 - ASI3(20.0/20.3) \n");
                Lin_DemoSelect();
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

/****************************************************************************************************
*   Function Name           : Lin_Demo
*
*   Service ID              : None.
*
*   Description             : This API shall be called by core which need to driver Lin channel.
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
void Lin_Demo(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    if ((Lin_DemoCoreSelFlg == CoreId) && (1U == LinCoreExeFlag.CoreCmdExist))
    {
        if(0U == *Lin_DemoCoreInitStatus[CoreId])
        {
            /* Initialize and each core needs to be initialized once */
            *Lin_DemoCoreInitStatus[CoreId] = 1U;
            Lin_Init(&Lin_ConfigSet[0]);
            (void)Lin_WakeupInternal(Lin_CorexChanneMap[CoreId]);
            (void)Lin_WakeupInternal(LinConf_LinChannel_Lin_TestSlaveChannel_0);
#if (LIN_CFG_INTERRUPT_ENABLE == STD_ON)
            if(MCAL_CORE0 == CoreId)
            {
                /* ASI2 Rx and error interrupt for master */
                Intc_EnableInterrupt(641);
                Intc_EnableInterrupt(643);
                /* ASI5 Tx Rx error interrupt for slave */
                Intc_EnableInterrupt(656);
                Intc_EnableInterrupt(657);
                Intc_EnableInterrupt(658);
            }
            else
            {
                /* ASI3 Rx and error interrupt for master */
                Intc_EnableInterrupt(646);
                Intc_EnableInterrupt(648);
            }
#endif /* (LIN_CFG_INTERRUPT_ENABLE  \== STD_ON) */
        }

        switch (LinCoreExeFlag.CoreExeCmd)
        {
            case 1:
            {
                Lin_SendFrameMasterResponse();
                break;
            }
            case 2:
            {
                Lin_SendFrameSlaveResponse();
                break;
            }
            case 3:
            {
                Lin_SendFrameSlaveToSlaveResponse();
                break;
            }
            case 4:
            {
                Lin_GoToSleepDemo();
                break;
            }
            case 5:
            {
                Lin_WakeupDemo();
                break;
            }
            case 6:
            {
                Lin_GoToSleepInternalDemo();
                break;
            }
            case 7:
            {
                Lin_WakeupInternalDemo();
                break;
            }
            case 8:
            {
                Lin_SlaveReceiveDemo();
                break;
            }
            case 9:
            {
                Lin_SlaveTransmitDemo();
                break;
            }
            case 10:
            {
                Lin_SlaveIgnoreDemo();
                break;
            }
            default:
            {
                break;
            }
        }
        if (0xFFU != LinCoreExeFlag.CoreExeCmd)
        {
            LinCoreExeFlag.CoreExeCmd = 0xFFU;
            /* Clear it to wait next command */
            LinCoreExeFlag.CoreCmdExist = 0U;
        }
    }
}

#define LIN_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Lin_MemMap.h"

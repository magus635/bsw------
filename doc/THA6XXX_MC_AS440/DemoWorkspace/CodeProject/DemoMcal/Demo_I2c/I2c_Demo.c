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

#include "I2c_Demo.h"
#include "Mcall.h"
#include "Demo_Common.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
#define EEPROM_PAGE_SZ                      (64U)

typedef volatile struct
{
    uint8 CoreCmdExist;    /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} I2c_ChannelCoreExeType;

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define I2C_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "I2c_MemMap.h"
static uint8 I2c_DemoInitStatusCore0 = 0U;
#define I2C_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#include "I2c_MemMap.h"

#define I2C_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "I2c_MemMap.h"
static uint8 I2c_DemoInitStatusCore1 = 0U;
#define I2C_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#include "I2c_MemMap.h"

#define I2C_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "I2c_MemMap.h"

static uint8 I2c_DemoCoreSelFlg = MCAL_CORE0;

#define I2C_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "I2c_MemMap.h"

#define I2C_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "I2c_MemMap.h"

static I2c_ChannelCoreExeType I2cCoreExeFlag = {0, 0xFFU};

static uint8 I2c_TransmitData[EEPROM_PAGE_SZ + 2U] = {0};
static uint8 I2c_ReceiveData[EEPROM_PAGE_SZ] = {0};

static I2c_TransDataInfoType I2c_UserTransmit =
{
    .DataPtr = &I2c_TransmitData[0],
    .Size = EEPROM_PAGE_SZ + 2U,
    .SlaveAddress = 0x50U,/* Eeprom adress */
    .Diraction = I2C_WRITE
};

static I2c_TransDataInfoType I2c_UserReceive =
{
    .DataPtr = &I2c_ReceiveData[0],
    .Size = EEPROM_PAGE_SZ,
    .SlaveAddress = 0x50U,
    .Diraction = I2C_READ
};


#define I2C_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "I2c_MemMap.h"

#define I2C_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "I2c_MemMap.h"

/* Used I2C channel in Demo */
static const uint8 I2c_CorexChanneMap[MCAL_NUMBER_OF_CORES] =
{
    /* Core0 */
    I2cConf_I2cChannel_I2cChannel_0
};

static uint8 * const I2c_DemoCoreInitStatus[MCAL_NUMBER_OF_CORES] =
{
    &I2c_DemoInitStatusCore0,
    &I2c_DemoInitStatusCore1
};

#define I2C_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "I2c_MemMap.h"
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
#define I2C_START_SEC_CODE_ASIL_D_GLOBAL
#include "I2c_MemMap.h"

static void I2c_WriteReadEeprom(void);
static void I2c_DemoSelect(void);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Lin_WakeupDemo
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
static void I2c_WriteReadEeprom(void)
{
    uint16 RegAddr;
    uint8 AddrBuf[2U];
    uint32 loopCount;
    Std_ReturnType RetStatus;
    Mcal_CoreType  CoreId;
    boolean compareResult;
    I2c_TransDataInfoType    SendRegisterAddress;

    RegAddr = 64U;
    compareResult = TRUE;

    CoreId = Mcal_GetCoreId();

    /* Set the EEPROM register address */
    AddrBuf[0U] = (uint8)(RegAddr >> 8U);
    AddrBuf[1U] = (uint8)RegAddr;

    /* The first two bits hold the EEPROM register address */
    I2c_TransmitData[0U] = AddrBuf[0U];
    I2c_TransmitData[1U] = AddrBuf[1U];

    I2c_Init(&I2c_ConfigSet[0]);

    for(loopCount = 2U; loopCount < EEPROM_PAGE_SZ + 2; loopCount++)
    {
        /* Fill write buffer */
        I2c_TransmitData[loopCount] = (uint8)loopCount;
    }
    /* Write eeprom */
    RetStatus = I2c_SyncTransmit(I2c_CorexChanneMap[CoreId], &I2c_UserTransmit);

    if(E_OK == RetStatus)
    {
        /* Eeprom adress */
        SendRegisterAddress.DataPtr = &AddrBuf[0];
        SendRegisterAddress.Size = 2U;
        SendRegisterAddress.SlaveAddress = 0x50U;
        SendRegisterAddress.Diraction = I2C_WRITE;
        Timer_DelayMs(5);
        /* Write eeprom register address */
        RetStatus = I2c_SyncTransmit(I2c_CorexChanneMap[CoreId], &SendRegisterAddress);
        if(E_OK == RetStatus)
        {
            /* Read eeprom */
            RetStatus = I2c_SyncTransmit(I2c_CorexChanneMap[CoreId], &I2c_UserReceive);
            if(E_OK == RetStatus)
            {
                loopCount = 0U;
                /* Compare write buffer and read buffer */
                do
                {
                    if(I2c_TransmitData[loopCount + 2] != I2c_ReceiveData[loopCount])
                    {
                        compareResult = FALSE;
                    }
                    loopCount += 1;
                }while((loopCount < EEPROM_PAGE_SZ) && (TRUE == compareResult));
            }
        }
    }

    if ((E_OK == RetStatus) && (TRUE == compareResult))
    {
        DEBUG_PRINTF("\nI2c write and read eeprom SUCCESS!");
    }
    else
    {
        DEBUG_PRINTF("\nI2c write and read eeprom FAILED!");
    }
    I2c_DeInit();
}

/****************************************************************************************************
*   Function Name           : I2c_DemoSelect
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
static void I2c_DemoSelect(void)
{
    uint8 Cmd;
    uint8 Exit;
    Std_VersionInfoType VersionInfo;

    Exit = 0U;
    while (0U == Exit)
    {
        I2c_GetVersionInfo(&VersionInfo);
        DEBUG_PRINTF((const uint8*)"\n\n\n");
        DEBUG_PRINTF((const uint8*)"\n/*********************************************************/");
        DEBUG_PRINTF((const uint8*)"\n           I2C DRIVER DEMO MENU V%02d.%02d.%02d            ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF((const uint8*)"\n                                                         ");
        if(MCAL_CORE0 == I2c_DemoCoreSelFlg)
        {
            DEBUG_PRINTF((const uint8*)"\n  <1> : Write and read eeprom demo: Send data to eeprom in Core0. ");
        }
        else
        {  
            DEBUG_PRINTF((const uint8*)"\n  <1> : Write and read eeprom demo: Send data to eeprom in Core1. ");
        }
        DEBUG_PRINTF((const uint8*)"\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF((const uint8*)"\n  ENTER YOUR OPTION   : ");
        /* Waiting till received a uart command character */
        Cmd = DEBUG_GETC();

        /* As for I2c Demo, valid command character range from 1 to 7 */
        if ((Cmd >= 0x31U) && (Cmd <= 0x31U))
        {
            /* Convert the command character to number */
            I2cCoreExeFlag.CoreExeCmd = (Cmd - 0x30U);
            /* Set it to inform the Core to running the demo
             * It must be here */
            I2cCoreExeFlag.CoreCmdExist = 1U;
            /* Call Lin_Demo direct in Core 0 */
            I2c_Demo();
            while(0xFFU != I2cCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Lin demo test finished */
            }
        }
        else if (((char)Cmd == 'x') || ((char)Cmd == 'X'))
        {
            Exit = 1U;
            I2cCoreExeFlag.CoreExeCmd = 0xFFU;
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
*   Function Name           : I2c_DemoEntry
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
void I2c_DemoEntry(void)
{
    uint8               Cmd  = 0U;
    uint8               Exit = 0U;
    Std_VersionInfoType VersionInfo;

    Exit = 0U;
    while (0U == Exit)
    {
        I2c_GetVersionInfo(&VersionInfo);
        DEBUG_PRINTF((const uint8*)"\n\n\n");
        DEBUG_PRINTF((const uint8*)"\n/*********************************************************/");
        DEBUG_PRINTF((const uint8*)"\n           I2C DRIVER DEMO MENU V%02d.%02d.%02d            ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF((const uint8*)"\n                                                         ");
        DEBUG_PRINTF((const uint8*)"\n  <1> : I2c Channel0 Demo in Core0. ");
        DEBUG_PRINTF((const uint8*)"\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF((const uint8*)"\n  ENTER YOUR OPTION   : ");

        /* Waiting till received a uart command character */
        Cmd = DEBUG_GETC();

        switch ((char)Cmd)
        {
            case '1':
            {
                /* Demo for Core0 */
                I2c_DemoCoreSelFlg = MCAL_CORE0;
                DEBUG_PRINTF((const uint8*)"\n  Choose the Core0 to running demo. \n");
                I2c_DemoSelect();
                break;
            }
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
void I2c_Demo(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();

    if ((I2c_DemoCoreSelFlg == CoreId) && (1U == I2cCoreExeFlag.CoreCmdExist))
    {
        if(0U == *I2c_DemoCoreInitStatus[CoreId])
        {
            /* Initialize and each core needs to be initialized once */
            *I2c_DemoCoreInitStatus[CoreId] = 1U;
        }

        switch (I2cCoreExeFlag.CoreExeCmd)
        {
            case 1:
            {
                I2c_WriteReadEeprom();
                break;
            }
            default:
            {
                break;
            }
        }
        if (0xFFU != I2cCoreExeFlag.CoreExeCmd)
        {
            I2cCoreExeFlag.CoreExeCmd = 0xFFU;
            /* Clear it to wait next command */
            I2cCoreExeFlag.CoreCmdExist = 0U;
        }
    }
}

#define I2C_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "I2c_MemMap.h"

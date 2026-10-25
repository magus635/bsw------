/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fee_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains Demo application for Fee Module
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
#include "Fee_Cfg.h"
#include "Fee.h"
#include "Fls_Cfg.h"
#include "Fls.h"
#include "Intc.h"
#include "Fee_Demo.h"
#include "Demo_Common.h"
#include "dflash_hal.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
typedef struct
{
    uint8 CoreCmdExist;    /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} Fee_CoreExeType;

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define FEE_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Fee_MemMap.h"

static volatile Fee_CoreExeType FeeCoreExeFlag = {0, 0xFFU};
static uint8 Fee_Write_Buffer[65] =
                                {"1234567890123456789012345678901234567890123456789012345678901234"};

#if (STD_ON == FEE_NOT_FOUND_MANAGEMENTINFO_DETECT)
static uint8 Nvm_NotFoundManagementInfo = 0U;
#endif /* (STD_ON == FEE_NOT_FOUND_MANAGEMENTINFO_DETECT) */

#define FEE_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Fee_MemMap.h"


#define FEE_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Fee_MemMap.h"

static uint8 Fee_Read_Buffer[64];
static uint8 Fee_DemoCoreSelFlg = MCAL_CORE0;
static uint8 FeeInitFlag = 0U;
static uint8 Nvm_JobEndFlag = 0U;
static uint8 Nvm_JobErrorFlag = 0U;
static uint8 Nvm_UnavailableFailure = 0U;

#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Fee_MemMap.h"

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
#define FEE_START_SEC_CODE_ASIL_D_GLOBAL
#include "Fee_MemMap.h"

static void Fee_DemoSelect(void);
static void FeeDemo_InitRun(void);
static void FeeDemo_WriteBlock(uint16 blockID, uint8* data);
static Std_ReturnType FeeDemo_ReadBlock(uint16 blockID, uint8* data, uint16 length);
static void FeeDemo_InvalidateBlock(uint16 blockID);
static void Fee_DelayUs(uint32 DelayTimeUs);

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : FeeDemo_InitRun
*
*   Service ID              : None.
*
*   Description             : FEE initialization function demo: initializing FLS and FEE modules.
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
static void FeeDemo_InitRun(void)
{
    DEBUG_PRINTF("\n\n\n  Initialing Fee Module... ");
    Fls_Init(&Fls_ConfigSet[0]);
    /* Demo: Closed Ecc error and generated BusError. */
    /* When a read error occurs, Fee will enter an exception. */
    /* Users can turn off the Ecc error generating BusError function in UCB or */
    /* add error handling in exceptions when using it. */
    Flash_Hal_ConfigDFlashEccBusErrorAlarm(DFLASH_INTOP_DISABLE);
    Fee_Init(&Fee_ConfigSet[0]);
    /* The request is not set successfully. The current core is not the Fee allocation core */
    while(MEMIF_BUSY_INTERNAL == Fee_GetStatus())
    {
        Fee_MainFunction();
        Fls_MainFunction();
    }
    Flash_Hal_ConfigDFlashEccBusErrorAlarm(DFLASH_INTOP_ENABLE);
    if ((0U == Nvm_JobErrorFlag) && (0U == Nvm_UnavailableFailure))
    {
        FeeInitFlag = 1U;
        DEBUG_PRINTF("\n  Fee Module initial complete. ");
    }
    else
    {
        DEBUG_PRINTF("\n  Fee Module initial fail!!! ");
    }
}

/****************************************************************************************************
*   Function Name           : FeeDemo_WriteBlock
*
*   Service ID              : None.
*
*   Description             : FEE write function demo.
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
static void FeeDemo_WriteBlock(uint16 blockID, uint8* data)
{
    Std_ReturnType ReturnValue;
    MemIf_JobResultType JobResult;

    DEBUG_PRINTF("\n\n\n  Fee is writing Block %d... ", blockID);
    ReturnValue = Fee_Write(blockID, data);
    if (E_OK == ReturnValue)
    {
        /* The request is not set successfully. The current core is not the Fee allocation core */
        while((MEMIF_IDLE != Fee_GetStatus()) && (MEMIF_UNINIT != Fee_GetStatus()))
        {
            Fee_DelayUs(10000U);
            Fee_MainFunction();
            Fls_MainFunction();
        }

        if ((1U == Nvm_JobEndFlag) && (0U == Nvm_JobErrorFlag) && (0U == Nvm_UnavailableFailure))
        {
            JobResult = Fee_GetJobResult();
            if (MEMIF_JOB_OK == JobResult)
            {
                DEBUG_PRINTF("\n  Fee write complete. ");
            }
            else
            {
                DEBUG_PRINTF("\n  Fee write fail. ");
            }
        }
        else
        {
            DEBUG_PRINTF("\n  Fee write fail. ");
        }
    }
    else
    {
        DEBUG_PRINTF("\n  Fee write request fail. ");
    }
}

/****************************************************************************************************
*   Function Name           : FeeDemo_ReadBlock
*
*   Service ID              : None.
*
*   Description             : FEE read function demo.
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
static Std_ReturnType FeeDemo_ReadBlock(uint16 blockID, uint8* data, uint16 length)
{
    Std_ReturnType ReturnValue;
    MemIf_JobResultType JobResult;
    Std_ReturnType RetVal;

    RetVal = E_NOT_OK;
    DEBUG_PRINTF("\n\n\n  Fee is reading Block %d... ", blockID);
    ReturnValue = Fee_Read(blockID, 0, data, length);
    if (E_OK == ReturnValue)
    {
        /* The request is not set successfully. The current core is not the Fee allocation core */
        while((MEMIF_IDLE != Fee_GetStatus()) && (MEMIF_UNINIT != Fee_GetStatus()))
        {
            Fee_DelayUs(10000U);
            Fee_MainFunction();
            Fls_MainFunction();
        }
        if (0U == Nvm_UnavailableFailure)
        {
            JobResult = Fee_GetJobResult();
            if ((MEMIF_JOB_OK == JobResult) && ((1U == Nvm_JobEndFlag)))
            {
                DEBUG_PRINTF("\n  Fee read complete. ");
                RetVal = E_OK;
            }
            else if ((MEMIF_BLOCK_INVALID == JobResult) && (1U == Nvm_JobErrorFlag))
            {
                DEBUG_PRINTF("\n  This block has been invalidated. ");
            }
            else
            {
                DEBUG_PRINTF("\n  Fee read fail.(JobResult) ");
            }
        }
        else
        {
            DEBUG_PRINTF("\n  Fee read fail.(Notification) ");
        }
    }
    else
    {
        DEBUG_PRINTF("\n  Fee read request fail. ");
    }

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : FeeDemo_InvalidateBlock
*
*   Service ID              : None.
*
*   Description             : FEE invalidate function demo.
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
static void FeeDemo_InvalidateBlock(uint16 blockID)
{
    Std_ReturnType ReturnValue;
    MemIf_JobResultType JobResult;

    DEBUG_PRINTF("\n\n\n  Fee is invalidating Block %d... ", blockID);
    ReturnValue = Fee_InvalidateBlock(blockID);
    if (E_OK == ReturnValue)
        {
        /* The request is not set successfully. The current core is not the Fee allocation core */
        while((MEMIF_IDLE != Fee_GetStatus()) && (MEMIF_UNINIT != Fee_GetStatus()))
        {
            Fee_DelayUs(10000U);
            Fee_MainFunction();
            Fls_MainFunction();
        }
        if ((1U == Nvm_JobEndFlag) && (0U == Nvm_JobErrorFlag) && (0U == Nvm_UnavailableFailure))
        {
            JobResult = Fee_GetJobResult();
            if (MEMIF_JOB_OK == JobResult)
            {
                DEBUG_PRINTF("\n  Block is invalid. ");
            }
            else
            {
                DEBUG_PRINTF("\n  Block invalid fail.(JobResult) ");
            }
        }
        else
        {
            DEBUG_PRINTF("\n  Block invalid fail.(Notification) ");
        }
    }
    else
    {
        DEBUG_PRINTF("\n  Fee invalid request fail. ");
    }
}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Fee_Demo
*
*   Service ID              : None.
*
*   Description             : Fee Demo function.
*                             Received UART data:
*                             <1> : Initialize Fee module.
*                             <2> : Write to block 8 (32byte) with fix data.
*                             <3> : Write to block 9 (64byte) with fix data.
*                             <4> : Read block 8 data.
*                             <5> : Read block 9 data.
*                             <6> : Invalidate block 8.
*                             <7> : Invalidate block 9.
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
void Fee_Demo(void)
{
    Mcal_CoreType CoreId;
    uint8 i;
    Std_ReturnType RetVal;

    CoreId = Mcal_GetCoreId();
    if ((Fee_DemoCoreSelFlg == CoreId) && (FeeCoreExeFlag.CoreCmdExist == 1U))
    {
        switch (FeeCoreExeFlag.CoreExeCmd)
        {
            case 1:
            {
                Nvm_JobEndFlag = 0U;
                Nvm_JobErrorFlag = 0U;
                Nvm_UnavailableFailure = 0U;
                if (0U == FeeInitFlag)
                {
                    FeeDemo_InitRun();
                }
                else
                {
                    DEBUG_PRINTF("\n  Fee module has already completed initialization. ");
                }
                break;
             }
            case 2:
            {
                Nvm_JobEndFlag = 0U;
                Nvm_JobErrorFlag = 0U;
                Nvm_UnavailableFailure = 0U;
                FeeDemo_WriteBlock(8, Fee_Write_Buffer);
                DEBUG_PRINTF("\n  Data = ");
                for(i = 0; i < 32U; i++)
                {
                    DEBUG_PRINTF("%c", Fee_Write_Buffer[i]);
                }
                break;
            }
            case 3:
            {
                Nvm_JobEndFlag = 0U;
                Nvm_JobErrorFlag = 0U;
                Nvm_UnavailableFailure = 0U;
                FeeDemo_WriteBlock(9, Fee_Write_Buffer);
                DEBUG_PRINTF("\n  Data = ");
                for(i = 0; i < 64U; i++)
                {
                    DEBUG_PRINTF("%c", Fee_Write_Buffer[i]);
                }
                break;
            }
            case 4:
            {
                Nvm_JobEndFlag = 0U;
                Nvm_JobErrorFlag = 0U;
                Nvm_UnavailableFailure = 0U;
                RetVal = FeeDemo_ReadBlock(8, Fee_Read_Buffer, 32);
                if (E_OK == RetVal)
                {
                    DEBUG_PRINTF("\n  Data = ");
                    for(i = 0; i < 32U; i++)
                    {
                        DEBUG_PRINTF("%c", Fee_Read_Buffer[i]);
                    }
                }
                break;
            }
            case 5:
            {
                Nvm_JobEndFlag = 0U;
                Nvm_JobErrorFlag = 0U;
                Nvm_UnavailableFailure = 0U;
                RetVal = FeeDemo_ReadBlock(9, Fee_Read_Buffer, 64);
                if (E_OK == RetVal)
                {
                    DEBUG_PRINTF("\n  Data = ");
                    for(i = 0; i < 64U; i++)
                    {
                        DEBUG_PRINTF("%c", Fee_Read_Buffer[i]);
                    }
                }
                break;
            }
            case 6:
            {
                Nvm_JobEndFlag = 0U;
                Nvm_JobErrorFlag = 0U;
                Nvm_UnavailableFailure = 0U;
                FeeDemo_InvalidateBlock(8);
                break;
            }
            case 7:
            {
                Nvm_JobEndFlag = 0U;
                Nvm_JobErrorFlag = 0U;
                Nvm_UnavailableFailure = 0U;
                FeeDemo_InvalidateBlock(9);
                break;
            }
            default:
            {
                break;
            }
        }
        if (0xFFU != FeeCoreExeFlag.CoreExeCmd)
        {
            FeeCoreExeFlag.CoreExeCmd = 0xFFU;
        }
    }
}

/****************************************************************************************************
*   Function Name           : Fee_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Fee demo application entry.
*                             Select which core to use to run Fee demo.
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
void Fee_DemoEntry(void)
{
    uint8 cmd;
    volatile uint8 loopvar = 0;
    Std_VersionInfoType VersionInfo;

    Fee_GetVersionInfo(&VersionInfo);
    while (loopvar == 0U)
    {
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                     Fee DRIVER DEMO MENU                          ");
        DEBUG_PRINTF("\n                      Fee Version V%d.%d.%d                        ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Run Fee Demo in Core0. ");
#if (MCAL_CFG_ENABLE_CORE1 == STD_ON)
        DEBUG_PRINTF("\n  <2> : Run Fee Demo in Core1. ");
#endif /* (MCAL_CFG_ENABLE_CORE1  \== STD_ON) */
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        cmd = DEBUG_GETC();
        DEBUG_PRINTF("%c", cmd);
        switch ((char)cmd)
        {
            case '1':
            {
                /* Demo for Core0 */
                Fee_DemoCoreSelFlg = MCAL_CORE0;
                DEBUG_PRINTF("\n  Choose the Core0 to running demo. \n");
                Fee_DemoSelect();
                break;
            }
#if (MCAL_CFG_ENABLE_CORE1 == STD_ON)
            case '2':
            {
                /* Demo for Core1 */
                Fee_DemoCoreSelFlg = MCAL_CORE1;
                DEBUG_PRINTF("\n  Choose the Core1 to running demo. \n");
                Fee_DemoSelect();
                break;
            }
#endif /* (MCAL_CFG_ENABLE_CORE1  \== STD_ON) */
            case 'x':
            case 'X':
            {
                loopvar = 1U;
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
*   Function Name           : Fee_DemoSelect
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
static void Fee_DemoSelect(void)
{
    uint8 cmd;
    uint8 Fee_exit;
    Std_VersionInfoType VersionInfo;

    Fee_GetVersionInfo(&VersionInfo);
    Fee_exit = 0U;
    while (0U == Fee_exit)
    {
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                     FEE DRIVER DEMO MENU                          ");
        DEBUG_PRINTF("\n                      FEE Version V%d.%d.%d                        ",
          VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Initialize Fee module. ");
        DEBUG_PRINTF("\n  <2> : Write to block 8 (32byte) with fix data. ");
        DEBUG_PRINTF("\n  <3> : Write to block 9 (64byte) with fix data. ");
        DEBUG_PRINTF("\n  <4> : Read block 8 data. ");
        DEBUG_PRINTF("\n  <5> : Read block 9 data. ");
        DEBUG_PRINTF("\n  <6> : Invalidate block 8. ");
        DEBUG_PRINTF("\n  <7> : Invalidate block 9. ");
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Fee_exit = 0U;
        cmd = DEBUG_GETC();
        if ((cmd >= 0x31U) && (cmd <= 0x37U))    /* ASCII '0'-'5' */
        {
            /* Convert the command character to number */
            FeeCoreExeFlag.CoreExeCmd = (cmd - 0x30U);
            /* Set it to inform the Core to running the demo
             * It must be here */
            FeeCoreExeFlag.CoreCmdExist = 1U;
            /* Call Fee_Demo direct in Core 0 */
            Fee_Demo();
            while(0xFFU != FeeCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Fee demo test finished */
            }
            /* Clear it to wait next command */
            FeeCoreExeFlag.CoreCmdExist = 0U;
        }
        else if (((char)cmd == 'x') || ((char)cmd == 'X'))
        {
            Fee_exit = 1U;
            FeeCoreExeFlag.CoreExeCmd = 0xFFU;
            if(FeeInitFlag == 1U)
            {
                FeeInitFlag = 0U;
            }
        }
        else
        {
            DEBUG_PRINTF("\n\n  INVALID OPTION");
        }
    }
}

void NvM_JobEndNotification(void)
{
    Nvm_JobEndFlag = 1U;
}

void NvM_JobErrorNotification(void)
{
    Nvm_JobErrorFlag = 1U;
}

void NvM_UnavailableFailureNotification(void)
{
    Nvm_UnavailableFailure = 1U;
}

#if (STD_ON == FEE_NOT_FOUND_MANAGEMENTINFO_DETECT)
void NvM_NotFoundManagementInfoNotification(void)
{
    Nvm_NotFoundManagementInfo = 1U;
}
#endif /* (STD_ON == FEE_NOT_FOUND_MANAGEMENTINFO_DETECT) */

static void Fee_DelayUs(uint32 DelayTimeUs)
{
    uint64 StartTime;
    uint64 OverTime;
    uint64 EndTime;
    uint32 StmFrequency;

    StmFrequency = (uint32)Mcal_GetSystemTimerFreq();
    OverTime = (uint64)DelayTimeUs * StmFrequency / 1000000U;
    StartTime = Stm_Hal_GetValue();   /* Get system counter */
    do
    {
        EndTime = Stm_Hal_GetValue() - StartTime;
    } while(EndTime < OverTime);
}

#define FEE_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Fee_MemMap.h"

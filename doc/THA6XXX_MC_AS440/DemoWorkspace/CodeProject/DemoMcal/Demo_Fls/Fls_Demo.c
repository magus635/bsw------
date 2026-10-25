/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls_Demo.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains Demo application for Fls Driver
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
#include "Fls_Cfg.h"
#include "Fls.h"
#include "Intc.h"
#include "Fls_Demo.h"
#include "Demo_Common.h"
#include "Std_Types.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
typedef struct
{
    uint8 CoreCmdExist;    /* This variable can only be changed by Core0(master) */
    uint8 CoreExeCmd;
} Fls_CoreExeType;

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define FLS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Fls_MemMap.h"

ALIGNED(64) static uint8 Fls_Write_Buffer1[65] = {"1234567890123456789012345678901234567890123456789012345678901234"};
ALIGNED(64) static uint8 Fls_Write_Buffer2[65] = {"ABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCDEFGHIJABCD"};
static volatile Fls_CoreExeType FlsCoreExeFlag = {0, 0xFFU};

#define FLS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Fls_MemMap.h"


#define FLS_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Fls_MemMap.h"

static uint8 FlsInitFlag;
/* Actually Fls_DemoCoreSelFlg = MCAL_CORE0 */
static uint8 Fls_DemoCoreSelFlg;
static uint8 Fls_Read_Buffer[64];
/* Actually FlsDemoBufferId = 0 */
static uint8 FlsDemoBufferId;

#define FLS_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Fls_MemMap.h"

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
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
#include "Fls_MemMap.h"

static void FlsDemo_EraseOneSector(Fls_AddressType Address);
static void FlsDemo_Write64(Fls_AddressType Address);
static void FlsDemo_BlankCheck64(Fls_AddressType Address);
static void FlsDemo_Read64(Fls_AddressType Address);
static void Fls_DemoSelect(void);
static void Fls_DelayUs(uint32 DelayTimeUs);
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
*   Function Name           : FlsDemo_EraseOneSector
*
*   Service ID              : None.
*
*   Description             : FLS erase demo: erase one sector.
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
static void FlsDemo_EraseOneSector(Fls_AddressType Address)
{
    MemIf_JobResultType result;
    Std_ReturnType ReTVal;

    DEBUG_PRINTF("\n\n  Erasing physical address  0x%x, length 8K", FLS_DFLASH_BASE_ADDRESS+Address);
    /* Erase Address must align with sector size, length must be multiple of sector size. */
    ReTVal = Fls_Erase(Address, FLS_SECTOR_SIZE);
    if (E_OK == ReTVal)
    {
        /* Job operation */
        while(MEMIF_JOB_PENDING == Fls_GetJobResult())
        {
            Fls_DelayUs(10000U);
            Fls_MainFunction();
        }
        result = Fls_GetJobResult();
        if(MEMIF_JOB_OK == result)
        {
            DEBUG_PRINTF("\n  Erase Success ");

        }
        else
        {
            DEBUG_PRINTF("\n  Erase Operation Fail ");
        }
    }
    else
    {
        DEBUG_PRINTF("\n  Erase Request Fail ");
    }
}

/****************************************************************************************************
*   Function Name           : FlsDemo_Write64
*
*   Service ID              : None.
*
*   Description             : FLS write demo: write 64 byte to flash.
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
static void FlsDemo_Write64(Fls_AddressType Address)
{
    uint8* bufferPtr;
    MemIf_JobResultType result;
    Std_ReturnType RetVal;
    uint8 i;

    if(FlsDemoBufferId == 0U)
    {
        bufferPtr = Fls_Write_Buffer1;
        FlsDemoBufferId = 1U;
    }
    else
    {
        bufferPtr = Fls_Write_Buffer2;
        FlsDemoBufferId = 0U;
    }
    DEBUG_PRINTF("\n\n  Programming physical address  0x%x, length 64 byte", FLS_DFLASH_BASE_ADDRESS+Address);
    DEBUG_PRINTF("\n  Write content:  ");
    for(i=0;i<64U;i++)
    {
        DEBUG_PRINTF("%c",*(uint8*)(bufferPtr+i));
    }
    DEBUG_PRINTF("\n");
    /* Program Address must align with 8 byte, length must be multiple of 8 byte */
    RetVal = Fls_Write(Address, bufferPtr, 64U);
    if (E_OK == RetVal)
    {
        /* Job operation */
        while(MEMIF_JOB_PENDING == Fls_GetJobResult())
        {
            Fls_DelayUs(10000U);
            Fls_MainFunction();
        }
        result = Fls_GetJobResult();
        if(MEMIF_JOB_OK == result)
        {
            DEBUG_PRINTF("\n  Write Success ");
        }
        else
        {
            DEBUG_PRINTF("\n  Write Operation Fail ");
        }
    }
    else
    {
        DEBUG_PRINTF("\n  Write Request Fail ");
    }
}

/****************************************************************************************************
*   Function Name           : FlsDemo_BlankCheck64
*
*   Service ID              : None.
*
*   Description             : FLS blank check demo: check 64 byte in flash.
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
static void FlsDemo_BlankCheck64(Fls_AddressType Address)
{
    MemIf_JobResultType result;
    Std_ReturnType ReTVal;

    DEBUG_PRINTF("\n\n  Blank Checking physical address  0x%x, length 64 byte", FLS_DFLASH_BASE_ADDRESS+Address);
    /* could check any valid address, will length scope 1 byte */
    ReTVal = Fls_BlankCheck(Address, 64U);
    if (E_OK == ReTVal)
    {
        while(MEMIF_JOB_PENDING == Fls_GetJobResult())
        {
            Fls_DelayUs(10000U);
            Fls_MainFunction();
        }
        result = Fls_GetJobResult();
        if(MEMIF_JOB_OK == result)
        {
            DEBUG_PRINTF("\n  Flash is blank. ");
        }
        else if (MEMIF_BLOCK_INCONSISTENT == result)
        {
            DEBUG_PRINTF("\n  Flash been written. ");
        }
        else
        {
            DEBUG_PRINTF("\n  Blank Check Operation Failed. ");
        }
    }
    else
    {
        DEBUG_PRINTF("\n  Blank Check Request Failed. ");
    }
}

/****************************************************************************************************
*   Function Name           : FlsDemo_Read64
*
*   Service ID              : None.
*
*   Description             : FLS read demo: read 64 byte in flash.
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
static void FlsDemo_Read64(Fls_AddressType Address)
{
    MemIf_JobResultType result;
    Std_ReturnType ReTVal;
    uint8 i;

    DEBUG_PRINTF("\n\n  Reading physical address  0x%x, length 64 byte", FLS_DFLASH_BASE_ADDRESS+Address);
    /* could read any valid address, will length scope 1 byte */
    ReTVal = Fls_Read(Address, Fls_Read_Buffer, 64U);
    if (E_OK == ReTVal)
    {
        /* Job operation */
        while(MEMIF_JOB_PENDING == Fls_GetJobResult())
        {
            Fls_DelayUs(10000U);
            Fls_MainFunction();
        }
        result = Fls_GetJobResult();
        if(MEMIF_JOB_OK == result)
        {
            DEBUG_PRINTF("\n  Read Success ");
            DEBUG_PRINTF("\n  Read content:  ");
            for(i=0;i<64U;i++)
            {
                DEBUG_PRINTF("%c",*(uint8*)(Fls_Read_Buffer+i));
            }
        }
        else
        {
            DEBUG_PRINTF("\n  Read Operation Fail ");
        }
    }
    else
    {
        DEBUG_PRINTF("\n  Read Request Fail ");
    }
}
/****************************************************************************************************
*   Function Name           : FlsDemo_Compare64
*
*   Service ID              : None.
*
*   Description             : FLS compare demo: compare 64 byte in flash.
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
static void FlsDemo_Compare64(Fls_AddressType Address)
{
    Std_ReturnType RetVal = E_OK;
    MemIf_JobResultType JobResult;
    
    DEBUG_PRINTF("\n== Phase 1: Write & Compare test (Expected: Success) ==");
    DEBUG_PRINTF("\n  Writing to physical address: 0x%x, Length: 64 bytes", FLS_DFLASH_BASE_ADDRESS + Address);

    RetVal = Fls_Write(Address, Fls_Write_Buffer1, 64U);
    if (E_OK != RetVal)
    {
        DEBUG_PRINTF("\n  [Phase 1] Write request failed at address: 0x%x", FLS_DFLASH_BASE_ADDRESS + Address);
    }
    else
    {
        while (MEMIF_JOB_PENDING == Fls_GetJobResult())
        {
            Fls_MainFunction();
        }
        if (MEMIF_JOB_OK != Fls_GetJobResult())
        {
            DEBUG_PRINTF("\n  [Phase 1] Write execution failed at address: 0x%x", FLS_DFLASH_BASE_ADDRESS + Address);
        }
        else
        {
            RetVal = Fls_Compare(Address, Fls_Write_Buffer1, 64U);
            if (E_OK != RetVal)
            {
                DEBUG_PRINTF("\n  [Phase 1] Compare request failed at address: 0x%x", 
                    FLS_DFLASH_BASE_ADDRESS + Address);
            }
            else
            {
                while (MEMIF_JOB_PENDING == Fls_GetJobResult())
                {
                    Fls_DelayUs(10000U); /* 延时10毫秒 */
                    Fls_MainFunction();
                }
                JobResult = Fls_GetJobResult();
                if (MEMIF_JOB_OK == JobResult)
                {
                    DEBUG_PRINTF("\n  [Phase 1] Compare Success: Data at 0x%x matches with buffer1", 
                        FLS_DFLASH_BASE_ADDRESS + Address);
                }
                else
                {
                    DEBUG_PRINTF("\n  [Phase 1] Compare executing failed at address: 0x%x", 
                        FLS_DFLASH_BASE_ADDRESS + Address);
                    RetVal = E_NOT_OK;
                }
            }
        }
    }
    
    DEBUG_PRINTF("\n\n== Phase 2: Write & Compare test (Expected: Mismatch) ==");
    DEBUG_PRINTF("\n  Writing to physical address: 0x%x, Length: 64 bytes", FLS_DFLASH_BASE_ADDRESS + Address + 64U);
    
    RetVal = Fls_Write(Address + 64U, Fls_Write_Buffer2, 64U);
    if (E_OK != RetVal)
    {
        DEBUG_PRINTF("\n  [Phase 2] Write request failed at address: 0x%x", 
            FLS_DFLASH_BASE_ADDRESS + Address + 64U);
    }
    else
    {
        while (MEMIF_JOB_PENDING == Fls_GetJobResult())
        {
            Fls_MainFunction();
        }
        if (MEMIF_JOB_OK != Fls_GetJobResult())
        {
            DEBUG_PRINTF("\n  [Phase 2] Write execution failed at address: 0x%x", 
                FLS_DFLASH_BASE_ADDRESS + Address + 64U);
        }
        else
        {
            Fls_Write_Buffer2[0] = 0xAA;
            RetVal = Fls_Compare(Address + 64U, Fls_Write_Buffer1, 64U);
            if (E_OK != RetVal)
            {
                DEBUG_PRINTF("\n  [Phase 2] Compare request failed at address: 0x%x", 
                    FLS_DFLASH_BASE_ADDRESS + Address + 64U);
            }
            else
            {
                while (MEMIF_JOB_PENDING == Fls_GetJobResult())
                {
                    Fls_DelayUs(10000U);
                    Fls_MainFunction();
                }
                JobResult = Fls_GetJobResult();
                if (MEMIF_JOB_OK == JobResult)
                {
                    DEBUG_PRINTF("\n  [Phase 2] Compare Success (Unexpected): Data at 0x%x " \
                        "unexpectedly matched buffer1", FLS_DFLASH_BASE_ADDRESS + Address + 64U);
                }
                else
                {
                    DEBUG_PRINTF("\n  [Phase 2] Compare Failure as ""expected: Data at " \
                        "0x%x does NOT match buffer1", FLS_DFLASH_BASE_ADDRESS + Address + 64U);
                }
            }
        }
    }
    
    DEBUG_PRINTF("\n\n== Testing Completed ==");
    if (E_OK == RetVal)
    {
        DEBUG_PRINTF("\n  Final Result: Flash compare tests executed ALL SUCCESS.");
    }
    else
    {
        DEBUG_PRINTF("\n  Final Result: Some tests encountered errors or unexpected behavior.");
    }

}
/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : Fls_Demo
*
*   Service ID              : None.
*
*   Description             : Fls Demo function.
*                             Received UART data:
*                             <1> : Initialize Fls module.
*                             <2> : Erase 8K Flash.
*                             <3> : Write 64 byte to Flash.
*                             <4> : Check 64 byte Blank.
*                             <5> : Read 64 byte from Flash.
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
void Fls_Demo(void)
{
    Mcal_CoreType CoreId;

    CoreId = Mcal_GetCoreId();
    if ((Fls_DemoCoreSelFlg == CoreId) && (FlsCoreExeFlag.CoreCmdExist == 1U))
    {
        switch (FlsCoreExeFlag.CoreExeCmd)
        {
            case 1:
            {
                DEBUG_PRINTF("\nCommand:1");
                if (0U == FlsInitFlag)
                {
                    DEBUG_PRINTF("\n\n\n  Initialing Fls Module... ");
                    Fls_Init(&Fls_ConfigSet[0U]);
                    DEBUG_PRINTF("\n  Fls Module initial complete. ");
                    FlsInitFlag = 1;
                }
                else
                {
                    DEBUG_PRINTF("\n  Fls module has already completed initialization. ");
                }

                break;
            }
            case 2:
            {
                DEBUG_PRINTF("\nCommand:2");
                FlsDemo_EraseOneSector(0U);
                break;
            }
            case 3:
            {
                DEBUG_PRINTF("\nCommand:3");
                FlsDemo_Write64(0U);
                break;
            }
            case 4:
            {
                DEBUG_PRINTF("\nCommand:4");
                FlsDemo_BlankCheck64(0);
                break;
            }
            case 5:
            {
                DEBUG_PRINTF("\nCommand:5");
                FlsDemo_Read64(0);
                break;
            }
            case 6:
            {
                DEBUG_PRINTF("\nCommand:6");
                FlsDemo_Compare64(64U);
                break;
            }
            default:
            {
                break;
            }
        }
        if (0xFFU != FlsCoreExeFlag.CoreExeCmd)
        {
            FlsCoreExeFlag.CoreExeCmd = 0xFFU;
        }
    }
}

/****************************************************************************************************
*   Function Name           : Fls_DemoEntry
*
*   Service ID              : None.
*
*   Description             : Fls demo application entry.
*                             Select which core to use to run Fls demo.
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
void Fls_DemoEntry(void)
{
    uint8 cmd;
    volatile uint8 loopvar = 0;
    Std_VersionInfoType VersionInfo;

    Fls_GetVersionInfo(&VersionInfo);
    while (loopvar == 0U)
    {
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                     Fls DRIVER DEMO MENU                          ");
        DEBUG_PRINTF("\n                      Fls Version V%d.%d.%d                        ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Run Fls Demo in Core0. ");
#if (MCAL_CFG_ENABLE_CORE1 == STD_ON)
        DEBUG_PRINTF("\n  <2> : Run Fls Demo in Core1. ");
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
                Fls_DemoCoreSelFlg = MCAL_CORE0;
                DEBUG_PRINTF("\n  Choose the Core0 to running demo. \n");
                Fls_DemoSelect();
                break;
            }
#if (MCAL_CFG_ENABLE_CORE1 == STD_ON)
            case '2':
            {
                /* Demo for Core1 */
                Fls_DemoCoreSelFlg = MCAL_CORE1;
                DEBUG_PRINTF("\n  Choose the Core1 to running demo. \n");
                Fls_DemoSelect();
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
*   Function Name           : Fls_DemoSelect
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
static void Fls_DemoSelect(void)
{
    uint8 cmd;
    uint8 Fls_exit;
    Std_VersionInfoType VersionInfo;

    Fls_GetVersionInfo(&VersionInfo);
    Fls_exit = 0U;
    while (0U == Fls_exit)
    {
        DEBUG_PRINTF("\n\n\n");
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                     FLS DRIVER DEMO MENU                          ");
        DEBUG_PRINTF("\n                      FLS Version V%d.%d.%d                        ",
                VersionInfo.sw_major_version, VersionInfo.sw_minor_version, VersionInfo.sw_patch_version);
        DEBUG_PRINTF("\n/*****************************************************************/");
        DEBUG_PRINTF("\n                                                         ");
        DEBUG_PRINTF("\n  <1> : Initialize Fls module. ");
        DEBUG_PRINTF("\n  <2> : Erase 8K Flash. ");
        DEBUG_PRINTF("\n  <3> : Write 64 byte to Flash. ");
        DEBUG_PRINTF("\n  <4> : Check 64 byte Blank. ");
        DEBUG_PRINTF("\n  <5> : Read 64 byte from Flash. ");
        DEBUG_PRINTF("\n  <x> : Go back to Main Menu. \n");
        DEBUG_PRINTF("\n  ENTER YOUR OPTION   : ");

        Fls_exit = 0U;
        cmd = DEBUG_GETC();
        if ((cmd >= 0x31U) && (cmd <= 0x36U))    /* ASCII '0'-'6' */
        {
            /* Convert the command character to number */
            FlsCoreExeFlag.CoreExeCmd = (cmd - 0x30U);
            /* Set it to inform the Core to running the demo
             * It must be here */
            FlsCoreExeFlag.CoreCmdExist = 1U;
            /* Call Fls_Demo direct in Core 0 */
            Fls_Demo();
            while(0xFFU != FlsCoreExeFlag.CoreExeCmd)
            {
                /* Waiting till Fls demo test finished */
            }
            /* Clear it to wait next command */
            FlsCoreExeFlag.CoreCmdExist = 0U;
        }
        else if (((char)cmd == 'x') || ((char)cmd == 'X'))
        {
            Fls_exit = 1U;
            FlsCoreExeFlag.CoreExeCmd = 0xFFU;
            if(FlsInitFlag == 1U)
            {
                FlsInitFlag = 0U;
            }
        }
        else
        {
            DEBUG_PRINTF("\n\n  INVALID OPTION");
        }
    }
}

static void Fls_DelayUs(uint32 DelayTimeUs)
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

#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Fls_MemMap.h"

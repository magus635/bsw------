/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Mcu_Demo.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : MCAN
 *
 *   brief                 : This file contains Demo application for Can Driver
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
#include "Mcu_Demo.h"
#include "Demo_Common.h"
#include "Mcall.h"
#include "Mcu.h"
#include "Gpt.h"

#ifdef __DEBUG_CHIP__
#include "Uart_Demo.h"
#endif
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

#define MCU_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Mcu_MemMap.h"

#define MCU_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
#include "Mcu_MemMap.h"
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
#define MCU_START_SEC_CODE_ASIL_D_GLOBAL
#include "Mcu_MemMap.h"

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
 *   Function Name           : Mcu_DemoEntry
 *
 *   Service ID              : None.
 *
 *   Description             : This function is the demo API for Mcu driver.
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
 *   Preconditions           : Mcu Driver must be uninitialized.
 *
 ****************************************************************************************************/
void Mcu_DemoEntry(void)
{
    uint8                     cmd;
    Mcu_ResetType             Mcu_Reset_Reason;
    uint32                    McuResetRaw;
    uint32                    looptimeCnt;
    uint64 TimeStart,TimeEnd;

    Std_VersionInfoType       VersionInfo;

    const Mcu_RamSettingType *RamSettingPtr;
    uint32                    RamAddress, Loop;
    uint8                     DefultValue = 0;
    uint8                     ValueJudge = 0;
    volatile uint8            loopvar = 0U;
    Mcu_GetVersionInfo(&VersionInfo);


    DEBUG_PRINTF("\n/*********************************************************/");
    DEBUG_PRINTF(
        "\n           MCU DRIVER CODE VERSION V%d.%d.%d                  ",
        VersionInfo.sw_major_version,
        VersionInfo.sw_minor_version,
        VersionInfo.sw_patch_version);
    DEBUG_PRINTF("\n/*********************************************************/\n");

    DEBUG_PRINTF("\n\n\n");
    DEBUG_PRINTF("\n/******************************************************");
    DEBUG_PRINTF("*********************/\n");
    DEBUG_PRINTF("\n                 MCU DRIVER DEMOAPP MENU                \n");
    DEBUG_PRINTF("                   ENTER YOUR OPTION                      \n");
    DEBUG_PRINTF("              < 1 >  Perform Software Reset               \n");
    DEBUG_PRINTF("              < 2 >  Get Reset Reason                     \n");
    DEBUG_PRINTF("              < 3 >  Mcu_InitRamSection Test                    \n");
    DEBUG_PRINTF("              < 4 >  SetMode Test                    \n");
    DEBUG_PRINTF("              < x >  Back To Main Menu                    \n");
    DEBUG_PRINTF("\n/******************************************************");
    DEBUG_PRINTF("*********************/\n");
    DEBUG_PRINTF("Enter Your Option: ");

    while (loopvar == 0U)
    {
        cmd = DEBUG_GETC();

        switch (cmd)
        {
        case '1':
            DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
            DEBUG_PRINTF(" The MCU will Reset by Mcu_PerformReset. ");
            DEBUG_PRINTF("\n/*********************************************************/\n\n\n");
            looptimeCnt = 20000U;
            while (looptimeCnt > 0U)
            {
                looptimeCnt--;
            }

#if (MCU_PERFORM_RESET_API == STD_ON)
            Mcu_PerformReset();
#endif
            break;

        case '2':
            DEBUG_PRINTF("\n\n\n/*********************************************************/\n");
            DEBUG_PRINTF(" Get MCU Reset Reason. ");
            DEBUG_PRINTF("\n/*********************************************************/\n\n\n");
            /* Get Reset reason. */
            Mcu_Reset_Reason = Mcu_GetResetReason();
            switch (Mcu_Reset_Reason)
            {
                case MCU_RSTREASON_ESR0:
                    DEBUG_PRINTF("MCU_RSTREASON_ESR0 Occured\n");
                    break;
                case MCU_RSTREASON_ESR1:
                    DEBUG_PRINTF("MCU_RSTREASON_ESR1 Occured\n");
                    break;
                case MCU_RSTREASON_SAC:
                    DEBUG_PRINTF("MCU_RSTREASON_SAC Occured\n");
                    break;
                case MCU_SW_RESET:
                    DEBUG_PRINTF("MCU_SW_RESET Occured\n");
                    break;
                case MCU_WATCHDOG_RESET:
                    DEBUG_PRINTF("MCU_WATCHDOG_RESET Occured\n");
                    break;
                case MCU_RSTREASON_CPU0WARMRST:
                    DEBUG_PRINTF("MCU_RSTREASON_CPU0WARMRST Occured\n");
                    break;
                case MCU_RSTREASON_CPU1WARMRST:
                    DEBUG_PRINTF("MCU_RSTREASON_CPU1WARMRST Occured\n");
                    break;
                case MCU_RSTREASON_PORSTPIN:
                    DEBUG_PRINTF("MCU_RSTREASON_PORSTPIN Occured\n");
                    break;
                case MCU_RSTREASON_IST:
                    DEBUG_PRINTF("MCU_RSTREASON_IST Occured\n");
                    break;
                case MCU_RSTREASON_HSMAPP:
                    DEBUG_PRINTF("MCU_RSTREASON_HSMAPP Occured\n");
                    break;
                case MCU_RSTREASON_HSMSYS:
                    DEBUG_PRINTF("MCU_RSTREASON_HSMSYS Occured\n");
                    break;
                case MCU_POWER_ON_RESET:
                    DEBUG_PRINTF("MCU_POWER_ON_RESET Occured\n");
                    break;
                case MCU_RSTREASON_MUTITYPE:
                    DEBUG_PRINTF("MCU_RSTREASON_MUTITYPE Occured\n");
                    break;
                case MCU_RESET_UNDEFINED:
                    DEBUG_PRINTF("MCU_RESET_UNDEFINED Occured\n");
                    break;
            default:
                DEBUG_PRINTF("\n\n  MCU_RESET_UNDEFINED Occured\n");
                break;
            }

            McuResetRaw = Mcu_GetResetRawValue();
            DEBUG_PRINTF("the raw reset value is  0x%02lx \n", McuResetRaw);

            break;
        case '3':
            RamSettingPtr = Mcu_ConfigSet[0].RamSettingPtr;
            RamAddress = (uint32)RamSettingPtr[0].RamSectionBaseAddrPtr;
            DefultValue = RamSettingPtr[0].RamDefaultValue;
            Mcu_InitRamSection(McuConf_McuRamSectorSettingConf_ATCM);
            for (Loop = 0; Loop < RamSettingPtr[0].RamSectionSize; Loop++)
            {
                if (DefultValue == (uint8)(*((uint8 *)RamAddress)))
                {
                    RamAddress += 1;
                }
                else
                {
                    ValueJudge = 1;
                    break;
                }
            }
            if (1 == ValueJudge)
            {
                DEBUG_PRINTF("\n\n  Mcu_InitRamSection FAIL");
            }
            else
            {
                DEBUG_PRINTF("\n\n  Mcu_InitRamSection SUCCESS");
            }

            break;
        case '4':
            /*Disable UART GPT*/
            Gpt_StopTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_6); /* 1000 = 2ms*/
            Gpt_StartTimer(
                GptConf_GptChannelConfiguration_GptForMcu_SetMode, 65000U); /* ONE SHOT MODE*/
            Gpt_EnableNotification(GptConf_GptChannelConfiguration_GptForMcu_SetMode);
            TimeStart = Stm_Hal_GetValue(); /* Get system counter */
            Mcu_SetMode(McuConf_McuModeSettingConf_McuModeSettingConf_0);
            TimeEnd = Stm_Hal_GetValue();         /* Get system counter */
            if ((TimeEnd - TimeStart) < 1625000U) /* Fail to sleep ,65ms*/
            {
                DEBUG_PRINTF("Fail !!!\n");
                DEBUG_PRINTF("start time:%UL,\n", TimeStart);
                DEBUG_PRINTF("end time:%UL,\n", TimeEnd);
                DEBUG_PRINTF("diff time:%UL,\n", (TimeEnd - TimeStart));
            }
            else
            {
                DEBUG_PRINTF("MCU Idle Mode OK\n");
            }

            Timer_DelayMs(100);

            Gpt_StopTimer(GptConf_GptChannelConfiguration_GptForMcu_SetMode);
            Gpt_DisableNotification(GptConf_GptChannelConfiguration_GptForMcu_SetMode);
            /*ENABLE UART GPT*/
            Gpt_StartTimer(
                GptConf_GptChannelConfiguration_GptChannelConfiguration_6, 2500); /* 1000 = 2ms*/

            break;

        case 'x':
        case 'X':
            /* end demo */
            loopvar = 1;
            break;

        default:
            DEBUG_PRINTF("\n\n  INVALID OPTION");
            break;
        } /* End of Case */
    }     /* End of While loop */
} /* Mcu_Demo() */

#define MCU_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Mcu_MemMap.h"

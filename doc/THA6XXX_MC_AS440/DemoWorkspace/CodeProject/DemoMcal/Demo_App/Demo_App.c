/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Demo_App.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : None
*
*   brief                 : Demo application for MCAL modules
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
#include "Uart.h"
#include "Intc.h"
#include "Mcu.h"
#include "Mcall.h"
#include "Demo_App.h"
#include "Demo_Common.h"
#include "exception.h"

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#define DEMO_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
#include "Demo_MemMap.h"

static boolean Init_Process_Is_Ready=FALSE;

#define DEMO_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
#include "Demo_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/
#if (DEMO_PRINT_METHOD == DEMO_PRINT_TOOLCHAIN)

#ifdef _ADS_C_THA6_
extern int _initio();
extern int _init_alloc();
ALIGNED(64) static uint8 s_printfBuffer[256] = {0};
#endif /* _ADS_C_THA6_ */

#ifdef _IAR_C_THA6_

#endif /* _IAR_C_THA6_ */

#ifdef _GHS_C_THA6_

#endif /* _GHS_C_THA6_ */

#endif /* (DEMO_PRINT_METHOD != DEMO_NO_PRINT) */

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

#define DEMO_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Demo_MemMap.h"

static const Demo_EntryInfoType Demo_EntryList[] =
{
#if (STD_ON == MCAL_MODULE_CFG_ETH_EN)
    {'0', Eth_Demo, NULL_PTR, NULL_PTR, NULL_PTR, "Eth"},
#endif /* (STD_ON == MCAL_MODULE_CFG_ETH_EN) */

#if (STD_ON == MCAL_MODULE_CFG_INTC_EN)
    {'1', Intc_DemoEntry, Intc_Demo, NULL_PTR, NULL_PTR, "Intc"},
#endif /* (STD_ON == MCAL_MODULE_CFG_INTC_EN) */

#if (STD_ON == MCAL_MODULE_CFG_MCU_EN)
    {'2', Mcu_DemoEntry, NULL_PTR, NULL_PTR, NULL_PTR, "Mcu"},
#endif /* (STD_ON == MCAL_MODULE_CFG_MCU_EN) */

#if (STD_ON == MCAL_MODULE_CFG_ICU_EN)
    {'3', Icu_DemoEntry, Icu_Demo, NULL_PTR, NULL_PTR, "Icu"},
#endif /* (STD_ON == MCAL_MODULE_CFG_ICU_EN) */

#if (STD_ON == MCAL_MODULE_CFG_DIO_EN)
    {'4', Dio_DemoEntry, Dio_Demo, NULL_PTR, NULL_PTR, "Dio"},
#endif /* (STD_ON == MCAL_MODULE_CFG_DIO_EN) */

#if (STD_ON == MCAL_MODULE_CFG_SPI_EN)
    {'5', Spi_DemoEntry, Spi_Demo, NULL_PTR, NULL_PTR, "Spi"},
#endif /* (STD_ON == MCAL_MODULE_CFG_SPI_EN) */

#if (STD_ON == MCAL_MODULE_CFG_CAN_EN)
    {'6', Can_DemoEntry, Can_DemoEntry, NULL_PTR, NULL_PTR, "Can"},
#endif /* (STD_ON == MCAL_MODULE_CFG_CAN_EN) */

#if (STD_ON == MCAL_MODULE_CFG_LIN_EN)
    {'7', Lin_DemoEntry, Lin_Demo, NULL_PTR, NULL_PTR, "Lin"},
#endif /* (STD_ON == MCAL_MODULE_CFG_LIN_EN) */

#if (STD_ON == MCAL_MODULE_CFG_GPT_EN)
    {'8', Gpt_DemoEntry, Gpt_Demo, NULL_PTR, NULL_PTR, "Gpt"},
#endif /* (STD_ON == MCAL_MODULE_CFG_GPT_EN) */

#if (STD_ON == MCAL_MODULE_CFG_PWM_EN)
    {'9', Pwm_DemoEntry, Pwm_Demo, NULL_PTR, NULL_PTR, "Pwm"},
#endif /* (STD_ON == MCAL_MODULE_CFG_PWM_EN) */

#if (STD_ON == MCAL_MODULE_CFG_OCU_EN)
    {'A', Ocu_DemoEntry, Ocu_Demo, NULL_PTR, NULL_PTR, "Ocu"},
#endif /* (STD_ON == MCAL_MODULE_CFG_OCU_EN) */

#if (STD_ON == MCAL_MODULE_CFG_WDG_EN)
    {'B', Wdg_DemoEntry, Wdg_Demo, NULL_PTR, NULL_PTR, "Wdg"},
#endif /* (STD_ON == MCAL_MODULE_CFG_WDG_EN) */

#if (STD_ON == MCAL_MODULE_CFG_FEE_EN)
    {'C', Fee_DemoEntry, Fee_Demo, NULL_PTR, NULL_PTR, "Fee"},
#endif /* (STD_ON == MCAL_MODULE_CFG_FEE_EN) */

#if (STD_ON == MCAL_MODULE_CFG_FLS_EN)
    {'D', Fls_DemoEntry, Fls_Demo, NULL_PTR, NULL_PTR, "Fls"},
#endif /* (STD_ON == MCAL_MODULE_CFG_FLS_EN) */

#if (STD_ON == MCAL_MODULE_CFG_IOM_EN)
    {'E', Iom_DemoEntry, Iom_Demo, NULL_PTR, NULL_PTR, "Iom"},
#endif /* (STD_ON == MCAL_MODULE_CFG_IOM_EN) */

#if (STD_ON == MCAL_MODULE_CFG_PORT_EN)
    {'F', Port_DemoEntry, Port_Demo, NULL_PTR, NULL_PTR, "Port"},
#endif /* (STD_ON == MCAL_MODULE_CFG_PORT_EN) */

#if (STD_ON == MCAL_MODULE_CFG_DMA_EN)
    {'G', Dma_DemoEntry, Dma_Demo, NULL_PTR, NULL_PTR, "Dma"},
#endif /* (STD_ON == MCAL_MODULE_CFG_DMA_EN) */

#if (STD_ON == MCAL_MODULE_CFG_SENT_EN)
    {'H', Sent_DemoEntry, NULL_PTR, NULL_PTR, NULL_PTR, "Sent"},
#endif /* (STD_ON == MCAL_MODULE_CFG_SENT_EN) */

#if ((defined(MCAL_MODULE_CFG_MSC_EN)) && (STD_ON == MCAL_MODULE_CFG_MSC_EN))
    {'I', Msc_DemoEntry, NULL_PTR, NULL_PTR, NULL_PTR, "Msc"},
#endif /* ((defined(MCAL_MODULE_CFG_MSC_EN)) && (STD_ON == MCAL_MODULE_CFG_MSC_EN)) */

#if (STD_ON == MCAL_MODULE_CFG_ADC_EN)
    {'J', Adc_DemoEntry, Adc_Demo, NULL_PTR, NULL_PTR, "Adc"},
#endif /* (STD_ON == MCAL_MODULE_CFG_ADC_EN) */

#if (STD_ON == MCAL_MODULE_CFG_I2C_EN)
    {'L', I2c_DemoEntry, NULL_PTR, NULL_PTR, NULL_PTR, "I2c"},
#endif /* (STD_ON == MCAL_MODULE_CFG_I2C_EN) */

#if ((defined(MCAL_MODULE_CFG_DSADC_EN)) && (STD_ON == MCAL_MODULE_CFG_DSADC_EN))
    {'M', Dsadc_DemoEntry, NULL_PTR, NULL_PTR, NULL_PTR, "Dsadc"},
#endif /* ((defined(MCAL_MODULE_CFG_DSADC_EN)) && (STD_ON == MCAL_MODULE_CFG_DSADC_EN)) */
};

#define DEMO_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "Demo_MemMap.h"

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
#define DEMO_START_SEC_CODE_ASIL_D_GLOBAL
#include "Demo_MemMap.h"

static void PrintfMainMenu(void)
{
    uint8 ModuleId;
    
    DEBUG_PRINTF("\n\n");
    DEBUG_PRINTF("\n/*********************************************************/\n");
    DEBUG_PRINTF("\n/*********************************************************/\n");
    DEBUG_PRINTF("\n                   DEMO MENU V%d.%d.%d              \n",
                                                          DEMO_SW_RELEASE_MAJOR_VERSION,
                                                          DEMO_SW_RELEASE_MINOR_VERSION,
                                                          DEMO_SW_RELEASE_PATCH_VERSION);

    for (ModuleId = 0U;
            ModuleId < (uint8)(sizeof(Demo_EntryList)/sizeof(Demo_EntryInfoType)); ModuleId ++)
    {
        DEBUG_PRINTF("\n <%c> : %s", Demo_EntryList[ModuleId].InputCmd,
                                    Demo_EntryList[ModuleId].DescInfoPtr);
    }

    DEBUG_PRINTF("\n\n  ENTER YOUR OPTION  : ");

    Init_Process_Is_Ready = TRUE;
}

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/****************************************************************************************************
*   Function Name           : DemoApp_Init
*
*   Service ID              : None.
*
*   Description             :
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
*   Preconditions           : None.
*
****************************************************************************************************/
void DemoApp_Init(void)
{
    Isr* HandlerPtr;
    uint32 ElemSize;
#if (DEMO_PRINT_METHOD == DEMO_PRINT_TOOLCHAIN)
    /* Initialize the function for used printf by toolchain */
#ifdef _ADS_C_THA6_
    __asm(".global __use_hlt_semihosting");
    _init_alloc(&s_printfBuffer[0], &s_printfBuffer[255]);
    _initio();
#endif /* _ADS_C_THA6_ */

#ifdef _IAR_C_THA6_

#endif /* _IAR_C_THA6_ */

#ifdef _GHS_C_THA6_

#endif /* _GHS_C_THA6_ */

#endif /* (DEMO_PRINT_METHOD != DEMO_NO_PRINT) */

    /* Demo Initialization */
    Mcu_Init(&Mcu_ConfigSet[0]);
    Mcu_InitClock(0);
    while(MCU_PLL_LOCKED != Mcu_GetPllStatus())
    {
        /* Waiting */
    }
    Mcu_DistributePllClock();
    
    Exception_GetIntVectorInfo(&HandlerPtr, &ElemSize);
    if (INTC_STA_INS_FINISHED != Intc_InstallInterrupt(&Intc_ConfigSet[0], HandlerPtr))
    {
        /* Install interrupt error */
        /* Dead code */
        while (1);
    }
    Port_Init(&Port_ConfigSet[0]);
    Gpt_Init(&Gpt_ConfigSet[0]);
#if (DEMO_PRINT_METHOD == DEMO_PRINT_UART)
    Uart_Init(&Uart_ConfigSet[0]);
#if ((STD_ON == DEMO_PRINTQUEUEMODE) && (STD_ON == DEMO_PRINTINTERRUPT))
    Gpt_EnableNotification(GptConf_GptChannelConfiguration_GptChannelConfiguration_6);
    Gpt_StartTimer(GptConf_GptChannelConfiguration_GptChannelConfiguration_6, 2500); /* 1000 = 2ms*/
#endif /* (STD_ON == DEMO_PRINTQUEUEMODE) && (STD_ON == DEMO_PRINTINTERRUPT) */
#endif /* (DEMO_PRINT_METHOD == DEMO_PRINT_UART) */
}
/****************************************************************************************************
*   Function Name           : DemoApp_Main
*
*   Service ID              : None.
*
*   Description             :
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
*   Preconditions           : None.
*
****************************************************************************************************/
void DemoApp_Main(void)
{
    char cmd;
    uint8 ModuleId;
        
    while(1)
    {
        PrintfMainMenu();

        cmd = DEBUG_GETC();
        if ((cmd >= 'a') && (cmd <= 'z'))
        {
            cmd -= 'a'- 'A';
        }

        for (ModuleId = 0U;
                ModuleId < (uint8)(sizeof(Demo_EntryList)/sizeof(Demo_EntryInfoType)); ModuleId ++)
        {
            if (cmd == Demo_EntryList[ModuleId].InputCmd)
            {
                Demo_EntryList[ModuleId].DemoEntryFuncPtr();
            }
        }
    }
}

/****************************************************************************************************
*   Function Name           : DemoApp_MainCore1
*
*   Service ID              : None.
*
*   Description             : Application demo for core1
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
*   Preconditions           : None.
*
****************************************************************************************************/
void DemoApp_MainCore1(void)
{
    uint8 ModuleId;
    Isr* HandlerPtr;
    uint32 ElemSize;

    /* Waiting for core0 initialization */
    while (Init_Process_Is_Ready == FALSE){}
    /* Installing the interrupts for core1 */
    Exception_GetIntVectorInfo(&HandlerPtr, &ElemSize);
    while (INTC_STA_INS_FINISHED != Intc_InstallInterrupt(&Intc_ConfigSet[0], HandlerPtr)){}

    while (1)
    {
        /* Core1 enabled */
        for (ModuleId = 0U;
                ModuleId < (uint8)(sizeof(Demo_EntryList)/sizeof(Demo_EntryInfoType)); ModuleId ++)
        {
            if (Demo_EntryList[ModuleId].DemoCore1FuncPtr != NULL_PTR)
            {
                Demo_EntryList[ModuleId].DemoCore1FuncPtr();
            }
        }

        Timer_DelayMs(100);

    }
}

#if (defined(MCAL_CFG_ENABLE_CORE2) && (MCAL_CFG_ENABLE_CORE2 == STD_ON))
/****************************************************************************************************
*   Function Name           : DemoApp_MainCore2
*
*   Service ID              : None.
*
*   Description             : Application demo for core2
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
*   Preconditions           : None.
*
****************************************************************************************************/
void DemoApp_MainCore2(void)
{
    uint8 ModuleId;
    Isr* HandlerPtr;
    uint32 ElemSize;

    /* Waiting for core0 initialization */
    while (Init_Process_Is_Ready == FALSE){}
    /* Installing the interrupts for core1 */
    Exception_GetIntVectorInfo(&HandlerPtr, &ElemSize);
    while (INTC_STA_INS_FINISHED != Intc_InstallInterrupt(&Intc_ConfigSet[0], HandlerPtr)){}

    while (1)
    {
        for (ModuleId = 0U;
                ModuleId < (uint8)(sizeof(Demo_EntryList)/sizeof(Demo_EntryInfoType)); ModuleId ++)
        {
            if (Demo_EntryList[ModuleId].DemoCore2FuncPtr != NULL_PTR)
            {
                Demo_EntryList[ModuleId].DemoCore2FuncPtr();
            }
        }

        Timer_DelayMs(100);
    }
}
#endif /* #if (defined(MCAL_CFG_ENABLE_CORE2) && (MCAL_CFG_ENABLE_CORE2 == STD_ON)) */

#if (defined(MCAL_CFG_ENABLE_CORE3) && (MCAL_CFG_ENABLE_CORE3 == STD_ON))
/****************************************************************************************************
*   Function Name           : DemoApp_MainCore3
*
*   Service ID              : None.
*
*   Description             : Application demo for core3
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
*   Preconditions           : None.
*
****************************************************************************************************/
void DemoApp_MainCore3(void)
{
    uint8 ModuleId;
    Isr* HandlerPtr;
    uint32 ElemSize;

    /* Waiting for core0 initialization */
    while (Init_Process_Is_Ready == FALSE){}
    /* Installing the interrupts for core1 */
    Exception_GetIntVectorInfo(&HandlerPtr, &ElemSize);
    while (INTC_STA_INS_FINISHED != Intc_InstallInterrupt(&Intc_ConfigSet[0], HandlerPtr)){}

    while (1)
    {
        for (ModuleId = 0U;
                ModuleId < (uint8)(sizeof(Demo_EntryList)/sizeof(Demo_EntryInfoType)); ModuleId ++)
        {
            if (Demo_EntryList[ModuleId].DemoCore3FuncPtr != NULL_PTR)
            {
                Demo_EntryList[ModuleId].DemoCore3FuncPtr();
            }
        }

        Timer_DelayMs(100);
    }
}
#endif /* #if (defined(MCAL_CFG_ENABLE_CORE3) && (MCAL_CFG_ENABLE_CORE3 == STD_ON)) */

#define DEMO_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Demo_MemMap.h"

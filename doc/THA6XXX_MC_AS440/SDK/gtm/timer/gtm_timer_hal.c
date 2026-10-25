/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_timebase_hal.c
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of TIMEBASE module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#gtm_timer_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#gtm_timer_hal_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core. Boolean can only be representes as uint8.
*
*#gtm_timer_hal_c_3:MISRAC2012-Rule-8.7;
* Justification: The module's API is exported for user's usage.
*
*#gtm_timer_hal_c_REF_4:CertC-DCL15-C;
* Justification: Reserved API for user access.
*
*#gtm_timer_hal_c_REF_5:CertC-DCL19-C;
* Justification: Reserved API for user access.
*
* #gtm_timer_hal_c_REF_6:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_timer_hal_c_REF_7:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #gtm_timer_hal_c_REF_8:MISRAC2012-Rule-8.7;
* Justification:The interface is called by the application layer.
*
*/
 /**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm_timer_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_timer_hal_c_REF_7 */
#define GPT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timer_hal_c_REF_6 */
#include "Gpt_MemMap.h"
#else
/* #Violation: gtm_timer_hal_c_REF_7 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timer_hal_c_REF_6 */
#include "Gtm_MemMap.h"
#endif

/* #Violation: gtm_timer_hal_c_REF_1 */
 boolean Gtm_Timer_Hal_InitChannel(const Gtm_Output_Driver *const pDriver, const Gtm_Timer_Config *const pConfig)
{
    GTM_OBP pTom;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    ret = TRUE;
    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);

    /* Initialize the timer part */
    ret &= Gtm_Tom_Std_SetClockSource(pTom, pDriver->channel, (uint8)pConfig->clk);
    ret &= Gtm_Tom_Std_SetTriggerOutput(pTom, pDriver->channel, (uint8)pConfig->trigOut);
    ret &= Gtm_Tom_Std_SetOneShotMode(pTom, pDriver->channel, pConfig->isOneShotEnable);

    /* Interrupt configuration */
    {
        Gtm_Tom_Std_ClearInterruptStatus(pTom, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0);
        /* CCU0 interrupt enabled */
        ret &= Gtm_Tom_Std_SetInterruptMode(pTom, pDriver->channel, pConfig->irqMode);
        ret &= Gtm_Tom_Std_SetInterrupt(pTom, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0, pConfig->isIrqEnable);
    }
    return ret;
}

/* #Violation: gtm_timer_hal_c_REF_1 */
void Gtm_Timer_Hal_DeinitChannel(const Gtm_Output_Driver *const pDriver)
{
    GTM_OBP pTgc;
    GTM_OBP pTom;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    pTgc = Gtm_Tom_Std_GetTgcPointer(pTom, pDriver->channel);
    Gtm_Tom_Std_ResetChannel(pTgc, pDriver->channel);
}

/* #Violation: gtm_timer_hal_c_REF_1 */
uint32 Gtm_Timer_Hal_GetChannelInfo(const Gtm_Output_Driver *const pDriver, Gtm_Timer_Count timeCount)
{
    uint32     value;
    boolean isOneShot, interruptStatus;
    GTM_C_OBP pTom;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);

    switch (timeCount)
    {
        case GTM_TIMER_COUNT_USED:
        {
            isOneShot = Gtm_Tom_Std_GetOneShotMode(pTom, pDriver->channel);
            interruptStatus = Gtm_Timer_Hal_GetInterruptStatus(pDriver);

            /* With oneshot mode and CN0 >= CM0 was detected, the timer is timeout */
            if ((FALSE != isOneShot) && (FALSE != interruptStatus))
            {
                value = Gtm_Tom_Std_GetCompareZero(pTom, pDriver->channel);
            }
            else
            {
                value = Gtm_Tom_Std_GetCounterValue(pTom, pDriver->channel);
            }
            break;
        }
        case GTM_TIMER_COUNT_REMAIN:
        {
            isOneShot = Gtm_Tom_Std_GetOneShotMode(pTom, pDriver->channel);
            interruptStatus = Gtm_Timer_Hal_GetInterruptStatus(pDriver);

            /* With oneshot mode and CN0 >= CM0 was detected, the timer is timeout */
            if ((FALSE != isOneShot) && (FALSE != interruptStatus))
            {
                value = 0;
            }
            else
            {
                value = Gtm_Tom_Std_GetCompareZero(pTom, pDriver->channel) - 
                                                    Gtm_Tom_Std_GetCounterValue(pTom, pDriver->channel);
            }
            break;
        }
        case GTM_TIMER_COUNT_PERIOD:
        {
            value = Gtm_Tom_Std_GetCompareZero(pTom, pDriver->channel);
            break;
        }
        default:
        {
            value = 0xFFFFFFFFU;
            break;
        }
    }

    return value;
}

/* #Violation: gtm_timer_hal_c_REF_1 */
boolean Gtm_Timer_Hal_StartChannel(const Gtm_Output_Driver *const pDriver, uint32 period)
{
    GTM_OBP pTgc;
    GTM_OBP pTom;
    boolean     oneShot;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)((0xFFFFU >= period)));
#endif

    ret = TRUE;
    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    pTgc = Gtm_Tom_Std_GetTgcPointer(pTom, pDriver->channel);
    Gtm_Tom_Std_ClearInterruptStatus(pTom, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0);
    ret &= Gtm_Tom_Std_SetCompareZero(pTom, pDriver->channel, period);
    ret &= Gtm_Tom_Std_SetChannel(pTgc, pDriver->channel, TRUE, TRUE);

    oneShot = Gtm_Tom_Std_GetOneShotMode(pTom, pDriver->channel);
    if (TRUE == oneShot)
    {
        Gtm_Tom_Std_SetCounterValue(pTom, pDriver->channel, 0U);
    }
    return ret;
}

/* #Violation: gtm_timer_hal_c_REF_1 */
boolean Gtm_Timer_Hal_StopChannel(const Gtm_Output_Driver *const pDriver)
{
    GTM_OBP pTgc;
    GTM_OBP pTom;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    ret = TRUE;
    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    pTgc = Gtm_Tom_Std_GetTgcPointer(pTom, pDriver->channel);
    ret &= Gtm_Tom_Std_SetChannel(pTgc, pDriver->channel, FALSE, TRUE);
    return ret;
}

/* #Violation: gtm_timer_hal_c_REF_1 */
void Gtm_Timer_Hal_SetCounterValue(const Gtm_Output_Driver *const pDriver, uint32 value)
{
    GTM_OBP pTom;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)((0xFFFFU >= value)));
#endif

    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    Gtm_Tom_Std_SetCounterValue(pTom, pDriver->channel, value);
}

/* #Violation: gtm_timer_hal_c_REF_1 */
uint32 Gtm_Timer_Hal_GetCounterValue(const Gtm_Output_Driver *const pDriver)
{
    GTM_C_OBP pTom;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    return Gtm_Tom_Std_GetCounterValue(pTom, pDriver->channel);
}

/* #Violation: gtm_timer_hal_c_REF_1 */
uint32 Gtm_Timer_Hal_GetCompareZero(const Gtm_Output_Driver *const pDriver)
{
    GTM_C_OBP pTom;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    return Gtm_Tom_Std_GetCompareZero(pTom, pDriver->channel);
}

/* #Violation: gtm_timer_hal_c_REF_1 */
boolean Gtm_Timer_Hal_SetInterrupt(const Gtm_Output_Driver *const pDriver, boolean enable)
{
    GTM_OBP pTom;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    ret = TRUE;
    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    Gtm_Tom_Std_ClearInterruptStatus(pTom, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0);
    ret &= Gtm_Tom_Std_SetInterrupt(pTom, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0, enable);
    return ret;
}

/* #Violation: gtm_timer_hal_c_REF_3 */
/* #Violation: gtm_timer_hal_c_REF_4 */
/* #Violation: gtm_timer_hal_c_REF_5 */
/* #Violation: gtm_timer_hal_c_REF_8 */
boolean Gtm_Timer_Hal_GetInterruptStatus(const Gtm_Output_Driver *const pDriver)
{
    boolean  ret;
    GTM_C_OBP pTom;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    ret = (boolean)Gtm_Tom_Std_GetInterruptStatus(pTom, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0);
    return ret;
}

/* #Violation: gtm_timer_hal_c_REF_1 */
boolean Gtm_Timer_Hal_GetInterruptEnableStatus(const Gtm_Output_Driver *const pDriver)
{
    boolean  ret;
    GTM_C_OBP pTom;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    ret = (boolean)Gtm_Tom_Std_GetInterruptEnableStatus(pTom, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0);
    return ret;
}

/* #Violation: gtm_timer_hal_c_REF_1 */
void Gtm_Timer_Hal_ClearInterruptStatus(const Gtm_Output_Driver *const pDriver)
{
    GTM_OBP pTom;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_TOM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_TOM_NUM));
    /* #Violation: gtm_timer_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_TOM_CH_NUM));
#endif

    pTom = Gtm_Tom_Std_GetTomPointer(pDriver->moduleIndex);
    Gtm_Tom_Std_ClearInterruptStatus(pTom, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0);
}

#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_timer_hal_c_REF_7 */
#define GPT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timer_hal_c_REF_6 */
#include "Gpt_MemMap.h"
#else
/* #Violation: gtm_timer_hal_c_REF_7 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timer_hal_c_REF_6 */
#include "Gtm_MemMap.h"
#endif
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

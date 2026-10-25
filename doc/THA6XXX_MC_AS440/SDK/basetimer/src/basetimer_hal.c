/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: basetimer_hal.c
 * Author:   01030
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: This file contains functions to initialize and operate the base  timer.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #basetimer_hal_c_REF_1:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core, Boolean can only be represents as uint8.
*
* #basetimer_hal_c_REF_2:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #basetimer_hal_c_REF_3:MISRAC2012-Rule-19.2;
* Justification:Define a union type to assign a one-time value to a register.
*
* #basetimer_hal_c_REF_4:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #basetimer_hal_c_REF_5:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
* #basetimer_hal_c_REF_6:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #basetimer_hal_c_REF_7:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*/
/**********************************************************************************************************************
 *                                                     Includes                                                       *
 *********************************************************************************************************************/
#include "common_hal.h"
#include "basetimer_hal.h"
#include "basetimer_register.h"
#include "Platform_Types.h"

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
/* #Violation: basetimer_hal_c_REF_7 */
#define BASETIMER_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: basetimer_hal_c_REF_6 */
#include "Basetimer_MemMap.h"

/* #Violation: basetimer_hal_c_REF_2 */
void Basetimer_Hal_InitModule(BASETIMER_MODULE *const pTimer, const Basetimer_InitConfig *const pConfig)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: basetimer_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: basetimer_hal_c_REF_4 */
    /* #Violation: basetimer_hal_c_REF_5 */
    Assert(((boolean)(CHECK_BASETIMER_BASE(pTimer))));
#endif

    /* Configure the control register to select the timer operation mode and other parameters */
    /* #Violation: basetimer_hal_c_REF_3 */
    BASETIMER_CTRL ctrlData;
    /* #Violation: basetimer_hal_c_REF_2 */
    ctrlData.U = 0U;
    /* Counter Size */
    ctrlData.B.SIZE = (uint32)pConfig->size;
    /* Counter Mode */
    if(BASETIMER_MODE_ONESHOT != pConfig->mode)
    {
        ctrlData.B.ONESHOT = 0U;
        if(BASETIMER_MODE_FREERUNNING == pConfig->mode)
        {
            ctrlData.B.MODE = 0U;
        }
        else
        {
            ctrlData.B.MODE = 1U;
        }
    }
    else
    {
        ctrlData.B.ONESHOT = 1U;
    }
    /* Disable the timer */
    ctrlData.B.EN = 0U;
    pTimer->CTRL.U = ctrlData.U;

    /* Set the initial value of the timer */
    pTimer->LOAD = pConfig->load;
    /* Clear the status register to ensure that the timer is in normal operation */
    pTimer->CLR.B.CLR = 1U;
}

/* #Violation: basetimer_hal_c_REF_2 */
void Basetimer_Hal_SetInterrupt(BASETIMER_MODULE *const pTimer, boolean enable)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: basetimer_hal_c_REF_4 */
    /* #Violation: basetimer_hal_c_REF_5 */
    Assert(((boolean)(CHECK_BASETIMER_BASE(pTimer))));
#endif

    /* Set interrupt enable/disable */
    pTimer->CTRL.B.INTEN = enable;
}

/* #Violation: basetimer_hal_c_REF_2 */
uint32 Basetimer_Hal_GetRemainingCount(const BASETIMER_MODULE *const pTimer)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: basetimer_hal_c_REF_4 */
    /* #Violation: basetimer_hal_c_REF_5 */
    Assert(((boolean)(CHECK_BASETIMER_BASE(pTimer))));
#endif

    /* Return current count */
    return pTimer->VALUE;
}

/* #Violation: basetimer_hal_c_REF_2 */
uint32 Basetimer_Hal_GetElapsedCount(const BASETIMER_MODULE *const pTimer)
{
    uint32 timerLoad;
    uint32 timerValue;
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: basetimer_hal_c_REF_4 */
    /* #Violation: basetimer_hal_c_REF_5 */
    Assert(((boolean)(CHECK_BASETIMER_BASE(pTimer))));
#endif

    /* Return remaining count */
    timerLoad = (uint32)pTimer->LOAD;
    timerValue = (uint32)pTimer->VALUE;
    return (timerLoad - timerValue);
}

/* #Violation: basetimer_hal_c_REF_2 */
void Basetimer_Hal_Reload(BASETIMER_MODULE *const pTimer, uint32 reload)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: basetimer_hal_c_REF_4 */
    /* #Violation: basetimer_hal_c_REF_5 */
    Assert(((boolean)(CHECK_BASETIMER_BASE(pTimer))));
#endif

    /* Write reload value to background load register */
    pTimer->BGLOAD = reload;
}

/* #Violation: basetimer_hal_c_REF_2 */
void Basetimer_Hal_StopTimer(BASETIMER_MODULE *const pTimer)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: basetimer_hal_c_REF_4 */
    /* #Violation: basetimer_hal_c_REF_5 */
    Assert(((boolean)(CHECK_BASETIMER_BASE(pTimer))));
#endif

    /* Disable timer by clearing enable bit in CTRL register */
    pTimer->CTRL.B.EN = 0U;
}

/* #Violation: basetimer_hal_c_REF_2 */
void Basetimer_Hal_StartTimer(BASETIMER_MODULE *const pTimer)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: basetimer_hal_c_REF_4 */
    /* #Violation: basetimer_hal_c_REF_5 */
    Assert(((boolean)(CHECK_BASETIMER_BASE(pTimer))));
#endif

    /* Enable timer by setting enable bit in CTRL register */
    pTimer->CTRL.B.EN = 1U;
}

/* #Violation: basetimer_hal_c_REF_2 */
void Basetimer_Hal_ClearFlag(BASETIMER_MODULE *const pTimer)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: basetimer_hal_c_REF_4 */
    /* #Violation: basetimer_hal_c_REF_5 */
    Assert(((boolean)(CHECK_BASETIMER_BASE(pTimer))));
#endif

    /* Clear status register */
    pTimer->CLR.B.CLR = 1U;
}

/* #Violation: basetimer_hal_c_REF_2 */
void Basetimer_Hal_SetLoad(BASETIMER_MODULE *const pTimer, uint32 loadValue)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: basetimer_hal_c_REF_4 */
    /* #Violation: basetimer_hal_c_REF_5 */
    Assert(((boolean)(CHECK_BASETIMER_BASE(pTimer))));
#endif

    /* Set the initial value of the timer */
    pTimer->LOAD = loadValue;
}


/* #Violation: basetimer_hal_c_REF_7 */
#define BASETIMER_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: basetimer_hal_c_REF_6 */
#include "Basetimer_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File                                                    *
 *********************************************************************************************************************/

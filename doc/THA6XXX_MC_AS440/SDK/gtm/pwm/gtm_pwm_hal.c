/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_pwm_hal.c
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of PWM module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_pwm_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
* #gtm_pwm_hal_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core. Boolean can only be representes as uint8.
*
* #gtm_pwm_hal_c_REF_3:CertC-DCL06_C;
* Justification: The Tresos-generated code does not use symbolic constants for buffer size substitution.
*
* #gtm_pwm_hal_c_REF_4:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_pwm_hal_c_REF_5:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
 /**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm_pwm_hal.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
#define PWM_MODULE_NUM    (2U)

typedef GTM_OBP (*Pfn_GetDevPointer)(uint8 devIndex);
typedef boolean (*Pfn_SetChannel)(GTM_OBP_C pTgc, uint8 channel, boolean enable, boolean immediate);
typedef uint32 (*Pfn_Channel_GetCounterValue)(GTM_C_OBP_C pDev, uint8 channel);
typedef void (*Pfn_Channel_SetCounterValue)(GTM_OBP_C pDev, uint8 channel, uint32 value);
typedef boolean (*Pfn_Channel_SetShadowZero)(GTM_OBP_C pDev, uint8 channel, uint32 shadowZero);
typedef boolean (*Pfn_Channel_SetCompareZero)(GTM_OBP_C pDev, uint8 channel, uint32 compareZero);
typedef boolean (*Pfn_Channel_SetShadowOne)(GTM_OBP_C pDev, uint8 channel, uint32 shadowOne);
typedef boolean (*Pfn_Channel_SetCompareOne)(GTM_OBP_C pDev, uint8 channel, uint32 compareOne);
typedef uint32 (*Pfn_Channel_GetCompareZero)(GTM_C_OBP_C pDev, uint8 channel);
typedef Gtm_SignalState (*Pfn_Channel_GetSignalLevel)(GTM_C_OBP_C pDev, uint8 channel);
typedef Gtm_SignalState (*Pfn_Channel_GetOutputLevel)(GTM_C_OBP_C pDev, uint8 channel);
typedef GTM_OBP (*Pfn_Channel_GetTgcPointer)(GTM_OBP_C pDev, uint8 channel);
typedef boolean (*Pfn_SetChannelsOutput)(GTM_OBP_C pTgc, uint16 mask, boolean immediate);
typedef boolean (*Pfn_Channel_SetCompareZeroOne)(GTM_OBP_C pDev, uint8 channel, uint32 cm0, uint32 cm1);
typedef boolean (*Pfn_Channel_SetCompareZeroOneShadow)(GTM_OBP_C pDev, uint8 channel, uint32 sr0, uint32 sr1);
typedef void (*Pfn_Channel_ClearInterruptStatus)(GTM_OBP_C pDev, uint8 channel, uint8 irq);
typedef boolean (*Pfn_Channel_SetInterrupt)(GTM_OBP_C pDev, uint8 channel, uint8 irq, boolean enable);
typedef boolean (*Pfn_SetChannelFreeze)(GTM_OBP_C pDev, uint8 channel, boolean enable);
typedef boolean (*Pfn_Channel_SetSignalLevel)(GTM_OBP_C pDev, uint8 channel, Gtm_SignalState activeState);
typedef boolean (*Pfn_Channel_SetSignalLevelShadow)(GTM_OBP_C pDev, uint8 channel, Gtm_SignalState activeState);
typedef boolean (*Pfn_SetChannelOutput)(GTM_OBP_C pTgc, uint8 channel, boolean enable, boolean immediate);
typedef boolean (*Pfn_SetChannelUpdate)(GTM_OBP_C pTgc, uint8 channel, boolean enable);
typedef boolean (*Pfn_Channel_SetClockSource)(GTM_OBP_C pDev, uint8 channel, uint8 clk);
typedef boolean (*Pfn_Channel_SetClockSourceShadow)(GTM_OBP_C pDev, uint8 channel, uint8 clk);
typedef boolean (*Pfn_Channel_SetTriggerOutput)(GTM_OBP_C pDev, uint8 channel, uint8 trigger);
typedef boolean (*Pfn_Channel_SetCounterRstSrc)(GTM_OBP_C pDev, uint8 channel, uint8 event);
typedef uint8 (*Pfn_Channel_GetCounterRstSrc)(GTM_C_OBP_C pDev, uint8 channel);
typedef boolean (*Pfn_Channel_SetInterruptMode)(GTM_OBP_C pDev, uint8 channel, Gtm_IrqMode mode);
typedef boolean (*Pfn_SetChannelMode)(GTM_OBP_C pDev, uint8 channel, Gtm_Atom_Mode mode);
typedef uint32 (*Pfn_Channel_GetInterruptStatus)(GTM_C_OBP_C pDev, uint8 channel, uint8 irq);
typedef uint32 (*Pfn_Channel_GetInterruptEnableStatus)(GTM_C_OBP_C pDev, uint8 channel, uint8 irq);
typedef void (*Pfn_Channel_ResetChannel)(GTM_OBP_C pTgc, uint8 channel);
typedef void (*Pfn_SetChannelHres)(GTM_OBP_C pDev, uint8 channel, boolean enable);
typedef boolean (*Pfn_GetChannelHres)(GTM_C_OBP_C pDev, uint8 channel);
typedef boolean (*Pfn_Channel_SetCountMode)(GTM_OBP_C pDev, uint8 channel, uint32 mode);
typedef void (*Pfn_Channel_SetHostTrig)(GTM_OBP_C pTgc);
typedef boolean (*Pfn_Channel_SetForceUpdate)(GTM_OBP_C pTgc, uint8 channel, boolean enable);


/* Ouput Dev(TOM/ATOM) Class */
typedef struct
{
    Pfn_GetDevPointer                   fnGetDevPointer;        /* Gets the TOM/ATOM pointer */
    Pfn_SetChannel                      fnSetChannel;           /* Enable/disable one channel */
    Pfn_Channel_GetCounterValue         fnGetCounterValue;      /* Gets the counter value */
    Pfn_Channel_SetCounterValue         fnSetCounterValue;      /* Sets the counter value */
    Pfn_Channel_SetShadowZero           fnSetShadowZero;        /* Sets the compare zero shadow value */
    Pfn_Channel_SetCompareZero          fnSetCompareZero;       /* Sets the compare zero value */
    Pfn_Channel_SetShadowOne            fnSetShadowOne;         /* Sets the compare one shadow value */
    Pfn_Channel_SetCompareOne           fnSetCompareOne;        /* Sets the compare one value */
    Pfn_Channel_GetCompareZero          fnGetCompareZero;       /* Gets the compare zero value */
    Pfn_Channel_GetSignalLevel          fnGetSignalLevel;       /* Gets the signal level */
    Pfn_Channel_SetSignalLevel          fnSetSignalLevel;       /* Sets the signal level */
    Pfn_Channel_SetSignalLevelShadow    fnSetSignalLevelShadow; /* Sets the shadow signal level */
    Pfn_Channel_GetOutputLevel          fnGetOutputLevel;       /* Gets the output level */
    Pfn_Channel_GetTgcPointer           fnGetTgcPointer;        /* Gets the TGC/AGC pointer */
    Pfn_SetChannelsOutput               fnSetChannelsOutput;    /* Enable/disable one or more channels output */
    Pfn_Channel_SetCompareZeroOne       fnSetCompareZeroOne;    /* Sets the compare zero and compare one value */
    Pfn_Channel_SetCompareZeroOneShadow fnSetCompareZeroOneShadow;  /* Sets the compare zero and compare one 
                                                                      shadow value */
    Pfn_Channel_ClearInterruptStatus    fnClearInterruptStatus;     /* Clears the channel interrupt status */
    Pfn_Channel_SetInterrupt            fnSetInterrupt;         /* Enable/disable the channel specific/all interrupt */
    Pfn_Channel_SetInterruptMode        fnSetInterruptMode;     /* Sets the channel interrupt mode */
    Pfn_Channel_GetInterruptStatus      fnGetInterruptStatus;   /* Gets the channel interrupt status */
    Pfn_Channel_GetInterruptEnableStatus fnGetInterruptEnableStatus; /*Gets the channel interrupt enable status*/
    Pfn_SetChannelFreeze                fnSetChannelFreeze;     /* Enable/disable channel freeze */
    Pfn_SetChannelOutput                fnSetChannelOutput;     /* Enable/disable one channel output */
    Pfn_SetChannelUpdate                fnSetChannelUpdate;     /* Enable/disable one channel for update */
    Pfn_Channel_SetClockSource          fnSetClockSource;       /* Sets the channel clock source */
    Pfn_Channel_SetClockSourceShadow    fnSetClockSourceShadow; /* Sets the channel shadow clock source */
    Pfn_Channel_SetTriggerOutput        fnSetTriggerOutput;     /* Sets the channel trigger output */
    Pfn_Channel_SetCounterRstSrc        fnSetCounterRstSrc;     /* Sets the channel counter reset source */
    Pfn_Channel_GetCounterRstSrc        fnGetCounterRstSrc;     /* Gets the channel counter reset source */
    Pfn_Channel_ResetChannel            fnResetChannel;         /* Reset the channel */
    Pfn_SetChannelMode                  fnSetChannelMode;       /* Sets the Atom operating mode */
    Pfn_SetChannelHres                  fnSetChannelHres;       /* Enable/disable channel high resolution */
    Pfn_GetChannelHres                  fnGetChannelHres;       /* Get the channel high resolution enable status */
    Pfn_Channel_SetCountMode            fnSetCountMode;         /* Sets the channel count mode */
    Pfn_Channel_SetHostTrig             fnSetHostTrig;          /* Sets the host trigger */
    Pfn_Channel_SetForceUpdate          fnSetForceUpdate;       /* Sets the force update */
    uint32                              maxCNValue;             /* The max counter(CN/CM) value for the dev */
} Gtm_Output_Dev_Class;

#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_pwm_hal_c_REF_5 */
#define PWM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: gtm_pwm_hal_c_REF_4 */
#include "Pwm_MemMap.h"
#else
/* #Violation: gtm_pwm_hal_c_REF_5 */
#define GTM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: gtm_pwm_hal_c_REF_4 */
#include "Gtm_MemMap.h"
#endif

/* #Violation: gtm_pwm_hal_c_REF_3 */
static const Gtm_Output_Dev_Class s_pwmOutputDevs[PWM_MODULE_NUM] =
{
    [GTM_OUTPUT_MODULE_TOM] = {
        .fnGetDevPointer             = Gtm_Tom_Std_GetTomPointer,
        .fnSetChannel                = Gtm_Tom_Std_SetChannel,
        .fnGetCounterValue            = Gtm_Tom_Std_GetCounterValue,
        .fnSetCounterValue          = Gtm_Tom_Std_SetCounterValue,
        .fnSetShadowZero            = Gtm_Tom_Std_SetShadowZero,
        .fnSetCompareZero           = Gtm_Tom_Std_SetCompareZero,
        .fnSetShadowOne             = Gtm_Tom_Std_SetShadowOne,
        .fnSetCompareOne            = Gtm_Tom_Std_SetCompareOne,
        .fnGetCompareZero           = Gtm_Tom_Std_GetCompareZero,
        .fnGetSignalLevel           = Gtm_Tom_Std_GetSignalLevel,
        .fnGetOutputLevel           = Gtm_Tom_Std_GetOutputLevel,
        .fnGetTgcPointer            = Gtm_Tom_Std_GetTgcPointer,
        .fnSetChannelsOutput        = Gtm_Tom_Std_SetChannelsOutput,
        .fnSetCompareZeroOne        = Gtm_Tom_Std_SetCompareZeroOne,
        .fnSetCompareZeroOneShadow  = Gtm_Tom_Std_SetCompareZeroOneShadow,
        .fnClearInterruptStatus     = Gtm_Tom_Std_ClearInterruptStatus,
        .fnSetInterrupt             = Gtm_Tom_Std_SetInterrupt,
        .fnSetInterruptMode         = Gtm_Tom_Std_SetInterruptMode,
        .fnGetInterruptStatus       = Gtm_Tom_Std_GetInterruptStatus,
        .fnGetInterruptEnableStatus = Gtm_Tom_Std_GetInterruptEnableStatus,
        .fnSetChannelFreeze         = Gtm_Tom_Std_SetChannelFreeze,
        .fnSetSignalLevel           = Gtm_Tom_Std_SetSignalLevel,
        .fnSetSignalLevelShadow     = Gtm_Tom_Std_SetSignalLevelShadow,
        .fnSetChannelOutput         = Gtm_Tom_Std_SetChannelOutput,
        .fnSetChannelUpdate         = Gtm_Tom_Std_SetChannelUpdate,
        .fnSetClockSource           = Gtm_Tom_Std_SetClockSource,
        .fnSetClockSourceShadow     = Gtm_Tom_Std_SetClockSourceShadow,
        .fnSetTriggerOutput         = Gtm_Tom_Std_SetTriggerOutput,
        .fnSetCounterRstSrc         = Gtm_Tom_Std_SetCounterRstSrc,
        .fnGetCounterRstSrc         = Gtm_Tom_Std_GetCounterRstSrc,
        .fnResetChannel             = Gtm_Tom_Std_ResetChannel,
        .fnSetChannelHres           = NULL_PTR,
        .fnGetChannelHres           = NULL_PTR,
        .fnSetChannelMode           = NULL_PTR,
        .fnSetCountMode             = Gtm_Tom_Std_SetCountMode,
        .fnSetHostTrig              = Gtm_Tom_Std_SetHostTrig,
        .fnSetForceUpdate           = Gtm_Tom_Std_SetForceUpdate,
        .maxCNValue                 = 0xFFFFU,
    },
    [GTM_OUTPUT_MODULE_ATOM] = {
        .fnGetDevPointer             = Gtm_Atom_Std_GetAtomPointer,
        .fnSetChannel                = Gtm_Atom_Std_SetChannel,
        .fnGetCounterValue            = Gtm_Atom_Std_GetCounterValue,
        .fnSetCounterValue          = Gtm_Atom_Std_SetCounterValue,
        .fnSetShadowZero            = Gtm_Atom_Std_SetShadowZero,
        .fnSetCompareZero           = Gtm_Atom_Std_SetCompareZero,
        .fnSetShadowOne             = Gtm_Atom_Std_SetShadowOne,
        .fnSetCompareOne            = Gtm_Atom_Std_SetCompareOne,
        .fnGetCompareZero           = Gtm_Atom_Std_GetCompareZero,
        .fnGetSignalLevel           = Gtm_Atom_Std_GetSignalLevel,
        .fnGetOutputLevel           = Gtm_Atom_Std_GetOutputLevel,
        .fnGetTgcPointer            = Gtm_Atom_Std_GetAgcPointer,
        .fnSetChannelsOutput        = Gtm_Atom_Std_SetChannelsOutput,
        .fnSetCompareZeroOne        = Gtm_Atom_Std_SetCompareZeroOne,
        .fnSetCompareZeroOneShadow  = Gtm_Atom_Std_SetCompareZeroOneShadow,
        .fnClearInterruptStatus     = Gtm_Atom_Std_ClearInterruptStatus,
        .fnSetInterrupt             = Gtm_Atom_Std_SetInterrupt,
        .fnSetInterruptMode         = Gtm_Atom_Std_SetInterruptMode,
        .fnGetInterruptStatus       = Gtm_Atom_Std_GetInterruptStatus,
        .fnGetInterruptEnableStatus = Gtm_Atom_Std_GetInterruptEnableStatus,
        .fnSetChannelFreeze         = Gtm_Atom_Std_SetChannelFreeze,
        .fnSetSignalLevel           = Gtm_Atom_Std_SetSignalLevel,
        .fnSetSignalLevelShadow     = Gtm_Atom_Std_SetSignalLevelShadow,
        .fnSetChannelOutput         = Gtm_Atom_Std_SetChannelOutput,
        .fnSetChannelUpdate         = Gtm_Atom_Std_SetChannelUpdate,
        .fnSetClockSource           = Gtm_Atom_Std_SetClockSource,
        .fnSetClockSourceShadow     = Gtm_Atom_Std_SetClockSourceShadow,
        .fnSetTriggerOutput         = Gtm_Atom_Std_SetTriggerOutput,
        .fnSetCounterRstSrc         = Gtm_Atom_Std_SetCounterRstSrc,
        .fnGetCounterRstSrc         = Gtm_Atom_Std_GetCounterRstSrc,
        .fnResetChannel             = Gtm_Atom_Std_ResetChannel,
        .fnSetChannelHres           = NULL_PTR,
        .fnGetChannelHres           = NULL_PTR,
        .fnSetChannelMode           = Gtm_Atom_Std_SetChannelMode,
        .fnSetCountMode             = Gtm_Atom_Std_SetCountMode,
        .fnSetHostTrig              = Gtm_Atom_Std_SetHostTrig,
        .fnSetForceUpdate           = Gtm_Atom_Std_SetForceUpdate,
        .maxCNValue                 = 0xFFFFFFU,
    }
};
#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_pwm_hal_c_REF_5 */
#define PWM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: gtm_pwm_hal_c_REF_4 */
#include "Pwm_MemMap.h"
#else
/* #Violation: gtm_pwm_hal_c_REF_5 */
#define GTM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: gtm_pwm_hal_c_REF_4 */
#include "Gtm_MemMap.h"
#endif
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_pwm_hal_c_REF_5 */
#define PWM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_pwm_hal_c_REF_4 */
#include "Pwm_MemMap.h"
#else
/* #Violation: gtm_pwm_hal_c_REF_5 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_pwm_hal_c_REF_4 */
#include "Gtm_MemMap.h"
#endif

#if (STD_ON == INPUT_ARG_DETECT)
/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_CheckModuleIndex
 * Description:  Check PWM parameters
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        module: GTM submodule (0:TOM, 1:ATOM)
 *               moduleIndex: Submodule index
 *               channel: Channel number
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the parameters are correctly
 *                        TRUE:  The parameter check is correct
 *                        FALSE: The parameter check is incorrect

 * Others:       None
 * History:
 * Date          Author    Modified
 * 2025/03/10    01031      Create
 *********************************************************************************************************************/
static boolean Gtm_Pwm_Hal_CheckModuleIndex(uint8 module, uint8 moduleIndex, uint8 channel);
#endif
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
#if (STD_ON == INPUT_ARG_DETECT)
static boolean Gtm_Pwm_Hal_CheckModuleIndex(uint8 module, uint8 moduleIndex, uint8 channel)
{
    boolean ret;

    if ((0U == module) && (moduleIndex < GTM_TOM_NUM) && (channel < GTM_TOM_CH_NUM))
    {
        ret = TRUE;
    }
    else if ((1U == module) && (moduleIndex < GTM_ATOM_NUM) && (channel < GTM_ATOM_CH_NUM))
    {
        ret = TRUE;
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}
#endif
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
 /* #Violation: gtm_pwm_hal_c_REF_1 */
boolean Gtm_Pwm_Hal_InitChannel(const Gtm_Output_Driver *const pDriver, const Gtm_Pwm_Config *const pConfig)
{
    GTM_OBP pDev;
    GTM_OBP pXgc;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)((s_pwmOutputDevs[pDriver->module].maxCNValue >= pConfig->period) && 
                     (s_pwmOutputDevs[pDriver->module].maxCNValue >= pConfig->dutyCycle) &&
                     (s_pwmOutputDevs[pDriver->module].maxCNValue >= pConfig->phase)));
#endif

    ret = TRUE;
    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    pXgc = s_pwmOutputDevs[pDriver->module].fnGetTgcPointer(pDev, pDriver->channel);

    /* Reset the channel */
    s_pwmOutputDevs[pDriver->module].fnResetChannel(pXgc, pDriver->channel);

    /* Disable channels */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannel(pXgc, pDriver->channel, FALSE, TRUE);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannelOutput(pXgc, pDriver->channel, FALSE, TRUE);

    /* Set clock source */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetClockSourceShadow(pDev, pDriver->channel, (uint8)(pConfig->clk));
    /* Set signal level */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetSignalLevelShadow(pDev, pDriver->channel, pConfig->signalLevel);

    /* ATOM SOMP mode */
    if (NULL_PTR != s_pwmOutputDevs[pDriver->module].fnSetChannelMode)
    {
        ret &= s_pwmOutputDevs[pDriver->module].fnSetChannelMode(pDev, pDriver->channel, GTM_ATOM_MODE_OUTPUTPWM);
    }

    /* Set count mode */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetCountMode(pDev, pDriver->channel, (uint32)pConfig->countMode);

    /* Set trigger out */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetTriggerOutput(pDev, pDriver->channel, (uint8)pConfig->trigOut);

    /* Set counter reset source */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetCounterRstSrc(pDev, pDriver->channel, (uint8)pConfig->resetSource);

    /* enable and initialize interrupts if chosen */
    s_pwmOutputDevs[pDriver->module].fnClearInterruptStatus(pDev, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_ALL);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetInterruptMode(pDev, pDriver->channel, pConfig->interrupt.mode);
    if (GTM_SIGNALSTATE_HIGH == pConfig->signalLevel)
    {
        ret &= s_pwmOutputDevs[pDriver->module].fnSetInterrupt(pDev, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0,
                                                                                    pConfig->interrupt.isRiseEnabled);
        ret &= s_pwmOutputDevs[pDriver->module].fnSetInterrupt(pDev, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU1,
                                                                                    pConfig->interrupt.isFallEnabled);
    }
    else
    {
        ret &= s_pwmOutputDevs[pDriver->module].fnSetInterrupt(pDev, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU0,
                                                                                    pConfig->interrupt.isFallEnabled);
        ret &= s_pwmOutputDevs[pDriver->module].fnSetInterrupt(pDev, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_CCU1,
                                                                                    pConfig->interrupt.isRiseEnabled);
    }

    if (0U != pConfig->phase)
    {
        s_pwmOutputDevs[pDriver->module].fnSetCounterValue(pDev, pDriver->channel, pConfig->phase);
    }

    (void)pConfig->hresConfig.isHresEnabled;  /* QAC */
    (void)pConfig->hresConfig.hresPeriod;     /* QAC */
    (void)pConfig->hresConfig.hresPulseWidth; /* QAC */

    /* Set period and duty-cycle */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowOne(pDev, pDriver->channel, pConfig->dutyCycle);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowZero(pDev, pDriver->channel, pConfig->period);

    /* Hold output level */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannelFreeze(pDev, pDriver->channel, TRUE);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannelOutput(pXgc, pDriver->channel, TRUE, TRUE);

    /* Set update mechanism */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannelUpdate(pXgc, pDriver->channel, pConfig->isSyncUpdateEnabled);

    /* Update SR0/SR1/SL_SR/CLK_SRC_SR to CM0/CM1/SL/CLK_SRC */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetForceUpdate(pXgc, pDriver->channel, TRUE);
    s_pwmOutputDevs[pDriver->module].fnSetHostTrig(pXgc);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetForceUpdate(pXgc, pDriver->channel, FALSE);

    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannel(pXgc, pDriver->channel, pConfig->isChannelEnable, FALSE);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannelOutput(pXgc, pDriver->channel, pConfig->isOutputEnable, FALSE);
    if (TRUE == pConfig->isImmediate)
    {
        s_pwmOutputDevs[pDriver->module].fnSetHostTrig(pXgc);
    }
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannelFreeze(pDev, pDriver->channel, FALSE);
    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
boolean Gtm_Pwm_Hal_DeinitChannel(const Gtm_Output_Driver *const pDriver, Gtm_SignalState idleLevel)
{
    Gtm_SignalState signalLevel;

    GTM_OBP pDev;
    GTM_OBP pXgc;
    boolean ret;
#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
#endif

    ret = TRUE;
    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    pXgc = s_pwmOutputDevs[pDriver->module].fnGetTgcPointer(pDev, pDriver->channel);
    s_pwmOutputDevs[pDriver->module].fnClearInterruptStatus(pDev, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_ALL);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetInterrupt(pDev, pDriver->channel, (uint8)GTM_TOM_IRQTYPE_ALL, FALSE);

    /* Sets the signal level based on the IDLE state */
    if (GTM_SIGNALSTATE_HIGH == idleLevel)
    {
        signalLevel = GTM_SIGNALSTATE_LOW;
    }
    else
    {
        signalLevel = GTM_SIGNALSTATE_HIGH;
    }
    ret &= s_pwmOutputDevs[pDriver->module].fnSetSignalLevelShadow(pDev, pDriver->channel, signalLevel);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetSignalLevel(pDev, pDriver->channel, signalLevel);

    /* Disable the output */
    /* When the output is disabled, the output signals are the inverse value of the SL bit.*/
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannelOutput(pXgc, pDriver->channel, FALSE, TRUE);
    /* Disable the channel */
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannel(pXgc, pDriver->channel, FALSE, TRUE);
    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
boolean Gtm_Pwm_Hal_SetPeriod(const Gtm_Output_Driver *const pDriver, uint32 period, boolean syncUpdate)
{
    GTM_OBP pDev;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(s_pwmOutputDevs[pDriver->module].maxCNValue >= period));
#endif

    ret = TRUE;
    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);

    if (TRUE == syncUpdate)
    {
        ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowZero(pDev, pDriver->channel, period);
    }
    else
    {
        ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareZero(pDev, pDriver->channel, period);
    }

    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
boolean Gtm_Pwm_Hal_SetDutyCycle(const Gtm_Output_Driver *const pDriver, uint32 dutyCycle, boolean syncUpdate)
{
    GTM_OBP pDev;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(s_pwmOutputDevs[pDriver->module].maxCNValue >= dutyCycle));
#endif

    ret = TRUE;
    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);

    if (TRUE == syncUpdate)
    {
        ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowOne(pDev, pDriver->channel, dutyCycle);
    }
    else
    {
        ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareOne(pDev, pDriver->channel, dutyCycle);
    }

    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
boolean Gtm_Pwm_Hal_SetIdleLevel(const Gtm_Output_Driver *const pDriver, Gtm_SignalState idleLevel)
{
    Gtm_SignalState signalLevel;
    uint32 period;
    uint8  rstSrc;
    GTM_OBP pDev;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
#endif

    ret = TRUE;
    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    /* Get signal level */
    signalLevel = s_pwmOutputDevs[pDriver->module].fnGetSignalLevel(pDev, pDriver->channel);
    rstSrc = s_pwmOutputDevs[pDriver->module].fnGetCounterRstSrc(pDev, pDriver->channel);

    /* Sets output level to IDLE state */
    /* Output is !TOM[i]_CH[x]_CTRL.SL (i.e. 0% duty cycle PWM signal) */
    /* Output is TOM[i]_CH[x]_CTRL.SL (i.e. 100% duty cycle PWM signal) */
    /* The hardware ensures that for both 0% and 100% duty cycle no glitch occurs at the output of the TOM channel. */
    if (0U == ((uint8)signalLevel ^ (uint8)idleLevel))
    {
        /* For 100% duty cycle */
        if ((uint8)GTM_PWM_RESETEVENT_ONCM0 == rstSrc)
        {
            period = s_pwmOutputDevs[pDriver->module].fnGetCompareZero(pDev, pDriver->channel);
            ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowOne(pDev, pDriver->channel, period);
            ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareOne(pDev, pDriver->channel, period);
        }
        else
        {
            ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowZero(pDev, pDriver->channel, 2U);
            ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareZero(pDev, pDriver->channel, 2U);
            ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowOne(pDev, pDriver->channel,
                                                            s_pwmOutputDevs[pDriver->module].maxCNValue);
            ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareOne(pDev, pDriver->channel,
                                                            s_pwmOutputDevs[pDriver->module].maxCNValue);
        }
    }
    else
    {
        /* For 0% duty cycle */
        if ((uint8)GTM_PWM_RESETEVENT_ONCM0 == rstSrc)
        {
            ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowOne(pDev, pDriver->channel, 0U);
            ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareOne(pDev, pDriver->channel, 0U);
        }
        else
        {
            ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowZero(pDev, pDriver->channel,
                                                             s_pwmOutputDevs[pDriver->module].maxCNValue);
            ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareZero(pDev, pDriver->channel,
                                                             s_pwmOutputDevs[pDriver->module].maxCNValue);
            ret &= s_pwmOutputDevs[pDriver->module].fnSetShadowOne(pDev, pDriver->channel, 0U);
            ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareOne(pDev, pDriver->channel, 0U);
        }
    }
    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
Gtm_SignalState Gtm_Pwm_Hal_GetOutputLevel(const Gtm_Output_Driver *const pDriver)
{
    Gtm_SignalState    ret;
    GTM_C_OBP pDev;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
#endif

    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    ret  = s_pwmOutputDevs[pDriver->module].fnGetOutputLevel(pDev, pDriver->channel);

    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
boolean Gtm_Pwm_Hal_SetInterrupt(const Gtm_Output_Driver *const pDriver, Gtm_Pwm_IrqEdge irqEdge, boolean enable)
{
    Gtm_SignalState signalLevel;
    Gtm_Om_IrqType typeTom;
    GTM_OBP pDev;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
#endif

    ret = TRUE;
    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    signalLevel = s_pwmOutputDevs[pDriver->module].fnGetSignalLevel(pDev, pDriver->channel);

    switch(irqEdge)
    {
        case GTM_PWM_IRQEDGE_RISE:
        {
            typeTom = ((GTM_SIGNALSTATE_HIGH == signalLevel) ? GTM_OM_IRQTYPE_CCU0 : GTM_OM_IRQTYPE_CCU1);
            break;
        }
        case GTM_PWM_IRQEDGE_FALL:
        {
            typeTom = ((GTM_SIGNALSTATE_HIGH == signalLevel) ? GTM_OM_IRQTYPE_CCU1 : GTM_OM_IRQTYPE_CCU0);
            break;
        }
        case GTM_PWM_IRQEDGE_ALL:
        {
            typeTom = GTM_OM_IRQTYPE_ALL;
            break;
        }
        default:
        {
            typeTom = GTM_OM_IRQTYPE_NONE;
            break;
        }
    }
    ret &= s_pwmOutputDevs[pDriver->module].fnSetInterrupt(pDev, pDriver->channel, (uint8)typeTom, enable);
    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
void Gtm_Pwm_Hal_ClearInterruptStatus(const Gtm_Output_Driver *const pDriver, Gtm_Pwm_IrqEdge irqEdge)
{
    Gtm_SignalState signalLevel;
    Gtm_Om_IrqType typeTom;
    GTM_OBP pDev;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
#endif

    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    signalLevel = s_pwmOutputDevs[pDriver->module].fnGetSignalLevel(pDev, pDriver->channel);

    switch(irqEdge)
    {
        case GTM_PWM_IRQEDGE_RISE:
        {
            typeTom = ((GTM_SIGNALSTATE_HIGH == signalLevel) ? GTM_OM_IRQTYPE_CCU0 : GTM_OM_IRQTYPE_CCU1);
            break;
        }
        case GTM_PWM_IRQEDGE_FALL:
        {
            typeTom = ((GTM_SIGNALSTATE_HIGH == signalLevel) ? GTM_OM_IRQTYPE_CCU1 : GTM_OM_IRQTYPE_CCU0);
            break;
        }
        case GTM_PWM_IRQEDGE_ALL:
        {
            typeTom = GTM_OM_IRQTYPE_ALL;
            break;
        }
        default:
        {
            typeTom = GTM_OM_IRQTYPE_NONE;
            break;
        }
    }
    s_pwmOutputDevs[pDriver->module].fnClearInterruptStatus(pDev, pDriver->channel, (uint8)typeTom);
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
void Gtm_Pwm_Hal_SetCounterValue(const Gtm_Output_Driver *const pDriver, uint32 value)
{
    GTM_OBP pDev;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(s_pwmOutputDevs[pDriver->module].maxCNValue >= value));
#endif

    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    s_pwmOutputDevs[pDriver->module].fnSetCounterValue(pDev, pDriver->channel, value);
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
uint32 Gtm_Pwm_Hal_GetCounterValue(const Gtm_Output_Driver *const pDriver)
{
    uint32 ret;
    GTM_C_OBP pDev;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
#endif

    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    ret  = s_pwmOutputDevs[pDriver->module].fnGetCounterValue(pDev, pDriver->channel);

    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
boolean Gtm_Pwm_Hal_SetChannelsOutput(uint8 module, uint8 moduleIndex, uint32 mask, boolean immediate)
{
    uint16 ctrl;
    GTM_OBP pDev;
    GTM_OBP pXgc;
    uint8 chIndex;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* Do not check channel */
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(module, moduleIndex, 0U));
#endif

    ret = TRUE;
    pDev = s_pwmOutputDevs[module].fnGetDevPointer(moduleIndex);

    /* Configs for channels 0~7 */
    if (0U != (mask & 0xFFFFU))
    {
        /* channel 0~7: TGC0/AGC, use channelIndex = 1 */
        chIndex = 1U;

        ctrl = (uint16)(mask & 0xFFFFU);
        pXgc = s_pwmOutputDevs[module].fnGetTgcPointer(pDev, chIndex);
        ret &= s_pwmOutputDevs[module].fnSetChannelsOutput(pXgc, ctrl, immediate);
    }

    /* Configs for channels 8~15 */
    /* There are only channels 0~7 for ATOM */
    if ((0U != (mask & 0xFFFF0000U)) && ((uint8)GTM_OUTPUT_MODULE_TOM == module))
    {
        /* channel 8~15: TGC1, use channelIndex = 9 */
        chIndex = 9U;

        ctrl = (uint16)(mask >> 16U);
        pXgc = s_pwmOutputDevs[module].fnGetTgcPointer(pDev, chIndex);
        ret &= s_pwmOutputDevs[module].fnSetChannelsOutput(pXgc, ctrl, immediate);
    }
    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
uint32 Gtm_Pwm_Hal_GetInterruptStatus(const Gtm_Output_Driver *const pDriver, Gtm_Pwm_IrqEdge irqEdge)
{
    Gtm_SignalState signalLevel;
    Gtm_Om_IrqType typeTom;
    GTM_C_OBP pDev;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
#endif

    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    signalLevel = s_pwmOutputDevs[pDriver->module].fnGetSignalLevel(pDev, pDriver->channel);

    switch(irqEdge)
    {
        case GTM_PWM_IRQEDGE_RISE:
        {
            typeTom = ((GTM_SIGNALSTATE_HIGH == signalLevel) ? GTM_OM_IRQTYPE_CCU0 : GTM_OM_IRQTYPE_CCU1);
            break;
        }
        case GTM_PWM_IRQEDGE_FALL:
        {
            typeTom = ((GTM_SIGNALSTATE_HIGH == signalLevel) ? GTM_OM_IRQTYPE_CCU1 : GTM_OM_IRQTYPE_CCU0);
            break;
        }
        case GTM_PWM_IRQEDGE_ALL:
        {
            typeTom = GTM_OM_IRQTYPE_ALL;
            break;
        }
        default:
        {
            typeTom = GTM_OM_IRQTYPE_NONE;
            break;
        }
    }

    return s_pwmOutputDevs[pDriver->module].fnGetInterruptStatus(pDev, pDriver->channel, (uint8)typeTom);
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
boolean Gtm_Pwm_Hal_SetPeriodDutyCycle(const Gtm_Output_Driver *const pDriver, uint32 period, uint32 dutyCycle,
                                                                                                  boolean syncUpdate)
{
    GTM_OBP pDev;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(s_pwmOutputDevs[pDriver->module].maxCNValue >= period));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(s_pwmOutputDevs[pDriver->module].maxCNValue >= dutyCycle));
#endif

    ret = TRUE;
    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);

    ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareZeroOneShadow(pDev, pDriver->channel, period, dutyCycle);
    if (FALSE == syncUpdate)
    {
        ret &= s_pwmOutputDevs[pDriver->module].fnSetCompareZeroOne(pDev, pDriver->channel, period, dutyCycle);
    }
    return ret;
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
uint32 Gtm_Pwm_Hal_GetInterruptEnableStatus(const Gtm_Output_Driver *const pDriver, Gtm_Pwm_IrqEdge irqEdge)
{
    Gtm_SignalState signalLevel;
    Gtm_Om_IrqType typeTom;
    GTM_C_OBP pDev;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
#endif

    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    signalLevel = s_pwmOutputDevs[pDriver->module].fnGetSignalLevel(pDev, pDriver->channel);

    switch(irqEdge)
    {
        case GTM_PWM_IRQEDGE_RISE:
        {
            typeTom = ((GTM_SIGNALSTATE_HIGH == signalLevel) ? GTM_OM_IRQTYPE_CCU0 : GTM_OM_IRQTYPE_CCU1);
            break;
        }
        case GTM_PWM_IRQEDGE_FALL:
        {
            typeTom = ((GTM_SIGNALSTATE_HIGH == signalLevel) ? GTM_OM_IRQTYPE_CCU1 : GTM_OM_IRQTYPE_CCU0);
            break;
        }
        case GTM_PWM_IRQEDGE_ALL:
        {
            typeTom = GTM_OM_IRQTYPE_ALL;
            break;
        }
        default:
        {
            typeTom = GTM_OM_IRQTYPE_NONE;
            break;
        }
    }

    return s_pwmOutputDevs[pDriver->module].fnGetInterruptEnableStatus(pDev, pDriver->channel, (uint8)typeTom);
}

/* #Violation: gtm_pwm_hal_c_REF_1 */
boolean Gtm_Pwm_Hal_SetChannelOutput(const Gtm_Output_Driver *const pDriver, boolean channelEnable, boolean outEnable)
{
    GTM_OBP pDev;
    GTM_OBP pXgc;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_pwm_hal_c_REF_2 */
    Assert((boolean)Gtm_Pwm_Hal_CheckModuleIndex(pDriver->module, pDriver->moduleIndex, pDriver->channel));
#endif

    ret = TRUE;
    pDev = s_pwmOutputDevs[pDriver->module].fnGetDevPointer(pDriver->moduleIndex);
    pXgc = s_pwmOutputDevs[pDriver->module].fnGetTgcPointer(pDev, pDriver->channel);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannel(pXgc, pDriver->channel, channelEnable, TRUE);
    ret &= s_pwmOutputDevs[pDriver->module].fnSetChannelOutput(pXgc, pDriver->channel, outEnable, TRUE);

    return ret;
}

#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_pwm_hal_c_REF_5 */
#define PWM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_pwm_hal_c_REF_4 */
#include "Pwm_MemMap.h"
#else
/* #Violation: gtm_pwm_hal_c_REF_5 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_pwm_hal_c_REF_4 */
#include "Gtm_MemMap.h"
#endif
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

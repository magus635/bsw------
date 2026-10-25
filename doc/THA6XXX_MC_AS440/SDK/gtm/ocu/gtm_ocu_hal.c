/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_ocu_hal.c
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of OCU module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_ocu_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
* #gtm_ocu_hal_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core. Boolean can only be representes as uint8.
*
* #gtm_ocu_hal_c_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_ocu_hal_c_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm_ocu_hal.h"
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
/* #Violation: gtm_ocu_hal_c_REF_4 */
#define OCU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_ocu_hal_c_REF_3 */
#include "Ocu_MemMap.h"
#else
/* #Violation: gtm_ocu_hal_c_REF_4 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_ocu_hal_c_REF_3 */
#include "Gtm_MemMap.h"
#endif

/* #Violation: gtm_ocu_hal_c_REF_1 */
 boolean Gtm_Ocu_Hal_InitChannel(const Gtm_Output_Driver *const pDriver, const Gtm_Ocu_Config *const pConfig)
{
    GTM_OBP pAgc;
    GTM_OBP pAtom;
    const Gtm_SignalState sl = pConfig->signalLevel;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_ATOM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_ATOM_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_ATOM_CH_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)((0xFFFFFFU >= pConfig->compareValue0) && (0xFFFFFFU >= pConfig->compareValue1)));
#endif

    ret = TRUE;
    pAtom = Gtm_Atom_Std_GetAtomPointer(pDriver->moduleIndex);
    pAgc  = Gtm_Atom_Std_GetAgcPointer(pAtom, pDriver->channel);

    /* Reset the channel */
    Gtm_Atom_Std_ResetChannel(pAgc, pDriver->channel);

    /* Disable channels */
    ret &= Gtm_Atom_Std_SetChannel(pAgc, pDriver->channel, FALSE, TRUE);
    ret &= Gtm_Atom_Std_SetChannelOutput(pAgc, pDriver->channel, FALSE, TRUE);

    /* SOMC mode */
    ret &= Gtm_Atom_Std_SetChannelMode(pAtom, pDriver->channel, GTM_ATOM_MODE_OUTPUTCOMPARE);

    /* Select clock source */
    ret &= Gtm_Atom_Std_SetClockSource(pAtom, pDriver->channel, (uint8)pConfig->clk);
    ret &= Gtm_Atom_Std_SetTimeBase(pAtom, pDriver->channel, pConfig->timeBase);

    ret &= Gtm_Atom_Std_SetCompareZero(pAtom, pDriver->channel, pConfig->compareValue0);
    ret &= Gtm_Atom_Std_SetCompareOne(pAtom, pDriver->channel, pConfig->compareValue1);

    ret &= Gtm_Atom_Std_SetSignalLevel(pAtom, pDriver->channel, pConfig->signalLevel);
    ret &= Gtm_Atom_Std_SetSomcControl(pAtom, pDriver->channel, pConfig->somcCtrl.somcCompareStrategy);

    /* If SL = 1, GTM_OCU_SLCTRL_OUT1 means output = 0 and GTM_OCU_SLCTRL_OUT0 means output = 1, So swap them */
    if ((GTM_SIGNALSTATE_HIGH == sl) && ((GTM_OCU_SLCTRL_OUT1 == pConfig->somcCtrl.somcSignalLevelControl) ||
                                       (GTM_OCU_SLCTRL_OUT0 == pConfig->somcCtrl.somcSignalLevelControl)))
    {
        ret &= Gtm_Atom_Std_SetSomcSignalLevelControl(pAtom, pDriver->channel, 3U - 
                                                                      pConfig->somcCtrl.somcSignalLevelControl);
    }
    else
    {
        ret &= Gtm_Atom_Std_SetSomcSignalLevelControl(pAtom, pDriver->channel, pConfig->somcCtrl.somcSignalLevelControl);
    }

    /* Interrupt configuration */
    Gtm_Atom_Std_ClearInterruptStatus(pAtom, pDriver->channel, (uint8)GTM_ATOM_IRQTYPE_ALL);
    ret &= Gtm_Atom_Std_SetInterruptMode(pAtom, pDriver->channel, pConfig->interrupt.mode);
    ret &= Gtm_Atom_Std_SetInterrupt(pAtom, pDriver->channel, (uint8)GTM_ATOM_IRQTYPE_CCU0, 
                                                                            pConfig->interrupt.isCcu0Enabled);
    ret &= Gtm_Atom_Std_SetInterrupt(pAtom, pDriver->channel, (uint8)GTM_ATOM_IRQTYPE_CCU1, 
                                                                            pConfig->interrupt.isCcu1Enabled);

    return ret;
}

/* #Violation: gtm_ocu_hal_c_REF_1 */
boolean Gtm_Ocu_Hal_SetInterrupt(const Gtm_Output_Driver *const pDriver, boolean isCcu0Enabled, boolean isCcu1Enabled)
{
    GTM_OBP pAtom;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_ATOM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_ATOM_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_ATOM_CH_NUM));
#endif

    ret = TRUE;
    pAtom = Gtm_Atom_Std_GetAtomPointer(pDriver->moduleIndex);
    ret &= Gtm_Atom_Std_SetInterrupt(pAtom, pDriver->channel, (uint8)GTM_ATOM_IRQTYPE_CCU0, isCcu0Enabled);
    ret &= Gtm_Atom_Std_SetInterrupt(pAtom, pDriver->channel, (uint8)GTM_ATOM_IRQTYPE_CCU1, isCcu1Enabled);
    return ret;
}

/* #Violation: gtm_ocu_hal_c_REF_1 */
boolean Gtm_Ocu_Hal_SetSignalLevel(const Gtm_Output_Driver *const pDriver, Gtm_SignalState signalLevel)
{
    GTM_OBP pAtom;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_ATOM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_ATOM_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_ATOM_CH_NUM));
#endif

    ret = TRUE;
    pAtom = Gtm_Atom_Std_GetAtomPointer(pDriver->moduleIndex);
    ret &= Gtm_Atom_Std_SetSignalLevel(pAtom, pDriver->channel, signalLevel);
    return ret;
}

/* #Violation: gtm_ocu_hal_c_REF_1 */
boolean Gtm_Ocu_Hal_SetSignalLevelControl(const Gtm_Output_Driver *const pDriver, uint8 ctrl)
{
    GTM_OBP pAtom;
    Gtm_SignalState sl;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_ATOM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_ATOM_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_ATOM_CH_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(ctrl <= 3U));
#endif

    ret = TRUE;
    pAtom = Gtm_Atom_Std_GetAtomPointer(pDriver->moduleIndex);

    sl = Gtm_Atom_Std_GetSignalLevel(pAtom, pDriver->channel);
    /* If SL = 1, GTM_OCU_SLCTRL_OUT1 means output = 0 and GTM_OCU_SLCTRL_OUT0 means output = 1, So swap them */
    if ((GTM_SIGNALSTATE_HIGH == sl) && ((GTM_OCU_SLCTRL_OUT1 == ctrl) || (GTM_OCU_SLCTRL_OUT0 == ctrl)))
    {
        ret &= Gtm_Atom_Std_SetSomcSignalLevelControl(pAtom, pDriver->channel, 3U - ctrl);
    }
    else
    {
        ret &= Gtm_Atom_Std_SetSomcSignalLevelControl(pAtom, pDriver->channel, ctrl);
    }
    return ret;
}

/* #Violation: gtm_ocu_hal_c_REF_1 */
boolean Gtm_Ocu_Hal_SetOutputBehavior(const Gtm_Output_Driver *const pDriver, const Gtm_Ocu_Control *const pCtrl, 
                                                                        const Gtm_Ocu_Output_Behavior *const pBehavior)
{
    GTM_OBP pAtom;
    Gtm_SignalState sl;
    boolean ret;
#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pCtrl));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pBehavior));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_ATOM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_ATOM_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_ATOM_CH_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)((0xFFFFFFU >= pCtrl->cm0) && (0xFFFFFFU >= pCtrl->cm1)));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pBehavior->somcSignalLevelControl <= 3U));
#endif

    ret = TRUE;
    pAtom = Gtm_Atom_Std_GetAtomPointer(pDriver->moduleIndex);
    sl = Gtm_Atom_Std_GetSignalLevel(pAtom, pDriver->channel);
    /* To set up a new compare action, first the ATOM[i]_CH[x]_SR0.SR0 and/or ATOM[i]_CH[x]_SR1.SR1 register */
    /* containing captured values have to be read and then new compare values have to be written into the    */
    /* register ATOM[i]_CH[x]_CM1.CM1 and/or ATOM[i]_CH[x]_CM1.CM1. Since the channel immediately starts with*/
    /* the comparison after the ATOM[i]_CH[x]_CM0.CM0/ATOM[i]_CH[x]_CM1.CM1 register was/were written, the   */
    /* compare strategy has to be updated before the ATOM[i]_CH[x]_CM0.CM0/ATOM[i]_CH[x]_CM1.CM1 registers   */
    /* are written.                                                                                          */
    /* 1. Read SR0 and SR1 */
    (void)Gtm_Atom_Std_GetShadowZero(pAtom, pDriver->channel);
    (void)Gtm_Atom_Std_GetShadowOne(pAtom, pDriver->channel);

    /* 2. Set the compare strategy */
    ret &= Gtm_Atom_Std_SetSomcControl(pAtom, pDriver->channel, pBehavior->somcCompareStrategy);

    /* If SL = 1, GTM_OCU_SLCTRL_OUT1 means output = 0 and GTM_OCU_SLCTRL_OUT0 means output = 1, So swap them */
    if ((GTM_SIGNALSTATE_HIGH == sl) && ((GTM_OCU_SLCTRL_OUT1 == pBehavior->somcSignalLevelControl) ||
                                       (GTM_OCU_SLCTRL_OUT0 == pBehavior->somcSignalLevelControl)))
    {
        ret &= Gtm_Atom_Std_SetSomcSignalLevelControl(pAtom, pDriver->channel, 3U - pBehavior->somcSignalLevelControl);
    }
    else
    {
        ret &= Gtm_Atom_Std_SetSomcSignalLevelControl(pAtom, pDriver->channel, pBehavior->somcSignalLevelControl);
    }

    /* 3. Update CM0 and CM1 */
    ret &= Gtm_Atom_Std_SetCompareZero(pAtom, pDriver->channel, pCtrl->cm0);
    ret &= Gtm_Atom_Std_SetCompareOne(pAtom, pDriver->channel, pCtrl->cm1);

    return ret;
}

/* #Violation: gtm_ocu_hal_c_REF_1 */
boolean Gtm_Ocu_Hal_SetChannelOutput(const Gtm_Output_Driver *const pDriver, boolean channelEnable, boolean outEnable)
{
    GTM_OBP pAgc;
    GTM_OBP pAtom;
    boolean ret;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_ATOM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_ATOM_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_ATOM_CH_NUM));
#endif

    ret = TRUE;
    pAtom = Gtm_Atom_Std_GetAtomPointer(pDriver->moduleIndex);
    pAgc =  Gtm_Atom_Std_GetAgcPointer(pAtom, pDriver->channel);
    ret &= Gtm_Atom_Std_SetChannel(pAgc, pDriver->channel, channelEnable, TRUE);
    ret &= Gtm_Atom_Std_SetChannelOutput(pAgc, pDriver->channel, outEnable, TRUE);

    return ret;
}

/* #Violation: gtm_ocu_hal_c_REF_1 */
uint32 Gtm_Ocu_Hal_GetCounterValue(Gtm_Tbu_Ch channel)
{
    /* TBU counter value */
    return Gtm_Tbu_Std_GetCounterValue(channel);
}

/* #Violation: gtm_ocu_hal_c_REF_1 */
uint32 Gtm_Ocu_Hal_GetInterruptStatus(const Gtm_Output_Driver *const pDriver, Gtm_Atom_IrqType irq)
{
    GTM_C_OBP pAtom;
#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_ATOM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_ATOM_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_ATOM_CH_NUM));
#endif

    pAtom = Gtm_Atom_Std_GetAtomPointer(pDriver->moduleIndex);
    return Gtm_Atom_Std_GetInterruptStatus(pAtom, pDriver->channel, (uint8)irq);
}

/* #Violation: gtm_ocu_hal_c_REF_1 */
uint32 Gtm_Ocu_Hal_GetInterruptEnableStatus(const Gtm_Output_Driver *const pDriver, Gtm_Atom_IrqType irq)
{
    GTM_C_OBP pAtom;
#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_ATOM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_ATOM_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_ATOM_CH_NUM));
#endif

    pAtom = Gtm_Atom_Std_GetAtomPointer(pDriver->moduleIndex);
    return Gtm_Atom_Std_GetInterruptEnableStatus(pAtom, pDriver->channel, (uint8)irq);
}

/* #Violation: gtm_ocu_hal_c_REF_1 */
void Gtm_Ocu_Hal_ClearInterruptStatus(const Gtm_Output_Driver *const pDriver, Gtm_Atom_IrqType irq)
{
    GTM_OBP pAtom;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDriver));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->module == (uint8)GTM_OUTPUT_MODULE_ATOM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->moduleIndex < GTM_ATOM_NUM));
    /* #Violation: gtm_ocu_hal_c_REF_2 */
    Assert((boolean)(pDriver->channel < GTM_ATOM_CH_NUM));
#endif

    pAtom = Gtm_Atom_Std_GetAtomPointer(pDriver->moduleIndex);
    Gtm_Atom_Std_ClearInterruptStatus(pAtom, pDriver->channel, (uint8)irq);
}

#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_ocu_hal_c_REF_4 */
#define OCU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_ocu_hal_c_REF_3 */
#include "Ocu_MemMap.h"
#else
/* #Violation: gtm_ocu_hal_c_REF_4 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_ocu_hal_c_REF_3 */
#include "Gtm_MemMap.h"
#endif
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

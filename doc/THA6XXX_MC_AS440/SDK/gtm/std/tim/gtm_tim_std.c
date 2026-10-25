/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_tim_std.c
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations for all the internal
 *                 functions of the TIM module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#gtm_tim_std_c_REF_1:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured 
*                by code review.
*
* #gtm_tim_std_c_REF_2:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_tim_std_c_REF_3:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_tim_std.h"
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
/* #Violation: gtm_tim_std_c_REF_3 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tim_std_c_REF_2 */
#include "Gtm_MemMap.h"

boolean Gtm_Tim_Std_SetInputSource(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_Tim_Input input)
{
    uint32 mode;    /* Input source to Channel. multi-core encoding in use (MODE_x(1) defines the state of the signal)
                     * 00- State is 0 (ignore write access)
                     * 01- Change state to 0
                     * 10- Change state to 1
                     * 11- State is 1 (ignore write access) */
    uint32 value;   /* Source value */
    uint32 expect;
    uint32 shift;
    boolean ret;

    ret = TRUE;
    mode = 0x1U;

    switch (input)
    {
        case GTM_TIM_INPUT_CURRENTCHANNEL:
        {
            value = 0x1U;
            expect = 0x0U;
            pTim->CH[channel].CTRL.B.CICTRL = 0x0U;
            ret = Gtm_Register_ReadBack_Check(ret, 0U, pTim->CH[channel].CTRL.B.CICTRL);
            break;
        }
        case GTM_TIM_INPUT_ADJACENTCHANNEL:
        {
            value = 0x1U;
            expect = 0x0U;
            pTim->CH[channel].CTRL.B.CICTRL = 0x1U;
            ret = Gtm_Register_ReadBack_Check(ret, 1U, pTim->CH[channel].CTRL.B.CICTRL);
            break;
        }
        case GTM_TIM_INPUT_AUX:
        {
            value = 0x2U;
            expect = 0x3U;
            break;
        }
        default:
        {
            ret = FALSE;
            break;
        }
    }

    if (TRUE == ret)
    {
        shift = (uint32)channel * 4U;
        pTim->IN_SRC.U = (value << shift);
        ret = Gtm_Register_ReadBack_Check(ret, (uint32)expect << shift, pTim->IN_SRC.U & ((uint32)3U << shift));

        shift = ((uint32)channel * 4U) + 2U;
        pTim->IN_SRC.U = (mode << shift);
        ret = Gtm_Register_ReadBack_Check(ret, 0U, pTim->IN_SRC.U & ((uint32)3U << shift));
    }

    return ret;
}

boolean Gtm_Tim_Std_SetCaptureEdge(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_Tim_Edge_Cap edge)
{
    boolean ret;

    ret = TRUE;
    if (edge != GTM_TIM_EDGE_CAP_BOTH)
    {
        pTim->CH[channel].CTRL.B.DSL = (uint32)edge;
        pTim->CH[channel].CTRL.B.ISL = 0U;

        ret = Gtm_Register_ReadBack_Check(ret, (uint32)edge, pTim->CH[channel].CTRL.B.DSL);
        ret = Gtm_Register_ReadBack_Check(ret, 0U, pTim->CH[channel].CTRL.B.ISL);
    }
    else
    {
        pTim->CH[channel].CTRL.B.ISL = 1U;
        ret = Gtm_Register_ReadBack_Check(ret, 1U, pTim->CH[channel].CTRL.B.ISL);
    }

    return ret;
}

boolean Gtm_Tim_Std_SetInterruptMode(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_IrqMode mode)
{
    /* #Violation: gtm_tim_std_c_REF_1 */
    GTM_TIM_CH_IRQ_EN en;
    boolean ret;

    ret = TRUE;
    en.U = pTim->CH[channel].IRQ.EN.U;

    /* Disable all interrupts of the interrupt set to change mode */
    pTim->CH[channel].IRQ.EN.U            = 0U;
    pTim->CH[channel].IRQ.MODE.B.IRQ_MODE = (uint32)mode;
    pTim->CH[channel].IRQ.EN.U            = en.U; /* Set the values back */

    ret = Gtm_Register_ReadBack_Check(ret, (uint32)mode, pTim->CH[channel].IRQ.MODE.B.IRQ_MODE);

    return ret;
}

boolean Gtm_Tim_Std_SetInterrupt(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, uint8 irq)
{
    boolean ret;

    ret = TRUE;
    pTim->CH[channel].IRQ.EN.U = irq;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)irq, pTim->CH[channel].IRQ.EN.U);

    return ret;
}

void Gtm_Tim_Std_ClearInterruptStatus(GTM_TIM_t *const pTim, Gtm_Tim_Ch_Index channel, Gtm_Tim_IrqType irqType)
{
    if (GTM_TIM_IRQTYPE_ALL != irqType)
    {
        pTim->CH[channel].IRQ.NOTIFY.U = (uint32)1U << (uint32)irqType;
    }
    else
    {
        pTim->CH[channel].IRQ.NOTIFY.U = (uint32)0x3FU;
    }
}

/* #Violation: gtm_tim_std_c_REF_3 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tim_std_c_REF_2 */
#include "Gtm_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

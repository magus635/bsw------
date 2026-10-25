/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_tom_std.c
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations for all the internal
 *                 functions of the TOM module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#gtm_tom_std_c_REF_1:MISRAC2012-Rule-11.5;
* Justification: Type conversions do not result in errors.
*
*#gtm_tom_std_c_REF_2:MISRAC2012-Dir-1.1;
* Justification: Necessary type casting for memory and/or register accessing.
*
*#gtm_tom_std_c_REF_3:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured 
*                by code review.
*
* #gtm_tom_std_c_REF_4:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_tom_std_c_REF_5:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #gtm_tom_std_c_REF_6:MISRAC2012-Rule-2.2; 
* Justification:Platform-based design with configurable macros.
* 
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_tom_std.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* Number of channels per TOM TGC */
#define GTM_TOM_NUM_TGC_CHANNELS (8U)
/* Offset for GTM_TOM_TGC_GLB_CTRL_Bits.UPEN_CTRL0 */
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL_OFF (16U)
/* Offset for GTM_TOM_TGC_GLB_CTRL_Bits.RST_CH0 */
#define GTM_TOM_TGC_GLB_CTRL_RST_CH_OFF (8U)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: gtm_tom_std_c_REF_5 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tom_std_c_REF_4 */
#include "Gtm_MemMap.h"

void Gtm_Tom_Std_ClearInterruptStatus(GTM_OBP_C pTom, uint8 channel, uint8 irq)
{
    switch (irq)
    {
        case (uint8)GTM_TOM_IRQTYPE_CCU0:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            ((GTM_TOM_t *)pTom)->CH[channel].IRQ.NOTIFY.U = 1U;
            break;
        }
        case (uint8)GTM_TOM_IRQTYPE_CCU1:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            ((GTM_TOM_t *)pTom)->CH[channel].IRQ.NOTIFY.U = 2U;
            break;
        }
        case (uint8)GTM_TOM_IRQTYPE_ALL:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            ((GTM_TOM_t *)pTom)->CH[channel].IRQ.NOTIFY.U = 3U;
            break;
        }
        default:
        {
            /* Do nothing */
            break;
        }
    }
}

Gtm_SignalState Gtm_Tom_Std_GetOutputLevel(GTM_C_OBP_C pTom, uint8 channel)
{
    Gtm_SignalState ret;

    if (1U == ((const GTM_TOM_t *)pTom)->CH[channel].STAT.B.OL)
    {
        ret = GTM_SIGNALSTATE_HIGH;
    }
    else
    {
        ret = GTM_SIGNALSTATE_LOW;
    }
    return ret;
}


GTM_OBP Gtm_Tom_Std_GetTgcPointer(GTM_OBP_C pTom, uint8 channel)
{
    GTM_OBP pTgc;

    if (7U >= (uint32)channel)
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        /* #Violation: gtm_tom_std_c_REF_2 */
        pTgc = (GTM_OBP)&((GTM_TOM_t *)pTom)->TGC[0];
    }
    else
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        /* #Violation: gtm_tom_std_c_REF_2 */
        pTgc = (GTM_OBP)&((GTM_TOM_t *)pTom)->TGC[1];
    }

    return pTgc;
}

uint32 Gtm_Tom_Std_GetInterruptStatus(GTM_C_OBP_C pTom, uint8 channel, uint8 irq)
{
    uint32 result;

    switch (irq)
    {
        case (uint8)GTM_TOM_IRQTYPE_CCU0:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            result = ((const GTM_TOM_t *)pTom)->CH[channel].IRQ.NOTIFY.B.CCU0TC;
            break;
        }
        case (uint8)GTM_TOM_IRQTYPE_CCU1:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            result = ((const GTM_TOM_t *)pTom)->CH[channel].IRQ.NOTIFY.B.CCU1TC;
            break;
        }
        case (uint8)GTM_TOM_IRQTYPE_ALL:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            result = ((const GTM_TOM_t *)pTom)->CH[channel].IRQ.NOTIFY.U;
            break;
        }
        default:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            result = ((const GTM_TOM_t *)pTom)->CH[channel].IRQ.NOTIFY.U;
            break;
        }
    }

    result &= 0x3U;
    return result;
}

uint32 Gtm_Tom_Std_GetInterruptEnableStatus(GTM_C_OBP_C pTom, uint8 channel, uint8 irq)
{
    uint32 result;

    switch (irq)
    {
        case (uint8)GTM_TOM_IRQTYPE_CCU0:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            result = ((const GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.B.CCU0TC_IRQ_EN;
            break;
        }
        case (uint8)GTM_TOM_IRQTYPE_CCU1:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            result = ((const GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.B.CCU1TC_IRQ_EN;
            break;
        }
        case (uint8)GTM_TOM_IRQTYPE_ALL:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            result = ((const GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.U;
            break;
        }
        default:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            result = ((const GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.U;
            break;
        }
    }

    result &= 0x3U;
    return result;
}

boolean Gtm_Tom_Std_SetInterrupt(GTM_OBP_C pTom, uint8 channel, uint8 irq, boolean enable)
{
    boolean ret;

    ret = TRUE;
    switch (irq)
    {
        case (uint8)GTM_TOM_IRQTYPE_CCU0:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            ((GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.B.CCU0TC_IRQ_EN = (uint32)enable;
            ret = Gtm_Register_ReadBack_Check(ret, (uint32)enable, 
                                                       ((GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.B.CCU0TC_IRQ_EN);
            break;
        }
        case (uint8)GTM_TOM_IRQTYPE_CCU1:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            ((GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.B.CCU1TC_IRQ_EN = (uint32)enable;
            ret = Gtm_Register_ReadBack_Check(ret, (uint32)enable, 
                                                       ((GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.B.CCU1TC_IRQ_EN);
            break;
        }
        case (uint8)GTM_TOM_IRQTYPE_ALL:
        {
            /* #Violation: gtm_tom_std_c_REF_1 */
            ((GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.U = (uint32)enable | ((uint32)enable << 1U);
            ret = Gtm_Register_ReadBack_Check(ret, (uint32)enable | ((uint32)enable << 1U), 
                                                       ((GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.U);
            break;
        }
        default:
        {
            /* Do nothing */
            ret = FALSE;
            break;
        }
    }

    return ret;
}

boolean Gtm_Tom_Std_SetInterruptMode(GTM_OBP_C pTom, uint8 channel, Gtm_IrqMode mode)
{
    /* #Violation: gtm_tom_std_c_REF_3 */
    GTM_TOM_CH_IRQ_EN en;
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_c_REF_1 */
    en.U = ((GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.U;
    /* Disable all interrupts of the interrupt set to change mode */
    /* #Violation: gtm_tom_std_c_REF_1 */
    ((GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.U            = 0U;
    /* #Violation: gtm_tom_std_c_REF_1 */
    ((GTM_TOM_t *)pTom)->CH[channel].IRQ.MODE.B.IRQ_MODE = (uint32)mode;
    /* #Violation: gtm_tom_std_c_REF_1 */
    ((GTM_TOM_t *)pTom)->CH[channel].IRQ.EN.U            = en.U; /* Set the values back */

    ret = Gtm_Register_ReadBack_Check(ret, (uint32)mode, ((GTM_TOM_t *)pTom)->CH[channel].IRQ.MODE.B.IRQ_MODE);

    return ret;
}

boolean Gtm_Tom_Std_SetChannel(GTM_OBP_C pTgc, uint8 channel, boolean enable, boolean immediate)
{
    uint32 value;
    uint32 shift;
    uint32 expect;
    uint32 mask;
    boolean ret;

    ret = TRUE;
    shift = ((uint32)channel % 8U) * 2U;
    mask = (uint32)3U << shift;
    if (TRUE == enable)
    {
        value = (uint32)2U << shift;
        expect = (uint32)3U << shift;
    }
    else
    {
        value = (uint32)1U << shift;
        expect = 0U;
    }

    if (TRUE == immediate)
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        /* #Violation: gtm_tom_std_c_REF_6 */
        ((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U = (((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U & ~mask) | (value & mask);
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->ENDIS_STAT.U = value;

        ret = Gtm_Register_ReadBack_Check(ret, expect, ((GTM_TOM_TGC *)pTgc)->ENDIS_STAT.U & ((uint32)3U << shift));
    }
    else
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        /* #Violation: gtm_tom_std_c_REF_6 */
        ((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U = (((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U & ~mask) | (value & mask);
    }

    return ret;
}


boolean Gtm_Tom_Std_SetChannelOutput(GTM_OBP_C pTgc, uint8 channel, boolean enable, boolean immediate)
{
    uint32 value;
    uint32 shift;
    uint32 expect;
    uint32 mask;
    boolean ret;

    ret = TRUE;
    shift = ((uint32)channel % 8U) * 2U;
    mask = (uint32)3U << shift;
    if (TRUE == enable)
    {
        value = (uint32)2U << shift;
        expect = (uint32)3U << shift;
    }
    else
    {
        value = (uint32)1U << shift;
        expect = 0U;
    }

    if (TRUE == immediate)
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        /* #Violation: gtm_tom_std_c_REF_6 */
        ((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U = (((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U & ~mask) | (value & mask);
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->OUTEN_STAT.U = value;

        ret = Gtm_Register_ReadBack_Check(ret, expect, ((GTM_TOM_TGC *)pTgc)->OUTEN_STAT.U & ((uint32)3U << shift));
    }
    else
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        /* #Violation: gtm_tom_std_c_REF_6 */
        ((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U = (((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U & ~mask) | (value & mask);
    }

    return ret;
}


boolean Gtm_Tom_Std_SetChannelUpdate(GTM_OBP_C pTgc, uint8 channel, boolean enable)
{
    uint32 value;
    uint32 shift;
    uint32 expect;
    boolean ret;

    ret = TRUE;
    shift = (((uint32)channel % 8U) * 2U) + GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL_OFF;
    if (TRUE == enable)
    {
        value = (uint32)2U << shift;
        expect = (uint32)3U << shift;
    }
    else
    {
        value = (uint32)1U << shift;
        expect = 0U;
    }

    /* #Violation: gtm_tom_std_c_REF_1 */
    ((GTM_TOM_TGC *)pTgc)->GLB_CTRL.U = value;
    ret = Gtm_Register_ReadBack_Check(ret, expect, ((GTM_TOM_TGC *)pTgc)->GLB_CTRL.U & ((uint32)3U << shift));

    return ret;
}

void Gtm_Tom_Std_ResetChannel(GTM_OBP_C pTgc, uint8 channel)
{
    if ((uint32)channel <= 7U)
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->GLB_CTRL.U = ((GTM_TOM_TGC *)pTgc)->GLB_CTRL.U | 
                                            ((uint32)1U << ((uint32)channel + GTM_TOM_TGC_GLB_CTRL_RST_CH_OFF));
    }
    else
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->GLB_CTRL.U = ((GTM_TOM_TGC *)pTgc)->GLB_CTRL.U | ((uint32)1U << (uint32)channel);
    }
}

boolean Gtm_Tom_Std_SetChannelsOutput(GTM_OBP_C pTgc, uint16 mask, boolean immediate)
{
    uint32 ch;
    uint32 value;
    uint32 shift;
    uint32 statVal;
    uint32 ctrlMask;
    uint16 maskVal;
    boolean ret;

    ret = TRUE;
    value = 0U;
    statVal = 0U;
    maskVal = mask;
    ctrlMask = 0U;

    for (ch = 0U; ch < GTM_TOM_NUM_TGC_CHANNELS; ch++)
    {
        /* Bitfield length is 2 bits */
        shift = ch * 2U;

        if (0x1U == (maskVal & 0x1U))
        {
            value = value | ((uint32)2U << shift);
            statVal |= ((uint32)3U << shift);
            ctrlMask = ctrlMask | ((uint32)3U << shift);
        }

        if (0x100U == (maskVal & 0x100U))
        {
            value = value | ((uint32)1U << shift);
            ctrlMask = ctrlMask | ((uint32)3U << shift);
        }

        maskVal = maskVal >> 1U;
    }

    if (TRUE == immediate)
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U = (((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U & ~ctrlMask) | (value & ctrlMask);
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U = (((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U & ~ctrlMask) | (value & ctrlMask);
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->OUTEN_STAT.U = value;
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->ENDIS_STAT.U = value;

        ret &= Gtm_Register_ReadBack_Check(ret, value, (((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U)&ctrlMask);
        ret &= Gtm_Register_ReadBack_Check(ret, value, (((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U)&ctrlMask);
        ret &= Gtm_Register_ReadBack_Check(ret, statVal, (((GTM_TOM_TGC *)pTgc)->ENDIS_STAT.U)&ctrlMask);
        ret &= Gtm_Register_ReadBack_Check(ret, statVal, (((GTM_TOM_TGC *)pTgc)->OUTEN_STAT.U)&ctrlMask);
    }
    else
    {
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U = (((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U & ~ctrlMask) | (value & ctrlMask);
        /* #Violation: gtm_tom_std_c_REF_1 */
        ((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U = (((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U & ~ctrlMask) | (value & ctrlMask);

        ret &= Gtm_Register_ReadBack_Check(ret, value, (((GTM_TOM_TGC *)pTgc)->ENDIS_CTRL.U)&ctrlMask);
        ret &= Gtm_Register_ReadBack_Check(ret, value, (((GTM_TOM_TGC *)pTgc)->OUTEN_CTRL.U)&ctrlMask);
    }

    return ret;
}

boolean Gtm_Tom_Std_SetForceUpdate(GTM_OBP_C pTgc, uint8 channel, boolean enable)
{
    uint32 en;
    uint32 expect;
    uint8 ch;
    uint32 shift;
    boolean ret;

    ret = TRUE;
    ch = channel % 8U;
    shift = (uint32)2U * ch;
    if (TRUE == enable)
    {
        en = 2U;
        expect = 3U;
    }
    else
    {
        en = 1U;
        expect = 0U;
    }
    ((GTM_TOM_TGC *)pTgc)->FUPD_CTRL.U = (en << shift);

    ret = Gtm_Register_ReadBack_Check(ret, (expect<<shift), (((GTM_TOM_TGC *)pTgc)->FUPD_CTRL.U&((uint32)3U<<shift)));

    return ret;
}
/* #Violation: gtm_tom_std_c_REF_5 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tom_std_c_REF_4 */
#include "Gtm_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

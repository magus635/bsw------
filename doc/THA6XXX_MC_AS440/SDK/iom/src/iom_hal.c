/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    iom_hal.c
 * Author:      00915
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: IOM hardware abstraction layer source file.
 *              This file contains implementations for IOM hardware abstraction layer.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
*#Violation Summary
*#iom_hal_c_REF_1:MISRAC2012-Rule-2.1; 
* Justification:Reserved API for user access.
*
*#iom_hal_c_REF_2:MISRAC2012-Rule-11.4; 
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#iom_hal_c_REF_3:MISRAC2012-Rule-19.2; 
* Justification:Necessary union type for bitwise access to register. Data integrity and correctness will be ensured by
*               code review.
*
*#iom_hal_c_REF_4:MISRAC2012-Rule-10.5; 
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be represents as uint8.
*
*#iom_hal_c_REF_5:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "iom_register.h"
#include "iom_hal.h"
#include "safewdt_hal.h"
#include "cpuwdt_hal.h"
#include "tha6_cfg.h"
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
#define IOM_START_SEC_CODE_ASIL_D_GLOBAL
#include "Iom_MemMap.h"

/* #Violation: iom_hal_c_REF_1*/
boolean Iom_Hal_SetClock(uint8 clockDivider)
{
    boolean ret = TRUE;
    /* #Violation: iom_hal_c_REF_3 */
    IOM_CKCON tempCKCON;

    tempCKCON.U = 0;
    tempCKCON.B.CKDIV = clockDivider;
    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();

    /* #Violation: iom_hal_c_REF_2*/
    IOM->CKCON.U = tempCKCON.U;
    /* #Violation: iom_hal_c_REF_2*/
    ret &= Iom_Register_ReadBack_Check(ret, IOM->CKCON.U, tempCKCON.U);

    ret &= Cpuwdt_Hal_SetEndinit();
    ENABLE_ALL_INTERRUPTS();
    return ret;
}

/* #Violation: iom_hal_c_REF_1*/
boolean Iom_Hal_InitLpu(Iom_Lpu *const pLPU, const Iom_LpuConfig *const pConfig)
{
    boolean ret = TRUE;
    uint8 refIndex;
    uint8 monIndex;
    uint8 counterIndex;
    uint8 refInput;
    uint8 monInput;
    /* #Violation: iom_hal_c_REF_3*/
    IOM_PPUCON ppuconReg;
    /* #Violation: iom_hal_c_REF_3*/
    IOM_LPUCFG lpuCfgReg;
    /* #Violation: iom_hal_c_REF_3*/
    IOM_EMUESEL tempEmusel;
    /* #Violation: iom_hal_c_REF_3*/
    IOM_EMUCCFG tempEmucfg;

#if(INPUT_ARG_DETECT == STD_ON)
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(NULL_PTR != pLPU));
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(NULL_PTR != pConfig));

#if defined(THA6_THA6412) || defined(THA6_THA6104)
    if (((uint8)pConfig->reference.filter.mode == (uint8)IOM_PPUFILTERMODE_PRESCALERONRISINGEDGE) ||
        ((uint8)pConfig->reference.filter.mode == (uint8)IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE))
    {
        /* #Violation: iom_hal_c_REF_4*/
        Assert((boolean)(pConfig->reference.filter.prescalerFactor >= 1U));
    }

    if (((uint8)pConfig->monitor.filter.mode == (uint8)IOM_PPUFILTERMODE_PRESCALERONRISINGEDGE) ||
        ((uint8)pConfig->monitor.filter.mode == (uint8)IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE))
    {
        /* #Violation: iom_hal_c_REF_4*/
        Assert((boolean)(pConfig->monitor.filter.prescalerFactor >= 1U));
    }
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D)
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(pConfig->reference.filter.filterTime >= 1U));
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(pConfig->monitor.filter.filterTime >= 1U));
#endif

#endif /* INPUT_ARG_DETECT */

    pLPU->channel = pConfig->channel;

    /* Configure reference input signal */
    refIndex = (uint8)IOM_LPU_GET_REF_INPUT_INDEX((pConfig->reference.input));
    refInput = (uint8)(IOM_LPU_GET_REF_INPUT_SIGNAL((pConfig->reference.input)));
    pLPU->refIndex = refIndex;
    /* #Violation: iom_hal_c_REF_4*/
    pLPU->refInput = (Iom_ReferenceSignal)refInput;
    /* #Violation: iom_hal_c_REF_2*/
    ppuconReg.U = IOM->PPUCON[refIndex].U;
    ppuconReg.B.RSEL = (uint8)refInput;

    if ((uint8)IOM_REFERENCESIGNAL_PORTLOGIC == refInput)
    {
        if ((uint8)pConfig->reference.filter.mode <= (uint8)IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCERISINGEDGEDELAYDEBOUNCEFALLINGEDGE)
        {
            ppuconReg.B.OMSEL = (uint8)pConfig->reference.filter.mode;
            ppuconReg.B.FTHR = pConfig->reference.filter.filterTime;
            ppuconReg.B.TBMOD = (TRUE == pConfig->reference.filter.clearTimerOnGlitch) ? 0u : 1u;
        }
#if defined(THA6_THA6412) || defined(THA6_THA6104)
        else if ((uint8)pConfig->reference.filter.mode <= (uint8)IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE)
        {
            ppuconReg.B.OMSEL = (uint8)pConfig->reference.filter.mode;
            ppuconReg.B.FTHR = (uint16)(pConfig->reference.filter.prescalerFactor - 1u);
        }
        else
        {
            /* No filter */
            ppuconReg.B.FTHR = 0u;
        }
#endif
    }
#if defined(THA6_THA6412) || defined(THA6_THA6104)
    else if((uint8)IOM_REFERENCESIGNAL_GTMEXORCOMBINER == (uint8)refInput)
    {
        /* #Violation: iom_hal_c_REF_2*/
        IOM->GSCCFG.U = pConfig->reference.exor;
        /* #Violation: iom_hal_c_REF_2*/
        ret &= Iom_Register_ReadBack_Check(ret, IOM->GSCCFG.U, pConfig->reference.exor);
    }
#endif
    else
    {
        /*No reference input signal*/
    }
    /* #Violation: iom_hal_c_REF_2*/
    IOM->PPUCON[refIndex].U = ppuconReg.U;
    /* #Violation: iom_hal_c_REF_2*/
    ret &= Iom_Register_ReadBack_Check(ret, IOM->PPUCON[refIndex].U, ppuconReg.U);

    /* Configure monitor input signal */
    monIndex = (uint8)IOM_LPU_GET_MON_INPUT_INDEX((pConfig->monitor.input));
    monInput = (uint8)(IOM_LPU_GET_MON_INPUT_SIGNAL((pConfig->monitor.input)));
    pLPU->monIndex = monIndex;
    /* #Violation: iom_hal_c_REF_4*/
    pLPU->monInput = (Iom_MonitorSignal)monInput;
    /* #Violation: iom_hal_c_REF_2*/
    ppuconReg.U = IOM->PPUCON[refIndex].U;
    ppuconReg.B.MSEL = (uint8)monInput;

    if ((uint8)IOM_MONITORSIGNAL_PORTLOGIC == (uint8)monInput)
    {

        if ((uint8)pConfig->monitor.filter.mode <= (uint8)IOM_PPUFILTERMODE_IMMEDIATEDEBOUNCERISINGEDGEDELAYDEBOUNCEFALLINGEDGE)
        {
            ppuconReg.B.OMSEL = (uint8)pConfig->monitor.filter.mode;
            ppuconReg.B.FTHR = pConfig->monitor.filter.filterTime;
            ppuconReg.B.TBMOD = (TRUE== pConfig->monitor.filter.clearTimerOnGlitch) ? 0u : 1u;
        }
#if defined(THA6_THA6412) || defined(THA6_THA6104)
        else if ((uint8)pConfig->monitor.filter.mode <= (uint8)IOM_PPUFILTERMODE_PRESCALERONFALLINGEDGE)
        {
            ppuconReg.B.OMSEL =(uint8)pConfig->monitor.filter.mode;
            ppuconReg.B.FTHR = (uint8)(pConfig->monitor.filter.prescalerFactor - 1u);
        }
        else
        {
            /* No filter */
            ppuconReg.B.FTHR = 0u;
        }
#endif
    }
    /* #Violation: iom_hal_c_REF_2*/
    IOM->PPUCON[monIndex].U = ppuconReg.U;
    /* #Violation: iom_hal_c_REF_2*/
    ret &= Iom_Register_ReadBack_Check(ret, IOM->PPUCON[monIndex].U, ppuconReg.U);    

    /* Configure the LPU */
    lpuCfgReg.U = 0u;
    lpuCfgReg.B.IVR = (TRUE == pConfig->reference.inverted) ? 1u : 0u;
    lpuCfgReg.B.IVM = (TRUE == pConfig->monitor.inverted) ? 1u : 0u;
    lpuCfgReg.B.MSSEL = (IOM_LPUEVENTSOURCE_MON == pConfig->event.source) ? 0u : 1u;
    lpuCfgReg.B.EMSEL = (uint8)pConfig->eventWindow.run;
    lpuCfgReg.B.EWSEL = (uint8)pConfig->eventWindow.controlSource;
    lpuCfgReg.B.EDS = (((uint8)(pConfig->eventWindow.clearEvent)) | (((uint8)(pConfig->event.trigger) << 2u)));
    lpuCfgReg.B.IVW = (TRUE == pConfig->eventWindow.inverted) ? 1u : 0u;
    lpuCfgReg.B.MSEL = (uint8)IOM_LPU_GET_MON_INPUT_INDEX((pConfig->monitor.input));
    lpuCfgReg.B.RSEL = (uint8)IOM_LPU_GET_REF_INPUT_INDEX((pConfig->reference.input));

    /* #Violation: iom_hal_c_REF_2*/
    IOM->LPUCFG[pLPU->channel].U = lpuCfgReg.U;
    /* #Violation: iom_hal_c_REF_2*/
    ret &= Iom_Register_ReadBack_Check(ret, IOM->LPUCFG[pLPU->channel].U, lpuCfgReg.U);     
    /* #Violation: iom_hal_c_REF_2*/
    IOM->LPUEWC[pLPU->channel].U = pConfig->eventWindow.threshold;
    /* #Violation: iom_hal_c_REF_2*/
    ret &= Iom_Register_ReadBack_Check(ret, IOM->LPUEWC[pLPU->channel].U, pConfig->eventWindow.threshold);     

    /* Configure the EMU */
    pLPU->counter.input = pConfig->counter.input;
    pLPU->counter.threshold = pConfig->counter.threshold;
    counterIndex = (uint8)pLPU->counter.input;

    if(0u != (uint32)pLPU->counter.threshold)
    {
        if((uint8)IOM_EVENTCOUNTERCHANNEL_NOCOUNTER == counterIndex)
        {
            /* #Violation: iom_hal_c_REF_2*/
            tempEmusel.U = IOM->EMUESEL.U;
            tempEmusel.U |= ((uint32)1u << ((uint8)pConfig->channel));
            /* #Violation: iom_hal_c_REF_2*/
            IOM->EMUESEL.U = tempEmusel.U;
            /* #Violation: iom_hal_c_REF_2*/
            ret &= Iom_Register_ReadBack_Check(ret, IOM->EMUESEL.U, tempEmusel.U);
        }
        else
        {
            /* #Violation: iom_hal_c_REF_2*/
            tempEmusel.U = IOM->EMUESEL.U;
            tempEmusel.U |= ((uint32)1u << (counterIndex + IOM_EMUESEL_RCES0_OFF));
            /* #Violation: iom_hal_c_REF_2*/
            IOM->EMUESEL.U = tempEmusel.U;
            /* #Violation: iom_hal_c_REF_2*/
            ret &= Iom_Register_ReadBack_Check(ret, IOM->EMUESEL.U, tempEmusel.U);
            /* #Violation: iom_hal_c_REF_2*/
            tempEmucfg.U = IOM->EMUCCFG.U;
            tempEmucfg.U &= ~(0xFFUL << ((uint32)counterIndex * IOM_EMUCCFG_SELC1_OFF));
            tempEmucfg.U |= ((uint32)pLPU->channel | ((uint32)(pLPU->counter.threshold ) << IOM_EMUCCFG_TEC0_OFF))
                               << ((uint32)counterIndex * IOM_EMUCCFG_SELC1_OFF);
            /* #Violation: iom_hal_c_REF_2*/
            IOM->EMUCCFG.U = tempEmucfg.U;
            /* #Violation: iom_hal_c_REF_2*/
            ret &= Iom_Register_ReadBack_Check(ret, IOM->EMUCCFG.U, tempEmucfg.U);
        }
    }

    return ret;
}

/* #Violation: iom_hal_c_REF_1*/
Iom_PpuGlitchFlag Iom_Hal_GetGlitch(Iom_PpuId index)
{
    uint8 RisingEdge;
    uint8 FallingEdge;
    uint8 edge;

    /* #Violation: iom_hal_c_REF_4 */
    /* #Violation: iom_hal_c_REF_2 */
    RisingEdge  = (uint8)((IOM->PPUESTS.U >> ((uint32)index + IOM_PPUESTS_REDC_OFF)) != 0u);
    /* #Violation: iom_hal_c_REF_4 */
    /* #Violation: iom_hal_c_REF_2 */
    FallingEdge = (uint8)((IOM->PPUESTS.U >> ((uint32)index)) != 0u);
    /* #Violation: iom_hal_c_REF_4 */
    edge = (FallingEdge << 1u) | RisingEdge;

    /* #Violation: iom_hal_c_REF_4 */
    return (Iom_PpuGlitchFlag)edge;
}

/* #Violation: iom_hal_c_REF_1*/
void Iom_Hal_ClearGlitch(Iom_PpuId index, Iom_PpuGlitchFlag edge)
{
    uint32 EdgeGlitchClrMask;
    if(IOM_PPUGLITCHFLAG_RISINGEDGE == edge)
    {
        EdgeGlitchClrMask = (~((uint32)0x1u << ((uint8)index + IOM_PPUESTS_REDC_OFF)));
    }
    else if(IOM_PPUGLITCHFLAG_FALLINGEDGE == edge)
    {
        EdgeGlitchClrMask = ~((uint32)0x1u << (uint8)index);
    }
    else
    {
        EdgeGlitchClrMask = ~(((uint32)0x1u << ((uint8)index + IOM_PPUESTS_REDC_OFF)) | 
                             (((uint32)0x1u << (uint8)index)));
    }
    /* #Violation: iom_hal_c_REF_2*/
    IOM->PPUESTS.U &= EdgeGlitchClrMask;
}

/* #Violation: iom_hal_c_REF_1*/
boolean Iom_Hal_SetPpuThreshold(Iom_PpuId index, uint16 threshold)
{
    boolean ret = TRUE;

#if(INPUT_ARG_DETECT == STD_ON)
#if defined(THA6_THA6206) || defined(THA6_THA6206D)
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)((uint16)threshold >= 1U));
#endif
#endif /* INPUT_ARG_DETECT */

    /* #Violation: iom_hal_c_REF_2*/
    IOM->PPUCON[index].B.FTHR = threshold;
    /* #Violation: iom_hal_c_REF_2*/
    ret &= Iom_Register_ReadBack_Check(ret, IOM->PPUCON[index].B.FTHR, threshold);

    return ret;
}

/* #Violation: iom_hal_c_REF_1*/
uint16 Iom_Hal_GetPpuThreshold(Iom_PpuId index)
{
    uint16 threshold;

    /* #Violation: iom_hal_c_REF_2*/
    threshold = (uint16)IOM->PPUCON[index].B.FTHR;

    return threshold;
}

/* #Violation: iom_hal_c_REF_1*/
boolean Iom_Hal_SetEventWindowThreshold(Iom_LpuId index,uint32 threshold)
{
    boolean ret = TRUE;

    /* #Violation: iom_hal_c_REF_2*/
    IOM->LPUEWC[index].B.EWTHR = threshold;
    /* #Violation: iom_hal_c_REF_2*/
    ret &= Iom_Register_ReadBack_Check(ret, IOM->LPUEWC[index].B.EWTHR, threshold);

    return ret;
}

/* #Violation: iom_hal_c_REF_1*/
uint32 Iom_Hal_GetEventWindowThreshold(Iom_LpuId index)
{
    uint32 threshold;

    /* #Violation: iom_hal_c_REF_2*/
    threshold = IOM->LPUEWC[index].B.EWTHR;

    return threshold;
}

/* #Violation: iom_hal_c_REF_1*/
boolean Iom_Hal_SetCombiner(Iom_EventCounterChannel index, Iom_LpuId channel, Iom_EventCounterThreshold threshold)
{
    boolean ret = TRUE;
    /* #Violation: iom_hal_c_REF_3*/
    IOM_EMUCCFG temp_EMUCCFG;

    /* #Violation: iom_hal_c_REF_2*/
    temp_EMUCCFG.U = IOM->EMUCCFG.U;
    switch(index)
    {
        case IOM_EVENTCOUNTERCHANNEL_0:
            temp_EMUCCFG.B.CXEC0 = (uint8)channel;
            temp_EMUCCFG.B.TEC0 = (uint8)threshold;
            /* #Violation: iom_hal_c_REF_2*/
            IOM->EMUCCFG.U = temp_EMUCCFG.U;
            /* #Violation: iom_hal_c_REF_2*/
            ret &= Iom_Register_ReadBack_Check(ret, IOM->EMUCCFG.U, temp_EMUCCFG.U);
            break;

        case IOM_EVENTCOUNTERCHANNEL_1:
            temp_EMUCCFG.B.CXEC1 = (uint8)channel;
            temp_EMUCCFG.B.TEC1 = (uint8)threshold;
            /* #Violation: iom_hal_c_REF_2*/
            IOM->EMUCCFG.U = temp_EMUCCFG.U;
            /* #Violation: iom_hal_c_REF_2*/
            ret &= Iom_Register_ReadBack_Check(ret, IOM->EMUCCFG.U, temp_EMUCCFG.U);            
            break;

        case IOM_EVENTCOUNTERCHANNEL_2:
            temp_EMUCCFG.B.CXEC2 = (uint8)channel;
            temp_EMUCCFG.B.TEC2 = (uint8)threshold;
            /* #Violation: iom_hal_c_REF_2*/
            IOM->EMUCCFG.U = temp_EMUCCFG.U;
            /* #Violation: iom_hal_c_REF_2*/
            ret &= Iom_Register_ReadBack_Check(ret, IOM->EMUCCFG.U, temp_EMUCCFG.U);            
            break;

        case IOM_EVENTCOUNTERCHANNEL_3:
            temp_EMUCCFG.B.CXEC3 = (uint8)channel;
            temp_EMUCCFG.B.TEC3 = (uint8)threshold;
            /* #Violation: iom_hal_c_REF_2*/
            IOM->EMUCCFG.U = temp_EMUCCFG.U;
            /* #Violation: iom_hal_c_REF_2*/
            ret &= Iom_Register_ReadBack_Check(ret, IOM->EMUCCFG.U, temp_EMUCCFG.U);
            break;

        default:
            ret = FALSE;
            /*default*/
            break;
    }
    
    return ret;  
}

/* #Violation: iom_hal_c_REF_1*/
void Iom_Hal_GetCombiner(Iom_EventCounterChannel index, Iom_LpuId *const pChannel, Iom_EventCounterThreshold *const pThreshold)
{
    /* #Violation: iom_hal_c_REF_3*/
    IOM_EMUCCFG temp_EMUCCFG;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the index is the range */
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)((uint8)index < 4u));
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(NULL_PTR != pChannel));
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(NULL_PTR != pThreshold));
#endif /* INPUT_ARG_DETECT */
    /* #Violation: iom_hal_c_REF_2*/
    temp_EMUCCFG.U = IOM->EMUCCFG.U;

    switch(index)
    {
        case IOM_EVENTCOUNTERCHANNEL_0:
            /* #Violation: iom_hal_c_REF_4*/
            *pChannel = (Iom_LpuId)temp_EMUCCFG.B.CXEC0;
            /* #Violation: iom_hal_c_REF_4*/
            *pThreshold = (Iom_EventCounterThreshold)temp_EMUCCFG.B.TEC0;
            break;

        case IOM_EVENTCOUNTERCHANNEL_1:
            /* #Violation: iom_hal_c_REF_4*/
            *pChannel = (Iom_LpuId)temp_EMUCCFG.B.CXEC1;
            /* #Violation: iom_hal_c_REF_4*/
            *pThreshold = (Iom_EventCounterThreshold)temp_EMUCCFG.B.TEC1;
            break;

        case IOM_EVENTCOUNTERCHANNEL_2:
            /* #Violation: iom_hal_c_REF_4*/
            *pChannel = (Iom_LpuId)temp_EMUCCFG.B.CXEC2;
            /* #Violation: iom_hal_c_REF_4*/
            *pThreshold = (Iom_EventCounterThreshold)temp_EMUCCFG.B.TEC2;
            break;

        case IOM_EVENTCOUNTERCHANNEL_3:
            /* #Violation: iom_hal_c_REF_4*/
            *pChannel = (Iom_LpuId)temp_EMUCCFG.B.CXEC3;
            /* #Violation: iom_hal_c_REF_4*/
            *pThreshold = (Iom_EventCounterThreshold)temp_EMUCCFG.B.TEC3;
            break;
            
        default:
            /*default*/
            break;
    }  
}

/* #Violation: iom_hal_c_REF_1*/
boolean Iom_Hal_SetEmuGlobalEventSel(uint32 EventSel)
{
    boolean ret = TRUE;
    
    /* #Violation: iom_hal_c_REF_2*/
    IOM->EMUESEL.U = EventSel;
    /* #Violation: iom_hal_c_REF_2*/
    ret &= Iom_Register_ReadBack_Check(ret, IOM->EMUESEL.U, EventSel);

    return ret;
}

/* #Violation: iom_hal_c_REF_1*/
uint32 Iom_Hal_GetEmuGlobalEventSel(void)
{
    uint32 EventSel;

    /* #Violation: iom_hal_c_REF_2*/
    EventSel = IOM->EMUESEL.U;

    return EventSel;
}

/* #Violation: iom_hal_c_REF_1*/
void Iom_Hal_GetAllHistory(uint16 *const pEh0, uint16 *const pEh1, uint16 *const pEh2, uint16 *const pEh3)
{
    uint32 value;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the index is the range */
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(NULL_PTR != pEh0));
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(NULL_PTR != pEh1));
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(NULL_PTR != pEh2));
    /* #Violation: iom_hal_c_REF_4*/
    Assert((boolean)(NULL_PTR != pEh3));
#endif /* INPUT_ARG_DETECT */

    /* #Violation: iom_hal_c_REF_2*/
    value = IOM->EMUEHR0.U;
    *pEh0 = (uint16)(value & IOM_EMUETH_AEH0_AEH2_MASK);
    *pEh1 = (uint16)(value >> IOM_EMUETH_AEH1_AEH3_OFF);

    /* #Violation: iom_hal_c_REF_2*/
    value = IOM->EMUEHR1.U;
    *pEh2 = (uint16)(value & IOM_EMUETH_AEH0_AEH2_MASK);
    *pEh3 = (uint16)(value >> IOM_EMUETH_AEH1_AEH3_OFF);
}

/* #Violation: iom_hal_c_REF_1*/
void Iom_Hal_ClearAllHistory(void)
{
    /* #Violation: iom_hal_c_REF_2*/
    IOM->EMUEHR0.U = 0u;
    /* #Violation: iom_hal_c_REF_2*/
    IOM->EMUEHR1.U = 0u;
}

/* #Violation: iom_hal_c_REF_1*/
uint8 Iom_Hal_GetSafetyStatus(void)
{
    /* #Violation: iom_hal_c_REF_2*/
    return (uint8)IOM->SAFETYSTS.U;
}

/* #Violation: iom_hal_c_REF_1*/
boolean Iom_Hal_ClearSafetyStatus(uint8 flag)
{
    boolean ret;

    ret = TRUE;
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* #Violation: iom_hal_c_REF_2*/
    IOM->SAFETYSTS.U &= ~(uint32)flag;
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

#define IOM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: iom_hal_c_REF_5*/
#include "Iom_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

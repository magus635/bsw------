/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_trig_hal.c
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the interface implementations of GTM_WRAP module.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031     Create
 *  2024/11/19    01031     Gtm_Trig_Hal_ToMscL1 internal implementation modification
 *  2024/11/19    01031     Gtm_Trig_Hal_ToDsadc internal implementation modification
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_trig_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
* #gtm_trig_hal_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core. Boolean can only be representes as uint8.
*
* #gtm_trig_hal_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #gtm_trig_hal_c_REF_4:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_trig_hal_c_REF_5:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #gtm_trig_hal_c_REF_6:MISRAC2012-Rule-2.2; 
* Justification:Platform-based design with configurable macros.
* 
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm_trig_hal.h"
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
 * Function:     Gtm_Trig_Hal_ToMscL2Check
 * Description:  Check GTM to MSC level 2 configuration
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pConfig: Configuration pointer
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Configuration is valid 
 *                        FALSE: Configuration is invalid
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/03/10    01031      Create
 *********************************************************************************************************************/
#if(STD_ON == INPUT_ARG_DETECT)
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
static boolean Gtm_Trig_Hal_ToMscL2Check(const Gtm_MscTrigL2Config *const pConfig);
#endif
#endif

/**********************************************************************************************************************
 * Function:     Gtm_Trig_Hal_GetMscMuxAndSets
 * Description:  Get MSC nput multiplex object and MSC sets
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pConfig: MSCTRIG level 2 configuration
 *               shift: MSC Signal
 * Inout:        pMsc: MSC0 input multiplex object
 * Output:       None
 * Return:       uint32: value: MSC sets
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/11/11    01359      Create
 *********************************************************************************************************************/
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
static uint32 Gtm_Trig_Hal_GetMscMuxAndSets(const Gtm_MscTrigL2Config *const pConfig, GTM_MSC **pMsc, uint32 shift);
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
#if(STD_ON == INPUT_ARG_DETECT)
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
static boolean Gtm_Trig_Hal_ToMscL2Check(const Gtm_MscTrigL2Config *const pConfig)
{
    boolean ret;

    switch (pConfig->Num)
    {
    case GTM_TRIG_MSCNUM_0:
        {
            ret = ((uint32)pConfig->mscSet <= (uint32)GTM_TRIG_MSCTRIGSET_3) ? TRUE : FALSE;
            break;
        }
#if defined(THA6_THA6412)
    case GTM_TRIG_MSCNUM_1:
        {
            ret = ((uint32)pConfig->mscSet <= (uint32)GTM_TRIG_MSCTRIGSET_3) ? TRUE : FALSE;
            break;
        }
    case GTM_TRIG_MSCNUM_2:
        {
            if ((GTM_TRIG_MSCTRIGSET_0 == pConfig->mscSet) || (GTM_TRIG_MSCTRIGSET_2 == pConfig->mscSet))
            {
                ret = TRUE;
            }
            else if ((GTM_TRIG_MSCTRIGSET_4 == pConfig->mscSet) || (GTM_TRIG_MSCTRIGSET_5 == pConfig->mscSet))
            {
                ret = (GTM_TRIG_MSCTRIGINPUT_LOW != pConfig->input) ? TRUE : FALSE;
            }
            else if (GTM_TRIG_MSCTRIGSET_6 == pConfig->mscSet)
            {
                ret = (GTM_TRIG_MSCTRIGINPUT_LOW == pConfig->input) ? TRUE : FALSE;
            }
            else
            {
                ret = FALSE;
            }
            break;
        }
#endif
        default:
        {
            ret = FALSE;
            break;
        }
    }

    return ret;
}
#endif
#endif

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
static uint32 Gtm_Trig_Hal_GetMscMuxAndSets(const Gtm_MscTrigL2Config *const pConfig, GTM_MSC **pMsc, uint32 shift)
{
    uint32 value;
    value = 0U;
    if(GTM_TRIG_MSCNUM_0 == pConfig->Num)
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        *pMsc = &GTM_WRAP->MSC0MUX;
        value  = (uint32)pConfig->mscSet << shift;
    }
#if defined(THA6_THA6412)
    else if(GTM_TRIG_MSCNUM_1 == pConfig->Num)
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        *pMsc = &GTM_WRAP->MSC1MUX;
        value  = (uint32)pConfig->mscSet << shift;
    }
    else if(GTM_TRIG_MSCNUM_2 == pConfig->Num)
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        *pMsc = &GTM_WRAP->MSC2MUX;
        if (GTM_TRIG_MSCTRIGSET_0 == pConfig->mscSet)
        {
            value  = (uint32)pConfig->mscSet << shift;
        }
        else if (GTM_TRIG_MSCTRIGSET_2 == pConfig->mscSet)
        {
            value  = (uint32)1U << shift;
        }
        else if (GTM_TRIG_MSCTRIGSET_4 == pConfig->mscSet)
        {
            value  = (uint32)3U << shift;
        }
        else
        {
            value  = (uint32)2U << shift;
        }
    }
#endif
    else
    {
        *pMsc = NULL_PTR;
    }
    return value;
}
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: gtm_trig_hal_c_REF_5 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_trig_hal_c_REF_4 */
#include "Gtm_MemMap.h"

/* #Violation: gtm_trig_hal_c_REF_1 */
 boolean Gtm_Trig_Hal_ToSaradc(const Gtm_AdcTrigConfig *const pConfig)
{
    uint32 shift;
    uint32 mask;
    uint32 value;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    ret = TRUE;
    shift = ((uint32)pConfig->adcGroup % 8U) * 4U;
    mask  = ((uint32)0xFU << shift);
    value = (uint32)pConfig->select << shift;

    if (0U == ((uint32)pConfig->adcGroup / 8U))
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->ADCTRIG[pConfig->adcTrig].OUTMUX0.U = (GTM_WRAP->ADCTRIG[pConfig->adcTrig].OUTMUX0.U & ~mask) | 
                                                                                                        (mask & value);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & value, GTM_WRAP->ADCTRIG[pConfig->adcTrig].OUTMUX0.U & mask);
    }
    else
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->ADCTRIG[pConfig->adcTrig].OUTMUX1.U = (GTM_WRAP->ADCTRIG[pConfig->adcTrig].OUTMUX1.U & ~mask) | 
                                                                                                        (mask & value);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & value, GTM_WRAP->ADCTRIG[pConfig->adcTrig].OUTMUX1.U & mask);
    }
    return ret;
}

/* #Violation: gtm_trig_hal_c_REF_1 */
boolean Gtm_Trig_Hal_ToDmaL1(const Gtm_DmaTrigL1Config *const pConfig)
{
    uint32 mask;
    uint32 value;
    uint32 muxIndex;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    ret = TRUE;
    value = pConfig->select;
    mask = 0x3FU;
    /* DMA L1 MUX/COMMON_MUX configuration */
    if ((uint32)pConfig->trigL1Mux <= (uint32)GTM_TRIG_DMAL1_MUX_17)
    {
        muxIndex = (uint32)pConfig->trigL1Mux / 8U;
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->DMAL1MUX[muxIndex].MUX[(uint32)pConfig->trigL1Mux % 8U].U = 
                                    /* #Violation: gtm_trig_hal_c_REF_3 */
                                    (GTM_WRAP->DMAL1MUX[muxIndex].MUX[(uint32)pConfig->trigL1Mux % 8U].U & ~mask) | 
                                                                                                        (mask & value);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & value, 
                                    /* #Violation: gtm_trig_hal_c_REF_3 */
                                    GTM_WRAP->DMAL1MUX[muxIndex].MUX[(uint32)pConfig->trigL1Mux % 8U].U & mask);
    }
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    else if((uint32)pConfig->trigL1Mux <= (uint32)GTM_TRIG_DMAL1_MUX_37)
    {
        muxIndex = (uint32)pConfig->trigL1Mux / 8U;
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->DMAL1MUX[muxIndex].MUX[(uint32)pConfig->trigL1Mux % 8U].U = 
                                    /* #Violation: gtm_trig_hal_c_REF_3 */
                                    (GTM_WRAP->DMAL1MUX[muxIndex].MUX[(uint32)pConfig->trigL1Mux % 8U].U & ~mask) | 
                                                                                                        (mask & value);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & value, 
                                    /* #Violation: gtm_trig_hal_c_REF_3 */
                                    GTM_WRAP->DMAL1MUX[muxIndex].MUX[(uint32)pConfig->trigL1Mux % 8U].U & mask);
    }
#endif
#if defined(THA6_THA6412)
    else if(((uint32)pConfig->trigL1Mux >= (uint32)GTM_TRIG_DMAL1_MUX_40) && ((uint32)pConfig->trigL1Mux <= 
                                                                                        (uint32)GTM_TRIG_DMAL1_MUX_77))
    {
        muxIndex = ((uint32)pConfig->trigL1Mux - (uint32)GTM_TRIG_DMAL1_MUX_40) / 8U;
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->DMAL1MUX1[muxIndex].MUX[((uint32)pConfig->trigL1Mux - (uint32)GTM_TRIG_DMAL1_MUX_40) % 8U].U =
                                    /* #Violation: gtm_trig_hal_c_REF_3 */
                                    (GTM_WRAP->DMAL1MUX1[muxIndex].MUX[((uint32)pConfig->trigL1Mux -
                                                      (uint32)GTM_TRIG_DMAL1_MUX_40) % 8U].U & ~mask) | (mask & value);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & value, 
                                  /* #Violation: gtm_trig_hal_c_REF_3 */
                                  GTM_WRAP->DMAL1MUX1[muxIndex].MUX[((uint32)pConfig->trigL1Mux -
                                                                        (uint32)GTM_TRIG_DMAL1_MUX_40) % 8U].U & mask);
    }
#endif
    else
    {
        muxIndex = (uint32)pConfig->trigL1Mux - (uint32)GTM_TRIG_DMAL1_COMMUX_0;
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->DMAL1COMMUX[muxIndex].U = (GTM_WRAP->DMAL1COMMUX[muxIndex].U & ~mask) | (mask & value);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & value, GTM_WRAP->DMAL1COMMUX[muxIndex].U & mask);
    }
    return ret;
}

/* #Violation: gtm_trig_hal_c_REF_1 */
boolean Gtm_Trig_Hal_ToDmaL2(const Gtm_DmaTrigL2Config *const pConfig)
{
    uint32 mask;
    uint32 value;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    ret = TRUE;
    /* Enable DMA request output */
    /* #Violation: gtm_trig_hal_c_REF_3 */
    GTM_WRAP->IDRQEN.B.EN1 = 3U;

    /* DMA L2 MUX configuration */
    mask = GTM_DMAL2_MUX_MSK;
    value = (uint32)pConfig->trigL1Mux;
    /* #Violation: gtm_trig_hal_c_REF_3 */
    GTM_WRAP->DMAL2MUX[(uint32)pConfig->dmaChannel].U = 
                                    /* #Violation: gtm_trig_hal_c_REF_3 */
                                    (GTM_WRAP->DMAL2MUX[(uint32)pConfig->dmaChannel].U & ~mask) | (mask & value);
    /* #Violation: gtm_trig_hal_c_REF_3 */
    ret = Gtm_Register_ReadBack_Check(ret, mask & value, GTM_WRAP->DMAL2MUX[(uint32)pConfig->dmaChannel].U & mask);
    return ret;
}

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* #Violation: gtm_trig_hal_c_REF_1 */
boolean Gtm_Trig_Hal_ToMscL1(const Gtm_MscTrigL1Config *const pConfig)
{
    GTM_MSCSET    *pMscSet;
    uint32      shift;
    uint32      mask;
    uint32      value;
    uint32        configVal;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    ret = TRUE;
    /* #Violation: gtm_trig_hal_c_REF_6 */
    pMscSet = NULL_PTR;
    if ((uint32)pConfig->mscSet < 4U)
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        pMscSet = &GTM_WRAP->MSCSET[pConfig->mscSet];
    }
#if defined(THA6_THA6412)
    else
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        pMscSet = &GTM_WRAP->MSCSET1[(uint32)pConfig->mscSet - 4U];
    }
#endif

    /****************************** MSC MUX L1 configuration ******************************/
    configVal    = (uint32)pConfig->select;
    shift = ((uint32)pConfig->signals % 4U) * 8U;
    mask = ((uint32)0x1FU << shift);
    value = configVal << shift;

    if (NULL_PTR != pMscSet)
    {
        switch ((uint32)pConfig->signals / 4U)
        {
            case 0:
            {
                pMscSet->MUX0.U = (pMscSet->MUX0.U & ~mask) | (mask & value);
                /* #Violation: gtm_trig_hal_c_REF_3 */
                ret = Gtm_Register_ReadBack_Check(ret, mask & value, pMscSet->MUX0.U & mask);
                break;
            }
            case 1:
            {
                pMscSet->MUX1.U = (pMscSet->MUX1.U & ~mask) | (mask & value);
                /* #Violation: gtm_trig_hal_c_REF_3 */
                ret = Gtm_Register_ReadBack_Check(ret, mask & value, pMscSet->MUX1.U & mask);
                break;
            }
            case 2:
            {
                pMscSet->MUX2.U = (pMscSet->MUX2.U & ~mask) | (mask & value);
                /* #Violation: gtm_trig_hal_c_REF_3 */
                ret = Gtm_Register_ReadBack_Check(ret, mask & value, pMscSet->MUX2.U & mask);
                break;
            }
            case 3:
            {
                pMscSet->MUX3.U = (pMscSet->MUX3.U & ~mask) | (mask & value);
                /* #Violation: gtm_trig_hal_c_REF_3 */
                ret = Gtm_Register_ReadBack_Check(ret, mask & value, pMscSet->MUX3.U & mask);
                break;
            }
            default:
            {
                ret = FALSE;
                break;
            }
        }
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* #Violation: gtm_trig_hal_c_REF_1 */
boolean Gtm_Trig_Hal_ToMscL2(const Gtm_MscTrigL2Config *const pConfig)
{
    GTM_MSC *pMsc;
    uint32  shift;
    uint32  mask;
    uint32  value;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(TRUE == Gtm_Trig_Hal_ToMscL2Check(pConfig)));
#endif

    ret = TRUE;
    /****************************** MSC MUX L2 configuration ******************************/
    shift  = (uint32)pConfig->signals * 2U;
    mask   = ((uint32)0x3U << shift);

    /* Get MSC nput multiplex object and MSC sets */
    value = Gtm_Trig_Hal_GetMscMuxAndSets(pConfig, &pMsc, shift);

    if (NULL_PTR != pMsc)
    {
        switch (pConfig->input)
        {
            case GTM_TRIG_MSCTRIGINPUT_LOW:
            {
                /* #Violation: gtm_trig_hal_c_REF_3 */
                pMsc->INL.U = (pMsc->INL.U & ~mask) | (mask & value);
                /* #Violation: gtm_trig_hal_c_REF_3 */
                ret = Gtm_Register_ReadBack_Check(ret, mask & value, pMsc->INL.U & mask);
                break;
            }
            case GTM_TRIG_MSCTRIGINPUT_LOWEXTENDED:
            {
                /* #Violation: gtm_trig_hal_c_REF_3 */
                pMsc->INLEXT.U = (pMsc->INLEXT.U & ~mask) | (mask & value);
                /* #Violation: gtm_trig_hal_c_REF_3 */
                ret = Gtm_Register_ReadBack_Check(ret, mask & value, pMsc->INLEXT.U & mask);
                break;
            }
            case GTM_TRIG_MSCTRIGINPUT_HIGH:
            {
                /* #Violation: gtm_trig_hal_c_REF_3 */
                pMsc->HNL.U = (pMsc->HNL.U & ~mask) | (mask & value);
                /* #Violation: gtm_trig_hal_c_REF_3 */
                ret = Gtm_Register_ReadBack_Check(ret, mask & value, pMsc->HNL.U & mask);
                break;
            }
            default:
            {
                ret = FALSE;
                break;
            }
        }
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */

/* #Violation: gtm_trig_hal_c_REF_1 */
boolean Gtm_Trig_Hal_TimIn(const Gtm_Tim_In *const pTin)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pTin));
#endif

    uint32 shift;
    uint32 mask;
    uint32 inSel;
    boolean ret;

    ret = TRUE;
    shift = (uint32)pTin->channel * 4U;
    mask = ((uint32)0xFU << shift);
    inSel = (uint32)pTin->select << shift;

    if(3U > (uint32)pTin->tim)
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->TIMINMUX[pTin->tim].U = (GTM_WRAP->TIMINMUX[pTin->tim].U & ~mask) | (mask & inSel);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & inSel, GTM_WRAP->TIMINMUX[pTin->tim].U & mask);
    }
#if defined(THA6_THA6412)
    else
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->TIMINMUX1[(uint32)pTin->tim - 3U].U = (GTM_WRAP->TIMINMUX1[(uint32)pTin->tim - 3U].U & ~mask) | 
                                                                                (mask & inSel);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & inSel, GTM_WRAP->TIMINMUX1[(uint32)pTin->tim - 3U].U & mask);
    }
#endif

    return ret;
}

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* #Violation: gtm_trig_hal_c_REF_1 */
boolean Gtm_Trig_Hal_DsadcIn(const Gtm_Dsadc_In *const pDsadcIn)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDsadcIn));
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)((uint32)pDsadcIn->index < GTM_DSADC_IN_MUX_NUM));
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)((uint32)pDsadcIn->mux < 8U));
#endif

    uint32 shift;
    uint32 mask;
    uint32 inSel;
    boolean ret;

    ret = TRUE;
    shift = (uint32)pDsadcIn->mux * 4U;
    mask = ((uint32)0xFU << shift);
    inSel = (uint32)pDsadcIn->select << shift;

    if(3U > pDsadcIn->index)
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->DSADCINMUX[pDsadcIn->index].U = (GTM_WRAP->DSADCINMUX[pDsadcIn->index].U & ~mask) | (mask & inSel);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & inSel, GTM_WRAP->DSADCINMUX[pDsadcIn->index].U & mask);
    }
#if defined(THA6_THA6412)
    else
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->DSADCINMUX1[pDsadcIn->index - 3U].U = (GTM_WRAP->DSADCINMUX1[pDsadcIn->index - 3U].U & ~mask) | 
                                                                                (mask & inSel);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & inSel, GTM_WRAP->DSADCINMUX1[pDsadcIn->index - 3U].U & mask);
    }
#endif

    return ret;
}
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
/* #Violation: gtm_trig_hal_c_REF_1 */
boolean Gtm_Trig_Hal_ToDsadc(const Gtm_Dsadc_Out *const pDsadcOut)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pDsadcOut));
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)((uint32)pDsadcOut->index < GTM_DSADC_OUT_MUX_NUM));
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)((uint32)pDsadcOut->mux < GTM_DSADC_NUM));
#endif

    uint32 shift;
    uint32 mask;
    uint32 inSel;
    boolean ret;

    ret = TRUE;
    shift = ((uint32)pDsadcOut->mux % 8U) * 4U;
    mask = ((uint32)0xFU << shift);
    inSel = (uint32)pDsadcOut->select << shift;

    if(8U > pDsadcOut->mux)
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->DSADCOUTMUX[pDsadcOut->index].U = (GTM_WRAP->DSADCOUTMUX[pDsadcOut->index].U & ~mask) | 
                                                                                (mask & inSel);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & inSel, GTM_WRAP->DSADCOUTMUX[pDsadcOut->index].U & mask);
    }
#if defined(THA6_THA6412)
    else
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->DSADCOUTMUX1[pDsadcOut->index].U = (GTM_WRAP->DSADCOUTMUX1[pDsadcOut->index].U & ~mask) | 
                                                                                (mask & inSel);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & inSel, GTM_WRAP->DSADCOUTMUX1[pDsadcOut->index].U & mask);
    }
#endif

    return ret;
}
#endif /* THA6_THA6206 || THA6_THA6206D || THA6_THA6412 */

/* #Violation: gtm_trig_hal_c_REF_1 */
boolean Gtm_Trig_Hal_ToutOut(const Gtm_Tout_Out *const pTout)
{
#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pTout));
    /* #Violation: gtm_trig_hal_c_REF_2 */
    Assert((boolean)(pTout->toutNum < GTM_TOUT_NUM));
#endif

    uint32 outmux; /* Number of TOUTSELxx */
    uint32 shift; /* current absolute bit number of LSB of current SELx */
    uint32 outSel;
    uint32 mask;
    boolean ret;

    ret = TRUE;
    outmux = (pTout->toutNum >> 3U);
    shift = (pTout->toutNum & 0x7U) * 4U;
    outSel = (uint32)pTout->toutSel << shift;
    mask = ((uint32)0xFU << shift);

    if(17U > outmux)
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->TOUTMUX[outmux].U = (GTM_WRAP->TOUTMUX[outmux].U & ~mask) | (mask & outSel);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & outSel, GTM_WRAP->TOUTMUX[outmux].U & mask);
    }
#if defined(THA6_THA6412)
    else
    {
        /* #Violation: gtm_trig_hal_c_REF_3 */
        /* #Violation: gtm_trig_hal_c_REF_3 */
        GTM_WRAP->TOUTMUX1[outmux - 17U].U = (GTM_WRAP->TOUTMUX1[outmux -17U].U & ~mask) | (mask & outSel);
        /* #Violation: gtm_trig_hal_c_REF_3 */
        ret = Gtm_Register_ReadBack_Check(ret, mask & outSel, GTM_WRAP->TOUTMUX1[outmux - 17U].U & mask);
    }
#endif

    return ret;
}

/* #Violation: gtm_trig_hal_c_REF_5 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_trig_hal_c_REF_4 */
#include "Gtm_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

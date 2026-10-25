/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName   : exti_hal.c
 * Author     : 01077
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all hardware abstract layer implementations of requirements of EXTI module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #exti_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
* #exti_hal_c_REF_2:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core. Boolean can only be representes as uint8.
*
* #exti_hal_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #exti_hal_c_REF_4:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured 
*                by code review.
*
* #exti_hal_c_REF_5:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #exti_hal_c_REF_6:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
* #exti_hal_c_REF_7:MISRAC2012-Rule-8.7;
* Justification:The interface is called by the application layer.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "exti_hal.h"
#include "cpuwdt_hal.h"
#include "tha6_cfg.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif
/**********************************************************************************************************************
 *                                                      Macros
 *********************************************************************************************************************/
/* EXTI ETL module number */
/* #Violation: exti_hal_c_REF_6 */
#define EXTI_ETL_MODULE_NUMBER (8U)
/* EXTI OGU module number */
/* #Violation: exti_hal_c_REF_6 */
#define EXTI_OGU_MODULE_NUMBER (8U)

/* Bits mask */
/* High 16 bits mask */
#define EXTI_BIT_MASK_HIGH_16 (0x0000FFFFU) 
/* Low 16 bits mask */
#define EXTI_BIT_MASK_LOW_16 (0xFFFF0000U)  

/* Register bit offset */
/* Register offset 8 */
#define EXTI_BIT_OFFSET_8 (8U)         
/* Register offset 16 */
#define EXTI_BIT_OFFSET_16 (16U)       
/* Register offset 24 */
#define EXTI_BIT_OFFSET_24 (24U)       

/* The maximum number of ETL participating in pattern detection */
/* Max number of 8 bit */
/* #Violation: exti_hal_c_REF_6 */
#define EXTI_8_BIT_MAX_NUMBER (0xFFU)       
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: exti_hal_c_REF_6 */
#define EXTI_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: exti_hal_c_REF_5 */
#include "Exti_MemMap.h"

/* #Violation: exti_hal_c_REF_1 */
 boolean Exti_Hal_Init(const Exti_Config *const pConfig)
{
    uint8 moduleNumber;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(EXTI_ETL_MODULE_NUMBER >= pConfig->inputChannelConfigLength));
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(EXTI_OGU_MODULE_NUMBER >= pConfig->outputChannelConfigLength));
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig->inputChannelConfig));
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig->outputChannelConfig));
#endif

    ret = TRUE;
    /* Configure filter */
    ret &= Exti_Hal_InitFilter(&pConfig->filterConfig);

    /* Configure selected ETL module */
    for(moduleNumber = 0U; moduleNumber < pConfig->inputChannelConfigLength; moduleNumber++)
    {
        ret &= Exti_Hal_InitInputChannel(&pConfig->inputChannelConfig[moduleNumber]);
    }

    /* Configure selected OGU module */
    for(moduleNumber = 0U; moduleNumber < pConfig->outputChannelConfigLength; moduleNumber++)
    {
        ret &= Exti_Hal_InitOutputChannel(&pConfig->outputChannelConfig[moduleNumber]);
    }

    return ret;
}

/* #Violation: exti_hal_c_REF_1 */
/* #Violation: exti_hal_c_REF_7 */
boolean Exti_Hal_InitFilter(const Exti_FilterConfig *const pConfig)
{
    /* #Violation: exti_hal_c_REF_4 */
    EXTI_EXIFLT filter;
    boolean ret;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(pConfig->filterMask <= (uint32)0x7FFFFU));
#endif

    ret = TRUE;
    /* #Violation: exti_hal_c_REF_3 */
    filter.U = EXTI->EXIFLT.U;
    filter.B.DFDTH = (uint32)pConfig->filterDepth;
    filter.B.FDCDFSC = (uint32)pConfig->filterPredivider;

    /* Configure filter */
    if(0U != pConfig->filterMask)
    {
        if(EXTI_STATE_ENABLE == pConfig->filterEnable) /* Enable selected filter */
        {
            filter.U |= pConfig->filterMask;
        }
        else
        {
            filter.U &= (~(pConfig->filterMask));
        }
    }

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit(); /* Unlock endinit protect */
    /* #Violation: exti_hal_c_REF_3 */
    EXTI->EXIFLT.U = filter.U; /* Write EXTI register */
    ret &= Cpuwdt_Hal_SetEndinit();   /* Lock endinit protect */
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: exti_hal_c_REF_3 */
    ret = Exti_Register_ReadBack_Check(ret, filter.U, EXTI->EXIFLT.U);
    return ret;
}

/* #Violation: exti_hal_c_REF_1 */
/* #Violation: exti_hal_c_REF_7 */
boolean Exti_Hal_InitInputChannel(const Exti_InputChannelConfig *const pConfig)
{
    uint8 numEtl;
    boolean ret;
    /* #Violation: exti_hal_c_REF_4 */
    EXTI_ETIPC ctrl;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
#endif

    ret = TRUE;
    numEtl = (uint8)pConfig->inputChannel >> 1U; /* Calculate the register offset */
    /* #Violation: exti_hal_c_REF_3 */
    ctrl.U = EXTI->ETIPC[numEtl].U;             /* Read EXTI register */

    /* Set EXTI configure register structure */
    if(1U == ((uint32)pConfig->inputChannel & 1U)) /* ETL nmber is an odd number */
    {
        ctrl.U &= EXTI_BIT_MASK_HIGH_16; /* Clear EXTI register */
        ctrl.B.ETIPS1 = (uint32)pConfig->inputMultiplexer;
        ctrl.U |= ((uint32)pConfig->edgeDetectionMode << EXTI_BIT_OFFSET_24);
        ctrl.B.LEDEEN1 = (uint32)pConfig->autoClear;
        ctrl.B.ETIPEN1 = (uint32)pConfig->triggerEnable;
        ctrl.B.INNOP1 = (uint32)pConfig->triggerOutput;
    }
    else /* ETL nmber is an even number */
    {
        ctrl.U &= EXTI_BIT_MASK_LOW_16; /* Clear EXTI register */
        ctrl.B.ETIPS0 = (uint32)pConfig->inputMultiplexer;
        ctrl.U |= ((uint32)pConfig->edgeDetectionMode << EXTI_BIT_OFFSET_8);
        ctrl.B.LEDEEN0 = (uint32)pConfig->autoClear;
        ctrl.B.ETIPEN0 = (uint32)pConfig->triggerEnable;
        ctrl.B.INNOP0 = (uint32)pConfig->triggerOutput;
    }

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();       /* Unlock endinit protect */
    /* #Violation: exti_hal_c_REF_3 */
    EXTI->ETIPC[numEtl].U = ctrl.U; /* Write EXTI register */
    ret &= Cpuwdt_Hal_SetEndinit();         /* Lock endinit protect */
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: exti_hal_c_REF_3 */
    ret = Exti_Register_ReadBack_Check(ret, ctrl.U, EXTI->ETIPC[numEtl].U);
    return ret;
}

/* #Violation: exti_hal_c_REF_1 */
/* #Violation: exti_hal_c_REF_7 */
boolean Exti_Hal_InitOutputChannel(const Exti_OutputChannelConfig *const pConfig)
{
    uint8 numIntgc;
    boolean ret;
    /* #Violation: exti_hal_c_REF_4 */
    EXTI_INTGC gate;

#if(STD_ON == INPUT_ARG_DETECT)
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: exti_hal_c_REF_2 */
    Assert((boolean)(EXTI_8_BIT_MAX_NUMBER >= pConfig->patternDetectSelection));
#endif

    ret = TRUE;
    numIntgc = (uint8)pConfig->outputChannel >> 1U; /* Calculate the register offset */
    /* #Violation: exti_hal_c_REF_3 */
    gate.U = EXTI->INTGC[numIntgc].U;              /* Read EXTI register */

    if(1U == ((uint32)pConfig->outputChannel & 1U)) /* OGU nmber is an odd number */
    {
        gate.U &= EXTI_BIT_MASK_HIGH_16; /* Clear EXTI register */
        gate.U |= (pConfig->patternDetectSelection << EXTI_BIT_OFFSET_16);
        gate.B.EGEN1 = (uint32)pConfig->patternTrigger;
        gate.B.IGM1 = (uint32)pConfig->triggerGatingMode;
    }
    else /* OGU nmber is an even number */
    {
        gate.U &= EXTI_BIT_MASK_LOW_16; /* Clear EXTI register */
        gate.U |= pConfig->patternDetectSelection;
        gate.B.EGEN0 = (uint32)pConfig->patternTrigger;
        gate.B.IGM0 = (uint32)pConfig->triggerGatingMode;
    }

    DISABLE_ALL_INTERRUPTS();
    ret &= Cpuwdt_Hal_ClearEndinit();         /* Unlock endinit protect */
    /* #Violation: exti_hal_c_REF_3 */
    EXTI->INTGC[numIntgc].U = gate.U; /* Write EXTI register */
    ret &= Cpuwdt_Hal_SetEndinit();           /* Lock endinit protect */
    ENABLE_ALL_INTERRUPTS();

    /* #Violation: exti_hal_c_REF_3 */
    ret = Exti_Register_ReadBack_Check(ret, gate.U, EXTI->INTGC[numIntgc].U);
    return ret;
}

/* #Violation: exti_hal_c_REF_1 */
Exti_PatternDetectResult Exti_Hal_GetPatternDetectResult(Exti_OutputChannel outputChannel)
{
    Exti_PatternDetectResult patternResult = EXTI_PATTERNDETECTRESULT_MISS;

    /* Get selected OGU pattern detect result */
    /* #Violation: exti_hal_c_REF_3 */
    if(0U != (EXTI->PADERR.U & (1UL << (uint32)outputChannel)))
    {
        patternResult = EXTI_PATTERNDETECTRESULT_MATCH;
    }

    return patternResult;
}

/* #Violation: exti_hal_c_REF_6 */
#define EXTI_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: exti_hal_c_REF_5 */
#include "Exti_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

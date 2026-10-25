/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    port_hal_esr.c
 * Author:      01077
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all hardware abstract layer implementations of requirements of PORT esr module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#port_hal_esr_c_REF_1:MISRAC2012-Rule-2.1; 
* Justification:Hal layer API needs to be provided to the upper layer.
*
*#port_hal_esr_c_REF_2:MISRAC2012-Rule-11.4; 
* Justification:Converting integers to object pointers to reduce register access complexity.
*
*#port_hal_esr_c_REF_3:MISRAC2012-Rule-10.5; 
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8
*
*#port_hal_esr_c_REF_4:MISRAC2012-Rule-19.2;
* Justification:Using unions for bit-field access to registers.
*
*#port_hal_esr_c_REF_5:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
*#port_hal_esr_c_REF_6:MISRAC2012-Dir-4.2;
* Justification:The assembler statements is used to synchronize the data of the ARM core.
*
*#port_hal_esr_c_REF_7:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "cpuwdt_hal.h"
#include "port_hal_esr.h"
#include "port_hal.h"
#include "compilertypes.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
#define PORT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: port_hal_esr_c_REF_7 */
#include "Port_MemMap.h"

/* #Violation: port_hal_esr_c_REF_1 */
boolean Port_Hal_Esr_Init(const Port_EsrConfig *const pConfig)
{
    boolean ret;
    /* #Violation: port_hal_esr_c_REF_4 */
    ESR_CTR0 ctrValue;
    /* #Violation: port_hal_esr_c_REF_4 */
    ESR_DSR0 dsrValue;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: port_hal_esr_c_REF_3 */
    Assert((boolean)(NULL_PTR != pConfig));
    /* #Violation: port_hal_esr_c_REF_3 */
    Assert((boolean)((PORT_ESR_PIN_0 == pConfig->pin) || (PORT_ESR_PIN_1 == pConfig->pin)));
#endif

    ret = TRUE;

    /* ESR0 */
    if (PORT_ESR_PIN_0 == pConfig->pin)
    {
        /* write ctr0 and psr register */
        /* #Violation: port_hal_esr_c_REF_2 */
        ctrValue.U = PORT_PESR->CTR0.U;
        /* Input disable / enable */
        ctrValue.B.DSI0 = pConfig->inputDis;
        /* Output multiplexer */
        ctrValue.B.SEL0 = pConfig->outputSel;
        /* Select push-pull/open-drain */
        ctrValue.B.OD0 = pConfig->outputMode;
        /* Output disable */
        ctrValue.B.ENO0 = FALSE;  
        /* #Violation: port_hal_esr_c_REF_2 */
        PORT_PESR->CTR0.U = ctrValue.U;
        /* #Violation: port_hal_esr_c_REF_2 */
        ret = Port_Register_ReadBack_Check(ret, ctrValue.U, PORT_PESR->CTR0.U);   

        /* Output Enable / disable */
        ctrValue.B.ENO0 = pConfig->outputEn;  
        /* #Violation: port_hal_esr_c_REF_2 */
        PORT_PESR->CTR0.U = ctrValue.U;
        /* #Violation: port_hal_esr_c_REF_2 */
        ret = Port_Register_ReadBack_Check(ret, ctrValue.U, PORT_PESR->CTR0.U);   

        /* #Violation: port_hal_esr_c_REF_2 */
        PORT_PESR->PSR.B.PS0 = pConfig->pullResistor; 
        /* #Violation: port_hal_esr_c_REF_2 */
        ret = Port_Register_ReadBack_Check(ret, (uint32)pConfig->pullResistor, (uint32)PORT_PESR->PSR.B.PS0);  

        if (NULL_PTR != pConfig->pPadDriverCfg)
        {
            /* #Violation: port_hal_esr_c_REF_2 */
            dsrValue.U = PORT_PESR->DSR0.U;
            /* drive strength selection */
            dsrValue.B.DR0 = pConfig->pPadDriverCfg->driveStrength;  
            /* pad level (AL, TTL) selection */    
            dsrValue.B.PL0 = pConfig->pPadDriverCfg->level;    
            /* slew rate enable/disable */ 
            dsrValue.B.SR0 = pConfig->pPadDriverCfg->slewRate;   
            /* Input Mode Selection */  
            dsrValue.B.IS0 = pConfig->pPadDriverCfg->inputMode;   

            /* Unlock endinit protect */
            /* #Violation: port_hal_esr_c_REF_6 */      
            DISABLE_ALL_INTERRUPTS();
            ret &= Cpuwdt_Hal_ClearEndinit();
            /* #Violation: port_hal_esr_c_REF_2 */
            PORT_PESR->DSR0.U = dsrValue.U;     
            /* Lock endinit protect */
            ret &= Cpuwdt_Hal_SetEndinit();
            /* #Violation: port_hal_esr_c_REF_6 */    
            ENABLE_ALL_INTERRUPTS();
            /* #Violation: port_hal_esr_c_REF_2 */
            ret = Port_Register_ReadBack_Check(ret, dsrValue.U, PORT_PESR->DSR0.U);  
        }
    }
    /* ESR1 */
    else
    {
        /* write ctr0 and psr register */
        /* #Violation: port_hal_esr_c_REF_2 */
        ctrValue.U = PORT_PESR->CTR0.U;
        /* Input disable / enable */
        ctrValue.B.DSI1 = pConfig->inputDis;
        /* Output multiplexer */
        ctrValue.B.SEL1 = pConfig->outputSel;
        /* Select push-pull/open-drain */
        ctrValue.B.OD1 = pConfig->outputMode;
        /* Output disable */
        ctrValue.B.ENO1 = FALSE;  
        /* #Violation: port_hal_esr_c_REF_2 */
        PORT_PESR->CTR0.U = ctrValue.U;
        /* #Violation: port_hal_esr_c_REF_2 */
        ret = Port_Register_ReadBack_Check(ret, ctrValue.U, PORT_PESR->CTR0.U);   

        /* Output Enable / disable */
        ctrValue.B.ENO1 = pConfig->outputEn;  
        /* #Violation: port_hal_esr_c_REF_2 */
        PORT_PESR->CTR0.U = ctrValue.U;
        /* #Violation: port_hal_esr_c_REF_2 */
        ret = Port_Register_ReadBack_Check(ret, ctrValue.U, PORT_PESR->CTR0.U);   

        /* #Violation: port_hal_esr_c_REF_2 */
        PORT_PESR->PSR.B.PS1 = pConfig->pullResistor; 
        /* #Violation: port_hal_esr_c_REF_2 */
        ret = Port_Register_ReadBack_Check(ret, (uint32)pConfig->pullResistor, (uint32)PORT_PESR->PSR.B.PS1);  

        if (NULL_PTR != pConfig->pPadDriverCfg)
        {
            /* #Violation: port_hal_esr_c_REF_2 */
            dsrValue.U = PORT_PESR->DSR0.U;
            /* drive strength selection */
            dsrValue.B.DR1 = pConfig->pPadDriverCfg->driveStrength;  
            /* pad level (AL, TTL) selection */    
            dsrValue.B.PL1 = pConfig->pPadDriverCfg->level;    
            /* slew rate enable/disable */ 
            dsrValue.B.SR1 = pConfig->pPadDriverCfg->slewRate;   
            /* Input Mode Selection */  
            dsrValue.B.IS1 = pConfig->pPadDriverCfg->inputMode;   

            /* Unlock endinit protect */
            /* #Violation: port_hal_esr_c_REF_6 */  
            DISABLE_ALL_INTERRUPTS();
            ret &= Cpuwdt_Hal_ClearEndinit();
            /* #Violation: port_hal_esr_c_REF_2 */
            PORT_PESR->DSR0.U = dsrValue.U;     
            /* Lock endinit protect */
            ret &= Cpuwdt_Hal_SetEndinit();
            /* #Violation: port_hal_esr_c_REF_6 */  
            ENABLE_ALL_INTERRUPTS();
            /* #Violation: port_hal_esr_c_REF_2 */
            ret = Port_Register_ReadBack_Check(ret, dsrValue.U, PORT_PESR->DSR0.U);  
        }
    }

    return ret;
}

/* #Violation: port_hal_esr_c_REF_1 */
uint8 Port_Hal_Esr_ClearAppResetIndicator(void)
{
    uint8 runState;
    uint32 timeout;
    boolean ret;

    runState = PORT_RUNSTATE_NOT_OK;

    /* Clear Application Reset Indicator */
    /* #Violation: port_hal_esr_c_REF_6 */  
    DISABLE_ALL_INTERRUPTS();
    ret = Cpuwdt_Hal_ClearEndinit();
    /* #Violation: port_hal_esr_c_REF_2 */
    PORT_PESR->OCFG.B.ARC = 1U;
    ret &= Cpuwdt_Hal_SetEndinit();
    /* #Violation: port_hal_esr_c_REF_6 */
    ENABLE_ALL_INTERRUPTS();

    /* Wait for Application Reset Indicator clear */
    timeout = 0U;
    /* #Violation: port_hal_esr_c_REF_2 */
    while ((timeout < 0xFFFFU) && (1U == (PORT_PESR->OCFG.B.ARI & 1U)))
    {
        timeout++;
    }

    /* #Violation: port_hal_esr_c_REF_2 */
    if (0U == (PORT_PESR->OCFG.B.ARI & 1U))
    {
        /* Clear Reset Mask Indicator */
        /* #Violation: port_hal_esr_c_REF_6 */
        DISABLE_ALL_INTERRUPTS();
        ret &= Cpuwdt_Hal_ClearEndinit();
        /* #Violation: port_hal_esr_c_REF_2 */
        PORT_PESR->OCFG.B.MSKC = 1U;
        ret &= Cpuwdt_Hal_SetEndinit();
        /* #Violation: port_hal_esr_c_REF_6 */
        ENABLE_ALL_INTERRUPTS();

        runState = PORT_RUNSTATE_OK;
    }

    return ((TRUE == ret) && (PORT_RUNSTATE_OK == runState)) ? PORT_RUNSTATE_OK : PORT_RUNSTATE_NOT_OK;
}

#define PORT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: port_hal_esr_c_REF_7 */
#include "Port_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

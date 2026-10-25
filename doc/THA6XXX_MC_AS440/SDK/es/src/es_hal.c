/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    es_hal.c
 * Author:      01321
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of ES module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#es_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*#es_hal_c_REF_2:MISRAC2012-Rule-19.2;
* Justification:Using unions for bit-field access to registers
*
*#es_hal_c_REF_3:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8
*
*#es_hal_c_REF_4:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity
*
*#es_hal_c_REF_5:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity
*
*#es_hal_c_REF_6:MISRAC2012-Dir-4.2;
* Justification:The assembler statements is used to synchronize the data of the ARM core.
*
*#es_hal_c_REF_7:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "es_hal.h"
#include "Platform_Types.h"
#include "compilertypes.h"
#include "es_register.h"
#include "safewdt_hal.h"
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
#define ES_START_SEC_CODE_ASIL_D_GLOBAL
#include "Es_MemMap.h"

/* #Violation: es_hal_c_REF_1 */
boolean Es_Hal_Init(const Es_Config *const pEsconfig)
{
    /* #Violation: es_hal_c_REF_2 */
    ES_ESCTRL esctrlValue;
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the pIntList is null pointer */
    /* #Violation: es_hal_c_REF_3 */
    Assert((boolean)(NULL_PTR != pEsconfig));
    /* #Violation: es_hal_c_REF_3 */
    Assert((boolean)(pEsconfig->glitchWidth <= ES_MAX_WIDTH_GLITCH_FILTER));
#endif /* INPUT_ARG_DETECT */

    ret = TRUE;
    esctrlValue.U = 0x1U;
    /* Port Selection Configuration */
    esctrlValue.B.PSEL = (uint32)(pEsconfig->portID);
    /* Glitch Enable Configuration */
    esctrlValue.B.PBGFEN = (uint32)(pEsconfig->portBGlitch);
    /* Configure width of glitch filter */
    esctrlValue.B.PBGFCNT = (uint32)(pEsconfig->glitchWidth);
    /* Polarity Active Configuration */
    esctrlValue.B.POL = (uint32)(pEsconfig->polarity);
    /* Mode Selection Configuration */
    esctrlValue.B.MODE = (uint32)(pEsconfig->mode);
    /* Enable Synchronous EMSF flag */
    esctrlValue.B.ENON = 1U;

    /* #Violation: es_hal_c_REF_6 */
    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit(); /* Unlock safe endinit protect */
    /* #Violation: es_hal_c_REF_4 */
    ES->ESCTRL.U = esctrlValue.U;
    ret &= Safewdt_Hal_SetSafetyEndinit(); /* Lock safe endinit protect */
    /* #Violation: es_hal_c_REF_6 */
    ENABLE_ALL_INTERRUPTS();
    /* #Violation: es_hal_c_REF_4 */
    ret = Es_Register_ReadBack_Check(ret, esctrlValue.U, ES->ESCTRL.U);

    return ret;
}

/* #Violation: es_hal_c_REF_1 */
void Es_Hal_TriggerES(Es_Flag flagType)
{
    /* Determine the Flag type */
    if(ES_FLAG_SAC == flagType)
    {
        /* Set SEMSF Flag */
        /* #Violation: es_hal_c_REF_4 */
        ES->ESCMD.B.SEMSFM = 1U;
    }
    else
    {
        /* Set EMSF Flag */
        /* #Violation: es_hal_c_REF_4 */
        ES->ESCMD.B.EMSFM = 1U;
    }
}

/* #Violation: es_hal_c_REF_1 */
void Es_Hal_TerminateES(Es_Flag flagType)
{
    /* Determine the Flag type */
    if(ES_FLAG_SAC == flagType)
    {
        /* Clear SEMSF Flag */
        /* #Violation: es_hal_c_REF_4 */
        ES->ESCMD.B.SEMSFM = 2U;
    }
    else
    {
        /* Clear EMSF Flag */
        /* #Violation: es_hal_c_REF_4 */
        ES->ESCMD.B.EMSFM = 2U;
    }
}

/* #Violation: es_hal_c_REF_1 */
Es_Status Es_Hal_GetAlarmFlagStatus(Es_AlarmStatusFlag flagStatus)
{
    Es_Status alarmStatus;
    /* Check the specific bit have a flag */
    /* #Violation: es_hal_c_REF_4 */
    alarmStatus = (0U == (ES->ALMSTS.U & (uint32)flagStatus)) ? ES_STATUS_RESET : ES_STATUS_SET;
    return alarmStatus;
}

/* #Violation: es_hal_c_REF_1 */
void Es_Hal_ClearAlarmFlagStatus(void)
{
    /* Clear all the Alarm flag */
    /* #Violation: es_hal_c_REF_4 */
    ES->ESCMD.B.ALMCLR = 3U;
}

/* #Violation: es_hal_c_REF_1 */
Es_Status Es_Hal_GetFlagStatus(Es_Flag flagStatus)
{
    uint32 status;
    
    /* Check the specific bit have a flag */
    if(ES_FLAG_SAC == flagStatus)
    {
        /* #Violation: es_hal_c_REF_4 */
        status = (uint32)ES->ESCTRL.B.SEMSF;
    }
    else
    {
        /* #Violation: es_hal_c_REF_4 */
        status = (uint32)ES->ESCTRL.B.EMSF;
    }
    return (1U == status) ? ES_STATUS_SET : ES_STATUS_RESET;
}

#define ES_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: es_hal_c_REF_7 */
#include "Es_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: busprot_hal.c
 * Author:   00930
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: BUSPROT hardware abstraction layer source file.
 *              This file contains implementations for BUSPROT hardware abstraction layer.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
 * #Violation Summary
 *
 * #busprot_hal_c_REF_1:MISRAC2012-Rule-10.5;
 * Justification: Cortex-R52+ lacks bool type, minimum unit is uint8.
 *
 * #busprot_hal_c_REF_2:MISRAC2012-Dir-4.9;
 * Justification: Function like macros are used to reduce code complexity.
 *
 * #busprot_hal_c_REF_3:MISRAC2012-Rule-11.4;
 * Justification: Converting integers to object pointers to reduce register access complexity.
 *
 * #busprot_hal_c_REF_4:MISRAC2012-Rule-19.2;
 * Justification: Necessary union type for bitwise access to register. Data integrity and correctness will be ensured
 *                by code review.
 *
 * #busprot_hal_c_REF_5:MISRAC2012-Rule-2.1;
 * Justification: The interface is called by the application layer.
 *
 * #busprot_hal_c_REF_6:MISRAC2012-Rule-2.5;
 * Justification: The macros are reserved for upper layers.
 *
 * #busprot_hal_c_REF_7:MISRAC2012-Rule-20.1;
 * Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
 *
 * #busprot_hal_c_REF_8:MISRAC2012-Dir-4.3;
 * Justification:Mixing inline assembly with C code reduces code complexity
 * 
 * #busprot_hal_c_REF_9:MISRAC2012-Dir-1.1;
 * Justification:Inline assembly for CPU-specific operations.
 * 
 * #busprot_hal_c_REF_10:MISRAC2012-Rule-1.2;
 * Justification:Inline assembly for CPU-specific operations.
 *
 * #busprot_hal_c_REF_11:MISRAC2012-Dir-4.2;
 * Justification:Inline assembly for CPU-specific operations.
 */

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "busprot_register.h"
#include "busprot_hal.h"
#include "safewdt_hal.h"
#if (INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* Bus protect type */
#define BUSPROT_AXI_BUS (0U) /* AXI bus */
#define BUSPROT_AHB_BUS (1U) /* AHB bus */
#define BUSPROT_APB_BUS (2U) /* APB bus */

/* Slave busprot */
#define BUSPROT_SLAVE (1U)

/* Master Id logic control */
#define BUSPROT_MASTERID_LOGIC_CONTROL (0x0000000FU)
/* Busprot timeout enable */
#define BUSPROT_TIMEOUT_ENABLE (0x03U)
/* Busprot timeout disable */
#define BUSPROT_TIMEOUT_DISABLE (0x00U)
/* Busprot error clear */
#define BUSPROT_ERR_CLR (0x03U)

/* Master Id mask  */
#define BUSPROT_ACCEN_MASK (0x0007FFFFU)
/* Busprot mask register mask */
#define BUSPROT_MSK_MASK (0x3FFU)
/* Busprot alarm status mask */
#define BUSPROT_ALMSTS_MASK (0xFFFU)
/* Busprot alarm clear mask */
#define BUSPROT_ALMCLR_MASK (0xFFU)

/* #Violation: busprot_hal_c_REF_6 */
#define BUSPROT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: busprot_hal_c_REF_7 */
#include "Busprot_MemMap.h"

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: busprot_hal_c_REF_5 */
/* #Violation: busprot_hal_c_REF_8 */
boolean Busprot_Hal_SetMasterId(Busprot_OffsetAddress busprotOffAddr, uint32 accessEnable)
{
    boolean ret;
    ret = TRUE;
    BUSPROT_MODULE *pBusprotModule;
    /* #Violation: busprot_hal_c_REF_3 */
    pBusprotModule = (BUSPROT_MODULE *)((uint32)busprotOffAddr + BUSPROT_BASE_ADDRESS);
#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: busprot_hal_c_REF_4 */
    BUSPROT_ID regId;
    regId.U = pBusprotModule->ID.U;
    /* #Violation: busprot_hal_c_REF_1 */
    Assert((boolean)(BUSPROT_SLAVE == regId.B.MOD_DIR));
#endif

    DISABLE_ALL_INTERRUPTS();
    /* Clear SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_ClearSafetyEndinit();

    /* Clear the access commands on the bus before modifying the access permissions */
    /* #Violation: busprot_hal_c_REF_9 */
    /* #Violation: busprot_hal_c_REF_10 */
    /* #Violation: busprot_hal_c_REF_11 */
    ISB();

    /* Set master ID access enable */
    pBusprotModule->ACCEN.U = accessEnable & BUSPROT_ACCEN_MASK;
    pBusprotModule->ACTRL.U = BUSPROT_MASTERID_LOGIC_CONTROL;
    /* Set SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Busprot_Register_ReadBack_Check(ret, (uint32)(accessEnable & BUSPROT_ACCEN_MASK), (uint32)pBusprotModule->ACCEN.U);
    ret = Busprot_Register_ReadBack_Check(ret, (uint32)(BUSPROT_MASTERID_LOGIC_CONTROL), (uint32)pBusprotModule->ACTRL.U);

    return ret;
}
/* #Violation: busprot_hal_c_REF_5 */
boolean Busprot_Hal_EnableTimeoutProt(Busprot_OffsetAddress busprotOffAddr, uint32 timeoutThreshold)
{
    boolean ret;
    ret = TRUE;
    BUSPROT_MODULE *pBusprotModule;

#if (STD_ON == INPUT_ARG_DETECT)
    /* #Violation: busprot_hal_c_REF_1 */
    Assert((boolean)(timeoutThreshold > 0U));
#endif
    /* #Violation: busprot_hal_c_REF_3 */
    pBusprotModule = (BUSPROT_MODULE *)((uint32)busprotOffAddr + BUSPROT_BASE_ADDRESS);

    DISABLE_ALL_INTERRUPTS();
    /* Clear SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* Busprot timeout disable */
    pBusprotModule->TMOUTCTRL.U = BUSPROT_TIMEOUT_DISABLE;
    /* Set timeout threshold */
    pBusprotModule->TMOUTHOLD.U = timeoutThreshold;
    /* Busprot timeout enable */
    pBusprotModule->TMOUTCTRL.U = BUSPROT_TIMEOUT_ENABLE;
    /* Set SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Busprot_Register_ReadBack_Check(ret, (uint32)BUSPROT_TIMEOUT_ENABLE, (uint32)pBusprotModule->TMOUTCTRL.U);
    ret = Busprot_Register_ReadBack_Check(ret, (uint32)timeoutThreshold, (uint32)pBusprotModule->TMOUTHOLD.U);
    return ret;
}

/* #Violation: busprot_hal_c_REF_5 */
boolean Busprot_Hal_DisableTimeoutProt(Busprot_OffsetAddress busprotOffAddr)
{
    BUSPROT_MODULE *pBusprotModule;
    boolean ret;
    ret = TRUE;

    /* #Violation: busprot_hal_c_REF_3 */
    pBusprotModule = (BUSPROT_MODULE *)((uint32)busprotOffAddr + BUSPROT_BASE_ADDRESS);

    DISABLE_ALL_INTERRUPTS();
    /* Clear SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_ClearSafetyEndinit();

    /* Busprot timeout disable */
    pBusprotModule->TMOUTCTRL.U = BUSPROT_TIMEOUT_DISABLE;
    /* Set SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Busprot_Register_ReadBack_Check(ret, (uint32)BUSPROT_TIMEOUT_DISABLE, (uint32)pBusprotModule->TMOUTCTRL.U);

    return ret;
}

/* #Violation: busprot_hal_c_REF_5 */
Busprot_Status Busprot_Hal_GetErrScene(Busprot_OffsetAddress busprotOffAddr, Busprot_ErrInfo *const pErrInfo)
{
    /* #Violation: busprot_hal_c_REF_4 */
    BUSPROT_ID regId;
    uint32 errStatus;
    uint32 busType;
    const BUSPROT_MODULE *pBusprotModule;
    Busprot_Status busprotStatusVal;

#if (STD_ON == INPUT_ARG_DETECT)
    /* Check if the pErrInfo is null pointer */
    /* #Violation: busprot_hal_c_REF_1 */
    Assert((boolean)(NULL_PTR != pErrInfo));
#endif /* INPUT_ARG_DETECT */

    busprotStatusVal = BUSPROT_STATUS_SUCCESS;
    pErrInfo->errStatus = 0U;
    pErrInfo->errAddr = 0U;
    pErrInfo->errData = 0U;
    pErrInfo->errInfo = 0U;
    /* #Violation: busprot_hal_c_REF_3 */
    pBusprotModule = (BUSPROT_MODULE *)((uint32)busprotOffAddr + BUSPROT_BASE_ADDRESS);
    regId.U = pBusprotModule->ID.U;
    busType = ((regId.U >> 4U) & 0x0fU);

    /* Get error scene information */
    switch (busType)
    {
    case (uint32)BUSPROT_AHB_BUS:
        errStatus = pBusprotModule->HEDCPTY.U;
        if ((uint32)BUSPROT_STATUS_SUCCESS != errStatus)
        {
            pErrInfo->errStatus =
                (uint32)((BUSPROT_SLAVE == regId.B.MOD_DIR) ? (errStatus & 0x3FF0U) : (errStatus & 0x03U));
            pErrInfo->errAddr = pBusprotModule->HERRADDR.U;
            pErrInfo->errData = pBusprotModule->HERRDATA.U;
            pErrInfo->errInfo = pBusprotModule->HERRINFO.U;
            busprotStatusVal = BUSPROT_STATUS_FAIL;
        }
        break;
    case (uint32)BUSPROT_APB_BUS:
        errStatus = pBusprotModule->PEDCPTY.U;
        if ((uint32)BUSPROT_STATUS_SUCCESS != errStatus)
        {
            pErrInfo->errStatus = errStatus;
            pErrInfo->errAddr = pBusprotModule->PERRADDR.U;
            pErrInfo->errData = pBusprotModule->PERRDATA.U;
            busprotStatusVal = BUSPROT_STATUS_FAIL;
        }
        break;
    case (uint32)BUSPROT_AXI_BUS:
    default:
        errStatus = pBusprotModule->AERR.U;
        if ((uint32)BUSPROT_STATUS_SUCCESS != errStatus)
        {
            pErrInfo->errStatus =
                (uint32)((BUSPROT_SLAVE == regId.B.MOD_DIR) ? (errStatus & 0x1F0U) : (errStatus & 0x07U));
            busprotStatusVal = BUSPROT_STATUS_FAIL;
        }
        break;
    }

    return busprotStatusVal;
}

/* #Violation: busprot_hal_c_REF_5 */
boolean Busprot_Hal_ClearErrStatus(Busprot_OffsetAddress busprotOffAddr)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: busprot_hal_c_REF_4 */
    BUSPROT_ID regId;
    uint32 errStatus;
    uint32 busType;
    BUSPROT_MODULE *pBusprotModule;

    /* #Violation: busprot_hal_c_REF_3 */
    pBusprotModule = (BUSPROT_MODULE *)((uint32)busprotOffAddr + BUSPROT_BASE_ADDRESS);
    regId.U = pBusprotModule->ID.U;
    busType = ((regId.U >> 4U) & 0x0fU);

    /* Get error scene information */
    switch (busType)
    {
    case (uint32)BUSPROT_AHB_BUS:
        errStatus = pBusprotModule->HEDCPTY.U;
        if ((uint32)BUSPROT_STATUS_SUCCESS != errStatus)
        {
            DISABLE_ALL_INTERRUPTS();
            ret &= Safewdt_Hal_ClearSafetyEndinit();
            
            /* Clear Busprot error status */
            pBusprotModule->HERRCLR.U = (uint32)BUSPROT_ERR_CLR;
            /* Set SAFETY ENDINIT protection */
            ret &= Safewdt_Hal_SetSafetyEndinit();
            
            ENABLE_ALL_INTERRUPTS();
        }
        break;
    case (uint32)BUSPROT_APB_BUS:
        errStatus = pBusprotModule->PEDCPTY.U;
        if ((uint32)BUSPROT_STATUS_SUCCESS != errStatus)
        {
            DISABLE_ALL_INTERRUPTS();
            /* Clear SAFETY ENDINIT protection */
            ret &= Safewdt_Hal_ClearSafetyEndinit();
            /* Clear Busprot error status */
            pBusprotModule->PERRCLR.U = (uint32)BUSPROT_ERR_CLR;
            /* Set SAFETY ENDINIT protection */
            ret &= Safewdt_Hal_SetSafetyEndinit();
            
            ENABLE_ALL_INTERRUPTS();
        }
        break;
    case (uint32)BUSPROT_AXI_BUS:
    default:
        errStatus = pBusprotModule->AERR.U;
        if ((uint32)BUSPROT_STATUS_SUCCESS != errStatus)
        {
            DISABLE_ALL_INTERRUPTS();
            /* Clear SAFETY ENDINIT protection */
            ret &= Safewdt_Hal_ClearSafetyEndinit();
            /* Clear Busprot error status */
            pBusprotModule->AERRCLR.U = (uint32)BUSPROT_ERR_CLR;
            /* Set SAFETY ENDINIT protection */
            ret &= Safewdt_Hal_SetSafetyEndinit();
            ENABLE_ALL_INTERRUPTS();
        }
        break;
    }

    return ret;
}

/* #Violation: busprot_hal_c_REF_5 */
boolean Busprot_Hal_SetAlarm(Busprot_OffsetAddress busprotOffAddr, Busprot_Alarm_Type alarmType,
                          Busprot_Alarm_Mask maskType)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: busprot_hal_c_REF_4 */
    BUSPROT_MSK regMsk;
    BUSPROT_MODULE *pBusprotModule;

    /* #Violation: busprot_hal_c_REF_3 */
    pBusprotModule = (BUSPROT_MODULE *)((uint32)busprotOffAddr + BUSPROT_BASE_ADDRESS);
    regMsk.U = pBusprotModule->MSK.U;
    regMsk.U &= ~(uint32)alarmType;
    if (BUSPROT_ALARM_MASK == maskType)
    {
        regMsk.U |= ((uint32)alarmType & BUSPROT_MSK_MASK);
    }
    DISABLE_ALL_INTERRUPTS();
    /* Clear SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* Set alarm enable */
    pBusprotModule->MSK.U = regMsk.U;
    /* Set SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    ret = Busprot_Register_ReadBack_Check(ret, (uint32)regMsk.U, (uint32)pBusprotModule->MSK.U);

    return ret;
}

/* #Violation: busprot_hal_c_REF_5 */
uint32 Busprot_Hal_GetAlarmStatus(Busprot_OffsetAddress busprotOffAddr)
{
    const BUSPROT_MODULE *pBusprotModule;

    /* #Violation: busprot_hal_c_REF_3 */
    pBusprotModule = (BUSPROT_MODULE *)((uint32)busprotOffAddr + BUSPROT_BASE_ADDRESS);
    return (pBusprotModule->ALMSTS.U & BUSPROT_ALMSTS_MASK);
}

/* #Violation: busprot_hal_c_REF_5 */
boolean Busprot_Hal_ClearAlarmStatus(Busprot_OffsetAddress busprotOffAddr, uint32 clearValue)
{
    BUSPROT_MODULE *pBusprotModule;
    boolean ret;
    ret = TRUE;

    /* #Violation: busprot_hal_c_REF_3 */
    pBusprotModule = (BUSPROT_MODULE *)((uint32)busprotOffAddr + BUSPROT_BASE_ADDRESS);
    DISABLE_ALL_INTERRUPTS();
    /* Clear SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* Clear alarm */
    pBusprotModule->ALMCLR.U = clearValue & BUSPROT_ALMCLR_MASK;
    /* Set SAFETY ENDINIT protection */
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();
    return ret;
}
/* #Violation: busprot_hal_c_REF_6 */
#define BUSPROT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: busprot_hal_c_REF_7 */
#include "Busprot_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gipc_hal.c
 * Author:      01200
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of GIPC module.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#gipc_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification: Reserved API for user access.
*
*#gipc_hal_c_REF_2:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*   
*#gipc_hal_c_REF_3:MISRAC2012-Dir-4.9; 
* Justification: Function like macros are used to reduce code complexity.
*
*#gipc_hal_c_REF_4:MISRAC2012-Rule-10.5;
* Justification: Limitation of Coretex-R52+ Core; Boolean can only be representes as unit8.
*
*#gipc_hal_c_REF_5:MISRAC2012-Rule-20.1; 
*Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

 /**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gipc_hal.h"
#include "gipc_register.h"
#include "Platform_Types.h"
#include "multicore.h"
#include "safewdt_hal.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
#define GIPC_ALARMCLR_REG_VAL_MAX    (0xFFFU)
/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/

#define GIPC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gipc_hal_c_REF_5 */
#include "Gipc_MemMap.h"

/* #Violation: gipc_hal_c_REF_1 */
void Gipc_Hal_SendNotification(GIPC_MODULE *const pGipc, MultiCoreID targetCoreID)
{
    uint32 ppictrlVal;
    MultiCoreID currentCoreID;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the GIPC base address is out of range */
    /* #Violation: gipc_hal_c_REF_2 */
    /* #Violation: gipc_hal_c_REF_3 */
    Assert((boolean)(CHECK_GIPC_BASE(pGipc)));
#endif /* INPUT_ARG_DETECT */

    /* Get current coreID */
    currentCoreID = Multicore_GetCoreID();

#if(INPUT_ARG_DETECT == STD_ON)
    /* Target coreID cannot equal to current coreID */
    /* #Violation: gipc_hal_c_REF_4 */
    Assert((boolean)(currentCoreID != targetCoreID));
#endif /* INPUT_ARG_DETECT */

    /* Send notification interrupt
     * For core0: core1 1-0bit, core2 3-2bit, core3 5-4bit
     * For core1: core0 1-0bit, core2 3-2bit, core3 5-4bit
     * For core2: core0 1-0bit, core1 3-2bit, core3 5-4bit
     * For core3: core0 1-0bit, core1 3-2bit, core2 5-4bit */
    /* SDK_GIPC_Deviation_Rule10_6 */
    if(targetCoreID > currentCoreID)
    {
        ppictrlVal = 0x3UL << (((uint32)targetCoreID - 1U) << 1U);
    }
    else
    {
        ppictrlVal = 0x3UL << ((uint32)targetCoreID << 1U);
    }

    pGipc->PPICTRL[currentCoreID].U = ppictrlVal;
}

/* #Violation: gipc_hal_c_REF_1 */
void Gipc_Hal_ClearInterruptFlag(GIPC_MODULE *const pGipc, MultiCoreID sourceCoreID)
{
    MultiCoreID currentCoreID;

    /* Get current coreID */
    currentCoreID = Multicore_GetCoreID();
    
#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the GIPC base address is out of range */
    /* #Violation: gipc_hal_c_REF_2 */
    /* #Violation: gipc_hal_c_REF_3 */
    Assert((boolean)(CHECK_GIPC_BASE(pGipc)));
    /* Source coreID cannot equal to current coreID */
    /* #Violation: gipc_hal_c_REF_4 */
    Assert((boolean)(currentCoreID != sourceCoreID));
#endif /* INPUT_ARG_DETECT */

    /* Clear interrupt flag
     * For core0: core1 0bit, core2 1bit, core3 2bit
     * For core1: core0 0bit, core2 1bit, core3 2bit
     * For core2: core0 0bit, core1 1bit, core3 2bit
     * For core3: core0 0bit, core1 1bit, core2 2bit */
    /* SDK_GIPC_Deviation_Rule10_6 */
    if(sourceCoreID > currentCoreID)
    {
        pGipc->PPISTS[currentCoreID].U = 0x1UL << ((uint32)sourceCoreID - 1U);

    }
    else
    {
        pGipc->PPISTS[currentCoreID].U = 0x1UL << (uint32)sourceCoreID;
    }
}

/* #Violation: gipc_hal_c_REF_1 */
uint32 Gipc_Hal_GetAlarmStatus(const GIPC_MODULE *const pGipc, uint32 alarm)
{
    uint32 flag;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the GIPC base address is out of range */
    /* #Violation: gipc_hal_c_REF_2 */
    /* #Violation: gipc_hal_c_REF_3 */
    Assert((boolean)(CHECK_GIPC_BASE(pGipc)));
    /* Alarm should be within the prescribed range */
    /* #Violation: gipc_hal_c_REF_4 */
    Assert((boolean)(0U == (alarm & (~GIPC_ALL_ALARM_MASK))));
#endif /* INPUT_ARG_DETECT */

    /* Get alarm status */
    flag = pGipc->ALARM.U & (uint32)alarm;
    return flag;
}

/* #Violation: gipc_hal_c_REF_1 */
boolean Gipc_Hal_ClearAlarmStatus(GIPC_MODULE *const pGipc, uint32 alarmType)
{
    boolean ret;

#if(INPUT_ARG_DETECT == STD_ON)
    /* Check if the GIPC base address is out of range */
    /* #Violation: gipc_hal_c_REF_2 */
    /* #Violation: gipc_hal_c_REF_3 */
    Assert((boolean)(CHECK_GIPC_BASE(pGipc)));
    /* Alarm type should be within the prescribed range */
    /* #Violation: gipc_hal_c_REF_4 */
    Assert((boolean)(alarmType <= GIPC_ALARMCLR_REG_VAL_MAX));
#endif /* INPUT_ARG_DETECT */
    ret = TRUE;

    DISABLE_ALL_INTERRUPTS();
    ret &= Safewdt_Hal_ClearSafetyEndinit();
    /* Write to clear */
    pGipc->ALARMCLR.U = (uint32)alarmType;
    ret &= Safewdt_Hal_SetSafetyEndinit();
    ENABLE_ALL_INTERRUPTS();

    return ret;
}

#define GIPC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gipc_hal_c_REF_5 */
#include "Gipc_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

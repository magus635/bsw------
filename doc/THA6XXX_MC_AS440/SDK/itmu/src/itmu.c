/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: itmu.c
 * Author:   00930
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: ITMU hardware abstraction layer source file.
 *              This file contains implementations for ITMU hardware abstraction layer.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #itmu_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #itmu_c_REF_2:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*
* #itmu_c_REF_3:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce register access complexity.
*
* #itmu_c_REF_4:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "stm_hal.h"
#include "tha6_cfg.h"
#include "itmu.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

#define ITMU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: itmu_c_REF_4 */
#include "Itmu_MemMap.h"

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
/* RAM initialize control mask */
#if defined(THA6_THA6104)
#define ITMU_RAMINICTRL0_MASK        (0x00CFFFFFU)
#endif /* THA6_THA6104 */

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
#define ITMU_RAMINICTRL0_MASK        (0x03FFFFFFU)
#if defined(THA6_THA6412)
#define ITMU_RAMINICTRL1_MASK        (0xFFFFU) /* THA6412 Only */
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 Ver. C&D || THA6_THA6412 */

/* RAM initialize status mask */
#if defined(THA6_THA6104)
#define ITMU_RAMINISTS0_MASK        (0x00455555U)
#endif /* THA6_THA6104 */

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
#define ITMU_RAMINISTS0_MASK        (0x01555555U)
#if defined(THA6_THA6412)
#define ITMU_RAMINISTS1_MASK        (0x5555U) /* THA6412 Only */
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 Ver. C&D || THA6_THA6412 */
/* RAM initialize time */
#define ITMU_RAMINI_TIMOUT (0xFFFFU)

#define ITMU_REG_CHECK
#if defined(ITMU_REG_CHECK)
LOCAL_FORCEINLINE boolean Itmu_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Itmu_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif


/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/



boolean Itmu_ClearModuleRam(uint32 index, uint32 clearBits)
{
    boolean ret = TRUE;
    Itmu_Status status;
    uint64 endTime;
    uint64 curTime;
    uint32 ramIniStatus;
    uint32 raministsRegAddr;
    uint32 raminictrlRegAddr;
    uint32 raminictrlMask;

#if(INPUT_ARG_DETECT == STD_ON)
     /* Check if the index is in the normal range */
    /* #Violation: itmu_c_REF_2_2 */
    Assert((boolean)(index <= 1U));
#endif /* INPUT_ARG_DETECT */

    /* Get alarm status */
    /* #Violation: itmu_c_REF_3 */
    /* #Violation: itmu_c_REF_3 */
    raministsRegAddr = (uint32)&ITMUINIT->RAMINISTS;
    /* #Violation: itmu_c_REF_3 */
    /* #Violation: itmu_c_REF_3 */
    raminictrlRegAddr = (uint32)&ITMUINIT->RAMINICTRL;
    raminictrlMask = ITMU_RAMINICTRL0_MASK;
    ramIniStatus = clearBits & ITMU_RAMINISTS0_MASK;
    (void)index;
#if defined(THA6_THA6412)
    if (0U != index)
    {
        /* #Violation: itmu_c_REF_3 */
        /* #Violation: itmu_c_REF_3 */
        raministsRegAddr = (uint32)&ITMUINIT->RAMINISTS1;
        /* #Violation: itmu_c_REF_3 */
        /* #Violation: itmu_c_REF_3 */
        raminictrlRegAddr = (uint32)&ITMUINIT->RAMINICTRL1;
        raminictrlMask = ITMU_RAMINICTRL1_MASK;
        ramIniStatus = clearBits & ITMU_RAMINISTS1_MASK;
    }
#endif /* THA6_THA6412 */

    /* Clear initialize status */
    /* #Violation: itmu_c_REF_3 */
    (*(volatile uint32 *)raministsRegAddr) = ramIniStatus;
    /* RAM initialize */
    /* #Violation: itmu_c_REF_3 */
    (*(volatile uint32 *)raminictrlRegAddr) = clearBits & raminictrlMask;

    /* Get current time as start time */
    endTime = Stm_Hal_GetValue() + ITMU_RAMINI_TIMOUT;
    status = ITMU_STATUS_ERROR;
    do
    {
        curTime = Stm_Hal_GetValue();
        /* #Violation: itmu_c_REF_3 */
        if (((*(volatile uint32 *)raministsRegAddr) & ramIniStatus) == ramIniStatus)
        {
            /*RAM initialization is finished */
            status = ITMU_STATUS_OK;
        }
    } while ((curTime < endTime) && (ITMU_STATUS_ERROR == status));

    if(ITMU_STATUS_OK != status)
    {
        ret = FALSE;
    }

    return ret;
}

/* #Violation: itmu_c_REF_1 */
boolean Itmu_InitRamOnSysReset(Itmu_RamIniOnSysReset ramIniOnSysReset)
{
    boolean ret = TRUE;
    /* #Violation: itmu_c_REF_3 */
    ITMUINIT->RAMINI = (uint32)ramIniOnSysReset;
    /* #Violation: itmu_c_REF_3 */
    ret = Itmu_Register_ReadBack_Check(ret, (uint32)ramIniOnSysReset, ITMUINIT->RAMINI);

    return ret;
}

#define ITMU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: itmu_c_REF_4 */
#include "Itmu_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

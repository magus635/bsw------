/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  pmu_hal.c
 * Author:    00412
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all implementations of requirements of PMU module
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #pmu_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #pmu_hal_c_REF_2:MISRAC2012-Rule-2.2;
* Justification:Value used in assembly code; Platform-based design with configurable macros.
*
* #pmu_hal_c_REF_3:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
* #pmu_hal_c_REF_4:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #pmu_hal_c_REF_5:MISRAC2012-Rule-1.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #pmu_hal_c_REF_6:MISRAC2012-Dir-4.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #pmu_hal_c_REF_7:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                 Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "compilertypes.h"
#include "pmu_register.h"
#include "pmu_hal.h"

#define CORE_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pmu_hal_c_REF_7*/
#include "Core_MemMap.h"
/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/

 /**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
 /**********************************************************************************************************************
 * Function:     PMU_Hal_IsRightEvent
 * Description:  Check if event counter index is in valid range
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pNode: event counter index
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE is success, FALSE is fail
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/09/06   01107      Create
 *********************************************************************************************************************/
static boolean PMU_Hal_IsRightEvent(uint32 uCntIndex);

/**********************************************************************************************************************
 *                                            Private Function Declarations
 *********************************************************************************************************************/
static boolean PMU_Hal_IsRightEvent(uint32 uCntIndex)
{
    boolean bRet = FALSE;
    if((PMU_FOURTH_EVENT_COUNTER_MASK == (uCntIndex & PMU_FOURTH_EVENT_COUNTER_MASK)) ||
       (PMU_THIRD_EVENT_COUNTER_MASK == (uCntIndex & PMU_THIRD_EVENT_COUNTER_MASK)) ||
       (PMU_SECOND_EVENT_COUNTER_MASK == (uCntIndex & PMU_SECOND_EVENT_COUNTER_MASK)) ||
       (PMU_FIRST_EVENT_COUNTER_MASK == (uCntIndex & PMU_FIRST_EVENT_COUNTER_MASK)))
    {
        bRet = TRUE;
    }
    return bRet;
}

/**********************************************************************************************************************
 *                                            Private Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                             Global Function Definitions
 *********************************************************************************************************************/
/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_Initialize(uint8 bClockDiv)
{
    uint32 uPMCR;

    /* #Violation: pmu_hal_c_REF_4 */
    GET_CP(15, 0, uPMCR, 9, 12, 0);
    /*Performance Monitors Control Register:[0]:Enable PMU;[3]:Clock divider */
    if(PMU_COUNT_DIVIDER_64 == bClockDiv)
    {
        /* #Violation: pmu_hal_c_REF_2 */
        uPMCR |= PMCR_ENABLE_MASK | PMCR_CLK_DIV_MASK | PMCR_LONG_COUNTER_EN_MASK;
    }
    else
    {
        /* #Violation: pmu_hal_c_REF_2 */
        uPMCR |= PMCR_ENABLE_MASK | PMCR_LONG_COUNTER_EN_MASK;
    }
    /* #Violation: pmu_hal_c_REF_4 */
    SET_CP(15, 0, uPMCR, 9, 12, 0);
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_Deinitialize(void)
{
    uint32 uPMCR;

    /*Performance Monitors Control Register:[0]:Disable PMU*/
    /* #Violation: pmu_hal_c_REF_4 */
    GET_CP(15, 0, uPMCR, 9, 12, 0);
    /* #Violation: pmu_hal_c_REF_2 */
    uPMCR &= ~(uint32)PMCR_ENABLE_MASK;
    /* #Violation: pmu_hal_c_REF_4 */
    SET_CP(15, 0, uPMCR, 9, 12, 0);
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_ResetCycCnt(void)
{
    uint32 uPMCR;

    /*Performance Monitors Control Register:[2]:Cycle counter reset*/
    /* #Violation: pmu_hal_c_REF_4 */
    GET_CP(15, 0, uPMCR, 9, 12, 0);
    /* #Violation: pmu_hal_c_REF_2 */
    uPMCR |= PMCR_CLK_COUN_RST_MASK;
    /* #Violation: pmu_hal_c_REF_4 */
    SET_CP(15, 0, uPMCR, 9, 12, 0);
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_EnCycCnt(void)
{
    uint32 uPMCNTENSET;

    /*PMCNTENSET Register:[31]:Enables the cycle counter register */
    /* #Violation: pmu_hal_c_REF_4 */
    GET_CP(15, 0, uPMCNTENSET, 9, 12, 1);
    /* #Violation: pmu_hal_c_REF_2 */
    uPMCNTENSET |= PMCNTENSET_C_MASK;
    /* #Violation: pmu_hal_c_REF_4 */
    SET_CP(15, 0, uPMCNTENSET, 9, 12, 1);
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_DisCycCnt(void)
{
    uint32 uPMCNTENCLR;

    /*PMCNTENCLR register:[31]:Disables the cycle counter register */
    /* #Violation: pmu_hal_c_REF_4 */
    GET_CP(15, 0, uPMCNTENCLR, 9, 12, 2);
    /* #Violation: pmu_hal_c_REF_2 */
    uPMCNTENCLR |= PMCNTENCLR_C_MASK;
    /* #Violation: pmu_hal_c_REF_4 */
    SET_CP(15, 0, uPMCNTENCLR, 9, 12, 2);
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
uint64 PMU_Hal_GetCycCntVal(void)
{
    uint64 uPMCCNTR;
    /*PMCCNTR register:[31:0]: Get the value of Cycle Counter*/
    /* #Violation: pmu_hal_c_REF_4 */
    GET_CP64(15, 0, (uPMCCNTR), 9);
    return uPMCCNTR;
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_ResetAllEvtCnt(void)
{
    uint32 uPMCR;

    /*PMCR register:[1]: Event counter reset*/
    /* #Violation: pmu_hal_c_REF_4 */
    GET_CP(15, 0, uPMCR, 9, 12, 0);
    /* #Violation: pmu_hal_c_REF_2 */
    uPMCR |= PMCR_EVT_COUN_RST_MASK;
    /* #Violation: pmu_hal_c_REF_4 */
    SET_CP(15, 0, uPMCR, 9, 12, 0);
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_EnEvtCnt(uint32 uMask)
{
    uint32 uPMCNTENSET;
    if(TRUE == PMU_Hal_IsRightEvent(uMask))
    {
        /*PMCNTENSET register:[30:0]: Enable event counter */
        /* #Violation: pmu_hal_c_REF_4 */
        GET_CP(15, 0, uPMCNTENSET, 9, 12, 1);
        /* #Violation: pmu_hal_c_REF_2 */
        uPMCNTENSET |= (uint32)uMask;
        /* #Violation: pmu_hal_c_REF_4 */
        SET_CP(15, 0, uPMCNTENSET, 9, 12, 1);
    }
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_DisEvtCnt(uint32 uMask)
{
    uint32 uPMCNTENCLR;
    if(TRUE == PMU_Hal_IsRightEvent(uMask))
    {
        /*PMCNTENCLR register:[30:0]: Disable event counter */
        /* #Violation: pmu_hal_c_REF_4 */
        GET_CP(15, 0, uPMCNTENCLR, 9, 12, 2);
        /* #Violation: pmu_hal_c_REF_2 */
        uPMCNTENCLR |= (uint32)uMask;
        /* #Violation: pmu_hal_c_REF_4 */
        SET_CP(15, 0, uPMCNTENCLR, 9, 12, 2);
    }
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
uint32 PMU_Hal_GetEvtCntVal(uint32 uCntIndex)
{
    uint32 uPMEVCNTR;
    switch(uCntIndex)
    {
        case PMU_FIRST_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVCNTR, 14, 8, 0);
            break;
        }
        case PMU_SECOND_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVCNTR, 14, 8, 1);
            break;
        }
        case PMU_THIRD_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVCNTR, 14, 8, 2);
            break;
        }
        case PMU_FOURTH_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVCNTR, 14, 8, 3);
            break;
        }

        default:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVCNTR, 14, 8, 0);
            break;
        }
    }

    return uPMEVCNTR;
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_SetEvtCntVal(uint32 uCntIndex, uint32 uVal)
{
    uint32 uPMEVCNTR;

    /* #Violation: pmu_hal_c_REF_2 */
    uPMEVCNTR = uVal;

    switch(uCntIndex)
    {
        case PMU_FIRST_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVCNTR, 14, 8, 0);
            break;
        }
        case PMU_SECOND_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVCNTR, 14, 8, 1);
            break;
        }
        case PMU_THIRD_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVCNTR, 14, 8, 2);
            break;
        }
        case PMU_FOURTH_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVCNTR, 14, 8, 3);
            break;
        }

        default:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVCNTR, 14, 8, 0);
            break;
        }
    }
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_SetEvtCntType(uint32 uCntIndex, PMU_EventCounterID uCntType)
{
    uint32 uPMEVTYPER;

    switch(uCntIndex)
    {
        case PMU_FIRST_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVTYPER, 14, 12, 0);
            /* #Violation: pmu_hal_c_REF_2 */
            uPMEVTYPER = (uint32)((uint32)uCntType & PMEVTYPER_MASK);
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVTYPER, 14, 12, 0);
            break;
        }
        case PMU_SECOND_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVTYPER, 14, 12, 1);
            /* #Violation: pmu_hal_c_REF_2 */
            uPMEVTYPER = (uint32)((uint32)uCntType & PMEVTYPER_MASK);
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVTYPER, 14, 12, 1);
            break;
        }
        case PMU_THIRD_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVTYPER, 14, 12, 2);
            /* #Violation: pmu_hal_c_REF_2 */
            uPMEVTYPER = (uint32)((uint32)uCntType & PMEVTYPER_MASK);
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVTYPER, 14, 12, 2);
            break;
        }
        case PMU_FOURTH_EVENT_COUNTER_MASK:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVTYPER, 14, 12, 3);
            /* #Violation: pmu_hal_c_REF_2 */
            uPMEVTYPER = (uint32)((uint32)uCntType & PMEVTYPER_MASK);
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVTYPER, 14, 12, 3);
            break;
        }

        default:
        {
            /* #Violation: pmu_hal_c_REF_4 */
            GET_CP(15, 0, uPMEVTYPER, 14, 12, 0);
            /* #Violation: pmu_hal_c_REF_2 */
            uPMEVTYPER = (uint32)((uint32)uCntType & PMEVTYPER_MASK);
            /* #Violation: pmu_hal_c_REF_4 */
            SET_CP(15, 0, uPMEVTYPER, 14, 12, 0);
            break;
        }
    }
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
uint32 PMU_Hal_GetEvtCntOvsStatus(uint32 uCntIndex)
{
    uint32 uPMOVSSET;

    if(TRUE == PMU_Hal_IsRightEvent(uCntIndex))
    {
        /*PMOVSR register, [31:0] Get event and cycle counter overflow status*/
        /* #Violation: pmu_hal_c_REF_4 */
        GET_CP(15, 0, uPMOVSSET, 9, 14, 3);
        if(uCntIndex > PMU_EVENT_COUNTER_NONE)
        {
            uPMOVSSET &= (uint32)(uCntIndex);
        }
    }
    else
    {
        uPMOVSSET = 0U;
    }
    return uPMOVSSET;
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_ClearEvCnOvs(uint32 uMask)
{
    uint32 uPMOVSR;

    if(TRUE == PMU_Hal_IsRightEvent(uMask))
    {
        /* #Violation: pmu_hal_c_REF_4 */
        GET_CP(15, 0, uPMOVSR, 9, 12, 3);
        /*PMOVSR register, [31:0] Clear event and cycle counter overflow */
        /* #Violation: pmu_hal_c_REF_2 */
        uPMOVSR = (uint32)uMask;
        /* #Violation: pmu_hal_c_REF_4 */
        SET_CP(15, 0, uPMOVSR, 9, 12, 3);
    }
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_EnEvtOvsIrq(uint32 uMask)
{
    uint32 uPMINTENSET;

    if(TRUE == PMU_Hal_IsRightEvent(uMask))
    {
        /*PMINTENSET Register:[31:0]: Enables interrupt requests on overflows for event and cycle counter */
        /* #Violation: pmu_hal_c_REF_4 */
        GET_CP(15, 0, uPMINTENSET, 9, 14, 1);

        /*PMINTENSET Register:[31:0]: Enables interrupt requests on overflows for event and cycle counter */
        /* #Violation: pmu_hal_c_REF_2 */
        uPMINTENSET |= (uint32)(uMask);
        /* #Violation: pmu_hal_c_REF_4 */
        SET_CP(15, 0, uPMINTENSET, 9, 14, 1);
    }
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_DisEvtOvsIrq(uint32 uMask)
{
    uint32 uPMINTENCLR;

    if(TRUE == PMU_Hal_IsRightEvent(uMask))
    {
        /* #Violation: pmu_hal_c_REF_4 */
        GET_CP(15, 0, uPMINTENCLR, 9, 14, 2);
        /*PMINTENCLR Register:[31:0]:Clear interrupt requests on overflows for event and cycle counter */
        /* #Violation: pmu_hal_c_REF_2 */
        uPMINTENCLR |= (uint32)(uMask);
        /* #Violation: pmu_hal_c_REF_4 */
        SET_CP(15, 0, uPMINTENCLR, 9, 14, 2);
    }
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_EvtIncrement(uint32 uCntIndex)
{
    uint32 uPMSWINC;

    if(TRUE == PMU_Hal_IsRightEvent(uCntIndex))
    {
        /*PMSWINC Register:[30:0]:Event counter software increment bit*/
        /* #Violation: pmu_hal_c_REF_2 */
        uPMSWINC = (uint32)uCntIndex;
        /* #Violation: pmu_hal_c_REF_4 */
        SET_CP(15, 0, uPMSWINC, 9, 12, 4);
    }
}

/* #Violation: pmu_hal_c_REF_1 */
/* #Violation: pmu_hal_c_REF_3 */
void PMU_Hal_EnableUserMode(uint32 uMode)
{
    uint32 uPMUSERENR;

    /*PMUSERENR Register:Enables or disables User mode access to the Performance Monitors*/
    /* #Violation: pmu_hal_c_REF_2 */
    uPMUSERENR = uMode & PMUSERENR_ALL_MASK;
    /* #Violation: pmu_hal_c_REF_4 */
    SET_CP(15, 0, uPMUSERENR, 9, 14, 0);
}
#define CORE_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: pmu_hal_c_REF_7*/
#include "Core_MemMap.h"
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

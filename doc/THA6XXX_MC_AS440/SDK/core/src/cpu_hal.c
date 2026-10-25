/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    cpu_hal.c
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all functions of CPU module.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #cpu_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #cpu_hal_c_REF_2:MISRAC2012-Rule-2.2;
* Justification:Value used in assembly code; Platform-based design with configurable macros.
*
* #cpu_hal_c_REF_3:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
* #cpu_hal_c_REF_4:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #cpu_hal_c_REF_5:MISRAC2012-Rule-1.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #cpu_hal_c_REF_6:MISRAC2012-Dir-4.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #cpu_hal_c_REF_7:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "compilertypes.h"
#include "cpu_hal.h"
#include "cpu_register.h"
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

#define CORE_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpu_hal_c_REF_7*/
#include "Core_MemMap.h"

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_EnableDSA(void)
{
    uint64 uCPUACTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*CPUACTLR register:[33:32]: Enable data side speculative access */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP64(15, 0, (uCPUACTLR), 15);
    uCPUACTLR &= ~(uint64)CPUACTLR_DSPECDIS_MASK;
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP64(15, 0, (uCPUACTLR), 15);

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_DisableDSA(void)
{
    uint64 uCPUACTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*CPUACTLR register:[33:32]: Disable data side speculative access */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP64(15, 0, (uCPUACTLR), 15);
    uCPUACTLR |= (uint64)CPUACTLR_DSPECDIS_MASK;
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP64(15, 0, (uCPUACTLR), 15);

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_EnableISA(void)
{
    uint64 uCPUACTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*CPUACTLR register:[33:32]: Enable instruction side speculative access */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP64(15, 0, (uCPUACTLR), 15);
    uCPUACTLR &= ~(uint64)CPUACTLR_ISPECDIS_MASK;
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP64(15, 0, (uCPUACTLR), 15);

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_DisableISA(void)
{
    uint64 uCPUACTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*CPUACTLR register:[33:32]: Disable instruction side speculative access */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP64(15, 0, (uCPUACTLR), 15);
    uCPUACTLR |= (uint64)CPUACTLR_ISPECDIS_MASK;
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP64(15, 0, (uCPUACTLR), 15);

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_EnableEL2DBP(void)
{
    uint32 uIMP_BPCTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*IMP_BPCTLR register:[2]:Enable dynamic branch predictor when running at EL2 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP(15, 1, (uIMP_BPCTLR), 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_2 */
    uIMP_BPCTLR &= ~(uint32)IMP_BPCTLR_DBPEL2DIS_MASK;
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP(15, 1, (uIMP_BPCTLR), 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_DisableEL2DBP(void)
{
    uint32 uIMP_BPCTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*IMP_BPCTLR register:[2]:Disable dynamic branch predictor when running at EL2 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_2 */
    uIMP_BPCTLR |= (uint32)IMP_BPCTLR_DBPEL2DIS_MASK;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_EnableEL1DBP(void)
{
    uint32 uIMP_BPCTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*IMP_BPCTLR register:[1]:Enable dynamic branch predictor when running at EL1 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_2 */
    uIMP_BPCTLR &= ~(uint32)IMP_BPCTLR_DBPEL1DIS_MASK;
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_DisableEL1DBP(void)
{
    uint32 uIMP_BPCTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*IMP_BPCTLR register:[1]:Disable dynamic branch predictor when running at EL1 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_2 */
    uIMP_BPCTLR |= (uint32)IMP_BPCTLR_DBPEL1DIS_MASK;
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_EnableEL0DBP(void)
{
    uint32 uIMP_BPCTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*IMP_BPCTLR register:[0]:Enable dynamic branch predictor when running at EL0 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_2 */
    uIMP_BPCTLR &= ~(uint32)IMP_BPCTLR_DBPEL0DIS_MASK;
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_DisableEL0DBP(void)
{
    uint32 uIMP_BPCTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*IMP_BPCTLR register:[0]:Disable dynamic branch predictor when running at EL0 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_2 */
    uIMP_BPCTLR |= (uint32)IMP_BPCTLR_DBPEL0DIS_MASK;
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP(15, 1, uIMP_BPCTLR, 9, 1, 1);
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_SetL1DPF(CPU_DataPrefetchControl ctl)
{
    uint64 uCPUACTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*CPUACTLR register:[11]: set L1 Data prefetch control. */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP64(15, 0, (uCPUACTLR), 15);
    uCPUACTLR &= ~(uint64)CPUACTLR_L1DPFCTL_MASK;
    uCPUACTLR |= (((uint64)ctl) << CPUACTLR_L1DPFCTL_POS);
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP64(15, 0, (uCPUACTLR), 15);

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_EnableL1IPF(void)
{
    uint64 uCPUACTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*CPUACTLR register:[11]: Enable L1 instruction prefetch */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP64(15, 0, (uCPUACTLR), 15);
    uCPUACTLR |= (uint64)CPUACTLR_L1IPFCTL_MASK;
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP64(15, 0, (uCPUACTLR), 15);

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

/* #Violation: cpu_hal_c_REF_1 */
/* #Violation: cpu_hal_c_REF_3 */
void CPU_Hal_DisableL1IPF(void)
{
    uint64 uCPUACTLR;

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
    /*CPUACTLR register:[11]: Disable L1 instruction prefetch */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    GET_CP64(15, 0, (uCPUACTLR), 15);
    uCPUACTLR &= ~(uint64)CPUACTLR_L1IPFCTL_MASK;
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_2 */
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_6 */
    SET_CP64(15, 0, (uCPUACTLR), 15);

    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    DSB();
    /* #Violation: cpu_hal_c_REF_4 */
    /* #Violation: cpu_hal_c_REF_5 */
    /* #Violation: cpu_hal_c_REF_6 */
    ISB();
}

#define CORE_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpu_hal_c_REF_7*/
#include "Core_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

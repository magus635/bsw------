/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  mpu_hal.c
 * Author:    00412
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all implementations of requirements of MPU module
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #mpu_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #mpu_hal_c_REF_2:MISRAC2012-Rule-2.2;
* Justification:Value used in assembly code; Platform-based design with configurable macros.
*
* #mpu_hal_c_REF_3:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #mpu_hal_c_REF_4:MISRAC2012-Rule-1.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #mpu_hal_c_REF_5:MISRAC2012-Dir-4.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #mpu_hal_c_REF_6:MISRAC2012-Rule-10.5;
* Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*
* #mpu_hal_c_REF_7:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity.
* 
* #mpu_hal_c_REF_8:DCL15-C;
* Justification:Reserved API for user access.
*
* #mpu_hal_c_REF_9:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                 Includes
 *********************************************************************************************************************/

#include "common_hal.h"
#include "compilertypes.h"
#if(STD_ON == INPUT_ARG_DETECT)
#include "dev.h"
#endif
#include "mpu_hal.h"
#include "mpu_register.h"
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
/* #Violation: mpu_hal_c_REF_9*/
#include "Core_MemMap.h"

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_EnableEL1(void)
{
    uint32 uSCTLR;

    /*SCTLR register:[0]:Enable EL1 controlled MPU */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 0, uSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_2 */
    uSCTLR |= (uint32)SCTLR_M_MPU_MASK;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 0, uSCTLR, 1, 0, 0);

    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_DisableEL1(void)
{
    uint32 uSCTLR;

    /*Wait any data transfers to complete before disabling MPU*/
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DMB();
    /*SCTLR register:[0]:Disable EL1 controlled MPU */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 0, uSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_2 */
    uSCTLR &= ~(uint32)SCTLR_M_MPU_MASK;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 0, uSCTLR, 1, 0, 0);

    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_EnableEL2(void)
{
    uint32 uHSCTLR;

    /*HSCTLR register:[0]: Enable EL2 controlled MPU */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 4, uHSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_2 */
    uHSCTLR |= (uint32)HSCTLR_M_MPU_MASK;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHSCTLR, 1, 0, 0);

    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_DisableEL2(void)
{
    uint32 uHSCTLR;

    /*Wait any data transfers to complete before disabling MPU*/
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DMB();

    /*HSCTLR register:[0]: Disable EL2 controlled MPU */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 4, uHSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_2 */
    uHSCTLR &= ~(uint32)HSCTLR_M_MPU_MASK;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHSCTLR, 1, 0, 0);

    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_EnableEL2Re(uint32 uRgNum)
{
    uint32 uHPRENR;
    uint32 uHMPUIR;


    /*Hyp MPU Type Register:[7:0]:Indicates the number of EL2 controlled MPU regions */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 4, uHMPUIR, 0, 0, 4);
    /* #Violation: mpu_hal_c_REF_2 */
    uHMPUIR &= 0x000000FFU;

#if(STD_ON == INPUT_ARG_DETECT)
    /*Check the validity of the region number.*/
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(uRgNum < uHMPUIR));
#endif

    /*HPRENR Register:[19:0]:Enables the respective EL2-controlled MPU N region */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 4, uHPRENR, 6, 1, 1);
    /* #Violation: mpu_hal_c_REF_2 */
    uHPRENR |= (uint32)(1UL << uRgNum);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHPRENR, 6, 1, 1);

    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_DisableEL2Re(uint32 uRgNum)
{
    uint32 uHPRENR;
    uint32 uHMPUIR;

    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DMB();
    /*Hyp MPU Type Register:[7:0]:Indicates the number of EL2 controlled MPU regions */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 4, uHMPUIR, 0, 0, 4);
    /* #Violation: mpu_hal_c_REF_2 */
    uHMPUIR &= 0x000000FFU;

#if(STD_ON == INPUT_ARG_DETECT)
    /*Check the validity of the region number.*/
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)((uint32)uRgNum < uHMPUIR));
#endif

    /*HPRENR Register:[19:0]:Disables the respective EL2-controlled MPU N region */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 4, uHPRENR, 6, 1, 1);
    /* #Violation: mpu_hal_c_REF_2 */
    uHPRENR &= ~(uint32)(1UL << uRgNum);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHPRENR, 6, 1, 1);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_EnableEL1Bg(void)
{
    uint32 uSCTLR;

    /*SCTLR register:[17]:Enable EL1 background region */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 0, uSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_2 */
    uSCTLR |= (uint32)SCTLR_BR_MPU_MASK;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 0, uSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_DisableEL1Bg(void)
{
    uint32 uSCTLR;

    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DMB();
    /*SCTLR register:[17]:Disable EL1 background region */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 0, uSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_2 */
    uSCTLR &= ~(uint32)SCTLR_BR_MPU_MASK;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 0, uSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_EnableEL2Bg(void)
{
    uint32 uHSCTLR;

    /*SCTLR register:[17]:Enable EL1 background region */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 4, uHSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_2 */
    uHSCTLR |= (uint32)HSCTLR_BR_MPU_MASK;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_DisableEL2Bg(void)
{
    uint32 uHSCTLR;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DMB();
    /*SCTLR register:[17]:Enable EL1 background region */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 4, uHSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_2 */
    uHSCTLR &= ~(uint32)HSCTLR_BR_MPU_MASK;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHSCTLR, 1, 0, 0);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}
/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_SetEL1Re(uint8 bRgNum, const MPU_RegionAtt * const pRegionAtt)
{
    uint32 uMPUIR;
    uint32 uPRSELR;
    uint32 uPRBAR;
    uint32 uPRLAR;
    uint32 uRegSize;

#if(STD_ON == INPUT_ARG_DETECT)
    /*Check the validity of the pointer*/
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(NULL_PTR != pRegionAtt));
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(0U == (pRegionAtt->MPU_StartAddress & (uint32)0x3F)));
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(0U == (pRegionAtt->MPU_RegionSize & (uint32)0x3F)));
#endif

    /*MPUIR Register:[15:8]:Indicates the number of EL1 controlled MPU regions */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 0, uMPUIR, 0, 0, 4);
    /* #Violation: mpu_hal_c_REF_2 */
    uMPUIR = ((uMPUIR & (uint32)0x0000FF00) >> 8U);

#if(STD_ON == INPUT_ARG_DETECT)
    /*Check the validity of the region number*/
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(bRgNum < uMPUIR));
#endif

    /*PRSELR Register:[3:0]:The number of the current region visible in PRBAR and PRLAR*/
    /* #Violation: mpu_hal_c_REF_2 */
    uPRSELR = (uint32)(bRgNum);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 0, uPRSELR, 6, 2, 1);

    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();

    uPRLAR = 0U; /* Disable Region */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 0, uPRLAR, 6, 3, 1);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();

    /*PRBAR Register:[0]:Execute-never;[2:1]:Access Permission bits;[4:3]:Shareability field*/
    uPRBAR = (uint32)(pRegionAtt->MPU_XN);
    uPRBAR |= ((uint32)pRegionAtt->MPU_AccPerm << 1U);
    uPRBAR |= ((uint32)pRegionAtt->MPU_ShareField << 3U);
    /* #Violation: mpu_hal_c_REF_2 */
    uPRBAR |= (uint32)(pRegionAtt->MPU_StartAddress);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 0, uPRBAR, 6, 3, 0);

    /*PRLAR Register:[0]:Region enable;[3:1]:Indexes a set of attributes in one of the MAIRx registers*/
    uPRLAR = (uint32)(pRegionAtt->MPU_RegionEnable);
    uPRLAR |= ((uint32)pRegionAtt->MPU_AttIndex << 1U);
    /*Limit address is postfixed with 0x3F to provide the limit address to be checked against*/
    uRegSize = pRegionAtt->MPU_RegionSize - LIMIT_ADDRESS_ALIGN_SIZE;
    /* #Violation: mpu_hal_c_REF_2 */
    uPRLAR |= (uint32)pRegionAtt->MPU_StartAddress + (uint32)uRegSize;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 0, uPRLAR, 6, 3, 1);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_SetEL2Re(uint8 bRgNum, const MPU_RegionAtt * const pRegionAtt)
{
    uint32 uHMPUIR;
    uint32 uHPRSELR;
    uint32 uHPRBAR;
    uint32 uHPRLAR;
    uint32 uRegSize;

#if(STD_ON == INPUT_ARG_DETECT)
    /*Check the validity of the pointer*/
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(NULL_PTR != pRegionAtt));
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(0U == (pRegionAtt->MPU_StartAddress & (uint32)0x3F)));
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(0U == (pRegionAtt->MPU_RegionSize & (uint32)0x3F)));
#endif

    /*Hyp MPU Type Register:[7:0]:Indicates the number of EL2 controlled MPU regions */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    GET_CP(15, 4, uHMPUIR, 0, 0, 4);
    /* #Violation: mpu_hal_c_REF_2 */
    uHMPUIR &= (uint32)0x000000FF;

#if(STD_ON == INPUT_ARG_DETECT)
    /*Check the validity of the region number.*/
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(bRgNum < uHMPUIR));
#endif

    /*HPRSELR Register:[3:0]:The number of the current region visible in HPRBAR and HPRLAR */
    /* #Violation: mpu_hal_c_REF_2 */
    uHPRSELR = bRgNum;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHPRSELR, 6, 2, 1);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();

    uHPRLAR = 0U; /* Disable Region */
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHPRLAR, 6, 3, 1);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();

    /*HPRBAR Register:[0]:Execute-never;[2:1]:Access Permission bits;[4:3]:Shareability field*/
    uHPRBAR = (uint32)(pRegionAtt->MPU_XN);
    uHPRBAR |= ((uint32)pRegionAtt->MPU_AccPerm << 1U);
    uHPRBAR |= ((uint32)pRegionAtt->MPU_ShareField << 3U);
    /* #Violation: mpu_hal_c_REF_2 */
    uHPRBAR |= ((uint32)pRegionAtt->MPU_StartAddress);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHPRBAR, 6, 3, 0);

    /*HPRLAR Register:[0]:Region enable;[3:1]:Indexes a set of attributes in one of the MAIRx registers*/
    uHPRLAR = (uint32)(pRegionAtt->MPU_RegionEnable);
    uHPRLAR |= ((uint32)pRegionAtt->MPU_AttIndex << 1U);
    /*Limit address is postfixed with 0x3F to provide the limit address to be checked against*/
    uRegSize = pRegionAtt->MPU_RegionSize - LIMIT_ADDRESS_ALIGN_SIZE;
    /* #Violation: mpu_hal_c_REF_2 */
    uHPRLAR |= (uint32)pRegionAtt->MPU_StartAddress + uRegSize;
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    SET_CP(15, 4, uHPRLAR, 6, 3, 1);
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    DSB();
    /* #Violation: mpu_hal_c_REF_3 */
    /* #Violation: mpu_hal_c_REF_4 */
    /* #Violation: mpu_hal_c_REF_5 */
    ISB();
}

/* #Violation: mpu_hal_c_REF_1 */
/* #Violation: mpu_hal_c_REF_8 */
/* #Violation: mpu_hal_c_REF_7 */
void MPU_Hal_SetMemAttri(uint8 bAttIndex, uint8 bMemAtt)
{
    uint32 uMAIR;
    uint32 uMemAtt;
    uint8 memAttShift;

#if(STD_ON == INPUT_ARG_DETECT)
    /*Check the validity of the attribute index*/
    /* #Violation: mpu_hal_c_REF_6 */
    Assert((boolean)(bAttIndex < (uint32)MAX_TOTAL_MEM_ATT_INDEX));
#endif

    uMemAtt = bMemAtt;

    if(bAttIndex < (uint32)MAX_GROUP_MEM_ATT_INDEX)
    {
        memAttShift = (bAttIndex)*8U;
        /*Set index and attribute to MAIR0*/
        /* #Violation: mpu_hal_c_REF_3 */
        /* #Violation: mpu_hal_c_REF_4 */
        /* #Violation: mpu_hal_c_REF_5 */
        GET_CP(15, 0, uMAIR, 10, 2, 0);
        uMemAtt = ((uint32)0xFFU) << memAttShift;
        uMAIR &= ~(uint32)(uMemAtt);
        /* #Violation: mpu_hal_c_REF_2 */
        uMAIR |= (((uint32)bMemAtt << (uint32)memAttShift) & (uint32)uMemAtt);
        /* #Violation: mpu_hal_c_REF_3 */
        /* #Violation: mpu_hal_c_REF_4 */
        /* #Violation: mpu_hal_c_REF_5 */
        SET_CP(15, 0, uMAIR, 10, 2, 0);
    }
    else
    {
        memAttShift = (bAttIndex - 4U)*8U;
        /*Set index and attribute to MAIR1*/
        /* #Violation: mpu_hal_c_REF_3 */
        /* #Violation: mpu_hal_c_REF_4 */
        /* #Violation: mpu_hal_c_REF_5 */
        GET_CP(15, 0, uMAIR, 10, 2, 1);
        uMemAtt = ((uint32)0xFFU) << memAttShift;
        uMAIR &= ~(uint32)(uMemAtt);
        /* #Violation: mpu_hal_c_REF_2 */
        /* #Violation: mpu_hal_c_REF_2 */
        uMAIR |= (((uint32)bMemAtt << (uint32)memAttShift) & (uint32)uMemAtt);
        /* #Violation: mpu_hal_c_REF_3 */
        /* #Violation: mpu_hal_c_REF_4 */
        /* #Violation: mpu_hal_c_REF_5 */
        SET_CP(15, 0, uMAIR, 10, 2, 1);
    }
}

#define CORE_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: mpu_hal_c_REF_9*/
#include "Core_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  cache_hal.c
 * Author:    00412
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all implementations of requirements of Cache module
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #cache_hal_c_REF_1:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access.
*
* #cache_hal_c_REF_2:MISRAC2012-Rule-2.2;
* Justification:Value used in assembly code; Platform-based design with configurable macros.
*
* #cache_hal_c_REF_3:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #cache_hal_c_REF_4:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
* #cache_hal_c_REF_5:MISRAC2012-Rule-2.3;
* Justification:The members of the type are used in configuration-generated code.
*
* #cache_hal_c_REF_6:MISRAC2012-Rule-8.7;
* Justification:The interface is called by the application layer.
*
* #cache_hal_c_REF_7:MISRAC2012-Rule-1.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #cache_hal_c_REF_8:MISRAC2012-Dir-4.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #cache_hal_c_REF_9:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

/**********************************************************************************************************************
 *                                                 Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "compilertypes.h"
#include "cache_register.h"
#include "cache_hal.h"

/**********************************************************************************************************************
 *                                              Private Macro Definitions
 *********************************************************************************************************************/
typedef enum
{
    /* clean d-cache */
    /* #Violation: cache_hal_c_REF_5 */
    DCACHE_OP_CLEAN = 0U,
    /* invalidate d-cache */
    /* Violation: cache_hal_c_REF_5 */
    DCACHE_OP_INVALIDATE = 1U,
    /* clean and invalidate d-cache */
    /* #Violation: cache_hal_c_REF_5 */
    DCACHE_OP_CLEAN_INVALIDATE = 2U,
/* #Violation: cache_hal_c_REF_5 */
/* #Violation: cache_hal_c_REF_5 */
} CACHE_OP;

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
/* #Violation: cache_hal_c_REF_9*/
#include "Core_MemMap.h"

/* #Violation: cache_hal_c_REF_4*/
/* #Violation: cache_hal_c_REF_6*/
void Cache_Hal_InvalidateD(void)
{
    uint32 uCCSIDR;
    uint32 uDCISW;
    uint32 uSetsCount;
    uint32 uWaysCount;
    uint32 uCSSELR;
    uint8 uWaysFlag = 0;
    uint8 uSetsFlag = 0;

    /* Select D-cache for CCSIDR */
    /*#Violation: cache_hal_c_REF_2 */
    uCSSELR = 0U;
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    SET_CP(15, 2, uCSSELR, 0, 0, 0);
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    DSB();
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    ISB();

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    GET_CP(15, 1, uCCSIDR, 0, 0, 0);

    uSetsCount = (((uCCSIDR)&CCSIDR_NUMSETS_MASK) >> CCSIDR_NUMSETS_POS);
    do
    {
        if (uSetsFlag != 0U)
        {
            uSetsCount = uSetsCount - 1U;
        }
        else
        {
            uSetsFlag = 1U;
        }

        uWaysCount = (((uCCSIDR)&CCSIDR_ASSOCIATIVITY_MASK) >> CCSIDR_ASSOCIATIVITY_POS);
        do
        {
            if (uWaysFlag != 0U)
            {
                uWaysCount = uWaysCount - 1U;
            }
            else
            {
                uWaysFlag = 1U;
            }
            /*#Violation: cache_hal_c_REF_2 */
            uDCISW =
                (((uSetsCount << DCISW_SET_POS) & DCISW_SET_MASK) | ((uWaysCount << DCISW_WAY_POS) & DCISW_WAY_MASK));

            /*#Violation: cache_hal_c_REF_3 */
            /*#Violation: cache_hal_c_REF_7 */
            /*#Violation: cache_hal_c_REF_8 */
            SET_CP(15, 0, uDCISW, 7, 6, 2);
            /*#Violation: cache_hal_c_REF_3 */
            /*#Violation: cache_hal_c_REF_7 */
            /*#Violation: cache_hal_c_REF_8 */
            DSB();
            /*#Violation: cache_hal_c_REF_3 */
            /*#Violation: cache_hal_c_REF_7 */
            /*#Violation: cache_hal_c_REF_8 */
            ISB();
        } while(uWaysCount != 0U);
    } while(uSetsCount != 0U);

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    DSB();
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    ISB();
}

 /* #Violation: cache_hal_c_REF_4*/
/* #Violation: cache_hal_c_REF_6*/
void Cache_Hal_InvalidateI(void)
{
    uint32 uICIALLUS;

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    DSB();
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    ISB();

    /*#Violation: cache_hal_c_REF_2 */
    uICIALLUS = 0;
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    SET_CP(15, 0, uICIALLUS, 7, 1, 0);
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    DSB();
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    ISB();
}


 /* #Violation: cache_hal_c_REF_4 */
/* #Violation: cache_hal_c_REF_6 */
void Cache_Hal_CleanInvalidateD(void)
{
    uint32 uCCSIDR;
    uint32 uDCCISW;
    uint32 uSetsCount;
    uint32 uWaysCount;
    uint32 uCSSELR;
    uint8 uWaysFlag = 0;
    uint8 uSetsFlag = 0;

    /* Select D-cache for CCSIDR */
    /*#Violation: cache_hal_c_REF_2 */
    uCSSELR = 0U;
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    SET_CP(15, 2, uCSSELR, 0, 0, 0);
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    DSB();

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    ISB();

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    GET_CP(15, 1, uCCSIDR, 0, 0, 0);

    /*CCSIDR register:[27:13]: (Number of sets in cache)*/
    uSetsCount = (((uCCSIDR)&CCSIDR_NUMSETS_MASK) >> CCSIDR_NUMSETS_POS);

    do
    {
        if (uSetsFlag != 0U)
        {
            uSetsCount = uSetsCount - 1U;
        }
        else
        {
            uSetsFlag = 1U;
        }
        uWaysCount = (((uCCSIDR)&CCSIDR_ASSOCIATIVITY_MASK) >> CCSIDR_ASSOCIATIVITY_POS);
        do
        {
            if (uWaysFlag != 0U)
            {
                uWaysCount = uWaysCount - 1U;
            }
            else
            {
                uWaysFlag = 1U;
            }
            /*#Violation: cache_hal_c_REF_2 */
            uDCCISW = (((uSetsCount << DCCISW_SET_POS) & DCCISW_SET_MASK) | ((uWaysCount << DCCISW_WAY_POS) & DCCISW_WAY_MASK));
            /*#Violation: cache_hal_c_REF_3 */
            /*#Violation: cache_hal_c_REF_7 */
            /*#Violation: cache_hal_c_REF_8 */
            SET_CP(15, 0, uDCCISW, 7, 14, 2);
            /*#Violation: cache_hal_c_REF_3 */
            /*#Violation: cache_hal_c_REF_7 */
            /*#Violation: cache_hal_c_REF_8 */
            DSB();
            /*#Violation: cache_hal_c_REF_3 */
            /*#Violation: cache_hal_c_REF_7 */
            /*#Violation: cache_hal_c_REF_8 */
            ISB();
        } while(uWaysCount != 0U);
    } while(uSetsCount != 0U);

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    DSB();
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    ISB();
}


/* #Violation: cache_hal_c_REF_1*/
/* #Violation: cache_hal_c_REF_4*/
void Cache_Hal_EnableD(void)
{
    uint32 uSCTLR;

    /*SCTLR register,[2]: Enable D-Cache*/
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    GET_CP(15, 0, uSCTLR, 1, 0, 0);

    /*Check wheter D-Cache has been enabled*/
    if(SCTLR_D_CACHE_MASK != (uSCTLR & SCTLR_D_CACHE_MASK))
    {
        Cache_Hal_InvalidateD();

        /*#Violation: cache_hal_c_REF_2 */
        uSCTLR |= (uint32)SCTLR_D_CACHE_MASK;
        /*First to invalidate all D-Cache*/
       /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        SET_CP(15, 0, uSCTLR, 1, 0, 0);

        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        DSB();
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        ISB();
    }
}

/* #Violation: cache_hal_c_REF_1*/
/* #Violation: cache_hal_c_REF_4*/
void Cache_Hal_DisableD(void)
{
    uint32 uSCTLR;

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    DSB();
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    ISB();

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    GET_CP(15, 0, uSCTLR, 1, 0, 0);

    if(SCTLR_D_CACHE_MASK == (uSCTLR & SCTLR_D_CACHE_MASK))
    {

        /*SCTLR register,[2]: Disable D-Cache*/
        /*#Violation: cache_hal_c_REF_2 */
        uSCTLR &= ~(uint32)SCTLR_D_CACHE_MASK;
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        SET_CP(15, 0, uSCTLR, 1, 0, 0);
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        DSB();
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        ISB();

        Cache_Hal_CleanInvalidateD();

        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        DSB();
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        ISB();
    }
}

/* #Violation: cache_hal_c_REF_1*/
/* #Violation: cache_hal_c_REF_4*/
void Cache_Hal_EnableI(void)
{
    uint32 uSCTLR;
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    GET_CP(15, 0, uSCTLR, 1, 0, 0);

    if(SCTLR_I_CACHE_MASK != (uSCTLR & SCTLR_I_CACHE_MASK))
    {
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        DSB();
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        ISB();

        /*SCTLR register,[12]: Enable I-Cache*/
        /*#Violation: cache_hal_c_REF_2 */
        uSCTLR |= SCTLR_I_CACHE_MASK;
        /*Invalidate I-Cache*/
        Cache_Hal_InvalidateI();

        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        SET_CP(15, 0, uSCTLR, 1, 0, 0);
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        DSB();
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        ISB();
    }
}

/* #Violation: cache_hal_c_REF_1*/
/* #Violation: cache_hal_c_REF_4*/
void Cache_Hal_DisableI(void)
{
    uint32 uSCTLR;
    uint32 uICIALLUS;

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */    
    GET_CP(15, 0, uSCTLR, 1, 0, 0);

    /*SDK_CORE_Deviation_Rule2_2:pony add for QAC*/
    if(SCTLR_I_CACHE_MASK == (uSCTLR & SCTLR_I_CACHE_MASK))
    {
        /* SCTLR register,[12]: Disable I-Cache */
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */ 
        DSB();
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */ 
        ISB();
        /*#Violation: cache_hal_c_REF_2 */
        uSCTLR &= ~(uint32)SCTLR_I_CACHE_MASK;
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */ 
        SET_CP(15, 0, uSCTLR, 1, 0, 0);

        /*#Violation: cache_hal_c_REF_2 */
        uICIALLUS = 0U;
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        SET_CP(15, 0, uICIALLUS, 7, 1, 0);

        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        DSB();
        /*#Violation: cache_hal_c_REF_3 */
        /*#Violation: cache_hal_c_REF_7 */
        /*#Violation: cache_hal_c_REF_8 */
        ISB();
    }
}

/* #Violation: cache_hal_c_REF_1*/
/* #Violation: cache_hal_c_REF_4*/
void Cache_Hal_CleanD(void)
{
    uint32 uCCSIDR;
    uint32 uDCCSW;
    uint32 uSetsCount;
    uint32 uWaysCount;
    uint32 uCSSELR;
    uint8 uWaysFlag = 0;
    uint8 uSetsFlag = 0;

    /* Select D-cache for CCSIDR */
    /*#Violation: cache_hal_c_REF_2 */
    uCSSELR = 0U;
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    SET_CP(15, 2, uCSSELR, 0, 0, 0);
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    DSB();

    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    GET_CP(15, 1, uCCSIDR, 0, 0, 0);

    /*CCSIDR register:[27:13]: (Number of sets in cache)*/
    uSetsCount = (((uCCSIDR)&CCSIDR_NUMSETS_MASK) >> CCSIDR_NUMSETS_POS);

    do
    {
        if (uSetsFlag != 0U)
        {
            uSetsCount = uSetsCount - 1U;
        }
        else
        {
            uSetsFlag = 1U;
        }
        /*CCSIDR register:[12:3]: (Associativity of cache)*/
        uWaysCount = (((uCCSIDR)&CCSIDR_ASSOCIATIVITY_MASK) >> CCSIDR_ASSOCIATIVITY_POS);
        do
        {
            if (uWaysFlag != 0U)
            {
                uWaysCount = uWaysCount - 1U;
            }
            else
            {
                uWaysFlag = 1U;
            }
            /*#Violation: cache_hal_c_REF_2 */
            uDCCSW = (((uSetsCount << DCCSW_SET_POS) & DCCSW_SET_MASK) | ((uWaysCount << DCCSW_WAY_POS) & DCCSW_WAY_MASK));

            /*#Violation: cache_hal_c_REF_3 */
            /*#Violation: cache_hal_c_REF_7 */
            /*#Violation: cache_hal_c_REF_8 */
            SET_CP(15, 0, uDCCSW, 7, 10, 2);

        } while(uWaysCount != 0U);

    } while(uSetsCount != 0U);
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    DSB();
    /*#Violation: cache_hal_c_REF_3 */
    /*#Violation: cache_hal_c_REF_7 */
    /*#Violation: cache_hal_c_REF_8 */
    ISB();
}

#define CORE_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cache_hal_c_REF_9*/
#include "Core_MemMap.h"

/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

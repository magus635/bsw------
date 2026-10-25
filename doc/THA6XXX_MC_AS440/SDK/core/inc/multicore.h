/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: multicore.h
 * Author:    30032
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file defines APIs and structures provided by multicore module.
 ************************************************************************************************/
/*
* #Violation Summary
*
* #multicore_h_REF_1:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
* #multicore_h_REF_2:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #multicore_h_REF_3:MISRAC2012-Rule-1.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #multicore_h_REF_4:MISRAC2012-Dir-4.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #multicore_h_REF_5:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/

#ifndef MULTICORE_H_
#define MULTICORE_H_

#include "compilertypes.h"

/* core id */
typedef enum
{
    MULTICOREID_CPU0 = 0U,      /* Current core id is 0 */
    MULTICOREID_CPU1 = 1U,      /* Current core id is 1 */
    MULTICOREID_CPU2 = 2U,      /* Current core id is 2 */
    MULTICOREID_CPU3 = 3U,      /* Current core id is 3 */
    MULTICOREID_NONE,           /* Invalid input parameter */
} MultiCoreID;

#define CORE_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: multicore_h_REF_5*/
#include "Core_MemMap.h"

/*********************************************************************
 * Function: Multicore_GetCoreID
 * Description: Get Current Core ID.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:   None.
 * Inout:   None
 * Output:  None.
 * Return:  MultiCoreID, return current core ID.
 * Others:  Do not support in EL0
 * History:
 *  Date          Author    Modified
 *  2023/05/14    30032      create
 ***********************************************************************/
/* #Violation: multicore_h_REF_1 */
LOCAL_FORCEINLINE MultiCoreID Multicore_GetCoreID(void)
{
    MultiCoreID id = MULTICOREID_CPU0;
    /* #Violation: multicore_h_REF_2 */
    /* #Violation: multicore_h_REF_3 */
    /* #Violation: multicore_h_REF_4 */
    ASM_VOLATILE(" mrc p15, 0, r1, c0, c0, 5\n"
                 " and %0, r1, #0xFF        \n"
                 " and r1, r1, #0xFF00      \n"
                 " lsr r1, r1, #7           \n"
                 " uxtab %0, %0, r1         \n"
                 : "=r"(id)
                 :
                 : "r1", "memory");
    return id;
}

#define CORE_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: multicore_h_REF_5*/
#include "Core_MemMap.h"

#endif /* MULTICORE_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

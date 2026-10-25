/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: dev.h
 * Author:    30032
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file defines APIs provided by development module.
 ************************************************************************************************/
/*
* #Violation Summary
*
* #dev_h_REF_1:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
* #dev_h_REF_2:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #dev_h_REF_3:MISRAC2012-Rule-1.2;
* Justification:Inline assembly for CPU-specific operations.
*
* #dev_h_REF_4:MISRAC2012-Dir-4.2;
* Justification:Inline assembly for CPU-specific operations.
*
*/

#ifndef DEV_H_
#define DEV_H_

#include "common_hal.h"
#include "Platform_Types.h"
#include "compilertypes.h"

/*********************************************************************
 * Function: Assert
 * Description: Assert local CPU when cond is false. This function is controlled by
 * macro INPUT_ARG_DETECT.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:      boolean cond, system assert when cond is false.
 * Inout:      None
 * Output:     None
 * Return:     None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/14    30032      create
 ***********************************************************************/
/* #Violation: dev_h_REF_1 */
LOCAL_FORCEINLINE void Assert(boolean cond)
{
    if(cond == FALSE)
    {
#ifdef __TASKING__
        /* #Violation: dev_REF_2 */
        ASM_VOLATILE("  cpsid aif   \n"
                     "  1:b 1p      \n");
#else
        /* #Violation: dev_h_REF_2 */
        /* #Violation: dev_h_REF_3 */
        /* #Violation: dev_h_REF_4 */
        ASM_VOLATILE("cpsid aif\n"
                     "1:b 1b\n");
#endif
    }
}

#endif /* DEV_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    cpu_hal.h
 * Author:      01254
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
#ifndef CORE_CPU_HAL_H_
#define CORE_CPU_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Enumeration for L1 Data prefetch control */
typedef enum
{
    CPU_DATAPREFETCHCONTROL_DISABLE = 0, /* Prefetch disabled */
    CPU_DATAPREFETCHCONTROL_NUM_1,       /* 1 outstanding prefetches allowed */
    CPU_DATAPREFETCHCONTROL_NUM_2,       /* 2 outstanding prefetches allowed */
    CPU_DATAPREFETCHCONTROL_NUM_3,       /* 3 outstanding prefetches allowed */
    CPU_DATAPREFETCHCONTROL_NUM_4,       /* 4 outstanding prefetches allowed */
    CPU_DATAPREFETCHCONTROL_NUM_5,       /* 5 outstanding prefetches allowed */
    CPU_DATAPREFETCHCONTROL_NUM_6,       /* 6 outstanding prefetches allowed */
    CPU_DATAPREFETCHCONTROL_NUM_8        /* 8 outstanding prefetches allowed */
}CPU_DataPrefetchControl;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
#define CORE_START_SEC_CODE_ASIL_D_GLOBAL
#include "Core_MemMap.h"
/**********************************************************************************************************************
 * Function:     CPU_Hal_EnableSA
 * Description:  Enable data side speculative access
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       The function can be used only when the system is idle.
 *               recommends that you use this funcion after the MPU is enabled.
 * History:
 * Date          Author    Modified
 * 2024/08/09    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_EnableDSA(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_DisableSA
 * Description:  Disable data side speculative access
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       The function can be used only when the system is idle.
 *               recommends that you use this funcion after the MPU is enabled.
 * History:
 * Date          Author    Modified
 * 2024/08/09    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_DisableDSA(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_EnableSA
 * Description:  Enable instruction side speculative access
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       The function can be used only when the system is idle.
 *               recommends that you use this funcion after the MPU is enabled.
 * History:
 * Date          Author    Modified
 * 2024/08/09    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_EnableISA(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_DisableSA
 * Description:  Disable instruction side speculative access
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       The function can be used only when the system is idle.
 *               recommends that you use this funcion after the MPU is enabled.
 * History:
 * Date          Author    Modified
 * 2024/08/09    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_DisableISA(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_EnableEL2DBP
 * Description:  Enable dynamic branch predictor when running at EL2
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       If HCR.TIDCP is set to 1, then use this function from EL1 are trapped to EL2.
 * History:
 * Date          Author    Modified
 * 2024/08/22    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_EnableEL2DBP(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_DisableEL2DBP
 * Description:  Disable dynamic branch predictor when running at EL2
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       If HCR.TIDCP is set to 1, then use this function from EL1 are trapped to EL2.
 * History:
 * Date          Author    Modified
 * 2024/08/22    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_DisableEL2DBP(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_EnableEL1DBP
 * Description:  Enable dynamic branch predictor when running at EL1
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       If HCR.TIDCP is set to 1, then use this function from EL1 are trapped to EL2.
 * History:
 * Date          Author    Modified
 * 2024/08/22    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_EnableEL1DBP(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_DisableEL1DBP
 * Description:  Disable dynamic branch predictor when running at EL1
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       If HCR.TIDCP is set to 1, then use this function from EL1 are trapped to EL2.
 * History:
 * Date          Author    Modified
 * 2024/08/22    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_DisableEL1DBP(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_EnableEL0DBP
 * Description:  Enable dynamic branch predictor when running at EL0
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       If HCR.TIDCP is set to 1, then use this function from EL1 are trapped to EL2.
 * History:
 * Date          Author    Modified
 * 2024/08/22    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_EnableEL0DBP(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_DisableEL0DBP
 * Description:  Disable dynamic branch predictor when running at EL0
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       If HCR.TIDCP is set to 1, then use this function from EL1 are trapped to EL2.
 * History:
 * Date          Author    Modified
 * 2024/08/22    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_DisableEL0DBP(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_SetL1DPF
 * Description:  Set L1 Data prefetch control
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        ctl : data prefetch control
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       The function can be used only when the system is idle.
 *               recommends that you use this funcion after the MPU is enabled.
 * History:
 * Date          Author    Modified
 * 2024/08/22    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_SetL1DPF(CPU_DataPrefetchControl ctl);
/**********************************************************************************************************************
 * Function:     CPU_Hal_EnableL1IPF
 * Description:  Enable L1 Instruction prefetch
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       The function can be used only when the system is idle.
 *               recommends that you use this funcion after the MPU is enabled.
 * History:
 * Date          Author    Modified
 * 2024/08/22    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_EnableL1IPF(void);
/**********************************************************************************************************************
 * Function:     CPU_Hal_DisableL1IPF
 * Description:  Disable L1 Instruction prefetch
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       The function can be used only when the system is idle.
 *               recommends that you use this funcion after the MPU is enabled.
 * History:
 * Date          Author    Modified
 * 2024/08/22    01254      create
 *********************************************************************************************************************/
extern void CPU_Hal_DisableL1IPF(void);

#define CORE_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Core_MemMap.h"

#endif /* CORE_CPU_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

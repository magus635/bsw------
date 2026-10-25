/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: basetimer_hal.h
 * Author:   01030
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains definitions and function prototypes for the base timer.
 *********************************************************************************************************************/
#ifndef BASETIMER_HAL_H_
#define BASETIMER_HAL_H_

/*
* #Violation Summary
*
* #basetimer_hal_h_REF_1:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #basetimer_hal_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*/
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "basetimer_register.h"
#include "compilertypes.h"
#include "tha6_cfg.h"
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
/* BASETIMER_MODULE modes definition. */
typedef enum
{
    BASETIMER_MODE_FREERUNNING = 0U, /* BaseTimer mode is free-running */
    BASETIMER_MODE_PERIODIC,         /* BaseTimer mode is periodic */
    BASETIMER_MODE_ONESHOT           /* BaseTimer mode is one-shot */
} Basetimer_Mode;

/* BaseTimer size definition. */
typedef enum
{
    BASETIMER_SIZE_16BITS = 0U, /* BaseTimer size is 16 bits */
    BASETIMER_SIZE_32BITS       /* BaseTimer size is 32 bits */
} Basetimer_Size;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* The basetimer module configuration structure */
typedef struct
{
    Basetimer_Size size; /* Specifies the counter size */
    uint32 load;         /* Specifies the initial counter value */
    Basetimer_Mode mode; /* Specifies the counter mode */
} Basetimer_InitConfig;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: basetimer_hal_h_REF_2 */
#define BASETIMER_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: basetimer_hal_h_REF_1 */
#include "Basetimer_MemMap.h"
/**********************************************************************************************************************
 * Function:    Basetimer_Hal_InitModule
 * Description: Initialize the timer.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant(When initializing different BASETIMER modules, this function is a reentrant function;
 *              in other cases, it is a non-reentrant function)
 * Input:       pTimer: pointer to the timer module.
 *              pConfig: pointer to the timer configuration structure.
 * Inout:       None
 * Output:      None
 * Return:      None
 * Others:
 * Date         Author   Modified
 * 2023/05/08   01030     create
 *********************************************************************************************************************/
extern void Basetimer_Hal_InitModule(BASETIMER_MODULE *const pTimer, const Basetimer_InitConfig *const pConfig);

/**********************************************************************************************************************
 * Function:    Basetimer_Hal_SetInterrupt
 * Description: Set interrupt enable/disable.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant(When operation different BASETIMER modules, this function is a reentrant function;
 *              in other cases, it is a non-reentrant function)
 * Input:       pTimer: pointer to the timer module.
 *              enable: 0-disable interrupt; 1-enable interrupt.
 * Inout:       None
 * Output:      None
 * Return:      None
 * Others:
 * Date         Author   Modified
 * 2023/05/08   01030     create
 *********************************************************************************************************************/
extern void Basetimer_Hal_SetInterrupt(BASETIMER_MODULE *const pTimer, boolean enable);

/**********************************************************************************************************************
 * Function:    Basetimer_Hal_GetRemainingCount
 * Description: Get remaining value.
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       pTimer: pointer to the timer module.
 * Inout:       None
 * Output:      None
 * Return:      uint32: Remaining value
 * Others:
 * Date         Author   Modified
 * 2023/05/08   01030     create
 *********************************************************************************************************************/
extern uint32 Basetimer_Hal_GetRemainingCount(const BASETIMER_MODULE *const pTimer);

/**********************************************************************************************************************
 * Function:    Basetimer_Hal_GetElapsedCount
 * Description: Get elapsed count.
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       pTimer: pointer to the timer module.
 * Inout:       None
 * Output:      None
 * Return:      uint32: Remaining count.
 * Others:
 * Date         Author   Modified
 * 2023/05/08   01030     create
 **********************************************************************************************************************/
extern uint32 Basetimer_Hal_GetElapsedCount(const BASETIMER_MODULE *const pTimer);

/**********************************************************************************************************************
 * Function:    Basetimer_Hal_Reload
 * Description: Reload timer value.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant(When operation different BASETIMER modules, this function is a reentrant function;
 *              in other cases, it is a non-reentrant function)
 * Input:       pTimer: pointer to the timer module.
 *              reload: new timer value. The value range from 0x0 to 0xFFFF_FFFF.
 * Inout:       None
 * Output:      None
 * Return:      None
 * Others:
 * Date         Author   Modified
 * 2023/05/08   01030     create
 *********************************************************************************************************************/
extern void Basetimer_Hal_Reload(BASETIMER_MODULE *const pTimer, uint32 reload);

/**********************************************************************************************************************
 * Function:    Basetimer_Hal_StopTimer
 * Description: Stop timer operation.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant(When operation different BASETIMER modules, this function is a reentrant function;
 *              in other cases, it is a non-reentrant function)
 * Input:       pTimer: pointer to the timer module.
 * Inout:       None
 * Output:      None
 * Return:      None
 * Others:
 * Date         Author   Modified
 * 2023/05/08   01030     create
 *********************************************************************************************************************/
extern void Basetimer_Hal_StopTimer(BASETIMER_MODULE *const pTimer);

/**********************************************************************************************************************
 * Function:    Basetimer_Hal_StartTimer
 * Description: Start timer operation.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant(When operation different BASETIMER modules, this function is a reentrant function;
 *              in other cases, it is a non-reentrant function)
 * Input:       pTimer: pointer to the timer module.
 * Inout:       None
 * Output:      None
 * Return:      None
 * Others:
 * Date         Author   Modified
 * 2023/05/08   01030     create
 **********************************************************************************************************************/
extern void Basetimer_Hal_StartTimer(BASETIMER_MODULE *const pTimer);

/**********************************************************************************************************************
 * Function:    Basetimer_Hal_ClearFlag
 * Description: Clear timer status register.
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       pTimer: pointer to the timer module.
 * Inout:       None
 * Output:      None
 * Return:      None
 * Others:
 * Date         Author   Modified
 * 2023/05/08   01030     create
 **********************************************************************************************************************/
extern void Basetimer_Hal_ClearFlag(BASETIMER_MODULE *const pTimer);

/**********************************************************************************************************************
 * Function:    Basetimer_Hal_SetLoad
 * Description: Set load value.
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant(When operation different BASETIMER modules, this function is a reentrant function;
 *              in other cases, it is a non-reentrant function)
 * Input:       pTimer: pointer to the timer module.
 *              loadValue: Set new timer load value. The value range from 0x0 to 0xFFFF_FFFF.
 * Inout:       None
 * Output:      None
 * Return:      None
 * Others:
 * Date         Author   Modified
 * 2023/05/08   01030     create
 **********************************************************************************************************************/
extern void Basetimer_Hal_SetLoad(BASETIMER_MODULE *const pTimer, uint32 loadValue);



/* #Violation: basetimer_hal_h_REF_2 */
#define BASETIMER_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: basetimer_hal_h_REF_1 */
#include "Basetimer_MemMap.h"

#endif /* BASETIMER_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

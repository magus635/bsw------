/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_timer_hal.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations of the TIMER module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#gtm_timer_hal_h_REF_1:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_timer_hal_h_REF_2:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_timer_hal_h_REF_3:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef GTM_TIMER_HAL_H_
#define GTM_TIMER_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_tom_std.h"
#include "gtm_register.h"
#include "gtm.h"
#include "Platform_Types.h"
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
/* Timer information */
typedef enum
{
    GTM_TIMER_COUNT_USED = 0U,    /* Time used */
    GTM_TIMER_COUNT_REMAIN,       /* Time remain */
    GTM_TIMER_COUNT_PERIOD        /* Timer period */
} Gtm_Timer_Count;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Initialization configuration structure for TIMER */
/* #Violation: gtm_timer_hal_h_REF_1 */
typedef struct
{
    Gtm_Tom_Ch_ClkSrc        clk;                 /* Timer input clock */
    Gtm_IrqMode              irqMode;             /* Interrupt mode for the timer */
    Gtm_Tom_Ch_TrigOut       trigOut;             /* Trigger output signal select */
    boolean                  isOneShotEnable;     /* Enable/Disable the one shot mode */
    boolean                  isIrqEnable;         /* Enable/Disable choice for timer interrupt */
} Gtm_Timer_Config;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_timer_hal_h_REF_3 */
#define GPT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timer_hal_h_REF_2 */
#include "Gpt_MemMap.h"
#else
/* #Violation: gtm_timer_hal_h_REF_3 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timer_hal_h_REF_2 */
#include "Gtm_MemMap.h"
#endif

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_InitChannel
 * Description:  TIMER channel initialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 *               pConfig: The pointer of the initialization configuration structure for TIMER channel
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/07/17    01031      Change the structure member filter to a pointer variable
 *********************************************************************************************************************/
extern boolean Gtm_Timer_Hal_InitChannel(const Gtm_Output_Driver *const pDriver, const Gtm_Timer_Config *const pConfig);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_DeinitChannel
 * Description:  TIMER channel deinitialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern void Gtm_Timer_Hal_DeinitChannel(const Gtm_Output_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_GetChannelInfo
 * Description:  Get channel time information
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 *               timeCount: Time information
 * Inout:        None
 * Output:       None
 * Return:       uint32: Time used or time remain
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Timer_Hal_GetChannelInfo(const Gtm_Output_Driver *const pDriver, Gtm_Timer_Count timeCount);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_StartChannel
 * Description:  Start channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 *               period: Timer period (the maximum value is 0xFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       This function is called only when the channel is disabled!
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Timer_Hal_StartChannel(const Gtm_Output_Driver *const pDriver, uint32 period);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_StopChannel
 * Description:  Stop channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Timer_Hal_StopChannel(const Gtm_Output_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_SetCounterValue
 * Description:  Sets channel counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 *               value: Counter value (the maximum value is 0xFFFF)
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern void Gtm_Timer_Hal_SetCounterValue(const Gtm_Output_Driver *const pDriver, uint32 value);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_GetCounterValue
 * Description:  Gets channel counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 * Inout:        None
 * Output:       None
 * Return:       uint32: Counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Timer_Hal_GetCounterValue(const Gtm_Output_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_GetCompareZero
 * Description:  Gets the channel compare zero(period) value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 * Inout:        None
 * Output:       None
 * Return:       uint32: Compare zero(period) value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/11/14    01177      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Timer_Hal_GetCompareZero(const Gtm_Output_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_SetInterrupt
 * Description:  Enable / disable channel interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 *                  enable: Enable/ Disable choice of the feature
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Timer_Hal_SetInterrupt(const Gtm_Output_Driver *const pDriver, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_GetInterruptStatus
 * Description:  Gets channel interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 * Inout:        None
 * Output:       None
 * Return:       boolean: Interrupt status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Timer_Hal_GetInterruptStatus(const Gtm_Output_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_GetInterruptEnableStatus
 * Description:  Gets channel interrupt enable status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 * Inout:        None
 * Output:       None
 * Return:       boolean: Interrupt enable status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/27    01177     Create
 *********************************************************************************************************************/
extern boolean Gtm_Timer_Hal_GetInterruptEnableStatus(const Gtm_Output_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Timer_Hal_ClearInterruptStatus
 * Description:  Clears channel interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the TIMER
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01031      Create
 *********************************************************************************************************************/
extern void Gtm_Timer_Hal_ClearInterruptStatus(const Gtm_Output_Driver *const pDriver);

#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_timer_hal_h_REF_3 */
#define GPT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timer_hal_h_REF_2 */
#include "Gpt_MemMap.h"
#else
/* #Violation: gtm_timer_hal_h_REF_3 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timer_hal_h_REF_2 */
#include "Gtm_MemMap.h"
#endif

#endif /* GTM_TIMER_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/***************************************************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:  stm_hal.h
 * Author:    30037
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all data type definitions and function declarations
 ************************************************************************************************/
/*
* #Violation Summary
*
* #stm_hal_h_REF_1:MISRAC2012-Dir-4.8;
* Justification:Apply such struct/union definitions to simplify the code structure
*               and reduce the code complexity.
*
* #stm_hal_h_REF_2:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #stm_hal_h_REF_3:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #stm_hal_h_REF_4:MISRAC2012-Dir-1.1;
* Justification:Inline assembly for CPU-specific operations.
*
* #stm_hal_h_REF_5:MISRAC2012-Dir-4.3;
* Justification:Mixing inline assembly with C code reduces code complexity.
*
*/
#ifndef  STM_HAL_H_
#define  STM_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes                                                        
 *********************************************************************************************************************/
#include "stm_std.h"
#include "stm_register.h"
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
/* Indicates whether the timer condition has been reached */
typedef enum
{
    STM_TIMER_NOT_MET = 0U,         /* Timer condition is not met */
    STM_TIMER_MET                   /* Timer condition is met */
}Stm_TimerStatus;
/**********************************************************************************************************************
 *                                              Global Union Definitions                                               
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions                                             
 *********************************************************************************************************************/
/* Structure of STM block configuration */
/* #Violation: stm_hal_h_REF_1 */
typedef struct
{
    boolean intr;                 /* 0-unmask interrupt; 1-mask interrupt */
    Stm_Event_Config *pEvent_cfg; /* Event stream config */
} Stm_Timer_Config;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************//* #Violation: stm_hal_h_REF_2 */
#define STM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: stm_hal_h_REF_3 */
#include "Stm_MemMap.h"
/**********************************************************************************************************************
 * Function:     Stm_Hal_GetValue
 * Description:  Get 64 bits system counter value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint64: System counter value.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint64 Stm_Hal_GetValue(void);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/* #Violation: stm_hal_h_REF_5 */
LOCAL_FORCEINLINE uint64 Stm_Hal_GetValue(void)
{
    /******************************************************************************************************************
     * Usage Restrictions
     * - System Timer Clock maximum is 25 MHz, if the CPU_CLK clock is less than 50MHz, adjust the STM module clock to 
     *   be less than half of the CPU_CLK clock.
     * - After an application reset, it needs to be configured again according to the clock constraints described above
     *   before it can be used.
     * - This function is used by default in EL1 mode. If it is to be used in EL0 mode, the PL0PCTEN bit field (bit[0])
     *   of the CNTKCTL register needs to be configured in EL1 mode first, and then switched to EL0 mode. After that,
     *   the function can be used normally.The reference code for modifying the register is as follows:
     *   MRC p15,0,<Rt>,14,1,0 ; Read CNTKCTL into Rt
     *   Rt = Rt | 0x1         ; Set the PL0PCTEN of CNTKCTL to 1
     *   MCR p15,0,<Rt>,14,1,0 ; Write Rt to CNTKCTL
    ******************************************************************************************************************/
    volatile uint64 value;
    value = 0U;

    /* Get Physical Count */
    /* #Violation: stm_hal_h_REF_4 */
    GET_CP64(15, 0, (value), 14);

    return value;

}
/**********************************************************************************************************************
 *                                            Global Function Declarations                                             
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Function:     Stm_Hal_Start
 * Description:  Start the system counter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE-Register read back check correct.
 *               FALSE-Register read back check incorrect.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern boolean Stm_Hal_Start(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Stop
 * Description:  Stop the system counter.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE-Register read back check correct.
 *               FALSE-Register read back check incorrect.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern boolean Stm_Hal_Stop(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_SetValue
 * Description:  Set 64 bit system counter value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value: Configuration structure of the value. The value range from 0x0 to 0xFFFF_FFFF_FFFF_FFFF.
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE-Register read back check correct.
 *               FALSE-Register read back check incorrect.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern boolean Stm_Hal_SetValue(uint64 value);

/**********************************************************************************************************************
 * Function:     Stm_Hal_InitPhyEL1Timer
 * Description:  Init EL1 physical timer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTimerConfig: Configuration structure of the Stm_Timer_Config.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_InitPhyEL1Timer(const Stm_Timer_Config *const pTimerConfig);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Get32BitPhyEL1TimerValue
 * Description:  Get EL1 physical timer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint32: 32-bit EL1 physical timer.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern uint32 Stm_Hal_Get32BitPhyEL1TimerValue(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Get64BitPhyEL1TimerCompareValue
 * Description:  Get EL1 physical Compare value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint64: 64-bit EL1 physical timer.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/11    30037      create
 *********************************************************************************************************************/
extern uint64 Stm_Hal_Get64BitPhyEL1TimerCompareValue(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Set32BitPhyEL1TimerValue
 * Description:  Set EL1 physical timer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value: 32bits timer value. The value range from 0x0 to 0xFFFF_FFFF.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_Set32BitPhyEL1TimerValue(uint32 value);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Set64BitPhyEL1TimerCompareValue
 * Description:  Set EL1 physical Compare value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value: 64bits timer value. The value range from 0x0 to 0xFFFF_FFFF_FFFF_FFFF.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_Set64BitPhyEL1TimerCompareValue(uint64 value);

/**********************************************************************************************************************
 * Function:     Stm_Hal_EnablePhyEL1Timer
 * Description:  Enable EL1 physical Timer output signal.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_EnablePhyEL1Timer(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_DisablePhyEL1Timer
 * Description:  Disable EL1 physical Timer output signal.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_DisablePhyEL1Timer(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_GetPhyEL1TimerStatus
 * Description:  Get status of the EL1 physical timer. This function indicates whether the timer condition is met.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       Stm_TimerStatus: 0-Timer condition is not met; 1-Timer condition is met;
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern Stm_TimerStatus Stm_Hal_GetPhyEL1TimerStatus(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_InitPhyEL2Timer
 * Description:  Init EL2 physical timer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTimerConfig: Configuration structure of the Stm_Timer_Config.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_InitPhyEL2Timer(const Stm_Timer_Config *const pTimerConfig);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Get32BitPhyEL2TimerValue
 * Description:  Get EL2 physical timer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint32: 32-bit EL2 physical timer.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern uint32 Stm_Hal_Get32BitPhyEL2TimerValue(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Get64BitPhyEL2TimerCompareValue
 * Description:  Get EL2 physical Compare value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint64: 64-bit EL2 physical timer.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/11    30037      create
 *********************************************************************************************************************/
extern uint64 Stm_Hal_Get64BitPhyEL2TimerCompareValue(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Set32BitPhyEL2TimerValue
 * Description:  Set EL2 physical timer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value: 32bits timer value. The value range from 0x0 to 0xFFFF_FFFFF.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_Set32BitPhyEL2TimerValue(uint32 value);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Set64BitPhyEL2TimerCompareValue
 * Description:  Set EL2 physical Compare value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value: 64bits timer value. The value range from 0x0 to 0xFFFF_FFFF_FFFF_FFFF.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_Set64BitPhyEL2TimerCompareValue(uint64 value);

/**********************************************************************************************************************
 * Function:     Stm_Hal_EnablePhyEL2Timer
 * Description:  Enable EL2 physical Timer output signal.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_EnablePhyEL2Timer(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_DisablePhyEL2Timer
 * Description:  Disable EL2 physical Timer output signal.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_DisablePhyEL2Timer(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_GetPhyEL2TimerStatus
 * Description:  Get status of the EL2 physical timer. This function indicates whether the timer condition is met.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       Stm_TimerStatus: 0-Timer condition is not met; 1-Timer condition is met;
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern Stm_TimerStatus Stm_Hal_GetPhyEL2TimerStatus(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_VirtualTimerInit
 * Description:  Init Virtual timer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTimerConfig: Configuration structure of the Stm_Timer_Config.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_InitVirtualTimer(const Stm_Timer_Config *const pTimerConfig);

/**********************************************************************************************************************
 * Function:     Stm_Hal_VirtualTimerGet32BitValue
 * Description:  Get Virtual timer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint32: 32-bit Virtual timer.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern uint32 Stm_Hal_Get32BitVirtualTimerValue(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Get64BitVirtualTimerCompareValue
 * Description:  Get Virtual Compare value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint64: 64-bit Virtual timer.
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/11    30037      create
 *********************************************************************************************************************/
extern uint64 Stm_Hal_Get64BitVirtualTimerCompareValue(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Set32BitVirtualTimerValue
 * Description:  Set Virtual timer.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value: 32bits timer value. The value range from 0x0 to 0xFFFF_FFFF.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_Set32BitVirtualTimerValue(uint32 value);

/**********************************************************************************************************************
 * Function:     Stm_Hal_Set64BitVirtualTimerCompareValue
 * Description:  Set Virtual Compare value.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        value: 64bits timer value. The value range from 0x0 to 0xFFFF_FFFF_FFFF_FFFF.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_Set64BitVirtualTimerCompareValue(uint64 value);

/**********************************************************************************************************************
 * Function:     Stm_Hal_EnableVirtualTimer
 * Description:  Enable Virtual Timer output signal.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_EnableVirtualTimer(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_GetVitualTimerStatus
 * Description:  Disable Virtual Timer output signal.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Hal_DisableVirtualTimer(void);

/**********************************************************************************************************************
 * Function:     Stm_Hal_GetVitualTimerStatus
 * Description:  Get status of the Virtual timer. This function indicates whether the timer condition is met.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       Stm_TimerStatus: 0-Timer condition is not met; 1-Timer condition is met;
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern Stm_TimerStatus Stm_Hal_GetVitualTimerStatus(void);

/* #Violation: stm_hal_h_REF_2 */
#define STM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: stm_hal_h_REF_3 */
#include "Stm_MemMap.h"

#endif /* STM_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File                                                     
 *********************************************************************************************************************/


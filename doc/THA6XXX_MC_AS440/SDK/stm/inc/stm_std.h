/**********************************************************************************************************************
 * FileName:  stm_std.h
 * Author:    30037
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file contains all data type definitions and function declarations
 ************************************************************************************************/
/*
* #Violation Summary
*
* #stm_std_h_REF_1:MISRAC2012-Dir-4.8;
* Justification:Apply such struct/union definitions to simplify the code structure
*               and reduce the code complexity.
*
* #stm_std_h_REF_2:CertC-DCL12-C;
* Justification:Apply such struct/union definitions to simplify the code structure and reduce the code complexity.
*
* #stm_std_h_REF_3:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #stm_std_h_REF_4:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*
*/
#ifndef  STM_STD_H_
#define  STM_STD_H_
/**********************************************************************************************************************
 *                                                     Includes                                                        
 *********************************************************************************************************************/
#include "common_hal.h"
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
/**********************************************************************************************************************
 *                                              Global Union Definitions                                               
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions                                             
 *********************************************************************************************************************/
/* Structure of STM event Block Configuration */
/* #Violation: stm_std_h_REF_1 */
/* #Violation: stm_std_h_REF_2 */
typedef struct
{
    boolean enable;      /* 0: Disable event stream 1: Enable event stream */
    boolean transition;  /* 0:  0 to 1 transition of the trigger bits triggers an event.  1:  1 to 0 transition of the
                            trigger bits triggers an event. */
    uint8 generate_bit;  /* Set event stream generation Bit.Only can set from 0-15 */
} Stm_Event_Config;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations                                          
 *********************************************************************************************************************/
/* #Violation: stm_std_h_REF_3 */
#define STM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: stm_std_h_REF_4 */
#include "Stm_MemMap.h"
/**********************************************************************************************************************
 * Function:     Stm_Register_ReadBack_Check
 * Description:  Check register readback values
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        state: initial state
 *               expect: Desired value
 *               value: readback value
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *               TRUE: Register read back check correct
 *               FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date         Author   Modified
 *  2024/11/10   01849    create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Stm_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define STM_REG_CHECK
#if defined(STM_REG_CHECK)
LOCAL_FORCEINLINE boolean Stm_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Stm_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Stm_Std_PhyEL1TimerInterruptMaskSet
 * Description:  Mask/Unmask EL1 physical interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intr: 0: unmask interrupt 1: mask interrupt
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Std_SetPhyEL1TimerInterrupt(boolean intr);  

/**********************************************************************************************************************
 * Function:     Stm_Std_SetPhyEL1TimerEvent
 * Description:  Enable/Disable and confige EL1 physical event stream
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEvent: Configuration structure of the Stm_Event_Config
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Std_SetPhyEL1TimerEvent(const Stm_Event_Config *const pEvent);

/**********************************************************************************************************************
 * Function:     Stm_Std_PhyEL2TimerInterruptMaskSet
 * Description:  Mask/Unmask EL2 physical interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intr: 0: unmask interrupt 1: mask interrupt
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Std_SetPhyEL2TimerInterrupt(boolean intr);

/**********************************************************************************************************************
 * Function:     Stm_Std_SetPhyEL2TimerEvent
 * Description:  Enable/Disable and confige EL2 physical event stream
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEvent: Configuration structure of the Stm_Event_Config
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Std_SetPhyEL2TimerEvent(const Stm_Event_Config *const pEvent);

/**********************************************************************************************************************
 * Function:     Stm_Std_VirtualTimerInterruptMaskSet
 * Description:  Mask/Unmask Virtual interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        intr: 0: unmask interrupt 1: mask interrupt
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2022/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Std_SetVirtualTimerInterrupt(boolean intr);

/*********************************************************************************************************************
 * Function:     Stm_Std_SetVirtualTimerEvent
 * Description:  Enable/Disable and confige Virtual event stream
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEvent: Configuration structure of the Stm_Event_Config
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/11    30037      create
 *********************************************************************************************************************/
extern void Stm_Std_SetVirtualTimerEvent(const Stm_Event_Config *const pEvent);

/* #Violation: stm_std_h_REF_3 */
#define STM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: stm_std_h_REF_4 */
#include "Stm_MemMap.h"

#endif /* STM_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File                                                     
 *********************************************************************************************************************/

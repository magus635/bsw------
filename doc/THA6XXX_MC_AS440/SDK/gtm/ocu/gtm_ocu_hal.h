/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_ocu_hal.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations of the OCU module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_ocu_hal_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_ocu_hal_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_ocu_hal_h_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_ocu_hal_h_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
 #ifndef GTM_OCU_HAL_H_
#define GTM_OCU_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_atom_std.h"
#include "gtm_tbu_std.h"
#include "gtm_register.h"
#include "gtm.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* GTM_OCU_SLCTRL_DEFINE */
/* #Violation: gtm_ocu_hal_h_REF_4 */
#define  GTM_OCU_SLCTRL_NOCHANGE  ((uint8)0x00)   /* No signal level change at output */
#define  GTM_OCU_SLCTRL_OUT1      ((uint8)0x01)   /* Output = 1 */
#define  GTM_OCU_SLCTRL_OUT0      ((uint8)0x02)   /* Output = 0 */
/* #Violation: gtm_ocu_hal_h_REF_4 */
#define  GTM_OCU_SLCTRL_TOGGLE    ((uint8)0x03)   /* Toggle the output signal level */

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
/* OCU channel interrupt control */
typedef struct
{
    boolean         isCcu0Enabled;       /* Enable/Disable choice for CCU0 trigger interrupt */
    boolean         isCcu1Enabled;       /* Enable/Disable choice for CCU1 trigger interrupt */
    Gtm_IrqMode     mode;                /* IRQ mode of interrupt */
} Gtm_Ocu_ConfigIrq;

/* SOMC output behavior control */
/* #Violation: gtm_ocu_hal_h_REF_2 */
typedef struct
{
    uint8                somcSignalLevelControl;    /* Signal level control */
                                                    /* This parameter can be a value of GTM_OCU_SLCTRL_DEFINE */
    Gtm_SomcCtrl         somcCompareStrategy;       /* Compare strategy, the value cannot be GTM_SOMCCTRL_CMPBOTH1 */
} Gtm_Ocu_Output_Behavior;

/* SOMC compare value control */
/* #Violation: gtm_ocu_hal_h_REF_1 */
/* #Violation: gtm_ocu_hal_h_REF_2 */
typedef struct
{
    uint32 cm0;            /* Compare zero value */
    uint32 cm1;            /* Compare one value */
} Gtm_Ocu_Control;

/* Initialization configuration structure for OCU */
/* #Violation: gtm_ocu_hal_h_REF_2 */
typedef struct
{
    Gtm_Atom_Ch_ClkSrc          clk;                /* Timer input clock */
    Gtm_Atom_TimeBase           timeBase;           /* Time base for OCU channel */
    Gtm_SignalState             signalLevel;        /* Signal Level */
    Gtm_Ocu_Output_Behavior     somcCtrl;           /* The control of the ATOM output behavior */
    Gtm_Ocu_ConfigIrq           interrupt;          /* Configuration structure for interrupt */
    uint32                      compareValue0;      /* Compare zero value */
    uint32                      compareValue1;      /* Compare one value */
} Gtm_Ocu_Config;
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
/* #Violation: gtm_ocu_hal_h_REF_4 */
#define OCU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_ocu_hal_h_REF_3 */
#include "Ocu_MemMap.h"
#else
/* #Violation: gtm_ocu_hal_h_REF_4 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_ocu_hal_h_REF_3 */
#include "Gtm_MemMap.h"
#endif

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_InitChannel
 * Description:  OCU channel initialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the OCU
 *               pConfig: The pointer of the initialization configuration structure for OCU channel
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Ocu_Hal_InitChannel(const Gtm_Output_Driver *const pDriver, const Gtm_Ocu_Config *const pConfig);

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_SetInterrupt
 * Description:  Enable / disable OCU channel interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the OCU
 *               isCcu0Enabled: Enable/Disable choice for CCU0 trigger interrupt
 *               isCcu1Enabled: Enable/Disable choice for CCU1 trigger interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Ocu_Hal_SetInterrupt(const Gtm_Output_Driver *const pDriver, boolean isCcu0Enabled, 
                                                                                         boolean isCcu1Enabled);

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_SetSignalLevel
 * Description:  Set channel signal level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the OCU
 *               signalLevel: Output signal level
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       This function has to be called before calling Gtm_Ocu_Hal_InitChannel(),
 *               Gtm_Ocu_Hal_SetOutputBehavior() and Gtm_Ocu_Hal_SetSignalLevelControl()
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Ocu_Hal_SetSignalLevel(const Gtm_Output_Driver *const pDriver, Gtm_SignalState signalLevel);

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_SetSignalLevelControl
 * Description:  Sets the output signal level control
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the OCU
 *               ctrl: Output signal level control, can be a value of GTM_OCU_SLCTRL_DEFINE
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Ocu_Hal_SetSignalLevelControl(const Gtm_Output_Driver *const pDriver, uint8 ctrl);

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_SetOutputBehavior
 * Description:  Sets the output behavior of the OCU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the OCU
 *               pCtrl: The pointer of compare value and result
 *               pBehavior: Pointer to output behavior (output signal level and compare strategy)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/08/01    01031      Parameter type modification
 *********************************************************************************************************************/
extern boolean Gtm_Ocu_Hal_SetOutputBehavior(const Gtm_Output_Driver *const pDriver, 
                                   const Gtm_Ocu_Control *const pCtrl, const Gtm_Ocu_Output_Behavior *const pBehavior);

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_SetChannelOutput
 * Description:  Start / stop channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the OCU
 *               channelEnable: Enable / disable channel
 *               outEnable: Enable / disable channel output
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/07/17    01031      Added output enable control
 *********************************************************************************************************************/
extern boolean Gtm_Ocu_Hal_SetChannelOutput(const Gtm_Output_Driver *const pDriver, boolean channelEnable, 
                                                                                        boolean outEnable);

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_GetCounterValue
 * Description:  Gets time base value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        channel: TBU channel index
 * Inout:        None
 * Output:       None
 * Return:       uint32: TBU counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Ocu_Hal_GetCounterValue(Gtm_Tbu_Ch channel);

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_GetInterruptStatus
 * Description:  Gets specific / all interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the OCU
 *                  irq: Interrupt types
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt status. If gets all status, bit 0: CCU0TC, bit 1: CCU1TC
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Ocu_Hal_GetInterruptStatus(const Gtm_Output_Driver *const pDriver, Gtm_Atom_IrqType irq);

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_GetInterruptEnableStatus
 * Description:  Gets specific / all interrupt enable status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the OCU
 *                  irq: Interrupt types
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt enable status. If gets all status, bit 0: CCU0TC, bit 1: CCU1TC
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/27    01177     Create
 *********************************************************************************************************************/
extern uint32 Gtm_Ocu_Hal_GetInterruptEnableStatus(const Gtm_Output_Driver *const pDriver, Gtm_Atom_IrqType irq);

/**********************************************************************************************************************
 * Function:     Gtm_Ocu_Hal_ClearInterruptStatus
 * Description:  Clears specific / all interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the OCU
 *                  irq: Interrupt types
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern void Gtm_Ocu_Hal_ClearInterruptStatus(const Gtm_Output_Driver *const pDriver, Gtm_Atom_IrqType irq);

#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_ocu_hal_h_REF_4 */
#define OCU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_ocu_hal_h_REF_3 */
#include "Ocu_MemMap.h"
#else
/* #Violation: gtm_ocu_hal_h_REF_4 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_ocu_hal_h_REF_3 */
#include "Gtm_MemMap.h"
#endif

#endif /* GTM_OCU_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

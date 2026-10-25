/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_atom_std.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations for all the internal
 *              functions of the ATOM module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#gtm_atom_std_h_REF_1:MISRAC2012-Rule-2.3;
* Justification: The members of the type are used in configuration-gererated code.
*
*#gtm_atom_std_h_REF_2:MISRAC2012-Rule-11.5;
* Justification: Type conversions do not result in errors.
*
*#gtm_atom_std_h_REF_3:MISRAC2012-Rule-10.5;
* Justification: Necessary type casting to reduce code complexity. Code review ensure the safety of the casting.
*
*#gtm_atom_std_h_REF_4:MISRAC2012-Dir-1.1;
* Justification: Necessary type casting for memory and/or register accessing.
*
*#gtm_atom_std_h_REF_5:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #gtm_atom_std_h_REF_6:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_atom_std_h_REF_7:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef GTM_ATOM_STD_H_
#define GTM_ATOM_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm_register.h"
#include "gtm.h"
#include "compilertypes.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
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
/* ATOM channel trigger output signal */
typedef enum
{
    GTM_ATOM_CH_OUTPUTTRIGGER_FORWARD  = 0U,  /* Forward the trigger from the previous channel */
    GTM_ATOM_CH_OUTPUTTRIGGER_GENERATE        /* Generate the trigger from the current channel */
/* #Violation: gtm_atom_std_h_REF_1 */
} Gtm_Atom_Ch_OutputTrigger;

/* Reset event for channel counter CN0 */
typedef enum
{
    GTM_ATOM_CH_RESETEVENT_ONCM0     = 0U,  /* Reset counter register CN0 on matching comparison with CM0 */
    GTM_ATOM_CH_RESETEVENT_ONTRIGGER        /* Reset counter register CN0 on trigger */
/* #Violation: gtm_atom_std_h_REF_1 */
} Gtm_Atom_Ch_ResetEvent;

/*  ATOM channel mode */
typedef enum
{
    GTM_ATOM_MODE_OUTPUTIMMEDIATE = 0U,     /* ATOM signal output mode immediate */
    GTM_ATOM_MODE_OUTPUTCOMPARE,            /* ATOM signal output mode compare */
    GTM_ATOM_MODE_OUTPUTPWM,                /* ATOM signal output mode PWM */
    GTM_ATOM_MODE_OUTPUTSERIAL,             /* ATOM signal output mode serial */
    GTM_ATOM_MODE_OUTPUTBUFFER              /* ATOM signal output mode buffered compare */
} Gtm_Atom_Mode;

/* Match compare control modes */
/* #Violation: gtm_atom_std_h_REF_1 */
typedef enum
{
    GTM_SOMCCTRL_CMPBOTH     = 0U,      /* Compare CCU0 and CCU1 in parallel, disable the CCUx on a compare match on
                                           either of compare units. */
    GTM_SOMCCTRL_CMPBOTH1,              /* Compare CCU0 and CCU1 in parallel, disable the CCU0 or CCU1 on a compare
                                           match on either compare units. */
    GTM_SOMCCTRL_CCU0TS0,               /* Compare CCU0 against TS0 */
    GTM_SOMCCTRL_CCU1TS12,              /* Compare only CCU1 against TS1 or TS2 */
    GTM_SOMCCTRL_CCU01TS0,              /* Compare CCU0 then CCU1, use TS0 */
    GTM_SOMCCTRL_CCU01TS12,             /* Compare CCU0 then CCU1. Use TS1 or TS2 */
    GTM_SOMCCTRL_CCU0TS0CCU1TS12,       /* Compare CCU0 with TS0 then CCU1 with TS1 or TS2 */
    GTM_SOMCCTRL_CNACELCOMPARE          /* Cancel pending compare events */
} Gtm_SomcCtrl;

/* SOMC signal level Control */
typedef enum
{
    GTM_SOMCSLCTRL_NOCHANGE = 0U,   /* No signal level change at output */
    GTM_SOMCSLCTRL_SL0OUT1,         /* SL= 0 -> Out=1; SL=1->Out=0 */
    GTM_SOMCSLCTRL_SL0OUT0,         /* SL=0->Out=0; SL=1->Out=1 */
    GTM_SOMCSLCTRL_TOGGLE           /* Toggle the output signal level */
/* #Violation: gtm_atom_std_h_REF_1 */
} Gtm_SomcSLCtrl;

/* Clock source for the ATOM channels */
typedef enum
{
    GTM_ATOM_CH_CLKSRC_CMUCLK0      = 0U,   /* CMU_CLK 0 */
    GTM_ATOM_CH_CLKSRC_CMUCLK1,             /* CMU_CLK 1 */
    GTM_ATOM_CH_CLKSRC_CMUCLK2,             /* CMU_CLK 2 */
    GTM_ATOM_CH_CLKSRC_CMUCLK3,             /* CMU_CLK 3 */
    GTM_ATOM_CH_CLKSRC_CMUCLK4,             /* CMU_CLK 4 */
    GTM_ATOM_CH_CLKSRC_CMUCLK5,             /* CMU_CLK 5 */
    GTM_ATOM_CH_CLKSRC_CMUCLK6,             /* CMU_CLK 6 */
    GTM_ATOM_CH_CLKSRC_CMUCLK7,             /* CMU_CLK 7 */
    GTM_ATOM_CH_CLKSRC_NOCLOCK,             /* No clock */
    GTM_ATOM_CH_CLKSRC_STOP         = 12U,  /* Functional operation stopped, clock resolution tied to zero */
    GTM_ATOM_CH_CLKSRC_TRIGOUT,             /* ATOM_CH_TRIGOUT x-1:x-1 */
    GTM_ATOM_CH_CLKSRC_EXTTRIGIN            /* ATOM_EXT_TRIGIN x:x */
} Gtm_Atom_Ch_ClkSrc;

/* ATOM interrupt type */
typedef enum
{
    GTM_ATOM_IRQTYPE_NONE = GTM_OM_IRQTYPE_NONE, /* None interrupt */
    GTM_ATOM_IRQTYPE_CCU0 = GTM_OM_IRQTYPE_CCU0, /* CCU0 trigger condition interrupt for channel [x] */
    GTM_ATOM_IRQTYPE_CCU1 = GTM_OM_IRQTYPE_CCU1, /* CCU1 trigger condition interrupt for channel [x] */
    GTM_ATOM_IRQTYPE_ALL  = GTM_OM_IRQTYPE_ALL   /* All interrupt */
} Gtm_Atom_IrqType;

/* ATOM channel time base */
typedef enum
{
    GTM_ATOM_TIMEBASE_TS1 = 0U,     /* TBU_TS1  */
    GTM_ATOM_TIMEBASE_TS2            /* TBU_TS2  */
} Gtm_Atom_TimeBase;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: gtm_atom_std_h_REF_7 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_atom_std_h_REF_6 */
#include "Gtm_MemMap.h"

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetClockSource
 * Description:  Sets the channel clock source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               clk: Channel clock source (0~15)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetClockSource(GTM_OBP_C pAtom, uint8 channel, uint8 clk);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetClockSourceShadow
 * Description:  Sets the channel shadow clock source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               clk: Channel clock source (0~15)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/02    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetClockSourceShadow(GTM_OBP_C pAtom, uint8 channel, uint8 clk);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetCompareOne
 * Description:  Sets the compare one value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               compareOne: Compare one value (the maximum value is 0xFFFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCompareOne(GTM_OBP_C pAtom, uint8 channel, uint32 compareOne);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetShadowOne
 * Description:  Sets the compare one shadow value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               shadowOne: Compare one shadow value (the maximum value is 0xFFFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetShadowOne(GTM_OBP_C pAtom, uint8 channel, uint32 shadowOne);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetCompareZero
 * Description:  Sets the compare zero value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               compareZero: Compare zero value (the maximum value is 0xFFFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCompareZero(GTM_OBP_C pAtom, uint8 channel, uint32 compareZero);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetShadowZero
 * Description:  Sets the compare zero shadow value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               shadowZero: Compare zero shadow value (the maximum value is 0xFFFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetShadowZero(GTM_OBP_C pAtom, uint8 channel, uint32 shadowZero);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetCounterValue
 * Description:  Sets the counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               value:Counter value (the maximum value is 0xFFFFFF)
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Gtm_Atom_Std_SetCounterValue(GTM_OBP_C pAtom, uint8 channel, uint32 value);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetCounterValue
 * Description:  Gets the counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Atom_Std_GetCounterValue(GTM_C_OBP_C pAtom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetCounterRstSrc
 * Description:  Sets the channel counter reset source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               event: Counter reset event (0~1)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCounterRstSrc(GTM_OBP_C pAtom, uint8 channel, uint8 event);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetCounterRstSrc
 * Description:  Gets the channel counter reset source
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 * Inout:        None
 * Output:       None
 * Return:       uint8: 0: counter reset on CN0 match comparison with CM0
 *                      1: counter reset on trigger
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/11/22    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint8 Gtm_Atom_Std_GetCounterRstSrc(GTM_C_OBP_C pAtom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetSignalLevel
 * Description:  Sets the signal level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               activeState: Signal level active state. In case the channel is reset, the output is set to not active.
 *                            The signal is active between 0 and the leading edge (CM1) and inactive between the
 *                            leading edge and the trailing edge (CM0).
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetSignalLevel(GTM_OBP_C pAtom, uint8 channel, Gtm_SignalState activeState);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetSignalLevelShadow
 * Description:  Sets the shadow signal level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               activeState: Signal level active state. In case the channel is reset, the output is set to not active.
 *                            The signal is active between 0 and the leading edge (CM1) and inactive between the
 *                            leading edge and the trailing edge (CM0).
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/02    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetSignalLevelShadow(GTM_OBP_C pAtom, uint8 channel, 
                                                                                 Gtm_SignalState activeState);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetSignalLevel
 * Description:  Gets the signal level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 * Inout:        None
 * Output:       None
 * Return:       Gtm_SignalState: Signal level active state. In case the channel is reset, the output is set to
 *                                not active.
 *                                The signal is active between 0 and the leading edge (CM1) and inactive between the
 *                                leading edge and the trailing edge (CM0).
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE Gtm_SignalState Gtm_Atom_Std_GetSignalLevel(GTM_C_OBP_C pAtom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetTriggerOutput
 * Description:  Sets the channel trigger output
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               trigger: Channel trigger output mode (0~1)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetTriggerOutput(GTM_OBP_C pAtom, uint8 channel, uint8 trigger);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetChannelFreeze
 * Description:  Enable/disable channel freeze
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               enable: Enable/ Disable choice of the feature
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetChannelFreeze(GTM_OBP_C pAtom, uint8 channel, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetChannelMode
 * Description:  Sets the Atom operating mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               mode: Atom operating mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetChannelMode(GTM_OBP_C pAtom, uint8 channel, Gtm_Atom_Mode mode);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetSomcSignalLevelControl
 * Description:  sets the SL control for SOMC mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               ctrl: Signal level control, can be a value of Gtm_SomcSLCtrl (0~3)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetSomcSignalLevelControl(GTM_OBP_C pAtom, uint8 channel, uint8 ctrl);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetSomcControl
 * Description:  Sets the SOMC control bits for the specified ATOM channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               control: SOMC compare strategy
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetSomcControl(GTM_OBP_C pAtom, uint8 channel, Gtm_SomcCtrl control);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetShadowZero
 * Description:  Gets the compare zero shadow value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Compare zero shadow value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Atom_Std_GetShadowZero(GTM_C_OBP_C pAtom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetShadowOne
 * Description:  Gets the compare one shadow value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Compare one shadow value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Atom_Std_GetShadowOne(GTM_C_OBP_C pAtom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetTimeBase
 * Description:  Sets the time base for channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               timeBase: TBU_TS0/1 select
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetTimeBase(GTM_OBP_C pAtom, uint8 channel, Gtm_Atom_TimeBase timeBase);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetAtomPointer
 * Description:  Gets the ATOM pointer
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        atomIndex: Atom index
 * Inout:        None
 * Output:       None
 * Return:       GTM_OBP: Pointer to the ATOM object
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE GTM_OBP Gtm_Atom_Std_GetAtomPointer(uint8 atomIndex);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetCompareZero
 * Description:  Gets compare zero value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        atomIndex: Atom index
 *               channel: Channel index (0~7)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Compare zero value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Atom_Std_GetCompareZero(GTM_C_OBP_C pAtom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetCompareZeroOne
 * Description:  Sets the compare zero and compare one value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               cm0: Compare zero value (the maximum value is 0xFFFFFF)
 *               cm1: Compare one value (the maximum value is 0xFFFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCompareZeroOne(GTM_OBP_C pAtom, uint8 channel, uint32 cm0, uint32 cm1);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetCompareZeroOneShadow
 * Description:  Sets the compare zero and compare one shadow value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               sr0: Compare zero shadow value (the maximum value is 0xFFFFFF)
 *               sr1: Compare one shadow value (the maximum value is 0xFFFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCompareZeroOneShadow(GTM_OBP_C pAtom, uint8 channel, uint32 sr0, uint32 sr1);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetCountMode
 * Description:  Sets counter counts mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               mode: Count mode (0~3)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/04/24    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCountMode(GTM_OBP_C pAtom, uint8 channel, uint32 mode);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetHostTrig
 * Description:  Sets host trigger
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAgc: Pointer to the AGC object
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/25    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Gtm_Atom_Std_SetHostTrig(GTM_OBP_C pAgc);

/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetClockSource(GTM_OBP_C pAtom, uint8 channel, uint8 clk)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.CLK_SRC = (uint32)clk;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)clk, ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.CLK_SRC);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetClockSourceShadow(GTM_OBP_C pAtom, uint8 channel, uint8 clk)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].CTRL_SR.B.CLK_SRC_SR = (uint32)clk;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)clk, ((GTM_ATOM_t *)pAtom)->CH[channel].CTRL_SR.B.CLK_SRC_SR);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCompareOne(GTM_OBP_C pAtom, uint8 channel, uint32 compareOne)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].CM1.U = compareOne;
    ret = Gtm_Register_ReadBack_Check(ret, compareOne, ((GTM_ATOM_t *)pAtom)->CH[channel].CM1.U);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetShadowOne(GTM_OBP_C pAtom, uint8 channel, uint32 shadowOne)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].SR1.U = shadowOne;
    ret = Gtm_Register_ReadBack_Check(ret, shadowOne, ((GTM_ATOM_t *)pAtom)->CH[channel].SR1.U);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCompareZero(GTM_OBP_C pAtom, uint8 channel, uint32 compareZero)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].CM0.U = compareZero;
    ret = Gtm_Register_ReadBack_Check(ret, compareZero, ((GTM_ATOM_t *)pAtom)->CH[channel].CM0.U);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetShadowZero(GTM_OBP_C pAtom, uint8 channel, uint32 shadowZero)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].SR0.U = shadowZero;
    ret = Gtm_Register_ReadBack_Check(ret, shadowZero, ((GTM_ATOM_t *)pAtom)->CH[channel].SR0.U);

    return ret;
}

LOCAL_FORCEINLINE void Gtm_Atom_Std_SetCounterValue(GTM_OBP_C pAtom, uint8 channel, uint32 value)
{
    /* #Violation: gtm_atom_std_h_REF_3 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].CN0.B.CN0 = value;
}

LOCAL_FORCEINLINE uint32 Gtm_Atom_Std_GetCounterValue(GTM_C_OBP_C pAtom, uint8 channel)
{
    /* #Violation: gtm_atom_std_h_REF_3 */
    return ((const GTM_ATOM_t *)pAtom)->CH[channel].CN0.B.CN0;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCounterRstSrc(GTM_OBP_C pAtom, uint8 channel, uint8 event)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.RST_CCU0 = (uint32)event;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)event, ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.RST_CCU0);

    return ret;
}

LOCAL_FORCEINLINE uint8 Gtm_Atom_Std_GetCounterRstSrc(GTM_C_OBP_C pAtom, uint8 channel)
{
    /* #Violation: gtm_atom_std_h_REF_2 */
    return ((const GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.RST_CCU0;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetSignalLevel(GTM_OBP_C pAtom, uint8 channel, Gtm_SignalState activeState)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.SL = (uint32)activeState;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)activeState, ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.SL);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetSignalLevelShadow(GTM_OBP_C pAtom, uint8 channel, 
                                                                                 Gtm_SignalState activeState)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].CTRL_SR.B.SL_SR = (uint32)activeState;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)activeState, ((GTM_ATOM_t *)pAtom)->CH[channel].CTRL_SR.B.SL_SR);

    return ret;
}

LOCAL_FORCEINLINE Gtm_SignalState Gtm_Atom_Std_GetSignalLevel(GTM_C_OBP_C pAtom, uint8 channel)
{
    Gtm_SignalState ret;

    if (1U == ((const GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.SL)
    {
        ret = GTM_SIGNALSTATE_HIGH;
    }
    else
    {
        ret = GTM_SIGNALSTATE_LOW;
    }
    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetTriggerOutput(GTM_OBP_C pAtom, uint8 channel, uint8 trigger)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.TRIGOUT = (uint32)trigger;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)trigger, ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.TRIGOUT);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetChannelFreeze(GTM_OBP_C pAtom, uint8 channel, boolean enable)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.FREEZE = (uint32)enable;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)enable, ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.FREEZE);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetChannelMode(GTM_OBP_C pAtom, uint8 channel, Gtm_Atom_Mode mode)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.MODE = (uint32)mode;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)mode, ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.MODE);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetSomcSignalLevelControl(GTM_OBP_C pAtom, uint8 channel, uint8 ctrl)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.SOMC.B.ACB10 = ctrl;
    ret = Gtm_Register_ReadBack_Check(ret, ctrl, ((GTM_ATOM_t *)pAtom)->CH[channel].AC.SOMC.B.ACB10);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetSomcControl(GTM_OBP_C pAtom, uint8 channel, Gtm_SomcCtrl control)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.SOMC.B.ACB42 = (uint32)control;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)control, ((GTM_ATOM_t *)pAtom)->CH[channel].AC.SOMC.B.ACB42);

    return ret;
}

LOCAL_FORCEINLINE uint32 Gtm_Atom_Std_GetShadowZero(GTM_C_OBP_C pAtom, uint8 channel)
{
    /* #Violation: gtm_atom_std_h_REF_2 */
    return ((const GTM_ATOM_t *)pAtom)->CH[channel].SR0.B.SR0;
}

LOCAL_FORCEINLINE uint32 Gtm_Atom_Std_GetShadowOne(GTM_C_OBP_C pAtom, uint8 channel)
{
    /* #Violation: gtm_atom_std_h_REF_2 */
    return ((const GTM_ATOM_t *)pAtom)->CH[channel].SR1.B.SR1;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetTimeBase(GTM_OBP_C pAtom, uint8 channel, Gtm_Atom_TimeBase timeBase)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.TB12_SEL = (uint32)timeBase;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)timeBase, ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.TB12_SEL);

    return ret;
}

LOCAL_FORCEINLINE GTM_OBP Gtm_Atom_Std_GetAtomPointer(uint8 atomIndex)
{
    /* #Violation: gtm_atom_std_h_REF_4 */
    /* #Violation: gtm_atom_std_h_REF_5 */
    return (GTM_OBP)&GTM_HAL->GTM_CLUSTER[atomIndex].ATOM;
}

LOCAL_FORCEINLINE uint32 Gtm_Atom_Std_GetCompareZero(GTM_C_OBP_C pAtom, uint8 channel)
{
    /* #Violation: gtm_atom_std_h_REF_2 */
    return ((const GTM_ATOM_t *)pAtom)->CH[channel].CM0.B.CM0;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCompareZeroOne(GTM_OBP_C pAtom, uint8 channel, uint32 cm0, uint32 cm1)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].CM1.B.CM1 = cm1;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].CM0.B.CM0 = cm0;

    ret = Gtm_Register_ReadBack_Check(ret, cm1, ((GTM_ATOM_t *)pAtom)->CH[channel].CM1.B.CM1);
    ret = Gtm_Register_ReadBack_Check(ret, cm0, ((GTM_ATOM_t *)pAtom)->CH[channel].CM0.B.CM0);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCompareZeroOneShadow(GTM_OBP_C pAtom, uint8 channel, uint32 sr0, uint32 sr1)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].SR1.B.SR1 = sr1;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].SR0.B.SR0 = sr0;

    ret = Gtm_Register_ReadBack_Check(ret, sr1, ((GTM_ATOM_t *)pAtom)->CH[channel].SR1.B.SR1);
    ret = Gtm_Register_ReadBack_Check(ret, sr0, ((GTM_ATOM_t *)pAtom)->CH[channel].SR0.B.SR0);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Atom_Std_SetCountMode(GTM_OBP_C pAtom, uint8 channel, uint32 mode)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_atom_std_h_REF_2 */
    ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.UDMODE = (mode & 0x3U);

    ret = Gtm_Register_ReadBack_Check(ret, (mode&0x3U), ((GTM_ATOM_t *)pAtom)->CH[channel].AC.CTRL.B.UDMODE);

    return ret;
}

LOCAL_FORCEINLINE void Gtm_Atom_Std_SetHostTrig(GTM_OBP_C pAgc)
{
    ((GTM_ATOM_AGC *)pAgc)->GLB_CTRL.B.HOST_TRIG = 1U;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_ClearInterruptStatus
 * Description:  Clears the channel interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               irq: Interrupt types (1~3)
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/08/29    01031      Cancel the bitfield operation
 *********************************************************************************************************************/
extern void Gtm_Atom_Std_ClearInterruptStatus(GTM_OBP_C pAtom, uint8 channel, uint8 irq);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetOutputLevel
 * Description:  Gets the ATOM output level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 * Inout:        None
 * Output:       None
 * Return:       Gtm_SignalState: Output signal level
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern Gtm_SignalState Gtm_Atom_Std_GetOutputLevel(GTM_C_OBP_C pAtom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetInterruptstatus
 * Description:  Gets the status of channel interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               irq: Interrupt types (1~3)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt status. If gets all status, bit 0: CCU0TC, bit 1: CCU1TC
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/08/29    01031      Cancel the bitfield operation
 *********************************************************************************************************************/
extern uint32 Gtm_Atom_Std_GetInterruptStatus(GTM_C_OBP_C pAtom, uint8 channel, uint8 irq);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetInterruptEnableStatus
 * Description:  Gets the status of channel interrupt enable status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               irq: Interrupt types (1~3)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt enable status. If gets all status, bit 0: CCU0TC, bit 1: CCU1TC
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/25    01177      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Atom_Std_GetInterruptEnableStatus(GTM_C_OBP_C pAtom, uint8 channel, uint8 irq);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetInterrupt
 * Description:  Enable / disable the channel specific / all interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               irq: Interrupt types
 *               enable: Enable / disable
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Atom_Std_SetInterrupt(GTM_OBP_C pAtom, uint8 channel, uint8 irq, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetInterruptMode
 * Description:  Sets the channel interrupt mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 *               mode: Interrupt mode
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Atom_Std_SetInterruptMode(GTM_OBP_C pAtom, uint8 channel, Gtm_IrqMode mode);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetChannel
 * Description:  Enable/disable one channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAgc: Pointer to the AGC object
 *               channel: Channel index (0~7)
 *               enable: Enable/ Disable choice of the feature
 *               immediate: If TRUE, the action is done immediately else the action is done on AGC trigger
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Atom_Std_SetChannel(GTM_OBP_C pAgc, uint8 channel, boolean enable, boolean immediate);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetChannelOutput
 * Description:  Enable/disable one channel output
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAgc: Pointer to the AGC object
 *               channel: Channel index (0~7)
 *               enable: Enable/ Disable choice of the feature
 *               immediate: If TRUE, the action is done immediately else, the action is done on AGC trigger
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Atom_Std_SetChannelOutput(GTM_OBP_C pAgc, uint8 channel, boolean enable, boolean immediate);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetChannelUpdate
 * Description:  Enable/disable one channel for update
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAgc: Pointer to the AGC object
 *               channel: Channel index (0~7)
 *               enable: Enable/ Disable choice of the feature
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Atom_Std_SetChannelUpdate(GTM_OBP_C pAgc, uint8 channel, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_ResetChannel
 * Description:  Reset ATOM channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAgc: Pointer to the AGC object
 *               channel: Channel index (0~7)
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/12/11    01177      Create
 *********************************************************************************************************************/
extern void Gtm_Atom_Std_ResetChannel(GTM_OBP_C pAgc, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetChannelsOutput
 * Description:  Enable/disable one or more channels output
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAgc: Pointer to the AGC object
 *               mask: Mask for the channel feature enable (bit[7:0]) / disable (bit[15:8])
 *               immediate: If TRUE, the action is done immediately else, the action is done on AGC trigger
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Atom_Std_SetChannelsOutput(GTM_OBP_C pAgc, uint16 mask, boolean immediate);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_GetAgcPointer
 * Description:  Gets the ATOM AGC pointer
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAtom: Pointer to the ATOM object
 *               channel: Channel index (0~7)
 * Inout:        None
 * Output:       None
 * Return:       GTM_OBP: Pointer to the ATOM AGC object
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/22    01177      Create
 *********************************************************************************************************************/
extern GTM_OBP Gtm_Atom_Std_GetAgcPointer(GTM_OBP_C pAtom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Atom_Std_SetForceUpdate
 * Description:  Sets force update for the channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pAgc: Pointer to the AGC object
 *               channel: Channel index (0~7)
 *               enable: Enable / disable force update
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/25    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Atom_Std_SetForceUpdate(GTM_OBP_C pAgc, uint8 channel, boolean enable);

/* #Violation: gtm_atom_std_h_REF_7 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_atom_std_h_REF_6 */
#include "Gtm_MemMap.h"
#endif /* GTM_ATOM_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

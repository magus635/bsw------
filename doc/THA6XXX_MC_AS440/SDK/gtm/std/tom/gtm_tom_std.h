/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_tom_std.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations for all the internal
 *                 functions of the TOM module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
*#gtm_tom_std_h_REF_1:MISRAC2012-Rule-2.3;
* Justification: The members of the type are used in configuration-gererated code.
*
*#gtm_tom_std_h_REF_2:MISRAC2012-Rule-11.5;
* Justification: Type conversions do not result in errors.
*
*#gtm_tom_std_h_3:MISRAC2012-Rule-10.5;
* Justification: Limitation of Cortex-R52+ Core. Boolean can only be representes as uint8.
*
*#gtm_tom_std_h_REF_4:MISRAC2012-Dir-1.1;
* Justification: Necessary type casting for memory and/or register accessing.
*
*#gtm_tom_std_h_REF_5:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
* #gtm_tom_std_h_REF_6:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_tom_std_h_REF_7:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef GTM_TOM_STD_H_
#define GTM_TOM_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm.h"
#include "gtm_register.h"
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
/* Clock source for the TOM channels */
typedef enum
{
    GTM_TOM_CH_CLKSRC_CMUFXCLK0 = 0U,  /* Fixed clock div 1 */
    GTM_TOM_CH_CLKSRC_CMUFXCLK1 = 1U,  /* Fixed clock div 16 */
    GTM_TOM_CH_CLKSRC_CMUFXCLK2 = 2U,  /* Fixed clock div 256 */
    GTM_TOM_CH_CLKSRC_CMUFXCLK3 = 3U,  /* Fixed clock div 4096 */
    GTM_TOM_CH_CLKSRC_CMUFXCLK4 = 4U,  /* Fixed clock div 65536 */
    GTM_TOM_CH_CLKSRC_NOCLOCK   = 5U,  /* No clock */
    GTM_TOM_CH_CLKSRC_STOP      = 12U, /* Functional operation stopped, clock resolution tied to zero */
    GTM_TOM_CH_CLKSRC_TRIGOUT   = 13U, /* TOM_CH_TRIGOUT x-1:x-1 */
    GTM_TOM_CH_CLKSRC_EXTTRIGIN = 14U  /* TOM_EXT_TRIGIN x:x  */
} Gtm_Tom_Ch_ClkSrc;

/* TOM channel trigger output signal */
typedef enum
{
    GTM_TOM_CH_TRIGOUT_FORWARD  = 0U, /* Forward the trigger from the previous channel */
    GTM_TOM_CH_TRIGOUT_GENERATE       /* Generate the trigger from the current channel */
} Gtm_Tom_Ch_TrigOut;

/* Reset event for channel counter CN0 */
typedef enum
{
    GTM_TOM_CH_RSTEVT_ONCM0     = 0U,   /* Reset counter register CN0 on matching comparison with CM0 */
    GTM_TOM_CH_RSTEVT_ONTRIGGER         /* Reset counter register CN0 on trigger */
/* #Violation: gtm_tom_std_h_REF_1 */
} Gtm_Tom_Ch_RstEvt;

/* TOM interrupt type */
typedef enum
{
    GTM_TOM_IRQTYPE_NONE = GTM_OM_IRQTYPE_NONE,    /* None interrupt */
    GTM_TOM_IRQTYPE_CCU0 = GTM_OM_IRQTYPE_CCU0,    /* CCU0 trigger condition interrupt for channel [x] */
    GTM_TOM_IRQTYPE_CCU1 = GTM_OM_IRQTYPE_CCU1,    /* CCU1 trigger condition interrupt for channel [x] */
    GTM_TOM_IRQTYPE_ALL  = GTM_OM_IRQTYPE_ALL      /* All interrupt */
/* #Violation: gtm_tom_std_h_REF_1 */
} Gtm_Tom_IrqType;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: gtm_tom_std_h_REF_7 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tom_std_h_REF_6 */
#include "Gtm_MemMap.h"

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetClockSource
 * Description:  Sets the channel clock source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
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
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetClockSource(GTM_OBP_C pTom, uint8 channel, uint8 clk);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetClockSourceShadow
 * Description:  Sets the channel shadow clock source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
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
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetClockSourceShadow(GTM_OBP_C pTom, uint8 channel, uint8 clk);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetCompareOne
 * Description:  Sets the compare one value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               compareOne: Compare one value (the maximum value is 0xFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCompareOne(GTM_OBP_C pTom, uint8 channel, uint32 compareOne);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetShadowOne
 * Description:  Sets the compare one shadow value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               shadowOne: Compare one shadow value (the maximum value is 0xFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetShadowOne(GTM_OBP_C pTom, uint8 channel, uint32 shadowOne);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetCompareZero
 * Description:  Sets the compare zero value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               compareZero: Compare zero value (the maximum value is 0xFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCompareZero(GTM_OBP_C pTom, uint8 channel, uint32 compareZero);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetShadowZero
 * Description:  Sets the compare zero shadow value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               shadowZero: Compare zero shadow value (the maximum value is 0xFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetShadowZero(GTM_OBP_C pTom, uint8 channel, uint32 shadowZero);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetCounterValue
 * Description:  Sets the counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               value:Counter value (the maximum value is 0xFFFF)
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Gtm_Tom_Std_SetCounterValue(GTM_OBP_C pTom, uint8 channel, uint32 value);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetCounterValue
 * Description:  Gets the counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Tom_Std_GetCounterValue(GTM_C_OBP_C pTom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetOneShotMode
 * Description:  Enable/disable the one shot mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
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
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetOneShotMode(GTM_OBP_C pTom, uint8 channel, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetOneShotMode
 * Description:  Get the one shot mode enable status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 * Inout:        None
 * Output:       boolean: If the channel is OneShotMode
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_GetOneShotMode(GTM_C_OBP_C pTom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetCounterRstSrc
 * Description:  Sets the channel counter reset source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
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
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCounterRstSrc(GTM_OBP_C pTom, uint8 channel, uint8 event);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetCounterRstSrc
 * Description:  Gets the channel counter reset source
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 * Inout:        None
 * Output:       None
 * Return:       uint8: 0: counter reset on CN0 match comparison with CM0
 *                      1: counter reset on trigger
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/11/22    01177      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint8 Gtm_Tom_Std_GetCounterRstSrc(GTM_C_OBP_C pTom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetSignalLevel
 * Description:  Sets the signal level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               activeState: Signal level active state. In case the channel is reset, the output is set to not active.
 *                             The signal is active between 0 and the leading edge (CM1) and inactive between the
 *                             leading edge and the trailing edge (CM0).
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetSignalLevel(GTM_OBP_C pTom, uint8 channel, Gtm_SignalState activeState);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetSignalLevelShadow
 * Description:  Sets the shadow signal level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               activeState: Signal level active state. In case the channel is reset, the output is set to not active.
 *                             The signal is active between 0 and the leading edge (CM1) and inactive between the
 *                             leading edge and the trailing edge (CM0).
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/02    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetSignalLevelShadow(GTM_OBP_C pTom, uint8 channel, Gtm_SignalState activeState);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetSignalLevel
 * Description:  Gets the signal level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
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
LOCAL_FORCEINLINE Gtm_SignalState Gtm_Tom_Std_GetSignalLevel(GTM_C_OBP_C pTom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetTriggerOutput
 * Description:  Sets the channel trigger output
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
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
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetTriggerOutput(GTM_OBP_C pTom, uint8 channel, uint8 trigger);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetChannelFreeze
 * Description:  Enable/disable channel freeze
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
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
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetChannelFreeze(GTM_OBP_C pTom, uint8 channel, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetTomPointer
 * Description:  Gets the TOM pointer
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        tomIndex: Tom index
 * Inout:        None
 * Output:       None
 * Return:       GTM_TOM_t *: Pointer to the TOM object
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE GTM_OBP Gtm_Tom_Std_GetTomPointer(uint8 tomIndex);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetCompareZero
 * Description:  Gets the compare zero value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Compare zero value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE uint32 Gtm_Tom_Std_GetCompareZero(GTM_C_OBP_C pTom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetCompareZeroOne
 * Description:  Sets the compare zero and compare one value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               cm0: Compare zero value (the maximum value is 0xFFFF)
 *               cm1: Compare one value (the maximum value is 0xFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCompareZeroOne(GTM_OBP_C pTom, uint8 channel, uint32 cm0, uint32 cm1);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetCompareZeroOneShadow
 * Description:  Sets the compare zero and compare one shadow value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               sr0: Compare zero shadow value (the maximum value is 0xFFFF)
 *               sr1: Compare one shadow value (the maximum value is 0xFFFF)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCompareZeroOneShadow(GTM_OBP_C pTom, uint8 channel, uint32 sr0, uint32 sr1);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetCountMode
 * Description:  Sets counter counts mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
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
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCountMode(GTM_OBP_C pTom, uint8 channel, uint32 mode);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetHostTrig
 * Description:  Sets host trigger
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTgc: Pointer to the TGC object
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/06/25    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Gtm_Tom_Std_SetHostTrig(GTM_OBP_C pTgc);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetClockSource(GTM_OBP_C pTom, uint8 channel, uint8 clk)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.CLK_SRC = (uint32)clk;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)clk, ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.CLK_SRC);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetClockSourceShadow(GTM_OBP_C pTom, uint8 channel, uint8 clk)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CTRL_SR.B.CLK_SRC_SR = (uint32)clk;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)clk, ((GTM_TOM_t *)pTom)->CH[channel].CTRL_SR.B.CLK_SRC_SR);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCompareOne(GTM_OBP_C pTom, uint8 channel, uint32 compareOne)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CM1.U = compareOne;
    ret = Gtm_Register_ReadBack_Check(ret, compareOne, ((GTM_TOM_t *)pTom)->CH[channel].CM1.U);

    return ret;
}


LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetShadowOne(GTM_OBP_C pTom, uint8 channel, uint32 shadowOne)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].SR1.U = shadowOne;
    ret = Gtm_Register_ReadBack_Check(ret, shadowOne, ((GTM_TOM_t *)pTom)->CH[channel].SR1.U);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCompareZero(GTM_OBP_C pTom, uint8 channel, uint32 compareZero)
{
    boolean ret;
    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CM0.U = compareZero;
    ret = Gtm_Register_ReadBack_Check(ret, compareZero, ((GTM_TOM_t *)pTom)->CH[channel].CM0.U);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetShadowZero(GTM_OBP_C pTom, uint8 channel, uint32 shadowZero)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].SR0.U = shadowZero;
    ret = Gtm_Register_ReadBack_Check(ret, shadowZero, ((GTM_TOM_t *)pTom)->CH[channel].SR0.U);

    return ret;
}


LOCAL_FORCEINLINE void Gtm_Tom_Std_SetCounterValue(GTM_OBP_C pTom, uint8 channel, uint32 value)
{
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CN0.B.CN0 = value;
}

LOCAL_FORCEINLINE uint32 Gtm_Tom_Std_GetCounterValue(GTM_C_OBP_C pTom, uint8 channel)
{
    /* #Violation: gtm_tom_std_h_REF_2 */
    return ((const GTM_TOM_t *)pTom)->CH[channel].CN0.B.CN0;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetOneShotMode(GTM_OBP_C pTom, uint8 channel, boolean enable)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.OSM = (uint32)enable;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)enable, ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.OSM);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_GetOneShotMode(GTM_C_OBP_C pTom, uint8 channel)
{
    /* #Violation: gtm_tom_std_h_REF_2 */
    return (boolean)((const GTM_TOM_t *)pTom)->CH[channel].CTRL.B.OSM;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCounterRstSrc(GTM_OBP_C pTom, uint8 channel, uint8 event)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.RST_CCU0 = event;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)event, ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.RST_CCU0);

    return ret;
}

LOCAL_FORCEINLINE uint8 Gtm_Tom_Std_GetCounterRstSrc(GTM_C_OBP_C pTom, uint8 channel)
{
    /* #Violation: gtm_tom_std_h_REF_2 */
    return ((const GTM_TOM_t *)pTom)->CH[channel].CTRL.B.RST_CCU0;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetSignalLevel(GTM_OBP_C pTom, uint8 channel, Gtm_SignalState activeState)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.SL = (uint32)activeState;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)activeState, ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.SL);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetSignalLevelShadow(GTM_OBP_C pTom, uint8 channel, Gtm_SignalState activeState)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CTRL_SR.B.SL_SR = (uint32)activeState;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)activeState, ((GTM_TOM_t *)pTom)->CH[channel].CTRL_SR.B.SL_SR);

    return ret;
}

LOCAL_FORCEINLINE Gtm_SignalState Gtm_Tom_Std_GetSignalLevel(GTM_C_OBP_C pTom, uint8 channel)
{
    Gtm_SignalState ret;

    if (1U == ((const GTM_TOM_t *)pTom)->CH[channel].CTRL.B.SL)
    {
        ret = GTM_SIGNALSTATE_HIGH;
    }
    else
    {
        ret = GTM_SIGNALSTATE_LOW;
    }
    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetTriggerOutput(GTM_OBP_C pTom, uint8 channel, uint8 trigger)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.TRIGOUT = trigger;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)trigger, ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.TRIGOUT);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetChannelFreeze(GTM_OBP_C pTom, uint8 channel, boolean enable)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.FREEZE = (uint32)enable;
    ret = Gtm_Register_ReadBack_Check(ret, (uint32)enable, ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.FREEZE);

    return ret;
}

LOCAL_FORCEINLINE GTM_OBP Gtm_Tom_Std_GetTomPointer(uint8 tomIndex)
{
    /* #Violation: gtm_tom_std_h_REF_4 */
    /* #Violation: gtm_tom_std_h_REF_5 */
    return (GTM_OBP)&GTM_HAL->GTM_CLUSTER[tomIndex].TOM;
}

LOCAL_FORCEINLINE uint32 Gtm_Tom_Std_GetCompareZero(GTM_C_OBP_C pTom, uint8 channel)
{
    /* #Violation: gtm_tom_std_h_REF_2 */
    return ((const GTM_TOM_t *)pTom)->CH[channel].CM0.B.CM0;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCompareZeroOne(GTM_OBP_C pTom, uint8 channel, uint32 cm0, uint32 cm1)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CM1.B.CM1 = cm1;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CM0.B.CM0 = cm0;

    ret = Gtm_Register_ReadBack_Check(ret, cm1, ((GTM_TOM_t *)pTom)->CH[channel].CM1.B.CM1);
    ret = Gtm_Register_ReadBack_Check(ret, cm0, ((GTM_TOM_t *)pTom)->CH[channel].CM0.B.CM0);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCompareZeroOneShadow(GTM_OBP_C pTom, uint8 channel, uint32 sr0, uint32 sr1)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].SR1.B.SR1 = sr1;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].SR0.B.SR0 = sr0;

    ret = Gtm_Register_ReadBack_Check(ret, sr1, ((GTM_TOM_t *)pTom)->CH[channel].SR1.B.SR1);
    ret = Gtm_Register_ReadBack_Check(ret, sr0, ((GTM_TOM_t *)pTom)->CH[channel].SR0.B.SR0);

    return ret;
}

LOCAL_FORCEINLINE boolean Gtm_Tom_Std_SetCountMode(GTM_OBP_C pTom, uint8 channel, uint32 mode)
{
    boolean ret;

    ret = TRUE;
    /* #Violation: gtm_tom_std_h_REF_2 */
    ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.UDMODE = (mode & 0x3U);

    ret = Gtm_Register_ReadBack_Check(ret, (mode&0x3U), ((GTM_TOM_t *)pTom)->CH[channel].CTRL.B.UDMODE);

    return ret;
}

LOCAL_FORCEINLINE void Gtm_Tom_Std_SetHostTrig(GTM_OBP_C pTgc)
{
    ((GTM_TOM_TGC *)pTgc)->GLB_CTRL.B.HOST_TRIG = 1U;
}

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_ClearInterruptStatus
 * Description:  Clears the channel interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               irq: Interrupt types (1~3)
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031     Create
 *  2023/08/29    01031     Cancel the bitfield operation
 *********************************************************************************************************************/
extern void Gtm_Tom_Std_ClearInterruptStatus(GTM_OBP_C pTom, uint8 channel, uint8 irq);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetOutputLevel
 * Description:  Gets the TOM output level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 * Inout:        None
 * Output:       None
 * Return:       Gtm_SignalState: Output signal level
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern Gtm_SignalState Gtm_Tom_Std_GetOutputLevel(GTM_C_OBP_C pTom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetTgcPointer
 * Description:  Gets the TOM TGC pointer
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 * Inout:        None
 * Output:       None
 * Return:       GTM_TOM_TGC *: Pointer to the TOM TGC object
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern GTM_OBP Gtm_Tom_Std_GetTgcPointer(GTM_OBP_C pTom, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetInterruptStatus
 * Description:  Gets the status of channel interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               irq: Interrupt types (1~3)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt status. If gets all status, bit 0: CCU0TC, bit 1: CCU1TC
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Tom_Std_GetInterruptStatus(GTM_C_OBP_C pTom, uint8 channel, uint8 irq);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_GetInterruptEnableStatus
 * Description:  Gets the status of channel interrupt enable status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               irq: Interrupt types (1~3)
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt enable status. If gets all status, bit 0: CCU0TC, bit 1: CCU1TC
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/25    01177      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Tom_Std_GetInterruptEnableStatus(GTM_C_OBP_C pTom, uint8 channel, uint8 irq);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetInterrupt
 * Description:  Enable / disable the channel specific / all interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
 *               irq: Interrupt types (1~3)
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
extern boolean Gtm_Tom_Std_SetInterrupt(GTM_OBP_C pTom, uint8 channel, uint8 irq, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetInterruptMode
 * Description:  Sets the channel interrupt mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTom: Pointer to the TOM object
 *               channel: Channel index (0~15)
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
extern boolean Gtm_Tom_Std_SetInterruptMode(GTM_OBP_C pTom, uint8 channel, Gtm_IrqMode mode);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetChannel
 * Description:  Enable/disable one channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTgc: Pointer to the TGC object
 *               channel: Channel index (0~15)
 *               enable: Enable/ Disable choice of the feature
 *               immediate: If TRUE, the action is done immediately else the action is done on TGC trigger
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Tom_Std_SetChannel(GTM_OBP_C pTgc, uint8 channel, boolean enable, boolean immediate);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetChannelOutput
 * Description:  Enable/disable one channel output
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTgc: Pointer to the TGC object
 *               channel: Channel index (0~15)
 *               enable: Enable/ Disable choice of the feature
 *               immediate: If TRUE, the action is done immediately else, the action is done on TGC trigger
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Tom_Std_SetChannelOutput(GTM_OBP_C pTgc, uint8 channel, boolean enable, boolean immediate);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetChannelUpdate
 * Description:  Enable/disable one channel for update
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTgc: Pointer to the TGC object
 *               channel: Channel index (0~15)
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
extern boolean Gtm_Tom_Std_SetChannelUpdate(GTM_OBP_C pTgc, uint8 channel, boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_ResetChannel
 * Description:  Reset TOM channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTgc: Pointer to the TGC object
 *               channel: Channel index (0~15)
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern void Gtm_Tom_Std_ResetChannel(GTM_OBP_C pTgc, uint8 channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetChannelsOutput
 * Description:  Enable/disable one or more channels output
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTgc: Pointer to the TGC object
 *               mask: Mask for the channel feature enable (bit[7:0]) / disable (bit[15:8])
 *               immediate: If TRUE, the action is done immediately else, the action is done on TGC trigger
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/07/17    01031      Modify parameter
 *********************************************************************************************************************/
extern boolean Gtm_Tom_Std_SetChannelsOutput(GTM_OBP_C pTgc, uint16 mask, boolean immediate);

/**********************************************************************************************************************
 * Function:     Gtm_Tom_Std_SetForceUpdate
 * Description:  Sets force update for the channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTgc: Pointer to the TGC object
 *               channel: Channel index (0~15)
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
extern boolean Gtm_Tom_Std_SetForceUpdate(GTM_OBP_C pTgc, uint8 channel, boolean enable);

/* #Violation: gtm_tom_std_h_REF_7 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tom_std_h_REF_6 */
#include "Gtm_MemMap.h"
#endif /* GTM_TOM_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

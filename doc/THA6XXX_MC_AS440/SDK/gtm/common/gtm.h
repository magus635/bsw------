/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
* #gtm_h_REF_1:MISRAC2012-Rule-2.3; 
* Justification:The members of the typ are used in configuration-generated code.
*
* #gtm_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_h_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_h_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef GTM_H_
#define GTM_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "gtm_register.h"
#include "compilertypes.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
#define GTM_REG_CHECK
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* ATOM objects */
typedef enum
{
    GTM_ATOM_INDEX_0 = 0U,  /* ATOM object 0 */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    GTM_ATOM_INDEX_1,       /* ATOM object 1 */
    GTM_ATOM_INDEX_2,       /* ATOM object 2 */
    GTM_ATOM_INDEX_3,       /* ATOM object 3 */
#endif
#if defined(THA6_THA6412)
    GTM_ATOM_INDEX_4,       /* ATOM object 4 */
    GTM_ATOM_INDEX_5,       /* ATOM object 5 */
    GTM_ATOM_INDEX_6,       /* ATOM object 6 */
    GTM_ATOM_INDEX_7,       /* ATOM object 7 */
#endif
/* #Violation: gtm_h_REF_1 */
} Gtm_Atom_Index;

/* ATOM channels */
typedef enum
{
    GTM_ATOM_CH_INDEX_0 = 0U,    /* ATOM channel 0  */
    GTM_ATOM_CH_INDEX_1,         /* ATOM channel 1  */
    GTM_ATOM_CH_INDEX_2,         /* ATOM channel 2  */
    GTM_ATOM_CH_INDEX_3,         /* ATOM channel 3  */
    GTM_ATOM_CH_INDEX_4,         /* ATOM channel 4  */
    GTM_ATOM_CH_INDEX_5,         /* ATOM channel 5  */
    GTM_ATOM_CH_INDEX_6,         /* ATOM channel 6  */
    GTM_ATOM_CH_INDEX_7          /* ATOM channel 7  */
/* #Violation: gtm_h_REF_1 */
} Gtm_Atom_Ch_Index;

/* TIM objects */
typedef enum
{
    GTM_TIM_INDEX_0 = 0U,     /* TIM object 0 */
    GTM_TIM_INDEX_1,          /* TIM object 1 */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    GTM_TIM_INDEX_2,          /* TIM object 2 */
#endif
#if defined(THA6_THA6412)
    GTM_TIM_INDEX_3,          /* TIM object 3 */
    GTM_TIM_INDEX_4,          /* TIM object 4 */
    GTM_TIM_INDEX_5,          /* TIM object 5 */
    GTM_TIM_INDEX_6,          /* TIM object 6 */
    GTM_TIM_INDEX_7,          /* TIM object 7 */
#endif
} Gtm_Tim_Index;

/* TIM channels */
typedef enum
{
    GTM_TIM_CH_INDEX_0 = 0U,    /* TIM channel 0  */
    GTM_TIM_CH_INDEX_1,         /* TIM channel 1  */
    GTM_TIM_CH_INDEX_2,         /* TIM channel 2  */
    GTM_TIM_CH_INDEX_3,         /* TIM channel 3  */
    GTM_TIM_CH_INDEX_4,         /* TIM channel 4  */
    GTM_TIM_CH_INDEX_5,         /* TIM channel 5  */
    GTM_TIM_CH_INDEX_6,         /* TIM channel 6  */
    GTM_TIM_CH_INDEX_7          /* TIM channel 7  */
} Gtm_Tim_Ch_Index;

/* TOM objects */
typedef enum
{
    GTM_TOM_INDEX_0 = 0U,        /* TOM object 0  */
    GTM_TOM_INDEX_1,             /* TOM object 1  */
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    GTM_TOM_INDEX_2,             /* TOM object 2 */
#endif
#if defined(THA6_THA6412)
    GTM_TOM_INDEX_3,             /* TOM object 3  */
    GTM_TOM_INDEX_4,             /* TOM object 4 */
#endif
/* #Violation: gtm_h_REF_1 */
} Gtm_Tom_Index;

/* TOM channels */
typedef enum
{
    GTM_TOM_CH_INDEX_0 = 0U,    /* TOM channel 0  */
    GTM_TOM_CH_INDEX_1,         /* TOM channel 1  */
    GTM_TOM_CH_INDEX_2,         /* TOM channel 2  */
    GTM_TOM_CH_INDEX_3,         /* TOM channel 3  */
    GTM_TOM_CH_INDEX_4,         /* TOM channel 4  */
    GTM_TOM_CH_INDEX_5,         /* TOM channel 5  */
    GTM_TOM_CH_INDEX_6,         /* TOM channel 6  */
    GTM_TOM_CH_INDEX_7,         /* TOM channel 7  */
    GTM_TOM_CH_INDEX_8,         /* TOM channel 8  */
    GTM_TOM_CH_INDEX_9,         /* TOM channel 9  */
    GTM_TOM_CH_INDEX_10,        /* TOM channel 10  */
    GTM_TOM_CH_INDEX_11,        /* TOM channel 11  */
    GTM_TOM_CH_INDEX_12,        /* TOM channel 12  */
    GTM_TOM_CH_INDEX_13,        /* TOM channel 13  */
    GTM_TOM_CH_INDEX_14,        /* TOM channel 14  */
    GTM_TOM_CH_INDEX_15         /* TOM channel 15  */
/* #Violation: gtm_h_REF_1 */
} Gtm_Tom_Ch_Index;

/* GTM interrupt modes */
typedef enum
{
    GTM_IRQMODE_LEVEL       = 0U,   /* Level interrupt mode  */
    GTM_IRQMODE_PULSE,              /* Pulse interrupt mode  */
    GTM_IRQMODE_PULSENOTIFY,        /* Pulse-notify interrupt mode  */
    GTM_IRQMODE_SINGLEPULSE         /* Single-pulse interrupt mode  */
} Gtm_IrqMode;

/* Signal active state definition */
typedef enum
{
    GTM_SIGNALSTATE_LOW  = 0U,       /* The signal is low active */
    GTM_SIGNALSTATE_HIGH             /* The signal is high active */
} Gtm_SignalState;

/* Output Module interrupt types */
typedef enum
{
    GTM_OM_IRQTYPE_NONE = 0U,   /* None interrupt */
    GTM_OM_IRQTYPE_CCU0,        /* CCU0 trigger condition interrupt for channel [x] */
    GTM_OM_IRQTYPE_CCU1,        /* CCU1 trigger condition interrupt for channel [x] */
    GTM_OM_IRQTYPE_ALL          /* All interrupt */
} Gtm_Om_IrqType;

/* The GTM module used by OCU/PWM/TIMER */
typedef enum
{
    GTM_OUTPUT_MODULE_TOM = 0U, /* TOM module  */
    GTM_OUTPUT_MODULE_ATOM,     /* ATOM module */
    GTM_OUTPUT_MODULE_TIO       /* TIO module  */
/* #Violation: gtm_h_REF_1 */
} Gtm_Output_Module;

/* Hardware resources used by OCU/PWM/TIMER */
/* #Violation: gtm_h_REF_2 */
typedef struct
{
    uint8    module;        /* GTM module, can be a value of Gtm_Output_Module */
    uint8    moduleIndex;   /* Module index */
    uint8    group;         /* Group index, only used for TIO module */
    uint8    channel;       /* Channel index */
} Gtm_Output_Driver;

/* GTM Object pointer */
typedef volatile void * GTM_OBP;

/* GTM Object const pointer */
typedef volatile void * const GTM_OBP_C;

/* GTM const Object const pointer */
typedef const volatile void * const GTM_C_OBP_C;

/* GTM const Object pointer */
typedef const volatile void * GTM_C_OBP;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/* #Violation: gtm_h_REF_4 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_h_REF_3 */
#include "Gtm_MemMap.h"
/**********************************************************************************************************************
 * Function:     Gtm_Register_ReadBack_Check
 * Description:  Check register read back value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        state: Indicates whether the register is configured correctly
 *               expect: Expect value
 *               actual: Actual value
 * Inout:        None
 * Output:       None
 * Return:       boolean: Indicates whether the register is configured correctly
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/03/10    01031      Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gtm_Register_ReadBack_Check(boolean state, uint32 expect, uint32 actual);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#if defined(GTM_REG_CHECK)
LOCAL_FORCEINLINE boolean Gtm_Register_ReadBack_Check(boolean state, uint32 expect, uint32 actual)
{
    boolean ret;
    ret = state;
    if (expect != actual)
    {
        ret &= FALSE;
    }
    return ret;
}
#else
LOCAL_FORCEINLINE boolean Gtm_Register_ReadBack_Check(boolean state, uint32 expect, uint32 actual)
{
    (void)state;
    (void)expect;
    (void)actual;
    return state;
}
#endif
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: gtm_h_REF_4 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_h_REF_3 */
#include "Gtm_MemMap.h"
#endif /* GTM_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

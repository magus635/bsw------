/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_icu_hal.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations of the ICU module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_icu_hal_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
* #gtm_icu_hal_h_REF_2:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_icu_hal_h_REF_3:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_icu_hal_h_REF_4:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_icu_hal_h_REF_5:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef GTM_ICU_HAL_H_
#define GTM_ICU_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_cmu_std.h"
#include "gtm_tim_std.h"
#include "gtm_register.h"
#include "gtm.h"
#include "Platform_Types.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/** \brief  interrupt config */
/* New measurement value detected by SMU of channel */
/* #Violation: gtm_icu_hal_h_REF_1 */
#define    GTM_TIM_IRQ_NEWVAL               ((uint32)1U << 0)
/* ECNT counter overflow of channel */
/* #Violation: gtm_icu_hal_h_REF_1 */
#define    GTM_TIM_IRQ_ECNTOVERFLOW         ((uint32)1U << 1)
/* CNT counter overflow of channel */
/* #Violation: gtm_icu_hal_h_REF_1 */
#define    GTM_TIM_IRQ_CNTOVERFLOW          ((uint32)1U << 2)
/* GPR0 and GPR1 data overflow */
/* #Violation: gtm_icu_hal_h_REF_1 */
#define    GTM_TIM_IRQ_GPROVERFLOW          ((uint32)1U << 3)
/* Time out reached for input signal of channel */
/* #Violation: gtm_icu_hal_h_REF_1 */
#define    GTM_TIM_IRQ_TIMEOUTDETECT        ((uint32)1U << 4)
/* A glitch was detected by the TIM filter of channel */
/* #Violation: gtm_icu_hal_h_REF_1 */
#define    GTM_TIM_IRQ_GLITCHDETECT         ((uint32)1U << 5)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* ICU channel mode */
typedef enum
{
    ICU_MODE_SIGNAL_EDGE_DETECT = 0U, /* Edge detect mode */
    ICU_MODE_SIGNAL_MEASUREMENT,      /* Signal measurement mode */
    ICU_MODE_TIMESTAMP,               /* Timestamp mode */
    ICU_MODE_EDGE_COUNTER,            /* Edge counter mode */
    ICU_MODE_UNDEFINE                 /* Undefined mode, can customize attribute values */
} Gtm_Icu_Mode;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* ICU channel interrupt control */
typedef struct
{
    uint8                irq;    /* Interrupt enable control */
    Gtm_IrqMode         mode;     /* Interrupt mode */
} Gtm_Icu_ConfigIrq;

/* TIM filter configuration */
/* #Violation: gtm_icu_hal_h_REF_2 */
/* #Violation: gtm_icu_hal_h_REF_3 */
typedef struct
{
    Gtm_Cmu_Tim_Filter_Clk        clk;                         /* Filter clock */
    Gtm_Tim_FltMode               risingEdgeMode;              /* Filter mode for rising edge */
    Gtm_Tim_FltMode              fallingEdgeMode;             /* Filter mode for falling edge */
    uint32                      risingEdgeFilterTime;        /* Rising edge filter time  in second */
    uint32                      fallingEdgeFilterTime;       /* Falling edge filter time in second */
} Gtm_Icu_ConfigFilter;

/* Hardware resources used by the ICU */
/* #Violation: gtm_icu_hal_h_REF_2 */
/* #Violation: gtm_icu_hal_h_REF_3 */
typedef struct
{
    Gtm_Tim_Index        tim;        /* TIM index */
    Gtm_Tim_Ch_Index    channel;    /* TIM channel index */
} Gtm_Icu_Driver;

/* Seting Items for Undefined mode*/
/* #Violation: gtm_icu_hal_h_REF_2 */
/* #Violation: gtm_icu_hal_h_REF_3 */
typedef struct
{
    Gtm_Tim_Mode          mode;            /* Measurement mode */
    Gtm_Tim_CntsSel       cntsCtrl;        /* Select input of CTNS */
    Gtm_Tim_GprSel        gpr0Ctrl;        /* Select input of GPR0 */
    Gtm_Tim_GprSel        gpr1Ctrl;        /* Select input of GPR1 */
} Gtm_Icu_CtrlMethodSetType;

/* Auxiliary input configuration */
typedef struct
{
    boolean isBigger8;  /* Auxiliary input channel index is bigger than 8 or not */
    boolean isTom;      /* Auxiliary input channel is from tom or not */
    boolean isNegtive;  /* Auxiliary input channel is negtive or not */
} Gtm_Icu_AuxInputConfig;

/* Initialization configuration structure for ICU */
/* #Violation: gtm_icu_hal_h_REF_2 */
/* #Violation: gtm_icu_hal_h_REF_3 */
typedef struct
{
    Gtm_Icu_Mode                icuMode;            /* ICU mode */
    Gtm_Cmu_Clk                 clk;                /* Timer input clock */
    Gtm_Tim_Input               input;              /* Selected input */
    Gtm_Tim_Edge_Cap            edge;               /* Measurement starting edge */
    const Gtm_Icu_ConfigFilter *filter;             /* Filter configuration */
    Gtm_Icu_CtrlMethodSetType  *ctrlMethodSetPtr;   /* Seting Items for Undefined mode*/
    boolean                     isEcntReset;        /* Enables resetting of counter in certain modes */
                                                    /* [1] It only makes sense in ICU_MODE_SIGNAL_MEASUREMENT and  */
                                                    /*     ICU_MODE_UNDEFINE modes. For other modes, this parameter*/
                                                    /*     is set to FALSE internally.                             */
                                                    /* [2] When using ICU_MODE_SIGNAL_MEASUREMENT mode to capture  */
                                                    /*     high(or low) level time, this parameter should be set   */
                                                    /*     to 'TRUE', and then using Gtm_Icu_Hal_GetTimeElapsed()  */
                                                    /*     to get the high(or low) level time. Otherwise this      */
                                                    /*     this parameter should be set to 'FALSE', and then using */
                                                    /*     Gtm_Icu_Hal_GetDutyCycleValues() to get the captured values*/
    Gtm_Icu_ConfigIrq           interrupt;          /* Interrupt control */
    boolean                     isChannelEnable;    /* Channel enable control */
    Gtm_Icu_AuxInputConfig      auxInCfg;           /* Aux input configuration, only for input = GTM_TIM_INPUT_AUX.*/
} Gtm_Icu_Config;

/* ICU Undefined mode result value */
typedef struct
{
    uint32    CNT;    /* CNT register value */
    uint32    CNTS;    /* CNTS register value */
    uint32  ECNT;    /* ECNT register value */
    uint32    GPR0;    /* GPR0 register value */
    uint32    GPR1;    /* GPR1 register value */
} Gtm_Icu_UndefinedResult;

/* ICU duty and period result values */
/* #Violation: gtm_icu_hal_h_REF_2 */
/* #Violation: gtm_icu_hal_h_REF_3 */
typedef struct
{
    uint32 ActiveTime; /* Duty value */
    uint32 PeriodTime; /* Period value */
} Gtm_Icu_DutyCycleResult;

/* CCM TIM AUX Input Source structure */
typedef struct
{
    Gtm_Tim_Index       tim;      /* TIM index */
    Gtm_Tim_Ch_Index    channel;  /* TIM channel index */
    uint8               src;      /* CCM_AUX_IN source of TIM channel */
    uint8               selOutN;  /* Use DTM_OUT[q] or DTM_OUT[q]_N signals as CCM_AUX_IN source of TIM channel*/
} Gtm_TimAux_In;
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
/* #Violation: gtm_icu_hal_h_REF_5 */
#define ICU_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_icu_hal_h_REF_4 */
#include "Icu_MemMap.h"
#else
/* #Violation: gtm_icu_hal_h_REF_5 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_icu_hal_h_REF_4 */
#include "Gtm_MemMap.h"
#endif

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_SetTimSrcInMux
 * Description:  ICU channel auxiliary input selection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        inMux: TIM AUX input source selection
 *                   0:  Select TOM_[i+8] (i=0~7)
 *                   1:  Select TOM_[i] (i=0~7)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/02/18    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Icu_Hal_SetTimSrcInMux(uint8 inMux);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_TimAuxIn
 * Description:  ICU channel auxiliary input selection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pTimAuxIn: The pointer of the TIM AUX input source structure
 *               Select TIM AUX input source (TOM/ATOM/TOM_N/ATOM_N)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/02/18    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Icu_Hal_TimAuxIn(const Gtm_TimAux_In *const pTimAuxIn);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_SetAuxInput
 * Description:  ICU channel auxiliary input selection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 *               pConfig: The pointer of the initialization configuration structure for ICU channel
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2024/02/18    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Icu_Hal_SetAuxInput(const Gtm_Icu_Driver *const pDriver, const Gtm_Icu_Config *const pConfig);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_InitChannel
 * Description:  ICU channel initialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 *               pConfig: The pointer of the initialization configuration structure for ICU channel
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/07/31    01031      The CTRL register assignment sequence is changed
 *********************************************************************************************************************/
extern boolean Gtm_Icu_Hal_InitChannel(const Gtm_Icu_Driver *const pDriver, const Gtm_Icu_Config *const pConfig);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_DeinitChannel
 * Description:  ICU channel deinitialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern void Gtm_Icu_Hal_DeinitChannel(const Gtm_Icu_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_SetCaptureEdge
 * Description:  Sets ICU channel capture edge
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 *                  edge: Capture edge
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Icu_Hal_SetCaptureEdge(const Gtm_Icu_Driver *const pDriver, Gtm_Tim_Edge_Cap edge);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_SetInterrupt
 * Description:  Enable / disable ICU channel interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 *                  irq: Interrupt enable control
 *                  1<<0    GTM_TIM_IRQ_NEWVAL
 *                  1<<1    GTM_TIM_IRQ_ECNTOVERFLOW
 *                  1<<2    GTM_TIM_IRQ_CNTOVERFLOW
 *                  1<<3    GTM_TIM_IRQ_GPROVERFLOW
 *                  1<<4    GTM_TIM_IRQ_TIMEOUTDETECT
 *                  1<<5    GTM_TIM_IRQ_GLITCHDETECT
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
extern boolean Gtm_Icu_Hal_SetInterrupt(const Gtm_Icu_Driver *const pDriver, uint8 irq);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_ResetEdgeCount
 * Description:  Reset ICU channel edge counter
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Counter reset correct
 *                        FALSE: Counter reset incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Icu_Hal_ResetEdgeCount(const Gtm_Icu_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_StartCapture
 * Description:  ICU channel start capture input signal
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 *                  irq: interrupt control
 *                  1<<0    GTM_TIM_IRQ_NEWVAL
 *                  1<<1    GTM_TIM_IRQ_ECNTOVERFLOW
 *                  1<<2    GTM_TIM_IRQ_CNTOVERFLOW
 *                  1<<3    GTM_TIM_IRQ_GPROVERFLOW
 *                  1<<4    GTM_TIM_IRQ_TIMEOUTDETECT
 *                  1<<5    GTM_TIM_IRQ_GLITCHDETECT
 *                  edge: Capture edge
 *                  immediate: Start immediately or start with valid edge
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       This function is called only when the channel is disabled!
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/07/17    01031      The irqCtrl parameter is changed to the structure pointer type
 *  2023/08/01    01031      Parameter type modification
 *********************************************************************************************************************/
extern boolean Gtm_Icu_Hal_StartCapture(const Gtm_Icu_Driver *const pDriver, uint8 irq, 
                                                        Gtm_Tim_Edge_Cap edge, boolean immediate);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_StartEdgeDetect
 * Description:  ICU channel start edge detect for the input signal
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 *               irq: Interrupt control
 *                  1<<0    GTM_TIM_IRQ_NEWVAL
 *                  1<<1    GTM_TIM_IRQ_ECNTOVERFLOW
 *                  1<<2    GTM_TIM_IRQ_CNTOVERFLOW
 *                  1<<3    GTM_TIM_IRQ_GPROVERFLOW
 *                  1<<4    GTM_TIM_IRQ_TIMEOUTDETECT
 *                  1<<5    GTM_TIM_IRQ_GLITCHDETECT
 *               edge: Capture edge
 *               cnt: The number of edges which should be detected before a IRQ is raised
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       This function is called only when the channel is disabled!
 * History:
 *  Date          Author    Modified
 *  2024/04/12    01177     Create
 *********************************************************************************************************************/
extern boolean Gtm_Icu_Hal_StartEdgeDetect(const Gtm_Icu_Driver *const pDriver, uint8 irq, 
                                                Gtm_Tim_Edge_Cap edge, uint32 cnt);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_StopCapture
 * Description:  ICU channel stop capture input signal immediately
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Icu_Hal_StopCapture(const Gtm_Icu_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_GetSignalLevel
 * Description:  Gets current input signal level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        None
 * Output:       None
 * Return:       Gtm_SignalState: Current input signal level
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern Gtm_SignalState Gtm_Icu_Hal_GetSignalLevel(const Gtm_Icu_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_GetTimeStamp
 * Description:  Get time stamp result
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        None
 * Output:       None
 * Return:       uint32: Time stamp
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/25    01177     Create
 *********************************************************************************************************************/
extern uint32 Gtm_Icu_Hal_GetTimeStamp(const Gtm_Icu_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_GetEdgeNums
 * Description:  Get edge number result
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        None
 * Output:       None
 * Return:       uint32: Edge number
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/25    01177     Create
 *********************************************************************************************************************/
extern uint32 Gtm_Icu_Hal_GetEdgeNums(const Gtm_Icu_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_GetTimeElapsed
 * Description:  Get time elapsed result
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        None
 * Output:       None
 * Return:       uint32: Time elapsed
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/25    01177     Create
 *********************************************************************************************************************/
extern uint32 Gtm_Icu_Hal_GetTimeElapsed(const Gtm_Icu_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_GetOverFlowElapsedTime
 * Description:  Get time elapsed result with overflow
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        None
 * Output:       None
 * Return:       uint32: Over flow time elapsed
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/25    01177     Create
 *********************************************************************************************************************/
extern uint32 Gtm_Icu_Hal_GetOverFlowElapsedTime(const Gtm_Icu_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_GetDutyCycleValues
 * Description:  Get duty cycle result
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        dutyCycle: The pointer of the dutycycle
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/25    01177     Create
 *********************************************************************************************************************/
extern void Gtm_Icu_Hal_GetDutyCycleValues(const Gtm_Icu_Driver *const pDriver, 
                                                            Gtm_Icu_DutyCycleResult *const dutyCycle);
/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_GetUndefinedResult
 * Description:  Get undefined mode result
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 * Inout:        result: The pointer of the undefined mode result
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/25    01177     Create
 *********************************************************************************************************************/
extern void Gtm_Icu_Hal_GetUndefinedResult(const Gtm_Icu_Driver *const pDriver, Gtm_Icu_UndefinedResult *const result);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_GetInterruptStatus
 * Description:  Gets specific / all interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 *                  irqType: Interrupt types
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt status
 *                       bit 0: NEWVAL, bit 1: ECNTOFL, bit 2: CNTOFL, bit 3: GPROFL, bit 4: TODET, bit 5: GLITCHDET
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Icu_Hal_GetInterruptStatus(const Gtm_Icu_Driver *const pDriver, Gtm_Tim_IrqType irqType);

/**********************************************************************************************************************
 * Function:     Gtm_Icu_Hal_ClearInterruptStatus
 * Description:  Clears specific / all interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the ICU
 *                  irqType: Interrupt types
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern void Gtm_Icu_Hal_ClearInterruptStatus(const Gtm_Icu_Driver *const pDriver, Gtm_Tim_IrqType irqType);

#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_icu_hal_h_REF_5 */
#define ICU_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_icu_hal_h_REF_4 */
#include "Icu_MemMap.h"
#else
/* #Violation: gtm_icu_hal_h_REF_5 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_icu_hal_h_REF_4 */
#include "Gtm_MemMap.h"
#endif

#endif /* GTM_ICU_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

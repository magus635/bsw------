/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_pwm_hal.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations of the PWM module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_pwm_hal_h_REF_1:MISRAC2012-Rule-2.3;
* Justification: The members of the typ are used in configuration-generated code.
*
* #gtm_pwm_hal_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_pwm_hal_h_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_pwm_hal_h_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
 #ifndef GTM_PWM_HAL_H_
#define GTM_PWM_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_tom_std.h"
#include "gtm_atom_std.h"
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
/* The GTM submodule (A)TOM index */
typedef enum
{
    GTM_PWM_MODULE_INDEX_0 = 0U,       /* PWM module index 0 */
    GTM_PWM_MODULE_INDEX_1,            /* PWM module index 1 */
    GTM_PWM_MODULE_INDEX_2,            /* PWM module index 2 */
    GTM_PWM_MODULE_INDEX_3,            /* PWM module index 3 */
    GTM_PWM_MODULE_INDEX_4,            /* PWM module index 4 */
    GTM_PWM_MODULE_INDEX_5,            /* PWM module index 5 */
    GTM_PWM_MODULE_INDEX_6,            /* PWM module index 6 */
    GTM_PWM_MODULE_INDEX_7             /* PWM module index 7 */
/* #Violation: gtm_pwm_hal_h_REF_1 */
} Gtm_Pwm_Module_Index;

/* The GTM submodule channel index */
typedef enum
{
    GTM_PWM_CH_INDEX_0    = 0U,    /* PWM channel 0 */
    GTM_PWM_CH_INDEX_1,            /* PWM channel 1 */
    GTM_PWM_CH_INDEX_2,            /* PWM channel 2 */
    GTM_PWM_CH_INDEX_3,            /* PWM channel 3 */
    GTM_PWM_CH_INDEX_4,            /* PWM channel 4 */
    GTM_PWM_CH_INDEX_5,            /* PWM channel 5 */
    GTM_PWM_CH_INDEX_6,            /* PWM channel 6 */
    GTM_PWM_CH_INDEX_7,            /* PWM channel 7 */
    GTM_PWM_CH_INDEX_8,            /* PWM channel 8 */
    GTM_PWM_CH_INDEX_9,            /* PWM channel 9 */
    GTM_PWM_CH_INDEX_10,           /* PWM channel 10 */
    GTM_PWM_CH_INDEX_11,           /* PWM channel 11 */
    GTM_PWM_CH_INDEX_12,           /* PWM channel 12 */
    GTM_PWM_CH_INDEX_13,           /* PWM channel 13 */
    GTM_PWM_CH_INDEX_14,           /* PWM channel 14 */
    GTM_PWM_CH_INDEX_15            /* PWM channel 15 */
/* #Violation: gtm_pwm_hal_h_REF_1 */
} Gtm_Pwm_Ch_Index;

/* Clock source */
typedef enum
{
    GTM_PWM_CLOCK_CMUFXCLK0    = 0U, /* Fixed clock 0, div 1, used by TOM */
    GTM_PWM_CLOCK_CMUFXCLK1 = 1U,    /* Fixed clock 1, div 16, used by TOM */
    GTM_PWM_CLOCK_CMUFXCLK2 = 2U,    /* Fixed clock 2, div 256, used by TOM */
    GTM_PWM_CLOCK_CMUFXCLK3 = 3U,    /* Fixed clock 3, div 4096, used by TOM */
    GTM_PWM_CLOCK_CMUFXCLK4 = 4U,    /* Fixed clock 4, div 65536, used by TOM */
    GTM_PWM_CLOCK_CMUCLK0   = 0U,    /* Configurable clock 0, used by ATOM */
    GTM_PWM_CLOCK_CMUCLK1   = 1U,    /* Configurable clock 1, used by ATOM */
    GTM_PWM_CLOCK_CMUCLK2   = 2U,    /* Configurable clock 2, used by ATOM */
    GTM_PWM_CLOCK_CMUCLK3   = 3U,    /* Configurable clock 3, used by ATOM */
    GTM_PWM_CLOCK_CMUCLK4   = 4U,    /* Configurable clock 4, used by ATOM */
    GTM_PWM_CLOCK_CMUCLK5   = 5U,    /* Configurable clock 5, used by ATOM */
    GTM_PWM_CLOCK_CMUCLK6   = 6U,    /* Configurable clock 6, used by ATOM */
    GTM_PWM_CLOCK_CMUCLK7   = 7U,    /* Configurable clock 7, used by ATOM */

    /* GTM_PWM_CLOCK_NOCLOCK, */
    GTM_PWM_CLOCK_STOP      = 12U,    /* Functional operation stopped, clock resolution tied to zero */
    GTM_PWM_CLOCK_TRIGOUT   = 13U,    /* TOM_CH_TRIGOUT[x-1:x-1] selected */
    GTM_PWM_CLOCK_EXTTRIGIN = 14U     /* TOM_EXT_TRIGIN[x:x] selected */
} Gtm_Pwm_Clock;

/* PWM channel counter reset source */
typedef enum
{
    GTM_PWM_RESETEVENT_ONCM0     = 0U,  /* Reset counter register CN0 on matching comparison with CM0 */
    GTM_PWM_RESETEVENT_ONTRIGGER        /* Reset counter register CN0 on trigger */
} Gtm_Pwm_ResetEvent;

/* PWM channel trigger output signal */
typedef enum
{
    GTM_PWM_TRIGOUT_FORWARD  = 0U,      /* Forward the trigger from the previous channel */
    GTM_PWM_TRIGOUT_GENERATE            /* Generate the trigger from the current channel */
} Gtm_Pwm_TrigOut;

/* PWM channel interrupt edge */
typedef enum
{
    GTM_PWM_IRQEDGE_NONE = 0U,   /* None interrupt */
    GTM_PWM_IRQEDGE_RISE,        /* Rising edge triggers interrupt */
    GTM_PWM_IRQEDGE_FALL,        /* Falling edge triggers interrupt */
    GTM_PWM_IRQEDGE_ALL          /* All interrupt */
} Gtm_Pwm_IrqEdge;

/* PWM channel count mode */
typedef enum
{
    GTM_PWM_COUNTMODE_UP = 0U,   /* Up/down counter mode disabled */
    GTM_PWM_COUNTMODE_UPDOWN_1,  /* Up/down counter mode 1 enabled */
    GTM_PWM_COUNTMODE_UPDOWN_2,  /* Up/down counter mode 2 enabled */
    GTM_PWM_COUNTMODE_UPDOWN_3   /* Up/down counter mode 3 enabled */
} Gtm_Pwm_CountMode;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* PWM channel Interrupt control */
typedef struct
{
    boolean        isRiseEnabled;       /* Enable/Disable choice for rising edge interrupt */
    boolean        isFallEnabled;       /* Enable/Disable choice for falling edge interrupt */
    Gtm_IrqMode    mode;                /* Interrupt mode */
} Gtm_Pwm_ConfigIrq;

/* PWM channel Interrupt control */
typedef struct
{
    boolean     isHresEnabled;       /* Enable/Disable the high resolution */
    uint8       hresPeriod;          /* High resolution micro-steps for period */
    uint8       hresPulseWidth;      /* High resolution micro-steps for pulse width */
} Gtm_Pwm_HresConfig;

/* Initialization configuration structure for PWM */
/* #Violation: gtm_pwm_hal_h_REF_2 */
typedef struct
{
    Gtm_Pwm_Clock            clk;                   /* Timer input clock */
    uint32                   period;                /* PWM period */
    uint32                   dutyCycle;             /* PWM duty cycle */
    uint32                   phase;                 /* PWM phase shift in ticks */
    Gtm_Pwm_HresConfig       hresConfig;            /* Reserved configuration */
    Gtm_Pwm_ResetEvent       resetSource;           /* Channel counter reset source */
    Gtm_SignalState          signalLevel;           /* Signal Level */
    Gtm_Pwm_ConfigIrq        interrupt;             /* Configuration structure for interrupt */
    Gtm_Pwm_TrigOut          trigOut;               /* Trigger output signal select */
    Gtm_Pwm_CountMode        countMode;             /* Count mode. If (countMode != 0), the period must greater than 2. */
    boolean                  isSyncUpdateEnabled;   /* Synchronous or Asynchronous update */
    boolean                  isChannelEnable;       /* Channel enable */
    boolean                  isOutputEnable;        /* Channel output enable */
    boolean                  isImmediate;           /* Enable/disable immediate start of PWM */
} Gtm_Pwm_Config;
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
/* #Violation: gtm_pwm_hal_h_REF_4 */
#define PWM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_pwm_hal_h_REF_3 */
#include "Pwm_MemMap.h"
#else
/* #Violation: gtm_pwm_hal_h_REF_4 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_pwm_hal_h_REF_3 */
#include "Gtm_MemMap.h"
#endif

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_InitChannel
 * Description:  PWM channel initialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               pConfig: The pointer of the initialization configuration structure for PWM channel
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/08/02    01031      Added shadow register configuration
 *********************************************************************************************************************/
extern boolean Gtm_Pwm_Hal_InitChannel(const Gtm_Output_Driver *const pDriver, const Gtm_Pwm_Config *const pConfig);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_DeinitChannel
 * Description:  PWM channel deinitialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               idleLevel: Idle state
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/08/02    01031      Added shadow register configuration
 *********************************************************************************************************************/
extern boolean Gtm_Pwm_Hal_DeinitChannel(const Gtm_Output_Driver *const pDriver, Gtm_SignalState idleLevel);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_SetPeriod
 * Description:  Sets pwm period
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               period: Pwm period (TOM: the maximum value is 0xFFFF, ATOM: the maximum value is 0xFFFFFF)
 *               syncUpdate: If ture, the period is set synchronously.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Pwm_Hal_SetPeriod(const Gtm_Output_Driver *const pDriver, uint32 period, boolean syncUpdate);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_SetDutyCycle
 * Description:  Sets pwm duty cycle
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               dutyCycle: Pwm duty cycle (TOM: the maximum value is 0xFFFF, ATOM: the maximum value is 0xFFFFFF)
 *               syncUpdate: If ture, the period is set synchronously.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_Pwm_Hal_SetDutyCycle(const Gtm_Output_Driver *const pDriver, uint32 dutyCycle, boolean syncUpdate);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_SetIdleLevel
 * Description:  Sets PWM channel idle state
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               idleLevel: Idle state
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/08/08    01031      Added the shadow register configuration
 *********************************************************************************************************************/
extern boolean Gtm_Pwm_Hal_SetIdleLevel(const Gtm_Output_Driver *const pDriver, Gtm_SignalState idleLevel);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_GetOutputLevel
 * Description:  Gets current output signal level
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 * Inout:        None
 * Output:       None
 * Return:       Gtm_SignalState: Current output signal level
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern Gtm_SignalState Gtm_Pwm_Hal_GetOutputLevel(const Gtm_Output_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_SetInterrupt
 * Description:  Enable / disable channel interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               irqEdge: Interrupt generate on specific edge
 *               enable: Enable / disable specific interrupt
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/07/17    01031      Change the interrupt type to PWM edge dependent
 *********************************************************************************************************************/
extern boolean Gtm_Pwm_Hal_SetInterrupt(const Gtm_Output_Driver *const pDriver, Gtm_Pwm_IrqEdge irqEdge,                                                                                                 boolean enable);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_ClearInterruptStatus
 * Description:  Clears PWM channel interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               irqEdge: Interrupt generate on specific edge
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/07/17    01031      Change the interrupt type to PWM edge dependent
 *********************************************************************************************************************/
extern void Gtm_Pwm_Hal_ClearInterruptStatus(const Gtm_Output_Driver *const pDriver, Gtm_Pwm_IrqEdge irqEdge);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_SetCounterValue
 * Description:  Sets PWM channel counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               value: Counter value (TOM: the maximum value is 0xFFFF, ATOM: the maximum value is 0xFFFFFF)
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern void Gtm_Pwm_Hal_SetCounterValue(const Gtm_Output_Driver *const pDriver, uint32 value);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_GetCounterValue
 * Description:  Gets PWM channel counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 * Inout:        None
 * Output:       None
 * Return:       uint32: Counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Pwm_Hal_GetCounterValue(const Gtm_Output_Driver *const pDriver);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_SetChannelsOutput
 * Description:  Enable / disable one or more channel output
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        module: The GTM submodule type. 0:TOM    1:ATOM
 *               moduleIndex: The GTM submodule index, for details about the index rang, see the user manual of the 
 *                            specific chip model
 *               mask: Mask for the channel feature enable (bit[7:0] or bit[23:16]) / disable (bit[15:8] or bit[31:24])
 *                     Note : The TOM module can only control the low 16 bits (TGC0) or high 16 bits (TGC1) at a time.
 *               immediate: If true, the channel output enable immediately, otherwise wait for the trigger
 *                          signal to enable the channel output.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       pDriver->channel is not used in this function! The TOM module can only control the low 16 bits (TGC0)
 *                  or high 16 bits (TGC1) at a time.
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/07/17    01031      Parameter modification
 *********************************************************************************************************************/
extern boolean Gtm_Pwm_Hal_SetChannelsOutput(uint8 module, uint8 moduleIndex, uint32 mask, boolean immediate);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_GetInterruptStatus
 * Description:  Gets specific / all interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               irqEdge: Interrupt generate on specific edge
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt status. If gets all status, bit 0: rise edge, bit 1: fall edge
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *  2023/07/17    01031      Change the interrupt type to PWM edge dependent
 *********************************************************************************************************************/
extern uint32 Gtm_Pwm_Hal_GetInterruptStatus(const Gtm_Output_Driver *const pDriver, Gtm_Pwm_IrqEdge irqEdge);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_SetPeriodDutyCycle
 * Description:  Sets pwm period and duty cycle
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant (reentrant when use different channels)
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               period: Pwm period (TOM: the maximum value is 0xFFFF, ATOM: the maximum value is 0xFFFFFF)
 *               dutyCycle: Pwm duty cycle (TOM: the maximum value is 0xFFFF, ATOM: the maximum value is 0xFFFFFF)
 *               syncUpdate: If ture, the period is set synchronously.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/17    01031      Create
 *  2023/08/08    01031      Added the shadow register configuration
 *********************************************************************************************************************/
extern boolean Gtm_Pwm_Hal_SetPeriodDutyCycle(const Gtm_Output_Driver *const pDriver, uint32 period, uint32 dutyCycle,
                                                                                                boolean syncUpdate);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_GetInterruptEnableStatus
 * Description:  Gets interrpt enable status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               irqEdge: Interrupt generate on specific edge
 * Inout:        None
 * Output:       None
 * Return:       uint32: Specific / all interrupt enable status. bit 0: CCU0TC, bit 1: CCU1TC
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/08/01    01031      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Pwm_Hal_GetInterruptEnableStatus(const Gtm_Output_Driver *const pDriver, Gtm_Pwm_IrqEdge irqEdge);

/**********************************************************************************************************************
 * Function:     Gtm_Pwm_Hal_SetChannelOutput
 * Description:  Start / stop channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pDriver: The pointer of the hardware resources used by the PWM
 *               channelEnable: Enable / disable channel
 *               outEnable: Enable / disable channel output
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/27    01177     Create
 *********************************************************************************************************************/
extern boolean Gtm_Pwm_Hal_SetChannelOutput(const Gtm_Output_Driver *const pDriver, boolean channelEnable,                                                                                             boolean outEnable);

#ifndef GTM_HAL_MEMMAP
/* #Violation: gtm_pwm_hal_h_REF_4 */
#define PWM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_pwm_hal_h_REF_3 */
#include "Pwm_MemMap.h"
#else
/* #Violation: gtm_pwm_hal_h_REF_4 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_pwm_hal_h_REF_3 */
#include "Gtm_MemMap.h"
#endif

#endif /* GTM_PWM_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_timebase_hal.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations of the TIMEBASE module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_timebase_hal_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_timebase_hal_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #gtm_timebase_hal_h_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_timebase_hal_h_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef GTM_TIMEBASE_HAL_H_
#define GTM_TIMEBASE_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_cmu_std.h"
#include "gtm_register.h"
#include "gtm_tbu_std.h"
#include "gtm.h"
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
/* GTM CMU global clock resolution generator */
typedef struct
{
    uint32        num; /* The numerator for CMU global clock resolution generator */
    uint32        den; /* The denominator for CMU global clock resolution generator */
} Gtm_Cmu_GlobalClkDivider;

/* GTM CMU external clock resolution generator */
typedef struct
{
    uint32        num;         /* The numerator for the external clock resolution generator */
    uint32        den;         /* The denominator for the external clock resolution generator */
    boolean    isEnabled;    /* Clock enable control */
} Gtm_Cmu_ExternalClk;

/* CMU external clock configuration */
typedef struct
{
    Gtm_Cmu_ExternalClk eclk0; /* The configuration of the external clock 0 */
    Gtm_Cmu_ExternalClk eclk1; /* The configuration of the external clock 1 */
    Gtm_Cmu_ExternalClk eclk2; /* The configuration of the external clock 2 */
} Gtn_Cmu_ExternalClkConfig;

/* CMU configuration clock configuration */
typedef struct
{
    uint32                divider;     /* Count value for the clock divider */
    Gtm_Cmu_Clk_Src        src;          /* Input selection for Clock Resolution Generator */
    boolean            isEnabled;  /* Clock enable control */
} Gtm_Cmu_ConfigurableClk;

/* CMU configuration clock configuration */
typedef struct
{
    Gtm_Cmu_ConfigurableClk        clk0; /* The configuration of the configurable clock 0 */
    Gtm_Cmu_ConfigurableClk        clk1; /* The configuration of the configurable clock 1 */
    Gtm_Cmu_ConfigurableClk        clk2; /* The configuration of the configurable clock 2 */
    Gtm_Cmu_ConfigurableClk        clk3; /* The configuration of the configurable clock 3 */
    Gtm_Cmu_ConfigurableClk        clk4; /* The configuration of the configurable clock 4 */
    Gtm_Cmu_ConfigurableClk        clk5; /* The configuration of the configurable clock 5 */
    Gtm_Cmu_ConfigurableClk        clk6; /* The configuration of the configurable clock 6 */
    Gtm_Cmu_ConfigurableClk        clk7; /* The configuration of the configurable clock 7 */
} Gtm_Cmu_ConfigurableClkConfig;

/* CMU fixed clock configuration */
typedef struct
{
    Gtm_Cmu_Fxclk_Src    src;         /* Input selection for CMU fixed clock */
    boolean            isEnabled;     /* Enable / disable fixed clock */
} Gtm_Cmu_FixedClkConfig;

/* TBU channel 0 configuration */
/* #Violation: gtm_timebase_hal_h_REF_1 */
/* #Violation: gtm_timebase_hal_h_REF_2 */
typedef struct
{
    uint32             initVal;     /* Free timer offset value */
    Gtm_Cmu_Clk         clk;         /* Free timer clock source */
    Gtm_Tbu_Ts0_Bit bitUse;     /* Count value alignment */
    boolean          isEnabled;     /* Enable / disable free timer */
} Gtm_Tbu_Channel0;

/* TBU channel (1,2) configuration */
/* #Violation: gtm_timebase_hal_h_REF_1 */
/* #Violation: gtm_timebase_hal_h_REF_2 */
typedef struct
{
    uint32             initVal;    /* Free timer offset value */
    Gtm_Cmu_Clk         clk;        /* Free timer clock source */
    Gtm_Tbu_Mode     mode;         /* Counting mode */
    boolean          isEnabled;    /* Enable / disable free timer */
} Gtm_Tbu_Channel12;

/* TBU channel configuration */
/* #Violation: gtm_timebase_hal_h_REF_2 */
typedef struct
{
    const Gtm_Tbu_Channel0    *pCh0; /* The configuration of the TBU channel 0 */
    const Gtm_Tbu_Channel12    *pCh1; /* The configuration of the TBU channel 1 */
    const Gtm_Tbu_Channel12    *pCh2; /* The configuration of the TBU channel 2 */
} Gtm_FreeTimerConfig;

/* GTM clock configuration */
/* #Violation: gtm_timebase_hal_h_REF_1 */
/* #Violation: gtm_timebase_hal_h_REF_2 */
typedef struct
{
    Gtm_Cluster_ClkConfig          clusterClk;     /* GTM cluster clock configuration */
    Gtm_Cmu_GlobalClkDivider      globalClk;     /* CMU global clock configuration */
    Gtn_Cmu_ExternalClkConfig      externalClk;     /* CMU external clock configuration */
    Gtm_Cmu_ConfigurableClkConfig configClk;     /* CMU configurable clock configuration */
    Gtm_Cmu_FixedClkConfig          fixedClk;     /* CMU fixed clock configuration */
} Gtm_ClockConfig;
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: gtm_timebase_hal_h_REF_4 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timebase_hal_h_REF_3 */
#include "Gtm_MemMap.h"

/**********************************************************************************************************************
 * Function:     Gtm_TimeBase_Hal_InitClock
 * Description:  GTM clock initialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: The pointer of the initialization configuration structure for GTM clock
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_TimeBase_Hal_InitClock(const Gtm_ClockConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Gtm_TimeBase_Hal_InitFreeTimer
 * Description:  TBU channel initialization
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: The pointer of the initialization configuration structure for TBU channel
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern boolean Gtm_TimeBase_Hal_InitFreeTimer(const Gtm_FreeTimerConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Gtm_TimeBase_Hal_GetFreeTimerCounter
 * Description:  Get TBU channel counter value
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        channel: The channel of the TBU
 * Inout:        None
 * Output:       None
 * Return:       uint32: TBU channel counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/25    01177     Create
 *  2024/02/18    01031     Parameter type modified
 *********************************************************************************************************************/
extern uint32 Gtm_TimeBase_Hal_GetFreeTimerCounter(Gtm_Tbu_Ch channel);

/* #Violation: gtm_timebase_hal_h_REF_4 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_timebase_hal_h_REF_3 */
#include "Gtm_MemMap.h"
#endif /* GTM_TIMEBASE_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

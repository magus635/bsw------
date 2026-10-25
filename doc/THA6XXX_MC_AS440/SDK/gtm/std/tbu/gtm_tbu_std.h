/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gtm_tbu_std.h
 * Author:      01031
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all the data type definitions and function declarations for all the internal
 *                 functions of the TBU module.
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
* #Violation Summary
*
* #gtm_tbu_std_h_REF_1:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #gtm_tbu_std_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
 #ifndef GTM_TBU_STD_H_
#define GTM_TBU_STD_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "gtm_register.h"
#include "compilertypes.h"
#include "Platform_Types.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* TBU_CHEN: 0b10 = channel enabled, 0b01 = channel disabled */
#define  GTM_TBU_CH_ENABLE      (2U)  /* TBU channel enable */
#define  GTM_TBU_CH_DISABLE      (1U) /* TBU channel disable */

#define  GTM_TBU_ENDIS_POS0     (0U)  /* [1:0] TBU channel[0] enable/disable position */
#define  GTM_TBU_ENDIS_POS1     (2U)  /* [3:2] TBU channel[1] enable/disable position */
#define  GTM_TBU_ENDIS_POS2     (4U)  /* [5:4] TBU channel[2] enable/disable position */
#define  GTM_TBU_ENDIS_POS3     (6U)  /* [7:6] TBU channel[3] enable/disable position */
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* GTM TBU Time stamps */
typedef enum
{
    GTM_TBU_CH_TS0 = 0U,        /* TBU time stamps 0 */
    GTM_TBU_CH_TS1,                /* TBU time stamps 1 */
    GTM_TBU_CH_TS2,                /* TBU time stamps 2 */
    GTM_TBU_CH_TS3                /* TBU time stamps 3 */
} Gtm_Tbu_Ch;

/* GTM TBU Time stamps 0 counter bits selection */
typedef enum
{
    GTM_TBU_TS0_BIT_LOWER = 0U,        /* TBU time stamps 0 use lower counter bits [23:0] */
    GTM_TBU_TS0_BIT_UPPER             /* TBU time stamps 0 use upper counter bits [26:3] */
} Gtm_Tbu_Ts0_Bit;

/* GTM TBU counter mode */
typedef enum
{
    GTM_TBU_MODE_FREERUNNING = 0U,    /* Free running counter mode */
    GTM_TBU_MODE_FORWARDBACKWARD    /* Forward / backward counter mode */
} Gtm_Tbu_Mode;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: gtm_tbu_std_h_REF_2 */
#define GTM_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tbu_std_h_REF_1 */
#include "Gtm_MemMap.h"

/**********************************************************************************************************************
 * Function:     Gtm_Tbu_Std_GetCounterValue
 * Description:  Gets the TBU timestamps
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        channel: TBU channel
 * Inout:        None
 * Output:       None
 * Return:       uint32: Counter value
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/19    01031      Create
 *********************************************************************************************************************/
extern uint32 Gtm_Tbu_Std_GetCounterValue(Gtm_Tbu_Ch channel);

/**********************************************************************************************************************
 * Function:     Gtm_Tbu_Std_SetClockSource
 * Description:  Set the clock source for the TBU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        channel: TBU channel
 *               clk: The clk source for the TBU channel (0~7)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/27    01177     Create
 *********************************************************************************************************************/
extern boolean Gtm_Tbu_Std_SetClockSource(Gtm_Tbu_Ch channel, uint8 clk);

/**********************************************************************************************************************
 * Function:     Gtm_Tbu_Std_SetMode
 * Description:  Set the mode for the TBU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        channel: TBU channel
 *               mode: The mode for the TBU channel (0~1)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/27    01177     Create
 *********************************************************************************************************************/
extern boolean Gtm_Tbu_Std_SetMode(Gtm_Tbu_Ch channel, uint8 mode);

/**********************************************************************************************************************
 * Function:     Gtm_Tbu_Std_SetBase
 * Description:  Set the base for the TBU channel
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        channel: TBU channel
 *               base: The base for the TBU channel, the maximum value is 0xFFFFFF.
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/27    01177     Create
 *********************************************************************************************************************/
extern void Gtm_Tbu_Std_SetBase(Gtm_Tbu_Ch channel, uint32 base);

/**********************************************************************************************************************
 * Function:     Gtm_Tbu_Std_SetTs0Res
 * Description:  Set channel0 base register resolution
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        res: The register resolution (0~1)
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/27    01177     Create
 *********************************************************************************************************************/
extern boolean Gtm_Tbu_Std_SetTs0Res(uint8 res);

/**********************************************************************************************************************
 * Function:     Gtm_Tbu_Std_SetChannels
 * Description:  Enable / Disable TBU channels
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        chEn: TBU global channel enable value. bit[1:0] = channel 0, bit[3:2] = channel 1,
 *               bit[5:4] = channel 2, bit[7:6] = channel 3.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/09/27    01177     Create
 *********************************************************************************************************************/
extern boolean Gtm_Tbu_Std_SetChannels(uint32 chEn);

/* #Violation: gtm_tbu_std_h_REF_2 */
#define GTM_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gtm_tbu_std_h_REF_1 */
#include "Gtm_MemMap.h"
#endif /* GTM_TBU_STD_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

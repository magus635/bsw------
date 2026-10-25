/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    safewdt_hal.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/

/*
* #Violation Summary
*
* #safewdt_hal_h_REF_1:MISRAC2012-Dir-4.8;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity 
* 
* #safewdt_hal_h_REF_2:CERTC-DCL12-C;
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
* #safewdt_hal_h_REF_3:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* #safewdt_hal_h_REF_4:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/

#ifndef SAFEWDT_HAL_H_
#define SAFEWDT_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "tha6_cfg.h"
#include "compilertypes.h"
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
/* Safety core ID */
typedef enum
{
    SAFEWDT_SAFECPUID_0 = 0U, /* CPU0 is safety core */
#if defined (THA6_THA6206) || defined(THA6_THA6206D) || defined (THA6_THA6412)
    SAFEWDT_SAFECPUID_1,      /* CPU1 is safety core */
#if defined (THA6_THA6412)
    SAFEWDT_SAFECPUID_2,      /* CPU2 is safety core */
    SAFEWDT_SAFECPUID_3,      /* CPU3 is safety core */
#endif
#endif
    SAFEWDT_SAFECPUID_NONE    /* None of above */
} Safewdt_SafeCpuId;

/* SE and WDT password mode */
typedef enum
{
    SAFEWDT_PWMODE_FIXED = 0U, /* Fixed password mode */
    SAFEWDT_PWMODE_DYNAMIC_1,  /* Dynamic password mode 1 */
    SAFEWDT_PWMODE_DYNAMIC_2   /* Dynamic password mode 2 */
} Safewdt_PwMode;

/* SE and WDT clock divisor coefficient */
typedef enum
{
    SAFEWDT_CLKDIV_THROUGH = 0U, /* Clock through */
    SAFEWDT_CLKDIV_64,           /* 64 frequency division */
    SAFEWDT_CLKDIV_256,          /* 256 frequency division */
    SAFEWDT_CLKDIV_16384         /* 16384 frequency division */
} Safewdt_ClkDiv;

/* SE and WDT output error mode of first period */
typedef enum
{
    SAFEWDT_OUTMODE_ALARM = 0U, /* Error trigger alarm */
    SAFEWDT_OUTMODE_INTERRUPT   /* Error trigger interrupt */
} Safewdt_OutMode;

/* SAFEWDT status */
typedef enum
{
    SAFEWDT_STATUS_RESET = 0U, /* SAFEWDT status reset */
    SAFEWDT_STATUS_SET,        /* SAFEWDT status set */
} Safewdt_Status;

/* SAFEWDT alarm status type */
typedef enum
{
    SAFEWDT_ALARMSTATUSFLAG_SETIMEOUT = 0x1U,        /* SE counter overflow error alarm */
    SAFEWDT_ALARMSTATUSFLAG_FIRSTWDTTIMEOUT = 0x2U,  /* WDT counter overflow error alarm of first interval */
    SAFEWDT_ALARMSTATUSFLAG_SECONDWDTTIMEOUT = 0x4U, /* WDT counter overflow error alarm of second interval */
    SAFEWDT_ALARMSTATUSFLAG_PASSWORDERROR = 0x8U,    /* SAFEWDT password error alarm */
    SAFEWDT_ALARMSTATUSFLAG_REGERROR = 0x10U         /* SAFEWDT register error alarm */
} Safewdt_AlarmStatusFlag;

/* SAFEWDT interrupt status type */
typedef enum
{
    SAFEWDT_INTERRUPTSTATUSFLAG_SETIMEOUT = 0x1U,      /* SE counter overflow error interrupt */
    SAFEWDT_INTERRUPTSTATUSFLAG_FIRSTWDTTIMEOUT = 0x2U /* WDT counter overflow error interrupt of first interval */
} Safewdt_InterruptStatusFlag;

/* SAFEWDT password and low power status type */
typedef enum
{
    SAFEWDT_PWANDLPSTATUSFLAG_SAFEWDTLP = 0x1U, /* SAFEWDT low power recording */
    SAFEWDT_PWANDLPSTATUSFLAG_WDTLP = 0x2U      /* WDT low power recording */
} Safewdt_PwAndLpStatusFlag;

/* SAFEWDT clear status type */
typedef enum
{
    SAFEWDT_CLEARSTATUSFLAG_SEALARM = 0x3U,            /* SE counter overflow error alarm */
    SAFEWDT_CLEARSTATUSFLAG_SEINTR = 0xCU,             /* SE counter overflow error interrupt */
    SAFEWDT_CLEARSTATUSFLAG_FIRSTWDTALARM = 0x30U,     /* WDT counter overflow error alarm of first interval */
    SAFEWDT_CLEARSTATUSFLAG_FIRSTWDTINTERRUPT = 0xC0U, /* WDT counter overflow error interrupt of first interval */
    SAFEWDT_CLEARSTATUSFLAG_SECONDWDTALARM = 0x300U,   /* WDT counter overflow error alarm of second interval */
    SAFEWDT_CLEARSTATUSFLAG_SAFEWDTLP = 0xC00U,        /* SAFEWDT low power recording */
    SAFEWDT_CLEARSTATUSFLAG_WDTLP = 0x3000U,           /* WDT low power recording */
    SAFEWDT_CLEARSTATUSFLAG_PASSWORDALARM = 0xC000U,   /* SAFEWDT password error alarm */
    SAFEWDT_CLEARSTATUSFLAG_REGALARM = 0x30000U,       /* SAFEWDT register error alarm */
    SAFEWDT_CLEARSTATUSFLAG_ALLCLEAR = 0x3FFFFU        /* Clear all SAFEWDT status flag */
} Safewdt_ClearStatusFlag;

/**********************************************************************************************************************
 *                                             Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Structure Definitions
 *********************************************************************************************************************/
/* WDT function configuration structure */
/* #Violation: safewdt_hal_h_REF_1 */
typedef struct
{
    uint16 pwWdtInit;              /* WDT password initial value */
    uint32 wdtLowThv0;             /* WDT low threshold value of first dog feeding interval */
    uint32 wdtLowThv1;             /* WDT low threshold value of second dog feeding interval */
    uint32 wdtHighThv0;            /* WDT high threshold value of first dog feeding interval */
    uint32 wdtHighThv1;            /* WDT high threshold value of second dog feeding interval */
    Safewdt_SafeCpuId safeCpuId;   /* Safety core ID */
    Safewdt_OutMode wdtFirOutMode; /* WDT error output mode of first interval */
    Safewdt_PwMode pwWdtMode;      /* WDT password generation mode */
    Safewdt_ClkDiv wdtClkDiv;      /* WDT clock divisor coefficient */
} Safewdt_WdtConfig;

/* Safety Endinit function configuration structure */
/* #Violation: safewdt_hal_h_REF_1 */
/* #Violation: safewdt_hal_h_REF_2 */
typedef struct
{
    uint16 pwSeInit;             /* SE password initial value */
    uint16 seThv;                /* SE counter threshold value */
    Safewdt_SafeCpuId safeCpuId; /* Safety core ID */
    Safewdt_OutMode seOutMode;   /* SE error output mode */
    Safewdt_PwMode pwSeMode;     /* SE password generation mode */
    Safewdt_ClkDiv seClkDiv;     /* SE clock divisor coefficient */
} Safewdt_SafetyEndinitConfig;

/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Function Declarations
 *********************************************************************************************************************/
/* #Violation: safewdt_hal_h_REF_4 */
#define SAFEWDT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: safewdt_hal_h_REF_3 */
#include "Safewdt_MemMap.h"

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_InitWdt
 * Description:  Initialize WDT function,configure initialization register:Clock frequency division, PWWDT mode and
 *               initial password, counter thresholds for two intervals, and error reporting method.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: Configuration structure of WDT
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       1. The optimal interval between two initialization operations is 20000 75MHz clock cycles.
 *               2. The initialization of PW0 care should precede the WDT part function.
 *               3. During the operation of the watchdog, if want reinitialize, disable watchdog in advance.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Hal_InitWdt(const Safewdt_WdtConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_InitSafetyEndinit
 * Description:  Initialize Safety ENDINIT function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: Configuration structure of Safety ENDINIT
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       1. The optimal interval between two initialization operations is 20000 75MHz clock cycles.
 *               2. The initialization of PW0 care should precede the ENDINIT part function.
 *               3. The ITMU module disables the ENDINIT function.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Hal_InitSafetyEndinit(const Safewdt_SafetyEndinitConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_GetWdtPassword
 * Description:  Gets current correct PWWDT permission password
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint16: Current correct password
 * Others:       Obtain a password must procede clear PWWDT protection.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *  2024/08/15    01208     Modify the static password generation mode
 *********************************************************************************************************************/
extern uint16 Safewdt_Hal_GetWdtPassword(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_EnableWdt
 * Description:  Enable the WDT function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Hal_EnableWdt(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_ServiSEWdt
 * Description:  Service watchdog
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Hal_ServiceWdt(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_DisableWdt
 * Description:  Disable the WDT function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Hal_DisableWdt(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_ChangeHighThv
 * Description:  Change dog feeding periods by modifying high thresholds
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        newHighThv0: User-defined high threshold of WDT counter first interval. The maximum value is 0x1FFFF.
 *               newHighThv1: User-defined high threshold of WDT counter second interval. The maximum value is 0x1FFFF.
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       1. The threshold cannot exceed the maximum range of the 17 bit counter.
 *               2. The optimal interval with the initialization interface is 20000 75MHz clock cycles.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Hal_ChangeHighThv(uint32 newHighThv0, uint32 newHighThv1);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_GetAlarmFlagStatus
 * Description:  This function acquires SAFEWDT module alarm error flag status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flag: SAFEWDT status type
 * Inout:        None
 * Output:       None
 * Return:       Safewdt_Status: SAFEWDT status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern Safewdt_Status Safewdt_Hal_GetAlarmFlagStatus(Safewdt_AlarmStatusFlag flag);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_GetInterruptFlagStatus
 * Description:  This function acquires SAFEWDT module interrupt error flag status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flag: SAFEWDT status type
 * Inout:        None
 * Output:       None
 * Return:       Safewdt_Status: SAFEWDT status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern Safewdt_Status Safewdt_Hal_GetInterruptFlagStatus(Safewdt_InterruptStatusFlag flag);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_GetPwAndLpFlagStatus
 * Description:  This function acquires SAFEWDT module error flag status.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flag: SAFEWDT status type
 * Inout:        None
 * Output:       None
 * Return:       Safewdt_Status: SAFEWDT status
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern Safewdt_Status Safewdt_Hal_GetPwAndLpFlagStatus(Safewdt_PwAndLpStatusFlag flag);

/**********************************************************************************************************************
 * Function:     SAFEwdt_Hal_ClearFlagStatus
 * Description:  Clear error alarm/interrupt status, PW0/PWWDT/PWCE password valid status flag non support
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        flag: SAFEWDT status type
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Hal_ClearFlagStatus(Safewdt_ClearStatusFlag flag);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_ClearSafetyEndinit
 * Description:  Clear Safety ENDINIT protection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       Appears in pairs with Safewdt_Hal_SetSafetyEndinit(). Disable all interrupts before using this function:
 *               DISABLE_ALL_INTERRUPTS()
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Hal_ClearSafetyEndinit(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_SetSafetyEndinit
 * Description:  Set Safety ENDINIT protection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       Appears in pairs with Safewdt_Hal_ClearSafetyEndinit(). Enable all interrupts after using this function:
 *               ENABLE_ALL_INTERRUPTS().
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Safewdt_Hal_SetSafetyEndinit(void);

/**********************************************************************************************************************
 * Function:     Safewdt_Hal_GetSePassword
 * Description:  Gets current correct PWSE permission password
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint16: Current correct password
 * Others:       Obtain a password must procede clear PWSE protection.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *  2024/08/15    01208     Modify the static password generation mode
 *********************************************************************************************************************/
extern uint16 Safewdt_Hal_GetSePassword(void);

/* #Violation: safewdt_hal_h_REF_4 */
#define SAFEWDT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: safewdt_hal_h_REF_3 */
#include "Safewdt_MemMap.h"
#endif /* SAFEWDT_HAL_H_ */
/**********************************************************************************************************************
 *                                                    End of File
 *********************************************************************************************************************/

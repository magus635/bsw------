/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    cpuwdt_hal.h
 * Author:      01208
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/
/*
* #Violation Summary
*
* #cpuwdt_hal_h_REF_1:MISRAC2012-Dir-4.8;
* Justification:reason 3630 Apply such struct/union definitons to simplify the code structure and reduce the code complexity 
* 
* *#cpuwdt_hal_h_REF_2:MISRAC2012-Rule-20.1; 
* Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
* *#cpuwdt_hal_h_REF_3:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/
#ifndef CPUWDT_HAL_H_
#define CPUWDT_HAL_H_
/**********************************************************************************************************************
 *                                                  Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "cpuwdt_register.h"
#include "tha6_cfg.h"
#include "compilertypes.h"
/**********************************************************************************************************************
 *                                          Global Macro Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                      Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Enumeration Definitions
 *********************************************************************************************************************/
/* CE and WDT password mode */
typedef enum
{
    CPUWDT_PWMODE_FIXED = 0U, /* Fixed password mode */
    CPUWDT_PWMODE_DYNAMIC_1,  /* Dynamic password mode 1 */
    CPUWDT_PWMODE_DYNAMIC_2   /* Dynamic password mode 2 */
} Cpuwdt_PwMode;

/* CE and WDT clock divisor coefficient */
typedef enum
{
    CPUWDT_CLKDIV_THROUGH = 0U, /* Clock through */
    CPUWDT_CLKDIV_64,           /* 64 frequency division */
    CPUWDT_CLKDIV_256,          /* 256 frequency division */
    CPUWDT_CLKDIV_16384         /* 16384 frequency division */
} Cpuwdt_ClkDiv;

/* CE and WDT output error mode of first period */
typedef enum
{
    CPUWDT_OUTMODE_ALARM = 0U, /* Error trigger alarm */
    CPUWDT_OUTMODE_INTERRUPT   /* Error trigger interrupt */
} Cpuwdt_OutMode;

/* CPUWDT status */
typedef enum
{
    CPUWDT_STATUS_RESET = 0U, /* CPUWDT status reset */
    CPUWDT_STATUS_SET         /* CPUWDT status set */
} Cpuwdt_Status;

/* CPUWDT alarm status type */
typedef enum
{
    CPUWDT_ALARMSTATUSFLAG_CETIMEOUT = 0x1U,        /* CE counter overflow error alarm */
    CPUWDT_ALARMSTATUSFLAG_FIRSTWDTTIMEOUT = 0x2U,  /* WDT counter overflow error alarm of first interval */
    CPUWDT_ALARMSTATUSFLAG_SECONDWDTTIMEOUT = 0x4U, /* WDT counter overflow error alarm of second interval */
    CPUWDT_ALARMSTATUSFLAG_PASSWORDERROR = 0x8U,    /* CPUWDT password error alarm */
    CPUWDT_ALARMSTATUSFLAG_REGERROR = 0x10U         /* CPUWDT register error alarm */
} Cpuwdt_AlarmStatusFlag;

/* CPUWDT interrupt status type */
typedef enum
{
    CPUWDT_INTERRUPTSTATUSFLAG_CETIMEOUT = 0x1U,      /* CE counter overflow error interrupt */
    CPUWDT_INTERRUPTSTATUSFLAG_FIRSTWDTTIMEOUT = 0x2U /* WDT counter overflow error interrupt of first interval */
} Cpuwdt_InterruptStatusFlag;

/* CPUWDT password and low power status type */
typedef enum
{
    CPUWDT_PWANDLPSTATUSFLAG_CPUWDTLP = 0x1U, /* CPUWDT low power recording */
    CPUWDT_PWANDLPSTATUSFLAG_WDTLP = 0x2U     /* WDT low power recording */
} Cpuwdt_PwAndLpStatusFlag;

/* CPUWDT clear status flag */
typedef enum
{
    CPUWDT_CLEARSTATUSFLAG_CEALARM = 0x3U,            /* CE counter overflow error alarm clear */
    CPUWDT_CLEARSTATUSFLAG_CEINTR = 0xCU,             /* CE counter overflow error interrupt clear */
    CPUWDT_CLEARSTATUSFLAG_FIRSTWDTALARM = 0x30U,     /* WDT counter overflow error alarm of first interval clear */
    CPUWDT_CLEARSTATUSFLAG_FIRSTWDTINTERRUPT = 0xC0U, /* WDT counter overflow error interrupt of first interval clear */
    CPUWDT_CLEARSTATUSFLAG_SECONDWDTALARM = 0x300U,   /* WDT counter overflow error alarm of second interval clear */
    CPUWDT_CLEARSTATUSFLAG_CPUWDTLP = 0xC00U,         /* CPUWDT low power recording clear */
    CPUWDT_CLEARSTATUSFLAG_WDTLP = 0x3000U,           /* WDT low power recording clear */
    CPUWDT_CLEARSTATUSFLAG_PASSWORDALARM = 0xC000U,   /* CPUWDT password error alarm clear */
    CPUWDT_CLEARSTATUSFLAG_REGALARM = 0x30000U,       /* CPUWDT register error alarm clear */
    CPUWDT_CLEARSTATUSFLAG_ALLCLEAR = 0x3FFFFU        /* All status flag clear */
} Cpuwdt_ClearStatusFlag;
/**********************************************************************************************************************
 *                                           Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Structure Definitions
 *********************************************************************************************************************/
/* WDT function configuration structure */
/* #Violation: cpuwdt_hal_h_REF_1 */
typedef struct
{
    uint16 pwWdtInit;             /* WDT password initial value */
    uint32 wdtLowThv0;            /* WDT low threshold value of first dog feeding interval */
    uint32 wdtLowThv1;            /* WDT low threshold value of second dog feeding interval */
    uint32 wdtHighThv0;           /* WDT high threshold value of first dog feeding interval */
    uint32 wdtHighThv1;           /* WDT high threshold value of second dog feeding interval */
    Cpuwdt_OutMode wdtFirOutMode; /* WDT error output mode of first interval */
    Cpuwdt_PwMode pwWdtMode;      /* WDT password generation mode */
    Cpuwdt_ClkDiv wdtClkDiv;      /* WDT clock divisor coefficient */
} Cpuwdt_WdtConfig;

/* Endinit function configuration structure */
/* #Violation: cpuwdt_hal_h_REF_1 */
typedef struct
{
    uint16 pwCeInit;          /* CE password initial value */
    uint16 ceThv;             /* CE counter threshold value */
    Cpuwdt_OutMode ceOutMode; /* CE error output mode */
    Cpuwdt_PwMode pwCeMode;   /* CE password generation mode */
    Cpuwdt_ClkDiv ceClkDiv;   /* CE clock divisor coefficient */
} Cpuwdt_EndinitConfig;
/**********************************************************************************************************************
 *                                     Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                      Global Inline Function Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
**                                           Global Function Declarations                                            **
**********************************************************************************************************************/
/* #Violation: cpuwdt_hal_h_REF_3 */
#define CPUWDT_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpuwdt_hal_h_REF_2 */
#include "Cpuwdt_MemMap.h"
/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_InitWdt
 * Description:  Initialize WDT function,configure initialization register:Clock frequency division, PWWDT mode and
 *               initial password, counter thresholds for two intervals, and error reporting method.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: Configuration structure of WDT
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       1. The optimal interval between each initialization register is 20000 75MHz clock cycles.
 *               2. The initialization operation of PW0 guarding should precede the WDT part function.
 *               3. During the operation of the watchdog, if want reinitialize, disable watchdog in advance.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Cpuwdt_Hal_InitWdt(const Cpuwdt_WdtConfig* const pConfig);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_InitEndinit
 * Description:  Initialize ENDINIT function
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pConfig: Configuration structure of ENDINIT
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       1. The optimal interval between each initialization register is 20000 75MHz clock cycles.
 *               2. The initialization operation of PW0 guarding should precede the ENDINIT part function.
 *               3. The ITMU module disables the ENDINIT function.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Cpuwdt_Hal_InitEndinit(const Cpuwdt_EndinitConfig *const pConfig);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_GetWdtPassword
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
 *  2024/08/13    01208     Modify the static password generation mode
 *********************************************************************************************************************/
extern uint16 Cpuwdt_Hal_GetWdtPassword(void);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_EnableWdt
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
extern boolean Cpuwdt_Hal_EnableWdt(void);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_ServiceWdt
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
extern boolean Cpuwdt_Hal_ServiceWdt(void);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_GetWdgCounter
 * Description:  Get the WDT counter (THA6206 does not support the use of this API. Calling this API will 
 *               return 0xFFFFFFFF.)
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint32: The WDT counter
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/11/06    00964     Create
 *********************************************************************************************************************/
extern uint32 Cpuwdt_Hal_GetWdgCounter(void);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_DisableWdt
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
extern boolean Cpuwdt_Hal_DisableWdt(void);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_ChangeHighThv
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
 *               2. The optimal interval between initialization interface is 20000 75MHz clock cycles.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Cpuwdt_Hal_ChangeHighThv(uint32 newHighThv0, uint32 newHighThv1);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_GetAlarmFlagStatus
 * Description:  Acquire error alarm status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flag: CPUWDT alarm status flag
 * Inout:        None
 * Output:       None
 * Return:       Cpuwdt_Status: CPUWDT status type
 *               - CPUWDT_STATUS_RESET: Corresponding status flag is reset
 *               - CPUWDT_STATUS_SET: Corresponding status flag is set
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern Cpuwdt_Status Cpuwdt_Hal_GetAlarmFlagStatus(Cpuwdt_AlarmStatusFlag flag);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_GetInterruptFlagStatus
 * Description:  Acquire error interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flag: CPUWDT interrupt status flag
 * Inout:        None
 * Output:       None
 * Return:       Cpuwdt_Status: CPUWDT status type
 *               - CPUWDT_STATUS_RESET: Corresponding status flag is reset
 *               - CPUWDT_STATUS_SET: Corresponding status flag is set
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern Cpuwdt_Status Cpuwdt_Hal_GetInterruptFlagStatus(Cpuwdt_InterruptStatusFlag flag);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_GetPwAndLpFlagStatus
 * Description:  Acquire error password and low power status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flag: CPUWDT password and lower power status flag
 * Inout:        None
 * Output:       None
 * Return:       Cpuwdt_Status: CPUWDT status type
 *               - CPUWDT_STATUS_RESET: Corresponding status flag is reset
 *               - CPUWDT_STATUS_SET: Corresponding status flag is set
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern Cpuwdt_Status Cpuwdt_Hal_GetPwAndLpFlagStatus(Cpuwdt_PwAndLpStatusFlag flag);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_ClearFlagStatus
 * Description:  Clear error alarm/interrupt status, PW0/PWWDT/PWCE password valid status flag non support
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        flag: CPUWDT clear status flag
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Cpuwdt_Hal_ClearFlagStatus(Cpuwdt_ClearStatusFlag flag);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_GetCePassword
 * Description:  Gets current correct PWCE permission password
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       uint16: Current correct password
 * Others:       Obtain a password must procede clear PWCE protection.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *  2024/08/13    01208     Modify the static password generation mode
 *********************************************************************************************************************/
extern uint16 Cpuwdt_Hal_GetCePassword(void);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_ClearEndinit
 * Description:  Clear ENDINIT protection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect 
 * Others:       Appears in pairs with Cpuwdt_Hal_SetEndinit().
 *               Disable all interrupts before using this function.
 *
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Cpuwdt_Hal_ClearEndinit(void);

/**********************************************************************************************************************
 * Function:     Cpuwdt_Hal_SetEndinit
 * Description:  Set ENDINIT protection
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE:  Register read back check correct
 *                        FALSE: Register read back check incorrect
 * Others:       Appears in pairs with Cpuwdt_Hal_ClearEndinit().
 *               Enable all interrupts after using this function.
 * History:
 *  Date          Author    Modified
 *  2023/05/28    01208     Create
 *********************************************************************************************************************/
extern boolean Cpuwdt_Hal_SetEndinit(void);

/* #Violation: cpuwdt_hal_h_REF_3 */
#define CPUWDT_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: cpuwdt_hal_h_REF_2 */
#include "Cpuwdt_MemMap.h"
#endif /* CPUWDT_HAL_H_ */
/**********************************************************************************************************************
 *                                                 End of File
 *********************************************************************************************************************/

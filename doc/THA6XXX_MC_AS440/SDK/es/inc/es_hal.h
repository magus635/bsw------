/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    es_hal.h
 * Author:      01321
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
*#Violation Summary
*#es_hal_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for different configurations
*/
#ifndef ES_HAL_H_
#define ES_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "es_register.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Maximum width of the glitch filter of Port B */
/* #Violation: es_hal_h_REF_1 */
#define ES_MAX_WIDTH_GLITCH_FILTER (1023U)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* The input Port that trigger ES */
typedef enum
{
    ES_PORTID_A = 0U, /* Indicate Port A 33.8 */
    ES_PORTID_B       /* Indicate Port B 21.2 */
} Es_PortID;

/* Mode Selection: Synchronous or Asynchronous */
typedef enum
{
    ES_MODE_SYN = 0U, /* Synchronous Mode */
    ES_MODE_ASY       /* Asynchronous Mode */
} Es_Mode;

/* Mode Polarity High active or Low active */
typedef enum
{
    ES_POLARITY_HIGH = 0U, /* High Polarity activation */
    ES_POLARITY_LOW        /* Low Polarity activation */
} Es_Polarity;

/* Flag set by ES port or set by SAC */
typedef enum
{
    ES_FLAG_SAC = 0U, /* ES Enable Flag from SAC */
    ES_FLAG_PORT      /* ES Enable Flag from Port */
} Es_Flag;

/* The switch for Glitch filter on Port B */
typedef enum
{
    ES_GLITCH_OFF = 0U, /* Disable Glitch Filter */
    ES_GLITCH_ON        /* Enable Glitch Filter */
} Es_Glitch;

/* Es alarm status */
typedef enum
{
    ES_STATUS_RESET = 0U, /* Es status reset */
    ES_STATUS_SET         /* Es status set */
} Es_Status;

/* Es alarm status type */
typedef enum
{
    ES_ALARMSTATUSFLAG_BITALM = 0x800000U,     /* Alarm bit redundant error */
    ES_ALARMSTATUSFLAG_SEALM = 0x1000000U,     /* ESCTRL register SE alarm */
    ES_ALARMSTATUSFLAG_SFFALMSTS = 0x2000000U, /* ALMRSTS register redundant error */
    ES_ALARMSTATUSFLAG_SFFCMD = 0x4000000U,    /* ESCMD register redundant error */
    ES_ALARMSTATUSFLAG_SFFCTRL = 0x8000000U    /* ESCTRL register redundant error */
} Es_AlarmStatusFlag;

/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Initial configuration structure for emergency stop */
typedef struct
{
    Es_PortID portID;      /* Port ID */
    Es_Glitch portBGlitch; /* Glitch filter enable */
    uint32 glitchWidth;    /* Width of the glitch filter */
    Es_Polarity polarity;  /* Polarity to trigger */
    Es_Mode mode;          /* Mode Selection */
} Es_Config;

/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
#define ES_START_SEC_CODE_ASIL_D_GLOBAL
#include "Es_MemMap.h"

/**********************************************************************************************************************
 * Function:     Es_Hal_Init
 * Description:  Initialize all ES setting
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pEsconfig: Emergency Stop configuration structure array
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: Register read back check correct
 *                 FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/25    01321      Create
 *********************************************************************************************************************/
extern boolean Es_Hal_Init(const Es_Config *const pEsconfig);

/**********************************************************************************************************************
 * Function:     Es_Hal_TriggerES
 * Description:  Manually trigger Emergency Stop
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flagType: SAC flag or Port flag
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/25    01321      Create
 *********************************************************************************************************************/
extern void Es_Hal_TriggerES(Es_Flag flagType);

/**********************************************************************************************************************
 * Function:     Es_Hal_TerminateES
 * Description:  Manually Terminate Emergency Stop
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flagType: SAC flag or Port flag
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/06/25    01321      Create
 *********************************************************************************************************************/
extern void Es_Hal_TerminateES(Es_Flag flagType);

/**********************************************************************************************************************
 * Function:     Es_Hal_GetAlarmFlagStatus
 * Description:  Check and return Es Alarm Status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flagStatus: Es alarm status type
 * Inout:        None
 * Output:       None
 * Return:       Es_Status: Es alarm status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/20    01321      Create
 *********************************************************************************************************************/
extern Es_Status Es_Hal_GetAlarmFlagStatus(Es_AlarmStatusFlag flagStatus);

/**********************************************************************************************************************
 * Function:     Es_Hal_ClearAlarmFlagStatus
 * Description:  Clear all Es alarm flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        None
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/20    01321      Create
 *********************************************************************************************************************/
extern void Es_Hal_ClearAlarmFlagStatus(void);

/**********************************************************************************************************************
 * Function:     Es_Hal_GetFlagStatus
 * Description:  Check status of Es flag
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        flagStatus: Es flag status(EMSF SEMSF)
 * Inout:        None
 * Output:       None
 * Return:       Es_Status: flag status
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/20    01321      Create
 *********************************************************************************************************************/
extern Es_Status Es_Hal_GetFlagStatus(Es_Flag flagStatus);

/**********************************************************************************************************************
 * Function: Es_Register_ReadBack_Check
 * Description: es register write check
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:     state: Original state.
 *            expect: The value expected to be written.
 *            value: The value actually written.
 * Inout:  None
 * Output: None
 * Return: boolean: TRUE: Register read back check correct FALSE: Register read back check incorrect
 * Others: None
 * History: None
 * Date         Author   Modified
 * 2025/05/14   01358     create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Es_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);

/**********************************************************************************************************************
 *                                           Global Macro Declarations
 *********************************************************************************************************************/
#define ES_REG_CHECK
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
#if defined(ES_REG_CHECK)
LOCAL_FORCEINLINE boolean Es_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret &= FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Es_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif

#define ES_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Es_MemMap.h"

#endif /* ES_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

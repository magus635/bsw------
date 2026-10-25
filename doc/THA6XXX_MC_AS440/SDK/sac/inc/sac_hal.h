/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    sac_hal.h
 * Author:      00977
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations.
 *********************************************************************************************************************/
#ifndef SAC_HAL_H_
#define SAC_HAL_H_

/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "sac_register.h"
#include "tha6_cfg.h"
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* The register protected by KEYS is locked and the protected register cannot be written */
#define SAC_KEYS_PROTECTION_LOCK (0x0000U)
/* The register protected by KEYS is unlocked and the protected register can be written */
#define SAC_KEYS_PROTECTION_UNLOCK (0x00BCU)
/* The register protected by KEYS is permanent locked and the protected register cannot be written */
#define SAC_KEYS_PROTECTION_PERMANENTLOCK (0xFFU)
/* Command, forces the Sac to go to the RUN state from the START state */
#define SAC_COMMAND_START  (0U)
/* Command, Turns the FIP into the fault free state */
#define SAC_COMMAND_RELEASEFIP (2U)
/* Command, Enables alarm status clear */
#define SAC_COMMAND_ALRAMSTATUSCLEAR (5U)
/* Command, Triggers software alarm */
#define SAC_COMMAND_TRIGGERSOFTWAREALARM  (6U)
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                              Global Type Definitions
 *********************************************************************************************************************/
/* Sac nmi is selected to which CPU to send non-maskable interrupt - Bit0 represents core0, bit1 represents core1 and so on */
typedef uint8 Sac_NmiSendTo;

/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Sac alarm group */
typedef enum
{
    SAC_ALARMGROUP_0 = 0U, /* Sac alarm group 0 */
    SAC_ALARMGROUP_1,      /* Sac alarm group 1 */
#if defined(THA6_THA6412)
    SAC_ALARMGROUP_2,      /* Sac alarm group 2, it is active in THA6412, reserved in THA6206 and THA6104 */
    SAC_ALARMGROUP_3,      /* Sac alarm group 3, it is active in THA6412, reserved in THA6206 and THA6104 */
#endif /* end of THA6_THA6412 */
    SAC_ALARMGROUP_4 = 4U, /* Sac alarm group 4 */
    SAC_ALARMGROUP_5,      /* Sac alarm group 5 */
    SAC_ALARMGROUP_6,      /* Sac alarm group 6 */
    SAC_ALARMGROUP_7,      /* Sac alarm group 7 */
    SAC_ALARMGROUP_8,      /* Sac alarm group 8 */
    SAC_ALARMGROUP_9,      /* Sac alarm group 9 */
    SAC_ALARMGROUP_10,     /* Sac alarm group 10 */
    SAC_ALARMGROUP_11,     /* Sac alarm group 11 */
    SAC_ALARMGROUP_12,      /* Sac alarm group 12 */
    SAC_ALARMGROUP_20 = 20U, /* Sac alarm group 20 */
    SAC_ALARMGROUP_21    /* Sac alarm group 21 */
} Sac_AlarmGroup;

/* Sac alarm index */
typedef enum
{
    SAC_ALARMINDEX_0 = 0U, /* Alarm index 0 */
    SAC_ALARMINDEX_1,      /* Alarm index 1 */
    SAC_ALARMINDEX_2,      /* Alarm index 2 */
    SAC_ALARMINDEX_3,      /* Alarm index 3 */
    SAC_ALARMINDEX_4,      /* Alarm index 4 */
    SAC_ALARMINDEX_5,      /* Alarm index 5 */
    SAC_ALARMINDEX_6,      /* Alarm index 6 */
    SAC_ALARMINDEX_7,      /* Alarm index 7 */
    SAC_ALARMINDEX_8,      /* Alarm index 8 */
    SAC_ALARMINDEX_9,      /* Alarm index 9 */
    SAC_ALARMINDEX_10,     /* Alarm index 10 */
    SAC_ALARMINDEX_11,     /* Alarm index 11 */
    SAC_ALARMINDEX_12,     /* Alarm index 12 */
    SAC_ALARMINDEX_13,     /* Alarm index 13 */
    SAC_ALARMINDEX_14,     /* Alarm index 14 */
    SAC_ALARMINDEX_15,     /* Alarm index 15 */
    SAC_ALARMINDEX_16,     /* Alarm index 16 */
    SAC_ALARMINDEX_17,     /* Alarm index 17 */
    SAC_ALARMINDEX_18,     /* Alarm index 18 */
    SAC_ALARMINDEX_19,     /* Alarm index 19 */
    SAC_ALARMINDEX_20,     /* Alarm index 20 */
    SAC_ALARMINDEX_21,     /* Alarm index 21 */
    SAC_ALARMINDEX_22,     /* Alarm index 22 */
    SAC_ALARMINDEX_23,     /* Alarm index 23 */
    SAC_ALARMINDEX_24,     /* Alarm index 24 */
    SAC_ALARMINDEX_25,     /* Alarm index 25 */
    SAC_ALARMINDEX_26,     /* Alarm index 26 */
    SAC_ALARMINDEX_27,     /* Alarm index 27 */
    SAC_ALARMINDEX_28,     /* Alarm index 28 */
    SAC_ALARMINDEX_29,     /* Alarm index 29 */
    SAC_ALARMINDEX_30,     /* Alarm index 30 */
    SAC_ALARMINDEX_31      /* Alarm index 31 */
} Sac_AlarmIndex;

/* Alarm internal action */
typedef enum
{
    SAC_ALARMINTERNALACTION_NONE = 0U, /* No action */
    SAC_ALARMINTERNALACTION_IGCS0,     /* Sends an interrupt request to the interrupt system according to the IGCS0 */
    SAC_ALARMINTERNALACTION_IGCS1,     /* Sends an interrupt request to the interrupt system according to the IGCS1 */
    SAC_ALARMINTERNALACTION_IGCS2,     /* Sends an interrupt request to the interrupt system according to the IGCS2 */
    SAC_ALARMINTERNALACTION_IGCS3,     /* Sends an interrupt request to the interrupt system according to the IGCS3 */
    SAC_ALARMINTERNALACTION_NMI,       /* Sends a NMI request */
    SAC_ALARMINTERNALACTION_RST        /* Sends a reset request */
} Sac_AlarmInternalAction;

/* FIP action */
typedef enum
{
    SAC_FIPACTION_NONE = 0U, /* No action */
    SAC_FIPACTION_ACTIVATE   /* FIP is activated for alarm event */
} Sac_FipAction;

/* Software alarm */
typedef enum
{
    SAC_SOFTWAREALARM_0 = 0U, /* Software alarm 0 */
    SAC_SOFTWAREALARM_1,      /* Software alarm 1 */
    SAC_SOFTWAREALARM_2,      /* Software alarm 2 */
    SAC_SOFTWAREALARM_3,      /* Software alarm 3 */
    SAC_SOFTWAREALARM_4,      /* Software alarm 4 */
    SAC_SOFTWAREALARM_5,      /* Software alarm 5 */
    SAC_SOFTWAREALARM_6,      /* Software alarm 6 */
    SAC_SOFTWAREALARM_7,      /* Software alarm 7 */
    SAC_SOFTWAREALARM_8,      /* Software alarm 8 */
    SAC_SOFTWAREALARM_9,      /* Software alarm 9 */
    SAC_SOFTWAREALARM_10,     /* Software alarm 10 */
    SAC_SOFTWAREALARM_11,     /* Software alarm 11 */
    SAC_SOFTWAREALARM_12,     /* Software alarm 12 */
    SAC_SOFTWAREALARM_13,     /* Software alarm 13 */
    SAC_SOFTWAREALARM_14,     /* Software alarm 14 */
    SAC_SOFTWAREALARM_15      /* Software alarm 15 */
} Sac_SoftwareAlarm;

/* Alarm executed status */
typedef enum
{
    SAC_ALARMEXECUTIONSTATUS_IRQ0 = 0U,     /* IRQ0 request status */
    SAC_ALARMEXECUTIONSTATUS_IRQ1 = 1U,     /* IRQ1 request status */
    SAC_ALARMEXECUTIONSTATUS_IRQ2 = 2U,     /* IRQ2 request status */
    SAC_ALARMEXECUTIONSTATUS_IRQ3 = 3U,     /* IRQ3 request status */
    SAC_ALARMEXECUTIONSTATUS_RST = 4U,      /* RST request status */
    SAC_ALARMEXECUTIONSTATUS_NMI = 9U,      /* NMI request status */
    SAC_ALARMEXECUTIONSTATUS_PES = 11U,     /* PES request status */
    SAC_ALARMEXECUTIONSTATUS_IRQ0AEM = 16U, /* IRQ0 alarm missed status */
    SAC_ALARMEXECUTIONSTATUS_IRQ1AEM = 17U, /* IRQ1 alarm missed status */
    SAC_ALARMEXECUTIONSTATUS_IRQ2AEM = 18U, /* IRQ2 alarm missed status */
    SAC_ALARMEXECUTIONSTATUS_IRQ3AEM = 19U, /* IRQ3 alarm missed status */
    SAC_ALARMEXECUTIONSTATUS_RSTAEM = 20U,  /* RST alarm missed status */
    SAC_ALARMEXECUTIONSTATUS_NMIAEM = 25U,  /* NMI alarm missed status */
    SAC_ALARMEXECUTIONSTATUS_PESAEM = 27U   /* PES alarm missed status */
} Sac_AlarmExecutionStatus;

/* Sac State */
typedef enum
{
    SAC_STATE_START = 0U,  /* Sac state is START */
    SAC_STATE_RUN,         /* Sac state is RUN */
    SAC_STATE_FAULT,       /* Sac state is FAULT */
    SAC_STATE_RUNPRE,      /* Sac state is RUNPRE */
    SAC_STATE_INTERMEDIATE /* Sac state is INTERMEDIATE */
} Sac_State;

/* Sac fault state duration prescaler */
typedef enum
{
    SAC_FIPFAULTDUPRE_CLKDIV2 = 0U, /* Fault state duration reference clock frequency divided by 2 */
    SAC_FIPFAULTDUPRE_CLKDIV4,      /* Fault state duration reference clock frequency divided by 4 */
    SAC_FIPFAULTDUPRE_CLKDIV8,      /* Fault state duration reference clock frequency divided by 8 */
    SAC_FIPFAULTDUPRE_CLKDIV16,     /* Fault state duration reference clock frequency divided by 16 */
    SAC_FIPFAULTDUPRE_CLKDIV32,     /* Fault state duration reference clock frequency divided by 32 */
    SAC_FIPFAULTDUPRE_CLKDIV64,     /* Fault state duration reference clock frequency divided by 64 */
    SAC_FIPFAULTDUPRE_CLKDIV128,    /* Fault state duration reference clock frequency divided by 128 */
    SAC_FIPFAULTDUPRE_CLKDIV256     /* Fault state duration reference clock frequency divided by 256 */
} Sac_FipFaultDuPre;

/* Sac dynamic protocol prescaler */
typedef enum
{
    SAC_FIPDYNPROTOPRE_CLKDIV512 = 0U, /* Dynamic protocol reference clock frequency divided by 512 */
    SAC_FIPDYNPROTOPRE_CLKDIV1024,     /* Dynamic protocol reference clock frequency divided by 1024 */
    SAC_FIPDYNPROTOPRE_CLKDIV2048,     /* Dynamic protocol reference clock frequency divided by 2048 */
    SAC_FIPDYNPROTOPRE_CLKDIV4096      /* Dynamic protocol reference clock frequency divided by 4096 */
} Sac_FipDynProtoPre;

/* Fault indication protocol mode */
typedef enum
{
    SAC_FIPMODE_SINGLERAILSTATICPROTOCOL = 0U, /* Single rail static protocol */
    SAC_FIPMODE_DUALRAILDYNAMICPROTOCOL,       /* Dual rail dynamic protocol */
    SAC_FIPMODE_SINGLERAILDYNAMICPROTOCOL      /* Single rail dynamic protocol */
} Sac_FipMode;

/* Sac command executed result */
typedef enum
{
    SAC_CMDEXRESULT_SUCCESSFUL = 0U, /* Command executed successfully */
    SAC_CMDEXRESULT_FAILED           /* Command executed failed */
} Sac_CmdExResult;

/* Sac alarm status */
typedef enum
{
    SAC_ALARMSTATUS_NOTTRIGGERED = 0U, /* Alarm is not triggered */
    SAC_ALARMSTATUS_TRIGGERED          /* Alarm is triggered */
} Sac_AlarmStatus;

/* Sac alarm executed status */
typedef enum
{
    SAC_ALARMEXSTATUS_NOREQSERORNOEVENTMISSED = 0U, /* No request was serviced or no alarm event missed */
    SAC_ALARMEXSTATUS_REQSEROREVENTMISSED           /* Request was serviced or at least one alarm event missed */
} Sac_AlarmExStatus;

/* Sac port direction */
typedef enum
{
    SAC_PORTDIR_FIP0ANDFIP1INPUT = 0U,       /* Sets FIP[0] and FIP[1] to input state */
    SAC_PORTDIR_FIP0OUTPUTANDFIP1INPUT = 1U, /* Sets FIP[0] to output state and FIP[1] to input state */
    SAC_PORTDIR_FIP0ANDFIP1OUTPUT = 3U       /* Sets FIP[0] and FIP[1] to output state */
} Sac_PortDir;

/* Sac Fault To Run */
typedef enum
{
    SAC_FAULTTORUN_DISABLED = 0U, /* Fault to Run transition disabled  */
    SAC_FAULTTORUN_ENABLED        /* Fault to Run transition enabled */
} Sac_FaultToRun;

/* Sac command  */
typedef enum
{
    SAC_EXECUTE_START = 0,   /* Sac execute start command, the ARG value must be 0 */
    SAC_EXECUTE_ACTIVE_FIP,  /* Sac execute active FIP command, the ARG value must be 0 */
    SAC_EXECUTE_RELRASE_FIP, /* Sac execute release FIP command, the ARG value must be 0 */
    SAC_EXECUTE_ACTIVE_PES,  /* Sac execute active PES command, the ARG value must be 0 */
    SAC_EXECUTE_IET_STOP,    /* Sac execute IET stop command, if ARG=0, stop IET0, if ARG=1, stop IET1 */
    SAC_EXECUTE_ASCE,        /* Sac execute enter clearing ASR command, the ARG value must be 0 */
    SAC_EXECUTE_TRIG_ALARM,  /* Sac execute clearing alarm command for SAR4, the ARG range value is 0~15 */
    SAC_EXECUTE_ALIVE_TEST   /* Sac execute core alive stest enable command, if ARG=0x5, statr test, if ARG=0xA, stop test */
} Sac_Command;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Sac alarm configuration structure */
typedef struct
{
    Sac_FaultToRun faultToRun; /* Enable/disable Fault to Run transition */
    Sac_NmiSendTo nmiSendTo;   /* Nmi is selected to which CPU to send */
    uint8 igcs0;               /* Mapping between Interrupt Generation Configuration Set 0 and Interrupt Request;
                                  1h: Interrupt request 0
                                  2h: Interrupt request 1
                                  4h: Interrupt request 2
                                  8h: Interrupt request 3
                                  Note: Interrupt Generation Configuration Set 0 can be mapped to multiple Interrupt
                                  requests simultaneously */
    uint8 igcs1;               /* Mapping between Interrupt Generation Configuration Set 1 and Interrupt Request;
                                  1h: Interrupt request 0
                                  2h: Interrupt request 1
                                  4h: Interrupt request 2
                                  8h: Interrupt request 3
                                  Note: Interrupt Generation Configuration Set 1 can be mapped to multiple Interrupt
                                  requests simultaneously */
    uint8 igcs2;               /* Mapping between Interrupt Generation Configuration Set 2 and Interrupt Request;
                                  1h: Interrupt request 0
                                  2h: Interrupt request 1
                                  4h: Interrupt request 2
                                  8h: Interrupt request 3
                                  Note: Interrupt Generation Configuration Set 2 can be mapped to multiple Interrupt
                                  requests simultaneously */
    uint8 igcs3;               /* Mapping between Interrupt Generation Configuration Set 3 and Interrupt Request;
                                  1h: Interrupt request 0
                                  2h: Interrupt request 1
                                  4h: Interrupt request 2
                                  8h: Interrupt request 3
                                  Note: Interrupt Generation Configuration Set 3 can be mapped to multiple Interrupt
                                  requests simultaneously */
} Sac_AlarmConfig;

/* Sac fault indication protocol configuration structure */
typedef struct
{
    Sac_FipFaultDuPre fipFaultDurationPre; /* FIP fault state duration prescaler */
    Sac_FipDynProtoPre fipDynProtoPre;     /* FIP dynamic protocol prescaler */
    Sac_FipMode fipMode;                   /* Fault indication protocol mode */
    uint16 faultStateDurationHigh;         /* FIP fault state duration high, the value range [0,0x3FF] */
} Sac_FipConfig;

/* Sac port control configuration structure */
typedef struct
{
    Sac_PortDir portDir; /* Port direction */
} Sac_PortConfig;

/* SAC module initialization configuration structure */
typedef struct
{
    Sac_FipConfig fipConfig;     /* FIP configuration */
    Sac_AlarmConfig alarmConfig; /* Alarm configuration */
    Sac_PortConfig portConfig;   /* Port configuration */
} Sac_InitConfig;

/* SAC configurate PES structure */
typedef struct
{
    uint8    innerTrigCfg;    /* Seting ICGS0/1/2/3, NMI, RST trigger PES  */
    boolean  fip0TrigEn;      /* En/Disable FIP0 trigger PES, FALSE:Disable, TRUE:Enable */
    boolean  fip0Filter;      /* En/Disable glitch filter FIP0 to PES, FALSE:Disable, TRUE:Enable */
} Sac_PesConfig;

#define SAC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Sac_MemMap.h"
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:    Sac_Register_ReadBack_Check
 * Description: Checks whether the register value written is equal to the value read back 
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       expect: Read back the value of the registe
 *              value: value written to register
 *              state: Wrong initial state
 * Inout:       None
 * Output:      None
 * Return:      boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2025/03/10   01368     create
 *********************************************************************************************************************/ 
LOCAL_FORCEINLINE boolean Sac_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define SAC_REG_CHECK
#if defined(SAC_REG_CHECK)
LOCAL_FORCEINLINE boolean Sac_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
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
LOCAL_FORCEINLINE boolean Sac_Register_ReadBack_Check(boolean state, uint32 value, uint32 expect)
{
    (void)state;
    (void)expect;
    (void)value;

    return state;
}
#endif
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:    Sac_Hal_InitModule
 * Description: This function initializes the Sac module
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       pConfig: Pointer to SAC initialization configuration structure
 * Inout:       None
 * Output:      None
 * Return:      boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:      Note: Once Sac_Hal_LockConfigRegPermanently has been called, the KEYS-protected registers will not be
 *                    writable permanently, so the module initialization configuration needs to be ready before calling
 *                    Sac_Hal_LockConfigRegPermanently.
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern boolean Sac_Hal_InitModule(const Sac_InitConfig  *const pConfig);

/**********************************************************************************************************************
 * Function:    Sac_Hal_SetAlarmAction
 * Description: The purpose of this function is to set the desired alarm action for the group and index specified
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       alarmGroup: Alarm group
 *              alarmIndex: Alarm Index within the requested group
 *              alarmAction: Alarm internal action, interrupt/NMI/Reset/None
 *              fipAction: Fip action, None / Active FIP
 * Inout:       None
 * Output:      None
 * Return:      boolean: FALSE: Register callback detection error, TRUE: Register callback detection is correct
 * Others:      Note: Once Sac_Hal_LockConfigRegPermanently has been called, the KEYS-protected registers will not be
 *                    writable permanently, so the alarm action configuration needs to be ready before calling
 *                    Sac_Hal_LockConfigRegPermanently.
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern boolean Sac_Hal_SetAlarmAction(Sac_AlarmGroup alarmGroup, Sac_AlarmIndex alarmIndex, Sac_AlarmInternalAction alarmAction, Sac_FipAction fipAction);

/**********************************************************************************************************************
 * Function:    Sac_Hal_ReleaseFip
 * Description: The purpose of this function is to turn the FIP into the fault-free state
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       None
 * Inout:       None
 * Output:      None
 * Return:      Sac_CmdExResult: SAC_CMDEXRESULT_SUCCESSFUL: Command executed successfully
 *                               SAC_CMDEXRESULT_FAILED: Command executed failed, or error occurred in parameter check.
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern Sac_CmdExResult Sac_Hal_ReleaseFip(void);

/**********************************************************************************************************************
 * Function:    Sac_Hal_StandbyReleaseFip
 * Description: The purpose of this function is to turn the standby FIP into the fault-free state
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       None
 * Inout:       None
 * Output:      None
 * Return:      Sac_CmdExResult: SAC_CMDEXRESULT_SUCCESSFUL: Command executed successfully
 *                               SAC_CMDEXRESULT_FAILED: Command executed failed, or error occurred in parameter check.
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2024/06/19   00930     create
 *********************************************************************************************************************/
extern Sac_CmdExResult Sac_Hal_StandbyReleaseFip(void);

/**********************************************************************************************************************
 * Function:    Sac_Hal_ActivateRunState
 * Description: The purpose of this function is to switch the Sac state machine from the Start state to the Run state
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       None
 * Inout:       None
 * Output:      None
 * Return:      Sac_CmdExResult: SAC_CMDEXRESULT_SUCCESSFUL: Command executed successfully
 *                               SAC_CMDEXRESULT_FAILED: Command executed failed, or Register callback detection error.       
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern Sac_CmdExResult Sac_Hal_ActivateRunState(void);

/**********************************************************************************************************************
 * Function:    Sac_Hal_TriggerSoftwareAlarm
 * Description: The purpose of this function is to trigger one or more specific alarms in the alarm group 4 by software. 
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       swAlarmNum: Software trigger alarm index within the group 4. 
 * Inout:       None
 * Output:      None
 * Return:      Sac_CmdExResult: SAC_CMDEXRESULT_SUCCESSFUL: Command executed successfully
 *                               SAC_CMDEXRESULT_FAILED: Command executed failed, or error occurred in parameter check.
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern Sac_CmdExResult Sac_Hal_TriggerSoftwareAlarm(Sac_SoftwareAlarm swAlarmNum);

/**********************************************************************************************************************
 * Function:    Sac_Hal_GetAlarmStatus
 * Description: The purpose of this function is to get the alarm status
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       alarmGroup: Alarm group
 *              alarmIndex: Alarm Index within the requested group
 * Inout:       None
 * Output:      None
 * Return:      Sac_AlarmStatus: SAC_ALARMSTATUS_NOTTRIGGERED: Alarm is not triggered
 *                               SAC_ALARMSTATUS_TRIGGERED: Alarm is triggered
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern Sac_AlarmStatus Sac_Hal_GetAlarmStatus(Sac_AlarmGroup alarmGroup, Sac_AlarmIndex alarmIndex);

/**********************************************************************************************************************
 * Function:    Sac_Hal_ClearAlarmStatus
 * Description: The purpose of this function is to clear alarm status of the requested alarm
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       alarmGroup: Alarm group
 *              alarmIndex: Alarm Index within the requested group
 * Inout:       None
 * Output:      None
 * Return:      Sac_CmdExResult: SAC_CMDEXRESULT_SUCCESSFUL: Command executed successfully
 *                               SAC_CMDEXRESULT_FAILED: Command executed failed, or error occurred in parameter check.
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern Sac_CmdExResult Sac_Hal_ClearAlarmStatus(Sac_AlarmGroup alarmGroup, Sac_AlarmIndex Index);

/**********************************************************************************************************************
 * Function:    Sac_Hal_GetAlarmExecutionStatus
 * Description: The purpose of this function is to get the status of the alarm reactions executed
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       alarmEx: Alarm execution status
 * Inout:       None
 * Output:      None
 * Return:      Sac_AlarmExStatus: SAC_ALARMEXSTATUS_NOREQSERORNOEVENTMISSED: No request was serviced or no alarm event missed
 *                                 SAC_ALARMEXSTATUS_REQSEROREVENTMISSED: Request was serviced or at least one alarm event missed
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern Sac_AlarmExStatus Sac_Hal_GetAlarmExecutionStatus(Sac_AlarmExecutionStatus alarmEx);

/**********************************************************************************************************************
 * Function:    Sac_Hal_ClearAlarmExecutionStatus
 * Description: The purpose of this function is to clear the status of the alarm reactions executed
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       alarmEx: Alarm execution status
 * Inout:       None
 * Output:      None
 * Return:      boolean: Indicates whether the check for register value passes
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern boolean Sac_Hal_ClearAlarmExecutionStatus(Sac_AlarmExecutionStatus alarmEx);

/**********************************************************************************************************************
 * Function:    Sac_Hal_GetSacState
 * Description: The purpose of this function is to get the current state of Sac
 * Sync/Async:  Synchronous
 * Reentrancy:  Reentrant
 * Input:       None
 * Inout:       None
 * Output:      None
 * Return:      Sac_State: SAC_STATE_START: Sac state is Start
 *                         SAC_STATE_RUN: Sac state is Run
 *                         SAC_STATE_FAULT: Sac state is Fault
 *                         SAC_STATE_RUNPRE: Sac state is Runpre
 * Others:      None
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern Sac_State Sac_Hal_GetSacState(void);

/**********************************************************************************************************************
 * Function:    Sac_Hal_LockConfigRegPermanently
 * Description: The purpose of this function is to lock config register permanently
 * Sync/Async:  Synchronous
 * Reentrancy:  Non-Reentrant
 * Input:       None
 * Inout:       None
 * Output:      None
 * Return:      boolean: Indicates whether the check for register value passes
 * Others:      Note: Call this function when Sac_Hal_InitMoudle and Sac_Hal_SetAlarmAction have been called and no
 *                    further configuration of SAC control registers is needed, to permanently lock the protected
 *                    registers.
 * History:
 * Date         Author    Modified
 * 2023/06/05   00977     create
 *********************************************************************************************************************/
extern boolean Sac_Hal_LockConfigRegPermanently(void);

/**********************************************************************************************************************
 * Function:    Sac_Hal_CommandExcute
 * Description: The purpose of this function is to execute SAC command to control SAC enter different state machine
 * Input:       command: Sac command 
 *              argVal: Auxiliary parameters corresponding to the command
 * Output:      N/A
 * Return:      Sac_CmdExResult:
 *              SAC_CMDEXRESULT_SUCCESSFUL: Command executed successfully
 *              SAC_CMDEXRESULT_FAILED: Command executed failed
 * Others:      Note: The API does not perform validity check for the parameter 'argVal'.
 *                    The input value range of 'argVal', please refer to the annotations of Enumeration Sac_Command.
 * History:     N/A
 * Date         Author    Modified
 * 2026/01/22   01368     create
 *********************************************************************************************************************/
Sac_CmdExResult Sac_Hal_CommandExcute(Sac_Command command, uint8 argVal);

/**********************************************************************************************************************
 * Function:    Sac_Hal_SetPesAction
 * Description: The purpose of this function is to configure SAC post-processing whether tirgger PES(ES) related function 
 * Input:       pPesConfig: The structure about configure en/disable whether SAC post-processing trigger PES
 * Output:      N/A
 * Return:      boolean: Indicates whether the check for register value passes
 * Others:      N/A
 * History:     N/A
 * Date         Author    Modified
 * 2026/01/22   01368     create
 *********************************************************************************************************************/
boolean Sac_Hal_SetPesAction(const Sac_PesConfig *const pPesConfig);


#define SAC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Sac_MemMap.h"
#endif /* SAC_HAL_H_ */

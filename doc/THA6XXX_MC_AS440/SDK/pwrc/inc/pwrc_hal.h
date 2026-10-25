/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: pwrc_hal.h
 * Author:   00930
 * Version:  V1.2.0
 * Date:     2026/02/28
 * Description: PWRC hardware abstraction layer header file.
 *              This file contains function prototypes for PWRC module hardware abstraction layer.
 *********************************************************************************************************************/

/**********************************************************************************************************************
**                          Codeing Rule Violations                                                                  **
**********************************************************************************************************************/
/*
*#Violation Summary
*#pwrc_hal_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#pwrc_hal_h_REF_2:MISRAC2012-Dir-4.8; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*/

#ifndef PWRC_HAL_H_
#define PWRC_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "port_hal.h"
#include "tha6_cfg.h"
#include "pwrc_register.h"
#include "compilertypes.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */

/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/
/* Voltage monitor type */
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGE_VEXT         (0x0001U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGE_VDDP3        (0x0002U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGE_VDD          (0x0004U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGE_VEVRSB       (0x0008U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGE_VDDSB        (0x0010U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGE_VDDM         (0x0020U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGE_VEXT          (0x0100U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGE_VDDP3         (0x0200U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGE_VDD           (0x0400U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGE_VEVRSB        (0x0800U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGE_VDDSB         (0x1000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGE_VDDM          (0x2000U)

/* Current and voltage alarm real time status */
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_RT_VEXT    (0x000001U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_RT_VDDP3   (0x000002U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_RT_VDD     (0x000004U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_RT_VEVRSB  (0x000008U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_RT_VDDSB   (0x000010U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_RT_VDDM    (0x000020U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_RT_VEXT     (0x000100U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_RT_VDDP3    (0x000200U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_RT_VDD      (0x000400U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_RT_VEVRSB   (0x000800U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_RT_VDDSB    (0x001000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_RT_VDDM     (0x002000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERCURRENTALM_RT_VDD      (0x020000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_SHORTCIRCUITALM_RT_VDD     (0x040000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERCURRENTALM_RT_VDDP3    (0x080000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_SHORTCIRCUITALM_RT_VDDP3   (0x100000U)

/* Current and voltage alarm */
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_VEXT       (0x000001U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_VDDP3      (0x000002U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_VDD        (0x000004U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_VEVRSB     (0x000008U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_VDDSB      (0x000010U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_UNDERVOLTAGEALM_VDDM       (0x000020U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_VEXT        (0x000100U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_VDDP3       (0x000200U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_VDD         (0x000400U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_VEVRSB      (0x000800U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_VDDSB       (0x001000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERVOLTAGEALM_VDDM        (0x002000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERCURRENTALM_VDD         (0x010000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_SHORTCIRCUITALM_VDD        (0x020000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_OVERCURRENTALM_VDDP3       (0x040000U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_SHORTCIRCUITALM_VDDP3      (0x080000U)

/* CPU low power mode status */
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_CPU0_WFI    (0x01U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_CPU0_WFE    (0x02U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_CPU1_WFI    (0x04U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_CPU1_WFE    (0x08U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_CPU2_WFI    (0x10U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_CPU2_WFE    (0x20U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_CPU3_WFI    (0x40U)
/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_CPU3_WFE    (0x80U)

/* #Violation: pwrc_hal_h_REF_1*/
#define PWRC_CPU_ALL_ACTIVE (0x00U)

/* Define PWRC Standby wake-up source status */
/*WAKEUPSOURCE: bit[9:0] for WKUPSTS[9:0], bit9 reserved, bit[31:11] for STIOWKUSTS[20:0]*/
/* WKUPSTS register */
/* #Violation: pwrc_hal_h_REF_1*/
#define    PWRC_WAKEUPSOURCE_ESR0     (0x01U)     /* ESR0 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/
#define    PWRC_WAKEUPSOURCE_ESR1     (0x02U)     /* ESR1 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/
#define    PWRC_WAKEUPSOURCE_PINA     (0x04U)     /* PINA as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/
#define    PWRC_WAKEUPSOURCE_PINB     (0x08U)     /* PINB as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/
#define    PWRC_WAKEUPSOURCE_PORST    (0x20U)     /* PORST as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/
#define    PWRC_WAKEUPSOURCE_VEXT     (0x80U)     /* VEXT as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/
#define    PWRC_STANDBY_FLAG          (0x200U)    /* Standby flag: has entered standby mode */

/* STIOWKUSTS register */
/* #Violation: pwrc_hal_h_REF_1*/
#define    PWRC_WAKEUPSOURCE_P34_01   (0x800U)      /* P34_01 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/    
#define    PWRC_WAKEUPSOURCE_P34_02   (0x1000U)     /* P34_02 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/       
#define    PWRC_WAKEUPSOURCE_P34_03   (0x2000U)     /* P34_03 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/       
#define    PWRC_WAKEUPSOURCE_P34_04   (0x4000U)     /* P34_04 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/       
#define    PWRC_WAKEUPSOURCE_P34_05   (0x8000U)     /* P34_05 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/    
#define    PWRC_WAKEUPSOURCE_P33_00   (0x10000U)    /* P33_00 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/      
#define    PWRC_WAKEUPSOURCE_P33_01   (0x20000U)    /* P33_01 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/      
#define    PWRC_WAKEUPSOURCE_P33_02   (0x40000U)    /* P33_02 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/      
#define    PWRC_WAKEUPSOURCE_P33_03   (0x80000U)    /* P33_03 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/    
#define    PWRC_WAKEUPSOURCE_P33_04   (0x100000U)   /* P33_04 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/     
#define    PWRC_WAKEUPSOURCE_P33_05   (0x200000U)   /* P33_05 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/     
#define    PWRC_WAKEUPSOURCE_P33_06   (0x400000U)   /* P33_06 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/     
#define    PWRC_WAKEUPSOURCE_P33_07   (0x800000U)   /* P33_07 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/     
#define    PWRC_WAKEUPSOURCE_P33_08   (0x1000000U)  /* P33_08 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/    
#define    PWRC_WAKEUPSOURCE_P33_09   (0x2000000U)  /* P33_09 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/    
#define    PWRC_WAKEUPSOURCE_P33_10   (0x4000000U)  /* P33_10 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/    
#define    PWRC_WAKEUPSOURCE_P33_11   (0x8000000U)  /* P33_11 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/  
#define    PWRC_WAKEUPSOURCE_P33_13   (0x20000000U) /* P33_13 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/   
#define    PWRC_WAKEUPSOURCE_P33_14   (0x40000000U) /* P33_14 as wake-up source for standby mode */
/* #Violation: pwrc_hal_h_REF_1*/   
#define    PWRC_WAKEUPSOURCE_P33_15   (0x80000000U) /* P33_15 as wake-up source for standby mode */

/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                         Global Pointer Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                           Global Enumeration Definitions
 *********************************************************************************************************************/
/* Define the PWRC function enable type */
typedef enum
{
    PWRC_FUNCTION_DISABLE = 0U, /* Function is disabled */
    PWRC_FUNCTION_ENABLE        /* Function is enabled */
} Pwrc_FunctionEnable;

/* Select the voltage supply Type */
typedef enum
{
    PWRC_VOLTAGEMONITOR_VEXT = 0U,  /* Select VEXT supply voltage monitoring */
    PWRC_VOLTAGEMONITOR_VDDP3,      /* Select VDDP3 supply voltage monitoring */
    PWRC_VOLTAGEMONITOR_VDD,        /* Select VDD supply voltage monitoring */
    PWRC_VOLTAGEMONITOR_VEVRSB,     /* Select VEVRSB supply voltage monitoring */
    PWRC_VOLTAGEMONITOR_VDDSB,      /* Select VDDSB supply voltage monitoring  */
    PWRC_VOLTAGEMONITOR_VDDM        /* Select VDDM supply voltage monitoring */
} Pwrc_VoltageMonitor;

/* Select voltage monitor threshold level */
typedef enum
{
    PWRC_VOLTAGETHRESHOLD_LEVEL0 = 0U,  /* Voltage threshold level 0 for vext/vdd/vevrsb/vdd/vddsb/vddp3 */
    PWRC_VOLTAGETHRESHOLD_LEVEL1,       /* Voltage threshold level 1 for vext/vdd/vevrsb/vdd/vddsb/vddp3 */
    PWRC_VOLTAGETHRESHOLD_LEVEL2,       /* Voltage threshold level 2 for vext/vdd/vevrsb/vdd/vddsb/vddp3 */
    PWRC_VOLTAGETHRESHOLD_LEVEL3,       /* Voltage threshold level 3 for vext/vdd/vevrsb/vdd/vddsb/vddp3 */
    PWRC_VOLTAGETHRESHOLD_LEVEL4,       /* Voltage threshold level 4 just for vext/vdd/vevrsb/vdd/vddsb */
    PWRC_VOLTAGETHRESHOLD_LEVEL5,       /* Voltage threshold level 5 just for vext/vdd/vevrsb/vdd/vddsb */
    PWRC_VOLTAGETHRESHOLD_LEVEL6,       /* Voltage threshold level 6 just for vext/vdd/vevrsb/vdd/vddsb */
    PWRC_VOLTAGETHRESHOLD_LEVEL7,       /* Voltage threshold level 7 just for vext/vdd/vevrsb/vdd/vddsb */
} Pwrc_VoltageThreshold;

/* Define PWRC Standby Domain standby wake-up source */
typedef enum
{
    PWRC_STBWAKEUPSOURCE_ESR0 = 0U,    /* ESR0 as wake-up source for standby mode */
    PWRC_STBWAKEUPSOURCE_ESR1 = 1U,    /* ESR1 as wake-up source for standby mode */
    PWRC_STBWAKEUPSOURCE_PINA = 2U,    /* PINA as wake-up source for standby mode */
    PWRC_STBWAKEUPSOURCE_PINB = 3U,    /* PINB as wake-up source for standby mode */
    PWRC_STBWAKEUPSOURCE_PORST = 5U,   /* PORST as wake-up source for standby mode */
    PWRC_STBWAKEUPSOURCE_VEXT = 7U,    /* VEXT as wake-up source for standby mode */
    PWRC_STBWAKEUPSOURCE_P33_00 = 32U, /* P33_00 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_01,       /* P33_01 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_02,       /* P33_02 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_03,       /* P33_03 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_04,       /* P33_04 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_05,       /* P33_05 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_06,       /* P33_06 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_07,       /* P33_07 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_08,       /* P33_08 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_09,       /* P33_09 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_10,       /* P33_10 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_11,       /* P33_11 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_13 = 45U, /* P33_07 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_14,       /* P33_14 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P33_15,       /* P33_15 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P34_01 = 64U, /* P34_01 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P34_02,       /* P34_02 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P34_03,       /* P34_03 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P34_04,       /* P34_04 as wake-up source for standby mode, only THA6412 support */
    PWRC_STBWAKEUPSOURCE_P34_05,       /* P34_05 as wake-up source for standby mode, only THA6412 support */
} Pwrc_StbWakeupSource;

/* Define PWRC Standby Domain wake-up pin edge for standby mode */
typedef enum
{
    PWRC_STBWAKEUPPINEDGE_NONE = 0U,    /* No pin edge wake up standby mode */
    PWRC_STBWAKEUPPINEDGE_RISING,       /* Rising pin edge wake up standby mode */
    PWRC_STBWAKEUPPINEDGE_FALLING,      /* Falling pin edge wake up standby mode */
    PWRC_STBWAKEUPPINEDGE_RISINGFALLING /* Rising and falling pin edge wake up standby mode */
} Pwrc_StbWakeupPinEdge;

/* Define the PWRC current monitoring type */
typedef enum
{
    PWRC_CURRENTMONITOR_OVERCURRENT = 1U,        /* PWRC overcurrent monitor */
    PWRC_CURRENTMONITOR_SHORTCIRCUIT,            /* PWRC short circuit monitor */
    PWRC_CURRENTMONITOR_OVERCURRENT_SHORTCIRCUIT /* PWRC short circuit and overcurrent monitor */
} Pwrc_CurrentMonitor;

/* Define the PWRC low power mode */
typedef enum
{
    PWRC_LOWPOWERMODE_SLEEP = 0U, /* PWRC sleep mode  */
    PWRC_LOWPOWERMODE_STANDBY     /* PWRC standby mode */
} Pwrc_LowpowerMode;
/**********************************************************************************************************************
 *                                              Global Union Definitions
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
/* Structure for standby source configuration, default:digital filter all enable */
/* #Violation: pwrc_hal_h_REF_2*/
typedef struct
{
    Pwrc_StbWakeupSource wakeupSource;   /* Specifies wake-up source for standby mode */
    Pwrc_StbWakeupPinEdge pinWakeupEdge; /* Specifies pin edge wake-up mode for standby mode */
} Pwrc_StandbySourceConfig;

/**********************************************************************************************************************
 *                                        Global Inline Function Declaration
 *********************************************************************************************************************/
#define PWRC_START_SEC_CODE_ASIL_D_GLOBAL
#include "Pwrc_MemMap.h"

/**********************************************************************************************************************
 * Function:     Pwrc_Register_ReadBack_Check
 * Description:  Register read back check
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        state: Original state
 *               expect: The value expected to be written
 *               value: The value actually written
 * Inout:        None
 * Output:       None
 * Return:       boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2025/03/10    01369     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Pwrc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value);
/**********************************************************************************************************************
 *                                         Global Inline Function Definitions
 *********************************************************************************************************************/
#define PWRC_REG_CHECK
#if defined(PWRC_REG_CHECK)
LOCAL_FORCEINLINE boolean Pwrc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
{
    boolean ret;

    ret = state;
    if (expect != value)
    {
        ret = FALSE;
    }

    return ret;
}
#else
LOCAL_FORCEINLINE boolean Pwrc_Register_ReadBack_Check(boolean state, uint32 expect, uint32 value)
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
 * Function: Pwrc_Hal_SetSecondaryVoltageMonitor
 * Description: The function shall enable or disable secondary voltage monitoring
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: voltageMonitorEnable: Enable the voltage monitoring when the relevant bit .
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_SetSecondaryVoltageMonitor(uint32 voltageMonitorEnable);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_SetSecondaryVoltageThreshold
 * Description: The function shall set secondary voltage monitoring threshold level
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: monitorVoltage: Specified the supply which be monitored.
 *        coarseGrade: Coarse voltage threshold grade
 *        fineGrade: fine voltage threshold grade
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13    00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_SetSecondaryVoltageThreshold(Pwrc_VoltageMonitor monitorVoltage, Pwrc_VoltageThreshold coarseGrade, Pwrc_VoltageThreshold fineGrade);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_GetCurVltAlmRealtimeStatus
 * Description: The function shall get current and voltage alarm real time status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: none
 * Inout:  None
 * Output: none
 * Return: uint32: Current and voltage alarm real time status(one bit indicate one alarm's status)
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern uint32 Pwrc_Hal_GetCurVltAlmRealtimeStatus(void);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_SetCurVltAlarm
 * Description: The function shall set current and voltage monitoring output alarm
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: curVltAlmEnable: The current and voltage alarm is enable when the relevant bit is set
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_SetCurVltAlarm(uint32 curVltAlmEnable);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_SetCurVltInterrupt
 * Description: The function shall set current and voltage monitoring output interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: curVltIntEnable: The current and voltage interrupt is enable when the relevant bit is set
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_SetCurVltInterrupt(uint32 curVltIntEnable);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_GetCurVltAlarmStatus
 * Description: The function shall get current and voltage alarm status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input: none
 * Inout:  None
 * Output: none
 * Return: uint32: Current and voltage alarm status(one bit indicate one alarm's status,1-alarm state)
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern uint32 Pwrc_Hal_GetCurVltAlarmStatus(void);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_ClearCurVltAlarmStatus
 * Description: The function shall clear current and voltage alarm status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: alarmStatus: if the according bits are 1, the alarm status will be clear
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_ClearCurVltAlarmStatus(uint32 alarmStatus);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_SetDsadcRefCurrent
 * Description: The function shall enable or disable DSADC reference current
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  functionEnable: Function is enable or disable
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
extern boolean Pwrc_Hal_SetDsadcRefCurrent(Pwrc_FunctionEnable functionEnable);
#endif/* THA6_THA6412, THA6_THA6206, THA6_THA6206D */

/**********************************************************************************************************************
 * Function: Pwrc_Hal_GetCpuRealtimeStatus
 * Description: The function shall get cpu real time status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:  none
 * Inout:  None
 * Output: none
 * Return: uint32: Cpu real time status
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern uint32 Pwrc_Hal_GetCpuRealtimeStatus(void);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_SetLowPowerInterrupt
 * Description: The function shall enable or disable cpu low power mode interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  lowPowerInterrupt: The Cpu low power interrupt is enable when the according bit is set
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_SetLowPowerInterrupt(uint32 lowPowerInterrupt);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_GetLowPowerIntStatus
 * Description: The function shall get cpu low power interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:  none
 * Inout:  None
 * Output: none
 * Return: uint32: Cpu low power interrupt status(one bit indicate one interrupt's status,1-interrupt state)
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern uint32 Pwrc_Hal_GetLowPowerIntStatus(void);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_ClearLowPowerIntStatus
 * Description: The function shall clear cpu low power interrupt status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:  lowPowerStatus: cpu low power interrupt status(if the according bits are 1, the alarm status will be clear)
 * Inout:  None
 * Output: none
 * Return: none
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern void Pwrc_Hal_ClearLowPowerIntStatus(uint32 lowPowerStatus);

/**********************************************************************************************************************
 *
 * Function: Pwrc_Hal_SetLowpowerMode
 * Description: The function shall set low power mode: sleep or standby mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  lowpowerMode: PWRC low power mode
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_SetLowpowerMode(Pwrc_LowpowerMode lowpowerMode);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_InitStandbyMode
 * Description: The function shall initialize standby mode
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  standbySourceConfig[]: The structure array for standby mode configuration
 *         wakeupSourceCount: The wakeupSource counter to be initialized
 *         standbyDelay: Specifies delay time before chip enter into standby mode, delay = (standbyDelay * 8) *0.25us
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_InitStandbyMode(const Pwrc_StandbySourceConfig standbySourceConfig[], uint8 wakeupSourceCount, uint8 standbyDelay);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_GetStbWakeupSource
 * Description: The function shall get standby wakeup source.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:  none
 * Inout:  None
 * Output: none
 * Return: uint32: wake-up source, from bit0~bit7,except bit4,one bit indicate one wake up source
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern uint32 Pwrc_Hal_GetStbWakeupSource(void);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_ClearStbWakeupSource
 * Description: The function shall clear standby wakeup source
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input: wakeupSource: if the according bits are 1, the wakeup source will be clear
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_ClearStbWakeupSource(uint32 wakeupSource);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_SetStbEvrcCurrentMonitor
 * Description: The function shall enable or disable EVRC current monitoring,
 *                 the monitoring is only for EVRC which is produced internally.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  monitorType: Current monitor type
 *         functionEnable: Function is enable or disable
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_SetStbEvrcCurrentMonitor(Pwrc_CurrentMonitor monitorType, Pwrc_FunctionEnable functionEnable);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_SetStbEvr33CurrentMonitor
 * Description: The function shall enable or disable EVR33 current monitoring,
 *                 the monitoring is only for EVR33 which is produced internally.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  monitorType: Current monitor type
 *         functionEnable: Function is enable or disable
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
extern boolean Pwrc_Hal_SetStbEvr33CurrentMonitor(Pwrc_CurrentMonitor monitorType, Pwrc_FunctionEnable functionEnable);

/**********************************************************************************************************************
 * Function: Pwrc_Hal_SetStbEvrcSpreadSpectrum
 * Description: The function shall set EVRC spread spectrum mode,
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  spreadSpectrumCycle: Spread spectrum cycle
 *         functionEnable: Function is enable or disable
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2024/03/13   00930     create
 *********************************************************************************************************************/
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
extern boolean Pwrc_Hal_SetStbEvrcSpreadSpectrum(uint8 spreadSpectrumCycle, Pwrc_FunctionEnable functionEnable);
#endif /* THA6_THA6412, THA6_THA6206, THA6_THA6206D */

/**********************************************************************************************************************
 * Function: Pwrc_Hal_SetStandbyModeEntryIndication
 * Description: This function is used to set the indication for the chip entering standby mode. 
 *              When enabled, it indicates whether the chip has entered standby mode via the P33.3 pin; 
 *              otherwise, it does so via the PORST pin.
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:  functionEnable: Function is enable or disable
 * Inout:  None
 * Output: none
 * Return: boolean: TRUE: Register read back check correct, FALSE: Register read back check incorrect
 * Others:
 * Date         Author   Modified
 * 2025/08/01   01358     create
 *********************************************************************************************************************/
#if defined(THA6_THA6104)
extern boolean Pwrc_Hal_SetStandbyModeEntryIndication(Pwrc_FunctionEnable functionEnable);
#endif

#define PWRC_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Pwrc_MemMap.h"

#endif /* PWRC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

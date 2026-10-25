/**********************************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName:    gipc_hal.h
 * Author:      01200
 * Version:     V1.2.0
 * Date:        2026/02/28
 * Description: This file contains all data type definitions and function declarations of interfaces.
 *********************************************************************************************************************/
/*
*#Violation Summary
*
*#gipc_hal_h_REF_1:MISRAC2012-Dir-1.1; 
* Justification: Inline assembly for CPU-specific operations.
*
*#gipc_hal_h_REF_2:MISRAC2012-Dir-4.8; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#gipc_hal_h_REF_3:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity.
*
*#gipc_hal_h_REF_4:MISRAC2012-Dir-2.7;
* Justification: Parameters are used by assembly code.
*
*#gipc_hal_h_REF_5:CertC-DCL00-C; 
* Justification: Inline assembly for CPU-specific operations.
*
*#gipc_hal_h_REF_6:MISRAC2012-Rule-1.2; 
* Justification: Inline assembly for CPU-specific operations.
*
*#gipc_hal_h_REF_7:MISRAC2012-Dir-4.2;
* Justification: Inline assembly for CPU-specific operations.
*
*#gipc_hal_h_REF_8:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#gipc_hal_h_REF_9:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*#gipc_hal_h_REF_10:MISRAC2012-Rule-20.1; 
*Justification:AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*#gipc_hal_h_REF_11:MISRAC2012-Rule-10.5;
*Justification:Limitation of Cortex-R52+ Core; Boolean can only be representes as uint8.
*
*/
#ifndef GIPC_HAL_H_
#define GIPC_HAL_H_
/**********************************************************************************************************************
 *                                                     Includes
 *********************************************************************************************************************/
#include "common_hal.h"
#include "Platform_Types.h"
#include "gipc_register.h"
#include "multicore.h"
#include "tha6_cfg.h"
#if(INPUT_ARG_DETECT == STD_ON)
#include "dev.h"
#endif /* INPUT_ARG_DETECT */
/**********************************************************************************************************************
 *                                             Global Macro Definitions
 *********************************************************************************************************************/

/* Core0 FSM monitor alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FMALM0           (0x1U)

/* Core1 FSM monitor alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FMALM1           (0x2U)

/* Core2 FSM monitor alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FMALM2           (0x4U)

/* Core3 FSM monitor alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FMALM3           (0x8U)

/* Core0 FSM plausibility check alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FPCALM0          (0x10U)

/* Core1 FSM plausibility check alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FPCALM1          (0x20U)

/* Core2 FSM plausibility check alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FPCALM2           (0x40U)

/* Core3 FSM plausibility check alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FPCALM3           (0x80U)

/* AXI addr logic redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_AARALM           (0x100U)

/* AXI addr channel protection code alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_AACPCALM         (0x200U)

/* E redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_EALM             (0x400U)

/* SE redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_SEALM            (0x800U)

/* ERG redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_ERGALM           (0x1000U)

/* FSMSTSCLR0 redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FSMSTSCLRALM0    (0x2000U)

/* FSMSTSCLR1 redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FSMSTSCLRALM1    (0x4000U)

/* FSMSTSCLR2 redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FSMSTSCLRALM2    (0x8000U)

/* FSMSTSCLR3 redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_FSMSTSCLRALM3    (0x10000U)

/* PPICTRL0 redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_PPICTRLALM0     (0x20000U)

/* PPICTRL1 redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_PPICTRLALM1     (0x40000U)

/* PPICTRL2 redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_PPICTRLALM2     (0x80000U)

/* PPICTRL3 redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_PPICTRLALM3     (0x100000U)

/* SAFEFAULT redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_SAFEFAULTALM    (0x200000U)

/* SAFEEN redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_SAFEENALM       (0x400000U)

/* ALARMCLR redundancy alarm */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_ALARMCLRALM     (0x800000U)

/* All alarm mask */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALL_ALARM_MASK        (0xFFFFFFU)


/* FSM monitor alarm clear */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_TYPE_FMALMC     (0x3U)

/* FSM plausibility check alarm clear */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_TYPE_FPCALMC    (0xCU)

/* AXI addr logic redundancy alarm clear */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_TYPE_AARALMC    (0x30U)

/* AXI addr channel protection code alarm clear */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_TYPE_AACPCALMC  (0xC0U)

/* E/SE alarm clear */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_TYPE_ESEALMC    (0x300U)

/* DFF redundancy alarm clear */
/* #Violation: gipc_hal_h_REF_9 */
#define GIPC_ALARM_TYPE_DRALMC     (0xC00U)
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
/* Structure for lock of GIPC */
/* #Violation: gipc_hal_h_REF_2 */
/* #Violation: gipc_hal_h_REF_8 */
typedef struct __attribute__((aligned(64)))
{
    uint32 lockStatus;  /* Lock of GIPC. 0: Unlocked; 1: Locked */
    uint32 reserved[15]; /* Reserved to ensure that the size of structure conforms to marked address size(64 Bytes). */
} Gipc_Lock;
/**********************************************************************************************************************
 *                                            Global Variable Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 *                                        Global Inline Function Declarations
 *********************************************************************************************************************/

#define GIPC_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gipc_hal_h_REF_10 */
#include "Gipc_MemMap.h"


/**********************************************************************************************************************
 * Function:     Gipc_Hal_ExclusiveWrite
 * Description:  Exclusive write a value in a specific address
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pAddr: Address to write to
 *               sourceValue: Value to be written to specified address
 * Inout:        None
 * Output:       None
 * Return:       boolean: Flag to indicate if the exclusive access is successful.
 * Others:       pAddr must be 16Bytes aligned
 * History:
 *  Date          Author    Modified
 *  2023/07/18    01200     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gipc_Hal_ExclusiveWrite(const uint32 *pAddr, uint32 sourceValue);
/**********************************************************************************************************************
 * Function:     Gipc_Hal_GetLock
 * Description:  Try to get the specified lock
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pLock: Index of lock
 * Inout:        None
 * Output:       None
 * Return:       boolean: Flag indicating whether the lock acquisition was successful.
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/26    01200     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE boolean Gipc_Hal_GetLock(const Gipc_Lock *pLock);
/**********************************************************************************************************************
 * Function:     Gipc_Hal_ReleaseLock
 * Description:  Try to release the specified lock
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pLock: Index of lock
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/26    01200     Create
 *********************************************************************************************************************/
LOCAL_FORCEINLINE void Gipc_Hal_ReleaseLock(const Gipc_Lock *pLock);


/* #Violation: gipc_hal_h_REF_3 */
/* #Violation: gipc_hal_h_REF_4 */
 LOCAL_FORCEINLINE boolean Gipc_Hal_ExclusiveWrite(const uint32 *pAddr, uint32 sourceValue)
{
    boolean result;

#if(INPUT_ARG_DETECT == STD_ON)
    /* pAddr cannot be null pointer */
    /* #Violation: gipc_hal_h_REF_5 */
    /* #Violation: gipc_hal_h_REF_11 */
    Assert((boolean)(NULL_PTR != pAddr));
#endif /* INPUT_ARG_DETECT */

    /* Exclusive write sourceValue to pAddr */
    /* #Violation: gipc_hal_h_REF_6 */
    ASM_VOLATILE(" ldrex r2, [%1]                    \n"
                 " dsb                               \n"
                 " strex r2, %2, [%1]                \n"
                 " dsb                               \n"
                 " eor %0, r2, #1                    \n"
                 : "=&r"(result), "+r"(pAddr)
                 : "r"(sourceValue)
                 : "memory", "r2");

    return result;
}

/* #Violation: gipc_hal_h_REF_3 */
/* #Violation: gipc_hal_h_REF_4 */
LOCAL_FORCEINLINE boolean Gipc_Hal_GetLock(const Gipc_Lock *pLock)
{
    /* #Violation: gipc_hal_h_REF_5 */
    boolean result;

#if(INPUT_ARG_DETECT == STD_ON)
    /* pAddr cannot be null pointer */
    /* #Violation: gipc_hal_h_REF_5 */
    /* #Violation: gipc_hal_h_REF_11 */
    Assert((boolean)(NULL_PTR != pLock));
#endif /* INPUT_ARG_DETECT */

    result = FALSE;

    /* Try to get lock */
    /* #Violation: gipc_hal_h_REF_1 */
    /* #Violation: gipc_hal_h_REF_6 */
    /* #Violation: gipc_hal_h_REF_7 */
    ASM_VOLATILE(
                " mov r1, #1                \n" /* 1: Locked */
                " ldrex r2, [%1]            \n" /* If is unlocked, lock it */
                " cmp r2, r1                \n" /* Check if lock is locked */
#ifdef __TASKING__
                " beq 1n                    \n" /* If is locked, return fail */
#else
                " beq 1f                    \n" /* If is locked, return fail */
#endif
                " dsb                       \n"
                " strex r2, r1, [%1]        \n"
                " dsb                       \n"
                "1: eor %0, r2, #1         \n" /* Write !r2 to result. */
                : "=&r"(result), "+r"(pLock)::"cc", "memory", "r1", "r2");


    return result;
}

/* #Violation: gipc_hal_h_REF_3 */
/* #Violation: gipc_hal_h_REF_4 */
LOCAL_FORCEINLINE void Gipc_Hal_ReleaseLock(const Gipc_Lock *pLock)
{
#if(INPUT_ARG_DETECT == STD_ON)
    /* pAddr cannot be null pointer */
    /* #Violation: gipc_hal_h_REF_5 */
    /* #Violation: gipc_hal_h_REF_11 */
    Assert((boolean)(NULL_PTR != pLock));
#endif /* INPUT_ARG_DETECT */
    /* Release lock */
    /* #Violation: gipc_hal_h_REF_6 */
    ASM_VOLATILE(
                "1:ldrex r1, [%0]             \n"
                " cmp r1, #1                  \n"
#ifdef __TASKING__
                " bne 2n                      \n"
#else
                " bne 2f                      \n"
#endif
                " mov r1, #0                  \n"
                " dsb                         \n"
                " strex r2, r1, [%0]          \n"
                " dsb                         \n"
                " cmp r2, #0                  \n"
#ifdef __TASKING__
                " bne 1p                      \n"
#else
                " bne 1b                      \n"
#endif
                "2:                           \n"
                : "+r"(pLock)::"cc", "memory", "r0", "r1", "r2");

}
/**********************************************************************************************************************
 *                                            Global Function Declarations
 *********************************************************************************************************************/
/**********************************************************************************************************************
 * Function:     Gipc_Hal_SendNotification
 * Description:  Notify specified core by interrupt
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant(If calling this function is for operations on different GIPC module, this function is a reentrant function; 
 *               in other cases, it is a non-reentrant function)
 * Input:        pGipc: Pointer to GIPC module
 *               targetCoreID: The target to which the interrupt is sent
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/18    01200     Create
 *  2024/07/17    01254     Add GIPC module input
 *********************************************************************************************************************/
extern void Gipc_Hal_SendNotification(GIPC_MODULE *const pGipc, MultiCoreID targetCoreID);
/**********************************************************************************************************************
 * Function:     Gipc_Hal_ClearInterruptFlag
 * Description:  Clear the flag of the interrupt sent by a core.
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pGipc: Pointer to GIPC module
 *               sourceCoreID: The source core of the interrupt to be cleared
 * Inout:        None
 * Output:       None
 * Return:       None
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/18    01200     Create
 *  2024/07/17    01254     Add GIPC module input
 *********************************************************************************************************************/
extern void Gipc_Hal_ClearInterruptFlag(GIPC_MODULE *const pGipc, MultiCoreID sourceCoreID);
/**********************************************************************************************************************
 * Function:     Gipc_Hal_GetAlarmStatus
 * Description:  Get the sac alarm status
 * Sync/Async:   Synchronous
 * Reentrancy:   Reentrant
 * Input:        pGipc: Pointer to GIPC module
 *               alarm: Alarm that GIPC will report to SAC.
 * Inout:        None
 * Output:       None
 * Return:       uint32: Flag to indicate every alarm is set or reset
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/18    01200     Create
 *  2024/07/17    01254     Add GIPC module input
 *********************************************************************************************************************/
extern uint32 Gipc_Hal_GetAlarmStatus(const GIPC_MODULE *const pGipc, uint32 alarm);
/**********************************************************************************************************************
 * Function:     Gipc_Hal_ClearAlarmStatus
 * Description:  Clear the specified sac alarm status
 * Sync/Async:   Synchronous
 * Reentrancy:   Non-Reentrant
 * Input:        pGipc: Pointer to GIPC module
 *               alarmTypeb: Alarm that GIPC will be cleared.
 * Inout:        None
 * Output:       None
 * Return:       boolean:
 *                 TRUE: SE unlock/lock success
 *                 FALSE: SE unlock/lock fail
 * Others:       None
 * History:
 *  Date          Author    Modified
 *  2023/07/18    01200     Create
 *  2024/07/17    01254     Add GIPC module input
 *********************************************************************************************************************/
extern boolean Gipc_Hal_ClearAlarmStatus(GIPC_MODULE *const pGipc, uint32 alarmType);


#define GIPC_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: gipc_hal_h_REF_10 */
#include "Gipc_MemMap.h"

#endif /* GIPC_HAL_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

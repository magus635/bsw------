/**************************************************************************************************
 *
 ***************************************************************************************************/
/**************************************************************************************************
 *   FileName             : Mcall.h
 *
 *   Platform             : AUTOSAR
 *
 *   brief                : Mcal common Macros and functions Definitions.
 *
 *   Autosar Version      : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ***************************************************************************************************/

/*
*#Violation Summary
*
*#Mcall_h_REF_1:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Mcall_h_REF_2:MISRAC2012-Rule-2.5;
* Justification: The macros are used to for other MCAL modules.
*
*#Mcall_h_REF_3:CertC-PRE00-C;
* Justification: Use simple macros to reduce code complexity.
*
*/

#ifndef MCALL_H_
#define MCALL_H_

/***************************************************************************************************
 *                               Includes
 ***************************************************************************************************/
#include "Mcall_Cfg.h"
#include "Mcall_GeneralTypes.h"

/* Header files including the HAL layer */
#include "cpuwdt_hal.h"
#include "safewdt_hal.h"
#include "stm_hal.h"
#include "rcc_hal.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/

/****************************************************************************************************
**                          Type Definitions                                                       **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

/* Check that the compiler used is supported (otherwise some defines might not exist) */
#ifndef _ADS_C_THA6_
#ifndef _GHS_C_THA6_
#ifndef _IAR_C_THA6_
#ifndef _HIGHTEC_C_THA6_
#ifndef _TASKING_C_THA6_
#error "Unsupported compiler. Compiler abstraction needs to be updated to use this compiler."
#endif /* _TASKING_C_THA6_ */
#endif /* _HIGHTEC_C_THA6_ */
#endif /* _IAR_C_THA6_ */
#endif /* _GHS_C_THA6_ */
#endif /* _ADS_C_THA6_ */

/*
 * !!! NOTE !!!
 * If AUTOSAR OS is not used:
 *     - If using a makefile, you must add "-DAUTOSAR_OS_NOT_USED" to compilation flags.
 *     - If using a IDE, you must define the global macro "AUTOSAR_OS_NOT_USED" within the
 *         IDE settings.
 * If AUTOSAR OS used: Do Nothing.
 */
#ifdef AUTOSAR_OS_NOT_USED

/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define ISR(IsrName)                           void IsrName(void)
/* Compiler abstraction for disabling all interrupts if no OS is present */
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define SuspendAllInterrupts()                 ASM(" cpsid if")
/* Compiler abstraction for re-enabling all interrupts if no OS is present */
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define ResumeAllInterrupts()                  ASM(" cpsie if")

#else /* AUTOSAR_OS_NOT_USED */

    #include "Os.h"

#endif /*AUTOSAR_OS_NOT_USED*/

/* Macro for ISR definition */
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define MCAL_ISR(IsrName)                      void IsrName(void)

/* Start Macro for re-definition the functions */
/* Get the core ID of the currently running core */
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_3 */
#define Mcal_GetCoreId()                       Multicore_GetCoreID()

/* WDT Endinit */
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define Mcal_EndinitOpen(para)                 Cpuwdt_Hal_InitEndinit(para)
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_3 */
#define Mcal_EndinitSet()                      Cpuwdt_Hal_SetEndinit()
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_3 */
#define Mcal_EndinitClr()                      Cpuwdt_Hal_ClearEndinit()
/* Safety WDT Endinit */
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define Mcal_SafeEndinitOpen(para)             Safewdt_Hal_InitSafetyEndinit(para)
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define Mcal_SafeEndinitSet()                  Safewdt_Hal_SetSafetyEndinit()
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define Mcal_SafeEndinitClr()                  Safewdt_Hal_ClearSafetyEndinit()
/* System timer */
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_3 */
#define Mcal_GetSystemTimerFreq()              Rcc_Hal_GetStmClkFreq()
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_3 */
#define Mcal_GetSystemTimerCount()             Stm_Hal_GetValue()
/* End Macro for re-definition the functions */

/* Macro for re-definition the enum */
/* CORE0 flag for MCAL */
#define MCAL_CORE0                             (MULTICOREID_CPU0)
/* CORE1 flag for MCAL */
#if (MCAL_NUMBER_OF_CORES > 1U)
#define MCAL_CORE1                             (MULTICOREID_CPU1)
#endif /* \(MCAL_NUMBER_OF_CORES > 1U) */
/* CORE1 flag for MCAL */
#if (MCAL_NUMBER_OF_CORES > 2U)
#define MCAL_CORE2                             (MULTICOREID_CPU2)
#endif /* \(MCAL_NUMBER_OF_CORES > 2U) */
/* CORE1 flag for MCAL */
#if (MCAL_NUMBER_OF_CORES > 3U)
#define MCAL_CORE3                             (MULTICOREID_CPU3)
#endif /* \(MCAL_NUMBER_OF_CORES > 3U) */

/* Macro for address of bootcore */
/* #Violation: Mcall_h_REF_2 */
#define MCAL_BOOTCORE_ADDR                     (0xC0020C58U)
/* Macro for value from bootcore configuration */
#define MCAL_BOOTCORE_VALUE                    ((uint8)(*((uint8 *)MCAL_BOOTCORE_ADDR)))
/* Macro for core1 value in bootcore */
/* #Violation: Mcall_h_REF_2 */
#define MCAL_BOOTCORE_CORE1                    (0xAAU)
/* Macro for boot core. Read from bootcore register. */
/* #Violation: Mcall_h_REF_2 */
#define MCAL_BOOTCORE                          ((MCAL_BOOTCORE_CORE1 == MCAL_BOOTCORE_VALUE) ? \
                                                                    (MCAL_CORE1): (MCAL_CORE0))

/* Other macros */
/* This macro is used for remove the unused parameter or variable warning */
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_3 */
#define MCAL_UNUSED_VAR(VariableName)          ((void)(VariableName))

/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define MCAL_CORE_BITPOS(CoreId)               ((uint8)(BIT(CoreId)))
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define MCAL_GET_CORE_BIT(MapCoreBits, CoreId) ((uint8)(MapCoreBits & (BIT(CoreId))))

/* Timeout value for waiting lock acquisition, loop count */
#define MCAL_LOCK_TIMEOUT                      ((uint32)0xFFFFFFFFU)

/* Macro for converting internal address to external device address in PFLASH */
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define MCAL_PFLASH_ADDR_INTERNALTODEVICE(Address)                  \
            ((FLASH_PFLASH_INTERNALADDR_COMPVALUE ==                 \
                ((Address) & FLASH_PFLASH_INTERNALADDR_MASKVALUE)) ? \
                    ((Address) + FLASH_PFLASH_INTERNALTODEVICE_ADDR_OFFSET) : (Address))

/* Macros for number */
#define MCAL_ZERO                              (0U)
#define MCAL_ONE                               (1U)
#define MCAL_TWO                               (2U)
/* #Violation: Mcall_h_REF_2 */
#define MCAL_THREE                             (3U)
#define MCAL_FOUR                              (4U)
/* #Violation: Mcall_h_REF_2 */
#define MCAL_FIVE                              (5U)
/* #Violation: Mcall_h_REF_2 */
#define MCAL_SIX                               (6U)
/* #Violation: Mcall_h_REF_2 */
#define MCAL_SEVEN                             (7U)
#define MCAL_EIGHT                             (8U)
/* #Violation: Mcall_h_REF_2 */
#define MCAL_NINE                              (9U)
/* #Violation: Mcall_h_REF_2 */
#define MCAL_TEN                               (10U)

/* Change the number of <BitLen> bits starting from the least significant bit <BitPos>
 * of the value of the address <OptData> to <Data>, leaving the other bits unchanged */
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_3 */
#define MCAL_SETBITS(OptDataPtr, BitPos, BitLen, Data)                          \
            do {                                                                \
                *(OptDataPtr) &= (~(((1UL << (BitLen)) - 1UL) << (BitPos)));          \
                *(OptDataPtr) |= (((Data) & ((1UL << (BitLen)) - 1UL)) << (BitPos));    \
            } while (0)

/* Change the number of <BitLen> bits starting from the least significant bit <BitPos>
 * of the value of the address <OptData> to 0, leaving the other bits unchanged */
/* #Violation: Mcall_h_REF_3 */
#define MCAL_CLRBITS(OptDataPtr, BitPos, BitLen)                                \
            do {                                                                \
                *(OptDataPtr) &= (~(((1UL << (BitLen)) - 1UL) << (BitPos)));          \
            } while (0)

/* Extract <BitLen> bits from the value of the number <DataValue> starting from the
 * least significant bit <BitPos> and assign it to <DestVal> */
/* #Violation: Mcall_h_REF_1 */
/* #Violation: Mcall_h_REF_3 */
#define MCAL_GETBITS(DataValue, BitPos, BitLen)                                 \
           ((uint32)(((DataValue) >> (BitPos)) & ((1U << (BitLen)) - 1U)))

/* Count Leading Zeros counts the number of binary zero bits before the first binary one bit in
 * the value of the <Data>, and writes the result to the pointer <LeadingCnt>. */
/* #Violation: Mcall_h_REF_2 */
/* #Violation: Mcall_h_REF_3 */
#define MCAL_CLZ(LeadingCntPtr, Data)                                           \
            ASM_VOLATILE("CLZ %0, %1" : "=r" (*(LeadingCntPtr)) : "r" (Data) : "memory")


/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/
/* #Violation: Mcall_h_REF_2 */
#define MCALL_START_SEC_CODE_ASIL_D_GLOBAL
#include "Mcall_MemMap.h"

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

extern FUNC(Std_ReturnType, MCAL_PRIVATE_CODE) Mcal_GetLock(Mcal_LockIdType LockId);

extern FUNC(void, MCAL_PRIVATE_CODE) Mcal_ReleaseLock(Mcal_LockIdType LockId);

/* #Violation: Mcall_h_REF_2 */
#define MCALL_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Mcall_MemMap.h"

#endif /* MCALL_H_ */

/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/

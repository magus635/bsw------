/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_compiler_hightec.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
*
*   Autosar Version       : R23-11
*
*   Build Version         : Cortex-R52/THA6206
*
*   Copyright (c) @#
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*  -------------------------------------------------------------------------------------------------
*  Version    Date           Author(ID)      SVN_Version         Description
*  -------------------------------------------------------------------------------------------------
*  V0.0.1   22-May-2024    zhangtr(30011)                        Initial Version
*
****************************************************************************************************/
#ifndef OS_COMPILER_HIGHTEC_H_
#define OS_COMPILER_HIGHTEC_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#include "common.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#ifndef ASM
#define ASM __asm__
#endif

#ifndef ASM_VOLATILE
#define ASM_VOLATILE __asm__ volatile
#endif

/* INLINE function is a global symbol and will be inline if optimization isn't -O0 */
#ifndef INLINE
#define INLINE __inline__
#endif
/* LOCAL_INLINE function is a local symbol and will be inline if optimization isn't -O0 */
#ifndef LOCAL_INLINE
#define LOCAL_INLINE static __inline__
#endif
/* LOCAL_FORCEINLINE function is a local symbol and will be inline */
#ifndef LOCAL_FORCEINLINE
#define LOCAL_FORCEINLINE __attribute__((always_inline)) static __inline__
#endif
/*define ALIGNED macro. */
#ifndef ALIGNED
#define ALIGNED(x) __attribute__((aligned(x)))
#endif

/* define __attribute__((naked)) attribute. */
#define ATTR_NAKED __attribute__((naked))

#define PACKED_ALIGN(x) __attribute__((packed)) __attribute__((aligned(x)))

#define Os_Inf_SetCP(cp, op1, Rt, CRn, CRm, op2)            \
   __asm volatile("mcr p" #cp ", " #op1 ", %0, c" #CRn ", c" #CRm ", " #op2 ::"r"(Rt) : "memory")

#define Os_Inf_GetCP(cp, op1, Rt, CRn, CRm, op2)            \
   __asm volatile("mrc p" #cp ", " #op1 ", %0, c" #CRn ", c" #CRm ", " #op2 : "=r"(Rt) : : "memory")

#define Os_Inf_SetCP64(cp, op1, Rt, CRm)                     \
   __asm volatile("mcrr p"#cp ", "#op1 ", %Q0, %R0, c" #CRm::"r"(Rt):"memory")

#define Os_Inf_GetCP64(cp, op1, Rt, CRm)                     \
   __asm volatile("mrrc p"#cp ", "#op1 ", %Q0, %R0, c" #CRm:"=r"(Rt)::"memory")

/* Instruction sync command. */
#define Os_Inf_Isync()                       __asm volatile("isb \n":::"memory")
/* Data sync command. */
#define Os_Inf_Dsync()                       __asm volatile("dmb \n":::"memory")
/* Nop command. */
#define Os_Inf_Nop()                         __asm volatile("nop \n")
/* Set TPIDRURO register value as expected.*/
#define Os_Inf_SetThread(Thread)             __asm volatile("mcr p15, 0, %0, c13, c0, 3 \n"::"r"(Thread))
/* Set ICC_PMR register value as expected.*/
#define Os_Inf_SetGicPmr(Priority)           __asm volatile("mcr p15, 0, %0, c4, c6, 0 \n"::"r"(Priority))

#define Os_Inf_DisableInt()                 __asm volatile("cpsid if \n")

#define Os_Inf_EnableInt()                  __asm volatile("cpsie if \n")

#define Os_Inf_StoreFPURegisters(Address)   __asm volatile("vstm  %0!, {d0-d15}  \n"   \
                                                           "vstm  %0!, {d16-d31} \n"   \
                                                           :"r"(Address)               \
                                                           :                           \
                                                           :"memory")

#define Os_Inf_RestoreFPURegisters(Address)  __asm volatile("vldm  %0!, {d0-d15}  \n"   \
                                                            "vldm  %0!, {d16-d31} \n"   \
                                                            :                           \
                                                            :"r"(Address)               \
                                                            :)

#define Os_Inf_TrapTaskSwitch()                 __asm volatile("svc #1    \n")
#define Os_Inf_TrapToSystemMode()            __asm volatile("svc #0    \n")
#define Os_Inf_TrapToUserMode()              __asm volatile("cps #0x10  \n")
#define Os_Inf_GetFunctionReturnValue(Var)   __asm volatile("mov %0, r0 \n"        \
                                                            :"=r"(Var)             \
                                                            :                      \
                                                            :"memory","r0")

LOCAL_FORCEINLINE uint32 Os_Inf_CompilerGetCoreID(void)
{
    uint32 CoreId;
    __asm volatile("mrc p15, 0, %0, c0, c0, 5 \n"
                   "and %0, %0, #0xFF         \n"
                   : "=r"(CoreId)
                   :
                   : "memory");
    return CoreId;
}

LOCAL_FORCEINLINE uint32 Os_Inf_clz(uint32 Value)
{
    uint32 ZeroLead;
    __asm volatile("clz %0, %1 \n" : "=r" (ZeroLead) : "r" (Value) : "memory");
    return ZeroLead;
}

LOCAL_FORCEINLINE void * Os_Inf_GetThread(void)
{
    uint32 Thread;
    __asm volatile("mrc p15, 0, %0, c13, c0, 3 \n":"=r"(Thread)::"memory");
    return (void*)Thread;
}

LOCAL_FORCEINLINE uint32 Os_Inf_GetCoreMode(void)
{
    uint32 CoreMode;
    __asm volatile("mrs %0, cpsr \n":"=r"(CoreMode)::"memory");
    return CoreMode;
}

LOCAL_FORCEINLINE uint32 Os_Inf_LoadExclusive(volatile uint32* Address)
{
    uint32 Value;
    __asm volatile ("ldrex %0, [%1] \n":"=r"(Value):"r"(Address));
    return Value;
}

LOCAL_FORCEINLINE uint32 Os_Inf_StoreExclusive(volatile uint32* Address, uint32 Value)
{
    uint32 Result;
    __asm volatile (" strex %0, %2, [%1] \n" :"=&r"(Result), "+&r"(Address): "r"(Value));
    return Result;
}

LOCAL_FORCEINLINE void Os_Inf_ClearExclusive(void)
{
    __asm volatile (" clrex \n" );
}

LOCAL_FORCEINLINE boolean IsNeedSysTrap(void)
{
    uint32 CoreMode;
    __asm volatile("mrs %0, cpsr \n":"=r"(CoreMode)::"memory");
    CoreMode &= 0x1FUL;
    return (CoreMode == MODE_USR);
}

LOCAL_FORCEINLINE uint32 Os_Inf_GetCPSR_AndDisableIRQ(void)
{
    uint32 CpsrValue;

    __asm volatile("mrs %0, cpsr \n":"=r" (CpsrValue)::"memory");
    __asm volatile("cpsid i \n");

    return CpsrValue;
}

LOCAL_FORCEINLINE void Os_Inf_RestoreCPSR(uint32 CpsrValue)
{
    if (0 == (CpsrValue & 0x00000080))
    {
        __asm volatile("cpsie i \n");
    }
    else
    {
        __asm volatile("cpsid i \n");
    }
}

LOCAL_FORCEINLINE void Os_AtomicBitClear(
    P2VAR(uint32, AUTOMATIC, OS_VAR) Address,
    uint32 Bit
)
{
    uint32 temp, result, status;
    uint32 mask = ~(1U << Bit);

    /* LDREX/STREX loop until successful */
    do {
        __asm volatile(
            "ldrex %0, [%3]\n"           /* Load-Exclusive: temp = *Address */
            "and %1, %0, %4\n"           /* Bit clear: result = temp & mask */
            "strex %2, %1, [%3]\n"       /* Store-Exclusive: status = strex(result, Address) */
            : "=&r" (temp), "=&r" (result), "=&r" (status)
            : "r" (Address), "r" (mask)
            : "cc", "memory"
        );
    } while (status != 0U);  /* STREX returns 0 on success, retry if status != 0 */

    /* Data Memory Barrier - ensure completion and visibility */
    __asm volatile("dmb sy" : : : "memory");
}

#endif /* OS_COMPILER_HIGHTEC_H_ */

/****************************************************************************************************
**     End of File: Os_compiler_hightec.h                                                          **
****************************************************************************************************/


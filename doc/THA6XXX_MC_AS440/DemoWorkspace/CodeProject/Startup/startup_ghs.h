/****************************************************************************************************
* Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
* FileName: exception.s
* Author:    30032
* Version:   v1.0
* Date:     2023/05/14
* Description: common Macros and functions Definitions for startup.c used by Green Hills compiler.
* Others:
* History:
*  Date          Author    Modified
*  2023/05/14    30032     create
****************************************************************************************************/

/*
*
*#startup_ghs_h_REF_1:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_2:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_3:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_4:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_5:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_6:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_7:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_8:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_9:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_10:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_11:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_12:PRE00-C;
*Justification: reduce code complexity.
*
*#startup_ghs_h_REF_13:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
*/


 /****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
 *   V1.0.0:  1-Aug-2022: Initial Version
 *
 ****************************************************************************************************/
#ifndef STARTUP_GHS_H_
#define STARTUP_GHS_H_
/***************************************************************************************************
 *                               Includes
 ***************************************************************************************************/
#include "Platform_Types.h"
#include "common_hal.h"
#include "compilertypes.h"

/*define temporary stack address. used for stack of function calling.*/
#define STARTUP_TEMPSTACKADDR_CORE0 (0x10000200U)

#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
#define STARTUP_TEMPSTACKADDR_CORE1 (0x10000400U)
#if defined(THA6_THA6412)
#define STARTUP_TEMPSTACKADDR_CORE2 (0x10000600U)
#define STARTUP_TEMPSTACKADDR_CORE3 (0x10000800U)
#endif /* THA6_THA6412 */
#endif /* THA6_THA6206 || THA6_THA6412 */

/* Must be placed in 0x10000000U~0x10000200U*/
/* MULTICORE_SYNCVAR is initialized at Start().0x10000040U */
/* PLOCK needs 64 bytes. do not use 0x10000000U~0x10000040U */
#define MULTICORE_SYNCVAR_ADDR (0x10000040U)
#define PLOCK_ADDR             (0x10000000U)

/* Change EL2 exception base address to Startup_EL2ExceptionTable */
/* #Violation: startup_ghs_h_REF_6 */
#define STARTUP_SETEL2EXCEPTIONBASEADDR(BaseAdddresss)                                                                 \
    {                                                                                                                  \
        /* Change EL2 exception base address. Write to HVBAR  */                                                       \
        ASM_VOLATILE("mcr p15, 4, %[r0], c12, c0, 0" ::[r0] "r"(&BaseAdddresss) : "memory", "r0");                     \
    }
/* Change EL1 exception base address to Startup_EL1ExceptionTable */
/* #Violation: startup_ghs_h_REF_7 */
#define STARTUP_SETEL1EXCEPTIONBASEADDR(BaseAdddresss)                                                                 \
    {                                                                                                                  \
        /* Change EL1 exception base address. Write to VBAR  */                                                        \
        ASM_VOLATILE("mcr p15, 0, %[r0], c12, c0, 0" ::[r0] "r"(&BaseAdddresss) : "memory", "r0");                     \
    }

/* Set the Stack point by cps to the mode and set the sp. */
/* #Violation: startup_ghs_h_REF_5 */
#define STARTUP_SETMODESP(mode, stacktype)                                                                             \
    {                                                                                                                  \
        /* Change mode to the defined mode */                                                                          \
        ASM_VOLATILE("cps #" #mode "\n");                                                                              \
        /* Set the stack pointer with the region limit address. */                                                     \
        ASM_VOLATILE("ldr r0, =__" #stacktype "_ADDRESS_END \n"                                                    \
                     "mov sp, r0                                \n"                                                    \
                     :                                                                                                 \
                     :                                                                                                 \
                     : "memory", "r0");                                                                                \
    }

/* #Violation: startup_ghs_h_REF_1 */
#define STARTUP_SETSTACK(mode, stacktype) STARTUP_SETMODESP(mode, stacktype)

/* Set the Stack point by set the sp for hyp. */
/* #Violation: startup_ghs_h_REF_9 */
#define STARTUP_SETHYPMODESP(stacktype)                                                                             \
    {                                                                                                                  \
        /* Set the stack pointer with the region limit address. */                                                     \
        ASM_VOLATILE("ldr r0, =__" #stacktype "_ADDRESS_END \n"                                                    \
                     "mov sp, r0                                \n"                                                    \
                     :                                                                                                 \
                     :                                                                                                 \
                     : "memory", "r0");                                                                                \
    }

/* #Violation: startup_ghs_h_REF_10 */
#define STARTUP_SETTEMPSVCSTACK(address)                                                                               \
    {                                                                                                                  \
        ASM_VOLATILE("msr   sp_svc, %0 \n"::"r"(address):);                                                            \
    }

/* #Violation: startup_ghs_h_REF_8 */
#define STARTUP_GETIMAGEBASEADDR(RegionName, address)                                                                  \
    {                                                                                                                  \
        /* Get the region image base address. */                                                                       \
        ASM_VOLATILE("ldr %0, =__" #RegionName "_ADDRESS_START" : "+r"(address)::"memory");                               \
    }
/* #Violation: startup_ghs_h_REF_3 */
#define STARTUP_GETIMAGELIMITADDR(RegionName, address)                                                                 \
    {                                                                                                                  \
        /* Get the region image limit address. */                                                                      \
        ASM_VOLATILE("ldr %0, =__" #RegionName "_ADDRESS_END" : "+r"(address)::"memory");                              \
    }
/* #Violation: startup_ghs_h_REF_4 */
#define STARTUP_GETIMAGEBSSLIMITADDR(RegionName, address)                                                              \
    {                                                                                                                  \
        /* Get the region image limit address. */                                                                      \
        ASM_VOLATILE("ldr %0, =__" #RegionName "_ADDRESS_END" : "+r"(address)::"memory");                          \
    }
/* #Violation: startup_ghs_h_REF_12 */
#define STARTUP_GETLOADBASEADDR(RegionName, address)                                                                   \
    {                                                                                                                  \
        /* Get the region load base address. */                                                                        \
        ASM_VOLATILE("ldr %0, =__" #RegionName "_LOAD_ADDRESS_START" : "+r"(address)::"memory");                       \
    }


/* Get the copy data image base and limit address ,load address by macro function . */
/* #Violation: startup_ghs_h_REF_11 */
#define STARTUP_GETCOPYDATAINFO(RegionName, InitSection)                                                               \
    do{                                                                                                                  \
        /* Get the region base address and set value to member copyDataImageAddr */                                    \
        STARTUP_GETIMAGEBASEADDR(RegionName, InitSection.copyDataImageAddr);                                           \
        /* Get the region limit address and set value to member copyDataLimitAddr */                                   \
        STARTUP_GETIMAGELIMITADDR(RegionName, InitSection.copyDataLimitAddr);                                          \
        /* Get the region flash load address and set value to member copyDataLoadAddr */                               \
        STARTUP_GETLOADBASEADDR(RegionName, InitSection.copyDataLoadAddr);                                             \
    }while(0);
/* Get the clear data image base and limit address by macro function . */
/* #Violation: startup_ghs_h_REF_2 */
#define STARTUP_GETBSSDATAINFO(RegionName, InitSection)                                                                \
    do{                                                                                                                  \
        /* Get the region base address and set value to member clearImageAddr */                                       \
        STARTUP_GETIMAGEBASEADDR(RegionName, InitSection.clearImageAddr);                                              \
        /* Get the region limit address and set value to member clearLimitAddr */                                      \
        STARTUP_GETIMAGEBSSLIMITADDR(RegionName, InitSection.clearLimitAddr);                                          \
    }while(0);
/**********************************************************************************************************************
 *                                            Global Structure Definitions
 *********************************************************************************************************************/
typedef void (*FunctionNoParam)(void);

typedef struct
{
    uint32 *copyDataImageAddr;
    uint32 *copyDataLimitAddr;
    uint32 *copyDataLoadAddr;
} Startup_CopyData;

typedef struct
{
    uint32 *clearImageAddr;
    uint32 *clearLimitAddr;
} Startup_ClearData;

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/
#pragma ghs section text = ".init_default_vector"
/* This is the EL2 Exception table that can jump to the function. */
ATTR_NAKED LOCAL_FORCEINLINE void Startup_EL2ExceptionTable(void)
{
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("    ldr pc, =Start                          \n"
                 "    ldr pc, =EL2_UndefinedException        \n"
                 "    ldr pc, =EL2_HVCHandler                 \n"
                 "    ldr pc, =EL2_PrefetchAbortException     \n"
                 "    ldr pc, =EL2_DataAbortException         \n"
                 "    ldr pc, =EL2_HypModeEntryHandler        \n"
                 "    ldr pc, =EL2_IRQHandler                 \n"
                 "    ldr pc, =EL2_FIQHandler                 \n");
}
/* This is the EL1 Exception table that can jump to the function. */
ATTR_NAKED LOCAL_FORCEINLINE void Startup_EL1ExceptionTable(void)
{
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("    ldr pc, =Start                          \n"
                 "    ldr pc, =EL1_UndefinedException        \n"
                 "    ldr pc, =EL1_SVCHandler                 \n"
                 "    ldr pc, =EL1_PrefetchAbortException     \n"
                 "    ldr pc, =EL1_DataAbortException         \n"
                 "    ldr pc, =EL1_Reserved                   \n"
                 "    ldr pc, =EL1_IRQHandler                 \n"
                 "    ldr pc, =EL1_FIQHandler                 \n");
}
#pragma ghs section text = default
/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/
/****************************************************************************************************
 *   Function Name           : Startup_JumpToFunction
 *
 *   Service ID              : 0x08.
 *
 *   Description             : This function is for jump to the function without pop stack.
 *
 *   Parameters in           : pFunction: The function name of the one jumping to.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_JumpToFunction(FunctionNoParam const pFunction)
{
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("bx %0\n" ::"r"(pFunction) : "memory");
}
/****************************************************************************************************
 *   Function Name           : Startup_InitEL2Configuration
 *
 *   Service ID              : 0x09.
 *
 *   Description             : This function is to initialize HSCTLR register and enable the EL2/EL1 ICache.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
#ifdef ICACHE_ENABLE
LOCAL_FORCEINLINE void Startup_InitEL2Configuration(void)
{
    /* set IMP_CSCTLR, FLASH WAY, AXIM WAYS  Flash ways 0~1, AXIM sways 2~3 */
    ASM_VOLATILE("mcr p15, 1, %[r0], c9, c1, 0 \n"
        "isb                          \n"
        :
        : [r0] "r"(0x202)
        : "memory", "r0");  
    /* Configurate the HSCTLR Register. */
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("mcr p15, 4, %[r0], c1, c0, 0 \n"
                 "isb                          \n"
                 :
                 : [r0] "r"(0x30C51808)
                 : "memory", "r0");
    /* EL1 ICache Enable, DCache Disable. */
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("    mrc        p15, 0, r0, c1, c0, 0    \n" /* Read System Control Register */
                 "    orr        r0, r0, #(0x1 << 12)     \n" /* ENABLE I Cache */
                 "    dsb                                 \n" /* Ensuring memory access complete */
                 "    mcr        p15, 0, r0, c1, c0, 0    \n" /* write System Control Register */
                 "    isb                                 \n" /* Ensuring Context-changing */
                 :
                 :
                 : "memory", "r0");
}
#endif

/****************************************************************************************************
 *   Function Name           : Startup_SetTCMAddr
 *
 *   Service ID              : 0x0A.
 *
 *   Description             : This function is for setting the Core0 BTCM and CTCM configuration register.
 *
 *   Parameters in           : BTCM_Address: The IMP_BTCMREGIONR register value to set.
 *                             CTCM_Address: The IMP_CTCMREGIONR register value to set.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_SetTCMAddr(uint32 BTCMAddress, uint32 CTCMAddress)
{
    /* Configurate the IMP_BTCMREGIONR Register. */
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("mcr p15, 0, %[r0], c9, c1, 1" ::[r0] "r"(BTCMAddress) : "memory", "r0");
    /* Configurate the  IMP_CTCMREGIONR Register. */
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("mcr p15, 0, %[r0], c9, c1, 2" ::[r0] "r"(CTCMAddress) : "memory", "r0");
}
/****************************************************************************************************
 *   Function Name           : Startup_ExitEL2WithSVCMode
 *
 *   Service ID              : 0x0B.
 *
 *   Description             : This function is for Change mode form EL2 to EL1 and jump to Startup_EL1ResetHandler.
 *
 *   Parameters in           : pFunction: The function name of the one jumping to.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                    : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_ExitEL2WithSVCMode(FunctionNoParam const pFunction)
{
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("    mrs   r0, cpsr                      \n" /* Original PSR value */
#ifdef THUMB_ENABLE
                "    mov   r1, #0x33                     \n" /* Set r1 with SVC mode and thumb bit*/
#else
                "    mov   r1, #0x13                     \n" /* Set r1 with SVC mode and thumb bit*/
#endif
                 "    bfi   r0, r1, #0, #6                \n" /* Load r0 bit0~6 with SVC mode */
                 "    msr   spsr_hyp, r0                  \n" /* Save the SVC mode to SPSR */
                 "    mov   r0, %0                        \n" /* Load the next execute function address */
                 "    msr   elr_hyp, r0                   \n" /* Save the address to elr_hyp register */
                 "    dsb                                 \n"
                 "    isb                                 \n"
                 "    eret                                \n" /* Branch to stack_init and enter EL1 */
                 :
                 : "r"(pFunction)
                 : "r0", "r1");
}
/****************************************************************************************************
 *   Function Name           : Startup_EnableVFP
 *
 *   Service ID              : 0x0C.
 *
 *   Description             : Initialize VFP function to be used at EL2/EL1/EL0.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_EnableVFP(void)
{
    /* EL1 DCache Enable */
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("    mrc        p15, 0, r0, c1, c0, 2    \n" /* Read CPACR Register */
                 "    orr        r0, r0, #(0xF << 20)     \n" /* Enable access to CP 10 & 11 */
                 "    mcr        p15, 0, r0, c1, c0, 2    \n" /* write CPACR Register */
                 "    isb                                 \n" /* Ensuring Context-changing */
                 "    mov        r0, #0x40000000          \n"
                 "    vmsr       fpexc, r0                \n" /* Write FPEXC register, EN bit set */
                 :
                 :
                 : "memory", "r0");
}
/****************************************************************************************************
 *   Function Name           : Startup_EnableDCache
 *
 *   Service ID              : 0x0E.
 *
 *   Description             : This function is for enable the dcached function before going to the main.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
#ifdef DCACHE_ENABLE
LOCAL_FORCEINLINE void Startup_EnableDCache(void)
{
    /* EL1 DCache Enable */
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("    mrc        p15, 0, r0, c1, c0, 0    \n" /* Read System Control Register */
                 "    orr        r0, r0, #(0x1 << 2)      \n" /* ENABLE D Cache */
                 "    dsb                                 \n" /* Ensuring memory access complete */
                 "    mcr        p15, 0, r0, c1, c0, 0    \n" /* write System Control Register */
                 "    isb                                 \n" /* Ensuring Context-changing */
                 :
                 :
                 : "memory", "r0");
}
#endif
/****************************************************************************************************
 *   Function Name           : Startup_InfiniteLoop
 *
 *   Service ID              : 0x0F.
 *
 *   Description             : This function is for unexpected return form main ,then loop in Startup_InfiniteLoop
 *                             to avoid the program is shutdown.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_InfiniteLoop(void)
{
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("14: nop        \n" /*Nop */
                 "    nop        \n" /*Nop */
                 "    nop        \n" /*Nop */
                 "    b  14b     \n" /* loop */
    );
}

/****************************************************************************************************
 *   Function Name           : Startup_InitATCMDataSection
 *
 *   Service ID              : 0x10.
 *
 *   Description             : This function is to initialize the data/code sections placed at ATCM. Copy data
 *   from flash to ATCM.
 *
 *   Parameters in           : *pDataSection: The structure include the imagebase address,imagelimit address and
 *loadbase address.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_InitATCMDataSection(const Startup_CopyData * const pDataSection)
{
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("   add   %1, %1, #0x3F        \n"
                 "   bic   %1, %1, #0x3F        \n"
                 "   cmp   %1, %0               \n"
                 "   ble   2f                   \n"
                 "1: ldmia  %2!, {r4-r7}        \n"
                 "   stmia  %0!, {r4-r7}        \n"
                 "   cmp  %1, %0                \n"
                 "   bgt  1b                    \n"
                 "2:                            \n"
                 :
                 : "r"(pDataSection->copyDataImageAddr), "r"(pDataSection->copyDataLimitAddr),
                   "r"(pDataSection->copyDataLoadAddr)
                 : "r4", "r5", "r6", "r7");
}

/****************************************************************************************************
 *   Function Name           : Startup_InitDataSection
 *
 *   Service ID              : 0x11.
 *
 *   Description             : This function is to initialize the data/code section which isn't placed at ATCM.
 *   copy data from flash to RAM/BTCM/CTCM.
 *
 *   Parameters in           : *pDataSection: The structure include the imagebase address,imagelimit address and
 *                               loadbase address.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_InitDataSection(Startup_CopyData * const pDataSection)
{
    while(pDataSection->copyDataImageAddr < pDataSection->copyDataLimitAddr)
    {
        *(pDataSection->copyDataImageAddr) = *(pDataSection->copyDataLoadAddr);
        pDataSection->copyDataImageAddr++;
        pDataSection->copyDataLoadAddr++;
    }
}

/****************************************************************************************************
 *   Function Name           : Startup_InitATCMBssSection
 *
 *   Service ID              : 0x12.
 *
 *   Description             : This function is for initializing the bss section by clear the private bss section
 *                             from the imaged base address to limit address
 *
 *   Parameters in           : *pBssSection: The structure include the cleared imagebase and imagelimit address.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_InitATCMBssSection(const Startup_ClearData * const pBssSection)
{
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE("   add   %1,  %1,  #0x3F  \n"
                 "   bic   %1,  %1,  #0x3F  \n" /* ALign 64 bytes*/
                 "   cmp   %1,  %0          \n"
                 "   ble   4f               \n"
                 "   mov   r2,  #0          \n"
                 "   mov   r3,  #0          \n"
                 "   mov   r4,  #0          \n"
                 "   mov   r5,  #0          \n"
                 "3: stmia %0!, {r2-r5}     \n"
                 "   cmp   %1,  %0          \n"
                 "   bgt   3b               \n"
                 "4:                        \n"
                 :
                 : "r"(pBssSection->clearImageAddr), "r"(pBssSection->clearLimitAddr)
                 : "r2", "r3", "r4", "r5");
}
/****************************************************************************************************
 *   Function Name           : Startup_InitBssSection
 *
 *   Service ID              : 0x13.
 *
 *   Description             : This function is for initializing the bss section by clear the private bss section
 *                             from the imaged base address to limit address
 *
 *   Parameters in           : *pBssSection: The structure include the cleared imagebase and imagelimit address.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_InitBssSection(Startup_ClearData *pBssSection)
{
    while(pBssSection->clearImageAddr < pBssSection->clearLimitAddr)
    {
        *(pBssSection->clearImageAddr) = 0U;
        pBssSection->clearImageAddr++;
    }
}

/****************************************************************************************************
 *   Function Name           : Startup_ExceptionConfiguration
 *
 *   Service ID              : 0x14.
 *
 *   Description             : This function is to set HCR.AMO to 1.
 *
 *   Parameters in           : None
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_ExceptionConfiguration(void)
{
    /* EL1 DCache Enable */
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE(
        "    mrc        p15, 4, r0, c1, c1, 0    \n" /* Read HCR Register */
        "    orr        r0, r0, #0x20            \n" /* Set HCR.AMO to 1, route system error to EL2 HYP mode Entry */
        "    mcr        p15, 4, r0, c1, c1, 0    \n" /* Write HCR Register */
        :
        :
        : "r0");
}

/****************************************************************************************************
 *   Function Name           : Startup_EnableLLPP
 *
 *   Service ID              : 0x15.
 *
 *   Description             : Enable LLPP0/LLPP1 Port at EL2/EL1/EL0.
 *
 *   Parameters in           : None
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   TraceID                 : None.
 ****************************************************************************************************/
LOCAL_FORCEINLINE void Startup_EnableLLPP(void)
{
    /* Enable LLPP0/LLPP1 at EL2/EL1/EL0 level */
    /* #Violation: startup_ghs_h_REF_13 */
    ASM_VOLATILE(
        "    mrc        p15, 0, r0, c15, c0, 0    \n"  /* Read IMP_PERIPHPREGIONR Register */
        "    orr        r0, r0, #0x3              \n"  /* Enable LLPP at EL2/EL1 */
        "    mcr        p15, 0, r0, c15, c0, 0     \n" /* Write IMP_PERIPHPREGIONR Register */
        :
        :
        : "r0");
}
/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern void Start(void);

#endif /* STARTUP_GHS_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

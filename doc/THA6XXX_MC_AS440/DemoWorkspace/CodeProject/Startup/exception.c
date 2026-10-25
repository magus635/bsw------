/****************************************************************************************************
* Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
* FileName: exception.s
* Author:    30032
* Version:   v1.0
* Date:     2023/05/14
* Description: This file process all exception handler of EL1/EL2.
* Others:
* History:
*  Date          Author    Modified
*  2023/05/14    30032     create
****************************************************************************************************/
/*
*#Violation Summary
*
*#exception_c_REF_1:MISRAC2012-Rule-20.1;
*Justification: Imposes the specification of the section in which certain parts of the driver must be placed.
*
*#exception_c_REF_2:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
*/

#include "compilertypes.h"
#include "common_hal.h"
#include "Platform_Types.h"
/* section for IRQ/FIQ Interrupt Handler. writable */
#define SDK_START_SEC_INIT_VAR_IRQ_VECTOR
#include "Sdk_MemMap.h"
/* There are 992 interrupt Handlers for R52+. */
uint32 GICIsrVectorTable[992]={0xFFFFFFFF};
#define SDK_STOP_SEC_INIT_VAR_IRQ_VECTOR
/* #Violation: exception_c_REF_1 */
#include "Sdk_MemMap.h"

/* exception reg information section. */
#define SDK_START_SEC_INIT_VAR_EXCEPTION_REG_INFO
/* #Violation: exception_c_REF_1 */
#include "Sdk_MemMap.h"
/* 10 words used to save exception register information. */
/*************************************************
*    WORD 0   -- el1Flag flag 0 for EL2 and 1 for EL1.
*    WORD 1   -- LR register indicates exception return addr.
*    WORD 2   -- HSR register value
*    WORD 3   -- HAIFSR register value.
*    WORD 4   -- HPFAR register value.
*    WORD 5   -- AIFSR register value.
*    WORD 6   -- ADFSR register value.
*    WORD 7   -- DFAR register value.
*    WORD 8   -- DFSR register value.
*    WORD 9   -- IFAR register value.
*    WORD 0xA -- IFSR register value.
*    WORD 0xB -- ISR register value.
**************************************************/
uint32 exceptionRegInformation[12]={0xFFFFFFFF};
#define SDK_STOP_SEC_INIT_VAR_EXCEPTION_REG_INFO
/* #Violation: exception_c_REF_1 */
#include "Sdk_MemMap.h"

/* exception handler section. */
#define SDK_START_SEC_EXCEPTION_HANDLER
/* #Violation: exception_c_REF_1 */
#include "Sdk_MemMap.h"

ATTR_NAKED WEAKFUNC void Exception_GetIntVectorInfo(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " cmp r0, #0x0    \n"
        " beq stepFail    \n"     /* parameter check. */
        " cmp r1, #0x0  \n"
        " beq stepFail    \n"     /* parameter check. */
        " ldr r2, =GICIsrVectorTable  \n"
        " str r2, [r0]    \n"     /* save interrupt vector table start address */
        " mov r2, #992    \n"
        " str r2, [r1]    \n"     /*save elemnet number of interrupt vector table. */
        " mov  r0, #0x0   \n"
        " b stepFinish    \n"
#ifdef __TASKING__
        "stepFail: movw r0, #@lsh(0xFFFFFFFF)  \n"
        " movt r0, #@msh(0xFFFFFFFF)  \n"
#else
        /* A space before the label is illegal in IAR, TASKING inline assembly should start with a space. */
        /* To ensure compatibility with both IAR and TASKING, spaces are added before all assembly instructions, and labels do not have spaces. */
        "stepFail: mov r0, #0xFFFFFFFF  \n"
#endif
        "stepFinish: blx lr \n"
    );
}


ATTR_NAKED WEAKFUNC void EL2_GetExceptionInformation(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " ldr r1, =exceptionRegInformation \n"
        " mov r2, #0x0 \n"                     /* EL2 flag */
        " mov r3, r0   \n"                     /* r0 save LR register value. */
        " strd r2, r3, [r1], #0x8   \n"

        " mrc p15, 4, r2, c5, c2, 0 \n"        /* HSR register. */
        " mrc p15, 4, r3, c5, c1, 1 \n"        /* HAIFS register */
        " strd r2, r3, [r1], #0x8   \n"

        " mrc p15, 4, r2, c6, c0, 4 \n"        /* HPFAR register. */
        " mrc p15, 0, r3, c5, c1, 1 \n"        /* AIFSR register. */
        " strd r2, r3, [r1], #0x8   \n"

        " mrc p15, 0, r2, c5, c1, 0 \n"        /* ADFSR register. */
        " mrc p15, 0, r3, c6, c0, 0 \n"        /* DFAR register. */
        " strd r2, r3, [r1], #0x8   \n"

        " mrc p15, 0, r2, c5, c0, 0 \n"        /* DFSR register. */
        " mrc p15, 0, r3, c6, c0, 2 \n"        /* IFAR */
        " strd r2, r3, [r1], #0x8   \n"

        " mrc p15, 0, r2, c5, c0, 1  \n"       /* IFSR regiser. */
        " mrc p15, 0, r3, c12, c1, 0 \n"       /* ISR register. */
        " strd r2, r3, [r1], #0x8    \n"

        " ldr r0, =exceptionRegInformation \n" /* pointer to the structure. */
        " blx lr \n"
    );
}

ATTR_NAKED WEAKFUNC void EL1_GetExceptionInformation(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " ldr r1, =exceptionRegInformation  \n"
        " mov r2, #0x1      \n"                     /* EL1 flag */
        " mov r3, r0        \n"                     /* r0 save LR register value. */
        " strd r2, r3, [r1], #0x8           \n"

        " mov r2, #0x0      \n"                     /* HSR */
        " mov r3, #0x0      \n"
        " strd r2, r3, [r1], #0x8 \n"               /* HAIFSR */

        /* r2 is 0 */                               /* HPFAR */
        " mrc p15, 0, r3, c5, c1, 1 \n"             /* AIFSR */
        " strd r2, r3, [r1], #0x8   \n"

        " mrc p15, 0, r2, c5, c1, 0 \n"             /* ADFSR */
        " mrc p15, 0, r3, c6, c0, 0 \n"             /* DFAR */
        " strd r2, r3, [r1], #0x8   \n"

        " mrc p15, 0, r2, c5, c0, 0 \n"             /* DFSR register. */
        " mrc p15, 0, r3, c6, c0, 2 \n"             /* IFAR */
        " strd r2, r3, [r1], #0x8   \n"

        " mrc p15, 0, r2, c5, c0, 1     \n"         /* IFSR */
        " mrc p15, 0, r3, c12, c1, 0    \n"         /* ISR register. */
        " strd r2, r3, [r1], #0x8       \n"
        " ldr r0, =exceptionRegInformation \n"      /*pointer to the structure. */
        " blx lr \n"
    );
}

ATTR_NAKED WEAKFUNC void Exception_UndefinedCallback(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b Exception_UndefinedCallback  \n"
    );
}

ATTR_NAKED WEAKFUNC void Exception_PrefetchAbortCallback(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b Exception_PrefetchAbortCallback  \n"
    );
}

ATTR_NAKED WEAKFUNC void Exception_DataAbortCallback(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b Exception_DataAbortCallback  \n"
#ifdef __ARMCC_VERSION
        /* use .eabi_attribute Tag_ABI_align_preserved, 1 to solve compiler warning. SP should be 8 bytes align. */
        " .eabi_attribute Tag_ABI_align_preserved, 1 \n"
#endif
    );
}

ATTR_NAKED WEAKFUNC void EL2_UndefinedException(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b EL2_UndefinedException  \n"
        " eret \n"
    );
}

ATTR_NAKED WEAKFUNC void EL2_HVCHandler(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b EL2_HVCHandler  \n"
        " eret \n"
    );
}

ATTR_NAKED WEAKFUNC void EL2_PrefetchAbortException(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b EL2_PrefetchAbortException  \n"
        " eret \n"
    );
}

ATTR_NAKED WEAKFUNC void EL2_DataAbortException(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " push {r0-r12, lr}     \n"                   /* save used registers at svc function. */
        " mrs r0, elr_hyp       \n"                   /* transfer abort lr register as an input parameter to EL1_GetExceptionInformation. */
        " bl EL2_GetExceptionInformation   \n"        /* read exception registers. */
        " bl Exception_DataAbortCallback   \n"        /* call Exception_DataAbortCallback function here. */
        " pop {r0-r12, lr} \n"
        " eret             \n"
    );
}

ATTR_NAKED WEAKFUNC void EL2_HypModeEntryHandler(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b EL2_HypModeEntryHandler  \n"
        " eret \n"
    );
}

ATTR_NAKED WEAKFUNC void EL2_IRQHandler(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b EL2_IRQHandler  \n"
        " eret \n"
    );
}

ATTR_NAKED WEAKFUNC void EL2_FIQHandler(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b EL2_FIQHandler  \n"
        " eret \n"
    );
}

ATTR_NAKED WEAKFUNC void EL1_Reserved(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " b EL1_Reserved  \n"
    );
}

ATTR_NAKED WEAKFUNC void readExceptionRegInfo(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " ldr r0, =exceptionRegInformation  \n"
        " blx lr  \n"
    );
}

ATTR_NAKED WEAKFUNC void EL1_SVCHandler(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " push {r0-r12, lr}  \n"                   /* save used registers at svc function. */
        " ldr r5, [lr, #-4]  \n"
        " bic r5, r5, #0xFF000000  \n"             /* get software interrupt number. */
        " cpsie i            \n"                   /* enable IRQ. */
        " cmp r4, #0         \n"
        " beq PopStack_SVC   \n"
        "PopStack_SVC: pop {r0-r12, lr} \n"
        " eret \n"
    );
}

ATTR_NAKED WEAKFUNC void EL1_UndefinedException(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " push {r0-r12, lr}               \n"        /* save registers to stack. */
        " mov r0, lr                      \n"        /* transfer undefined lr register as an input parameter to EL1_GetExceptionInformation. */
        " bl EL1_GetExceptionInformation  \n"        /* read exception registers. */
        " bl Exception_UndefinedCallback  \n"        /* call ExceptionUndefinedCallback function here. */
        " cmp r0, #0                      \n"
        " beq ignore_undefinedInstruction \n"
        " ldr r0, [sp, #0x34]             \n"
        " sub r0, r0, #4                  \n"        /* Perform lr adjustment to preferred return address: legacy */
        " str r0, [sp, #0x34]             \n"
        "ignore_undefinedInstruction: pop {r0-r12, lr} \n"
        " eret  \n"
    );
}

ATTR_NAKED WEAKFUNC void EL1_PrefetchAbortException(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " sub lr, lr, #4     \n"                     /* Perform lr adjustment to preferred return address: legacy */
        " push {r0-r12, lr}  \n"                     /* save registers to stack. */
        " mov r0, lr         \n"                     /* transfer abort lr register as an input parameter to EL1_GetExceptionInformation. */
        " bl EL1_GetExceptionInformation      \n"    /* read exception registers. */
        " bl Exception_PrefetchAbortCallback  \n"    /* call Exception_PrefetchAbortCallback function here. */
        " pop {r0-r12, lr}   \n"
        " eret               \n"
    );
}

ATTR_NAKED WEAKFUNC void EL1_DataAbortException(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " sub lr, lr, #8                  \n"        /* Perform lr adjustment to preferred return address: legacy */
        " push {r0-r12, lr}               \n"        /* save registers to stack. */
        " mov r0, lr                      \n"        /* transfer abort lr register as an input parameter to EL1_GetExceptionInformation. */
        " bl EL1_GetExceptionInformation  \n"        /* read exception registers. */
        " bl Exception_DataAbortCallback  \n"        /* call Exception_DataAbortCallback function here. */
        " cmp r0, #0                      \n"
        " bne try_dataabort_again         \n"
        " ldr r0, [sp, #0x34]             \n"
        " add r0, r0, #4                  \n"
        " str r0, [sp, #0x34]             \n"
        "try_dataabort_again: pop {r0-r12, lr} \n"
        " eret       \n"
    );
}

ATTR_NAKED WEAKFUNC void EL1_IRQHandler(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " sub lr, lr, #4     \n"                     /* Perform lr adjustment to preferred return address: legacy */
        " srsfd sp!, #0x13   \n"                     /* Save SPSR_irq and lr_irq into the SVC stack */
        " cps  #0x13         \n"                     /* Switch to SVC mode to support irq preemption. */
        " push {r0-r12, lr}  \n"                     /* Stack registers onto stack */
        /* Arm_trm 2.2.9 An additional set of registers is used by Advanced SIMD and floating-point
        instructions. These registers can be accessed as 32-bit single-precision registers S0-S31, or
        as 64-bit double-precision registers D0- D31, or 128-bit quad registers Q0-Q15, but these are
        different views of the same data. Data can be transferred between the Advanced SIMD and
        floating-point registers and the integer registers */
        /*The Advanced SIMD and floating-point features controlled by this field are:
        • Floating-point instructions.
        • Advanced SIMD instructions, both integer and floating-point.
        • Advanced SIMD and floating-point registers D0-D31 and their views as S0-S31 and Q0-Q15.
        • FPSCR, FPSID, MVFR0, MVFR1, MVFR2, FPEXC system registers.*/
        /* FPSID, MVFR0, MVFR1, MVFR2, read only */
        /*Demo tha6412,tha6206configed as hard float and double-precision */
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
        " VMRS R1, FPSCR     \n"                     /* save VFP register FPSCR to R1. */
        " PUSH {R1}          \n"                     /* Push R1 to stack. */
        " VMRS R1, FPEXC     \n"                     /* save VFP register FPEXC to R1. */
        " PUSH {R1}          \n"                     /* Push R1 to stack. */
        " vpush {d0-d15}     \n"                     /* save VFP register d0-d15 to stack. */
        " vpush {d16-d31}    \n"                     /* save VFP register d16-d31 to stack. */
#endif
        /*Demo tha6104 is configured as hard float and single-precision */
#if defined(THA6_THA6104)
        " VMRS R1, FPSCR     \n"                    /* save VFP register FPSCR to R1. */
        " PUSH {R1}          \n"                    /* Push R1 to stack. */
        " VMRS R1, FPEXC     \n"                    /* save VFP register FPEXC to R1. */
        " PUSH {R1}          \n"                    /* Push R1 to stack. */
        " vpush {s0-s15}     \n"                    /* save VFP register s0-s15 to stack. */
        " vpush {s16-s31}    \n"                    /* save VFP register s16-s31 to stack. */
#endif
        " and r1, sp, #4     \n"                     /* Check if the sp is 8-byte aligned, if not r1 = 4. AAPCS mandates 8-byte alignment at all external boundaries (i.e. separately compiled or assembled files). */
        " sub sp, sp, r1     \n"                     /* Sub 0 (already aligned) or 4 (misaligned) */
        " mrc p15,0,r0,c12,c12,0  \n"                /* Read ICC_IAR1 into r0, ACK Int. r0 will contain the IRQ source number, source identified, interrupt active */
        "Hanlde_Another_IRQ: push {r0-r1}  \n"                        /* Push r1 (adjustment info) and intno to the stack for later usage. */
        " cpsie i  \n"                             /* Re-enable interrupts (IRQ) */
        " ldr r1, =GICIsrVectorTable  \n"          /* Load in r1 base of the IRQ vector table */
        " ldr r1, [r1, r0, lsl #2]  \n"            /* Load in r1 = r1 + r0*4. Multiply by 4: offset from the base of the vector table */
        " blx r1  \n"                              /* Branch to the C Interrupt Service Routine */
        " cpsid i  \n"                             /* Disable interrupts (IRQ) */
        " pop {r0-r1}  \n"                         /* R1 save sp alignment info. should not crashed later. */
        " mrc p15, 0, r2, c12,c12,4  \n"           /* read ICC_CTLR */
        " tst r2, #0x02  \n"                       /* set according to EOImode. 0, framework just EOI inter, 1 should deactive int. */
        " bne EOIMODE_Enable_IRQ  \n"              /* indicate EOImode== 1. */
        " mcr p15, 0, r0, c12, c12, 1  \n"         /* indicate EOImode == 0. Write r0 to ICC_EOIR1 */
        " isb  \n"
        " b   EOIMODE_Disable_IRQ  \n"
        "EOIMODE_Enable_IRQ: mcr p15, 0, r0, c12, c11, 1  \n"         /* write ICC_DIR to deactive interrupt. */
        " isb  \n"
        " b   EOIMODE_Disable_IRQ  \n"
        "EOIMODE_Disable_IRQ: mrc p15, 0, r0, c12, c12, 0  \n"         /* Read ICC_IAR1 into r0, ACK Int. Before restoring the context, check if any other interrupt is pending */
        " ldr r2, =0x3FF  \n"                      /* 1023: spurios interrupt, meaning no interrupt pending */
        " cmp r0, r2  \n"                          /* Compare with what we read */
        " bne Hanlde_Another_IRQ  \n"              /* If there is another interrupt pending, handle it */
        " add sp, sp, r1  \n"                      /* Unadjust sp as per previous state */
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
        " vpop {d16-d31}  \n"                      /* Pop VFP regsiter d16-d31. */
        " vpop {d0-d15}  \n"                       /* Pop VFP regsiter d0-d15. */
        " POP {R1}  \n"                            /* Pop regsiter to R1. */
        " VMSR FPEXC, R1  \n"                      /* save R1 to VFP regsiter FPEXC. */
        " POP {R1}  \n"                            /* Pop regsiter to R1. */
        " VMSR FPSCR, R1  \n"                      /* save R1 to VFP regsiter FPEXC. */
#endif
#if defined(THA6_THA6104)
        " vpop {s16-s31}  \n"                       /* Pop VFP regsiter s16-s31. */
        " vpop {s0-s15}  \n"                        /* Pop VFP regsiter s0-s15. */
        " POP {R1}  \n"                             /* Pop regsiter to R1. */
        " VMSR FPEXC, R1  \n"                       /* save R1 to VFP regsiter FPEXC. */
        " POP {R1}  \n"                             /* Pop regsiter to R1. */
        " VMSR FPSCR, R1  \n"                       /* save R1 to VFP regsiter FPEXC. */
#endif
        " pop {r0-r12, lr}  \n"                    /* Pop the rest of the AAPCS registers to restore the context */
        " rfefd sp!  \n"                           /* Return from exception by restoring the pc from the lr_irq and the CPSR from SPSR_irq saved in the SVC stack */
        " eret  \n"                                /* Never executed. eret = MOVS pc, lr; it can be used but the handler should be slightly modified */
    );
}

ATTR_NAKED WEAKFUNC void EL1_FIQHandler(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " sub lr, lr, #4     \n"                     /* Perform lr adjustment to preferred return address: legacy */
        " srsfd sp!, #0x13   \n"                     /* Save SPSR_fiq and lr_fiq into the SVC stack. */
        " cps  #0x13         \n"                     /* Switch to SVC mode to support fiq preemption. */
        " push {r0-r12, lr}  \n"                     /* Stack registers onto the SVC stack */
        /* Arm_trm 2.2.9 An additional set of registers is used by Advanced SIMD and floating-point
        instructions. These registers can be accessed as 32-bit single-precision registers S0-S31, or
        as 64-bit double-precision registers D0- D31, or 128-bit quad registers Q0-Q15, but these are
        different views of the same data. Data can be transferred between the Advanced SIMD and
        floating-point registers and the integer registers */
        /*The Advanced SIMD and floating-point features controlled by this field are:
        • Floating-point instructions.
        • Advanced SIMD instructions, both integer and floating-point.
        • Advanced SIMD and floating-point registers D0-D31 and their views as S0-S31 and Q0-Q15.
        • FPSCR, FPSID, MVFR0, MVFR1, MVFR2, FPEXC system registers.*/
        /* FPSID, MVFR0, MVFR1, MVFR2, read only */
        /*Demo tha6412,tha6206configed as hard float and double-precision */
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
        " VMRS R1, FPSCR     \n"                     /* save VFP register FPSCR to R1. */
        " PUSH {R1}          \n"                     /* Push R1 to stack. */
        " VMRS R1, FPEXC     \n"                     /* save VFP register FPEXC to R1. */
        " PUSH {R1}          \n"                     /* Push R1 to stack. */
        " vpush {d0-d15}     \n"                     /* save VFP register d0-d15 to stack. */
        " vpush {d16-d31}    \n"                     /* save VFP register d0-d15 to stack. */
#endif
        /*Demo tha6104 is configured as hard float and single-precision */
#if defined(THA6_THA6104)
        " VMRS R1, FPSCR     \n"                    /* save VFP register FPSCR to R1. */
        " PUSH {R1}          \n"                    /* Push R1 to stack. */
        " VMRS R1, FPEXC     \n"                    /* save VFP register FPEXC to R1. */
        " PUSH {R1}          \n"                    /* Push R1 to stack. */
        " vpush {s0-s15}     \n"                    /* save VFP register s0-s15 to stack. */
        " vpush {s16-s31}    \n"                    /* save VFP register s16-s31 to stack. */
#endif
        " and r1, sp, #4     \n"                     /* Check if the sp is 8-byte aligned, if not r1 = 4. AAPCS mandates 8-byte alignment at all external boundaries (i.e. separately compiled or assembled files). */
        " sub sp, sp, r1     \n"                     /* Sub 0 (already aligned) or 4 (misaligned) */
        " mrc p15,0,r0,c12,c8,0  \n"                 /* Read ICC_IAR0 into r0 */
        "Hanlde_Another_FIRQ: push {r0-r1}  \n"      /* Push interrupt number and r1 (adjustment info) to the stack. */
        " cpsie f  \n"                               /* Re-enable interrupts (FIQ) */
        " ldr r1, =GICIsrVectorTable  \n"            /* Load in r1 base of the IRQ vector table */
        " ldr r1, [r1, r0, lsl #2]  \n"              /* Load in r1 = r1 + r0*4. Multiply by 4: offset from the base of the vector table */
        " blx r1  \n"                                /* Branch to the C Interrupt Service Routine */
        " cpsid f  \n"                               /* Disable interrupts (FIQ) */
        " pop {r0-r1}  \n"                           /* restore aligment and interrupt number information. */
        " mrc p15, 0, r2, c12,c12,4  \n"             /* read ICC_CTLR */
        " tst r2, #0x02  \n"                         /* set according to EOImode. 0, framework just EOI inter, 1 should deactive int. */
        " bne EOIMODE_Enable_FIRQ  \n"               /* indicate EOImode == 1. */
        " mcr p15,0,r0,c12,c8,1  \n"                 /* EOImode == 0. Write r0 to ICC_EOIR0 */
        " isb  \n"
        " b   EOIMODE_Disable_FIRQ  \n"
        "EOIMODE_Enable_FIRQ: mcr p15, 0, r0, c12, c11, 1  \n"           /* EOImode == 1. write ICC_DIR to deactive interrupt. */
        " isb  \n"
        "EOIMODE_Disable_FIRQ: mrc p15,0,r0,c12,c8,0  \n"                /* Read ICC_IAR0 into r0 Before restoring the context, check if any other interrupt is pending */
        " ldr r2, =0x3FF  \n"                        /* 1023: spurios interrupt, meaning no interrupt pending */
        " cmp r0, r2  \n"                            /* Compare with what we read */
        " bne Hanlde_Another_FIRQ  \n"               /* If there is another interrupt pending, handle it */
        " add sp, sp, r1  \n"                        /* Unadjust sp as per previous state */
#if defined(THA6_THA6412) || defined(THA6_THA6206) || defined(THA6_THA6206D)
        " vpop {d16-d31}  \n"                        /* Pop VFP regsiter d16-d31. */
        " vpop {d0-d15}  \n"                         /* Pop VFP regsiter d0-d15. */
        " POP {R1}  \n"                              /* Pop regsiter to R1. */
        " VMSR FPEXC, R1  \n"                        /* save R1 to VFP regsiter FPEXC. */
        " POP {R1}  \n"                              /* Pop regsiter to R1. */
        " VMSR FPSCR, R1  \n"                        /* save R1 to VFP regsiter FPEXC. */
#endif
#if defined(THA6_THA6104)
        " vpop {s16-s31}  \n"                       /* Pop VFP regsiter s16-s31. */
        " vpop {s0-s15}  \n"                        /* Pop VFP regsiter s0-s15. */
        " POP {R1}  \n"                             /* Pop regsiter to R1. */
        " VMSR FPEXC, R1  \n"                       /* save R1 to VFP regsiter FPEXC. */
        " POP {R1}  \n"                             /* Pop regsiter to R1. */
        " VMSR FPSCR, R1  \n"                       /* save R1 to VFP regsiter FPEXC. */
#endif
        " pop {r0-r12, lr}  \n"                      /* Pop the rest of the AAPCS registers to restore the context */
        " rfefd sp!  \n"                             /* Return from exception by restoring the pc from the lr_irq and the CPSR from SPSR_irq saved in the stack */
        " eret  \n"                                  /* Never executed. eret = MOVS pc, lr; it can be used but the handler should be slightly modified */
    );
}

/* Dummp for default IRQ Handler. */
ATTR_NAKED WEAKFUNC void dummp(void)
{
    /* #Violation: exception_c_REF_2 */
    ASM_VOLATILE
    (
        " nop      \n"
        " b dummp  \n"
    );
}

#define SDK_STOP_SEC_EXCEPTION_HANDLER
/* #Violation: exception_c_REF_1 */
#include "Sdk_MemMap.h"

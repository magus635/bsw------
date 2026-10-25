/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: common_hal.h
 * Author:    30032
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file defines macro provided by base module.
 ************************************************************************************************/
/*
* #Violation Summary
*
* #common_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
* #common_h_REF_2:MISRAC2012-Rule-20.10;
* Justification:Use glue operator to construct the exclusive area function name.
*
* #common_h_REF_3:MISRAC2012-Dir-4.9;
* Justification: Function like macro are used to reduce code complexity.
*/

#ifndef COMMON_H_
#define COMMON_H_
#include "compilertypes.h"

#ifndef NULL_PTR
#define NULL_PTR ((void *)0)
#endif


#ifndef STD_ON
#define STD_ON (1U)
#endif

#ifndef STD_OFF
#define STD_OFF (0U)
#endif

/* define macro BIT(n). */
#ifndef BIT
#define BIT(n) (1U << n)
#endif

#ifndef INPUT_ARG_DETECT
#define INPUT_ARG_DETECT STD_OFF
#endif

/* define macro BITMASK. */
#ifndef BITMASK
#define BITMASK(n) (~(1U << n))
#endif


/* define float32 and float64 EPSILON value and check function */
#define FLOAT_EPSILON 1e-6F
/* #Violation: common_h_REF_3 */
#define IS_ZERO_FLT(value) (((value) < FLOAT_EPSILON) && ((value) > -FLOAT_EPSILON))


/* define GET_CP/SET_CP/GET_CP64/SET_CP64 to mask MRC/MCR/MRRC/MCRR operation.
 * cp, op1, CRn, CRm and op2 are digital number. Rt is uint32 or uint64 variable.
 */
/* #Violation: common_h_REF_2 */
#define GET_CP(cp, op1, Rt, CRn, CRm, op2)                                                                             \
    ASM_VOLATILE("MRC p" #cp ", " #op1 ", %0, c" #CRn ", c" #CRm ", " #op2 : "=r"(Rt) : : "memory")
/* #Violation: common_h_REF_2 */
#define SET_CP(cp, op1, Rt, CRn, CRm, op2)                                                                             \
    ASM_VOLATILE("MCR p" #cp ", " #op1 ", %0, c" #CRn ", c" #CRm ", " #op2 : : "r"(Rt) : "memory")
/* #Violation: common_h_REF_2 */
#define GET_CP64(cp, op1, Rt, CRm) {uint32 val1_temp = 0U, val2_temp = 0U;  \
    ASM_VOLATILE("MRRC p" #cp ", " #op1 ", %0, %1, c" #CRm : "=r"(val1_temp), "=r"(val2_temp): : "memory"); \
    Rt = (((uint64)val2_temp) << 32) + val1_temp;}
/* #Violation: common_h_REF_2 */
#define SET_CP64(cp, op1, Rt, CRm) {uint32 val1_temp, val2_temp; \
    val1_temp = (uint32) Rt; \
    val2_temp = (uint32)(Rt >> 32);    \
    ASM_VOLATILE("MCRR p" #cp ", " #op1 ", %0, %1, c" #CRm :: "r"(val1_temp), "r"(val2_temp): "memory");}

#define DMB() ASM_VOLATILE("dmb" ::: "memory")
#define DSB() ASM_VOLATILE("dsb" ::: "memory")
#define ISB() ASM_VOLATILE("isb" ::: "memory")

/*define CPU modes. */
/* #Violation: common_h_REF_1 */
#define MODE_USR       (0x10)
#define MODE_FIQ       (0x11)
#define MODE_IRQ       (0x12)
#define MODE_SVC       (0x13)
/* #Violation: common_h_REF_1 */
#define MODE_MON       (0x16)
#define MODE_ABT       (0x17)
#define MODE_UND       (0x1B)
#define MODE_SYS       (0x1F)
/* #Violation: common_h_REF_1 */
#define MODE_HYP       (0x1A)
/* #Violation: common_h_REF_1 */
#define SPURIOUSID     (0x3FF)
/* #Violation: common_h_REF_1 */
#define EOIMODEBIT     (0x02)
/* #Violation: common_h_REF_1 */
#define TOTALIRQNUM    (992)

#if defined(THA6_REG_ENDINIT_CRITICAL_PROTECT)
#define DISABLE_ALL_INTERRUPTS()    ASM_VOLATILE("CPSID if\n")
#define ENABLE_ALL_INTERRUPTS()     ASM_VOLATILE("CPSIE if\n")
#else
#define DISABLE_ALL_INTERRUPTS()    
#define ENABLE_ALL_INTERRUPTS()     
#endif

#endif /* COMMON_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

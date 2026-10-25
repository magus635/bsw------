/**************************************************************************************************
 * Copyright (c) Tongxin Microelectronics Co., Ltd. All Rights Reserved.
 * FileName: compiler_tasking.h
 * Author:    30011
 * Version:   V1.2.0
 * Date:      2026/02/28
 * Description: This file defines related macro related to TASKING compiler.
 ************************************************************************************************/
/*
*#Violation Summary
*
* #complier_tasking_h_REF_1:MISRAC2012-Rule-2.5;;
* Justification: The macros are reserved for upper layers
*
* #complier_tasking_h_REF_2:MISRAC2012-Rule-20.10;
* Justification:Use glue operator to construct the exclusive area function name.
*
*/

#ifndef COMPILER_TASKING_H_
#define COMPILER_TASKING_H_
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#ifndef STRINGIFY
/* #Violation: complier_tasking_h_REF_2 */
#define STRINGIFY(x)     #x
#endif

#ifndef EXPAND_PRAGMA
#define EXPAND_PRAGMA(x) _Pragma(STRINGIFY(x))
#endif

#ifndef ASM
#define ASM __asm
#endif

#ifndef ASM_VOLATILE
#define ASM_VOLATILE __asm volatile
#endif

/* INLINE function is a global symbol and will be inline if optimization isn't -O0 */
#ifndef INLINE
#define INLINE inline
#endif
/* LOCAL_INLINE function is a local symbol and will be inline if optimization isn't -O0 */
#ifndef LOCAL_INLINE
#define LOCAL_INLINE static inline
#endif
/* LOCAL_FORCEINLINE function is a local symbol and will be inline */
#ifndef LOCAL_FORCEINLINE
#define LOCAL_FORCEINLINE __attribute__((always_inline)) static inline
#endif
/*define ALIGNED macro. */
#ifndef ALIGNED
#define ALIGNED(x) __attribute__((aligned(x)))
#endif
/* define __attribute__((naked)) attribute. */
#define ATTR_NAKED __frame()
#define PACKED_ALIGN(x) __attribute__((packed)) __attribute__((aligned(x)))
/* define __attribute__((weak)) attribute. */
#define WEAKFUNC __attribute__((weak))

/* #Violation: complier_tasking_h_REF_1 */
#define SECTION_ASM(name,ctrIns,opt)
/* #Violation: complier_tasking_h_REF_1 */
#define REPT_ASM                        .REPEAT
/* #Violation: complier_tasking_h_REF_1 */
#define ENDR                            .ENDREP
/* #Violation: complier_tasking_h_REF_1 */
#define END_FILE                        .END
/* #Violation: complier_tasking_h_REF_1 */
#define WORD_ASM                        .DW
/* #Violation: complier_tasking_h_REF_1 */
#define GLOBAL_ASM                      .global
/* #Violation: complier_tasking_h_REF_1 */
#define TYPE_ASM(name,typeclass)
/* #Violation: complier_tasking_h_REF_1 */
#define LOCALFUNC_ASM(name)
/* #Violation: complier_tasking_h_REF_1 */
#define WEAKFUNC_ASM(name)              .WEAK name
/* #Violation: complier_tasking_h_REF_1 */
#define SP_FORCE_ALIGN_ASM(cmd)

#ifndef STOP_SECTION
#define STOP_SECTION                     _Pragma("section restore")
#endif
#ifndef PRAGMA_HELPER
#define PRAGMA_HELPER(x)                 _Pragma(#x)
#endif

#ifndef MEMMAP_START_BSS
#define MEMMAP_START_BSS(SectionName)    PRAGMA_HELPER(section SectionName)
#endif
#ifndef MEMMAP_STOP_BSS
#define MEMMAP_STOP_BSS()                STOP_SECTION
#endif

#ifndef MEMMAP_START_RODATA
#define MEMMAP_START_RODATA(SectionName) PRAGMA_HELPER(section SectionName)
#endif
#ifndef MEMMAP_STOP_RODATA
#define MEMMAP_STOP_RODATA()             STOP_SECTION
#endif

#ifndef MEMMAP_START_DATA
#define MEMMAP_START_DATA(SectionName)   PRAGMA_HELPER(section SectionName)
#endif
#ifndef MEMMAP_STOP_DATA
#define MEMMAP_STOP_DATA()               STOP_SECTION
#endif

#ifndef MEMMAP_START_TEXT
#define MEMMAP_START_TEXT(SectionName)   PRAGMA_HELPER(section SectionName)
#endif
#ifndef MEMMAP_STOP_TEXT
#define MEMMAP_STOP_TEXT()               STOP_SECTION
#endif

#endif /* COMPILER_TASKING_H_ */
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/

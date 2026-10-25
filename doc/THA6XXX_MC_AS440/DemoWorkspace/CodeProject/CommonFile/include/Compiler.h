/**************************************************************************************************
 *
 ***************************************************************************************************/
/**************************************************************************************************
 *   FileName             : Compiler.h
 *
 *   Platform             : AUTOSAR
 *
 *   brief                : The file Compiler.h shall contain the definitions and macros specified in
 *                          Specification of Compiler Abstraction AUTOSAR Release 4.4.0 chapter 7.1.5.
 *                          Those are fix for one specific compiler and platform.
 *
 *   Autosar Version      : 4.4.0
 *
 *   SW Version           : 1.0.0
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ***************************************************************************************************/
/**************************************************************************************************/
#ifndef COMPILER_H_
#define COMPILER_H_

#ifdef __cplusplus
extern "C" {
#endif

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#include "Compiler_Cfg.h"
#include "compilertypes.h"

#define STRINGIFY(x)     #x
#define EXPAND_PRAGMA(x) _Pragma(STRINGIFY(x))

/* Abstraction of the keyword inline in functions with static scope*/

/* ADS compiler */
#if defined(__ARMCC_VERSION)
#define _ADS_C_THA6_
#endif /* defined(__ARMCC_VERSION) */

/*  GreenHills compiler */
#if defined(__ghs__)

#define _GHS_C_THA6_

#endif /* defined(__ghs__) */

/* IAR compiler */
#if defined(__ICCARM__)

#define _IAR_C_THA6_

#endif /* defined(__ICCARM__) */

/* HIGHTEC compiler */
#if defined(__HIGHTEC__)

#define _HIGHTEC_C_THA6_

#endif /* defined(__HIGHTEC__) */

/* TASKING compiler */
#if defined(__TASKING__)

#define _TASKING_C_THA6_

#endif /* defined(__TASKING__) */


/* ADS compiler */
#if defined(_ADS_C_THA6_)

/* for ADS compiler,INLINE function will be inline if optimization is -Oz or -Os.
* if compiler  decides not to inlineand it, INLINE may cause error:
* "Error: L6218E: Undefined symbol <symbol> (referred from <file>)"
* To avoid this problem, there are several options:
-Provide an equivalent implementation of the function.
-Change the inline or __inline__ keyword to static inline.
-Remove the inline or __inline__ keyword, because it is only acting as a suggestion.
-Compile your program using the GNU C90 dialect, using the -std=gnu90 option.*/
#ifndef INLINE
#define INLINE __inline
#endif
/* for ADS compiler,INLINE function will be inline if optimization is -Oz or -Os. */
#ifndef LOCAL_INLINE
#define LOCAL_INLINE static __inline
#endif


#define ADS_STOP_SECTION                 _Pragma("clang section bss=\"\" data=\"\" text=\"\"")

/*        MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified_core0")  */
#define MEMMAP_START_BSS(SectionName)    EXPAND_PRAGMA(clang section bss = SectionName)
#define MEMMAP_STOP_BSS()                ADS_STOP_SECTION

#define MEMMAP_START_RODATA(SectionName) EXPAND_PRAGMA(clang section rodata = SectionName)
#define MEMMAP_STOP_RODATA()             ADS_STOP_SECTION

#define MEMMAP_START_DATA(SectionName)   EXPAND_PRAGMA(clang section data = SectionName)
#define MEMMAP_STOP_DATA()               ADS_STOP_SECTION

#define MEMMAP_START_TEXT(SectionName)   EXPAND_PRAGMA(clang section text = SectionName)
#define MEMMAP_STOP_TEXT()               ADS_STOP_SECTION

#endif /* defined(_ADS_C_THA6_)  */

#if defined(_GHS_C_THA6_)
#ifndef INLINE
#define INLINE  __inline
#endif
#ifndef LOCAL_INLINE
#define LOCAL_INLINE  static __inline
#endif


#define MEMMAP_START_BSS(SectionName)    EXPAND_PRAGMA(ghs section bss = SectionName)
#define MEMMAP_STOP_BSS()                EXPAND_PRAGMA(ghs section bss = default)

#define MEMMAP_START_RODATA(SectionName) EXPAND_PRAGMA(ghs section rodata = SectionName)
#define MEMMAP_STOP_RODATA()             EXPAND_PRAGMA(ghs section rodata = default)

#define MEMMAP_START_DATA(SectionName)   EXPAND_PRAGMA(ghs section data = SectionName)
#define MEMMAP_STOP_DATA()               EXPAND_PRAGMA(ghs section data = default)

#define MEMMAP_START_TEXT(SectionName)   EXPAND_PRAGMA(ghs section text = SectionName)
#define MEMMAP_STOP_TEXT()               EXPAND_PRAGMA(ghs section text = default)

#endif /* defined(_GHS_C_THA6_) */

#if defined(_IAR_C_THA6_) 

/* For IAR compiler,INLINE function will be inline if optimization is -Oh -Ohz -Ohs,
 * * if compiler  decides not to inlineand it, INLINE may cause error:
* "Error: L6218E: Undefined symbol <symbol> (referred from <file>)"
* To avoid this problem, there are several options:
-Provide an equivalent implementation of the function.
-Change the inline or  keyword to static inline.
-Remove the inline or  keyword, because it is only acting as a suggestion.
-Compile your program using the GNU C90 dialect, using the -std=gnu90 option.*/
#ifndef INLINE
#define INLINE  inline
#endif
/* For IAR compiler,INLINE function will be inline if optimization is -Oh -Ohz -Ohs */
#ifndef LOCAL_INLINE
#define LOCAL_INLINE  static inline
#endif
#ifndef ALIGNED
#define ALIGNED(x) __attribute__((aligned(x)))
#endif

#define MEMMAP_START_BSS(SectionName)    EXPAND_PRAGMA(default_variable_attributes = @SectionName)
#define MEMMAP_STOP_BSS()                EXPAND_PRAGMA(default_variable_attributes =)

#define MEMMAP_START_RODATA(SectionName) EXPAND_PRAGMA(default_variable_attributes = @SectionName)
#define MEMMAP_STOP_RODATA()             EXPAND_PRAGMA(default_variable_attributes =)

#define MEMMAP_START_DATA(SectionName)   EXPAND_PRAGMA(default_variable_attributes = @SectionName)
#define MEMMAP_STOP_DATA()               EXPAND_PRAGMA(default_variable_attributes =)

#define MEMMAP_START_TEXT(SectionName)   EXPAND_PRAGMA(default_function_attributes = @SectionName)
#define MEMMAP_STOP_TEXT()               EXPAND_PRAGMA(default_function_attributes =)

#endif /* defined(_IAR_C_THA6_) */



#if defined(_HIGHTEC_C_THA6_)


#ifndef INLINE
#define INLINE  __inline__
#endif
/* For IAR compiler,INLINE function will be inline if optimization is -Oh -Ohz -Ohs */
#ifndef LOCAL_INLINE
#define LOCAL_INLINE  static __inline__
#endif
#ifndef ALIGNED
#define ALIGNED(x) __attribute__((aligned(x)))
#endif

#define STOP_SECTION                 _Pragma("clang section bss=\"\" data=\"\" text=\"\"")

/*        MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified_core0")  */
#define MEMMAP_START_BSS(SectionName)    EXPAND_PRAGMA(clang section bss = SectionName)
#define MEMMAP_STOP_BSS()                STOP_SECTION

#define MEMMAP_START_RODATA(SectionName) EXPAND_PRAGMA(clang section rodata = SectionName)
#define MEMMAP_STOP_RODATA()             STOP_SECTION

#define MEMMAP_START_DATA(SectionName)   EXPAND_PRAGMA(clang section data = SectionName)
#define MEMMAP_STOP_DATA()               STOP_SECTION

#define MEMMAP_START_TEXT(SectionName)   EXPAND_PRAGMA(clang section text = SectionName)
#define MEMMAP_STOP_TEXT()               STOP_SECTION

#endif /*defined(_HIGHTEC_C_THA6_)  */



#if defined(_TASKING_C_THA6_)


#ifndef INLINE
#define INLINE  __inline__
#endif
/* For IAR compiler,INLINE function will be inline if optimization is -Oh -Ohz -Ohs */
#ifndef LOCAL_INLINE
#define LOCAL_INLINE  static __inline__
#endif
#ifndef ALIGNED
#define ALIGNED(x) __attribute__((aligned(x)))
#endif

#define STOP_SECTION                     _Pragma("section restore")
#define PRAGMA_HELPER(x)                 _Pragma(#x)

/*        MEMMAP_START_BSS(".mcal_bss_asil_d_unspecified_core0")  */
#define MEMMAP_START_BSS(SectionName)    PRAGMA_HELPER(section SectionName)
#define MEMMAP_STOP_BSS()                STOP_SECTION

#define MEMMAP_START_RODATA(SectionName) PRAGMA_HELPER(section SectionName)
#define MEMMAP_STOP_RODATA()             STOP_SECTION

#define MEMMAP_START_DATA(SectionName)   PRAGMA_HELPER(section SectionName)
#define MEMMAP_STOP_DATA()               STOP_SECTION

#define MEMMAP_START_TEXT(SectionName)   PRAGMA_HELPER(section SectionName)
#define MEMMAP_STOP_TEXT()               STOP_SECTION

#endif /*defined(_TASKING_C_THA6_)  */


/***************************************************************************************************
 *                              General Definitions
 ****************************************************************************************************/
/****************************************************************************************************
 *   brief                   : The memory class AUTOMATIC shall be provided as empty definition, used
 *                             for the declaration of local pointers.
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00046
 *
 ****************************************************************************************************/
#define AUTOMATIC

/****************************************************************************************************
 *   brief                   : The memory class TYPEDEF shall be provided as empty definition.
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00059
 *
 ****************************************************************************************************/
#define TYPEDEF

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall provide the NULL_PTR define with a void
 *                             pointer to zero definition.
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00051
 *
 ****************************************************************************************************/
#define NULL_PTR ((void *)0) /*Remove from AUTOSAR R211*/

/***************************************************************************************************
 *                              Function Definitions
 ****************************************************************************************************/
/****************************************************************************************************
*   brief                   : The compiler abstraction shall define the FUNC macro for the declaration
*                             and definition of functions, that ensures correct syntax of function
*                             declarations as required by a specific compiler.
*
*   Parameters In           : retype: return type of the function
*                             memclass: classification of the function itself
*
*   AUTOSAR_Requirement     : SWS_COMPILER_00001

****************************************************************************************************/
#define FUNC(rettype, memclass)                   rettype

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the P2VAR macro for the
 *declaration and definition of pointers in RAM, pointing to variables.
 *
 *   Parameters In           : ptrtype: type of the referenced variable
 *                             memclass: classification of the function itself
 *                             ptrclass: defines the classification of the pointer's distance
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00006
 *
 ****************************************************************************************************/
#define P2VAR(ptrtype, memclass, ptrclass)        ptrtype *

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the P2CONST macro for the
 *declaration and definition of pointers in RAM pointing to constants
 *
 *   Parameters In           : ptrtype: type of the referenced variable
 *                             memclass: classification of the function itself
 *                             ptrclass: defines the classification of the pointer's distance
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00013
 *
 ****************************************************************************************************/
#define P2CONST(ptrtype, memclass, ptrclass)      const ptrtype *

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the CONSTP2VAR macro for the
 *declaration and definition of constant pointers accessing variables.
 *
 *   Parameters In           : ptrtype: type of the referenced variable
 *                             memclass: classification of the function itself
 *                             ptrclass: defines the classification of the pointer's distance
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00031
 *
 ****************************************************************************************************/
#define CONSTP2VAR(ptrtype, memclass, ptrclass)   ptrtype *const

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the CONSTP2CONST macro for the
 *declaration and definition of constant pointers accessing constants.
 *
 *   Parameters In           : ptrtype: type of the referenced variable
 *                             memclass: classification of the function itself
 *                             ptrclass: defines the classification of the pointer's distance
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00032
 *
 ****************************************************************************************************/
#define CONSTP2CONST(ptrtype, memclass, ptrclass) const ptrtype *const

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the P2FUNC macro for the type
 *definition of pointers to functions.
 *
 *   Parameters In           : ptrtype: type of the referenced variable
 *                             memclass: classification of the function itself
 *                             ptrclass: defines the classification of the pointer's distance
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00039
 *
 ****************************************************************************************************/
#define P2FUNC(rettype, ptrclass, fctname)        rettype(*fctname)

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the CONST macro for the
 *declaration and definition of constants.
 *
 *   Parameters In           : consttype: type of the constant
 *                             memclass: classification of the function itself
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00023
 *
 ****************************************************************************************************/
#define CONST(consttype, memclass)                const consttype

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the VAR macro for the declaration
 *                             and definition of variables.
 *
 *   Parameters In           : vartype: type of the variable
 *                             memclass: classification of the function itself
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00026
 *
 ****************************************************************************************************/
#define VAR(vartype, memclass)                    vartype

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the CONSTP2FUNC macro for the
 *type definition of constant pointers to functions.
 *
 *   Parameters In           : rettype: return type of the function
 *                             ptrclass: defines the classification of the pointer's distance
 *                             fctname: function name respectively name of the defined type
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00065
 *
 ****************************************************************************************************/
#define CONSTP2FUNC(rettype, ptrclass, fctname)   rettype(*const fctname)

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the FUNC_P2CONST macro for the
 *                             declaration and definition of functions returning a pointer to a
 *constant.
 *
 *   Parameters In           : rettype: return type of the function
 *                             ptrclass: defines the classification of the pointer's distance
 *                             memclass: classification of the function itself
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00061
 *
 ****************************************************************************************************/
#define FUNC_P2CONST(rettype, ptrclass, memclass) const ptrclass rettype *memclass

/****************************************************************************************************
 *   brief                   : The compiler abstraction shall define the FUNC_P2VAR macro for the
 *declaration and definition of functions returning a pointer to a variable.
 *
 *   Parameters In           : rettype: return type of the function
 *                             ptrclass: defines the classification of the pointer's distance
 *                             memclass: classification of the function itself
 *
 *   AUTOSAR_Requirement     : SWS_COMPILER_00063
 *
 ****************************************************************************************************/
#define FUNC_P2VAR(rettype, ptrclass, memclass)   ptrclass rettype *memclass

/**
 * @brief The compiler abstraction for pointer to pointer to variable.
 */
#define P2P2VAR(ptrtype, memclass, ptrclass)      ptrtype **

/**
 * @brief The compiler abstraction for pointer to pointer to constant.
 */
#define P2P2CONST(ptrtype, memclass, ptrclass)    const ptrtype **

/***************************************************************************************************
 *                               Version Information
 ***************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* COMPILER_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

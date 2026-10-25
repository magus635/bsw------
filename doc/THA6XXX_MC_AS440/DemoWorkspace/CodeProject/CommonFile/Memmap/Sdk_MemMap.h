/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Sdk_MemMap.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : None
*
*   brief                 : This document specifies mechanisms for the mapping of code and data to
*                           specific memory sections via memory mapping file. For many ECUs and
*                           microcontroller platforms it is of utmost necessity to be able to map
*                           code, variables and constants module wise to specific memory sections.
*                           This file contains sample code only. It is not part of the production
*                           code deliverables.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c)
*   All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Revision Control History                                               **
****************************************************************************************************/
/*
*   V1.0.0:  01-Feb-2023  : Initial Version
*
****************************************************************************************************/
/*
* #Violation Summary
*
* #sdk_memmap_h_REF_1:MISRAC2012-Dir-1.1;
* Justification:Compiler instruction specific format.
*
* #sdk_memmap_h_REF_2:MISRAC2012-Dir-20.5;
* Justification:Memmap file specific syntax format.
*
* #sdk_memmap_h_REF_3:MISRAC2012-Dir-4.10;
* Justification:Memmap file specific syntax format.
*/


/**
* #brief Symbol used for checking correctness of the includes
*/
#define MEMMAP_ERROR


/**************************************** Config Data Sections *******************************/
#if defined SDK_START_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE
    #define INSIDE_SDK_START_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section data=".uncached_data"
    #elif defined __ghs__
        #pragma ghs section data=".uncached_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".uncached_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".uncached_data"
    #elif defined __TASKING__
        #pragma section .data=uncached_data
    #endif

#elif defined SDK_STOP_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE
        #undef INSIDE_SDK_START_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_GLOBAL_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #endif

#elif defined SDK_START_SEC_INIT_VAR_IRQ_VECTOR
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_INIT_VAR_IRQ_VECTOR
    #define INSIDE_SDK_START_SEC_INIT_VAR_IRQ_VECTOR

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_INIT_VAR_IRQ_VECTOR
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section data=".IRQ_init_vector"
    #elif defined __ghs__
        #pragma ghs section data=".IRQ_init_vector"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".IRQ_init_vector"
    #elif defined __HIGHTEC__
        #pragma clang section data=".IRQ_init_vector"
    #elif defined __TASKING__
        #pragma section .data=IRQ_init_vector
    #endif

#elif defined SDK_STOP_SEC_INIT_VAR_IRQ_VECTOR

    #ifdef INSIDE_SDK_START_SEC_INIT_VAR_IRQ_VECTOR
        #undef INSIDE_SDK_START_SEC_INIT_VAR_IRQ_VECTOR
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_INIT_VAR_IRQ_VECTOR
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore
    #endif



#elif defined SDK_START_SEC_INIT_VAR_EXCEPTION_REG_INFO
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_INIT_VAR_EXCEPTION_REG_INFO
    #define INSIDE_SDK_START_SEC_INIT_VAR_EXCEPTION_REG_INFO

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_INIT_VAR_EXCEPTION_REG_INFO
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section data=".exceptionRegInfo"
    #elif defined __ghs__
        #pragma ghs section data=".exceptionRegInfo"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".exceptionRegInfo"
    #elif defined __HIGHTEC__
        #pragma clang section data=".exceptionRegInfo"
    #elif defined __TASKING__
        #pragma section .data=exceptionRegInfo
    #endif

#elif defined SDK_STOP_SEC_INIT_VAR_EXCEPTION_REG_INFO

    #ifdef INSIDE_SDK_START_SEC_INIT_VAR_EXCEPTION_REG_INFO
        #undef INSIDE_SDK_START_SEC_INIT_VAR_EXCEPTION_REG_INFO
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_INIT_VAR_EXCEPTION_REG_INFO
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore
    #endif


/* exception_text */
#elif defined SDK_START_SEC_EXCEPTION_HANDLER
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef INSIDE_SDK_START_SEC_EXCEPTION_HANDLER
    #define INSIDE_SDK_START_SEC_EXCEPTION_HANDLER

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_EXCEPTION_HANDLER
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section text=".exceptionHandler"
    #elif defined __ghs__
        #pragma ghs section text=".exceptionHandler"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".exceptionHandler"
    #elif defined __HIGHTEC__
        #pragma clang section text=".exceptionHandler"
    #elif defined __TASKING__
        #pragma section .text=exceptionHandler
    #endif

#elif defined SDK_STOP_SEC_EXCEPTION_HANDLER

    #ifdef INSIDE_SDK_START_SEC_EXCEPTION_HANDLER
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_EXCEPTION_HANDLER
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef SDK_STOP_SEC_EXCEPTION_HANDLER
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section text = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore
    #endif



#elif defined SDK_START_SEC_VAR_CLEAR_GLOBAL_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_CLEAR_GLOBAL_NO_CACHEABLE
    #define INSIDE_SDK_START_SEC_VAR_CLEAR_GLOBAL_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_CLEAR_GLOBAL_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section bss=".uncached_bss"
    #elif defined __ghs__
        #pragma ghs section bss=".uncached_bss"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".uncached_bss"
    #elif defined __HIGHTEC__
        #pragma clang section bss=".uncached_bss"
    #elif defined __TASKING__
        #pragma section .bss=uncached_bss
    #endif

#elif defined SDK_STOP_SEC_VAR_CLEAR_GLOBAL_NO_CACHEABLE

    #ifdef INSIDE_SDK_START_SEC_VAR_CLEAR_GLOBAL_NO_CACHEABLE
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_CLEAR_GLOBAL_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_CLEAR_GLOBAL_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section bss = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore            
    #endif

#elif defined SDK_START_SEC_CODE_GLOBAL
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_CODE_GLOBAL
    #define INSIDE_SDK_START_SEC_CODE_GLOBAL

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_CODE_GLOBAL
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section text = ".user_code"
    #elif defined __ghs__
        #pragma ghs section text=".user_code"
    #elif defined __ICCARM__
        #pragma default_function_attributes = @ ".user_code"
    #elif defined __HIGHTEC__
        #pragma clang section text = ".user_code"
    #elif defined __TASKING__
        #pragma section .text=user_code
    #endif

#elif defined SDK_STOP_SEC_CODE_GLOBAL

    #ifdef INSIDE_SDK_START_SEC_CODE_GLOBAL
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_CODE_GLOBAL
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_CODE_GLOBAL
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section text = default
    #elif defined __ICCARM__
        #pragma default_function_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif

#elif defined SDK_START_SEC_VAR_INIT_DFLASH
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_DFLASH
    #define INSIDE_SDK_START_SEC_VAR_INIT_DFLASH

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_DFLASH
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section rodata = ".dflash_data"
    #elif defined __ghs__
        #pragma ghs section rodata=".dflash_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".dflash_data"
    #elif defined __HIGHTEC__
        #pragma clang section rodata = ".dflash_data"
    #elif defined __TASKING__
        #pragma section .rodata=dflash_data
    #endif        

#elif defined SDK_STOP_SEC_VAR_INIT_DFLASH

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_DFLASH
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_DFLASH
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_DFLASH
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text="" rodata=""
    #elif defined __ghs__
        #pragma ghs section bss="" data="" text="" rodata=""
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text="" rodata=""
    #elif defined __TASKING__
        #pragma section restore    
    #endif

#elif defined SDK_START_SEC_VAR_CLEARED_GLOBAL
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_CLEARED_GLOBAL
    #define INSIDE_SDK_START_SEC_VAR_CLEARED_GLOBAL

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_CLEARED_GLOBAL
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section bss=".global_bss"
    #elif defined __ghs__
        #pragma ghs section bss=".global_bss"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".global_bss"
    #elif defined __HIGHTEC__
        #pragma clang section bss=".global_bss"
    #elif defined __TASKING__
        #pragma section .bss=global_bss
    #endif

#elif defined SDK_STOP_SEC_VAR_CLEARED_GLOBAL

    #ifdef INSIDE_SDK_START_SEC_VAR_CLEARED_GLOBAL
        #undef INSIDE_SDK_START_SEC_VAR_CLEARED_GLOBAL
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_CLEARED_GLOBAL
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section bss = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif

#elif defined SDK_START_SEC_VAR_CLEARED_GLOBAL_NO_CLEAR
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_CLEARED_GLOBAL_NO_CLEAR
    #define INSIDE_SDK_START_SEC_VAR_CLEARED_GLOBAL_NO_CLEAR

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_CLEARED_GLOBAL_NO_CLEAR
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section bss=".unclear_bss"
    #elif defined __ghs__
        #pragma ghs section bss=".unclear_bss"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".unclear_bss"
    #elif defined __HIGHTEC__
        #pragma clang section bss=".unclear_bss"
    #elif defined __TASKING__
        #pragma section .bss=unclear_bss
    #endif

#elif defined SDK_STOP_SEC_VAR_CLEARED_GLOBAL_NO_CLEAR

    #ifdef INSIDE_SDK_START_SEC_VAR_CLEARED_GLOBAL_NO_CLEAR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_CLEARED_GLOBAL_NO_CLEAR
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_CLEARED_GLOBAL_NO_CLEAR
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section bss = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif

#elif defined SDK_START_SEC_VAR_INIT_GLOBAL
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_GLOBAL
    #define INSIDE_SDK_START_SEC_VAR_INIT_GLOBAL

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_GLOBAL
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section data=".global_data"
    #elif defined __ghs__
        #pragma ghs section data=".global_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".global_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".global_data"
    #elif defined __TASKING__
        #pragma section .data=global_data
    #endif

#elif defined SDK_STOP_SEC_VAR_INIT_GLOBAL

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_GLOBAL
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_GLOBAL
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_GLOBAL
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif


#elif defined SDK_START_SEC_VAR_CLEARED_PRIVATE_CLONE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_CLEARED_PRIVATE_CLONE
    #define INSIDE_SDK_START_SEC_VAR_CLEARED_PRIVATE_CLONE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_CLEARED_PRIVATE_CLONE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section bss=".private_clone_bss"
    #elif defined __ghs__
        #pragma ghs section bss=".private_clone_bss"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_clone_bss"
    #elif defined __HIGHTEC__
        #pragma clang section bss=".private_clone_bss"
    #elif defined __TASKING__
        #pragma section .bss=private_clone_bss
    #endif

#elif defined SDK_STOP_SEC_VAR_CLEARED_PRIVATE_CLONE

    #ifdef INSIDE_SDK_START_SEC_VAR_CLEARED_PRIVATE_CLONE
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_CLEARED_PRIVATE_CLONE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_CLEARED_PRIVATE_CLONE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section bss = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore    
    #endif


#elif defined SDK_START_SEC_VAR_INIT_PRIVATE_CLONE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_PRIVATE_CLONE
    #define INSIDE_SDK_START_SEC_VAR_INIT_PRIVATE_CLONE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_PRIVATE_CLONE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section data=".private_clone_data"
    #elif defined __ghs__
        #pragma ghs section data=".private_clone_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_clone_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".private_clone_data"
    #elif defined __TASKING__
        #pragma section .data=private_clone_data
    #endif

#elif defined SDK_STOP_SEC_VAR_INIT_PRIVATE_CLONE

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_PRIVATE_CLONE
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_PRIVATE_CLONE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_PRIVATE_CLONE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif


#elif defined SDK_START_SEC_CODE_PRIVATE_CLONE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_CODE_PRIVATE_CLONE
    #define INSIDE_SDK_START_SEC_CODE_PRIVATE_CLONE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_CODE_PRIVATE_CLONE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section text=".private_clone_code"
    #elif defined __ghs__
        #pragma ghs section text=".private_clone_code"
    #elif defined __ICCARM__
        #pragma default_function_attributes = @ ".private_clone_code"
    #elif defined __HIGHTEC__
        #pragma clang section text=".private_clone_code"
    #elif defined __TASKING__
        #pragma section .text=private_clone_code
    #endif

#elif defined SDK_STOP_SEC_CODE_PRIVATE_CLONE

    #ifdef INSIDE_SDK_START_SEC_CODE_PRIVATE_CLONE
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_CODE_PRIVATE_CLONE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_CODE_PRIVATE_CLONE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section text = default
    #elif defined __ICCARM__
        #pragma default_function_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif
/***************************************************************************************************/
/*******************************************CORE0***************************************************/
/***************************************************************************************************/
#elif defined SDK_START_SEC_VAR_CLEARED_CORE0

    #undef SDK_START_SEC_VAR_CLEARED_CORE0
    #define INSIDE_SDK_START_SEC_VAR_CLEARED_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_CLEARED_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section bss=".private_Core0_bss"
    #elif defined __ghs__
        #pragma ghs section bss=".private_Core0_bss"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_Core0_bss"
    #elif defined __HIGHTEC__
        #pragma clang section bss=".private_Core0_bss"
    #elif defined __TASKING__
        #pragma section .bss=private_Core0_bss
    #endif

#elif defined SDK_STOP_SEC_VAR_CLEARED_CORE0

    #ifdef INSIDE_SDK_START_SEC_VAR_CLEARED_CORE0
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_CLEARED_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_CLEARED_CORE0
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section bss = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore    
    #endif


#elif defined SDK_START_SEC_VAR_INIT_CORE0
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_CORE0
    #define INSIDE_SDK_START_SEC_VAR_INIT_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section data=".private_Core0_data"
    #elif defined __ghs__
        #pragma ghs section data=".private_Core0_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_Core0_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".private_Core0_data"
    #elif defined __TASKING__
        #pragma section .data=private_Core0_data
    #endif

#elif defined SDK_STOP_SEC_VAR_INIT_CORE0

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_CORE0
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_CORE0
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif


#elif defined SDK_START_SEC_CODE_CORE0
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_CODE_CORE0
    #define INSIDE_SDK_START_SEC_CODE_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_CODE_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        #pragma clang section text=".private_Core0_code"
    #elif defined __ghs__
        #pragma ghs section text=".private_Core0_code"
    #elif defined __ICCARM__
        #pragma default_function_attributes = @ ".private_Core0_code"
    #elif defined __HIGHTEC__
        #pragma clang section text=".private_Core0_code"
    #elif defined __TASKING__
        #pragma section .text=private_Core0_code
    #endif

#elif defined SDK_STOP_SEC_CODE_CORE0

    #ifdef INSIDE_SDK_START_SEC_CODE_CORE0
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_CODE_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_CODE_CORE0
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section text = default
    #elif defined __ICCARM__
        #pragma default_function_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif


/***************************************************************************************************/
/*******************************************CORE1***************************************************/
/***************************************************************************************************/
#elif defined SDK_START_SEC_VAR_CLEARED_CORE1
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_CLEARED_CORE1
    #define INSIDE_SDK_START_SEC_VAR_CLEARED_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_CLEARED_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss=".private_Core1_bss"
    #elif defined __ghs__
        #pragma ghs section bss=".private_Core1_bss"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_Core1_bss"
    #elif defined __HIGHTEC__
        #pragma clang section bss=".private_Core1_bss"
    #elif defined __TASKING__
        #pragma section .bss=private_Core1_bss
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */
#elif defined SDK_STOP_SEC_VAR_CLEARED_CORE1

    #ifdef INSIDE_SDK_START_SEC_VAR_CLEARED_CORE1
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_CLEARED_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_CLEARED_CORE1
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section bss = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */
#elif defined SDK_START_SEC_VAR_INIT_CORE1
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_CORE1
    #define INSIDE_SDK_START_SEC_VAR_INIT_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section data=".private_Core1_data"
    #elif defined __ghs__
        #pragma ghs section data=".private_Core1_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_Core1_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".private_Core1_data"
    #elif defined __TASKING__
        #pragma section .data=private_Core1_data
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */
#elif defined SDK_STOP_SEC_VAR_INIT_CORE1

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_CORE1
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_CORE1
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */

#elif defined SDK_START_SEC_CODE_CORE1
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_CODE_CORE1
    #define INSIDE_SDK_START_SEC_CODE_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_CODE_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section text=".private_Core1_code"
    #elif defined __ghs__
        #pragma ghs section text=".private_Core1_code"
    #elif defined __ICCARM__
        #pragma default_function_attributes = @ ".private_Core1_code"
    #elif defined __HIGHTEC__
        #pragma clang section text=".private_Core1_code"
    #elif defined __TASKING__
        #pragma section .text=private_Core1_code
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */
#elif defined SDK_STOP_SEC_CODE_CORE1

    #ifdef INSIDE_SDK_START_SEC_CODE_CORE1
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_CODE_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_CODE_CORE1
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section text = default
    #elif defined __ICCARM__
        #pragma default_function_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */



/***************************************************************************************************/
/*******************************************CORE2***************************************************/
/***************************************************************************************************/
#elif defined SDK_START_SEC_VAR_CLEARED_CORE2
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_CLEARED_CORE2
    #define INSIDE_SDK_START_SEC_VAR_CLEARED_CORE2

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_CLEARED_CORE2
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss=".private_Core2_bss"
    #elif defined __ghs__
        #pragma ghs section bss=".private_Core2_bss"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_Core2_bss"
    #elif defined __HIGHTEC__
        #pragma clang section bss=".private_Core2_bss"
    #elif defined __TASKING__
        #pragma section .bss=private_Core2_bss
    #endif
#endif /*THA6_THA6412*/
#elif defined SDK_STOP_SEC_VAR_CLEARED_CORE2

    #ifdef INSIDE_SDK_START_SEC_VAR_CLEARED_CORE2
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_CLEARED_CORE2
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_CLEARED_CORE2
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section bss = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif
#endif /*THA6_THA6412*/

#elif defined SDK_START_SEC_VAR_INIT_CORE2
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_CORE2
    #define INSIDE_SDK_START_SEC_VAR_INIT_CORE2

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_CORE2
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section data=".private_Core2_data"
    #elif defined __ghs__
        #pragma ghs section data=".private_Core2_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_Core2_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".private_Core2_data"
    #elif defined __TASKING__
        #pragma section .data=private_Core2_data
    #endif
#endif /*THA6_THA6412*/

#elif defined SDK_STOP_SEC_VAR_INIT_CORE2

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_CORE2
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_CORE2
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_CORE2
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore            
    #endif
#endif /*THA6_THA6412*/

#elif defined SDK_START_SEC_CODE_CORE2
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_CODE_CORE2
    #define INSIDE_SDK_START_SEC_CODE_CORE2

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_CODE_CORE2
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section text=".private_Core2_code"
    #elif defined __ghs__
        #pragma ghs section text=".private_Core2_code"
    #elif defined __ICCARM__
        #pragma default_function_attributes = @ ".private_Core2_code"
    #elif defined __HIGHTEC__
        #pragma clang section text=".private_Core2_code"
    #elif defined __TASKING__
        #pragma section .text=private_Core2_code
    #endif
#endif /*THA6_THA6412*/

#elif defined SDK_STOP_SEC_CODE_CORE2

    #ifdef INSIDE_SDK_START_SEC_CODE_CORE2
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_CODE_CORE2
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_CODE_CORE2
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section text = default
    #elif defined __ICCARM__
        #pragma default_function_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore    
    #endif
#endif /*THA6_THA6412*/

/***************************************************************************************************/
/*******************************************CORE3***************************************************/
/***************************************************************************************************/
#elif defined SDK_START_SEC_VAR_CLEARED_CORE3
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_CLEARED_CORE3
    #define INSIDE_SDK_START_SEC_VAR_CLEARED_CORE3

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_CLEARED_CORE3
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss=".private_Core3_bss"
    #elif defined __ghs__
        #pragma ghs section bss=".private_Core3_bss"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_Core3_bss"
    #elif defined __HIGHTEC__
        #pragma clang section bss=".private_Core3_bss"
    #elif defined __TASKING__
        #pragma section .bss=private_Core3_bss
    #endif
#endif /*THA6_THA6412*/

#elif defined SDK_STOP_SEC_VAR_CLEARED_CORE3

    #ifdef INSIDE_SDK_START_SEC_VAR_CLEARED_CORE3
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_CLEARED_CORE3
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_CLEARED_CORE3
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section bss = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif
#endif /*THA6_THA6412*/

#elif defined SDK_START_SEC_VAR_INIT_CORE3
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_CORE3
    #define INSIDE_SDK_START_SEC_VAR_INIT_CORE3

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_CORE3
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section data=".private_Core3_data"
    #elif defined __ghs__
        #pragma ghs section data=".private_Core3_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".private_Core3_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".private_Core3_data"
    #elif defined __TASKING__
        #pragma section .data=private_Core3_data
    #endif
#endif /*THA6_THA6412*/

#elif defined SDK_STOP_SEC_VAR_INIT_CORE3

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_CORE3
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_CORE3
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_CORE3
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore            
    #endif
#endif /*THA6_THA6412*/


#elif defined SDK_START_SEC_CODE_CORE3
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_CODE_CORE3
    #define INSIDE_SDK_START_SEC_CODE_CORE3

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_CODE_CORE3
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section text=".private_Core3_code"
    #elif defined __ghs__
        #pragma ghs section text=".private_Core3_code"
    #elif defined __ICCARM__
        #pragma default_function_attributes = @ ".private_Core3_code"
    #elif defined __HIGHTEC__
        #pragma clang section text=".private_Core3_code"
    #elif defined __TASKING__
        #pragma section .text=private_Core3_code
    #endif
#endif /*THA6_THA6412*/

#elif defined SDK_STOP_SEC_CODE_CORE3

    #ifdef INSIDE_SDK_START_SEC_CODE_CORE3
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_CODE_CORE3
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_CODE_CORE3
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section text = default
    #elif defined __ICCARM__
        #pragma default_function_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif
#endif /* THA6_THA6412 */


#elif defined SDK_START_SEC_VAR_INIT_LMU1_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_LMU1_NO_CACHEABLE
    #define INSIDE_SDK_START_SEC_VAR_INIT_LMU1_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_LMU1_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section data=".lmu1_uncached_data"
    #elif defined __ghs__
        #pragma ghs section data=".lmu1_uncached_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".lmu1_uncached_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".lmu1_uncached_data"
    #elif defined __TASKING__
        #pragma section .data=lmu1_uncached_data
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */

#elif defined SDK_STOP_SEC_VAR_INIT_LMU1_NO_CACHEABLE

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_LMU1_NO_CACHEABLE
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_LMU1_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_LMU1_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */

#elif defined SDK_START_SEC_VAR_INIT_LMU2_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_LMU2_NO_CACHEABLE
    #define INSIDE_SDK_START_SEC_VAR_INIT_LMU2_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_LMU2_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412) ||defined(THA6_THA6104)
    #ifdef __ARMCC_VERSION
        #pragma clang section data=".lmu2_uncached_data"
    #elif defined __ghs__
        #pragma ghs section data=".lmu2_uncached_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".lmu2_uncached_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".lmu2_uncached_data"
    #elif defined __TASKING__
        #pragma section .data=lmu2_uncached_data
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 || THA6_THA6104 */

#elif defined SDK_STOP_SEC_VAR_INIT_LMU2_NO_CACHEABLE

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_LMU2_NO_CACHEABLE
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_LMU2_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_LMU2_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif

#elif defined SDK_START_SEC_VAR_INIT_LMU3_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_SEC_VAR_INIT_LMU3_NO_CACHEABLE
    #define INSIDE_SDK_START_SEC_VAR_INIT_LMU3_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_SEC_VAR_INIT_LMU3_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section data=".lmu3_uncached_data"
    #elif defined __ghs__
        #pragma ghs section data=".lmu3_uncached_data"
    #elif defined __ICCARM__
        #pragma default_variable_attributes = @ ".lmu3_uncached_data"
    #elif defined __HIGHTEC__
        #pragma clang section data=".lmu3_uncached_data"
    #elif defined __TASKING__
        #pragma section .data=lmu3_uncached_data
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */

#elif defined SDK_STOP_SEC_VAR_INIT_LMU3_NO_CACHEABLE

    #ifdef INSIDE_SDK_START_SEC_VAR_INIT_LMU3_NO_CACHEABLE
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_SEC_VAR_INIT_LMU3_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_SEC_VAR_INIT_LMU3_NO_CACHEABLE
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    #ifdef __ARMCC_VERSION
        #pragma clang section bss="" data="" text=""
    #elif defined __ghs__
        #pragma ghs section data = default
    #elif defined __ICCARM__
        #pragma default_variable_attributes =
    #elif defined __HIGHTEC__
        #pragma clang section bss="" data="" text=""
    #elif defined __TASKING__
        #pragma section restore        
    #endif
#endif /* THA6_THA6206 || THA6_THA6412 */

/***************************************************************************************************/
#elif defined SDK_START_OPTIMIZE_OFF
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_START_OPTIMIZE_OFF
    #define INSIDE_SDK_START_OPTIMIZE_OFF

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef SDK_STOP_OPTIMIZE_OFF
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR

    #ifdef __ARMCC_VERSION
        /* #Violation: sdk_memmap_h_REF_1 */
        #pragma clang optimize off
    #elif defined __ghs__
        #pragma ghs Onone
    #elif defined __ICCARM__
        #pragma optimize=none
    #elif defined __HIGHTEC__
        #pragma clang optimize off
    #elif defined __TASKING__    
        #pragma optimize=0
    #endif

#elif defined SDK_STOP_OPTIMIZE_OFF

    #ifdef INSIDE_SDK_START_OPTIMIZE_OFF
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef INSIDE_SDK_START_OPTIMIZE_OFF
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        /* #Violation: sdk_memmap_h_REF_2 */
        #undef MEMMAP_MATCH_ERROR
    #endif
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef SDK_STOP_OPTIMIZE_OFF
    /* #Violation: sdk_memmap_h_REF_2 */
    #undef MEMMAP_ERROR
    #ifdef __ARMCC_VERSION
        #pragma clang optimize on
    #elif defined __ghs__
        #pragma ghs Odefault
    #elif defined __ICCARM__
        #pragma optimize=default
    #elif defined __HIGHTEC__
        #pragma clang optimize on
    #elif defined __TASKING__
        #pragma optimize=1
    #endif

#endif
/**************************************************************************************************/
/****************************************** Report error ******************************************/
/**************************************************************************************************/
#ifdef MEMMAP_ERROR
    #error "MemMap.h, no valid memory mapping symbol defined."
#endif
/**********************************************************************************************************************
 *                                                     End of File
 *********************************************************************************************************************/
/* #Violation: sdk_memmap_h_REF_3 */

/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : port_sdk_memmap.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
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
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/**
* @brief Symbol used for checking correctness of the includes
*/
#define MEMMAP_ERROR

 
/**************************************** Config Data Sections *******************************/
#if defined OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_BOOLEAN

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR

    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_bool")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_BOOLEAN

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_8

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_8
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_8
            #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_8")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_8

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_8
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_16

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_16
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_16")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_16

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_16
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_32

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_32
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_32")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_32

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_32
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_unspecified")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Const Data Sections *******************************/
#elif defined OVC_START_SEC_CONST_ASIL_D_GLOBAL_BOOLEAN

    #undef OVC_START_SEC_CONST_ASIL_D_GLOBAL_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_bool")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_GLOBAL_8

    #undef OVC_START_SEC_CONST_ASIL_D_GLOBAL_8
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_8")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_8
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_8
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_GLOBAL_16

    #undef OVC_START_SEC_CONST_ASIL_D_GLOBAL_16
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_16")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_16
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_16
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_GLOBAL_32

    #undef OVC_START_SEC_CONST_ASIL_D_GLOBAL_32
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_32")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_32
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_32
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED

    #undef OVC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_unspecified")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Variable Sections *******************************/
#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_bool")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_8")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_16")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_32")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_unspecified")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_8
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_16
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

/**********************************  Non Cacheable Variable Sections ***************************/
#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_bool_uncached")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_8_uncached")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_16_uncached")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_32_uncached")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_unspecified_uncached")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()



#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE

    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_lmu1_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()





#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_lmu1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_lmu1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_8
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_lmu1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_16
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_lmu1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_32
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_lmu1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED

    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_lmu1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_lmu1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_8
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_lmu1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_16
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_lmu1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_32
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_lmu1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()



#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE

    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_lmu2_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()



#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_lmu2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_lmu2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_8
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_lmu2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_16
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_lmu2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_32
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_lmu2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED

    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU2_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_lmu2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_lmu2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_8
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_lmu2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_16
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_lmu2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_32
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_lmu2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU2_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()



#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE

    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_lmu3_uncached")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()


#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_lmu3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_lmu3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_8
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_lmu3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_16
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_lmu3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_32
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_lmu3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED

    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_LMU3_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_lmu3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_lmu3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_8
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_lmu3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_16
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_lmu3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_32
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_lmu3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_LMU3_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()


/********************************** Code Sections ***************************/
#elif defined OVC_START_SEC_CODE_ASIL_D_GLOBAL

    #undef OVC_START_SEC_CODE_ASIL_D_GLOBAL
    #define INSIDE_OVC_START_SEC_CODE_ASIL_D_GLOBAL

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_ASIL_D_GLOBAL
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_asil_d")

#elif defined OVC_STOP_SEC_CODE_ASIL_D_GLOBAL

    #ifdef INSIDE_OVC_START_SEC_CODE_ASIL_D_GLOBAL
        #undef INSIDE_OVC_START_SEC_CODE_ASIL_D_GLOBAL
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_ASIL_D_GLOBAL

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

#elif defined OVC_START_SEC_RAMCODE_ASIL_D_GLOBAL

    #undef OVC_START_SEC_RAMCODE_ASIL_D_GLOBAL
    #define INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_GLOBAL

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_RAMCODE_ASIL_D_GLOBAL
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_ramcode_asil_d")

#elif defined OVC_STOP_SEC_RAMCODE_ASIL_D_GLOBAL

    #ifdef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_GLOBAL
        #undef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_GLOBAL
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_RAMCODE_ASIL_D_GLOBAL

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Callout Code Sections ***************************/
#elif defined OVC_START_SEC_CALLOUT_CODE_ASIL_D_GLOBAL

    #undef OVC_START_SEC_CALLOUT_CODE_ASIL_D_GLOBAL
    #define INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_GLOBAL

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_GLOBAL
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_callout_asil_d")

#elif defined OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_GLOBAL

    #ifdef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_GLOBAL
        #undef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_GLOBAL
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_GLOBAL

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Fast Code Sections ***************************/
#elif defined OVC_START_SEC_CODE_FAST_ASIL_D_GLOBAL

    #undef OVC_START_SEC_CODE_FAST_ASIL_D_GLOBAL
    #define INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_GLOBAL

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_FAST_ASIL_D_GLOBAL
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_fast_asil_d")

#elif defined OVC_STOP_SEC_CODE_FAST_ASIL_D_GLOBAL

    #ifdef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_GLOBAL
        #undef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_GLOBAL
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_FAST_ASIL_D_GLOBAL

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Clone Code Sections ***************************/
#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_PRIVATE_CLONE

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_PRIVATE_CLONE
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_PRIVATE_CLONE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_PRIVATE_CLONE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".private_clone_bss")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_PRIVATE_CLONE

    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_PRIVATE_CLONE
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_PRIVATE_CLONE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_PRIVATE_CLONE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()


#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_PRIVATE_CLONE

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_PRIVATE_CLONE
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_PRIVATE_CLONE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_PRIVATE_CLONE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".private_clone_data")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_PRIVATE_CLONE

    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_PRIVATE_CLONE
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_PRIVATE_CLONE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_PRIVATE_CLONE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()


#elif defined OVC_START_SEC_CODE_ASIL_D_PRIVATE_CLONE

    #undef OVC_START_SEC_CODE_ASIL_D_PRIVATE_CLONE
    #define INSIDE_OVC_START_SEC_CODE_ASIL_D_PRIVATE_CLONE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_ASIL_D_PRIVATE_CLONE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".private_clone_code")

#elif defined OVC_STOP_SEC_CODE_ASIL_D_PRIVATE_CLONE

    #ifdef INSIDE_OVC_START_SEC_CODE_ASIL_D_PRIVATE_CLONE
        #undef INSIDE_OVC_START_SEC_CODE_ASIL_D_PRIVATE_CLONE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_ASIL_D_PRIVATE_CLONE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/***************************************************************************************************/
/*******************************************CORE0***************************************************/
/***************************************************************************************************/
/****************************************  Config Data Sections *******************************/
#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_BOOLEAN

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_bool_core0")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_BOOLEAN

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_8

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_8
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_8_core0")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_8

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_8
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_16

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_16
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_16_core0")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_16

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_16
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_32

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_32
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_32_core0")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_32

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_32
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_unspecified_core0")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Const Data Sections *******************************/
#elif defined OVC_START_SEC_CONST_ASIL_D_CORE0_BOOLEAN

    #undef OVC_START_SEC_CONST_ASIL_D_CORE0_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE0_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_bool_core0")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE0_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE0_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE0_8

    #undef OVC_START_SEC_CONST_ASIL_D_CORE0_8
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE0_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_8_core0")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE0_8
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_8
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE0_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE0_16

    #undef OVC_START_SEC_CONST_ASIL_D_CORE0_16
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE0_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_16_core0")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE0_16
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_16
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE0_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE0_32

    #undef OVC_START_SEC_CONST_ASIL_D_CORE0_32
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_32_core0")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE0_32
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_32
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED

    #undef OVC_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_unspecified_core0")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Variable Sections *******************************/
#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_bool_core0")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_8_core0")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_8
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_16_core0")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_16
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_32_core0")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_32
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_UNSPECIFIED

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_unspecified_core0")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_BOOLEAN

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_core0")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_8

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_8
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_core0")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_8
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_8
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_16

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_16
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_core0")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_16
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_16
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_32

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_32
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_core0")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_32
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_32
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_core0")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_BOOLEAN

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_core0")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_8

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_8
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_core0")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_8
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_8
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_16

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_16
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_core0")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_16
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_16
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_32

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_32
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_core0")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_32
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_32
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_core0")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

/**********************************  Non Cacheable Variable Sections ***************************/
#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_bool_uncached_core0")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_8_uncached_core0")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_16_uncached_core0")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_32_uncached_core0")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE0_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE0_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

/****************************************  Code Sections *******************************/
#elif defined OVC_START_SEC_CODE_ASIL_D_CORE0

    #undef OVC_START_SEC_CODE_ASIL_D_CORE0
    #define INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_ASIL_D_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_asil_d_core0")

#elif defined OVC_STOP_SEC_CODE_ASIL_D_CORE0

    #ifdef INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE0
        #undef INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_ASIL_D_CORE0

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

#elif defined OVC_START_SEC_RAMCODE_ASIL_D_CORE0

    #undef OVC_START_SEC_RAMCODE_ASIL_D_CORE0
    #define INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_RAMCODE_ASIL_D_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_ramcode_asil_d_core0")

#elif defined OVC_STOP_SEC_RAMCODE_ASIL_D_CORE0

    #ifdef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE0
        #undef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_RAMCODE_ASIL_D_CORE0

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Callout Code Sections ***************************/
#elif defined OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE0

    #undef OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE0
    #define INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_callout_asil_d_core0")

#elif defined OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE0

    #ifdef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE0
        #undef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE0

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Fast Code Sections ***************************/
#elif defined OVC_START_SEC_CODE_FAST_ASIL_D_CORE0

    #undef OVC_START_SEC_CODE_FAST_ASIL_D_CORE0
    #define INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_fast_asil_d_core0")

#elif defined OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE0

    #ifdef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE0
        #undef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE0

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/***************************************************************************************************/
/*******************************************CORE1***************************************************/
/***************************************************************************************************/
/****************************************  Config Data Sections *******************************/
#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_BOOLEAN

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_bool_core1")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_BOOLEAN

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_8

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_8
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_8_core1")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_8

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_8
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_16

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_16
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_16_core1")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_16

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_16
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_32

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_32
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_32_core1")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_32

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_32
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_unspecified_core1")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Const Data Sections *******************************/
#elif defined OVC_START_SEC_CONST_ASIL_D_CORE1_BOOLEAN

    #undef OVC_START_SEC_CONST_ASIL_D_CORE1_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_bool_core1")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE1_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE1_8

    #undef OVC_START_SEC_CONST_ASIL_D_CORE1_8
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_8_core1")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE1_8
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_8
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE1_16

    #undef OVC_START_SEC_CONST_ASIL_D_CORE1_16
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_16_core1")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE1_16
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_16
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE1_32

    #undef OVC_START_SEC_CONST_ASIL_D_CORE1_32
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_32_core1")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE1_32
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_32
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED

    #undef OVC_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_unspecified_core1")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Variable Sections *******************************/
#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_BOOLEAN

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_bool_core1")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_8

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_8
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_8_core1")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_8
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_8
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_16

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_16
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_16_core1")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_16
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_16
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_32

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_32
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_32_core1")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_32
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_32
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_UNSPECIFIED

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_unspecified_core1")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_BOOLEAN

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_core1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_8

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_8
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_core1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_8
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_8
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_16

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_16
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_core1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_16
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_16
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_32

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_32
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_core1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_32
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_32
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_core1")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_BOOLEAN

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_core1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_8

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_8
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_core1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_8
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_8
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_16

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_16
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_core1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_16
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_16
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_32

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_32
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_core1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_32
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_32
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_core1")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

/****************************************  Code Sections *******************************/
#elif defined OVC_START_SEC_CODE_ASIL_D_CORE1

    #undef OVC_START_SEC_CODE_ASIL_D_CORE1
    #define INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_ASIL_D_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_asil_d_core1")

#elif defined OVC_STOP_SEC_CODE_ASIL_D_CORE1

    #ifdef INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE1
        #undef INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_ASIL_D_CORE1

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/****************************************  RAMCode Sections *******************************/
#elif defined OVC_START_SEC_RAMCODE_ASIL_D_CORE1

    #undef OVC_START_SEC_RAMCODE_ASIL_D_CORE1
    #define INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_RAMCODE_ASIL_D_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_ramcode_asil_d_core1")

#elif defined OVC_STOP_SEC_RAMCODE_ASIL_D_CORE1

    #ifdef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE1
        #undef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_RAMCODE_ASIL_D_CORE1

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Callout Code Sections ***************************/
#elif defined OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE1

    #undef OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE1
    #define INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_callout_asil_d_core1")

#elif defined OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE1

    #ifdef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE1
        #undef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE1

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Fast Code Sections ***************************/
#elif defined OVC_START_SEC_CODE_FAST_ASIL_D_CORE1

    #undef OVC_START_SEC_CODE_FAST_ASIL_D_CORE1
    #define INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_fast_asil_d_core1")

#elif defined OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE1

    #ifdef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE1
        #undef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE1

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/***************************************************************************************************/
/*******************************************CORE2***************************************************/
/***************************************************************************************************/
/****************************************  Config Data Sections *******************************/
#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_BOOLEAN

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_bool_core2")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_BOOLEAN

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_8

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_8
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_8_core2")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_8

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_8
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_16

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_16
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_16_core2")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_16

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_16
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_32

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_32
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_32_core2")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_32

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_32
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_unspecified_core2")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE2_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Const Data Sections *******************************/
#elif defined OVC_START_SEC_CONST_ASIL_D_CORE2_BOOLEAN

    #undef OVC_START_SEC_CONST_ASIL_D_CORE2_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE2_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_bool_core2")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE2_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE2_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE2_8

    #undef OVC_START_SEC_CONST_ASIL_D_CORE2_8
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE2_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_8_core2")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE2_8
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_8
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE2_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE2_16

    #undef OVC_START_SEC_CONST_ASIL_D_CORE2_16
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE2_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_16_core2")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE2_16
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_16
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE2_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE2_32

    #undef OVC_START_SEC_CONST_ASIL_D_CORE2_32
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE2_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_32_core2")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE2_32
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_32
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE2_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED

    #undef OVC_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_unspecified_core2")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Variable Sections *******************************/
#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_bool_core2")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_8_core2")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_8
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_16_core2")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_16
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_32_core2")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_32
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_UNSPECIFIED

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_unspecified_core2")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_BOOLEAN

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_core2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_8

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_8
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_core2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_8
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_8
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_16

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_16
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_core2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_16
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_16
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_32

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_32
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_core2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_32
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_32
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_core2")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE2_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_BOOLEAN

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_core2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_8

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_8
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_core2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_8
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_8
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_16

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_16
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_core2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_16
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_16
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_32

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_32
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_core2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_32
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_32
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_core2")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

/**********************************  Non Cacheable Variable Sections ***************************/
#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_bool_uncached_core2")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_8_uncached_core2")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_8_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_16_uncached_core2")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_16_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32_NO_CACHEABLE

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32_NO_CACHEABLE
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_32_uncached_core2")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_32_NO_CACHEABLE
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32_NO_CACHEABLE
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE2_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE2_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

/****************************************  Code Sections *******************************/
#elif defined OVC_START_SEC_CODE_ASIL_D_CORE2

    #undef OVC_START_SEC_CODE_ASIL_D_CORE2
    #define INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE2

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_ASIL_D_CORE2
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_asil_d_core2")

#elif defined OVC_STOP_SEC_CODE_ASIL_D_CORE2

    #ifdef INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE2
        #undef INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE2
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_ASIL_D_CORE2

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

#elif defined OVC_START_SEC_RAMCODE_ASIL_D_CORE2

    #undef OVC_START_SEC_RAMCODE_ASIL_D_CORE2
    #define INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE2

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_RAMCODE_ASIL_D_CORE2
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_ramcode_asil_d_core2")

#elif defined OVC_STOP_SEC_RAMCODE_ASIL_D_CORE2

    #ifdef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE2
        #undef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE2
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_RAMCODE_ASIL_D_CORE2

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Callout Code Sections ***************************/
#elif defined OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE2

    #undef OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE2
    #define INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE2

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE2
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_callout_asil_d_core2")

#elif defined OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE2

    #ifdef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE2
        #undef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE2
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE2

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Fast Code Sections ***************************/
#elif defined OVC_START_SEC_CODE_FAST_ASIL_D_CORE2

    #undef OVC_START_SEC_CODE_FAST_ASIL_D_CORE2
    #define INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE2

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE2
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_fast_asil_d_core2")

#elif defined OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE2

    #ifdef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE2
        #undef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE2
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE2

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/***************************************************************************************************/
/*******************************************CORE3***************************************************/
/***************************************************************************************************/
/****************************************  Config Data Sections *******************************/
#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_BOOLEAN

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_bool_core3")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_BOOLEAN

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_8

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_8
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_8_core3")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_8

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_8
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_16

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_16
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_16_core3")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_16

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_16
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_32

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_32
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_32_core3")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_32

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_32
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED

    #undef OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_cfg_asil_d_unspecified_core3")

#elif defined OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED

    #ifdef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONFIG_DATA_ASIL_D_CORE3_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Const Data Sections *******************************/
#elif defined OVC_START_SEC_CONST_ASIL_D_CORE3_BOOLEAN

    #undef OVC_START_SEC_CONST_ASIL_D_CORE3_BOOLEAN
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE3_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_bool_core3")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE3_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_BOOLEAN
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE3_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE3_8

    #undef OVC_START_SEC_CONST_ASIL_D_CORE3_8
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE3_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_8_core3")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE3_8
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_8
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE3_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE3_16

    #undef OVC_START_SEC_CONST_ASIL_D_CORE3_16
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE3_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_16_core3")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE3_16
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_16
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE3_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE3_32

    #undef OVC_START_SEC_CONST_ASIL_D_CORE3_32
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE3_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_32_core3")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE3_32
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_32
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE3_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

#elif defined OVC_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED

    #undef OVC_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_RODATA(".sdk_const_asil_d_unspecified_core3")

#elif defined OVC_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_RODATA()

/****************************************  Variable Sections *******************************/
#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_BOOLEAN

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_bool_core3")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_8

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_8
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_8_core3")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_8
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_8
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_16

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_16
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_16_core3")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_16
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_16
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_32

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_32
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_32_core3")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_32
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_32
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_UNSPECIFIED

    #undef OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_no_init_asil_d_unspecified_core3")

#elif defined OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_NO_INIT_ASIL_D_CORE3_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_NO_INIT_ASIL_D_CORE3_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_BOOLEAN

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_bool_core3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_8

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_8
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_8_core3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_8
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_8
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_16

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_16
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_16_core3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_16
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_16
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_32

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_32
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_32_core3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_32
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_32
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED

    #undef OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_DATA(".sdk_data_asil_d_unspecified_core3")

#elif defined OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_INIT_ASIL_D_CORE3_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_DATA()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_BOOLEAN

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_BOOLEAN
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_bool_core3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_BOOLEAN
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_BOOLEAN
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_8

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_8
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_8_core3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_8
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_8
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_16

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_16
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_16_core3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_16
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_16
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_32

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_32
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_32_core3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_32
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_32
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

#elif defined OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED

    #undef OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
    #define INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".sdk_bss_asil_d_unspecified_core3")

#elif defined OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
    #ifdef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
        #undef INSIDE_OVC_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()

/****************************************  Code Sections *******************************/
#elif defined OVC_START_SEC_CODE_ASIL_D_CORE3

    #undef OVC_START_SEC_CODE_ASIL_D_CORE3
    #define INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE3

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_ASIL_D_CORE3
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_asil_d_core3")

#elif defined OVC_STOP_SEC_CODE_ASIL_D_CORE3

    #ifdef INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE3
        #undef INSIDE_OVC_START_SEC_CODE_ASIL_D_CORE3
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_ASIL_D_CORE3

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/****************************************  RAMCode Sections *******************************/
#elif defined OVC_START_SEC_RAMCODE_ASIL_D_CORE3

    #undef OVC_START_SEC_RAMCODE_ASIL_D_CORE3
    #define INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE3

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_RAMCODE_ASIL_D_CORE3
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_ramcode_asil_d_core3")

#elif defined OVC_STOP_SEC_RAMCODE_ASIL_D_CORE3

    #ifdef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE3
        #undef INSIDE_OVC_START_SEC_RAMCODE_ASIL_D_CORE3
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_RAMCODE_ASIL_D_CORE3

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Callout Code Sections ***************************/
#elif defined OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE3

    #undef OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE3
    #define INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE3

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE3
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_callout_asil_d_core3")

#elif defined OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE3

    #ifdef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE3
        #undef INSIDE_OVC_START_SEC_CALLOUT_CODE_ASIL_D_CORE3
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CALLOUT_CODE_ASIL_D_CORE3

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

/**********************************  Fast Code Sections ***************************/
#elif defined OVC_START_SEC_CODE_FAST_ASIL_D_CORE3

    #undef OVC_START_SEC_CODE_FAST_ASIL_D_CORE3
    #define INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE3

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE3
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif

    #undef MEMMAP_ERROR
    MEMMAP_START_TEXT(".sdk_text_fast_asil_d_core3")

#elif defined OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE3

    #ifdef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE3
        #undef INSIDE_OVC_START_SEC_CODE_FAST_ASIL_D_CORE3
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif

    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif

    #undef OVC_STOP_SEC_CODE_FAST_ASIL_D_CORE3

    #undef MEMMAP_ERROR
    MEMMAP_STOP_TEXT()

#endif

/**************************************************************************************************/
/****************************************** Report error ******************************************/
/**************************************************************************************************/
#ifdef MEMMAP_ERROR
    #error "MemMap.h, no valid memory mapping symbol defined."
#endif

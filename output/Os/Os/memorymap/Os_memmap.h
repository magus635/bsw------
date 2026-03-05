/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_MemMap.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : This document specifies mechanisms for the mapping of code and data to
*                           specific memory sections via memory mapping file. For many ECUs and
*                           microcontroller platforms it is of utmost necessity to be able to map
*                           code, variables and constants module wise to specific memory sections.
*                           This file contains sample code only. It is not part of the production
*                           code deliverables.
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
/**
* @brief Symbol used for checking correctness of the includes
*/
#define MEMMAP_ERROR
#if defined OS_START_SEC_CONFIG_DATA_QM_GLOBAL_BOOLEAN
    #undef OS_START_SEC_CONFIG_DATA_QM_GLOBAL_BOOLEAN
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_bool")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_BOOLEAN
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_BOOLEAN
    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_GLOBAL_8
    #undef OS_START_SEC_CONFIG_DATA_QM_GLOBAL_8
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_8")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_8
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_8
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_GLOBAL_16
    #undef OS_START_SEC_CONFIG_DATA_QM_GLOBAL_16
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_16")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_16
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_16
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_GLOBAL_32
    #undef OS_START_SEC_CONFIG_DATA_QM_GLOBAL_32
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_32")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_32
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_32
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
    #undef OS_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_unspecified")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_GLOBAL_BOOLEAN
    #undef OS_START_SEC_CONST_QM_GLOBAL_BOOLEAN
    #define INSIDE_OS_START_SEC_CONST_QM_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_bool")
#elif defined OS_STOP_SEC_CONST_QM_GLOBAL_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_BOOLEAN
        #undef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_GLOBAL_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_GLOBAL_8
    #undef OS_START_SEC_CONST_QM_GLOBAL_8
    #define INSIDE_OS_START_SEC_CONST_QM_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_GLOBAL_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_8")
#elif defined OS_STOP_SEC_CONST_QM_GLOBAL_8
    #ifdef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_8
        #undef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_GLOBAL_16
    #undef OS_START_SEC_CONST_QM_GLOBAL_16
    #define INSIDE_OS_START_SEC_CONST_QM_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_16")
#elif defined OS_STOP_SEC_CONST_QM_GLOBAL_16
    #ifdef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_16
        #undef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_GLOBAL_32
    #undef OS_START_SEC_CONST_QM_GLOBAL_32
    #define INSIDE_OS_START_SEC_CONST_QM_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_32")
#elif defined OS_STOP_SEC_CONST_QM_GLOBAL_32
    #ifdef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_32
        #undef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
    #undef OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
    #define INSIDE_OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_unspecified")
#elif defined OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_CONST_QM_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_BOOLEAN
    #undef OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_BOOLEAN
    #define INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_no_init_qm_bool")
#elif defined OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_BOOLEAN
        #undef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_8
    #undef OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_8
    #define INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_no_init_qm_8")
#elif defined OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_8
    #ifdef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_8
        #undef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_16
    #undef OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_16
    #define INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_no_init_qm_16")
#elif defined OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_16
    #ifdef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_16
        #undef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_32
    #undef OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_32
    #define INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_no_init_qm_32")
#elif defined OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_32
    #ifdef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_32
        #undef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED
    #undef OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED
    #define INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_no_init_qm_unspecified")
#elif defined OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_NO_INIT_QM_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN
    #undef OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_bool")
#elif defined OS_STOP_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_SEC_VAR_INIT_QM_GLOBAL_8
    #undef OS_START_SEC_SEC_VAR_INIT_QM_GLOBAL_8
    #define INSIDE_OS_START_SEC_SEC_VAR_INIT_QM_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_SEC_VAR_INIT_QM_GLOBAL_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_8")
#elif defined OS_STOP_SEC_SEC_VAR_INIT_QM_GLOBAL_8
    #ifdef INSIDE_OS_START_SEC_SEC_VAR_INIT_QM_GLOBAL_8
        #undef INSIDE_OS_START_SEC_SEC_VAR_INIT_QM_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_SEC_VAR_INIT_QM_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_GLOBAL_16
    #undef OS_START_SEC_VAR_INIT_QM_GLOBAL_16
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_16")
#elif defined OS_STOP_SEC_VAR_INIT_QM_GLOBAL_16
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_16
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_GLOBAL_32
    #undef OS_START_SEC_VAR_INIT_QM_GLOBAL_32
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_32")
#elif defined OS_STOP_SEC_VAR_INIT_QM_GLOBAL_32
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_32
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
    #undef OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_unspecified")
#elif defined OS_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_bool")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_8")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_16")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_16
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_32")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_unspecified")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
    #undef OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_bool_uncached")
#elif defined OS_STOP_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE
    #undef OS_START_SEC_VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_8_uncached")
#elif defined OS_STOP_SEC_VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE
    #undef OS_START_SEC_VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_16_uncached")
#elif defined OS_STOP_SEC_VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE
    #undef OS_START_SEC_VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_32_uncached")
#elif defined OS_STOP_SEC_VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #undef OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_unspecified_uncached")
#elif defined OS_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_bool_uncached")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_BOOLEAN_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_8_uncached")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_8_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_16_uncached")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_16_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_32_uncached")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_32_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #undef OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_unspecified_uncached")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_GLOBAL_UNSPECIFIED_NO_CACHEABLE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CODE_QM_GLOBAL
    #undef OS_START_SEC_CODE_QM_GLOBAL
    #define INSIDE_OS_START_SEC_CODE_QM_GLOBAL

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CODE_QM_GLOBAL
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_text_qm")
#elif defined OS_STOP_SEC_CODE_QM_GLOBAL
    #ifdef INSIDE_OS_START_SEC_CODE_QM_GLOBAL
        #undef INSIDE_OS_START_SEC_CODE_QM_GLOBAL
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CODE_QM_GLOBAL

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CALLOUT_CODE_QM_GLOBAL
    #undef OS_START_SEC_CALLOUT_CODE_QM_GLOBAL
    #define INSIDE_OS_START_SEC_CALLOUT_CODE_QM_GLOBAL

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CALLOUT_CODE_QM_GLOBAL
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_text_callout_qm")
#elif defined OS_STOP_SEC_CALLOUT_CODE_QM_GLOBAL
    #ifdef INSIDE_OS_START_SEC_CALLOUT_CODE_QM_GLOBAL
        #undef INSIDE_OS_START_SEC_CALLOUT_CODE_QM_GLOBAL
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CALLOUT_CODE_QM_GLOBAL

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE0_BOOLEAN
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE0_BOOLEAN
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_bool_core0")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE0_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_BOOLEAN
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE0_8
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE0_8
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_8_core0")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE0_8
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_8
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE0_16
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE0_16
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_16_core0")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE0_16
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_16
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE0_32
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE0_32
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_32_core0")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE0_32
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_32
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_unspecified_core0")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE0_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE0_BOOLEAN
    #undef OS_START_SEC_CONST_QM_CORE0_BOOLEAN
    #define INSIDE_OS_START_SEC_CONST_QM_CORE0_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE0_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_bool_core0")
#elif defined OS_STOP_SEC_CONST_QM_CORE0_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE0_BOOLEAN
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE0_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE0_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE0_8
    #undef OS_START_SEC_CONST_QM_CORE0_8
    #define INSIDE_OS_START_SEC_CONST_QM_CORE0_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE0_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_8_core0")
#elif defined OS_STOP_SEC_CONST_QM_CORE0_8
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE0_8
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE0_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE0_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE0_16
    #undef OS_START_SEC_CONST_QM_CORE0_16
    #define INSIDE_OS_START_SEC_CONST_QM_CORE0_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE0_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_16_core0")
#elif defined OS_STOP_SEC_CONST_QM_CORE0_16
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE0_16
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE0_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE0_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE0_32
    #undef OS_START_SEC_CONST_QM_CORE0_32
    #define INSIDE_OS_START_SEC_CONST_QM_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_32_core0")
#elif defined OS_STOP_SEC_CONST_QM_CORE0_32
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE0_32
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE0_UNSPECIFIED
    #undef OS_START_SEC_CONST_QM_CORE0_UNSPECIFIED
    #define INSIDE_OS_START_SEC_CONST_QM_CORE0_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE0_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_unspecified_core0")
#elif defined OS_STOP_SEC_CONST_QM_CORE0_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE0_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE0_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE0_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE0_BOOLEAN
    #undef OS_START_SEC_VAR_INIT_QM_CORE0_BOOLEAN
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE0_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_bool_core0")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE0_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_BOOLEAN
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE0_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE0_8
    #undef OS_START_SEC_VAR_INIT_QM_CORE0_8
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE0_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_8_core0")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE0_8
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_8
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE0_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE0_16
    #undef OS_START_SEC_VAR_INIT_QM_CORE0_16
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE0_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_16_core0")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE0_16
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_16
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE0_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE0_32
    #undef OS_START_SEC_VAR_INIT_QM_CORE0_32
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_32_core0")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE0_32
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_32
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
    #undef OS_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_unspecified_core0")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE0_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE0_BOOLEAN
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE0_BOOLEAN
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_bool_core0")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE0_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_BOOLEAN
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE0_8
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE0_8
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_8_core0")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE0_8
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_8
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE0_16
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE0_16
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_16_core0")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE0_16
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_16
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE0_32
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE0_32
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_32_core0")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE0_32
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_32
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_unspecified_core0")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE0_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
    #undef OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
    #define INSIDE_OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_trust_qm_32_core0")
#elif defined OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
    #ifdef INSIDE_OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
        #undef INSIDE_OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
    #undef OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
    #define INSIDE_OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_nontrust_qm_32_core0")
#elif defined OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
    #ifdef INSIDE_OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
        #undef INSIDE_OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CODE_QM_CORE0
    #undef OS_START_SEC_CODE_QM_CORE0
    #define INSIDE_OS_START_SEC_CODE_QM_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CODE_QM_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_text_qm_core0")
#elif defined OS_STOP_SEC_CODE_QM_CORE0
    #ifdef INSIDE_OS_START_SEC_CODE_QM_CORE0
        #undef INSIDE_OS_START_SEC_CODE_QM_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CODE_QM_CORE0

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_RAMCODE_QM_CORE0
    #undef OS_START_SEC_RAMCODE_QM_CORE0
    #define INSIDE_OS_START_SEC_RAMCODE_QM_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_RAMCODE_QM_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_ramcode_qm_core0")
#elif defined OS_STOP_SEC_RAMCODE_QM_CORE0
    #ifdef INSIDE_OS_START_SEC_RAMCODE_QM_CORE0
        #undef INSIDE_OS_START_SEC_RAMCODE_QM_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_RAMCODE_QM_CORE0

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CALLOUT_CODE_QM_CORE0
    #undef OS_START_SEC_CALLOUT_CODE_QM_CORE0
    #define INSIDE_OS_START_SEC_CALLOUT_CODE_QM_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CALLOUT_CODE_QM_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_text_callout_qm_core0")
#elif defined OS_STOP_SEC_CALLOUT_CODE_QM_CORE0
    #ifdef INSIDE_OS_START_SEC_CALLOUT_CODE_QM_CORE0
        #undef INSIDE_OS_START_SEC_CALLOUT_CODE_QM_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CALLOUT_CODE_QM_CORE0

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CODE_FAST_QM_CORE0
    #undef OS_START_SEC_CODE_FAST_QM_CORE0
    #define INSIDE_OS_START_SEC_CODE_FAST_QM_CORE0

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CODE_FAST_QM_CORE0
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_text_fast_qm_core0")
#elif defined OS_STOP_SEC_CODE_FAST_QM_CORE0
    #ifdef INSIDE_OS_START_SEC_CODE_FAST_QM_CORE0
        #undef INSIDE_OS_START_SEC_CODE_FAST_QM_CORE0
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CODE_FAST_QM_CORE0

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE1_BOOLEAN
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE1_BOOLEAN
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_bool_core1")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE1_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_BOOLEAN
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE1_8
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE1_8
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_8_core1")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE1_8
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_8
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE1_16
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE1_16
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_16_core1")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE1_16
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_16
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE1_32
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE1_32
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_32_core1")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE1_32
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_32
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
    #undef OS_START_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
    #define INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_cfg_qm_unspecified_core1")
#elif defined OS_STOP_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONFIG_DATA_QM_CORE1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE1_BOOLEAN
    #undef OS_START_SEC_CONST_QM_CORE1_BOOLEAN
    #define INSIDE_OS_START_SEC_CONST_QM_CORE1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_bool_core1")
#elif defined OS_STOP_SEC_CONST_QM_CORE1_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE1_BOOLEAN
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE1_8
    #undef OS_START_SEC_CONST_QM_CORE1_8
    #define INSIDE_OS_START_SEC_CONST_QM_CORE1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_8_core1")
#elif defined OS_STOP_SEC_CONST_QM_CORE1_8
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE1_8
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE1_16
    #undef OS_START_SEC_CONST_QM_CORE1_16
    #define INSIDE_OS_START_SEC_CONST_QM_CORE1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_16_core1")
#elif defined OS_STOP_SEC_CONST_QM_CORE1_16
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE1_16
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE1_32
    #undef OS_START_SEC_CONST_QM_CORE1_32
    #define INSIDE_OS_START_SEC_CONST_QM_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_32_core1")
#elif defined OS_STOP_SEC_CONST_QM_CORE1_32
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE1_32
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CONST_QM_CORE1_UNSPECIFIED
    #undef OS_START_SEC_CONST_QM_CORE1_UNSPECIFIED
    #define INSIDE_OS_START_SEC_CONST_QM_CORE1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CONST_QM_CORE1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_const_qm_unspecified_core1")
#elif defined OS_STOP_SEC_CONST_QM_CORE1_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_CONST_QM_CORE1_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_CONST_QM_CORE1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CONST_QM_CORE1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE1_BOOLEAN
    #undef OS_START_SEC_VAR_INIT_QM_CORE1_BOOLEAN
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_bool_core1")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE1_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_BOOLEAN
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE1_8
    #undef OS_START_SEC_VAR_INIT_QM_CORE1_8
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_8_core1")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE1_8
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_8
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE1_16
    #undef OS_START_SEC_VAR_INIT_QM_CORE1_16
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_16_core1")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE1_16
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_16
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE1_32
    #undef OS_START_SEC_VAR_INIT_QM_CORE1_32
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_32_core1")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE1_32
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_32
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
    #undef OS_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_data_qm_unspecified_core1")
#elif defined OS_STOP_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_CORE1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE1_BOOLEAN
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE1_BOOLEAN
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_BOOLEAN

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_BOOLEAN
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_bool_core1")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE1_BOOLEAN
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_BOOLEAN
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_BOOLEAN
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_BOOLEAN

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE1_8
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE1_8
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_8

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_8
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_8_core1")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE1_8
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_8
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_8
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_8

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE1_16
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE1_16
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_16

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_16
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_16_core1")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE1_16
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_16
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_16
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_16

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE1_32
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE1_32
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_32_core1")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE1_32
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_32
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
    #undef OS_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_bss_qm_unspecified_core1")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_CORE1_UNSPECIFIED

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
    #undef OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
    #define INSIDE_OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_trust_qm_32_core1")
#elif defined OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
    #ifdef INSIDE_OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
        #undef INSIDE_OS_START_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_TRUSTED_VAR_CLEARED_QM_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE1_32
    #undef OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE1_32
    #define INSIDE_OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_nontrust_qm_32_core1")
#elif defined OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE1_32
    #ifdef INSIDE_OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE1_32
        #undef INSIDE_OS_START_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_NONTRUSTED_VAR_CLEARED_QM_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CODE_QM_CORE1
    #undef OS_START_SEC_CODE_QM_CORE1
    #define INSIDE_OS_START_SEC_CODE_QM_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CODE_QM_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_text_qm_core1")
#elif defined OS_STOP_SEC_CODE_QM_CORE1
    #ifdef INSIDE_OS_START_SEC_CODE_QM_CORE1
        #undef INSIDE_OS_START_SEC_CODE_QM_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CODE_QM_CORE1

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_RAMCODE_QM_CORE1
    #undef OS_START_SEC_RAMCODE_QM_CORE1
    #define INSIDE_OS_START_SEC_RAMCODE_QM_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_RAMCODE_QM_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_ramcode_qm_core1")
#elif defined OS_STOP_SEC_RAMCODE_QM_CORE1
    #ifdef INSIDE_OS_START_SEC_RAMCODE_QM_CORE1
        #undef INSIDE_OS_START_SEC_RAMCODE_QM_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_RAMCODE_QM_CORE1

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CALLOUT_CODE_QM_CORE1
    #undef OS_START_SEC_CALLOUT_CODE_QM_CORE1
    #define INSIDE_OS_START_SEC_CALLOUT_CODE_QM_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CALLOUT_CODE_QM_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_text_callout_qm_core1")
#elif defined OS_STOP_SEC_CALLOUT_CODE_QM_CORE1
    #ifdef INSIDE_OS_START_SEC_CALLOUT_CODE_QM_CORE1
        #undef INSIDE_OS_START_SEC_CALLOUT_CODE_QM_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CALLOUT_CODE_QM_CORE1

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CODE_FAST_QM_CORE1
    #undef OS_START_SEC_CODE_FAST_QM_CORE1
    #define INSIDE_OS_START_SEC_CODE_FAST_QM_CORE1

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CODE_FAST_QM_CORE1
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_text_fast_qm_core1")
#elif defined OS_STOP_SEC_CODE_FAST_QM_CORE1
    #ifdef INSIDE_OS_START_SEC_CODE_FAST_QM_CORE1
        #undef INSIDE_OS_START_SEC_CODE_FAST_QM_CORE1
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CODE_FAST_QM_CORE1

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_CLEARED_QM_PRIVATE_CLONE
    #undef OS_START_SEC_VAR_CLEARED_QM_PRIVATE_CLONE
    #define INSIDE_OS_START_SEC_VAR_CLEARED_QM_PRIVATE_CLONE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_CLEARED_QM_PRIVATE_CLONE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".private_clone_bss")
#elif defined OS_STOP_SEC_VAR_CLEARED_QM_PRIVATE_CLONE
    #ifdef INSIDE_OS_START_SEC_VAR_CLEARED_QM_PRIVATE_CLONE
        #undef INSIDE_OS_START_SEC_VAR_CLEARED_QM_PRIVATE_CLONE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_CLEARED_QM_PRIVATE_CLONE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_VAR_INIT_QM_PRIVATE_CLONE
    #undef OS_START_SEC_VAR_INIT_QM_PRIVATE_CLONE
    #define INSIDE_OS_START_SEC_VAR_INIT_QM_PRIVATE_CLONE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_VAR_INIT_QM_PRIVATE_CLONE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".private_clone_data")
#elif defined OS_STOP_SEC_VAR_INIT_QM_PRIVATE_CLONE
    #ifdef INSIDE_OS_START_SEC_VAR_INIT_QM_PRIVATE_CLONE
        #undef INSIDE_OS_START_SEC_VAR_INIT_QM_PRIVATE_CLONE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_VAR_INIT_QM_PRIVATE_CLONE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_CODE_QM_PRIVATE_CLONE
    #undef OS_START_SEC_CODE_QM_PRIVATE_CLONE
    #define INSIDE_OS_START_SEC_CODE_QM_PRIVATE_CLONE

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_CODE_QM_PRIVATE_CLONE
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".private_clone_code")
#elif defined OS_STOP_SEC_CODE_QM_PRIVATE_CLONE
    #ifdef INSIDE_OS_START_SEC_CODE_QM_PRIVATE_CLONE
        #undef INSIDE_OS_START_SEC_CODE_QM_PRIVATE_CLONE
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_CODE_QM_PRIVATE_CLONE

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_STACKCFG_QM_CORE0_32
    #undef OS_START_SEC_STACKCFG_QM_CORE0_32
    #define INSIDE_OS_START_SEC_STACKCFG_QM_CORE0_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_STACKCFG_QM_CORE0_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_stack_qm_32_core0")
#elif defined OS_STOP_SEC_STACKCFG_QM_CORE0_32
    #ifdef INSIDE_OS_START_SEC_STACKCFG_QM_CORE0_32
        #undef INSIDE_OS_START_SEC_STACKCFG_QM_CORE0_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_STACKCFG_QM_CORE0_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#elif defined OS_START_SEC_STACKCFG_QM_CORE1_32
    #undef OS_START_SEC_STACKCFG_QM_CORE1_32
    #define INSIDE_OS_START_SEC_STACKCFG_QM_CORE1_32

    #ifndef MEMMAP_MATCH_ERROR
        #define MEMMAP_MATCH_ERROR
    #else
        #ifndef OS_STOP_SEC_STACKCFG_QM_CORE1_32
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
    #endif
    #undef MEMMAP_ERROR
    MEMMAP_START_BSS(".os_stack_qm_32_core1")
#elif defined OS_STOP_SEC_STACKCFG_QM_CORE1_32
    #ifdef INSIDE_OS_START_SEC_STACKCFG_QM_CORE1_32
        #undef INSIDE_OS_START_SEC_STACKCFG_QM_CORE1_32
    #else
        #error "MemMap.h, no valid matching start-stop section defined."
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        #undef MEMMAP_MATCH_ERROR
    #endif
    #undef OS_STOP_SEC_STACKCFG_QM_CORE1_32

    #undef MEMMAP_ERROR
    MEMMAP_STOP_BSS()
#endif

/**************************************************************************************************/
/****************************************** Report error ******************************************/
/**************************************************************************************************/
#ifdef MEMMAP_ERROR
    #error "MemMap.h, no valid memory mapping symbol defined."
#endif
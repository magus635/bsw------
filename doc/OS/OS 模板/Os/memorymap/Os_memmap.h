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
[!VAR "FirstCall" = "0"!][!//
[!INDENT "0"!][!//
[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/OsMemoryMap"!][!//
    [!LOOP "node:order(./*,'@index')"!][!//
        [!IF "$FirstCall = 0"!][!//
            [!VAR "FirstCall" = "1"!][!//
#if defined OS_START_SEC_[!"node:name(.)"!]
    [!INDENT "4"!][!//
    [!VAR "MemorySectionName" = "node:name(node:ref(./MemorySectionMatch))"!][!//
    #undef OS_START_SEC_[!"node:name(.)"!]
    #define INSIDE_OS_START_SEC_[!"node:name(.)"!]

    #ifndef MEMMAP_MATCH_ERROR
        [!INDENT "8"!][!//
        #define MEMMAP_MATCH_ERROR
        [!ENDINDENT!][!//
    #else
        [!INDENT "8"!][!//
        #ifndef OS_STOP_SEC_[!"node:name(.)"!]
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
        [!ENDINDENT!][!//
    #endif
    #undef MEMMAP_ERROR
    [!LOOP "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock/*"!][!//
        [!LOOP "./MemorySectionRef/*"!][!//
            [!IF "$MemorySectionName = node:name(node:ref(.))"!][!//
                [!VAR "MemoryAttribute" = "node:value(../../MemoryRegionType)"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!IF "$MemoryAttribute = 'RO_CODE'"!][!//
        MEMMAP_START_TEXT(".[!"node:name(node:ref(./MemorySectionMatch))"!]")
    [!ELSEIF "$MemoryAttribute = 'RO_DATA'"!][!//
        MEMMAP_START_RODATA(".[!"node:name(node:ref(./MemorySectionMatch))"!]")
    [!ELSEIF "$MemoryAttribute = 'VARIABLE'"!][!//
        MEMMAP_START_DATA(".[!"node:name(node:ref(./MemorySectionMatch))"!]")
    [!ELSE!][!//
        MEMMAP_START_BSS(".[!"node:name(node:ref(./MemorySectionMatch))"!]")
    [!ENDIF!][!//

    [!ENDINDENT!][!//
#elif defined OS_STOP_SEC_[!"node:name(.)"!]
    [!INDENT "4"!][!//
    #ifdef INSIDE_OS_START_SEC_[!"node:name(.)"!]
        [!INDENT "8"!][!//
        #undef INSIDE_OS_START_SEC_[!"node:name(.)"!]
        [!ENDINDENT!][!//
    #else
        [!INDENT "8"!][!//
        #error "MemMap.h, no valid matching start-stop section defined."
        [!ENDINDENT!][!//
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        [!INDENT "8"!][!//
        #undef MEMMAP_MATCH_ERROR
        [!ENDINDENT!][!//
    #endif
    #undef OS_STOP_SEC_[!"node:name(.)"!]
    #undef MEMMAP_ERROR
    [!IF "$MemoryAttribute = 'RO_CODE'"!][!//
        MEMMAP_STOP_TEXT()
    [!ELSEIF "$MemoryAttribute = 'RO_DATA'"!][!//
        MEMMAP_STOP_RODATA()
    [!ELSEIF "$MemoryAttribute = 'VARIABLE'"!][!//
        MEMMAP_STOP_DATA()
    [!ELSE!][!//
        MEMMAP_STOP_BSS()
    [!ENDIF!][!//

    [!ENDINDENT!][!//
        [!ELSE!][!//
#elif defined OS_START_SEC_[!"node:name(.)"!]
    [!VAR "MemorySectionName" = "node:name(node:ref(./MemorySectionMatch))"!][!//
    [!INDENT "4"!][!//
    #undef OS_START_SEC_[!"node:name(.)"!]
    #define INSIDE_OS_START_SEC_[!"node:name(.)"!]

    #ifndef MEMMAP_MATCH_ERROR
        [!INDENT "8"!][!//
        #define MEMMAP_MATCH_ERROR
        [!ENDINDENT!][!//
    #else
        [!INDENT "8"!][!//
        #ifndef OS_STOP_SEC_[!"node:name(.)"!]
        #error "MemMap.h, no valid matching start-stop section defined."
        #endif
        [!ENDINDENT!][!//
    #endif
    #undef MEMMAP_ERROR
    [!LOOP "/AUTOSAR/TOP-LEVEL-PACKAGES/Os/ELEMENTS/Os/MemoryBlock/*"!][!//
        [!LOOP "./MemorySectionRef/*"!][!//
            [!IF "$MemorySectionName = node:name(node:ref(.))"!][!//
                [!VAR "MemoryAttribute" = "node:value(../../MemoryRegionType)"!][!//
            [!ENDIF!][!//
        [!ENDLOOP!][!//
    [!ENDLOOP!][!//
    [!IF "$MemoryAttribute = 'RO_CODE'"!][!//
        MEMMAP_START_TEXT(".[!"node:name(node:ref(./MemorySectionMatch))"!]")
    [!ELSEIF "$MemoryAttribute = 'RO_DATA'"!][!//
        MEMMAP_START_RODATA(".[!"node:name(node:ref(./MemorySectionMatch))"!]")
    [!ELSEIF "$MemoryAttribute = 'VARIABLE'"!][!//
        MEMMAP_START_DATA(".[!"node:name(node:ref(./MemorySectionMatch))"!]")
    [!ELSE!][!//
        MEMMAP_START_BSS(".[!"node:name(node:ref(./MemorySectionMatch))"!]")
    [!ENDIF!][!//

    [!ENDINDENT!][!//
#elif defined OS_STOP_SEC_[!"node:name(.)"!]
    [!INDENT "4"!][!//
    #ifdef INSIDE_OS_START_SEC_[!"node:name(.)"!]
        [!INDENT "8"!][!//
        #undef INSIDE_OS_START_SEC_[!"node:name(.)"!]
        [!ENDINDENT!][!//
    #else
        [!INDENT "8"!][!//
        #error "MemMap.h, no valid matching start-stop section defined."
        [!ENDINDENT!][!//
    #endif
    #ifdef MEMMAP_MATCH_ERROR
        [!INDENT "8"!][!//
        #undef MEMMAP_MATCH_ERROR
        [!ENDINDENT!][!//
    #endif
    #undef OS_STOP_SEC_[!"node:name(.)"!]

    #undef MEMMAP_ERROR
    [!IF "$MemoryAttribute = 'RO_CODE'"!][!//
        MEMMAP_STOP_TEXT()
    [!ELSEIF "$MemoryAttribute = 'RO_DATA'"!][!//
        MEMMAP_STOP_RODATA()
    [!ELSEIF "$MemoryAttribute = 'VARIABLE'"!][!//
        MEMMAP_STOP_DATA()
    [!ELSE!][!//
        MEMMAP_STOP_BSS()
    [!ENDIF!][!//

    [!ENDINDENT!][!//
        [!ENDIF!][!//
    [!ENDLOOP!][!//
[!ENDSELECT!][!//
[!ENDINDENT!][!//
[!/* Close the #if chain only if it was opened: without any OsMemoryMap entry the chain is empty and a
     bare #endif would not compile; MEMMAP_ERROR below then reports the missing section. */!][!//
[!IF "$FirstCall = 1"!][!//
#endif
[!ENDIF!][!//

/**************************************************************************************************/
/****************************************** Report error ******************************************/
/**************************************************************************************************/
#ifdef MEMMAP_ERROR
    #error "MemMap.h, no valid memory mapping symbol defined."
#endif
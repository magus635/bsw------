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
#endif

/**************************************************************************************************/
/****************************************** Report error ******************************************/
/**************************************************************************************************/
#ifdef MEMMAP_ERROR
    #error "MemMap.h, no valid memory mapping symbol defined."
#endif
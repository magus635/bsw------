/**************************************************************************************************
*
***************************************************************************************************/
/**************************************************************************************************
*   FileName             : CanIf_Typedefs.h
*
*   Platform             : AUTOSAR
*
*   brief                : This file contains sample code only. It is not part of the production
*                          code deliverables.
*
*   Autosar Version      : 4.4.0
*
*   SW Version           : 1.0.0
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
***************************************************************************************************/
/**************************************************************************************************/
#ifndef CANIF_TYPEDEFS_H_
#define CANIF_TYPEDEFS_H_
/***************************************************************************************************
*                               Include
***************************************************************************************************/
#include "ComStack_Types.h"

/*=================================================================================================*/
/**
* brief          CanIf_ControllerModeType
* details        Operating modes of the CAN Controller and CAN Driver
*
*/
typedef enum
{
    CANIF_CS_UNINIT = 0U,    /**< brief UNINIT mode */
    CANIF_CS_SLEEP,         /**< brief SLEEP mode */
    CANIF_CS_STARTED,        /**< brief STARTED mode */
    CANIF_CS_STOPPED        /**< brief STOPPED mode */
} CanIf_ControllerModeType;



#endif

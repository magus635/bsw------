/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Mcall_GeneralTypes.h
 *
 *   Platform              : AUTOSAR
 *
 *   brief                 : This file contains all type definitions of Mcall Driver
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/

#ifndef MCALL_GENERAL_TYPES_H_
#define MCALL_GENERAL_TYPES_H_

/****************************************************************************************************
 *                               Include
 ****************************************************************************************************/
#include "Std_Types.h"
#include "multicore.h"

/****************************************************************************************************
 *                               Symbol Definitions
 ****************************************************************************************************/
/* Type for core id */
typedef MultiCoreID Mcal_CoreType;

/****************************************************************************************************
 *                               Typedef Enum
 ****************************************************************************************************/
/* Type for modules that need the lock */
typedef enum
{
    /* Lock for INTC module */
    MCAL_LOCK_ID_INTC = 0U,
    /* Lock for GPT module */
    MCAL_LOCK_ID_GPT,
    /* Lock for PORT module */
    MCAL_LOCK_ID_PORT,
    /* Lock for ICU module */
    MCAL_LOCK_ID_ICU,
    /* Lock for RCC reset */
    MCAL_LOCK_ID_RCC,
    /* Lock for PWM module */
    MCAL_LOCK_ID_PWM,
    /* Lock for Mcu module */
    MCAL_LOCK_ID_MCU,    
    /* Lock for Ocu module */
    MCAL_LOCK_ID_OCU,    
    /* Total number of all Locks */
    MCAL_LOCK_ID_NUM
} Mcal_LockIdType;

typedef struct
{
    uint32 LockStatus;  /* Lock of GIPC. 0: Unlocked; 1: Locked */
    uint32 Reserved[15]; /* Reserved to ensure that the size of structure conforms to marked address size(64 Bytes). */
} Mcal_LockType;


/****************************************************************************************************
 *                               Type Definitions
 ****************************************************************************************************/

#endif /* MCALL_GENERAL_TYPES_H_ */

/****************************************************************************************************
**                      End of File
****************************************************************************************************/

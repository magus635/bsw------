/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Intc_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Intc/GIC
*
*   brief                 : This file contains all type definitions of Intc Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright \(c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*
*#Intc_GeneralTypes_h_REF_1:CertC-DCL12-C;
* Justification: MCAL code is open-source without using opaque types.
*
*/

#ifndef INTC_GENERAL_TYPES_H_
#define INTC_GENERAL_TYPES_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Intc_Cfg.h"
#include "Mcall.h"
/* Header files including the HAL layer */
#include "intc_hal.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define INTC_ATOMIC_BUSY       (Std_ReturnType)(0x02U)

/****************************************************************************************************
**                          Global basic type Definitions                                          **
****************************************************************************************************/
/* Type definition for numeric id for interrupt source */
typedef uint16 Intc_IntSrcType;
/* Type definition for interrupt configuration */
typedef Intc_InterruptConfig Intc_IntSrcConfigType;
/* Type definition for software interrupt generation */
typedef Intc_TargetCore Intc_TargetCoreType;
/* Type definition for interrupt handler */
typedef IntHandler Intc_HandlerType;
/* Type definition for interrupt handler (for compatibility) */
typedef IntHandler IntHandlerType;

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
#if (INTC_DEV_ERROR_DETECT == STD_ON)
/* Interrupt source install status */
typedef enum
{
    INTC_UNINITIALIZE = 0U,
    INTC_INITIALIZED
} Intc_InitType;
#endif /* (INTC_DEV_ERROR_DETECT  \== STD_ON) */

/* Interrupt install processing */
typedef enum
{
    /* Interrupt source list parameter error */
    INTC_STA_ERR = 0U,
    /* Installing the interrupt source */
    INTC_STA_INSTALLING,
    /* All interrupt source installed successfully */
    INTC_STA_INS_FINISHED,
    /* The interrupt is not installed because the master core is installing the interrupt source.
     * This status is only for slave cores */
    INTC_STA_INS_BLOCKED
} Intc_InsStaType;

/* Interrupt install status of Master core */
typedef enum
{
    /* INTC not mapped by master core */
    INTC_MASTER_CORE_NOT_MAP = 0U,
    /* INTC mapped by master core */
    INTC_MASTER_CORE_MAPPED
} Intc_MapStatusType;

/****************************************************************************************************
**                          Global Structure Definitions                                          **
****************************************************************************************************/
/* Type for interrupt configuration */
typedef struct
{
    /* Total number of interrupt sources for core */
    Intc_IntSrcType                    TotalIntSrcNum;
    /* Pointer to the interrupt sources mapping list for core */
    const Intc_IntSrcConfigType        *IntSrcConfigPtr;
} Intc_CoreConfigType;

/* Type for Intc driver configuration and used for initializing driver */
/* #Violation: Intc_GeneralTypes_h_REF_1 */
typedef struct 
{
    /* Pointer to the list of interrupt source set */
    const Intc_CoreConfigType          CoreConfigPtr[MCAL_NUMBER_OF_CORES];
} Intc_ConfigType;

#endif /* INTC_GENERAL_TYPES_H_ */

/****************************************************************************************************
**                      End of File
****************************************************************************************************/

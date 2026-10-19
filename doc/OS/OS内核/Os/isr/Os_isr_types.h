/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_isr_types.h
*
*   Platform              : AUTOSAR
*
*   BSW Module            : Os
*
*   brief                 : xxx
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
#ifndef OS_ISR_TYPES_H_
#define OS_ISR_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "datatypes.h"
#include "Std_Types.h"
#include "Os_GeneralTypes.h"
#include "Os_lock_types.h"
#include "Os_spinlock_types.h"
#include "Os_isr_Cfg.h"
#include "Os_isr_hal_types.h"
#include "Os_ArtiCfg.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef uint32 ISRType;
typedef uint32 Os_IsrLevelType;
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    OS_INTERRUPTTYPE_CAT1,
    OS_INTERRUPTTYPE_CAT2
}Os_InterruptType;
/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
typedef struct
{
    /* Resource/Spinlock used by ISR */
    Os_LockConfigRefType LockList;
    /* Spinlock used by ISR */
    Os_SpinlockConfigRefType SpinlockOccupied;
#if (OS_ARTI_TRACE_CAT2ISR == STD_ON)
    /* ARTI shadow state (OS_ARTI_ISR_*), for Preempt / Resume of nested ISR2 */
    uint8 ArtiState;
#endif
}Os_IsrDynamicType;

typedef struct
{
    /* Interrupt configuration structure */
    Os_Isr_Hal_ConfigType IsrHwConfig;
    /* ISR type */
    Os_InterruptType IntType;
    /* ISR ID */
    ISRType ISRID;
    /* Object ID */
    uint32 ObjectID;
    /* If this isr is used to inter core service call */
    boolean isCrossCore;
    /* Entry function address */
    uint32 InterruptHandlerAddress;
    /* Running data for each isr */
    P2VAR(Os_IsrDynamicType, TYPEDEF, OS_VAR) IsrRunningData;
}Os_IsrConfigType;

typedef struct
{
    /* Flag to DisableAllInterrupt */
    boolean IsrDisableAll;
    /* The number of suspend all interrupt nesting */
    uint32 SuspendAllCount;
    /* The number of suspend os interrupt nesting */
    uint32 SuspendOsCount;
    /* Bit array to record the order of SuspendAllInterrupt/SuspendOsInterrupt */
    uint32 SuspendIsrBitArray;
    /* The isr level before suspend all interrupt */
    Os_IsrLevelType PreviousIsr1Level;
    /* The isr level before suspend os interrupt */
    Os_IsrLevelType PreviousIsr2Level;
}Os_IsrRunningDataType;

typedef P2CONST(Os_IsrConfigType, TYPEDEF, OS_CONST) Os_IsrConfigRefType;

#endif /* OS_ISR_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_isr_types.h                                                                 **
****************************************************************************************************/


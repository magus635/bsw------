/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_spinlock_types.h
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
#ifndef OS_SPINLOCK_TYPES_H_
#define OS_SPINLOCK_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "datatypes.h"
#include "Std_Types.h"
#include "Os_GeneralTypes.h"
#include "Os_lock_types.h"
#include "Compiler.h"
#include "compilertypes.h"
#include "Os_spinlock_Cfg.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef uint32 SpinlockIdType;
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
typedef enum
{
    LOCK_ALL_INTERRUPTS,
    LOCK_CAT2_INTERRUPTS,
    LOCK_NOTHING,
    LOCK_WITH_RES_SCHEDULER
}Os_SpinlockLockMethodType;

typedef enum
{
    TRYTOGETSPINLOCK_NOSUCCESS,
    TRYTOGETSPINLOCK_SUCCESS
}TryToGetSpinlockType;
/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
typedef struct ALIGNED(16)
{
    /* Lock of GIPC. 0: Unlocked; 1: Locked */
    uint32 lockStatus;
    /* Reserved to ensure that the size of structure conforms to marked address size(16 Bytes). */
    uint32 reserved[3];
} Os_SpinlockLockType;

struct Os_SpinlockCfgType;
typedef struct
{
    /* Task priority before getting this spinlock */
    uint32 PreviousTaskPriority;
    /* ObjectID of template owner of this spinlock */
    uint32 OwnerObjectID;
    /* Pointer to previous spinlock */
    P2VAR(struct Os_SpinlockCfgType, AUTOMATIC, OS_VAR) Previous;
}Os_SpinlockRunningDataType;

typedef struct Os_SpinlockCfgType
{
    SpinlockIdType SpinlockId;
    /* Lock status of spinlock. 0: Unlocked; 1: Locked */
    P2VAR(Os_SpinlockLockType, AUTOMATIC, OS_VAR) LockStatus;
    Os_LockConfigRefType Lock;
    /* The behaviour while spinlock is occupied */
    Os_SpinlockLockMethodType OsSpinlockLockMethod;
    /* Id used to indicate the order of nesting */
    uint32 SpinlockSuccessorID;
    uint32 SpinlockSuccessorListID;
    /* Mask of applications that can access current spinlock */
    uint32 AccessApplicationIdMask;
    /* Spinlock running data */
    P2VAR(Os_SpinlockRunningDataType, AUTOMATIC, OS_VAR) SpinlockRunningData;
}Os_SpinlockConfigType;

typedef P2CONST(Os_SpinlockConfigType, AUTOMATIC, OS_CONST) Os_SpinlockConfigRefType;

#endif /* OS_SPINLOCK_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_spinlock_types.h                                                            **
****************************************************************************************************/


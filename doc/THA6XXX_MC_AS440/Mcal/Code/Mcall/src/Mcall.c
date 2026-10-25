/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Mcall.c
 *
 *   Platform              : AUTOSAR
 *
 *   brief                 : Mcal common Macros and functions Definitions.
 *
 *   Autosar Version       : 4.4.0
 *
 *   Build Version         : Cortex-R52+/THA6xxx
 *
 *   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
 *
 ****************************************************************************************************/

/*
*#Violation Summary
*
*#Mcall_c_REF_1:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the
*   driver must be placed.
*
*#Mcall_c_REF_2:MISRAC2012-Rule-8.13;
* Justification: The object values be modified during assembly execution.
*
*#Mcall_c_REF_3:MISRAC2012-Rule-1.2;
* Justification: Inline assembly for CPU-specific operations.
*
*#Mcall_c_REF_4:MISRAC2012-Rule-2.2;
* Justification: Value used in assembly code.
*
*#Mcall_c_REF_5:MISRAC2012-Dir-4.3;
* Justification: Mixing inline assembly with C code reduces code complexity.
*
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcall.h"
#include "Mcall_Version.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (MCALL_VENDOR_ID != RESOURCE_CFG_VENDOR_ID)
#error "Mcal.c : Mismatch in Vendor ID"
#endif /* \(MCAL_VENDOR_ID != RESOURCE_CFG_VENDOR_ID) */

#if (MCALL_AR_RELEASE_MAJOR_VERSION != RESOURCE_CFG_AR_RELEASE_MAJOR_VERSION)
#error "Mcal.c : Mismatch in Release Major Version"
#endif /* \(MCALL_AR_RELEASE_MAJOR_VERSION != RESOURCE_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (MCALL_AR_RELEASE_MINOR_VERSION != RESOURCE_CFG_AR_RELEASE_MINOR_VERSION)
#error "Mcal.c : Mismatch in Release Minor Version"
#endif /* \(MCALL_AR_RELEASE_MINOR_VERSION != RESOURCE_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (MCALL_AR_RELEASE_REVISION_VERSION != RESOURCE_CFG_AR_RELEASE_REVISION_VERSION)
#error "Mcal.c : Mismatch in Release Revision Version"
#endif /* \(MCALL_AR_RELEASE_REVISION_VERSION != RESOURCE_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (MCALL_SW_MAJOR_VERSION != RESOURCE_CFG_SW_MAJOR_VERSION)
#error "Mcal.c : Mismatch in Software Major Version"
#endif /* \(MCALL_SW_MAJOR_VERSION != RESOURCE_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (MCALL_SW_MINOR_VERSION != RESOURCE_CFG_SW_MINOR_VERSION)
#error "Mcal.c : Mismatch in Software Minor Version"
#endif /* \(MCALL_SW_MINOR_VERSION != RESOURCE_CFG_SW_MINOR_VERSION) */

#if (MCALL_SW_PATCH_VERSION != RESOURCE_CFG_SW_PATCH_VERSION)
#error "Mcal.c : Mismatch in Software Minor Version"
#endif /* \(MCALL_SW_PATCH_VERSION != RESOURCE_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)

#define MCALL_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Mcall_c_REF_1 */
#include "Mcall_MemMap.h"

/* #Violation: Mcall_c_REF_2 */
ALIGNED(64) static Mcal_LockType Mcal_Lock[MCAL_LOCK_ID_NUM];

#define MCALL_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED_NO_CACHEABLE
/* #Violation: Mcall_c_REF_1 */
#include "Mcall_MemMap.h"

#endif /* \defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412) */

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Declarations                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
#define MCALL_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Mcall_c_REF_1 */
#include "Mcall_MemMap.h"

/****************************************************************************************************
 *   Function Name           : Mcal_ReleaseLock
 *
 *   Service ID              : 0x00.
 *
 *   Description             : Release the software lock.
 *
 *   Parameters in           : LockId: Software lock ID.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Reentrant(thread-safe)
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Mcall_c_REF_5 */
FUNC(void, MCAL_PRIVATE_CODE) Mcal_ReleaseLock
(
    Mcal_LockIdType LockId
)
{
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    const Mcal_LockType *LockPtr;

    /* #Violation: Mcall_c_REF_4 */
    LockPtr = &Mcal_Lock[LockId];

    /* Release lock */
    /* #Violation: Mcall_c_REF_3 */
    ASM_VOLATILE(
                "1:ldrex r1, [%0]             \n"
                " cmp r1, #1                  \n"
#ifdef __TASKING__
                " bne 2n                      \n"
#else /* __TASKING__ */
                " bne 2f                      \n"
#endif /* __TASKING__ */
                " mov r1, #0                  \n"
                " dsb                         \n"
                " strex r2, r1, [%0]          \n"
                " dsb                         \n"
                " cmp r2, #0                  \n"
#ifdef __TASKING__
                " bne 1p                      \n"
#else /* __TASKING__ */
                " bne 1b                      \n"
#endif /* __TASKING__ */
                "2:                           \n"
                : "+r"(LockPtr)
                :
                :"cc", "memory", "r1", "r2");
#else /* \defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412) */
    MCAL_UNUSED_VAR(LockId);
#endif /* \defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412) */
}

/****************************************************************************************************
 *   Function Name           : Mcal_GetLock
 *
 *   Service ID              : 0x01.
 *
 *   Description             : Get the software lock.
 *
 *   Parameters in           : LockId: Software lock ID.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None
 *
 *   Sync/Async              : Synchronous
 *
 *   Reentrancy              : Reentrant(thread-safe)
 *
 *   Return value            : Std_ReturnType: E_OK -  success.
 *                                             E_NOT_OK -  failed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Mcall_c_REF_5 */
FUNC(Std_ReturnType, MCAL_PRIVATE_CODE) Mcal_GetLock
(
    Mcal_LockIdType LockId
)
{
    Std_ReturnType  Status;
#if defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412)
    boolean         LockFlag;
    uint32          TimeoutCnt;
    const Mcal_LockType *LockPtr;

    /* Get lock address */
    /* #Violation: Mcall_c_REF_4 */
    LockPtr = &Mcal_Lock[LockId];

    /* Check to whether the lock id out of range */
    TimeoutCnt = 0U;
    do
    {
        /* Get lock status */
        /* #Violation: Mcall_c_REF_3 */
        ASM_VOLATILE(
                    " mov r1, #1                \n" /* 1: Locked */
                    " ldrex r2, [%1]            \n" /* If is unlocked, lock it */
                    " cmp r2, r1                \n" /* Check if lock is locked */
#ifdef __TASKING__
                    " beq 1n                    \n" /* If is locked, return fail */
#else /* __TASKING__ */
                    " beq 1f                    \n" /* If is locked, return fail */
#endif /* __TASKING__ */
                    " dsb                       \n"
                    " strex r2, r1, [%1]        \n"
                    " dsb                       \n"
                    "1: eor %0, r2, #1         \n" /* Write !r2 to result. */
                    :"=&r"(LockFlag), "+r"(LockPtr)
                    :
                    :"cc", "memory", "r1", "r2");
        TimeoutCnt++;
    } while ((TimeoutCnt < MCAL_LOCK_TIMEOUT) && (FALSE == LockFlag));

    Status = (TRUE == LockFlag) ? (E_OK) : (E_NOT_OK);
#else /* \defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412) */
    MCAL_UNUSED_VAR(LockId);
    Status = E_OK;
#endif /* \defined(THA6_THA6206) || defined(THA6_THA6206D) || defined(THA6_THA6412) */

    return Status;
}

#define MCALL_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Mcall_c_REF_1 */
#include "Mcall_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
*****************************************************************************************************/

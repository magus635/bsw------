/****************************************************************************************************
*
****************************************************************************************************/

/****************************************************************************************************
*   FileName              : Os_application_types.h
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
*  V0.1.0   28-May-2024    Pony(00412)                           Add Initial Code
****************************************************************************************************/
#ifndef OS_CONTEXT_TYPES_H_
#define OS_CONTEXT_TYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Os_GeneralTypes.h"
#include "Os_context_Cfg.h"
#include "Os_mpu_types.h"
#include "Os_timingprotection_types.h"
#include "Os_isr_types.h"
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
typedef P2VAR(void, AUTOMATIC, OS_VAR) Os_ServiceCallInputType;
typedef CONSTP2CONST(Os_MpuConfigType, TYPEDEF, OS_CONST) Os_MpuConfigContextRefType;
typedef CONSTP2CONST(Os_AccessConfigType, TYPEDEF, OS_CONST) Os_AccessConfigRefType;
/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
typedef struct
{
    uint32 Spsr;                     /* CPSR_SVC */
    uint32 Icc_pmr;                  /* ICC_PMR. */
    uint32 Lr_usr;                   /* Lr_usr */
    uint32 Sp_usr;                   /* Sp_usr */
    uint32 R0;                       /* R0. */
    uint32 R4;                       /* R4. */
    uint32 R5;                       /* R5. */
    uint32 R6;                       /* R6. */
    uint32 R7 ;                      /* R7. */
    uint32 R8 ;                      /* R8. */
    uint32 R9 ;                      /* R9. */
    uint32 R10 ;                     /* R10. */
    uint32 R11;                      /* R11. */
    uint32 Lr;                       /* LR_SVC. */
} Os_Hal_ContextFrame;

typedef struct
{
    uint32 Spsr;                     /* CPSR_SVC */
    uint32 Icc_pmr;                  /* ICC_PMR. */
    uint32 Lr_usr;                   /* Lr_usr */
    uint32 Sp_usr;                   /* Sp_usr */
    Os_ServiceCallInputType R0;                       /* R0. */
    Os_ServiceCallInputType R1;                       /* R1. */
    Os_ServiceCallInputType R2;                       /* R2. */
    Os_ServiceCallInputType R3;                       /* R3. */
    uint32 R4;                       /* R4. */
    uint32 R5;                       /* R5. */
    uint32 Lr;                       /* LR_SVC. */
    uint32 ReturnVal;
    Os_ServiceType ServiceId;
    uint32 ServiceType;
} Os_Hal_ServiceContextFrame;

typedef struct
{
    uint64 FpuRegisters[FPU_DREGS_NUM];
    uint32 Fpscr;
    uint32 Fpexc;
} Os_Hal_FpuContextType;

typedef struct
{
    Os_IsrRunningDataType IsrRunningData;
} Os_Hal_ContextRunningDataType;

typedef struct 
{
      /*  */
    uint32 StackTopAddr;
    /*  */
    uint32 StackBottomAddr;
      /*  */
    uint32 EntryFunction;
      /*  */
    uint32 ReturnFunction;
      /*  */
    uint32 ProgramSetting;
      /*  */
    uint32 InterruptSetting;
      /*  */
    P2VAR(Os_Hal_ContextFrame, TYPEDEF, OS_VAR) ContextInfoPtr;
      /*  */
    P2VAR(Os_MpuConfigContextRefType, TYPEDEF, OS_VAR) MpuInfoPtr;

    P2VAR(Os_AccessConfigRefType, TYPEDEF, OS_VAR) AccessCheckInfoPtr;

    P2CONST(Os_TpObjectConfigTypeRef, TYPEDEF, OS_CONST) TpInfoPtr;

    P2VAR(Os_Hal_ContextRunningDataType, TYPEDEF, OS_VAR) ContextRunningDataPtr;
}Os_ContextType;

typedef struct 
{
    /* */
    P2CONST(Os_ContextType, TYPEDEF, OS_CONST) ContextConfigPtr[TOTALNUM_OF_CONTEXT + 1];
    /*   */

}Os_ContextConfigType;

#endif /* OS_APPLICATION_TYPES_H_ */

/****************************************************************************************************
**     End of File: Os_application_types.h                                                         **
****************************************************************************************************/


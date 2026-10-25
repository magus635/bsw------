/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all type definitions of DFlash Driver
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
*#Fls_GeneralTypes_h_REF_1:CertC-DCL12-C;
* Justification:Apply such struct/union definitons to simplify the code structure and 
* reduce the code complexity;
*#Fls_GeneralTypes_h_REF_2:MISRAC2012-Dir-4.8; 
* Justification:Apply such struct/union definitons to simplify the code structure and reduce the 
*   code complexity.
*
*/

#ifndef FLS_GENERALTYPES_H_
#define FLS_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcall.h"
#include "Fls_Cfg.h"
#include "dflash_hal.h"
#include "pflash_hal.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* Used as address offset from the configured flash base address. [SWS_Fls_00369], [SWS_Fls_00216] */
typedef uint32 Fls_AddressType;

/* Specifies the number of bytes to read/write/erase/compare. [SWS_Fls_00370] */
typedef uint32 Fls_LengthType;

/* Function pointer for JobEnd and JobError Notification */
/* The callback notifications shall have no parameters and no return value.[SWS_Fls_00110] */
typedef void (*Fls_NotifFunctionPtrType)(void);

/****************************************************************************************************
**                          Global Enumration Definitions                                          **
****************************************************************************************************/
/* Options of FlsJobType */
typedef enum
{
    /* Fls not initialized */
    FLS_JOB_UNINIT = 0U,
    /* Fls in Idle */
    FLS_JOB_NONE,
    /* Fls is performing asynchronous write operation */
    FLS_JOB_WRITE,
    /* Fls is performing asynchronous erase operation */
    FLS_JOB_ERASE,
    /* Fls is performing asynchronous read operation */
    FLS_JOB_READ,
    /* Fls is performing asynchronous compare operation */
    FLS_JOB_COMPARE,
    /* Fls is performing asynchronous blankcheck operation */
    FLS_JOB_BLANKCHECK,
    /* Fls is performing synchronous read operation */
    FLS_JOB_READSYNC,
    /* Fls is performing synchronous cancel operation */
    FLS_JOB_CANCEL,
    /* Fls is performing synchronous compare operation */
    FLS_JOB_COMPARESYNC,
    /* Fls is performing synchronous blankcheck operation */
    FLS_JOB_BLANKCHECKSYNC
} Fls_JobType;

/* Enumeration to represent the type of flash memory region */
typedef enum
{
    FLS_DFLASH_REGION = 0U,             /* DFlash */
    FLS_PFLASH_REGION = 1U,             /* PFlash */
} Fls_OptFlashType;
/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/

typedef struct
{
    boolean Write;                              /* The write job has been started */
    boolean Erase;                              /* The erase job has been started */
} Fls_JobStartType;

/* Includes module status, mode, and job results for easy debugging. */
typedef struct
{
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
    uint64              TimeoutCount;           /* Timeout count */
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
    uint32              JobAddress;             /* Source Address for user job */
    Fls_LengthType      JobLength;              /* Number of bytes for user job */
    uint8 *             ReadBufferPtr;          /* Destination pointer for read/compare job */
    const uint8 *       CompareBufferPtr;       /* Source pointer for compare job */
    const uint8 *       WriteBufferPtr;         /* Destination pointer for write job */
    Fls_JobType         JobType;                /* current job type*/
    MemIf_JobResultType JobResult;              /* store Job Result of the Flash */
    MemIf_ModeType      Mode;                   /* FLS current mode */
    Fls_JobStartType    JobStarted;             /* Status to indicate if the job has been started */
    Fls_LengthType      CurVerifyLen;           /* Length for erase or write verification */
#if (FLS_USE_INTERRUPTS == STD_ON)
    boolean             EraseFinish;            /* Erase operation finished in interrupt mode */
    boolean             WriteFinish;            /* Write operation finished in interrupt mode */
    uint8               JobCanceling;           /* Cancel operation flag */
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
    Fls_OptFlashType    CurFlashType;
} Fls_StateType;

/* The configuration of the Fls sectors config set */
/* #Violation: Fls_GeneralTypes_h_REF_2 */
typedef struct
{
    uint32 FlsSectorStartAddress;         /* Number of FLS sectors in the config set */
    uint32 FlsSectorSize;        /* Size of a page in bytes */
    uint32 FlsSectorPageSize;              /* Size of a sector in bytes */
    uint32 FlsSectorEndAddress;      /* Start address of the config set */
}Fls_SectorConfigType;

/* The configuration of the driver and flash memory hardware. [SWS_Fls_00368] */
/* #Violation: Fls_GeneralTypes_h_REF_1 */
typedef struct
{
    uint16                   FlsFastRead;    /* Max read length in one cycle of FLS in fast mode */
    uint16                   FlsSlowRead;    /* Max read length in one cycle of FLS in slow mode */
    uint16                   FlsFastWrite;   /* Max write length in one cycle of FLS in fast mode */
    uint16                   FlsSlowWrite;   /* Max write length in one cycle of FLS in slow mode */
    /* The job processing callback notifications shall be configurable as function pointers */
    /* within the initialization data structure (Fls_ConfigType). [SWS_Fls_00109] */
    Fls_NotifFunctionPtrType FlsJobEndNotificationPtr;
    Fls_NotifFunctionPtrType FlsJobErrorNotificationPtr;
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
    /* Cycle time of calls of the flash driver's main function */
    uint32                   FlsCallCycle;
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
    MemIf_ModeType           FlsDefaultMode;        /* Default mode */
    const Fls_SectorConfigType * const FlsSectorConfigPtr; /* Pointer to the sector configuration */
    uint16                   FlsNumberOfSectors;    /* Number of FLS sectors in the config set */
} Fls_ConfigType;

/* Hardware or implementation specific parameters can be added if necessary. [SWS_Fls_00355] */

#endif /* FLS_GENERALTYPES_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


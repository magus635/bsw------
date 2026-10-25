/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fee_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all type definitions of FEE module
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
*#Fee_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Redundant of struct or union type has no affect to driver operation.
*
*#Fee_GeneralTypes_h_REF_2:MISRAC2012-Rule-19.2;
* Justification: Necessary union type for share buffer. Data integrity and correctness will be ensured
* by code review.
*/

#ifndef FEE_GENERALTYPES_H_
#define FEE_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Fee_Cfg.h"
#include "Std_Types.h"
#include "Platform_Types.h"

/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* Function pointer for JobEnd and JobError Notification  */
typedef void (*Fee_NotificationPtrType)(void);

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
/* Pending request types */
typedef enum
{
    /* IDLE */
    FEE_PEND_NO_REQ = 0U,
    /* Read request suspended */
    FEE_READ_REQ,
    /* Write request suspended */
    FEE_WRITE_REQ
} Fee_PendRequestStatusType;

/* Garbage Collection Status */
typedef enum
{
    /* GC Idle */
    FEE_GC_IDLE = 0U,
    /* In GC */
    FEE_GC_REQUESTED,
    /* GC Fail */
    FEE_GC_FAIL,
    /* GC: Write Valid Bank information complete.
           Start erase old Bank */
    FEE_GC_ERASE_PREV_BANK,
    /* GC: The block is too large to be read by one main function
           or the block is stored in two sectors */
    FEE_GC_COPY_READ_NXTPAGE,
    /* GC: Start copy Block to new Bank */
    FEE_GC_COPY_WRITE,
    /* GC: Block copy complete.
           Write Valid Bank information data in the new bank */
    FEE_GC_MARK_BANK_NEW_V_SP,
    /* GC: Write Valid Bank information data complete.
           Write Valid Bank information Marker in the new bank */
    FEE_GC_MARK_BANK_NEW_V_M,
    /* GC: Erase old Bank complete.
           Write Erase Bank information data in the old bank */
    FEE_GC_MARK_BANK_OLD_E_SP,
    /* GC: Write Erase Bank information data complete.
           Write Erase Bank information Marker in the old bank */
    FEE_GC_MARK_BANK_OLD_E_M
} Fee_GcStatusType;

/* Fee Main Function States */
typedef enum
{
    /* In Idle state */
    FEE_MAIN_NONE,
    /* In init GC state */
    FEE_MAIN_INITGC,
    /* In GC state */
    FEE_MAIN_GC,
    /* In Read state */
    FEE_MAIN_READ,
    /* In Write state */
    FEE_MAIN_WRITE
} Fee_MainJobType;

/* Job states */
typedef enum
{
    /* Idle */
    FEE_JOB_IDLE = 0U,
    /* Job processing in progress */
    FEE_JOB_REQSTD,
    /* Job processing completes */
    FEE_JOB_DONE,
    /* Job processing completes but error */
    FEE_JOB_FAILED
} Fee_JobStateType;

/* Error events during User/Internal operations */
typedef enum
{
    /* No Error  */
    FEE_NO_ERROR = 0U,
    /* GC Error: Write */
    FEE_GC_WRITE,
    /* GC Error: Read */
    FEE_GC_READ,
    /* GC Error: Erase */
    FEE_GC_ERASE,
    /* GC Error: FLS don't accept the request */
    FEE_GC_FLS,
    /* GC Error: GC operation triggers the another GC operation */
    FEE_GC_TRIG,
} Fee_JobErrorType;

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* #Violation: Fee_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Block information collection */
    /* the block meta information shall be made available for debugging. Refer to [SWS_Fee_00130] */
    boolean Valid;
    boolean Consistent;
    boolean Copied;
    uint16  BlockNumber;
    uint16  PageCount;
    uint32  Address;
    uint32  BlockCycleCount;
} Fee_BlockInfoType;

typedef struct
{
    uint16 Tag;
    /* first byte is unerasable sector count for erase sate page and reserved for valid sate page */
    /* second byte count reverse for erase sate page and sate count for valid sate page */
    uint8  BadSectorNum;
    uint8  Reserved[FEE_VIRTUAL_PAGE_SIZE - 4U];
    uint8  TailTag;
} Fee_ErasePageHeaderType;

typedef struct
{
    uint16 Tag;
    /* first byte is unerasable sector count for erase sate page and reserved for valid sate page */
    /* second byte count reverse for erase sate page and sate count for valid sate page */
    uint8  Reserved_0;
    uint8  StateCount;
    uint32 GcNumber;
    uint8  Reserved_1[FEE_VIRTUAL_PAGE_SIZE - 9U];
    uint8  TailTag;
} Fee_ValidPageHeaderType;

typedef struct
{
    uint8   Tag;
    uint8   BlockNumber[2];
    uint8   BlockCycleCount[3];
    /* Pages count use the lower 15 bit and valid use the 16th bit. */
    uint16  PagesAndValid;
} Fee_BlockHeaderType;

typedef struct
{
    uint16 Tag;
    uint16 PageCount;
    uint16 PageCountRev;
    uint8  Reserved[FEE_VIRTUAL_PAGE_SIZE - 8U];
    uint16 TailTag;
} Fee_BlockMarkerType;

/* recode the next reading when the read cross bad sector */
typedef struct
{
    uint32  Remain;
    uint8  *ResumeBufferPtr;
    uint32  ResumeSrcAddr;
} Fee_StatusSkipReadType;

/* DFLASH bank info */
/* #Violation: Fee_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Address of the next free WordLine  */
    uint32 NextFreeAddr;
    /* Un-erasable sector address's count */
    uint8  UnerasableCount;
    /* Unerasable sector number for bank0 & bank1 */
#if (FEE_MAX_BADSECTOR_COUNT > 0U)
    uint8  UnerasableSectorNum[FEE_MAX_BADSECTOR_COUNT];
#endif /* (STD_ON \== FEE_SOFTWARE_VERIFY) */
    /* Valid / Erased / Stateless */
    uint8  State;
    /* valid state page count */
    uint8  StateCount;
    /* gc Number */
    uint32 GcNumber;
} Fee_BankInfoType;

/* pending request */
typedef struct
{
    /* the status of the pending request */
    Fee_PendRequestStatusType PendReqStatus;
    /* the pending status of the set mode request */
    boolean                   FeeSetModeReqPend;
    /* the mode will be set to Fls by the set mode request */
    MemIf_ModeType            Mode;
    /* Invalidate request */
    boolean                   BlockInvalidReq;
    /* request a write during GC */
    boolean                   WaitGc;
    /* Record user read buffer pointer */
    uint8                    *ReadDataBufferPtr;
    /* Record user write buffer pointer */
    const uint8              *WriteDataBufferPtr;
    /* Record the block number requested by the user */
    uint16                    BlockNumber;
    /* Record the array Index of Block number in static configuration */
    uint16                    BlockIndex;
    /* Record the block offset requested by the user */
    uint16                    BlockOffset;
    /* Record the Length requested by the user */
    uint32                    CurrBankSrcAddr;
    /* read length */
    uint16                    Length;
    /* Last write size */
    uint16                    LastWriteSize;
    /* Last read size */
    uint16                    LastReadSize;
    /* number of DFlash pages read/written */
    uint16                    BlockPageCount;
    /* Totol number of DFlash pages of block */
    uint16                    BlockPages;
    /* the number of user data bytes written */
    uint16                    UserWriteBytesCount;
    /* the job result of the ongoing/finished job, it can be get by Fee_GetJobResult */
    MemIf_JobResultType       JobResult;
    /* the job is fail but the error need report at next mainFunction call to conform the Autosar */
    MemIf_JobResultType       JobResultPending;
    /* Fls Job Status */
    Fee_JobStateType          FlsJobStatus;
} Fee_UserJobInfoType;

/* Fee state */
typedef struct
{
    /* the state of GC */
    Fee_GcStatusType GcState;
    /* Target Addr from which data needs to be copied during GC */
    uint32           GcDestAddr;
    /* Source Addr from which data needs to be copied during GC */
    uint32           GcSrcAddr;
    /* the Index of logical blocks during GC */
    sint16           GCCopyIndex;
    /* Current Block size being written during GC */
    uint16           GcCurrBlockPageCount;
    /* Last write size */
    uint16           LastWriteSize;
    /* Last read size */
    uint16           LastReadSize;
    /* number of DFlash pages read/written */
    uint16           BlockPageCount;
    /* indicate if the block contents were modified during GC */
    boolean          BlockModified;
    /* Fls Job Status */
    Fee_JobStateType FlsJobStatus;
} Fee_GcJobInfoType;

/* Fee state */
typedef struct
{
    /* the current bank */
    uint8              CurrBank;
    /* FeeIntrJobFailCount: Stores the number of times the
     comparison during GC failed   */
    uint8              IntrJobFailCount;
    /* if the write API is called */
    boolean            FeeWriteAPICalled;
    /* the current Main Job */
    Fee_MainJobType    MainJob;
    /* Store information for two banks */
    Fee_BankInfoType  *BankInfoPtr;
    /* Block information */
    Fee_BlockInfoType *BlockInfoPtr;
    /* Stores the status whether the number of un-configured blocks exceeded the configured limit */
    uint8              UncfgBlksExceeded;
    /* Number of un-configured blocks in cache table */
    uint16             UnConfigBlockCount;
    /* the next available DFlash address */
    uint32             NextFreePageAddr;
} Fee_StateDataType;

/* Fee block configuration information */
/* #Violation: Fee_GeneralTypes_h_REF_1 */
typedef struct
{
    /* Number of write cycles for each logical block. [SWS_Fee_00102] */
    uint32  NumberOfWriteCycles;
    /* Fee block number */
    uint16  BlockNumber;
    /* Size of Fee block in bytes */
    uint16  BlockSize;
    /* TRUE if it is an immediate data block */
    boolean ImmediateData;
} Fee_BlockConfigType;

/* Refer to \[SWS_Fee_00188] */
typedef struct
{
    /* Derived Config parameter : No. of configured blocks */
    uint16                     FeeBlkCnt;
    /* Pointer to logical block configurations */
    const Fee_BlockConfigType *FeeBlockConfigPtr;
    Fee_NotificationPtrType    FeeJobEndNotificationPtr;
    Fee_NotificationPtrType    FeeJobErrorNotificationPtr;
    Fee_NotificationPtrType    FeeUnavailableFailureNotificationPtr;
    Fee_NotificationPtrType    FeeDiscoverNonErasableAreasNotificationPtr;
    Fee_NotificationPtrType    FeeNotFoundManagementInfoNotificationPtr;
} Fee_ConfigType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/
/* #Violation: Fee_GeneralTypes_h_REF_2 */
typedef union
{
    uint32 Buffer[FEE_VIRTUAL_PAGE_SIZE >> 2U];           /* Unsigned access */
    Fee_ValidPageHeaderType ValidHeader;
    Fee_BlockHeaderType BlockHeader;
} Fee_BufferUnionType;

#endif /* FEE_GENERALTYPES_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

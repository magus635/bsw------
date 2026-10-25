/****************************************************************************************************
 *
 ****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Fee.c
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : DFlash
 *
 *   brief                 : This file contains all functions of FEE module
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
*#Fee_c_REF_1:MISRAC2012-Rule-8.9;
* Justification:The value should be placed in the const data sections to reduce code complexity 
* and stack size.
*
*#Fee_c_REF_2:MISRAC2012-Dir-4.9;
* Justification: Function like macros are used to reduce code complexity.
*
*#Fee_c_REF_3:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*#Fee_c_REF_4:MISRAC2012-Rule-2.2;
* Justification: Platform-based design with configurable macros.
*
*#Fee_c_REF_5:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Fee_c_REF_6:MISRAC2012-Rule-11.4;
Justification:Casting pointer to an integeral type to obtain its address.
*
*#Fee_c_REF_7:MISRAC2012-Rule-11.3;
* Justification:Casting Ram address; Address is verified to be 32bit aligned before casting.
*
*#Fee_c_REF_8:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts 
* of the driver must be placed.
*
*#Fee_c_REF_9:CertC-PRE00-C;
* Justification: Function like macros are used to reduce code complexity.
*
*#Fee_c_REF_10:CWE-1071;
* Justification: MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block.
*
*#Fee_c_REF_11:MISRAC2012-Rule-11.3;
* Justification:Converting integers to object pointers to reduce targeted RAM/FLASH memory
* address data access complexity.
*/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Fee.h"
#include "Det.h"
#include "Fee_Cfg.h"
#include "Fee_GeneralTypes.h"
#include "Fee_Version.h"
#include "Fls.h"
#include "Fls_Cfg.h"
#include "MemIf_Types.h"
#include "Platform_Types.h"
#include "Std_Types.h"
#if (FEE_DEM_ENABLED == STD_ON)
/* DEM header file */
#include "Dem.h"
#endif

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (FEE_VENDOR_ID != FEE_CFG_VENDOR_ID)
#error "Fee.c : Mismatch in Vendor ID"
#endif /* (FEE_VENDOR_ID \!= FEE_CFG_VENDOR_ID) */

#if (FEE_MODULE_ID != FEE_CFG_MODULE_ID)
#error "Fee.c : Mismatch in Module ID"
#endif /* \(FEE_MODULE_ID != FEE_CFG_MODULE_ID) */

#if (FEE_AR_RELEASE_MAJOR_VERSION != FEE_CFG_AR_RELEASE_MAJOR_VERSION)
#error "Fee.c : Mismatch in Release Major Version"
#endif /* (FEE_AR_RELEASE_MAJOR_VERSION \!= FEE_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (FEE_AR_RELEASE_MINOR_VERSION != FEE_CFG_AR_RELEASE_MINOR_VERSION)
#error "Fee.c : Mismatch in Release Minor Version"
#endif /* (FEE_AR_RELEASE_MINOR_VERSION \!= FEE_CFG_AR_RELEASE_MINOR_VERSION) */

#if (FEE_AR_RELEASE_REVISION_VERSION != FEE_CFG_AR_RELEASE_REVISION_VERSION)
#error "Fee.c : Mismatch in Release Revision Version"
#endif /* (FEE_AR_RELEASE_REVISION_VERSION \!= FEE_CFG_AR_RELEASE_REVISION_VERSION) */

#if (FEE_SW_MAJOR_VERSION != FEE_CFG_SW_MAJOR_VERSION)
#error "Fee.c : Mismatch in Software Major Version"
#endif /* (FEE_SW_MAJOR_VERSION \!= FEE_CFG_SW_MAJOR_VERSION) */

#if (FEE_SW_MINOR_VERSION != FEE_CFG_SW_MINOR_VERSION)
#error "Fee.c : Mismatch in Software Minor Version"
#endif /* (FEE_SW_MINOR_VERSION \!= FEE_CFG_SW_MINOR_VERSION) */

#if (FEE_SW_PATCH_VERSION != FEE_CFG_SW_PATCH_VERSION)
  #error "Fee.c : Mismatch in Software Patch Version"
#endif /* (FEE_SW_PATCH_VERSION \!= FEE_CFG_SW_PATCH_VERSION) */
/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* There is no Fee management information in the bank */
#define FEE_STATELESS                         (0U)
/* The bank is in Valid state(has Valid Bank Info) */
#define FEE_VALID                             (1U)
/* The bank is in Erase state(has Erase Bank Info) */
#define FEE_ERASED                            (2U)
/* The bank is in Erase state(has Erase Bank Info, and No other information available) */
#define FEE_ERASED_NOT_USED                   (4U)
/* The bank is in Erase state(has Erase Bank Info, and There may be other information indicating that
   GC has been interrupted) */
#define FEE_ERASED_USED                       (8U)
/* The FLS error that FEE can't deal with */
#define FEE_FLS_ERROR                         (16U)

/* Bank state Marker size */
#define FEE_STATEPAGE_MARKER_SIZE             (FEE_DFLASH_PAGE_SIZE)
/* Bank state Header + Data size */
#define FEE_STATEPAGE_HEADER_DATA_SIZE        (FEE_DFLASH_PAGE_SIZE)
/* Bank State Page Identifier */
#define FEE_STATEPAGE_ERASE_HEADER            (0x45A7U)
#define FEE_STATEPAGE_VALID_HEADER            (0x56A7U)
#define FEE_STATEPAGE_DATA_TAG                (0xA5U)
#define FEE_STATEPAGE_BAD_TAG                 (0xAAU)
#define FEE_STATEPAGE_MARKER_TAG              (0x5A5A5A5AU)
#define FEE_UNERASABLE_SECTOR_OFFSET          (24U)
#define FEE_STATEPAGE_NUMBER                  (0U)
/* The size of unerasable sector info */
#define FEE_UNERASABLE_INFO_SIZE              (4U)
/* The number of non erasable Sector numbers stored on a page.(4byte for one sector) */
#define FEE_MAX_UNERASABLE_INFO_IN_PAGE       (FEE_DFLASH_PAGE_SIZE / FEE_UNERASABLE_INFO_SIZE)

/* Fee Block header size in byte */
#define FEE_BLOCK_HEADER_SIZE                 (8U)
/* The page size occupied by Fee invalid block */
#define FEE_INVALIDBLOCK_PAGE_SIZE            (2U)
/* Fee header size */
#define FEE_BLOCK_HEADER_DATA_SIZE            (8U)
/* logical block Identifier */
#define FEE_BLOCK_HEADER_TAG                  (0xA3U)
#define FEE_BLOCK_DATA_TAG                    (0xA1U)
#define FEE_BLOCK_MARKER_TAG                  (0x5555U)
/* The index value returned when the index corresponding to the block is not found. */
#define FEE_LOG_BLOCK_NOT_FOUND               (0xFFFFU)
/* Use this value to the verify block pagecount */
#define FEE_PAGECOUNT_VERIFY                  (0xFFFFU)

/* The contents of an erased flash memory cell. */
#define FEE_ERASE_VALUE                       (FLS_ERASE_VALUE)
/* The size in bytes to which logical blocks shall be aligned. refer to [SWS_Fee_00076] */
#define FEE_DFLASH_PAGE_SIZE                  (FEE_VIRTUAL_PAGE_SIZE)
/* how many user data bytes in one page */
#define FEE_USER_PAGE_BYTE_COUNT              ((FEE_DFLASH_PAGE_SIZE - FEE_PAGE_OVERHEAD))
/* The amount of shift between word and byte conversion */
#define FEE_WORD_TO_BYTE_SHIFT                (2U)
/* Fee virtual wordline size. */
#define FEE_DFLASH_WORDLINE_SIZE              (256U)
/* Fee virtual sector size. */
#define FEE_DFLASH_SECTOR_SIZE                (FEE_SECTOR_SIZE)
/* The mask to get the lower byte. */
#define FEE_GET_LOW_BYTE                      (0x00FFU)

#define FEE_PAGE_COUNT_MASK                   (0x7FFFU)
#define FEE_VALID_MASK                        (0x8000U)
#define FEE_VALID_BIT                         (0x8000U)
#define FEE_MAX_RETRY_TIMES                   (2U)
#define FEE_ONE_BYTE_SHIFT                    (8U)
#define FEE_TWO_BYTE_SHIFT                    (16U)

/* Fee bank size and address */
#define FEE_DFLASH_BANK_NUM                   (2U)
#define FEE_DFLASH_BANK_SECTOR_NUM            (FEE_SECTOR_NUMBER >> 1U)
#define FEE_DFLASH_BANK_SIZE                  (FEE_DFLASH_SIZE >> 1U)
#define FEE_DFLASH_BANK0_BASE                 (0U)
#define FEE_DFLASH_BANK1_BASE                 (FEE_DFLASH_BANK_SIZE)

/* Get the smaller number from the two number. */
/* #Violation: Fee_c_REF_2 */
#define FEE_MIN(Number1, Number2) (((Number1) < (Number2)) ? (Number1) : (Number2))

/* Gets the offset of a sector. */
/* #Violation: Fee_c_REF_2 */
/* #Violation: Fee_c_REF_9 */
#define FEE_OFFSETOFSECTOR(Address) \
    ((Address) & (FEE_DFLASH_SECTOR_SIZE - 1U))

/* Calculates the start wordline address of Address. */
/* #Violation: Fee_c_REF_2 */
/* #Violation: Fee_c_REF_9 */
#define FEE_GETWLBEGINNING(Address) \
    ((Address) & (~(FEE_DFLASH_WORDLINE_SIZE - 1U)))

/* Calculates the start sector address of Address. */
/* #Violation: Fee_c_REF_2 */
/* #Violation: Fee_c_REF_9 */
#define FEE_GETSECTORBEGINNING(Address) \
    ((Address) & (~(FEE_DFLASH_SECTOR_SIZE - 1U)))

/* Gets the offset of a wordline. */
/* #Violation: Fee_c_REF_2 */
/* #Violation: Fee_c_REF_9 */
#define FEE_OFFSETOFWL(Address) \
    ((Address) & (FEE_DFLASH_WORDLINE_SIZE - 1U))

/* Return the sector number for the given address. */
/* #Violation: Fee_c_REF_9 */
#define FEE_ADDRTOSECTORNUMBER(Address) \
    (uint8)((Address) >> FEE_SECTOR_TO_BYTE_SHIFT)

/* Calculate the real address from the given virtual address. */
/* #Violation: Fee_c_REF_9 */
#define FEE_MAPADDR(Address) \
    (Fls_AddressType)(((uint32)Fee_SectorReMap[FEE_ADDRTOSECTORNUMBER(Address)] << FEE_SECTOR_TO_BYTE_SHIFT) + FEE_OFFSETOFSECTOR(Address) + FEE_STARTADDRESS)

/* Calculate the real address from the given virtual address when init and erase pre bank. */
/* #Violation: Fee_c_REF_9 */
#define FEE_REALADDR(Address) \
    (Fls_AddressType)((Address) + FEE_STARTADDRESS)

/* Return the real page size of block exclude the marker */
/* #Violation: Fee_c_REF_9 */
#define FEE_CALPAGES(Size) \
    (uint16)((((uint32)(Size) + FEE_BLOCK_HEADER_DATA_SIZE - 2U) / FEE_USER_PAGE_BYTE_COUNT) + 1U)

/* Return the free page size of the bank */
/* #Violation: Fee_c_REF_9 */
#define FEE_GETREMAINPAGES(BankNumber, StartAddr) \
    (uint16)(((FEE_DFLASH_BANK_SIZE << (BankNumber)) - (StartAddr) - ((uint32)Fee_State.BankInfoPtr[BankNumber].UnerasableCount * FEE_SECTOR_SIZE)) >> FEE_PAGE_TO_BYTE_SHIFT);

#if (FEE_DEV_ERROR_DETECT == STD_ON)
/* #Violation: Fee_c_REF_9 */
#define FEE_REPORTERROR(ApiId, ErrorId) \
    (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId, ErrorId)
#else /* FEE_DEV_ERROR_DETECT \== STD_ON */
#define FEE_REPORTERROR(ApiId, ErrorId)
#endif /* FEE_DEV_ERROR_DETECT \== STD_ON */

/* #Violation: Fee_c_REF_9 */
#define FEE_REPORTRUNTIMEERROR(ApiId, ErrorId) \
    (void)Det_ReportRuntimeError(FEE_MODULE_ID, FEE_INSTANCE_ID, ApiId, ErrorId)

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#if (0U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FEE_CORE_ALLOCATION) */
#include "Fee_MemMap.h"

static P2CONST(Fee_ConfigType, AUTOMATIC, FEE_APPL_CONST) Fee_ConfigPtr;

/* Store all gc information of Fee */
static Fee_GcJobInfoType Fee_GcJobInfo;

/* Store all user job information of Fee */
static Fee_UserJobInfoType Fee_UserJobInfo;

/* Store fee two bank info */
/* #Violation: Fee_c_REF_1 */
static Fee_BankInfoType Fee_BankInfo[FEE_DFLASH_BANK_NUM];

/* Store all status management information of Fee */
static Fee_StateDataType Fee_State;

/* Store all block info */
static Fee_BlockInfoType Fee_BlockInfos[FEE_DFLASH_BANK_NUM][FEE_MAX_BLOCK_COUNT];

/* Store the skip read state of fee */
static Fee_StatusSkipReadType Fee_SkipReadStatus;

/* A buffer for temporarily storing data */
ALIGNED(64) static uint8 Fee_RWBuffer[FEE_DFLASH_WORDLINE_SIZE];

#if (0U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FEE_CORE_ALLOCATION) */
/* #Violation: Fee_c_REF_8 */
#include "Fee_MemMap.h"

#if (0U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE0_8
#elif (1U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE1_8
#elif (2U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE2_8
#elif (3U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_VAR_CLEARED_ASIL_D_CORE3_8
#endif /* (CoreID \== FEE_CORE_ALLOCATION) */
/* #Violation: Fee_c_REF_8 */
#include "Fee_MemMap.h"
/* Unerasable sector number for bank0 & bank1 */
static uint8 Fee_SectorReMap[FEE_SECTOR_NUMBER];

/* Fee init Flag */
static MemIf_StatusType Fee_Init_Status;

#if (0U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_8
#elif (1U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_8
#elif (2U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_8
#elif (3U == FEE_CORE_ALLOCATION)
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_8
#endif /* (CoreID \== FEE_CORE_ALLOCATION) */
/* #Violation: Fee_c_REF_8 */
#include "Fee_MemMap.h"

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
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fee_c_REF_8 */
#include "Fee_MemMap.h"
static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalMakeBlockMarker
(
    Fee_BlockMarkerType *const BlockMarkerPtr,
    uint16 PageCount
);

static FUNC(uint16, FEE_PRIVATE_CODE) Fee_LocalGetUsrBlockIndex
(
    uint16 BlockNumber
);

static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalHandleUsrJobEnd
(
    MemIf_JobResultType Error
);

static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalDecideMainJob
(
    void
);

static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalSetInitGc
(
    void
);

static FUNC(uint8, FEE_PRIVATE_CODE) Fee_LocalCheckEraseStatePage
(
    uint32 CurrBankSrcAddr
);

static FUNC(uint8, FEE_PRIVATE_CODE) Fee_LocalTraversalUpdateBlockInfo
(
    uint8 BankNumber
);

static FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_LocalUpdateBlockInfo
(
    uint32 *const CurrBankAddr,
    CONSTP2CONST(Fee_BlockHeaderType, AUTOMATIC, FEE_APPL_CONST) BlockHeaderPtr
);

static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalHandleUserWriteReq
(
    uint16 BlockIndex,
    CONSTP2CONST(uint8, AUTOMATIC, FEE_APPL_CONST) DataBufferPtr
);

static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalWrite
(
    void
);

static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalRead
(
    void
);

static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcRead
(
    Fls_AddressType SrcAddr
);

static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcWrite
(
    Fls_AddressType DestAddr,
    uint16 Size
);

static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcRequested
(
    void
);

static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcStartCopy
(
    void
);

static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcStartCopyWrite
(
    void
);

static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcErasePrevBank
(
    void
);

static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcStatePageCompare
(
    Fee_GcStatusType GcState
);

static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcProgramStatePage
(
    Fee_GcStatusType GcState
);

static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalGC
(
    void
);

#if (STD_ON == FEE_DEV_ERROR_DETECT)
static FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_LocalCommonDetCheck
(
    uint8 ServiceID
);
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */

static FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_LocalSkipRead
(
    uint32 SrcAddr,
    uint32 ReadLength
);

static FUNC(MemIf_StatusType, FEE_PRIVATE_CODE) Fee_LocalGetStatus
(
    void
);
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fee_c_REF_8 */
#include "Fee_MemMap.h"

/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/

/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fee_c_REF_8 */
#include "Fee_MemMap.h"
/****************************************************************************************************
 *   Function Name           : Fee_LocalMakeBlockMarker
 *
 *   Service ID              : None.
 *
 *   Description             : This function fills Fee_RWBuffer with state page data.
 *
 *   Parameters in           : BlockMarkerPtr: Point to BlockMarker.
 *                             PageCount: The block page count.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalMakeBlockMarker
(
    Fee_BlockMarkerType *const BlockMarkerPtr,
    uint16 PageCount
)
{
    uint16 Count;

    BlockMarkerPtr->Tag = FEE_BLOCK_MARKER_TAG;
    BlockMarkerPtr->PageCount = PageCount;
    BlockMarkerPtr->PageCountRev = FEE_PAGECOUNT_VERIFY - PageCount;
    for (Count = 0U; Count < (FEE_VIRTUAL_PAGE_SIZE - FEE_BLOCK_HEADER_DATA_SIZE); Count++)
    {
        BlockMarkerPtr->Reserved[Count] = 0U;
    }
    BlockMarkerPtr->TailTag = FEE_BLOCK_MARKER_TAG;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGetUsrBlockIndex
 *
 *   Service ID              : None.
 *
 *   Description             : This function gets the Index of the block in the user configuration.
 *
 *   Parameters in           : BlockNumber: Number of logical block.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : The block index in the user configuration.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(uint16, FEE_PRIVATE_CODE) Fee_LocalGetUsrBlockIndex
(
    uint16 BlockNumber
)
{
    const Fee_BlockConfigType *BlockPtr;
    uint16                     Index;

    Index = 0U;
    BlockPtr = &(Fee_ConfigPtr->FeeBlockConfigPtr[0]);
    /* no restrict on BlockNumber's order, so we use index++ to search here */
    while ((Index < Fee_ConfigPtr->FeeBlkCnt) && (BlockPtr->BlockNumber != BlockNumber))
    {
        Index++;
        BlockPtr++;
    }

    /* if block is not configured, return invalid block index */
    if (Index >= Fee_ConfigPtr->FeeBlkCnt)
    {
        Index = FEE_LOG_BLOCK_NOT_FOUND;
    }

    return Index;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalHandleUsrJobEnd
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles the user job failure.
 *
 *   Parameters in           : Error: Type of user job failure.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalHandleUsrJobEnd
(
    MemIf_JobResultType Error
)
{
    Fee_NotificationPtrType NotificationPtr;

    /* Return MEMIF_JOB_FAILED if the last job has failed. [SWS_Fee_00158], [SWS_Fee_00155] */
    Fee_UserJobInfo.PendReqStatus = FEE_PEND_NO_REQ;
    Fee_UserJobInfo.FlsJobStatus = FEE_JOB_IDLE;
    if (Fee_State.MainJob >= FEE_MAIN_READ)
    {
        Fee_State.MainJob = FEE_MAIN_NONE;
    }

    /* If job result is MEMIF_JOB_PENDING, shall set the job result to MEMIF_JOB_FAILED, */
    /* else it shall leave the job result untouched. [SWS_Fee_00143] */
    if (MEMIF_JOB_PENDING == Fee_UserJobInfo.JobResult)
    {
        /* Set the job result to MEMIF_JOB_OK. [SWS_Fee_00035], [SWS_Fee_00155] */
        Fee_UserJobInfo.JobResult = Error;
    }
    NotificationPtr = (MEMIF_JOB_OK == Error) ? Fee_ConfigPtr->FeeJobEndNotificationPtr
                                              : Fee_ConfigPtr->FeeJobErrorNotificationPtr;
    if (NotificationPtr != NULL_PTR)
    {
        /* Upon failure/successful of an asynchronous operation call the ErrorNotification/EndNotification
           [SWS_Fee_00055], [SWS_Fee_00056]. */
        (NotificationPtr)();
    }
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalDecideMainJob
 *
 *   Service ID              : None.
 *
 *   Description             : This function decides the current main job.
 *
 *   Parameters in           : None
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalDecideMainJob
(
    void
)
{
    switch (Fee_State.MainJob)
    {
        case FEE_MAIN_NONE:
        {
            /* User Read request is registered */
            if (FEE_READ_REQ == Fee_UserJobInfo.PendReqStatus)
            {
                Fee_State.MainJob = FEE_MAIN_READ;
            }
            /* User Write, Invalidate request is registered */
            else if (FEE_WRITE_REQ == Fee_UserJobInfo.PendReqStatus)
            {
                if (FALSE == Fee_UserJobInfo.WaitGc)
                {
                    Fee_State.MainJob = FEE_MAIN_WRITE;
                }
                else
                {
                    if (FEE_GC_IDLE == Fee_GcJobInfo.GcState)
                    {
                        /* Start the GC */
                        Fee_GcJobInfo.GcState = FEE_GC_REQUESTED;
                    }

                    if (FEE_GC_FAIL != Fee_GcJobInfo.GcState)
                    {
                        Fee_State.MainJob = FEE_MAIN_GC;
                    }
                }
            }
            /* no user job, switch to GC */
            else if ((FEE_GC_IDLE != Fee_GcJobInfo.GcState) && (FEE_GC_FAIL != Fee_GcJobInfo.GcState))
            {
#if (STD_ON == FEE_GC_RESTART_WRITE)
                if (TRUE == Fee_State.FeeWriteAPICalled)
#endif /* STD_ON \== FEE_GC_RESTART_WRITE */
                {
                    Fee_State.MainJob = FEE_MAIN_GC;
                }
            }
            /* stay FEE_MAIN_NONE */
            else
            /* #Violation: Fee_c_REF_10 */
            {
                /* Do Nothing */
            }
            break;
        }
        case FEE_MAIN_GC:
        {
            if ((FEE_GC_REQUESTED == Fee_GcJobInfo.GcState) ||
                /* Copying of a block is done. Copy of next block has not yet started */
                ((FEE_JOB_REQSTD != Fee_GcJobInfo.FlsJobStatus) &&
                 ((FEE_GC_ERASE_PREV_BANK == Fee_GcJobInfo.GcState) ||
                  (FEE_GC_COPY_WRITE == Fee_GcJobInfo.GcState))))
            {

                if (FEE_WRITE_REQ == Fee_UserJobInfo.PendReqStatus)
                {
                    /* Block can write to the old bank. */
                    if (FALSE == Fee_UserJobInfo.WaitGc)
                    {
                        /* switch to WRITE, halt GC */
                        Fee_State.MainJob = FEE_MAIN_WRITE;
                    }
                }
                else if (FEE_READ_REQ == Fee_UserJobInfo.PendReqStatus)
                {
                    Fee_State.MainJob = FEE_MAIN_READ;
                }
                else
                /* #Violation: Fee_c_REF_10 */
                {
                    /* Do Nothing */
                }
            }
            break;
        }
        /* FEE_MAIN_READ */
        default:
        {
            /* Do Nothing */
            break;
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalSetInitGc
 *
 *   Service ID              : None.
 *
 *   Description             : This function sets the InitGc state.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalSetInitGc
(
    void
)
{
    uint8  Bank0State;
    uint8  Bank1State;
    uint32 BaseAddr[FEE_DFLASH_BANK_NUM];

    Bank0State = Fee_State.BankInfoPtr[0].State;
    Bank1State = Fee_State.BankInfoPtr[1].State;
    BaseAddr[0] = FEE_DFLASH_BANK0_BASE;
    BaseAddr[1] = FEE_DFLASH_BANK1_BASE;

    if ((FEE_VALID == Bank0State) && (FEE_VALID == Bank1State))
    {
        /* when Erase of bank0 or bank1 is interrupted */
        /* because state count is update by such 1->2->3->1 order, the new bank state count is one
           more than other when modulo 3 */
        if (((Fee_State.BankInfoPtr[0].StateCount + 1U) % 3U) == (Fee_State.BankInfoPtr[1].StateCount % 3U))
        {
            Fee_State.CurrBank = 1U;
        }
        else
        {
            Fee_State.CurrBank = 0U;
        }
    }
    else if (FEE_VALID == Bank0State)
    {
        Fee_State.CurrBank = 0U;
    }
    else if (FEE_VALID == Bank1State)
    {
        Fee_State.CurrBank = 1U;
    }
    else
    /* #Violation: Fee_c_REF_10 */
    {
        /* Do Nothing */
    }

    /**
    * +-------------------------+-----------+---------------------+-----------------+---------------+
    * | Bank0State \ Bank1State | FEE_VALID | FEE_ERASED_NOT_USED | FEE_ERASED_USED | FEE_STATELESS |
    * +-------------------------+-----------+---------------------+-----------------+---------------+
    * | FEE_VALID               |     X     |          O          |        X        |        X      |
    * | FEE_ERASED_NOT_USED     |     O     |          X          |        X        |        X      |
    * | FEE_ERASED_USED         |     X     |          X          |        X        |        X      |
    * | FEE_STATELESS           |     X     |          X          |        X        |        X      |
    * +-------------------------+-----------+---------------------+-----------------+---------------+
    */
    /* one is valid and the other is erase_not_used, last gc completed. */
    if ((FEE_VALID | FEE_ERASED_NOT_USED) == (Bank0State | Bank1State))
    /* #Violation: Fee_c_REF_10 */
    {
        /* Do Nothing */
    }
    /**
    * +-------------------------+-----------+---------------------+-----------------+---------------+
    * | Bank0State \ Bank1State | FEE_VALID | FEE_ERASED_NOT_USED | FEE_ERASED_USED | FEE_STATELESS |
    * +-------------------------+-----------+---------------------+-----------------+---------------+
    * | FEE_VALID               |     O     |          X          |        O        |        O      |
    * | FEE_ERASED_NOT_USED     |     X     |          X          |        X        |        X      |
    * | FEE_ERASED_USED         |     O     |          X          |        X        |        X      |
    * | FEE_STATELESS           |     O     |          X          |        X        |        X      |
    * +-------------------------+-----------+---------------------+-----------------+---------------+
    */
    /* one is valid and another is not erase_not_used, last gc not completed because of power lose */
    else if ((FEE_VALID == Bank0State) || (FEE_VALID == Bank1State))
    {
        Fee_GcJobInfo.GcSrcAddr = BaseAddr[Fee_State.CurrBank];
        /* erase bank1 */
        Fee_GcJobInfo.GcDestAddr = BaseAddr[Fee_State.CurrBank ^ 1U];
        Fee_GcJobInfo.GcState = FEE_GC_ERASE_PREV_BANK;
        /* clear unerasable address to record bad sectors during Erase */
        Fee_State.BankInfoPtr[Fee_State.CurrBank ^ 1U].UnerasableCount = 0U;
    }
    /**
    * +-------------------------+-----------+---------------------+-----------------+---------------+
    * | Bank0State \ Bank1State | FEE_VALID | FEE_ERASED_NOT_USED | FEE_ERASED_USED | FEE_STATELESS |
    * +-------------------------+-----------+---------------------+-----------------+---------------+
    * | FEE_VALID               |     X     |          X          |        X        |        X      |
    * | FEE_ERASED_NOT_USED     |     X     |          X          |        X        |        O      |
    * | FEE_ERASED_USED         |     X     |          X          |        X        |        X      |
    * | FEE_STATELESS           |     X     |          X          |        X        |        X      |
    * +-------------------------+-----------+---------------------+-----------------+---------------+
    */
    /* Init gc not completed. */
    else if ((FEE_ERASED_NOT_USED == Bank0State) && (FEE_STATELESS == Bank1State))
    {
        /* when bank0 write VALID is interrupted. */
#if (STD_OFF == FEE_NOT_FOUND_MANAGEMENTINFO_DETECT)
        Fee_State.MainJob = FEE_MAIN_INITGC;
        Fee_GcJobInfo.GcState = FEE_GC_MARK_BANK_NEW_V_SP;
        Fee_State.CurrBank = 1U;
        /* point to the start address of bank0 */
        Fee_GcJobInfo.GcDestAddr = Fee_State.BankInfoPtr[0U].NextFreeAddr;
#else  /* (STD_OFF \== FEE_NOT_FOUND_MANAGEMENTINFO_DETECT) */
        /* initialization failed, switch to the uninit */
        Fee_Init_Status = MEMIF_UNINIT;
        /* Not found Fee module's management information */
        if (Fee_ConfigPtr->FeeNotFoundManagementInfoNotificationPtr != NULL_PTR)
        {
            Fee_ConfigPtr->FeeNotFoundManagementInfoNotificationPtr();
        }
#endif /* (STD_OFF \== FEE_NOT_FOUND_MANAGEMENTINFO_DETECT) */
    }
    /* (FEE_STATELESS == Bank0State) && (FEE_STATELESS \== Bank1State) or others */
    else
    {
        /* All state regard as sateless */
        Fee_State.BankInfoPtr[0].State = FEE_STATELESS;
        Fee_State.BankInfoPtr[1].State = FEE_STATELESS;
#if (STD_OFF == FEE_NOT_FOUND_MANAGEMENTINFO_DETECT)
        /* erase bank0 */
        Fee_State.MainJob = FEE_MAIN_INITGC;
        Fee_GcJobInfo.GcState = FEE_GC_ERASE_PREV_BANK;
        Fee_State.CurrBank = 1U;
        Fee_GcJobInfo.GcDestAddr = FEE_DFLASH_BANK0_BASE;
        Fee_State.BankInfoPtr[0].UnerasableCount = 0U;
        /* clear unerasable count */
#else  /* (STD_OFF \== FEE_NOT_FOUND_MANAGEMENTINFO_DETECT) */
        /* initialization failed, switch to the uninit */
        Fee_Init_Status = MEMIF_UNINIT;
        /* Not found Fee module's management information */
        if (Fee_ConfigPtr->FeeNotFoundManagementInfoNotificationPtr != NULL_PTR)
        {
            Fee_ConfigPtr->FeeNotFoundManagementInfoNotificationPtr();
        }
#endif /* (STD_OFF \== FEE_NOT_FOUND_MANAGEMENTINFO_DETECT) */
    }

    /* Point to the valid bank block info */
    Fee_State.BlockInfoPtr = &Fee_BlockInfos[Fee_State.CurrBank][0];
    Fee_State.NextFreePageAddr = Fee_State.BankInfoPtr[Fee_State.CurrBank].NextFreeAddr;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalCheckEraseStatePage
 *
 *   Service ID              : None.
 *
 *   Description             : This function evaluates the state page content.
 *
 *   Parameters in           : CurrBankSrcAddr: the current bank source address to check state page.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : State: Bank State.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(uint8, FEE_PRIVATE_CODE) Fee_LocalCheckEraseStatePage
(
    uint32 CurrBankSrcAddr
)
{
    uint8                   State;
    uint8                   ReturnVal;
    uint8                   Index;
    uint16                  BankNumber;
    uint16                  Count;
    uint16                  NormalSector;
    uint16                  Offset;
    uint32                  Addr;
    Fee_BankInfoType       *BankInfoPtr;
    Fee_ErasePageHeaderType EraseHeader;

    BankNumber = (CurrBankSrcAddr >= FEE_DFLASH_BANK1_BASE) ? 1U : 0U;
    BankInfoPtr = &Fee_State.BankInfoPtr[BankNumber];
    State = FEE_STATELESS;
    /* not empty, Read 1 page to get state page, excludes marker page */
    /* because this time the unerasable sector before find the erase state information so we don't
       map the address */
    /* #Violation: Fee_c_REF_7 */
    /* #Violation: Fee_c_REF_4 */
    /* #Violation: Fee_c_REF_11 */
    ReturnVal = Fls_ReadWordsSync(FEE_REALADDR(CurrBankSrcAddr), (uint32 *)&EraseHeader,
                                  sizeof(Fee_ErasePageHeaderType) >> FEE_WORD_TO_BYTE_SHIFT);
    /* parse erase state page info */
    if ((FLS_READ_SUCCESS == ReturnVal) && (FEE_STATEPAGE_ERASE_HEADER == EraseHeader.Tag) &&
        (FEE_STATEPAGE_DATA_TAG == EraseHeader.TailTag))
    {
        /* get unerasable count */
        BankInfoPtr->UnerasableCount = EraseHeader.BadSectorNum;
        /* Three Unerasable addresses can be stored in 16byte */
        Offset = (((uint16)BankInfoPtr->UnerasableCount + (FEE_MAX_UNERASABLE_INFO_IN_PAGE - 1U)) /
                  FEE_MAX_UNERASABLE_INFO_IN_PAGE) *
                 FEE_DFLASH_PAGE_SIZE;
        /* Check the marker */
        Addr = CurrBankSrcAddr + FEE_STATEPAGE_HEADER_DATA_SIZE + Offset;
        /* #Violation: Fee_c_REF_4 */
        ReturnVal = Fls_BlankCheckSync(FEE_REALADDR(Addr), (Fls_LengthType)FEE_DFLASH_PAGE_SIZE);
        if (FLS_BLANKCHECK_DIRTY == ReturnVal)
        {
            State = FEE_ERASED;
        }
    }

    /* verify unerasable sector's info */
    if (FEE_ERASED == State)
    {
        if (BankInfoPtr->UnerasableCount > 0U)
        {
            /* #Violation: Fee_c_REF_4 */
            ReturnVal = Fls_ReadWordsSync(FEE_REALADDR(CurrBankSrcAddr + FEE_STATEPAGE_HEADER_DATA_SIZE),
                                          /* #Violation: Fee_c_REF_7 */
                                          /* #Violation: Fee_c_REF_11 */
                                          (uint32 *)Fee_RWBuffer,
                                          ((Fls_LengthType)Offset >> FEE_WORD_TO_BYTE_SHIFT));
            if (FLS_READ_SUCCESS == ReturnVal)
            {
                for (Index = 0U; Index < BankInfoPtr->UnerasableCount; Index++)
                {
                    Fee_SectorReMap[Fee_RWBuffer[(Index << FEE_WORD_TO_BYTE_SHIFT) + 3U]] = 1U;
                }
            }
        }
        Offset = FEE_DFLASH_BANK_SECTOR_NUM * BankNumber;
        NormalSector = Offset;
        for (Count = Offset; Count < (Offset + FEE_DFLASH_BANK_SECTOR_NUM); Count++)
        {
            if (0U == Fee_SectorReMap[Count])
            {
                /* find normal sector so map the virtual sector to the normal sector index */
                Fee_SectorReMap[NormalSector] = (uint8)Count;
                NormalSector++;
            }
        }
    }

    if (FLS_READ_BUSY == ReturnVal)
    {
        State = FEE_FLS_ERROR;
    }

    return State;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalUpdateBlockInfo
 *
 *   Service ID              : None.
 *
 *   Description             : This function checks whether HeaderAddress contains a header.
 *
 *   Parameters in           : BlockHeaderPtr: point to the block header structure.
 *
 *   Parameters inout        : CurrBankAddr: address where may be the header.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: it is a header
 *                             E_NOT_OK: it is not a header
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_LocalUpdateBlockInfo
(
    uint32 *const CurrBankAddr,
    CONSTP2CONST(Fee_BlockHeaderType, AUTOMATIC, FEE_APPL_CONST) BlockHeaderPtr
)
{
    uint8               RetVal;
    uint8               BankNumber;
    uint16              BlockNumber;
    uint16              Index;
    uint16              DataPageCount;
    uint16              PageCount;
    uint32              TotalLen;
    boolean             IntactBlock;
    Fls_AddressType     Addr;
    boolean             PotentialMarkerPage;
    Fee_BlockInfoType  *BlockInfoPtr;
    Fee_BlockMarkerType BlockMarker;

    RetVal = E_OK;
    DataPageCount = 0U;
    IntactBlock = FALSE;
    BankNumber = (*CurrBankAddr >= FEE_DFLASH_BANK1_BASE) ? 1U : 0U;
    BlockNumber = ((uint16)BlockHeaderPtr->BlockNumber[1] << FEE_ONE_BYTE_SHIFT) | (uint16)BlockHeaderPtr->BlockNumber[0];
    Index = Fee_LocalGetUsrBlockIndex(BlockNumber);

    if (Index != FEE_LOG_BLOCK_NOT_FOUND)
    {
        PageCount = FEE_CALPAGES(Fee_ConfigPtr->FeeBlockConfigPtr[Index].BlockSize);
        BlockInfoPtr = &Fee_BlockInfos[BankNumber][Index];
    }
    else
    {
        PageCount = BlockHeaderPtr->PagesAndValid & FEE_PAGE_COUNT_MASK;
        BlockInfoPtr = &Fee_BlockInfos[BankNumber][Fee_ConfigPtr->FeeBlkCnt];
        Index = 0U;
        /* Whether the unconfigured block has been recorded or not. If it is, the index will point to that
         * block info; If not, the index will point to the next unset block info. */
        while ((Index < Fee_State.UnConfigBlockCount) &&
               (BlockInfoPtr->BlockNumber != BlockNumber))
        {
            Index++;
            BlockInfoPtr++;
        }
        Index += Fee_ConfigPtr->FeeBlkCnt;
    }

    if ((BlockHeaderPtr->PagesAndValid & FEE_VALID_MASK) == 0U)
    {
        /* invalid block contains no data */
        PageCount = 1U;
    }

    /* old version unconfigure block header not have pagecount fied, so the page count is zero. skip this
     * old unconfigure block */
    if (PageCount > 0U)
    {
        TotalLen = (uint32)PageCount << FEE_PAGE_TO_BYTE_SHIFT;
        /* Need check if the block have marker */
        /* #Violation: Fee_c_REF_4 */
        Addr = FEE_MAPADDR(*CurrBankAddr + TotalLen);
        /* #Violation: Fee_c_REF_7 */
        /* #Violation: Fee_c_REF_11 */
        RetVal = Fls_ReadWordsSync(Addr, (uint32 *)&BlockMarker,
                                   sizeof(Fee_BlockMarkerType) >> FEE_WORD_TO_BYTE_SHIFT);
        PotentialMarkerPage = TRUE;
        /* check whether it is Marker page */
        if (FLS_READ_SUCCESS == RetVal)
        {
            if (FEE_BLOCK_MARKER_TAG == BlockMarker.Tag)
            {
                if ((BlockMarker.PageCount == (FEE_PAGECOUNT_VERIFY - BlockMarker.PageCountRev)) &&
                    (BlockMarker.PageCount == PageCount))
                {
                    IntactBlock = TRUE;
                }
            }
            else if (FEE_BLOCK_HEADER_TAG == (BlockMarker.Tag & FEE_GET_LOW_BYTE))
            {
                /* There is other block */
                PotentialMarkerPage = FALSE;
            }
            else if (FEE_ERASE_VALUE == (BlockMarker.Tag & FEE_GET_LOW_BYTE))
            {
                /* this page maybe erase */
                RetVal = Fls_BlankCheckSync(Addr, FEE_DFLASH_PAGE_SIZE);
                if (FLS_BLANKCHECK_EMPTY == RetVal)
                {
                    /* the marker location is erased  */
                    PotentialMarkerPage = FALSE;
                }
            }
            else
            /* #Violation: Fee_c_REF_10 */
            {
                /* Do Nothing */
            }
        }

        if ((RetVal != FLS_READ_BUSY) && (FALSE == IntactBlock) && (TRUE == PotentialMarkerPage))
        {
            /* Not have valid marker */
            while (DataPageCount < (PageCount - 1U))
            {
                /* Need check if the block have enough data */
                DataPageCount++;
                /* #Violation: Fee_c_REF_4 */
                Addr = FEE_MAPADDR(*CurrBankAddr + (FEE_DFLASH_PAGE_SIZE * (uint32)DataPageCount));
                /* #Violation: Fee_c_REF_7 */
                /* #Violation: Fee_c_REF_11 */
                RetVal = Fls_ReadWordsSync(Addr, (uint32 *)Fee_RWBuffer, 1U);
                if ((FLS_READ_SUCCESS != RetVal) || (FEE_BLOCK_DATA_TAG != Fee_RWBuffer[0U]))
                {
                    /* skip the data we have read that not intact except the last page that may belong
                    to other block */
                    *CurrBankAddr += FEE_DFLASH_PAGE_SIZE * ((uint32)DataPageCount - 1U);
                    /* break the while */
                    DataPageCount = PageCount;
                }
            }

            if (DataPageCount == (PageCount - 1U))
            {
                /* the block have enough data, so we think this is a intact block */
                RetVal = E_OK;
                IntactBlock = TRUE;
            }
        }
    }

    if (TRUE == IntactBlock)
    {
        if (Index < FEE_MAX_BLOCK_COUNT)
        {
            /* find new unconfigued block */
            if (Index == (Fee_ConfigPtr->FeeBlkCnt + Fee_State.UnConfigBlockCount))
            {
                Fee_State.UnConfigBlockCount++;
            }
            /* Record the block info to cache table.  */
            BlockInfoPtr->Address = *CurrBankAddr;
            BlockInfoPtr->BlockCycleCount = ((uint32)BlockHeaderPtr->BlockCycleCount[2] << FEE_TWO_BYTE_SHIFT) |
                                            ((uint32)BlockHeaderPtr->BlockCycleCount[1] << FEE_ONE_BYTE_SHIFT)  |
                                            (uint32)BlockHeaderPtr->BlockCycleCount[0];
            BlockInfoPtr->Valid = ((BlockHeaderPtr->PagesAndValid & FEE_VALID_MASK) != 0U) ? TRUE : FALSE;
            BlockInfoPtr->Consistent = TRUE;
            BlockInfoPtr->Copied = FALSE;
            BlockInfoPtr->PageCount = PageCount;
            BlockInfoPtr->BlockNumber = BlockNumber;
        }
        else
        {
            /* Un-configured blocks cache table is already full, And no FEE_E_UNCONFIG_BLK_EXCEEDED error
             * has been reported yet  */
            if (0U == Fee_State.UncfgBlksExceeded)
            {
#if (FEE_UNCFG_BLK_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
               /* Report unconfig block exceeded error to Dem */
                Dem_ReportErrorStatus(FEE_E_UNCONFIG_BLK_EXCEEDED, DEM_EVENT_STATUS_FAILED);
#endif
                FEE_REPORTERROR(FEE_INIT_ID, FEE_E_UNCONFIG_BLOCK_EXCEEDED);
                Fee_State.UncfgBlksExceeded++;
            }
        }
        /* Got a intact block so update the block info. */
        *CurrBankAddr += TotalLen;
    }

    /* Read the header page + data. 16byte */
    return RetVal;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalTraversalUpdateBlockInfo
 *
 *   Service ID              : None.
 *
 *   Description             : This function traversal the whole bank and update the block infomation.
 *
 *   Parameters in           : BankNumber: The bank number to traversal.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(uint8, FEE_PRIVATE_CODE) Fee_LocalTraversalUpdateBlockInfo
(
    uint8 BankNumber
)
{
    uint32                   EndAddr;
    uint32                   CurrBankSrcAddr;
    uint32                   BlankCheckLen;
    boolean                  FindValid;
    boolean                  SearchEnd;
    uint8                    RetVal;
    Fee_BankInfoType        *BankInfoPtr;
    Fee_BufferUnionType      BufferUnion;


    RetVal = E_OK;
    FindValid = FALSE;
    SearchEnd = FALSE;
    BankInfoPtr = &Fee_State.BankInfoPtr[BankNumber];
    CurrBankSrcAddr = BankInfoPtr->NextFreeAddr;
    EndAddr =
        (FEE_DFLASH_BANK_SIZE << BankNumber) - (FEE_SECTOR_SIZE * (uint32)BankInfoPtr->UnerasableCount);

    /* search from stat of bank to end of bank */
    while ((FALSE == SearchEnd) && (FLS_READ_BUSY != RetVal))
    {
        /* Read the header 1 page (4 Words), 16bytes */
        /* #Violation: Fee_c_REF_4 */
        RetVal = Fls_ReadWordsSync(FEE_MAPADDR(CurrBankSrcAddr), BufferUnion.Buffer,
                                   FEE_DFLASH_PAGE_SIZE >> FEE_WORD_TO_BYTE_SHIFT);
        if (FLS_READ_SUCCESS == RetVal)
        {
            if (FEE_BLOCK_HEADER_TAG == BufferUnion.BlockHeader.Tag)
            {
                /* It maybe a block */
                /* #Violation: Fee_c_REF_7 */
                /* #Violation: Fee_c_REF_11 */
                RetVal = Fee_LocalUpdateBlockInfo(&CurrBankSrcAddr, &BufferUnion.BlockHeader);
            }
            else if (FEE_ERASE_VALUE == BufferUnion.BlockHeader.Tag)
            {
                /* It may be a empty page. Check whether the maximum length written last time is blank to
                 * make sure there is no powerlose. */
                /* #Violation: Fee_c_REF_2 */
                /* #Violation: Fee_c_REF_2 */
                BlankCheckLen = FEE_MIN(FEE_WRITE_LEN_MAX,
                                        FEE_DFLASH_WORDLINE_SIZE - FEE_OFFSETOFWL(CurrBankSrcAddr));
                /* #Violation: Fee_c_REF_4 */
                RetVal = Fls_BlankCheckSync(FEE_MAPADDR(CurrBankSrcAddr), BlankCheckLen);
                if (FLS_BLANKCHECK_EMPTY == RetVal)
                {
                    if (TRUE == FindValid)
                    {
                        /* After valid sate page the empty page present the end of written date of bank,
                         so stop traverse, and log the position */
                        SearchEnd = TRUE;
                        BankInfoPtr->NextFreeAddr = CurrBankSrcAddr;
                        BankInfoPtr->State = FEE_VALID;
                    }
                    else if (0U == (CurrBankSrcAddr % FEE_DFLASH_WORDLINE_SIZE))
                    {
                        /* Because valid page align to wordline, if their is no valid Page in the start
                           of wordline, their is no valid state in the bank */
                        if (((FEE_DFLASH_BANK_SIZE * BankNumber) + FEE_DFLASH_WORDLINE_SIZE) ==
                            CurrBankSrcAddr)
                        {
                            /* the bank only have ease state page */
                            BankInfoPtr->State = FEE_ERASED_NOT_USED;
                        }
                        else
                        {
                            /* the bank only have ease state page and some other data */
                            BankInfoPtr->State = FEE_ERASED_USED;
                        }
                        SearchEnd = TRUE;
                        /* This addr is align to word line so it maybe skip some erased page */
                        BankInfoPtr->NextFreeAddr = CurrBankSrcAddr;
                    }
                    else
                    {
                        /* Maybe there is valid state page in the next wordLine */
                        /* #Violation: Fee_c_REF_2 */
                        CurrBankSrcAddr = FEE_GETWLBEGINNING(CurrBankSrcAddr + FEE_DFLASH_WORDLINE_SIZE) -
                                          FEE_DFLASH_PAGE_SIZE;
                    }
                }
            }
            else if ((FALSE == FindValid) && (0U == (CurrBankSrcAddr % FEE_DFLASH_WORDLINE_SIZE)))
            {
                /* Maybe find a valid State page */
                if (FEE_STATEPAGE_VALID_HEADER == BufferUnion.ValidHeader.Tag)
                {
                    /* check the valid sate page */
                    RetVal =
                        /* #Violation: Fee_c_REF_4 */
                        Fls_BlankCheckSync(FEE_MAPADDR(CurrBankSrcAddr + FEE_STATEPAGE_HEADER_DATA_SIZE),
                                           (Fls_LengthType)FEE_DFLASH_PAGE_SIZE);
                    if (FLS_BLANKCHECK_DIRTY == RetVal)
                    {
                        /* Log the state count in the valid page */
                        BankInfoPtr->StateCount = BufferUnion.ValidHeader.StateCount;
                        BankInfoPtr->GcNumber = BufferUnion.ValidHeader.GcNumber;
                        /* There maybe other block date behind the valid state page, so continue
                           traverse. */
                        CurrBankSrcAddr += FEE_DFLASH_PAGE_SIZE;
                        FindValid = TRUE;
                    }
                }
            }
            else
            /* #Violation: Fee_c_REF_10 */
            {
                /* Do Nothing */
            }
        }

        /* Add one page by default */
        CurrBankSrcAddr += FEE_DFLASH_PAGE_SIZE;
        /* Arrive the end of the bank */
        if (CurrBankSrcAddr >= EndAddr)
        {
            BankInfoPtr->State = (TRUE == FindValid) ? FEE_VALID : FEE_ERASED_USED;
            BankInfoPtr->NextFreeAddr = CurrBankSrcAddr;
            SearchEnd = TRUE;
        }
    }

    return RetVal;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalHandleUserWriteReq
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles write request.
 *
 *   Parameters in           : BlockIndex: Index of the requested block.
 *                           : DataBufferPtr: The data buffer to write.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalHandleUserWriteReq
(
    uint16 BlockIndex,
    CONSTP2CONST(uint8, AUTOMATIC, FEE_APPL_CONST) DataBufferPtr
)
{
    const Fee_BlockConfigType *BlockPtr;
    uint16                     BlockPages;
    uint16                     RemainingPages;
    Fee_BlockInfoType const   *BlockInfoPtr;

    BlockPtr = &Fee_ConfigPtr->FeeBlockConfigPtr[BlockIndex];
    Fee_State.FeeWriteAPICalled = TRUE;
    BlockPages = (TRUE == Fee_UserJobInfo.BlockInvalidReq) ? FEE_INVALIDBLOCK_PAGE_SIZE
                                                           : (1U + FEE_CALPAGES(BlockPtr->BlockSize));
    /* Set the job result to MEMIF_JOB_PENDING, [SWS_Fee_00025] */
    Fee_UserJobInfo.JobResult = MEMIF_JOB_PENDING;
    Fee_UserJobInfo.PendReqStatus = FEE_WRITE_REQ;
    /* Store the pending request parameters */
    Fee_UserJobInfo.BlockNumber = BlockPtr->BlockNumber;
    Fee_UserJobInfo.WriteDataBufferPtr = DataBufferPtr;
    Fee_UserJobInfo.BlockIndex = BlockIndex;
    /* write is to be started, set variables */
    Fee_UserJobInfo.UserWriteBytesCount = 0U;
    Fee_UserJobInfo.BlockPageCount = 0U;
    Fee_UserJobInfo.LastWriteSize = 0U;
    Fee_UserJobInfo.BlockPages = BlockPages;
    BlockInfoPtr = &(Fee_State.BlockInfoPtr[BlockIndex]);

    /* Check if Block Cycle Count has reached the maximum and Check left space if request can be
     * performed */
    if ((0U == BlockPtr->NumberOfWriteCycles) ||
        (BlockInfoPtr->BlockCycleCount < BlockPtr->NumberOfWriteCycles))
    {
        /* check current bank's empty space how many we need */
        /* how many left in this BANK */
        RemainingPages = FEE_GETREMAINPAGES(Fee_State.CurrBank, Fee_State.NextFreePageAddr);
        /* Reserve writable space for immediate writing. Refer to [SWS_Fee_00009] */
        Fee_UserJobInfo.WaitGc = FALSE;
        if (RemainingPages < (BlockPages + (FEE_THRESHOLD_LIMIT >> FEE_PAGE_TO_BYTE_SHIFT)))
        {
            if (FEE_GC_IDLE == Fee_GcJobInfo.GcState)
            {
                /* Start the GC */
                Fee_GcJobInfo.GcState = FEE_GC_REQUESTED;
            }

            if ((FALSE == BlockPtr->ImmediateData) || (RemainingPages < BlockPages))
            {
                /* Will be block by gc in mainfunciton */
                Fee_UserJobInfo.WaitGc = TRUE;
            }
        }
    }
    else
    {
#if (FEE_WRITE_CYCLES_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
        /* Report write cycles exhausted error to Dem */
        Dem_ReportErrorStatus(FEE_E_WRITE_CYCLES_EXHAUSTED, DEM_EVENT_STATUS_FAILED);
#endif
        Fee_UserJobInfo.FlsJobStatus = FEE_JOB_FAILED;
        Fee_UserJobInfo.JobResultPending = MEMIF_JOB_FAILED;
    }
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalWrite
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles FEE write process.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalWrite
(
    void
)
{
    uint16                     RemainLen;
    uint16                     RealLen;
    uint16                     PageOffset;
    uint16                     BlockSize;
    uint16                     BlockPages;
    uint32                     Length;
    const uint8               *SrcDataBufferPtr;
    const Fee_BlockConfigType *BlockPtr;
    Fee_BlockInfoType         *BlockInfoPtr;
    Fee_BlockHeaderType       *BlockHeaderPtr;
    uint8                     *DestWriteBuffPtr;
    Std_ReturnType             RetVal;
#if (STD_ON == FEE_SOFTWARE_VERIFY)
    uint8 CompareReturnVal;
#endif /* (STD_ON \== FEE_SOFTWARE_VERIFY) */

    BlockInfoPtr = &(Fee_State.BlockInfoPtr[Fee_UserJobInfo.BlockIndex]);
    /* finish last write, continue. Next Step: End or Continue write */
    if (FEE_JOB_DONE == Fee_UserJobInfo.FlsJobStatus)
    {
#if (STD_ON == FEE_SOFTWARE_VERIFY)
        CompareReturnVal = Fls_CompareWordsSync(
            /* #Violation: Fee_c_REF_7 */
            /* #Violation: Fee_c_REF_11 */
            FEE_MAPADDR(Fee_State.NextFreePageAddr), (uint32 *)(Fee_RWBuffer),
            ((Fls_LengthType)Fee_UserJobInfo.LastWriteSize >> FEE_WORD_TO_BYTE_SHIFT));
        /* Compare failed */
        if (CompareReturnVal != FLS_COMPARE_EQUAL)
        {
            /* Skip the already written area */
            Fee_State.NextFreePageAddr += Fee_UserJobInfo.LastWriteSize;
            /* Invalidate and write, error handling are handled using the same logic */
            Fee_LocalHandleUsrJobEnd(MEMIF_JOB_FAILED);
        }
        /* Compare Successful */
        else
#endif /* (STD_ON \== FEE_SOFTWARE_VERIFY) */
        {
            /* move to next */
            Fee_State.NextFreePageAddr += Fee_UserJobInfo.LastWriteSize;
            /* Invalid Block only requires writing two pages. Header + Marker */
            /* Write request - Check if all pages written */
            if (Fee_UserJobInfo.BlockPageCount == Fee_UserJobInfo.BlockPages)
            {
                /* Update latest copy information in the Block Info buffer */
                BlockInfoPtr->Address =
                    Fee_State.NextFreePageAddr - ((uint32)Fee_UserJobInfo.BlockPages * FEE_DFLASH_PAGE_SIZE);
                /* Upon the successful end of the block write operation, the block shall be */
                /* marked as "not corrupted" (again). Refer to [SWS_Fee_00154] */
                BlockInfoPtr->Consistent = TRUE;
                /* Set Block Validity */
                BlockInfoPtr->Valid = (TRUE == Fee_UserJobInfo.BlockInvalidReq) ? FALSE : TRUE;
                BlockInfoPtr->PageCount = Fee_UserJobInfo.BlockPages - 1U;

                if ((Fee_GcJobInfo.GcState != FEE_GC_IDLE) &&
                    (Fee_GcJobInfo.GcState != FEE_GC_FAIL))
                {
                    /* GC is going on */
                    /* The marked block has been copied to a new bank */
                    Fee_GcJobInfo.BlockModified = TRUE;
                    BlockInfoPtr->Copied = FALSE;
                }
                Fee_LocalHandleUsrJobEnd(MEMIF_JOB_OK);
            }
        }
    }

    if (FEE_JOB_FAILED == Fee_UserJobInfo.FlsJobStatus)
    {
        Fee_State.NextFreePageAddr += Fee_UserJobInfo.LastWriteSize;
        Fee_LocalHandleUsrJobEnd(Fee_UserJobInfo.JobResultPending);
    }

    /* start write */
    if (FEE_WRITE_REQ == Fee_UserJobInfo.PendReqStatus)
    {
        /* success \==> FEE_WRITE_COMPARE */
        /* write align in one wordline */
        SrcDataBufferPtr = Fee_UserJobInfo.WriteDataBufferPtr;
        DestWriteBuffPtr = Fee_RWBuffer;
        BlockPtr = &Fee_ConfigPtr->FeeBlockConfigPtr[Fee_UserJobInfo.BlockIndex];
        BlockSize = (TRUE == Fee_UserJobInfo.BlockInvalidReq) ? 0U : BlockPtr->BlockSize;
        BlockPages = FEE_CALPAGES(BlockSize);

        /* If the block write complete. */
        if (Fee_UserJobInfo.BlockPageCount >= BlockPages)
        {
            /* #Violation: Fee_c_REF_7 */
            /* #Violation: Fee_c_REF_11 */
            Fee_LocalMakeBlockMarker((Fee_BlockMarkerType *)DestWriteBuffPtr, BlockPages);
            Fee_UserJobInfo.BlockPageCount++;
            Fee_UserJobInfo.LastWriteSize = FEE_DFLASH_PAGE_SIZE;
        }
        else
        {
            if (0U == Fee_UserJobInfo.BlockPageCount)
            {
                /* Header page */
                /* #Violation: Fee_c_REF_7 */
                /* #Violation: Fee_c_REF_11 */
                BlockHeaderPtr = (Fee_BlockHeaderType *)Fee_RWBuffer;
                BlockInfoPtr->Consistent = FALSE;
                BlockInfoPtr->BlockCycleCount++;
                BlockHeaderPtr->Tag = FEE_BLOCK_HEADER_TAG;
                BlockHeaderPtr->BlockNumber[0] = (uint8)Fee_UserJobInfo.BlockNumber;
                BlockHeaderPtr->BlockNumber[1] = (uint8)(Fee_UserJobInfo.BlockNumber >> FEE_ONE_BYTE_SHIFT);
                BlockHeaderPtr->PagesAndValid =
                    BlockPages | ((TRUE == Fee_UserJobInfo.BlockInvalidReq) ? 0U : FEE_VALID_BIT);
                /* Record the number of block writes. */
                BlockHeaderPtr->BlockCycleCount[0] = (uint8)BlockInfoPtr->BlockCycleCount;
                BlockHeaderPtr->BlockCycleCount[1] = (uint8)(BlockInfoPtr->BlockCycleCount >> FEE_ONE_BYTE_SHIFT);
                BlockHeaderPtr->BlockCycleCount[2] = (uint8)(BlockInfoPtr->BlockCycleCount >> FEE_TWO_BYTE_SHIFT);
                /*  Valid bit zero */
                PageOffset = FEE_BLOCK_HEADER_SIZE;
                DestWriteBuffPtr = &Fee_RWBuffer[PageOffset];
            }
            else
            {
                PageOffset = 1U;
            }

            /* Calculate the actually length of flash data should be write, it limit by 3 condition:
               1.the length of date to be be write, 2.not cross wordline, 3. the max size the fls can write.
            */
            RemainLen = BlockSize - Fee_UserJobInfo.UserWriteBytesCount;
            Length = (((uint32)RemainLen + PageOffset + FEE_USER_PAGE_BYTE_COUNT - 2U) /
                      FEE_USER_PAGE_BYTE_COUNT * FEE_DFLASH_PAGE_SIZE);
            Length =
                /* #Violation: Fee_c_REF_2 */
                /* #Violation: Fee_c_REF_2 */
                FEE_MIN(Length, FEE_DFLASH_WORDLINE_SIZE - FEE_OFFSETOFWL(Fee_State.NextFreePageAddr));
            /* #Violation: Fee_c_REF_2 */
            Length = FEE_MIN(Length, FEE_WRITE_LEN_MAX);
            Fee_UserJobInfo.LastWriteSize = (uint16)Length;

            /* Calculate the actually length data of block be write from the length of flash data */
            RealLen = ((Fee_UserJobInfo.LastWriteSize >> FEE_PAGE_TO_BYTE_SHIFT) * FEE_USER_PAGE_BYTE_COUNT) - PageOffset + 1U;
            /* #Violation: Fee_c_REF_2 */
            RealLen = FEE_MIN(RemainLen, RealLen);
            Fee_UserJobInfo.WriteDataBufferPtr = &Fee_UserJobInfo.WriteDataBufferPtr[RealLen];
            Fee_UserJobInfo.UserWriteBytesCount += RealLen;
            Fee_UserJobInfo.BlockPageCount += Fee_UserJobInfo.LastWriteSize >> FEE_PAGE_TO_BYTE_SHIFT;

            /* Add data to the write buffer from the user specified pointer */
            while (SrcDataBufferPtr < Fee_UserJobInfo.WriteDataBufferPtr)
            {
                /* #Violation: Fee_c_REF_6 */
                if (((uint32)DestWriteBuffPtr & (FEE_DFLASH_PAGE_SIZE - 1U)) == 0U)
                {
                    *DestWriteBuffPtr = FEE_BLOCK_DATA_TAG;
                    DestWriteBuffPtr++;
                }
                *DestWriteBuffPtr = *SrcDataBufferPtr;
                DestWriteBuffPtr++;
                SrcDataBufferPtr++;
            }
            /* Use zero to fill the last one page */
            /* #Violation: Fee_c_REF_6 */
            while (((uint32)DestWriteBuffPtr & (FEE_DFLASH_PAGE_SIZE - 1U)) != 0U)
            {
                *DestWriteBuffPtr = 0U;
                DestWriteBuffPtr++;
            }
        }

        /* Call Fls_Write() to write data to Flash after writing format construction */
        Fee_UserJobInfo.FlsJobStatus = FEE_JOB_REQSTD;
        /* #Violation: Fee_c_REF_4 */
        RetVal = Fls_Write(FEE_MAPADDR(Fee_State.NextFreePageAddr), Fee_RWBuffer,
                           Fee_UserJobInfo.LastWriteSize);
        if (RetVal != E_OK)
        {
            /* Invalidate and write, error handling are handled using the same logic */
            Fee_LocalHandleUsrJobEnd(MEMIF_JOB_FAILED);
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalRead
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles FEE read process.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalRead
(
    void
)
{

    uint8 const   *ReadBufferPtr;
    uint8 const   *ReadLimitPtr;
    uint16         RealLen;
    uint32         SrcAddr;
    uint32         ReadLength;
    Std_ReturnType ReturnValue;

    if (FEE_JOB_DONE == Fee_UserJobInfo.FlsJobStatus)
    {
        /* Perform any necessary block management operations. [SWS_Fee_00052] */
        ReadBufferPtr = &Fee_RWBuffer[Fee_UserJobInfo.BlockOffset];
        ReadLimitPtr = &Fee_UserJobInfo.ReadDataBufferPtr[Fee_UserJobInfo.LastReadSize];
        while (Fee_UserJobInfo.ReadDataBufferPtr < ReadLimitPtr)
        {
            /* #Violation: Fee_c_REF_6 */
            if (((uint32)ReadBufferPtr & (FEE_DFLASH_PAGE_SIZE - 1U)) == 0U)
            {
                /* skip DATA_TAG, at 16th, 32th.... */
                ReadBufferPtr++;
            }
            *Fee_UserJobInfo.ReadDataBufferPtr = *ReadBufferPtr;
            Fee_UserJobInfo.ReadDataBufferPtr++;
            ReadBufferPtr++;
        }

        if (Fee_UserJobInfo.Length > 0U)
        {
            /* after the first round of read, the next will align to first byte of page */
            Fee_UserJobInfo.BlockOffset = 1U;
        }
        else
        /* Same as Fee_UserJobInfo.FeePendReqStatus = FEE_READ_ALL; */
        /* Finish read job */
        {
            Fee_LocalHandleUsrJobEnd(MEMIF_JOB_OK);
        }
    }

    if (FEE_JOB_FAILED == Fee_UserJobInfo.FlsJobStatus)
    {
        Fee_LocalHandleUsrJobEnd(Fee_UserJobInfo.JobResultPending);
    }

    /* Read not complete */
    if (FEE_READ_REQ == Fee_UserJobInfo.PendReqStatus)
    {
        /* Record the address that needs to be read */
        SrcAddr = Fee_UserJobInfo.CurrBankSrcAddr;

        /* Determine whether the read content is on the same page as the header */
        /* Counting tag information(FEE_BLOCK_DATA_TAG), calculate how many bytes need to be read in
           total */
        ReadLength = (((uint32)Fee_UserJobInfo.Length + Fee_UserJobInfo.BlockOffset +
                       FEE_USER_PAGE_BYTE_COUNT - 2U) /
                      FEE_USER_PAGE_BYTE_COUNT * FEE_DFLASH_PAGE_SIZE);
        /* #Violation: Fee_c_REF_2 */
        ReadLength = FEE_MIN(ReadLength, FEE_DFLASH_WORDLINE_SIZE);
        RealLen = (uint16)(((ReadLength >> FEE_PAGE_TO_BYTE_SHIFT) * FEE_USER_PAGE_BYTE_COUNT) -
                           Fee_UserJobInfo.BlockOffset + 1U);
        /* #Violation: Fee_c_REF_2 */
        RealLen = FEE_MIN(RealLen, Fee_UserJobInfo.Length);
        Fee_UserJobInfo.Length -= RealLen;

        /* Call Fls_Read to read the data from DFLASH */
        ReturnValue = Fee_LocalSkipRead(SrcAddr, ReadLength);
        if (ReturnValue == E_OK)
        {
            Fee_UserJobInfo.FlsJobStatus = FEE_JOB_REQSTD;
            /* Increment FeeCurrBankSrcAddr to point to next page */
            SrcAddr += ReadLength;
            /* update next address */
            Fee_UserJobInfo.CurrBankSrcAddr = SrcAddr;
            /* use it to extract logical block data from RWBuffer */
            Fee_UserJobInfo.LastReadSize = RealLen;
        }
        else
        {
            Fee_LocalHandleUsrJobEnd(MEMIF_JOB_FAILED);
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGcRead
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles GC read process.
 *
 *   Parameters in           : SrcAddr: DFlash address where to read.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : FEE_NO_ERROR: success
 *                             FEE_GC_READ: read error
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcRead
(
    Fls_AddressType SrcAddr
)
{
    uint16           ReadLength;
    uint16           PendingBlockSize;
    Fee_JobErrorType Error;
    Std_ReturnType   RetVal;

    Error = FEE_NO_ERROR;

    /* how many bytes left in this logical block to be copied (except marker page) */
    PendingBlockSize =
        (Fee_GcJobInfo.GcCurrBlockPageCount - Fee_GcJobInfo.BlockPageCount) * FEE_DFLASH_PAGE_SIZE;

    /* make sure we write in one wordline for destAddr to use fifo write */
    /* #Violation: Fee_c_REF_2 */
    /* #Violation: Fee_c_REF_2 */
    ReadLength = FEE_MIN(PendingBlockSize,
                         FEE_DFLASH_WORDLINE_SIZE - (uint16)FEE_OFFSETOFWL(Fee_GcJobInfo.GcDestAddr));
    RetVal = Fee_LocalSkipRead(SrcAddr, ReadLength);
    if (E_OK == RetVal)
    {
        Fee_GcJobInfo.LastReadSize = ReadLength;
        Fee_GcJobInfo.FlsJobStatus = FEE_JOB_REQSTD;
    }
    else
    {
        Error = FEE_GC_READ;
    }

    return Error;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGcWrite
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles GC write process.
 *
 *   Parameters in           : DestAddr: DFlash address where to write.
 *                             Size: data length
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : FEE_NO_ERROR: success
 *                             FEE_GC_WRITE: write error
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcWrite
(
    Fls_AddressType DestAddr,
    uint16 Size
)
{
    Fee_JobErrorType Error;
    Std_ReturnType   ReturnValue;

    /* Backup Fee internal status and mark it before Fls_Write called */
    Fee_GcJobInfo.LastWriteSize = Size;
    Fee_GcJobInfo.FlsJobStatus = FEE_JOB_REQSTD;
    /* #Violation: Fee_c_REF_4 */
    ReturnValue = Fls_Write(FEE_MAPADDR(DestAddr), Fee_RWBuffer, (Fls_LengthType)Size);
    /* if the Fls routine did not accept the request */
    if (ReturnValue != E_OK)
    {
        /* Resume Fee internal status */
        Fee_GcJobInfo.FlsJobStatus = FEE_JOB_IDLE;
        Error = FEE_GC_WRITE;
    }
    else
    {
        /* Prepare for skipping this area next time when writing */
        Error = FEE_NO_ERROR;
    }
    return Error;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGcRequested
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles GC request process.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : FEE_NO_ERROR: success
 *                             FEE_GC_READ: read error
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcRequested
(
    void
)
{
    Fee_BlockInfoType      *BlockInfoPtr;
    uint16                  BlockCount;
    Fee_JobErrorType        Error;
    Fee_BankInfoType const *BankInfoPtr;

    /* Calculate the target address of GC */
    BankInfoPtr = &Fee_State.BankInfoPtr[Fee_State.CurrBank ^ 1U];
    Fee_GcJobInfo.GcDestAddr = BankInfoPtr->NextFreeAddr;
    BlockInfoPtr = Fee_State.BlockInfoPtr;
    BlockCount = 0U;
    /* clear copied status */
    do
    {
        BlockInfoPtr->Copied = FALSE;
        BlockCount++;
        BlockInfoPtr++;
    } while (BlockCount < FEE_MAX_BLOCK_COUNT);
    /* mark if any write operation issued during GC */
    Fee_GcJobInfo.BlockModified = FALSE;

    /* Record the current GC block index, start form unconfigureble */
    Fee_GcJobInfo.GCCopyIndex = (sint16)Fee_ConfigPtr->FeeBlkCnt + (sint16)Fee_State.UnConfigBlockCount - 1;
    /* the target bank have enough space */
    Error = Fee_LocalGcStartCopy();

    return Error;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGcStartCopy
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles GC process(start copy).
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : FEE_NO_ERROR: success
 *                             FEE_GC_WRITE: write error.
 *                             FEE_GC_READ: read error
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcStartCopy
(
    void
)
{
    Fee_BlockInfoType *BlockInfoPtr;
    boolean            Flag;
    sint16             BlockCount;
    uint16             RemainingPages;
    boolean            ConsistentFlag;
    boolean            CopiedFlag;
    Fee_JobErrorType   Error;

    Error = FEE_NO_ERROR;
    Flag = FALSE;
    BlockCount = Fee_GcJobInfo.GCCopyIndex;

    /* Check if there are any blocks to be copied, if any of the logical blocks were modified.
         * Immediate write occurred during GC period. */
    if ((TRUE == Fee_GcJobInfo.BlockModified) && (BlockCount < (sint16)Fee_ConfigPtr->FeeBlkCnt))
    {
        Fee_GcJobInfo.BlockModified = FALSE;
        /* start from the beginning */
        BlockCount = (sint16)Fee_ConfigPtr->FeeBlkCnt - 1;
    }

    while ((BlockCount >= 0) && (Flag != TRUE))
    {
        BlockInfoPtr = &Fee_State.BlockInfoPtr[BlockCount];
        /* If block is consistent and not copied */
        ConsistentFlag = BlockInfoPtr->Consistent;
        CopiedFlag = BlockInfoPtr->Copied;
        if ((TRUE == ConsistentFlag) && (FALSE == CopiedFlag))
        {
            /* there is some logical block un-copied */
            Flag = TRUE;
            /* found an un-copied block, FeeGCCopyIndex record it, i.e. FeeBlockInfoPtr[index] */
            Fee_GcJobInfo.GCCopyIndex = BlockCount;
        }
        else
        {
            BlockCount--;
        }
    }

    /* start Block copying*/
    if (Flag == TRUE)
    {
        BlockInfoPtr = &Fee_State.BlockInfoPtr[Fee_GcJobInfo.GCCopyIndex];
        BlockInfoPtr->Copied = TRUE;
        Fee_GcJobInfo.BlockPageCount = 0U;
        Fee_GcJobInfo.GcSrcAddr = BlockInfoPtr->Address;
        /* total page count need to read */
        /* Reasons for excluding markers: The marker information may not be completed and
            reading may result in an Ecc error, and there is no need to copy the erroneous
            marker to a new bank. After copying, Fee will automatically build a new marker
            for the Block */
        Fee_GcJobInfo.GcCurrBlockPageCount = BlockInfoPtr->PageCount;

        RemainingPages = FEE_GETREMAINPAGES(Fee_State.CurrBank ^ 1U, Fee_GcJobInfo.GcDestAddr);
        if ((Fee_GcJobInfo.GcCurrBlockPageCount + 1U) > RemainingPages)
        {
            Error = FEE_GC_TRIG;
        }
        else
        {
            /* read enough data to fill DestAddr in a whole wordline */
            Fee_GcJobInfo.GcState = FEE_GC_COPY_READ_NXTPAGE;
            Error = Fee_LocalGcRead((Fls_AddressType)Fee_GcJobInfo.GcSrcAddr);
        }
    }
    /* Finished copying all the configured blocks */
    else
    {
        /* do not need to check whether GcDestAddr reaches the end of the new bank,
            due to we check space when start copy a logical block */
        /* start to write valid state page */
        Fee_GcJobInfo.FlsJobStatus = FEE_JOB_IDLE;
        Fee_GcJobInfo.GcState = FEE_GC_MARK_BANK_NEW_V_SP;
    }

    return Error;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGcStartCopyWrite
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles GC process(write to flash).
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : FEE_GC_WRITE: write error
 *                             FEE_GC_TRIG: not enough space
 *                             FEE_NO_ERROR: success
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcStartCopyWrite
(
    void
)
{
    uint16             Offset;
    uint8             *BufferPtr;
    Fee_JobErrorType   Error;
    Fee_BlockInfoType *BlockInfoPtr;

    Error = FEE_NO_ERROR;
    if (FEE_JOB_FAILED == Fee_GcJobInfo.FlsJobStatus)
    {
        BlockInfoPtr = &Fee_State.BlockInfoPtr[Fee_GcJobInfo.GCCopyIndex];
        if (FEE_GC_COPY_READ_NXTPAGE == Fee_GcJobInfo.GcState)
        {
            /* The block has not been updated when gc is copying this block, otherwise ignore the readding
             * error and copy again */
            if (TRUE == BlockInfoPtr->Copied)
            {
#if (FEE_GC_READ_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
                /* Report read error to DEM FEE_E_GC_READ */
                Dem_ReportErrorStatus(FEE_E_GC_READ, DEM_EVENT_STATUS_FAILED);
#endif
                /* Read fail, discard the block */
                Fee_State.BlockInfoPtr[Fee_GcJobInfo.GCCopyIndex].Consistent = FALSE;
                BlockInfoPtr->Copied = FALSE;
            }
            Error = Fee_LocalGcStartCopy();
        }
        else
        {
            /* Write fail, rewrite aganin, but one block only have one change to rewrite */
            if (Fee_State.IntrJobFailCount == 0U)
            {
                Fee_GcJobInfo.GcDestAddr += Fee_GcJobInfo.LastWriteSize;
                Fee_State.IntrJobFailCount++;
                BlockInfoPtr->Copied = FALSE;
                Error = Fee_LocalGcStartCopy();
            }
            else
            {
                Error = FEE_GC_WRITE;
            }
        }
    }

    if ((FEE_JOB_DONE == Fee_GcJobInfo.FlsJobStatus) &&
        (FEE_GC_COPY_WRITE == Fee_GcJobInfo.GcState))
    {
        /*.FeeIntrJobInfo FeeGcState = FEE_GC_COPY_READ_NXTPAGE(same logical block)
            or FEE_GC_START_COPY(new logical block) */
        Fee_GcJobInfo.GcDestAddr += Fee_GcJobInfo.LastWriteSize;
        Fee_GcJobInfo.BlockPageCount += Fee_GcJobInfo.LastWriteSize >> FEE_PAGE_TO_BYTE_SHIFT;
        /* Find the next block after the block marker is wrote */
        if (Fee_GcJobInfo.BlockPageCount == (Fee_GcJobInfo.GcCurrBlockPageCount + 1U))
        {
            /* Update the Block Info buffer */
            BlockInfoPtr = &Fee_State.BlockInfoPtr[Fee_GcJobInfo.GCCopyIndex];
            if (TRUE == BlockInfoPtr->Copied)
            {
                BlockInfoPtr->Address =
                    Fee_GcJobInfo.GcDestAddr -
                    ((uint32)Fee_GcJobInfo.BlockPageCount << FEE_PAGE_TO_BYTE_SHIFT);
            }

            /* check next block in Fee_LocalGcCheckBlockCopy */
            Fee_GcJobInfo.GCCopyIndex--;
            /* reset the fail count */
            Fee_State.IntrJobFailCount = 0U;
            /* start copy next block */
            Error = Fee_LocalGcStartCopy();
        }
        else if (Fee_GcJobInfo.BlockPageCount == Fee_GcJobInfo.GcCurrBlockPageCount)
        {
            /* Because we can make marker, so set the fls status directly to done for skipping read
                the marker. */
            Fee_GcJobInfo.LastReadSize = 0U;
            Fee_GcJobInfo.FlsJobStatus = FEE_JOB_DONE;
            Fee_GcJobInfo.GcState = FEE_GC_COPY_READ_NXTPAGE;
        }
        else
        {
            /* copy marker page or left data */
            Fee_GcJobInfo.GcState = FEE_GC_COPY_READ_NXTPAGE;
            /* may point to unerasable sector addr */
            Fee_GcJobInfo.GcSrcAddr += Fee_GcJobInfo.LastWriteSize;
            Error = Fee_LocalGcRead((Fls_AddressType)Fee_GcJobInfo.GcSrcAddr);
        }
    }

    if ((FEE_JOB_DONE == Fee_GcJobInfo.FlsJobStatus) &&
        (FEE_GC_COPY_READ_NXTPAGE == Fee_GcJobInfo.GcState))
    {
        Fee_GcJobInfo.GcState = FEE_GC_COPY_WRITE;
        /* #Violation: Fee_c_REF_2 */
        Offset = (uint16)FEE_OFFSETOFWL(Fee_GcJobInfo.GcDestAddr);
        /* If this write does not exceed the wordline, the block is reach to the end. */
        if ((FEE_DFLASH_WORDLINE_SIZE - Offset) >  Fee_GcJobInfo.LastReadSize)
        {
            /* The Block Marker may be damaged, rewrite it */
            BufferPtr = &Fee_RWBuffer[Fee_GcJobInfo.LastReadSize];
            Fee_GcJobInfo.LastReadSize += FEE_DFLASH_PAGE_SIZE;
            /* fill marker page, avoid to read marker page */
            /* #Violation: Fee_c_REF_7 */
            /* #Violation: Fee_c_REF_11 */
            Fee_LocalMakeBlockMarker((Fee_BlockMarkerType *)BufferPtr, Fee_GcJobInfo.GcCurrBlockPageCount);
        }
        Error =
            Fee_LocalGcWrite((Fls_AddressType)Fee_GcJobInfo.GcDestAddr, Fee_GcJobInfo.LastReadSize);
    }

    return Error;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGcErasePrevBank
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles GC process(erase bank).
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : FEE_GC_ERASE: erase error.
 *                             FEE_NO_ERROR: success.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcErasePrevBank
(
    void
)
{
    uint16            BankNumber;
    uint16            Count;
    uint16            Offset;
    uint16            NormalSector;
    Fee_JobErrorType  Error;
    Std_ReturnType    ReturnValue;
#if (FEE_MAX_BADSECTOR_COUNT > 0U)
    Fee_BankInfoType *BankPtr;
    uint8             SectorNumber;
#endif /* (FEE_MAX_BADSECTOR_COUNT \> 0U) */

    Error = FEE_NO_ERROR;
    /* state transfer */
    if (Fee_GcJobInfo.FlsJobStatus >= FEE_JOB_DONE)
    {
        /* record it to bad sector list */
        BankNumber = (Fee_GcJobInfo.GcDestAddr >= FEE_DFLASH_BANK1_BASE) ? 1U : 0U;
#if (STD_ON == FEE_SOFTWARE_VERIFY)
        if (FEE_JOB_DONE == Fee_GcJobInfo.FlsJobStatus)
        {
            /* #Violation: Fee_c_REF_4 */
            ReturnValue = Fls_BlankCheckSync(FEE_REALADDR(Fee_GcJobInfo.GcDestAddr), FEE_DFLASH_PAGE_SIZE);
            if (FLS_BLANKCHECK_EMPTY == ReturnValue)
            {
                /* Check the first and last pages of the Sector*/
                ReturnValue = Fls_BlankCheckSync(
                    /* #Violation: Fee_c_REF_4 */
                    FEE_REALADDR(Fee_GcJobInfo.GcDestAddr + FEE_DFLASH_SECTOR_SIZE - FEE_DFLASH_PAGE_SIZE),
                    FEE_DFLASH_PAGE_SIZE);
                if (ReturnValue != FLS_BLANKCHECK_EMPTY)
                {
                    Fee_GcJobInfo.FlsJobStatus = FEE_JOB_FAILED;
                }
            }
            else
            {
                Fee_GcJobInfo.FlsJobStatus = FEE_JOB_FAILED;
            }
        }
#endif /* (STD_ON \== FEE_SOFTWARE_VERIFY) */

        if (FEE_JOB_FAILED == Fee_GcJobInfo.FlsJobStatus)
        {
#if (FEE_MAX_BADSECTOR_COUNT > 0U)
            BankPtr = &Fee_State.BankInfoPtr[BankNumber];
            if (BankPtr->UnerasableCount < FEE_MAX_BADSECTOR_COUNT)
            {
                SectorNumber = FEE_ADDRTOSECTORNUMBER(Fee_GcJobInfo.GcDestAddr);
                BankPtr->UnerasableSectorNum[BankPtr->UnerasableCount] = SectorNumber;
                Fee_SectorReMap[SectorNumber] = 1U;
                BankPtr->UnerasableCount++;
            }
            else
#endif /* (FEE_MAX_BADSECTOR_COUNT \> 0U) */
            {
                /* Exceeded The maximum number of unerasable sector */
                Error = FEE_GC_ERASE;
                Fee_GcJobInfo.GcState = FEE_GC_FAIL;
            }
        }

        /* next sector address */
        Fee_GcJobInfo.GcDestAddr += FEE_DFLASH_SECTOR_SIZE;
        if ((FEE_GC_FAIL != Fee_GcJobInfo.GcState) &&
            ((Fee_GcJobInfo.GcDestAddr % FEE_DFLASH_BANK_SIZE) == 0U))
        {
            /* reach the end */
            Offset = FEE_DFLASH_BANK_SECTOR_NUM * BankNumber;
            NormalSector = Offset;
            for (Count = Offset; Count < (Offset + FEE_DFLASH_BANK_SECTOR_NUM); Count++)
            {
                if (0U == Fee_SectorReMap[Count])
                {
                    /* find normal sector so map the virtual sector to the normal sector index */
                    Fee_SectorReMap[NormalSector] = (uint8)Count;
                    NormalSector++;
                }
            }

            Fee_GcJobInfo.FlsJobStatus = FEE_JOB_IDLE;
            Fee_GcJobInfo.GcState = FEE_GC_MARK_BANK_OLD_E_SP;
            /* point to bank0's first sector, the address become virtual address from now on. */
            Fee_GcJobInfo.GcDestAddr = Fee_GcJobInfo.GcDestAddr - FEE_DFLASH_BANK_SIZE;
            if (0U != Fee_State.BankInfoPtr[BankNumber].UnerasableCount)
            {
                if (Fee_ConfigPtr->FeeDiscoverNonErasableAreasNotificationPtr != NULL_PTR)
                {
                    Fee_ConfigPtr->FeeDiscoverNonErasableAreasNotificationPtr();
                }
            }
        }
    }

    /* FEE_GC_ERASE_PREV_BANK or FEE_GC_MARK_BANK_OLD_E_SP */
    if (FEE_GC_ERASE_PREV_BANK == Fee_GcJobInfo.GcState)
    {
        /* Backup Fee internal status and mark it before Fls_Write called */
        Fee_GcJobInfo.FlsJobStatus = FEE_JOB_REQSTD;
        /* erase a sector, the erase address is the real fls address */
        /* #Violation: Fee_c_REF_4 */
        ReturnValue = Fls_Erase(FEE_REALADDR(Fee_GcJobInfo.GcDestAddr),
                                (Fls_LengthType)FEE_DFLASH_SECTOR_SIZE);

        /* if the Fls did not accept the request */
        if (ReturnValue != E_OK)
        {
            /* Resume Fee internal status */
            Fee_GcJobInfo.FlsJobStatus = FEE_JOB_IDLE;
            Error = FEE_GC_ERASE;
        }
    }

    return Error;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGcStatePageCompare
 *
 *   Service ID              : None.
 *
 *   Description             : This function compares the state page.
 *
 *   Parameters in           : GcState: Current Gc State
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : FEE_GC_WRITE: write error.
 *                             FEE_NO_ERROR: success.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcStatePageCompare
(
    Fee_GcStatusType GcState
)
{
    uint8             Offset;
    uint8             Count;
    uint16            RemainPages;
    Fee_BankInfoType *BankInfoPtr;
    Fee_JobErrorType  Error;

    Error = FEE_NO_ERROR;
    switch (GcState)
    {
        case FEE_GC_MARK_BANK_NEW_V_SP:
        {
            Fee_GcJobInfo.GcState = FEE_GC_MARK_BANK_NEW_V_M;
            break;
        }
        case FEE_GC_MARK_BANK_NEW_V_M:
        {
            /* current use bank0, erase bank1 */
            Fee_State.BankInfoPtr[Fee_State.CurrBank].UnerasableCount = 0U;
            Offset = FEE_DFLASH_BANK_SECTOR_NUM * Fee_State.CurrBank;
            for (Count = 0U; Count < FEE_DFLASH_BANK_SECTOR_NUM; Count++)
            {
                Fee_SectorReMap[Offset] = 0;
                Offset++;
            }
            /* now we can use new bank due to valid state page is ok */
            Fee_State.CurrBank = Fee_State.CurrBank ^ 1U;
            /* Update FreeWLAddr and StatePage Addr and NextFreePageAddr */
            BankInfoPtr = &Fee_State.BankInfoPtr[Fee_State.CurrBank];
            BankInfoPtr->NextFreeAddr = Fee_GcJobInfo.GcDestAddr + (2U * FEE_DFLASH_PAGE_SIZE);
            Fee_GcJobInfo.GcDestAddr = (1U == Fee_State.CurrBank) ? FEE_DFLASH_BANK0_BASE
                                                                  : FEE_DFLASH_BANK1_BASE;
            /* Block information follows VALID closely */
            Fee_State.NextFreePageAddr = BankInfoPtr->NextFreeAddr;
            /* Move to next state */
            Fee_GcJobInfo.GcState = FEE_GC_ERASE_PREV_BANK;
            /* GC complete the pending write can have chance to be run */
            Fee_UserJobInfo.WaitGc = FALSE;
            if (FEE_WRITE_REQ == Fee_UserJobInfo.PendReqStatus)
            {
                RemainPages = FEE_GETREMAINPAGES(Fee_State.CurrBank, BankInfoPtr->NextFreeAddr);
                if (RemainPages < Fee_UserJobInfo.BlockPages)
                {
                    /* Have not free page to write the pending block. */
                    Error = FEE_GC_TRIG;
                }
            }
            break;
        }
        case FEE_GC_MARK_BANK_OLD_E_SP:
        {
            Fee_GcJobInfo.GcState = FEE_GC_MARK_BANK_OLD_E_M;
            break;
        }
        /* FEE_GC_MARK_BANK_OLD_E_M, do not verify marker */
        default:
        {
            /* update new erased bank's info: Update FreeWLAddr */
            BankInfoPtr = &Fee_State.BankInfoPtr[Fee_State.CurrBank ^ 1U];
            /* When first init the flash, the GcDestAddr will be use for next MainFunction for
               writing valid state page, so update it */
            Fee_GcJobInfo.GcDestAddr += FEE_DFLASH_WORDLINE_SIZE;
            BankInfoPtr->NextFreeAddr = Fee_GcJobInfo.GcDestAddr;
            /* In init gc job, when finish erase and make erase marker in bank 0(current bank is 1), the
               next step is make valid marker so change the state to the FEE_GC_MARK_BANK_NEW_V_SP  */
            if ((FEE_MAIN_INITGC == Fee_State.MainJob) && (Fee_State.CurrBank == 1U))
            {
                Fee_GcJobInfo.GcState = FEE_GC_MARK_BANK_NEW_V_SP;
            }
            else if (FEE_ERASED_USED == BankInfoPtr->State)
            {
                /* The last gc interrupt when copying the block. After re-erasing the target bank, resume
                 * gc */
                BankInfoPtr->State = FEE_ERASED_NOT_USED;
                Fee_GcJobInfo.GcState = FEE_GC_REQUESTED;
            }
            else
            {
                Fee_GcJobInfo.GcState = FEE_GC_IDLE;
                Fee_State.MainJob = FEE_MAIN_NONE;
            }
            break;
        }
    }

    return Error;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGcProgramStatePage
 *
 *   Service ID              : None.
 *
 *   Description             : This function writes the state page.
 *
 *   Parameters in           : GcState: Current Gc State
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : FEE_GC_TRIG: not enough space.
 *                             FEE_GC_WRITE: write error.
 *                             FEE_NO_ERROR: success
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Fee_JobErrorType, FEE_PRIVATE_CODE) Fee_LocalGcProgramStatePage
(
    Fee_GcStatusType GcState
)
{
    uint8                     NewCount;
    uint32                    GcNumber;
    uint32                    Addr;
    uint16                    Size;
    uint16                    Count;
    uint32                   *MarkerPtr;
    uint16                    RemainingPages;
    Fee_JobErrorType          Error;
    Fee_ErasePageHeaderType  *ErasePageHeaderPtr;
    Fee_ValidPageHeaderType  *ValidPageHeaderPtr;
    Fee_BankInfoType         *BankInfoPtr;
#if (FEE_MAX_BADSECTOR_COUNT > 0U)
    uint32                   *UnerasableSectorPtr;
#endif /* (STD_ON \== FEE_SOFTWARE_VERIFY) */

    /*state transfer*/
    Error = FEE_NO_ERROR;
    if (Fee_GcJobInfo.FlsJobStatus >= FEE_JOB_DONE)
    {
        if (FEE_JOB_FAILED == Fee_GcJobInfo.FlsJobStatus)
        {
            if ((FEE_GC_MARK_BANK_NEW_V_M == Fee_GcJobInfo.GcState) ||
                (FEE_GC_MARK_BANK_OLD_E_M == Fee_GcJobInfo.GcState))
            {
                /* Ignore marker write fail, becase only need check marker whether it's dirty. */
                Fee_GcJobInfo.FlsJobStatus = FEE_JOB_DONE;
            }
            /* if it's state page body, rewrite aganin, but state page only have one change to rewrite */
            else if (Fee_State.IntrJobFailCount == 0U)
            {
                Fee_State.IntrJobFailCount++;
                Fee_GcJobInfo.GcDestAddr += FEE_DFLASH_WORDLINE_SIZE;
                Fee_GcJobInfo.FlsJobStatus = FEE_JOB_IDLE;
            }
            else
            {
                Error = FEE_GC_WRITE;
            }
        }

        if (FEE_JOB_DONE == Fee_GcJobInfo.FlsJobStatus)
        {
            /* switch state or return Error
             * FEE_GC_MARK_BANK_NEW_V_SP ==> FEE_GC_MARK_BANK_NEW_V_M
             * FEE_GC_MARK_BANK_NEW_V_M ==> FEE_GC_ERASE_PREV_BANK
             * FEE_GC_ERASE_PREV_BANK ==> FEE_GC_MARK_BANK_OLD_E_SP
             * FEE_GC_MARK_BANK_OLD_E_SP ==> FEE_GC_MARK_BANK_OLD_E_M
             */
            Error = Fee_LocalGcStatePageCompare(GcState);
            Fee_State.IntrJobFailCount = 0U;
            Fee_GcJobInfo.FlsJobStatus = FEE_JOB_IDLE;
        }
    }
    else
    {
        /* prepare data and commit write job */
        switch (GcState)
        {
            /* program valid state page for new bank */
            case FEE_GC_MARK_BANK_NEW_V_SP:
            /* program erase state page for old bank */
            case FEE_GC_MARK_BANK_OLD_E_SP:
            {
                Size = FEE_DFLASH_PAGE_SIZE;
                BankInfoPtr = &Fee_State.BankInfoPtr[Fee_State.CurrBank ^ 1U];
                /* #Violation: Fee_c_REF_7 */
                /* #Violation: Fee_c_REF_11 */
                for (Count = 0U; Count < FEE_VIRTUAL_PAGE_SIZE; Count++)
                {
                    /* Padding 0 */
                    Fee_RWBuffer[Count] = 0U;
                }
                if (FEE_GC_MARK_BANK_NEW_V_SP == GcState)
                {
                    /* #Violation: Fee_c_REF_7 */
                    /* #Violation: Fee_c_REF_11 */
                    ValidPageHeaderPtr = (Fee_ValidPageHeaderType *)Fee_RWBuffer;
                    /* Write Valid Bank Information */
                    ValidPageHeaderPtr->TailTag = FEE_STATEPAGE_DATA_TAG;
                    ValidPageHeaderPtr->Tag = FEE_STATEPAGE_VALID_HEADER;
                    /* Write valid tag status. Interrupt and restart GC to identify which one is for the
                       new bank  1 => 2 => 3 => 1 */
                    NewCount = (Fee_State.BankInfoPtr[Fee_State.CurrBank].StateCount % 3U) + 1U;
                    BankInfoPtr->StateCount = NewCount;
                    ValidPageHeaderPtr->StateCount = NewCount;
                    GcNumber = Fee_State.BankInfoPtr[Fee_State.CurrBank].GcNumber + 1U;
                    BankInfoPtr->GcNumber = GcNumber;
                    ValidPageHeaderPtr->GcNumber = GcNumber;
                    /* VALID information wordline alignment */
                    /* #Violation: Fee_c_REF_2 */
                    Fee_GcJobInfo.GcDestAddr = FEE_GETWLBEGINNING(
                        Fee_GcJobInfo.GcDestAddr + FEE_DFLASH_WORDLINE_SIZE - FEE_DFLASH_PAGE_SIZE);
                }
                /* FEE_GC_MARK_BANK_OLD_E_SP */
                else
                {
                    /* #Violation: Fee_c_REF_7 */
                    /* #Violation: Fee_c_REF_11 */
                    ErasePageHeaderPtr = (Fee_ErasePageHeaderType *)Fee_RWBuffer;
                    /* data in Fee_RWBuffer,
                       FeeCurrBank has switch to new bank after valid state page finish */
                    ErasePageHeaderPtr->TailTag = FEE_STATEPAGE_DATA_TAG;
                    ErasePageHeaderPtr->Tag = FEE_STATEPAGE_ERASE_HEADER;
#if (FEE_MAX_BADSECTOR_COUNT > 0U)
                    /* Write Erase Bank Information(Number of non erasable areas) */
                    ErasePageHeaderPtr->BadSectorNum = BankInfoPtr->UnerasableCount;

                    /* #Violation: Fee_c_REF_7 */
                    /* #Violation: Fee_c_REF_11 */
                    UnerasableSectorPtr = (uint32 *)&Fee_RWBuffer[FEE_DFLASH_PAGE_SIZE];
                    /* Write Erase Bank Information(non erasable areas sector number) */
                    for (Count = 0U; Count < BankInfoPtr->UnerasableCount; Count++)
                    {
                        UnerasableSectorPtr[Count] = FEE_STATEPAGE_BAD_TAG;
                        UnerasableSectorPtr[Count] |= (uint32)BankInfoPtr->UnerasableSectorNum[Count]
                                                      << FEE_UNERASABLE_SECTOR_OFFSET;
                    }
                    /* Calculate how many bytes need to be written */
                    while (0U != (Count % FEE_MAX_UNERASABLE_INFO_IN_PAGE))
                    {
                        UnerasableSectorPtr[Count] = 0U;
                        Count++;
                    }
                    Size += Count * FEE_UNERASABLE_INFO_SIZE;
#else
                    ErasePageHeaderPtr->BadSectorNum = 0U;
#endif /* (FEE_MAX_BADSECTOR_COUNT \> 0U) */
                }

                RemainingPages = FEE_GETREMAINPAGES(Fee_State.CurrBank ^ 1U, Fee_GcJobInfo.GcDestAddr);
                if (RemainingPages < (FEE_DFLASH_WORDLINE_SIZE >> FEE_PAGE_TO_BYTE_SHIFT))
                {
                    Error = FEE_GC_TRIG;
                }
                else
                {
                    Error = Fee_LocalGcWrite((Fls_AddressType)Fee_GcJobInfo.GcDestAddr, Size);
                }
                break;
            }
            /* FEE_GC_MARK_BANK_NEW_V_M, write new bank's valid state page's marker page
               FEE_GC_MARK_BANK_OLD_E_M  */
            default:
            {
                /* Write Bank Marker information into Buffer */
                /* #Violation: Fee_c_REF_7 */
                /* #Violation: Fee_c_REF_11 */
                MarkerPtr = (uint32 *)Fee_RWBuffer;
                for (Count = 0U; Count < (FEE_DFLASH_PAGE_SIZE >> FEE_WORD_TO_BYTE_SHIFT); Count++)
                {
                    *MarkerPtr = FEE_STATEPAGE_MARKER_TAG;
                    MarkerPtr++;
                }
                Addr = Fee_GcJobInfo.GcDestAddr + Fee_GcJobInfo.LastWriteSize;
                Error = Fee_LocalGcWrite((Fls_AddressType)Addr, FEE_STATEPAGE_MARKER_SIZE);
                break;
            }
        }
    }

    return Error;
}

/****************************************************************************************************
 *   Function Name           : Fee_LocalGC
 *
 *   Service ID              : None.
 *
 *   Description             : This function handles inner GC job.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(void, FEE_PRIVATE_CODE) Fee_LocalGC
(
    void
)
{
    Fee_JobErrorType Error;

    Error = FEE_NO_ERROR;

    /* Writing a page of a block */
    if ((FEE_GC_COPY_WRITE == Fee_GcJobInfo.GcState) ||
        (FEE_GC_COPY_READ_NXTPAGE == Fee_GcJobInfo.GcState))
    {
        /* state transfer:
         .FeeIntrJobInfo FeeGcState = FEE_GC_COPY_READ_NXTPAGE(same logical block)
          due to this process is behind Fee_LocalGcStartCopy, it will be processed next mainFunction,
          so read/write job can be inserted at this time
          operation:
          issue Fls_Write, and stay FEE_GC_COPY_WRITE */
        Error = Fee_LocalGcStartCopyWrite();
    }

    /* This is gc Entrance, because after this call the gc state is change to FEE_GC_READ_NETPAGE but 
       the read job is not return, no nead to run Fee_LocalGcStartCopyWrite.  */
    if ((FEE_GC_REQUESTED == Fee_GcJobInfo.GcState) && (Error == FEE_NO_ERROR))
    {
        /* \==>FEE_GC_READ_NETPAGE */
        Error = Fee_LocalGcRequested();
    }

    /* Writing the valid state page content */
    if ((FEE_GC_MARK_BANK_NEW_V_SP == Fee_GcJobInfo.GcState) && (Error == FEE_NO_ERROR))
    {
        /* All block data copies are completed and ready
           to write Valid bank information for the new bank */
        /* \==> FEE_GC_MARK_BANK_NEW_V_M */
        Error = Fee_LocalGcProgramStatePage(FEE_GC_MARK_BANK_NEW_V_SP);
    }

    /* Erasing the previous sector is done here (initGcNormal may start from here). Because
       FEE_GC_MARK_BANK_NEW_V_M step could change gc state to FEE_GC_ERASE_PREV_BANK, let the step before
       FEE_GC_MARK_BANK_NEW_V_M so this step will be run in the next mainFunction, and the write and read
       request can insert before the erase. */
    if ((FEE_GC_ERASE_PREV_BANK == Fee_GcJobInfo.GcState) && (Error == FEE_NO_ERROR))
    {
        /* case1 : issue fls_erase and stay FEE_GC_ERASE_PREV_BANK,
          case2 : when finish erase , ==> FEE_GC_MARK_BANK_OLD_E_SP */
        Error = Fee_LocalGcErasePrevBank();
    }

    /* Writing the valid state page marker */
    if ((FEE_GC_MARK_BANK_NEW_V_M == Fee_GcJobInfo.GcState) && (Error == FEE_NO_ERROR))
    {
        /*.FeeIntrJobInfo FeeGcState \==> FEE_GC_ERASE_PREV_BANK; */
        Error = Fee_LocalGcProgramStatePage(FEE_GC_MARK_BANK_NEW_V_M);
    }

    /* Writing the erased state page content */
    if ((FEE_GC_MARK_BANK_OLD_E_SP == Fee_GcJobInfo.GcState) && (Error == FEE_NO_ERROR))
    {
        /* when finish, \==>FEE_GC_MARK_BANK_OLD_E_M */
        Error = Fee_LocalGcProgramStatePage(FEE_GC_MARK_BANK_OLD_E_SP);
    }

    /* Writing the erased state page marker */
    if ((FEE_GC_MARK_BANK_OLD_E_M == Fee_GcJobInfo.GcState) && (Error == FEE_NO_ERROR))
    {
        /* when finish, \==>FEE_GC_IDLE */
        Error = Fee_LocalGcProgramStatePage(FEE_GC_MARK_BANK_OLD_E_M);
    }

    if (Error != FEE_NO_ERROR)
    {
        /* Enter GC Fail state */
        Fee_GcJobInfo.GcState = FEE_GC_FAIL;
        Fee_State.MainJob = FEE_MAIN_NONE;
#if (FEE_GC_WRITE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
        /* Report gc write error to Dem */
        if (FEE_GC_WRITE == Error)
        {
            Dem_ReportErrorStatus(FEE_E_GC_WRITE, DEM_EVENT_STATUS_FAILED);
        }
#endif
#if (FEE_GC_READ_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
        /* Report gc read error to Dem */
        if (FEE_GC_READ == Error)
        {
            Dem_ReportErrorStatus(FEE_E_GC_READ, DEM_EVENT_STATUS_FAILED);
        }
#endif
#if (FEE_GC_ERASE_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
        /* Report gc erase error to Dem */
        if (FEE_GC_ERASE == Error)
        {
            Dem_ReportErrorStatus(FEE_E_GC_ERASE, DEM_EVENT_STATUS_FAILED);
        }
#endif
#if (FEE_GC_TRIG_DEM_REPORT == FEE_ENABLE_DEM_REPORT)
        /* Report gc trigger gc error to Dem */
        if (FEE_GC_TRIG == Error)
        {
            Dem_ReportErrorStatus(FEE_E_GC_TRIG, DEM_EVENT_STATUS_FAILED);
        }
#endif
        if (Fee_ConfigPtr->FeeUnavailableFailureNotificationPtr != NULL_PTR)
        {
            Fee_ConfigPtr->FeeUnavailableFailureNotificationPtr();
        }
    }
}

#if (STD_ON == FEE_DEV_ERROR_DETECT)
/****************************************************************************************************
 *   Function Name           : Fee_LocalCommonDetCheck
 *
 *   Service ID              : None.
 *
 *   Description             : This is a common DET check function.
 *
 *   Parameters in           : ServiceID: API function is ServiceID.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : E_OK: There is no Det error.
 *                             E_NOT_OK: There is a Det error.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_LocalCommonDetCheck
(
    uint8 ServiceID
)
{
    Std_ReturnType ReturnValue;
    Mcal_CoreType  CoreId;

    ReturnValue = E_NOT_OK;
    /* Get core id which is executing currently */
    /* #Violation: Fee_c_REF_2 */
    CoreId = Mcal_GetCoreId();
    if (FEE_CORE_ALLOCATION != (uint8)CoreId)
    {
        FEE_REPORTERROR(ServiceID, FEE_E_CORE_NOT_CONFIGURED);
    }
    /* If status is MEMIF_UNINIT, report DET FEE_E_UNINIT. [SWS_Fee_00123] */
    /* \[SWS_Fee_00121], [SWS_Fee_00122], [SWS_Fee_00124], [SWS_Fee_00126] */
    else if (MEMIF_UNINIT == Fee_Init_Status)
    {
        FEE_REPORTERROR(ServiceID, FEE_E_UNINIT);
    }
    else
    {
        ReturnValue = E_OK;
    }

    return ReturnValue;
}
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */

/****************************************************************************************************
 *   Function Name           : Fee_LocalSkipRead
 *
 *   Service ID              : None.
 *
 *   Description             : Read the data from flash and skip the crossed bad sector.
 *
 *   Parameters in           : SrcAddr: The source address where to read.
 *                             ReadLength: The length of read data.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : E_OK: Success.
 *                             E_NOT_OK: The fls moudle not accepted this read.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(Std_ReturnType, FEE_PRIVATE_CODE) Fee_LocalSkipRead
(
    uint32 SrcAddr,
    uint32 ReadLength
)
{
    uint32           SectorRemain;
    uint32           SectorNo;
    uint32           ActReadLength;
    Std_ReturnType   ReturnStatus;

    ActReadLength = ReadLength;
    /* #Violation: Fee_c_REF_2 */
    SectorRemain = FEE_SECTOR_SIZE - FEE_OFFSETOFSECTOR(SrcAddr);
    Fee_SkipReadStatus.Remain = 0U;

    if (SectorRemain < ReadLength)
    {
        /* #Violation: Fee_c_REF_2 */
        SectorNo = FEE_ADDRTOSECTORNUMBER(SrcAddr);
        /* Cross sector reading, so the sectorNo is less than the last sectorNo */
        if ((Fee_SectorReMap[SectorNo + 1U] -
             Fee_SectorReMap[SectorNo]) > 1U)
        {
            /* Cross sector and the next sector is unusable so should split in two reading and the
               next reading will skip the unusable sector. */
            Fee_SkipReadStatus.Remain = ReadLength - SectorRemain;
            Fee_SkipReadStatus.ResumeBufferPtr = &Fee_RWBuffer[SectorRemain];
            /* #Violation: Fee_c_REF_4 */
            Fee_SkipReadStatus.ResumeSrcAddr = FEE_MAPADDR(SrcAddr + SectorRemain);
            ActReadLength = SectorRemain;
        }
    }

    /* #Violation: Fee_c_REF_4 */
    ReturnStatus = Fls_Read(FEE_MAPADDR(SrcAddr), Fee_RWBuffer, (Fls_LengthType)ActReadLength);

    return ReturnStatus;
}

/****************************************************************************************************
*   Function Name           : Fee_LocalGetStatus
*
*   Service ID              : None.
*
*   Description             : Get the current status of the Fee module.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : MemIf_StatusType: Current status of fee module.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(MemIf_StatusType, FEE_PRIVATE_CODE) Fee_LocalGetStatus
(
    void
)
{
    MemIf_StatusType ReturnStatus;

    /* Return MEMIF_UNINIT, if module has not (yet) been initialized. [SWS_Fee_00034] */
    if (MEMIF_UNINIT == Fee_Init_Status)
    {
        ReturnStatus = MEMIF_UNINIT;
    }
    /* Return MEMIF_BUSY, if it's currently processing request. [SWS_Fee_00129] */
    else if (Fee_UserJobInfo.PendReqStatus != FEE_PEND_NO_REQ)
    {
        ReturnStatus = MEMIF_BUSY;
    }
    else if (FEE_MAIN_INITGC == Fee_State.MainJob)
    {
        ReturnStatus = MEMIF_BUSY_INTERNAL;
    }
    /* \[SWS_Fee_00074] internal activities */
    else if ((Fee_GcJobInfo.GcState != FEE_GC_IDLE) && (FEE_GC_FAIL != Fee_GcJobInfo.GcState))
    {
#if (STD_ON == FEE_GC_RESTART_WRITE)
        if (FALSE == Fee_State.FeeWriteAPICalled)
        {
            ReturnStatus = MEMIF_IDLE;
        }
        else
#endif /* STD_ON \== FEE_GC_RESTART_WRITE */
        {
            ReturnStatus = MEMIF_BUSY_INTERNAL;
        }
    }
    /* return MEMIF_IDLE if the module is neither processing a request from the upper layer nor is
     * it doing an internal management operation. [SWS_Fee_00128] */
    else
    {
        ReturnStatus = MEMIF_IDLE;
    }

    return ReturnStatus;
}

/****************************************************************************************************
*   Function Name           : Fee_InitializeModuleAndBanks
*
*   Service ID              : None
*
*   Description             : Initializes the Fee module state and processes all banks initialization.
*
*   Parameters in           : ConfigPtr: Pointer to Fee configuration.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : Parameters validated.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, FEE_PRIVATE_CODE) Fee_InitializeModuleAndBanks
(
    P2CONST(Fee_ConfigType, AUTOMATIC, FEE_CONFIG_CONST) ConfigPtr
)
{
    uint8  BankNumber;
    uint32 Count;
    uint8  FeeFailRetryNumber;
    uint16 RetVal;
    uint8  State;
    uint32 CurrBankSrcAddr;

    State = FEE_STATELESS;
    Fee_ConfigPtr = ConfigPtr;
    /* Traverses the two bank and fetch block info and manage info on the bank. */
    for (BankNumber = 0U; (BankNumber < FEE_DFLASH_BANK_NUM) && (FEE_FLS_ERROR != State); BankNumber++)
    {
        for (Count = 0U; Count < FEE_MAX_BLOCK_COUNT; Count++ )
        {
            Fee_BlockInfos[BankNumber][Count].Consistent = FALSE;
            Fee_BlockInfos[BankNumber][Count].Valid = FALSE;
            Fee_BlockInfos[BankNumber][Count].BlockCycleCount = 0U;
        }

        FeeFailRetryNumber = 0U;
        State = FEE_STATELESS;
        CurrBankSrcAddr = FEE_DFLASH_BANK_SIZE * (uint32)BankNumber;
        /* search erase state page, because all allowed bad sector may locate in front of bank,
            when fail to find state page, should retry next sector until reach the max bad sector
            count. */
        while (FeeFailRetryNumber <= FEE_MAX_BADSECTOR_COUNT)
        {
            /* Check if there is erase state page information at this position. If it fails, try again
             * at the next wordline position, as the state page may have been rewritten once. */
            for (Count = 0U; (Count < FEE_MAX_RETRY_TIMES) && (FEE_STATELESS == State); Count++)
            {
                State = Fee_LocalCheckEraseStatePage(CurrBankSrcAddr);
                CurrBankSrcAddr += FEE_DFLASH_WORDLINE_SIZE;
            }

            if (FEE_STATELESS == State)
            {
                FeeFailRetryNumber++;
                /* #Violation: Fee_c_REF_2 */
                CurrBankSrcAddr = FEE_GETSECTORBEGINNING(FEE_DFLASH_SECTOR_SIZE + CurrBankSrcAddr);
            }
            else
            {
                Fee_BankInfo[BankNumber].NextFreeAddr =
                    (FEE_DFLASH_BANK_SIZE * (uint32)BankNumber) + (Count * FEE_DFLASH_WORDLINE_SIZE);
                FeeFailRetryNumber = FEE_MAX_BADSECTOR_COUNT + 1U;
            }
        }

        if (FEE_ERASED == State)
        {
            /* when find erase sate page, next step is traverse the bank to find block and valid
                * info */
            RetVal = Fee_LocalTraversalUpdateBlockInfo(BankNumber);
            if (FLS_READ_BUSY == RetVal)
            {
                State = FEE_FLS_ERROR;
            }
        }
    }

    if (FEE_FLS_ERROR == State)
    {
        /* Fls busy. Abort Fee init */
        if (Fee_ConfigPtr->FeeUnavailableFailureNotificationPtr != NULL_PTR)
        {
            Fee_ConfigPtr->FeeUnavailableFailureNotificationPtr();
        }
        FEE_REPORTERROR(FEE_INIT_ID, FEE_E_INIT_FAILED);
    }
    else
    {
        /* The init function is a sync, so when init function return, we can use write and read
            FEE API */
        Fee_Init_Status = MEMIF_IDLE;
        /* Select the operation to be executed based on the status of Fee module */
        Fee_LocalSetInitGc();
    }
}
/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fee_c_REF_8 */
#include "Fee_MemMap.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Fee_c_REF_5 */
#define FEE_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fee_c_REF_8 */
#include "Fee_MemMap.h"

/****************************************************************************************************
 *   Function Name           : Fee_Init
 *
 *   Service ID              : 0x00.
 *
 *   Description             : This function initializes the FEE module.
 *
 *   Parameters in           : ConfigPtr: Pointer to the selected configuration set
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Asynchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00085.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(void, FEE_PUBLIC_CODE) Fee_Init
(
    P2CONST(Fee_ConfigType, AUTOMATIC, FEE_CONFIG_CONST) ConfigPtr
)
{
    uint32 Count;
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Mcal_CoreType CoreId;

    /* Get core id which is executing currently */
    /* #Violation: Fee_c_REF_2 */
    CoreId = Mcal_GetCoreId();
    if (FEE_CORE_ALLOCATION != (uint8)CoreId)
    {
        FEE_REPORTERROR(FEE_INIT_ID, FEE_E_CORE_NOT_CONFIGURED);
    }
    else if (NULL_PTR == ConfigPtr)
    {
        /* The configuration pointer ConfigPtr shall always have a NULL_PTR value.
               Refer to \[SWS_Fee_00189] */
        FEE_REPORTERROR(FEE_INIT_ID, FEE_E_INIT_FAILED);
    }
    else
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */
    {
        /* Reset the gc and user job, for reinit  */
        Fee_State.MainJob = FEE_MAIN_NONE;
        Fee_State.BankInfoPtr = Fee_BankInfo;
        Fee_State.FeeWriteAPICalled = FALSE;
        Fee_State.IntrJobFailCount = 0U;
        Fee_State.UnConfigBlockCount = 0U;
        Fee_State.UncfgBlksExceeded = 0U;
        Fee_GcJobInfo.GcState = FEE_GC_IDLE;
        Fee_GcJobInfo.FlsJobStatus = FEE_JOB_IDLE;
        Fee_UserJobInfo.PendReqStatus = FEE_PEND_NO_REQ;
        Fee_UserJobInfo.FlsJobStatus = FEE_JOB_IDLE;
        Fee_UserJobInfo.FeeSetModeReqPend = FALSE;
        Fee_State.BankInfoPtr[0].State = FEE_STATELESS;
        Fee_State.BankInfoPtr[1].State = FEE_STATELESS;
        for (Count = 0U; Count < FEE_SECTOR_NUMBER; Count++)
        {
            Fee_SectorReMap[Count] = 0U;
        }

        Fee_InitializeModuleAndBanks(ConfigPtr);
    }
}

#if (STD_ON == FEE_SETMODE_API)
/****************************************************************************************************
 *   Function Name           : Fee_SetMode
 *
 *   Service ID              : 0x01.
 *
 *   Description             : This function calls Fls_SetMode.
 *
 *   Parameters in           : MemIf_ModeType: Desired mode for the underlying flash driver.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00086.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(void, FEE_PUBLIC_CODE) Fee_SetMode
(
    MemIf_ModeType Mode
)
{
    MemIf_StatusType FeeStatus;
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Std_ReturnType DetCheckResult;

    DetCheckResult = Fee_LocalCommonDetCheck(FEE_SETMODE_ID);
    if (E_OK == DetCheckResult)
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */
    {
        /* Get the FEE status */
        FeeStatus = Fee_LocalGetStatus();
        /* Check if the module state is MEMIF_BUSY. [SWS_Fee_00170] */
        if ((MEMIF_IDLE == FeeStatus) || (MEMIF_BUSY_INTERNAL == FeeStatus))
        {
            /* If status is OK, and hardware support the given "Mode". */
            /* Then Fee_SetMode calls the Fls_SetMode. [SWS_Fee_00020] */
            Fee_UserJobInfo.FeeSetModeReqPend = TRUE;
            Fee_UserJobInfo.Mode = Mode;
        }
        else
        {
            /* \[SWS_Fee_00170] If busy, report error */
            FEE_REPORTRUNTIMEERROR(FEE_SETMODE_ID, FEE_E_BUSY);
        }
    }
}
#endif /* (STD_ON \== FEE_SETMODE_API) */

/****************************************************************************************************
 *   Function Name           : Fee_Read
 *
 *   Service ID              : 0x02.
 *
 *   Description             : This function initiate a read job.
 *
 *   Parameters in           : BlockNumber: Logical Block Number.
 *                             BlockOffset: Read address offset inside the block
 *                             Length: Number of bytes to read
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : DataBufferPtr: Pointer to data buffer
 *
 *   Sync/Async              : Asynchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: job accepted
 *                             E_NOT_OK: job declined
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00087.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_Read
(
    uint16 BlockNumber,
    uint16 BlockOffset,
    P2VAR(uint8, AUTOMATIC, FEE_APPL_DATA) DataBufferPtr,
    uint16 Length
)
{
    uint16                  BlockIndex;
    Std_ReturnType          ReturnValue;
    MemIf_StatusType        FeeStatus;
    boolean                 ConsistentFlag;
    boolean                 ValidFlag;
    Fee_BlockInfoType const *BlockInfoPtr;

#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Std_ReturnType DetCheckResult;
    uint16         BlockSize;
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */

#if (STD_OFF == FEE_DEV_ERROR_DETECT)
    /* Return the configuration set array Index corresponding to BlockNumber */
    BlockIndex = Fee_LocalGetUsrBlockIndex(BlockNumber);
#else  /* (STD_OFF \== FEE_DEV_ERROR_DETECT) */
    ReturnValue = E_NOT_OK;
    DetCheckResult = Fee_LocalCommonDetCheck(FEE_READ_ID);
    if (E_OK == DetCheckResult)
    {
        /* Return the configuration set array Index corresponding to BlockNumber */
        BlockIndex = Fee_LocalGetUsrBlockIndex(BlockNumber);
        /* \[SWS_Fee_00134] BlockNumber exists */
        if (FEE_LOG_BLOCK_NOT_FOUND == BlockIndex)
        {
            FEE_REPORTERROR(FEE_READ_ID, FEE_E_INVALID_BLOCK_NO);
        }
        /* \[SWS_Fee_00136] buffer pointer is non-NULL */
        else if (NULL_PTR == DataBufferPtr)
        {
            FEE_REPORTERROR(FEE_READ_ID, FEE_E_PARAM_POINTER);
        }
        /* additional check */
        else if (0U == Length)
        {
            FEE_REPORTERROR(FEE_READ_ID, FEE_E_INVALID_BLOCK_LEN);
        }
        else
        {
            BlockSize = Fee_ConfigPtr->FeeBlockConfigPtr[BlockIndex].BlockSize;
            /* \[SWS_Fee_00135] offset is valid i.e. within the block size */
            if (BlockOffset >= BlockSize)
            {
                FEE_REPORTERROR(FEE_READ_ID, FEE_E_INVALID_BLOCK_OFS);
            }
            /* \[SWS_Fee_00137] Length is valid */
            else if ((BlockOffset + Length) > BlockSize)
            {
                FEE_REPORTERROR(FEE_READ_ID, FEE_E_INVALID_BLOCK_LEN);
            }
            else
            {
                ReturnValue = E_OK;
            }
        }
    }

    /* If read request is rejected, shall not change status or job result. [SWS_Fee_00162] */
    if (ReturnValue != E_NOT_OK)
#endif /* (STD_OFF \== FEE_DEV_ERROR_DETECT) */
    {
        /* Execute if there is no pending request. [SWS_Fee_00133] */
        FeeStatus = Fee_LocalGetStatus();
        if ((MEMIF_IDLE == FeeStatus) || (MEMIF_BUSY_INTERNAL == FeeStatus))
        {
            /* Store the read request parameters. [SWS_Fee_00022] */
            /* Asynchronous execution of read operations. [SWS_Fee_00073] */
            Fee_UserJobInfo.PendReqStatus = FEE_READ_REQ;
            Fee_UserJobInfo.BlockNumber = BlockNumber;
            Fee_UserJobInfo.BlockOffset = BlockOffset;
            Fee_UserJobInfo.ReadDataBufferPtr = DataBufferPtr;
            Fee_UserJobInfo.Length = Length;
            Fee_UserJobInfo.BlockIndex = BlockIndex;
            /* Return MEMIF_JOB_PENDING if the requested job is still waiting for execution or */
            /* is currently being executed. [SWS_Fee_00156], [SWS_Fee_00155]*/
            Fee_UserJobInfo.JobResult = MEMIF_JOB_PENDING;

            BlockInfoPtr = &(Fee_State.BlockInfoPtr[BlockIndex]);
            ConsistentFlag = BlockInfoPtr->Consistent;
            ValidFlag = BlockInfoPtr->Valid;
            /* If the logical block is inconsistent */
            /* If this logical block does not exist, will be here too. */
            if ((ConsistentFlag != TRUE) || (ValidFlag != TRUE))
            {
                /* The FEE module shall manage for each block the information, */
                /* whether this block is correct. Refer to [SWS_Fee_00049] */
                /* Set the job result to MEMIF_BLOCK_INCONSISTENT. */
                /* \[SWS_Fee_00159], [SWS_Fee_00155], [SWS_Fee_00023] */
                /* Set the job result to MEMIF_BLOCK_INVALID. [SWS_Fee_00160], [SWS_Fee_00155],
                 * [SWS_Fee_00075] */
                Fee_UserJobInfo.FlsJobStatus = FEE_JOB_FAILED;
                Fee_UserJobInfo.JobResultPending = (ConsistentFlag != TRUE) ? MEMIF_BLOCK_INCONSISTENT
                                                                               : MEMIF_BLOCK_INVALID;
            }
            else
            {
                /* Calculates the start position of the page where the read starts. */
                Fee_UserJobInfo.CurrBankSrcAddr =
                    BlockInfoPtr->Address +
                    ((((uint32)BlockOffset + FEE_BLOCK_HEADER_SIZE - 1U) / FEE_USER_PAGE_BYTE_COUNT) *
                        FEE_DFLASH_PAGE_SIZE);
                /* the first page contains data at BlockOffset */
                Fee_UserJobInfo.BlockOffset =
                    ((BlockOffset + FEE_BLOCK_HEADER_SIZE - 1U) % FEE_USER_PAGE_BYTE_COUNT) + 1U;
            }
            ReturnValue = E_OK;
        }
        else
        {
            /* \[SWS_Fee_00133] FEE is busy with another request */
            FEE_REPORTRUNTIMEERROR(FEE_READ_ID, FEE_E_BUSY);
            /* \[SWS_Fee_00172] */
            ReturnValue = E_NOT_OK;
        }
    }

    return ReturnValue;
}

/****************************************************************************************************
 *   Function Name           : Fee_Write
 *
 *   Service ID              : 0x03.
 *
 *   Description             : This function initiate a write job.
 *
 *   Parameters in           : BlockNumber: Logical Block Number.
 *                             DataBufferPtr: Pointer to data buffer
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Asynchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: job accepted
 *                             E_NOT_OK: job declined
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00088.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_Write
(
    uint16 BlockNumber,
    P2CONST(uint8, AUTOMATIC, FEE_APPL_CONST) DataBufferPtr
)
{
    uint16           BlockIndex;
    Std_ReturnType   ReturnValue;
    MemIf_StatusType FeeStatus;
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Std_ReturnType DetCheckResult;
#endif /* (STD_OFF \== FEE_DEV_ERROR_DETECT) */

#if (STD_OFF == FEE_DEV_ERROR_DETECT)
    /* Return the configuration set array Index corresponding to BlockNumber */
    BlockIndex = Fee_LocalGetUsrBlockIndex(BlockNumber);
#else  /* (STD_OFF \== FEE_DEV_ERROR_DETECT) */
    ReturnValue = E_NOT_OK;
    DetCheckResult = Fee_LocalCommonDetCheck(FEE_WRITE_ID);
    if (E_OK == DetCheckResult)
    {
        /* Return the configuration set array Index corresponding to BlockNumber */
        BlockIndex = Fee_LocalGetUsrBlockIndex(BlockNumber);
        /* \[SWS_Fee_00138]  block number is correct */
        if (FEE_LOG_BLOCK_NOT_FOUND == BlockIndex)
        {
            FEE_REPORTERROR(FEE_WRITE_ID, FEE_E_INVALID_BLOCK_NO);
        }
        /* \[SWS_Fee_00139] Check if the buffer pointer is NULL */
        else if (NULL_PTR == DataBufferPtr)
        {
            FEE_REPORTERROR(FEE_WRITE_ID, FEE_E_PARAM_POINTER);
        }
        else
        {
            ReturnValue = E_OK;
        }
    }
    if (ReturnValue != E_NOT_OK)
#endif /* (STD_OFF \== FEE_DEV_ERROR_DETECT) */
    {
        /* \[SWS_Fee_00025] MEMIF_IDLE or MEMIF_BUSY_INTERNAL, accept the write request */
        FeeStatus = Fee_LocalGetStatus();
        if ((MEMIF_IDLE == FeeStatus) || (MEMIF_BUSY_INTERNAL == FeeStatus))
        {
            Fee_UserJobInfo.BlockInvalidReq = FALSE;
            Fee_LocalHandleUserWriteReq(BlockIndex, DataBufferPtr);
            ReturnValue = E_OK;
        }
        else
        /* If status is MEMIF_BUSY, Report DET FEE_E_BUSY, and return E_NOT_OK. [SWS_Fee_00144] */
        {
            /* FEE status is MEMIF_BUSY, job request and return with E_NOT_OK. [SWS_Fee_00174] */
            /* \[SWS_Fee_00144]  BUSY DET */
            FEE_REPORTRUNTIMEERROR(FEE_WRITE_ID, FEE_E_BUSY);
            ReturnValue = E_NOT_OK;
        }
    }
    /* If write request is rejected, shall not change status or job result. [SWS_Fee_00163] */

    return ReturnValue;
}

/****************************************************************************************************
 *   Function Name           : Fee_Cancel
 *
 *   Service ID              : 0x04.
 *
 *   Description             : This function calls the cancel function of the underlying flash driver.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00089.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(void, FEE_PUBLIC_CODE) Fee_Cancel
(
    void
)
{
    MemIf_StatusType FeeStatus;
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Std_ReturnType DetCheckResult;

    DetCheckResult = Fee_LocalCommonDetCheck(FEE_CANCEL_ID);
    if (E_OK == DetCheckResult)
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */
    {
        FeeStatus = Fee_LocalGetStatus();
        /* If status is not MEMIF_BUSY, shall not change status or job result. [SWS_Fee_00164] */
        if (FeeStatus == MEMIF_BUSY)
        {
            switch (Fee_State.MainJob)
            {
                /* read/write job is on-going */
                case FEE_MAIN_WRITE:
                {
                    Fee_State.NextFreePageAddr += Fee_UserJobInfo.LastWriteSize;
                    Fee_State.MainJob = FEE_MAIN_NONE;
                    break;
                }
                case FEE_MAIN_READ:
                {
                    Fee_State.MainJob = FEE_MAIN_NONE;
                    Fls_Cancel();
                    break;
                }
                default:
                {
                    /* Job is requested but not started */
                    break;
                }
            }

            /* Update the current pending request type to 'No pending request' */
            Fee_UserJobInfo.PendReqStatus = FEE_PEND_NO_REQ;
            /* Set the job result to MEMIF_JOB_CANCELED. [SWS_Fee_00157], [SWS_Fee_00155] */
            Fee_UserJobInfo.JobResult = MEMIF_JOB_CANCELED;
            /* After Fee_Cancel finish, Status shall be set to MEMIF_IDLE. [SWS_Fee_00081] */
            Fee_UserJobInfo.FlsJobStatus = FEE_JOB_IDLE;
        }
        else
        /* If status is MEMIF_BUSY, accepted function. [SWS_Fee_00080] */
        {
            /* If status is not MEMIF_BUSY, Report DET FEE_E_INVALID_CANCEL. [SWS_Fee_00184] */
            FEE_REPORTRUNTIMEERROR(FEE_CANCEL_ID, FEE_E_INVALID_CANCEL);
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Fee_GetStatus
 *
 *   Service ID              : 0x05.
 *
 *   Description             : This function returns the status.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : MEMIF_UNINIT: not initialized
 *                             MEMIF_IDLE: idle
 *                             MEMIF_BUSY: busy
 *                             MEMIF_BUSY_INTERNAL: busy with internal management operation
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00090.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(MemIf_StatusType, FEE_PUBLIC_CODE) Fee_GetStatus
(
    void
)
{
    MemIf_StatusType ReturnStatus;
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Mcal_CoreType CoreId;

    /* Get core id which is executing currently */
    /* #Violation: Fee_c_REF_2 */
    CoreId = Mcal_GetCoreId();
    if (FEE_CORE_ALLOCATION != (uint8)CoreId)
    {
        FEE_REPORTERROR(FEE_GETSTATUS_ID, FEE_E_CORE_NOT_CONFIGURED);
        ReturnStatus = MEMIF_UNINIT;
    }
    else
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */
    {
        ReturnStatus = Fee_LocalGetStatus();
    }

    return ReturnStatus;
}

/****************************************************************************************************
 *   Function Name           : Fee_GetJobResult
 *
 *   Service ID              : 0x06.
 *
 *   Description             : This function returns the last job's result.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : MEMIF_JOB_OK: The last job has been finished successfully.
 *                             MEMIF_JOB_PENDING: The last job is waiting for execution or
 *                                                currently being executed.
 *                             MEMIF_JOB_CANCELED: The last job has been canceled.
 *                                                 (which means it failed)
 *                             MEMIF_JOB_FAILED: The last job has not been finished successfully.
 *                             MEMIF_BLOCK_INCONSISTENT: The requested block is inconsistent,
 *                                                       it may contain corrupted data.
 *                             MEMIF_BLOCK_INVALID: The requested block has been invalidated,
 *                                                the requested read operation can not be performed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00091.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(MemIf_JobResultType, FEE_PUBLIC_CODE) Fee_GetJobResult
(
    void
)
{
    MemIf_JobResultType ReturnValue;
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Std_ReturnType DetCheckResult;

    /* If state is MEMIF_UNINIT, Report DET FEE_E_UNINIT. [SWS_Fee_00125] */
    DetCheckResult = Fee_LocalCommonDetCheck(FEE_GETJOBRESULT_ID);
    if (E_OK != DetCheckResult)
    {
        ReturnValue = MEMIF_JOB_FAILED;
    }
    else
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */
    {
        ReturnValue = Fee_UserJobInfo.JobResult;
    }

    return ReturnValue;
}

/****************************************************************************************************
 *   Function Name           : Fee_InvalidateBlock
 *
 *   Service ID              : 0x07.
 *
 *   Description             : This function invalidate a logical block.
 *
 *   Parameters in           : BlockNumber: Logical Block Number.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Asynchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: job accepted
 *                             E_NOT_OK: job declined
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00092.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_InvalidateBlock
(
    uint16 BlockNumber
)
{
    uint16           BlockIndex;
    Std_ReturnType   ReturnValue;
    MemIf_StatusType FeeStatus;
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Std_ReturnType DetCheckResult;
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */

#if (STD_OFF == FEE_DEV_ERROR_DETECT)
    /* Return the configuration set array Index corresponding to BlockNumber */
    BlockIndex = Fee_LocalGetUsrBlockIndex(BlockNumber);
#else  /* (STD_OFF \== FEE_DEV_ERROR_DETECT) */
    ReturnValue = E_NOT_OK;
    DetCheckResult = Fee_LocalCommonDetCheck(FEE_INVALIDATEBLOCK_ID);
    if (E_OK == DetCheckResult)
    {
        /* Return the configuration set array Index corresponding to BlockNumber */
        BlockIndex = Fee_LocalGetUsrBlockIndex(BlockNumber);
        if (FEE_LOG_BLOCK_NOT_FOUND == BlockIndex)
        {
            /* Block number is not valid. [SWS_Fee_00140] */
            FEE_REPORTERROR(FEE_INVALIDATEBLOCK_ID, FEE_E_INVALID_BLOCK_NO);
        }
        else
        {
            ReturnValue = E_OK;
        }
    }
    /* If status is not MEMIF_IDLE, shall reject request, return E_NOT_OK. [SWS_Fee_00176] */
    if (ReturnValue != E_NOT_OK)
#endif /* (STD_OFF \== FEE_DEV_ERROR_DETECT) */
    {
        /* \[SWS_Fee_00176]Execute only if there is no pending request */
        FeeStatus = Fee_LocalGetStatus();
        if ((MEMIF_IDLE == FeeStatus) || (MEMIF_BUSY_INTERNAL == FeeStatus))
        {
            Fee_UserJobInfo.BlockInvalidReq = TRUE;
            Fee_LocalHandleUserWriteReq(BlockIndex, Fee_RWBuffer);
            ReturnValue = E_OK;
        }
        else
        {
            /* \[SWS_Fee_00145] FEE is busy with another request; raise FEE_E_BUSY DET */
            FEE_REPORTRUNTIMEERROR(FEE_INVALIDATEBLOCK_ID, FEE_E_BUSY);
            ReturnValue = E_NOT_OK;
        }
    }
    /* If invalidation request is rejected, shall not change status or job result.[SWS_Fee_00165] */

    return ReturnValue;
}

#if (FEE_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
 *   Function Name           : Fee_GetVersionInfo
 *
 *   Service ID              : 0x08.
 *
 *   Description             : This function returns the version information of this module.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : VersionInfoPtr: Pointer to store the version information
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00093.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(void, FEE_PUBLIC_CODE) Fee_GetVersionInfo
(
    P2VAR(Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA) VersionInfoPtr
)
{
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    if (NULL_PTR == VersionInfoPtr)
    {
        /* Data pointer is not valid. [SWS_Fee_00147] */
        FEE_REPORTERROR(FEE_GETVERSIONINFO_ID, FEE_E_PARAM_POINTER);
    }
    else
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */
    {
        VersionInfoPtr->moduleID = FEE_MODULE_ID;
        VersionInfoPtr->vendorID = (uint16)FEE_VENDOR_ID;
        VersionInfoPtr->sw_major_version = (uint8)FEE_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)FEE_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)FEE_SW_PATCH_VERSION;
    }
}
#endif /* (FEE_VERSION_INFO_API \== STD_ON) */

/****************************************************************************************************
 *   Function Name           : Fee_EraseImmediateBlock
 *
 *   Service ID              : 0x09.
 *
 *   Description             : This function erase a logical block.
 *
 *   Parameters in           : BlockNumber: Logical Block Number.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Asynchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : E_OK: job accepted
 *                             E_NOT_OK: job declined
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00094.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_EraseImmediateBlock
(
    uint16 BlockNumber
)
{
    /* #Violation: Fee_c_REF_2 */
    MCAL_UNUSED_VAR(BlockNumber);
    /* not support */
    return E_OK;
}

/****************************************************************************************************
 *   Function Name           : Fee_MainFunction
 *
 *   Service ID              : 0x12.
 *
 *   Description             : This function handles the requested job and internal management
 *                             operations.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00097.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(void, FEE_PUBLIC_CODE) Fee_MainFunction
(
    void
)
{
    MemIf_StatusType FlsStatus;
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Mcal_CoreType CoreId;

    /* Get core id which is executing currently */
    /* #Violation: Fee_c_REF_2 */
    CoreId = Mcal_GetCoreId();
    if (FEE_CORE_ALLOCATION != (uint8)CoreId)
    {
        FEE_REPORTERROR(FEE_MAINFUNCTION_ID, FEE_E_CORE_NOT_CONFIGURED);
    }
    else
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */
    {
        /* Fls_SetMode is sync and can run when Fls is idle, so we can call Fls_SetMode and no need
           wait the gc job complete. */
        if ((TRUE == Fee_UserJobInfo.FeeSetModeReqPend) &&
            (FEE_JOB_REQSTD != Fee_GcJobInfo.FlsJobStatus))
        {
            Fls_SetMode(Fee_UserJobInfo.Mode);
            Fee_UserJobInfo.FeeSetModeReqPend = FALSE;
        }

        /* Only run mainfuncion when fls is idle */
        FlsStatus = Fls_GetStatus();
        if (MEMIF_IDLE == FlsStatus)
        {
            /* switch Main Job */
            Fee_LocalDecideMainJob();
            /* Fee_MainFunction shall asynchronously handle the read / write / erase / invalidate jobs */
            /* requested by the upper layer and internal management operations. [SWS_Fee_00057] */
            switch (Fee_State.MainJob)
            {
                case FEE_MAIN_INITGC:
                case FEE_MAIN_GC:
                {
                    /* When job is init gc. This function will write erase bank information in one bank.
                     * And write erase bank information and valid bank information in another bank. */
                    /* When job is gc, Fee will automatically start garbage collection operations. Copy
                     * all block data (latest) from previous bank to another bank. After block copying is
                     * complete, erase the previous bank, and the new bank will be used for subsequent
                     * reads and writes. */
                    if (Fee_GcJobInfo.FlsJobStatus != FEE_JOB_REQSTD)
                    {
                        Fee_LocalGC();
                    }
                    break;
                }
                case FEE_MAIN_WRITE:
                {
                    /* Write operation execution function, first determine whether writing can be
                     * performed, then construct the data structure, call the Fls_Write function to write
                     * the data to Flash, and after writing, it can be read back for verification */
                    if (Fee_UserJobInfo.FlsJobStatus != FEE_JOB_REQSTD)
                    {
                        Fee_LocalWrite();
                    }
                    break;
                }
                case FEE_MAIN_READ:
                {
                    /* Read the operation execution function, first check whether the Block is valid and
                     * complete, and then call the Fls_Read function to read data from Flash. Process the
                     * read data in End Notification, delete the tags, and then perform the next read or
                     * return the data to the user */
                    if (Fee_UserJobInfo.FlsJobStatus != FEE_JOB_REQSTD)
                    {
                        Fee_LocalRead();
                    }
                    break;
                }
                /* FEE_MAIN_NONE */
                default:
                {
                    /* Do Nothing */
                    break;
                }
            }
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Fee_JobEndNotification
 *
 *   Service ID              : 0x10.
 *
 *   Description             : This function reports the successful end of an asynchronous operation.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00095.
 ****************************************************************************************************/
FUNC(void, FEE_PUBLIC_CODE) Fee_JobEndNotification
(
    void
)
{
    Std_ReturnType   RetVal;
    /* Make sure that notification runtime is reasonably short. [SWS_Fls_00193] */
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Mcal_CoreType CoreId;

    /* Get core id which is executing currently */
    /* #Violation: Fee_c_REF_2 */
    CoreId = Mcal_GetCoreId();
    if (FEE_CORE_ALLOCATION != (uint8)CoreId)
    {
        FEE_REPORTERROR(FEE_JOBENDNOTIFICATION_ID, FEE_E_CORE_NOT_CONFIGURED);
    }
    else
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */
    {
        /* The read job is done */
        if (Fee_SkipReadStatus.Remain > 0U)
        {
            /* Because the read data cross bad sector, we split it to two readings, the first is
               done, we need call fls for second reading. */
            RetVal = Fls_Read((Fls_AddressType)Fee_SkipReadStatus.ResumeSrcAddr,
                              Fee_SkipReadStatus.ResumeBufferPtr,
                              (Fls_LengthType)Fee_SkipReadStatus.Remain);
            if (E_OK != RetVal)
            {
                Fee_JobErrorNotification();
            }
            Fee_SkipReadStatus.Remain = 0U;
        }
        else
        {
            if (Fee_State.MainJob >= FEE_MAIN_READ)
            {
                /* User job */
                Fee_UserJobInfo.FlsJobStatus = FEE_JOB_DONE;
            }
            else if (Fee_State.MainJob >=  FEE_MAIN_INITGC)
            {
                /* Gc job */
                Fee_GcJobInfo.FlsJobStatus = FEE_JOB_DONE;
            }
            else
            /* #Violation: Fee_c_REF_10 */
            {
                /* Do Nothing */
            }
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Fee_JobErrorNotification
 *
 *   Service ID              : 0x11.
 *
 *   Description             : This function reports the failure of an asynchronous operation.
 *
 *   Parameters in           : None.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            : None.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : SWS_Fee_00096.
 ****************************************************************************************************/
FUNC(void, FEE_PUBLIC_CODE) Fee_JobErrorNotification
(
    void
)
{
#if (STD_ON == FEE_DEV_ERROR_DETECT)
    Mcal_CoreType CoreId;

    /* Get core id which is executing currently */
    /* #Violation: Fee_c_REF_2 */
    CoreId = Mcal_GetCoreId();
    if (FEE_CORE_ALLOCATION != (uint8)CoreId)
    {
        FEE_REPORTERROR(FEE_JOBERRORNOTIFICATION_ID, FEE_E_CORE_NOT_CONFIGURED);
    }
    else
#endif /* (STD_ON \== FEE_DEV_ERROR_DETECT) */
    {
        if (Fee_State.MainJob >=  FEE_MAIN_READ)
        {
            /* User job */
            Fee_UserJobInfo.FlsJobStatus = FEE_JOB_FAILED;
            Fee_UserJobInfo.JobResultPending = MEMIF_JOB_FAILED;
        }
        else if (Fee_State.MainJob >=  FEE_MAIN_INITGC)
        {
            /* Gc job */
            Fee_GcJobInfo.FlsJobStatus = FEE_JOB_FAILED;
        }
        else
        /* #Violation: Fee_c_REF_10 */
        {
            /* Do Nothing */
        }
    }
}

/****************************************************************************************************
 *   Function Name           : Fee_GetCycleCount
 *
 *   Service ID              : 0x13.
 *
 *   Description             : When called with BlockNumber = 0, this routine delivers the FEE sector
 *                             erase cycle count. When called with a configured BlockNumber, the write
 *                             cycle count of the given block is returned.
 *
 *   Parameters in           : BlockNumber: Logical Block Number.
 *                             CountPtr: Pointer to value to save block write cycle count.
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Non-Reentrant.
 *
 *   Return value            :  Std_ReturnType
 *                              E_OK: Block cycle count read successfully
 *                              E_NOT_OK: Block cycle count can not be read
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
/* #Violation: Fee_c_REF_3 */
FUNC(Std_ReturnType, FEE_PUBLIC_CODE) Fee_GetCycleCount
(
    uint16 BlockNumber,
    P2VAR(uint32, AUTOMATIC, FEE_APPL_DATA) CountPtr
)
{
    uint16           BlockIndex;
    Std_ReturnType   ReturnValue;

#if (STD_ON == FEE_DEV_ERROR_DETECT)
    ReturnValue = Fee_LocalCommonDetCheck(FEE_SID_GETCYCLECOUNT);
    if (E_OK == ReturnValue)
    {
        /* \[SWS_Fee_00139] Check if the buffer pointer is NULL */
        if (NULL_PTR == CountPtr)
        {
            FEE_REPORTERROR(FEE_SID_GETCYCLECOUNT, FEE_E_PARAM_POINTER);
            ReturnValue = E_NOT_OK;
        }
        else if (FEE_STATEPAGE_NUMBER != BlockNumber)
        {
            /* Return the configuration set array Index corresponding to BlockNumber */
            BlockIndex = Fee_LocalGetUsrBlockIndex(BlockNumber);
            /* \[SWS_Fee_00138]  block number is correct */
            if (FEE_LOG_BLOCK_NOT_FOUND == BlockIndex)
            {
                FEE_REPORTERROR(FEE_SID_GETCYCLECOUNT, FEE_E_INVALID_BLOCK_NO);
                ReturnValue = E_NOT_OK;
            }
        }
        else
        {
            /* Do Nothing */
        }
    }

    if (E_OK == ReturnValue)
#else
    ReturnValue = E_OK;
#endif /* (STD_OFF \== FEE_DEV_ERROR_DETECT) */
    {
        if (FEE_STATEPAGE_NUMBER != BlockNumber)
        {
#if (STD_OFF == FEE_DEV_ERROR_DETECT)
            /* Return the configuration set array Index corresponding to BlockNumber */
            BlockIndex = Fee_LocalGetUsrBlockIndex(BlockNumber);
#endif /* (STD_OFF \== FEE_DEV_ERROR_DETECT) */
            *CountPtr = Fee_State.BlockInfoPtr[BlockIndex].BlockCycleCount;
        }
        else
        {
            *CountPtr = (Fee_State.BankInfoPtr[Fee_State.CurrBank].GcNumber >> 1U);
        }
    }

    return ReturnValue;
}

/* #Violation: Fee_c_REF_5 */
#define FEE_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fee_c_REF_8 */
#include "Fee_MemMap.h"
/****************************************************************************************************
**                                           End of File                                           **
****************************************************************************************************/

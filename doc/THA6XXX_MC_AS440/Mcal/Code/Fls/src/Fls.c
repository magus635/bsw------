/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls.c
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all functions of DFlash Driver
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
*#Fls_c_REF_1:MISRAC2012-Rule-20.10;
* Justification:Use glue operator to construct the exclusive area function name.
*
*#Fls_c_REF_2:MISRAC2012-Rule-20.1;
* Justification:AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
*#Fls_c_REF_3:MISRAC2012-Rule-11.4;
* Justification:Casting pointer to an integeral type to obtain its address.
*
*#Fls_c_REF_4:MISRAC2012-Dir-4.9;
* Justification:Function like macros are used to reduce code complexity.
*
*#Fls_c_REF_5:MISRAC2012-Rule-11.3;
* Justification:Casting FLASH address; Address is verified to be 32bits aligned before casting.
*
*#Fls_c_REF_6:MISRAC2012-Rule-2.1;
* Justification:Reserved API for user access
*
*#Fls_c_REF_7:CertC-DCL00-C
* Justification:Parameter declared refer to AUTOSAR specifications.
*
*#Fls_c_REF_8:MISRAC2012-Rule-20.7
* Justification:Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Fls_c_REF_9:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*#Fls_c_REF_10:CertC-DCL00;
* Justification:Parameter declared refer to AUTOSAR specifications.
*
*#Fls_c_REF_11:CertC-EXP39-C;
* Justification:Casting FLASH address; Address is verified to be 32bits aligned before casting.
*
*#Fls_c_REF_12:CertC-INT36-C;
* Justification:Cast a numeric value to a pointer type for accessing data at a specified
* memory address.
*
*#Fls_c_REF_13:CertC-PRE00-C;
* Justification:Function like macros are used to reduce code complexity.
*
*#Fls_c_REF_14:CWE-1071;
* Justification:MISRA-2012 Rule 15.7/Rule 16.4 require reserved empty code block
*
*#Fls_c_REF_15:CWE-119;
* Justification:Valid range check has been performed for the target address
*
*#Fls_c_REF_16:CWE-843;
* Justification:Casting FLASH address; Address is verified to be 32bits aligned before casting.
*
*#Fls_c_REF_17:MISRAC2012-Rule-11.4;
* Justification:Converting integers to object pointers to reduce targeted RAM/FLASH memory
* address data access complexity.
*
*#Fls_c_REF_18:MISRAC2012-Rule-10.5;
* Justification:Redundant cast is necessary to maintain the software structure and reduce the
* complexity.
*
*#Fls_c_REF_19:CertC-INT18-C;
* Justification:Address range is vaild for the target flash type.
*
*#Fls_c_REF_20:CWE-128;
* Justification:Address range is vaild for the target flash type.
*
*#Fls_c_REF_21:CWE-191;
* Justification:Address range is vaild for the target flash type.
*
*/


/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Fls.h"
#include "Fls_Cfg.h"
#include "Fls_GeneralTypes.h"
#include "Mcall.h"
#include "SchM_Fls.h"
/* Mandatory Interfaces: Det_ReportRuntimeError. [SWS_Fls_00260] */
/* Optional Interfaces: Det_ReportError. [SWS_Fls_00261] */
#include "Det.h"

/****************************************************************************************************
**                          Version Checks                                                         **
****************************************************************************************************/
#if (FLS_VENDOR_ID != FLS_CFG_VENDOR_ID)
  #error "Fls.c : Mismatch in Vendor ID"
#endif /* (FLS_VENDOR_ID \!= FLS_CFG_VENDOR_ID) */

#if (FLS_MODULE_ID != FLS_CFG_MODULE_ID)
  #error "Fls.c : Mismatch in Module ID"
#endif /* (FLS_MODULE_ID \!= FLS_CFG_MODULE_ID) */

#if (FLS_AR_RELEASE_MAJOR_VERSION != FLS_CFG_AR_RELEASE_MAJOR_VERSION)
  #error "Fls.c : Mismatch in Release Major Version"
#endif /* (FLS_AR_RELEASE_MAJOR_VERSION \!= FLS_CFG_AR_RELEASE_MAJOR_VERSION) */

#if (FLS_AR_RELEASE_MINOR_VERSION != FLS_CFG_AR_RELEASE_MINOR_VERSION)
  #error "Fls.c : Mismatch in Release Minor Version"
#endif /* (FLS_AR_RELEASE_MINOR_VERSION \!= FLS_CFG_AR_RELEASE_MINOR_VERSION) */

#if (FLS_AR_RELEASE_REVISION_VERSION != FLS_CFG_AR_RELEASE_REVISION_VERSION)
  #error "Fls.c : Mismatch in Release Revision Version"
#endif /* (FLS_AR_RELEASE_REVISION_VERSION \!= FLS_CFG_AR_RELEASE_REVISION_VERSION) */

#if (FLS_SW_MAJOR_VERSION != FLS_CFG_SW_MAJOR_VERSION)
  #error "Fls.c : Mismatch in Software Major Version"
#endif /* (FLS_SW_MAJOR_VERSION \!= FLS_CFG_SW_MAJOR_VERSION) */

#if (FLS_SW_MINOR_VERSION != FLS_CFG_SW_MINOR_VERSION)
  #error "Fls.c : Mismatch in Software Minor Version"
#endif /* (FLS_SW_MINOR_VERSION \!= FLS_CFG_SW_MINOR_VERSION) */

#if (FLS_SW_PATCH_VERSION != FLS_CFG_SW_PATCH_VERSION)
  #error "Fls.c : Mismatch in Software Patch Version"
#endif /* (FLS_SW_PATCH_VERSION \!= FLS_CFG_SW_PATCH_VERSION) */

/****************************************************************************************************
**                          Private Macro Definitions                                              **
****************************************************************************************************/
/* #Violation: Fls_c_REF_13*/
/* #Violation: Fls_c_REF_1 */
#define FLS_ENTER_CRITICAL_SECTION(Exclusive_Area) SchM_Enter_Fls_##Exclusive_Area()
/* #Violation: Fls_c_REF_13*/
/* #Violation: Fls_c_REF_1 */
#define FLS_EXIT_CRITICAL_SECTION(Exclusive_Area)  SchM_Exit_Fls_##Exclusive_Area()

/* One word occupies 4 bytes */
#define FLS_WORD_SIZE_TO_BTYE             (4UL)
/* Word size mask */
#define FLS_WORD_SIZE_MASK                (FLS_WORD_SIZE_TO_BTYE - 1UL)


/* DET Error Flag */
#define FLS_NO_DET_ERROR                  (0U)
#define FLS_DET_ERROR                     (1U)

/* Flash status not error . */
#define FLS_STATUS_NO_ERROR               (0U)
/* Flash status error mask. */
#define FLS_STATUS_ERROR_MASK             (0x150000U)
/* Fls Error type : hardware error. */
#define FLS_ERROR_TYPE_HW_FAIL            (0U)
/* Fls Error type : software error. */
#define FLS_ERROR_TYPE_SW_FAIL            (1U)

/* Mask for checking which type of hardware FLASH type */
#define FLS_FLASH_TYPE_MASK               (0x10000000U)


/* Number of hardware FLASH */
#define FLS_FLASH_HW_COUNT                (2U)

#if (FLS_USE_INTERRUPTS == STD_ON)
/* Trigger interrupt after programming (erasing) is completed. */
#define FLS_INT_ENABLE                    (0xFU)
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */


/* Variable not used&quot */
/* #Violation: Fls_c_REF_13 */
/* #Violation: Fls_c_REF_4 */
#define FLS_UNUNSED_VAR(var) \
    ((void)(var))

/* Retrieve a pointer to the hardware information structure for the given flash type */
/* #Violation: Fls_c_REF_13 */
/* #Violation: Fls_c_REF_4 */
#define FLS_GET_FLASH_HW_INFO_PTR(FlashType)  \
    (&(Fls_HwInfoList[(FlashType)]))

/* Determine the type of flash memory (DFlash or PFlash) based on the address */
/* #Violation: Fls_c_REF_13 */
/* #Violation: Fls_c_REF_4 */
#define FLS_GET_FLASH_TYPE(Addr) \
    (((((uint32)(Addr)) & FLS_FLASH_TYPE_MASK) == 0U)?FLS_DFLASH_REGION:FLS_PFLASH_REGION)

/****************************************************************************************************
**                          Private Type Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Enumration Definitions                                         **
****************************************************************************************************/
/* Enumeration to represent the result status of flash operations */
typedef enum
{
    FLS_HW_RESULT_OK     = 0U,        /* Operation completed successfully */
    FLS_HW_RESULT_FAILED = 1U,        /* Operation failed */
    FLS_HW_RESULT_BUSY   = 4U,        /* Flash memory is busy with another operation */
} Fls_FlashResultStatus;

/****************************************************************************************************
**                          Private Union Definitions                                              **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Structure Definitions                                          **
****************************************************************************************************/
/* Structure to hold hardware parameters for a flash memory region */
typedef struct
{
    Fls_AddressType FlashBaseAddress; /* Base address of the flash memory region */
    Fls_LengthType  FlashSize;        /* Total size of the flash memory region in bytes */
    Fls_LengthType  SectorSize;       /* Size of a single sector in the flash memory */
    uint32 FlashPWordSize;            /* Size of a program word in bytes */
    uint32 FlashRowSize;              /* Size of a row in the flash memory */
    uint32 FlashEndAddress;           /* End address of the flash memory region */
} Fls_FlashHwParaType;

/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_c_REF_9 */
#define FLS_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
#define FLS_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
#define FLS_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
#define FLS_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"

/* \[SWS_Fls_00191] */
/* Default value is NULL_PTR */
static P2CONST(Fls_ConfigType, AUTOMATIC, FLS_APPL_CONST) Fls_ConfigPtr;

#if (STD_ON == FLS_USE_INTERRUPTS)
/* Canceling job address */
static VAR(Fls_AddressType, AUTOMATIC) Fls_CancelJobAddress;
#endif /* (STD_ON \== FLS_USE_INTERRUPTS) */

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_c_REF_9 */
#define FLS_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
#define FLS_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
#define FLS_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
#define FLS_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"


#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_c_REF_9 */
#define FLS_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
#define FLS_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
#define FLS_START_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
#define FLS_START_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"

/**
 * This variable holds the state of the Flash driver. It is allocated in the BSS,
 * which is zero-initialized at the start of the program.
 */
static Fls_StateType Fls_State;

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_c_REF_9 */
#define FLS_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
#define FLS_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
#define FLS_STOP_SEC_VAR_CLEARED_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
#define FLS_STOP_SEC_VAR_CLEARED_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"

#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_c_REF_9 */
#define FLS_START_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
#define FLS_START_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
#define FLS_START_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
#define FLS_START_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"
static const Fls_FlashHwParaType Fls_HwInfoList[FLS_FLASH_HW_COUNT] =
{
    /* DFlash hadware parameter */
    {
        FLS_DFLASH_BASE_ADDRESS,
        FLS_DFLASH_TOTAL_SIZE,
        FLS_DFLASH_SECTOR_SIZE,
        FLS_DFLASH_PAGE_SIZE,
        FLS_DFLASH_ROW_SIZE,
        FLS_DFLASH_END_ADDRESS
    },
    /* PFlash hardware parameter */
    {
        FLS_PFLASH_BASE_ADDRESS,
        FLS_PFLASH_TOTAL_SIZE,
        FLS_PFLASH_SECTOR_SIZE,
        FLS_PFLASH_PAGE_SIZE,
        FLS_PFLASH_ROW_SIZE,
        FLS_PFLASH_END_ADDRESS
    }
};
#if (0U == FLS_CORE_ALLOCATION)
/* #Violation: Fls_c_REF_9 */
#define FLS_STOP_SEC_CONST_ASIL_D_CORE0_UNSPECIFIED
#elif (1U == FLS_CORE_ALLOCATION)
#define FLS_STOP_SEC_CONST_ASIL_D_CORE1_UNSPECIFIED
#elif (2U == FLS_CORE_ALLOCATION)
#define FLS_STOP_SEC_CONST_ASIL_D_CORE2_UNSPECIFIED
#elif (3U == FLS_CORE_ALLOCATION)
#define FLS_STOP_SEC_CONST_ASIL_D_CORE3_UNSPECIFIED
#endif /* (CoreID \== FLS_CORE_ALLOCATION) */
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"
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
/* #Violation: Fls_c_REF_9 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"

#if (FLS_DEV_ERROR_DETECT == STD_ON)
static FUNC(uint8, FLS_PRIVATE_CODE) Fls_CommonDetCheck
(
    uint8 ServiceID,
    Fls_AddressType JobAddress,
    Fls_LengthType JobLength
);

static FUNC(uint8, FLS_PRIVATE_CODE) Fls_CompareWordsSyncDetCheck
(
    uint8 Error,
    Fls_AddressType SourceAddress,
    CONSTP2CONST(uint32, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
    Fls_LengthType Length
);
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */

#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
static FUNC(void, FLS_PRIVATE_CODE) Fls_TimeOutDet
(
    uint8 ServiceID
);
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */

static FUNC(void, FLS_PRIVATE_CODE) Fls_ErrorHandler
(
    Fls_JobType JobType,
    uint8 ErrorType
);

static FUNC(void, FLS_PRIVATE_CODE) Fls_EndHandler
(
    Fls_JobType JobType
);

static FUNC(Fls_LengthType, FLS_PRIVATE_CODE) Fls_GetReadModeLength
(
    void
);

static FUNC(Fls_LengthType, FLS_PRIVATE_CODE) Fls_GetWriteLength
(
    void
);

static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainEraseJobStart
(
    void
);

static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainErase
(
    void
);

static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainEraseHandler
(
    void
);

static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainWriteJobStart
(
    uint32 Length
);

static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainWrite
(
    void
);

static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainWriteHandler
(
    void
);

static FUNC(void, FLS_PRIVATE_CODE) Fls_MainCompareHandler
(
    void
);

static FUNC(void, FLS_PRIVATE_CODE) Fls_MainReadHandler
(
    void
);

#if (FLS_BLANK_CHECK_API == STD_ON)
static FUNC(void, FLS_PRIVATE_CODE) Fls_MainCheckHandler
(
    void
);
#endif /* (FLS_BLANK_CHECK_API  \== STD_ON) */

/* Internal functions for compatiblilty with PFlash and DFlash */
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InnerInit
(
    void
);

static FUNC(boolean, FLS_PRIVATE_CODE) Fls_InnerCheckFlashBusy
(
    Fls_AddressType TargetAddress
);

static FUNC(void, FLS_PRIVATE_CODE) Fls_InnerClearFlashAllStatus
(
    Fls_AddressType TargetAddress
);

static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InnerEraseSectorAsync
(
    Fls_AddressType TargetAddress
);

static FUNC(Fls_FlashResultStatus, FLS_PRIVATE_CODE) Fls_InnerCheckHwEraseStatus
(
    Fls_AddressType TargetAddress
);

static FUNC(Fls_FlashResultStatus, FLS_PRIVATE_CODE) Fls_InnerCheckFlashBlankSync
(
    Fls_AddressType TargetAddress,
    Fls_LengthType FlashLength
);

static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InnerProgramFlash
(
    Fls_AddressType TargetAddress,
    CONSTP2CONST(uint8, AUTOMATIC, FLS_APPL_DATA) SourceAddressPtr,
    Fls_LengthType FlashLength
);

static FUNC(Fls_FlashResultStatus, FLS_PRIVATE_CODE) Fls_InnerCheckHwWriteStatus
(
    Fls_AddressType TargetAddress
);

static FUNC(boolean, FLS_PRIVATE_CODE) Fls_InnerGetFlashEccStatus
(
    Fls_AddressType TargetAddress
);

static FUNC(boolean, FLS_PRIVATE_CODE) Fls_InnerClearFlashEccStatus
(
    Fls_AddressType TargetAddress
);
#if (FLS_WRITE_VERIFICATION_ENABLED == STD_ON)
static FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_InnerCheckWriteReadback
(
    Fls_AddressType SourceAddress,
    CONSTP2CONST(uint32, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
    Fls_LengthType Length
);
#endif /* \(FLS_WRITE_VERIFICATION_ENABLED \== STD_ON) */
#if (FLS_USE_INTERRUPTS == STD_ON)
static FUNC(uint32, FLS_PRIVATE_CODE) Fls_InnerGetAllFlashStatus
(
    Fls_AddressType TargetAddress
);
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */

#if (FLS_USE_INTERRUPTS == STD_ON)
static FUNC(boolean, FLS_PRIVATE_CODE) Fls_InnerEnableFlashInt(void);
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */

#if (FLS_USE_INTERRUPTS == STD_OFF)
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InnerFlashOperateStatusRight
(
    Fls_AddressType TargetAddress
);
#endif /* (FLS_USE_INTERRUPTS  \== STD_OFF) */
/* #Violation: Fls_c_REF_9 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"
/****************************************************************************************************
**                          Private Function Definitions                                           **
****************************************************************************************************/
/* #Violation: Fls_c_REF_9 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"
static FUNC(Fls_AddressType, FLS_PRIVATE_CODE) Fls_InnerGetOffsetAddress
(
    Fls_AddressType TargetAddress,
    Fls_OptFlashType FlashType
)
{
    Fls_AddressType OffsetAddress;
    if (FlashType == FLS_DFLASH_REGION)
    {
        OffsetAddress = TargetAddress;
    }
    else
    {
        /* #Violation: Fls_c_REF_19 */
        /* #Violation: Fls_c_REF_20 */
        /* #Violation: Fls_c_REF_21 */
        OffsetAddress = TargetAddress - FLS_FLASH_TYPE_MASK;
    }

    return OffsetAddress;
}

/****************************************************************************************************
*   Function Name           : Fls_InnerInit
*
*   Service ID              : None.
*
*   Description             : Initializes the internal state of the Flash Driver. Sets up necessary
*                             hardware configurations and prepares the driver for operation.
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
*   Return value            : Std_ReturnType: E_OK if successful, E_NOT_OK otherwise.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InnerInit
(
    void
)
{
    /* Variable to store the result status of DFlash initialization */
    Dflash_ResultStatus  DfRetStatus;
#if (FLS_PFLASH_USED == STD_ON)
    /* Variable to store the result status of PFlash initialization */
    Pflash_ResultStatus  PfRetStatus;
#endif /* (FLS_PFLASH_USED  \== STD_ON) */
    /* Variable to store the overall return status, initialized to E_NOT_OK */
    Std_ReturnType RetStatus = E_NOT_OK;


    /* Initialize the DFlash and store the result status */
    DfRetStatus = Flash_Hal_InitDFlash();
#if (FLS_PFLASH_USED == STD_ON)
    /* If PFlash is enabled, initialize it and store the result status */
    PfRetStatus = Flash_Hal_InitPFlash();
#endif /* (FLS_PFLASH_USED  \== STD_ON) */

    /* Check if both DFlash and PFlash (if enabled) initialization are successful */
#if (FLS_PFLASH_USED == STD_ON)
    if ((DfRetStatus == DFLASH_RESULTSTATUS_OK)
        && (PfRetStatus == PFLASH_RESULTSTATUS_OK))
#else /* (FLS_PFLASH_USED  \== STD_ON) */
    if (DfRetStatus == DFLASH_RESULTSTATUS_OK)
#endif /* (FLS_PFLASH_USED  \== STD_ON) */
    {
        /* If both initializations are successful, set the return status to E_OK */
        RetStatus = E_OK;
    }
    /* Return the overall initialization status */
    return RetStatus;
}

#if (FLS_USE_INTERRUPTS == STD_OFF)
/****************************************************************************************************
*   Function Name           : Fls_InnerFlashOperateStatusRight
*
*   Service ID              : None.
*
*   Description             : This function verifies the correctness of flash erase and program
*                             operations.
*
*   Parameters in           : TargetAddress: The address in flash memory to check status.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : Std_ReturnType: E_OK if the operation status is correct,
*                             E_NOT_OK otherwise.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InnerFlashOperateStatusRight
(
    Fls_AddressType TargetAddress
)
{
    uint32 ErrorStatus;
    Std_ReturnType RetStatus = E_OK;

#if (FLS_PFLASH_USED == STD_ON)
    if (Fls_State.CurFlashType == FLS_PFLASH_REGION)
    {
        ErrorStatus = Flash_Hal_GetAllPFlashStatus(TargetAddress);
    }
    else
#endif /* (FLS_PFLASH_USED  \== STD_ON) */
    {
        ErrorStatus = Flash_Hal_GetAllDFlashStatus();
        /* #Violation: Fls_c_REF_4 */
        FLS_UNUNSED_VAR(TargetAddress);
    }

    if (FLS_STATUS_NO_ERROR != (ErrorStatus & FLS_STATUS_ERROR_MASK))
    {
        RetStatus = E_NOT_OK;
    }

    return RetStatus;
}
#endif /* \(FLS_USE_INTERRUPTS == STD_OFF) */

/****************************************************************************************************
*   Function Name           : Fls_InnerCheckFlashBusy
*
*   Service ID              : None.
*
*   Description             : Checks if the flash memory at the specified target address is busy.
*
*   Parameters in           : TargetAddress: The address in flash memory to check.
*                             FlashType: The type of flash memory (e.g., DFlash, PFlash).
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : boolean: TRUE if flash is busy, FALSE otherwise.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, FLS_PRIVATE_CODE) Fls_InnerCheckFlashBusy
(
    Fls_AddressType TargetAddress
)
{
    boolean IsBusy;
#if (FLS_PFLASH_USED == STD_ON)
    if ( Fls_State.CurFlashType == FLS_PFLASH_REGION )
    {
        IsBusy = Flash_Hal_CheckPFlashBusy(TargetAddress);
    }
    else /* ( Fls_State.CurFlashType \== FLS_PFLASH_REGION ) */
#endif /* (FLS_PFLASH_USED  \== STD_ON) */
    {
        IsBusy = Flash_Hal_CheckDFlashBusy();
        /* #Violation: Fls_c_REF_4 */
        FLS_UNUNSED_VAR(TargetAddress);
    }

#if (FLS_USE_INTERRUPTS == STD_ON)
    /* In interrupt mode, if the current driver is canceling a task
       while the HAL layer is still busy. */
    IsBusy |= Fls_State.JobCanceling;
#endif /* (FLS_USE_INTERRUPTS \== STD_ON) */
    return IsBusy;
}

/****************************************************************************************************
*   Function Name           : Fls_InnerEraseSectorAsync
*
*   Service ID              : None.
*
*   Description             : Initiates an asynchronous erase operation on a flash sector.
*
*   Parameters in           : TargetAddress: The starting address of the sector to erase.
*                             FlashType: The type of flash memory (e.g., DFlash, PFlash).
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : Std_ReturnType: E_OK if the erase operation is successfully initiated,
*                             E_NOT_OK otherwise.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InnerEraseSectorAsync
(
    Fls_AddressType TargetAddress
)
{
    Std_ReturnType RetStatus;
    Dflash_ResultStatus DfRet;
#if (FLS_PFLASH_USED == STD_ON)
    boolean PfRet;

    if ( Fls_State.CurFlashType == FLS_PFLASH_REGION )
    {
        Fls_State.CurVerifyLen = FLS_PFLASH_SECTOR_SIZE;
        PfRet = Flash_Hal_ErasePFlashAsync(TargetAddress, PFLASH_ERASETYPE_SECTOR);
#if (FLS_SAFETY_ENABLE == STD_ON)
        if (PfRet == FALSE)
        {
            RetStatus = E_NOT_OK;
        }
        else
#endif /* (FLS_SAFETY_ENABLE \== STD_ON) */
        {
            FLS_UNUNSED_VAR(PfRet);
            RetStatus = E_OK;
        }
    }
    else /* ( Fls_State.CurFlashType \== FLS_PFLASH_REGION ) */
#endif /* (FLS_PFLASH_USED  \== STD_ON) */
    {
        Fls_State.CurVerifyLen = FLS_DFLASH_SECTOR_SIZE;
        DfRet = Flash_Hal_EraseDFlash(TargetAddress);
#if (FLS_SAFETY_ENABLE == STD_ON)
        if (DfRet == DFLASH_RESULTSTATUS_FAILED)
        {
            RetStatus = E_NOT_OK;
        }
        else
#endif /* (FLS_SAFETY_ENABLE \== STD_ON) */
        {
            /* #Violation: Fls_c_REF_4 */
            FLS_UNUNSED_VAR(DfRet);
            RetStatus = E_OK;
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Fls_InnerProgramFlash
*
*   Service ID              : None.
*
*   Description             : Programs data into the flash memory at the specified target address.
*
*   Parameters in           : TargetAddress: The starting address in flash memory for programming.
*                             SourceAddressPtr: Pointer to the source data buffer.
*                             FlashLength: The length of the data to program.
*                             FlashType: The type of flash memory (e.g., DFlash, PFlash).
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : void: This function does not return a value.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_InnerProgramFlash(
    Fls_AddressType TargetAddress,
    const uint8* const SourceAddressPtr,
    Fls_LengthType FlashLength)
{
    Std_ReturnType RetStatus;
    Dflash_ResultStatus DfRet;
#if (FLS_PFLASH_USED == STD_ON)
    boolean PfRet;

    if (Fls_State.CurFlashType == FLS_PFLASH_REGION)
    {
        /* #Violation: Fls_c_REF_5 */
        /* #Violation: Fls_c_REF_11 */
        PfRet = Flash_Hal_ProgPFlashAsync(TargetAddress, (const uint32 *)SourceAddressPtr, FlashLength);
#if (FLS_SAFETY_ENABLE == STD_ON)
        if (PfRet == FALSE)
        {
            RetStatus = E_NOT_OK;
        }
        else
#endif /* (FLS_SAFETY_ENABLE \== STD_ON) */
        {
            RetStatus = E_OK;
            FLS_UNUNSED_VAR(PfRet);
        }
    }
    else /* (Fls_State.CurFlashType \== FLS_PFLASH_REGION) */
#endif /* (FLS_PFLASH_USED \== STD_ON) */
    {
        DfRet = Flash_Hal_ProgDFlash(TargetAddress, SourceAddressPtr, FlashLength);
#if (FLS_SAFETY_ENABLE == STD_ON)
        if (DfRet == DFLASH_RESULTSTATUS_FAILED)
        {
            RetStatus = E_NOT_OK;
        }
        else
#endif /* (FLS_SAFETY_ENABLE \== STD_ON) */
        {
            RetStatus = E_OK;
            /* #Violation: Fls_c_REF_4 */
            FLS_UNUNSED_VAR(DfRet);
        }
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Fls_InnerCheckHwEraseStatus
*
*   Service ID              : None.
*
*   Description             : Checks the hardware status of a flash erase operation.
*
*   Parameters in           : TargetAddress: The address of the flash sector that was erased.
*                             FlashType: The type of flash memory (e.g., DFlash, PFlash).
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : uint8: Status of the erase operation (e.g., no error, busy, error).
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Fls_FlashResultStatus, FLS_PRIVATE_CODE) Fls_InnerCheckHwEraseStatus
(
    Fls_AddressType TargetAddress
)
{
    Fls_FlashResultStatus RetHwEraseStatus;
    boolean IsFlashBusy;
    Dflash_ResultStatus DfRetStatus;
#if (FLS_PFLASH_USED == STD_ON)
    Pflash_ResultStatus PfRetStatus;
#endif /* (FLS_PFLASH_USED \== STD_ON) */


    IsFlashBusy = Fls_InnerCheckFlashBusy(TargetAddress);
#if (FLS_PFLASH_USED == STD_ON)
    if (Fls_State.CurFlashType == FLS_PFLASH_REGION)
    {
        if (FALSE == IsFlashBusy)
        {
            PfRetStatus = Flash_Hal_GetPFlashEraseStatus(TargetAddress);
            /* #Violation: Fls_c_REF_18 */
            RetHwEraseStatus = (Fls_FlashResultStatus)PfRetStatus;
        }
        else
        {
            RetHwEraseStatus = FLS_HW_RESULT_BUSY;
        }
    }
    else
#endif /* (FLS_PFLASH_USED \== STD_ON) */
    {
        if (FALSE == IsFlashBusy)
        {
            /* The erase operation only has two states: completion and verification failure */
            DfRetStatus = Flash_Hal_GetDFlashStatus(DFLASH_STATUSID_ERASE);
            /* #Violation: Fls_c_REF_18 */
            RetHwEraseStatus = (Fls_FlashResultStatus)DfRetStatus;
            /* Clear all status before the next write flow */
            Flash_Hal_ClearAllDFlashStatus();
        }
        else
        {
            RetHwEraseStatus = FLS_HW_RESULT_BUSY;
        }
    }

    return RetHwEraseStatus;
}

/****************************************************************************************************
*   Function Name           : Fls_InnerCheckFlashBlankSync
*
*   Service ID              : None.
*
*   Description             : This function synchronously checks if a specified flash memory area
*                             is blank.
*
*   Parameters in           : TargetAddress: The starting address of the flash memory area to check.
*                             FlashLength: The length of the flash memory area to check.
*                             FlashType: The type of flash memory (e.g., DFlash, PFlash).
*                             FlsConfigPtr: Pointer to the flash driver configuration.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : Fls_FlashResultStatus: Status of the blank check operation.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Fls_FlashResultStatus, FLS_PRIVATE_CODE) Fls_InnerCheckFlashBlankSync
(
    Fls_AddressType TargetAddress,
    Fls_LengthType FlashLength
)
{
    Fls_FlashResultStatus RetStatus;
    Dflash_ResultStatus DfRetStatus;
#if (FLS_PFLASH_USED == STD_ON)
    Pflash_ResultStatus PfRetStatus;
#endif /* \(FLS_PFLASH_USED == STD_ON) */

#if (FLS_PFLASH_USED == STD_ON)
    uint32 BlankCheckCnt;
    boolean IsContinueCheckFlg;
    uint32 LoopCnt;
    const Fls_FlashHwParaType *Fls_FlashHwParas;
    Fls_AddressType CurTargetAddress;

    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_State.CurFlashType);
    IsContinueCheckFlg = TRUE;
#endif /* (FLS_PFLASH_USED \== STD_ON) */

#if (FLS_PFLASH_USED == STD_ON)
    CurTargetAddress = TargetAddress;
    if (Fls_State.CurFlashType == FLS_PFLASH_REGION)
    {
        if ((Fls_LengthType)FLASH_PFLASH_SECTOR_SIZE == FlashLength)
        {
            PfRetStatus = Flash_Hal_CheckPFlashBlankSync(CurTargetAddress, PFLASH_BLANKTYPE_SECTOR);
        }
        else
        {
            BlankCheckCnt = (FlashLength + Fls_FlashHwParas->FlashPWordSize - 1U)
            / Fls_FlashHwParas->FlashPWordSize;
            PfRetStatus = PFLASH_RESULTSTATUS_FAILED;
            for (LoopCnt = 0U; (LoopCnt < BlankCheckCnt) && (TRUE == IsContinueCheckFlg); LoopCnt++)
            {
                /* execute blank check sync and this api also clear flash status register */
                PfRetStatus = Flash_Hal_CheckPFlashBlankSync(CurTargetAddress, PFLASH_BLANKTYPE_PWORD);
                CurTargetAddress += FLASH_PFLASH_PWORD_SIZE;
                if (PFLASH_RESULTSTATUS_OK != PfRetStatus)
                {
                    IsContinueCheckFlg = FALSE;
                }
            }
        }

        /* #Violation: Fls_c_REF_18 */
        RetStatus = (Fls_FlashResultStatus)PfRetStatus;
    }
    else
#endif /* (FLS_PFLASH_USED \== STD_ON) */
    {
        if ((Fls_LengthType)FLASH_DFLASH_SECTOR_SIZE == FlashLength)
        {
            DfRetStatus = Flash_Hal_CheckDFlashSectorBlankSync(TargetAddress);
        }
        else
        {
            DfRetStatus = Flash_Hal_CheckDFlashBlankSync(TargetAddress, FlashLength);
        }
        
        /* #Violation: Fls_c_REF_18 */
        RetStatus = (Fls_FlashResultStatus)DfRetStatus;
    }

    return RetStatus;
}

/****************************************************************************************************
*   Function Name           : Fls_InnerCheckHwWriteStatus
*
*   Service ID              : None.
*
*   Description             : This function checks the hardware status of a flash write operation.
*
*   Parameters in           : TargetAddress: The address of the flash memory that was written to.
*                             FlashType: The type of flash memory (e.g., DFlash, PFlash).
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : uint8: Status of the write operation (e.g., no error, busy, error).
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Fls_FlashResultStatus, FLS_PRIVATE_CODE) Fls_InnerCheckHwWriteStatus
(
    Fls_AddressType TargetAddress
)
{
    Fls_FlashResultStatus RetHwProgStatus;
    boolean IsFlashBusy;
    Dflash_ResultStatus DfRetStatus;
#if (FLS_PFLASH_USED == STD_ON)
    Pflash_ResultStatus PfRetStatus;
#endif /* (FLS_PFLASH_USED \== STD_ON) */

    IsFlashBusy = Fls_InnerCheckFlashBusy(TargetAddress);
    RetHwProgStatus = FLS_HW_RESULT_BUSY;
#if (FLS_PFLASH_USED == STD_ON)
    if (Fls_State.CurFlashType == FLS_PFLASH_REGION)
    {
        if (FALSE == IsFlashBusy)
        {
            PfRetStatus = Flash_Hal_GetPFlashProgStatus(TargetAddress);
            /* #Violation: Fls_c_REF_18 */
            RetHwProgStatus = (Fls_FlashResultStatus)PfRetStatus;
        }
    }
    else
#endif /* (FLS_PFLASH_USED \== STD_ON) */
    {
        if (FALSE == IsFlashBusy)
        {
            DfRetStatus = Flash_Hal_GetDFlashStatus(DFLASH_STATUSID_PROG);
            /* #Violation: Fls_c_REF_18 */
            RetHwProgStatus = (Fls_FlashResultStatus)DfRetStatus;
            /* Clear all status before the next write flow */
            Flash_Hal_ClearAllDFlashStatus();
        }
    }


    return RetHwProgStatus;
}

/****************************************************************************************************
*   Function Name           : Fls_InnerGetFlashEccStatus
*
*   Service ID              : None.
*
*   Description             : This function retrieves the ECC (Error Correction Code) status of the
*                             flash memory.
*
*   Parameters in           : TargetAddress: The address in flash memory to check the ECC status.
*                             FlashType: The type of flash memory (e.g., DFlash, PFlash).
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : boolean: TRUE if an ECC error is detected, FALSE otherwise.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, FLS_PRIVATE_CODE) Fls_InnerGetFlashEccStatus
(
    Fls_AddressType TargetAddress
)
{
    boolean IsEccError;

#if (FLS_PFLASH_USED == STD_ON)
    if (Fls_State.CurFlashType == FLS_PFLASH_REGION)
    {
        IsEccError = Flash_Hal_GetPFlashEccStatus(TargetAddress);
    }
    else
#endif /* (FLS_PFLASH_USED \== STD_ON) */
    {
        IsEccError = Flash_Hal_GetDFlashEccStatus();
        /* #Violation: Fls_c_REF_4 */
        FLS_UNUNSED_VAR(TargetAddress);
    }

    return IsEccError;
}

/****************************************************************************************************
*   Function Name           : Fls_InnerClearFlashEccStatus
*
*   Service ID              : None.
*
*   Description             : This function clears the ECC (Error Correction Code) status of the
*                             flash memory.
*
*   Parameters in           : TargetAddress: The address in flash memory to clear the ECC status.
*                             FlashType: The type of flash memory (e.g., DFlash, PFlash).
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : void: This function does not return a value.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(boolean, FLS_PRIVATE_CODE) Fls_InnerClearFlashEccStatus
(
    Fls_AddressType TargetAddress
)
{
    boolean RetValue;
    RetValue = TRUE;

#if (FLS_PFLASH_USED == STD_ON)
    if (Fls_State.CurFlashType == FLS_PFLASH_REGION)
    {
        /* PFlash clear ecc status */
        RetValue &= Flash_Hal_ClearPFlashEccStatus(TargetAddress);
    }
    else
#endif /* \(FLS_PFLASH_USED \== STD_ON) */
    {
        RetValue &= Flash_Hal_ClearDFlashEccStatus();
        /* #Violation: Fls_c_REF_4 */
        FLS_UNUNSED_VAR(TargetAddress);
    }

    return RetValue;
}

#if (FLS_USE_INTERRUPTS == STD_ON)
static FUNC(uint32, FLS_PRIVATE_CODE) Fls_InnerGetAllFlashStatus
(
    Fls_AddressType TargetAddress
)
{
    uint32 FlashAllStatus = 0xFFFFFFFFU;

#if (FLS_PFLASH_USED == STD_ON)
    if (Fls_State.CurFlashType == FLS_PFLASH_REGION)
    {
        /* PFlash get all status */
        FlashAllStatus = Flash_Hal_GetAllPFlashStatus(TargetAddress);
    }
    else
#endif /* (FLS_PFLASH_USED \== STD_ON) */
    {
        FlashAllStatus = Flash_Hal_GetAllDFlashStatus();
        FLS_UNUNSED_VAR(TargetAddress);
    }

    return FlashAllStatus;
}
#endif /* \(FLS_USE_INTERRUPTS == STD_ON) */

#if (FLS_USE_INTERRUPTS == STD_ON)
static FUNC(boolean, FLS_PRIVATE_CODE) Fls_InnerEnableFlashInt(void)
{
    boolean retValue = TRUE;

    retValue &= Flash_Hal_ConfigDFlashInt(FLS_INT_ENABLE, DFLASH_INTOP_ENABLE);
#if (FLS_PFLASH_USED == STD_ON)
    retValue &= Flash_Hal_ConfigAllPFlashInt(FLS_INT_ENABLE, PFLASH_INTOP_ENABLE);
#endif /* (FLS_PFLASH_USED \== STD_ON) */

    return retValue;
}
#endif /* \(FLS_USE_INTERRUPTS == STD_ON) */
/****************************************************************************************************
*   Function Name           : Fls_InnerClearFlashAllStatus
*
*   Service ID              : None.
*
*   Description             : Clears all status flags of the flash memory at the specified
*                             target address.
*
*   Parameters in           : TargetAddress: The address in flash memory to clear status flags.
*                             FlashType: The type of flash memory (e.g., DFlash, PFlash).
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : void: This function does not return a value.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(void, FLS_PRIVATE_CODE) Fls_InnerClearFlashAllStatus
(
    Fls_AddressType TargetAddress
)
{
    /* this function is required by FLASH interrupt call back, target address verifing is needed */
    if ((TargetAddress <= Fls_HwInfoList[FLS_DFLASH_REGION].FlashEndAddress) &&
        (TargetAddress >= Fls_HwInfoList[FLS_DFLASH_REGION].FlashBaseAddress) )
    {
        Flash_Hal_ClearAllDFlashStatus();
    }
#if (FLS_PFLASH_USED == STD_ON)
    else
    {
        Flash_Hal_ClearAllPFlashStatus(TargetAddress);
    }
#endif /* (FLS_PFLASH_USED \== STD_ON) */
}
#if (FLS_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_InitStatusDetCheck
*
*   Service ID              : None.
*
*   Description             : This function checks the initialization status of the flash driver
*                             and reports DET if the driver initialization error.
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
*   Return value            : void: This function does not return a value.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(uint8, FLS_PRIVATE_CODE) Fls_InitStatusDetCheck
(
    uint8 ServiceID
)
{
    MultiCoreID CoreId;
    uint8 ErrorFlag;


    CoreId = Mcal_GetCoreId();

    if (FLS_CORE_ALLOCATION != (uint8)CoreId)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, ServiceID,
                                  FLS_E_CORE_NOT_CONFIGURED);
        ErrorFlag = FLS_DET_ERROR;
    }
    /* Check that the FLS module has been initialized. */
    else if (FLS_JOB_UNINIT == Fls_State.JobType)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, ServiceID, FLS_E_UNINIT);
        ErrorFlag = FLS_DET_ERROR;
    }
    else
    {
        ErrorFlag = FLS_NO_DET_ERROR;
    }

    return ErrorFlag;
}

/****************************************************************************************************
*   Function Name           : Fls_CommonDetCheck
*
*   Service ID              : None.
*
*   Description             : This function performs common DET checks and reports errors
*                             if any development error is detected.
*
*   Parameters in           : ApiId: The ID of the API function that is being checked.
*                             ErrorId: The ID of the error that has occurred.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : void: This function does not return a value.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(uint8, FLS_PRIVATE_CODE) Fls_CommonDetCheck
(
    uint8 ServiceID,
    Fls_AddressType JobAddress,
    Fls_LengthType JobLength
)
{
    uint8 ErrorFlag;
    const Fls_SectorConfigType * SctrCfgPtr;
    uint16 SectorCount;
    uint16 SectorIndex;
    boolean IsInsideSector = FALSE;

    ErrorFlag = Fls_InitStatusDetCheck(ServiceID);

    if (ErrorFlag != FLS_NO_DET_ERROR)
    {
        /* DET is reported in function Fls_InitStatusDetCheck, nothing to do */
    }
    else
    {
        SctrCfgPtr = Fls_ConfigPtr->FlsSectorConfigPtr;
        SectorCount = Fls_ConfigPtr->FlsNumberOfSectors;
        /* Check the JobAddress and JobLength configed or not */
        for (SectorIndex = 0U;
             ((SectorIndex < SectorCount) && (IsInsideSector == FALSE));
             SectorIndex++)
        {
            /* If the JobAddress is within one FlsSector, the judgment will begin  */
            if ((JobAddress >= SctrCfgPtr[SectorIndex].FlsSectorStartAddress) &&
                (JobAddress <= SctrCfgPtr[SectorIndex].FlsSectorEndAddress))
            {
                IsInsideSector = TRUE;
                /* Check the JobLength is within one FlsSector or not */
                if (JobLength > (SctrCfgPtr[SectorIndex].FlsSectorEndAddress - JobAddress + 1U))
                {
                    (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, ServiceID, FLS_E_PARAM_LENGTH);
                    ErrorFlag = FLS_DET_ERROR;
                }
            }
        }

        /* Parameter checking must be in the condition of initialised Fls mode */
        if (IsInsideSector == FALSE)
        {
            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, ServiceID, FLS_E_PARAM_ADDRESS);
            ErrorFlag = FLS_DET_ERROR;
        }
    }

    return ErrorFlag;
}
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */

#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_TimeOutDet
*
*   Service ID              : None.
*
*   Description             : This function performs the TIMEOUT DET check.
*
*   Parameters in           : ServiceID: API's service ID, i.e. Fls_Read.
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
static FUNC(void, FLS_PRIVATE_CODE) Fls_TimeOutDet
(
    uint8 ServiceID
)
{
    uint64 TimerCount;

    /* Provide a timeout monitoring for the currently running job, that is it shall supervise the
       deadline of the read / compare / erase or write job. [SWS_Fls_00272] */
    /* Check, whether the configured maximum erase time has been exceeded. [SWS_Fls_00359] */
    if (Fls_State.JobStarted.Erase != (boolean)FALSE)
    {
        TimerCount = Mcal_GetSystemTimerCount();
        if (Fls_State.TimeoutCount < TimerCount)
        {
            /* Raise development error FLS_E_TIMEOUT. [SWS_Fls_00359] [SWS_Fls_00361] */
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, ServiceID, FLS_E_TIMEOUT);
            Fls_ErrorHandler(Fls_State.JobType, FLS_ERROR_TYPE_SW_FAIL);
        }
    }
    /* Check, whether the expected maximum write time has been exceeded. [SWS_Fls_00360] */
    else if (Fls_State.JobStarted.Write != (boolean)FALSE)
    {
        TimerCount = Mcal_GetSystemTimerCount();
        if (Fls_State.TimeoutCount < TimerCount)
        {
            /* Raise development error FLS_E_TIMEOUT. [SWS_Fls_00360] [SWS_Fls_00361] */
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, ServiceID, FLS_E_TIMEOUT);
            Fls_ErrorHandler(Fls_State.JobType, FLS_ERROR_TYPE_SW_FAIL);
        }
    }
    else
    /* #Violation: Fls_c_REF_14 */
    {
        /* \[SWS_Fls_00362] read or compare, do not check in this implementation */
        /* Do Nothing */
    }
}
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Fls_ErrorHandler
*
*   Service ID              : None.
*
*   Description             : This function handles the DFlash error.
*
*   Parameters in           : JobType:   FLS_JOB_ERASE, FLS_JOB_WRITE etc.
*                             ErrorType: FLS_ERROR_TYPE_SW_FAIL, FLS_ERROR_TYPE_SW_FAIL etc.
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
static FUNC(void, FLS_PRIVATE_CODE) Fls_ErrorHandler
(
    Fls_JobType JobType,
    uint8 ErrorType
)
{
    if (FLS_JOB_COMPARE == JobType)
    {
        if (ErrorType != FLS_ERROR_TYPE_HW_FAIL)
        {
            /* Set the job result to MEMIF_BLOCK_INCONSISTENT. [SWS_Fls_00200] */
            Fls_State.JobResult = MEMIF_BLOCK_INCONSISTENT;
        }
        else
        {
            /* Set the job result to MEMIF_JOB_FAILED. [SWS_Fls_00154] */
            Fls_State.JobResult = MEMIF_JOB_FAILED;
        }
    }
    else if (FLS_JOB_BLANKCHECK == JobType)
    {
        if (ErrorType != FLS_ERROR_TYPE_HW_FAIL)
        {
            /* Set the job result to MEMIF_BLOCK_INCONSISTENT. [SWS_Fls_00200] */
            Fls_State.JobResult = MEMIF_BLOCK_INCONSISTENT;
        }
        else
        {
            Fls_State.JobResult = MEMIF_JOB_FAILED;
        }
    }
    else if (FLS_JOB_ERASE == JobType)
    {
        /* Set the job result to MEMIF_JOB_FAILED. [SWS_Fls_00104], [SWS_Fls_00022] */
        /* If this check fails, the function Fls_MainFunction shall set the
         * FLS module's job result to MEMIF_JOB_FAILED. [SWS_Fls_00022], [SWS_Fls_00055] */
        Fls_State.JobResult = MEMIF_JOB_FAILED;
        Fls_State.JobStarted.Erase = (boolean)FALSE;
    }
    else if (FLS_JOB_WRITE == JobType)
    {
        /* Set the job result to MEMIF_JOB_FAILED. [SWS_Fls_00105] */
        /* If this check fails, the function Fls_MainFunction shall set the
         * FLS module's job result to MEMIF_JOB_FAILED. [SWS_Fls_00056] */
        Fls_State.JobResult = MEMIF_JOB_FAILED;
        Fls_State.JobStarted.Write = (boolean)FALSE;
    }
    else
    {
        /* Set the job result to MEMIF_JOB_FAILED. [SWS_Fls_00106] */
        Fls_State.JobResult = MEMIF_JOB_FAILED;
    }
    Fls_InnerClearFlashAllStatus(Fls_State.JobAddress);
    /* Job completed, Set status to IDLE */
    Fls_State.JobType = FLS_JOB_NONE;
    /* Call callback function when FLS has finished a job with a negative result. [SWS_Fls_00347] */
    /* Call callback function when FLS has canceled an ongoing job. [SWS_Fls_00348] */
    /* FLS has finished a compare job and the memory blocks differ. [SWS_Fls_00348] */
    if (Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR)
    {
        (Fls_ConfigPtr->FlsJobErrorNotificationPtr)();
    }
}

/****************************************************************************************************
*   Function Name           : Fls_EndHandler
*
*   Service ID              : None.
*
*   Description             : This function handles the DFlash operate end.
*
*   Parameters in           : JobType: FLS_JOB_ERASE, FLS_JOB_WRITE etc.
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
static FUNC(void, FLS_PRIVATE_CODE) Fls_EndHandler
(
    Fls_JobType JobType
)
{
    if (FLS_JOB_ERASE == JobType)
    {
        /* Reset the erase job start flag */
        Fls_State.JobStarted.Erase = (boolean)FALSE;
    }
    else if (FLS_JOB_WRITE == JobType)
    {
        /* Reset the write job start flag */
        Fls_State.JobStarted.Write = (boolean)FALSE;
    }
    else
    /* #Violation: Fls_c_REF_14 */
    {
        /* Do Nothing */
    }

    /* Set the FLS module's job result to MEMIF_JOB_OK. [SWS_Fls_00345] */
    if (MEMIF_JOB_PENDING == Fls_State.JobResult)
    {
        Fls_State.JobResult = MEMIF_JOB_OK;
    }
    Fls_InnerClearFlashAllStatus(Fls_State.JobAddress);
    /* Set the FLS module's state to MEMIF_IDLE. [SWS_Fls_00346] */
    Fls_State.JobType = FLS_JOB_NONE;
    /* Call the job end notification function if configured. [SWS_Fls_00346] */
    /* Call callback function when FLS has completed a job with a positive result. [SWS_Fls_00167] */
    if (Fls_ConfigPtr != NULL_PTR)
    {
        if (Fls_ConfigPtr->FlsJobEndNotificationPtr != NULL_PTR)
        {
            (Fls_ConfigPtr->FlsJobEndNotificationPtr)();
        }
    }
}

/****************************************************************************************************
*   Function Name           : Fls_GetReadModeLength
*
*   Service ID              : None.
*
*   Description             : This function get max read length according to the FLS mode.
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
*   Return value            : max read length.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Fls_LengthType, FLS_PRIVATE_CODE) Fls_GetReadModeLength
(
    void
)
{
    Fls_LengthType MaxRead;

    /* Only process as much data in one call cycle as statically configured for current job type */
    /* and current FLS module's operating mode (normal, fast). [SWS_Fls_00040] */
    if (MEMIF_MODE_SLOW == Fls_State.Mode)
    {
        MaxRead = Fls_ConfigPtr->FlsSlowRead;
    }
    else
    {
        MaxRead = Fls_ConfigPtr->FlsFastRead;
    }

    return MaxRead;
}

/****************************************************************************************************
*   Function Name           : Fls_GetWriteLength
*
*   Service ID              : None.
*
*   Description             : This function get max write length in one burst.
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
*   Return value            : max write length.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Fls_LengthType, FLS_PRIVATE_CODE) Fls_GetWriteLength
(
    void
)
{
    Fls_LengthType MaxWrite;

    MaxWrite = 0;
    if (Fls_ConfigPtr != NULL_PTR)
    {
        /* Only process as much data in one call cycle as statically configured for current job type */
        /* and current FLS module's operating mode (normal, fast). [SWS_Fls_00040] */
        if (MEMIF_MODE_SLOW == Fls_State.Mode)
        {
            MaxWrite = Fls_ConfigPtr->FlsSlowWrite;
        }
        else
        {
            MaxWrite = Fls_ConfigPtr->FlsFastWrite;
        }
    }

    return MaxWrite;
}

/****************************************************************************************************
*   Function Name           : Fls_MainEraseJobStart
*
*   Service ID              : None.
*
*   Description             : This function starts the erase operation.
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
*   Return value            : Std_ReturnType: E_OK:     Operation successful.
*                                             E_NOT_OK: Error occurs.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainEraseJobStart
(
    void
)
{
#if (FLS_USE_INTERRUPTS == STD_OFF)
    uint32 IsOptOK;
#endif /* (FLS_USE_INTERRUPTS  \== STD_OFF) */
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
    uint64 TimerFreq;
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
    Std_ReturnType RetVal;
#if (FLS_SAFETY_ENABLE == STD_ON)
    Std_ReturnType FlashEraseRet;
#endif /* (FLS_SAFETY_ENABLE \== STD_ON) */

    RetVal = E_OK;
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
    /* Obtain STM clock frequency */
    /* #Violation: Fls_c_REF_4 */
    TimerFreq = (uint64)Mcal_GetSystemTimerFreq();
    /* Update Timeout count for erase a sector */
    /* Add one extra count since MainFunction needs to be called once after
       all the data is erased for checking errors and to set status */
    Fls_State.TimeoutCount = (FLS_ERASE_SECTOR_TIMEOUT_US +
                              ((uint64)Fls_ConfigPtr->FlsCallCycle)) * TimerFreq / 1000000ULL;
    /* Flash access routines shall disable interrupts (no other code is executed). [SWS_Fls_00215] */
    FLS_ENTER_CRITICAL_SECTION(EraseProtection);
    Fls_State.TimeoutCount += Mcal_GetSystemTimerCount();
#else /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
    /* Flash access routines shall disable interrupts (no other code is executed). [SWS_Fls_00215] */
    FLS_ENTER_CRITICAL_SECTION(EraseProtection);
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
    /* Mark Erase Job has been started */
    Fls_State.JobStarted.Erase = (boolean)TRUE;
    /* At the most issue one sector erase command (to the hardware) in each cycle. [SWS_Fls_00196] */
    /* execute erase operation */
#if (FLS_SAFETY_ENABLE == STD_ON)
    FlashEraseRet = Fls_InnerEraseSectorAsync(Fls_State.JobAddress);
    if (FlashEraseRet != E_OK)
    {
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                     FLS_SID_MAIN, FLS_E_REG_CHECK_FAILED);
        Fls_ErrorHandler(FLS_JOB_ERASE, FLS_ERROR_TYPE_HW_FAIL);
        RetVal = E_NOT_OK;
    }
#else /* (FLS_SAFETY_ENABLE  \== STD_ON) */
    (void)Fls_InnerEraseSectorAsync(Fls_State.JobAddress);
#endif /* (FLS_SAFETY_ENABLE  \== STD_ON) */
    FLS_EXIT_CRITICAL_SECTION(EraseProtection);
#if (FLS_USE_INTERRUPTS == STD_OFF)
    /* In interrupt mode, the hardware error flag check is executed in the interrupt handling
       function because after the error flag is set, the CPU will enter the interrupt handling
       function first and will not execute the following code first */
    /* Check hardware error flag */
    IsOptOK = Fls_InnerFlashOperateStatusRight(Fls_State.JobAddress);
    if (E_OK != IsOptOK)
    {
        /* Report the error code FLS_E_ERASE_FAILED to the DET. [SWS_Fls_00104] */
        /* When the flash erase function failed, Report FLS_E_ERASE_FAILED. [SWS_Fls_00315] */
        (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                       FLS_SID_MAIN, FLS_E_ERASE_FAILED);
        Fls_ErrorHandler(FLS_JOB_ERASE, FLS_ERROR_TYPE_HW_FAIL);
        RetVal = E_NOT_OK;
    }
#endif /* (FLS_USE_INTERRUPTS \== STD_OFF) */

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Fls_MainErase
*
*   Service ID              : None.
*
*   Description             : This function performs the erase operation.
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
*   Return value            : Std_ReturnType: E_OK:     Operation successful.
*                                             E_NOT_OK: Error occurs.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainErase
(
    void
)
{
    Std_ReturnType RetVal;
    Fls_LengthType SectorLength;
    const Fls_FlashHwParaType * Fls_FlashHwParas;

    RetVal = E_OK;
    /* Supports hardware verification function, so there is no need for software to verify. */
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_State.CurFlashType);
    if (Fls_State.JobLength <= Fls_FlashHwParas->SectorSize)
    {
         Fls_EndHandler(FLS_JOB_ERASE);
    }
    /* continue erase operation*/
    else
    {
        SectorLength = (Fls_FlashHwParas->SectorSize);
        /* Update Address, BufferPtr, Length */
        Fls_State.JobAddress += (Fls_AddressType)SectorLength;
        Fls_State.JobLength -= SectorLength;
#if (FLS_USE_INTERRUPTS == STD_ON)
        Fls_State.EraseFinish = FALSE;
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
        /* Continue erasing */
        RetVal = Fls_MainEraseJobStart();
    }

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Fls_MainEraseHandler
*
*   Service ID              : None.
*
*   Description             : This function handles the erase operation.
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
*   Return value            : Std_ReturnType: E_OK:     Operation successful.
*                                             E_NOT_OK: Error occurs.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainEraseHandler
(
    void
)
{
#if ((FLS_USE_INTERRUPTS == STD_OFF) || (FLS_ERASE_VERIFICATION_ENABLED == STD_ON))
    Fls_FlashResultStatus OperationError;
#endif /* \(\(FLS_USE_INTERRUPTS \== STD_OFF) \|| \(FLS_ERASE_VERIFICATION_ENABLED \== STD_ON)) */
    Std_ReturnType RetVal;

    RetVal = E_NOT_OK;
    if ((boolean)FALSE == Fls_State.JobStarted.Erase)
    {
        /* After calling Fls_Cancel, the hardware flag may not have been cleared yet.
           Clear the hardware flag before start a new job */
        Fls_InnerClearFlashAllStatus(Fls_State.JobAddress);
        /* start erase job, judging Flash type internally */
        RetVal = Fls_MainEraseJobStart();
    }
    else
    {
#if (FLS_USE_INTERRUPTS == STD_OFF)
        /* Erase will only have 3 states:
         * completion, busy, verification error */
        OperationError = Fls_InnerCheckHwEraseStatus(Fls_State.JobAddress);
        if (FLS_HW_RESULT_OK == OperationError)
        {
#if (FLS_ERASE_VERIFICATION_ENABLED == STD_ON)
            OperationError = Fls_InnerCheckFlashBlankSync(Fls_State.JobAddress, 
                                                          Fls_State.CurVerifyLen);
            if (FLS_HW_RESULT_OK != OperationError)
            {
                /* Erase verification fail, reported FLS_E_VERIFY_ERASE_FAILED. [SWS_Fls_00313] */
                /* After a flash block has been erased, check the block has been completely erased.
                *  If check fails raise runtime error FLS_E_VERIFY_ERASE_FAILED. [SWS_Fls_00022] */
                (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                            FLS_SID_MAIN, FLS_E_VERIFY_ERASE_FAILED);
                Fls_ErrorHandler(FLS_JOB_ERASE, FLS_ERROR_TYPE_HW_FAIL);
            }
            else
#endif /* (FLS_ERASE_VERIFICATION_ENABLED  \== STD_ON) */
            {
                RetVal = Fls_MainErase();
            }
        }
        else if(FLS_HW_RESULT_BUSY == OperationError)
        {
            RetVal = E_OK;
        }
        /* verification error */
        else
        {
            /* Report the error code FLS_E_ERASE_FAILED to the DET. [SWS_Fls_00104] */
            /* When the flash erase function failed, Report FLS_E_ERASE_FAILED. [SWS_Fls_00315] */
            (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                           FLS_SID_MAIN, FLS_E_ERASE_FAILED);
            Fls_ErrorHandler(FLS_JOB_ERASE, FLS_ERROR_TYPE_HW_FAIL);
        }
#else
        /* (FLS_USE_INTERRUPTS \== STD_ON) */
        /* Erase will only have 3 states:
         * completion, busy, verification error */
        if (TRUE == Fls_State.EraseFinish)
        {
            Fls_State.EraseFinish = FALSE;
#if (FLS_ERASE_VERIFICATION_ENABLED == STD_ON)
            OperationError = Fls_InnerCheckFlashBlankSync(Fls_State.JobAddress, 
                                                          Fls_State.CurVerifyLen);
            if (FLS_HW_RESULT_OK != OperationError)
            {
                /* Erase verification fail, reported FLS_E_VERIFY_ERASE_FAILED. [SWS_Fls_00313] */
                /* After a flash block has been erased, check the block has been completely erased.
                *  If check fails raise runtime error FLS_E_VERIFY_ERASE_FAILED. [SWS_Fls_00022] */
                (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                            FLS_SID_MAIN, FLS_E_VERIFY_ERASE_FAILED);
                Fls_ErrorHandler(FLS_JOB_ERASE, FLS_ERROR_TYPE_HW_FAIL);
            }
            else
#endif /* (FLS_ERASE_VERIFICATION_ENABLED  \== STD_ON) */
            {
                RetVal = Fls_MainErase();
            }
        }
#endif /* (FLS_USE_INTERRUPTS \== STD_OFF) */
    }

    return RetVal;
}
/****************************************************************************************************
*   Function Name           : Fls_MainWriteJobStart
*
*   Service ID              : None.
*
*   Description             : This function starts the write operation.
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
*   Return value            : Std_ReturnType: E_OK:     Operation successful.
*                                             E_NOT_OK: Error occurs.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainWriteJobStart
(
    uint32 Length
)
{
#if (FLS_USE_INTERRUPTS == STD_OFF)
    Std_ReturnType ErrorStatus;
#endif /* (FLS_USE_INTERRUPTS  \== STD_OFF) */
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
    uint64 TimerFreq;
    const Fls_FlashHwParaType * Fls_FlashHwParas;
    uint64 PwordCnt;
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
    Std_ReturnType RetVal;
#if (FLS_SAFETY_ENABLE == STD_ON)
    Std_ReturnType ProgRet;
#endif
    RetVal = E_OK;
    if (NULL_PTR != Fls_ConfigPtr)
    {
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
        Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_State.CurFlashType);
        PwordCnt = (uint64)(Fls_State.JobLength / Fls_FlashHwParas->FlashPWordSize);
        /* Obtain STM clock frequency and it no more than 0xFFFFFFFF */
        /* #Violation: Fls_c_REF_4 */
        TimerFreq = (uint64)Mcal_GetSystemTimerFreq();
        /* Add one extra count since MainFunction needs to be called once after
           all the data is written for checking errors and to set status */
        /* Convert timeout time to STM tick */
        Fls_State.TimeoutCount = (((FLS_WRITE_PAGE_TIMEOUT_US * PwordCnt) +
                                   ((uint64)Fls_ConfigPtr->FlsCallCycle)) * TimerFreq) / 1000000ULL;
        /* Flash access routines shall disable interrupts (no other code is executed). [SWS_Fls_00215] */
        FLS_ENTER_CRITICAL_SECTION(WriteProtection);
        /* #Violation: Fls_c_REF_4 */
        Fls_State.TimeoutCount += Mcal_GetSystemTimerCount();
#else /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
        /* Flash access routines shall disable interrupts (no other code is executed). [SWS_Fls_00215] */
        FLS_ENTER_CRITICAL_SECTION(WriteProtection);
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
        /* Mark Write Job has been started */
        Fls_State.JobStarted.Write = (boolean)TRUE;
        /* first mark then start the flow in case interrupt occurs before the flag set */
        /* The FLS module shall not buffer data. [SWS_Fls_00002] */
        /* Not ensure data consistency. [SWS_Fls_00003] */
#if (FLS_SAFETY_ENABLE == STD_ON)
        ProgRet = Fls_InnerProgramFlash(
                Fls_State.JobAddress,
                Fls_State.WriteBufferPtr,
                Length);
        if (E_OK != ProgRet)
        {
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                         FLS_SID_MAIN, FLS_E_WRITE_FAILED);
            Fls_ErrorHandler(FLS_JOB_WRITE, FLS_E_REG_CHECK_FAILED);
            RetVal = E_NOT_OK;
        }
#else /* (FLS_SAFETY_ENABLE  \== STD_ON) */
        (void)Fls_InnerProgramFlash(
            Fls_State.JobAddress,
            Fls_State.WriteBufferPtr,
            Length);
#endif /* (FLS_SAFETY_ENABLE  \== STD_ON) */
        FLS_EXIT_CRITICAL_SECTION(WriteProtection);
#if (FLS_USE_INTERRUPTS == STD_OFF)
        /* In interrupt mode, the hardware error flag check is executed in the interrupt handling
        function because after the error flag is set, the CPU will enter the interrupt handling
        function first and will not execute the following code first */
        /* Check hardware error flag */
        ErrorStatus = Fls_InnerFlashOperateStatusRight(Fls_State.JobAddress);
        if (ErrorStatus != E_OK)
        {
            /* Report the error code FLS_E_WRITE_FAILED to the DET. [SWS_Fls_00105] */
            /* When the flash write function failed, Report FLS_E_WRITE_FAILED. [SWS_Fls_00316] */
            (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                        FLS_SID_MAIN, FLS_E_WRITE_FAILED);
            Fls_ErrorHandler(FLS_JOB_WRITE, FLS_ERROR_TYPE_HW_FAIL);
            RetVal = E_NOT_OK;
        }
#endif /* (FLS_USE_INTERRUPTS \== STD_OFF) */
    }
    else
    {
        RetVal = E_NOT_OK;
    }
    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Fls_MainWrite
*
*   Service ID              : None.
*
*   Description             : This function performs the write operation.
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
*   Return value            : Std_ReturnType: E_OK:     Operation successful.
*                                             E_NOT_OK: Error occurs.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainWrite
(
    void
)
{
    Fls_LengthType JobLength;
    Fls_LengthType MaxWriteSize;
    Std_ReturnType RetVal;
    const Fls_FlashHwParaType * Fls_FlashHwParas;

    MaxWriteSize = Fls_GetWriteLength();
    if (Fls_State.JobLength > MaxWriteSize)
    {
        /* Max Byte to write in one MainFunction */
        JobLength = MaxWriteSize;
    }
    else
    {
        JobLength = Fls_State.JobLength;
    }
    /* Calculate the remaining writable size in the ROW where the write address is located. */
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_State.CurFlashType);
    MaxWriteSize = Fls_FlashHwParas->FlashRowSize -
                    (Fls_State.JobAddress & (Fls_FlashHwParas->FlashRowSize - 1U));
    if (JobLength > MaxWriteSize)
    {
        JobLength = MaxWriteSize;
    }
    /* Supports hardware verification function, so there is no need for software to verify. */
    /* Clear all status before the next erase flow */
    Fls_InnerClearFlashAllStatus(Fls_State.JobAddress);
    /* Check for Flash write Job is finished completely */
    if (Fls_State.JobLength <= JobLength)
    {
        Fls_EndHandler(FLS_JOB_WRITE);
        RetVal = E_OK;
    }
    else
    {
        /* Update Address, BufferPtr, Length */
        Fls_State.JobAddress += JobLength;
        Fls_State.WriteBufferPtr = &Fls_State.WriteBufferPtr[JobLength];
        Fls_State.JobLength -= JobLength;
        MaxWriteSize = Fls_GetWriteLength();
        if (Fls_State.JobLength > MaxWriteSize)
        {
            /* Max Byte to write in one MainFunction */
            JobLength = MaxWriteSize;
        }
        else
        {
            JobLength = Fls_State.JobLength;
        }
        /* Calculate the remaining writable size in the ROW where the write address is located. */
        MaxWriteSize = Fls_FlashHwParas->FlashRowSize -
            (Fls_State.JobAddress & (Fls_FlashHwParas->FlashRowSize - 1U));
        if (JobLength > MaxWriteSize)
        {
            JobLength = MaxWriteSize;
        }
        Fls_State.CurVerifyLen = JobLength;
#if (FLS_USE_INTERRUPTS == STD_ON)
        Fls_State.WriteFinish = FALSE;
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
        /* continue write */
        RetVal = Fls_MainWriteJobStart(JobLength);
    }

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Fls_MainWriteHandler
*
*   Service ID              : None.
*
*   Description             : This function handles the write operation.
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
*   Return value            : Std_ReturnType: E_OK:     Operation successful.
*                                             E_NOT_OK: Error occurs.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
static FUNC(Std_ReturnType, FLS_PRIVATE_CODE) Fls_MainWriteHandler
(
    void
)
{
    Fls_LengthType Length;
    Fls_LengthType MaxWriteSize;
#if (FLS_USE_INTERRUPTS == STD_OFF)
    Fls_FlashResultStatus OperationError;
#endif /* (FLS_USE_INTERRUPTS \== STD_ON) */
#if (FLS_ERASE_VERIFICATION_ENABLED == STD_ON)
    Fls_FlashResultStatus DriverResult;
#endif /* (FLS_ERASE_VERIFICATION_ENABLED  \== STD_ON) */
#if (FLS_WRITE_VERIFICATION_ENABLED == STD_ON)
    Std_ReturnType compState;
#endif /* (FLS_WRITE_VERIFICATION_ENABLED  \== STD_ON) */
    Std_ReturnType RetVal;
    const Fls_FlashHwParaType * Fls_FlashHwParas;

    RetVal = E_NOT_OK;
    if ((boolean)FALSE == Fls_State.JobStarted.Write)
    {
        /* After calling Fls_Cancel, the hardware flag may not have been cleared yet.
           Clear the hardware flag before start a new job */
        Fls_InnerClearFlashAllStatus(Fls_State.JobAddress);
#if (FLS_ERASE_VERIFICATION_ENABLED == STD_ON)
        /* Before writing a block, MainFunction check block has been erased. [SWS_Fls_00055] */
        DriverResult = Fls_InnerCheckFlashBlankSync(Fls_State.JobAddress, Fls_State.JobLength);
        if (FLS_HW_RESULT_OK != DriverResult)
        {
            /* If this check fails, the function Fls_MainFunction shall set the
               FLS module's job result to MEMIF_JOB_FAILED and raise the runtime error
               FLS_E_VERIFY_ERASE_FAILED. [SWS_Fls_00055] */
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN,
                                  FLS_E_VERIFY_ERASE_FAILED);
            /* When the flash write function failed, Report FLS_E_WRITE_FAILED. [SWS_Fls_00316] */
            (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                           FLS_SID_MAIN, FLS_E_WRITE_FAILED);
            Fls_ErrorHandler(FLS_JOB_WRITE, FLS_ERROR_TYPE_SW_FAIL);
        }
        else
#endif /* (FLS_ERASE_VERIFICATION_ENABLED  \== STD_ON) */
        {
            MaxWriteSize = Fls_GetWriteLength();
            if (Fls_State.JobLength > MaxWriteSize)
            {
                /* Max Byte to write in one MainFunction */
                Length = MaxWriteSize;
            }
            else
            {
                Length = Fls_State.JobLength;
            }
            /* Calculate the remaining writable size in the ROW where the write address is located. */
            /* #Violation: Fls_c_REF_4 */
            Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_State.CurFlashType);
            MaxWriteSize = (Fls_FlashHwParas->FlashRowSize -
                (Fls_State.JobAddress & (Fls_FlashHwParas->FlashRowSize - 1U)));
            /* If the current write length exceeds the writable size, it must be adjusted to
               the writable size */
            if (Length > MaxWriteSize)
            {
                Length = MaxWriteSize;
            }
            Fls_State.CurVerifyLen = Length;
            /* start write job */
            RetVal = Fls_MainWriteJobStart(Length);
        }
    }
    else
    {
#if (FLS_USE_INTERRUPTS == STD_OFF)
        /* Write will only have 5 states:
         * completion, busy, verification error, timeout, unaligned */
        OperationError = Fls_InnerCheckHwWriteStatus(Fls_State.JobAddress);
        if (FLS_HW_RESULT_OK == OperationError)
        {
#if (FLS_WRITE_VERIFICATION_ENABLED == STD_ON)
            /* #Violation: Fls_c_REF_5 */
            /* #Violation: Fls_c_REF_11 */
            compState = Fls_InnerCheckWriteReadback(Fls_State.JobAddress, (const uint32 *)Fls_State.WriteBufferPtr, 
                                                                Fls_State.CurVerifyLen);
            if (E_OK != compState)
            {
                /* Write verification fail, reported FLS_E_VERIFY_WRITE_FAILED. [SWS_Fls_00314] */
                /* After writing a flash block, check the block has been completely reprogrammed.
                * If check fails raise runtime error FLS_E_VERIFY_WRITE_FAILED. [SWS_Fls_00056] */
                (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                            FLS_SID_MAIN, FLS_E_VERIFY_WRITE_FAILED);
                Fls_ErrorHandler(FLS_JOB_WRITE, FLS_ERROR_TYPE_HW_FAIL);
            }
            else
#endif /* (FLS_ERASE_VERIFICATION_ENABLED  \== STD_ON) */
            {
                RetVal = Fls_MainWrite();
            }
        }
        else if (FLS_HW_RESULT_BUSY == OperationError)
        {
            RetVal = E_OK;
        }
        /* verification error */
        else if (FLS_HW_RESULT_FAILED == OperationError)
        {
            /* Report the error code FLS_E_WRITE_FAILED to the DET. [SWS_Fls_00105] */
            /* When the flash write function failed, Report FLS_E_WRITE_FAILED. [SWS_Fls_00316] */
            (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                           FLS_SID_MAIN, FLS_E_WRITE_FAILED);
#if (FLS_WRITE_VERIFICATION_ENABLED == STD_ON)
            /* Write verification fail, reported FLS_E_VERIFY_WRITE_FAILED. [SWS_Fls_00314] */
            /* After writing a flash block, check the block has been completely reprogrammed.
             * If check fails raise runtime error FLS_E_VERIFY_WRITE_FAILED. [SWS_Fls_00056] */
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                         FLS_SID_MAIN, FLS_E_VERIFY_WRITE_FAILED);
#endif /* (FLS_ERASE_VERIFICATION_ENABLED  \== STD_ON) */
            Fls_ErrorHandler(FLS_JOB_WRITE, FLS_ERROR_TYPE_HW_FAIL);
        }
        /* timeout, unaligned */
        else
        {
            /* Report the error code FLS_E_WRITE_FAILED to the DET. [SWS_Fls_00105] */
            /* When the flash write function failed, Report FLS_E_WRITE_FAILED. [SWS_Fls_00316] */
            (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                           FLS_SID_MAIN, FLS_E_WRITE_FAILED);
            Fls_ErrorHandler(FLS_JOB_WRITE, FLS_ERROR_TYPE_HW_FAIL);
        }
#else
        /* (FLS_USE_INTERRUPTS \== STD_ON) */
        if (TRUE == Fls_State.WriteFinish)
        {
            Fls_State.WriteFinish = FALSE;
#if (FLS_WRITE_VERIFICATION_ENABLED == STD_ON)
            /* #Violation: Fls_c_REF_5 */
            /* #Violation: Fls_c_REF_11 */
            compState = Fls_InnerCheckWriteReadback(Fls_State.JobAddress, (const uint32 *)Fls_State.WriteBufferPtr, 
                                                                Fls_State.CurVerifyLen);
            if (E_OK != compState)
            {
                /* Write verification fail, reported FLS_E_VERIFY_WRITE_FAILED. [SWS_Fls_00314] */
                /* After writing a flash block, check the block has been completely reprogrammed.
                * If check fails raise runtime error FLS_E_VERIFY_WRITE_FAILED. [SWS_Fls_00056] */
                (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                            FLS_SID_MAIN, FLS_E_VERIFY_WRITE_FAILED);
                Fls_ErrorHandler(FLS_JOB_WRITE, FLS_ERROR_TYPE_HW_FAIL);
            }
            else
#endif /* (FLS_ERASE_VERIFICATION_ENABLED  \== STD_ON) */
            {
                RetVal = Fls_MainWrite();
            }
        }
#endif /* FLS_USE_INTERRUPTS \== STD_OFF */
    }

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Fls_MainCompareHandler
*
*   Service ID              : None.
*
*   Description             : This function performs the compare operation.
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
static FUNC(void, FLS_PRIVATE_CODE) Fls_MainCompareHandler
(
    void
)
{
    Fls_LengthType CompareCount;
    uint32 SourceAddr;
    Fls_LengthType MaxRead;
    boolean EccErrorFlag;
    MemIf_JobResultType LastJobResult;

    MaxRead = Fls_GetReadModeLength();
    if (Fls_State.JobLength > MaxRead)
    {
        /* Max Byte to read in one MainFunction */
        CompareCount = MaxRead;
    }
    else
    {
        CompareCount = Fls_State.JobLength;
    }

    SourceAddr = Fls_State.JobAddress;
    Fls_State.JobLength -= CompareCount;
    LastJobResult = MEMIF_JOB_PENDING;
    /* The FLS module shall not buffer data. [SWS_Fls_00002] */
    /* Not ensure data consistency. [SWS_Fls_00003] */
    /* \[SWS_Fls_00385] the function Fls_MainFunction shall internally compensate for missing
       alignment, that is the function Fls_MainFunction shall provide byte-wise read access to
       the flash memory, regardless of any alignment restrictions imposed by the Hardware. */
    do
    {
        /* Check if Address is word aligned */
        if (((SourceAddr & FLS_WORD_SIZE_MASK) == 0U) &&
            /* #Violation: Fls_c_REF_3 */
            ((((uint32)(Fls_State.CompareBufferPtr) & FLS_WORD_SIZE_MASK) == 0U) &&
             (CompareCount >= FLS_WORD_SIZE_TO_BTYE)))
        {
            /* Word alignment compare */
            /* #Violation: Fls_c_REF_17 */
            /* #Violation: Fls_c_REF_5 */
            /* #Violation: Fls_c_REF_11*/
            /* #Violation: Fls_c_REF_12*/
            /* #Violation: Fls_c_REF_15 */
            /* #Violation: Fls_c_REF_15 */
            /* #Violation: Fls_c_REF_16 */
            if ( *((const uint32*)Fls_State.CompareBufferPtr) != *((const uint32 *)SourceAddr) )
            {
                LastJobResult = MEMIF_BLOCK_INCONSISTENT;
                CompareCount = 0U;
            }
            else
            {
                Fls_State.CompareBufferPtr = &(Fls_State.CompareBufferPtr[FLS_WORD_SIZE_TO_BTYE]);
                SourceAddr += FLS_WORD_SIZE_TO_BTYE;
                CompareCount -= FLS_WORD_SIZE_TO_BTYE;
            }
        }
        else
        {
            /* Byte alignment compare */
            /* #Violation: Fls_c_REF_17 */
            /* #Violation: Fls_c_REF_12*/
            /* #Violation: Fls_c_REF_15 */
            if (*(Fls_State.CompareBufferPtr) != *((uint8 *)SourceAddr))
            {
                LastJobResult = MEMIF_BLOCK_INCONSISTENT;
                CompareCount = 0U;
            }
            else
            {
                Fls_State.CompareBufferPtr++;
                SourceAddr++;
                CompareCount--;
            }
        }
    } while (CompareCount > 0U);
    /* Update the compare address */
    Fls_State.JobAddress = SourceAddr;
    /* Check for ECC errors */
    EccErrorFlag = Fls_InnerGetFlashEccStatus(Fls_State.JobAddress);
    if (FALSE == EccErrorFlag)
    {
        if (LastJobResult == MEMIF_BLOCK_INCONSISTENT)
        {
            Fls_ErrorHandler(FLS_JOB_COMPARE, FLS_ERROR_TYPE_SW_FAIL);
        }
        else
        {
            /* completed */
            if (0U == Fls_State.JobLength)
            {
                Fls_EndHandler(FLS_JOB_COMPARE);
            }
        }
    }
    else
    {
        FLS_ENTER_CRITICAL_SECTION(Compare);
        /* Clear ECC error flag */
        (void)Fls_InnerClearFlashEccStatus(Fls_State.JobAddress);
        FLS_EXIT_CRITICAL_SECTION(Compare);
        /* Report the error code FLS_E_COMPARE_FAILED to the DET. [SWS_Fls_00154] */
        /* When the flash compare function failed, Report FLS_E_COMPARE_FAILED. [SWS_Fls_00318] */
        (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                       FLS_SID_MAIN, FLS_E_COMPARE_FAILED);
        Fls_ErrorHandler(FLS_JOB_COMPARE, FLS_ERROR_TYPE_HW_FAIL);
    }
}

/****************************************************************************************************
*   Function Name           : Fls_MainReadHandler
*
*   Service ID              : None.
*
*   Description             : This function performs the read operation.
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
static FUNC(void, FLS_PRIVATE_CODE) Fls_MainReadHandler
(
    void
)
{
    Fls_LengthType ReadCount;
    uint32 SourceAddr;
    Fls_LengthType MaxRead;
    boolean EccErrorFlag;

    MaxRead = Fls_GetReadModeLength();
    if (Fls_State.JobLength > MaxRead)
    {
        ReadCount = MaxRead;
    }
    else
    {
        ReadCount = Fls_State.JobLength;
    }

    SourceAddr = Fls_State.JobAddress;
    Fls_State.JobLength -= ReadCount;
    /* The FLS module shall not buffer data. [SWS_Fls_00002] */
    /* Not ensure data consistency. [SWS_Fls_00003] */
    /* \[SWS_Fls_00385] the function Fls_MainFunction shall internally compensate for missing
       alignment, that is the function Fls_MainFunction shall provide byte-wise read access to
       the flash memory, regardless of any alignment restrictions imposed by the Hardware. */
    do
    {
        /* Word alignment allows for reading one word at a time */
        if (((SourceAddr & FLS_WORD_SIZE_MASK) == 0U) &&
             /* #Violation: Fls_c_REF_3 */
            ((((uint32)(Fls_State.ReadBufferPtr) & FLS_WORD_SIZE_MASK) == 0U) &&
             (ReadCount >= FLS_WORD_SIZE_TO_BTYE)))
        {
            /* Word alignment reading */
            /* #Violation: Fls_c_REF_17 */
            /* #Violation: Fls_c_REF_5 */
            /* #Violation: Fls_c_REF_11*/
            /* #Violation: Fls_c_REF_12*/
            /* #Violation: Fls_c_REF_15 */
            /* #Violation: Fls_c_REF_15 */
            /* #Violation: Fls_c_REF_16 */
            *((uint32*)Fls_State.ReadBufferPtr) = *(uint32 *)SourceAddr;

            Fls_State.ReadBufferPtr = &(Fls_State.ReadBufferPtr[FLS_WORD_SIZE_TO_BTYE]);
            SourceAddr += FLS_WORD_SIZE_TO_BTYE;
            ReadCount -= FLS_WORD_SIZE_TO_BTYE;
        }
        else
        {
            /* Byte alignment reading */
            /* #Violation: Fls_c_REF_12*/
            /* #Violation: Fls_c_REF_17 */
            /* #Violation: Fls_c_REF_15 */
            *(Fls_State.ReadBufferPtr) = *((uint8 *)SourceAddr);
            (Fls_State.ReadBufferPtr)++;
            SourceAddr++;
            ReadCount--;
        }
    } while (ReadCount > 0U);
    Fls_State.JobAddress = SourceAddr;
    /* Check for ECC errors */
    EccErrorFlag = Fls_InnerGetFlashEccStatus(Fls_State.JobAddress);
    if (FALSE == EccErrorFlag)
    {
        /* reading completed */
        if (0U == Fls_State.JobLength)
        {
            Fls_EndHandler(FLS_JOB_READ);
        }
    }
    else
    {
        FLS_ENTER_CRITICAL_SECTION(Read);
        /* Clear ECC error flag */
        (void)Fls_InnerClearFlashEccStatus(Fls_State.JobAddress);
        FLS_EXIT_CRITICAL_SECTION(Read);
        /* Report the error code FLS_E_READ_FAILED to the DET. [SWS_Fls_00106] */
        /* When the flash read function failed, Report FLS_E_READ_FAILED. [SWS_Fls_00317] */
        (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                       FLS_SID_MAIN, FLS_E_READ_FAILED);
        Fls_ErrorHandler(FLS_JOB_READ, FLS_ERROR_TYPE_HW_FAIL);
    }
}

#if (FLS_BLANK_CHECK_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_MainCheckHandler
*
*   Service ID              : None.
*
*   Description             : This function handles the blankcheck operation.
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
static FUNC(void, FLS_PRIVATE_CODE) Fls_MainCheckHandler
(
    void
)
{
    Fls_LengthType PageLength;
    Fls_LengthType MaxCheckSize;
    Fls_FlashResultStatus DriverResult;
    uint32 SizeNeedToAlign;
    uint32 FlashPageSizeMask;
    uint32 FlashPageSize;
    const Fls_FlashHwParaType *Fls_FlashHwParas;
    Fls_AddressType FlashUnAlignedPageLength;

    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_State.CurFlashType);
    FlashPageSizeMask = Fls_FlashHwParas->FlashPWordSize - 1U;
    FlashPageSize = Fls_FlashHwParas->FlashPWordSize;
    /* \[SWS_Fls_00385] the function Fls_MainFunction shall internally compensate for missing
       alignment, that is the function Fls_MainFunction shall provide byte-wise read access to
       the flash memory, regardless of any alignment restrictions imposed by the Hardware. */
    MaxCheckSize = Fls_GetReadModeLength();
    if (Fls_State.JobLength > MaxCheckSize)
    {
        /* Calculate the actual size of the blank check in this MainFunction */
        PageLength = MaxCheckSize;
        /* Calculate the remaining blank check size */
        Fls_State.JobLength -= (MaxCheckSize - (Fls_State.JobAddress & FlashPageSizeMask));
    }
    else
    {
        /* Calculate the actual size of the blank check in this MainFunction */
        FlashUnAlignedPageLength = (Fls_State.JobAddress & FlashPageSizeMask);
        PageLength = (((FlashUnAlignedPageLength + Fls_State.JobLength +
                        FlashPageSizeMask) / FlashPageSize) * FlashPageSize);
        /* Completed blank check */
        Fls_State.JobLength = 0U;
    }
    /* The blankcheck address requires Pword alignment */
    SizeNeedToAlign = (Fls_State.JobAddress & FlashPageSizeMask);
    Fls_State.JobAddress -= SizeNeedToAlign;
    /* Synchronize to determine if the flash area is empty */
    DriverResult = Fls_InnerCheckFlashBlankSync(Fls_State.JobAddress, PageLength);

    if (FLS_HW_RESULT_OK == DriverResult)
    {
        /* Update addresses that have already been checked after the current job is successful */
        Fls_State.JobAddress += PageLength;
        /* Check for Flash check Job is finished completely */
        if (0U == Fls_State.JobLength)
        {
            Fls_EndHandler(FLS_JOB_BLANKCHECK);
        }
    }
    /* End the current job if the current address is not blank */
    else if (FLS_HW_RESULT_FAILED == DriverResult)
    {
        Fls_ErrorHandler(FLS_JOB_BLANKCHECK, FLS_ERROR_TYPE_SW_FAIL);
    }
    else
    {
        (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                       FLS_SID_MAIN, FLS_E_BLANKCHECK_FAILED);
        Fls_ErrorHandler(FLS_JOB_BLANKCHECK, FLS_ERROR_TYPE_HW_FAIL);
    }
}
#endif /* (FLS_BLANK_CHECK_API  \== STD_ON) */

#if (FLS_DEV_ERROR_DETECT == STD_ON)
/****************************************************************************************************
 *   Function Name           : Fls_CompareWordsSyncDetCheck
 *
 *   Service ID              : None.
 *
 *   Description             : This API returns the Det error of Fls_CompareWordsSyncDetCheck.
 *
 *   Parameters in           : Error: Prevous det check status.
 *                             SourceAddress: Source address.
 *                             TargetAddressPtr: Target adress pointer.
 *                             Length: Memory length
 *
 *   Parameters inout        : None.
 *
 *   Parameters out          : None.
 *
 *   Sync/Async              : Synchronous.
 *
 *   Reentrancy              : Reentrant.
 *
 *   Return value            : E_OK: DET check passed.
 *                             E_NOT_OK: DET check failed.
 *
 *   Preconditions           : None.
 *
 *   AUTOSAR_Requirement     : None.
 ****************************************************************************************************/
static FUNC(uint8, FLS_PRIVATE_CODE) Fls_CompareWordsSyncDetCheck
(
    uint8 Error,
    Fls_AddressType SourceAddress,
    CONSTP2CONST(uint32, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
    Fls_LengthType Length
)
{
    uint8 RetVal;
    Fls_AddressType FlashOffsetAddress;
    Fls_OptFlashType Fls_CurFlashType;
    const Fls_FlashHwParaType * Fls_FlashHwParas;
    RetVal = FLS_COMPARE_PARAM_ERR;

    /* #Violation: Fls_c_REF_4 */
    Fls_CurFlashType = FLS_GET_FLASH_TYPE(SourceAddress);
    FlashOffsetAddress = Fls_InnerGetOffsetAddress(SourceAddress, Fls_CurFlashType);
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_CurFlashType);
    if (Error != FLS_NO_DET_ERROR)
    {
        RetVal = FLS_COMPARE_PARAM_ERR;
    }
    /* Checking whether given SourceAddress is valid or not. */
    /* The read address must be 4-byte aligned. */
    else if ((FlashOffsetAddress >= Fls_FlashHwParas->FlashSize) || ((FlashOffsetAddress & FLS_WORD_SIZE_MASK) != 0U))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                              FLS_SID_COMPARESYNC, FLS_E_PARAM_ADDRESS);
    }
    /* Check the given data buffer pointer for not being a null pointer. */
    else if ((NULL_PTR == TargetAddressPtr) ||
             /* #Violation: Fls_c_REF_3 */
             (((uint32)TargetAddressPtr & FLS_WORD_SIZE_MASK) != 0U))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARESYNC, FLS_E_PARAM_DATA);
    }
    /* Checking whether given Length is valid or not. */
    else if ((0U == Length) || ((FlashOffsetAddress + Length) > Fls_FlashHwParas->FlashSize))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                              FLS_SID_COMPARESYNC, FLS_E_PARAM_LENGTH);
    }
    else
    {
        RetVal = E_OK;
    }

    return RetVal;
}
#endif /* \(FLS_DEV_ERROR_DETECT \== STD_ON\) */
#if (FLS_WRITE_VERIFICATION_ENABLED == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_InnerCheckWriteReadback
*
*   Service ID              : NA.
*
*   Description             : This function compares the flash synchronously.
*
*   Parameters in           : SourceAddress: source address in flash memory.
*                             TargetAddressPtr: Pointer to target data buffer.
*                             Length: number of bytes.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK:        The data being compared is equal.
*                             E_NOT_OK:    The data being compared is not equal.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Fls_c_REF_6 */
static FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_InnerCheckWriteReadback
(
    Fls_AddressType SourceAddress,
    CONSTP2CONST(uint32, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
    Fls_LengthType Length
)
{
    const uint32 * SrcPtr;
    Std_ReturnType RetVal;
    Fls_LengthType RestLength;
    const uint32 * CompareTargetAddressPtr;

    /* #Violation: Fls_c_REF_17 */
    /* #Violation: Fls_c_REF_12*/
    SrcPtr = (uint32 *)SourceAddress;
    RetVal = E_OK;
    RestLength = Length;
    CompareTargetAddressPtr = TargetAddressPtr;
    do
    {
        if ((CompareTargetAddressPtr[0]) != SrcPtr[0])
        {
            RetVal = E_NOT_OK;
            RestLength = 0U;
        }
        else
        {
            CompareTargetAddressPtr++;
            SrcPtr++;
            RestLength-=4U;
        }
    } while (RestLength > 0U);

    return RetVal;
}
#endif /* \(FLS_WRITE_VERIFICATION_ENABLED \== STD_ON) */

/* #Violation: Fls_c_REF_9 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"

/****************************************************************************************************
**                          Global Function Definitions                                            **
****************************************************************************************************/
/* #Violation: Fls_c_REF_9 */
#define FLS_START_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"
/****************************************************************************************************
*   Function Name           : Fls_Init
*
*   Service ID              : 0x00.
*
*   Description             : This function initializes the Flash Driver.
*
*   Parameters in           : ConfigPtr: Pointer to flash driver configuration set
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
*   AUTOSAR_Requirement     : SWS_Fls_00249.
****************************************************************************************************/
/* #Violation: Fls_c_REF_6 */
FUNC(void, FLS_PUBLIC_CODE) Fls_Init
(
    /* #Violation: Fls_c_REF_7 */
    /* #Violation: Fls_c_REF_10*/
    P2CONST(Fls_ConfigType, AUTOMATIC, FLS_CONFIG_CONST) ConfigPtr
)
{
    Std_ReturnType RetVal;
#if (FLS_USE_INTERRUPTS == STD_ON)
    boolean ConfigIntRet;
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
    boolean OperationRslt;

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    Std_ReturnType DetCheckResultValue;
    Mcal_CoreType CoreId;

    DetCheckResultValue = E_NOT_OK;
    /* Get core id which is executing currently */
    /* #Violation: Fls_c_REF_4 */
    CoreId = Mcal_GetCoreId();

    if (FLS_CORE_ALLOCATION != (uint8)CoreId)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT,
                              FLS_E_CORE_NOT_CONFIGURED);
    }
    /* Shall check contents of the given configuration set. [SWS_Fls_00015] */
    else if (ConfigPtr == NULL_PTR)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_PARAM_CONFIG);

    }
    /* Check if the driver is BUSY. [SWS_Fls_00268] */
    else if ((Fls_State.JobType != FLS_JOB_NONE) && (Fls_State.JobType != FLS_JOB_UNINIT))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_BUSY);
    }
    else
    {
        DetCheckResultValue = E_OK;
    }

    if (E_OK == DetCheckResultValue)
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Store the pointer to the given configuration set in a variable. [SWS_Fls_00191] */
        Fls_ConfigPtr = ConfigPtr;

        /* Initialize Flash relevant registers (hardware). [SWS_Fls_00014] */
        RetVal = Fls_InnerInit();
        if (E_OK == RetVal)
        {
#if (FLS_USE_INTERRUPTS == STD_ON)
            ConfigIntRet = Fls_InnerEnableFlashInt();
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
#if (FLS_DF_ECC_TRIGGER_BUS_ERROR_MASK_ENABLE == STD_ON)
            OperationRslt = Flash_Hal_ConfigDFlashEccBusErrorAlarm(DFLASH_INTOP_DISABLE);
#else /* (FLS_DF_ECC_TRIGGER_BUS_ERROR_MASK_ENABLE \== STD_ON) */
            OperationRslt = Flash_Hal_ConfigDFlashEccBusErrorAlarm(DFLASH_INTOP_ENABLE);
#endif /* (FLS_DF_ECC_TRIGGER_BUS_ERROR_MASK_ENABLE  \== STD_ON) */
#if (FLS_USE_INTERRUPTS == STD_ON)
            if (TRUE == ConfigIntRet)
            {
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
                if (TRUE == OperationRslt)
                {
                    /* Set JobResult to MEMIF_JOB_OK after finished Fls initialization. 
                       [SWS_Fls_00324] */
                    Fls_State.JobResult = MEMIF_JOB_OK;
                    /* Initialize all FLS module global variables. [SWS_Fls_00086] */
                    Fls_State.JobStarted.Write = (boolean)FALSE;
                    Fls_State.JobStarted.Erase = (boolean)FALSE;
#if (FLS_USE_INTERRUPTS == STD_ON)
                    /* Set Cancel flag, Prevent interrupt logic exceptions */
                    Fls_State.JobCanceling = FALSE;
                    Fls_State.EraseFinish = FALSE;
                    Fls_State.WriteFinish = FALSE;
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
                    Fls_State.TimeoutCount = 0U;
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
                    Fls_State.ReadBufferPtr = NULL_PTR;
                    Fls_State.CompareBufferPtr = NULL_PTR;
                    Fls_State.WriteBufferPtr = NULL_PTR;
                    /* Assign default mode */
                    Fls_State.Mode = Fls_ConfigPtr->FlsDefaultMode;
                    /* Set FLS module state to MEMIF_IDLE after finished initialization. 
                       [SWS_Fls_00323] */
                    Fls_State.JobType = FLS_JOB_NONE;
                    /* Set FLS current Flash type which will change before job excuted */
                    Fls_State.CurFlashType = FLS_DFLASH_REGION;
                    Fls_State.CurVerifyLen = 0U;
                }
                else
                {
                    /* If the DFLASH bus error mask configuration failed (e.g. related register write
                       verification failed), The runtime error FLS_E_INIT_FAILED will be reported. */
                    (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT,
                                           FLS_E_INIT_FAILED);
                }
#if (FLS_USE_INTERRUPTS == STD_ON)
            }
            else 
            {
                /* If the FLASH interrupt configuration failed (e.g. related register write
                   verification failed), The runtime error FLS_E_INIT_FAILED will be reported. */
                (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, 
                                       FLS_E_INIT_FAILED);
            }
#endif /* \(FLS_USE_INTERRUPTS \== STD_ON) */
        }
        else
        {
            /* If flash register write verification fails or other Flash HAL errors occur, 
               the runtime error FLS_E_INIT_FAILED will be reported. */
            (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INIT, FLS_E_INIT_FAILED);
        }
    }
}

/****************************************************************************************************
*   Function Name           : Fls_Erase
*
*   Service ID              : 0x01.
*
*   Description             : This function erases flash sectors.
*
*   Parameters in           : TargetAddress: target address
*                             Length: number of bytes to erase
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: erase command has been accepted.
*                             E_NOT_OK: erase command has not been accepted
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Fls_00250.
****************************************************************************************************/
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Erase
(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
)
{
    Std_ReturnType RetVal;
    Fls_AddressType FlashOffsetAddress;
    const Fls_FlashHwParaType * Fls_FlashHwParas;
    Fls_OptFlashType Fls_CurFlashType;

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */

    /* #Violation: Fls_c_REF_4 */
    Fls_CurFlashType = FLS_GET_FLASH_TYPE(TargetAddress);
    FlashOffsetAddress = Fls_InnerGetOffsetAddress(TargetAddress, Fls_CurFlashType);
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_CurFlashType);

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    RetVal = E_NOT_OK;
    /* Check that the FLS module has been initialized. [SWS_Fls_00065] */
    Error = Fls_CommonDetCheck(FLS_SID_ERASE, TargetAddress, Length);

    if (Error != FLS_NO_DET_ERROR)
    /* #Violation: Fls_c_REF_14 */
    {
        /* Do Nothing */
    }
    /* Check address within the flash address boundary. [SWS_Fls_00020] */
    else if ((Fls_FlashHwParas->FlashBaseAddress + FlashOffsetAddress) >= Fls_FlashHwParas->FlashEndAddress)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_PARAM_ADDRESS);
    }
    /* Align to sector boundary. [SWS_Fls_00020] */
    else if ((FlashOffsetAddress & (Fls_FlashHwParas->SectorSize - 1U)) != 0U)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_PARAM_ADDRESS);
    }
    /* Check whether given Length is valid or not. [SWS_Fls_00021] */
    else if ((((Fls_FlashHwParas->FlashBaseAddress + FlashOffsetAddress) + Length - 1U) > Fls_FlashHwParas->FlashEndAddress) ||
            (0U == Length) )
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_PARAM_LENGTH);
    }
    /* Check whether the Length is aligned  */
    else if ((Length & (Fls_FlashHwParas->SectorSize - 1U)) != 0U)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_PARAM_LENGTH);
    }
    else
    {
        RetVal = E_OK;
    }

    if (E_OK == RetVal)
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        FLS_ENTER_CRITICAL_SECTION(Erase);
        if (FLS_JOB_NONE == Fls_State.JobType)
        {
            /* Erase one or more complete flash sectors. [SWS_Fls_00218] */
            /* Copy the given parameters to FLS module internal variables. [SWS_Fls_00327] */
            /* Set the job result to MEMIF_JOB_PENDING. [SWS_Fls_00329] */
            Fls_State.JobResult = MEMIF_JOB_PENDING;
            /* Erase start address is (FlsBaseAddress + FlashOffsetAddress). [SWS_Fls_00221] */
            Fls_State.JobAddress = Fls_FlashHwParas->FlashBaseAddress + FlashOffsetAddress;
            /* Erase size is the Length (from parameter). [SWS_Fls_00221] */
            Fls_State.JobLength = Length;
            /* Update current operating FLASH type */
            Fls_State.CurFlashType = Fls_CurFlashType;
            RetVal = E_OK;
            Fls_State.JobStarted.Erase = FALSE;
            /* If no error occur, set the state to FLS_JOB_ERASE */
            /* Set the FLS module status to MEMIF_BUSY. [SWS_Fls_00328] */
            /* Erase asynchronous request pending.
                * [SWS_Fls_00220], [SWS_Fls_00327] */
            Fls_State.JobType = FLS_JOB_ERASE;
            
            FLS_EXIT_CRITICAL_SECTION(Erase);
        }
        else
        {
            FLS_EXIT_CRITICAL_SECTION(Erase);
#if (FLS_DEV_ERROR_DETECT == STD_ON)
            /* Check that the FLS module is currently not busy. [SWS_Fls_00023] */
            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_ERASE, FLS_E_BUSY);
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
            RetVal = E_NOT_OK;
        }
    }

    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Fls_Write
*
*   Service ID              : 0x02.
*
*   Description             : This function write one or more complete flash pages.
*
*   Parameters in           : TargetAddress: target address
*                             SourceAddressPtr: pointer to source data buffer
*                             Length: number of bytes to write
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: write command has been accepted.
*                             E_NOT_OK: write command has not been accepted
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Fls_00251.
****************************************************************************************************/
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Write
(
    /* #Violation: Fls_c_REF_7 */
    Fls_AddressType TargetAddress,
    /* #Violation: Fls_c_REF_10*/
    P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) SourceAddressPtr,
    Fls_LengthType Length
)
{
    Std_ReturnType RetVal;
    Fls_AddressType FlashOffsetAddress;
    Fls_OptFlashType Fls_CurFlashType;
    const Fls_FlashHwParaType * Fls_FlashHwParas;
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;
#endif /* \(FLS_DEV_ERROR_DETECT == STD_ON) */

    /* Judge the type of current operating Flash */
    /* #Violation: Fls_c_REF_4 */
    Fls_CurFlashType = FLS_GET_FLASH_TYPE(TargetAddress);
    FlashOffsetAddress = Fls_InnerGetOffsetAddress(TargetAddress, Fls_CurFlashType);
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_CurFlashType);

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    RetVal = E_NOT_OK;
    /* Check that the FLS module has been initialized. [SWS_Fls_00066] */
    Error = Fls_CommonDetCheck(FLS_SID_WRITE, TargetAddress, Length);

    if (Error != FLS_NO_DET_ERROR)
    /* #Violation: Fls_c_REF_14 */
    {
        /* Do Noting */
    }
    /* Checking whether given FlashOffsetAddress is valid or not */
    else if (FlashOffsetAddress > (Fls_FlashHwParas->FlashSize - Fls_FlashHwParas->FlashPWordSize))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_PARAM_ADDRESS);
    }
    /* Check if aligned to Pword, where Pword must be at least a power of 2 */
    else if( (FlashOffsetAddress & (Fls_FlashHwParas->FlashPWordSize - 1U)) != 0U)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_PARAM_ADDRESS);
    }
    /* Checking whether given Length is valid or not. [SWS_Fls_00026] [SWS_Fls_00027] */
    else if ((0U == Length) || ((FlashOffsetAddress + Length) > Fls_FlashHwParas->FlashSize))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_PARAM_LENGTH);
    }
    /* Checking whether given Length is aligned. [SWS_Fls_00026] [SWS_Fls_00027] */
    else if ((Length & (Fls_FlashHwParas->FlashPWordSize - 1U)) != 0U)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_PARAM_LENGTH);
    }
    /* Check the given data buffer pointer for not being a null pointer. [SWS_Fls_00157] */
    else if (NULL_PTR == SourceAddressPtr)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_PARAM_DATA);
    }
    else
    {
        RetVal = E_OK;
    }

    if (E_OK == RetVal)
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        FLS_ENTER_CRITICAL_SECTION(Write);
        if (FLS_JOB_NONE == Fls_State.JobType)
        {
            /* Write one or more complete flash pages. [SWS_Fls_00223] */
            /* Copy the given parameters to Fls module internal variables. [SWS_Fls_00331] */
            /* Set the job result to MEMIF_JOB_PENDING. [SWS_Fls_00333] */
            Fls_State.JobResult = MEMIF_JOB_PENDING;
            /* Program a flash memory block with data
               provided via SourceAddressPtr. [SWS_Fls_00226] */
            /* Starting from FlsBaseAddress + FlashOffsetAddress of size Length. [SWS_Fls_00226] */
            Fls_State.JobAddress = Fls_FlashHwParas->FlashBaseAddress + FlashOffsetAddress;
            Fls_State.JobLength = Length;
            /* The FLS module shall not buffer data. [SWS_Fls_00002] */
            Fls_State.WriteBufferPtr = SourceAddressPtr;
            /* Update current operating FLASH type */
            Fls_State.CurFlashType = Fls_CurFlashType;
            /* After initiating the write job, return with E_OK. [SWS_Fls_00334] */
            RetVal = E_OK;
            Fls_State.JobStarted.Write = FALSE;
            /* If no error occur, set the state to FLS_JOB_WRITE */            
            /* Set the FLS module status to MEMIF_BUSY. [SWS_Fls_00332] */
            /* Suspend write operation, execute in Fls_MainFunction.
                * [SWS_Fls_00225], [SWS_Fls_00223] */
            Fls_State.JobType = FLS_JOB_WRITE;
        
            FLS_EXIT_CRITICAL_SECTION(Write);
        }
        else
        {
            FLS_EXIT_CRITICAL_SECTION(Write);
#if (FLS_DEV_ERROR_DETECT == STD_ON)
            /* Check that the FLS module is currently not busy. [SWS_Fls_00030] */
            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_WRITE, FLS_E_BUSY);
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
            RetVal = E_NOT_OK;
        }
    }

    return RetVal;
}

/* The function Fls_Compare shall be pre-compile time configurable On/Off. [SWS_Fls_00186] */
#if (FLS_COMPARE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_Compare
*
*   Service ID              : 0x08.
*
*   Description             : This function compares the contents of an area of flash memory.
*
*   Parameters in           : TargetAddressPtr: pointer to target data buffer
*                             SourceAddress: source address in flash memory
*                             Length: number of bytes
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non-Reentrant.
*
*   Return value            : E_OK: compare command has been accepted.
*                             E_NOT_OK: compare command has not been accepted
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Fls_00257.
****************************************************************************************************/
/* #Violation: Fls_c_REF_6 */
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Compare
(
    /* #Violation: Fls_c_REF_7*/
    Fls_AddressType SourceAddress,
    /* #Violation: Fls_c_REF_10*/
    P2CONST(uint8, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
    Fls_LengthType Length
)
{
    Std_ReturnType RetVal;
    Fls_AddressType FlashOffsetAddress;
    Fls_OptFlashType Fls_CurFlashType;

    const Fls_FlashHwParaType * Fls_FlashHwParas;
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;
#endif /* FLS_DEV_ERROR_DETECT \== STD_ON */

    /* #Violation: Fls_c_REF_4 */
    Fls_CurFlashType = FLS_GET_FLASH_TYPE(SourceAddress);
    FlashOffsetAddress = Fls_InnerGetOffsetAddress(SourceAddress, Fls_CurFlashType);
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_CurFlashType);

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    RetVal = E_NOT_OK;
    /* Check that the driver has been initialized. [SWS_Fls_00152] */
    Error = Fls_CommonDetCheck(FLS_SID_COMPARE, SourceAddress, Length);
    if (Error != FLS_NO_DET_ERROR)
    /* #Violation: Fls_c_REF_14 */
    {
        RetVal = E_NOT_OK;
    }
    /* Checking whether given SourceAddress is valid or not. [SWS_Fls_00150] */
    else if (FlashOffsetAddress >= Fls_FlashHwParas->FlashSize)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_PARAM_ADDRESS);
    }
    /* Check the given data buffer pointer for not being a null pointer. [SWS_Fls_00273] */
    else if (NULL_PTR == TargetAddressPtr)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_PARAM_DATA);
    }
    /* Checking whether given Length is valid or not. [SWS_Fls_00151] */
    else if ((0U == Length) || ((FlashOffsetAddress + Length) > Fls_FlashHwParas->FlashSize))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_PARAM_LENGTH);
    }
    else
    {
        RetVal = E_OK;
    }

    if(E_OK == RetVal)
#endif /* FLS_DEV_ERROR_DETECT \== STD_ON */
    {
        FLS_ENTER_CRITICAL_SECTION(Compare);
        /* Protection state machine read-modify-write will not be interrupted */
        if (FLS_JOB_NONE == Fls_State.JobType)
        {
            /* Set the FLS module status to MEMIF_BUSY. [SWS_Fls_00342] */
            Fls_State.JobType = FLS_JOB_COMPARE;
            /* Compare contents of flash memory with a application data buffer. [SWS_Fls_00241] */
            /* Copy the given parameters to Fls internal variables. [SWS_Fls_00341] */
            /* Set the job result to MEMIF_JOB_PENDING. [SWS_Fls_00343] */
            Fls_State.JobResult = MEMIF_JOB_PENDING;
            /* compare a continuous flash memory block starting
               from FlsBaseAddress + FlashOffsetAddress */
            /* of size Length with the buffer pointed to by TargetAddressPtr. [SWS_Fls_00244] */
            Fls_State.JobAddress = (uint32)(Fls_FlashHwParas->FlashBaseAddress +
                                            FlashOffsetAddress);
            /* The FLS module shall not buffer data. [SWS_Fls_00002] */
            /* When comparing execution, the data in CompareBufferPtr will not be modified,
               so it doesn't matter if targetAddressPtr loses the const property */
            Fls_State.CompareBufferPtr = TargetAddressPtr;
            Fls_State.JobLength = Length;
            /* Update current operating FLASH type */
            Fls_State.CurFlashType = Fls_CurFlashType;
            /* After initiating the compare job, Fls_Compare
               shall return with E_OK. [SWS_Fls_00344] */
            RetVal = E_OK;
            FLS_EXIT_CRITICAL_SECTION(Compare);
        }
        else
        {
            FLS_EXIT_CRITICAL_SECTION(Compare);
#if (FLS_DEV_ERROR_DETECT == STD_ON)
            /* Check that the driver is currently not busy. [SWS_Fls_00153] */
            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_COMPARE, FLS_E_BUSY);
#endif /* FLS_DEV_ERROR_DETECT \== STD_ON */
            RetVal = E_NOT_OK;
        }

    }

    return RetVal;
}
#endif /* FLS_COMPARE_API \== STD_ON */

/* Fls_Cancel shall be pre-compile time configurable On/Off. [SWS_Fls_00183] */
#if (FLS_CANCEL_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_Cancel
*
*   Service ID              : 0x03.
*
*   Description             : This function cancels an ongoing job.
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
*   AUTOSAR_Requirement     : SWS_Fls_00252.
****************************************************************************************************/
FUNC(void, FLS_PUBLIC_CODE) Fls_Cancel
(
    void
)
{
    boolean JobCanceled;

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;

    /* Check that the FLS module has been initialized. [SWS_Fls_00356] */
    Error = Fls_InitStatusDetCheck(FLS_SID_CANCEL);
    if (FLS_NO_DET_ERROR == Error)
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        FLS_ENTER_CRITICAL_SECTION(CancelProtection);
#if (FLS_USE_INTERRUPTS == STD_ON)
        /* Update the address needed clear status if FLS already in canceling mode */
        if (TRUE != Fls_State.JobCanceling)
        {
            Fls_CancelJobAddress = Fls_State.JobAddress;
        }
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
        /* Cancel an ongoing flash read, write, erase or compare job. [SWS_Fls_00229] */
        /* Abort a running job synchronously. [SWS_Fls_00230] */
        /* When using interrupt mode, the Fls_State.JobAddress will be cleared in interrupt
           callback function(named: Fls_Flash_ISRHandler) */
        if (FLS_JOB_WRITE == Fls_State.JobType)
        {
#if (FLS_USE_INTERRUPTS == STD_ON)
            if (Fls_State.JobStarted.Write == TRUE)
            {
                /* Set Cancel flag, Prevent interrupt logic exceptions */
                Fls_State.JobCanceling = TRUE;
            }
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
            /* Reset the FLS module's internal job processing variables. [SWS_Fls_00335] */
            Fls_State.JobStarted.Write = (boolean)FALSE;
            Fls_State.WriteBufferPtr = NULL_PTR;
            Fls_State.JobAddress = 0U;
            Fls_State.JobLength = 0U;
            JobCanceled = (boolean)TRUE;
        }
        else if (FLS_JOB_ERASE == Fls_State.JobType)
        {
#if (FLS_USE_INTERRUPTS == STD_ON)
            if (Fls_State.JobStarted.Erase == TRUE)
            {
                /* Set Cancel flag, Prevent interrupt logic exceptions */
                Fls_State.JobCanceling = TRUE;
            }
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
            /* Reset the FLS module's internal job processing variables. [SWS_Fls_00335] */
            Fls_State.JobStarted.Erase = (boolean)FALSE;
            Fls_State.JobAddress = 0U;
            Fls_State.JobLength = 0U;
            JobCanceled = (boolean)TRUE;
        }
        else if (FLS_JOB_READ == Fls_State.JobType)
        {
            /* Reset the FLS module's internal job processing variables. [SWS_Fls_00335] */
            Fls_State.ReadBufferPtr = NULL_PTR;
            Fls_State.JobAddress = 0U;
            Fls_State.JobLength = 0U;
            JobCanceled = (boolean)TRUE;
        }
        else if (FLS_JOB_COMPARE == Fls_State.JobType)
        {
            /* Reset the FLS module's internel job processing variables. [SWS_Fls_00335] */
            Fls_State.CompareBufferPtr = NULL_PTR;
            Fls_State.JobAddress = 0U;
            Fls_State.JobLength = 0U;
            JobCanceled = (boolean)TRUE;
        }
        else if (FLS_JOB_BLANKCHECK == Fls_State.JobType)
        {
            /* Reset the FLS module's internal job processing variables. [SWS_Fls_00335] */
            Fls_State.JobAddress = 0U;
            Fls_State.JobLength = 0U;
            JobCanceled = (boolean)TRUE;
        }
        else
        {
            JobCanceled = (boolean)FALSE;
        }
        /* Set the FLS module state to MEMIF_IDLE. [SWS_Fls_00336] */
        Fls_State.JobType = FLS_JOB_NONE;

        /* Set job result to MEMIF_JOB_CANCELED if the currently value is MEMIF_JOB_PENDING. */
        /* Otherwise Fls_Cancel shall leave the job result unchanged. [SWS_Fls_00033] */
        if (MEMIF_JOB_PENDING == Fls_State.JobResult)
        {
            Fls_State.JobResult = MEMIF_JOB_CANCELED;
        }
        FLS_EXIT_CRITICAL_SECTION(CancelProtection);

        /* If configured, Fls_Cancel shall call the error notification. [SWS_Fls_00147] */
        if (((boolean)TRUE == JobCanceled) &&
            (Fls_ConfigPtr->FlsJobErrorNotificationPtr != NULL_PTR))
        {
            Fls_ConfigPtr->FlsJobErrorNotificationPtr();
        }
    }
}
#endif /* (FLS_CANCEL_API  \== STD_ON) */

/* The function Fls_SetMode shall be pre-compile time configurable On/Off. [SWS_Fls_00187] */
#if (FLS_SET_MODE_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_SetMode
*
*   Service ID              : 0x09.
*
*   Description             : This function sets the flash driver's operation mode.
*
*   Parameters in           : Mode: slow read mode or fast read mode
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
*   AUTOSAR_Requirement     : SWS_Fls_00258.
****************************************************************************************************/
FUNC(void, FLS_PUBLIC_CODE) Fls_SetMode
(
    MemIf_ModeType Mode
)
{
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;

    Error = Fls_InitStatusDetCheck(FLS_SID_SETMODE);
    if (Error != FLS_NO_DET_ERROR)
    /* #Violation: Fls_c_REF_14 */
    {
        /* Do Nothing */
    }
    /* Check that the FLS module is currently not busy. [SWS_Fls_00156]*/
    else if (Fls_State.JobType != FLS_JOB_NONE)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_SETMODE, FLS_E_BUSY);
    }
    else
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Set the FLS module's operation mode to the given "Mode" parameter. [SWS_Fls_00155] */
        Fls_State.Mode = Mode;
    }
}
#endif /* (FLS_SET_MODE_API  \== STD_ON) */

/****************************************************************************************************
*   Function Name           : Fls_MainFunction
*
*   Service ID              : 0x06.
*
*   Description             : Handle read, write, erase, compare, and whitespace check job
*                             operations for requests.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Fls_00255.
****************************************************************************************************/
/* #Violation: Fls_c_REF_6 */
FUNC(void, FLS_PUBLIC_CODE) Fls_MainFunction
(
    void
)
{
    boolean HWBusy;
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    Mcal_CoreType CoreId;

    /* #Violation: Fls_c_REF_4 */
    CoreId = Mcal_GetCoreId();
    if (FLS_CORE_ALLOCATION != (uint8)CoreId)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_MAIN,
                                  FLS_E_CORE_NOT_CONFIGURED);
    }
    else
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* Process jobs without hardware interrupt support (e.g. read jobs). [SWS_Fls_00235] */
        if (Fls_State.JobType != FLS_JOB_NONE)
        {
            /* The flash driver's main function shall check that the hardware is
               indeed free before starting a new job */
            HWBusy = Fls_InnerCheckFlashBusy(Fls_State.JobAddress);
            if (HWBusy != (boolean)TRUE)
            {
    /* Perform processing of the flash read, write, erase and compare jobs. [SWS_Fls_00037] */
    /* FLS shall offer asynchronous services. [SWS_Fls_00001] */
    /* Fee main processing routine shall execute flash access code routines. [SWS_Fls_00212] */
    /* Read/write flash memory cannot usually be done simultaneously. [SWS_Fls_00269] */
                if (FLS_JOB_ERASE == Fls_State.JobType)
                {
                    (void)Fls_MainEraseHandler();
                }
                else if (FLS_JOB_WRITE == Fls_State.JobType)
                {
                    (void)Fls_MainWriteHandler();
                }
                else if (FLS_JOB_READ == Fls_State.JobType)
                {
                    Fls_MainReadHandler();
                }
                else if (FLS_JOB_COMPARE == Fls_State.JobType)
                {
                    Fls_MainCompareHandler();
                }
#if (FLS_BLANK_CHECK_API == STD_ON)
                else if (FLS_JOB_BLANKCHECK == Fls_State.JobType)
                {
                    Fls_MainCheckHandler();
                }
#endif /* (FLS_BLANK_CHECK_API  \== STD_ON) */
                else
                /* #Violation: Fls_c_REF_14 */
                {
                    /* Do Nothing */
                }
            }
#if (FLS_TIMEOUT_SUPERVISION_ENABLED == STD_ON)
            else
            {
                Fls_TimeOutDet(FLS_SID_MAIN);
            }
#endif /* (FLS_TIMEOUT_SUPERVISION_ENABLED  \== STD_ON) */
        }
#if (FLS_USE_INTERRUPTS == STD_ON)
        else 
        {
            /* Fls_Cancel is called before Fls_Mainfunction, the Canceling state should set to 
             * FALSE */
            if (Fls_State.JobCanceling == TRUE)
            {
                Fls_State.JobCanceling = FALSE;
            }
        }
#endif /* (FLS_USE_INTERRUPTS  \== STD_ON) */
        /* Return without any action if no job is pending. [SWS_Fls_00039] */
    }
}

/****************************************************************************************************
*   Function Name           : Fls_Read
*
*   Service ID              : 0x07.
*
*   Description             : This function reads from flash memory.
*
*   Parameters in           : SourceAddress: source address in flash memory
*                             Length: number of bytes
*
*   Parameters inout        : None.
*
*   Parameters out          : TargetAddressPtr: Pointer to target data buffer.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: read command has been accepted.
*                             E_NOT_OK: read command has not been accepted .
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Fls_00256.
****************************************************************************************************/
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_Read
(
    /* #Violation: Fls_c_REF_7 */
    Fls_AddressType SourceAddress,
    /* #Violation: Fls_c_REF_8 */
    /* #Violation: Fls_c_REF_10*/
    P2VAR(uint8, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
    Fls_LengthType Length
)
{
    Std_ReturnType RetVal;
    Fls_AddressType FlashOffsetAddress;
    const Fls_FlashHwParaType * Fls_FlashHwParas;
    Fls_OptFlashType Fls_CurFlashType;
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */

    /* #Violation: Fls_c_REF_4 */
    Fls_CurFlashType = FLS_GET_FLASH_TYPE(SourceAddress);
    FlashOffsetAddress = Fls_InnerGetOffsetAddress(SourceAddress, Fls_CurFlashType);
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_CurFlashType);

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    RetVal = E_NOT_OK;
    /* Check that the driver has been initialized. [SWS_Fls_00099] */
    Error = Fls_CommonDetCheck(FLS_SID_READ, SourceAddress, Length);
    if (Error != FLS_NO_DET_ERROR)
    /* #Violation: Fls_c_REF_14 */
    {
        /* Fls_Read can be called after FLS has been initialized. [SWS_Fls_00240] */
        /* Do Nothing */
    }
    /* Check the given data buffer pointer for not being a null pointer. [SWS_Fls_00158] */
    else if (NULL_PTR == TargetAddressPtr)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_PARAM_DATA);
    }
    /* Checking whether given Length is valid or not. [SWS_Fls_00098] */
    else if ((0U == Length) || ((FlashOffsetAddress + Length) > Fls_FlashHwParas->FlashSize))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_PARAM_LENGTH);
    }
    else
    {
        RetVal = E_OK;
    }

    if(E_OK == RetVal)
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        FLS_ENTER_CRITICAL_SECTION(Read);
        /* Protection state machine read-modify-write will not be interrupted */
        if (FLS_JOB_NONE == Fls_State.JobType)
        {
            /* Set the FLS module status to MEMIF_BUSY. [SWS_Fls_00338] */
            /* Read asynchronous request pending. [SWS_Fls_00238], [SWS_Fls_00337] */
            Fls_State.JobType = FLS_JOB_READ;
            /* Read from flash memory. [SWS_Fls_00236] */
            /* Copy the given parameters to FLS internal variables. [SWS_Fls_00337] */
            /* Set the FLS module job result to MEMIF_JOB_PENDING. [SWS_Fls_00339] */
            Fls_State.JobResult = MEMIF_JOB_PENDING;
            /* Copy a continuous flash memory block starting from FlsBaseAddress + FlashOffsetAddress */
            /* of size Length to the buffer pointed to by TargetAddressPtr. [SWS_Fls_00239] */
            Fls_State.JobAddress = Fls_FlashHwParas->FlashBaseAddress + FlashOffsetAddress;
            /* The FLS module shall not buffer data. [SWS_Fls_00002] */
            Fls_State.ReadBufferPtr = TargetAddressPtr;
            Fls_State.JobLength = Length;
            /* Update current operating FLASH type */
            Fls_State.CurFlashType = Fls_CurFlashType;
            /* After initiating a read job, Fls_Read shall return with E_OK. [SWS_Fls_00340] */
            RetVal = E_OK;
            FLS_EXIT_CRITICAL_SECTION(Read);
        }
        else
        {
            FLS_EXIT_CRITICAL_SECTION(Read);
#if (FLS_DEV_ERROR_DETECT == STD_ON)
            /* Check that the driver is currently not busy. [SWS_Fls_00100] */
            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READ, FLS_E_BUSY);
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
            RetVal = E_NOT_OK;
        }

    }

    return RetVal;
}

#if (FLS_BLANK_CHECK_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_BlankCheck
*
*   Service ID              : 0x0a.
*
*   Description             : The function shall verify, whether a given memory area has been erased
*                             but not (yet) programmed.
*
*   Parameters in           : TargetAddress: Address in flash memory from which the blank check
*                             should be started.
*                             Length: Number of bytes to be checked for erase pattern.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Asynchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : E_OK: command has been accepted.
*                             E_NOT_OK: command has not been accepted .
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Fls_00371.
****************************************************************************************************/
/* #Violation: Fls_c_REF_6 */
FUNC(Std_ReturnType, FLS_PUBLIC_CODE) Fls_BlankCheck
(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
)
{
    Std_ReturnType RetVal;
    Fls_AddressType FlashOffsetAddress;
    const Fls_FlashHwParaType * Fls_FlashHwParas;
    Fls_OptFlashType Fls_CurFlashType;
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */

    /* #Violation: Fls_c_REF_4 */
    Fls_CurFlashType = FLS_GET_FLASH_TYPE(TargetAddress);
    FlashOffsetAddress = Fls_InnerGetOffsetAddress(TargetAddress, Fls_CurFlashType);
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_CurFlashType);
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    RetVal = E_NOT_OK;
    /* Check that the driver has been initialized. [SWS_Fls_00382] */
    Error = Fls_CommonDetCheck(FLS_SID_BLANKCHECK, TargetAddress, Length);
    if (Error != FLS_NO_DET_ERROR)
    /* #Violation: Fls_c_REF_14 */
    {
        /* Do Nothing */
    }
    /* Checking whether given TargetAddress is valid or not. [SWS_Fls_00380] */
    else if (FlashOffsetAddress >= Fls_FlashHwParas->FlashSize)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANKCHECK,
                              FLS_E_PARAM_ADDRESS);
    }
    /* Checking whether given Length is valid or not. [SWS_Fls_00381] */
    else if ((0U == Length) || ((FlashOffsetAddress + Length) > Fls_FlashHwParas->FlashSize))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANKCHECK,
                              FLS_E_PARAM_LENGTH);
    }
    else
    {
        RetVal = E_OK;
    }

    if (E_OK == RetVal)
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        FLS_ENTER_CRITICAL_SECTION(BlankCheck);
        /* Protection state machine read-modify-write will not be interrupted */
        if (FLS_JOB_NONE == Fls_State.JobType)
        {
            /* Set the FLS module status to MEMIF_BUSY. [SWS_Fls_00375] */
            /* BlankCheck asynchronous request pending. [SWS_Fls_00374], [SWS_Fls_00378] */
            Fls_State.JobType = FLS_JOB_BLANKCHECK;
            /* Verify, whether memory area has been erased but
               not (yet) re-programmed. [SWS_Fls_00373]*/
            /* Copy the given parameters to FLS module internal variables. [SWS_Fls_00374] */
            /* Set the FLS module job result to MEMIF_JOB_PENDING. [SWS_Fls_00376] */
            Fls_State.JobResult = MEMIF_JOB_PENDING;
            Fls_State.JobLength = Length;
            /* Flash check area start from FlsBaseAddress + FlashOffsetAddress
               of size Length [SWS_Fls_00379] */
            Fls_State.JobAddress = Fls_FlashHwParas->FlashBaseAddress + FlashOffsetAddress;
            /* Update current operating FLASH type */
            Fls_State.CurFlashType = Fls_CurFlashType;
            /* After initiating verification job, shall return with E_OK. [SWS_Fls_00377] */
            RetVal = E_OK;
            FLS_EXIT_CRITICAL_SECTION(BlankCheck);
        }
        else
        {
            FLS_EXIT_CRITICAL_SECTION(BlankCheck);
#if (FLS_DEV_ERROR_DETECT == STD_ON)
            /* Check that the driver is currently not busy. [SWS_Fls_00383] */
            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANKCHECK, FLS_E_BUSY);
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
            RetVal = E_NOT_OK;
        }
    }

    return RetVal;
}
#endif /* (FLS_BLANK_CHECK_API  \== STD_ON) */

/* Fls_GetStatus shall be pre-compile time configurable On/Off. [SWS_Fls_00184] */
#if (FLS_GET_STATUS_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_GetStatus
*
*   Service ID              : 0x04.
*
*   Description             : This function returns the driver state.
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
*   Return value            : MemIf_StatusType: status.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Fls_00253.
****************************************************************************************************/
/* #Violation: Fls_c_REF_6 */
FUNC(MemIf_StatusType, FLS_PUBLIC_CODE) Fls_GetStatus
(
    void
)
{
    MemIf_StatusType RetVal;
    Fls_JobType FlsCurJobType;

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    Mcal_CoreType CoreId;

    RetVal = MEMIF_UNINIT;
    /* Get core id which is executing currently */
    /* #Violation: Fls_c_REF_4 */
    CoreId = Mcal_GetCoreId();
    if (FLS_CORE_ALLOCATION != (uint8)CoreId)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_GETSTATUS,
                              FLS_E_CORE_NOT_CONFIGURED);
    }
    else
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* If not DET, get current JobType */
        FlsCurJobType = Fls_State.JobType;

        if (FLS_JOB_UNINIT == FlsCurJobType)
        {
            RetVal = MEMIF_UNINIT;
        }
        else if (FLS_JOB_NONE != FlsCurJobType)
        {
            RetVal = MEMIF_BUSY;
        }
        else
        {
            RetVal = MEMIF_IDLE;
        }
        /* \[SWS_Fls_00034] Service shall return driver state synchronously. */
    }

    /* Return the FLS module state synchronously. [SWS_Fls_00034] */
    return RetVal;
}
#endif /* (FLS_GET_STATUS_API  \== STD_ON) */

/* Fls_GetJobResult shall be pre-compile time configurable On/Off. [SWS_Fls_00185] */
#if (FLS_GET_JOB_RESULT_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_GetJobResult
*
*   Service ID              : 0x05.
*
*   Description             : This function returns the result of the last job.
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
*   Return value            : job result.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Fls_00254.
****************************************************************************************************/
/* #Violation: Fls_c_REF_6 */
FUNC(MemIf_JobResultType, FLS_PUBLIC_CODE) Fls_GetJobResult
(
    void
)
{
    MemIf_JobResultType RetVal;

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;

    /* Check that the FLS module has been initialized. [SWS_Fls_00358] */
    Error = Fls_InitStatusDetCheck(FLS_SID_GETJOBRESULT);
    if (Error != FLS_NO_DET_ERROR)
    {
        /* If this check fails, return with MEMIF_JOB_FAILED. [SWS_Fls_00358] */
        RetVal = MEMIF_JOB_FAILED;
    }
    else
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        /* The erase, write, read and compare shall share same job result. Overwrite job result */
        /* with MEMIF_JOB_PENDING if FLS has accepted a new job. [SWS_Fls_00036]*/
        RetVal = Fls_State.JobResult;
    }

    /* Return the result of the last job synchronously. [SWS_Fls_00035] */
    return RetVal;
}
#endif /*FLS_GET_JOB_RESULT_API \== STD_ON */

/****************************************************************************************************
*   Function Name           : Fls_ReadWordsSync
*
*   Service ID              : 0x12.
*
*   Description             : This function reads the flash synchronously.
*
*   Parameters in           : SourceAddress: source address in flash memory.
*                             Length: number of words.
*
*   Parameters inout        : None.
*
*   Parameters out          : TargetAddressPtr: Pointer to target data buffer.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : FLS_READ_SUCCESS:          Read successful.
*                             FLS_READ_BUSY:             FLS is busy.
*                             FLS_READ_ECC:              Uncorrectable ECC error occurred.
*                             FLS_READ_PARAM_ERR:        DET error occurred.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(uint8, FLS_PUBLIC_CODE) Fls_ReadWordsSync
(
    Fls_AddressType SourceAddress,
    /* #Violation: Fls_c_REF_8 */
    CONSTP2VAR(uint32, AUTOMATIC, FLS_APPL_DATA) TargetAddressPtr,
    Fls_LengthType Length
)
{
    uint32 const * SrcPtr;
    uint8 RetVal;
    boolean EccErrorFlag;
    uint32 * ReadTargetPtr;
    Fls_LengthType RestLength;
    Fls_AddressType FlashOffsetAddress;
    Fls_AddressType FlashPhySourceAddress;
    const Fls_FlashHwParaType * Fls_FlashHwParas;
    Fls_OptFlashType Fls_CurFlashType;
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    boolean OperationRslt;

    OperationRslt = TRUE;
    /* #Violation: Fls_c_REF_4 */
    Fls_CurFlashType = FLS_GET_FLASH_TYPE(SourceAddress);
    FlashOffsetAddress = Fls_InnerGetOffsetAddress(SourceAddress, Fls_CurFlashType);
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_CurFlashType);

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    RetVal = FLS_READ_PARAM_ERR;
    /* Check that the driver has been initialized. */
    Error = Fls_CommonDetCheck(FLS_SID_READSYNC, SourceAddress, Length);
    if (Error != FLS_NO_DET_ERROR)
    /* #Violation: Fls_c_REF_14 */
    {
        /* Fls_Read can be called after FLS has been initialized. */
        /* Do Nothing */
    }
    /* Checking whether given SourceAddress is valid or not. */
    /* The read address must be 4-byte aligned. */
    else if ((FlashOffsetAddress >= Fls_FlashHwParas->FlashSize) || ((FlashOffsetAddress & FLS_WORD_SIZE_MASK) != 0U))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READSYNC, FLS_E_PARAM_ADDRESS);
    }
    /* Check the given data buffer pointer for not being a null pointer. */
    else if (NULL_PTR == TargetAddressPtr)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READSYNC, FLS_E_PARAM_DATA);
    }
    /* Checking whether given Length is valid or not. */
    else if ((0U == Length) || ((FlashOffsetAddress + Length) > Fls_FlashHwParas->FlashSize))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_READSYNC, FLS_E_PARAM_LENGTH);
    }
    else
    {
        RetVal = E_OK;
    }

    if(E_OK == RetVal)
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        FLS_ENTER_CRITICAL_SECTION(ReadWordsSync);
        /* Protection state machine read-modify-write will not be interrupted */
        if (FLS_JOB_NONE == Fls_State.JobType)
        {
            Fls_State.JobType = FLS_JOB_READSYNC;
            Fls_State.CurFlashType = Fls_CurFlashType;
            FLS_EXIT_CRITICAL_SECTION(ReadWordsSync);
            FlashPhySourceAddress = Fls_FlashHwParas->FlashBaseAddress + FlashOffsetAddress;
            /* #Violation: Fls_c_REF_12 */
            /* #Violation: Fls_c_REF_17 */
            /* #Violation: Fls_c_REF_15 */
            SrcPtr = (uint32 *)(FlashPhySourceAddress);
            ReadTargetPtr = TargetAddressPtr;
            RestLength    = Length;
            /* Read the data */
            do
            {
                *ReadTargetPtr = *SrcPtr;
                ReadTargetPtr++;
                SrcPtr++;
                RestLength--;
            } while (RestLength > 0U);
            EccErrorFlag = Fls_InnerGetFlashEccStatus(FlashPhySourceAddress);
            if (TRUE == EccErrorFlag)
            {
                FLS_ENTER_CRITICAL_SECTION(ReadWordsSync);
                /* Clear ECC error flag */
                OperationRslt = Fls_InnerClearFlashEccStatus(FlashPhySourceAddress);
                FLS_EXIT_CRITICAL_SECTION(ReadWordsSync);
                /* double ECC error occurred */
                RetVal = FLS_READ_ECC;
            }
            else
            {
                RetVal = FLS_READ_SUCCESS;
            }
            Fls_State.JobType = FLS_JOB_NONE;
        }
        else
        {
            FLS_EXIT_CRITICAL_SECTION(ReadWordsSync);
            RetVal = FLS_READ_BUSY;
        }
    }
#if (FLS_SAFETY_ENABLE == STD_ON)
    if (OperationRslt == FALSE)
    {
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                     FLS_SID_READSYNC, FLS_E_REG_CHECK_FAILED);
    }
#else /* (FLS_SAFETY_ENABLE \== STD_ON) */
    FLS_UNUNSED_VAR(OperationRslt);
#endif /* (FLS_SAFETY_ENABLE \== STD_ON) */
    return RetVal;
}

/****************************************************************************************************
*   Function Name           : Fls_CompareWordsSync
*
*   Service ID              : 0x13.
*
*   Description             : This function compares the flash synchronously.
*
*   Parameters in           : SourceAddress: source address in flash memory.
*                             TargetAddressPtr: Pointer to target data buffer.
*                             Length: number of words.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : FLS_COMPARE_EQUAL:        The data being compared is equal.
*                             FLS_COMPARE_NOT_EQUAL:    The data being compared is not equal.
*                             FLS_COMPARE_BUSY:         FLS is busy.
*                             FLS_COMPARE_ECC:          Uncorrectable ECC error occurred.
*                             FLS_COMPARE_PARAM_ERR:    DET error occurred.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
/* #Violation: Fls_c_REF_6 */
FUNC(uint8, FLS_PUBLIC_CODE) Fls_CompareWordsSync
(
    Fls_AddressType SourceAddress,
    CONSTP2CONST(uint32, AUTOMATIC, FLS_APPL_CONST) TargetAddressPtr,
    Fls_LengthType Length
)
{
    const uint32 * SrcPtr;
    uint8 RetVal;
    boolean EccErrorFlag;
    Fls_LengthType RestLength;
    const uint32 * CompareTargetAddressPtr;
    Fls_AddressType FlashOffsetAddress;
    Fls_AddressType FlashPhySourceAddress;
    Fls_OptFlashType Fls_CurFlashType;
    const Fls_FlashHwParaType * Fls_FlashHwParas;
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    boolean OperationRslt;

    OperationRslt = TRUE;
    /* #Violation: Fls_c_REF_4 */
    Fls_CurFlashType = FLS_GET_FLASH_TYPE(SourceAddress);
    FlashOffsetAddress = Fls_InnerGetOffsetAddress(SourceAddress, Fls_CurFlashType);
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_CurFlashType);

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    /* Check that the driver has been initialized. */
    Error = Fls_CommonDetCheck(FLS_SID_COMPARESYNC, SourceAddress, Length);
    RetVal = Fls_CompareWordsSyncDetCheck(Error, SourceAddress, TargetAddressPtr, Length);

    if(E_OK == RetVal)
#endif /* FLS_DEV_ERROR_DETECT \== STD_ON */
    {
        FLS_ENTER_CRITICAL_SECTION(CompareWordsSync);
        /* Protection state machine read-modify-write will not be interrupted */
        /* Check if no operation ongoing */
        if (FLS_JOB_NONE == Fls_State.JobType)
        {
            Fls_State.JobType = FLS_JOB_COMPARESYNC;
            Fls_State.CurFlashType = Fls_CurFlashType;
            FLS_EXIT_CRITICAL_SECTION(CompareWordsSync);
            FlashPhySourceAddress = Fls_FlashHwParas->FlashBaseAddress + FlashOffsetAddress;
            /* #Violation: Fls_c_REF_17 */
            /* #Violation: Fls_c_REF_12*/
            SrcPtr = (uint32 *)(FlashPhySourceAddress);
            RetVal = FLS_COMPARE_EQUAL;
            RestLength = Length;
            CompareTargetAddressPtr = TargetAddressPtr;
            do
            {
                if ((CompareTargetAddressPtr[0]) != SrcPtr[0])
                {
                    RetVal = FLS_COMPARE_NOT_EQUAL;
                    RestLength = 0U;
                }
                else
                {
                    CompareTargetAddressPtr++;
                    SrcPtr++;
                    RestLength--;
                }
            } while (RestLength > 0U);
            EccErrorFlag = Fls_InnerGetFlashEccStatus(FlashPhySourceAddress);
            if (TRUE == EccErrorFlag)
            {
                FLS_ENTER_CRITICAL_SECTION(CompareWordsSync);
                /* Clear ECC error flag */
                OperationRslt = Fls_InnerClearFlashEccStatus(FlashPhySourceAddress);
                FLS_EXIT_CRITICAL_SECTION(CompareWordsSync);
                /* double ECC error occurred */
                RetVal = FLS_COMPARE_ECC;
            }
            Fls_State.JobType = FLS_JOB_NONE;
        }
        else
        {
            FLS_EXIT_CRITICAL_SECTION(CompareWordsSync);
            RetVal = FLS_COMPARE_BUSY;
        }
    }

#if (FLS_SAFETY_ENABLE == STD_ON)
    if (OperationRslt == FALSE)
    {
        (void)Det_ReportRuntimeError(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                     FLS_SID_COMPARESYNC, FLS_E_REG_CHECK_FAILED);
    }
#else /* (FLS_SAFETY_ENABLE \== STD_ON) */
    FLS_UNUNSED_VAR(OperationRslt);
#endif /* (FLS_SAFETY_ENABLE \== STD_ON) */

    return RetVal;
}


/****************************************************************************************************
*   Function Name           : Fls_BlankCheckSync
*
*   Service ID              : 0x14.
*
*   Description             : This function checks whether the flash has been erased or not.
*
*   Parameters in           : TargetAddress: Address in flash memory from which the blank check
*                             should be started.
*                             Length: Number of bytes to be checked for erase pattern.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : FLS_BLANKCHECK_EMPTY:         Empty.
*                             FLS_BLANKCHECK_DIRTY:         Dirty.
*                             FLS_BLANKCHECK_OVERTIME:      Blank check overtime.
*                             FLS_BLANKCHECK_BUSY:          FLS is busy.
*                             FLS_BLANKCHECK_PARAM_ERR:     DET error occurred.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(uint8, FLS_PUBLIC_CODE) Fls_BlankCheckSync
(
    Fls_AddressType TargetAddress,
    Fls_LengthType Length
)
{
    Fls_AddressType JobAddress;
    Fls_FlashResultStatus DriverResult;
    uint8 RetVal;
    Fls_AddressType FlashOffsetAddress;
    const Fls_FlashHwParaType * Fls_FlashHwParas;
    Fls_OptFlashType Fls_CurFlashType;
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    uint8 Error;
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */

    /* #Violation: Fls_c_REF_4 */
    Fls_CurFlashType = FLS_GET_FLASH_TYPE(TargetAddress);
    FlashOffsetAddress = Fls_InnerGetOffsetAddress(TargetAddress, Fls_CurFlashType);
    /* #Violation: Fls_c_REF_4 */
    Fls_FlashHwParas = FLS_GET_FLASH_HW_INFO_PTR(Fls_CurFlashType);

#if (FLS_DEV_ERROR_DETECT == STD_ON)
    RetVal = FLS_BLANKCHECK_PARAM_ERR;
    /* Check that the driver has been initialized. */
    Error = Fls_CommonDetCheck(FLS_SID_BLANKCHECKSYNC, TargetAddress, Length);

    if (Error != FLS_NO_DET_ERROR)
    /* #Violation: Fls_c_REF_14 */
    {
        /* Do Nothing */
    }
    /* Checking whether given FlashOffsetAddress is valid or not. */
    else if (FlashOffsetAddress >= Fls_FlashHwParas->FlashSize)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANKCHECKSYNC,
                              FLS_E_PARAM_ADDRESS);
    }
    /* Checking whether given Length is valid or not. */
    else if ((0U == Length) || ((FlashOffsetAddress + Length) > Fls_FlashHwParas->FlashSize))
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANKCHECKSYNC,
                              FLS_E_PARAM_LENGTH);
    }
    /* Check if the address is page aligned. */
    else if ((FlashOffsetAddress & (Fls_FlashHwParas->FlashPWordSize - 1U)) != 0U)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANKCHECKSYNC,
                              FLS_E_PARAM_ADDRESS);
    }
    /* Check if the length is page aligned. */
    else if ((Length & (Fls_FlashHwParas->FlashPWordSize - 1U)) != 0U)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_BLANKCHECKSYNC,
                              FLS_E_PARAM_LENGTH);
    }
    else
    {
        RetVal = E_OK;
    }

    if (E_OK == RetVal)
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        FLS_ENTER_CRITICAL_SECTION(BlankCheckSync);
        /* Protection state machine read-modify-write will not be interrupted */
        /* Check if no operation ongoing */
        if (FLS_JOB_NONE == Fls_State.JobType)
        {
            Fls_State.JobType = FLS_JOB_BLANKCHECKSYNC;
            Fls_State.CurFlashType = Fls_CurFlashType;
            FLS_EXIT_CRITICAL_SECTION(BlankCheckSync);
            JobAddress = Fls_FlashHwParas->FlashBaseAddress + FlashOffsetAddress;;
            DriverResult = Fls_InnerCheckFlashBlankSync(JobAddress, Length);
            if (FLS_HW_RESULT_OK == DriverResult)
            {
                RetVal = FLS_BLANKCHECK_EMPTY;
            }
            else if (FLS_HW_RESULT_FAILED == DriverResult)
            {
                RetVal = FLS_BLANKCHECK_DIRTY;
            }
            else
            {
                RetVal = FLS_BLANKCHECK_OVERTIME;
            }
            Fls_State.JobType = FLS_JOB_NONE;
        }
        else
        {
            FLS_EXIT_CRITICAL_SECTION(BlankCheckSync);
            /* flash is busy */
            RetVal = FLS_BLANKCHECK_BUSY;
        }
    }

    return RetVal;
}

#if (FLS_VERSION_INFO_API == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_GetVersionInfo
*
*   Service ID              : 0x16.
*
*   Description             : This function returns the version information of this module.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : VersioninfoPtr: Pointer to store the version information
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : SWS_Fls_00259.
****************************************************************************************************/
/* #Violation: Fls_c_REF_6 */
FUNC(void, FLS_PUBLIC_CODE) Fls_GetVersionInfo
(
    /* #Violation: Fls_c_REF_7 */
    /* #Violation: Fls_c_REF_8 */
    /* #Violation: Fls_c_REF_10*/
    P2VAR(Std_VersionInfoType, AUTOMATIC, FLS_APPL_DATA) VersionInfoPtr
)
{
#if (FLS_DEV_ERROR_DETECT == STD_ON)
    /* The argument is a NULL pointer and return without any action. [SWS_Fls_00363] */
    if (NULL_PTR == VersionInfoPtr)
    {
        (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_GETVERSIONINFO,
                              FLS_E_PARAM_POINTER);
    }
    else
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
    {
        VersionInfoPtr->moduleID = FLS_MODULE_ID;
        VersionInfoPtr->vendorID = (uint16)FLS_VENDOR_ID;
        VersionInfoPtr->sw_major_version = (uint8)FLS_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version = (uint8)FLS_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version = (uint8)FLS_SW_PATCH_VERSION;
    }
}
#endif /* (FLS_VERSION_INFO_API  \== STD_ON) */

/* The configuration parameter FlsUseInterrupts shall switch between interrupt and polling */
/* controlled job processing if this is supported by the flash memory hardware. [SWS_Fls_00232] */
#if (FLS_USE_INTERRUPTS == STD_ON)
/****************************************************************************************************
*   Function Name           : Fls_DFlash_ISRHandler
*
*   Service ID              : None.
*
*   Description             : This function is DFlash interrupt handler.
*
*   Parameters in           : None.
*
*   Parameters inout        : None.
*
*   Parameters out          : None.
*
*   Sync/Async              : Synchronous.
*
*   Reentrancy              : Non Reentrant.
*
*   Return value            : None.
*
*   Preconditions           : None.
*
*   AUTOSAR_Requirement     : None.
****************************************************************************************************/
FUNC(void, FLS_PUBLIC_CODE) Fls_Flash_ISRHandler
(
    void
)
{
    uint8 OperationError;
    uint32 ErrorStatus;
    /* The interrupt service routine shall reset the interrupt flag, check for errors reported by */
    /* underlying hardware, reload hardware finite state machine for the next round of pending job*/
    /* or call appropriate notification routine if job is finished or aborted. [SWS_Fls_00234] */
    /* If the operation is cancelled, there is no problem with this interrupt triggering. */
    if (TRUE != Fls_State.JobCanceling)
    {
        /* Check for erase operation */
        if (FLS_JOB_ERASE == Fls_State.JobType)
        {
            /* Check hardware error flag */
            ErrorStatus = Fls_InnerGetAllFlashStatus(Fls_State.JobAddress );

            if ((ErrorStatus & FLS_STATUS_ERROR_MASK) == FLS_STATUS_NO_ERROR)
            {
                /* Erase will only have 2 states:
                * completion and verification error */
                OperationError = Fls_InnerCheckHwEraseStatus(Fls_State.JobAddress );
                if (FLS_HW_RESULT_OK == OperationError)
                {
                    /* check & continue  */
                    Fls_State.EraseFinish = TRUE;
                }
                else
                {
                    Fls_State.EraseFinish = FALSE;
                    /* When the flash erase function failed, Report FLS_E_ERASE_FAILED. [SWS_Fls_00315] */
                    (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                                FLS_SID_INTERRUPT, FLS_E_ERASE_FAILED);
                    Fls_ErrorHandler(FLS_JOB_ERASE, FLS_ERROR_TYPE_HW_FAIL);
                }
            }
            else
            {
                /* When the flash erase function failed, Report FLS_E_ERASE_FAILED. [SWS_Fls_00315] */
                (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID,
                                            FLS_SID_INTERRUPT, FLS_E_ERASE_FAILED);
                Fls_ErrorHandler(FLS_JOB_ERASE, FLS_ERROR_TYPE_HW_FAIL);
            }
        }
        /* Check for write operation */
        else if (FLS_JOB_WRITE == Fls_State.JobType)
        {
            /* Check hardware error flag */
            ErrorStatus = Fls_InnerGetAllFlashStatus(Fls_State.JobAddress );
            if ((ErrorStatus & FLS_STATUS_ERROR_MASK) == FLS_STATUS_NO_ERROR)
            {
                /* Write will only have 2 states:
                * completion, verification error */
                OperationError = Fls_InnerCheckHwWriteStatus(Fls_State.JobAddress );
                if (FLS_HW_RESULT_OK == OperationError)
                {
                    /* check & continue  */
                    Fls_State.WriteFinish = TRUE;
                }
                else
                {
                    Fls_State.WriteFinish = FALSE;
                    /* When the flash write function failed, Report FLS_E_WRITE_FAILED. [SWS_Fls_00316] */
                    (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INTERRUPT,
                                                   FLS_E_WRITE_FAILED);
                    Fls_ErrorHandler(FLS_JOB_WRITE, FLS_ERROR_TYPE_HW_FAIL);
                }
            }
            else
            {
                /* When the flash write function failed, Report FLS_E_WRITE_FAILED. [SWS_Fls_00316] */
                (void)Det_ReportTransientFault(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INTERRUPT,
                                               FLS_E_WRITE_FAILED);
                Fls_ErrorHandler(FLS_JOB_WRITE, FLS_ERROR_TYPE_HW_FAIL);
            }
        }
        else
        {
            /* If the operation is invalid, there is no problem with this interrupt triggering. */
#if (FLS_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(FLS_MODULE_ID, FLS_INSTANCE_ID, FLS_SID_INTERRUPT,
                                  FLS_E_INTC_TRIGGER_EXCEPTION);
#endif /* (FLS_DEV_ERROR_DETECT  \== STD_ON) */
            /* Clear hardware completion flag */
            Fls_InnerClearFlashAllStatus(Fls_State.JobAddress);
        }
    }
    else
    {
        /* Clear hardware completion flag */
        Fls_InnerClearFlashAllStatus(Fls_CancelJobAddress);
        /* Clear Cancel flag */
        Fls_State.JobCanceling = FALSE;
    }
}
#endif /* FLS_USE_INTERRUPTS \== STD_ON */
/* #Violation: Fls_c_REF_9 */
#define FLS_STOP_SEC_CODE_ASIL_D_GLOBAL
/* #Violation: Fls_c_REF_2 */
#include "Fls_MemMap.h"
/****************************************************************************************************
**                                           End of File                                           **
****************************************************************************************************/

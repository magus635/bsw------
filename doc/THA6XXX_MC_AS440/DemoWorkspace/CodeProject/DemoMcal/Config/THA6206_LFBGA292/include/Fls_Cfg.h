/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fls_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all configurations of FLS module
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
*#Fls_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers
*
*/

#ifndef FLS_CFG_H_
#define FLS_CFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
/* Imported types. [SWS_Fls_00248] */
#include "MemIf_Types.h"
#include "Mcall.h"
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
/* Autosar specification version */
#define FLS_CFG_AR_RELEASE_MAJOR_VERSION            (4U)
#define FLS_CFG_AR_RELEASE_MINOR_VERSION            (4U)
#define FLS_CFG_AR_RELEASE_REVISION_VERSION         (0U)


/* Vendor specific implementation version information */
#define FLS_CFG_SW_MAJOR_VERSION                    (1U)
#define FLS_CFG_SW_MINOR_VERSION                    (2U)
#define FLS_CFG_SW_PATCH_VERSION                    (0U)

#define FLS_CFG_VENDOR_ID                           (175U)
#define FLS_CFG_MODULE_ID                           (92U)

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
/* Config Constant */
#define FLS_INSTANCE_ID                 (0U)

/*
Configuration: FlsSafetyDetect
- if Selected, Safety Error Check is Enabled 
- if Deselected, Safety Error Check is Disabled 
*/
#define FLS_SAFETY_ENABLE                                  (STD_ON)

/*
Configuration: FlsDflashECCTriggerBusErrorMaskEnable
- if Selected, Mask bus error is triggered when ECC Error occurs
- if Deselected, Unmask bus error is not triggered when ECC Error occurs
*/
#define FLS_DF_ECC_TRIGGER_BUS_ERROR_MASK_ENABLE           (STD_ON)


/* Configuration of whether to use FLS to operate PFLASH or not */
#define FLS_PFLASH_USED                                    (STD_ON)

/* Information for Fls */
/* DFlash and PFlash base address */
#define FLS_DFLASH_BASE_ADDRESS         (0x94000000U)
#define FLS_PFLASH_BASE_ADDRESS         (0x90400000U)
/* DFlash and PFlash size */
#define FLS_DFLASH_TOTAL_SIZE           (0x00080000U)
#define FLS_PFLASH_TOTAL_SIZE           (0x00600000U)
/* DFlash and PFlash sector size */
#define FLS_DFLASH_SECTOR_SIZE          (0x00002000U)
#define FLS_PFLASH_SECTOR_SIZE          (0x00004000U)
/* DFlash and PFlash page size */
#define FLS_DFLASH_PAGE_SIZE            (0x00000010U)
#define FLS_PFLASH_PAGE_SIZE            (0x00000020U)
/* DFlash and PFlash row size */
#define FLS_DFLASH_ROW_SIZE             (0x00000200U)
#define FLS_PFLASH_ROW_SIZE             (0x00000400U)
/* DFlash and PFlash end address */
#define FLS_DFLASH_END_ADDRESS          (0x9407ffffU)
#define FLS_PFLASH_END_ADDRESS          (0x909fffffU)


/* Hardware Information (Base address). [SWS_Fls_00217] */
/* Page size of DFlash */
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_PAGE_SIZE                   FLS_DFLASH_PAGE_SIZE
/* Sector size of DFlash */
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_SECTOR_SIZE                 FLS_DFLASH_SECTOR_SIZE
/* DFLASH total size */
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_TOTAL_SIZE                  (0x80000U)

/* Maximum time to erase one complete flash sector in Microseconds. */
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_ERASE_SECTOR_TIMEOUT_US     (16000ULL)
/* Maximum time to program one complete flash page in Microseconds. */
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_WRITE_PAGE_TIMEOUT_US       (1500ULL)
/* The contents of an erased flash memory cell. */
#define FLS_ERASE_VALUE                 (0xffU)

/* Fls_cancel api selection enabled/disabled */
#define FLS_CANCEL_API                  (STD_ON)

/* Fls_SetMode api selection enabled/disabled */
#define FLS_SET_MODE_API                (STD_ON)

/* Fls_compare api selection enabled/disabled */
#define FLS_COMPARE_API                 (STD_ON)

/* Fls_GetJobResult api selection enabled/disabled */
#define FLS_GET_JOB_RESULT_API          (STD_ON)

/* Fls_GetStatus api selection enabled/disabled */
#define FLS_GET_STATUS_API              (STD_ON)

/* Fls_GetVersionInfo api selection enabled/disabled */
#define FLS_VERSION_INFO_API            (STD_ON)

/* Fls_BlankCheck api selection enabled/disabled */
#define FLS_BLANK_CHECK_API             (STD_ON)

/* Development error detection enabled/disabled */
#define FLS_DEV_ERROR_DETECT            (STD_ON)

/* Interrupt Use/Unused */
#define FLS_USE_INTERRUPTS              (STD_OFF)

/* Pre-processor switch to enable / disable the write verification. */
#define FLS_ERASE_VERIFICATION_ENABLED  (STD_ON)

/* Pre-processor switch to enable / disable the erase verification */
#define FLS_WRITE_VERIFICATION_ENABLED  (STD_ON)

/* Pre-processor switch to enable / disable the timeout supervision. */
#define FLS_TIMEOUT_SUPERVISION_ENABLED (STD_ON)


/* Fls module configuration count */
#define FLS_CONFIG_COUNT                (1U)

#define FLS_CORE_ALLOCATION             (0U)


/****************************************************************************************************
*                         Callback Function Declarations                                           **
****************************************************************************************************/

#endif  /* FLS_CFG_H_ */


/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

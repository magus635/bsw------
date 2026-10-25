/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Fee_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : DFlash
*
*   brief                 : This file contains all configuration declarations of FEE module
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
*#Fee_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*/


#ifndef  FEE_CFG_H_
#define  FEE_CFG_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "MemIf_Types.h"
#include "NvM.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

#define FEE_CFG_VENDOR_ID                          (175U)
#define FEE_CFG_MODULE_ID                          (21U)

/* Autosar specification version */
#define FEE_CFG_AR_RELEASE_MAJOR_VERSION           (4U)
#define FEE_CFG_AR_RELEASE_MINOR_VERSION           (4U)
#define FEE_CFG_AR_RELEASE_REVISION_VERSION        (0U)

/* Vendor specific implementation version information */
#define FEE_CFG_SW_MAJOR_VERSION                   (1U)
#define FEE_CFG_SW_MINOR_VERSION                   (2U)
#define FEE_CFG_SW_PATCH_VERSION                   (0U)
                    
/* Development error detection enabled/disabled */
#define FEE_DEV_ERROR_DETECT                       (STD_ON)

/* Software verification function enabled/disabled */
#define FEE_SOFTWARE_VERIFY                        (STD_ON)

/* Fee_GetVersionInfo API enabled/disabled */
#define FEE_VERSION_INFO_API                       (STD_ON)

/* Fee_SetMode API enabled/disabled */
#define FEE_SETMODE_API                            (STD_ON)

/* GC restart write enabled/disabled */
#define FEE_GC_RESTART_WRITE                       (STD_ON)

/* Fee module configuration count */
#define FEE_CONFIG_COUNT                           (1U)

/* Number of Sectors allocated to Fee by FlsSector */
#define FEE_SECTOR_NUMBER                          (64U)

/* The starting address of the fee set by FlsSector */
#define FEE_STARTADDRESS                           (0U)

/* The sector size of the Fee set by FlsSector */
#define FEE_SECTOR_SIZE                            (8192U)

/* Fee amount of shift between sector and byte conversion */
#define FEE_SECTOR_TO_BYTE_SHIFT                   (13U)

/* Size of Dflash allocated to Fee by FlsSector */
#define FEE_DFLASH_SIZE                            (524288U)

/* The configuration of the Fee module shall be such that the virtual page size 
(defined in FeeVirtualPageSize) is an integer multiple of the physical page size, 
i.e. it is not allowed to configure a smaller virtual page than the actual physical
page size. [SWS_Fee_00076] */
#define FEE_VIRTUAL_PAGE_SIZE                      (16U)

/* The amount of shift between page and byte conversion */
#define FEE_PAGE_TO_BYTE_SHIFT                     (4U)

/* Logical block's overhead in bytes */
/* #Violation: Fee_Cfg_h_REF_1 */
#define FEE_BLOCK_OVERHEAD                         (24U)

/* Logical block's data page overhead in bytes */
#define FEE_PAGE_OVERHEAD                          (1U)

/* Number of blocks fee can handle */
#define FEE_MAX_BLOCK_COUNT                        (2U)

/* The maximum number of bad sector allowed */
#define FEE_MAX_BADSECTOR_COUNT                    (2U)

/* Byte size occupied by all configured blocks */
/* #Violation: Fee_Cfg_h_REF_1 */
#define FEE_ALL_BLOCK_SIZE                         (160U)

/* The size of the max block. */
/* #Violation: Fee_Cfg_h_REF_1 */
#define FEE_MAX_BLOCK_SIZE                         (96U)


/* Threshold for normal write, should cover immediate data */
#define FEE_THRESHOLD_LIMIT                        (200U)

/* When the Fee module is initialized, it is detected that there is no Fee management */
/* information in the flash memory. (or it is virgin flash) */
/* TRUE: Stop the initialization operation and call the notification function */
/* FALSE: Continue the initialization operation and write Fee management information */
#define FEE_NOT_FOUND_MANAGEMENTINFO_DETECT        (STD_OFF)

/* The maximum write capacity of a FeeMainFunction */
#define FEE_WRITE_LEN_MAX                          (128U)

/* FeeMainFunction Period value in micro seconds(us) */
/* #Violation: Fee_Cfg_h_REF_1 */
#define FEE_MAIN_FUNCTION_PERIOD                   (10000U)

/* Symbolic names of logical blocks */
#ifdef FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0 already defined
#else 
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0                        (8U)
#endif /* \#ifdef FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_0 */

#ifdef FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_1 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_1 already defined
#else 
#define FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_1                        (9U)
#endif /* \#ifdef FeeConf_FeeBlockConfiguration_FeeBlockConfiguration_1 */


/* Fee module Core allocation */
/* CPU0 = 0U; CPU1 = 1U */
#define FEE_CORE_ALLOCATION             (0U)

/****************************************************************************************************
*                          Callback Function Declarations                                          **
****************************************************************************************************/
/* Function declaration of Fee Unavailable Failure Notifications */
extern void NvM_UnavailableFailureNotification(void);

/* Discover NonErasable Areas Notification Function is not configured */
/* Not Found ManagementInfo Notification Function is not configured */

#define FEE_DISABLE_DEM_REPORT   (0U)
#define FEE_ENABLE_DEM_REPORT    (1U)

/* DEM Configurations */
#define FEE_GC_WRITE_DEM_REPORT            (FEE_DISABLE_DEM_REPORT)

#define FEE_GC_READ_DEM_REPORT             (FEE_DISABLE_DEM_REPORT)

#define FEE_GC_ERASE_DEM_REPORT            (FEE_DISABLE_DEM_REPORT)

#define FEE_GC_TRIG_DEM_REPORT             (FEE_DISABLE_DEM_REPORT)

#define FEE_WRITE_CYCLES_DEM_REPORT        (FEE_DISABLE_DEM_REPORT)

#define FEE_UNCFG_BLK_DEM_REPORT           (FEE_DISABLE_DEM_REPORT)

#define FEE_DEM_ENABLED                    (STD_OFF)

#endif /* FEE_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

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

[!NOCODE!][!//
[!INCLUDE "Fls.m"!][!//
[!ENDNOCODE!][!//
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
#define FLS_CFG_AR_RELEASE_MAJOR_VERSION            ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define FLS_CFG_AR_RELEASE_MINOR_VERSION            ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define FLS_CFG_AR_RELEASE_REVISION_VERSION         ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)


/* Vendor specific implementation version information */
#define FLS_CFG_SW_MAJOR_VERSION                    ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define FLS_CFG_SW_MINOR_VERSION                    ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define FLS_CFG_SW_PATCH_VERSION                    ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define FLS_CFG_VENDOR_ID                           ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define FLS_CFG_MODULE_ID                           ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/***************************************************************************************************
*                            Definitions and Macros
****************************************************************************************************/
[!/* Select MODULE-CONFIGURATION as context-node */!][!//
[!SELECT "as:modconf('Fls')[1]"!][!//
[!//
/* Config Constant */
#define FLS_INSTANCE_ID                 ([!"num:i(FlsGeneral/FlsDriverIndex)"!]U)

/*
Configuration: FlsSafetyDetect
- if Selected, Safety Error Check is Enabled 
- if Deselected, Safety Error Check is Disabled 
*/
#define FLS_SAFETY_ENABLE                                  [!IF "FlsGeneral/FlsSafetyErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: FlsDflashECCTriggerBusErrorMaskEnable
- if Selected, Mask bus error is triggered when ECC Error occurs
- if Deselected, Unmask bus error is not triggered when ECC Error occurs
*/
#define FLS_DF_ECC_TRIGGER_BUS_ERROR_MASK_ENABLE           [!IF "FlsGeneral/FlsDflashECCTriggerBusErrorMaskEnable = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]


/* Configuration of whether to use FLS to operate PFLASH or not */
[!INDENT "0"!][!//
[!VAR "Fls_IsPFlashUsed" = " 'false' "!][!//
[!LOOP "node:order(as:modconf('Fls')[1]/FlsConfigSet/FlsSectorList/FlsSector/*, 'FlsSectorStartaddress')"!][!//
    [!IF "num:i(./FlsSectorStartaddress) >= ecu:get('Fls.PFlashVirtualBaseAddress') and num:i(./FlsSectorStartaddress) < ecu:get('Fls.PFlashVirtualEndAddress') "!][!//
        [!VAR "Fls_IsPFlashUsed" = " 'true' "!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
#define FLS_PFLASH_USED                                    [!IF "$Fls_IsPFlashUsed = 'false' "!](STD_OFF)[!ELSE!](STD_ON)[!ENDIF!][!//
[!ENDINDENT!]

/* Information for Fls */
/* DFlash and PFlash base address */
#define FLS_DFLASH_BASE_ADDRESS         ([!"num:inttohex(num:i(FlsGeneral/FlsBaseAddress), 8)"!]U)
#define FLS_PFLASH_BASE_ADDRESS         ([!"num:inttohex(num:i(ecu:get('Fls.PFlashBaseAddress')), 8)"!]U)
/* DFlash and PFlash size */
#define FLS_DFLASH_TOTAL_SIZE           ([!"num:inttohex(num:i(ecu:get('Fls.TotalSize')), 8)"!]U)
#define FLS_PFLASH_TOTAL_SIZE           ([!"num:inttohex(num:i(ecu:get('Fls.PFlashTotalSize')), 8)"!]U)
/* DFlash and PFlash sector size */
#define FLS_DFLASH_SECTOR_SIZE          ([!"num:inttohex(num:i(ecu:get('Fls.SectorSize')), 8)"!]U)
#define FLS_PFLASH_SECTOR_SIZE          ([!"num:inttohex(num:i(ecu:get('Fls.PFlashSectorSize')), 8)"!]U)
/* DFlash and PFlash page size */
#define FLS_DFLASH_PAGE_SIZE            ([!"num:inttohex(num:i(ecu:get('Fls.PageSize')), 8)"!]U)
#define FLS_PFLASH_PAGE_SIZE            ([!"num:inttohex(num:i(ecu:get('Fls.PFlashPageSize')), 8)"!]U)
/* DFlash and PFlash row size */
#define FLS_DFLASH_ROW_SIZE             ([!"num:inttohex(num:i(ecu:get('Fls.DFlashRowSize')), 8)"!]U)
#define FLS_PFLASH_ROW_SIZE             ([!"num:inttohex(num:i(ecu:get('Fls.PFlashRowSize')), 8)"!]U)
/* DFlash and PFlash end address */
#define FLS_DFLASH_END_ADDRESS          ([!"num:inttohex(num:i(ecu:get('Fls.TotalSize')) + num:i(ecu:get('Fls.BaseAddress')) - num:i(1))"!]U)
#define FLS_PFLASH_END_ADDRESS          ([!"num:inttohex(num:i(ecu:get('Fls.PFlashTotalSize')) + num:i(ecu:get('Fls.PFlashBaseAddress')) - num:i(1))"!]U)


/* Hardware Information (Base address). [SWS_Fls_00217] */
/* Page size of DFlash */
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_PAGE_SIZE                   FLS_DFLASH_PAGE_SIZE
/* Sector size of DFlash */
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_SECTOR_SIZE                 FLS_DFLASH_SECTOR_SIZE
/* DFLASH total size */
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_TOTAL_SIZE                  ([!"num:inttohex(num:i(FlsGeneral/FlsTotalSize))"!]U)

/* Maximum time to erase one complete flash sector in Microseconds. */
[!VAR "EraseTime" = "FlsPublishedInformation/FlsEraseTime"!][!//
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_ERASE_SECTOR_TIMEOUT_US     ([!"num:i($EraseTime)"!]ULL)
/* Maximum time to program one complete flash page in Microseconds. */
[!VAR "WriteTime" = "FlsPublishedInformation/FlsWriteTime"!][!//
/* #Violation: Fls_Cfg_h_REF_1 */
#define FLS_WRITE_PAGE_TIMEOUT_US       ([!"num:i($WriteTime)"!]ULL)
/* The contents of an erased flash memory cell. */
[!VAR "ErasedValue" = "FlsPublishedInformation/FlsErasedValue"!][!//
#define FLS_ERASE_VALUE                 ([!"num:inttohex($ErasedValue)"!]U)

/* Fls_cancel api selection enabled/disabled */
#define FLS_CANCEL_API                  ([!//
[!IF "FlsGeneral/FlsCancelApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Fls_SetMode api selection enabled/disabled */
#define FLS_SET_MODE_API                ([!//
[!IF "FlsGeneral/FlsSetModeApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Fls_compare api selection enabled/disabled */
#define FLS_COMPARE_API                 ([!//
[!IF "FlsGeneral/FlsCompareApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Fls_GetJobResult api selection enabled/disabled */
#define FLS_GET_JOB_RESULT_API          ([!//
[!IF "FlsGeneral/FlsGetJobResultApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Fls_GetStatus api selection enabled/disabled */
#define FLS_GET_STATUS_API              ([!//
[!IF "FlsGeneral/FlsGetStatusApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Fls_GetVersionInfo api selection enabled/disabled */
#define FLS_VERSION_INFO_API            ([!//
[!IF "FlsGeneral/FlsVersionInfoApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Fls_BlankCheck api selection enabled/disabled */
#define FLS_BLANK_CHECK_API             ([!//
[!IF "FlsGeneral/FlsBlankCheckApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Development error detection enabled/disabled */
#define FLS_DEV_ERROR_DETECT            ([!//
[!IF "FlsGeneral/FlsDevErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Interrupt Use/Unused */
#define FLS_USE_INTERRUPTS              ([!//
[!IF "FlsGeneral/FlsUseInterrupts = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Pre-processor switch to enable / disable the write verification. */
#define FLS_ERASE_VERIFICATION_ENABLED  ([!//
[!IF "FlsGeneral/FlsWriteVerificationEnabled"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Pre-processor switch to enable / disable the erase verification */
#define FLS_WRITE_VERIFICATION_ENABLED  ([!//
[!IF "FlsGeneral/FlsEraseVerificationEnabled"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* Pre-processor switch to enable / disable the timeout supervision. */
#define FLS_TIMEOUT_SUPERVISION_ENABLED ([!//
[!IF "FlsGeneral/FlsTimeoutSupervisionEnabled"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)


/* Fls module configuration count */
#define FLS_CONFIG_COUNT                (1U)

[!VAR "Var_MasterCore" = "as:modconf('Resource')/ResourceCoreConfigSet/ResourceMasterCore"!][!//
[!IF "$Var_MasterCore = 'CORE0'"!][!//
#define FLS_CORE_ALLOCATION             (0U)
[!ELSE!][!//
#define FLS_CORE_ALLOCATION             (1U)
[!ENDIF!][!//


/****************************************************************************************************
*                         Callback Function Declarations                                           **
****************************************************************************************************/
[!VAR "PostBuildType" = "'SELECTABLE'"!][!//
[!IF "$PostBuildType = 'SELECTABLE'"!][!//
[!SELECT "FeeGeneral"!][!//
[!IF "node:exists(./FeeUnavailableFailureNotification)"!][!//
[!VAR "UnavailableFailureNotification" = "./FeeUnavailableFailureNotification"!][!//
[!ELSE!][!//
[!VAR "UnavailableFailureNotification" = "''"!][!//
[!ENDIF!][!//
[!IF "string-length($UnavailableFailureNotification) = 0"!][!//
[!VAR "UnavailableFailureNotification" = "'(Fee_NotificationPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$UnavailableFailureNotification = '"NULL"' or $UnavailableFailureNotification = 'NULL' or $UnavailableFailureNotification = 'NULL_PTR' or $UnavailableFailureNotification = ''"!][!//
[!VAR "UnavailableFailureNotification" = "'(Fee_NotificationPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$PostBuildType != 'SELECTABLE'"!][!//
[!VAR "UnavailableFailureNotification" = "concat('(Fee_NotificationPtrType)',($UnavailableFailureNotification))"!][!//
[!ELSE!][!//
[!VAR "UnavailableFailureNotification" = "$UnavailableFailureNotification"!][!//
[!ENDIF!][!//
[!IF "$UnavailableFailureNotification != '(Fee_NotificationPtrType)0'"!][!//
/* Function declaration of Fee Unavailable Failure Notifications */
extern void [!"$UnavailableFailureNotification"!](void);

[!ELSE!][!//
/* Unavailable Failure Notification Function is not configured */
[!ENDIF!][!//
[!//
[!IF "node:exists(./FeeDiscoverNonErasableAreasNotification)"!][!//
[!VAR "DiscoverNonErasableAreasNotification" = "./FeeDiscoverNonErasableAreasNotification"!][!//
[!ELSE!][!//
[!VAR "DiscoverNonErasableAreasNotification" = "''"!][!//
[!ENDIF!][!//
[!IF "string-length($DiscoverNonErasableAreasNotification) = 0"!][!//
[!VAR "DiscoverNonErasableAreasNotification" = "'(Fee_NotificationPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$DiscoverNonErasableAreasNotification = '"NULL"' or $DiscoverNonErasableAreasNotification = 'NULL' or $DiscoverNonErasableAreasNotification = 'NULL_PTR' or $DiscoverNonErasableAreasNotification = ''"!][!//
[!VAR "DiscoverNonErasableAreasNotification" = "'(Fee_NotificationPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$PostBuildType != 'SELECTABLE'"!][!//
[!VAR "DiscoverNonErasableAreasNotification" = "concat('(Fee_NotificationPtrType)',($DiscoverNonErasableAreasNotification))"!][!//
[!ELSE!][!//
[!VAR "DiscoverNonErasableAreasNotification" = "$DiscoverNonErasableAreasNotification"!][!//
[!ENDIF!][!//
[!IF "$DiscoverNonErasableAreasNotification != '(Fee_NotificationPtrType)0'"!][!//
/* Function declaration of Fee Discover NonErasable Areas Notifications */
extern void [!"$DiscoverNonErasableAreasNotification"!](void);

[!ELSE!][!//
/* Discover NonErasable Areas Notification Function is not configured */
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDIF!][!//

#endif  /* FLS_CFG_H_ */
[!ENDSELECT!]

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

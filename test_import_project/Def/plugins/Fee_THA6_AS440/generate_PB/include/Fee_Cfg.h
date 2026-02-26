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

[!NOCODE!][!//
[!INCLUDE "Fee.m"!][!//
[!ENDNOCODE!][!//

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

#define FEE_CFG_VENDOR_ID                          ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define FEE_CFG_MODULE_ID                          ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/* Autosar specification version */
#define FEE_CFG_AR_RELEASE_MAJOR_VERSION           ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define FEE_CFG_AR_RELEASE_MINOR_VERSION           ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define FEE_CFG_AR_RELEASE_REVISION_VERSION        ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

/* Vendor specific implementation version information */
#define FEE_CFG_SW_MAJOR_VERSION                   ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define FEE_CFG_SW_MINOR_VERSION                   ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define FEE_CFG_SW_PATCH_VERSION                   ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)
                    
/* Development error detection enabled/disabled */
[!IF "FeeGeneral/FeeDevErrorDetect = 'true'"!][!//
#define FEE_DEV_ERROR_DETECT                       (STD_ON)
[!ELSE!][!//
#define FEE_DEV_ERROR_DETECT                       (STD_OFF)
[!ENDIF!][!//

/* Software verification function enabled/disabled */
[!IF "FeeGeneral/FeeSoftwareVerify = 'true'"!][!//
#define FEE_SOFTWARE_VERIFY                        (STD_ON)
[!ELSE!][!//
#define FEE_SOFTWARE_VERIFY                        (STD_OFF)
[!ENDIF!][!//

/* Fee_GetVersionInfo API enabled/disabled */
[!IF "FeeGeneral/FeeVersionInfoApi = 'true'"!][!//
#define FEE_VERSION_INFO_API                       (STD_ON)
[!ELSE!][!//
#define FEE_VERSION_INFO_API                       (STD_OFF)
[!ENDIF!][!//

/* Fee_SetMode API enabled/disabled */
[!IF "FeeGeneral/FeeSetModeSupported = 'true'"!][!//
#define FEE_SETMODE_API                            (STD_ON)
[!ELSE!][!//
#define FEE_SETMODE_API                            (STD_OFF)
[!ENDIF!][!//

/* GC restart write enabled/disabled */
[!IF "FeeGeneral/FeeGcRestart = 'FEE_GC_RESTART_WRITE'"!][!//
#define FEE_GC_RESTART_WRITE                       (STD_ON)
[!ELSE!][!//
#define FEE_GC_RESTART_WRITE                       (STD_OFF)
[!ENDIF!][!//

/* Fee module configuration count */
#define FEE_CONFIG_COUNT                           (1U)

/* Number of Sectors allocated to Fee by FlsSector */
#define FEE_SECTOR_NUMBER                          ([!"num:i(node:ref(FeeGeneral/FeeFlsSectorSelectionRef)/FlsNumberOfSectors)"!]U)

/* The starting address of the fee set by FlsSector */
#define FEE_STARTADDRESS                           ([!"num:i(node:ref(FeeGeneral/FeeFlsSectorSelectionRef)/FlsSectorStartaddress)"!]U)

/* The sector size of the Fee set by FlsSector */
#define FEE_SECTOR_SIZE                            ([!"num:i(node:ref(FeeGeneral/FeeFlsSectorSelectionRef)/FlsSectorSize)"!]U)

/* Fee amount of shift between sector and byte conversion */
[!IF "num:i(node:ref(FeeGeneral/FeeFlsSectorSelectionRef)/FlsSectorSize) = 1024"!][!//
#define FEE_SECTOR_TO_BYTE_SHIFT                   (10U)
[!ELSE!][!//
#define FEE_SECTOR_TO_BYTE_SHIFT                   (13U)
[!ENDIF!][!//

/* Size of Dflash allocated to Fee by FlsSector */
#define FEE_DFLASH_SIZE                            ([!"num:i(num:i(node:ref(FeeGeneral/FeeFlsSectorSelectionRef)/FlsNumberOfSectors) * num:i(node:ref(FeeGeneral/FeeFlsSectorSelectionRef)/FlsSectorSize))"!]U)

[!NOCODE!][!//
[!VAR "FlashPageSize" = "ecu:get('Fls.PageSize')"!][!//
[!VAR "FeeVirtualPageSize" = "num:i(FeeGeneral/FeeVirtualPageSize)"!][!//
[!VAR "Temp0" = "$FeeVirtualPageSize div $FlashPageSize"!][!//
[!VAR "Temp1" = "num:i($Temp0)"!][!//
[!VAR "Temp2" = "$Temp0 - $Temp1"!][!//
[!IF "$Temp2 != 0"!][!//
[!ERROR!][!//
21-00-03-ERROR: The configuration of the Fee module shall be such that the virtual page size 
(defined in FeeVirtualPageSize) is an integer multiple of the physical page size, 
i.e. it is not allowed to configure a smaller virtual page than the actual physical
page size. [SWS_Fee_00076]
[!ENDERROR!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
/* The configuration of the Fee module shall be such that the virtual page size 
(defined in FeeVirtualPageSize) is an integer multiple of the physical page size, 
i.e. it is not allowed to configure a smaller virtual page than the actual physical
page size. [SWS_Fee_00076] */
#define FEE_VIRTUAL_PAGE_SIZE                      ([!"num:i($FeeVirtualPageSize)"!]U)

/* The amount of shift between page and byte conversion */
[!CALL "Fee_GetPageToByteShift"!][!//

/* Logical block's overhead in bytes */
/* #Violation: Fee_Cfg_h_REF_1 */
#define FEE_BLOCK_OVERHEAD                         ([!"num:i(FeePublishedInformation/FeeBlockOverhead)"!]U)

/* Logical block's data page overhead in bytes */
#define FEE_PAGE_OVERHEAD                          ([!"num:i(FeePublishedInformation/FeePageOverhead)"!]U)

/* Number of blocks fee can handle */
[!VAR "feemaxblkcnt" = "num:i(./FeeGeneral/FeeMaxBlockCount)"!][!//
[!IF "num:i(count(FeeBlockConfiguration/*)) > $feemaxblkcnt"!][!//
[!VAR "feemaxblkcnt" = "num:i(count(FeeBlockConfiguration/*))"!][!//
[!ENDIF!][!//
#define FEE_MAX_BLOCK_COUNT                        ([!"num:i($feemaxblkcnt)"!]U)

/* The maximum number of bad sector allowed */
#define FEE_MAX_BADSECTOR_COUNT                    ([!"num:i(./FeeGeneral/FeeMaxAllowedBadSector)"!]U)

/* Byte size occupied by all configured blocks */
[!CALL "Fee_GetAllBlockSize"!][!//

/* Threshold for normal write, should cover immediate data */
#define FEE_THRESHOLD_LIMIT                        ([!"num:i(./FeeGeneral/FeeThresholdValue)"!]U)

/* When the Fee module is initialized, it is detected that there is no Fee management */
/* information in the flash memory. (or it is virgin flash) */
/* TRUE: Stop the initialization operation and call the notification function */
/* FALSE: Continue the initialization operation and write Fee management information */
[!IF "FeeGeneral/FeeNotFoundManagementInfo = 'true'"!][!//
#define FEE_NOT_FOUND_MANAGEMENTINFO_DETECT        (STD_ON)
[!ELSE!][!//
#define FEE_NOT_FOUND_MANAGEMENTINFO_DETECT        (STD_OFF)
[!ENDIF!][!//

/* The maximum write capacity of a FeeMainFunction */
[!NOCODE!][!//
[!VAR "FeeMaxWriteBytes" = "./FeeGeneral/FeeMaxWriteBytesPerCycle"!][!//
[!IF "$FeeMaxWriteBytes = 'FEE_MAX_BYTES_32_PERCYCLE'"!][!//
[!VAR "FeeMaxWriteBytes" = "num:i(32)"!][!//
[!ELSEIF "$FeeMaxWriteBytes = 'FEE_MAX_BYTES_64_PERCYCLE'"!][!//
[!VAR "FeeMaxWriteBytes" = "num:i(64)"!][!//
[!ELSE!][!//
[!VAR "FeeMaxWriteBytes" = "num:i(128)"!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//
#define FEE_WRITE_LEN_MAX                          ([!"num:i($FeeMaxWriteBytes)"!]U)

/* FeeMainFunction Period value in micro seconds(us) */
/* #Violation: Fee_Cfg_h_REF_1 */
#define FEE_MAIN_FUNCTION_PERIOD                   ([!"num:i((./FeeGeneral/FeeMainFunctionPeriod) * 1000 * 1000)"!]U)

/* Symbolic names of logical blocks */
[!LOOP "FeeBlockConfiguration/*"!][!//
[!VAR "SymbolicName" = "node:name(.)"!][!//
#ifdef FeeConf_FeeBlockConfiguration_[!"$SymbolicName"!] 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_[!"$SymbolicName"!] already defined
#else 
#define FeeConf_FeeBlockConfiguration_[!"$SymbolicName"!]                        ([!"(num:i(./FeeBlockNumber))"!]U)
#endif /* \#ifdef FeeConf_FeeBlockConfiguration_[!"$SymbolicName"!] */

[!ENDLOOP!][!//

/* Fee module Core allocation */
/* CPU0 = 0U; CPU1 = 1U */
[!VAR "Var_MasterCore" = "as:modconf('Resource')/ResourceCoreConfigSet/ResourceMasterCore"!][!//
[!IF "$Var_MasterCore = 'CORE0'"!][!//
#define FEE_CORE_ALLOCATION             (0U)
[!ELSE!][!//
#define FEE_CORE_ALLOCATION             (1U)
[!ENDIF!][!//

/****************************************************************************************************
*                          Callback Function Declarations                                          **
****************************************************************************************************/
[!VAR "PostBuildType" = "'SELECTABLE'"!][!//
[!IF "$PostBuildType = 'SELECTABLE'"!][!//
[!SELECT "FeeGeneral"!][!//
[!//
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
[!//
[!IF "node:exists(./FeeNotFoundManagementInfoNotification)"!][!//
[!VAR "NotFoundManagementInfoNotification" = "./FeeNotFoundManagementInfoNotification"!][!//
[!ELSE!][!//
[!VAR "NotFoundManagementInfoNotification" = "''"!][!//
[!ENDIF!][!//
[!IF "string-length($NotFoundManagementInfoNotification) = 0"!][!//
[!VAR "NotFoundManagementInfoNotification" = "'(Fee_NotificationPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$NotFoundManagementInfoNotification = '"NULL"' or $NotFoundManagementInfoNotification = 'NULL' or $NotFoundManagementInfoNotification = 'NULL_PTR' or $NotFoundManagementInfoNotification = ''"!][!//
[!VAR "NotFoundManagementInfoNotification" = "'(Fee_NotificationPtrType)0'"!][!//
[!ENDIF!][!//
[!IF "$PostBuildType != 'SELECTABLE'"!][!//
[!VAR "NotFoundManagementInfoNotification" = "concat('(Fee_NotificationPtrType)',($NotFoundManagementInfoNotification))"!][!//
[!ELSE!][!//
[!VAR "NotFoundManagementInfoNotification" = "$NotFoundManagementInfoNotification"!][!//
[!ENDIF!][!//
[!IF "$NotFoundManagementInfoNotification != '(Fee_NotificationPtrType)0'"!][!//
/* Function declaration of Fee Not Found ManagementInfo Notifications */
extern void [!"$NotFoundManagementInfoNotification"!](void);

[!ELSE!][!//
/* Not Found ManagementInfo Notification Function is not configured */
[!ENDIF!][!//
[!ENDSELECT!][!//
[!ENDIF!][!//

#define FEE_DISABLE_DEM_REPORT   (0U)
#define FEE_ENABLE_DEM_REPORT    (1U)

/* DEM Configurations */
[!VAR "FeeDemEnabled" = "num:i(0)"!][!//
[!NOCODE!][!//
[!IF "(node:exists(FeeDemEventParameterRefs/FEE_E_GC_WRITE)) and (node:value(FeeDemEventParameterRefs/FEE_E_GC_WRITE) != '')"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!CODE!][!//
#define FEE_E_GC_WRITE                     (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(FeeDemEventParameterRefs/FEE_E_GC_WRITE)))"!])
#define FEE_GC_WRITE_DEM_REPORT            (FEE_ENABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
#define FEE_GC_WRITE_DEM_REPORT            (FEE_DISABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ENDIF!][!//
[!IF "(node:exists(FeeDemEventParameterRefs/FEE_E_GC_READ)) and (node:value(FeeDemEventParameterRefs/FEE_E_GC_READ) != '')"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!CODE!][!//
#define FEE_E_GC_READ                      (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(FeeDemEventParameterRefs/FEE_E_GC_READ)))"!])
#define FEE_GC_READ_DEM_REPORT             (FEE_ENABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
#define FEE_GC_READ_DEM_REPORT             (FEE_DISABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ENDIF!][!//
[!IF "(node:exists(FeeDemEventParameterRefs/FEE_E_GC_ERASE)) and (node:value(FeeDemEventParameterRefs/FEE_E_GC_ERASE) != '')"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!CODE!][!//
#define FEE_E_GC_ERASE                     (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(FeeDemEventParameterRefs/FEE_E_GC_ERASE)))"!])
#define FEE_GC_ERASE_DEM_REPORT            (FEE_ENABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
#define FEE_GC_ERASE_DEM_REPORT            (FEE_DISABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ENDIF!][!//
[!IF "(node:exists(FeeDemEventParameterRefs/FEE_E_GC_TRIG)) and (node:value(FeeDemEventParameterRefs/FEE_E_GC_TRIG) != '')"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!CODE!][!//
#define FEE_E_GC_TRIG                      (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(FeeDemEventParameterRefs/FEE_E_GC_TRIG)))"!])
#define FEE_GC_TRIG_DEM_REPORT             (FEE_ENABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
#define FEE_GC_TRIG_DEM_REPORT             (FEE_DISABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ENDIF!][!//
[!IF "(node:exists(FeeDemEventParameterRefs/FEE_E_WRITE_CYCLES_EXHAUSTED)) and (node:value(FeeDemEventParameterRefs/FEE_E_WRITE_CYCLES_EXHAUSTED) != '')"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!CODE!][!//
#define FEE_E_WRITE_CYCLES_EXHAUSTED       (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(FeeDemEventParameterRefs/FEE_E_WRITE_CYCLES_EXHAUSTED)))"!])
#define FEE_WRITE_CYCLES_DEM_REPORT        (FEE_ENABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
#define FEE_WRITE_CYCLES_DEM_REPORT        (FEE_DISABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ENDIF!][!//
[!IF "(node:exists(FeeDemEventParameterRefs/FEE_E_UNCONFIG_BLK_EXCEEDED)) and (node:value(FeeDemEventParameterRefs/FEE_E_UNCONFIG_BLK_EXCEEDED) != '')"!][!//
[!VAR "FeeDemEnabled" = "num:i(1)"!][!//
[!CODE!][!//
#define FEE_E_UNCONFIG_BLK_EXCEEDED        (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(FeeDemEventParameterRefs/FEE_E_UNCONFIG_BLK_EXCEEDED)))"!])
#define FEE_UNCFG_BLK_DEM_REPORT           (FEE_ENABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
#define FEE_UNCFG_BLK_DEM_REPORT           (FEE_DISABLE_DEM_REPORT)

[!ENDCODE!][!//
[!ENDIF!][!//
[!IF "$FeeDemEnabled = num:i(1)"!][!//
[!CODE!][!//
#define FEE_DEM_ENABLED                    (STD_ON)
[!ENDCODE!][!//
[!ELSE!][!//
[!CODE!][!//
#define FEE_DEM_ENABLED                    (STD_OFF)
[!ENDCODE!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

#endif /* FEE_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

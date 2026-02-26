/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Wdg_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : CPUWDT
*
*   brief                 : This file contains all configuration declarations of Wdg Driver
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
*#Wdg_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification:The macros are reserved for upper layers.
*
*/

[!NOCODE!][!//
[!INCLUDE "Wdg.m"!][!//
[!ENDNOCODE!][!//
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#ifndef WDG_CFG_H_
#define WDG_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define WDG_CFG_AR_RELEASE_MAJOR_VERSION       ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define WDG_CFG_AR_RELEASE_MINOR_VERSION       ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
/* #Violation: Wdg_Cfg_h_REF_1 */
#define WDG_CFG_AR_RELEASE_REVISION_VERSION    ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define WDG_CFG_SW_MAJOR_VERSION               ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define WDG_CFG_SW_MINOR_VERSION               ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define WDG_CFG_SW_PATCH_VERSION               ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define WDG_CFG_VENDOR_ID                      ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define WDG_CFG_MODULE_ID                      ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/*
Configuration: WDG_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define WDG_DEV_ERROR_DETECT                   [!IF "WdgGeneral/WdgDevErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/*
Configuration: WDG_DISABLE_ALLOWED
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
/* #Violation: Wdg_Cfg_h_REF_1 */
#define WDG_DISABLE_ALLOWED                    [!IF "WdgGeneral/WdgDisableAllowed = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
/*
Configuration: WDG_SAFETY_ENABLE
- if Selected, Safety runtime error is Enabled
- if Deselected, Safety runtime error is Disabled
*/
#define WDG_SAFETY_ENABLE                      [!IF "WdgGeneral/WdgSafetyErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: WDG_VERSION_INFO_API
- if Selected,  Function Wdg_GetVersionInfo is available
- if Deselected, Function Wdg_GetVersionInfo is not available
*/
#define WDG_VERSION_INFO_API                   [!IF "WdgGeneral/WdgVersionInfoApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* WDG_CLOCK Khz */
/* #Violation: Wdg_Cfg_h_REF_1 */
#define WDG_CLOCK                              ([!"num:i(num:i(node:value(node:ref(WdgGeneral/WdgClockReference)/McuClockReferencePointFrequency)) div 1000)"!]U)

[!NOCODE!][!//
[!FOR "DeviceID" = "1" TO "num:i(ecu:get('Resource.NumOfCores'))"!][!//
[!VAR "WDG_DeviceFindFlag" = "num:i(0)"!][!//
[!LOOP "WdgSettingsConfig/*"!][!//
    [!VAR "WDG_DeviceID" = "./WdgDeviceID"!][!//
    [!IF "$WDG_DeviceID = num:i($DeviceID - num:i(1))"!][!//
    [!VAR "WDG_DeviceFindFlag" = "num:i(1)"!][!//
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!CODE!][!//
#define WDG_DEVICE[!"num:i($DeviceID - num:i(1))"!]_CONFIGURED                  [!IF "$WDG_DeviceFindFlag = num:i(1)"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
[!ENDCODE!][!//
[!ENDFOR!][!//
[!ENDNOCODE!][!//

/* WDG MODULE INSTANCE ID */
#define WDG_INSTANCE_ID                        ([!"num:i(WdgGeneral/WdgIndex)"!]U)

/* Wdg module configuration count */
#define WDG_CONFIG_COUNT                       (1U)

/* Wdg module configuration count */
#define WDG_OVERFLOW_ACTION_RESET              [!IF "WdgGeneral/WdgOverflowAction = 'WDG_OVERFLOW_ACTION_RESET'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* Dem related pre-compile switches */
/* Dem reporting enable/disabled macro */
#define WDG_ENABLE_DEM_REPORT  (1U)
#define WDG_DISABLE_DEM_REPORT (0U)

[!NOCODE!][!//
[!IF "node:exists(WdgDemEventParameterRefs)"!][!//
  [!SELECT "WdgDemEventParameterRefs"!][!//
    [!IF "(node:exists(./WDG_E_DISABLE_REJECTED))"!][!//
[!CODE!][!//
/* \[SWS_Wdg_00179] */
#define WDG_E_DISABLE_REJECTED                 (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./WDG_E_DISABLE_REJECTED)))"!])
#define WDG_DISABLE_REJECT_DEM_REPORT          (WDG_ENABLE_DEM_REPORT)
[!ENDCODE!][!//
    [!ELSE!][!//
[!CODE!][!//
#define WDG_DISABLE_REJECT_DEM_REPORT          (WDG_DISABLE_DEM_REPORT)
[!ENDCODE!][!//
    [!ENDIF!][!//
    [!IF "((node:exists(./WDG_E_MODE_FAILED)))"!][!//
[!CODE!][!//
/* \[SWS_Wdg_00178] */
#define WDG_E_MODE_FAILED                      (DemConf_DemEventParameter_[!"node:name(node:ref(node:value(./WDG_E_MODE_FAILED)))"!])
#define WDG_MODE_FAIL_DEM_REPORT               (WDG_ENABLE_DEM_REPORT)
[!ENDCODE!][!//
    [!ELSE!][!//
[!CODE!][!//
#define WDG_MODE_FAIL_DEM_REPORT               (WDG_DISABLE_DEM_REPORT)
[!ENDCODE!][!//
    [!ENDIF!][!//
  [!ENDSELECT!][!//
[!ELSE!][!//
[!CODE!][!//
#define WDG_DISABLE_REJECT_DEM_REPORT          (WDG_DISABLE_DEM_REPORT)
#define WDG_MODE_FAIL_DEM_REPORT               (WDG_DISABLE_DEM_REPORT)
[!ENDCODE!][!//
[!ENDIF!][!//
[!ENDNOCODE!][!//

/****************************************************************************************************
**                          Global Variable Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Constant Declarations                                           **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Inline Function Definitions                                     **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/

#endif /* WDG_CFG_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

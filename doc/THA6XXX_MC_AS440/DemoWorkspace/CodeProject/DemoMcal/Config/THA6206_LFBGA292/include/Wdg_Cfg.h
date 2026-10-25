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

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#ifndef WDG_CFG_H_
#define WDG_CFG_H_

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
#define WDG_CFG_AR_RELEASE_MAJOR_VERSION       (4U)
#define WDG_CFG_AR_RELEASE_MINOR_VERSION       (4U)
/* #Violation: Wdg_Cfg_h_REF_1 */
#define WDG_CFG_AR_RELEASE_REVISION_VERSION    (0U)

#define WDG_CFG_SW_MAJOR_VERSION               (1U)
#define WDG_CFG_SW_MINOR_VERSION               (2U)
#define WDG_CFG_SW_PATCH_VERSION               (0U)

#define WDG_CFG_VENDOR_ID                      (175U)
#define WDG_CFG_MODULE_ID                      (102U)

/*
Configuration: WDG_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define WDG_DEV_ERROR_DETECT                   (STD_ON)
/*
Configuration: WDG_DISABLE_ALLOWED
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
/* #Violation: Wdg_Cfg_h_REF_1 */
#define WDG_DISABLE_ALLOWED                    (STD_ON)
/*
Configuration: WDG_SAFETY_ENABLE
- if Selected, Safety runtime error is Enabled
- if Deselected, Safety runtime error is Disabled
*/
#define WDG_SAFETY_ENABLE                      (STD_ON)

/*
Configuration: WDG_VERSION_INFO_API
- if Selected,  Function Wdg_GetVersionInfo is available
- if Deselected, Function Wdg_GetVersionInfo is not available
*/
#define WDG_VERSION_INFO_API                   (STD_ON)

/* WDG_CLOCK Khz */
/* #Violation: Wdg_Cfg_h_REF_1 */
#define WDG_CLOCK                              (50000U)

#define WDG_DEVICE0_CONFIGURED                  (STD_ON)
#define WDG_DEVICE1_CONFIGURED                  (STD_ON)

/* WDG MODULE INSTANCE ID */
#define WDG_INSTANCE_ID                        (0U)

/* Wdg module configuration count */
#define WDG_CONFIG_COUNT                       (1U)

/* Wdg module configuration count */
#define WDG_OVERFLOW_ACTION_RESET              (STD_ON)

/* Dem related pre-compile switches */
/* Dem reporting enable/disabled macro */
#define WDG_ENABLE_DEM_REPORT  (1U)
#define WDG_DISABLE_DEM_REPORT (0U)

#define WDG_DISABLE_REJECT_DEM_REPORT          (WDG_DISABLE_DEM_REPORT)
#define WDG_MODE_FAIL_DEM_REPORT               (WDG_DISABLE_DEM_REPORT)

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

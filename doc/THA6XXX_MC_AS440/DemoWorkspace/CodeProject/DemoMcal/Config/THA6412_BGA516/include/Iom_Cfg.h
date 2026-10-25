/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Iom_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : IOM
*
*   brief                 : IOM configuration generated out of ECU configuration file
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Iom_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/


/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#ifndef IOM_CFG_H
#define IOM_CFG_H

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

#define IOM_CFG_AR_RELEASE_MAJOR_VERSION           (4U)
#define IOM_CFG_AR_RELEASE_MINOR_VERSION           (4U)
#define IOM_CFG_AR_RELEASE_REVISION_VERSION        (0U)

#define IOM_CFG_SW_MAJOR_VERSION                   (1U)
#define IOM_CFG_SW_MINOR_VERSION                   (2U)
#define IOM_CFG_SW_PATCH_VERSION                   (0U)

#define IOM_CFG_VENDOR_ID                          (175U)
#define IOM_CFG_MODULE_ID                          (255U)

/*
Configuration: IOM_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected,DET is Disabled
*/
#define IOM_DEV_ERROR_DETECT                       (STD_ON) 

/*
Configuration: IOM_RUNTIME_ERROR_DETECT
- if Selected, Runtime error detect is Enabled
- if Deselected, Runtime error detect is Disabled
*/
/* #Violation: Iom_Cfg_h_REF_1 */
#define IOM_RUNTIME_ERROR_DETECT                   (STD_ON)

/*
Configuration: IOM_SAFETY_ENABLE
- if Selected, safty detect is Enabled
- if Deselected, safty detect is Disabled
*/
#define IOM_SAFETY_ENABLE                          (STD_ON)

/*
Configuration: IOM_VERSION_INFO_API
- if Selected,  Function Iom_GetVersionInfo is available
- if Deselected, Function Iom_GetVersionInfo is not available
*/
#define IOM_VERSION_INFO_API                       (STD_ON) 

/*
Configuration: IOM_PPU_PRESCALER_API
- if Selected,  Function Iom_SetPpuPrecalerThreshold, Iom_GetPpuPrecalerThreshold is available
- if Deselected, Function Iom_SetPpuPrecalerThreshold, Iom_GetPpuPrecalerThreshold is not available
*/
#define IOM_PPU_PRESCALER_API                      (STD_ON) 

/*
Configuration: IOM_PPU_FILTER_API
- if Selected,  Function Iom_SetPpuFilterTimeThreshold, Iom_GetPpuFilterTimeThreshold is available
- if Deselected, Function Iom_SetPpuFilterTimeThreshold, Iom_GetPpuFilterTimeThreshold is not available
*/
#define IOM_PPU_FILTER_API                         (STD_ON) 

/*
Configuration: IOM_GET_PPUGLITCH_API
- if Selected,  Function Iom_GetPpuGlitch is available
- if Deselected, Function Iom_GetPpuGlitch is not available
*/
#define IOM_GET_PPUGLITCH_API                      (STD_ON) 

/*
Configuration: IOM_GTM_EXOR_AVAILABLE
- if Selected, The reference signal can select GTM EXOR signal.
- if Deselected, The reference signal can not select GTM EXOR signal.
*/
/* #Violation: Iom_Cfg_h_REF_1 */
#define IOM_GTM_EXOR_AVAILABLE                     (STD_OFF)

/* The number of used LPU channel */
#define IOM_CHANNEL_USED_NUMBER                    (1U)

/* Iom module Core allocation */
/* CPU00 = 0; CPU01 = 1; CPU02 = 2; CPU03 = 3 */
#define IOM_CORE_ALLOCATION                        (0U)
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

#endif /* IOM_CFG_H */

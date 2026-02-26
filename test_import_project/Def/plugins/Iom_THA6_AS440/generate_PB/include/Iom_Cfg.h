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

[!NOCODE!][!//
[!INCLUDE "Iom.m"!][!//
[!ENDNOCODE!][!//

/***************************************************************************************************
 *                               Include
 ***************************************************************************************************/
#ifndef IOM_CFG_H
#define IOM_CFG_H

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/

#define IOM_CFG_AR_RELEASE_MAJOR_VERSION           ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define IOM_CFG_AR_RELEASE_MINOR_VERSION           ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define IOM_CFG_AR_RELEASE_REVISION_VERSION        ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define IOM_CFG_SW_MAJOR_VERSION                   ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define IOM_CFG_SW_MINOR_VERSION                   ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define IOM_CFG_SW_PATCH_VERSION                   ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define IOM_CFG_VENDOR_ID                          ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define IOM_CFG_MODULE_ID                          ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)

/*
Configuration: IOM_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected,DET is Disabled
*/
#define IOM_DEV_ERROR_DETECT                       [!IF "IomGeneralConfiguration/IomDevErrorDetect = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!][!//


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
#define IOM_SAFETY_ENABLE                          ([!//
[!IF "IomGeneralConfiguration/IomSafetyErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/*
Configuration: IOM_VERSION_INFO_API
- if Selected,  Function Iom_GetVersionInfo is available
- if Deselected, Function Iom_GetVersionInfo is not available
*/
#define IOM_VERSION_INFO_API                       [!IF "IomGeneralConfiguration/IomVersionInfoApi = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!][!//


/*
Configuration: IOM_PPU_PRESCALER_API
- if Selected,  Function Iom_SetPpuPrecalerThreshold, Iom_GetPpuPrecalerThreshold is available
- if Deselected, Function Iom_SetPpuPrecalerThreshold, Iom_GetPpuPrecalerThreshold is not available
*/
#define IOM_PPU_PRESCALER_API                      [!IF "IomGeneralConfiguration/IomPpuPrecalerApi = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!][!//


/*
Configuration: IOM_PPU_FILTER_API
- if Selected,  Function Iom_SetPpuFilterTimeThreshold, Iom_GetPpuFilterTimeThreshold is available
- if Deselected, Function Iom_SetPpuFilterTimeThreshold, Iom_GetPpuFilterTimeThreshold is not available
*/
#define IOM_PPU_FILTER_API                         [!IF "IomGeneralConfiguration/IomPpuFilterApi = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!][!//


/*
Configuration: IOM_GET_PPUGLITCH_API
- if Selected,  Function Iom_GetPpuGlitch is available
- if Deselected, Function Iom_GetPpuGlitch is not available
*/
#define IOM_GET_PPUGLITCH_API                      [!IF "IomGeneralConfiguration/IomGetPpuGlitchApi = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!][!//


/*
Configuration: IOM_GTM_EXOR_AVAILABLE
- if Selected, The reference signal can select GTM EXOR signal.
- if Deselected, The reference signal can not select GTM EXOR signal.
*/
/* #Violation: Iom_Cfg_h_REF_1 */
#define IOM_GTM_EXOR_AVAILABLE                     [!IF "IomGeneralConfiguration/IomGtmExor = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!][!//


/* The number of used LPU channel */
[!VAR "LPUCountNumber" = "num:i(count(IomModuleConfiguration/IomLPUConfiguration/*))"!][!//
#define IOM_CHANNEL_USED_NUMBER                    ([!"$LPUCountNumber"!]U)

/* Iom module Core allocation */
/* CPU00 = 0; CPU01 = 1; CPU02 = 2; CPU03 = 3 */
[!CALL "Iom_FindIomModuleMappedCoreId"!][!//
#define IOM_CORE_ALLOCATION                        ([!"$IOMModuleAllocationCoreId"!]U)
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

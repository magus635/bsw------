/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Lin_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : ASI
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/*
*#Violation Summary
*#Lin_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*/

/***************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "Lin.m"!][!//
[!ENDNOCODE!][!//
/***************************************************************************************************/
#ifndef LIN_CFG_H_
#define LIN_CFG_H_

/****************************************************************************************************
*                            Global Macro Definitions
****************************************************************************************************/
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define LIN_CFG_AR_RELEASE_MAJOR_VERSION                       ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define LIN_CFG_AR_RELEASE_MINOR_VERSION                       ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define LIN_CFG_AR_RELEASE_REVISION_VERSION                    ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define LIN_CFG_SW_MAJOR_VERSION                               ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define LIN_CFG_SW_MINOR_VERSION                               ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define LIN_CFG_SW_PATCH_VERSION                               ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define LIN_CFG_VENDOR_ID                                      ([!"num:i(CommonPublishedInformation/VendorId)"!]U)/*([!"text:toupper(num:inttohex(CommonPublishedInformation/VendorId))"!])*/
#define LIN_CFG_MODULE_ID                                      ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)/*([!"text:toupper(num:inttohex(CommonPublishedInformation/ModuleId))"!])*/
/*
Configuration: LIN_DEV_ERROR_DETECT  
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define LIN_DEV_ERROR_DETECT                                   [!IF "LinGeneral/LinDevErrorDetect = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: LIN_VERSION_INFO_API  
- if Selected, Function Lin_GetVersionInfo is Enabled
- if Deselected, Function Lin_GetVersionInfo is Enabled
*/
#define LIN_VERSION_INFO_API                                   [!IF "LinGeneral/LinVersionInfoApi = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: LIN_CFG_INTERRUPT_ENABLE  
- if Selected, Lin Channels working in interrupt mode
- if Deselected, Lin Channels working in non-interrupt mode
*/
#define LIN_CFG_INTERRUPT_ENABLE                               [!IF "LinGeneral/LinInterruptEnable = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: LIN_DEM_ERROR_REPORT_STATUS
 Specifies whether report LIN_E_TIMEOUT.
*/
[!IF "node:exists(LinDemEventParameterRefs/LIN_E_TIMEOUT)"!][!//
[!IF "node:exists(node:ref(LinDemEventParameterRefs/LIN_E_TIMEOUT))"!][!//
#define LIN_DEM_ERROR_REPORT_STATUS                            (STD_ON)
/*
Configuration: LIN_DEM_ERROR_REPORT_STATUS
 Defining Hardware Error Event ID.
*/
#define LIN_E_TIMEOUT                                          ((Dem_EventIdType)DemConf_DemEventParameter_[!"node:name(node:ref(LinDemEventParameterRefs/LIN_E_TIMEOUT))"!])
[!ELSE!][!//
[!ERROR "Invalid reference for LIN_E_TIMEOUT"!][!//
[!ENDIF!][!//
[!ELSE!][!//
#define LIN_DEM_ERROR_REPORT_STATUS                            (STD_OFF)
[!ENDIF!][!//

/*
Macro definition: LINIF_WAKEUP_SUPPORT
 Generate the macro definition LinIf_WakeupConfirmation function is available.
*/
[!CALL "CG_GeneLinWakeUpMacro"!]

/*
Configuration: LIN_TIMEOUT_DURATION
 Specifies duration of LIN channel timeout.
*/
#define LIN_TIMEOUT_DURATION                                   ([!"num:i(LinGeneral/LinTimeoutDuration)"!]U)

/*
Configuration: LIN_INDEX
 Specifies index number of LIN channel.
*/
/* #Violation: Lin_Cfg_h_REF_1 */
#define LIN_INDEX                                              ([!"num:i(LinGeneral/LinIndex)"!]U)

/*
Configuration: LIN_CONFIG_COUNT
 Defines the total number of LIN Config infomation.
*/
#define LIN_CONFIG_COUNT                                       (1U)

/*
Configuration: LIN_MAX_HWUNIT_COUNT
 Defines the total number of LIN HwUnit.
*/
#define LIN_MAX_HWUNIT_COUNT                                   ([!"num:i(ecu:get('Asi.MaxHwUnit'))"!]U)

/*
Configuration: LIN_TOTAL_CFG_CHANNEL_NUM
 Define the total number of LIN channels.
*/
#define LIN_TOTAL_CFG_CHANNEL_NUM                              ([!"num:i(count(LinGlobalConfig/LinChannel/*))"!]U)

/* 
Whether there is hardware 
as a master mode. 
*/
#define LIN_MASTER_MODE_USED                                   [!IF "node:exists(LinGlobalConfig/LinChannel/*[LinNodeType = 'MASTER'])"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]

/* 
Whether there is hardware 
as a master mode. 
*/
#define LIN_SLAVE_MODE_USED                                    [!IF "node:exists(LinGlobalConfig/LinChannel/*[LinNodeType = 'SLAVE'])"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: LIN_MAX_CHANNEL_TO_COREx
 Defines the total number of channels mapped to Corex.
*/
[!INDENT "0"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!CALL "CG_GetVauleInStringDictByKey", "StringDict" = "$G_LinChannelMappedCoreIdDict", "Key" = "$CoreIndex"!][!//
    [!VAR "LinMaxChannelToCoreX" = "$CG_GetVauleInStringDictByKey_ReturnObject"!][!//
    #define LIN_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!] [!WS "30"!]([!"$LinMaxChannelToCoreX"!]U)
[!ENDFOR!][!//
[!ENDINDENT!][!//
/*
Macro definition: LIN Channel name
 Generate the macro definition for LIN Channel name.
*/
[!CALL "CG_GeneLinChannelIdMacro"!]

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

#endif /* _LIN_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Mcu_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Rcc,PWRC
*
*   brief                 : This file contains all configuration declarations of Mcu Driver
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
*#Mcu_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.  
*/
#ifndef MCU_CFG_H_
#define MCU_CFG_H_
[!NOCODE!][!//
[!INCLUDE "Mcu.m"!][!//
[!ENDNOCODE!][!//
/****************************************************************************************************
*                               Include Section
****************************************************************************************************/
/****************************************************************************************************
*                               Resource used
****************************************************************************************************/
#define MCU_INSTANCE_ID_VALUE                                     (0U)
/* ECUC_Mcu_00172 Total number of RAM sector configured */
#define MCU_NUM_RAM_SECTORS                                       ([!"num:i(count(McuModuleConfiguration/McuRamSectorSettingConf/*))"!]U)
/* Total number of Clock Setting configured */
#define MCU_NUM_CLOCK_SETTING                                     ([!"num:i(count(McuModuleConfiguration/McuClockSettingConfig/*))"!]U)
/* ECUC_Mcu_00171 Total number of Power Mode configured */
/* \[SWS_Mcu_00165]
 * be configured in the configuration set of the MCU module */
/* #Violation: Mcu_Cfg_h_REF_1*/
#define MCU_NUM_MODE_CONFIG                                       ([!"num:i(count(McuModuleConfiguration/McuModeSettingConf/*))"!]U)
/* The number of basetimer source */
#define MCU_NUM_BASETIMER                                         ([!"num:i(ecu:get('Basetimer.MaxHwUnit'))"!]U)
#define MCU_RESET_CONFIG_NUM                                      (7U)
/****************************************************************************************************
*                               API  Enable/Disable
****************************************************************************************************/
/* Required variables */
/* ECUC_Mcu_00166 */
#define MCU_DEV_ERROR_DETECT   [!WS "38"!][!IF "McuGeneralConfiguration/McuDevErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
#define MCU_DEV_RUNTIME_ERROR_DETECT                                 (STD_ON)
#define MCU_SAFETY_ENABLE                                            ([!//
[!IF "McuGeneralConfiguration/McuSafetyErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* ECUC_Mcu_00181 */
#define MCU_GET_RAM_STATE_API  [!WS "38"!][!IF "McuGeneralConfiguration/McuGetRamStateApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
#define MCU_CLR_COLD_RESET_STAT_API  [!WS "32"!][!IF "McuGeneralConfiguration/McuClearColdResetStatusApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* ECUC_Mcu_00168 */
#define MCU_VERSION_INFO_API   [!WS "38"!][!IF "McuGeneralConfiguration/McuVersionInfoApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* ECUC_Mcu_00167 */
#define MCU_PERFORM_RESET_API  [!WS "38"!][!IF "McuGeneralConfiguration/McuPerformResetApi = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]


/* ECUC_Mcu_00182 */
#define MCU_INIT_CLOCK         [!WS "38"!][!IF "McuGeneralConfiguration/McuInitClock = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

/* ECUC_Mcu_00180 */
#define MCU_NO_PLL             [!WS "38"!][!IF "McuGeneralConfiguration/McuNoPll = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]

#define MCU_RSTSOURCE_TIMEOUT_VALUE   [!WS "33"!][!//
[!IF "node:exists(McuModuleConfiguration/McuResetTimeoutCnt)"!][!//
([!"McuModuleConfiguration/McuResetTimeoutCnt"!]U)[!//
[!ELSE!][!//
(400U)
[!ENDIF!][!//
#define MCU_CONFIG_COUNT                                             (1U)
[!IF "node:exists(McuModuleConfiguration/McuDemEventParameterRefs/MCU_E_CLOCK_FAILURE)"!][!//
    [!IF "node:refvalid(McuModuleConfiguration/McuDemEventParameterRefs/MCU_E_CLOCK_FAILURE)"!]
#define MCU_DEM_REPORT_ERROR_STATUS                                  (STD_ON)
#define MCU_E_CLOCK_FAILURE                                          ((Dem_EventIdType)DemConf_DemEventParameter_[!"node:name(node:ref(McuModuleConfiguration/McuDemEventParameterRefs/MCU_E_CLOCK_FAILURE))"!])
    [!ELSE!][!//
        [!ERROR "Invalid reference for MCU_E_CLOCK_FAILURE"!][!//
    [!ENDIF!][!//
[!ELSE!][!//
#define MCU_DEM_REPORT_ERROR_STATUS                                  (STD_OFF)
[!ENDIF!][!//

[!VAR "ModulePath" = "'McuModuleConfiguration'"!][!//
[!VAR "ModeSettingConfig" = "num:i(count(node:ref($ModulePath)/McuModeSettingConf/*))"!]
[!FOR "ModeIndex" = "num:i(0)" TO "($ModeSettingConfig - num:i(1))"!][!//
  [!VAR "SymbolicName" = "concat('McuConf_McuModeSettingConf_',node:name(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]))"!]
#ifndef [!"$SymbolicName"!]
#define [!"$SymbolicName"!]              ([!"num:i(node:ref($ModulePath)/McuModeSettingConf/*[$ModeIndex+1]/McuMode)"!]U)
#endif
[!ENDFOR!][!//
/* Clock Setting ID */
[!VAR "ClockSettingConfig" = "num:i(count(node:ref($ModulePath)/McuClockSettingConfig/*))"!][!//
[!FOR "ClockIndex" = "num:i(0)" TO "($ClockSettingConfig - num:i(1))"!][!//
  [!VAR "SymbolicName" = "concat('McuConf_McuClockSettingConfig_',node:name(node:ref($ModulePath)/McuClockSettingConfig/*[McuClockSettingId = num:i($ClockIndex)]))"!]
#ifndef [!"$SymbolicName"!]
  #define [!"$SymbolicName"!]      ([!"num:i(node:ref($ModulePath)/McuClockSettingConfig/*[McuClockSettingId = num:i($ClockIndex)]/McuClockSettingId)"!]U)
#endif
[!ENDFOR!][!//
/* Ram Section Config ID */
[!VAR "RamSectorSettingConfig" = "num:i(count(node:ref($ModulePath)/McuRamSectorSettingConf/*))"!][!//
[!IF "$RamSectorSettingConfig > num:i(0)"!][!//
  [!FOR "RAMSectionIndex" = "num:i(0)" TO "($RamSectorSettingConfig - num:i(1))"!][!//
  [!VAR "SymbolicName" = "concat('McuConf_McuRamSectorSettingConf_',node:name(node:ref($ModulePath)/McuRamSectorSettingConf/*[$RAMSectionIndex+1]))"!]
#ifndef [!"$SymbolicName"!]
  #define [!"$SymbolicName"!]                        ([!"num:i($RAMSectionIndex)"!]U)
#endif
  [!ENDFOR!][!//
[!ENDIF!][!//

/* ResetReason Config */
[!VAR "LoopCounter" = "'McuPublishedInformation/McuResetReasonConf'"!][!//
[!LOOP "node:ref($LoopCounter)/*"!][!//
[!NOCODE!][!//
    [!VAR "SymbolicName" = "concat('McuConf_McuResetReasonConf_',node:name(.))"!]
[!ENDNOCODE!][!//
#ifndef [!"$SymbolicName"!]
  #define [!"$SymbolicName"!]  ([!"num:i(./McuResetReason)"!]U)
#endif
[!ENDLOOP!][!//
/****************************************************************************************************
*                               Function Prototypes
****************************************************************************************************/
/****************************************************************************************************
*                               Version Information
****************************************************************************************************/
#define MCU_CFG_VENDOR_ID                                             ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define MCU_CFG_MODULE_ID                                             ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)
#define MCU_CFG_AR_RELEASE_MAJOR_VERSION                              ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define MCU_CFG_AR_RELEASE_MINOR_VERSION                              ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define MCU_CFG_AR_RELEASE_REVISION_VERSION                           ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)
#define MCU_CFG_SW_MAJOR_VERSION                                      ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define MCU_CFG_SW_MINOR_VERSION                                      ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
/* #Violation: Mcu_Cfg_h_REF_1*/
#define MCU_CFG_SW_PATCH_VERSION                                      ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#endif /* \#ifndef MCU_CFG_H_ */

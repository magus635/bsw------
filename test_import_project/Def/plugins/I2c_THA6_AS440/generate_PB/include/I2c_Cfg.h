/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : I2c_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : I2C
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
*#I2c_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*/

/***************************************************************************************************/
[!NOCODE!][!//
[!INCLUDE "I2c.m"!][!//
[!ENDNOCODE!][!//
/***************************************************************************************************/
#ifndef I2C_CFG_H_
#define I2C_CFG_H_


/****************************************************************************************************
*                            Global Macro Definitions
****************************************************************************************************/
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define I2C_CFG_AR_RELEASE_MAJOR_VERSION                       ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define I2C_CFG_AR_RELEASE_MINOR_VERSION                       ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define I2C_CFG_AR_RELEASE_REVISION_VERSION                    ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define I2C_CFG_SW_MAJOR_VERSION                               ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define I2C_CFG_SW_MINOR_VERSION                               ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define I2C_CFG_SW_PATCH_VERSION                               ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define I2C_CFG_VENDOR_ID                                      ([!"num:i(CommonPublishedInformation/VendorId)"!]U)/*([!"text:toupper(num:inttohex(CommonPublishedInformation/VendorId))"!])*/
#define I2C_CFG_MODULE_ID                                      ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)/*([!"text:toupper(num:inttohex(CommonPublishedInformation/ModuleId))"!])*/
/*
Configuration: I2C_DEV_ERROR_DETECT  
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define I2C_DEV_ERROR_DETECT                                   [!IF "I2cGeneral/I2cDevErrorDetect = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: I2C_CFG_DEINIT_API  
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define I2C_CFG_DEINIT_API                                   [!IF "I2cGeneral/I2cDeInitApi = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: I2C_VERSION_INFO_API  
- if Selected, Function I2c_GetVersionInfo is Enabled
- if Deselected, Function I2c_GetVersionInfo is Enabled
*/
#define I2C_VERSION_INFO_API                                   [!IF "I2cGeneral/I2cVersionInfoApi = 'true'"!](STD_ON) [!ELSE!](STD_OFF)[!ENDIF!]

/*
Configuration: I2C_TIMEOUT_DURATION
 Specifies duration of I2C channel timeout.
*/
#define I2C_TIMEOUT_DURATION                                   ([!"num:i(I2cGeneral/I2cTimeoutDuration)"!]U)

/*
Configuration: I2C_INDEX
 Specifies index number of I2C channel.
*/
/* #Violation: I2c_Cfg_h_REF_1 */
#define I2C_INSTANCE_INDEX                                              ([!"num:i(I2cGeneral/I2cIndex)"!]U)

/*
Configuration: I2C_CONFIG_COUNT
 Defines the total number of I2C Config infomation.
*/
#define I2C_CONFIG_COUNT                                       (1U)

/*
Configuration: I2C_MAX_HWUNIT_COUNT
 Defines the total number of I2C HwUnit.
*/
#define I2C_MAX_HWUNIT_COUNT                                   ([!"num:i(ecu:get('I2c.NumofAvailableI2c'))"!]U)

/*
Configuration: I2C_TOTAL_CFG_CHANNEL_NUM
 Define the total number of I2C configuration.
*/
#define I2C_TOTAL_CFG_CHANNEL_NUM                              ([!"num:i(count(I2cGlobalConfig/I2cChannel/*))"!]U)

/*
Configuration: I2C_MAX_CHANNEL_TO_COREx
 Defines the total number of channels mapped to Corex.
*/
[!INDENT "0"!][!//
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "I2cChannelNumCorex" = "num:i(substring-after(text:split($I2cChannelTotalNumCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
    #define I2C_MAX_CHANNEL_TO_CORE[!"$CoreIndex"!]    [!WS "15"!]([!"$I2cChannelNumCorex"!]U)
[!ENDFOR!][!//
[!ENDINDENT!][!//

/*
Macro definition: I2C Channel name
 Generate the macro definition for I2C Channel name.
*/
[!CALL "CG_GeneI2cChannelIdMacro"!]
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

#endif /* _I2C_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

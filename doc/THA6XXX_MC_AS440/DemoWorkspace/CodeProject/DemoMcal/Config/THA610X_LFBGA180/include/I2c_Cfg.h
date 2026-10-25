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
/***************************************************************************************************/
#ifndef I2C_CFG_H_
#define I2C_CFG_H_


/****************************************************************************************************
*                            Global Macro Definitions
****************************************************************************************************/
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define I2C_CFG_AR_RELEASE_MAJOR_VERSION                       (4U)
#define I2C_CFG_AR_RELEASE_MINOR_VERSION                       (4U)
#define I2C_CFG_AR_RELEASE_REVISION_VERSION                    (0U)

#define I2C_CFG_SW_MAJOR_VERSION                               (1U)
#define I2C_CFG_SW_MINOR_VERSION                               (2U)
#define I2C_CFG_SW_PATCH_VERSION                               (0U)

#define I2C_CFG_VENDOR_ID                                      (175U)/*(0XAF)*/
#define I2C_CFG_MODULE_ID                                      (255U)/*(0XFF)*/
/*
Configuration: I2C_DEV_ERROR_DETECT  
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define I2C_DEV_ERROR_DETECT                                   (STD_ON) 

/*
Configuration: I2C_CFG_DEINIT_API  
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define I2C_CFG_DEINIT_API                                   (STD_ON) 

/*
Configuration: I2C_VERSION_INFO_API  
- if Selected, Function I2c_GetVersionInfo is Enabled
- if Deselected, Function I2c_GetVersionInfo is Enabled
*/
#define I2C_VERSION_INFO_API                                   (STD_ON) 

/*
Configuration: I2C_TIMEOUT_DURATION
 Specifies duration of I2C channel timeout.
*/
#define I2C_TIMEOUT_DURATION                                   (100000U)

/*
Configuration: I2C_INDEX
 Specifies index number of I2C channel.
*/
/* #Violation: I2c_Cfg_h_REF_1 */
#define I2C_INSTANCE_INDEX                                              (0U)

/*
Configuration: I2C_CONFIG_COUNT
 Defines the total number of I2C Config infomation.
*/
#define I2C_CONFIG_COUNT                                       (1U)

/*
Configuration: I2C_MAX_HWUNIT_COUNT
 Defines the total number of I2C HwUnit.
*/
#define I2C_MAX_HWUNIT_COUNT                                   (2U)

/*
Configuration: I2C_TOTAL_CFG_CHANNEL_NUM
 Define the total number of I2C configuration.
*/
#define I2C_TOTAL_CFG_CHANNEL_NUM                              (1U)

/*
Configuration: I2C_MAX_CHANNEL_TO_COREx
 Defines the total number of channels mapped to Corex.
*/
#define I2C_MAX_CHANNEL_TO_CORE0                   (1U)
#define I2C_MAX_CHANNEL_TO_CORE1                   (0U)

/*
Macro definition: I2C Channel name
 Generate the macro definition for I2C Channel name.
*/
#ifndef I2cConf_I2cChannel_I2cChannel_0
/* I2C Channel ID 0 -> I2cChannel_0, mapped to I2C0 in Core0 */
#define I2cConf_I2cChannel_I2cChannel_0                               (0U)
#define I2C_HWUNIT_CHANNEL0
#endif

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

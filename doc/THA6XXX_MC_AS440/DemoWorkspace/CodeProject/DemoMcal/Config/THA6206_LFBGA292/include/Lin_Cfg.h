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
/***************************************************************************************************/
#ifndef LIN_CFG_H_
#define LIN_CFG_H_

/****************************************************************************************************
*                            Global Macro Definitions
****************************************************************************************************/
/***************************************************************************************************
*                               Version Information
***************************************************************************************************/
#define LIN_CFG_AR_RELEASE_MAJOR_VERSION                       (4U)
#define LIN_CFG_AR_RELEASE_MINOR_VERSION                       (4U)
#define LIN_CFG_AR_RELEASE_REVISION_VERSION                    (0U)

#define LIN_CFG_SW_MAJOR_VERSION                               (1U)
#define LIN_CFG_SW_MINOR_VERSION                               (2U)
#define LIN_CFG_SW_PATCH_VERSION                               (0U)

#define LIN_CFG_VENDOR_ID                                      (175U)/*(0XAF)*/
#define LIN_CFG_MODULE_ID                                      (82U)/*(0X52)*/
/*
Configuration: LIN_DEV_ERROR_DETECT  
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define LIN_DEV_ERROR_DETECT                                   (STD_ON) 

/*
Configuration: LIN_VERSION_INFO_API  
- if Selected, Function Lin_GetVersionInfo is Enabled
- if Deselected, Function Lin_GetVersionInfo is Enabled
*/
#define LIN_VERSION_INFO_API                                   (STD_ON) 

/*
Configuration: LIN_CFG_INTERRUPT_ENABLE  
- if Selected, Lin Channels working in interrupt mode
- if Deselected, Lin Channels working in non-interrupt mode
*/
#define LIN_CFG_INTERRUPT_ENABLE                               (STD_ON) 

/*
Configuration: LIN_DEM_ERROR_REPORT_STATUS
 Specifies whether report LIN_E_TIMEOUT.
*/
#define LIN_DEM_ERROR_REPORT_STATUS                            (STD_OFF)

/*
Macro definition: LINIF_WAKEUP_SUPPORT
 Generate the macro definition LinIf_WakeupConfirmation function is available.
*/
#define LIN_WAKEUP_SUPPORT                                   (STD_OFF)


/*
Configuration: LIN_TIMEOUT_DURATION
 Specifies duration of LIN channel timeout.
*/
#define LIN_TIMEOUT_DURATION                                   (1000U)

/*
Configuration: LIN_INDEX
 Specifies index number of LIN channel.
*/
/* #Violation: Lin_Cfg_h_REF_1 */
#define LIN_INDEX                                              (0U)

/*
Configuration: LIN_CONFIG_COUNT
 Defines the total number of LIN Config infomation.
*/
#define LIN_CONFIG_COUNT                                       (1U)

/*
Configuration: LIN_MAX_HWUNIT_COUNT
 Defines the total number of LIN HwUnit.
*/
#define LIN_MAX_HWUNIT_COUNT                                   (8U)

/*
Configuration: LIN_TOTAL_CFG_CHANNEL_NUM
 Define the total number of LIN channels.
*/
#define LIN_TOTAL_CFG_CHANNEL_NUM                              (3U)

/* 
Whether there is hardware 
as a master mode. 
*/
#define LIN_MASTER_MODE_USED                                   (STD_ON) 

/* 
Whether there is hardware 
as a master mode. 
*/
#define LIN_SLAVE_MODE_USED                                    (STD_ON) 

/*
Configuration: LIN_MAX_CHANNEL_TO_COREx
 Defines the total number of channels mapped to Corex.
*/
#define LIN_MAX_CHANNEL_TO_CORE0                               (2U)
#define LIN_MAX_CHANNEL_TO_CORE1                               (1U)
/*
Macro definition: LIN Channel name
 Generate the macro definition for LIN Channel name.
*/
#ifndef LinConf_LinChannel_Lin_TestChannel_0
/* LIN Channel ID 0 -> Lin_TestChannel_0, mapped to ASI2 in Core0 */
#define LinConf_LinChannel_Lin_TestChannel_0                               (0U)
#define LIN_HWUNIT_CHANNEL2
#endif
#ifndef LinConf_LinChannel_Lin_TestChannel_1
/* LIN Channel ID 1 -> Lin_TestChannel_1, mapped to ASI3 in Core1 */
#define LinConf_LinChannel_Lin_TestChannel_1                               (1U)
#define LIN_HWUNIT_CHANNEL3
#endif
#ifndef LinConf_LinChannel_Lin_TestSlaveChannel_0
/* LIN Channel ID 2 -> Lin_TestSlaveChannel_0, mapped to ASI5 in Core0 */
#define LinConf_LinChannel_Lin_TestSlaveChannel_0                               (2U)
#define LIN_HWUNIT_CHANNEL5
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

#endif /* _LIN_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

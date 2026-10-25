/****************************************************************************************************
*   FileName              : Ocu_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GTM-ATOM
*
*   brief                 : This file contains all configuration declarations of OCU Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Codeing Rule Violations                                                **
****************************************************************************************************/
/*
*#Violation Summary
*#Ocu_Cfg_h_REF_1:MISRAC2012-Rule-2.5; 
* Justification: The macros are reserved for upper layers.
*
*/
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/

#ifndef OCU_CFG_H
#define OCU_CFG_H

/****************************************************************************************************
**                                  Version Information                                            **
*****************************************************************************************************/
/* AUTOSAR release version information */
#define OCU_CFG_AR_RELEASE_MAJOR_VERSION                             (4U)
#define OCU_CFG_AR_RELEASE_MINOR_VERSION                             (4U)
#define OCU_CFG_AR_RELEASE_REVISION_VERSION                          (0U)
/* OCU module release version information */
#define OCU_CFG_SW_MAJOR_VERSION                                     (1U)
#define OCU_CFG_SW_MINOR_VERSION                                     (2U)
#define OCU_CFG_SW_PATCH_VERSION                                     (0U)
/* Vendor ID */
#define OCU_CFG_VENDOR_ID                                            (175U)
/* Module ID */
#define OCU_CFG_MODULE_ID                                            (125U)

/****************************************************************************************************
**                                   API Information                                               **
****************************************************************************************************/
/*
Configuration: OCU_DE_INIT_API
Adds/removes Ocu_DeInit API 
from the code 
- if STD_ON, Ocu_DeInit is enabled
- if STD_OFF, Ocu_DeInit is disabled
*/
#define OCU_DE_INIT_API                                              (STD_ON)
/*
Configuration: OCU_SET_PIN_ACTION_API
Adds/removes Set Pin Action API from the code 
- if STD_ON, Ocu_SetPinAction is enabled
- if STD_OFF, Ocu_SetPinAction is disabled
*/
#define OCU_SET_PIN_ACTION_API                                       (STD_ON)
/*
Configuration: OCU_SET_PIN_STATE_API
Adds/removes Set Pin State API from the code 
- if STD_ON, Ocu_SetPinState is enabled
- if STD_OFF, Ocu_SetPinState is disabled
*/
#define OCU_SET_PIN_STATE_API                                        (STD_ON)
/*
Configuration: OCU_GET_COUNTER_API
Adds/removes Get Counter API from the code 
- if STD_ON, Ocu_GetCounter is enabled
- if STD_OFF, Ocu_GetCounter is disabled
*/
#define OCU_GET_COUNTER_API                                          (STD_ON)
/*
Configuration: OCU_SET_ABSOLUTE_THRESHOLD_API
Adds/removes Set Absolute Threshold API from the code 
- if STD_ON, Ocu_SetAbsoluteThreshold is enabled
- if STD_OFF, Ocu_SetAbsoluteThreshold is disabled
*/
#define OCU_SET_ABSOLUTE_THRESHOLD_API                               (STD_ON)
/*
Configuration: OCU_SET_RELATIVE_THRESHOLD_API
Adds/removes Set Relative Threshold API from the code 
- if STD_ON, Ocu_SetRelativeThreshold is enabled
- if STD_OFF, Ocu_SetRelativeThreshold is disabled
*/
#define OCU_SET_RELATIVE_THRESHOLD_API                               (STD_ON)
/*
Configuration: OCU_VERSION_INFO_API
Adds/removes Get Version Info API from the code 
- if STD_ON, Ocu_GetVersionInfo is enabled
- if STD_OFF, Ocu_GetVersionInfo is disabled
*/
#define OCU_VERSION_INFO_API                                         (STD_ON)

/****************************************************************************************************
**                          Ocu Channel Symbolic Names                                             **
****************************************************************************************************/
/* Ocu Channel ID Macro for Channel Configuration. */
#ifndef OcuConf_OcuChannel_OcuChannel_0
#define OcuConf_OcuChannel_OcuChannel_0  \
((Ocu_ChannelType)0U)
#endif

#ifndef OcuConf_OcuChannel_OcuChannel_1
#define OcuConf_OcuChannel_OcuChannel_1  \
((Ocu_ChannelType)1U)
#endif


/****************************************************************************************************
**                          Function features control                                              **
****************************************************************************************************/
/* Notification supported */
#define OCU_NOTIFICATION_SUPPORTED                                   (STD_ON)
/* Development error detect */
#define OCU_DEV_ERROR_DETECT                                         (STD_ON)
/* Safty enable */
#define OCU_SAFETY_ENABLE                                            (STD_ON)
/* Ocu runtime error detect */
/* #Violation: Ocu_Cfg_h_REF_1 */
#define OCU_RUNTIME_ERROR_DETECT                                     (STD_ON)
/* OCU channel mapped to Core0 */
#define OCU_MAX_CHANNEL_TO_CORE0                                     (2U)
/* OCU channel mapped to Core1 */
#define OCU_MAX_CHANNEL_TO_CORE1                                     (0U)
/* OCU channel mapped to Core2 */
#define OCU_MAX_CHANNEL_TO_CORE2                                     (0U)
/* OCU channel mapped to Core3 */
#define OCU_MAX_CHANNEL_TO_CORE3                                     (0U)
/* The number of all OCU channel */
#define OCU_MAX_CHANNELS                                             (2U)
/* The maximum id of OCU channel */
/* #Violation: Ocu_Cfg_h_REF_1 */
#define OCU_MAX_CHANNEL_ID                                           (1U)

#endif  /* OCU_CFG_H */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


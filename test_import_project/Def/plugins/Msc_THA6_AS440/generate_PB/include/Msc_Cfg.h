/****************************************************************************************************
*   FileName              : Msc_Cfg.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MSC
*
*   brief                 : This file contains all post-build parameters of msc.
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx 
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#ifndef MSC_CFG_H_
#define MSC_CFG_H_

[!NOCODE!][!//
[!INCLUDE "Msc.m"!][!//
[!ENDNOCODE!][!//
/****************************************************************************************************
**                          Version Information                                               **
****************************************************************************************************/
[!AUTOSPACING!]
/* AUTOSAR release version information */
#define MSC_CFG_AR_RELEASE_MAJOR_VERSION                             ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define MSC_CFG_AR_RELEASE_MINOR_VERSION                             ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define MSC_CFG_AR_RELEASE_REVISION_VERSION                          ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion  )"!]U)
/* MSC module software release version information */
#define MSC_CFG_SW_MAJOR_VERSION                                     ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define MSC_CFG_SW_MINOR_VERSION                                     ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define MSC_CFG_SW_PATCH_VERSION                                     ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define MSC_CFG_VENDOR_ID                                            ([!"num:i(CommonPublishedInformation/VendorId)"!]U)
#define MSC_CFG_MODULE_ID                                            ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)
/****************************************************************************************************
**                          API Add/Remove Information                                             **
****************************************************************************************************/
/*
Configuration: MSC_VERSION_INFO_API
Adds/removes the service Msc_GetVersionInfo() from the code
- if STD_ON, Msc_GetVersionInfo() can be used
- if STD_OFF, Msc_GetVersionInfo() can not be used
*/
#define MSC_VERSION_INFO_API                                         ([!//
[!IF "MscConfigurationOfOptApiServices/MscGetVersionInfo = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: MSC_DEINIT_API
Adds/removes the service Msc_DeInit() from the code
- if STD_ON, Msc_DeInit() can be used
- if STD_OFF, Msc_DeInit() can not be used
*/
#define MSC_DEINIT_API                                               ([!//
[!IF "MscConfigurationOfOptApiServices/MscDeInitApi  = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: MSC_GET_RX_DATA_API
Adds/removes the service Msc_GetRxData() from the code
- if STD_ON, Msc_GetRxData() can be used
- if STD_OFF, Msc_GetRxData() can not be used
*/
#define MSC_GET_RX_DATA_API                                          ([!//
[!IF "MscConfigurationOfOptApiServices/Msc_GetRxDataApi          = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: MSC_GET_TX_STATUS_API
Adds/removes the service Msc_GetTxStatus() from the code
- if STD_ON, Msc_GetTxStatus() can be used
- if STD_OFF, Msc_GetTxStatus() can not be used
*/
#define MSC_GET_TX_STATUS_API                                        ([!//
[!IF "MscConfigurationOfOptApiServices/MscGetTxStatusApi          = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: MSC_SELECT_RX_DEVICE_API
Adds/removes the service Msc_SelectRxDevice() from the code
- if STD_ON, Msc_SelectRxDevice() can be used
- if STD_OFF, Msc_SelectRxDevice() can not be used
*/
#define MSC_SELECT_RX_DEVICE_API                                     ([!//
[!IF "MscConfigurationOfOptApiServices/MscSelectRxDeviceApi       = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: MSC_TX_DATA_FRAME_API
Adds/removes the service Msc_TxDataFrame() from the code
- if STD_ON, Msc_TxDataFrame() can be used
- if STD_OFF, Msc_TxDataFrame() can not be used
*/
#define MSC_TX_DATA_FRAME_API                                        ([!//
[!IF "MscConfigurationOfOptApiServices/MscTxDataFrameApi         = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: MSC_CHANGE_TX_STATUS_API
Adds/removes the service Msc_ChangeTxState() from the code
- if STD_ON, Msc_ChangeTxState() can be used
- if STD_OFF, Msc_ChangeTxState() can not be used
*/
#define MSC_CHANGE_TX_STATUS_API                                     ([!//
[!IF "MscConfigurationOfOptApiServices/MscChangeTxStateApi       = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: MSC_CHANGE_RX_STATUS_API
Adds/removes the service Msc_ChangeRxState() from the code
- if STD_ON, Msc_ChangeRxState() can be used
- if STD_OFF, Msc_ChangeRxState() can not be used
*/
#define MSC_CHANGE_RX_STATUS_API                                     ([!//
[!IF "MscConfigurationOfOptApiServices/MscChangeRxStateApi       = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: MSC_START_RX_TIMEOUT_API
Adds/removes the service Msc_StartRxTimeout() from the code
- if STD_ON, Msc_StartRxTimeout() can be used
- if STD_OFF, Msc_StartRxTimeout() can not be used
*/
#define MSC_START_RX_TIMEOUT_API                                     ([!//
[!IF "MscConfigurationOfOptApiServices/Msc_StartRxTimeoutAPI = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)
/*
Configuration: MSC_GET_RX_TIMEOUT_STATUS_API
Adds/removes the service Msc_GetRxTimeoutStatus() from the code
- if STD_ON, Msc_GetRxTimeoutStatus() can be used
- if STD_OFF, Msc_GetRxTimeoutStatus() can not be used
*/
#define MSC_GET_RX_TIMEOUT_STATUS_API                                ([!//
[!IF "MscConfigurationOfOptApiServices/Msc_StartRxTimeoutAPI = 'true' and MscConfigurationOfOptApiServices/MscGetRxTimeoutStatusApi = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/****************************************************************************************************
**                          Function features control                                              **
****************************************************************************************************/
/* Development error trace */
#define MSC_DEV_ERROR_DETECT                                         ([!//
[!IF "MscDriverConfiguration/MscDevErrorDetect = 'true'"!][!//
STD_ON[!//
[!ELSE!][!//
STD_OFF[!//
[!ENDIF!][!//
)

/* The number of Msc instances are allocated in core0 */
#define MSC_MAX_CHANNEL_TO_CORE0                                     ([!"num:i($MscChannelMappedCore0)"!]U)
/* The number of Msc instances are allocated in core1 */
#define MSC_MAX_CHANNEL_TO_CORE1                                     ([!"num:i($MscChannelMappedCore1)"!]U)
/* The number of Msc instances are allocated in core2 */
#define MSC_MAX_CHANNEL_TO_CORE2                                     ([!"num:i($MscChannelMappedCore2)"!]U)
/* The number of Msc instances are allocated in core3 */
#define MSC_MAX_CHANNEL_TO_CORE3                                     ([!"num:i($MscChannelMappedCore3)"!]U)
/* The number of Msc instances are used */
#define MSC_TOTAL_CHANNEL_NUMBER                                     ([!"num:i($MscChannelMappedCore0 + $MscChannelMappedCore1 + $MscChannelMappedCore2 + $MscChannelMappedCore3)"!]U)


/*******************************************************************************
**                          Msc Channel Symbolic Names                        **
*******************************************************************************/
/* Msc Channel ID Enumerations for Channel Configuration. */
[!VAR "ChanId" = "num:i(0)"!][!//
[!LOOP "node:order(/AUTOSAR/TOP-LEVEL-PACKAGES/Msc/ELEMENTS/Msc/MscConfigSet/MscModuleConfiguration/*, 'MscHWUnitMapping')"!][!//
#ifndef MscConf_MscChannelConfiguration_[!"@name"!]
#define MscConf_MscChannelConfiguration_[!"@name"!]  \
((Msc_ModuleType)[!"$ChanId"!]U)
#endif
[!VAR "ChanId" = "$ChanId + num:i(1)"!][!//

[!ENDLOOP!][!//  

#endif /* MSC_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

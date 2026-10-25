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

/****************************************************************************************************
**                          Version Information                                               **
****************************************************************************************************/
/* AUTOSAR release version information */
#define MSC_CFG_AR_RELEASE_MAJOR_VERSION                             (4U)
#define MSC_CFG_AR_RELEASE_MINOR_VERSION                             (4U)
#define MSC_CFG_AR_RELEASE_REVISION_VERSION                          (0U)
/* MSC module software release version information */
#define MSC_CFG_SW_MAJOR_VERSION                                     (1U)
#define MSC_CFG_SW_MINOR_VERSION                                     (2U)
#define MSC_CFG_SW_PATCH_VERSION                                     (0U)

#define MSC_CFG_VENDOR_ID                                            (175U)
#define MSC_CFG_MODULE_ID                                            (255U)
/****************************************************************************************************
**                          API Add/Remove Information                                             **
****************************************************************************************************/
/*
Configuration: MSC_VERSION_INFO_API
Adds/removes the service Msc_GetVersionInfo() from the code
- if STD_ON, Msc_GetVersionInfo() can be used
- if STD_OFF, Msc_GetVersionInfo() can not be used
*/
#define MSC_VERSION_INFO_API                                         (STD_ON)
/*
Configuration: MSC_DEINIT_API
Adds/removes the service Msc_DeInit() from the code
- if STD_ON, Msc_DeInit() can be used
- if STD_OFF, Msc_DeInit() can not be used
*/
#define MSC_DEINIT_API                                               (STD_ON)
/*
Configuration: MSC_GET_RX_DATA_API
Adds/removes the service Msc_GetRxData() from the code
- if STD_ON, Msc_GetRxData() can be used
- if STD_OFF, Msc_GetRxData() can not be used
*/
#define MSC_GET_RX_DATA_API                                          (STD_ON)
/*
Configuration: MSC_GET_TX_STATUS_API
Adds/removes the service Msc_GetTxStatus() from the code
- if STD_ON, Msc_GetTxStatus() can be used
- if STD_OFF, Msc_GetTxStatus() can not be used
*/
#define MSC_GET_TX_STATUS_API                                        (STD_ON)
/*
Configuration: MSC_SELECT_RX_DEVICE_API
Adds/removes the service Msc_SelectRxDevice() from the code
- if STD_ON, Msc_SelectRxDevice() can be used
- if STD_OFF, Msc_SelectRxDevice() can not be used
*/
#define MSC_SELECT_RX_DEVICE_API                                     (STD_ON)
/*
Configuration: MSC_TX_DATA_FRAME_API
Adds/removes the service Msc_TxDataFrame() from the code
- if STD_ON, Msc_TxDataFrame() can be used
- if STD_OFF, Msc_TxDataFrame() can not be used
*/
#define MSC_TX_DATA_FRAME_API                                        (STD_ON)
/*
Configuration: MSC_CHANGE_TX_STATUS_API
Adds/removes the service Msc_ChangeTxState() from the code
- if STD_ON, Msc_ChangeTxState() can be used
- if STD_OFF, Msc_ChangeTxState() can not be used
*/
#define MSC_CHANGE_TX_STATUS_API                                     (STD_ON)
/*
Configuration: MSC_CHANGE_RX_STATUS_API
Adds/removes the service Msc_ChangeRxState() from the code
- if STD_ON, Msc_ChangeRxState() can be used
- if STD_OFF, Msc_ChangeRxState() can not be used
*/
#define MSC_CHANGE_RX_STATUS_API                                     (STD_ON)
/*
Configuration: MSC_START_RX_TIMEOUT_API
Adds/removes the service Msc_StartRxTimeout() from the code
- if STD_ON, Msc_StartRxTimeout() can be used
- if STD_OFF, Msc_StartRxTimeout() can not be used
*/
#define MSC_START_RX_TIMEOUT_API                                     (STD_OFF)
/*
Configuration: MSC_GET_RX_TIMEOUT_STATUS_API
Adds/removes the service Msc_GetRxTimeoutStatus() from the code
- if STD_ON, Msc_GetRxTimeoutStatus() can be used
- if STD_OFF, Msc_GetRxTimeoutStatus() can not be used
*/
#define MSC_GET_RX_TIMEOUT_STATUS_API                                (STD_OFF)

/****************************************************************************************************
**                          Function features control                                              **
****************************************************************************************************/
/* Development error trace */
#define MSC_DEV_ERROR_DETECT                                         (STD_ON)

/* The number of Msc instances are allocated in core0 */
#define MSC_MAX_CHANNEL_TO_CORE0                                     (1U)
/* The number of Msc instances are allocated in core1 */
#define MSC_MAX_CHANNEL_TO_CORE1                                     (0U)
/* The number of Msc instances are allocated in core2 */
#define MSC_MAX_CHANNEL_TO_CORE2                                     (0U)
/* The number of Msc instances are allocated in core3 */
#define MSC_MAX_CHANNEL_TO_CORE3                                     (0U)
/* The number of Msc instances are used */
#define MSC_TOTAL_CHANNEL_NUMBER                                     (1U)


/*******************************************************************************
**                          Msc Channel Symbolic Names                        **
*******************************************************************************/
/* Msc Channel ID Enumerations for Channel Configuration. */
#ifndef MscConf_MscChannelConfiguration_MscModuleConfiguration_0
#define MscConf_MscChannelConfiguration_MscModuleConfiguration_0  \
((Msc_ModuleType)0U)
#endif


#endif /* MSC_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

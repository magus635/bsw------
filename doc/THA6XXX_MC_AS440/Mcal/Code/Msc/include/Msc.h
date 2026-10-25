/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Msc.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : MSC
*
*   brief                 : This file contains all function declarations of Msc Driver
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
*
*#Msc_h_REF_1:MISRAC2012-Rule-20.7; 
* Justification: Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*/

#ifndef MCAL_MSC_H_
#define MCAL_MSC_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Std_Types.h"
#include "Msc_GeneralTypes.h"
#include "Msc_Version.h"
#include "Msc_PBcfg.h"

/*****************************************************************************************************
**                      Global Variables
*****************************************************************************************************/


/****************************************************************************************************
**                          Global Macro Definitions                                              **
****************************************************************************************************/

/****************************Service ID****************************/
/* Service Id of Msc_Init */
#define MSC_INIT_SID                                   (0x00U)
/* Service Id of Msc_DeInit */
#define MSC_DEINIT_SID                                 (0x01U)
/* Service Id of Msc_ChangeTxStatus */
#define MSC_CHANGETXSTATUS_SID                         (0x02U)
/* Service Id of Msc_GetTxStatus */
#define MSC_GETTXSTATUS_SID                            (0x03U)
/* Service Id of Msc_TxCmdFrame */
#define MSC_TXCMDFRAME_SID                             (0x04U)
/* Service Id of Msc_TxDataFrame */
#define MSC_TXDATAFRAME_SID                            (0x05U)
/* Service Id of Msc_GetRxData */
#define MSC_GETRXDATA_SID                              (0x06U)
/* Service Id of Msc_SelectRxDevice */
#define MSC_SELRXDEVICE_SID                            (0x07U)
#if (MSC_START_RX_TIMEOUT_API == STD_ON)
/* Service Id of Msc_StartRxTimeout */
#define MSC_STARTRXTIMEOUT_SID                         (0x08U)
#endif /* MSC_START_RX_TIMEOUT_API \== STD_ON */
#if (MSC_GET_RX_TIMEOUT_STATUS_API == STD_ON)
/* Service Id of Msc_GetRxTimeout */
#define MSC_GETRXTIMEOUT_SID                           (0x09U)
#endif /* MSC_GET_RX_TIMEOUT_STATUS_API == STD_ON */
/* Service Id of Msc_GetVersionInfo */
#define MSC_GETVERSIONINFO_SID                         (0x0AU)
/* Service Id of Msc_ChangeRxStatus */
#define MSC_CHANGERXSTATUS_SID                         (0x0BU)
/* Service Id of Msc_EnableNotfication */
#define MSC_ENABLENOTFICATION_SID                      (0x0CU)
/* Service Id of Msc_DisableNotfication */
#define MSC_DISABLENOTFICATION_SID                     (0x0DU)
/* Service Id of Msc_ISRHandler */
#define MSC_ISRHANDLER_SID                             (0x0EU)
/* Service Id of Msc_SelectTxDevice */
#define MSC_SELTXDEVICE_SID                            (0x0FU)
/* Service Id of Msc_SyncTxCmdFrame */
#define MSC_SYNCTXCMDFRAME_SID                         (0x10U)

/****************************DET Error ID***************************/
/* API service called without module initialization */
#define MSC_E_UNINIT                                   (0x01U)
/* Call Msc_ChangeRxState() or Msc_ChangeTxState() with invalid parameter */
#define MSC_E_INVALID_MODE                             (0x02U)
/* Call Msc_GetTxStatus with invalid parameter */
#define MSC_E_INVALID_TXTYPE                           (0x03U)
/* Call Msc_TxCmdFrame or Msc_TxDataFrame with invalid device */
#define MSC_E_INVALID_DEVICE                           (0x04U)
/* Call Msc_GetRxData with invalid data register index */
#define MSC_E_INVALID_RXREGISTER                       (0x05U)
/* Call Msc_SelectRxDevice with invalid receive device */
#define MSC_E_INVALID_RXDEVICE                         (0x06U)
/* Call Msc_GetVersionInfo or Msc_Init with NULL_PTR parameter-in */
#define MSC_E_PARAM_POINTER                            (0x07U)
/* Re-call Msc_Init without calling Msc_DeInit */
#define MSC_E_ALREADY_INITIALIZED                      (0x08U)
/* No Msc channel is not allocated to current core */
#define MSC_E_CORE_NOT_CONFIGURATED                    (0x09U)
/* Call Msc_EnableNotfication but the notification type is already enabled */
#define MSC_E_ALREADY_ENABLED                          (0x0AU)
#if (MSC_START_RX_TIMEOUT_API == STD_ON) || (MSC_GET_RX_TIMEOUT_STATUS_API == STD_ON)
/* Call Msc_StartRxTimeout or Msc_GetRxTimeoutStatus but the timeout feature is not configured */
#define MSC_E_TIMEOUT_NOT_CONFIGURATED                 (0x0BU)
#endif /* \(MSC_START_RX_TIMEOUT_API == STD_ON) || (MSC_GET_RX_TIMEOUT_STATUS_API == STD_ON) */
/* Call Msc_DisableNotfication but the notification type is already disabled */
#define MSC_E_ALREADY_DISABLED                         (0x0CU)
/* The Msc is not belong to the current core */
#define MSC_E_CORE_NOT_MATCH                           (0x0EU)
/* API service called without invalid module number */
#define MSC_E_INVALID_CHANNEL                          (0x0FU)
/*Module initialization failed */
#define MSC_E_INIT_FAILED                              (0x10U)

/****************************************************************************************************
**                          Global Function Declarations                                           **
****************************************************************************************************/
extern FUNC(void, MSC_PUBLIC_CODE) Msc_Init
(
    CONSTP2CONST(Msc_ConfigType, AUTOMATIC, MSC_APPL_CONST)ConfigPtr
);

#if (MSC_DEINIT_API == STD_ON)
extern FUNC(void, MSC_PUBLIC_CODE) Msc_DeInit
(
  void
);
#endif /* (MSC_DEINIT_API  \== STD_ON) */

#if (MSC_CHANGE_TX_STATUS_API == STD_ON)
extern FUNC(void, MSC_PUBLIC_CODE) Msc_ChangeTxState
(
    Msc_ModuleType ModNum,
    Msc_TxStateType DownstreamStatus
);
#endif /* (MSC_CHANGE_TX_STATUS_API  \== STD_ON) */

#if (MSC_GET_TX_STATUS_API == STD_ON)
extern FUNC(Msc_TxStatusType, MSC_PUBLIC_CODE) Msc_GetTxStatus
(
    Msc_ModuleType ModNum,
    Msc_FrameClassType TxFrameType
);
#endif /* (MSC_GET_TX_STATUS_API  \== STD_ON) */

extern FUNC(void, MSC_PUBLIC_CODE) Msc_TxCmdFrame
(
    Msc_ModuleType ModNum,
    Msc_TxDevSelectType Device,
    uint32 Cmd
);

#if defined(THA6_THA6206D)
extern FUNC(Std_ReturnType, MSC_PUBLIC_CODE) Msc_SyncTxCmdFrame
(
    Msc_ModuleType ModNum,
    Msc_TxDevSelectType Device,
    uint32 Cmd
);
#endif

#if (MSC_TX_DATA_FRAME_API == STD_ON)
extern FUNC(void, MSC_PUBLIC_CODE) Msc_TxDataFrame
(
    Msc_ModuleType ModNum,
    Msc_TxDevSelectType DeviceHigh,
    Msc_TxDevSelectType DeviceLow, 
    uint32 DataValue
);

#endif /* (MSC_TX_DATA_FRAME_API  \== STD_ON) */

extern FUNC(void, MSC_PUBLIC_CODE)Msc_SelectTxDevice
(
    Msc_ModuleType ModNum,
    Msc_TxDevSelectType DeviceHigh,
    Msc_TxDevSelectType DeviceLow
);

#if (MSC_CHANGE_RX_STATUS_API == STD_ON)
extern FUNC(void, MSC_PUBLIC_CODE) Msc_ChangeRxState
(
    Msc_ModuleType ModNum,
    Msc_RxStateType UpstreamStatus
);
#endif /* (Msc_ChangeRxState  \== STD_ON) */

#if (MSC_GET_RX_DATA_API == STD_ON)
extern FUNC(Msc_RxStatus, MSC_PUBLIC_CODE) Msc_GetRxData
(
    Msc_ModuleType ModNum,
    Msc_UpstreamRegType Msc_RxRegister,
    uint8 *const DataPtr
);
#endif /* (MSC_GET_RX_DATA_API  \== STD_ON) */

#if (MSC_SELECT_RX_DEVICE_API == STD_ON)
extern FUNC(void, MSC_PUBLIC_CODE) Msc_SelectRxDevice
(
    Msc_ModuleType ModNum,
    Msc_RxDevSelectType Msc_Device
);
#endif /* (MSC_SELECT_RX_DEVICE_API  \== STD_ON) */

#if (MSC_START_RX_TIMEOUT_API == STD_ON)
extern FUNC(void, MSC_PUBLIC_CODE) Msc_StartRxTimeout
(
    Msc_ModuleType ModNum
);
#endif /* (MSC_START_RX_TIMEOUT_API  \== STD_ON) */

#if (MSC_GET_RX_TIMEOUT_STATUS_API == STD_ON)
extern FUNC(Msc_RxTimeoutStatusType, MSC_PUBLIC_CODE) Msc_GetRxTimeoutStatus
(
    Msc_ModuleType ModNum
);
#endif /* (MSC_GET_RX_TIMEOUT_STATUS_API  \== STD_ON) */

extern FUNC(void, MSC_PUBLIC_CODE) Msc_EnableNotfication 
(
    Msc_ModuleType ModNum
);

extern FUNC(void, MSC_PUBLIC_CODE) Msc_DisableNotfication 
(
    Msc_ModuleType ModNum
);

/* #Violation: Msc_h_REF_1 */
extern FUNC(void, MSC_PUBLIC_CODE) Msc_ISRHandler
(
    uint8 HwModNum,
    uint8 ServiceNum
);

#if (MSC_VERSION_INFO_API == STD_ON)
extern FUNC(void, Msc_PUBLIC_CODE) Msc_GetVersionInfo
(
    /* #Violation: Msc_h_REF_1 */
    CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, Msc_APPL_DATA)VersionInfoPtr
);
#endif /* (Msc_VERSION_INFO_API  \== STD_ON) */

#endif /*MSC_INCLUDE_MSC_H_ */

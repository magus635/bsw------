/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Sent.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : SENT
*
*   brief                 : This file contains all function declarations of Sent Driver
*
*   Autosar Version       : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright /(c) 2021,Beijing Tongxin Microelectroics co.Ltd
*
****************************************************************************************************/

/*
*#Violation Summary
*#Sent_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Sent_h_REF_2:MISRAC2012-Rule-20.1;
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*/


#ifndef SENT_H_
#define SENT_H_

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Sent_Version.h"
#include "Sent_Cfg.h"
#include "Sent_PBcfg.h"
#include "Sent_GeneralTypes.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
******************************************************************************/

/* Sent module Status Uninitialized */
#define SENT_UNINITIALIZED            ((uint8)0x00U)
/* Status to indicate that SENT module is initialized */
#define SENT_INITIALIZED              ((uint8)0x01U)
/*
  Development error codes
*/
/* Service is called before Init */
#define SENT_E_UNINIT                   ((uint8)0x05)
/*Synchronous transmission service called at invalid channel.*/
#define SENT_E_INVALID_CHANNEL          ((uint8)0x02)
/* Service is called with invalid parameter */
#define SENT_E_PARAM_POINTER            ((uint8)0x03)
/* Service is called when initialization is failed */
#define SENT_E_INIT_FAILED              ((uint8)0x10)
/* Service is called when already initialized */
#define SENT_E_ALREADY_INITIALIZED      ((uint8)0x14)
/* DeInit failed */
#define SENT_E_DEINIT_FAILED            ((uint8)0x15)

/* Multi-core DETs*/
/* SENT channel is not allocated to this core */
#define SENT_E_CORE_CHANNEL_MISMATCH    ((uint8)0x65)
/* Report DET when channel is not configured */
# define SENT_E_CHANNEL_NOT_CONFIGURED  ((uint8)0x68)
/* Report DET when channel is not enabled */
#define SENT_E_CHANNEL_NOT_ENABLED      ((uint8)0x69)

/*
  Service ID number for all SENT driver services
*/
/* Service ID for Sent_Init */
#define SENT_SID_INIT                   ((uint8)0x00)
/* Service ID for Sent_SetChannel */
#define SENT_SID_SETCHANNEL             ((uint8)0x01)
/* Service ID for Sent_ReadData */
#define SENT_SID_READDATA               ((uint8)0x03)
/* Service ID for Sent_ReadSerialData */
#define SENT_SID_READSERIALDATA         ((uint8)0x04)
/* Service ID for Sent_ReadChannelStatus */
#define SENT_SID_READCHANSTATUS         ((uint8)0x05)
/* Service ID for Sent_SpcGenPulse */
#define SENT_SID_SPCGENPULSE            ((uint8)0x06)
/* Service ID for Sent_GetVersionInfo */
#define SENT_SID_GETVERINFO             ((uint8)0x08)
/* Service ID for Sent_DeInit */
#define SENT_SID_DEINIT                 ((uint8)0x07)
/* Service ID for Sent_Receive_ISRHandler */
#define SENT_SID_RECVISR                ((uint8)0x09)
/* Service ID for Sent_Error_ISRHandler */
#define SENT_SID_ERRISR                ((uint8)0x0A)

/* Serial data was not received  */
/* #Violation: Sent_h_REF_1 */
#define SENT_NO_DATA                    ((uint8)SENT_SLOW_TYPE_NO) 
/* Serial data has been received */
/* #Violation: Sent_h_REF_1 */
#define SENT_RECEIVED_SERIAL_DATA       ((uint8)SENT_SLOW_TYPE_ALL) 

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
/* #Violation: Sent_h_REF_1 */
#define SENT_START_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Sent_h_REF_2 */
#include "Sent_MemMap.h"

extern void Sent_Init
(
  const Sent_ConfigType * const ConfigPtr
);

extern void Sent_SetChannel
(
  const Sent_ChannelIdxType ChanId,
  Sent_ChanOpType Operation
);

extern uint32 Sent_ReadData
(
  const Sent_ChannelIdxType ChannelId
);

extern void Sent_ReadSerialData
(
  const Sent_ChannelIdxType ChannelId,
  Sent_RxSerialDataType * const DataPtr
);

extern void Sent_ReadChannelStatus
(
  const Sent_ChannelIdxType ChannelId,
  Sent_ChanStatusType * const StatPtr
);

#if (SENT_VERSION_INFO_API == STD_ON)
extern void Sent_GetVersionInfo
(
  Std_VersionInfoType* const VersionInfo
);
#endif /* #if( (SENT_VERSION_INFO_API  \== STD_ON) */

#if (SENT_SPC_USED == STD_ON)
extern void Sent_SpcGenPulse
(
  const Sent_ChannelIdxType ChanId
);
#endif /* #if (SENT_SPC_USED  \== STD_ON) */

#if (SENT_DEINIT_API == STD_ON)
extern void Sent_DeInit
(
  void
);
#endif /* #if (SENT_DEINIT_API  \== STD_ON) */

extern void Sent_Receive_ISRHandler
(
  uint8 IntrNode
);

extern void Sent_Error_ISRHandler
(
  uint8 IntrNode
);

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/

/* To store the SENT driver configuration pointer */
/* #Violation: Sent_h_REF_1 */
#define SENT_STOP_SEC_CODE_ASIL_D_GLOBAL 
/* #Violation: Sent_h_REF_2 */
#include "Sent_MemMap.h"
#endif /* SENT_H_ */

/****************************************************************************************************
 **                          End of File                                                            *
 ***************************************************************************************************/


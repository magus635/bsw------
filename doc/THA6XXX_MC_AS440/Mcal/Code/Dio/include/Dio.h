/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dio.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : GPIO
*
*   brief                 : This file contains all function declarations of Dio Driver
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
*#Dio_h_REF_1:MISRAC2012-Rule-20.7;
* Justification:Compiler keyword (macro) is defined and used followed AUTOSAR standard rule.
*
*#Dio_h_REF_2:MISRAC2012-Rule-2.5; 
* Justification:The macros are reserved for upper layers.
*
*/

#ifndef DIO_H_
#define DIO_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Dio_GeneralTypes.h"
#include "Dio_Cfg.h"
#include "Dio_Version.h"

/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Development error codes*/
#if (DIO_DEV_ERROR_DETECT == STD_ON)

/* Invalid Channel name requested */
#define DIO_E_PARAM_INVALID_CHANNEL_ID           ((uint8)0x0AU)
/* Invalid Port name requested */
#define DIO_E_PARAM_INVALID_PORT_ID              ((uint8)0x14U)
/* Invalid Group name requested */
#define DIO_E_PARAM_INVALID_GROUP                ((uint8)0x1FU)
/* Service is called with NULL_PTR */
#define DIO_E_PARAM_POINTER                      ((uint8)0x20U)

/*
  Service ID number for all DIO driver services
*/
/* Service ID for Read_Channel */
#define DIO_SID_READCHANNEL                      ((uint8)0x00U)
/* Service ID for Write_Channel */
#define DIO_SID_WRITECHANNEL                     ((uint8)0x01U)
/* Service ID for Read_Port */
#define DIO_SID_READPORT                         ((uint8)0x02U)
/* Service ID for Write_Port */
#define DIO_SID_WRITEPORT                        ((uint8)0x03U)
/* Service ID for Read_Group */
#define DIO_SID_READGROUP                        ((uint8)0x04U)
/* Service ID for Write_Group */
#define DIO_SID_WRITEGROUP                       ((uint8)0x05U)
/* Service ID for FlipChannel */
#if (DIO_FLIP_CHANNEL_API == STD_ON)
#define DIO_SID_FLIPCHANNEL                      ((uint8)0x11U)
#endif /* (DIO_FLIP_CHANNEL_API  \== STD_ON) */
/* Service ID for GetVersion */
#if (STD_ON == DIO_VERSION_INFO_API)
#define DIO_SID_GETVERSIO                        ((uint8)0x12U)
#endif /* (STD_ON \== DIO_VERSION_INFO_API) */
#endif /* (DIO_DEV_ERROR_DETECT  \== STD_ON) */

/* DIO MODULE INSTANCE ID */
#define DIO_INSTANCE_ID                          ((uint8)0x00U)
/* Dio group mask all bit */
#define DIO_GROUP_MASKALL                        ((uint16)0xFFFFU)
/* Invalid port index */
#define DIO_INVALID_PORT_INDEX                   ((uint8)0xFFU)
/* Dio group mask */
#define DIO_GROUP_MIN_MASK                       ((uint16)0x01U)
/* Dio channel not config */
#define DIO_CHANNEL_NOT_CONFIG                   ((uint16)0x00U)
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
/* #Violation: Dio_h_REF_2 */
#define DIO_START_SEC_CODE_ASIL_D_GLOBAL
#include "Dio_MemMap.h"

extern FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_ReadChannel
(
    Dio_ChannelType ChannelId
);

extern FUNC(void, DIO_PUBLIC_CODE) Dio_WriteChannel
(
    Dio_ChannelType ChannelId,
    Dio_LevelType Level
);

extern FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE) Dio_ReadPort
(
    Dio_PortType PortId
);

extern FUNC(void, DIO_PUBLIC_CODE) Dio_WritePort
(
    Dio_PortType PortId,
    Dio_PortLevelType Level
);

extern FUNC(Dio_PortLevelType, DIO_PUBLIC_CODE) Dio_ReadChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_CONFIG_CONST) ChannelGroupIdPtr
);

extern FUNC(void, DIO_PUBLIC_CODE) Dio_WriteChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_CONFIG_CONST) ChannelGroupIdPtr,
    Dio_PortLevelType Level
);

#if (STD_ON == DIO_VERSION_INFO_API)

extern FUNC(void, DIO_PUBLIC_CODE) Dio_GetVersionInfo
(
    /* #Violation: Dio_h_REF_1 */
    P2VAR(Std_VersionInfoType, AUTOMATIC, DIO_APPL_DATA) VersionInfoPtr
);

#endif /* (STD_ON \== DIO_VERSION_INFO_API) */

#if (DIO_FLIP_CHANNEL_API == STD_ON)
extern FUNC(Dio_LevelType, DIO_PUBLIC_CODE) Dio_FlipChannel
(
    Dio_ChannelType ChannelId
);
#endif /* (DIO_FLIP_CHANNEL_API  \== STD_ON) */

#if (STD_ON == DIO_MASKED_WRITE_PORT_API)
extern FUNC(void, DIO_PUBLIC_CODE) Dio_MaskedWritePort
(
    const Dio_PortType PortId,
    const Dio_PortLevelType Level,
    const Dio_PortLevelType Mask
);
#endif /* (STD_ON \== DIO_MASKED_WRITE_PORT_API) */
/* #Violation: Dio_h_REF_2 */
#define DIO_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "Dio_MemMap.h"

#endif /* DIO_H_ */

/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/


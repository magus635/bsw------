/****************************************************************************************************
 *   FileName              : Msc_GeneralTypes.h
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
*#Msc_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
* code complexity 
*
*#Msc_GeneralTypes_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
* code complexity;
*
*/

#ifndef MSC_GENERAL_TYPES_H_
#define MSC_GENERAL_TYPES_H_
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Msc_Cfg.h"
#include "Mcall_GeneralTypes.h"
#include "Mcall_Cfg.h"
#include "msc_hal.h"

/****************************************************************************************************
 *                           Global Symbols                                                         **
 ****************************************************************************************************/

/****************************************************************************************************
**                          Global basic type Definitions                                          **
****************************************************************************************************/
/* Downstream channel status */
typedef Msc_DownstreamEn Msc_TxStateType;
/* Transmit device select */
typedef Msc_Target Msc_TxDevSelectType;
/*  Receiver select */
typedef Msc_Sdi Msc_RxDevSelectType;
/* Msc logic module number */
typedef uint8 Msc_ModuleType;

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
/* Driver status type */
typedef enum
{
    /* Msc driver is not initialized */
    MSC_UNINITIALIZED = 0U,
    /* Msc driver is initialized */
    MSC_INITIALIZED
}Msc_InitStateType;

/* Receive channel status */
typedef enum
{
    /* Upstream channel is off */
    MSC_RX_OFF = 0U,
    /* Upstream channel is on */
    MSC_RX_ON
}Msc_RxStateType;

typedef enum
{
    /* Frame type is command frame */
    MSC_CMD_FRAME = 0U,
    /* Frame type is data frame */
    MSC_DATA_FRAME
}Msc_FrameClassType;

typedef enum
{
    /* API execute failed */
    MSC_TX_NOT_OK = 0U,
    /* Transmitter of command is ready */
    MSC_CMDFRMTX_READY,
    /* Transmitter of command is busy */
    MSC_CMDFRMTX_NOTREADY,
    /* Transmitter of data is ready */
    MSC_DATAFRMTX_READY,
    /* Transmitter of data is busy */
    MSC_DATAFRMTX_NOTREADY
}Msc_TxStatusType;

#if (MSC_GET_RX_TIMEOUT_STATUS_API == STD_ON)
typedef enum
{
    /* API ececute failed */
    MSC_TIMEOUT_NOT_OK = 0U,
    /* Upstream receive is not timeout */
    MSC_UPSTREAM_NO_TIMEOUT,
    /* Upstream receive is timeout */
    MSC_UPSTREAM_TIMEOUT
}Msc_RxTimeoutStatusType;
#endif /* (MSC_GET_RX_TIMEOUT_STATUS_API  \== STD_ON) */

/****************************************************************************************************
**                          Global Structure Definitions                                          **
****************************************************************************************************/
/* Channel Status Type */
typedef  struct
{
    /* Notification status */
    boolean                      NotifyStatus;
    /* upstream status */
    Msc_RxStateType              UpstreamChannelStatus;
    /* Downstream status */
    Msc_TxStateType              DownstreamChannelStatus;
}Msc_ChannelStatusType;

typedef struct
{
    /* The function pointer of data frame interrupt notification function */
    void (*DataFrmNotifyPtr)(void);
    /* The function pointer of command frame interrupt notification function */
    void (*CmdFrmNotifyPtr)(void);
    /* The function pointer of time frame interrupt notification function */
    void (*TimeFrmNotifyPtr)(void);
    /* The function pointer of receive data interrupt notification function */
    void (*RxFrmNotifyPtr)(void);
/* #Violation: Msc_GeneralTypes_h_REF_1 */
}Msc_NotficationType;

/* The msc interrupt configuration */
/* #Violation: Msc_GeneralTypes_h_REF_1 */
/* #Violation: Msc_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Interrupt configuration */
    Msc_IntrConfig             IntConfig;
    /* Interrupt notification function Configuration */
    Msc_NotficationType        Notification;
    /* Interrupt enable configuration parameter */
    uint32                     IntEnablePara;
/* #Violation: Msc_GeneralTypes_h_REF_1 */
}Msc_IntConfigType;

/* #Violation: Msc_GeneralTypes_h_REF_1 */
/* #Violation: Msc_GeneralTypes_h_REF_2 */
typedef struct
{
    Msc_TimeoutConfig            TimeoutConfig;
    /* The function pointer of upstream timeout interrupt notification function */
    void                         (*UpTimeoutFrmNotifyPtr)(void);
}Msc_TimeoutConfigType;

/* Hardware mapping type */
/* #Violation: Msc_GeneralTypes_h_REF_1 */
/* #Violation: Msc_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Index of the core of the current hardware */
    uint8                             Core;
    /* index of the channel of the current hardware */
    uint8                             Index;
/* #Violation: Msc_GeneralTypes_h_REF_1 */
}Msc_MappingType;

/* Channel Configuration Type */
/* #Violation: Msc_GeneralTypes_h_REF_1 */
/* #Violation: Msc_GeneralTypes_h_REF_2 */
typedef struct
{
    /* MSC module hardware pointer */
    MSC_MODULE *                     MscModulePtr;
    /* Module configuration */
    const Msc_ModuleConfig*          ModuleConfigPtr;
    /* Interrupt configuration */
    const Msc_IntConfigType*         InterruptConfigPtr;
    /* Timeout configuration */
    const Msc_TimeoutConfigType*     TimeoutConfigPtr;
/* #Violation: Msc_GeneralTypes_h_REF_1 */
}Msc_ChConfigType;

/* Core configuration type */
/* #Violation: Msc_GeneralTypes_h_REF_1 */
/* #Violation: Msc_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Number of MSC channel of current core */
    uint8                            MaxChannel;
    /* MSC Channel Configuration */
    const Msc_ChConfigType*          Msc_ChannelConfigPtr;
/* #Violation: Msc_GeneralTypes_h_REF_1 */
}Msc_CoreConfigType;

/* The msc driver configuration set */
/* #Violation: Msc_GeneralTypes_h_REF_2 */
typedef struct
{
    /* The pointer to the core hardware configuration */
    const Msc_CoreConfigType*        CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* Core mapping */
    const Msc_MappingType*           MscCoreMappingPtr;
    /* Pointer to hardware channel mapping with logic channel */
    const uint8*                     MscHwChannelMapPtr;
}Msc_ConfigType;

#endif /* MSC_GENERAL_TYPES_H_*/

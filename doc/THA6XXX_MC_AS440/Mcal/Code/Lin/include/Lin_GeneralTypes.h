/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Lin_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : ASI
*
*   brief                 : This file contains all type definitions of Lin Driver
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
*#Lin_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Lin_GeneralTypes_h_REF_2:MISRAC2012-Rule-2.3; 
* Justification: Reserved types are defined in AUTOSAR specifications.
*
*#Lin_GeneralTypes_h_REF_3:CertC-DCL02-C; 
* Justification: Company-specific naming conventions are applied. Developers will not be confused.
*
*#Lin_GeneralTypes_h_REF_4:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*/

/**************************************************************************************************/
#ifndef LIN_GENERAL_TYPES_H_
#define LIN_GENERAL_TYPES_H_
/***************************************************************************************************
*                               Includes
***************************************************************************************************/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "EcuM.h"
#include "Lin_Cfg.h"
#include "Mcall.h"
#include "asi_hal.h"
#if(LIN_WAKEUP_SUPPORT == STD_ON)
/* LIN implements a wake-up function,"
*  this header file needs to be include */
#include "EcuM_Externals.h"
#endif/* (LIN WAKEUP SUPPORT \== STD ON) */
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/* SWS_Lin_00228: Represents all valid protected identifier used by Lin_SendFrame()
 * Range: The LIN identifier (0x3F) together with its two parity bits. */
typedef uint8 Lin_FramePidType;

/* SWS_Lin_00231: This type is used to specify the number of SDU data bytes to copy
 * Range: Data length of a LIN Frame. */
typedef uint8 Lin_FrameDlType;

/* Specifies the ID for a ASI Hardware microcontroller peripheral unit */
typedef uint8 Lin_HWUnitType;

/* Lin initialization parameter structure remapping */
typedef Asi_Lin_Config       Lin_HwUnitConfigType;

/* Lin frame structure parameter structure remapping */
typedef Asi_Lin_FrameControl Lin_FrameControlType;

/****************************************************************************************************
**                          Global Enumeration Definitions                                         **
****************************************************************************************************/
/* SWS_Lin_00229: This type is used to specify the Checksum model to be used for the LIN Frame */
typedef enum
{
    /* Enhanced checksum mode */
    LIN_ENHANCED_CS = 0U,
    /* Classic checksum model */
    LIN_CLASSIC_CS
} Lin_FrameCsModelType;

/* SWS_Lin_00230: This type is used to specify whether the frame processor is required to transmit the
 * response part of the LIN frame */
typedef enum
{
    /* Response is generated from this (master) node */
    LIN_FRAMERESPONSE_TX = 0U,
    /* Response is generated from a remote slave node */
    LIN_FRAMERESPONSE_RX,
    /* Response is generated from one slave to another slave, * for the master the response will
     * be anonymous, it does not have to receive the response */
    LIN_FRAMERESPONSE_IGNORE
} Lin_FrameResponseType;

/* SWS_Lin_00233: LIN operation states for a LIN channel or frame, as returned by the API service Lin_GetStatus() */
typedef enum
{
    /* LIN frame operation return value. Development or production error occurred. */
    LIN_NOT_OK = 0U,
    /* LIN frame operation return value. Successful transmission. */
    LIN_TX_OK,
    /* LIN frame operation return value. Ongoing transmission (Header or Response). */
    LIN_TX_BUSY,
    /* LIN frame operation return value.
     * Erroneous header transmission such as:
     * - Mismatch between sent and read back data
     * - Physical bus error */
    LIN_TX_HEADER_ERROR,
    /* LIN frame operation return value.
     * Erroneous response transmission such as:
     * - Mismatch between sent and read back data
     * - Physical bus error */
    LIN_TX_ERROR,
    /* LIN frame operation return value. Reception of correct response. */
    LIN_RX_OK,
    /* LIN frame operation return value.
     *  Ongoing reception: at least one response byte has been received, but the
     *  checksum byte has not been received */
    LIN_RX_BUSY,
    /* LIN frame operation return value.
     * Erroneous response reception such as:
     * - Framing error
     * - Overrun error
     * - Checksum error or
     * - Short response */
    LIN_RX_ERROR,
    /* LIN frame operation return value. No response byte has been received so far. */
    LIN_RX_NO_RESPONSE,
    /* LIN channel state return value. Normal operation; the related LIN channel is ready to
     * transmit next header. No data from previous frame available (e.g. after initialization) */
    LIN_OPERATIONAL,
    /* LIN channel state return value. Sleep state operation;
     * in this state wake-up detection from slave nodes is enabled. */
    LIN_CH_SLEEP
} Lin_StatusType;

/* LIN Channel Status */
typedef enum
{
    /* LIN channel frame transmission finished */
    LIN_CH_TX_OK_STATUS = 1U,
    /* LIN channel frame is transmitting */
    LIN_CH_TX_BUSY_STATUS,
    /* LIN channel frame header error when transmitting */
    LIN_CH_TX_HEADER_ERROR_STATUS,
    /* LIN channel frame response error when transmitting */
    LIN_CH_TX_ERROR_STATUS,
    /* LIN channel frame response receive finished */
    LIN_CH_RX_OK_STATUS,
    /* LIN channel frame is receiving */
    LIN_CH_RX_BUSY_STATUS,
    /* LIN channel frame error when receiving */
    LIN_CH_RX_ERROR_STATUS,
    /* LIN channel frame is not response */
    LIN_CH_RX_NO_RESPONSE_STATUS,
    /* The individual channel has been initialized (using at least one statically configured
     * data set) and is able to participate in the LIN cluster. */
    LIN_CH_OPERATIONAL,
    /* The detection of a wake-up pulse is enabled. The LIN hardware is into a low power mode
     * if such a mode is provided by the hardware. */
    LIN_CH_SLEEP_STATE,
    /* go-to-sleep-command has been issued on the bus, LIN channel stay at this state
     * until Lin_GetStatus() is called */
    LIN_CH_SLEEP_PENDING,
    /* LIN channel frame header is transmitting */
    LIN_CH_TX_HEADER_BUSY_STATUS,
    /* LIN channel exception error */
    LIN_CH_OTHER_ERROR
} Lin_ChStatusType;

/** This type represents the slave error types that are detected during header reception
 * and response transmission / reception. */
typedef enum
{
    LIN_ERR_HEADER = 0U,   /**< Error in header */
    LIN_ERR_RESP_STOPBIT, /**< Framing error in response */
    LIN_ERR_RESP_CHKSUM,  /**< Checksum error */
    LIN_ERR_RESP_DATABIT, /**<  Monitoring error of transmitted data bit in response */
    LIN_ERR_NO_RESP,      /**< No response */
    LIN_ERR_INC_RESP      /**< Incomplete response */
    /* #Violation: Lin_GeneralTypes_h_REF_2 */
} Lin_SlaveErrorType;

typedef enum
{
    LINTRCV_WUMODE_ENABLE = 0U,    /**< The notification for wakeup events is enabled on the addressed
                                       network. */
    LINTRCV_WUMODE_DISABLE,       /**< The notification for wakeup events is disabled on the
                                       addressed network. */
    LINTRCV_WUMODE_CLEAR          /**< A stored wakeup event is cleared on the addressed network. */
    /* #Violation: Lin_GeneralTypes_h_REF_2 */
} LinTrcv_TrcvWakeupModeType;

typedef enum
{
    LINTRCV_WU_ERROR = 0U,         /**< Due to an error wake up reason was not detected. This value may
                                       only be reported when error was reported to DEM before. */
    LINTRCV_WU_NOT_SUPPORTED,     /**< The transceiver does not support any information for the wake
                                       up reason. */
    LINTRCV_WU_BY_BUS,            /**< The transceiver has detected, that the network has caused the
                                       wake up of the ECU. */
    LINTRCV_WU_BY_PIN,            /**< The transceiver has detected a wake-up event at one of the
                                       transceiver's pins (not at the LIN bus). */
    LINTRCV_WU_INTERNALLY,        /**< The transceiver has detected, that the network has woken up by
                                       the ECU via a request to NORMAL mode. */
    LINTRCV_WU_RESET,             /**< The transceiver has detected, that the "wake up" is due to an
                                       ECU reset. */
    LINTRCV_WU_POWER_ON           /**< The transceiver has detected, that the "wake up" is due to an
                                       ECU reset after power on. */
  /* #Violation: Lin_GeneralTypes_h_REF_2 */
} LinTrcv_TrcvWakeupReasonType;

/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* SWS_Lin_00232: This Type is used to provide PID, checksum model, data length and SDU pointer
     from the LIN Interface to the LIN driver */
/* \[SWS_Lin_00014] = Each LIN PID shall be associated with a checksum model 
(either enhanced where the PID is included in the checksum, or classic where only 
the response data is check-summed) */
/* \[SWS_Lin_00015]  Each LIN PID shall be associated with a response data length 
in bytes */
typedef struct
/* #Violation: Lin_GeneralTypes_h_REF_4 */
{
    /* LIN frame identifier. */
    Lin_FramePidType       Pid;
    /* Checksum model type. */
    /* #Violation: Lin_GeneralTypes_h_REF_3 */
    Lin_FrameCsModelType   Cs;
    /* Response type. */
    Lin_FrameResponseType  Drc;
    /* Data length. */
    Lin_FrameDlType        Dl;
    /* Pointer to Sdu. */
    uint8*                 SduPtr;
} Lin_PduType;

/* Type for LIN channel configuration information */
/* #Violation: Lin_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Lin_GeneralTypes_h_REF_4 */
{
    /* LIN Channel ID */
    /* #Violation: Lin_GeneralTypes_h_REF_3 */
    uint8                 ChannelId;
    /* LIN Hardware Channel */
    Lin_HWUnitType        HwUnitId;
    /* Is wake-up supported by the LIN channel */
    boolean               ChannelWakeupSupport;
    /* This parameter contains a reference to the Wake-up Source for this controller
     * as defined in the ECU State Manager.*/
    EcuM_WakeupSourceType ChannelEcuMWakeupSource;
    /* Lin (ASI) register configuration information */
    const Lin_HwUnitConfigType *RegisterConfigPtr;
} Lin_ChannelConfigType;

/* Type for core configuration */
/* #Violation: Lin_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Lin_GeneralTypes_h_REF_4 */
{
    /* Maximum number of the channels allocated to the core */
    uint8                       MaxCoreChannels;
    /* Pointer to LIN Channel Configuration */
    const Lin_ChannelConfigType *ChannelConfigPtr;
} Lin_CoreConfigType;

/* Type for LIN channel status */
/* #Violation: Lin_GeneralTypes_h_REF_1 */
typedef struct
/* #Violation: Lin_GeneralTypes_h_REF_4 */
{
    /* LIN channel status */
    Lin_ChStatusType        ChStatus;
    /* LIN channel PDU buffer pointer */
    Lin_PduType             PduBuffer;
    /* Check wake-up signal */
    boolean                 WakeupFlag;
    /* LIN header received or not */
    boolean                 IsHeaderRecv;
} Lin_ChInternalStatusType;

/* This type is used to flag the LIN channel information */
typedef struct
{
    /* LIN channel frame error status */
    Lin_ChInternalStatusType *ChannelStatusPtr;
    /* LIN driver initialization status in current core */
    uint8                    *CoreInitStatusPtr;
    /* LIN data buffer pointer of this core */
    uint8                    *CoreSduBufferPtr;
} Lin_CoreStatusType;

/* SWS_Lin_00247: LIN driver configuration for initializing the LIN Driver */
/* \[SWS_Lin_00227] */
typedef struct
/* #Violation: Lin_GeneralTypes_h_REF_4 */
{
    /* Pointer to core configuration */
    const Lin_CoreConfigType *CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* Pointer to the channel allocation core mapping */
    const uint8              *ChannelToCorePtr;
    /* HwUnit assigned to the LIN channel */
    const uint8              *HwUnitToChannelIdPtr;
} Lin_ConfigType;


#endif /* _LIN_GENERAL_TYPES_H_ */

/*****************************************************************************************************
**                      End of File
*****************************************************************************************************/

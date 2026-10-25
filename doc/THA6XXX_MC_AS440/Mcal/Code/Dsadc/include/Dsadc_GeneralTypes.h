/****************************************************************************************************
*
****************************************************************************************************/
/****************************************************************************************************
*   FileName              : Dsadc_GeneralTypes.h
*
*   Platform              : AUTOSAR
*
*   Peripheral            : Dsadc
*
*   brief                 : This file contains all type definitions of Dsadc Driver
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
*#Dsadc_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
*   code complexity.
*
*#Dsadc_GeneralTypes_h_REF_2:CertC-DCL12-C;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the 
*   code complexity.
*
*/

#ifndef DSADC_GENERAL_TYPES_H_
#define DSADC_GENERAL_TYPES_H_

/****************************************************************************************************
*                               Include
****************************************************************************************************/
#include "Dsadc_Cfg.h"
#include "Mcall.h"
/* Header files including the HAL layer */
#include "dsadc_hal.h"

/****************************************************************************************************
*                               Symbol Definitions
****************************************************************************************************/
/* Type for the numeric ID of an DSADC channel */
typedef uint8 Dsadc_ChannelType;
/* Type for the conversion result buffer */
typedef sint16 Dsadc_ResultType;
/* Type for timestamp */
typedef uint16 Dsadc_TimestampType;
/* Type for the number of samples of a streaming conversion buffer */
typedef uint8 Dsadc_NumSampleType;
/* Type for HW unit identifier */
typedef Dsadc_ChannelType Dsadc_HWUnitType;
#if (DSADC_CFG_SET_CARRIER_SYNC_PARAM_API == STD_ON)
/* Type for carrier sync parameters */
typedef Dsadc_CarrierWaveSyncConfig Dsadc_CarrierSyncConfigType;
#endif /* \(DSADC_CFG_SET_CARRIER_SYNC_PARAM_API == STD_ON) */

/****************************************************************************************************
*                               Typedef Enum
****************************************************************************************************/
#if (DSADC_DEV_ERROR_DETECT == STD_ON)
/* DSADC driver initialization status */
typedef enum
{
    DSADC_UNINITIALIZE = 0U,
    DSADC_INITIALIZED
} Dsadc_InitType;
#endif /* \(DSADC_DEV_ERROR_DETECT == STD_ON) */

/* Type for current status of the conversion of the requested DSADC channel */
typedef enum
{
    /* The conversion of the specified channel has not been started. */
    /* Channel is in IDLE state, No result is available. */
    DSADC_IDLE = 0U,
    /* The conversion of the specified channel has been started and is still going on. */
    /* Channel is in BUSY state, So far no result is available */
    DSADC_BUSY,
    /* A conversion round (which is not the final one) of the specified channel has been finished. */
    /* Channel is in COMPLETED state, A result is available for the channels. */
    DSADC_COMPLETED,
    /* The result buffer is completely filled. */
    /* Channel is in STREAM_COMPLETED state, For channel the number of samples to be acquired is
     * available*/
    DSADC_STREAM_COMPLETED
} Dsadc_StatusType;

/* Type for configuring the access mode to group conversion results */
typedef enum
{
    /* Return the result register value is read to the user/integrator without buffering. */
    DSADC_ACCESS_MODE_SINGLE = 0U,
    /* Streaming access mode */
    DSADC_ACCESS_MODE_STREAMING,
} Dsadc_AccessType;

/* Type for configuring the streaming access mode buffer type */
typedef enum
{
    /* The DSADC Driver stops the conversion as soon as the stream buffer is full
     * (number of samples reached). */
    DSADC_STREAM_BUFFER_LEANER = 0U,
    /* The DSADC Driver continues the conversion even if the stream buffer is full
     * (number of samples reached) by wrapping around the stream buffer itself. */
    DSADC_STREAM_BUFFER_CIRCULAR
} Dsadc_StreamBufType;

/* Limit checking event */
typedef enum
{
    /* Conversion result above the upper limit */
    DSADC_RESULT_ABOVE_UPPER_LIMIT = 0U,
    /* Conversion result below the lower limit */
    DSADC_RESULT_BELOW_LOWER_LIMIT
} Dsadc_LimitCheckingEventType;

/* Type for conversion channel */
typedef enum
{
    /* Main conversion channel */
    DSADC_CONV_CHANNEL_MAIN = DSADC_MAINCHANNEL,
    /* Auxiliary conversion channel */
    DSADC_CONV_CHANNEL_AUX = DSADC_AUXILIARYCHANNEL
} Dsadc_ConvChannelType;

/****************************************************************************************************
*                               Type Definitions
****************************************************************************************************/

/* Type definition for HW unit mapping relationship */
/* #Violation: Dsadc_GeneralTypes_h_REF_1 */
/* #Violation: Dsadc_GeneralTypes_h_REF_2 */
typedef struct
{
    /* The index position of the Channel in Core private configuration parameter structure */
    Dsadc_ChannelType                  CoreChannelIdx;
    /* Mapping information of logical channel to HW unit */
    Dsadc_HWUnitType                   HwUnitId;
    /* Core Id which the Channel belong to */
    uint8                              ChannelMapCoreId;
} Dsadc_ChannelCoreMapType;

/* Type definition for the global data information */
typedef struct
{
#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
    /* Notification status for the channel */
    boolean                              ChNotifStatus;
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */
    /* Interrupt enable flag */
    uint16                               IntEnBits;
    /* Timestamp count */
    Dsadc_TimestampType                  Timestamp;
    /* Number of valid conversion result for main conversion channel */
    Dsadc_NumSampleType                  ChValidRsltNum;
    /* Pointer to the Result buffer */
    Dsadc_ResultType                     *ChRsltBufPtr;
    /* HW FIFO error status */
    Dsadc_FifoErrorStatus                FifoErrFlag;
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    /* Auxiliary conversion channel status */
    Dsadc_StatusType                     ChAuxStatus;
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
    /* Variable to hold main conversion channel Status */
    Dsadc_StatusType                     ChStatus;
} Dsadc_GlobalDataType;

/* Type for channel configuration set */
/* #Violation: Dsadc_GeneralTypes_h_REF_1 */
/* #Violation: Dsadc_GeneralTypes_h_REF_2 */
typedef struct
{
    /* HW unit identifier */
    Dsadc_HWUnitType                     HwUnitId;
    /* Logic channel identifier */
    Dsadc_ChannelType                    LgcChId;
    /* Modulator enable status */
    boolean                              IsMdlDitheringEn;
    /* Common mode voltage enable flag */
    boolean                              IsCommonModeVoltEn;
    /* Common mode voltage level */
    Dsadc_BiasVoltageSelect              CommonModeVoltLevel;
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    /* Flag the result acquisition functionality enable status */
    boolean                              IsAuxChRsltAcqEn;
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
#if (DSADC_CFG_TIMESTAMP_ENABLE == STD_ON)
    /* Flag timestamp enable status */
    boolean                              TimestampEn;
#endif /* \(DSADC_CFG_TIMESTAMP_ENABLE == STD_ON) */
    /* Result handling implementation */
    uint8                                RsltHldMthd;
    /* Number of values to be acquired in streaming access mode */
    Dsadc_NumSampleType                  NumSamples;
    /* Conversion result access mode */
    Dsadc_AccessType                     RsltAccessMod;
    /* Buffer mode type - Configure streaming buffer as "linear buffer" or "circular buffer" */
    Dsadc_StreamBufType                  StreamBufMod;
#if (DSADC_CFG_NOTIF_CAPABILITY == STD_ON)
    /* Pointer to the new conversion result generated notification function */
    void (*NewRsltNotifFuncPtr)(Dsadc_ConvChannelType ConvChannel);
    /* Pointer to the new conversion result generated notification function */
    void (*BufFullNotifFuncPtr)(void);
    /* Pointer to the new conversion result generated notification function */
    void (*LimitChkNotifFuncPtr)(Dsadc_LimitCheckingEventType ChEvent, Dsadc_ResultType ChResult);
#endif /* \(DSADC_CFG_NOTIF_CAPABILITY == STD_ON) */
#if (DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_ON)
    /* Interrupt event when limit checking enabled */
    uint8                                LimitCheckEvtBits;
#endif /* \(DSADC_CFG_LIMIT_CHECKING_ENABLE == STD_ON) */
    /* Compensation parameter when auto calibration is not used */
    const Dsadc_CompensationConfig       *CalibCompConfigPtr;
    /* Pointer to the configuration information */
    const Dsadc_ModuleConfig             *HwCfgPtr;
} Dsadc_ChannelConfigType;

/* Type for channel configuration in core */
/* #Violation: Dsadc_GeneralTypes_h_REF_1 */
/* #Violation: Dsadc_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Maximum number of the channels allocated to the core */
    uint8                                MaxCoreChannel;
    /* Pointer to channel configuration */
    const Dsadc_ChannelConfigType        *ChannelConfigPtr;
} Dsadc_CoreConfigType;

/* Type for global configuration */
/* #Violation: Dsadc_GeneralTypes_h_REF_1 */
/* #Violation: Dsadc_GeneralTypes_h_REF_2 */
typedef struct
{
    /* Bits for enable the HW units. bit0-DSADC0, bit<x>-DSADC<x> */
    uint32                               HWUnitEnBits;
#if (DSADC_CFG_AUX_FILTER_ENABLE == STD_ON)
    /* Bits for enable the auxiliary filter chain. bit<x>-DSADC<x> auxiliary filter.  */
    uint32                               AuxFltrHwUnitEnBits;
#endif /* \(DSADC_CFG_AUX_FILTER_ENABLE == STD_ON) */
    /* Pointer to the carrier configuration information */
    const Dsadc_CarrierWaveConfig        *CarrierCfgPtr;
} Dsadc_GlobalConfigType;

/* Type for Dsadc driver configuration and used for initializing driver */
/* #Violation: Dsadc_GeneralTypes_h_REF_2 */
typedef struct 
{
    /* Pointer to DSADC HW unit configuration buffer address */
    const Dsadc_CoreConfigType           *CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* Pointer to the global configuration buffer address */
    const Dsadc_GlobalConfigType         *GlobalCfgPtr;
    /* Pointer to the Mapping information of logical channels to cores */
    const Dsadc_ChannelCoreMapType       *ChannelMapPtr;
    /* Pointer to the Mapping information of HW unit to logical channels */
    const uint8                          *HwUnitToChannelIdPtr;
#if (MCAL_PROCESSOR_CAT == MCAL_PROCESSOR_THA6412_BGA516)
    uint8                                Dsadc1InputPin;
#endif /* \ */
} Dsadc_ConfigType;

#endif /* \DSADC_GENERAL_TYPES_H_ */

/****************************************************************************************************
**                      End of File
****************************************************************************************************/

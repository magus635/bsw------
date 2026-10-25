/****************************************************************************************************
 *
****************************************************************************************************/
/****************************************************************************************************
 *   FileName              : Spi_GeneralTypes.h
 *
 *   Platform              : AUTOSAR
 *
 *   Peripheral            : Espi
 *
 *   brief                 : This file contains all type definitions of Spi Driver
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
*#Spi_GeneralTypes_h_REF_1:MISRAC2012-Dir-4.8;
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*#Spi_GeneralTypes_h_REF_2:CertC-DCL12-C; 
* Justification: Apply such struct/union definitons to simplify the code structure and reduce the code complexity.
*
*/
#ifndef SPI_GENERALTYPES_H_
#define SPI_GENERALTYPES_H_

/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Mcall.h"
#include "Spi_Cfg.h"
#include "Std_Types.h"
#include "espi_hal.h"
#if (SPI_ENABLE_DMA == STD_ON)
#include "Dma.h"
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
/****************************************************************************************************
**                          Global Type Definitions                                                **
****************************************************************************************************/
/*  SWS_Spi_00376: 
    Type of application data buffer elements
    SWS_Spi_00355:
    Spi_DataBufferType defines the type of application data buffer elements. Type is uint8. Access to
    the data is selected dynamically as is described in SWS_SPI_00437. The data buffer has to be
    aligned to 32 bits. It shall be provided for external use.
    SWS_Spi_00164:
    The type Spi_DataBufferType refers to application data buffer elements.
*/
typedef uint8                         Spi_DataBufferType;

/*  SWS_Spi_00377: 
    Type for defining the number of data elements of the type Spi_DataBufferType
    SWS_Spi_00165:
    The type Spi_NumberOfDataType is used for defining the number of data elements of the type
    specified in [SWS_SPI_00437]  to send and / or receive by Channel.
*/
typedef uint16                        Spi_NumberOfDataType;

/*  SWS_Spi_00378:
    Specifies the identification (ID) for a Channel
    SWS_Spi_00356:
    The type Spi_ChannelType specifies the identification (ID) for a Channel.
    SWS_Spi_00166:
    The type Spi_ChannelType is used for specifying the identification (ID) for a Channel.
*/
typedef uint8                         Spi_ChannelType;

/*  SWS_Spi_00379:
    Specifies the identification (ID) for a Job
    SWS_Spi_00357:
    The type Spi_JobType specifies the identification (ID) for a Job.
    SWS_Spi_00167:
    The type Spi_JobType is used for specifying the identification (ID) for a Job.
*/
typedef uint16                        Spi_JobType;

/*  SWS_Spi_00380:
    Specifies the identification (ID) for a sequence
    SWS_Spi_00358:
    The type Spi_SequenceType specifies the identification (ID) for a sequence of jobs.
    SWS_Spi_00168:
    The type Spi_SequenceType is used for specifying the identification (ID) for a sequence of jobs.
*/
typedef uint8                         Spi_SequenceType;

/*  SWS_Spi_00381:
    Specifies the identification (ID) for a ESPI hardware unit
    SWS_Spi_00359:
    The type Spi_HWUnitType specifies the identification (ID) for a SPI Hardware
    microcontroller peripheral (unit).
    SWS_Spi_00169:
    The type Spi_HWUnitType is used for specifying the identification (ID) for a SPI Hardware
    microcontroller peripheral (unit).
*/
typedef uint8                         Spi_HWUnitType;

/* ECUC_Spi_00207: Specifies the identification (ID) for a external device */
typedef uint8                         Spi_ExternalDeviceType;

/* ECUC_Spi_00207: Type redefinition Espi PhyUnit external device configuration parameter structure */
typedef Espi_Master_ChannelInitConfig Spi_ExternalDeviceConfigParamType;

/* Type redefinition Espi PhyUnit initialization parameter structure */
typedef Espi_Master_ModuleInitConfig  Spi_PhyUnitConfigParamType;

/* ECUC_Spi_00104: Type redefinition Espi PhyUnit channel dynamic configuration parameter structure */
typedef Espi_ChannelDynamicConfig     Spi_ChannelDynamicConfigType;

/****************************************************************************************************
**                          Global Enumeration Definitions                                          **
****************************************************************************************************/
/*  SWS_Spi_00373:
    This type defines a range of specific status for SPI Driver
    Range:     SPI_UNINIT       The SPI Handler/Driver is not initialized or not usable.
               SPI_IDLE The     SPI Handler/Driver is not currently transmitting any Job.
               SPI_BUSY The     SPI Handler/Driver is performing a SPI Job (transmit).
    SWS_Spi_00061:
    The type Spi_StatusType defines a range of specific status for SPI Handler/Driver. It informs
    about the SPI Handler/Driver status or specified SPI Hardware microcontroller peripheral.
*/
typedef enum
{
    SPI_UNINIT = 1U, /* Not initialized or not usable */
    SPI_IDLE,       /* Not currently transmitting any jobs */
    SPI_BUSY        /* Performing a SPI Job(transmit) */
} Spi_StatusType;

/*  SWS_Spi_00374:
    This type defines a range of specific Jobs status for SPI Driver
    Range:  SPI_JOB_OK          The last transmission of the Job has been finished successfully.
            SPI_JOB_PENDING     The SPI Handler/Driver is performing a SPI Job. The meaning of this
                                status is equa to SPI_BUSY.
            SPI_JOB_FAILED      The last transmission of the Job has failed.
            SPI_JOB_QUEUED      An asynchronous transmit Job has been accepted, while actual
                                transmission for this Job has not started yet.
*/
typedef enum
{
    SPI_JOB_OK = 0U,  /* The last transmission of the Job has been finished */
    SPI_JOB_PENDING, /* The SPI handler/Driver is performing a SPI Job */
    SPI_JOB_FAILED,  /* The last transmission of the Job has failed */
    SPI_JOB_QUEUED   /* An asynchronous transmit Job has been accepted, while
                        actual transmission for this Job has not started yet */
} Spi_JobResultType;

/*  SWS_Spi_00375:
    This type defines a range of specific Sequences status for SPI Driver
    Range:    SPI_SEQ_OK        The last transmission of the Sequence has been finished successfully.
              SPI_SEQ_PENDING   The SPI Handler/Driver is performing a SPI Sequence. The meaning of
                                this status is equal to SPI_BUSY.
              SPI_SEQ_FAILED    The last transmission of the Sequence has failed.
              SPI_SEQ_CANCELED  The last transmission of the Sequence has been canceled by user.
    SWS_Spi_00351:
    The type Spi_SeqResultType defines a range of specific Sequences status for SPI Handler/Driver
    and can be obtained calling the API service Spi_GetSequenceResult, it shall be provided for
    external use.
    SWS_Spi_00019:
    The type Spi_SeqResultType defines the range of specific Sequences status for SPI Handler/Driver.
    SWS_Spi_00251:
    The type Spi_SeqResultType defines about SPI Handler/Driver Sequence status and can be obtained
    calling the API service Spi_GetSequenceResult with the Sequence ID.
*/
typedef enum
{
    SPI_SEQ_OK = 0U,   /* The last transmission of the Sequence has been finished */
    SPI_SEQ_PENDING,  /* The SPI handler/Driver is performing a SPI Sequence */
    SPI_SEQ_FAILED,   /* The last transmission of the Sequence has failed */
    SPI_SEQ_CANCELLED /* The last transmission of the Sequence has been
                         cancelled by the user. */
} Spi_SeqResultType;

/*  SWS_Spi_00382:
    Specifies the asynchronous mechanism mode for SPI buses handled asynchronously in Level2
    Range: SPI_POLLING_MODE     The asynchronous mechanism is ensured by polling, so interrupts 
                                related to SPI busses handled asynchronously are disabled. 
           SPI_INTERRUPT_MODE   The asynchronous mechanism is ensured by interrupt, so interrupts 
                                related to SPI busses handled asynchronously are enabled. 
    SWS_Spi_00360:
    The type Spi_AsyncModeType specifies the asynchronous mechanism mode for SPI buses handled
    asynchronously in LEVEL2 and obtained by the API Spi_SetAsyncMode.
    SWS_Spi_00170:
    The type Spi_AsyncModeType is used for specifying the asynchronous mechanism mode for SPI
    busses handled asynchronously in LEVEL2.
    SWS_Spi_00150:
    The type Spi_AsyncModeType is made available or not depending on the pre-compile time
    parameter: SpiLevelDelivered. This is only relevant for LEVEL 2.
    SWS_Spi_00361:
    If API Spi_SetAsyncMode function is called by the parameter value SPI_POLLING_MODE then
    asynchronous mechanism is ensured by polling. So interrupts related to SPI buses handled
    asynchronously are disabled.
    SWS_Spi_00362:
    If API Spi_SetAsyncMode function is called by the parameter value SPI_INTERRUPT_MODE
    asynchronous mechanism is ensured by interrupt, so interrupts related to SPI buses handled
    asynchronously are enabled.
*/
typedef enum
{
    SPI_POLLING_MODE = 0U,
    SPI_INTERRUPT_MODE
} Spi_AsyncModeType;

/*  SWS_Spi_00052
    For the IB Channels, the Handler/Driver shall provide the buffering but it is not able to take
    care of the consistency of the data in the buffer during transmission. The size of the Channel
    buffer is fixed.
    SWS_Spi_00053:   
    For EB Channels the application shall provide the buffering and shall take care of the
    consistency of the data in the buffer during transmission.
*/
/* The enumeration containing the designated values for buffer types  */
typedef enum
{
    SPI_IB = 0U,
    SPI_EB
} Spi_BufferType;

/* ECUC_Spi_00239: When the Chip select handling is enabled (see SpiEnableCs), then this parameter
   specifies if the chip select is handled automatically by Peripheral HW engine or via general
   purpose IO by Spi driver.
*/
typedef enum
{
    SPI_CS_VIA_GPIO = 0U,
    SPI_CS_VIA_PERIPHERAL_ENGINE
} Spi_CsSelectionType;

/* Enumeration defines the initialization state of SpiDriver */
#if (SPI_DEV_ERROR_DETECT == STD_ON)
typedef enum
{
    SPI_UNINITIALIZE = 0U,
    SPI_INITIALIZED
} Spi_DriverStateType;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
/****************************************************************************************************
**                          Global Union Definitions                                               **
****************************************************************************************************/

/****************************************************************************************************
**                          Global Structure Definitions                                           **
****************************************************************************************************/
/* Type definition Spi internal (send/receive) buffer configuration structure */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* SPI Channel default transmission value */
    uint32                    ChDefaultData;
    /* Transmit buffer pointer */
    Spi_DataBufferType       *TXBuffPtr;
    /* Receive buffer pointer */
    Spi_DataBufferType       *RXBuffPtr;
} Spi_BufferDescriptorType;

/*  SWS_Spi_00064:
    For the type Spi_ConfigType, the definition for each Sequence shall contain:
        Collection of Jobs (at least one);
        Interruptible or not interruptible after each Job;
        Sequence finish end notification function;
*/
/* Type definition Spi Sequence configuration information structure */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* SPI Sequence ID */
    Spi_SequenceType   SequenceId;
    /* Boolean indicating if the Job of Sequence is interruptible or not */
    boolean            Interruptible;
    /* Number of jobs in the sequence */
    Spi_JobType        NumJobs;
    /* Job index list in current Sequence */
    const Spi_JobType  *JobIndexListPtr;
    /* bitx = 1 means Spix is occupy in current Sequence */
    uint16             MaskSeqUsedPhyUnit;
    /* Seq notification handler */
    /*  SWS_Spi_00044:
        The SPI Handler/Driver's implementer must implement the callback notifications
        Spi_JobEndNotification and Spi_SeqEndNotification as function pointers defined within the
        initialization data structure (Spi_ConfigType).
        SWS_Spi_00054:
        If a callback notification is configured as null pointer, no callback shall be executed.
    */
    void (*SeqEndNotificationPtr)(void);
} Spi_SequenceConfigType;
/* SWS_Spi_00009:
    For the type Spi_ConfigType, the definition for each Job shall contain:
        Assigned SPI HW Unit;
        Assigned Chip Select pin (it is possible to assign no pin);
        Chip select functionality on/off;
        Chip select pin polarity high or low;
        Baudrate;
        Timing between clock and chip select;
        Shift clock idle low or idle high;
        Data shift with leading or trailing edge;
        Priority (4 levels are available from 0, the lower to 3, the higher);
        Job finish end notification function;
        MCU dependent properties for the Job (only if needed);
        Fixed link of Channels (at least one);
*/
/* Type definition Spi external device configuration parameter structure */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* Define the HW SPI Hardware Index */
    Spi_HWUnitType                           SpiNumber;
    /* Deifne Chip select control mode GPIO/Spi driver */
    Spi_CsSelectionType                      CsSelection;
    /* Variable to save / restore Gpio CS pin */
    uint16                                   GpioPortPin;
    /* Parity Type Even or Odd */
    Espi_ParityMode                          ParitySelection;
    /* FSwR_MCAL_SPI_003: Phase delay parameter */
    Espi_PhaseDelay                          DelayParam;
    /* PhyUnit configuration data structure provided by the SDK */
    const Spi_ExternalDeviceConfigParamType *Spi_ExDeviceCfgInfoPtr;
} Spi_ExternalDeviceConfigType;
/* Type definition Spi PhyUnit configuration parameter structure */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* Define Spi PhyUnit number */
    Spi_HWUnitType                          SpiNumber;
#if (SPI_ENABLE_DMA == STD_ON)
    /* FSwR_MCAL_SPI_001*/
    /* Defines the TX DMA Channel ID referenced by the Spi PhyUnit */
    Dma_ChannelType                         TxDmaChannel;
    /* Defines the RX DMA Channel ID referenced by the Spi PhyUnit */
    Dma_ChannelType                         RxDmaChannel;
    /* FSwR_MCAL_SPI_001: Pointer Corex DMA linked list Channel dynamic configuration
       information storage buffer
    */
    uint32                                  *ChDynamicCfgPtr;
    /* FSwR_MCAL_SPI_001: Points to the DMA linked list TCS storage buffer */
    Dma_LliBufType                          *DmaTcsBufferPtr;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
    /* Define Spi PhyUnit initialization parameter structure pointer */
    const Spi_PhyUnitConfigParamType        *Spi_PhyUnitConfigParamPtr;
} Spi_PhyUnitConfigType;
/* Type definition Spi Sequence state management structure */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* Sequence Result state */
    Spi_SeqResultType             SeqResult;
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    /* Pointer to the Sequence configuration */
    const Spi_SequenceConfigType *SeqConfigPtr;
    /* Position to the job in transmission of an async sequence */
    const Spi_JobType            *CurJobIndexPtr;
    /* Number of jobs in a pending async sequence, not yet transmited */
    Spi_JobType                   RemainingJobs;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
} Spi_SequenceStateType;
/* Type definition Spi Job status management structure */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* Job Result State */
    Spi_JobResultType           JobResult;
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    /* Pointer to the state information of the async sequence */
    Spi_SequenceStateType       *AsyncSeqStatePtr;
    /* Pointer to the next async job planned for transmission */
    Spi_JobType                 AsyncNextJob;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
} Spi_JobStateType;
/* SWS_Spi_00063:
    For the type Spi_ConfigType, the definition for each Channel shall contain:
        Buffer usage with EB/IB Channel;
        Transmit data width (1 up to 32 bits);
        Number of data buffers for IB Channels (at least 1) or
        it is the maximum of data for EB Channels (a value of 0 makes no sense);
        Transfer start LSB or MSB;
        Default transmit value
*/
/* Type definition Spi channel configuration information structure */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* SPI channel ID */
    Spi_ChannelType                     LogicChId;
    /* Define the SPI Buffer type Internal Buffer(IB)/External Buffer(EB) */
    Spi_BufferType                      ChannelType;
    /* Define the number of bits of the SPI transmission data frame */
    Espi_DataWidth                      DataFrameWidth;
    /* Define the number of bytes of the SPI transmission data frame */
    Espi_DataBufferWidth                FrameWidth;
    /* Number of data buffers for IB Channels (at least 1) or
       it is the maximum of data for EB Channels (a value of 0 makes no sense) */
    Spi_NumberOfDataType                DataLength;
    /* Transmit buffer pointer and Receive buffer pointer */
    Spi_BufferDescriptorType            *BufferDescriptorPtr;
    /* Actual Transfer Byte size for EB */
    Spi_NumberOfDataType                *ActualDataLengthPtr;
    /* Defines the first starting bit for transmission */
    Espi_BitOrder                       TransferStart;
} Spi_ChannelConfigType;
/* Type definition Spi Job configuration information structure */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* SPI Job ID */
    Spi_JobType             JobId;
    /* Identify the HW SPI Hardware Index */
    Spi_HWUnitType          SpiNumber;
    /* Define release the chip select after each Byte is sent */
    boolean                 PullCSbyData;
    /*  SWS_Spi_00010:
        For the type Spi_ConfigType, the configuration will map the Jobs to the different SPI
        hardware units and the devices.
    */
    /* External device ID configured by the Job */
    Spi_ExternalDeviceType  ExDeviceUnit;
    /* Number of channels in the Job */
    Spi_ChannelType         NumChannels;
    /* Channel index list in current Job */
    const Spi_ChannelType   *ChannelIndexListPtr;
    /* Job end notification */
    /*   SWS_Spi_00044:
        The SPI Handler/Driver's implementer must implement the callback notifications
        Spi_JobEndNotification and Spi_SeqEndNotification as function pointers defined within the
        initialization data structure (Spi_ConfigType).
        SWS_Spi_00054:
        If a callback notification is configured as null pointer, no callback shall be executed.
    */
    void (*JobEndNotificationPtr)(void);
    /* Job priority level */
    uint8                   Priority;
    /* Implementation specific field referencing the channel internal state */
    Spi_JobStateType        *JobStatePtr;
} Spi_JobConfigType;
/* SPI hardware unit state data structure */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
#if (SPI_ENABLE_DMA == STD_ON)
    /* FSwR_MCAL_SPI_001: SPI PhyUnit DMA enable flag */
    boolean                 DmaEnable;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    boolean                 IsAsync;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
    /* SPI driver status */
    Spi_StatusType          PhyUnitStatus;
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    /* Array of the IDs of last jobs in queues, for each priority level */
    Spi_JobType             ScheduledJobsListHead[SPI_JOB_PRIORITY_LEVELS_COUNT];
    /* Array of the IDs of last jobs in queues, for each priority level */
    Spi_JobType             ScheduledJobsListTail[SPI_JOB_PRIORITY_LEVELS_COUNT];
    /* Max priority level for HwUint */
    sint8                   MaxScheduledPriority;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
} Spi_PhyUnitStateType;
/* External device status data structure in asynchronous communication mode */
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
#if (SPI_LEVEL_DELIVERED == SPI_LEVEL2)
    /* System timer count at which the asynchronous transfer of this hardware unit is supervised as
       timed out, 0 means that no transfer is supervised */
    uint64                      AsyncDeadline;
#endif /* (SPI_LEVEL_DELIVERED \== SPI_LEVEL2) */
    /* Actual receive data length, not yet received */
    Spi_NumberOfDataType        ReceivedData;
    /* Reference to the current job */
    const Spi_JobConfigType     *CurJobPtr;
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    /* Pointer to the Tx buffer of the channel currently in transmission */
    Spi_DataBufferType          *CurTxBufPtr;
    /* Pointer to the Rx buffer of the channel currently in transmission */
    Spi_DataBufferType          *CurRxBufPtr;
    /* Position in ChannelIndexList to the channel in transmission */
    const Spi_ChannelType       *CurChannelIndexPtr;
    /* Number of channels in a pending async job, not yet transmitted */
    Spi_ChannelType             RemainingChannels;
    /* Number of frames in a pending channel, not yet transmitted */
    Spi_NumberOfDataType        RemainingData;
    /* Number of sent frames, which must be read back in the next ISR call */
    Spi_NumberOfDataType        SentFrames;
    /* Width of Sent frames in a pending channel */
    Espi_DataBufferWidth        SentFramesWidth;
    /* Flag indicates whether it is the last frame of data in the current Job */
    boolean                     IsEndOfJob;
    /* Channel dynamic configuration register value */
    uint32                      ChDynamicCfg;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
} Spi_DeviceStateType;
/* Type definition Corex Spi driver state management structure */
typedef struct
{
    /* SPI Sequence status pointer */
    Spi_SequenceStateType       *SequenceStatusPtr;
    /* SPI hardware status pointer */
    Spi_PhyUnitStateType         *PhyUnitStatusPtr;
    /* Variables used in Asynchronous mode */
    Spi_DeviceStateType         *DeviceStatePtr;
#if (SPI_DEV_ERROR_DETECT == STD_ON)
    /* SPI current Core init status */
    Spi_DriverStateType         *CoreInitStatusPtr;
#endif /* (SPI_DEV_ERROR_DETECT  \== STD_ON) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    /* Asynchronous operating mode of the ESPI unit */
    Spi_AsyncModeType           *AsyncMode;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL1) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
#if ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) || (SPI_LEVEL_DELIVERED == SPI_LEVEL2))
    /* bitx = 1 means Spix's Synchronous transmission in progress */
    uint16                      *PhyUnitBusySyncStatusPtr;
#endif /* ((SPI_LEVEL_DELIVERED == SPI_LEVEL0) \|| (SPI_LEVEL_DELIVERED == SPI_LEVEL2)) */
    /* bitx = 1 means Spix belongs to a Sequence (synchronous or asynchronous) that has
       been declared but whose teardown, including its end notification, is not yet
       complete. Independent of PhyUnitBusySyncStatusPtr/PhyUnitStatus, which are also
       used to decide scheduling and are cleared earlier, before notifications run: this
       flag exists only so busy-detection (Spi_GetDriverStatus, Spi_SyncCheckPhyUnitsFree)
       is never fooled by a gap where those drop to idle/free while the Sequence is still
       being torn down or about to truly claim its HW unit. */
    uint16                      *PhyUnitPendingTeardownStatusPtr;
} Spi_CoreStatusType;

/* SWS_Spi_00008:
    The type Spi_ConfigType is an external data structure and shall contain the initialization data
    for the SPI Handler/Driver. It shall contain:
        MCU dependent properties for SPI HW units;
        Definition of Channels;
        Definition of Jobs;
        Definition of Sequences.
*/
/* This is the top level structure containing all the needed parameters for the SPI Handler Driver.*/
/* #Violation: Spi_GeneralTypes_h_REF_1 */ 
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* Number of sequences defined in the Corex configuration */
    Spi_SequenceType                    MaxSeq;
    /* Number of jobs defined in the Corex configuration */
    Spi_JobType                         MaxJob;
    /* Number of channels defined in the Corex configuration */
    Spi_ChannelType                     MaxChannel;
    /* Number of external devices defined in the Corex configuration */
    Spi_ExternalDeviceType              MaxExDevice;
    /* Number of hardware unit defined in the Corex configuration */
    Spi_HWUnitType                      MaxPhyUnit;
    /* Pointer to Array of sequences defined in the Corex configuration */
    const Spi_SequenceConfigType        *SeqCfgPtr;
    /* Pointer to Array of jobs defined in the Corex configuration */
    const Spi_JobConfigType             *JobCfgPtr;
    /* Pointer to Array of channels defined in the Corex configuration */
    const Spi_ChannelConfigType         *ChannelCfgPtr;
    /* Pointer to Array of External device instances defined in the Corex configuration */
    const Spi_ExternalDeviceConfigType  *ExDeviceCfgPtr;
    /* Pointer to Array of SPI device instances defined in the Corex configuration */
    const Spi_PhyUnitConfigType          *PhyUnitCfgPtr;
} Spi_CoreConfigType;
/* SWS_Spi_00372:
    This type of the external data structure shall contain the initialization data for the SPI
    Handler/Driver.
   SWS_Spi_00344:
    The description of the type Spi_ConfigType is implementation specific and it shall be provided
    for external use.
*/
typedef struct
/* #Violation: Spi_GeneralTypes_h_REF_2 */
{
    /* Pointer to Corex ESPI HW Unit configuration buffer address */
    const Spi_CoreConfigType        *CoreConfigPtr[MCAL_NUMBER_OF_CORES];
    /* The total number of Sequence configured in SpiSequence container */
    const Spi_SequenceType          MaxSequence;
    /* The total number of Jobs configured in SpiJob container */
    const Spi_JobType               MaxJob;
    /* The total number of Channels configured in SpiChannel container */
    const Spi_ChannelType           MaxChannel;
    /* The total number of Channels configured in SpiHwUnitConfig container */
    const Spi_HWUnitType            MaxPhyUnit;
    /* Map information that Spi Sequence allocated to the each core */
    const Spi_SequenceType          *SequenceToCorePtr;
    /* Map information that Spi Job allocated to the each core */
    const Spi_JobType               *JobToCorePtr;
    /* Map information that Spi Channel allocated to the each core */
    const Spi_ChannelType           *ChannelToCorePtr;
    /* Map information that Spi External Device allocated to the each core */
    const Spi_ExternalDeviceType    *ExDeviceToCorePtr;
    /* Map information that Spi HW unit allocated to the each core */
    const Spi_HWUnitType            *PhyUnitToCorePtr;
#if (SPI_ENABLE_DMA == STD_ON)
    /* Map information that DMA Channel allocated to Spi PhyUnit */
    const Spi_HWUnitType            *DmaChToPhyUnitPtr;
#endif /* (SPI_ENABLE_DMA  \== STD_ON) */
    /* Spi available Espi hardware unit mapping table */
    ESPI_MODULE * const             *PhyUnitMapPtr;
} Spi_ConfigType;
#endif /* SPI_GENERALTYPES_H */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

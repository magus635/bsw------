/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Spi_PBCfg.c
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Espi
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version        : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
/*
*#Violation Summary
*
*#Spi_PBcfg_c_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*#Spi_PBcfg_c_REF_2:MISRAC2012-Rule-8.9;
* Justification: Static global variables are placed in non-cached RAM regions to ensure accessibility by multiple cores.
*
*#Spi_PBcfg_c_REF_3:MISRAC2012-Rule-11.4;
* Justification: Converting integers to object pointers to reduce register access complexity.
*
*#Spi_PBcfg_c_REF_4:MISRAC2012-Rule-20.1; 
* Justification: AUTOSAR imposes the specification of the sections in which certain parts of the driver must be placed.
*
*/
/****************************************************************************************************
**                          Includes                                                               **
****************************************************************************************************/
#include "Spi.h"
#include "Spi_Cfg.h"
#include "tha6_cfg.h"
/***************************************************************************************************
*                               Local Macros
****************************************************************************************************/
/* Spi maximum number of Job configured in Core0 */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_JOB_CORE0                        (1U)
/* Spi maximum number of Job configured in Core1 */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_JOB_CORE1                        (1U)

/* Spi maximum number of Channel configured in Core0 */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_CHANNEL_CORE0                    (3U)
/* Spi maximum number of Channel configured in Core1 */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_CHANNEL_CORE1                    (3U)

/* Spi maximum number of External Device configured in Core0 */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_EXT_DEV_CORE0                    (1U)
/* Spi maximum number of External Device configured in Core1 */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_EXT_DEV_CORE1                    (1U)

/*
  Configuration: SpiSequence
- The total number of Sequence configured in SpiSequence container.
*/
#define SPI_MAX_SEQUENCE                         (2U)
/*
  Configuration: SpiJob
- The total number of Jobs configured in SpiJob container.
*/
#define SPI_MAX_JOB                              (2U)
/*
  Configuration: SpiChannel
- The total number of Channels configured in SpiChannel container.
*/
#define SPI_MAX_CHANNEL                          (6U)
/*
  Configuration: SpiExternalDevice
- The total number of External Device configured in SpiExternalDevice container.
*/
#define SPI_MAX_EXTERNAL_DEVICE                  (2U)
/*
  Configuration: SpiMaxHwUnit
- The total number of Spi hardware microcontroller peripherals available and handled by
- this SPI Handler/Driver module.
*/
#define SPI_MAX_HWUNIT_COUNT                     (9U)
/*
  Configuration: SpiMaxDmaChannel
- The max Channel of DMA assigned to this SPI Handler/Driver module.
*/
#define SPI_DMACHANNEL_COUNT                     (17U)
/****************************************************************************************************
**                          External Function Declarations                                         **
****************************************************************************************************/
/*SWS_Spi_00264:
   The SPI Handler/Driver shall use the callback routines Spi_SeqEndNotification to inform
   other software modules about certain states or state changes.
  SWS_Spi_00265:
   For implement the call back function other modules are required to provide the routines
   in the expected manner.
  SWS_Spi_00048:
   The callback notifications Spi_JobEndNotification and Spi_SeqEndNotification shall have
   no parameters and no return value.
  SWS_Spi_00341:
   The operation SpiSeqEndNotification is Re-entrant.
*/
/* SpiJob0 'SpiSeqEndNotification' Function Declartion */
extern void Spi_SeqNotificationTest0(void);
/* SpiJob1 'SpiSeqEndNotification' Function Declartion */
extern void Spi_SeqNotificationTest1(void);
/*SWS_Spi_00075:
   The SPI Handler/Driver shall use the callback routines Spi_JobEndNotification to inform
   other software modules about certain states or state changes.
  SWS_Spi_00265:
   For implement the call back function other modules are required to provide the routines
   in the expected manner.
  SWS_Spi_00048:
   The callback notifications Spi_JobEndNotification and Spi_SeqEndNotification shall have
   no parameters and no return value.
  SWS_Spi_00340:
   The operation SpiJobEndNotification is Re-entrant.
*/
/* SpiJob0 'SpiJobEndNotification' Function Declartion */
extern void Spi_JobNotificationTest0(void);
/* SpiJob1 'SpiJobEndNotification' Function Declartion */
extern void Spi_JobNotificationTest1(void);
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/* Spi_0 DMA linked list Channel dynamic configuration information storage buffer */
static uint32                    Spi_ChDynamicCfgBufferPhyUint0[3];
/* Spi_0 DMA linked list node storage buffer */
static Dma_LliBufType            Spi_DmaTcsBufferPhyUint0[9];

/*SWS_Spi_00052:
   For the IB Channels, the Handler/Driver shall provide the buffering but it is not able to take
   care of the consistency of the data in the buffer during transmission. The size of the Channel
   buffer is fixed.
  SWS_Spi_00438:
   The Handler/Driver shall provide separate buffer for receive and transmit to ensure that transmitted
   data are not overwritten by the receive data.
  SWS_Spi_00053:
   For EB Channels the application shall provide the buffering and shall take care of the consistency
   of the data in the buffer during transmission.
*/
/* Record the length of the actual data to be transmitted on the channel (Byte) in core0 */
static Spi_NumberOfDataType      Spi_ChannelActualDataLengthCore0[SPI_MAX_CHANNEL_CORE0];
/* Job status management structure variables. */
static Spi_JobStateType          Spi_JobStateCore0[SPI_MAX_JOB_CORE0];

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_START_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/* Buffers Descriptors for EB Channel0 */
static Spi_BufferDescriptorType  Buffer_PBSpiChannel_0 =
{
    /* Channel default Transmit Value. */
    (uint32)0x55UL,
    /* Tx buffer address pointer */
    NULL_PTR,
    /* Rx buffer address pointer */
    NULL_PTR
};

/* Buffers Descriptors for EB Channel1 */
static Spi_BufferDescriptorType  Buffer_PBSpiChannel_1 =
{
    /* Channel default Transmit Value. */
    (uint32)0x55UL,
    /* Tx buffer address pointer */
    NULL_PTR,
    /* Rx buffer address pointer */
    NULL_PTR
};

/* Buffers Descriptors for EB Channel2 */
static Spi_BufferDescriptorType  Buffer_PBSpiChannel_2 =
{
    /* Channel default Transmit Value. */
    (uint32)0x55UL,
    /* Tx buffer address pointer */
    NULL_PTR,
    /* Rx buffer address pointer */
    NULL_PTR
};

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_STOP_SEC_VAR_INIT_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_START_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/*SWS_Spi_00052:
   For the IB Channels, the Handler/Driver shall provide the buffering but it is not able to take
   care of the consistency of the data in the buffer during transmission. The size of the Channel
   buffer is fixed.
  SWS_Spi_00438:
   The Handler/Driver shall provide separate buffer for receive and transmit to ensure that transmitted
   data are not overwritten by the receive data.
  SWS_Spi_00053:
   For EB Channels the application shall provide the buffering and shall take care of the consistency
   of the data in the buffer during transmission.
*/
/* Allocate Buffers for IB Channel3 */
/* Expand internal buffer aligned to uint8(buffer is uint8 and actual data also is uint8) */
static ALIGNED(4) Spi_DataBufferType        BufferTX_PBSpiChannel_3[5];
static ALIGNED(4) Spi_DataBufferType        BufferRX_PBSpiChannel_3[5];

/* Allocate Buffers for IB Channel4 */
/* Expand internal buffer aligned to uint16(buffer is uint8 and actual data is uint16) */
static ALIGNED(4) Spi_DataBufferType        BufferTX_PBSpiChannel_4[10];
static ALIGNED(4) Spi_DataBufferType        BufferRX_PBSpiChannel_4[10];

/* Allocate Buffers for IB Channel5 */
/* Expand internal buffer aligned to uint32(buffer is uint8 and actual data is uint32) */
static ALIGNED(4) Spi_DataBufferType        BufferTX_PBSpiChannel_5[20];
static ALIGNED(4) Spi_DataBufferType        BufferRX_PBSpiChannel_5[20];

/* Record the length of the actual data to be transmitted on the channel (Byte) in core1 */
static Spi_NumberOfDataType      Spi_ChannelActualDataLengthCore1[SPI_MAX_CHANNEL_CORE1];
/* Job status management structure variables. */
static Spi_JobStateType          Spi_JobStateCore1[SPI_MAX_JOB_CORE1];

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_STOP_SEC_VAR_CLEARED_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_START_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/* Buffers Descriptors for IB Channel3 */
static Spi_BufferDescriptorType  Buffer_PBSpiChannel_3 =
{
    /* Channel default Transmit Value. */
    (uint32)0x55UL,
    /* Tx buffer address pointer */
    BufferTX_PBSpiChannel_3,
    /* Rx buffer address pointer */
    BufferRX_PBSpiChannel_3
};

/* Buffers Descriptors for IB Channel4 */
static Spi_BufferDescriptorType  Buffer_PBSpiChannel_4 =
{
    /* Channel default Transmit Value. */
    (uint32)0x55UL,
    /* Tx buffer address pointer */
    BufferTX_PBSpiChannel_4,
    /* Rx buffer address pointer */
    BufferRX_PBSpiChannel_4
};

/* Buffers Descriptors for IB Channel5 */
static Spi_BufferDescriptorType  Buffer_PBSpiChannel_5 =
{
    /* Channel default Transmit Value. */
    (uint32)0x55UL,
    /* Tx buffer address pointer */
    BufferTX_PBSpiChannel_5,
    /* Rx buffer address pointer */
    BufferRX_PBSpiChannel_5
};

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_STOP_SEC_VAR_INIT_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_START_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/* All Channel configuration information in Core0 */
static const Spi_ChannelConfigType Spi_ChannelConfigSetCore0[SPI_MAX_CHANNEL_CORE0] =
{
    {
        /* SPI channel ID: SpiChannel_0 */
        0U,
        /* Buffer Type IB/EB. */
        SPI_EB,
        /* SPI data width in channel */
        ESPI_DATAWIDTH_8,
        /* The number of bytes occupied by a data bits */
        ESPI_DATABUFFER_8BITS,
        /* Data length. SpiEbMaxLength */
        5U,
        /* Buffer Descriptor. */
        &Buffer_PBSpiChannel_0,
        /* The length of the actual data to be transmitted on the channel (Byte). */
        &Spi_ChannelActualDataLengthCore0[0],
        /* Defines the first starting bit for transmission */
        ESPI_BITORDER_MSB
    },
    {
        /* SPI channel ID: SpiChannel_1 */
        1U,
        /* Buffer Type IB/EB. */
        SPI_EB,
        /* SPI data width in channel */
        ESPI_DATAWIDTH_16,
        /* The number of bytes occupied by a data bits */
        ESPI_DATABUFFER_16BITS,
        /* Data length. SpiEbMaxLength */
        5U,
        /* Buffer Descriptor. */
        &Buffer_PBSpiChannel_1,
        /* The length of the actual data to be transmitted on the channel (Byte). */
        &Spi_ChannelActualDataLengthCore0[1],
        /* Defines the first starting bit for transmission */
        ESPI_BITORDER_MSB
    },
    {
        /* SPI channel ID: SpiChannel_2 */
        2U,
        /* Buffer Type IB/EB. */
        SPI_EB,
        /* SPI data width in channel */
        ESPI_DATAWIDTH_32,
        /* The number of bytes occupied by a data bits */
        ESPI_DATABUFFER_32BITS,
        /* Data length. SpiEbMaxLength */
        5U,
        /* Buffer Descriptor. */
        &Buffer_PBSpiChannel_2,
        /* The length of the actual data to be transmitted on the channel (Byte). */
        &Spi_ChannelActualDataLengthCore0[2],
        /* Defines the first starting bit for transmission */
        ESPI_BITORDER_MSB
    }
};

/* Channel to Job Assignment */
/* Channel list assigned in the SpiJob_0 */
static const Spi_ChannelType SpiJob_0_ChannelAssignment_PB[3] =
{
    0U,
    1U,
    2U
};

/* All Job configuration information in Core0 */
static const Spi_JobConfigType Spi_JobConfigSetCore0[SPI_MAX_JOB_CORE0] =
{
    {
        /* Spi Job ID: SpiJob_0 */
        (Spi_JobType)0U,
        /* SPI hardware number: Spi0 */
        (Spi_HWUnitType)0U,
        /* Configure whether to release the chip select after each frame of data */
        FALSE,
        /* External device ID configured by the job, SpiExternalDevice_0" */
        (Spi_ExternalDeviceType)0U,
        /* SpiJob_0 total channel counts */
        (Spi_ChannelType)3U,
        /* List of Channels */
        &SpiJob_0_ChannelAssignment_PB[0],
        /* End Notification */
        &Spi_JobNotificationTest0,
        /* Job Priority */
        0U,
        /* Implementation specific field referencing the channel internal state. */
        &Spi_JobStateCore0[0]
    }
};

/* Job to Sequence Assignment.
   Job ID with high priority are at the front of the Sequence list */
static const Spi_JobType SpiSequence_0_JobAssignment_PB[1] =
{
    0U
};

/* All Sequence configuration information in Core0 */
static const Spi_SequenceConfigType Spi_SequenceConfigSetCore0[SPI_MAX_SEQUENCE_CORE0] =
{
    {
        /* SPI Sequence ID: SpiSequence_0 */
        (Spi_SequenceType)0U,
        /*SWS_Spi_00126:
           When the SPI Handler/Driver is configured allowing interruptible Sequences, all Sequences
           declared shall have their dedicated parameter SpiInterruptibleSequence (see SWS_Spi_00064
           &amp; SPI106) to identify whether the Sequence can be suspended during transmission.
        */
        /* Sequence cann't be Interruptible */
        FALSE,
        /* Number of jobs in the sequence. */
        (Spi_JobType)1U,
        /* List of Jobs */
        &SpiSequence_0_JobAssignment_PB[0],
        /* bitx = 1 means Spix is occupy in current Sequence */
        (uint16)0x0001U,
        /* End Notification */
        &Spi_SeqNotificationTest0
    }
};

/* All ExternalDevice dynamic configuration information in Core0 */
static const Spi_ExternalDeviceConfigParamType SpiExternalDevice_ConfigParamCore0[SPI_MAX_EXT_DEV_CORE0] =
{
    {
        {
            /*
            SpiExternalDevice_0
            Baudrate parameter Tq is 4U.
            SpiModuleClock is 4.0E7
            Baudrate calculation formula:
            if SpiBaudParamB+SpiBaudParamC  = 0U: Baudrate = SpiModuleClock / (Tq*Q*(A+1))
            if SpiBaudParamB+SpiBaudParamC != 0U: Baudrate = SpiModuleClock / (Tq*Q*(A+B+C))
            Baudrate is 3333333U.
            */
            /* Baudrate parameter A */
            ESPI_PARAMETER_A_ONE_UNIT,
            /* Baudrate parameter B */
            ESPI_PARAMETER_B_ONE_UNIT,
            /* Baudrate parameter C */
            ESPI_PARAMETER_C_ONE_UNIT,
            /* Baudrate parameter Q */
            1U
        },
        /* Defines the SPI Idle clock level  */
        ESPI_CLOCKPOLARITY_IDLE_LOW,
        /* Defines the SPI data sampling edge */
        ESPI_CLOCKPHASE_FIRSTSAMPLE,
        /* Defines disable SPI parity check */
        FALSE,
        /* Defines SPI CS channel number */
        ESPI_CS_CHANNEL_ID_1,
        /* Defines SPI CS active output level */
        ESPI_SLSOOUTPUT_LEVEL_LOW,
        /* Define enable SPI internal chip select */
        TRUE
    }
};

/* All ExternalDevice static configuration information in Core0 */
static const Spi_ExternalDeviceConfigType Spi_ExternalDeviceConfigSetCore0[SPI_MAX_EXT_DEV_CORE0] =
{
    {
        /* SpiExternalDevice_0 use Espi HwUnit: Espi0 */
        (Spi_HWUnitType)0U,
        /* The chip select */
        SPI_CS_VIA_PERIPHERAL_ENGINE,
        /* Variable to restore Gpio CS pin. */
        (uint16)0xFFU,    /* Dio is not used as the chip selector */
        /* Parity: NONE, Not using parity */
        ESPI_PARITYMODE_NONE,
        /* Delay parameters */
        {
        /* SpiModuleClock is 4.0E7 */
            {
            /* SpiTrailingTime =  (SpiParamTrailUnit + 1) * 4^SpiParamTrail / SpiModuleClock */
                ESPI_DELAY_PRESCALER_4,
                ESPI_DELAY_UNIT_2
            },
            {
            /* SpiTimeClk2Cs =  (SpiDelayParamLeadUnits + 1) * 4^SpiDelayParamLead / SpiModuleClock */
                ESPI_DELAY_PRESCALER_4,
                ESPI_DELAY_UNIT_2
            },
            {
            /* SpiIdleTime =  (SpiDelayParamIdleUnits + 1) * 4^SpiDelayParamIdle / SpiModuleClock */
                ESPI_DELAY_PRESCALER_4,
                ESPI_DELAY_UNIT_2
            }
        },
        /* External device configuration parameter structure */
        &SpiExternalDevice_ConfigParamCore0[0]
    }
};

/* All SPI PhyUnit configuration information in Core0 */
static const Spi_PhyUnitConfigParamType Spi_PhyUnitConfigParamCore0[SPI_MAX_HWUNIT_CORE0] =
{
    {
        /* SPI0 use Espi HwUnit:ESpi_0*/
        /* Timeout duration threshold */
        ESPI_EXPECTTIMEOUT_2097152,
        /* Set TX FIFO Threshold */
        ESPI_TXFIFO_THRESHOLD_ONE,
        /* Set RX FIFO Threshold */
        ESPI_RXFIFO_THRESHOLD_ONE,
        /* Set SPI TX FIFO move mode*/
        ESPI_FIFOMODE_SINGLE,
        /* Set SPI RX FIFO move mode*/
        ESPI_FIFOMODE_BATCH,
        /* Configuration Enable or Disable RX and ERROR interrupts */
        ESPI_INTC_FLAG_NO_ERROR,
        /* Define the SPI global clock frequency division factor (Tq) */
        4U,
        /* Enable/Disable SPI TX/RX DMA */
        TRUE,
        /* Enable Move Counter Mode */
        TRUE
    }
};

/* All SPI PhyUnit parameter configuration information in Core0 */
static const Spi_PhyUnitConfigType Spi_PhyUnitConfigSetCore0[SPI_MAX_HWUNIT_CORE0] =
{
    {
        /* Spi number is: Spi0  */
        (uint8)0U,
        /* Defines the TX DMA Channel ID referenced by the Spi HwUnit */
        15U,
        /* Defines the RX DMA Channel ID referenced by the Spi HwUnit */
        16U,
        /* Pointer DMA linked list Channel dynamic configuration information storage buffer */
        &Spi_ChDynamicCfgBufferPhyUint0[0],
        /* Points to the DMA linked list TCS storage buffer */
        &Spi_DmaTcsBufferPhyUint0[0],
        /* SPI HwUnit configuration parameter structure */
        &Spi_PhyUnitConfigParamCore0[0]
    }
};

/* SPI driver configuration information in Core0 */
static const Spi_CoreConfigType Spi_ConfigSetCore0 =
{
    /* Number of sequences defined in the configuration. */
    SPI_MAX_SEQUENCE_CORE0,
    /* Number of jobs defined in the configuration. */
    SPI_MAX_JOB_CORE0,
    /* Number of channels defined in the configuration. */
    SPI_MAX_CHANNEL_CORE0,
    /* Number of external devices defined in the configuration. */
    SPI_MAX_EXT_DEV_CORE0,
    /* Number of HW unit defined in the configuration. */
    SPI_MAX_HWUNIT_CORE0,
    /* Pointer to Array of sequences defined in the Corex configuration */
    &Spi_SequenceConfigSetCore0[0],
    /* Pointer to Array of jobs defined in the Corex configuration */
    &Spi_JobConfigSetCore0[0],
    /* Pointer to Array of channels defined in the Corex configuration */
    &Spi_ChannelConfigSetCore0[0],
    /* Pointer to Array of External device instances defined in the Corex configuration */
    &Spi_ExternalDeviceConfigSetCore0[0],
    /* Pointer to Array of SPI device instances defined in the Corex configuration */
    &Spi_PhyUnitConfigSetCore0[0]
};

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_D_CORE0_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"
/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_START_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/* All Channel configuration information in Core1 */
static const Spi_ChannelConfigType Spi_ChannelConfigSetCore1[SPI_MAX_CHANNEL_CORE1] =
{
    {
        /* SPI channel ID: SpiChannel_3 */
        3U,
        /* Buffer Type IB/EB. */
        SPI_IB,
        /* SPI data width in channel */
        ESPI_DATAWIDTH_8,
        /* The number of bytes occupied by a data bits */
        ESPI_DATABUFFER_8BITS,
        /* Data length. SpiIbNBuffers */
        5U,
        /* Buffer Descriptor. */
        &Buffer_PBSpiChannel_3,
        /* The length of the actual data to be transmitted on the channel (Byte). */
        &Spi_ChannelActualDataLengthCore1[0],
        /* Defines the first starting bit for transmission */
        ESPI_BITORDER_MSB
    },
    {
        /* SPI channel ID: SpiChannel_4 */
        4U,
        /* Buffer Type IB/EB. */
        SPI_IB,
        /* SPI data width in channel */
        ESPI_DATAWIDTH_16,
        /* The number of bytes occupied by a data bits */
        ESPI_DATABUFFER_16BITS,
        /* Data length. SpiIbNBuffers */
        5U,
        /* Buffer Descriptor. */
        &Buffer_PBSpiChannel_4,
        /* The length of the actual data to be transmitted on the channel (Byte). */
        &Spi_ChannelActualDataLengthCore1[1],
        /* Defines the first starting bit for transmission */
        ESPI_BITORDER_MSB
    },
    {
        /* SPI channel ID: SpiChannel_5 */
        5U,
        /* Buffer Type IB/EB. */
        SPI_IB,
        /* SPI data width in channel */
        ESPI_DATAWIDTH_32,
        /* The number of bytes occupied by a data bits */
        ESPI_DATABUFFER_32BITS,
        /* Data length. SpiIbNBuffers */
        5U,
        /* Buffer Descriptor. */
        &Buffer_PBSpiChannel_5,
        /* The length of the actual data to be transmitted on the channel (Byte). */
        &Spi_ChannelActualDataLengthCore1[2],
        /* Defines the first starting bit for transmission */
        ESPI_BITORDER_MSB
    }
};

/* Channel to Job Assignment */
/* Channel list assigned in the SpiJob_1 */
static const Spi_ChannelType SpiJob_1_ChannelAssignment_PB[3] =
{
    3U,
    4U,
    5U
};

/* All Job configuration information in Core1 */
static const Spi_JobConfigType Spi_JobConfigSetCore1[SPI_MAX_JOB_CORE1] =
{
    {
        /* Spi Job ID: SpiJob_1 */
        (Spi_JobType)1U,
        /* SPI hardware number: Spi2 */
        (Spi_HWUnitType)2U,
        /* Configure whether to release the chip select after each frame of data */
        FALSE,
        /* External device ID configured by the job, SpiExternalDevice_1" */
        (Spi_ExternalDeviceType)1U,
        /* SpiJob_1 total channel counts */
        (Spi_ChannelType)3U,
        /* List of Channels */
        &SpiJob_1_ChannelAssignment_PB[0],
        /* End Notification */
        &Spi_JobNotificationTest1,
        /* Job Priority */
        0U,
        /* Implementation specific field referencing the channel internal state. */
        &Spi_JobStateCore1[0]
    }
};

/* Job to Sequence Assignment.
   Job ID with high priority are at the front of the Sequence list */
static const Spi_JobType SpiSequence_1_JobAssignment_PB[1] =
{
    1U
};

/* All Sequence configuration information in Core1 */
static const Spi_SequenceConfigType Spi_SequenceConfigSetCore1[SPI_MAX_SEQUENCE_CORE1] =
{
    {
        /* SPI Sequence ID: SpiSequence_1 */
        (Spi_SequenceType)1U,
        /*SWS_Spi_00126:
           When the SPI Handler/Driver is configured allowing interruptible Sequences, all Sequences
           declared shall have their dedicated parameter SpiInterruptibleSequence (see SWS_Spi_00064
           &amp; SPI106) to identify whether the Sequence can be suspended during transmission.
        */
        /* Sequence cann't be Interruptible */
        FALSE,
        /* Number of jobs in the sequence. */
        (Spi_JobType)1U,
        /* List of Jobs */
        &SpiSequence_1_JobAssignment_PB[0],
        /* bitx = 1 means Spix is occupy in current Sequence */
        (uint16)0x0004U,
        /* End Notification */
        &Spi_SeqNotificationTest1
    }
};

/* All ExternalDevice dynamic configuration information in Core1 */
static const Spi_ExternalDeviceConfigParamType SpiExternalDevice_ConfigParamCore1[SPI_MAX_EXT_DEV_CORE1] =
{
    {
        {
            /*
            SpiExternalDevice_1
            Baudrate parameter Tq is 4U.
            SpiModuleClock is 4.0E7
            Baudrate calculation formula:
            if SpiBaudParamB+SpiBaudParamC  = 0U: Baudrate = SpiModuleClock / (Tq*Q*(A+1))
            if SpiBaudParamB+SpiBaudParamC != 0U: Baudrate = SpiModuleClock / (Tq*Q*(A+B+C))
            Baudrate is 333333U.
            */
            /* Baudrate parameter A */
            ESPI_PARAMETER_A_ONE_UNIT,
            /* Baudrate parameter B */
            ESPI_PARAMETER_B_ONE_UNIT,
            /* Baudrate parameter C */
            ESPI_PARAMETER_C_ONE_UNIT,
            /* Baudrate parameter Q */
            10U
        },
        /* Defines the SPI Idle clock level  */
        ESPI_CLOCKPOLARITY_IDLE_HIGH,
        /* Defines the SPI data sampling edge */
        ESPI_CLOCKPHASE_SECONDSAMPLE,
        /* Defines disable SPI parity check */
        FALSE,
        /* Defines SPI CS channel number */
        ESPI_CS_CHANNEL_ID_6,
        /* Defines SPI CS active output level */
        ESPI_SLSOOUTPUT_LEVEL_HIGH,
        /* Define enable SPI internal chip select */
        FALSE
    }
};

/* All ExternalDevice static configuration information in Core1 */
static const Spi_ExternalDeviceConfigType Spi_ExternalDeviceConfigSetCore1[SPI_MAX_EXT_DEV_CORE1] =
{
    {
        /* SpiExternalDevice_1 use Espi HwUnit: Espi2 */
        (Spi_HWUnitType)2U,
        /* The chip select */
        SPI_CS_VIA_GPIO,
        /* Variable to restore Gpio CS pin. */
        (uint16)233U,
        /* Parity: NONE, Not using parity */
        ESPI_PARITYMODE_NONE,
        /* Delay parameters */
        {
        /* SpiModuleClock is 4.0E7 */
            {
            /* SpiTrailingTime =  (SpiParamTrailUnit + 1) * 4^SpiParamTrail / SpiModuleClock */
                ESPI_DELAY_PRESCALER_4,
                ESPI_DELAY_UNIT_2
            },
            {
            /* SpiTimeClk2Cs =  (SpiDelayParamLeadUnits + 1) * 4^SpiDelayParamLead / SpiModuleClock */
                ESPI_DELAY_PRESCALER_4,
                ESPI_DELAY_UNIT_2
            },
            {
            /* SpiIdleTime =  (SpiDelayParamIdleUnits + 1) * 4^SpiDelayParamIdle / SpiModuleClock */
                ESPI_DELAY_PRESCALER_4,
                ESPI_DELAY_UNIT_2
            }
        },
        /* External device configuration parameter structure */
        &SpiExternalDevice_ConfigParamCore1[0]
    }
};

/* All SPI PhyUnit configuration information in Core1 */
static const Spi_PhyUnitConfigParamType Spi_PhyUnitConfigParamCore1[SPI_MAX_HWUNIT_CORE1] =
{
    {
        /* SPI2 use Espi HwUnit:ESpi_2*/
        /* Timeout duration threshold */
        ESPI_EXPECTTIMEOUT_2097152,
        /* Set TX FIFO Threshold */
        ESPI_TXFIFO_THRESHOLD_ONE,
        /* Set RX FIFO Threshold */
        ESPI_RXFIFO_THRESHOLD_ONE,
        /* Set SPI TX FIFO move mode*/
        ESPI_FIFOMODE_SINGLE,
        /* Set SPI RX FIFO move mode*/
        ESPI_FIFOMODE_BATCH,
        /* Configuration Enable or Disable RX and ERROR interrupts */
        ESPI_INTC_FLAG_NO_ERROR,
        /* Define the SPI global clock frequency division factor (Tq) */
        4U,
        /* Enable/Disable SPI TX/RX DMA */
        FALSE,
        /* Enable Move Counter Mode */
        TRUE
    }
};

/* All SPI PhyUnit parameter configuration information in Core1 */
static const Spi_PhyUnitConfigType Spi_PhyUnitConfigSetCore1[SPI_MAX_HWUNIT_CORE1] =
{
    {
        /* Spi number is: Spi2  */
        (uint8)2U,
        /* Defines the TX DMA Channel ID referenced by the Spi HwUnit */
        0xFFU,
        /* Defines the RX DMA Channel ID referenced by the Spi HwUnit */
        0xFFU,
        /* Pointer DMA linked list Channel dynamic configuration information storage buffer */
        NULL_PTR,
        /* Points to the DMA linked list TCS storage buffer */
        NULL_PTR,
        /* SPI HwUnit configuration parameter structure */
        &Spi_PhyUnitConfigParamCore1[0]
    }
};

/* SPI driver configuration information in Core1 */
static const Spi_CoreConfigType Spi_ConfigSetCore1 =
{
    /* Number of sequences defined in the configuration. */
    SPI_MAX_SEQUENCE_CORE1,
    /* Number of jobs defined in the configuration. */
    SPI_MAX_JOB_CORE1,
    /* Number of channels defined in the configuration. */
    SPI_MAX_CHANNEL_CORE1,
    /* Number of external devices defined in the configuration. */
    SPI_MAX_EXT_DEV_CORE1,
    /* Number of HW unit defined in the configuration. */
    SPI_MAX_HWUNIT_CORE1,
    /* Pointer to Array of sequences defined in the Corex configuration */
    &Spi_SequenceConfigSetCore1[0],
    /* Pointer to Array of jobs defined in the Corex configuration */
    &Spi_JobConfigSetCore1[0],
    /* Pointer to Array of channels defined in the Corex configuration */
    &Spi_ChannelConfigSetCore1[0],
    /* Pointer to Array of External device instances defined in the Corex configuration */
    &Spi_ExternalDeviceConfigSetCore1[0],
    /* Pointer to Array of SPI device instances defined in the Corex configuration */
    &Spi_PhyUnitConfigSetCore1[0]
};

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_D_CORE1_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"
/****************************************************************************************************
**                          Global Constant Definitions                                            **
****************************************************************************************************/
/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_START_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"

/*
This array is used for mapping Spi Sequence to the Core.
Array index is Spi Sequence Id -> array member is index of Spi_SequenceSetCorex[x=0~4].
*/
static const Spi_SequenceType Spi_SequenceToCoreMap[SPI_MAX_SEQUENCE] =
{
    /* SpiSequence_0 configuration information is assigned to index0 of Core0 */
    0U,
    /* SpiSequence_1 configuration information is assigned to index0 of Core1 */
    0U
};

/*
This array is used for mapping Spi Job to the Core.
Array index is Spi Job Id -> array member is index of Spi_ChannelJobSetCorex[x=0~4].
*/
static const Spi_JobType Spi_JobToCoreMap[SPI_MAX_JOB] =
{
    /* SpiJob_0 configuration information is assigned to index0 of Core0 */
    0U,
    /* SpiJob_1 configuration information is assigned to index0 of Core1 */
    0U
};

/*
This array is used for mapping Spi Channel to the Core.
Array index is Spi Channel Id -> array member is index of Spi_ChannelConfigSetCorex[x=0~4].
*/
static const Spi_ChannelType Spi_ChannelToCoreMap[SPI_MAX_CHANNEL] =
{
    /* SpiChannel_0 configuration information is assigned to index0 of Core0 */
    0U,
    /* SpiChannel_1 configuration information is assigned to index1 of Core0 */
    1U,
    /* SpiChannel_2 configuration information is assigned to index2 of Core0 */
    2U,
    /* SpiChannel_3 configuration information is assigned to index0 of Core1 */
    0U,
    /* SpiChannel_4 configuration information is assigned to index1 of Core1 */
    1U,
    /* SpiChannel_5 configuration information is assigned to index2 of Core1 */
    2U
};

/*
This array is used for mapping Spi External Device to the Core.
Array index is Spi External Device Id -> array member is index of Spi_ExternalDeviceSetCorex[x=0~4].
*/
static const Spi_ExternalDeviceType Spi_ExternalDeviceToCoreMap[SPI_MAX_EXTERNAL_DEVICE] =
{
    /* SpiExternalDevice_0 configuration information is assigned to index0 of Core0 */
    /* SpiExternalDevice_0 is allocated to SPI0 */
    0U,
    /* SpiExternalDevice_1 configuration information is assigned to index0 of Core1 */
    /* SpiExternalDevice_1 is allocated to SPI2 */
    0U
};

/*
This array is used for mapping Spi hardware unit to the Core.
Array index is Spi hardware unit -> array member is index of Spi_PhyUnitConfigSetCorex[x=0~4].
*/
static const Spi_HWUnitType Spi_PhyUnitToCoreMap[SPI_MAX_HWUNIT_COUNT] =
{
    /* Spi0 configuration information is assigned to index0 of Core0 */
    0U,
    /* Spi1 not assigned */
    0xFFU,
    /* Spi2 configuration information is assigned to index0 of Core1 */
    0U,
    /* Spi3 not assigned */
    0xFFU,
    /* Spi4 not assigned */
    0xFFU,
    /* Spi5 not assigned */
    0xFFU,
    /* Spi6 not assigned */
    0xFFU,
    /* Spi7 not assigned */
    0xFFU,
    /* Spi8 not assigned */
    0xFFU
};

/*
This array is used for mapping DMA Channel to Spi hardware unit.
Array index is DMA Channel ID -> array member is index of Spi hardware unit[x=0~9].
*/
static const Spi_HWUnitType Spi_DmaChToPhyUnit[SPI_DMACHANNEL_COUNT] =
{
    /* DMA Channel0 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel1 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel2 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel3 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel4 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel5 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel6 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel7 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel8 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel9 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel10 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel11 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel12 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel13 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel14 isn't assigned to Spi */
    0xFFU,
    /* DMA Channel15 is assigned to Spi0 TX Channel */
    0U,
    /* DMA Channel16 is assigned to Spi0 RX Channel */
    0U
};

/* SPI available Espi hardware unit mapping table.*/
static ESPI_MODULE *const Spi_PhyUnitMap[SPI_MAX_HWUNIT_COUNT] =
{
    /* #Violation: Spi_PBcfg_c_REF_3 */
    ESPI0,        /* Espi0 is available*/
    /* #Violation: Spi_PBcfg_c_REF_3 */
    ESPI1,        /* Espi1 is available*/
    /* #Violation: Spi_PBcfg_c_REF_3 */
    ESPI2,        /* Espi2 is available*/
    /* #Violation: Spi_PBcfg_c_REF_3 */
    ESPI3,        /* Espi3 is available*/
    /* #Violation: Spi_PBcfg_c_REF_3 */
    ESPI4,        /* Espi4 is available*/
    /* #Violation: Spi_PBcfg_c_REF_3 */
    ESPI5,        /* Espi5 is available*/
    /* #Violation: Spi_PBcfg_c_REF_3 */
    ESPI6,        /* Espi6 is available*/
    /* #Violation: Spi_PBcfg_c_REF_3 */
    ESPI7,        /* Espi7 is available*/
    /* #Violation: Spi_PBcfg_c_REF_3 */
    ESPI8         /* Espi8 is available*/
};

/* Configuration parameters */
/* #Violation: Spi_PBcfg_c_REF_2 */
const Spi_ConfigType Spi_ConfigSet[SPI_CONFIG_COUNT] =
{
    {
        {
            /* Spi driver configuration of Core0 */
            &Spi_ConfigSetCore0,
            /* Spi driver configuration of Core1 */
            &Spi_ConfigSetCore1
        },
        /* The total number of Sequence configured in SpiSequence container */
        SPI_MAX_SEQUENCE,
        /* The total number of Jobs configured in SpiJob container */
        SPI_MAX_JOB,
        /* The total number of Channels configured in SpiChannel container */
        SPI_MAX_CHANNEL,
        /* The total number of Channels configured in SpiHwUnitConfig container */
        SPI_MAX_HWUNIT_COUNT,
        /* Define Sequence in the Corex mapping table */
        &Spi_SequenceToCoreMap[0],
        /* Define Job in the Corex mapping table */
        &Spi_JobToCoreMap[0],
        /* Define Channel in the Corex mapping table */
        &Spi_ChannelToCoreMap[0],
        /* Define External Device in the Corex mapping table */
        &Spi_ExternalDeviceToCoreMap[0],
        /* Define Spi HwUnit in the Corex mapping table */
        &Spi_PhyUnitToCoreMap[0],
        /* Map information that DMA Channel allocated to Spi HwUnit */
        &Spi_DmaChToPhyUnit[0],
        /* SPI available Espi hardware unit mapping table.*/
        &Spi_PhyUnitMap[0]
    }
};

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

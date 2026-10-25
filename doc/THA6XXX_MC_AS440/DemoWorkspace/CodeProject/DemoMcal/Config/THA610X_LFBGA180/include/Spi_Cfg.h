/***************************************************************************************************
*
****************************************************************************************************/
/***************************************************************************************************
*   FileName             : Spi_Cfg.h
*
*   Platform             : AUTOSAR
*
*   Peripheral           : Espi
*
*   brief                : This file will generate by EB tresos or Configurator Tools.
*
*   Autosar Version      : 4.4.0
*
*   Build Version         : Cortex-R52+/THA6xxx
*
*   Copyright (c) 2024 Tongxin Micro Co., Ltd. All Rights Reserved.
*
****************************************************************************************************/
/*
*#Violation Summary
*
*#Spi_Cfg_h_REF_1:MISRAC2012-Rule-2.5;
* Justification: The macros are reserved for upper layers.
*
*/

#ifndef SPI_CFG_H_
#define SPI_CFG_H_
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Version Information */
#define SPI_CFG_AR_RELEASE_MAJOR_VERSION         (4U)
#define SPI_CFG_AR_RELEASE_MINOR_VERSION         (4U)
#define SPI_CFG_AR_RELEASE_REVISION_VERSION      (0U)

#define SPI_CFG_SW_MAJOR_VERSION                 (1U)
#define SPI_CFG_SW_MINOR_VERSION                 (2U)
#define SPI_CFG_SW_PATCH_VERSION                 (0U)

#define SPI_CFG_VENDOR_ID                        (175U) /* 0xAF */
#define SPI_CFG_MODULE_ID                        (83U)  /* 0x53 */

/* ECUC_Spi_00227: SPI channel buffer type */
/* Internal buffer(IB) */
#define SPI_USAGE0                               (0x00U)
/* External buffer(EB) */
#define SPI_USAGE1                               (0x01U)
/* Internal buffer(IB) or External buffer(EB) */
#define SPI_USAGE2                               (0x02U)

/* ECUC_Spi_00231: SPI Handler/Driver level */
/* Only Simple Synchronous Behavior */
#define SPI_LEVEL0                               (0x00U)
/* Basic Asynchronous Behavior */
#define SPI_LEVEL1                               (0x01U)
/* Enhanced Behavior(Both Synchronous and Asynchronous) */
#define SPI_LEVEL2                               (0x02U)

/*ECUC_Spi_00228:
   Switches the development error detection and notification on or off.
  Configuration: SPI_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define SPI_DEV_ERROR_DETECT                     (STD_ON)

/*ECUC_Spi_00228:
   Switches the Functional Safety error detection and notification on or off.
  Configuration: SPI_SAFETY_ENABLE
- if Selected, Safety check is Enabled
- if Deselected, Safety check is Disabled
*/
#define SPI_SAFETY_ENABLE                        (STD_ON)
/*
  Configuration: SPI_DEM_REPORT_ERROR_STATUS
- Specifies whether report SPI_E_HARDWARE_ERROR.
*/
#define SPI_DEM_REPORT_ERROR_STATUS              (STD_OFF)
/*ECUC_Spi_00232:
  Configuration: SPI_VERSION_INFO_API
- if Selected, Function Intc_GetVersionInfo is Enabled
- if Deselected, Function Intc_GetVersionInfo is Disabled
*/
#define SPI_VERSION_INFO_API                     (STD_ON)
/*SWS_Spi_00142 ECUC_Spi_00229:
   The function Spi_GetHWUnitStatus is pre-compile time configurable On / Off by the configuration
   parameter SpiHwStatusApi.
  Configuration: SpiHwStatusApi
- if Selected, Function Spi_GetHWUnitStatus is Enabled
- if Deselected, Function Spi_GetHWUnitStatus is Disabled
*/
#define SPI_HW_STATUS_API                        (STD_ON)
/*ECUC_Spi_00226:
  Configuration: SpiCancelApi
- if Selected, Function Spi_Cancel is Enabled
- if Deselected, Function Spi_Cancel is Disabled
*/
#define SPI_CANCEL_API                           (STD_ON)
/*SWS_Spi_00114:
   The LEVEL 0 SPI Handler/Driver shall accept concurrent Spi_SyncTransmit(), if the sequences to be
   transmitted use different bus and parameter SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT is enabled. This
   feature shall be disabled per default. That means during a Sequence on-going transmission, all
   requests to transmit another Sequence shall be rejected.
  SWS_Spi_00146:
   The function Spi_Cancel is pre-compile time configurable On / Off by the configuration
   parameter SpiCancelApi.
  Configuration: SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT
- if Selected, Function Spi Concurrent synchronous transmission is Enabled
- if Deselected, Function Spi Concurrent synchronous transmission is Disabled
*/
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT     (STD_ON)

/*
  Configuration: SPI use DMA
- if Selected, Function Spi DMA is Enabled
- if Deselected, Function Spi DMA is Disabled
*/
#define SPI_ENABLE_DMA                           (STD_ON)
/*SWS_Spi_00121:
   The SPI Handler/Driver's environment shall configure the SpiInterruptibleSeqAllowed parameter
   (ON / OFF) in order to select which kind of Sequences the SPI Handler/Driver manages.
  SWS_Spi_00123:
   When the SPI Handler/Driver is configured not allowing interruptible Sequences, all Sequences
   declared are considered as Non-Interruptible Sequences.
  SWS_Spi_00282:
   When the SPI Handler/Driver is configured not allowing interruptible Sequences their dedicated
   parameter SpiInterruptibleSequence can be omitted or the FALSE value should be used as default.
  ECUC_Spi_00230:
   Switches the Interruptible Sequences handling functionality ON or OFF.
  Configuration: SpiInterruptibleSeqAllowed
- if Selected, SPI sequence interrupt allowed
- if Deselected, SPI sequence interrupt not allowed
*/
#define SPI_INTERRUPTIBLE_SEQ_ALLOWED            (STD_ON)
/*ECUC_Spi_00212:
   This parameter enables or not the Chip Select handling functions. If this parameter is enabled
   then parameter SpiCsSelection further details the type of chip selection.
  Configuration: SpiEnableCs
- Macro definition whether enable Customer CS.
*/
#define SPI_CUSTOMIZED_CS_EN                     (STD_ON)
/*SWS_Spi_00111:
   The SpiChannelBuffersAllowed parameter shall be configured with one of the 3 authorized values
   (0, 1 or 2) according to the described usage.
  ECUC_Spi_00227:
   Selects the SPI Handler/Driver Channel Buffers usage allowed and delivered.
  Configuration: SpiChannelBuffersAllowed
- SPI_USAGE0, Only Internal Buffers (IB) are allowed
- SPI_USAGE1, Only External buffers (EB) are allowed
- SPI_USAGE2, Both Internal (IB) and External (EB) buffers are allowed
*/
#define SPI_CHANNEL_BUFFERS_ALLOWED              (SPI_USAGE2)
/*SWS_Spi_00110:
   The SpiLevelDelivered parameter shall be configured with one of the 3 authorized values according
   to the described levels (0, 1 or 2) to allow the selection of the SPI Handler/Driver's level of
   scalable functionality.
  ECUC_Spi_00231:
   Selects the SPI Handler/Driver level of scalable functionality that is available and delivered.
  Configuration: SpiLevelDelivered
- SPI_Level0: Only Simple Synchronous Behavior
- SPI_Level1: Basic Asynchronous Behavior
- SPI_Level2: Enhanced Behavior(Both Synchronous and Asynchronous).
*/
#define SPI_LEVEL_DELIVERED                      (SPI_LEVEL2)

/*
  Configuration: SpiTransmitTimeout
- Timeout value used to wait for the TX transfer to complete and the RX flag to be set. Unit: us
*/
#define SPI_TIMEOUT_US                           (1000ULL)

/*ECUC_Spi_00242:
   This parameter defines the cycle time of the function Spi_MainFunction_Handling in seconds.
   The parameter is not used by the driver it self, but it is used by upper layer.
  Configuration: SpiMainFunctionPeriod
- Defines the cycle time of the function Spi_MainFunction_Handling in seconds
*/
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAIN_FUNCTION_PERIOD                 (0.01)
/*
  Configuration: Job Priority
- Define the total number of Job priorities.
*/
#define SPI_JOB_PRIORITY_LEVELS_COUNT            (4U)

/* Spi configuration count */
#define SPI_CONFIG_COUNT                         (1U)

/* Spi maximum number of Sequence configured in Core0 */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_SEQUENCE_CORE0                   (2U)

/* Spi maximum number of HW unit configured in Core0 */
#define SPI_MAX_HWUNIT_CORE0                     (2U)
/* Spi maximum number of HW unit configured in Core1 */
#define SPI_MAX_HWUNIT_CORE1                     (0U)

/*
  Configuration: SPI Enable
Generate the macro definition for SPI enable.
*/
#define SPI_HWUNIT_EXISTS_SPI0                   (STD_ON)
#define SPI_HWUNIT_EXISTS_SPI2                   (STD_ON)

/*
  Configuration: Sequence Name
Generate the macro definition for Sequence name.
*/
/* SpiSequenceId: 0 -> SpiSequence_0, mapped to Core0 */
#ifndef SpiConf_SpiSequence_SpiSequence_0
#define SpiConf_SpiSequence_SpiSequence_0        ((Spi_SequenceType)0U)
#endif
/* SpiSequenceId: 1 -> SpiSequence_1, mapped to Core0 */
#ifndef SpiConf_SpiSequence_SpiSequence_1
#define SpiConf_SpiSequence_SpiSequence_1        ((Spi_SequenceType)1U)
#endif

/*
  Configuration: Job Name
Generate the macro definition for Job name.
*/
/* SpiJobId: 0 -> SpiJob_0, mapped to Core0 */
#ifndef SpiConf_SpiJob_SpiJob_0
#define SpiConf_SpiJob_SpiJob_0                  ((Spi_JobType)0U)
#endif
/* SpiJobId: 1 -> SpiJob_1, mapped to Core0 */
#ifndef SpiConf_SpiJob_SpiJob_1
#define SpiConf_SpiJob_SpiJob_1                  ((Spi_JobType)1U)
#endif

/*
  Configuration: Channel Name
Generate the macro definition for Channel name.
*/
/* SpiChannelId: 0 -> SpiChannel_0, mapped to Core0 */
#ifndef SpiConf_SpiChannel_SpiChannel_0
#define SpiConf_SpiChannel_SpiChannel_0          ((Spi_ChannelType)0U)
#endif
/* SpiChannelId: 1 -> SpiChannel_1, mapped to Core0 */
#ifndef SpiConf_SpiChannel_SpiChannel_1
#define SpiConf_SpiChannel_SpiChannel_1          ((Spi_ChannelType)1U)
#endif
/* SpiChannelId: 2 -> SpiChannel_2, mapped to Core0 */
#ifndef SpiConf_SpiChannel_SpiChannel_2
#define SpiConf_SpiChannel_SpiChannel_2          ((Spi_ChannelType)2U)
#endif
/* SpiChannelId: 3 -> SpiChannel_3, mapped to Core0 */
#ifndef SpiConf_SpiChannel_SpiChannel_3
#define SpiConf_SpiChannel_SpiChannel_3          ((Spi_ChannelType)3U)
#endif
/* SpiChannelId: 4 -> SpiChannel_4, mapped to Core0 */
#ifndef SpiConf_SpiChannel_SpiChannel_4
#define SpiConf_SpiChannel_SpiChannel_4          ((Spi_ChannelType)4U)
#endif
/* SpiChannelId: 5 -> SpiChannel_5, mapped to Core0 */
#ifndef SpiConf_SpiChannel_SpiChannel_5
#define SpiConf_SpiChannel_SpiChannel_5          ((Spi_ChannelType)5U)
#endif

/*
Macro definition: SPI HwUnit name
Generate the macro definition for SPI config name.
*/
/* SpiHwUnitId: 0 -> SPI0, mapped to ESPI0 in Core0 */
#ifndef SpiConf_SpiHwUnitConfig_SPI0
#define SpiConf_SpiHwUnitConfig_SPI0        ((Spi_ChannelType)0U)
#endif
/* SpiHwUnitId: 1 -> SPI2, mapped to ESPI2 in Core0 */
#ifndef SpiConf_SpiHwUnitConfig_SPI2
#define SpiConf_SpiHwUnitConfig_SPI2        ((Spi_ChannelType)2U)
#endif

/*
Macro definition: SPI HwUnit name
Generate the macro definition for ESPI HwUnit name.
*/
/* SpiHwUnitId: 0 -> SPI0, mapped to ESPI0 in Core0 */
#ifndef SpiConf_SpiHwUnitConfig_Espi0
#define SpiConf_SpiHwUnitConfig_Espi0            ((Spi_HWUnitType)0U)
#endif
/* SpiHwUnitId: 1 -> SPI2, mapped to ESPI2 in Core0 */
#ifndef SpiConf_SpiHwUnitConfig_Espi2
#define SpiConf_SpiHwUnitConfig_Espi2            ((Spi_HWUnitType)2U)
#endif
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

#endif /* _SPI_CFG_H_ */
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/

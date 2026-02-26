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
[!NOCODE!][!//
[!INCLUDE "Spi.m"!][!//
[!ENDNOCODE!][!//

[!CODE!][!//
[!INDENT "0"!][!//
#ifndef SPI_CFG_H_
#define SPI_CFG_H_
/****************************************************************************************************
**                          Global Macro Definitions                                               **
****************************************************************************************************/
/* Version Information */
#define SPI_CFG_AR_RELEASE_MAJOR_VERSION         ([!"num:i(CommonPublishedInformation/ArReleaseMajorVersion)"!]U)
#define SPI_CFG_AR_RELEASE_MINOR_VERSION         ([!"num:i(CommonPublishedInformation/ArReleaseMinorVersion)"!]U)
#define SPI_CFG_AR_RELEASE_REVISION_VERSION      ([!"num:i(CommonPublishedInformation/ArReleaseRevisionVersion)"!]U)

#define SPI_CFG_SW_MAJOR_VERSION                 ([!"num:i(CommonPublishedInformation/SwMajorVersion)"!]U)
#define SPI_CFG_SW_MINOR_VERSION                 ([!"num:i(CommonPublishedInformation/SwMinorVersion)"!]U)
#define SPI_CFG_SW_PATCH_VERSION                 ([!"num:i(CommonPublishedInformation/SwPatchVersion)"!]U)

#define SPI_CFG_VENDOR_ID                        ([!"num:i(CommonPublishedInformation/VendorId)"!]U) /* 0x[!"substring-after(text:toupper(num:inttohex(CommonPublishedInformation/VendorId)), 'X')"!] */
#define SPI_CFG_MODULE_ID                        ([!"num:i(CommonPublishedInformation/ModuleId)"!]U)  /* 0x[!"substring-after(text:toupper(num:inttohex(CommonPublishedInformation/ModuleId)), 'X')"!] */

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
    [!WS "3"!]Switches the development error detection and notification on or off.
[!WS "2"!]Configuration: SPI_DEV_ERROR_DETECT
- if Selected, DET is Enabled
- if Deselected, DET is Disabled
*/
#define SPI_DEV_ERROR_DETECT                     ([!IF "SpiGeneral/SpiDevErrorDetect"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/*ECUC_Spi_00228:
    [!WS "3"!]Switches the Functional Safety error detection and notification on or off.
[!WS "2"!]Configuration: SPI_SAFETY_ENABLE
- if Selected, Safety check is Enabled
- if Deselected, Safety check is Disabled
*/
#define SPI_SAFETY_ENABLE                        [!IF "SpiGeneral/SpiSafetyErrorDetect = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!][!//

/*
[!WS "2"!]Configuration: SPI_DEM_REPORT_ERROR_STATUS
- Specifies whether report SPI_E_HARDWARE_ERROR.
*/
[!IF "not(node:exists(SpiDemEventParameterRefs/SPI_E_HARDWARE_ERROR))"!][!//
#define SPI_DEM_REPORT_ERROR_STATUS              (STD_OFF)
[!ELSE!]
#define SPI_DEM_REPORT_ERROR_STATUS              (STD_ON)
/*
[!WS "2"!]Configuration: SPI_E_HARDWARE_ERROR
- Defining Hardware Error Event IDs.
*/
#define SPI_E_HARDWARE_ERROR                      ((Dem_EventIdType)DemConf_DemEventParameter_[!"node:name(node:ref(SpiDemEventParameterRefs/SPI_E_HARDWARE_ERROR))"!])
[!ENDIF!][!//
/*ECUC_Spi_00232:
[!WS "2"!]Configuration: SPI_VERSION_INFO_API
- if Selected, Function Intc_GetVersionInfo is Enabled
- if Deselected, Function Intc_GetVersionInfo is Disabled
*/
#define SPI_VERSION_INFO_API                     ([!IF "SpiGeneral/SpiVersionInfoApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/*SWS_Spi_00142 ECUC_Spi_00229:
    [!WS "3"!]The function Spi_GetHWUnitStatus is pre-compile time configurable On / Off by the configuration
    [!WS "3"!]parameter SpiHwStatusApi.
    [!WS "2"!]Configuration: SpiHwStatusApi
- if Selected, Function Spi_GetHWUnitStatus is Enabled
- if Deselected, Function Spi_GetHWUnitStatus is Disabled
*/
#define SPI_HW_STATUS_API                        ([!IF "SpiGeneral/SpiHwStatusApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/*ECUC_Spi_00226:
[!WS "2"!]Configuration: SpiCancelApi
- if Selected, Function Spi_Cancel is Enabled
- if Deselected, Function Spi_Cancel is Disabled
*/
#define SPI_CANCEL_API                           ([!IF "SpiGeneral/SpiCancelApi"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/*SWS_Spi_00114:
    [!WS "3"!]The LEVEL 0 SPI Handler/Driver shall accept concurrent Spi_SyncTransmit(), if the sequences to be
    [!WS "3"!]transmitted use different bus and parameter SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT is enabled. This
    [!WS "3"!]feature shall be disabled per default. That means during a Sequence on-going transmission, all
    [!WS "3"!]requests to transmit another Sequence shall be rejected.
[!WS "2"!]SWS_Spi_00146:
    [!WS "3"!]The function Spi_Cancel is pre-compile time configurable On / Off by the configuration
    [!WS "3"!]parameter SpiCancelApi.
[!WS "2"!]Configuration: SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT
- if Selected, Function Spi Concurrent synchronous transmission is Enabled
- if Deselected, Function Spi Concurrent synchronous transmission is Disabled
*/
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_SUPPORT_CONCURRENT_SYNC_TRANSMIT     ([!IF "SpiGeneral/SpiSupportConcurrentSyncTransmit"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])

/*
[!WS "2"!]Configuration: SPI use DMA
- if Selected, Function Spi DMA is Enabled
- if Deselected, Function Spi DMA is Disabled
*/
#define SPI_ENABLE_DMA                           ([!IF "contains($SpiUseDmaMaskMappedCorex, 'true')"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/*SWS_Spi_00121:
    [!WS "3"!]The SPI Handler/Driver's environment shall configure the SpiInterruptibleSeqAllowed parameter
    [!WS "3"!](ON / OFF) in order to select which kind of Sequences the SPI Handler/Driver manages.
    [!WS "2"!]SWS_Spi_00123:
    [!WS "3"!]When the SPI Handler/Driver is configured not allowing interruptible Sequences, all Sequences
    [!WS "3"!]declared are considered as Non-Interruptible Sequences.
    [!WS "2"!]SWS_Spi_00282:
    [!WS "3"!]When the SPI Handler/Driver is configured not allowing interruptible Sequences their dedicated
    [!WS "3"!]parameter SpiInterruptibleSequence can be omitted or the FALSE value should be used as default.
    [!WS "2"!]ECUC_Spi_00230:
    [!WS "3"!]Switches the Interruptible Sequences handling functionality ON or OFF.
[!WS "2"!]Configuration: SpiInterruptibleSeqAllowed
- if Selected, SPI sequence interrupt allowed
- if Deselected, SPI sequence interrupt not allowed
*/
#define SPI_INTERRUPTIBLE_SEQ_ALLOWED            ([!IF "SpiGeneral/SpiLevelDelivered != num:i(0) and SpiGeneral/SpiInterruptibleSeqAllowed = 'true'"!]STD_ON[!ELSE!]STD_OFF[!ENDIF!])
/*ECUC_Spi_00212:
    [!WS "3"!]This parameter enables or not the Chip Select handling functions. If this parameter is enabled
    [!WS "3"!]then parameter SpiCsSelection further details the type of chip selection.
    [!WS "2"!]Configuration: SpiEnableCs
- Macro definition whether enable Customer CS.
*/
[!CALL "CG_GenerateCustomizeCsEnMacro"!][!//
/*SWS_Spi_00111:
    [!WS "3"!]The SpiChannelBuffersAllowed parameter shall be configured with one of the 3 authorized values
    [!WS "3"!](0, 1 or 2) according to the described usage.
    [!WS "2"!]ECUC_Spi_00227:
    [!WS "3"!]Selects the SPI Handler/Driver Channel Buffers usage allowed and delivered.
[!WS "2"!]Configuration: SpiChannelBuffersAllowed
- SPI_USAGE0, Only Internal Buffers (IB) are allowed
- SPI_USAGE1, Only External buffers (EB) are allowed
- SPI_USAGE2, Both Internal (IB) and External (EB) buffers are allowed
*/
#define SPI_CHANNEL_BUFFERS_ALLOWED              (SPI_USAGE[!"SpiGeneral/SpiChannelBuffersAllowed"!])
/*SWS_Spi_00110:
    [!WS "3"!]The SpiLevelDelivered parameter shall be configured with one of the 3 authorized values according
    [!WS "3"!]to the described levels (0, 1 or 2) to allow the selection of the SPI Handler/Driver's level of
    [!WS "3"!]scalable functionality.
    [!WS "2"!]ECUC_Spi_00231:
    [!WS "3"!]Selects the SPI Handler/Driver level of scalable functionality that is available and delivered.
[!WS "2"!]Configuration: SpiLevelDelivered
- SPI_Level0: Only Simple Synchronous Behavior
- SPI_Level1: Basic Asynchronous Behavior
- SPI_Level2: Enhanced Behavior(Both Synchronous and Asynchronous).
*/
#define SPI_LEVEL_DELIVERED                      (SPI_LEVEL[!"SpiGeneral/SpiLevelDelivered"!])

/*
[!WS "2"!]Configuration: SpiTransmitTimeout
- Timeout value used to wait for the TX transfer to complete and the RX flag to be set. Unit: us
*/
#define SPI_TIMEOUT_US                           ([!"num:i(SpiGeneral/SpiTransmitTimeout)"!]ULL)

[!IF " node:exists(SpiGeneral/SpiMainFunctionPeriod)"!][!//
/*ECUC_Spi_00242:
    [!WS "3"!]This parameter defines the cycle time of the function Spi_MainFunction_Handling in seconds.
    [!WS "3"!]The parameter is not used by the driver it self, but it is used by upper layer.
    [!WS "2"!]Configuration: SpiMainFunctionPeriod
- Defines the cycle time of the function Spi_MainFunction_Handling in seconds
*/
    /* #Violation: Spi_Cfg_h_REF_1 */
    #define SPI_MAIN_FUNCTION_PERIOD                 ([!"num:f(SpiGeneral/SpiMainFunctionPeriod)"!])
[!ENDIF!][!//
[!IF "SpiGeneral/SpiLevelDelivered = 1 or SpiGeneral/SpiLevelDelivered = 2"!][!//
/*
[!WS "2"!]Configuration: Job Priority
- Define the total number of Job priorities.
*/
#define SPI_JOB_PRIORITY_LEVELS_COUNT            (4U)
[!ENDIF!][!//

/* Spi configuration count */
#define SPI_CONFIG_COUNT                         (1U)

[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!VAR "SpiSeqNumCorex" = "num:i(substring-after(text:split($SpiSeqMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
[!IF "num:i($SpiSeqNumCorex) != num:i(0)"!][!//
/* Spi maximum number of Sequence configured in Core[!"$CoreIndex"!] */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_SEQUENCE_CORE[!"$CoreIndex"!]    [!WS "15"!]([!"$SpiSeqNumCorex"!]U)
[!ENDIF!][!//
[!ENDFOR!][!//

[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!VAR "SpiHwUnitNumCorex" = "num:i(substring-after(text:split($SpiHwUnitMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
/* Spi maximum number of HW unit configured in Core[!"$CoreIndex"!] */
#define SPI_MAX_HWUNIT_CORE[!"$CoreIndex"!]      [!WS "15"!]([!"$SpiHwUnitNumCorex"!]U)
[!ENDFOR!][!//

[!IF "SpiGeneral/SpiLevelDelivered = 1 or SpiGeneral/SpiLevelDelivered = 2"!][!//
/*
[!WS "2"!]Configuration: SPI Enable
 Generate the macro definition for SPI enable.
*/
[!LOOP "node:order(SpiDriver/SpiHwUnitConfig/*, './SpiHWUnitMapping')"!][!//
#define SPI_HWUNIT_EXISTS_SPI[!"substring-after(./SpiHWUnitMapping,'Spi_')"!]    [!WS "15"!](STD_ON)
[!ENDLOOP!][!//
[!/* Line feed */!]
[!ENDIF!][!//
/*
[!WS "2"!]Configuration: Sequence Name
 Generate the macro definition for Sequence name.
*/
[!CALL "CG_GenerateSeqIdMacro"!][!//

/*
[!WS "2"!]Configuration: Job Name
 Generate the macro definition for Job name.
*/
[!CALL "CG_GenerateJobIdMacro"!][!//

/*
[!WS "2"!]Configuration: Channel Name
 Generate the macro definition for Channel name.
*/
[!CALL "CG_GenerateChannelIdMacro"!][!//

/*
Macro definition: SPI HwUnit name
 Generate the macro definition for SPI config name.
*/
[!CALL "CG_GenerateHwUnitIdMacro"!][!//

/*
Macro definition: SPI HwUnit name
 Generate the macro definition for ESPI HwUnit name.
*/
[!CALL "CG_GenerateHwUnitMacro"!][!//
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
[!ENDINDENT!][!//
[!ENDCODE!][!//
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
[!NOCODE!][!//
[!INCLUDE "Spi.m"!][!//
[!ENDNOCODE!][!//
[!CODE!][!//
[!INDENT "0"!][!//
#include "Spi.h"
#include "Spi_Cfg.h"
#include "tha6_cfg.h"
/***************************************************************************************************
*                               Local Macros
****************************************************************************************************/
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!VAR "SpiJobNumCorex" = "num:i(substring-after(text:split($SpiJobMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
[!IF "num:i($SpiJobNumCorex) != num:i(0)"!][!//
/* Spi maximum number of Job configured in Core[!"$CoreIndex"!] */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_JOB_CORE[!"$CoreIndex"!]         [!WS "15"!]([!"$SpiJobNumCorex"!]U)
[!ENDIF!][!//
[!ENDFOR!][!//

[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!VAR "SpiChannelNumCorex" = "num:i(substring-after(text:split($SpiChannelMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
[!IF "num:i($SpiChannelNumCorex) != num:i(0)"!][!//
/* Spi maximum number of Channel configured in Core[!"$CoreIndex"!] */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_CHANNEL_CORE[!"$CoreIndex"!]     [!WS "15"!]([!"$SpiChannelNumCorex"!]U)
[!ENDIF!][!//
[!ENDFOR!][!//

[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
[!VAR "SpiExDeviceNumCorex" = "num:i(substring-after(text:split($SpiExDeviceMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
[!IF "num:i($SpiExDeviceNumCorex) != num:i(0)"!][!//
/* Spi maximum number of External Device configured in Core[!"$CoreIndex"!] */
/* #Violation: Spi_Cfg_h_REF_1 */
#define SPI_MAX_EXT_DEV_CORE[!"$CoreIndex"!]     [!WS "15"!]([!"$SpiExDeviceNumCorex"!]U)
[!ENDIF!][!//
[!ENDFOR!][!//

/*
[!WS "2"!]Configuration: SpiSequence
- The total number of Sequence configured in SpiSequence container.
*/
#define SPI_MAX_SEQUENCE                         ([!"num:i(count(SpiDriver/SpiSequence/*))"!]U)
/*
[!WS "2"!]Configuration: SpiJob
- The total number of Jobs configured in SpiJob container.
*/
#define SPI_MAX_JOB                              ([!"num:i(count(SpiDriver/SpiJob/*))"!]U)
/*
[!WS "2"!]Configuration: SpiChannel
- The total number of Channels configured in SpiChannel container.
*/
#define SPI_MAX_CHANNEL                          ([!"num:i(count(SpiDriver/SpiChannel/*))"!]U)
/*
[!WS "2"!]Configuration: SpiExternalDevice
- The total number of External Device configured in SpiExternalDevice container.
*/
#define SPI_MAX_EXTERNAL_DEVICE                  ([!"num:i(count(SpiDriver/SpiExternalDevice/*))"!]U)
/*
[!WS "2"!]Configuration: SpiMaxHwUnit
- The total number of Spi hardware microcontroller peripherals available and handled by
- this SPI Handler/Driver module.
*/
#define SPI_MAX_HWUNIT_COUNT                     ([!"num:i(count(text:split(ecu:get('Spi.HwUnitList'),', ')))"!]U)
/*
[!WS "2"!]Configuration: SpiMaxDmaChannel
- The max Channel of DMA assigned to this SPI Handler/Driver module.
*/
#define SPI_DMACHANNEL_COUNT                     ([!"num:i($MaxDMAChannel + 1)"!]U)
/****************************************************************************************************
**                          External Function Declarations                                         **
****************************************************************************************************/
[!IF "node:exists(SpiDriver/SpiSequence/*/SpiSeqEndNotification) = 'true'"!][!//
/*SWS_Spi_00264:
    [!WS "3"!]The SPI Handler/Driver shall use the callback routines Spi_SeqEndNotification to inform
    [!WS "3"!]other software modules about certain states or state changes.
    [!WS "2"!]SWS_Spi_00265:
    [!WS "3"!]For implement the call back function other modules are required to provide the routines
    [!WS "3"!]in the expected manner.
    [!WS "2"!]SWS_Spi_00048:
    [!WS "3"!]The callback notifications Spi_JobEndNotification and Spi_SeqEndNotification shall have
    [!WS "3"!]no parameters and no return value.
    [!WS "2"!]SWS_Spi_00341:
    [!WS "3"!]The operation SpiSeqEndNotification is Re-entrant.
*/
[!ENDIF!][!//
[!LOOP "node:order(SpiDriver/SpiSequence/*, 'SpiSequenceId')"!][!//
    [!IF "node:exists(./SpiSeqEndNotification) = 'true'"!][!//
        /* SpiJob[!"./SpiSequenceId"!] 'SpiSeqEndNotification' Function Declartion */
        extern void [!"node:value(SpiSeqEndNotification)"!](void);
    [!ENDIF!][!//
[!ENDLOOP!][!//
[!IF "node:exists(SpiDriver/SpiJob/*/SpiJobEndNotification) = 'true'"!][!//
/*SWS_Spi_00075:
    [!WS "3"!]The SPI Handler/Driver shall use the callback routines Spi_JobEndNotification to inform
    [!WS "3"!]other software modules about certain states or state changes.
    [!WS "2"!]SWS_Spi_00265:
    [!WS "3"!]For implement the call back function other modules are required to provide the routines
    [!WS "3"!]in the expected manner.
    [!WS "2"!]SWS_Spi_00048:
    [!WS "3"!]The callback notifications Spi_JobEndNotification and Spi_SeqEndNotification shall have
    [!WS "3"!]no parameters and no return value.
    [!WS "2"!]SWS_Spi_00340:
    [!WS "3"!]The operation SpiJobEndNotification is Re-entrant.
*/
[!ENDIF!][!//
[!LOOP "node:order(SpiDriver/SpiJob/*, 'SpiJobId')"!][!//
    [!IF "node:exists(./SpiJobEndNotification) = 'true'"!][!//
        /* SpiJob[!"./SpiJobId"!] 'SpiJobEndNotification' Function Declartion */
        extern void [!"node:value(SpiJobEndNotification)"!](void);
    [!ENDIF!][!//
[!ENDLOOP!][!//
/****************************************************************************************************
**                          Private Variable Definitions                                           **
****************************************************************************************************/
[!CALL "CG_GenerateEBIBEBbuffer"!][!//
/****************************************************************************************************
**                          Global Variable Definitions                                            **
****************************************************************************************************/

/****************************************************************************************************
**                          Private Constant Definitions                                           **
****************************************************************************************************/
[!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
    [!VAR "SpiChannelNumCorex" = "num:i(substring-after(text:split($SpiChannelMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
    [!VAR "SpiJobNumCorex" = "num:i(substring-after(text:split($SpiJobMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
    [!VAR "SpiSeqNumCorex" = "num:i(substring-after(text:split($SpiSeqMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
    [!VAR "SpiHwUnitNumCorex" = "num:i(substring-after(text:split($SpiHwUnitMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
    [!VAR "SpiExDeviceNumCorex" = "num:i(substring-after(text:split($SpiExDeviceMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
    [!VAR "SpiUseDmaMaskCorex" = "substring-after(text:split($SpiUseDmaMaskMappedCorex)[num:i($CoreIndex + 1)], ':')"!][!/* CoreId:Num--->1:false */!][!//
    [!IF "$SpiHwUnitNumCorex != num:i(0)"!][!//
        [!IF "$SpiExDeviceNumCorex = num:i(0)"!][!//
            /* There are some hardware units assigned to core[!"$CoreIndex"!],
               but no external devices are assigned to these hardware units,
               So no configuration code will be generated here. */
            [!/* Line feed */!]
        [!ELSEIF "$SpiJobNumCorex = num:i(0)"!][!//
            /* There are some hardware units assigned to core[!"$CoreIndex"!],
               but no jobs are assigned to these hardware units,
            So no configuration code will be generated here. */
            [!/* Line feed */!]
        [!ENDIF!][!//
    [!ENDIF!][!//
    [!//
    [!IF "($SpiHwUnitNumCorex != num:i(0))
          and ($SpiChannelNumCorex != num:i(0))
          and ($SpiJobNumCorex != num:i(0))
          and ($SpiSeqNumCorex != num:i(0))
          and ($SpiExDeviceNumCorex != num:i(0))"!][!//
        /* #Violation: Spi_PBcfg_c_REF_1 */
        #define SPI_START_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
        /* #Violation: Spi_PBcfg_c_REF_4 */
        #include "Spi_MemMap.h"

        /* All Channel configuration information in Core[!"$CoreIndex"!] */
        static const Spi_ChannelConfigType Spi_ChannelConfigSetCore[!"$CoreIndex"!][SPI_MAX_CHANNEL_CORE[!"num:i($CoreIndex)"!]] =
        {
            [!CALL "CG_GenerateChannelConfig"!][!//
        };

        /* Channel to Job Assignment */
        [!/* Retrieves all Channel assignments */!][!//
        [!LOOP "node:order(SpiDriver/SpiJob/*, 'SpiJobId')"!][!//
            [!CALL "CG_FindSpiJobMappedCoreId", "SpiJobName"="node:name(.)"!][!//
            [!IF "$SpiJobMappedCoreId = $CoreIndex"!][!//
                [!VAR "TotalAssignedChNum" = "num:i(count(SpiChannelList/*))"!][!//
                /* Channel list assigned in the [!"node:name(.)"!] */
                static const Spi_ChannelType [!"name(.)"!]_ChannelAssignment_PB[[!"$TotalAssignedChNum"!]] =
                {
                    [!INDENT "4"!][!//
                    [!LOOP "node:order(SpiChannelList/*, 'SpiChannelIndex')"!][!//
                        [!VAR "TotalAssignedChNum" = "$TotalAssignedChNum - 1"!][!//
                        [!"num:i(node:value(node:ref(SpiChannelAssignment)/SpiChannelId))"!]U[!IF "num:i(0) < num:i($TotalAssignedChNum)"!],[!ENDIF!]
                    [!ENDLOOP!][!//
                    [!ENDINDENT!][!//
                };
                [!/* Line feed */!]
            [!ENDIF!][!//
        [!ENDLOOP!][!//
        [!//
        /* All Job configuration information in Core[!"$CoreIndex"!] */
        static const Spi_JobConfigType Spi_JobConfigSetCore[!"$CoreIndex"!][SPI_MAX_JOB_CORE[!"num:i($CoreIndex)"!]] =
        {
            [!CALL "CG_GenerateJobConfig"!][!//
        };

        /* Job to Sequence Assignment.
        [!WS "3"!]Job ID with high priority are at the front of the Sequence list */
        [!LOOP "node:order(SpiDriver/SpiSequence/*, 'SpiSequenceId')"!][!//
            [!CALL "CG_FindSpiSequenceMappedCoreId", "SpiSequenceName"="node:name(.)"!][!//
            [!IF "$SpiSequenceMappedCoreId = $CoreIndex"!][!//
                [!VAR "EndFlg" = "num:i(0)"!][!//
                [!VAR "TotalAssignedJobNum" = "num:i(count(SpiJobAssignment/*))"!][!//
                static const Spi_JobType [!"name(.)"!]_JobAssignment_PB[[!"$TotalAssignedJobNum"!]] =
                {
                [!INDENT "4"!][!//
                [!/* Need be sort , the requirement from SWS_Spi_00002 */!][!//
                [!FOR "x" = "0" TO "3"!][!//
                    [!VAR "JobPriNum" = "3 - $x"!][!//
                    [!LOOP "SpiJobAssignment/*"!][!//
                        [!IF "num:i(node:value(node:ref(.)/SpiJobPriority)) = num:i($JobPriNum)"!][!//
                            [!"num:i(node:value(node:ref(.)/SpiJobId))"!]U[!//
                            [!IF "$EndFlg < num:i($TotalAssignedJobNum - 1)"!][!//
                            ,
                            [!ENDIF!][!//
                            [!VAR "EndFlg" = "$EndFlg + num:i(1)"!][!//
                        [!ENDIF!][!//
                    [!ENDLOOP!][!//
                [!ENDFOR!][!//
                [!ENDINDENT!][!//
                [!/* Line feed */!]
                };
            [!ENDIF!][!//
        [!ENDLOOP!][!//

        /* All Sequence configuration information in Core[!"$CoreIndex"!] */
        static const Spi_SequenceConfigType Spi_SequenceConfigSetCore[!"$CoreIndex"!][SPI_MAX_SEQUENCE_CORE[!"num:i($CoreIndex)"!]] =
        {
            [!CALL "CG_GenerateSeqConfig"!][!//
        };

        /* All ExternalDevice dynamic configuration information in Core[!"$CoreIndex"!] */
        static const Spi_ExternalDeviceConfigParamType SpiExternalDevice_ConfigParamCore[!"$CoreIndex"!][SPI_MAX_EXT_DEV_CORE[!"num:i($CoreIndex)"!]] =
        {
            [!CALL "CG_GenerateExternalDeviceDynamicConfig"!][!//
        };

        /* All ExternalDevice static configuration information in Core[!"$CoreIndex"!] */
        static const Spi_ExternalDeviceConfigType Spi_ExternalDeviceConfigSetCore[!"$CoreIndex"!][SPI_MAX_EXT_DEV_CORE[!"num:i($CoreIndex)"!]] =
        {
            [!CALL "CG_GenerateExternalDeviceConfig"!][!//
        };

        /* All SPI PhyUnit configuration information in Core[!"$CoreIndex"!] */
        static const Spi_PhyUnitConfigParamType Spi_PhyUnitConfigParamCore[!"$CoreIndex"!][SPI_MAX_HWUNIT_CORE[!"$CoreIndex"!]] =
        {
            [!CALL "CG_GenerateHwUnitDynamicConfig"!][!//
        };

        /* All SPI PhyUnit parameter configuration information in Core[!"$CoreIndex"!] */
        static const Spi_PhyUnitConfigType Spi_PhyUnitConfigSetCore[!"$CoreIndex"!][SPI_MAX_HWUNIT_CORE[!"$CoreIndex"!]] =
        {
            [!CALL "CG_GenerateHwUnitConfig"!][!//
        };

        /* SPI driver configuration information in Core[!"$CoreIndex"!] */
        static const Spi_CoreConfigType Spi_ConfigSetCore[!"$CoreIndex"!] =
        {
            [!INDENT "4"!][!//
            /* Number of sequences defined in the configuration. */
            SPI_MAX_SEQUENCE_CORE[!"$CoreIndex"!],
            /* Number of jobs defined in the configuration. */
            SPI_MAX_JOB_CORE[!"$CoreIndex"!],
            /* Number of channels defined in the configuration. */
            SPI_MAX_CHANNEL_CORE[!"$CoreIndex"!],
            /* Number of external devices defined in the configuration. */
            SPI_MAX_EXT_DEV_CORE[!"$CoreIndex"!],
            /* Number of HW unit defined in the configuration. */
            SPI_MAX_HWUNIT_CORE[!"$CoreIndex"!],
            /* Pointer to Array of sequences defined in the Corex configuration */
            &Spi_SequenceConfigSetCore[!"$CoreIndex"!][0],
            /* Pointer to Array of jobs defined in the Corex configuration */
            &Spi_JobConfigSetCore[!"$CoreIndex"!][0],
            /* Pointer to Array of channels defined in the Corex configuration */
            &Spi_ChannelConfigSetCore[!"$CoreIndex"!][0],
            /* Pointer to Array of External device instances defined in the Corex configuration */
            &Spi_ExternalDeviceConfigSetCore[!"$CoreIndex"!][0],
            /* Pointer to Array of SPI device instances defined in the Corex configuration */
            &Spi_PhyUnitConfigSetCore[!"$CoreIndex"!][0]
            [!ENDINDENT!][!//
        };

        /* #Violation: Spi_PBcfg_c_REF_1 */
        #define SPI_STOP_SEC_CONFIG_DATA_ASIL_D_CORE[!"$CoreIndex"!]_UNSPECIFIED
        /* #Violation: Spi_PBcfg_c_REF_4 */
        #include "Spi_MemMap.h"
    [!ENDIF!][!//
[!ENDFOR!][!//
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
    [!CALL "CG_GenerateSequencelToCoreMap"!][!//
};

/*
This array is used for mapping Spi Job to the Core.
Array index is Spi Job Id -> array member is index of Spi_ChannelJobSetCorex[x=0~4].
*/
static const Spi_JobType Spi_JobToCoreMap[SPI_MAX_JOB] =
{
    [!CALL "CG_GenerateJobToCoreMap"!][!//
};

/*
This array is used for mapping Spi Channel to the Core.
Array index is Spi Channel Id -> array member is index of Spi_ChannelConfigSetCorex[x=0~4].
*/
static const Spi_ChannelType Spi_ChannelToCoreMap[SPI_MAX_CHANNEL] =
{
    [!CALL "CG_GenerateChannelToCoreMap"!][!//
};

/*
This array is used for mapping Spi External Device to the Core.
Array index is Spi External Device Id -> array member is index of Spi_ExternalDeviceSetCorex[x=0~4].
*/
static const Spi_ExternalDeviceType Spi_ExternalDeviceToCoreMap[SPI_MAX_EXTERNAL_DEVICE] =
{
    [!CALL "CG_GenerateExternalDeviceToCoreMap"!][!//
};

/*
This array is used for mapping Spi hardware unit to the Core.
Array index is Spi hardware unit -> array member is index of Spi_PhyUnitConfigSetCorex[x=0~4].
*/
static const Spi_HWUnitType Spi_PhyUnitToCoreMap[SPI_MAX_HWUNIT_COUNT] =
{
    [!CALL "CG_GenerateHwUnitToCoreMap"!][!//
};

[!IF "contains($SpiUseDmaMaskMappedCorex, 'true')"!][!//
/*
This array is used for mapping DMA Channel to Spi hardware unit.
Array index is DMA Channel ID -> array member is index of Spi hardware unit[x=0~9].
*/
static const Spi_HWUnitType Spi_DmaChToPhyUnit[SPI_DMACHANNEL_COUNT] =
{
    [!CALL "CG_GenerateDmaChtoHwUnitMap"!][!//
};
[!ENDIF!][!//

/* SPI available Espi hardware unit mapping table.*/
static ESPI_MODULE *const Spi_PhyUnitMap[SPI_MAX_HWUNIT_COUNT] =
{
    [!CALL "CG_GeneHwUnitMap"!][!//
};

/* Configuration parameters */
/* #Violation: Spi_PBcfg_c_REF_2 */
[!IF "variant:name() != ''"!][!//
const Spi_ConfigType Spi_ConfigSet_[!"variant:name()"!][SPI_CONFIG_COUNT] =
[!ELSE!][!//
const Spi_ConfigType Spi_ConfigSet[SPI_CONFIG_COUNT] =
[!ENDIF!][!//
{
    [!INDENT "4"!][!//
    {
        [!INDENT "8"!][!//
        {
            [!INDENT "12"!][!//
            [!FOR "CoreIndex" = "0" TO "num:i(ecu:get('Resource.NumOfCores') - 1)"!][!//
                /* Spi driver configuration of Core[!"$CoreIndex"!] */
                [!VAR "SpiChannelNumCorex" = "num:i(substring-after(text:split($SpiChannelMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
                [!VAR "SpiJobNumCorex" = "num:i(substring-after(text:split($SpiJobMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
                [!VAR "SpiSeqNumCorex" = "num:i(substring-after(text:split($SpiSeqMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
                [!VAR "SpiHwUnitNumCorex" = "num:i(substring-after(text:split($SpiHwUnitMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
                [!VAR "SpiExDeviceNumCorex" = "num:i(substring-after(text:split($SpiExDeviceMappedCorex)[num:i($CoreIndex + 1)], ':'))"!][!/* CoreId:Num--->1:2 */!][!//
                [!IF "($SpiHwUnitNumCorex != num:i(0))
                      and ($SpiChannelNumCorex != num:i(0))
                      and ($SpiSeqNumCorex != num:i(0))
                      and ($SpiJobNumCorex != num:i(0))
                      and ($SpiExDeviceNumCorex != num:i(0))"!][!//
                    &Spi_ConfigSetCore[!"$CoreIndex"!][!IF "num:i($CoreIndex) != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ENDIF!]
                [!ELSE!][!//
                    NULL_PTR[!IF "num:i($CoreIndex) != num:i(ecu:get('Resource.NumOfCores') - 1)"!],[!ENDIF!]
                [!ENDIF!][!//
            [!ENDFOR!][!//
            [!ENDINDENT!][!//
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
[!IF "contains($SpiUseDmaMaskMappedCorex, 'true')"!][!//
        /* Map information that DMA Channel allocated to Spi HwUnit */
        &Spi_DmaChToPhyUnit[0],
[!ENDIF!][!//
        /* SPI available Espi hardware unit mapping table.*/
        &Spi_PhyUnitMap[0]
        [!ENDINDENT!][!//
    }
    [!ENDINDENT!][!//
};

/* #Violation: Spi_PBcfg_c_REF_1 */
#define SPI_STOP_SEC_CONFIG_DATA_ASIL_D_GLOBAL_UNSPECIFIED
/* #Violation: Spi_PBcfg_c_REF_4 */
#include "Spi_MemMap.h"
[!ENDINDENT!][!//
[!ENDCODE!][!//
/****************************************************************************************************
**                          End of File                                                            **
****************************************************************************************************/
